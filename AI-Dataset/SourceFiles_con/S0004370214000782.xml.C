<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A general framework for sound assumption-based argumentation dialogues.
   </title>
   <abstract>
    We propose a formal model for argumentation-based dialogues between agents, using assumption-based argumentation (ABA) as the underlying argumentation framework. Thus, the dialogues amount to conducting an argumentation process in ABA. The model is given in terms of ABA-specific utterances, debate trees and forests implicitly built during and drawn from dialogues, legal-move functions (amounting to protocols) and outcome functions. The model is generic in that it is not restricted to any specific dialogue types and can be used to support a wide range thereof. We prove a formal connection between dialogues and three well-known argumentation semantics (i.e. grounded, admissible and ideal extensions), by giving soundness results for our dialogue models with respect to these semantics. Thus, our dialogues can be seen as a distributed mechanism for successfully determining acceptability of claims (with respect to the semantics considered), while constructing argumentation frameworks and arguments for these claims.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Argumentation-based dialogue systems have attracted considerable research interest in recent years (e.g. see [33], [27]), largely due to the need for agents to communicate and agree in multi-agent systems. Indeed, argumentation is a powerful reasoning abstraction where conflicting positions or opinions are evaluated against one another in order to resolve conflicts. Argumentation has been used quite extensively in AI in the last two decades to support a number of applications and address a number of problems (e.g. see [4], [5], [38] for an overview). To support this line of research, several argumentation frameworks have been proposed through the years, including [11], [7] and many more (see for example [1] for a recent overview of some approaches). The modern study of formal dialogue systems for argumentation can be deemed to have started with Charles Hamblin's work [24]. The topic was initially studied within philosophical logic and argumentation theory [26], [43]. Subsequently, researchers from the field of AI &amp; law [23], [31] and multi-agent systems [3], [30] have looked into dialogue systems as well.
     </paragraph>
     <paragraph>
      This paper presents a two-agent argumentation-based dialogue model, using Assumption-based Argumentation (ABA) [7], [12], [40], [42] for the representation of arguments and attacks, and for determining “success” of dialogues. ABA is well-suited as a foundation for argumentation-based dialogues for a number of reasons. It is a general purpose argumentation framework with several applications (e.g. see [12], [40], [42]) including applications requiring dialogues between agents [20]. It is a structured argumentation frameworks, so that a dialogue model based on it can allow the collective construction of arguments and attacks, and a distributed evaluation of “success”, rather than forcing, as when using abstract argumentation [11], for example as in [36], that arguments and attacks are determined and/or constructed individually by agents or collectively but prior to dialogues. At the same time, it is an instance of abstract argumentation [15], [40] and it admits abstract argumentation as an instance [40], thus allowing our dialogue model to accommodate, as a special case, the communication and evaluation of abstract arguments as well. There are several other structured argumentation frameworks available as a basis for argumentation-based dialogues, notably logic-based argumentation [5], DeLP [22] and, more recently, ASPIC+ [34] (see [1] for a recent survey of all these structured argumentation frameworks). Of these, only ASPIC+ is an instance of abstract argumentation and allows abstract argumentation dialogues to be generated, if required by applications. ASPIC+ is a generalisation of ABA and has been designed to admit ABA as an instance [34]. Thus, our ABA-based dialogue model can also be seen as a dialogue model based on ASPIC+, and extending the functionalities and properties of dialogue models based on precursors of ASPIC+ (e.g. [32], [33], as we will discuss later). Another essential feature of ABA, for the purposes of this article, is that it is equipped with provably correct computational mechanisms with respect to several semantics [14], [15], [41]. We rely upon aspects of these mechanisms, as well as their soundness, in order to prove our formal soundness results.
     </paragraph>
     <paragraph>
      An ABA framework consists of rules, assumptions, and contraries, specified in a logical language. Informally, rules and assumptions form deductions (arguments); contraries of assumptions provide means of specifying counter-arguments (attacks) against arguments. Within an ABA framework, sets of arguments are deemed “acceptable” if they fulfil certain properties, e.g., under the semantics of admissible extensions [7], [12], a set of arguments does not attack itself and attacks all arguments that attack it. Then, claims are deemed “acceptable” if they are supported by (are conclusions of) arguments that belong to “acceptable” sets.
     </paragraph>
     <paragraph>
      Our dialogue model makes use of the same building blocks as ABA, in that a dialogue is composed of utterances whose content may be a rule, an assumption, a contrary, or a claim whose “acceptability” needs to be ascertained. In addition, the content of utterances may be a pass, amounting to the agent contributing no information to the dialogue at the time of the utterance. Dialogues start with an agent putting forward a claim. Our dialogue model is generic in that it does not focus on any particular dialogue type, e.g. information seeking, persuasion or negotiation [43], but can be used to support several such dialogue types [17], [18], [19], [20].
     </paragraph>
     <paragraph>
      Through dialogues, the participating agents construct a “joint knowledge base” by pooling all disclosed information to form an ABA framework. The ABA framework drawn from a dialogue δ, referred to as {a mathematical formula}Fδ, contains all information that the two agents have uttered in the dialogue and gives the context for examining the acceptability of the claim of the dialogue. Conceptually, a dialogue is “successful” if its claim is “acceptable” in {a mathematical formula}Fδ. Note that the claim of a dialogue may be a belief, and acceptability thereof an indication that the agents may legitimately uphold the belief, or a course of actions, and acceptability thereof an indication that the agents may legitimately choose to adhere to it. Indeed, acceptability has so far shown to be an important criterion for assessing the outcome of various types of dialogues [17], [18], [19], [20], and thus “successful” dialogues can be seen as building blocks of a widely deployable framework for distributed interactions in multi-agent systems. We focus here on three forms of “acceptability” and “success”, with respect to three well-known argumentation semantics.
     </paragraph>
     <paragraph>
      Rather than checking “success” retrospectively, we define legal-move functions guaranteed to generate “successful” dialogues if a limited form of retrospective checking by means of outcome functions succeeds. Given a dialogue, a legal-move function returns a set of allowed utterances that can be uttered to extend the dialogue. Legal-move functions can thus be viewed as dialogue protocols. Outcome functions are mappings from dialogues to true/false. Given a dialogue, an outcome function returns true if a certain property holds for that dialogue.
     </paragraph>
     <paragraph>
      In summary, the main contributions of this work are: (1) a generic formal model for ABA-based dialogues; and (2) the link between this model and standard argumentation semantics (of grounded, admissible and ideal extensions) to define success of these dialogues. We focus on these three semantics as they allow to capture general forms of credulous reasoning (admissible) and two well-understood forms of sceptical reasoning (grounded and ideal), and are thus suitable for a wide range of problems. Our soundness results are obtained by mapping the debate tree/debate forest generated from a dialogue onto an abstract dispute tree[14] that is known to sanction the “acceptability” of the claim [14], [15]. These debate tree/forest can be seen as a commitment store[43] holding information that agents disclose and share using the dialogue.
     </paragraph>
     <paragraph>
      The paper generalises and extends the initial proposal of ABA-based dialogues in [16] in several ways. Firstly, this paper shows soundness results with respect to grounded, admissible and ideal extensions, rather than just admissible extensions as in [16]. Secondly, [16] uses “dialectical trees”, which are mapped onto the concrete dispute trees of [14] whereas this work uses a new notion of debate trees (see Definition 8.1), which are mapped onto the abstract dispute trees of [14], directly allowing to use soundness results from [15]. Moreover, [16] defines dialectical trees constructively, whereas this work defines debate trees declaratively, allowing to prove some novel results (e.g. Lemma 11.1). Thirdly, in this paper we define debate forests and use them to study unrestricted dialogues, completely absent from [16], which studies focused dialogues only.
     </paragraph>
     <paragraph>
      The article is structured as follows. Section 2 presents background on ABA. Section 3 sets the foundation of our dialogue framework and Section 4 introduces generic notions of legal-move and outcome functions. Section 5 defines specific kinds of these functions to generate special kinds of dialogues, guaranteed to draw ABA frameworks. Section 6 defines the three notions of “successful” dialogue we are after, in a non-constructive way. Section 7 starts refining the dialogue framework by introducing new legal-move and outcome functions that enforce core properties of “successful” dialogues, constructively. Section 8 presents debate trees that are then used to define legal-move and outcome functions, in Section 9, allowing to construct “successful” dialogues and prove our soundness results in Sections 10 and 11, for focused and unrestricted dialogues, respectively. Section 12 discusses related works and Section 13 concludes.
     </paragraph>
     <paragraph>
      The proposed dialogue model relies upon several notions and formal definitions: the most important amongst these are summarised in a glossary in Appendix A, to aid readability.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background: assumption-based argumentation (ABA)
     </section-title>
     <paragraph>
      An ABA framework is a tuple {a mathematical formula}〈L,R,A,C〉 where
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}〈L,R〉 is a deductive system, with a language{a mathematical formula}L and a set of inference rules{a mathematical formula}R of the form {a mathematical formula}β0←β1,…,βm(m&gt;0) or {a mathematical formula}β0← with, for {a mathematical formula}i=0,…,m, {a mathematical formula}βi∈L, and, if {a mathematical formula}m&gt;1, then {a mathematical formula}βi≠βj for {a mathematical formula}i≠j, {a mathematical formula}1≤i,j≤m{sup:1};
      </list-item>
      <list-item label="•">
       {a mathematical formula}A⊆L is a (non-empty) set, whose elements are referred to as assumptions,
      </list-item>
      <list-item label="•">
       {a mathematical formula}C is a total mapping from {a mathematical formula}A into {a mathematical formula}2L−{{}}, where each {a mathematical formula}c∈C(α) is a contrary of α.{sup:2}
      </list-item>
     </list>
     <paragraph>
      Basically, ABA frameworks can be defined for any logic specified by means of inference rules. Some of the sentences in the underlying language are assumptions.
     </paragraph>
     <paragraph>
      Given {a mathematical formula}β0←β1,…,βm or {a mathematical formula}β0←, {a mathematical formula}β0 is referred as the head and {a mathematical formula}β1,…,βm or the empty sequence, respectively, as the body. We will use the following notation: {a mathematical formula}Head(β0←β1,…,βm)=β0; {a mathematical formula}Body(β0←β1,…,βm)=β1,…,βm, {a mathematical formula}Head(β0←)=β0, and {a mathematical formula}Body(β0←) is empty. An ABA framework is flat iff no assumption is the head of a rule. We will focus on flat ABA frameworks, so as to be able to use results valid for them (see later).
     </paragraph>
     <paragraph label="Example 2.1">
      Let {a mathematical formula}AF1=〈L1,R1,A1,C1〉 be as follows:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}L1={a,b,c,p,q,r,s},
      </list-item>
      <list-item label="•">
       {a mathematical formula}R1={p←a,q←b,s,r←c,s←},
      </list-item>
      <list-item label="•">
       {a mathematical formula}A1={a,b,c},
      </list-item>
      <list-item label="•">
       {a mathematical formula}C1(a)={q},C1(b)={p},C1(c)={r,q}.
      </list-item>
     </list>
     <paragraph>
      In ABA, informally, arguments are deductions of claims supported by sets of assumptions, and attacks against arguments are directed at the assumptions in their supports, and are given by arguments with an assumption's contrary as their claim. Formally, given an ABA framework {a mathematical formula}〈L,R,A,C〉, an argument for {a mathematical formula}β∈L supported by {a mathematical formula}A⊆A is a tree with nodes labelled by sentences in {a mathematical formula}L or by τ,{sup:3} such that
     </paragraph>
     <list>
      <list-item label="1.">
       the root is labelled by β
      </list-item>
      <list-item label="2.">
       for every node N
      </list-item>
      <list-item label="3.">
       A is the set of all assumptions labelling the leaves.
      </list-item>
     </list>
     <paragraph>
      The shorthand {a mathematical formula}A⊢β is used to denote an argument for β supported by A. Given argument {a mathematical formula}A⊢β, A is referred to as the support and β as the claim. Fig. 1 illustrates this notion of argument for {a mathematical formula}AF1 in Example 2.1.
     </paragraph>
     <paragraph>
      With the notion of arguments and contrary of assumption, attack in an ABA framework is defined as follows:
     </paragraph>
     <list>
      <list-item label="•">
       an argument {a mathematical formula}A1⊢β1 attacks an argument {a mathematical formula}A2⊢β2 iff the claim {a mathematical formula}β1 of the first argument is a contrary of one of the assumptions in the support {a mathematical formula}A2 of the second argument (i.e., {a mathematical formula}∃α∈A2 such that {a mathematical formula}β1∈C(α));
      </list-item>
      <list-item label="•">
       a set of arguments As attacks a set of arguments Bs if some argument in As attacks some argument in Bs;
      </list-item>
      <list-item label="•">
       a set of assumptions {a mathematical formula}A1 attacks a set of assumptions {a mathematical formula}A2 iff an argument supported by a subset of {a mathematical formula}A1 attacks an argument supported by a subset of {a mathematical formula}A2.
      </list-item>
     </list>
     <paragraph label="Example 2.2">
      Continuation of Example 2.1In {a mathematical formula}AF1, we have that {a mathematical formula}{a}⊢p attacks {a mathematical formula}{b}⊢q, {a mathematical formula}{b}⊢q attacks {a mathematical formula}{a}⊢p, {a mathematical formula}{b}⊢q attacks {a mathematical formula}{c}⊢r, and {a mathematical formula}{c}⊢r attacks {a mathematical formula}{c}⊢r. Also, {a mathematical formula}{{a}⊢p} attacks {a mathematical formula}{{b}⊢q,{c}⊢r} and {a} attacks {b}, {b} attacks {a, c}, {b} attacks {c}, and {c} attacks any set of assumptions containing c.
     </paragraph>
     <paragraph>
      With argument and attack defined, all argumentation semantics introduced in abstract argumentation [11] can be applied in ABA. These semantics can be defined for assumptions, as in [8], [7], or, equivalently, for arguments [15], [40]. Formally, given {a mathematical formula}F=〈L,R,A,C〉, sets of assumptions can be deemed to be acceptable according to the following semantics{sup:4}:
     </paragraph>
     <list>
      <list-item label="•">
       a set of assumptions is admissible (in {a mathematical formula}F) iff it does not attack itself and it attacks all {a mathematical formula}A⊆A that attack it;
      </list-item>
      <list-item label="•">
       a set of assumptions is complete (in {a mathematical formula}F) iff it is admissible (in {a mathematical formula}F) and contains all assumptions it defends (in {a mathematical formula}F), where a set of assumptions A defends another set of assumptions {a mathematical formula}A′ (in {a mathematical formula}F) iff A attacks all sets of assumptions that attack {a mathematical formula}A′;
      </list-item>
      <list-item label="•">
       a set of assumptions is grounded (in {a mathematical formula}F) iff it the least set (with respect to ⊆) that is complete (in {a mathematical formula}F);
      </list-item>
      <list-item label="•">
       a set of assumptions is preferred (in {a mathematical formula}F) iff it is maximally (with respect to ⊆) admissible (in {a mathematical formula}F);
      </list-item>
      <list-item label="•">
       a set of assumptions is ideal (in {a mathematical formula}F) iff it is an admissible set (in {a mathematical formula}F) contained in all preferred sets (in {a mathematical formula}F).
      </list-item>
     </list>
     <paragraph>
      In this paper, we will also use the following notions of individual arguments and sentences being acceptable according to different argumentation semantics:
     </paragraph>
     <list>
      <list-item label="•">
       an argument{a mathematical formula}A⊢βis admissible (complete, grounded, preferred, ideal) (in{a mathematical formula}F) supported by{a mathematical formula}A′⊆A iff {a mathematical formula}A⊆A′ and {a mathematical formula}A′ is admissible (complete, grounded, preferred, ideal, respectively) (in {a mathematical formula}F);
      </list-item>
      <list-item label="•">
       a sentence is admissible (complete, grounded, preferred, ideal) (in {a mathematical formula}F) iff it is the claim of an argument that is admissible (complete, grounded, preferred, ideal, respectively) (in {a mathematical formula}F) supported by some {a mathematical formula}A⊆A.
      </list-item>
     </list>
     <paragraph>
      In this paper we will focus on the admissible, grounded and ideal semantics.
     </paragraph>
     <paragraph label="Example 2.3">
      Continuation of Example 2.2The sets of assumptions {a mathematical formula}{a}, {a mathematical formula}{b}, {} are all admissible (and no other set is admissible). Amongst these, {} is the only grounded as well as the only ideal set, and {a mathematical formula}{a} and {a mathematical formula}{b} are the only preferred sets.The sets of arguments {a mathematical formula}{{a}⊢p}, {a mathematical formula}{{b}⊢q}, {a mathematical formula}{{a}⊢a}, {a mathematical formula}{{b}⊢b}, {a mathematical formula}{{a}⊢p,{a}⊢a}, {a mathematical formula}{{b}⊢q,{b}⊢b}, and {} are all admissible (and no other set is admissible). Amongst these, {} is the only grounded as well as the only ideal set, and {a mathematical formula}{{a}⊢p,{a}⊢a} and {a mathematical formula}{{b}⊢q,{b}⊢b} are the only preferred sets. Finally, p and q are both admissible, whereas no sentence is grounded or ideal.
     </paragraph>
     <paragraph>
      We will use the abstract dispute trees of [14] to prove some of our results later, where an abstract dispute tree for an argument A (in an ABA framework {a mathematical formula}F) is a (possibly infinite) tree {a mathematical formula}Ta such that{sup:5}:
     </paragraph>
     <list>
      <list-item label="1.">
       every node of {a mathematical formula}Ta holds an argument B (in {a mathematical formula}F) and is labelled by either proponent (P) or opponent (O), but not both, denoted by {a mathematical formula}L:B, for {a mathematical formula}L∈{P,O};
      </list-item>
      <list-item label="2.">
       the root of {a mathematical formula}Ta is a P node holding A;
      </list-item>
      <list-item label="3.">
       for every P node N holding an argument B, and for every argument C that attacks B (in {a mathematical formula}F), there exists a child of N, which is an O node holding C;
      </list-item>
      <list-item label="4.">
       for every O node N holding an argument B, there exists exactly one child of N which is a P node holding an argument which attacks (in {a mathematical formula}F) some assumption α in the support of B.{sup:6}α is said to be the culprit in B;
      </list-item>
      <list-item label="5.">
       there are no other nodes in {a mathematical formula}Ta except those given by 1–4 above.
      </list-item>
     </list>
     <paragraph>
      The set of all assumptions in (the support of arguments hold of) the P nodes in {a mathematical formula}Ta is called the defence set of {a mathematical formula}Ta.
     </paragraph>
     <paragraph>
      Abstract dispute trees can be used as the basis for computing various argumentation semantics as follows, given an ABA framework {a mathematical formula}F:
     </paragraph>
     <list>
      <list-item label="•">
       An abstract dispute tree {a mathematical formula}Ta is admissible iff no culprit in the argument of an O labelling node in {a mathematical formula}Ta belongs to the defence set of {a mathematical formula}Ta. The defence set of an admissible abstract dispute tree for an argument A (in {a mathematical formula}F) is admissible (Theorem 5.1 in [14]), and thus A as well as the sentence in the root node of A is admissible (in {a mathematical formula}F).
      </list-item>
      <list-item label="•">
       An abstract dispute tree is grounded iff it is admissible and finite. The defence set of a grounded abstract dispute tree {a mathematical formula}Ta for an argument A (in {a mathematical formula}F) is contained in the grounded set [12], and thus A as well as the sentence in the root node of A is grounded (in {a mathematical formula}F).
      </list-item>
      <list-item label="•">
       An abstract dispute tree is ideal iff for no O node N in the tree there exists an admissible abstract dispute tree with root N (in {a mathematical formula}F). The defence set of an ideal abstract dispute tree for an argument is ideal (Theorem 3.4 in [15]), and thus A as well as the sentence in the root node of A is ideal (in {a mathematical formula}F).
      </list-item>
     </list>
     <paragraph label="Example 2.4">
      Continuation of Example 2.3Fig. 2 gives an example of an (infinite) admissible dispute tree, with (admissible) defence set {a mathematical formula}{a}.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Basic dialogue notions
     </section-title>
     <paragraph>
      This section presents the basis of our model of argumentation-based dialogues between (two) agents, {a mathematical formula}a1 and {a mathematical formula}a2. In our dialogue model, agents can utter claims (to be debated), rules, assumptions and contraries, or pass. Thus, dialogues allow agents to “build” a shared repository of components of ABA frameworks. Note that {a mathematical formula}a1, {a mathematical formula}a2 may or may not be equipped with ABA frameworks. ABA is used as a lingua franca in the spirit of the Argument Interchange Format (AIF) [9], [37], in the sense that, internally, agents can use knowledge representation formalisms different from ABA, but, while communicating, agents convert their internal representation into ABA. Even if {a mathematical formula}a1, {a mathematical formula}a2 are equipped with ABA frameworks, the agents may or may not be truthful, in that, for example, an agent may utter “made-up” rules which do not exist in its ABA framework.
     </paragraph>
     <paragraph>
      We assume the agents share a common logical language {a mathematical formula}L and a (non-empty, possibly infinite) set {a mathematical formula}ID that:
     </paragraph>
     <list>
      <list-item label="•">
       is totally ordered, with the ordering given by &lt;;
      </list-item>
      <list-item label="•">
       contains a special element {a mathematical formula}ID0 which is the least element with respect to &lt;.
      </list-item>
     </list>
     <paragraph label="Example 3.1">
      We can choose {a mathematical formula}ID to be the set of non-negative integers, {a mathematical formula}N∪{0}. The total order relation &lt; is the standard &lt; relation, such that for {a mathematical formula}a,b∈ID, {a mathematical formula}a&lt;b iff there exists some {a mathematical formula}c∈N such that {a mathematical formula}a+c=b. For this choice of {a mathematical formula}ID, {a mathematical formula}ID0 is 0.
     </paragraph>
     <paragraph>
      For simplicity, in all our examples {a mathematical formula}ID and {a mathematical formula}ID0 are as in Example 3.1. However, several other choices are possible, including a closed interval of real numbers and a set of strings (with &lt; the lexicographic order). Utterances are defined as follows:
     </paragraph>
     <paragraph label="Definition 3.1">
      An utterance from agent {a mathematical formula}ai to agent {a mathematical formula}aj ({a mathematical formula}i,j=1,2, {a mathematical formula}i≠j) is a tuple {a mathematical formula}〈ai,aj,T,C,ID〉 where:
     </paragraph>
     <list>
      <list-item label="•">
       C (the content) is of one of the following forms:
      </list-item>
      <list-item label="•">
       {a mathematical formula}ID∈ID∖{ID0} (the identifier).
      </list-item>
      <list-item label="•">
       {a mathematical formula}T∈ID (the target); we impose that {a mathematical formula}T&lt;ID.
      </list-item>
     </list>
     <paragraph>
      Note that our utterances are generic and not tailored to any specific types of dialogues, but can be used to provide specialised semantics for specific dialogue types (such as persuasion and inquiry [43]), e.g. following the lines of [17], [18], [19], [20].
     </paragraph>
     <paragraph label="Notation 3.1">
      We use {a mathematical formula}U to denote the set of all possible utterances as in Definition 3.1, given {a mathematical formula}L, and {a mathematical formula}Ui to denote all utterances from {a mathematical formula}ai in {a mathematical formula}U, i.e. of the form {a mathematical formula}〈ai,_,_,_,_〉.
     </paragraph>
     <paragraph>
      Intuitively, when the content of an utterance is π, the utterance indicates that the agent making it does not have or want to contribute any information (i.e. claim, rule, assumption, contrary) that can be added to the dialogue at that point, either because no such information is in the agent's possession or because the agent chooses not to disclose such information. The target of an utterance is the identifier of some earlier utterance in the dialogue, as we will see next.
     </paragraph>
     <paragraph label="Definition 3.2">
      A dialogue{a mathematical formula}Dajai(χ) (between{a mathematical formula}aiand{a mathematical formula}aj,{a mathematical formula}i,j∈{1,2},{a mathematical formula}i≠j, for{a mathematical formula}χ∈L), is a sequence {a mathematical formula}〈u1,…,un〉, {a mathematical formula}n≥0, where each {a mathematical formula}ul, {a mathematical formula}l=1,…,n, is in {a mathematical formula}U, and:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}u1=〈ai,aj,_,_,_〉;
      </list-item>
      <list-item label="2.">
       the content of {a mathematical formula}ul is {a mathematical formula}claim(χ) iff {a mathematical formula}l=1;
      </list-item>
      <list-item label="3.">
       the target of pass and claim utterances is {a mathematical formula}ID0; the target of regular utterances is not {a mathematical formula}ID0;
      </list-item>
      <list-item label="4.">
       for every utterance {a mathematical formula}ul=〈_,_,T,_,_〉, such that {a mathematical formula}l&gt;1 and {a mathematical formula}T≠ID0, there exists some {a mathematical formula}uk=〈_,_,_,C,T〉, such that {a mathematical formula}C≠π and {a mathematical formula}k&lt;l;
      </list-item>
      <list-item label="5.">
       for {a mathematical formula}0≤k&lt;l≤n, if {a mathematical formula}IDl is the identifier of {a mathematical formula}ul and {a mathematical formula}IDk is the identifier of {a mathematical formula}uk then {a mathematical formula}IDk&lt;IDl.
      </list-item>
     </list>
     <paragraph label="Notation 3.2">
      We use {a mathematical formula}D to denote the set of all dialogues as in Definition 3.2.
     </paragraph>
     <paragraph label="Example 3.2">
      Given {a mathematical formula}L={s,a,b,c,d,g,q,r}, and {a mathematical formula}ID=N∪{0} with {a mathematical formula}ID0=0, a possible dialogue {a mathematical formula}Da2a1(s) is as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      Our dialogue model allows pass utterances being uttered at any moment throughout a dialogue. Given any dialogue, the π-pruned sequence obtained from the dialogue consists of all regular utterances in the dialogue.
     </paragraph>
     <paragraph label="Example 3.3">
      The π-pruned sequence obtained from the dialogue δ in Example 3.2 is {a mathematical formula}δ′ as follows:{a mathematical formula} Here {a mathematical formula}δ′=〈u1′,…,u9′〉 where {a mathematical formula}u1′=u1,u2′=u3,u3′=u4,u4′=u5,u5′=u6,u6′=u7,u7′=u8,u9′=u10, for {a mathematical formula}ui=〈_,_,_,_,i〉 in the original δ.
     </paragraph>
     <paragraph>
      Note that, since no regular utterance has a pass utterance as its target (by condition 3 in Definition 3.2), the target of every utterance in a π-pruned sequence is guaranteed to be in this sequence. Also, since the first utterance in a dialogue can never be a pass utterance (by condition 2 of Definition 3.2), the first utterance in a π-pruned sequence is always the same as the first utterance in the original dialogue. Moreover, it is trivially true that, for any utterance u, if u is not in a dialogue δ, u is not in the π-pruned sequence of δ.
     </paragraph>
     <paragraph>
      By means of dialogues agents “build” a shared repository of components of an ABA framework, defined as follows:
     </paragraph>
     <paragraph label="Definition 3.3">
      The (argumentation) framework drawn from a dialogue{a mathematical formula}δ=〈u1,…,un〉∈D is {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉 where:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Rδ={ρ|rl(ρ)is the content of some ui in δ};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Aδ={α|asm(α) is the content of some ui in δ};
      </list-item>
      <list-item label="•">
       for any {a mathematical formula}α∈Aδ, {a mathematical formula}Cδ(α)={β|ctr(α,β) is the content of some ui in δ}.
      </list-item>
     </list>
     <paragraph>
      Clearly, the framework drawn from a dialogue represents all information that has been disclosed by the two agents in the dialogue.
     </paragraph>
     <paragraph label="Example 3.4">
      The framework drawn from the dialogue δ in Example 3.2 is {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉, in which
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a,b,c};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={s←a,q←b};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={q},Cδ(b)={c},Cδ(c)={r}.
      </list-item>
     </list>
     <paragraph>
      Note that the framework drawn from the dialogues in Example 3.4 is an ABA framework, but, in general, the framework drawn from a dialogue may or may not be an ABA framework, as we will discuss later in Section 5.
     </paragraph>
     <section label="3.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       Throughout the paper, we will illustrate our model in the context of the following example, adapted from the movie Twelve Angry Men, an example of argumentation-based collaborative reasoning [2]. Here, twelve jurors need to decide whether to condemn a boy, accused of murder, or acquit him, after a trial where two witnesses have provided evidence against the boy. According to the law, the jurors should acquit the boy if they do not believe that the trial has proven him guilty convincingly. We focus on the reasoning of two of the jurors: juror 8, played by Henry Fonda ({a mathematical formula}a1), and juror 9, played by Joseph Sweeney ({a mathematical formula}a2). We can model their exchanges of opinions as the two-agents dialogue {a mathematical formula}δ=Da2a1(boy_innocent) in Table 1. Here, {a mathematical formula}a1 starts the dialogue by putting forward the claim that the boy is innocent (boy_innocent). Then both agents contribute rules, assumptions and contraries for and against the claim (directly or indirectly). The content of utterances in this dialogue should be self-explanatory. For example, {a mathematical formula}boy_innocent←boy_not_proven_guilty says that the boy should be deemed to be innocent if he cannot be proven guilty. A natural language reading of this dialogue is in Table 2. The framework drawn from this dialogue δ is {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉 where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Aδ={boy_not_proven_guilty,w1_is_believable,w2_is_believable};
       </list-item>
       <list-item label="•">
        {a mathematical formula}Rδ={boy_innocent←boy_not_proven_guilty,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Cδ(boy_not_proven_guilty)={boy_proven_guilty},{a mathematical formula}Cδ(w1_is_believable)={w1_is_not_believable},{a mathematical formula}Cδ(w2_is_believable)={w2_is_not_believable}.
       </list-item>
      </list>
      <paragraph>
       Note that this is an ABA framework.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Constructing dialogues
     </section-title>
     <paragraph>
      This section gives the basic notions used in our model to allow agents to construct dialogues. As in other dialogue models, notably that of [33], these notions amount to turn-making functions, to determine which agent should make an utterance at any point in a dialogue, legal-move functions, to determine which utterances agents can make during dialogues, and outcome functions, to determine whether dialogues have desirable properties.
     </paragraph>
     <paragraph>
      In Example 3.2, the two agents take turns in making utterances: a strict interleaving is enforced between these two agents. In general, such requirement is unnecessary, i.e., an agent may be allowed to make a few consecutive utterances before the other agent makes any. We define a turn-making function to specify which agent makes the next utterance in a dialogue.
     </paragraph>
     <paragraph label="Definition 4.1">
      A turn-making function is a mapping γ: {a mathematical formula}D↦{a1,a2} such that, given {a mathematical formula}δ=Dajai(χ)=〈u1,…,un〉, {a mathematical formula}i,j∈{1,2}, {a mathematical formula}i≠j:{a mathematical formula}A dialogue {a mathematical formula}〈u1,…,un〉 ({a mathematical formula}n&gt;0) is compatible with a turn-making function γ iff for each {a mathematical formula}l=1,…,n, if {a mathematical formula}ul=〈ax,_,_,_,_〉 then {a mathematical formula}γ(〈u1,…,ul−1〉)=ax.
     </paragraph>
     <paragraph>
      Our definition of turn-making function is very liberal, in that it states that {a mathematical formula}ai starts {a mathematical formula}Dajai(χ) and all subsequent utterances are made by any of the agents as dictated by γ. As observed earlier, {a mathematical formula}γ(δ) for {a mathematical formula}δ=Da2a1(χ) in Example 3.2 forces a strict interleaving between {a mathematical formula}a1 and {a mathematical formula}a2, whereas the dialogue in Example 3.2 does not.
     </paragraph>
     <paragraph label="Definition 4.2">
      A legal-move function (with respect to a turn-taking function γ) is a mapping {a mathematical formula}λ:D↦2U such that, given {a mathematical formula}δ=〈u1,…,un〉∈D, for all {a mathematical formula}u∈λ(δ):
      <list>
       {a mathematical formula}δ∘u is a dialogue;{a mathematical formula}δ∘u is compatible with γ if δ is;if {a mathematical formula}u=〈_,_,T,C,_〉, then there is no i, {a mathematical formula}1≤i≤n, such that {a mathematical formula}ui=〈_,_,T,C,_〉.Given
      </list>
      <paragraph>
       {a mathematical formula}δ=〈u1,…,un〉, if {a mathematical formula}um+1∈λ(〈u1,…,um〉) for all m such that {a mathematical formula}0≤m&lt;n, we say that δ is compatible with λ.
      </paragraph>
     </paragraph>
     <paragraph>
      Here condition 3 regulates that there is no repeated utterance to the same target in a dialogue. However, the definition of legal-move function does not impose any “mentalistic” requirement on agents, such as that they utter information they hold true, similarly to communication protocols in multi-agent systems [44].
     </paragraph>
     <paragraph label="Notation 4.1">
      We use Λ to denote the set of all legal-move functions.
     </paragraph>
     <paragraph>
      Different types of dialogues will require a different turn-making functions. For example, negotiation typically requires a strict interleaving, whereas inquiry does not (although strict interleaving may be used for inquiry too, as in [6]). As our dialogue framework is generic, from now on we will assume as given a generic turn-making function γ and we will omit to mention it in definitions, assuming implicitly that all our dialogues are compatible with this γ. In particular, we will omit the turn-making function when giving legal-move functions.
     </paragraph>
     <paragraph>
      We conclude this section by defining outcome functions, to determine whether dialogues have desirable properties.
     </paragraph>
     <paragraph label="Definition 4.3">
      An outcome function is a mapping {a mathematical formula}ω:D×Λ↦{true,false}.
     </paragraph>
     <paragraph label="Notation 4.2">
      We use Ω to denote the set of all outcome functions.
     </paragraph>
     <paragraph>
      In the remainder we give several concrete legal-move and outcome functions.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      ABA dialogues
     </section-title>
     <paragraph>
      In this section, we refine our dialogues so that the frameworks drawn from them are guaranteed to be flat ABA frameworks. The resulting dialogues are referred to as ABA dialogues. This refinement builds upon specific kinds of legal-move function and outcome function to restrict the kind of allowed utterances.
     </paragraph>
     <paragraph>
      As mentioned earlier, in general, the framework drawn from a dialogue may not be an ABA framework, since the contrary of some assumption may be empty:
     </paragraph>
     <paragraph label="Example 5.1">
      Given {a mathematical formula}L={s,a}, let δ be:{a mathematical formula} The framework drawn from this dialogue, {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉, has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={s←a};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={}.
      </list-item>
     </list>
     <paragraph>
      Even when the framework drawn from a dialogue is an ABA framework, it may not be flat, as the agents may disagree on the assumptions:
     </paragraph>
     <paragraph label="Example 5.2">
      Given {a mathematical formula}L={s,a,q,r}, let δ be:{a mathematical formula} The framework {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉 has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={s←a,a←q};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={r}.
      </list-item>
     </list>
     <paragraph>
      We ensure flatness of the framework drawn from a dialogue using a specific kind of legal-move function, as follows.
     </paragraph>
     <paragraph label="Definition 5.1">
      A flat legal-move function is a legal-move function {a mathematical formula}λ∈Λ such that, given a dialogue {a mathematical formula}δ=〈u1,…,un〉∈D, for all {a mathematical formula}u=〈_,_,_,C,_〉∈λ(δ), then
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}C=asm(α) only if there exists no {a mathematical formula}ui for {a mathematical formula}1≤i≤n with content {a mathematical formula}rl(ρ) and {a mathematical formula}Head(ρ)=α;
      </list-item>
      <list-item label="•">
       {a mathematical formula}C=rl(ρ) only if there exists no {a mathematical formula}ui for {a mathematical formula}1≤i≤n with content {a mathematical formula}asm(α) and {a mathematical formula}Head(ρ)=α.
      </list-item>
     </list>
     <paragraph>
      δ in Example 5.2 is not compatible with a flat legal-move function.
     </paragraph>
     <paragraph label="Lemma 5.1">
      Given a dialogue{a mathematical formula}δ∈D, if δ is compatible with a flat legal-move function and the framework{a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉drawn from δ is an ABA framework, then{a mathematical formula}Fδis a flat ABA framework.
     </paragraph>
     <paragraph>
      The proof of this and all results in this article can be found in Appendix B.
     </paragraph>
     <paragraph>
      In order to guarantee that the framework drawn from a dialogue is an ABA framework, we will use a specific kind of outcome function imposing that each assumption has a non-empty set as its contrary:
     </paragraph>
     <paragraph label="Definition 5.2">
      The ABA outcome function{a mathematical formula}ωABA is such that given a dialogue {a mathematical formula}δ∈D and a legal-move function {a mathematical formula}λ∈Λ, {a mathematical formula}ωABA(δ,λ)=true iff δ is compatible with λ and the framework {a mathematical formula}〈L,Rδ,Aδ,Cδ〉 drawn from δ is such that for all {a mathematical formula}α∈Aδ,Cδ(α)≠{}. A λ-ABA dialogue is a dialogue {a mathematical formula}δ∈D with {a mathematical formula}λ∈Λ flat such that {a mathematical formula}ωABA(δ,λ)=true. An ABA dialogue is a λ-ABA dialogue for some {a mathematical formula}λ∈Λ.
     </paragraph>
     <paragraph label="Lemma 5.2">
      The framework drawn from an ABA dialogue is a flat ABA framework.
     </paragraph>
     <paragraph>
      In the remainder, all dialogues will be λ-ABA dialogues, for some (flat) λ. In the remainder of the paper we will impose further restrictions on λ to obtain specialised forms of dialogues. First, however, let us give a concrete example of ABA dialogue.
     </paragraph>
     <section label="5.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       The dialogue δ in Table 1 is an ABA dialogue. Indeed, it is compatible with a flat legal-move function {a mathematical formula}λfl since there is no β such that both {a mathematical formula}asm(β) and {a mathematical formula}rl(β←…) are contents of utterances in δ. As a result, {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉 is a (flat) ABA framework and indeed {a mathematical formula}ωABA(δ,λfl)=true, since for all assumptions
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}α∈Aδ={boy_not_proven_guilty,w1_is_believable,w2_is_believable}
       </list-item>
      </list>
      <paragraph>
       the contrary of α is not empty.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Successful dialogues
     </section-title>
     <paragraph>
      The definitions so far jointly establish the foundations of a generic dialogue framework for determining acceptability of claims (in the flat ABA framework drawn from ABA dialogues). In this section, we define three notions of successful dialogues, intuitively amounting to sanctioning the initial claims as acceptable according to the admissible, grounded and ideal semantics, respectively.
     </paragraph>
     <paragraph label="Definition 6.1">
      Given a dialogue {a mathematical formula}Dajai(χ)=δ, let {a mathematical formula}Fδ be the ABA framework drawn from δ. Then δ is:
     </paragraph>
     <list>
      <list-item label="•">
       a-successful iff χ is admissible in {a mathematical formula}Fδ;
      </list-item>
      <list-item label="•">
       g-successful iff χ is grounded in {a mathematical formula}Fδ;
      </list-item>
      <list-item label="•">
       i-successful iff χ is ideal in {a mathematical formula}Fδ.
      </list-item>
     </list>
     <paragraph>
      These notions equate success of a dialogue with determining whether its claim is semantically acceptable, according to the three semantics we focus on, in the ABA framework drawn form the dialogue. Thus, successful dialogues can be seen as a distributed mechanism for determining acceptability while also building a shared knowledge base (the ABA framework) to determine acceptability. As discussed earlier, this shared knowledge base may or may not reflect the agents' individual knowledge bases, depending on whether they are truthful or not.
     </paragraph>
     <paragraph label="Proposition 6.1">
      Given a dialogue{a mathematical formula}δ∈D, if δ is g-successful, then δ is also a-successful and i-successful.
     </paragraph>
     <paragraph label="Proposition 6.2">
      Given a dialogue{a mathematical formula}δ∈D, if δ is i-successful, then δ is a-successful.
     </paragraph>
     <paragraph label="Example 6.1">
      Let the dialogue δ be:{a mathematical formula} The ABA framework, {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉, drawn from this dialogue has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a,c};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={c},Cδ(c)={a}.
      </list-item>
     </list>
     <paragraph label="Example 6.2">
      Let the dialogue δ be:{a mathematical formula} The ABA framework, {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉, drawn from this dialogue has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a,c};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={b←};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={c}, {a mathematical formula}Cδ(c)={b}.
      </list-item>
     </list>
     <paragraph label="Example 6.3">
      Let the dialogue δ be:{a mathematical formula} The ABA framework drawn from this dialogue, {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉, has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Aδ={a,c,d};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Rδ={b←c,d};
      </list-item>
      <list-item label="•">
       {a mathematical formula}Cδ(a)={b}, {a mathematical formula}Cδ(c)={a}, {a mathematical formula}Cδ(d)={c}.
      </list-item>
     </list>
     <paragraph>
      Note that we could define a notion of p-successful dialogue, with preferred claim in the ABA framework drawn from the dialogue. Since every admissible set (of assumptions/arguments) is necessarily contained in a preferred set (see [11], [7]), and every preferred set is admissible by definition, trivially a dialogue is p-successful iff it is a-successful. Similarly, we could define a notion of c-successful dialogue, with claim in the ABA framework drawn from the dialogue. However, since every preferred set is complete (see [11], [7]) and thus every admissible set is contained in a complete set, trivially a dialogue is c-successful iff it is a-successful. Therefore, we can focus on g-, a- and i-successful dialogues.
     </paragraph>
     <section label="6.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <list>
       <list-item>
        The claim, boy_innocent, of the dialogue in Table 1 is supported by:
       </list-item>
       <list-item>
        attacked by:
       </list-item>
       <list-item>
        B and C are in turn attacked by:
       </list-item>
       <list-item>
        respectively. Since D and E are supported by the empty set, they cannot be attacked. Hence, boy_innocent is admissible, grounded, and ideal in {a mathematical formula}Fδ, and this dialogue is a-, g- and i-successful.
       </list-item>
      </list>
      <paragraph>
       In this section we have given non-constructive notions of successful dialogues, sanctioning the acceptability of their claims. In the remainder of the paper we show how successful dialogues can be constructed by deploying appropriate legal-move and outcome functions.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Related and exhaustive dialogues
     </section-title>
     <paragraph>
      In this section, we refine ABA dialogues, by using a specialised class of legal-move functions to avoid “disconnected” dialogues, and by using a new outcome function to avoid “incomplete” dialogues. The resulting refined ABA dialogues bring us closer to constructing successful dialogues.
     </paragraph>
     <paragraph>
      The following is an example of “disconnected” dialogue:
     </paragraph>
     <paragraph label="Example 7.1">
      Consider dialogue δ:{a mathematical formula} Here, there is no connection between contents of utterances and their targets, e.g., there is no connection between the rule {a mathematical formula}p←q and the sentence s, and between the assumption a and the sentence s. The dialogue is not a-successful (and thus not g- and i-successful) as indeed s is not even supported by an argument in {a mathematical formula}Fδ.
     </paragraph>
     <paragraph>
      Note that the second and third utterances in the dialogue in Example 7.1 are connected to their target in the sense of the following definition of related-ness:
     </paragraph>
     <paragraph label="Definition 7.1">
      For any two utterances {a mathematical formula}ui,uj∈U, {a mathematical formula}ui≠uj, {a mathematical formula}uj is related to{a mathematical formula}ui iff {a mathematical formula}ui=〈_,_,_,_,ID〉, {a mathematical formula}uj=〈_,_,ID,_,_〉.
     </paragraph>
     <paragraph>
      Indeed, condition 4 in Definition 3.2 enforces that all regular utterances in a dialogue are related according to this basic, syntactic notion. The following is a more purposeful notion of related-ness:
     </paragraph>
     <paragraph label="Definition 7.2">
      For any two utterances {a mathematical formula}ui,uj∈U, {a mathematical formula}ui=〈_,_,_,Ci,_〉, {a mathematical formula}uj=〈_,_,_,Cj,_〉, {a mathematical formula}uj is top–down related to{a mathematical formula}ui iff {a mathematical formula}uj is related to {a mathematical formula}ui (as in Definition 7.1) and one of the following cases holds:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Cj=rl(ρj), {a mathematical formula}Head(ρj)=β and either {a mathematical formula}Ci=rl(ρi) with {a mathematical formula}β∈Body(ρi), or {a mathematical formula}Ci=ctr(_,β), or {a mathematical formula}Ci=claim(β);
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Cj=asm(α) and either {a mathematical formula}Ci=rl(ρ) with {a mathematical formula}α∈Body(ρ), or {a mathematical formula}Ci=ctr(_,α), or {a mathematical formula}Ci=claim(α);
      </list-item>
      <list-item label="3.">
       {a mathematical formula}Cj=ctr(α,_) and {a mathematical formula}Ci=asm(α).
      </list-item>
     </list>
     <paragraph>
      Intuitively, an utterance is top–down related to another if it contributes to expanding an argument (case 1), identifies an assumption in the support of an argument (case 2) or starts the construction of a counter-argument (case 3). Note that an utterance may be top–down related to an utterance from the same agent or not. Also, no pass utterance can be top–down related to an utterance and vice versa.
     </paragraph>
     <paragraph>
      We use the notion of top–down related-ness to define a new class of legal-move functions and corresponding connected dialogues:
     </paragraph>
     <paragraph label="Definition 7.3">
      A top–down related legal-move function{a mathematical formula}λ∈Λ is such that for {a mathematical formula}δ=〈u1,…,un〉, {a mathematical formula}δ∈D, and for all {a mathematical formula}u∈λ(δ) such that u is a regular utterance, then u is top–down related to some {a mathematical formula}um in δ ({a mathematical formula}1≤m≤n). A top–down related dialogue is a λ-ABA dialogue for a top–down related {a mathematical formula}λ∈Λ.
     </paragraph>
     <paragraph>
      For simplicity, in the remainder, we use “related” to mean “top–down related”. The dialogue in Example 3.2 is related; the dialogue in Example 7.1 is not. Note that a dialogue can be compatible with a legal-move function that fulfils several purposes, e.g., being flat and related, as is the case in Example 3.2. In the remainder, all dialogues will be related.
     </paragraph>
     <paragraph>
      The following is an example of an “incomplete” dialogue:
     </paragraph>
     <paragraph label="Example 7.2">
      The following dialogue δ:{a mathematical formula} is “incomplete”, as {a mathematical formula}〈a2,a1,5,rl(c←),6〉 can be uttered as {a mathematical formula}rl(c←) is in {a mathematical formula}Fδ (since it is the content of utterance with identifier 4).
     </paragraph>
     <paragraph>
      The next notion we introduce prevents this form of “incompleteness” and gives a sense of exhaustiveness. Exhaustiveness is introduced to ensure a dialogue is “complete” in the sense that there are no “unsaid” utterances in such dialogues that would explicitly bring about important arguments for determining success. This feature will ease the proof of soundness results later.
     </paragraph>
     <paragraph label="Definition 7.4">
      The exhaustive outcome function{a mathematical formula}ωex is such that, given {a mathematical formula}δ∈D and {a mathematical formula}λ∈Λ, {a mathematical formula}ωex(δ,λ)=true iff {a mathematical formula}ωABA(δ,λ)=true and, given {a mathematical formula}〈L,Rδ,Aδ,Cδ〉 the ABA framework drawn from δ, there exists no {a mathematical formula}u′∈λ(δ) with content either:
      <list>
       {a mathematical formula}asm(α), for {a mathematical formula}α∈Aδ, or{a mathematical formula}rl(ρ), for {a mathematical formula}ρ∈Rδ, or{a mathematical formula}ctr(α,β), for {a mathematical formula}β∈Cδ(α),A
      </list>
      <paragraph>
       λ-exhaustive dialogue is a λ-ABA dialogue δ such that {a mathematical formula}ωex(δ,λ)=true and λ is related. An exhaustive dialogue is a λ-exhaustive dialogue for some {a mathematical formula}λ∈Λ.
      </paragraph>
     </paragraph>
     <paragraph>
      Note that exhaustiveness does not force agents to contribute to dialogues all relevant information they hold. Rather, it enforces that if an utterance u with content equal to an assumption, a rule or contrary has been made compatibly with a certain λ, then another utterance {a mathematical formula}u′ with the same content as u should be made in δ, if such {a mathematical formula}u′ is allowed by λ. The dialogue in Example 7.2 is not exhaustive, whereas the dialogue in Example 3.2 is.
     </paragraph>
     <section label="7.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       The dialogue δ shown in Table 1 is related and λ-exhaustive, for λ related. Indeed, in addition to being an ABA dialogue (as we have seen in Section 5.1), δ is compatible with a (top–down) related legal-move function λ as all regular utterances are related; and it is λ-exhaustive as there is no utterance {a mathematical formula}u′ related to any existing utterance with content an assumption, rule or contrary already in {a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉 (see Section 5.1) that can be added to δ.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Debate trees
     </section-title>
     <paragraph>
      In this section we define debate trees to keep track of information that has been disclosed in dialogues. These are then used to define new legal-move functions and outcome functions guaranteeing the construction of successful dialogues (see later in Section 10). The new legal-move functions allow to decide utterances on the basis of debate trees drawn from dialogues. The new outcome functions determine the outcome of dialogues on the basis of conditions satisfied by the corresponding debate trees. Informally (see Definition 8.1 below for the formal definition), each node of debate trees
     </paragraph>
     <list>
      <list-item label="1.">
       contains one sentence,
      </list-item>
      <list-item label="2.">
       is tagged as either unmarked (um), marked-rule (mr) or marked-assumption (ma),
      </list-item>
      <list-item label="3.">
       is labelled either proponent (P) or opponent (O) as in the abstract dispute trees of [14], and
      </list-item>
      <list-item label="4.">
       has an ID taken from an utterance in the dialogue.
      </list-item>
     </list>
     <paragraph>
      Intuitively, the sentence of each node in a debate tree represents an argument's claim or element of the argument's support. A node is tagged unmarked if its sentence is only mentioned in the claim or the body of a rule or contrary of an assumption, but without any further examination, marked-rule if its sentence is the head of an uttered rule, and marked-assumption if its sentence has been explicitly uttered as an assumption. A node is labelled P (O) if it is (directly or indirectly) for (against, respectively) the claim of the dialogue. The ID is used to identify the node's corresponding utterance in the dialogue.
     </paragraph>
     <paragraph>
      As an illustration, possible nodes from utterances in Example 3.2 are:{a mathematical formula} Note that, since debate trees can be viewed as constructed in steps as dialogues proceed, not all nodes in the above list are in a debate tree at every step. Namely, certain nodes tagged as um, such as {a mathematical formula}(s,um:P[1]) and {a mathematical formula}(q,um:O[5]) are replaced by nodes with “updated” information about the same sentences, i.e., {a mathematical formula}(s,mr:P[1]) and {a mathematical formula}(q,mr:O[5]), respectively, after new utterances are inserted into the dialogue. For instance, the content of utterance 5 in the dialogue in Example 3.2 is {a mathematical formula}ctr(a,q), so when this utterance occurs, q is only mentioned as a contrary of a, it is uncertain whether q is an assumption or the head of a rule, hence the tag in {a mathematical formula}(q,um:O[5]) is um. However, after utterance 6, which has content {a mathematical formula}rl(q←b), it is known that q is the head of the rule {a mathematical formula}q←b, hence {a mathematical formula}(q,um:O[5]) is replaced by {a mathematical formula}(q,mr:O[5]). Thus nodes tagged um may be replaced by other nodes during the construction of a debate tree. Also, when “updating” a node, its ID is not always changed, as seen in the example, where {a mathematical formula}(s,um:P[1]) and {a mathematical formula}(s,mr:P[1]) have the same ID (1). This is because that ID is used for book keeping purposes to decide where to insert new nodes. The rules for updating IDs are given later.
     </paragraph>
     <paragraph>
      In a debate tree, nodes are connected in two cases:
     </paragraph>
     <list>
      <list-item label="1.">
       they belong to the same argument, and
      </list-item>
      <list-item label="2.">
       they form attacks between two arguments.
      </list-item>
     </list>
     <paragraph>
      Fig. 3 (left) gives an example of the first case, for the dialogue in Example 3.2. Here, we see the connected nodes in a debate tree on the far left and, next to them, the corresponding argument (represented as a tree). In the second case, two nodes {a mathematical formula}N1=(α,ma:L[id]) and {a mathematical formula}N2=(β,_:L′[_]), {a mathematical formula}L,L′∈{P,O}, {a mathematical formula}L′≠L, are connected if there is an utterance {a mathematical formula}u=〈_,_,id,ctr(α,β),_〉 in the dialogue (e.g., see Fig. 3, right). Hence, the two nodes are connected if the parent node contains an assumption and the child node contains a contrary of that assumption.
     </paragraph>
     <paragraph>
      We give the formal definition of a debate tree as follows.
     </paragraph>
     <paragraph label="Definition 8.1">
      Given a dialogue {a mathematical formula}Dajai(χ)=δ, the debate tree drawn from δ is a tree {a mathematical formula}T(δ), where:
     </paragraph>
     <list>
      <list-item label="1.">
       nodes of {a mathematical formula}T(δ) can be characterised as follows:
      </list-item>
      <list-item label="2.">
       edges of {a mathematical formula}T(δ) are of 6 types (below {a mathematical formula}L,L′∈{P,O}, {a mathematical formula}L≠L′):
      </list-item>
     </list>
     <paragraph label="Notation 8.1">
      For convenience, we call {a mathematical formula}(_,mr:_[_]), {a mathematical formula}(_,ma:_[_]), and {a mathematical formula}(_,um:_[_]), a rule, assumption, and unmarked node, respectively.
     </paragraph>
     <paragraph>
      The debate tree {a mathematical formula}T(δ) for δ in Example 3.2 is shown in Fig. 4.
     </paragraph>
     <paragraph>
      Definition 8.1 gives the characteristics of debate trees. Debate trees are constructed as dialogues progress. The construction of debate trees is given below.
     </paragraph>
     <paragraph label="Lemma 8.1">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ, the debate tree{a mathematical formula}T(δ)is{a mathematical formula}Tm(δ)in the sequence{a mathematical formula}T0(δ),T1(δ),…,Tm(δ)constructed inductively from the π-pruned sequence {a mathematical formula}δ′=〈u1′…,um′〉obtained from δ, as follows ({a mathematical formula}L,L′∈{P,O},{a mathematical formula}L≠L′):
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}T0(δ)is empty;
      </list-item>
      <list-item label="2.">
       {a mathematical formula}T1(δ)contains a single node:{a mathematical formula}where{a mathematical formula}id1is the identifier of{a mathematical formula}u1′=u1;
      </list-item>
      <list-item label="3.">
       let{a mathematical formula}Ti(δ)be the i-th tree,{a mathematical formula}0&lt;i&lt;m, let{a mathematical formula}ui+1′=〈_,_,t,C,id〉and{a mathematical formula}〈_,_,_,Ct,t〉be the target utterance of{a mathematical formula}ui+1′; then{a mathematical formula}Ti+1(δ)is obtained as follows:
      </list-item>
     </list>
     <paragraph>
      The construction of the debate tree in Fig. 4 is shown in Fig. 5.
     </paragraph>
     <paragraph>
      Arguments can be drawn from a debate tree, as follows:
     </paragraph>
     <paragraph label="Definition 8.2">
      An argument drawn from a debate tree{a mathematical formula}T(δ) is a sub-tree {a mathematical formula}T of {a mathematical formula}T(δ) such that:
     </paragraph>
     <list>
      <list-item label="1.">
       all nodes in {a mathematical formula}T have the same label (either P or O);
      </list-item>
      <list-item label="2.">
       if there is an utterance {a mathematical formula}〈_,_,_,rl(β0←β1,…,βm),t〉 in δ and {a mathematical formula}(β0,mr:L[t]) is in {a mathematical formula}T, then {a mathematical formula}(β1,_:L[_]),…,(βm,_:L[_]) are in {a mathematical formula}T;
      </list-item>
      <list-item label="3.">
       there does not exist a node {a mathematical formula}N′ in {a mathematical formula}T(δ) such that {a mathematical formula}N′ is parent or child of some node {a mathematical formula}Ni in {a mathematical formula}T, {a mathematical formula}N′ is not in {a mathematical formula}T and {a mathematical formula}Ni,N′ have the same label.
      </list-item>
     </list>
     <paragraph label="Example 8.1">
      Given the debate tree in Fig. 4, we can draw three actual arguments and one potential argument, as shown in Fig. 6.
     </paragraph>
     <paragraph>
      Note that, in debate trees, as in abstract dispute trees [14], proponent/opponent are roles/fictitious players rather than actual agents and agents can play separate or both such roles in a dialogue. For example, in the case of inquiry dialogues [43], agents may want to play both roles interchangeably, whereas in persuasion dialogues [43] the agent putting forward the claim may play solely the role of proponent and the other agent the role of opponent.
     </paragraph>
     <paragraph label="Notation 8.2">
      We refer to an actual or potential argument drawn from a debate tree simply as actual or potential argument (respectively).We refer to arguments in ABA (see Section 2) as ABA arguments, to distinguish them from arguments drawn from debate trees.Given a debate tree {a mathematical formula}T(δ), we say that a node is in an argument (in {a mathematical formula}T(δ)) iff it is a node in some argument drawn from {a mathematical formula}T(δ).If {a mathematical formula}T is a potential argument and χ is its claim, {a mathematical formula}T is written as {a mathematical formula}Sa,Sr⊢tχ, where {a mathematical formula}Sa={α|(α,ma:_[_])is a node inT} and {a mathematical formula}Sr={β|(β,um:_[_]) is a node in {a mathematical formula}T}. If {a mathematical formula}T is an actual argument and χ is its claim, {a mathematical formula}T is written as {a mathematical formula}S⊢tχ, where {a mathematical formula}S={α|(α,ma:_[_]) is a node in {a mathematical formula}T}.
     </paragraph>
     <paragraph>
      Definition 8.2 gives a means of talking about arguments in the context of debate trees. The following lemma sanctions that actual arguments can be mapped to equivalent ABA arguments.
     </paragraph>
     <paragraph label="Lemma 8.2">
      Given a dialogue{a mathematical formula}δ∈D, for each actual argument{a mathematical formula}S⊢tβdrawn from the debate tree{a mathematical formula}T(δ), there exists an ABA argument{a mathematical formula}S⊢βin the ABA framework drawn from δ.
     </paragraph>
     <paragraph>
      The ABA arguments corresponding to actual arguments drawn from the debate tree drawn from the dialogue in Example 3.2 (see Fig. 4, Fig. 6) are {a mathematical formula}{a}⊢s, {a mathematical formula}{b}⊢q, and {a mathematical formula}{c}⊢c.
     </paragraph>
     <paragraph>
      For exhaustive dialogues, the other direction of Lemma 8.2 holds as well:
     </paragraph>
     <paragraph label="Lemma 8.3">
      Given an exhaustive dialogue{a mathematical formula}δ∈D, for each ABA argument{a mathematical formula}S⊢βin the ABA framework drawn from δ,{a mathematical formula}S⊢tβcan be drawn from{a mathematical formula}T(δ).
     </paragraph>
     <paragraph>
      Lemma 8.3 does not hold if a dialogue is not exhaustive, as shown next.
     </paragraph>
     <paragraph label="Example 8.2">
      Let a dialogue {a mathematical formula}δ∈D be:{a mathematical formula} The ABA framework {a mathematical formula}Fδ drawn from δ has:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Rδ={a←b,c,b←,c←b},
      </list-item>
      <list-item label="•">
       {a mathematical formula}Aδ={}.
      </list-item>
     </list>
     <paragraph>
      As in [14], we introduce the defence set and the culprits of a debate tree. We use these two concepts for our soundness result in the next sections.
     </paragraph>
     <paragraph label="Definition 8.3">
      Given a debate tree {a mathematical formula}T(δ),
     </paragraph>
     <list>
      <list-item label="•">
       the defence set{a mathematical formula}DEF(T(δ)) is the union of all assumptions α in proponent nodes of the form {a mathematical formula}N=(α,ma:P[_]), such that N is in an actual argument;
      </list-item>
      <list-item label="•">
       the culprits{a mathematical formula}CUL(T(δ)) is the set of all assumptions α in opponent nodes {a mathematical formula}N=(α,ma:O[_]) such that the child of N in {a mathematical formula}T(δ) is {a mathematical formula}N′=(_,_:P[_]) and both N and {a mathematical formula}N′ are in actual arguments.
      </list-item>
     </list>
     <section label="8.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       The debate tree drawn from the dialogue δ shown in Table 1 is {a mathematical formula}T(δ) shown in Fig. 8. Here, the defence set containing the only assumption in proponent nodes is {a mathematical formula}{boy_not_proven_guilty} and the culprits set containing the two assumptions in opponent nodes is {a mathematical formula}{w1_is_believable,w2_is_believable}.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Legal-move and outcome functions from debate trees
     </section-title>
     <paragraph>
      In this section we use debate trees to provide new, refined legal-move and outcome functions. The definition thereof requires agents to consult the current debate tree before making utterances or deciding whether the dialogue has achieved the desired outcome. In particular, when an agent decides what to utter, it needs to take the current debate tree into account and make sure that its new utterance will keep the tree fulfilling desired properties. Thus, the debate tree drawn from a dialogue can be seen as a commitment store[43] holding information that agents disclose and share using the dialogue.
     </paragraph>
     <paragraph>
      The new notions of legal-move and outcome functions will then be used, in Sections 10 and 11, to generate provably successful dialogues, in the sense of Section 6. Note that the first such notion (of patient legal-move function, see Section 9.1) is not necessary to guarantee successful dialogues, but it is intuitive and considerably simplifies the proof of results.
     </paragraph>
     <section label="9.1">
      <section-title>
       Patient legal-move functions
      </section-title>
      <paragraph>
       During dialogues, agents may in general choose to start attacking arguments while these arguments are still under construction. In patient dialogues, defined below, this is not allowed, as, in this type of dialogues, arguments are fully expanded (cf. actual) before being attacked.
      </paragraph>
      <paragraph label="Definition 9.1">
       A debate tree {a mathematical formula}T(δ) is patient iff for all nodes {a mathematical formula}N=(_,ma:_[_]) in {a mathematical formula}T(δ) such that N has a child, then N is in an actual argument drawn from {a mathematical formula}T(δ).A legal-move function {a mathematical formula}λ∈Λ is patient iff for every {a mathematical formula}δ∈D such that {a mathematical formula}T(δ) is patient, for every {a mathematical formula}u∈λ(δ), {a mathematical formula}T(δ∘u) is still patient.
      </paragraph>
      <paragraph>
       The debate tree in Fig. 4 is patient, whereas the one in the following example is not.
      </paragraph>
      <paragraph label="Example 9.1">
       Let dialogue δ be as follows:{a mathematical formula}{a mathematical formula}T(δ), given in Fig. 9, is not patient as the argument {a mathematical formula}{a},{b}⊢ts is not actual, since its node {a mathematical formula}(b,um:P[2]) has the tag um, yet the assumption node {a mathematical formula}(a,ma:P[3]) already has a child {a mathematical formula}(c,um:O[4]).
      </paragraph>
      <paragraph>
       In the remainder, dialogues are compatible with a patient legal-move function.
      </paragraph>
     </section>
     <section label="9.2">
      <section-title>
       Last-word outcome function and defensive dialogues
      </section-title>
      <paragraph label="Definition 9.2">
       We refine the notion of exhaustive outcome function guaranteeing that the (fictitious) proponent has the last-word in the dialogue, namely all leaves in the debate tree are proponent nodes or “dead-end” opponent nodes (not corresponding to any un-attacked actual arguments). We first define the notion of a node being properly attacked in a debate tree: Given a debate tree {a mathematical formula}T(δ), a node N in {a mathematical formula}T(δ) is properly attacked iff N is of the form {a mathematical formula}(_,ma:_[_]) and N has a child {a mathematical formula}N′ that is in an actual argument.
      </paragraph>
      <paragraph>
       Thus, a node is properly attacked iff it is an assumption node and there is an actual argument attacking the assumption in the node. Intuitively, this notion allows to distinguish assumptions against which actual attacks have been constructed (and thus ‘properly attacked’) from assumptions currently under attack but for which no actual attack has yet been finalised. In what we call ‘last-word’ dialogues, the debate tree is such that all its opponent arguments have an assumption node which is properly attacked:
      </paragraph>
      <paragraph label="Definition 9.3">
       A debate tree {a mathematical formula}T(δ) is last-word iff
       <list>
        for all leaf nodes N in {a mathematical formula}T(δ), N is either {a mathematical formula}(_,mr:P[_]) or {a mathematical formula}(_,ma:P[_]), andif a leaf node N is of the form {a mathematical formula}(_,_:O[_]), then eitherA
       </list>
       <paragraph>
        λ-defensive dialogue is a λ-exhaustive dialogue {a mathematical formula}δ∈D such that {a mathematical formula}ωlw(δ,λ)=true. A defensive dialogue is a λ-defensive dialogue for some {a mathematical formula}λ∈Λ.
       </paragraph>
      </paragraph>
      <paragraph>
       Intuitively, the last-word outcome function specifies a winning condition for the (fictitious) proponent: either the proponent finishes the dialogue with rules and un-attacked assumptions (condition 1), or the (fictitious) opponent does not pose any valid attacks via actual argument (condition 2a), or any valid attacks posed by the opponent has been answered with valid counter attacks (condition 2b).
      </paragraph>
      <paragraph>
       The dialogue in Example 3.2 is defensive, as the debate tree in Fig. 4 shows. The next example shows a dialogue that is not.
      </paragraph>
      <paragraph label="Example 9.2">
       The following dialogue δ{a mathematical formula} is not defensive. Indeed, the debate tree {a mathematical formula}T(δ) (see Fig. 10) is not last-word, as there are two unmarked leaf node in {a mathematical formula}T(δ): {a mathematical formula}(a,um:P[2]) and {a mathematical formula}(b,um:P[2]).
      </paragraph>
     </section>
     <section label="9.3">
      <section-title>
       Conflict-free outcome function and conflict-free dialogues
      </section-title>
      <paragraph>
       As in the case of abstract dispute trees, the defence set of a debate tree may attack itself. We refine the notion of outcome function to avoid this, as follows:
      </paragraph>
      <paragraph label="Definition 9.4">
       The conflict-free outcome function{a mathematical formula}ωcf is such that, given {a mathematical formula}δ∈D and a legal-move function λ, {a mathematical formula}ωcf(δ,λ)=true iff {a mathematical formula}ωlw(δ,λ)=true and {a mathematical formula}DEF(T(δ))∩CUL(T(δ))={}.A λ-conflict-free dialogue is a λ-defensive dialogue {a mathematical formula}δ∈D such that {a mathematical formula}ωcf(δ,λ)=true. A conflict-free dialogue is a λ-conflict-free dialogue for some {a mathematical formula}λ∈Λ.
      </paragraph>
      <paragraph label="Lemma 9.1">
       Let δ be a conflict-free dialogue and let{a mathematical formula}Fδbe the ABA framework drawn from δ. Then,{a mathematical formula}DEF(T(δ))does not attack itself in{a mathematical formula}Fδ.
      </paragraph>
     </section>
     <section label="9.4">
      <section-title>
       Filtered legal-move functions
      </section-title>
      <paragraph>
       Another legal-move function that relies on the debate tree as a commitment store is the filtered legal-move function, defined in terms of filtered debate trees. These are trees where the same assumptions are not attacked repeatedly, unnecessarily. Instead, in a filtered debate tree, if an assumption has already been marked, then it does not need to be “dealt with” again. Formally:
      </paragraph>
      <paragraph label="Definition 9.5">
       A debate tree {a mathematical formula}T(δ) is filtered iff for any two nodes {a mathematical formula}T(δ): {a mathematical formula}N1=(β,ma:L[id1]), {a mathematical formula}N2=(β,ma:L[id2]), {a mathematical formula}L∈{P,O}, {a mathematical formula}N1≠N2, if {a mathematical formula}N1 has a child {a mathematical formula}N1′ in an actual argument {a mathematical formula}T1 and {a mathematical formula}N2 has a child {a mathematical formula}N2′ in an actual argument {a mathematical formula}T2, then {a mathematical formula}T1≠T2.{sup:8} A legal-move function {a mathematical formula}λ∈Λ is filtered iff for every {a mathematical formula}δ∈D such that {a mathematical formula}T(δ) is filtered, for every {a mathematical formula}u∈λ(δ), {a mathematical formula}T(δ∘u) is still filtered.
      </paragraph>
      <paragraph label="Example 9.3">
       The following dialogue (from which the debate tree in Fig. 11 (left) is drawn) is compatible with a filtered legal-move function:{a mathematical formula} Here the argument {a mathematical formula}{a}⊢a is attacked by {a mathematical formula}{b}⊢b once and only once, and, in the filtered debate tree (Fig. 11 left), since the node {a mathematical formula}(a,ma:P[2]) has a child {a mathematical formula}(b,ma:O[4]), the node {a mathematical formula}(a,ma:P[6]) cannot be attacked by the same argument {a mathematical formula}{b}⊢b, hence {a mathematical formula}(b,um:O[7]) is an unmarked node, rather than a marked assumption node. Instead, the dialogue below{a mathematical formula} (from which the debate tree in Fig. 11 (right) is drawn) is not compatible with a filtered legal-move function. Here, the argument {a mathematical formula}{a}⊢a is attacked by {a mathematical formula}{b}⊢b twice.
      </paragraph>
      <paragraph>
       Thus, filtered legal-move functions bring efficiency to dialogues, as, in dialogues that are compatible with a filtered legal-move function, any assumption is attacked at most once by the same argument.
      </paragraph>
     </section>
     <section label="9.5">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       The debate tree {a mathematical formula}T(δ) given in Fig. 8 is patient and filtered. Hence, δ in Table 1 is compatible with a patient and filtered (as well as flat and related) legal-move function λ. The two leaf nodes in Fig. 8 are:{a mathematical formula} both are proponent nodes with marked rules, hence of the form {a mathematical formula}(_,mr:P[_]). By Definition 9.3, {a mathematical formula}T(δ) is last-word and {a mathematical formula}ωlw(δ,λ)=true. Moreover, {a mathematical formula}DEF(T(δ))={boy_not_proven_guilty} and {a mathematical formula}CUL(T(δ))={w1_is_believable,w2_is_believable}. Thus, by Definition 9.4, {a mathematical formula}ωcf(δ,λ)=true and δ is λ-conflict-free.
      </paragraph>
      <paragraph>
       Overall, in this section we have introduced the basic ingredients to formally link dialogues with argumentation semantics and show how successful dialogues can be constructed. In the next sections, we will do so for different categories of dialogues, that vary in how broadly or narrowly they debate the given claim.
      </paragraph>
     </section>
    </section>
    <section label="10">
     <section-title>
      Focused dialogues
     </section-title>
     <paragraph>
      In this section we link dialogues and argumentation semantics for dialogues that focus on constructing a single abstract dispute tree for the claim, where the (fictitious) proponent only needs to build single (supporting and defending) arguments, whereas the (fictitious) opponent may build several (attacking) arguments.
     </paragraph>
     <paragraph label="Definition 10.1">
      A debate tree {a mathematical formula}T(δ) is focused iff
      <list>
       for all arguments A drawn from {a mathematical formula}T(δ), if A contains a node {a mathematical formula}(_,ma:O[_]), then there is at most one node N of the form {a mathematical formula}(_,ma:O[_]) in A such that N has any child, and such node N has a single child;for all nodes of the form {a mathematical formula}(β0,mr:P[t]) with children {a mathematical formula}(β1,_:P[_]), …, {a mathematical formula}(βn,_:P[_]) there must be an utterance in δ of the form{a mathematical formula}A legal-move function
      </list>
      <paragraph>
       {a mathematical formula}λ∈Λ is focused iff for every {a mathematical formula}δ∈D such that {a mathematical formula}T(δ) is focused, for every {a mathematical formula}u∈λ(δ), {a mathematical formula}T(δ∘u) is still focused. A focused dialogue is a dialogue compatible with a focused legal-move function.
      </paragraph>
     </paragraph>
     <paragraph>
      In focused trees, no alternative ways to support or defend the claim are considered simultaneously, e.g. an opponent argument is only attacked by a single proponent argument, whereas a proponent argument can be attacked in as many ways as the number of its assumptions and ways to prove their contraries. Moreover, the claim is supported by a single proponent argument. The tree in Fig. 4 is focused. Fig. 12, Fig. 13 show two non-focused debate trees drawn from the dialogues in Table 3, Table 4, respectively, and violating condition 1 and 2 in Definition 10.1, respectively. In these (unfocused) dialogues the agents stick to the original claim but they shift the way they carry out the debate. For example, in the dialogue in Table 3 two different ways to defeat an opponent argument are explored concurrently (by building arguments against a and b), although one suffices to determine acceptability of the claim.
     </paragraph>
     <paragraph>
      λ-defensive dialogues for λ focused give debate trees corresponding to abstract dispute trees[14] with the same defence set and culprits. Formally:
     </paragraph>
     <paragraph label="Lemma 10.1">
      Given a λ-defensive dialogue{a mathematical formula}δ∈Dfor χ, for λ-focused, let{a mathematical formula}T(δ)be the debate tree drawn from δ and{a mathematical formula}Fδ=〈L,Rδ,Aδ,Cδ〉be the ABA framework drawn from δ. Then there is an abstract dispute tree{a mathematical formula}Tafor{a mathematical formula}S⊢χfor some{a mathematical formula}S⊆Aδ, such that{a mathematical formula}DEF(T(δ))=DEF(Ta)and{a mathematical formula}CUL(T(δ))=CUL(Ta).
     </paragraph>
     <paragraph>
      Lemma 10.1 shows the connection between the debate trees drawn from λ-defensive for λ-related and focused dialogues and abstract dispute trees. An analogous result can be obtained for λ-defensive and filtered dialogues. Indeed, since filtered legal-move functions perform a form of “filtering” resulting in pruned trees, the result relies upon inserting nodes that have been filtered back into the debate tree, resulting in expanded debate trees, defined as follows:
     </paragraph>
     <paragraph label="Definition 10.2">
      Given a debate tree {a mathematical formula}T(δ) where δ is λ-defensive for λ-focused, we construct a (possibly infinite) sequence {a mathematical formula}T0E,…,TnE,… of trees as follows:
      <list>
       Delete all nodes N from {a mathematical formula}T(δ) where N is in a potential argument. Let {a mathematical formula}T′(δ) be the result.{a mathematical formula}T0E=T′(δ).Suppose {a mathematical formula}TiE, for {a mathematical formula}i≥0, has been constructed; then {a mathematical formula}Ti+1E is obtained by adding arguments {a mathematical formula}T1,…,Tk simultaneously to leaf nodes {a mathematical formula}N1,…,Nk of {a mathematical formula}TiE, as children, respectively, where {a mathematical formula}Tj and {a mathematical formula}Nj, {a mathematical formula}1≤j≤k are such that:The
      </list>
      <paragraph>
       expanded debate tree{a mathematical formula}TE(δ) of {a mathematical formula}T(δ) is the limit{sup:9} of this sequence.
      </paragraph>
     </paragraph>
     <paragraph>
      Note that {a mathematical formula}TE(δ) of {a mathematical formula}T(δ) is the last element of this sequence, if the sequence is finite (when no leaf node is an assumption node).
     </paragraph>
     <paragraph label="Example 10.1">
      We illustrate the notion of expanded debate tree with the debate tree in Fig. 14 for the dialogue in Example 6.3. Here, filtering has been applied to both: {a mathematical formula}(b,um:O[11]) and {a mathematical formula}(a,um:O[12]). Hence, there is no repeated attack against these two assumptions. The expanded debate tree is shown in Fig. 15.
     </paragraph>
     <paragraph label="Lemma 10.2">
      Given a λ-defensive dialogue δ for χ, for λ-focused and filtered, let{a mathematical formula}T(δ)be the debate tree drawn from δ. There is an abstract dispute tree{a mathematical formula}Tafor{a mathematical formula}S⊢χfor some S, such that{a mathematical formula}DEF(T(δ))=DEF(Ta)and{a mathematical formula}CUL(T(δ))=CUL(Ta).
     </paragraph>
     <paragraph>
      In order to guarantee that dialogues are (g-/a-/i-)successful, we restrict them to be conflict-free (as given in Definition 9.4):
     </paragraph>
     <paragraph label="Theorem 10.1">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈D, if δ is λ-conflict-free for λ-focused, then δ is g-successful and χ is grounded in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δ))).
     </paragraph>
     <paragraph>
      Theorem 10.1 gives a “recipe” for generating a- and i-successful dialogues, by virtue of Proposition 6.1. The following Theorem 10.2, Theorem 10.3 characterise a larger class of dialogues that can be proven to be a- and i-successful, respectively.
     </paragraph>
     <paragraph label="Theorem 10.2">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈D, if δ is λ-conflict-free for λ-focused and filtered, then δ is a-successful and χ is admissible in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δ))).
     </paragraph>
     <paragraph label="Definition 10.3">
      A debate tree {a mathematical formula}T(δ) is ideal iff none of the opponent arguments drawn from {a mathematical formula}T(δ) belongs to an admissible set of arguments in the ABA framework {a mathematical formula}Fδ drawn from δ.The ideal outcome function{a mathematical formula}ωi is such that, given {a mathematical formula}δ∈D and {a mathematical formula}λ∈Λ, {a mathematical formula}ωi(δ,λ)=true iff {a mathematical formula}ωcf(δ,λ)=true and {a mathematical formula}T(δ) is ideal.A λ-ideal dialogue is a λ-conflict-free dialogue {a mathematical formula}δ∈D such that {a mathematical formula}ωi(δ,λ)=true. An ideal dialogue is a λ-ideal dialogue for some {a mathematical formula}λ∈Λ.
     </paragraph>
     <paragraph label="Theorem 10.3">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈D, if δ is λ-ideal for λ-focused and filtered, then δ is i-successful and χ is ideal in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δ))).
     </paragraph>
     <section label="10.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       The debate tree {a mathematical formula}T(δ) given in Fig. 8 is focused. Hence, δ in Table 1 is focused. Then, by Theorem 10.2, Theorem 10.1 and Proposition 6.1, δ is a-/g-/i-successful, as we noted in Section 6.1. The techniques presented in this section give a more constructive way to guarantee success.
      </paragraph>
     </section>
    </section>
    <section label="11">
     <section-title>
      Debate forests and unrestricted dialogues
     </section-title>
     <paragraph>
      Focused dialogues are restricted, in that they force a single way of supporting or defending claims. Instead, in realistic dialogues (of various types) shifts inter- and intra-topic are likely to occur. In this section we consider unrestricted dialogues, that may not be focused by allowing multiple ways of supporting or defending claims (while sticking however to the initial claim). These may be useful to support brain storming and explore different alternative ways to determine acceptability of claims. We will show that analogous versions of Theorem 10.1, Theorem 10.2, Theorem 10.3 hold for such unrestricted dialogues, that thus can be still be used to determine acceptability of claims.
     </paragraph>
     <paragraph label="Example 11.1">
      The following dialogue δ{a mathematical formula} is not focused as both utterances {a mathematical formula}〈a2,a1,1,rl(s←p),2〉 and {a mathematical formula}〈a1,a2,1,rl(s←q),3〉 expand s. The (non-focused) debate tree {a mathematical formula}T(δ) is shown in Fig. 16. Nonetheless, δ is a- and g-successful, as s is admissible and grounded in the framework {a mathematical formula}Fδ drawn from δ, since there is an argument {a mathematical formula}{b}⊢s but no attack against b in {a mathematical formula}Fδ.
     </paragraph>
     <paragraph>
      To study the acceptability of claims in unrestricted dialogues, we first introduce the notion of arguments being attacked as follows.
     </paragraph>
     <paragraph label="Definition 11.1">
      Given a debate tree {a mathematical formula}T and an argument A drawn from {a mathematical formula}T, A is attacked in {a mathematical formula}T iff there is a node {a mathematical formula}N=(_,ma:_[_]) in A such that N has a child node m in {a mathematical formula}T. We say that the sub-tree rooted at m in {a mathematical formula}T is an attacker of A in {a mathematical formula}T.
     </paragraph>
     <paragraph label="Example 11.2">
      Consider the dialogue δ{a mathematical formula} The debate tree drawn from this dialogue is in Fig. 17. Here, the argument {a mathematical formula}{s}⊢ts is attacked; and the attacker of {a mathematical formula}{s}⊢ts is shown in Fig. 18 (right).
     </paragraph>
     <paragraph>
      The notion of attacked differs from the notion of properly attacked given in Definition 9.2 in two ways:
     </paragraph>
     <list>
      <list-item label="•">
       Definition 11.1 defines attacked with respect to an argument, or a sub-tree, of a debate tree, whereas Definition 9.2 defines properly attacked with respect to a single (assumption) node in a debate tree;
      </list-item>
      <list-item label="•">
       Definition 11.1 states that an argument is attacked as long as there are some nodes in the debate tree that are children of the argument, whereas Definition 9.2 defines an assumption node being properly attacked iff there is an actual argument that hangs from that node.
      </list-item>
     </list>
     <paragraph>
      Debate trees are insufficient to help determine the acceptability of claims of non-focused dialogues. We introduce the notion of debate forest, composed of (debate) trees and defined in terms of the notions of attacked and attacker just given.
     </paragraph>
     <paragraph label="Definition 11.2">
      Given a dialogue {a mathematical formula}Dajai(χ)=δ=〈u1,…,un〉, the debate forest{a mathematical formula}F(δ) drawn from δ is the set of trees {a mathematical formula}Fm(δ) in the sequence {a mathematical formula}F0(δ),F1(δ),…,Fm(δ) constructed inductively from the π-pruned sequence {a mathematical formula}δ′=〈u1′…,um′〉 obtained from δ, as follows (below, {a mathematical formula}L,L′∈{P,O}, {a mathematical formula}L≠L′):
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}F0(δ) is empty;
      </list-item>
      <list-item label="2.">
       {a mathematical formula}F1(δ) consists of a single debate tree {a mathematical formula}T11(δ), which consists of a single node {a mathematical formula}(χ,um:P[id1]), where {a mathematical formula}id1 is the identifier of {a mathematical formula}u1=u1′;
      </list-item>
      <list-item label="3.">
       Let {a mathematical formula}Fi(δ) be the i-th forest consisting of trees {a mathematical formula}T1i(δ),…,Tli(δ), let {a mathematical formula}ui+1′=〈_,_,t,C,id〉, and let {a mathematical formula}ut′=〈_,_,_,Ct,t〉 be the target utterance of {a mathematical formula}ui+1′; then {a mathematical formula}Fi+1(δ) is obtained as follows.
      </list-item>
     </list>
     <paragraph>
      The construction of the debate forest drawn from the dialogue in Example 11.1 is shown in Fig. 19, Fig. 20, Fig. 21.
     </paragraph>
     <paragraph>
      Conceptually, we construct debate forests using the same procedure for constructing debate trees, i.e. inserting new nodes and locating parents, etc. However, since the main purpose of having a debate forest is to ensure that every individual debate tree in the forest is focused, if we encounter a new utterance u such that adding u will yield a non-focused debate tree (as in cases 3(a)ii and 3(c)ii), we (I) duplicate all existing trees in the forest that contain the target of u, (II) remove all sub-trees of the target of u from the duplications, and (III) “add u” to the duplicated trees. Note that cases 3(a)i, 3(b), and 3(c)i describe “normal” cases where adding u to the forest will not yield non-focused debate trees.
     </paragraph>
     <paragraph>
      In this process, it is possible that more trees are duplicated than needed but the forest is a set, so only a single version of identical trees is kept. Hence, at the end, we obtain a set of unique trees in a debate forest.
     </paragraph>
     <paragraph>
      Note that each such tree in the debate forest drawn from a dialogue is a top-portion of the dialogue tree drawn from the dialogue.
     </paragraph>
     <paragraph label="Definition 11.3">
      In order to study semantic properties of debate forests, we introduce the concept of sub-dialogues. Given a dialogue {a mathematical formula}Dajai(χ)=δ, {a mathematical formula}δ′ is a sub-dialogue of δ iff it is a dialogue for χ between {a mathematical formula}ai and {a mathematical formula}aj and, for all utterances u in {a mathematical formula}δ′, u is in δ. We say that δ is the full-dialogue of {a mathematical formula}δ′.
     </paragraph>
     <paragraph label="Example 11.3">
      Two sub-dialogues of the dialogue in Example 11.1 are in Table 5, Table 6. The first sub-dialogue (in Table 5) is neither a- nor g-successful as the proponent fails to defend a, an assumption in the argument {a mathematical formula}{a}⊢s. The second sub-dialogue (in Table 6) is both a- and g-successful as the proponent is able to construct the argument {a mathematical formula}{b}⊢s and defend it (since b is not attacked).
     </paragraph>
     <paragraph>
      Note that both example sub-dialogues in Example 11.3 are exhaustive, however Definition 11.3 does not impose that sub-dialogues are exhaustive.
     </paragraph>
     <paragraph>
      Sub-dialogues can be used to prove properties of unrestricted dialogues in that, intuitively, each unrestricted (but exhaustive) dialogue can be understood as the collection of several independent focused sub-dialogues. Hence, each sub-dialogue draws a tree in the debate forest drawn from the full (unrestricted) dialogue. Thus, as soon as one debate tree is found to be “good”, then the particular sub-dialogue drawing the debate tree becomes successful, and the full non-focused dialogue is successful.
     </paragraph>
     <paragraph label="Lemma 11.1">
      Given a debate forest{a mathematical formula}F(δ)drawn from a dialogue δ, each tree in{a mathematical formula}F(δ)is a debate tree drawn from a focused sub-dialogue{a mathematical formula}δiof δ.
     </paragraph>
     <paragraph>
      For example, the two debate trees {a mathematical formula}T111(δ) and {a mathematical formula}T211(δ) in Fig. 20, Fig. 21 are drawn from the sub-dialogues in Table 5, Table 6, respectively.
     </paragraph>
     <paragraph>
      Note that, in the case of unrestricted dialogues, the notion of filtered legal-move functions is overly strong, in that it imposes filtering across trees in the forest, thus ruling out successful dialogues unnecessarily. In order to prove semantic properties for a wider class of unrestricted dialogues, we relax the definition of filtered legal-move functions by redefining it with respect to debate forests:
     </paragraph>
     <paragraph label="Definition 11.4">
      A debate forest {a mathematical formula}F(δ) is filtered iff all debate trees in {a mathematical formula}F(δ) are filtered. A legal-move function {a mathematical formula}λ∈Λ is filtered iff for every {a mathematical formula}δ∈D such that {a mathematical formula}F(δ) is filtered, for every {a mathematical formula}u∈λ(δ), {a mathematical formula}F(δ∘u) is still filtered.
     </paragraph>
     <paragraph>
      This notion of legal-move function is a generalised version of the notion in Definition 9.5, since a debate tree is a special case of a debate forest that consists of a single tree. From now on we will assume that filtered dialogues are dialogues compatible with this generalised notion of filtered legal-move function.
     </paragraph>
     <paragraph>
      Similarly, patient legal-move functions can be redefined with respect to debate forests as follows. (Again, we assume that dialogues in later discussion are compatible with the following generalised notion of patient legal-move function.)
     </paragraph>
     <paragraph label="Definition 11.5">
      A debate forest {a mathematical formula}F(δ) is patient iff all debate trees in {a mathematical formula}F(δ) are patient debate trees. A legal-move function {a mathematical formula}λ∈Λ is patient iff for every {a mathematical formula}δ∈D such that {a mathematical formula}F(δ) is patient, for every {a mathematical formula}u∈λ(δ), {a mathematical formula}F(δ∘u) is still patient.
     </paragraph>
     <paragraph>
      We can obtain similar results as for focused dialogues, by using the same combinations of legal move-functions and outcome functions, as follows.
     </paragraph>
     <paragraph label="Theorem 11.1">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈Dsuch that δ is λ-exhaustive, if there is a debate tree{a mathematical formula}T(δi)drawn from a sub-dialogue{a mathematical formula}δiof δ such that{a mathematical formula}δiis λ-conflict-free, then δ is g-successful and χ is grounded in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δi))).
     </paragraph>
     <paragraph label="Theorem 11.2">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈Dsuch that δ is λ-exhaustive for λ filtered, if there is a debate tree{a mathematical formula}T(δi)drawn from a sub-dialogue{a mathematical formula}δiof δ such that{a mathematical formula}δiis λ-conflict-free, then δ is a-successful and χ is admissible in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δi))).
     </paragraph>
     <paragraph>
      Theorem 11.1, Theorem 11.2 do not refer to debate forests drawn from dialogues directly, rather, they specify conditions of sub-dialogues thereof. This is partly because {a mathematical formula}ωcf is defined with respect to properties of debate trees rather than debate forest (see Definition 9.4). Though we could overwrite Definition 9.4 and redefine it with respect to debate forests, we choose not to as the current version of Theorem 11.1, Theorem 11.2 clearly indicates that testing the acceptability of the claim of an unrestricted dialogue can be reduced to testing the acceptability of the claim of sub-dialogues that draw debate trees and exhibit desirable properties.
     </paragraph>
     <paragraph>
      To lift the results for the ideal semantics to unrestricted dialogues, we modify the notion of ideal outcome function so that it focuses on a sub-dialogue but uses the ABA framework drawn from the full dialogue to check opponent nodes:
     </paragraph>
     <paragraph label="Definition 11.6">
      Let {a mathematical formula}δ∈D, {a mathematical formula}F(δ) be the debate forest drawn from δ and {a mathematical formula}δi be a sub-dialogue of δ. {a mathematical formula}T(δi) in {a mathematical formula}F(δ) is ideal with respect to δ iff none of the opponent arguments drawn from {a mathematical formula}T(δi) belongs to an admissible set of arguments in the ABA framework {a mathematical formula}Fδ drawn from δ. The ideal outcome function{a mathematical formula}ωi is such that, given {a mathematical formula}δ∈D and {a mathematical formula}λ∈Λ, {a mathematical formula}ωi(δ,λ)=true iff there exists a sub-dialogue {a mathematical formula}δi of δ such that {a mathematical formula}ωcf(δi,λ)=true and {a mathematical formula}T(δi) is ideal with respect to δ. A λ-ideal dialogue is a dialogue {a mathematical formula}δ∈D such that {a mathematical formula}ωi(δ,λ)=true.
     </paragraph>
     <paragraph>
      The following example illustrates the computational advantages of this definition in the case of unrestricted dialogues.
     </paragraph>
     <paragraph label="Example 11.4">
      Given the dialogue δ:{a mathematical formula} the forest {a mathematical formula}F(δ) drawn from δ is shown in Fig. 22, where {a mathematical formula}δ1 and {a mathematical formula}δ2 are the two sub-dialogues that draw the individual debate trees. We can see that {a mathematical formula}δ1 is ideal in {a mathematical formula}F(δ) as the opponent argument, {a mathematical formula}{q}⊢q, drawn from {a mathematical formula}T(δ1), is not in an admissible set in {a mathematical formula}Fδ, even though {a mathematical formula}δ2 is not “complete” yet as {a mathematical formula}〈_,_,9,ctr(a,q),10〉 can still be uttered. Such “early termination” is possible because of the redefined ideal outcome function.
     </paragraph>
     <paragraph label="Theorem 11.3">
      Given a dialogue{a mathematical formula}Dajai(χ)=δ∈D, if δ is λ-ideal for λ-focused and filtered, then δ is i-successful and χ is ideal in the ABA framework{a mathematical formula}Fδdrawn from δ (supported by{a mathematical formula}DEF(T(δ))).
     </paragraph>
     <section label="11.1">
      <section-title>
       Illustration: twelve angry men
      </section-title>
      <paragraph>
       We modify the dialogue shown in Table 1/Table 2 to illustrate non-focused dialogues. In Table 2, after {a mathematical formula}a1 making the utterance: Witness 2 cannot be believed if it has a poor eyesight.{a mathematical formula}a1 makes another utterance: Witness 2 cannot be believed if it has a conflict of interest. Correspondingly, in Table 1, after the utterance{a mathematical formula} another utterance{a mathematical formula} is added to the dialogue. (Utterances with ID 14, 15 and 16 in the original dialogue are then given with ID 15, 16 and 17, respectively.) This modified dialogue is not focused, as the new utterance leads to another way of supporting {a mathematical formula}w2_not_believable, which defends the claim boy_innocent.
      </paragraph>
      <paragraph>
       The resulting debate forest contains two debate trees: {a mathematical formula}T1(δ) and {a mathematical formula}T2(δ). {a mathematical formula}T1(δ) is the debate tree shown in Fig. 8. {a mathematical formula}T2(δ) is {a mathematical formula}T1(δ) with node{a mathematical formula} replaced by{a mathematical formula}
      </paragraph>
     </section>
    </section>
    <section label="12">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Several proposals for argumentation based dialogues exist in the literature. We briefly review here those that are most closely related to our work.
     </paragraph>
     <paragraph>
      McBurney and Parsons [27] give an overview of dialogue games for argumentation relaying upon syntax and semantics of dialogue protocols. Our work can be seen as providing a novel dialogue game for ABA, hence the syntax of our dialogue is based on ABA and the semantics of our dialogues are standard ABA semantics. These argumentation semantics can be used to define specialised semantics for specific dialogue types (such as persuasion and inquiry [43]), e.g. following the lines of [17], [18], [19], [20].
     </paragraph>
     <paragraph>
      Black and Hunter [6] present a formal system for inquiry dialogues based on DeLP [22] as the underlying argumentation framework. Our work differs from theirs as (1) it defines a mechanism for any type of dialogue whereas they focus on inquiry dialogues; (2) it uses ABA whereas they use DeLP; (3) it does not force an agent to disclose all knowledge whereas they force full disclosure of all relevant knowledge for the purpose of inquiry; (4) it does not force a strict interleaving whereas they do. In addition to being more general, our model benefits from using ABA as it makes use of formal soundness results thereof to prove soundness of dialogues. Moreover, since abstract argumentation is an instance of ABA, our model also provides a model for abstract argumentation dialogues too.
     </paragraph>
     <paragraph>
      Parsons et al. [29] examine three notions of relevance in dialogues where utterances are arguments and attacks:
     </paragraph>
     <list>
      <list-item label="•">
       R1 (every new utterance has a direct impact on the claim),
      </list-item>
      <list-item label="•">
       R2 (every new utterance directly or indirectly impacts the claim), and
      </list-item>
      <list-item label="•">
       R3 (every new utterance has a direct impact on the previous one).
      </list-item>
     </list>
     <paragraph>
      Our patient legal-move function and focused legal-move function jointly resemble their R1 related-ness. Our related legal-move function has some of the features of their R2 related-ness in that all related utterances have impact on the claim. However, our utterances are at a finer granularity level, as they correspond to rules, assumptions, and contraries, whereas in [29] utterances are at the argument level, i.e., each utterance contains an argument. Thus, there is no direct mapping between our work and their relevance.
     </paragraph>
     <paragraph>
      Prakken [32] defines a formal system for persuasion. The main differences with our work are: (1) since that work focuses on persuasion dialogues, proponent and opponent roles are pre-assigned to agents before the dialogue whereas in our work agents can play both roles within the same dialogue; (2) Prakken focuses on the grounded semantics, whereas we allow admissibility, grounded, and ideal semantics; (3) his set of utterances refers to arguments and attacks, as in the case of [29]; (4) he forces the support of arguments to be minimal, whereas we do not, in the spirit of [13]; (5) he does not allow agents to jointly construct arguments whereas we do. Roughly speaking, in terms of obtaining the soundness result, i.e., a “successful” dialogue means that the claim of the dialogue is “acceptable”, there are two main differences between his approach and ours. Firstly, we rely on mapping our dialogues to abstract dispute trees whereas he uses a form of labelling. Hence, in our case, “successful” dialogues can be mapped to “good” abstract dispute trees; whereas, in Prakken's case, “successful” dialogues have winning arguments that are labelled in. Secondly, to support non-focused dialogues, we use debate forests, and show that individual trees in a forest can be mapped to abstract dispute trees, whereas Prakken puts all arguments into a single tree and then identifies a “winning strategy” that represents a sub part of the single tree. Overall, our definitions allow to leverage on formal results for ABA (and in particular the connection between abstract dispute trees in ABA and our debate trees and forests) to formally prove soundness of our dialogue model with respect to a range of argumentation semantics. It is not clear whether and how this could be done in the case of Prakken's trees, as the labels already carry a semantic connotation and are intrinsically linked to a specific argumentation semantics.
     </paragraph>
     <paragraph>
      Thang et al. [39] propose a dialogue system for persuasion. Similar to Prakken's work, they pre-assign the roles of proponent and opponent to agents participating in a dialogue. Moreover, they use an annotation scheme similar to Prakken's IN/OUT labelling to compute the acceptability of the dialogue. Unlike Prakken's work, they have used ABA as their underlying representation and define an ABA-based dialogue system. Yet, unlike our generic framework composed of various components (legal-move functions and outcome functions), their work has a limited focus on persuasion. They point out computational inefficiency of our notion of exhaustive dialogue, also present in our earlier work [16], as some utterances might be repeated in exhaustive dialogues without adding information to the ABA framework drawn from these dialogues. We believe that this potential loss of efficiency is a small price to pay if enforcing exhaustiveness helps to define appropriate legal-move and outcome functions to establish the correspondence between debate trees and abstract dispute trees and formally prove soundness. Moreover, the potential inefficiency can be mitigated in implementations of our dialogues, where such utterances can be brought about automatically.
     </paragraph>
     <paragraph>
      Prakken et al. [35] introduce an argumentation dialogue game for analysing IT security risk assessment, with {a mathematical formula}ASPIC+[34] as the underlying argumentation framework, under the grounded semantics. As [32], this work pre-assigns the roles of proponent and opponent to the two participating agents and uses a version of the IN/OUT labelling to compute acceptability. Instead of using explicitly defined structures such as our legal-move functions, this work relies on a single notion of legal dialogue which, not unlike our outcome functions, serves the purpose of validating the dialogue by checking that it exhibits desirable properties.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Glossary
     </section-title>
     <list>
      <list-item label="•">
       Utterance (Definition 3.1) is the basic building block in our dialogue model.
      </list-item>
      <list-item label="•">
       Dialogue (Definition 3.2) is a sequence of utterances.
      </list-item>
      <list-item label="•">
       Framework drawn from a Dialogue (Definition 3.3) contains all rules, assumptions and contraries disclosed in a dialogue.
      </list-item>
      <list-item label="•">
       Turn-making Function (Definition 4.1) decides the agent making the next utterance.
      </list-item>
      <list-item label="•">
       Legal-move Function (Definition 4.2) specifies how to continue a dialogue.
      </list-item>
      <list-item label="•">
       Outcome Function (Definition 4.3) allows to determine whether dialogues have desirable properties.
      </list-item>
      <list-item label="•">
       Flat Legal-move Function (Definition 5.1) and ABA outcome function (Definition 5.2) ensure that the framework drawn from a dialogue is a flat ABA framework.
      </list-item>
      <list-item label="•">
       A-/G-/I-successful Dialogues (Definition 6.1) are dialogues with their claims being admissible, grounded, and ideal, respectively, in the ABA frameworks drawn from them.
      </list-item>
      <list-item label="•">
       Related Utterances (Definition 7.1) are “syntactically” related utterances.
      </list-item>
      <list-item label="•">
       Top–down Related Utterances (Definition 7.2) are “semantically” related utterances.
      </list-item>
      <list-item label="•">
       Top–down Related Legal-move Function (Definition 7.3) ensures “semantically” related relations between utterances.
      </list-item>
      <list-item label="•">
       Exhaustive Outcome Function (Definition 7.4) ensures that all utterances compatible with the used legal-move functions are utteranced in the dialogue.
      </list-item>
      <list-item label="•">
       Debate Tree drawn from Dialogue (Definition 8.1) keeps track of dialogue progress, for book-keeping purpose.
      </list-item>
      <list-item label="•">
       Argument drawn from a Debate Tree (Definition 8.2) defines how to extracts ABA arguments from debate trees.
      </list-item>
      <list-item label="•">
       Defence Set and Culprits (Definition 8.3) are proponent and attacked opponent assumptions from a debate tree.
      </list-item>
      <list-item label="•">
       In Patient Debate Trees (Definition 9.1) arguments are not attacked until fully constructed.
      </list-item>
      <list-item label="•">
       Patient Legal-move Function (Definition 9.1) constructs dialogues drawing patient debate trees.
      </list-item>
      <list-item label="•">
       In Last-word Debate Tree (Definition 9.3) all leaves are proponent nodes.
      </list-item>
      <list-item label="•">
       Defensive Dialogues (Definition 9.3) draw last-word debate trees.
      </list-item>
      <list-item label="•">
       Conflict-free Outcome Function (Definition 9.4) enforces that there is no overlap between defence set and culprits.
      </list-item>
      <list-item label="•">
       Conflict-free Dialogues (Definition 9.4) are defensive dialogues for which the conflict-free outcome function returns true.
      </list-item>
      <list-item label="•">
       In Filtered Debate Trees (Definition 9.5) there is no repeated attack between arguments. In Filtered Debate Forests (Definition 11.4) all debate trees are filtered.
      </list-item>
      <list-item label="•">
       Filtered Legal-move Functions (Definition 9.5, Definition 11.4) construct dialogue drawing filtered debate trees/forests.
      </list-item>
      <list-item label="•">
       Properly Attacked Node (Definition 9.2) is an assumption node which has been attacked by some actual argument.
      </list-item>
      <list-item label="•">
       Focused Debate Trees (Definition 10.1) contain a single way of defending their root.
      </list-item>
      <list-item label="•">
       Focused Legal-move Function (Definition 10.1) constructs dialogues drawing focused debate trees.
      </list-item>
      <list-item label="•">
       Ideal Debate Tree (Definition 10.3) has the property that none of the opponent arguments drawn from the tree is admissible.
      </list-item>
      <list-item label="•">
       Ideal Outcome Function (Definition 10.3, Definition 11.6) returns true iff the debate tree/forest drawn from a dialogue is ideal.
      </list-item>
      <list-item label="•">
       Ideal Dialogue (Definition 10.3, Definition 11.6) is a conflict-free dialogue for which the ideal outcome function returns true.
      </list-item>
      <list-item label="•">
       Attacked Argument (Definition 11.1) is an argument n a debate tree with an assumption node that has a child.
      </list-item>
      <list-item label="•">
       Debate Forest (Definition 11.2) is a set of debate trees.
      </list-item>
      <list-item label="•">
       Sub-dialogue (Definition 11.3) is a set of utterances extracted from a dialogue.
      </list-item>
      <list-item label="•">
       Patient Debate Forest (Definition 11.5) is a debate forest containing only patient debate trees.
      </list-item>
      <list-item label="•">
       Ideal Debate Forest (Definition 11.6) a debate is forest containing only ideal debate trees.
      </list-item>
     </list>
    </section>
    <section label="Appendix B">
     <section-title>
      Proofs
     </section-title>
     <paragraph label="Proof of Lemma 5.1">
      By Definition 5.1, for any {a mathematical formula}β∈L, if {a mathematical formula}β∈Aδ then there exists no ρ, such that {a mathematical formula}ρ∈Rδ and {a mathematical formula}Head(ρ)=β; and if there exists ρ, such that {a mathematical formula}ρ∈Rδ then {a mathematical formula}β∉Aδ. Therefore, {a mathematical formula}Fδ is flat.  □
     </paragraph>
     <paragraph label="Proof of Lemma 5.2">
      Trivial.  □
     </paragraph>
     <paragraph label="Proof of Proposition 6.1">
      Since δ is g-successful, χ is grounded. By definition of grounded semantics (see Section 2), χ is also complete and admissible. Hence g-successful implies a-successful. By Theorem 2.1 (iii) of [15], which states that an ideal set of arguments is a superset of the grounded set of arguments, we have that g-successful implies i-successful.  □
     </paragraph>
     <paragraph label="Proof of Proposition 6.2">
      Trivial by definition of ideal semantics (see Section 2).  □
     </paragraph>
     <paragraph label="Proof of Lemma 8.1">
      It is easy to see that debate trees for related dialogues are always guaranteed to be well-formed, in that each non-root node in them has exactly one parent. We show, given a dialogue δ, that this inductive process constructs a debate tree {a mathematical formula}T(δ) as in Definition 8.1.Condition 1(a) and 1(b) in Definition 8.1 are trivially true since nodes in {a mathematical formula}T0(δ),…,Tm(δ) are nodes inserted in accordance with utterances in δ hence, if a sentence β is in a node, then β must be in some utterance in the dialogue. Condition 1(c) in Definition 8.1 is true as 3(a) and 3(b) in the lemma specify how nodes tagged um are replaced by nodes tagged ma and mr. Condition 2(a) through 2(f) in Definition 8.1 are jointly met by 3(a) through 3(c) in the lemma.Hence, this inductive process yields a debate tree as per Definition 8.1.  □
     </paragraph>
     <paragraph label="Proof of Lemma 8.2">
      This lemma is trivially true as a node in an actual argument can be mapped to a node in an ABA argument by 1) dropping the tag and the ID, and 2) adding nodes τ as children of leaf nodes of the form {a mathematical formula}(_,mr:_[_]) (as each of these node represents a rule with an empty body).  □
     </paragraph>
     <paragraph label="Proof of Lemma 8.3">
      To show {a mathematical formula}S⊢tβ can be drawn from {a mathematical formula}T(δ) is to show all sentences in {a mathematical formula}S⊢β have corresponding nodes in {a mathematical formula}T(δ); and these nodes are connected in the right order with the same label. Let {a mathematical formula}Fδ be {a mathematical formula}〈L,Rδ,Aδ,Cδ〉. Since δ is λ-exhaustive, for all sentences {a mathematical formula}β0,β1,…,βn∈L, if {a mathematical formula}β0←β1,…,βn∈Rδ, then nodes {a mathematical formula}n0=(β0,_:L[_]), {a mathematical formula}n1=(β1,_:L[_]),…,n2=(β2,_:L[_]).  □
     </paragraph>
     <paragraph label="Proof of Lemma 9.1">
      Assume otherwise, let {a mathematical formula}D=DEF(T(δ)), {a mathematical formula}A,A′⊆D and {a mathematical formula}A⊢c attacking {a mathematical formula}A′⊢c′ in {a mathematical formula}Fδ. By definition of defence set, all assumptions in D are labelled P. Since δ is λ-exhaustive, by Lemma 8.3, we know that {a mathematical formula}A⊢tc and {a mathematical formula}A′⊢tc′ are in {a mathematical formula}T(δ). Since A and {a mathematical formula}A′ are in two arguments attacking each other, they cannot have the same labelling. So either A is labelled P or {a mathematical formula}A′ is labelled P, but not both: contradiction, since both A and {a mathematical formula}A′ are subsets of D.  □
     </paragraph>
     <paragraph label="Proof of Lemma 10.1">
      We can transform debate trees into abstract dispute trees. Given a debate tree {a mathematical formula}T(δ), its equivalent abstract dispute tree {a mathematical formula}Ta is constructed as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       Delete all nodes N from {a mathematical formula}T(δ) where N is in a potential argument. Let {a mathematical formula}T′(δ) be the result.
      </list-item>
      <list-item label="2.">
       Modify {a mathematical formula}T′(δ) by appending a new flag field {a mathematical formula}Z={0,1} to each remaining node in {a mathematical formula}T(δ) and initialise Z to 0 for all nodes, i.e., a node now looks like {a mathematical formula}(_,_:_[_])[0]. Let {a mathematical formula}T″(δ) be the result.
      </list-item>
      <list-item label="3.">
       {a mathematical formula}Ta is {a mathematical formula}Tma in the sequence {a mathematical formula}T1a,…,Tma constructed inductively as follows:
      </list-item>
      <list-item label="4.">
       m is the smallest index such that there is no node in {a mathematical formula}Tm″(δ) with its flag equal to 0.
      </list-item>
     </list>
     <paragraph label="Proof of Lemma 10.2">
      We can transform debate trees into abstract dispute trees using the procedure as shown in the proof of Lemma 10.1 with a modification. After deleting all nodes N from {a mathematical formula}T(δ) where N is in a potential argument (step 1), we replace {a mathematical formula}T(δ) with {a mathematical formula}TE(δ), the expanded debate tree of {a mathematical formula}T(δ). The rest of the construction of {a mathematical formula}Ta remains unchanged.It is easy to see that {a mathematical formula}Ta constructed with the modified {a mathematical formula}TE(δ) is an abstract dispute tree and {a mathematical formula}DEF(T(δ))=DEF(Ta) and {a mathematical formula}CUL(T(δ))=CUL(Ta), as shown in the proof of Lemma 10.1.  □
     </paragraph>
     <paragraph label="Proof of Theorem 10.1">
      Similar to the proof of Lemma 10.1, if {a mathematical formula}ωcf(δ,λ)=true, then there exists an abstract dispute tree {a mathematical formula}Ta such that {a mathematical formula}DEF(T(δ))=DEF(Ta) and {a mathematical formula}CUL(T(δ))=CUL(Ta). As shown in [12], as a direct consequence of Theorem 3.7 in [25], we obtain that the defence set of a grounded abstract dispute tree is a subset of the grounded set of arguments. Hence δ is g-successful and χ is grounded and supported by {a mathematical formula}DEF(T(δ)).  □
     </paragraph>
     <paragraph label="Proof of Theorem 10.2">
      If {a mathematical formula}ωcf(δ,λ)=true, by Lemma 10.2 there exists an abstract dispute tree {a mathematical formula}Ta such that {a mathematical formula}DEF(T(δ))=DEF(Ta) and {a mathematical formula}CUL(T(δ))=CUL(Ta). By Theorem 5.1 of [14], the theorem holds.  □
     </paragraph>
     <paragraph label="Proof of Theorem 10.3">
      Let {a mathematical formula}Fδ be {a mathematical formula}〈L,R,A,C〉. From Lemma 10.2, we know that there is an abstract dispute tree {a mathematical formula}Ta for {a mathematical formula}S⊢χ for some {a mathematical formula}S⊆A. Since δ is ideal, by Definition 10.3 we know that none of the opponent arguments drawn from {a mathematical formula}T(δ) belongs to an admissible set of arguments in {a mathematical formula}Fδ. Hence, {a mathematical formula}Ta is ideal. By Theorem 3.4 in [15] the theorem holds.  □
     </paragraph>
     <paragraph label="Proof of Lemma 11.1">
      We show that (I) the inductive process in Definition 11.2 constructs a set of debate trees (II) each of these is for a sub-dialogue of δ and (III) each such sub-dialogue is focused.(I) For each tree {a mathematical formula}Tji(δ) in {a mathematical formula}Fi(δ), Conditions 1(a) and 1(b) in Definition 8.1 are trivially true as all nodes in each tree are inserted in accordance with utterances in δ hence if a sentence β is in a node, β must be in some utterance in the dialogue. Conditions 2(a)–2(f) in Definition 8.1 are met by Conditions 3(a)–3(c) in Definition 11.2. Hence, each tree in a debate forest is a debate tree.(II) Given that {a mathematical formula}F(δ) contains l debate trees {a mathematical formula}T1(δ),…,Tl(δ), the sub-dialogue {a mathematical formula}δi, {a mathematical formula}0&lt;i≤l, that draws the debate tree {a mathematical formula}Ti(δ) is constructed as follows.
      <list>
       {a mathematical formula}δi is initialised to empty;For each node {a mathematical formula}(β,F:_[id])=n in {a mathematical formula}T(δi),Sort {a mathematical formula}δi in the order of utterance IDs.It is easy to see that each
      </list>
      <paragraph>
       {a mathematical formula}δi constructed as above is a sub-dialogue of δ and {a mathematical formula}Ti(δ) is drawn from {a mathematical formula}δi.(III) Let us consider any sub-dialogue {a mathematical formula}δi from part (II). We first show that {a mathematical formula}δi is related, and then that it is focused.{a mathematical formula}δiis related: Trivially {a mathematical formula}δi is and ABA dialogue, given that δ is. We now show {a mathematical formula}δi is compatible with a related {a mathematical formula}λi∈Λ and that {a mathematical formula}ωex(δi,λi)=true.By Definition 8.1, we know that, in a debate tree, there are 6 ways in which two nodes N and {a mathematical formula}N′ can be connected (N is the parent of {a mathematical formula}N′):
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}N=(_,mr:L[id]) and {a mathematical formula}N′=(_,mr:L[id′]), or
       </list-item>
       <list-item label="2.">
        {a mathematical formula}N=(_,mr:L[id]) and {a mathematical formula}N′=(_,ma:L[id′]), or
       </list-item>
       <list-item label="3.">
        {a mathematical formula}N=(_,mr:L[id]) and {a mathematical formula}N′=(_,um:L[id′]), or
       </list-item>
       <list-item label="4.">
        {a mathematical formula}N=(_,ma:L[id]) and {a mathematical formula}N′=(_,mr:L′[id′]), or
       </list-item>
       <list-item label="5.">
        {a mathematical formula}N=(_,ma:L[id]) and {a mathematical formula}N′=(_,ma:L′[id′]), or
       </list-item>
       <list-item label="6.">
        {a mathematical formula}N=(_,ma:L[id]) and {a mathematical formula}N′=(_,um:L′[id′]),
       </list-item>
      </list>
      <paragraph>
       in which {a mathematical formula}L,L′∈{P,O}, {a mathematical formula}L≠L′, {a mathematical formula}id,id′∈ID∖{ID0}. By Definition 7.2, the utterance {a mathematical formula}uid′=〈_,_,_,_,id′〉 is related to the utterance {a mathematical formula}uid=〈_,_,_,_,id〉 in cases 1, 3, 4 and 6. In cases 2 and 5, there is an utterance {a mathematical formula}ut=〈_,_,id,asm(_),t〉, such that {a mathematical formula}ut is related to {a mathematical formula}uid and {a mathematical formula}uid′ is related to {a mathematical formula}ut. It can be seen that the previous construction of {a mathematical formula}δi includes all utterances {a mathematical formula}uid, {a mathematical formula}uid′ and {a mathematical formula}ut but no other utterance. Hence {a mathematical formula}δi is compatible with a related {a mathematical formula}λi∈Λ.{a mathematical formula}δiis focused: Definition 10.1 defines two conditions for debate trees to be focused. Condition (a) in Definition 10.1 is met by 3(c) in Definition 11.2 as this ensures that, in a single tree, a proponent argument is only attacked by a single opponent argument. Condition (b) in Definition 10.1 is met by 3(a) in Definition 11.2 as this ensures that, when a proponent node is expanded such that it has a set of proponent children, then these children must be from a single utterance.  □
      </paragraph>
     </paragraph>
     <paragraph label="Proof of Theorem 11.1">
      Let {a mathematical formula}F(δ) be the debate forest drawn from δ and {a mathematical formula}F(δ) contains debate trees {a mathematical formula}T(δ1),…,T(δn). Given Lemma 11.1, we know all trees in {a mathematical formula}F(δ) are debate trees drawn from some sub-dialogue of δ and each sub-dialogue is focused.Since {a mathematical formula}δi is focused, defensive and conflict-free, {a mathematical formula}δi is g-successful and χ is grounded in {a mathematical formula}AFi, the ABA framework drawn from {a mathematical formula}δi (by Theorem 10.1). We need to show χ is also grounded in {a mathematical formula}AF, the ABA framework drawn from δ.Since {a mathematical formula}δi is g-successful in {a mathematical formula}AFi, then it is not the case that there is an arguments that attacks {a mathematical formula}DEF(T(δi)) that has not been countered attacked in the ABA framework drawn from δ. By Definition 11.2 each debate tree in {a mathematical formula}F(δ) represents a set of arguments that support the claim of δ. Hence each tree contains its own set of defence set, i.e., {a mathematical formula}DEF(T(δi)) is different from {a mathematical formula}DEF(T(δj)), where {a mathematical formula}1≤i,j≤n, {a mathematical formula}i≠j. Therefore, if a defence set of a tree is grounded in the ABA framework drawn from the sub-dialogue, it is also grounded in the ABA framework drawn from the full-dialogue. Hence δ is g-successful as {a mathematical formula}δi is.  □
     </paragraph>
     <paragraph label="Proof of Theorem 11.2">
      Similar to the proof of Theorem 11.1, we can show that properties of {a mathematical formula}δi imply properties of δ.Since δ is filtered, by Definition 11.4, we know that {a mathematical formula}δi is filtered. Also, by Lemma 11.1, {a mathematical formula}δi is focused. Hence, by Theorem 10.2, {a mathematical formula}δi is a-successful in {a mathematical formula}AFi (the ABA framework drawn from {a mathematical formula}δi) and χ is admissible in {a mathematical formula}AFi. Again, by the construction of debate forest (Definition 11.2), we know that each debate tree in the debate forest contains its own defence set, so arguments in other trees do not affect arguments in {a mathematical formula}AFi. Hence, Hence δ is a-successful as {a mathematical formula}δi is.  □
     </paragraph>
     <paragraph label="Proof of Theorem 11.3">
      Let {a mathematical formula}F(δ) be the debate forest drawn from δ and let {a mathematical formula}T(δ1),…,T(δn) be the trees in {a mathematical formula}F(δ). By Lemma 11.1, all trees in {a mathematical formula}F(δ) are debate trees drawn from some sub-dialogue of δ and each sub-dialogue is focused.Since δ is λ-ideal, by Definition 11.6, there is a debate tree {a mathematical formula}T(δi) such that none of the opponent arguments drawn from {a mathematical formula}T(δi) belongs to an admissible set of arguments in {a mathematical formula}Fδ.By Lemma 10.2, there is an abstract dispute tree {a mathematical formula}Ta for {a mathematical formula}S⊢χ for some {a mathematical formula}S⊆A. Since δ is ideal, {a mathematical formula}Ta is ideal. By Theorem 3.4 in [15] the theorem holds.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>