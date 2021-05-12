<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Hierarchical semi-Markov conditional random fields for deep recursive sequential data.
   </title>
   <abstract>
    We present the hierarchical semi-Markov conditional random field (HSCRF), a generalisation of linear-chain conditional random fields to model deep nested Markov processes. It is parameterised as a conditional log-linear model and has polynomial time algorithms for learning and inference. We derive algorithms for partially-supervised learning and constrained inference. We develop numerical scaling procedures that handle the overflow problem. We show that when depth is two, the HSCRF can be reduced to the semi-Markov conditional random fields. Finally, we demonstrate the HSCRF on two applications: (i) recognising human activities of daily living (ADLs) from indoor surveillance cameras, and (ii) noun-phrase chunking. The HSCRF is capable of learning rich hierarchical models with reasonable accuracy in both fully and partially observed data cases.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Modelling hierarchical depth in complex stochastic processes is important in many application domains. In a deep hierarchy, each level is an abstraction of lower level details [1], [2], [3], [4]. This paper studies recursively sequential processes, in that each level is a sequence and each node in a sequence can be decomposed further into a sub-sequence of finer grain [2].
     </paragraph>
     <paragraph>
      Consider, for example, a frequent activity performed by human ‘eat-breakfast’. It may include a series of more specific activities like ‘enter-kitchen’, ‘go-to-cupboard’, ‘take-cereal’, ‘wash-dishes’ and ‘leave-kitchen’. Each specific activity can be decomposed into finer details. Similarly, in natural language processing (NLP) syntax trees are inherently hierarchical. In a partial parsing task known as noun-phrase (NP) chunking [5], there are three syntactic levels: the sentence, noun-phrases and part-of-speech (POS) tags. In this setting, the sentence is a sequence of NPs and non-NPs, and each phrase is a sub-sequence of POS tags.
     </paragraph>
     <paragraph>
      A popular approach to deal with hierarchical data is to build a cascaded model where each level is modelled separately, and the output of the lower level is used as the input of the level right above it (e.g. see [6]). For instance, in NP chunking this approach first builds a POS tagger and then constructs a chunker that incorporates the output of the tagger. This approach is sub-optimal because the POS tagger takes no information of the NPs and the chunker is not aware of the reasoning of the tagger. In contrast, a noun-phrase is often very informative to infer the POS tags belonging to the phrase. As a result, this layered approach may suffer from the so-called cascading error problem in that errors introduced from the lower layer propagate to higher levels.
     </paragraph>
     <paragraph>
      A more holistic approach is to build a joint representation of all the levels. Formally, given a data sequence z we need to model and infer about the deep, nested semantic x. The main problem is to choose an appropriate representation of x so that inference can be efficient. An important class of representation is hierarchical hidden Markov model (HHMM) [2]. An HHMM is a nested hidden Markov network (HMM) in the sense that each state is also a sub HMM. Although HMMs represent only first-order Markov processes, HHMMs offer higher-order interaction. HHMMs are generative models with joint distribution {a mathematical formula}Pr⁡(x,z), where the data generating distribution {a mathematical formula}Pr⁡(z|x) must be simplified for efficient inference about the semantic {a mathematical formula}Pr⁡(x|z). An alternative is to model the discriminative distribution {a mathematical formula}Pr⁡(x|z) directly without modelling the data {a mathematical formula}Pr⁡(z). This can be more effective since arbitrary long-range and interdependent data features can be incorporated into the model.
     </paragraph>
     <paragraph>
      The most popular class of probabilistic structured output methods are conditional random fields (CRFs) [7], but the early models are flat. Deep variants have been introduced the past decade, including dynamic CRFs (DCRF) [8], hierarchical CRFs [9], [10]), and stacked CRFs [11]. However, these methods require a fixed pre-defined hierarchy, and thus are not suitable for problems with automatically inferred topologies.
     </paragraph>
     <paragraph>
      To this end, we construct a novel discriminative model called Hierarchical Semi-Markov Conditional Random Field (HSCRF).{sup:1} The HSCRF offers nested semantic similar to that by the HHMM but is parameterised as an undirected log-linear model. The HSCRF generalises linear-chain CRFs [7] and semi-Markov CRFs [13].
     </paragraph>
     <paragraph>
      To be more concrete, let us return to the NP chunking example. The problem can be modelled as a three-level HSCRF, where the root represents the sentence, the second level the NP process, and the bottom level the POS process. The root and the two processes are conditioned on the sequence of words in the sentence. Under discriminative modelling, rich contextual information can be simply encoded as features including starting and ending of a phrase, phrase length, and distribution of words falling inside the phrase can be effectively encoded. On the other hand, such encoding is much more difficult for HHMMs.
     </paragraph>
     <paragraph>
      We then proceed to address important issues. First, we show how to represent HSCRFs using a dynamic graphical model (e.g. see [14]) which effectively encodes hierarchical and temporal semantics. For parameter learning, an efficient algorithm based on the Asymmetric Inside–Outside of [15] is introduced. For inference, we generalise the Viterbi algorithm to decode the semantics from an observational sequence.
     </paragraph>
     <paragraph>
      The common assumptions in discriminative learning and inference are that the training data in learning is fully labelled, and the test data during inference is not labelled. We propose to relax these assumptions in that training labels may only be partially available. Likewise, when some labels are given during inference, the algorithm should automatically adjust to meet the new constraints.
     </paragraph>
     <paragraph>
      We demonstrate the effectiveness of HSCRFs in two applications: (i) segmenting and labelling activities of daily living (ADLs) in an indoor environment and (ii) jointly modelling noun-phrases and part-of-speeches in shallow parsing. Our experimental results in the first application show that the HSCRFs are capable of learning rich, hierarchical activities with good accuracy and exhibit better performance when compared to DCRFs and flat-CRFs. Results for the partially supervised case also demonstrate that significant reduction of training labels still results in models that perform reasonably well. We also show that observing a small amount of labels can significantly increase the accuracy during decoding. In shallow parsing, the HSCRFs can achieve higher accuracy than standard CRF-based techniques and the recent DCRFs.
     </paragraph>
     <paragraph>
      To summarise, in this paper we claim the following contributions:
     </paragraph>
     <list>
      <list-item label="•">
       Introducing a novel Hierarchical Semi-Markov Conditional Random Field (HSCRF) to model complex hierarchical and nested Markovian processes in a discriminative framework.
      </list-item>
      <list-item label="•">
       Developing an efficient generalised Asymmetric Inside–Outside (AIO) algorithm for full-supervised learning.
      </list-item>
      <list-item label="•">
       Generalising the Viterbi algorithm for decoding the most probable semantic labels and structure given an observational sequence.
      </list-item>
      <list-item label="•">
       Addressing the problem of partially-supervised learning and constrained inference.
      </list-item>
      <list-item label="•">
       Constructing a numerical scaling algorithm to prevent numerical overflow.
      </list-item>
      <list-item label="•">
       Demonstration of the applicability of the HSCRFs for modelling human activities in the domain of home video surveillance and shallow parsing of English.
      </list-item>
     </list>
     <paragraph>
      The rest of the paper is organised as follows. Section 2 reviews Conditional Random Fields and Hierarchical Hidden Markov Models. Section 3 continues with the HSCRF model definition. Section 4 defines building blocks required for common inference tasks. Section 5 presents the generalised Viterbi algorithm. Parameterisation and estimation follow in Section 6. Learning and inference with partially available labels are addressed in Section 7. Section 8 presents a method for numerical scaling to prevent numerical overflow. Section 9 documents experimental results. Section 11 concludes the paper.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      This section presents foundations upon which the proposed HSCRF is built: conditional random fields and hierarchical hidden Markov models. For later reference, we define mathematical notations in Table 1.
     </paragraph>
     <section label="2.1">
      <section-title>
       Conditional random fields
      </section-title>
      <paragraph>
       Denote by {a mathematical formula}G=(V,E) the graph where {a mathematical formula}V is the set of vertices, and {a mathematical formula}E is the set of edges. Associated with each vertex i is a state variable {a mathematical formula}xi Let x be joint state variable, i.e. {a mathematical formula}x=(xi)i∈V. Conditional random fields (CRFs) [7] define a conditional distribution given the observation z as follows{a mathematical formula} where c is the index of cliques in the graph, {a mathematical formula}ϕc(xc,z) is a non-negative potential function defined over the clique c, and {a mathematical formula}Z(z)=∑x∏cϕc(xc,z) is the partition function.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}{x˜} be the set of observed state variables with the empirical distribution {a mathematical formula}Q(x˜), and w be the parameter vector. Learning in CRFs is typically by maximising the (log) likelihood{a mathematical formula}
      </paragraph>
      <paragraph>
       The gradient of the log-likelihood can be computed as{a mathematical formula} Thus, the inference needed in CRF parameter estimation is the computation of clique marginals {a mathematical formula}Pr⁡(xc|z).
      </paragraph>
      <paragraph>
       Typically, CRFs are parameterised as log-linear models, i.e. {a mathematical formula}ϕc(xc,z)=exp⁡(w⊤f(xc,z)), where {a mathematical formula}f(.) is the feature vector and w is weight vector. Let {a mathematical formula}F(x,z)=∑cf(xc,z) be the global feature. Eq. (3) can be written as follows{a mathematical formula}{a mathematical formula} Thus gradient-based maximum likelihood learning in the log-linear setting boils down to estimating the feature expectations, also known as expected sufficient statistics (ESS).
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Learning with partial labels
       </section-title>
       <paragraph>
        Let {a mathematical formula}x˜=(v,h), where v is the set of visible variables, and h is the set of hidden variables. The incomplete log-likelihood and its gradient are given as{a mathematical formula} where {a mathematical formula}Z(v,z)=∑h∏cϕc(vc,hc,z). The gradient reads{a mathematical formula}
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        Sequential models
       </section-title>
       <paragraph>
        The most popular form of CRFs is linear-chain of order n, where n is typically a small integer. This allows fast estimation of the clique marginals {a mathematical formula}Pr⁡(xc|z) using a forward-backward procedure with time complexity of {a mathematical formula}O(TKn+1) for sequence length T and K states.
       </paragraph>
       <paragraph>
        A generalisation of chain-CRF is semi-Markov CRF (SemiCRF) [13], which is first-order Markovian in segments (but non-Markovian in states). A forward-backward procedure is adapted accordingly with time complexity of {a mathematical formula}O(TLK2) where L is the maximum segment length. In Appendix C we will show that the SemiCRF is a special case of the proposed HSCRF.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Hierarchical hidden Markov models
      </section-title>
      <paragraph>
       Hierarchical HMMs are generalisation of HMMs [16] in that a state in an HHMM may be a sub-HHMM. Thus, an HHMM is a nested Markov chain. In the temporal evolution of HHMM, when a child Markov chain terminates, it returns the control to its parent. Nothing from the terminated child chain is carried forward. Thus, the parent state abstracts out everything belonging to it. Upon receiving the return control the parent then either transits to a new parent or terminates.
      </paragraph>
      <paragraph>
       Fig. 1 illustrates the state transition diagram of a two-level HHMM. At the top level there are two parent states {a mathematical formula}{A,B}. Parent A has three children, i.e. {a mathematical formula}ch(A)={1,2,3} and B has four, i.e. {a mathematical formula}ch(B)={4,5,6,7}. At the top level the transitions are between A and B, as in a normal directed Markov chain. Under each parent there are also transitions between child states, which only depend on the direct parent (either A or B). There are special ending states (represented as shaded nodes in Fig. 1) to signify the termination of the Markov chains. At each time step of the child Markov chain, a child will emit an observational symbol (not shown here).
      </paragraph>
      <paragraph>
       The temporal evolution of the HHMM can be represented as a dynamic Bayesian network (DBN), which was first done in [17]. Fig. 2 depicts a DBN structure of 3 levels. Associated with each state is an ending indicator to signify the termination of the state. Denote by {a mathematical formula}xtd and {a mathematical formula}etd the state and ending indicator at level d and time t, respectively. When {a mathematical formula}etd=0, the state {a mathematical formula}xtd continues, i.e. {a mathematical formula}xtd=xt+1d. And when {a mathematical formula}etd=1, the state {a mathematical formula}xtd transits to a new state, or transits to itself. There are hierarchical consistency rules that must be strictly observed. Whenever a state persists (i.e. {a mathematical formula}etd=0), all of the states above it must also persist (i.e. {a mathematical formula}etd′=0 for all {a mathematical formula}d′&lt;d). Similarly, whenever a state ends (i.e {a mathematical formula}etd=1), all of the states below it must also end (i.e. {a mathematical formula}etd′=1 for all {a mathematical formula}d′&gt;d).
      </paragraph>
      <paragraph>
       Inference and learning in HHMMs follow the Inside–Outside algorithm of the probabilistic context-free grammars. Overall, the algorithm has {a mathematical formula}O(K3DT3) time complexity where K is the maximum size of the state space at each level, D is the depth of the model and T is the model length.
      </paragraph>
      <paragraph>
       When representing as a DBN, the whole stack of states {a mathematical formula}xt1:D can be collapsed into a ‘mega-state’ of a big HMM, and therefore inference can be carried out in {a mathematical formula}O(K2DT) time. This is efficient for a shallow model (i.e. D is small), but problematic for a deep model (i.e. D is large).
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Model definition
     </section-title>
     <paragraph>
      In this section we define the general HSCRF as a hierarchically nested Markov process. Specific log-linear parameterisation will be presented in Sec. 6.1. In an HSCRF, like its generative counterpart (HHMM, Sec. 2.2), each parent state embeds a child Markov chain whose states may in turn contain child Markov chains. The family relation is defined in a topology, which is a state hierarchy of depth {a mathematical formula}D&gt;1. The model has a set of states {a mathematical formula}Sd at each level {a mathematical formula}d∈[1,D], i.e. {a mathematical formula}Sd={1...Kd}. For each state {a mathematical formula}sd∈Sd where {a mathematical formula}1≤d&lt;D, the topological structure also defines a set of children {a mathematical formula}ch(sd)⊂Sd+1. Conversely, each child {a mathematical formula}sd+1 has a set of parents {a mathematical formula}pa(sd+1)⊂Sd. Unlike the original HHMMs where the child states belong exclusively to the parent, the HSCRFs allow arbitrary sharing of children between parents. For example, in Fig. 3, {a mathematical formula}ch(s1=1)={1,2,3}, and {a mathematical formula}pa(s3=1)={1,2,4}. This helps avoid an explosive number of sub-states when D is large, leading to fewer parameters and possibly less training data and time. The shared topology has been investigated in the context of HHMMs in [15].
     </paragraph>
     <paragraph>
      The temporal evolution in the nested Markov processes with sequence length of T operates as follows:
     </paragraph>
     <list>
      <list-item label="•">
       As soon as a state is created at level {a mathematical formula}d&lt;D, it initialises a child state at level {a mathematical formula}d+1. The initialisation continues downward until reaching the bottom level.
      </list-item>
      <list-item label="•">
       As soon as a child process at level {a mathematical formula}d+1ends, it returns control to its parent at level d, and in the case of {a mathematical formula}d&gt;1, the parent either transits to a new parent state or returns to the grand-parent at level {a mathematical formula}d−1.
      </list-item>
     </list>
     <paragraph>
      In hierarchical nesting, the life-span of a child process belongs exclusively to the life-span of its parent. For example, a parent process at level d starts a new state {a mathematical formula}si:jd at time i and persists until time j. At time i the parent initialises a child state {a mathematical formula}sid+1 which continues until it ends at time {a mathematical formula}k&lt;j, at which the child state transits to a new child state {a mathematical formula}sk+1d+1. The child process exits at time j, returning the control to the parent {a mathematical formula}si:jd. Upon receiving the control the parent state {a mathematical formula}si:jd may transit to a new parent state {a mathematical formula}sj+1:ld, or end at j, returning the control to the grand-parent at level {a mathematical formula}d−1.
     </paragraph>
     <paragraph>
      We now formally specify the nested Markov processes. Let us introduce a multi-level temporal graphical model of length T with D levels, starting from the top as 1 and the bottom as D (Fig. 4). At each level {a mathematical formula}d∈[1,D] and time index {a mathematical formula}i∈[1,T], there is a node representing a state variable {a mathematical formula}xid∈Sd={1,2,...,Kd}. Associated with each {a mathematical formula}xid is an ending indicator {a mathematical formula}eid signifying whether the state {a mathematical formula}xid ends or persists at i. The nesting nature of the HSCRFs is now realised by imposing the specific constraints on the value assignment of ending indicators as summarised in Table 2.
     </paragraph>
     <paragraph>
      Thus, specific value assignments of ending indicators provide contexts that realise the evolution of the model states in both hierarchical (vertical) and temporal (horizontal) directions. Each context at a level and associated state variables form a contextual clique, and we identify four contextual clique types:
     </paragraph>
     <list>
      <list-item label="•">
       State-persistence: This corresponds to the life time of a state at a given level (see Fig. 5). Specifically, given a context {a mathematical formula}c=[ei−1:jd=(1,0,..,0,1)], then {a mathematical formula}σi:jpersist,d=(xi:jd,c), is a contextual clique that specifies the life-span {a mathematical formula}[i,j] of any state {a mathematical formula}s=xi:jd.
      </list-item>
      <list-item label="•">
       State-transition: This corresponds to a state at level {a mathematical formula}d∈[2,D] at time i transiting to a new state (see Fig. 6a). Specifically, given a context {a mathematical formula}c=[eid−1=0,eid=1] then {a mathematical formula}σitransit,d=(xi+1d−1,xi:i+1d,c) is a contextual clique that specifies the transition of {a mathematical formula}xid to {a mathematical formula}xi+1d at time i under the same parent {a mathematical formula}xi+1d−1.
      </list-item>
      <list-item label="•">
       State-initialisation: This corresponds to a state at level {a mathematical formula}d∈[1,D−1] initialising a new child state at level {a mathematical formula}d+1 at time i (see Fig. 6b). Specifically, given a context {a mathematical formula}c=[ei−1d=1], then {a mathematical formula}σiinit,d=(xid,xid+1,c) is a contextual clique that specifies the initialisation at time i from the parent {a mathematical formula}xid to the child {a mathematical formula}xid+1.
      </list-item>
      <list-item label="•">
       State-ending: This corresponds to a state at level {a mathematical formula}d∈[1,D−1] ending at time i (see Fig. 6c). Specifically, given a context {a mathematical formula}c=[eid=1], then {a mathematical formula}σiend,d=(xid,xid+1,c) is a contextual clique that specifies the ending of {a mathematical formula}xid at time i with the last child {a mathematical formula}xid+1.
      </list-item>
     </list>
     <paragraph>
      In the HSCRF we are interested in the conditional setting in which the entire state variables and ending indicators {a mathematical formula}(x1:T1:D,e1:T1:D) are conditioned on an observational sequence z. For example, in NLP the observation is a sequence of words and the state variables might be the part-of-speech tags and the phrases.
     </paragraph>
     <paragraph>
      To capture the correlation between variables and such conditioning, we define a positive potential function {a mathematical formula}ψ(σ,z) over each contextual clique σ. Table 3 shows the notations for potentials that correspond to the four contextual clique types we have identified above. Details of potential specification are described in the Sec. 6.1.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}ζ=(x1:T1:D,e1:T1:D) denote the set of all variables that satisfies the set of hierarchical constraints listed in Table 2. Let {a mathematical formula}τd denote the ordered set of all ending time indices at level d, i.e. if {a mathematical formula}i∈τd then {a mathematical formula}eid=1. The joint potential defined for each configuration is the product of all contextual clique potentials over all ending time indices {a mathematical formula}i∈[1,T] and all semantic levels {a mathematical formula}d∈[1,D]:{a mathematical formula}
     </paragraph>
     <paragraph>
      The conditional distribution is given as{a mathematical formula} where {a mathematical formula}Z(z)=∑ζΦ[ζ,z] is the partition function for normalisation.
     </paragraph>
     <paragraph>
      In what follows we omit z for clarity, and implicitly use it as part of the partition function Z and the potential {a mathematical formula}Φ[.]. It should be noted that in the unconditional formulation, there is only a single Z for all data instances. In conditional setting there is a {a mathematical formula}Z(z) for each data instance z.
     </paragraph>
     <paragraph label="Remarks">
      The temporal model of HSCRFs presented here is not a standard graphical model [14] since the connectivity (and therefore the clique structures) is not fixed. The potentials are defined on-the-fly depending on the context of assignments of ending indicators. Although the model topology is identical to that of shared structure HHMMs [15], the unrolled temporal representation is an undirected graph and the model distribution is formulated in a discriminative way. Furthermore, the state persistence potentials capture duration information that is not available in the dynamic DBN representation of the HHMMs in [17]. The HSCRF potentials may first appear to resemble the clique templates in the discriminative relational Markov networks [19]. They are, however, different because cliques in the HSCRFs are dynamic and context-dependent.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Asymmetric inside–outside algorithm
     </section-title>
     <paragraph>
      This section describes a core inference engine called Asymmetric Inside–Outside (AIO) algorithm. The AIO algorithm computes building blocks that are needed in inference and learning tasks, including the partition function, time-specific marginals and feature expectations.
     </paragraph>
     <section label="4.1">
      <section-title>
       Building blocks and conditional independence
      </section-title>
      <section label="4.1.1">
       <section-title>
        Contextual Markov blankets
       </section-title>
       <paragraph>
        In this subsection we define elements that are building blocks for inference and learning. These building blocks are identified given the corresponding boundaries. Let us introduce two types of boundaries: the contextual symmetric and asymmetric Markov blankets.
       </paragraph>
       <paragraph label="Definition 1">
        A symmetric Markov blanket at level d for a state s starting at i and ending at j is the following set{a mathematical formula}
       </paragraph>
       <paragraph label="Definition 2">
        Let {a mathematical formula}Πi:jd,s be a symmetric Markov blanket, we define {a mathematical formula}ζi:jd,s and {a mathematical formula}ζ_i:jd,s as follows{a mathematical formula}{a mathematical formula} subject to {a mathematical formula}xi:jd=s. Further, we define{a mathematical formula}
       </paragraph>
       <paragraph>
        Fig. 7a shows an example of a symmetric Markov blanket (represented by a double-arrowed line).
       </paragraph>
       <paragraph label="Definition 3">
        A asymmetric Markov blanket at level d for a parent state s starting at i and a child state u ending at j is the following set{a mathematical formula}
       </paragraph>
       <paragraph label="Definition 4">
        Let {a mathematical formula}Γi:jd,s(u) be an asymmetric Markov blanket, we define {a mathematical formula}ζi:jd,s(u) and {a mathematical formula}ζ_i:jd,s(u) as follows{a mathematical formula}{a mathematical formula} subject to {a mathematical formula}xi:jd=s and {a mathematical formula}xjd+1=u. Further, we define{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Fig. 7b shows an example of asymmetric Markov blanket (represented by an arrowed line).
       </paragraph>
       <paragraph label="Remark">
        The concepts of contextual Markov blankets (or Markov blankets for short) are different from those in traditional Markov random fields and Bayesian networks because they are specific assignments of a subset of variables, rather than a collection of variables.
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        Conditional independence
       </section-title>
       <paragraph>
        Given these two definitions we have the following propositions of conditional independence.
       </paragraph>
       <paragraph label="Proposition 1">
        {a mathematical formula}ζi:jd,sand{a mathematical formula}ζ_i:jd,sare conditionally independent given{a mathematical formula}Πi:jd,s{a mathematical formula}
       </paragraph>
       <paragraph>
        This proposition gives rise to the following factorisation{a mathematical formula}
       </paragraph>
       <paragraph label="Proposition 2">
        {a mathematical formula}ζi:jd,s(u)and{a mathematical formula}ζ_i:jd,s(u)are conditionally independent given{a mathematical formula}Γi:jd,s(u){a mathematical formula}
       </paragraph>
       <paragraph>
        The following factorisation is a consequence of Proposition 2{a mathematical formula}
       </paragraph>
       <paragraph>
        The proofs of Proposition 1, Proposition 2 are given in Appendix A.1.
       </paragraph>
      </section>
      <section label="4.1.3">
       <section-title>
        Symmetric inside/outside masses
       </section-title>
       <paragraph>
        From Eq. (12) we have {a mathematical formula}ζ=(ζi:jd,s,Πi:jd,s,ζ_i:jd,s). Since {a mathematical formula}Πi:jd,s separates {a mathematical formula}ζi:jd,s from {a mathematical formula}ζ_i:jd,s, we can group local potentials in Eq. (8) into three parts: {a mathematical formula}Φ[ζˆi:jd,s], {a mathematical formula}Φ[ζ_ˆi:jd,s], and {a mathematical formula}Φ[Πi:jd,s]. By ‘grouping’ we mean to multiply all the local potentials belonging to a certain part, in the same way that we group all the local potentials belonging to the model in Eq. (8). Note that although {a mathematical formula}ζˆi:jd,s contains {a mathematical formula}Πi:jd,s we do not group {a mathematical formula}Φ[Πi:jd,s] into {a mathematical formula}Φ[ζˆi:jd,s]. The same holds for {a mathematical formula}Φ[ζ_ˆi:jd,s].
       </paragraph>
       <paragraph>
        By definition of the state-persistence clique potential (Fig. 3), we have {a mathematical formula}Φ[Πi:jd,s]=Ri:jd,s. Thus Eq. (8) can be replaced by{a mathematical formula} There are two special cases: (1) when {a mathematical formula}d=1, {a mathematical formula}Φ[ζ_ˆ1:T1,s]=1 for {a mathematical formula}s∈S1, and (2) when {a mathematical formula}d=D, {a mathematical formula}Φ[ζˆi:iD,s]=1 for {a mathematical formula}s∈SD and {a mathematical formula}i∈[1,T]. This factorisation plays an important role in efficient inference.
       </paragraph>
       <paragraph>
        We know define a quantity called symmetric inside mass{a mathematical formula}Δi:jd,s, and another called symmetric outside mass{a mathematical formula}Λi:jd,s.
       </paragraph>
       <paragraph label="Definition 5">
        Given a symmetric Markov blanket {a mathematical formula}Πi:jd,s, the symmetric inside mass {a mathematical formula}Δi:jd,s and the symmetric outside mass {a mathematical formula}Λi:jd,s are defined as{a mathematical formula}{a mathematical formula} As special cases we have {a mathematical formula}Λ1:T1,s=1 and {a mathematical formula}s∈S1, and {a mathematical formula}Δi:iD,s=1 for {a mathematical formula}i∈[1,T], {a mathematical formula}s∈SD. For later use let us introduce the ‘full’ symmetric inside mass {a mathematical formula}Δˆi:jd,s and the ‘full’ symmetric outside mass {a mathematical formula}Λˆi:jd,s as{a mathematical formula}
       </paragraph>
       <paragraph>
        In the rest of the paper, when it is clear in the context, we will use inside mass as a shorthand for symmetric inside mass, outside mass for symmetric outside mass, full-inside mass for full-symmetric inside mass, and full-outside mass for full-symmetric outside mass.
       </paragraph>
       <paragraph>
        Thus, from Eq. (22) the partition function can be computed from the full-inside mass at the top level ({a mathematical formula}d=1){a mathematical formula} With the similar derivation the partition function can also be computed from the full-outside mass at the bottom level ({a mathematical formula}d=D){a mathematical formula} In fact, we will prove a more general way to compute Z in Appendix B{a mathematical formula} for any {a mathematical formula}t∈[1,T] and {a mathematical formula}d∈[2,D−1]. These relations are summarised in Table 4.
       </paragraph>
       <paragraph>
        Given the fact that {a mathematical formula}ζi:jd,s is separated from the rest of variables by the symmetric Markov blanket {a mathematical formula}Πi:jd,s, we have Proposition 3.
       </paragraph>
       <paragraph label="Proposition 3">
        The following relations hold{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        The proof of this proposition is given in Appendix A.2.
       </paragraph>
      </section>
      <section label="4.1.4">
       <section-title>
        Asymmetric inside/outside masses
       </section-title>
       <paragraph>
        Recall that we have introduced the concept of asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u) which separates {a mathematical formula}ζi:jd,s(u) and {a mathematical formula}ζ_i:jd,s(u). Let us group all the local contextual clique potentials associated with {a mathematical formula}ζi:jd,s(u) and {a mathematical formula}Γi:jd,s(u) into a joint potential {a mathematical formula}Φ[ζˆi:jd,s(u)]. Similarly, we group all local potentials associated with {a mathematical formula}ζ_i:jd,s(u) and {a mathematical formula}Γi:jd,s(u) into a joint potential {a mathematical formula}Φ[ζ_ˆi:jd,s(u)]. Note that {a mathematical formula}Φ[ζ_ˆi:jd,s(u)] includes the state-persistence potential {a mathematical formula}Ri:jd,s.
       </paragraph>
       <paragraph label="Definition 6">
        Given the asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u), the asymmetric inside mass {a mathematical formula}αi:jd,s(u) and the asymmetric outside mass {a mathematical formula}λi:jd,s(u) are defined as follows{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        The relationship between the asymmetric outside mass and asymmetric inside mass is analogous to that between the outside and inside masses. However, there is a small difference, that is, the asymmetric outside mass ‘owns’ the segment {a mathematical formula}xi:jd=s and the associated state-persistence potential {a mathematical formula}Ri:jd,s, whilst the outside mass {a mathematical formula}Λi:jd(s) does not.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Computing inside masses
      </section-title>
      <paragraph>
       In this subsection we show how to recursively compute the pair: inside mass and asymmetric inside mass. The key idea here is to exploit the decomposition within the asymmetric Markov blanket. As shown in Fig. 8, an outer asymmetric Markov blanket can be decomposed into a sub-asymmetric Markov blanket and a symmetric blanket.
      </paragraph>
      <section label="4.2.1">
       <section-title>
        Computing asymmetric inside mass from inside mass
       </section-title>
       <paragraph>
        Assume that within the asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u), the child u starts somewhere at {a mathematical formula}t∈[i,j] and ends at j, i.e. {a mathematical formula}xt:jd+1=u, {a mathematical formula}et:j−1d+1=0 and {a mathematical formula}et−1d+1:D−1=1. Let us consider two cases: {a mathematical formula}t&gt;i and {a mathematical formula}t=i.
       </paragraph>
       <paragraph>
        Case 1. For {a mathematical formula}t&gt;i, denote by {a mathematical formula}v=xt−1d+1. We have two smaller blankets within {a mathematical formula}Γi:jd,s(u): the symmetric blanket {a mathematical formula}Πt:jd+1,u associated with the child {a mathematical formula}u=xt:jd+1, and the asymmetric blanket {a mathematical formula}Γi:t−1d,s(v) associated with the child v ending at {a mathematical formula}t−1 under the parent s. Fig. 8 illustrates the blanket decomposition. The assignment {a mathematical formula}ζi:jd,s(u) can be decomposed as{a mathematical formula}
       </paragraph>
       <paragraph>
        Thus, the joint potential {a mathematical formula}Φ[ζˆi:jd,s(u)] can be factorised as follows{a mathematical formula} The transition potential {a mathematical formula}Av,u,t−1d+1,s is enabled in the context {a mathematical formula}c=[et−1d=0,et−1d+1=1,xtd=s,xt−1d+1=v,xtd+1=u], and the state-persistence potential {a mathematical formula}Rt:jd+1,u in the context {a mathematical formula}c=[et:j−1d+1=0,et−1d+1:D=1,ejd+1:D=1,xt:jd+1=u].
       </paragraph>
       <paragraph>
        Case 2. For {a mathematical formula}t=i, the asymmetric blanket {a mathematical formula}Γi:t−1d,s(v) does not exist since {a mathematical formula}i&gt;t−1. We have the following decompositions of assignment {a mathematical formula}ζˆi:jd,s(u)=(ζˆi:jd+1,u,ei−1d=1,ei:j−1d=0). In the context {a mathematical formula}c=[ei−1d=1], the state-initialisation potential {a mathematical formula}πu,id,s is activated. Thus we have{a mathematical formula}
       </paragraph>
       <paragraph>
        Substituting Eqs. (34), (35) into Eq. (31), and together with the fact that t can take any value in the interval {a mathematical formula}[i,j], and v can take any value in {a mathematical formula}Sd+1, we have the following relation{a mathematical formula} As we can see, the asymmetric inside mass α plays the role of a forward message starting from the starting time i to the ending time j. There is a recursion where the asymmetric inside mass ending at time j is computed from all the asymmetric inside masses ending at time {a mathematical formula}t−1, for {a mathematical formula}t∈[i+1,j].
       </paragraph>
       <paragraph>
        There are special cases for the asymmetric inside mass: (1) when {a mathematical formula}i=j, we only have{a mathematical formula} and (2) when {a mathematical formula}d=D−1, the sum over the index t as in Eq. (36) is not allowed since at level D the inside mass only spans a single index. We have the following instead{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.2.2">
       <section-title>
        Computing inside mass from asymmetric inside mass
       </section-title>
       <paragraph>
        Notice the relationship between the asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u) and the symmetric blanket {a mathematical formula}Πi:jd,s, where {a mathematical formula}d&lt;D. When {a mathematical formula}ejd=1, i.e. the parent s ends at j, and {a mathematical formula}Γi:jd,s(u) will become {a mathematical formula}Πi:jd,s with {a mathematical formula}u=xjd+1. Then we have decompositions {a mathematical formula}ζi:jd,s=(ζi:jd,s(u),u=xjd+1) and {a mathematical formula}ζˆi:jd,s=(ζˆi:jd,s(u),ejd=1,u=xjd+1). These lead to the factorisation{a mathematical formula} where the state-ending potential {a mathematical formula}Eu,jd,s is activated in the context {a mathematical formula}c=[ejd=1]. Thus, the inside mass in Eq. (23) can be rewritten as{a mathematical formula} This equation holds for {a mathematical formula}d&lt;D. When {a mathematical formula}d=D, we set {a mathematical formula}Δi:iD,s=1 for all {a mathematical formula}s∈SD and {a mathematical formula}i∈[1,T], and when {a mathematical formula}d=1, we must ensure that {a mathematical formula}i=1 and {a mathematical formula}j=T.
       </paragraph>
       <paragraph label="Remark">
        Eqs. (36), (37), (38) and (40) specify a left-right and bottom-up algorithm to compute both the inside and asymmetric inside masses. Initially, at the bottom level {a mathematical formula}Δi:iD,s=1 for {a mathematical formula}i∈[1,T] and {a mathematical formula}s∈SD. Pseudo-code of the dynamic programming algorithm to compute all the inside and asymmetric inside masses and the partition function is given in Algorithm 1.
       </paragraph>
      </section>
     </section>
     <section label="4.3">
      <section-title>
       Computing outside masses
      </section-title>
      <paragraph>
       In this subsection we show how to recursively compute the symmetric outside mass and the asymmetric outside mass. We use the same blanket decomposition as in Section 4.2. However, this time the view is reversed as we are interested in quantities outside the blankets. For example, outside the inner symmetric Markov blanket in Fig. 8, there exists an outer asymmetric blanket and another sub-asymmetric blanket on the left.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Computing asymmetric outside mass from outside mass
       </section-title>
       <paragraph>
        Let us examine the variables {a mathematical formula}ζ_i:jd,s(u) associated with the asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u), for {a mathematical formula}d∈[1,D−1] and {a mathematical formula}1≤i≤j≤T (see Definition 4). For {a mathematical formula}j&lt;T, assume that there exists an outer asymmetric Markov blanket {a mathematical formula}Γi:td,s(v) for some {a mathematical formula}v∈Sd+1 and {a mathematical formula}t∈[j+1,T], and a symmetric Markov blanket {a mathematical formula}Πj+1:td+1,v right next to {a mathematical formula}Γi:jd,s(u). Given these blankets we have the decomposition {a mathematical formula}ζ_ˆi:jd,s(u)=(ζ_ˆi:td,s(v),ζˆj+1:td+1,v,xjd+1=u), which leads to the following factorisation{a mathematical formula} The state transition potential {a mathematical formula}Au,v,jd+1,s is enabled in the context {a mathematical formula}c=[ejd=0,ejd+1=1], and the state persistence potential {a mathematical formula}Rj+1:td+1,v in the context {a mathematical formula}c=[ejd+1=1,ej+1:t−1d+1=0,etd+1=1].
       </paragraph>
       <paragraph>
        In addition, there exists a special case where the state s ends at j. We have the decomposition {a mathematical formula}ζ_ˆi:jd,s(u)=(ζ_ˆi:jd,s,u=xjd+1) and the following factorisation{a mathematical formula} The ending potential {a mathematical formula}Eu,jd,s appears here because of the context {a mathematical formula}c=[ejd=1], i.e. s ends at j.
       </paragraph>
       <paragraph>
        Now we relax the assumption of {a mathematical formula}t,v and allow them to receive all possible values, i.e. {a mathematical formula}t∈[j,T] and {a mathematical formula}v∈Sd+1. Thus we can replace Eq. (32) by{a mathematical formula} for {a mathematical formula}d∈[2,D−2], and {a mathematical formula}1≤i≤j≤T. Thus, the {a mathematical formula}λi:jd,s(u) can be thought as a message passed backward from {a mathematical formula}j=T to {a mathematical formula}j=i. Here, the asymmetric outside mass ending at j is computed by using all the asymmetric outside masses ending at t for {a mathematical formula}t∈[j+1,T].
       </paragraph>
       <paragraph>
        There are two special cases. At the top level, i.e. {a mathematical formula}d=1, then {a mathematical formula}λi:jd,s(u) is only defined at {a mathematical formula}i=1, and the second term of the RHS of Eq. (43) is included only if {a mathematical formula}i=1,j=T. At the second lowest level, i.e. {a mathematical formula}d=D−1, we cannot sum over t as in Eq. (43) since {a mathematical formula}Δˆj+1:tD,v is only defined for {a mathematical formula}t=j+1. We have the following relation instead{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Computing outside mass from asymmetric outside mass
       </section-title>
       <paragraph>
        Given a symmetric Markov blanket {a mathematical formula}Πi:jd+1,u for {a mathematical formula}d∈[1,D−1], assume that there exists an asymmetric Markov blanket {a mathematical formula}Γt:jd,s(u) at the parent level d, where {a mathematical formula}t∈[1,i]. Clearly, for {a mathematical formula}t∈[1,i−1] there exists some sub-asymmetric Markov blanket {a mathematical formula}Γt:i−1d,s(v). See Fig. 8 for an illustration.
       </paragraph>
       <paragraph>
        Let us consider two cases: {a mathematical formula}t&lt;i and {a mathematical formula}t=i.
       </paragraph>
       <paragraph>
        Case 1. For {a mathematical formula}t&lt;i, this enables the decomposition {a mathematical formula}ζ_ˆi:jd+1,u=(ζ_ˆt:jd,s(u),ζˆt:i−1d,s(v),u=xi:jd+1), which leads to the following factorisation{a mathematical formula} The state transition potential {a mathematical formula}Av,u,i−1d,s is activated in the context {a mathematical formula}c=[ei−1d=0,ei−1d+1=1].
       </paragraph>
       <paragraph>
        Case 2. For {a mathematical formula}t=i, the decomposition reduces to {a mathematical formula}ζ_ˆi:jd+1,u=(ζ_ˆi:jd,s(u),u=xi:jd+1), which leads to the following factorisation{a mathematical formula} The state-initialisation potential {a mathematical formula}πu,id,s plays the role in the context {a mathematical formula}c=[ei−1d=1]
       </paragraph>
       <paragraph>
        However, these decompositions and factorisations only hold given the assumption of specific values of {a mathematical formula}s∈Sd, {a mathematical formula}v∈Sd+1, and {a mathematical formula}t∈[1,i]. Without further information we have to take all possibilities into account. Substituting these relations into Eq. (24), we have{a mathematical formula} for {a mathematical formula}d∈[2,D−2].
       </paragraph>
       <paragraph>
        There are three special cases. The first is the base case where {a mathematical formula}d=0 and {a mathematical formula}Λ1:T1,s=1 for all {a mathematical formula}s∈S1. In the second case, for {a mathematical formula}d=1, we must fix the index {a mathematical formula}t=1 since the asymmetric inside mass {a mathematical formula}αt:i−1d,s is only defined at {a mathematical formula}t=1. Also the second term in the RHS is included only if {a mathematical formula}i=1 for the asymmetric outside mass {a mathematical formula}λi:jd,s(u) to make sense. In the second case, for {a mathematical formula}d+1=D, we only have {a mathematical formula}i=j.
       </paragraph>
       <paragraph label="Remark">
        Eqs. (43), (44) and (47) show a recursive top-down and outside-in approach to compute the symmetric/asymmetric outside masses. We start from the top with {a mathematical formula}d=1 and {a mathematical formula}Λ1:T1,s=1 for all {a mathematical formula}s∈S1 and proceed downward until {a mathematical formula}d=D. The pseudo-code is given in Algorithm 2. Table 5 summarises the quantities computed in Section 4.2 and 4.3.
       </paragraph>
       <paragraph>
        Algorithm 3 summarises the AIO algorithm for computing all building blocks and the partition function.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      The generalised Viterbi algorithm
     </section-title>
     <paragraph>
      The MAP assignment is{a mathematical formula} The process of computing the MAP assignment is similar to that of computing the partition function. This similarity comes from the relation between the sum-product and max-product algorithm (a generalisation of the Viterbi algorithm) of [20], and from the fact that inside/asymmetric inside procedures described in Section 4.2 are essentially a sum-product. We just need to convert all the summations into corresponding maximisations. The algorithm is a two-step procedure:
     </paragraph>
     <list>
      <list-item label="•">
       In the first step the maximum joint potential is computed and local maximum states and ending indicators are saved along the way. These states and ending indicators are maintained in a bookkeeper.
      </list-item>
      <list-item label="•">
       In the second step we decode the best assignment by backtracking through saved local maximum states.
      </list-item>
     </list>
     <paragraph>
      We make use of the contextual decompositions and factorisations from Section 4.2.
     </paragraph>
     <paragraph>
      Notations
     </paragraph>
     <paragraph>
      This section, with some abuse of notations, uses some slight modifications to the notations used in the rest of the paper. See Table 6 for reference.
     </paragraph>
     <paragraph>
      We now describe the first step.
     </paragraph>
     <section label="5.1">
      <section-title>
       Computing the maximum joint potential, maximal states and time indices
      </section-title>
      <paragraph>
       For clarity, let us drop the notation z in {a mathematical formula}Φ[ζ,z]. As {a mathematical formula}Φ[ζ]=Φ[ζˆ1:T1,s]R1:T1,s for {a mathematical formula}s∈S1 we have{a mathematical formula} Now, for a sub-assignment {a mathematical formula}ζi:jd,s for {a mathematical formula}1∈[1,D−1], Eq. (39) leads to{a mathematical formula}
      </paragraph>
      <paragraph>
       With some slight abuse of notation we introduce {a mathematical formula}Δi:jmax⁡,d,s as the optimal potential function of the subset of variables {a mathematical formula}ζi:jd,s, and {a mathematical formula}αi:jmax⁡,d,s(u) as the optimal potential function of the subset of variables {a mathematical formula}ζi:jd,s(u).
      </paragraph>
      <paragraph label="Definition 7">
       We define {a mathematical formula}Δi:jmax⁡,d,s and {a mathematical formula}αi:jmax⁡,d,s(u) as follows{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Eqs. (48) and (49) can be rewritten more compactly as{a mathematical formula}{a mathematical formula} for {a mathematical formula}d∈[1,D−1]. When {a mathematical formula}d=D, we simply set {a mathematical formula}Δi:imax⁡,D,s=1 for all {a mathematical formula}s∈SD and {a mathematical formula}i∈[1,T].
      </paragraph>
      <paragraph>
       From the factorisation in Eqs. (34), (35), we have{a mathematical formula} and{a mathematical formula} for {a mathematical formula}d∈[1,D−2] and {a mathematical formula}i&lt;j. For {a mathematical formula}d=D−1, we cannot scan the index t in the interval {a mathematical formula}[i+1,j] because the maximum inside {a mathematical formula}Δt:jmax⁡,D,u is only defined at {a mathematical formula}t=j. We have the following instead{a mathematical formula}
      </paragraph>
      <paragraph>
       There is a base case for {a mathematical formula}i=j, where the context {a mathematical formula}c=[ei−1d=1] is active, then{a mathematical formula}
      </paragraph>
      <paragraph>
       Of course, what we are really interested in is not the maximum joint potentials but the optimal states and time indices (or ending indicators). We need some bookkeepers to hold these quantities along the way. With some abuse of notation let us introduce the symmetric inside bookkeeper {a mathematical formula}Δi:jarg⁡,d,s associated with Eq. (54), and the asymmetric inside bookkeeper {a mathematical formula}αi:jarg⁡,d,s(u) associated with Eqs. (56), (57) and (58).
      </paragraph>
      <paragraph label="Definition 8">
       We define the symmetric inside bookkeeper {a mathematical formula}Δi:jarg⁡,d,s as follows{a mathematical formula} Similarly, we define the asymmetric inside bookkeeper {a mathematical formula}αi:jarg⁡,d,s(u) associated with Eq. (56) for {a mathematical formula}d∈[1,D−2] as{a mathematical formula} if {a mathematical formula}maxv∈Sd+1,t∈[i+1,j]⁡αi:t−1max⁡,d,s(v)Δˆt:jmax⁡,d+1,uAv,u,t−1d,s&gt;Δˆi:jmax⁡,d+1,uπu,id+1,s and {a mathematical formula}i&lt;j; and{a mathematical formula} otherwise. For {a mathematical formula}d=D−1, the {a mathematical formula}αi:jarg⁡,d,s(u) is associated with Eq. (57){a mathematical formula}
      </paragraph>
      <paragraph>
       The Eqs. (53), (54), (56), (57) and (58) provide a recursive procedure to compute maximum joint potential in a bottom-up and left-right manner. Initially we just set {a mathematical formula}Δi:imax⁡,D,s=1 for all {a mathematical formula}s∈SD and {a mathematical formula}i∈[1,T]. The procedure is summarised in Algorithm 4.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Decoding the MAP assignment
      </section-title>
      <paragraph>
       The proceeding of the backtracking process is opposite to that of the max-product. Specifically, we start from the root and proceed in a top-down and right-left manner. The goal is to identify the right-most segment at each level. Formally, a segment is a triple {a mathematical formula}(s,i,j) where s is the segment label, and i and j are start and end time indices, respectively. From the maximum inside {a mathematical formula}Δi:jmax⁡,d,s at level d, we identify the best child u and its ending time j from Eq. (54). This gives rise to the maximum asymmetric inside {a mathematical formula}αi:jmax⁡,d,s(u). Then we seek for the best child v that transits to u under the same parent s using Eq. (56). Since the starting time t for u has been identified the ending time for v is {a mathematical formula}t−1. We now have a right-most segment {a mathematical formula}(u,t,j) at level {a mathematical formula}d+1. The procedure is repeated until we reach the starting time i of the parent s. The backtracking algorithm is summarised in Algorithm 5.
      </paragraph>
      <paragraph>
       Finally, the generalised Viterbi algorithm is given in Algorithm 6.
      </paragraph>
      <paragraph>
       Working in log-space to avoid numerical overflow
      </paragraph>
      <paragraph>
       With long sequence and complex topology we may run into the problem of numerical overflow, i.e. when the numerical value of the maximum joint potential is beyond the number representation of the machine. To avoid this, we can work in the log-space instead, using the monotonic property of the log function. The equations in the log-space are summarised in Table 7.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Parameter estimation
     </section-title>
     <paragraph>
      In this section, we tackle the problem of parameter estimation by maximising the (conditional) data likelihood. Typically we need some parametric form to be defined for a particular problem and we need some numerical method to do the optimisation task.
     </paragraph>
     <paragraph>
      Here we employ the log-linear parameterisation, which is commonly used in the CRF setting. Recall from Section 2.1 that estimating parameters of the log-linear models using gradient-based methods requires the computation of feature expectation, or expected sufficient statistics (ESS). For our HSCRFs we need to compute four types of ESS corresponding to the state-persistence, state-transition, state-initialisation and state-ending.
     </paragraph>
     <section label="6.1">
      <section-title>
       Log-linear parameterisation
      </section-title>
      <paragraph>
       In our HSCRF setting there is a feature vector {a mathematical formula}fσd(σ,z) associated with each type of contextual clique σ, in that {a mathematical formula}ϕ(σd,z)=exp⁡[wσd⊤fσd(σ,z)]. Thus, the features are active only in the context in which the corresponding contextual cliques appear.
      </paragraph>
      <paragraph>
       For the state-persistence contextual clique, the features incorporate state-duration, start time i and end time j of the state. Other feature types incorporate the time index in which the features are triggered. Specifically,{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Denote by {a mathematical formula}Fσd(ζ,z) the global feature, which is the sum of all active features {a mathematical formula}fσd(z) at level d in the duration {a mathematical formula}[1,T] for a given assignment of ζ and a clique type σ. Recall that {a mathematical formula}τd={ik}k=1m is the set of ending time indices (i.e. {a mathematical formula}eikd=1). The four feature types are given in Eqs. (67)–(70).{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Substituting the global features into potentials in Eqs. (8), (9) we obtain the following log-linear model:{a mathematical formula} where {a mathematical formula}C={persist,transit,init,exit}.
      </paragraph>
      <paragraph>
       Again, for clarity of presentation we will drop the notion of z but implicitly assume that it is still in the each quantity.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       ESS for state-persistence features
      </section-title>
      <paragraph>
       Recall from Section 6.1 that the feature function for the state-persistence {a mathematical formula}fσpersistd,s(i,j) is active only in the context where {a mathematical formula}Πi:jd,s∈ζ. Thus, Eq. (67) can be rewritten as{a mathematical formula} The indicator function in the RHS ensures that the feature {a mathematical formula}fσpersistd,s(i,j) is only active if there exists a symmetric Markov blanket {a mathematical formula}Πi:jd,s in the assignment of ζ. Consider the following expectation{a mathematical formula}{a mathematical formula} Using the factorisation in Eq. (22) we can rewrite{a mathematical formula} Note that the elements inside the sum of the RHS are only non-zeros for those assignment of ζ that respect the persistent state {a mathematical formula}si:jd and the factorisation in Eq. (22), i.e. {a mathematical formula}ζ=(ζi:jd,s,ζ_i:jd,s,Πi:jd,s). Thus, the equation can be simplified to{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Using Eq. (72) we obtain the ESS for the state-persistence features{a mathematical formula}
      </paragraph>
      <paragraph>
       There are two special cases: (1) when {a mathematical formula}d=1, we do not sum over {a mathematical formula}i,j but fix {a mathematical formula}i=1,j=T, and (2) when {a mathematical formula}d=D then we keep {a mathematical formula}j=i.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       ESS for transition features
      </section-title>
      <paragraph>
       Recall that in Section 6.1 we define {a mathematical formula}fσtransit,u,vd,s(t) as a function that is active in the context {a mathematical formula}ctransit=[etd−1=0,etd=1], in which the child state {a mathematical formula}ud finishes its job at time t and transits to the child state {a mathematical formula}vd under the same parent {a mathematical formula}sd−1 (that is {a mathematical formula}sd−1 is still running). Thus Eq. (68) can be rewritten as{a mathematical formula}
      </paragraph>
      <paragraph>
       We now consider the following expectation{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Assume that the parent s starts at i. Since {a mathematical formula}etd=1, the child v must starts at {a mathematical formula}t+1 and ends some time later at {a mathematical formula}j≥t+1. We have the following decomposition of the configuration ζ that respects this assumption{a mathematical formula} and the following factorisation of the joint potential{a mathematical formula} The state persistent potential {a mathematical formula}Rt+1:jd,v is enabled in the context {a mathematical formula}c=[etd=1,et+1:j−1d=0,ejd=1] and the state transition potential {a mathematical formula}Au,v,td,s in the context {a mathematical formula}ctransit.
      </paragraph>
      <paragraph>
       Substituting this factorisation into the RHS of Eq. (81) gives us{a mathematical formula} which can be simplified to{a mathematical formula}
      </paragraph>
      <paragraph>
       Using Eqs. (79) and (84) we obtain the ESS for the state-transition features{a mathematical formula} When {a mathematical formula}d=2 we must fix {a mathematical formula}i=1 since {a mathematical formula}αi:t1,s(u) and {a mathematical formula}λi:j1,s(v) are only defined at {a mathematical formula}i=1.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       ESS for initialisation features
      </section-title>
      <paragraph>
       Recall that in Section 6.1 we define {a mathematical formula}fσinit,ud,s(i) as a function at level d that is triggered at time i when a parent s at level d initialises a child u at level {a mathematical formula}d+1. In this event, the context {a mathematical formula}cinit=[ei−1d=1] must be activated for {a mathematical formula}i&gt;1. Thus, Eq. (69) can be rewritten as{a mathematical formula}
      </paragraph>
      <paragraph>
       Now we consider the following feature expectation{a mathematical formula} For each assignment of ζ that enables {a mathematical formula}fσinit,ud,s(i), we have the following decomposition{a mathematical formula} where the context {a mathematical formula}cinit activates the emission from s to u and the feature function {a mathematical formula}fσinit,ud,s(i). Thus the joint potential {a mathematical formula}Φ[ζ] can be factorised as{a mathematical formula} Using this factorisation and noting that the elements within the summation in the RHS of Eq. (87) are only non-zeros with such assignments, we can simplify the RHS of Eq. (87) to{a mathematical formula} The summation over {a mathematical formula}j∈[i,T] is due to the fact that we do not know this index.
      </paragraph>
      <paragraph>
       Using Eqs. (86), (90) we obtain the ESS for the initialisation features{a mathematical formula}
      </paragraph>
      <paragraph>
       There are two special cases: (1) when {a mathematical formula}d=1, there must be no scanning of i but fix {a mathematical formula}i=1 since there is only a single initialisation at the beginning of the sequence, (2) when {a mathematical formula}d=D−1, we fix {a mathematical formula}j=i for {a mathematical formula}Δˆi:jD,u is only defined at {a mathematical formula}i=j.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       ESS for ending features
      </section-title>
      <paragraph>
       Recall that in Section 6.1 we define {a mathematical formula}fσend,ud,s(j) as a function that is activated when a child u at level {a mathematical formula}d+1 returns the control to its parent s at level d and time j. This event also enables the context {a mathematical formula}cend=[ejd=1]. Thus Eq. (70) can be rewritten as{a mathematical formula}
      </paragraph>
      <paragraph>
       Now we consider the following feature expectation{a mathematical formula} Assume that the state s starts at i and ends at j. For each assignment of ζ that enables {a mathematical formula}fσend,ud,s(j) and respects this assumption, we have the following decomposition{a mathematical formula} This assignment has the context {a mathematical formula}cend that activates the ending of u. Thus the joint potential {a mathematical formula}Φ[ζ] can be factorised as{a mathematical formula}
      </paragraph>
      <paragraph>
       Substituting this factorisation into the summation of the RHS of Eq. (93) yields{a mathematical formula}
      </paragraph>
      <paragraph>
       Using Eqs. (92) and (96) we obtain the ESS for the exiting features{a mathematical formula}
      </paragraph>
      <paragraph>
       There is a special case: when {a mathematical formula}d=1 there must be no scanning of {a mathematical formula}i,j but fix {a mathematical formula}i=1, {a mathematical formula}j=T.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Partial labels in learning and inference
     </section-title>
     <paragraph>
      So far we have assumed that training data is fully labelled, and that testing data does not have any labels. In this section we extend the AIO to handle the cases in which these assumptions do not hold. Specifically, it may happen that the training data is not completely labelled, possibly due to lack of labelling resources. In this case, the learning algorithm should be robust enough to handle missing labels. On the other hand, during inference, we may partially obtain high quality labels from external sources. This requires the inference algorithm to be responsive to that data.
     </paragraph>
     <section label="7.1">
      <section-title>
       The constrained AIO algorithm
      </section-title>
      <paragraph>
       In this section we consider the general case when {a mathematical formula}ζ=(ϑ,h), where ϑ is the visible set labels, and h the hidden set. Since our HSCRF is also an exponential model it shares the same computation required for general CRFs (Eqs. (6) and (7)). We have to compute four quantities: the partial log-partition function {a mathematical formula}Z(ϑ,z), the partition function {a mathematical formula}Z(z), the ‘constrained’ ESS {a mathematical formula}Eh|ϑ,z[F(ϑ,h,z)], and the ‘free’ ESS {a mathematical formula}Eζ|z[F(ζ,z)]. The partition function and the ‘free’ ESS has been computed in Sections 4 and 6, respectively. This section describes the other two quantities.
      </paragraph>
      <paragraph>
       Let the set of visible labels be {a mathematical formula}ϑ=(x˜,e˜) where {a mathematical formula}x˜ is the visible set of state variables and {a mathematical formula}e˜ is the visible set of ending indicators. The basic idea is that we have to modify procedures for computing the building blocks such as {a mathematical formula}Δi:jd,s and {a mathematical formula}αi:jd,s(u), to address constraints imposed by the labels. For example, {a mathematical formula}Δi:jd,s implies that the state s at level d starts at i and persists till terminating at j. Then, if any labels (e.g. there is an {a mathematical formula}x˜kd≠s for {a mathematical formula}k∈[i,j]) are seen, causing this assumption to be inconsistent, {a mathematical formula}Δi:jd,s will be zero. Therefore, in general, the computation of each building block is multiplied by an identity function that enforces the consistency between these labels and the required constraints for computation of that block. As an example, we consider the computation of {a mathematical formula}Δi:jd,s and {a mathematical formula}αi:jd,s(u).
      </paragraph>
      <paragraph>
       The symmetric inside mass {a mathematical formula}Δi:jd,s is consistent only if all of the following conditions are satisfied:
      </paragraph>
      <list>
       <list-item label="1.">
        If there are state labels {a mathematical formula}x˜kd at level d within the interval {a mathematical formula}[i,j], then {a mathematical formula}x˜kd=s,
       </list-item>
       <list-item label="2.">
        If there is any label of ending indicator {a mathematical formula}e˜i−1d, then {a mathematical formula}e˜i−1d=1,
       </list-item>
       <list-item label="3.">
        If there is any label of ending indicator {a mathematical formula}e˜kd for some {a mathematical formula}k∈[i,j−1], then {a mathematical formula}e˜kd=0, and
       </list-item>
       <list-item label="4.">
        If any ending indicator {a mathematical formula}e˜jd is labelled, then {a mathematical formula}e˜jd=1.
       </list-item>
      </list>
      <paragraph>
       These conditions are captured by using the following identity function:{a mathematical formula} When labels are observed, Eq. (40) is thus replaced by{a mathematical formula} Note that we do not need to explicitly enforce the state consistency in the summation over u since in the bottom-up and left-right computation, {a mathematical formula}αi:jd,s(u) is already computed and contributes to the sum only if it is consistent.
      </paragraph>
      <paragraph>
       Analogously, the asymmetric inside mass {a mathematical formula}αi:jd,s(u) is consistent if all of the following conditions are satisfied:
      </paragraph>
      <list>
       <list-item label="1.">
        The first three conditions for the symmetric inside mass {a mathematical formula}Δi:jd,s hold,
       </list-item>
       <list-item label="2.">
        If the state at level d at time j is labelled, it must be u, and
       </list-item>
       <list-item label="3.">
        If any ending indicator {a mathematical formula}e˜jd+1 is labelled, then {a mathematical formula}e˜jd+1=1.
       </list-item>
      </list>
      <paragraph>
       These conditions are captured by the identity function{a mathematical formula} Thus Eq. (36) becomes{a mathematical formula} Note that we do not need to explicitly enforce the state consistency in the summation over v and time consistency in the summation over k since in bottom-up computation, {a mathematical formula}αi:jd,s(u) and {a mathematical formula}Δk:jd+1,u are already computed and contribute to the sum only if they are consistent. Finally, the constrained partition function {a mathematical formula}Z(ϑ,z) is computed using Eq. (25) given that the inside mass is consistent with the observations.
      </paragraph>
      <paragraph>
       Other building blocks, such as the symmetric outside mass {a mathematical formula}Λi:jd,s and the asymmetric outside mass {a mathematical formula}λi:jd,s(u), are computed in an analogous way. Since {a mathematical formula}Λi:jd,s and {a mathematical formula}Δi:jd,s are complementary and they share {a mathematical formula}(d,s,i,j), the same indicator function {a mathematical formula}I[Δi:jd,s] can be applied. Similarly, the pair asymmetric inside mass {a mathematical formula}αi:jd,s(u) and asymmetric outside mass {a mathematical formula}λi:jd,s(u) are complementary and they share {a mathematical formula}d,s,i,j,u, thus the same indicator function {a mathematical formula}I[αi:jd,s(u)] can be applied.
      </paragraph>
      <paragraph>
       Once all constrained building blocks have been computed they can be used to calculate constrained ESS as in Section 6 without any further modifications. The only difference is that we need to replace the partition function {a mathematical formula}Z(z) by the constrained version {a mathematical formula}Z(ϑ,z).
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       The constrained Viterbi algorithm
      </section-title>
      <paragraph>
       Recall that in the Generalised Viterbi Algorithm described in Section 5 we want to find the most probable configuration {a mathematical formula}ζMAP=arg⁡maxζ⁡Pr⁡(ζ|z). When some variables ϑ of ζ are labelled, it is not necessary to estimate them. The task is now to estimate the most probable configuration of the hidden variables h given the labels:{a mathematical formula} It turns out that the constrained MAP estimation is identical to the standard MAP except that we have to respect the labelled variables ϑ.
      </paragraph>
      <paragraph>
       Since the Viterbi algorithm is just the max-product version of the AIO, the constrained Viterbi can be modified in the same manner as in the constrained AIO (Section 7.1). Specifically, for each auxiliary quantities such as {a mathematical formula}Δi:jmax,s and {a mathematical formula}αi:jmax,s(u), we need to maintain a set of indicator functions that ensures the consistency with labels. Eqs. (98), (99) become{a mathematical formula} Likewise, we have the modifications to Eq. (100) and Eq. (101), respectively.{a mathematical formula}
      </paragraph>
      <paragraph>
       Other tasks in the Viterbi algorithm including bookkeeping and backtracking are identical to those described in Section 5.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Complexity analysis
      </section-title>
      <paragraph>
       The complexity of the constrained AIO and constrained Viterbi has an upper bound of {a mathematical formula}O(T3), when no labels are given. It also has a lower bound of {a mathematical formula}O(T) when all ending indicators are known and the model reduces to the standard tree-structured graphical model. In general, the complexity decreases as more labels are available, and we can expect a sub-cubic time behaviour.
      </paragraph>
      <paragraph>
       Learning requires both the constrained ESSes and free ESSes to be computed. Regardless of labels, the free ESSes still require cubic time. Thus with less labels, the overall computation will increase slightly.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Numerical scaling
     </section-title>
     <paragraph>
      In previous sections, we have derived AIO-based inference and learning algorithms for both unconstrained and constrained models. The quantities computed by these algorithms like the inside/outside masses often involve summation over exponentially many positive potentials. The potentials, when estimated from data, are not upper-bounded, causing the magnitude of the masses to increase exponentially fast in the sequence length T. The magnitude goes beyond the numerical capacity of most machines for moderate T. In this section we present a scaling method to reduce this numerical overflow problem.
     </paragraph>
     <section label="8.1">
      <section-title>
       Scaling symmetric/asymmetric inside masses
      </section-title>
      <paragraph>
       Let us revisit Eq. (40). If we scale down the asymmetric inside mass {a mathematical formula}αi:jd,s(u) by a factor {a mathematical formula}κj&gt;1, i.e.{a mathematical formula} then the symmetric inside mass {a mathematical formula}Δi:jd,s is also scaled down by the same factor. Similarly, as we can see from Eq. (36) that{a mathematical formula} where {a mathematical formula}Δˆt:jd+1,u=Δt:jd+1,uRt:jd+1,u, if {a mathematical formula}Δt:jd+1,u for {a mathematical formula}t∈[1,j] is reduced by {a mathematical formula}κj, then {a mathematical formula}αi:jd,s is also reduced by the same factor. In addition, using the set of recursive relations in Eqs. (36), (40), any reduction at the bottom level of {a mathematical formula}Δj:jD,s will result in the reduction of the symmetric inside mass {a mathematical formula}Δi:jd,s and of the asymmetric inside mass {a mathematical formula}αi:jd,s(u), for {a mathematical formula}d&lt;D, by the same factor.
      </paragraph>
      <paragraph>
       Suppose {a mathematical formula}Δi:iD,s is reduced by a factor of {a mathematical formula}κi&gt;1 for all {a mathematical formula}i∈[1,j], the quantities {a mathematical formula}Δ1:jd,s and {a mathematical formula}α1:jd,s(u) will be reduced by a factor of {a mathematical formula}∏i=1jκi. That is{a mathematical formula}{a mathematical formula} It follows immediately from Eq. (25) that the partition function is scaled down by a factor of {a mathematical formula}∏i=1Tκi{a mathematical formula} where {a mathematical formula}Δˆ1:T′1,s=Δ1:T′1,sB1:T1,s. Clearly, we should deal with the log of this quantity to avoid numerical overflow. Thus, the log-partition function can be computed as{a mathematical formula} where {a mathematical formula}Δ1:T′1,s has been scaled appropriately.
      </paragraph>
      <paragraph>
       One question is how to choose the set of meaningful scaling factors {a mathematical formula}{κj}1T. The simplest way is to choose a relatively large number for all scaling factors but making the right choice is not straightforward. Here we describe a more natural way to do so. Assume that we have chosen all the scaling factors {a mathematical formula}{κi}1j−1. Using the original Eqs. (36), (37), and (38), where all the sub-components have been scaled appropriately, we compute the partially-scaled inside mass {a mathematical formula}Δi:j″d,s for {a mathematical formula}d∈[2,D] and asymmetric inside mass {a mathematical formula}αi:j″d,s(u), for {a mathematical formula}d∈[1,D−1] and {a mathematical formula}i∈[1,j]. Then the scaling factor at time j is computed as{a mathematical formula}
      </paragraph>
      <paragraph>
       The next step is to rescale all the partially-scaled variables:{a mathematical formula}{a mathematical formula}{a mathematical formula} where {a mathematical formula}i∈[1,j].
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Scaling symmetric/asymmetric outside masses
      </section-title>
      <paragraph>
       In a similar fashion we can work out the set of factors from the derivation of symmetric/asymmetric outside masses since these masses solely depend on the inside masses as building blocks. In other words, after scaling the inside masses we can compute the scaled outside masses directly, using the same set of equations described in Section 4.3.
      </paragraph>
      <paragraph>
       The algorithm is summarised in Algorithm 7. Note that the order of performing the loops in this case is different from that in Algorithm 1.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Applications
     </section-title>
     <paragraph>
      In this section we present experimental results to demonstrate the capacity of the proposed HSCRFs in two applications: activity recognition and shallow parsing.
     </paragraph>
     <section label="9.1">
      <section-title>
       Recognising indoor activities
      </section-title>
      <paragraph>
       In this experiment, we evaluate the HSCRFs with a relatively small dataset from the domain of indoor video surveillance. The task is to recognise indoor trajectories and activities of a person from his noisy positions extracted from video. The data was captured in [21], and was subsequently used to evaluate DCRFs in [22]. The raw data consists of 90 sequences of noisy coordinates. Each time step is manually annotated by two labels: the complex and primitive activities. There are three complex activities (preparing-short-meal, having-snack and preparing-normal-meal); and 12 primitive activities listed in Table 8. As in [22], the data is split into two sets of equal size for training and testing, respectively.
      </paragraph>
      <paragraph>
       We assume that state-specific features such as initialisation, transition and exiting are indicator functions. For the data-associations (i.e. embedded in state-persistence potentials) at the bottom level, we use the same feature set as in [22], which are: the {a mathematical formula}(X,Y) coordinates, the X &amp; Y velocities, and the speed. At the second level during duration of a state, we use average velocities and a vector of positions visited within that duration. To encode the duration into the state-persistence potentials, we employ the sufficient statistics of the gamma distribution as features {a mathematical formula}fk(s,Δt)=I(s)log⁡(Δt) and {a mathematical formula}fk+1(s,Δt)=I(s)(Δt).
      </paragraph>
      <paragraph>
       For learning, labels for each sequence are provided fully for the case of fully observed state data, and partially for the case of missing state data. For testing, at each level d and time t we count an error if the predicted state is not the same as the ground-truth.
      </paragraph>
      <section label="9.1.1">
       <section-title>
        Fully supervised learning
       </section-title>
       <paragraph>
        Firstly, we examine the fully observed case where the HSCRF is compared against the DCRF at both data levels, and against the flat-CRF at bottom level. Table 9 (the left half) shows that (a) both the multilevel models significantly outperform the flat model and (b) the HSCRF outperforms the DCRF.
       </paragraph>
       <paragraph>
        We also test the ability of the model to learn the hierarchical topology and state transitions. Using log-linear parameterisation described in Section 6.1, the parent–child relationship in the topology and the state-transitions are captured in the corresponding parameters. Only positive parameters are used. This is because state features are non-negative, so negative parameters mean the probabilities of these transitions are very small (due to the exponential), compared to the positive ones. For the transition at the second level (the complex activity level), we obtain all negative entries. This clearly matches the training data, in which each sequence already belongs to one of three complex activities. With this method, we are able to construct the correct hierarchical topology as in Fig. 9. The state transition model is presented in Fig. 10. There is only one wrong transition, from state 12 to state 10, which is not presented in the training data. The rest is correct.
       </paragraph>
      </section>
      <section label="9.1.2">
       <section-title>
        Partially supervised learning
       </section-title>
       <paragraph>
        Next we consider partially-supervised learning in that about 50% of start/end times of a segment and segment labels are observed at the second level. All ending indicators are known at the bottom level. The results are reported in Table 9 (the right half). As can be seen, although only 50% of the state labels and state start/end times are observed, the model learned is still performing well with accuracy of 80.2% and 90.4% at levels 2 and 3, respectively.
       </paragraph>
      </section>
      <section label="9.1.3">
       <section-title>
        Prediction with partial labelling
       </section-title>
       <paragraph>
        We now consider the issue of using partial observed labels during decoding to improve prediction accuracy of poorly estimated models. We extract the parameters from the 10th iteration of the fully observed data case. The labels are provided at random time indexes. Fig. 11a shows the decoding accuracy as a function of available state labels. It is interesting to observe that a moderate amount of observed labels (e.g. 20–40%) causes the accuracy rate to go up considerably.
       </paragraph>
      </section>
     </section>
     <section label="9.2">
      <section-title>
       POS tagging and noun-phrase chunking
      </section-title>
      <paragraph>
       In this experiment we apply the HSCRF to the task of noun-phrase chunking. The data is from the CoNLL-2000 shared task [5], in which 8,926 English sentences from the Wall Street Journal corpus are used for training and 2,012 sentences are for testing. Each word in a pre-processed sentence is labelled by two labels: the part-of-speech (POS) and the noun-phrase (NP). There are 48 POS different labels and 3 NP labels (B-NP for beginning of a noun-phrase, I-NP for inside a noun-phrase or O for others). Each noun-phrase generally has more than one word. To reduce the computational burden, we reduce the POS tag-set to 5 groups: noun, verb, adjective, adverb and others. Since in our HSCRFs we do not have to explicitly indicate which node is at the beginning of a segment, the NP label set can be reduced further into NP for noun-phrase, and O for anything else.
      </paragraph>
      <paragraph>
       The POS tags are actually the output of the Brill's tagger [23], while the NPs are manually labelled. We extract raw features from the text in the way similar to that in [8]. However, we consider only a limited vocabulary extracted from the training data in that we only select words with more than 3 occurrences. This reduces the vocabulary and the feature size significantly. We also make use of bi-grams with similar selection criteria. Furthermore, we use the contextual window of 5 instead of 7 as in [8]. This setting gives rise to about 32K raw features. The model feature is factorised as {a mathematical formula}f(xc,z)=I(xc)gc(z), where {a mathematical formula}I(xc) is a binary function on the assignment of the clique variables {a mathematical formula}xc, and {a mathematical formula}gc(z) are the raw features.
      </paragraph>
      <paragraph>
       We build an HSCRF topology of 3 levels where the root is just a dummy node, the second level has 2 NP states and the bottom level has 5 POS states. For comparison, we implement a DCRF, a simple sequential CRF (SCRF), and a semi-Markov CRF (SemiCRF) [13]. The DCRF has grid structure of depth 2, one for modelling the NP process and another for the POS process. Since the state spaces are relatively small, we are able to run exact inference in the DCRF by collapsing both the NP and POS state spaces to a combined state space of size {a mathematical formula}3×5=15. The SCRF and SemiCRF model only the NP process, taking the POS tags as input. The raw feature set used in the DCRF is identical to those in our HSCRF. However, the set shared by the SCRF and the SemiCRF is a little more elaborate since it takes the POS tags into account [8].
      </paragraph>
      <paragraph>
       Although both the HSCRF and the SemiCRF are capable of modelling arbitrary segment duration, we use a simple exponential distribution as it can be processed sequentially and thus is very efficient. For learning, we use a simple online stochastic gradient ascent method since it has been shown to work relatively well and fast in CRFs [24]. At test time, as the SCRF and the SemiCRF are able to use the Brill's POS tags as input, it is not fair for the DCRF and HSCRF to predict those labels during inference. Instead, we also give the POS tags to the DCRF and HSCRF and perform constrained inference to predict only the NP labels. This boosts the performance of the two multi-level models significantly.
      </paragraph>
      <paragraph>
       The performance of these models is depicted in Fig. 12 and we are interested in only the prediction of the noun-phrases since this data has Brill's POS tags. Without Brill's POS tags given at test time, both the HSCRF and the DCRF perform worse than the SCRF trained on POS tags. This is not surprising because the Brill's POS tags are always given in the case of SCRF. However, with POS tags given at test time, the HSCRF consistently works better than all other models. In particular, our HSCRF + POS is significantly better than the SCRF (with POS included as features) when training data is small. There is a subtle but important difference here: The HSCRF was trained without knowledge of POS availability at test time. In contrast, SCRF was trained with this knowledge so that good POS-based features were used.
      </paragraph>
      <paragraph>
       The DCRF does worse than the SCRF, even with POS tags given. This does not share the observation made in [8]. However, we use a much smaller POS tag set than [8] does. Our explanation is that the SCRF is able to make use of wider context of the given POS tags (here, within the window of 5 tags) than the DCRF (limited to 1 POS tag per NP chunk). The SemiCRF, although in theory it is more expressive than the SCRF, does not show any advantage under current setting. Recall that the SemiCRF is a special case of HSCRF in that the POS level is not modelled, it is possible to conclude that joint modelling of NP and POS levels is important.
      </paragraph>
      <paragraph>
       More formally, let us look at the difference between the flat setting of SCRF and Semi-CRF and the multi-level setting of DCRF and HSCRF. Let {a mathematical formula}x=(xnp,xpos). Essentially, we are about to model the distribution {a mathematical formula}Pr⁡(x|z)=Pr⁡(xnp|xpos,z)Pr⁡(xpos|z) in the multi-level models while we ignore the {a mathematical formula}Pr⁡(xpos|z) in the flat models. During test time of the multi-level models, we predict only the {a mathematical formula}xnp by finding the maximiser of {a mathematical formula}Pr⁡(xnp|xpos,z). The POS model {a mathematical formula}Pr⁡(xpos|z) seems to be a waste because we do not make use of it at test time. However, {a mathematical formula}Pr⁡(xpos|z) does give extra information about the joint distribution {a mathematical formula}Pr⁡(x|z), that is, modelling the POS process may help to get smoother estimate of the NP distribution.
      </paragraph>
     </section>
    </section>
    <section label="10">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Hierarchical modelling of stochastic processes can be largely categorised as either graphical models extending the flat hidden (semi-)Markov models (HMM/HsMM) (e.g., the layered HMM [6], the abstract HMM [25], hierarchical HMM (HHMM) [2], [15], DBN [26]), grammar-based models (e.g., PCFG [27]), or deterministic models [28], [29]. These models are all directed while HSCRF is undirected.
     </paragraph>
     <paragraph>
      Higher-order extensions to the linear-chain CRFs have been developed recently [30], [31]. These methods exploit sparsity in the state transition for efficient inference, but they are shallow models. Development in deeper structures include dynamic CRFs (DCRF) [8], hierarchical CRFs [9], [10], and stacked CRFs [11]. The main difference between HSCRF and these CRF variants is that the hierarchical topology of HSCRF is dynamically inferred from data, unlike the others, where the topology is pre-defined by users. In term of inference complexity, DCRFs are not tractable in large-state settings. The hierarchical CRFs, on the other hand, are tractable but assume fixed tree structures, and therefore are not flexible to adapt to complex data. For example, the noun-phrase chunking problem does not assume prior tree structures. Rather, if such a structure exists, it can only be discovered after the model has been successfully built and learned.
     </paragraph>
     <paragraph>
      Our HSCRFs deal with the inference problem of DCRFs by limiting to recursive processes, and thus obtaining efficient inference via dynamic programming in the Inside–Outside family of algorithms. Furthermore, it generalises the SemiCRFs to model multilevel of semantics. It also addresses partial labels by introducing appropriate constraints to the Inside–Outside algorithms.
     </paragraph>
     <paragraph>
      As the HHMMs are special case of PCFG with bounded depth, HSCRFs are also special case of the conditional probabilistic context-free grammar (C-PCFG) (e.g. see [32], [33]). Like HSCRFs, C-PCFG requires cubic time in sequence length to parse a sentence. However, the context-free grammar does not limit the depth of semantic hierarchy, thus making it unnecessarily difficult to map many hierarchical problems into its form. Secondly, it lacks a graphical model representation and thus does not enjoy the rich set of approximate inference techniques available in graphical models.
     </paragraph>
     <paragraph>
      The AIO algorithm presented in Section 4 is inspired from the AIO algorithm in HHMMs [15], [2]. However, due to the log-linear parameterisation, there are no probabilistic interpretations of the inside and outside masses.
     </paragraph>
     <paragraph>
      The idea of numerical scaling presented in Section 8 can be traced back to the Pearl's message-passing procedure [20], [34]. In our AIO algorithms, the inside masses play the role of the inside-out messages. In Pearl's method, we reduce the messages' magnitude by normalising them at each step. The overflow problem is opposite to the underflow in directed counterparts. A similar idea has been proposed in [15] for HHMMs.
     </paragraph>
     <paragraph>
      The graphical model-like dynamic representation of the HSCRF appears similar to the DBN representation of the HHMMs in [17], and somewhat resembles a dynamic factor graph [35], [36]. However, it is not exactly the standard graphical model because the contextual cliques in HSCRFs are not fixed during inference. This makes it difficult to apply approximate inference methods such as Loopy Belief Propagation (LBP) and Gibbs sampling, which are designed for fixed cliques. The Gibbs sampling can be applied to a special arrangement as in [37], but convergence is not guaranteed within limited time and our preliminary experiments have indicated no advantage compared to exact inference.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <paragraph>
      In this appendix we give detailed proofs of propositions stated in the main text.
     </paragraph>
     <section label="A.1">
      Proof of Propositions 1 and 2
      <paragraph label="Lemma 1">
       Before proving Proposition 1, Proposition 2 let us introduce a lemma. Given a distribution of the form{a mathematical formula}Pr⁡(x)∝Φ[x]and{a mathematical formula}x=(xa,xs,xb), if there exists a factorisation{a mathematical formula}then{a mathematical formula}xaand{a mathematical formula}xbare conditionally independent given{a mathematical formula}xs.
      </paragraph>
      <paragraph label="Proof">
       We want to prove that{a mathematical formula} Since {a mathematical formula}Pr⁡(xa,xb|xs)=Pr⁡(xa,xb,xs)/∑xa,xbPr⁡(xa,xb,xs), the LHS of Eq. (A.2) becomes{a mathematical formula} where we have used the following fact{a mathematical formula}To prove {a mathematical formula}Pr⁡(xa|xs)=Φ[xa,xs]/∑xaΦ[xa,xs], we need only to show {a mathematical formula}Pr⁡(xa|xs)∝Φ[xa,xs] since the normalisation over {a mathematical formula}xa is due to {a mathematical formula}∑xaPr⁡(xa|xs)=1. Using the Bayes rule, we have{a mathematical formula} where we have ignored all the factors that do not depend on {a mathematical formula}xa.A similar proof gives {a mathematical formula}Pr⁡(xb|xs)=Φ[xs,xb]/∑xbΦ[xs,xb]. Combining this result and Eq. (A.5) with Eq. (A.3) gives us Eq. (A.2). This completes the proof.  □
      </paragraph>
      <paragraph>
       In fact, {a mathematical formula}xs acts as a separator between {a mathematical formula}xa and {a mathematical formula}xb. In standard Markov networks there are no paths from {a mathematical formula}xa to {a mathematical formula}xb that do not go through {a mathematical formula}xs. Now we proceed to proving Proposition 1, Proposition 2.
      </paragraph>
      <paragraph>
       Given the symmetric Markov blanket {a mathematical formula}Πi:jd,s, there are no potentials that are associated with variables belonging to both {a mathematical formula}ζi:jd,s and {a mathematical formula}ζ_i:jd,s. The blanket completely separates the {a mathematical formula}ζi:jd,s and {a mathematical formula}ζ_i:jd,s. Therefore, Lemma 1 ensures the conditional independence between {a mathematical formula}ζi:jd,s and {a mathematical formula}ζ_i:jd,s.
      </paragraph>
      <paragraph>
       Similarly, the asymmetric Markov blanket {a mathematical formula}Γi:jd,s(u) separates {a mathematical formula}ζi:jd,s(u) and {a mathematical formula}ζ_i:jd,s(u) and thus these two variable sets are conditionally independent due to Lemma 1.  □
      </paragraph>
     </section>
     <section label="A.2">
      Proof of Proposition 3
      <paragraph>
       Here we want to derive Eqs. (28), (29) and (30). With the same conditions as in Lemma 1, in Eq. (A.5) we have shown that {a mathematical formula}Pr⁡(xa|xs)∝Φ[xa,xs]. Similarly, this extends to{a mathematical formula} which is equivalent to{a mathematical formula} The last equation follows from the definition of the symmetric inside mass in Eq. (23). Similar procedure will yield Eq. (29).
      </paragraph>
      <paragraph>
       To prove Eq. (30), notice the Eq. (19) that says{a mathematical formula} or equivalently{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} In the proof proceeding, we have made use of the relation in Eq. (22). This completes the proof.  □
      </paragraph>
     </section>
    </section>
    <section label="Appendix B">
     <section-title>
      Computing state marginals
     </section-title>
     <paragraph>
      We are interested in computing the marginals of state variables {a mathematical formula}Pr⁡(xtd). We have{a mathematical formula} Let {a mathematical formula}s=xtd and assume that the state s starts at i and end at j, and {a mathematical formula}t∈[i,j]. For each configuration ζ that respects this assumption, we have the factorisation of Eq. (22) that says{a mathematical formula} Then Eq. (B.1) becomes{a mathematical formula} The summing over i and j is due to the fact that we do not know these indices.
     </paragraph>
     <paragraph>
      There are two special cases, (1) when {a mathematical formula}d=1 we cannot scan the left and right indices, the marginals are simply{a mathematical formula} since {a mathematical formula}Λ1:T1,s=1 for all {a mathematical formula}s∈S1; and (2) when {a mathematical formula}d=D, the start and end times must be the same ({a mathematical formula}i=j), thus{a mathematical formula} since {a mathematical formula}Δt:tD,s=1 for all {a mathematical formula}t∈[1,T] and {a mathematical formula}s∈SD.
     </paragraph>
     <paragraph>
      Since {a mathematical formula}∑s∈SdPr⁡(xtd=s)=1, it follows from Eq. (B.3) that{a mathematical formula} This turns out to be the most general way of computing the partition function. Some special cases have been shown earlier. For example, when {a mathematical formula}d=1, {a mathematical formula}i=1 and {a mathematical formula}j=T, Eq. (B.6) becomes Eq. (25) since {a mathematical formula}Λ1:T1,s=1. Similarly, when {a mathematical formula}d=D, {a mathematical formula}i=j=t, Eq. (B.6) recovers Eq. (26) since {a mathematical formula}Δi:iD,s=1.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Semi-Markov CRFs as a special case
     </section-title>
     <paragraph>
      In this appendix we show how to convert a semi-Markov CRF (SemiCRF) [13] into an HSCRF. SemiCRF is an interesting flat segmental undirected model that generalises the chain CRF. In the SemiCRF framework the Markov process operates at the segment level, where a segment is a non-Markovian chain of nodes. A chain of segments is a Markov chain. However, since each segment can potentially have arbitrary length, inference in SemiCRFs is more involved than the chain CRFs.
     </paragraph>
     <paragraph>
      Represented in our HSCRF framework (Fig. C.13), each node {a mathematical formula}xt of the SemiCRF is associated with an ending indicator {a mathematical formula}et, with the following contextual cliques
     </paragraph>
     <list>
      <list-item label="•">
       Segmental state, which corresponds to a single segment {a mathematical formula}si:j and is essentially the state persistence contextual clique in the context {a mathematical formula}c=[ei−1:j=(1,0,..,0,1)] in the HSCRF's terminology.
      </list-item>
      <list-item label="•">
       State transition, which is similar to the state transition contextual clique in the HSCRFs, corresponding to the context {a mathematical formula}c=[et=1].
      </list-item>
     </list>
     <paragraph>
      Associated with the segmental state clique is the potential {a mathematical formula}Ri:js, and with the state transition is the potential {a mathematical formula}As′,s,t, where {a mathematical formula}s,s′∈S, and {a mathematical formula}S={1,2,...,K}.
     </paragraph>
     <paragraph>
      A SemiCRF is a three-level HSCRF, where the root and bottom are dummy states. This gives a simplified way to compute the partition function, ESS, and the MAP assignment using the AIO algorithms. Thus, techniques developed in this paper for numerical scaling and partially observed data can be applied to the SemiCRF. To be more consistent with the literature of flat models such as HMMs and CRFs, we call the asymmetric inside/outside masses by the forward/backward, respectively. Since the model is flat, we do not need the inside and outside variables.
     </paragraph>
     <paragraph>
      Forward
     </paragraph>
     <paragraph>
      With some abuse of notation, let {a mathematical formula}ζ1:js=(x1:j−1,e1:j−1,xj=s,ej=1). In other words, there is a segment of state s ending at j. We write the forward {a mathematical formula}αt(s) as{a mathematical formula}
     </paragraph>
     <paragraph>
      As a result the partition function can be written in term of the forward as{a mathematical formula}
     </paragraph>
     <paragraph>
      We now derive a recursive relation for the forward. Assume that the segment ending at j starts somewhere at {a mathematical formula}i∈[1,j]. Then for {a mathematical formula}i&gt;1, there exists the decomposition {a mathematical formula}ζ1:js=(ζ1:i−1s′,xi:j=s,ei:j−1=0) for some {a mathematical formula}s′, which leads to the following factorisation{a mathematical formula} The transition potential {a mathematical formula}As′,s,i−1 occurs in the context {a mathematical formula}c=[ei−1=1], and the segmental potential {a mathematical formula}Ri:js in the context {a mathematical formula}c=[xi:j=s,ei−1=1,ei:j−1=0].
     </paragraph>
     <paragraph>
      For {a mathematical formula}i=1, the factorisation reduces to {a mathematical formula}Φ[ζ1:js,z]=R1:js. Since we do not know the starting i, we must consider all possible values in the interval {a mathematical formula}[1,j. Thus, Eq. (C.1) can be rewritten as{a mathematical formula}{a mathematical formula}Backward
     </paragraph>
     <paragraph>
      The backward is the ‘mirrored’ version of the forward. In particular, let {a mathematical formula}ζ_j:Ts=(xj+1:T,ej:T,xj=s,ej−1=1). and we define the backward {a mathematical formula}βt(s) as{a mathematical formula}
     </paragraph>
     <paragraph>
      Clearly, the partition function can be written in term of the backward as{a mathematical formula}
     </paragraph>
     <paragraph>
      The recursive relation for the backward{a mathematical formula}
     </paragraph>
     <paragraph>
      Typically, we want to limit the segment to the maximum length of {a mathematical formula}L∈[1,T]. This limitation introduces some special cases when performing recursive computation of the forward and backward. Eqs. (C.4) and (C.8) are rewritten as follows{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Finally, we can extend the HSCRF straightforwardly by allowing the bottom level states to persist. With this relaxation we have a nested semi-Markov CRF model in the sense that each segment in a Markov chain is also a Markov chain of sub-segments.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>