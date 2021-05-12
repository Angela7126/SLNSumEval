<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Automata for infinite argumentation structures.
   </title>
   <abstract>
    The theory of abstract argumentation frameworks (afs) has, in the main, focused on finite structures, though there are many significant contexts where argumentation can be regarded as a process involving infinite objects. To address this limitation, in this paper we propose a novel approach for describing infinite afs using tools from formal language theory. In particular, the possibly infinite set of arguments is specified through the language recognized by a deterministic finite automaton while a suitable formalism, called attack expression, is introduced to describe the relation of attack between arguments. The proposed approach is shown to satisfy some desirable properties which cannot be achieved through other “naive” uses of formal languages. In particular, the approach is shown to be expressive enough to capture (besides any arbitrary finite structure) a large variety of infinite afs including two major examples from previous literature and two sample cases from the domains of multi-agent negotiation and ambient intelligence. On the computational side, we show that several decision and construction problems which are known to be polynomial time solvable in finite afs are decidable in the context of the proposed formalism and we provide the relevant algorithms. Moreover we obtain additional results concerning the case of finitaryafs.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The theory of abstract argumentation frameworks (afs) has advanced considerably since its original formulation in the work of Dung [37]. Now recognized as a core research topic within the field of AI in general and its sub-disciplines concerned with knowledge representation and multi-agent systems in particular, afs have proven a powerful modeling tool to address reasoning issues in contexts where classical deductive logic is not the most suitable technique. An overview of the role of argumentation in AI may be found in recent surveys such as that of Bench-Capon and Dunne [14] or the comprehensive collection of introductory articles in Rahwan and Simari [77]. In total matters of semantics, algorithms and computational complexity have occupied many researchers to the extent that their key properties are, now, reasonably well understood. Partly in consequence of such understanding, a rich body of subsequent work has emerged promoting developments of Dungʼs basic formalism in order to encompass scenarios within which the purely abstract approach of [37] is felt to be too limiting. Among the many notable contributions of this nature one finds proposals such as the preference-based afs of Amgoud and Cayrol [2]; the value-based model of Bench-Capon [15]; eafs from Modgil [64]; recursive attacks in the afra mechanism from Baroni et al. [5]; divers treatments of weighted frameworks such as Dunne et al. [43]; as well as sophisticated developments of the basic “binary attack” concept from [37] such as the adf model from Brewka and Woltran [25], [24] and the constrained afs of Coste-Marquis et al. [32], [35].
     </paragraph>
     <paragraph>
      Amidst the wealth and variety of treatments stemming from [37] one can, however, note a common factor: invariably discussion is focused on finite environments be they finite sets of basic arguments or finite attack relationships over these. In contrast, consideration of infinite scenarios has been largely neglected. This turns out to be a limitation from a theoretical, conceptual, and practical perspective.
     </paragraph>
     <paragraph>
      From a theoretical viewpoint, infinite frameworks extend (and, in a sense, complete) the range of investigation on abstract argumentation semantics and their properties. In fact, infinite afs have been the subject of specific attention in the seminal paper by Dung, whose fundamental results do not rely on finiteness. Subsequently, infinite afs have sometimes been considered per se as significant testbeds for examining semantics properties which, though holding in the finite case, may be challenging to prove or fail to hold in the infinite case. For instance, the existence of semi-stable extensions [29] is guaranteed for finite frameworks, while an infinite framework admitting no semi-stable extensions has been devised in [30] (and will be recalled in Section 7.1) and the existence of semi-stable extensions for finitary frameworks has been proved in [91]. Apart from theoretical interest, this kind of results may be useful to shed new light on fundamental issues underlying the definition of different semantics, thus enabling a broader view and deeper understanding in comparing and assessing them.
     </paragraph>
     <paragraph>
      From a conceptual perspective, considering finite frameworks corresponds to (i) adopting a closed view of the argumentation process, which is bounded to terminate after a finite number of steps and (ii) excluding reasoning about infinite domains. Assumption (i) contrasts with the intrinsically open nature of the argumentation process, arising from the fundamental distinction between the concepts of “demonstration by proof” and “persuasion through argument”. That is to say, as noted in [14, p. 620]: “Arguments are defeasible: the reasoning that formed a persuasive case, in the light of changes of viewpoint or awareness of information not previously available, may fail to convince. This defeasibility is never removed: an argument may cease to be challenged and so accepted, but the possibility of challenge remains.”. In other words, the finite view can (at best) describe a “snapshot” of the notional complete context within which an argumentation process could evolve due to potential (but as yet unvoiced) challenge to the conclusions derived. On the other hand, limitation (ii) prevents the use of the abstract argumentation formalism in contexts where reasoning has to deal with open-ended scenarios. For instance, considering an open time horizon, one may want to encompass the existence of infinite arguments associated with infinitely many time instants: this kind of approach has been proposed by Pollock to model reasoning about temporal persistence of beliefs [74].
     </paragraph>
     <paragraph>
      From the practical perspective, it has to be remarked that systems giving rise to a potentially infinite automated production of arguments may well occur in actual applications. On one hand, there are well-known correspondences between argumentation frameworks and other kinds of reasoning systems potentially producing infinite derivations: an example concerning logic programming is in fact given in Appendix A of [37] and will be recalled in this paper. On the other hand, abstract argumentation is widely adopted as a general tool to model dialogues with different purposes (e.g. deliberation, negotiation, persuasion) between self-interested agents in a multi-agent system. In such a context the opportunistic behavior of each agent, driven by “selfish” criteria, and the absence of global coordination and shared information may lead to non-terminating argument exchanges [10].
     </paragraph>
     <paragraph>
      Adding to the considerations above the fact that, as already recalled, Dungʼs original work not only addresses infinite afs as objects of interest but also establishes a number of fundamental properties of such in the context of the basic semantics put forward for afs, it appears that the very limited coverage of infinite frameworks in the subsequent literature represents an important and, to some extent, surprising lacuna in the field.
     </paragraph>
     <paragraph>
      This work contributes to fill this gap by addressing the problem of defining finite specifications of infinite afs through formal languages and proposing an approach based on finite automata. This proposal consists of two basic elements: a description of the (infinite) set of arguments through a finite automaton, and a description of the attack relations linking arguments together through an attack expression. More precisely, the attack expression specifies a mapping between regular expressions describing sets of arguments, with the intended meaning that a set S is attacked by the elements of the set obtained from S through the mapping. The combination of the automaton describing the set of arguments and of the attack expression will be called the afspecification and will be shown to be expressive enough to encompass a variety of infinite argumentation frameworks, including the major examples available in the literature.
     </paragraph>
     <paragraph>
      Clearly, a sufficiently expressive specification formalism needs to be complemented by some suitable computational mechanism for the evaluation of argument justification status, which represents the main goal of any application of computational argumentation, either in finite or infinite contexts. The proposed approach is shown to be satisfactory also from this viewpoint, being able to support the definition of suitable algorithms for some “standard” computational problems in argumentation semantics.
     </paragraph>
     <paragraph>
      The paper is organized as follows. We lay down the context of the work, discuss motivations, and introduce application examples in Section 2. We then recall the necessary technical background on Dungʼs argumentation framework and on formal languages in Section 3. In Section 4 we state a set of basic requirements for a representation formalism for infinite frameworks and show that they are not satisfied by a straightforward naive approach one may adopt. Section 5 introduces and illustrates with a trailing set of examples the afspecification formalism for infinite frameworks and shows that it is expressive enough to capture also “regular” finite frameworks and frameworks that can be regarded as composed by a finite subframework and one or more infinite subframeworks. Section 6 introduces effective computational procedures{sup:1} for several standard decision problems in argumentation semantics in the context of the af specification formalism. Section 7 demonstrates the suitability of the approach, both on the representation and on the computational side, by analyzing in detail its application to four examples: two infinite frameworks previously introduced in the literature for the sake of theoretical analysis and two examples of infinite argumentation in multi-agent systems taken from Section 2. Section 8 discusses related works whilst Section 9 concludes and proposes some areas for future work. Appendix A recalls the basics of formal language and automata theory to make the paper self-contained, while proofs of all technical results are collected in Appendix B.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Context and motivations
     </section-title>
     <paragraph>
      Quoting Prakken [76], Dungʼs paper on abstract argumentation framework “was a breakthrough in three ways: it provided a general and intuitive semantics for the consequence notions of argumentation logics (and for nonmonotonic logics in general); it made a precise comparison possible between different systems (by translating them into his abstract format); and it made a general study of formal properties of systems possible, which are inherited by instantiations of his framework.” Due to its abstract nature, Dungʼs formalism “is best seen not as a formalism for directly representing argumentation-based inference problems but as a tool for analyzing particular argumentation systems and for developing a metatheory of such systems”. In this perspective, investigation of infinite afs finds its motivations in the variety of more concrete contexts and systems where infinite structures play a role and that can be modeled using afs. A (non-exhaustive) account is given in the following subsections.
     </paragraph>
     <section label="2.1">
      <section-title>
       Argumentation models and systems
      </section-title>
      <paragraph>
       Infinite entities have been encompassed at a foundational level by all the main literature approaches to formal argumentation. In fact, both before and after Dungʼs work, other “less abstract” approaches have been defined which formalize arguments and their structure in various ways, with the common property of referring to a generic (and often only partially specified) language, encompassing infinite structures.
      </paragraph>
      <paragraph>
       In the formalization of defeasible reasoning by Simari and Loui [81] an argument structure comprises a possibly infinite set of sentences supporting a conclusion, and, in turn, the set of all possible argument structures is infinite.
      </paragraph>
      <paragraph>
       In the theory of assumption-based argumentation[23] an assumption-based framework consists of a set of beliefs and a set of assumptions which are possibly infinite subsets of a language consisting of countably many sentences. Again the infinite case is explicitly considered in the theoretical analysis of semantics properties in the framework.
      </paragraph>
      <paragraph>
       In Vreeswijkʼs abstract argumentation systems[89], [9] arguments are restricted to have a finite set of premises, but the set of arguments is possibly infinite and infinite argumentation sequences (involving either finite or infinite sets of arguments) are used as a formal tool for extension evaluation, by introducing a notion of “limit” for infinite argumentation sequences. In [89] it is remarked in particular that some desirable limit properties of infinite argumentation sequences may not hold when an infinite set of arguments is considered. This is left as an open problem, which, as to our knowledge, has still to be solved.
      </paragraph>
      <paragraph>
       In DEFLOG [87] the central notion is the “dialectical interpretation” of a theory, which basically is a (possibly infinite) set of sentences related by two connectives representing support and defeat relations respectively.
      </paragraph>
      <paragraph>
       Finally, in the more recent ASPIC formalism [1] and its ASPIC+ evolution [76] arguments with an infinite number of subarguments (and hence infinite sets of arguments) are encompassed and none of the main properties relies on argument finiteness.
      </paragraph>
      <paragraph>
       It can hence be stated that the consideration of infinite structures and derivations has been consistently regarded as a basic, one could even say “natural”, feature in argumentation formalisms. It has however to be acknowledged that this feature has typically been regarded as problematic when moving from (more or less abstract) theory to complete specification (and implementation) of actual argumentation-based reasoning systems. In fact, the unbounded open nature of argumentative reasoning has often been contrasted with the practical needs and limitations of resource-bounded agents.
      </paragraph>
      <paragraph>
       From a philosophical stance, this contrast has been pointed out by Pollock [72] by introducing the distinction between justified beliefs and warranted propositions. Quoting Pollock, “at each stage of reasoning, if the reasoning is correct then a belief held on the basis of that reasoning is justified, even if subsequent reasoning will mandate its retraction” while “in contrast to justification, warrant is what the system of reasoning is ultimately striving for. A proposition is warranted in a particular epistemic situation if and only if, starting from that epistemic situation, an ideal reasoner unconstrained by time or resource limitations would ultimately be led to believe the proposition”. In this view, warrant may be regarded as a sort of unattainable goal for a practical resource-bounded agent, which needs to be content with the more limited notion of justification.
      </paragraph>
      <paragraph>
       From the practical side, an example of the problems in dealing with infinite structures is presented in [52] in the context of the DeLP (Defeasible Logic Programming) system. Here, one of the central notions is the one of an “argumentation line”, which is basically a sequence of argument structures where each element of the sequence is a defeater of its predecessor. As discussed in [52] infinite argumentation lines may easily emerge for various reasons (e.g. self-defeating arguments, reciprocal defeaters, non-concordant sets of supporting arguments). Since managing infinite argumentation lines is regarded as undesirable, suitable restrictions are introduced in the formal definition of argumentation line to avoid these cases.
      </paragraph>
      <paragraph>
       A different kind of restriction is adopted in the argumentation-based approach to Defeasible Logic proposed in [54]. Here, an argument is a possibly infinite proof tree for a literal p (associated with the tree root). By definition, however, only finite arguments can be acceptable (this rather drastic choice is motivated by the goal of avoiding the risk of supporting “well-known fallacies such as circular argument and infinite regress”) while infinite arguments keep anyway the power to prevent justification of other arguments.
      </paragraph>
      <paragraph>
       In the context of the logic-based approach to argumentation of Besnard and Hunter [16] the classical chicken and egg dilemma is used as a common sense reasoning example giving rise to an infinite sequence of arguments, each being a counterargument to the preceding one (such a sequence is called dispute in this context). In fact, dilemmas (of various nature and possibly more interesting than chicken and egg) are recognized as a significant case of infinite reasoning with conflicting arguments also in non-technical literature.
      </paragraph>
      <paragraph>
       An example is given in the novel “Runaround” by Isaac Asimov where, on the planet Mercury, a robot, called SPD-13, receives by two spacemen the order to accomplish a mission which requires to collect selenium from a pool. The robot is programmed to obey three basic rules which can be synthesized as follows. The first rule states that the robot has to protect human lives. The second rule states that the robot has to obey orders unless they conflict with the first rule. The third rule states that the robot has to protect itself unless this conflicts with the first rule. After a long wait, the spacemen send out another (less capable) robot to look for SPD-13. From the report of the second robot they realize that the mind of SPD-13 is in a loop (which has caused a sort of “drunkenness”) which can be described as follows: when the robot gets near the selenium pool it perceives an unforeseen danger, the third rule is activated and the robot builds an argument to go away, prevailing on the previous decision to obey the order. When the robot is sufficiently far from the pool, its danger perception decreases and so according to the second rule it builds a new argument which leads it to turn back towards the pool, prevailing over the previous decision. When it gets sufficiently closer to the pool, it feels the danger again and the process restarts.
      </paragraph>
      <paragraph>
       From the representation point of view in [16] this kind of problems is tackled by imposing some restriction in the definition of the argument tree structure, which is meant to capture all the disputes concerning a specific argument (represented by the root of the tree). More precisely, the premises of an argument added to the tree are forbidden to be a subset of the union of the premises of its ancestors. With this constraint, the argument tree for the chicken and egg dilemma reduces to a two-length chain, but, as observed in [16, p. 62] “the argument tree is merely a representation of the argumentation” and “although the argument tree is finite, the argumentation here is infinite and unresolved”.
      </paragraph>
      <paragraph>
       An explicit restriction to finite structures is also adopted in a recent work concerning the study of postulates and properties of logic-based instantiations of abstract argumentation [53]. In this work, a propositional logic with a countable set of propositional letters is used as a basis for the argumentation process. It ensues that the set of all arguments is countably infinite (though, by definition, an argument is assumed to be built on a finite set of formulae). However, when introducing the notion of argument graph, where nodes are arguments and the arcs represent the attack relation, the authors restrict the consideration to graphs with a finite number of nodes.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Multi-agent systems
      </section-title>
      <paragraph>
       From the previous subsection it appears that while the potential existence of infinite structures is widely acknowledged in non-abstract argumentation contexts too, there is a prevailing attitude to overlook the difficult problem of actually managing them, by ascribing their genesis to undesirable/pathological conditions which can be avoided at the implementation level with proper programming and preventive checks on the knowledge base. While it is certainly true that infinite argumentation structures may arise from uninteresting/undesirable conditions, we remark that these do not exhaust the range of cases where such structures may arise and that, whatever the underlying reason, their emergence cannot always be prevented. In fact, there are concrete situations where systematic well-founded argument generation mechanisms may incur in an open-ended non-terminating behavior.
      </paragraph>
      <paragraph>
       Multi-agent (and more generally distributed) systems provide a major case for this statement, under the non-restrictive and fairly standard assumptions of self-interest and absence of a global reasoner to which all information is available.
      </paragraph>
      <paragraph>
       For instance in [17] argumentation semantics of Defeasible Logic is extended to the case of a multi-context system for distributed ambient intelligence. Each context corresponds to the local knowledge and reasoning of an agent and arguments of different contexts are interrelated through mapping rules. As to undesirable circularities, it is observed that “loops in the local knowledge bases can be easily detected and removed without needing to interact with other agents. However, even if there are no loops in the local theories, the global knowledge base may contain loops caused by mapping rules.” Such loops in the global knowledge base may cause infinite argumentation lines. In [17] this problem is dealt with by adopting the specific assumptions that (i) each agent uses its own vocabulary and is therefore the unique responsible of the evaluation of some literals, (ii) the agents behave in a fully cooperative manner in the process of justification evaluation.
      </paragraph>
      <paragraph>
       In fact, unless one adopts some restrictive assumptions of this kind, the possible onset of non-terminating behaviors in argument defeat status computation is inherent to multi-agent system. This is formally proved in [10] where it is shown that approaches to distributed defeat status computation (see for instance [61], [70]) usually rely on assumptions like a predefined unmodifiable number of agents, the existence of a centralized structure, or the obligation to reveal the entire inner structure of the arguments an agent has built. Removing these restrictions and assuming a multi-agent system with the general properties of unlimited cardinality, autonomy, asynchronism, dynamism, and unconstrained communication (see [10] for details), an impossibility result is obtained showing that no self-stabilizing algorithm can exist for defeat status computation according to any semantics which is valid (namely obeys some fairly general constraint on the defeat status assignment). The paper provides two practical examples of non-terminating behavior: a distributed version of the three liars paradox introduced by Pollock [73] and a negotiation dialogue for resource exchange among three agents.{sup:2}
      </paragraph>
      <paragraph>
       In the following subsections we provide two extended examples of infinite argumentation in multi-agent systems, namely an infinite negotiation process and a distributed reasoning process involving the components of an ambient intelligence system. These examples are inspired to the application contexts considered in [10] and [17] and will be used in Section 7 to demonstrate the application of the formalism proposed in this paper.
      </paragraph>
      <section label="2.2.1">
       <section-title>
        An example in multi-agent negotiation
       </section-title>
       <paragraph>
        In multi-agent systems, independent and possibly self-interested components strive to achieve common or individual goals by various forms of interaction (cooperation, negotiation, persuasion, resource exchange, task allocation, …) for most of which argumentation is considered a suitable model in the literature (see for instance [78] and the references thereof).
       </paragraph>
       <paragraph>
        If one considers interactions involving more than two agents and removes some not always realistic assumptions (e.g. that information on all argument exchanges is available to all agents) the interaction process may not reach a solution and continue forever with an infinite production of arguments.
       </paragraph>
       <paragraph>
        To exemplify, consider a simple negotiation setting where three agents {a mathematical formula}A1, {a mathematical formula}A2 and {a mathematical formula}A3 may exchange resources called {a mathematical formula}Ra,Rb,Rc. Each agent possesses some resource and has its own preference ordering on resources. Each agent is only partially informed on the resources owned by other agents and cannot know the preferences of other agents. At a given time instant, an agent {a mathematical formula}Ax builds an argument for proposing to {a mathematical formula}Ay an exchange between resources {a mathematical formula}Rx and {a mathematical formula}Ry if the following conditions holds: (i) {a mathematical formula}Ax owns {a mathematical formula}Rx; (ii) {a mathematical formula}Ax knows that {a mathematical formula}Ay owns {a mathematical formula}Ry; (iii) {a mathematical formula}Ax prefers {a mathematical formula}Ry to {a mathematical formula}Rx. An agent receiving a proposal may accept or reject it at a later time: the agent who has sent the proposal is free to withdraw it before receiving confirmation of acceptance (typically because the agent has received a more convenient exchange proposal which conflicts with the previous one). An agent is free to reiterate a proposal after having withdrawn it (typically because the reason to withdraw does not hold any more) and is obliged to withdraw an offer s/he has made before accepting an incompatible offer s/he has received. Message exchanges between two agents are not available to other agents but they are collected by an authority supervising the negotiation arena. The authority is informed on all the exchanged messages and on the resources possessed by all agents but has not access to agentsʼ preference rankings. The authority may therefore build an argumentation framework representing the evolution of the negotiation process and may help agents to overcome critical situations. We suppose that the attack relation in the argumentation framework managed by the authority is defined on the basis of the two following rules:
       </paragraph>
       <list>
        <list-item label="•">
         a (possibly reiterated) proposal {a mathematical formula}P1 (received or sent by an agent {a mathematical formula}Ai) attacks a (possibly reiterated) proposal {a mathematical formula}P2 (received or sent by the same agent {a mathematical formula}Ai) if accepting the exchange proposed in {a mathematical formula}P1 makes impossible the exchange proposed in {a mathematical formula}P2;
        </list-item>
        <list-item label="•">
         a withdrawal obviously attacks the withdrawn proposal, a reiterated proposal attacks the corresponding previous withdrawal.
        </list-item>
       </list>
       <paragraph>
        Suppose now that the initial situation is the one described in Table 1.
       </paragraph>
       <paragraph>
        Then each agent builds an offer as follows:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}A1 sends an offer to {a mathematical formula}A2 proposing an exchange between {a mathematical formula}Rc and {a mathematical formula}Rb: {a mathematical formula}O1=Off(t0,(A1,A2,Exch(Rc,Rb)))
        </list-item>
        <list-item label="•">
         {a mathematical formula}A2 sends an offer to {a mathematical formula}A3 proposing an exchange between {a mathematical formula}Rb and {a mathematical formula}Ra: {a mathematical formula}O2=Off(t0,(A2,A3,Exch(Rb,Ra)))
        </list-item>
        <list-item label="•">
         {a mathematical formula}A3 sends an offer to {a mathematical formula}A1 proposing an exchange between {a mathematical formula}Ra and {a mathematical formula}Rc: {a mathematical formula}O3=Off(t0,(A3,A1,Exch(Ra,Rc)))
        </list-item>
       </list>
       <paragraph>
        Clearly each offer is incompatible with the two others.
       </paragraph>
       <paragraph>
        It can be seen that each agent prefers the status resulting from the exchange in the offer s/he has received wrt the one resulting from the offer s/he has made. For instance, agent {a mathematical formula}A1 prefers exchanging {a mathematical formula}Rc with {a mathematical formula}Ra (as proposed by {a mathematical formula}A3) than exchanging {a mathematical formula}Rc with {a mathematical formula}Rb (as s/he has proposed to {a mathematical formula}A2). Then, let say at time {a mathematical formula}t1, each agent sends a message of withdrawal of the previous offer: {a mathematical formula}W1=Wd(t1,(A1,A2,Exch(Rc,Rb))), {a mathematical formula}W2=Wd(t1,(A2,A3,Exch(Rb,Ra))), {a mathematical formula}W3=Wd(t1,(A3,A1,Exch(Ra,Rc))).
       </paragraph>
       <paragraph>
        As a consequence of the withdrawal and of its local view, each agent is now, let say at time {a mathematical formula}t2, in a position where the only reasonable move is to reiterate the initial offer (let say that these messages are denoted as {a mathematical formula}O4, {a mathematical formula}O5, {a mathematical formula}O6): clearly this reproduces the initial situation, causes three further withdrawals and the process goes on forever.{sup:3}
       </paragraph>
      </section>
      <section label="2.2.2">
       <section-title>
        An example in ambient intelligence
       </section-title>
       <paragraph>
        Consider a system of ambient intelligence consisting of several independently developed interacting components, some of which join and leave dynamically the system, as described in [17].
       </paragraph>
       <paragraph>
        Adapting an example presented in [17] suppose that the system includes the following components:
       </paragraph>
       <list>
        <list-item label="•">
         a people locator;
        </list-item>
        <list-item label="•">
         a video surveillance system for each room;
        </list-item>
        <list-item label="•">
         a lighting management system for each room;
        </list-item>
        <list-item label="•">
         personal smartphones.
        </list-item>
       </list>
       <paragraph>
        The components interact as follows:
       </paragraph>
       <list>
        <list-item label="•">
         personal smartphones notify their position to the people locator;
        </list-item>
        <list-item label="•">
         the video surveillance system notifies the results about people detection to the people locator;
        </list-item>
        <list-item label="•">
         the lighting management system has a light sensor and informs the video surveillance system whether each room is dark or not;
        </list-item>
        <list-item label="•">
         the people locator informs the lighting system about peopleʼs presence in each room.
        </list-item>
       </list>
       <paragraph>
        The people locator uses the following rules:
       </paragraph>
       <list>
        <list-item label="R1:">
         if a smartphone is in a room the smartphone owner is in the room
        </list-item>
        <list-item label="R2:">
         if the video surveillance notifies the presence of a person in a room then there is a person in the room
        </list-item>
        <list-item label="R3:">
         if the video surveillance notifies the absence of any person in a room then there is no person in the room
        </list-item>
        <list-item label="R4:">
         if a person is present in a room at time t then the person is present in the room at time ({a mathematical formula}t+1)
        </list-item>
        <list-item label="R5:">
         if a person is not present in a room at time t then the person is not present in the room at time ({a mathematical formula}t+1)
        </list-item>
       </list>
       <paragraph>
        The video surveillance system uses the following rules:
       </paragraph>
       <list>
        <list-item label="R6:">
         if it is not dark and the image processing system recognizes a person in a room then the video surveillance system notifies the presence of a person in the room
        </list-item>
        <list-item label="R7:">
         if it is not dark and the image processing system does not recognize any person in a room then the video surveillance system notifies the absence of any person in the room
        </list-item>
       </list>
       <paragraph>
        The lighting system uses the following rules:
       </paragraph>
       <list>
        <list-item label="R8:">
         if it is dark in a room and a person is in the room switch the room lights on
        </list-item>
        <list-item label="R9:">
         if the lights are on in a room and no person is in the room switch the room lights off
        </list-item>
       </list>
       <paragraph>
        The people locator uses two default persistence rules (R4 and R5) which can be applied in absence of new information and are the weakest ones: in case of conflicting conclusions those derived using R4 and R5 are overruled by those derived using R1, R2, and R3. Moreover video surveillance is regarded as providing more reliable information than the mere presence of a smartphone, hence R3 is stronger than R1.
       </paragraph>
       <paragraph>
        To make the presentation compact, let us omit the details concerning message exchanges among the various components and, as a consequence, combine rules together where possible. The set of rules presented above can be represented by the following logic program{sup:4}M, where not denotes negation as failure and ¬ denotes explicit negation.{a mathematical formula}
       </paragraph>
       <paragraph>
        Most predicates in M have self-explaining names. We assume that variable t refers to time instants, which are discrete and totally ordered, and that {a mathematical formula}s(t) denotes the successor of instant t. We assume that information about the presence of smartphones, darkness, and the outcome of the video recognition system is available for each room in the form of asserted or explicitly negated facts at each time instant, as provided by the relevant devices. In particular, we assume that the image processing component returns either videorecogn or {a mathematical formula}¬videorecogn for each triple {a mathematical formula}(p,r,t) and, of course, does not recognize any person when it is dark. We also assume that all devices are properly working so that, in particular, when light is on in a room r at time t the predicate {a mathematical formula}dark(r,t) is false.
       </paragraph>
       <paragraph>
        R1 is represented by line {a mathematical formula}(r1) of M with the condition {a mathematical formula}notvideovalid(r,t) to ensure priority to the video surveillance system when its output is valid, namely when it is not dark in the room, as specified by {a mathematical formula}(r9). Line {a mathematical formula}(r2) synthesizes rules R2 and R6, and, similarly, {a mathematical formula}(r3) synthesizes R3 and R7. The persistence rules R4 and R5 are represented by lines {a mathematical formula}(r4) and {a mathematical formula}(r5) with the conditions {a mathematical formula}notvideovalid(s(t)) and {a mathematical formula}notphlocated(s(t)) to ensure that other rules prevail when information from devices is available and valid (for phones {a mathematical formula}(r8) applies, where the predicate {a mathematical formula}phlocated(x,t) means that the location of phone x, whatever it is, is known at instant t). Rules R8 and R9, concerning the lighting system are represented respectively by lines {a mathematical formula}(r6) and {a mathematical formula}(r7).
       </paragraph>
       <paragraph>
        Suppose now that Brian at time instant 0 (when outside is dark) exits the office, switches the light off and forgets his smartphone.
       </paragraph>
       <paragraph>
        It follows that, applying {a mathematical formula}(r1), {a mathematical formula}in(Brian,office,0) is derived and as a consequence, by {a mathematical formula}(r6), light is switched on at instant 1. Then the room is no more dark, {a mathematical formula}videovalid(office,1) holds by {a mathematical formula}(r9) and since {a mathematical formula}¬videorecogn(Brian,office,1) holds, by {a mathematical formula}(r3){a mathematical formula}¬in(Brian,office,1) is derived and, applying {a mathematical formula}(r7), the light is switched off. As a consequence at instant 2 the room is dark and {a mathematical formula}videovalid(office,2) cannot be derived. {a mathematical formula}(r1) then applies and {a mathematical formula}in(Brian,office,2) is derived, it follows that, by {a mathematical formula}(r6), light is switched on at instant 3, and so on.
       </paragraph>
      </section>
      <section label="2.2.3">
       <section-title>
        Non-cooperative dialogues
       </section-title>
       <paragraph>
        To avoid situations of the kind described in Sections 2.2.1 An example in multi-agent negotiation, 2.2.2 An example in ambient intelligence, most argumentation-related dialogue protocols in the literature (see for instance [90], [88], [42], [75], [62]) concern the two-party case, which implies in particular that all moves are known to all dialogue participants, and assume that both participants accept some rules (in particular some kind of non-repetition constraint) in order to guarantee termination.{sup:5} While, as already remarked, this guarantee cannot be extended to more general contexts, it can also be observed that works encompassing non-cooperative, and hence potentially infinite, two-party dialogues have been considered in the literature (see for instance [51], [50]). In particular, in [51] the authors describe several kinds of non-cooperative dialogue games, such as so-called stone-walling tactics. An example [51, p. 178] is the following game between two agents, the proponent (P) and the opponent (O):
       </paragraph>
       <paragraph label="Example 1">
        Example of stone-walling:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        P makes substantially the same move from {a mathematical formula}m5 onwards: this can be interpreted as being convinced that α cannot be false and that no case against α can succeed. This kind of non-cooperation structure is called mind closed and it is easy to imagine such a dialogue continuing forever if Pʼs mind does not change.
       </paragraph>
       <paragraph>
        In the previous example, stone-walling is done by one party, P. In [51, p. 181], however, the authors define a quarrel as a reciprocal stone-walling dialogue. As the authors remark, the quarrel model shows up frequently in actual dialogical practice, and they suggest that this is an efficient way of playing the game of dialectical fatigue. Dialectical fatigue settles a dispute, and declares a win for the party whose opponent just gives up{sup:6}:
       </paragraph>
       <paragraph label="Example 2">
        Example from [51, p. 182]:{a mathematical formula}
       </paragraph>
       <paragraph>
        One may wonder what the outcome of the dialogues in Examples 1 and 2 ought to be from a computational perspective. If the traditional termination rule is adopted, the outcome is that the proponent wins if the opponent concedes the main claim, and the opponent wins if the proponent retracts the main claim [75]. However, this rule cannot be applied to the non-terminating Example 1. Moreover termination in Example 2 is due to fatigue of one of the players, so that this outcome may be regarded as “non-rational”, while a “rational” development of Example 2 would be non-terminating too. One may also observe that the termination rule imposes that one position prevails over the other one, while one might consider also the case where the two positions are regarded as equally acceptable.
       </paragraph>
       <paragraph>
        Besides issues concerning dialogues, multi-agent systems provide a further case for non-terminating argumentation in presence of reasoning about mutual beliefs. In fact an agent ag1 able to reason about the beliefs of another agent ag2, may take into account also the ability of ag2 to reason about the beliefs of ag1 in turn, then both ag1 and ag2 may reason about the mutual beliefs about beliefs an so on ad libitum. This kind of problem is exemplified, in a common sense setting, by the novel by the Argentine writer Osvaldo Soriano “The longest penalty ever” [83]. Here, in a football game, a goal keeper has to reason about whether to dive to the left or to the right. The keeper knows that the kicker in the past has always kicked to the right: this would be a reason to dive to the right, but the keeper also knows the kicker knows that the keeper knows his past records (and might therefore decide to kick to the left) and this would be a reason to dive to the left, but in turn the kicker knows that the keeper knows that the kicker knows … , and the chain of mutually attacking arguments supporting the decision of diving to the left or to the right grows to infinity. Of course, in a non-cooperative context this growth cannot be prevented by mutual agreement and, for either agent, stopping the reasoning at a given level represents an arbitrary, and possibly not appropriate, choice.
       </paragraph>
      </section>
     </section>
     <section label="2.3">
      <section-title>
       Reasoning with unbounded domains
      </section-title>
      <paragraph>
       Leaving apart non-terminating situations in multi-agent systems, a further example of infinite argumentation concerns reasoning with unbounded domains like time or space.
      </paragraph>
      <paragraph>
       For instance, reactive systems are characterized by “their perpetual interaction with their environment as well as their nonterminating behaviour” [55] and as such require models able to encompass infinite objects like automata over infinite words or infinite games. While these models are suitable to analyze properties of these systems in a monotonic reasoning context, different issues arise and different formalisms are needed in case some kind of nonmonotonic reasoning is carried out.
      </paragraph>
      <paragraph>
       An example of use of argumentation in a nonmonotonic open-horizon context is provided by Pollock [74], who introduced a temporal projection principle to address the problem of argumentation-based reasoning on “stable” properties of the world. Quoting Pollock “the built-in epistemic arsenal of a rational agent must include reason-schemas of the following sort for at least some choices of P: if {a mathematical formula}t0&lt;t1, believing {a mathematical formula}P−at−t0 is a defeasible reason for the agent to believe {a mathematical formula}P−at−t1”. To allow new information to override presumptions based on out-of-date perceptions it is necessary that “the strength of the presumption that a stable property will continue to hold over time decays as the time interval increases”. Though not explicitly addressed by [74], it is straightforward to consider a spatial version of this projection principle too. For instance if one has a reason to believe that a certain site is highly dangerous due to pollution or contamination, then this belief can be reasonably projected to all the neighbor locations with strength decaying as the distance from the contaminated site increases. The set of arguments (with different strength) that can be produced on the basis of this kind of projection principles is, in general, unbounded. To cope with this, in the OSCAR implementation described in [74], Pollock restricts the use of the temporal projection principle to a specific form of backward reasoning: the agent is interested in the value of a property at a specific time instant t and checks whether there are reasons to believe that the property had a certain value at an instant {a mathematical formula}t0&lt;t. If this is the case, the reason can be projected, with decreased strength, from {a mathematical formula}t0 to t. However explicit representations of infinite arguments are needed to go beyond this specific form of reasoning.
      </paragraph>
      <paragraph>
       Formulating (defeasible) previsions on the basis of (discrete) series of past observations is a further form of reasoning involving similar issues as the set of possible observations is countably infinite and the set of actual observations may, in general, grow indefinitely. To give an example, consider previsions concerning sport events (e.g. soccer matches) based on previous performances of the teams with defeasible rules of the kind “A team which has won the majority of past matches will win future matches” and “A team which has lost the last three matches will loose next match” (or more complex ones with similar structure). Here the observation of the outcomes for a team is constantly updated after each match giving rise to new arguments representing new previsions (possibly conflicting each other and with previous ones). The set of generated “previsional” arguments is (at least in principle) infinite at each step as some of the previsions could be projected over the set of all future matches, e.g. for a very strong team with very long tradition one can, reasonably but defeasibly, foresee further wins for many years to come. It can be observed that open-ended horizons of this kind can be managed in practice by considering a finite temporal window excluding time instants which are “too far” in the past or in the future. It can be also observed, however, that if such a temporal window is very large it can be anyway more convenient in practice to adopt compact specification techniques for infinite frameworks of the kind we propose in this paper rather than to deal explicitly with all the elements of finite (but very large) sets and that, in any case, an open-ended representation is more appropriate for reasoning concerning long-term trends and scenarios.
      </paragraph>
      <paragraph>
       As already mentioned, unbounded time horizons have been considered also in game theory, where infinite games are meant to represent open-ended (e.g. life-long) interactions between the players. Different kinds of infinite games can be considered. In iterated variable-sum non-cooperative games, like the iterated prisoner dilemma [3], each player has a payoff at each turn and seeks strategies maximizing the value of the infinite series of the payoffs. Quite differently, in Gale–Stewart two-player zero-sum games, one of the two player wins depending on the membership of the infinite sequence of the moves played by both players to a predefined payoff set. Here a winning strategy for a player is a function for choosing the next move which ensures the membership (or non-membership) of the resulting infinite sequence to the payoff set. There is a potential rich interplay between infinite games and infinite argumentation. On one hand, infinite argumentation frameworks can be used as an abstract model for some game-theoretic problems and, especially thanks to their rich endowment of alternative semantics, may suggest variants and open new perspectives for these problems, in the same spirit as done by Dung for the stable marriage problem (see [37, Section 3.2]). On the other hand existing results on infinite games may provide a formal basis for the open investigation area on infinite argumentation games and the relevant strategies, building on the standpoint that non-termination does not mean necessarily indeterminacy.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Motivation summary
      </section-title>
      <paragraph>
       Summing up, it appears that investigation on infinite argumentation structures got somehow stuck in a sort of deadlock situation. From a theoretical point of view, their fundamental role has been consistently acknowledged and they have been universally encompassed at a definitional level, but actual formalisms to deal with them at an operational level, i.e. compact representations along with computational procedures, have not been developed, possibly due to a “lack of pressure” from the application side. In turn, the potential emergence of infinite argumentation structures has been evidenced in a variety of application contexts, but, possibly due to the lack of suitable operational approaches from the theoretical side, they have generally been disregarded as problematic or dealt with by adopting specific workarounds.
      </paragraph>
      <paragraph>
       The present work contributes to overcome this situation by proposing an approach to compact specification of infinite abstract argumentation frameworks endowed with effective computational procedures.
      </paragraph>
      <paragraph>
       The approach is suitable, in general, to describe infinite argumentation frameworks with some kind of regular structure. This covers, in fact, the cases of practical interest, since it corresponds to the generation of arguments (and of the attacks between them) by some systematic non-terminating mechanism, as it may occur in a multi-agent system or in other automated reasoning contexts, as described above. As it will be better commented later, the approach is also suitable to manage cases where argument generation terminates but the resulting framework is so large to make a compact representation advantageous. Our proposal can therefore be regarded as a novel enabling technique with respect to the long-term goal of deploying extended argumentation-based reasoners covering also the case of infinite (or very large) frameworks. In a shorter-term perspective, the results in this paper provide a formal basis for incorporating the management of infinite frameworks in existing implementations of Dungʼs style argumentation like ASPARTIX [47] or Dungine [84].
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Background notions
     </section-title>
     <section label="3.1">
      <section-title>
       Argumentation frameworks
      </section-title>
      <paragraph>
       In this section we review the elements of Dungʼs abstract argumentation frameworks [37] and the relevant semantics notions and basic computational issues.
      </paragraph>
      <paragraph label="Definition 1">
       An argumentation framework (af) is defined as a pair {a mathematical formula}〈X,A〉 in which {a mathematical formula}X is a set of arguments and {a mathematical formula}A⊆X×X describes the attack relation between arguments in {a mathematical formula}X, so that {a mathematical formula}〈x,y〉∈A indicates “the argument x attacks the argument y” (or, equivalently, “the argument y is attacked by the argument x”).For {a mathematical formula}S⊆X we use the notations {a mathematical formula}S− (resp. {a mathematical formula}S+) to indicate{a mathematical formula}{a mathematical formula} The arguments in {a mathematical formula}S− (resp. {a mathematical formula}S+) are said to attack (resp. be attacked by) S.When for any argument {a mathematical formula}x∈X, the set {a mathematical formula}{x}− of its attackers is finite, the argumentation framework is said to be finitary. Formally, an af, {a mathematical formula}〈X,A〉, is finitary iff for each argument {a mathematical formula}x∈X|{y:〈y,x〉∈A}| is finite.A subset {a mathematical formula}S⊆X is conflict-free if no argument in S attacks another argument in S, i.e. {a mathematical formula}(S×S)∩A is empty. An argument x is said to be acceptable with respect to {a mathematical formula}S⊆X if for any {a mathematical formula}y∈X such that {a mathematical formula}〈y,x〉∈A there is some {a mathematical formula}z∈S for which {a mathematical formula}〈z,y〉∈A, i.e. x is acceptable wrt to S if any attacker (y) of x is counterattacked by an argument (z) of S.The characteristic function of an af is the mapping {a mathematical formula}F:2X→2X where{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 2">
       Much of the development of afs has focused on the study of argumentation semantics which can be regarded as refining the informal idea of “collection of justifiable arguments in an af”. Typically this has been achieved by considering predicates that such collections must satisfy, i.e. mappings {a mathematical formula}σ:2X→{⊤,⊥} so that {a mathematical formula}Eσ(〈X,A〉) describes the set of subsets of {a mathematical formula}X that satisfy the criteria given by σ within the af{a mathematical formula}〈X,A〉. A review of the many choices that have been considered for σ may be found in Baroni and Giacomin [7]. Let {a mathematical formula}〈X,A〉 be an af and S a subset of {a mathematical formula}X.
      </paragraph>
      <list>
       <list-item label="(a)">
        S is admissible (denoted as {a mathematical formula}S∈Eadm(〈X,A〉)) if S is conflict-free and every argument in S is acceptable wrt S, i.e. {a mathematical formula}S⊆F(S).
       </list-item>
       <list-item label="(b)">
        S is a complete extension, (denoted as {a mathematical formula}S∈Ecomp(〈X,A〉)) if S is conflict-free and {a mathematical formula}x∈S if and only if x is acceptable wrt S, i.e. {a mathematical formula}S=F(S).
       </list-item>
       <list-item label="(c)">
        S is a preferred extension (denoted as {a mathematical formula}S∈Epr(〈X,A〉)) if S is a maximal (wrt ⊆) admissible set.
       </list-item>
       <list-item label="(d)">
        S is a stable extension (denoted as {a mathematical formula}S∈Estab(〈X,A〉)) if S is conflict-free and for any {a mathematical formula}y∉S, there is some {a mathematical formula}x∈S that attacks y, i.e. {a mathematical formula}S+=X∖S.
       </list-item>
       <list-item label="(e)">
        S is the grounded extension of {a mathematical formula}〈X,A〉 (denoted as {a mathematical formula}S∈Egr(〈X,A〉)) if it is the (unique) least fixed point of {a mathematical formula}F, i.e. {a mathematical formula}S=F(S) and there is no {a mathematical formula}S′⊊S such that {a mathematical formula}S′=F(S′).
       </list-item>
      </list>
      <paragraph>
       The existence and uniqueness of the grounded extension is established in [37] for all afs.
      </paragraph>
      <paragraph label="Definition 3">
       Finally, we recall the various ways in which a given argument may relate to these sets in an af{a mathematical formula}〈X,A〉. Let {a mathematical formula}x∈X and {a mathematical formula}σ:2X→{⊤,⊥}. The argument x is credulously accepted wrt σ if there is some S in {a mathematical formula}Eσ(〈X,A〉) such that {a mathematical formula}x∈S. It is said to be sceptically accepted wrt σ if every S in {a mathematical formula}Eσ(〈X,A〉) satisfies {a mathematical formula}x∈S.
      </paragraph>
      <paragraph label="Definition 4">
       The concepts of credulous and skeptical acceptance, together with the various semantics that have been put forward, naturally motivate a number of computational problems involving afs. Let {a mathematical formula}σ:2X→{⊤,⊥}.
      </paragraph>
      <list>
       <list-item label="(a)">
        {a mathematical formula}caσ is the decision problem whose instances, {a mathematical formula}〈〈X,A〉,x〉, are accepted if and only if x is credulously accepted wrt σ in {a mathematical formula}〈X,A〉.
       </list-item>
       <list-item label="(b)">
        {a mathematical formula}saσ is the decision problem whose instances, {a mathematical formula}〈〈X,A〉,x〉, are accepted if and only if x is sceptically accepted wrt σ in {a mathematical formula}〈X,A〉.
       </list-item>
       <list-item label="(c)">
        {a mathematical formula}verσ is the decision problem whose instances, {a mathematical formula}〈〈X,A〉,S〉, are accepted if and only if {a mathematical formula}S∈Eσ(〈X,A〉).
       </list-item>
       <list-item label="(d)">
        {a mathematical formula}existσ is the decision problem whose instances, {a mathematical formula}〈X,A〉, are accepted if and only if {a mathematical formula}Eσ(〈X,A〉)≠∅.
       </list-item>
       <list-item label="(e)">
        {a mathematical formula}non-emptyσ is the decision problem whose instances, {a mathematical formula}〈X,A〉, are accepted if and only if {a mathematical formula}Eσ(〈X,A〉)∉{∅,{∅}}.
       </list-item>
      </list>
      <paragraph>
       As well as the decision problems described in Definition 4 there are a range of function (or construction) problems. We focus on that of given {a mathematical formula}〈X,A〉 (for which {a mathematical formula}Eσ(〈X,A〉)≠∅) identifying all sets {a mathematical formula}S⊆X for which {a mathematical formula}S∈Eσ(〈X,A〉), denoting this problem {a mathematical formula}consσ.
      </paragraph>
      <paragraph>
       For each of the semantics σ presented in Definition 2, these computational problems have been studied in depth (within finiteafs) and their general properties are now well understood. We summarize these results in Fact 1 and Table 2.
      </paragraph>
      <paragraph label="Fact 1">
       <list>
        <list-item label="(a)">
         The function{a mathematical formula}consgris polynomial time computable, hence all of the cases (a) though (e) ofDefinition 4are polynomial time decidable for the grounded extension[37].
        </list-item>
        <list-item label="(b)">
         For{a mathematical formula}σ∈{adm, pr, comp, gr},{a mathematical formula}existσis trivial (i.e. it is always verified as a consequence of well-known results).
        </list-item>
        <list-item label="(c)">
         {a mathematical formula}existstabisnp-complete[36] (see also[49]).
        </list-item>
        <list-item label="(d)">
         For{a mathematical formula}σ∈{adm, stab, comp},{a mathematical formula}verσis decidable in polynomial-time, however{a mathematical formula}verpris conp-complete[36].
        </list-item>
        <list-item label="(e)">
         For{a mathematical formula}σ∈{adm,pr,stab,comp},{a mathematical formula}caσisnp-complete[36].
        </list-item>
        <list-item label="(f)">
         {a mathematical formula}saσis trivial for{a mathematical formula}σ=adm, polynomial for{a mathematical formula}σ=comp, conp-complete for{a mathematical formula}σ=stab,{sup:7}and{a mathematical formula}Π2p-complete for{a mathematical formula}σ=pr[41].
        </list-item>
        <list-item label="(g)">
         {a mathematical formula}non-emptyσisnp-complete for{a mathematical formula}σ∈{adm,pr,comp,stab}[36].
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       We emphasize that the classifications in Fact 1 are with respect to finite afs. For a more detailed summary of complexity and algorithms within af semantics we refer the reader to the overview of Dunne and Wooldridge [44]; complexity-theoretic treatments of both novel semantics and developments of Dungʼs original proposals may be found in, among others, [6], [46], [40], [43], [45].
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Formal languages
      </section-title>
      <paragraph>
       As to the required background on formal languages, which will be heavily used in the paper, we assume that the reader is familiar with the standard concepts and basic results in the field (to make the paper self-contained the necessary ones are provided in Appendix A). We recall only the basic definitions in this section, in order to introduce the reader to the notation used in the sequel of the paper.
      </paragraph>
      <paragraph label="Definition 6">
       An alphabet is a finite set of symbols. For an arbitrary alphabet, the notation {a mathematical formula}Σ={σ1,σ2,…,σk} will be used. A word, w, over an alphabet Σ is a finite sequence, {a mathematical formula}w=wi1wi2⋯wir of symbols from Σ. The set of all possible words is denoted as {a mathematical formula}Σ⁎. The length, {a mathematical formula}|w|, of {a mathematical formula}w∈Σ⁎ is the total number of symbols occurring in its definition. The word of length 0 in {a mathematical formula}Σ⁎ is called the empty word and is denoted as ε.For {a mathematical formula}u=ui1⋯uir and {a mathematical formula}v=vj1⋯vjs words in {a mathematical formula}Σ⁎ the word {a mathematical formula}w∈Σ⁎ formed by concatenating u with v (denoted {a mathematical formula}u⋅v) is the word {a mathematical formula}ui1…uirvj1…vjs whose length is {a mathematical formula}|u|+|v|=r+s. For any {a mathematical formula}u∈Σ⁎, {a mathematical formula}u⋅ε=ε⋅u=u, i.e. ε is an identity element in {a mathematical formula}Σ⁎ with respect to the operation ⋅ of concatenation.A language, L, over an alphabet Σ, is a subset of {a mathematical formula}Σ⁎. For languages {a mathematical formula}L1 and {a mathematical formula}L2 we define languages {a mathematical formula}L1∪L2, {a mathematical formula}L1∩L2, and {a mathematical formula}L1∖L2 in the obvious way so that the operations {a mathematical formula}{∪,∩,∖} are the standard set-theoretic ones.In addition, specific to languages,{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The language {a mathematical formula}L⁎ is sometimes referred to as the Kleene closure (or ⁎-closure) of L, while {a mathematical formula}L1/L2 is called the quotient of {a mathematical formula}L1 wrt {a mathematical formula}L2.{sup:8}
      </paragraph>
      <paragraph label="Definition 7">
       A language {a mathematical formula}L⊆Σ⁎ is a regular language if L satisfies any of the following requirements:
      </paragraph>
      <list>
       <list-item label="R1.">
        {a mathematical formula}L=∅ or {a mathematical formula}L={ε} or {a mathematical formula}L={σ} for any {a mathematical formula}σ∈Σ.
       </list-item>
       <list-item label="R2.">
        {a mathematical formula}L=L1∪L2 where {a mathematical formula}L1 and {a mathematical formula}L2 are regular languages.
       </list-item>
       <list-item label="R3.">
        {a mathematical formula}L=L1⋅L2 where {a mathematical formula}L1 and {a mathematical formula}L2 are regular languages.
       </list-item>
       <list-item label="R4.">
        {a mathematical formula}L=(L1)⁎ where {a mathematical formula}L1 is a regular language.
       </list-item>
      </list>
      <paragraph label="Definition 8">
       A formal grammar is defined via a 4-tuple, {a mathematical formula}〈Σ,V,P,S〉 where {a mathematical formula}Σ={σ1,σ2,…,σn} is a finite alphabet of terminal symbols; {a mathematical formula}V={V1,…,Vm} a finite set of variable symbols, P is a finite set of production rules, {a mathematical formula}{p1,p2,…,pr} of the form {a mathematical formula}pi:αi→βi where {a mathematical formula}αi∈(V∪Σ)⁎∖Σ⁎ and {a mathematical formula}βi∈(V∪Σ)⁎ and {a mathematical formula}S∈V is the start symbol. The language generated (see Appendix A) by a grammar G is denoted as {a mathematical formula}L(G).
      </paragraph>
      <paragraph label="Definition 9">
       A deterministic finite automaton (dfa) is defined via a 5-tuple, {a mathematical formula}M=〈Σ,Q,q0,F,δ〉 where {a mathematical formula}Σ={σ1,…,σk} is a finite set of input symbols, {a mathematical formula}Q={q0,q1,…,qm} a finite set of states; {a mathematical formula}q0∈Q the initial state; {a mathematical formula}F⊆Q the set of accepting states; and {a mathematical formula}δ:Q×Σ→Q the state transition function. A word {a mathematical formula}w=wnwn−1…w1∈Σ⁎ is accepted by the dfa{a mathematical formula}〈Σ,Q,q0,F,δ〉 if the sequence of states {a mathematical formula}qi1qi2…qin consistent with the state transition function δ which processes every symbol in w, i.e. satisfying {a mathematical formula}qi1=δ(q0,w1) and {a mathematical formula}qij=δ(qij−1,wj) for each {a mathematical formula}2⩽j⩽n, has {a mathematical formula}qin∈F. For a dfa, {a mathematical formula}M=〈Σ,Q,q0,F,δ〉, {a mathematical formula}L(M) is the subset of {a mathematical formula}Σ⁎ accepted by M.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Formalism requirements and weaknesses of naive representations
     </section-title>
     <paragraph>
      Given the goal of investigating novel approaches to deal with argumentation frameworks with a countably infinite set of arguments, we need to establish some basic criteria to evaluate the approaches themselves.
     </paragraph>
     <paragraph>
      A first basic criterion is expressiveness, namely the ability to encompass the description of a sufficiently large variety of infinite argumentation frameworks so as to cover those cases which are meaningful from a theoretical or practical perspective. These include in particular the cases of infinite argumentation frameworks already considered in the literature.
     </paragraph>
     <paragraph>
      A second criterion is tractability: the use of the formalism should not raise intractable computational problems making it impractical. In particular, we have to notice the arousal of a problem not occurring in the finite case: given that an argumentation framework {a mathematical formula}〈X,A〉 involving infinite sets can only be given through a finite encoding {a mathematical formula}η(〈X,A〉), it must be validated that an encoding {a mathematical formula}η(〈X,A〉) is indeed a valid description of someaf.
     </paragraph>
     <paragraph>
      Further, computational requirements related to the basic decision problems listed in Definition 4 have to be taken into account. A third criterion is therefore closure wrt set-theoretical operations, as they are involved in the definition and/or characterization of the fundamental properties in argumentation semantics and hence in the relevant decision procedures. To exemplify, testing whether a set of arguments is conflict-free corresponds to test whether the intersection between this set and the set of its attackers is empty. Hence, given the specification of two infinite sets of arguments in a formalism, the specification of their intersection should be captured (and, hopefully, be easily constructable) within the same formalism.
     </paragraph>
     <paragraph>
      In the view of satisfying the above requirements, a standard approach to the problem of representing an infinite collection of objects via a finite specification is to exploit formal grammars and their associated machine models.{sup:9}
     </paragraph>
     <paragraph>
      In this context, we now consider and criticize a rather straightforward approach one might adopt in describing {a mathematical formula}〈X,A〉 where the supporting set of arguments is an infinite, but enumerable, set. The idea, introduced in Definition 10 consists in describing the attack relation with a language referring to indexes in the argument enumeration.
     </paragraph>
     <paragraph label="Definition 10">
      Let {a mathematical formula}X={x1,x2,…,xn,…} be a countably infinite set of atomic arguments. A subset {a mathematical formula}A⊆X×X is naively encoded if described as the language {a mathematical formula}LA over the two symbol alphabet {a mathematical formula}{0,1} for which{a mathematical formula}
     </paragraph>
     <paragraph>
      Thus the naive encoding of a set of attacks uses a unary{sup:10} form to describe the (indices) of the source and destination arguments involved in the attack with the symbol 1 used to separate these two components (in the absence of any attack {a mathematical formula}LA=∅).
     </paragraph>
     <paragraph>
      For naive encodings one can consider formal grammars and their associated languages as a means of presenting a finite specification of {a mathematical formula}〈X,A〉, i.e. as a grammar G over alphabet {a mathematical formula}{0,1} for which {a mathematical formula}L(G)=LA. We show (proofs are given in Appendix B.1) that different choices for the family of grammars G belongs to lead invariably to the violation of (at least) one of the three criteria above, making this approach unsuitable in spite of its apparent simplicity.
     </paragraph>
     <paragraph label="Proposition 1">
      We start with an unsurprising property of naive encodings. For{a mathematical formula}Xas introduced inDefinition 10, there are choices of{a mathematical formula}A⊆X×Xsuch that there is no formal grammar, G with{a mathematical formula}L(G)=LA⊆{0i⋅1⋅0j:i,j⩾1}.
     </paragraph>
     <paragraph>
      The issue of infinite attack structures which cannot be described within naive encodings may, justifiably, be seen as a purely technical limitation as far as the families of afs so affected are unlikely to feature in applications (see the proof of Proposition 1). It turns out however that, for unrestricted grammars, the criterion of tractability is not satisfied since the problem of determining if a naive encoding does indeed describe someaf is not semi-decidable.
     </paragraph>
     <paragraph label="Proposition 2">
      Given an arbitrary (i.e. unrestricted) grammar G over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is not semi-decidable, i.e. there is no TM program which given (a description of) G as input halts and accepts precisely those G for which{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}.
     </paragraph>
     <paragraph label="Proposition 3">
      In fact, results analogous to Proposition 2 continue to hold even if we use the less expressive class of context-sensitive grammars. Given an arbitrary context-sensitive grammar, G, over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is not semi-decidable.
     </paragraph>
     <paragraph>
      The problem evidenced in Proposition 2, Proposition 3 does not hold when considering context-free languages.
     </paragraph>
     <paragraph label="Proposition 4">
      Given an arbitrary context-free grammar (cfg), G, over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is decidable.
     </paragraph>
     <paragraph>
      Context-free languages, however, do not satisfy the property of closure: it is well-known that they are not closed under intersection, complement and set difference.
     </paragraph>
     <paragraph>
      Turning to regular languages, as with the context-free case one can decide if a given dfa accepts the naive encoding of some {a mathematical formula}〈X,A〉.
     </paragraph>
     <paragraph label="Proposition 5">
      Given{a mathematical formula}M=〈Q,{0,1},q0,F,δ〉adfaover the alphabet{a mathematical formula}{0,1}there is a polynomial (in{a mathematical formula}|Q|) algorithm that decides{a mathematical formula}L(M)⊆{0i⋅1⋅0j:i,j⩾1}.
     </paragraph>
     <paragraph>
      Moreover, regular languages are fully satisfactory as far as closure properties are concerned (see Appendix AFact 6). Unfortunately, however, they feature very limited expressive power in terms of describing naive encodings.
     </paragraph>
     <paragraph label="Proposition 6">
      Let L be any subset of{a mathematical formula}{0i⋅1⋅0j:i,j⩾1}with the following property: there are infinitely many values of k such that{a mathematical formula}{0k⋅1⋅0m:m⩾1}∩L≠∅ and for all{a mathematical formula}0n⋅1⋅0m∈L,{a mathematical formula}n⩽m. Then L is not a regular language.
     </paragraph>
     <paragraph>
      Notice that one consequence of Proposition 6 is that the naive encoding of the infinite af whose only attacks are self-attacks, i.e. {a mathematical formula}〈p,p〉 for all {a mathematical formula}p∈X fails to be a regular language.{sup:11}
     </paragraph>
     <paragraph>
      In summary, although naive representations have an appealing structural simplicity, if adopted one has to contend with issues of undecidability (for the most expressive grammar classes), lack of closure (for context-free languages) or limited expressiveness (for regular languages).
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      A generic regular expression formalism and its properties
     </section-title>
     <paragraph>
      The issues identified with so-called naive representations in the preceding section largely stem from the following fact: given that encodings of arguments, {a mathematical formula}pi∈X are effectively achieved for free – that is, for all natural numbers k, {a mathematical formula}pk∈X and no further analysis is needed – the task of describing {a mathematical formula}〈X,A〉 comes down to describing the (infinite) set {a mathematical formula}A. In assuming that {a mathematical formula}pk∈X for any k, however, this severely limits the extent to which {a mathematical formula}A can be described in a computationally useful manner.
     </paragraph>
     <paragraph>
      In this section we present an alternative method for describing infinite afs, {a mathematical formula}〈X,A〉. The basic idea is that, rather than assuming {a mathematical formula}X is understood simply as {a mathematical formula}{p1,p2,…,pn,…}, we consider arguments in {a mathematical formula}X to be specified so that there is some structural aspect linking them. In this way we can then present very general specifications of the attack structure that are conditioned solely in terms of the specific arguments in {a mathematical formula}X.
     </paragraph>
     <paragraph>
      In a nutshell, the proposal consists of two basic elements: a description of the (infinite) set of arguments through an appropriate argument encoding relying on some finite automaton, and a description of the attack relations linking arguments together through an attack expression. More precisely, the attack expression specifies a mapping between regular expressions describing sets of arguments, with the intended meaning that the set S is attacked by the elements of the set obtained from S through the mapping. The combination of the automaton describing the set of arguments and of the attack expression will be called the afspecification.
     </paragraph>
     <paragraph label="Example 3">
      To illustrate our approach we will use some “simple” infinite structures, which can be regarded as basic patterns, possibly to be reused in the context of more articulated infinite argumentation frameworks. A first example of basic structure (related to endless debates, or “chicken and egg” style dilemmas, or the kicker and goalkeeper example) is an infinite sequence of arguments linked by the attack relation. We note that this kind of structure admits two different instantiations: one where the sequence “starts” with an attacked argument (which corresponds to the examples mentioned above) and a dual one where the sequence “starts” with an attacking argument. They correspond respectively to the argumentation frameworks {a mathematical formula}AFD and {a mathematical formula}AFU (see Fig. 1) defined as follows: {a mathematical formula}AFD=〈X,AD〉 with {a mathematical formula}X={A1,A2,…,An,…} and {a mathematical formula}AD={〈Ai+1,Ai〉:i⩾1} and {a mathematical formula}AFU=〈X,AU〉 with {a mathematical formula}X as above and {a mathematical formula}AU={〈Ai,Ai+1〉:i⩾1}. Another example of basic structure, related to temporal projection, is a couple of “parallel” sequences of arguments where corresponding arguments in the sequences mutually attack each other. This kind of structure may correspond to conflicting information acquired at the same time for the same entity (e.g. a physical quantity) from two different and equally reliable sources A and B (e.g. two different experiments or measurements). The conflict between the initial arguments corresponding to the readings from the two sources is then projected over time. This can be represented by the argumentation framework {a mathematical formula}AFM=〈XM,AM〉 with {a mathematical formula}XM={A1,A2,…,An,…}∪{B1,B2,…,Bn,…} and {a mathematical formula}AM={〈Ai,Bi〉:i⩾1}∪{〈Bi,Ai〉:i⩾1} (see Fig. 2(a)). To provide a slightly more complicated structure, we will consider also a variant of this temporal projection situation, with a third source C which is in agreement with the source A and is considered more reliable than A and B. This can be represented by the argumentation framework {a mathematical formula}AFR=〈XR,AR〉 with {a mathematical formula}XR={A1,A2,…,An,…}∪{B1,B2,…,Bn,…}∪{C1,C2,…,Cn,…} and {a mathematical formula}AR={〈Ai,Bi〉:i⩾1}∪{〈Bi,Ai〉:i⩾1}∪{〈Ci,Bi〉:i⩾1} (see Fig. 2(b)).
     </paragraph>
     <section label="5.1">
      <section-title>
       Argument encoding
      </section-title>
      <paragraph label="Definition 11">
       Central to our formalism is the notion of “argument encoding” as a given set of words over some base set of symbols. Let {a mathematical formula}Σ={σ1,σ2,…,σk} be an alphabet. An argument encoding over Σ is any regular language {a mathematical formula}X⊆Σ⁎∖{ε}.
      </paragraph>
      <paragraph>
       Thus a (possibly infinite) set of arguments, {a mathematical formula}X, corresponds to some regular language over a finite alphabet Σ.
      </paragraph>
      <paragraph label="Example 3">
       continuedThe notion of argument encoding is very general and, in fact, leaves completely open the choice of the alphabet and of the regular language to be adopted to represent a given infinite structure. Considering the frameworks {a mathematical formula}AFD and {a mathematical formula}AFU, featuring a simple “linear” structure, the straightforward choice we will follow uses an alphabet consisting of a unique symbol, actually {a mathematical formula}Σ={0}, and the regular language {a mathematical formula}0⋅0⁎, by adopting the correspondence {a mathematical formula}0i≜Ai. For frameworks with more articulated structures like {a mathematical formula}AFM and {a mathematical formula}AFR, one might consider using an alphabet with a symbol for each class of arguments, e.g. {a mathematical formula}ΣM={0,1} and {a mathematical formula}ΣR={0,1,2}. Accordingly the regular languages to encode {a mathematical formula}XM and {a mathematical formula}XR would be {a mathematical formula}0⋅0⁎∪1⋅1⁎ and {a mathematical formula}0⋅0⁎∪1⋅1⁎∪2⋅2⁎ respectively, with the correspondences {a mathematical formula}0i≜Ai, {a mathematical formula}1i≜Bi, {a mathematical formula}2i≜Ci. As we will see later, however, a different approach will be adopted since it is more suitable for the purpose of representation of the attack relation. In fact, we will use again the alphabet {a mathematical formula}Σ={0}, and the regular language {a mathematical formula}0⋅0⁎ for all arguments, putting the different classes of arguments in correspondence with distinct sub-languages of {a mathematical formula}0⋅0⁎. In fact for {a mathematical formula}AFM we will adopt the correspondence {a mathematical formula}0⋅(00)i≜Ai+1 and {a mathematical formula}00⋅(00)i≜Bi+1 for {a mathematical formula}i⩾0, i.e. {a mathematical formula}0≜A1, {a mathematical formula}00≜B1, {a mathematical formula}000≜A2, {a mathematical formula}0000≜B2 and so on. Similarly for {a mathematical formula}AFR we will adopt the correspondence {a mathematical formula}0⋅(000)i≜Ai+1, {a mathematical formula}00⋅(000)i≜Bi+1 and {a mathematical formula}000⋅(000)i≜Ci+1 for {a mathematical formula}i⩾0.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Attack expression
      </section-title>
      <paragraph>
       The increased expressivity and computational effectiveness of our approach (in comparison to naive encodings), derives from the mechanism used to describe sets of attacks. We seek to develop formalisms by which the set of arguments (in {a mathematical formula}X) that “attack” in the standard sense of [37] some specified subset {a mathematical formula}S⊆X may be presented, i.e. for defining “suitable” functions {a mathematical formula}μ:2X→2X, such that, for a given set of arguments S, {a mathematical formula}μ(S) specifies the set of arguments attacking S, i.e. {a mathematical formula}μ(S)=S−. By “suitable” we recognize that there are certain natural conditions that such functions ought to respect.
      </paragraph>
      <paragraph label="Definition 12">
       A mapping {a mathematical formula}μ:2Σ⁎→2Σ⁎ is reasonable if
      </paragraph>
      <list>
       <list-item label="R1.">
        {a mathematical formula}∀S⊆Σ⁎, {a mathematical formula}μ(S)=⋃u∈Sμ({u}). (Additivity)
       </list-item>
       <list-item label="R2.">
        {a mathematical formula}∀S⊆Σ⁎ for which S is a regular language, {a mathematical formula}μ(S) is a regular language. (Closure)
       </list-item>
      </list>
      <paragraph>
       We observe that all of these conditions hold for the finite instantiations of {a mathematical formula}A in Dungʼs afs. For the development we consider to infinite {a mathematical formula}X, the additivity restriction states that attacks on S must be associated with individual arguments in S and not with S as a whole, i.e. we can construct the set of attacks on S simply by considering attacks on the members of S in turn.{sup:12} It may be noted that additivity implies that the mapping is also monotonic, i.e. if {a mathematical formula}R⊆S then {a mathematical formula}μ(R)⊆μ(S). Thus additive mappings reflect the natural condition that attacks on a set of arguments, S, cannot be eliminated simply by adding more arguments to S: notice that by disallowing explicit removal of an attack on a set (in the definition of μ) we require defenses to attacks to be made by direct counterattacks. In this way we preserve the concept of “u is acceptable to S” by identifying any {a mathematical formula}v∈S such that {a mathematical formula}v∈μ({x}) for each {a mathematical formula}x∈μ({u}).
      </paragraph>
      <paragraph>
       While the additivity may be justified through semantic considerations, our reason for imposing “closure wrt regular languages” is motivated by computational concerns: given that {a mathematical formula}S⊆X (if regular) has a simple computational representation (e.g. as a dfa accepting exactly the arguments in S) it is desirable that subsets of {a mathematical formula}X “related to” S, e.g. through the property of attacking its members, can also be so described. In principle this allows for the outcome of {a mathematical formula}μ(S) to be described as a dfa.
      </paragraph>
      <paragraph>
       Finally the concept of invertibility addresses issues arising with the “inverse” mapping: just as {a mathematical formula}μ:2X→2X describes the subset of {a mathematical formula}X that attacks a given {a mathematical formula}S⊆X, so {a mathematical formula}ν:2X→2X describes the subset of {a mathematical formula}X that is attacked by S. The justification of additivity and closure properties is on similar grounds to those used with μ.
      </paragraph>
      <paragraph label="Definition 13">
       Given the basic desiderata that mappings defining attacks ought to satisfy stated in Definition 12, we now turn to the issue of how general functions satisfying these desiderata can be constructed. For this purpose we introduce the concept of attack expressions over a finite alphabet Σ. A well-formed attack expression (ae) over Σ is a sentence constructed by the following rules.
      </paragraph>
      <list>
       <list-item label="1.">
        For all {a mathematical formula}σi∈Σ, {a mathematical formula}σi is an attack expression over Σ.
       </list-item>
       <list-item label="2.">
        The symbol I (for identity) is an attack expression over Σ.
       </list-item>
       <list-item label="3.">
        If p and q are two attack expressions over Σ then {a mathematical formula}p∪q is also an attack expression over Σ.
       </list-item>
       <list-item label="4.">
        If p is an attack expression and {a mathematical formula}KΣ is a regular expression (using the operations {a mathematical formula}{+,⋅,⁎}) over only symbols from Σ (i.e. the identity symbol I does not occur in {a mathematical formula}KΣ) then all of {a mathematical formula}KΣ⋅p, {a mathematical formula}p⋅KΣ, {a mathematical formula}p/KΣ, {a mathematical formula}KΣ/p and {a mathematical formula}p∩KΣ are attack expressions.
       </list-item>
       <list-item label="5.">
        If p is an attack expression over Σ then (p) and {a mathematical formula}γ(p) for {a mathematical formula}γ∈{hd,tl} are attack expressions over Σ.
       </list-item>
       <list-item label="6.">
        The only attack expressions over Σ are those formed by a finite number of applications of (1) through (5).
       </list-item>
      </list>
      <paragraph label="Definition 14">
       Let {a mathematical formula}AE(Σ) denote the set of all well-formed attack expressions over Σ and for {a mathematical formula}a∈AE(Σ) let {a mathematical formula}size(a) denote the number of operations (i.e. applications of rules 3–5) used to define a. The key motivation for this formalism is in describing the attack structure relating a set of arguments. Hence each {a mathematical formula}a∈AE(Σ), defines a mapping {a mathematical formula}a̲:2Σ⁎→2Σ⁎ as follows Let {a mathematical formula}p∈AE(Σ) and {a mathematical formula}S⊆Σ⁎, the set {a mathematical formula}p̲(S) is given by the rules below:{a mathematical formula} The unary operations – {a mathematical formula}{hd,tl} – are defined as follows for {a mathematical formula}S⊆Σ⁎:{a mathematical formula}{a mathematical formula} Note that {a mathematical formula}tl({σ})={ε} and {a mathematical formula}tl(∅)=hd({ε})=hd(∅)=∅.
      </paragraph>
      <paragraph>
       Before analyzing the properties of the proposed attack expressions, we comment on the set of operations – {a mathematical formula}{∪,⋅KΣ,KΣ⋅,/KΣ,KΣ/,∩KΣ,hd,tl} that are provided. In particular we note the limited way in which ⋅ and ∩ may be used and the absence of complement and Kleene ⁎ operators, despite the fact that regular languages are closed under the last two of these. The immediate problem with allowing arbitrary usage of ⋅ and ∩ concerns the fact that, for expressions such as {a mathematical formula}p⋅q or {a mathematical formula}p∩q we cannot, in general, guarantee that the mappings {a mathematical formula}p̲⋅q̲ or {a mathematical formula}p̲∩q̲ are additive. For example, suppose that {a mathematical formula}p=q=I, {a mathematical formula}Σ={0,1} and {a mathematical formula}S={0k:k⩾1}. Then {a mathematical formula}(p̲⋅q̲)(S)=S∖{0}, however{a mathematical formula} Similarly if {a mathematical formula}p=I, {a mathematical formula}q=tl(I), {a mathematical formula}S={1k:k⩾1}∪{0⋅1k:k⩾1} we get{a mathematical formula} but{a mathematical formula} We could, of course, avoid this by directly defining {a mathematical formula}μ(S) to be {a mathematical formula}⋃w∈Sμ({w}), i.e. restricting the domain of μ to {a mathematical formula}Σ⁎. In this case, however, we cannot always ensure that {a mathematical formula}p̲⋅q̲ preserves regularity. For example, using {a mathematical formula}p=I, {a mathematical formula}q={1}⋅I with {a mathematical formula}S={0k:k⩾1} (which is a regular language),{a mathematical formula} is not regular. This behavior arises since regular languages are not closed under unbounded union (only with respect to finite union). The issues underpinning the absence of ⋅ from the class of allowed operations are easily seen also to arise were ⁎ to be added. Finally allowing complementation would lead to mappings which were not monotonic (and thus could not be additive).
      </paragraph>
      <paragraph>
       Theorem 1 provides a first confirmation of the soundness of the proposed approach by showing{sup:13} that the mappings arising via attack expressions have appropriate properties.
      </paragraph>
      <paragraph label="Theorem 1">
       Let{a mathematical formula}p∈AE(Σ)be any attack expression over Σ. The mapping{a mathematical formula}p̲:2Σ⁎→2Σ⁎is reasonable.
      </paragraph>
     </section>
     <section label="5.3">
      af specification
      <paragraph>
       We now have the basic elements of our formal descriptive mechanism for infinite frameworks, the idea being that the set of arguments is specified as a regular language {a mathematical formula}X⊆Σ⁎ and the attack relation is specified through an attack expression a. In fact, given an element v of {a mathematical formula}X the set T of attackers of v might be defined as {a mathematical formula}T=a̲({v}). Considering now a set {a mathematical formula}S⊆X, the set of attackers of S is given by {a mathematical formula}{v∈Σ⁎:∃u∈S s.t. v∈a̲({u})} which is equal to {a mathematical formula}a̲(S) by additivity of {a mathematical formula}a̲. However, it should be noted that while the attack relation must be a subset of {a mathematical formula}X×X, it might be the case that for some {a mathematical formula}S⊆Xa̲(S)⊈X. To fix this (actually minor) problem we need to introduce some further notation.
      </paragraph>
      <paragraph label="Definition 15">
       Let {a mathematical formula}μ:2Σ⁎→2Σ⁎ and {a mathematical formula}X⊆Σ⁎ a regular language, we define {a mathematical formula}μX:2X→2X as{a mathematical formula}
      </paragraph>
      <paragraph>
       Proposition 7 shows that considering {a mathematical formula}μX instead of μ does not affect the property of being a reasonable mapping.
      </paragraph>
      <paragraph label="Proposition 7">
       If μ is a reasonable mapping over the domain{a mathematical formula}2Σ⁎then{a mathematical formula}μXis a reasonable mapping over the domain{a mathematical formula}2X.
      </paragraph>
      <paragraph>
       We can now formally introduce the notion of af specification.
      </paragraph>
      <paragraph label="Definition 16">
       Let Σ be a finite alphabet of symbols and {a mathematical formula}X⊆Σ⁎ be a regular language. An afspecification (afs) is a pair {a mathematical formula}〈M,a〉 where {a mathematical formula}M=〈Q,Σ,q0,δ,F〉 is some finite automaton{sup:14} for which {a mathematical formula}L(M)=X and {a mathematical formula}a∈AE(Σ) is a well-formed attack expression over Σ. Given an afs{a mathematical formula}〈M,a〉, the relation {a mathematical formula}→a over {a mathematical formula}X×X is defined by {a mathematical formula}u→av (read as “v is attacked by u”) if {a mathematical formula}u∈a̲X({v}). We call {a mathematical formula}〈X,→a〉 the argumentation framework induced by {a mathematical formula}〈M,a〉.
      </paragraph>
      <paragraph>
       Note that, given an afspecification and a set {a mathematical formula}S⊆X, the set of attackers of S denoted as {a mathematical formula}πa−(S)≜{v∈Σ⁎:∃u∈S s.t. v→au} is equal to {a mathematical formula}a̲X(S), by additivity.
      </paragraph>
      <paragraph label="Example 3">
       continuedContinuing with the examples, we can now complete the specification of {a mathematical formula}AFU, {a mathematical formula}AFD, {a mathematical formula}AFM and {a mathematical formula}AFR by identifying the relevant attack expressions.As to {a mathematical formula}AFU we note that, for a generic {a mathematical formula}i⩾2 the argument (corresponding to) {a mathematical formula}0i is attacked by the argument {a mathematical formula}0i−1, leading to the attack expression {a mathematical formula}a=tl(I). Note that {a mathematical formula}a̲({0})={ε} but {a mathematical formula}a̲X({0})=∅. On the other hand, in {a mathematical formula}AFD, for a generic {a mathematical formula}i⩾1, the argument {a mathematical formula}0i is attacked by the argument {a mathematical formula}0i+1, leading to the attack expression {a mathematical formula}I⋅0.{sup:15}{a mathematical formula}AFM requires a more articulated attack expression. Here each argument {a mathematical formula}Ai corresponding to {a mathematical formula}0⋅(00)i−1 is attacked by the argument {a mathematical formula}Bi corresponding to {a mathematical formula}00⋅(00)i−1 and viceversa each argument {a mathematical formula}Bi is attacked by the argument {a mathematical formula}Ai. As to the attacks from a generic {a mathematical formula}Bi to a generic {a mathematical formula}Ai we note that the attacker can simply be obtained by adding a trailing 0. We cannot however use the simple expression {a mathematical formula}I⋅0 as above since this would entail not only that any {a mathematical formula}Ai is attacked by {a mathematical formula}Bi but also that any {a mathematical formula}Bi is attacked by {a mathematical formula}Ai+1 which is not the case. The attack expression has therefore to specify that the trailing 0 applies only to the elements of the sub-language {a mathematical formula}0⋅(00)⁎, giving rise to the expression {a mathematical formula}(I∩(0⋅(00)⁎))⋅0. Similarly, the attacks from a generic {a mathematical formula}Ai to a generic {a mathematical formula}Bi can be obtained using the tl operator and properly restricting its application, giving rise to {a mathematical formula}tl(I∩((00)⋅(00)⁎)). The complete attack expression of {a mathematical formula}AFM is obtained by the union of the two expressions above: {a mathematical formula}aM=((I∩(0⋅(00)⁎))⋅0)∪tl(I∩((00)⋅(00)⁎)).As to {a mathematical formula}AFR, we note first that the attacks between arguments {a mathematical formula}Ai and {a mathematical formula}Bi are analogous to the case of {a mathematical formula}AFM with the difference that {a mathematical formula}Ai corresponds to {a mathematical formula}0⋅(000)i−1 and {a mathematical formula}Bi corresponds to {a mathematical formula}00⋅(000)i−1. Hence, similarly to above, we obtain the expressions {a mathematical formula}(I∩(0⋅(000)⁎))⋅0 and {a mathematical formula}tl(I∩((00)⋅(000)⁎)). As to the attacks from an argument {a mathematical formula}Ci, corresponding to {a mathematical formula}000⋅(000)i−1, to an argument {a mathematical formula}Bi corresponding to {a mathematical formula}00⋅(000)i−1 we note that they can again be represented through the addition of a trailing 0 yielding {a mathematical formula}(I∩(00⋅(000)⁎))⋅0. The complete attack expression of {a mathematical formula}AFR turns out to be {a mathematical formula}aR=((I∩(0⋅(000)⁎))⋅0)∪(tl(I∩((00)⋅(000)⁎)))∪((I∩(00⋅(000)⁎))⋅0).
      </paragraph>
      <paragraph>
       As a further remark, we note that the attack expression I captures the case of an argumentation framework where each argument attacks itself (and only itself) which has been shown not to be representable in the naive approach using regular languages in Section 4.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Inverting the attack expression
      </section-title>
      <paragraph>
       Definition 16 provides a formal specification of the attackers of an element (subset) of {a mathematical formula}Σ⁎. However it is useful to consider also the specification of the arguments attacked by a given element (subset) of {a mathematical formula}Σ⁎. This is possible since the function {a mathematical formula}a̲ is invertible as shown below by Theorem 2. In particular, the proof of the theorem (see Appendix B.2) allows one to construct from a given {a mathematical formula}a∈AE(Σ) a related expression {a mathematical formula}a+ with the property that for all {a mathematical formula}u,v∈Σ⁎, {a mathematical formula}u∈a̲({v}) if and only if {a mathematical formula}v∈a̲+({u}). The expressions {a mathematical formula}a+ use the same basic elements as {a mathematical formula}AE(Σ) plus the {a mathematical formula}rev() operator,{sup:16} which does not affect any of the desired properties.
      </paragraph>
      <paragraph>
       The following properties, shown to be valid in the proof of Theorem 2, provide the basic elements to derive the expressions {a mathematical formula}a+ from {a mathematical formula}a̲.
      </paragraph>
      <paragraph label="Fact 2">
       <list>
        <list-item label="1.">
         If{a mathematical formula}a=σithen{a mathematical formula}a̲+(S)=tl(I∩σi)⋅Σ⁎; If{a mathematical formula}a=Ithen{a mathematical formula}a̲+(S)=S.
        </list-item>
        <list-item label="2.">
         If{a mathematical formula}a=b∪c, then{a mathematical formula}a̲+(S)=b̲+(S)∪c̲+(S).
        </list-item>
        <list-item label="3.">
         If{a mathematical formula}a=b⋅KΣ, then{a mathematical formula}a̲+(S)=b̲+(S/KΣ).
        </list-item>
        <list-item label="4.">
         If{a mathematical formula}a=KΣ⋅b, then{a mathematical formula}a̲+(S)=b̲+(rev(rev(S)/rev(KΣ))).
        </list-item>
        <list-item label="5.">
         If{a mathematical formula}a=b/KΣ, then{a mathematical formula}a̲+(S)=b̲+(S⋅KΣ).
        </list-item>
        <list-item label="6.">
         If{a mathematical formula}a=KΣ/b, then{a mathematical formula}a̲+(S)=b̲+(rev(rev(KΣ)/rev(S))).
        </list-item>
        <list-item label="7.">
         If{a mathematical formula}a=b∩KΣ, then{a mathematical formula}a̲+(S)=b̲+(S∩KΣ).
        </list-item>
        <list-item label="8.">
         If{a mathematical formula}a=hd(b), then{a mathematical formula}a̲+(S)=b̲+(((S∩Σ)⋅Σ⁎)).
        </list-item>
        <list-item label="9.">
         If{a mathematical formula}a=tl(b), then{a mathematical formula}a̲+(S)=b̲+(Σ⋅S).
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Theorem 2">
       Let{a mathematical formula}〈M,a〉be anafswith{a mathematical formula}L(M)=Xand{a mathematical formula}a∈AE(Σ). The mapping{a mathematical formula}a̲+:2Σ⁎→2Σ⁎, defined as{a mathematical formula}a̲+(S)={v∈Σ⁎:∃u∈Ss.t.u∈a̲(v)}is closed wrt regular languages.
      </paragraph>
      <paragraph>
       It remains now to show that the inverse of an attack expression actually provides the set of the arguments attacked by a set.
      </paragraph>
      <paragraph label="Proposition 8">
       Let{a mathematical formula}〈M,a〉be anafswith{a mathematical formula}L(M)=Xand{a mathematical formula}a∈AE(Σ). Define the mapping,{a mathematical formula}πa+:2X→2Xby{a mathematical formula}It holds that{a mathematical formula}πa+(S)=a̲X+(S).
      </paragraph>
      <paragraph>
       By Theorem 2 and the regularity of {a mathematical formula}X it is easy to see that {a mathematical formula}πa+ is additive and preserves regularity.
      </paragraph>
      <paragraph label="Example 3">
       continuedCompleting our example, we can now derive the mapping {a mathematical formula}πa+ for {a mathematical formula}AFU, {a mathematical formula}AFD, {a mathematical formula}AFM and {a mathematical formula}AFR.As to {a mathematical formula}AFU from the attack expression {a mathematical formula}tl(I) applying Fact 2.9 (and 2.1 for I) we get {a mathematical formula}a̲+(S)=I(Σ⋅S)=Σ⋅S=0⋅S. As to {a mathematical formula}AFD, from the attack expression {a mathematical formula}I⋅0 applying Fact 2.3 (and 2.1 for I) we get {a mathematical formula}a̲+(S)=I(S/0)=S/0 which (in view of {a mathematical formula}S⊆0⋅0⁎) is equivalent to {a mathematical formula}tl(S).As to {a mathematical formula}AFM, given the attack expression {a mathematical formula}aM=((I∩(0⋅(00)⁎))⋅0)∪tl(I∩((00)⋅(00)⁎)) by Fact 2.2 we can examine separately the two terms {a mathematical formula}b=((I∩(0⋅(00)⁎))⋅0) and {a mathematical formula}c=tl(I∩((00)⋅(00)⁎)). As to {a mathematical formula}b̲+, from 2.3 we get {a mathematical formula}d̲+(S/0) with {a mathematical formula}d=(I∩(0⋅(00)⁎)). Applying then 2.7 (and 2.1 for I) we get {a mathematical formula}b̲+(S)=(S/0)∩(0⋅(00)⁎). As to {a mathematical formula}c̲+, from Fact 2.9 we get {a mathematical formula}e̲+(Σ⋅S) with {a mathematical formula}e=I∩((00)⋅(00)⁎). Applying again 2.7 and 2.1 and taking into account {a mathematical formula}Σ={0} we get {a mathematical formula}c̲+(S)=(0⋅S)∩((00)⋅(00)⁎). Summing up {a mathematical formula}aM̲+(S)=((S/0)∩(0⋅(00)⁎))∪((0⋅S)∩((00)⋅(00)⁎)).The case of {a mathematical formula}AFR is analogous, yielding {a mathematical formula}aR̲+(S)=((S/0)∩(0⋅(000)⁎))∪((0⋅S)∩((00)⋅(000)⁎))∪((S/0)∩(00⋅(000)⁎)).
      </paragraph>
     </section>
     <section label="5.5">
      Representation of finite afs and combination of af specifications
      <paragraph>
       The previous sections show how the proposed af specification mechanism can deal with (up to now simple) infinite frameworks. One may then wonder whether this mechanism is suitable to describe finiteafs as well or its structure is somehow bounded to the infinite case. In fact this problem does not arise: any finite af{a mathematical formula}〈X,A〉 can be easily described via the mechanisms proposed in this paper. Noting that {a mathematical formula}X is finite simply choose {a mathematical formula}Σ=X as the underlying alphabet, and let {a mathematical formula}M be the trivial associated automaton. The set {a mathematical formula}A is a finite subset of {a mathematical formula}Σ×Σ and treated directly as a regular language {a mathematical formula}LA={x⋅y:〈x,y〉∈A}. We then have {a mathematical formula}a∈AE(Σ) specified by {a mathematical formula}a=hd((Σ⋅I)∩LA), giving {a mathematical formula}πa−(S)=hd((Σ⋅S)∩LA) and (after some manipulation) {a mathematical formula}πa+(S)=tl((S⋅Σ)∩LA).
      </paragraph>
      <paragraph>
       For example if {a mathematical formula}X={w,x,y,z} and {a mathematical formula}A={〈w,x〉,〈x,y〉,〈y,z〉,〈z,w〉} then {a mathematical formula}LA={wx,xy,yz,zw} with, for example,{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Having shown that finite afs do not raise, per se any expressiveness concern, a further important question has to be addressed: one may wonder whether it is possible to give the specification of an af resulting from the combination of a finite subframework with one or more infinite subframeworks, with the different subframeworks linked together by finite attack relations. This kind of combined specification is particularly relevant in practice. To have an example, consider again the frameworks {a mathematical formula}AFM and {a mathematical formula}AFR, concerning cases of temporal projection with initial information acquired from different sources at the same time. Clearly, one has also to cover the case where information is acquired from different sources at different times. As a very simple example, consider a slight modification of the situation represented by {a mathematical formula}AFR, so that information from the third more reliable source, C, is acquired with some delay (to keep things simple, let say one time instant later) wrt the information from sources A and B. This situation could be represented with a framework composed by two subframeworks, a finite one, consisting of two mutually attacking arguments corresponding to the information initially acquired from A and B, and an infinite one, with the same structure as {a mathematical formula}AFR. More generally, frameworks with this kind of structure correspond to cases where a reasoning (or dialogue) process enters a non-terminating iterative behavior after some initial non-iterative steps, which is clearly a more general (and possibly more common) situation wrt the cases of “iterative behavior from the beginning” we have considered in our simple illustrative examples. We will now show how this kind of structure can be captured in our formalism.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}AF0=〈X0,A0〉 a finite af and {a mathematical formula}AF1=〈X1,A1〉,…,AFn=〈Xn,An〉 a finite sequence of infinite frameworks with specifications {a mathematical formula}〈M1,a1〉,…,〈Mn,an〉 such that for each {a mathematical formula}1⩽i⩽nL(Mi)=Xi⊆Σi⁎ and {a mathematical formula}ai∈AE(Σi).
      </paragraph>
      <paragraph>
       Letting {a mathematical formula}Σ0=X0 we assume without loss of generality that the alphabets used for the different frameworks are pairwise disjoint namely, for {a mathematical formula}0⩽i⩽n, {a mathematical formula}0⩽j⩽n, {a mathematical formula}i≠j, {a mathematical formula}Σi∩Σj=∅.
      </paragraph>
      <paragraph>
       Consider now the problem of specifying a framework {a mathematical formula}AF∪=〈X∪,A∪〉 with the following structure:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}X∪=⋃i∈{0,…,n}Xi;
       </list-item>
       <list-item label="•">
        {a mathematical formula}A∪=⋃i∈{0,…,n}Ai∪⋃i,j∈{0,…,n},i≠jAi,j, where {a mathematical formula}Ai,j is an arbitrary finite subset of {a mathematical formula}Xi×Xj.
       </list-item>
      </list>
      <paragraph>
       In words, {a mathematical formula}AF∪ includes all the subframeworks {a mathematical formula}AF0,…AFn with their “internal” attack relations {a mathematical formula}A0,…,An plus new arbitrary finite attack relations {a mathematical formula}Ai,j linking each pair of subframeworks and representing the additional attacks from elements of {a mathematical formula}Xi to elements of {a mathematical formula}Xj.
      </paragraph>
      <paragraph>
       The question is now how to derive the specification of {a mathematical formula}AF∪ from the specifications of the subframeworks {a mathematical formula}AF0,…,AFn and from the new attacks {a mathematical formula}Ai,j. As to the reference alphabet, clearly {a mathematical formula}Σ∪=⋃i∈{0,…,n}Σi. Thanks to the hypothesis of disjointness of the alphabets {a mathematical formula}Σi, we know that also the sets of arguments {a mathematical formula}Xi are disjoint and we can safely define {a mathematical formula}X∪=⋃i∈{0,…,n}Xi. As {a mathematical formula}X∪ is the union of a set of regular languages it is a regular language too (Fact 4, Appendix A), whose automaton {a mathematical formula}M∪ can be effectively derived from the automata {a mathematical formula}Mi (Fact 6(b), Appendix A).
      </paragraph>
      <paragraph>
       As to the attack expression, it has to preserve, in the new framework, the attack relations {a mathematical formula}A0,…,An of all the subframeworks and include the new attacks {a mathematical formula}Ai,j.
      </paragraph>
      <paragraph>
       As to {a mathematical formula}A0, the corresponding attack expression in {a mathematical formula}AF∪ is exactly the same as for {a mathematical formula}A0 in isolation. Letting {a mathematical formula}L0={x⋅y:〈x,y〉∈A0}, the attack expression{sup:17} for the finite subframework is {a mathematical formula}aˆ0=hd((Σ0⋅I)∩L0).
      </paragraph>
      <paragraph>
       As to the attack relations {a mathematical formula}A1,…,An of the infinite subframeworks {a mathematical formula}AF1,…AFn, each relation {a mathematical formula}Ai is described by an attack expression {a mathematical formula}ai and we need to devise a corresponding attack expression {a mathematical formula}aˆi which preserves exactly the same attacks between the arguments of {a mathematical formula}AFi in the context of {a mathematical formula}AF∪, i.e. for any set {a mathematical formula}S⊆Σ∪ it must hold that {a mathematical formula}aˆ̲i(S)=aˆ̲i(S∩Xi)=a̲i(S∩Xi). It can be seen that such an expression {a mathematical formula}aˆi can be obtained from {a mathematical formula}ai by applying two simple replacement operations concerning the basic elements σ and I (rules 1 and 2 of Definition 13):
      </paragraph>
      <list>
       <list-item label="•">
        each occurrence of σ (with σ an element of {a mathematical formula}Σi) in {a mathematical formula}ai is replaced by {a mathematical formula}hd(σ⋅(I∩Ki)) within {a mathematical formula}aˆi, where {a mathematical formula}Ki is the regular expression specifying {a mathematical formula}Xi;
       </list-item>
       <list-item label="•">
        each occurrence of I in {a mathematical formula}ai is replaced by {a mathematical formula}(I∩Ki) within {a mathematical formula}aˆi, where {a mathematical formula}Ki is as above.
       </list-item>
      </list>
      <paragraph>
       It is immediate to see that if the attack expression {a mathematical formula}ai consists exactly of I or σ, the above replacements ensure that {a mathematical formula}aˆi satisfies the desired property. By inspection of the rules 3–5 of Definition 13 it is also easy to see that the desired property is preserved in more articulated expressions, constructed by repeated application of these rules starting from the basic elements, without requiring any further modification.
      </paragraph>
      <paragraph>
       Let us turn now to the specification of the additional finite attack relations {a mathematical formula}Ai,j ({a mathematical formula}i≠j) between subframeworks. First, observe that each {a mathematical formula}Ai,j can be specified directly as a regular language {a mathematical formula}Li,j={x⋅y:〈x,y〉∈Ai,j} and let again {a mathematical formula}Ki be the regular expression corresponding to {a mathematical formula}Xi. Then, note that the expression {a mathematical formula}(Ki⋅I)∩Li,j is useful to select words in {a mathematical formula}Li,j when appropriate and that the quotient operator wrt {a mathematical formula}Kj can then be applied to extract the subword referring to the attacker. Finally, we have to ensure that the extracted subword belongs to {a mathematical formula}Ki which can be obtained by an intersection operation. In summary, the attack expression specifying an attack relations {a mathematical formula}Ai,j ({a mathematical formula}i≠j) is {a mathematical formula}aˆi,j=(((Ki⋅I)∩Li,j)/Kj)∩Ki.
      </paragraph>
      <paragraph>
       Putting together the various subexpressions we have devised above, the complete attack expression {a mathematical formula}a∪ for {a mathematical formula}AF∪ is given by {a mathematical formula}a∪=⋃i∈{0,…,n}aˆi∪⋃i,j∈{0,…,n},i≠jaˆi,j.
      </paragraph>
     </section>
    </section>
    <section label="6">
     Computing with af specifications
     <paragraph>
      In this section we show{sup:18} that a number of problems that are well-known to be efficiently, i.e. polynomial time, decidable in finite afs may be effectively handled within the context of af specifications, i.e. there exist procedures which are certain to produce the answer in a finite number of steps.
     </paragraph>
     <paragraph>
      Theorem 3 provides the main result of this section.
     </paragraph>
     <paragraph label="Theorem 3">
      Let{a mathematical formula}〈M,a〉be anafs, with induced argumentation framework{a mathematical formula}〈X,A〉and{a mathematical formula}S⊆X. The following problems are decidable.
     </paragraph>
     <list>
      <list-item label="(a)">
       Deciding if the set S is conflict free.
      </list-item>
      <list-item label="(b)">
       For{a mathematical formula}x∈X, deciding if{a mathematical formula}x∈F(S), i.e. whether x is acceptable to S.
      </list-item>
      <list-item label="(c)">
       Deciding if{a mathematical formula}S∈Eadm(〈X,A〉), i.e. whether S is admissible.
      </list-item>
      <list-item label="(d)">
       Deciding if{a mathematical formula}S∈Estab(〈X,A〉), i.e. whether S is a stable extension.
      </list-item>
      <list-item label="(e)">
       Constructing adfaaccepting{a mathematical formula}F(S)=X∖πa+(X∖πa+(S)), i.e. the set of arguments acceptable to S.
      </list-item>
      <list-item label="(f)">
       Deciding if{a mathematical formula}S∈Ecomp(〈X,A〉), i.e. whether S is a complete extension.
      </list-item>
     </list>
     <paragraph>
      The algorithms described in the proof of Theorem 3 provide full solutions to the decision problems listed above and are applicable irrespective of whether {a mathematical formula}〈M,a〉 gives rise to finitary frameworks or not. For the construction of the grounded extension we obtain a result applicable to finitary argumentation frameworks only. In fact, in [37] it is shown that, letting {a mathematical formula}F1(S)=F(S), and for {a mathematical formula}i&gt;1Fi(S)=F(Fi−1(S)), for a finitary argumentation framework the grounded extension is given by {a mathematical formula}⋃i⩾1Fi(∅).
     </paragraph>
     <paragraph>
      Using this result we can in some cases obtain (a representation of) the grounded extension through Algorithm 1.
     </paragraph>
     <paragraph>
      Algorithm 1 effectively reproduces the sequence of iterations involving:
     </paragraph>
     <list>
      <list-item label="•">
       identifying unattacked arguments in {a mathematical formula}X (in l.2 and l.7), where we note that {a mathematical formula}Y0 computes {a mathematical formula}F(∅), i.e. {a mathematical formula}X∖πa+(X) since {a mathematical formula}πa+(∅)=∅;
      </list-item>
      <list-item label="•">
       adding these to the extension being accumulated (in l.3 and l.8);
      </list-item>
      <list-item label="•">
       repeating this process on the af induced by the arguments remaining after removing these and those they attack (in l.6).
      </list-item>
     </list>
     <paragraph>
      The process terminates when the set of unattacked arguments is empty. Let us exemplify the application of Algorithm 1 to {a mathematical formula}AFR. Starting with the set of unattacked arguments, we get {a mathematical formula}Y0=000⋅(000)⁎ at l.2. Then, given that {a mathematical formula}πa+(Y0)=00⋅(000)⁎ in the first iteration of the while loop we get {a mathematical formula}X1=0⋅(000)⁎ at l.6 and, given that {a mathematical formula}πa+(X1)=00⋅(000)⁎, we get {a mathematical formula}Y1=X1 at l.7 and {a mathematical formula}G=(000⋅(000)⁎)∪(0⋅(000)⁎) then in the next iteration {a mathematical formula}X2=Y2=∅ and the algorithm terminates.
     </paragraph>
     <paragraph>
      Algorithm 1, however, does not guarantee termination, since it terminates only in the cases where there is k such that {a mathematical formula}Fk+1(∅)=Fk(∅). For instance in the framework {a mathematical formula}AFU of Example 3, in which for {a mathematical formula}i⩾1, {a mathematical formula}Fi={02k−1:1⩽k⩽i}, no such k exists.
     </paragraph>
     <paragraph>
      In such cases we can use properties of the operations involved in defining attack expressions together with known identities for regular expressions to derive the form taken by arguments in the grounded extension directly. In the case of {a mathematical formula}AFU we recall that,{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} For notational ease we write {a mathematical formula}T¯ for {a mathematical formula}X∖T so that {a mathematical formula}F0=∅, {a mathematical formula}Fi=F(Fi−1) and{a mathematical formula} For {a mathematical formula}AFU we get{a mathematical formula}{a mathematical formula}{a mathematical formula} So that the least fixed-point is the infinite set {a mathematical formula}{02i−1:i⩾1}: note that, by the analysis given, this is a fixed-point and it is straightforward to show that no strict subset defines a fixed-point.
     </paragraph>
     <paragraph>
      The analysis in the infinite case of those problems which are computationally intractable within finite afs (cf. the summary presented in Fact 1) is left to future work. As a first step in this direction, we can show that, restricting again to finitary frameworks, limited decision procedures are possible for two of these problems. Note that we currently have no result on whether these problems are decidable: Theorem 4 ensures that, if this is not the case, they are at least semi-decidable.
     </paragraph>
     <paragraph label="Theorem 4">
      Let{a mathematical formula}〈M,a〉be anafsin which the induced argumentation framework{a mathematical formula}〈X,A〉is finitary. The following problems are all semi-decidable.
     </paragraph>
     <list>
      <list-item label="(a)">
       Determining if{a mathematical formula}Estab(〈X,A〉)=∅.
      </list-item>
      <list-item label="(b)">
       Given a finite {a mathematical formula}R⊂X, determining if  {a mathematical formula}∀w∈R¬caadm(〈X,A〉,w).
      </list-item>
     </list>
     <paragraph>
      We note that the restriction to finitary frameworks (and finite subsets of {a mathematical formula}X in the second part) is needed: without this the method used in proving Theorem 4 could not be applied.
     </paragraph>
     <paragraph>
      To conclude this section, as some of the results we provided rely on the condition that an af specification gives rise to a finitary argumentation framework, one is interested in conditions ensuring that this holds. We provide an easy sufficient condition to this purpose, namely the absence of the ⁎ operator in the attack expression, leaving further investigations on this specific question for future work.
     </paragraph>
     <paragraph label="Proposition 9">
      Let{a mathematical formula}〈M,a〉be anafswith induced argumentation framework{a mathematical formula}〈X,→a〉. Let{a mathematical formula}K={KΣ1,KΣ2,…,KΣr}be the set of regular expressions used in defining a, i.e. with operations{a mathematical formula}b⋅KΣ,{a mathematical formula}KΣ⋅b,{a mathematical formula}KΣ/b,{a mathematical formula}b/KΣand{a mathematical formula}b∩KΣ. If no {a mathematical formula}K∈Kuses the ⁎ operator then{a mathematical formula}〈X,→a〉is finitary.
     </paragraph>
     <paragraph>
      It is easy to see that the condition of Proposition 9 is not a necessary one. Consider, for example {a mathematical formula}a=hd(I⋅(σ1+σ2)⁎). This is finitary, however, fails to satisfy the conditions of Proposition 9. Less trivially, {a mathematical formula}a=(σ1⋅(σ1)⁎)⋅I⋅(σ2⋅(σ2)⁎) will be finitary when {a mathematical formula}X∩{σ1⋅(σ1)⁎⋅x⋅σ2⋅(σ2)⁎} is bounded for all {a mathematical formula}x∈X.
     </paragraph>
    </section>
    <section label="7">
     af specifications at work
     <paragraph>
      In this section we illustrate the suitability of our approach by showing how it can be used to provide a formal representation of four examples which altogether combine different features. Two of the examples (presented in Sections 7.1 The, 7.2 Dungʼs example) are abstract in nature (they have been previously introduced in the literature mainly for the sake of theoretical analysis), while the examples of Sections 7.3 An example in multi-agent negotiation (from Section, 7.4 An example in ambient intelligence (from Section are inspired to realistic application domains (also taken from the literature) and have been introduced in Section 2.2. The two abstract examples of Sections 7.1 The, 7.2 Dungʼs example concern infinite non-finitary afs, while the “application-oriented” examples of Sections 7.3 An example in multi-agent negotiation (from Section, 7.4 An example in ambient intelligence (from Section give rise to infinite finitary afs.
     </paragraph>
     <paragraph>
      Moreover, we remark that the examples of Sections 7.2 Dungʼs example, 7.4 An example in ambient intelligence (from Section are based on a formalization in terms of a logic program featuring an infinite Herbrand base. In fact, the formalization in argumentation terms of logic programs with infinite Herbrand base is, at a general level, one of the “natural” applications of the proposed framework, given that a direct correspondence between logic programs with negation as failure and abstract argumentation frameworks has been established in Dungʼs paper itself.
     </paragraph>
     <paragraph>
      We will present the abstract examples before, as they are more suitable to illustrate in detail the technical use of the formalism as a specification tool in articulated frameworks, and later the “application-oriented” examples, to give an account of some potential practical uses of the formalism without cluttering the description of the more realistic examples with too much technical details, derivable by analogy from the first examples.
     </paragraph>
     <section label="7.1">
      The af from Caminada and Verheij [30]
      <paragraph>
       In [30] Caminada and Verheij describe a (non-finitary) af, {a mathematical formula}〈X,A〉 (see Fig. 3) with the property that {a mathematical formula}〈X,A〉 has no semi-stable extension,{sup:19} i.e. admissible set S for which {a mathematical formula}S∪S+ is maximal wrt ⊆. The construction uses arguments{a mathematical formula} linked by the attack relation, {a mathematical formula}A, containing{a mathematical formula}
      </paragraph>
      <paragraph>
       One obvious choice to describe this scheme would be the set {a mathematical formula}Σ={A,B,C} so that{a mathematical formula} It is not too hard to see, however, that it is impossible to describe the required set of attacks via some {a mathematical formula}a∈AE({A,B,C}): for example suppose S is an infinite regular subset of {a mathematical formula}{Ai:i⩾1}. Then{a mathematical formula} Now while this is a regular language for any fixed subset of {a mathematical formula}{Ai:i⩾1} given that it requires determining {a mathematical formula}min{i:Ai∈S} it is not possible to construct a general expression allowing this minimum to be computed.
      </paragraph>
      <paragraph>
       Nevertheless this scheme can be described within our formalism. Let {a mathematical formula}Σ={0} and {a mathematical formula}X={0i:i⩾1}={0}⋅{0}⁎. We can partition {a mathematical formula}X into three sets, {a mathematical formula}LA, {a mathematical formula}LB and {a mathematical formula}LC, as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       We can now identify the attack expression:
      </paragraph>
      <list>
       <list-item label="•">
        each element of {a mathematical formula}LA is attacked by itself, giving rise to the sub-expression {a mathematical formula}I∩LA, and by all elements of {a mathematical formula}LB with greater or equal index, giving rise to the sub-expression {a mathematical formula}(I∩LA)⋅0⋅(000)⁎;
       </list-item>
       <list-item label="•">
        each element of {a mathematical formula}LB is attacked by the element of {a mathematical formula}LC with the same index, giving rise to the sub-expression {a mathematical formula}(I∩LB)⋅0, and by all elements of {a mathematical formula}LB with greater index, giving rise to the sub-expression {a mathematical formula}(I∩LB)⋅(000)⋅(000)⁎;
       </list-item>
       <list-item label="•">
        each element of {a mathematical formula}LC is attacked by the element of {a mathematical formula}LB with the same index, giving rise to the sub-expression {a mathematical formula}tl(I∩LC).
       </list-item>
      </list>
      <paragraph>
       Summing up, we get{a mathematical formula} giving directly{a mathematical formula}
      </paragraph>
      <paragraph>
       In order to compute {a mathematical formula}πa+(S), we need to take into account Fact 2. From 2.2 the inverted mapping will be the union of the inverted sub-mappings corresponding to the various sub-expressions of a.
      </paragraph>
      <list>
       <list-item label="•">
        The first term: {a mathematical formula}I∩LA, according to 2.7 with {a mathematical formula}b=I, gives rise to {a mathematical formula}I̲+(S∩LA), and thus, from 2.1, to {a mathematical formula}S∩LA.
       </list-item>
       <list-item label="•">
        As to the second term {a mathematical formula}(I∩LA)⋅0⋅(000)⁎, from 2.3 with {a mathematical formula}b=(I∩LA) we obtain {a mathematical formula}b̲+(S/{0⋅(000)⁎}). In turn, to obtain {a mathematical formula}b̲+, 2.7 applies, which letting {a mathematical formula}c=I yields {a mathematical formula}c̲+(LA∩(S/{0⋅(000)⁎})), which applying 2.1 yields {a mathematical formula}LA∩(S/{0⋅(000)⁎}).
       </list-item>
       <list-item label="•">
        Following the same steps, from {a mathematical formula}(I∩LB)⋅(000)⋅(000)⁎ we obtain {a mathematical formula}LB∩(S/{000⋅(000)⁎}), and from {a mathematical formula}(I∩LB)⋅0 we derive {a mathematical formula}LB∩(S/0).
       </list-item>
       <list-item label="•">
        Finally from {a mathematical formula}tl(I∩LC), applying 2.9 with {a mathematical formula}b=I∩LC we obtain {a mathematical formula}b̲+(Σ⋅S). Applying then 2.7 with {a mathematical formula}c=I we get {a mathematical formula}c̲+(LC∩Σ⋅S), which applying 2.1 yields {a mathematical formula}LC∩Σ⋅S.
       </list-item>
      </list>
      <paragraph>
       Putting things together (according to Fact 2.2), we obtain{a mathematical formula}
      </paragraph>
      <paragraph>
       We can now exemplify the use of the computational procedures{sup:20} of Section 6 in this case. Let us start with the check of conflict-freeness, which for a set S involves verifying whether {a mathematical formula}πa−(S)∩S=∅. From the formulation of {a mathematical formula}πa+(S) given above it is easily verifiable that:
      </paragraph>
      <list>
       <list-item label="•">
        any set S such that {a mathematical formula}S∩LA≠∅ is not conflict-free;
       </list-item>
       <list-item label="•">
        any set S such that {a mathematical formula}|S∩LB|⩾2 is not conflict-free;
       </list-item>
       <list-item label="•">
        any set {a mathematical formula}S⊆LC is conflict-free.
       </list-item>
      </list>
      <paragraph>
       As to conflict-freeness, leaving apart the empty set, we have therefore to consider only singletons of the form {a mathematical formula}S={00⋅(000)i} with a fixed {a mathematical formula}i⩾0, any set {a mathematical formula}S⊆LC, and the union of any of the singletons {a mathematical formula}{00⋅(000)i} with any subset of {a mathematical formula}LC∖{000⋅(000)i}. For admissibility of a set S, one has to verify whether {a mathematical formula}πa+(S)⊇πa−(S) in addition to conflict-freeness. For the generic singleton {a mathematical formula}S={00⋅(000)i}, we have {a mathematical formula}πa+(S)={0⋅(000)j}∪{00⋅(000)k}∪{000⋅(000)i} for {a mathematical formula}0⩽j⩽i and {a mathematical formula}0⩽k&lt;i, while {a mathematical formula}πa−(S)={00⋅(000)i+1⋅(000)⁎}∪{000⋅(000)i}. Since {a mathematical formula}{00⋅(000)i+1⋅(000)⁎}∩πa+(S)=∅, it turns out that {a mathematical formula}πa+(S)⊉πa−(S) hence no {a mathematical formula}S={00⋅(000)i} is admissible. Considering instead any set {a mathematical formula}S⊆LC it can be seen that {a mathematical formula}πa+(S)=LB∩(S/0)=tl(S∩LC)=πa−(S). Hence any subset of {a mathematical formula}LC is admissible. Considering now the union S of a singleton {a mathematical formula}{00⋅(000)i} and a subset of {a mathematical formula}LC, since {a mathematical formula}πa−({00⋅(000)i})⊇{00⋅(000)i+1⋅(000)⁎} then {a mathematical formula}{(000)i+2⋅(000)⁎} must be contained in S. Taking now into account the facts above, it turns out that {a mathematical formula}S={00⋅(000)i,(000)i+2⋅(000)⁎}∪L′ for any {a mathematical formula}L′⊆{(000)j|1⩽j⩽i}. To determine whether an admissible set {a mathematical formula}S⊆LC is a complete extension we have to check whether {a mathematical formula}S=F(S)=X∖πa+(X∖πa+(S)). Considering any such {a mathematical formula}S⊆LC, we have already seen that {a mathematical formula}πa+(S)=LB∩(S/0). Hence {a mathematical formula}X∖πa+(S)=LA∪(LB∖(S/0))∪LC. It follows that {a mathematical formula}πa+(X∖πa+(S))=LA∪LB∪(LC∖S), and hence {a mathematical formula}F(S)=X∖(LA∪LB∪(LC∖S))=S. As to the sets of the form {a mathematical formula}S={00⋅(000)i,(000)i+2⋅(000)⁎}∪L′, it turns out (using the same reasoning line) that {a mathematical formula}F(S)={00⋅(000)i}∪(LC∖{000⋅(000)i}), which is also the unique complete extension including {a mathematical formula}{00⋅(000)i}. Summing up, all (either finite or infinite) subsets of {a mathematical formula}LC plus the sets {a mathematical formula}{00⋅(000)i}∪(LC∖{000⋅(000)i}) with {a mathematical formula}i⩾0 form the set of all the complete extensions of this framework.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Dungʼs example
      </section-title>
      <paragraph>
       We will now consider the infinite argumentation framework introduced in [37, pp. 331, 352]. The framework is derived from the following logic program{sup:21}Q.{a mathematical formula}
      </paragraph>
      <paragraph>
       The rules for transforming a logic program into an AF are defined in [37, p. 343] as follows.
      </paragraph>
      <paragraph>
       First of all, for a logic program P, {a mathematical formula}GP denotes the set of all ground instances of clauses in P. For each literal h, the complement of h is denoted by {a mathematical formula}h⁎. Let {a mathematical formula}K={notb1,…,notbm} be a set of ground negative literals. A ground atom k is said to be a defeasible consequence of {a mathematical formula}P,K if there is a sequence of ground atoms {a mathematical formula}(e0,e1,…,en) with {a mathematical formula}en=k such that for each {a mathematical formula}ei, either {a mathematical formula}ei←∈GP or {a mathematical formula}ei is the head of a clause {a mathematical formula}ei←a1,…,at,notat+1,…,notat+r in {a mathematical formula}GP such that the positive literals {a mathematical formula}a1,…,at belong to the preceding members in the sequence and the negative literals {a mathematical formula}notat+1,…,notat+3 belong to K. K is said to be a support for k with respect to P.
      </paragraph>
      <paragraph>
       A logic program P is transformed into an af{a mathematical formula}AF(P)=〈XP,AP〉 as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Arguments of the form {a mathematical formula}({notk},notk) capture the idea that k would be concluded false if there is no acceptable argument supporting k. An argument a attacks an argument b when the consequence of a contradicts one of the members of the support of b.
      </paragraph>
      <paragraph>
       The framework {a mathematical formula}AF(Q)=〈XQ,AQ〉, derived from the logic program Q, turns out to be non-finitary and is depicted in Fig. 4. Note that to keep the notation simple each predicate {a mathematical formula}s(x¯) has been replaced by the result of the expression {a mathematical formula}x¯+1.
      </paragraph>
      <paragraph>
       Let us examine the elements of {a mathematical formula}XQ. First, there are arguments of the form {a mathematical formula}({notk},notk) for each ground atom k, namely:
      </paragraph>
      <list>
       <list-item label="•">
        two “single” arguments for the atoms p and r (at the right of the figure, respectively in the lower and higher part);
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments for the atoms with form {a mathematical formula}q(x¯), corresponding to the fifth (from the left) “column” in Fig. 4;
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments for the atoms with form {a mathematical formula}even(x¯), corresponding to the first (from the left) “column” in Fig. 4.
       </list-item>
      </list>
      <paragraph>
       Then, there are arguments of the form {a mathematical formula}(K,k) derived by applying rules {a mathematical formula}(r1)–(r6), where K is a support for k. In particular we have:
      </paragraph>
      <list>
       <list-item label="•">
        two arguments with empty support: from {a mathematical formula}(r6) we get {a mathematical formula}({},even(0)) (top of the second “column”) and from {a mathematical formula}(r6) and {a mathematical formula}(r3) we get {a mathematical formula}({},q(0)) (above third “column” in Fig. 4);
       </list-item>
       <list-item label="•">
        a “single” argument {a mathematical formula}({notp},r) from {a mathematical formula}(r1) (at the right of the figure, in the higher part);
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments of the form {a mathematical formula}({notq(x¯)},p)|x¯⩾0 from {a mathematical formula}(r2) (sixth “column”);
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments of the form {a mathematical formula}({noteven(x¯)},q(x¯))|x¯⩾0 from {a mathematical formula}(r4) (fourth “column”);
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments of the form {a mathematical formula}({noteven(x¯)},even(x¯+1))|x¯⩾0 from {a mathematical formula}(r5) (second “column”);
       </list-item>
       <list-item label="•">
        an infinite sequence of arguments of the form {a mathematical formula}({noteven(x¯)},q(x¯+1))|x¯⩾0 from {a mathematical formula}(r5) and {a mathematical formula}(r3) (third “column”).
       </list-item>
      </list>
      <paragraph>
       Turning to the attack relation {a mathematical formula}AQ, we observe that:
      </paragraph>
      <list>
       <list-item label="•">
        each argument in the second “column”, (with consequence {a mathematical formula}even(x¯)) attacks the corresponding arguments in the first, third and fourth “columns” (having support {a mathematical formula}noteven(x¯));
       </list-item>
       <list-item label="•">
        each argument in the second “column” also attacks its “successor” in the column;
       </list-item>
       <list-item label="•">
        each argument in the third “column”, (with consequence {a mathematical formula}q(x¯)) attacks the corresponding arguments in the fifth and sixth “columns” (having support {a mathematical formula}notq(x¯));
       </list-item>
       <list-item label="•">
        similarly, each argument in the fourth “column”, (with consequence {a mathematical formula}q(x¯)) attacks the corresponding arguments in the fifth and sixth “columns” (having support {a mathematical formula}notq(x¯));
       </list-item>
       <list-item label="•">
        each argument in the sixth “column” (with consequence p) attacks both arguments {a mathematical formula}({notp},notp) and {a mathematical formula}({notp},r);
       </list-item>
       <list-item label="•">
        argument {a mathematical formula}({notp},r) attacks {a mathematical formula}({notr},notr).
       </list-item>
      </list>
      <paragraph>
       In order to provide an af specification for {a mathematical formula}AF(Q) we need first a dfa representing the infinite set of arguments {a mathematical formula}XQ and then a proper attack expression representing the relation {a mathematical formula}AQ.
      </paragraph>
      <paragraph>
       As to the dfa representation of {a mathematical formula}XQ, it is handy to consider separately the infinite sequences corresponding to the six “columns” in Fig. 4 and the three “single” arguments {a mathematical formula}({notp},r), {a mathematical formula}({notr},notr), and {a mathematical formula}({notp},notp).
      </paragraph>
      <paragraph>
       As to the arguments included in the “columns”, we define a correspondence with sequences of a unique symbol, namely A, by exploiting the “regular” structure of the sequences of arguments. In fact, let us associate the string A with argument {a mathematical formula}({},q(0)), AA with argument {a mathematical formula}({notq(0)},notq(0)), AAA with argument {a mathematical formula}({notq(0)},p), {a mathematical formula}AAAA with argument {a mathematical formula}({noteven(0)},q(0)), {a mathematical formula}A5 with argument {a mathematical formula}({},even(0)), and {a mathematical formula}A6 with argument {a mathematical formula}({noteven(0)},noteven(0)). The association may then continue periodically over the “columns” by putting {a mathematical formula}A7 in correspondence with {a mathematical formula}({noteven(0)},q(1)), {a mathematical formula}A8 with {a mathematical formula}({notq(1)},notq(1)) and so on. More formally, we use the elements of {a mathematical formula}A⋅A⁎ to represent arguments as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       To simplify the subsequent description it is useful to denote as six distinct (regular) languages the subsets of {a mathematical formula}A⁎ corresponding to the different sequences of arguments in {a mathematical formula}XQ:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       To complete the representation of {a mathematical formula}XQ, the remaining three “single” arguments are assigned three distinct alphabet elements as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}B≜({notp},r)
       </list-item>
       <list-item label="•">
        {a mathematical formula}C≜({notr},notr)
       </list-item>
       <list-item label="•">
        {a mathematical formula}D≜({notp},notp)
       </list-item>
      </list>
      <paragraph>
       In summary, the representation of the arguments in {a mathematical formula}AF(Q) is based on the set of symbols {a mathematical formula}ΣQ={A,B,C,D} and the encoding consists of a DFA{a mathematical formula}MQ accepting the language {a mathematical formula}L(MQ)={B,C,D}∪{A⋅A⁎}. Clearly {a mathematical formula}L(MQ) is a regular language included in {a mathematical formula}ΣQ⁎∖{ε}.
      </paragraph>
      <paragraph>
       The simple minimal DFA accepting {a mathematical formula}L(MQ) is depicted in Fig. 5.
      </paragraph>
      <paragraph>
       We need now to identify a suitable attack expression {a mathematical formula}aQ for {a mathematical formula}AF(Q). To this purpose let us first observe that, for a set of arguments S, the function {a mathematical formula}πaQ−(S) must return as result a non-empty set if and only if S has a non-empty intersection with the set of arguments which receive an attack in {a mathematical formula}AF(Q), namely {a mathematical formula}{B,C,D}∪L2∪L3∪L4∪L6∪L7∪L11. As a consequence, the global attack expression may be built as the union of various sub-expressions, each associated with a class of attacked arguments. Each sub-expression:
      </paragraph>
      <list>
       <list-item label="•">
        has to select the range of sets for which a non-empty result is returned: this can be achieved specifying the intersection between I and a given sub-language of {a mathematical formula}XQ corresponding to the class of attacked arguments;
       </list-item>
       <list-item label="•">
        has to define a set of attackers through a proper symbol manipulation.
       </list-item>
      </list>
      <paragraph>
       To exemplify, consider a sub-expression to specify the attackers of argument B, namely {a mathematical formula}{A3+6x¯|x¯⩾0} (corresponding to {a mathematical formula}{({notq(x¯)},p)}, {a mathematical formula}x¯⩾0). This can be obtained as {a mathematical formula}tl(I∩B)⋅AAA⋅(A⋅…⋅A︸6)⁎=tl(I∩B)⋅L3. In fact, {a mathematical formula}I∩B yields either {a mathematical formula}{B} or the empty set. In the former case the tl operator yields ε which, combined with {a mathematical formula}L3, gives the desired result, while in the latter case the combination produces the empty set. In a similar (and simpler) way, since C is attacked only by B we obtain the subexpression {a mathematical formula}tl(I∩C)⋅B, while D has exactly the same attackers as B, yielding {a mathematical formula}tl(I∩D)⋅L3.
      </paragraph>
      <paragraph>
       Consider now the specification of the attackers of the elements of sub-languages of {a mathematical formula}XQ. Starting from {a mathematical formula}L2 we observe that each element {a mathematical formula}A2+6x¯ (corresponding to {a mathematical formula}({notq(x¯)},notq(x¯)), {a mathematical formula}x¯⩾0) has two attackers namely {a mathematical formula}A2+6x¯−1 (corresponding to {a mathematical formula}({},q(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},q(x¯)) for {a mathematical formula}x¯&gt;0) and {a mathematical formula}A2+6x¯+2 (corresponding to {a mathematical formula}({noteven(x¯)},q(x¯)), {a mathematical formula}x¯⩾0). The elements of the first family of attackers can be obtained by applying the tl operator to {a mathematical formula}L2, those of the second family of attackers by concatenating {a mathematical formula}A⋅A to {a mathematical formula}L2. This reasoning gives rise to the sub-expressions {a mathematical formula}tl(I∩L2) and {a mathematical formula}(I∩L2)⋅A⋅A.
      </paragraph>
      <paragraph>
       Similarly, each element of {a mathematical formula}L3A3+6x¯ (corresponding to {a mathematical formula}({notq(x¯)},p), {a mathematical formula}x¯⩾0) has two attackers namely {a mathematical formula}A3+6x¯+1 (corresponding to {a mathematical formula}({noteven(x¯)},q(x¯)), {a mathematical formula}x¯⩾0) and {a mathematical formula}A3+6x¯−2 (corresponding to {a mathematical formula}({},q(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},q(x¯)) for {a mathematical formula}x¯⩾1). This reasoning gives rise to the sub-expressions{sup:22}{a mathematical formula}(I∩L3)⋅A and {a mathematical formula}tl2(I∩L3).
      </paragraph>
      <paragraph>
       As to {a mathematical formula}L4, each element {a mathematical formula}A4+6x¯ (corresponding to {a mathematical formula}({noteven(x¯)},q(x¯)), {a mathematical formula}x¯⩾0) has one attacker {a mathematical formula}A4+6x¯+1 (corresponding to {a mathematical formula}({},even(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},even(x¯)), {a mathematical formula}x¯⩾1). This gives rise to the sub-expression {a mathematical formula}(I∩L4)⋅A.
      </paragraph>
      <paragraph>
       Turning to {a mathematical formula}L6, each element {a mathematical formula}A6+6x¯ (corresponding to {a mathematical formula}({noteven(x¯)},noteven(x¯)), {a mathematical formula}x¯⩾0) has one attacker {a mathematical formula}A6+6x¯−1 (corresponding to {a mathematical formula}({},even(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},even(x¯)), {a mathematical formula}x¯⩾1). This gives rise to the sub-expression {a mathematical formula}tl(I∩L6).
      </paragraph>
      <paragraph>
       In {a mathematical formula}L7, each element {a mathematical formula}A7+6x¯ (corresponding to {a mathematical formula}({noteven(x¯)},q(x¯+1)), {a mathematical formula}x¯⩾0) has one attacker {a mathematical formula}A7+6x¯−2 (corresponding to {a mathematical formula}({},even(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},even(x¯)), {a mathematical formula}x¯⩾1). This gives rise to the sub-expression {a mathematical formula}tl2(I∩L7).
      </paragraph>
      <paragraph>
       Finally, each element of {a mathematical formula}L11A11+6x¯,(corresponding to {a mathematical formula}({noteven(x¯)},even(x¯+1)), {a mathematical formula}x¯⩾0) has one attacker {a mathematical formula}A11+6x¯−6 (corresponding to {a mathematical formula}({},even(0)) for {a mathematical formula}x¯=0 and to {a mathematical formula}({noteven(x¯−1)},even(x¯)), {a mathematical formula}x¯⩾1). This gives rise to the sub-expression {a mathematical formula}tl6(I∩L11).
      </paragraph>
      <paragraph>
       In summary, we obtain the following attack expression:{a mathematical formula} The relevant mapping {a mathematical formula}aQ̲:2ΣQ⁎→2ΣQ⁎ follows directly:{a mathematical formula}
      </paragraph>
      <paragraph>
       We can now apply Fact 2 to obtain the inverted mapping {a mathematical formula}aQ̲+. First, we observe that on the basis of 2.2 the inverted mapping will be the union of the inverted sub-mappings corresponding to the various sub-expressions of {a mathematical formula}aQ.
      </paragraph>
      <paragraph>
       Consider first, for the sake of illustration, the sub-expression {a mathematical formula}tl(I∩B)⋅L3, which has the form {a mathematical formula}b⋅KΣ with {a mathematical formula}b=tl(I∩B) and {a mathematical formula}KΣ=L3. Accordingly, Fact 2.3 applies, yielding {a mathematical formula}b̲+(S/L3). In turn, to obtain {a mathematical formula}b̲+, Fact 2.9 applies which, letting {a mathematical formula}c=I∩B, gives {a mathematical formula}c̲+(ΣQ⋅(S/L3)). Applying Fact 2.7 (and the base case for I) to c we obtain {a mathematical formula}B∩(ΣQ⋅(S/L3)).
      </paragraph>
      <paragraph>
       The sub-expressions {a mathematical formula}tl(I∩C)⋅B and {a mathematical formula}tl(I∩D)⋅L3 are analogous, yielding {a mathematical formula}C∩(ΣQ⋅(S/B)) and {a mathematical formula}D∩(ΣQ⋅(S/L3)).
      </paragraph>
      <paragraph>
       From the sub-expression {a mathematical formula}tl(I∩L2) orderly applying Fact 2.9 and 2.7 we obtain {a mathematical formula}L2∩(ΣQ⋅S), while from {a mathematical formula}(I∩L2)⋅A⋅A applying 2.3 and 2.7 we have {a mathematical formula}L2∩(S/(A⋅A)).
      </paragraph>
      <paragraph>
       For the sub-expression {a mathematical formula}tl2(I∩L3) we apply 2.9 twice and 2.7, yielding {a mathematical formula}L3∩(ΣQ⋅ΣQ⋅S).
      </paragraph>
      <paragraph>
       The treatment of each of the remaining sub-expressions is similar to one of the previous cases, yielding the following result.{a mathematical formula}
      </paragraph>
      <paragraph>
       It can be easily observed that both {a mathematical formula}aQ̲ and {a mathematical formula}aQ̲+ cannot produce results outside {a mathematical formula}XQ hence, for any {a mathematical formula}S⊆XQ, {a mathematical formula}πaQ−(S)=aQ̲(S)∩XQ=aQ̲(S) and {a mathematical formula}πaQ+(S)=aQ̲+(S)∩XQ=aQ̲+(S).
      </paragraph>
      <paragraph>
       We can now exemplify the analysis of semantics properties in {a mathematical formula}AF(Q).
      </paragraph>
      <paragraph>
       Letting {a mathematical formula}S={B}∪{D}∪{A1+12x¯|x¯⩾0}∪{A5+12x¯|x¯⩾0}∪{A10+12x¯|x¯⩾0}∪{A12+12x¯|x¯⩾0} consider the problem of checking whether S is conflict-free (the structure of the infinite set S is evidenced in Fig. 6).
      </paragraph>
      <paragraph>
       We have to prove that {a mathematical formula}πaQ−(S)∩S=∅.
      </paragraph>
      <paragraph>
       We can now apply {a mathematical formula}aQ̲ to the subsets forming the definition of S. Noting in particular that
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}{A1+12x¯|x¯⩾0} intersects {a mathematical formula}L7 “starting” from {a mathematical formula}A⋅…⋅A︸13
       </list-item>
       <list-item label="•">
        {a mathematical formula}{A5+12x¯|x¯⩾0} intersects {a mathematical formula}L11 “starting” from {a mathematical formula}A⋅…⋅A︸17
       </list-item>
       <list-item label="•">
        {a mathematical formula}{A10+12x¯|x¯⩾0} intersects {a mathematical formula}L4 “starting” from {a mathematical formula}A⋅…⋅A︸10
       </list-item>
       <list-item label="•">
        {a mathematical formula}{A12+12x¯|x¯⩾0} intersects {a mathematical formula}L6 “starting” from {a mathematical formula}A⋅…⋅A︸12
       </list-item>
      </list>
      <paragraph>
       we obtain:{a mathematical formula}
      </paragraph>
      <paragraph>
       Noting that the last four elements of the above expression coincide, we have {a mathematical formula}πaQ−(S)=L3∪A⋅…⋅A︸11⋅(A⋅…⋅A︸12)⁎. As to conflict-freeness, it is easily seen that {a mathematical formula}πaQ−(S)∩S=∅.
      </paragraph>
      <paragraph>
       Let us now turn to the problem of acceptability checking, by verifying whether the argument B is acceptable wrt S, i.e. {a mathematical formula}B∈FQ(S). This requires to check whether {a mathematical formula}πaQ−({B})∖πaQ+(S)=∅ (see the proof of part b of Theorem 3).
      </paragraph>
      <paragraph>
       To identify {a mathematical formula}πaQ+(S) we can apply {a mathematical formula}aQ̲+ to the subsets evidenced in the above definition of S. In particular:
      </paragraph>
      <list>
       <list-item label="•">
        the second item in the definition of {a mathematical formula}aQ̲+ is effective (i.e. gives a non-empty result) on {a mathematical formula}{B} yielding {a mathematical formula}{C}
       </list-item>
       <list-item label="•">
        no item is effective on {a mathematical formula}{D}
       </list-item>
       <list-item label="•">
        the fourth and sixth items are effective on {a mathematical formula}{A1+12x¯|x¯⩾0} yielding {a mathematical formula}A⋅A⋅(A⋅…⋅A︸12)⁎ and {a mathematical formula}A⋅A⋅A⋅(A⋅…⋅A︸12)⁎
       </list-item>
       <list-item label="•">
        the eighth, ninth, tenth, and eleventh items are effective on {a mathematical formula}{A5+12x¯|x¯⩾0} yielding {a mathematical formula}A⋅…⋅A︸4⋅(A⋅…⋅A︸12)⁎, {a mathematical formula}A⋅…⋅A︸6⋅(A⋅…⋅A︸12)⁎, {a mathematical formula}A⋅…⋅A︸7⋅(A⋅…⋅A︸12)⁎, {a mathematical formula}A⋅…⋅A︸11⋅(A⋅…⋅A︸12)⁎
       </list-item>
       <list-item label="•">
        the fifth and seventh items are effective on {a mathematical formula}{A10+12x¯|x¯⩾0} yielding {a mathematical formula}A⋅…⋅A︸8⋅(A⋅…⋅A︸12)⁎ and {a mathematical formula}A⋅…⋅A︸9⋅(A⋅…⋅A︸12)⁎
       </list-item>
       <list-item label="•">
        no item is effective on {a mathematical formula}{A12+12x¯|x¯⩾0}
       </list-item>
      </list>
      <paragraph>
       Summing up,{a mathematical formula}
      </paragraph>
      <paragraph>
       Since {a mathematical formula}πaQ−({B})=L3 while from the expression derived above we note that {a mathematical formula}A⋅A⋅A⋅(A⋅…⋅A︸12)⁎∪A⋅…⋅A︸9⋅(A⋅…⋅A︸12)⁎=L3⊂πaQ+(S), it follows that {a mathematical formula}B∈FQ(S).
      </paragraph>
      <paragraph>
       Let us now check whether S is admissible. We have already proved that S is conflict free, therefore, from part (c) of Theorem 3, we have to check whether {a mathematical formula}πaQ−(S)∖πaQ+(S)=∅.
      </paragraph>
      <paragraph>
       Recalling{a mathematical formula}
      </paragraph>
      <paragraph>
       it is easily seen that {a mathematical formula}πaQ−(S)∖πaQ+(S)=∅.
      </paragraph>
      <paragraph>
       We can also check whether S is a stable extension. Since S is conflict free, we just need to confirm that {a mathematical formula}S∪πa+(S)=X:{a mathematical formula}
      </paragraph>
      <paragraph>
       Then S is a stable extension of {a mathematical formula}AF(Q). From this fact it follows that S is also a complete extension of {a mathematical formula}AF(Q), hence {a mathematical formula}FQ(S)=S. This could be independently verified, according to part (f) of Theorem 3, computing {a mathematical formula}FQ(S)=XQ∖πaQ+(XQ∖πaQ+(S)). As we already know, {a mathematical formula}XQ∖πaQ+(S)=S, hence {a mathematical formula}FQ(S)=XQ∖πaQ+(S)=S.
      </paragraph>
      <paragraph>
       It can also be observed that {a mathematical formula}AF(Q) is well-founded (Definition 29 of [37]) namely there is no infinite sequence of arguments {a mathematical formula}X0,X1,…,Xn,… such that {a mathematical formula}Xi+1 attacks {a mathematical formula}Xi. Note in particular that letting {a mathematical formula}X0 any argument in {a mathematical formula}L11, i.e. {a mathematical formula}X0=A11+6x¯ for some {a mathematical formula}x¯⩾0, there is only a finite sequence {a mathematical formula}X0,…,Xx¯+1 satisfying the condition of Definition 29 in [37], with {a mathematical formula}X1=A11+6(x¯−1),…,Xx¯+1=A5. Note also that the framework would not be well-founded with a “reverse” attack relation, namely if we had {a mathematical formula}(A11+6(x¯+1),A11+6(x¯))∈AQ instead of having {a mathematical formula}(A11+6(x¯−1),A11+6(x¯))∈AQ.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}AF(Q) is well-founded, by Theorem 30 of [37] it has exactly one complete extension which is grounded, preferred and stable, namely the set S identified above. It is described by the regular language {a mathematical formula}LEgrQ accepted by the DFA depicted in Fig. 7.
      </paragraph>
     </section>
     <section label="7.3">
      An example in multi-agent negotiation (from Section 2.2.1)
      <paragraph>
       Referring to the description of the example given in Section 2.2.1, the global argumentation framework {a mathematical formula}AFneg arising from the non-terminating message exchanges among the three agents is depicted in Fig. 8.
      </paragraph>
      <paragraph>
       Upon detection of a long sequence of withdrawals and reiterations of the same offers (and assuming that the agents programmatically repeat their behavior), the market authority can identify{sup:23} the relevant AF specification, which can be given as follows.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}Σ={0} and {a mathematical formula}X={0i:i⩾1}={0}⋅{0}⁎. We can partition {a mathematical formula}X into six sets {a mathematical formula}LA, {a mathematical formula}LB, {a mathematical formula}LC, {a mathematical formula}LD, {a mathematical formula}LE, and {a mathematical formula}LF (corresponding respectively to the six sequences {a mathematical formula}{O1,O4,…}, {a mathematical formula}{O2,O5,…}, {a mathematical formula}{O3,O6,…}, {a mathematical formula}{W1,W4,…}, {a mathematical formula}{W2,W5,…}, {a mathematical formula}{W3,W6,…}) as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The attack expression can then be formulated as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The market authority can then stop the activities of the agents and check whether some combination of offers and withdrawals can be regarded as a feasible solution (the market authority is interested in favoring the execution of as many exchanges as possible). Using the algorithms presented in Section 6, it can be checked that:
      </paragraph>
      <list>
       <list-item label="•">
        all three sets representing the reiteration of a specific offer, namely {a mathematical formula}LA, {a mathematical formula}LB, and {a mathematical formula}LC corresponding respectively to {a mathematical formula}{O1,O4,O7,…}, {a mathematical formula}{O2,O5,O8,…}, and {a mathematical formula}{O3,O6,O9,…}, are admissible;
       </list-item>
       <list-item label="•">
        none of the possible pairwise unions of the three sets above is admissible;
       </list-item>
       <list-item label="•">
        each set consisting of the reiteration of an offer and of the withdrawals of the two other offers (i.e. each of the following sets {a mathematical formula}LA∪LE∪LF; {a mathematical formula}LB∪LD∪LF; {a mathematical formula}LC∪LD∪LE) is stable.
       </list-item>
      </list>
      <paragraph>
       On the basis of these evaluations, it emerges that exactly one of the three exchanges can be executed, with the choice left to the authority itself.
      </paragraph>
      <paragraph>
       Consider now a similar situation with four agents involved in the loop, with the initial situation as described in Table 3.
      </paragraph>
      <paragraph>
       In this case in the first round we have four offers, namely:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}O1=Off(t0,(A1,A2,Exch(Rd,Rc)))
       </list-item>
       <list-item label="•">
        {a mathematical formula}O2=Off(t0,(A2,A3,Exch(Rc,Rb)))
       </list-item>
       <list-item label="•">
        {a mathematical formula}O3=Off(t0,(A3,A4,Exch(Rb,Ra)))
       </list-item>
       <list-item label="•">
        {a mathematical formula}O4=Off(t0,(A4,A1,Exch(Ra,Rd)))
       </list-item>
      </list>
      <paragraph>
       As in the case above we have consequently four withdrawals, four offers in turn and so on (see the framework {a mathematical formula}AFneg4 in Fig. 9).
      </paragraph>
      <paragraph>
       Skipping technical details, it turns out that:
      </paragraph>
      <list>
       <list-item label="•">
        all three sets representing the reiteration of a specific offer, namely {a mathematical formula}O1,O5,O9,… , {a mathematical formula}O2,O6,O10,… , {a mathematical formula}O3,O7,O11,… , and {a mathematical formula}O4,O8,O12,… , are admissible;
       </list-item>
       <list-item label="•">
        two of the pairwise unions of these sets are admissible namely {a mathematical formula}O1,O3,O5,… , and {a mathematical formula}O2,O4,O6,… ;
       </list-item>
       <list-item label="•">
        each set consisting of one of the above mentioned pairwise unions and of the withdrawals of the two other offers is stable.
       </list-item>
      </list>
      <paragraph>
       On the basis of these evaluations, it emerges that two exchanges can be executed, with the choice left again to the authority.
      </paragraph>
      <paragraph>
       In general, using the evaluation of an infinite framework, the authority can go beyond detecting and stopping non-terminating situations in this kind of multi-agent dialogues: the added-value consists in identifying which exchanges are anyway feasible in such situations.
      </paragraph>
     </section>
     <section label="7.4">
      An example in ambient intelligence (from Section 2.2.2)
      <paragraph>
       Referring to the description of the example given in Section 2.2.2 and omitting the burden of some uninteresting details (in particular all arguments corresponding to default assumptions which are contradicted by facts), the argumentation framework corresponding to the interactions among the components of the ambient intelligence system consists of:
      </paragraph>
      <list>
       <list-item label="•">
        a finite part corresponding to basic facts which are not time-dependent, namely {a mathematical formula}F1=person(Brian), {a mathematical formula}F2=room(office), {a mathematical formula}F3=phone(Brianphone), {a mathematical formula}F4=owner(Brianphone,Brian) and are not involved in attack relations;
       </list-item>
       <list-item label="•">
        an infinite part consisting of the regular iteration of a section corresponding to even time instants and a section corresponding to odd time instants.{sup:24}
       </list-item>
      </list>
      <paragraph>
       The following arguments and attacks are common to all sections independently of oddness or evenness of the time instant i:
      </paragraph>
      <list>
       <list-item label="•">
        two facts corresponding to device readings: {a mathematical formula}NVR(i)=¬videorecogn(Brian,office,i), {a mathematical formula}PI(i)=phonein(Brianphone,office,i);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}PL(i) with conclusion {a mathematical formula}phlocated(Brianphone,i) derived from fact {a mathematical formula}phonein(Brianphone,office,i) using {a mathematical formula}(r8);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}VV(i) with conclusion {a mathematical formula}videovalid(office,i) derived using {a mathematical formula}(r9) on the basis of the default assumption {a mathematical formula}notdark(office,i);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}IN(i) with conclusion {a mathematical formula}in(Brian,office,i) derived using {a mathematical formula}(r1) on the basis of the default assumption {a mathematical formula}notvideovalid(office,i);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}NIN(i) with conclusion {a mathematical formula}¬in(Brian,office,i) derived using {a mathematical formula}(r3) on the basis of the fact {a mathematical formula}¬videorecogn(Brian,office,i) and of the previously derived conclusion {a mathematical formula}videovalid(office,i);
       </list-item>
      </list>
      <paragraph>
       The following arguments are included only in sections corresponding to an even time instant j:
      </paragraph>
      <list>
       <list-item label="•">
        the fact {a mathematical formula}D(j) corresponding to the device reading {a mathematical formula}dark(office,j);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}LO(j) with conclusion {a mathematical formula}lighton(office,j+1) derived using {a mathematical formula}(r6).
       </list-item>
      </list>
      <paragraph>
       The following arguments are included only in sections corresponding to an odd time instant k:
      </paragraph>
      <list>
       <list-item label="•">
        the fact {a mathematical formula}ND(k) corresponding to the device reading: {a mathematical formula}¬dark(office,k);
       </list-item>
       <list-item label="•">
        an argument {a mathematical formula}NLO(k) with conclusion {a mathematical formula}¬lighton(office,k+1) derived using {a mathematical formula}(r7).
       </list-item>
      </list>
      <paragraph>
       As to attacks:
      </paragraph>
      <list>
       <list-item label="•">
        each argument with conclusion {a mathematical formula}videovalid(office,i) attacks the argument with conclusion {a mathematical formula}in(Brian,office,i);
       </list-item>
       <list-item label="•">
        arguments with conclusion {a mathematical formula}in(Brian,office,i) and {a mathematical formula}¬in(Brian,office,i) mutually attack each other;
       </list-item>
       <list-item label="•">
        each fact {a mathematical formula}dark(office,i) attacks the arguments with conclusions {a mathematical formula}videovalid(office,i) and {a mathematical formula}¬in(Brian,office,i).
       </list-item>
      </list>
      <paragraph>
       The corresponding argumentation framework {a mathematical formula}AFamb is depicted in Fig. 10. The relevant AF specification can be given as follows. Let {a mathematical formula}Σ={F1,F2,F3,F4,0} and {a mathematical formula}X={F1,F2,F3,F4}∪{0i:i⩾1}. We can partition {a mathematical formula}X∖{F1,F2,F3,F4} into 10 sets {a mathematical formula}LA, {a mathematical formula}LB, {a mathematical formula}LC, {a mathematical formula}LD, {a mathematical formula}LE, {a mathematical formula}LF, {a mathematical formula}LG, {a mathematical formula}LH, {a mathematical formula}LI, {a mathematical formula}LJ, (corresponding respectively to the 10 sequences {a mathematical formula}NVR(i),PI(i),PL(i),VV(i),IN(i),NIN(i),D(2i),LO(2i),ND(2i+1),NLO(2i+1), with {a mathematical formula}i⩾0:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The attack expression can then be formulated as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       We observe that the attack expression satisfies the hypothesis of Proposition 9 hence it can be determined that the argumentation framework is finitary. Algorithm 1 can then be applied and it can be verified that it terminates determining the grounded extension {a mathematical formula}G={F1,F2,F3,F4}∪LA∪LB∪LC∪(LD∩{016i+12:i⩾0})∪(LE∩{016i+5:i⩾0})∪(LF∩{016i+14:i⩾0})∪LG∪LH∪LI∪LJ. Using the method included in the proof of Theorem 3 it can also be verified that G is stable, which implies that G is also the unique preferred extension.
      </paragraph>
      <paragraph>
       From the argumentation perspective the situation is not pathological per se and in fact this oscillating behavior is the desired one in case a person continuously enters and exits a room. Computing a compact representation of the grounded extension is however useful since it can be passed to a higher-level reasoning module which may detect the anomaly that the conclusions entailed by the system involve a person entering and exiting the same room let say every 5 seconds (or less). It can also be observed that, in this case, the produced sequence of arguments is not actually infinite since the oscillating behavior will stop with the sunrise the morning after (or the semester after if we are in a polar winter). However, we are interested in analyzing (and stopping) such a very long sequence of arguments produced with a regular pattern well before it reaches its “natural” termination. To this purpose it can be definitely more advantageous to treat it as an infinite sequence with compact representation rather than dealing explicitly with a finite sequence of thousands (if not millions) of “machine-produced-always-the-same” arguments.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Treatments of infinite afs have, as already outlined, been largely limited to specific instances exemplifying particular properties, e.g. that infinitary frameworks may occur naturally, as in the main example from [37] presented in the previous section, or the issue of existence of semi-stable extensions [30], [91]. Beyond such examples the principal results have not advanced noticeably since the general properties proven in [37] were established. In particular, the question of computational issues in infinite afs has not been considered.
     </paragraph>
     <paragraph>
      At heart (interpretative matters aside) Dungʼs af model is graph-theoretic (a property exploited in much extant work on algorithmic and complexity treatments of afs). The computational theory of infinite directed graphs has, in contrast, long been recognized as a core area of graph theory, arguably dating back to the beginning of the 20th century in the work of Thue [86]. Indeed, as observed by Morvan [66]: “When dealing with computers, infinite graphs are natural objects”.
     </paragraph>
     <paragraph>
      The idea of viewing vertex sets as a formal language with an edge relationship determined by operations on words representing vertices dates back at least as far as Muller and Schupp [67] and much of the focus of such computational treatments from a graph-theoretic perspective has tended to concentrate on, what may loosely be termed, “specification processes” for generating families of infinite graphs and model-theoretic treatments of logics defined via these processes. Thus, Courcelle [33] addresses properties expressible in monadic second-order logic with respect to bounded-width infinite graphs; Blumensath and Grädel [19] consider model-theoretic issues for properties expressible in first-order logic augmented with a quantifier, {a mathematical formula}∃ω, expressing the existence of infinitely many objects within its scope. The “reachability problem” (given u and v is there a directed path of edges from u to v) of importance in analyses of program behavior, has been widely studied, e.g. in Thomas [85] and Colcombet [31].
     </paragraph>
     <paragraph>
      In these treatments, as well as in our own approach, the central concern is that of “finite presentations of infinite objects” and so, unsurprisingly, the mechanisms adopted exhibit some structural similarities, e.g. in the use of automata-theoretic models. Overall, however, the issues of interest differ: in particular, aside from specialized studies such as that of Bean [13] regarding colorings of infinite graphs, properties impinging directly on graph-theoretic views of extension-based semantics have not explicitly been dealt with.
     </paragraph>
     <paragraph>
      Turning to another field related to argumentation, infinite structures have also received a significant deal of attention in the field of logic programming where admitting function symbols and recursion in the language gives rise to possibly infinite domains. Hence, a significant gain in expressiveness has to be traded off with the possibility of actual implementation in practical solvers. Focusing on the family of ASP (Answer Set Programming) solvers, Bonatti [21], [22] investigated the class of finitary logic programs which admit unbounded (possibly infinite) domains and cyclic definitions while ensuring that inference is r.e.-complete. Finitary logic programs are therefore amenable to implementation within existing ASP solvers with suitable extensions. A larger class of logic programs with functions called finitely grounded is shown to preserve most of the good properties of finitary programs in [12]. Unfortunately the class of finitary logic programs is undecidable: several subsequent works have then been devoted to investigate other classes of logic programs allowing functions, trading off expressiveness and tractability in various ways. In [82], [48] a decidable class of disjunctive logic programs with function symbols under stable model semantics, called {a mathematical formula}FDNC, is introduced and a method is provided to finitely represent all the (possibly infinite) stable models of a given {a mathematical formula}FDNC program. In [26], [28] the semi-decidable class of finitely ground programs is considered, along with its decidable subclass of finite domain programs, while another decidable subclass, called argument restricted, has been analyzed in [60]. Further, a decidable subclass of finitary programs, called FP2, has been recently presented in [11]. On the implementation side, the DLV solver [59] has been extended to encompass the treatment of finitely ground and finite domain programs resulting in a publicly available system called DLV-complex [27].
     </paragraph>
     <paragraph>
      The above studies witness a large interest in reasoning with infinite domains in answer set programming, with a range of motivations including the explicit treatment of recursive data structures like lists and trees, the encoding of problems not admitting a priori bounds on the solution size (e.g. planning or reasoning about actions), and the consideration of potentially infinite processes in time (a biology-inspired example is provided in [48]). While many of the above needs are common to argumentation theory (and more generally to any approach to defeasible reasoning, as remarked in Section 2) it has to be acknowledged that the significant advancements both on the theoretical and on the application side surveyed above have no counterpart (yet) in the argumentation field, so that the useful connections and interplay between the two fields have definitely to be regarded as a future research subject. As far as the present work is concerned, it can be remarked in particular that the investigations surveyed above lie at the level of the representation language, which is abstracted away in Dungʼs framework, hence our work concerns a different, and not directly comparable, abstraction level. Moreover the above works are based on the stable model semantics adopted in the context of ASP solvers, while the approach proposed in this paper is not committed to a specific semantics choice and hence is applicable beyond the limits of the stable semantics, which, as well-known, does not always guarantees the existence of extensions (the existence of models in the logic programming context) and does not feature, in general, some desirable properties like directionality or relevance (see [8] for a discussion).
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Formal languages and automata
     </section-title>
     <paragraph>
      A standard approach to the problem of representing an infinite collection of objects via a finite specification is to exploit so-called formal grammars and their associated machine models. In this section we review some basic elements and results from this discipline to complement the basic definitions given in Section 3.2.
     </paragraph>
     <paragraph>
      Given a formal grammar, {a mathematical formula}G=〈Σ,V,P,S〉 (Definition 8), and a production rule {a mathematical formula}α→β∈P, for all {a mathematical formula}γ,δ∈(V∪Σ)⁎ we say that γαδ derives γβδ in G ({a mathematical formula}γαδ⇒Gγβδ) and in general {a mathematical formula}u⇒G⁎w whenever there is a finite sequence of derivations such that{a mathematical formula} A derivation {a mathematical formula}u⇒Gw is terminated if {a mathematical formula}w∈Σ⁎. The language generated by {a mathematical formula}G=〈Σ,V,P,S〉, denoted as {a mathematical formula}L(G), is{a mathematical formula} A language, {a mathematical formula}L⊆Σ⁎, is recognizable if there is a formal grammar {a mathematical formula}G=〈Σ,V,P,S〉 for which {a mathematical formula}w∈L if and only if {a mathematical formula}w∈L(G).
     </paragraph>
     <paragraph>
      Notice that, in general, formal grammars provide a process for proving that {a mathematical formula}w∈L(G) and that there is not, necessarily, a unique sequence of derivations under which {a mathematical formula}S⇒G⁎w.
     </paragraph>
     <paragraph label="Definition 17">
      A grammar {a mathematical formula}〈Σ,V,P,S〉 is unrestricted if P is allowed to contain arbitrary rules {a mathematical formula}α→β (subject to the constraint that {a mathematical formula}α∉Σ⁎). It is context-sensitive if {a mathematical formula}∀α→β∈P we have {a mathematical formula}|β|⩾|α|; context-free if {a mathematical formula}∀α→β∈P we have {a mathematical formula}α∈V and right-linear if every {a mathematical formula}α→β∈P has the form {a mathematical formula}Vi→ε or {a mathematical formula}Vi→σ or {a mathematical formula}Vi→σVj for {a mathematical formula}Vi, {a mathematical formula}Vj∈V and {a mathematical formula}σ∈Σ.
     </paragraph>
     <paragraph>
      Recall that a language L is recursively enumerable (r.e.) if there is a Turing machine (TM) program, M, that given any {a mathematical formula}w∈L as input will eventually halt and accept w; with L being recursive if there is a TM program, M, that given any {a mathematical formula}w∈Σ⁎ as input eventually halts and accepts any {a mathematical formula}w∈L and halts and rejects any {a mathematical formula}w∉L. We use the term decidable to describe languages which are recursive and semi-decidable for those which are recursively enumerable. The term effective algorithm for L will be used for an algorithmic process, e.g. a Turing machine program, that witnesses L as decidable.{sup:27}
     </paragraph>
     <paragraph label="Fact 3">
      <list>
       <list-item label="(a)">
        {a mathematical formula}L⊆Σ⁎is recursively enumerable if and only if there is an unrestricted grammar, G such that{a mathematical formula}L(G)=L.
       </list-item>
       <list-item label="(b)">
        {a mathematical formula}L⊆Σ⁎is recursive if and only if there are unrestricted grammars,{a mathematical formula}G1and{a mathematical formula}G2such that{a mathematical formula}L(G1)=Land{a mathematical formula}L(G2)=L¯, i.e.{a mathematical formula}L(G2)=Σ⁎∖L.
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      It is well known that there are languages that fail to be r.e.
     </paragraph>
     <paragraph>
      Regular languages (Definition 7) are captured by a syntactic formalism called regular expressions. A regular expression, E over Σ is constructed by a finite number of applications of the following{a mathematical formula}
     </paragraph>
     <paragraph>
      The associated regular languages {a mathematical formula}L(E)⊆Σ⁎ being,{a mathematical formula} In order to reduce notational complications we will, in general, equate a regular expression, R, with the language, {a mathematical formula}L(R), it describes, thus writing R for both cases. Where no ambiguity arises, we dispense with superfluous parentheses.
     </paragraph>
     <paragraph label="Fact 4">
      Let{a mathematical formula}reg⊆2Σ⁎be the property describing all regular languages, i.e.{a mathematical formula}L∈regif and only if L is a regular language. The classregis closed with respect to all of the operations{a mathematical formula}θ∈{∪,∩,{}¯,∖,⋅,⁎,/,rev}.
     </paragraph>
     <paragraph>
      The class of machine models that express exactly the regular languages are the deterministic finite automata (Definition 9), other classes of finite automata can also be considered.
     </paragraph>
     <paragraph label="Definition 18">
      A non-deterministic finite automaton (ndfa) {a mathematical formula}NM=〈Σ,Q,q0,F,δ〉 has {a mathematical formula}δ:Q×Σ→2Q, indicating that in some states and symbols there may be more than one “next” state (or even that no state at all can be reached should {a mathematical formula}δ(q,σ)=∅). An ε-ndfa has a state transition function {a mathematical formula}δ:Q×Σ∪{ε}→2Q where the interpretation of {a mathematical formula}δ(q,ε)=Q′⊆Q is that having reached state q the automaton may process its next input symbol {a mathematical formula}σ∈Σ from q itself or from any state in {a mathematical formula}δ(q,ε). We identify a sub-class, the so-called “ε-dfa” of ε-ndfa via those whose transition function satisfies: {a mathematical formula}δ:Q×Σ→Q and {a mathematical formula}δ:Q×{ε}→2Q, i.e. ε-dfa specify exactly one successor state for each {a mathematical formula}q∈Q and {a mathematical formula}σ∈Σ but can allow arbitrary ε transitions between states.For a ndfa, M, {a mathematical formula}w=wk⋅w2⋯w1∈Σ⁎ is accepted by M, written {a mathematical formula}w∈L(M) if there is at least one sequence of states {a mathematical formula}qi1qi2…qik such that {a mathematical formula}qi1∈δ(q0,w1), {a mathematical formula}qij∈δ(qij−1,wj) for {a mathematical formula}2⩽j⩽k and {a mathematical formula}qik∈F. For ε-ndfa{a mathematical formula}w=wk⋅wk−1⋯w1∈Σ⁎ is accepted by M, if there is a finite sequence {a mathematical formula}qj1qj2…qjr of states with {a mathematical formula}r⩾k and a finite sequence {a mathematical formula}α1α2…αr with {a mathematical formula}αi∈{ε}∪Σ such that: {a mathematical formula}αr⋅αr−1⋯α1=w, {a mathematical formula}qi1∈δ(q0,α1), {a mathematical formula}qij∈δ(qij−1,αj) for {a mathematical formula}2⩽j⩽r, and {a mathematical formula}qjr∈F. The concept of acceptance by ε-dfa is defined similarly.
     </paragraph>
     <paragraph label="Fact 5">
      For{a mathematical formula}L⊆Σ⁎the following are equivalent.
     </paragraph>
     <list>
      <list-item label="(a)">
       L is a regular language.
      </list-item>
      <list-item label="(b)">
       There is an ε-ndfa, M, for which{a mathematical formula}L(M)=L.
      </list-item>
      <list-item label="(c)">
       There is an ε-dfa, M, for which{a mathematical formula}L(M)=L.
      </list-item>
      <list-item label="(d)">
       There is andfa, M, with{a mathematical formula}L(M)=L.
      </list-item>
      <list-item label="(e)">
       There is adfa, M with{a mathematical formula}L(M)=L.
      </list-item>
      <list-item label="(f)">
       There is a right-linear grammar, G, for which{a mathematical formula}L(G)=L.
      </list-item>
     </list>
     <paragraph label="Fact 6">
      <list>
       <list-item label="(a)">
        Given any finite automaton (dfa,ndfa, ε-dfaor ε-ndfa),{a mathematical formula}M=〈Σ,Q,q0,F,δ〉, it may decided in polynomial time (in{a mathematical formula}|Q|+|Σ|) if{a mathematical formula}L(M)=∅.
       </list-item>
       <list-item label="(b)">
        Given twodfas accepting languages{a mathematical formula}L1and{a mathematical formula}L2there are effective algorithms for constructing adfaaccepting{a mathematical formula}L1∩L2,{a mathematical formula}L1∪L2,{a mathematical formula}L1∖L2,{a mathematical formula}L1/L2.
       </list-item>
       <list-item label="(c)">
        Every regular language{a mathematical formula}L⊆Σ⁎has a unique{sup:28}minimal number of statesdfa, M for which{a mathematical formula}L(M)=L. Furthermore, given{a mathematical formula}M′with{a mathematical formula}L(M′)=Lthe unique minimized automaton, M with{a mathematical formula}L(M)=L(M′)=Lmay be constructed in polynomial time in{a mathematical formula}|QM′|+|Σ|.
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      Fact 6(c) is the Myhill–Nerode Theorem [68], a polynomial time algorithm for constructing the minimal automaton may be found in [57, Chap. 3.4]; the most efficient (currently known) algorithm is that of Hopcroft [56] which takes at most {a mathematical formula}O(|Q|log|Q|) steps to minimize a dfa with {a mathematical formula}|Q| states.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Proofs
     </section-title>
     <section label="B.1">
      Proofs of Section 4
      <paragraph label="Proposition 1">
       For{a mathematical formula}Xas introduced inDefinition 10, there are choices of{a mathematical formula}A⊆X×Xsuch that there is no formal grammar, G with{a mathematical formula}L(G)=LA⊆{0i⋅1⋅0j:i,j⩾1}.
      </paragraph>
      <paragraph label="Proof">
       It is well-known that Turing machine programs may be encoded as words in {a mathematical formula}{0,1}⁎ in such a way that if {a mathematical formula}β(M) is the encoding of some TM, M, then there is a (so-called universal) TM which given the pair {a mathematical formula}〈β(M),w〉 as input, exactly simulates the computational steps of M on input w.{sup:29} Furthermore it can be decided if any {a mathematical formula}w∈{0,1}⁎ is such that {a mathematical formula}w=β(M) for some TM program M. For any such encoding scheme we may use the standard lexicographic ordering{sup:30} of {a mathematical formula}{0,1}⁎ to order TM programs, so that{a mathematical formula} Finally, we recall that there is no formal grammar, G, that generates the following language:{a mathematical formula} We can now define the language {a mathematical formula}LA with the property required via{a mathematical formula} From which it follows that a grammar G with {a mathematical formula}L(G)=LA allows a grammar {a mathematical formula}G¬ε-halt with {a mathematical formula}L(G¬ε-halt)=non-halt-empty to be built.  □
      </paragraph>
      <paragraph label="Proposition 2">
       Given an arbitrary (i.e. unrestricted) grammar G over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is not semi-decidable, i.e. there is no TM program which given (a description of) G as input halts and accepts precisely those G for which{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}.
      </paragraph>
      <paragraph label="Proof">
       Immediate consequence of Riceʼs Theorem for r.e. Index Sets, [79], see e.g. [57, pp. 189–192] or [38, pp. 57–66].{sup:31}  □
      </paragraph>
      <paragraph label="Proposition 3">
       Given an arbitrary context-sensitive grammar, G, over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is not semi-decidable.
      </paragraph>
      <paragraph label="Proof">
       The problem of determining if {a mathematical formula}L(G)=∅ for an arbitrary context-sensitive grammar (over alphabet {a mathematical formula}{0,1}) is not semi-decidable. Given a context-sensitive grammar G over {a mathematical formula}{0,1} we construct a context-sensitive grammar {a mathematical formula}G′ over {a mathematical formula}{0,1} with the property that {a mathematical formula}L(G′)⊆{0i⋅1⋅0j:i,j⩾1} if and only if {a mathematical formula}L(G)=∅. Let S be the start symbol of G. Add a new starting symbol {a mathematical formula}S′ to G with a single production {a mathematical formula}S′→1⋅S to give the new grammar {a mathematical formula}G′. Then given that any word actually generated by {a mathematical formula}G′ must begin with the symbol 1, the only way in which {a mathematical formula}L(G′)⊆{0i⋅1⋅0j:i,j⩾1} would be if {a mathematical formula}L(G′)=∅. This can only be the case if {a mathematical formula}L(G)=∅ to begin with.  □
      </paragraph>
      <paragraph label="Proposition 4">
       Given an arbitrary context-free grammar (cfg), G, over the alphabet{a mathematical formula}{0,1}the problem of determining if{a mathematical formula}L(G)⊆{0i⋅1⋅0j:i,j⩾1}is decidable.
      </paragraph>
      <paragraph label="Proof">
       First note that {a mathematical formula}L010={0i⋅1⋅0j:i,j⩾1} is a regular language, and hence its complement {a mathematical formula}L010¯ is a regular language too. Now, given G a context-free grammar over the alphabet {a mathematical formula}{0,1}, checking {a mathematical formula}L(G)⊆L010 is equivalent to check {a mathematical formula}L(G)∩L010¯=∅. It is well-known [57] that the intersection of a context-free language (in our case {a mathematical formula}L(G)) with a regular language (in our case {a mathematical formula}L010¯) is a context-free language, whose specification can be constructed from those of {a mathematical formula}L(G) and {a mathematical formula}L010¯. The conclusion then follows from the fact that verifying the emptiness of the language generated by a context-free grammar can be done in polynomial time [57].  □
      </paragraph>
      <paragraph label="Proposition 5">
       Given{a mathematical formula}M=〈Q,{0,1},q0,F,δ〉adfaover the alphabet{a mathematical formula}{0,1}there is a polynomial (in{a mathematical formula}|Q|) algorithm that decides{a mathematical formula}L(M)⊆{0i⋅1⋅0j:i,j⩾1}.
      </paragraph>
      <paragraph label="Proof">
       The dfa, M, accepts a subset of {a mathematical formula}{0i⋅1⋅0j:i,j⩾1} if and only if {a mathematical formula}L(M)∖{0i⋅1⋅0j:i,j⩾1}=∅. Noting the language {a mathematical formula}{0i⋅1⋅0j:i,j⩾1} is regular and that for dfas, M, {a mathematical formula}M′ a dfa accepting exactly {a mathematical formula}L(M)∖L(M′) may be constructed in polynomial time, the proof is completed by observing that {a mathematical formula}L(M)=∅ is also decidable in polynomial time for any given dfa.  □
      </paragraph>
      <paragraph label="Proposition 6">
       Let L be any subset of{a mathematical formula}{0i⋅1⋅0j:i,j⩾1}with the following property: there are infinitely many values of k such that{a mathematical formula}{0k⋅1⋅0m:m⩾1}∩L≠∅ and for all{a mathematical formula}0n⋅1⋅0m∈L,{a mathematical formula}n⩽m. Then L is not a regular language.
      </paragraph>
      <paragraph label="Proof">
       From the Pumping Lemma for regular languages, cf. [57, Chap. 3.1], with any regular language, L, there is an associated constant, {a mathematical formula}KL, such that: for all {a mathematical formula}w∈L, with {a mathematical formula}|w|⩾KL, {a mathematical formula}w=x⋅y⋅z with {a mathematical formula}|x⋅y|&lt;KL, {a mathematical formula}|y|⩾1 and {a mathematical formula}x⋅yt⋅z∈L for all {a mathematical formula}t⩾0. Thus proceeding by contradiction it suffices to consider some {a mathematical formula}w=0r⋅1⋅0s∈L with {a mathematical formula}r⩾KL: note that the existence of a suitable w is guaranteed by the premise that there are infinitely many distinct values of k for which {a mathematical formula}0k⋅1⋅0m∈L. Now, since by the condition {a mathematical formula}|x⋅y|&lt;KL⩽r 1 does not belong to {a mathematical formula}x⋅y, we can write {a mathematical formula}w=x⋅y⋅0a⋅1⋅0s=0p⋅0q⋅1⋅0s with {a mathematical formula}q=|y|, {a mathematical formula}p=|x|+a, and {a mathematical formula}p+q&lt;KL. It follows that all words of the form {a mathematical formula}0p+tq⋅1⋅0s are in L for all {a mathematical formula}t⩾0. Now choosing t so that {a mathematical formula}p+tq&gt;s yields a word which violates the conditions for membership in L.  □
      </paragraph>
     </section>
     <section label="B.2">
      Proofs of Section 5
      <paragraph label="Theorem 1">
       Let{a mathematical formula}p∈AE(Σ)be any attack expression over Σ. The mapping{a mathematical formula}p̲:2Σ⁎→2Σ⁎is reasonable.
      </paragraph>
      <paragraph label="Proof">
       Let p be an attack expression over Σ. We proceed by induction on {a mathematical formula}size(p)⩾0.The inductive base case involves {a mathematical formula}p∈{σ1,…,σk,I}. First observe that {a mathematical formula}p̲ in these cases satisfies the additivity requirement (R1) of Definition 12 since for any {a mathematical formula}S⊆Σ⁎ we have {a mathematical formula}p̲(S)∈{σ1,…,σk,S} and for each {a mathematical formula}w∈S, {a mathematical formula}p̲({w})∈{σ1,…,σk,{w}}. Hence in the case {a mathematical formula}p=σ we obtain{a mathematical formula} whereas for {a mathematical formula}p=I we have{a mathematical formula} Finally, since S is assumed regular to begin with, for each of the base case possibilities, we have {a mathematical formula}p̲(S) is also regular.Now inductively assume for some {a mathematical formula}k&gt;0 and all attack expressions over Σ, q, with {a mathematical formula}size(q)&lt;k the mapping given via {a mathematical formula}q̲ is a reasonable attack function. Consider any attack expression, p, over Σ for which {a mathematical formula}size(p)=k. Since {a mathematical formula}size(p)&gt;0 its construction must involve (at least) one of the operations from {a mathematical formula}{∪,KΣ⋅,⋅KΣ,/KΣ,KΣ/,∩KΣ,hd,tl}. We consider these in turn.If {a mathematical formula}p=q∪r then {a mathematical formula}p̲(S)=(q̲(S)∪r̲(S)). By the inductive hypothesis {a mathematical formula}q̲ and {a mathematical formula}r̲ are both reasonable, hence since ∪ preserves both the properties (R1) and (R2) it follows that {a mathematical formula}p̲ is reasonable.If {a mathematical formula}p=KΣ⋅q for some regular subset {a mathematical formula}KΣ of {a mathematical formula}Σ⁎{a mathematical formula} where, from the inductive hypothesis, {a mathematical formula}q̲ is reasonable. Thus{a mathematical formula} which is{a mathematical formula} by the additivity of {a mathematical formula}q̲. Again (R2) holds by virtue of the fact that {a mathematical formula}KΣ⋅ preserves regularity.The argument for {a mathematical formula}p=q⋅KΣ is similar.If {a mathematical formula}p=q/KΣ then: {a mathematical formula}p̲(S)=q̲(S)/KΣ, which, by the additivity of {a mathematical formula}q̲, is equivalent to{a mathematical formula} so that again {a mathematical formula}p̲ is additive from the fact that {a mathematical formula}q̲ is additive. The closure property is again easily verified.The case {a mathematical formula}p=KΣ/q is similar.If {a mathematical formula}p=q∩KΣ then {a mathematical formula}p̲(S) is{a mathematical formula} and{a mathematical formula} so that again additivity holds. Closure is trivially established.For {a mathematical formula}p=hd(q), we get{a mathematical formula} using additivity of {a mathematical formula}q̲ for the second equality.To see that (R2) holds it suffices to note that (given a regular language S) {a mathematical formula}hd(q̲(S))⊆Σ is finite and hence trivially a regular language.For {a mathematical formula}p=tl(q):{a mathematical formula} using the additivity of {a mathematical formula}q̲ for the third equality.It remains to show {a mathematical formula}p̲(S) is regular if S is so. Consider a dfa, {a mathematical formula}Mq, accepting {a mathematical formula}q̲(S) – such a dfa being guaranteed by the fact that {a mathematical formula}q̲(S) is regular. In order to build a dfa accepting {a mathematical formula}tl(q̲(S)) it suffices to replace its accepting states, {a mathematical formula}Fq by {a mathematical formula}{r:δ(r,σ)∈Fq}. We deduce that {a mathematical formula}tl(q) gives rise to {a mathematical formula}p̲ satisfying R2 thus completing the inductive argument.  □
      </paragraph>
      <paragraph label="Proposition 7">
       If μ is a reasonable mapping over the domain{a mathematical formula}2Σ⁎then{a mathematical formula}μXis a reasonable mapping over the domain{a mathematical formula}2X.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}X⊆Σ⁎ and {a mathematical formula}μ:2Σ⁎→2Σ⁎ be a reasonable mapping. First note that {a mathematical formula}μX:2X→2X is additive since for any {a mathematical formula}S⊆X we have {a mathematical formula}μX(S) equal to{a mathematical formula} Finally, that {a mathematical formula}μX preserves regularity for regular subsets S of {a mathematical formula}X is immediate from {a mathematical formula}μX(S)=μ(S)∩X.  □
      </paragraph>
      <paragraph label="Theorem 2">
       Let{a mathematical formula}〈M,a〉be anafswith{a mathematical formula}L(M)=Xand{a mathematical formula}a∈AE(Σ). The mapping{a mathematical formula}a̲+:2Σ⁎→2Σ⁎, defined as{a mathematical formula}a̲+(S)={v∈Σ⁎:∃u∈Ss.t.u∈a̲(v)}is closed wrt regular languages.
      </paragraph>
      <paragraph label="Proof">
       Consider the various forms that {a mathematical formula}a∈AE(Σ) may have. We show by induction on {a mathematical formula}size(a) that if S is a regular language then {a mathematical formula}a̲+(S) is a regular language too.
      </paragraph>
      <paragraph label="Case 1">
       {a mathematical formula}size(a)=0 (Inductive base – Fact 2.1)In this case, {a mathematical formula}a∈{σ1,…,σk,I}.For {a mathematical formula}a=σi,{a mathematical formula} We note, in view of the properties {a mathematical formula}tl(∅)=∅, {a mathematical formula}tl({σ})=ε and {a mathematical formula}∅⋅L=∅, that {a mathematical formula}a̲+(S)=tl(S∩{σi})⋅Σ⁎, i.e. we do not need to explicitly represent the conditional behavior, thus allowing one to express {a mathematical formula}a+ as {a mathematical formula}tl(I∩σi)⋅Σ⁎.For {a mathematical formula}a=I, {a mathematical formula}a̲+(S)=S. Thus in each case {a mathematical formula}a̲+(S) is a regular language.Assuming for each a with {a mathematical formula}size(a)&lt;k, that {a mathematical formula}a̲+(S) is regular, consider {a mathematical formula}a∈AE(Σ) with {a mathematical formula}size(a)=k.
      </paragraph>
      <paragraph label="Case 2.1">
       {a mathematical formula}a=b∪c (Fact 2.2)Then{a mathematical formula} Via the inductive hypothesis and the closure properties of regular languages (see Fact 4 in Appendix A), this is a regular language.
      </paragraph>
      <paragraph label="Case 2.2">
       {a mathematical formula}a=b⋅KΣ (Fact 2.3){a mathematical formula} Recall that the quotient of a language {a mathematical formula}L1 wrt {a mathematical formula}L2 (denoted {a mathematical formula}L1/L2) is{a mathematical formula} It is easily seen that for {a mathematical formula}a=b⋅KΣ this leads to{a mathematical formula} That is, unless {a mathematical formula}u∈S has the form {a mathematical formula}p⋅q with {a mathematical formula}q∈KΣ, then {a mathematical formula}a̲+({u})=∅; for {a mathematical formula}u∈S which is of the required form, it is necessary to identify which arguments these (with the {a mathematical formula}KΣ component removed, i.e. replacing {a mathematical formula}p⋅q, {a mathematical formula}q∈KΣ with p) attack according to the specification b.Again, this case is completed by recalling that regular languages – which S and {a mathematical formula}KΣ are by definition – are closed under the quotient operator (see Fact 4 in Appendix A) and the inductive hypothesis which ensures that {a mathematical formula}b̲+ preserves regularity.
      </paragraph>
      <paragraph label="Case 2.3">
       {a mathematical formula}a=KΣ⋅b (Fact 2.4)The argument is similar to that used in Case 2.2, so that:{a mathematical formula} Hence if {a mathematical formula}w∈Σ⁎ does not have the form {a mathematical formula}p⋅q for some {a mathematical formula}p∈KΣ then {a mathematical formula}a̲+({w})=∅ otherwise {a mathematical formula}a̲+({w})=b̲+({q}), i.e.{a mathematical formula} However, noting that {a mathematical formula}rev(L⋅R)=rev(R)⋅rev(L), it follows that {a mathematical formula}p∈KΣ and {a mathematical formula}p⋅q∈S if and only if {a mathematical formula}rev(q)⋅rev(p)∈rev(S) and {a mathematical formula}rev(p)∈rev(KΣ) so that {a mathematical formula}{q:∃p∈KΣ s.t. p⋅q∈S} is {a mathematical formula}rev(T) where{a mathematical formula} and {a mathematical formula}a̲+(S)=b̲+(rev(rev(S)/rev(KΣ))) with this case following since regular languages are closed under {a mathematical formula}rev().
      </paragraph>
      <paragraph label="Case 2.4">
       {a mathematical formula}a=b/KΣ (Fact 2.5.){a mathematical formula}
      </paragraph>
      <paragraph label="Case 2.5">
       {a mathematical formula}a=KΣ/b (Fact 2.6){a mathematical formula}
      </paragraph>
      <paragraph label="Case 2.6">
       {a mathematical formula}a=b∩KΣ (Fact 2.7){a mathematical formula}
      </paragraph>
      <paragraph label="Case 2.7">
       {a mathematical formula}a=hd(b) (Fact 2.8){a mathematical formula} i.e. if {a mathematical formula}w∈S but {a mathematical formula}w∉Σ then {a mathematical formula}a̲+({w})=∅, if {a mathematical formula}σ∈S∩Σ, then σ attacks every argument v such that there in an element of {a mathematical formula}b̲({v}) having the form {a mathematical formula}σ⋅z.
      </paragraph>
      <paragraph label="Case 2.8">
       {a mathematical formula}a=tl(b) (Fact 2.9){a mathematical formula} from which {a mathematical formula}a̲+(S)=b̲+(Σ⋅S).  □
      </paragraph>
      <paragraph label="Proposition 8">
       Let{a mathematical formula}〈M,a〉be anafswith{a mathematical formula}L(M)=Xand{a mathematical formula}a∈AE(Σ). Define the mapping,{a mathematical formula}πa+:2X→2Xby{a mathematical formula}It holds that{a mathematical formula}πa+(S)=a̲X+(S).
      </paragraph>
      <paragraph label="Proof">
       By definition {a mathematical formula}πa+(S)={v∈X:∃u∈S s.t. u∈a̲(v)∩X}, which, since {a mathematical formula}S⊆X, is equivalent to {a mathematical formula}{v∈X:∃u∈S s.t. u∈a̲(v)}={v∈Σ⁎:∃u∈S s.t. u∈a̲(v)}∩X=a̲+(S)∩X=a̲X+(S).  □
      </paragraph>
     </section>
     <section label="B.3">
      Proofs of Section 6
      <paragraph label="Theorem 3">
       Let{a mathematical formula}〈M,a〉be anafs, with induced argumentation framework{a mathematical formula}〈X,A〉and{a mathematical formula}S⊆X. The following problems are decidable.
      </paragraph>
      <list>
       <list-item label="(a)">
        Deciding if the set S is conflict free.
       </list-item>
       <list-item label="(b)">
        For{a mathematical formula}x∈X, deciding if{a mathematical formula}x∈F(S), i.e. whether x is acceptable to S.
       </list-item>
       <list-item label="(c)">
        Deciding if{a mathematical formula}S∈Eadm(〈X,A〉), i.e. whether S is admissible.
       </list-item>
       <list-item label="(d)">
        Deciding if{a mathematical formula}S∈Estab(〈X,A〉), i.e. whether S is a stable extension.
       </list-item>
       <list-item label="(e)">
        Constructing adfaaccepting{a mathematical formula}F(S)=X∖πa+(X∖πa+(S)), i.e. the set of arguments acceptable to S.
       </list-item>
       <list-item label="(f)">
        Deciding if{a mathematical formula}S∈Ecomp(〈X,A〉), i.e. whether S is a complete extension.
       </list-item>
      </list>
      <paragraph label="Proof">
       We first observe that validating an instance {a mathematical formula}〈〈M,a〉,MS〉, where {a mathematical formula}MS is a finite automaton accepting S, as legal simply involves checking {a mathematical formula}L(MS)⊆L(M), i.e. constructing an automaton {a mathematical formula}MV accepting {a mathematical formula}L(MS)∖L(M) and checking that {a mathematical formula}L(MV)=∅ (see Fact 6(a) in Appendix A).For (a), S is conflict free if and only if {a mathematical formula}S+∩S=S−∩S=∅. Thus given a dfa, {a mathematical formula}MS with {a mathematical formula}L(MS)⊆X it suffices to check that {a mathematical formula}L(MS)∩πa−(S)=∅, i.e. construct {a mathematical formula}Mcf accepting {a mathematical formula}L(MS)∩πa−(S) and check that {a mathematical formula}L(Mcf)=∅.In (b), {a mathematical formula}x∈F(S) if and only if {a mathematical formula}(y∈πa−({x}))⇒(y∈πa+(S)) so that {a mathematical formula}x∈F(S) if and only if {a mathematical formula}πa+(S)⊇πa−({x}) which can be verified by constructing suitable automata {a mathematical formula}MS+ for {a mathematical formula}πa+(S), {a mathematical formula}Mx− for {a mathematical formula}πa−({x}) and checking that {a mathematical formula}L(Mx−)∖L(MS+)=∅.For (c), {a mathematical formula}S∈Eadm(〈X,A〉) if and only if S is conflict free, which can be verified using the result of part (a) and {a mathematical formula}S+⊇S−, i.e. every attacker y of an argument in S is counterattacked by some argument z of S. It follows that to check {a mathematical formula}S∈Eadm(〈X,A〉) having verified that S is conflict free requires only checking {a mathematical formula}πa−(S)∖πa+(S)=∅.Part (d) follows by checking that S is conflict free and {a mathematical formula}S∪πa+(S)=X.To show (e), first observe that {a mathematical formula}X∖πa+(S) consists of those arguments in {a mathematical formula}X that are not attacked by any argument in S. It follows that any argument that is attacked by some {a mathematical formula}y∈X∖πa+(S) cannot be acceptable wrt to S since S does not contain any counterattack. The set of arguments attacked by some {a mathematical formula}y∈X∖πa+(S) is just {a mathematical formula}πa+(X∖πa+(S)) and, hence, any argument that does not belong to this set, i.e. arguments in {a mathematical formula}X∖πa+(X∖πa+(S)) are acceptable to S. If S is a regular language, then since all stages preserve regularity, i.e. {a mathematical formula}πa+(S), {a mathematical formula}X∖πa+(S), {a mathematical formula}πa+(X∖πa+(S)) and {a mathematical formula}X∖πa+(X∖πa+(S)) are all regular, from Theorem 2 and the fact that there are effective algorithms for constructing a dfa accepting {a mathematical formula}S1∖L2 (see Fact 6 in Appendix A) we can construct the required dfa.Finally (f) is immediate from (a) and (e) and the definition of {a mathematical formula}Ecomp.  □
      </paragraph>
      <paragraph label="Theorem 4">
       Let{a mathematical formula}〈M,a〉be anafsin which the induced argumentation framework{a mathematical formula}〈X,A〉is finitary. The following problems are all semi-decidable.
      </paragraph>
      <list>
       <list-item label="(a)">
        Determining if{a mathematical formula}Estab(〈X,A〉)=∅.
       </list-item>
       <list-item label="(b)">
        Given a finite {a mathematical formula}R⊂X, determining if  {a mathematical formula}∀w∈R¬caadm(〈X,A〉,w).
       </list-item>
      </list>
      <paragraph label="Proof">
       The approach used is similar for both results and exploits the (propositional) form of the so-called Compactness Theorem.{sup:32}The lexicographic ordering, {a mathematical formula}⩽lex of {a mathematical formula}Σ⁎∖{ε} has {a mathematical formula}u⩽lexv if {a mathematical formula}|u|&lt;|v| or (when {a mathematical formula}|u|=|v|) if {a mathematical formula}u=σix, {a mathematical formula}v=σjy and {a mathematical formula}i&lt;j or when {a mathematical formula}u=σix, {a mathematical formula}v=σiy if either {a mathematical formula}x=y=ε or {a mathematical formula}x⩽lexy. We use {a mathematical formula}wi to denote the iʼth word in {a mathematical formula}Σ⁎∖{ε} under this ordering.Let {a mathematical formula}Z={z1,z2,…,zk,…} be an enumerable infinite set of propositional variables and define a bijective mapping {a mathematical formula}χ:Z↔Σ⁎ via {a mathematical formula}χ(zi)=wi. For part (a) consider the following collection of clauses {a mathematical formula}φ(Z):{a mathematical formula} where{a mathematical formula}{a mathematical formula} Thus if {a mathematical formula}S∈Estab(〈X,A〉) then the assignment {a mathematical formula}zi=⊤ iff {a mathematical formula}χ(zi)∈S will satisfy {a mathematical formula}φ(Z) and, conversely, if {a mathematical formula}〈α1,α2,…,ak,…〉 is a satisfying assignment to Z for {a mathematical formula}φ(Z) then the subset {a mathematical formula}{χ(zi):αi=⊤}∈Estab(〈X,A〉). It follows that {a mathematical formula}Estab(〈X,A〉)=∅ if and only if {a mathematical formula}φ(Z) is unsatisfiable, and hence via the Compactness Theorem, if and only if there is a finite subset of clauses from {a mathematical formula}φ(Z) that are collectively unsatisfiable.For any subset S of {a mathematical formula}Σ⁎ let{a mathematical formula} where{a mathematical formula}{a mathematical formula}For a finite S both {a mathematical formula}conf(S) and {a mathematical formula}range(S) are finite since for each element {a mathematical formula}zi of S the set of elements {a mathematical formula}zj corresponding to its attackers is finite. Moreover note that the set of clauses in {a mathematical formula}Cl(S) is strictly monotonic wrt inclusion (since each additional element {a mathematical formula}zi entails the addition of at least a clause in {a mathematical formula}range(S)) and that for each clause in {a mathematical formula}CONF(Z) and {a mathematical formula}RANGE(Z) there is a {a mathematical formula}zi such that if {a mathematical formula}zi∈S then the clause belongs to {a mathematical formula}Cl(S).Now consider the increasing (wrt inclusion) sequence of finite subsets S of {a mathematical formula}Σ⁎ obtained by adding incrementally the k-th element of {a mathematical formula}Σ⁎∖{ε} in the lexicographic order. Then for any finite subset Q of clauses from {a mathematical formula}φ(Z) it is clearly the case that there is some S in the sequence for which {a mathematical formula}Q⊆Cl(S).These observations yield the method given in Algorithm 2.To establish correctness it is sufficient to note that, by the compactness theorem, {a mathematical formula}φ(Z) is unsatisfiable iff some finite subset Q of its clauses is so, hence iff there is some finite set {a mathematical formula}SQ⊆X with {a mathematical formula}Q⊆Cl(SQ) yielding an unsatisfiable subset of clauses. Since {a mathematical formula}SQ is finite, such a subset will eventually have {a mathematical formula}SQ⊆S in the algorithm iff {a mathematical formula}φ(Z) is unsatisfiable, i.e. the Algorithm 2 will terminate whenever {a mathematical formula}Estab(〈X,A〉)=∅.For part (b), the formula {a mathematical formula}φ(Z)=CONF(Z)∧DEF(Z)∧IN(R) is used, where {a mathematical formula}CONF(Z) is as previously, {a mathematical formula}DEF(Z) is{a mathematical formula} and{a mathematical formula} A similar procedure is used to that of Algorithm 2, however S in l. 1 is initiated to R (the finite subset of {a mathematical formula}X forming part of the problem instance) and {a mathematical formula}Cl(S) in l. 6 is replaced by {a mathematical formula}conf(S)∧def(S)∧IN(R), so that {a mathematical formula}φ(Z) is satisfiable iff every finite subset of its clauses that include the clause {a mathematical formula}IN(R) is satisfiable: note that the assignment {a mathematical formula}zi:=⊥ for all i will satisfy every finite subset of {a mathematical formula}φ(Z)∖{IN(R)}.  □
      </paragraph>
      <paragraph label="Proposition 9">
       Let{a mathematical formula}〈M,a〉be anafswith induced argumentation framework{a mathematical formula}〈X,→a〉. Let{a mathematical formula}K={KΣ1,KΣ2,…,KΣr}be the set of regular expressions used in defining a, i.e. with operations{a mathematical formula}b⋅KΣ,{a mathematical formula}KΣ⋅b,{a mathematical formula}KΣ/b,{a mathematical formula}b/KΣand{a mathematical formula}b∩KΣ. If no {a mathematical formula}K∈Kuses the ⁎ operator then{a mathematical formula}〈X,→a〉is finitary.
      </paragraph>
      <paragraph label="Proof">
       Suppose {a mathematical formula}a∈AE(Σ) satisfies the conditions of the proposition statement. Consider any {a mathematical formula}x∈X. If, in contradiction to the claim, {a mathematical formula}πa−({x}) is unbounded then {a mathematical formula}a̲({x}) must yield an infinite language. Let a be a smallest (wrt size) member of {a mathematical formula}AE(Σ) with this property. Clearly {a mathematical formula}size(a)&gt;0 since all a with {a mathematical formula}size(a)=0 have {a mathematical formula}|a̲({x})|=1. Then a must have one of the forms {a mathematical formula}{b∪c,KΣ⋅b,b⋅KΣ,KΣ/b,b/KΣ,b∩KΣ,tl(b),hd(b)}, where {a mathematical formula}size(b)&lt;size(a) and {a mathematical formula}size(c)&lt;size(a), hence {a mathematical formula}|b̲({x})| and {a mathematical formula}|c̲({x})| are finite. The expression, {a mathematical formula}KΣ, uses only operations from {a mathematical formula}{⋅,+} and it is easily shown that these cannot generate an infinite subset of {a mathematical formula}Σ⁎. Then it is easy to see that all the operators above give rise to a finite language, i.e. {a mathematical formula}a̲({x}) is finite.  □
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>