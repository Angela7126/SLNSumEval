<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A logic for reasoning about ambiguity.
   </title>
   <abstract>
    Standard models of multi-agent modal logic do not capture the fact that information is often ambiguous, and may be interpreted in different ways by different agents. We propose a framework that can model this, and consider different semantics that capture different assumptions about the agents' beliefs regarding whether or not there is ambiguity. We examine the expressive power of logics of ambiguity compared to logics that cannot model ambiguity, with respect to the different semantics that we propose.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In the study of multi-agent modal logics, it is implicitly assumed that all agents interpret all formulas the same way. While they may have different beliefs regarding whether a formula φ is true, they agree on what φ means. Formally, this is captured by the fact that the truth of φ does not depend on the agent.
     </paragraph>
     <paragraph>
      Of course, in the real world, there is ambiguity; different agents may interpret the same utterance in different ways. For example, consider a public announcement p. Each player i may interpret p as corresponding to some event {a mathematical formula}Ei, where {a mathematical formula}Ei may be different from {a mathematical formula}Ej if {a mathematical formula}i≠j. This seems natural: even if people have a common background, they may still disagree on how to interpret certain phenomena or new information. Someone may interpret a smile as just a sign of friendliness; someone else may interpret it as a “false” smile, concealing contempt; yet another person may interpret it as a sign of sexual interest.
     </paragraph>
     <paragraph>
      To model this formally, we can use a straightforward approach already used in [4], [5]: formulas are interpreted relative to a player. But once we allow such ambiguity, further subtleties arise. Returning to the announcement p, not only can it be interpreted differently by different players, it may not even occur to the players that others may interpret the announcement in a different way. Thus, for example, i may believe that {a mathematical formula}Ei is common knowledge. The assumption that each player believes that her interpretation is how everyone interprets the announcement is but one assumption we can make about ambiguity. It is also possible that player i may be aware that there is more than one interpretation of p, but believes that player j is aware of only one interpretation. For example, think of a politician making an ambiguous statement which he realizes that different constituencies will interpret differently, but will not realize that there are other possible interpretations. In this paper, we investigate a number of different semantics of ambiguity that correspond to some standard assumptions that people make with regard to ambiguous statements, and investigate their relationship.
     </paragraph>
     <paragraph>
      Our interest in ambiguity was originally motivated by a seminal result in game theory: Aumann's [1] theorem showing that players cannot “agree to disagree.” More precisely, this theorem says that agents with a common prior on a state space cannot have common knowledge that they have different posteriors. This result has been viewed as paradoxical in the economics literature. Trade in a stock market seems to require common knowledge of disagreement (about the value of the stock being traded), yet we clearly observe a great deal of trading. One well-known explanation for the disagreement is that we do not in fact have common priors: agents start out with different beliefs. In a companion paper [6], we provide a different explanation, in terms of ambiguity. It is easy to show that we can agree to disagree when there is ambiguity, even if there is a common prior.
     </paragraph>
     <paragraph>
      Although our work is motivated by applications in economics, ambiguity has long been a concern in philosophy, linguistics, and natural language processing. For example, there has been a great deal of work on word-sense disambiguation (i.e., trying to decide from context which of the multiple meanings of a word are intended); see [7] for a seminal contribution, and [11] for a recent survey. However, there does not seem to be much work on incorporating ambiguity into a logic. Apart from the literature on the logic of context and on underspecification (see [13]), the only papers that we are aware of that do this are the ones by Monz [10] and Kuijer [8]. Monz allows for statements that have multiple interpretations, just as we do. But rather than incorporating the ambiguity directly into the logic, he considers updates by ambiguous statements.
     </paragraph>
     <paragraph>
      Kuijer models the fact that ambiguous statements can have multiple meanings by using a nondeterministic propositional logic, which, roughly speaking, allows him to consider all the meanings simultaneously. He then defines a notion of implication such that an ambiguous statement A entails another ambiguous statement B if and only if every possible interpretations of A entails every possible interpretation of B. This idea of considering all possible interpretations of an ambiguous statement actually has a long tradition in the philosophy literature. For example, Lewis [9] considers assigning truth values to an ambiguous formula ϕ by considering all possible disambiguations of ϕ. This leads to a semantics where a formula can, for example, have the truth value {a mathematical formula}{true,false}. Lewis views this as a potential justification for relevance logic (a logic where a formula can be true, false, both, or neither; cf. [12]). Our approach is somewhat different. We assume that each agent uses only one interpretation of a given ambiguous formula ϕ, but an agent may consider it possible that another agent interprets ϕ differently. In our applications, this seems to be the most appropriate way to dealing with ambiguity (especially when it comes to considering the strategic implications of ambiguity).
     </paragraph>
     <paragraph>
      There are also connections between ambiguity and vagueness. Although the two notions are different—a term is vague if it is not clear what its meaning is, and is ambiguous if it can have multiple meanings, Halpern [5] also used agent-dependent interpretations in his model of vagueness, although the issues that arose were quite different from those that concern us here.
     </paragraph>
     <paragraph>
      Given the widespread interest in ambiguity, in this paper we focus on the logic of ambiguity. We introduce the logic in Section 2. The rest of the paper is devoted to arguing that, in some sense, ambiguity is not necessary. In Section 3, we show that a formula is satisfiable in a structure with ambiguity (i.e., one where different agents interpret formulas differently) if and only if it is satisfiable in a structure without ambiguity. Then in Section 4, we show that, by extending the language so that we can talk explicitly about how agents interpret formulas, we do not need structures with ambiguity. Despite that, we argue in Section 5 that we it is useful to be able to model ambiguity directly, rather than indirectly.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Syntax and semantics
     </section-title>
     <section label="2.1">
      <section-title>
       Syntax
      </section-title>
      <paragraph>
       We want a logic where players use a fixed common language, but each player may interpret formulas in the language differently. Although we do not need probability for the points we want to make in this paper, for the applications that we have in mind it is also important for the agents to be able to reason about their probabilistic beliefs. Thus, we take as our base logic a propositional logic for reasoning about probability.
      </paragraph>
      <paragraph>
       The syntax of the logic is straightforward (and is, indeed, essentially the syntax already used in papers going back to [2]). There is a finite, nonempty set {a mathematical formula}N={1,…,n} of players, and a countable, nonempty set Φ of primitive propositions. Let {a mathematical formula}LnC(Φ) be the set of formulas that can be constructed starting from Φ, and closing off under conjunction, negation, the modal operators {a mathematical formula}{CBG}G⊆N,G≠∅, and the formation of probability formulas. (We omit the Φ if it is irrelevant or clear from context.) Probability formulas are constructed as follows. If {a mathematical formula}φ1,…,φk are formulas, and {a mathematical formula}a1,…,ak,b∈Q, then for {a mathematical formula}i∈N,{a mathematical formula} is a probability formula, where {a mathematical formula}pri(φ) denotes the probability that player i assigns to a formula φ. Note that this syntax allows for nested probability formulas. We use the abbreviation {a mathematical formula}Biφ for {a mathematical formula}pri(φ)=1, {a mathematical formula}EBG1φ for {a mathematical formula}∧i∈GBiφ, and {a mathematical formula}EBGm+1φ for {a mathematical formula}EBGmEBG1φ for {a mathematical formula}m=1,2… . Finally, we take true to be the abbreviation for a fixed tautology such as {a mathematical formula}p∨¬p.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Epistemic probability structures
      </section-title>
      <paragraph>
       There are standard approaches for interpreting this language [2], but they all assume that there is no ambiguity, that is, that all players interpret the primitive propositions the same way. To allow for different interpretations, we use an approach used earlier [5], [4]: formulas are interpreted relative to a player.
      </paragraph>
      <paragraph>
       An (epistemic probability) structure (over Φ) has the form{a mathematical formula} where Ω is the state space, and for each {a mathematical formula}i∈N, {a mathematical formula}Πi is a partition of Ω, {a mathematical formula}Pi is a function that assigns to each {a mathematical formula}ω∈Ω a probability space {a mathematical formula}Pi(ω)=(Ωi,ω,Fi,ω,μi,ω), and {a mathematical formula}πi is an interpretation that associates with each state a truth assignment to the primitive propositions in Φ. That is, {a mathematical formula}πi(ω)(p)∈{true,false} for all ω and each primitive proposition p. Intuitively, {a mathematical formula}πi describes player i's interpretation of the primitive propositions. Standard models use only a single interpretation π; this is equivalent in our framework to assuming that {a mathematical formula}π1=⋯=πn. We call a structure where {a mathematical formula}π1=⋯=πn a common-interpretation structure; we call a structure where {a mathematical formula}πi≠πj for some agents i and j a structure with ambiguity. Denote by {a mathematical formula}[[p]]i the set of states where i assigns the value true to p. The partitions {a mathematical formula}Πi are called information partitions. While it is more standard in the philosophy and computer science literature to use models where there is a binary relation {a mathematical formula}Ki on Ω for each agent i that describes i's accessibility relation on states, we follow the common approach in economics of working with information partitions here, as that makes it particularly easy to define a player's probabilistic beliefs. Assuming information partitions corresponds to the case that {a mathematical formula}Ki is an equivalence relation (and thus defines a partition). The intuition is that a cell in the partition {a mathematical formula}Πi is defined by some information that i received, such as signals or observations of the world. Intuitively, agent i receives the same information at each state in a cell of {a mathematical formula}Πi. Let {a mathematical formula}Πi(ω) denote the cell of the partition {a mathematical formula}Πi containing ω. Finally, the probability space {a mathematical formula}Pi(ω)=(Ωi,ω,Fi,ω,μi,ω) describes the beliefs of player i at state ω, with {a mathematical formula}μi,ω a probability measure defined on the subspace {a mathematical formula}Ωi,ω of the state space Ω. The σ-algebra {a mathematical formula}Fi,ω consists of the subsets of {a mathematical formula}Ωi,ω to which {a mathematical formula}μi,ω can assign a probability. (If {a mathematical formula}Ωi,ω is finite, we typically take {a mathematical formula}Fi,ω=2Ωi,ω, the set of all subsets of {a mathematical formula}Ωi,ω.) The interpretation is that {a mathematical formula}μi,ω(E) is the probability that i assigns to event {a mathematical formula}E∈Fi,ω in state ω.
      </paragraph>
      <paragraph>
       Throughout this paper, we make the following assumptions regarding the probability assignments {a mathematical formula}Pi, {a mathematical formula}i∈N:
      </paragraph>
      <list>
       <list-item label="A1.">
        For all {a mathematical formula}ω∈Ω, {a mathematical formula}Ωi,ω=Πi(ω).
       </list-item>
       <list-item label="A2.">
        For all {a mathematical formula}ω∈Ω, if {a mathematical formula}ω′∈Πi(ω), then {a mathematical formula}Pi(ω′)=Pi(ω).
       </list-item>
       <list-item label="A3.">
        For all {a mathematical formula}j∈N,ω,ω′∈Ω, {a mathematical formula}Πi(ω)∩Πj(ω′)∈Fi,ω.
       </list-item>
      </list>
      <paragraph>
       Furthermore, we make the following joint assumption on players' interpretations and information partitions:
      </paragraph>
      <list>
       <list-item label="A4.">
        For all {a mathematical formula}ω∈Ω, {a mathematical formula}i∈N, and primitive proposition {a mathematical formula}p∈Φ, {a mathematical formula}Πi(ω)∩[[p]]i∈Fi,ω.
       </list-item>
      </list>
      <paragraph>
       These are all standard assumptions. A1 says that the set of states to which player i assigns probability at state ω is just the set {a mathematical formula}Πi(ω) of worlds that i considers possible at state ω. A2 says that the probability space used is the same at all the worlds in a cell of player i's partition. Intuitively, this says that player i knows his probability space. Informally, A3 says that player i can assign a probability to each of j's cells, given his information. A4 says that primitive propositions (as interpreted by player i) are measurable according to player i.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Prior-generated beliefs
      </section-title>
      <paragraph>
       One assumption that we do not necessarily make, but want to examine in this framework, is the common-prior assumption. The common-prior assumption is an instance of a more general assumption, that beliefs are generated from a prior, which we now define. The intuition is that players start with a prior probability; they then update the prior in light of their information. Player i's information is captured by her partition {a mathematical formula}Πi. Thus, if i's prior is {a mathematical formula}νi, then we would expect {a mathematical formula}μi,ω to be {a mathematical formula}νi(⋅|Πi(ω)).
      </paragraph>
      <paragraph label="Definition 2.1">
       An epistemic probability structure {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,(πj)j∈N) has prior-generated beliefs (generated by{a mathematical formula}(F1,ν1),…,(Fn,νn)) if, for each player i, there exist probability spaces {a mathematical formula}(Ω,Fi,νi) such that
      </paragraph>
      <list>
       <list-item label="•">
        for all {a mathematical formula}i,j∈N and {a mathematical formula}ω∈Ω, {a mathematical formula}Πj(ω)∈Fi;
       </list-item>
       <list-item label="•">
        for all {a mathematical formula}i∈N and {a mathematical formula}ω∈Ω, {a mathematical formula}Pi(ω)=(Πi(ω),Fi|Πi(ω),μi,ω), where {a mathematical formula}Fi|Πi(ω) is the restriction of {a mathematical formula}Fi to {a mathematical formula}Πi(ω),{sup:1} and {a mathematical formula}μi,ω(E)=νi(E|Πi(ω)) for all {a mathematical formula}E∈Fi|Πi(ω) if {a mathematical formula}νi(Πi(ω))&gt;0. (There are no constraints on {a mathematical formula}νi,ω if {a mathematical formula}νi(Πi(ω))=0.)
       </list-item>
      </list>
      <paragraph>
       It is easy to check that if M has prior-generated beliefs, then M satisfies A1, A2, and A3. More interestingly for our purposes, the converse also holds for a large class of structures. Say that a structure is countably partitioned if for each player i, the information partition {a mathematical formula}Πi has countably many elements, i.e., {a mathematical formula}Πi is a finite or countably infinite collection of subsets of Ω.
      </paragraph>
      <paragraph label="Proposition 2.2">
       If a structure M has prior-generated beliefs, then M satisfies A1, A2, and A3. Moreover, every countably partitioned structure that satisfies A1, A2, and A3 is one with prior-generated beliefs, with the priors{a mathematical formula}νisatisfying{a mathematical formula}νi(Πi(ω))&gt;0for each player{a mathematical formula}i∈Nand state{a mathematical formula}ω∈Ω.
      </paragraph>
      <paragraph label="Proof">
       The first part is immediate. To prove the second claim, suppose that M is a structure satisfying A1–A3. Let {a mathematical formula}Fi be the unique algebra generated by {a mathematical formula}∪ω∈ΩFi,ω. To define {a mathematical formula}νi, if there are {a mathematical formula}Ni&lt;∞ cells in the partition {a mathematical formula}Πi, define {a mathematical formula}νi(ω)=1Niμi,ω(ω). Otherwise, if the collection {a mathematical formula}Πi is countably infinite, order the elements of {a mathematical formula}Πi as {a mathematical formula}pi1,pi2,… . Choose some state {a mathematical formula}ωk∈pik for each k, with associated probability space {a mathematical formula}Pi(ωk)=(Ωi,ωk,Fi,ωk,μi,ωk). By A2, each choice of {a mathematical formula}ωk in {a mathematical formula}pik gives the same probability measure {a mathematical formula}μi,ωk. Define {a mathematical formula}νi=∑k12kμi,ωk. It is easy to see that {a mathematical formula}νi is a probability measure on Ω, and that M is generated by {a mathematical formula}(F1,ν1),…,(Fn,νn).  □
      </paragraph>
      <paragraph>
       Note that the requirement that that M is countably partitioned is necessary to ensure that we can have {a mathematical formula}νi(Πi(ω))&gt;0 for each player i and state ω.
      </paragraph>
      <paragraph>
       In light of Proposition 2.2, when it is convenient, we will talk of a structure satisfying A1–A3 as being generated by{a mathematical formula}(F1,ν1),…,(Fn,νn).
      </paragraph>
      <paragraph>
       The common-prior assumption discussed in the introduction is essentially just the special case of prior-generated beliefs where all the priors are identical.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Capturing ambiguity
      </section-title>
      <paragraph>
       We use epistemic probability structures to give meaning to formulas. Since primitive propositions are interpreted relative to players, we must allow the interpretation of arbitrary formulas to depend on the player as well. Exactly how we do this depends on what further assumptions we make about what players know about each other's interpretations. There are many assumptions that could be made. We focus on two of them here, ones that we believe arise in applications of interest, and then reconsider them under the assumption that there may be some ambiguity about the partitions.
      </paragraph>
     </section>
     <section>
      <section>
       <section>
        <section-title>
         Believing there is no ambiguity.
        </section-title>
        <paragraph>
         The first approach is appropriate for situations where players may interpret statements differently, but it does not occur to them that there is another way of interpreting the statement. Thus, in this model, if there is a public announcement, all players will think that their interpretation of the announcement is common knowledge. We write {a mathematical formula}(M,ω,i)⊨outφ to denote that φ is true at state ω according to player i (that is, according to i's interpretation of the primitive propositions in φ). The superscript out denotes outermost scope, since the formulas are interpreted relative to the “outermost” player, namely the player i on the left-hand side of {a mathematical formula}⊨out. We define {a mathematical formula}⊨out, as usual, by induction.
        </paragraph>
        <paragraph>
         If p is a primitive proposition,{a mathematical formula} This just says that player i interprets a primitive proposition p according to his interpretation function {a mathematical formula}πi. This clause is common to all our approaches for dealing with ambiguity.
        </paragraph>
        <paragraph>
         For conjunction and negation, as is standard,{a mathematical formula}{a mathematical formula}
        </paragraph>
        <paragraph>
         Now consider a probability formula of the form {a mathematical formula}a1prj(φ1)+⋯+akprj(φk)⩾b. The key feature that distinguishes this semantics is how i interprets j's beliefs. This is where we capture the intuition that it does not occur to i that there is another way of interpreting the formulas other than the way she does. Let{a mathematical formula} Thus, {a mathematical formula}[[φ]]iout is the event consisting of the set of states where φ is true, according to i. Note that A1 and A3 guarantee that the restriction of {a mathematical formula}Ωj,ω to {a mathematical formula}Πi(ω) belongs to {a mathematical formula}Fi,ω. Assume inductively that {a mathematical formula}[[φ1]]iout∩Ωj,ω,…,[[φk]]iout∩Ωj,ω∈Fj,ω. The base case of this induction, where φ is a primitive proposition, is immediate from A3 and A4, and the induction assumption clearly extends to negations and conjunctions. We now define{a mathematical formula} Note that it easily follows from A2 that {a mathematical formula}(M,ω,i)⊨outa1prj(φ1)+⋯+akprj(φk)⩾b if and only if {a mathematical formula}(M,ω′,i)⊨outa1prj(φ1)+⋯+akprj(φk)⩾b for all {a mathematical formula}ω′∈Πj(ω). Thus, {a mathematical formula}[[a1prj(φ1)+⋯+akprj(φk)⩾b]]i is a union of cells of {a mathematical formula}Πj, and hence {a mathematical formula}[[a1prj(φ1)+⋯+akprj(φk)⩾b]]i∩Ωj,ω∈Fj,ω.
        </paragraph>
        <paragraph>
         With this semantics, according to player i, player j assigns φ probability b if and only if the set of worlds where φ holds according to i has probability b according to j. Intuitively, although i “understands” j's probability space, player i is not aware that j may interpret φ differently from the way she (i) does. That i understands j's probability space is plausible if we assume that there is a common prior and that i knows j's partition (this knowledge is embodied in the assumption that i intersects {a mathematical formula}[[φk]]iout with {a mathematical formula}Ωj,ω when assessing what probability j assigns to {a mathematical formula}φk).{sup:2}
        </paragraph>
        <paragraph>
         Given our interpretation of probability formulas, the interpretation of {a mathematical formula}Bjφ and {a mathematical formula}EBkφ follows. For example,{a mathematical formula} For readers more used to belief defined in terms of a possibility relation, note that if the probability measure {a mathematical formula}μj,ω is discrete (i.e., all sets are {a mathematical formula}μj,ω-measurable, and {a mathematical formula}μj,ω(E)=∑ω′∈Eμj,ω(ω′) for all subsets {a mathematical formula}E⊂Πj(ω)), we can define {a mathematical formula}Bj={(ω,ω′):μj,ω(ω′)&gt;0}; that is, {a mathematical formula}(ω,ω′)∈Bj if, in state ω, agent j gives state {a mathematical formula}ω′ positive probability. In that case, {a mathematical formula}(M,ω,i)⊨outBjφ iff {a mathematical formula}(M,ω′,i)⊨outφ for all {a mathematical formula}ω′ such that {a mathematical formula}(ω,ω′)∈Bj. That is, {a mathematical formula}(M,ω,i)⊨outBjφ iff φ is true according to i in all the worlds to which j assigns positive probability at ω.
        </paragraph>
        <paragraph>
         It is important to note that {a mathematical formula}(M,ω,i)⊨φ does not imply {a mathematical formula}(M,ω,i)⊨Biφ: while {a mathematical formula}(M,ω,i)⊨outφ means “φ is true at ω according to i's interpretation,” this does not mean that i believes φ at state ω. The reason is that i can be uncertain as to which state is the actual state. For i to believe φ at ω, φ would have to be true (according to i's interpretation) at all states to which i assigns positive probability.
        </paragraph>
        <paragraph>
         Finally, we define{a mathematical formula} for any nonempty subset {a mathematical formula}G⊆N of players.
        </paragraph>
       </section>
       <section>
        <section-title>
         Awareness of possible ambiguity.
        </section-title>
        <paragraph>
         We now consider the second way of interpreting formulas. This is appropriate for players who realize that other players may interpret formulas differently. We write {a mathematical formula}(M,ω,i)⊨inφ to denote that φ is true at state ω according to player i using this interpretation, which is called innermost scope. The definition of {a mathematical formula}⊨in is identical to that of {a mathematical formula}⊨out except for the interpretation of probability formulas. In this case, we have{a mathematical formula} where {a mathematical formula}[[φ]]jin is the set of states ω such that {a mathematical formula}(M,ω,j)⊨inφ. Hence, according to player i, player j assigns φ probability b if and only if the set of worlds where φ holds according to j has probability b according to j. Intuitively, now i realizes that j may interpret φ differently from the way that she (i) does, and thus assumes that j uses his (j's) interpretation to evaluate the probability of φ. Again, in the case that {a mathematical formula}μj,ω is discrete, this means that {a mathematical formula}(M,ω,i)⊨inBjφ iff {a mathematical formula}(M,ω′,j)⊨inφ for all {a mathematical formula}ω′ such that {a mathematical formula}(ω,ω′)∈Bj.
        </paragraph>
        <paragraph>
         Note for future reference that if φ is a probability formula or a formula of the form {a mathematical formula}CBGφ′, then it is easy to see that {a mathematical formula}(M,ω,i)⊨inφ if and only if {a mathematical formula}(M,ω,j)⊨inφ; we sometimes write {a mathematical formula}(M,ω)⊨inφ in this case. Clearly, {a mathematical formula}⊨out and {a mathematical formula}⊨in agree in the common-interpretation case, and we can write ⊨. There is a sense in which innermost scope is able to capture the intuitions behind outermost scope. Specifically, we can capture the intuition that player i is convinced that all players interpret everything just as he (i) does by assuming that in all worlds {a mathematical formula}ω′ that player i considers possible, {a mathematical formula}πi(ω′)=πj(ω′) for all players j.
        </paragraph>
       </section>
       <section>
        <section-title>
         Ambiguity about information partitions.
        </section-title>
        <paragraph>
         Up to now, we have assumed that players “understand” each other's probability spaces. This may not be so reasonable in the presence of ambiguity and prior-generated beliefs. We want to model the following type of situation. Players receive information, or signals, about the true state of the world, in the form of strings (formulas). Each player understands what signals he and other players receive in different states of the world, but players may interpret signals differently. For instance, player i may understand that j sees a red car if ω is the true state of the world, but i may or may not be aware that j has a different interpretation of “red” than i does. In the latter case, i does not have a full understanding of j's information structure.
        </paragraph>
        <paragraph>
         We would like to think of a player's information as being characterized by a formula (intuitively, the formula that describes the signals received). Even if the formulas that describe each information set are commonly known, in the presence of ambiguity, they might be interpreted differently.
        </paragraph>
        <paragraph>
         To make this precise, let {a mathematical formula}Φ⁎ be the set of formulas that is obtained from Φ by closing off under negation and conjunction. That is, {a mathematical formula}Φ⁎ consists of all propositional formulas that can be formed from the primitive propositions in Φ. Since the formulas in {a mathematical formula}Φ⁎ are not composed of probability formulas, and thus do not involve any reasoning about interpretations, we can extend the function {a mathematical formula}πi(⋅) to {a mathematical formula}Φ⁎ in a straightforward way, and write {a mathematical formula}[[φ]]i for the set of the states of the world where the formula {a mathematical formula}φ∈Φ⁎ is true according to i.
        </paragraph>
        <paragraph>
         The key new assumption that we make to model players' imperfect understanding of the other players' probability spaces is that i's partition cell at ω is described by a formula {a mathematical formula}φi,ω∈Φ⁎. Roughly speaking, this means that {a mathematical formula}Πi(ω) should consist of all states where the formula {a mathematical formula}φi,ω is true. More precisely, we take {a mathematical formula}Πi(ω) to consist of all states where {a mathematical formula}ϕi,ω is true according to i. If player j understands that i may be using a different interpretation than he does (i.e., the appropriate semantics are the innermost-scope semantics), then j correctly infers that the set of states that i thinks are possible in ω is {a mathematical formula}Πi(ω)=[[φi,ω]]i. But if j does not understand that i may interpret formulas in a different way (i.e., under outermost scope), then he thinks that the set of states that i thinks are possible in ω is given by {a mathematical formula}[[φi,ω]]j. Of course, {a mathematical formula}[[φi,ω]]j does not in general coincide with {a mathematical formula}Πi(ω). Indeed, {a mathematical formula}[[φi,ω]]j may even be empty. If this happens, j might well wonder if i is interpreting things the same way that he (j) is. In any case, we require that j understand that these formulas form a partition and that ω belongs to {a mathematical formula}[[φi,ω]]j. Thus, we consider structures that satisfy A1–A5, and possibly A6 (when we use outermost scope semantics).
        </paragraph>
        <list>
         <list-item label="A5.">
          For each {a mathematical formula}i∈N and {a mathematical formula}ω∈Ω, there is a formula {a mathematical formula}φi,ω∈Φ⁎ such that {a mathematical formula}Πi(ω)=[[φi,ω]]i.
         </list-item>
         <list-item label="A6.">
          For each {a mathematical formula}i,j∈N, the collection {a mathematical formula}{[[φi,ω]]j:ω∈Ω} is a partition of Ω and for all {a mathematical formula}ω∈Ω, {a mathematical formula}ω∈[[φi,ω]]j.
         </list-item>
        </list>
        <paragraph>
         Assumption A6 ensure that the signals for player i define an information partition according to every player j when we consider the outermost scope semantics. With innermost scope, this already follows from A5 and the definition of {a mathematical formula}Πi(ω).
        </paragraph>
        <paragraph>
         We can now define analogues of outermost scope and innermost scope in the presence of ambiguous information. Thus, we define two more truth relations, {a mathematical formula}⊨out,ai and {a mathematical formula}⊨in,ai. (The “ai” here stands for “ambiguity of information”.) The only difference between {a mathematical formula}⊨out,ai and {a mathematical formula}⊨out is in the semantics of probability formulas. In giving the semantics in a structure M, we assume that M has prior-generated beliefs, generated by {a mathematical formula}(F1,ν1),…,(Fn,νn). As we observed in Proposition 2.2, this assumption is without loss of generality as long as the structure is countably partitioned. However, the choice of prior beliefs is relevant, as we shall see, so we have to be explicit about them. When i evaluates j's probability at a state ω, instead of using {a mathematical formula}μj,ω, player i uses {a mathematical formula}νj(⋅|[[φj,ω]]i). When {a mathematical formula}i=j, these two approaches agree, but in general they do not. Thus, assuming that M satisfies A5 and A6 (which are the appropriate assumptions for the outermost-scope semantics), we have{a mathematical formula} where {a mathematical formula}[[ψ]]iout,ai={ω′:(M,ω,i)⊨out,aiψ}.
        </paragraph>
        <paragraph>
         That is, at {a mathematical formula}ω∈Ω, player j receives the information (a string) {a mathematical formula}φj,ω, which he interprets as {a mathematical formula}[[φj,ω]]j. Player i understands that j receives the information {a mathematical formula}φj,ω in state ω, but interprets this as {a mathematical formula}[[φj,ω]]i. This models a situation such as the following. In state ω, player j sees a red car, and thinks possible all states of the world where he sees a car that is red (according to j). Player i knows that at world ω player j will see a red car (although she may not know that the actual world is ω, and thus does not know what color of car player j actually sees). However, i has a somewhat different interpretation of “red car” (or, more precisely, of j seeing a red car) than j; i's interpretation corresponds to the event {a mathematical formula}[[φj,ω]]i. Since i understands that j's beliefs are determined by conditioning her prior {a mathematical formula}νj on her information, i can compute what she believes j's beliefs are.
        </paragraph>
        <paragraph>
         We can define {a mathematical formula}⊨in,ai in an analogous way. Thus, the semantics for formulas that do not involve probability formulas are as given by {a mathematical formula}⊨in, while the semantics of probability formulas is defined as follows (where M is assumed to satisfy A5, which is the appropriate assumption for the innermost-scope semantics):{a mathematical formula} Note that although we have written {a mathematical formula}[[φj,ω]]iin,ai, since {a mathematical formula}φj,ω is a propositional formula, {a mathematical formula}[[φj,ω]]iin,ai=[[φj,ω]]iout,ai=[[φj,ω]]iout=[[φj,ω]]iin. It is important that {a mathematical formula}φj,ω is a propositional formula here; otherwise, we would have circularities in the definition, and would somehow need to define {a mathematical formula}[[φj,ω]]iin,ai.
        </paragraph>
        <paragraph>
         Again, here it may be instructive to consider the definition of {a mathematical formula}Bjφ in the case that {a mathematical formula}μj,ω is discrete for all ω. In this case, {a mathematical formula}Bj becomes the set {a mathematical formula}{(ω,ω′):νj(ω′|[[φj,ω]]jin,ai)&gt;0. That is, state {a mathematical formula}ω′ is considered possible by player j in state ω if agent j gives {a mathematical formula}ω′ positive probability after conditioning his prior {a mathematical formula}νj on (his interpretation of) the information {a mathematical formula}φj,ω he receives in state ω. With this definition of {a mathematical formula}Bj, we have, as expected, {a mathematical formula}(M,ω,i)⊨in,aiBjφ iff {a mathematical formula}(M,ω′,i)⊨in,aiφ for all {a mathematical formula}ω′ such that {a mathematical formula}(ω,ω′)∈Bj.
        </paragraph>
        <paragraph>
         The differences in the different semantics arise only when we consider probability formulas. If we go back to our example with the red car, we now have a situation where player j sees a red car in state ω, and thinks possible all states where he sees a red car. Player i knows that in state ω, player j sees a car that he (j) interprets to be red, and that this determines his posterior. Since i understands j's notion of seeing a red car, she has a correct perception of j's posterior in each state of the world. Thus, the semantics for {a mathematical formula}⊨in,ai are identical to those for {a mathematical formula}⊨in (restricted to the class of structures with prior-generated beliefs that satisfy A5), though the information partitions are not predefined, but rather generated by the signals.
        </paragraph>
        <paragraph>
         Note that, given an epistemic structure M satisfying A1–A4, there are many choices for {a mathematical formula}νi that allow M to be viewed as being generated by prior beliefs. All that is required of {a mathematical formula}νj is that for all {a mathematical formula}ω∈Ω and {a mathematical formula}E∈Fj,ω such that {a mathematical formula}E⊆[[φj,ω]]jout,ai, it holds that {a mathematical formula}νj(E∩[[φj,ω]]jout,ai)/νj([[φj,ω]]jout,ai)=μj,ω(E). However, because {a mathematical formula}[[φj,ω]]iout,ai may not be a subset of {a mathematical formula}[[φj,ω]]jout,ai=Πj(ω), we can have two prior probabilities {a mathematical formula}νj and {a mathematical formula}νj′ that generate the same posterior beliefs for j, and still have {a mathematical formula}νj([[φk]]iout,ai|[[φj,ω]]iout,ai)≠νj′([[φk]]iout,ai|[[φj,ω]]iout,ai) for some formulas {a mathematical formula}φk. Thus, we must be explicit about our choice of priors here.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Common interpretations suffice
     </section-title>
     <paragraph>
      In this section, we show in there is a sense in which we do not need structures with ambiguity. Specifically, we show that the same formulas are valid in common-interpretation structures as in structures that do not have a common interpretation, no matter what semantics we use, even if we have ambiguity about information partitions.
     </paragraph>
     <paragraph>
      To make this precise, we need some notation. Fix a nonempty, countable set Ψ of primitive propositions, and let {a mathematical formula}M(Ψ) be the class of all structures that satisfy A1–A4 and that are defined over some nonempty subset Φ of Ψ such that {a mathematical formula}Ψ∖Φ is countably infinite.{sup:3} Given a subset Φ of Ψ, a formula {a mathematical formula}φ∈LnC(Φ), and a structure {a mathematical formula}M∈M(Ψ) over Φ, we say that φ is valid in M according to outermost scope, and write {a mathematical formula}M⊨outφ, if {a mathematical formula}(M,ω,i)⊨outφ for all {a mathematical formula}ω∈Ω and {a mathematical formula}i∈N. Given {a mathematical formula}φ∈Ψ, say that φ is valid according to outermost scope in a class {a mathematical formula}N⊆M(Ψ) of structures, and write {a mathematical formula}N⊨outφ, if {a mathematical formula}M⊨outφ for all {a mathematical formula}M∈N defined over a set {a mathematical formula}Φ⊂Ψ of primitive propositions that includes all the primitive propositions that appear in φ.
     </paragraph>
     <paragraph>
      We get analogous definitions by replacing {a mathematical formula}⊨out by {a mathematical formula}⊨in, {a mathematical formula}⊨out,ai and {a mathematical formula}⊨in,ai throughout (in the latter two cases, we have to restrict {a mathematical formula}N to structures that satisfy A5 and A6 or just A5, respectively, in addition to A1–A4). Finally, given a class of structures {a mathematical formula}N, let {a mathematical formula}Nc be the subclass of {a mathematical formula}N in which players have a common interpretation. Thus, {a mathematical formula}Mc(Ψ) denotes the structures in {a mathematical formula}M(Ψ) with a common interpretation. Let {a mathematical formula}Mai(Ψ) denote all structures in {a mathematical formula}M(Ψ) with prior-generated beliefs that satisfy A5 and A6 (where we assume that the prior ν that describes the initial beliefs is given explicitly).{sup:4}
     </paragraph>
     <paragraph label="Theorem 3.1">
      For all formulas{a mathematical formula}φ∈LnC(Ψ), the following are equivalent:
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}Mc(Ψ)⊨φ;
      </list-item>
      <list-item label="(b)">
       {a mathematical formula}M(Ψ)⊨outφ;
      </list-item>
      <list-item label="(c)">
       {a mathematical formula}M(Ψ)⊨inφ;
      </list-item>
      <list-item label="(d)">
       {a mathematical formula}Mcai(Ψ)⊨φ;
      </list-item>
      <list-item label="(e)">
       {a mathematical formula}Mai(Ψ)⊨out,aiφ;
      </list-item>
      <list-item label="(f)">
       {a mathematical formula}Mai(Ψ)⊨in,aiφ.
      </list-item>
     </list>
     <paragraph label="Proof">
      Since the set of structures with a common interpretation is a subset of the set of structures, it is immediate that (c) and (b) both imply (a). Similarly, (e) and (f) both imply (d). The fact that (a) implies (b) is also immediate. For suppose that {a mathematical formula}Mc(Ψ)⊨φ and that {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,(πj)j∈N)∈M(Ψ) is a structure over a set {a mathematical formula}Φ⊂Ψ of primitive propositions that contains the primitive propositions that appear in φ. We must show that {a mathematical formula}M⊨outφ. Thus, we must show that {a mathematical formula}(M,ω,i)⊨outφ for all {a mathematical formula}ω∈Ω and {a mathematical formula}i∈N. Fix {a mathematical formula}ω∈Ω and {a mathematical formula}i∈N, and let {a mathematical formula}Mi′=(Ω,(Πj)j∈N,(Pj)j∈N,(πj′)j∈N), where {a mathematical formula}πj′=πi for all j. Thus, {a mathematical formula}Mi′ is a common-interpretation structure over Φ, where the interpretation coincides with i's interpretation in M. Clearly {a mathematical formula}Mi′ satisfies A1–A4, so {a mathematical formula}Mi′∈Mc(Ψ). It is easy to check that {a mathematical formula}(M,ω,i)⊨outψ if and only if {a mathematical formula}(Mi′,ω,i)⊨ψ for all states {a mathematical formula}ω∈Ω and all formulas {a mathematical formula}ψ∈LnC(Φ). Since {a mathematical formula}Mi′⊨φ, we must have that {a mathematical formula}(M,ω,i)⊨outφ, as desired.To see that (a) implies (c), given a structure {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,(πj)j∈N)∈M(Ψ) over some set {a mathematical formula}Φ⊂Ψ of primitive propositions and a player {a mathematical formula}j∈N, let {a mathematical formula}Ωj be a disjoint copy of Ω; that is, for every state {a mathematical formula}ω∈Ω, there is a corresponding state {a mathematical formula}ωj∈Ωj. Let {a mathematical formula}Ω′=Ω1∪⋯∪Ωn. Given {a mathematical formula}E⊆Ω, let the corresponding subset {a mathematical formula}Ej⊆Ωj be the set {a mathematical formula}{ωj:ω∈E}, and let {a mathematical formula}E′ be the subset of {a mathematical formula}Ω′ corresponding to E, that is, {a mathematical formula}E′={ωj:ω∈E,j∈N}.Define {a mathematical formula}M′=(Ω′,(Πj′)j∈N,(Pj′)j∈N,(πj′)j∈N), where {a mathematical formula}Ω′=Ω1∪⋯∪Ωn and, for all {a mathematical formula}ω∈Ω and {a mathematical formula}i,j∈N, we have
      <list>
       {a mathematical formula}Πi′(ωj)=(Πi(ω))′;{a mathematical formula}πi(ωj)(p)=πj(ω)(p) for a primitive proposition {a mathematical formula}p∈Φ;{a mathematical formula}Pi′(ωj)=(Ωi,ωj′,Fi,ωj′,μi,ωj′), where {a mathematical formula}Ωi,ωj′=Ωi,ω′, {a mathematical formula}Fi,ωj′={Eℓ:E∈Fi,ω,ℓ∈N}, {a mathematical formula}μi,ωj′(Ei)=μi,ω(E), {a mathematical formula}μi,ωj′(Eℓ)=0 if {a mathematical formula}ℓ≠i.Thus,
      </list>
      <paragraph>
       {a mathematical formula}π1=⋯=πn, so that {a mathematical formula}M′ is a common-interpretation structure; on a state {a mathematical formula}ωj, these interpretations are all determined by {a mathematical formula}πj. Also note that the support of the probability measure {a mathematical formula}μi,ωj′ is contained in {a mathematical formula}Ωi, so for different players i, the probability measures {a mathematical formula}μi,ωj′ have disjoint supports. Now an easy induction on the structure of formulas shows that {a mathematical formula}(M′,ωj)⊨ψ if and only if {a mathematical formula}(M,ω,j)⊨inψ for any formula {a mathematical formula}ψ∈LnC(Φ). It easily follows that if {a mathematical formula}M′⊨φ, then {a mathematical formula}M⊨inφ for all {a mathematical formula}φ∈LnC(Φ).The argument that (d) implies (e) is essentially identical to the argument that (a) implies (b); similarly, the argument that (d) implies (f) is essentially the same as the argument that (a) implies (c). Since {a mathematical formula}Mcai(Ψ)⊆Mc(Ψ), (a) implies (d). To show that (d) implies (a), suppose that {a mathematical formula}Mcai(Ψ)⊨φ for some formula {a mathematical formula}φ∈LnC(Ψ). Given a structure {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,π)∈Mc(Ψ) over a set {a mathematical formula}Φ⊂Ψ of primitive propositions that includes the primitive propositions that appear in φ, we want to show that {a mathematical formula}(M,ω,i)⊨φ for each state {a mathematical formula}ω∈Ω and player i. Fix ω. Recall that {a mathematical formula}RN(ω) consists of the set of states N-reachable from ω. Let {a mathematical formula}M′=(RN(ω),(Πj′)j∈N,(Pj′)j∈N,π′), with {a mathematical formula}Πj′ and {a mathematical formula}Pj′ the restriction of {a mathematical formula}Πj and {a mathematical formula}Pj, respectively, to the states in {a mathematical formula}RN(ω), be a structure over a set {a mathematical formula}Φ′ of primitive propositions, where {a mathematical formula}Φ′ contains Φ and new primitive propositions that we call {a mathematical formula}pi,ω for each player i and state {a mathematical formula}ω∈RN(ω).{sup:5} Note that there are only countably many information sets in {a mathematical formula}RN(ω), so {a mathematical formula}Φ′ is countable. Define {a mathematical formula}π′ so that it agrees with π (restricted to {a mathematical formula}RN(ω)) on the propositions in Φ, and so that {a mathematical formula}[[pi,ω]]i=Πi(ω). Thus, {a mathematical formula}M′ satisfies A5 and A6. It is easy to check that, for all {a mathematical formula}ω′∈RN(ω) and all formulas {a mathematical formula}ψ∈LnC(Φ), we have that {a mathematical formula}(M,ω′,i)⊨ψ iff {a mathematical formula}(M′,ω′,i)⊨ψ. Since {a mathematical formula}M′⊨φ, it follows that {a mathematical formula}(M,ω,i)⊨φ, as desired.  □
      </paragraph>
     </paragraph>
     <paragraph>
      From Theorem 3.1 it follows that for formulas in {a mathematical formula}LnC(Ψ), we can get the same axiomatization with respect to structures in {a mathematical formula}M(Ψ) for both the {a mathematical formula}⊨out and {a mathematical formula}⊨in semantics; moreover, this axiomatization is the same as that for the common-interpretation case. An axiomatization for this case is already given in [2]; there is also a complete characterization of the complexity of determining whether a formula is valid.
     </paragraph>
     <paragraph>
      However, the equivalence in Theorem 3.1 does not extend to subclasses of {a mathematical formula}M, {a mathematical formula}Mc, and {a mathematical formula}Mai. As shown in our companion paper [6], the equivalence result does not hold if we consider the innermost scope semantics and restrict attention to the subclasses of {a mathematical formula}M and {a mathematical formula}Mc that satisfy the common-prior assumption. We defer a further discussion of the modeling implications of this result to Section 5.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      A more general language
     </section-title>
     <paragraph>
      Although, when considering innermost scope, we allowed for agents that were sophisticated enough to realize that different agents might interpret things in different ways, our syntax did not reflect that sophistication. Specifically, the language does not allow the modeler (or the agents) to reason about how other agents interpret formulas. Here we consider a language that is rich enough to allow this. Specifically, we have primitive propositions of the form {a mathematical formula}(p,i), that can be interpreted as “i's interpretation of p.” With this extended language, we do not need to have a different interpretation function {a mathematical formula}πi for each i; it suffices in a precise sense to use a single (common) interpretation function. We now make this precise, and show that this approach is general enough to capture both outermost and innermost scope.
     </paragraph>
     <paragraph>
      More precisely, we consider the same syntax as in Section 2.1, with the requirement that the set Φ of primitive propositions have the form {a mathematical formula}Φ′×N, for some set {a mathematical formula}Φ′; that is, primitive propositions have the form {a mathematical formula}(p,i) for some {a mathematical formula}p∈Φ′ and some agent {a mathematical formula}i∈N. We interpret these formulas using a standard epistemic probability structure {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,π), with a common interpretation π, as in [2]. Thus, truth is no longer agent-dependent, so we have only {a mathematical formula}(M,ω) on the left-hand side of ⊨, not {a mathematical formula}(M,ω,i). In particular, if {a mathematical formula}(p,i) is a primitive proposition,{a mathematical formula} As expected, we have{a mathematical formula} We no longer need to write {a mathematical formula}[[φj]]iou or {a mathematical formula}[[φj]]iin, since all agents interpret all formulas the same way.
     </paragraph>
     <paragraph>
      We now show how we can capture innermost and outermost scope using this semantics. Specifically, suppose that we start with an epistemic probability structure {a mathematical formula}M=(Ω,(Πj)j∈N,(Pj)j∈N,(πj)j∈N) over some set Φ of primitive propositions. Consider the corresponding common-interpretation structure {a mathematical formula}Mc=(Ω,(Πj)j∈N,(Pj)j∈N,π) over {a mathematical formula}Φ×N, where {a mathematical formula}π(ω)(p,i)=πi(ω)(p). Thus, M and {a mathematical formula}Mc are identical except in the primitive propositions that they interpret, and how they interpret them. In {a mathematical formula}Mc, the primitive proposition {a mathematical formula}(p,i)∈Φ×N is interpreted the same way that i interprets p in M.
     </paragraph>
     <paragraph>
      We can now define, for each formula ϕ, two formulas {a mathematical formula}ϕiin and {a mathematical formula}ϕiout with the property that {a mathematical formula}(M,ω,i)⊨inϕ iff {a mathematical formula}(Mc,ω)⊨ϕiin and {a mathematical formula}(M,ω,i)⊨outϕ iff {a mathematical formula}(Mc,ω)⊨ϕiout. We start with {a mathematical formula}ϕiin, defining it by induction on structure:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}piin=(p,i)
      </list-item>
      <list-item label="•">
       {a mathematical formula}(ψ∧ψ′)iin=ψiin∧(ψi′)in
      </list-item>
      <list-item label="•">
       {a mathematical formula}(a1prj(φ1)+⋯+akprj(φk)⩾b)iin=a1prj((φ1)jin)+⋯+akprj((φk)jin)⩾b
      </list-item>
      <list-item label="•">
       {a mathematical formula}(CBGψ)iin=CBG(∧j∈GBjψjin).
      </list-item>
     </list>
     <paragraph>
      Note that {a mathematical formula}ϕiin is independent of i if ϕ is a probability formula or of the form {a mathematical formula}CBGψ. This is to be expected, since, as we have seen, with innermost scope, the semantics of such formulas is independent of i. The definition of {a mathematical formula}(CBGψ)iin is perhaps the only somewhat surprising clause here; as we discuss after the proof of Theorem 4.1 below, the more natural definition, {a mathematical formula}(CBGψ)iin=CBG(ψiin), does not work.
     </paragraph>
     <paragraph>
      For outermost scope, the first two clauses of the translation are identical to those above; the latter two change as required for outermost scope. Thus, we get
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}piout=(p,i)
      </list-item>
      <list-item label="•">
       {a mathematical formula}(ψ∧ψ′)iout=ψiout∧(ψi′)out
      </list-item>
      <list-item label="•">
       {a mathematical formula}(a1prj(φ1)+⋯+akprj(φk)⩾b)iout=a1prj((φ1)iout)+⋯+akprj((φk)iout)⩾b
      </list-item>
      <list-item label="•">
       {a mathematical formula}(CBGψ)iout=CBG(ψiout).
      </list-item>
     </list>
     <paragraph>
      Interestingly, here the natural definition of {a mathematical formula}(CBGψ)iout does work.
     </paragraph>
     <paragraph label="Theorem 4.1">
      If M is a probabilistic epistemic structure over Φ and{a mathematical formula}Mcis the corresponding common-interpretation structure over{a mathematical formula}Φ×N, then
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}(M,ω,i)⊨inϕiff{a mathematical formula}(Mc,ω)⊨ϕiin;
      </list-item>
      <list-item label="(b)">
       {a mathematical formula}(M,ω,i)⊨outϕiff{a mathematical formula}(Mc,ω)⊨ϕiout.
      </list-item>
     </list>
     <paragraph label="Proof">
      We prove the result by induction on the structure of ϕ. The argument for outermost scope is completely straightforward, and left to the reader. The argument for innermost scope is also straightforward, except for the case that ϕ has the form {a mathematical formula}CBGψ. We now consider this case carefully.By definition,{a mathematical formula} Note that, by definition, {a mathematical formula}(EBGψ)iin=∧j∈GBjψjin. Thus, by the induction hypothesis, it follows that{a mathematical formula} Now by a straightforward induction on k, we can show that{a mathematical formula} That is,{a mathematical formula}It immediately follows from (1) that if {a mathematical formula}(M,ω,i)⊨inCBGψ, then {a mathematical formula}(Mc,ω)⊨CB(∧j∈GBjψjin). The converse also follows from (1), once we show that {a mathematical formula}(M,ω,i)⊨inEBG2ψ implies {a mathematical formula}(M,ω,i)⊨inEBGψ. But this too follows easily since{a mathematical formula} This completes the argument.  □
     </paragraph>
     <paragraph>
      To see why we need we need the more complicated definition of {a mathematical formula}(CBGψ)iin, it is perhaps best to consider an example. By definition, {a mathematical formula}(CB{1,2}p)1in=CB{1,2}(B1(p,1)∧B2(p,2)). By way of contrast, {a mathematical formula}CB{1,2}(p1in)=CB{1,2}(p,1), which (using arguments similar in spirit to those used above) can be shown to be equivalent to {a mathematical formula}CB{1,2}(B1(p,1)∧B2(p,1)). They key point here is whether we have {a mathematical formula}B2(p,1) or {a mathematical formula}B2(p,2). We want the latter, which is what we get from the more complicated translation that we use; it is easy to show that the former does not give the desired result. These issues do not arise with outermost scope.
     </paragraph>
     <paragraph>
      Theorem 4.1 shows that, from a modeler's point of view, there is no loss in working with common-interpretations structures. Any structure that uses ambiguous propositions can be converted to one that uses unambiguous propositions of the form {a mathematical formula}(p,i). In a sense, this can be viewed as a strengthening of Theorem 3.1. Theorem 3.1 says that any formula that is satisfiable using innermost or outermost semantics in the presence of ambiguity is also satisfiable in a common-interpretation structure. However, that common-interpretation structure might be quite different from the original structure. Theorem 4.1 shows that if a formula ϕ is true according to agent i at a state ω in a structure M, then a variant of ϕ (namely, {a mathematical formula}ϕiin or {a mathematical formula}ϕiout) is true at state ω in essentially the same structure.
     </paragraph>
     <paragraph>
      Moreover, once we add propositions of the form {a mathematical formula}(p,i) to the language, we have a great deal of additional expressive power. For example, we can say directly that agent i believes that all agents interpret p the same way that he does by writing {a mathematical formula}Bi(∧j((p,i)⇔(p,j))). We can also make more complicated statements, such as “agent i believes that agents j and k interpret p the same way, although they interpret p differently from him: {a mathematical formula}Bi((p,j)⇔(p,k))∧¬Bi((p,i)⇔(p,j)). Clearly, far more subtle relationships among agents' interpretations of primitive propositions can be expressed in this language.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>