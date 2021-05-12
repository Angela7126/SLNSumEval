<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Achieving fully proportional representation: Approximability results.
   </title>
   <abstract>
    We study the complexity of (approximate) winner determination under the Monroe and Chamberlin–Courant multiwinner voting rules, which determine the set of representatives by optimizing the total satisfaction or dissatisfaction of the voters with their representatives. The total (dis)satisfaction is calculated either as the sum of individual (dis)satisfactions in the utilitarian case or as the (dis)satisfaction of the worst off voter in the egalitarian case. We provide good approximation algorithms for the satisfaction-based utilitarian versions of the Monroe and Chamberlin–Courant rules, and inapproximability results for the dissatisfaction-based utilitarian versions of these rules and also for all egalitarian cases. Our algorithms are applicable and particularly appealing when voters submit truncated ballots. We provide experimental evaluation of the algorithms both on real-life preference-aggregation data and on synthetic preference data. These experiments show that our simple and fast algorithms can, in many cases, find near-perfect solutions.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      We study the complexity of (approximate) winner determination under the Monroe [40] and Chamberlin–Courant [13] multiwinner voting rules, both of which aim to select a group of candidates that best represent the voters. Multiwinner elections are important both for human societies (e.g., in indirect democracies for electing committees of representatives such as parliaments) and for software multiagent systems (e.g., for recommendation systems [32], [41]), and thus it is important to have good multiwinner rules and good algorithms for them. The Monroe and Chamberlin–Courant rules are particularly appealing because they create an explicit (and, in some sense, optimal) connection between the elected committee members and the voters; each voter knows her representative and each committee member knows to whom she is accountable.
     </paragraph>
     <paragraph>
      We assume that m candidates participate in the election and that the society consists of n voters, each of whom rank the candidates, expressing their preferences about who they would like to see as their representative. When choosing a K-member committee, the Monroe and Chamberlin–Courant rules work as follows. For each voter these rules assign a single candidate as their representative, respecting the following constraints:
     </paragraph>
     <list>
      <list-item label="(a)">
       For the Monroe rule exactly K candidates are assigned to the voters and each selected candidate is assigned to about {a mathematical formula}nK voters (see the definitions in Section 2 for details); for the Chamberlin–Courant rule the number of selected candidates is at most K and there is no restriction on the number of voters each committee member might represent. (The elected committee should take this into account in its operation, e.g., by means of weighted voting.)
      </list-item>
      <list-item label="(b)">
       The candidates are selected and assigned to the voters optimally, either by minimizing the total (societal) dissatisfaction or by maximizing the total (societal) satisfaction (both views are equivalent in terms of optimality of solutions, but—as we will show—are different from the approximability perspective).
      </list-item>
     </list>
     <paragraph>
      The total satisfaction is calculated on the basis of individual satisfactions of the agents. We assume that there is a function {a mathematical formula}α:N→N such that {a mathematical formula}α(i) measures how well a voter is represented by the candidate that this voter ranks as i-th best. This function is the same for each voter. Naturally, it is a decreasing function; a voter is more satisfied with the candidates that she ranks higher. For example, it is typical to use the Borda count scoring function whose satisfaction in case of m candidates is {a mathematical formula}αB,decm(i)=m−i. The dissatisfaction of a voter is calculated analogously, except that we assume that α is an increasing function (a voter is more dissatisfied with the candidates that she ranks lower). The dissatisfaction variant of the Borda count scoring function is {a mathematical formula}αB,incm(i)=i−1.
     </paragraph>
     <paragraph>
      In the utilitarian variants of the rules, the assignment should maximize the total satisfaction (minimize the total dissatisfaction) calculated as the sum of the voters' individual satisfactions (dissatisfactions) with their representatives. In the egalitarian variants, the assignment should maximize the satisfaction (minimize the dissatisfaction) of the worst-off voter.
     </paragraph>
     <paragraph>
      The Monroe and Chamberlin–Courant rules create a useful connection between the voters and their representatives that makes it possible to achieve both the accountability of candidates to the voters, and proportional representation of the views of the voters. Among common multi-winner voting rules, the Monroe and Chamberlin–Courant rules are quite special in having both the aforementioned accountability and proportionality properties simultaneously. For example, First Past the Post system (where the voters are partitioned into districts with a separate single-winner Plurality election in each) can give very disproportionate results (forcing some of the voters to be represented by candidates they dislike). On the other side of the spectrum are the party-list systems, which achieve perfect proportionality. In those systems the voters vote for the parties, and, based on the numbers, each party receives its quota of seats in the parliament, which is filled from a publicly available ordered list of candidates of this party. This process makes the elected candidates feel more accountable to the apparatchiks of their parties than to the voters. We point the readers to the recent book of Pukelsheim [49] for a detailed discussion of such issues.
     </paragraph>
     <paragraph>
      Unfortunately, the Monroe and Chamberlin–Courant rules have one crucial drawback that makes them impractical. It is NP-hard to tell who the winners are! Specifically, NP-hardness of winner determination under the Monroe and Chamberlin–Courant rules was shown by Procaccia et al. [48] and by Lu and Boutilier [32]. Further, Betzler et al. [9] have studied parameterized complexity of winner determination for these rules and, in particular, have shown {a mathematical formula}W[2]-hardness for winner determination parameterized by the size K of the desired committee. Nonetheless, they have also shown XP algorithms for this parameter (an XP algorithm runs in polynomial time provided the parameter is treated as a constant; thus, in other words, Betzler et al. [9] have given a separate polynomial-time algorithm for each fixed size of the committee). It is also possible to compute Chamberlin–Courant winners provided that the voters have either single-peaked preferences [9] or single-crossing preferences [58]. (For the case of the Monroe rule, single-crossing preferences do not help and winner determination remains NP-hard in this case [58]; the complexity for the case of single-peaked preferences remains open.)
     </paragraph>
     <paragraph>
      Lu and Boutilier [32] proposed the use of approximation algorithms as a mean of dealing with hardness of the Chamberlin–Courant rule, and have given the first such algorithm for it. Their procedure outputs an assignment that achieves no less than {a mathematical formula}1−1e≈0.63 fraction of the optimal voter satisfaction. However, the approximation ratio 0.63 here means that it is possible that, on average, each agent is represented by a candidate that this agent prefers to only about 63% of other candidates, even if there is a perfect solution that assigns each agent to her most preferred candidate. Such issues, however, would not occur if we had a constant-factor approximation algorithm minimizing the total dissatisfaction. Indeed, if a perfect solution exists, then the optimal dissatisfaction is zero and a constant-factor approximation algorithm must also output this perfect solution.
     </paragraph>
     <paragraph>
      The use of approximation algorithms in real-life applications requires some discussion. For example, their use is naturally justified in the context of recommendation systems. Here the strive for optimality is not crucial since a good but not optimal recommendation still has useful information and nobody would object if we replaced the exact recommendation with an approximate one (given that the exact one is hard to calculate). For example, Amazon.com may recommend a book on gardening which may not be the best book for you on this topic, but which is still full of useful advice. For such situations, Herbert Simon [55] used the term ‘satisficing,’ instead of optimizing, to explain the behavior of decision makers under circumstances in which an optimal solution cannot be easily determined. On page 129 he wrote: “Evidently, organisms adapt well enough to ‘satisfice’; they do not, in general, ‘optimize’.” The use of approximation algorithms therefore fits well with the human nature.
     </paragraph>
     <paragraph>
      Still, the use of approximation algorithms in elections requires some care. It is conceivable that the electoral commission finds an allocation of voters to candidates with a certain value of (dis)satisfaction and one of the parties participating in the election finds an allocation with a better value. If the commission does not accept such an improved allocation, the society may lose faith in the fairness of the electoral process. There are several ways of handling this possibility. Firstly, an approximation algorithm can be fixed by law. In such a case, it becomes an acting voting rule and a new way to measure fairness in the society (indeed, the results of Caragiannis et al. [11] for the case of Dodgson's rule and of Elkind et al. [19], for one of our approximation algorithms, indicate that approximation algorithms may even have some more desirable axiomatic properties than the voting rules they approximate). Secondly, an electoral commission may calculate the allocation, but also publish the raw data and issue a call for submissions. If, within the period specified by law, nobody can produce a better allocation, then the committee goes ahead and announces the result. If someone produces a better allocation, then the electoral commission uses the latter one. If the electoral commission adopts this approach, then it makes sense to seek randomized approximation algorithms for our rules. While it is hard to imagine that a randomized algorithm would be fixed as an acting voting rule, a group of supporters of a party can certainly try to use it to find an allocation which is more beneficial for the party than the one found by the electoral commission.{sup:1}
     </paragraph>
     <paragraph>
      The use of approximation algorithms is even more natural in elections with partial ballots. Indeed, even an exact algorithm would produce approximate results because the voters provide us with approximate preferences.
     </paragraph>
     <section label="1.1">
      <section-title>
       Our results
      </section-title>
      <paragraph>
       In this paper we focus on the computational complexity of achieving fully proportional representation. Specifically, we are interested in approximation algorithms for winner determination under two fully proportional representation systems—the Monroe system and the Chamberlin–Courant system. Our main conclusion is the following:
      </paragraph>
      <list>
       <list-item>
        Achieving near-perfect proportional representation of the voters (as defined by the Monroe and Chamberlin–Courant rules) is computationally easy both theoretically and practically.
       </list-item>
      </list>
      <paragraph>
       To support this statement, we provide several polynomial-time approximation algorithms, provide guaranteed approximation ratios for them, and evaluate exact approximation ratios empirically. The former depend on two parameters: the number m of alternatives and the size K of the committee to be selected. Our two most important algorithms have the following properties.
      </paragraph>
      <list>
       <list-item label="1.">
        The first algorithm (Algorithm P from Section 4.6) finds a set of K candidates such that, on average, each agent is represented by someone whom she prefers to at least {a mathematical formula}(1−2w(K)K) fraction of the candidates, where w is Lambert's W-function, for which it is known that {a mathematical formula}w(x)=ln⁡x−ln⁡ln⁡x+o(1). We stress that this guarantee holds for every possible profile of (complete) preference orders. This algorithm approximates the Chamberlin–Courant rule.
       </list-item>
       <list-item label="2.">
        The second algorithm (Algorithm A from Section 4.1; see also its improvements, Algorithms B and C) guarantees that each agent is, on average, represented by someone whom she prefers to at least {a mathematical formula}(1−K−12(m−1)−HKK) fraction of the candidates, where {a mathematical formula}HK is the K-th harmonic number. It guarantees that each member of the committee represents roughly the same number of agents.{sup:2} As before, this guarantee holds for every possible profile of (complete) preference orders. This algorithm approximates the Monroe rule.
       </list-item>
      </list>
      <paragraph>
       The guarantees we provide for our algorithms are very strong. For instance, in the Polish parliamentary elections, where {a mathematical formula}K=460 and {a mathematical formula}m≈6000, our algorithms guarantee that each voter will be, on average, represented by a candidate that she prefers to 99% of the candidates (in the case of Algorithm P) and to 96% of the candidates (in the case of Algorithm A). Our experimental data shows that in real-life settings we indeed achieve such high-quality results. Additionally, we show that the algorithms preserve their approximation properties even if we consider truncated ballots, in which agents rank only several most preferred candidates. The fact that our algorithms work well with truncated ballots may be very practically important. When the ballots are truncated, the results of an election are intrinsically approximate since the exact information about preferences of voters is not available. Hence the use of approximation algorithms in this case is even more pertinent.
      </paragraph>
      <paragraph>
       Our paper gives a detailed account of the approximability of the Monroe and Chamberlin–Courant voting rules. Below we provide a more comprehensive summary of our results.
      </paragraph>
      <list>
       <list-item label="1.">
        The utilitarian variants of the Monroe and Chamberlin–Courant rules are hard to approximate up to any constant factor for the dissatisfaction-based cases (see Theorem 1, Theorem 2). These results justify studying the satisfaction-based setting. Constant-factor approximation algorithms for the dissatisfaction-based cases would have been more powerful, but, unless unlikely complexity class collapses occur, they do not exist.
       </list-item>
       <list-item label="2.">
        For the satisfaction-based utilitarian framework we show the following. For the Monroe rule with the Borda scoring function we give a randomized {a mathematical formula}(0.715−ϵ)-approximation algorithm (often, the ratio is much better; see Section 4 and the comment on Algorithm A above). In the case of an arbitrary positional scoring function we give a ({a mathematical formula}1−1e)-approximation algorithm (Theorem 10). For the Chamberlin–Courant rule with the Borda scoring function we give a polynomial-time approximation scheme (that is, for each ϵ, {a mathematical formula}0&lt;ϵ&lt;1, we have a polynomial-time {a mathematical formula}(1−ϵ)-approximation algorithm; see Corollary 13 and the comment on Algorithm P above).
       </list-item>
       <list-item label="3.">
        We provide empirical evaluation of our algorithms for the satisfaction-based utilitarian framework, both on synthetic data and on real-life data. This evaluation shows that in practice our best algorithms achieve at least 0.9 approximation ratios, and even better results are typical (see Section 5).
       </list-item>
       <list-item label="4.">
        We show that our algorithms work very well in the setting where voters do not necessarily rank all the candidates, but only provide truncated ballots, in which they rank several most preferred candidates (usually at least three). We provide theoretical guarantees on the performance of our algorithms (Proposition 6, Proposition 14) as well as empirical evaluation (see Section 5.4).
       </list-item>
       <list-item label="5.">
        We show that egalitarian variants of the Monroe and Chamberlin–Courant rules are hard to approximate up to any constant factor, both for the dissatisfaction-based case and for the satisfaction-based case (see Theorem 15, Theorem 16, Theorem 17, Theorem 19; the discussion of the egalitarian variants is presented in Appendix C).
       </list-item>
      </list>
      <paragraph>
       Our approximability results show that, as long as one is willing to accept approximate solutions, it is possible to use the utilitarian variants of the Monroe and Chamberlin–Courant rules in practice. This view is justified both from the theoretical and from the empirical point of view.
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       The Monroe and Chamberlin–Courant rules belong to the class of social assignment rules as they produce a representative committee and an assignment of voters to candidates. There are other voting rules that can perform this function but only one of them comes close in terms of axiomatic properties. This is the multiwinner Single Transferrable Vote rule (STV). The comparison of various axiomatic properties of multiwinner rules conducted by Elkind et al. [19] shows that variants of STV have many nice properties and, in particular, are rather strong on proportionality. One has to have in mind that a multiwinner STV is not a single rule but a large family of them. A number of different quotas can be used (the most common is the Droop quota). There are also variations, such as in how to transfer surplus votes from winning candidates and whether to transfer votes to already elected candidates (see [59] for the details). Tie-breaking under STV may be challenging and, indeed, there are natural tie-breaking rules that make the winner-determination problem in STV NP-hard [15]. It is still possible that a variant STV can be extended to a useful social assignment rule which may serve as an alternative to the Chamberlin–Courant rule (but not the Monroe one) but this is yet to be done.
      </paragraph>
      <paragraph>
       There is a large body of work related to our research either in terms of motivation, perspective, methodology, or the exact subject of study. For example, in Appendix A we present a resource-allocation view of the Monroe and Chamberlin–Courant rules and, so, our results relate to those on resource-allocation. In terms of formal similarity, the winner determination problem for the Chamberlin–Courant rule can be seen as a close relative of the facility location problem. Finally, other authors have studied the complexity of and the algorithms for Monroe and Chamberlin–Courant voting rules before. Below we review this related literature.
      </paragraph>
      <paragraph>
       Our methodology is similar to that previously used in the study of approximation algorithms for other NP-hard voting rules. These rules include, for example, Dodgson's rule [4], [8], [24], Young's rule [8], [51], and Kemeny's rule [4], [7], [25]. For the single-transferable vote rule (STV), the winner determination problem becomes NP-hard if we use the parallel-universes tie-breaking [15]. Many of these hardness results hold even in the sense of parameterized complexity theory (however, there are also fixed-parameter tractability results; see the references above for the details).
      </paragraph>
      <paragraph>
       The aforementioned hardness results motivated the search for approximation algorithms. There are now very good approximation algorithms for Kemeny's rule [1], [16], [28] and for Dodgson's rule [10], [11], [20], [26], [38]. In both cases the results are, in essence, optimal. For Kemeny's rule there is a polynomial-time approximation scheme [28] (although the running time of this algorithm is not very practical) and for Dodgson's rule the achieved approximation ratio is optimal under standard complexity-theoretic assumptions [10] (unfortunately, the approximation ratio is not constant but depends logarithmically on the number of candidates). On the other hand, for Young's rule it is known that no good approximation algorithms exist [10].
      </paragraph>
      <paragraph>
       The work of Caragiannis et al. [11] and of Faliszewski et al. [20] on approximate winner determination for Dodgson's rule is particularly interesting from our perspective. In the former, the authors advocate treating approximation algorithms for Dodgson's rule as voting rules in their own right and design them to have desirable properties. In the latter, the authors show that a well-established voting rule, the Maximin rule, is a reasonable, though not optimal, approximation of Dodgson's rule. This perspective is important for anyone interested in using approximation algorithms for winner determination in elections and, in particular, for the case of Monroe and Chamberlin–Courant voting rules. For example, Elkind et al. [19] provide a discussion of axiomatic properties of multiwinner voting rules and show that some of our approximation algorithms have more desirable properties than the rules they approximate.
      </paragraph>
      <paragraph>
       The complexity of the winner determination problem for the Monroe and Chamberlin–Courant rules has been considered in several papers. Procaccia, Rosenschein and Zohar [48] were the first to show the hardness of these two rules for the case of a particular approval-style dissatisfaction function. Their results were complemented by Lu and Boutilier [32] who proved the hardness of the Chamberlin–Courant rule for the case of Borda satisfaction function, by Betzler, Slinko and Uhlmann [9] who focused on the parameterized complexity of the rules for both the case of unrestriced voter preferences and the case of single-peaked preferences, by Yu, Chan, and Elkind [61] who considered voters with preferences that are single-peaked on a tree, and by Skowron et al. [58] who considered voters with single-crossing preferences. Further, Lu and Boutilier [32] initiated the study of approximability for the Chamberlin–Courant rule and were the first to use the satisfaction-based framework. Specifically, they gave the greedy {a mathematical formula}(1−1e)-approximation algorithm for the Chamberlin–Courant rule. Lu and Boutilier were motivated by applications to recommendation systems and, in that sense, our view of the rules is quite similar to theirs.
      </paragraph>
      <paragraph>
       In this paper we take the view that the Monroe and Chamberlin–Courant rules are special cases of the following resource allocation problem (presented in Appendix A in more detail). The alternatives are viewed as shareable resources, each with a certain capacity defined as the maximal number of agents that may share this resource. Each agent has preferences over the resources and is entitled in getting exactly one. The goal is to select a predetermined number K of resources and to find an optimal allocation of these resources. This provides a unified framework for the two rules and reveals the connection of proportional representation problems to other resource allocation problems. In particular, it closely resembles multi-unit resource allocation with single-unit demand [54, Chapter 11] (see also the work of Chevaleyre et al. [14] for a survey of the most fundamental issues in the multiagent resource allocation theory) and resource allocation with sharable indivisible goods [2], [14]. Below, we point out other connections of the Monroe and Chamberlin–Courant rules to several other problems. Facility Location Problems.In the facility location problem, there are n customers located in some area and an authority, say a city council, that wants to establish a fixed number K of facilities to serve those customers. Customers incur certain costs (say transportation costs) of using the facilities. Further, establishing a facility may have additional cost, possibly depending on aspects such as the facility's location. The problem is to find K locations for the facilities that would minimize the total cost for the society. If these facilities have unlimited capacities and can serve any number of customers, then each customer would use her most preferred (i.e., closest) facility and the problem is similar to finding the Chamberlin–Courant assignment. If the capacities of the facilities are finite and equal, the problem looks like finding an assignment under the Monroe rule. An essential difference between this problem and the winner determination problem under the Chamberlin–Courant rule are the setup costs and the distance metric. The parameterized complexity of the Facility Location Problem was investigated by Fellows and Fernau [21]. The papers of Procaccia et al. [48] and of Betzler et al. [9] contain a brief discussion of the connection between the Facility Location Problem and the winner determination problem under the Chamberlin–Courant rule. Note that in the context of facility location, it makes sense to look at both the utilitarian setting and at the egalitarian setting. The latter is particularly appealing, for example, when we seek to locate such facilities as fire stations or intensive care units and we want to guarantee a particular level of service to every member of the society.{sup:3}Group Activity Selection Problem.In the group activity selection problem [17] we have a group of agents (say, conference attendees) and a set of activities (say, options that they have for a free afternoon such as a bus city tour or a wine tasting). The agents express preferences regarding the activities and organizers try to allocate agents to activities to maximize their total satisfaction. If the number of agents that can participate in each activity is unrestricted, this reduces to the winner determination problem under the Chamberlin–Courant rule. Similarly, if roughly the same number of agents should participate in each activity, the problem becomes very close to computing the winners under the Monroe rule. The Group Activity Selection Problem is, however, far more general and allows the agents to express quite complicated preferences. For example, an agent might have preferences of the form: “I like wine-tasting best provided that at most 10 people participate in it, and otherwise I prefer a bus city tour provided that at least 15 people participate, and otherwise I prefer to not take part in any activity.” Darmann et al. [17] give some hardness and easiness results for this problem, but its investigation has only started.
      </paragraph>
      <paragraph>
       Finally, we mention that finding winners under the Monroe and Chamberlin–Courant rules can be seen from the perspective of matching theory. One of the closest problems in this context is that of demand matching [52], [56]. We are given a biparite graph {a mathematical formula}G=(U,V;E) and three functions: the profit function {a mathematical formula}π:E→R+, the demand function {a mathematical formula}d:E→R+, and the capacity function {a mathematical formula}b:U∪V→R+. If we write {a mathematical formula}δ(v) to denote the set of edges incident to a vertex v, the goal can be formulated as follows: Find a subset {a mathematical formula}M⊆E that maximizes the profit {a mathematical formula}∑e∈Mπ(e) under the constraint that for each vertex {a mathematical formula}w∈U∪V we have {a mathematical formula}∑e∈M∩δ(w)d(e)≤b(w).
      </paragraph>
      <paragraph>
       Intuitively, the connection of demand matching to our problems is as follows. The vertices on one side, say V, correspond to the agents and for each such vertex v in this group we set {a mathematical formula}b(v)=1. The vertices on the other side, U, correspond to the candidates; under Mondroe rule, for each vertex u on this side we set {a mathematical formula}b(u) to be the number of agents divided by the size of the committee and under Chamberlin–Courant, we set {a mathematical formula}b(u) to be the number of agents. We have a complete bipartite graph, where the profits of the edges are the satisfactions derived by the agents from being represented by the candidates. The significant difference between the winner-determination problems for our two rules and the demand matching problem is that the demand matching does not put constraints on the number of vertices from U involved in the matching (and we need that at most K candidate vertices are involved, where K is the size of the committee to be elected). Also, the profit functions that we focus on are of a very special form. The results of Shepherd and Vetta [52] and of Singh and Wu [56] show that the demand matching problem appears to be much harder to solve (approximately) than our problems. Nonehteless, we believe that exploring the connections between (demand) matching and our problems is a very promising direction.
      </paragraph>
      <paragraph>
       The above connections show that, indeed, the complexity of winner determination under the Monroe and Chamberlin–Courant voting rules is interesting, can lead to progress in several other directions, and may have impact on applications within artificial intelligence.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      We first define basic notions such as preference orders and positional scoring rules. Then we present the formal definitions of the winner determination problems for the Monroe and Chamberlin–Courant voting rules. Finally, we briefly recall relevant notions regarding computational complexity.
     </paragraph>
     <paragraph>
      Preferences. For each {a mathematical formula}n∈N, by {a mathematical formula}[n] we mean {a mathematical formula}{1,…,n}. We assume that there is a set {a mathematical formula}N=[n] of agents and a set {a mathematical formula}A={a1,…,am} of alternatives. Each agent i has a preference order{a mathematical formula}≻i over A, i.e., a strict linear order of the form {a mathematical formula}aπ(1)≻iaπ(2)≻i⋯≻iaπ(m) for some permutation π of {a mathematical formula}[m]. For an alternative a, by {a mathematical formula}posi(a) we mean the position of a in the i-th agent's preference order. For example, if a is the most preferred alternative for i then {a mathematical formula}posi(a)=1, and if a is the least preferred one then {a mathematical formula}posi(a)=m. A collection {a mathematical formula}V=(≻1,…,≻n) of agents' preference orders is called a preference profile.
     </paragraph>
     <paragraph>
      We often include subsets of the alternatives in the descriptions of preference orders. For example, if A is the set of all the alternatives and B is some nonempty strict subset of A, then by {a mathematical formula}B≻A−B we mean that for the preference order ≻ all alternatives in B are preferred to those outside of B.
     </paragraph>
     <paragraph>
      A positional scoring function (PSF) is a function {a mathematical formula}αm:[m]→N. A PSF {a mathematical formula}αm is an increasing positional scoring function (IPSF) if for each {a mathematical formula}i,j∈[m], if {a mathematical formula}i&lt;j then {a mathematical formula}αm(i)&lt;αm(j). Analogously, a PSF {a mathematical formula}αm is a decreasing positional scoring function (DPSF) if for each {a mathematical formula}i,j∈[m], if {a mathematical formula}i&lt;j then {a mathematical formula}αm(i)&gt;αm(j).
     </paragraph>
     <paragraph>
      Intuitively, if {a mathematical formula}βm is an IPSF then {a mathematical formula}βm(i) can represent the dissatisfaction that an agent suffers when assigned to an alternative that is ranked i-th in her preference order. Thus, we assume that for each IPSF {a mathematical formula}βm it holds that {a mathematical formula}βm(1)=0 (an agent is not dissatisfied by her top alternative). Similarly, a DPSF {a mathematical formula}γm measures an agent's satisfaction and we assume that for each DPSF {a mathematical formula}γm it holds that {a mathematical formula}γm(m)=0 (an agent is completely not satisfied with her least desired alternative). Sometimes we write α instead of {a mathematical formula}αm, when it cannot lead to confusion.
     </paragraph>
     <paragraph>
      We will often speak of families α of IPSFs (DPSFs) of the form {a mathematical formula}α=(αm)m∈N, where {a mathematical formula}αm is a PSF on [m], such that:
     </paragraph>
     <list>
      <list-item label="1.">
       For a family of IPSFs it holds that {a mathematical formula}αm+1(i)=αm(i) for all {a mathematical formula}m∈N and {a mathematical formula}i∈[m].
      </list-item>
      <list-item label="2.">
       For a family of DPSFs it holds that {a mathematical formula}αm+1(i+1)=αm(i) for all {a mathematical formula}m∈N and {a mathematical formula}i∈[m].
      </list-item>
     </list>
     <paragraph>
      In other words, we build our families of IPSFs (DPSFs) by appending (prepending) values to functions with smaller domains. To simplify notation, we will refer to such families of IPSFs (DPSFs) as normal IPSFs (normal DPSFs). We assume that each function {a mathematical formula}αm from a family can be computed in polynomial time with respect to m. Indeed, we are particularly interested in the Borda families of IPSFs and DPSFs defined by {a mathematical formula}αB,incm(i)=i−1 and {a mathematical formula}αB,decm(i)=m−i, respectively.
     </paragraph>
     <paragraph>
      Assignment functions. A K-assignment function (or simply K-assignment) is any function {a mathematical formula}Φ:N→A, such that {a mathematical formula}‖Φ(N)‖≤K (that is, it assigns agents to at most K alternatives). A Monroe K-assignment function is an assignment function that additionally satisfies the following cardinality constraint: For each alternative {a mathematical formula}a∈A we have {a mathematical formula}‖Φ(N)‖=K and either {a mathematical formula}⌊‖N‖K⌋≤‖Φ−1(a)‖≤⌈‖N‖K⌉ or {a mathematical formula}‖Φ−1(a)‖=0.
     </paragraph>
     <paragraph>
      We also consider partial assignment functions. A partial K-assignment function is defined in the same way as the regular one, except that it may assign a null alternative, ⊥, to some of the agents. It is convenient to think that for each agent i we have {a mathematical formula}posi(⊥)=m. A partial Monroe K-assignment is a partial K-assignment that can be extended to a regular Monroe K-assignment (that is, a partial Monroe K-assignment can break the cardinality constraints, but it must be possible to extend it in such a way that these constraints are no longer broken). Given an assignment Φ, for each agent i we refer to alternative {a mathematical formula}Φ(i) as the representative of i.
     </paragraph>
     <paragraph>
      Given a normal IPSF (DPSF) α, we consider the following three functions, each assigning a positive integer to a given assignment Φ:{a mathematical formula} These functions aggregate individual dissatisfaction (satisfaction) values of the agents to measure the overall quality of the assignment. In the utilitarian framework, we use the first function, {a mathematical formula}ℓsumα(Φ), as the total (societal) dissatisfaction function in the IPSF case and as the total (societal) satisfaction function in the DPSF case. We use the second and the third functions, respectively, as the total dissatisfaction and satisfaction functions for IPSF and DPSF cases in the egalitarian framework (the egalitarian framework is discussed in Appendix C). We sometimes omit the word “total” if no confusion may arise.
     </paragraph>
     <paragraph>
      The Monroe and Chamberlin–Courant rules. Let us now define the problems of winner determination under the Monroe and Chamberlin–Courant (CC) rules. In both cases the goal is to find an optimal assignment, where the optimality is relative to one of the total dissatisfaction or satisfaction functions that we have just introduced. The former is to be minimized and the latter is to be maximized.
     </paragraph>
     <paragraph label="Definition 1">
      Let α be a normal IPSF. An instance of α-CC-DisWinner problem consists of a set of agents {a mathematical formula}N=[n], a set of alternatives {a mathematical formula}A={a1,…,am}, a preference profile V of the agents, and a positive integer K. We ask for a K-assignment function Φ such that {a mathematical formula}ℓsumα(Φ) is minimized. The problem α-Monroe-DisWinner is defined in the same way but we additionally require Φ to be a Monroe K-assignment function.
     </paragraph>
     <paragraph label="Definition 2">
      Let α be a normal DPSF. The problem α-CC-SatWinner is defined in the same way as α-CC-DisWinner, except that we seek a K-assignment Φ such that {a mathematical formula}ℓsumα(Φ) is maximized. The problem α-Monroe-SatWinner is defined in the same way but we additionally require Φ to be a Monroe K-assignment function.
     </paragraph>
     <paragraph>
      Definition 1, Definition 2 regard the utilitarian variants of the rules: We consider the egalitariant variants in Appendix C. Below we provide an example illustrating the utilitarian variants.
     </paragraph>
     <paragraph label="Example 1">
      Consider a set {a mathematical formula}N={1,2,3,4,5,6} of six agents and a set {a mathematical formula}A={a,b,c,d} of four alternatives. Suppose the agents have the following preference orders:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} and we are looking for a committee of size {a mathematical formula}K=2. Consider the dissatisfaction-based variant of Chamberlin–Courant rule with the Borda dissatisfaction function, {a mathematical formula}αB,inc (i.e., problem {a mathematical formula}αB,inc-CC-DisWinner). In this case, there is a unique optimal K-assignment Φ:{a mathematical formula} Agent 5 ranks her representative on the second position and all the other agents rank their representatives on the first positions. Thus, the aggregated dissatisfaction of the agents is {a mathematical formula}ℓsumαB,inc(Φ)=0+0+0+0+1+0=1. If we considered the satisfaction-based variant of the problem ({a mathematical formula}αB,dec-CC-SatWinner), the assignment would be the same, but with the satisfaction {a mathematical formula}ℓsumαB,dec(Φ)=3+3+3+3+2+3=17.On the other hand, consider the dissatisfaction variant of the Monroe rule, that is, problem {a mathematical formula}αB,inc-Monroe-DisWinner. In this case we are looking for a Monroe K-assignment function, so each alternative who is a representative has to represent exactly three agents. The following assignment function, {a mathematical formula}Φ′, is optimal:{a mathematical formula} The aggregated dissatisfaction is {a mathematical formula}ℓsumαB,inc(Φ′)=0+1+0+0+1+0=2. In the satisfaction based variant the same assignment is optimal, and its satisfaction is {a mathematical formula}ℓsumαB,dec(Φ′)=3+2+3+3+2+3=16.
     </paragraph>
     <paragraph>
      As is clearly visible in the above example, in terms of exact solutions our satisfaction-based problems are equivalent to the dissatisfaction-based ones (indeed, one can always transform an IPSF to an equivalent DPSF and vice versa). However, as we will see, these two families of problems behave differently in terms of their approximability.
     </paragraph>
     <paragraph>
      The goal in our problems is to compute a particular (Monroe) K-assignment. Naturally, such an assignment defines a set of K alternatives, who are viewed as the winners of the given multiwinner election. In this paper we make the following assumption.
     </paragraph>
     <paragraph label="Assumption">
      We assume that the size K of the committee that we seek always divides the number n of the agents.
     </paragraph>
     <paragraph>
      Note that while this assumption looks very innocent at first, in fact in many related settings it can be crucial. For example, Elkind et al. [19] have shown that the Monroe rule satisfies homogeneity property when K divides the number of agents, but fails it in general. Nonetheless, this assumption does not affect our hardness proofs at all, and one can verify that all our approximation algorithms also work when it is not satisfied. However, this assumption simplifies the presentation.
     </paragraph>
     <paragraph>
      For each subset of the alternatives {a mathematical formula}S⊆A such that {a mathematical formula}‖S‖≤K, we write {a mathematical formula}ΦαS to denote the partial (Monroe) K-assignment that assigns agents only to the alternatives from S and such that {a mathematical formula}ΦαS maximizes the utilitarian satisfaction {a mathematical formula}ℓsumα(ΦαS). (We introduce this notation only for the utilitarian satisfaction-based setting because it is useful to express appropriate algorithms for this case. For other settings we only have hardness results and this notation would not be useful. Whether we mean a K-assignment or a Monroe K-assignment will always be clear from the context.)
     </paragraph>
     <paragraph>
      Computational Issues. For many normal IPSFs α and, in particular, for the Borda IPSF, our problems are NP-hard [9], [48]. Thus we seek approximate solutions.
     </paragraph>
     <paragraph label="Definition 3">
      Let r be a real number such that {a mathematical formula}r≥1, let α be a normal IPSF (or, let α be a normal DPSF and let r be such that {a mathematical formula}0&lt;r≤1), and let {a mathematical formula}R be either Monroe or CC. An algorithm is an r-approximation algorithm for α-{a mathematical formula}R-DisWinner problem (for α-{a mathematical formula}R-SatWinner problem) if on each instance I it returns a feasible assignment Φ such that {a mathematical formula}ℓsumα(Φ)≤r⋅OPT (such that {a mathematical formula}ℓsumα(Φ)≥r⋅OPT), where OPT is the optimal total dissatisfaction (satisfaction) {a mathematical formula}ℓsumα(ΦOPT).
     </paragraph>
     <paragraph label="Example 2">
      Let us once again analyze the setting from Example 1. Consider the dissatisfaction-based variant of Chamberlin–Courant rule and the following assignment:{a mathematical formula} (Note that this is the best K-assignment function if both b and c are to be the representatives; also, this assignment happens to be a Monroe 2-assignment.) The total dissatisfaction of the agents is {a mathematical formula}ℓsumαB,inc(Φ″)=1+1+2+1+0+0=4. Since the optimal dissatisfaction is 1, this is a 4-approximate solution for {a mathematical formula}αB,inc-CC-DisWinner. (For the case of Monroe the optimal dissatisfaction is 2, so this is also a 2-approximate solution for {a mathematical formula}αB,inc-Monroe-DisWinner.)On the other hand, consider the satisfaction-based setting. The optimal satisfaction of the voters is 17 but under {a mathematical formula}Φ″ the satisfaction is {a mathematical formula}ℓsumαB,dec(Φ″)=2+2+1+2+3+3=13. That is, {a mathematical formula}Φ″ is a 0.76-approximate solution for {a mathematical formula}αB,dec-CC-SatWinner (and, since the optimal satisfaction for the case of Monroe is 16, this is a 0.81-approximate solution for {a mathematical formula}αB,dec-Monroe-SatWinner).
     </paragraph>
     <paragraph>
      Lu and Boutilier [32] gave a {a mathematical formula}(1−1e)-approximation algorithm for the CC-SatWinner family of problems. Throughout this paper, for each of our problems we either prove inapproximability with respect to any constant r (under standard complexity-theoretic assumptions) or we present an approximation algorithm. In our inapproximability proofs, we use the following two classic NP-complete problems [23].
     </paragraph>
     <paragraph label="Definition 4">
      An instance I of Set-Cover consists of set {a mathematical formula}U=[n] (called the ground set), family {a mathematical formula}F={F1,F2,…,Fm} of subsets of U, and positive integer K. We ask if there exists a set {a mathematical formula}J⊆[m] such that {a mathematical formula}‖J‖≤K and {a mathematical formula}⋃j∈JFj=U.
     </paragraph>
     <paragraph label="Definition 5">
      X3C is a variant of Set-Cover where {a mathematical formula}‖U‖ is divisible by 3, each member of {a mathematical formula}F has exactly three elements, and {a mathematical formula}K=‖U‖3. (Since K is defined implicitly, an X3C instance consists only of the set U and the family {a mathematical formula}F.)
     </paragraph>
     <paragraph>
      Set-Cover remains NP-complete even if we restrict each member of U to be contained in at most two sets from {a mathematical formula}F (it suffices to note that this restriction is satisfied by Vertex-Cover, which is a special case of Set-Cover). X3C remains NP-complete even if we additionally assume that n is divisible by 2 and each member of U appears in at most 3 sets from {a mathematical formula}F[23].
     </paragraph>
     <paragraph>
      We also use results from the theory of parameterized complexity developed by Downey and Fellows [18]. This theory allows one to single out a particular parameter, say k, and analyze its ‘contribution’ to the overall complexity of the problem. An analogue of the class P here is the class FPT which contains problems that can be solved in time {a mathematical formula}f(k)nO(1), where n is the size of the input instance and f is some computable function. The class of problems that can be solved in polynomial time provided the value of the parameter is fixed is called XP; note that {a mathematical formula}FPT⊆XP. Parameterized complexity theory also operates with classes {a mathematical formula}W[1]⊆W[2]⊆⋯ which are believed to form a hierarchy of classes of hard problems (combined, they are analogous to the class NP). It holds that {a mathematical formula}FPT⊆W[1], but it seems unlikely that {a mathematical formula}FPT=W[1], let alone {a mathematical formula}FPT=W[2]. We point the reader to the books of Niedermeier [44] and Flum and Grohe [22] for detailed overviews of parametrized complexity theory. Interestingly, while both Set-Cover and Vertex-Cover are NP-complete, the former is {a mathematical formula}W[2]-complete and the latter belongs to FPT (see, e.g., the book of Niedermeier [44] for these now-standard results and their history).
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Hardness of approximation
     </section-title>
     <paragraph>
      We now present our inapproximability results for the Monroe and Chamberlin–Courant rules in the dissatisfaction-based utilitarian case. We show similar inapproximability results for the egalitarian variants of our rules in Appendix C.
     </paragraph>
     <paragraph label="Theorem 1">
      For each normal IPSF α and each constant factor{a mathematical formula}r&gt;1, there is no polynomial-time r-approximation algorithm for α-Monroe-DisWinnerunless{a mathematical formula}P=NP.
     </paragraph>
     <paragraph label="Proof">
      Let us fix a normal IPSF α and let us assume, aiming at getting a contradiction, that there is some constant {a mathematical formula}r&gt;1 and a polynomial-time r-approximation algorithm {a mathematical formula}A for α-Monroe-DisWinner.Let I be an instance of X3C with a ground set {a mathematical formula}U=[n] and a family {a mathematical formula}F={F1,F2,…,Fm} of 3-element subsets of U. Without loss of generality, we assume that n is divisible by both 2 and 3 and that each member of U appears in at most 3 sets from {a mathematical formula}F.Using I, we build an instance {a mathematical formula}IM of α-Monroe-DisWinner as follows. We set {a mathematical formula}N=U (that is, the elements of the ground set are the agents) and we set {a mathematical formula}A=A1∪A2, where {a mathematical formula}A1={a1,…,am} is a set of alternatives corresponding to the sets from the family {a mathematical formula}F, and {a mathematical formula}A2 is a set of dummy alternatives of cardinality {a mathematical formula}‖A2‖=12n2r⋅α(3), needed for the construction. We let {a mathematical formula}m′=‖A2‖ and rename the alternatives in {a mathematical formula}A2 so that {a mathematical formula}A2={b1,…,bm′}. We set {a mathematical formula}K=n3.We build agents' preference orders using the following algorithm. For each {a mathematical formula}j∈N, set {a mathematical formula}Mf(j)={ai|j∈Fi} and {a mathematical formula}Ml={ai|j∉Fi}. Set {a mathematical formula}mf(j)=‖Mf(j)‖ and {a mathematical formula}ml(j)=‖Ml(j)‖. As the frequency of the elements from U is bounded by 3, we have {a mathematical formula}mf(j)≤3. For each agent j we set her preference order to be of the form {a mathematical formula}Mf(j)≻jA2≻jMl(j), where the alternatives in {a mathematical formula}Mf(j) and {a mathematical formula}Ml(j) are ranked in an arbitrary way and the alternatives from {a mathematical formula}A2 are placed at positions {a mathematical formula}mf(j)+1,…,mf(j)+m′ in the way described below (see Fig. 1 for a high-level illustration of the construction).We place the alternatives from {a mathematical formula}A2 in the preference orders of the agents in such a way that for each alternative {a mathematical formula}bi∈A2 there are at most two agents that rank {a mathematical formula}bi among their {a mathematical formula}nr⋅α(3) top alternatives. The following construction achieves this effect. If {a mathematical formula}(i+j)modn&lt;2, then alternative {a mathematical formula}bi is placed at one of the positions {a mathematical formula}mf(j)+1,…,mf(j)+nr⋅α(3) in j's preference order. Otherwise, {a mathematical formula}bi is placed at a position with index higher than {a mathematical formula}mf(j)+nr⋅α(3) (and, thus, at a position with index higher than {a mathematical formula}nr⋅α(3)). This construction can be implemented because for each agent j there are exactly {a mathematical formula}m′⋅2n=nr⋅α(3) alternatives {a mathematical formula}bi1,bi2,…,binrα(3) such that {a mathematical formula}(it+j)modn&lt;2, where {a mathematical formula}t∈[nrα(3)].Let Φ be an assignment computed by {a mathematical formula}A on {a mathematical formula}IM. We will show that {a mathematical formula}ℓsumα(Φ)≤n⋅α(3)⋅r if and only if I is a yes-instance of X3C.(⇐) If there exists a solution for I (i.e., an exact cover of U with {a mathematical formula}n3 sets from {a mathematical formula}F), then we can easily show an assignment in which each agent j is assigned to an alternative from the top {a mathematical formula}mf(j) positions of her preference order (namely, one that assigns each agent j to the alternative {a mathematical formula}ai∈A1 that corresponds to the set {a mathematical formula}Fi, from the exact cover of U, that contains j). Thus, for the optimal assignment {a mathematical formula}ΦOPT it holds that {a mathematical formula}ℓsumα(ΦOPT)≤α(3)⋅n. In consequence, since {a mathematical formula}A is an r-approximation algorithm, it must return an assignment with the total dissatisfaction at most {a mathematical formula}nr⋅α(3).(⇒) Let us now consider the opposite direction. We assume that {a mathematical formula}A found an assignment Φ such that {a mathematical formula}ℓsumα(Φ)≤nr⋅α(3) and we will show that I is a yes-instance of X3C. Since we require each alternative to be assigned to either 0 or 3 agents, if some alternative {a mathematical formula}bi from {a mathematical formula}A2 were assigned to some 3 agents, at least one of them would rank {a mathematical formula}bi at a position worse than {a mathematical formula}nr⋅α(3). This would mean that {a mathematical formula}ℓsumα(Φ)≥nr⋅α(3)+1. Analogously, no agent j can be assigned to an alternative that is placed at one of the {a mathematical formula}ml(j) bottom positions of j's preference order. Thus, only the alternatives in {a mathematical formula}A1 have agents assigned to them and, further, if agents {a mathematical formula}x,y,z, are assigned to some {a mathematical formula}ai∈A1, then it holds that {a mathematical formula}Fi={x,y,z} (recall that {a mathematical formula}Fi is a set from the input X3C instance; we will call each set {a mathematical formula}Fi for which alternative {a mathematical formula}ai is assigned to some agents {a mathematical formula}x,y,zselected). Since each agent is assigned to exactly one alternative, the selected sets are disjoint. Since the number of selected sets is {a mathematical formula}K=n3, it must be the case that the selected sets form an exact cover of U. Thus, I is a yes-instance of X3C.  □
     </paragraph>
     <paragraph>
      One may wonder if hardness of approximation for α-Monroe-DisWinner is not an artifact of the strict requirements regarding the number of chosen candidates. It turns out that unless {a mathematical formula}P=NP, then for each {a mathematical formula}r,s&gt;1 there is no {a mathematical formula}(r,s)-approximation algorithm that finds an assignment with the following properties: (1) the aggregated dissatisfaction {a mathematical formula}ℓsumα(Φ) is at most r times higher than the optimal one, (2) the number of alternatives to which agents are assigned is at most sK and (3) each selected alternative (i.e., each alternative that has agents assigned), is assigned to no more than {a mathematical formula}snK and no less than {a mathematical formula}1snK agents. (The proof is similar to the one used for Theorem 1.) Thus, in our further study we do not consider such relaxations of the problem.
     </paragraph>
     <paragraph>
      A result analogous to Theorem 1 also holds for the CC-DisWinner family of problems.
     </paragraph>
     <paragraph label="Theorem 2">
      For each normal IPSF α and each constant factor{a mathematical formula}r&gt;1, there is no polynomial-time r-approximation algorithm for α-CC-DisWinnerunless{a mathematical formula}P=NP.
     </paragraph>
     <paragraph label="Proof">
      The proof is in Appendix D.  □
     </paragraph>
     <paragraph>
      The above results show that the task of computing winner sets with aggregated voter dissatisfaction close to the optimal one is computationally hard both for the Monroe and Chamberlin–Courant rules. On the other hand, if we focus on agents' total satisfaction then polynomial-time constant-factor approximation algorithms exist in many cases (see, e.g., the work of Lu and Boutilier [32] and the next section).
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Algorithms for the utilitarian, satisfaction-based cases
     </section-title>
     <paragraph>
      We now turn to approximation algorithms for the Monroe and Chamberlin–Courant multiwinner voting rules in the satisfaction-based framework. Indeed, if one focuses on agents' total satisfaction then it is possible to obtain high-quality approximation results. In particular, we show the first nontrivial (randomized) approximation algorithm for {a mathematical formula}αB,dec-Monroe-SatWinner (recall that {a mathematical formula}αB,dec is the Borda family of DPSFs; for the case of m candidates, we have {a mathematical formula}αB,decm(i)=m−i). We show that for each {a mathematical formula}ϵ&gt;0 we can provide a randomized polynomial-time algorithm that achieves {a mathematical formula}0.715−ϵ approximation ratio; the algorithm usually achieves even a better approximation. For the case of arbitrarily selected DPSF we show a {a mathematical formula}(1−1e)-approximation algorithm. Finally, we present the first polynomial-time approximation scheme (PTAS) for {a mathematical formula}αB,dec-CC-SatWinner. These results stand in sharp contrast to those from the previous section, where we have shown that approximation is hard for the dissatisfaction-based framework.
     </paragraph>
     <paragraph>
      The core difficulty in computing the winners under the Monroe and Chamberlin–Courant rules is in selecting the alternatives that should be assigned to the agents. Given a preference profile and a set S of up to K alternatives, using the standard network-flow argument, it is easy to find a (possibly partial) optimal assignment {a mathematical formula}ΦαS of the agents to the alternatives from S.
     </paragraph>
     <paragraph label="Proposition 3">
      (Implicit in the paper of Betzler et al.[9].) Let α be a normal DPSF, N be a set of agents, A be a set of alternatives, V be a preference profile of N over A, and S a K-element subset of A (where K divides{a mathematical formula}‖N‖). Then there is a polynomial-time algorithm that computes a (possibly partial) optimal K-assignment{a mathematical formula}ΦαS(Monroe K-assignment{a mathematical formula}ΦαS) of the agents to the alternatives from S.
     </paragraph>
     <paragraph>
      Note that for the case of the Chamberlin–Courant rule the algorithm from the above proposition can be greatly simplified: To each voter we assign the candidate that she ranks highest among those from S. For the case of Monroe, unfortunately, we need the expensive, though still polynomial-time, network-flow-based approach. Nonetheless, Proposition 3 allows us to focus on the issue of selecting the winning alternatives and not on the issue of matching them to the agents.
     </paragraph>
     <paragraph>
      Below we describe our algorithms for {a mathematical formula}αB,dec-Monroe-SatWinner and for {a mathematical formula}αB,dec-CC-SatWinner. Formally speaking, every approximation algorithm for {a mathematical formula}αB,dec-Monroe-SatWinner also gives feasible results for {a mathematical formula}αB,dec-CC-SatWinner. However, some of our algorithms are particularly well-suited for both problems and some are tailored to only one of them. Thus, for each algorithm we clearly indicate if it is meant only for the case of Monroe, only for the case of Chamberlin–Courant, or if it naturally works for both systems.
     </paragraph>
     <section label="4.1">
      <section-title>
       Algorithm A (Monroe)
      </section-title>
      <paragraph>
       Perhaps the most natural approach to solve {a mathematical formula}αB,dec-Monroe-SatWinner is to build a solution iteratively: In each step we pick some not-yet-assigned alternative {a mathematical formula}ai (using some criterion) and assign it to those {a mathematical formula}nK agents that (a) are not assigned to any other alternative yet, and (b) whose satisfaction of being matched with {a mathematical formula}ai is maximal. It turns out that this idea, implemented formally as Algorithm A (see pseudocode in Fig. 2), works very well in many cases. We provide a lower bound on the total satisfaction it guarantees in the next lemma. We remind the reader that the j-th harmonic number{a mathematical formula}Hj=∑i=1j1i has asymptotics {a mathematical formula}Hj=Θ(log⁡j).
      </paragraph>
      <paragraph label="Lemma 4">
       For every preference profile, Algorithm A returns a solution in which each agent is, on average, represented by an alternative that she prefers to at least{a mathematical formula}(1−K−12(m−1)−HKK)fraction of the alternatives.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}n=‖N‖. When {a mathematical formula}K≤2, our algorithm computes an optimal solution exactly so we assume that {a mathematical formula}K≥3. Let us consider the situation in the algorithm after the i-th iteration of the outer loop (we have {a mathematical formula}i=0 if no iteration has been executed yet). So far, the algorithm has picked i alternatives and assigned them to {a mathematical formula}inK agents (recall that for simplicity we assume that K divides n evenly). Hence, each agent has {a mathematical formula}⌈m−iK−i⌉ unassigned alternatives among her {a mathematical formula}i+⌈m−iK−i⌉ top-ranked alternatives. By the pigeonhole principle, this means that there is an unassigned alternative {a mathematical formula}aℓ who is ranked among the top {a mathematical formula}i+⌈m−iK−i⌉ positions by at least {a mathematical formula}nK agents. To see this, note that there are {a mathematical formula}(n−inK)⌈m−iK−i⌉ slots for unassigned alternatives among the top {a mathematical formula}i+⌈m−iK−i⌉ positions in the preference orders of unassigned agents, and that there are {a mathematical formula}m−i unassigned alternatives. As a result, there must be an alternative {a mathematical formula}aℓ for whom the number of agents that rank him or her among the top {a mathematical formula}i+⌈m−iK−i⌉ positions is at least:{a mathematical formula} In consequence, the {a mathematical formula}nK agents assigned in the next step of the algorithm will have the total satisfaction at least {a mathematical formula}nK⋅(m−i−⌈m−iK−i⌉). Thus, summing over the K iterations, the total satisfaction guaranteed by the assignment Φ computed by Algorithm A is at least the following value: (to derive the fifth line from the fourth one we note that {a mathematical formula}K(HK−1)−HK≥0 when {a mathematical formula}K≥3):{a mathematical formula} This completes the proof.  □
      </paragraph>
      <paragraph>
       The relation between m, the ratio {a mathematical formula}K/m, and the guarantee of satisfaction of an average voter is depicted in Fig. 3.
      </paragraph>
      <paragraph label="Corollary 5">
       Algorithm A is a polynomial-time{a mathematical formula}(1−K−12(m−1)−HKK)-approximation algorithm for{a mathematical formula}αB,dec-Monroe-SatWinner.
      </paragraph>
      <paragraph label="Proof">
       If each agent were assigned to her top alternative, the total satisfaction would be equal to {a mathematical formula}(m−1)n. Thus, by applying Lemma 4 we get the following bound:{a mathematical formula}  □
      </paragraph>
      <paragraph>
       Note that in the above proof we measure the quality of our assignment against a, perhaps-impossible, perfect solution, where each agent is assigned to her top alternative. This means that for relatively large m and K, and small {a mathematical formula}Km ratio, the algorithm can achieve a close-to-ideal solution irrespective of the voters' preference orders. We believe that this is an argument in favor of using Monroe's system in multiwinner elections. On the flip side, to obtain a better approximation ratio, we would have to use a more involved bound on the quality of the optimal solution. To see that this is the case, form an instance I of {a mathematical formula}αB,dec-Monroe-SatWinner with n agents and m alternatives, where all the agents have the same preference order, and where we seek to elect K candidates (and where K divides n). It is easy to see that each solution that assigns the K universally top-ranked alternatives to the agents is optimal. Thus the total dissatisfaction of the agents in the optimal solution is:{a mathematical formula} By taking large enough m and K (even for a fixed value of {a mathematical formula}mK), the fraction {a mathematical formula}1−K−12(m−1) can be arbitrarily close to the approximation ratio of our algorithm (the reasoning here is somewhat in the spirit of the idea of identifying maximally robust elections, as studied by Shiryaev, Yu, and Elkind [53]).
      </paragraph>
      <paragraph>
       For small values of K, it is possible that the {a mathematical formula}HKK part of our approximation ratio would dominate the {a mathematical formula}K−12(m−1) part. In such cases we can use the result of Betzler et al. [9], who showed that for each fixed constant K, {a mathematical formula}αB,dec-Monroe-SatWinner can be solved in polynomial time. Thus, for the finite number of cases, where {a mathematical formula}HKK is too large, we can solve the problem optimally using their algorithm. In consequence, the quality of the solution produced by Algorithm A most strongly depends on the ratio {a mathematical formula}K−12(m−1). In most cases we can expect it to be small. For example, in Polish parliamentary elections {a mathematical formula}K=460 and {a mathematical formula}m≈6000; in this case the greedy algorithm's approximation ratio is about 0.96. Put differently, in this case our algorithm guarantees to provide a solution in which each voter is, on average, represented by a candidate that she prefers to at least 96% of the candidates.
      </paragraph>
      <paragraph>
       Our algorithm has one more great advantage: Since it focuses on the top parts of voters' preference orders, it can achieve very good results even if the voters submit truncated ballots (that is, if they rank some of their top alternatives only).{sup:4} Below we present the formal analysis of the algorithm's approximation ratio for this case. Unfortunately, we did not obtain a closed form formula and, instead, we present the guaranteed approximation ratio as a sum, in Proposition 6 below. We also present the relation between the fraction of the top alternatives ranked by each of the voters and the approximation ratio for few values of m and K in Fig. 4.
      </paragraph>
      <paragraph label="Proposition 6">
       Let P be the number of top positions in the agents' preference orders that are known by the algorithm. In this case Algorithm A returns a solution in which each agent is, on average, represented by an alternative that she prefers to at least r fraction of the alternatives (in particular, this algorithm is a polynomial-time r-approximation algorithm for{a mathematical formula}αB,dec-Monroe-SatWinner), where:{a mathematical formula}and{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       The proof is in Appendix D.  □
      </paragraph>
      <paragraph>
       For example, for the case of Polish parliamentary elections ({a mathematical formula}K=460 and {a mathematical formula}m=6000), to achieve {a mathematical formula}90% of voters' optimal satisfaction, each voter would have to rank about {a mathematical formula}8.7% of the candidates. Of course, {a mathematical formula}8.7% of 6000 candidates is still over 500. It is too much for the algorithm to be directly useful in these elections, but it indicates the power of truncated ballots. Extending our approach to further limit the number of candidates each voter has to rank is an important open issue. We stress again that our results give even stronger guarantees than just an approximation. For instance, in our example, if each voter ranks about {a mathematical formula}8.7% of the candidates then, independently of the agents' preferences, on average each agent will be represented by someone who she prefers to {a mathematical formula}90% of the candidates.
      </paragraph>
      <paragraph>
       Our results show that for most settings there is very little reason to ask the agents to rank all the alternatives. Using Proposition 6, election designers can estimate how many alternatives the agents should rank to obtain a particular level of satisfaction and, since computing preference orders can be expensive for the agents, this can save a large amount of effort.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Algorithm B (Monroe)
      </section-title>
      <paragraph>
       There are simple ways in which we can improve the quality of the assignment Φ produced by Algorithm A. For example, we can keep the elected committee {a mathematical formula}S=Φ(N) but optimally reassign the alternatives to the voters using the algorithm in Proposition 3 obtaining the assignment {a mathematical formula}ΦαS. This is exactly what our Algorithm B is doing. As shown in Section 5, this very simple trick turns out to noticeably improve the results of the Algorithm A in practice (and, of course, the theoretical approximation guarantees of Algorithm A carry over to Algorithm B).
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Algorithm C (Monroe, CC)
      </section-title>
      <paragraph>
       Algorithm C is a further heuristic improvement over Algorithm B. This time the idea is that instead of keeping only one partial function Φ that is iteratively extended up to the full assignment, we keep a list of up to d partial assignment functions, where d is a parameter of the algorithm. At each iteration, for each assignment function Φ among the d stored ones and for each alternative a to which Φ has not assigned agents yet, we compute an optimal extension of this Φ that assigns agents to a. As a result we obtain possibly more than d (partial) assignment functions. For the next iteration we keep those d that give highest satisfaction.
      </paragraph>
      <paragraph>
       We provide pseudocode for Algorithm C in Fig. 5. If we take {a mathematical formula}d=1, we obtain Algorithm B. If we also disregard the last two lines prior to returning the solution, we obtain Algorithm A.
      </paragraph>
      <paragraph>
       Algorithm C can also be adapted for the Chamberlin–Courant rule. The only difference concerns creating the assignment functions: we replace the contents of the first foreach loop with the following code:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Note that, for the case of the Chamberlin–Courant rule, Algorithm C can also be seen as a generalization of Algorithm GM that we discuss in Section 4.5.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Algorithm R (Monroe, CC)
      </section-title>
      <paragraph>
       Algorithms A, B and C achieve very high approximation ratios for the cases where K is small relative to m. For the remaining cases, where K and m are comparable, we can use a sampling-based randomized algorithm (denoted as Algorithm R) described below. We focus on the case of Monroe and we briefly mention the case of CC at the end.
      </paragraph>
      <paragraph>
       The idea of this algorithm is to randomly pick K alternatives and match them optimally to the agents, using Proposition 3. Naturally, such an algorithm might be very unlucky and pick K alternatives that all of the agents rank low. Yet, if K is comparable to m then it is likely that such a random sample would include a large chunk of some optimal solution. In the lemma below, we assess the expected satisfaction obtained with a single sampling step (relative to the satisfaction given by the optimal solution) and the probability that a single sampling step gives satisfaction close to the expected one. Naturally, in practice one should try several sampling steps and pick the one with the highest satisfaction.
      </paragraph>
      <paragraph label="Lemma 7">
       A single sampling step of the randomized algorithm for{a mathematical formula}αB,dec-Monroe-SatWinnerachieves expected approximation ratio of{a mathematical formula}12(1+Km−K2m2−m+K3m3−m2). Let{a mathematical formula}pϵdenote the probability that the relative difference between the expected total satisfaction and the obtained total satisfaction is higher than ϵ. Then we have{a mathematical formula}pϵ≤11+ϵ.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}N=[n] be the set of agents, {a mathematical formula}A={a1,…,am} be the set of alternatives, and V be the preference profile of the agents. Let us fix some optimal solution {a mathematical formula}Φopt and let {a mathematical formula}Aopt be the set of alternatives assigned to the agents in this solution. For each {a mathematical formula}ai∈Aopt, we write {a mathematical formula}sat(ai) to denote the total satisfaction of the agents assigned to {a mathematical formula}ai in {a mathematical formula}Φopt. Naturally, we have {a mathematical formula}∑a∈Aoptsat(a)=OPT. In a single sampling step, we choose uniformly at random a K-element subset B of A. Then, we form a solution {a mathematical formula}ΦB by matching the alternatives in B optimally to the agents (via Proposition 3). We write {a mathematical formula}Kopt to denote the random variable equal to {a mathematical formula}‖Aopt∩B‖, the number of sampled alternatives that belong to {a mathematical formula}Aopt. We define {a mathematical formula}pi=Pr⁡(Kopt=i) to be the probability that B contains i alternatives from {a mathematical formula}Aopt. For each {a mathematical formula}j∈{1,…,K}, we write {a mathematical formula}Xj to denote the random variable equal to the total satisfaction of the agents assigned to the j-th alternative from the sample. We claim that for each i, {a mathematical formula}0≤i≤K, it holds that:{a mathematical formula} Why is this so? Given a sample B that contains i members of {a mathematical formula}Aopt, our algorithm's solution is at least as good as a solution that matches the alternatives from {a mathematical formula}B∩Aopt in the same way as {a mathematical formula}Φopt, and the alternatives from {a mathematical formula}B−Aopt in a random manner. Since {a mathematical formula}Kopt=i and each {a mathematical formula}aj∈Aopt has equal probability of being in the sample, it is easy to see that the expected value of {a mathematical formula}∑aj∈B∩Aoptsat(aj) is {a mathematical formula}iKOPT. After we allocate the agents from {a mathematical formula}B∩Aopt, each of the remaining, unassigned agents has {a mathematical formula}m−i positions in her preference order where she ranks the agents from {a mathematical formula}A−Aopt. For each unassigned agent, the average score value associated with these positions is at least {a mathematical formula}m−i−12 (this is so, because in the worst case the agent could rank the alternatives from {a mathematical formula}B∩Aopt in the top i positions). There are {a mathematical formula}(n−inK) agents that are not yet assigned, and so the expected total satisfaction from assigning them randomly to the alternatives is {a mathematical formula}m−i−12⋅(n−inK). This proves our bound on the expected satisfaction of a solution yielded by optimally matching a random sample of K alternatives.Since OPT is upper bounded by {a mathematical formula}(m−1)n (consider a possibly-nonexistent solution where every agent is assigned to his or her top preference), we get that:{a mathematical formula} We can compute the unconditional expected satisfaction of {a mathematical formula}ΦB as follows:{a mathematical formula} Since {a mathematical formula}∑i=1Kpi⋅i is the expected value of {a mathematical formula}Kopt, we have that {a mathematical formula}∑i=1Kpi⋅i=K2m (one can think of summing the expected values of K indicator random variables; one for each element of {a mathematical formula}Aopt, taking the value 1 if a given alternative is selected and taking the value 0 otherwise). Further, from the generalized mean inequality we obtain {a mathematical formula}∑i=1Kpi⋅i2≥(K2m)2. In consequence, through routine calculation, we get that:{a mathematical formula}It remains to assess the probability that the total satisfaction obtained through {a mathematical formula}ΦB is close to its expected value. By the definition in the statement of the theorem, we have:{a mathematical formula} We define random variable Y, which with probability {a mathematical formula}pϵ has value {a mathematical formula}(1−ϵ)E(∑j=1KXj) and with probability {a mathematical formula}1−pϵ has value OPT. Since the value of {a mathematical formula}∑j=1KXj is smaller or equal to OPT with probability 1, and by the definition of {a mathematical formula}pϵ, it must hold that {a mathematical formula}E(Y)≥E(∑j=1KXj). After substituting the exact formula for {a mathematical formula}E(Y) in this inequality, it becomes:{a mathematical formula} Since {a mathematical formula}E(∑j=1KXj)≥OPT2, we get:{a mathematical formula} From which we get that {a mathematical formula}pϵ≤11+ϵ. This completes the proof.  □
      </paragraph>
      <paragraph>
       In the next theorem we show that to have a high chance of obtaining a high quality assignment, we need to repeat the sampling step many times. Thus, for practical purposes, by Algorithm R we mean an algorithm that repeats the sampling process a given number of times (this parameter is given as input) and returns the best solution found (the assignment is created using Proposition 3).
      </paragraph>
      <paragraph>
       The relation between the ratio {a mathematical formula}K/m and the expected approximation guarantee of Algorithm R is depicted in Fig. 6.
      </paragraph>
      <paragraph>
       The threshold for {a mathematical formula}Km, where the sampling step is (in expectation) better than the greedy algorithm is about 0.57. Thus, by combining Algorithm R and Algorithm A, we can guarantee an expected approximation ratio of {a mathematical formula}0.715−ϵ, for each fixed constant ϵ. We give the pseudocode for the combination of the two algorithms (Algorithm AR) in Fig. 7.
      </paragraph>
      <paragraph label="Theorem 8">
       For each fixed ϵ, Algorithm AR provides a{a mathematical formula}(0.715−ϵ)-approximate solution for the problem{a mathematical formula}αB,dec-Monroe-SatWinnerwith probability λ in time polynomial with respect to the input instance size and{a mathematical formula}−log⁡(1−λ).
      </paragraph>
      <paragraph label="Proof">
       Let ϵ be a fixed constant. We are given an instance I of {a mathematical formula}αB,dec-Monroe-SatWinner.We consider the following cases. If {a mathematical formula}m≤1+2ϵ, then we solve I using a brute-force algorithm (note that in this case the number of alternatives is at most a fixed constant). Similarly, if {a mathematical formula}HKK≥ϵ2 then we use the exact algorithm of Betzler et al. [9] for a fixed value of K (note that in this case K is no greater than a certain fixed constant).On the other hand, if neither of the above conditions hold (that is, if we have {a mathematical formula}m&gt;1+2ϵ and {a mathematical formula}HKK≤ϵ2), then we try both Algorithm A and a number of runs of the sampling-based algorithm. It is easy to check through routine calculation that if {a mathematical formula}HKK≤ϵ2 and {a mathematical formula}m&gt;1+2ϵ then Algorithm A achieves approximation ratio no worse than {a mathematical formula}(1−K2m−ϵ). We run the sampling-based algorithm {a mathematical formula}−log⁡(1−λ)2+ϵϵ times. The probability that a single run fails to find a solution with approximation ratio at least {a mathematical formula}12(1+Km−K2m2−m+K3m3−m2)−ϵ2 is {a mathematical formula}pϵ2≤22+ϵ. Thus, the probability that at least one run will find a solution with at least this approximation ratio is at least:{a mathematical formula} Since {a mathematical formula}m≤1+2ϵ, by routine calculation we see that the sampling-based algorithm with probability λ finds a solution with approximation ratio at least {a mathematical formula}12(1+Km−K2m2+K3m3)−ϵ. By solving the equation{a mathematical formula} we can find the value of {a mathematical formula}Km for which the two algorithms give the same approximation ratio. By substituting {a mathematical formula}x=Km we get equality {a mathematical formula}1+x−x2+x3=2−x. One can calculate that this equality has a single solution within {a mathematical formula}〈0,1〉 and that this solution is {a mathematical formula}x≈0.57. For this x both algorithms guarantee approximation ratio of {a mathematical formula}0.715−ϵ. For {a mathematical formula}x&lt;0.57 the deterministic algorithm guarantees a better approximation ratio and for {a mathematical formula}x&gt;0.57, the randomized algorithm does better.  □
      </paragraph>
      <paragraph>
       The relation between m, the ratio {a mathematical formula}K/m, and the approximation guarantee of Algorithm AR is depicted in Fig. 8.
      </paragraph>
      <paragraph>
       Let us now consider the case of CC. It is just as natural to try a sampling-based approach for solving {a mathematical formula}αB,dec-CC-SatWinner, as we did for the Monroe variant. Indeed, as recently (and independently) observed by Oren [45], this leads to a randomized algorithm with expected approximation ratio of {a mathematical formula}(1−1K+1)(1+1m). However, since we will later see an effective, deterministic, polynomial-time approximation scheme for {a mathematical formula}αB,dec-CC-SatWinner, there is little reason to explore the sampling based approach.
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Algorithm GM (Monroe, CC)
      </section-title>
      <paragraph>
       Algorithm GM (greedy marginal improvement) was introduced by Lu and Boutilier for the case of the Chamberlin–Courant rule. Here we generalize it to apply to the Monroe rule as well, and we show that it is a {a mathematical formula}(1−1e)-approximation algorithm for α-Monroe-SatWinner. We point out that this approximation result for the Monroe rule applies to all non-decreasing PSFs α. For the Monroe rule, the algorithm can be viewed as an extension of Algorithm B.
      </paragraph>
      <paragraph>
       The algorithm proceeds as follows. We start with an empty set S. Then we execute K iterations. In each iteration we find an alternative a that is not assigned to agents yet, and that maximizes the value {a mathematical formula}ΦαS∪{a}. (A certain disadvantage of this algorithm for the case of Monroe is that it requires a large number of computations of {a mathematical formula}ΦαS. Since the Monroe rule assigns each alternative to at most {a mathematical formula}nK agents in the partial assignment {a mathematical formula}ΦαS, computing {a mathematical formula}ΦαS is a slow process based on min-cost/max-flow algorithm.) We provide the pseudocode for Algorithm GM in Fig. 9.
      </paragraph>
      <paragraph>
       We derive the approximation ratio of Algorithm GM as a corollary of a more general result regarding weighted b-matchings in bipartite graphs.
      </paragraph>
      <paragraph label="Definition 6">
       Weighted-B-Matching (for bipartite graphs)Let {a mathematical formula}(U,V,E) be a bipartite undirected graph, where {a mathematical formula}U∪V is the set of vertices and E is the set of edges. For each edge {a mathematical formula}{u,v}∈E, by {a mathematical formula}w(u,v)∈R≥0 we denote its weight, and for each left-side vertex {a mathematical formula}u∈U, by {a mathematical formula}su∈N we denote its capacity. The goal is to find a subset of the edges with the maximal total weight, such that each vertex {a mathematical formula}u∈U belongs to at most {a mathematical formula}su of the selected edges, each vertex {a mathematical formula}v∈V belongs to at most one of the selected edges, and altogether at most K vertices from U belong to the selected edges.
      </paragraph>
      <paragraph label="Theorem 9">
       Consider a greedy algorithm forWeighted-B-Matchingthat proceeds as follows. It starts with an empty set S of edges, and in each of K consecutive steps adds to S such a vertex{a mathematical formula}u∈Uthat{a mathematical formula}{u}∪S∪Vinduces a weighted B-matching with the maximal total weight. After K steps, the algorithm returns a weighted B-matching with maximal total weight for the graph induced by vertices{a mathematical formula}S∪V. This algorithm is a polynomial-time{a mathematical formula}(1−1e)-approximation algorithm forWeighted-B-Matching.
      </paragraph>
      <paragraph label="Proof">
       The proof is in Appendix D.  □
      </paragraph>
      <paragraph label="Theorem 10">
       For each non-decreasing positional scoring function α Algorithm GM is a{a mathematical formula}(1−1e)-approximation algorithm for α-Monroe-SatWinner.
      </paragraph>
      <paragraph label="Proof">
       This theorem follows from Theorem 9. To show that this is the case, we reduce α-Monroe-SatWinner to Weighted-B-Matching. Consider an instance of α-Monroe-SatWinner with the set of agents {a mathematical formula}[n], with the set of alternatives A, and with committee size K. We form an instance of Weighted-B-Matching with bipartite graph {a mathematical formula}(U,V,E) as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        We set {a mathematical formula}U=A, i.e., the vertices on the left correspond to the candidates.
       </list-item>
       <list-item label="2.">
        We set {a mathematical formula}V=[n], i.e., the vertices on the right correspond to the agents.
       </list-item>
       <list-item label="3.">
        For every candidate {a mathematical formula}a∈A and every agent {a mathematical formula}i∈[n], we form an edge {a mathematical formula}{a,i}, whose weight is equal to the satisfaction of agent i from being assigned to candidate a.
       </list-item>
       <list-item label="4.">
        Each candidate a has capacity {a mathematical formula}sa=nK.
       </list-item>
      </list>
      <paragraph>
       Formally speaking, Algorithm GM is never worse than Algorithm A. For the Borda satisfaction function, it inherits the approximation guarantees from Algorithm A, and for other cases Theorem 10 guarantees approximation ratio {a mathematical formula}1−1e (we do not know of any guarantees for Algorithm A for these cases). The comparison with Algorithms B and C is not nearly as easy. Algorithm GM is still likely better than both of them for satisfaction functions significantly different from the Borda one, but for the Borda case our experiments show that Algorithm GM is much slower than Algorithms B and C and obtains almost the same or slightly worse results (see Section 5).
      </paragraph>
     </section>
     <section label="4.6">
      <section-title>
       Algorithm P (CC)
      </section-title>
      <paragraph>
       Algorithm P is presented in Fig. 10. The idea of this algorithm is to compute {a mathematical formula}x=mw(K)K, where w is the Lambert's W-function and to greedily compute an assignment that (approximately) maximizes the number of agents assigned to one of their top x alternatives.{sup:5} If after this process some agent has not been assigned to any alternative, we assign her to her most preferred alternative from those already selected. Somewhat surprisingly, it turns out that this greedy strategy achieves high-quality results.
      </paragraph>
      <paragraph label="Theorem 11">
       For every preference profile, Algorithm P returns a solution in which each agent is, on average, represented by an alternative that she prefers to at least{a mathematical formula}1−2w(K)Kfraction of the alternatives.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}x=mw(K)K. We will first give an inductive proof that, for each i, {a mathematical formula}0≤i≤K, after the i-th iteration of the outer loop at most {a mathematical formula}n(1−w(K)K)i agents are unassigned. Based on this observation, we will derive the approximation ratio of our algorithm.For {a mathematical formula}i=0, the inductive hypothesis holds because {a mathematical formula}n(1−w(K)K)0=n. For each i, let {a mathematical formula}ni denote the number of unassigned agents after the i-th iteration. Thus, after the i-th iteration there are {a mathematical formula}ni unassigned agents, each with x unassigned alternatives among her top x ranked alternatives. As a result, at least one unassigned alternative is present in at least {a mathematical formula}nixm−i of the top x positions of unassigned agents. This means that after the {a mathematical formula}(i+1)-th iteration the number of unassigned agents is:{a mathematical formula} If for a given i the inductive hypothesis holds, that is, if {a mathematical formula}ni≤n(1−w(K)K)i, then:{a mathematical formula} Thus the hypothesis holds and, as a result, we have that:{a mathematical formula} Let Φ be the assignment computed by our algorithm. To compare it against the optimal solution, it suffices to observe that the optimal solution has the value of satisfaction of at most {a mathematical formula}OPT≤(m−1)n, that each agent selected during the first K steps has satisfaction at least {a mathematical formula}m−x=m−mw(K)K, and that the agents not assigned within the first K steps have satisfaction no worse than 0. Thus it holds that:{a mathematical formula} This completes the proof.  □
      </paragraph>
      <paragraph>
       The relation between K, and the guarantee of satisfaction of an average voter is given in Fig. 11.
      </paragraph>
      <paragraph label="Corollary 12">
       Algorithm P is a polynomial-time{a mathematical formula}(1−2w(K)K)-approximation algorithm for{a mathematical formula}αB,dec-CC-SatWinner.
      </paragraph>
      <paragraph label="Proof">
       Since a satisfaction of each single agent is bounded by {a mathematical formula}(m−1), by applying Theorem 11, we get the conclusion.  □
      </paragraph>
      <paragraph>
       Since for each {a mathematical formula}ϵ&gt;0 there is a value {a mathematical formula}Kϵ such that for each {a mathematical formula}K&gt;Kϵ it holds that {a mathematical formula}2w(K)K&lt;ϵ, and {a mathematical formula}αB,dec-CC-SatWinner problem can be solved optimally in polynomial time for each fixed constant K (see the XP algorithm for parameter K given by Betzler et al. [9]), there is a polynomial-time approximation scheme (PTAS) for {a mathematical formula}αB,dec-CC-SatWinner (i.e., a family of algorithms such that for each fixed r, {a mathematical formula}0&lt;r&lt;1, there is a polynomial-time r-approximation algorithm for {a mathematical formula}αB,dec-CC-SatWinner in the family; note that in PTASes we measure the running time by considering r to be a fixed constant). The reason is that given the approximation parameter ϵ and an instance of the problem with a particular value of K, we can solve it as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        If {a mathematical formula}K≤Kϵ, then we use the brute-force algorithm of Betzler et al. [9] to solve the problem optimally (since {a mathematical formula}Kϵ is a constant, the algorithm runs in polynomial time).{sup:6}
       </list-item>
       <list-item label="2.">
        Otherwise, we use Algorithm P (whose approximation ratio is sufficiently good when {a mathematical formula}K≥Kϵ).
       </list-item>
      </list>
      <paragraph label="Corollary 13">
       There is a PTAS for{a mathematical formula}αB,dec-CC-SatWinner.
      </paragraph>
      <paragraph>
       Finally, we show that Algorithm P performs very well even if the voters cast truncated ballots. Proposition 14 gives the relation between the number Q of positions used by the algorithm and the approximation ratio. In Fig. 12 we show this relation for some values of the parameters m and K.
      </paragraph>
      <paragraph label="Proposition 14">
       Algorithm P that uses{a mathematical formula}x=Qinstead of{a mathematical formula}x=⌈mw(K)K⌉, where{a mathematical formula}Q≤mw(K)K, returns a solution in which each agent is, on average, represented by an alternative that she prefers to at least{a mathematical formula}m−Qm−1(1−e−QKm)fraction of the alternatives. In particular, such algorithm is a polynomial-time{a mathematical formula}(m−Qm−1(1−e−QKm))-approximation algorithm for{a mathematical formula}αB,dec-CC-SatWinner.
      </paragraph>
      <paragraph label="Proof">
       The proof is in Appendix D.  □
      </paragraph>
      <paragraph>
       For example, for Polish parliamentary elections ({a mathematical formula}K=460, {a mathematical formula}m=6000), it suffices that each voter ranks only {a mathematical formula}0.5% of her top alternatives (that is, about 30 alternatives) for the algorithm to find a solution with guaranteed satisfaction at least {a mathematical formula}90% of the maximal satisfaction (possibly not achievable) when every voter is assigned to her top alternative.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Empirical evaluation of the algorithms
     </section-title>
     <paragraph>
      In this section we present the results of empirical evaluation of algorithms from Section 4. In the experiments we consider variants of the randomized algorithms that use exactly 100 sampling steps. In all cases but one, we use Borda DPSF to measure voter satisfaction. In one case, with six candidates, we use PSF defined through vector {a mathematical formula}(3,3,3,2,1,0) (we made this choice due to the nature of the data set; see discussion later).
     </paragraph>
     <paragraph>
      We have conducted four sets of experiments. First, we have tested all our algorithms on relatively small elections (up to 10 candidates, up to 100 agents). In this case we were able to compare the solutions provided by our algorithms with the optimal ones. (To obtain the optimal solutions, we were using the ILP formulations, see Appendix B, and the GLPK's ILP solver.) Thus we report the quality of our algorithms as the average of fractions {a mathematical formula}C/Copt, where C is the satisfaction obtained by a respective algorithm and {a mathematical formula}Copt is the satisfaction in the optimal solution. For each algorithm and data set, we also report the average fraction {a mathematical formula}C/Cideal, where {a mathematical formula}Cideal is the satisfaction that the voters would have obtained if each of them were matched to her most preferred alternative. In our further experiments, where we considered larger elections, we were not able to compute optimal solutions, but the fraction {a mathematical formula}C/Cideal gives a lower bound for {a mathematical formula}C/Copt. We report this value for small elections so that we can see an example of the relation between {a mathematical formula}C/Copt and {a mathematical formula}C/Cideal and so that we can compare the results for small elections with the results for the larger ones. Further, for the case of Borda PSF the {a mathematical formula}C/Cideal fraction has a very natural interpretation: If its value for a given solution is v, then, on the average, in this solution each voter is matched to an alternative that she prefers to {a mathematical formula}(m−1)v alternatives.
     </paragraph>
     <paragraph>
      In our second set of experiments, we have run our algorithms on large elections (thousands of agents, hundreds of alternatives), coming either from the NetFlix data set (see below) or generated by us using one of our models. Here we report the average fraction {a mathematical formula}C/Cideal only. We analyze the quality of the solutions as a function of the number of agents, the number of candidates, and the relative number of winners (fraction {a mathematical formula}K/m). (This last set of results is particularly interesting because in addition to measuring the quality of our algorithms, it allows one to assess the size of a committee one should seek if one wants to achieve a given average satisfaction of agents.)
     </paragraph>
     <paragraph>
      In the third set of experiments, we investigate the effect of submitting truncated ballots (i.e., preference orders where only some of the top alternatives are ranked). Specifically, we focus on the relation between the fraction of ranked alternatives and the approximation ratios of the algorithms. We ran our experiments on relatively large instances describing agents' preferences; thus, here as in the previous set of experiments, we used NetFlix data set and the synthetic data sets. We report the quality of the algorithms as the ratio {a mathematical formula}C/Cideal.
     </paragraph>
     <paragraph>
      In the fourth set of experiments we have measured running times of our algorithms and of the ILP solver. Even though all our algorithms (except for the ILP based ones) are polynomial-time, in practice some of them are too slow to be useful.
     </paragraph>
     <section label="5.1">
      <section-title>
       Experimental data
      </section-title>
      <paragraph>
       For the evaluation of the algorithms we consider both real-life preference-aggregation data and synthetic data, generated according to a number of election models. The experiments reported in this paper predate the work of Mattei and Walsh [37] on gathering a large collection of data sets with preference data, but we mention that the conference version of this paper contributed several data sets to their collection.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Real-life data
       </section-title>
       <paragraph>
        We use real-life data regarding people's preference on sushi types, movies, college courses, and performance of athletes in figure-skating competitions. One of the major problems regarding real-life preference data is that either people express preferences over a very limited set of alternatives, or their preference orders are partial. To address the latter issue, for each such data set we extended the partial orders to total orders using the technique of Kamishima [27]. (The idea is to complete each preference order based on those reported preference orders that appear to be similar.)
       </paragraph>
       <paragraph>
        Some of our data sets contain a single profile, whereas the others contain multiple profiles. When preparing data for a given number m of candidates and a given number n of voters from a given data set, we used the following method: We first uniformly at random chose a profile within the data set, and then we randomly selected n voters and m candidates. We used preference orders of these n voters restricted to these m candidates.
       </paragraph>
       <paragraph>
        There are two important points that we should make about our real-life data sets and the way we use them. First, one should keep in mind that the method of extending partial preference orders to total ones can possibly have significant influence on the results. Here we used the Kamishima [27] technique, but other ones are possible and might give different results. Second, in our experiments on real-life data, for each experiment we redraw a sample from a given data set. This means that our samples are not independent and our results should be seen as “noisy observations about the same event,” where the event corresponds to the type of preferences in a given data set. We believe that such results are still useful and do give some information on how our algorithms would behave in practice. Nonetheless, one should keep in mind their limitations. We point the reader to Regenwetter et al.'s book [50] for a detailed discussion of various issues in treating empirical data in social choice, including the two issues just mentioned.{sup:7}
       </paragraph>
       <paragraph>
        Sushi Preferences. We used the set of preferences regarding sushi types collected by Kamishima [27].{sup:8} Kamishima has collected two sets of preferences, which we call S1 and S2. Data set S1 contains complete rankings of 10 alternatives collected from 5000 people. S2 contains partial rankings provided by 5000 people over a set of 100 alternatives (each “vote” ranks 10 alternatives). We used Kamishima's [27] technique to obtain total rankings.
       </paragraph>
       <paragraph>
        Movie Preferences. Following Mattei et al. [35], [36], we have used the NetFlix data set{sup:9} of movie preferences (we call it Mv). NetFlix data set contains ratings collected from about 480 thousand distinct users regarding 18 thousand movies. The users rated movies by giving them a score between 1 (bad) and 5 (good). The set contains about 100 million ratings. We have generated 50 profiles using the following method: For each profile we have randomly selected 300 movies, picked {a mathematical formula}10000 users that ranked the highest number of the selected movies, and for each user we have extended her ratings to a complete preference order using the method of Kamishima [27]. (However, we should mention that Popova et al. [46] presented a detailed discussion showing that the exact results—in their case for single-winner voting rules—that one could derive from the NetFlix data set vary strongly depending on the assumptions one makes about extending the ratings to complete preference profiles. Thus our results about this data set should be understood only as examples of the type of results one should expect.)
       </paragraph>
       <paragraph>
        Course Preferences. Each year the computer science students at the AGH University in Krakow choose courses that they would like to attend. In our case, the students were offered a choice of six courses of which they had to attend three. Thus the students were asked to give an unordered set of their three most preferred courses and a ranking of the remaining ones (in case too many students selected a particular course, those with the highest GPA were enrolled and the remaining ones were moved to their less preferred courses). In this data set, which we call Cr, we have 120 voters (students) and 6 alternatives (courses). However, due to the nature of the data, instead of using Borda count PSF as the satisfaction measure, we use the vector {a mathematical formula}(3,3,3,2,1,0). Currently this data set is available as part of PrefLib [37].
       </paragraph>
       <paragraph>
        Figure Skating. This data set, which we call Sk, contains preferences of the judges over performances in figure-skating competitions. The data set contains 48 profiles, each describing a single competition. Each profile contains preference orders of 9 judges over about 20 participants. The competitions include European skating championships, Olympic Games, World Junior, and World Championships, all from 1998.{sup:10} (Note that while in figure skating judges provide numerical scores, this data set is preprocessed to contain preference orders.)
       </paragraph>
       <paragraph>
        Most of the data sets that we used are currently available as part of the PrefLib [37] library of preference data.
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Synthetic data
       </section-title>
       <paragraph>
        For our tests, we also use profiles generated using three well-known distributions of preference orders.
       </paragraph>
       <paragraph>
        Impartial Culture. Under the impartial culture model of preferences (which we denote IC), for a given set A of alternatives, each voter's preference order is drawn uniformly at random from the set of all possible total orders over A. While not very realistic, profiles generated using impartial culture model are a standard testbed of election-related algorithms.
       </paragraph>
       <paragraph>
        Polya–Eggenberger Urn Model. Following McCabe-Dansted and Slinko [39] and Walsh [60], we use the Polya–Eggenberger urn model [6] (which we denote Ur). In this model we generate votes as follows. We have a set A of m alternatives and an urn that initially contains a copy of each of the m! preference orders over A. To generate a vote, we simply randomly pick one from the urn (this is our generated vote), and then—to simulate correlation between voters—we return a copies of this preference order to the urn. When generating an election with m candidates using the urn model, we set the parameter a so that {a mathematical formula}am!=0.05. (Both McCabe-Dansted and Slinko [39] and Walsh [60] refer to the value {a mathematical formula}am! as parameter b; we mention that those authors use much higher values of b but we felt that too high a value leads to a much too strong correlation between votes.)
       </paragraph>
       <paragraph>
        Generalized Mallow's Model. We refer to this data set as Ml. Let ≻ and {a mathematical formula}≻′ be two preference orders over some alternative set A. Kendal–Tau distance between ≻ and {a mathematical formula}≻′, denoted {a mathematical formula}dK(≻,≻′), is defined as the number of pairs of candidates {a mathematical formula}x,y∈A such that either {a mathematical formula}(x≻y)∧(y≻′x) or {a mathematical formula}(y≻x)∧(x≻′y).
       </paragraph>
       <paragraph>
        Under Mallow's distribution of preferences [34] we are given two parameters: a center preference order ≻ and a number ϕ between 0 and 1. The model says that the probability of generating preference order {a mathematical formula}≻′ is proportional to the value {a mathematical formula}ϕdK(≻,≻′) To generate preference orders following Mallow's distribution, we use the algorithm given by Lu and Boutilier [33].
       </paragraph>
       <paragraph>
        In our experiments, we use a mixture of Mallow's models. Let A be a set of alternatives and let ℓ be a positive integer. This mixture model is parametrized by three vectors, {a mathematical formula}Λ=(λ1,…,λℓ) (where each {a mathematical formula}λi is between 0 and 1, and {a mathematical formula}∑i=1ℓλ1=1), {a mathematical formula}Φ=(ϕ1,…,ϕℓ) (where each {a mathematical formula}ϕi is a number between 0 and 1), and {a mathematical formula}Π=(≻1,…,≻ℓ) (where each {a mathematical formula}≻i is a preference order over A). To generate a vote, we pick a random integer i, {a mathematical formula}1≤i≤ℓ (each i is chosen with probability {a mathematical formula}λi), and then generate the vote using Mallow's model with parameters {a mathematical formula}(≻i,ϕi).
       </paragraph>
       <paragraph>
        For our experiments, we use {a mathematical formula}a=5, and generate vectors Λ, Φ, and Π uniformly at random.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Evaluation on small instances
      </section-title>
      <paragraph>
       We now present the results of our experiments on small elections. For each data set, we generated elections with the number of agents {a mathematical formula}n=100 ({a mathematical formula}n=9 for data set Sk because there are only 9 voters there) and with the number of alternatives {a mathematical formula}m=10 ({a mathematical formula}m=6 for data set Cr because there are only 6 alternatives there) using the method described in Section 5.1.1 for the real-life data sets, and in the natural obvious way for synthetic data. For each algorithm and for each data set we ran 500 experiments on different instances for {a mathematical formula}K=3 (for the Cr data set we used {a mathematical formula}K=2) and 500 experiments for {a mathematical formula}K=6 (for Cr we set {a mathematical formula}K=4). For Algorithm C (both for Monroe and for CC) we set the parameter d, describing the number of assignment functions computed in parallel, to 15. The results (average fractions {a mathematical formula}C/Copt and {a mathematical formula}C/Cideal) for {a mathematical formula}K=3 are given in Table 1, Table 3; the results for {a mathematical formula}K=6 are given in Table 2, Table 4 (they are almost identical as for {a mathematical formula}K=3). For each experiment in this section we also computed the standard deviation; it was always on the order of 0.01. We also computed the minimum satisfaction values returned by our algorithms in each of the experiments. For all the algorithms except Algorithm P, these values were never lower than 90% of the reported average values (for Algorithm P, they were never lower than 85% of the reported average values). These results lead to the following conclusions:
      </paragraph>
      <list>
       <list-item label="1.">
        For the case of Monroe, Algorithm A obtains very good results, but nonetheless Algorithms B and C improve noticeably upon Algorithm A. In particular, Algorithm C (for {a mathematical formula}d=15) obtained the highest satisfaction on all data sets and in almost all cases was able to find an optimal solution.
       </list-item>
       <list-item label="2.">
        Both for Monroe and for CC, Algorithm R gives slightly worse solutions than Algorithm C.
       </list-item>
       <list-item label="3.">
        The results do not seem to depend on the data sets used in the experiments (the only exception is Algorithm R for the Monroe system on data set Sk; however Sk has only 9 voters so we view it as a border case).
       </list-item>
      </list>
      <paragraph>
       Since Algorithm C achieves very good results, it is natural to ask for the impact of the value of the parameter d on the quality of approximation. We present this relation for {a mathematical formula}n=100, {a mathematical formula}m=10, and {a mathematical formula}K=3 in Fig. 13. We see that for the case of Chamberlin–Courant system even a small value of d is sufficient to obtain algorithm's optimal behavior. For the case of the Monroe system, slightly larger values of d lead to optimal behavior. In the next section we show that for the larger values of m Algorithm A gives high quality results by itself, and thus the impact of the value of d is even less pronounced. For this reason we omit presentation of the analogous results regarding parameter d for larger values of m.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Evaluation on larger instances
      </section-title>
      <paragraph>
       For experiments on larger instances we needed data sets with at least {a mathematical formula}n=10000 agents. Thus we used the NetFlix data set and synthetic data. (Additionally, we ran the subset of experiments (for {a mathematical formula}n≤5000) also for the S2 data set.) For the Monroe rule we present results for Algorithms A, C, and R, and for the Chamberlin–Courant rule we present results for Algorithms C and R. We limit the set of algorithms for the sake of clarity of presentation. For Monroe we chose Algorithm A because it is the simplest and the fastest one, Algorithm C because it is the best generalization of Algorithm A that we were able to run in reasonable time, and Algorithm R to compare a randomized algorithm to deterministic ones. For the Chamberlin–Courant rule we chose Algorithm C because it is, intuitively, the best one, and we chose Algorithm R for the same reason as in the case of Monroe.
      </paragraph>
      <paragraph>
       First, for each data set and for each algorithm we fixed the value of m and K and for each n ranging from 1000 to {a mathematical formula}10000 with the step of 1000 we ran 50 experiments. We repeated this procedure for 4 different combinations of m and K: ({a mathematical formula}m=10, {a mathematical formula}K=3), ({a mathematical formula}m=10, {a mathematical formula}K=6), ({a mathematical formula}m=100, {a mathematical formula}K=30) and ({a mathematical formula}m=100, {a mathematical formula}K=60). We measured the statistical correlation between the number of voters and the quality of the algorithms {a mathematical formula}C/Cideal. The ANOVA test in most cases showed that there is no such correlation. The only exception was S2 data set, for which we obtained an almost negligible correlation. For example, for ({a mathematical formula}m=10, {a mathematical formula}K=3) Algorithm C under data set S2 for the Monroe system for {a mathematical formula}n=5000 gave {a mathematical formula}C/Cideal=0.88, while for {a mathematical formula}n=100 (in the previous section) we got {a mathematical formula}C/Cideal=0.89. Thus we conclude that in practice the number of agents has almost no influence on the quality of the results provided by our algorithms.
      </paragraph>
      <paragraph>
       Next, we fixed the number of voters {a mathematical formula}n=1000 and the ratio {a mathematical formula}K/m=0.3, and for each m ranging from 30 to 300 with step size 30 (naturally, as m changed, so did K to maintain the ratio {a mathematical formula}K/m), we ran 50 experiments. We repeated this procedure for {a mathematical formula}K/m=0.6. The relation between m and {a mathematical formula}C/Cideal for Mv and Ur, under both the Monroe rule and the Chamberlin–Courant rule, is given in Fig. 14, Fig. 15 (the results for {a mathematical formula}K/m=0.6 look similar).
      </paragraph>
      <paragraph>
       Finally, we fixed {a mathematical formula}n=1000 and {a mathematical formula}m=100, and for each {a mathematical formula}K/m ranging from 0.1 and 0.5 with the step of 0.1 we ran 50 experiments. The relation between the ratio {a mathematical formula}K/m and the quality {a mathematical formula}C/Cideal is presented in Fig. 16, Fig. 17.
      </paragraph>
      <paragraph>
       For the case of Chamberlin–Courant system, increasing the size of the committee to be elected improves overall agents' satisfaction. Indeed, since there are no constraints on the number of agents matched to a given alternative, a larger committee means more opportunities to satisfy the agents. For the Monroe rule, a larger committee may lead to a lower total satisfaction. This happens if many agents like a particular alternative a lot, but only some of them can be matched to this alternative and others have to be matched to their less preferred ones. Indeed, this observation is—to some extent—supported by our theoretical results: For example, if we fix the number of candidates m, the approximation guarantee of Algorithm P (for Chamberlin–Courant; see Fig. 11) is monotonically increasing with K, whereas this is not the case for the approximation guarantee of Algorithm A (for Monroe; see the right-hand side of Fig. 3). Nonetheless, we see that for Monroe Algorithm C achieves {a mathematical formula}C/Cideal=0.925 even for {a mathematical formula}K/m=0.5 for the NetFlix data set.
      </paragraph>
      <paragraph>
       Our conclusions from these experiments are the following. For the Monroe rule, even Algorithm A achieves very good results. However, Algorithm C consistently achieves better (indeed, almost perfect) ones. For the Chamberlin–Courant rule the randomized algorithm on some datasets performs better than the deterministic ones. However, even in such cases, the improvement over Algorithm C is small.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Truncated ballots
      </section-title>
      <paragraph>
       The purpose of our third set of experiments is to see how our algorithms behave in practical settings with truncated ballots. We conducted this part of evaluation on relatively large instances, including {a mathematical formula}n=1000 agents and up to {a mathematical formula}m=100 alternatives. Thus, in this set of experiments, we used the same sets of data as in the previous subsection: the NetFlix data set and the synthetic distributions. Similarly, we evaluated the same algorithms: Algorithms A, C, and R for the case of the Monroe system, and Algorithms C and R for the case of the Chamberlin–Courant system.
      </paragraph>
      <paragraph>
       For each data set and for each algorithm we ran experiments for three independent settings with different values of the parameters describing the elections: (1) {a mathematical formula}m=100, {a mathematical formula}K=20, (2) {a mathematical formula}m=100, {a mathematical formula}K=10, and (3) {a mathematical formula}m=20, {a mathematical formula}K=4. For each setting we ran the experiments for the values of P (the number of known positions) varying between 1 and m.
      </paragraph>
      <paragraph>
       For each algorithm, data set, setting and each value of P we ran 50 independent experiments in the following way. From a data set we sampled a sub-profile of the appropriate size {a mathematical formula}n×m. We truncated this profile to the P first positions. We ran the algorithm for the truncated profile and calculated the quality ratio {a mathematical formula}C/Cideal. When calculating {a mathematical formula}C/Cideal we assumed the worst case scenario, i.e., that the satisfaction of each agent from an alternative outside of her first P positions is equal to 0. In other words, we used the positional scoring function described by the following vector: {a mathematical formula}〈m−1,m−2,…,m−P,0,…,0〉. Next, we averaged the values of {a mathematical formula}C/Cideal over all 50 experiments.
      </paragraph>
      <paragraph>
       The relation between the percentage of the known positions in the preference profile and the average quality of the algorithm for the Monroe and Chamberlin–Courant systems are plotted in Fig. 18, Fig. 19, respectively. We omit the plots for the Urn model and for the Mallow's model, as in this case the results are very similar. We have the following conclusions.
      </paragraph>
      <list>
       <list-item label="1.">
        All the algorithms require only small number of the top positions to achieve their best quality. Here, the deterministic algorithms are superior.
       </list-item>
       <list-item label="2.">
        The small elections with synthetic distributions appear to be the worst case scenario (we also run our experiments for Urn model and for Mallow's model: for these two models our algorithms gave slightly better results than for the impartial culture model)—in such cases we require the knowledge of about 40% of the top positions to obtain the highest approximation ratios of the algorithms. In the case of the NetFlix data set, even on small instances the deterministic algorithms require only about 8% of the top positions to get their best quality (however the quality is already high for 3–5% of the top positions). For the larger number of the alternatives, the algorithms do not require more than 3% of the top positions to reach their top results.
       </list-item>
       <list-item label="3.">
        Algorithm C gives the best solutions and is also the most immune one to the lack of knowledge. These results are more evident for the case of the Monroe system.
       </list-item>
      </list>
     </section>
     <section label="5.5">
      <section-title>
       Running time
      </section-title>
      <paragraph>
       In our final set of experiments, we measured running times of our algorithms on the data set Mv. We used a machine with Intel Pentium Dual T2310 1.46 GHz processor and 1.5 GB of RAM. In Fig. 20 we show the running times of the GLPK ILP solver for the Monroe and for Chamberlin–Courant rules. These running times are already large for small instances and they are increasing exponentially with the number of voters. For the Monroe rule, even for {a mathematical formula}K=9, {a mathematical formula}m=30, {a mathematical formula}n=100 some of the experiments timed out after 1 hour, and for {a mathematical formula}K=9, {a mathematical formula}m=30, {a mathematical formula}n=200 none of the experiments finished within one day. Thus we conclude that the real application of the ILP-based algorithm is very limited.
      </paragraph>
      <paragraph>
       Example running times of the other algorithms for some combinations of n, m, and K are presented in Table 5. For the case of CC, essentially all the algorithms are very fast and the quality of computed solutions is the main criterion in choosing among them. For the case of Monroe, the situation is more complicated. While for small elections all the algorithms are practical, for elections with thousands of voters, using Algorithm GM becomes problematic. Indeed, even Algorithm C can be seen as a bit too slow if one expects immediate results. On the other hand, Algorithms A and B seem perfectly practical and, as we have seen in the previous experiments, give high-quality results.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      The Monroe and Chamberlin–Courant rules as resource allocation problems
     </section-title>
     <paragraph>
      One of the ways of looking at the Monroe and Chamberlin–Courant rules is to consider them through the lenses of resource allocation. In this section we describe this more general view.
     </paragraph>
     <paragraph>
      As before, we assume that we have a set {a mathematical formula}N=[n] of agents and a set {a mathematical formula}A={a1,…,am} of items. In the voting setting the items were the candidates participating in election; now they can be other entities as well (see the example later). Each agent has a preference order over A. The understanding is that each agent will receive access to one of the items and in the preference order each agent ranks the items from the most desired one to the least desired one. Additionally, each item {a mathematical formula}a∈A has the capacity{a mathematical formula}capa∈N. At most {a mathematical formula}capa agents can be granted access to item a. A capacitated K-assignment function Φ is a K-assignment that satisfies the constraint that for each item a, {a mathematical formula}‖Φ−1(a)‖≤capa.
     </paragraph>
     <paragraph>
      Given this setup, our resource allocation problem is the following (for the dissatisfaction-based case and for the satisfaction-based case).
     </paragraph>
     <paragraph label="Definition 7">
      Let α be a normal IPSF. An instance of α-Capacitated-DisWinner problem consists of a set of agents {a mathematical formula}N=[n], a set of items {a mathematical formula}A={a1,…,am}, a preference profile V of the agents, a sequence {a mathematical formula}(capa1,…,capam) of items' capacities, and a positive integer K. We ask for a capacitated K-assignment function Φ such that {a mathematical formula}ℓsumα(Φ) is minimized.
     </paragraph>
     <paragraph label="Definition 8">
      Let α be a normal DPSF. α-Capacitated-SatWinner is defined in the same way as α-Capacitated-DisWinner except that we ask to maximize {a mathematical formula}ℓsumα(Φ).
     </paragraph>
     <paragraph>
      Now it is easy to see that for each IPSF α (DPSF α), α-CC-DisWinner (α-CC-SatWinner) is a special case of α-Capacitated-DisWinner (α-Capacitated-SatWinner): It suffices that the capacities are set to be {a mathematical formula}‖N‖. Similarly, if K divides {a mathematical formula}‖N‖ and we set the all the capacities to {a mathematical formula}‖N‖K, then we obtain the variants of the problem for the Monroe rule.
     </paragraph>
     <paragraph>
      Nonetheless, Capacitated-DisWinner (Capacitated-SatWinner) is a far more general problem and we believe that it is interesting in its own right. For example, consider a company that wants to pay for sport classes for its employees. Naturally, each class can fit only a given number of employees and, due to limited budget, the company wants to pay for K different classes only. However, it also wants the employees to be as happy with the provided classes as possible and, so, it asks each employee to rank the classes. Our problem models exactly the issue of choosing which classes to offer and which employees should be assigned to which one of them.
     </paragraph>
     <paragraph>
      While all the negative results for the case of the Monroe and Chamberlin–Courant rules translate directly to our resource allocation problem, we do not have any positive results for it. We believe that finding approximation algorithms for it (in the satisfaction-based setting) is a very interesting, challenging, open problem.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      ILP formulation for the Monroe and Chamberlin–Courant rules
     </section-title>
     <paragraph>
      To experimentally measure the quality of our approximation algorithms, we compare the results against optimal solutions that we obtain using integer linear programs (ILPs) that solve the Monroe and Chamberlin–Courant winner determination problem. An ILP for the Monroe rule was provided by Potthoff and Brams [47], Lu and Boutilier [32] adapted it also for the Chamberlin–Courant rule with arbitrary PSF α. For the sake of completeness, below we recall the ILP whose optimal solutions correspond to α-Monroe-SatWinner winner sets for the given election (we also indicate which constraints to drop to obtain an ILP for finding α-CC-SatWinner winner sets):
     </paragraph>
     <list>
      <list-item label="1.">
       For each i, {a mathematical formula}1≤i≤n, and each j, {a mathematical formula}1≤j≤m we have a 0/1 variable {a mathematical formula}aij indicating whether alternative {a mathematical formula}aj represents agent i. For each j, {a mathematical formula}1≤j≤m, we have a 0/1 variable {a mathematical formula}xj indicating whether alternative {a mathematical formula}aj is included in the set of winners.
      </list-item>
      <list-item label="2.">
       Our goal is to maximize the value {a mathematical formula}∑i=1nα(posi(aj))aij subject to the following constraints:
      </list-item>
     </list>
     <paragraph>
      We used the GLPK 4.47 package (GNU Linear Programming Kit, version 4.47) to solve these ILPs, whenever it was possible to do so in reasonable time.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Egalitarian cases: hardness results
     </section-title>
     <paragraph>
      In this section we provide our results for the egalitarian variants of the Monroe and Chamberlin–Courant rules. We start by providing formal definitions of our problems.
     </paragraph>
     <paragraph label="Definition 9">
      Let α be a normal IPSF. Problems α-EgalitarianCC-DisWinner and α-EgalitarianMonroe-DisWinner are defined in the same way as α-CC-DisWinner and α-Monroe-DisWinner, respectively, except that we seek to minimize {a mathematical formula}ℓmaxα(Φ) (instead of {a mathematical formula}ℓsumα(Φ)).
     </paragraph>
     <paragraph label="Definition 10">
      Let α be a normal DPSF. Problems α-EgalitarianCC-SatWinner and α-EgalitarianMonroe-SatWinner are defined in the same way as α-CC-SatWinner and α-Monroe-SatWinner, respectively, except that we seek to maximize {a mathematical formula}ℓminα(Φ) (instead of {a mathematical formula}ℓsumα(Φ)).
     </paragraph>
     <paragraph>
      In other words, the egalitarian variants of our problems are defined in the same way as the utilitarian variants, but the aggregated satisfaction of the agents (the aggregated dissatisfaction of the agents) is understood as that of the worst-off one of them.
     </paragraph>
     <paragraph>
      We define the notion of approximation algorithms for the egalitarian variants of the problems in the same way as in the utilitarian case. We show that there are no constant-factor approximation algorithms for the egalitarian variants of the Monroe and Chamberlin–Courant rules.
     </paragraph>
     <paragraph label="Theorem 15">
      For each normal IPSF α and each constant{a mathematical formula}r&gt;1, there is no polynomial-time r-approximation algorithm for α-Monroe-DisWinnerunless{a mathematical formula}P=NP.
     </paragraph>
     <paragraph label="Proof">
      The proof of Theorem 1 applies to this case as well. In fact, it even suffices to take {a mathematical formula}m′=‖A2‖=12nr⋅α(3).  □
     </paragraph>
     <paragraph label="Theorem 16">
      For each normal IPSF α and each constant factor{a mathematical formula}r&gt;1, there is no polynomial-time r-approximation algorithm for α-EgalitarianCC-DisWinnerunless{a mathematical formula}P=NP.
     </paragraph>
     <paragraph label="Proof">
      The proof of Theorem 2 is applicable in this case as well. In fact, it even suffices to take the m groups of alternatives, {a mathematical formula}A1,…,Am, to contain {a mathematical formula}α(2)⋅r alternatives each.  □
     </paragraph>
     <paragraph label="Theorem 17">
      For each normal DPSF α (where each entry is polynomially bounded in the number of alternatives) and each constant factor r, with{a mathematical formula}0&lt;r≤1, there is no r-approximation algorithm for α-EgalitarianMonroe-SatWinnerunless{a mathematical formula}P=NP.
     </paragraph>
     <paragraph label="Proof">
      Let us fix a DPSF {a mathematical formula}α=(αm)m∈N, where each entry {a mathematical formula}αm is polynomially bounded in the number of alternatives m. For the sake of contradiction, let us assume that for some r, {a mathematical formula}0&lt;r≤1, there is a polynomial-time r-approximation algorithm {a mathematical formula}A for α-EgalitarianMonroe-SatWinner. We will show that the existence of this algorithm implies that X3C is solvable in polynomial time.Let I be an X3C instance with ground set {a mathematical formula}U={1,2,…,n} and collection {a mathematical formula}F={F1,…,Fm} of subsets of U. Each set in {a mathematical formula}F has cardinality three. Further, without loss of generality, we can assume that n is divisible by three and that each {a mathematical formula}i∈U appears in at most three sets from {a mathematical formula}F. Given I, we form an instance {a mathematical formula}IM of α-EgalitarianMonroe-SatWinner as follows. Let {a mathematical formula}n′=3⋅(αm+1(1)⋅⌈1−rr⌉+3). The set N of agents is partitioned into two subsets, {a mathematical formula}N1 and {a mathematical formula}N2. {a mathematical formula}N1 contains n agents (intuitively, corresponding to the elements of the ground set U) and {a mathematical formula}N2 contains {a mathematical formula}n′ agents (used to enforce certain properties of the solution). The set of alternatives A is partitioned into two subsets, {a mathematical formula}A1 and {a mathematical formula}A2. We set {a mathematical formula}A1={a1,…,am} (members of {a mathematical formula}A1 correspond to the sets in {a mathematical formula}F), and we set {a mathematical formula}A2={b1,…,bm′}, where {a mathematical formula}m′=n′3.For each j, {a mathematical formula}1≤j≤n, we set {a mathematical formula}Mf(j)={ai|j∈Fi}. For each j, {a mathematical formula}1≤j≤n, we set the preference order of the j-th agent in {a mathematical formula}N1 to be of the form{a mathematical formula} Note that by our assumptions, {a mathematical formula}‖Mf(j)‖≤3. For each j, {a mathematical formula}1≤j≤n′, we set the preference order of the j-th agent in {a mathematical formula}N2 to be of the form{a mathematical formula} Note that each agent in {a mathematical formula}N2 ranks the alternatives from {a mathematical formula}A1 in positions {a mathematical formula}m′+1,…,m′+m. Finally, we set the number of candidates that can be selected to be {a mathematical formula}K=n+n′3.Now, consider the solution Φ returned by {a mathematical formula}A on {a mathematical formula}IM. We will show that {a mathematical formula}ℓmaxαm+m′(Φ)≤rαm+m′(3) if and only if I is a yes-instance of X3C.(⇐) If there exists an exact set cover of U with sets from {a mathematical formula}F, then it is easy to construct a solution for {a mathematical formula}IM where the satisfaction of each agent is greater or equal to {a mathematical formula}r⋅αm+m′(3). Let {a mathematical formula}I⊆{1,…,m} be a set such that {a mathematical formula}⋃i∈IFi=U and {a mathematical formula}‖I‖=n3. We assign each agent j from {a mathematical formula}N1 to the alternative {a mathematical formula}ai such that (a) {a mathematical formula}i∈I and (b) {a mathematical formula}j∈Fi, and we assign each agent from {a mathematical formula}N2 to her most preferred alternative. Thus, Algorithm {a mathematical formula}A has to return an assignment with the minimal satisfaction greater or equal to {a mathematical formula}r⋅αm+m′(3).(⇒) For the other direction, we first show that {a mathematical formula}r⋅αm+m′(3)≥αm+m′(m′). Since DPSFs are strictly decreasing, it holds that:{a mathematical formula} Then, by the definition of DPSFs, it holds that:{a mathematical formula} Using the fact that {a mathematical formula}m′=(αm+1(1)⋅⌈1−rr⌉+3) and using (2), we can transform inequality (1) to obtain the following:{a mathematical formula} This means that if the minimal satisfaction of an agent is at least {a mathematical formula}r⋅αm+m′(3), then no agent was assigned to an alternative that she ranked beyond position {a mathematical formula}m′. If some agent j from {a mathematical formula}N1 were assigned to an alternative from {a mathematical formula}A2, then, by the pigeonhole principle, some agent from {a mathematical formula}N2 would be assigned to an alternative from {a mathematical formula}A1. However, each agent in {a mathematical formula}N2 ranks the alternatives from {a mathematical formula}A1 beyond position {a mathematical formula}m′ and thus such an assignment is impossible. In consequence, it must be that each agent in j was assigned to an alternative that corresponds to a set {a mathematical formula}Fi in {a mathematical formula}F that contains j. Such an assignment directly leads to a solution for I.  □
     </paragraph>
     <paragraph>
      Let us now move on to the case of EgalitarianCC-SatWinner family of problems. Unfortunately, in this case our inapproximability argument holds for the case of Borda DPSF only (though we believe that it can be adapted to other DPSFs as well). Further, in our previous theorems we were showing that existence of a respective constant-factor approximation algorithm implies that NP collapses to P. In the following theorem we will show a seemingly weaker collapse of {a mathematical formula}W[2] to FPT.
     </paragraph>
     <paragraph>
      To prove hardness of approximation for {a mathematical formula}αB,dec-EgalitarianCC-SatWinner, we first prove the following simple lemma.
     </paragraph>
     <paragraph label="Lemma 18">
      Let K, p, l be three positive integers and let X be a set of cardinality lpK. There exists a family{a mathematical formula}S={S1,…,S(lKK)}of pK-element subsets of X such that for each K-element subset B of X, there is a set{a mathematical formula}Si∈Ssuch that{a mathematical formula}B⊆Si.
     </paragraph>
     <paragraph label="Proof">
      Set {a mathematical formula}X′=[lK] and let {a mathematical formula}S′ be a family of all K-element subsets of {a mathematical formula}X′. Replace each element i of {a mathematical formula}X′ with p new elements (at the same time replacing i with the same p elements within each set in {a mathematical formula}S′ that contains i). As a result we obtain two new sets, X and {a mathematical formula}S, that satisfy the statement of the theorem (up to the renaming of the elements).  □
     </paragraph>
     <paragraph label="Theorem 19">
      Let{a mathematical formula}αB,decmbe the Borda DPSF ({a mathematical formula}αB,decm(i)=m−i). For each constant factor r,{a mathematical formula}0&lt;r≤1, there is no r-approximation algorithm for{a mathematical formula}αB,decm-EgalitarianCC-SatWinnerunless{a mathematical formula}FPT=W[2].
     </paragraph>
     <paragraph label="Proof">
      For the sake of contradiction, let us assume that there is some constant r, {a mathematical formula}0&lt;r≤1, and a polynomial-time r-approximation algorithm {a mathematical formula}A for {a mathematical formula}αB,decm-EgalitarianCC-SatWinner. We will show that the existence of this algorithm implies that Set-Cover is fixed-parameter tractable for the parameter K (since Set-Cover is known to be {a mathematical formula}W[2]-complete for this parameter, this will imply {a mathematical formula}FPT=W[2]).Let I be an instance of Set-Cover with ground set {a mathematical formula}U=[n] and family {a mathematical formula}F={F1,F2,…,Fm} of subsets of U. Given I, we build an instance {a mathematical formula}ICC of {a mathematical formula}αB,decm-EgalitarianCC-SatWinner as follows. The set of agents N consists of n subsets of agents, {a mathematical formula}N1,…,Nn, where each group {a mathematical formula}Ni contains exactly {a mathematical formula}n′=(⌈2r⌉KK) agents. Intuitively, for each i, {a mathematical formula}1≤i≤n, the agents in the set {a mathematical formula}Ni correspond to the element i in U. The set of alternatives A is partitioned into two subsets, {a mathematical formula}A1 and {a mathematical formula}A2, such that: (1) {a mathematical formula}A1={a1,…,am} is a set of alternatives corresponding to the sets from the family {a mathematical formula}F, and (2) {a mathematical formula}A2, {a mathematical formula}‖A2‖=⌈2r⌉⌈m(1+r)K⌉K, is a set of dummy alternatives needed for our construction. We set {a mathematical formula}m′=‖A‖=m+‖A2‖.Before we describe the preference orders of the agents in N, we form a family {a mathematical formula}R={r1,…,rn′} of preference orders over {a mathematical formula}A2 that satisfies the following condition: For each K-element subset B of {a mathematical formula}A2, there exists {a mathematical formula}rj in R such that all members of B are ranked among the bottom {a mathematical formula}⌈m(1+r)K⌉K positions in {a mathematical formula}rj. By Lemma 18, such a construction is possible (it suffices to take {a mathematical formula}l=⌈2r⌉ and {a mathematical formula}p=⌈m(1+r)K⌉); further, the proof of the lemma provides an algorithmic way to construct R.We form the preference orders of the agents as follows. For each i, {a mathematical formula}1≤i≤n, set {a mathematical formula}Mf(i)={at|i∈Ft}. For each i, {a mathematical formula}1≤i≤n, and each j, {a mathematical formula}1≤j≤n′, the j-th agent from {a mathematical formula}Ni has preference order of the form:{a mathematical formula} (we pick any arbitrary, polynomial-time computable order of candidates within {a mathematical formula}Mf(i) and {a mathematical formula}A1−Mf(i)).Let Φ be an assignment computed by {a mathematical formula}A on {a mathematical formula}IM. We will show that {a mathematical formula}ℓmaxαB,decm′(Φ)≥r⋅(m′−m) if and only if I is a yes-instance of Set-Cover.(⇐) If there exists a solution for I (i.e., a cover of U with K sets from {a mathematical formula}F), then we can easily show an assignment where each agent is assigned to an alternative that he or she ranks among the top m positions (namely, for each j, {a mathematical formula}1≤j≤n, we assign all the agents from the set {a mathematical formula}Nj to the alternative {a mathematical formula}ai∈A1 such that {a mathematical formula}j∈Fi and {a mathematical formula}Fi belongs to the alleged K-element cover of U). Under this assignment, the least satisfied agent's satisfaction is at least {a mathematical formula}m′−m and, thus, {a mathematical formula}A has to return an assignment Φ where {a mathematical formula}ℓmaxαB,decm′(Φ)≥r⋅(m′−m).(⇒) Let us now consider the opposite direction. We assume that {a mathematical formula}A found an assignment Φ such that {a mathematical formula}ℓmaxαB,decm(Φ)≥r⋅(m′−m) and we will show that I is a yes-instance of Set-Cover. We claim that for each i, {a mathematical formula}1≤i≤n, at least one agent j in {a mathematical formula}Ni were assigned to an alternative from {a mathematical formula}A1. If all the agents in {a mathematical formula}Ni were assigned to alternatives from {a mathematical formula}A2, then, by the construction of R, at least one of them would have been assigned to an alternative that she ranks at a position greater than {a mathematical formula}‖A2‖−⌈m(1+r)K⌉K=⌈2r⌉⌈m(1+r)K⌉K−⌈m(1+r)K⌉K. For {a mathematical formula}x=⌈m(1+r)K⌉K we have:{a mathematical formula} (we skip the straightforward calculation) and, thus, this agent would have been assigned to an alternative that she ranks at a position greater than {a mathematical formula}m′−m′r+mr. As a consequence, this agent's satisfaction would be lower than {a mathematical formula}(m′−m)r. Similarly, no agent from {a mathematical formula}Ni can be assigned to an alternative from {a mathematical formula}A1−Mf(i). Thus, for each i, {a mathematical formula}1≤i≤n, there exists at least one agent {a mathematical formula}j∈Ni that is assigned to an alternative from {a mathematical formula}Mf(i). In consequence, the covering subfamily of {a mathematical formula}F consists simply of those sets {a mathematical formula}Ft, for which some agent is assigned to alternative {a mathematical formula}at∈A1.The presented construction gives the exact algorithm for Set-Cover problem running in time {a mathematical formula}f(K)(n+m)O(1), where {a mathematical formula}f(K) is polynomial in {a mathematical formula}(⌈2r⌉K). The existence of such an algorithm means that Set-Cover is in FPT. On the other hand, we know that Set-Cover is {a mathematical formula}W[2]-complete, and thus if {a mathematical formula}A existed then {a mathematical formula}FPT=W[2] would hold.  □
     </paragraph>
    </section>
    <section label="Appendix D">
     <section-title>
      Other proofs omitted from the main text
     </section-title>
     <paragraph label="Proof of Theorem 2">
      Let us fix a normal IPSF α. For the sake of contradiction, let us assume that there is some constant {a mathematical formula}r&gt;1, and a polynomial-time r-approximation algorithm {a mathematical formula}A for α-CC-DisWinner. We will show that it is possible to use {a mathematical formula}A to solve the NP-complete Vertex-Cover problem.Let {a mathematical formula}I=(U,F,K) be an instance of Vertex-Cover, where {a mathematical formula}U=[n] is the ground set, {a mathematical formula}F={F1,…,Fm} is a family of subsets of U (where each member of U belongs to exactly two sets in {a mathematical formula}F), and K is a positive integer.{sup:12}Given I, we construct an instance {a mathematical formula}ICC of α-CC-DisWinner as follows. The set of agents is {a mathematical formula}N=U and the set of alternatives is {a mathematical formula}A=⋃j=1mAj, where each {a mathematical formula}Aj contains exactly {a mathematical formula}α(2)⋅r⋅n (unique) alternatives. Our intention is that for each {a mathematical formula}j∈[m] the alternatives in {a mathematical formula}Aj correspond to the set {a mathematical formula}Fj. For each {a mathematical formula}Aj, {a mathematical formula}1≤j≤m, we pick one alternative, which we denote {a mathematical formula}aj. For each agent {a mathematical formula}i∈N, we set i's preference order as follows: Let {a mathematical formula}Fj and {a mathematical formula}Ft, {a mathematical formula}j&lt;t, be the two sets that contain i. Agent i's preference order is of the form {a mathematical formula}aj≻iat≻iAt−{at}≻iA−(At∪{aj,at}) (the particular order of alternatives in the sets {a mathematical formula}At−{at} and {a mathematical formula}A−(At∪{aj,at}) is irrelevant for the construction). We ask for an assignment of the agents to at most K alternatives.Let us consider a solution Φ returned by {a mathematical formula}A on input {a mathematical formula}ICC. We claim that {a mathematical formula}ℓsumα(Φ)≤nr⋅α(2) if and only if I is a yes-instance of Vertex-Cover.(⇐) If I is a yes-instance then each agent i can be assigned to one of the top two alternatives in his or her preference order (if there is a size-K cover, then this assignment selects at most K candidates). Thus the total dissatisfaction of an optimal assignment is at most {a mathematical formula}n⋅α(2). As a result, the solution Φ returned by {a mathematical formula}A has total dissatisfaction at most {a mathematical formula}nr⋅α(2).(⇒) If {a mathematical formula}A returns an assignment with total dissatisfaction no greater than {a mathematical formula}nr⋅α(2), then, by the construction of agents' preference orders, we see that each agent i was assigned to an alternative from a set {a mathematical formula}Aj such that {a mathematical formula}i∈Fj. Since the assignment can use at most K alternatives, this directly implies that there is a size-K cover of U with sets from {a mathematical formula}F.  □
     </paragraph>
     <paragraph label="Proof of Proposition 6">
      We use the same approach as in the proof of Lemma 4, except that we adjust our estimates of voters' satisfaction. Consider a situation after some i-th iteration of the algorithm's outer loop ({a mathematical formula}i=0 if we are before the first iteration). If {a mathematical formula}i+m−iK−i≤P, then we can use the same lower bound for the satisfaction of the agents assigned in the {a mathematical formula}(i+1)-th iteration as in the proof of Lemma 4. That is, the agents assigned in the {a mathematical formula}(i+1)-th iteration will have satisfaction at least {a mathematical formula}r1(i)=nK⋅(m−i−m−iK−i).For the case where {a mathematical formula}i+m−iK−i&gt;P, the bound from Lemma 4 does not hold, but we can use a similar approach to find a different one. Let {a mathematical formula}Px≤P be some positive integer. We are interested in the number x of not-yet assigned agents who rank some not-yet-selected alternative among their top {a mathematical formula}Px positions (after the i-th iteration). Similarly as in the proof of Lemma 4, using the pigeonhole principle we note that:{a mathematical formula} Thus, the satisfaction of the agents assigned in the {a mathematical formula}(i+1)-th iteration is at least:{a mathematical formula} The case {a mathematical formula}(K−i)(Px−i)m−i≥1 (or, equivalently, {a mathematical formula}i+m−iK−i≤Px) implies that {a mathematical formula}i+m−iK−i≤P and for this case we lower-bound agents' satisfaction by {a mathematical formula}r1(i). For the case where {a mathematical formula}(K−i)(Px−i)m−i≤1, i.e. where {a mathematical formula}i+m−iK−i≥Px, Eq. (3) simplifies to:{a mathematical formula} We use the estimate given by Eq. (4) to bound the satisfaction of the agents assigned in the {a mathematical formula}(i+1)-th iteration for the cases where (a) {a mathematical formula}i+m−iK−i≥m+i2 and (b) {a mathematical formula}m+i2≤P (or, equivalently, {a mathematical formula}(2P−m)≥i≥(K−2)): We estimate Eq. (4) as follows:{a mathematical formula} For the remaining cases (corresponding to the “otherwise” clause in the definition of {a mathematical formula}r(i)), we set {a mathematical formula}Px=P and (4) becomes:{a mathematical formula} Naturally, we replace our estimates by 0 whenever they become negative.To complete the proof, it suffice to, as in the proof of Lemma 4, note that {a mathematical formula}(m−1)n is an upper bound on the satisfaction achieved by the optimal solution.  □
     </paragraph>
     <paragraph label="Proof of Theorem 9">
      The proof follows by applying the powerful result of Nemhauser et al. [43], which says that greedy algorithms achieve {a mathematical formula}(1−1e)-approximation ratio when used to optimize nondecreasing submodular functions (we explain these notions formally below). The main challenge in the proof is to define a function that, on one hand, satisfies the conditions of Nemhauser et al.'s result, and, on the other hand, models solutions for Weighted-B-Matching.Let {a mathematical formula}U∪V be the set of vertices and E be the set of edges of a given bipartite graph. For each edge {a mathematical formula}{u,v}∈E, let {a mathematical formula}w(u,v) denote its weight. Without loss of generality, we assume that each vertex from U is connected with each vertex from V. Indeed, it is always possible to modify the original graph by introducing the missing edges and setting their weight to 0, so that the optimal solutions for the modified graph are the same as for the original one. Let {a mathematical formula}s:U→N be a function assigning to the vertices from U their capacities, and let K denote the number of vertices from U that can be used in a B-matching. For each {a mathematical formula}S⊆U such that {a mathematical formula}‖S‖≤K, by {a mathematical formula}ΦS:V→U we denote the optimal B-matching in the graph induced by {a mathematical formula}S∪V; by {a mathematical formula}ℓ(ΦS) we denote the total weight of {a mathematical formula}ΦS. It is easy to verify that both {a mathematical formula}ΦS and {a mathematical formula}ℓ(ΦS) are computable in polynomial time. We define function z, {a mathematical formula}z:2U→R+, so that for each {a mathematical formula}S⊆U, {a mathematical formula}‖S‖≤K, we have {a mathematical formula}z(S)=ℓ(ΦS). Clearly, {a mathematical formula}z(S) is nondecreasing (that is, for each two sets A and B, if {a mathematical formula}A⊆B⊆U and {a mathematical formula}‖B‖≤K, then {a mathematical formula}z(A)≤z(B)). Let {a mathematical formula}Smax=argmaxS⊂U,‖S‖=Kz(S). We see that each optimal B-matching for the graph induced by {a mathematical formula}Smax∪V is also optimal for the original graph. Thus, if z were submodular, then by the result of Nemhauser et al. [43] we would get that the greedy algorithm from the theorem statement is a {a mathematical formula}(1−1e)-approximation algorithm for Weighted-B-Matching (for bipartite graphs). So, our goal is to show that z is submodular.Formally, function z is submodular if for each two sets S and T, {a mathematical formula}S⊂T⊂U, and each vertex {a mathematical formula}u∈U∖T it holds that:{a mathematical formula} We will show a slightly stronger variant of submodularity. However, first we introduce some additional notation for capacity functions. For each {a mathematical formula}u∈U, we write {a mathematical formula}s∪{u} to denote the function such that {a mathematical formula}(s∪{u})(u)=s(u)+1 and {a mathematical formula}∀u′∈S∖{u}(s∪{u})(u′)=s(u′). (Analogously, we interpret {a mathematical formula}s∖{u} as subtracting one from the capacity for u, provided the capacity is nonzero.) Also, if s and t are two capacity functions, then by {a mathematical formula}s≤t we mean that {a mathematical formula}∀u∈Us(u)≤t(u). We extend our function z to allow subsets of the vertices from V and arbitrary capacity functions: For each subset {a mathematical formula}V′⊆V and each capacity function s, we define {a mathematical formula}zV′(s) to be the weight of the optimal B-matching for a graph induced by {a mathematical formula}U∪V′, such that the capacities of the vertices from U are given by the capacity function s. We will now prove a stronger variant of submodularity for our extended z. That is, we will show that for each two capacity functions s and t, each {a mathematical formula}V′⊆V, and each vertex {a mathematical formula}u∈U it holds that:{a mathematical formula} We will also extend notation for optimal matchings: Let {a mathematical formula}ΦV′s:V′→U denote the optimal B-matching for a graph induced by {a mathematical formula}U∪V′, and capacity function s.Our proof is by induction on {a mathematical formula}V′. Clearly, Eq. (5) holds for {a mathematical formula}V′=∅. Now, assuming that Eq. (5) holds for every {a mathematical formula}V′⊂V″ we will prove its correctness for {a mathematical formula}V″. Let us fix some vertex {a mathematical formula}u∈U and let {a mathematical formula}v∈V″ denote a vertex such that {a mathematical formula}ΦV″t∪{u}(v)=u (if there is no such vertex v then clearly the equation holds). Let {a mathematical formula}us=ΦV″s(v) and {a mathematical formula}ut=ΦV″t(v) (technically, it is possible that either of these vertices does not exist; in such a case, in the reasoning below we treat this vertex as a null one and we assume the weight of each edge incident to the null vertex is zero). We have:{a mathematical formula} We also have:{a mathematical formula} Since {a mathematical formula}ΦV″t describes an optimal B-matching under the capacity restriction t, we have that:{a mathematical formula} Finally, from the inductive hypothesis for {a mathematical formula}V′=V″∖{v} we have:{a mathematical formula} By combining these inequalities we get:{a mathematical formula} This completes the proof.  □
     </paragraph>
     <paragraph label="Proof of Proposition 14">
      Let {a mathematical formula}ni denote the number of the agents not-yet-assigned until the {a mathematical formula}(i+1)-th iteration of the algorithm. Using the same reasoning as in Theorem 11 we show that {a mathematical formula}ni≤n(1−Qm)i. As before, our proof proceeds by induction on i. It is evident that the hypothesis is correct for {a mathematical formula}i=0. Now, assuming that {a mathematical formula}ni≤n(1−Qm)i, we assess {a mathematical formula}ni+1 as follows:{a mathematical formula} This proves the hypothesis. Thus, we can bound {a mathematical formula}nK:{a mathematical formula} This means that the satisfaction of the assignment Φ returned by our algorithm is at least:{a mathematical formula} In effect, it holds that:{a mathematical formula} This completes the proof.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>