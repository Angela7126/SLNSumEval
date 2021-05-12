<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Strategy-proof school choice mechanisms with minimum quotas and initial endowments.
   </title>
   <abstract>
    We consider a school choice program where minimum quotas are imposed for each school, i.e., a school must be assigned at least a certain number of students to operate. We require that the obtained matching must respect the initial endowments, i.e., each student must be assigned to a school that is at least as good as her initial endowment school. Although minimum quotas are relevant in school choice programs and strategy-proofness is important to many policymakers, few existing mechanisms simultaneously achieve both. One difficulty is that no strategy-proof mechanism exists that is both efficient and fair under the presence of minimum quotas. Furthermore, existing mechanisms require that all students consider all schools acceptable to obtain a feasible matching that respects minimum quotas. This assumption is unrealistic in a school choice program. We consider the environment where a student considers her initial endowment school acceptable and the initial endowments satisfy all the minimum quotas. We develop two strategy-proof mechanisms. One mechanism, which we call the Top Trading Cycles among Representatives with Supplementary Seats (TTCR-SS), is based on the Top Trading Cycles (TTC) mechanism and is significantly extended to handle the supplementary seats of schools while respecting minimum quotas. TTCR-SS is Pareto efficient. The other mechanism, which we call Priority List-based Deferred Acceptance with Minimum Quotas (PLDA-MQ), is based on the Deferred Acceptance (DA) mechanism. PLDA-MQ is fair, satisfies a concept called Priority List-based (PL-) stability, and obtains the student-optimal matching within all PL-stable matchings. Our simulation results show that our new mechanisms are significantly better than simple extensions of the existing mechanisms.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Traditionally, a student who plans to attend a public school is assigned to one based on where she lives. School choice programs are implemented to give students and their parents opportunities to choose which public schools to attend. In such programs, students submit their preferences over schools to a centralized matching mechanism, which assigns students to schools. A seminal work by Abdulkadiroğlu and Sönmez [3] introduced the idea of using a mechanism design approach to study this issue by formalizing it as a problem of allocating indivisible objects with multiple supplies (seats in schools) to agents (students). This problem is referred to as the school choice problem.
     </paragraph>
     <paragraph>
      In this paper, we consider a school choice problem with two requirements. First, we assume that a minimum quota constraint is imposed on each school. A school is required to enroll a certain number of students. This is a reasonable assumption since each school needs a minimum number of students to operate. Second, we assume that each student has a default school that she would have attended without a school choice program, which we refer to as her initial endowment. We further assume that initial endowments satisfy all minimum quotas. The objective of this paper is to design school choice mechanisms so that each student who participates in the matching process will be able to attend a school that is at least as good as her initial endowment school. On the other hand, strategy-proofness, i.e., no student ever has any incentive to misreport her preference regardless of other students' reports, is critical to many policymakers. We focus on strategy-proof mechanisms in this paper.
     </paragraph>
     <paragraph>
      Several desirable properties of a matching mechanism have been proposed in the literature. Two widely discussed properties are Pareto efficiency and stability. Pareto efficiency is a welfare notion that rules out incidents that can improve agents' well-being without making others worse off. Stability rules out justified envy, which is an incident that violates priority in a school.{sup:1} However, [3] showed that a matching mechanism cannot be both stable and Pareto efficient in the setting of school choice problem, even when there is no distributional constraint. As a result, a policymaker needs to choose between Pareto efficiency and stability.
     </paragraph>
     <paragraph>
      In this paper, we develop two strategy-proof mechanisms: the Top Trading Cycles among Representatives with Supplementary Seats (TTCR-SS) and the Priority List-based Deferred Acceptance with Minimum Quotas (PLDA-MQ). The first achieves Pareto efficiency,{sup:2} and the second achieves PL-stability, which is a version of stability we consider in this paper.
     </paragraph>
     <paragraph>
      Before we introduce our mechanisms, we first introduce two simple mechanisms that can handle minimum quotas. The first is based on the Top Trading Cycles (TTC) mechanism of [44]. Since in our setting, each student is endowed with a seat in a default school, a simple way to improve students' welfare is to allow them to trade their seats in schools. Moreover, since we assume that the initial matching satisfies maximum and minimum quotas, the new matching that resulted from trading also satisfies these distributional constraints. This is because trading happens only when a group of students wants to exchange seats, and therefore, the numbers of students who are matched to a school are the same both in the initial and new matching. We call this simple mechanism the Top Trading Cycles among Representatives (TTCR). Note that we design a list over the students, the Master List (ML), in TTCR to prioritize their rights to form a trading cycle.{sup:3} Note that a student will exchange her seat in her default school with another student only when she can obtain a seat in a school that she prefers to her default school. Thus, in the new matching, each student is weakly better off.
     </paragraph>
     <paragraph>
      The second simple mechanism is the Artificial Cap Deferred Acceptance (ACDA), which is identical as the Deferred Acceptance (DA) mechanism [16] except for two adjustments. First, we created an artificial maximum quota for each school that is equal to the number of students who are matched to this school in the initial matching. The mechanism uses artificial maximum quotas instead of true maximum quotas to create matchings. Second, we adjust the priorities of the students in schools so that a student has higher priority in her default school than a student whose default school is different. These two adjustments guarantee that the new matchings created by DA satisfy the distributional constraints and that every student is weakly better off in the new matching.
     </paragraph>
     <paragraph>
      ACDA is a popular mechanism to handle minimum quotas in practice,{sup:4} and its properties have been analyzed in several studies, for example, [15] and [23]. The real-world applications of ACDA include the hospital-doctor matching in Japan and the cadet-branch matching in the United States ([15] and [23]).
     </paragraph>
     <paragraph>
      We find that both TTCR and ACDA have severe shortcomings emanating from the fact that the number of students who are assigned to a school is weakly less than its capacity in both mechanisms. The mechanisms developed in this paper, TTCR-SS and PLDA-MQ, are designed to properly exploit these extra seats. TTCR-SS is designed to achieve efficiency, and PLDA-MQ is designed to improve students' welfare while achieving a certain degree of fairness.
     </paragraph>
     <paragraph>
      In developing both of these mechanisms, the presence of minimum quotas plays a crucial role. If there are no minimum quotas and if only the initial endowments are addressed, we can use a simple extension of the TTC-based mechanism described in [2] to achieve Pareto efficiency. Also, to achieve stability, we can use the standard DA mechanism with the modified priorities so that each school respects its initial endowment students.
     </paragraph>
     <paragraph>
      The design of TTCR-SS is based on TTC. We introduce dummy students who are used to facilitate the formation of trading cycles in the mechanism.{sup:5} We carefully design the dummy students' preferences to satisfy the distributional constraints and show that TTCR-SS is strategy-proof and Pareto efficient. Note that the notion of Pareto efficiency is stronger than nonwastefulness.
     </paragraph>
     <paragraph>
      The design of PLDA-MQ is based on DA. Although the design objective is to create a mechanism that is fair and nonwasteful, such fair and nonwasteful matching might not exist in our setting. This impossibility result precludes the existence of a fair and nonwasteful mechanism. We find that this impossibility result comes from the standard definitions of fairness and nonwastefulness. In fact, these definitions do not prioritize students' rights to leave their default schools for other schools when leaving might cause the constraints of minimum quotas to fail to be satisfied. To accommodate this situation, we use the notions of PL-fairness and PL-nonwastefulness.{sup:6} These two notions are based on an ordering over all pairs of schools and students, called the Priority List (PL). With PL, if two students want to move to two (possibly different) schools but only one can, PL determines which student can move. We only make two assumptions about PL. First, PL respects students' priorities in each school. Second, it respects their initial endowments. This gives the policymaker great flexibility in designing PL. In particular, it can be designed to prioritize which schools have the right to receive students from other schools if moving all of the students might violate distributional constraints. In the setting of cadet-branch matching, policymakers might prioritize one branch over another for receiving more personnel, while all branches still satisfy the minimum quotas constraints. A matching is PL-stable if it is PL-fair and PL-nonwasteful. We show that ACDA does not create PL-stable matching.{sup:7}
     </paragraph>
     <paragraph>
      We show that PLDA-MQ is strategy-proof and PL-stable. Moreover, it obtains the student-optimal matching within all PL-stable matchings. We use the techniques developed in [27] to develop PLDA-MQ. Although they provide a useful toolkit, developing a concrete mechanism that works for new types of constraints remains challenging; we need to appropriately design a choice function of schools so that their framework is applicable for achieving the required design goals. PLDA-MQ is an instance of the Generalized Deferred Acceptance (GDA) mechanism [20]{sup:8} whose skeleton resembles DA. Thus, PLDA-MQ can be easily adopted to policymakers, schools, and students. This is a major advantage compared to applying a completely new or unfamiliar mechanism.
     </paragraph>
     <paragraph>
      Our mechanisms can be used in a setting where students' preferences are changed after they receive their initial assignments, and there is a minimum quota constraint in each school. In many universities in Japan, undergraduate engineering students must be assigned to a laboratory to conduct projects. However, students sometimes have difficulty choosing appropriate laboratories since their familiarity with them is limited. Our mechanisms can be used to reallocate students after they experience a certain trial period. In the NYC high school choice program, the allocation of students is determined by a centralized matching mechanism in December, and students are allowed to participate in a reapplication process in April [35]. He empirically showed that some students change their preferences after they receive their first assignments. Such reapplication processes are a potential application of our mechanisms.
     </paragraph>
     <paragraph>
      Very few studies have addressed strategy-proof mechanisms that can handle minimum quotas. One example is [15], who developed mechanisms based on DA. However, there is a severe limitation to apply their mechanisms to our settings. They require that every student consider all schools acceptable. This assumption is not realistic in our setting.
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. We show a more detailed literature review in the rest of this section and introduce a formal model of our problem setting in Section 2. In Section 3, we describe TTCR and show its deficiency and then introduce our first main mechanism, TTCR-SS, and describe its properties. In Section 4 we describe ACDA and show its deficiency and then introduce our second main mechanism, PLDA-MQ, and show its properties. We evaluate our mechanisms by computer simulation in Section 5. In Section 6 we discuss some relevant issues and provide a conclusion in Section 7. All long proofs are found in the Appendix.
     </paragraph>
     <section label="1.1">
      <section-title>
       Related literature
      </section-title>
      <paragraph>
       In the context of school choice, distributional constraints are often imposed on different types of students, e.g., gender and socioeconomic status [7], [11], [19], [26], [29], [45]. The crucial difference between our setting and those works that consider minimum quotas is that the minimum quotas in our paper are hard constraints that must be satisfied by any matching, while these works treat minimum quotas as “soft” constraints that may or may not be satisfied.
      </paragraph>
      <paragraph>
       [11] showed that if the constraints are interpreted as hard constraints, no mechanism satisfies fairness, constrained nonwastefulness,{sup:9} and strategy-proofness. Due to this impossibility result, [15] developed two strategy-proof mechanisms. However, their mechanisms cannot simultaneously satisfy fairness and nonwastefulness. One is called the Extended Seat Deferred Acceptance (ESDA) mechanism, which is fair but wasteful. The other is called the Multi-Stage Deferred Acceptance (MSDA) mechanism, which is nonwasteful but not fair. Based on their work, [17] developed a strategy-proof mechanism that can handle hierarchical minimum quotas. We cannot use these mechanisms in our setting since they do not respect initial endowments.
      </paragraph>
      <paragraph>
       The computer science community has also been studying the problem of matching with minimum quotas [6], [14], [22]. These works examined the complexity of verifying the existence of types of stable matchings, but they did not provide explicit mechanisms or consider incentive issues. Our approach to this problem resembles those used in [15] and [17], and we study strategy-proof mechanisms that achieve desirable outcomes in polynomial time.
      </paragraph>
      <paragraph>
       There is other closely related literature that starts from [44] who introduced the housing market problem, which addresses the problem of allocating objects to agents when they are initially owned by agents who have strict preferences over them. In their paper, they introduced TTC due to David Gale and showed that the core is nonempty. [42] showed that, when the preferences of agents are strict, the core is a singleton. For the incentive property, [41] showed that TTC is strategy-proof. [31] argued that a trading mechanism is individual rational, Pareto efficient, and strategy-proof if and only if it is TTC. Later, TTC was generalized to the Hierarchical Exchange mechanism [37] and to the Trading Cycles mechanism [40]. [39] generalized [40] to an environment where each object can have more than one copy{sup:10}. [2], who considered a setting that resembles ours, modified TTC to a setting where some houses are initially owned by tenants, while others are not. The differences between [2] and our work are that we consider a setting where multiple copies of objects (school seats) exist and minimum quotas are imposed.
      </paragraph>
      <paragraph>
       School choice programs have also been identified as an important application domain of TTC [3]. This work formulated a school choice problem, in which school seats are allocated to students. A school can have multiple seats, and each school can have an idiosyncratic priority among students. They also introduced a modified version of the original TTC that is specific to a school choice problem and show that the mechanism is Pareto efficient and strategy-proof. Since then in the setting of school choice problems, TTC has drawn independent research interest and many research directions. One direction is to design the priority structure of students for a given mechanism [18], [25]. Another direction is using an axiomatic approach to characterize it [1], [10], [32], [33].
      </paragraph>
      <paragraph>
       There are other related works on matching theory in AI literature. For example, [28] studied the house allocation problem, and [4], [43], and [24] studied the housing market problem. [21] investigated a dynamic matching problem, and [8] and [38] studied matching problems with couples.
      </paragraph>
      <paragraph>
       We conclude this section by comparing the properties of the mechanisms that respect minimum quotas. Table 1 summarizes the comparison (“NW” stands for nonwastefulness and “PE” stands for Pareto efficiency). Here, for ESDA and MSDA, we assume all students consider all schools acceptable. Without this assumption, they cannot satisfy minimum quotas.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Model
     </section-title>
     <paragraph>
      A market is a tuple {a mathematical formula}(S,C,X,qC,pC,ω,≻S,≻C).
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}S={s1,…,sn} is a finite set of students.
      </list-item>
      <list-item label="•">
       {a mathematical formula}C={c1,…,cm} is a finite set of schools.
      </list-item>
      <list-item label="•">
       {a mathematical formula}X=S×C is a finite set of contracts. Contract {a mathematical formula}x=(s,c)∈X represents that student s is assigned to school c. For any {a mathematical formula}X′⊆X, let {a mathematical formula}Xs′ denote {a mathematical formula}{(s,c)∈X′|c∈C}, i.e., the sets of contracts related to student s who is involved in {a mathematical formula}X′, and let {a mathematical formula}Xc′ denote {a mathematical formula}{(s,c)∈X′|s∈S}, i.e., the sets of contracts related to school c involved in {a mathematical formula}X′.
      </list-item>
      <list-item label="•">
       {a mathematical formula}qC=(qc)c∈C is a vector of the schools' maximum quotas.
      </list-item>
      <list-item label="•">
       {a mathematical formula}pC=(pc)c∈C is a vector of the schools' minimum quotas.
      </list-item>
      <list-item label="•">
       ω: {a mathematical formula}S→C is an initial endowment function. {a mathematical formula}ω(s) returns {a mathematical formula}c∈C, which is s's initial endowment. When {a mathematical formula}ω(s)=c, we say school c is student s's initial endowment school, and student s is school c's initial endowment student. Let {a mathematical formula}X⁎ denote {a mathematical formula}⋃s∈S{(s,ω(s))}, i.e., {a mathematical formula}X⁎ is the set of contracts, where each element is a contract between a student and her initial endowment school. We assume {a mathematical formula}∑c∈Cpc≤n≤∑c∈Cqc holds. Also, we assume {a mathematical formula}X⁎ satisfies minimum and maximum quotas, i.e., for all {a mathematical formula}c∈C, {a mathematical formula}pc≤|Xc⁎|≤qc holds.
      </list-item>
      <list-item label="•">
       {a mathematical formula}≻S=(≻s)s∈S is a profile of the students' preferences. For each student s, {a mathematical formula}≻s represents the preference of s over {a mathematical formula}Xs. We assume {a mathematical formula}≻s is strict for each s. We say {a mathematical formula}(s,c) is acceptable for s if {a mathematical formula}(s,c)≻s(s,ω(s)) or {a mathematical formula}c=ω(s) holds. We sometimes use such notation as {a mathematical formula}c≻sc′ instead of {a mathematical formula}(s,c)≻s(s,c′) and write {a mathematical formula}≻−s=(≻s′)s′∈S∖{s}.
      </list-item>
      <list-item label="•">
       {a mathematical formula}≻C=(≻c)c∈C is a profile of the schools' priorities. For each school c, {a mathematical formula}≻c represents the priorities of c over {a mathematical formula}Xc. We assume {a mathematical formula}≻c is strict for each c. We sometimes write {a mathematical formula}s≻cs′ instead of {a mathematical formula}(s,c)≻c(s′,c).
      </list-item>
     </list>
     <paragraph>
      With a slight abuse of notation, for two sets of contracts, {a mathematical formula}X′ and {a mathematical formula}X″, we denote {a mathematical formula}Xs′≻sXs″ if either (i) {a mathematical formula}Xs′={x′}, {a mathematical formula}Xs″={x″}, and {a mathematical formula}x′≻sx″ for some {a mathematical formula}x′,x″∈Xs that are acceptable for s, or (ii) {a mathematical formula}Xs′={x′} for some {a mathematical formula}x′∈Xs that is acceptable for s and {a mathematical formula}Xs″=∅. We denote {a mathematical formula}Xs′⪰sXs″ if either {a mathematical formula}Xs′≻sXs″ or {a mathematical formula}Xs′=Xs″. Also, for {a mathematical formula}Xs′⊆Xs, we say {a mathematical formula}Xs′ is acceptable for s if {a mathematical formula}Xs′={x} and x is acceptable for s.{sup:11}
     </paragraph>
     <paragraph>
      Next, we define the concept of a feasible outcome.
     </paragraph>
     <paragraph label="Definition 1">
      feasibility{a mathematical formula}X′⊆X is student-feasible if {a mathematical formula}∀s∈S, {a mathematical formula}Xs′ is acceptable for s. {a mathematical formula}X′ is school-feasible if {a mathematical formula}∀c∈C,pc≤|Xc′|≤qc holds. {a mathematical formula}X′ is feasible if it is both student- and school-feasible.
     </paragraph>
     <paragraph>
      We call a feasible set of contracts a matching. Note that by definition, any matching is individually rational, i.e., every student is matched with a school that is at least as good as her initial endowment school. Also note that since {a mathematical formula}X⁎ is school-feasible, it is a matching.
     </paragraph>
     <paragraph>
      A mechanism is function φ that takes a profile of students' preferences {a mathematical formula}≻S as input and returns set of contracts {a mathematical formula}φ(≻S)⊆X. We write {a mathematical formula}φs(≻S), which is the set of contracts assigned to student s given submitted preference profile {a mathematical formula}≻S. A mechanism is called feasible if it always returns a matching.
     </paragraph>
     <paragraph>
      In the following, we describe several properties that are widely discussed in the literature. One important property regards students' incentives when they submit preferences.
     </paragraph>
     <paragraph label="Definition 2">
      strategy-proofnessWe say mechanism φ is strategy-proof if {a mathematical formula}φs(≻s,≻−s)⪰sφs(≻s′,≻−s) holds ∀ s, {a mathematical formula}≻s, {a mathematical formula}≻s′, and {a mathematical formula}≻−s.
     </paragraph>
     <paragraph>
      In words, a mechanism is strategy-proof if no student ever has any incentive to misreport her preference, regardless of the reports of other students. Another important concept concerns students' welfare.
     </paragraph>
     <paragraph label="Definition 3">
      Pareto efficiencyMatching {a mathematical formula}X′Pareto dominates another matching {a mathematical formula}X″ if {a mathematical formula}∀s∈S,Xs′⪰sXs″ and {a mathematical formula}∃s∈S,Xs′≻sXs″ hold, i.e., compared with {a mathematical formula}X″, {a mathematical formula}X′ makes all students weakly better off and at least one student strictly better off. A matching is Pareto efficient if no other matching Pareto dominates it. A mechanism is Pareto efficient if it always selects a Pareto efficient matching.
     </paragraph>
     <paragraph>
      In other words, a policymaker cannot make a student better off without making another student worse off in a Pareto efficient matching. Pareto efficiency may not be the only property with which a policymaker is concerned. One might think that the priorities of students should be respected. This concept is formalized by the following definition.
     </paragraph>
     <paragraph label="Definition 4">
      fairnessWe say student s has justified envy toward {a mathematical formula}s′≠s in matching {a mathematical formula}X′, where {a mathematical formula}(s,c)∈X′, {a mathematical formula}(s′,c′)∈X′∖X⁎, and {a mathematical formula}(s,c′)∈X∖X′, if {a mathematical formula}(s,c′)≻s(s,c) and {a mathematical formula}(s,c′)≻c′(s′,c′) hold. Matching {a mathematical formula}X′ is fair if no student has justified envy. A mechanism is fair if it always gives a fair matching.
     </paragraph>
     <paragraph>
      In words, student s, who is allocated to c, has justified envy toward student {a mathematical formula}s′ who is allocated to {a mathematical formula}c′ if s prefers {a mathematical formula}c′ over c, s has a higher priority than {a mathematical formula}s′ in {a mathematical formula}c′, and {a mathematical formula}c′ is not the initial endowment of {a mathematical formula}s′. Finally, we introduce a weaker welfare notion than Pareto efficiency. Basically, it says that empty seats should not be wasted.
     </paragraph>
     <paragraph label="Definition 5">
      nonwastefulnessWe say student s claims an empty seat of {a mathematical formula}c′ in matching {a mathematical formula}X′, where {a mathematical formula}(s,c)∈X′ and {a mathematical formula}(s,c′)∈X∖X′, if {a mathematical formula}(s,c′)≻s(s,c), {a mathematical formula}|Xc′′|&lt;qc′, and {a mathematical formula}|Xc′|&gt;pc hold. Matching {a mathematical formula}X′ is nonwasteful if no student claims an empty seat. A mechanism is nonwasteful if it always gives a nonwasteful matching.
     </paragraph>
     <paragraph>
      The above definition says that student s, who is allocated to c, claims an empty seat of {a mathematical formula}c′ if s prefers {a mathematical formula}c′ over c and the set of contracts obtained by moving s from c to {a mathematical formula}c′ is school-feasible. If {a mathematical formula}X′ is Pareto efficient, then {a mathematical formula}X′ is nonwasteful, but not vice versa.
     </paragraph>
     <paragraph>
      We say a matching is stable if it is fair and nonwasteful. A mechanism is stable if it always gives a stable matching.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Top trading cycles among representatives with supplementary seats
     </section-title>
     <paragraph>
      In this section, we study TTC-based mechanisms. We begin by describing a straightforward extension of TTC and show its deficiency. Then we introduce our first main mechanism and describe its properties.
     </paragraph>
     <section label="3.1">
      <section-title>
       Top trading cycles among representatives
      </section-title>
      <paragraph>
       Let us introduce the Top Trading Cycles among Representatives (TTCR). Since a student is indifferent between multiple seats within the same school, we cannot directly apply the standard TTC mechanism. TTCR, which exploits ML to treat such indifferences in a simple manner, is a special case of Algorithm III in [25].
      </paragraph>
      <paragraph>
       Before we formally introduce TTCR, let us introduce some notions that will be used in its description. Directed graph G is a pair {a mathematical formula}(V,E) where V is a set of vertices and {a mathematical formula}E⊆{(i,j)|i,j∈V} is a collection of ordered pairs of vertices in V. Ordered pair {a mathematical formula}(i,j), where {a mathematical formula}i,j∈V, is called a directed edge from i to j. A sequence of vertices {a mathematical formula}(i1,…,ik), {a mathematical formula}k≥2, is a directed path from vertex {a mathematical formula}i1 to vertex {a mathematical formula}ik if {a mathematical formula}(ih,ih+1)∈E for {a mathematical formula}h=1,…,k−1. If {a mathematical formula}i1=ik, then we call this directed path a cycle. In particular, {a mathematical formula}(i,i), where {a mathematical formula}(i,i)∈E, is called a self-loop cycle.
      </paragraph>
      <paragraph>
       {a mathematical formula}≻ML ranks all the students in the market. One example is using the scores of nation-wide exams. ML can be exogenously given and therefore it might be completely independent from the schools' priorities. Without loss of generality, in the rest of the paper we assume {a mathematical formula}≻ML such that {a mathematical formula}s1≻MLs2≻ML⋯≻MLsn. Note that, given a market, any ordering on S can be ML. In Subsection 6.2, we discuss how the choice of such a list affects the outcome of the introduced mechanism.
      </paragraph>
      <paragraph>
       This mechanism repeats several rounds. At Round k, {a mathematical formula}Yk−1 represents the set of remaining initial endowment contracts and {a mathematical formula}Zk−1 represents the set of contracts that has already been finalized. TTCR is defined in Mechanism 1.
      </paragraph>
      <paragraph>
       Intuitively, we can assume in TTCR that each school chooses one representative student from its initial endowment students based on ML. Then within these representative students, the standard TTC mechanism is applied. By choosing one representative for each school, we can ignore the fact that a student is indifferent among multiple seats within the same school. Since a student considers her initial endowment school acceptable, at least one cycle always exists. TTCR can be considered one instance of Algorithm III [25]. In Algorithm III, each school has its own priority ordering among students. Student s, who has the highest priority in school c's ordering, obtains all the seats of c. Then the standard TTC mechanism is applied among the students who own seats. When a student is involved in a cycle and obtains her desired seat, she returns the remaining seats to each school. Then the mechanism repeats the same procedure for the remaining students. If we assume the number of seats available for a school equals the number of its initial endowment students, and school c gives the highest priority to student s according to ML within her initial endowment students, Algorithm III becomes identical to TTCR.
      </paragraph>
      <paragraph label="Example 1">
       The obtained matching of TTCR satisfies all the minimum and maximum quotas, since the number of students matched to a school are identical in the initial matching and in the resulting matching. However, this mechanism is not Pareto efficient, as shown in the following example: Assume {a mathematical formula}S={s1,s2,s3,s4,s5,s6,s7},C={c1,c2,c3}, where {a mathematical formula}ω(s1)=ω(s2)=ω(s3)=c1, {a mathematical formula}ω(s4)=ω(s5)=ω(s6)=c2, and {a mathematical formula}ω(s7)=c3. {a mathematical formula}qc=3 for all {a mathematical formula}c∈C. {a mathematical formula}pc1=2 and {a mathematical formula}pc2=pc3=0.The preferences of students are given as follows:{a mathematical formula}First, {a mathematical formula}Y0 is determined: {a mathematical formula}{(s1,c1),(s2,c1),(s3,c1),(s4,c2),(s5,c2),(s6,c2),(s7,c3)}.At Step 1 of Round 1, since {a mathematical formula}Yc0≠∅ for all {a mathematical formula}c∈C, the mechanism selects each {a mathematical formula}(s,c) where s has the highest priority according to ML within the students in {a mathematical formula}Yc0 for all {a mathematical formula}c∈C and adds {a mathematical formula}(s1,c1), {a mathematical formula}(s4,c2), and {a mathematical formula}(s7,c3) to {a mathematical formula}V1. Then each selected student points to her most preferred school according to {a mathematical formula}≻s within the schools in {a mathematical formula}V1; {a mathematical formula}s1, {a mathematical formula}s4, and {a mathematical formula}s7 point to {a mathematical formula}c2, {a mathematical formula}c3, and {a mathematical formula}c1, respectively. Therefore, {a mathematical formula}G1 is determined as follows:{a mathematical formula} There exists one cycle: {a mathematical formula}((s1,c1),(s4,c2),(s7,c3),(s1,c1)). At Step 2, {a mathematical formula}C1 is {a mathematical formula}{(s1,c1),(s4,c2),(s7,c3)}. At Step 3, {a mathematical formula}(s1,c2), {a mathematical formula}(s4,c3), and {a mathematical formula}(s7,c1) are added to {a mathematical formula}Z0, and the contracts in {a mathematical formula}C1 are removed from {a mathematical formula}Y0. {a mathematical formula}Z1 and {a mathematical formula}Y1 are determined as follows:{a mathematical formula} At Step 4, go to Round 2 because {a mathematical formula}Y1≠∅.At Step 1 of Round 2, since {a mathematical formula}Yc31=∅, there is no representative student from {a mathematical formula}c3. The mechanism selects {a mathematical formula}(s2,c1) and {a mathematical formula}(s5,c2) according to ML and adds them to {a mathematical formula}V2. Then each selected student points to her most preferred school according to {a mathematical formula}≻s within the schools in {a mathematical formula}V2. Therefore, {a mathematical formula}G2 is determined as follows:{a mathematical formula} There are two self-loop cycles. At Step 2, {a mathematical formula}C2 is {a mathematical formula}{(s2,c1),(s5,c2)}. Therefore, at Step 3, {a mathematical formula}Z2 and {a mathematical formula}Y2 are given as follows:{a mathematical formula} At Step 4, go to Round 3 because {a mathematical formula}Y2≠∅.At Step 1 of Round 3, {a mathematical formula}G3 is determined as follows:{a mathematical formula} There are two self-loop cycles. At Step 2, {a mathematical formula}C2 is {a mathematical formula}{(s3,c1),(s6,c2)}. Therefore, at Step 3, {a mathematical formula}Z3 and {a mathematical formula}Y3 are given as follows:{a mathematical formula} At Step 4, return {a mathematical formula}Z3 because {a mathematical formula}Y3=∅.In the end, obtained matching {a mathematical formula}Z3 is:{a mathematical formula} Consider another matching {a mathematical formula}Z′:{a mathematical formula} We find that {a mathematical formula}Zs′⪰sZs3 for all {a mathematical formula}s∈S and {a mathematical formula}Zs′≻sZs3 for {a mathematical formula}s∈{s2,s5} hold. Therefore, {a mathematical formula}Z3 is not Pareto efficient. Also, {a mathematical formula}|Zc3|=|Xc⁎| for all {a mathematical formula}c∈C.
      </paragraph>
      <paragraph>
       TTCR's limitation is that it cannot allocate supplementary seats, as shown in Example 1. However, if we allocate supplementary seats too generously, constraints on minimum quotas can be violated. In the following, we develop a new Pareto efficient mechanism, which is called the Top Trading Cycles among Representatives with Supplementary Seats (TTCR-SS), that utilizes the notion of dummy students to control the supplementary seats at each school. In TTCR-SS, if a school has already “consumed” its initial endowment students and has supplementary seats, it selects a dummy student as its representative.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Top trading cycles among representatives with supplementary seats
      </section-title>
      <paragraph>
       TTCR-SS repeats several rounds like TTCR. At Round k, {a mathematical formula}Yk−1 represents the set of remaining initial endowment contracts and {a mathematical formula}Zk−1 represents the set of contracts that has already been finalized. We divide each school c at Round k into the following four categories: minimum:{a mathematical formula}|Yck−1|&gt;0 and {a mathematical formula}|Zck−1|+|Yck−1|=pc, i.e., c has the remaining initial endowment contracts and the total number of students in the finalized contracts and the initial endowment contracts equals the minimum quota. Thus, a student in its initial endowment contracts cannot move to another school without violating the constraint on minimum quotas.decrementable:{a mathematical formula}|Yck−1|&gt;0 and {a mathematical formula}|Zck−1|+|Yck−1|&gt;pc, i.e., c has the remaining initial endowment contracts and a student in its initial endowment contracts can move to another school.maximum:{a mathematical formula}|Yck−1|=0 and {a mathematical formula}|Zck−1|=qc, i.e., c has no remaining initial endowment contracts and it has already accepted students up to its maximum quota.incrementable:{a mathematical formula}|Yck−1|=0 and {a mathematical formula}|Zck−1|&lt;qc, i.e., c has no remaining initial endowment contract and can accept another student without violating its maximum quota constraint. Let {a mathematical formula}Cmink, {a mathematical formula}Cdeck, {a mathematical formula}Cmaxk, and {a mathematical formula}Cinck represent the sets of schools in each of the above categories at Round k.
      </paragraph>
      <paragraph>
       TTCR-SS resembles TTCR, but if school c has exhausted its initial endowment students (i.e., {a mathematical formula}Yck−1=∅ holds) while it has a supplementary seat (i.e., {a mathematical formula}|Zck−1|&lt;qc), it is incrementable and can send dummy student {a mathematical formula}sd as its representative. If a dummy student points to {a mathematical formula}(s,c) and obtains c's seat, in reality, the number of assigned students in c is decremented by one. To ensure that the obtained matching respects the minimum quotas, we carefully design the “preference” of each dummy student. If {a mathematical formula}|Yck−1|+|Zck−1|=pc holds for school c, i.e., if c is minimum, then c cannot afford to “accept” a dummy student. Thus each dummy student points to the contract, in which the student has the highest priority among students whose initial endowment schools are decrementable. Note that all dummy students point to the same contract. Thus, at most one cycle exists that includes a dummy student. TTCR-SS is defined in Mechanism 2.
      </paragraph>
      <paragraph>
       Fig. 1 shows the possible transitions of the school categories. Typically, school c is initially decrementable. If {a mathematical formula}|Xc⁎|=pc, c is initially minimum. If {a mathematical formula}|Xc⁎|=0, c is initially incrementable. As long as all the schools are decrementable or minimum, no dummy student is introduced. Thus, for each contract in a cycle, the related school is either decrementable or minimum. Then at some Round k, {a mathematical formula}Yck eventually becomes ∅ for some school c. c typically becomes incrementable, and a dummy student is introduced. After a dummy student is introduced, for each contract in a cycle, the related school can be incrementable, decrementable, or minimum, and a student whose initial endowment school is decrementable can obtain a seat of an incrementable school from a dummy student. A decrementable school can become minimum, and an incrementable school can become maximum. As a special case (represented by a dotted line in Fig. 1), if for school c, the number of initial endowment students exactly equals {a mathematical formula}qc, and no student whose initial endowment is c gives a seat to a dummy student, then c becomes maximum when {a mathematical formula}Yck becomes ∅. As another special case (represented by a dotted line in Fig. 1), if {a mathematical formula}pc=qc holds for school c, then c is initially minimum and directly moves to maximum when {a mathematical formula}Yck becomes ∅. The assignment of maximum schools becomes fixed. When no decrementable school exists, no dummy student is introduced. Thus, for each contract in a cycle, the related school is minimum. Once this happens, there will be no decrementable school in the later rounds. Thus, no dummy student will be introduced at any later round.
      </paragraph>
      <paragraph label="Example 2">
       Let us describe how TTCR-SS works. Consider the same instance as in Example 1. {a mathematical formula}Y0 is the same as Example 1.The mechanism behaves exactly the same as the previous example until a dummy student is introduced. The following is the result of Round 1:{a mathematical formula}At Step 1 of Round 2, {a mathematical formula}c1 and {a mathematical formula}c2 are decrementable, and {a mathematical formula}c3 is incrementable. Schools {a mathematical formula}c1 and {a mathematical formula}c2 select their representative students {a mathematical formula}s2 and {a mathematical formula}s5, and {a mathematical formula}(s2,c1) and {a mathematical formula}(s5,c2) are added to {a mathematical formula}V2. Since there are decrementable schools, {a mathematical formula}c3 sends a dummy student and {a mathematical formula}(sd,c3) is added to {a mathematical formula}V2. Then each selected student points to her most preferred school according to {a mathematical formula}≻s among the schools in {a mathematical formula}V2; {a mathematical formula}s2 and {a mathematical formula}s5 indicate {a mathematical formula}c3. On the other hand, dummy student {a mathematical formula}sd points to the school whose initial endowment student has the highest priority according to ML within {a mathematical formula}Cdec2; {a mathematical formula}sd of {a mathematical formula}c3 points to {a mathematical formula}c1. Therefore, {a mathematical formula}G2 is given as follows:{a mathematical formula} There is one cycle {a mathematical formula}((s2,c1),(sd,c3),(s2,c1)). At Step 2, {a mathematical formula}C2 is {a mathematical formula}{(s2,c1),(sd,c3)}. Therefore, at Step 3, {a mathematical formula}Z2 and {a mathematical formula}Y2 are given as follows:{a mathematical formula}At Step 1 of Round 3, {a mathematical formula}c1 is minimum, {a mathematical formula}c2 is decrementable, and {a mathematical formula}c3 is incrementable. Thus the mechanism adds {a mathematical formula}(s3,c1), {a mathematical formula}(s5,c2), and {a mathematical formula}(sd,c3) to {a mathematical formula}V3. Then {a mathematical formula}s3 and {a mathematical formula}s5 point to {a mathematical formula}c3. Here, although {a mathematical formula}s3 has higher priority than {a mathematical formula}s5 according to ML, since {a mathematical formula}s3's initial endowment school {a mathematical formula}c1 is minimum, {a mathematical formula}sd points to {a mathematical formula}c2 instead of {a mathematical formula}c1. Therefore, {a mathematical formula}G3 is given as follows:{a mathematical formula} There is one cycle {a mathematical formula}((s5,c2),(sd,c3),(s5,c2)). At Step 2, {a mathematical formula}C3 is {a mathematical formula}{(s5,c2),(sd,c3)}. {a mathematical formula}Z3 and {a mathematical formula}Y3 are given as follows:{a mathematical formula}At Step 1 of Round 4, {a mathematical formula}c1 is minimum, {a mathematical formula}c2 is decrementable, and {a mathematical formula}c3 is maximum. Then the mechanism adds {a mathematical formula}(s3,c1) and {a mathematical formula}(s6,c2) to {a mathematical formula}V4. Since {a mathematical formula}c3 is maximum, it cannot send a representative. Thus no dummy student is added. Therefore, {a mathematical formula}G4 is given as follows:{a mathematical formula} There are two self-loop cycles. At Step 2, {a mathematical formula}C4 is {a mathematical formula}{(s3,c1),(s6,c2)}. {a mathematical formula}Z4 and {a mathematical formula}Y4 are determined as follows:{a mathematical formula} At Step 4, since {a mathematical formula}Y4=∅, the mechanism returns {a mathematical formula}Z4.The obtained matching is identical to {a mathematical formula}Z′ in Example 1.
      </paragraph>
      <paragraph label="Proof">
       Next, we describe the theoretical properties of TTCR-SS. TTCR-SS is feasible, strategy-proof, and Pareto efficient.See Appendix A.1.  □
      </paragraph>
      <paragraph>
       The fact that TTCR-SS is Pareto efficient, while TTCR is not, does not imply that all students weakly prefer the matching of TTCR-SS over that of TTCR. This is because there can be multiple Pareto efficient matchings. Let us show a simple example. Assume two students, {a mathematical formula}s1 and {a mathematical formula}s2, and three schools, {a mathematical formula}c1,c2, and {a mathematical formula}c3. The minimum quota of {a mathematical formula}c1 is 1, and the minimum quotas of {a mathematical formula}c2 and {a mathematical formula}c3 are 0. The maximum quotas of all the schools are 1. The initial endowment schools of {a mathematical formula}s1 and {a mathematical formula}s2 are {a mathematical formula}c1 and {a mathematical formula}c2. The preference of {a mathematical formula}s1 is {a mathematical formula}c2≻s1c1, and the preference of {a mathematical formula}s2 is {a mathematical formula}c3≻s2c1≻s2c2. In TTCR-SS, {a mathematical formula}sd of {a mathematical formula}c3 and {a mathematical formula}s2 swap seats, and {a mathematical formula}s1 cannot move to {a mathematical formula}c2. Thus the obtained matching is {a mathematical formula}{(s1,c1),(s2,c3)}. On the other hand, in TTCR, no dummy student is introduced and {a mathematical formula}s1 and {a mathematical formula}s2 swap seats. The obtained matching is {a mathematical formula}{(s1,c2),(s2,c1)}. Here {a mathematical formula}s1 prefers the TTCR matching. In the next section, we experimentally show that the overwhelming majority of students prefer the matching obtained by TTCR-SS.
      </paragraph>
      <paragraph label="Proof">
       Finally, we show that TTCR-SS can be done in polynomial time in {a mathematical formula}|S| and {a mathematical formula}|C|. The time complexity of TTCR-SS is{a mathematical formula}O(|S|⋅|C|).At each round, there exists at least one cycle that contains at least one student {a mathematical formula}s∈S, and the assignment of s is fixed. Thus the number of rounds required for TTCR-SS is at most {a mathematical formula}|S|. Also, for each round, there are at most {a mathematical formula}|C| contracts, and finding the cycles can be done in {a mathematical formula}O(|C|). Therefore, the time complexity of TTCR-SS is {a mathematical formula}O(|S|⋅|C|).  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Priority list-based deferred acceptance with minimum quotas
     </section-title>
     <paragraph>
      In this section, we study DA-based mechanisms. We first describe a simple extension of DA and show its deficiency. Then we introduce our second main mechanism and show its properties.
     </paragraph>
     <section label="4.1">
      <section-title>
       Artificial Cap DA
      </section-title>
      <paragraph>
       In this subsection, we introduce the Artificial Cap Deferred Acceptance mechanism (ACDA), which is a simple extension of DA that can handle minimum and maximum quotas. The idea of ACDA is used in the Japan Residency Matching Program. It works by reducing the maximum quotas of hospitals in such urban areas as Tokyo so that more doctors are assigned to rural hospitals [23].
      </paragraph>
      <paragraph>
       For each school c, original maximum quota {a mathematical formula}qc is decreased to {a mathematical formula}|Xc⁎|, i.e., the number of its initial endowment students. Also, original school priority {a mathematical formula}≻c is modified so that each of its initial endowment contracts has a higher priority than any contract in {a mathematical formula}Xc∖Xc⁎. Then the mechanism performs the standard DA procedure described as follows, which repeats the following rounds.{a mathematical formula} In the following, we show that ACDA is not a stable mechanism.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       PL-stability
      </section-title>
      <paragraph label="Example 3">
       We show that the standard notion of stability is not appropriate in our setting because a stable outcome might not exist. This impossibility result is shown in the following example.{sup:12}Assume {a mathematical formula}S={s1,s2},C={c1,c2,c3}, where {a mathematical formula}ω(s1)=ω(s2)=c1. {a mathematical formula}qc=2 for all {a mathematical formula}c∈C. {a mathematical formula}pc1=1, {a mathematical formula}pc2=pc3=0. The priorities of schools are given as follows:{a mathematical formula} We assume the preferences of students are given as follows:{a mathematical formula}Here {a mathematical formula}c1 is the least popular school for both {a mathematical formula}s1 and {a mathematical formula}s2, but at least one student must be assigned to it since {a mathematical formula}pc1=1. Assume {a mathematical formula}s1 is allocated to {a mathematical formula}c1. Then {a mathematical formula}s2 must be allocated to her most preferred school {a mathematical formula}c3, or otherwise {a mathematical formula}s2 claims an empty seat of {a mathematical formula}c3. However, then {a mathematical formula}s1 has justified envy toward {a mathematical formula}s2 since {a mathematical formula}s1≻c3s2. Similarly, assume {a mathematical formula}s2 is allocated to {a mathematical formula}c1. Then {a mathematical formula}s1 must be allocated to her most preferred school {a mathematical formula}c2, or otherwise {a mathematical formula}s1 claims an empty seat of {a mathematical formula}c2. However, then {a mathematical formula}s2 has justified envy toward {a mathematical formula}s1 since {a mathematical formula}s2≻c2s1.
      </paragraph>
      <paragraph>
       This example also shows that there exists no stable mechanism. Therefore ACDA is not a stable mechanism. We use an alternative concept of stability, Priority List-based (PL-) stability. PL-stability consists of PL-fairness and PL-nonwastefulness.{sup:13} PL-stability relies on priority list, {a mathematical formula}≻PL, that ranks all of the contracts. Such a list breaks ties between students or contracts when necessary.
      </paragraph>
      <paragraph>
       We only make two assumptions about PL. First, we assume {a mathematical formula}≻PL respects {a mathematical formula}≻C, i.e., for any {a mathematical formula}(s,c),(s′,c)∈X∖X⁎, {a mathematical formula}(s,c)≻PL(s′,c) holds if {a mathematical formula}(s,c)≻c(s′,c) holds. Second, we assume {a mathematical formula}≻PL respects the initial endowments,{sup:14} i.e., for each {a mathematical formula}x∈X⁎ and {a mathematical formula}x′∈X∖X⁎, it holds that {a mathematical formula}x≻PLx′.
      </paragraph>
      <paragraph>
       The way we construct PL gives much flexibility to policymakers, since we only make two assumptions for it. One feature of PL is that in addition to the fact that it respects students' priorities in schools, it also prioritizes the rights of schools for receiving students. One application of such prioritization is in cadet-branch matching where policymakers want to prioritize the rights of individual branches for accepting personnel.
      </paragraph>
      <paragraph>
       One simple way of creating {a mathematical formula}≻PL is based on the ranking of students and the tie-breaking order among schools. Let {a mathematical formula}rank(c,s) denote the ranking of student s for school c based on {a mathematical formula}≻c, i.e., if s is ranked highest for c among students except c's initial endowment students, {a mathematical formula}rank(c,s)=1, and if she is ranked second, {a mathematical formula}rank(c,s)=2, and so on. If s is c's initial endowment student, we assume {a mathematical formula}rank(c,s)=0. Also, assume the tie-breaking order among schools is defined as {a mathematical formula}c1,c2,…,cm. Then {a mathematical formula}(s,ci)≻PL(s′,cj) holds when {a mathematical formula}rank(ci,s)&lt;rank(cj,s′), or {a mathematical formula}rank(ci,s)=rank(cj,s′) and {a mathematical formula}i&lt;j hold.
      </paragraph>
      <paragraph>
       In the following we formally define PL-fairness and PL-nonwastefulness.
      </paragraph>
      <paragraph label="Definition 6">
       PL-fairnessWe say student s has justified envy toward {a mathematical formula}s′≠s in matching {a mathematical formula}X′ based on PL, where {a mathematical formula}(s,c),(s′,c′)∈X′ and {a mathematical formula}(s,c″)∈X∖X′, if {a mathematical formula}(s,c″)≻s(s,c), {a mathematical formula}|Xc″′|&lt;qc″, {a mathematical formula}|Xc′′|&gt;pc′, and {a mathematical formula}(s,c″)≻PL(s′,c′) hold. Matching {a mathematical formula}X′ is PL-fair if no student has justified envy or justified envy based on PL. A mechanism is PL-fair if it always gives a PL-fair matching.
      </paragraph>
      <paragraph>
       In words, if student s is assigned to c even though she hopes to be assigned to {a mathematical formula}c″, which can accept one more student, while another student {a mathematical formula}s′ is assigned to {a mathematical formula}c′ even though it has already satisfied its minimum quota, then s has justified envy toward {a mathematical formula}s′ if the tie-breaking rule supports this, i.e., {a mathematical formula}(s,c″)≻PL(s′,c′) holds. This condition is stronger than what is required by the standard fairness, since a student may justifiably envy another student whose matched school is not exactly where she wants to go.
      </paragraph>
      <paragraph>
       Intuitively, PL-fairness requires that if we need to reject a contract to satisfy the minimum quota of a school, and when there exist several candidate contracts to reject, the mechanism should fairly reject one based on PL, i.e., the contract with the lowest priority according to PL.
      </paragraph>
      <paragraph label="Definition 7">
       PL-nonwastefulnessStudent s claims an empty seat of {a mathematical formula}c′ in matching {a mathematical formula}X′ based on PL, where {a mathematical formula}(s,c)∈X′ and {a mathematical formula}(s,c′)∈X∖X′, if {a mathematical formula}(s,c′)≻s(s,c), {a mathematical formula}|Xc′′|&lt;qc′, {a mathematical formula}|Xc′|&gt;pc and {a mathematical formula}(s,c′)≻PL(s,c) hold. Matching {a mathematical formula}X′ is PL-nonwasteful if no student claims an empty seat based on PL. A mechanism is PL-nonwasteful if it always gives a PL-nonwasteful matching.
      </paragraph>
      <paragraph>
       This definition weakens standard nonwastefulness. Here, the claim of student s who is assigned to c to obtain an empty seat of {a mathematical formula}c′ is legitimate only if the tie-breaking rule supports this, i.e., {a mathematical formula}(s,c′)≻PL(s,c).
      </paragraph>
      <paragraph>
       Recall that a matching is PL-stable if it is PL-fair and PL-nonwasteful. We say a mechanism is PL-stable if it always gives a PL-stable matching. Note that a stable matching might not be PL-stable and vice versa.
      </paragraph>
      <paragraph>
       Consider the situation of Example 3, where all the schools prefer {a mathematical formula}s2 over {a mathematical formula}s1, and {a mathematical formula}≻PL is given as follows (which respects the schools' priorities):{a mathematical formula} Since {a mathematical formula}pc1=1, at least one student must be assigned to {a mathematical formula}c1 even though {a mathematical formula}c1 is the least popular school for both students. A mechanism needs to decide which contract should be rejected, e.g., among {a mathematical formula}{(s1,c3),(s2,c2)}. Here since both schools {a mathematical formula}c2 and {a mathematical formula}c3 unanimously prefer {a mathematical formula}s2 over {a mathematical formula}s1, it is natural to assume that {a mathematical formula}(s1,c3) is rejected. Indeed, PL-fairness requires the mechanism to reject {a mathematical formula}(s1,c3), which has the lowest priority according to PL (which respects the schools' priorities).
      </paragraph>
      <paragraph>
       Note that from these definitions, the initial endowment matching {a mathematical formula}X⁎ is PL-stable. Since a student cannot have justified envy toward another student allocated to her initial endowment, {a mathematical formula}X⁎ is fair. Also, for any {a mathematical formula}x∈X⁎ and {a mathematical formula}x′∈X∖X⁎, {a mathematical formula}x≻PLx′ holds. Then a student cannot have justified envy based on PL or claim an empty seat based on PL. Thus {a mathematical formula}X⁎ is PL-stable. Therefore, there always exists at least one PL-stable matching.
      </paragraph>
      <paragraph label="Example 4">
       In the next example we show that ACDA does not satisfy PL-stability. Assume {a mathematical formula}S={s1,s2,s3,s4},C={c1,c2,c3}, where {a mathematical formula}ω(s1)=c1, {a mathematical formula}ω(s2)=ω(s3)=c2, {a mathematical formula}ω(s4)=c3. {a mathematical formula}qc=4 for all {a mathematical formula}c∈C. {a mathematical formula}pc1=pc2=0, {a mathematical formula}pc3=1. The priorities of the schools and the preferences of students are given as follows:{a mathematical formula}{a mathematical formula} We assume {a mathematical formula}≻PL is given as follows:{a mathematical formula}Now, assume {a mathematical formula}q1,q2, and {a mathematical formula}q3 are artificially reduced to 1, 2, and 1, respectively.In Round 1, each student applies to her most preferred school, i.e., {a mathematical formula}s2, {a mathematical formula}s3, {a mathematical formula}s4 apply to {a mathematical formula}c1, and {a mathematical formula}s1 applies to {a mathematical formula}c2. Since three students are applying to {a mathematical formula}c1, which is larger than the (artificially decreased) maximum quota {a mathematical formula}qc1=1, {a mathematical formula}c1 deferred-accepts {a mathematical formula}s2, who has the highest priority according to {a mathematical formula}≻c1, and rejects {a mathematical formula}s3 and {a mathematical formula}s4. {a mathematical formula}c2 deferred-accepts {a mathematical formula}s1.In Round 2, {a mathematical formula}s3 and {a mathematical formula}s4, who were rejected in the previous step, apply to {a mathematical formula}c2. Thus, three students in total are applying to {a mathematical formula}c2, which is larger than the (artificially decreased) maximum quota {a mathematical formula}qc2=2. Then {a mathematical formula}c2 deferred-accepts {a mathematical formula}s3 and {a mathematical formula}s4 and rejects {a mathematical formula}s1.In Round 3, {a mathematical formula}s1 applies to {a mathematical formula}c3. Then all students are deferred-accepted and the mechanism terminates.In the end, the obtained matching becomes the following:{a mathematical formula} In this matching, {a mathematical formula}s4 claims an empty seat of {a mathematical formula}c1 based on PL since moving {a mathematical formula}s4 from {a mathematical formula}c2 to {a mathematical formula}c1 is possible and {a mathematical formula}(s4,c1)≻PL(s4,c2) holds. If {a mathematical formula}≻PL is defined such that {a mathematical formula}(s1,c2)≻PL(s2,c1) holds, then {a mathematical formula}s1 has justified envy toward {a mathematical formula}s2 based on PL. Thus, ACDA is neither PL-fair nor PL-nonwasteful.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Priority-list based DA with minimum quotas
      </section-title>
      <paragraph>
       In this subsection, we introduce the Priority-List based Deferred Acceptance mechanism with Minimum Quotas (PLDA-MQ) and describe its properties. We utilize a general framework for developing a strategy-proof mechanism with various distributional constraints recently developed by [27]. Their framework exploits choice functions for students ({a mathematical formula}ChS) and schools ({a mathematical formula}ChC), defined as follows:
      </paragraph>
      <paragraph label="Definition 8">
       students' choice functionFor each student s, her choice function {a mathematical formula}Chs is defined as follows. Given {a mathematical formula}X′⊆X, let {a mathematical formula}Ys denote that {a mathematical formula}{x∈Xs′|x is acceptable for s}. {a mathematical formula}Chs(X′) returns {a mathematical formula}{x}, s.t. {a mathematical formula}x∈Ys and x is the most preferred contract in {a mathematical formula}Ys for s. If {a mathematical formula}Ys=∅, then {a mathematical formula}Chs(X′) returns ∅. Then the choice function of all students {a mathematical formula}ChS is defined as {a mathematical formula}ChS(X′):=⋃s∈SChs(X′).
      </paragraph>
      <paragraph label="Definition 9">
       schools' choice functionGiven {a mathematical formula}X′⊆X, the choice function of the schools returns set of contracts {a mathematical formula}ChC(X′), defined as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Here {a mathematical formula}f:2X→R∪{−∞} is an evaluation function that aggregates the schools' priorities and distributional constraints. We sometime say f represents the priorities of schools. We assume f is unique-selecting, i.e., for all {a mathematical formula}X′⊆X, there exists a unique {a mathematical formula}X″⊆X′ that maximizes {a mathematical formula}f(X″).
      </paragraph>
      <paragraph>
       Based on these choice functions, GDA is defined as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Here Re represents a set of contracts proposed by the students and rejected by the schools. Students are not allowed to propose a contract in Re, which is initially empty. They can choose their most preferred contracts and propose them to the schools. This set is {a mathematical formula}X′. Then schools choose the most preferred subset {a mathematical formula}X″ from {a mathematical formula}X′. If no contract is rejected, the mechanism terminates. Otherwise, the rejected contracts are added to Re, and the mechanism repeats the same procedure.
      </paragraph>
      <paragraph>
       Next we show how to appropriately define f. To exploit previous results by [27], we decompose f into two parts, {a mathematical formula}fˆ and {a mathematical formula}f˜, such that f is expressed as {a mathematical formula}f=fˆ+f˜. Roughly speaking, given a market, {a mathematical formula}fˆ is responsible for the distributional constraints and {a mathematical formula}f˜ takes care of the priorities of the schools.
      </paragraph>
      <paragraph label="Definition 10">
       hard constraintGiven {a mathematical formula}X′⊆X, {a mathematical formula}fˆ(X′) is defined as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively, if {a mathematical formula}fˆ(X′)=−∞ holds, no {a mathematical formula}X″⊇X′ exists such that {a mathematical formula}X″ is feasible. This is because, if count {a mathematical formula}∑c∈Cmax⁡(|Xc′|,pc) exceeds n, there are not enough remaining students (who are not involved in {a mathematical formula}X′ or cannot be accepted in {a mathematical formula}X′) to fill the seats of schools whose minimum quotas are not satisfied under {a mathematical formula}X′. Let the effective domain of {a mathematical formula}fˆ (denoted as {a mathematical formula}domfˆ) be defined as {a mathematical formula}domfˆ:={X′⊆X|fˆ(X′)≠−∞}.
      </paragraph>
      <paragraph>
       Defining {a mathematical formula}f˜ is straightforward. Let {a mathematical formula}v:X→(0,∞) with {a mathematical formula}v(∅)=0 be a function such that {a mathematical formula}x≠x′ implies {a mathematical formula}v(x)≠v(x′). We can assume that {a mathematical formula}v(x) represents the value of contract x and that v respects PL; we define {a mathematical formula}v(⋅) based on {a mathematical formula}≻PL such that {a mathematical formula}x≻PLx′ implies {a mathematical formula}v(x)&gt;v(x′). Then given a market, PL, and v that respects PL, {a mathematical formula}f˜ is defined such that {a mathematical formula}f˜(X′)=∑x∈X′v(x) holds for {a mathematical formula}X′⊆X.
      </paragraph>
      <paragraph>
       With these definitions of {a mathematical formula}fˆ and {a mathematical formula}f˜, we call GDA, where {a mathematical formula}f(X′) is defined by {a mathematical formula}fˆ(X′)+f˜(X′), the Priority List-based Deferred Acceptance mechanism with Minimum Quotas (PLDA-MQ).
      </paragraph>
      <paragraph label="Example 5">
       Let us show the execution of PLDA-MQ. We consider the same instance as Example 4. First, each student chooses her most preferred acceptable contract. Thus, {a mathematical formula}X′={(s1,c2), {a mathematical formula}(s2,c1), {a mathematical formula}(s3,c1), {a mathematical formula}(s4,c1)}. Here {a mathematical formula}fˆ(X′)=−∞ since {a mathematical formula}∑c∈Cmax⁡(|Xc′|,pc)=3+1+1=5&gt;4. Then the schools choose {a mathematical formula}X″={(s1,c2),(s2,c1),(s4,c1)} and {a mathematical formula}X′∖X″={(s3,c1)} is rejected, since {a mathematical formula}v((s3,c1)) has the lowest value, i.e., the lowest priority according to {a mathematical formula}≻PL, within {a mathematical formula}X′.Next {a mathematical formula}s3 chooses her second preferred contract {a mathematical formula}(s3,c2), while other students choose the same schools as before. {a mathematical formula}X′={(s1,c2),(s2,c1),(s3,c2),(s4,c1)}. {a mathematical formula}fˆ(X′)=−∞ since {a mathematical formula}∑c∈Cmax⁡(|Xc′|,pc)=2+2+1=5&gt;4. Then {a mathematical formula}(s1,c2) is rejected since it has the lowest priority according to {a mathematical formula}≻PL within {a mathematical formula}X′.Finally, {a mathematical formula}s1 chooses her second preferred contract {a mathematical formula}(s1,c3). Thus {a mathematical formula}X′={(s1,c3), {a mathematical formula}(s2,c1), {a mathematical formula}(s3,c2), {a mathematical formula}(s4,c1)}. {a mathematical formula}fˆ(X′)=0 since {a mathematical formula}∑c∈Cmax⁡(|Xc′|,pc)=2+1+1=4. Since no contract is rejected, the mechanism terminates.In the end, the obtained matching becomes the following:{a mathematical formula} This matching is PL-fair and PL-nonwasteful.
      </paragraph>
      <paragraph>
       Consider the situation described in Example 3, where {a mathematical formula}≻PL is given as follows (which respects schools' priorities):{a mathematical formula} The matching obtained by PLDA-MQ is {a mathematical formula}{(s1,c1),(s2,c2)}. This is PL-stable; {a mathematical formula}s2 cannot claim an empty seat of {a mathematical formula}c3 based on PL since {a mathematical formula}(s2,c2)≻PL(s2,c3) holds.
      </paragraph>
      <paragraph>
       Now we describe the theoretical properties of PLDA-MQ. In general there are multiple PL-stable matchings, including the initial endowment matching {a mathematical formula}X⁎. We show that PLDA-MQ selects a particular stable matching. We say a matching is student-optimal if every student weakly prefers her matching to any other matching.
      </paragraph>
      <paragraph label="Definition 11">
       student optimalityFor set of matchings {a mathematical formula}X, {a mathematical formula}X′∈X is student-optimal within {a mathematical formula}X if {a mathematical formula}Xs′⪰sXs″ holds {a mathematical formula}∀X″∈X, {a mathematical formula}∀s∈S.
      </paragraph>
      <paragraph>
       It is possible that no student-optimal matching exists in {a mathematical formula}X. If a student-optimal matching does exist in {a mathematical formula}X, it must be unique.{sup:15} Also, if there exists a unique Pareto efficient matching, it is student-optimal within all matchings. The following theorem describes the properties of PLDA-MQ.
      </paragraph>
      <paragraph label="Theorem 3">
       PLDA-MQ is feasible, strategy-proof, and PL-stable. Moreover, it obtains the student-optimal matching within all the PL-stable matchings.
      </paragraph>
      <paragraph label="Proof">
       See Appendix A.2.  □
      </paragraph>
      <paragraph label="Proof">
       Let us briefly discuss the time complexity of PLDA-MQ with the following theorem. The time complexity of PLDA-MQ is{a mathematical formula}O(|X|3).It is clear that f can be calculated in {a mathematical formula}O(|X|), since both {a mathematical formula}fˆ and {a mathematical formula}f˜ can be calculated in it. Since the f used in PLDA-MQ is M{sup:♮}-concave and Condition 2 of Theorem 5, the time complexity of PLDA-MQ is {a mathematical formula}O(|X|3).  □
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Evaluation
     </section-title>
     <paragraph>
      In this section, we conduct quantitative evaluations by computer simulations. In the previous sections we theoretically showed that TTCR-SS is an efficient mechanism and that PLDA-MQ is a fair mechanism in our setting. What we are mainly concerned with here is TTCR-SS's fairness and PLDA-MQ's efficiency. As benchmarks we use TTCR and ACDA, two simple mechanisms described above. Both are feasible and strategy-proof in our setting. TTCR, which is based on TTC, is a special case of Algorithm III in [25]. ACDA is based on DA, and a modified version of it is used as a benchmark in [15] and [17], for example.
     </paragraph>
     <paragraph>
      We consider two markets, A and B, which have different sizes. Market A has {a mathematical formula}n=720 students and {a mathematical formula}m=36 schools. We assume the schools and the residences of the students are located in a {a mathematical formula}6×6 grid space, where the right-end school is connected to the left-end school in each row, and the lower-end school is connected to the upper-end school in each column, i.e., the grid space constitutes a torus.{sup:16} Market B has {a mathematical formula}n=1280 students and {a mathematical formula}m=64 schools, distributed in an {a mathematical formula}8×8 grid space constituting a torus.
     </paragraph>
     <paragraph>
      In both markets, we assume that the schools and students are distributed evenly in the grid space and that a student is initially endowed with the school at her location. Therefore, each location has one school and 20 initial endowment students. We set the minimum and maximum quotas of each school to 5 and 60 in both markets. Note that the artificial maximum quota of each school is set to 20, which is the number of initial endowment students of the school.
     </paragraph>
     <paragraph>
      Regarding student preferences over the schools, we assume a student considers a school unacceptable if it is located too far from her residence. More precisely, a student considers a school unacceptable if the Manhattan distance between her residence and the school exceeds 2 in Market A. In Market B, a student will not consider attending a school whose Manhattan distance exceeds 3 from her location. Each student considers at most 13 schools acceptable in Market A and at most 25 schools acceptable in Market B.
     </paragraph>
     <paragraph>
      We generate the student preferences over the schools as follows. We first draw one common vector v of the cardinal utilities from set {a mathematical formula}[0,1]m uniformly at random. We then draw private vector {a mathematical formula}us of the cardinal utilities of each student s from the same set, again uniformly at random. Next we construct the cardinal utilities over all m schools for student s as {a mathematical formula}αv+(1−α)us for {a mathematical formula}α∈[0,1]. Here the i-th element of this vector represents the cardinal utility for school {a mathematical formula}ci. A student's preference is then determined by converting her cardinal utilities into an ordinal preference relation over the following schools: (i) those located within the above distance from her location, and (ii) those whose cardinal utilities are weakly higher than that of her initial endowment school. Here parameter α reflects the similarity of the student preferences. The higher the value of α, the greater the difference in popularity among schools becomes. In this experiment, we varied α from 0.0 to 1.0 in increments of 0.1.
     </paragraph>
     <paragraph>
      Regarding the schools' priorities over students, we assume here that a school prioritizes students who live closer to it. Among students whose locations are equidistant from a school, we use one common vector u, drawn from set {a mathematical formula}[0,1]n uniformly at random, to break ties; if {a mathematical formula}si and {a mathematical formula}sj are equally distant from a school, then the school prioritizes student {a mathematical formula}si over {a mathematical formula}sj if {a mathematical formula}ui&gt;uj holds. An ML is generated by converting u into an ordering over students, i.e., for two students, {a mathematical formula}si and {a mathematical formula}sj, {a mathematical formula}si≻MLsj holds if {a mathematical formula}ui&gt;uj.
     </paragraph>
     <paragraph>
      For obtaining a PL, we use the simple method introduced in Subsection 4.2. We first fix a round-robin ordering among schools as {a mathematical formula}c1→c2→⋯→cm→c1→c2→⋯. Then at each of its turns according to this ordering, school c removes its most prioritized contract from {a mathematical formula}Xc and adds it to the bottom of the current list, starting from empty. Note that the priorities of the schools in our experimental setting guarantee that school c first adds contracts in {a mathematical formula}Xc⁎ to the list. We obtain a PL by repeating this procedure until all the contracts are added to the list.
     </paragraph>
     <paragraph>
      We created 100 problem instances for each parameter setting and compared the outcomes of four mechanisms (TTCR, TTCR-SS, ACDA, and PLDA-MQ) and a trivial mechanism that assigns each student to her initial endowment school, i.e., it always returns {a mathematical formula}X⁎. We refer to this mechanism as Initial in the figures. Fig. 2, Fig. 3, Fig. 4 concern the stability of the mechanisms, and Fig. 5, Fig. 6 show the results of the students' welfare.
     </paragraph>
     <paragraph>
      Fig. 2 shows the average ratios of the students with justified envy or justified envy based on PL. Since PLDA-MQ and the initial endowments are PL-fair, no student has such envy for any α. For the other three mechanisms, the ratio of students with envy increases as α increases, as a result of more conflicts in the student preferences. With TTCR-SS, however, these conflicts are somehow mitigated by exploiting the supplementary seats. We can see that for small α, TTCR-SS efficiently assigns supplementary seats so that no student has envy, and the slope in the figures is much gentler than those of TTCR and ACDA. In Market A, for example, when {a mathematical formula}α=0.6, fewer than 30% of the 720 students have envy in TTCR-SS, while at least 70% are envious under the simple extensions. When {a mathematical formula}α=1, since all the student preferences are basically the same, no trade occurs in TTCR and its outcome is {a mathematical formula}X⁎. The ACDA outcome becomes the initial endowments if {a mathematical formula}α=1 because, for any school, there is a round in the mechanism where the school receives applications from all of its initial endowment students. In Market B, the slopes shift upward, meaning conflicts of interest are more difficult to resolve. This is because in Market B, more students consider a school acceptable, and thus a student might have many more students to envy.
     </paragraph>
     <paragraph>
      Fig. 3, Fig. 4 show the student claims for empty seats. Fig. 3 shows the ratio of students who claimed empty seats based on PL.
     </paragraph>
     <paragraph>
      We showed in the previous sections that PLDA-MQ is a PL-stable mechanism and that the TTCR-SS outcome satisfies Pareto efficiency, which is a stronger notion than PL-nonwastefulness. Initial is by definition also PL-nonwasteful. Thus, no student claims an empty seat based on PL under these mechanisms, as shown in the figure. On the other hand, we observe an inverted U-shaped relationship between α and both the TTCR and ACDA ratios. In both mechanisms, if conflicts of interest among the students are very high, then more students are likely to be assigned to their initial endowment schools. Since PL respects the initial endowments, a student's claim is not supported by PL if she is matched to her initial endowment school. As α gets closer to 1, the number of claims based on PL decreases.
     </paragraph>
     <paragraph>
      Fig. 4 shows the average ratio of students who claimed empty seats in the sense of Definition 5. The difference between Fig. 3, Fig. 4 reveals the amount of claims supported by PL. Note that Initial gives the highest ratio for any α. Since all the mechanisms are individually rational, the worst outcome in terms of efficiency for students is {a mathematical formula}X⁎: the Initial outcome. On the other hand, no student claims an empty seat under TTCR-SS, since it is Pareto efficient. Among the remaining mechanisms, the PLDA-MQ ratio stays the lowest for almost all the cases.{sup:17} Although PLDA-MQ and its properties depend on PL, this figure shows that this mechanism outperforms the simple extensions with respect to the amount of conventional claims. For a large α, the PLDA-MQ ratio begins to decrease. A rationale is that, for a large α, popular schools begin to fill their maximum quotas, and no student can claim their seats any more, implying that the ratio declines.
     </paragraph>
     <paragraph>
      Regarding the efficiency of the mechanisms, Fig. 5, Fig. 6 compare them in terms of students' welfare. Fig. 5 plots the cumulative distribution functions (CDFs) of the average number of students matched with their kth or higher ranked schools under each mechanism when {a mathematical formula}α=0.6. The ordering of the mechanisms in terms of their performance is consistent with the previous figures; TTCR-SS outperforms the other mechanisms in terms of students' welfare, since it is Pareto efficient, and PLDA-MQ, the runner-up, outperforms TTCR and ACDA. Therefore, the developed mechanisms in this paper obtain better matchings than the simple extensions of existing mechanisms in terms of both fairness and efficiency. Fig. 6 compares the outcomes for different α with respect to the Borda scores of the students. If a student is assigned to her kth-choice school, her score is {a mathematical formula}m−k+1; a higher score is more desirable. The figure's y-axis shows the ratio of the average scores to m. This figure supports the result of Fig. 5 and suggests that the ordering of mechanisms in terms of students' welfare is consistent over α. By comparing Figs. 6a and 6b, it can also be seen that students' welfare slightly worsens in Market B due to more competition among students.
     </paragraph>
     <paragraph>
      To illustrate the relationship between efficiency and fairness obtained by these mechanisms, we plot the average points of the obtained matchings in the x–y plane in Fig. 7 (when {a mathematical formula}α=0.6), where the x-axis shows the ratio of the average Borda scores of the students and the y-axis shows the ratio of students without envy or envy based on PL. The point in the upper-right corner is preferable, and the figure shows that the developed mechanisms outperformed the simple extensions of the existing mechanisms in both aspects. This figure displays a trade-off between the mechanisms; TTCR-SS does not maintain fairness but achieves an efficient outcome, while PLDA-MQ maintains fairness to a certain extent by giving up some efficiency. In Market B, the matching outcomes become worse for all the mechanisms due to a more competitive setting in terms of the number of schools a student might consider acceptable.
     </paragraph>
     <paragraph>
      We conclude this section by comparing the welfare of TTCR-SS and TTCR. Section 3 argues that the outcome of TTCR-SS may not Pareto dominate TTCR, i.e., some students might be worse off by exploiting the supplementary seats. The gray area in Fig. 8 shows the ratio of students who prefer TTCR-SS matching, and the black area shows the ratio of students who prefer TTCR matching. Note that this area is very narrow and resembles a line. The white area shows the ratio of students whose assignments are the same. For example, when {a mathematical formula}α=0.6, only 1% of the students prefer TTCR matching, while more than 60% prefer TTCR-SS matching. These figures clearly show that the fraction of students who are worse off due to TTCR-SS is rather small compared to the overwhelming majority of students who benefit from it.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      In this section we discuss some relevant issues about TTCR-SS and PLDA-MQ. In the first subsection, we discuss some relationships between TTCR-SS and the hierarchical exchange mechanism [37], which generalizes TTC. We show that TTCR-SS, as with the hierarchical exchange mechanism, satisfies the notion of group strategy-proofness. In the second subsection, we discuss the effects of choosing different MLs on the TTCR-SS outcome and different PLs on the PLDA-MQ outcome. We experimentally show that such effects are rather small.
     </paragraph>
     <section label="6.1">
      <section-title>
       Relationship between TTCR-SS and hierarchical exchange mechanism
      </section-title>
      <paragraph>
       In this subsection, we discuss some relationships between TTCR-SS and the hierarchical exchange mechanism [37], which is a generalization of TTC. As mentioned in the literature review, [37] proposed a class of exchange mechanisms called hierarchical exchange mechanisms, which characterize Pareto efficient, group strategy-proof, and reallocation proof mechanisms, when each object (or school in our context) has only one copy (or seat). Since she does not consider any distributional constraints, her notion of Pareto efficiency and ours are different. In particular, one can construct an example of a Pareto efficient (in the sense of [37]) allocation that does not satisfy minimum quotas and thus is not Pareto efficient according to our notion. On the other hand, one can construct an example of a Pareto efficient allocation that satisfies minimum quota (in the sense of our definition) but is not Pareto efficient among matchings that do not satisfy minimum quotas. Recall from the literature review that [40] generalized the characterization of [37] for environments where each object has one copy, and [39] generalized [40] to environments where each object can have more than one copy. Since the notion of Pareto efficiency in these papers and ours are different, TTCR-SS, which produces a Pareto efficient allocation based on our notion, is not an instance of the mechanisms proposed in [37], [40], or [39].
      </paragraph>
      <section label="6.1.1">
       <section-title>
        Group strategy-proofness of TTCR-SS
       </section-title>
       <paragraph>
        [37] showed that the hierarchical exchange mechanism is group strategy-proof. Given {a mathematical formula}S′⊆S, let {a mathematical formula}≻S′=(≻s′)s′∈S′ and {a mathematical formula}≻−S′=(≻s′)s′∈S∖S′. The notion of group strategy-proofness is described as follows.
       </paragraph>
       <paragraph label="Definition 12">
        group strategy-proofnessWe say mechanism φ is group strategy-proof if ∀ {a mathematical formula}≻S, there is no {a mathematical formula}S′⊆S and {a mathematical formula}≻S′′ such that {a mathematical formula}φs(≻S′′,≻−S′)⪰sφs(≻S′,≻−S′){a mathematical formula}∀s∈S′ and for some {a mathematical formula}s∈S′, {a mathematical formula}φs(≻S′′,≻−S′)≻sφs(≻S′,≻−S′).
       </paragraph>
       <paragraph>
        In other words, a mechanism is group strategy-proof if no set of students ever has any incentive to jointly misreport their preferences, regardless of the reports of the rest of the students.{sup:18}
       </paragraph>
       <paragraph>
        Note that group strategy-proofness is a stronger notion than strategy-proofness. Although TTCR-SS is different from the hierarchical exchange mechanism, in the following, we show that TTCR-SS is also group strategy-proof by following the previously developed techniques of [37]. First, we introduce the definition of nonbossiness.
       </paragraph>
       <paragraph label="Definition 13">
        nonbossinessWe say mechanism φ is nonbossy if {a mathematical formula}φs(≻s,≻−s)=φs(≻s′,≻−s) implies {a mathematical formula}φ(≻s,≻−s)=φ(≻s′,≻−s), ∀s, {a mathematical formula}≻s, {a mathematical formula}≻s′, and {a mathematical formula}≻−s.
       </paragraph>
       <paragraph>
        In words, a mechanism is nonbossy if no student can affect other students' assignments by changing her reporting preference, as long as her own assignment does not change.
       </paragraph>
       <paragraph label="Lemma 1">
        TTCR-SS is nonbossy.
       </paragraph>
       <paragraph label="Proof">
        See Appendix A.3.  □
       </paragraph>
       <paragraph label="Lemma 2">
        From this result and the strategy-proofness of TTCR-SS, it immediately follows (as shown in [37]) that TTCR-SS is group strategy-proof. Lemma 1 in [37]Strategy-proofness and nonbossiness imply group strategy-proofness.
       </paragraph>
       <paragraph label="Corollary 1">
        Although [37] assumes that each school has only one seat, one can easily verify from the proof of Lemma 1 in [37] that Lemma 2 holds in our setting, where each object (school) may have more than one copy (seat). Thus we have the following corollary. TTCR-SS is group strategy-proof.
       </paragraph>
      </section>
     </section>
     <section label="6.2">
      <section-title>
       Effect of choices of lists
      </section-title>
      <paragraph>
       We exploit two kinds of lists for our mechanisms to work: ML for TTCR-SS and PL for PLDA-MQ. While PL is generated to reflect the schools' priorities, the choice of ML can be completely independent from the market. Introducing such a list would be controversial if the obtained matching by a mechanism varied significantly, depending on the chosen list. In this subsection we examine whether our mechanisms are sensitive to the choices of lists. We focus on the number of assigned students to schools, which should reflect their popularity. Thus it is desirable that such numbers do not heavily depend on the choice of a list.
      </paragraph>
      <section label="6.2.1">
       <section-title>
        Effect of ML choices
       </section-title>
       <paragraph>
        To see the effect of the choice of ML, we fixed one problem instance of Market A in Section 5 and ran TTCR-SS for 100 randomly generated different MLs. Fig. 9 shows the differences of the number of assigned students under the cases of {a mathematical formula}α=0, 0.6, and 1. We show the average, minimum, and maximum numbers of allocated students for each school. The x-axis represents the schools that are sorted in decreasing order of their average number of assigned students. When {a mathematical formula}α=0, the preferences of the students are independent from each other and there is virtually no competition. Then the choice of ML did not affect the outcome very much; the average, minimum, and maximum numbers are almost the same (Fig. 9a). When {a mathematical formula}α=1, the preferences of the students are the same and they are all competing for the seats of the same popular schools. Thus the choice of ML affects who will be assigned to the popular schools, but it does not affect the number of students assigned to them. The average, minimum, and maximum numbers are identical (Fig. 9c). When {a mathematical formula}α=0.6, the number of allocated students can vary by the choice of ML. In this case, however, the numbers of students allocated to either popular or unpopular schools are almost the same under different MLs, and it varies in the schools that are neither popular nor unpopular (Fig. 9b). Thus we conjecture that the choice of ML is not very controversial; the choice only slightly affects the popularity of schools.
       </paragraph>
      </section>
      <section label="6.2.2">
       <section-title>
        Effect of PL choices
       </section-title>
       <paragraph>
        We also ran PLDA-MQ under different PLs. We fixed one problem instance of Market A in Section 5 and ran PLDA-MQ for 100 different PLs as follows. First we randomly generated 100 different orderings among schools. For each ordering σ, we fixed the round-robin ordering among the schools as {a mathematical formula}cσ(1)→cσ(2)→⋯→cσ(m)→cσ(1)→cσ(2)→⋯ and created a PL based on it, as in Section 5. Fig. 10 shows the differences of the number of assigned students under the cases of {a mathematical formula}α=0, 0.6, and 1. When {a mathematical formula}α=0, each school has enough students who consider it their favorite to satisfy its minimum quota. In this case, schools can just accept their prioritized students without referring to PL. Since there is no correlation in the student preferences, every student is assigned to her favorite school; recall Fig. 6a with {a mathematical formula}α=0. Using a different PL does not even change the outcome. As α increases, the preferences of students are more correlated, resulting in fluctuations for some schools (Figs. 9b and 9c). However, the difference in the numbers in a school under different PLs is at most 2. This shows the robustness of PLDA-MQ over different PLs in this respect, even in comparison with TTCR-SS over MLs. Thus we experimentally show evidence that the choice of PL has only a limited effect on the mechanism's outcome in terms of the number of filled seats of each school.
       </paragraph>
       <paragraph>
        Note that the choice of PL only affects the PLDA-MQ process when the mechanism needs to break ties among contracts of the same rank, e.g., when either one of the two contracts, {a mathematical formula}(s1,c1) and {a mathematical formula}(s2,c2) where {a mathematical formula}rank(s1,c1)=rank(s2,c2), must be rejected. Intuitively, such ties are more likely to occur in the later rounds of the process, and at that time the choice of PL, or rather the choice of σ, begins to matter. On the other hand, ML affects the TTCR-SS process from the beginning to the end, which results in more fluctuations among schools that are neither extremely popular nor unpopular.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <section label="A.1">
      <section-title>
       Proof of Theorem 1
      </section-title>
      <paragraph>
       We separately show the feasibility, strategy-proofness, and Pareto efficiency of TTCR-SS.
      </paragraph>
      <section label="A.1.1">
       <section-title>
        Proof of feasibility for TTCR-SS
       </section-title>
       <paragraph label="Proof">
        The outcome is clearly student-feasible since a student never selects a contract that is related to her unacceptable school.As for the school-feasibility of the outcome, we show by induction that {a mathematical formula}{Yk∪Zk} is school-feasible for any k. For {a mathematical formula}k=0, {a mathematical formula}{Y0∪Z0} is clearly school-feasible because {a mathematical formula}Y0=X⁎ is school-feasible and {a mathematical formula}Z0=∅. Suppose {a mathematical formula}{Yk∪Zk} is school-feasible for some k. The induction is completed if we show that for any {a mathematical formula}c∈C it holds that {a mathematical formula}pc≤|Yck+1|+|Zck+1|≤qc. If a contract related to c is not included in {a mathematical formula}Ck+1, the assignment related to c never changes and from the induction argument {a mathematical formula}pc≤|Yck+1|+|Zck+1|≤qc holds. Next, assume {a mathematical formula}(s,c)∈Ck+1 for some s. It is clear that {a mathematical formula}c∉Cmaxk+1. If {a mathematical formula}c∈Cinck+1 is the case, it holds that {a mathematical formula}Yck=Yck+1=∅ and {a mathematical formula}pc≤|Zck|&lt;qc. Furthermore, {a mathematical formula}s=sd. The fact {a mathematical formula}(sd,c)∈Ck+1 implies {a mathematical formula}|Zck+1|=|Zck|+1, and therefore {a mathematical formula}pc≤|Yck+1|+|Zck+1|=|Zck+1|≤qc holds. If {a mathematical formula}c∈Cdeck+1 is the case, it follows that {a mathematical formula}pc&lt;|Yck|+|Zck|≤qc with {a mathematical formula}Yck≠∅. The fact {a mathematical formula}(s,c)∈Ck+1 implies {a mathematical formula}|Yck+1|=|Yck|−1. It holds either {a mathematical formula}Zck+1=Zck or {a mathematical formula}|Zck+1|=|Zck|+1, depending on who (a dummy or a non-dummy student) obtains the seat of c in {a mathematical formula}Ck+1. In either case, {a mathematical formula}pc≤|Yck+1|+|Zck+1|≤qc holds. Finally, if {a mathematical formula}c∈Cmink+1 is the case, it holds that {a mathematical formula}pc=|Yck|+|Zck|≤qc with {a mathematical formula}Yck≠∅. The fact {a mathematical formula}(s,c)∈Ck+1 implies {a mathematical formula}|Yck+1|=|Yck|−1. It also implies that {a mathematical formula}|Zck+1|=|Zck|+1, since a dummy student never obtains a seat of c in {a mathematical formula}Ck+1. Thus {a mathematical formula}pc=|Yck+1|+|Zck|≤qc holds.  □
       </paragraph>
      </section>
      <section label="A.1.2">
       <section-title>
        Proof of strategy-proofness for TTCR-SS
       </section-title>
       <paragraph>
        We need several lemmas to prove strategy-proofness for TTCR-SS.
       </paragraph>
       <paragraph>
        School c is available at Round k if either (i) {a mathematical formula}Cdeck≠∅ and {a mathematical formula}c∈C∖Cmaxk or (ii) {a mathematical formula}Cdeck=∅ and {a mathematical formula}c∈Cmink hold. Let {a mathematical formula}Cavak denote the set of all available schools. At Round k, a contract related to school c is clearly included in {a mathematical formula}Vk if and only if c is available at Round k.
       </paragraph>
       <paragraph>
        It is obvious that the following lemma holds from the category transition of the schools and the definition of {a mathematical formula}Cavak.
       </paragraph>
       <paragraph label="Lemma 3">
        For any two Rounds k and{a mathematical formula}k′with{a mathematical formula}k&lt;k′,{a mathematical formula}Cdeck⊇Cdeck′and{a mathematical formula}Cavak⊇Cavak′hold.
       </paragraph>
       <paragraph>
        Intuitively, this lemma means that the possible choices for a student weakly monotonically shrink in the later rounds. As a result, the following lemma argues that a student's choice is the best within all the schools that are available in the later rounds.
       </paragraph>
       <paragraph label="Proof">
        Suppose TTCR-SS obtains{a mathematical formula}X′. For any k and{a mathematical formula}c∈Cavak, and any student s who is included in{a mathematical formula}Ck′, i.e., a cycle at Round{a mathematical formula}k′≤k,{a mathematical formula}Xs′⪰s{(s,c)}holds.From Lemma 3, {a mathematical formula}Cavak⊆Cavak′ holds. Also, the fact that s is included in {a mathematical formula}Ck′ means that {a mathematical formula}{(s,c′)}=Xs′ and {a mathematical formula}c′ is the most preferred school for s within {a mathematical formula}Cavak′. Thus {a mathematical formula}Xs′⪰s{(s,c)} holds.  □
       </paragraph>
       <paragraph>
        The following lemma implies if there exists a directed path toward a contract at some round, it remains in the later rounds unless the contract is removed because it is included in a cycle. As a consequence, if a student is assigned to a school by her manipulative report, then she can be assigned to the school when it becomes her best available school during the mechanism.
       </paragraph>
       <paragraph label="Proof">
        Suppose there is a directed path from contract{a mathematical formula}(s,c)to{a mathematical formula}(s′,c′)in{a mathematical formula}Gk, and suppose{a mathematical formula}(s′,c′)∈Vk′for some{a mathematical formula}k′&gt;k. Then exactly the same directed path from{a mathematical formula}(s,c)to{a mathematical formula}(s′,c′)exists in{a mathematical formula}Gk′.It is sufficient to show that {a mathematical formula}((s,c),(s′,c′))∈Ek and {a mathematical formula}(s′,c′)∈Vk+1 imply {a mathematical formula}((s,c),(s′,c′))∈Ek+1, since a directed path is a sequence of directed edges. First, suppose {a mathematical formula}s≠sd. From Lemma 3, {a mathematical formula}Cavak+1⊆Cavak holds. Since {a mathematical formula}c′ is the most preferred school for s within {a mathematical formula}Cavak, if {a mathematical formula}c′∈Cavak+1, {a mathematical formula}c′ remains the most preferred school for s within {a mathematical formula}Cavak+1. Thus {a mathematical formula}((s,c),(s′,c′))∈Ek+1 holds. Second, suppose {a mathematical formula}s=sd. The fact that {a mathematical formula}((sd,c),(s′,c′))∈Ek implies that {a mathematical formula}c′ is decrementable at Round k and that {a mathematical formula}s′ has the highest priority in ML among all the remaining students in all the decrementable schools. According to Lemma 3, the set of decrementable schools never expands. As long as {a mathematical formula}(s′,c′) remains in {a mathematical formula}Vk+1, {a mathematical formula}c′ remains decrementable and {a mathematical formula}s′ still has the highest priority in ML among all the remaining students in all the decrementable schools at Round {a mathematical formula}k+1. Thus {a mathematical formula}((s,c),(s′,c′))∈Ek+1 holds.  □
       </paragraph>
       <paragraph label="Proof">
        The following lemma means that the declared preference of a student does not affect the outcome of the rounds before she is included in a cycle. Fix the reported preferences of all students except s at{a mathematical formula}≻−s. Suppose that{a mathematical formula}(s,ω(s))∈Ckif she reports{a mathematical formula}≻sand{a mathematical formula}(s,ω(s))∈Ck′if she reports{a mathematical formula}≻s′, where{a mathematical formula}k≤k′. Then{a mathematical formula}C⁎kdoes not change, where “⁎” can be either “max,” “min,” “inc,” “dec,” or “ava,” regardless of whether student s reports{a mathematical formula}≻sor{a mathematical formula}≻s′.Since {a mathematical formula}(s,ω(s))∉Ckˆ holds for any {a mathematical formula}kˆ&lt;k, the same contracts form cycles before Round k whether student s reports {a mathematical formula}≻s or {a mathematical formula}≻s′. Then the remaining contracts in {a mathematical formula}Yk−1 are identical in both cases. Also, the same sets of contracts are added to Z in both cases. This implies that {a mathematical formula}C⁎k does not change.  □
       </paragraph>
       <paragraph>
        Now, we are ready to prove that TTCR-SS is strategy-proof.
       </paragraph>
       <paragraph>
        Proof of strategy-proofness for TTCR-SS
       </paragraph>
       <paragraph label="Proof">
        Fix the reported preferences of all the students except s at {a mathematical formula}≻−s and denote {a mathematical formula}≻=(≻s,≻−s) and {a mathematical formula}≻′=(≻s′,≻−s), where {a mathematical formula}≻s is her true preference and {a mathematical formula}≻s′ is fake. For Round k, explicitly write {a mathematical formula}Vk(≻), {a mathematical formula}Gk(≻), {a mathematical formula}Ek(≻), and {a mathematical formula}Ck(≻) to denote {a mathematical formula}Vk, {a mathematical formula}Gk, {a mathematical formula}Ek, and {a mathematical formula}Ck when the reported preference profile is ≻ and so on. Explicitly write {a mathematical formula}C⁎k(≻) to denote {a mathematical formula}C⁎k when the reported preference profile is ≻ and so on. Suppose that {a mathematical formula}(s,ω(s))∈Ck(≻), i.e., if s reports her true preference {a mathematical formula}≻s, she belongs to a cycle at Round k, and {a mathematical formula}(s,ω(s))∈Ck′(≻′), i.e., if she reports some other preference {a mathematical formula}≻s′, she belongs to a cycle at Round {a mathematical formula}k′.First, assume {a mathematical formula}k≤k′. Since {a mathematical formula}(s,ω(s))∈Ck(≻), s must be matched with her most preferred school within {a mathematical formula}Cavak(≻). Also, {a mathematical formula}(s,ω(s))∈Ck′(≻′) means that s is matched with a school within {a mathematical formula}Cavak′(≻′). Therefore, it is sufficient to show that {a mathematical formula}Cavak′(≻′)⊆Cavak(≻) holds. Since {a mathematical formula}k≤k′, it follows from Lemma 6 that {a mathematical formula}Cavak(≻′)=Cavak(≻) holds. Also, from Lemma 3, it follows that {a mathematical formula}Cavak′(≻′)⊆Cavak(≻′). Combining these results, we have {a mathematical formula}Cavak′(≻′)⊆Cavak(≻).Next assume {a mathematical formula}k&gt;k′. Since {a mathematical formula}(s,ω(s))∈Ck′(≻′), there exists a directed path from {a mathematical formula}(s′,c′) to {a mathematical formula}(s,ω(s)) in {a mathematical formula}Gk′(≻′), where {a mathematical formula}((s,ω(s)),(s′,c′))∈Ek′(≻′). From Lemma 6, {a mathematical formula}Cavak′(≻′)=Cavak′(≻) holds. Thus, there exists the same directed path from {a mathematical formula}(s′,c′) to {a mathematical formula}(s,ω(s)) in {a mathematical formula}Gk′(≻). The fact that {a mathematical formula}(s,ω(s))∈Ck(≻) implies {a mathematical formula}(s,ω(s))∈Vk(≻), and thus from Lemma 5 there exists the same directed path from {a mathematical formula}(s′,c′) to {a mathematical formula}(s,ω(s)) in {a mathematical formula}Gk(≻). Then s's assignment under ≻ is at least as good as {a mathematical formula}c′, which is the assignment under {a mathematical formula}≻′. Thus s cannot be better off by reporting {a mathematical formula}≻s′.  □
       </paragraph>
      </section>
      <section label="A.1.3">
       <section-title>
        Proof of Pareto efficiency for TTCR-SS
       </section-title>
       <paragraph label="Proof">
        We show, by induction, that the following statement is true when we run TTCR-SS: A student, who is matched at Round r, cannot be better off without making a student, who is matched before r, worse off.When {a mathematical formula}r=1, the statement is trivially true because a matched student at Round 1 is assigned to her top choice.Assume the supposition is true up to {a mathematical formula}r=k. Consider {a mathematical formula}r=k+1. Take student s who is matched to a school c at Round {a mathematical formula}k+1, and assume her assignment is not her top choice. If no such s exists, then every student goes to her top choice, and thus the statement is true.From Lemma 4, for any school {a mathematical formula}c′ such that {a mathematical formula}c′≻sc, it holds that {a mathematical formula}c′∉Cavak+1. Then either (i) {a mathematical formula}c′∈Cmaxk+1 or (ii) {a mathematical formula}c′∈Cinck+1 and {a mathematical formula}Cdeck+1=∅ holds.If (i) {a mathematical formula}c′∈Cmaxk+1 is the case, then {a mathematical formula}c′ is already matched to students up to its maximum quota before Round {a mathematical formula}k+1. Improving s, by assigning her to {a mathematical formula}c′, therefore necessarily forces a student who is matched before Round {a mathematical formula}k+1 to leave {a mathematical formula}c′ to make room for s. However, because of the induction argument, it is not possible to improve the departing student without making someone worse off.Suppose (ii) {a mathematical formula}c′∈Cinck+1 and {a mathematical formula}Cdeck+1=∅ is the case. Then at Round {a mathematical formula}k+1, the number of seats that must be filled to satisfy the minimum quotas equals the number of students who have not been matched yet. Therefore, improving student s, by assigning her a school that is not available at {a mathematical formula}k+1, necessarily forces a student who was matched before {a mathematical formula}k+1 to change her assignment to satisfy the minimum quotas. From the induction argument, however, such a change will make someone worse off.  □
       </paragraph>
      </section>
     </section>
     <section label="A.2">
      <section-title>
       Proof of Theorem 3
      </section-title>
      <paragraph>
       We first introduce an equilibrium concept based on choice functions proposed by [20].
      </paragraph>
      <paragraph label="Definition 14">
       HM-stability{a mathematical formula}X′⊆X is Hatfield–Milgrom (HM-) stable if {a mathematical formula}X′=ChS(X′)=ChC(X′) and there exists no {a mathematical formula}x∈X∖X′ such that {a mathematical formula}x∈ChS(X′∪{x}) and {a mathematical formula}x∈ChC(X′∪{x}) hold.
      </paragraph>
      <paragraph label="Definition 15">
       Note that if {a mathematical formula}ChS and {a mathematical formula}ChC are the ones for PLDA-MQ defined in Subsection 4.3, then it always holds that {a mathematical formula}X′=ChS(X′)=ChC(X′) whenever {a mathematical formula}X′ is a matching. Next we introduce some mathematical tools used in the proofs. M{sup:♮}-concavityWe say that f is M{sup:♮}-concave if for all {a mathematical formula}Y,Z⊆X and {a mathematical formula}y∈Y∖Z, there exists {a mathematical formula}z∈(Z∖Y)∪{∅} such that {a mathematical formula}f(Y)+f(Z)≤f((Y∖{y})∪{z})+f((Z∖{z})∪{y}) holds.
      </paragraph>
      <paragraph label="Definition 16">
       M{sup:♮}-concavity, introduced in [34], is a discrete analogue of concavity. We also exploit the notion of matroid, see for example, [36]. matroidLet X be a finite set and let {a mathematical formula}F be a family of the subsets of X. Pair {a mathematical formula}(X,F) is a matroid if it satisfies the following conditions:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}∅∈F,
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}X′∈F and {a mathematical formula}X″⊂X′, then {a mathematical formula}X″∈F holds,
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}X′,X″∈F and {a mathematical formula}|X′|&gt;|X″|, then there exists {a mathematical formula}x∈X′∖X″ such that {a mathematical formula}X″∪{x}∈F.
       </list-item>
      </list>
      <paragraph label="Theorem 5">
       Next we present the existing results in [27], which connects the aforementioned concepts. Theorem 5, which is identical to Theorem 1 in their paper, clarifies the conditions so that GDA satisfies several desirable properties. Theorem 1 in [27]Suppose that the preference of the schools can be represented by M{sup:♮}-concave function f. Then
      </paragraph>
      <list>
       <list-item label="1.">
        GDA is strategy-proof and the obtained matching is student-optimal in all of the HM-stable matchings.
       </list-item>
       <list-item label="2.">
        The time complexity of GDA is{a mathematical formula}O(T(f)⋅|X|2), assuming f can be calculated in{a mathematical formula}T(f)time.
       </list-item>
      </list>
      <paragraph label="Theorem 6">
       Furthermore, they show a sufficient condition where f becomes M{sup:♮}-concave. Theorem 3 in [27]Suppose{a mathematical formula}f=fˆ+f˜, where (i){a mathematical formula}fˆreturns −∞ if{a mathematical formula}X′violates the hard constraint and otherwise it returns 0, and (ii){a mathematical formula}f˜(X′)=∑x∈X′v(x), where{a mathematical formula}v:X→(0,∞)is a function such that{a mathematical formula}x≠x′implies{a mathematical formula}v(x)≠v(x′). Then f is M{sup:♮}-concave if{a mathematical formula}(X,domfˆ)is a matroid.
      </paragraph>
      <paragraph>
       Note that function f, defined in Subsection 4.3, satisfies conditions (i) and (ii). Let {a mathematical formula}fˆ be the function proposed in Definition 10. The following lemma shows that we can use these results in PLDA-MQ.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}(X,domfˆ)is a matroid.It is clear that {a mathematical formula}fˆ(∅)=0, and thus {a mathematical formula}∅∈domfˆ holds. Also, if {a mathematical formula}fˆ(X′)=0, then for any {a mathematical formula}X″⊂X′, {a mathematical formula}fˆ(X″)=0 holds since {a mathematical formula}max⁡(|Xc″|,pc)≤max⁡(|Xc′|,pc) holds for all {a mathematical formula}c∈C when {a mathematical formula}X″⊂X′ holds.Finally, we show that for any {a mathematical formula}X′,X″∈domfˆ, where {a mathematical formula}|X′|&gt;|X″|, there exists {a mathematical formula}x∈X′∖X″ such that {a mathematical formula}X″∪{x}∈domfˆ holds.Let {a mathematical formula}C˜ denote {a mathematical formula}{c∈C‖Xc″|&lt;pc}. If there exists {a mathematical formula}c∈C˜ with {a mathematical formula}|Xc′|&gt;|Xc″|, we can choose any {a mathematical formula}(s,c)∈Xc′∖Xc″ such that {a mathematical formula}X″∪{(s,c)}∈domfˆ holds, since {a mathematical formula}|Xc″|&lt;pc. Thus assume for all {a mathematical formula}c∈C˜, {a mathematical formula}|Xc′|≤|Xc″| holds.{sup:19} Since {a mathematical formula}|X′|&gt;|X″| and {a mathematical formula}|Xc′|≤|Xc″| hold for all {a mathematical formula}c∈C˜, {a mathematical formula}∑c∈C∖C˜|Xc′|&gt;∑c∈C∖C˜|Xc″| holds. Also, there exists {a mathematical formula}c′∈C∖C˜ such that {a mathematical formula}|Xc′′|&gt;|Xc′″| holds. Thus we can choose {a mathematical formula}(s,c′)∈Xc′′∖Xc′″. Let Y denote {a mathematical formula}X″∪{(s,c′)}. Note that {a mathematical formula}∑c∈Cmax⁡(|Xc″|,pc)=∑c∈C∖C˜|Xc″|+∑c∈C˜pc&lt;∑c∈C∖C˜|Xc′|+∑c∈C˜pc≤n holds, and therefore {a mathematical formula}∑c∈Cmax⁡(|Yc|,pc)=∑c∈Cmax⁡(|Xc″|,pc)+1≤n holds. Thus {a mathematical formula}fˆ(Y)=0 and {a mathematical formula}Y∈domfˆ hold.  □
      </paragraph>
      <paragraph>
       The following lemmas show a relationship between HM-stability and PL-stability.
      </paragraph>
      <paragraph label="Lemma 8">
       {a mathematical formula}ChC(X′)is equivalent to the following procedure:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Y←∅.
       </list-item>
       <list-item label="2.">
        Remove{a mathematical formula}(s,c)from{a mathematical formula}X′such that{a mathematical formula}v((s,c))is largest in{a mathematical formula}X′. If there exists no such contract, terminate the procedure and return Y.
       </list-item>
       <list-item label="3.">
        If{a mathematical formula}fˆ(Y∪{(s,c)})=0, then{a mathematical formula}Y←Y∪{(s,c)}. Go to 2.
       </list-item>
      </list>
      <paragraph label="Proof">
       Since {a mathematical formula}(X,domfˆ) is a matroid, the above greedy procedure, which selects a contract from {a mathematical formula}X′ one by one according to v, is guaranteed to obtain {a mathematical formula}arg⁡maxX″⊆X′⁡f(X″), i.e., the optimal solution [36].  □
      </paragraph>
      <paragraph label="Proof">
       Student s is never rejected by her initial endowment school{a mathematical formula}ω(s), i.e., whenever{a mathematical formula}(s,ω(s))∈X′,{a mathematical formula}(s,ω(s))∈ChC(X′)holds.If {a mathematical formula}(s,ω(s))∈X′, since {a mathematical formula}≻PL respects the initial endowments, when {a mathematical formula}(s,ω(s)) is selected in the procedure of Lemma 8, {a mathematical formula}Y∪{(s,ω(s))}⊆X⁎ holds. Since {a mathematical formula}fˆ(X⁎)=0, {a mathematical formula}fˆ(Y∪{(s,ω(s))})=0 holds. Thus {a mathematical formula}(s,ω(s)) is included in {a mathematical formula}ChC(X′).  □
      </paragraph>
      <paragraph label="Proof">
       Matching{a mathematical formula}X′is HM-stable iff it is PL-stable.We first show that HM-stability implies PL-stability. First, assume for contradiction, {a mathematical formula}X′ is HM-stable but there exists a student who has justified envy; there exist {a mathematical formula}(s,c)∈X′, {a mathematical formula}(s′,c′)∈X′∖X⁎, and {a mathematical formula}(s,c′)∈X∖X′ such that {a mathematical formula}(s,c′)≻s(s,c) and {a mathematical formula}(s,c′)≻c′(s′,c′) hold. Then it is clear that {a mathematical formula}(s,c′)∈ChS(X′∪{(s,c′)}) holds. Also, in the procedure of Lemma 8, when calculating {a mathematical formula}ChC(X′∪{(s,c′)}), {a mathematical formula}(s,c′) is selected before {a mathematical formula}(s′,c′) since {a mathematical formula}ω(s)≠c′,ω(s′)≠c′, and {a mathematical formula}≻PL respects {a mathematical formula}≻C. In the calculation of {a mathematical formula}ChC(X′), when {a mathematical formula}(s′,c′) is selected, {a mathematical formula}fˆ(Y∪{(s′,c′)})=0 holds since {a mathematical formula}X′=ChC(X′). In the calculation of {a mathematical formula}ChC(X′∪{(s,c′)}), when {a mathematical formula}(s,c′) is selected, {a mathematical formula}fˆ(Y∪{(s,c′)})=0 also holds. Then {a mathematical formula}(s,c′)∈ChC(X′∪{(s,c′)}) holds; {a mathematical formula}X′ is not HM-stable.Second, assume {a mathematical formula}X′ is HM-stable but there exists a student who has justified envy based on PL, i.e., there exist {a mathematical formula}(s,c),(s′,c′)∈X′ and {a mathematical formula}(s,c″)∈X∖X′ such that {a mathematical formula}(s,c″)≻s(s,c), {a mathematical formula}|Xc″′|&lt;qc″, {a mathematical formula}|Xc′′|&gt;pc′ and {a mathematical formula}(s,c″)≻PL(s′,c′) hold. It is clear that {a mathematical formula}(s,c″)∈ChS(X′∪{(s,c″)}) holds. In the procedure of Lemma 8, when calculating {a mathematical formula}ChC(X′∪{(s,c″)}), {a mathematical formula}(s,c″) is selected before {a mathematical formula}(s′,c′). In the calculation of {a mathematical formula}ChC(X′), when {a mathematical formula}(s′,c′) is selected, {a mathematical formula}fˆ(Y∪{(s′,c′)})=0 holds since {a mathematical formula}X′=ChC(X′). In the calculation of {a mathematical formula}ChC(X′∪{(s,c″)}), when {a mathematical formula}(s,c″) is selected, {a mathematical formula}fˆ(Y∪{(s,c″)})=0 also holds since {a mathematical formula}|Xc″′|&lt;qc″ and {a mathematical formula}|Xc′′|&gt;pc′ hold. Then {a mathematical formula}(s,c″)∈ChC(X′∪{(s,c″)}) holds; {a mathematical formula}X′ is not HM-stable.Third, assume {a mathematical formula}X′ is HM-stable but not PL-nonwasteful, i.e., there exist {a mathematical formula}(s,c)∈X′ and {a mathematical formula}(s,c′)∈X∖X′ such that {a mathematical formula}(s,c′)≻s(s,c), {a mathematical formula}|Xc′′|&lt;qc′, {a mathematical formula}|Xc′|&gt;pc, and {a mathematical formula}(s,c′)≻PL(s,c) hold. It is clear that {a mathematical formula}(s,c′)∈ChS(X′∪{(s,c′)}) holds. Also, in the procedure of Lemma 8, when calculating {a mathematical formula}ChC(X′∪{(s,c′)}), {a mathematical formula}(s,c′) is selected before {a mathematical formula}(s,c). In the calculation of {a mathematical formula}ChC(X′), when {a mathematical formula}(s,c) is selected, {a mathematical formula}fˆ(Y∪{(s,c)})=0 holds since {a mathematical formula}X′=ChC(X′). In the calculation of {a mathematical formula}ChC(X′∪{(s,c′)}), when {a mathematical formula}(s,c′) is selected, {a mathematical formula}fˆ(Y∪{(s,c′)})=0 also holds since {a mathematical formula}|Xc′′|&lt;qc′ and {a mathematical formula}|Xc′|&gt;pc hold. Then {a mathematical formula}(s,c′)∈ChC(X′∪{(s,c′)}) holds; {a mathematical formula}X′ is not HM-stable.Next we show that PL-stability implies HM-stability. Assume {a mathematical formula}X′ is not HM-stable, i.e., there exists contract {a mathematical formula}(s,c′)∈X∖X′ such that {a mathematical formula}(s,c′)∈ChS(X′∪{(s,c′)}) and {a mathematical formula}(s,c′)∈ChC(X′∪{(s,c′)}) hold. It is clear that {a mathematical formula}(s,c′)≻s(s,c) holds for some {a mathematical formula}(s,c)∈X′. Since {a mathematical formula}|X′|=n, there exists at least one contract {a mathematical formula}(s″,c″)∈ChC(X′) and {a mathematical formula}(s″,c″)∉ChC(X′∪{(s,c′)}). {a mathematical formula}(s″,c″) is rejected as a consequence of accepting {a mathematical formula}(s,c′). Since {a mathematical formula}(s″,c″) is rejected, {a mathematical formula}ω(s″)≠c″ holds from Lemma 9. Also, it is clear that {a mathematical formula}(s,c′)≻PL(s″,c″) holds. First, assume {a mathematical formula}s″≠s and {a mathematical formula}c″=c′ hold. Then {a mathematical formula}(s,c′)≻PL(s″,c′) and {a mathematical formula}(s,c′)≻c′(s″,c′) hold since {a mathematical formula}ω(s)≠c′, {a mathematical formula}ω(s″)≠c′, and {a mathematical formula}≻PL respects {a mathematical formula}≻C. Therefore, s has justified envy toward {a mathematical formula}s″. Second, assume {a mathematical formula}c″≠c′ holds. Then {a mathematical formula}|Xc″′|&gt;pc″ holds since {a mathematical formula}(s″,c″) is rejected by accepting s to another school {a mathematical formula}c′. It is clear that {a mathematical formula}|Xc′′|&lt;qc′ holds. If {a mathematical formula}s″≠s, s has justified envy toward {a mathematical formula}s″ based on PL. If {a mathematical formula}s″=s, s claims an empty seat of {a mathematical formula}c′ based on PL since {a mathematical formula}c″=c holds. In either case, {a mathematical formula}X′ is not PL-stable.  □
      </paragraph>
      <paragraph>
       With these results, we obtain the following.
      </paragraph>
      <section label="A.2.1">
       <section-title>
        Proof of feasibility for PLDA-MQ
       </section-title>
       <paragraph label="Proof">
        Assume PLDA-MQ obtains set of contracts {a mathematical formula}X′. If {a mathematical formula}Xs′=∅, then {a mathematical formula}(s,ω(s))∈ChS(X′∪{(s,ω(s))}) holds. Also, from Lemma 9, {a mathematical formula}(s,ω(s))∈ChC(X′∪{(s,ω(s))}) holds. This violates the fact that GDA obtains an HM-stable matching. If {a mathematical formula}Xs′={(s,c)} holds, for each student s, {a mathematical formula}(s,c) is clearly acceptable for s since {a mathematical formula}(s,c)∈ChS(X′). Thus {a mathematical formula}X′ is student-feasible. Since each student is accepted by some school, {a mathematical formula}|X′|=n holds.Next we show that {a mathematical formula}X′ is school-feasible. It is clear that all contracts in {a mathematical formula}Xc′ are acceptable for c. Also, for all {a mathematical formula}c∈C, {a mathematical formula}|Xc′|≤qc holds, since otherwise, {a mathematical formula}fˆ(X′)=−∞ and {a mathematical formula}ChC(X′) cannot be {a mathematical formula}X′. Assume for contradiction there exists {a mathematical formula}c∈C such that {a mathematical formula}|Xc′|&lt;pc. Then {a mathematical formula}∑c∈Cmax⁡(|Xc′|,pc)&gt;|X′|=n. Thus {a mathematical formula}fˆ(X′)=−∞ and {a mathematical formula}ChC(X′) cannot be {a mathematical formula}X′.  □
       </paragraph>
      </section>
      <section label="A.2.2">
       <section-title>
        Proof of strategy-proofness, PL-stability, and obtaining the student-optimal matching within all the PL-stable matchings for PLDA-MQ
       </section-title>
       <paragraph label="Proof">
        From Lemma 7 and Theorem 6, the f used in PLDA-MQ is M{sup:♮}-concave. Thus from Condition 1 of Theorem 5, PLDA-MQ is strategy-proof and obtains the student-optimal matching within all HM-stable matchings. From Lemma 10, HM-stability is equivalent to PL-stability. Thus PLDA-MQ satisfies these properties.  □
       </paragraph>
      </section>
     </section>
     <section label="A.3">
      <section-title>
       Proof of Lemma 1
      </section-title>
      <paragraph label="Proof">
       Fix ≻, s, and {a mathematical formula}≻s′ such that {a mathematical formula}≻′=(≻s′,≻−s), and suppose TTCR-SS assigns s to the same school under ≻ and {a mathematical formula}≻′. Let k and {a mathematical formula}k′ be such that {a mathematical formula}(s,ω(s))∈Ck(≻) and {a mathematical formula}(s,ω(s))∈Ck′(≻′). If {a mathematical formula}k=k′, then the assumption that s receives the same assignment implies that exactly the same cycles are formed at each round under ≻ and {a mathematical formula}≻′. Thus consider when {a mathematical formula}k≠k′ holds, and without loss of generality assume {a mathematical formula}k&lt;k′.Let {a mathematical formula}k⁎≥k be such that TTCR-SS terminates at Round {a mathematical formula}k⁎ when the input is ≻. Given some {a mathematical formula}z≤k⁎, take any cycle in {a mathematical formula}Gz(≻). We show that there exists {a mathematical formula}z′ such that the cycle is formed in {a mathematical formula}Gz′(≻′), which implies that the outcomes are identical.First, suppose {a mathematical formula}1≤z&lt;k. Obviously, this cycle is formed in {a mathematical formula}Gz(≻′). Next consider {a mathematical formula}k≤z≤k⁎. The rest of the proof is done by induction on z.When {a mathematical formula}z=k, which is the base case, then all the cycles formed in {a mathematical formula}Gk(≻), except the one in which {a mathematical formula}(s,ω(s)) is involved, are formed in {a mathematical formula}Gk(≻′). From Lemma 5 and since the assignments of s are identical in both cases, the same cycle containing {a mathematical formula}(s,ω(s)) in {a mathematical formula}Gk(≻) is formed in {a mathematical formula}Gk′(≻′). Thus it is true for the base case.Assume the supposition is true up to some z, {a mathematical formula}k≤z&lt;k⁎. Take any cycle in {a mathematical formula}Gz+1(≻), and let {a mathematical formula}((sˆ1,cˆ1),…,(sˆt,cˆt),(sˆ1,cˆ1)) be the cycle. Assume first that it does not contain any contract related to a dummy student. For each ℓ, {a mathematical formula}1≤ℓ≤t, there must exist Round {a mathematical formula}zℓ′ such that {a mathematical formula}(sℓˆ,cℓˆ)∈Czℓ′(≻′). We show that {a mathematical formula}zℓ′≥zℓ+1′ holds for all ℓ, {a mathematical formula}1≤ℓ≤t with {a mathematical formula}t+1=1, where under {a mathematical formula}≻′, the contract {a mathematical formula}(sˆℓ,cˆℓ) does not leave the mechanism before {a mathematical formula}(sˆℓ+1,cˆℓ+1). Given that the supposition is true, {a mathematical formula}sˆℓ cannot obtain any of the seats that are gone by the end of Round z under ≻, when the input is {a mathematical formula}≻′. Thus {a mathematical formula}cˆℓ+1, which is the school she receives at Round {a mathematical formula}z+1 under ≻, must be the best possible assignment for her under the supposition and {a mathematical formula}≻′. On the other hand, {a mathematical formula}sˆℓ+1 has the highest priority in {a mathematical formula}≻ML to represent {a mathematical formula}cˆℓ+1 among those whose assignments are not fixed by the supposition. Therefore, if {a mathematical formula}((sˆℓ,cˆℓ),(sˆℓ+1,cˆℓ+1)){a mathematical formula}∉Ezℓ′(≻′) is the case, then {a mathematical formula}(sˆℓ+1,cˆℓ+1) is already gone before Round {a mathematical formula}zℓ′, i.e., {a mathematical formula}zℓ′&gt;zℓ+1′. If {a mathematical formula}((sℓˆ,cℓˆ),(sˆℓ+1,cˆℓ+1))∈Ezℓ′(≻′) holds, then it obviously follows that {a mathematical formula}zℓ′=zℓ+1′. In any case, {a mathematical formula}zℓ′≥zℓ+1′ holds. This argument implies that if the cycle is a self-loop, then it must be formed under {a mathematical formula}≻′.Next suppose the cycle contains a contract related to a dummy student. There is at most one such contract in the cycle, because all dummy students point to the same contract in a round. Without loss of generality, assume {a mathematical formula}sˆt=sd and let {a mathematical formula}((sˆ1,cˆ1),…,(sˆt−1,cˆt−1),(sd,cˆt),(sˆ1,cˆ1)) be the cycle. There must exist {a mathematical formula}zℓ′ such that {a mathematical formula}(sˆℓ,cˆℓ)∈Czℓ′(≻′) for each ℓ, {a mathematical formula}1≤ℓ≤t−1, and the previous argument leads to {a mathematical formula}z1′≥⋯≥zt−1′. What follows shows that {a mathematical formula}zt′ exists, i.e., supplementary seat {a mathematical formula}(sd,cˆt) leaves the mechanism under {a mathematical formula}≻′ by forming a cycle. Since {a mathematical formula}((sd,cˆt),(sˆ1,cˆ1))∈Ez+1(≻) is the case, it follows that {a mathematical formula}cˆ1∈Cdecz+1(≻). The supposition then implies that {a mathematical formula}cˆ1∈Cdecz1′(≻′). Since {a mathematical formula}z1′≥zt−1′ holds, it follows from Lemma 3 that {a mathematical formula}cˆ1∈Cdeczt−1′(≻′). Therefore, if {a mathematical formula}((sˆt−1,cˆt−1),(sd,cˆt))∉Ezt−1′(≻′) occurs, it implies that {a mathematical formula}cˆt∈Cmaxzt−1′(≻′), i.e., supplementary seat {a mathematical formula}(sd,cˆt) has been taken by another student at some round before Round {a mathematical formula}zt−1′. If {a mathematical formula}((sˆt−1,cˆt−1),(sd,cˆt))∈Ezt−1′(≻′) is the case, then {a mathematical formula}zt′ clearly exists with {a mathematical formula}zt−1′=zt′. In both cases, {a mathematical formula}zt′ exists and {a mathematical formula}zt−1′≥zt′ holds. Then the previous argument can be applied to pair of contracts {a mathematical formula}(sd,cˆt) and {a mathematical formula}(sˆ1,cˆ1), and it must hold that {a mathematical formula}zt′≥z1′.Therefore, {a mathematical formula}z1′≥⋯≥zt′≥z1′ should be satisfied in all cases. This condition can only be satisfied with equalities. Thus all the contracts in the cycle are in {a mathematical formula}Vz′(≻′) for some {a mathematical formula}z′, and all leave the mechanism at Round {a mathematical formula}z′. The requirement for equalities directly implies {a mathematical formula}((sℓˆ,cℓˆ),(sˆℓ+1,cˆℓ+1))∈Ez′(≻′) for all ℓ, i.e., the cycle is formed in {a mathematical formula}Gz′(≻′).  □
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>