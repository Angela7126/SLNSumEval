<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    On the responsibility for undecisiveness in preferred and stable labellings in abstract argumentation.
   </title>
   <abstract>
    Different semantics of abstract Argumentation Frameworks (AFs) provide different levels of decisiveness for reasoning about the acceptability of conflicting arguments. The stable semantics is useful for applications requiring a high level of decisiveness, as it assigns to each argument the label “accepted” or the label “rejected”. Unfortunately, stable labellings are not guaranteed to exist, thus raising the question as to which parts of AFs are responsible for the non-existence. In this paper, we address this question by investigating a more general question concerning preferred labellings (which may be less decisive than stable labellings but are always guaranteed to exist), namely why a given preferred labelling may not be stable and thus undecided on some arguments. In particular, (1) we give various characterisations of parts of an AF, based on the given preferred labelling, and (2) we show that these parts are indeed responsible for the undecisiveness if the preferred labelling is not stable. We then use these characterisations to explain the non-existence of stable labellings. We present two types of characterisations, based on labellings that are more (or equally) committed than the given preferred labelling on the one hand, and based on the structure of the given AF on the other, and compare the respective AF parts deemed responsible. To prove that our characterisations indeed yield responsible parts, we use a notion of enforcement of labels through structural revision, by means of which the preferred labelling of the given AF can be turned into a stable labelling of the structurally revised AF. Rather than prescribing how this structural revision is carried out, we focus on the enforcement of labels and leave the engineering of the revision open to fulfil differing requirements of applications and information available to users.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Argumentation formalisms have been widely studied for representing arguments and conflicts between these arguments, and for evaluating which sets of arguments should be accepted by resolving the conflicts. An important application area of such formalisms is in decision support, where decisions are made based on an exchange of arguments and an evaluation of their acceptability, see for example [1], [2], [3], [4], [5], [6], [7], [8], [9].
     </paragraph>
     <paragraph>
      One of the most prominent formalisms is Dung's (abstract) Argumentation Framework (AF) [10], which assumes as given a set of arguments, i.e. abstract entities that can represent anything desired by users, and attacks between these arguments. AFs are equipped with different semantics, defining which arguments should be deemed acceptable. They can be defined in terms of acceptable sets of arguments, so called extensions[10], or equivalently in terms of labellings[11], [12], which assign one of the labels in (accepted), out (rejected), or undec (undecided) to each argument. Extensions coincide with the set of all arguments labelled in by a corresponding labelling. Different semantics impose different restrictions on labellings and extensions. Concerning labellings in particular, each argument needs to be legally labelled, where an in -labelled argument is legally labelled if all arguments attacking it are labelled out, an out -labelled argument is legally labelled if at least one argument attacking it is labelled in, and an undec -labelled argument is legally labelled if at least one argument attacking it is labelled undec and no argument attacking it is labelled in[11], [12].
     </paragraph>
     <paragraph>
      In many applications, it is desirable to choose a highly decisive semantics, in other words, a semantics that assigns the label in or the label out to as many arguments as possible. Compared to less decisive semantics, this means greater certainty about the acceptance status of arguments for the user. In particular, the preferred semantics assigns the label in to a maximal set of arguments (w.r.t. set inclusion). If the union of all in - and out -labelled arguments in a preferred labelling is maximal among all preferred labellings (w.r.t. set inclusion), the labelling is semi-stable [13]. Even more decisively, if all arguments in a preferred labelling are labelled in or out, the labelling is stable. In applications requiring decisiveness, e.g. in medical or legal scenarios, it is desirable to have at least one stable labelling. Unfortunately, stable labellings are not guaranteed to exist, that is, in some cases all preferred labellings may comprise arguments labelled undec.
     </paragraph>
     <paragraph>
      As an illustration, consider the following example from the medical domain,{sup:1} represented graphically as an AF in Fig. 1, where nodes are arguments and directed edges are attacks.{sup:2} A physician needs to decide which therapy amongst five possible therapies to recommend to her patient. She first reads a study praising therapy A and concluding that therapy A is way more effective than therapy B. This study thus provides an argument for the effectiveness of therapy A and positions it as a counterargument against any argument stating that therapy B is effective and should be chosen. In Fig. 1, this is indicated by the attack from argument “A is effective” to argument “B is effective”, which the physician obtains reading a second article. This second article recommends therapy B, showing that it is more reliable than therapy C and much more effective than therapy D. The physician reviews a third study, which describes the enormous success of therapy C and the poor performance of therapy A compared to C. Another article advocates therapy D somewhat incoherently, providing within the same study evidence against the effectiveness of this therapy. Therefore, the argument “D is effective” in Fig. 1 attacks itself. Finally, a fifth article discusses therapy E, providing evidence against its effectiveness.
     </paragraph>
     <paragraph>
      The resulting AF, representing the physician's information on the effectiveness of the five therapies, has a single preferred (and semi-stable) labelling but no stable labelling. Thus, using the stable semantics, no therapy can be recommended. The preferred (and semi-stable) labelling, referred to as {a mathematical formula}LabArgpref in the remainder of this introduction and illustrated in Fig. 1, labels all arguments as undec except for argument “E is not effective”, which is labelled in. Thus, using the preferred (or semi-stable) semantics, the physician can draw the conclusion that therapy E is definitely not effective but still cannot make any decision as to which therapy to prescribe. Thus, the non-existence of stable labellings and the undecisiveness of preferred labellings are closely connected problems.
     </paragraph>
     <paragraph>
      In this paper we address the problem of non-existence of stable labellings as a by-product of identifying, for a chosen non-stable preferred labelling of a given AF, which parts of the AF can be deemed responsible that this preferred labelling is not stable. Our mechanisms for identifying parts responsible that a chosen preferred labelling is not stable can be seen as means to move from a “partially undecided” preferred labelling to a “fully decided” stable labelling in a rational way. Note that the problem of identifying parts responsible that a chosen preferred labelling is not stable is interesting in its own right, even if the AF admits stable labellings. Indeed, preferred, non-stable labellings will differ from stable labellings in their assignment of in and out labels, so an argument may be labelled in in a stable labelling and out in a non-stable preferred one. If the user has a preference for the assignment in the latter, but needs to be fully decisive, then understanding why the preferred labelling is not stable is important.
     </paragraph>
     <paragraph>
      Naively, the set of all undec arguments may be deemed responsible if a preferred labelling is not stable, since there are no undec arguments in a stable labelling. We show that, in general, only a subset of undec arguments is in fact responsible. We propose two different characterisation approaches identifying such sets of responsible arguments: a labelling-based approach and a structural approach.
     </paragraph>
     <paragraph>
      In the labelling-based approach, we give characterisations of responsible parts in terms of sets of arguments labelled undec by the chosen preferred labelling and illegally labelled if all undec labels are changed to in or out. As an example, consider the AF in Fig. 1 and its only preferred labelling {a mathematical formula}LabArgpref. Fig. 2 illustrates a re-labelling of the AF, where all arguments labelled undec by {a mathematical formula}LabArgpref are re-labelled as in or out. This may reflect the physician's intuition about the effectiveness of the different therapies or her belief in the truth of the different studies. For example, she may know that the authors of the first study cannot be trusted, whereas those of the second study work in an exemplary scientific manner, leading to the labels illustrated in Fig. 2. Only the argument “A is effective” is illegally labelled by the new labelling and is thus deemed responsible by our labelling-based approach that {a mathematical formula}LabArgpref is not a stable labelling, and consequently that no stable labelling exists.
     </paragraph>
     <paragraph>
      In contrast, in the structural approach we characterise responsible parts as initial strongly connected components (SCCs) [16] of the AF restricted to arguments labelled undec by the chosen preferred labelling. We call such parts strongly connectedundecparts (SCUPs) and prove that they always comprise an odd-length cycle of attacking arguments. The only SCUP of the AF in Fig. 1 is the cycle of arguments about therapies A, B, and C, so the set of these three arguments is deemed responsible by our structural approach that {a mathematical formula}LabArgpref is not a stable labelling, and consequently that no stable labelling exists.
     </paragraph>
     <paragraph>
      We define responsibility that a chosen preferred labelling is not stable in terms of parts of the AF that require changes in order to turn the undec labels into legal in or out labels. This necessarily requires some structural revision of those responsible parts. Importantly, the exact structural change is not of interest here; instead, the engineering of the revision is left open to fulfil differing requirements of applications and information available to users. We therefore focus on the change of labels from undec to in or out and the fact that enforcing{sup:3} the label through some structural revision makes this label legal (in the structurally revised AF).
     </paragraph>
     <paragraph>
      For instance, in our example we determined that one of the sets of arguments deemed responsible by our labelling-based characterisation comprises only the argument “A is effective”, since it is illegally labelled out by the re-labelling in Fig. 2. Enforcing the label out for this argument leads to “A is effective” being legally labelled out. This could be achieved, e.g., by adding a new argument attacking the argument about A, as illustrated in Fig. 3. The new argument may be additional evidence found by the physician, concluding that therapy A is not effective at all. In this paper, however, we are interested in the existence of some structural revision rather than the exact nature of the structural change.
     </paragraph>
     <paragraph>
      Using this notion of enforcement of labels, we prove that our labelling-based characterisations yield exactly those sets of arguments (a) that need to be enforced and (b) that are sufficient to enforce in order to ensure that all arguments are legally labelled (in the structurally revised AF). Since our labelling-based characterisations thus provide necessary and sufficient conditions for turning a non-stable into a stable labelling (through structural revision), the characterised parts of the AF can be deemed responsible that the given preferred labelling is not stable.
     </paragraph>
     <paragraph>
      Within our structural approach, the characterisation in terms of SCUPs give a necessary condition for turning a non-stable into a stable labelling (through structural revision). We furthermore show that iteratively enforcing arguments in SCUPs gives a sufficient condition for turning a non-stable into a stable labelling (through structural revision). SCUPs can thus be deemed responsible that the given preferred labelling is not stable.
     </paragraph>
     <paragraph>
      Note that our labelling-based characterisations are defined with respect to any preferred labelling. For preferred labellings that are stable, the empty set of arguments is the only “responsible” set identified by our characterisations. We can therefore show that an AF has no stable labelling if and only if, with respect to all preferred labellings, there exists a non-empty set of arguments identified as the responsible part of the AF.
     </paragraph>
     <paragraph>
      The paper is organised as follows. We provide background on AFs in Section 2 and give some preliminary definitions used throughout this paper in Section 3. In Section 4, we define our labelling-based characterisations of parts of an AF and prove that two of them are indeed responsible if a given preferred labelling is not stable since they provide necessary and sufficient conditions for turning the preferred labelling into a stable labelling through a structural revision. In Section 5, we introduce our structural characterisations of responsible parts: odd-length cycles of attacking arguments, specific strongly connected components (SCCs), and SCUPs. The latter are indeed responsible if the given preferred labelling is not stable as they provide a sufficient condition for turning a non-stable preferred labelling into a stable one (of the structural revision). We then investigate the relation between our labelling-based and structural characterisations in Section 6. In Section 7, we discuss how our definitions characterise the non-existence of stable labellings, explain some of the design choices underlying our approach, and compare our to related work. In Section 8, we conclude and discuss future work.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      An argumentation framework (AF) [10] is a pair {a mathematical formula}AF=〈Ar,Att〉, where Ar is a (finite) set of arguments and {a mathematical formula}Att⊆(Ar×Ar) is a set of attacks between them. We say that argument Aattacks argument B, or equivalently that Bis attacked byA, if and only if {a mathematical formula}(A,B)∈Att. A set of arguments {a mathematical formula}Args⊆Ar attacks a set of arguments {a mathematical formula}Args′⊆Ar if and only if there exist arguments {a mathematical formula}A∈Args and {a mathematical formula}B∈Args′ such that {a mathematical formula}(A,B)∈Att. We denote by {a mathematical formula}parents(Args) the set of all arguments that are not contained in {a mathematical formula}Args and attack {a mathematical formula}Args, i.e. {a mathematical formula}parents(Args)={A∈Ar∖Args|(A,B)∈Att,B∈Args}.
     </paragraph>
     <paragraph label="Example 1">
      Let {a mathematical formula}AF1=〈{a,b,c},{(a,b),(b,b),(b,c),(c,b)}〉, which is illustrated as a graph in Fig. 4 (with arguments as nodes and attacks as directed edges). For the set of arguments {a mathematical formula}{b}, {a mathematical formula}parents({b})={a,c}.
     </paragraph>
     <paragraph>
      For the rest of this paper, we assume as given a fixed but arbitrary argumentation framework {a mathematical formula}AF=〈Ar,Att〉, unless specified otherwise.
     </paragraph>
     <paragraph>
      The semantics of an AF are originally defined in terms of extensions[10], i.e. sets of “accepted” arguments, which are able to defend themselves against all attacking arguments. The semantics can be equivalently expressed in terms of labellings [11], [12], which we will use here.
     </paragraph>
     <paragraph>
      A labelling of {a mathematical formula}AF is a total function {a mathematical formula}LabArg:Ar⟶{in,out,undec}. We will sometimes refer to a labelling regarding the set of arguments it labels rather than the AF, for example {a mathematical formula}LabArg is a labelling of Ar. We denote the set of all arguments labelled in by {a mathematical formula}LabArg as {a mathematical formula}in(LabArg), i.e. {a mathematical formula}in(LabArg)={A∈Ar|LabArg(A)=in}, and the sets of arguments labelled out and undec as {a mathematical formula}out(LabArg) and {a mathematical formula}undec(LabArg), respectively. We call a labelling with {a mathematical formula}undec(LabArg)=∅ an in –outlabelling.
     </paragraph>
     <paragraph>
      Given a labelling {a mathematical formula}LabArg of {a mathematical formula}AF and an argument {a mathematical formula}A∈Ar:
     </paragraph>
     <list>
      <list-item label="•">
       A is legally labelledin by {a mathematical formula}LabArg if and only if {a mathematical formula}A∈in(LabArg) and {a mathematical formula}∀B∈Ar attacking A it holds that {a mathematical formula}B∈out(LabArg);
      </list-item>
      <list-item label="•">
       A is legally labelledout by {a mathematical formula}LabArg if and only if {a mathematical formula}A∈out(LabArg) and {a mathematical formula}∃B∈Ar attacking A such that {a mathematical formula}B∈in(LabArg);
      </list-item>
      <list-item label="•">
       A is legally labelledundec by {a mathematical formula}LabArg if and only if {a mathematical formula}A∈undec(LabArg) and {a mathematical formula}∃B∈Ar attacking A such that {a mathematical formula}B∈undec(LabArg), and {a mathematical formula}∀C∈Ar attacking A it holds that {a mathematical formula}C∉in(LabArg).
      </list-item>
     </list>
     <paragraph>
      A is legally labelled by {a mathematical formula}LabArg if and only if it is legally labelled in, out, or undec by {a mathematical formula}LabArg; otherwise A is illegally labelled by {a mathematical formula}LabArg. Equivalently we say that a label is legal/illegal w.r.t. {a mathematical formula}LabArg.
     </paragraph>
     <paragraph>
      A labelling {a mathematical formula}LabArg of {a mathematical formula}AF is a complete labelling of {a mathematical formula}AF if and only if all arguments {a mathematical formula}A∈Ar are legally labelled by {a mathematical formula}LabArg. A complete labelling {a mathematical formula}LabArg of {a mathematical formula}AF is
     </paragraph>
     <list>
      <list-item label="•">
       a stable labelling of {a mathematical formula}AF if and only if it is an in –out labelling;
      </list-item>
      <list-item label="•">
       a preferred labelling of {a mathematical formula}AF if and only if {a mathematical formula}in(LabArg) is maximal (w.r.t. ⊆) among all complete labellings.
      </list-item>
     </list>
     <paragraph label="Example 2">
      {a mathematical formula}AF1 (see Fig. 4) has one complete labelling, namely {a mathematical formula}LabArg={(a,in),(b,out),(c,in)}, which is also the only preferred and only stable labelling.
     </paragraph>
     <paragraph>
      Given a set of arguments {a mathematical formula}Args⊆Ar, {a mathematical formula}AF↓Args=〈Args,AttArgs〉 denotes the restriction of{a mathematical formula}AFto{a mathematical formula}Args, where {a mathematical formula}AttArgs=Att∩(Args×Args). Furthermore, given a labelling {a mathematical formula}LabArg of {a mathematical formula}AF, {a mathematical formula}LabArg↓Args=LabArg∩(Args×{in,out,undec}) denotes the restriction of{a mathematical formula}LabArgto{a mathematical formula}Args[18].
     </paragraph>
     <paragraph label="Example 3">
      Given the set of arguments {a mathematical formula}{a,b}, {a mathematical formula}AF1↓{a,b} is depicted in Fig. 5 along with the labelling {a mathematical formula}LabArg↓{a,b}.
     </paragraph>
     <paragraph>
      A path from argument {a mathematical formula}A∈Ar to argument {a mathematical formula}B∈Ar is a sequence of arguments {a mathematical formula}A0,A1,…,An ({a mathematical formula}n&gt;0, {a mathematical formula}∀i∈{0,…,n}:Ai∈Ar) with {a mathematical formula}A0=A and {a mathematical formula}An=B such that {a mathematical formula}∀i∈{0,…,n−1}: {a mathematical formula}Ai attacks {a mathematical formula}Ai+1. A cycle is a path {a mathematical formula}A0,A1,…,An where {a mathematical formula}An=A0. It is an odd-length cycle if and only if n is odd. With an abuse of notation, we denote a cycle as a set of arguments {a mathematical formula}C, where {a mathematical formula}Ai∈C if and only if {a mathematical formula}Ai occurs in the cycle.
     </paragraph>
     <paragraph>
      Path-equivalence between two arguments {a mathematical formula}A∈Ar and {a mathematical formula}B∈Ar holds if and only if {a mathematical formula}A=B or there exists a path both from A to B and from B to A. The equivalence classes of arguments under the relation of path-equivalence are called strongly connected components (SCCs) of {a mathematical formula}AF[16]. Since SCCs are sets of arguments, the notion of attacks between sets of arguments can be straightforwardly lifted to a notion of attacks between SCCs. Given an SCC {a mathematical formula}Args⊆Ar, the set of parent SCCs is {a mathematical formula}parentSCCs(Args)={Args′⊆Ar|Args′is an SCC ofAF,Args′∩parents(Args)≠∅}. If {a mathematical formula}parentSCCs(Args)=∅, then {a mathematical formula}Args is an initial SCC. Furthermore, the set of ancestor SCCs of {a mathematical formula}Args is{a mathematical formula}
     </paragraph>
     <paragraph label="Example 4">
      {a mathematical formula}AF1 (see Fig. 4) has one odd-length cycle, namely {a mathematical formula}{b}, and two SCCs, namely {a mathematical formula}{a} and {a mathematical formula}{b,c}, where the former attacks the latter. {a mathematical formula}parentSCCs({a})=ancestorSCCs({a})=∅, so {a mathematical formula}{a} is an initial SCC, and {a mathematical formula}parentSCCs({b,c})=ancestorSCCs({b,c})={a}.
     </paragraph>
     <paragraph>
      An argumentation framework (AF) with input[18] is a tuple{a mathematical formula} where I is a set of input arguments such that {a mathematical formula}I∩Ar=∅, {a mathematical formula}LabArgI is the input labelling of I (i.e. a labelling of I), and {a mathematical formula}AttI is an attack relation between I and Ar, i.e. {a mathematical formula}AttI⊆(I×Ar). We say that argument {a mathematical formula}A∈Iattacks argument {a mathematical formula}B∈Ar if {a mathematical formula}(A,B)∈AttI.
     </paragraph>
     <paragraph>
      The semantics of an AF with input is defined as follows. A labelling {a mathematical formula}LabArg of {a mathematical formula}AF is a complete labelling w.r.t.{a mathematical formula}AFI if and only if for all {a mathematical formula}A∈Ar it holds that{sup:4}:
     </paragraph>
     <list>
      <list-item label="•">
       if {a mathematical formula}A∈in(LabArg), then {a mathematical formula}∀B∈Ar∪I attacking A it holds that {a mathematical formula}B∈out(LabArg)∪out(LabArgI);
      </list-item>
      <list-item label="•">
       if {a mathematical formula}A∈out(LabArg), then {a mathematical formula}∃B∈Ar∪I attacking A such that {a mathematical formula}B∈in(LabArg)∪in(LabArgI);
      </list-item>
      <list-item label="•">
       if {a mathematical formula}A∈undec(LabArg), then {a mathematical formula}∃B∈Ar∪I attacking A such that {a mathematical formula}B∈undec(LabArg)∪undec(LabArgI), and {a mathematical formula}∀B∈Ar∪I attacking A it holds that {a mathematical formula}B∉in(LabArg)∪in(LabArgI).
      </list-item>
     </list>
     <paragraph>
      A labelling {a mathematical formula}LabArg of {a mathematical formula}AF is a stable labelling w.r.t.{a mathematical formula}AFI if and only if {a mathematical formula}LabArg is a complete labelling w.r.t. {a mathematical formula}AFI and {a mathematical formula}undec(LabArg)=∅. We sometimes say that {a mathematical formula}LabArg is a complete/stable labelling of{a mathematical formula}AFw.r.t. the input I.
     </paragraph>
     <paragraph label="Example 5">
      An AF with input {a mathematical formula}(AF1,I,LabArgI,AttI) is depicted in Fig. 6, where the set of input arguments is {a mathematical formula}I={a′,b′}, the labelling of input arguments is {a mathematical formula}LabArgI={(a′,in),(b′,undec)}, and {a mathematical formula}AttI={(a′,a)}. There are two complete labellings w.r.t. {a mathematical formula}(AF1,I,LabArgI,AttI), namely {a mathematical formula}{(a,out),(b,undec),(c,undec)} and {a mathematical formula}{(a,out),(b,out),(c,in)}, where the latter is a stable labelling w.r.t. {a mathematical formula}(AF1,I,LabArgI,AttI).
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      The aim of this paper is to give characterisations of parts of an AF responsible that a given preferred labelling is not stable. To prove that the characterised parts are in fact responsible, we show that when re-labelling arguments labelled undec by the preferred labelling as in or out, with the aim to obtain a stable labelling, the labels of arguments in the characterised parts have to be enforced through some structural revision to ensure their legality. In contrast, labels of arguments not in the characterised parts may not have to be enforced.
     </paragraph>
     <paragraph>
      Importantly, we are here not interested in the exact structural revision, but rather in any (sensible) structural revision of the AF that turns illegally labelled arguments into legally re-labelled ones. In other words, we see structural revisions as a way to “enforce” the legality of labels. Since we are only interested in enforcing the labels of certain arguments (usually those re-labelled as in or out that have been identified as responsible), we restrict structural revisions to a given set of arguments.
     </paragraph>
     <paragraph>
      The rational behind this enforcement of labels through structural revision is as follows: If a preferred labelling is not stable, our characterisations of responsible sets point the user towards parts of the AF responsible that the acceptability of some arguments cannot be decided. The user can then further investigate the nature of these arguments and decide which label they should have. The user may for example notice that she expected one of the responsible arguments to be accepted and would thus label it as in. To ensure that this argument is legally labelled, the structure of the AF (in particular, the structure of the part including the re-labelled argument) then has to be revised. This revision may be grounded in the user's realisation that the structure of the AF is incorrect, for example, that an important argument is missing (adding an argument to the AF) or that an existing attack should not be present in the AF (deleting an attack).
     </paragraph>
     <paragraph>
      Following this intuition, we introduce set-driven revisions, which ensure that labels (according to some desired labelling) of arguments in a given set {a mathematical formula}Args are legal after structurally revising the part of the AF consisting of {a mathematical formula}Args, while not making any structural changes affecting arguments not in {a mathematical formula}Args.
     </paragraph>
     <paragraph label="Definition 1">
      Set-driven revision and revision labellingLet {a mathematical formula}LabArg be a labelling of {a mathematical formula}AF and let {a mathematical formula}Args⊆Ar. A (set-driven) revision of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg is {a mathematical formula}AF⊛=〈Ar⊛,Att⊛〉 such that:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Ar⊆Ar⊛;
      </list-item>
      <list-item label="•">
       {a mathematical formula}{(A,B)∈Att|B∈Ar∖Args}={(A,B)∈Att⊛|B∈Ar∖Args};
      </list-item>
      <list-item label="•">
       there exists a labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ satisfying that:
      </list-item>
     </list>
     <paragraph>
      Since a set-driven revision enforces desired labels for arguments in the given set {a mathematical formula}Args, we do not allow the deletion of arguments in {a mathematical formula}Args. Arguments may thus only be added in a set-driven revision (specified by the first bullet in Definition 1). Furthermore, structural changes that may affect (the legality of labels of) arguments not in {a mathematical formula}Args are prohibited. Thus, all attacks on arguments not in {a mathematical formula}Args have to remain the same in the revision (specified by the second bullet). It follows, that permitted structural changes are the addition of attacks between arguments in {a mathematical formula}Args or between new arguments and arguments in {a mathematical formula}Args, and the deletion of attacks between arguments in {a mathematical formula}Args or from arguments not in {a mathematical formula}Args to arguments in {a mathematical formula}Args (indirectly specified by the second bullet). Since {a mathematical formula}LabArg specifies the desired labels of all arguments, a revision labelling is a simple “enlargement” of {a mathematical formula}LabArg to include (legal) labels of new arguments; the labels of all other arguments remain unchanged (specified by the first and second item of the third bullet). Furthermore, and most importantly, a revision labelling ensures that all arguments in {a mathematical formula}Args are legally labelled in the revision (specified by the third item of the third bullet).
     </paragraph>
     <paragraph>
      From here onwards, we will refer to set-driven revisions simply as revisions.
     </paragraph>
     <paragraph label="Example 6">
      Consider the AF in Fig. 1 (see page 302), call it {a mathematical formula}AFtherapy. From here on, we use a shorthand notation for each argument according to the letter of the respective therapy, e.g. A denotes the argument “A is effective”. Let {a mathematical formula}LabArg be the labelling of {a mathematical formula}AFtherapy illustrated in Fig. 2 (see page 303). Fig. 3 (see page 304) depicts a revision of {a mathematical formula}AFtherapy w.r.t. {a mathematical formula}{A} by {a mathematical formula}LabArg, which we denote {a mathematical formula}AFtherapy⊛, and the labelling in Fig. 3 is a revision labelling of {a mathematical formula}AFtherapy⊛. Note that {a mathematical formula}AFtherapy⊛ is also a revision of {a mathematical formula}AFtherapy w.r.t. any superset of {a mathematical formula}{A} by {a mathematical formula}LabArg.
     </paragraph>
     <paragraph>
      As shown by the following lemma, a revision exists for any given set of arguments and any labelling.
     </paragraph>
     <paragraph label="Lemma 1">
      Let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFand let{a mathematical formula}Args⊆Ar. Then there exists a revision of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArg.
     </paragraph>
     <paragraph>
      The proof of this lemma and of most other lemmas and propositions presented throughout this paper can be found in Appendix B.
     </paragraph>
     <paragraph>
      Note that, in this paper, we are not concerned with the exact structural change of a revision compared to the original AF. We simply use the structural change of an AF as a tool to ensure that labels of arguments are legal. As a result, there may be various revisions of an AF w.r.t. a given set of arguments and labelling. Furthermore, a revision may have various different revision labellings. It is in general up to the preference of users and the application scenario to decide which of these revisions and revision labellings to use. For example, a user may be interested in revisions with “minimal” structural changes as in [19], [20].
     </paragraph>
     <paragraph label="Example 7">
      Let {a mathematical formula}AF2 be the AF depicted on the left of Fig. 7 and {a mathematical formula}LabArg the labelling of {a mathematical formula}AF2 illustrated on the left of Fig. 7, which is the labelling we desire. Argument a is illegally labelled by {a mathematical formula}LabArg, so a revision can be used to enforce the desired label for argument a. A possible revision of {a mathematical formula}AF2 w.r.t. {a mathematical formula}{a} by {a mathematical formula}LabArg is illustrated on the right of Fig. 7, alongside a revision labelling. Another revision of {a mathematical formula}AF2 w.r.t. {a mathematical formula}{a} by {a mathematical formula}LabArg is illustrated in Fig. 8, alongside two different revision labellings.
     </paragraph>
     <paragraph>
      Next, we extend the comparison notion of commitment of two labellings of an AF [11] to the comparison of labellings of potentially different AFs, where the arguments of one AF form a superset of the arguments of the other.
     </paragraph>
     <paragraph label="Definition 2">
      Commitment of labellingsLet {a mathematical formula}LabArg be a labelling of {a mathematical formula}AF and let {a mathematical formula}LabArg′ be a labelling of {a mathematical formula}AF′=〈Ar′,Att′〉, where {a mathematical formula}Ar⊆Ar′.
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}LabArg′ is more or equally committed than {a mathematical formula}LabArg, denoted {a mathematical formula}LabArg⊑LabArg′, if and only if {a mathematical formula}in(LabArg)⊆in(LabArg′), {a mathematical formula}out(LabArg)⊆out(LabArg′) and {a mathematical formula}undec(LabArg′)⊆undec(LabArg).
      </list-item>
      <list-item label="•">
       {a mathematical formula}LabArg′ is more committed than {a mathematical formula}LabArg, denoted {a mathematical formula}LabArg⊏LabArg′, if and only if {a mathematical formula}LabArg⊑LabArg′ and {a mathematical formula}undec(LabArg′)⊂undec(LabArg).
      </list-item>
     </list>
     <paragraph>
      We note that a revision labelling is more or equally committed than the original labelling.
     </paragraph>
     <paragraph label="Observation 2">
      Let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFand{a mathematical formula}Args⊆Ar. Then, for all revisions{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand all revision labellings{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛, it holds that{a mathematical formula}LabArg⊑LabArg⊛.
     </paragraph>
     <paragraph>
      For instance, the two revision labellings of the revision of {a mathematical formula}AF2 illustrated in Fig. 8 (see Example 7) are more committed than the original labelling of {a mathematical formula}AF2, depicted on the left of Fig. 7.
     </paragraph>
     <paragraph label="Notation 1">
      In the remainder of this paper, and if not stated otherwise, we assume as given a fixed but arbitrary argumentation framework {a mathematical formula}AF=〈Ar,Att〉 and a preferred labelling {a mathematical formula}LabArgpref of {a mathematical formula}AF.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Labelling-based characterisations
     </section-title>
     <paragraph>
      As previously explained, we aim to 1) characterise parts of an AF responsible that a chosen preferred labelling is not stable and 2) prove the responsibility of these parts by showing that, in order to obtain a stable labelling that is more committed than this preferred labelling, in or out labels have to be enforced for arguments in these responsible parts.
     </paragraph>
     <paragraph>
      In this section, we give three declarative characterisations of sets of arguments responsible if {a mathematical formula}LabArgpref is not a stable labelling. All characterisations identify the empty set as responsible if and only if {a mathematical formula}LabArgpref is stable. These characterisations are labelling-based, which means that they identify responsible sets based on labellings that are more or equally committed than {a mathematical formula}LabArgpref. We also investigate our characterisations in the light of revisions of the AF that (do not) have a stable labelling that is more committed than {a mathematical formula}LabArgpref. In particular, we show that our two non-naïve characterisations, which we introduce in Sections 4.2 and 4.3, define necessary and sufficient conditions for the existence and non-existence of a more committed stable labelling of a revision.
     </paragraph>
     <section label="4.1">
      <section-title>
       The basic approach
      </section-title>
      <paragraph>
       A naïve way to characterise arguments responsible that {a mathematical formula}LabArgpref is not a stable labelling is in terms of all arguments labelled undec by {a mathematical formula}LabArgpref, since these are the arguments violating the definition of a stable labelling.
      </paragraph>
      <paragraph label="Definition 3">
       Labelling-based characterisation 1{a mathematical formula}undec(LabArgpref) is the labelling-based responsible set w.r.t. {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       Trivially, if {a mathematical formula}LabArgpref is a stable labelling, the labelling-based responsible set is the empty set.
      </paragraph>
      <paragraph>
       It is straightforward that this characterisation provides a sufficient condition for turning a non-stable preferred labelling into a stable labelling (of a revision), as stated in the following proposition. That is, a labelling-based responsible set comprises all those arguments whose labels definitely need to be enforced in order to obtain a stable labelling of a revision, i.e. the responsible arguments are included in this set. However, (since this characterisation gives only a sufficient but not a necessary condition) a labelling-based responsible set may also comprise arguments whose labels do not necessarily need to be enforced, i.e. non-responsible arguments.
      </paragraph>
      <paragraph label="Proposition 3">
       Let{a mathematical formula}Argsbe the labelling-based responsible set w.r.t.{a mathematical formula}LabArgprefand let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊑LabArgand{a mathematical formula}undec(LabArg)=∅. Then, for all revisions{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand all revision labellings{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛,{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
      </paragraph>
      <paragraph label="Example 8">
       Consider again {a mathematical formula}AFtherapy from Example 6 (see page 306) and its only preferred labelling {a mathematical formula}LabArgpref, which labels all arguments undec except for argument E, which is labelled in. Thus, the labelling-based responsible set w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}{A,B,C,D}. Let {a mathematical formula}LabArg be the labelling of {a mathematical formula}AFtherapy illustrated in Fig. 2 (see page 303). The revision labelling of the revision {a mathematical formula}AFtherapy⊛ of {a mathematical formula}AFtherapy w.r.t. {a mathematical formula}{A,B,C,D} by {a mathematical formula}LabArg (see Fig. 3, page 304) is a stable labelling of {a mathematical formula}AFtherapy⊛.
      </paragraph>
      <paragraph>
       Since by Lemma 1 a revision exists w.r.t. any set of arguments and any labelling, it follows that there exists a revision w.r.t. the labelling-based responsible set, and in particular (by Proposition 3) a revision that has a stable labelling.
      </paragraph>
      <paragraph label="Corollary 4">
       Let{a mathematical formula}Argsbe the labelling-based responsible set w.r.t.{a mathematical formula}LabArgprefand let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊑LabArgand{a mathematical formula}undec(LabArg)=∅. Then there exists a revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand a revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
      </paragraph>
      <paragraph>
       Note that, by Observation 2, a stable labelling obtained through such a revision is more committed than {a mathematical formula}LabArgpref (if {a mathematical formula}LabArgpref is not stable). Thus, as desired, the labelling-based responsible set can be used to turn a non-stable preferred labelling into a stable labelling (of a revision).
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Enforcement sets
      </section-title>
      <paragraph>
       The definition of labelling-based responsible set is a rather naïve characterisation of arguments responsible if a preferred labelling is not stable, since it is often possible to legally label some of its arguments as in or out. For example, considering the arguments A, B, C, and D labelled undec by the preferred labelling of {a mathematical formula}AFtherapy (see Fig. 1, page 302), we observe that three out of these four arguments can in fact be legally labelled in or out, as illustrated in Fig. 2 (see page 303).
      </paragraph>
      <paragraph>
       Our next characterisation takes this observation into account, characterising specific subsets of the labelling-based responsible set as responsible. In particular, arguments that are legally labelled by an in –out labelling that is more or equally committed than {a mathematical formula}LabArgpref will not be deemed responsible. More precisely, our second labelling-based characterisation defines a minimal set of arguments labelled undec by {a mathematical formula}LabArgpref satisfying that some in –out labelling that is more or equally committed than {a mathematical formula}LabArgpref legally labels all non-responsible arguments (i.e. all arguments not contained in this set).
      </paragraph>
      <paragraph label="Definition 4">
       Labelling-based characterisation 2{a mathematical formula}Args⊆Ar is an enforcement set w.r.t. {a mathematical formula}LabArgpref if and only if it is a minimal set of arguments (w.r.t. ⊆) such that
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}Args⊆undec(LabArgpref)
       </list-item>
       <list-item>
        and {a mathematical formula}∃LabArg of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊑LabArg and {a mathematical formula}undec(LabArg)=∅
       </list-item>
       <list-item>
        such that {a mathematical formula}∀A∈undec(LabArgpref)∖Args: A is legally labelled by {a mathematical formula}LabArg.
       </list-item>
      </list>
      <paragraph label="Example 9">
       Consider {a mathematical formula}AFtherapy and its only preferred labelling {a mathematical formula}LabArgpref (see Example 8 on page 308 and Fig. 1 on page 302). Then {a mathematical formula}{A} is an enforcement set w.r.t. {a mathematical formula}LabArgpref, where the labelling shown in Fig. 2 (page 303) is an enforcement labelling, as it is an in –out labelling that is more committed than {a mathematical formula}LabArgpref and it legally labels all arguments labelled undec by {a mathematical formula}LabArgpref except for argument A (i.e. arguments B, C, and D). Furthermore, {a mathematical formula}{A} is a minimal set satisfying this condition, since for its only subset {a mathematical formula}{} there exists no in –out labelling that is more committed than {a mathematical formula}LabArgpref and that legally labels all arguments labelled undec by {a mathematical formula}LabArgpref. There are two more enforcement sets w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{B} and {a mathematical formula}{C}. Note that {a mathematical formula}{D} is not an enforcement set since there exists no in –out labelling that legally labels A, B, and C. Furthermore, no superset of {a mathematical formula}{D} is an enforcement set, as no such superset fulfils the minimality condition.
      </paragraph>
      <paragraph>
       In Example 9, all enforcement sets are disjoint. The following example illustrates that different enforcement sets may contain the same arguments and that an enforcement set may have various different enforcement labellings.
      </paragraph>
      <paragraph label="Example 10">
       Let {a mathematical formula}AF3 be the AF on the left of Fig. 9, whose only preferred labelling {a mathematical formula}LabArgpref labels all arguments as undec. There are three enforcement sets w.r.t. {a mathematical formula}LabArgpref: {a mathematical formula}{a,e}, {a mathematical formula}{b,e}, and {a mathematical formula}{c,e}. Note that for all of them various enforcement labellings exist, e.g. the labelling illustrated on the left of Fig. 9 is an enforcement labelling of {a mathematical formula}{b,e}, and so is {a mathematical formula}{(a,out),(b,out),(c,in), {a mathematical formula}(d,in),(e,in)} (among others).
      </paragraph>
      <paragraph>
       It follows from Definition 4 that all arguments in an enforcement set are illegally labelled by an enforcement labelling. For example, arguments b and e are illegally labelled by both enforcement labellings discussed in Example 10. Still, we note that an enforcement set is defined as a minimal set of arguments such that all arguments not in this set are legally labelled. An alternative definition of enforcement set as a minimal set of arguments such that all arguments in this set are illegally labelled is however not equivalent as it would always yield the empty set as the only enforcement set (w.r.t. any enforcement labelling). Clearly, the empty set, and thus the alternative definition, would not be helpful in characterising parts of an AF responsible that a given preferred labelling is not stable.
      </paragraph>
      <paragraph>
       In the following lemma, we show that at least one enforcement set exists and that enforcement sets are always non-empty if {a mathematical formula}LabArgpref is not a stable labelling. Both are important properties for sets of arguments characterising parts of an AF responsible that a preferred labelling is not stable.
      </paragraph>
      <paragraph label="Lemma 5">
       Enforcement sets have the following properties:
      </paragraph>
      <list>
       <list-item label="1.">
        There exists an enforcement set w.r.t.{a mathematical formula}LabArgpref.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Args=∅is an enforcement set w.r.t.{a mathematical formula}LabArgprefif and only if{a mathematical formula}LabArgprefis a stable labelling.
       </list-item>
      </list>
      <paragraph>
       Note that if {a mathematical formula}Args=∅ is an enforcement set w.r.t. {a mathematical formula}LabArgpref, it is the only enforcement set w.r.t. {a mathematical formula}LabArgpref as it is the minimal set satisfying Definition 4, where {a mathematical formula}LabArgpref is the only enforcement labelling.
      </paragraph>
      <section label="4.2.1">
       <section-title>
        Responsibility of enforcement sets
       </section-title>
       <paragraph>
        The reason for naming our second labelling-based characterisation “enforcement sets” is illustrated by Theorem 6: “enforcing” the labels of an enforcement labelling for arguments in an enforcement set in terms of a revision results in a stable labelling (of a revision). An enforcement set is thus a sufficient condition for obtaining a stable labelling through a revision, which is more refined than the condition given by the labelling-based responsible set (since every enforcement set is a subset of the labelling-based responsible set). This proves that all arguments that are jointly responsible that a preferred labelling is not stable are contained in an enforcement set.
       </paragraph>
       <paragraph label="Theorem 6">
        Let{a mathematical formula}Args⊇Argsenfwhere{a mathematical formula}Argsenfis an enforcement set w.r.t.{a mathematical formula}LabArgprefand let{a mathematical formula}LabArgbe an enforcement labelling w.r.t.{a mathematical formula}Argsenf. Then, for all revisions{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand all revision labellings{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛,{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
       </paragraph>
       <paragraph label="Proof">
        Since by Definition 4, {a mathematical formula}undec(LabArg)=∅, it follows from Observation 2 that {a mathematical formula}undec(LabArg⊛)=∅. By Definition 1, all {a mathematical formula}A∈Ar⊛∖Ar are legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Let {a mathematical formula}B∈Ar. If {a mathematical formula}B∈Args, then, by Definition 1, B is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. If {a mathematical formula}B∉Args, and thus B {a mathematical formula}∉Argsenf, then by Lemma 39 in Appendix A, B is legally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF, so by Lemma 37 in Appendix A, B is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Since all arguments are legally labelled by {a mathematical formula}LabArg⊛ and {a mathematical formula}undec(LabArg⊛)=∅, {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛.  □
       </paragraph>
       <paragraph label="Example 11">
        Consider the enforcement set {a mathematical formula}{b,e} and the enforcement labelling {a mathematical formula}LabArg of {a mathematical formula}AF3, illustrated on the left of Fig. 9 (see page 309). The AF on the right of Fig. 9 is a revision {a mathematical formula}AF3⊛ of {a mathematical formula}AF3 w.r.t. {a mathematical formula}{b,e} by {a mathematical formula}LabArg and the revision labelling {a mathematical formula}LabArg⊛ illustrated in the figure is a stable labelling of {a mathematical formula}AF3⊛.
       </paragraph>
       <paragraph>
        Note that Theorem 6 shows that in order to obtain a stable labelling (of a revision), it is sufficient to enforce the label in or out for certain arguments that are labelled undec by {a mathematical formula}LabArgpref. In particular, it tells us which subsets of undec arguments can be chosen for the enforcement, namely enforcement sets. In general enforcing labels for some (unrestricted) subset of undec arguments may not result in a stable labelling (of a revision). For example, for {a mathematical formula}AF3, whose only preferred labelling labels all arguments as undec, choosing {a mathematical formula}{d} (or even {a mathematical formula}{d,e}) as a subset of undec arguments and enforcing the labels in or out for these arguments, we do not obtain a stable labelling. If, however, one of the enforcement sets is chosen, as illustrated in Example 11, and labels are enforced appropriately, then a stable labelling (of the revision) is obtained.
       </paragraph>
       <paragraph>
        Since by Lemma 1 a revision exists w.r.t. any set of arguments and labelling, it follows that there exists a revision w.r.t. an enforcement set by an enforcement labelling and that the revision has a stable labelling that is more committed than {a mathematical formula}LabArgpref.
       </paragraph>
       <paragraph label="Corollary 7">
        Let{a mathematical formula}Args⊇Argsenfwhere{a mathematical formula}Argsenfis an enforcement set w.r.t.{a mathematical formula}LabArgprefand let{a mathematical formula}LabArgbe an enforcement labelling w.r.t.{a mathematical formula}Argsenf. Then there exists a revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand a revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
       </paragraph>
      </section>
     </section>
     <section label="4.3">
      <section-title>
       Preventing sets
      </section-title>
      <paragraph>
       Enforcement sets characterise a responsible set of arguments with respect to a specific more committed labelling, which illegally labels all arguments in this set. Instead, our second non-naïve characterisation defines a responsible set of arguments as a minimal set containing at least one illegally labelled argument with respect to everyin –out labelling that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Definition 5">
       Labelling-based characterisation 3{a mathematical formula}Args⊆Ar is a preventing set w.r.t. {a mathematical formula}LabArgpref if and only if it is a minimal set of arguments (w.r.t. ⊆) such that
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}Args⊆undec(LabArgpref)
       </list-item>
       <list-item>
        and {a mathematical formula}∀LabArg of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅
       </list-item>
       <list-item>
        it holds that {a mathematical formula}∃A∈Args such that A is illegally labelled by {a mathematical formula}LabArg.
       </list-item>
      </list>
      <paragraph label="Example 12">
       Consider {a mathematical formula}AFtherapy and its only preferred labelling {a mathematical formula}LabArgpref (see Example 8 on page 308 and Fig. 1 on page 302). The only preventing set w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}{A,B,C}, since no matter how the labels in and out are assigned to this set of arguments, at least one argument is illegally labelled. In contrast, for all subsets there exists some in –out labelling that legally labels all arguments. For instance, for the set {a mathematical formula}{A,B}, an in –out labelling that labels A as in and B and C as out legally labels both A and B.
      </paragraph>
      <paragraph>
       Note that in contrast to the definition of enforcement sets, we only consider labellings that are more committed than {a mathematical formula}LabArgpref in the definition of preventing sets. This is because for enforcement sets {a mathematical formula}LabArgpref itself can be an enforcement labelling (if it is a stable labelling), whereas for preventing sets {a mathematical formula}LabArgpref needs to be excluded as a labelling having illegally labelled arguments if it is a stable labelling.
      </paragraph>
      <paragraph label="Lemma 8">
       As for enforcement sets, at least one preventing set exists w.r.t. {a mathematical formula}LabArgpref and preventing sets are always non-empty if {a mathematical formula}LabArgpref is not a stable labelling. Preventing sets have the following properties:
      </paragraph>
      <list>
       <list-item label="1.">
        There exists a preventing set w.r.t.{a mathematical formula}LabArgpref.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Args=∅is a preventing set w.r.t.{a mathematical formula}LabArgprefif and only if{a mathematical formula}LabArgprefis a stable labelling.
       </list-item>
      </list>
      <paragraph>
       Note that, analogously to enforcement sets, if {a mathematical formula}Args=∅ is a preventing set w.r.t. {a mathematical formula}LabArgpref, it is the only preventing set w.r.t. {a mathematical formula}LabArgpref.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Responsibility of preventing sets
       </section-title>
       <paragraph>
        Theorem 9 illustrates the reason for naming our third labelling-based characterisation “preventing sets”: all revisions w.r.t. a set of arguments not comprising any argument from some preventing set have no stable labelling that is more committed than {a mathematical formula}LabArgpref. Thus, preventing sets define a sufficient condition for “preventing” the existence of a stable labelling that is more committed than {a mathematical formula}LabArgpref.
       </paragraph>
       <paragraph label="Theorem 9">
        Let{a mathematical formula}Args⊆Ar∖Argsprevwhere{a mathematical formula}Argsprevis a preventing set w.r.t.{a mathematical formula}LabArgpref. Then, for all labellings{a mathematical formula}LabArgof{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊏LabArgand{a mathematical formula}undec(LabArg)=∅, there exists no revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgsuch that some revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
       </paragraph>
       <paragraph label="Proof">
        Assume there exists a revision {a mathematical formula}AF⊛ of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg and a revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ such that {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛. By Definition 5, {a mathematical formula}∃A∈Argsprev such that A is illegally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF. Since {a mathematical formula}A∈Ar∖Args, it follows from Lemma 37 in Appendix A that A is illegally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Contradiction.  □
       </paragraph>
       <paragraph label="Example 13">
        Recall {a mathematical formula}AF3, depicted on the left of Fig. 9 (see page 309), and its only preferred labelling {a mathematical formula}LabArgpref, which labels all arguments as undec. There are two preventing sets w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{a,b,c} and {a mathematical formula}{e}. Consider the preventing set {a mathematical formula}{e} and some in –out labelling of {a mathematical formula}AF3, e.g. {a mathematical formula}LabArg illustrated on the left of Fig. 9. In order to ensure that e is legally labelled by {a mathematical formula}LabArg, an attack on e from some argument labelled in has to be added (e.g. as illustrated on the right of Fig. 9). Conversely, if e was labelled in by an in –out labelling, the self-attack of e would have to be deleted in order to ensure that e was legally labelled. Thus, no revision w.r.t. a set of arguments not containing e can result in e being legally labelled.
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Enforcement versus preventing sets
      </section-title>
      <paragraph>
       Theorem 6, Theorem 9 hint at a connection between enforcement and preventing sets: one provides a sufficient condition for the existence of a stable labelling after revision, the other a sufficient condition for the non-existence. In this section, we investigate the relationship between enforcement and preventing sets in more detail.
      </paragraph>
      <paragraph>
       We first show that a preventing set is a minimal set containing at least one argument from each enforcement set (if non-empty enforcement sets exist).
      </paragraph>
      <paragraph label="Theorem 10">
       Let{a mathematical formula}Senfbe the set of all enforcement sets w.r.t.{a mathematical formula}LabArgpref. Then{a mathematical formula}S={Args⊆Ar|Argsis a minimal set satisfying that∀Argsenf≠∅∈Senf:Args∩Argsenf≠∅}is the set of all preventing sets w.r.t.{a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Proof">
       We prove that all {a mathematical formula}Args∈S are preventing sets and that all preventing sets are contained in S. We note that, by Lemma 5, {a mathematical formula}Senf≠∅. If {a mathematical formula}Senf={∅} then {a mathematical formula}S={∅}. By Lemma 5{a mathematical formula}LabArgpref is a stable labelling and by Lemma 8 the empty set is the only preventing set. If {a mathematical formula}Senf≠{∅} then {a mathematical formula}∀Argsenf∈Senf: {a mathematical formula}Argsenf≠∅ and {a mathematical formula}LabArgpref is not a stable labelling.
      </paragraph>
      <list>
       <list-item label="•">
        Let {a mathematical formula}Args∈S and assume that {a mathematical formula}Args is not a preventing set. Then either {a mathematical formula}Args is not a minimal set satisfying the conditions in Definition 5 or {a mathematical formula}Args does not satisfy the conditions at all.
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}Argsprev be a preventing set and assume that {a mathematical formula}Argsprev∉S. Then either {a mathematical formula}∃Argsenf∈Senf such that {a mathematical formula}Argsprev∩Argsenf=∅ or there exists a minimal set {a mathematical formula}Args⊂Argsprev satisfying that {a mathematical formula}Args∩Argsenf≠∅ for all {a mathematical formula}Argsenf∈Senf.
       </list-item>
      </list>
      <paragraph label="Example 14">
       From Example 10, we know that for {a mathematical formula}AF3 the set of all enforcement sets is {a mathematical formula}Senf={{a,e},{b,e},{c,e}}. Then both {a mathematical formula}{a,b,c} and {a mathematical formula}{e} are minimal sets containing an argument from each enforcement set. Indeed, {a mathematical formula}{a,b,c} and {a mathematical formula}{e} are the two preventing sets w.r.t. {a mathematical formula}LabArgpref of {a mathematical formula}AF3 (see Example 13).
      </paragraph>
      <paragraph>
       Conversely, an enforcement set is a minimal set containing at least one argument from each preventing set (if non-empty preventing sets exist).
      </paragraph>
      <paragraph label="Theorem 11">
       Let{a mathematical formula}Sprevthe set of all preventing sets w.r.t.{a mathematical formula}LabArgpref. Then{a mathematical formula}S={Args⊆Ar|Argsis a minimal set satisfying that∀Argsprev≠∅∈Sprev:Args∩Argsprev≠∅}is the set of all enforcement sets w.r.t.{a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Proof">
       Analogous to the proof of Theorem 10, see Appendix B.  □
      </paragraph>
      <paragraph label="Example 15">
       From Example 13, we know that {a mathematical formula}Sprev={{a,b,c},{e}} for {a mathematical formula}AF3. Then {a mathematical formula}{a,e}, {a mathematical formula}{b,e}, and {a mathematical formula}{c,e} are all the minimal sets containing an argument from each preventing set. Indeed, these three sets are the enforcement sets of {a mathematical formula}AF3 w.r.t. {a mathematical formula}LabArgpref (see Example 10 on page 309).
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Necessary conditions for the (non-)existence of stable labellings
      </section-title>
      <paragraph>
       Based on the correspondence results between enforcement and preventing sets, we now further investigate their responsibility regarding a non-stable preferred labelling {a mathematical formula}LabArgpref. We prove that both enforcement and preventing sets define not only sufficient but also necessary conditions for the existence and non-existence, respectively, of a stable labelling (of a revision) that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       Concerning enforcement sets, Theorem 12 proves that in order to obtain a stable labelling (through a revision) that is more committed than {a mathematical formula}LabArgpref, the labels of all arguments in some enforcement set have to be enforced for sure. Enforcement sets thus provide a necessary condition for obtaining a stable labelling (of a revision) that is more committed than {a mathematical formula}LabArgpref. It follows that all arguments in an enforcement set are responsible that the given preferred labelling is not stable, in other words, the enforcement set does not comprise non-responsible arguments.
      </paragraph>
      <paragraph label="Theorem 12">
       Let{a mathematical formula}Args⊆Arand let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊑LabArg,{a mathematical formula}undec(LabArg)=∅, and there exists a revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand a revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛. Then there exists an enforcement set{a mathematical formula}Argsenfw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}Argsenf⊆Args.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}LabArgpref is a stable labelling then the only more or equally committed labelling is {a mathematical formula}LabArgpref itself. Thus, for any set {a mathematical formula}Args⊆Ar it holds that there exists a revision {a mathematical formula}AF⊛=AF of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg=LabArgpref and a revision labelling {a mathematical formula}LabArg⊛=LabArgpref of {a mathematical formula}AF⊛=AF such that {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛. By Lemma 5, the only enforcement set is the empty set, so it holds that {a mathematical formula}Argsenf⊆Args. Let {a mathematical formula}LabArgpref be a non-stable preferred labelling and let {a mathematical formula}Args⊆Ar. By (the contrapositive of) Theorem 9 it holds that: if there exists a labelling {a mathematical formula}LabArg of {a mathematical formula}AF such that {a mathematical formula}LabArgpref⊏LabArg, {a mathematical formula}undec(LabArg)=∅, and there exists a revision {a mathematical formula}AF⊛ of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg and a revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ such that {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛, then {a mathematical formula}Args⊈Ar∖Argsprev where {a mathematical formula}Argsprev is a preventing set w.r.t. {a mathematical formula}LabArgpref. Thus, {a mathematical formula}∃A∈Args such that {a mathematical formula}A∉Ar∖Argsprev, and consequently {a mathematical formula}A∈Argsprev. Since this holds for all preventing sets {a mathematical formula}Argsprev, let {a mathematical formula}Args′ be the set of all such {a mathematical formula}A∈Args that are part of a preventing set, so {a mathematical formula}Args′ consists of at least one argument from each preventing set. By Theorem 11, {a mathematical formula}Argsenf⊆Args′, where {a mathematical formula}Argsenf is an enforcement set, and since {a mathematical formula}Args′⊆Args, it follows that {a mathematical formula}Argsenf⊆Args.  □
      </paragraph>
      <paragraph label="Example 16">
       Consider {a mathematical formula}AF4 and its only preferred labelling {a mathematical formula}LabArgpref, illustrated at the left of Fig. 10. Let {a mathematical formula}LabArg be the labelling illustrated at the right of Fig. 10 and let {a mathematical formula}Args={d,g}. Then {a mathematical formula}AF4⊛ at the left of Fig. 11 is a revision of {a mathematical formula}AF4 w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg, where the labelling {a mathematical formula}LabArg⊛ at the left of Fig. 11 is a revision labelling of {a mathematical formula}AF4⊛. We note that {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛. As stated by Theorem 12, {a mathematical formula}Args is a superset of some enforcement set, in fact, it is a superset of both enforcement set {a mathematical formula}{d} and enforcement set {a mathematical formula}{g}.
      </paragraph>
      <paragraph>
       Note that even if a set of arguments used to revise an AF is a superset of an enforcement set, the labelling used for the revision may be different from all enforcement labellings of this enforcement set. For example, {a mathematical formula}LabArg from Example 16 (see right of Fig. 10) is used for the revision of {a mathematical formula}AF4 w.r.t. {a mathematical formula}Args, but it is not an enforcement labelling of either of the two enforcement sets that are subsets of {a mathematical formula}Args. For instance, the only enforcement labelling of the enforcement set {a mathematical formula}{d} is illustrated at the right of Fig. 11.
      </paragraph>
      <paragraph>
       The next Corollary follows directly from Theorem 12 and states that the converse of Theorem 6 holds.
      </paragraph>
      <paragraph label="Corollary 13">
       Let{a mathematical formula}Args⊆Arand let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊑LabArg,{a mathematical formula}undec(LabArg)=∅, and for all revisions{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand all revision labellings{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛it holds that{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛. Then there exists an enforcement set{a mathematical formula}Argsenfw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}Argsenf⊆Args.
      </paragraph>
      <paragraph>
       Theorem 14 proves that the converse of Theorem 9 holds. That is, if no revision w.r.t. a set of arguments {a mathematical formula}Args is such that some revision labelling is a stable labelling of the revision, then there exists a preventing set that is disjoint from {a mathematical formula}Args. In other words, preventing sets define a necessary condition for the non-existence of a stable labelling that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Theorem 14">
       Let{a mathematical formula}Args⊆Arbe such that, for all labellings{a mathematical formula}LabArgof{a mathematical formula}AFwith{a mathematical formula}LabArgpref⊏LabArgand{a mathematical formula}undec(LabArg)=∅, there exists no revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgsuch that some revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛is a stable labelling of{a mathematical formula}AF⊛. Then there exists a preventing set{a mathematical formula}Argsprevw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}Args⊆Ar∖Argsprev.
      </paragraph>
      <paragraph label="Proof">
       Since {a mathematical formula}LabArgpref⊏LabArg it follows that {a mathematical formula}LabArgpref is not a stable labelling. Let {a mathematical formula}Args⊆Ar. By (the contrapositive of) Corollary 7 it holds that: if for all labellings {a mathematical formula}LabArg of {a mathematical formula}AF such that {a mathematical formula}LabArgpref⊑LabArg and {a mathematical formula}undec(LabArg)=∅, there exists no revision {a mathematical formula}AF⊛ of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg such that some revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ is a stable labelling of {a mathematical formula}AF⊛, then {a mathematical formula}Args⊉Argsenf where {a mathematical formula}Argsenf is an enforcement set. Thus, {a mathematical formula}∃A∈Argsenf such that {a mathematical formula}A∉Args. Since this holds for all enforcement sets {a mathematical formula}Argsenf, let {a mathematical formula}Args′ be the set of all such A occurring in some enforcement set such that {a mathematical formula}A∉Args, so {a mathematical formula}Args′ consists of at least one argument from each enforcement set. By Theorem 10, {a mathematical formula}Args′⊇Argsprev where {a mathematical formula}Argsprev is a preventing set. Clearly, {a mathematical formula}Args⊆Ar∖Args′, so {a mathematical formula}Args⊆Ar∖Argsprev where {a mathematical formula}Argsprev is a preventing set.  □
      </paragraph>
      <paragraph label="Example 17">
       Consider again {a mathematical formula}AF3=〈Ar3,Att3〉 illustrated on the left of Fig. 9 (see page 309) and the set of arguments {a mathematical formula}Args={c,d}. Then, for any in –out labelling {a mathematical formula}LabArg of {a mathematical formula}AF3 that is more committed than {a mathematical formula}LabArgpref, there exists no revision {a mathematical formula}AF3⊛ of {a mathematical formula}AF3 w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg such that a revision labelling of {a mathematical formula}AF3⊛ is a stable labelling of {a mathematical formula}AF3⊛, since any revision labelling will illegally label e (as no attacks can be added to or deleted from e). As stated by Theorem 14, it holds that for the preventing set {a mathematical formula}{e}, {a mathematical formula}Args⊂Ar3∖{e}.
      </paragraph>
      <paragraph>
       Note that the correspondence between preventing and enforcement sets implies that, for a revision w.r.t. a set of arguments comprising an argument from each preventing set, there exists a revision whose revision labelling is a stable labelling (of the revision). Thus, a revision w.r.t. the union of all preventing sets by an appropriately chosen labelling is a sufficient condition for obtaining a stable labelling (of the revision) that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       Theorem 6, Theorem 12 as well as Theorem 9, Theorem 14 show that enforcement and preventing sets indeed characterise exactly those sets of arguments responsible if a preferred labelling is not a stable labelling. Enforcement sets are responsible since they consist of exactly the arguments whose labels need to be enforced in order to obtain a stable labelling (of a revision), whereas preventing sets are responsible because they consist of exactly those arguments that prevent the existence of a stable labelling (of a revision) if the label of no argument in the set is enforced.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Structural characterisations
     </section-title>
     <paragraph>
      Determining responsible sets of arguments according to the declarative labelling-based characterisations from Section 4 involves guessing sets of arguments and checking if they satisfy the respective definition. In this section, we instead characterise sets of arguments as responsible if a preferred labelling is not a stable labelling based on the structure of the AF. We thereby aim at characterisations that allow for a constructive determination of responsible sets of arguments.
     </paragraph>
     <section label="5.1">
      <section-title>
       Odd-length cycles
      </section-title>
      <paragraph>
       Our first structural characterisation is inspired by the seminal work of Dung [10], who proved that if an AF has no odd-length cycles, then a stable extension – and thus a stable labelling{sup:5} – exists. Consequently, the non-existence of stable labellings implies the existence of an odd-length cycle.
      </paragraph>
      <paragraph>
       We show that, furthermore, an odd-length cycle exists if some preferred labelling is not stable, even if the AF has a stable labelling. In particular, there exists an odd-length cycle of arguments labelled undec by this (non-stable) preferred labelling. Thus, we define such odd-length cycles of arguments labelled undec as responsible if the preferred labelling is not stable. The reason to exclude odd-length cycles of arguments labelled in or out is that such cycles do not violate the definition of a stable labelling.
      </paragraph>
      <paragraph label="Definition 6">
       Structural characterisation 1{a mathematical formula}C⊆Ar is a responsible cycle w.r.t. {a mathematical formula}LabArgpref if and only if {a mathematical formula}C is an odd-length cycle of {a mathematical formula}AF and for all {a mathematical formula}A∈C it holds that {a mathematical formula}A∈undec(LabArgpref).
      </paragraph>
      <paragraph label="Example 18">
       Let {a mathematical formula}AF5 be the AF illustrated in Fig. 12 and let {a mathematical formula}LabArgpref be its only preferred labelling, also depicted in the figure. {a mathematical formula}AF5 has five odd-length cycles, including nested ones: the odd-length cycle {a mathematical formula}{d,e,f} contains the two odd-length cycles {a mathematical formula}{d} and {a mathematical formula}{e}. However, only the two odd-length cycles {a mathematical formula}C1={c} and {a mathematical formula}C2={e} are responsible cycles w.r.t. {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       In contrast to our labelling-based characterisations, which always exist but coincide with the empty set in case {a mathematical formula}LabArgpref is a stable labelling, responsible cycles exist if and only if {a mathematical formula}LabArgpref is not stable. Thus, responsible cycles are well-defined characterisations of parts of an AF responsible if {a mathematical formula}LabArgpref is not a stable labelling.
      </paragraph>
      <paragraph label="Proposition 15">
       There exists a responsible cycle w.r.t.{a mathematical formula}LabArgprefif and only if{a mathematical formula}LabArgprefis not a stable labelling.
      </paragraph>
      <paragraph>
       We are again interested in characterising our responsible parts as indeed being responsible that {a mathematical formula}LabArgpref is not stable. The following proposition states that it is sufficient to consider the set of all responsible cycles to obtain a stable labelling by enforcing labels for arguments in the responsible cycles. Importantly, to obtain a stable labelling (of a revision) that is more or equally committed than {a mathematical formula}LabArgpref, the labelling used for the revision has to be chosen carefully.
      </paragraph>
      <paragraph label="Proposition 16">
       Let{a mathematical formula}S={A∈Ar|Cis a responsible cycle w.r.t.LabArgpref,A∈C}. Then there exists a labelling{a mathematical formula}LabArgof{a mathematical formula}AFwith{a mathematical formula}LabArgpref⊑LabArgand{an inline-figure}such that, for all revisions{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t. S by{a mathematical formula}LabArgand all revision labellings{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛,{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
      </paragraph>
      <paragraph>
       Note that this also holds if {a mathematical formula}LabArgpref is a stable labelling, in which case {a mathematical formula}S=∅, {a mathematical formula}LabArg=LabArg⊛=LabArgpref, and {a mathematical formula}AF⊛=AF.
      </paragraph>
      <paragraph label="Example 19">
       Consider again {a mathematical formula}AF4 illustrated at the left of Fig. 10 (see page 313). The set of arguments occurring in responsible cycles w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}S={d,g}. Consider the labelling {a mathematical formula}LabArg depicted at the rigth of Fig. 10, which is more committed than {a mathematical formula}LabArgpref and labels no arguments as undec. A revision {a mathematical formula}AF4⊛ of {a mathematical formula}AF4 w.r.t. S by {a mathematical formula}LabArg is shown at the left of Fig. 11, along with a revision labelling that is a stable labelling of {a mathematical formula}AF4⊛.
      </paragraph>
      <paragraph>
       Since by Lemma 1 a revision exists w.r.t. any set of arguments and any labelling, it follows that there indeed exists a revision w.r.t. responsible cycles that has a stable labelling that is more committed than the given non-stable preferred labelling.
      </paragraph>
      <paragraph label="Corollary 17">
       Let{a mathematical formula}S={A∈Ar|Cis a responsible cycle w.r.t.LabArgpref,A∈C}. Then there exists a labelling{a mathematical formula}LabArgof{a mathematical formula}AFwith{a mathematical formula}LabArgpref⊑LabArgand{a mathematical formula}undec(LabArg)=∅, and there exists a revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t. S by{a mathematical formula}LabArgand a revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArg⊛is a stable labelling of{a mathematical formula}AF⊛.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Strongly connected components
      </section-title>
      <paragraph>
       Our second structural characterisation is based upon a result on the composition of stable labellings, namely that stable labellings can be computed along the SCCs [16] of the AF. That is, the stable labellings of initial SCCs are computed and, subsequently, the stable labellings of the following SCCs are iteratively determined, while taking the labels of arguments in their parent SCCs into account. It follows that if the AF has no stable labelling, some SCC in this iterative computation has no stable labelling (when taking the labels in parent SCCs into account).
      </paragraph>
      <paragraph>
       The following structural characterisation of sets of arguments responsible if {a mathematical formula}LabArgpref is not a stable labelling refines this observation. It defines as responsible the “first” SCCs that have no stable labelling in the iterative computation of a stable labelling, given the labels of {a mathematical formula}LabArgpref. More precisely, responsible sets are SCCs satisfying that: 1) the SCC has no stable labelling w.r.t. the input from its parent SCCs, i.e. w.r.t. the labels of attackers in parent SCCs according to {a mathematical formula}LabArgpref; and 2) all parent SCCs have a stable labelling w.r.t. the input from their parent SCCs that coincides with the labels assigned by {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Definition 7">
       Structural characterisation 2{a mathematical formula}Args⊆Ar is a responsible SCC w.r.t. {a mathematical formula}LabArgpref if and only if {a mathematical formula}Args is an SCC of {a mathematical formula}AF such that
      </paragraph>
      <list>
       <list-item label="1.">
        there exists no stable labelling w.r.t. {a mathematical formula}(AF↓Args,parents(Args),LabArgpref↓parents(Args),Att∩(parents(Args)×Args)) that is more or equally committed than {a mathematical formula}LabArgpref↓Args, and
       </list-item>
       <list-item label="2.">
        for all {a mathematical formula}Args′∈parentSCCs(Args), {a mathematical formula}LabArgpref↓Args′ is a stable labelling w.r.t. {a mathematical formula}(AF↓Args′,parents(Args′),LabArgpref↓parents(Args′),Att∩(parents(Args′)×Args′)).
       </list-item>
      </list>
      <paragraph label="Example 20">
       The only responsible SCC of {a mathematical formula}AFtherapy w.r.t. its only preferred labelling {a mathematical formula}LabArgpref (see Fig. 1 on page 302) is {a mathematical formula}{A,B,C}. Since this is an initial SCC, it is trivially satisfied that its parent SCCs have a stable labelling.
      </paragraph>
      <paragraph>
       The following example illustrates an AF where a responsible SCC is not an initial SCC of the AF.
      </paragraph>
      <paragraph label="Example 21">
       Consider again {a mathematical formula}AF4 and its only preferred labelling {a mathematical formula}LabArgpref, illustrated at the left of Fig. 10 (see page 313). The only responsible SCC w.r.t. {a mathematical formula}LabArgpref is the SCC {a mathematical formula}{b,c,d,e,f,g,h} since: 1) there exists no stable labelling w.r.t. the AF with input {a mathematical formula}(AF↓{b,c,d,e,f,g,h},{a},{(a,in)},{(a,b)}), which is depicted in Fig. 13; and 2) {a mathematical formula}{b,c,d,e,f,g,h} only has one parent SCC, namely {a mathematical formula}{a}, and {a mathematical formula}LabArgpref restricted to {a mathematical formula}{a}, i.e. {a mathematical formula}{(a,in)}, is a stable labelling w.r.t. {a mathematical formula}(AF↓{a},∅,∅,∅).
      </paragraph>
      <paragraph>
       Note that Definition 7 does not require a responsible SCC to not have a stable labelling at all (w.r.t. its parent SCCs), but rather that it has no stable labelling that is more committed than the labels assigned to the SCC by {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Example 22">
       Let {a mathematical formula}AF6 be the AF in Fig. 14, which has no stable labelling, and consider the depicted preferred labelling {a mathematical formula}LabArgpref. {a mathematical formula}AF6 has three SCCs, namely {a mathematical formula}{a,b,c}, {a mathematical formula}{d}, and {a mathematical formula}{e}. The SCC {a mathematical formula}{a,b,c}has a stable labelling w.r.t. {a mathematical formula}(AF↓{a,b,c},∅,∅,∅), namely {a mathematical formula}{(a,out),(b,in),(c,out)}, but this stable labelling is not more or equally committed than {a mathematical formula}LabArgpref↓{a,b,c}. This illustrates the importance of the comparison with {a mathematical formula}LabArgpref in the first condition of Definition 7: due to the comparison, {a mathematical formula}{a,b,c} satisfies the condition; without the comparison, {a mathematical formula}{a,b,c} would not satisfy the condition. Thus, without the comparison {a mathematical formula}{a,b,c} would not be identified as a responsible SCC. However, {a mathematical formula}{a,b,c} should be identified as responsible since it is the “first” SCC that provides a reason why {a mathematical formula}LabArgpref is not a stable labelling.Of similar importance is the comparison with {a mathematical formula}LabArgpref in the second condition of Definition 7. Consider the SCC {a mathematical formula}{d} and its parent SCC {a mathematical formula}{a,b,c}. {a mathematical formula}{a,b,c}has a stable labelling w.r.t. {a mathematical formula}(AF↓{a,b,c},∅,∅,∅), namely {a mathematical formula}{(a,out),(b,in),(c,out)}, so without the comparison with {a mathematical formula}LabArgpref, {a mathematical formula}{d} would be identified as a responsible SCC. However, since the stable labelling w.r.t. {a mathematical formula}(AF↓{a,b,c},∅,∅,∅) does not coincide with {a mathematical formula}LabArgpref↓{a,b,c}, {a mathematical formula}{d} is not a responsible SCC.
      </paragraph>
      <paragraph>
       We prove that at least one responsible SCC exists if and only if the given preferred labelling is not stable.
      </paragraph>
      <paragraph label="Proposition 18">
       There exists a responsible SCC w.r.t.{a mathematical formula}LabArgprefif and only if{a mathematical formula}LabArgprefis not a stable labelling.
      </paragraph>
      <paragraph>
       Differently from our previous characterisations, we do not investigate the role of responsible SCCs w.r.t. the existence of a stable labelling (of a revision), since we do so for our next structural characterisation, which refines our definition of responsible SCCs.
      </paragraph>
     </section>
     <section label="5.3">
      Strongly connected undec parts (SCUPs)
      <paragraph>
       Our characterisation of responsible SCCs relies on the decomposability of stable labellings with regards to the SCCs of an AF. In this section, we refine this notion by using another decomposability result. Baroni et al. [18] show that the complete labellings of an AF can be obtained by splitting the AF into any partition and then determining complete labellings of the different parts in such a way that they are compatible. We can thus think of {a mathematical formula}LabArgpref as a combination of two compatible labellings: a labelling of the part of the AF whose arguments are labelled in or out by {a mathematical formula}LabArgpref, and a labelling of the part of the AF whose arguments are labelled undec by {a mathematical formula}LabArgpref. We call these two parts the in /out -part and the undec -part, respectively.
      </paragraph>
      <paragraph>
       The fact that all arguments in the undec -part are labelled undec by {a mathematical formula}LabArgpref implies that this is the only labelling compatible with the in and out labels in the in /out -part (if there was another labelling, {a mathematical formula}LabArgpref would not be maximal). Proposition 19 proves that, furthermore, labelling all arguments in the undec -part as undec is the only complete labelling of this part on its own (disregarding the in /out -part). In other words, the labels of arguments in the in /out -part are not responsible that all arguments in the undec -part are labelled undec. Rather, the structure of the undec -part itself is responsible that the arguments cannot be legally labelled in or out.
      </paragraph>
      <paragraph label="Proposition 19">
       Let{a mathematical formula}undec(LabArgpref)≠∅. The only complete labelling of{a mathematical formula}AF↓undec(LabArgpref)labels all arguments asundec.
      </paragraph>
      <paragraph>
       Since the undec -part has only one complete labelling, which labels all arguments as undec, this labelling is also its only preferred labelling. Thus, the question as to why {a mathematical formula}LabArgpref is not a stable labelling can be reduced to the question as to why the only preferred labelling of the undec -part is not a stable labelling.
      </paragraph>
      <paragraph>
       Applying our notion of responsible SCCs, we obtain that the preferred labelling of the undec -part is not a stable labelling because of its “first” SCCs that have no stable labelling. These “first” SCCs are the initial SCCs of the undec -part since no SCC in the undec -part has a stable labelling. This observation results in the following new characterisation of sets of arguments responsible if {a mathematical formula}LabArgpref is not a stable labelling: a set of arguments is responsible if it is an initial SCC of the undec -part.
      </paragraph>
      <paragraph label="Definition 8">
       Structural characterisation 3{a mathematical formula}Args⊆Ar is a strongly connectedundecpart (SCUP) w.r.t. {a mathematical formula}LabArgpref if and only if {a mathematical formula}Args is an initial SCC of {a mathematical formula}AF↓undec(LabArgpref).
      </paragraph>
      <paragraph label="Example 23">
       {a mathematical formula}AFtherapy from Section 1 has only one SCUP w.r.t. its only preferred labelling (see Fig. 1 on page 302), namely {a mathematical formula}{A,B,C}.
      </paragraph>
      <paragraph>
       Importantly, at least one SCUP exists w.r.t. a preferred labelling if and only if this preferred labelling is not stable, which shows that SCUPs provide a well-defined characterisation of responsible sets of arguments.
      </paragraph>
      <paragraph label="Proposition 20">
       There exists a SCUP w.r.t.{a mathematical formula}LabArgprefif and only if{a mathematical formula}LabArgprefis not stable.
      </paragraph>
      <paragraph>
       The following example illustrates that an AF may have various SCUPs w.r.t. a preferred labelling.
      </paragraph>
      <paragraph label="Example 24">
       Let {a mathematical formula}AF7 and its only preferred labelling {a mathematical formula}LabArgpref be as illustrated in Fig. 15. There are two SCUPs w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{c} and {a mathematical formula}{d}.
      </paragraph>
      <paragraph>
       We now prove that SCUPs are refinements of responsible SCCs in the sense that every responsible SCC comprises a SCUP.
      </paragraph>
      <paragraph label="Proposition 21">
       Let{a mathematical formula}Argsbe a responsible SCC w.r.t.{a mathematical formula}LabArgpref. Then{a mathematical formula}∃Args′⊆Argssuch that{a mathematical formula}Args′is a SCUP w.r.t.{a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Example 25">
       Consider again {a mathematical formula}AF4 and its only preferred labelling {a mathematical formula}LabArgpref illustrated at the left of Fig. 10 (see page 313). As discussed in Example 21, the only responsible SCC w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}{b,c,d,e,f,g,h}. As expected, there exists a SCUP that is a subset of this responsible SCC, namely {a mathematical formula}{c,d,e,f,g,h}, which is the only SCUP of {a mathematical formula}AF4 w.r.t. {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       Note that the converse of Proposition 21 does not hold in general, i.e. it is not the case that every SCUP is a subset of some responsible SCC. For example, {a mathematical formula}{d} is a SCUP of {a mathematical formula}AF7 w.r.t. {a mathematical formula}LabArgpref (see Fig. 15), but the SCC containing d, i.e. {a mathematical formula}{b,d}, is not a responsible SCC, since the parent SCC {a mathematical formula}{c} has no stable labelling.
      </paragraph>
      <paragraph>
       Even though SCUPs are defined based on the structure of the AF rather than based on labellings that are more committed than {a mathematical formula}LabArgpref, as our labelling-based characterisations, we prove that SCUPs constitute sets of arguments that cannot all be legally labelled in or out. More precisely, with respect to any in –out labelling that is more committed than {a mathematical formula}LabArgpref, at least one argument in every SCUP is illegally labelled. This indicates that SCUPs indeed characterise sets of arguments responsible if {a mathematical formula}LabArgpref is not a stable labelling.
      </paragraph>
      <paragraph label="Lemma 22">
       Let{a mathematical formula}Argsbe a SCUP w.r.t.{a mathematical formula}LabArgpref. Then, for all labellings{a mathematical formula}LabArgof{a mathematical formula}AFwith{a mathematical formula}LabArgpref⊏LabArgand{a mathematical formula}undec(LabArg)=∅, it holds that there exists{a mathematical formula}A∈Argssuch that A is illegally labelled by{a mathematical formula}LabArg.
      </paragraph>
      <paragraph>
       Since by Proposition 21 every responsible SCC comprises a SCUP, an analogous result to Lemma 22 also holds for responsible SCCs. That is, with respect to all in –out labellings that are more committed than {a mathematical formula}LabArgpref, at least one argument in every responsible SCC is illegally labelled.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Revising SCUPs
      </section-title>
      <paragraph>
       In this section, we investigate the responsibility of SCUPs in more detail, by examining revisions that turn {a mathematical formula}LabArgpref into a stable labelling (of the revision). We first prove that, as for preventing sets, SCUPs provide a sufficient condition for “preventing” the existence of a stable labelling that is more committed than {a mathematical formula}LabArgpref. That is, a revision w.r.t. a set of arguments not containing an argument from some SCUP will not yield a stable labelling that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Theorem 23">
       Let{a mathematical formula}Args⊆Ar∖ArgsSCUPwhere{a mathematical formula}ArgsSCUPis a SCUP w.r.t.{a mathematical formula}LabArgprefand let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AFsuch that{a mathematical formula}LabArgpref⊏LabArgand{a mathematical formula}undec(LabArg)=∅. Then there exists no revision{a mathematical formula}AF⊛of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgsuch that some revision labelling{a mathematical formula}LabArg⊛of{a mathematical formula}AF⊛is a stable labelling of{a mathematical formula}AF⊛.
      </paragraph>
      <paragraph label="Proof">
       Assume there exists a revision {a mathematical formula}AF⊛ of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg and a revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ such that {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛. By Lemma 22, {a mathematical formula}∃A∈ArgsSCUP such that A is illegally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF. Since {a mathematical formula}A∈Ar∖Args, by Lemma 37 in Appendix A, A is illegally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Contradiction.  □
      </paragraph>
      <paragraph label="Example 26">
       Consider again the SCUPs of {a mathematical formula}AF7 w.r.t. its only preferred labelling {a mathematical formula}LabArgpref (see Example 24 on page 317). Let {a mathematical formula}LabArg be the in –out labelling illustrated in Fig. 16, which is more committed than {a mathematical formula}LabArgpref. The set {a mathematical formula}{a,b,d,e} does not contain any argument from the SCUP {a mathematical formula}{c}. It is easy to see that there exists no revision {a mathematical formula}AF7⊛ of {a mathematical formula}AF7 w.r.t. {a mathematical formula}{a,b,d,e} by {a mathematical formula}LabArg such that a revision labelling is a stable labelling of {a mathematical formula}AF7⊛, since c will always be illegally labelled out.
      </paragraph>
      <paragraph>
       Therefore, if we are to obtain a stable labelling, a revision has to involve arguments from every SCUP. In what follows, we thus investigate whether enforcing labels for arguments in all SCUPs yields a stable labelling (of a revision). For this purpose, we define a SCUP revision as a revision w.r.t. the set of all arguments in all SCUPs by a labelling that is more committed than {a mathematical formula}LabArgpref and labels all arguments in all SCUPs as in or out. That is, a SCUP revision enforces the labels in and out for all arguments in all SCUPs.
      </paragraph>
      <paragraph label="Notation 2">
       Let {a mathematical formula}Args1,…,Argsn be all SCUPs w.r.t. {a mathematical formula}LabArgpref. {a mathematical formula}SCUPS=Args1∪…∪Argsn denotes the set of all arguments in SCUPs.
      </paragraph>
      <paragraph label="Definition 9">
       SCUP revision and SCUP revision labellingLet {a mathematical formula}LabArgSCUPS be a labelling of {a mathematical formula}AF↓SCUPS with {a mathematical formula}undec(LabArgSCUPS)=∅ and let {a mathematical formula}LabArg=LabArgSCUPS∪LabArgpref↓Ar∖SCUPS. {a mathematical formula}AF⊛ is a SCUP revision of {a mathematical formula}AF if and only if {a mathematical formula}AF⊛ is a revision of {a mathematical formula}AF w.r.t. {a mathematical formula}SCUPS by {a mathematical formula}LabArg. A revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ is called a SCUP revision labelling of {a mathematical formula}AF⊛.
      </paragraph>
      <paragraph label="Example 27">
       Consider again {a mathematical formula}AF7 from Example 24 (see Fig. 15 on page 317). A SCUP revision of {a mathematical formula}AF7 along with a SCUP revision labelling is depicted on the left of Fig. 17. The labelling of arguments in {a mathematical formula}SCUPS used for the SCUP revision is {a mathematical formula}LabArgSCUPS={(c,out),(d,in)}.
      </paragraph>
      <paragraph>
       Since, by Lemma 1, a revision exists w.r.t. any set of arguments and labelling and since, by Proposition 20, there exists a SCUP w.r.t. a preferred labelling if and only if it is not stable, the following holds.
      </paragraph>
      <paragraph label="Corollary 24">
       There exists a SCUP revision{a mathematical formula}AF⊛of{a mathematical formula}AFif and only if{a mathematical formula}LabArgprefis not a stable labelling.
      </paragraph>
      <paragraph>
       The SCUP revision from Example 27 illustrates that a SCUP revision labelling may not be a complete labelling of the SCUP revision since arguments labelled undec by {a mathematical formula}LabArgpref that are not contained in {a mathematical formula}SCUPS may be illegally labelled (see the left of Fig. 17). However, we prove that there exists a preferred labelling of the SCUP revision that is more or equally committed than the SCUP revision labelling. In other words, illegally labelled undec arguments can be appropriately changed to in or out labels, yielding a preferred labelling of the SCUP revision.
      </paragraph>
      <paragraph label="Theorem 25">
       Let{a mathematical formula}AF⊛be a SCUP revision of{a mathematical formula}AFand{a mathematical formula}LabArg⊛a SCUP revision labelling of{a mathematical formula}AF⊛. Then there exists a preferred labelling{a mathematical formula}LabArgpref⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArg⊛⊑LabArgpref⊛.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}SCUPS⊛={A∈Ar⊛|A∈SCUPS∨A∉Ar}. Let {a mathematical formula}Args1=in(LabArgpref)∪out(LabArgpref)∪SCUPS⊛, {a mathematical formula}Args2=Ar⊛∖Args1, and {a mathematical formula}LabArg1=LabArg⊛↓Args1.By Definition 9, Definition 1 it holds that {a mathematical formula}∀A∈SCUPS⊛, A is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Since {a mathematical formula}SCUPS consists of arguments in SCUPs, it holds that {a mathematical formula}∀A∈SCUPS⊛ and ∀B attacking A in {a mathematical formula}AF⊛, {a mathematical formula}B∈Args1. Thus, A being legally labelled by {a mathematical formula}LabArg⊛ only depends on {a mathematical formula}LabArg1. Let {a mathematical formula}LabArg2 be some labelling of {a mathematical formula}Args2. Then, {a mathematical formula}∀A∈SCUPS⊛, A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF⊛. Note that for any {a mathematical formula}LabArg2 of {a mathematical formula}Args2 it holds that {a mathematical formula}LabArg⊛↓Args2⊑LabArg2 since {a mathematical formula}undec(LabArg⊛↓Args2)=Args2, because {a mathematical formula}Args2⊆undec(LabArgpref)∖SCUPS. Then {a mathematical formula}LabArg⊛⊑LabArg1∪LabArg2.Let {a mathematical formula}LabArg=LabArgSCUPS∪LabArgpref↓Ar∖SCUPS be the labelling used for the SCUP revision. By Lemma 38 in Appendix A, {a mathematical formula}∀A∈in(LabArgpref)∪out(LabArgpref) it holds that A is legally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF since {a mathematical formula}LabArgpref⊏LabArg. Then, by Lemma 37 in Appendix A, {a mathematical formula}∀A∈in(LabArgpref)∪out(LabArgpref) it holds that A is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Since {a mathematical formula}LabArg⊛⊑LabArg1∪LabArg2, by Lemma 38 in Appendix A it holds that {a mathematical formula}∀A∈in(LabArgpref)∪out(LabArgpref), A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF⊛.Thus, {a mathematical formula}∀A∈Args1, A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF⊛. Then, by Lemma 43 in Appendix A, {a mathematical formula}LabArg1 is compatible with {a mathematical formula}LabArg2 (for any labelling {a mathematical formula}LabArg2 of {a mathematical formula}Args2). Furthermore by Lemma 45 in Appendix A, there exists a labelling {a mathematical formula}LabArg2′ that is compatible with {a mathematical formula}LabArg1. Then, by Lemma 40 in Appendix A, {a mathematical formula}LabArg1∪LabArg2′ is a complete labelling of {a mathematical formula}AF⊛. Then either {a mathematical formula}LabArg1∪LabArg2′ is a preferred labelling of {a mathematical formula}AF⊛ or there exists a preferred labelling {a mathematical formula}LabArg⊛′ such that {a mathematical formula}LabArg1∪LabArg2′⊏LabArg⊛′ and thus {a mathematical formula}LabArg⊛⊏LabArg⊛′.  □
      </paragraph>
      <paragraph label="Example 28">
       Given the SCUP revision {a mathematical formula}AF7⊛ and the SCUP revision labelling {a mathematical formula}LabArg⊛ from Example 27 (see left of Fig. 17), there exists a preferred labelling of {a mathematical formula}AF7⊛ that is more committed than {a mathematical formula}LabArg⊛, as illustrated on the right of Fig. 17.
      </paragraph>
      <paragraph>
       Since a SCUP revision labelling is more committed than {a mathematical formula}LabArgpref (because all arguments in SCUPs are labelled in or out by the SCUP revision labelling, but are labelled undec by {a mathematical formula}LabArgpref), it follows that there exists a preferred labelling of the SCUP revision that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Corollary 26">
       Let{a mathematical formula}AF⊛be a SCUP revision of{a mathematical formula}AF. Then there exists a preferred labelling{a mathematical formula}LabArgpref⊛of{a mathematical formula}AF⊛such that{a mathematical formula}LabArgpref⊏LabArgpref⊛.
      </paragraph>
      <paragraph>
       In Example 28, there exists a preferred labelling of the SCUP revision that is more committed than the SCUP revision labelling and that is also a stable labelling of the SCUP revision. However, in general a SCUP revision may not have a stable labelling that is more committed than the SCUP revision labelling.
      </paragraph>
      <paragraph label="Example 29">
       Let {a mathematical formula}AF8 and its only preferred labelling {a mathematical formula}LabArgpref be as illustrated at the top of Fig. 18. There are two SCUPs w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{a} and {a mathematical formula}{e}. A SCUP revision {a mathematical formula}AF8⊛ of {a mathematical formula}AF8 is depicted at the bottom of Fig. 18, along with the SCUP revision labelling. A preferred labelling {a mathematical formula}LabArgpref⊛ of {a mathematical formula}AF8⊛ that is more committed than the revision labelling is illustrated in Fig. 19. However, {a mathematical formula}LabArgpref⊛ is not a stable labelling of {a mathematical formula}AF8⊛. Furthermore, in this example there exist no SCUP revision and SCUP revision labelling that result in a stable labelling that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       To summarise, differently from preventing sets, revisions w.r.t. the union of all SCUPs are not guaranteed to have a stable labelling that is more committed than {a mathematical formula}LabArgpref. Nevertheless, they yield a more committed preferred labelling.
      </paragraph>
      <paragraph>
       If a SCUP revision has a preferred labelling that is not a stable labelling, then by Proposition 20 there exists a SCUP w.r.t. this preferred labelling. In order to obtain a stable labelling of the whole AF, these “new” SCUPs thus have to be revised. We therefore define an iterative procedure of SCUP revisions w.r.t. preferred labellings, which can be used to obtain a stable labelling (of a revision). As for preventing sets, this shows the responsibility of SCUPs, since it provides a sufficient condition for obtaining a stable labelling.
      </paragraph>
      <paragraph label="Definition 10">
       Iterative SCUP revisionA sequence {a mathematical formula}〈AF1,LabArg1〉,…,〈AFn,LabArgn〉 ({a mathematical formula}n&gt;1) is an iterative SCUP revision of {a mathematical formula}AF if and only if
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}AF1=AF and {a mathematical formula}LabArg1=LabArgpref, and
       </list-item>
       <list-item label="•">
        ∀i ({a mathematical formula}1≤i&lt;n) it holds that {a mathematical formula}AFi+1 is a SCUP revision of {a mathematical formula}AFi, with {a mathematical formula}LabArg⊛i+1 a SCUP revision labelling of {a mathematical formula}AFi+1, and {a mathematical formula}LabArgi+1 is a preferred labelling of {a mathematical formula}AFi+1 such that {a mathematical formula}LabArg⊛i+1⊑LabArgi+1.
       </list-item>
      </list>
      <paragraph>
       We are, of course, most interested in iterative SCUP revisions that result in a stable labelling.
      </paragraph>
      <paragraph label="Definition 11">
       Stable iterative SCUP revisionAn iterative SCUP revision {a mathematical formula}〈AF1,LabArg1〉,…,〈AFn,LabArgn〉 of {a mathematical formula}AF is a stable iterative SCUP revision of {a mathematical formula}AF if and only if {a mathematical formula}LabArgn is a stable labelling of {a mathematical formula}AFn.
      </paragraph>
      <paragraph label="Example 30">
       Consider again {a mathematical formula}AF8 and its preferred labelling, illustrated at the top of Fig. 18. An example of a stable iterative SCUP revision of {a mathematical formula}AF8 is {a mathematical formula}〈AF81,LabArg1〉,〈AF82,LabArg2〉,〈AF83,LabArg3〉, where {a mathematical formula}AF82 and {a mathematical formula}LabArg2 are depicted in Fig. 12, and {a mathematical formula}AF83 and {a mathematical formula}LabArg3 are as illustrated in Fig. 19.
      </paragraph>
      <paragraph>
       Since a SCUP revision has a preferred labelling that is more committed than {a mathematical formula}LabArgpref, each iteration in the iterative SCUP revision reduces the set of arguments labelled undec. Since there are only finitely many arguments, there exists an iterative SCUP revision that results in a stable labelling (of the revision).
      </paragraph>
      <paragraph label="Theorem 27">
       There exists a stable iterative SCUP revision of{a mathematical formula}AFif and only if{a mathematical formula}LabArgprefis not a stable labelling.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}LabArgpref is a stable labelling then there exists no iterative SCUP revision since by Proposition 20, there exists no SCUP w.r.t. {a mathematical formula}LabArgpref. If {a mathematical formula}LabArgpref is not a stable labelling, by Proposition 20, there exists a SCUP w.r.t. {a mathematical formula}LabArgpref and thus by Corollary 26 there exists a preferred labelling {a mathematical formula}LabArg2 of {a mathematical formula}AF2 such that {a mathematical formula}LabArgpref⊏LabArg2. If {a mathematical formula}LabArg2 is not a stable labelling, then, by Proposition 20, there exists a SCUP w.r.t. {a mathematical formula}LabArg2 and thus a SCUP revision {a mathematical formula}AF3 of {a mathematical formula}AF2, and by Corollary 26 a preferred labelling {a mathematical formula}LabArg3 of {a mathematical formula}AF3 such that {a mathematical formula}LabArg2⊏LabArg3. The same then applies to {a mathematical formula}AF3, and so on. Thus, the set of undec arguments in {a mathematical formula}LabArgi monotonically decreases, and since there are only finitely many arguments, the sequence terminates with some {a mathematical formula}AFn such that {a mathematical formula}undec(LabArgn)=∅.  □
      </paragraph>
      <paragraph>
       Our results show that iteratively revising SCUPs provides a sufficient condition for turning a non-stable preferred labelling into a stable labelling (of a revision), and SCUPs are thus parts of the AF that can be deemed responsible that {a mathematical formula}LabArgpref is not a stable labelling. Furthermore, SCUPs can be used for a well-directed revision of the AF that leads to a stable labelling that is more committed than {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       Since by Proposition 21 every responsible SCC comprises a SCUP, responsible SCCs also define a sufficient condition for turning {a mathematical formula}LabArgpref into a stable labelling (of a revision), and consequently need to be revised in order to obtain a stable labelling. However, the condition provided by responsible SCCs is less refined than the notion of SCUPs. Therefore, we do not investigate the revision w.r.t. responsible SCCs in more detail.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Responsible cycles versus responsible SCCs and SCUPs
      </section-title>
      <paragraph>
       The characterisation of responsible arguments in terms of responsible cycles differs considerably from our second and third structural characterisations, which are based on SCCs. Nevertheless, we prove that the three characterisations are related. In particular, every SCUP comprises a responsible cycle.
      </paragraph>
      <paragraph label="Proposition 28">
       Let{a mathematical formula}Argsbe a SCUP w.r.t.{a mathematical formula}LabArgpref. Then there exists a responsible cycle{a mathematical formula}Cw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}C⊆Args.
      </paragraph>
      <paragraph label="Example 31">
       The only SCUP of {a mathematical formula}AF4 (see left of Fig. 10 on page 313) is {a mathematical formula}{c,d,e,f,g,h}. There are furthermore two responsible cycles that form subsets of the SCUP, namely {a mathematical formula}{d} and {a mathematical formula}{g} (see Example 19 on page 315).
      </paragraph>
      <paragraph>
       Note that the converse of Proposition 28 does not hold in general, i.e. it is not the case that every responsible cycle is a subset of some SCUP. For instance, in {a mathematical formula}AF8 (see top of Fig. 18 on page 320) each of the five self-attacking arguments is a responsible cycle. However, there are only two SCUPs, namely {a mathematical formula}{a} and {a mathematical formula}{e}, so for instance the responsible cycle {a mathematical formula}{b} is not a subset of any SCUP.
      </paragraph>
      <paragraph>
       Since by Proposition 21 every responsible SCC comprises a SCUP, it follows that every responsible SCC contains a responsible cycle.
      </paragraph>
      <paragraph label="Corollary 29">
       Let{a mathematical formula}Argsbe a responsible SCC w.r.t.{a mathematical formula}LabArgpref. Then there exists a responsible cycle{a mathematical formula}Cw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}C⊆Args.
      </paragraph>
      <paragraph>
       Note that Proposition 16, Proposition 28 imply that rather than defining a SCUP revision w.r.t. all arguments in SCUPs, we could only revise the responsible cycles in the SCUPs. This is illustrated by Example 19 (see page 315), where a revision w.r.t. the responsible cycles contained in the only SCUP is illustrated.
      </paragraph>
      <paragraph>
       On the other hand, the responsible cycles in a SCUP do not have to be revised in order to legally label all arguments in the SCUP. Instead, the SCUP may be revised w.r.t. a subset of the SCUP not containing arguments from responsible cycles. For instance, a SCUP revision of {a mathematical formula}AF4 w.r.t. {a mathematical formula}LabArgpref (see left of Fig. 10 on page 313) where no responsible cycles are revised is illustrated in Fig. 20 (see page 321), along with a preferred labelling that is more committed than the SCUP revision labelling.
      </paragraph>
      <paragraph>
       It is therefore up to the user to decide what type of SCUP revision is most suitable for the application at hand.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Labelling-based versus structural characterisations
     </section-title>
     <paragraph>
      We presented two different approaches to characterising sets of arguments responsible if {a mathematical formula}LabArgpref is not a stable labelling: a labelling-based and a structural approach. We proved that the labelling-based characterisations in terms of enforcement and preventing sets define necessary and sufficient conditions for the (non-) existence of a stable labelling that is more committed than {a mathematical formula}LabArgpref. However, these characterisations are not constructive, whereas our structural characterisations are. The structural characterisation in terms of SCUPs can also be used to guide the revision of an AF in such a way that a stable labelling is obtained, defining a sufficient but not a necessary condition for obtaining a stable labelling.
     </paragraph>
     <paragraph>
      In this section, we examine the connection between our labelling-based and structural characterisations in more detail. Note that we omit the naïve characterisation of labelling-based responsible sets, since both enforcement and preventing sets are refinements of this characterisation. Similarly, we do not include responsible SCCs in our comparison since SCUPs provide a refinement of responsible SCCs.
     </paragraph>
     <section label="6.1">
      <section-title>
       SCUPs versus preventing sets
      </section-title>
      <paragraph>
       SCUPs and preventing sets share the property that if none of their arguments is involved in a revision, then the revision has no stable labelling that is more committed than {a mathematical formula}LabArgpref (see Theorem 9, Theorem 23). These results hint at a close connection between SCUPs and preventing sets. Indeed, Theorem 30 proves that each SCUP comprises a preventing set.
      </paragraph>
      <paragraph label="Theorem 30">
       Let{a mathematical formula}ArgsSCUPbe a SCUP w.r.t.{a mathematical formula}LabArgpref. Then there exists a preventing set{a mathematical formula}Argsprevw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}Argsprev⊆ArgsSCUP.
      </paragraph>
      <paragraph label="Proof">
       By Lemma 22, for all labellings {a mathematical formula}LabArg of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅, it holds that there exists {a mathematical formula}A∈ArgsSCUP such that A is illegally labelled by {a mathematical formula}LabArg. Then either {a mathematical formula}ArgsSCUP is a minimal set satisfying this property, and thus {a mathematical formula}ArgsSCUP is a preventing set, or there exists a minimal set {a mathematical formula}Argsprev⊂ArgsSCUP satisfying this property, so {a mathematical formula}Argsprev is a preventing set.  □
      </paragraph>
      <paragraph label="Example 32">
       Consider again {a mathematical formula}AF4 illustrated on the left of Fig. 10 (see page 313). As discussed in Example 25 (see page 317), the only SCUP w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}{c,d,e,f,g,h}. Here, two different preventing sets w.r.t. {a mathematical formula}LabArgpref are subsets of the SCUP, namely {a mathematical formula}{c,d,g,h} and {a mathematical formula}{d,e,f,g}.
      </paragraph>
      <paragraph>
       Note that, conversely, it is not the case that every preventing set is a subset of some SCUP.
      </paragraph>
      <paragraph label="Example 33">
       Consider again {a mathematical formula}AF8, illustrated at the top of Fig. 18 (see page 320). There are three preventing sets w.r.t. {a mathematical formula}LabArgpref: {a mathematical formula}{a}, {a mathematical formula}{e}, and {a mathematical formula}{b,c,d}. The first two coincide with the two SCUPs w.r.t. {a mathematical formula}LabArgpref, but the latter is not a subset of any SCUP.
      </paragraph>
      <paragraph>
       Since SCUPs only characterise the “first” problematic sets of arguments, whereas preventing sets define “all” problematic sets, it is not surprising that some preventing sets are disjoint from SCUPs. However, when considering all SCUPs in a stable iterative SCUP revision, every preventing set shares an argument with some SCUP.
      </paragraph>
      <paragraph label="Notation 3">
       Let {a mathematical formula}〈AF1,LabArg1〉,…,〈AFn,LabArgn〉 be an iterative SCUP revision. {a mathematical formula}⨄SCUPS={SCUPSi|SCUPSiis theset of all arguments in SCUPsw.r.t.LabArgi,1≤i≤n} consists of the sets of arguments in SCUPs at every step in the iterative SCUP revision.
      </paragraph>
      <paragraph label="Theorem 31">
       Let{a mathematical formula}〈AF1,LabArg1〉,…,〈AFn,LabArgn〉be a stable iterative SCUP revision. Then, for all preventing sets{a mathematical formula}Argsprevw.r.t.{a mathematical formula}LabArgpref, it holds that{a mathematical formula}∃SCUPS∈⨄SCUPSsuch that{a mathematical formula}SCUPS∩Argsprev≠∅.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}Argsprev be a preventing set w.r.t. {a mathematical formula}LabArgpref. By (the contrapositive of) Theorem 9, it holds that if {a mathematical formula}AF⊛ is a revision of {a mathematical formula}AF w.r.t. some {a mathematical formula}Args⊆Ar by some {a mathematical formula}LabArg such that some revision labelling {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛ is a stable labelling of {a mathematical formula}AF⊛, then {a mathematical formula}Args∩Argsprev≠∅. Since {a mathematical formula}AFn has a stable labelling {a mathematical formula}LabArgn and since {a mathematical formula}AFn is a revision of {a mathematical formula}AF w.r.t. {a mathematical formula}⋃SCUPS∈⨄SCUPSSCUPS by {a mathematical formula}LabArgn∩(Ar×{in,out,undec}) it holds that {a mathematical formula}∃SCUPS∈⨄SCUPS such that {a mathematical formula}SCUPS∩Argsprev≠∅.  □
      </paragraph>
      <paragraph label="Example 34">
       Consider again {a mathematical formula}AF8, illustrated at the top of Fig. 18 (see page 320), and the stable iterative SCUP revision of {a mathematical formula}AF8 discussed in Example 30 (see page 320). The set of arguments in SCUPs in every step of the stable iterative SCUP revision is {a mathematical formula}⨄SCUPS={{a,e},{c}}. For the preventing set {a mathematical formula}{b,c,d} w.r.t. {a mathematical formula}LabArgpref, which is not a subset of any SCUP w.r.t. {a mathematical formula}LabArgpref (see Example 33), there exists the set {a mathematical formula}{c} in {a mathematical formula}⨄SCUPS, which shares an argument with {a mathematical formula}{b,c,d}. Clearly, the preventing sets {a mathematical formula}{a} and {a mathematical formula}{e}, which are subsets of SCUPs w.r.t. {a mathematical formula}LabArgpref, also have a non-empty intersection with a set in {a mathematical formula}⨄SCUPS, namely with {a mathematical formula}{a,e}.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       SCUPs versus enforcement sets
      </section-title>
      <paragraph>
       Next, we investigate the relationship between SCUPs and enforcement sets. We first show that a SCUP contains an argument from each enforcement set.
      </paragraph>
      <paragraph label="Theorem 32">
       Let{a mathematical formula}ArgsSCUPbe a SCUP w.r.t.{a mathematical formula}LabArgpref. Then, for all enforcement sets{a mathematical formula}Argsenfw.r.t.{a mathematical formula}LabArgpref, it holds that{a mathematical formula}ArgsSCUP∩Argsenf≠∅.
      </paragraph>
      <paragraph label="Proof">
       By Theorem 30, there exists a preventing set {a mathematical formula}Argsprev w.r.t. {a mathematical formula}LabArgpref such that {a mathematical formula}Argsprev⊆ArgsSCUP. Since by Theorem 10 it holds that for all enforcement sets {a mathematical formula}Argsenf w.r.t. {a mathematical formula}LabArgpref, {a mathematical formula}Argsprev∩Argsenf≠∅, it follows that {a mathematical formula}ArgsSCUP∩Argsenf≠∅.  □
      </paragraph>
      <paragraph label="Example 35">
       {a mathematical formula}AF8, illustrated at the top of Fig. 18 (see page 320), has two SCUPs w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{a} and {a mathematical formula}{e} (see Example 29 on page 319). Both SCUPs contain an argument from each of the three enforcement sets w.r.t. {a mathematical formula}LabArgpref, i.e. {a mathematical formula}{a,b,e}, {a mathematical formula}{a,c,e}, {a mathematical formula}{a,d,e}. In fact, both SCUPs are subsets of each enforcement set.In contrast, {a mathematical formula}AF4, illustrated at the left of Fig. 10 (see page 313), has only one SCUP w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{c,d,e,f,g,h}. Again the SCUP contains an argument from each enforcement set w.r.t. {a mathematical formula}LabArgpref, i.e. from {a mathematical formula}{d}, {a mathematical formula}{g}, {a mathematical formula}{c,e}, {a mathematical formula}{c,f}, {a mathematical formula}{e,h}, and {a mathematical formula}{f,h}. In fact, here each enforcement set is a subset of the SCUP.
      </paragraph>
      <paragraph>
       Note that, in general, SCUPs are not subsets of enforcement sets or vice versa. For instance, the SCUP {a mathematical formula}{a,b,c} of {a mathematical formula}AF3 (see left of Fig. 9 on page 309) is not a subset of any of the enforcement sets {a mathematical formula}{a,e}, {a mathematical formula}{b,e}, or {a mathematical formula}{c,e} or vice versa.
      </paragraph>
      <paragraph>
       By Theorem 12, we know that if a revision has a stable labelling that is more committed than {a mathematical formula}LabArgpref, the set of arguments used for the revision must be a superset of some enforcement set. Since a stable iterative SCUP revision results in such a stable labelling, it follows that there exists an enforcement set that is a subset of the set of all arguments occurring in SCUPs of the iterative SCUP revision.
      </paragraph>
      <paragraph label="Theorem 33">
       Let{a mathematical formula}〈AF1,LabArg1〉,…,〈AFn,LabArgn〉be a stable iterative SCUP revision. Then there exists an enforcement set{a mathematical formula}Argsenfw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}∀A∈Argsenf:∃SCUPS∈⨄SCUPSwith{a mathematical formula}A∈SCUPS.
      </paragraph>
      <paragraph label="Proof">
       By Theorem 31, for each preventing set {a mathematical formula}Argsprev it holds that {a mathematical formula}∃A∈Argsprev such that {a mathematical formula}∃SCUPS∈⨄SCUPS with {a mathematical formula}A∈SCUPS. It then follows from Theorem 11 that there exists an enforcement set {a mathematical formula}Argsenf such that such that {a mathematical formula}∀A∈Argsenf:∃SCUPS∈⨄SCUPS with {a mathematical formula}A∈SCUPS.  □
      </paragraph>
      <paragraph label="Example 36">
       Consider again {a mathematical formula}AF8 illustrated in Fig. 18 (see page 320) and the stable iterative SCUP revision of {a mathematical formula}AF8 discussed in Example 30 (see page 320). {a mathematical formula}⨄SCUPS={{a,e},{c}}, so there exists an enforcement set such that each argument is contained in a set in {a mathematical formula}⨄SCUPS, namely the enforcement set {a mathematical formula}{a,c,e}.
      </paragraph>
      <paragraph>
       The relation between enforcement sets and SCUPs implies that even though a stable iterative SCUP revision is not a minimal way of revising the AF to obtain a stable labelling, it includes the arguments that definitely have to be revised.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Responsible cycles versus enforcement and preventing sets
      </section-title>
      <paragraph>
       We now turn to the comparison between responsible cycles and enforcement and preventing sets. We first prove that there exists an enforcement set that consists only of arguments from responsible cycles.
      </paragraph>
      <paragraph label="Theorem 34">
       Let{a mathematical formula}S={A∈Ar|Cis a responsible cycle w.r.t.LabArgpref,A∈C}. Then there exists an enforcement set{a mathematical formula}Argsw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}Args⊆S.
      </paragraph>
      <paragraph label="Proof">
       By Proposition 16, there exists a labelling {a mathematical formula}LabArg of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊑LabArg and {a mathematical formula}undec(LabArg)=∅ such that, for all revisions {a mathematical formula}AF⊛ of {a mathematical formula}AF w.r.t. S by {a mathematical formula}LabArg and all revision labellings {a mathematical formula}LabArg⊛ of {a mathematical formula}AF⊛, {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛. It then follows from Theorem 12 that there exists an enforcement set {a mathematical formula}Args w.r.t. {a mathematical formula}LabArgpref such that {a mathematical formula}Args⊆S.  □
      </paragraph>
      <paragraph label="Example 37">
       Consider again {a mathematical formula}AF4, illustrated at the left of Fig. 10 (see page 313). The set of arguments in responsible cycles w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}S={d,g}. There are two different enforcement sets that are subsets of S, namely {a mathematical formula}{d} and {a mathematical formula}{g}. This example also illustrates that not all enforcement sets contain arguments that are part of a responsible cycle, e.g. the enforcement set {a mathematical formula}{c,e} is disjoint from S.
      </paragraph>
      <paragraph>
       Note that not every responsible cycle shares arguments with some enforcement set. For instance, the responsible cycle {a mathematical formula}{e} w.r.t. the preferred labelling {a mathematical formula}LabArgpref of {a mathematical formula}AF7, illustrated in Fig. 15 (see page 317), and the only enforcement set w.r.t. {a mathematical formula}LabArgpref, namely {a mathematical formula}{c,d}, do not have any arguments in common.
      </paragraph>
      <paragraph>
       Next, we show the connection between responsible cycles and preventing set. In particular, every preventing set comprises a responsible cycle.
      </paragraph>
      <paragraph label="Theorem 35">
       Let{a mathematical formula}Args≠∅be a preventing set w.r.t.{a mathematical formula}LabArgpref. Then there exists a responsible cycle{a mathematical formula}Cw.r.t.{a mathematical formula}LabArgprefsuch that{a mathematical formula}C⊆Args.
      </paragraph>
      <paragraph label="Proof">
       By Lemma 8, {a mathematical formula}LabArgpref is not a stable labelling. Let {a mathematical formula}ArgsIO=in(LabArgpref)∪out(LabArgpref). Assume there exists no responsible cycle {a mathematical formula}C w.r.t. {a mathematical formula}LabArgpref such that {a mathematical formula}C⊆Args. Thus, {a mathematical formula}AF↓Args comprises no odd-length cycles, so by Corollary 36 in [10]{a mathematical formula}AF↓Args has a stable labelling {a mathematical formula}LabArgArgs. By Lemma 46 in Appendix A, {a mathematical formula}LabArgpref↓ArgsIO is compatible with {a mathematical formula}LabArgArgs. Furthermore, by the same reasoning as in the proof of Proposition 19, {a mathematical formula}LabArgArgs is compatible with {a mathematical formula}LabArgpref↓ArgsIO. It follows from Lemma 40 in Appendix A that {a mathematical formula}LabArgArgs∪LabArgpref↓ArgsIO is a complete labelling of {a mathematical formula}AF↓Args∪ArgsIO. Let {a mathematical formula}LabArg′ be a labelling of {a mathematical formula}Args′=Ar∖(Args∪ArgsIO) such that {a mathematical formula}out(LabArg′)=Args′. Let {a mathematical formula}LabArg=LabArgArgs∪LabArgpref↓ArgsIO∪LabArg′. Clearly {a mathematical formula}LabArgpref⊏LabArg. Furthermore, {a mathematical formula}∀A∈Args it holds that A is legally labelled by {a mathematical formula}LabArg. Contradiction, since by Definition 5, {a mathematical formula}∀LabArg with {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅ it holds that {a mathematical formula}∃A∈Args such that A is illegally labelled by {a mathematical formula}LabArg.  □
      </paragraph>
      <paragraph label="Example 38">
       Consider again {a mathematical formula}AF4, illustrated at the left of Fig. 10 (see page 313). The two preventing sets w.r.t. the preferred labelling {a mathematical formula}LabArgpref of {a mathematical formula}AF4 are {a mathematical formula}{c,d,g,h} and {a mathematical formula}{d,e,f,g}. Both contain a responsible cycle w.r.t. {a mathematical formula}LabArgpref, in this case even two responsible cycles, namely {a mathematical formula}{d} and {a mathematical formula}{g}.
      </paragraph>
      <paragraph>
       These results imply that odd-length cycles of arguments labelled undec by {a mathematical formula}LabArgpref are an important characteristic of sets of arguments that prevent {a mathematical formula}LabArgpref from being a stable labelling (Theorem 35). Furthermore, it is sufficient to revise (specific) arguments in odd-length cycles to obtain a stable labelling (of the revision) that is more committed than {a mathematical formula}LabArgpref (Theorem 34).
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Discussion and related work
     </section-title>
     <paragraph>
      Having introduced and analysed various characterisations of parts of an AF responsible if a given preferred labelling is not stable, we now discuss the implications for the non-existence of stable labellings, the choice of preferred semantics, and connections with related work.
     </paragraph>
     <section label="7.1">
      <section-title>
       Non-existence of stable labellings
      </section-title>
      <paragraph>
       Throughout this paper, we gave different characterisations of parts of an AF responsible that a given preferred labelling is not stable, irrespective of the existence of a stable labelling. That is, in general, the AF may have various preferred labellings, some that are stable and some that are not. These preferred labellings differ in their assignment of the labels in and out to certain arguments, in other words, an argument may be labelled in by one but out by another preferred labelling. This gives users the freedom to choose an assignment according to their own preferences.
      </paragraph>
      <paragraph>
       In applications where decisiveness is required, users can thus decide whether they only care about finding some labelling without undec labels, in which case they can simply choose a stable labelling (if one exists), or they can choose one of the preferred labellings according to their preference concerning the assignment of in and out labels, and, if this preferred labelling is not stable, identify a suitable revision of the AF. If the AF has no stable labelling at all, the second situation is the only possible one. Our characterisations are thus versatile, as they can be applied both in scenarios where an AF has no stable labelling and in scenarios where a stable labelling exists, but the desired preferred labelling is not stable.
      </paragraph>
      <paragraph>
       Since every stable labelling is a preferred labelling [11], it follows that if no stable labelling exists, then no preferred labelling is stable. Thus, in the case of non-existence of stable labellings, our characterisations can explain the non-existence in terms of the preferred labellings not being stable in the following sense.
      </paragraph>
      <paragraph label="Proposition 36">
       {a mathematical formula}AFhas no stable labelling if and only if for all preferred labellings{a mathematical formula}LabArgprefof{a mathematical formula}AFthere exist a non-empty enforcement and a non-empty preventing set w.r.t.{a mathematical formula}LabArgpref, and there exist a responsible cycle and a SCUP w.r.t.{a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph label="Proof">
       Follows from Lemma 5, Lemma 8, and Proposition 15, Proposition 20.  □
      </paragraph>
      <paragraph>
       Note that any one of the “responsibility conditions”, e.g. the existence of a non-empty enforcement set, implies all the other “responsibility conditions”, e.g. the existence of a SCUP. Which of our characterisations is most suitable for an application in question is left to the user to decide. As we have shown, each characterisation defines parts of an AF that are indeed responsible that a preferred labelling is not stable, and consequently that no stable labelling exists.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Preferred versus other approximation labellings
      </section-title>
      <paragraph>
       The preferred semantics is not the only one to “approximate” the stable semantics. In particular, semi-stable labellings [13] are specific preferred labellings. Furthermore, stage and CF2 semantics [21] capture special types of maximal conflict-free sets. Even though stable labellings are always stage and CF2 labellings, stage and CF2 semantics do not generally adhere to the same basic properties as stable semantics in that, in particular, they do not satisfy admissibility [12]. Therefore, stage and CF2 semantics do not lend themselves to investigating the non-existence of stable labellings. However, it will be interesting future work to investigate whether similar methods as presented in this paper could help characterise why stage or CF2 labellings are not stable.
      </paragraph>
      <paragraph>
       In contrast to CF2 and stage semantics, semi-stable labellings fulfil the admissibility property. They are defined as preferred labellings where the union of in and out labelled arguments is maximal (w.r.t. ⊆) among all complete labellings [13]. We therefore also considered to use semi-stable labellings for our characterisations, instead of preferred labellings. In fact, most of our definitions apply to semi-stable labellings, too. For example, we could define enforcement and preventing sets w.r.t. a semi-stable rather than a preferred labelling since every semi-stable labelling is preferred.
      </paragraph>
      <paragraph>
       However, with regards to SCUPs, semi-stable labellings lead to a problem: even though SCUPs can be defined with respect to a semi-stable instead of a preferred labelling, stable iterative SCUP revisions may not exist when defining SCUPs with respect to a semi-stable labelling. The reason is that Theorem 25 and Corollary 26 are not guaranteed to hold for semi-stable labellings, i.e. a SCUP revision may not have a semi-stable labelling that is more committed than the semi-stable labelling of the original AF, as illustrated by the following example.
      </paragraph>
      <paragraph label="Example 39">
       Let {a mathematical formula}AF9 be the AF on the left of Fig. 21, which also illustrates the only preferred and only semi-stable labelling {a mathematical formula}LabArgpref of {a mathematical formula}AF9. The only SCUP w.r.t. {a mathematical formula}LabArgpref is {a mathematical formula}{a}. A SCUP revision {a mathematical formula}AF9⊛ of {a mathematical formula}AF9 and its SCUP revision labelling {a mathematical formula}LabArg⊛ are shown on the right of Fig. 21. The left of Fig. 22 illustrates the only preferred labelling of {a mathematical formula}AF9⊛ that is more committed than {a mathematical formula}LabArg⊛ and {a mathematical formula}LabArgpref. Note that this preferred labelling is not a semi-stable labelling of {a mathematical formula}AF9⊛. The only semi-stable labelling of {a mathematical formula}AF9⊛ is illustrated on the right of Fig. 22. It is not more (or equally) committed than {a mathematical formula}LabArg⊛. The same problem arises if the SCUP is revised in such a way that a is labelled out in the SCUP revision labelling, as illustrated at the left of Fig. 23. The only semi-stable labelling of the SCUP revision is shown at the right of Fig. 23, which is not more or equally committed than the SCUP revision labelling or {a mathematical formula}LabArgpref.
      </paragraph>
      <paragraph>
       The problem with defining SCUPs with respect to semi-stable rather than preferred labellings is thus that iterative SCUP revisions cannot be applied, unless we are prepared to change the labels of arguments already labelled in and out by the semi-stable labelling of the original AF. However, this would defeat the spirit of our work, as we are interested in why a particular labelling is not a stable labelling. Of course, one could start with a semi-stable labelling and then use preferred labellings in the iterative SCUP revision.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       Related to our work on stable semantics, Baumann and Strass [22] focus on the question how many stable extensions an AF has on average and what the maximal number of stable extensions is. Furthermore, Dunne and Bench-Capon [23] investigate AFs whose stable and preferred extensions coincide, so-called coherent AFs, and thus deal with AFs that always have a stable extension.
      </paragraph>
      <paragraph>
       To the best of our knowledge, the only work investigating the non-existence of stable extensions or labellings is by Nouioua and Würbel [24], who propose a revision operator that transforms an AF without stable extensions into one with a stable extension. Their setting is different from ours as they assume that the AF in question, which has no stable extension, was obtained from an addition of arguments and attacks to some original AF. Assuming that the added arguments and attacks are “correct”, they restrict the structural change performed by the revision operator to the original AF. In contrast, our work aims at characterising parts of an AF responsible for the non-existence of stable labellings and only uses the notion of structural change to prove that our characterised parts are indeed responsible. Furthermore, Nouioua and Würbel's approach differs from ours in various ways: Firstly, they revise an AF through a particular structural change, namely the deletion of attacks, whereas in our approach the addition of arguments and attacks is allowed, too. Importantly, in some cases, an enforcement labelling may be such that a mere deletion of attacks does not yield the desired enforcement, in other words, adding arguments may be necessary to obtain the desired enforcement.{sup:6} Furthermore, their approach is not concerned with preserving a particular preferred, or even the grounded, labelling when performing the structural change. Another difference is that they are concerned with minimal (w.r.t. cardinality) changes that guarantee the existence of a stable extension. In our approach minimality also plays a role, as enforcement sets are minimal (w.r.t. set inclusion) sets of arguments used to obtain a stable labelling. However, as far as structural changes are concerned we do not make any minimality assumptions.
      </paragraph>
      <paragraph>
       Like us, Baroni, Giacomin and Liao [25] are interested in arguments labelled undec. However, rather than investigating how undec labels can be turned into definite in or out labels, they argue that undecidedness is desirable in some situations and review various semantics that include different notions of “undecidedness”.
      </paragraph>
      <paragraph>
       Caminada and Pigozzi [26] also investigate labellings that are “as close as possible” to a given labelling and fulfil certain conditions, e.g. down-admissible labellings are the closest admissible labellings less committed than the given labelling and up-complete labellings are the closest complete labellings more committed than the given labelling. Instead, our enforcement labellings define more committed labellings that are “closest” to a stable labelling in terms of a minimal set of illegally labelled arguments, so they are not complete labellings. Another idea shared with their work is that of an iterative re-labelling (contraction and expansion functions) to obtain a labelling that legally labels all arguments. This is related to our iterative SCUP revision, where arguments in SCUPs are iteratively re-labelled (and enforced through structural revision) until a stable labelling (of a revision) is obtained.
      </paragraph>
      <paragraph>
       The ideas of enforcement and preventing sets introduced here are similar in spirit as Reiter's [27] diagnoses and conflict sets. They describe components of a system causing abnormal behaviour of the system. Similarly to enforcement and preventing sets, they form duals (in terms of Reiter, one is a “hitting set” of the other). Inspired by that, Ignatiev et al. [28] define similar duals for propositional logic in terms of minimal corrections subsets and minimal unsatisfiable subsets.
      </paragraph>
      <paragraph>
       In the following sections, we review some further strands of research sharing particular aspects with our work.
      </paragraph>
      <section label="7.3.1">
       <section-title>
        Cycles in argumentation frameworks
       </section-title>
       <paragraph>
        Recently, cycles (of attacking arguments) in AFs have received considerable attention, including a special issue of the Journal of Logic and Computation [29]. Many authors regard the behaviour of preferred semantics with respect to cycles as “problematic”, as it treats odd-length and even-length cycles differently. In particular, arguments in odd-length cycles can often only be labelled undec, as is the case for our responsible cycles, whereas arguments in even-length cycles can be alternately labelled in and out.
       </paragraph>
       <paragraph>
        Baroni, Giacomin and Guida [16] discuss this “problematic” behaviour of preferred semantics and introduce the CF2 semantics for AFs, which “correctly” handles odd- and even-length cycles. Dvořák and Gaggl [30] extend the CF2 semantics to the so-called stage2 semantics, which fulfils some additional properties. Arieli [31] introduces a new family of conflict-tolerant semantics, where the conflict-freeness requirement for extensions is dropped. Therefore, odd- and even-length cycles are treated the same by the new semantics. Gabbay [32] defines another family of new semantics, able to handle the “problematic” behaviour of the preferred semantics with regards to cycles. In the loop busting semantics no argument is labelled undec. The procedure for computing the semantics has similarities with ideas used in our approach, since it iteratively applies a specific type of revision of initial SCCs. More precisely, an argument in an initial SCC of the undec -part with respect to the grounded extension is chosen and a new attacker is added. Then the grounded labelling of the new AF is computed and the same procedure is performed iteratively for the new AF restricted to arguments labelled undec. The iterative SCUP revision introduced here applies a similar approach since an initial SCC of the undec -part (i.e. a SCUP) is revised and the revision is then repeated on the AF restricted to arguments still labelled undec. However, we allow for any revision and use the preferred rather than grounded semantics. Bodanza and Tohmé [33] propose two new semantics for handling odd-length cycles: the first one allows to accept arguments attacked by an odd-length cycle, and the second one additionally allows to accept single arguments in an odd-length cycle. Both types of semantics yield labellings that are more committed than preferred labellings.
       </paragraph>
       <paragraph>
        In contrast to the aforementioned works, Bench-Capon [34] argues that the way the preferred semantics handles cycles is not “problematic”, by providing an interpretation of even-length cycles as dilemmas and odd-length cycles as paradoxes. He argues that using this point of view, it is reasonable that arguments in odd-length cycles are neither true nor false, and that consequently their justification status cannot be decided.
       </paragraph>
       <paragraph>
        Note that the motivation of our approach is completely different from the motivations of the works reviewed above. We do not make any claims about whether or not the preferred semantics handles cycles “correctly”, and are therefore not concerned with new semantics. Instead, we characterise specific parts of an AF, which turn out to comprise odd-length cycles, as responsible that a preferred labelling is not stable, which also characterise parts of the AF responsible for the non-existence of stable labellings.
       </paragraph>
       <paragraph>
        Like us, Baumann and Woltran [35] are not concerned with the “correct” or “incorrect” behaviour of semantics regarding odd-length cycles. Instead, they study the role of self-attacking arguments, i.e. cycles of length one, with regards to the equivalence of AFs.
       </paragraph>
      </section>
      <section label="7.3.2">
       <section-title>
        Splitting argumentation frameworks
       </section-title>
       <paragraph>
        Two of our structural characterisations build upon the idea of SCCs introduced in [16]. We investigate a particular type of SCCs, namely specific initial SCCs, and use Baroni, Giacomin and Guida's results [16] that the preferred and stable semantics are SCC-recursive, i.e. that the preferred and stable extensions (or equivalently labellings) of an AF can be obtained by computing the respective extensions for initial SCCs and using them recursively for computing the extensions of the following SCCs. Liao [36] shows how the semantics of an AF can be computed through the step-wise computation of semantics of SCCs, and Baroni et al. [18] generalise the decomposability results about SCCs, showing how complete labellings of an AF can be computed by combining complete labellings of arbitrary parts of the AF. We apply and extend Baroni et al.'s results for a particular partitions of an AF into the set of arguments labelled in or out by a preferred labelling, and (a subset of the) arguments labelled undec.
       </paragraph>
       <paragraph>
        Our results about combining a labelling of a SCUP with the in and out labels in a preferred labelling are also related to the splitting results of Baumann et al. [37], [38]. They show that, for the stable semantics, extensions of an AF can be obtained by splitting the AF into two parts and computing the extensions of the two parts using a method that takes the extensions of the respective other part into account. Another related approach was introduced by Rienstra et al. [39], who propose multi-sorted extensions as a new semantics of an AF with respect to a partition of the AF. A multi-sorted extension is such that its restriction to a part coincides with a given semantics for this part. This approach is conceptually related to our work, which combines the stable labellings of parts of the AF, namely SCUPs, with in and out labels from a preferred labelling.
       </paragraph>
      </section>
      <section label="7.3.3">
       <section-title>
        Dynamics in argumentation frameworks
       </section-title>
       <paragraph>
        The study of dynamics in AFs has received considerable attention in recent years. Our work investigates the dynamics of AFs from a special angle, since we are not concerned with the exact structural change of an AF and its effect (as e.g. in [40]), but rather with the existence of some structural change resulting in the enforcement of a desired label for an argument. Importantly, which structural change is chosen is not of importance for our work.
       </paragraph>
       <paragraph>
        Liao, Jin, and Koons [41] introduce a general approach for computing extensions of an AF that has been structurally changed, allowing for any number of additions and deletions of arguments and attacks. The idea is that, in order to compute the semantics of the new AF, only the semantics of the part of the AF that is affected by the structural change has to be re-computed. The semantics of the unaffected part stays the same as before the structural change and only “conditions” the extensions of the affected part. This idea is related to our iterative SCUP revisions, where we do not change the labels of arguments labelled in or out in the SCUP revision labelling (they are “unaffected”), but only of those labelled undec that are “conditioned” by the in and out labels of the SCUP revision labelling.
       </paragraph>
       <paragraph>
        The work of Booth et al. [42] is of similar spirit to our work, but concerned with the complete rather than the stable semantics: they investigate how to turn a non-complete labelling into a complete one through a structural change. In contrast to our work, Booth et al. assume an intended complete labelling, whereas for our approach no intended stable labelling is required.
       </paragraph>
       <paragraph>
        Baumann and Brewka [17] were the first to investigate whether certain sets of arguments can be enforced as an extension according to a chosen semantics. In contrast to our general revisions, they only allow structural changes called “expansions”, where arguments and attacks can be added, and new attacks must involve a new argument. Baumann and Brewka prove that for certain kinds of expansions, all arguments that are part of extensions before the structural change are also part of extensions after the structural change. In line with their work, we show that for any revision w.r.t. an enforcement set by an enforcement labelling, a stable labelling is obtained in which all previously in - and out -labelled arguments keep their labels. Baumann [19] as well as Coste-Marquis et al. [20] then studied how to enforce a set of arguments through a minimal structural change of adding or deleting attacks. Similarly, we prove that enforcement sets are minimal sets of arguments that, when used for a revision, yield a stable labelling. Coste-Marquis et al. [43] introduce a whole family of revision operators that can be used for enforcement, generalising revision operators defined by others, e.g. [44], [45], [46]. Other authors [47], [48], [49] study enforcements as logical formulae to be satisfied through structural change. It is important to note that even though enforcement is a related problem, we do not assume a set of arguments to be “enforced” as an extension of the SCUP. In contrast, we only require that some stable extension exists after the revision. However, the previously mentioned approaches could be used for enforcing a certain set of arguments as a stable extension of a SCUP.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Auxiliary results
     </section-title>
     <paragraph label="Lemma 37">
      Let{a mathematical formula}LabArgbe a labelling of{a mathematical formula}AF,{a mathematical formula}Args⊆Arand{a mathematical formula}A∈Ar∖Args. Let{a mathematical formula}AF⊛be a revision of{a mathematical formula}AFw.r.t.{a mathematical formula}Argsby{a mathematical formula}LabArgand{a mathematical formula}LabArg⊛a revision labelling of{a mathematical formula}AF⊛. Then A is legally labelled by{a mathematical formula}LabArgin{a mathematical formula}AFif and only if A is legally labelled by{a mathematical formula}LabArg⊛in{a mathematical formula}AF⊛.
     </paragraph>
     <paragraph label="Proof">
      From left to right: Let A be legally labelled by {a mathematical formula}LabArg. By Definition 1, {a mathematical formula}(B,A)∈Att if and only if {a mathematical formula}(B,A)∈Att⊛. Furthermore, {a mathematical formula}LabArg⊛(A)=LabArg(A) and for all {a mathematical formula}B∈Ar, {a mathematical formula}LabArg⊛(B)=LabArg(B). Since it only depends on the labels of attackers of A whether or not A is legally labelled, it follows that A is legally labelled by {a mathematical formula}LabArg⊛. The proof of the opposite direction is analogous.  □
     </paragraph>
     <paragraph label="Lemma 38">
      Let{a mathematical formula}LabArgand{a mathematical formula}LabArg′be two labellings of{a mathematical formula}AFsuch that{a mathematical formula}LabArg⊑LabArg′. Then,{a mathematical formula}∀A∈in(LabArg)∪out(LabArg)it holds that if A is legally labelled by{a mathematical formula}LabArg, then A is legally labelled by{a mathematical formula}LabArg′.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}A∈in(LabArg). Then, for all attackers B of A, {a mathematical formula}B∈out(LabArg). By definition of {a mathematical formula}LabArg′, {a mathematical formula}A∈in(LabArg′) and for all attackers B of A, {a mathematical formula}B∈out(LabArg′). Thus, A is legally labelled in by {a mathematical formula}LabArg′. Let {a mathematical formula}A∈out(LabArg). Then there exists an attacker B of A such that {a mathematical formula}B∈in(LabArg). By definition of {a mathematical formula}LabArg′, {a mathematical formula}A∈out(LabArg′) and {a mathematical formula}B∈in(LabArg′). Thus, A is legally labelled out by {a mathematical formula}LabArg′.  □
     </paragraph>
     <paragraph label="Lemma 39">
      Let{a mathematical formula}Argsbe an enforcement set w.r.t.{a mathematical formula}LabArgprefand{a mathematical formula}LabArgan enforcement labelling w.r.t.{a mathematical formula}Args. Then,{a mathematical formula}∀A∈Ar∖Args, A is legally labelled by{a mathematical formula}LabArg.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}A∈Ar∖Args. By Definition 4, if {a mathematical formula}A∈undec(LabArgpref), then A is legally labelled by {a mathematical formula}LabArg. If {a mathematical formula}A∈in(LabArgpref)∪out(LabArgpref), then by Lemma 38A is legally labelled by {a mathematical formula}LabArg, since {a mathematical formula}LabArgpref⊏LabArg.  □
     </paragraph>
     <paragraph label="Definition 12">
      Compatible labellingLet {a mathematical formula}Args1,Args2⊆Ar such that {a mathematical formula}Args1∩Args2=∅ and {a mathematical formula}Args1∪Args2=Ar. Let {a mathematical formula}LabArg1 be a labelling of {a mathematical formula}AF↓Args1 and {a mathematical formula}LabArg2 a labelling of {a mathematical formula}AF↓Args2. {a mathematical formula}LabArg1 is compatible with {a mathematical formula}LabArg2 if and only if {a mathematical formula}LabArg1 is a complete labelling w.r.t. {a mathematical formula}(AF↓Args1,Args2,LabArg2,Att∩(Args2×Args1)).
     </paragraph>
     <paragraph label="Lemma 40">
      Let{a mathematical formula}Args1,Args2⊆Arsuch that{a mathematical formula}Args1∩Args2=∅and{a mathematical formula}Args1∪Args2=Ar. Let{a mathematical formula}LabArg1be a labelling of{a mathematical formula}AF↓Args1and{a mathematical formula}LabArg2a labelling of{a mathematical formula}AF↓Args2.{a mathematical formula}LabArg=LabArg1∪LabArg2is a complete labelling of{a mathematical formula}AFif and only if{a mathematical formula}LabArg1is compatible with{a mathematical formula}LabArg2and{a mathematical formula}LabArg2is compatible with{a mathematical formula}LabArg1.
     </paragraph>
     <paragraph label="Proof">
      Follows from Definition 12 and Theorem 3 in [18].  □
     </paragraph>
     <paragraph label="Lemma 41">
      Let{a mathematical formula}Args1,Args2⊆Arsuch that{a mathematical formula}Args1∩Args2=∅,{a mathematical formula}Args1∪Args2=Ar, and{a mathematical formula}Args2does not attack{a mathematical formula}Args1. Let{a mathematical formula}LabArg1be a complete labelling of{a mathematical formula}AF↓Args1and{a mathematical formula}LabArg2a labelling of{a mathematical formula}AF↓Args2.{a mathematical formula}LabArg=LabArg1∪LabArg2is a complete labelling of{a mathematical formula}AFif and only if{a mathematical formula}LabArg2is compatible with{a mathematical formula}LabArg1.
     </paragraph>
     <paragraph label="Proof">
      From left to right: Let {a mathematical formula}LabArg=LabArg1∪LabArg2 be a complete labelling of {a mathematical formula}AF. Then, by Lemma 40, {a mathematical formula}LabArg2 is compatible with {a mathematical formula}LabArg1.From right to left: Let {a mathematical formula}LabArg2 be compatible with {a mathematical formula}LabArg1. Since {a mathematical formula}LabArg1 is a complete labelling of {a mathematical formula}AF↓Args1, by Proposition 1 in [18]{a mathematical formula}LabArg1 is a complete labelling w.r.t. {a mathematical formula}(AF↓Args1,∅,∅,∅). Since {a mathematical formula}Args2 does not attack {a mathematical formula}Args1, it follows that {a mathematical formula}LabArg1 is a complete labelling w.r.t. {a mathematical formula}(AF↓Args1,Args2,LabArg2,∅), so {a mathematical formula}LabArg1 is compatible with {a mathematical formula}LabArg2. Thus by Lemma 40, {a mathematical formula}LabArg1∪LabArg2 is a complete labelling of {a mathematical formula}AF.  □
     </paragraph>
     <paragraph label="Corollary 42">
      We can generalise Lemma 41 to SCCs. Let{a mathematical formula}Args1,…,Argsn({a mathematical formula}n≥1) be a sequence of all SCCs of{a mathematical formula}AFand for all{a mathematical formula}i≠j,{a mathematical formula}Argsi≠Argsj, and if{a mathematical formula}Argsiis attacked by{a mathematical formula}Argsk({a mathematical formula}i≠k), then{a mathematical formula}k&lt;i. Let{a mathematical formula}LabArgibe a labelling of{a mathematical formula}AF↓Argsi. Then{a mathematical formula}LabArg=LabArg1∪…∪LabArgnis a complete labelling of{a mathematical formula}AFif and only if{a mathematical formula}LabArg1is a complete labelling of{a mathematical formula}Args1and{a mathematical formula}LabArgiis compatible with{a mathematical formula}LabArg1∪…∪LabArgi−1for all{a mathematical formula}i∈{2…n}.
     </paragraph>
     <paragraph label="Lemma 43">
      Let{a mathematical formula}Args1,Args2⊆Arsuch that{a mathematical formula}Args1∩Args2=∅and{a mathematical formula}Args1∪Args2=Ar. Let{a mathematical formula}LabArg1be a labelling of{a mathematical formula}AF↓Args1and{a mathematical formula}LabArg2a labelling of{a mathematical formula}AF↓Args2. If{a mathematical formula}∀A∈Args1it holds that A is legally labelled by{a mathematical formula}LabArg1∪LabArg2in{a mathematical formula}AF, then{a mathematical formula}LabArg1is compatible with{a mathematical formula}LabArg2.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}LabArg=LabArg1∪LabArg2 and let {a mathematical formula}A∈Args1.
     </paragraph>
     <list>
      <list-item label="•">
       If {a mathematical formula}A∈in(LabArg1), then clearly {a mathematical formula}A∈in(LabArg). Thus, ∀B attacking A, {a mathematical formula}B∈out(LabArg). It follows that if {a mathematical formula}B∈Args1, {a mathematical formula}B∈out(LabArg1), and if {a mathematical formula}B∈Args2, then {a mathematical formula}B∈out(LabArg2).
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A∈out(LabArg1), then clearly {a mathematical formula}A∈out(LabArg). Thus, ∃B attacking A such that {a mathematical formula}B∈in(LabArg). It follows that {a mathematical formula}B∈Args1 and {a mathematical formula}B∈in(LabArg1), or {a mathematical formula}B∈Args2 and {a mathematical formula}B∈in(LabArg2).
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A∈undec(LabArg1), then clearly {a mathematical formula}A∈undec(LabArg). Thus, ∀B attacking A, {a mathematical formula}B∉in(LabArg), and ∃C attacking A such that {a mathematical formula}C∈undec(LabArg). It follows that if {a mathematical formula}B∈Args1, {a mathematical formula}B∉in(LabArg1), and if {a mathematical formula}B∈Args2, then {a mathematical formula}B∉in(LabArg2). Furthermore, it follows that {a mathematical formula}C∈Args1 and {a mathematical formula}C∈undec(LabArg1) or {a mathematical formula}C∈Args2 and {a mathematical formula}C∈undec(LabArg2).
      </list-item>
     </list>
     <paragraph label="Lemma 44">
      Let{a mathematical formula}ArgsIO=in(LabArgpref)∪out(LabArgpref)and{a mathematical formula}ArgsU=undec(LabArgpref). Then{a mathematical formula}LabArgpref↓ArgsUis the only complete labelling w.r.t.{a mathematical formula}(AF↓ArgsU,ArgsIO,LabArgpref↓ArgsIO,Att∩(ArgsIO×ArgsU)).
     </paragraph>
     <paragraph label="Proof">
      Since {a mathematical formula}LabArgpref is a complete labelling of {a mathematical formula}AF, it holds by Lemma 40 that {a mathematical formula}LabArgpref↓ArgsIO is compatible with {a mathematical formula}LabArgpref↓ArgsU and vice versa. By Definition 12, it follows that {a mathematical formula}LabArgpref↓ArgsU is a complete labelling w.r.t. {a mathematical formula}(AF↓ArgsU,ArgsIO,LabArgpref↓ArgsIO,Att∩(ArgsIO×ArgsU)).To prove that {a mathematical formula}LabArgpref↓ArgsU is the only such labelling, assume there exists a labelling {a mathematical formula}LabArgU≠LabArgpref↓ArgsU of {a mathematical formula}AF↓ArgsU such that {a mathematical formula}LabArgU is a complete labelling w.r.t. {a mathematical formula}(AF↓ArgsU,ArgsIO,LabArgpref↓ArgsIO,Att∩(ArgsIO×ArgsU)).Thus by Definition 12, {a mathematical formula}LabArgU is compatible with {a mathematical formula}LabArgpref↓ArgsIO.Clearly, {a mathematical formula}LabArgpref⊏LabArgpref↓ArgsIO∪LabArgU, so by Lemma 38 all {a mathematical formula}A∈ArgsIO are legally labelled by {a mathematical formula}LabArgpref↓ArgsIO∪LabArgU. Then, by Lemma 43, {a mathematical formula}LabArgpref↓ArgsIO is compatible with {a mathematical formula}LabArgU. It follows by Lemma 40, that {a mathematical formula}LabArgpref↓ArgsIO∪LabArgU is a complete labelling of {a mathematical formula}AF. Contradiction, since {a mathematical formula}LabArgpref⊏LabArgpref↓ArgsIO∪LabArgU and {a mathematical formula}LabArgpref is a preferred labelling. Thus, {a mathematical formula}LabArgpref↓ArgsU is the only complete labelling w.r.t. {a mathematical formula}(AF↓ArgsU,ArgsIO,LabArgpref↓ArgsIO,Att∩(ArgsIO×ArgsU)).  □
     </paragraph>
     <paragraph label="Lemma 45">
      Let{a mathematical formula}Args1,Args2⊆Arsuch that{a mathematical formula}Args1∩Args2=∅and{a mathematical formula}Args1∪Args2=Ar. Let{a mathematical formula}LabArg2be a labelling of{a mathematical formula}AF↓Args2. Then there exists a labelling{a mathematical formula}LabArg1of{a mathematical formula}AF↓Args1such that{a mathematical formula}LabArg1is compatible with{a mathematical formula}LabArg2.
     </paragraph>
     <paragraph label="Proof">
      Since Definition 12 mirrors the definition of canonical local function of the complete semantics (Definition 24 in [18]), a labelling {a mathematical formula}LabArg1 of {a mathematical formula}Args1 is compatible with a labelling {a mathematical formula}LabArg2 of {a mathematical formula}Args2 if and only if {a mathematical formula}LabArg1 is an element of the canonical local function of the complete semantics of the argumentation framework with input {a mathematical formula}(AF↓Args1,Args2,LabArg2,Att∩(Args2×Args1)). By Definition 13 in [18], the canonical local function of the complete semantics of {a mathematical formula}(AF↓Args1,Args2,LabArg2,Att∩(Args2×Args1)) can be computed via the complete labellings of the standard argumentation framework of {a mathematical formula}(AF↓Args1,Args2,LabArg2,Att∩(Args2×Args1)). Since a standard argumentation framework always exists, it has a complete labelling, so the canonical local function of the complete semantics for {a mathematical formula}(AF↓Args1,Args2,LabArg2,Att∩(Args2×Args1)) is non-empty. Thus {a mathematical formula}LabArg1 exists.  □
     </paragraph>
     <paragraph label="Lemma 46">
      Let{a mathematical formula}ArgsIO=in(LabArgpref)∪out(LabArgpref)and{a mathematical formula}ArgsU⊆undec(LabArgpref). Let{a mathematical formula}LabArgIO=LabArgpref↓ArgsIOand let{a mathematical formula}LabArgUbe some labelling of{a mathematical formula}AF↓ArgsU. Then{a mathematical formula}LabArgIOis compatible with{a mathematical formula}LabArgU.
     </paragraph>
     <paragraph label="Proof">
      We note that {a mathematical formula}∀B∈ArgsU attacking some {a mathematical formula}A∈ArgsIO it holds that {a mathematical formula}A∈out(LabArgIO) since arguments labelled in are not attacked by arguments labelled undec in {a mathematical formula}LabArgpref. Let {a mathematical formula}A∈ArgsIO.
     </paragraph>
     <list>
      <list-item label="•">
       If {a mathematical formula}A∈in(LabArgIO), then, for all {a mathematical formula}B∈ArgsIO attacking A, it holds that {a mathematical formula}B∈out(LabArgIO) since {a mathematical formula}LabArgpref is a complete labelling. Furthermore, no {a mathematical formula}B∈ArgsU attacks A.
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A∈out(LabArgIO), then there exists {a mathematical formula}B∈ArgsIO attacking A such that {a mathematical formula}B∈in(LabArgIO) since {a mathematical formula}LabArgpref is a complete labelling.
      </list-item>
     </list>
    </section>
    <section label="Appendix B">
     <section-title>
      Proofs
     </section-title>
     <paragraph label="Proof of Lemma 1">
      Let {a mathematical formula}AF⊛=〈Ar⊛,Att⊛〉 be such that
      <list>
       {a mathematical formula}Ar⊛=Ar∪{X} where {a mathematical formula}X∉Ar and{a mathematical formula}Att⊛=(Att∖{(B,A)∈Att|A∈Args,A∈in(LabArg)∪undec(LabArg)})∪({(X,A)|A∈Args,A∈out(LabArg)}∪{(A,A)|A∈Args,A∈undec(LabArg)}).Let
      </list>
      <paragraph>
       {a mathematical formula}A∈Args. If {a mathematical formula}A∈in(LabArg⊛), then A is not attacked by any argument B in {a mathematical formula}AF⊛, so trivially, for all attackers B of A in {a mathematical formula}AF⊛, {a mathematical formula}B∈out(LabArg⊛). Thus, A is legally labelled in by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. If {a mathematical formula}A∈out(LabArg⊛), then A is attacked by X in {a mathematical formula}AF⊛ and {a mathematical formula}X∈in(LabArg⊛), so A is legally labelled out by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. If {a mathematical formula}A∈undec(LabArg⊛), then A is only attacked by itself in {a mathematical formula}AF⊛. Thus, there exists an attacker of A in {a mathematical formula}AF⊛ labelled undec by {a mathematical formula}LabArg⊛ and there exists no attacker of A in {a mathematical formula}AF⊛ labelled in by {a mathematical formula}LabArg⊛, so A is legally labelled undec by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛.Since furthermore {a mathematical formula}X∈Ar⊛∖Ar is legally labelled in by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛, {a mathematical formula}AF⊛ and {a mathematical formula}LabArg⊛ satisfy the conditions in Definition 1, so {a mathematical formula}AF⊛ is a revision of {a mathematical formula}AF w.r.t. {a mathematical formula}Args by {a mathematical formula}LabArg.  □
      </paragraph>
     </paragraph>
     <paragraph label="Proof of Proposition 3">
      Since {a mathematical formula}undec(LabArg)=∅, it follows from Observation 2 that {a mathematical formula}undec(LabArg⊛)=∅. Furthermore, by Definition 1 all {a mathematical formula}A∈Ar⊛∖Ar are legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Let {a mathematical formula}B∈Ar. If {a mathematical formula}B∈Args, then, by Definition 1, B is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. If {a mathematical formula}B∉Args, then {a mathematical formula}B∈in(LabArgpref)∪out(LabArgpref), so B is legally labelled by {a mathematical formula}LabArgpref in {a mathematical formula}AF. By Lemma 38 in Appendix A, B is legally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF, and by Lemma 37 in Appendix A, B is legally labelled by {a mathematical formula}LabArg⊛ in {a mathematical formula}AF⊛. Since all arguments in {a mathematical formula}AF⊛ are legally labelled by {a mathematical formula}LabArg⊛ and {a mathematical formula}undec(LabArg⊛)=∅, {a mathematical formula}LabArg⊛ is a stable labelling of {a mathematical formula}AF⊛.  □
     </paragraph>
     <paragraph label="Proof of Lemma 5">
      <list>
       <list-item label="1.">
        Let {a mathematical formula}Args=undec(LabArgpref). Clearly there exists some {a mathematical formula}LabArg with {a mathematical formula}LabArgpref⊑LabArg and {a mathematical formula}undec(LabArg)=∅. Then trivially, {a mathematical formula}∀A∈undec(LabArgpref)∖Args=∅ it holds that A is legally labelled by {a mathematical formula}LabArg. Thus, {a mathematical formula}Args and {a mathematical formula}LabArg satisfy the conditions in Definition 4, but {a mathematical formula}Args may not be a minimal set satisfying the conditions. If for all {a mathematical formula}Args1⊂Args and for all {a mathematical formula}LabArg′ of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊑LabArg′ and {a mathematical formula}undec(LabArg′)=∅ there exists some {a mathematical formula}A∈undec(LabArgpref)∖Args1 that is illegally labelled by {a mathematical formula}LabArg′, then {a mathematical formula}Args is a minimal set satisfying the conditions in Definition 4, so it is an enforcement set (and {a mathematical formula}LabArg an enforcement labelling w.r.t. {a mathematical formula}Args). Else, there is a smallest {a mathematical formula}Args1⊂Args satisfying that {a mathematical formula}∃LabArg1 with {a mathematical formula}LabArgpref⊑LabArg1 and {a mathematical formula}undec(LabArg1)=∅ such that {a mathematical formula}∀A∈undec(LabArgpref)∖Args1: A is legally labelled by {a mathematical formula}LabArg1. Thus, {a mathematical formula}Args1 is an enforcement set (and {a mathematical formula}LabArg1 an enforcement labelling).
       </list-item>
       <list-item label="2.">
        Let {a mathematical formula}LabArg be an enforcement labelling w.r.t. {a mathematical formula}Args. If {a mathematical formula}Args=∅, then, by Lemma 39 in Appendix A, all arguments in Ar are legally labelled by {a mathematical formula}LabArg, so since {a mathematical formula}undec(LabArg)=∅, {a mathematical formula}LabArg is a stable labelling. Thus, {a mathematical formula}LabArgpref=LabArg is a stable labelling.If {a mathematical formula}LabArgpref is a stable labelling then {a mathematical formula}undec(LabArgpref)=∅. Then {a mathematical formula}Args=∅ is the minimal set satisfying Definition 4 with {a mathematical formula}LabArg=LabArgpref as the only enforcement labelling.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof of Lemma 8">
      <list>
       <list-item label="1.">
        Let {a mathematical formula}Args=undec(LabArgpref) and let {a mathematical formula}LabArg be such that {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅. Since {a mathematical formula}LabArgpref is a maximal complete labelling, {a mathematical formula}∃A∈Args such that A is illegally labelled by {a mathematical formula}LabArg. Since this holds for all such labellings {a mathematical formula}LabArg, {a mathematical formula}Args satisfies the conditions in Definition 5. However, {a mathematical formula}Args may not be a minimal set satisfying these conditions. If for all {a mathematical formula}Args1⊂Args there exists {a mathematical formula}LabArg1 with {a mathematical formula}LabArgpref⊏LabArg1 and {a mathematical formula}undec(LabArg1)=∅ such that all {a mathematical formula}A∈Args1 are legally labelled by {a mathematical formula}LabArg1, then {a mathematical formula}Args is a minimal set satisfying the conditions in Definition 5, so it is a preventing set w.r.t. {a mathematical formula}LabArgpref. Else, there is a smallest {a mathematical formula}Args1⊂Args satisfying that {a mathematical formula}∀LabArg′ with {a mathematical formula}LabArgpref⊏LabArg′ and {a mathematical formula}undec(LabArg′)=∅ it holds that {a mathematical formula}∃A∈Args1 such that A is illegally labelled by {a mathematical formula}LabArg′. Then {a mathematical formula}Args1 is a preventing set w.r.t. {a mathematical formula}LabArgpref.
       </list-item>
       <list-item label="2.">
        Assume {a mathematical formula}Args=∅ is a preventing set w.r.t. {a mathematical formula}LabArgpref and {a mathematical formula}LabArgpref is not a stable labelling. Then {a mathematical formula}∃LabArg⊏LabArgpref and, by Definition 5, {a mathematical formula}∃A∈Args such that A is illegally labelled. Contradiction since {a mathematical formula}∄A∈Args, so {a mathematical formula}LabArgpref is a stable labelling.Assume {a mathematical formula}LabArgpref is a stable labelling. Then {a mathematical formula}undec(LabArgpref)=∅ and {a mathematical formula}Args=∅ satisfies Definition 5.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof of Theorem 11">
      We prove that all {a mathematical formula}Args∈S are enforcement sets and that all enforcement sets are contained in S. We note that, by Lemma 8{a mathematical formula}Sprev≠∅. If {a mathematical formula}Sprev={∅} then {a mathematical formula}S={∅}. Then, by Lemma 8, {a mathematical formula}LabArgpref is a stable labelling and by Lemma 5 the empty set is the only enforcement set. If {a mathematical formula}Sprev≠{∅} then by Lemma 8{a mathematical formula}∀Argsprev∈Sprev: {a mathematical formula}Argsprev≠∅.
     </paragraph>
     <list>
      <list-item label="•">
       Let {a mathematical formula}Args∈S and assume that {a mathematical formula}Args is not an enforcement set. Then either {a mathematical formula}Args is not a minimal set satisfying the conditions in Definition 4 or it does not satisfy the conditions at all.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}Argsenf be an enforcement set and assume that {a mathematical formula}Argsenf∉S. Then either {a mathematical formula}∃Argsprev∈Sprev such that {a mathematical formula}Argsenf∩Argsprev=∅ or there exists a minimal set {a mathematical formula}Args⊂Argsenf satisfying that {a mathematical formula}∀Argsprev∈Sprev:Args∩Argsprev≠∅.
      </list-item>
     </list>
     <paragraph label="Proof of Proposition 15">
      Assume there exists no odd-length cycle of arguments all labelled undec by {a mathematical formula}LabArgpref. Then {a mathematical formula}AFu=AF↓undec(LabArgpref) comprises no odd-length cycle. By Corollary 36 in [10], {a mathematical formula}AFu has a stable labelling {a mathematical formula}LabArgu. We observe that, for all arguments {a mathematical formula}A∈in(LabArgpref)∪out(LabArgpref) that are attacking some argument in {a mathematical formula}undec(LabArgpref), it holds that {a mathematical formula}A∈out(LabArgpref) and that, for all arguments {a mathematical formula}B∈in(LabArgpref)∪out(LabArgpref) that are attacked by some argument in {a mathematical formula}undec(LabArgpref), it holds that {a mathematical formula}B∈out(LabArgpref).Let {a mathematical formula}LabArg=LabArgpref↓undec(LabArgpref)∪out(LabArgpref)∪LabArgu, so {a mathematical formula}undec(LabArg)=∅ and {a mathematical formula}LabArgpref⊑LabArg. We show that {a mathematical formula}LabArg is a complete labelling of {a mathematical formula}AF:
      <list>
       Let {a mathematical formula}A∈in(LabArg). If {a mathematical formula}A∈in(LabArgpref), then, by Lemma 38 in Appendix A, A is legally labelled by {a mathematical formula}LabArg. If {a mathematical formula}A∈in(LabArgu), then, for all attackers B of A such that {a mathematical formula}B∈in(LabArgpref)∪out(LabArgpref), {a mathematical formula}B∈out(LabArgpref) (by the above observation), and thus {a mathematical formula}B∈out(LabArg). Furthermore, for all attackers C of A such that {a mathematical formula}C∈undec(LabArgpref), {a mathematical formula}C∈out(LabArgu) since {a mathematical formula}LabArgu is a stable labelling of {a mathematical formula}AFu, and thus {a mathematical formula}C∈out(LabArg). Thus, A is legally labelled in by {a mathematical formula}LabArg.Let {a mathematical formula}A∈out(LabArg). If {a mathematical formula}A∈out(LabArgpref), then, by Lemma 38 in Appendix A, A is legally labelled by {a mathematical formula}LabArg. If {a mathematical formula}A∈out(LabArgu), then there exists an attacker B of A such that {a mathematical formula}B∈undec(LabArgpref) and {a mathematical formula}B∈in(LabArgu) since {a mathematical formula}LabArgu is a stable labelling of {a mathematical formula}AFu, and thus {a mathematical formula}B∈in(LabArg). Thus, A is legally labelled out by {a mathematical formula}LabArg.If
      </list>
      <paragraph>
       {a mathematical formula}LabArgpref is a stable labelling, then {a mathematical formula}undec(LabArgpref)=∅. Thus there exists no odd-length cycle of arguments all labelled undec.  □
      </paragraph>
     </paragraph>
     <paragraph label="Proof of Proposition 16">
      Since {a mathematical formula}AF↓undec(LabArgpref)∖S comprises no odd-length cycles, by Corollary 36 in [10] it has a stable labelling {a mathematical formula}LabArgstable. Let {a mathematical formula}LabArg′=LabArgstable∪LabArgo be a labelling of {a mathematical formula}AF↓undec(LabArgpref) where {a mathematical formula}LabArgo is a labelling of arguments in {a mathematical formula}AF↓S such that {a mathematical formula}out(LabArgo)=S, and let {a mathematical formula}LabArg=LabArg′∪LabArgpref↓in(LabArgpref)∪out(LabArgpref). Clearly {a mathematical formula}LabArg is a labelling of {a mathematical formula}AF such that {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅.
     </paragraph>
     <list>
      <list-item label="•">
       Let {a mathematical formula}A∈in(LabArgpref)∪out(LabArgpref). By Lemma 38 in Appendix A, A is legally labelled by {a mathematical formula}LabArg.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}A∈undec(LabArgpref)∖S and {a mathematical formula}LabArg(A)=in. Then, for all attackers B of A such that {a mathematical formula}B∈undec(LabArgpref)∖S, {a mathematical formula}LabArgstable(B)=out and thus {a mathematical formula}LabArg(B)=out. Furthermore, for all attackers C of A such that {a mathematical formula}C∈S, {a mathematical formula}LabArgo(C)=out and thus {a mathematical formula}LabArg(C)=out. Additionally, for all attackers D of A such that {a mathematical formula}D∈in(LabArgpref)∪out(LabArgpref), {a mathematical formula}LabArgpref(D)=out and thus {a mathematical formula}LabArg(D)=out. Hence, A is legally labelled in by {a mathematical formula}LabArg.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}A∈undec(LabArgpref)∖S and {a mathematical formula}LabArg(A)=out. Then there exists an attacker B of A such that {a mathematical formula}B∈undec(LabArgpref)∖S and {a mathematical formula}LabArgstable(B)=in and thus {a mathematical formula}LabArg(B)=in. Hence, A is legally labelled out by {a mathematical formula}LabArg.
      </list-item>
     </list>
     <paragraph label="Proof of Proposition 18">
      If {a mathematical formula}LabArgpref is a stable labelling, then for all SCCs {a mathematical formula}Args it holds that {a mathematical formula}LabArgpref↓Args is a stable labelling w.r.t. {a mathematical formula}(AF↓Args,parents(Args),LabArgpref↓parents(Args),Att∩(parents(Args)×Args)). This violates the condition in Definition 7, so there exists no responsible SCC.If {a mathematical formula}LabArgpref is not a stable labelling then since the attacks between SCCs are by definition unidirectional, there exists a sequence of SCCs {a mathematical formula}Args1,…,Argsn ({a mathematical formula}∀i≠k:Argsi≠Argsk) such that if {a mathematical formula}Argsi is attacked by {a mathematical formula}Argsk ({a mathematical formula}i≠k), then {a mathematical formula}k&lt;i. By Corollary 42 in Appendix A, {a mathematical formula}LabArgpref=LabArg1∪…∪LabArgn where {a mathematical formula}LabArgi is a labelling of {a mathematical formula}Argsi, {a mathematical formula}LabArg1 is a complete labelling of {a mathematical formula}Args1, and for all {a mathematical formula}j∈{2…n} it holds that {a mathematical formula}LabArgj is compatible with {a mathematical formula}LabArg1∪…∪LabArgj−1. If {a mathematical formula}LabArg1 is not a stable labelling of {a mathematical formula}Args1, then {a mathematical formula}Args1 satisfies Definition 7, so there exists a responsible SCC w.r.t. {a mathematical formula}LabArgpref. Else, there exists {a mathematical formula}LabArgi such that, for all {a mathematical formula}LabArgj with {a mathematical formula}j&lt;i, it holds that {a mathematical formula}undec(LabArgj)=∅ and {a mathematical formula}undec(LabArgi)≠∅. Since by the construction of our sequence of SCCs, for all {a mathematical formula}Args′∈parentSCCs(Argsi) it holds that {a mathematical formula}Args′=Argsj for some {a mathematical formula}j&lt;i, it follows that, for all these {a mathematical formula}Args′, {a mathematical formula}LabArgpref↓Args′ is a stable labelling w.r.t. {a mathematical formula}(AF↓Args′,parents(Args′),LabArgpref↓parents(Args′),Att∩(parents(Args′)×Args′)). Furthermore, since {a mathematical formula}undec(LabArgi)≠∅, it follows that there exists no stable labelling w.r.t. {a mathematical formula}(AF↓Argsi,parents(Argsi),LabArgpref↓parents(Argsi),Att∩(parents(Argsi)×Argsi)) that is more committed than {a mathematical formula}LabArgi. (If there was such a labelling, then {a mathematical formula}LabArgpref would be a stable labelling.)  □
     </paragraph>
     <paragraph label="Proof of Proposition 19">
      Let {a mathematical formula}ArgsIO=in(LabArgpref)∪out(LabArgpref) and {a mathematical formula}ArgsU=undec(LabArgpref). We observe that since arguments labelled undec are not attacked by arguments labelled in by a complete labelling, {a mathematical formula}∀B∈ArgsIO attacking some {a mathematical formula}A∈ArgsU, it holds that {a mathematical formula}B∈out(LabArgpref↓ArgsIO).We first prove that {a mathematical formula}LabArgpref↓ArgsU is a complete labelling of {a mathematical formula}AF↓ArgsU. Since by Lemma 44 in Appendix A, {a mathematical formula}LabArgpref↓ArgsU is a complete labelling w.r.t. {a mathematical formula}(AF↓ArgsU,ArgsIO,LabArgpref↓ArgsIO,Att∩(ArgsIO×ArgsU)), it follows that {a mathematical formula}∀A∈ArgsU and {a mathematical formula}∀B∈ArgsU attacking A, {a mathematical formula}B∉in(LabArgpref↓ArgsU), and {a mathematical formula}∃C∈ArgsU attacking A such that {a mathematical formula}C∈undec(LabArgpref↓ArgsU) since by our above observation {a mathematical formula}∄D∈ArgsIO attacking A such that {a mathematical formula}D∈undec(LabArgpref↓ArgsIO). Thus, all {a mathematical formula}A∈ArgsU are legally labelled by {a mathematical formula}LabArgpref↓ArgsU, so {a mathematical formula}LabArgpref↓ArgsU is a complete labelling of {a mathematical formula}AF↓ArgsU.We now prove that there exists no other complete labelling of {a mathematical formula}AF↓ArgsU. Assume there exists a complete labelling {a mathematical formula}LabArgU of {a mathematical formula}AF↓ArgsU such that {a mathematical formula}undec(LabArgU)≠ArgsU. Clearly, {a mathematical formula}LabArgpref⊏LabArgpref↓ArgsIO∪LabArgU.By Lemma 46 in Appendix A, {a mathematical formula}LabArgpref↓ArgsIO is compatible with {a mathematical formula}LabArgU. Furthermore, {a mathematical formula}LabArgU is compatible with {a mathematical formula}LabArgpref↓ArgsIO:
     </paragraph>
     <list>
      <list-item label="•">
       If {a mathematical formula}A∈in(LabArgU), then {a mathematical formula}∀B∈ArgsU attacking A, {a mathematical formula}B∈out(LabArgU) since {a mathematical formula}LabArgU is a complete labelling of {a mathematical formula}AF↓ArgsU. Furthermore {a mathematical formula}∀B∈ArgsIO attacking A, {a mathematical formula}B∈out(LabArgpref↓ArgsIO) as previously noted.
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A∈out(LabArgU), then {a mathematical formula}∃B∈ArgsU attacking A such that {a mathematical formula}B∈in(LabArgU) since {a mathematical formula}LabArgU is a complete labelling of {a mathematical formula}AF↓ArgsU.
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A∈undec(LabArgU), then {a mathematical formula}∀B∈ArgsU attacking A, {a mathematical formula}B∉in(LabArgU), and {a mathematical formula}∃B∈ArgsU attacking A such that {a mathematical formula}B∈undec(LabArgU) since {a mathematical formula}LabArgU is a complete labelling of {a mathematical formula}AF↓ArgsU. Furthermore, {a mathematical formula}∀B∈ArgsIO attacking A, {a mathematical formula}B∉in(LabArgpref↓ArgsIO) as previously noted.
      </list-item>
     </list>
     <paragraph label="Proof of Proposition 20">
      Since every non-empty AF has an initial SCC, {a mathematical formula}AF↓undec(LabArgpref) has an initial SCC if and only if {a mathematical formula}undec(LabArgpref)≠∅, i.e. if and only if {a mathematical formula}LabArgpref is not a stable labelling. By Definition 8 this initial SCC is a SCUP w.r.t. {a mathematical formula}LabArgpref.  □
     </paragraph>
     <paragraph label="Proof of Proposition 21">
      By Definition 7, there exists no stable labelling w.r.t. {a mathematical formula}(AF↓Args,parents(Args),LabArgpref↓parents(Args),Att∩(parents(Args)×Args)) that is more or equally committed than {a mathematical formula}LabArgpref↓Args. Thus, {a mathematical formula}undec(LabArgpref↓Args)≠∅. Let {a mathematical formula}Args′=undec(LabArgpref↓Args). Since {a mathematical formula}Args is an SCC of {a mathematical formula}AF, {a mathematical formula}Args′ is an SCC of {a mathematical formula}AF↓undec(LabArgpref).By Definition 7, for all {a mathematical formula}Argsp∈parentSCCs(Args) it holds that {a mathematical formula}LabArgpref↓Argsp is a stable labelling w.r.t. {a mathematical formula}(AF↓Argsp,parents(Argsp),LabArgpref↓parents(Argsp),Att∩(parents(Argsp)×Argsp)). Thus, {a mathematical formula}∄A∈parents(Args),B∈Args such that A attacks B and {a mathematical formula}A∈undec(LabArgpref). Since {a mathematical formula}Args′⊆Args and since {a mathematical formula}Args∖Args′⊆in(LabArgpref)∪out(LabArgpref), it follows that {a mathematical formula}∄A∈parents(Args′),B∈Args′ such that A attacks B and {a mathematical formula}A∈undec(LabArgpref). Thus, in {a mathematical formula}AF↓undec(LabArgpref) it holds that {a mathematical formula}Args′ is an SCC and {a mathematical formula}Args′ is not attacked by any arguments not contained in {a mathematical formula}Args′. Thus, {a mathematical formula}Args′ is an initial SCC of {a mathematical formula}AF↓undec(LabArgpref), so it is a SCUP w.r.t. {a mathematical formula}LabArgpref.  □
     </paragraph>
     <paragraph label="Proof of Lemma 22">
      Assume {a mathematical formula}∃LabArg of {a mathematical formula}AF with {a mathematical formula}LabArgpref⊏LabArg and {a mathematical formula}undec(LabArg)=∅ such that {a mathematical formula}∀A∈Args, A is legally labelled by {a mathematical formula}LabArg in {a mathematical formula}AF. Let {a mathematical formula}Args1=in(LabArgpref)∪out(LabArgpref)∪Args, {a mathematical formula}Args2=Ar∖Args1, and {a mathematical formula}LabArg1=LabArg↓Args1. Since {a mathematical formula}Args is a SCUP, it holds that {a mathematical formula}∀A∈Args and ∀B attacking A, {a mathematical formula}B∈Args1. Thus, A being legally labelled by {a mathematical formula}LabArg only depends on {a mathematical formula}LabArg1. Let {a mathematical formula}LabArg2 be some labelling of {a mathematical formula}Args2. Then, {a mathematical formula}∀A∈Args, A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF. Furthermore, clearly {a mathematical formula}LabArgpref⊏LabArg1∪LabArg2. Then, by Lemma 38 in Appendix A, {a mathematical formula}∀A∈in(LabArgpref)∪out(LabArgpref) it holds that A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF. Thus, {a mathematical formula}∀A∈Args1, A is legally labelled by {a mathematical formula}LabArg1∪LabArg2 in {a mathematical formula}AF. Then, by Lemma 43 in Appendix A, {a mathematical formula}LabArg1 is compatible with {a mathematical formula}LabArg2 (for any labelling {a mathematical formula}LabArg2 of {a mathematical formula}Args2). Furthermore, by Lemma 45 in Appendix A, there exists a labelling {a mathematical formula}LabArg2′ that is compatible with {a mathematical formula}LabArg1. Then, by Lemma 40 in Appendix A, {a mathematical formula}LabArg1∪LabArg2′ is a complete labelling of {a mathematical formula}AF. Contradiction since {a mathematical formula}LabArgpref⊏LabArg1∪LabArg2′.  □
     </paragraph>
     <paragraph label="Proof of Proposition 28">
      By Proposition 19 and the SCC recursiveness of complete labellings [16], {a mathematical formula}AF↓Args has no stable labelling. Then, by Corollary 36 in [10], there exists an odd-length cycle in {a mathematical formula}Args.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>