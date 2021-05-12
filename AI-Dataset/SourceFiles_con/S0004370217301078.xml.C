<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Taking account of the actions of others in value-based reasoning.
   </title>
   <abstract>
    Practical reasoning, reasoning about what actions should be chosen, is highly dependent both on the individual values of the agent concerned and on what others choose to do. Hitherto, computational models of value-based argumentation for practical reasoning have required assumptions to be made about the beliefs and preferences of other agents. Here we present a new method for taking the actions of others into account that does not require these assumptions: the only beliefs and preferences considered are those of the agent engaged in the reasoning. Our new formalism draws on utility-based approaches and expresses the reasoning in the form of arguments and objections, to enable full integration with value-based practical reasoning. We illustrate our approach by showing how value-based reasoning is modelled in two scenarios used in experimental economics, the Ultimatum Game and the Prisoner's Dilemma, and we present an evaluation of our approach in terms of these experiments. The evaluation demonstrates that our model is able to reproduce computationally the results of ethnographic experiments, serving as an encouraging validation exercise.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The Ultimatum Game is widely used in experimental economics to explore interactions between people. In the Ultimatum Game, one person is given a sum of money and told that she can offer as much of it as she wishes to her partner. That partner can accept the offer, in which case both keep the money offered, or the partner can reject the offer, in which case neither gets any money at all. Classical game theory suggests that the offer should be as small as possible: it will be accepted by a rationally self-interested person, since anything is better than nothing, and this will maximise what can be kept. But in practice people do not offer the minimum: it seems that they take other factors into account, perhaps altruism, perhaps a feeling that they are not comfortable with exploitation, or something else. Worse, minimum offers are very often rejected: the partner cannot be relied on to act out of rational self interest either. Studies have shown that people rarely act in conformity with the classical model, and have also shown that they exhibit a wide range of behaviours, with extensive inter-cultural and intra-cultural variation. Since so many of the decisions we take in practical reasoning rely for their success on how other people respond and make their own choices, we have to take account of how other people will behave. Since, however, reliable assumptions about others' actions cannot be made, when choosing our actions we need to find a way to reduce the assumptions we make about how other people will react, or at least be clear about the extent of our assumptions, and the consequences of them being mistaken. In this paper we will look at how we can take account of not just particular actions that other people might do, but the whole set of actions that they might do. We begin with a general consideration of practical reasoning.
     </paragraph>
     <paragraph>
      A key difference between theoretical reasoning (reasoning about what is the case) and practical reasoning (reasoning about what to do) [3] is the direction of fit[4]. Whereas in theoretical reasoning an agent is trying to fit its beliefs to the world, in practical reasoning an agent is choosing an action intended to fit the world to its desires. For theoretical reasoning, there is only one, shared, world, and so if agents differ, one (or both) of them is wrong. In contrast, desires will legitimately differ from agent to agent and so conclusions drawn from practical reasoning will depend on the subjective aspirations and desires of the individual agents. Agents may even be in conflict, so that they attempt to bring about different worlds. The conclusions are therefore legitimately subjective, and disagreement is both rational and to be expected, as discussed extensively by Searle in [4]. Acceptance of an argument as to what to do depends not only on the argument itself – for it must, of course, be a sound argument – but also on the audience to which it is addressed [5]. Capturing such rational disagreement within a computational model of argument is one of the key motivations for our work, as we will discuss in more detail in the next section. First we set out our main objectives for this paper, which are:
     </paragraph>
     <list>
      <list-item label="•">
       to take account of the effects on our actions of what others may do in the framework of value-based practical reasoning; and do this without requiring assumptions about the beliefs and preferences of any agents other than the agent engaged in the reasoning;
      </list-item>
      <list-item label="•">
       to do so in a manner compatible with the results of game theory and multi-criteria utility (e.g., [6], [7]) while explicitly and transparently allowing for subjectivity and altruism;
      </list-item>
      <list-item label="•">
       to be able to express the reasoning in the form of arguments and objections so as to facilitate integration with value-based practical reasoning, and persuasion [8] and deliberation [9] dialogues based on this style of reasoning.
      </list-item>
     </list>
     <paragraph>
      The rest of the paper is structured as follows. In section 2 we provide some background discussion that motivates our computational account of value-based reasoning and we also summarise prior work on the topic. In section 3 we provide an overview of the games we use from experimental economics as the settings for exploring our computational account. Section 4 contains the main details of our account of justifying actions by relating arguments to reasoning about expected utilities. In section 5 we show how the reasoning can be expressed in terms of argumentation schemes that can be used as the basis of persuasion and deliberation dialogues within practical reasoning. Further, we demonstrate how the schemes can be used in the Prisoner's Dilemma scenario, before going on to demonstrate in section 6 how the account can be applied in the Ultimatum Game. Section 7 offers an evaluation of the approach by relating it back to our original objectives and also through consideration of how well our approach is able to reproduce the results of previous real world ethnographic studies. Section 8 closes the paper with some concluding remarks.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      In this section we provide some background motivation for the work that we present. We start by discussing Perelman's notion of an audience [5], then we summarise prior work that provides a computational realisation of this concept within an argumentation-based account, and we follow this with a discussion on modelling the values of others.
     </paragraph>
     <section label="2.1">
      <section-title>
       Audiences
      </section-title>
      <paragraph>
       Perelman's insight that we draw upon in our work is that for an argument to be accepted, it has to be accepted by someone, an argument is only convincing if it convinces people. There are a number of reasons why the audience should fail to accept an argument that seems entirely convincing to the speaker.
      </paragraph>
      <list>
       <list-item label="•">
        The audience may be irrational, or use some different kind of logic. In [10], the tortoise accepts both p and {a mathematical formula}p→q, but refuses to accept q. No efforts on the part of Achilles can persuade the tortoise: there is insufficient in common between them to enable any meaningful debate.
       </list-item>
       <list-item label="•">
        The audience may lack the capacity to follow the argument. While a watertight proof may appear to be a universally acceptable argument, it may be that the audience cannot follow the proof and so are not convinced by it. If such an audience accepts the conclusion it is on the basis of a kind of argument from authority, because they recognise that the speaker is in a position to know and they trust the speaker, not on the basis of the proof they do not understand.
       </list-item>
       <list-item label="•">
        The audience and the speaker may have different Weltanschauungs. Thus for example, Christians often deploy arguments about green issues based on a God-given duty of stewardship. Obviously such arguments will have no impact on secular ecologists. The groups may be able to debate, but there will be some arguments that they are not able to share. In the famous words of Karl Barth, “belief cannot argue with unbelief”.
       </list-item>
       <list-item label="•">
        Related, but more tractable, is that there may be a difference in conceptualisation. This may well lead to mutual misunderstandings. In Computer Science, this problem is addressed by the use of ontologies [11]. Once the different conceptualisations have been made explicit it may be possible to align them [12], enabling fruitful debate.
       </list-item>
       <list-item label="•">
        The audience may differ from the speaker in beliefs. This is perhaps the most corrigible, since both should agree that either the speaker or the audience is right. They can thus use mutually acceptable methods to resolve the factual dispute, or appeal to an arbitration process, such as the use of a jury to establish the facts in legal cases.
       </list-item>
       <list-item label="•">
        Finally, as suggested above, in practical reasoning the audience may differ in aspirations, interests, values, goals and preferences, so that they evaluate future states of affairs differently. While it is possible to argue for value preferences [13], it may well be that the participants will agree to disagree [8]. Unlike the other disagreements, disagreements about what to do are based on individual properties of the agents, and so agents should be expected to differ. For practical reasoning, unlike the other cases, the disagreement is not a sign that something has gone wrong, and reconciliation is not always achievable, or desirable.
       </list-item>
      </list>
      <paragraph>
       These are all interesting cases, and all need to be considered in argumentation, but it is only the last that we are concerned with in this paper. Perelman summarises the situation with respect to practical reasoning in [14]: If men oppose each other concerning a decision to be taken, it is not because they commit some error of logic or calculation. They discuss apropos the applicable rule, the ends to be considered, the meaning to be given to values, the interpretation and characterisation of facts. Searle expresses a similar view in [4]: Assume universally valid and accepted standards of rationality, assume perfectly rational agents operating with perfect information, and you will find that rational disagreement will still occur; because, for example, the rational agents are likely to have different and inconsistent values and interests, each of which may be rationally acceptable. In what follows, to capture the required type of disagreement, we will consider an audience to be characterised by a set of values, and a preference ordering on those values.
      </paragraph>
      <paragraph>
       This notion of audience was computationally modelled in [15] and made more formal in Value-based Argumentation Frameworks (VAFs) [16]. VAFs are an extension of the abstract Argumentation Frameworks (AFs) introduced in the seminal paper of Dung [17]. In a VAF arguments are associated with the social (i.e. not numeric) values{sup:1} their acceptance promotes or demotes. Different audiences can now be characterised by the ordering they place on these values. Whereas in an AF an argument is defeated by any attacking argument, in a VAF an argument is defeated for an audience by an attacker only if the value associated with the attacking argument is ranked at least as highly by that audience. In this way different audiences will accept different sets of arguments (preferred semantics [17] is used to determine acceptance), and, as is shown in [16], provided the VAF contains no cycles in the same value, there will be a unique non-empty preferred extension. Thus, use of VAFs provides a way of explaining (and computing) the different arguments accepted by different audiences. Value-based Reasoning has been widely used as the basis of practical reasoning ([18], [19], [20], [21], [7], [22]) and applied in particular areas such as law ([23], [24], [25]), e-democracy ([26], [27]), policy analysis ([28]), medicine, ([29]), experimental economics ([30]), rule compliance ([31]), decision support ([32]) and even ontology alignment ([33], [34]). Complexity results for VAFs were established in [35] and [36].
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       An argumentation scheme for value-based practical reasoning
      </section-title>
      <paragraph>
       The application of the preferences of an audience, expressed as an ordering on values, to practical reasoning requires the generation of the arguments and identification of the values associated with them. The proposal made in [37] was to use an argumentation scheme (now included in the compendium of argumentation schemes collected in [38]) justifying an action in terms of the values it promotes. The scheme appears in [37] as: In the current circumstances R, I should perform action A, to bring about new circumstances S, which will achieve goal G and promote value V.
      </paragraph>
      <paragraph>
       We will henceforth refer to this scheme as Practical Reasoning Argumentation Scheme (PRAS). Like all argumentation schemes, PRAS establishes its conclusion only presumptively [39] and can be challenged using what [39] and [38] call critical questions. Thus an argument generated using PRAS can be challenged by claims against its soundness such as:
      </paragraph>
      <list>
       <list-item label="•">
        that the current state is different,
       </list-item>
       <list-item label="•">
        that the action is not possible,
       </list-item>
       <list-item label="•">
        that the action will reach a different state,
       </list-item>
       <list-item label="•">
        that the action will fail to achieve its goal, or
       </list-item>
       <list-item label="•">
        that the action will fail to promote its value.
       </list-item>
      </list>
      <paragraph>
       It can also be challenged on the basis of the desirability of the action:
      </paragraph>
      <list>
       <list-item label="•">
        that it will also demote values and these values are more important, or
       </list-item>
       <list-item label="•">
        that alternative actions promote values that are more important.
       </list-item>
      </list>
      <paragraph>
       This second group of objections is what gives room for subjectivity arising from different value orderings so that we can model the differences between audiences arising from differences in the states they wish to bring about.
      </paragraph>
      <paragraph>
       In [19] seventeen different critical questions were identified that could give rise to objections to, and counter-arguments against, instantiations of PRAS.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Computational realisation of this scheme
      </section-title>
      <paragraph>
       In order to make this approach computable, it is necessary to provide an underlying representation of relevant aspects of the world and how they can be affected by the actions of agents. State Transition Diagrams are a natural choice for this purpose, since they can represent the world as a set of states, and actions as the transitions between them. In open agent systems, however, the outcome of an action may well depend on what the other agents in the situation choose to do. Thus an individual's choice does not necessarily determine the state that will be reached. To account for this, open agent systems should model transitions as the joint actions{sup:2} composed of the individual actions of all the agents relevant to the situation.{sup:3} A suitable variant of state transition diagrams for use in open agent systems is Action-based Alternating Transition Systems (AATS), introduced in [41], since they do have joint actions as their transitions. AATSs are formally based on Alternating-time Temporal Logic [40]. The basic AATS was augmented in [19] to allow the labelling of the transitions with the values promoted and demoted by that transition. AATSs labelled in this way were termed Action-based Alternating Transition Systems with Values (AATS+V) and AATS+Vs were used to provide the underpinning semantical structure for the approach to practical reasoning set out in that paper.
      </paragraph>
      <paragraph>
       AATSs are particularly concerned with the joint actions of the set of agents Ag. {a mathematical formula}jAg is the joint action of the set of n agents that make up Ag, and is a tuple {a mathematical formula}〈α1,...,αn〉, where for each {a mathematical formula}αj (where {a mathematical formula}j≤n) there is some {a mathematical formula}agi∈Ag such that {a mathematical formula}αj∈Aci. Moreover, there are no two different actions {a mathematical formula}αj and {a mathematical formula}αj′ in {a mathematical formula}jAg that belong to the same {a mathematical formula}Aci. That is, a joint action contains one, and only one action, for every agent in Ag. The set of all joint actions for the set of agents Ag is denoted by {a mathematical formula}JAg, so {a mathematical formula}JAg=∏i∈AgAci. Given a {a mathematical formula}j∈JAg and an agent {a mathematical formula}agi∈Ag, {a mathematical formula}agi's action in j is denoted by {a mathematical formula}ji. Using this, the formal definitions of an AATS are as follows:
      </paragraph>
      <paragraph label="Definition 1">
       AATS [41]An Action-based Alternating Transition System (AATS) is an {a mathematical formula}(n+7)-tuple {a mathematical formula}S=〈Q,q0,Ag,Ac1,...,Acn,ρ,τ,Φ,π〉, where:
      </paragraph>
      <list>
       <list-item label="•">
        Q is a finite, non-empty set of states;
       </list-item>
       <list-item label="•">
        {a mathematical formula}q0∈Q is the initial state;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ag={ag1,...,agn} is a finite, non-empty set of agents;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Aci is a finite, non-empty set of actions, for each {a mathematical formula}agi∈Ag where {a mathematical formula}Aci∩Acj=∅ for all {a mathematical formula}agi≠agj∈Ag; {a mathematical formula}AcAg is the set of all actions {a mathematical formula}{Ac1∪...∪Acn};
       </list-item>
       <list-item label="•">
        {a mathematical formula}ρ:AcAg→2Q is an action pre-condition function, which for each action {a mathematical formula}α∈Acag defines the set of states {a mathematical formula}ρ(α) from which α may be executed;
       </list-item>
       <list-item label="•">
        {a mathematical formula}τ:Q×JAg→Q is a partial system transition function, which defines the state {a mathematical formula}τ(q,j) that would result by the performance of j in state q. This function is partial as not all joint actions are possible in all states;
       </list-item>
       <list-item label="•">
        Φ is a finite, non-empty set of atomic propositions; and
       </list-item>
       <list-item label="•">
        {a mathematical formula}π:Q→2Φ is an interpretation function, which gives the set of primitive propositions satisfied in each state: if {a mathematical formula}p∈π(q), then this means that the propositional variable p is satisfied (equivalently, true) in state q.
       </list-item>
      </list>
      <paragraph>
       This definition was extended in [19] to allow the transitions to be labelled with the values they promote.
      </paragraph>
      <paragraph label="Definition 2">
       AATS+V [19]Given an AATS, an AATS+V is defined by adding two additional elements as follows:
      </paragraph>
      <list>
       <list-item label="•">
        V is a finite, non-empty set of values.
       </list-item>
       <list-item label="•">
        {a mathematical formula}δ:Q×Q×J×V→{+,−,=} is a valuation function which defines the status (promoted (+), demoted (−) or neutral (=)) of a value {a mathematical formula}vu∈V ascribed to the transition between two states made using a particular joint action: {a mathematical formula}δ(qx,qy,ji,vu) labels the transition between {a mathematical formula}qx and {a mathematical formula}qy using {a mathematical formula}ji with one of {a mathematical formula}{+,−,=} with respect to the value {a mathematical formula}vu∈V.
       </list-item>
      </list>
      <paragraph>
       This definition is an extension of [19] to allow for values to be promoted by the intrinsic worth of actions. Suppose Tom enjoys fishing while Dick does not. Now both the joint action where Tom fishes and Dick does nothing and the joint action where Dick fishes and Tom does nothing will result in the pair having fish. But only the first will promote pleasure, since only Tom enjoys the activity of fishing in itself. Thus there will be two different transitions, one for each of the joint actions, and only one of them should return “+” with respect to the value pleasure.
      </paragraph>
      <paragraph>
       An Action-based Alternating Transition System with Values (AATS+V) is thus defined as an {a mathematical formula}(n+9) tuple {a mathematical formula}S=〈Q,q0,Ag,Ac1,...,Acn,ρ,τ,Φ,π,V,δ〉. The values may be ascribed to transitions on the basis of the source and target states, or in virtue of an action in the joint action, where that action has intrinsic value.
      </paragraph>
      <paragraph>
       Given a representation of the problem situation as an AATS+V, the discovery of arguments, counter arguments and objections can be implemented in several ways, including that used in [44]. In [44] a database containing tables for the states, joint actions and transitions of the AATS+V is created to hold the problem information and then instantiations of PRAS and challenges to those instantiations can be found by fairly simple queries to that database. For example there will be an instantiation of PRAS if there is a transition from the current state which promotes a value.
      </paragraph>
      <paragraph>
       Three stages in practical reasoning are identified in [19]:
      </paragraph>
      <list>
       <list-item label="•">
        Problem formulation: essentially the construction of an AATS+V for the particular problem situation. The AATS+V will reflect the views of the agent engaged in the reasoning, and so can be seen as embodying that agent's causal model (to determine the transitions) and its values (to enable the labelling of transitions), as is demonstrated in [45];
       </list-item>
       <list-item label="•">
        Epistemic stage: this involves determination of what the agent engaged in the reasoning believes (or chooses to assume) about the current state and the joint action that will result from the choice of a particular individual action by the agent concerned;
       </list-item>
       <list-item label="•">
        Option selection: the arguments generated from the AATS+V are formed into a VAF and their acceptability status determined according to the preferences of the agent engaged in the reasoning.
       </list-item>
      </list>
      <paragraph>
       While problem formulation and the identification of the current state can be resolved using normal theoretical reasoning techniques, and the option selection stage can be carried out using value-based reasoning based on VAFs as described in [16], how the joint action should be determined in the epistemic stage is less obvious and is the topic of this paper. The essential problem is that in order to know what it is best to do, it is necessary to anticipate what the other agents that can influence the outcome of our action will do, since this may drastically affect what results from our own actions. But since this reasoning will depend on the beliefs, aspirations and preferences of these other agents, a number of assumptions are required to be made and these are often difficult to justify. Agents who adopt the naive approach of assuming that others will be like themselves, tend to perform badly in practice as is shown in work such as [46], but the agents may have no knowledge at all of some or all the other agents involved, which could provide the basis of a different model. Even if they do have knowledge of these other agents, predicting their behaviour is a highly uncertain matter. This variety of possible behaviours should be expected since an important feature underlying practical reasoning is that agents are different, have different desires and aspirations, and will rightly make different choices in similar situations.
      </paragraph>
      <paragraph>
       In [47] the argumentation was articulated into a set of argumentation schemes designed to justify each of the components in PRAS. In that paper the actions of others were seen to present a problem for the justification of the claim that a particular value would be promoted, since this required that a specific transition be followed. As noted in [47], the requirement imposed by PRAS is rather weak: merely that there is some joint action containing the advocated action which gives rise to a transition labelled with the value. But if this is challenged we need to show why we believe the other relevant agents will act so that this is indeed the joint action that will be performed and that this is the transition that will be followed. To do this in the terms of PRAS requires that, for every other agent modelled in the AATS+V, we can show that they will choose the appropriate action using an instantiation of PRAS applicable to them individually. That is, they use an AATS+V embodying their beliefs, causal model, and values [45]. This, in turn, requires us to consider how each relevant agent will formulate the problem, the epistemic assumptions that each agent will make, and the value preferences of each agent. Note that this will include the assumptions that the agents will make about each other. Given the number of assumptions that need to be made, it is evident that some firmer basis for the choice of joint action is highly desirable.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Modelling the values of others
      </section-title>
      <paragraph>
       One approach, common in classical economics, is to see agents as consistently rational and narrowly self-interested agents who can be expected to pursue their subjectively-defined ends optimally. John Stuart Mill [48] put it thus when describing “economic man” (sometimes called homo economicus): [Economics] is concerned with him solely as a being who desires to possess wealth, and who is capable of judging the comparative efficacy of means for obtaining that end.
      </paragraph>
      <paragraph>
       Game Theory [49] also uses a single measure of utility expressed as a payoff matrix, and has become a very widespread basis for the design of multi-agent systems [50]. This approach has led to some insights, and provided the foundation for much elegant mathematics, but unfortunately does not provide a satisfactory explanation of the way in which humans behave in practice. And of course, if we are deciding what to do, we cannot expect others to behave as they should, so even if this were a good normative theory, we would still need an adequate descriptive theory.
      </paragraph>
      <paragraph>
       That others cannot be seen in this way is well demonstrated by a number of experiments carried out in behavioural economics. These experiments are carried out, using a variety of public goods games, to test the theory that behaviour can be predicted using the assumptions of classical economics and game theory. There are valuable meta studies, in particular for the Dictator Game [51] and the Ultimatum Game [52]. There is also a study comparing how fifteen small scale societies play the Ultimatum Game [53]. The findings suggest that the canonical model is followed only very rarely. Thus in [53] we read: in addition to their own material payoffs, many experimental subjects appear to care about fairness and reciprocity, are willing to change the distribution of material outcomes at personal cost, and are willing to reward those who act in a cooperative manner while punishing those who do not even when these actions are costly to the individual.
      </paragraph>
      <paragraph>
       Even in the Prisoner's Dilemma [54], where defection is clearly the dominant strategy, we find a tendency to deviate from it [55]. In [56], the emergence of norms and conventions is discussed in terms of the Prisoner's Dilemma, and some of the other characteristics influencing behaviour, such as empathy, trust and esprit de corps are cited as ways in which these norms can be formed. The role of punishment is explored in [57]. What all these comparative studies show is that:
      </paragraph>
      <list>
       <list-item label="•">
        The canonical model used in classical economics, game theory and many multi agent systems is not adequate to explain the behaviour encountered in experimental studies;
       </list-item>
       <list-item label="•">
        There is a significant amount of inter-cultural variation, suggesting that the established values of subjects is carried forward into these experiments;
       </list-item>
       <list-item label="•">
        There is also a significant amount of intra-cultural variation, suggesting that the behaviour of individuals cannot reliably be predicted solely on the basis of their cultural background.
       </list-item>
      </list>
      <paragraph>
       Our view is that by bringing the subjective ordering of values of agents to the fore, value-based reasoning can provide a fruitful way of exploring these issues. This was borne out by the examination of the Dictator and Ultimatum Games in [30]. There, however, like all approaches based on [19], the reasoning about what others would do relied too heavily on unjustifiable assumptions about the values they would use, and how they would order them, which is an issue that we address in this paper.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      The games
     </section-title>
     <paragraph>
      In this section we describe two games from experimental economics that we use as the setting for exploring our computational account. We will not consider the Dictator Game here, because although, as shown in [51] and [30], it is amenable to analysis in terms of value-based reasoning, there is only one decision maker, and so the need to anticipate the actions of others, which is the aspect in which we are interested here, does not arise. We will therefore only consider the Ultimatum Game and the Prisoner's Dilemma in this paper.
     </paragraph>
     <section label="3.1">
      <section-title>
       The Ultimatum Game
      </section-title>
      <paragraph>
       In the Ultimatum Game [58] the first player is given a sum of money and told that he may offer some (or all) of it to the second player. Once the proposer has made an offer the respondent may choose to accept the offer, or reject it, in which case both players receive nothing. Whereas traditional game theory would suggest that the proposer would make the smallest offer possible and the respondent would accept it, experiments do not support this. The meta-analysis of thirty-seven papers reported in [52] found that on average the proposer offers 40% of the pie to the responder. ... On average 16% of the offers is rejected. ... We find differences in behavior of responders (and not of proposers) across geographical regions.
      </paragraph>
      <paragraph>
       It may well be that regions (at least at the country or even continent level used in [52]) do not provide the best explanation for different behaviours, being themselves large and often culturally heterogeneous. Another study [53], based on small-scale, homogeneous societies, found the different cultures more predictive: Among the Achuar, Ache and Tsimane, we observe zero rejections [...]. Moreover, while the Ache and Achuar made fairly equitable offers, nearly 50 percent of Tsimane offers were at or below 30 percent, yet all were accepted. Similarly, Machiguenga responders rejected only one offer, despite the fact that over 75 percent of their offers were below 30 percent. At the other end of the rejection scale, Hadza responders rejected 24 percent of all proposer offers and 43 percent of offers at 20 percent and below. Unlike the Hadza, who preferentially rejected low offers, the Au and Gnau of Papua New Guinea rejected both unfair and hyper-fair (greater than 50 percent). Two aspects of the societies concerned, namely the amount of cooperation found in the general economic activity of the society and the extent to which market exchanges were a feature of daily life, were found to be explanatory in [53]: the Machiguenga and Tsimane rank the lowest; they are almost entirely economically independent at the family level and engage rarely in productive activities involving more than members of a family. By contrast, the Lamelara whale-hunters go to sea in large canoes manned by a dozen or more individuals. ... The Machiguenga show the lowest cooperation rates in public-good games, reflecting ethnographic descriptions of Machiguenga life, which report little cooperation, exchange, or sharing beyond the family unit.
      </paragraph>
      <paragraph>
       In contrast, the Lamelara have the highest mean offer (58%) and a zero rejection rate. As shown in [30], this can be explained by differing values and preferences amongst the participants, with the ordering emerging from their everyday activities being applied in the games. The game was analysed in [30], with the following six values:
      </paragraph>
      <list>
       <list-item label="•">
        Proposer's Money (M1): Promoted by acceptance of an offer to a degree inversely related to the size of the offer and demoted if the offer is rejected;
       </list-item>
       <list-item label="•">
        Respondent's Money (M2): Promoted by acceptance of an offer, to a degree related to the size of the offer;
       </list-item>
       <list-item label="•">
        Generosity (G): Promoted for the proposer by giving away a reasonable amount of money;
       </list-item>
       <list-item label="•">
        Equality (E): Promoted by both participants receiving the same amount;
       </list-item>
       <list-item label="•">
        Proposer's Contentment (C1): Promoted by the acceptance of a low offer (did not offer too much) and demoted by the rejection of a low offer (did not offer enough), or by the rejection of a good offer, since the respondent would then be considered unreasonable;
       </list-item>
       <list-item label="•">
        Respondent's Contentment (C2): Promoted by accepting a good offer and demoted by accepting a low offer.
       </list-item>
      </list>
      <paragraph>
       The transition diagram for the Ultimatum Game used in [30] is given in Fig. 1. This considers the actions as happening serially, so that the joint actions have two stages. Whilst this makes the interaction, where values are promoted and demoted, more explicit, in this paper we prefer to combine the actions, so that our joint actions will comprise a proposal and a response to it. The proposer may make a very high (vho) offer (more than 50%), an equal (eo) offer ({a mathematical formula}=50%), a fair (fo) offer (35–50%), or a low (lo) offer (less than 35%). The respondent may accept or reject, giving 8 joint actions. {a mathematical formula}j1 is {a mathematical formula}{vho,accept}, {a mathematical formula}j2 is {a mathematical formula}{vho,reject} and so on. The AATS+V state records the money for each participant, and two flags, indicating whether the participants are content. Most important are the values promoted and demoted by the transitions determined by joint actions. These are shown in Table 1.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Prisoner's Dilemma
      </section-title>
      <paragraph>
       In this very well known game [54], widely used in discussions of norm emergence such as [56] and [55], both players may either cooperate or defect. Mutual cooperation results (for example) in a payoff of 3 to each player, mutual defection a payoff of 1 to each player, and if one cooperates and the other defects the defector receives 5 and the cooperator receives 0 (though other payoffs are possible provided the order defect-cooperate, both cooperate, both defect and cooperate-defect is maintained, and that the sum for mutual cooperation exceeds the sum for any other option). The “correct” strategy is to defect since that gives a better payoff whichever move the other makes (thus it is the dominant strategy). Note also it is not a zero-sum game: collective utility is maximised by mutual cooperation. Here too, experiments find that the game-theoretic choice is not always made in practice. As explained in [56] conventions to encourage mutual cooperation often emerge or are devised. An example used in [56] is a military situation where much effort is made to build up trust and loyalty to create an esprit de corps in a regiment so that members will cooperate rather than defect, feeling that they are able to rely on their comrades, and in turn reluctant to let their comrades down. The conventions are often reinforced by the use of sanctions to punish defectors [57], [59]. Again there seem to be additional values considered by participants. Here we use the following values:
      </paragraph>
      <list>
       <list-item label="•">
        Player Money (M1 and M2): promoted if a player's payoff is greater than 1 (which can be ensured by defection), and demoted if it is less than 1.
       </list-item>
       <list-item label="•">
        Player Guilt (G1 and G2): demoted if player defects and the other player cooperates.
       </list-item>
       <list-item label="•">
        Player Self-Esteem (S1 and S2): demoted if player 1 (or 2) cooperates and player 2 (or 1) defects: since the player may feel that they should have known better.
       </list-item>
      </list>
      <paragraph>
       In this game there are four joint actions which promote and demote values as shown in Table 2. Note that mutual defection provides a baseline, neither promoting nor demoting any values, since it can always be achieved or bettered.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Justification of actions
     </section-title>
     <paragraph>
      The currently used approach to value-based reasoning about the actions of others follows that proposed in [19] and applied in [30]. This approach is:
     </paragraph>
     <list>
      <list-item label="1.">
       Select a desirable transition based on the values it promotes and demotes.
      </list-item>
      <list-item label="2.">
       Argue for the individual action performed by the agent in the joint action corresponding to that transition.
      </list-item>
      <list-item label="3.">
       Consider objections based on the other agents choosing different actions and so causing different joint actions to be performed.
      </list-item>
      <list-item label="4.">
       Attempt to rebut these objections because:
      </list-item>
     </list>
     <paragraph>
      Whereas 4(a) can be resolved on the basis of the preferences of the agent at whom the argument is directed, 4(b), which is very often needed since the alternative choices of the other agents may lead to undesirable situations, requires more assumptions about the other agents than can be really justified.
     </paragraph>
     <paragraph>
      In previous treatments based on such transition diagrams and using PRAS (e.g. [30]) we would get arguments such as we should cooperate to promote M1 which would be challenged with objections such as but player 2 might defect which would demote M1. Now if M1 is the most important value for Player 1, then the objection will succeed, unless cooperation can be assumed. If M1 is the only value considered, defection is dominant, giving a better outcome whatever the other player chooses. Only if other values are considered will Player 1 choose cooperation. For example, M2 might be rated as highly as M1 (perhaps Player 2 is Player 1's child, or a close colleague), or a clear conscience is regarded as more important than money, in which case Guilt must be considered. The arguments as modelled in [30] are, however, really for a particular transition (joint action), with the agent's own action justified in virtue of the appearance of that action in the desired transition: the objections are available because other joint actions contain the same individual action for the agent concerned. Better would be an argument for the individual action itself, not the joint action and its corresponding transition. This will require us to look at the set of transitions containing the action. In the Ultimatum Game suppose that {a mathematical formula}prob(jointaction) is the probability of jointaction being performed when the agent making the argument chooses some particular individual action. Now the values will be expected to be promoted and demoted according to the probability of the second player's response, as shown in Table 3, and so the expected utility can be calculated, taking account of the complete set of joint actions that include a particular individual action. This obviates the need to assume that the other will perform a particular action, which would enable a particular joint action to be performed. The calculation can be made for the whole range of probabilities: {a mathematical formula}0≤prob(jointaction)≤1.
     </paragraph>
     <paragraph>
      Now we can base arguments on the complete set of transitions containing an action, taking into account the likelihoods of all possible responses, rather than having to assume an action on the part of the other and then consider objections based on the potential performance of a different action. Several forms of argument are available: our examples assume the context of a persuasion dialogue [60] between a persuader (who may be an advisor or the proposer engaged in an internal dialogue, but cannot be the respondent, since the Ultimatum Game, in this form, allows no contact between the two players) and the proposer:
     </paragraph>
     <list>
      <list-item label="•">
       Where an action is certain to promote a value. E.g. You should make a very high offer to promote G.
      </list-item>
      <list-item label="•">
       Where an action cannot promote a value. E.g. You should not make a very high offer as that cannot promote C1.
      </list-item>
      <list-item label="•">
       Where an action can promote a value. E.g. You should make a fair offer as this can promote M1.
      </list-item>
      <list-item label="•">
       Where an action can demote a value. E.g. You should not make a low offer as that will risk demoting C1.
      </list-item>
     </list>
     <paragraph>
      The third and fourth forms will have variants, if we can say something about the relative probabilities of acceptance and rejection. These variants will replace “can” with an indicator of how probable promotion is, such as “very likely”, “more likely than not”, “may possibly” etc. For example, we know from [52] that a fair offer is much more likely to be accepted than rejected, and so we can say you should make a fair offer as that is likely to promote M1, or, since low offers are more likely to be rejected, you should not make a low offer as there is a substantial risk of demoting M1.
     </paragraph>
     <paragraph>
      Similar arguments can be generated for the Prisoner's Dilemma. Promotions and demotions of the extended set of values for each action are shown in Table 4. From this table, arguments can be generated (using techniques from [27], for example), as given below.
     </paragraph>
     <list>
      <list-item label="•">
       You should cooperate to promote M2
      </list-item>
      <list-item label="•">
       You should not cooperate as this risks demoting M1, S1 and G2
      </list-item>
      <list-item label="•">
       You should defect as this might promote M1
      </list-item>
      <list-item label="•">
       You should not defect as this risks demoting M2, G1 and S2.
      </list-item>
     </list>
     <paragraph>
      The real advance here over previous work such as [19] is that there is no longer any need to make assumptions about what the other believes and prefers: the agent can now come to a decision using its own relative preferences between values, its own beliefs and the degree of risk it is prepared to take, whilst requiring no additional machinery: it uses only the AATS+V [19] based on its own beliefs, causal model and values [45]. This fulfils the first of the objectives identified in section 1.
     </paragraph>
     <section label="4.1">
      <section-title>
       More than one other agent
      </section-title>
      <paragraph>
       The games discussed above have only one other agent. Of course, in practice there will typically be several, or even very many, agents that can have an influence. For example, we might extend the Ultimatum Game so that there are several respondents and acceptance or rejection is determined by a majority, or acceptance may require unanimity. Or we might want to look at a problem such as the free-rider problem, whereby defection pays, unless some proportion of the population defects. For example, a small number of tax avoiders will not affect services, but if there are too many, the state infrastructure will collapse. In other situations there may be a number of agents with a range of, perhaps different, choices. This might, at first sight, present a problem, since the number of joint actions rises rapidly: n agents each with m actions give rise to {a mathematical formula}nm joint actions. But we are not especially interested in details of the joint actions: the point of our approach here is to consider the set of joint actions in which the agent of concern performs a particular action, which limits what we have to consider.
      </paragraph>
      <paragraph>
       In the standard value-based approach, as proposed in [19] the values promoted and demoted by a transition are determined by the source and target states. Even where the action performed does affect values, as in [47], so that the intrinsic value of an action can be taken into account, what matters for the agent concerned is its own individual action, and so all transitions between the same pair of states containing that action will promote and demote the same values, as far as that agent is concerned. Thus, for our current purposes, we will consider all joint actions with the same action by the agent concerned leading to the same state to be equivalent, so that consideration can be limited to the different outcomes possible for a given action of the agent engaged in the reasoning, irrespective of how many joint actions reach each outcome. Effectively all the other agents can be considered together as a single other. If a majority is required, it does not matter which agents make up that majority; nor does it matter who the other free loaders are provided that there are not too many of them, and so on. Of course, what can be said about the probabilities may be affected: if we know that only one agent in six will reject a fair offer, then we can be more confident that the larger the number of respondents the more likely it is that there will be a majority for acceptance, but the less likely it is that the offer will be accepted if we require unanimity.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Preferred values
      </section-title>
      <paragraph>
       If only a single value is recognised as worthy of promotion, the choice is often unproblematic. In the Prisoner's Dilemma, M1 may be promoted and cannot be demoted by defection, M2 is only promoted by cooperation, C1 can only be demoted by defection and S1 can only be demoted by cooperation. In some cases, however, whether a value is promoted or demoted may depend on what the other agents choose to do (as is shown through the example presented in Table 3, Table 4). Similarly some combinations of values are unproblematic, but hard choices arise when different values pull us in different directions, because an action may promote one value and demote another, or because values are promoted and demoted to different extents. In such cases we will need to express the subjective preferences of the agent engaged in the reasoning to establish the outcome it prefers.{sup:4}
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Expected utilities
      </section-title>
      <paragraph>
       We now turn to our second objective. In all value-based reasoning it is assumed that an agent is capable of expressing a preference in terms of an ordering on values. However, sometimes quantification of the degree of preference and the extent of promotion is required (see e.g. [32]). In the Prisoner's Dilemma the payoff matrix gives the extent of promotion e.g. {a mathematical formula}j1 promotes M1 and M2 to extent 2 etc: (remember that we only count gains in excess of the baseline towards promoting M1 and M2), but to quantify the preference of combinations of values each value can conveniently be expressed in terms of a single selected value (M1 is the obvious choice). The valuation is subjective to each agent, but requires reference only to its own preferences. Agent Preferences are defined below.
      </paragraph>
      <paragraph label="Definition 3">
       Agent preferencesThe preferences of an agent {a mathematical formula}ag∈Ag is the set {a mathematical formula}Oag={〈v0,w0〉,〈v1,w1〉,...,〈vn,wn〉}, where {a mathematical formula}v0...vn are values and {a mathematical formula}w0...wn are weights associated with these values.
      </paragraph>
      <paragraph>
       Using these weights we can calculate the expected utility of agent i performing α. We will assume that if the desired joint action ({a mathematical formula}j0) does not result from the performance of α, the worst case alternative joint action ({a mathematical formula}jw) will be the one that does result (providing a lower bound). Informally the expected utility of performing α will be the utility of {a mathematical formula}j0 multiplied by the probability of {a mathematical formula}j0 plus the utility of {a mathematical formula}jw (which will often be negative) multiplied by (1 minus the probability of {a mathematical formula}j0).
      </paragraph>
      <paragraph>
       Now, unlike previous work such as [19], there is no longer any need for the reasoning agent to make assumptions about the others' beliefs, domain conceptualisation and preferences that this other agent would use to choose a particular action: the reasoning agent will then be able to decide using its own relative preferences between values, its own beliefs and, where necessary, the particular degree of risk it is subjectively prepared to accept.
      </paragraph>
      <paragraph>
       Once the agent preferences have been established, the expected utilities can be calculated as shown in Definition 4 below:
      </paragraph>
      <paragraph label="Definition 4">
       Expected utility of ag performing α in state {a mathematical formula}qs
      </paragraph>
      <list>
       <list-item label="•">
        Let {a mathematical formula}Jα={j0,j1...jn} be the set of joint actions in which ag performs α (i.e. {a mathematical formula}jag=α) available in the starting state, {a mathematical formula}qs. The action which ag wants to result from performing α is {a mathematical formula}j0.
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}Ejkag=〈e0,e1,...,em〉 be the {a mathematical formula}(m+1)-tuple of the extents to which the values {a mathematical formula}v0..vm are promoted ({a mathematical formula}ei positive) or demoted ({a mathematical formula}ei negative) for ag by the performance of {a mathematical formula}jk∈Jα in {a mathematical formula}qs.
       </list-item>
       <list-item label="•">
        The utility for ag of the performance of {a mathematical formula}jk∈Jα in {a mathematical formula}qs, {a mathematical formula}u(ag,jk), is {a mathematical formula}∑i=0n(ei⁎wi) for every {a mathematical formula}ei in {a mathematical formula}Ejkag where {a mathematical formula}〈vi,wi〉∈Oag. Now {a mathematical formula}Uαag is the set of utilities for ag for all {a mathematical formula}ji∈Jα. Let {a mathematical formula}uw be the {a mathematical formula}ui∈Uαag, such that {a mathematical formula}uw≤ui, for all {a mathematical formula}ui∈Uαag. Thus {a mathematical formula}jw is the worst case for ag of performing α (and so represents the strongest of the possible objections).
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}prob(j0) be the probability of {a mathematical formula}j0 being the joint action performed when ag performs α in {a mathematical formula}qs.
       </list-item>
       <list-item label="•">
        Now the expected utility, {a mathematical formula}euag(α) for ag of performing α in {a mathematical formula}qs is {a mathematical formula}(u(ag,j0)⁎prob(j0))+(u(ag,jw)⁎(1−prob(j0))). Note that we are assuming that if {a mathematical formula}j0 does not result from ag performing α, then {a mathematical formula}jw results, so that {a mathematical formula}euag(α) is a lower bound on the expected utility for ag of performing α.
       </list-item>
      </list>
      <paragraph>
       If we apply our machinery to the Prisoner's Dilemma (PD), since there are only two joint actions containing cooperation by a given agent, {a mathematical formula}prob(j2)=1−prob(j1). In the traditional PD only the agent's own payoff is recognised as having utility. The utility is the actual payoff minus the guaranteed payoff (i.e. the payoff from mutual defection). For cooperation by an agent the extent to which M1 is promoted for that agent is 2 when the other cooperates. M1 is demoted to extent 1 for that agent when the other defects. For defection by the agent it is promoted to extent 4 when the other cooperates and neither promoted nor demoted when the other defects. The expected utilities for ag cooperating (dark grey) and defecting (light grey) for the various probabilities of the other cooperating are shown in Fig. 2.
      </paragraph>
      <paragraph>
       Suppose, however, that both the values M1 and M2 are recognised in PD, and M2 is weighted by the agent engaged in the reasoning at 0.5M1. Now the utility of cooperating when the other also cooperates will be 3M1, and the utility of cooperating when the other defects M1. Similarly we can calculate the expected utility of defecting for the various probabilities of the other cooperating. Defecting when the other cooperates yields a utility of 3.5M1, and mutual defection 0 (since this is the baseline case, no values are considered promoted). Again the desired joint action is performed when the other agent cooperates. This gives the graph shown as Fig. 3. The crossover is at {a mathematical formula}prob(j0)=0.67.
      </paragraph>
      <paragraph>
       If we now add in the value of Guilt (with a weight of 1), which gives a negative utility when an agent defects and the other cooperates, we get the expected utilities shown in Fig. 4.
      </paragraph>
      <paragraph>
       These three figures represent the three possibilities. In Fig. 2, which shows the traditional PD, we find that defection dominates cooperation: the expected utility is higher however likely it is that other defects or cooperates. Therefore defection is the preferred action, whatever the probability of the other cooperating. In Fig. 4 the reverse is true: the inclusion of the additional values means that cooperation dominates defection. In Fig. 3, there is a crossover, at {a mathematical formula}prob(j0)=0.67, so that for high probabilities of cooperation by the other, defection is preferred, but for low levels, the utility afforded to the payoff received by the other makes cooperation preferred.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Arguments in Prisoner's Dilemma using expected utilities
      </section-title>
      <paragraph>
       Our third objective, to be able to express the reasoning in the form of arguments and objections, is addressed by producing arguments based on the expected utilities. These different possibilities mean that several types of argument can be based on the expected utilities. Our examples are expressed in terms suitable for a persuasion dialogue (not between the PD participants, but between a participant and advisor).
      </paragraph>
      <list>
       <list-item label="1.">
        With your value preferences, you should C (respectively, D) since the expected utility is always greater than any alternative.
       </list-item>
       <list-item label="2.">
        With your value preferences, you should C (respectively, D) since the expected utility is always positive.
       </list-item>
       <list-item label="3.">
        With your value preferences, you should C (respectively, D) since the expected utility is greater than the alternative when the probability of cooperation is greater (less) than P.
       </list-item>
      </list>
      <paragraph>
       Of these (1) is appropriate when the action advocated is dominant, and is the strongest of the three. Argument (2) is rather weak: although the expected utility is always positive, the proposed action may have a lower expected utility than the alternative for some (or even all) values of {a mathematical formula}prob(j1). It may, however, be useful if we wish to reach the target state in order to enable some more beneficial action, since it indicates that no harm is done, and so can be used to rebut objections. The argument shows that we suffer no loss, although there may be an opportunity cost. Argument (3) can be effective provided we can give reasons to suppose that probability of cooperation is in the desired range.
      </paragraph>
      <paragraph>
       A natural dialogue arising from using (1) for cooperation might run:
      </paragraph>
      <list>
       <list-item>
        Since you value M1 and M2 equally, you should C since the expected return is always greater than the alternative.
       </list-item>
       <list-item>
        This overvalues M2.
       </list-item>
       <list-item>
        Even if M2 is only worth 70% of M1, the expected utility is always greater than the alternative.
       </list-item>
       <list-item>
        But even 70% overvalues M2.
       </list-item>
       <list-item>
        Even if M2 is only worth half M1, a less than 0.6 probability of cooperation by the other player will mean cooperation has the higher expected utility. Moreover the expected utility of cooperation is still always positive.
       </list-item>
      </list>
      <paragraph>
       In the course of the dialogue, the very strong argument of type (1) has become untenable, but a combination of arguments of types (2) and (3) remain potentially persuasive. Here we are producing argumentation dialogues (albeit not yet expressed in a computational dialogue model) which explore the sensitivity to the assessment of the relative valuations, and the sensitivity to the estimates of cooperation. These dialogues do not require knowledge about the other, but if such information is available these dialogues provide a context in which the information can be deployed by constraining the range for the probability of cooperation by the other player. For an example based on (2):
      </paragraph>
      <list>
       <list-item>
        Since you value M2 at 50% of M1, you should C since the expected return is always positive.
       </list-item>
       <list-item>
        But with these values, D gives a better return unless the probability of cooperation is worse than 0.6.
       </list-item>
      </list>
      <paragraph>
       This objection could be reinforced with reasons to suppose it likely that the other will cooperate (family member, team member or similar, or experimental results, if appropriate results are available). Note, however, that these may also be reasons to increase the valuation of M2 relative to M1.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Expression as argumentation schemes
     </section-title>
     <paragraph>
      The above arguments (1)–(3) for PD can be generalised and presented as argumentation schemes in the manner of [39]; here we present one possible set of such schemes. Note that the users of these schemes are not to be identified with the players in the PD. The dialogues below are supposed to represent one player being given advice (likely to be a persuasion situation), or two people acting as a team in the PD discussing their best course of action (likely to be a deliberation situation). The schemes have a number of premises, and the conclusion in common. These are the premises that set up the situation and identify the key elements. Then additionally there is one key premise for each scheme, which will be characteristic of the scheme. All the schemes have
     </paragraph>
     <list>
      <list-item label="•">
       Conclusion: ag should perform α.
      </list-item>
     </list>
     <section label="5.1">
      <section-title>
       Common premises
      </section-title>
      <paragraph>
       Each scheme will have four premises in common{sup:5}:
      </paragraph>
      <list>
       <list-item label="•">
        Values Premise: V is the set of values considered to be relevant by ag.
       </list-item>
       <list-item label="•">
        Weighting Premise: The relative valuation of the members of V given by ag is a set of {a mathematical formula}〈value,relative weight〉 pairs.
       </list-item>
       <list-item label="•">
        Joint Action Premise: {a mathematical formula}{j0,j1,...jn} is the set of joint actions in which ag performs α.
       </list-item>
       <list-item label="•">
        Expected Utility Premise: {a mathematical formula}euag(α,prob(j0)) returns the expected utilities of agent ag performing α for values of {a mathematical formula}prob(j0) where {a mathematical formula}j0 is the desired joint action.
       </list-item>
      </list>
      <paragraph>
       The first premise identifies the values that the agent will consider and the second weights them in terms of the most important value. The joint actions containing the advocated action α as the action of ag are then taken from the AATS+V to give the third premise. The fourth premise then establishes the expected utilities for the various probabilities of the desired joint action, {a mathematical formula}j0, resulting from ag performing α.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Characteristic premises
      </section-title>
      <paragraph>
       We have three schemes to express the arguments (1)–(3) of section 4. We will name these as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        Argument from Dominance
       </list-item>
       <list-item label="2.">
        Argument from Positive Expected Utility
       </list-item>
       <list-item label="3.">
        Argument from Probability of Cooperation.{sup:6}
       </list-item>
      </list>
      <paragraph>
       Each scheme has its own characteristic premises. For Argument from Dominance:
      </paragraph>
      <list>
       <list-item label="•">
        Dominance Premise: {a mathematical formula}euag(α,j0)≥euag(β,j0) for any alternative action β available to ag, for all values of {a mathematical formula}prob(j0); where {a mathematical formula}j0 is the joint action compliant with the action of ag.
       </list-item>
      </list>
      <paragraph>
       For Argument from Positive Expected Utility:
      </paragraph>
      <list>
       <list-item label="•">
        Positive Utility Premise: {a mathematical formula}euag(α,j0)≥0 for all values of {a mathematical formula}prob(j0).
       </list-item>
      </list>
      <paragraph>
       Finally, for Argument from Probability of Cooperation:
      </paragraph>
      <list>
       <list-item label="•">
        Probability Range Premise: {a mathematical formula}euag(α,j0)≥euag(β,j0) for all values of {a mathematical formula}prob(j0)≥ (respectively, ≤) crossover, where crossover is the point at which {a mathematical formula}euag(α,j0) becomes greater (respectively, less) than {a mathematical formula}euag(β,j0).
       </list-item>
      </list>
      <paragraph>
       Here we are taking the joint action resulting from the agent engaged in the reasoning (ag) performing β to be the best alternative, namely the joint action containing β is the one which yields ag the highest expected utility. Thus β will represent a better choice for ag for some probabilities of cooperation (i.e. there is a cross over point). When, however, we are considering non-cooperation we use the worst case for ag to provide a lower bound on the expected utility. For instance, suppose we are playing chess and there is a choice of three moves A, B and C. When considering alternatives to A, we choose the better of B and C. However, when considering the opponent's response to each of these moves, we consider the response that will give rise to the desired transition and the response that will produce the worst outcome for our agent. This will allow us to compare the joint actions using a lower bound on their expected utility.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Critical questions
      </section-title>
      <paragraph>
       These schemes can be associated with critical questions, as in [39]. Some will be common to all three schemes, while those associated with the characteristic premises will be applicable only to the particular scheme. We begin with those common to all schemes.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Critical questions applicable to all schemes
       </section-title>
       <list>
        <list-item label="•">
         CQ1 Are all the members of V relevant?
        </list-item>
        <list-item label="•">
         CQ2 Are any other Values (i.e. values in the AATS+V, but not included in V for this argument) relevant?
        </list-item>
        <list-item label="•">
         CQ3 Are any members of V over weighted?
        </list-item>
        <list-item label="•">
         CQ4 Are any members of V under weighted?
        </list-item>
       </list>
       <paragraph>
        CQ1 and CQ2 are directed at the Values Premise and CQ3 and CQ4 at the Weighting premise. We have no CQs directed at the other two premises, which are taken directly from the AATS+V and so considered beyond challenge at this stage. If there are only two joint actions containing α, the Expected Utility Premise is fully determined by the labelling of transitions in the AATS+V, together with the Values and Weighting premises. If there are more than two such joint actions, the worst case should be used as the basis for comparison, as described above.
       </paragraph>
       <paragraph>
        Once we have established which values we wish to consider, we can only challenge the characteristic premise of the Argument from Dominance by coming up with an alternative action γ for which {a mathematical formula}euag(γ,j0)&gt;euag(α,j0) for at least some probabilities of compliance. But if the dominance premise is correct with respect to the AATS+V it follows strictly, and so this would challenge the AATS+V, which is considered outside the scope of this stage of the argumentation. Therefore there are no CQs peculiar to the Argument from Dominance. Similarly the Argument from Positive Expected Utility has no individually applicable CQs. The Argument from Probability of Cooperation does, however, have its own CQ:
       </paragraph>
       <list>
        <list-item label="•">
         CQ5 Can {a mathematical formula}prob(j0) be assumed to be ≥ (respectively, ≤) crossover?
        </list-item>
       </list>
      </section>
      <section label="5.3.2">
       <section-title>
        Rebuttals
       </section-title>
       <paragraph>
        These critical questions will have their own typical rebuttals, but these may depend on the context supplied by the original scheme. For example CQ3 could be met by
       </paragraph>
       <list>
        <list-item>
         even if the relative weight of v is reduced to n%,{a mathematical formula}euag(α,j0)remains greater than its alternatives for all values of{a mathematical formula}prob(j0).
        </list-item>
       </list>
       <paragraph>
        in the context of the Argument from Dominance. In the context of Argument from Positive Expected Utility, however, we would meet CQ3 with
       </paragraph>
       <list>
        <list-item>
         even if the relative weight of v is reduced to n%,{a mathematical formula}euag(α,j0)remains ≥0 for all values of{a mathematical formula}prob(j0).
        </list-item>
       </list>
       <paragraph>
        These rebuttals can be preempted by posing a more specific challenge: for example, to the Argument from Positive Expected Utility:
       </paragraph>
       <list>
        <list-item>
         if the relative weight of v is reduced to n%,{a mathematical formula}euag(α,j0)becomes &lt;0 for values of{a mathematical formula}prob(j0)&lt;p.
        </list-item>
       </list>
       <paragraph>
        Perhaps a more natural way of challenging a move in a dialogue is first to pose the appropriate CQ and then to put forward an argument of ones own. Thus the last challenge would be made using both CQ3, and an Argument from Probability of Cooperation for an alternative to α.
       </paragraph>
      </section>
      <section label="5.3.3">
       <section-title>
        Dialogue based on these schemes
       </section-title>
       <paragraph>
        These schemes, challenges based on the critical questions and rebuttals can be deployed in an adversarial discussion, enabling us to realise dialogues of the sort sketched in section 4.4. As an example we will consider a dialogue between White and Black, concerning the action to take in the Prisoner's Dilemma.
       </paragraph>
       <paragraph>
        In the dialogue, we will take it that the participants start from a common AATS+V, so that the schemes can be summarised in the form
       </paragraph>
       <list>
        <list-item>
         Given ListOfValueWeightPairs, one should α because CharacteristicPremise.
        </list-item>
       </list>
       <paragraph>
        White, arguing for defection, begins the dialogue:
       </paragraph>
       <list>
        <list-item>
         Given {a mathematical formula}〈M1,1〉, one should defect because the expected value of defection is always greater than the expected value of cooperation.
        </list-item>
       </list>
       <paragraph>
        Black, arguing for cooperation, can now challenge this using CQ2. As M1 is the only value used in W1, the other CQs cannot be used against W1. Black needs to find a value demoted by defection. As Table 2 shows, there are three possibilities: the payoff of the other player, guilt, or the self-esteem of the other player. Black can make the challenge (here Black uses the payoff of the other player) and then counter with an Argument from Probability of Cooperation:
       </paragraph>
       <list>
        <list-item>
         You must take some account of the payoff to the other player.
        </list-item>
        <list-item>
         Given {a mathematical formula}〈M1,1〉, {a mathematical formula}〈M2,0.5〉, one should cooperate since the expected utility is greater for probability of the other cooperating less than 0.67.
        </list-item>
       </list>
       <paragraph>
        At this point White has several possibilities:
       </paragraph>
       <list>
        <list-item>
         R1, based on CQ1: There is no reason to care about the payoff of the other. This simply refuses to modify the position of W1.
        </list-item>
        <list-item>
         R2, based on CQ2: Introduce another value, demoted by cooperation. Self Esteem is a possibility. A weight of 1 for S1 will restore Defection to dominance.
        </list-item>
        <list-item>
         R3, based on CQ3: Argue that M2 is overrated. For example, reducing the weight to 0.2 will restore defection to dominance. Any greater weight will give some value of {a mathematical formula}prob(j0) at which cooperation is better.
        </list-item>
        <list-item>
         R4. Since B2 expresses an Argument from Probability of Cooperation, CQ5 is also available.
        </list-item>
       </list>
       <paragraph>
        How Black responds will depend on the particular move chosen by White. For R1, much will depend on the context. If White is trying to persuade Black, Black gets to choose the weights on values [8],{sup:7} and so the move is not available to White, since Black has, in B1, already shown that M2 is, in its opinion, something to care about. In other situations, such as deliberation, they are in a different dialogue type, and a nested persuasion dialogue must be entered in which Black will attempt to persuade White that the value should be given a positive weight. Unless Black is trying to persuade White (when White has the last word on what values should be considered), R1 is probably best avoided at this point. R2 similarly depends on context. If it is Black being persuaded, Black can simply reject this challenge, but if White is being persuaded, or in a deliberation, R2 may be an effective move, if arguments for why the additional value merits consideration can be produced.
       </paragraph>
       <paragraph>
        Probably the best tactic for White is to use R3, since this explores the sensitivity of Black's challenge to the weight used and so can establish the least weight that may be accorded to the payoff of the other. Even if White and Black agree to compromise and accept a value for M2 between 0.2 and 0.5, then having made R3 means that R4 becomes more effective because of the reduction in the crossover point. For example, splitting the difference at 0.35 will reduce the crossover to 0.29.
       </paragraph>
       <paragraph>
        Suppose, however, the dialogue in fact continues as follows (e.g. Black is the persuader, and so is able, in this context, to have the final say as to weights and values.)
       </paragraph>
       <list>
        <list-item>
         You have overrated M2. At 0.5, you would be happy for the other to defect when you cooperate.{sup:8} Suppose we weight it at no more than 0.25M1.
        </list-item>
        <list-item>
         Given {a mathematical formula}〈M1,1〉 and {a mathematical formula}〈M2,0.25〉 one should defect because the expected value of defection is always greater than the expected value of cooperation.
        </list-item>
        <list-item>
         I think that 0.5 is the correct weight for M2.
        </list-item>
       </list>
       <paragraph>
        Black may now introduce a third value, say Guilt, which will enable the Argument from Dominance:
       </paragraph>
       <list>
        <list-item>
         Given {a mathematical formula}〈M1,1〉, {a mathematical formula}〈M2,0.5〉 and {a mathematical formula}〈G1,0.5〉, one should cooperate because the expected value of cooperation is always greater than the expected value of defection.
        </list-item>
       </list>
       <paragraph>
        This will work well if Black has the final say as to the weights on values. But even if this is not so, Black may still defend cooperation with the Argument from Positive Expected Utility:
       </paragraph>
       <list>
        <list-item>
         Given {a mathematical formula}〈M1,1〉 and {a mathematical formula}〈M2,0.5〉, I can cooperate because the expected value of cooperation is always greater than zero.
        </list-item>
       </list>
       <paragraph>
        If White had responded to B2 using R4, arguing that there is no reason to think that the probability of cooperation will be below 0.67, Black could try to argue that cooperation is unlikely (e.g. because of the game-theoretic dominance of defection) or, as in B4a, reply with the Argument from Positive Expected Utility, which licenses the performance of the action as a non-harmful choice, while acknowledging that it may not be the best choice.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="6">
     <section-title>
      Application to the Ultimatum Game
     </section-title>
     <paragraph>
      Similar arguments as used in the Prisoner's Dilemma scenario can be developed for the Ultimatum Game. Different weights for the different values will lead to different arguments being dominant. Also the different actions will promote M1 and M2 to varying degrees. M1 will be promoted most (if accepted) by lo, then fo then eo and least by vho, whereas for M2 the reverse will be true. Some example value profiles and recommended actions corresponding to them are given in Table 5. The first six columns indicate the weights for each value, the seventh the best choice for low probabilities of acceptance of offers made, the eighth whether the choice is dominant, or the particular crossover point for this profile, and the last column the best choice for high probabilities of acceptance of offers made. For example, in the penultimate row, at low probabilities of acceptance the best choice is the equal offer: this promotes generosity and avoids angering the other, without sacrificing more money than is necessary to achieve these goals. When the probability of acceptance reaches 0.5 both the fair offer and the low offer take over, with the low offer being slightly preferred. In the final row, the high weight of M2 means that the very high offer is better than the equal offer for low probabilities of acceptance, but the fair offer becomes best for probabilities of acceptance greater than 0.6. When the probability exceeds 0.7, the low offer is also better than the very high offer, but the fair offer remains better.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Evaluation
     </section-title>
     <paragraph>
      We offer two aspects of evaluation. Technically, we can ask whether we achieved the objectives set out in section 2.4. Practically, we can explore the extent to which our proposed approach is able to reproduce the results of empirical studies such as [53].
     </paragraph>
     <paragraph>
      Three technical objectives were given in section 2. Our first objective was to accommodate the need to take account of the possible actions of others, while only considering the values, and preferences of the agent concerned, since modelling of others is inevitably unreliable, given the extent of inter- and intra-cultural variation. We have achieved this, using only the structure of the AATS+V applicable to the agent engaged in the reasoning, by considering all the joint actions containing a given individual action as a set, for all probabilities of compliance, obviating the need to choose the specific actions performed by others. The second objective was to capture this reasoning in a way consistent with existing game and multi-criteria utility theory. We have achieved this by relating the value-based approach to expected utilities. The key notion of a dominant action remains, since, if there is a dominant action, the expected utility of the values promoted by that action will always be greater than any alternative. Moreover where an action is not dominant for all probabilities of the other behaving as required, the bounds can be identified, which allows for the sensitivity to the relative weighting of the relevant values, and to the probability of the other cooperating, to be quantified. To fulfil the third objective, we have given argumentation schemes grounded on the expected utilities. Objections can be based on adding, removing or re-weighting values, which can change the dominant action, or restrict its dominance to a certain range of probabilities of the other agents allowing a particular outcome to be reached. The required degree of revaluation can be specified, allowing for the degree of risk to be specified.
     </paragraph>
     <paragraph>
      The payoffs of game theory are, as is perfectly correct for games which do require firm rules, fixed and unchanging and the same for all the agents. However, the utilities of these payoffs are subjective with respect to the individual goals and aspirations of the agent concerned, and so can be individually set and made subject to change, possibly as a result of persuasive argument, or of empirical evidence. This means that we can attempt a more practical evaluation in terms of reproducing the results of studies such as [53].
     </paragraph>
     <paragraph>
      In [53], it was suggested that the different societies' actions in the Ultimatum Game could be accounted for in terms of the degree of cooperation, and degree of commercial exchange found in daily life. We can relate these characteristics to a value profile. Suppose we associate the value of generosity with the cooperative groups such as the whale hunting Lamelara, and the recognition of C2 (the need to maintain good relations with the other) with commercial exchange. Those who do not engage in cooperative or exchange activities, we term solitary. The results for three such profiles are shown in the first three rows of Table 6. These initial results do indeed support the hypothesis of [53], since they predict equal offers for the cooperation and exchange based societies and low offers for the solitary one.
     </paragraph>
     <paragraph>
      These initial results show that these value profiles can be seen as predicting the action choices typical of corresponding societies. Note that it is the equal offer rather than the very high offer that Table 6 predicts for cooperative societies and those accustomed to commercial exchange. This coheres with the offers made in [53] where the mode offer for the most cooperative society (the Lamelara from Indonesia) and the most exchange based society (the Orma of Kenya) were both 50%, while the Machiguenga of Peru, which report little cooperation, exchange, or sharing beyond the family unit, and so can be seen as solitary, have a mode of less than 25%.
     </paragraph>
     <paragraph>
      We can also look at some specific cases. Two societies seem to have a practice of sharing food, the Ache of Paraguay, and Hadza of Tanzania. But although the hunters in both cases do practice sharing, the Ache seem to willingly embrace the sharing culture, while the Hadza are more reluctant. Thus in [53] we read of the Ache that there are ethnographic descriptions indicating widespread meat-sharing and cooperation in community projects despite the absence of a fear of punishment in Ache society. Ache hunters, returning home, quietly leave their kill at the edge of camp, often claiming that the hunt was fruitless; their catch is later discovered and collected by others and then meticulously shared among all in the camp. [53] (page 76).
     </paragraph>
     <paragraph>
      In contrast the Hadza are reluctant sharers: Hadza appear to reflect their reluctant process of sharing (termed “tolerated theft” by a leading ethnographer of the Hadza). While the Hadza extensively share meat, many hunters look for opportunities to avoid sharing and share only because they fear the social consequences of not sharing. [53] (page 76).
     </paragraph>
     <paragraph>
      In Table 6 we reflect this in rows 4 and 5 by giving a weight to generosity of 1 for the Ache and 0 for the Hadza. This results in equal offers dominating for the Ache, while the Hadza changes to a low offer when the probability of acceptance increases above 0.4. The mode for the Ache is, as this would suggest, 50%. Interestingly there are two different experiments featuring the Hadza, one from a small camp and one from a large camp. In the large camp, where there is a very high (80%) rejection of low offers, the mode is an equal offer, whereas in the small camp, which has a much lower rate of rejection of low offers (31%), the mode offer falls to only 20%. The behaviour of the Hadza thus supports the lack of a dominant action, the ability of the proposer to gauge the likely response of the recipient, and the making of proposals that conform broadly to our account of the reasoning.
     </paragraph>
     <paragraph>
      Another interesting case is the Gnau and Au of Papua New Guinea, shown in the sixth row of Table 6. There the culture of gift giving is such that acceptance places the recipient under an obligation to the giver, which may be called in at a certain date. Thus excessively large gifts, especially unsolicited ones, will frequently be refused because of the anxiety about the unspecific strings attached. [53] (page 76).
     </paragraph>
     <paragraph>
      We represent this by giving a large weight to the value C1. The study shows that the Gnau have a very high rejection rate of offers. Therefore we would expect the Gnau to choose an action reflecting this, which is, as Table 6 shows, the fair offer. And indeed the Gnau have a mode offer of 40% and a mean of 38% which reflects both such a profile and such expectations of response. The Au, however, also from New Guinea and with a similar culture, have a lower rejection rate than the Gnau, (27% as against 40%), and the mode offer from the Au falls to 30%. This reflects the shift from a fair offer to a low offer as the probability of acceptance rises, shown in Table 6.
     </paragraph>
     <paragraph>
      We have produced some results which show that the cultural variations encountered in public goods game experiments of the sort described in [53] can be reproduced in our computational account using suitable value profiles. Thus far we have just looked at reproducing the results of studies such as [53] using profiles reflecting our opinions of the values associated with the different societies. These results are encouraging and suggest that we are thinking along the right lines, but to confirm their significance more broadly we would need to perform our own experiments in which the value preferences of the subjects are established (e.g. through a preparatory questionnaire), and then the subsequent behaviour in the games compared with what is predicted by the value profile. Any large scale empirical study of this sort must, however, be left as the subject of future work, and be properly designed and conducted, which will involve collaboration with experimental economists or psychologists especially to determine how relative weights are to be elicited.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>