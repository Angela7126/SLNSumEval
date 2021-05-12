<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A general semi-structured formalism for computational argumentation: Definition, properties, and examples of application.
   </title>
   <abstract>
    In the field of computational argumentation several formalisms featuring different levels of abstraction and focusing on different aspects of the argumentation process have been developed. Their combined use, necessary to achieve a comprehensive formal coverage of the argumentation phenomenon, gives rise to a nontrivial interplay between different abstraction levels, so that counterintuitive or undesirable outcomes may result from the combination of formalisms which appear to be well-behaved when considered in isolation. To address this problem we introduce a semi-structured formalism for argumentation, called LAF-ensembles, capturing a set of essential features of structured arguments and define a class of set based argumentation frameworks appropriate to support a semantic assessment of arguments for LAF-ensembles. It is shown that, under suitable assumptions, the combination of a LAF-ensemble and of an appropriate argumentation framework is guaranteed to produce justification outcomes satisfying a set of essential requirements. The generality and usefulness of the proposed approach are demonstrated by illustrating its ability to capture as instances and enhance two structured argumentation formalisms from the literature, namely Vreeswijk's abstract argument systems and Modgil and Prakken's ASPIC+. In particular, a revised version of the latter formalism, properly dealing with generic contrariness and solving significant technical limitations of ASPIC+, is proposed.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In the last decades computational argumentation has emerged as a powerful approach to the study of reasoning in the presence of incomplete and conflicting information with a wide range of applications in AI [1], [2]. In this context several formalisms at various levels of abstraction have been developed, in order to support the investigation of general and reusable properties, valid for all the instances of a given abstract model.
     </paragraph>
     <paragraph>
      At the highest abstraction level, internal properties of arguments are ignored and only their relationships are considered. This is exemplified by the well-known formalism of argumentation frameworks proposed by Dung [3], focused on a binary relation of attack between arguments, and by subsequent proposals like bipolar argumentation frameworks [4], where a support relation is also considered, and Abstract Dialectical Frameworks [5], capturing a generic notion of dependence among arguments. In these works, the main interest is typically on assessing the acceptance or justification status of arguments on the basis of their relationships and according to some criteria formalized by the notion of argumentation semantics.
     </paragraph>
     <paragraph>
      Structured argumentation formalisms [6] can be regarded as less abstract as they provide some details of how arguments are built and, accordingly, of how and why they relate (and, in particular, attack) each other, possibly leaving unspecified or partially specified other aspects, e.g. the actual language used to build arguments or the preference relation (if any) holding over them.
     </paragraph>
     <paragraph>
      It is rather common that in a structured argumentation formalism the assessment of the acceptance or justification status of the produced arguments is achieved by resorting to a more abstract representation. For instance, given a set of structured arguments where some attack relation is identified, one may first produce a corresponding argumentation framework, where everything but the attack relation is ignored, then apply an argumentation semantics to identify the accepted abstract arguments, and finally project back the results so as to identify the corresponding accepted structured arguments.
     </paragraph>
     <paragraph>
      This gives rise to a nontrivial interplay among concepts and properties defined at the different levels of abstraction. In the example above, the properties of the set of accepted structured arguments depend in some way on the set of accepted abstract arguments, which in turn depends on the argumentation semantics applied and on the argumentation framework built, which in turn depends on the correspondence drawn between the structured level and its abstract representation and on the notion of attack adopted.
     </paragraph>
     <paragraph>
      If, in the end, something goes wrong, i.e. the set of accepted structured arguments has some undesirable features, it may not be obvious to ‘find the culprit’ (or anyway to find the best way to fix the problem) among the many assumptions and technical choices involved in the various steps of this process, all of which may sound reasonable when considered in isolation, but whose combination may turn out not to work well.
     </paragraph>
     <paragraph>
      This calls for the study of a set of properties, spanning across the different abstraction levels of an argumentation system, which are able altogether to guarantee that such problems do not arise.
     </paragraph>
     <paragraph>
      This kind of investigation has been pioneered by the work in [7] where it is pointed out that several argumentation systems fail to comply with a set of basic desirable properties, called rationality postulates, and it is shown how to guarantee that they are satisfied for a class of rule-based argumentation systems using a language equipped with classical negation.
     </paragraph>
     <paragraph>
      Recently, it has been shown in [8] that the technical solutions proposed in [7] may run into troubles when considering a language equipped with a generic contrariness relation, rather than classical negation, and the need for a novel approach suitable to this generalized context has been evidenced.
     </paragraph>
     <paragraph>
      Moreover, the definition of these postulates and even more the technical solutions proposed to guarantee their satisfaction are formalism specific and their extension to other classes of argumentation systems, like Vreeswijk's abstract argumentation systems [9], has not been investigated yet and represents an open problem.
     </paragraph>
     <paragraph>
      To provide a comprehensive answer to these research issues we adopt the standpoint that both postulates and solutions are investigated at a higher level of abstraction with an approach that is as formalism independent as possible. In this way we not only ensure generality and wider applicability of the achieved results but also that they are, in a sense, more robust since they rely (explicitly or implicitly) on less specific assumptions and, by construction, must be valid in a larger variety of cases. To this purpose, we introduce a semi-structured argumentation formalism, called LAF-ensembles, which captures a set of essential features of structured arguments, while not being committed to any specific way of actually building them. Following this line, we propose a set of requirements which generalize to LAF-ensembles those already introduced in the literature and a general method, resorting to set based argumentation frameworks, to guarantee the satisfaction of these requirements. We stress that the proposed requirements represent a generalization rather than a modification of similar ideas already presented in the literature, lying at a novel abstraction level. The choice of this abstraction level turns out to be a key factor in the identification of the general well-founded solution we propose, which instead includes several original aspects with respect to previous literature. The approach is validated by applying it to two argumentation formalisms, namely Vreeswijk's abstract argumentation systems [9] and {a mathematical formula}ASPIC+[10], and showing that it is not just able to capture them as instances but, more importantly, to support the identification of significant problems and the definition of proper solutions, based on the underlying general principles. In particular, we propose a revised version of {a mathematical formula}ASPIC+ which on the one hand turns out to be more expressive, as it deals properly with any form of contrariness relation, and on the other hand is conceptually and technically more solid, as it avoids the limitations and some undesirable side-effects of the previous solution, even in the case of classical negation. Moreover the approach is able to reveal inter-formalism relationships as we show by identifying a previously unknown correspondence between Vreeswijk's approach and Dung's semantics.
     </paragraph>
     <paragraph>
      These results support the claim that the main contribution of the paper is introducing and validating a novel general formal tool supporting the analysis, revision, and possibly design from scratch of argumentation systems, applicable to a virtually unlimited range of diverse actual argumentation formalisms.
     </paragraph>
     <paragraph>
      The paper is organized as follows.
     </paragraph>
     <paragraph>
      After recalling some necessary background in Section 2, we introduce LAF-ensembles in Section 3. To ensure generality, LAF-ensembles make very limited assumptions on the underlying language, which is not required to be closed with respect to classical negation but is only assumed to be equipped with a set-level inhibition function, satisfying some very mild constraints.
     </paragraph>
     <paragraph>
      On these bases, we define in Section 4 a generic notion of argument justification and specify some fundamental requirements for it. We then identify in Section 5 a fundamental property for LAF-ensembles, called inhibition infallibility consonance ({a mathematical formula}II-consonance) and characterize in Section 6 a family of argumentation frameworks which are appropriate to provide an abstract representation of LAF-ensembles. These argumentation frameworks are called set based since their nodes correspond to sets of arguments, rather than to individual arguments as in many other approaches.
     </paragraph>
     <paragraph>
      One of the main theoretical results of the paper is then to show that the argument justification function induced by any complete extension of an appropriate argumentation framework for an {a mathematical formula}II-consonant LAF-ensemble satisfies all the desired requirements, as proved in Section 7.
     </paragraph>
     <paragraph>
      As mentioned above, to exemplify the usefulness of the modeling approach based on LAF-ensembles and of the relevant theoretical results we demonstrate their use in capturing and revising two structured argumentation formalisms from the literature, namely Vreeswijk's abstract argumentation systems (AASs) [9] and {a mathematical formula}ASPIC+[10].
     </paragraph>
     <paragraph>
      In particular, in Section 8 we show that AASs can be seen as an instance of LAF-ensembles and, accordingly, we define appropriate argumentation frameworks for them. In this way we reveal, for the first time in the literature, a relationship between Vreeswijk's theory and Dung's theory. More precisely, we show a correspondence between Vreeswijk's notion of extension and the stable extensions of the relevant set based argumentation framework. Moreover, we identify a missing correspondence between Vreeswijk's ultimately undefeated arguments and the grounded extension of the relevant set based argumentation framework, and point out that this is due to a counterintuitive behavior of Vreeswijk's theory in some cases.
     </paragraph>
     <paragraph>
      Section 9 shows more extensively the ability of LAF-ensembles not only to encompass other formalisms as specific instances but also to provide a set of reference properties supporting their verification and revision. In particular we discuss the problems arising in {a mathematical formula}ASPIC+ when a generic contrariness notion is adopted and provide a solution by defining a revisited version of {a mathematical formula}ASPIC+ based on the concepts introduced in Sections 3–7. In addition to solving the problem pointed out, the revisited version is shown to avoid some peculiarities arising even in the case where a language equipped with classical negation is assumed.
     </paragraph>
     <paragraph>
      The paper is completed by a discussion of related works in Section 10 and by some conclusive remarks in Section 11. All proofs are given in Appendix A.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      We review in this section the necessary background on Dung's theory of argumentation frameworks. Other useful notions from previous literature will be recalled in later sections where appropriate.
     </paragraph>
     <paragraph>
      An argumentation framework simply encodes a binary attack relation between the elements of a set, usually referred to as arguments.{sup:1}
     </paragraph>
     <paragraph label="Definition 1">
      An argumentation framework is a pair {a mathematical formula}AF=〈AA,↠〉, where AA is a set of arguments and {a mathematical formula}↠⊆(AA×AA) is a binary relation on AA, called the attack relation.
     </paragraph>
     <paragraph>
      An argumentation framework {a mathematical formula}AF=〈AA,↠〉 can be obviously represented as a directed graph, called the defeat graph, whose edges correspond to the elements of the attack relation. When {a mathematical formula}(α,β)∈↠ (also denoted as {a mathematical formula}α↠β) we say that α attacks β.
     </paragraph>
     <paragraph label="Definition 2">
      Since we will frequently consider properties of sets of arguments, it is useful to define suitable notations for them. Given an argumentation framework {a mathematical formula}AF=〈AA,↠〉, an argument {a mathematical formula}α∈AA and two (not necessarily disjoint) sets {a mathematical formula}X,Y⊆AA, we define: {a mathematical formula}X↠α≜∃β∈X:β↠α; {a mathematical formula}α↠X≜∃β∈X:α↠β; {a mathematical formula}X↠Y≜∃α∈X,β∈Y:α↠β; {a mathematical formula}X−≜{α∈AA|α↠X}; {a mathematical formula}X+≜{α∈AA|X↠α}.
     </paragraph>
     <paragraph>
      With a little abuse of notation, for an argument α, we will sometimes write {a mathematical formula}α− for {a mathematical formula}{α}− and similarly {a mathematical formula}α+ for {a mathematical formula}{α}+.
     </paragraph>
     <paragraph>
      Given an argumentation framework encoding the conflicts in a set of arguments, a fundamental problem consists in determining the conflict outcome, namely which arguments can be considered justified. An argumentation semantics can be conceived, in broad terms, as a formal way to answer this question. More formally, in the extension-based approach an argumentation semantics σ specifies the criteria for identifying, for a generic argumentation framework, a set of extensions, where each extension is a set of arguments considered to be acceptable together. Given a generic argumentation semantics σ, the set of extensions prescribed by σ for a given argumentation framework AF is denoted as {a mathematical formula}Eσ(AF). Several argumentation semantics are quickly recalled in Definition 3, along with some basic underlying notions. For more details and introductory material on argumentation semantics at a general level the reader is referred to [11].
     </paragraph>
     <paragraph label="Definition 3">
      Let {a mathematical formula}AF=〈AA,↠〉 be an argumentation framework, {a mathematical formula}α∈AA an argument, and {a mathematical formula}X⊆AA a set of arguments
     </paragraph>
     <list>
      <list-item label="•">
       X is conflict-free, denoted as {a mathematical formula}X∈ECF(AF), if and only if {a mathematical formula}X∩X−=∅;
      </list-item>
      <list-item label="•">
       α is acceptable with respect to X (or α is defended by X) if and only if {a mathematical formula}{α}−⊆X+;
      </list-item>
      <list-item label="•">
       the function {a mathematical formula}FAF:2AA→2AA which, given a set {a mathematical formula}X⊆AA, returns the set of the acceptable arguments with respect to X, is called the characteristic function of AF;
      </list-item>
      <list-item label="•">
       X is admissible (denoted as {a mathematical formula}X∈EAD(AF)) if and only if {a mathematical formula}X∈ECF(AF) and {a mathematical formula}X⊆FAF(X);
      </list-item>
      <list-item label="•">
       X is a complete extension (denoted as {a mathematical formula}X∈ECO(AF)) if and only if {a mathematical formula}X∈ECF(AF) and {a mathematical formula}X=FAF(X);
      </list-item>
      <list-item label="•">
       X is the grounded extension (denoted as {a mathematical formula}X=GR(AF) or {a mathematical formula}X∈EGR(AF)) if and only if X is the least fixed point of {a mathematical formula}FAF (equivalently, the least complete extension);
      </list-item>
      <list-item label="•">
       X is a preferred extension (denoted as {a mathematical formula}X∈EPR(AF)) if and only if X is a maximal (with respect to set inclusion) admissible set;
      </list-item>
      <list-item label="•">
       X is a stable extension (denoted as {a mathematical formula}X∈EST(AF)) if and only if {a mathematical formula}X+=AA∖X (implying {a mathematical formula}X∈ECF(AF));
      </list-item>
      <list-item label="•">
       X is a semi-stable extension (denoted as {a mathematical formula}X∈ESST(AF)) if and only if it is a complete extension such that {a mathematical formula}X∪X+ is maximal (with respect to set inclusion) among all complete extensions;
      </list-item>
      <list-item label="•">
       X is the ideal extension (denoted as {a mathematical formula}X=ID(AF) or {a mathematical formula}X∈EID(AF)) if and only if X is the maximal admissible set included in all preferred extensions.
      </list-item>
     </list>
     <paragraph>
      As a final remark, which will be particularly relevant later, we recall that many semantics in the literature, and in particular the grounded, preferred, stable, semi-stable and ideal semantics recalled above are complete based, i.e. their extensions are a subset of the set of complete extensions. Formally it holds that {a mathematical formula}Eσ(AF)⊆ECO(AF) for {a mathematical formula}σ∈{GR,PR,ST,SST,ID}.
     </paragraph>
     <paragraph>
      For this reason it is worth to restate here in words the main features of a complete extension: it is a conflict free and admissible set, i.e. able to defend all its members, which includes all the arguments it defends.
     </paragraph>
    </section>
    <section label="3">
     A generic semi-structured argumentation formalism: LAF-ensembles
     <paragraph>
      In this section we introduce a generic argumentation formalism. We call it semi-structured as it refers, unlike abstract argumentation frameworks, to some structural properties of arguments (like having a conclusion or having some subarguments) but, differently from several structured argumentation formalisms, it does not specify the internal structure of arguments in terms of rules or other representation elements.
     </paragraph>
     <paragraph>
      The formalism distinguishes two layers: a language layer described in Section 3.1 and an argument layer introduced in Section 3.2 (see Fig. 1 for an overview of the notions and symbols introduced in the following). The two layers interact mainly through the notion of justification, defined in Section 4.
     </paragraph>
     <section label="3.1">
      <section-title>
       Language level inhibition and acceptance
      </section-title>
      <paragraph>
       As a starting point we assume a generic language {a mathematical formula}L equipped with an inhibition function {a mathematical formula}INH to form what we call an inhibition framework.
      </paragraph>
      <paragraph label="Definition 4">
       An inhibition framework is a pair {a mathematical formula}IF=〈L,INH〉 where {a mathematical formula}L is a set, called language, and {a mathematical formula}INH is a total function {a mathematical formula}INH:2L→22L satisfying the constraint that {a mathematical formula}∅∉INH(∅).
      </paragraph>
      <paragraph>
       The elements of {a mathematical formula}L correspond to entities in a given domain of discourse, while {a mathematical formula}INH specifies for each subset S of {a mathematical formula}L the set of its inhibitors, which are in turn subsets of {a mathematical formula}L. Note that we don't make any assumption on the inhibition function. In particular {a mathematical formula}INH may, but need not, be symmetric: S being an inhibitor of T does not imply, nor prevent, that T is an inhibitor of S. Further, a subset S may have no inhibitors, i.e. it may be the case that {a mathematical formula}INH(S)=∅.
      </paragraph>
      <paragraph>
       As a second step, we assume that the elements of the language are subject to an acceptance assessment: typically only some elements of the language can be accepted in a given context by an intelligent reasoner. To formalize this we introduce a simple binary notion of acceptance{sup:2} over a language {a mathematical formula}L (with no commitment on what acceptance actually means).
      </paragraph>
      <paragraph label="Definition 5">
       An acceptance function on {a mathematical formula}L is a total function {a mathematical formula}ACC:L→{⊤,⊥} which states for each {a mathematical formula}φ∈L whether it is regarded as accepted ({a mathematical formula}ACC(φ)=⊤) or not ({a mathematical formula}ACC(φ)=⊥). An acceptance function is extended to subsets of {a mathematical formula}L in a straigthforward way: for every {a mathematical formula}S⊆L{a mathematical formula}ACC(S)=⊤ iff for every {a mathematical formula}φ∈S{a mathematical formula}ACC(φ)=⊤, while {a mathematical formula}ACC(S)=⊥ otherwise.{sup:3} Note in particular that {a mathematical formula}ACC(∅)=⊤.
      </paragraph>
      <paragraph>
       It is reasonable to expect that the acceptance function over a language {a mathematical formula}L, being part of an inhibition framework, takes into account the relevant inhibition function, as evidenced in the bottom part of Fig. 1. The underlying intuition is that if T is an inhibitor for S (i.e. {a mathematical formula}T∈INH(S)) the acceptance of T inhibits the acceptance of S. We introduce a notion of consistency accordingly.
      </paragraph>
      <paragraph label="Definition 6">
       Given an inhibition framework {a mathematical formula}〈L,INH〉, an acceptance function {a mathematical formula}ACC is consistent with the inhibition function {a mathematical formula}INH iff {a mathematical formula}∄S,T∈2L:S∈INH(T),ACC(S)=⊤,ACC(T)=⊤.
      </paragraph>
      <paragraph>
       Some comments on the inhibition function are now in order. First, note that the case {a mathematical formula}INH(S)=∅ is totally different from {a mathematical formula}∅∈INH(S) (in particular from {a mathematical formula}INH(S)={∅}). In fact, {a mathematical formula}INH(S)=∅ means that S has no inhibitors, so nothing can prevent the acceptance of S. Differently, if {a mathematical formula}∅∈INH(S) the acceptance of S is always prevented since S is inhibited by ∅, which is always accepted, as entailed by Definition 5. In other words, in this case if {a mathematical formula}ACC(S)=⊤ then {a mathematical formula}ACC is inconsistent. This provides an explanation for the constraint {a mathematical formula}∅∉INH(∅) in Definition 4, which is necessary to ensure that some consistent acceptance function exists, since {a mathematical formula}∅∈INH(∅) would imply that every acceptance function is inconsistent.
      </paragraph>
      <paragraph label="Example 1">
       We will illustrate our formalism through a running example. In line with the abstraction level of the model, we don't provide any specific intuitive interpretation of the illustrating example, while a case referring to a concrete domain will be provided in the ASPIC-like instantiation of the model in Section 9. In the running example the language simply consists of seven elements, i.e. {a mathematical formula}L={a,b,c,d,e,z,h}, and the inhibition function is defined as follows: {a mathematical formula}INH({e})={{a},{b}}, {a mathematical formula}INH({c,d})={{a},{b}}, {a mathematical formula}INH({c,h})={{a},{b}}, while {a mathematical formula}INH(S)=∅ for all other sets {a mathematical formula}S⊆L. Then, for instance any acceptance function {a mathematical formula}ACC such that {a mathematical formula}ACC(a)=ACC(c)=ACC(d)=⊤ would not be consistent with {a mathematical formula}INH, while any acceptance function {a mathematical formula}ACC such that {a mathematical formula}ACC(c)=ACC(e)=⊥ would be consistent.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Arguments, subarguments and fallibility
      </section-title>
      <paragraph>
       We assume that an argument construction mechanism on top of {a mathematical formula}L is given, with the ultimate goal of building sensible acceptance functions. Intuitively an argument is a possibly defeasible derivation of a conclusion on some basis. As we leave the derivation mechanism unspecified, the only relevant properties of an argument for our purposes are its conclusion and the possible presence of attackable elements{sup:4} inside it. Since different arguments with the same conclusion and same attackable elements may exist, we need however an additional identification mechanism to distinguish them. To this purpose we assume the existence of a suitable universe IDS of argument identifiers (e.g. natural numbers). This leads to the following definition (see also the upper part of Fig. 1).
      </paragraph>
      <paragraph label="Definition 7">
       Given a language {a mathematical formula}L and a disjoint set IDS of argument identifiers ({a mathematical formula}IDS∩L=∅), a {a mathematical formula}L-argument α is a tuple {a mathematical formula}〈AI(α),Conc(α),AE(α)〉 where {a mathematical formula}AI(α)∈IDS is the argument identifier, {a mathematical formula}Conc(α)∈L is the argument conclusion and {a mathematical formula}AE(α)⊆L is the set of attackable elements of α. For a set of {a mathematical formula}L-arguments X we define, with a little abuse of notation, {a mathematical formula}Conc(X)≜{Conc(α)|α∈X} and {a mathematical formula}AE(X)≜⋃α∈XAE(α).
      </paragraph>
      <paragraph>
       For this and for other notions, in the following we will omit the reference to {a mathematical formula}L whenever not strictly required.
      </paragraph>
      <paragraph>
       While the actual argument construction mechanism is left unspecified, we have to somehow capture the fact that an argument can be built incrementally over other arguments, called subarguments. At an abstract level this is achieved by assuming the existence of a suitable subargument relation.
      </paragraph>
      <paragraph label="Definition 8">
       A {a mathematical formula}L-subargument structure is a pair {a mathematical formula}〈Σ,⊑〉 where Σ is a set of {a mathematical formula}L-arguments and ⊑ is a reflexive, antisymmetric, and transitive relation (i.e. a partial order) over Σ called subargument relation. The set of subarguments of an argument {a mathematical formula}α∈Σ is defined as {a mathematical formula}Sub(α)≜{β∈Σ|β⊑α}. The set of proper subarguments of α is defined as {a mathematical formula}PSub(α)≜Sub(α)∖{α}. The condition {a mathematical formula}β∈PSub(α) is denoted as {a mathematical formula}β⊏α. Whenever β is a (proper) subargument of α we say also that α is a (proper) superargument of β.
      </paragraph>
      <paragraph>
       Note that for every argument α, {a mathematical formula}Sub(α)≠∅ since {a mathematical formula}α∈Sub(α). To avoid unnecessary technical complications we assume that for every argument α the set {a mathematical formula}Sub(α) is finite. This implies that, for every argument α, {a mathematical formula}∃β∈Sub(α) such that {a mathematical formula}Sub(β)={β}, i.e. that there are always subarguments that have no proper subarguments.
      </paragraph>
      <paragraph label="Example 2">
       In our running example we will consider seven arguments. The set of identifiers is defined as {a mathematical formula}IDS={α,β,γ,δ,ϵ,ζ,η}, and for the sake of simplicity we assume that the set of attackable elements is empty for every argument (an example of use of attackable elements will be given in Section 9). The set of arguments is defined as {a mathematical formula}Σ={〈α,a,∅〉,〈β,b,∅〉,〈γ,c,∅〉,〈δ,d,∅〉,〈ϵ,e,∅〉,〈ζ,z,∅〉,〈η,h,∅〉}. In the following we will refer to each argument by its identifier, e.g. we will speak of argument α to refer to {a mathematical formula}〈α,a,∅〉. The subargument relation ⊑ is defined as in the Hasse diagram of Fig. 2, where in particular {a mathematical formula}PSub(α)={β}, {a mathematical formula}PSub(β)=PSub(ζ)=PSub(η)=∅, {a mathematical formula}PSub(γ)={ζ}, {a mathematical formula}PSub(δ)={η}, {a mathematical formula}PSub(ϵ)={γ,δ,ζ,η}.
      </paragraph>
      <paragraph>
       In the following it will be useful to refer to sets of arguments which are subargument closed, namely include all the subarguments of their members.
      </paragraph>
      <paragraph label="Definition 9">
       Given a subargument structure {a mathematical formula}〈Σ,⊑〉, a set of arguments {a mathematical formula}X⊆Σ is subargument closed iff {a mathematical formula}∀α∈XSub(α)⊆X.
      </paragraph>
      <paragraph label="Example 3">
       The set of arguments {a mathematical formula}{δ,η,ζ} is subargument closed while {a mathematical formula}{δ,γ,ζ} is not.
      </paragraph>
      <paragraph>
       In addition to the example, in the following we will use some figures to illustrate the concepts we introduce. Fig. 3 shows the basic graphical representation we adopt. An argument, like α or β is represented as a triangle, where the conclusion (e.g. a for argument α) is indicated over the upper vertex of the triangle, emphasized with a black dot, and the set of attackable elements is indicated at the right of the conclusion after a comma (e.g. {a mathematical formula}{r1,r2}). Some elements may be omitted when not needed (e.g. conclusion and attackable elements of argument β are not indicated). A proper subargument of an argument is indicated as a smaller internal triangle inside the superargument, e.g. β is a proper subargument of α. A set of subarguments which is possibly not subargument closed is indicated as a trapezium inside the argument, e.g. X is a set of subarguments of α which is possibly not subargument closed. A set of subarguments which is assumed to be subargument closed is indicated by a trapezium with a thick minor base, e.g. Y is a set of subarguments of α which is subargument closed. Finally the set of proper subarguments is indicated by a trapezium whose minor base connects the two sides of the triangle (and of course is thick) as shown for {a mathematical formula}PSub(α).
      </paragraph>
      <paragraph>
       An important aspect of argument construction we need to capture is that it may involve fallible (i.e. error- or exception-prone and hence subject to revision) or infallible (error- and exception-free, hence definitive) steps. As a consequence an argument can be classified as fallible or infallible. An infallible argument must not have attackable elements. Moreover, (in)fallibility of an argument is constrained by its subarguments: all the superarguments of a fallible argument must be fallible. In other words, an argument can be infallible only if all its subarguments are infallible too.
      </paragraph>
      <paragraph label="Definition 10">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉, an argument fallibility classification over SS is a total function {a mathematical formula}FI:Σ→{F,I} such that {a mathematical formula}FI(α)=I implies that {a mathematical formula}AE(α)=∅ and that {a mathematical formula}∄β∈Sub(α):FI(β)=F. Given a set of arguments X, the fallible (resp. infallible) arguments in X are defined as {a mathematical formula}Fall(X)≜{α∈X|FI(α)=F} (resp. {a mathematical formula}Infall(X)≜{α∈X|FI(α)=I}).
      </paragraph>
      <paragraph>
       Clearly, for every set of arguments X, {a mathematical formula}Fall(X) and {a mathematical formula}Infall(X) are disjoint and {a mathematical formula}X=Fall(X)∪Infall(X).
      </paragraph>
      <paragraph>
       At a more detailed level, we need to discriminate (in)fallibility not only of an entire argument but also of the ‘difference’ between an argument α and a set of its subarguments {a mathematical formula}X⊆Sub(α). Intuitively we need to indicate whether the elements involved in the construction of α in addition to X are (collectively) fallible or infallible, or, in other words, whether the construction of α has to be regarded as a fallible or infallible addition with respect to X.
      </paragraph>
      <paragraph>
       Fig. 4 illustrates the above idea for an argument α with respect to a set X of its subarguments, which is formally introduced by Definition 11.
      </paragraph>
      <paragraph label="Definition 11">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉, an incremental fallibility classification over SS is a set of total functions (called incremental fallibility classification functions) {a mathematical formula}FI⁎Δ≜{FIαΔ:2Sub(α)→{F,I}|α∈Σ} satisfying the following properties:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(Sub(α))=I;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(X)=FIαΔ(⋃β∈XSub(β));
       </list-item>
       <list-item label="3.">
        {a mathematical formula}∀α∈Σ, if {a mathematical formula}X⊊Sub(α) is subargument closed and {a mathematical formula}∃β∈(Sub(α)∖X) such that {a mathematical formula}FIβΔ(PSub(β))=F, then {a mathematical formula}FIαΔ(X)=F;
       </list-item>
       <list-item label="4.">
        if {a mathematical formula}FIαΔ(X)=I then {a mathematical formula}AE(α)⊆AE(X);
       </list-item>
       <list-item label="5.">
        if {a mathematical formula}FIαΔ(PSub(α))=I then for every argument β and for every set X such that {a mathematical formula}X⊆Sub(β) and {a mathematical formula}α∈X it holds that {a mathematical formula}FIβΔ(X)=FIβΔ((X∖{α})∪PSub(α)).
       </list-item>
      </list>
      <paragraph>
       Some comments on the properties stated in Definition 11 orderly follow:
      </paragraph>
      <list>
       <list-item label="1.">
        when considering the whole set of subarguments of α, {a mathematical formula}FIαΔ must indicate infallibility, since there are no elements involved in the construction of α in addition to {a mathematical formula}Sub(α) (which includes α itself) and a void addition cannot fail;
       </list-item>
       <list-item label="2.">
        for any argument β included in X, its subarguments cannot be regarded as additional to X in the construction of α. Hence, even if some subargument of β is not included in X the value of {a mathematical formula}FIαΔ(X) must be the same (this is graphically illustrated in Fig. 5, where it is meant that {a mathematical formula}X′=⋃β∈XSub(β)). This means that technically speaking one could restrict the domain of the function {a mathematical formula}FIαΔ to those subsets of {a mathematical formula}Sub(α) which are subargument closed;
       </list-item>
       <list-item label="3.">
        for a subargument closed set X of subarguments of an argument α, if, for some subargument β of α outside X, a fallible addition is needed to build β from its proper subarguments, then the addition from X to α (necessarily including the addition mentioned above) must be fallible too (this is graphically illustrated in Fig. 6);
       </list-item>
       <list-item label="4.">
        if an argument is derived infallibly from a set of subarguments, it cannot contain additional attackable elements with respect to those subarguments;
       </list-item>
       <list-item label="5.">
        if an argument is derived infallibly from its proper subarguments (e.g. α in Fig. 7), it does not carry any further information with respect to its proper subarguments as far as the evaluation of incremental fallibility of any of its superarguments (e.g. β in Fig. 7) is concerned (as illustrated in Fig. 7, where it is meant that {a mathematical formula}X′=X∖{α}).
       </list-item>
      </list>
      <paragraph label="Example 4">
       The full incremental fallibility classification assumed for our example is shown in Table 1, Table 2, referring respectively to α and ϵ and their subarguments. Both tables show only subargument closed sets of subarguments since the other sets of subarguments are derivable on the basis of point 2 of Definition 11. The reader can easily check that all other required properties are satisfied. For instance, as to point 1, {a mathematical formula}FIαΔ({α,β})=I. As to point 3, considering the subargument closed set {a mathematical formula}X={δ,η}⊊Sub(ϵ) and {a mathematical formula}γ∈(Sub(ϵ)∖X), given {a mathematical formula}FIγΔ({ζ})=F, it holds that {a mathematical formula}FIϵΔ(X)=F. Point 4 is trivial in the example given that we do not consider attackable elements. Finally, as to point 5, given {a mathematical formula}FIδΔ({η})=I, considering {a mathematical formula}X={γ,δ}⊆Sub(ϵ), it holds that {a mathematical formula}FIϵΔ(X)=FIϵΔ({γ,η}).
      </paragraph>
      <paragraph>
       Every incremental fallibility classification {a mathematical formula}FI⁎Δ induces an associated argument fallibility classification {a mathematical formula}FI which for every argument α coincides with {a mathematical formula}FIαΔ(∅), namely with the (in)fallibility of all the elements involved in the construction of α from ‘nothing’.
      </paragraph>
      <paragraph label="Definition 12">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉 and an incremental fallibility classification {a mathematical formula}FI⁎Δ over SS, the overall argument classification associated to {a mathematical formula}FI⁎Δ is defined for every argument α as {a mathematical formula}FI(α)=FIαΔ(∅).
      </paragraph>
      <paragraph label="Example 5">
       Considering again Table 1, Table 2 we get {a mathematical formula}FI(ζ)=I while all other arguments are fallible, i.e. {a mathematical formula}Infall(Σ)={ζ} while {a mathematical formula}Fall(Σ)={α,β,γ,δ,ϵ,η}.
      </paragraph>
      <paragraph>
       We prove with Lemma 1 and Proposition 1 that the overall argument classification introduced in Definition 12 complies with the properties of an argument fallibility classification stated in Definition 10. For this reason, whenever an incremental fallibility classification {a mathematical formula}FI⁎Δ is considered, the symbol {a mathematical formula}FI will denote the overall argument classification associated to {a mathematical formula}FI⁎Δ, which will be directly called the argument fallibility classification associated to {a mathematical formula}FI⁎Δ.
      </paragraph>
      <paragraph label="Lemma 1">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS, for every argument α such that{a mathematical formula}FI(α)=Fit holds that{a mathematical formula}∃β∈Sub(α):FIβΔ(PSub(β))=F.
      </paragraph>
      <paragraph label="Proposition 1">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS, the overall argument classification{a mathematical formula}FIsatisfies the properties required byDefinition 10.
      </paragraph>
      <paragraph>
       As evidenced by some items of Definition 11 and Lemma 1, in the sequel a special role will be played by the incremental fallibility evaluations concerning the ‘last construction step’ of an argument, namely the addition with respect to the set of its proper subarguments. We formally introduce therefore the notions of ultimately fallible and ultimately infallible arguments.
      </paragraph>
      <paragraph label="Definition 13">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉 and an incremental fallibility classification {a mathematical formula}FI⁎Δ over SS, an argument α is said to be ultimately fallible if {a mathematical formula}FIαΔ(PSub(α))=F and ultimately infallible if {a mathematical formula}FIαΔ(PSub(α))=I. Given a set of arguments X, the set of ultimately fallible and ultimately infallible arguments in X will be denoted as {a mathematical formula}UF(X) and {a mathematical formula}UI(X) respectively.
      </paragraph>
      <paragraph label="Example 6">
       Referring again to Table 2, for instance, given that {a mathematical formula}FIδΔ({η})=I it holds that {a mathematical formula}δ∈UI(Σ). Also, given that {a mathematical formula}FIϵΔ({γ,δ,ζ,η})=I it holds that {a mathematical formula}ϵ∈UI(Σ) and given that {a mathematical formula}FIγΔ({ζ})=F it holds that {a mathematical formula}γ∈UF(Σ).
      </paragraph>
      <paragraph>
       More generally, one may be interested in identifying the last fallible steps occurring along the construction of an argument. To this purpose we need to focus on suitable sets X of subarguments, called fallible blocks, which are subargument closed and minimal with respect to inclusion while ensuring that {a mathematical formula}FIαΔ(X)=I.
      </paragraph>
      <paragraph label="Definition 14">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉, an incremental fallibility classification {a mathematical formula}FI⁎Δ over SS and an argument {a mathematical formula}α∈Σ, a subargument closed set {a mathematical formula}X⊆Sub(α) is a fallible block for α iff {a mathematical formula}FIαΔ(X)=I and {a mathematical formula}∄Y⊊X such that Y is subargument closed{sup:5} and {a mathematical formula}FIαΔ(Y)=I.
      </paragraph>
      <paragraph>
       Actually, each argument α has a unique fallible block (which always exists), as shown by the following proposition.
      </paragraph>
      <paragraph label="Proposition 2">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an argument{a mathematical formula}α∈Σwith incremental fallibility classification function{a mathematical formula}FIαΔ, there is a unique fallible block for α.
      </paragraph>
      <paragraph>
       We introduce a special terminology for the unique subargument closed fallible block of an argument α and for its maximal, with respect to the subargument relation, elements as they intuitively correspond to the ‘last fallible steps’ in the construction of α.
      </paragraph>
      <paragraph label="Definition 15">
       Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉, an incremental fallibility classification {a mathematical formula}FI⁎Δ over SS and an argument {a mathematical formula}α∈Σ, the unique subargument closed fallible block of α will be called the fallible kernel of α and denoted as {a mathematical formula}FK(α). We define the fallible frontier of α as {a mathematical formula}FF(α)={β∈FK(α)|∄γ∈FK(α):β⊏γ}. As usual, for a set of arguments X we define {a mathematical formula}FF(X)=⋃α∈XFF(α).
      </paragraph>
      <paragraph>
       Definition 15 is illustrated in Fig. 8, where the three grey triangles are meant to indicate the arguments included in the set represented by the trapezium which have no proper superarguments inside the set itself.
      </paragraph>
      <paragraph label="Example 7">
       Given {a mathematical formula}FIαΔ({β})=I and {a mathematical formula}FIβΔ(∅)=F, {a mathematical formula}FK(α)={β} is the fallible kernel for α, with {a mathematical formula}FF(α)={β}. Note that in the case where instead {a mathematical formula}FIβΔ(∅)=I it would hold that {a mathematical formula}FK(α)=∅ with {a mathematical formula}FF(α)=∅. Considering then {a mathematical formula}FIϵΔ({γ,δ,ζ,η})=I, it can be checked that {a mathematical formula}FK(ϵ)={γ,ζ,η} with {a mathematical formula}FF(ϵ)={γ,η}.
      </paragraph>
      <paragraph>
       Some properties concerning Definition 15 are worth proving after a preliminary lemma.
      </paragraph>
      <paragraph label="Lemma 2">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS,  for every argument α such that{a mathematical formula}FI(α)=Iit holds that{a mathematical formula}∀X⊆Sub(α){a mathematical formula}FIαΔ(X)=I.
      </paragraph>
      <paragraph label="Proposition 3">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS
      </paragraph>
      <list>
       <list-item label="•">
        for an argument α,{a mathematical formula}FK(α)=FF(α)=∅iff α is an infallible argument;
       </list-item>
       <list-item label="•">
        {a mathematical formula}FK(α)=Sub(α)and{a mathematical formula}FF(α)={α}iff α is ultimately fallible;
       </list-item>
       <list-item label="•">
        every argument{a mathematical formula}β∈FF(α)is ultimately fallible.
       </list-item>
      </list>
      <paragraph>
       Given that in the following we will deal with the various elements we introduced altogether, let us define the notion of LAF-ensemble (LAF standing for Language, Arguments, Fallibility) collecting them (evidenced as a dashed box in Fig. 1).
      </paragraph>
      <paragraph label="Definition 16">
       A LAF-ensemble is a tuple {a mathematical formula}LE=〈IF,SS,FI⁎Δ〉 where {a mathematical formula}IF=〈L,INH〉 is an inhibition framework, {a mathematical formula}SS=〈Σ,⊑〉 is a {a mathematical formula}L-subargument structure, and {a mathematical formula}FI⁎Δ={FIαΔ|α∈Σ} is an incremental fallibility classification over SS.
      </paragraph>
      <paragraph>
       In the following, when referring to LAF-ensembles we will implicitly assume that the symbols denoting its components are the ones we uniformly used up to now, if not differently specified.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Argument justification and its requirements
     </section-title>
     <paragraph>
      In the view of producing language acceptance functions, we assume that a set of arguments can be subjected to a justification assessment, which we define as binary since this rather simplistic choice is adequate for our purposes.
     </paragraph>
     <paragraph label="Definition 17">
      Given a subargument structure {a mathematical formula}SS=〈Σ,⊑〉, a justification function on SS is a total function {a mathematical formula}JUS:Σ→{⊤,⊥}. If {a mathematical formula}JUS(α)=⊤ it is said that α is justified, while if {a mathematical formula}JUS(α)=⊥ it is said that α is not justified or rejected.
     </paragraph>
     <paragraph>
      An argument justification function {a mathematical formula}JUS directly induces an acceptance function on {a mathematical formula}L on the basis of argument conclusions. This is represented by a downward arrow in Fig. 9, which extends Fig. 1 with the concepts introduced in this section.
     </paragraph>
     <paragraph label="Definition 18">
      Given a {a mathematical formula}L-subargument structure {a mathematical formula}SS=〈Σ,⊑〉 and a justification function {a mathematical formula}JUS on SS, the conclusion acceptance function on {a mathematical formula}L induced by {a mathematical formula}JUS is denoted as {a mathematical formula}ACCJUS and is defined as follows: {a mathematical formula}∀φ∈L, {a mathematical formula}ACCJUS(φ)=⊤ iff {a mathematical formula}∃α∈Σ such that {a mathematical formula}JUS(α)=⊤ and {a mathematical formula}Conc(α)=φ.
     </paragraph>
     <paragraph>
      In words, a language element φ is accepted if and only if there is a justified argument whose conclusion is φ.
     </paragraph>
     <paragraph>
      Further, we can consider a notion of extended acceptance involving also the attackable elements of the arguments.
     </paragraph>
     <paragraph label="Definition 19">
      Given a {a mathematical formula}L-subargument structure {a mathematical formula}SS=〈Σ,⊑〉 and a justification function {a mathematical formula}JUS on SS, the extended acceptance function on {a mathematical formula}L induced by {a mathematical formula}JUS is denoted as {a mathematical formula}EACCJUS and is defined as follows: {a mathematical formula}∀φ∈L, {a mathematical formula}EACCJUS(φ)=⊤ iff {a mathematical formula}∃α∈Σ such that {a mathematical formula}JUS(α)=⊤ and {a mathematical formula}φ∈({Conc(α)}∪AE(α)).
     </paragraph>
     <paragraph>
      To constrain the set of sensible argument justification functions one may establish a set of general desirable requirements (see the dotted box in Fig. 9). In this paper, we consider two main families of requirements.
     </paragraph>
     <paragraph>
      The first family concerns consistency: in the context of a LAF-ensemble a commonly desirable property for an argument justification function is that it does not induce inconsistencies in the induced acceptance function at the language level.
     </paragraph>
     <paragraph label="Definition 20">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is conclusion consistent iff {a mathematical formula}ACCJUS is consistent with {a mathematical formula}INH.
     </paragraph>
     <paragraph>
      Considering the extended acceptance function yields a notion of extensive consistency.
     </paragraph>
     <paragraph label="Definition 21">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is extensively consistent iff {a mathematical formula}EACCJUS is consistent with {a mathematical formula}INH.
     </paragraph>
     <paragraph>
      It is immediate to note that extensive consistency implies conclusion consistency.
     </paragraph>
     <paragraph label="Example 8">
      Taking into account Example 1, any justification function such that {a mathematical formula}JUS(α)=JUS(γ)=JUS(δ)=⊤, implying {a mathematical formula}ACCJUS(a)=ACCJUS(c)=ACCJUS(d)=⊤, would not be conclusion consistent (and hence also not extensively consistent), while any justification function such that {a mathematical formula}JUS(γ)=JUS(ϵ)=⊥ would be conclusion consistent (and also trivially extensively consistent).
     </paragraph>
     <paragraph>
      Clearly, any form of consistency can easily but trivially be achieved by not justifying anything: to avoid this kind of extreme behavior a second family of requirements, oriented to acceptance, is introduced.
     </paragraph>
     <paragraph>
      A first requirement is based on the idea that the justification status of an argument is ⊤ unless there are some reasons to the contrary. Intuitively this is motivated by the fact that the existence of an argument α is a reason per se to justify it (backed by the argument construction process) and the decision of not justifying α instead, should be based on some explicit motivation. This motivation may come from the language level inhibition function applied to argument conclusions or argument attackable elements. In line with this, we require that argument rejection has an explicit motivation as expressed by the following definition.{sup:6}
     </paragraph>
     <paragraph label="Definition 22">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is fully inhibition driven if for every argument α, {a mathematical formula}JUS(α)=⊥ implies that {a mathematical formula}∃X,Y⊆Σ, {a mathematical formula}∃β∈Sub(α)∩Y such that {a mathematical formula}∃S⊆(Conc(X)∪AE(X)), {a mathematical formula}∃T⊆(Conc(Y)∪AE(Y)):S∈INH(T) and {a mathematical formula}T∩(Conc(β)∪AE(β))≠∅.
     </paragraph>
     <paragraph>
      The idea is that the rejection of an argument α must be due to some other arguments whose conclusions and/or attackable elements play an inhibiting role with respect to a set including the conclusion and/or some of the attackable elements of a subargument of α. This is illustrated in Fig. 10 which assumes that argument α is not justified and that the inhibition function at the language level involves the conclusion or an attackable element of the subargument β of α, while Example 9 describes a couple of the many ways of satisfying this property in the context of our running example.
     </paragraph>
     <paragraph label="Example 9">
      Consider a case where {a mathematical formula}JUS(ϵ)=⊥. Then since there exist arguments α and β such that {a mathematical formula}Conc(α)∈INH({Conc(ϵ)}) and also {a mathematical formula}Conc(β)∈INH({Conc(ϵ)}) the property of being fully inhibition driven is satisfied. In a case where {a mathematical formula}JUS(α)=⊥ the property could not be satisfied because {a mathematical formula}INH({Conc(α)})=INH({Conc(β)})=∅ and, more generally, there is no set T such that {a mathematical formula}INH(T)≠∅ and {a mathematical formula}Conc(α) or {a mathematical formula}Conc(β) belongs to T. Therefore there cannot be any set {a mathematical formula}S∈INH(T) satisfying the required condition.
     </paragraph>
     <paragraph>
      Further, the notion itself of infallibility poses some constraints on argument justification. First, the justification of infallible arguments should be regarded as mandatory.
     </paragraph>
     <paragraph label="Definition 23">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is infallibility compatible iff {a mathematical formula}∀α∈Infall(Σ){a mathematical formula}JUS(α)=⊤.
     </paragraph>
     <paragraph>
      Clearly, if {a mathematical formula}JUS is infallibility compatible its induced acceptance function reflects this property, namely {a mathematical formula}∀α∈Infall(Σ){a mathematical formula}ACCJUS(Conc(α))=⊤. With a little abuse of language we will therefore speak of infallibility compatible acceptance functions too.
     </paragraph>
     <paragraph>
      The requirement introduced above can be generalized taking into account the notion of incremental infallibility.
     </paragraph>
     <paragraph label="Definition 24">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is incremental infallibility compatible iff it holds that whenever {a mathematical formula}∃α∈Σ, {a mathematical formula}∃X⊆Sub(α) such that {a mathematical formula}∀β∈X{a mathematical formula}JUS(β)=⊤ and {a mathematical formula}FIαΔ(X)=I then {a mathematical formula}JUS(α)=⊤.
     </paragraph>
     <paragraph>
      In words, whenever for some argument α it holds that some of its subarguments (the set X) are justified according to {a mathematical formula}JUS and the ‘difference’ between α and X is regarded as an infallible addition, it is required that α too is justified according to {a mathematical formula}JUS: otherwise {a mathematical formula}JUS would miss an infallible addition to what it already justifies.
     </paragraph>
     <paragraph label="Example 10">
      In the running example the property of being infallibility compatible only requires that {a mathematical formula}JUS(ζ)=⊤. Concerning the property of being incremental infallibility compatible, for instance, if {a mathematical formula}JUS(γ)=JUS(δ)=⊤ then it should also hold that {a mathematical formula}JUS(ϵ)=⊤.
     </paragraph>
     <paragraph>
      It is easy to see that an incremental infallibility compatible justification function is also infallibility compatible.
     </paragraph>
     <paragraph label="Proposition 4">
      Given aLAF-ensemble {a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, if a justification function{a mathematical formula}JUSon SS is incremental infallibility compatible then it is also infallibility compatible.
     </paragraph>
     <paragraph>
      Finally, it seems natural to require that an argument can be justified only if all its subarguments are justified too.
     </paragraph>
     <paragraph label="Definition 25">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, a justification function {a mathematical formula}JUS on SS is subargument coherent iff for every argument {a mathematical formula}α∈Σ if {a mathematical formula}JUS(α)=⊤ then {a mathematical formula}∀β∈Sub(α) it holds that {a mathematical formula}JUS(β)=⊤.
     </paragraph>
     <paragraph label="Example 11">
      In the running example the property of being subargument coherent requires for instance that if {a mathematical formula}JUS(ϵ)=⊤ then {a mathematical formula}JUS(γ)=JUS(δ)=JUS(ζ)=JUS(η)=⊤.
     </paragraph>
     <paragraph>
      For the sake of conciseness an argument justification function which is extensively consistent, fully inhibition driven, incremental infallibility compatible and subargument coherent will be called proper.
     </paragraph>
    </section>
    <section label="5">
     Assumptions on LAF-ensembles
     <paragraph>
      In the view of investigating any mechanism for the production of argument justification functions able to ensure the satisfaction of the requirements introduced in the previous section, we first need to characterize some basic assumptions about LAF-ensembles, since any justification mechanism would fail if ‘unreasonable’ LAF-ensembles are considered.
     </paragraph>
     <paragraph>
      A first requirement concerns the connection between the inhibition function and the infallibility classification of arguments. In this respect, for a set of arguments Σ suppose that {a mathematical formula}∃S,T⊆Conc(Infall(Σ)) such that {a mathematical formula}S∈INH(T). Then the requirement that an argument justification function {a mathematical formula}JUS is infallibility compatible clashes with the requirement that the induced acceptance function {a mathematical formula}ACCJUS is consistent.{sup:7} The only way to avoid this clash is to assume that such a situation cannot occur, by restricting attention on infallibility consistentLAF-ensembles.
     </paragraph>
     <paragraph label="Definition 26">
      Given a LAF-ensemble{a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, we say that {a mathematical formula}X⊆Σ is infallibility consistent iff {a mathematical formula}∄S,T⊆Conc(Infall(X)) such that {a mathematical formula}S∈INH(T). LE is infallibility consistent iff Σ is infallibility consistent.
     </paragraph>
     <paragraph label="Example 12">
      In the running example only ζ is infallible, so infallibility consistency imposes the three conditions {a mathematical formula}{z}∉INH({z}), {a mathematical formula}∅∉INH({z}), and {a mathematical formula}{z}∉INH(∅), which actually hold.
     </paragraph>
     <paragraph>
      While the above requirement concerns the infallibility of arguments as a whole, one may consider relating the inhibition function with incremental infallibility too.
     </paragraph>
     <paragraph>
      To see this, consider the case where there is a fallible argument α with {a mathematical formula}Conc(α)=φ, another fallible argument β with {a mathematical formula}Conc(β)=ψ, and a third argument γ with {a mathematical formula}Conc(γ)=χ such that {a mathematical formula}β⊑γ and {a mathematical formula}FIγΔ({β})=I. Suppose also that {a mathematical formula}INH({χ})={{φ}}, and that {a mathematical formula}INH({φ})=INH({ψ})=∅. We get that an argument justification function {a mathematical formula}JUS cannot justify both arguments α and γ, i.e. it cannot be the case that {a mathematical formula}JUS(α)=JUS(γ)=⊤, since the induced acceptance function {a mathematical formula}ACCJUS would be inconsistent. Consider then a justification function {a mathematical formula}JUS where {a mathematical formula}JUS(α)=⊤ and {a mathematical formula}JUS(γ)=⊥. Unfortunately, in this case both the possible assignments of a justification status to β turn out to be unsatisfactory. If {a mathematical formula}JUS(β)=⊤ we get a violation of the requirement of incremental infallibility compatibility, given that {a mathematical formula}JUS(γ)=⊥. If {a mathematical formula}JUS(β)=⊥ we get the unpleasant fact that β is not justified, which appears to be unmotivated at the underlying level, since there are no inhibitors for {a mathematical formula}Conc(β), i.e. {a mathematical formula}JUS is not fully inhibition driven. Similarly, any other justification function {a mathematical formula}JUS with {a mathematical formula}JUS(α)=⊥ would be unsatisfactory since the rejection of α is also not backed by any inhibitor.
     </paragraph>
     <paragraph>
      This simple example shows that if one wants to comply with all the requirements we have previously stated for the justification and acceptance functions, the inhibition function at the language level and the incremental infallibility properties at the argument level should be somehow in accordance: in the example the inhibition function appears to be inadequate.
     </paragraph>
     <paragraph>
      To deal with this problem we follow the intuition that whenever an inconsistency is detectable in the conclusions of a set of arguments it must be possible to trace it back to an inhibition relation involving the fallible parts of (some of) the arguments involved. Note that exploring this direction is possible since we have already excluded that an inconsistency may arise from infallible arguments.
     </paragraph>
     <paragraph>
      Formally, we introduce a property corresponding to the idea that whenever an inhibition involving some infallible elements occurs, it is possible to identify another inhibition involving some underlying fallible elements. Basically this means that whenever there is an inhibition relation involving conclusions and attackable elements of some arguments, there is also an inhibition relation involving (some of) the conclusions and attackable elements of the relevant fallible frontiers. This leads to the definition of the property of inhibition infallibility ({a mathematical formula}II) consonance.
     </paragraph>
     <paragraph label="Definition 27">
      A LAF-ensemble is {a mathematical formula}II-consonant iff the following condition holds:if {a mathematical formula}∃T,U⊆L, {a mathematical formula}∃X,Y⊆Σ such that
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}T∈INH(U);
      </list-item>
      <list-item label="•">
       {a mathematical formula}T⊆Conc(X)∪AE(X);
      </list-item>
      <list-item label="•">
       {a mathematical formula}U⊆Conc(Y)∪AE(Y);
      </list-item>
     </list>
     <paragraph>
      Definition 27 is graphically illustrated in Fig. 11, where the dashed line, as in Fig. 10, separates the argument layer from the language layer, and it is then instantiated in Example 13.
     </paragraph>
     <paragraph label="Example 13">
      Consider for instance arguments α and ϵ. Since {a mathematical formula}Conc(α)=a and {a mathematical formula}Conc(ϵ)=e, {a mathematical formula}{Conc(α)}∈INH({Conc(ϵ)}) (see Example 1). Then recall from Example 7 that {a mathematical formula}FF({α})={β} and {a mathematical formula}FF({ϵ})={γ,η}. As far as this case is concerned, the property of {a mathematical formula}II-consonance is then satisfied since {a mathematical formula}{b}∈INH({c,h}). Applying the same check to other arguments it can be verified that the LAF-ensemble in our example is {a mathematical formula}II-consonant.
     </paragraph>
     <paragraph>
      Some comments on the relation of {a mathematical formula}II-consonance with infallible arguments are in order. First, note that {a mathematical formula}II-consonance directly implies infallibility consistency.
     </paragraph>
     <paragraph label="Proposition 5">
      An{a mathematical formula}II-consonantLAF-ensemble is infallibility consistent.
     </paragraph>
     <paragraph>
      Another remark concerns the fact that the fallible frontier of infallible arguments is the empty set. In particular, consider the case where an inconsistency arises from a pair including an ultimately fallible argument α and an infallible argument β, and suppose that {a mathematical formula}{Conc(β)}∈INH({Conc(α)}). Given that β is infallible, {a mathematical formula}II-consonance entails that {a mathematical formula}∅∈INH(Conc(α)). This corresponds to the idea that since β is infallible and hence {a mathematical formula}Conc(β) is mandatory, a mandatory inhibition towards {a mathematical formula}Conc(α) is enforced: as commented in Section 3.1, being inhibited by the empty set corresponds to this strong form of inhibition.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      A set based argumentation framework
     </section-title>
     <paragraph>
      We aim now at defining a suitable mechanism for the production of argument justification functions for LAF-ensembles based on the AF formalism recalled in Section 2. This amounts to introducing a third layer, leading to the complete picture shown in Fig. 12.
     </paragraph>
     <paragraph>
      Let us first recall the main elements of the AF formalism and relate them to our modeling goals:
     </paragraph>
     <list>
      <list-item label="•">
       an argumentation framework consists of two very simple elements: the nodes AA, whose unique feature is the ability to attack each other, and their attack relation ↠;
      </list-item>
      <list-item label="•">
       an argumentation semantics σ determines for an argumentation framework {a mathematical formula}F a set of extensions, where each extension {a mathematical formula}E⊆AA is a set of nodes that, according to the criteria embedded in the semantics definition, can ‘survive together’ the conflict represented by the attack relation. In general many extensions exist, each representing an alternative reasonable viewpoint based on the framework at hand.
      </list-item>
     </list>
     <paragraph>
      Now, let us orderly introduce and discuss the main modeling choices we adopt.
     </paragraph>
     <paragraph>
      Since the requirements on argument justification functions are based on the inhibition function and the attack relationship is the basis for the evaluation produced by an argumentation semantics, one is led to deduce that the attack relation ↠ should be somehow inhibition driven. Given that the inhibition function concerns sets of language elements (that may correspond to argument conclusions and/or attackable elements) it follows that ↠ should involve sets of arguments. Formally, this implies that {a mathematical formula}AA⊆2Σ, informally this means that from now on the correspondence between the nodes of an argumentation framework and individual arguments, usually adopted in the literature, should be forgotten (we continue here the presentation of our technical development, while we will discuss more extensively later in Section 10 this important point and the relationships with the relevant literature). This gives rise to a first very basic definition.
     </paragraph>
     <paragraph label="Definition 28">
      Given a LAF-ensemble LE, a set based argumentation framework for LE is a tuple {a mathematical formula}FLE=〈AA,↠〉 where {a mathematical formula}AA⊆2Σ and {a mathematical formula}↠⊆AA×AA.
     </paragraph>
     <paragraph>
      For the sake of readability, a set of arguments {a mathematical formula}X⊆Σ is denoted as {a mathematical formula}‖X‖ when referring to it as a node of a set based argumentation framework.
     </paragraph>
     <paragraph label="Example 14">
      To complete our running example, we consider, among the many possible ones, the following set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 where {a mathematical formula}AA={‖{α}‖,‖{β}‖,‖{γ}‖,‖{δ}‖,‖{ϵ}‖,‖{ζ}‖,‖{η}‖,‖{β,γ}‖,‖{β,η}‖} and {a mathematical formula}↠={(‖{β,γ}‖,‖{δ}‖),(‖{β,γ}‖,‖{η}‖),(‖{β,γ}‖,‖{ϵ}‖),(‖{β,η}‖,‖{γ}‖),(‖{β,η}‖,‖{ϵ}‖),(‖{β,γ}‖,‖{β,η}‖),(‖{β,η}‖,‖{β,γ}‖)} (see Fig. 13).
     </paragraph>
     <paragraph>
      It follows that an extension E of {a mathematical formula}FLE, being a set of elements of AA, corresponds to a set of sets of arguments of LE. The justification function induced by a subset of AA is defined in the obvious way.
     </paragraph>
     <paragraph label="Definition 29">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE and {a mathematical formula}E⊆AA, the justification function {a mathematical formula}JUSE on Σ induced by E is defined as follows: for every {a mathematical formula}α∈Σ, {a mathematical formula}JUSE(α)=⊤ iff {a mathematical formula}∃‖X‖∈E such that {a mathematical formula}α∈X.
     </paragraph>
     <paragraph>
      Clearly, {a mathematical formula}JUSE induces a conclusion acceptance function {a mathematical formula}ACCJUSE and an extended acceptance function {a mathematical formula}EACCJUSE on {a mathematical formula}L.
     </paragraph>
     <paragraph label="Example 15">
      Considering {a mathematical formula}E={‖{α}‖,‖{β}‖,‖{γ}‖,‖{ζ}‖,‖{β,γ}‖} we get that {a mathematical formula}JUSE is such that {a mathematical formula}JUSE(α)=JUSE(β)=JUSE(γ)=JUSE(ζ)=⊤ and {a mathematical formula}JUSE(δ)=JUSE(ϵ)=JUSE(η)=⊥. Then {a mathematical formula}ACCJUSE=EACCJUSE and in particular {a mathematical formula}ACCJUSE(a)=ACCJUSE(b)=ACCJUSE(c)=ACCJUSE(z)=⊤, while {a mathematical formula}ACCJUSE(d)=ACCJUSE(e)=ACCJUSE(h)=⊥.
     </paragraph>
     <paragraph>
      It follows that when applying an argumentation semantics to {a mathematical formula}FLE a set of justification functions (and consequently of acceptance functions) is induced.
     </paragraph>
     <paragraph label="Definition 30">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE, and an argumentation semantics σ the set of justification functions induced by σ is defined as: {a mathematical formula}J˜σ={JUSE|E∈Eσ(FLE)}. The set of conclusion acceptance functions induced by σ is defined as: {a mathematical formula}A˜σ={ACCJUS|JUS∈J˜σ}. The set of extended acceptance functions induced by σ is defined as: {a mathematical formula}EA˜σ={EACCJUS|JUS∈J˜σ}.
     </paragraph>
     <paragraph label="Example 16">
      Letting σ be the preferred or stable semantics, for the argumentation framework in Fig. 13, we have that {a mathematical formula}Eσ(FLE)={E,E′} where E is as in Example 15 and {a mathematical formula}E′={‖{α}‖,‖{β}‖,‖{δ}‖,‖{ζ}‖,‖{η}‖,‖{β,η}‖}. Then {a mathematical formula}J˜σ={JUSE,JUSE′} and {a mathematical formula}A˜σ=EA˜σ={ACCJUSE,ACCJUSE′} where {a mathematical formula}ACCJUSE is as in Example 15 and {a mathematical formula}ACCJUSE′ yields a, b, d, z, h as accepted conclusions.
     </paragraph>
     <paragraph>
      Now, in order to obtain suitable justification outcomes we need to constrain in some way AA and ↠ and to properly choose the semantics σ. The latter point is quite easy: we will consider complete semantics, since this will ensure that the results we obtain directly carry over to the many complete based argumentation semantics in the literature.
     </paragraph>
     <paragraph>
      Turning to AA, in principle every set of arguments {a mathematical formula}X⊆Σ might have a corresponding node {a mathematical formula}‖X‖ within AA, but we need to select those that actually need a representation.
     </paragraph>
     <paragraph>
      First we include of course every singleton: this is due to the fact that every individual argument is possibly justified and needs to be included independently of its involvement in any attack. This leads to the definition of singleton covering framework.
     </paragraph>
     <paragraph label="Definition 31">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is singleton covering iff {a mathematical formula}∀α∈Σ{a mathematical formula}‖{α}‖∈AA.
     </paragraph>
     <paragraph>
      Second, the attack relation must account for the subargument relation. This means that whenever the node corresponding to a set of arguments {a mathematical formula}‖X‖ attacks a node corresponding to a singleton {a mathematical formula}‖{α}‖, it must also attack all the nodes corresponding to the superarguments of α. This leads to the definition of subargument aware argumentation frameworks.
     </paragraph>
     <paragraph label="Definition 32">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is subargument aware iff there are no arguments α, β and set of arguments X such that {a mathematical formula}‖X‖∈AA, {a mathematical formula}‖X‖↠‖{α}‖, {a mathematical formula}α⊑β, {a mathematical formula}‖X‖↠̸‖{β}‖.
     </paragraph>
     <paragraph>
      Third, the attack relation must account for the inclusion relation: an attack against a set carries the meaning that (on the basis of the attacking set) it cannot be the case that all the arguments in the attacked set are justified and this implies that it cannot be the case that all the arguments are justified also for every superset of the attacked set.
     </paragraph>
     <paragraph>
      This leads to the definition of inclusion aware argumentation frameworks.
     </paragraph>
     <paragraph label="Definition 33">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is inclusion aware iff {a mathematical formula}∄‖X‖,‖Y‖,‖W‖∈AA such that {a mathematical formula}‖X‖↠‖Y‖, {a mathematical formula}Y⊆W, {a mathematical formula}‖X‖↠̸‖W‖.
     </paragraph>
     <paragraph label="Example 17">
      It is easy to see that in our example {a mathematical formula}FLE is singleton covering. It is also subargument aware: {a mathematical formula}‖{β,γ}‖ attacks {a mathematical formula}‖{η}‖ and also {a mathematical formula}‖{δ}‖ and {a mathematical formula}‖{ϵ}‖, where {a mathematical formula}η⊑δ⊑ϵ. Moreover {a mathematical formula}‖{β,η}‖ attacks {a mathematical formula}‖{γ}‖ and also {a mathematical formula}‖{ϵ}‖ with {a mathematical formula}γ⊑ϵ. It is also inclusion aware: {a mathematical formula}‖{β,γ}‖ attacks {a mathematical formula}‖{η}‖ and also {a mathematical formula}‖{β,η}‖, moreover {a mathematical formula}‖{β,η}‖ attacks {a mathematical formula}‖{γ}‖ and also {a mathematical formula}‖{β,γ}‖.
     </paragraph>
     <paragraph>
      The following two properties concern the fact that the attack relationship should, in a sense, capture all and only the information encoded by the inhibition relation. This intuition needs to be combined with the fact that, based on the considerations drawn in previous sections, conflicts should be traced back to fallible reasoning. Hence we regard as eligible to be directly involved in conflicts only the ultimately fallible arguments, i.e. if an argument is not ultimately fallible, the conflict should be rather referred to its fallible frontier (of course if an argument is not ultimately fallible it may still be attacked on one of its ultimately fallible subarguments, see Definition 32).
     </paragraph>
     <paragraph>
      Accordingly, the first property we introduce here represents a sort of completeness requirement on the attack relation. Referring to Fig. 14, observe that, given two sets of language elements S and T such that {a mathematical formula}S∈INH(T), to preserve the consistency of an acceptance function {a mathematical formula}ACC on {a mathematical formula}L it is sufficient that {a mathematical formula}∃φ∈S∪T such that {a mathematical formula}ACC(φ)=⊥. Carrying this consideration at the level of arguments and taking into account that our analysis has to focus on ultimately fallible arguments, this suggests that, whenever there are two sets of ultimately fallible arguments X, Y such that their conclusions and attackable elements are involved in an inhibition relationship, it must be the case that {a mathematical formula}∃α∈X∪Y which is attacked by some subset W of {a mathematical formula}X∪Y. Intuitively, this is sufficient to prevent that the arguments in {a mathematical formula}X∪Y are all accepted together since a part of {a mathematical formula}X∪Y is against the acceptance of α (which belongs to {a mathematical formula}X∪Y too).
     </paragraph>
     <paragraph>
      Making these intuitions formal leads to the definition of fallible language inhibition covering frameworks.
     </paragraph>
     <paragraph label="Definition 34">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is fallible language inhibition covering iff the following condition holds: whenever {a mathematical formula}∃S,T⊆L:S∈INH(T), {a mathematical formula}∃X⊆UF(Σ):S⊆Conc(X)∪AE(X), {a mathematical formula}∃Y⊆UF(Σ):T⊆Conc(Y)∪AE(Y) then {a mathematical formula}∃α∈X∪Y,∃W⊆X∪Y:‖W‖↠‖{α}‖.
     </paragraph>
     <paragraph label="Example 18">
      {a mathematical formula}FLE is also fallible language inhibition covering. Consider the sets of ultimately fallible arguments {a mathematical formula}X={β} and {a mathematical formula}Y={γ,η} such that {a mathematical formula}Conc(X)∈INH(Conc(Y)) since {a mathematical formula}{b}∈INH({c,h}). Then letting {a mathematical formula}W={β,γ} it holds that {a mathematical formula}‖W‖↠‖{η}‖, which is sufficient to satisfy the property (the same holds for {a mathematical formula}W={β,η} attacking {a mathematical formula}‖{γ}‖).
     </paragraph>
     <paragraph>
      Having provided in Definition 32, Definition 34 some properties specifying which attacks are required to be present in a set based argumentation framework, we need also to exclude that spurious attacks are present, i.e., as a sort of soundness condition, we need to require that every attack corresponds to one of the properties above. This is achieved by the following definition.
     </paragraph>
     <paragraph label="Definition 35">
      Given a LAF-ensemble LE, a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is attack accurate iff {a mathematical formula}∀W,Z such that {a mathematical formula}‖W‖↠‖Z‖ one of the following conditions holds:
     </paragraph>
     <list>
      <list-item label="1.">
       Z is a singleton {a mathematical formula}{α} and {a mathematical formula}∃X,Y:W⊆X∪Y⊆UF(Σ) such that {a mathematical formula}α∈Y and {a mathematical formula}∃S,T⊆L such that (i) {a mathematical formula}S∈INH(T); (ii) {a mathematical formula}S⊆Conc(X)∪AE(X); (iii) {a mathematical formula}T⊆Conc(Y)∪AE(Y) and {a mathematical formula}∀Y′⊊Y{a mathematical formula}T⊈Conc(Y′)∪AE(Y′);
      </list-item>
      <list-item label="2.">
       Z is a singleton {a mathematical formula}{α} and {a mathematical formula}∃β∈PSub(α):‖W‖↠‖{β}‖;
      </list-item>
      <list-item label="3.">
       Z is not a singleton and {a mathematical formula}∃α∈Z:‖W‖↠‖{α}‖.
      </list-item>
     </list>
     <paragraph>
      Item 1 is illustrated by Fig. 15 (where W corresponds to the union of the two grey areas). Note that in point (iii) we impose a minimality condition on Y, since otherwise the whole item 1 could be directly satisfied, whenever the inhibition function is not empty, by referring to a sufficiently large Y, thus losing any capability to avoid spurious attacks.
     </paragraph>
     <paragraph label="Example 19">
      {a mathematical formula}FLE is attack accurate. For instance, letting {a mathematical formula}W={β,η} it holds that {a mathematical formula}‖W‖↠‖{γ}‖ and condition 1 of Definition 35 is satisfied letting {a mathematical formula}X={β} and {a mathematical formula}Y={γ,η} (and similarly for the attack {a mathematical formula}‖{β,γ}‖↠‖{η}‖). The attacks {a mathematical formula}‖{β,γ}‖↠‖{δ}‖, {a mathematical formula}‖{β,γ}‖↠‖{ϵ}‖, and {a mathematical formula}‖{β,η}‖↠‖{ϵ}‖, satisfy condition 2 of Definition 35. Finally the attacks {a mathematical formula}‖{β,γ}‖↠‖{β,η}‖ and {a mathematical formula}‖{β,η}‖↠‖{β,γ}‖ satisfy condition 3 of Definition 35.
     </paragraph>
     <paragraph>
      Given a LAF-ensemble LE, any set based argumentation framework {a mathematical formula}FLE is called appropriate for LE if it is singleton covering, subargument aware, inclusion aware, fallible language inhibition covering, and attack accurate.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Appropriate argumentation frameworks generate proper justification functions
     </section-title>
     <paragraph>
      The main result we provide in this section is that, given an {a mathematical formula}II-consonant LAF-ensemble LE, any set based argumentation framework {a mathematical formula}FLE which is appropriate for LE is a possibly reasonable choice, under any complete based semantics σ, for assessing the justification of the arguments in Σ. More precisely let {a mathematical formula}C be any complete extension of such {a mathematical formula}FLE with induced justification function {a mathematical formula}JUSC on Σ: we aim at showing that {a mathematical formula}JUSC is proper, namely fully inhibition driven, incremental infallibility compatible (implying that it is infallibility compatible), extensively consistent (implying that it is conclusion consistent) and subargument coherent. This is evidenced in Fig. 12 where the relevant hypotheses and the implied requirements are evidenced in grey.
     </paragraph>
     <paragraph>
      Two preliminary lemmata are required, showing that complete extensions of appropriate set based argumentation frameworks satisfy some desirable and technically useful properties. First, if a node corresponding to a set of arguments belongs to an extension then all the nodes corresponding to the relevant singletons belong to the extension. Second, if two nodes corresponding to two sets belong to an extension, then the node corresponding to their union (if present in the framework) also belongs to the extension.
     </paragraph>
     <paragraph label="Lemma 3">
      Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, a complete extension{a mathematical formula}Cof{a mathematical formula}FLE, and a set of arguments X, if{a mathematical formula}‖X‖∈Cthen{a mathematical formula}∀α∈X{a mathematical formula}‖{α}‖∈C.
     </paragraph>
     <paragraph label="Lemma 4">
      Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, a complete extension{a mathematical formula}Cof{a mathematical formula}FLE, two sets of arguments X, Y, if{a mathematical formula}‖X‖∈C,{a mathematical formula}‖Y‖∈Cand{a mathematical formula}‖X∪Y‖∈AAthen{a mathematical formula}‖X∪Y‖∈C.
     </paragraph>
     <paragraph>
      On the basis of the above Lemmata the desired properties are proved in Proposition 6, Proposition 9.
     </paragraph>
     <paragraph label="Proposition 6">
      Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis subargument coherent, i.e. for every argument α if{a mathematical formula}JUSC(α)=⊤then{a mathematical formula}∀β∈Sub(α)it holds that{a mathematical formula}JUSC(β)=⊤.
     </paragraph>
     <paragraph label="Proposition 7">
      Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis fully inhibition driven.
     </paragraph>
     <paragraph label="Proposition 8">
      Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis incremental infallibility compatible.
     </paragraph>
     <paragraph label="Proposition 9">
      Given an{a mathematical formula}II-consonant LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis extensively consistent.
     </paragraph>
     <paragraph label="Example 20">
      To conclude our running example, the complete extensions of {a mathematical formula}FLE are {a mathematical formula}E={‖{α}‖,‖{β}‖,‖{γ}‖,‖{ζ}‖,‖{β,γ}‖} and {a mathematical formula}E′={‖{α}‖,‖{β}‖, {a mathematical formula}‖{δ}‖,‖{ζ}‖, {a mathematical formula}‖{η}‖,‖{β,η}‖}, as in Example 15, Example 16, and also {a mathematical formula}E″={‖{α}‖, {a mathematical formula}‖{β}‖,‖{ζ}‖}, which is actually the grounded extension. Since {a mathematical formula}FLE has been shown to be appropriate according to Proposition 9 we expect {a mathematical formula}JUSE, {a mathematical formula}JUSE′, and {a mathematical formula}JUSE″ to be extensively consistent. Skipping details, the sets of accepted conclusions are respectively {a mathematical formula}{a,b,c,z}, {a mathematical formula}{a,b,d,z,h} and {a mathematical formula}{a,b,z}, which all are consistent.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Capturing Vreeswijk's abstract argument systems
     </section-title>
     <paragraph>
      In this section we show that the proposed framework captures Vreeswijk's Abstract Argument Systems (AASs) [9], [12] and provides a counterpart in terms of argumentation frameworks and their semantics to the relevant argument evaluation mechanism.
     </paragraph>
     <paragraph>
      We proceed by recalling the definition of the key concepts of the AAS formalism and then showing the correspondence with our formalization.
     </paragraph>
     <paragraph label="Definition 36">
      An abstract argumentation system is a triple {a mathematical formula}〈L,R,≤〉 where {a mathematical formula}L is a language (namely a set containing a distinguished element ⊥), {a mathematical formula}R is a set of rules of inference and ≤ is a reflexive and transitive relation (i.e. a preorder) on arguments.
     </paragraph>
     <paragraph>
      Rules of inference are based on the language {a mathematical formula}L and are partitioned into strict and defeasible.
     </paragraph>
     <paragraph label="Definition 37">
      Let {a mathematical formula}L be a language, {a mathematical formula}φ1,…,φn be a finite (possibly empty) sequence of elements of {a mathematical formula}L, and φ be an element of {a mathematical formula}L. A strict rule of inference has the form {a mathematical formula}φ1,…,φn→φ. A defeasible rule of inference has the form {a mathematical formula}φ1,…,φn⇒φ.
     </paragraph>
     <paragraph>
      Arguments are defined as chains of rules organized as trees. Each argument α has a set of premises denoted as {a mathematical formula}Prem(α), a conclusion {a mathematical formula}Conc(α), a set of sentences {a mathematical formula}Snt(α), a set of subarguments {a mathematical formula}Sub(α), a length {a mathematical formula}Len(α), and a size {a mathematical formula}Sz(α).
     </paragraph>
     <paragraph label="Definition 38">
      An argument α is
     </paragraph>
     <list>
      <list-item label="1.">
       a member φ of {a mathematical formula}L (atomic argument) with {a mathematical formula}Prem(α)={φ}, {a mathematical formula}Conc(α)=φ, {a mathematical formula}Snt(α)={φ}, {a mathematical formula}Sub(α)={φ}, {a mathematical formula}Len(α)=1, {a mathematical formula}Sz(α)=1; or
      </list-item>
      <list-item label="2.">
       a formula of the form {a mathematical formula}α1,…,αn→φ, where {a mathematical formula}α1,…,αn is a finite, possibly empty, sequence of arguments such that {a mathematical formula}Conc(α1)=φ1,…,Conc(αn)=φn for some rule {a mathematical formula}φ1,…,φn→φ in {a mathematical formula}R and {a mathematical formula}φ∉Snt(α1)∪…∪Snt(αn) with {a mathematical formula}Prem(α)=⋃i=1nPrem(αi), {a mathematical formula}Conc(α)=φ, {a mathematical formula}Snt(α)=⋃i=1nSnt(αi)∪{φ}, {a mathematical formula}Sub(α)=⋃i=1nSub(αi)∪{α}, {a mathematical formula}Len(α)=1+maxi=1,…,n⁡Len(αi), {a mathematical formula}Sz(α)=1+∑i=1nSz(αi); or
      </list-item>
      <list-item label="3.">
       a formula of the form {a mathematical formula}α1,…,αn⇒φ where {a mathematical formula}α1,…,αn is a finite, possibly empty, sequence of arguments such that {a mathematical formula}Conc(α1)=φ1,…,Conc(αn)=φn for some rule {a mathematical formula}φ1,…,φn⇒φ in {a mathematical formula}R and {a mathematical formula}φ∉Snt(α1)∪…∪Snt(αn) with all other definitions as in 2.
      </list-item>
     </list>
     <paragraph>
      In the cases 2 and 3 the arguments {a mathematical formula}α1,…,αn are called immediate subarguments of α and {a mathematical formula}φ1,…,φn→(⇒)φ is called the top rule of α. The notation {a mathematical formula}α1,…,αn→(⇒)α is used to indicate that the argument α is built from immediate subarguments {a mathematical formula}α1,…,αn applying a strict (defeasible) rule. All the notions defined for arguments can be extended to sets of arguments in the obvious way. For instance if X is a set of arguments {a mathematical formula}Conc(X)≜⋃α∈XConc(α).
     </paragraph>
     <paragraph>
      The notion of superargument is defined in an intuitive way.
     </paragraph>
     <paragraph label="Definition 39">
      The set of superarguments of an argument α is defined as {a mathematical formula}Sup(α)={β|α∈Sub(β)}.
     </paragraph>
     <paragraph>
      The distinction between strict and defeasible arguments follows the one between strict and defeasible rules.
     </paragraph>
     <paragraph label="Definition 40">
      An argument α is strict if {a mathematical formula}α∈L or α has the form {a mathematical formula}α1,…,αn→φ where {a mathematical formula}α1,…,αn are strict arguments. If an argument is not strict it is defeasible.
     </paragraph>
     <paragraph>
      Note that in the original definition of [9], reported here, atomic arguments are strict, based on the implicit assumption that atomic arguments are not weaker than defeasible arguments (this assumption is formalized by the fourth point of Definition 42). This assumption has been relaxed in [12] where a more general approach, removing the implicit assumption, has been introduced. For the sake of conciseness, we limit our presentation here to the original definition of [9], without covering the generalized variant of [12].
     </paragraph>
     <paragraph label="Definition 41">
      The relationships between sets of language elements and the arguments built on them are characterized by the following definition. Let {a mathematical formula}L be a language and {a mathematical formula}S⊆L. An argument α is based on S if {a mathematical formula}Prem(α)⊆S; a set of arguments X is based on S if all the members of X are based on S. The set of all arguments that are based on S is denoted by {a mathematical formula}args(S).
     </paragraph>
     <paragraph>
      The third component of an AAS is a relation ≤ on arguments, called order of conclusive force and determining “the relative difference in strength among arguments” [9]: {a mathematical formula}α≤β indicates that β is at least as strong as α, and {a mathematical formula}α&lt;β indicates that β is stronger than α (formally {a mathematical formula}α≤β and {a mathematical formula}β≰α). Besides being reflexive and transitive, ≤ is required to satisfy four properties, recalled in Definition 42.
     </paragraph>
     <paragraph label="Definition 42">
      An order of conclusive force ≤ on a set of arguments is:
     </paragraph>
     <list>
      <list-item label="1.">
       Upwards well-founded: there are no infinite chains of arguments such that {a mathematical formula}α1&lt;α2&lt;…&lt;αj&lt;… ;
      </list-item>
      <list-item label="2.">
       Monotonically non-increasing: if {a mathematical formula}α∈Sub(β) then {a mathematical formula}β≤α;
      </list-item>
      <list-item label="3.">
       Propagating through strict rules: if α has the form {a mathematical formula}α1,…,αn→φ then {a mathematical formula}αi≤α for some {a mathematical formula}1≤i≤n;
      </list-item>
      <list-item label="4.">
       Favoring atomic arguments: for any arguments {a mathematical formula}α,β such that α is atomic and β is defeasible it is not the case that {a mathematical formula}α&lt;β.
      </list-item>
     </list>
     <paragraph>
      Based on the order of conclusive force, least and minimal elements can be defined.
     </paragraph>
     <paragraph label="Definition 43">
      Given a set of arguments X, an argument {a mathematical formula}α∈X is a ≤-least element of X if {a mathematical formula}∀β∈X{a mathematical formula}α≤β. α is a ≤-minimal element of X if {a mathematical formula}∀β∈X{a mathematical formula}β=α whenever {a mathematical formula}β≤α. Similarly, the set X may have ≤-greatest or ≤-maximal elements.
     </paragraph>
     <paragraph>
      Moreover an argument which is stronger than at least an element of a set is called an underminer for the set.
     </paragraph>
     <paragraph label="Definition 44">
      Given a set of arguments X, an argument α is an underminer of X (or X is undermined by α) if {a mathematical formula}∃β∈X such that {a mathematical formula}β&lt;α.
     </paragraph>
     <paragraph>
      In AASs conflicts are based on the meaning of the special symbol ⊥ as a conclusion of an argument.
     </paragraph>
     <paragraph label="Definition 45">
      An argument α is in contradiction if {a mathematical formula}Conc(α)=⊥.
     </paragraph>
     <paragraph>
      This induces a notion of compatibility within the language {a mathematical formula}L and then on sets of arguments.
     </paragraph>
     <paragraph label="Definition 46">
      Given a language {a mathematical formula}L, a set {a mathematical formula}S⊆L is incompatible if there exists a strict argument in contradiction, that is based on S. S is compatible if it is not incompatible. S is minimally incompatible if it is incompatible and {a mathematical formula}∀T⊊ST is compatible. A set of arguments X is incompatible if {a mathematical formula}Conc(X) is incompatible.
     </paragraph>
     <paragraph>
      The following proposition (Prop. 3.5 of [9]) plays a key role in the following.
     </paragraph>
     <paragraph label="Proposition 10">
      Let ≤ be an order of conclusive force on arguments. Then every minimally incompatible set of arguments has a ≤-least element.
     </paragraph>
     <paragraph>
      In the formal context introduced above, the argumentation process starts with a base set S, including the premises of all arguments: in the following whenever a base set S is given it is assumed that all arguments are based on S.
     </paragraph>
     <paragraph label="Definition 47">
      A base set is a finite compatible subset of {a mathematical formula}L.
     </paragraph>
     <paragraph>
      If some incompatibility occurs, a set of arguments may defeat another argument.
     </paragraph>
     <paragraph label="Definition 48">
      Let S be a base set and α be an argument. A set of arguments X is a defeater of α if {a mathematical formula}X∪α is incompatible and X is not undermined by it; in this case α is defeated by X, and X defeats α. X is a minimal defeater of α if all its proper subsets do not defeat α.
     </paragraph>
     <paragraph>
      The following lemmata will be useful for later proofs.
     </paragraph>
     <paragraph label="Lemma 5">
      If X is a minimal defeater of α then either{a mathematical formula}Conc(X∪{α})or{a mathematical formula}Conc(X)is minimally incompatible.
     </paragraph>
     <paragraph label="Lemma 6">
      The empty set is a minimal defeater of an argument α iff{a mathematical formula}Conc(α)is incompatible. Moreover if{a mathematical formula}Conc(α)is incompatible then{a mathematical formula}{α}is a minimal defeater of every argument β such that{a mathematical formula}β≤αand{a mathematical formula}Conc(β)is not incompatible.
     </paragraph>
     <paragraph>
      Given a base set, a recursive notion of enablement by a generic set of arguments X is introduced. Intuitively, an argument is enabled by X if it follows strictly from the base set and other arguments enabled, or if it follows defeasibly from the base set and other arguments enabled and it is not defeated by (some subset of) X.
     </paragraph>
     <paragraph label="Definition 49">
      Let S be a base set and X a set of arguments. An argument α is enabled by X on the basis of S, denoted as {a mathematical formula}S|X∼α, if
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}α∈S; or
      </list-item>
      <list-item label="2.">
       for some arguments {a mathematical formula}α1,…,αn it holds {a mathematical formula}S|X∼αi for {a mathematical formula}i=1,…,n and {a mathematical formula}α1,…,αn→α; or
      </list-item>
      <list-item label="3.">
       for some arguments {a mathematical formula}α1,…,αn it holds {a mathematical formula}S|X∼αi for {a mathematical formula}i=1,…,n and {a mathematical formula}α1,…,αn⇒α and X does not contain defeaters of α.
      </list-item>
     </list>
     <paragraph>
      An enablement operator is then defined which is proved in [9] to feature a monotony property.
     </paragraph>
     <paragraph label="Definition 50">
      Let S be a base set and X a set of arguments. The enablement operator {a mathematical formula}enableS(X) denotes the set of arguments {a mathematical formula}{α|S|X∼α}.
     </paragraph>
     <paragraph label="Proposition 11">
      Let S be a base set and{a mathematical formula}X,Ysets of arguments. If{a mathematical formula}X⊆Ythen{a mathematical formula}enableS(Y)⊆enableS(X).
     </paragraph>
     <paragraph>
      The notion of warrant for arguments is defined inductively with reference to a sequence of levels.
     </paragraph>
     <paragraph label="Definition 51">
      Let S be a base set. An argument α is in force at level 1 on the basis of S if it is based on S. Let {a mathematical formula}n&gt;1. An argument α is in force at level n on the basis of S, denoted as {a mathematical formula}S|∼nα if
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}α∈S; or
      </list-item>
      <list-item label="•">
       for some arguments {a mathematical formula}α1,…,αm we have {a mathematical formula}S|∼nαi for {a mathematical formula}i=1,…,m and {a mathematical formula}α1,…,αm→α or
      </list-item>
      <list-item label="•">
       for some arguments {a mathematical formula}α1,…,αm we have {a mathematical formula}S|∼nαi for {a mathematical formula}i=1,…,m and {a mathematical formula}α1,…,αm⇒α and every set of arguments X that is in force at level {a mathematical formula}n−1 on the basis of S is not a defeater of α.
      </list-item>
     </list>
     <paragraph>
      The set of arguments in force at level n on the basis of S is denoted as {a mathematical formula}infon(S).
     </paragraph>
     <paragraph>
      It can be shown that {a mathematical formula}infon(S) corresponds to iterative applications of the enablement operator starting from S itself.
     </paragraph>
     <paragraph label="Proposition 12">
      Let S be a base set. For every n,{a mathematical formula}infon(S)=enableSn(∅).
     </paragraph>
     <paragraph>
      Arguments in force with increasing n form an alternating sequence, as described by the following proposition.
     </paragraph>
     <paragraph label="Proposition 13">
      Let S be a base set. The sequence{a mathematical formula}{infon(S)}n=1∞is an alternating sequence of sets of arguments, such that{a mathematical formula}{info2n(S)}n=1∞is monotonically increasing, and{a mathematical formula}{info2n−1(S)}n=1∞is monotonically decreasing with:{a mathematical formula}
     </paragraph>
     <paragraph>
      The definition of defeasible entailment is similar to the one of argument in force at a level, but adds recursion on defeaters in the third clause.
     </paragraph>
     <paragraph label="Definition 52">
      Let S be a base set. A relation |∼ between S and arguments based on S is a defeasible entailment relation if, for every argument α based on S, we have {a mathematical formula}S|∼α (also called α is in force on the basis of S) if and only if
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}α∈S; or
      </list-item>
      <list-item label="2.">
       for some arguments {a mathematical formula}α1,…,αn we have {a mathematical formula}S|∼α1,…,αn and {a mathematical formula}α1,…,αn→α; or
      </list-item>
      <list-item label="3.">
       for some arguments {a mathematical formula}α1,…,αn we have {a mathematical formula}S|∼α1,…,αn and {a mathematical formula}α1,…,αn⇒α and every set of arguments X that is in force on the basis of S is not a defeater of α.
      </list-item>
     </list>
     <paragraph>
      Several defeasible entailment relations may exist for a base set S: this gives rise to the notion of extension.
     </paragraph>
     <paragraph label="Definition 53">
      Let S be a base set. A set of arguments X is an extension of S if there exists a defeasible entailment relation |∼ such that {a mathematical formula}X={α|S|∼α}.
     </paragraph>
     <paragraph>
      Intuitively an extension is made up of those arguments that emerge undefeated from all the arguments that can be constructed on the basis of S. Since there can be incompatible arguments having the same force or not comparable, there are in general multiple extensions of a given base set. In other words, there are different scenarios defeasibly entailed by a set of premises, the choice among them being arbitrary.
     </paragraph>
     <paragraph>
      It can be proved that extensions coincide with the fixed points of the enablement operator.
     </paragraph>
     <paragraph label="Proposition 14">
      Let S be a base set. A set of arguments X is an extension of S if and only if{a mathematical formula}enableS(X)=X.
     </paragraph>
     <paragraph>
      We can now recast the fundamental notions of AASs in terms of our general model.
     </paragraph>
     <paragraph>
      Let us start with some straightforward correspondences.
     </paragraph>
     <paragraph>
      Concerning the notion of argument (Definition 7) we can assume that every argument α satisfying Definition 38 is assigned a distinct identifier {a mathematical formula}AI(α) and has a conclusion {a mathematical formula}Conc(α) as prescribed by Definition 38. In AAS there is no notion of attackable element, hence for every argument α{a mathematical formula}AE(α)=∅. The subargument relation ⊑ (Definition 8) is also specified by Definition 38. Note in particular that for every argument α the set of its subarguments {a mathematical formula}Sub(α) is finite.
     </paragraph>
     <paragraph label="Proposition 15">
      Given an AAS, for every argument α the set{a mathematical formula}Sub(α)is finite.
     </paragraph>
     <paragraph>
      As to the fallibility classification (Definition 10), in AAS infallible (resp. fallible) arguments coincide with strict (resp. non-strict) arguments (Definition 40). It is easy to see that the properties required by Definition 10 for infallible arguments are satisfied, in particular {a mathematical formula}AE(α)=∅ for every argument (not just infallible ones) and if an argument has a fallible (i.e. not strict) subargument it is easy to see that it cannot be strict, i.e. it cannot be infallible.
     </paragraph>
     <paragraph>
      Concerning the incremental fallibility classification (Definition 11) the construction of an argument α from a set X of subarguments is infallible if it uses only strict rules on top of all the subarguments of α which are not included in X nor are subarguments of an argument included in X.
     </paragraph>
     <paragraph label="Definition 54">
      Given an AAS, for every argument α and {a mathematical formula}X⊆Sub(α) we define {a mathematical formula}FIαΔ(X)=I iff {a mathematical formula}∀β∈Sub(α)∖X such that {a mathematical formula}∄γ∈X with {a mathematical formula}β⊑γ, it holds that β is atomic or the top rule of β is strict; {a mathematical formula}FIαΔ(X)=F otherwise.
     </paragraph>
     <paragraph>
      It is easy to see that (according to Definition 12) this notion induces the fallibility classification mentioned above, i.e. for each argument α it holds {a mathematical formula}FI(α)=FIαΔ(∅).
     </paragraph>
     <paragraph>
      We have also to show that this notion satisfies the properties stated in Definition 11.
     </paragraph>
     <paragraph label="Proposition 16">
      Given an AAS, for every argument α the function{a mathematical formula}FIαΔintroduced inDefinition 54satisfies the requirements ofDefinition 11.
     </paragraph>
     <paragraph>
      Referring to Definition 13, in AAS an argument is ultimately fallible if its top rule is defeasible, ultimately infallible if it is atomic or its top rule is strict.
     </paragraph>
     <paragraph>
      Having examined the notions concerning the internal structure of arguments and their properties, let us move to their conflicts and hence to the inhibition relation. In AAS argument construction refers to base sets (Definition 47) namely compatible subsets of {a mathematical formula}L and a special symbol ⊥ is used to represents contradiction and it is assumed that contradiction is detected by producing it as conclusion of an argument (Definition 45). In particular, a set of language elements T is incompatible if it is possible to strictly derive ⊥ from it (Definition 46). This could be recasted in terms of our inhibition function saying that T is inhibited by ∅. More precisely, taking into account that the elements of the base set are strict, we say that a set T is inhibited by ∅ if it is a minimal set such that it is possible to strictly derive ⊥ from T, together with some elements of the base set.
     </paragraph>
     <paragraph label="Definition 55">
      Given an AAS, with language {a mathematical formula}L and a base set S, the inhibition function {a mathematical formula}INH:2L→22L on {a mathematical formula}L induced by AAS for base set S is defined as follows: {a mathematical formula}∀T∈2L∖S s.t. {a mathematical formula}T∪U for some {a mathematical formula}U⊆S is minimally incompatible we define {a mathematical formula}INH(T)={∅}; {a mathematical formula}INH(T)=∅ for every T for which {a mathematical formula}INH(T) is not specified by the condition above.
     </paragraph>
     <paragraph>
      Note that, by construction, for {a mathematical formula}T≠∅ it cannot be the case that {a mathematical formula}T∈INH(∅). Moreover, from the consistency of the base set, it follows directly that {a mathematical formula}∅∉INH(∅). Hence the requirement of Definition 4 is satisfied.
     </paragraph>
     <paragraph>
      We can now introduce the notion of LAF-ensemble for AAS.
     </paragraph>
     <paragraph label="Definition 56">
      Given an AAS with language {a mathematical formula}L and a base set S, the LAF-ensemble corresponding to S is defined as {a mathematical formula}LE=〈IF,SS,FI⁎Δ〉 where the inhibition framework {a mathematical formula}IF=〈L,INH〉 is specified by Definition 55, the {a mathematical formula}L-subargument structure {a mathematical formula}SS=〈Σ,⊑〉 is such that {a mathematical formula}Σ=args(S) and ⊑ is specified by Definition 38, and, for each argument α, {a mathematical formula}FIαΔ∈FI⁎Δ is specified by Definition 54.
     </paragraph>
     <paragraph>
      Note that, by definition of base set, the LAF-ensemble corresponding to S is infallibility consistent.
     </paragraph>
     <paragraph>
      We now prove that it is {a mathematical formula}II-consonant (Definition 27).
     </paragraph>
     <paragraph label="Proposition 17">
      Given an AAS with language{a mathematical formula}Land a base set S, the LAF-ensemble corresponding to S is{a mathematical formula}II-consonant.
     </paragraph>
     <paragraph>
      We aim now at defining a set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 (Definition 28) capturing the notion of argument acceptance in AAS.
     </paragraph>
     <paragraph>
      To this purpose let us note that the starting point is provided by the notion of defeater (Definition 48): whenever a set of arguments {a mathematical formula}X⊆args(S) is a defeater of an argument {a mathematical formula}α∈args(S) we could assume that {a mathematical formula}‖X‖ and {a mathematical formula}‖{α}‖ are included in AA and that {a mathematical formula}‖X‖↠‖{α}‖. This basic intuition needs however to be integrated with other properties in order to adhere to the requirements listed in Section 6. This is the aim of the following definition.
     </paragraph>
     <paragraph label="Definition 57">
      Given an AAS with language {a mathematical formula}L and a base set S, a set of arguments X is a primitive defeater of {a mathematical formula}α∈args(S) if (i) X is a minimal defeater of α; (ii) X is compatible; (iii) {a mathematical formula}X⊆UF(args(S))∪S. If X is a primitive defeater of α, {a mathematical formula}X∖S is a genuine defeater of α.
     </paragraph>
     <paragraph>
      In words, a compatible set of arguments which is a minimal defeater is a primitive defeater if it consists only of ultimately fallible arguments and elements of the base set: intuitively the conclusions of a primitive defeater represent the frontier closest to the base set from which a set of strict derivations leading to contradiction is drawn. In a defeater which includes an argument β whose top rule is strict intuitively one may make a step back (to the immediate subarguments of β) while keeping the property of deriving strictly a contradiction with α (and of being compatible). The compatibility requirement is needed to avoid the unnecessary{sup:8} consideration of incompatible defeaters (see e.g. Lemma 6 for the case of singleton incompatible defeaters). A genuine defeater is a primitive defeater without the elements of the base set. Note that the empty set can be a genuine defeater if there is an (obviously defeasible) argument α whose conclusion gives rise to a conflict with some strict consequences of a subset of the base set.
     </paragraph>
     <paragraph>
      It is useful to observe that the singleton including an argument cannot be a genuine defeater of the argument itself.
     </paragraph>
     <paragraph label="Lemma 7">
      For every argument α it cannot be the case that{a mathematical formula}{α}is a genuine defeater of α.
     </paragraph>
     <paragraph>
      Genuine defeaters are the key elements for the definition of the set based argumentation framework for AAS.
     </paragraph>
     <paragraph label="Definition 58">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language {a mathematical formula}L, the set based argumentation framework {a mathematical formula}FLE=〈AA,↠〉 for LE is defined as follows: {a mathematical formula}AA={‖{α}‖|α∈args(S)}∪{‖X‖|∃α∈UF(args(S)) s.t. Xis a genuine defeater of α}; {a mathematical formula}‖X‖↠‖Y‖ iff {a mathematical formula}∃α∈Y and {a mathematical formula}∃β∈UF(Sub(α)) s.t. X is a genuine defeater of β.
     </paragraph>
     <paragraph>
      Let us show that the set based argumentation framework specified by Definition 58 satisfies the requirements presented in Section 6, i.e. it is appropriate for LE. First of all it is singleton covering (Definition 31) by construction. Subargument awareness (Definition 32) and inclusion awareness (Definition 33) are proved easily.
     </paragraph>
     <paragraph label="Proposition 18">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is subargument aware.
     </paragraph>
     <paragraph label="Proposition 19">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is inclusion aware.
     </paragraph>
     <paragraph>
      We then prove the properties of fallible language inhibition coverage (Definition 34) and attack accuracy (Definition 35).
     </paragraph>
     <paragraph label="Proposition 20">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is fallible language inhibition covering.
     </paragraph>
     <paragraph label="Proposition 21">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is attack accurate.
     </paragraph>
     <paragraph>
      Having drawn a correspondence between AASs and our general model, the point is now to show whether the acceptance evaluation encompassed by the set based argumentation framework of Definition 58 has some correspondence with the notions of argument acceptance in the original theory.
     </paragraph>
     <paragraph>
      First of all, we show in Proposition 22 that if there is a compatible defeater for an argument then there is also a primitive, and hence a genuine, defeater for it. This requires a preliminary lemma.
     </paragraph>
     <paragraph label="Lemma 8">
      Given an AAS with language{a mathematical formula}Land a base set S, if there is an argument β with length{a mathematical formula}Len(β)≥2such that the top rule of β is strict then{a mathematical formula}∃Y⊆UF(PSub(β))∪Ssuch that{a mathematical formula}Conc(β)is strictly derivable from{a mathematical formula}Conc(Y).
     </paragraph>
     <paragraph label="Proposition 22">
      Given an AAS with language{a mathematical formula}Land a base set S, if there exists a compatible defeater X of an argument α then there exists also a primitive defeater of α whose ultimately fallible arguments are subarguments of the arguments in X.
     </paragraph>
     <paragraph>
      We now show that AAS extensions (Definition 53) are in correspondence with the stable{sup:9} extensions of the corresponding set based argumentation framework, using two preliminary lemmata.
     </paragraph>
     <paragraph label="Lemma 9">
      Given an AAS with language{a mathematical formula}Land a base set S, let X be a set of arguments such that{a mathematical formula}X=enableS(X). Then X is compatible.
     </paragraph>
     <paragraph label="Lemma 10">
      Given an AAS with language{a mathematical formula}Land a base set S, and given X such that{a mathematical formula}X=enableS(X), for every argument α the following conditions hold: (i) if{a mathematical formula}α∈enableS(X)then{a mathematical formula}∀β∈Sub(α)X does not include any defeater of β; (ii) if{a mathematical formula}α∉enableS(X)then{a mathematical formula}∃β∈UF(Sub(α))such that X includes a defeater of β.
     </paragraph>
     <paragraph label="Proposition 23">
      Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, let{a mathematical formula}FLE=〈AA,↠〉be the set based argumentation framework specified byDefinition 58. A set of arguments X is an extension according toDefinition 53if and only if there is a stable extension{a mathematical formula}Sof{a mathematical formula}FLEsuch that{a mathematical formula}X={α∈Σ|JUSS(α)=⊤}.
     </paragraph>
     <paragraph>
      The above proposition establishes a significant correspondence between one of the central notions in AAS and stable extensions in the corresponding set based argumentation framework. This correspondence is backed by the intuition that in AAS every extension either includes or defeats (possibly through some subargument) an argument, exactly as in the case of stable extensions.
     </paragraph>
     <paragraph>
      In the same line, intuition would suggest another correspondence. In AAS the arguments belonging to {a mathematical formula}limn→∞⁡info2n(S) are called ultimately undefeated arguments. An argument α is ultimately undefeated if and only if for some {a mathematical formula}n≥1, it holds {a mathematical formula}S|∼n+kα for every {a mathematical formula}k≥1. In words, α is ultimately undefeated if its acceptance is rock solid since all its defeaters (if any) are defeated by other ultimately undefeated arguments. Then, one could expect that the set of ultimately defeated arguments coincides with the arguments justified by the grounded extension of {a mathematical formula}FLE.
     </paragraph>
     <paragraph>
      However this is not always the case for a subtle technical reason.
     </paragraph>
     <paragraph>
      Consider a simple AAS with three defeasible rules: ⇒φ, ⇒ψ, ⇒χ and one strict rule {a mathematical formula}φ,ψ→⊥. Then letting the base set {a mathematical formula}S=∅ we have three defeasible arguments {a mathematical formula}α,β,γ corresponding to the three defeasible rules and one additional argument δ using the strict rule and ‘revealing’ the contradiction between φ and ψ. Suppose the three defeasible arguments all have the same conclusive force. Then clearly {a mathematical formula}{α} is a (genuine) defeater of β and {a mathematical formula}{β} is a (genuine) defeater of α. It must be noted however that it also holds that {a mathematical formula}{α,β} is a defeater of γ. In fact, every superset of {a mathematical formula}φ,ψ (in particular the set {a mathematical formula}{φ,ψ,χ}) is incompatible. Then also the set of arguments {a mathematical formula}{α,β,γ} is incompatible and, given that {a mathematical formula}{α,β} is not undermined by γ it follows that {a mathematical formula}{α,β} is a defeater of γ. {a mathematical formula}{α,β} is a minimal defeater, but, not being compatible, is not a primitive, hence not a genuine, defeater. It can be seen that there are two extensions namely {a mathematical formula}{α,γ} and {a mathematical formula}{β,γ} hence, intuitively, γ is accepted in all cases, but γ is not ultimately undefeated. This sounds peculiar because the conclusion of γ, namely χ, might be totally unrelated with those of α and β, namely φ and ψ, and hence one could expect that it should not be affected by a conflict concerning a totally distinct matter. By the way, this possibly undesired side effect is not mentioned in [9] and is overlooked in some examples where it might be mentioned (e.g. in example 4.28 of [9]). In our formalization we get {a mathematical formula}FLE=〈{‖α‖,‖β‖,‖γ‖,‖δ‖},{(‖α‖,‖β‖),(‖β‖,‖α‖),(‖α‖,‖δ‖),(‖β‖,‖δ‖)}〉. Here there are two stable extensions {a mathematical formula}{α,γ} and {a mathematical formula}{β,γ} as above, but γ does not receive attacks and we get that it is the unique member of the grounded extension, corresponding to the intuitive fact that it is an unchallenged argument.
     </paragraph>
     <paragraph>
      This small example shows that the principles underlying the formalism we propose are not only able to capture other existing formalisms within a quite general setting, but also have the capability to point out possible technical and/or conceptual problems inside a formalism and to support the relevant adjustments.
     </paragraph>
     <paragraph>
      In the next section, we will exploit more extensively this capability in the context of the {a mathematical formula}ASPIC+ formalism.
     </paragraph>
    </section>
    <section label="9">
     Revising {a mathematical formula}ASPIC+
     <paragraph>
      {a mathematical formula}ASPIC+ is a well-known formalism described in [13] as “a general abstract model of argumentation with structured arguments” and subsequently developed in [10]. {a mathematical formula}ASPIC+ is an extension of ASPIC[14], able to satisfy the same rationality postulates[7] while offering a more general account of structured argumentation. Indeed, in [10]{a mathematical formula}ASPIC+ is shown to capture a variety of existing argumentation systems. A key aspect in this respect is the adoption of a generic, possibly asymmetric, relation of contrariness between formulas while ASPIC assumes standard negation, i.e. a binary and symmetric contrariness relation. While in [13], [10] it is mainly emphasized that generic contrariness is useful to encompass a larger variety of more specific literature proposals, it can be observed that this notion also opens the way to novel investigation directions, like the use of multivalued logics in the construction of arguments (see [15] for an initial analysis on this issue).
     </paragraph>
     <paragraph>
      As to the evaluation of argument acceptance, both ASPIC and {a mathematical formula}ASPIC+ rely on AFs. The rationality postulates prescribe that the outcomes of this evaluation respect some closure and consistency properties when mapped back at the instantiated level. Both in ASPIC and in {a mathematical formula}ASPIC+ postulate satisfaction is ensured on the basis of some well-formedness assumptions, including some closure properties of the set of strict rules. However, as first pointed out in [8], the combination of a generic contrariness relation and rule closure may give rise to counterintuitive results. To solve this problem while preserving the generality of {a mathematical formula}ASPIC+, in [8] a modified version of the formalism was proposed.
     </paragraph>
     <paragraph>
      In this section, after recalling the main points of the {a mathematical formula}ASPIC+ definitions and the problem pointed out in [8], we provide a solution{sup:10} using the general framework introduced in Sections 3–7.
     </paragraph>
     <section label="9.1">
      The {a mathematical formula}ASPIC+ formalism
      <paragraph>
       We recall in the sequel the essentials of the definition of {a mathematical formula}ASPIC+, omitting some details not required by the present paper.
      </paragraph>
      <paragraph label="Definition 59">
       An argumentation system is a tuple {a mathematical formula}AS=(L,¯,R,n) where:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}L is a logical language
       </list-item>
       <list-item label="2.">
        {a mathematical formula}¯ is a contrariness function from {a mathematical formula}L to {a mathematical formula}2L such that: (i) φ is a contrary of ψ if {a mathematical formula}φ∈ψ‾, {a mathematical formula}ψ∉φ‾; (ii) φ is a contradictory of ψ (denoted by {a mathematical formula}φ=−ψ) if {a mathematical formula}φ∈ψ‾, {a mathematical formula}ψ∈φ‾; (iii) each {a mathematical formula}φ∈L has at least one contradictory
       </list-item>
       <list-item label="3.">
        {a mathematical formula}R=RS∪RD is a set of strict ({a mathematical formula}RS) and defeasible ({a mathematical formula}RD) inference rules of the form {a mathematical formula}φ1,…,φn→φ and {a mathematical formula}φ1,…,φn⇒φ respectively (where {a mathematical formula}φi,φ are meta-variables ranging over wff in {a mathematical formula}L), and {a mathematical formula}RS∩RD=∅
       </list-item>
       <list-item label="4.">
        {a mathematical formula}n:RD→L is a naming convention for {a mathematical formula}RD.
       </list-item>
      </list>
      <paragraph>
       A knowledge base is a subset of {a mathematical formula}L including certain (called axioms) and defeasible (called ordinary) premises. It gives rise to the notion of argumentation theory.
      </paragraph>
      <paragraph label="Definition 60">
       A knowledge base in an argumentation system {a mathematical formula}AS=(L,¯,R,n) is a set {a mathematical formula}K⊆L consisting of two disjoint subsets {a mathematical formula}Kn (the axioms) and {a mathematical formula}Kp (the ordinary premises). The tuple {a mathematical formula}AT=(AS,K) is called an argumentation theory.
      </paragraph>
      <paragraph>
       Two notions of consistency are considered in {a mathematical formula}ASPIC+.
      </paragraph>
      <paragraph label="Definition 61">
       For any {a mathematical formula}S⊆L, let the closure of S under strict rules, denoted {a mathematical formula}ClRS(S), be the smallest set containing S and the consequent of any strict rule in {a mathematical formula}RS, whose antecedents are in {a mathematical formula}ClRS(S). Then a set {a mathematical formula}S⊆L is: (i) directly consistent iff {a mathematical formula}∄φ,ψ∈S such that {a mathematical formula}φ∈ψ‾; (ii) indirectly consistent iff {a mathematical formula}ClRS(S) is directly consistent.
      </paragraph>
      <paragraph>
       Arguments are built from a knowledge base using rules.
      </paragraph>
      <paragraph label="Definition 62">
       An argument α on the basis of a knowledge base {a mathematical formula}K in an argumentation system {a mathematical formula}(L,¯,R,n) is:
       <list>
        φ if {a mathematical formula}φ∈K with: {a mathematical formula}Prem(α)={φ}; {a mathematical formula}Conc(α)=φ; {a mathematical formula}Sub(α)={φ}; {a mathematical formula}Rules(α)=∅; {a mathematical formula}Top(α)=undefined.{a mathematical formula}α1,…,αn→(⇒)ψ if {a mathematical formula}α1,…,αn are arguments such that there exists a strict (defeasible) rule {a mathematical formula}Conc(α1),…,Conc(αn)→(⇒)ψ in {a mathematical formula}RS ({a mathematical formula}RD) with: {a mathematical formula}Prem(α)=Prem(α1)∪…∪Prem(αn); {a mathematical formula}Conc(α)=ψ; {a mathematical formula}Sub(α)=Sub(α1)∪…∪Sub(αn)∪{α}; {a mathematical formula}Rules(α)=Rules(α1)∪…∪Rules(αn)∪{Conc(α1),…,Conc(αn)→(⇒)ψ}; {a mathematical formula}Top(α)=Conc(α1),…,Conc(αn)→(⇒)ψ; {a mathematical formula}DefRules(α)={r|r∈Rules(α)∩RD}; {a mathematical formula}StRules(α)={r|r∈Rules(α)∩RS}.For any argument
       </list>
       <paragraph>
        α, {a mathematical formula}Premn(α)=Prem(α)∩Kn; {a mathematical formula}Premp(α)=Prem(α)∩Kp. α is: strict if {a mathematical formula}DefRules(α)=∅, defeasible if {a mathematical formula}DefRules(α)≠∅; firm if {a mathematical formula}Prem(α)⊆Kn; plausible if {a mathematical formula}Prem(α)⊈Kn; fallible if α is plausible or defeasible; finite if {a mathematical formula}Rules(α) is finite.
       </paragraph>
      </paragraph>
      <paragraph>
       We assume, as in [10], that the set {a mathematical formula}Prem(α) of premises of an argument α is always finite. An argument may include both fallible (ordinary premises and defeasible rules) and infallible (axioms and strict rules) elements. The following definition is based on this distinction.
      </paragraph>
      <paragraph label="Definition 63">
       For any set of arguments {a mathematical formula}{α1,…,αn} the argument α is a strict continuation of {a mathematical formula}{α1,…,αn} iff {a mathematical formula}Premp(α)=⋃i=1nPremp(αi); {a mathematical formula}DefRules(α)=⋃i=1nDefRules(αi); {a mathematical formula}StRules(α)⊇⋃i=1nStRules(αi); {a mathematical formula}Premn(α)⊇⋃i=1nPremn(αi).
      </paragraph>
      <paragraph>
       Some further notations are worth introducing.
      </paragraph>
      <paragraph label="Notation 1">
       <list>
        <list-item label="1.">
         Given {a mathematical formula}S⊆L, {a mathematical formula}S⊢φ denotes that there exists a strict argument α such that {a mathematical formula}Conc(α)=φ, with {a mathematical formula}Prem(α)⊆S.
        </list-item>
        <list-item label="2.">
         {a mathematical formula}S⊢minφ denotes that {a mathematical formula}S⊢φ and {a mathematical formula}∄T⊊S : {a mathematical formula}T⊢φ.
        </list-item>
        <list-item label="3.">
         Given a set of arguments Σ, {a mathematical formula}Prem(Σ)≜⋃α∈ΣPrem(α), and similarly for {a mathematical formula}Conc(Σ), {a mathematical formula}Sub(Σ), {a mathematical formula}Rules(Σ), {a mathematical formula}Top(Σ), {a mathematical formula}DefRules(Σ), {a mathematical formula}StRules(Σ).
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       The notion of c-consistency is based on contradiction.
      </paragraph>
      <paragraph label="Definition 64">
       A set {a mathematical formula}S⊆L is c-consistent if for no φ it holds that {a mathematical formula}S⊢φ,−φ. Otherwise S is c-inconsistent. S is minimally c-inconsistent iff S is c-inconsistent and {a mathematical formula}∀S′⊊S, {a mathematical formula}S′ is c-consistent. An argument α on the basis of a knowledge-base {a mathematical formula}K in an argumentation system {a mathematical formula}(L,¯,R,n) is c-consistent iff {a mathematical formula}Prem(α) is c-consistent.
      </paragraph>
      <paragraph>
       Accordingly, several properties for an argumentation theory can be formulated.
      </paragraph>
      <paragraph label="Definition 65">
       Let {a mathematical formula}AT=(AS,K) be an argumentation theory, where {a mathematical formula}AS=(L,¯,R,n). AT is:
      </paragraph>
      <list>
       <list-item label="1.">
        closed under contraposition iff for all {a mathematical formula}S⊆L, {a mathematical formula}ψ∈S, {a mathematical formula}φ∈L, if {a mathematical formula}S⊢φ then {a mathematical formula}S∖{ψ}∪{−φ}⊢−ψ;
       </list-item>
       <list-item label="2.">
        closed under transposition iff if {a mathematical formula}φ1,…,φn→ψ∈RS then, for {a mathematical formula}i=1…n, {a mathematical formula}φ1,…,φi−1,−ψ,φi+1,…,φn→−φi∈RS;
       </list-item>
       <list-item label="3.">
        axiom consistent iff {a mathematical formula}ClRS(Kn) is directly consistent;
       </list-item>
       <list-item label="4.">
        c-classical iff for any minimal c-inconsistent {a mathematical formula}S⊆L and for any {a mathematical formula}φ∈S, it holds that {a mathematical formula}S∖{φ}⊢−φ;
       </list-item>
       <list-item label="5.">
        well-formed if whenever φ is a contrary of ψ then {a mathematical formula}ψ∉Kn and ψ is not the consequent of a strict rule.
       </list-item>
      </list>
      <paragraph>
       Three kinds of attack between arguments are considered.
      </paragraph>
      <paragraph label="Definition 66">
       An argument αattacks an argument β iff αundercuts, rebuts, or underminesβ where:
      </paragraph>
      <list>
       <list-item label="•">
        αundercutsβ (on {a mathematical formula}β′) iff {a mathematical formula}Conc(α)∈n(r)‾ for some {a mathematical formula}β′∈Sub(β) such that {a mathematical formula}r=Top(β′) is defeasible.
       </list-item>
       <list-item label="•">
        αrebutsβ (on {a mathematical formula}β′) iff {a mathematical formula}Conc(α)∈φ‾ for some {a mathematical formula}β′∈Sub(β) of the form {a mathematical formula}β1″,…,βn″⇒φ. In such a case αcontrary-rebutsβ iff {a mathematical formula}Conc(α) is a contrary of φ.
       </list-item>
       <list-item label="•">
        αunderminesβ (on {a mathematical formula}β′) iff {a mathematical formula}Conc(α)∈φ‾ for some {a mathematical formula}β′=φ, {a mathematical formula}φ∈Premp(β). In such a case αcontrary-underminesβ iff {a mathematical formula}Conc(α) is a contrary of φ.
       </list-item>
      </list>
      <paragraph>
       Attack effectiveness, in some cases, depends on an ordering ⪯ over arguments, where {a mathematical formula}α⪯β means that argument β is at least as preferred as α and, following [13], we assume that ⪯ is a preorder. As usual {a mathematical formula}α≺β iff {a mathematical formula}α⪯β and {a mathematical formula}β⪯̸α; {a mathematical formula}α≈β iff {a mathematical formula}α⪯β and {a mathematical formula}β⪯α.
      </paragraph>
      <paragraph label="Definition 67">
       An argument ordering ⪯ is reasonable iff:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}∀α,β if α is strict and firm and β is plausible or defeasible, then {a mathematical formula}β≺α;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}∀α,β if α is strict and firm then {a mathematical formula}α⊀β;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}∀α,α′,β with {a mathematical formula}α′ a strict continuation of {a mathematical formula}{α}, if {a mathematical formula}α⊀β then {a mathematical formula}α′⊀β and if {a mathematical formula}β⊀α then {a mathematical formula}β⊀α′;
       </list-item>
       <list-item label="4.">
        let {a mathematical formula}Θ={α1,…,αn} be a finite set of arguments and for {a mathematical formula}i=1…n let {a mathematical formula}α+∖i be some strict continuation of {a mathematical formula}Θ∖{αi}. Then, it is not the case that ∀i{a mathematical formula}α+∖i≺αi.
       </list-item>
      </list>
      <paragraph>
       Effective attacks give rise to defeat.
      </paragraph>
      <paragraph label="Definition 68">
       Let α attack β on {a mathematical formula}β′. If α undercuts, contrary-rebuts, or contrary-undermines β on {a mathematical formula}β′, then αpreference-independent attacks β on {a mathematical formula}β′, otherwise αpreference-dependent attacks β on {a mathematical formula}β′. Then, αdefeatsβ iff for some {a mathematical formula}β′ either αpreference-independent attacks β on {a mathematical formula}β′ or αpreference-dependent attacks β on {a mathematical formula}β′ and {a mathematical formula}α⊀β′. αstrictly defeatsβ iff α defeats β and β does not defeat α.
      </paragraph>
      <paragraph>
       Two kinds of structured argumentation frameworks are defined from an argumentation theory, using the attack relation.
      </paragraph>
      <paragraph label="Definition 69">
       Let {a mathematical formula}AT=(AS,K) be an argumentation theory. A (c-)structured argumentation framework, denoted as {a mathematical formula}(c-)SAF, defined by AT is a triple {a mathematical formula}(Σ,C,⪯) where Σ is the set of all (c-consistent) finite arguments constructed from {a mathematical formula}K in AS (henceforth called the set of arguments on the basis of AT), {a mathematical formula}C⊆Σ×Σ is such that {a mathematical formula}(α,β)∈C iff α attacks β, and ⪯ is an ordering on Σ.
      </paragraph>
      <paragraph label="Definition 70">
       Well-definedness of (c-)structured argumentation frameworks depends on the properties of the underlying theory. A SAF defined by an AT is well-defined iff AT is c-classical, axiom consistent, well-formed and closed under contraposition or closed under transposition; A {a mathematical formula}c-SAF defined by an AT is well-defined iff AT is axiom consistent, well-formed and closed under contraposition or closed under transposition.
      </paragraph>
      <paragraph>
       A traditional Dung's framework is derived from a {a mathematical formula}(c-)SAF using the defeat relation.
      </paragraph>
      <paragraph label="Definition 71">
       Let {a mathematical formula}Δ=(Σ,C,⪯) be a {a mathematical formula}(c-)SAF, and {a mathematical formula}D⊆Σ×Σ be the defeat relation according to Definition 68. The AF corresponding to Δ is defined as {a mathematical formula}FΔ=(Σ,D).
      </paragraph>
      <paragraph>
       Compliance with rationality postulates is then proved in [10] under the assumptions above.
      </paragraph>
      <paragraph label="Theorem 1">
       Let{a mathematical formula}Δ=(Σ,C,⪯)be a well-defined{a mathematical formula}(c-)SAFwith reasonable ⪯ and E a complete extension of{a mathematical formula}FΔ. Then
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∀α∈Eif{a mathematical formula}α′∈Sub(α)then{a mathematical formula}α′∈E;
       </list-item>
       <list-item label="•">
        {a mathematical formula}{Conc(α)|α∈E}=ClRS({Conc(α)|α∈E});
       </list-item>
       <list-item label="•">
        {a mathematical formula}{Conc(α)|α∈E}is consistent;
       </list-item>
       <list-item label="•">
        {a mathematical formula}ClRS({Conc(α)|α∈E})is consistent.
       </list-item>
      </list>
     </section>
     <section label="9.2">
      A problem in {a mathematical formula}ASPIC+ without negation
      <paragraph>
       Definition 59 is liberal about the notion of contrariness and contradiction. In particular, it requires every {a mathematical formula}φ∈L to have a contradictory (to ensure that the items of Definition 65 using − are well-founded) but leaves open the possibility of having more than one contradictory. However this may give rise to difficulties with the closure properties stated in Definition 65. To see this, consider a simple language {a mathematical formula}L6={B,M,D,T,A,O} meant to intuitively correspond to the properties of being Bachelor, Married, Divorced, Teen-ager, Adult, and Old respectively, where the former three properties are mutually exclusive and so are the three latter ones, hence {a mathematical formula}B‾={M,D}, {a mathematical formula}M‾={B,D}, {a mathematical formula}D‾={B,M}, and {a mathematical formula}T‾={A,O}, {a mathematical formula}A‾={T,O}, {a mathematical formula}O‾={T,A}.
      </paragraph>
      <paragraph>
       Suppose now that as a strict rule (e.g. imposed by law) a teen-ager is a bachelor, i.e. {a mathematical formula}T→B∈RS. Moreover, suppose that closure under transposition is applied to this rule. We get {a mathematical formula}−B→−T, however both −B and −T admit two replacements, namely M or D and A or O respectively. Hence a plain application of closure under transposition generates four strict rules: {a mathematical formula}M→A, {a mathematical formula}M→O, {a mathematical formula}D→A, {a mathematical formula}D→O. It follows that both {a mathematical formula}{M} and {a mathematical formula}{D} are c-inconsistent. Then a c-classical AT (required for a well-defined SAF) would impose {a mathematical formula}∅⊢−M and {a mathematical formula}∅⊢−D, leading to {a mathematical formula}∅⊢B,D,M, i.e. contradictory conclusions should be strictly derived from the empty set. Given that AT must be axiom consistent, it follows that {a mathematical formula}L6 with {a mathematical formula}T→B∈RS is forbidden in a well-defined SAF.
      </paragraph>
      <paragraph>
       A well-defined {a mathematical formula}c-SAF does not require a c-classical AT, but arguments must be c-consistent, which, in this case, implies in particular that neither M nor D can be premises. To put it in other words, the fact that a teen-ager must be bachelor prevents you to have as a premise that a person is married or divorced. Note that these observations do not affect the correctness of the results in [10], rather they show that multiple contradictories may give rise to a collapse of the expressiveness of the system: consistency is preserved at the price of very counterintuitive limitations.
      </paragraph>
      <paragraph>
       One could fix this problem by requiring in Definition 65 every element of the language to have exactly one contradictory. Indeed the main example presented in [10] is coherent with this restriction. It may be noted however that this amounts to actually reintroduce negation within the language, though in disguise. While using negation (and possibly also disjunction) would be appropriate to this toy example, proposing it as the general solution to these difficulties would compromise the aim of {a mathematical formula}ASPIC+ of being as language-independent as possible. Quoting [13], “formulas like bachelor and married can, if desired, be declared contradictory without having to reason with an axiom {a mathematical formula}¬(bachelor∧married)”. Moreover this restriction would be incompatible with the perspective of investigating argumentation systems based on multi-valued logics, where the existence of more than two truth values implies that there can be multiple contradictories. In this spirit, we exclude the adoption of very specific technical fixes, like for instance forbidding that two contraries of a formula are in turn contrary each other, and in the next section we revisit {a mathematical formula}ASPIC+ in the context of the general framework we are proposing.
      </paragraph>
     </section>
     <section label="9.3">
      {a mathematical formula}ASPIC+ revisited
      <paragraph>
       We assume the same basic elements of {a mathematical formula}ASPIC+ removing any further specification and constraint on the contrariness function but adding the constraint that the name of a rule cannot be the contrary of anything, i.e. for every rule r{a mathematical formula}∄φ∈L such that {a mathematical formula}n(r)∈φ‾. This, in our opinion rather natural, constraint was not present in the original definition of {a mathematical formula}ASPIC+ probably because the notion of extensive consistency was not considered in that context.{sup:11} Similarly we forbid the names of the rules to be included in the antecedent of a rule or in the knowledge base. Thus, in Definition 59 items 1 and 4 are unmodified, while item 2 is reduced to: {a mathematical formula}¯ is a function from {a mathematical formula}L to {a mathematical formula}2L∖RN where {a mathematical formula}RN={n(r)|r∈RD}, and in item 3 {a mathematical formula}φi are meta-variables ranging over wff in {a mathematical formula}L∖RN while φ is a meta-variable ranging over wff in {a mathematical formula}L.
      </paragraph>
      <paragraph>
       In Definition 60 we prescribe {a mathematical formula}K⊆L∖RN while Definition 61, Definition 62, as well as Notation 1 are left unmodified.
      </paragraph>
      <paragraph>
       We then leave apart the notion of strict continuation (Definition 63) and of c-consistency (Definition 64) and, among the properties of Definition 65, we keep only the property of axiom consistency and a relaxed notion of well-formedness, which involves axioms and their strict consequences rather than all the consequents of strict rules. More precisely, we define the property of weak well-formedness as follows.
      </paragraph>
      <paragraph label="Definition 72">
       Let {a mathematical formula}AT=(AS,K) be an argumentation theory, where {a mathematical formula}AS=(L,¯,R,n). AT is weakly well-formed if whenever {a mathematical formula}φ∈ψ‾ and {a mathematical formula}ψ∈Kn or ψ can be obtained from {a mathematical formula}Kn by applying strict rules, it also holds that {a mathematical formula}ψ∈φ‾.
      </paragraph>
      <paragraph>
       As to the closure requirements, closure under transposition imposes a sort of explicit completeness of the set of strict rules with respect to contradictories, i.e. based on the − relation, while closure under contraposition imposes this completeness implicitly through the notion of strict derivation ⊢. The use of − being problematic, (explicit or implicit) closure of strict rules cannot be adopted. In the spirit of the analysis carried out in Section 5, one can, however, pursue the complementary idea of establishing a closure of the contrariness relation on the basis of strict rules and axioms, based on the fact that the contrariness relation captures some form of (directional) incompatibility.
      </paragraph>
      <paragraph>
       Accordingly, we introduce an extended contrariness relation between subsets of {a mathematical formula}L obtained as a ‘completion’ of the basic contrariness relation {a mathematical formula}¯. A preliminary clarification is required. Taking into account Definition 62 and Notation 1, in an argumentation theory strict derivation must start from the knowledge base, i.e. {a mathematical formula}S⊢minφ implies {a mathematical formula}S⊆K. However, starting from a given contrariness relation {a mathematical formula}¯, we aim at defining a notion of closure that does not depend on the set of premises in the knowledge base but only on the contrariness relation itself and the set of strict rules.{sup:12} To this purpose we need to define a notion of strict derivability, rather than of strict derivation, namely the possibility to derive a conclusion from some elements of the language using strict rules only, independently of the presence of these elements in the knowledge base.
      </paragraph>
      <paragraph label="Definition 73">
       Given an argumentation system {a mathematical formula}AS=(L,¯,R,n) the strict knowledge base {a mathematical formula}KAS⁎ for AS is given by {a mathematical formula}Kn=L, {a mathematical formula}Kp=∅ and the corresponding argumentation theory is defined as {a mathematical formula}ATAS⁎=(AS,KAS⁎). {a mathematical formula}S⊢⁎φ and {a mathematical formula}S⊢min⁎φ denote respectively that {a mathematical formula}S⊢φ and {a mathematical formula}S⊢minφ in {a mathematical formula}ATAS⁎.
      </paragraph>
      <paragraph>
       Note that, by definition, for any {a mathematical formula}φ∈L it holds that {a mathematical formula}{φ}⊢⁎φ, while it may not be the case that {a mathematical formula}{φ}⊢min⁎φ. Note also that, from the finiteness of the set of premises of any argument, whenever {a mathematical formula}S⊢min⁎φ, S is finite.
      </paragraph>
      <paragraph>
       The extended contrariness relation is then obtained by the closure mentioned above together with a requirement of minimality to avoid redundancies.
      </paragraph>
      <paragraph label="Definition 74">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) with {a mathematical formula}AS=(L,¯,R,n), let {a mathematical formula}EC⁎(AS)⊆2L×2L be defined as {a mathematical formula}EC⁎(AS)={(S,T)|S⊢⁎φ,T⊢⁎ψ and φ∈ψ‾}. Letting for {a mathematical formula}S⊆L, {a mathematical formula}Sˆ=S∖Kn, the extended contrariness relation is defined as {a mathematical formula}EC(AS)={(Sˆ,Tˆ)|(S,T)∈EC⁎(AS) and ∀(S′,T′)∈EC⁎(AS) s.t. S′ˆ⊆Sˆ and T′ˆ⊆Tˆ,S′ˆ=Sˆ and T′ˆ=Tˆ}⊆2L×2L. U is a contrary of V if {a mathematical formula}(U,V)∈EC(AS) and {a mathematical formula}(V,U)∉EC(AS); U is a contradictory of V if {a mathematical formula}(U,V)∈EC(AS) and {a mathematical formula}(V,U)∈EC(AS).
      </paragraph>
      <paragraph>
       In words, {a mathematical formula}EC⁎(AS) corresponds to the completion of the contrariness relation {a mathematical formula}¯ on the basis of the set of strict rules, i.e. a set S is regarded as ‘being against’ a set T if a strict consequence of S ‘is against’ a strict consequence of T. Then for each pair {a mathematical formula}(S,T)∈EC⁎(AS) the corresponding pair {a mathematical formula}(Sˆ,Tˆ) where axioms are excluded is considered. Among these pairs, only those which are not redundant belong to {a mathematical formula}EC(AS).
      </paragraph>
      <paragraph>
       The following lemma follows directly from the above definition.
      </paragraph>
      <paragraph label="Lemma 11">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), if{a mathematical formula}(S,T)∈EC⁎(AS)then{a mathematical formula}∃S′⊆Sˆ⊆S,{a mathematical formula}∃T′⊆Tˆ⊆T, such that{a mathematical formula}(S′,T′)∈EC(AS).
      </paragraph>
      <paragraph>
       As proved below, Definition 74 can be equivalently expressed in the more constructive form encompassed by the following definition.
      </paragraph>
      <paragraph label="Definition 75">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) with {a mathematical formula}AS=(L,¯,R,n), let {a mathematical formula}EC1(AS), {a mathematical formula}EC2(AS), {a mathematical formula}EC3(AS) be the following subsets of {a mathematical formula}2L×2L
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}EC1(AS)={({φ},{ψ})|φ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC2(AS)={(S,{ψ})|S⊢min⁎φ and φ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC3(AS)={(S,T)|T⊢min⁎ψ and (S,{ψ})∈EC1(AS)∪EC2(AS)}.
       </list-item>
      </list>
      <paragraph>
       Let us comment on the above definition. First, {a mathematical formula}EC⁎m(AS) is defined in a constructive incremental way starting from {a mathematical formula}EC1(AS) which mirrors, at level of singletons, the contrariness relation {a mathematical formula}¯. Then {a mathematical formula}EC2(AS) is defined taking into account {a mathematical formula}EC1(AS), i.e. the contrariness relation {a mathematical formula}¯, and the strict rules: basically a set S is put in relation to {a mathematical formula}{ψ}, i.e. is regarded as being against {a mathematical formula}{ψ}, if it is possible to strictly derive a contradiction to ψ from S. Finally {a mathematical formula}EC3(AS) is defined taking into account {a mathematical formula}EC1(AS) and {a mathematical formula}EC2(AS): a set S is put in relation to T, i.e. is regarded as being against T, if S is against some {a mathematical formula}{ψ} according to {a mathematical formula}EC1(AS) or {a mathematical formula}EC2(AS) and ψ strictly follows from T. Then, as in Definition 74, for each pair {a mathematical formula}(S,T)∈EC⁎m(AS) the corresponding pair {a mathematical formula}(Sˆ,Tˆ) where axioms are excluded is considered. Among these pairs, only those which are not redundant belong to {a mathematical formula}ECm(AS).
      </paragraph>
      <paragraph>
       Equivalence between Definition 74 and Definition 75 is proven in Proposition 24, which requires two preliminary lemmata.
      </paragraph>
      <paragraph label="Lemma 12">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n),{a mathematical formula}EC⁎(AS)=EC⁎1(AS)∪EC⁎2(AS)∪EC⁎3(AS), where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}EC⁎1(AS)={({φ},{ψ})|φ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC⁎2(AS)={(S,{ψ})|S⊢⁎φandφ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC⁎3(AS)={(S,T)|T⊢⁎ψand(S,{ψ})∈EC⁎1(AS)∪EC⁎2(AS)}.
       </list-item>
      </list>
      <paragraph label="Lemma 13">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), the following conditions hold:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∀(S,T)∈EC⁎m(AS),{a mathematical formula}(S,T)∈EC⁎(AS).
       </list-item>
       <list-item label="•">
        {a mathematical formula}∀(S,T)∈EC⁎(AS),{a mathematical formula}∃(S′,T′)∈EC⁎m(AS)such that{a mathematical formula}S′⊆Sand{a mathematical formula}T′⊆T.
       </list-item>
      </list>
      <paragraph label="Proposition 24">
       Definition 74, Definition 75are equivalent, i.e.{a mathematical formula}(S,T)∈EC(AS)iff{a mathematical formula}(S,T)∈ECm(AS).
      </paragraph>
      <paragraph>
       It should be noted that any two sets S and T such that {a mathematical formula}(S,T)∈EC(AS), or equivalently {a mathematical formula}(S,T)∈ECm(AS), are finite. This can easily be seen by considering the characterization encompassed in Definition 75 and the fact that, as recalled above, if {a mathematical formula}S⊢min⁎φ then S is finite.
      </paragraph>
      <paragraph>
       In the following we will consider Definition 74, since this will make the proofs of the paper easier. The idea we pursue is that {a mathematical formula}EC(AS) corresponds to the inhibition function of LAF-ensembles. It is then useful to show that {a mathematical formula}EC satisfies the property required for {a mathematical formula}INH by Definition 4.
      </paragraph>
      <paragraph label="Proposition 25">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n),{a mathematical formula}(∅,∅)∉EC(AS).
      </paragraph>
      <paragraph>
       We can now revise accordingly the various forms of attack, replacing Definition 66 with the following definition.
      </paragraph>
      <paragraph label="Definition 76">
       Given an argumentation theory {a mathematical formula}AT=(AS,K), a set of arguments Σ attacks an argument β iff Σ undercuts, rebuts, or underminesβ where:
      </paragraph>
      <list>
       <list-item label="•">
        Σ undercutsβ (on {a mathematical formula}β′) iff for some {a mathematical formula}β′∈Sub(β) such that {a mathematical formula}r=Top(β′)∈RD, the following condition holds: {a mathematical formula}∃T,U such that {a mathematical formula}T∪U=Conc(Σ)∪{n(r)}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}n(r)∈U.
       </list-item>
       <list-item label="•">
        Σ rebutsβ (on {a mathematical formula}β′) iff for some {a mathematical formula}β′∈Sub(β) of the form {a mathematical formula}β1″,…,βn″⇒φ the following condition holds: {a mathematical formula}∃T,U such that {a mathematical formula}T∪U=Conc(Σ)∪{φ}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}φ∈U. In this case Σ contrary-rebutsβ if {a mathematical formula}(U,T)∉EC(AS).
       </list-item>
       <list-item label="•">
        Σ underminesβ (on {a mathematical formula}β′) iff for some {a mathematical formula}β′=φ, {a mathematical formula}φ∈Premp(β) the following condition holds: {a mathematical formula}∃T,U such that {a mathematical formula}T∪U=Conc(Σ)∪{φ}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}φ∈U. In this case Σ contrary-underminesβ if {a mathematical formula}(U,T)∉EC(AS).
       </list-item>
      </list>
      <paragraph>
       As far as the notion of undercut is concerned, the following proposition proves that any set including the name of a rule cannot be against any other set. This explains why there is no need for a notion of “contrary-undercut” in the first item of Definition 76.
      </paragraph>
      <paragraph label="Proposition 26">
       For any two sets{a mathematical formula}T,Usuch that{a mathematical formula}T∩RN≠∅, it cannot be the case that{a mathematical formula}(T,U)∈EC(AS).
      </paragraph>
      <paragraph>
       The following proposition shows that it is not possible to be against a set which includes a rule name together with other elements, i.e. if T is against U and U includes a rule name then U is a singleton including the rule name only.
      </paragraph>
      <paragraph label="Proposition 27">
       For any two sets{a mathematical formula}T,Usuch that{a mathematical formula}(T,U)∈EC(AS), if{a mathematical formula}U∩RN≠∅then{a mathematical formula}U={n(r)}with{a mathematical formula}r∈RD.
      </paragraph>
      <paragraph>
       As the effectiveness of some attacks depends on the preference relation, we need to generalize the notion of preference ordering to our extended context. We drop Definition 67 and we only assume as given a preorder ⪯ between arguments.
      </paragraph>
      <paragraph label="Definition 77">
       Given a preorder ⪯ on a set of arguments Σ, we extend ⪯ to {a mathematical formula}2Σ×Σ as follows. An argument α is at least as preferred as a set of arguments Θ, denoted as {a mathematical formula}Θ⪯α, iff {a mathematical formula}∃β∈Θ such that {a mathematical formula}β⪯α. α is strictly preferred to Θ, denoted as {a mathematical formula}Θ≺α, iff {a mathematical formula}∃β∈Θ such that {a mathematical formula}β≺α, not strictly preferred to Θ, denoted {a mathematical formula}Θ⊀α iff {a mathematical formula}∄β∈Θ such that {a mathematical formula}β≺α.
      </paragraph>
      <paragraph>
       Note that it would have not been possible to define {a mathematical formula}Θ≺α as {a mathematical formula}Θ⪯α∧α⪯̸Θ, since the relation {a mathematical formula}α⪯Θ (between an element and a set) is undefined. Note also that the relations ⪯ and ≺ extend the corresponding relations between the arguments of Σ, i.e. {a mathematical formula}α⪯β iff {a mathematical formula}{α}⪯β and {a mathematical formula}α≺β iff {a mathematical formula}{α}≺β.
      </paragraph>
      <paragraph>
       According to Definition 77, we can define an extended notion of defeat, thus replacing Definition 68.
      </paragraph>
      <paragraph label="Definition 78">
       Let the set of arguments Θ attack an argument β on {a mathematical formula}β′ according to Definition 76. If Θ undercuts, contrary-rebuts, or contrary-undermines β on {a mathematical formula}β′, then Θ preference-independent attacks β on {a mathematical formula}β′, otherwise Θ preference-dependent attacks β on {a mathematical formula}β′. Then, Θ defeatsβ iff either Θ preference-independent attacks β on {a mathematical formula}β′ or Θ preference-dependent attacks β on {a mathematical formula}β′ and {a mathematical formula}Θ⊀β′. Θ minimally defeatsβ, denoted as {a mathematical formula}Θ⇝β, if Θ defeats β and {a mathematical formula}∄Θ′⊊Θ such that {a mathematical formula}Θ′ defeats β.
      </paragraph>
      <paragraph>
       It should be noted that whenever {a mathematical formula}Θ⇝β holds Θ is finite: this can be easily seen from Definition 76 taking into account that, as noted above, if {a mathematical formula}(S,T)∈EC(AS) then both S and T are finite.
      </paragraph>
      <paragraph>
       Lemma 14, Lemma 15 are used later (the obvious proofs are omitted).
      </paragraph>
      <paragraph label="Lemma 14">
       If Θ is finite,{a mathematical formula}∃α∈Θ:(Θ∖{α})⊀α.
      </paragraph>
      <paragraph label="Lemma 15">
       Given an argumentation theory{a mathematical formula}AT=(AS,K), if{a mathematical formula}Θ⇝αthen{a mathematical formula}Θ⇝βfor every β such that{a mathematical formula}α∈Sub(β).
      </paragraph>
      <paragraph>
       The proposed revision of the {a mathematical formula}ASPIC+ formalism is clearly inspired by the concepts presented in Sections 3–7. In the view of introducing the LAF-ensemble for {a mathematical formula}ASPIC+ let us now examine the relevant formal correspondences and introduce some additional required elements.
      </paragraph>
      <paragraph>
       First, referring to the language {a mathematical formula}L the inhibition function {a mathematical formula}INH corresponds to the extended contrariness relation {a mathematical formula}EC(AS) (Definition 74), with the required property guaranteed by Proposition 25.
      </paragraph>
      <paragraph>
       Concerning the notion of argument (Definition 7), every argument α satisfying Definition 62 has a conclusion {a mathematical formula}Conc(α) as prescribed by Definition 62 and we can assume that a distinct identifier {a mathematical formula}AI(α) is assigned to each argument. As to the notion of attackable elements, we adopt a very simple one: if the top rule of an argument α is defeasible then its name is the only attackable element of α, otherwise α has no attackable elements.
      </paragraph>
      <paragraph label="Definition 79">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) and an argument α built on the basis of {a mathematical formula}K we define {a mathematical formula}AE(α)={n(Top(α))} if {a mathematical formula}Top(α)∈RD, {a mathematical formula}AE(α)=∅ otherwise.
      </paragraph>
      <paragraph>
       The subargument relation ⊑ (Definition 8) is also specified by Definition 62. We restrict our consideration to systems where for every argument α the set {a mathematical formula}Sub(α) is finite. As pointed out in [13], Definition 62 allows arguments which are ‘backward’ infinite and hence have an infinite set of subarguments. We rule out this possibility, by considering only systems where these arguments do not appear. This restriction does not affect significantly the expressiveness of {a mathematical formula}ASPIC+ (the conceptual status of backward infinite arguments, which are not grounded on any premise, is quite dubious in our view) while it avoids the peculiar technical complications related to this specific case in the analysis of the properties of the proposed revision of the formalism.
      </paragraph>
      <paragraph>
       As to the fallibility classification (Definition 10), in {a mathematical formula}ASPIC+ infallible arguments must be both firm and strict arguments (Definition 62) while fallible arguments are those which are defeasible or plausible.
      </paragraph>
      <paragraph label="Definition 80">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) for every argument α we define {a mathematical formula}FI(α)=I iff {a mathematical formula}Prem(α)⊆Kn and {a mathematical formula}DefRules(α)=∅; {a mathematical formula}FI(α)=F otherwise.
      </paragraph>
      <paragraph>
       It is easy to see that this definition satisfies the requirements for infallible arguments specified in Definition 10: if an argument α is strict and firm it has no defeasible top rule, hence {a mathematical formula}AE(α)=∅. Moreover if it is strict and firm it cannot have any subargument which is not strict and firm too.
      </paragraph>
      <paragraph>
       Concerning the incremental fallibility classification (Definition 11) we use an analogous definition as for AAS.
      </paragraph>
      <paragraph label="Definition 81">
       Given an argumentation theory AT, for every argument α and {a mathematical formula}X⊆Sub(α) we define {a mathematical formula}FIαΔ(X)=I iff {a mathematical formula}∀β∈Sub(α)∖X such that {a mathematical formula}∄γ∈X with {a mathematical formula}β⊑γ, it holds that β is an axiom or the top rule of β is strict; {a mathematical formula}FIαΔ(X)=F otherwise.
      </paragraph>
      <paragraph>
       We have to show that this notion satisfies the properties stated in Definition 11.
      </paragraph>
      <paragraph label="Proposition 28">
       Given an argumentation theory AT, for every argument α the function{a mathematical formula}FIαΔintroduced inDefinition 81satisfies the requirements ofDefinition 11.
      </paragraph>
      <paragraph>
       It can be seen that the incremental fallibility classification introduced in Definition 81 induces the fallibility classification of Definition 80, i.e. {a mathematical formula}FIαΔ(∅)=FI(α).
      </paragraph>
      <paragraph label="Proposition 29">
       Given an argumentation theory AT,{a mathematical formula}∀α∈Σit holds that{a mathematical formula}FIαΔ(∅)=FI(α).
      </paragraph>
      <paragraph>
       Referring to Definition 13 and considering Definition 81, it turns out that an argument is ultimately fallible if it is an ordinary premise or its top rule is defeasible, ultimately infallible if it is an axiom or its top rule is strict. Moreover, for any argument the conclusion can be strictly derived from the (possibly empty) set of conclusions of its fallible frontier along with some axioms. This is formalized in the following lemma, whose obvious proof is omitted.
      </paragraph>
      <paragraph label="Lemma 16">
       Given an argumentation theory AT,{a mathematical formula}∀α∈Σ{a mathematical formula}∃K1⊆Knsuch that{a mathematical formula}Conc(FF(α))∪K1⊢⁎Conc(α).
      </paragraph>
      <paragraph>
       We can now introduce the notion of LAF-ensemble for an argumentation theory AT.
      </paragraph>
      <paragraph label="Definition 82">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) such that every argument has a finite set of subarguments, the LAF-ensemble corresponding to AT is defined as {a mathematical formula}LE=〈IF,SS,FI⁎Δ〉 where the inhibition framework {a mathematical formula}IF=〈L,INH〉 is specified by Definition 74, i.e. {a mathematical formula}X∈INH(Y) iff {a mathematical formula}(X,Y)∈EC(AS), the {a mathematical formula}L-subargument structure {a mathematical formula}SS=〈Σ,⊑〉 is such that Σ is the set of arguments built on the basis of {a mathematical formula}K (Definition 62), for each argument α the set {a mathematical formula}AE(α) is specified by Definition 79 and ⊑ is specified by Definition 62, and, for each argument α, {a mathematical formula}FIαΔ∈FI⁎Δ is specified by Definition 81.
      </paragraph>
      <paragraph>
       First of all, we prove that the LAF-ensemble prescribed by Definition 82 is {a mathematical formula}II-consonant.
      </paragraph>
      <paragraph label="Proposition 30">
       Given an argumentation theory{a mathematical formula}AT=(AS,K), the LAF-ensemble corresponding to AT is{a mathematical formula}II-consonant.
      </paragraph>
      <paragraph>
       We can now define an AF based on the notion of defeat provided in Definition 78 in order to evaluate the justification status of arguments. The idea is that the nodes of the framework represent relevant sets of arguments. In particular we need a node for each singleton corresponding to a produced argument, and a node for each set of ultimately fallible arguments that minimally defeats some produced argument.
      </paragraph>
      <paragraph label="Definition 83">
       Given an argumentation theory {a mathematical formula}AT=(AS,K) with ordering ⪯, let {a mathematical formula}ARGS(AT) be the set of the arguments produced in AS on the basis of {a mathematical formula}K. The set of relevant sets of arguments of AT, denoted as {a mathematical formula}RS(AT), is defined as {a mathematical formula}RS(AT)={{α}|α∈ARGS(AT)}∪{Θ|Θ⊆UF(ARGS(AT)) and {a mathematical formula}∃β∈ARGS(AT):Θ⇝β}.
      </paragraph>
      <paragraph>
       It should be noted that for any {a mathematical formula}Θ∈RS(AT), Θ is finite, since it is a singleton or a minimal defeater of an argument (and minimal defeaters, as recalled above, are finite).
      </paragraph>
      <paragraph>
       In the AF a relevant set of ultimately fallible arguments attacks another one simply if it minimally defeats one of its members.
      </paragraph>
      <paragraph label="Definition 84">
       Let {a mathematical formula}Θ,Λ∈RS(AT) for an argumentation theory AT. Θ D-attacks Λ, denoted as {a mathematical formula}‖Θ‖↠‖Λ‖, iff {a mathematical formula}Θ⊆UF(ARGS(AT)) and {a mathematical formula}∃α∈Λ:Θ⇝α.
      </paragraph>
      <paragraph>
       The relevant set based AF is defined accordingly.
      </paragraph>
      <paragraph label="Definition 85">
       Given an argumentation theory {a mathematical formula}AT=(AS,K), the {a mathematical formula}RS-based argumentation framework induced by AT is defined as {a mathematical formula}RS−AF(AT)=({‖Θ‖|Θ∈RS(AT)},↠).
      </paragraph>
      <paragraph>
       A particular role is played by the empty set. It belongs to {a mathematical formula}RS(AT) iff there is an argument {a mathematical formula}β∈ARGS(AT) for which a defeasible rule, an ordinary premise or a (possibly intermediate) conclusion defeasibly derived is in contradiction with the axioms in the knowledge base. In this case, {a mathematical formula}‖∅‖↠‖{β}‖ holds. This is more precisely stated in the following proposition.
      </paragraph>
      <paragraph label="Proposition 31">
       Given an argumentation theory{a mathematical formula}AT=(AS,K),{a mathematical formula}∅∈RS(AT)iff{a mathematical formula}∃β∈ARGS(AT)such that one of the following two conditions hold:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∃β′∈Sub(β)such that{a mathematical formula}Top(β′)=ror{a mathematical formula}β′is of the form{a mathematical formula}β1″,…,βn″⇒n(r),{a mathematical formula}r∈RD, and ∃φ such that{a mathematical formula}Kn⊢⁎φand{a mathematical formula}φ∈n(r)‾
       </list-item>
       <list-item label="•">
        {a mathematical formula}∃φ∈Premp(β)or{a mathematical formula}∃β′∈Sub(β)of the form{a mathematical formula}β1″,…,βn″⇒φ, and{a mathematical formula}∃η,θsuch that{a mathematical formula}Kn∪{φ}⊢⁎η,{a mathematical formula}Kn∪{φ}⊢⁎θ, and{a mathematical formula}η∈θ‾.
       </list-item>
      </list>
      <paragraph>
       We have now to show that {a mathematical formula}RS−AF(AT) satisfies the requirements presented in Section 6. First of all it is singleton covering (Definition 31) by construction. Subargument awareness (Definition 32) and inclusion awareness (Definition 33) are proved easily.
      </paragraph>
      <paragraph label="Proposition 32">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is subargument aware.
      </paragraph>
      <paragraph label="Proposition 33">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is inclusion aware.
      </paragraph>
      <paragraph>
       We now prove the properties of fallible language inhibition coverage (Definition 34) and attack accuracy (Definition 35). This requires a preliminary lemma.
      </paragraph>
      <paragraph label="Lemma 17">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), if{a mathematical formula}(S,∅)∈EC(AS)then{a mathematical formula}∃S′⊆S,{a mathematical formula}S′≠∅, such that{a mathematical formula}(∅,S′)∈EC(AS).
      </paragraph>
      <paragraph label="Proposition 34">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is fallible language inhibition covering.
      </paragraph>
      <paragraph label="Proposition 35">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is attack accurate.
      </paragraph>
     </section>
     <section label="9.4">
      Dealing with multiple contradictories in {a mathematical formula}ASPIC+ revisited
      <paragraph>
       To illustrate the behavior of the revisited version of {a mathematical formula}ASPIC+ in the presence of multiple contradictories we consider in this section an example extending the basic problematic case introduced in Section 9.2.
      </paragraph>
      <paragraph>
       Consider language {a mathematical formula}L10=L6∪{HC,GC,FC,WR}, where intuitively HC means that the person we are speaking about has a birth certificate dated 16 years ago, GC represents the default assumption that the certificate is genuine, FC means that the certificate is fake, and WR means that the person wears a wedding ring. The contrariness relation is as in Section 9.2 with the only addition of {a mathematical formula}GC‾={FC}, i.e. FC is a contrary of GC. Let {a mathematical formula}RS={T→B;HC,GC→T} and {a mathematical formula}RD={WR⇒M} (including in particular the strict rule {a mathematical formula}T→B identified as problematic in Section 9.2). Suppose also that {a mathematical formula}Kn={HC,WR} (it is certain that the person has a birth certificate and wears a wedding ring) and {a mathematical formula}Kp={GC} (it is defeasibly assumed that the certificate is genuine).
      </paragraph>
      <paragraph>
       Starting from the extended contrariness relation as in Definition 75, from {a mathematical formula}RS we obtain {a mathematical formula}{T}⊢min⁎B, {a mathematical formula}{HC,GC}⊢min⁎T, {a mathematical formula}{HC,GC}⊢min⁎B. Applying Definition 75 and omitting {a mathematical formula}EC1(AS), we get {a mathematical formula}EC2(AS)=EC1(AS)∪{({T},{M}),({T},{D}), {a mathematical formula}({HC,GC},{A}), {a mathematical formula}({HC,GC},{O}), {a mathematical formula}({HC,GC},{M}), {a mathematical formula}({HC,GC},{D})} and then {a mathematical formula}EC3(AS)=EC2(AS)∪{({M},{T}),({D},{T}), {a mathematical formula}({A},{HC,GC}), {a mathematical formula}({O},{HC,GC}), {a mathematical formula}({M},{HC,GC}), {a mathematical formula}({D},{HC,GC})}.
      </paragraph>
      <paragraph>
       Then {a mathematical formula}EC(AS)=ECm(AS) is obtained by suppressing axioms and considering minimality leading to {a mathematical formula}EC(AS)=EC1(AS)∪{({T},{M}),({T},{D}), {a mathematical formula}({GC},{A}), {a mathematical formula}({GC},{O}), {a mathematical formula}({GC},{M}), {a mathematical formula}({GC},{D})}∪{({M},{T}),({D},{T}), {a mathematical formula}({A},{GC}), {a mathematical formula}({O},{GC}), {a mathematical formula}({M},{GC}), {a mathematical formula}({D},{GC})}.
      </paragraph>
      <paragraph>
       Turning to arguments and their attacks, it is easy to see that the following arguments can be built: {a mathematical formula}α1=HC, {a mathematical formula}α2=GC, {a mathematical formula}α3=WR, {a mathematical formula}α4=[α1,α2→T], {a mathematical formula}α5=[α4→B], {a mathematical formula}α6=[α3⇒M].
      </paragraph>
      <paragraph>
       From Definition 76 we have that {a mathematical formula}{α2}, {a mathematical formula}{α4} and {a mathematical formula}{α5} rebut {a mathematical formula}α6, and {a mathematical formula}{α6} undermines (and also rebuts) {a mathematical formula}α2 and its superarguments {a mathematical formula}α4 and {a mathematical formula}α5. All these attacks are preference dependent. To keep the presentation simple we assume that all fallible arguments (i.e. {a mathematical formula}α2,α4,α5,α6) are equally preferred and are less preferred than the infallible arguments {a mathematical formula}α1 and {a mathematical formula}α3. Under this assumption, all the above attacks are successful and give rise to minimal defeats according to Definition 78, i.e., summing up, {a mathematical formula}{α4}⇝α6, {a mathematical formula}{α5}⇝α6, {a mathematical formula}{α2}⇝α6, {a mathematical formula}{α6}⇝α2, {a mathematical formula}{α6}⇝α4, {a mathematical formula}{α6}⇝α5.
      </paragraph>
      <paragraph>
       Then, by Definition 83, {a mathematical formula}RS(AT)={{α1},{α2},{α3},{α4},{α5},{α6}} and by Definition 84 the D-attack relation ↠ corresponds to those defeat relations where the attacking argument is ultimately fallible (namely {a mathematical formula}α2 and {a mathematical formula}α6) leading to {a mathematical formula}‖{α2}‖↠‖{α6}‖, {a mathematical formula}‖{α6}‖↠‖{α2}‖, {a mathematical formula}‖{α6}‖↠‖{α4}‖, {a mathematical formula}‖{α6}‖↠‖{α5}‖.
      </paragraph>
      <paragraph>
       The corresponding argumentation framework is depicted in Fig. 16.
      </paragraph>
      <paragraph>
       Its complete extensions are {a mathematical formula}C1={‖{α1}‖,‖{α3}‖}, {a mathematical formula}C2={‖{α1}‖,‖{α3}‖,‖{α6}‖}, {a mathematical formula}C3={‖{α1}‖,‖{α2}‖,‖{α3}‖,‖{α4}‖,‖{α5}‖}.
      </paragraph>
      <paragraph>
       {a mathematical formula}C1 is the grounded extension supporting only the conclusions HC and WR. {a mathematical formula}C2 and {a mathematical formula}C3 correspond to the two alternative choices arising from the incompatibility between the fallible arguments {a mathematical formula}α2 (the certificate is genuine) and {a mathematical formula}α6 (the person is married) given that it is certain that s/he has a certificate asserting that s/he is a teenager and that there is no preference between the alternatives. Note that the structure of the AF evidences this mutual attack as the root of all the inconsistencies. In fact, the acceptance of the other arguments (apart the unattacked ones) basically depends on the choice between {a mathematical formula}‖{α2}‖ and {a mathematical formula}‖{α6}‖.
      </paragraph>
      <paragraph>
       As a variation of the example, assume that we add an ordinary premise FC since there is some evidence suggesting the falsity of the certificate. Then we get an additional argument {a mathematical formula}α7=FC which preference-independent attacks {a mathematical formula}α2 and its superarguments {a mathematical formula}α4 and {a mathematical formula}α5. Skipping some obvious steps we obtain a modified framework where, in particular, {a mathematical formula}‖{α7}‖↠‖{α2}‖ and, as expected, there is exactly one complete extension {a mathematical formula}C1′={‖{α1}‖,‖{α3}‖,‖{α6}‖,‖{α7}‖} corresponding to the unique surviving (but still defeasible) alternative.
      </paragraph>
     </section>
     <section label="9.5">
      {a mathematical formula}ASPIC+ revisited avoids peculiarities of closure under transposition
      <paragraph>
       Having seen that the revisited version of {a mathematical formula}ASPIC+ can handle properly the presence of multiple contradictories, we provide in this section additional evidence of its advantages by showing that it avoids some peculiar situations which may arise from the adoption of closure under transposition as a way to ensure the property of consistency, even in the basic case where the traditional notion of negation is used for contrariness.
      </paragraph>
      <paragraph>
       Consider a simple language {a mathematical formula}L={φ,ψ,χ,ω,¬φ,¬ψ,¬χ,¬ω,r1} with the contrariness function {a mathematical formula}¯ defined in the obvious way (i.e. φ and ¬φ are contradictory and similarly for the other elements, with the exception of {a mathematical formula}r1 which has no contraries).
      </paragraph>
      <paragraph>
       Assume that a single defeasible rule is given, namely {a mathematical formula}RD={⇒φ} with naming convention {a mathematical formula}n(⇒φ)=r1, and that the following set of strict rules is initially given: {a mathematical formula}RS={φ→ψ;φ→χ;ψ,χ→¬ω;→ω}.
      </paragraph>
      <paragraph>
       Considering the original version of {a mathematical formula}ASPIC+, by closure under transposition the following additional strict rules are derived: {a mathematical formula}RST={¬ψ→¬φ;¬χ→¬φ;ψ,ω→¬χ;χ,ω→¬ψ}.
      </paragraph>
      <paragraph>
       Given the argumentation system {a mathematical formula}AS=(L,¯,RD∪RS∪RST,n) and assuming an empty knowledge base, the following arguments are built from the theory {a mathematical formula}AT=(AS,∅):
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}α0:[→ω];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α1:[⇒φ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α2:[α1→ψ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α3:[α1→χ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α4:[α2,α3→¬ω];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α5:[α0,α2→¬χ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α6:[α5→¬φ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α7:[α0,α3→¬ψ];
       </list-item>
       <list-item label="•">
        {a mathematical formula}α8:[α7→¬φ].
       </list-item>
      </list>
      <paragraph>
       It follows that both {a mathematical formula}α6 and {a mathematical formula}α8 rebut (on {a mathematical formula}α1) all the arguments {a mathematical formula}α1,…,α8 (hence in particular they rebut themselves), while {a mathematical formula}α0 is not involved in any attack. Assuming again that all fallible arguments are equally preferred, these attacks are successful and it follows that the argumentation framework corresponding to this example (depicted in Fig. 17) has the following characteristics:
      </paragraph>
      <list>
       <list-item label="•">
        it does not admit any stable extension;
       </list-item>
       <list-item label="•">
        under any complete-based semantics (but stable) there is exactly one extension, namely {a mathematical formula}{α0}, while all arguments {a mathematical formula}α1,…,α8 are in an undecided state (they are not included in, nor attacked by, the extension {a mathematical formula}{α0}).
       </list-item>
      </list>
      <paragraph>
       Both facts are somehow unpleasant. As to the first point, the unability of stable semantics to draw any conclusion in this case is somehow surprising and one may wonder whether the semantics itself or the representation adopted is to blame. As to the second one, the fact that {a mathematical formula}α1 is undecided could be regarded as even more surprising: one might expect that it is rejected since it gives rise to a conflict with the infallible argument {a mathematical formula}α0. As a matter of fact, this fact may have undesired consequences: suppose that there is an additional defeasible argument {a mathematical formula}α9 with conclusion ¬φ. Then {a mathematical formula}α1 and {a mathematical formula}α9 mutually rebut and, in the case of adoption of grounded semantics, this would prevent {a mathematical formula}α9 to be accepted (the grounded extension would be {a mathematical formula}{α0}). Again one might wonder whether the semantics or the representation adopted is to blame.
      </paragraph>
      <paragraph>
       Using the revisited version of {a mathematical formula}ASPIC+ in this example avoids these problems. Consider the argumentation system {a mathematical formula}AS′=(L,¯,RD∪RS,n), where the rules derived by closure under transposition are not included, and the argumentation theory {a mathematical formula}AT′=(AS′,∅).
      </paragraph>
      <paragraph>
       First let us consider the extended contrariness relation. From Definition 75, taking into account {a mathematical formula}∅⊢min⁎ω, {a mathematical formula}{φ}⊢min⁎ψ, {a mathematical formula}{φ}⊢min⁎χ, {a mathematical formula}{ψ,χ}⊢min⁎¬ω, {a mathematical formula}{φ}⊢min⁎¬ω we get:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}EC1(AS)={({φ},{¬φ}),({¬φ},{φ}),({ψ},{¬ψ}),({¬ψ},{ψ}),({χ},{¬χ}),({¬χ},{χ}),({ω},{¬ω}),({¬ω},{ω})};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC2(AS)=EC1(AS)∪{(∅,{¬ω}),({φ},{¬ψ}),({φ},{¬χ}),({ψ,χ},{ω}),({φ},{ω})};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC3(AS)=EC2(AS)∪{({φ},∅),({¬ω},∅),({ψ,χ},∅),({ω},{φ}),(∅,{φ}),({¬ψ},{φ}),({¬χ},{φ}),({ω},{ψ,χ}),(∅,{ψ,χ})}.
       </list-item>
      </list>
      <paragraph>
       From the argumentation theory AT only the arguments {a mathematical formula}α0,…,α4 already considered before are generated.
      </paragraph>
      <paragraph>
       On the basis of Definition 76, Definition 77, Definition 78 we can observe that both the empty set of arguments and the set {a mathematical formula}{α0} rebut and then defeat the arguments {a mathematical formula}α1, {a mathematical formula}α2, {a mathematical formula}α3, {a mathematical formula}α4 on {a mathematical formula}α1. Of course, only the empty set of arguments minimally defeats these arguments and is a subset of the set of ultimately fallible arguments.
      </paragraph>
      <paragraph>
       Skipping some easy steps, on the basis of Definition 83, Definition 84, Definition 85 we get the argumentation framework {a mathematical formula}RS−AF(AT′)=({‖∅‖,‖{α0}‖,‖{α1}‖,‖{α2}‖,‖{α3}‖,‖{α4}‖},{(‖∅‖,‖{α1}‖),(‖∅‖,‖{α2}‖),(‖∅‖,‖{α3}‖),(‖∅‖,‖{α4}‖)}.
      </paragraph>
      <paragraph>
       It follows that according to all semantics considered in this paper {a mathematical formula}RS−AF(AT′) has a unique extension, namely {a mathematical formula}{‖∅‖,‖α0‖}, leading to acceptance of the argument {a mathematical formula}α0 only. Note also that in case an additional defeasible arguments {a mathematical formula}α9 with conclusion ¬φ were present, {a mathematical formula}‖α9‖ would be included also in the grounded extension (and {a mathematical formula}α9 accepted) because the only attacker of {a mathematical formula}‖{α9}‖, namely {a mathematical formula}‖{α1}‖, is rejected being attacked by {a mathematical formula}‖∅‖ and {a mathematical formula}‖{α0}‖.
      </paragraph>
      <paragraph>
       This shows that the problems evidenced in the approach based on transposition do not appear in our approach.
      </paragraph>
     </section>
    </section>
    <section label="10">
     <section-title>
      Discussion and related works
     </section-title>
     <paragraph>
      In this section we orderly review the main contents of Sections 3–9, discussing their relationships with the related literature.
     </paragraph>
     <section label="10.1">
      LAF-ensemble elements
      <paragraph>
       Starting from inhibition frameworks, the notion of an inhibition function can be regarded as a further step in the literature towards the generalization of the traditional notion of negation into a more general contrariness function. In the structured argumentation literature an asymmetric contrariness relation was considered as early as in the seminal paper on Assumption Based Argumentation (ABA) [16], where a subset of the considered language is identified as a set of assumptions and a contrariness function maps each assumption into a contrary belonging to the language. As explicitly stated in [17], the language needs not to be closed under classical negation and the simple contrariness relation recalled above is the only necessary element of the theory. While in ABA each assumption has exactly one contrary, in {a mathematical formula}ASPIC+, more generally, each language element may have more than one contrary, making this formalism capable of capturing as instances a large variety of other formalisms, including ABA itself, as discussed in [13]. Our proposal further extends the generality of the contrariness function of {a mathematical formula}ASPIC+ to the set level (the above cases being instances where all sets are singletons) as this provides the ability to capture cases of non-binary incompatibility. This is a key feature of the formalism, as evidenced, for instance, by the crucial role it plays in capturing Vreeswijk's abstract argument systems and in formulating a revised version of {a mathematical formula}ASPIC+ using an extended contrariness function. A set level contrariness function has also been considered in a generalized version of ABA [18] which will be discussed later in this section.
      </paragraph>
      <paragraph>
       While the inhibition function is meant to support a rich expressiveness, the notions of acceptance and consistency at the language level and of justification at the argument level are very simple, namely binary. The basic reason is that we assume that consistency is a crisp notion: a set of language elements is either consistent or not. As a consequence, even if one considers non-binary notions of acceptance at language level and of justification at the argument level, they would need to be converted into binary notions for the sake of consistency evaluation. Given that in argument-based reasoning, statement acceptance directly depends on argument acceptance, this amounts to require that the notion of argument justification is ‘binarized’ in the first place. For instance, in labeling-based semantics three labels are considered namely {an inline-figure}, {an inline-figure}, and {an inline-figure} but usually, as far as consistency evaluation is concerned (e.g. in [7]), only the conclusions of arguments labeled {an inline-figure} count, which implicitly amounts to equate {an inline-figure} to ⊤ and both {an inline-figure} and {an inline-figure} to ⊥ in this respect. Similarly, in works considering various kinds of numerical evaluation of arguments (e.g. [19], [20]) it is common to distinguish those arguments which are justified or believed, because their evaluation is above a given threshold, with respect to those which are below such a threshold. In this light, our approach does not prevent, but abstracts away, the possible use of more gradual notions of justification of argument, capturing only the fact that they are mapped into a binary notion, as far as the evaluation of the consistency of their conclusions is concerned. Generalizing our approach to the adoption of a non-binary notion of consistency is a very interesting (and substantial) direction of future work.
      </paragraph>
      <paragraph>
       Turning to the generic argumentation model encompassed by LAF-ensembles, its main elements are the conclusions and attackable elements associated to an argument, the subargument relation, and the incremental fallibility classification. Accordingly, this model lies at an intermediate abstraction level between structured argumentation formalisms, like Vreeswijk's AAS [9], {a mathematical formula}ASPIC+[13], [10], ABA [16], [17], DeLP [21], [22], and deductive argumentation [23], [24], which specify in more detail how arguments are built and how their properties (including defeasibility) are determined, and fully abstract{sup:13} argumentation formalisms, like Dung's argumentation frameworks, where the arguments' structure and properties are completely abstracted away and only their relationships of attack (and support in the case of bipolar frameworks) are represented. The intermediate level of abstraction of LAF-ensembles turns out to be useful to investigate properties of argumentation formalisms based on a notion of argument which is still general and largely detail-free but not completely void (as it is in Dung's framework). Indeed we have shown in Sections 8 and 9 the ability of LAF-ensembles to capture existing ‘less abstract’ formalisms and to provide a sort of guidance for their analysis and revision. Dung's framework, being ‘more abstract’, keeps its role in semantics-based evaluation (though with a revised set based interpretation of nodes) as presented in Section 6.
      </paragraph>
      <paragraph>
       Abstract Dialectical Frameworks (ADFs) [5], [25] are another example of a general abstract graph-based formalism, which is able in particular to capture Dung's AFs as a special case. Briefly, analogously to AFs, nodes in ADFs are structure-free entities, called statements, positions, or nodes, while the main difference with respect to AFs is that in ADFs links have no fixed meaning (attack in the case of AFs) but just express the existence of a dependency relation between a node and its parents in the graph. As such, ADFs belong to the class of ‘fully abstract’ argumentation formalisms and pertain to a different abstraction level with respect to LAF-ensembles, while it might be interesting to investigate, as a future work, their use as an alternative formal tool for the production of consistent argument justification functions, along the lines presented in Sections 6 and 7.
      </paragraph>
     </section>
     <section label="10.2">
      <section-title>
       Requirements on argument justification
      </section-title>
      <paragraph>
       Turning to the requirements introduced in Section 4, conclusion consistency of argument justification is a rather natural constraint, corresponding to the postulate of direct consistency introduced in [7] (where only classical negation is considered) and extended to generic contrariness functions in [10]. Extensive consistency includes in the consistency evaluation scope attackable elements, in addition to conclusions, thus making the requirement stricter. While this strengthening does not affect the possibility to prove useful results, as shown in Section 7, it can be observed that the explicit consideration of attackable elements in this respect is useful to point out and avoid some peculiar situations. Consider for instance a situation in {a mathematical formula}ASPIC+ where the name of a defeasible rule, say r, is a contrary of a language element φ, i.e. {a mathematical formula}n(r)∈φ‾. Technically{sup:14} this is not forbidden, but it can be remarked that this kind of contrariness, though expressible in the formalism, may not give rise to an attack. For instance, if r is the defeasible rule ⇒ψ, and letting ⇒φ be another defeasible rule, in {a mathematical formula}ASPIC+ the two arguments {a mathematical formula}α:⇒ψ and {a mathematical formula}β:⇒φ are not in conflict and can be accepted together. In this sense the contrariness of {a mathematical formula}n(r) (the name of the rule used for the construction of α) with respect to φ (the conclusion of β) would be ineffective and could be regarded as spurious or redundant. This also means that, when interpreted in terms of LAF-ensembles, {a mathematical formula}ASPIC+ is not extensively consistent. In the revisited version of {a mathematical formula}ASPIC+ no element of the contrariness function can be ineffective, since these spurious cases have been forbidden, based on the observation that they would have prevented the satisfaction of the extensive consistency property or otherwise imposed to introduce possibly bizarre additional forms of attack. This provides further evidence of the potential of LAF-ensembles as an analysis and ‘diagnostic’ tool for more specific formalisms.
      </paragraph>
      <paragraph>
       The requirement that justification is fully inhibition driven, though not having, to the best of our knowledge, a direct counterpart among the principles explicitly considered in the previous literature, is based on two general properties largely shared by the existing argumentation formalisms. The first property is that arguments not receiving attacks are justified. The underlying intuition is that the construction of an argument is by itself a reason to regard it as justified, and some explicit opposite reasons (corresponding to attacks) have to be present to regard the argument as not justified. This is also a special case of the principle of reinstatement [26] to which most argumentation semantics adhere: informally, it states that an argument must be justified if all its attackers are not justified, which is trivially true if there are no attackers at all. The second property is that the presence of an attack is motivated by some contrariness involving the structural elements (including subarguments) of the attacked and attacking arguments. The requirement that attacks are motivated is, in a sense, so obvious that it is respected by structured argumentation formalisms without being explicitly formulated, while the requirement cannot be expressed at the level of Dung's argumentation framework, where attack motivations, like all other structural properties, are abstracted away. Formulating this requirement explicitly is instead necessary in LAF-ensembles since they lie at an intermediate level of abstraction, where some structural elements are considered but the actual attack relations cannot be directly specified.
      </paragraph>
      <paragraph>
       The property that justification is incremental infallibility compatible (implying in particular that it is infallibility compatible) is related with the postulate of closure, introduced in [7], which essentially states that, for a structured rule-based argumentation formalism, the justified conclusions must coincide with the ones obtained after applying the closure with respect to strict rules. In LAF-ensembles the mechanism of argument construction is abstracted away and hence essentially the same idea is reformulated, in more abstract terms, with reference to infallible additions with respect to the justified arguments. Generally speaking, it can be seen that the postulate of closure at the structured level is implied by the property of being incremental infallibility compatible at the LAF-ensemble level. While the idea underlying closure with respect to strict rules and incremental infallibility compatibility is quite natural and is widely adopted, it must be acknowledged that it has not been regarded as unquestionable in the literature. For instance in a recent work by Prakken [27] a modified version of the postulate of closure is considered, restricted to the case where only one fallible argument is used as a basis for a strict derivation. Investigating variations of our approach corresponding to this kind of alternative postulates is an interesting direction of future work.
      </paragraph>
     </section>
     <section label="10.3">
      Assumptions on LAF-ensembles
      <paragraph>
       Let us now turn to the assumptions on LAF-ensembles introduced in Section 5. Infallibility consistency is a basic hypothesis obviously needed to avoid degenerate cases where inconsistency is unavoidable given that it follows from infallible reasoning. It corresponds directly to the property of axiom consistency of {a mathematical formula}ASPIC+ and to the fact that the base set is compatible in Vreeswijk's AASs. Considering other argumentation formalisms not extensively discussed in this paper, in DeLP it corresponds to the assumption that the set of facts and strict rules is non-contradictory [21], while in ABA it corresponds indirectly to the fact that only assumptions (which are the only fallible elements in this context) have contraries thus no contradiction may emerge, by construction, from the infallible reasoning part.
      </paragraph>
      <paragraph>
       {a mathematical formula}II-consonance implies infallibility consistency and can be regarded as a strengthening of the relevant intuition: while infallibility consistency focuses on entirely infallible arguments, {a mathematical formula}II-consonance considers also the ‘infallible sections’ inside arguments and imposes that the roots of the conflict can be traced back to their fallible frontiers (implying in particular that when the fallible frontiers are altogether empty no conflict can exist). To the best of our knowledge {a mathematical formula}II-consonance has no direct counterpart in properties explicitly expressed in the previous literature. It can be noted however that the idea of ‘tracing back’ the conflict is somehow and indirectly pursued through the property of closure under transposition in {a mathematical formula}ASPIC+, while in other approaches, like ABA, a similar property is enforced by construction given that, as already mentioned, only the fallible elements (assumptions) may have contraries.
      </paragraph>
     </section>
     <section label="10.4">
      <section-title>
       Set based argumentation frameworks
      </section-title>
      <paragraph>
       Set based argumentation frameworks, introduced in Section 6, are a key element of our approach. They are plain argumentation frameworks where the only difference with respect to the traditional uses of argumentation frameworks is the interpretation of nodes as sets of arguments instead of individual arguments, with straightforward consequences on the identification of justified arguments and conclusions. The underlying idea is that attacks generally occur at the set level, attacks between individual arguments being an instance (representable through singletons) of this more general case.
      </paragraph>
      <paragraph>
       Several variations of Dung's framework encompassing some notion of collective attack have been considered previously in the literature. Nielsen and Parsons [28] proposed an extension of Dung's framework where the attack relation goes from sets of arguments (with the exclusion of the empty set) to individual arguments. They redefined all traditional semantics notions in this extended setting, showing that all the relevant fundamental properties are preserved. The work was originally motivated by an application in the context of fusion of Bayesian networks [29] and this may explain some specific technical differences with respect to our approach. In particular in [28] only individual arguments can be the target of attacks and the empty set cannot be the source of any attack, while in our approach the relation of attack is generalized to every set of arguments and the role of attacks from the empty set is crucial. The main difference however consists in the fact that, from a technical point of view, we use Dung's framework as is, since it perfectly fits our purposes, rather than modifying it. This avoids the need of considering further related modifications and additional investigations (see for instance the discussion about the computation of preferred extensions in Nielsen and Parsons' formalism presented in [30]). Analyzing whether Nielsen and Parsons' formalism can be retrofitted, with some modifications, to the needs of the approach proposed in this paper (and then adopted as an alternative formal tool for the technical development presented in Sections 6 and 7) is an interesting theoretical question which may be considered for future work.
      </paragraph>
      <paragraph>
       In [31] an extension of Dung's framework especially devoted to capture evidential reasoning is introduced. It includes a so-called special argument η representing evidence, and considers both a relation of attack and of support between sets of arguments and individual arguments. As in the case of [28], the empty set cannot be the source of an attack. The main motivation of this work is to formalize a notion of evidential support of arguments and attacks and to adapt traditional Dung's semantics notions accordingly. Extending our approach to encompass some notion of support is another direction of future work.
      </paragraph>
      <paragraph>
       Joint attacks have been considered also by Gabbay [32] in the context of the problem of fibring argumentation frames, namely of replacing subnetworks of a complex argumentation network with single nodes and vice versa. This leads to a quite sophisticated development, also involving the notion of disjunctive attacks. Both joint and disjunctive attacks are reduced to a traditional Dung's framework representation using additional meta-arguments and a suitably defined attack relation. This kind of developments is orthogonal to our approach: the work presented in [32] considers arguments at a purely abstract level and adopts sophisticated technical tools to formalize some meta-level reasoning tasks about abstract argumentation networks, while in our approach we refer to arguments as structured entities and use argumentation frameworks as a tool to formalize argument-level reasoning activities.
      </paragraph>
      <paragraph>
       Some works concerning the relationships between argumentation and logic programming with negation as failure include intuitions which are closer to our approach. Briefly (see Section 4.3 of [3]), a logic program is a set of rules, regarded as infallible, where each rule derives a conclusion from a set of premises, some of which, namely the literals of the form ¬k expressing negation as failure, are explicitly identified as fallible assumptions. Each assumption is regarded as a fallible argument on its own, technically represented as a pair {a mathematical formula}({¬k},¬k). The notion of argument is then extended to the derivation of some conclusion obtained using rules and assumptions. The set of assumptions K used in the derivation of a given conclusion k is called support of k and the pair {a mathematical formula}(K,k) is regarded as an argument. Note that in this context an argument is infallible only if {a mathematical formula}K=∅ and that an assumption, in a sense, is regarded as a self-supporting argument.
      </paragraph>
      <paragraph>
       On this basis, two alternative perspectives on the notion of attack can be found in the literature.
      </paragraph>
      <paragraph>
       In Section 4.3 of [3] attack is defined as a binary relation between arguments: an argument α attacks an argument β if the conclusion of α asserts the contrary of one of the assumptions used by β. Formally an argument {a mathematical formula}(K,k) attacks another argument {a mathematical formula}(K′,k′) if ¬k belongs to {a mathematical formula}K′.
      </paragraph>
      <paragraph>
       In [33] instead attack is defined as a relation between sets of assumptions, based on the basic notion (Def. 2.1 of [33]) that a set of assumptions K attacks another set of assumption {a mathematical formula}K′ (on an assumption ¬k) if it is possible to derive k from K. This view can be regarded as sharing some basic intuitions with the approach presented in this paper: similarly to our case set level attacks involving the elements of the fallible frontier of arguments (which in this case coincides with the set of assumptions used) are identified. Clearly, there is a direct correspondence between the two perspectives, given that in this specific context each individual argument is essentially regarded as a set of assumptions plus some strict derivation from them. This suggests that also the original modeling proposed in [3] can be regarded, though indirectly, as a sort of instance of our approach.
      </paragraph>
      <paragraph>
       Assumption-based argumentation [16], [17] generalizes the ideas presented above by providing a more abstract framework which assumes the existence of a generic deductive system, not necessarily based on logic programming. Also in the context of ABA the two views mentioned above can be regarded as coexisting: in the original paper the relation of attack concerns sets of assumptions (Def. 3.1 of [16]) while in a recent tutorial paper [17] attack is defined as a binary relation between arguments but it is remarked that “attacks between arguments correspond in ABA to attacks between sets of assumptions”. On this basis it can be observed that, in this specific context, defining attacks at the level of individual arguments is not in contrast with defining attacks at the level of sets of (ultimately fallible) arguments, indeed the two options essentially coincide. The choice of focusing on the argument level in [3] and later in [17] can hence be regarded as motivated by presentation simplicity but is not enforced by deep technical reasons.
      </paragraph>
      <paragraph>
       It is then worth remarking that some works in the literature suggest that if one considers a more general setting, the two options are no more ‘interchangeable’ and defining attacks at the level of sets of arguments becomes the preferred choice, being more expressive.
      </paragraph>
      <paragraph>
       For instance in [18] a generalized form of assumption-based argumentation including the consideration of defeasible rules is proposed and its ability to satisfy the postulates proposed in [7] is verified. In this extended formalism, which assumes that the language adopted is closed with respect to the traditional notion of negation, a set based contrariness relation {a mathematical formula}C is considered formed by pairs {a mathematical formula}(X,Y) where both X and Y are non-empty sets of language elements and the set X (called retractible) contains at least an assumption. On this basis, a set of assumptions A attacks a set of assumptions B if there is some {a mathematical formula}(X,Y)∈C and some {a mathematical formula}φ∈X such that {a mathematical formula}φ∈B, every element of {a mathematical formula}X∖{φ} can be derived from some set of assumptions {a mathematical formula}B′⊆B and every element of Y can be derived from some set of assumptions {a mathematical formula}A′⊆A. Quoting [18]: “Intuitively, A and B together derive all elements of X and Y (and thus conflict), and B is to blame, by being responsible for deriving the elements of the culprits in X”. At a general level there are clearly some direct analogies between the intuitions underlying this proposal and our approach. There are however also some non-negligible technical differences. For instance in [18] the set based contrariness relation may not involve the empty set. This is backed by the somehow restrictive assumption that conflicts always involve defeasible rules on both sides, which we avoid (while we fully agree with and formally capture the remark in [18] that if some conclusion can be derived by strict rules only, it would be natural to adopt this conclusion instead of its defeasibly derived negation). Moreover in [18] no minimality requirement is considered in the derivations used to define the set based contrariness and this leads to impose some additional assumptions on the set of rules.
      </paragraph>
      <paragraph>
       Bochman has considered an extension of Dung's theory called collective argumentation[34] starting from the goal of representing semantics of disjunctive logic programs but with the more general aim of describing “reasoning situations in which the conflict between incompatible views or theories is global and cannot be reduced to particular claims made by these theories”. This intuition is also rather close to our approach and Bochman points out that to capture the semantics of disjunctive logic programs the ‘traditional’ view of attacks defined at the argument level is insufficient. Bochman then adopts an approach to the evaluation of argument acceptance which significantly departs from Dung's semantics, by using a four valued labeling of arguments inspired to Belnap's logic. Analyzing in more technical detail the relationships between this four valued evaluation and our approach appears to be another very interesting topic of future work.
      </paragraph>
     </section>
     <section label="10.5">
      <section-title>
       Postulate satisfaction
      </section-title>
      <paragraph>
       We have shown in Section 7 that the joint use of {a mathematical formula}II-consonant LAF-ensembles and appropriate set based argumentation frameworks ensures that the justification function induced by any complete-based argumentation semantics satisfies a comprehensive set of requirements. Starting from [7], several works have been devoted, mainly in the context of the ASPIC or {a mathematical formula}ASPIC+ formalism, to devise restrictions or assumptions on the use of the formalism itself able to ensure the satisfaction of the set of properties called rationality postulates in [7]. Given the similarity already discussed between our requirements and the rationality postulates, it is worth comparing our approach with these works.
      </paragraph>
      <paragraph>
       In [7] the satisfaction of the postulates in ASPIC is based on three basic elements: the assumption that the set of strict rules satisfies one among two forms of closure (either under classical entailment or under transposition), the assumption that the set of strict rules is consistent, and the adoption of the so-called restricted rebut, namely the fact that an argument can be rebutted only on a subargument whose top rule is defeasible.
      </paragraph>
      <paragraph>
       In {a mathematical formula}ASPIC+[10], as recalled in Section 9 a similar approach is adopted based on some form of closure of strict rules (under contraposition or under transposition), axiom consistency, an assumption on the arguments (being c-consistent) or on the strict rules (being c-classical), restricted rebut, and an assumption of well-formedness on axioms and strict rules, the last one being necessary due to the possible asymmetry of the contrariness relation, while in [7] only classical negation was considered.
      </paragraph>
      <paragraph>
       Both approaches consider an argumentation framework where nodes correspond to individual arguments and attacks correspond to the (restricted) rebut, undercut and undermining relationships between them.
      </paragraph>
      <paragraph>
       As discussed in Section 9, the idea of closure of the set of strict rules may run into troubles in the presence of a general contrariness relation and, in some cases, even when contrariness coincides with classical negation. To avoid this kind of problem, in our approach the idea of imposing closure with respect to strict reasoning is ‘transferred’ to the inhibition function. Apart from the technical advantages evidenced by the results obtained along the paper, the underlying intuition is that of making explicit the incompatibilities derivable from a given set of strict rules rather than adding new rules which ensure that such incompatibilities are detected at the level of conflicts between arguments. An instantiation of this idea is provided by the extended contrariness relation introduced in Section 9.3. Note that making these incompatibilities explicit is made possible by the adoption of a generic notion of inhibition function, which provides a flexible representation tool, while updating or closing the inhibition function is simply impossible if it is assumed to coincide with classical negation. This indicates that closure of the set of rules was a sort of ‘enforced’ choice in the approach proposed in [7] based on ASPIC, which has been subsequently directly extended to the {a mathematical formula}ASPIC+ generalization. Our proposal shows that considering an alternative form of closure, enabled by a possibly asymmetric inhibition function defined at the level of sets of language elements, can be both conceptually and technically fruitful. A direct consequence of set level inhibition is identifying conflicts among arguments at set level too and thus rethinking the interpretation and use of argumentation frameworks, while keeping unchanged the relevant semantics notions. As a side effect there are some gains in generality, in particular the notion of well-formedness has been relaxed.
      </paragraph>
      <paragraph>
       Another point deserving some comment is the notion of restricted rebut introduced in [7] for ASPIC and then adopted also in {a mathematical formula}ASPIC+ (without explicitly calling it restricted and applying implicitly the same restriction to undermining too, a form of attack not considered in [7]). Restricted rebut involves a sort of asymmetry: there is a restriction on the target of an attack (it is required that the attacked argument has a subargument whose top rule is defeasible) while there is no restriction on the source of the attack. This asymmetry is required to ensure the satisfaction of all rationality postulates by complete-based semantics, while if one adopts unrestricted rebut postulates are satisfied by the grounded semantics only, as shown in [7] for ASPIC and in [35] for a slightly restricted version of {a mathematical formula}ASPIC+, called {a mathematical formula}ASPIC−.
      </paragraph>
      <paragraph>
       Our approach (at set level) avoids this asymmetry because attacks are required to involve ultimately fallible arguments on both sides. As already mentioned, the underlying intuition is that the conflicts are necessarily caused by fallible reasoning and so it is both conceptually cleaner and technically advantageous to keep a full separation between conflicts and infallible reasoning, while, in a sense, this separation is only partially captured by restricted rebut. Again, achieving this full separation is not possible in contexts where inhibition is assumed to coincide with classical negation.
      </paragraph>
      <paragraph>
       Rationality postulates have also been investigated for the family of logic-based argumentation systems [36], [37]. A detailed analysis of the relationships between our proposal and this family of systems is left to future work.
      </paragraph>
     </section>
     <section label="10.6">
      <section-title>
       Capturing and revisiting existing formalisms
      </section-title>
      <paragraph>
       In Section 8 we have shown that Vreeswijk's Abstract Argument Systems formalism can be seen as an instance of the notion of LAF-ensemble, thus providing a Dung's based representation of the formalism and drawing correspondences between Dung's semantics and argument acceptance notions in Abstract Argument Systems. To the best of our knowledge this kind of bridge between the two formalisms had never been considered before in the literature.
      </paragraph>
      <paragraph>
       In Section 9 we have discussed some limitations of {a mathematical formula}ASPIC+ and proposed a revisited version of the formalism based on LAF-ensembles. The limitations of {a mathematical formula}ASPIC+ in the case of a generic contrariness relations and a preliminary proposal of revision of the formalism have been initially presented in a previous paper of ours [8]. The present paper, by introducing and analyzing the formalism of LAF-ensembles, provides a much more general and abstract approach with respect to the specific solution focused on {a mathematical formula}ASPIC+ considered in [8]. It is also worth remarking that the revisited version of {a mathematical formula}ASPIC+ presented in this paper can be regarded as an evolution of the one proposed in [8], since it shows some significant technical differences. In particular, in [8] the notion of rebut was closer to the original idea of restricted rebut, thus still showing the asymmetry discussed above between targets and sources of attacks, which has been overcome in the present paper.
      </paragraph>
      <paragraph>
       Dung and Thang [38] also provide a critical analysis of ASPIC-like formalisms and, somehow similarly to us, address the problem of defining an improved version. They observe that closure of strict rules under transposition or under contraposition is a sufficient but not necessary condition to satisfy the rationality postulates, thus ruling out all systems not satisfying one of the two forms of closure implies ruling out also some well-behaved systems. Further, they point out some peculiar behaviors following from either form of closure and, as a consequence, they aim at identifying a property which is weaker than both forms of closure while still ensuring the satisfaction of the postulates. To this purpose a semi-abstract model of argument-based reasoning is developed, whose main components are an abstract logic and a logic-associated argumentation framework. This semi-abstract model is similar in spirit to our notion of LAF-ensemble. However there are also several significant technical differences: it adopts a notion of contradiction which is inherently symmetric, it equips the considered language with a strict consequence relation, while we abstract away the actual form of both strict and defeasible inference, it has no explicit notion of attackable elements, and it uses an argumentation framework whose nodes correspond to individual arguments. In this context, it is shown that two properties called cohesiveness and compactness are sufficient to guarantee the satisfaction of the postulates of [7]. On this basis, it is shown that ASPIC-like systems using classical negation only and without preferences between arguments satisfy the postulates if they respect a property called self-contradiction, which is less restrictive than closure under contraposition and transposition. With our approach we have revisited the more general {a mathematical formula}ASPIC+ formalism with generic contrariness and preferences using requirements at the semi-abstract level only, together with some well-formedness conditions. A detailed analysis of the technical relationships between the semi-abstract model of [38] and LAF-ensembles is beyond the scope of the present paper and represents another promising direction of investigation.
      </paragraph>
      <paragraph>
       Other recent works [39], [40] deal with the analysis of some axiomatic properties for structured argumentation with preferences between arguments. This analysis is motivated by the fact that using some of the preference criteria considered in [10] leads in some cases to violate some basic intuitive requirements. In order to address this problem in a systematic way, some generic properties for ASPIC-like systems with classical negation are considered. Most of these properties, like credulous cumulativity, attack monotonicity, irrelevance of redundant defaults, context independence, link orientation concern the preservation of the existence of some attacks or of some justified beliefs after some modification to the knowledge base or to the arguments is applied, while other properties, like effective rebut and normal rebut, concern the relations between attacks and preferences over rules.
      </paragraph>
      <paragraph>
       Our results do not depend on the relationship between attacks and preferences, which is abstracted away in our approach, and do not involve any form of preservation property between different argumentation systems. The investigation of possible interaction between the properties we consider and the preservation properties of [39], [40] is left to future work.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <section label="A.1">
      Proofs of Section 3
      <paragraph label="Lemma 1">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS, for every argument α such that{a mathematical formula}FI(α)=Fit holds that{a mathematical formula}∃β∈Sub(α):FIβΔ(PSub(β))=F.
      </paragraph>
      <paragraph label="Proof">
       Suppose by contradiction that {a mathematical formula}∀β∈Sub(α){a mathematical formula}FIβΔ(PSub(β))=I. Then by point 5 of Definition 11 we get in particular {a mathematical formula}FIαΔ(Sub(α))=FIαΔ(PSub(α)). Moreover, for any argument β in {a mathematical formula}PSub(α) applying again point 5 of Definition 11 we get {a mathematical formula}FIαΔ(PSub(α))=FIαΔ((PSub(α)∖β)∪PSub(β)) and this reasoning can be repeated recursively until every subargument β of α such that {a mathematical formula}PSub(β)=∅ is reached. Thus, it holds that {a mathematical formula}FIαΔ(Sub(α))=FIαΔ(∅), which according to Definition 12 is equal to {a mathematical formula}FI(α). By the hypothesis, {a mathematical formula}FI(α)=F thus {a mathematical formula}FIαΔ(Sub(α))=F. However, this contradicts point 1 of Definition 11, which states that {a mathematical formula}FIαΔ(Sub(α))=I.  □
      </paragraph>
      <paragraph label="Proposition 1">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS, the overall argument classification{a mathematical formula}FIsatisfies the properties required byDefinition 10.
      </paragraph>
      <paragraph label="Proof">
       To see that {a mathematical formula}FI(α)=I implies {a mathematical formula}AE(α)=∅, consider that {a mathematical formula}FI(α)=FIαΔ(∅) by definition. By point 4 of Definition 11 we have then {a mathematical formula}AE(α)⊆AE(∅), thus {a mathematical formula}AE(α)=∅.Let us now prove that if {a mathematical formula}FI(α)=I then {a mathematical formula}∄β∈Sub(α):FI(β)=F. Suppose by contradiction that {a mathematical formula}∃β∈Sub(α):FI(β)=F. Then, by Lemma 1{a mathematical formula}∃β′∈Sub(α):FIβ′Δ(PSub(β′))=F, which by point 3 of Definition 11 (with {a mathematical formula}X=∅) entails that {a mathematical formula}FIαΔ(∅)=F. However, taking into account that {a mathematical formula}FI(α)=FIαΔ(∅), by the hypothesis {a mathematical formula}FIαΔ(∅)=I.  □
      </paragraph>
      <paragraph label="Proposition 2">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an argument{a mathematical formula}α∈Σwith incremental fallibility classification function{a mathematical formula}FIαΔ, there is a unique fallible block for α.
      </paragraph>
      <paragraph label="Proof">
       First, note that, according to point 1 of Definition 11, {a mathematical formula}FIαΔ(Sub(α))=I thus a fallible block always exists. Now, suppose by contradiction that {a mathematical formula}∃X,X′⊆Sub(α) such that both X and {a mathematical formula}X′ are subargument closed, {a mathematical formula}X≠X′, {a mathematical formula}FIαΔ(X)=I, {a mathematical formula}FIαΔ(X′)=I and {a mathematical formula}∄X″⊆Sub(α) such that {a mathematical formula}X″ is subargument closed, {a mathematical formula}FIαΔ(X″)=I, and {a mathematical formula}X″⊊X or {a mathematical formula}X″⊊X′. It follows that {a mathematical formula}X⊈X′, {a mathematical formula}X′⊈X. Without loss of generality consider an argument {a mathematical formula}β∈(X′∖X). Only two cases are possible:
      </paragraph>
      <list>
       <list-item label="•">
        β is ultimately fallible, but, in virtue of item 3 of Definition 11, this contradicts the fact that {a mathematical formula}FIαΔ(X)=I;
       </list-item>
       <list-item label="•">
        β is ultimately infallible. Then two subcases are possible:
       </list-item>
      </list>
      <paragraph label="Lemma 2">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS, for every argument α such that{a mathematical formula}FI(α)=Iit holds that{a mathematical formula}∀X⊆Sub(α){a mathematical formula}FIαΔ(X)=I.
      </paragraph>
      <paragraph label="Proof">
       By definition of associated argument fallibility classification {a mathematical formula}FIαΔ(∅)=I. By item 3 of Definition 11, {a mathematical formula}∀β∈Sub(α){a mathematical formula}FIβΔ(PSub(β))=I. As a consequence, {a mathematical formula}∀X⊆Sub(α) an iterative application of point 5 of Definition 11 to the finite set X yields {a mathematical formula}FIαΔ(X)=FIαΔ(∅)=I.  □
      </paragraph>
      <paragraph label="Proposition 3">
       Given a subargument structure{a mathematical formula}SS=〈Σ,⊑〉and an incremental fallibility classification{a mathematical formula}FI⁎Δover SS
      </paragraph>
      <list>
       <list-item label="•">
        for an argument α,{a mathematical formula}FK(α)=FF(α)=∅iff α is an infallible argument;
       </list-item>
       <list-item label="•">
        {a mathematical formula}FK(α)=Sub(α)and{a mathematical formula}FF(α)={α}iff α is ultimately fallible;
       </list-item>
       <list-item label="•">
        every argument{a mathematical formula}β∈FF(α)is ultimately fallible.
       </list-item>
      </list>
      <paragraph label="Proof">
       As to the first point, suppose first that {a mathematical formula}FK(α)=∅: by definition of fallible kernel, it holds that {a mathematical formula}FIαΔ(∅)=I, i.e. {a mathematical formula}FI(α)=I. As to the reverse part of the proof, by Lemma 2 every non-empty set {a mathematical formula}X⊆Sub(α) cannot be a fallible block (since it would violate minimality), while ∅ is the unique fallible block of α.As to the second point, if {a mathematical formula}FK(α)=Sub(α) then according to the definition of fallible block it must in particular be the case that {a mathematical formula}FIαΔ(PSub(α))=F, i.e. α is ultimately fallible. On the other hand, assuming that α is ultimately fallible, i.e. {a mathematical formula}FIαΔ(PSub(α))=F, since {a mathematical formula}FIαΔ(Sub(α))=I by point 1 of Definition 11 and {a mathematical formula}Sub(α) is minimal by point 3 of Definition 11, one is led to conclude that {a mathematical formula}FK(α)=Sub(α). This obviously entails that {a mathematical formula}FF(α)={α} by the antisymmetry of the subargument relation.As to the third point, assume by contradiction that there is an argument {a mathematical formula}β∈FF(α) which is ultimately infallible. Then, by point 5 of Definition 11 it holds that {a mathematical formula}FIαΔ(FF(α))=FIαΔ((FF(α)∖{β})∪PSub(β))=FIαΔ(FF(α)∖{β}), where the last equality holds since {a mathematical formula}FF(α) is subargument closed. However, this contradicts the definition of fallible block, since {a mathematical formula}FIαΔ(FF(α)∖{β})=I and {a mathematical formula}FF(α)∖{β}⊊FF(α).  □
      </paragraph>
     </section>
     <section label="A.2">
      Proofs of Section 4
      <paragraph label="Proposition 4">
       Given aLAF-ensemble {a mathematical formula}LE=〈IF,SS,FI⁎Δ〉, if a justification function{a mathematical formula}JUSon SS is incremental infallibility compatible then it is also infallibility compatible.
      </paragraph>
      <paragraph label="Proof">
       Consider an argument {a mathematical formula}α∈Infall(Σ). Since by definition {a mathematical formula}FI(α)=FIαΔ(∅), it holds that {a mathematical formula}FIαΔ(∅)=I. Then, the set {a mathematical formula}X=∅ satisfies the conditions of Definition 24 (in particular, the condition that all of its arguments are justified is trivially satisfied), thus by incremental infallibility compatibility it must be the case that {a mathematical formula}JUS(α)=⊤.  □
      </paragraph>
     </section>
     <section label="A.3">
      Proofs of Section 5
      <paragraph label="Proposition 5">
       An{a mathematical formula}II-consonantLAF-ensemble is infallibility consistent.
      </paragraph>
      <paragraph label="Proof">
       Assume by contradiction that {a mathematical formula}∃S,T⊆Conc(Infall(Σ)) such that {a mathematical formula}S∈INH(T). Then {a mathematical formula}∃X,Y⊆Infall(Σ) satisfying the hypotheses stated in Definition 27, and from {a mathematical formula}FF(X)=FF(Y)=∅ (see Proposition 3) and {a mathematical formula}II-consonance it follows that {a mathematical formula}∅∈INH(∅) which is impossible by Definition 4.  □
      </paragraph>
     </section>
     <section label="A.4">
      Proofs of Section 7
      <paragraph label="Lemma 3">
       Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, a complete extension{a mathematical formula}Cof{a mathematical formula}FLE, and a set of arguments X, if{a mathematical formula}‖X‖∈Cthen{a mathematical formula}∀α∈X{a mathematical formula}‖{α}‖∈C.
      </paragraph>
      <paragraph label="Proof">
       First, since LE is singleton covering (Definition 31) {a mathematical formula}‖{α}‖∈AA, i.e. {a mathematical formula}‖{α}‖ is a node of LE. Now, by the property of inclusion awareness (Definition 33) every attacker of {a mathematical formula}‖{α}‖ in {a mathematical formula}FLE is also an attacker of {a mathematical formula}‖X‖, i.e. {a mathematical formula}‖{α}‖−⊆‖X‖−. By the properties of complete semantics, since {a mathematical formula}‖X‖∈C, we get that {a mathematical formula}‖{α}‖−⊆‖X‖−⊆C+. Hence {a mathematical formula}C defends {a mathematical formula}‖{α}‖. Since {a mathematical formula}C is a complete extension, {a mathematical formula}‖{α}‖∈C.  □
      </paragraph>
      <paragraph label="Lemma 4">
       Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, a complete extension{a mathematical formula}Cof{a mathematical formula}FLE, two sets of arguments X, Y, if{a mathematical formula}‖X‖∈C,{a mathematical formula}‖Y‖∈Cand{a mathematical formula}‖X∪Y‖∈AAthen{a mathematical formula}‖X∪Y‖∈C.
      </paragraph>
      <paragraph label="Proof">
       The property is obviously satisfied if {a mathematical formula}X=Y=∅. Consider now the case {a mathematical formula}X∪Y≠∅ and {a mathematical formula}‖X∪Y‖∈AA. If {a mathematical formula}‖X∪Y‖−=∅ then by definition of complete extension it is obvious that {a mathematical formula}‖X∪Y‖∈C. Suppose {a mathematical formula}‖X∪Y‖−≠∅. If {a mathematical formula}X∪Y is not a singleton, by the property of attack accuracy (Definition 35, third item), for every attacker {a mathematical formula}‖W‖ of {a mathematical formula}‖X∪Y‖ it must be the case that {a mathematical formula}∃β∈X∪Y such that {a mathematical formula}‖W‖↠‖{β}‖. Otherwise {a mathematical formula}X∪Y={α} and of course {a mathematical formula}∃β=α∈X∪Y such that {a mathematical formula}‖W‖↠‖{β}‖. Now, by Lemma 3, {a mathematical formula}∀β∈(X∪Y) it holds that {a mathematical formula}‖{β}‖∈C. Since {a mathematical formula}C is a complete extension, {a mathematical formula}C defends {a mathematical formula}‖{β}‖. It follows that {a mathematical formula}‖X∪Y‖−⊆C+ i.e. {a mathematical formula}C defends {a mathematical formula}‖X∪Y‖. Since {a mathematical formula}‖X∪Y‖∈AA and {a mathematical formula}C is a complete extension, {a mathematical formula}‖X∪Y‖∈C.  □
      </paragraph>
      <paragraph label="Proposition 6">
       Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis subargument coherent, i.e. for every argument α if{a mathematical formula}JUSC(α)=⊤then{a mathematical formula}∀β∈Sub(α)it holds that{a mathematical formula}JUSC(β)=⊤.
      </paragraph>
      <paragraph label="Proof">
       Taking into account Definition 29 and Lemma 3 we can prove that {a mathematical formula}‖{α}‖∈C implies that {a mathematical formula}‖{β}‖∈C when {a mathematical formula}β⊑α. First note that {a mathematical formula}‖{β}‖ is a node of LE, since the latter is singleton covering. By the property of subargument awareness (Definition 32) every attacker of {a mathematical formula}‖{β}‖ in {a mathematical formula}FLE is also an attacker of {a mathematical formula}‖{α}‖, i.e. {a mathematical formula}‖{β}‖−⊆‖{α}‖−. By the properties of complete semantics, since {a mathematical formula}‖{α}‖∈C, we get that {a mathematical formula}‖{β}‖−⊆‖{α}‖−⊆C+. Hence {a mathematical formula}C defends {a mathematical formula}‖{β}‖ and by the definition of complete extension {a mathematical formula}‖{β}‖∈C.  □
      </paragraph>
      <paragraph label="Proposition 7">
       Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis fully inhibition driven.
      </paragraph>
      <paragraph label="Proof">
       According to Definition 22 we have to show that, given any argument α, {a mathematical formula}JUSC(α)=⊥ implies that {a mathematical formula}∃X,Y⊆Σ, {a mathematical formula}∃β∈Sub(α)∩Y, such that {a mathematical formula}∃S⊆(Conc(X)∪AE(X)), {a mathematical formula}∃T⊆(Conc(Y)∪AE(Y)):S∈INH(T) and {a mathematical formula}T∩({Conc(β)∪AE(β)})≠∅.First, {a mathematical formula}JUSC(α)=⊥ implies by definition of induced justification function that {a mathematical formula}∄‖X‖∈C such that {a mathematical formula}α∈X, thus in particular {a mathematical formula}‖{α}‖∉C. Given that {a mathematical formula}FLE is singleton covering (Definition 31) by the properties of complete semantics it must then be the case that {a mathematical formula}‖{α}‖−≠∅.We prove that there is an argument {a mathematical formula}β∈Sub(α) for which item 1 of Definition 35 holds. Suppose to the contrary that this is not the case: given the property of attack accuracy, item 2 of Definition 35 holds for α, i.e. {a mathematical formula}∃γ∈PSub(α) such that {a mathematical formula}‖W‖↠‖{γ}‖. But then, item 2 holds for γ and there must be {a mathematical formula}γ′∈PSub(γ) such that {a mathematical formula}‖W‖↠‖{γ′}‖ and so on. Given the finiteness of {a mathematical formula}PSub(α) this reasoning can only be iterated a finite number of times: hence it must exists {a mathematical formula}γ⁎⊏…γ′⊏γ⊏α such that item 1 of Definition 35 applies to {a mathematical formula}γ⁎, getting a contradiction.Now, since item 1 of Definition 35 holds for {a mathematical formula}β∈Sub(α), we have that {a mathematical formula}∃X,Y⊆Σ with {a mathematical formula}β∈Y, {a mathematical formula}∃S⊆(Conc(X)∪AE(X)), {a mathematical formula}∃T⊆(Conc(Y)∪AE(Y)):S∈INH(T) and to comply with Definition 22 it has only to be proved that {a mathematical formula}T∩({Conc(β)}∪AE(β))≠∅. This is achieved by contradiction: from {a mathematical formula}T∩({Conc(β)}∪AE(β))=∅ it would follow {a mathematical formula}T⊆(Conc(Y∖{β})∪AE(Y∖{β})) contradicting condition (iii) of item 1 of Definition 35 that {a mathematical formula}∀Y′⊊Y{a mathematical formula}T⊈Conc(Y′)∪AE(Y′).  □
      </paragraph>
      <paragraph label="Proposition 8">
       Given a LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis incremental infallibility compatible.
      </paragraph>
      <paragraph label="Proof">
       According to Definition 24 and taking into account Lemma 3, we can prove that whenever {a mathematical formula}∃α∈Σ, {a mathematical formula}∃X⊆Sub(α) such that {a mathematical formula}∀β∈X{a mathematical formula}‖{β}‖∈C and {a mathematical formula}FIαΔ(X)=I then {a mathematical formula}‖{α}‖∈C. This is obvious for the case {a mathematical formula}X=Sub(α) thus we can focus on the case {a mathematical formula}X⊊Sub(α) which implies {a mathematical formula}α∈UI(Σ). According to the definition of complete extension, to prove that {a mathematical formula}‖{α}‖∈C we have to show that {a mathematical formula}C defends {a mathematical formula}‖{α}‖. This obviously holds if {a mathematical formula}‖{α}‖ has no attackers, therefore we assume {a mathematical formula}‖{α}‖−≠∅.Let us consider an attacker {a mathematical formula}‖Z‖ of {a mathematical formula}‖{α}‖. We first prove that there is a proper subargument β of α such that {a mathematical formula}‖Z‖∈‖{β}‖− and such that item 1 of Definition 35 holds for the attack from {a mathematical formula}‖Z‖ to {a mathematical formula}‖{β}‖. As in the previous proof, suppose this were not the case. Then, given the property of attack accuracy, item 2 of Definition 35 requires that {a mathematical formula}‖Z‖∈‖{γ}‖− for some proper subargument γ of α. Iterating the same reasoning step on γ we would derive an impossible infinite sequence of distinct ultimately infallible proper subarguments of α, leading to a contradiction.Let us then consider such argument β. Since item 1 of Definition 35 applies, {a mathematical formula}β∈UF(Σ). Then, since {a mathematical formula}FIαΔ(X)=I, it must be the case that {a mathematical formula}∃γ∈X such that {a mathematical formula}β⊑γ. In fact, letting {a mathematical formula}X′=⋃δ∈XSub(δ), if {a mathematical formula}∄γ∈X such that {a mathematical formula}β⊑γ it would be the case that {a mathematical formula}β∉X′ and from item 3 of Definition 11 we would get {a mathematical formula}FIαΔ(X′)=F contradicting the fact (item 2 of Definition 11) that {a mathematical formula}FIαΔ(X′)=FIαΔ(X)=I. By hypothesis, from {a mathematical formula}γ∈X we get {a mathematical formula}‖{γ}‖∈C and, by subargument awareness, {a mathematical formula}‖Z‖∈‖{γ}‖−. Then it must be the case that {a mathematical formula}C defends {a mathematical formula}‖{γ}‖, and hence also {a mathematical formula}‖{α}‖, against {a mathematical formula}‖Z‖.  □
      </paragraph>
      <paragraph label="Proposition 9">
       Given an{a mathematical formula}II-consonant LAF-ensemble LE, an argumentation framework{a mathematical formula}FLEappropriate for LE, and a complete extension{a mathematical formula}Cof{a mathematical formula}FLE,{a mathematical formula}JUSCis extensively consistent.
      </paragraph>
      <paragraph label="Proof">
       On the basis, in particular, of Definition 29, Definition 21 we have to prove that letting {a mathematical formula}Y=⋃‖X‖∈CX it holds that the set {a mathematical formula}S=⋃α∈Y({Conc(α)}∪AE(α)) is consistent, i.e. that {a mathematical formula}∄T,U⊆S such that {a mathematical formula}T∈INH(U). In virtue of Lemma 3 it holds that {a mathematical formula}Y={α∈Σ|‖{α}‖∈C}. Suppose now, for the sake of contradiction, that {a mathematical formula}∃T,U⊆S such that {a mathematical formula}T∈INH(U) (note that, in virtue of Definition 4, it cannot be the case that {a mathematical formula}T=U=∅). Since {a mathematical formula}T,U⊆S, it follows that {a mathematical formula}∃W,Z⊆Y such that {a mathematical formula}T⊆Conc(W)∪AE(W) and {a mathematical formula}U⊆Conc(Z)∪AE(Z). From the property of {a mathematical formula}II-consonance (Definition 27) it follows that {a mathematical formula}∃T′⊆Conc(FF(W))∪AE(FF(W)), {a mathematical formula}∃U′⊆Conc(FF(Z))∪AE(FF(Z)), such that {a mathematical formula}T′∈INH(U′).Then {a mathematical formula}T′, {a mathematical formula}U′, {a mathematical formula}FF(W), and {a mathematical formula}FF(Z) satisfy the conditions stated in Definition 34, hence it must hold that {a mathematical formula}∃β∈FF(W)∪FF(Z),∃K⊆FF(W)∪FF(Z):‖K‖↠‖{β}‖. Now, since {a mathematical formula}β⊑α for some argument α such that {a mathematical formula}‖{α}‖∈C, from Proposition 6 we get {a mathematical formula}‖{β}‖∈C. Similarly, by definition of fallible frontier each element γ of {a mathematical formula}FF(W) and {a mathematical formula}FF(Z) is a subargument of some α such that {a mathematical formula}‖{α}‖∈C, thus {a mathematical formula}‖{γ}‖∈C. Given that {a mathematical formula}K⊆FF(W)∪FF(Z), by Lemma 4 also {a mathematical formula}‖K‖∈C contradicting the conflict freeness of {a mathematical formula}C.  □
      </paragraph>
     </section>
     <section label="A.5">
      Proofs of Section 8
      <paragraph label="Lemma 5">
       If X is a minimal defeater of α then either{a mathematical formula}Conc(X∪{α})or{a mathematical formula}Conc(X)is minimally incompatible.
      </paragraph>
      <paragraph label="Proof">
       From the hypothesis that X is a defeater, according to Definition 48 and Definition 46, we have that {a mathematical formula}Conc(X∪{α}) is incompatible and {a mathematical formula}∀β∈X{a mathematical formula}β≮α. From the hypothesis that X is a minimal defeater it follows that {a mathematical formula}∀X′⊊X{a mathematical formula}X′ is not a defeater. Clearly, also for {a mathematical formula}X′ it holds that {a mathematical formula}∀β∈X′{a mathematical formula}β≮α hence it must be the case that {a mathematical formula}Conc(X′∪{α}) is not incompatible. It follows in particular that {a mathematical formula}Conc(X′∪{α})⊊Conc(X∪{α}) and {a mathematical formula}∄β,γ∈X∪{α} such that {a mathematical formula}β≠γ and {a mathematical formula}Conc(β)=Conc(γ). Now for every set {a mathematical formula}S⊊Conc(X∪{α}) such that {a mathematical formula}Conc(α)∈S there is a set of arguments {a mathematical formula}X′⊊X such that {a mathematical formula}S⊆Conc(X′∪{α}), hence S is not incompatible. Also, for every set {a mathematical formula}S⊊Conc(X) there is a set of arguments {a mathematical formula}X′⊊X such that {a mathematical formula}S⊆Conc(X′∪{α}), hence S is not incompatible. The only strict subset of {a mathematical formula}Conc(X∪{α}) not covered by this analysis is {a mathematical formula}Conc(X) and, from above, it is easy to see that if {a mathematical formula}Conc(X) is incompatible then it is minimally incompatible. Otherwise, it follows that {a mathematical formula}Conc(X∪{α}) is minimally incompatible.  □
      </paragraph>
      <paragraph label="Lemma 6">
       The empty set is a minimal defeater of an argument α iff{a mathematical formula}Conc(α)is incompatible. Moreover if{a mathematical formula}Conc(α)is incompatible then{a mathematical formula}{α}is a minimal defeater of every argument β such that{a mathematical formula}β≤αand{a mathematical formula}Conc(β)is not incompatible.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}Conc(α) is incompatible clearly {a mathematical formula}Conc(∅∪{α}) is incompatible and it trivially holds that {a mathematical formula}∀β∈∅{a mathematical formula}β≮α. Hence ∅ is a, obviously minimal, defeater of α. Conversely if ∅ is a, obviously minimal, defeater of α, it must be the case that {a mathematical formula}Conc(∅∪{α})=Conc(α) is incompatible. Further, for every argument β it holds that {a mathematical formula}Conc({α}∪{β}) is incompatible and if {a mathematical formula}β≤α it follows that {a mathematical formula}{α} is a defeater of β. Clearly {a mathematical formula}{α} is a minimal defeater if ∅ is not a defeater of β, i.e., as just proved, if {a mathematical formula}Conc(β) is not incompatible.  □
      </paragraph>
      <paragraph label="Proposition 15">
       Given an AAS, for every argument α the set{a mathematical formula}Sub(α)is finite.
      </paragraph>
      <paragraph label="Proof">
       The proof is by induction on the length of α. If {a mathematical formula}Len(α)=1α is atomic and {a mathematical formula}|Sub(α)|=|{α}|=1. Let {a mathematical formula}Len(α)=n&gt;1, then α has the form {a mathematical formula}α1,…,αn→(⇒)φ where {a mathematical formula}α1,…,αn is a finite, possibly empty, sequence of arguments such that {a mathematical formula}∀αi, {a mathematical formula}i=1,…,n{a mathematical formula}Len(αi)&lt;n and {a mathematical formula}Sub(α)=⋃i=1nSub(αi)∪{α}. It follows that {a mathematical formula}|Sub(α)|≤1+∑1n|Sub(αi)| which is finite given that n is finite and each term {a mathematical formula}|Sub(αi)| is finite by the induction hypothesis.  □
      </paragraph>
      <paragraph label="Proposition 16">
       Given an AAS, for every argument α the function{a mathematical formula}FIαΔintroduced inDefinition 54satisfies the requirements ofDefinition 11.
      </paragraph>
      <paragraph label="Proof">
       We orderly consider the list of properties:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(Sub(α))=I;In this case {a mathematical formula}X=Sub(α) hence {a mathematical formula}Sub(α)∖X=∅ and it trivially holds that for all the arguments in the empty set the condition stated in Definition 54 is satisfied, hence {a mathematical formula}FIαΔ(Sub(α))=I.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(X)=FIαΔ(⋃β∈XSub(β));The property obviously holds if X is subargument closed, i.e. {a mathematical formula}X=⋃β∈XSub(β). Suppose now that X is not subargument closed i.e. {a mathematical formula}∃γ,δ:γ∈X,δ∉X,δ⊏γ. Referring to Definition 54, it holds that {a mathematical formula}δ∈Sub(α)∖X but, since {a mathematical formula}∃γ∈X:δ⊑γ, δ does not affect the value assigned to {a mathematical formula}FIαΔ(X). It follows that {a mathematical formula}FIαΔ(X)=FIαΔ(X∪{δ}). Iterating the same reasoning on every such argument δ we get the desired conclusion.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}∀α∈Σ, if {a mathematical formula}X⊊Sub(α) is subargument closed and {a mathematical formula}∃β∈(Sub(α)∖X), such that {a mathematical formula}FIβΔ(PSub(β))=F then {a mathematical formula}FIαΔ(X)=F;From {a mathematical formula}FIβΔ(PSub(β))=F it follows that the top rule of β is defeasible. Given that {a mathematical formula}β∈Sub(α)∖X and that X is subargument closed it follows that {a mathematical formula}∄γ∈X:β⊑γ then given that the top rule of β is defeasible from Definition 54 we get {a mathematical formula}FIαΔ(X)=F.
       </list-item>
       <list-item label="4.">
        if {a mathematical formula}FIαΔ(X)=I then {a mathematical formula}AE(α)⊆AE(X);Trivial since for every argument α and every set of arguments X{a mathematical formula}AE(α)=AE(X)=∅.
       </list-item>
       <list-item label="5.">
        if {a mathematical formula}FIαΔ(PSub(α))=I then for every argument β such that {a mathematical formula}α∈Sub(β) for every set X such that {a mathematical formula}X⊆Sub(β) and {a mathematical formula}α∈X it holds that {a mathematical formula}FIβΔ(X)=FIβΔ((X∖{α})∪PSub(α)).From {a mathematical formula}FIαΔ(PSub(α))=I we get that α is atomic or the top rule of α is strict. Now considering an argument β such that {a mathematical formula}α∈Sub(β) and a set X such that {a mathematical formula}X⊆Sub(β) and {a mathematical formula}α∈X, letting {a mathematical formula}W={γ∈(Sub(β)∖X)|∄δ∈X:γ⊑δ} and {a mathematical formula}W′={γ∈(Sub(β)∖(X∪PSub(α)))|∄δ∈X:γ⊑δ}, it is easy to see that {a mathematical formula}W=W′. Given that α is atomic or the top rule of α is strict, we get that all arguments in W satisfy the condition of Definition 54 if and only if all arguments in {a mathematical formula}W′∪{α} satisfy it. It follows that {a mathematical formula}FIβΔ(X)=FIβΔ((X∖{α})∪PSub(α)). □
       </list-item>
      </list>
      <paragraph label="Proposition 17">
       Given an AAS with language{a mathematical formula}Land a base set S, the LAF-ensemble corresponding to S is{a mathematical formula}II-consonant.
      </paragraph>
      <paragraph label="Proof">
       Assume that {a mathematical formula}∃T,U⊆L, {a mathematical formula}∃X,Y⊆Σ such that {a mathematical formula}T∈INH(U), {a mathematical formula}T⊆Conc(X)∪AE(X) and {a mathematical formula}U⊆Conc(Y)∪AE(Y). We need to show that {a mathematical formula}∃T′⊆Conc(FF(X))∪AE(FF(X)), {a mathematical formula}∃U′⊆Conc(FF(Y))∪AE(FF(Y)), such that {a mathematical formula}T′∈INH(U′). Taking into account Definition 55 it must be the case {a mathematical formula}INH(U)={∅} and {a mathematical formula}∃S′⊆S such that {a mathematical formula}U∪S′ is minimally incompatible. Moreover since {a mathematical formula}AE(Y)=∅{a mathematical formula}U⊆Conc(Y), therefore {a mathematical formula}Conc(Y)∪S′ is incompatible and also {a mathematical formula}Conc(FF(Y))∪S′ is incompatible. Therefore {a mathematical formula}∃V⊆Conc(FF(Y))∪S′ which is minimally incompatible. According to Definition 55{a mathematical formula}{∅}=INH(V∖S). Letting {a mathematical formula}U′=V∖S we get {a mathematical formula}U′⊆Conc(FF(Y)), {a mathematical formula}{∅}=INH(U′) and of course {a mathematical formula}∅⊆Conc(FF(X)). Putting {a mathematical formula}T′=∅ the conclusion follows.  □
      </paragraph>
      <paragraph label="Lemma 7">
       For every argument α it cannot be the case that{a mathematical formula}{α}is a genuine defeater of α.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}{α} be a genuine defeater of α. Then {a mathematical formula}∃T⊆S such that {a mathematical formula}T∪{α} is a primitive defeater of α (note that {a mathematical formula}α∉S). Then {a mathematical formula}T∪Conc({α})∪{Conc(α)} is incompatible, i.e. {a mathematical formula}T∪{Conc(α)} is incompatible, but then, taking into account the fourth condition of Definition 42, it follows that T is a defeater of α contradicting the fact that {a mathematical formula}T∪{α} is a primitive (hence minimal) defeater of α.  □
      </paragraph>
      <paragraph label="Proposition 18">
       Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is subargument aware.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}‖X‖↠‖{α}‖ then {a mathematical formula}∃β∈UF(Sub(α)) s.t. X is a genuine defeater of β. For every argument γ such that {a mathematical formula}α⊑γ it also holds that {a mathematical formula}β⊑γ, hence {a mathematical formula}β∈UF(Sub(γ)) and {a mathematical formula}‖X‖↠‖{γ}‖.  □
      </paragraph>
      <paragraph label="Proposition 19">
       Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is inclusion aware.
      </paragraph>
      <paragraph label="Proof">
       If {a mathematical formula}‖X‖↠‖Y‖ then {a mathematical formula}∃α∈Y and {a mathematical formula}∃β∈UF(Sub(α)) s.t. X is a genuine defeater of β. Suppose {a mathematical formula}Y⊆W. Then {a mathematical formula}α∈W and the above condition holds for W too. It follows that {a mathematical formula}‖X‖↠‖W‖.  □
      </paragraph>
      <paragraph label="Proposition 20">
       Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is fallible language inhibition covering.
      </paragraph>
      <paragraph label="Proof">
       Given that the arguments of LE have no attackable elements and that, according to Definition 55, the only possible inhibitor of a set T is the empty set, we prove the following condition which entails the requirements of Definition 34: whenever {a mathematical formula}∃T⊆L:{∅}=INH(T), {a mathematical formula}∃X⊆UF(Σ):T⊆Conc(X) then {a mathematical formula}∃α∈X, {a mathematical formula}∃W⊆X, such that {a mathematical formula}‖W‖↠‖{α}‖. From the hypothesis that {a mathematical formula}{∅}=INH(T) it follows that {a mathematical formula}T∩S=∅ and {a mathematical formula}∃U⊇T such that U is minimally incompatible and {a mathematical formula}U∖T⊆S. From {a mathematical formula}∃X⊆UF(Σ):T⊆Conc(X) it then follows that {a mathematical formula}∃Y⊇X such that {a mathematical formula}Conc(Y)⊇U and {a mathematical formula}Y∖X⊆S. It follows that Y is an incompatible set of arguments and {a mathematical formula}∃Y′⊆Y which is minimally incompatible and by Proposition 10 has a least element. Since, by fourth condition of Definition 42 atomic arguments are not weaker than defeasible arguments, and an incompatible set cannot consist of atomic arguments only, among the least elements one must be defeasible. Hence we can consider a least element {a mathematical formula}α∈X. Now, {a mathematical formula}Y′∖{α} is a defeater of α (note in particular that {a mathematical formula}Y′∖{α} must be compatible, otherwise we would contradict that {a mathematical formula}Y′ is minimally incompatible) and, given that {a mathematical formula}X⊆UF(Σ) and {a mathematical formula}Y′∖X⊆S, in particular it is a primitive defeater of α. Hence {a mathematical formula}W=(Y′∖{α})∖S⊆X is a genuine defeater of α and by Definition 58, {a mathematical formula}‖W‖↠‖{α}‖ as desired.  □
      </paragraph>
      <paragraph label="Proposition 21">
       Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, the set based argumentation framework{a mathematical formula}FLE=〈AA,↠〉specified byDefinition 58is attack accurate.
      </paragraph>
      <paragraph label="Proof">
       According to Definition 58{a mathematical formula}‖W‖↠‖Z‖ iff {a mathematical formula}∃α∈Z and {a mathematical formula}∃β∈UF(Sub(α)) s.t. W is a genuine defeater of β. We have to prove that whenever {a mathematical formula}‖W‖↠‖Z‖ one of the three conditions specified in Definition 35 holds. Referring to Definition 58 let us consider first the case where the attacked element corresponds to a singleton, i.e. {a mathematical formula}‖W‖↠‖{α}‖. Then {a mathematical formula}∃β∈UF(Sub(α)) such that {a mathematical formula}‖W‖↠‖{β}‖ and we can consider two subcases: {a mathematical formula}β=α and {a mathematical formula}β∈PSub(α).If {a mathematical formula}β=α, W is a genuine defeater of α, i.e. according to Definition 57 there is some set {a mathematical formula}K⊆S such that {a mathematical formula}W∪K is a primitive defeater of α. We have to show that {a mathematical formula}W⊆X∪Y for some X and Y satisfying {a mathematical formula}α∈Y, {a mathematical formula}X∪Y⊆UF(Σ), and the three conditions (i)–(iii) specified in item 1 of Definition 35. In particular we let {a mathematical formula}X=Y=W∪{α} thus clearly {a mathematical formula}α∈Y while the inclusion condition {a mathematical formula}X∪Y=W∪{α}⊆UF(Σ) follows from the facts that {a mathematical formula}W⊆UF(Σ) because it is a genuine defeater and {a mathematical formula}α∈UF(Σ) because of the assumption {a mathematical formula}α=β∈UF(Sub(α)).Now, taking into account the fact that we assumed {a mathematical formula}X=Y and that there are no attackable elements, conditions (i)–(iii) are entailed by the following conditions, corresponding in Definition 35 to {a mathematical formula}T=Conc(Y).
       <list>
        {a mathematical formula}∅∈INH(Conc(Y));{a mathematical formula}∀Y′⊊Y{a mathematical formula}Conc(Y)⊈Conc(Y′).As to item (i′), recall from above that
       </list>
       <paragraph>
        {a mathematical formula}∃K⊆S such that {a mathematical formula}W∪K is a primitive defeater of α. Then, in particular, {a mathematical formula}W∪K is a minimal defeater of α. From the fact that {a mathematical formula}W∪K is a primitive defeater it follows that {a mathematical formula}W∪K is compatible, then from Lemma 5 we get that {a mathematical formula}Conc(W∪K∪{α})=Conc(Y)∪K is minimally incompatible. It follows from Definition 55 that {a mathematical formula}∅∈INH(Conc(Y)).As to item (ii′), suppose {a mathematical formula}∃Y′⊊Y such that {a mathematical formula}Conc(Y)⊆Conc(Y′). Then, if {a mathematical formula}α∈Y′, letting {a mathematical formula}W′=Y′∖{α} we get that {a mathematical formula}W′∪K is a defeater of α contradicting the fact that {a mathematical formula}W∪K is a minimal defeater of α. If instead {a mathematical formula}α∉Y′ it must be the case that {a mathematical formula}∃β∈W∪K such that {a mathematical formula}Conc(β)=Conc(α) but then {a mathematical formula}Conc(W∪K)=Conc(W∪K∪{α}) contradicting the fact that {a mathematical formula}W∪K is compatible.Turning to the case {a mathematical formula}β∈PSub(α) we have that W is a genuine defeater of β, hence it also holds that {a mathematical formula}‖W‖↠‖{β}‖ matching the second condition of Definition 35.Turning to the case where Z is not a singleton, then {a mathematical formula}∃α∈Z, {a mathematical formula}∃β∈Sub(α) such that W is a genuine defeater of β. Then it follows in particular that {a mathematical formula}‖W‖↠‖{α}‖ matching the third condition of Definition 35.  □
       </paragraph>
      </paragraph>
      <paragraph label="Lemma 8">
       Given an AAS with language{a mathematical formula}Land a base set S, if there is an argument β with length{a mathematical formula}Len(β)≥2such that the top rule of β is strict then{a mathematical formula}∃Y⊆UF(PSub(β))∪Ssuch that{a mathematical formula}Conc(β)is strictly derivable from{a mathematical formula}Conc(Y).
      </paragraph>
      <paragraph label="Proof">
       The statement can be proved by induction on the length of β, for length ≥2. For the base case, if {a mathematical formula}Len(β)=2, clearly {a mathematical formula}Y=PSub(β)⊆S. Suppose now the statement holds for every argument γ such that {a mathematical formula}Len(γ)≤n. For {a mathematical formula}Len(β)=n+1 it holds that {a mathematical formula}∀δ∈PSub(β){a mathematical formula}Len(δ)≤n, hence {a mathematical formula}∃Wδ⊆UF(PSub(β))∪S such that {a mathematical formula}Conc(δ) is strictly derivable from {a mathematical formula}Conc(Wδ). Given that the top rule of β is strict, it follows that {a mathematical formula}Conc(β) is strictly derivable from the union of these sets {a mathematical formula}Y=⋃δ∈PSub(β)Wδ⊆UF(PSub(β))∪S.  □
      </paragraph>
      <paragraph label="Proposition 22">
       Given an AAS with language{a mathematical formula}Land a base set S, if there exists a compatible defeater X of an argument α then there exists also a primitive defeater of α whose ultimately fallible arguments are subarguments of the arguments in X.
      </paragraph>
      <paragraph label="Proof">
       Of course the statement is directly verified if X is a primitive defeater. Suppose it is not. First, it is possible to identify a set {a mathematical formula}X′⊆X which is a minimal defeater. If {a mathematical formula}X′⊆UF(Σ)∪S then {a mathematical formula}X′ is a primitive defeater. Otherwise {a mathematical formula}∃β∈X′ with length {a mathematical formula}Len(β)≥2 such that the top rule of β is strict. By Lemma 8 this implies that {a mathematical formula}∃Y⊆UF(Sub(X))∪S such that {a mathematical formula}Conc(β) is strictly derivable from {a mathematical formula}Conc(Y). Then {a mathematical formula}(X′∖{β})∪Y is still a compatible defeater of α (note in particular that the conclusive force of every member of Y cannot be lesser than the conclusive force of β).Repeating the same reasoning for every member of {a mathematical formula}X′ with length ≥2 and a strict top rule, we build a compatible set of arguments {a mathematical formula}X″⊆UF(Σ)∪S which is still a defeater of α. It is then possible to pick a subset {a mathematical formula}X‴⊆X″ which is a minimal defeater of α and hence a primitive defeater of α.  □
      </paragraph>
      <paragraph label="Lemma 9">
       Given an AAS with language{a mathematical formula}Land a base set S, let X be a set of arguments such that{a mathematical formula}X=enableS(X). Then X is compatible.
      </paragraph>
      <paragraph label="Proof">
       First recall that, since {a mathematical formula}X=enableS(X), X is subargument closed and includes the base set. Assume by contradiction that X is incompatible, i.e. there is a strict argument in contradiction which is based on {a mathematical formula}Conc(X). Then it is possible to construct an argument β in contradiction which is based on S and whose subarguments are all included in X. If β has a strict top rule then by Lemma 8{a mathematical formula}∃Y⊆UF(PSub(β))∪S which is incompatible, and {a mathematical formula}∃Y′⊆Y which is minimally incompatible. It holds that {a mathematical formula}Y′⊆X and, since the base set is compatible, {a mathematical formula}Y′⊈S. By Proposition 10, {a mathematical formula}Y′ has a least element. Since, by fourth condition of Definition 42, atomic arguments are not weaker than defeasible arguments, among the least elements one, say γ, must belong to {a mathematical formula}UF(PSub(β)). Then {a mathematical formula}Y′∖{γ} is a defeater of γ, which contradicts the fact that {a mathematical formula}γ∈X and {a mathematical formula}X=enableS(X). If β has a defeasible top rule then we can apply the same reasoning as above and get a contradiction by letting {a mathematical formula}Y={β}.  □
      </paragraph>
      <paragraph label="Lemma 10">
       Given an AAS with language{a mathematical formula}Land a base set S, and given X such that{a mathematical formula}X=enableS(X), for every argument α the following conditions hold: (i) if{a mathematical formula}α∈enableS(X)then{a mathematical formula}∀β∈Sub(α)X does not include any defeater of β; (ii) if{a mathematical formula}α∉enableS(X)then{a mathematical formula}∃β∈UF(Sub(α))such that X includes a defeater of β.
      </paragraph>
      <paragraph label="Proof">
       The proof of condition (ii) is by induction on argument length.For every argument α such that {a mathematical formula}Len(α)=1 we have that {a mathematical formula}α∈S and since {a mathematical formula}S⊆X the statement trivially holds.Suppose now that the statement holds for every argument {a mathematical formula}α′ such that {a mathematical formula}Len(α′)=n≥1 and consider an argument α such that {a mathematical formula}Len(α)=n+1.If the top rule of α is strict, then by case 2 of Definition 49 there is an immediate subargument {a mathematical formula}αi of α such that {a mathematical formula}αi∉enableS(X). Then the statement follows immediately from the induction hypothesis.If the top rule of α is defeasible, then by case 3 of Definition 49 either X includes a defeater of α (entailing the conclusion) or there is an immediate subargument {a mathematical formula}αi of α such that {a mathematical formula}αi∉enableS(X) and the conclusion follows as before from the induction hypothesis.  □
      </paragraph>
      <paragraph label="Proposition 23">
       Given the LAF-ensemble LE corresponding to a base set S of an AAS with language{a mathematical formula}L, let{a mathematical formula}FLE=〈AA,↠〉be the set based argumentation framework specified byDefinition 58. A set of arguments X is an extension according toDefinition 53if and only if there is a stable extension{a mathematical formula}Sof{a mathematical formula}FLEsuch that{a mathematical formula}X={α∈Σ|JUSS(α)=⊤}.
      </paragraph>
      <paragraph label="Proof">
       First let us show that if X is an extension according to Definition 53 then there is a stable extension {a mathematical formula}S of {a mathematical formula}FLE such that {a mathematical formula}X={α∈Σ|JUSS(α)=⊤}. By Proposition 14, {a mathematical formula}enableS(X)=X hence, by Lemma 10, {a mathematical formula}∀α∈XX does not include any defeater of any subargument of α and, for every {a mathematical formula}α∉X, X includes at least a defeater of an ultimately fallible subargument of α. Consider now the set {a mathematical formula}S={‖Y‖|Y⊆X and ‖Y‖∈AA} (which includes in particular the set {a mathematical formula}{‖{α}‖|α∈X}). {a mathematical formula}S is conflict free in {a mathematical formula}FLE: if it was not, there would be some {a mathematical formula}Y,W⊆X such that {a mathematical formula}‖Y‖↠‖W‖. Then by Definition 58{a mathematical formula}∃α∈W s.t. {a mathematical formula}∃β∈UF(Sub(α)) s.t. Y is a genuine defeater of β. Given that the base set is included in any extension, it follows that there is {a mathematical formula}Z⊆X which is a primitive defeater of β. However this contradicts the fact that X does not contain any defeater of any subargument of its members. We have now to show that {a mathematical formula}∀Y∉S such that {a mathematical formula}‖Y‖∈AA{a mathematical formula}∃W∈S such that {a mathematical formula}‖W‖↠‖Y‖. By the definition of {a mathematical formula}S and the properties of the ↠ relation (in particular inclusion awareness) this is equivalent to show that {a mathematical formula}∀β∉X{a mathematical formula}∃W∈S such that {a mathematical formula}‖W‖↠‖{β}‖. Now given that {a mathematical formula}β∉X it is known that X includes a (compatible, since X itself is compatible by Lemma 9) defeater Y of an ultimately fallible subargument {a mathematical formula}β′ of β. Then, by Proposition 22, there is also a primitive defeater W of {a mathematical formula}β′ consisting of subarguments of the elements of Y. Then, again by the fact that if an argument belongs to an extension X also its subarguments belong to X, it follows that {a mathematical formula}W⊆X and also the genuine defeater {a mathematical formula}W∖S⊆X. It follows that {a mathematical formula}‖W∖S‖∈S and {a mathematical formula}‖W∖S‖↠‖{β′}‖ as desired.Turning to the other direction of the proof, let {a mathematical formula}S be a stable extension of {a mathematical formula}FLE. We need to show that {a mathematical formula}X={α∈Σ|JUSS(α)=⊤}={α∈Σ|‖{α}‖∈S} is an extension. To this purpose we use again Proposition 14, i.e. we show that {a mathematical formula}X=enableS(X) referring to the conditions for membership in {a mathematical formula}enableS(X) established by Definition 49.We proceed by induction on the length of arguments. For an argument α such that {a mathematical formula}Len(α)=1 we have that {a mathematical formula}α∈S. By construction (see Definition 58) it holds that {a mathematical formula}‖{α}‖−=∅, hence {a mathematical formula}‖{α}‖∈S and {a mathematical formula}α∈X. Moreover, by item 1 of Definition 49, all arguments in S belong to {a mathematical formula}enableS(X). We have thus seen that for every argument α such that {a mathematical formula}Len(α)=1{a mathematical formula}α∈X if and only if {a mathematical formula}α∈enableS(X). Note also that, given {a mathematical formula}Sub(α)={α}, we have also shown that for every {a mathematical formula}β∈Sub(α) it holds that {a mathematical formula}β∈X (i.e. {a mathematical formula}‖{β}‖∈S) if and only if {a mathematical formula}β∈enableS(X).Suppose now the above conditions hold for every argument α of length {a mathematical formula}n≥1. For an argument α such that {a mathematical formula}Len(α)=n+1, {a mathematical formula}α∈enableS(X) if either item 2 or 3 of Definition 49 is applicable.Suppose item 2 is applicable, i.e. {a mathematical formula}α∈UI(Σ) and, for every immediate subargument {a mathematical formula}αi of α, {a mathematical formula}αi∈enableS(X). Given that {a mathematical formula}α∈UI(Σ), from Definition 58 we get that {a mathematical formula}∀‖Y‖∈‖{α}‖−{a mathematical formula}∃β∈PSub(α) such that {a mathematical formula}‖Y‖∈‖{β}‖−, but since there is an immediate subargument {a mathematical formula}αi of α such that {a mathematical formula}β∈Sub(αi), {a mathematical formula}αi∈enableS(X), {a mathematical formula}Len(αi)≤n by the induction hypothesis we have that {a mathematical formula}‖{β}‖∈S, then {a mathematical formula}‖Y‖∈S+. Hence {a mathematical formula}S defends {a mathematical formula}‖{α}‖ against every attacker. Since {a mathematical formula}S is a stable extension and thus a complete extension, we conclude that {a mathematical formula}‖α‖∈S hence {a mathematical formula}α∈X. From this and the induction hypothesis it also follows {a mathematical formula}∀β∈Sub(α) it holds that {a mathematical formula}‖{β}‖∈S and {a mathematical formula}β∈X.Suppose item 3 is applicable, then {a mathematical formula}α∈UF(Σ), for every immediate subargument {a mathematical formula}αi of α{a mathematical formula}αi∈enableS(X) and X does not contain defeaters of α. Using the same reasoning as for item 2 it can be shown that if {a mathematical formula}∃β∈PSub(α), {a mathematical formula}∃‖Y‖∈‖{β}‖− then it must be the case that {a mathematical formula}S defends {a mathematical formula}‖{β}‖, hence {a mathematical formula}‖{α}‖, against the attack from {a mathematical formula}‖Y‖. It remains to be considered the case where {a mathematical formula}‖Y‖↠‖{α}‖ and {a mathematical formula}∄β∈PSub(α) such that {a mathematical formula}‖Y‖↠‖{β}‖. Then Y is a genuine defeater of α and there is a primitive defeater W of α such that {a mathematical formula}W∖Y⊆S. Given that {a mathematical formula}W⊈X and {a mathematical formula}S⊆X, it must be the case that {a mathematical formula}Y⊈X. It follows that {a mathematical formula}‖Y‖∉S and by the properties of stable extensions {a mathematical formula}S↠‖Y‖. Hence {a mathematical formula}S defends {a mathematical formula}‖{α}‖ against every attacker. Again, it follows that {a mathematical formula}‖{α}‖∈S hence {a mathematical formula}α∈X. From this and the induction hypothesis it also follows {a mathematical formula}∀β∈Sub(α) it holds that {a mathematical formula}‖{β}‖∈S and {a mathematical formula}β∈X.We have thus shown that if {a mathematical formula}α∈enableS(X) then {a mathematical formula}α∈X. It remains to be shown that if {a mathematical formula}α∈X then {a mathematical formula}α∈enableS(X). Since stable extensions are complete extensions, from Proposition 6, we have that {a mathematical formula}∀β∈PSub(α){a mathematical formula}β∈X, hence by induction hypothesis {a mathematical formula}β∈enableS(X). Now if α has the form {a mathematical formula}α1,…,αn→α the fact that {a mathematical formula}α∈enableS(X) follows directly from the fact that for {a mathematical formula}i=1,…,n{a mathematical formula}αi∈enableS(X) and item 2 of Definition 49. If instead α has the form {a mathematical formula}α1,…,αn⇒α we have again that for {a mathematical formula}i=1,…,n{a mathematical formula}αi∈enableS(X) and to derive {a mathematical formula}α∈enableS(X) from item 3 of Definition 49 we only need to show that there are no defeaters of α included in X. This follows from the fact that, taking into account Proposition 22, if there was a defeater Y of α included in X then there would be also a genuine defeater W of α included in X and we would get {a mathematical formula}‖W‖↠‖{α}‖ with both {a mathematical formula}‖W‖ and {a mathematical formula}‖{α}‖ belonging to {a mathematical formula}S hence contradicting the conflict freeness of {a mathematical formula}S.  □
      </paragraph>
     </section>
     <section label="A.6">
      Proofs of Section 9
      <paragraph label="Lemma 11">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), if{a mathematical formula}(S,T)∈EC⁎(AS)then{a mathematical formula}∃S′⊆Sˆ⊆S,{a mathematical formula}∃T′⊆Tˆ⊆T, such that{a mathematical formula}(S′,T′)∈EC(AS).
      </paragraph>
      <paragraph label="Proof">
       Taking into account that the set of premises of any argument is finite, if {a mathematical formula}(S,T)∈EC⁎(AS) then there are {a mathematical formula}Sf⊆S and {a mathematical formula}Tf⊆T such that {a mathematical formula}Sf and {a mathematical formula}Tf are finite and {a mathematical formula}(Sf,Tf)∈EC⁎(AS). Since {a mathematical formula}Sf and {a mathematical formula}Tf are finite, it is possible to identify {a mathematical formula}Sm⊆Sf and {a mathematical formula}Tm⊆Tf such that {a mathematical formula}(Sm,Tm)∈EC⁎(AS) satisfying the minimality condition in Definition 74, i.e. {a mathematical formula}(Smˆ,Tmˆ)∈EC(AS). Letting {a mathematical formula}S′=Smˆ and {a mathematical formula}T′=Tmˆ, since {a mathematical formula}Sm⊆Sf⊆S and {a mathematical formula}Tm⊆Tf⊆T, it holds that {a mathematical formula}S′⊆Sˆ and {a mathematical formula}T′⊆Tˆ.  □
      </paragraph>
      <paragraph label="Lemma 12">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n),{a mathematical formula}EC⁎(AS)=EC⁎1(AS)∪EC⁎2(AS)∪EC⁎3(AS), where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}EC⁎1(AS)={({φ},{ψ})|φ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC⁎2(AS)={(S,{ψ})|S⊢⁎φandφ∈ψ‾};
       </list-item>
       <list-item label="•">
        {a mathematical formula}EC⁎3(AS)={(S,T)|T⊢⁎ψand(S,{ψ})∈EC⁎1(AS)∪EC⁎2(AS)}.
       </list-item>
      </list>
      <paragraph label="Proof">
       First, if {a mathematical formula}(S,T)∈EC⁎(AS) then {a mathematical formula}S⊢⁎φ, {a mathematical formula}T⊢⁎ψ and {a mathematical formula}φ∈ψ‾. According to the definition of {a mathematical formula}EC⁎2(AS), {a mathematical formula}(S,{ψ})∈EC⁎2(AS), thus according to the definition of {a mathematical formula}EC⁎3(AS) it holds that {a mathematical formula}(S,T)∈EC⁎3(AS)⊆EC⁎(AS).As to the reverse direction of the proof, assume that {a mathematical formula}(S,T)∈EC⁎1(AS)∪EC⁎2(AS)∪EC⁎3(AS). We orderly consider the three (non-mutually exclusive) possible cases.If {a mathematical formula}(S,T)∈EC⁎1(AS) then {a mathematical formula}S={φ}, {a mathematical formula}T={ψ} and {a mathematical formula}φ∈ψ‾. Since {a mathematical formula}{φ}⊢⁎φ and {a mathematical formula}{ψ}⊢⁎ψ, {a mathematical formula}S⊢⁎φ and {a mathematical formula}T⊢⁎ψ, thus by definition of {a mathematical formula}EC⁎(AS) it holds that {a mathematical formula}(S,T)∈EC⁎(AS).If {a mathematical formula}(S,T)∈EC⁎2(AS) then {a mathematical formula}T={ψ}, {a mathematical formula}S⊢⁎φ and {a mathematical formula}φ∈ψ‾. Since {a mathematical formula}{ψ}⊢⁎ψ, by definition of {a mathematical formula}EC⁎(AS) it holds that {a mathematical formula}(S,T)∈EC⁎(AS).Finally, if {a mathematical formula}(S,T)∈EC⁎3(AS) then {a mathematical formula}T⊢⁎ψ and {a mathematical formula}(S,{ψ})∈EC⁎1(AS)∪EC⁎2(AS). If {a mathematical formula}(S,{ψ})∈EC⁎1(AS) then {a mathematical formula}S={φ}, {a mathematical formula}φ∈ψ‾ and taking into account that {a mathematical formula}{φ}⊢⁎φ we have that {a mathematical formula}(S,T)∈EC⁎(AS). If instead {a mathematical formula}(S,{ψ})∈EC⁎2(AS) it holds that {a mathematical formula}S⊢⁎φ and {a mathematical formula}φ∈ψ‾, and we have directly that {a mathematical formula}(S,T)∈EC⁎(AS).  □
      </paragraph>
      <paragraph label="Lemma 13">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), the following conditions hold:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∀(S,T)∈EC⁎m(AS),{a mathematical formula}(S,T)∈EC⁎(AS).
       </list-item>
       <list-item label="•">
        {a mathematical formula}∀(S,T)∈EC⁎(AS),{a mathematical formula}∃(S′,T′)∈EC⁎m(AS)such that{a mathematical formula}S′⊆Sand{a mathematical formula}T′⊆T.
       </list-item>
      </list>
      <paragraph label="Proof">
       The first claim immediately follows from Lemma 12, taking into account that {a mathematical formula}S⊢min⁎φ entails {a mathematical formula}S⊢⁎φ.As to the second claim, by Lemma 12 it holds that {a mathematical formula}(S,T)∈EC⁎1(AS)∪EC⁎2(AS)∪EC⁎3(AS).If {a mathematical formula}(S,T)∈EC⁎1(AS) then by definition {a mathematical formula}(S,T)∈EC1(AS)⊆EC⁎m(AS) and the claim is verified with {a mathematical formula}S′=S and {a mathematical formula}T′=T.If {a mathematical formula}(S,T)∈EC⁎2(AS) then by definition {a mathematical formula}T={ψ}, {a mathematical formula}S⊢⁎φ and {a mathematical formula}φ∈ψ‾. Taking into account that the set of premises of any argument is finite {a mathematical formula}∃S′⊆S:S′⊢min⁎φ. By definition of {a mathematical formula}EC2(AS) it holds that {a mathematical formula}(S′,T)∈EC2(AS)⊆EC⁎m(AS).If {a mathematical formula}(S,T)∈EC⁎3(AS) then {a mathematical formula}T⊢⁎ψ and {a mathematical formula}(S,{ψ})∈EC⁎1(AS)∪EC⁎2(AS). Taking into account that the set of premises of any argument is finite, {a mathematical formula}∃T′⊆T:T′⊢min⁎ψ. We distinguish two cases. If {a mathematical formula}(S,{ψ})∈EC⁎1(AS) then by definition {a mathematical formula}(S,{ψ})∈EC1(AS), thus {a mathematical formula}(S,T′)∈EC3(AS)⊆EC⁎m(AS). In the other case {a mathematical formula}(S,{ψ})∈EC⁎2(AS), thus {a mathematical formula}S⊢⁎φ and {a mathematical formula}φ∈ψ‾. As above we can consider a set {a mathematical formula}S′⊆S such that {a mathematical formula}S′⊢min⁎φ. Then it holds by definition that {a mathematical formula}(S′,{ψ})∈EC2(AS), entailing {a mathematical formula}(S′,T′)∈EC3(AS)⊆EC⁎m(AS).  □
      </paragraph>
      <paragraph label="Proposition 24">
       Definition 74, Definition 75are equivalent, i.e.{a mathematical formula}(S,T)∈EC(AS)iff{a mathematical formula}(S,T)∈ECm(AS).
      </paragraph>
      <paragraph label="Proof">
       First, consider a pair {a mathematical formula}(S,T)∈ECm(AS). By definition {a mathematical formula}∃K1,K2⊆Kn such that {a mathematical formula}(S∪K1,T∪K2)∈EC⁎m(AS), thus by Lemma 13{a mathematical formula}(S∪K1,T∪K2)∈EC⁎(AS). We have to prove that {a mathematical formula}∀(S′,T′)∈EC⁎(AS) such that {a mathematical formula}S′ˆ⊆S and {a mathematical formula}T′ˆ⊆T, it holds that {a mathematical formula}S′ˆ=S and {a mathematical formula}T′ˆ=T. Given such a pair {a mathematical formula}(S′,T′), by Lemma 13{a mathematical formula}∃(S″,T″)∈EC⁎m(AS) such that {a mathematical formula}S″⊆S′ and {a mathematical formula}T″⊆T′. Then {a mathematical formula}S″ˆ⊆S′ˆ⊆S and {a mathematical formula}T″ˆ⊆T′ˆ⊆T. Since {a mathematical formula}(S,T)∈ECm(AS) and {a mathematical formula}(S″,T″)∈EC⁎m(AS), according to the minimality condition in Definition 75 it holds that {a mathematical formula}S″ˆ=S and {a mathematical formula}T″ˆ=T, entailing {a mathematical formula}S′ˆ=S and {a mathematical formula}T′ˆ=T.As to the other direction of the proof, consider a pair {a mathematical formula}(S,T)∈EC(AS), i.e. {a mathematical formula}∃K1,K2⊆Kn such that {a mathematical formula}(S∪K1,T∪K2)∈EC⁎(AS) and {a mathematical formula}∀(S′,T′)∈EC⁎(AS) such that {a mathematical formula}S′ˆ⊆S and {a mathematical formula}T′ˆ⊆T, it holds that {a mathematical formula}S′ˆ=S and {a mathematical formula}T′ˆ=T. By Lemma 13 (second item) {a mathematical formula}∃(S′,T′)∈EC⁎m(AS) such that {a mathematical formula}S′⊆S∪K1 and {a mathematical formula}T′⊆T∪K2, entailing that {a mathematical formula}S′ˆ⊆S and {a mathematical formula}T′ˆ⊆T. Since by Lemma 13 (first item) {a mathematical formula}(S′,T′)∈EC⁎(AS), it must be the case that {a mathematical formula}S′ˆ=S and {a mathematical formula}T′ˆ=T. Then, since {a mathematical formula}(S′,T′)∈EC⁎m(AS), in order to prove that {a mathematical formula}(S,T)∈ECm(AS) it has to be shown that {a mathematical formula}∀(S″,T″)∈EC⁎m(AS) such that {a mathematical formula}S″ˆ⊆S and {a mathematical formula}T″ˆ⊆T, it holds that {a mathematical formula}S″ˆ=S and {a mathematical formula}T″ˆ=T. If {a mathematical formula}(S″,T″)∈EC⁎m(AS), by Lemma 13 (first item) {a mathematical formula}(S″,T″)∈EC⁎(AS). Since {a mathematical formula}S″ˆ⊆S, {a mathematical formula}T″ˆ⊆T and {a mathematical formula}(S,T)∈EC(AS), it must be the case that {a mathematical formula}S″ˆ=S and {a mathematical formula}T″ˆ=T, and we are done.  □
      </paragraph>
      <paragraph label="Proposition 25">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n),{a mathematical formula}(∅,∅)∉EC(AS).
      </paragraph>
      <paragraph label="Proof">
       Suppose that {a mathematical formula}(∅,∅)∈EC(AS). Then {a mathematical formula}∃S,T⊆Kn:(S,T)∈EC⁎(AS), i.e. {a mathematical formula}∃φ,ψ:S⊢⁎φ,T⊢⁎ψ and {a mathematical formula}φ∈ψ‾. It is easy to see that this would contradict axiom consistency.  □
      </paragraph>
      <paragraph label="Proposition 26">
       For any two sets{a mathematical formula}T,Usuch that{a mathematical formula}T∩RN≠∅, it cannot be the case that{a mathematical formula}(T,U)∈EC(AS).
      </paragraph>
      <paragraph label="Proof">
       Since {a mathematical formula}T∩RN≠∅, {a mathematical formula}∃r∈RD such that {a mathematical formula}n(r)∈T. Recall that {a mathematical formula}n(r) cannot be among the premises of a rule, {a mathematical formula}n(r)∉Kn, and ∀ψ it holds that {a mathematical formula}n(r)∉ψ‾. Reasoning by contradiction, assume that {a mathematical formula}(T,U)∈EC(AS). This in particular entails that {a mathematical formula}T∪K1⊢⁎φ, {a mathematical formula}U∪K2⊢⁎ψ and {a mathematical formula}φ∈ψ‾, where {a mathematical formula}K1,K2⊆Kn. Since {a mathematical formula}n(r)∉ψ‾, {a mathematical formula}n(r)≠φ. Then, taking into account that {a mathematical formula}n(r) cannot be among the premises of a rule, {a mathematical formula}(T∖{n(r)})∪K1⊢⁎φ, entailing that {a mathematical formula}((T∖{n(r)})∪K1,U∪K2)∈EC⁎(AS). However, {a mathematical formula}(T∖{n(r)})⊊T, and this contradicts the minimality condition in Definition 74.  □
      </paragraph>
      <paragraph label="Proposition 27">
       For any two sets{a mathematical formula}T,Usuch that{a mathematical formula}(T,U)∈EC(AS), if{a mathematical formula}U∩RN≠∅then{a mathematical formula}U={n(r)}with{a mathematical formula}r∈RD.
      </paragraph>
      <paragraph label="Proof">
       Since {a mathematical formula}(T,U)∈EC(AS), by definition {a mathematical formula}T∪K1⊢⁎φ, {a mathematical formula}U∪K2⊢⁎ψ and {a mathematical formula}φ∈ψ‾, where {a mathematical formula}K1,K2⊆Kn. Since {a mathematical formula}U∩RN≠∅, there is a rule {a mathematical formula}r∈RD such that {a mathematical formula}n(r)∈U. Since {a mathematical formula}n(r) cannot be among the premises of a rule, two cases can be considered. If {a mathematical formula}(U∖{n(r)})∪K2⊢⁎ψ then {a mathematical formula}(T∪K1,U∖{n(r)}∪K2)∈EC⁎(AS). However, this contradicts the minimality condition relevant to {a mathematical formula}(T,U) in Definition 74. Then, the only possible case is that {a mathematical formula}ψ=n(r)∈U, and taking into account the minimality condition in Definition 74 it must be the case that {a mathematical formula}U={n(r)}.  □
      </paragraph>
      <paragraph label="Proposition 28">
       Given an argumentation theory AT, for every argument α the function{a mathematical formula}FIαΔintroduced inDefinition 81satisfies the requirements ofDefinition 11.
      </paragraph>
      <paragraph label="Proof">
       We orderly consider the list of properties:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(Sub(α))=I;In this case {a mathematical formula}X=Sub(α) hence {a mathematical formula}Sub(α)∖X=∅ and it trivially holds that for all the arguments in the empty set the condition stated in Definition 81 is satisfied, hence {a mathematical formula}FIαΔ(Sub(α))=I.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}∀α∈Σ{a mathematical formula}FIαΔ(X)=FIαΔ(⋃β∈XSub(β));The property obviously holds if X is subargument closed, i.e. {a mathematical formula}X=⋃β∈XSub(β). Suppose now that X is not subargument closed i.e. {a mathematical formula}∃γ,δ:γ∈X,δ∉X,δ⊏γ. Referring to Definition 81, it holds that {a mathematical formula}δ∈Sub(α)∖X but, since {a mathematical formula}∃γ∈X:δ⊑γ, δ does not affect the value assigned to {a mathematical formula}FIαΔ(X). It follows that {a mathematical formula}FIαΔ(X)=FIαΔ(X∪{δ}). Iterating the same reasoning on every such argument δ we get the desired conclusion.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}∀α∈Σ, if {a mathematical formula}X⊊Sub(α) is subargument closed and {a mathematical formula}∃β∈(Sub(α)∖X), such that {a mathematical formula}FIβΔ(PSub(β))=F then {a mathematical formula}FIαΔ(X)=F;From {a mathematical formula}FIβΔ(PSub(β))=F it follows that β is an ordinary premise or the top rule of β is defeasible. Given that {a mathematical formula}β∈Sub(α)∖X and that X is subargument closed it follows that {a mathematical formula}∄γ∈X:β⊑γ then from Definition 81 we get {a mathematical formula}FIαΔ(X)=F.
       </list-item>
       <list-item label="4.">
        if {a mathematical formula}FIαΔ(X)=I then {a mathematical formula}AE(α)⊆AE(X);In the case {a mathematical formula}X=Sub(α) the conclusion trivially follows. Otherwise, {a mathematical formula}X⊆PSub(α) and from {a mathematical formula}FIαΔ(X)=I we get that the top rule of α must be strict or α is an axiom, from which {a mathematical formula}AE(α)=∅, obviously satisfying the condition.
       </list-item>
       <list-item label="5.">
        if {a mathematical formula}FIαΔ(PSub(α))=I then for every argument β and for every set X such that {a mathematical formula}X⊆Sub(β) and {a mathematical formula}α∈X it holds that {a mathematical formula}FIβΔ(X)=FIβΔ((X∖{α})∪PSub(α)).From {a mathematical formula}FIαΔ(PSub(α))=I we get that the top rule of α is strict or α is an axiom. Now considering an argument β such that {a mathematical formula}α∈Sub(β) and a set X such that {a mathematical formula}X⊆Sub(β) and {a mathematical formula}α∈X, letting {a mathematical formula}W={γ∈(Sub(β)∖X)|∄δ∈X:γ⊑δ} and {a mathematical formula}W′={γ∈(Sub(β)∖(X∪PSub(α)))|∄δ∈X:γ⊑δ}, it is easy to see that {a mathematical formula}W=W′. Given that the top rule of α is strict or α is an axiom, we get that all arguments in W satisfy the condition of Definition 81 (i.e. being an axiom or having a strict top rule) if and only if all arguments in {a mathematical formula}W′∪{α} satisfy it. It follows that {a mathematical formula}FIβΔ(X)=FIβΔ((X∖{α})∪PSub(α)). □
       </list-item>
      </list>
      <paragraph label="Proposition 29">
       Given an argumentation theory AT,{a mathematical formula}∀α∈Σit holds that{a mathematical formula}FIαΔ(∅)=FI(α).
      </paragraph>
      <paragraph label="Proof">
       From Definition 62 it is easy to see that an argument is firm and strict (hence {a mathematical formula}FI(α)=I) if and only if only strict rules and axioms are used in its construction. It follows that all its atomic subarguments are axioms and all the top rules of its non-atomic subarguments (if any) are strict, hence it is easy to derive that {a mathematical formula}FIαΔ(∅)=I. If an argument is not firm and strict (hence {a mathematical formula}FI(α)=F) at least an ordinary premise or a defeasible rule is used in its construction, hence there is at least a subargument of α such that α is an ordinary premise or the top rule of α is defeasible and it follows {a mathematical formula}FIαΔ(∅)=F.  □
      </paragraph>
      <paragraph label="Proposition 30">
       Given an argumentation theory{a mathematical formula}AT=(AS,K), the LAF-ensemble corresponding to AT is{a mathematical formula}II-consonant.
      </paragraph>
      <paragraph label="Proof">
       We have to prove that if {a mathematical formula}∃T,U⊆L, {a mathematical formula}∃X,Y⊆Σ such that
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}T∈INH(U);
       </list-item>
       <list-item label="•">
        {a mathematical formula}T⊆Conc(X)∪AE(X);
       </list-item>
       <list-item label="•">
        {a mathematical formula}U⊆Conc(Y)∪AE(Y);
       </list-item>
      </list>
      <paragraph label="Proposition 31">
       Given an argumentation theory{a mathematical formula}AT=(AS,K),{a mathematical formula}∅∈RS(AT)iff{a mathematical formula}∃β∈ARGS(AT)such that one of the following two conditions hold:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∃β′∈Sub(β)such that{a mathematical formula}Top(β′)=ror{a mathematical formula}β′is of the form{a mathematical formula}β1″,…,βn″⇒n(r),{a mathematical formula}r∈RD, and ∃φ such that{a mathematical formula}Kn⊢⁎φand{a mathematical formula}φ∈n(r)‾
       </list-item>
       <list-item label="•">
        {a mathematical formula}∃φ∈Premp(β)or{a mathematical formula}∃β′∈Sub(β)of the form{a mathematical formula}β1″,…,βn″⇒φ, and{a mathematical formula}∃η,θsuch that{a mathematical formula}Kn∪{φ}⊢⁎η,{a mathematical formula}Kn∪{φ}⊢⁎θ, and{a mathematical formula}η∈θ‾.
       </list-item>
      </list>
      <paragraph label="Proof">
       According to Definition 83, {a mathematical formula}∅∈RS(AT) iff {a mathematical formula}∃β∈ARGS(AT):∅⇝β, and since ∅ is obviously minimal under set inclusion this in turns holds iff ∅ defeats β. Taking into account that, according to Definition 77, there cannot exist any argument {a mathematical formula}β′ such that {a mathematical formula}∅≺β′, the set ∅ defeats β iff ∅ undercuts, rebuts or undermines β, which according to Definition 76 may hold in one of the following two cases:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}∃β′∈Sub(β) such that {a mathematical formula}Top(β′)=r or {a mathematical formula}β′ is of the form {a mathematical formula}β1″,…,βn″⇒n(r), {a mathematical formula}r∈RD, and {a mathematical formula}∃T,U such that {a mathematical formula}T∪U={n(r)}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}n(r)∈U. Taking into account Proposition 26, this holds iff {a mathematical formula}(∅,{n(r)})∈EC(AS). Taking into account that {a mathematical formula}n(r) cannot be among the premises of any rule, this condition in turn holds iff ∃φ such that {a mathematical formula}Kn⊢⁎φ and {a mathematical formula}φ∈n(r)‾.
       </list-item>
       <list-item label="•">
        {a mathematical formula}∃φ∈Premp(β) or {a mathematical formula}∃β′∈Sub(β) of the form {a mathematical formula}β1″,…,βn″⇒φ, {a mathematical formula}∃T,U such that {a mathematical formula}T∪U={φ}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}φ∈U, i.e. {a mathematical formula}U={φ}. We prove the desired claim by considering both directions of the equivalence. First, if the previous conditions hold, T is either ∅ or {a mathematical formula}{φ}. In both of the cases, {a mathematical formula}(T,{φ})∈EC(AS) entails that {a mathematical formula}∃η,θ such that {a mathematical formula}Kn∪{φ}⊢⁎η, {a mathematical formula}Kn∪{φ}⊢⁎θ, and {a mathematical formula}η∈θ‾. As to the other direction of the equivalence, assume that {a mathematical formula}∃φ∈Premp(β) or {a mathematical formula}∃β′∈Sub(β) of the form {a mathematical formula}β1″,…,βn″⇒φ, and {a mathematical formula}∃η,θ such that {a mathematical formula}Kn∪{φ}⊢⁎η, {a mathematical formula}Kn∪{φ}⊢⁎θ, and {a mathematical formula}η∈θ‾. We have to prove that {a mathematical formula}∃T,U such that {a mathematical formula}T∪U={φ}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}φ∈U, i.e. {a mathematical formula}U={φ}. By the hypothesis, {a mathematical formula}∃K1,K2⊆Kn such that {a mathematical formula}(K1∪{φ},K2∪{φ})∈EC⁎(AS). By Lemma 11, {a mathematical formula}∃T′⊆{φ}, {a mathematical formula}∃U′⊆{φ} such that {a mathematical formula}(T′,U′)∈EC(AS). Since {a mathematical formula}(∅,∅)∈EC(AS) is prevented by Proposition 25, only two cases are possible. If {a mathematical formula}(T′,{φ})∈EC(AS), the claim is proved with {a mathematical formula}T=T′. In the other case, {a mathematical formula}({φ},∅)∈EC(AS), entailing that {a mathematical formula}∃K1,K2⊆Kn, {a mathematical formula}∃η,θ with {a mathematical formula}K1∪{φ}⊢⁎η, {a mathematical formula}K2⊢⁎θ, {a mathematical formula}η∈θ‾. By weak well-formedness, it must be the case that {a mathematical formula}θ∈η‾, thus {a mathematical formula}(K2,K1∪{φ})∈EC⁎(AS), which taking into account Proposition 25 entails {a mathematical formula}(∅,{φ})∈EC(AS). This proves the claim with {a mathematical formula}T=∅.
       </list-item>
      </list>
      <paragraph label="Proposition 32">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is subargument aware.
      </paragraph>
      <paragraph label="Proof">
       By Definition 84, for a generic set Θ and an argument β, {a mathematical formula}‖Θ‖↠‖{β}‖ if {a mathematical formula}Θ⇝{β} i.e., according to Definition 78, Θ is a minimal set such that either Θ preference-independent attacks β on {a mathematical formula}β′ or Θ preference-dependent attacks β on {a mathematical formula}β′ and {a mathematical formula}Θ⊀β′ with {a mathematical formula}β′∈Sub(β). Since for every superargument α of β it holds that {a mathematical formula}β′∈Sub(α), the above condition applies to α too and we get {a mathematical formula}‖Θ‖↠‖{α}‖.  □
      </paragraph>
      <paragraph label="Proposition 33">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is inclusion aware.
      </paragraph>
      <paragraph label="Proof">
       By Definition 84, for generic sets {a mathematical formula}Θ,Λ{a mathematical formula}‖Θ‖↠‖Λ‖ if {a mathematical formula}∃β∈Λ such that {a mathematical formula}Θ⇝{β}. Of course if {a mathematical formula}Λ⊆ϒ then {a mathematical formula}β∈ϒ too and {a mathematical formula}‖Λ‖↠‖ϒ‖.  □
      </paragraph>
      <paragraph label="Lemma 17">
       Given an argumentation theory{a mathematical formula}AT=(AS,K)with{a mathematical formula}AS=(L,¯,R,n), if{a mathematical formula}(S,∅)∈EC(AS)then{a mathematical formula}∃S′⊆S,{a mathematical formula}S′≠∅, such that{a mathematical formula}(∅,S′)∈EC(AS).
      </paragraph>
      <paragraph label="Proof">
       Since {a mathematical formula}(S,∅)∈EC(AS), by definition {a mathematical formula}∃K1,K2⊆Kn:(K1∪S,K2)∈EC⁎(AS), i.e. {a mathematical formula}K1∪S⊢⁎φ, {a mathematical formula}K2⊢⁎ψ and {a mathematical formula}φ∈ψ‾. By weak well-formedness, it has to be the case that also {a mathematical formula}ψ∈φ‾ holds, entailing {a mathematical formula}(K2,K1∪S)∈EC⁎(AS). By Lemma 11, {a mathematical formula}∃S′⊆S such that {a mathematical formula}(∅,S′)∈EC(AS), and by Proposition 25 it must be the case that {a mathematical formula}S′≠∅.  □
      </paragraph>
      <paragraph label="Proposition 34">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is fallible language inhibition covering.
      </paragraph>
      <paragraph label="Proof">
       We have to prove that the condition stated in Definition 34 is satisfied, i.e. that whenever {a mathematical formula}∃S,T⊆L:S∈INH(T), {a mathematical formula}∃X⊆UF(Σ):S⊆Conc(X)∪AE(X), and {a mathematical formula}∃Y⊆UF(Σ):T⊆Conc(Y)∪AE(Y) then {a mathematical formula}∃α∈X∪Y,∃W⊆X∪Y:‖W‖↠‖{α}‖. Note that both S and T are finite, since {a mathematical formula}S∈INH(T) means that {a mathematical formula}(S,T)∈EC(AS).In order to prove the claim, we show that {a mathematical formula}∃α∈X∪Y and {a mathematical formula}∃W′⊆X∪Y, where {a mathematical formula}W′ is finite, such that {a mathematical formula}W′ defeats α. This entails that {a mathematical formula}∃W⊆W′⊆X∪Y which minimally defeats α, i.e. by Definition 84{a mathematical formula}‖W‖↠‖{α}‖, which proves the claim.By Proposition 26 it holds that {a mathematical formula}S∩RN=∅, thus {a mathematical formula}S⊆Conc(X), i.e. {a mathematical formula}∃X′⊆X⊆UF(Σ):S=Conc(X′). Since S is finite, we can choose {a mathematical formula}X′ finite as well. As far as T is concerned, we distinguish three cases.First, if {a mathematical formula}T=∅ then by the hypothesis {a mathematical formula}(S,∅)∈EC(AS), thus by Lemma 17{a mathematical formula}∃S′⊆S, {a mathematical formula}S′≠∅, such that {a mathematical formula}(∅,S′)∈EC(AS). Since {a mathematical formula}S=Conc(X′), {a mathematical formula}∃X″⊆X′ such that {a mathematical formula}S′=Conc(X″), where {a mathematical formula}X″ is finite and non-empty. Then, by Lemma 14, {a mathematical formula}∃α∈X″:(X″∖{α})⊀α. Letting {a mathematical formula}W′=X″∖{α}, we have that {a mathematical formula}Conc(W′)∪Conc(α)=S′, {a mathematical formula}(∅,S′)∈EC(AS) and {a mathematical formula}Conc(α)∈S′, thus {a mathematical formula}W′ either rebuts or undermines α. As a consequence, {a mathematical formula}W′ either preference-independent attacks α, or preference-dependent attacks α with {a mathematical formula}W′⊀α, i.e. in both cases {a mathematical formula}W′ defeats α with {a mathematical formula}W′⊆X″⊆X′⊆X and {a mathematical formula}α∈X″⊆X.Let us now consider the case where {a mathematical formula}T∩AE(Y)≠∅, i.e. {a mathematical formula}∃r:n(r)∈T and {a mathematical formula}r=Top(α), where α is an argument in Y. By Proposition 27 it holds that {a mathematical formula}T={n(r)}, thus {a mathematical formula}(Conc(X′),{n(r)})∈EC(AS). Accordingly, {a mathematical formula}X′ undercuts α on α (see Definition 76), thus it also defeats α (see Definition 78). Taking into account that {a mathematical formula}X′ is finite, {a mathematical formula}X′⊆X⊆(X∪Y) and {a mathematical formula}α∈Y⊆(X∪Y), this proves the claim (with {a mathematical formula}W′=X′) for the current case.The final case to be considered is {a mathematical formula}T≠∅ and {a mathematical formula}T∩AE(Y)=∅, i.e. {a mathematical formula}T⊆Conc(Y). Thus {a mathematical formula}∃Y′⊆Y:T=Conc(Y′), where as above {a mathematical formula}Y′ can be assumed finite without loss of generality. We distinguish two cases. If {a mathematical formula}(T,S)∉EC(AS), letting α an arbitrary argument in {a mathematical formula}Y′ and {a mathematical formula}W′=(X′∪Y′)∖{α} it holds that {a mathematical formula}Conc(W′)∪Conc(α)=S∪T, {a mathematical formula}(S,T)∈EC(AS) and {a mathematical formula}Conc(α)∈T, thus {a mathematical formula}W′ either rebuts or undermines α (note that α is ultimately fallible since {a mathematical formula}α∈Y′⊆Y). Since {a mathematical formula}(T,S)∉EC(AS), {a mathematical formula}W′ preference-independent attacks α, thus it defeats α. If instead both {a mathematical formula}(S,T)∈EC(AS) and {a mathematical formula}(T,S)∈EC(AS) hold, applying Lemma 14 we see that {a mathematical formula}∃α∈(X′∪Y′):((X′∪Y′)∖{α})⊀α. Now, letting {a mathematical formula}W′=(X′∪Y′)∖{α} it holds that {a mathematical formula}Conc(W′)∪Conc(α)=S∪T, {a mathematical formula}(S,T)∈EC(AS) and {a mathematical formula}(T,S)∈EC(AS), and either {a mathematical formula}Conc(α)∈S or {a mathematical formula}Conc(α)∈T. Thus, {a mathematical formula}W′ rebuts or undermines α (note that α is ultimately fallible since {a mathematical formula}α∈(X′∪Y′)⊆(X∪Y)), and in particular preference-dependent attacks α with {a mathematical formula}W′⊀α, proving the claim for this final case.  □
      </paragraph>
      <paragraph label="Proposition 35">
       Given an argumentation theory AT, the set based argumentation framework{a mathematical formula}RS−AF(AT)specified byDefinition 85is attack accurate.
      </paragraph>
      <paragraph label="Proof">
       We have to prove that whenever {a mathematical formula}‖Θ‖↠‖Λ‖ one of the three conditions specified in Definition 35 holds. Referring to Definition 84, {a mathematical formula}‖Θ‖↠‖Λ‖ iff {a mathematical formula}Θ⊆UF(ARGS(AT)) and {a mathematical formula}∃α∈Λ:Θ⇝α, i.e. Θ minimally defeats α. First note that condition 3 of Definition 35 is directly satisfied when Λ is not a singleton, thus we can focus on the cases where Λ is a singleton, i.e. {a mathematical formula}Λ={α}, and {a mathematical formula}Θ⇝α. By Definition 78 it holds that Θ preference-independent attacks α on some subargument {a mathematical formula}α′ or Θ preference-dependent attacks α on some subargument {a mathematical formula}α′ and {a mathematical formula}Θ⊀α′. In the case {a mathematical formula}α′∈PSub(α) condition 2 of Definition 35 is directly satisfied, thus we can focus on {a mathematical formula}α′=α and we have to consider the various forms of attack encompassed by Definition 76.First, consider the cases where Θ undercuts α, with {a mathematical formula}r=Top(α)∈RD, or Θ rebuts α with {a mathematical formula}Conc(α)=n(r). In both of the considered cases, according to Definition 76 it holds that {a mathematical formula}α∈UF(ARGS(AT)) and {a mathematical formula}∃T,U such that {a mathematical formula}T∪U=Conc(Θ)∪{n(r)}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}n(r)∈U. On the basis of Proposition 27 it must be the case that {a mathematical formula}U={n(r)}, and taking into account Proposition 26 we also have {a mathematical formula}T=Conc(Θ). Thus {a mathematical formula}(Conc(Θ),{n(r)})∈EC(AS) where it obviously holds that {a mathematical formula}n(r)∈{Conc(α)}∪AE(α). Letting in Definition 35{a mathematical formula}X=Θ and {a mathematical formula}Y={α}, we have thus {a mathematical formula}Conc(X)∈INH({n(r)}) where {a mathematical formula}{n(r)}⊆Conc(Y)∪AE(Y), and the minimality condition concerning Y in Definition 35 is directly satisfied, since the unique proper subset of Y is the empty set and {a mathematical formula}Conc(∅)∪AE(∅)=∅⊉{n(r)}.Turning to the other cases, it cannot hold that Θ undermines α on a rule name, since rule names do not belong to {a mathematical formula}K. We then consider the remaining cases where Θ rebuts α with {a mathematical formula}Conc(α)=φ, or Θ undermines α on an ordinary premise φ, and φ (in both of the cases) is not a rule name. According to Definition 76, {a mathematical formula}α∈UF(ARGS(AT)) and {a mathematical formula}∃T,U such that {a mathematical formula}T∪U=Conc(Θ)∪{φ}, {a mathematical formula}(T,U)∈EC(AS) and {a mathematical formula}φ∈U. It is then possible to identify a set {a mathematical formula}X⊆Θ∪{α} such that {a mathematical formula}T=Conc(X). Moreover, taking into account that {a mathematical formula}Θ∪{α} is finite (since Θ as any set in {a mathematical formula}RS(AT) is finite) and {a mathematical formula}U⊆Conc(Θ)∪{φ}, it is possible to identify a set {a mathematical formula}Y⊆Θ∪{α} such that {a mathematical formula}U=Conc(Y) and {a mathematical formula}∀Y′⊊Y,U⊈Conc(Y′). Then Definition 35 is satisfied by X and Y, provided that {a mathematical formula}Θ⊆X∪Y and {a mathematical formula}α∈Y.As to the latter condition, assume by contradiction that {a mathematical formula}α∉Y. Then, since {a mathematical formula}Conc(Y)=U and {a mathematical formula}φ∈U, we get that there is some argument {a mathematical formula}β∈Y⊆Θ, with {a mathematical formula}β≠α, such that {a mathematical formula}Conc(β)=Conc(α). However, this entails that {a mathematical formula}Θ∖{β} defeats α, contradicting the fact that Θ minimally defeats α.As to the first condition, assume by contradiction that {a mathematical formula}Θ⊈X∪Y. Since {a mathematical formula}X∪Y⊆Θ∪{α}, we have that {a mathematical formula}X∪Y∖{α}⊆Θ, and since {a mathematical formula}Θ⊈X∪Y it must be the case that {a mathematical formula}X∪Y∖{α}⊊Θ. However, letting {a mathematical formula}Θ′=X∪Y∖{α} we would have {a mathematical formula}Conc(Θ′∪{α})=Conc(X∪Y)=T∪U=Conc(Θ)∪{φ}, entailing that {a mathematical formula}Θ′ defeats α. Again, since {a mathematical formula}Θ′⊊Θ this would contradict the fact that Θ minimally defeats α.  □
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>