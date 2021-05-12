<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Truthful learning mechanisms for multi-slot sponsored search auctions with externalities.
   </title>
   <abstract>
    Sponsored Search Auctions (SSAs) constitute one of the most successful applications of microeconomic mechanisms. In mechanism design, auctions are usually designed to incentivize advertisers to bid their truthful valuations and, at the same time, to guarantee both the advertisers and the auctioneer a non-negative utility. Nonetheless, in sponsored search auctions, the Click–Through–Rates (CTRs) of the advertisers are often unknown to the auctioneer and thus standard truthful mechanisms cannot be directly applied and must be paired with an effective learning algorithm for the estimation of the CTRs. This introduces the critical problem of designing a learning mechanism able to estimate the CTRs at the same time as implementing a truthful mechanism with a revenue loss as small as possible compared to the mechanism that can exploit the true CTRs. Previous work showed that, when dominant-strategy truthfulness is adopted, in single-slot auctions the problem can be solved using suitable exploration–exploitation mechanisms able to achieve a cumulative regret (on the auctioneer's revenue) of order O˜(T23), where T is the number of times the auction is repeated. It is also known that, when truthfulness in expectation is adopted, a cumulative regret (over the social welfare) of order O˜(T12) can be obtained. In this paper we extend the results available in the literature to the more realistic case of multi-slot auctions. In this case, a model of the user is needed to characterize how the CTR of an ad changes as its position in the allocation changes. In particular, we adopt the cascade model, one of the most popular models for sponsored search auctions, and we prove a number of novel upper bounds and lower bounds on both auctioneer's revenue loss and social welfare w.r.t. the Vickrey–Clarke–Groves (VCG) auction. Furthermore, we report numerical simulations investigating the accuracy of the bounds in predicting the dependency of the regret on the auction parameters.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      SSAs constitute one of the most successful applications of microeconomic mechanisms, producing a revenue of about $6 billion dollars in the US alone in the first half of 2010 [1]. In an SSA, a number of advertisers bids to have their sponsored links (from here on ads) displayed in some slot alongside the search results of a keyword. SSAs currently adopt the pay-per-click payment scheme, which requires positive payments from an advertiser only when its ad is clicked. Given an allocation of ads over the available slots, each ad is associated with a CTR, corresponding to the probability of being clicked by the user. CTRs play a crucial role in the definition of the auction, since the auctioneer relies on (estimates of) the CTRs to determine the allocation of ads over slots and to compute the payment of each ad. Models similar to SSAs are also used in many other advertisement applications. For instance, in contextual advertising, the text of a website is scanned for keywords and an auction is used to select the ads to display in vertical/horizontal slots on the basis of the advertisers' bids and CTRs of the ads in the given context [2].
     </paragraph>
     <paragraph>
      In microeconomic literature, SSAs have been formalized as a mechanism design problem [3], where the objective is to design an auction that incentivizes advertisers to bid their truthful valuations (needed for economic stability) and that guarantees both the advertisers and the auctioneer to have a non-negative utility. The most common SSA mechanism is the Generalized Second Price (GSP) auction [4], [5]. As shown in [4], this mechanism is not truthful and advertisers may implement bidding strategies that pay more than bidding their truthful valuations.
     </paragraph>
     <paragraph>
      While the GSP is still popular in many SSAs, the increasing evidence of its limits is strongly pushing towards the adoption of the more appealing Vickrey–Clarke–Groves (VCG) mechanism, which is already successfully employed in the related scenario of contextual advertising, by Google [2] and Facebook [6]. The first drawback of the GSP is that its equilibria may be inefficient (in terms of social welfare) w.r.t. the VCG outcome: considering the whole set of Nash equilibria in full information, the Price of Anarchy (PoA) of the GSP is upper bounded by about 1.6, while considering the set of Bayes–Nash equilibria the PoA is upper bounded by about 3.1 [7]. Similarly, the revenue of a (full information) Nash equilibrium can be arbitrarily small w.r.t. the VCG outcome, while in the Bayesian case the revenue is upper bounded by 6 [8]. Furthermore, the automated bidding strategies, used in practice by the advertisers to find their best bids, may not even converge to any Nash equilibrium and, under mild assumptions, the states they converge to are shown to be arbitrarily inefficient [9]. When externalities are introduced, it is known that no Nash equilibrium of the GSP provides a larger revenue than the VCG outcome [10], [11]. Finally, there is a recent increase in the use of additional features (such as larger formats, reviews, maps, or phone numbers) arranged by the search engines on the web page together with the ads to increase the attention of the user. It is known that the GSP behaves poorly in this setting, while the VCG is almost equivalent to the standard setting [12].
     </paragraph>
     <paragraph>
      In this paper, we focus on the problem of designing truthful mechanisms when the CTRs are not known and need to be estimated in SSAs with multiple slots. This problem is particularly relevant in practice because the assumption that all the CTRs are known beforehand is rarely realistic. Furthermore, it also poses interesting scientific challenges since it represents one of the first examples where online learning theory and mechanism design—two important fields in artificial intelligence that recently received a lot of attention in the literature—are paired to obtain effective methods to learn under equilibrium constraints (notably the truthfulness property). For the sake of completeness, we remark that the combination of these ideas have been used also in the other fields, e.g., crowdsourcing [13].
     </paragraph>
     <paragraph>
      Related works. The problem of estimating the CTRs and identifying the best allocation of ads can be effectively formalized as a Multi-Armed Bandit (MAB) problem[14], where each ad is an arm and the objective is to minimize the cumulative regret either on the auctioneer's revenue or the social welfare, i.e., the difference in revenue or social welfare, respectively, of the mechanisms implemented over time estimating the CTRs and of the mechanisms that can exploit the true CTRs. The problem of budgeted advertisers (i.e., auctions where the total amount of money each advertiser is willing to pay is limited) with multiple queries is considered in [15]. This problem is formalized as a budgeted multi-bandit multi-arm problem, where each bandit corresponds to a query, and an algorithm is proposed with theoretical guarantees on auctioneer revenue regret. Nonetheless, the proposed method works in a non-strategic environment, where advertisers do not try to influence the outcome of the auction and always bid their true values. The strategic dimension of SSAs is partially taken into consideration in [16], where the advertisers are assumed to play a bidding strategy at the equilibrium of the GSP w.r.t. a set of estimated CTRs available to both the auctioneer and the advertisers. The authors introduce a learning algorithm which explores different rankings of the ads to improve the CTR estimates and, at the same time, to avoid that the advertisers have incentives to deviate from the aforementioned equilibrium strategy. In [17], [18], the authors formulate for the first time the problem of designing truthful learning mechanisms according to the notion of truthfulness in high probability in multi-slot SSAs. The single-slot online advertising is studied also in [19] where the notion of Bayesian Incentive Compatibility (BIC) is taken into consideration and an asymptotically BIC and ex ante efficient mechanism is introduced.
     </paragraph>
     <paragraph>
      The most complete study of truthful bandit mechanisms so far is reported in [20] and [21]. These works provide a complete analysis on the constraints that truthfulness forces on the MAB algorithm with single-slot SSAs, proving that no dominant-strategy truthful bandit mechanism can achieve a regret (over social welfare or auctioneer's revenue) smaller than {a mathematical formula}Ω˜(T23) and that the exploration and exploitation phases must be separate.{sup:1}{sup:,}{sup:2} The lower bound over the regret holds also when the truthfulness is in expectation w.r.t. the click realizations. Finally, they also provide nearly-optimal algorithms matching the lower bound on the regret. In both [20] and [21], advertisers' utility is not subject to any form of time discount, in contrast with what happens in practice, where advertisers may favor early small gains over larger gains in the future. However, the mechanisms introduced in [20] and [21] are truthful even in presence of discount since the sharp separation of exploration and exploitation would still force advertisers with discounting to reveal their true valuation.{sup:3} When the notion of truthfulness is relaxed, adopting truthfulness in expectation w.r.t. the mechanism randomness, it is possible to obtain in the case of single-slot SSAs a regret {a mathematical formula}O˜(T12) (over the social welfare) without separating the exploration and exploitation phases [23].
     </paragraph>
     <paragraph>
      When multiple slots are present, a user model is needed to describe how the CTR of an ad changes as its position in the allocation changes. All the models available in the literature assume that the CTR is given by the product of two terms: the probability that an ad is clicked once observed by the user, and the probability that the user observes an ad given the complete allocation of ads over slots. The basic model (commonly referred to as separability model) prescribes that the probability of observing an ad depends only on its position [3]. Recently, more accurate models have been proposed and one of the most popular models is the cascade model. According to this model, the user scans the slots from top to bottom and the probability that she moves from a given slot to the next depends on the former slot itself and the identity of the ad displayed in it (this kind of user is commonly called Markovian user) [24], [25]. As a result, the overall probability of observing an ad depends on the slot in which it is displayed and on all the ads allocated above it. The validity of the cascade model has been evaluated and supported by a wide range of experimental investigations [26], [27]. The only results on learning mechanisms for SSAs with multiple slots are described in [28], where the authors characterize dominant-strategy truthful mechanisms and provide theoretical bounds over the social welfare regret for the separability model. However, these results are partial (e.g., they do not consider the common case in which the slot-dependent parameters are monotonically decreasing over slots), and they cannot be easily extended to the more challenging case of the cascade model (see Section 3.3).
     </paragraph>
     <paragraph>
      Original contributions. In the present paper, we build on the results available in the literature and we extend the partial results presented in [29] to a wider range of cases, providing also a number of contributions when the separability model and the cascade model are adopted. More precisely, our results can be summarized as follows.
     </paragraph>
     <list>
      <list-item label="•">
       Separability model with monotonically decreasing parameters/only position-dependent cascade model: in this case, there are two groups of parameters, one related to the ads (called quality) and one to the slots (called prominence). We studied all the configurations of information incompleteness. When only qualities are unknown, we provide a non-randomized learning mechanism that is dominant-strategy truthful a posteriori w.r.t. the click realizations and with a regret of {a mathematical formula}O˜(T23) (while it is an open problem whether it is possible to obtain a better upper bound adopting truthfulness in expectation).{sup:4} When only prominences are unknown, we provide a non-randomized learning mechanism that is dominant-strategy truthful in expectation w.r.t. the click realizations with a regret of 0 and a randomized learning mechanism that is dominant-strategy truthful in expectation w.r.t. the realizations of the random component of the mechanism with a regret of {a mathematical formula}O(1). We also show that any dominant-strategy truthful a posteriori w.r.t. all the sources of randomness learning mechanism would have a regret of {a mathematical formula}Θ(T). When both groups of parameters are unknown, we provide a random learning mechanism that is dominant-strategy truthful in expectation only w.r.t. the realizations of the random component of the mechanism with a regret of {a mathematical formula}O˜(T23),
      </list-item>
      <list-item label="•">
       Cascade model: in the non-factorized cascade model (i.e., when the observation probabilities can be arbitrary) we show that it is possible to obtain a regret of {a mathematical formula}O˜(T23) in dominant-strategy truthful in expectation w.r.t. all the sources of randomness learning mechanisms when only the qualities of the ads are unknown.{sup:5} We show also that in the factorized cascade model (i.e., when the observation probabilities are the products of terms depending on either the slot or the ads, as used in [24]), any non-randomized learning mechanism that is dominant-strategy truthful (even in expectation w.r.t. the click realizations) has a regret of {a mathematical formula}Θ(T) even in the special case in which only the ad-dependent parameters are unknown (while it is an open problem whether it is possible to obtain a better upper bound adopting a randomized mechanism and truthfulness in expectation w.r.t. the realization of the random component of the mechanism),
      </list-item>
      <list-item label="•">
       Learning parameters: for each setting described above we provide practical guidelines on how the learning parameters can be tuned to minimize the bound over the regret depending on the characteristics of the auction (e.g., number of slots and advertisers),
      </list-item>
      <list-item label="•">
       Numerical simulations: we investigate the accuracy of all the theoretical regret bounds in predicting the dependency of the regret on the auction parameters by numerical simulations. We show that the theoretical asymptotic dependency matches the actual dependency we observed by simulation.
      </list-item>
     </list>
     <paragraph>
      Paper organization. The paper is organized as follows. In Section 2, we briefly review the basics of mechanism design and MAB learning. Section 3, formalizes SSAs, introduces the corresponding online learning mechanism design problem, and it provides a more formal overview of existing results and the new findings of this paper. In Sections 4 and 5, we report and discuss the main regret bounds in the case of position-dependent and position- and ad-dependent externalities. In Section 6, we report numerical simulations aiming at testing the accuracy of the theoretical bounds. Section 7 concludes the paper and proposes future directions of investigation. The detailed proofs of the theorems are reported in Appendix A Vickrey–Clarke–Groves mechanism, Appendix B Monotonicity and Myerson's payments, Appendix C Proof of revenue regret in, Appendix D Proof of revenue regret in, Appendix E Proof of revenue regret in, Appendix F Proof of revenue regret in, Appendix G Deviation regret, Appendix H Proofs of social-welfare regret in, Appendix I Proof of social-welfare regret in, Appendix J Proof of social-welfare regret.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <section label="2.1">
      <section-title>
       Economic mechanisms
      </section-title>
      <paragraph>
       In this section we provide an overview on the definitions and results of mechanism design that are relevant to the paper. The objective of mechanism design [30] is to design allocation and payment functions satisfying some desirable properties when agents are rational and retain private information representing their preferences—also referred to as the type of the agent. Without loss of generality, mechanism design focuses on specific mechanisms, called direct, in which the only action available to the agents is to report their (potentially non-truthful) type. On the basis of the agents' reports the mechanism determines the allocation of resources to agents and the agents' payments.
      </paragraph>
      <paragraph>
       The main desirable property of a mechanism is truthfulness, often referred to as Incentive Compatibility (IC), which requires that reporting the true types constitutes an equilibrium strategy profile for the agents.{sup:6} When a mechanism is not truthful, agents should try to optimize their (untruthful) strategies on the basis of some model about the opponents' behavior, but, in absence of common information, no normative model for rational agents exists. This leads the mechanism to be economically unstable, given that the agents continuously change their strategies. Different notions of truthfulness are available. The most common ones are Dominant Strategy Incentive Compatibility (DSIC)—i.e., reporting the true types is the best action an agent can play independently of the actions of the other agents, ex post incentive compatibility (ex post IC)—i.e., reporting the true types is a Nash equilibrium, and BIC—i.e., reporting the true types is a Bayes–Nash equilibrium. Interestingly, DSIC and ex post IC are equivalent notions of truthfulness in absence of interdependency among the types of the agents, while BIC is weaker than DSIC, since it only requires that every agent has a Bayesian prior over the types of the other agents and IC is defined in expectation w.r.t. the prior. When there are other sources of randomness in the mechanism design problem (not due to the distribution of probabilities over the types of the agents), e.g., random components of the mechanism or the realization of events, weaker solution concepts, said in expectation, are commonly adopted, e.g., DSIC in expectation or ex post IC in expectation. Instead, we use the term “a posteriori” when the truthfulness holds for every realization. In presence of multiple sources of randomness, a mechanism may be in expectation w.r.t. some sources and a posteriori w.r.t. other sources. When we use only DSIC a posteriori without specifying the source of randomness, we mean DSIC a posteriori w.r.t. all the sources of randomness. Moreover, mechanisms can exploit the realizations of the events adopting different payment functions for each different realization. These mechanisms are said Execution Contingent (EC) [31], [32].
      </paragraph>
      <paragraph>
       In addition to IC, other desirable properties include: Allocative Efficiency (AE)—i.e., the allocation maximizes the social welfare, Individual Rationality (IR)—i.e., each agent is guaranteed to have no loss when reporting truthfully, and Weak Budget Balance (WBB)—i.e., the mechanism is guaranteed to have no loss. In presence of sources of randomness, IR and WBB can be in expectation w.r.t. all the possible realizations, or a posteriori if they hold for every possible realization. As for IC, in presence of multiple sources of randomness, these properties may be in expectation w.r.t. some sources and a posteriori w.r.t. other sources. When we use only IR (or WBB) a posteriori without specifying the source of randomness, we mean IR (or WBB) a posteriori w.r.t. all the sources of randomness.
      </paragraph>
      <paragraph>
       The economic literature provides an important characterization of the allocation functions that can be adopted in IC mechanisms when utilities are quasi linear[30]. Here, we survey the main results related to DSIC mechanisms where no sources of randomness are present. In unrestricted domains (i.e., the agents' types are defined over spaces with arbitrary structure) for the agents' preferences, only weighted maximal-in-its-range allocation functions can be adopted in DSIC mechanisms [33], [34]. More precisely, a weighted maximal-in-its-range allocation function chooses, among a subset of allocations that does not depend on the types reported by the agents (i.e., the range), the allocation maximizing the weighted social welfare, where each agent is associated with a positive (type-independent) weight. It trivially follows that, when the range is composed of all the possible allocations and all the agents have the same weights, only AE mechanisms can be DSIC. When weighted maximal-in-its-range allocation functions are adopted, only weighted Groves payments lead to DSIC mechanisms [30]. The most common DSIC mechanism is the VCG [30], in which the range is composed of all the allocations and all the weights are unitary. The idea of the VCG mechanism is that each agent pays the difference between the social welfare of the optimal outcome when she does not participate to the mechanism and the social welfare of the outcome obtained when she participates minus its contribution (we leave a more formal and detailed description of the VCG mechanism to Appendix A). Notice that the VCG mechanism satisfies also IR and WBB and, among all the Groves mechanisms, it is the one maximizing the revenue of the auctioneer. We refer to the weighted version of the VCG as Weighted Vickrey–Clarke–Groves (WVCG).
      </paragraph>
      <paragraph>
       When the domain of the agents' preferences is restricted (i.e., the types are defined over spaces with specific structure, e.g., compact sets or discrete values), weighted maximal-in-its-range property is not necessary for DSIC. The necessary condition is weakly monotonicity [30], which is also sufficient for convex domains. In specific restricted domains, weak monotonicity leads to simple and operational tools. For instance, when the preferences of the agents are single-parameter linear—i.e., the agents' value is given as the product between the agent's type and an allocation-dependent coefficient called load[35], monotonicity requires that the load is monotonically increasing in the type of the agent. In this case, any DSIC mechanism is based on the Myerson's payments defined in [35], [36].{sup:7} Notice that the VCG mechanism is still the mechanism maximizing the auctioneer's revenue among all the DSIC mechanisms, including those that are not AE. The Myerson's payments include an integral that may be not easily computable. However, by adopting a random mechanism and accepting DSIC in expectation w.r.t. the realizations of the random component of the mechanism, such integral can be easily estimated by using samples [37]. Another drawback of the payments described in [35], [36] is that they require the off-line evaluation of the social welfare of the allocations for some agents' types different from the reported ones and this may be not possible in many practical situations. A way to overcome this issue is to adopt the result presented in [23], in which the authors propose an implicit way to calculate the payments. More precisely, given an allocation function in input, a random component is introduced such that with a small probability the reported types of the agents are modified to obtain the allocations that are needed to compute the payments in [35], [36]. The resulting allocation function is less efficient than the allocation function given in input, but the computation of the payments is possible and it is executed online.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Multi-armed bandit
      </section-title>
      <paragraph>
       The MAB [14] is a simple yet powerful framework formalizing the online decision-making problem under uncertainty. Historically, the MAB framework finds its motivation in optimal experimental design in clinical trials, where two treatments, say A and B, need to be tested. In an idealized version of the clinical trial, T patients are sequentially enrolled in the trial, so that whenever a treatment is tested on a patient, the outcome of the test is recorded and it is used to choose which treatment to provide to the next patient. The objective is to provide the best treatment to the largest number of patients. This raises the challenge of balancing the collection of information and the maximization of the performance of the trial, a problem usually referred to as the exploration–exploitation trade-off. On the one hand, it is important to gather information about the effectiveness of the two treatments by repeatedly providing them at different patients (exploration). On the other hand, as the estimate of effectiveness of the treatments becomes more accurate, the (estimated) best treatment should be selected more often (exploitation). This scenario matches with a large number of applications, such as online advertisements, adaptive routing, and cognitive radio.
      </paragraph>
      <paragraph>
       In general, the MAB framework can be adopted whenever a set of N arms (e.g., treatments, ads) is available and the rewards (e.g., effectiveness of a treatment, CTR of an ad) associated with each of them are random realizations from unknown distributions. Although this problem can be solved by dynamic programming methods and notably by using the Gittins index solution [38], this requires a prior over the distribution of the reward of the arms and it is often computationally heavy (high-degree polynomial in T). More recently, a wide range of techniques have been developed to solve the bandit problem. In particular, these algorithms formalize the objective using the notion of regret, which corresponds to the difference in performance over T steps between an optimal selection strategy which knows in advance the performance of all the arms and an adaptive strategy which learns over time which arms to select. Although a complete review of the bandit algorithms is beyond the scope of this paper (see [39] for a review), we only discuss two results which are relevant to the rest of the paper. The exploration-separated algorithms solve the exploration–exploitation trade-off by introducing a strict separation between the exploration and the exploitation phases. While during the exploration phase all the arms are uniformly selected, in the exploitation phase only the best estimated arm is selected until the end of the experiment. The length τ of the exploration phase is critical to guarantee the success of the experiment and it is possible to show that, if properly tuned, the worst-case cumulative regret scales as {a mathematical formula}O˜(T23), matching the lower bound {a mathematical formula}Ω˜(T23). Another class of algorithms relies on the construction of confidence intervals for the reward of each arm and it does not separate exploration and exploitation steps. In particular, the Upper-Confidence Bound (UCB) algorithm [40] gives an extra exploration bonus to arms which have been selected only few times in the past and it achieves a worst-case cumulative regret of order {a mathematical formula}O˜(T12), matching the lower bound {a mathematical formula}Ω˜(T12).
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Problem statement
     </section-title>
     <paragraph>
      In this section we introduce all the notation used throughout the rest of the paper. In particular, we formalize the SSA model, we define the mechanism design problem, and we introduce the learning process.
     </paragraph>
     <section label="3.1">
      <section-title>
       SSA model
      </section-title>
      <paragraph>
       We resort to the standard model of SSAs [3]. The notation described in the sequel is summarized in Table 1. We denote by {a mathematical formula}N={1,…,N} the set of ads indexes and by {a mathematical formula}ai with {a mathematical formula}i∈N the i-th ad (we assume w.l.o.g. each advertiser has only one ad and therefore we can identify by {a mathematical formula}ai the i-th ad and the i-th advertiser indifferently). Each ad {a mathematical formula}ai is characterized by a quality{a mathematical formula}qi corresponding to the probability that {a mathematical formula}ai is clicked once observed by the user, and by a value{a mathematical formula}vi∈V=[0,V] that {a mathematical formula}ai receives when clicked ({a mathematical formula}ai receives a value of zero if not clicked). We denote by v the values profile {a mathematical formula}(v1,…,vN) and by {a mathematical formula}v−i the values profile obtained by removing {a mathematical formula}vi from v. While the qualities {a mathematical formula}{qi}i∈N may be known by the auctioneer with some level of accuracy, the values {a mathematical formula}{vi}i∈N are private information of the advertisers. We denote by {a mathematical formula}K={1,…,K} with {a mathematical formula}K&lt;N, the set of slot indexes and by {a mathematical formula}sm, with {a mathematical formula}m∈K, the m-th slot from top to bottom. For notational convenience, we also define the extended set of slots indexes {a mathematical formula}K′=K∪{K+1,…,N}.{sup:8}
      </paragraph>
      <paragraph>
       We use the ordered pair {a mathematical formula}〈sm,ai〉 to indicate that ad {a mathematical formula}ai is allocated to slot {a mathematical formula}sm, while we denote by θ an allocation, defined as a collection of pairs {a mathematical formula}〈sm,ai〉, and by Θ the set of all the possible allocations. Although in an auction only K ads can be actually displayed, we define an allocation as {a mathematical formula}θ={〈sm,ai〉:m∈K′,i∈N} where both m and i occur exactly once and any ad assigned to a slot {a mathematical formula}sm with {a mathematical formula}m&gt;K is not displayed. We define two maps {a mathematical formula}π:N×Θ→K′ and {a mathematical formula}α:K′×Θ→N such that {a mathematical formula}π(i;θ) returns the index of the slot in which {a mathematical formula}ai is displayed in allocation θ and {a mathematical formula}α(m;θ) returns the index of the ad displayed in slot {a mathematical formula}sm in allocation θ. Given {a mathematical formula}θ∈Θ, we have that {a mathematical formula}π(i;θ)=m if and only if {a mathematical formula}α(m;θ)=i.
      </paragraph>
      <paragraph>
       With more than one slot, it is necessary to adopt a model of the user describing how the value of an advertiser varies over the slots. We assume that the user behaves according to the cascade model defined by [24], [25]. In the cascade model, the user's behavior is defined by a Markov chain whose possible states correspond to the slots, which are observed sequentially from the top to the bottom, and a transition matrix that defines, given the current slot, the probability that the user observes the ad {a mathematical formula}ai displayed in the next slot or stops observing any other ad. More precisely, the probability may depend on the index of the slot (i.e., {a mathematical formula}π(i;θ)), in this case the externalities are said position-dependent, and/or on the ad that precedes {a mathematical formula}ai in the current allocation θ (i.e., {a mathematical formula}aα(π(i;θ)−1;θ)), in this case the externalities are said ad-dependent.
      </paragraph>
      <paragraph>
       In the general case, the cascade model can be described by introducing a set of parameters {a mathematical formula}γm,i defined as the probability that a user, observing ad {a mathematical formula}ai in slot {a mathematical formula}sm, observes the ad in the next slot {a mathematical formula}sm+1. The probability that a user observes the ad displayed at slot {a mathematical formula}sm in allocation θ is denoted by {a mathematical formula}Γm(θ) and it is defined as:{a mathematical formula} Given an allocation θ, the CTR of an ad {a mathematical formula}ai is the probability to be clicked once allocated according to θ and it is computed as {a mathematical formula}Γπ(i;θ)(θ)qi, corresponding to the joint probability that the user arrives at observing the slot in which the ad is displayed and then clicks on it. Similarly, the CTR of the ad displayed at slot {a mathematical formula}sm can be computed as {a mathematical formula}Γm(θ)qα(m;θ). We notice that, according to this model, the user may click multiple different ads at each impression. Given an allocation θ, the expected value (w.r.t. the click realizations) of advertiser {a mathematical formula}ai from θ is {a mathematical formula}Γπ(i;θ)(θ)qivi, that is, the product of the CTR {a mathematical formula}Γπ(i;θ)(θ)qi by the value of the advertiser {a mathematical formula}vi. The advertisers' cumulative expected value from allocation θ, commonly referred to as Social Welfare (SW), is:{a mathematical formula} In [24], [25], the authors factorize the probability {a mathematical formula}γm,i as the product of two independent terms: the prominence{a mathematical formula}λm, which only depends on the slot {a mathematical formula}sm, and the continuation probability{a mathematical formula}ci, which only depends on the ad {a mathematical formula}ai.{sup:9}
      </paragraph>
      <paragraph>
       Finally, we denote by {a mathematical formula}clickmi∈{0,1} the no-click/click event for ad {a mathematical formula}ai allocated in slot {a mathematical formula}sm.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Mechanism design problem
      </section-title>
      <paragraph>
       A direct-revelation economic mechanism for SSAs is formally defined as a tuple {a mathematical formula}(N,V,Θ,f,{pi}i∈N) where {a mathematical formula}N is the set of the agents' (i.e., the advertisers) indexes, {a mathematical formula}V is the set of the types of the agents (where the type of ad {a mathematical formula}ai is the single-parameter valuation {a mathematical formula}vi), Θ is the set of the outcomes (i.e., the allocations), f is the allocation function defined as {a mathematical formula}f:VN→Θ, and {a mathematical formula}pi is the payment function for advertiser {a mathematical formula}ai defined as {a mathematical formula}pi:VN→R. We denote by {a mathematical formula}vˆi the value reported by advertiser {a mathematical formula}ai to the mechanism, by {a mathematical formula}vˆ the profile of reported values, and by {a mathematical formula}vˆ−i the profile obtained by removing {a mathematical formula}vˆi from {a mathematical formula}vˆ.
      </paragraph>
      <paragraph>
       At the beginning of an auction, each advertiser {a mathematical formula}ai reports its value {a mathematical formula}vˆi. The mechanism chooses the allocation on the basis of the values reported by the advertisers using {a mathematical formula}f(vˆ) and subsequently computes the payment of each advertiser {a mathematical formula}ai as {a mathematical formula}pi(vˆ). The expected utility of advertiser {a mathematical formula}ai is defined as {a mathematical formula}Γπ(i;f(vˆ))(f(vˆ))qivi−pi(vˆ), corresponding to the value expected by advertiser {a mathematical formula}ai minus the payment prescribed by the payment function. Notice that the utility is linear in the type of the agent. Since each advertiser is an expected utility maximizer, it will misreport its value (i.e., {a mathematical formula}vˆi≠vi) whenever this may lead to increase its utility. Mechanism design aims at finding an allocation function f and a vector of payments {a mathematical formula}{pi}i∈N such that some desirable properties—discussed in Section 2.1—are satisfied [30].
      </paragraph>
      <paragraph>
       When the parameters {a mathematical formula}qi and {a mathematical formula}γm,i are known, the VCG mechanism satisfies DSIC in expectation w.r.t. the click realizations, IR in expectation w.r.t. the click realizations, WBB a posteriori w.r.t. the click realizations, and AE. DSIC and IR do not hold a posteriori. In the VCG mechanism, the allocation function, denoted by {a mathematical formula}f⁎, maximizes the SW given the reported types as{a mathematical formula} and the payments are defined as{a mathematical formula} where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}θ−i⁎:=f⁎(vˆ−i), i.e., the optimal allocation when advertiser {a mathematical formula}ai is not present in the auction, and
       </list-item>
       <list-item label="•">
        {a mathematical formula}SW−i(θ⁎,vˆ):=∑j∈N,j≠iΓπ(j;θ⁎)(θ⁎)qjvˆj, i.e., the cumulative expected value of the optimal allocation {a mathematical formula}θ⁎ minus the expected value of advertiser {a mathematical formula}ai.
       </list-item>
      </list>
      <paragraph>
       The payment of advertiser {a mathematical formula}ai is the difference between the SW that could be obtained from allocation {a mathematical formula}θ−i⁎, computed removing ad {a mathematical formula}ai from the auction, and the SW of the efficient allocation {a mathematical formula}θ⁎ without the contribution of advertiser {a mathematical formula}ai. In other words, this corresponds to the cost in terms of efficiency of the presence of {a mathematical formula}ai in the auction. The VCG mechanism can be easily extended to weighted case (the WVCG mechanism). The weighted SW is {a mathematical formula}SWw(θ,v)=∑i=1NΓπ(i;θ)(θ)qiviwi where {a mathematical formula}wi is the weight of advertiser {a mathematical formula}ai. In the WVCG, the allocation maximizing the weighted SW is chosen, while the payment is defined as {a mathematical formula}piw(vˆ)=1wi(SWw(θ−i⁎,vˆ−i)−SW−iw(θ⁎,vˆ)), where {a mathematical formula}SW−iw(θ,vˆ))=∑j∈N,j≠iΓπ(j;θ)(θ)qjvjwj.
      </paragraph>
      <paragraph>
       The WVCG mechanism is DSIC in expectation w.r.t. the click realizations and IR in expectation w.r.t. the click realizations, but, WVCG being a generalization of the VCG, these properties do not hold a posteriori. This is because an advertiser may have a positive payment even when its ad has not been clicked. Nonetheless, the mechanism can be easily modified to satisfy DSIC w.r.t. the click realizations and IR a posteriori w.r.t. the click realizations by using pay-per-click payments {a mathematical formula}pi⁎,c as follows:{a mathematical formula} The contingent formulation of the payments is such that {a mathematical formula}E[pi⁎,c(vˆ,clickπ(i;θ⁎)i)]=pi⁎(vˆ), where the expectation is w.r.t. the click event, which is distributed as a Bernoulli random variable with parameter coinciding with the CTR of ad {a mathematical formula}ai in allocation {a mathematical formula}θ⁎, i.e., {a mathematical formula}Γπ(i;θ⁎)(θ⁎)qi. Similar definitions hold for the WVCG mechanism.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Online learning mechanism design problem
      </section-title>
      <paragraph>
       In many practical problems, the parameters (i.e., {a mathematical formula}qi and {a mathematical formula}γm,i) are not known in advance by the auctioneer and must be estimated at the same time as the auction is run. This leads to the definition of an iterative process where the auction is repeated over T steps using different estimates of the CTRs. This introduces a tradeoff between exploring different possible allocations, so as to collect information about the parameters, and exploiting the estimated parameters, so as to implement a truthful high-revenue auction (i.e., a VCG mechanism). This problem could be easily cast as a MAB problem [14] and standard techniques could be used to solve it, e.g., [42]. Nonetheless, such an approach would completely overlook the strategic dimension of the problem: advertisers may choose their reported values at each step {a mathematical formula}t∈{1…,T} to influence the outcome of the auction at t and/or in future steps in order to increase their cumulative utility over all the steps of the horizon T. Thus, in this context, truthfulness requires that reporting the truthful valuation maximizes the cumulative utility over the whole horizon T. The truthfulness can be in dominant strategies if advertisers know everything (including, e.g., the ads that will be clicked at each step t if displayed) or in expectation. As customary, we adopt four forms of truthfulness:
      </paragraph>
      <list>
       <list-item label="•">
        DSIC a posteriori w.r.t. the click realizations and the realizations of the random component of the mechanism (if such a component is present),
       </list-item>
       <list-item label="•">
        DSIC in expectation w.r.t. the click realizations and a posteriori w.r.t. the realizations of the random component of the mechanism (if such a component is present),
       </list-item>
       <list-item label="•">
        DSIC in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations, and
       </list-item>
       <list-item label="•">
        DSIC in expectation w.r.t. both randomization sources.
       </list-item>
      </list>
      <paragraph>
       Here we face the challenging problem where the exploration–exploitation dilemma must be solved so as to maximize the revenue of the auction under the hard constraint of truthfulness. Let {a mathematical formula}A be a mechanism run over T steps. In particular, we only focus on mechanisms which are (at least) DSIC in expectation w.r.t. all sources of randomization, since for non-truthful mechanisms the dynamics of bids is unpredictable. At each step t, {a mathematical formula}A defines an allocation {a mathematical formula}θt and prescribes an expected payment {a mathematical formula}pi,t(v) for each ad {a mathematical formula}ai. The objective of {a mathematical formula}A is to minimize the loss of the auctioneer w.r.t. the revenue provided by the VCG mechanism computed on the actual parameters, and to preserve the properties of IR and WBB. More precisely, we measure the performance of {a mathematical formula}A as its cumulative expected regret over T steps:{a mathematical formula} where the expectation is taken w.r.t. the click realizations and the realization of the random component of the mechanism if present. Indeed, we remark that the regret is not defined on the basis of the pay-per-click payments asked on a specific sequence of clicks but on the expected payments {a mathematical formula}pi,t(v). Furthermore, we notice that since the learning mechanism {a mathematical formula}A estimates the CTRs from the observed (random) clicks, the expected payments {a mathematical formula}pi,t(v) are random as well. Finally, the payments are computed on the true valuations v constant over time since the mechanism {a mathematical formula}A is truthful by definition and thus the best option for all advertisers is to bid their true value at any step. The mechanism {a mathematical formula}A is a no-regret mechanism if its per-step regret {a mathematical formula}RT(A)/T decreases to 0 as T increases, i.e., {a mathematical formula}limT→∞⁡RT(A)/T=0. Another popular definition of performance [17], [21] is the SW regret, that measures the performance of {a mathematical formula}A as follows:{a mathematical formula} where {a mathematical formula}θ˜t is the allocation prescribed by the learning mechanism at step t and the expectation, as before, is taken w.r.t. the click realizations and the realization of the random component of the mechanism if present. We notice that minimizing the SW regret {a mathematical formula}RTSW does not coincide with minimizing {a mathematical formula}RT. In fact, once the quality estimates are accurate enough, such that {a mathematical formula}θt is equal to {a mathematical formula}θ⁎, the SW regret drops to zero. On the other hand, since {a mathematical formula}pi,t(v) is computed according to the estimated qualities, {a mathematical formula}RT(A) might still be positive even if {a mathematical formula}θt=θ⁎. In addition, we believe that in practical applications, providing a theoretical bound over the regret of the auctioneer's revenue is more important rather than a bound on the regret of the SW. Nevertheless, we show that the same approach we use to derive the bounds over the auctioneer's revenue can be employed to derive similar bounds over the SW. Finally, we refer to Appendix G for an alternative definition of the regret, related to the deviation between payments.
      </paragraph>
      <paragraph>
       The study of the problem when {a mathematical formula}K=1 is well established in the literature. More precisely, the properties required to have a mechanism that is DSIC a posteriori w.r.t. the realizations of the random component of the mechanism are studied in [20] and it is shown that any learning algorithm must split the exploration and the exploitation in two separate phases in order to incentivize the advertisers to report their true values. This condition has a strong impact on the regret {a mathematical formula}RT(A) of the mechanism. In fact, while in a standard bandit problem the distribution-free regret is of order {a mathematical formula}Ω(T12), in single-slot auctions, DSIC a posteriori mechanisms have a regret {a mathematical formula}Ω(T23). The same result holds for DSIC a posteriori w.r.t. the realizations of the random component of the mechanism and in expectation w.r.t. the click realizations. In [20], a truthful learning mechanism is designed with nearly optimal regret of order {a mathematical formula}O˜(T23). Similar structural properties for DSIC a posteriori w.r.t. the click realizations mechanisms are also studied in [21] and similar lower-bounds are derived for the SW regret. In [23] the authors show that, by introducing a random component in the allocation function and resorting to DSIC a posteriori w.r.t. the click realizations and in expectation w.r.t. the realizations of the random component of the mechanism, the separation of exploration and exploitation phases can be avoided. In this case, the upper bound over the regret of the SW is {a mathematical formula}O˜(T12), thus matching the best distribution-free bound in standard bandit problems. However, the payments of this mechanism suffer of potentially high variance, which may be an undesirable property in practice. Although we expect that this mechanism could also achieve a revenue regret of the order of {a mathematical formula}O˜(T12), no formal proof is known.
      </paragraph>
      <paragraph>
       In this paper, we focus on the study of the problem when {a mathematical formula}K&gt;1, which is still mostly unexplored. In this case, a crucial role is played by the CTR model. While with only one slot, the advertisers' CTRs coincide to their qualities {a mathematical formula}qi, with multiple slots the CTRs may also depend on the slots and the allocation of the other ads. The only results on learning mechanisms for SSAs with {a mathematical formula}K&gt;1 are described in [28], [43], where the authors characterize DSIC a posteriori mechanisms and provide theoretical bounds over the SW regret. More precisely, the authors assume a simple CTR model in which the CTR itself depends on the ad {a mathematical formula}ai and the slot {a mathematical formula}sm. This model differs from the cascade model (see Section 2.1) where the CTR is a more complex function of the quality {a mathematical formula}qi of an ad and the cumulative probability of observation {a mathematical formula}Γm(θ), which in general depends on both the slot {a mathematical formula}sm and the full allocation θ (i.e., the ads allocated before slot {a mathematical formula}sm). It can be easily shown that the model studied in [28] does not include and, at the same time, is not included by the cascade model. However, the two models match when the CTRs are separable in two terms, in which the first is the agents' quality and the second is a parameter in {a mathematical formula}[0,1] monotonically decreasing over the slots (i.e., only-position-dependent cascade model). Furthermore, while the cascade model is supported by an empirical activity which confirms its validity as a model of the user behavior [26], [27], the model considered in [28] has not been empirically studied. In [28], the authors show that when the CTRs are unrestricted (e.g., they are not strictly monotonically decreasing in the slots), the regret over the SW is {a mathematical formula}Θ(T) and therefore at every step (of repetition of the auction) a non-zero regret is accumulated. In addition, the authors provide necessary and, in some situations, sufficient conditions to have DSIC a posteriori w.r.t. the click realizations. More precisely, the authors show that the allocation function of a mechanism that is DSIC a posteriori w.r.t. the click realizations must be monotonic a posteriori w.r.t. the click realizations. We recall that, given {a mathematical formula}vi and {a mathematical formula}vi′ with {a mathematical formula}vi′&gt;vi and called {a mathematical formula}θ=f(vi,v−i) and {a mathematical formula}θ′=f(vi′,v−i), f is monotonic in expectation w.r.t. the click realizations if and only if the CTR of ad {a mathematical formula}ai in {a mathematical formula}θ′ is not strictly smaller than the CTR in θ. The definition of monotonicity a posteriori w.r.t. the click realizations is similar. Given {a mathematical formula}vi and {a mathematical formula}vi′ with {a mathematical formula}vi′&gt;vi and called {a mathematical formula}θ=f(vi,v−i) and {a mathematical formula}θ′=f(vi′,v−i), f is monotonic a posteriori w.r.t. the click realizations if and only if the ad {a mathematical formula}ai is clicked in {a mathematical formula}θ′ whenever it would be clicked in θ. However, the authors do not present in [28] any bound over the regret (except for reporting an experimental evidence that the regret is {a mathematical formula}Ω(T23) when the CTRs are separable). In [43], the authors preliminarily extend the analysis to the case of the cascade model, showing that, even with only ad-dependent externalities, any DSIC a posteriori w.r.t. the click realizations mechanism has a regret {a mathematical formula}Θ(T).
      </paragraph>
      <paragraph>
       We summarize in Table 2 the known results in the literature and, in bold font, the original results provided in this paper. We first consider the cascade model with only position-dependent externalities analyzing the case where only the parameters {a mathematical formula}{qi}i∈N are unknown to the auctioneer. We show that it is possible to obtain a DSIC a posteriori learning mechanism with a regret {a mathematical formula}Θ˜(T23) over the auctioneer's revenue.{sup:10} Similarly, we show that in this setting, the regret over the SW is {a mathematical formula}Θ˜(T23). In Section 4.2, we consider the opposite case where only the parameters {a mathematical formula}{Λm}m∈K are unknown. We focus on mechanisms that are DSIC in expectation w.r.t. the click realizations and a posteriori w.r.t. the random component of the mechanism in Section 4.2.1, and DSIC in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations in Section 4.2.2. In the first case we observe that we can obtain a mechanism with a regret (both over the auctioneer's revenue and over the SW) of 0, but the obtained mechanism is WBB only in expectation w.r.t. the click realizations. In the second scenario, both the regrets are bounded by a constant and the mechanism is IR a posteriori and WBB in expectation w.r.t. the random component of the mechanism. In Section 4.2.3, we derive a negative result on the possibility of having no-regret DSIC a posteriori w.r.t. both sources of randomness mechanisms. Obviously, this negative result extends to all the generalizations of the cascade model with only position-dependent externalities. We conclude the analysis of the position-dependent model studying, in Section 4.3, the case where both {a mathematical formula}{Λm}m∈K and {a mathematical formula}{qi}i∈N are unknown by the auctioneer, showing that it is possible to obtain DSIC in expectation w.r.t. the random component of the mechanism and a posteriori w.r.t. the click realizations mechanisms with bounds of {a mathematical formula}O˜(T23) for both kinds of regret.
      </paragraph>
      <paragraph>
       In Section 5 we study the cascade model with both position- and ad-dependent externalities. We provide a DSIC in expectation w.r.t. the click realizations learning algorithm minimizing the regret over the auctioneer's revenue when only the parameters {a mathematical formula}{qi}i∈N are unknown.{sup:11} Then we provide a result over the SW regret, where the bound is still {a mathematical formula}Θ˜(T23). Finally, in Section 5.2, we consider other situations of lack of information obtaining negative results. More precisely, there is not any no-regret DSIC mechanism in expectation w.r.t. the click realizations and a posteriori w.r.t. realizations of the random component of the mechanism when parameters {a mathematical formula}{ci}i∈N are unknown. This result applies to both kinds of regret and it extends to the more general cascade model.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Learning with position-dependent externalities
     </section-title>
     <paragraph>
      In this section we study multi-slot auctions with only position-dependent cascade model. The CTRs depend only on the quality of the ads and on the position of the slots in which the ads are allocated. Formally, the parameters {a mathematical formula}γm,i coincide with the prominence parameter, i.e., {a mathematical formula}γm,i=λm for every {a mathematical formula}m∈K and {a mathematical formula}i∈N. As a result, the cumulative probability of observation, defined in Eq. (1), reduces to{a mathematical formula} where we use {a mathematical formula}Λm instead of {a mathematical formula}Γm(θ) for consistency with most of the literature on position-dependent externalities and to stress the difference w.r.t. the general case described in Section 3.1.
     </paragraph>
     <paragraph>
      When all the parameters are known by the auctioneer, the efficient allocation {a mathematical formula}θ⁎ greatly simplifies. In fact, the expected value of an ad {a mathematical formula}ai for an allocation θ in this case reduces to {a mathematical formula}Λπ(i;θ)qivi and, since the cumulative probabilities of observation are non-increasing over slots, the efficient allocation simply needs to allocate the slots in decreasing order of their reported values in expectation w.r.t. the qualities, i.e., {a mathematical formula}qivˆi. More precisely, for any {a mathematical formula}k∈K′, let {a mathematical formula}maxi∈N⁡(qivˆi;k) be the operator returning the k-th largest value in the set {a mathematical formula}{q1vˆ1,…,qNvˆN}, then {a mathematical formula}θ⁎ is such that, for every {a mathematical formula}m∈K′, the ad displayed at slot {a mathematical formula}sm is{a mathematical formula} This condition also simplifies the definition of the efficient allocation {a mathematical formula}θ−i⁎ when {a mathematical formula}ai is removed from {a mathematical formula}N. In fact, for any {a mathematical formula}i,j∈N, if {a mathematical formula}π(j;θ⁎)&lt;π(i;θ⁎) (i.e., ad {a mathematical formula}aj is displayed before {a mathematical formula}ai) then {a mathematical formula}π(j;θ−i⁎)=π(j;θ⁎), while if {a mathematical formula}π(j;θ⁎)&gt;π(i;θ⁎) then {a mathematical formula}π(j;θ−i⁎)=π(j;θ⁎)−1 (i.e., ad {a mathematical formula}aj is moved one slot upward), and w.l.o.g. we assume {a mathematical formula}π(i;θ−i⁎)=N. In case of position-dependent externalities, the VCG payments {a mathematical formula}pi⁎ defined in Eq. (3) take the simplified formulation:{a mathematical formula} which can be written as a per-slot payment as:{a mathematical formula} In the following sections we study the problem of designing incentive compatible mechanisms under different conditions of lack of information over the parameters {a mathematical formula}{qi}i∈N and {a mathematical formula}{Λm}m∈K. In particular, in Section 4.1, we assume that the actual values of {a mathematical formula}{qi}i∈N are unknown by the auctioneer, while those of {a mathematical formula}{Λm}m∈K are known. In Section 4.2, we assume that the actual values of {a mathematical formula}{Λm}m∈K are unknown by the auctioneer, while those of {a mathematical formula}{qi}i∈N are known. Finally, in Section 4.3, we assume that both {a mathematical formula}{qi}i∈N and {a mathematical formula}{Λm}m∈K are unknown.
     </paragraph>
     <section label="4.1">
      Unknown qualities {a mathematical formula}{qi}i∈N
      <paragraph>
       In this section we assume that the qualities of the ads {a mathematical formula}{qi}i∈N are unknown, while {a mathematical formula}{Λm}m∈K are known. We initially focus on DSIC a posteriori mechanisms and subsequently we discuss about DSIC in expectation mechanisms.
      </paragraph>
      <paragraph>
       As in [20], [21], we formalize the problem as a MAB problem and we study the properties of a learning mechanism where the exploration and exploitation phases are separated, such that during the exploration phase, we estimate the values of {a mathematical formula}{qi}i∈N and during the exploitation phase we use the estimated qualities {a mathematical formula}{q˜i}i∈N to implement a DSIC a posteriori mechanism. The pseudo code of the algorithm A-VCG1 (Adaptive VCG 1) is given in Fig. 1. The details of the algorithm follow.
      </paragraph>
      <section>
       <section>
        <section-title>
         Exploration phase
        </section-title>
        <paragraph>
         During an exploration phase of length τ, the algorithm receives as input the parameters {a mathematical formula}{Λm}m∈K and collects data to estimate the quality of each ad. Unlike the single-slot case, where we collect only one sample of no-click/click event per step, here we can exploit the fact that each ad {a mathematical formula}ai has a non-zero CTR whenever it is allocated to a slot {a mathematical formula}sm with {a mathematical formula}m≤K. As a result, at each step of the exploration phase, we collect K samples (no-click/click events), one from each slot. Let {a mathematical formula}θt (for {a mathematical formula}1≤t≤τ) be a sequence of allocations independent from the advertisers' bids. Let {a mathematical formula}Bi={t:π(i;θt)≤K,1≤t≤τ} be the set of all the steps when {a mathematical formula}ai is allocated to a valid slot, so that {a mathematical formula}|Bi| corresponds to the total number of (no-click/click) samples available for ad {a mathematical formula}ai. We denote by {a mathematical formula}clickπ(i;θt)i(t)∈{0,1} the no-click/click event at step t for ad {a mathematical formula}ai when displayed in slot {a mathematical formula}sπ(i;θt). Depending on the slot in which the click event happens, the ad {a mathematical formula}ai has different CTR, thus we need to weigh each click sample by the probability of observation {a mathematical formula}Λm related to the slot in which the ad is allocated. As a result, the estimated quality {a mathematical formula}q˜i is computed as{a mathematical formula} Since {a mathematical formula}q˜i is an unbiased estimate of {a mathematical formula}qi (i.e., {a mathematical formula}Eclick[q˜i]=qi, where {a mathematical formula}Eclick is the expectation w.r.t. the click realizations), we can resort to the Hoeffding's inequality [44] and a bound over the error of the estimated quality {a mathematical formula}q˜i for each ad {a mathematical formula}ai.
        </paragraph>
        <paragraph label="Proposition 1">
         For any ad{a mathematical formula}ai,{a mathematical formula}i∈N{a mathematical formula}with probability{a mathematical formula}1−δ(w.r.t. the click realizations).
        </paragraph>
        <paragraph>
         During the exploration phase, at each step {a mathematical formula}t∈{1,…,τ}, we adopt the following sequence of allocations{a mathematical formula} thus obtaining {a mathematical formula}|Bi|=⌊Kτ/N⌋ for all the ads {a mathematical formula}ai. Given that {a mathematical formula}⌊Kτ/N⌋≥τK2N, Eq. (12) becomes{a mathematical formula} where η represents the accuracy of the estimator.{sup:12} The previous inequality is non-trivial only for a long enough exploration phase. In particular, to have a meaningful bound, i.e., {a mathematical formula}|qi−q˜i|&lt;1, the length of the exploration phase has to be {a mathematical formula}τ&gt;(∑m=1K1Λm2)NK2log⁡2Nδ. During this phase, in order to guarantee DSIC a posteriori, the advertisers cannot be charged with any payment, i.e., all the payments in steps {a mathematical formula}1≤t≤τ are set to 0. In fact, as shown in [21], any bid-dependent payment could be easily manipulated by bidders, thus obtaining a non-truthful mechanism, whereas bid-independent payments could lead to a non-IR mechanism to which bidders may prefer not to participate.
        </paragraph>
       </section>
       <section>
        <section-title>
         Exploitation phase
        </section-title>
        <paragraph>
         Once the exploration phase is terminated, an upper-confidence bound over each quality {a mathematical formula}qi is computed as{a mathematical formula} and the exploitation phase is started and run for the remaining {a mathematical formula}T−τ steps. We define the upper-confidence bound on the SW as{a mathematical formula} and we define {a mathematical formula}f˜ as the allocation function that displays ads in decreasing order of {a mathematical formula}q˜i+vˆi. Thus {a mathematical formula}f˜ returns the efficient allocation {a mathematical formula}θ˜ on the basis of the estimated qualities as:{a mathematical formula} The allocation function {a mathematical formula}f˜ is then run for all the steps of the exploitation phase. Notice that {a mathematical formula}f˜ is an affine maximizer, since{a mathematical formula} where each weight {a mathematical formula}wi=q˜i+/qi is independent of the advertisers' types {a mathematical formula}vi. Hence, we can apply the WVCG payments (here denoted by {a mathematical formula}p˜ because of the estimated parameters) satisfying the DSIC a posteriori property. In particular, for any {a mathematical formula}ai, we define the payment{a mathematical formula} Although these payments cannot be computed by the auctioneer, since the actual {a mathematical formula}{qi}i∈N are unknown, we can resort to the pay-per-click payments{a mathematical formula} which in expectation coincide with the payments {a mathematical formula}p˜i(vˆ)=E[p˜ic(vˆ,clickπ(i;θ˜)i)] and can be computed at run time. Unlike the payments {a mathematical formula}p˜i(vˆ), these payments can be computed simply relying on the estimates {a mathematical formula}q˜i+ and on the knowledge of the probabilities of observation {a mathematical formula}Λm. The following properties hold for this mechanism.
        </paragraph>
        <paragraph label="Theorem 1">
         The A-VCG1 is:
        </paragraph>
        <list>
         <list-item label="•">
          DSIC a posteriori,
         </list-item>
         <list-item label="•">
          IR a posteriori,
         </list-item>
         <list-item label="•">
          WBB a posteriori.
         </list-item>
        </list>
        <paragraph label="Proof">
         The allocation function is monotonic a posteriori w.r.t. the click realizations since, by the nature of the externality model, each click realization plan prescribing that an ad is clicked in a given slot prescribes also that the same ad would be clicked in all the slots above. Thus, DSIC a posteriori trivially follows from the fact that the mechanism is a WVCG mechanism and that the payments are pay-per-click. □
        </paragraph>
        <paragraph>
         We now move to the analysis of the performance of A-VCG1 in terms of the regret the mechanism accumulates through T steps.
        </paragraph>
        <paragraph label="Theorem 2">
         Let us consider a sequential auction with N advertisers, K slots, and T steps with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1Kand accuracy η as defined in Eq.(14). For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG1 achieves auctioneer's revenue expected regret:{a mathematical formula}By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}δ=K−13T−13N13
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=K−13T23N13Λmin−23[log⁡(K13T13N23)]13,
         </list-item>
        </list>
        <paragraph>
         We initially introduce some remarks about the above results, and subsequently discuss the proof of the theorem, which can be found in Appendix C.
        </paragraph>
        <paragraph label="Remark 1">
         The boundUp to numerical constants and logarithmic factors, the bound in Eq. (20) is {a mathematical formula}RT=O˜(K23T23N13). We first notice that A-VCG1 is a no-regret algorithm since its per-step regret ({a mathematical formula}RT/T) decreases to 0 as {a mathematical formula}T−13, thus implying that it asymptotically achieves the same performance as the VCG. Furthermore, we notice that for {a mathematical formula}K=1 the bound reduces (up to constants) to the single-slot case analyzed in [20]. Unlike the standard bound for MAB algorithms, the regret scales as {a mathematical formula}O˜(T23) instead of {a mathematical formula}O˜(T12). As pointed out in [20] and [21] this is the unavoidable price the bandit algorithm has to pay to be DSIC a posteriori w.r.t. the realizations of the random component of a mechanism. Finally, the dependence of the regret on N is sub-linear ({a mathematical formula}N13) and therefore increasing the number of advertisers does not significantly worsen the regret. The dependency on the number of slots K is similar: according to the bound in Eq. (20) the regret has a sublinear dependency {a mathematical formula}O˜(K23), meaning that whenever one slot is added to the auction, the performance of the algorithm does not significantly worsen. By analyzing the difference between the payments of the VCG and A-VCG1, we notice that during the exploration phase the regret is {a mathematical formula}O(τK) (e.g., if all the ads allocated into the K slots are clicked at each explorative step), while during the exploitation phase the error in estimating the qualities sum over all the K slots, thus suggesting a linear dependency on K for this phase as well. Nonetheless, as K increases, the number of samples available per-ad increases as {a mathematical formula}τK/N, thus improving the accuracy of the quality estimates by {a mathematical formula}O˜(K−12) (see Proposition 1). As a result, as K increases, the exploration phase can be shortened (the optimal τ actually decreases as {a mathematical formula}K−13), thus reducing the regret during the exploration, and still have accurate enough estimates to control the regret of the exploitation phase.
        </paragraph>
        <paragraph label="Remark 2">
         Distribution-free boundThe bound derived in Theorem 2 is a distribution-free (or worst-case) bound, since it holds for any set of advertisers (i.e., for any {a mathematical formula}{qi}i∈N and {a mathematical formula}{vi}i∈N). This generality comes at the price that, as illustrated in other remarks and in the numerical simulations (see Section 6), the bound could be inaccurate for some specific sets of advertisers. On the other hand, distribution-dependent bounds (see e.g., the bounds of UCB [42]), where q and v appear explicitly, would be more accurate in predicting the behavior of the algorithm. Nonetheless, they could not be used to optimize the parameters δ and τ, since they would then depend on unknown quantities.
        </paragraph>
        <paragraph label="Remark 3">
         ParametersThe choice of parameters τ and δ reported in Theorem 2 is obtained by a rough minimization of the upper-bound in Eq. (19). Each parameter can be computed by knowing the characteristics of the auction (number of steps T, number of slots K, number of ads N, and {a mathematical formula}Λm). Moreover, since the values are obtained optimizing an upper-bound of the regret and not directly the true cumulative regret, these values can provide a good guess for the parametrization, but they might not be optimal. In practice, we expect that the regret could be optimized by searching the space of the parameters around the values suggested in Theorem 2.
        </paragraph>
        <paragraph label="Remark 4">
         DSIC in expectationIn this paper, we do not solve two interesting problems when DSIC in expectation w.r.t. the realizations of the random component of the mechanism is adopted: (i) whether it is possible or not to avoid the separation of the exploration and exploitation phases and (ii) whether it is possible to obtain a regret of {a mathematical formula}O˜(T12) as in the case of {a mathematical formula}K=1[23]. Any attempt we tried to extend the result presented in [23] to the multi-slot case led to a non-IC mechanism. We briefly provide some examples of adaptation to our framework of the two MAB presented in [23]. None of these attempts provided a monotonic allocation function. We tried to extend the UCB1 in different ways, e.g., by introducing {a mathematical formula}N⋅K estimators, one for each ad for each slot, or maintaining N estimators weighing in different ways clicks obtained in different slots. The second MAB algorithm, called NewCB, is based on the definition of a set of active ads, i.e., the ones that can be displayed in the unique slot. We considered some extensions for the multi-slot setting (e.g., a single set for all the slots and multiple sets, one for each slot) without identifying monotonic allocation algorithms.
        </paragraph>
        <paragraph>
         Comments to the proof. The proof uses relatively standard arguments to bound the regret of the exploitation phase. As discussed in Remark 2, the bound is distribution-free and some steps in the proof are conservative upper-bounds on quantities that might be smaller for specific auctions. For instance, the inverse dependency on the smallest cumulative discount factor {a mathematical formula}Λmin in the final bound could be a quite inaccurate upper-bound on the quantity {a mathematical formula}∑m=1K1/Λm2. In fact, the parameter τ itself could be optimized as a direct function of {a mathematical formula}∑m=1K1/Λm2, thus obtaining a more accurate tuning of the length of the exploration phase and a slightly tighter bound (in terms of constant terms). Furthermore, a crucial step in the proof is the inequality {a mathematical formula}maxi∈N⁡(q˜i+vi;h)/maxi∈N⁡(q˜i+vi;m)≤1, which is likely to become less accurate as the difference between h and m increases (see Eq. (C.4) in the proof). For instance, if the qualities {a mathematical formula}qi are drawn from a uniform distribution in {a mathematical formula}(0,1), as the number of slots increases this quantity reduces as well (on average), thus making the upper-bound by 1 less and less accurate. The accuracy of the proof and the corresponding bound are further studied in the simulations in Section 6.
        </paragraph>
        <paragraph>
         Besides a bound on the revenue regret, in a similar way we can bound the SW, as in [23]. In particular, we obtain that A-VCG1 is a no-regret algorithm and {a mathematical formula}RTSW=O˜(T23).
        </paragraph>
        <paragraph label="Theorem 3">
         Let us consider a sequential auction with N advertisers, K slots, and T steps with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1Kand accuracy η as defined in Eq.(14). For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG1 achieves a SW regret:{a mathematical formula}By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}δ=(1Λmin)23K−13T−13N13
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=(1Λmin)23K−13T23N13(log⁡2Λmin23K13T13N23)13,
         </list-item>
        </list>
        <paragraph>
         Notice that using τ and δ defined in Theorem 2, the bound for {a mathematical formula}RTSW is {a mathematical formula}O˜(T23), even if the parameters are not optimal for this second framework.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="4.2">
      Unknown {a mathematical formula}{Λm}m∈K
      <paragraph>
       We now focus on the situation when the auctioneer knows {a mathematical formula}{qi}i∈N, while {a mathematical formula}{Λm}m∈K are unknown. By definition of cascade model, {a mathematical formula}{Λm}m∈K are strictly non-increasing in m. This dramatically simplifies the allocation problem since the optimal allocation can be found without knowing the actual values of {a mathematical formula}{Λm}m∈K. Indeed, the allocation {a mathematical formula}θ⁎ such that {a mathematical formula}α(m;θ⁎)∈arg⁡maxi∈N⁡(qivˆi;m),∀m∈K, is optimal for any possible {a mathematical formula}{Λm}m∈K. However, the lack of knowledge about {a mathematical formula}{Λm}m∈K makes the design of a truthful mechanism non-trivial because the cumulative probabilities of observation appear in the calculation of the payments. In the following, we initially focus on DSIC in expectation mechanisms, providing two mechanisms, the first DSIC in expectation w.r.t. the click realizations and the second DSIC in expectation w.r.t. the realizations of the random component of the mechanism, and finally we discuss about DSIC a posteriori mechanisms.
      </paragraph>
      <section label="4.2.1">
       <section-title>
        DSIC in expectation w.r.t. the click realizations mechanism
       </section-title>
       <paragraph>
        In this case, we do not need to estimate the parameters {a mathematical formula}{Λm}m∈K and therefore we do not resort to the MAB framework to solve any exploration-exploitation dilemma. The pseudocode of the algorithm A-VCG2 (Adaptive VCG2) is given in Fig. 2. On the basis of the above considerations, we can adopt the allocatively efficient allocation function {a mathematical formula}f⁎ as prescribed by Eq. (8) even if the mechanism does not know the actual values of the parameters {a mathematical formula}{Λm}m∈K. Nonetheless, the VCG payments defined in Eq. (9) cannot be computed, since {a mathematical formula}{Λm}m∈K are unknown. However, by resorting to execution-contingent payments (generalizing the pay-per-click approach), we can impose computable payments that, in expectation, are equal to Eq. (9).{sup:13} More precisely, the contingent payments are computed given the bids {a mathematical formula}vˆ and all click events over the slots and take the form:{a mathematical formula} Notice that the payment {a mathematical formula}pic depends not only on the click of ad {a mathematical formula}ai, but also on the clicks of all the ads displayed below {a mathematical formula}ai. In expectation, the two terms of {a mathematical formula}pic are:{a mathematical formula}{a mathematical formula} and therefore, in expectation, the payment equals those defined in Eq. (9). We discuss the properties of the mechanism in what follows.
       </paragraph>
       <paragraph label="Proposition 2">
        The A-VCG2 is IR a posteriori.
       </paragraph>
       <paragraph label="Proof">
        Rename the ads {a mathematical formula}{a1,…,aN} such that {a mathematical formula}q1v1≥q2v2≥…≥qNvN. We can write payments in Eq. (23) as:{a mathematical formula} Thus, the utility for advertiser {a mathematical formula}ai is:{a mathematical formula} Since {a mathematical formula}clickjjqj≥0 by definition and {a mathematical formula}qjvj−qj+1vj+1≥0 because of the chosen ordering of the ads, then the utility is always positive and we can conclude that the mechanism is IR a posteriori.  □
       </paragraph>
       <paragraph label="Theorem 4">
        The A-VCG2 is:
       </paragraph>
       <list>
        <list-item label="•">
         DSIC in expectation w.r.t. the click realizations,
        </list-item>
        <list-item label="•">
         IR a posteriori,
        </list-item>
        <list-item label="•">
         WBB in expectation w.r.t. the click realizations,
        </list-item>
        <list-item label="•">
         AE.
        </list-item>
       </list>
       <paragraph label="Proof">
        It trivially follows from the fact that the allocation function is AE and the payments in expectation equal the VCG ones and by Proposition 2.  □
       </paragraph>
       <paragraph label="Proposition 3">
        The A-VCG2 is not DSIC a posteriori (w.r.t. the click realizations).
       </paragraph>
       <paragraph label="Proof">
        The proof is by counterexample. Consider an environment with 3 ads {a mathematical formula}N={1,2,3} and 2 slots {a mathematical formula}K={1,2} s.t. {a mathematical formula}q1=0.5, {a mathematical formula}v1=4, {a mathematical formula}q2=1, {a mathematical formula}v2=1, {a mathematical formula}q3=1, {a mathematical formula}v3=0.5, which correspond to expected values of 2, 1, and 0.5.The optimal allocation {a mathematical formula}θ⁎ consists in allocating {a mathematical formula}a1 in {a mathematical formula}s1 and {a mathematical formula}a2 in {a mathematical formula}s2. Consider a step t when both ad {a mathematical formula}a1 and {a mathematical formula}a2 are clicked, from Eq. (23) we have that the payment of {a mathematical formula}a2 is:{a mathematical formula} If ad {a mathematical formula}a2 reports a value {a mathematical formula}vˆ2=3, the optimal allocation is now {a mathematical formula}a2 in {a mathematical formula}s1 e {a mathematical formula}a1 in {a mathematical formula}s2. In the case both {a mathematical formula}a1 and {a mathematical formula}a2 are clicked, the payment of {a mathematical formula}a2 is:{a mathematical formula} Given that, in both cases, the utility is {a mathematical formula}u2=v2−p2c(vˆ,{clickmα(m;θ⁎)}m=1K), reporting a non-truthful value is optimal. Thus, we can conclude that the mechanism is not DSIC a posteriori w.r.t. the click realizations.  □.
       </paragraph>
       <paragraph label="Proposition 4">
        The A-VCG2 is not WBB a posteriori (w.r.t. the click realizations).
       </paragraph>
       <paragraph label="Proof">
        The proof is by counterexample. Consider an environment with 3 ads {a mathematical formula}N={1,2,3} and 2 slots {a mathematical formula}K={1,2} s.t. {a mathematical formula}q1=1, {a mathematical formula}v1=2, {a mathematical formula}q2=0.5, {a mathematical formula}v2=1, {a mathematical formula}q3=1, {a mathematical formula}v3=0.1.The optimal allocation {a mathematical formula}θ⁎ consists in allocating {a mathematical formula}a1 in {a mathematical formula}s1 e {a mathematical formula}a2 in {a mathematical formula}s2. Consider step t when both ad {a mathematical formula}a1 and {a mathematical formula}a2 are clicked, their payments are:{a mathematical formula}{a mathematical formula}Thus, {a mathematical formula}∑i=13pic(v,{clickmα(m;θ⁎)}m=1K)=0.4−0.5&lt;0, and we can conclude that the mechanism is not WBB a posteriori. □
       </paragraph>
       <paragraph>
        Now we state the following theorem, whose proof is straightforward.
       </paragraph>
       <paragraph label="Theorem 5">
        Let us consider a sequential auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K. The A-VCG2 achieves an auctioneer's revenue expected regret{a mathematical formula}RT=0.
       </paragraph>
       <paragraph>
        An important property of this mechanism is that the expected payments are exactly the VCG payments for the optimal allocation when all the parameters are known. Moreover, the absence of an exploration phase allows us to obtain a per-step expected regret of zero and, thus, the cumulative regret over the T steps of auction is {a mathematical formula}RT=0. Similar considerations can be applied to the study of the regret over the SW, obtaining the following.
       </paragraph>
       <paragraph label="Corollary 1">
        Let us consider a sequential auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K. The A-VCG2 achieves an SW regret{a mathematical formula}RTSW=0.
       </paragraph>
      </section>
      <section label="4.2.2">
       <section-title>
        DSIC in expectation w.r.t. the realizations of the random component mechanisms
       </section-title>
       <paragraph>
        As for the previous mechanism, also in this case we only need an exploitation phase. Unlike A-VCG2, in this case we need to follow a similar approach as in [23] and introduce a random component, which leads to the mechanism, called A-{a mathematical formula}VCG2′ reported in Fig. 3.
       </paragraph>
       <paragraph>
        Since {a mathematical formula}f⁎ is monotonic (see Appendix B) and the problem is with single parameter and linear utilities, payments that guarantee DSIC in expectation w.r.t. the click realizations can be written as Myerson payments:{a mathematical formula} which coincide with the VCG payments defined in Eq. (3) (hence the use of the same notation {a mathematical formula}pi⁎). This is justified by the fact that when a mechanism is AE, IR in expectation w.r.t. the click realizations and WBB in expectation w.r.t. the click realizations the only payments that lead to a DSIC in expectation w.r.t. the click realizations mechanism are the VCG payments with Clacke's pivot [45], and thus Eq. (24) coincides with Eq. (3). However, these payments are not directly computable, since the parameters {a mathematical formula}{Λm}m∈K in the integral are unknown and, as in the case discussed in Section 4.2.1, we cannot replace them by empirical estimates. Nonetheless, we could obtain these payments in expectation by using execution-contingent payments associated with non-optimal allocations where the report {a mathematical formula}vˆi is randomly modified in an interval between 0 and the actual value. This can be obtained by resorting to the approach proposed in [23], which takes as input a generic allocation function f and introduces a randomized component to it, thus producing a new (random) allocation function that we denote by {a mathematical formula}f′. At the cost of reducing the efficiency of the mechanism, this technique allows the computation of the allocation and the payments at the same time, even when payments described in [35] cannot be directly computed.
       </paragraph>
       <paragraph>
        In A-{a mathematical formula}VCG2′, we apply this approach to {a mathematical formula}f⁎, thus obtaining a new allocation function {a mathematical formula}f⁎′. With {a mathematical formula}f⁎′, the advertisers' reported values {a mathematical formula}{vˆi}i∈N are modified, each with a (small) probability {a mathematical formula}μ∈(0,1). The (potentially) modified values are then used to compute the allocation (using {a mathematical formula}f⁎) and the payments. More precisely, with a probability of {a mathematical formula}(1−μ)N, {a mathematical formula}f⁎′ returns the same allocation as {a mathematical formula}f⁎, while it defines a different allocation with probability of {a mathematical formula}1−(1−μ)N. The reported values {a mathematical formula}{vˆi}i∈N are modified through the canonical Self-Resampling Procedure (cSRP) described in [23] that generates two samples: {a mathematical formula}xi(vˆi,ωi) and {a mathematical formula}yi(vˆi,ωi), where {a mathematical formula}ωi is the random seed. We sketch the result of cSRP where the function ‘rec’ is defined in [23]:{a mathematical formula} where {a mathematical formula}vˆi′∼U([0,vˆi]) and {a mathematical formula}vˆi″=rec(vˆi′). The algorithm in Fig. 4 shows how {a mathematical formula}f⁎′ works when the original allocation function is {a mathematical formula}f⁎. The reported values {a mathematical formula}{vˆi}i∈N are perturbed through the cSRP (Step 2) and then the allocation is chosen by applying the original allocation function {a mathematical formula}f⁎ to the new values x (Step 4). Finally, the payments are computed as{a mathematical formula} where{a mathematical formula} with {a mathematical formula}y=(y1,…,yN). If we take the expectation of the payments in Eq. (25) w.r.t. the randomization of the mechanism, then we obtain exactly the same form of payments as in Eq. (24) but instantiated for the randomized allocation function {a mathematical formula}f⁎′ (for the explicit equation refer to Eq. (E.1) in Appendix E). Furthermore, the resulting mechanism is shown to be DSIC in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations. As a result we obtained the following properties.
       </paragraph>
       <paragraph label="Theorem 6">
        The A-{a mathematical formula}VCG2′is:
       </paragraph>
       <list>
        <list-item label="•">
         DSIC in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations,
        </list-item>
        <list-item label="•">
         IR a posteriori,
        </list-item>
        <list-item label="•">
         WBB in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations.
        </list-item>
       </list>
       <paragraph>
        We also obtain the following regret guarantees.
       </paragraph>
       <paragraph label="Theorem 7">
        Let us consider an auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K. The A-{a mathematical formula}VCG2′achieves an auctioneer's revenue expected regret{a mathematical formula}RT≤2K2μvmaxT.
       </paragraph>
       <paragraph>
        If we tune the randomization parameter as {a mathematical formula}μ=1K2T, then we obtain {a mathematical formula}RT=O(1). Notice that μ cannot be just set to zero, since it would lead to a division by zero in Eq. (25). Furthermore, as illustrated in Section 6, an undesirable effect of a small μ is the corresponding increase in the variance in the payments. Thus a proper trade-off should be found when tuning μ in practice. We provide a similar result for the regret over the SW.
       </paragraph>
       <paragraph label="Theorem 8">
        Let us consider a sequential auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K. The A-{a mathematical formula}VCG2′achieves a SW regret{a mathematical formula}RTSW≤K2μvmaxT.
       </paragraph>
      </section>
      <section label="4.2.3">
       Discussion about DSIC a posteriori mechanisms
       <paragraph>
        One may wonder whether there exists a no-regret DSIC a posteriori mechanism, even at the cost of a worse regret. Resorting to the same arguments used in [28], we show that the answer to such question is negative.
       </paragraph>
       <paragraph label="Theorem 9">
        Let us consider a sequential auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1Kwhose value are unknown. Any online learning mechanism that is DSIC a posteriori achieves an auctioneer's revenue expected regret{a mathematical formula}RTof{a mathematical formula}Θ(T).
       </paragraph>
       <paragraph label="Proof (sketch)">
        Basically, the A-VCG2 mechanism is DSIC in expectation w.r.t. the click realizations because it adopts execution-contingent payments in which the payment of advertiser {a mathematical formula}ai depends also on the clicks over ads other than {a mathematical formula}ai, while A-{a mathematical formula}VCG2′ is DSIC in expectation w.r.t. the realization of the random component of the mechanism because it adopts implicit payments. In order to have DSIC a posteriori, we need payments {a mathematical formula}pi that are deterministic w.r.t. the click realizations over other ads other than {a mathematical formula}ai (i.e., pay-per-click payments are needed) and deterministic w.r.t. any realization of the random component of the mechanism.We notice that even if {a mathematical formula}{Λm}m∈K have been estimated (e.g., in an exploitation phase), we cannot have payments leading to DSIC a posteriori. Indeed, with estimates {a mathematical formula}{Λ˜m}m∈K, the allocation function maximizing {a mathematical formula}SW˜ (computed with {a mathematical formula}Λ˜m) is not an affine maximizer and therefore the adoption of WVCG mechanism would not guarantee DSIC, not even in expectation. As a result, only mechanisms with payments defined in Eq. (24) can be used. However, these payments, if computed exactly (and not estimated in expectation), as required to have DSIC a posteriori, require the knowledge about the actual {a mathematical formula}Λm related to each slot {a mathematical formula}sm in which an ad can be allocated for each report {a mathematical formula}vˆ≤v.To prove the theorem, we provide a characterization of DSIC a posteriori mechanisms. More precisely, we need a monotonic allocation function and the payments defined in Eq. (24). As mentioned above, these payments require the knowledge about the actual {a mathematical formula}Λm related to the slot {a mathematical formula}sm in which an ad can be allocated for any report {a mathematical formula}vˆ≤v. Thus we have two possibilities:
       </paragraph>
       <list>
        <list-item label="•">
         In the first case, the ads are partitioned and each partition is associated with a single slot and the ad with the largest expected valuation is chosen at each slot independently. In other words, an ad can be allocated only in one given specific slot and its report determines only whether it is displayed or not (and not where). This case is equivalent to multiple separate-single slot auctions and therefore each auction is DSIC a posteriori as shown in [20]. However, as shown in [28], this mechanism would have a regret {a mathematical formula}Θ(T).
        </list-item>
        <list-item label="•">
         In the second case, the ads are partitioned and each partition is associated with multiple slots and for each partition an auction is carried out to determine the allocation over each slot. In other words, an ad can be allocated in one of a given set of slots (associated with its partition) on the basis of its report. In this case, to compute the payments, it would be necessary to know the exact CTR of the ad for each possible slot, but this is possible only in expectation either by using the above execution-contingent mechanism, as we do in Section 4.2.1, or by using a random component in the mechanism, as we do in Section 4.2.2. However, in both these case we would not obtain DSIC a posteriori.
        </list-item>
       </list>
      </section>
     </section>
     <section label="4.3">
      Unknown {a mathematical formula}{Λm}m∈K and {a mathematical formula}{qi}i∈N
      <paragraph>
       In this section we study the situation in which both {a mathematical formula}{qi}i∈N and {a mathematical formula}{Λm}m∈K are unknown. From the results derived in the previous section, we know that adopting DSIC a posteriori leads to {a mathematical formula}RT=Θ(T). Thus, we will only focus on DSIC in expectation.
      </paragraph>
      <paragraph>
       First of all, we remark that the mechanisms presented in Section 4.1 and 4.2 cannot be adopted here and a new mechanism is needed. By combining A-VCG1 and A-{a mathematical formula}VCG2′, we obtain the algorithm A-VCG3 (Adaptive VCG3) illustrated in Fig. 5. As in the case when only the qualities {a mathematical formula}{qi}i∈N are unknown, we formalize the problem as a MAB where the exploration and exploitation phases are separate and where, during the exploration phase, we estimate the values of {a mathematical formula}{qi}i∈N.
      </paragraph>
      <section>
       <section>
        <section-title>
         Exploration phase
        </section-title>
        <paragraph>
         During the first τ steps, estimates of {a mathematical formula}{qi}i∈N are computed. We use the same exploration policy of Section 4.1, but the estimates are computed just using samples from the first slot, since {a mathematical formula}Λm with {a mathematical formula}m&gt;1 are unknown.{sup:14} Define {a mathematical formula}Bi={t:π(i;θt)=1,1≤t≤τ} the set of steps where {a mathematical formula}ai is displayed in the first slot, the number of samples collected for {a mathematical formula}ai is {a mathematical formula}|Bi|=⌊τN⌋≥τ2N.{sup:15} The estimated value of {a mathematical formula}qi is:{a mathematical formula} such that {a mathematical formula}q˜i is an unbiased estimate of {a mathematical formula}qi (i.e., {a mathematical formula}Eclick[q˜i]=qi). By applying the Hoeffding's inequality we obtain an upper bound over the error of the estimated quality {a mathematical formula}q˜i for each ad {a mathematical formula}ai.
        </paragraph>
        <paragraph label="Proposition 5">
         For any ad{a mathematical formula}{ai}i∈N{a mathematical formula}with probability{a mathematical formula}1−δ(w.r.t. the click realizations).
        </paragraph>
        <paragraph>
         In this case, in order to have a meaningful bound, i.e., {a mathematical formula}|qi−q˜i|&lt;1, the length of the exploration phase has to be {a mathematical formula}τ&gt;Nlog⁡2Nδ. After the exploration phase, an upper-confidence bound over each quality is computed as {a mathematical formula}q˜i+=q˜i+η.
        </paragraph>
       </section>
       <section>
        <section-title>
         Exploitation phase
        </section-title>
        <paragraph>
         We first focus on the allocation function. During the exploitation phase we want to use an allocation {a mathematical formula}θ˜=f˜(vˆ) maximizing the estimated SW with estimated {a mathematical formula}{q˜i+}i∈N and the parameters {a mathematical formula}{Λm}m∈K. Since the actual parameters {a mathematical formula}{Λm}m∈K are monotonically non-increasing, {a mathematical formula}θ˜ is defined as an allocation {a mathematical formula}{〈sm,aα(m;θ˜)〉}m∈K′, where{a mathematical formula}
        </paragraph>
        <paragraph label="Theorem 10">
         We now focus on payments. Allocation function {a mathematical formula}f˜ is an affine maximizer (due to weights depending on {a mathematical formula}q˜i as in Section 4.1), but WVCG payments cannot be computed given that parameters {a mathematical formula}{Λm}m∈K are unknown. Neither the adoption of execution-contingent payments, like in Eq. (23), is allowed, given that {a mathematical formula}qi is unknown and only estimates {a mathematical formula}q˜i are available. Thus, we resort to implicit payments as in Section 4.2.2. More precisely, we use the same exploitation phase adopted in Section 4.2.2, except that we use {a mathematical formula}f˜ in place of {a mathematical formula}f⁎. In this case, we have that the per-click payments are:{a mathematical formula} where{a mathematical formula} We can state the following. The A-VCG3 is:
        </paragraph>
        <list>
         <list-item label="•">
          DSIC in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations,
         </list-item>
         <list-item label="•">
          IR a posteriori,
         </list-item>
         <list-item label="•">
          WBB in expectation w.r.t. the realizations of the random component of the mechanism and a posteriori w.r.t. the click realizations.
         </list-item>
        </list>
        <paragraph label="Proof">
         The proof of DSIC in expectation and WBB in expectation easily follows from the definition of the adopted mechanism as discussed in [23]. The proof of IR a posteriori is similar to the proof of Proposition 2. The fact that the properties hold a posteriori w.r.t. the click realizations follows from [23]. □
        </paragraph>
        <paragraph>
         Now we want to analyze the performance of the mechanism in terms of the regret accumulated through T steps. Notice that in this case we have to focus on two different potential sources of regret: the adoption of a sub-optimal (randomized) allocation function and the estimation of the unknown parameters.
        </paragraph>
        <paragraph label="Theorem 11">
         Let us consider a sequential auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K, accuracy η as defined in Eq.(27)and parameter{a mathematical formula}μ∈(0,1]. For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG3 achieves an auctioneer's revenue expected regret:{a mathematical formula}By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}μ=T−13N−23,
         </list-item>
         <list-item label="•">
          {a mathematical formula}δ=T−13N13,
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=T23N13(log⁡2Nδ)13,
         </list-item>
        </list>
        <paragraph label="Remark 1">
         The boundUp to numerical constants and logarithmic factors, the previous bound on {a mathematical formula}RT=O˜(T23KN13). We first notice that also in this case we match the lowest possible regret w.r.t. T when exploration and exploitation phases are separate. As a result, the proposed mechanism is a no-regret algorithm and it asymptotically approaches the performance of the VCG (when all the parameter are known). Compared to the results in Section 4.1, the dependency of the regret on K increased by a factor {a mathematical formula}K13 and it is now linear. This is a direct consequence of the exploration phase. In fact, here we cannot take advantage of the samples collected over all the slots, and the qualities are estimated only using samples observed in the first slot. On the other hand, the dependency on N is the same as in Section 4.1.
        </paragraph>
        <paragraph label="Remark 3">
         Non-separate phases and {a mathematical formula}O˜(T12)The questions whether it is possible to avoid separating exploration and exploitation and preserve DSIC in expectation (in some form) and whether it is possible to obtain a regret of {a mathematical formula}O˜(T12) are open.Using samples from multiple slotsAn important issue is whether it is possible to exploit samples from the slots below the first one to improve the accuracy of the estimates and reduce the length of the exploration phase. The critical issue here is that the samples from slots below the first are drawn from a Bernoulli distribution with parameter obtained by the product of {a mathematical formula}Λm and {a mathematical formula}qi, and it is not trivial to find a method to use these samples to improve the estimates. However, we notice that the exploitation of these additional samples would correspond to a reduction of the regret bound of at most {a mathematical formula}K13, given that the dependency from K cannot be better than in the case discussed in Section 4.1 (i.e., {a mathematical formula}O(K23)).
        </paragraph>
        <paragraph>
         We can also prove an upper-bound for the regret for the SW of A-VCG3.
        </paragraph>
        <paragraph label="Theorem 12">
         Let us consider an auction with N advertisers, K slots, and T steps, with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1K, accuracy η as defined in Eq.(27)and parameter{a mathematical formula}μ∈(0,1]. For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG3 achieves a SW regret:{a mathematical formula}By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}μ=K−1T−13N13,
         </list-item>
         <list-item label="•">
          {a mathematical formula}δ=T−13N13,
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=T23N13(log⁡2Nδ)13,
         </list-item>
        </list>
        <paragraph>
         Also in this case we obtain a regret on the SW {a mathematical formula}RTSW=O˜(T23).
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Learning with position- and ad-dependent externalities
     </section-title>
     <paragraph>
      In this section we deal with the general model in Eq. (1), where both position- and ad-dependent externalities are present and we provide several partial results. In Section 5.1, we analyze the problem of designing a DSIC a posteriori mechanism when only the qualities of the ads are unknown, while in Section 5.2 we highlight some problems that rise when also continuation probabilities are uncertain.
     </paragraph>
     <section label="5.1">
      Unknown qualities {a mathematical formula}{qi}i∈N
      <paragraph>
       We first focus on the problem where the only unknown parameters are the qualities {a mathematical formula}{qi}i∈N of the ads and the externality model includes position- and ad-dependent externalities. We focus on DSIC in expectation w.r.t. the click realizations, since there is not any no-regret mechanism that is DSIC a posteriori w.r.t. the click realizations [43], and we study MAB algorithms that separate the exploration and exploitation phases. The structure of the mechanism we propose, called A-VCG4, is similar to the A-VCG1 and is reported in Fig. 6.
      </paragraph>
      <section>
       <section>
        <section-title>
         Exploration phase
        </section-title>
        <paragraph>
         At each step of the exploration phase of length τ, we collect K samples of no-click/click events. Given a generic exploration policy {a mathematical formula}{θt}t=1τ, the estimated quality {a mathematical formula}q˜i is computed as:{a mathematical formula} where {a mathematical formula}Bi={t:π(i;θt)≤K,1≤t≤τ}. Since the explorative allocations {a mathematical formula}θt impact on the cumulative probabilities of observation {a mathematical formula}Γm(θt), we use a variation of Proposition 1 in which Eq. (12) is replaced by:{a mathematical formula} For each exploration policy such that {a mathematical formula}|Bi|=⌊KτN⌋≥Kτ2N for any {a mathematical formula}i∈N (e.g., the policy defined in Eq. (13)), we redefine η as{a mathematical formula} where {a mathematical formula}Γmin=minθ∈Θ,m∈K⁡{Γm(θ)}. In this case, in order to have a meaningful bound, i.e., {a mathematical formula}|qi−q˜i|&lt;1, the length of the exploration phase has to be {a mathematical formula}τ&gt;1Γmin2NKlog⁡2Nδ. We define the upper-confidence bound {a mathematical formula}q˜i+=q˜i+η. During the exploration phase, in order to preserve the DSIC a posteriori property, the allocations {a mathematical formula}{θt}t=1τ do not depend on the reported values of the advertisers and no payments are imposed to the advertisers.
        </paragraph>
       </section>
       <section>
        <section-title>
         Exploitation phase
        </section-title>
        <paragraph>
         We define an upper bound on the SW as{a mathematical formula} We denote by {a mathematical formula}θ˜ the allocation maximizing {a mathematical formula}SW˜(f(vˆ),vˆ) and by {a mathematical formula}f˜ the allocation function returning {a mathematical formula}θ˜:{a mathematical formula}
        </paragraph>
        <paragraph>
         Once the exploration phase is over, the ads are allocated on the basis of {a mathematical formula}f˜. Since {a mathematical formula}f˜ is an affine maximizer, the mechanism can impose WVCG payments to the advertisers satisfying the DSIC a posteriori property. In a pay-per-click fashion the advertiser {a mathematical formula}ai is charged{a mathematical formula} which corresponds, in expectation, to the WVCG payment {a mathematical formula}p˜i(vˆ)=E[p˜ic(vˆ,clickπ(i;θ˜)i)]. As a result, we have:
        </paragraph>
        <paragraph label="Theorem 13">
         The A-VCG4 is:
        </paragraph>
        <list>
         <list-item label="•">
          DSIC in expectation w.r.t. the click realizations,
         </list-item>
         <list-item label="•">
          IR a posteriori,
         </list-item>
         <list-item label="•">
          WBB a posteriori.
         </list-item>
        </list>
        <paragraph>
         We are interested in bounding the regret of the auctioneer's revenue due to A-VCG4 compared to the auctioneer's revenue of the VCG mechanism when all the parameters are known.
        </paragraph>
        <paragraph label="Theorem 14">
         Let us consider a sequential auction with N advertisers, K slots, and T steps with position/ad-dependent externalities and cumulative discount factors{a mathematical formula}{Γm(θ)}m=1Kand accuracy η defined as in Eq.(31). For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG4 achieves an auctioneer's revenue expected regret:{a mathematical formula}where{a mathematical formula}qmin=mini∈N⁡qi. By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}δ=(5Γmin)23K13T−13N13,
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=(5Γmin)23K13T23N13(log⁡2Nδ)13,
         </list-item>
        </list>
        <paragraph label="Remark 1">
         Differences w.r.t. position-dependent externalitiesUp to constants and logarithmic factors, the previous distribution-free bound on {a mathematical formula}RT is {a mathematical formula}O˜(T23N13K43).{sup:16} We first notice that moving from position- to position/ad-dependent externalities does not change the dependency of the regret on the number of steps T and the number of ads N. Moreover, the per-step regret still decreases to 0 as T increases. The main difference w.r.t. the bound in Theorem 2 is in the dependency on K and on the smallest quality {a mathematical formula}qmin. We believe that the augmented dependence in K is mostly due to an intrinsic difficulty of the position/ad-dependent externalities. As a result, the bound displays a super-linear dependency on the number of slots. The other main difference is that now the regret has an inverse dependency on the smallest quality {a mathematical formula}qmin. Inspecting the proof, this dependency is due to the fact that the error of a quality estimate for an ad {a mathematical formula}ai might be amplified by the inverse of the quality itself. As discussed in Remark 2 of Theorem 2, this dependency may also follow from the fact that we have a distribution-free bound. Further discussion on the tightness of this bound is postponed to Section 6.
        </paragraph>
        <paragraph label="Remark 2">
         Optimization of the parameter τAlthough the actual qualities {a mathematical formula}{qi}i∈N are unknown, whenever a lower-bound on {a mathematical formula}qmin is available, the parameter τ could be better tuned by multiplying it by {a mathematical formula}(qmin)−23, thus reducing the regret from {a mathematical formula}O˜((qmin)−1) to {a mathematical formula}O˜((qmin)−23).
        </paragraph>
        <paragraph label="Remark 3">
         Externalities-dependent boundWe notice that the previous bound does not reduce to the bound in Eq. (20) in which only position-dependent externalities are present. Indeed, the dependency on K is different in the two bounds: from {a mathematical formula}K23 in Eq. (20) to {a mathematical formula}K43 in Eq. (34). This means that the bound in Eq. (34) over-estimates the dependency on K whenever the auction has only position-dependent externalities. It is an interesting open question whether it is possible to derive an auction-dependent bound where the specific values of the cumulative probabilities of observation {a mathematical formula}γm,i explicitly appear in the bound and which reduces to Eq. (20) for position-dependent externalities.
        </paragraph>
        <paragraph>
         Comments to the proof. While the proof of Theorem 2 could exploit the specific definition of the payments for position-dependent slots and it is a fairly simple extension of [20], in this case the proof is more complicated because of the dependency of the cumulative probabilities of observation on the actual allocations and decomposes the regret of the exploitation phase in components due to the different allocations ({a mathematical formula}f˜ instead of {a mathematical formula}f⁎) and the different qualities as well ({a mathematical formula}q˜i+ instead of {a mathematical formula}qi).
        </paragraph>
        <paragraph>
         Using the mechanism described before, it is possible to derive an upper-bound over the cumulative regret over the SW of the allocation (as in [23]). We obtain the same dependence over T, as for the regret on the revenue.
        </paragraph>
        <paragraph label="Theorem 15">
         Let us consider a sequential auction with N advertisers, K slots, and T steps. The auction has position/ad-dependent externalities and cumulative discount factors{a mathematical formula}{Γm(θ)}m=1Kand accuracy η defined as in Eq.(31). For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG4 achieves a SW regret:{a mathematical formula}By setting the parameters to
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}δ=(1Γmin)23K−13T−13N13,
         </list-item>
         <list-item label="•">
          {a mathematical formula}τ=(1Γmin)23K−13T23N13(log⁡2Nδ)13,
         </list-item>
        </list>
        <paragraph>
         Thus {a mathematical formula}RTSW=O˜(T23). In particular notice that A-VCG4 is a zero-regret algorithm. We notice that unlike the bound on the revenue regret, in this case {a mathematical formula}RTSW does not display any dependency on {a mathematical formula}qmin, which suggests that the problem of minimizing the SW regret may be easier. Roughly speaking, this is due to the fact that the accuracy of the estimated qualities is only used to determine the allocation {a mathematical formula}f˜ but they do not determine the performance of {a mathematical formula}f˜ itself, which is measured according to its actual SW. On the other hand, in the computation of the revenue regret, the qualities {a mathematical formula}q˜i+ are used to determine the payments and this may lead to an additional error, which is reflected in the presence of {a mathematical formula}qmin in the bound.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Further extensions
      </section-title>
      <paragraph>
       In this section we provide a negative, in terms of regret, result under DSIC in expectation w.r.t. the click realizations and a posteriori w.r.t. the realization of the random component of the mechanism when the parameter {a mathematical formula}γm,i depends only on the ad {a mathematical formula}ai (we denote it by {a mathematical formula}ci=γm,i for any {a mathematical formula}m∈K as in [24]) and this parameter is the only uncertain parameter (i.e., the qualities are known).
      </paragraph>
      <paragraph>
       We focus on the exploitation phase, supposing the exploration phase has produced the estimates {a mathematical formula}{c˜i+}i∈N for the continuation probabilities {a mathematical formula}{ci}i∈N. The allocation function f presented in [24] is able to compute the optimal allocation when {a mathematical formula}{ci}i∈N values are known, but it is not an affine maximizer when applied to the estimated values {a mathematical formula}{c˜i+}i∈N. In fact, in that case the allocation becomes{a mathematical formula} In this case, it is not possible to isolate a weight depending only on a single ad and thus {a mathematical formula}f˜(vˆ) is not affine. Furthermore, we can also show that such allocation function is not monotonic.
      </paragraph>
      <paragraph label="Proposition 6">
       The allocation function{a mathematical formula}f˜in Eq.(37)is not monotonic.
      </paragraph>
      <paragraph label="Proof">
       The proof is by counterexample. Consider an environment with 3 ads and 2 slots such that{a mathematical formula} and {a mathematical formula}qi=1∀i∈N. The optimal allocation {a mathematical formula}θ˜ computed by {a mathematical formula}f˜ when agents declare their true values v is: ad {a mathematical formula}a2 is allocated in the first slot and {a mathematical formula}a3 in the second one. We have {a mathematical formula}CTRa3(θ˜)=0.9.If advertiser {a mathematical formula}a3 reports a larger value, e.g., {a mathematical formula}vˆ3=1.6, in the resulting allocation {a mathematical formula}f˜(vˆ3,v−3), ad {a mathematical formula}a1 is displayed into the first slot and {a mathematical formula}a3 into the second one. In this case {a mathematical formula}CTRa3(θˆ)=0.89&lt;CTRa3(θ˜), thus the allocation function {a mathematical formula}f˜ is not monotonic.  □
      </paragraph>
      <paragraph>
       On the basis of this result, we can state the following theorem.
      </paragraph>
      <paragraph label="Theorem 16">
       Let us consider a sequential auction with N advertisers, K slots, and T steps, with ad-dependent cascade model with parameters{a mathematical formula}{ci}i=1Nwhose value are unknown. Any online learning mechanism that is DSIC in expectation w.r.t. the click realizations and a posteriori w.r.t. the realization of the random component of the mechanism achieves a SW regret{a mathematical formula}RTSW=Θ(T).
      </paragraph>
      <paragraph label="Proof">
       Let, with abuse of notation, {a mathematical formula}f(vˆ|c) be the allocation function maximizing the SW given parameters c. As shown above, {a mathematical formula}f(vˆ|c˜) cannot be used in the exploitation phase, because the resulting mechanism would not be DSIC in expectation w.r.t. the click realizations. However, it can be easily observed that a necessary condition to have a no-regret algorithm is that the allocation function used in the exploitation phase, say {a mathematical formula}g(vˆ|c˜), is such that {a mathematical formula}g(vˆ|c)=f(vˆ|c) for every {a mathematical formula}vˆ and c (that is, they always return the same allocation). Indeed, if there exists at least a {a mathematical formula}vˆ such that {a mathematical formula}g(vˆ|c)≠f(vˆ|c), then, as {a mathematical formula}T→+∞, {a mathematical formula}f(vˆ|c)≠g(vˆ|c˜), given that {a mathematical formula}c˜→c. Thus, since the difference between the values of the allocations is generically strictly positive, the algorithm would suffer from a strictly positive regret when {a mathematical formula}T→+∞ and therefore it would not be a no-regret mechanism. However, any such a g would not be monotonic and therefore it cannot be adopted in a DSIC in expectation w.r.t. the click realizations mechanism. As a result, any online learning mechanism that is DSIC in expectation w.r.t. the click realizations is not a no-regret mechanism.To complete the proof, we need to provide a mechanism with regret {a mathematical formula}Θ(T). Such a mechanism can be easily obtained by partitioning ads in groups such that in each group the ads compete only for a single slot. Therefore, each ad can appear in only one slot.  □
      </paragraph>
      <paragraph>
       The above result shows that no approach similar to the one described in [23] can be adopted even for obtaining DSIC in expectation w.r.t. realizations of the random component of the mechanism. Indeed, the approach described in [23] requires in input a monotonic allocation function. This would suggest a negative result in terms of regret also with DSIC in expectation w.r.t. realizations of the random component of the mechanism.
      </paragraph>
      <paragraph>
       Finally, we provide a result on the regret over the auctioneer's revenue. The proof is straightforward given that the WVCG cannot be adopted due to the above result and therefore the regret over the payments cannot go to zero as T goes to infinite.
      </paragraph>
      <paragraph label="Theorem 17">
       Let us consider a sequential auction with N advertisers, K slots, and T steps, with ad-dependent cascade model with parameters{a mathematical formula}{ci}i=1Nwhose value are unknown. Any online learning mechanism that is DSIC in expectation w.r.t. the click realizations and a posteriori w.r.t. realization of the random component of the mechanism achieves an auctioneer's revenue expected regret{a mathematical formula}RT=Θ(T).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Numerical simulations
     </section-title>
     <paragraph>
      In this section we report numerical simulations to validate the theoretical bounds over the regret of the auctioneer's revenue proved in the previous sections.{sup:17} In particular, the theoretical bounds reveal the dependency of (expected) regret on characteristic parameters of the auction (i.e., T, N, K, and {a mathematical formula}qmin, and μ if the mechanism is randomized). Nonetheless, the upper bounds may be inaccurate in overestimating the actual performance of the proposed algorithms. In fact, while we prove that the regret can never be larger than the upper bound, some steps in the proofs may be loose, thus leading to bounds which do not accurately predict the behavior of the algorithms in practice. In the following we investigate by means of numerical simulations whether the dependency, in terms of asymptotic order, of the bounds on each single parameter of the auction is accurate except for a numerical constant factor. In all the following experiments, we generate the parameters related to the ads in the same way. The qualities {a mathematical formula}{qi}i∈N are drawn from a uniform distribution in {a mathematical formula}[0.01,0.1], while the values {a mathematical formula}{vi}i∈N are randomly drawn from a uniform distribution on {a mathematical formula}[0,1] ({a mathematical formula}vmax=1). On the other hand, the cumulative probabilities of observation {a mathematical formula}{Λm}m∈K are different case by case.
     </paragraph>
     <paragraph>
      Since the main objective is to evaluate the asymptotic accuracy of the bounds, we report the relative regret{a mathematical formula} where {a mathematical formula}B(T,K,N,qmin) is the value of the bound for the specific setting (i.e., Eq. (20) and Eq. (30) for position-dependent, and Eq. (34) for position/ad-dependent externalities).
     </paragraph>
     <paragraph>
      We analyze the asymptotic accuracy of the bounds w.r.t. each specific parameter, changing only its value and keeping the values of all the others fixed. Since B is proved to be an upper-bound on the actual regret {a mathematical formula}RT, we expect the relative regret {a mathematical formula}RRT to be always smaller than 1 ({a mathematical formula}RRT=1 corresponds to the case in which the experimental regret perfectly matches our upper bound). In particular, we say that our upper-bound accurately predicts the actual asymptotic dependency of the regret w.r.t. a specific parameter if the experimental dependence of {a mathematical formula}RRT w.r.t. the parameter is a constant as the parameter changes. Notice that we do not expect the constant to be close to 1, given that we focus on the asymptotic dependence w.r.t. the parameters and in the steps of the proofs we often use worst-case distribution-free bounds. All the results presented in the following sections are obtained by setting τ and δ as suggested by our bounds and, where it is not differently specified, by averaging over 100 independent runs.
     </paragraph>
     <section label="6.1">
      <section-title>
       Position-dependent externalities
      </section-title>
      <section label="6.1.1">
       Unknown {a mathematical formula}{qi}i∈N
       <paragraph>
        First of all we analyze the asymptotic accuracy of the bound provided in Section 4.1, where the model presents only position-dependent externalities and the qualities of the ads are unknown. We design the simulations such that {a mathematical formula}λm=λ for every {a mathematical formula}m∈K with {a mathematical formula}Λ1=1 and {a mathematical formula}ΛK=0.8 (i.e., {a mathematical formula}λ=0.8K−1). Thus, {a mathematical formula}Λmin=0.8 in all the experiments.
       </paragraph>
       <paragraph>
        In Fig. 7 we analyze the asymptotic accuracy of the bound w.r.t. the parameters T and N. All the three curves in the left plot are completely flat (except for noise due to the randomness of the simulations) showing that the value of the relative regret {a mathematical formula}RRT for different values of K and N does not change as T increases. This suggests that the bound in Theorem 2 effectively predicts the dependency of the regret {a mathematical formula}RT w.r.t. the number of steps T of the auction as {a mathematical formula}O˜(T2/3). The right plot represents the dependency of the relative regret {a mathematical formula}RRT on the number of ads N. In this case we notice that it is relatively accurate as N increases, but there is a transitory effect for smaller values of N where the regret grows faster than predicted by the bound (although {a mathematical formula}B(T,K,N,qmin,Λmin) is still an upper-bound to {a mathematical formula}RT). Finally, the left plot of Fig. 8 suggests that the asymptotic dependency on K in the bound of Theorem 2 is over-estimated, since the relative regret {a mathematical formula}RRT decreases as K increases. As discussed in the comment to the proof in Section 4, this might be explained by the over-estimation of the term {a mathematical formula}maxi⁡(q˜i+vˆi;l)maxi⁡(q˜i+vˆi;k) in the proof. In fact, this term is likely to decrease as K increases. In order to validate this intuition, we have identified some experimental settings for which the bound seems to accurately predict the asymptotic dependency on K: {a mathematical formula}q1=0.1, {a mathematical formula}q2=0.095, and {a mathematical formula}qi=0.09 for every {a mathematical formula}i,2&lt;i≤K. As a result, the ratio between the qualities {a mathematical formula}{qi}i∈N is fixed (on average) and does not change with K. The right plot of Fig. 8 shows that, with these values of {a mathematical formula}{qi}i∈N, the ratio {a mathematical formula}RRT is constant for different values of N, implying that in this case the bound accurately predicts the asymptotic behavior of {a mathematical formula}RT. In fact, as commented in the remarks to Theorem 2, we derive distribution-independent bounds where the qualities {a mathematical formula}{qi}i∈N do not appear in the bound. As a result, {a mathematical formula}RT should be intended as a worst case w.r.t. all the possible configurations of qualities and externalities.
       </paragraph>
      </section>
      <section label="6.1.2">
       Unknown {a mathematical formula}{Λm}m∈K
       <paragraph>
        We now investigate the asymptotic accuracy of the bound derived for algorithm A-{a mathematical formula}VCG2′ presented in Section 4.2.2. We used several probability distributions to generate the values of {a mathematical formula}{λm}m∈K. We observed that, when they are drawn uniformly from the interval {a mathematical formula}[0.98,1.00], the numerical simulations confirm our bound (as we show below), whereas the bound seems to overestimate the dependencies on K and μ when the support of the probability distribution is wider (e.g., {a mathematical formula}[ξ,1.00] with {a mathematical formula}ξ≪0.98); we do not report any plot for this second case.
       </paragraph>
       <paragraph>
        The left plot of Fig. 9 shows the dependence of the ratio {a mathematical formula}RRT w.r.t. T when {a mathematical formula}μ=0.01. Despite the noise, the ratio seems not to be affected by the variation of T, confirming our bound. In the right plot of Fig. 9, we observe that when {a mathematical formula}T=105 and {a mathematical formula}μ=0.01 the behavior of the ratio as K changes is essentially the same for different values of N. Furthermore, we observe that the bound is accurate except that it seems to overestimate the dependence when K assumes small values (as it happens in practice). In the left plot of Fig. 10, the ratio {a mathematical formula}RRT seems to be constant as μ varies when {a mathematical formula}T=105.
       </paragraph>
       <paragraph>
        We conclude our analysis studying the variance of the payments as μ varies. The bound over {a mathematical formula}RT, provided in Section 4.2.2, suggests to choose a {a mathematical formula}μ→0 in order to reduce the regret. Nonetheless, the regret bounds are obtained in expectation w.r.t. all the sources of randomization and do not consider how single realizations of the learning mechanism may deviate w.r.t. the expected regret. Thus in the right plot of Fig. 10 we investigate the variance of the payments. The variance is excessively high for small values of μ, making the adoption of these value inappropriate. Thus, the choice of μ should consider both these two dimensions of the problem: the regret and the variance of the payments.
       </paragraph>
      </section>
      <section label="6.1.3">
       Unknown {a mathematical formula}{Λm}m∈K and {a mathematical formula}{qi}i∈N
       <paragraph>
        In this section we analyze the bound provided in Section 4.3 for position-dependent auctions where both the prominences and the qualities are unknown. For these simulations we generate {a mathematical formula}{λm}m∈K samples from a uniform distribution over {a mathematical formula}[0.5,1] and we set τ, δ and μ to the values derived for the bound. In particular, in order to balance the increase of variance of the payments when μ decreases, the number of steps is not constant, but it changes as a function of μ as {a mathematical formula}1000μ. This means that, in expectation, the bid of a generic ad {a mathematical formula}ai is modified 1000 times over the number of the steps.
       </paragraph>
       <paragraph>
        In the plots of Fig. 11, we show that the bound in Eq. (30) accurately predicts the asymptotic dependence of the regret w.r.t. the parameters T and N. Indeed, except for the noise due to the high variance of the payments based on the cSRP, the two plots show that fixing the other parameters, the ratio {a mathematical formula}RRT is constant as both T increases and N increases.
       </paragraph>
       <paragraph>
        The plot in Fig. 12 represents the dependency of the relative regret w.r.t. the parameter K. We can deduce that the bound {a mathematical formula}RT over-estimates the dependency on K for small values of the parameters, while, with larger values, the bound accurately predicts the behavior, the curves being flat.
       </paragraph>
      </section>
     </section>
     <section label="6.2">
      <section-title>
       Position/ad-dependent externalities
      </section-title>
      <paragraph>
       In this section we analyze the bound provided in Section 5.1 for auctions with position-dependent and ad-dependent externalities where only the qualities are unknown.
      </paragraph>
      <paragraph>
       In the bound provided in Theorem 14 the regret {a mathematical formula}RT presents a linear dependency on N and an inverse dependency on the smallest quality {a mathematical formula}qmin. In the left plot of Fig. 13 we report {a mathematical formula}RRT as T increases. As it can be observed, the bound accurately predicts the behavior of the regret w.r.t. T as in the case of position-dependent externalities. In the right plot of Fig. 13 we report {a mathematical formula}RRT as we change {a mathematical formula}qmin. According to the bound in Eq. (34) the regret should decrease as {a mathematical formula}qmin increases (i.e., {a mathematical formula}RT=O˜(qmin−1)) but it is clear from the plot that {a mathematical formula}RT has a much smaller dependency on {a mathematical formula}qmin, if any.{sup:18} Finally, we study the dependency on N (Fig. 14). In this case {a mathematical formula}RRT slightly increases and then it tends to flat as N increases. This result suggests that the, theoretically derived, {a mathematical formula}N13 asymptotic dependency of {a mathematical formula}RT w.r.t. the number of ads might be correct. We do not report results on K since the complexity of finding the optimal allocation {a mathematical formula}f⁎ becomes intractable for values of K larger than 8, as shown in [41], making the empirical evaluation of the bound unfeasible.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Vickrey–Clarke–Groves mechanism
     </section-title>
     <paragraph>
      Consider a generic direct-revelation mechanism {a mathematical formula}M=(N,V,Θ,f,{pi}i∈N) as defined in Section 3.2. Differently from the SSA case, in general the type of an agent, denoted by {a mathematical formula}vi for consistency with the rest of the paper, is a vector of parameters. We define a function {a mathematical formula}vali:Θ×V→R+, which returns the value obtained by agent {a mathematical formula}ai when its type is {a mathematical formula}vi and the allocation chosen by the mechanism is θ.
     </paragraph>
     <paragraph>
      The VCG mechanism is obtained coupling the two following functions:
     </paragraph>
     <list>
      <list-item label="•">
       the allocation function f which returns the allocation maximizing the social welfare, i.e.,{a mathematical formula}
      </list-item>
      <list-item label="•">
       the payment rule {a mathematical formula}pi, which defines the payment required from agent {a mathematical formula}ai, i.e.,{a mathematical formula} where we denote by {a mathematical formula}f(vˆ−i) the allocation returned by f when agent i does not participate to the auction.
      </list-item>
     </list>
     <paragraph>
      In this quasi-linear environment, when there are no interdependencies among the types of the agents and the no-single-agent effect [3] holds, the VCG mechanism is AE, DSIC a posteriori, IR a posteriori, and WBB a posteriori.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Monotonicity and Myerson's payments
     </section-title>
     <paragraph>
      Consider a generic direct-revelation mechanism {a mathematical formula}M=(N,V,Θ,f,{pi}i∈N) as defined in Section 3.2. A single-parameter linear environment is such that
     </paragraph>
     <list>
      <list-item label="•">
       the type of each agent {a mathematical formula}ai is a scalar {a mathematical formula}vi (single-parameter assumption),
      </list-item>
      <list-item label="•">
       the utility function of agent {a mathematical formula}ai is {a mathematical formula}ui(vˆ)=zi(f(vˆ))vi−pi(vˆ) where {a mathematical formula}zi:Θ→R is a function of the allocation (linear assumption).
      </list-item>
     </list>
     <paragraph>
      An allocation function f is monotonic in a single-parameter linear environment if for any {a mathematical formula}vˆ−i{a mathematical formula} for any {a mathematical formula}vi″≥vi′. Essentially, {a mathematical formula}zi is monotonically increasing in {a mathematical formula}vi once {a mathematical formula}vˆ−i has been fixed. In such environments, it is always possible to design a DSIC mechanism imposing the following payments [35]:{a mathematical formula} where {a mathematical formula}hi:VN−1→R is a generic function not depending on the type of agent {a mathematical formula}ai.
     </paragraph>
    </section>
    <section label="Appendix C">
     Proof of revenue regret in Theorem 2
     <paragraph>
      We start by reporting the proof of Proposition 1.
     </paragraph>
     <paragraph label="Proof of Proposition 1">
      The derivation is a simple application of the Hoeffding's bound. We first notice that each of the terms in the empirical average {a mathematical formula}q˜i (Eq. (11)) is bounded in {a mathematical formula}[0;1/Λπ(i;θt)]. Thus we obtain{a mathematical formula} By reordering the terms in the previous expression we have{a mathematical formula} which guarantees that all the empirical estimates {a mathematical formula}q˜i are within η of {a mathematical formula}qi for all the ads with probability, at least, {a mathematical formula}1−δ.  □
     </paragraph>
     <paragraph>
      Before stating the main result of this section, we need the following lemma.
     </paragraph>
     <paragraph label="Lemma 1">
      For any slot{a mathematical formula}smwith{a mathematical formula}m∈K, with probability{a mathematical formula}1−δ,{a mathematical formula}where the operator{a mathematical formula}max⁡(⋅;⋅)is defined as in Section4.
     </paragraph>
     <paragraph label="Proof">
      The proof is a straightforward application of Proposition 1. We consider the optimal allocation {a mathematical formula}θ⁎ defined in Eq. (2) and the optimal allocation {a mathematical formula}θ˜ when estimates {a mathematical formula}q˜+ are adopted defined in Eq. (16). We denote {a mathematical formula}h=α(m;θ⁎)∈arg⁡maxi∈N⁡(qivˆi;m), i.e., the index of the ad allocated in a generic slot in position m. There are two possible scenarios:
     </paragraph>
     <list>
      <list-item label="•">
       If {a mathematical formula}π(h;θ˜)&lt;m (the ad is displayed into a higher slot in the approximated allocation {a mathematical formula}θ˜), then {a mathematical formula}∃j∈N s.t. {a mathematical formula}π(j;θ⁎)&lt;m∧π(j;θ˜)≥m. Thus{a mathematical formula} where the second inequality holds with probability {a mathematical formula}1−δ;
      </list-item>
      <list-item label="•">
       If {a mathematical formula}π(h;θ˜)≥m (the ad is displayed into a lower or equal slot in the approximated allocation {a mathematical formula}θ˜), then{a mathematical formula} where the second inequality holds with probability {a mathematical formula}1−δ.
      </list-item>
     </list>
     <paragraph label="Proof of Theorem 2">
      Step 1: expected payments. The proof follows steps similar to those in the proofs in [20]. We first recall that since the mechanism is DSIC in expectation w.r.t. the clicks, then we can directly focus on the regret when the actual values v are bid. For any ad {a mathematical formula}ai such that {a mathematical formula}π(i;θ⁎)≤K, the expected payments of the VCG mechanism in this case reduce to Eq. (9):{a mathematical formula} while, given the definition of A-VCG1 reported in Section 4.1, the expected payments for at t-th iteration of the auction are{a mathematical formula} where the payment for any ad {a mathematical formula}ai such that {a mathematical formula}π(i;θ˜)≤K is defined in Eq. (17) as:{a mathematical formula}Step 2: per-step exploration regret. Since for any {a mathematical formula}1≤t≤τ, A-VCG1 sets all the payments to 0, the per-step regret is{a mathematical formula} where {a mathematical formula}Δl=Λl−Λl+1. The exploration regret is obtained by summing up r over τ steps.Step 3: per-step exploitation regret. Now we focus on the expected (w.r.t. click realizations) per-step regret during the exploitation phase. According to the definition of payments, at each step {a mathematical formula}t∈{τ+1,…,T} of the exploitation phase we bound the per-step regret r as{a mathematical formula} By definition of the max operator, since {a mathematical formula}l+1&gt;m, it follows that{a mathematical formula} Finally, from Lemma 1 and {a mathematical formula}vα(m;θ˜)≤vmax, it follows that{a mathematical formula} with probability at least {a mathematical formula}1−δ. Notice that, by definition of {a mathematical formula}Δl, {a mathematical formula}∑l=mKΔl=Λm−ΛK+1=Λm. Furthermore, from the definition of {a mathematical formula}q˜i+ and using Eq. (14) we have that for any ad {a mathematical formula}ai:{a mathematical formula} with probability at least {a mathematical formula}1−δ. Thus, the difference between the payments becomes{a mathematical formula} with probability {a mathematical formula}1−δ.{sup:19}Step 4: cumulative regret. We first consider the (low-probability) event in which the bound on {a mathematical formula}q˜i+ derived in Proposition 1. In this case, we cannot guarantee anything about the behavior of the mechanism, since the payments are very inaccurate estimates of the CTRs, and thus the largest possible regret is suffered. In particular, we consider the worst case loss of {a mathematical formula}vmax for each slot for each step, leading to a total regret of {a mathematical formula}vmax(∑m=1KΛm)T with probability δ. By summing up the regrets reported in Eq. (C.3) during the exploration phase and Eq. (C.6) during the exploitation phase and by considering that these bounds hold with probability at least {a mathematical formula}1−δ (upper-bounded by 1 in the following), we obtain an expected regret{a mathematical formula} where {a mathematical formula}Rei is the upper bound on the regret suffered during the exploitation phase (which holds with probability at least {a mathematical formula}1−δ), {a mathematical formula}Rer is the upper bound on the regret suffered during the exploitation phase (which holds with probability at least {a mathematical formula}1−δ) and {a mathematical formula}Rδ is the upper bound on the regret when the bounds do not hold (with probability at most δ). This bound can be further simplified, given that {a mathematical formula}∑m=1KΛm≤K, as{a mathematical formula}Step 5: parameters optimization. Beside describing the performance of A-VCG1, the previous bound also provides guidance for the optimization of the parameters τ and δ. We first simplify the bound in Eq. (C.7) as{a mathematical formula} where we used {a mathematical formula}∑m=1K1/Λm2≤K/Λmin2, with {a mathematical formula}Λmin=minm∈K⁡Λm. In order to find the optimal value of τ, we take the derivative of the previous bound w.r.t. τ, set it to zero and obtain{a mathematical formula} which leads to{a mathematical formula} Substituting this value of τ into Eq. (C.8) leads to the optimized bound{a mathematical formula} We are now left with the choice of the confidence parameter {a mathematical formula}δ∈(0,1), which can be easily set to optimize the asymptotic rate (i.e., ignoring constants and logarithmic factors) as{a mathematical formula} We thus obtain the final bound{a mathematical formula} We have to impose the constraints that {a mathematical formula}T&gt;NK (given by {a mathematical formula}δ&lt;1) and that {a mathematical formula}T&gt;τ, i.e., {a mathematical formula}T&gt;NKΛmin2log⁡Nδ. The two constraints imply:{a mathematical formula}  □
     </paragraph>
    </section>
    <section label="Appendix D">
     Proof of revenue regret in Theorem 7
     <paragraph>
      Unlike the setting considered in Theorem 2, here the regret is only due to the use of a randomized mechanism, since no parameter estimation is actually needed.
     </paragraph>
     <paragraph label="Proof of Theorem 7">
      Step 1: payments and additional notation. We recall that according to [35] and [45] the expected VCG payments can be written, as in Eq. (24), in the form{a mathematical formula} while the A-{a mathematical formula}VCG2′ mechanism prescribes contingent payments as in Eq. (25), which lead to expected payments{a mathematical formula} Given the randomness of the allocation function of A-{a mathematical formula}VCG2′, we need to introduce the following additional notation:
      <list>
       {a mathematical formula}s∈{0,1}N is a vector where each element {a mathematical formula}si denotes whether the i-th bid has been preserved or it has been modified by the cSRP, i.e., if {a mathematical formula}xi=vˆi then {a mathematical formula}si=1, otherwise if {a mathematical formula}xi&lt;vˆi then {a mathematical formula}si=0. Notice that s does not provide information about the actual modified values x;{a mathematical formula}Ex|s[Λπ(i;f(x))|vˆ] is the expected value of prominence associated with the slots allocated to ad {a mathematical formula}ai, conditioned on the declared bids {a mathematical formula}vˆ being perturbed as in s.Step 2: cumulative regret.
      </list>
      <paragraph>
       We proceed by studying the per-ad regret {a mathematical formula}ri(v)=pi⁎(v)−pi⁎′(v), where the advertisers bid their true values v since the mechanism is DSIC. Given the previous definitions, we rewrite the expected payments {a mathematical formula}pi⁎′(v) as{a mathematical formula} where in the last expression we used the expression of the VCG payments in Eq. (24) according to [35] and [45]. The per-ad regret is{a mathematical formula} Since we have that {a mathematical formula}u≤vi in the integral and since the allocation function defined in [23] is monotonic, we have that{a mathematical formula} which implies that {a mathematical formula}ri,1B is non-negative. Thus the regret {a mathematical formula}riB can be bounded as{a mathematical formula} We can now compute the bound on the global regret {a mathematical formula}RT. Since this mechanism does not require any estimation phase, the regret is simply{a mathematical formula}Step 3: parameters optimization. In this case, the bound would suggest to choose a {a mathematical formula}μ→0, but it is necessary to consider that with {a mathematical formula}μ→0 the variance of the payment goes to infinity.  □
      </paragraph>
     </paragraph>
    </section>
    <section label="Appendix E">
     Proof of revenue regret in Theorem 11
     <paragraph>
      The proof of Theorem 11 needs to combine the result of Theorem 7 and the regret due to the estimation of the parameters similarly to what is done in Theorem 2.
     </paragraph>
     <paragraph label="Proof of Theorem 11">
      Step 1: payments and the regret. Similar to the proof of Theorem 7, we use the form of the VCG payments as in Eq. (24):{a mathematical formula} while A-VCG3 uses the contingent payments in Eq. (28), which in expectation become{a mathematical formula} We also need to introduce the expected payments{a mathematical formula} which correspond to the VCG payments except for the use of allocation function {a mathematical formula}f˜ in place of {a mathematical formula}f⁎.Initially, we compute an upper bound over the per-ad regret {a mathematical formula}ri=pi⁎−pi′ for each step of the exploitation phase and we later use this result to compute the upper bound for the regret {a mathematical formula}RT over T steps. We divide the per-ad regret in two different components:{a mathematical formula} where
      <list>
       {a mathematical formula}riB(v) is the regret due to the use of the approach proposed in [23] instead of the VCG payments, when all the parameters are known;{a mathematical formula}riL(v) is the regret due to the uncertainty on the parameters when the payments defined in [23] are considered.Step 2: the per-ad per-step cSRP regret.
      </list>
      <paragraph>
       We can reuse the result obtained in the proof of Theorem 7. In particular, we can use the bound in Eq. D.2, i.e. {a mathematical formula}riB(v)≤(K+1)μvmax. Given that we have assumed {a mathematical formula}N&gt;K, in the remaining parts of this proof we will use the following upper bound: {a mathematical formula}riB(v)≤(K+1)μvmax≤Nμvmax.Step 3: the per-ad per-step learning regret. Similar to the previous step, we write the learning expected payments based on the cSRP in Eq. (E.1) as{a mathematical formula} Then the per-ad regret is{a mathematical formula} We now simply notice that payments {a mathematical formula}p˜i are WVCG payments corresponding to the estimated allocation function {a mathematical formula}f˜ and can be written as{a mathematical formula} which allows us to use the results stated in proof of Theorem 2 and from Eq. (C.5) we can conclude that{a mathematical formula}Step 4: cumulative regret. We now bring together the two per-step regrets and we have that at each step of the exploitation phase we have the regret {a mathematical formula}r=∑i=1Nri. We first notice that the expected per-step regret {a mathematical formula}ri for each ad {a mathematical formula}ai is defined as the difference between the VCG payments {a mathematical formula}pi⁎(v) and the (expected) payments {a mathematical formula}pi′(v) computed by the randomized mechanism when the estimates {a mathematical formula}q˜+ are used. We notice that {a mathematical formula}pi⁎(v) can be strictly positive only for the K displayed ads, while {a mathematical formula}pi′(v)≥0∀i∈N, due to the mechanism randomization. Thus, {a mathematical formula}pi⁎(v)−pi′(v)&gt;0 only for at most K ads. Thus we obtain the per-step regret{a mathematical formula} Finally, the global regret becomes{a mathematical formula}Step 5: parameters optimization. We first simplify further the previous bound as{a mathematical formula} We first optimize the value of τ, take the derivative of the previous bound w.r.t. τ and set it to zero and obtain{a mathematical formula} which leads to{a mathematical formula} Once replaced into Eq. (E.3) we obtain{a mathematical formula} The optimization of the asymptotic order of the bound can then be obtained by setting μ and δ so as to equalize the orders of the second and third term in the bound. In particular, by setting{a mathematical formula} we obtain the final bound{a mathematical formula} Notice that, since {a mathematical formula}δ&lt;1, this implies that {a mathematical formula}T&gt;N, and, since {a mathematical formula}μ&lt;1, it must be the case {a mathematical formula}T&gt;N−2&gt;1 that always holds. Moreover {a mathematical formula}T&gt;τ, thus {a mathematical formula}T&gt;Nlog⁡2Nδ.  □
      </paragraph>
     </paragraph>
    </section>
    <section label="Appendix F">
     Proof of revenue regret in Theorem 14
     <paragraph>
      Before deriving the proof of Theorem 14, we prove two lemmas that we use in what follows.
     </paragraph>
     <paragraph label="Lemma 2">
      Let{a mathematical formula}Gbe an arbitrary space of allocation functions, then for any{a mathematical formula}g∈G, when{a mathematical formula}|qi−q˜i+|≤ηwith probability{a mathematical formula}1−δ, then for any{a mathematical formula}vˆwe have{a mathematical formula}with probability{a mathematical formula}1−δ.
     </paragraph>
     <paragraph label="Proof">
      By using the definition of SW and {a mathematical formula}SW˜ we have the following sequence of inequalities{a mathematical formula} The second statement follows from{a mathematical formula}  □
     </paragraph>
     <paragraph label="Lemma 3">
      Let{a mathematical formula}Gbe an arbitrary space of allocation functions, then for any{a mathematical formula}g∈G, when{a mathematical formula}|qi−q˜i+|≤ηwith probability{a mathematical formula}1−δ, we have{a mathematical formula}with probability{a mathematical formula}1−δ.
     </paragraph>
     <paragraph label="Proof">
      The first inequality follows from{a mathematical formula} while the second inequality follows from{a mathematical formula}  □
     </paragraph>
     <paragraph>
      We are now ready to proceed with the proof of Theorem 14.
     </paragraph>
     <paragraph label="Proof of Theorem 14">
      Step 1: per-ad per-step regret. We first compute the per-step per-ad regret {a mathematical formula}ri=pi⁎(v)−p˜i(v) at each step of the exploitation phase for each ad {a mathematical formula}ai. According to the definition of payments we have{a mathematical formula} We bound the first term through Lemma 2 and the following inequalities{a mathematical formula} with probability {a mathematical formula}1−δ. We rewrite {a mathematical formula}ri2 as{a mathematical formula} We now focus on the term {a mathematical formula}ri3 and use Lemma 2 to bound it as{a mathematical formula}Step 2: exploitation and cumulative regret. We define {a mathematical formula}I={i∈N|π(i;f˜(v))≤K∨π(i;f˜(v))≤K}, {a mathematical formula}|I|≤2K. It is clear that only the ads {a mathematical formula}ai s.t. {a mathematical formula}i∈I have a regret {a mathematical formula}ri≠0. The other ads, {a mathematical formula}i∉I, have both {a mathematical formula}pi⁎(v)=0 and {a mathematical formula}p˜i(v)=0. Thus, we can bound the regret r, at each exploitative step, in the following way{a mathematical formula} The remaining terms {a mathematical formula}r1 and {a mathematical formula}r2 can be easily bounded using Lemma 3 as{a mathematical formula} Summing up all the terms we finally obtain{a mathematical formula} with probability {a mathematical formula}1−δ. Now, considering the per-step regret of the exploration and exploitation phases, we obtain the final bound on the cumulative regret {a mathematical formula}RT as follows{a mathematical formula}Step 3: parameter optimization. Let {a mathematical formula}c:=5Γminqmin, then we first simplify the previous bound as{a mathematical formula} Taking the derivative w.r.t. τ leads to{a mathematical formula} which leads to{a mathematical formula} Once replaced in the bound, we obtain{a mathematical formula} Finally, we choose δ to optimize the asymptotic order by setting{a mathematical formula} which leads to the final bound{a mathematical formula} Notice that this bound imposes constraints on the value of T, indeed, {a mathematical formula}T&gt;τ, thus {a mathematical formula}T&gt;c23K13T23N13(log⁡2Nδ)13 and {a mathematical formula}δ&lt;1, thus {a mathematical formula}T&gt;c2KN, leading to:{a mathematical formula}The problem associated with the previous bound is that τ and δ depends on {a mathematical formula}qmin, which is an unknown quantity. Thus actually choosing this value to optimize the bound may be unfeasible. An alternative choice of τ and δ is obtained by optimizing the bound removing the dependency on {a mathematical formula}qmin. Let {a mathematical formula}d:=5Γmin, then we choose{a mathematical formula} and{a mathematical formula} This leads to the final bound{a mathematical formula} Given that {a mathematical formula}δ&lt;1, this implies that {a mathematical formula}T&gt;KNd2, and {a mathematical formula}T&gt;τ implies {a mathematical formula}T&gt;d2KNlog⁡2Nδ. Together they impose{a mathematical formula}  □
     </paragraph>
    </section>
    <section label="Appendix G">
     <section-title>
      Deviation regret
     </section-title>
     <paragraph>
      The definition of regret in Eq. (5) measures the cumulative difference between the revenue of the VCG compared to the one obtained by A-VCG1 over T steps. Upper-bounds over this quantity guarantees that the loss in terms of revenue does not increase linearly with T. As illustrated in the previous sections, the key passage in the proofs is the upper-bounding of the regret at each step of the exploitation phase (i.e., {a mathematical formula}r=∑i=1N(pi⁎(v)−p˜i(v))). Nonetheless, we notice that this quantity could be negative as well. In this section we introduce a different notion of regret ({a mathematical formula}R˜T) that we study only for A-VCG1, leaving for the future a more comprehensive analysis of the other algorithms. Let us consider the following simple example. Let {a mathematical formula}N=3, {a mathematical formula}K=1, {a mathematical formula}vi=1 for all the ads, and {a mathematical formula}q1=0.1, {a mathematical formula}q2=0.2, and {a mathematical formula}q3=0.3. Let assume that after the exploration phase we have {a mathematical formula}q˜1+=0.1, {a mathematical formula}q˜2+=0.29, {a mathematical formula}q˜3+=0.3. The standard VCG mechanism allocates ad {a mathematical formula}a3 and asks for a payment {a mathematical formula}p3⁎(v)=0.2. During the exploitation phase A-VCG1 also allocates {a mathematical formula}a3 but asks for an (expected) payment {a mathematical formula}p˜3(v)=(q˜2+/q˜3+)q3=0.29. Thus, the regret in each exploitation step is {a mathematical formula}r=p3⁎(v)−p˜3(v)=−0.09. Although this result might seem surprising, it is due to the fact that while both A-VCG1 and VCG are truthful, in general A-VCG1 is not AE. We recall that a mechanism is AE if for any set of advertisers it always maximizes the social welfare. In the example, if for instance the true quality of ad {a mathematical formula}a3 is {a mathematical formula}q3=0.28, then the allocation induced by {a mathematical formula}q˜+s is not efficient anymore. For this reason, we characterized the behavior of A-VCG1 compared to the VCG considering the deviation between their payments, defined as{a mathematical formula} where we consider the definition of {a mathematical formula}p˜i in Eq. (C.2). We leave to further investigation the study of this regret for the other considered mechanisms.
     </paragraph>
     <paragraph label="Theorem 18">
      Let us consider a sequential auction with N advertisers, K slots, and T steps with position-dependent cascade model with parameters{a mathematical formula}{Λm}m=1Kand accuracy η as defined in Eq.(14). For any parameter{a mathematical formula}τ∈{1,…,T}and{a mathematical formula}δ∈(0,1), the A-VCG1 achieves an auctioneer's revenue expected regret:{a mathematical formula}where{a mathematical formula}qmin=mini∈N⁡qi. By setting the parameters to
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}δ=N13K−13T−13,
      </list-item>
      <list-item label="•">
       {a mathematical formula}τ=K−13N13T23Λmin23(log⁡Nδ)13,
      </list-item>
     </list>
     <paragraph label="Proof">
      We initially provide a bound over the per-step regret during the exploitation phase. We consider the two sides of the bound separately. We have that for the first side of the bound we can use the result provided in Step 3 in the proof of Theorem 2, i.e.,{a mathematical formula} with probability {a mathematical formula}1−δ. Now we bound the other side.{a mathematical formula}In order to proceed we need to bound the ratio in the inner term. We first recall that for any ad {a mathematical formula}ai, we have that {a mathematical formula}q˜i+vi=(q˜i+η)vi≤(qi+2η)vi. Let {a mathematical formula}i′∈arg⁡maxj∈N⁡(qjvj;l+1) be the ad displayed in {a mathematical formula}sl+1 when the true qualities are known. We distinguish two cases:
      <list>
       The ad {a mathematical formula}ai′ shifts from slot {a mathematical formula}l+1 to a higher precedence slot when allocated according to {a mathematical formula}f˜, i.e., {a mathematical formula}π(i′;f˜(v))≤l+1. In this case we have{a mathematical formula}The ad {a mathematical formula}ai′ shifts from slot {a mathematical formula}l+1 to a lower precedence slot when allocated according to {a mathematical formula}f˜, i.e., {a mathematical formula}π(i′;f˜(v))&gt;l+1. In this case, there must exist an ad j that in the exact allocation is allocated after {a mathematical formula}i′ but it is promoted to a higher precedence slot according to {a mathematical formula}f˜. This corresponds to a {a mathematical formula}j∈N such that {a mathematical formula}π(j;f⁎(v))≥l+1 but {a mathematical formula}π(j;f˜(v))&lt;l+1. As a result we have{a mathematical formula}Using these results we obtain
      </list>
      <paragraph>
       {a mathematical formula} with probability {a mathematical formula}1−δ. As a result we have{a mathematical formula} with probability {a mathematical formula}1−δ. The final bound on the expected regret is thus{a mathematical formula}We first simplify the previous bound as{a mathematical formula} and choosing the parameters{a mathematical formula}{a mathematical formula} the final bound is{a mathematical formula} The fact {a mathematical formula}δ&lt;1 implies that {a mathematical formula}T&gt;NK, and {a mathematical formula}T&gt;τ implies {a mathematical formula}T&gt;K−1NΛmin2log⁡Nδ. Together they constrain{a mathematical formula}  □
      </paragraph>
     </paragraph>
     <paragraph label="Remark">
      The boundWe notice that the bound is very similar to the bound for the regret {a mathematical formula}RT but now an inverse dependency on {a mathematical formula}qmin appears. This suggests that bounding the deviation between the two mechanisms is more difficult than bounding the revenue loss and that, as the qualities become smaller, the A-VCG1 could be less and less efficient and, thus, have a larger and larger revenue. This result has two important implications. (i) If SW maximization is an important requirement in the design of the learning mechanism, we should analyze the loss of A-VCG1 in terms of social welfare and provide (probabilistic) guarantees about the number of steps the learning mechanism need in order to be AE (see [17] for a similar analysis). (ii) If social welfare is not a priority, this result implies that a learning mechanism could be preferable w.r.t. the standard VCG mechanism. We believe that further theoretical analysis and experimental validation are needed to understand better both aspects.
     </paragraph>
    </section>
    <section label="Appendix H">
     Proofs of social-welfare regret in Theorems 3 and 15
     <paragraph>
      Before stating the main result of this section, we need the following technical lemma.
     </paragraph>
     <paragraph label="Lemma 4">
      Let us consider an auction with N advertisers, K slots, and T steps, and a mechanism that separates the exploration (τ steps) and the exploitation phases ({a mathematical formula}T−τsteps). Consider an arbitrary space of allocation functions{a mathematical formula}G,{a mathematical formula}g˜∈arg⁡maxg′∈G⁡SW˜(g′(vˆ),vˆ)and{a mathematical formula}|qi−q˜i+|≤ηwith probability{a mathematical formula}1−δ. For any{a mathematical formula}g∈G, an upper bound of SW regret{a mathematical formula}RTSWof the mechanism adopting{a mathematical formula}g˜instead of g is:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      We now prove the bound on the social welfare, starting from the cumulative per-step regret during the exploitation phase.{a mathematical formula} The two remaining terms {a mathematical formula}r1 and {a mathematical formula}r2 can be easily bounded by using Lemma 3{a mathematical formula} with probability {a mathematical formula}1−δ.Thus, we can conclude that:{a mathematical formula}  □
     </paragraph>
     <paragraph label="Proof of Theorem 3">
      Step 1: cumulative regret. We apply Lemma 4 to the position-dependent cascade model with {a mathematical formula}{qi}i∈N unknowns, obtaining{a mathematical formula}Step 2: parameter optimization. First we notice that adopting the value of the parameters identified in Theorem 2 we obtain an upper bound {a mathematical formula}O˜(T23) for the global regret {a mathematical formula}RTSW.In order to find values that better optimize the bound over {a mathematical formula}RTSW, let {a mathematical formula}e:=1Λmin, then we first simplify the previous bound as{a mathematical formula} Taking the derivative of the previous bound w.r.t. τ leads to{a mathematical formula} which leads to{a mathematical formula} Once replaced in the bound, we obtain{a mathematical formula} Finally, we choose δ to optimize the asymptotic order by setting{a mathematical formula} The final bound is{a mathematical formula} Given that {a mathematical formula}δ&lt;1 this implies that {a mathematical formula}T&gt;e2K−1N. This constrain is satisfied imposing {a mathematical formula}T&gt;τ, i.e.,{a mathematical formula}  □
     </paragraph>
     <paragraph label="Proof of Theorem 15">
      Step 1: cumulative regret. We apply Lemma 4 to the model with position- and ad-dependent externalities with {a mathematical formula}{qi}i∈N unknowns, obtaining{a mathematical formula}Step 2: parameter optimization. First we notice that adopting the value of the parameters identified in Theorem 14 we obtain an upper bound {a mathematical formula}O˜(T23) for the global regret {a mathematical formula}RTSW.In order to find values that better optimize the bound over {a mathematical formula}RTSW, it is possible to use the procedure followed in the proof of Theorem 3 with {a mathematical formula}e:=1Γmin:{a mathematical formula}  □
     </paragraph>
    </section>
    <section label="Appendix I">
     Proof of social-welfare regret in Theorem 8
     <paragraph label="Proof of Theorem 8">
      The bound over the SW regret {a mathematical formula}RTSW can be easily derived considering that each bid is modified by the cSRP with a probability of μ. Thus we can define {a mathematical formula}S′={s′|s′∈{0,1}N,π(i;f⁎(vˆ))≤K⇒si′=1}, i.e., the set of the random realizations where the cSRP does not modify the bids of the ads displayed when the allocation function {a mathematical formula}f⁎ is applied to the true bids {a mathematical formula}vˆ. Thus we have:{a mathematical formula}  □
     </paragraph>
    </section>
    <section label="Appendix J">
     Proof of social-welfare regret Theorem 12
     <paragraph label="Proof of Theorem 12">
      Step 1: per-step regret. We start computing the per-step regret over the SW during the exploitation phase.First of all we introduce the following definition: {a mathematical formula}S′={s′|s′∈{0,1}N,π(i;f⁎(vˆ))≤K⇒si′=1}, i.e., the set of the random realization where the cSRP does not modify the bids of the ads displayed when the allocation function is {a mathematical formula}f⁎ is applied to the true bids {a mathematical formula}vˆ.We now provide the bound over the regret.{a mathematical formula} We provide a brief intuition of bounds {a mathematical formula}r1 and {a mathematical formula}r2. The bound {a mathematical formula}r1 can be explained noticing that when the bids of the ads displayed in {a mathematical formula}f⁎(vˆ) are not modified we have that {a mathematical formula}α(m;f⁎(vˆ))=α(m;f⁎(x)) where {a mathematical formula}m≤K and x s.t. {a mathematical formula}s∈S′. The bound for {a mathematical formula}r2 can be understood noticing that when the bids of the ads s.t. {a mathematical formula}π(j;f⁎(x))≤K are not modified and {a mathematical formula}xi≤vˆi∀i∈N, we obtain {a mathematical formula}SW˜(f⁎(x),vˆ)=SW˜(f⁎(x),x)≤maxθ∈Θ⁡SW˜(θ,x)=SW˜(f˜(x),x)≤SW˜(f˜(x),vˆ).Step 2: cumulative regret. We can now compute the upper bound for the global regret{a mathematical formula}Step 3: parameter optimization. We first simplify the previous bound as{a mathematical formula}Taking the derivative of the previous bound w.r.t. τ leads to{a mathematical formula} which leads to{a mathematical formula}Once replaced τ in the bound, we obtain{a mathematical formula}Finally, we choose δ and μ to optimize the asymptotic order by setting{a mathematical formula}{a mathematical formula} The final bound is{a mathematical formula} Given that {a mathematical formula}δ&lt;1 this implies that {a mathematical formula}T&gt;N and, given that {a mathematical formula}μ&lt;1 we have that {a mathematical formula}T&gt;NK3. Both the constraints are satisfied imposing {a mathematical formula}T&gt;τ, i.e.,{a mathematical formula}  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>