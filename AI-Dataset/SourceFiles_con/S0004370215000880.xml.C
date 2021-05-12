<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Fair assignment of indivisible objects under ordinal preferences.
   </title>
   <abstract>
    We consider the discrete assignment problem in which agents express ordinal preferences over objects and these objects are allocated to the agents in a fair manner. We use the stochastic dominance relation between fractional or randomized allocations to systematically define varying notions of proportionality and envy-freeness for discrete assignments. The computational complexity of checking whether a fair assignment exists is studied for these fairness notions. We also characterize the conditions under which a fair assignment is guaranteed to exist. For a number of fairness concepts, polynomial-time algorithms are presented to check whether a fair assignment exists. Our algorithmic results also extend to the case of unequal entitlements of agents. Our NP-hardness result, which holds for several variants of envy-freeness, answers an open question posed by Bouveret, Endriss, and Lang (ECAI 2010). We also propose fairness concepts that always suggest a non-empty set of assignments with meaningful fairness properties. Among these concepts, optimal proportionality and optimal weak proportionality appear to be desirable fairness concepts.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A basic yet widely applicable problem in computer science and economics is to allocate discrete objects to agents given the preferences of the agents over the objects. The setting is referred to as the assignment problem or the house allocation problem (see, e.g., [1], [8], [28], [32], [40], [50], [51]). In this setting, there is a set of agents {a mathematical formula}N={1,…,n}, a set of objects {a mathematical formula}O={o1,…,om} with each agent {a mathematical formula}i∈N expressing ordinal preferences {a mathematical formula}≿i over O. The goal is to allocate the objects among the agents in a fair or optimal manner without allowing transfer of money. The assignment problem is a fundamental setting within the wider domain of fair division or multiagent resource allocation[23]. The model is applicable to many resource allocation or fair division settings where the objects may be public houses, school seats, course enrollments, kidneys for transplant, car park spaces, chores, joint assets of a divorcing couple, or time slots in schedules. Fair division has become a major area in AI research in the last decade, and especially the last few years (see, e.g., [3], [12], [13], [14], [15], [18], [23], [25], [29], [37], [44]).
     </paragraph>
     <paragraph>
      In this paper, we consider the fair assignment of indivisible objects. Two of the most fundamental concepts of fairness are envy-freeness and proportionality. Envy-freeness requires that no agent considers that another agent's allocation would give him more utility than his own. Proportionality requires that each agent should get an allocation that gives him at least {a mathematical formula}1/n of the utility that he would get if he was allocated all the objects. When agents' ordinal preferences are known but utility functions are not given, then ordinal notions of envy-freeness and proportionality need to be formulated. We consider a number of ordinal fairness concepts. Most of these concepts are based on the stochastic dominance (SD) relation which is a standard way of comparing fractional/randomized allocations. An agent prefers one allocation over another with respect to the SD relation if he gets at least as much utility from the former allocation as the latter for all cardinal utilities consistent with the ordinal preferences. Although this paper is restricted to discrete assignments, using stochastic dominance to define fairness concepts for discrete assignments turns out to be fruitful. The fairness concepts we study include SD envy-freeness, weak SD envy-freeness, possible envy-freeness, SD proportionality, and weak SD proportionality. We consider the problems of computing a discrete assignment that satisfies some ordinal notion of fairness if one exists, and the problems of verifying whether a given assignment satisfies the fairness notions.
     </paragraph>
     <section>
      <section>
       <section>
        <section-title>
         Contributions
        </section-title>
        <paragraph>
         We present a systematic way of formulating fairness properties in the context of the assignment problem. The logical relationships between the properties are proved. Interestingly, our framework leads to new solution concepts such as weak SD proportionality that have not been studied before. The motivation to study a range of fairness properties is that, depending on the situation, only some of them are achievable. In addition, only some of them can be computed efficiently. In order to find fairest achievable assignment, one can start by checking whether there exists a fair assignment for the strongest notion of fairness. If not, one can try the next fairness concept that is weaker than the one already checked (Fig. 1).
        </paragraph>
        <paragraph>
         We present a comprehensive study of the computational complexity of computing fair assignments under ordinal preferences. In particular, we present a polynomial-time algorithm to check whether an SD proportional exists even when agents may express indifferences. The algorithm generalizes the main result of [46] (Theorem 1) who focused on strict preferences. For the case of two agents, we obtain a polynomial-time algorithm to check whether an SD envy-free assignment exist. The result generalizes Proposition 2 in [12] in which preferences over objects were assumed to be strict. For a constant number of agents, we propose a polynomial-time algorithm to check whether a weak SD proportional assignment exists. As a corollary, for two agents, we obtain a polynomial-time algorithm to check whether a weak SD envy-free or a possible envy-free assignment exists. Even for an unbounded number of agents, if the preferences are strict, we characterize the conditions under which a weak SD proportional assignment exists. We show that the problems of checking whether possible envy-free, SD envy-free, or weak SD envy-free assignments exist are NP-complete. The result for possible envy-freeness answers an open problem posed in [12]. Our computational results are summarized in Table 1.
        </paragraph>
        <paragraph>
         We show that our two main algorithms can be extended to the case where agents have different entitlements over the objects or if we additionally require the assignment to be Pareto optimal. Our study highlights the impacts of the following settings: i) randomized/fractional versus discrete assignments, ii) strict versus non-strict preferences, and iii) multiple objects per agent versus a single object per agent.
        </paragraph>
        <paragraph>
         Since the fairness concepts we introduce may not be guaranteed to exist, we suggest possible ways to extend the fairness concepts. Firstly, we consider the problem of maximizing the number of agents for whom the corresponding fairness constraint is satisfied. A criticism of this approach is that there can still be agents who are completely dissatisfied. We then consider an alternative approach in which the proportionality constraints is weakened in a natural and gradual manner. We refer to the concepts as optimal proportionality and optimal weak proportionality. The fairness concepts are not only attractive but we show that an optimal proportional assignment can be computed in polynomial time and an optimal weak proportional assignment can be computed in polynomial time for a constant number of agents.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Proportionality and envy-freeness are two of the most established fairness concepts. Proportionality dates back to at least the work of Steinhaus [48] in the context of cake-cutting. It is also referred to as fair share guarantee in the literature [41]. A formal study of envy-freeness in microeconomics can be traced back to the work of Foley [31].
     </paragraph>
     <paragraph>
      The computation of fair discrete assignments has been intensely studied in the last decade within computer science. In many of the papers considered, agents express cardinal utilities for the objects and the goal is to compute fair assignments (see, e.g., [9], [13], [15], [28], [35], [39], [42], [45]). A prominent paper is that of Lipton et al. [39] in which algorithms for approximately envy-free assignments are discussed. It follows from [39] that even when two agents express cardinal utilities, checking whether there exists a proportional or envy-free assignment is NP-complete. A closely related problem is the Santa Claus problem in which the agents again express cardinal utilities for objects and the goal is to compute an assignment which maximizes the utility of the agent that gets the least utility (see e.g., [2], [9], [30], [42]). Just as in [12], [46], we consider the setting in which agents only express ordinal preferences over objects. There are some merits of considering this setting. Firstly, ordinal preferences require elicitation of less information from the agents. Secondly, some of the weaker ordinal fairness concepts we consider may lead to positive existence or computational results. Thirdly, some of the stronger ordinal fairness concepts we consider are more robust than the standard fairness concepts. Fourthly, when the exchange of money is not possible, mechanisms that elicit cardinal preferences may be more susceptible to manipulation because of the larger strategy space. Finally, it may be the case that cardinal preferences are simply not available.
     </paragraph>
     <paragraph>
      There are other papers in fair division in which agents explicitly express ordinal preferences over sets of objects rather than simply expressing preferences over objects. For these more expressive models, the computational complexity of computing fair assignments is either even higher [23], [27] or representing preferences require exponential space [3], [20]. In this paper, we restrict agents to simply express ordinal preferences over objects. Some papers assume ordinal preferences but superimpose a cardinal utilities via some scoring function (see e.g., [16]). However, this approach does not allow for indifferences in a canonical way and has led to negative complexity results [8], [26], [33]. Garg et al. [33] assumed that agents have lexicographic preferences and tried to maximize the lexicographic signature of the worst off agents. However the problem is NP-hard if there are more than two equivalence classes.
     </paragraph>
     <paragraph>
      The ordinal fairness concepts we consider are SD envy-freeness; weak SD envy-freeness; possible envy-freeness; SD proportionality; and weak SD proportionality. Not all of these concepts are new but they have not been examined systematically for discrete assignments. SD envy-freeness and weak SD envy-freeness have been considered in the randomized assignment domain [11] but not the discrete domain. Bogomolnaia and Moulin [11] referred to SD envy-freeness and weak SD envy-freeness as envy-freeness and weak envy-freeness. SD envy-freeness and weak SD envy-freeness have been considered implicitly for discrete assignments but the treatment was axiomatic [16], [17]. Mathematically equivalent versions of SD envy-freeness and weak SD envy-freeness have been considered by Bouveret et al. [12] but only for strict preferences. They referred to them as necessary (completion) envy-freeness and possible (completion) envy-freeness. A concept equivalent to SD proportionality was examined by Pruhs and Woeginger [46] but again only for strict preferences. Pruhs and Woeginger [46] referred to weak SD proportionality simply as ordinal fairness. Interestingly, weak SD or possible proportionality has not been studied in randomized or discrete settings (to the best of our knowledge).
     </paragraph>
     <paragraph>
      Envy-freeness is well-established in fair division, especially cake-cutting. Fair division of goods has been extensively studied within economics but in most of the papers, either the goods are divisible or agents are allowed to use money to compensate each other (see e.g., [49]). In the model we consider, we do not allow money transfers.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      An assignment problem is a triple {a mathematical formula}(N,O,≿) such that {a mathematical formula}N={1,…,n} is a set of agents, {a mathematical formula}O={o1,…,om} is a set of objects, and the preference profile {a mathematical formula}≿=(≿1,…,≿n) specifies for each agent i his complete and transitive preference {a mathematical formula}≿i over O. Agents may be indifferent among objects. We denote {a mathematical formula}≿i:Ei1,…,Eiki for each agent i with equivalence classes in decreasing order of preferences. Thus, each set {a mathematical formula}Eij is a maximal equivalence class of objects among which agent i is indifferent, and {a mathematical formula}ki is the number of equivalence classes of agent i. If an equivalence class is a singleton {a mathematical formula}{o}, we list the object o in the list without the curly brackets. In case each equivalence class is a singleton, the preferences are said to be strict. For any set of objects {a mathematical formula}O′⊆O, {a mathematical formula}max≿i⁡(O′)={o∈O′:o≿io′ for each o′∈O′} and {a mathematical formula}min≿i⁡(O′)={o∈O′:o′≿io for each o′∈O′}.
     </paragraph>
     <paragraph>
      A fractional assignment p is an {a mathematical formula}(n×m) matrix {a mathematical formula}[p(i)(oj)] such that {a mathematical formula}p(i)(oj)∈[0,1] for all {a mathematical formula}i∈N, and {a mathematical formula}oj∈O, and {a mathematical formula}∑i∈Np(i)(oj)=1 for all {a mathematical formula}j∈{1,…,m}. The value {a mathematical formula}p(i)(oj) represents the probability of object {a mathematical formula}oj being allocated to agent i. Each row {a mathematical formula}p(i)=(p(i)(o1),…,p(i)(om)) represents the allocation of agent i. The set of columns correspond to the objects {a mathematical formula}o1,…,om. A fractional assignment is discrete if {a mathematical formula}p(i)(o)∈{0,1} for all {a mathematical formula}i∈N and {a mathematical formula}o∈O.
     </paragraph>
     <paragraph label="Example 1">
      Consider an assignment problem {a mathematical formula}(N,O,≿) where {a mathematical formula}|N|=2, {a mathematical formula}O=o1,o2,o3,o4 and the preferences of the agents are as follows{a mathematical formula}{a mathematical formula} Then,{a mathematical formula} is a discrete assignment in which agent 1 gets {a mathematical formula}o1 and {a mathematical formula}o4 and agent 2 gets {a mathematical formula}o2 and {a mathematical formula}o3.
     </paragraph>
     <paragraph>
      A uniform assignment is a fractional assignment in which each agent gets {a mathematical formula}1/n-th of each object. Although we will deal with discrete assignments, the fractional uniform assignment is useful in defining some fairness concepts. Similarly, we will use the SD relation to define relations between assignments. Our algorithmic focus will be on computing discrete assignments only even though concepts are defined using the framework of fractional assignments.
     </paragraph>
     <paragraph>
      Informally, an agent ‘SD prefers’ one allocation over another if for each object o, the former allocation gives the agent at least as many objects that are at least as preferred as o as the latter allocation. More formally, given two fractional assignments p and q, {a mathematical formula}p(i)≿iSDq(i), i.e., agent i SD prefers allocation {a mathematical formula}p(i) to allocation {a mathematical formula}q(i) if{a mathematical formula} He strictly SD prefers{a mathematical formula}p(i) to {a mathematical formula}q(i) if {a mathematical formula}p(i)≿iSDq(i) and {a mathematical formula}¬[q(i)≿iSDp(i)]. Although each agent i expresses ordinal preferences over objects, he could have a private cardinal utility {a mathematical formula}ui consistent with {a mathematical formula}≿i: {a mathematical formula}ui(o)≥ui(o′) if and only if o≿io′. The set of all utility functions consistent with {a mathematical formula}≿i is denoted by {a mathematical formula}U(≿i). When we consider agents' valuations according to their cardinal utilities, then we will assume additivity, that is {a mathematical formula}ui(O′)=∑o∈O′ui(o) for each {a mathematical formula}i∈N and {a mathematical formula}O′⊆O.
     </paragraph>
     <paragraph>
      An assignment p is envy-free if the total utility each agent i gets for his allocation is at least the utility he would get if he had any another agent's allocation:{a mathematical formula} Note that we sometimes interpret a discrete allocation {a mathematical formula}p(i) as a set, namely the set of objects allocated to agent i. An assignment is proportional if each agent gets at least {a mathematical formula}1/n-th of the utility he would get if he got all the objects:{a mathematical formula}
     </paragraph>
     <paragraph>
      Note that we require that the assignment is complete, that is, each object is allocated. In the context of fractional assignments, an assignment is complete if no fraction of an object is unallocated. In the absence of this requirement a null assignment is obviously envy-free. On the other hand a null assignment is not proportional.
     </paragraph>
     <paragraph>
      When allocations are discrete and when agents may get more than one object, we will also consider preference relations over sets of objects. One way of extending preferences over objects to preferences over sets of objects is via the responsive set extension[7]. In the responsive set extension, preferences over objects are extended to preferences over sets of objects in such a way that a set in which an object is replaced by a more preferred object is more preferred. Formally, for each agent {a mathematical formula}i∈N, his preferences {a mathematical formula}≿i over O are extended to his preferences {a mathematical formula}≿iRS over {a mathematical formula}2O via the responsive set extension as follows. For all {a mathematical formula}S⊂O, for all {a mathematical formula}o∈S, for all {a mathematical formula}o′∈O∖S,{a mathematical formula} Equivalent, we say that {a mathematical formula}p(i)≿iRSq(i) if and only if there is an injection f from {a mathematical formula}q(i) to {a mathematical formula}p(i) such that for each {a mathematical formula}o∈q(i), {a mathematical formula}f(o)≿io.
     </paragraph>
     <paragraph label="Theorem 1">
      For discrete assignments p and q, the following are equivalent.
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}p(i)≿iSDq(i).
      </list-item>
      <list-item>
       {a mathematical formula}∀ui∈U(≿i),ui(p(i))≥ui(q(i)).
      </list-item>
      <list-item>
       {a mathematical formula}p(i)≿iRSq(i).
      </list-item>
     </list>
     <paragraph label="Proof">
      Firstly, (i) and (ii) are known to be equivalent (see e.g., [4], [24], [38]).We now show that (iii) implies (ii). If {a mathematical formula}p(i)≿iRSq(i), then we know that for each object allocated to i in {a mathematical formula}q(i), there is an injection which maps the object to an object in {a mathematical formula}p(i) which is at least as preferred by i. Hence, for each {a mathematical formula}ui∈U(≿i), we have that {a mathematical formula}ui(p(i))≥ui(q(i)).We now show that (i) implies (iii). Assume that {a mathematical formula}p(i)≿̸iRSq(i). Consider a bipartite graph {a mathematical formula}G=(q(i)∪p(i),E) where {a mathematical formula}{o,o′}∈E if {a mathematical formula}o∈q(i), {a mathematical formula}o′∈p(i), and {a mathematical formula}o′≿io. Since {a mathematical formula}p(i)≿̸iRSq(i), G does not have a matching saturating {a mathematical formula}q(i). Then by Hall's theorem, there exists a set {a mathematical formula}O′⊆q(i) such that {a mathematical formula}|N(O′)|&lt;|O′| where {a mathematical formula}N(O′) denote the neighborhood of {a mathematical formula}O′. Consider an object {a mathematical formula}o∈min≿i⁡(O′). We can assume without loss of generality that {a mathematical formula}O′ is maximal so that each {a mathematical formula}o⁎∈q(i) such that {a mathematical formula}o⁎≿io is in {a mathematical formula}O′ because this only increases the difference {a mathematical formula}|O′|−|N(O′)|. Note that {a mathematical formula}O′ is then {a mathematical formula}{o′:o′≿io}∩p(i) and {a mathematical formula}N(O′) is {a mathematical formula}{o′:o′≿io}∩q(i). Since, {a mathematical formula}|N(O′)|&lt;|O′|, we have that{a mathematical formula} But then {a mathematical formula}p(i)≿̸iSDq(i).  □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Fairness concepts under ordinal preferences
     </section-title>
     <paragraph>
      We now define fairness notions that are independent of the actual cardinal utilities of the agents. The fairness concepts are defined for fractional assignments. Since discrete assignments are special cases of fractional assignments, the concepts apply just as well to discrete assignments. For algorithmic problems, we will only consider those assignments that are discrete. The fairness concepts that are defined are with respect to the SD and RS relations as well as by quantifying over the set of utility functions consistent with the ordinal preferences.
     </paragraph>
     <section>
      <section>
       <section>
        <section-title>
         Proportionality
        </section-title>
        <list>
         <list-item>
          <list>
           <list-item label="(a)">
            Weak SD proportionality: An assignment p satisfies weak SD proportionality if no agent strictly SD prefers the uniform assignment to his allocation:{a mathematical formula}
           </list-item>
           <list-item label="(b)">
            Possible proportionality: An assignment satisfies possible proportionality if for each agent, there are cardinal utilities consistent with his ordinal preferences such that his allocation yields him as at least as much utility as he would get under the uniform assignment:{a mathematical formula}
           </list-item>
          </list>
         </list-item>
         <list-item>
          <list>
           <list-item label="(a)">
            SD proportionality: An assignment p satisfies SD proportionality if each agent SD prefers his allocation to the allocation under the uniform assignment:{a mathematical formula}
           </list-item>
           <list-item label="(b)">
            Necessary proportionality: An assignment satisfies necessary proportionality if it is proportional for all cardinal utilities consistent with the agents' preferences.{sup:1}{a mathematical formula}
           </list-item>
          </list>
         </list-item>
        </list>
       </section>
       <section>
        <section-title>
         Envy-freeness
        </section-title>
        <list>
         <list-item>
          <list>
           <list-item label="(a)">
            Weak SD envy-freeness: An assignment p satisfies weak SD envy-freeness if no agent strictly SD prefers someone else's allocation to his:{a mathematical formula}
           </list-item>
           <list-item label="(b)">
            Possible envy-freeness: An assignment satisfies possible envy-freeness if for each agent, there are cardinal utilities consistent with his ordinal preferences such that his allocation yields him as at least as much utility as he would get if he was given any other agent's allocation.{a mathematical formula}
           </list-item>
           <list-item label="(c)">
            Possible completion envy-freeness: An assignment satisfies possible completion envy-freeness[12] if for each agent, there exists a preference relation of the agent over sets of objects that is a weak order consistent with the responsive set extension such that the agent weakly prefers his allocation over the allocations of other agents. The concept has also been referred to as not “envy-ensuring” [17].
           </list-item>
          </list>
         </list-item>
         <list-item>
          <list>
           <list-item label="(a)">
            SD envy-freeness: An assignment p satisfies SD envy-freeness if each agent SD prefers his allocation to that of any other agent:{a mathematical formula}
           </list-item>
           <list-item label="(b)">
            Necessary envy-freeness: An assignment satisfies necessary envy-freeness if it is envy-free for all cardinal utilities consistent with the agents' preferences.{a mathematical formula}
           </list-item>
           <list-item label="(c)">
            Necessary completion envy-freeness: An assignment satisfies necessary completion envy-freeness[12] if for each agent, and each total order consistent with the responsive set extension of the agents, each agent weakly prefers his allocation to any other agents' allocation. The concept has also been referred to as not envy-possible[17].
           </list-item>
          </list>
         </list-item>
        </list>
        <paragraph>
         We consider the assignment problem in Example 1 to illustrate some of the fairness notions.
        </paragraph>
        <paragraph label="Example 2">
         Consider an assignment problem {a mathematical formula}(N,O,≿) where {a mathematical formula}|N|=2, {a mathematical formula}O=o1,o2,o3,o4 and the preferences of the agents are as follows{a mathematical formula}{a mathematical formula}Consider the discrete assignment p in which agent 1 gets {a mathematical formula}o1 and {a mathematical formula}o4 and agent 2 gets {a mathematical formula}o2 and {a mathematical formula}o3. The assignment p is not SD proportional or SD envy-free because the fairness constraints for agent 1 are not satisfied. However, p is weak SD proportional, possible envy-free, and weak SD envy-free.
        </paragraph>
        <paragraph>
         Possible completion envy-freeness and necessary completion envy-freeness were simply referred to as possible and necessary envy-freeness in [12]. We will use the former terms to avoid confusion.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Relations between fairness concepts
     </section-title>
     <paragraph>
      In this section, we highlight the inclusion relationships between fairness concepts (see Fig. 1). Based on the connection between the SD relation and utilities (Theorem 1), we obtain the following equivalences. The equivalences are also summarized in Table 2.
     </paragraph>
     <paragraph label="Theorem 2">
      For any number of agents and objects,
     </paragraph>
     <list>
      <list-item>
       Weak SD proportionality and possible proportionality are equivalent;
      </list-item>
      <list-item>
       SD proportionality and necessary proportionality are equivalent;
      </list-item>
      <list-item>
       weak SD envy-freeness and possible completion envy-freeness are equivalent;
      </list-item>
      <list-item>
       SD envy-freeness, necessary envy-freeness and necessary completion envy-freeness are equivalent.
      </list-item>
     </list>
     <paragraph label="Proof">
      We deal with each case separately.
     </paragraph>
     <list>
      <list-item>
       The statement follows directly from the characterization of the SD relation.
      </list-item>
      <list-item>
       The statement follows directly from the characterization of the SD relation.
      </list-item>
      <list-item>
       If an assignment is weak SD envy-free, then each agent either SD prefers his allocation over another agent's allocation or finds them incomparable. In case of incomparability, the relation can be completed with the agent's own allocation being more preferred. Thus the assignment is also possible completion envy-free. If an assignment is possible completion envy-free, then either an agent prefers his allocation over another agent's allocation with respect to the responsive set extension or finds them incomparable with respect to the responsive set extension. Hence each agent either SD prefers his allocation over another agent's allocation or finds them incomparable. Thus the assignment is also weak SD envy-free.
      </list-item>
      <list-item>
       It follows from Theorem 1 that SD envy-freeness and necessary envy-freeness are equivalent. We now prove that SD envy-freeness and necessary completion envy-freeness are equivalent. Note that an agent SD prefers his allocation over other agents' allocation if and only if he prefers his allocation with respect to the responsive set extension over other agents' allocation. □
      </list-item>
     </list>
     <paragraph>
      It is well-known that when an allocation is complete and utilities are additive, envy-freeness implies proportionality. Assume that an assignment p is envy-free. Then for each {a mathematical formula}i∈N, {a mathematical formula}ui(p(i))≥ui(p(j)) for all {a mathematical formula}j∈N. Thus, {a mathematical formula}n⋅ui(p(i))≥∑j∈Nui(p(j))=ui(O). Hence {a mathematical formula}ui(p(i))≥ui(O)/n. We can also get similar relations when we consider stronger and weaker notions of envy-freeness and proportionality.
     </paragraph>
     <paragraph label="Theorem 3">
      The following relations hold between the fairness concepts defined.
     </paragraph>
     <list>
      <list-item>
       SD envy-freeness implies SD proportionality.
      </list-item>
      <list-item>
       SD proportionality implies weak SD proportionality.
      </list-item>
      <list-item>
       Possible envy-freeness implies weak SD proportionality.
      </list-item>
      <list-item>
       Possible envy-freeness implies weak SD envy-freeness.
      </list-item>
     </list>
     <paragraph label="Proof">
      We deal with the cases separately.
     </paragraph>
     <list>
      <list-item>
       SD envy-freeness implies SD proportionality. Assume an assignment p satisfies SD envy-freeness. Then, by Theorem 2(iv), it satisfies envy-freeness for all utilities consistent with the ordinal preferences. If an assignment satisfies envy-freeness for particular cardinal utilities, it satisfies proportionality for the same cardinal utilities. Therefore, p satisfies proportionality for all cardinal utilities consistent with the ordinal preferences. Hence, due to Theorem 2(ii), it implies that p satisfies SD proportionality.
      </list-item>
      <list-item>
       SD proportionality implies weak SD proportionality. Assume an assignment p does not satisfy weak SD proportionality. Then, there exists some agent {a mathematical formula}i∈N such that {a mathematical formula}(1/n,…,1/n)≻iSDp(i). But this implies that {a mathematical formula}¬[p(i)≿iSD(1/n,…,1/n)]. Hence p is not SD proportional.
      </list-item>
      <list-item>
       Possible envy-freeness implies weak SD proportionality. Assume an assignment p is not weak SD proportional. By Theorem 2, p is not possible proportional. Let {a mathematical formula}i∈N be an agent such that for all {a mathematical formula}ui∈U(≿i) we have that {a mathematical formula}ui(p(i))&lt;ui(O)/n. But then, for each {a mathematical formula}ui∈U(≿i) there exists an agent {a mathematical formula}j∈N such that {a mathematical formula}ui(p(i))&lt;ui(p(j)), otherwise {a mathematical formula}n⋅ui(p(i))≥ui(O). Hence p is not possible envy-free.
      </list-item>
      <list-item>
       Possible envy-freeness implies weak SD envy-freeness. Assume that an assignment p is not weak SD envy-free. Therefore there exist {a mathematical formula}i,j∈N such that {a mathematical formula}p(j)≻iSDp(i). Due to Theorem 1, we get that for each {a mathematical formula}ui∈U(≿i), ui(p(j))&gt;ui(p(i)). Hence p is not possible envy-free. □
      </list-item>
     </list>
     <paragraph>
      We also highlight certain equivalences for the special case of two agents.
     </paragraph>
     <paragraph label="Theorem 4">
      For two agents,
     </paragraph>
     <list>
      <list-item>
       proportionality is equivalent to envy-freeness;
      </list-item>
      <list-item>
       SD proportionality is equivalent to SD envy-freeness;
      </list-item>
      <list-item>
       weak SD proportionality and possible envy-freeness are equivalent; and
      </list-item>
      <list-item>
       weak SD envy-freeness and weak SD proportionality are equivalent.
      </list-item>
     </list>
     <paragraph label="Proof">
      We deal with the cases separately while assuming {a mathematical formula}n=2. Since {a mathematical formula}n=2, for any agent i, we will denote by −i the other agent.
     </paragraph>
     <list>
      <list-item>
       Proportionality is equivalent to envy-freeness. Since envy-freeness implies proportionality, we only need to show that for two agents proportionality implies envy-freeness. Assume that an assignment is not envy-free. Then,{a mathematical formula}
      </list-item>
      <list-item>
       SD proportionality is equivalent to SD envy-freeness. We note that for {a mathematical formula}n=2, if an assignment satisfies envy-freeness for particular cardinal utilities, it satisfies proportionality for those cardinal utilities. Moreover, if an assignment is SD proportional, it satisfies proportionality for all cardinal utilities, hence it satisfies envy-freeness for all cardinal utilities and hence it satisfies SD envy-freeness.
      </list-item>
      <list-item>
       Weak SD proportionality and possible envy-freeness are equivalent. By Theorem 3(iii), possible envy-freeness implies weak SD proportionality. If an assignment satisfies weak SD proportionality, then there exist cardinal utilities consistent with the ordinal preferences for which proportionality is satisfied. Hence for {a mathematical formula}n=2, there exist cardinal utilities consistent with the ordinal preferences for which envy-freeness is satisfied, which means that the assignment satisfies possible envy-freeness.
      </list-item>
      <list-item>
       Weak SD envy-freeness and weak SD proportionality are equivalent. We have already shown that weak SD proportionality implies possible envy-freeness for {a mathematical formula}n=2, and that possible envy-freeness implies weak SD envy-freeness. Therefore, it is sufficient to prove that weak SD envy-freeness implies weak SD proportionality. Assume that an assignment p is not weak SD proportional. Then, there exists at least one agent {a mathematical formula}i∈{1,2} such that{a mathematical formula} for all {a mathematical formula}k∈{1,…,ki} and{a mathematical formula} for some {a mathematical formula}k∈{1,…,ki}. But this implies that{a mathematical formula} for all {a mathematical formula}k∈{1,…,ki} and{a mathematical formula} for some {a mathematical formula}k∈{1,…,ki}. Thus {a mathematical formula}p(−i)≻iSDp(i) and hence p is not weak SD envy-free. □
      </list-item>
     </list>
     <paragraph>
      In the next examples, we show that some of the inclusion relations do not hold in the opposite direction and that some of the solution concepts are incomparable. Firstly, we show that SD proportionality does not imply weak SD envy-freeness.
     </paragraph>
     <paragraph label="Example 3">
      SD proportionality does not imply weak SD envy-freeness. Consider the following preference profile:{a mathematical formula}{a mathematical formula}{a mathematical formula} The allocation that gives {a mathematical formula}{a,d} to agent 1, {a mathematical formula}{b,c} to agent 2 and {a mathematical formula}{e,f} to agent 3 is SD proportional. However it is not weak SD envy-free since agent 1 is envious of agent 2. Hence it also follows that SD proportionality does not imply possible envy-freeness or SD envy-freeness.
     </paragraph>
     <paragraph>
      Next, we show that weak SD envy-freeness neither implies possible envy-freeness nor weak SD proportionality.
     </paragraph>
     <paragraph label="Example 4">
      Weak SD envy-freeness neither implies possible envy-freeness nor weak SD proportionality. Consider an assignment problem in which {a mathematical formula}N={1,2,3}, and there are 4 copies of A, 6 copies of B, 1 copy of C and 1 copy of D. Let the preference profile be as follows.{a mathematical formula}{a mathematical formula}{a mathematical formula}Clearly p, the assignment specified in Table 3 is weak SD envy-free. Assume that p is also possible envy-free. Let {a mathematical formula}u1 be the utility function of agent 1 for which he does not envy agent 2 or 3. Let {a mathematical formula}u1(A)=a; {a mathematical formula}u1(B)=b; {a mathematical formula}u1(C)=c; and {a mathematical formula}u1(D)=d. Since {a mathematical formula}A≻1B≻1C≻1D, we get that{a mathematical formula} Since p is possible envy-free, {a mathematical formula}u1(p(1))≥u1(p(2)) iff a+b+c+d≥3a iff a≤b+c+d2which implies a&lt;3b2. Since p is possible envy-free, {a mathematical formula}u1(p(1))≥u1(p(3)) iff {a mathematical formula}a+b+c+d≥5b iff {a mathematical formula}a+c+d≥4b. Since {a mathematical formula}a&gt;b&gt;c&gt;d, it follows that {a mathematical formula}a&gt;2b. This is a contradiction since both {a mathematical formula}a&lt;3b2 and {a mathematical formula}a≥2b cannot hold.Now we show that weak SD envy-freeness does not even imply weak SD proportionality. Assignment p is weak SD envy-free. If it were weak SD proportional then there exists a utility function {a mathematical formula}u1 such that {a mathematical formula}u1(a)+u1(b)+u1(c)+u1(d)≥4u1(a)+6u1(b)+u1(c)+u1(d)3 which means that {a mathematical formula}u1(a)3+u1(b)≤2u1(c)3+2u1(d)3 which is equivalent to {a mathematical formula}a3+b≤2c3+2d3. But this is not possible because of (1).
     </paragraph>
     <paragraph>
      Since, we have shown that weak SD envy-freeness is not equivalent to possible envy-freeness, and since we showed in Theorem 2(iii) that weak SD envy-freeness is equivalent to possible completion envy-freeness, this means that possible envy-freeness and possible completion envy-freeness are also not equivalent to each other. We now point out that possible envy-freeness does not imply SD proportionality.
     </paragraph>
     <paragraph label="Example 5">
      Possible envy-freeness does not imply SD proportionality. Consider an assignment problem with two agents with preferences {a mathematical formula}1:{a},{b,c} and {a mathematical formula}2:{a,b,c}. Then the assignment in which 1 gets a and 2 gets b and c is possible envy-free. However it is not SD proportional, because agent 1's allocation does not SD dominate the uniform allocation.
     </paragraph>
     <paragraph>
      Finally, we note that all notions of proportionality and envy-freeness are trivially satisfied if randomized assignments are allowed by giving each agent {a mathematical formula}1/n of each object. As we show here, achieving any notion of proportionality is a challenge when outcomes need to be discrete.
     </paragraph>
     <paragraph>
      Next, we study the existence and computation of fair assignments. Even the weakest fairness concepts like weak SD proportionality may not be possible to achieve: consider two agents with identical and strict preferences over two objects. This problem remains even if m is a multiple of n.
     </paragraph>
     <paragraph label="Example 6">
      A discrete weak SD proportional assignment may not exist even if m is a multiple of n. Consider the following preferences:{a mathematical formula}{a mathematical formula}{a mathematical formula} If all agents get 2 objects, then those agents that have to get at least one object from {a mathematical formula}{b1,b2} will get an allocation that is strictly SD dominated by {a mathematical formula}(1/3,…,1/3). Otherwise, at least one agent gets at most one object, and is therefore strictly SD dominated by the uniform assignment.If m is not a multiple of n, then an even simpler example shows that a weak SD proportional assignment may not exist. Consider the case when all agents are indifferent among all objects. Then the agent who gets less objects than {a mathematical formula}m/n will get an allocation that is strictly SD dominated by {a mathematical formula}(1/n,…,1/n).
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Computational complexity
     </section-title>
     <paragraph>
      In this paper, we consider the natural computational question of checking whether a discrete fair assignment exists and if it does exist then to compute it. The problem of verifying whether a (discrete or fractional) assignment is fair is easy for all the notions we defined.
     </paragraph>
     <paragraph label="Remark 1">
      It can be verified in time polynomial in n and m whether an assignment is fair for all notions of fairness considered in the paper. For possible envy-freeness, a linear program can be used to find the ‘witness’ cardinal utilities of the agents.
     </paragraph>
     <paragraph label="Remark 2">
      For a constant number of objects, it can be checked in polynomial time whether a fair discrete assignment exists for all notions of fairness considered in the paper. This is because the total number of discrete assignments is {a mathematical formula}nm.
     </paragraph>
     <paragraph>
      We note that if the assignment is not required to be discrete, then even SD envy-freeness can be easily achieved [38]. Finally, we have the following necessary condition for SD proportional and hence for SD envy-free assignments.
     </paragraph>
     <paragraph label="Proof">
      If p is a discrete SD proportional assignment, then m is a multiple of n and each agent gets{a mathematical formula}m/nobjects.If p is an SD proportional assignment, then the following constraint is satisfied for each agent {a mathematical formula}i∈N.{a mathematical formula} Each agent must get {a mathematical formula}m/n objects. If p is discrete, each agents gets {a mathematical formula}m/n objects only if m is a multiple of n.  □
     </paragraph>
     <section label="6.1">
      <section-title>
       SD proportionality
      </section-title>
      <paragraph>
       In this subsection, we show that it can be checked in polynomial time whether a discrete SD proportional assignment exists even in the case of indifferences. The algorithm is via a reduction to the problem of checking whether a bipartite graph admits a feasible b-matching.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}H=(VH,EH) be an undirected graph with vertex capacities {a mathematical formula}b:VH→N0 and edge capacities {a mathematical formula}c:EH→N0 where {a mathematical formula}N0 is the set of natural numbers including zero. Then, a b-matching of H is a function {a mathematical formula}m:EH→N0 such that {a mathematical formula}∑e∈{e′∈EH:v∈e′}m(e)≤b(v) for each {a mathematical formula}v∈VH, and {a mathematical formula}m(e)≤c(e) for all {a mathematical formula}e∈EH. The size of the b-matching m is defined as {a mathematical formula}∑e∈EHm(e). We point out that if {a mathematical formula}b(v)=1 for all {a mathematical formula}v∈VH, and {a mathematical formula}c(e)=1 for all {a mathematical formula}e∈EH then a maximum size b-matching is equivalent to a maximum cardinality matching. In a b-matching problem with upper and lower bounds, there further is a function {a mathematical formula}a:VH→N0. A feasible b-matching then is a function {a mathematical formula}m:EH→N0 such that {a mathematical formula}a(v)≤∑e∈{e′∈EH:v∈e′}m(e)≤b(v) for each {a mathematical formula}v∈VH, and {a mathematical formula}m(e)≤c(e) for all {a mathematical formula}e∈EH. If H is bipartite, then the problem of computing a maximum weight feasible b-matching with lower and upper bounds can be solved in strongly polynomial time (Chapter 35 [47]).
      </paragraph>
      <paragraph label="Theorem 6">
       It can be checked in polynomial time whether a discrete SD proportional assignment exists even if agents are allowed to express indifference between objects.
      </paragraph>
      <paragraph label="Proof">
       Consider {a mathematical formula}(N,O,≿). If m is not a multiple of n, then by Theorem 5, no discrete SD proportional assignment exists. In this case, in each discrete assignment p, there exists some agent {a mathematical formula}i∈N who gets less than {a mathematical formula}m/n objects. Thus, the following does not hold: {a mathematical formula}p(i)≿iSD(1/n,…,1/n). Hence we can now assume that m is a multiple of n i.e., {a mathematical formula}m=nc where c is a constant. We reduce the problem to checking whether a feasible b-matching exists for a graph {a mathematical formula}G=(V,E). Recall that {a mathematical formula}ki is the number of equivalence classes of agent i. For each agent i, and for each {a mathematical formula}ℓ∈{1,…,ki} we introduce a vertex {a mathematical formula}viℓ. For each {a mathematical formula}o∈O, we create a corresponding vertex with the same name. Now, {a mathematical formula}V={vi1,…,viki:i∈N}∪O. The graph G is bipartite with independent sets O and {a mathematical formula}V∖O. Let us now specify the edges of G:
       <list>
        for each {a mathematical formula}i∈N, {a mathematical formula}ℓ∈{1,…,ki} and {a mathematical formula}o∈O we have that {a mathematical formula}{viℓ,o}∈E if and only if {a mathematical formula}o∈⋃j=1ℓEij.We specify the lower and upper bounds of each vertex:
       </list>
       <list>
        <list-item label="•">
         {a mathematical formula}a(viℓ)=⌈∑j=1ℓ|Eij|n⌉−∑j=1ℓ−1a(vij) and {a mathematical formula}b(viℓ)=∞ for each {a mathematical formula}i∈N and {a mathematical formula}ℓ∈{1,…,ki};
        </list-item>
        <list-item label="•">
         {a mathematical formula}a(o)=b(o)=1 for each {a mathematical formula}o∈O.
        </list-item>
       </list>
       <paragraph>
        For each edge {a mathematical formula}e∈E, {a mathematical formula}c(e)=1.Now that {a mathematical formula}(V,E) has been specified, we check whether a feasible b-matching exists. If so, we allocate an object o to an agent i if the edge incident to o that is included in the matching is incident to a vertex corresponding to an equivalence class of agent i. We claim that a discrete SD proportional assignment exists if and only if a feasible b-matching exists. If a feasible b-matching exists, then each {a mathematical formula}o∈O is matched so we have a complete assignment. For each agent {a mathematical formula}i∈N, and for each {a mathematical formula}Eiℓ, an agent is allocated at least {a mathematical formula}⌈∑j=1ℓ|Eij|/n⌉ objects of the same or more preferred equivalence class. Thus, the assignment is SD proportional.On the other hand if a discrete SD proportional assignment p exists, then {a mathematical formula}p(i)≿iSD(1/n,…,1/n) implies that for each equivalence class {a mathematical formula}Eiℓ, an agent is allocated at least {a mathematical formula}⌈∑j=1ℓ|Eij|/n⌉ objects from the same or more preferred equivalence class as {a mathematical formula}Eiℓ. Hence there is a b-matching in which the lower bound of each vertex of the type {a mathematical formula}viℓ is met. For any remaining vertices {a mathematical formula}o∈O that have not been allocated, they may be allocated to any agent. Hence a feasible b-matching exists.  □
       </paragraph>
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Weak SD proportionality
      </section-title>
      <paragraph>
       In the previous subsection, we examined the complexity of checking the existence of SD proportional discrete assignments. In this section we consider weak SD proportionality.
      </paragraph>
      <paragraph label="Theorem 7">
       For strict preferences, a weak SD proportional discrete assignment exists if and only if one of two cases holds:
       <list>
        {a mathematical formula}m=nand it is possible to allocate to each agent an object that is not his least preferred object;{a mathematical formula}m&gt;n.Moreover, it can be checked in polynomial time whether a weak SD proportional discrete assignment exists when agents have strict preferences.
       </list>
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}m&lt;n, at least one agent will not get any object. Hence there exists no weak SD proportional discrete assignment. Hence {a mathematical formula}m≥n is a necessary condition for the existence of a weak SD proportional discrete assignment.Let us consider the case of {a mathematical formula}m=n. Clearly each agent needs to get one object. If an agent i gets an object that is not the least preferred object {a mathematical formula}o′, then his allocation {a mathematical formula}p(i) is weak SD proportional. The reason is that {a mathematical formula}∑o≻o′p(i)(o)=1&gt;|{o:o≻o′}|/n. Hence the following does not hold: {a mathematical formula}(1/n,…,1/n)≿iSDp(i). On the other hand, if i gets the least preferred object, his allocation is not weak SD proportional since {a mathematical formula}(1/m,…,1/m)≻iSDp(i). Hence, we just need to check whether there exists a discrete assignment in which each agent gets an object that is not least preferred. This can be solved as follows. We construct a graph {a mathematical formula}(V,E) such that {a mathematical formula}V=N∪O and for all {a mathematical formula}i∈N and {a mathematical formula}o∈O, {a mathematical formula}{i,o}∈E if and only if {a mathematical formula}o∉min≿i⁡(O). We just need to check whether {a mathematical formula}(V,E) has a perfect matching. If it does, the matching is a weak SD proportional discrete assignment.If {a mathematical formula}m≥n+1, we show that a weak SD proportional discrete assignment exists. Allocate the most preferred object to the agents in the following order {a mathematical formula}1,2,3,…n,n,n−1…,1,…. Then each agent {a mathematical formula}i∈{1,…,n−1} gets in the worst case his i-th most preferred object. This worst case occurs if agents preceding i pick the {a mathematical formula}i−1 most preferred objects of agent i. Even in this worst case, since {a mathematical formula}1&gt;i/n, we have that the allocation of agents in {a mathematical formula}{1,…,n−1} is weak SD proportional. As for agent n, in the worst case he get his n-th and {a mathematical formula}n+1st most preferred objects. Since {a mathematical formula}2≥nn+1n, by Lemma 1 we get that the allocation of agent n is also weak SD proportional. This completes the proof.  □
      </paragraph>
      <paragraph>
       Indifferences result in all sorts of challenges. Some arguments that we used for the case for strict preferences do not work for the case of indifferences. The case of strict preferences may lead one to wrongly assume that given a sufficient number of objects, a weak SD proportional discrete assignment is guaranteed to exist. However, if agents are allowed to express indifference, this is not the case. Consider the case where {a mathematical formula}m=nc+1 and each agent is indifferent among each of the objects. Then there exists no weak SD proportional discrete assignment because some agent will get fewer than {a mathematical formula}m/n objects. We first present a helpful lemma which follows directly from the definition of weak SD proportionality.
      </paragraph>
      <paragraph label="Lemma 1">
       An assignment p is weak SD proportional if and only if for each{a mathematical formula}i∈N,
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}∑o′≿op(i)(o′)&gt;|{o′:o′≿o}|/nfor some{a mathematical formula}o∈O; or
       </list-item>
       <list-item>
        {a mathematical formula}∑o′≿op(i)(o′)≥|{o′:o′≿o}|/nfor all{a mathematical formula}o∈O.
       </list-item>
      </list>
      <paragraph>
       We will use Lemma 1 in designing an algorithm to check whether a weak SD proportional discrete assignment exists when agents are allowed to express indifference.
      </paragraph>
      <paragraph label="Theorem 8">
       For a constant number of agents, it can be checked in polynomial time whether a weak SD proportional discrete assignment exists even if agents are allowed to express indifference between objects.
      </paragraph>
      <paragraph label="Proof">
       Consider {a mathematical formula}(N,O,≿). We want to check whether a weak SD proportional discrete assignment exists. By Lemma 1, this is equivalent to checking whether there exists a discrete assignment p, where for each {a mathematical formula}i∈N, one of the following {a mathematical formula}ki conditions holds: for {a mathematical formula}l∈{1,…,ki},{a mathematical formula} or the following {a mathematical formula}(ki+1)-st condition holds{a mathematical formula}The {a mathematical formula}(ki+1)-st condition only holds if each {a mathematical formula}|Eij| is a multiple of n for {a mathematical formula}j∈{1,…,ki}.We need to check whether there exists a discrete assignment in which for each agent one of the {a mathematical formula}ki+1 conditions is satisfied. In total there are {a mathematical formula}∏i=1n(ki+1) different ways in which the agents could be satisfied. We will now present an algorithm to check if there exists a feasible weakly SD proportional discrete assignment in which for each agent i, a certain condition among the {a mathematical formula}ki+1 conditions is satisfied. Since n is a constant, the total number of combinations of conditions is polynomial.We define a bipartite graph {a mathematical formula}G=(V,E) whose vertex set is initially empty. For each agent i, if the condition number is {a mathematical formula}ℓ∈{1,…,ki} then we add a vertex {a mathematical formula}viℓ. If the condition number is {a mathematical formula}ki+1, then we add {a mathematical formula}ki vertices – {a mathematical formula}Bij for each {a mathematical formula}Eij where {a mathematical formula}j∈{1,…,ki}. For each {a mathematical formula}o∈O, we add a corresponding vertex with the same name. The sets O and {a mathematical formula}V∖O will be independent sets in G. We now specify the edges of G.
       <list>
        {a mathematical formula}{viℓ,o}∈E if and only if {a mathematical formula}o∈⋃j=1ℓEij for each {a mathematical formula}i∈N, {a mathematical formula}ℓ∈{1,…,ki} and {a mathematical formula}o∈O.{a mathematical formula}{Bij,o}∈E if and only if {a mathematical formula}o∈Eij for each {a mathematical formula}i∈N, {a mathematical formula}j∈{1,…,ki}, and {a mathematical formula}o∈O.We specify the lower and upper bounds of each vertex.
       </list>
       <list>
        <list-item label="•">
         {a mathematical formula}a(viℓ)=⌊|⋃j=1ℓEij|n⌋+1 and {a mathematical formula}b(viℓ)=∞ for each {a mathematical formula}i∈N and {a mathematical formula}ℓ∈{1,…,ki};
        </list-item>
        <list-item label="•">
         {a mathematical formula}a(Bij)=b(Bij)=|Eij|n for each {a mathematical formula}Bij;
        </list-item>
        <list-item label="•">
         {a mathematical formula}a(o)=b(o)=1 for each {a mathematical formula}o∈O.
        </list-item>
       </list>
       <paragraph>
        For each edge {a mathematical formula}e∈E, {a mathematical formula}c(e)=1. For each n-tuple of satisfaction conditions, we construct the graph as specified above and then check whether there exists a feasible b-matching. A weak SD proportional discrete assignment exists if and only if a feasible b-matching exists for the graph corresponding to at least one of the {a mathematical formula}∏i=1n(ki+1) combinations of conditions. Since {a mathematical formula}∏i=1n(ki+1) is polynomial if n is a constant and since a feasible b-matching can be checked in strongly polynomial time, we can check the existence of a weak SD proportional discrete assignment in polynomial time.  □
       </paragraph>
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Envy-freeness
      </section-title>
      <paragraph>
       In this section, we examine the complexity of checking whether an envy-free assignment exists or not. Our positive algorithmic results for SD proportionality and weak SD proportionality help us obtain algorithms for SD envy-freeness and weak SD envy-freeness when {a mathematical formula}n=2.
      </paragraph>
      <paragraph>
       From Theorem 6, we get the following corollary.
      </paragraph>
      <paragraph label="Corollary 1">
       For two agents, it can be checked in polynomial time whether a discrete SD envy-free assignment exists even if agents are allowed to express indifference between objects.
      </paragraph>
      <paragraph label="Proof">
       For two agents, SD proportionality implies SD envy-freeness, and by Theorem 3, SD envy-freeness implies SD proportionality.  □
      </paragraph>
      <paragraph>
       Corollary 1 generalizes Proposition 10 of [12] which stated that for two agents and strict preferences, it can be checked in polynomial time whether a necessary envy-free discrete assignment exists.
      </paragraph>
      <paragraph>
       Similarly, from Theorem 8, we get the following corollary.
      </paragraph>
      <paragraph label="Corollary 2">
       For two agents, it can be checked in polynomial time whether a weak SD envy-free or a possible envy-free discrete assignment exists.
      </paragraph>
      <paragraph label="Proof">
       For two agents, weak SD proportional is equivalent to weak SD envy-free and possible envy-free (Theorem 4).  □
      </paragraph>
      <paragraph>
       We prove that checking whether a (weak) SD envy-free or possible envy-free discrete assignment exists is NP-complete. The complexity of the second problem was mentioned as an open problem in [12]. Bouveret et al. [12] showed that the problem of checking whether a necessary envy-free discrete assignment exists is NP-complete. The statement carries over to the more general domain that allows for ties. We point out that if agents have identical preferences, it can be checked in linear time whether an SD envy-free discrete assignment exists even when preferences are not strict. Identical preferences have received special attention within fair division (see e.g., [19]).
      </paragraph>
      <paragraph label="Theorem 9">
       For agents with identical preferences, an SD envy-free discrete assignment exists if and only if each equivalence class is a multiple of n.
      </paragraph>
      <paragraph>
       Even n is not constant but preferences are strict, it can be checked in time linear in n and m whether a complete weak SD envy-free discrete assignment exists. This follows from an equivalent result in [12] for possible completion envy-freeness and the fact that weak SD envy-freeness is equivalent to possible completion envy-freeness (Theorem 2(iii)). We use similar arguments as Bouveret et al. [12] for possible envy-freeness.
      </paragraph>
      <paragraph label="Proof">
       For strict preferences, it can be checked in time linear in n and m whether a possible envy-free discrete assignment exists.We reuse the arguments in the proof of (Proposition 4 [12]). Let the number of distinct top-ranked objects be k. If {a mathematical formula}m&lt;2n−k, then there is at least one agent who receives one object that is not his top-ranked o and no further items. Thus he necessarily envies the agent who received o and hence there cannot exist a possible envy-free discrete assignment. If {a mathematical formula}m≥2n−k, then we run the following algorithm. (1) For each of the k top-ranked objects, allocate it to an agent that ranks it first. Denote by {a mathematical formula}N′ the set of agents that have not yet received an object, and order them arbitrarily. (2) Go through the {a mathematical formula}n−k agents in {a mathematical formula}N′ in ascending order and ask them to claim their most preferred item from those still available. (3) Go through the agents in {a mathematical formula}N′ again, but this time in descending order, and ask them to claim their most preferred item from those still available. The agents who got their most preferred object do not envy any other agent if they have sufficiently high utility for their most preferred object. For the remaining agents, who have received two objects each, no agent i strictly SD prefers another agent j's current allocation: even if j (who had an earlier first turn) received a more preferred first object, i strictly prefers his second object to j's second object (in case j received a second object). Therefore, there exist cardinal utilities consistent with the ordinal preferences where the agents in {a mathematical formula}N′ put high enough utility for the second object they get so that they are not envious of other agents even if the other agent gets all the unallocated objects. Therefore the unallocated objects can be allocated in an arbitrary manner among the remaining agents and the resulting complete discrete assignment is still possible envy-free.  □
      </paragraph>
      <paragraph>
       Bouveret et al. [12] mentioned the complexity of possible completion envy-freeness for the case of indifferences as an open problem. We present a reduction to prove that for all notions of envy-freeness considered in this paper, checking the existence of a fair discrete assignment is NP-complete.
      </paragraph>
      <paragraph label="Theorem 11">
       The following problems are NP-complete:
      </paragraph>
      <list>
       <list-item>
        check whether there exists a weak SD envy-free (equivalently possible completion envy-free) discrete assignment,
       </list-item>
       <list-item>
        check whether there exists a possible envy-free discrete assignment, and
       </list-item>
       <list-item>
        check whether there exists an SD envy-free discrete assignment.
       </list-item>
      </list>
      <paragraph label="Proof">
       Membership in NP is shown by Remark 1. To show hardness we use a reduction from X3C (Exact Cover by 3-sets). In X3C, the input is a ground set S and a collection C containing 3-sets of elements from S, and the question is whether there exists a subcollection {a mathematical formula}X⊆C such that each element of S is contained in exactly one of the 3-sets in X. X3C is known to be NP-complete [36]. Consider an instance {a mathematical formula}(S,C) of X3C where {a mathematical formula}S={s1,…,s3q} and {a mathematical formula}C={c1,…,cl}. Without loss of generality, {a mathematical formula}l≥q. We construct the following assignment problem {a mathematical formula}(N,O,≿) where {a mathematical formula}N={a1,…,a40l} is partitioned into three sets {a mathematical formula}N1,N2 and {a mathematical formula}N3 with {a mathematical formula}|N1|=l, {a mathematical formula}|N2|=30l, {a mathematical formula}|N3|=9l and {a mathematical formula}O={o1,…,o120l} is partitioned into three sets {a mathematical formula}O1,O2 and {a mathematical formula}O3 with {a mathematical formula}|O1|=3l, {a mathematical formula}|O2|=90l and {a mathematical formula}|O3|=27l. The set {a mathematical formula}O1 is partitioned into two sets, {a mathematical formula}O1S and {a mathematical formula}O1B, the first one corresponding to the set of elements of S in the X3C instance and the second being a ‘buffer’ set. We have {a mathematical formula}|O1S|=3q and {a mathematical formula}|O1B|=3l−3q. We associate each {a mathematical formula}cj∈C with the j-th agent in {a mathematical formula}N1. With each {a mathematical formula}cj∈C we also associate nine consecutive agents in {a mathematical formula}N3. The preferences of the agents are defined as follows:
       <list>
        {a mathematical formula}i:O2∪ci,(O1\ci)∪O3 for {a mathematical formula}i∈N1{a mathematical formula}i:O2,O1∪O3 for all {a mathematical formula}i∈N2{a mathematical formula}i:f(i),O\f(i) for {a mathematical formula}i∈N3The function
       </list>
       <paragraph>
        {a mathematical formula}f:N3→2O is such that it ensures the following properties: For each of the three elements e of {a mathematical formula}cj, three out of the nine agents associated with {a mathematical formula}cj list e as a second choice object, and list {a mathematical formula}cj\{e} as first choice objects. Let us label these three agents {a mathematical formula}a1, {a mathematical formula}a2 and {a mathematical formula}a3. The sets of objects {a mathematical formula}f(a1), {a mathematical formula}f(a2) and {a mathematical formula}f(a3) each exclude a distinct {a mathematical formula}13 of the buffer objects {a mathematical formula}O1B. {a mathematical formula}f(a1), {a mathematical formula}f(a2) and {a mathematical formula}f(a3) each contain 2/3 of the elements of {a mathematical formula}OB. The 1/3 elements that are excluded from each of these sets must be distinct i.e., elements that {a mathematical formula}f(a1) does not contain are contained in {a mathematical formula}f(a2) and {a mathematical formula}f(a3), and vice versa.For each {a mathematical formula}i∈N3, {a mathematical formula}f(i)∩(O2∪O3)=Of. Let {a mathematical formula}Of contain {a mathematical formula}23 of the elements of {a mathematical formula}O2 and {a mathematical formula}23 of the elements of {a mathematical formula}O3. Consider a discrete assignment that is weak SD envy-free or possible envy-free or SD envy-free. We can make the following observations:
       </paragraph>
       <list>
        <list-item>
         Agents in {a mathematical formula}N2 are allocated all objects from {a mathematical formula}O2 and none from {a mathematical formula}O\O2. To show this, first consider the case where 30l or more objects from {a mathematical formula}O2 are assigned to {a mathematical formula}N\N2. In this case, at least one agent in {a mathematical formula}N2 is envious of an agent from {a mathematical formula}N\N2: there will be an agent {a mathematical formula}b1 in {a mathematical formula}N\N2 with three or more objects from {a mathematical formula}O2, and there will be an agent {a mathematical formula}b2 in {a mathematical formula}N2 with at most three elements, at most two of which are from {a mathematical formula}O2. This is because if an agent has more than three objects, another has at most two and if they all have three, some of those will be objects from {a mathematical formula}O1, and at least one agent from {a mathematical formula}N2 will have a second choice object. For all considered notions of envy-freeness {a mathematical formula}b2 will be envious of {a mathematical formula}b1.If {a mathematical formula}0&lt;z1&lt;30l objects from {a mathematical formula}O2 are assigned to {a mathematical formula}N\N2, we have three cases:
        </list-item>
        <list-item>
         Each agent in {a mathematical formula}N2 is allocated exactly three objects. Since as shown above all and only {a mathematical formula}O2 objects go to {a mathematical formula}N2, not all agents in {a mathematical formula}N2 can have four objects. Therefore if one has four, those without four objects will envy him since they value all objects from {a mathematical formula}O2 the same.
        </list-item>
        <list-item>
         Each agent in {a mathematical formula}N2∪N1 has three objects. This is because if an agent in {a mathematical formula}N2∪N1 has four or more objects, another has two or less. The argument in the first observation still applies, and therefore this agent will be envious of at least one agent from {a mathematical formula}N2.
        </list-item>
        <list-item>
         Agents in {a mathematical formula}N1 will not be assigned any objects from {a mathematical formula}O3 since they all consider them to be second choices. To not envy agents in {a mathematical formula}N2 agents in {a mathematical formula}N1 have three of their preferred choices.
        </list-item>
        <list-item>
         Each agent in {a mathematical formula}N2∪N3 are given two of {a mathematical formula}N3's common preferred choices, and one of their second choices. This is the only way to avoid envy from an element of {a mathematical formula}N3 to at least one element of {a mathematical formula}N2∪N3: if an element of {a mathematical formula}N2 has two or three of {a mathematical formula}N3 second choices, then another has three preferred choices, and therefore at least one of {a mathematical formula}N3 will be envious of him. If an agent in {a mathematical formula}N3 has three preferred choices, then at least one has only one preferred choice, and will be envious of the agent with three preferred choices.
        </list-item>
        <list-item>
         An agent from {a mathematical formula}N1 does not have objects from {a mathematical formula}O1S and also {a mathematical formula}O1B, since otherwise at least one agent from {a mathematical formula}N3 will be envious of him. This is because of the conditions satisfied by f. There are at least three agents in {a mathematical formula}N3 who see the one or two selected elements from the three-set associated to the {a mathematical formula}N1 agent as first choice objects. For any set of elements of size two or less in {a mathematical formula}O1B, at least one of these three agents considers said set to be composed of first choice object. Therefore, there is at least one agent in {a mathematical formula}N3 who will be envious of an agent in {a mathematical formula}N1 who selects both from {a mathematical formula}O1S and {a mathematical formula}O1B, since he sees this agent as having three preferred choices whilst he only has two (according to the previous observation).
        </list-item>
       </list>
       <paragraph>
        If there exists an exact cover of S by a subset of C, then there is an SD envy-free discrete assignment since agents corresponding to elements of C used for the cover will be given their preferred items from {a mathematical formula}O1S and the others will be given items from {a mathematical formula}O1B.If there does not exist an exact cover of S by a subset of C then there does not exist a weak SD envy-free discrete assignment (equivalently an assignment in which no agent strictly prefers another agent's allocation with respect to responsive preferences). This is because even if all the previous conditions are respected, at least one agent from {a mathematical formula}N1 gets a second choice object and is envious of agents from {a mathematical formula}N2. This follows from the fact that no matter which agents of {a mathematical formula}N1 we assign buffer objects to, the remaining agents are not able to cover {a mathematical formula}O1S with their sets of most preferred objects. This completes the proof.  □
       </paragraph>
      </paragraph>
      <paragraph>
       In view of Theorem 1, the proof above also shows that when agents have responsive preferences over sets of objects, then checking whether there exists an envy-free (weak or strong) allocation is NP-complete. Another corollary is that is if agents have cardinal utilities 1 or 0 for objects, then checking whether there exists an envy-free assignment is NP-complete.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Extensions
     </section-title>
     <paragraph>
      In this section, we consider two extensions of our results: (i) additionally requiring Pareto optimality and (ii) handling varying entitlements. We show that our algorithmic results can be extended in both cases.
     </paragraph>
     <section label="7.1">
      <section-title>
       Additionally requiring Pareto optimality
      </section-title>
      <paragraph>
       We focused on fairness and only required a weak form of efficiency that each object is allocated. In this subsection, we seek discrete assignments that are both fair and Pareto optimal.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}(N,O,≿) be an assignment problem. A discrete assignment q Pareto dominates a discrete assignment p if {a mathematical formula}q(i)≿iSDp(i) for all {a mathematical formula}i∈N and {a mathematical formula}q(i)≻iSDp(i) for some {a mathematical formula}i∈N. We also say that q is a Pareto improvement over p. A discrete assignment p is Pareto optimal if there exists no discrete assignment q that Pareto dominates it.
      </paragraph>
      <paragraph label="Example 7">
       Consider the following assignment problem:{a mathematical formula}{a mathematical formula} The discrete assignment that gives {a mathematical formula}{b,c,f} to agent 1 and {a mathematical formula}{d,e,a} to agent 2 is SD proportional. However it is not Pareto optimal since it is SD-dominated by the assignment in which agent 1 gets {a mathematical formula}{a,b,c} and agent 2 gets {a mathematical formula}{d,e,f}.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}(N,O,≿) be an assignment problem and p be a discrete assignment. We will create an auxiliary assignment problem and assignment where each agent is allocated exactly one object. The clones of an agent {a mathematical formula}i∈N are the agents in {a mathematical formula}Ni′={io:o∈O and p(i)(o)=1}. The cloned assignment problem corresponding to assignment problem {a mathematical formula}(N,O,≿) and assignment p is {a mathematical formula}(N′,O,≿′) such that {a mathematical formula}N′=⋃i∈NNi′. and for each {a mathematical formula}io∈N′, {a mathematical formula}≿io′=≿i. The cloned assignment of p is the discrete assignment {a mathematical formula}p′ in which {a mathematical formula}p′(io)(o)=1 if {a mathematical formula}p(i)(o)=1 and {a mathematical formula}p′(io)(o)=0 otherwise.
      </paragraph>
      <paragraph>
       A cloned assignment can easily be transformed back into the original assignment where each agent {a mathematical formula}i∈N is allocated all the objects assigned by {a mathematical formula}p′ to the clones of i.
      </paragraph>
      <paragraph label="Lemma 2">
       A discrete assignment is Pareto optimal if and only if its cloned assignment is Pareto optimal for the cloned assignment problem.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}(N,O,≿) be an assignment problem and p be a discrete assignment. We will prove that p is not Pareto optimal if and only if its cloned assignment {a mathematical formula}p′ is not Pareto optimal for the cloned assignment problem {a mathematical formula}(N′,O,≿′).For the backwards direction, assume that {a mathematical formula}p′ is not Pareto optimal for {a mathematical formula}(N′,O,≿′). Then, there exists another discrete assignment {a mathematical formula}p′⁎ in which each of the cloned agents get at least as preferred an object and at least one agent gets a strictly more preferred object. But if {a mathematical formula}p′⁎ is transformed into the discrete assignment {a mathematical formula}p⁎ for the original assignment problem, then {a mathematical formula}p⁎ Pareto dominates p.For the forward direction, assume that p is not Pareto optimal. Then, there exists another discrete assignment {a mathematical formula}p⁎ that Pareto dominates it. But this implies that the cloned assignment of {a mathematical formula}p⁎ also Pareto dominates {a mathematical formula}p′ in {a mathematical formula}(N′,O,≿′) (modulo name changes among clones).  □
      </paragraph>
      <paragraph label="Lemma 3">
       If a discrete assignment is not Pareto optimal, a Pareto improvement that is Pareto optimal can be computed in polynomial time.
      </paragraph>
      <paragraph label="Proof">
       We first take the assignment problem and the given discrete assignment and construct the corresponding cloned assignment problem and cloned assignment. For such a cloned discrete assignment, a Pareto optimal Pareto improvement can be computed in polynomial time (see e.g., [6]). The updated cloned assignment is then transformed back into an assignment for the original assignment problem.  □
      </paragraph>
      <paragraph label="Remark 3">
       A Pareto improvement over a weak SD proportional or SD proportional discrete assignment is weak SD proportional or SD proportional, respectively. Therefore, if a (weak) SD proportional discrete assignment exists then there also exists a Pareto optimal and (weak) SD proportional discrete assignment.
      </paragraph>
      <paragraph>
       Based on Lemma 3 and Remark 3 we obtain the following theorems.
      </paragraph>
      <paragraph label="Theorem 12">
       If a Pareto optimal and SD proportional discrete assignment exists, it can be computed in polynomial time.
      </paragraph>
      <paragraph label="Theorem 13">
       For a constant number of agents, if a Pareto optimal and weak SD proportional discrete assignment exists, it can be computed in polynomial time.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Unequal entitlements
      </section-title>
      <paragraph>
       Throughout this paper, we assumed that each agent has the same entitlement to the objects. However, it could be the case that an agent {a mathematical formula}i∈N has entitlement {a mathematical formula}ei. There can be various reasons for unequal entitlements. An agent may be given more entitlement for the resources to reward his contributions and effort in obtaining the objects for the set of objects. Entitlements can also be used to model justified demand. For example, if an agent represents a different number of sub-agents, the agent who represents more sub-agents may have more entitlement. Unequal entitlements have been considered in the fair division literature (see, e.g., [22, page 44]).
      </paragraph>
      <paragraph>
       In the case of unequal entitlements, proportionality and envy-freeness can be redefined:{a mathematical formula} for proportionality and{a mathematical formula} for envy-freeness. For envy-freeness, the idea is that if agent i has half the entitlement of agent j, then i will only be envious of agent j if agent's j allocation gives agent i more than twice the utility agent i has for his own allocation. Just like possible and necessary fairness is defined for equal entitlements, the definitions can be extended for the case of unequal entitlements. Hence possible and necessary proportionality and envy-freeness are natural ordinal notions that can also take into account entitlements. Our two algorithms for possible and necessary proportionality can also be modified to cater for entitlements by replacing {a mathematical formula}1/n with {a mathematical formula}ei∑j∈Nej whenever a matching lower bound is specified for a vertex.
      </paragraph>
      <paragraph label="Theorem 14">
       For a constant number of agents, it can be checked in polynomial time whether a possible proportional discrete assignment exists even if agents have different entitlements.
      </paragraph>
      <paragraph label="Theorem 15">
       It can be checked in polynomial time whether a necessary proportional discrete assignment exists even if agents have different entitlements.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Fairness concepts that guarantee the existence of fair outcomes
     </section-title>
     <paragraph>
      We observed that there are instances where even the weakest fairness notions such as weak SD proportionality cannot be guaranteed. Hence the fairness notions considered are not proper solution concepts. In this section, we propose fairness concepts that always suggest a non-empty set of assignments with meaningful fairness properties.
     </paragraph>
     <section label="8.1">
      <section-title>
       Maximal and maximum fairness
      </section-title>
      <paragraph>
       We first seek a way out by considering corresponding solution concepts that maximize the number of agents being satisfied with their allocation. The idea has been used in matching theory where for example if a stable matching does not exist, then one may aim to minimize the number of unstable pairs (see, e.g., [10]). For each fairness notion {a mathematical formula}X∈{SD envy-freeness,weak SD envy-freeness,possible envy-freeness,SD proportionality,weak SD proportionality}, we define the following concepts:
      </paragraph>
      <list>
       <list-item>
        Maximum X: a discrete assignment p satisfies Maximum X if it maximizes the total number of agents for which the fairness condition according to X is satisfied.
       </list-item>
       <list-item>
        Maximal X: a discrete assignment p satisfies Maximal X if the fairness condition according to X cannot be satisfied for any more agents while maintaining the fairness condition for agents who are satisfied by p.
       </list-item>
      </list>
      <paragraph>
       The following lemmas are useful in relating the complexity of fairness concept X with Maximum X and Maximal X. The proofs are straightforward.
      </paragraph>
      <paragraph label="Corollary 3">
       If there exists a polynomial-time algorithm to compute a discrete assignment that is Maximum X then there exists a polynomial-time algorithm to compute a discrete assignment satisfying X if one exists.Simply compute the Maximum X and check whether the fairness condition is satisfied for each agent. If not, then the fairness condition cannot be satisfied for each agent and hence no X discrete assignment exists.  □Computing a maximum SD envy-free discrete assignment is NP-hard.
      </paragraph>
      <paragraph label="Corollary 4">
       If there exists a polynomial-time algorithm to check whether a discrete assignment satisfying X exists, then the problem of computing a Maximal X discrete assignment can also be solved in polynomial time.We describe the reduction. Initialize S, the set of agents for which the fairness condition can be met, to the empty set. Check whether there exists an agent {a mathematical formula}j∈N∖S that can be moved to S such that there still exists a discrete assignment that satisfies the fairness condition according to X for agents in S. If yes, then move j to S. Repeat the process until the set S cannot be grown. Hence S is the maximal set of agents that can be satisfied.  □A maximal SD proportional discrete assignment can be computed in polynomial time.
      </paragraph>
      <paragraph label="Corollary 5">
       A maximal weak SD proportional discrete assignment can be computed in polynomial time if n is a constant.
      </paragraph>
      <paragraph>
       Fig. 2 illustrates the polynomial-time reductions between computational problems for fairness concept {a mathematical formula}X∈{envy-freeness, proportionality, SD envy-freeness, weak SD envy-freeness, possible envy-freeness, weak SD proportionality, SD proportionality}.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Optimal proportionality
      </section-title>
      <paragraph>
       A possible criticism of maximal and maximum fairness is that the fairness constraint of each agent is strong enough so that it is not possible to satisfy it for each agent. Hence those agents that do not have their fairness constraints satisfied may not view the assignment as fair from their perspective. To counter this criticism, we weaken the fairness constraint in a uniform way which leads to attractive fairness concepts called optimal proportionality and optimal weak proportionality. The concepts are similar to egalitarian equivalence rule for continuous resource settings [43]. For continuous settings, an allocation satisfies egalitarian equivalence if each agent is indifferent between his allocation and the reference resource bundle. Since we consider only ordinal preferences, we exploit the SD relations to define suitable concepts. Moreover, since we consider discrete assignments, we relax the requirement of each agent's allocation being equivalent to the reference allocation.
      </paragraph>
      <paragraph>
       We say that an assignment satisfies {a mathematical formula}1/αproportionality if{a mathematical formula} We note that {a mathematical formula}1/n proportionality is equivalent to SD proportionality. An assignment satisfies optimal proportionality if{a mathematical formula} for the smallest possible α. We will refer to the smallest such α as {a mathematical formula}α⁎ and call {a mathematical formula}1/α⁎ as the optimal proportionality value.
      </paragraph>
      <paragraph>
       We point out that Theorem 6 can be generalized from {a mathematical formula}1/n proportionality to {a mathematical formula}1/α proportionality for any value of α:
      </paragraph>
      <paragraph label="Proof">
       It can be checked in polynomial time whether a discrete{a mathematical formula}1/αproportional assignment exists even if agents are allowed to express indifference between objects.The algorithm and proof is identical to that of the algorithm in the proof of Theorem 6. The only difference is that for each {a mathematical formula}i∈N and {a mathematical formula}ℓ∈{1,…,ki}, the lower bound of each vertex is set to {a mathematical formula}a(viℓ)=⌈∑j=1ℓ|Eij|α⌉−∑j=1ℓ−1a(vij) instead of {a mathematical formula}⌈∑j=1ℓ|Eij|n⌉−∑j=1ℓ−1a(vij).  □
      </paragraph>
      <paragraph>
       The algorithm in the proof of Theorem 16 can be used to check the existence of a {a mathematical formula}1/α proportional assignment for different values of α. However, among other cases, if {a mathematical formula}m&lt;n, then we know that a {a mathematical formula}1/α proportional assignment does not exist for any finite value of α. We first characterize the settings that admit a {a mathematical formula}1/α proportional assignment for some finite α.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}α⁎is finite iff there exists an assignment in which each agent gets one of his most preferred objects.In case each agent gets one of his most preferred objects, proportionality is satisfied for {a mathematical formula}α⁎=mn. If {a mathematical formula}α⁎ is finite, then each agent's proportionality constraint with respect to the first equivalence class is satisfied. Hence for some finite {a mathematical formula}α⁎,{a mathematical formula} Hence each i gets at least one of his most preferred objects.  □
      </paragraph>
      <paragraph>
       Since α is a positive real in the interval {a mathematical formula}(0,∞], it appears that even binary search cannot be used to find the optimal proportional assignment in polynomial time. Next, we show that interestingly we only need to check a polynomial number of values of α to find the optimal proportional assignment.
      </paragraph>
      <paragraph label="Proof">
       An optimal proportional assignment can be computed in polynomial time even if agents are allowed to express indifference between objects.If there exists no assignment in which each agent gets one of his most preferred objects, then {a mathematical formula}α⁎ is infinite. This means the first proportionality constraint of agents cannot be simultaneously satisfied for a finite {a mathematical formula}α⁎. In that case any arbitrary assignment satisfies optimality proportionality with {a mathematical formula}α⁎=∞. In case there exists an assignment in which each agent gets one of his most preferred objects, then {a mathematical formula}α⁎ is finite. We show how to compute such an {a mathematical formula}α⁎ as well as the assignment corresponding to it. An assignment p satisfies {a mathematical formula}1/α proportionality if for each {a mathematical formula}i∈N and each {a mathematical formula}k∈{1,…,ki},{a mathematical formula} Since {a mathematical formula}ki≤m, there are in total mn such constraints. Since the left hand side of each such constraint is an integer, the overall constraint is tight if{a mathematical formula}If the value of α is such that no proportionality constraint is tight then this means that α is not optimal. Therefore, we can restrict our attention to those values of α for which at least one of the constraints of the type in (4) is tight. When a constraint is tight, both sides of the constraint take one of the values from the set {a mathematical formula}{1,…,m}. No constraint can take value 0 because we know that {a mathematical formula}α⁎ is finite and that there exists an assignment in which each agent gets one of his most preferred objects. For the tight constraint{a mathematical formula} for some {a mathematical formula}ℓ∈{0,…,m−1}. This constraint is tight for one of the following values of α:{a mathematical formula}It follows that if we restrict α to those values for which at least one proportionality constraint is tight, then we just need to consider at most {a mathematical formula}nm2 values of α all of which are rationals. For each of these values, we check whether a {a mathematical formula}1/α proportional assignment exists or not. The smallest α for which a {a mathematical formula}1/α proportional assignment exists is the optimal {a mathematical formula}α=α⁎. The assignment is the optimal proportional assignment.  □
      </paragraph>
      <paragraph>
       We note that if an SD proportional assignment exists, then it is also an optimal proportional assignment.
      </paragraph>
      <paragraph label="Proof">
       SD proportionality implies optimal proportionality irrespective of whether the assignments are discrete or not.Assume that assignment p is SD proportional not an optimal proportional assignment. Then, we know that it is {a mathematical formula}1/n proportional. Assume for contradiction that p is {a mathematical formula}1/α proportional for {a mathematical formula}α&lt;n. But this means that for each {a mathematical formula}i∈N, the following constraint is satisfied.{a mathematical formula}Since {a mathematical formula}α&lt;n, it follows that {a mathematical formula}|O|α&gt;|O|n. But if each agent gets more than {a mathematical formula}|O|n objects, then the number of objects is more than {a mathematical formula}|O| which is a contradiction. □
      </paragraph>
      <paragraph>
       We show that even if an SD proportional assignment does not exist, an optimal proportional assignment suggests a desirable allocation of objects.
      </paragraph>
      <paragraph label="Example 8">
       Assume that the preferences of the agents are as follows.{a mathematical formula}{a mathematical formula} Since m is not a multiple of n, an SD proportional assignment does not exist. Now consider the assignment p that gives two objects to one agent and one object to the other. It is an optimal proportional assignment where the optimal proportionality value is 1/3.
      </paragraph>
      <paragraph>
       Optimal proportionality seems to be a useful fairness concept for ordinal settings. It guarantees the existence of an assignment that satisfies a fairness notion along the lines of proportionality. If each agent cannot get a most preferred object, then the optimal proportionality value reached is {a mathematical formula}1/∞=0. If the optimal proportionality value is 0, then one can modify the preference profile by gradually merging the first few equivalence classes of the agents. If {a mathematical formula}m&gt;n, then after merging enough equivalence classes of the agents, one can ensure that the optimal proportional value for the modified profile is finite. An optimal proportional assignment for the modified preference profile stills seems to constitute a desirable and fair assignment for the original preference profile. We note that in contrast to the ordinal setting, when agents have cardinal utilities, even checking whether there exists a proportional assignment is NP-complete [15], [39].
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Optimal weak proportionality
      </section-title>
      <paragraph>
       Just like the concept of SD proportionality can be used to define optimal proportionality, weak SD proportionality can be used to define optimal weak proportionality. We say that an assignment satisfies {a mathematical formula}1/βweak proportionality if{a mathematical formula} We note that {a mathematical formula}1/n weak proportionality is equivalent to weak SD proportionality. An assignment satisfies optimal weak proportionality if{a mathematical formula} for the infimum of the set {a mathematical formula}{β|∃a1/βweak proportional assignment}. We will refer to the infimum as {a mathematical formula}β⁎ and call {a mathematical formula}1/β⁎ as the optimal weak proportionality value.
      </paragraph>
      <paragraph>
       We point out that Theorem 8 can be generalized from {a mathematical formula}1/n proportionality to {a mathematical formula}1/β proportionality for any value of β:
      </paragraph>
      <paragraph label="Proof">
       For a constant number of agents, it can be checked in polynomial time whether a{a mathematical formula}1/βweak proportional discrete assignment exists even if agents are allowed to express indifference between objects.The algorithm and proof is identical to that of the algorithm in the proof of Theorem 8. The only difference in the algorithm is in the lower bounds of vertices.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}a(viℓ)=⌊|⋃j=1ℓEij|β⌋+1 and {a mathematical formula}b(viℓ)=∞ for each {a mathematical formula}i∈N and {a mathematical formula}ℓ∈{1,…,ki};
       </list-item>
       <list-item label="•">
        {a mathematical formula}a(Bij)=b(Bij)=|Eij|β for each {a mathematical formula}Bij;
       </list-item>
       <list-item label="•">
        {a mathematical formula}a(o)=b(o)=1 for each {a mathematical formula}o∈O. □
       </list-item>
      </list>
      <paragraph>
       The algorithm in the proof of Theorem 19 can be used to check the existence of a {a mathematical formula}1/β weak proportional assignment for different values of β. However, among other cases, if {a mathematical formula}m&lt;n, then we know that a {a mathematical formula}1/β weak proportional assignment does not exist for any finite value of β.
      </paragraph>
      <paragraph label="Lemma 7">
       For any assignment setting,{a mathematical formula}β⁎≥1.
      </paragraph>
      <paragraph label="Proof">
       Assume for contradiction that {a mathematical formula}β⁎&lt;1. This means that there exists a discrete assignment p such that for each agent {a mathematical formula}i∈N, either {a mathematical formula}p(i)∼iSD(1/β⁎,…,1/β⁎) or {a mathematical formula}|p(i)∩⋃j=1kEij|&gt;|⋃j=1kEi|β⁎ for some k. Note that the former condition is not feasible because it means that {a mathematical formula}p(i)≻iRSO. For the latter condition, since {a mathematical formula}β⁎&lt;1, therefore {a mathematical formula}|p(i)∩⋃j=1kEij|&gt;|⋃j=1kEij|. But this is a contradiction.  □
      </paragraph>
      <paragraph>
       Next, we characterize those assignment settings for which {a mathematical formula}β⁎ is finite.
      </paragraph>
      <paragraph label="Lemma 8">
       {a mathematical formula}β⁎is finite if and only if{a mathematical formula}m≥n.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}β⁎ is finite, then at least one of each agent's weak {a mathematical formula}β⁎ proportionality constraint is satisfied. This implies that each agent gets at least one object which means that {a mathematical formula}m≥n.Assume that {a mathematical formula}m≥n. Hence there exists an assignment in which each agent gets one object. In the worst case, some agent {a mathematical formula}i∈N gets only one object that is also his least preferred. Even then {a mathematical formula}p(i)≻iSD(1/β,…,1/β) if {a mathematical formula}1/β&lt;1/m. Hence p is weak {a mathematical formula}1/β weak proportional for any finite {a mathematical formula}β&gt;m.  □
      </paragraph>
      <paragraph label="Theorem 20">
       Next, we show that if the number of agents is constant, an optimal weak proportional assignment can be computed in polynomial time. If the number of agents is constant, a discrete optimal weak proportional assignment can be computed in polynomial time even if agents are allowed to express indifference between objects.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}m&lt;n, then by Lemma 8, {a mathematical formula}β⁎ is infinite and at least one agent cannot get an object. In that case, any assignment satisfies {a mathematical formula}1/∞ weak proportionality. If {a mathematical formula}m≥n, then by Lemma 8, {a mathematical formula}β⁎ is finite, we show how to compute such a {a mathematical formula}β⁎ as well as the assignment corresponding to it. Assume that {a mathematical formula}β⁎ is such that there exists at least one {a mathematical formula}i∈N such that {a mathematical formula}p(i)∼iSD(1/β⁎,…,1/β⁎). In this case, for each {a mathematical formula}j∈{1,…,ki}i gets {a mathematical formula}|Eij|β⁎ objects from {a mathematical formula}p(i)∩Eij. Since {a mathematical formula}|Eij|∈{1,…,m} and {a mathematical formula}|p(i)∩Eij|∈{1,…,m}, {a mathematical formula}β⁎ takes one of at most {a mathematical formula}O(m2) values from set {a mathematical formula}{a/b:a,b∈{1,…,m},a&gt;b}.Now let us assume that {a mathematical formula}β⁎ is such that there exists no {a mathematical formula}i∈N such that {a mathematical formula}p(i)∼iSD(1/β⁎,…,1/β⁎). In that case for each agent {a mathematical formula}i∈N, an assignment p satisfies {a mathematical formula}1/β proportionality if for each {a mathematical formula}i∈N and some {a mathematical formula}k∈{1,…,ki},{a mathematical formula}For an arbitrarily small rational {a mathematical formula}ϵ&gt;0, this constraint is equivalent to{a mathematical formula}Since {a mathematical formula}ki≤m, there are in total mn such constraints. Since the left hand side of each such constraint is an integer, the overall constraint is tight if{a mathematical formula}If the value of {a mathematical formula}β−ϵ is such that no proportionality constraint is tight then this means that {a mathematical formula}β−ϵ is not optimal. Therefore, we can restrict our attention to those values of {a mathematical formula}β−ϵ for which at least one of the constraints of the type in (6) is tight. When a constraint is tight, both sides of the constraint take one of the values from the set {a mathematical formula}{1,…,m}. For the tight constraint,{a mathematical formula} for some {a mathematical formula}ℓ∈{0,…,m−1}. This constraint is tight for one of the following values of {a mathematical formula}β−ϵ:{a mathematical formula}It follows that if we restrict {a mathematical formula}β−ϵ to those values for which at least one proportionality constraint is tight, then we just need to consider at most {a mathematical formula}nm2 values of {a mathematical formula}β−ϵ all of which are rationals. We can informally consider these values as the values of β because {a mathematical formula}β−ϵ is a tiny perturbation of β. For each of the values, we check whether a {a mathematical formula}1/β proportional assignment exists or not. Similarly, for each of the values from the set {a mathematical formula}β∈{a/b:a,b∈{1,…,m},a&gt;b}, we check whether a β weak proportional assignment exists or not. The smallest β for which a {a mathematical formula}1/β assignment exists is {a mathematical formula}β⁎.  □
      </paragraph>
      <paragraph>
       It remains open whether the theorem above can be generalized to the case where the number of agents is not constant. We note that whereas an SD proportional assignment is an optimal proportional assignment (Theorem 18), a weak SD proportional assignment may not be an optimal weak proportional assignment.
      </paragraph>
      <paragraph label="Example 9">
       Assume that the preferences of the agents are as follows.{a mathematical formula}{a mathematical formula} Note that the discrete assignment p that gives {a mathematical formula}{o2,o3} to agent 1 and the other objects to agent 2 is weak SD proportional. In fact it is not only 1/2 weak proportional but {a mathematical formula}(3/5−ϵ) weak proportional where {a mathematical formula}ϵ&gt;0 is arbitrarily small. It is not {a mathematical formula}1/β weak proportional for {a mathematical formula}1/β&lt;3/5.We now consider a discrete assignment q, that gives {a mathematical formula}{o1} to agent 1 and the other objects to agent 2. It is easily seen that q is {a mathematical formula}(1−ϵ) weak proportional where {a mathematical formula}ϵ&gt;0 is arbitrarily small. Since the weak SD proportional assignment p is not {a mathematical formula}1/β weak proportional for {a mathematical formula}1/β&lt;3/5 but there exists another discrete assignment q that is {a mathematical formula}(1−ϵ) weak proportional, it shows that a weak SD proportional discrete assignment may not be an optimal weak proportional assignment.
      </paragraph>
      <paragraph>
       Next, we provide further justification for optimal weak proportionality. Optimal weak proportionality is equivalent to an established fairness concept called maximin defined for a restricted domain. When {a mathematical formula}n=m and preferences of agents are strict, Brams and King [21] defined an assignment satisfying maximin if it maximizes the minimum rank of items that any player receives. We show that for {a mathematical formula}n=m and strict preferences, maximin is equivalent to optimal weak proportional.
      </paragraph>
      <paragraph label="Proof">
       For{a mathematical formula}n=mand strict preferences, maximin is equivalent to optimal weak proportional.Assume that each agent gets an object that is at least his k-th ranked object. Then the assignment satisfies {a mathematical formula}1/(k−ϵ) weak proportionality for some arbitrarily small {a mathematical formula}ϵ&gt;0. We now assume that an assignment satisfies {a mathematical formula}1/(k−ϵ) weak proportionality for some arbitrarily small {a mathematical formula}ϵ&gt;0. In that case we know that each agent gets an object that is k-th or higher ranked.  □
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>