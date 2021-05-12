<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Arguing about informant credibility in open multi-agent systems.
   </title>
   <abstract>
    This paper proposes the use of an argumentation framework with recursive attacks to address a trust model in a collaborative open multi-agent system. Our approach is focused on scenarios where agents share information about the credibility (informational trust) they have assigned to their peers. We will represent informants' credibility through credibility objects which will include not only trust information but also the informant source. This leads to a recursive setting where the reliability of certain credibility information depends on the credibility of other pieces of information that should be subject to the same analysis. Credibility objects are maintained in a credibility base which can have information in conflict. In this scenario, we will formally show that our proposal will produce a partially ordered credibility relation; such relation contains the information that can be justified by an argumentation process.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Open multi-agent systems have been characterized [20], [31] as multi-agent systems where the agents have different aims and goals and they can freely join and leave the system. In such system, it is possible to assume that agents display important characteristics: agents can be assumed to be self-interested and unreliable, agents lack a global perspective of the system, and there is no central control over the agents behavior that could facilitate the prediction of the interactions with other agents.
     </paragraph>
     <paragraph>
      In this paper, we will consider a set of deliberative agents that participate in a collaborative open multi-agent system in which each agent plays the role of an informant for other agents, and can receive information from multiple sources, i.e., several agents could contribute information to another agent. It is clear that some form of trust model is needed when the adoption of a critical decision depends on the credibility (informational trust) assigned to the information received from other agents. In multi-agent systems, interaction is a crucial activity and, through interaction, agents share different kinds of information. In our approach, agents will share information about the credibility or informational trust they have assigned to their peers and then, through this interaction, the credibility assigned to their peers could change. Since the credibility information received may be conflicting, we propose an argumentative formalism for handling decisions about the credibility information that an agent (as presented in [9], the trustor) stores about their informants (as presented in [9], the trustees). Therefore, when an agent is faced with conflictive information, the proposed argumentation framework can be used to decide which information is more credible, and hence, which information prevails.
     </paragraph>
     <paragraph>
      In multi-agent systems, representing the credibility associated with a piece of information and making the evaluation of this credibility possible are two important aspects when the agents have their own beliefs and can obtain new information from other sources [12]. Furthermore, as it was mentioned in [28], agents acting in open environments depend on reputation and trust mechanisms to evaluate the behavior of potential partners. Research in this area has increased considerably, and reputation and trust mechanisms have become key elements in the design of multi-agent systems [25], [33].
     </paragraph>
     <paragraph>
      In [28] and [32], a set of relevant aspects to classify trust models is proposed. In this proposal, we will consider only two of those aspects: information sources and a trust reliability measure. In [32] the authors suggest that “...Sometimes, as important as the trust/reputation value itself is to know how reliable is that value and the relevance it deserves in the final decision making process...”. In our approach, as in [36], [37], we introduce this type of information through the use of agent identifiers that represent the information sources, avoiding in that way the need of a separate data structure to maintain the measure of reliability. This leads to a recursive setting in which the reliability of certain credibility information depends on the credibility of other pieces of information that should be subject to the same analysis.
     </paragraph>
     <paragraph>
      This research is motivated by two key factors. To begin with, the existence of large amounts of available data that intelligent agents and information system can access nowadays from different sources such as social networks, open data servers, and other similarly available origins. Additionally, the need of having a way to consider the reliability of that data. Indeed, many actual applications, such as booking services, buying and selling portals, renting locations pages or tourist attractions recommending services, etc. request and use their customers' evaluations to produce rankings of the products they handle. Moreover, nowadays there is also a tendency of having a reciprocal evaluation of the informants' reliability. The combination of these two factors produces a significant amount of information regarding the reliability of those informants, and these assessments are becoming available. Since that information could come from different sources (e.g., social media, open data), it is clear that substantial inconsistency in the obtained data could arise; therefore, there is a need for devising a way of deciding which information prevails. In this scenario, since the sources of that information are dynamic, we consider that the classical approaches of revising databases eliminating information for the sake of maintaining consistency would not be appropriated because that approach loses valuable information. In our proposal, we examine a scenario where the two factors mentioned above are present: we propose a formalization that allows to represent the evaluation of informant agents and to investigate the possibility of dealing with information from different sources that, when put together, the result could be contradictory.
     </paragraph>
     <paragraph>
      Below, we will introduce an example in the stock market domain that considers the credibility that a particular agent called Tory assigns to its informants in this topic. Our aim of using this example is to provide a more intuitive introduction of the ideas in order to help the reader follow the presentation. Furthermore, it will be employed as a running example for the rest of the paper, though in Section 5 other applications domains will be discussed. Here, we will restrict our research to considering credibility information for a single topic; multi-topic or multi-context credibility orders are left as future work. Intuitively, the notion of credibility should be irreflexive and transitive.
     </paragraph>
     <paragraph label="Example 1">
      Running exampleLet Alex, Barbara, and Carla (abbreviated A, B, C) be stock market experts, and let Harry, John, and Kate (abbreviated H, J, K) be journalists on this topic. Agent Tory (T) has all the agents mentioned above as its informants, and T has collected the following information about their credibilities in the stock market topic. According to Kate, Alex is more credible than Carla (represented {a mathematical formula}A&gt;C); and according to Harry, Carla is more credible than Barbara, {a mathematical formula}(C&gt;B). However, for John, Barbara is more credible than Alex, {a mathematical formula}(B&gt;A). Finally, according to the editor of a newsletter called X-market, which specializes on this topic, the journalist Kate is more credible than John, {a mathematical formula}(K&gt;J).Now, assume that Tory has to decide whether Alex is more credible than Barbara. Tory can conclude {a mathematical formula}B&gt;A using the information obtained from John but, assuming the credibility relation is transitive, Tory can also infer {a mathematical formula}A&gt;B from the information obtained from Kate ({a mathematical formula}A&gt;C) and Harry ({a mathematical formula}C&gt;B). In this situation, Tory can use the information that she has about the credibility of the journalists John, Harry and Kate to decide whether {a mathematical formula}A&gt;B or {a mathematical formula}B&gt;A prevails. Since the editor of X-market reports that {a mathematical formula}K&gt;J, then Tory has a reason to consider Kate more credible than John on this topic and therefore, a reason to support that Alex is more credible than Barbara.
     </paragraph>
     <paragraph>
      The example above describes a situation where an agent receives information from different sources and shows how the agents' subjective attribution of credibility to a particular informant can be related to the credibility attributed to others. In our proposal, we will deal with information that an agent stores about the credibility of its informants, and also we will assume that the information received from an agent is as credible as the agent that supplies it.
     </paragraph>
     <paragraph>
      In decision-making problems where information coming from multiple agents is involved it is possible to use the credibility of the informants to help in making a decision. Similar to [1], [12], [34], we will favor the use of the word credibility to refer to this characteristic of informant agents as this particular word carries an intuitive sense that helps to understand the related problems. Here, the credibility of informant agents will be represented in a credibility base that will store the credibilities that an agent assigns to its informants and also its reliability.
     </paragraph>
     <paragraph>
      In the literature, credibility has been represented using elements of possibility theory, see [6], [12], or adopting a symbolic approach, as in [8], [13], [18], [24], [35], [36], [37]. Some of these symbolic approaches, for instance [24], [35], propose to use total orders whereas others [36], [37] adopt partial orders providing the capability of representing cases where the credibility of two agents cannot be compared because of different reasons, e.g., the relation between them has not been established. In particular in [36], following belief revision techniques, the authors formalized change operators over a credibility base to maintain it as non-contradictory. Although those change operators have been designed using the principle of informational economy (i.e., when accepting a new piece of information the agent should aim at a minimal change of its previously held beliefs), in general, when maintaining consistency some information is lost. We will follow a different tack in this work: our proposal gives the capability of adding multiple beliefs simultaneously (e.g., to join two or more bases) without having to eliminate the possible contradictions that may arise.
     </paragraph>
     <paragraph>
      Since obtaining information is a very expensive process, in our approach an agent will keep all the information it receives thus allowing the possibility of having an inconsistent credibility base. In this manner, in dynamic scenarios with many interactions where the trust model uses witness information[28], [32], our proposal will cover cases in which beliefs that in the current situation are less important, but may become so in the future, are not lost. It is also important to note that, since we keep all the information, the order in which new information is added to the credibility base will not affect the result as occurs in [36]. In this paper, we will propose how to equip agents with a mechanism that will allow them to coherently infer information from their credibility base despite possible inconsistencies. Therefore, the main contribution of our proposal is to define an argumentation formalism which will provide the capability to coherently infer strict partial orders from such bases. An argument in this formalism will provide a reason to support the fact that an informant is more credible than other. As arguments can be challenged, we will introduce different types of attacks. Given the recursive nature of the attacks in our system, in order to define which arguments will be accepted, and thus which conclusions will be obtained, we will use the Argumentation Framework with Recursive Attacks (AFRA) introduced in [3], [4], which allows attacks to the attack relation. We will use acceptability semantics (in particular preferred extensions) to determine which are the accepted arguments in our system, and then, we will formally show that the conclusions of an extension from a credibility base constitute a partial order with respect to the credibility relation.
     </paragraph>
     <paragraph>
      The rest of this paper is structured as follows. In Section 2, we will introduce how to represent the credibility of informants. In Section 3, an argumentation framework with three different type of attacks is proposed. Then, in Section 4 we will define how to obtain credibility partial orders from potentially inconsistent credibility bases using our argumentation approach. In Section 5 we discuss how our approach can be applied to some real world domains. Section 6 analyzes related work, and finally, in Section 7 conclusions are offered and ideas for future work are given. All the proofs for the results will be included in the corresponding sections.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Representing informant's credibility
     </section-title>
     <paragraph>
      In this proposal, we consider a finite set {a mathematical formula}A of identifiers for naming informant agents and each agent will be labeled with a unique name from that set. Agents' identifiers will be denoted with uppercase italic letters that can have subscripts and each identifier will represent a unique agent; thus {a mathematical formula}A = {a mathematical formula}{A,B,…,Z,A1,…,Zn}. Since our approach assumes a collaborative environment, it is unnecessary to make provisions to prevent identity theft. We also assume that each agent already has a repository of the informational trust of other agents, i.e., we do not require any particular bootstrapping mechanism. Following [36], the credibilities an agent assigns to its informant agents is stored in a Credibility Base as defined next.
     </paragraph>
     <paragraph label="Definition 1">
      Credibility object – credibility baseLet {a mathematical formula}A be a set of agent identifiers and {a mathematical formula}P,Q,S∈A. A credibility object is a pair {a mathematical formula}[P&gt;Q,S] which represents that agent P is strictly more credible than Q, and the agent S is the information source of the credibility element{a mathematical formula}P&gt;Q. A credibility base is a finite set {a mathematical formula}C of credibility objects.
     </paragraph>
     <paragraph>
      A credibility base stores credibility objects that are pairs of credibility elements together with their associated information source which will represent the reliability of the associated credibility element. Observe that, as in [36], the credibility base itself stores the information for considering the reliability of each element. Thus, there is no need for a separate data structure maintaining the measure of reliability of credibility elements. We include below a simple example that will be used for introducing the main concepts of our approach.
     </paragraph>
     <paragraph label="Example 2">
      Consider the credibility base:{a mathematical formula} This set represents the information introduced above for our running example: the agent K has informed that A is more credible than C ({a mathematical formula}A&gt;C), the agent H has informed that {a mathematical formula}C&gt;B, J has informed that {a mathematical formula}B&gt;A, and X (the editor of the newsletter) has informed that {a mathematical formula}K&gt;J.
     </paragraph>
     <paragraph>
      Consider the credibility base {a mathematical formula}C2 from Example 2 where the following two credibility elements {a mathematical formula}A&gt;C and {a mathematical formula}C&gt;B are explicitly stored. It is clear that from {a mathematical formula}C2, {a mathematical formula}A&gt;B can be inferred, which is in contradiction with the credibility element {a mathematical formula}B&gt;A informed by J that is explicitly stored in {a mathematical formula}C. Next, we will introduce three functions: {a mathematical formula}ce(C), {a mathematical formula}cl(C), and {a mathematical formula}rel(C) that will be used in the formalism proposed below. The first function returns all the credibility elements of a credibility base, i.e., {a mathematical formula}ce(C)={P&gt;Q:[P&gt;Q,S]∈C}. Note that {a mathematical formula}ce(C) is a finite set that corresponds to the projection of {a mathematical formula}C with respect to those credibility elements that are explicitly represented in {a mathematical formula}C. Then, {a mathematical formula}cl(C) will include all credibility elements that can be inferred from {a mathematical formula}ce(C) by the transitive closure of {a mathematical formula}ce(C). Considering the credibility base from Example 2, {a mathematical formula}ce(C2)={A&gt;C,C&gt;B,B&gt;A,K&gt;J} and {a mathematical formula}cl(C2)={A&gt;C,C&gt;B,B&gt;A,A&gt;B,C&gt;A,B&gt;C,K&gt;J,A&gt;A,B&gt;B,C&gt;C}.
     </paragraph>
     <paragraph>
      In a credibility object {a mathematical formula}[A&gt;C,K], K is the source of {a mathematical formula}A&gt;C, and K represents the reliability of {a mathematical formula}A&gt;C. Given a credibility base {a mathematical formula}C, the function {a mathematical formula}rel(C) returns the set of agent identifiers that are sources of credibility elements in {a mathematical formula}C, i.e., {a mathematical formula}rel(C)={S:[P&gt;Q,S]∈C}. This function will be used to determine the set of agent identifiers that represents the reliability of an argument. As we will show below, an argument will be composed of a set of credibility objects, and to obtain its reliability the sources of those objects will be considered.
     </paragraph>
     <paragraph>
      Observe that given a credibility base {a mathematical formula}C, {a mathematical formula}cl(C) can have contradictory credibility elements, e.g., {a mathematical formula}A&gt;B and {a mathematical formula}B&gt;A both belong to {a mathematical formula}cl(C2). Also note that both elements were obtained from different sources and, for that reason, their reliability could be different. Therefore, in the following sections we will propose an argumentation formalism that given a credibility base it will find a non-contradictory subset of {a mathematical formula}cl(C) that has the information that is more reliable. We will also show below that this subset is a strict partial order of credibility elements.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Arguments and attacks
     </section-title>
     <paragraph>
      Each credibility element that can be inferred from a credibility base {a mathematical formula}C will have an argument associated that supports it, and such argument will contain the reliability information for that inference. This reliability information will be used for comparing arguments supporting contradictory conclusions. An argument is a minimal set of credibility objects as defined next.
     </paragraph>
     <paragraph label="Definition 2">
      ArgumentLet {a mathematical formula}C be a credibility base, {a mathematical formula}A be a set of agents, and {a mathematical formula}B,C∈A where {a mathematical formula}B≠C, an argument {a mathematical formula}X for the conclusion {a mathematical formula}B&gt;C from {a mathematical formula}C is a set of credibility objects {a mathematical formula}X⊆C, such that {a mathematical formula}B&gt;C∈cl(X) and there is no {a mathematical formula}X′⊂X holding that {a mathematical formula}B&gt;C∈cl(X′). The set of all arguments that can be built from {a mathematical formula}C will be denoted as {a mathematical formula}ArgsC. If {a mathematical formula}X is an argument for the conclusion {a mathematical formula}B&gt;C, sometimes we will use the notation {a mathematical formula}〈X,B&gt;C〉.
     </paragraph>
     <paragraph>
      Observe that it is not possible to have arguments for a conclusion such as {a mathematical formula}A&gt;A. This is concordant with the intuition that credibility is an irreflexive relation since agents cannot be more credible than themselves. An argument is a minimal set with respect to set inclusion and, therefore, an argument cannot have a cycle. Note that even though an argument {a mathematical formula}X can have one or more credibility objects, each argument has only one conclusion. Any proper subset of an argument is itself an argument for a different conclusion, and represents an intermediate reasoning step in the argument in which it is contained and, trivially, an argument is a subargument of itself. This notion is captured in the subargument relation defined next.
     </paragraph>
     <paragraph label="Definition 3">
      SubargumentLet {a mathematical formula}C be a credibility base and {a mathematical formula}X,Z∈ArgsC, then {a mathematical formula}Z is a subargument of {a mathematical formula}X if and only if {a mathematical formula}Z⊆X.
     </paragraph>
     <paragraph>
      The following proposition shows that the argument construction is monotonic. That is, the addition of credibility objects to a credibility base does not preclude the construction of an argument.
     </paragraph>
     <paragraph label="Proposition 1">
      Let{a mathematical formula}〈X,A&gt;B〉be an argument that can be built from the credibility base{a mathematical formula}Cand{a mathematical formula}C⊆C′then{a mathematical formula}〈X,A&gt;B〉can also be built from{a mathematical formula}C′.
     </paragraph>
     <paragraph label="Proof">
      Straightforward from Definition 2.  □
     </paragraph>
     <paragraph label="Example 3">
      Consider again the credibility base of our running example introduced in Example 2:{a mathematical formula} There are seven arguments that can be built from {a mathematical formula}C2. For the sake of clarity, in this example we will present three of them, nevertheless the remaining arguments will be presented when the full example is studied in greater depth in Section 4. For instance, from {a mathematical formula}C2 it is possible to build the argument {a mathematical formula}A2={[A&gt;C,K],[C&gt;B,H]} for the conclusion {a mathematical formula}A&gt;B, the argument {a mathematical formula}A1={[A&gt;C,K],[B&gt;A,J]} for the conclusion {a mathematical formula}B&gt;C, and {a mathematical formula}A3={[B&gt;A,J]} for the conclusion {a mathematical formula}B&gt;A. Note that {a mathematical formula}A3 is a subargument of {a mathematical formula}A1. On the other hand, there are several subsets of {a mathematical formula}C2 that are not arguments. For instance, the set {a mathematical formula}N={[A&gt;C,K],[C&gt;B,H],[B&gt;A,J]} is not an argument because for any potential conclusion in {a mathematical formula}cl(N) the set {a mathematical formula}N is not minimal. A similar situation occurs with the set {a mathematical formula}{[B&gt;A,J],[K&gt;J,X]} and with the set {a mathematical formula}{[A&gt;C,K],[K&gt;J,X]}.
     </paragraph>
     <paragraph>
      Fig. 1 depicts the three arguments introduced in Example 3. There, each argument is represented as a table of one column with its name and conclusion at the top, and below them, the set of credibility objects used for obtaining the conclusion. Given an argument {a mathematical formula}X, the set {a mathematical formula}rel(X) contains all the agent identifiers which are sources of the credibility objects in {a mathematical formula}X, and hence {a mathematical formula}rel(X) represents the reliability of {a mathematical formula}X. Considering the arguments from Example 3, we have {a mathematical formula}rel(A1)={K,J}, {a mathematical formula}rel(A2)={K,H}, and {a mathematical formula}rel(A3)={J}.
     </paragraph>
     <paragraph>
      Observe that in Example 3 the argument {a mathematical formula}A2 provides a reason to conclude that A is more credible than B, whereas {a mathematical formula}A3 concludes the contrary, i.e., B is more credible than A. We next introduce the definition of arguments with contradictory conclusions that will be used in our formalization below.
     </paragraph>
     <paragraph label="Definition 4">
      Contradictory conclusionsLet {a mathematical formula}X, {a mathematical formula}Z be two arguments in {a mathematical formula}ArgsC. If {a mathematical formula}X concludes {a mathematical formula}B&gt;C and {a mathematical formula}Z concludes {a mathematical formula}C&gt;B, for some {a mathematical formula}B,C∈A, then {a mathematical formula}X and {a mathematical formula}Z have contradictory conclusions.
     </paragraph>
     <paragraph>
      Clearly, arguments with contradictory conclusions are in conflict. As we will discuss in detail below, we will study three types of conflicts that will lead to three different attack relations. The first type, called trust-attacks, captures the type of conflicts related to contradictory conclusions. The second type of attacks, called reliability-attacks, captures how an argument can challenge the reliability of an argument that trust-attacks another. The third type, called indirect-reliability-attacks, captures the indirect conflict that is implicit between two reliability-attacks that challenge opposing positions.
     </paragraph>
     <paragraph>
      These three attack relations together will characterize an AFRA's recursive attack relation, and that framework will be used to determine the arguments that are finally accepted. For convenience, given a credibility base {a mathematical formula}C we will denote with {a mathematical formula}TAttsC the set of trust-attacks from {a mathematical formula}C, with {a mathematical formula}RAttsC the set of reliability-attacks from {a mathematical formula}C, and with {a mathematical formula}IAttsC the set of indirect-reliability-attacks from {a mathematical formula}C. Below we will explain the intuitions that motivate each type of attack and present their definitions.
     </paragraph>
     <section label="3.1">
      <section-title>
       Trust-attacks
      </section-title>
      <paragraph>
       A trust-attack captures the conflict between arguments that conclude contradictory credibilities. Intuitively, argument {a mathematical formula}Y trust-attacks another {a mathematical formula}X if either they have contradictory conclusions, or there is a subargument of {a mathematical formula}X having a contradictory conclusion with {a mathematical formula}Y; that is, either {a mathematical formula}Y contradicts the credibility concluded by {a mathematical formula}X or {a mathematical formula}Y contradicts an intermediate reasoning step of {a mathematical formula}X. Next, we formalize this notion.
      </paragraph>
      <paragraph label="Definition 5">
       Trust-attackLet {a mathematical formula}X,Y be two arguments in {a mathematical formula}ArgsC, we will say that {a mathematical formula}(Y,X)∈TAttsC if there exists a subargument {a mathematical formula}Z of {a mathematical formula}X such that {a mathematical formula}Y and {a mathematical formula}Z have contradictory conclusions. This subargument {a mathematical formula}Z is referred as the disagreement subargument of {a mathematical formula}(Y,X) and denoted {a mathematical formula}dis((Y,X))=Z.
      </paragraph>
      <paragraph>
       Recall that every argument is trivially a subargument of itself. Thus, an argument {a mathematical formula}A will be attacked by (and will also attack) any other argument {a mathematical formula}B such that {a mathematical formula}A and {a mathematical formula}B have contradictory conclusions. Therefore, intuitively an argument can trust-attack other argument at its conclusion or at an intermediate point (subargument). Fig. 2 shows the three arguments introduced in Example 3 and the trust-attacks between them; these attacks are depicted with solid arrows. Each arrow is labeled with a lowercase Greek letter, e.g., there exists a trust-attack {a mathematical formula}α=(A2,A3) because {a mathematical formula}A2 and {a mathematical formula}A3 have contradictory conclusions. An analogous situation holds for {a mathematical formula}β=(A3,A2). The trust-attack {a mathematical formula}λ=(A2,A1) occurs because {a mathematical formula}A1 has a subargument concluding {a mathematical formula}B&gt;A and {a mathematical formula}A2 concludes {a mathematical formula}A&gt;B. Finally, the trust-attack {a mathematical formula}π=(A1,A2) occurs because {a mathematical formula}A1 and a subargument of {a mathematical formula}A2 have contradictory conclusions.
      </paragraph>
      <paragraph>
       In the case shown in Fig. 2, where only three arguments are considered, a kind of blocking situation occurs because all the arguments are trust-attacked by another argument. Nevertheless, in the credibility base {a mathematical formula}C2 there is more information that can be used. In the next subsection, we will show how an attack can be attacked in order to decide which information prevails; but first, we will show some results that are related to the previous definitions and that characterize our framework.
      </paragraph>
      <paragraph>
       The following result shows that any argument built from a credibility base has internal coherence. That is, an argument should be consistent by itself, and thus it will not attack itself.
      </paragraph>
      <paragraph label="Proposition 2">
       There is no{a mathematical formula}X∈ArgsCsuch that{a mathematical formula}(X,X)∈TAttsC.
      </paragraph>
      <paragraph label="Proof">
       Suppose that {a mathematical formula}(X,X)∈TAttsC, then there is an argument {a mathematical formula}Z which is a subargument of {a mathematical formula}X such that {a mathematical formula}X and {a mathematical formula}Z have contradictory conclusions. That is, if {a mathematical formula}X concludes {a mathematical formula}B&gt;C then {a mathematical formula}Z concludes {a mathematical formula}C&gt;B. Then, by Definition 2 it holds that {a mathematical formula}{B&gt;C,C&gt;B}⊆cl(X). Therefore, there exists {a mathematical formula}X′⊂X such that {a mathematical formula}B&gt;C∈cl(X′), contradiction.  □
      </paragraph>
      <paragraph>
       The following proposition shows that trust-attacks happen in pairs. That is, if an argument trust-attacks another argument, the attacking argument will, in turn, also be trust-attacked.
      </paragraph>
      <paragraph label="Proposition 3">
       Let{a mathematical formula}X,Y∈ArgsC. If{a mathematical formula}(Y,X)∈TAttsCthen there is{a mathematical formula}Z∈ArgsCsuch that{a mathematical formula}(Z,Y)∈TAttsC.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}(Y,X)∈TAttsC then by Definition 5 there is a subargument {a mathematical formula}Z of {a mathematical formula}X such that {a mathematical formula}Y and {a mathematical formula}Z have contradictory conclusions. Then, given that any argument is trivially a subargument of itself, by Definition 5 it holds that {a mathematical formula}(Z,Y)∈TAttsC.  □
      </paragraph>
      <paragraph>
       The following corollary establishes the notion of symmetry of trust-attacks between arguments with contradictory conclusions.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}α=(Y,X)∈TAttsC. If{a mathematical formula}dis(α)=Xthen{a mathematical formula}(X,Y)∈TAttsC.Straightforward from Definition 5 and Proposition 3.  □
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Reliability-attacks
      </section-title>
      <paragraph>
       We introduce now the possibility of representing an attack to an attack called reliability-attack. Below we will explain how with this form of attack the reliability of the information can be used to decide which argument prevails when arguments for contradictory conclusions are obtained.
      </paragraph>
      <paragraph>
       Recall that given an argument {a mathematical formula}X the set {a mathematical formula}rel(X) represents the reliability of {a mathematical formula}X and contains all the agent identifiers that are sources of the credibility objects in {a mathematical formula}X. For instance, as shown for the arguments from Example 3, {a mathematical formula}rel(A1)={K,J}, {a mathematical formula}rel(A2)={K,H} and {a mathematical formula}rel(A3)={J}.
      </paragraph>
      <paragraph>
       Consider again the credibility base {a mathematical formula}C2 and Fig. 2 where trusts-attacks {a mathematical formula}α=(A2,A3) and {a mathematical formula}β=(A3,A2) are depicted. From {a mathematical formula}C2 the argument {a mathematical formula}A4={[K&gt;J,X]} concluding {a mathematical formula}K&gt;J can be built. Observe that the argument {a mathematical formula}A2 has K as one of the sources of its information ({a mathematical formula}K∈rel(A2)), and {a mathematical formula}A3 has J as the source of its information ({a mathematical formula}J∈rel(A3)). In this scenario, we can use the argument {a mathematical formula}A4 to establish a preference of {a mathematical formula}A2 over {a mathematical formula}A3, given that {a mathematical formula}A2 has sources that can be deemed as more credible than some of the sources in {a mathematical formula}A3. That is, {a mathematical formula}A4 establishes that {a mathematical formula}A2 is based on more reliable information than {a mathematical formula}A3. Following this line of reasoning, argument {a mathematical formula}A4 challenges the validity of the trust-attack β (see Fig. 3 where this challenge is depicted with a dashed line).
      </paragraph>
      <paragraph>
       This form of conflict will be captured by an attack to an attack that will be introduced below in Definition 6; but first, we will introduce two auxiliary notions: the origin of an attack α, denoted {a mathematical formula}og(α), and the target of an attack, denoted {a mathematical formula}tg(α). Given an attack {a mathematical formula}α=(A,T), the first element of the pair is the origin of the attack, i.e., {a mathematical formula}og(α) = {a mathematical formula}A, while the second element of the pair is the target of the attack, i.e., {a mathematical formula}tg(α)=T. Since in our framework there can be attacks to arguments and attacks to attacks, the target T could be either an argument or an attack.
      </paragraph>
      <paragraph>
       Reliability-attacks, as we have discussed above, capture the preference of some arguments considering how reliable they are in light of their sources. This notion will formalize the intuition of challenging attacks.
      </paragraph>
      <paragraph>
       Next, we will formally introduce the basic form of reliability-attacks, that will challenge trust-attacks in {a mathematical formula}TAttsC (as was exemplified above). Once we have introduced the indirect-reliability-attacks, we will present the recursive version of reliability-attacks capable of targeting such form of attack.
      </paragraph>
      <paragraph label="Definition 6">
       Basic reliability-attackLet {a mathematical formula}X be an argument in {a mathematical formula}ArgsC concluding {a mathematical formula}C&gt;B and {a mathematical formula}β∈TAttsC such that no agent in the conclusion of {a mathematical formula}og(β) appears in {a mathematical formula}rel(X). We say that {a mathematical formula}(X,β)∈RAttsC if and only if {a mathematical formula}B∈rel(og(β)) and {a mathematical formula}C∈rel(dis(β)).
      </paragraph>
      <paragraph label="Example 4">
       Consider the credibility base of our running example:{a mathematical formula} In Example 3, we have shown how from {a mathematical formula}C2 it is possible to build the arguments {a mathematical formula}A2,A3, and {a mathematical formula}A1, and Fig. 2 depicts a situation where the trust-attacks α, β, γ, and π appear. Note that the argument {a mathematical formula}A4={[K&gt;J,X]} can also be built from {a mathematical formula}C2. Fig. 3 shows that {a mathematical formula}A4 effects a reliability-attack to β, denoted {a mathematical formula}γ=(A4,β), since we have that {a mathematical formula}og(β)=A3, neither A nor B are in {a mathematical formula}rel(A4)={X}, {a mathematical formula}J∈rel(A3), the disagreement subargument of β is {a mathematical formula}dis(β)=A2, {a mathematical formula}K∈rel(A2), and {a mathematical formula}K&gt;J is the conclusion of {a mathematical formula}A4.
      </paragraph>
      <paragraph>
       For convenience, a reliability-attack will be depicted using dashed arrows (e.g., γ in Fig. 3), and if we consider only the arguments that can be obtained from {a mathematical formula}C2, there is no other reliability-attack. In particular, it is worth to mention that {a mathematical formula}A4 does not produce a reliability-attack to π. To understand why, observe that {a mathematical formula}J∈rel(og(π)) but the disagreement subargument for π is {a mathematical formula}dis(π)={[C&gt;B,H]} and {a mathematical formula}K∉rel(dis(π)).
      </paragraph>
      <paragraph>
       Another important remark concerning Definition 6 is that it forbids circular defenses using reliability-attacks. Observe that the argument producing a reliability-attack, should not contain as part of its reliability (i.e., its sources) any of those agents involved in the trust conflict which it aims to settle. In other words, an argument will not be able to challenge the reliability of a trust-attack if some of its sources are the ones that cause such trust-attack.
      </paragraph>
      <paragraph>
       Although in Fig. 3 the reliability-attack γ breaks the blocking situation between arguments {a mathematical formula}A2 and {a mathematical formula}A3, there are more arguments and attacks in this scenario and more elements need to be considered to decide which arguments prevail. The complete analysis of the situation will be shown in Section 4.
      </paragraph>
      <paragraph>
       The following proposition shows that if an argument challenges a trust-attack which models the conflict between two arguments, it will also challenge every other trust-attack that involves any superargument of such arguments.
      </paragraph>
      <paragraph label="Proposition 4">
       Let{a mathematical formula}Cbe a credibility base,{a mathematical formula}α=(W,V)∈TAttsCand{a mathematical formula}(X,α)∈RAttsC. For every trust-attack{a mathematical formula}β=(W,Y)∈TAttsCwhere the argument{a mathematical formula}Vis a subargument of{a mathematical formula}Yit holds that{a mathematical formula}(X,β)∈RAttsC.
      </paragraph>
      <paragraph label="Proof">
       Since {a mathematical formula}γ=(X,α)∈RAttsC, by Definition 6 it holds that if {a mathematical formula}X concludes {a mathematical formula}A&gt;B then {a mathematical formula}B∈rel(og(α)) and {a mathematical formula}A∈rel(dis(α)). Also, by Definition 5 it holds {a mathematical formula}dis(α)=dis(β), then {a mathematical formula}A∈rel(dis(β)). Therefore, by Definition 6 it holds that {a mathematical formula}(X,β)∈RAttsC.  □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Indirect-reliability-attacks
      </section-title>
      <paragraph>
       To motivate this new form of attack, we will extend our running example with more information objects that will introduce more arguments (see Example 5).
      </paragraph>
      <paragraph label="Example 5">
       Consider the credibility base{a mathematical formula} which is in fact {a mathematical formula}C2{a mathematical formula}∪{[J&gt;H,Y]}. The new credibility object represents that the newsletter Y-invest (abbreviated Y) has informed that agent J is more credible than H. Note that from {a mathematical formula}C5 we have the same arguments and attacks shown in Example 4 and, in addition, the argument {a mathematical formula}A5={[J&gt;H,Y]} can be built. This argument produces a reliability-attack {a mathematical formula}δ=(A5,α) because {a mathematical formula}og(α)=A2, {a mathematical formula}H∈rel(A2), the disagreement subargument of α is {a mathematical formula}dis(α)=A3, {a mathematical formula}J∈rel(A3), and {a mathematical formula}A5 has {a mathematical formula}J&gt;H as conclusion. Furthermore, note that {a mathematical formula}A5 also produces a reliability-attack θ to λ, since {a mathematical formula}H∈rel(og(λ)) and {a mathematical formula}J∈rel(dis(λ)). The situation is shown in Fig. 4.
      </paragraph>
      <paragraph>
       Indirect-reliability-attacks will be used to capture an implicit situation of conflict that can occur between two reliability-attacks. Observe in Fig. 4 that the reliability-attack γ challenges the trust-attack β and, simultaneously, the reliability-attack δ challenges the trust-attack α. Therefore, considering δ and γ it could be seen that γ is representing a preference of {a mathematical formula}A2 over {a mathematical formula}A3, meanwhile δ represents the contrary, and thus this means an implicit conflict between reliability-attacks such as δ and γ exists. Also note that, if we suppose that the reliability-attacks δ and γ are successful, then α and β will be ineffective. This leads to an undesirable situation where arguments with contradictory conclusions, such as {a mathematical formula}A2 and {a mathematical formula}A3, could hold together.
      </paragraph>
      <paragraph>
       To capture a conflict as the one between δ and γ discussed above, we will introduce indirect-reliability-attacks which originate from an argument and target a reliability-attack. The argument producing the indirect-reliability-attack will be the same that produces the reliability-attack which is in conflict with the reliability-attack that is the target of the indirect-reliability-attack. As we did for the basic reliability-attack, we will present the basic indirect-reliability-attacks that target basic reliability-attacks next.
      </paragraph>
      <paragraph label="Definition 7">
       Basic indirect-reliability-attackLet {a mathematical formula}α,β∈RAttsC where {a mathematical formula}og(α) = {a mathematical formula}X and {a mathematical formula}tg(α),tg(β)∈TAttsC. We say that {a mathematical formula}(X,β)∈IAttsC if and only if either {a mathematical formula}og(tg(α))=dis(tg(β)) or {a mathematical formula}og(tg(α))=tg(tg(β))
      </paragraph>
      <paragraph label="Example 6">
       Consider the credibility base {a mathematical formula}C5 from Example 5. In this scenario, given that γ is a reliability-attack and {a mathematical formula}og(γ)=A4, we have that {a mathematical formula}A4 produces the indirect-reliability-attack ϕ to δ. This is so because {a mathematical formula}tg(γ)=β, {a mathematical formula}og(β)=A3 and because {a mathematical formula}tg(δ)=α∈TAttsC5, {a mathematical formula}tg(α)=A3. An analogous situation holds for the indirect-reliability-attack ε: {a mathematical formula}tg(δ)=α, {a mathematical formula}og(α)=A2 and because {a mathematical formula}tg(γ)=β∈TAttsC5, {a mathematical formula}tg(β)=A2. These indirect-reliability-attacks, together with previously described items, are depicted using dotted arrows in Fig. 5. In addition, note that there is no indirect-attack to θ.
      </paragraph>
      <paragraph>
       As we have stated above Definition 6, reliability-attacks can also challenge indirect-reliability-attacks, and the intuition is similar to how these attacks challenged trust-attacks: a reliability-attack poses a preference over the arguments involved in a conflict. Following this line of reasoning, indirect-reliability-attacks should be capable of targeting these reliability-attacks, and in turn such indirect-reliability-attacks can also be challenged by reliability-attacks. Clearly, this naturally leads to a mutually recursive definition where both types of attacks can attack each other.
      </paragraph>
      <paragraph label="Definition 8">
       Reliability-attack/Indirect-reliability-attackLet {a mathematical formula}X be an argument in {a mathematical formula}ArgsC with conclusion {a mathematical formula}C&gt;B. It will hold that:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}(X,β)∈RAttsC iff {a mathematical formula}β∈IAttsC is such that no agent in the conclusion of {a mathematical formula}og(β) is in {a mathematical formula}rel(X), {a mathematical formula}B∈rel(og(β)), and {a mathematical formula}C∈rel(og(tg(β))).
       </list-item>
       <list-item label="•">
        {a mathematical formula}(X,β)∈IAttsC iff {a mathematical formula}β∈RAttsC and there is {a mathematical formula}α∈RAttsC such that {a mathematical formula}og(α)=X and {a mathematical formula}og(tg(α))=og(tg(tg(β))).
       </list-item>
      </list>
      <paragraph>
       We extend in Example 7 our running example to show a scenario where there exists a reliability-attack targeting an indirect-reliability-attack (which corresponds to the second condition from Definition 8).
      </paragraph>
      <paragraph label="Example 7">
       Consider the credibility base{a mathematical formula} that corresponds to {a mathematical formula}C5{a mathematical formula}∪{[Y&gt;X,T]}. Here, the new credibility object is expressing that for the agent Tory the newsletter Y-invest is more credible than X-market. Note that from {a mathematical formula}C7 we have the same arguments and attacks shown in Example 6 and, in addition, the argument {a mathematical formula}A6={[Y&gt;X,T]} can be built. The argument {a mathematical formula}A6 provides information to prefer the indirect-reliability-attack ε over the indirect-reliability-attack ϕ; this is so because {a mathematical formula}A6 establishes that {a mathematical formula}A5 (which is the argument producing ε) is based on more reliable sources than {a mathematical formula}A4 (which is the argument that produces ϕ). This preference is captured by a reliability-attack from {a mathematical formula}A6 to the indirect-reliability-attack ϕ, as we depict in Fig. 6; this intuitions are formalized in Definition 6. In this particular case, we have that {a mathematical formula}μ=(A6,ϕ) is a reliability-attack because {a mathematical formula}og(ϕ)=A4, {a mathematical formula}X∈rel(A4), and {a mathematical formula}tg(ϕ)=δ, {a mathematical formula}og(δ)=A5 and {a mathematical formula}Y∈rel(A5).
      </paragraph>
      <paragraph>
       Next, we will present another example to show indirect-reliability-attacks that target reliability-attacks, which in turn target indirect-reliability-attacks.
      </paragraph>
      <paragraph label="Example 8">
       Consider the following credibility base:{a mathematical formula}Fig. 7 shows the arguments and attacks that can be built from {a mathematical formula}C8. There are six trust-attacks between these arguments: {a mathematical formula}κ1,κ2 capture the conflict between {a mathematical formula}A20 and {a mathematical formula}A21, {a mathematical formula}κ3,κ4 the conflict between {a mathematical formula}A22 and {a mathematical formula}A23, and {a mathematical formula}κ5,κ6 the conflict between {a mathematical formula}A24 and {a mathematical formula}A25. There are four basic reliability-attacks: {a mathematical formula}ω1, {a mathematical formula}ω2, {a mathematical formula}ω3 and {a mathematical formula}ω4; and there are four basic indirect-reliability-attacks: {a mathematical formula}η1, {a mathematical formula}η2, {a mathematical formula}η3 and {a mathematical formula}η4. Note that there are two non basic reliability-attacks: {a mathematical formula}ω5 and {a mathematical formula}ω6, and two non basic indirect-reliability-attacks: {a mathematical formula}η5 and {a mathematical formula}η6. In particular, observe that {a mathematical formula}η5=(A25,ω6) occurs because there is {a mathematical formula}ω5 such that {a mathematical formula}og(ω5)=A25, and it also holds that {a mathematical formula}tg(ω5)=η1, {a mathematical formula}og(η1)=A22 and {a mathematical formula}tg(ω6)=η2, {a mathematical formula}tg(η1)=ω1, {a mathematical formula}og(ω1)=A22. An analogous situation occurs for {a mathematical formula}η6.
      </paragraph>
      <paragraph>
       In the following section, we will introduce an argumentation formalism for analyzing which arguments and attacks prevail.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Obtaining the credibility relation through argumentation
     </section-title>
     <paragraph>
      As described above, arguments can attack each other, but they can challenge attacks as well. It is clear that conflicting elements cannot be accepted together and their status need to be evaluated, and in such evaluation it is necessary to consider their acceptability status. Intuitively, an argument should be accepted if it is able to survive the attacks it receives, and should be rejected otherwise [30]. Since in our formalization attacks can also receive attacks, the evaluation process should also be capable of deciding whether an attack can be regarded as effective or not. In our proposal, the goal of the evaluation process is that after everything is considered, the accepted arguments will provide the credibility elements that will be justified from the credibility base.
     </paragraph>
     <paragraph>
      In this work, we will use the evaluation approach of argumentation semantics in abstract argumentation frameworks [14]. Such semantics are abstracted from argument internal structures and are focused on establishing which arguments can be regarded as accepted considering just the attacks. In particular, given the recursive nature of the attacks in our system, we will use an AFRA introduced in [3], [4], which extends the classical approach of [14] by allowing attacks to the attack relation.
     </paragraph>
     <paragraph>
      An AFRA is expressed as a set of arguments and a set of attacks, where an attack is a pair {a mathematical formula}(A,T) such that {a mathematical formula}A is an argument and {a mathematical formula}T is either an argument or an attack [4]. To instantiate an AFRA, we will use arguments and attacks obtained from a credibility base, and then we will analyze which elements are accepted from this framework. Thus, each credibility base will characterize a particular AFRA which will be called its associated AFRA.
     </paragraph>
     <paragraph label="Definition 9">
      Associated AFRALet {a mathematical formula}C be a credibility base, the associated AFRA of {a mathematical formula}C is {a mathematical formula}(ArgsC,AttsC) where {a mathematical formula}ArgsC is the set of arguments that can be built from {a mathematical formula}C, and {a mathematical formula}AttsC=TAttsC∪RAttsC∪IAttsC with {a mathematical formula}TAttsC its set of trust-attacks, {a mathematical formula}RAttsC its set of reliability-attacks and {a mathematical formula}IAttsC its set of indirect-reliability-attacks.
     </paragraph>
     <paragraph>
      It is important to remark that the sets of attacks are pairwise disjoint by their own nature, i.e., every attack belongs to only one form of attack.
     </paragraph>
     <paragraph label="Example 9">
      Consider for instance the credibility base {a mathematical formula}C7 from Example 7. The associated AFRA {a mathematical formula}(ArgsC7,AttsC7) of that credibility base is depicted in Fig. 8. Observe that {a mathematical formula}ArgsC7 has ten arguments: six of them were shown in previous examples, and there are other four arguments: {a mathematical formula}A7, {a mathematical formula}A8, {a mathematical formula}A9, and {a mathematical formula}A10 (see Fig. 8). Note that {a mathematical formula}A3 is a subargument of {a mathematical formula}A1 and {a mathematical formula}A7; {a mathematical formula}A9 is a subargument of {a mathematical formula}A2 and {a mathematical formula}A7; {a mathematical formula}A8 is a subargument of {a mathematical formula}A1 and {a mathematical formula}A2. There are twelve trust-attacks in {a mathematical formula}TAttsC7, fifteen reliability-attacks in {a mathematical formula}RAttsC7 and six indirect-reliability-attacks in {a mathematical formula}IAttsC7.
     </paragraph>
     <paragraph>
      Following [4], the first step towards determining the accepted arguments from an associated AFRA {a mathematical formula}(ArgsC,AttsC) is to establish the existing attacks and consequent defeats. A defeat to an argument or an attack in an AFRA is determined by analyzing a recursive attack relation [4]. In addition, argument defeats are also propagated to the attacks they originate. In what follows, we will slightly adapt the formalization of defeats in an AFRA to use them in an associated AFRA of a credibility base. In the definitions below we will use the functions {a mathematical formula}og(⋅) and {a mathematical formula}tg(⋅) that were introduced in Section 3.2. The reader should note that these two notions correspond to src and trg defined in [3], [4] which we renamed to og and tg in order to avoid confusion with our notion of source of a credibility element.
     </paragraph>
     <paragraph label="Definition 10">
      Defeat in associated AFRALet {a mathematical formula}〈ArgsC,AttsC〉 be the associated AFRA of a credibility base {a mathematical formula}C, {a mathematical formula}α,β∈AttsC and {a mathematical formula}X∈ArgsC∪AttsC:
     </paragraph>
     <list>
      <list-item label="•">
       αdirectly defeats{a mathematical formula}X iff {a mathematical formula}tg(α)=X.
      </list-item>
      <list-item label="•">
       αindirectly defeatsβ iff {a mathematical formula}tg(α)=X, and {a mathematical formula}X=og(β).
      </list-item>
     </list>
     <paragraph label="Example 10">
      In the associated AFRA {a mathematical formula}(ArgsC7,AttsC7) depicted in Fig. 8, for instance, we have that α directly defeats {a mathematical formula}A3, α indirectly defeats β, β directly defeats {a mathematical formula}A2, β indirectly defeats α, δ directly defeats α, γ directly defeats β, ϕ directly defeats δ, and μ directly defeats ϕ.
     </paragraph>
     <paragraph>
      Note that attacks are the only elements of the framework capable of defeating arguments and other attacks. This is also coherent with the fact that an attack can be rendered ineffective by either attacking the attack itself or the argument where originates.
     </paragraph>
     <paragraph>
      In abstract argumentation, the formal definitions of declarative methods ruling the argument evaluation process are called argumentation semantics. In an AFRA, a semantics definition specifies how to obtain a set of extensions. An extension E of an AFRA is simply a subset of arguments and attacks that represents a set of elements which can survive together or are collectively acceptable[4].
     </paragraph>
     <paragraph>
      We will introduce the basic elements from which the different semantics are defined [5]. The notion of conflict-free set captures the idea that an extension is a set of elements that “can stand together”; in other words, the attacks in the set do not defeat elements of the set. The notion of acceptability establishes that an argument or an attack {a mathematical formula}X is acceptable with respect to (or defended by) a set of elements if this set defeats every attack defeating {a mathematical formula}X. Finally, the notion of admissibility captures the intuition that an extension is a set of elements that “can stand on its own”, i.e., it is a conflict-free set and it defends all its elements.
     </paragraph>
     <paragraph label="Definition 11">
      Conflict-freeness, acceptability, admissibilityLet {a mathematical formula}〈ArgsC,AttsC〉 be the associated AFRA of a credibility base {a mathematical formula}C, {a mathematical formula}S⊆ArgsC∪AttsC, and {a mathematical formula}X∈ArgsC∪AttsC. Then:
     </paragraph>
     <list>
      <list-item label="•">
       S is conflict-free iff there is no {a mathematical formula}α,Y∈S{a mathematical formula}s.t.{a mathematical formula}α∈AttsC and α defeats {a mathematical formula}Y.
      </list-item>
      <list-item label="•">
       {a mathematical formula}X is acceptable w.r.t. S iff for all {a mathematical formula}α∈AttsC such that α defeats {a mathematical formula}X, there exists {a mathematical formula}β∈S such that β defeats α.
      </list-item>
      <list-item label="•">
       S is an admissible set iff S is conflict-free and each element in S is acceptable w.r.t. S.
      </list-item>
     </list>
     <paragraph>
      It is worth mentioning that the concepts presented by Definition 11 have a remarkable difference with those used in classical abstract argumentation frameworks. In such frameworks, these concepts are only defined in terms arguments [14]; instead, as we are in the context of the AFRA, here, these notions are defined in terms of arguments and attacks. This is because in an AFRA not only arguments can be defeated, but also attacks (for a more detailed discussion see [4]).
     </paragraph>
     <paragraph label="Example 11">
      In the associated AFRA {a mathematical formula}(ArgsC7,AttsC7) of {a mathematical formula}C7 depicted in Fig. 8, we have that the set {a mathematical formula}{A2,A3,β} is not conflict free because β defeats {a mathematical formula}A2, and the set {a mathematical formula}{A3,β,γ} is not conflict free since γ defeats β. Also note that {a mathematical formula}A3 is not acceptable with respect to {a mathematical formula}{A5,A1} since this set has no element that defeats α. However, {a mathematical formula}A3 is acceptable with respect to {a mathematical formula}{A5,A1,π} given that π indirectly defeats α. Finally, observe that the set {a mathematical formula}{A5,A3,δ} is not admissible since δ is not acceptable with respect to the set (it is not defended form ϕ), whereas {a mathematical formula}{A5,A3,μ,δ} and {a mathematical formula}{A1,ρ1,θ,ρ5} are admissible.
     </paragraph>
     <paragraph>
      If we look further into the admissible set {a mathematical formula}{A1,ρ1,θ,ρ5} from Example 11, it can be noted that adding elements such as {a mathematical formula}A5 or μ to that set will also result into an admissible set. We can keep adding elements and at some point we will reach a maximal admissible set such that adding any other element will result into a non-admissible set. Such maximal admissible sets will hold together all the elements of the framework that can stand by their own, and thus should be regarded as accepted. This idea of maximizing accepted elements is expressed by the preferred semantics. Next, the formalization of these intuitions based in [3], [4] are presented.
     </paragraph>
     <paragraph label="Definition 12">
      Preferred ExtensionLet {a mathematical formula}〈ArgsC,AttsC〉 be the associated AFRA of a credibility base {a mathematical formula}C and {a mathematical formula}S⊆ArgsC∪AttsC. The set S is a preferred extension of {a mathematical formula}〈ArgsC,AttsC〉 iff it is a maximal (w.r.t. ⊆) admissible set.
     </paragraph>
     <paragraph label="Example 12">
      Consider the credibility base {a mathematical formula}C7 and its associated AFRA as depicted in Fig. 8. This credibility base has only one preferred extension {a mathematical formula}EC7={A6,A5,A3,A1,A4,A8,A10,μ,ρ11,ρ12,ρ1,θ,δ,ρ3,ψ1,ψ2,ϵ,τ1,π,τ4,β,ρ10,ρ9,ρ7,τ9,ρ5,ρ6}.
     </paragraph>
     <paragraph>
      There are several argumentation semantics defined for AFRAs [3], [4]; nevertheless, since we do not aim to contrast the results of every conceivable semantics applied to our approach, in this work we will only consider the preferred semantics. This semantics provides a sensible approach to show how the argumentation machinery can be used for dealing with the different conflicts that we have described in the previous sections and for deciding which elements prevail. In Example 12 we have shown that in same cases one single preferred extension holds; however, as shown in Example 13, when there are mutual attacks between unchallenged arguments several extensions hold (one for each mutually exclusive option).
     </paragraph>
     <paragraph label="Example 13">
      Consider the credibility base {a mathematical formula}C8 introduced in Example 8. The associated AFRA of this base is characterized by the arguments and attacks that were depicted in Fig. 7. From such associated AFRA there are two preferred extensions: {a mathematical formula}EC81={A20,A23,A25,κ1,κ4,κ6,ω2,ω4,ω5,η2,η3,η5} and {a mathematical formula}EC82={A21,A22,A24,κ2,κ3,κ5,ω1,ω3,ω6,η1,η4,η6}.
     </paragraph>
     <paragraph>
      As it was mentioned, the justification state of a credibility element (e.g., {a mathematical formula}A&gt;B) in a base {a mathematical formula}C will depend on the status of the argument that supports that credibility element in the associated AFRA {a mathematical formula}〈ArgsC,AttsC〉; in turn, this status depends on the membership to an extension of such an argument. Note that, given a credibility base {a mathematical formula}C, there always exists an associated AFRA from which it is possible to obtain the extensions containing the acceptable arguments; hence, we will introduce to our framework the notion of extension of a credibility base that considers preferred extensions which satisfy a particular constraint. There can be AFRA extensions that are not extensions for a credibility base.
     </paragraph>
     <paragraph label="Definition 13">
      Extension of a credibility baseLet {a mathematical formula}C be a credibility base and E a preferred extension of its associated AFRA {a mathematical formula}〈ArgsC,AttsC〉. We will say that E is an extension of a credibility base {a mathematical formula}C iff for any argument {a mathematical formula}X∈ArgsC if every subargument {a mathematical formula}Z⊂X is in E then {a mathematical formula}X is in E.
     </paragraph>
     <paragraph label="Definition 14">
      Justified credibilitiesLet {a mathematical formula}C be a credibility base and E an extension of {a mathematical formula}C, then the set of justified credibilities of E is {a mathematical formula}JE={A&gt;B:〈X,A&gt;B〉∈E}.
     </paragraph>
     <paragraph>
      For instance, the credibility base {a mathematical formula}C7 has only one extension that is the only preferred extension {a mathematical formula}EC7 of its associated AFRA {a mathematical formula}〈ArgsC7,AttsC7〉, which was shown in Example 12. Then, the justified credibilities of {a mathematical formula}C7 are {a mathematical formula}JEC7={X&gt;Y,J&gt;H,B&gt;A,B&gt;C,K&gt;J,A&gt;C,K&gt;H}. Note that in this case the credibility information in {a mathematical formula}C7 is enough for deciding in every conflictive situation. In contrast, consider now the credibility base {a mathematical formula}Cm introduced in Example 13; in that example, we have shown that its associated AFRA has two preferred extensions {a mathematical formula}ECm1 and {a mathematical formula}ECm2. Observe that both are extensions of {a mathematical formula}Cm, therefore there are two possible sets of justified credibilities, {a mathematical formula}JECm1={L&gt;M,R&gt;S} and {a mathematical formula}JECm2={M&gt;L,S&gt;R}. Having more than one justified credibility set means that the credibility information in the base is not enough for deciding in every conflictive situation. In this work, we do not propose any particular mechanism to chose among multiple extensions. Nevertheless, a skeptical approach could involve to consider the intersection of all the extensions, i.e., only those arguments that appear in every extension (see [15] for more details on the implication of such approach).
     </paragraph>
     <paragraph>
      Next, with the following example we show that not every extension of the associated AFRA of a credibility base is an extension of that credibility base.
     </paragraph>
     <paragraph label="Example 14">
      Consider a credibility base {a mathematical formula}Cs={[O&gt;P,X],[P&gt;Q,Y],[Q&gt;O,Z]}. From this credibility base we can build six arguments: {a mathematical formula}A31 for {a mathematical formula}O&gt;P, {a mathematical formula}A32 for {a mathematical formula}P&gt;Q, {a mathematical formula}A33 for {a mathematical formula}Q&gt;O, {a mathematical formula}A34 for {a mathematical formula}O&gt;Q, {a mathematical formula}A35 for {a mathematical formula}P&gt;O and {a mathematical formula}A36 for {a mathematical formula}Q&gt;P. In Fig. 9 we depict the associated AFRA of {a mathematical formula}Cs. The preferred extension from such AFRA are {a mathematical formula}ECs1={A31,A34,A32,α4,α13,α10,α5,α2}, {a mathematical formula}ECs2={A31,A36,A33,α4,α7,α9,α6,α1}, {a mathematical formula}ECs3={A35,A33,A32,α3,α12,α8,α6,α2}, {a mathematical formula}ECs4={A31,A33,A32,α4,α6,α2}. Observe that {a mathematical formula}ECs1, {a mathematical formula}ECs2 and {a mathematical formula}ECs3 are also extensions of {a mathematical formula}Cs, whereas {a mathematical formula}ECs4 is not. This is because {a mathematical formula}ECs4, for instance, includes {a mathematical formula}A31 and {a mathematical formula}A32 but it does not include the superargument {a mathematical formula}A34. In addition, note that if {a mathematical formula}ECs4 was considered an extension of {a mathematical formula}Cs, the set of justified credibilities for such extension would had been {a mathematical formula}{O&gt;P,P&gt;Q,Q&gt;O} which clearly is not coherent with what we expect from a set of justified credibilities.
     </paragraph>
     <paragraph>
      It is worth mentioning that using the AFRA as the basis for the acceptance calculus allows us to apply any existing algorithm for preferred extension enumeration for Dung's classical abstract argumentation frameworks. Even though it is known that preferred extension enumeration is a costly process, the argumentation community has recently developed several methods that show promising empirical results, as it can be seen in the International Competition on Computational Models of Argumentation [40]. To use such methods, it is possible to translate an AFRA into a classical argumentation framework, as proposed in [4]. This transformation can be polynomially computed and there is a bijection between the preferred extensions of the resulting framework and those of the original AFRA.
     </paragraph>
     <paragraph>
      Once the preferred extensions are calculated, we can easily discard those AFRA's extensions that are not extensions of the credibility base and then pick the conclusion of every argument in each of the remaining extensions to build the sets of justified credibilities. Both tasks can be polynomially computed. The former requires just to check for every pair of arguments in the extension if the super-argument that can be built by combining them is also in the extension. The latter can be trivially computed by iterating among the arguments in the extension.
     </paragraph>
     <paragraph>
      Next, we include results that characterize our framework. The following proposition shows that an extension of a credibility base is coherent with respect to the argument composition. That is, if an argument is accepted then every part of it will be accepted as well.
     </paragraph>
     <paragraph label="Proposition 5">
      Let{a mathematical formula}Cbe a credibility base and E an extension of{a mathematical formula}C. It holds that if an argument{a mathematical formula}Xis in E then every subargument{a mathematical formula}Zof{a mathematical formula}Xbelongs to E.
     </paragraph>
     <paragraph label="Proof">
      Assume that {a mathematical formula}X is in a extension E of {a mathematical formula}C and suppose that there is a subargument {a mathematical formula}Z of {a mathematical formula}X such that {a mathematical formula}Z∉E; note that {a mathematical formula}{Z}∪E is conflict free. Then, by Definition 12, it holds that {a mathematical formula}Z is not acceptable w.r.t. E. Therefore, since {a mathematical formula}Z∉E there must exist α defeating {a mathematical formula}Z and there is no {a mathematical formula}β∈E such that β defeats α. Also, by Definition 5, Definition 6, Definition 7, Definition 8, Definition 9, arguments are only attacked by trust-attacks, thus {a mathematical formula}α∈TAttsC. Since {a mathematical formula}Z is a subargument of {a mathematical formula}X, by Definition 5 there is {a mathematical formula}γ∈TAttsC such that {a mathematical formula}tg(γ)=X, {a mathematical formula}dis(γ)=dis(α) and {a mathematical formula}og(γ)=og(α). By Proposition 4 and Definition 6, we know that if there is no defeater in E for α then there is no defeater in E for γ. Hence, {a mathematical formula}X∉E in contradiction with the original assumption.  □
     </paragraph>
     <paragraph>
      As we have shown, reliability-attacks can defeat trust-attacks, turning the latter ineffective. Given that trust-attacks model the conflicts between arguments with contradictory conclusions, it is important to show that even in the presence of reliability-attacks, in our formalism no extension will contain such arguments together. This is formalized in the following Lemma.
     </paragraph>
     <paragraph label="Lemma 1">
      Let{a mathematical formula}Cbe a credibility base and E an extension of{a mathematical formula}C, then there is no pair of arguments{a mathematical formula}Xand{a mathematical formula}Yin E, such that{a mathematical formula}Xand{a mathematical formula}Yhave contradictory conclusions.
     </paragraph>
     <paragraph label="Proof">
      Suppose that there are {a mathematical formula}X, {a mathematical formula}Y in E such that {a mathematical formula}X and {a mathematical formula}Y have contradictory conclusions. By Definition 5 and Corollary 1 it holds that there are {a mathematical formula}ϕ=(X,Y) and {a mathematical formula}ψ=(Y,X), such that {a mathematical formula}ϕ,ψ∈TAttsC. By Definition 12, we have that E is conflict free, then {a mathematical formula}ϕ,ψ∉E. Given that by Definition 12{a mathematical formula}X and {a mathematical formula}Y are acceptable with respect to E, there are {a mathematical formula}α,β∈E such that α defeats ϕ and β defeats ψ. By Definition 5, Definition 6, Definition 7 we have that {a mathematical formula}α,β∈RAttsC. Then, by Definition 7 there are {a mathematical formula}γ,δ∈IAttsC such that γ defeats α and δ defeats β. Thus, by Definition 12 there should be {a mathematical formula}ϵ,ω∈E such that ϵ defeats δ and ω defeats γ. In particular, those defeats should be direct defeats; otherwise, ϵ would also defeat α and ω would also defeat β. Then, by Definition 8, it holds that {a mathematical formula}ϵ,ω∈E. Then, given that for ϵ and ω are in E we have an analogous case to that of α and β. This leads us to an infinite amount of attacks, which is a contradiction.  □
     </paragraph>
     <paragraph>
      As we mentioned in the introduction of this article, one of the main goals of our system was to determine from a potentially conflicting credibility base a strict partial order representing the credibilities that can be coherently justified. As reported in [36], a set of justified credibilities from a credibility base is sound if it is a strict partial order. The following theorem shows that our approach is sound, i.e., every set of justified credibilities obtained from a credibility base is sound.
     </paragraph>
     <paragraph label="Theorem 1">
      Let{a mathematical formula}Cbe a credibility base with{a mathematical formula}JEthe set of justified credibilities of an extension E of{a mathematical formula}C. It holds that{a mathematical formula}JEis a strict-partial order.
     </paragraph>
     <paragraph label="Proof">
      We have to prove that the relation expressed by the set {a mathematical formula}JE is irreflexive, asymmetric, and transitive.
     </paragraph>
     <list>
      <list-item label="•">
       Irreflexive: Suppose that {a mathematical formula}JE is not irreflexive, then there is an A such that {a mathematical formula}A&gt;A∈JE. Thus, there must exist an argument {a mathematical formula}X such that its conclusion is {a mathematical formula}A&gt;A, which is not possible.
      </list-item>
      <list-item label="•">
       Asymmetric: Straightforward from Lemma 1 and Definition 14.
      </list-item>
      <list-item label="•">
       Transitive: If {a mathematical formula}A&gt;B and {a mathematical formula}B&gt;C are in {a mathematical formula}JE then we have two arguments {a mathematical formula}X and {a mathematical formula}Y in E concluding {a mathematical formula}A&gt;B and {a mathematical formula}B&gt;C respectively. By Definition 2, it holds that there is an argument {a mathematical formula}Z=X∪Y concluding {a mathematical formula}A&gt;C. Then {a mathematical formula}X and {a mathematical formula}Y are subarguments of {a mathematical formula}Z and, by Definition 13 it holds that {a mathematical formula}Z∈E. Therefore, {a mathematical formula}A&gt;C∈JE. □
      </list-item>
     </list>
     <paragraph>
      Finally, in Proposition 6 we show that when there are no conflicts in the credibility base every element in that base will be a justified credibility under any semantics. Then, in Proposition 7 we show that in a conflicting credibility base there are elements in the base that will not be justified under any semantics.
     </paragraph>
     <paragraph label="Proposition 6">
      Let{a mathematical formula}Cbe a credibility base with{a mathematical formula}JEas the set of justified credibilities of an extension E of{a mathematical formula}C. If{a mathematical formula}TAttsC=∅, it holds that{a mathematical formula}JE=cl(C).
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="•">
        If {a mathematical formula}A&gt;B∈JE, by Definition 14 it holds that there is an argument {a mathematical formula}〈X,A&gt;B〉 in E, thus {a mathematical formula}〈X,A&gt;B〉 in {a mathematical formula}ArgsC. By Definition 2 we have that {a mathematical formula}X⊆C and {a mathematical formula}A&gt;B∈cl(X). Then {a mathematical formula}A&gt;B∈cl(C).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}A&gt;B∈cl(C), then there is {a mathematical formula}X⊆C such that {a mathematical formula}A&gt;B∈cl(X) and {a mathematical formula}X is the minimal set holding that. Then by Definition 2, {a mathematical formula}〈X,A&gt;B〉∈ArgsC. Additionally, given that {a mathematical formula}TAttsC=∅, it holds that {a mathematical formula}RAttsC=∅ and {a mathematical formula}IAttsC=∅, then the associated AFRA of {a mathematical formula}C is {a mathematical formula}〈ArgsC,∅〉. Therefore, by Definition 12 it holds that {a mathematical formula}E=ArgsC. Then {a mathematical formula}〈X,A&gt;B〉∈E, and by Definition 14 holds that {a mathematical formula}A&gt;B∈JE.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proposition 7">
      Let{a mathematical formula}Cbe a credibility base with{a mathematical formula}JEthe set of justified credibilities of an extension E of{a mathematical formula}C. If{a mathematical formula}TAttsC≠∅then it holds that{a mathematical formula}JE⊂cl(C).
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="•">
        If {a mathematical formula}A&gt;B∈JE then, by Definition 14, there is an argument {a mathematical formula}〈X,A&gt;B〉 in E. By Definition 2 it holds that {a mathematical formula}X⊆C and {a mathematical formula}A&gt;B∈cl(X). Then {a mathematical formula}A&gt;B∈cl(C).
       </list-item>
       <list-item label="•">
        Since {a mathematical formula}TAttsC≠∅, there are two arguments with contradictory conclusions, for instance, {a mathematical formula}〈X,A&gt;B〉 and {a mathematical formula}〈Y,B&gt;A〉. Then, by Definition 2 it holds that {a mathematical formula}A&gt;B∈cl(X), {a mathematical formula}B&gt;A∈cl(Y), {a mathematical formula}X⊆C, and {a mathematical formula}Y⊆C; thus, {a mathematical formula}A&gt;B and {a mathematical formula}B&gt;A are in {a mathematical formula}cl(C). By Definition 5{a mathematical formula}(X,Y) and {a mathematical formula}(Y,X) are in {a mathematical formula}TAttsC; so, by Definition 10, Definition 12, if {a mathematical formula}X∈E it holds that {a mathematical formula}Y∉E and, therefore, by Definition 14{a mathematical formula}B&gt;A∉JE. On the other hand, if {a mathematical formula}Y∈E it holds that {a mathematical formula}X∉E, then by Definition 14 results that {a mathematical formula}A&gt;B∉JE. □
       </list-item>
      </list>
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Applying our approach to real world domains
     </section-title>
     <paragraph>
      A possible application of our approach is to use the proposed mechanism to estimate and maintain the credibility associated with individuals in a social network. The idea is to feed our framework with the information emerging from the interaction between the users of the network to obtain a (possibly partial) ordering of said users that will reflect their credibility. This credibility relation can then, in turn, be used by one of the users to help in deciding between contradictory opinions/positions of two other users.
     </paragraph>
     <paragraph>
      Let us consider for instance Twitter, which is an online news and social networking service that allows users to post and exchange short messages known as “tweets”. A user in Twitter can propagate a tweet from another user by “retweeting” it. A retweeted message contains a reference to the user who originally posted it. The strength of Twitter as a medium for information dissemination is based in large part on its speed and number of retweets. Retweeting is often used as an indication that the original information was of high value or significant interest for the retweeting user. There are studies showing that retweeting indicates, not only interest in a message, but also trust in the message and the originator [2], [26]. Therefore, retweets can be seen as indicators of trust based on the propagation of information. That is, if a user A retweets messages from a user B often, then it can be considered that user A implicitly trusts user B[39].
     </paragraph>
     <paragraph>
      We can use our formalism to measure user trust resulting of the retweet behavior of a group of Twitter users. For this, based on the intuition mentioned above, we can use the retweets as a measure of credibility among users. The idea is to use the retweets from a user as an indicator of how credible are other users for her. Then, intuitively, if user A retweets more from user B than from another user C there is an indication that A will find B more credible than C. Using that information, we will be able to construct a credibility object {a mathematical formula}[B&gt;C,A]. Each user will have their own credibility assessment according to their retweeting profile, and it is possible that two or more users have discrepancies in such valuation. For instance, if we have that user D retweets more posts from user C than posts from user B, then there is an indication that D finds more credible C than B, contrasting with the assessment of user A discussed above. In this scenario, we will construct {a mathematical formula}[C&gt;B,D]. Using our formalism, if we consider the credibility objects for A and D, we will have two conflicting arguments (they will trust-attack each other).
     </paragraph>
     <paragraph>
      Another consideration regarding measuring user trust in this scenario is that we have to deal with situations where users can retweet posts among each other leading to potentially recursive valuation. Our formalism provides a tool to reason with the above-mentioned conflicts in the context of such recursivity, as we have shown through the paper. In particular, using reliability attacks, most reliable sources will help decide among conflicts of assessment. Then, a user X that is the one that has been the most retweeted (that is, simply counting how much she has been retweeted) in our approach will not necessarily be the most credible user. To decide this, a qualitative argumentation analysis will be carried out considering how reliable are the users that report X as the most credible user and how reliable are the users estimating the contrary. Also, contrasting with the existing methods for user trust assessment the argumentation reasoning mechanism provides an intelligible explanation of the trust valuation process from a human point of view [17], [16]. Therefore, using our mechanism to measure the credibility of Twitter users based on their retweeting profiles, would give a user a qualitative and explanatory tool to choose when she has to make a decision regarding the information that other users provide.
     </paragraph>
     <paragraph>
      In the last years, the use of trust and reputation systems for enhancing on-line service provision has been widely used (e.g., Amazon, eBay, GoogleMaps, Trip Advisor, AirBnB, Stack Exchange). As stated in [21], those systems use the aggregated ratings about a given party to derive a trust or reputation score, which can assist other parties in deciding whether or not to transact with that party in the future. A natural side effect is that it also provides an incentive for good behavior, and therefore tends to have a positive effect on market quality. Any system that facilitates interaction between humans depends on how they respond to it and people appear to respond well to online services that have a reputation component despite some of them having drawbacks or being somewhat primitive.
     </paragraph>
     <paragraph>
      Note that in all the systems mentioned in the paragraph above, users rank other users. Hence, our proposed approach can be used as a complement to enhance the way in which reputation is assessed in those systems. Consider for instance Stack Exchange which is a network of question-and-answer websites on topics in varied fields, each site covering a specific topic in which questions, answers, and users are subject to a reputation award process. Each users' reputation score goes up when others users vote up questions, answers, and edits (e.g., currently, +5 for a question voted up, +10 for an answer voted up, +15 when an answer is accepted, and +2 for an edit approved). Once the reputation score of a user reaches certain level, the user unlocks privileges like the ability to vote, comment, and edit other users posts and also vote down (that costs one reputation point). For instance, with a reputation score of 15 the user has the privilege to vote, with 50 the privilege to leave comments, and with 125 to vote down. At the highest levels, users have access to special moderation tools to keep the site focused and helpful.
     </paragraph>
     <paragraph>
      Similarly to the application described above for Twitter, when users vote other user's questions or answers, not only they are increasing their partners' reputation but also they are setting their preferences among them. That is, if a user A gives more positive feedback (votes, etc.) to the user B than the user C, then there is an indication that A finds B more credible than C. Also, if for a query there are several answers given for instance by users G, H, and I and user A votes for G's answer, then a preference can be inferred: that for A user G is more credible than H or I. Note that no preference of A over H or I can be entailed. That is, in terms of our proposed notation {a mathematical formula}[G&gt;H,A] and {a mathematical formula}[G&gt;I,A]. In all the websites of the Stack Exchange community users rank other users, then, following with this example, it can also be the case that for a different user B, it can be inferred that {a mathematical formula}[H&gt;G,B]. Consider finally that from the same website it can be inferred that {a mathematical formula}[A&gt;B,X], then our proposed approach can be applied to decide between two contradictory answers given by users G and H, using more information than the rankings of these answers.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      As we mentioned before in this article, and also in [36], [37], trust kept as a credibility order can present contradictory information, that is, from a credibility base it is possible to infer that an agent is more credible than other and vice versa. To address this issue, in [36] the authors formalized change operators over a credibility base following belief revision techniques aiming to maintain credibility bases without contradictory information. Maintaining consistency using those belief revision operators will lead to lose some information. Since obtaining information is an expensive process, in contrast to [23], in order to avoid losing information to maintain consistency, in our approach, we have proposed to keep all beliefs even in situations in which the credibility bases are contradictory. In dynamic scenarios where the trust model uses witness information[28], [32] with many interactions, our approach covers cases in which beliefs that are currently not important may become so in the future.
     </paragraph>
     <paragraph>
      In [36] the credibility bases were defined in a similar manner as in the present work. There, in order to determine which information prevails when contradictory information arises, a reliability function was used to obtain a set of agent identifiers which represents the credibility of a given credibility element, and it considers all the agent identifiers involved in every minimal proof of that credibility element. They follow a cautious approach: the function first obtains the set with the least credible agent identifiers from each proof, and then, if there exist more than one proof, the most credible identifiers of the resulting set. Therefore, to compute the reliability of a credibility element, they use a function min and a function max. Thus, based on a credibility base, they define a function such that when given a credibility element in the transitive closure of the credibility base will return a set of agent identifiers that represents the reliability of the credibility element with respect to the credibility base. In our work, where credibility bases may contain information in conflict, it becomes unsound to compute reliability using the functions min and max because this can lead to potential cycles. For this reason, in this article, we defined an argumentation formalism with recursive attacks which provides the capability to infer a strict partial order from a credibility base (without contradictory information). In addition, in [36], the possibility that an agent receives multiple beliefs simultaneously, was not considered; for that reason, in that approach the order in which the beliefs are acquired will affect which information is retained by the agent. In contrast to [23], the proposal introduced here gives the capability of adding multiple beliefs simultaneously. This choice allows to address cases where it is possible to join two or more bases without worrying about the possible contradictions that may arise.
     </paragraph>
     <paragraph>
      The works [27] and [38] propose an argumentation formalism that can be used to reason using information about trust. This formalism is described as a set of graphs, and to determine agent's beliefs the authors propose a model which considers the trust in the information that is used for building arguments. Like ours, this approach is intended for a multi-agent setting and informant agents can have different credibilities. In contrast to our work, where each agent has its own credibility order, they use a centralized notion of trust that is codified in a shared trust network. This global network holds information about how agents trust each other and can be used to obtain an agent-centric trust network that represents the viewpoint of a particular agent. Although from these graphs it is possible to determine a credibility order for each agent, these orderings are strongly dependent on the connections in the global network. In contrast, in our work each agent has its own credibility order which is completely independent from the credibility order of any other agent. Another significant difference is that they use numerical values to establish the trust relation among agents, leading to a total order on the set of agents. In contrast, our approach uses symbolic information and an argumentation system to infer a strict partial order. Similarly to our formalism, each piece of information is linked to an agent that determines how credible this information is, and the formalism in [27], [38] uses an argumentation inference mechanism to deal with a potentially contradictory belief base. Nevertheless, unlike in our approach, in theirs there are no inconsistencies in the trust networks and their beliefs do not involve information about trust. Their argumentation system uses trust information from these networks to reason with non-trust referring beliefs while, in contrast, ours uses credibility information to reason about the potential conflicts in the credibility.
     </paragraph>
     <paragraph>
      In [18], [19], in a manner similar to ours, the authors use a symbolic approach to model credibility using two global relations: the trust relation and the distrust relation. These relations together with the set of agents constitute a trust system. A pair {a mathematical formula}(a,b) in the trust (distrust) relation determines that agent a trusts (distrusts) agent b. Their formalism aims to determine whether an agent trusts another taking into account the potential conflicts that may appear when the trust and distrust relations are analyzed together in the trust system. To do this, they follow an argumentation approach in which arguments represent a position for an agent to either trust or distrust a peer. Additionally, when considering an advanced version of their system, each agent is also provided with a partial order defined among its peers, using this order to codify the efficacy in which this agent trusts its peers (aiming to model a grade of trustworthiness or reputation). Even if this can be seen as similar to the credibility base of our proposal, their efficacy measure is a partial order while our bases, as we have shown in various examples, are not necessarily ordered. Therefore, their efficacy is a consistent measure while a credibility base can have credibility conflicts. In addition, they use these efficacy orders to provide strength to their arguments in order to decide if an agent trusts another or not, while we use the credibility base to build arguments and reason about the credibility itself. In this sense, the goal of the argumentation systems differ. They aim to decide if an agent trusts another or not from the trust and distrust relation, while our formalism aims to determine a partial order form a potentially contradictory credibility base. Nevertheless, similarly to us, their proposal aims to enrich the trust mechanisms by allowing the representation of conflicting trust notions and use an argumentation mechanism to decide which information prevails. It could be interesting to study how to integrate our credibility bases with their efficacy measure and how our formalism could consider trust and distrust relations as theirs.
     </paragraph>
     <paragraph>
      In our system, given the nature in which reliability-attacks are generated, a weakest link approach is used to decide between conflicting arguments (between trust-attacks, specifically). With this we aim to capture the notion that an argument for a credibility element is as weak as the weakest (least reliable) source that provided information to build such an argument. Intuitively, using this approach in a conflicting situation, the more sources used to build an argument the more chances that the argument ends up defeated. Nevertheless, it is worth to mention that, in our model, we do not explicitly deal with the problem of assessing the trustworthiness of a piece of information considering the amount of sources needed to infer it. There are more comprehensive approaches to deal with this problem like [11], [22]. In [22], an argumentation mechanism based on trust is used as a layer of a belief revision process for agents dealing with (potentially conflicting) opinions about their pairs. In that argumentation approach, trust is used to build a preference ordering amongst arguments. First, they aggregate the information of the different opinions regarding the same proposition. Then, using these aggregated propositions, they build arguments whose trustworthiness is assessed using a conjunctive fusion operator over the opinions forming the argument. This assessment considers the number of agents and information pieces which where needed for building the argument. The work of [11] is similar to [22] in the sense that they use the argumentation mechanism as part of a belief revision process to deal with potentially conflicting information obtained from different sources. Agents transmit complete arguments and, to calculate trustworthiness, they use the most trustworthy source that communicated an argument in an iterative fuzzy labeling process. Even though these works do not have explicit mechanisms for considering agents that provide information about the trust relation on their peers, it could be interesting to adapt some of their ideas to our system. For that purpose, we can think of two alternatives: either extend the notion of basic reliability-attack to consider the above mentioned strategies, or extend the AFRA to consider preferences codifying these strategies.
     </paragraph>
     <paragraph>
      In [12], the authors propose a framework over multi-agent systems which uses trust to make decisions. Like ours, the agents interact exchanging information and these agents consider the sources to compute the trust of the information; however, they perform the computation of credibilities through a possibilistic model which they use to determine the acceptance of information in a framework to support belief revision. In our framework, we adopt a symbolic approach and the credibility of a piece of information is evaluated considering all the credibility objects using an argumentation framework. Furthermore, their proposal works in scenarios that are not necessarily collaborative using trust and distrust, where the credibility of a piece of information represents the capability of the agent to evaluate the tenability of the piece of information with respect to its own competence and the ones of the sources.
     </paragraph>
     <paragraph>
      In [29], a qualitative bipolar argumentative modeling of trust is proposed. Similar to our proposal, their approach is qualitative and only a finite number of levels is assumed in the trust scale. In contrast with our proposal they use a bipolar argumentative approach where trust and distrust can be independently assessed. In their approach, an agent can evaluate its trust into an object X (that can be either a source or another agent) on the basis of two types of information: the observed behavior of X, and the reputation of X according to the other agents. Reputation information is viewed as an input information used for revising or updating its own trust evaluation based on its perception. Two kinds of arguments in favor of trusting an agent (either pointing out that a good point is reached or a bad point is avoided), and also two kinds of arguments against trusting an agent can be constructed (either pointing out that a bad point is satisfied or that a good point is not reached). These four kinds of arguments are based on an inference rule and the trust evaluation of the agent, that is represented with an interval {a mathematical formula}[t−,t+] over a discrete scale S, with the intended meaning that the trust is not larger than t+ and not smaller than t−. Although the paper indicates some basic mechanisms leading to revision of trust values, it is mainly focused on trust evaluation rather than trust dynamics in a multiple-agent world.
     </paragraph>
     <paragraph>
      The work reported in [23], describes an approach that enables personalized communication about trust. The proposal is based on certain capabilities an agent must have. Namely, the ability to adapt its trust model to personalize its evaluations to the other agent's needs, the capability of communicating its criteria for evaluating trust together with the beliefs and goals that led to these criteria, and the willingness and ability to change its trust model when and if it is persuaded that it is wrong. A difference with the work presented here is that their proposal considers aggregation and a dialogue between agents to obtain conclusions regarding trust. We have concentrated on producing a system that addresses the problem of receiving trust information where the argumentation process is circumscribed to that information, while Koster et al. consider the beliefs and goals of the participants to build the arguments. It is interesting to note that it could be possible to integrate both systems in a sufficiently complex framework; this effort is outside the current goals of this research.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>