<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Fundamental properties of attack relations in structured argumentation with priorities.
   </title>
   <abstract>
    Due to a proliferation and diversity of approaches to structured argumentation with prioritized rules, several simple and intuitive principles for characterization and evaluation of the proposed attack relations have recently been introduced in [23]. While the proposed principles and properties are helpful, they do not identify unique attack relations. Any user of structured argumentation still faces a fundamental problem of determining an appropriate attack relation for her/his application and further principles that could help in identifying such attack relation. We argue that a key purpose of introducing priorities between defeasible rules is to remove undesired attacks while keeping the set of removed attacks to a minimum. This intuitive idea could be viewed as a kind of minimal-removal-principle. We show in this paper that the minimal-removal-principle together with a new simple and intuitive property of inconsistency-resolving and previously proposed properties indeed characterize a unique attack relation referred to as the canonical attack relation. We show that canonical attack relations could be characterized in three distinct ways, as the supremum of a complete upper-semilattice of regular attack relations, or by removing the undesired attacks from the basic attack relations where the undesired attacks are captured by a least-fixed point of an intuitive removal function, or as the normal attack relations introduced in an earlier paper for a class of well-prioritized knowledge bases. We start our study with a language consisting only of literals and two type of attacks, rebut and undercut. We then show that our approach can easily be scaled up by showing that all key results still hold for general underlying logical languages and the inclusion of assumptions. We apply our proposed approach to valued-based argumentation and show that it also leads to the canonical semantics.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      At its most abstraction, an argument system could be viewed as an argumentation framework [29] consisting of a set of arguments and a binary attack relation between them. Though simple, argumentation frameworks are powerful enough to provide a sophisticated account of the acceptance of arguments representing different ways people could draw conclusions from exchanges of arguments.
     </paragraph>
     <paragraph>
      While there is a good understanding about the acceptability of arguments due to an extensive amount of research [29], [7], [6], [8], [34], [35], [14], [2], [19], more needs to be done to gain a better understanding about the structure of arguments and their attack relations. In domains like experimental medicine, arguments often have no internal structure as the purpose of the experiments is to uncover the underlining rules [41]. In contrast, arguments in commonsense reasoning and legal domains are often based on complex sets of rules [9], [26]. The complex structure of arguments often leads to challenging questions about the structure of their attack relations.
     </paragraph>
     <paragraph>
      There are extensive research on rule-based systems with prioritized rules (see for example [44], [43], [51], [4], [3], [13], [22], [50], [48], [15], [39], [38], [49]). Amgoud&amp;Cayrol [4] have proposed the use of priorities between rules to filter out certain undesired attacks. Continuing this idea, Prakken and Modgil&amp;Prakken [47], [43], [44] have proposed ASPIC+, a rich framework for structured argumentation with prioritized rules with several distinct systems of attack relations. This rich diversity of proposed attack relations also poses a serious challenge for any potential user of structured argumentation as such a user would have to decide which attack relation should be selected and implemented for her/his domain.
     </paragraph>
     <paragraph>
      For illustration, we recall and elaborate a simple example from [23] that is helpful in explaining many concepts and ideas later.
     </paragraph>
     <paragraph label="Example 1">
      A Sherlock Holmes investigationSherlock Holmes is investigating a case involving three persons {a mathematical formula}P1,P2 and S together with the dead body of a big man. The case could be represented by the following knowledge base.
      <list>
       The knowledge that one of the persons is the murderer is represented by three strict rules:{sup:1}{a mathematical formula}S is a small child who cannot kill a big man. This fact is captured in the base of evidence {a mathematical formula}BE={Inno(S)}.The legal principle that people are considered innocent until proven otherwise could be represented by three defeasible rules{a mathematical formula}After digging around, it becomes clear to Holmes that {a mathematical formula}P1 has a strong motive to kill the victim while there is nothing connecting {a mathematical formula}P2 to the dead man. He hence will focus his investigation on {a mathematical formula}P1. This knowledge is represented by a preference{a mathematical formula} stating that Holmes gives higher priority (in his investigation) to the scenario in which {a mathematical formula}P2 is innocent than to the other one.Let
      </list>
      <paragraph>
       KB be the knowledge base containing the strict rules {a mathematical formula}r1,r2,r3, the three defaults {a mathematical formula}d1,d2,d and the fact that S is innocent together with the preference {a mathematical formula}d1≺d2.Relevant arguments concerning the innocence of {a mathematical formula}P1,P2 wrt KB are given in Fig. 1.Due to the preference of {a mathematical formula}d2 over {a mathematical formula}d1, {a mathematical formula}N2 attacks {a mathematical formula}A1 wrt all four MP-attack relations{sup:2} in the ASPIC+ framework. Therefore {a mathematical formula}N2 also attacks {a mathematical formula}N1,N1′. Hence there is a stable extension containing {a mathematical formula}A2,N2,N2′ implying the expected conclusion {a mathematical formula}¬Inno(P1),Inno(P2).According to the MP-attack relations based on the democratic order, {a mathematical formula}N1′ attacks {a mathematical formula}A2.{sup:3} Hence {a mathematical formula}N1′ also attacks {a mathematical formula}N2,N2′. Therefore there is another stable extension containing {a mathematical formula}A1,N1′,N1 justifying {a mathematical formula}Inno(P1),¬Inno(P2), a rather counter-intuitive set of beliefs.Even though {a mathematical formula}N1′ attacks {a mathematical formula}A2 wrt MP-attack relations based on the democratic order, {a mathematical formula}N1 does not. This is rather surprising as {a mathematical formula}N1′ could be seen as a weakened version of {a mathematical formula}N1 where the undisputed fact “S is innocent” in {a mathematical formula}N1 is replaced by a defeasible one in {a mathematical formula}N1′ stating only that if there is no evidence to the contrary then S is innocent. As it has been pointed out in [23], MP-attack relations based on the democratic order do not satisfy the property of attack monotonicity stating that if a weakened version of an argument A attacks an argument B then A itself should also attack B. We can say the reason that MP-attack relations based on democratic order support counter-intuitive beliefs in this example is due to a violation of this property.
      </paragraph>
     </paragraph>
     <paragraph>
      The example illustrates the need to establish general principles for the characterization and evaluation of alternative attack relations for rule-based systems.{sup:4} Caminada and Amgoud [17] have introduced the postulates of consistency and closure for argument-based systems. A subargument closure postulate stating that any extension should contain all subarguments of its arguments has been studied by Martinez&amp;Garcia&amp;Simari [42], Amgoud [1], Modgi&amp;Prakken [43]. Though the three proposed postulates are very helpful, they are not sufficient to guarantee intuitive semantics, as they do not take into account the preferences of defeasible rules. To address this problem, Dung [30], [23] has proposed a set of simple and intuitive properties, referred to as ordinary properties in [23] and showed that they can be used to characterize and evaluate the proposed attack relations in structured argumentation with prioritized rules.
     </paragraph>
     <paragraph>
      As there could be in general many attack relations satisfying the ordinary properties, there still remains a huge challenge for any user/developer of structured argumentation with prioritized rules to decide which of the ordinary attack relations should be selected/implemented for her/his domain and what are the guidelines for picking an appropriate one.
     </paragraph>
     <paragraph>
      Amgoud&amp;Cayrol [4] were arguably the first to study the application of priorities of defeasible rules to define a preference relation between arguments and then using the preference relation to define attack relation between arguments. Prakken [47] and Modgil&amp;Prakken [43] distinguished between preference independent and preference dependent attacks and similar to Amgoud&amp;Cayrol [4], applied priorities to define a preference relation between preference dependent arguments. In essence, we can say that both Amgoud&amp;Cayrol [4] and Modgil&amp;Prakken [43] have applied priorities between defeasible rules to filter out undesired attacks. In this paper, we argue further that the removal of attacks should be kept to a minimum. This intuitive idea could be viewed as a kind of minimal-removal-principle.
     </paragraph>
     <paragraph>
      The following very simple example illustrates the idea.
     </paragraph>
     <paragraph label="Example 2">
      Consider a knowledge base consisting of just four defeasible rules and four arguments {a mathematical formula}A,A1,B,B1 as seen in Fig. 2. Without any preference between the rules, we have {a mathematical formula}A,A1 attack each other. Similarly {a mathematical formula}B,B1 attack each other.Suppose that for whatever reason {a mathematical formula}d3 is strictly less preferred than {a mathematical formula}d2 (i.e. {a mathematical formula}d3≺d2). The introduction of the preference {a mathematical formula}d3≺d2 in essence means that the attack of {a mathematical formula}B1 against B should be removed, but it does not say anything about the other attacks. Hence these other attacks should be kept, i.e. the attacks that should be removed should be kept to a minimum.
     </paragraph>
     <paragraph>
      We introduce in this paper an intuitive property of inconsistency-resolving providing a deep structural insight into the nature of attack relations satisfying the postulate of consistency. We refer to the inconsistency-resolving property and the ordinary properties other than the credulous cumulativity as regular properties.
     </paragraph>
     <paragraph>
      It turns out that the minimal-removal principle coupled with regular properties indeed determine a unique attack relation that can be viewed as the common attack relation by any user/developer who agrees with the regular properties. Formally, we show that attack relations satisfying the regular properties form a complete upper-semilattice whose supremum referred to as the canonical attack relations could be viewed as uniquely identified by the minimal-removal principle. We also show that the canonical attack relations can be characterized by the least-fixed point of a removal-function defined by interpreting the regular properties contrapositively.
     </paragraph>
     <paragraph>
      A class of normal attack relations has been introduced in [23]. Since every stable extension wrt any ordinary attack relation is also stable wrt a normal attack relation, normal attack relations are proposed as a kind of normal form for stable semantics, i.e. a kind of a standard candidate for selection as their attack relation by those users/developers of structured argumentation who adopt the stable extensions as their semantics. An interesting question is whether or under which conditions normal attack relations capture the intended attack relations of prioritized rules wrt to any extension semantics, not just stable semantics. More precisely, we are interested in the question of whether normal attack relations satisfy the property of consistency-resolving and the principle of minimal removal and whether or under which conditions normal attack relations capture the canonical attack relations. As determining whether an argument normal-attacks another is both simple and efficient, this question is hence both theoretically interesting and practically relevant.
     </paragraph>
     <paragraph>
      When introducing preferences between defeasible rules, one key question is whether the introduced preferences are helpful and sensible. We introduce a class of well-prioritized systems and show that for this class, the canonical attack relation assignments and the normal attack relation assignment are identical. This result is important as determining whether an argument normal attacks another is very simple. Moreover we show that the canonical and normal attack relation assignments are equivalent wrt the stable semantics, i.e. they deliver the same sets of stable extensions.
     </paragraph>
     <paragraph>
      In order to provide a simpler and more focused presentation of the essential notions of our proposal, we first introduce them in the context of a basic system that is expanded further later. In particular, we start with a language consisting only of literals and two type of attacks, rebut and undercut. We then show that our approach can easily be scaled up by showing that all key results still hold for general underlying logical languages and the inclusion of assumptions.
     </paragraph>
     <paragraph>
      The paper is organized as follows. We recall in the next section the key concepts and notions of argumentation and defeasible knowledge bases on which the paper is based. We then introduce the important property of inconsistency-resolving and discuss sufficient conditions for the postulates of consistency and closure. In section 4, we introduce the concepts of regular attack relations and regular attack relation assignments. In section 5, we study the semilattice of regular attack relation assignments and propose the canonical attack relations. We formalize the minimal removal intuition by providing a least fixed-point characterization of the canonical attack relation assignments in section 6. We study a relevant class of well-prioritized rule-based systems for which canonical attack relations and normal attack relations coincide in section 7. We discuss the relationship of our approach to others in section 8. We show in section 9 that our approach can easily be scaled up for general underlying logical languages and the inclusion of assumptions. We conclude in section 10.{sup:5} For ease of reading, the graph in Fig. 3 indicates the dependency between the sections.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <section label="2.1">
      <section-title>
       Abstract argumentation
      </section-title>
      <paragraph>
       An abstract argumentation framework [29] is defined simply as a pair {a mathematical formula}AF=(AR,att) where AR is a set of arguments and {a mathematical formula}att⊆AR×AR and {a mathematical formula}(A,B)∈att means that A attacks B.
      </paragraph>
      <paragraph>
       A set of arguments S attacks (or is attacked by) an argument A (or a set of arguments R) if some argument in S attacks (or is attacked by) A (or some argument in R); S is conflict-free if it does not attack itself. A set of arguments S defends an argument A if S attacks each argument attacking A.
      </paragraph>
      <paragraph>
       S is admissible if S is conflict-free and defends each argument in it. A complete extension is an admissible set of arguments containing each argument it defends. A preferred extension is a maximal admissible set of arguments. A stable extension is a conflict-free set of arguments that attacks every argument not belonging to it. It is well-known that both preferred and stable extensions are complete but not vice versa.
      </paragraph>
      <paragraph>
       The characteristic function of AF is defined by{a mathematical formula} Since {a mathematical formula}FAF is a monotonic function, there exists a least fixed point of {a mathematical formula}FAF. The grounded extension is defined as the least fixed point of {a mathematical formula}FAF. As complete extensions coincide with conflict-free fixed points of {a mathematical formula}FAF, the grounded extension is also the least complete extension.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Defeasible knowledge bases
      </section-title>
      <paragraph>
       In this section, we recall the basic notions and notations on knowledge bases from [23]. We assume a non-empty set {a mathematical formula}L of ground atoms (also called a positive literal) and their classical negations (also called negative literals). A set of literals is said to be contradictory iff it contains an atom a and its negation ¬a. The complement of a positive literal α is ¬α while the complement of a negative literal ¬α is α. Abusing the notation slightly, we denote the complement of any literal λ by ¬λ.
      </paragraph>
      <paragraph>
       We distinguish between domain atoms representing propositions about the concerned domains and non-domain atoms of the form {a mathematical formula}abd representing the non-applicability of defeasible rules d (even if the premises of d hold).
      </paragraph>
      <paragraph>
       We denote by {a mathematical formula}Ldom the set of all domain literals.
      </paragraph>
      <paragraph>
       We distinguish between strict and defeasible rules as often done in the literature [43], [44], [37], [38], [52], [23]. A defeasible (resp. strict) rule r is of the form {a mathematical formula}b1,…,bn⇒h (resp. {a mathematical formula}b1,…,bn→h) where {a mathematical formula}b1,…,bn∈Ldom and {a mathematical formula}h∈Ldom or h is an atom of the form {a mathematical formula}abd. The set {a mathematical formula}{b1,…,bn} (resp. h) is referred to as the body (resp. head) of r and denoted by bd(r) (resp. hd(r)).
      </paragraph>
      <paragraph label="Definition 1">
       <list>
        <list-item label="1.">
         A rule-based system is a triple {a mathematical formula}R=(RS,RD,⪯) where
        </list-item>
        <list-item label="2.">
         A knowledge base is defined as a pair {a mathematical formula}K=(R,BE) consisting of a rule-based system {a mathematical formula}R, and a set {a mathematical formula}BE⊆Ldom, the base of evidence of K, representing unchallenged observations, facts etc.{sup:6}For convenience, knowledge base K is often written directly as a quadruple {a mathematical formula}(RS,RD,⪯,BE) where the components RS, RD, ⪯ or BE are often referred to by {a mathematical formula}RSK,RDK,⪯K or {a mathematical formula}BEK respectively.
        </list-item>
        <list-item label="3.">
         A knowledge base K is basic if its precedence relation is empty (i.e. {a mathematical formula}⪯K=∅).
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       A knowledge base is essentially a defeasible theory in [17] together with a set of preferences between defeasible rules where following Modgil&amp;Prakken [43] we separate the evidence base from the set of rules. The separation is necessary as many key properties of attack relations (like the properties of context-independence (Definition 17) or credulous cumulativity (section 8.2) are defined across distinct knowledge bases with the same set of rules.{sup:7} A knowledge base is an argumentation theory as defined in [43] with only one kind of (classical) negation (another type of negation is added later in section 9).
      </paragraph>
      <paragraph label="Definition 2">
       Let {a mathematical formula}K=(RS,RD,⪯,BE) be a knowledge base. An argument wrt K is a proof tree defined inductively as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        For each {a mathematical formula}α∈BE, {a mathematical formula}[α] is an argument with conclusion α.
       </list-item>
       <list-item label="2.">
        Let r be a rule of the forms {a mathematical formula}α1,…,αn→/⇒α, {a mathematical formula}n≥0, from {a mathematical formula}RS∪RD and {a mathematical formula}A1,…,An be arguments with conclusions {a mathematical formula}αi, {a mathematical formula}1≤i≤n, respectively. Then {a mathematical formula}A=[A1,…,An,r] is an argument with conclusion α and last rule r denoted by {a mathematical formula}cnl(A) and {a mathematical formula}last(A) respectively.Note that for argument of the form {a mathematical formula}[α], {a mathematical formula}α∈BE, {a mathematical formula}last([α]) is not defined.
       </list-item>
       <list-item label="3.">
        Each argument wrt K is obtained by applying the above steps 1, 2 finitely many times.
       </list-item>
      </list>
      <paragraph label="Example 3">
       Consider a knowledge base K (adapted from [15], [16], [23]), consisting of three defeasible rules{a mathematical formula} and two strict rules{a mathematical formula} together with a precedence relation consisting of just {a mathematical formula}d2≺d3. Suppose we know some dean who is also a professor.The considered knowledge base is represented by {a mathematical formula}K=(RS,RD,⪯,BE) with {a mathematical formula}RS={r,r′}, {a mathematical formula}RD={d1,d2,d3}, {a mathematical formula}⪯={(d2,d3)} and {a mathematical formula}BE={D,P}.{sup:8}Relevant arguments can be found in Fig. 4 where {a mathematical formula}A1=[[D],d1], {a mathematical formula}A2=[A1,d2], {a mathematical formula}A2′=[[P],d2], {a mathematical formula}A3=[[[D],r],d3].
      </paragraph>
      <paragraph label="Notation 1">
       <list>
        <list-item label="1.">
         The set of all arguments wrt a knowledge base K is denoted by {a mathematical formula}ARK. The set of the conclusions of arguments in a set {a mathematical formula}S⊆ARK is denoted by {a mathematical formula}cnl(S).
        </list-item>
        <list-item label="2.">
         A strict argument is an argument containing no defeasible rule. An argument is defeasible iff it is not strict. A defeasible argument A is called basic defeasible iff {a mathematical formula}last(A) is defeasible.
        </list-item>
        <list-item label="3.">
         For any argument A, the set of defeasible rules appearing in A is denoted by {a mathematical formula}dr(A). The set of last defeasible rules in A, denoted by {a mathematical formula}ldr(A), is {a mathematical formula}{last(A)} if A is basic defeasible, otherwise it is equal {a mathematical formula}ldr(A1)∪…∪ldr(An) where {a mathematical formula}A=[A1,…,An,r].
        </list-item>
        <list-item label="4.">
         An argument B is a subargument of an argument A iff {a mathematical formula}B=A or {a mathematical formula}A=[A1,…,An,r] and B is a subargument of some {a mathematical formula}Ai. B is a proper subargument of A if B is a subargument of A and {a mathematical formula}B≠A.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Definition 3">
       Let K be a knowledge base and {a mathematical formula}X⊆L and {a mathematical formula}l∈L. Further let {a mathematical formula}Xdom=X∩Ldom.{sup:9}
      </paragraph>
      <list>
       <list-item label="1.">
        We say that l is strictly derived from X wrt K, denoted by {a mathematical formula}X⊢Kl, iff {a mathematical formula}l∈X or l is the conclusion of an argument constructed according to Definition 2 where in step 1 only elements from {a mathematical formula}Xdom are used and in step 2, only the strict rules from K are used.
       </list-item>
       <list-item label="2.">
        The closure of a set {a mathematical formula}X⊆L wrt knowledge base K, denoted by {a mathematical formula}CNK(X), is defined by {a mathematical formula}CNK(X)={l|X⊢Kl}.
       </list-item>
       <list-item label="3.">
        X is said to be closed wrt K iff {a mathematical formula}X=CNK(X). X is said to be inconsistent wrt K iff its closure {a mathematical formula}CNK(X) is contradictory. X is consistent wrt K iff it is not inconsistent wrt K.
       </list-item>
       <list-item label="4.">
        K is said to be consistent iff its base of evidence {a mathematical formula}BEK is consistent wrt K.
       </list-item>
      </list>
      <paragraph>
       As the notions of closure, consistency depends only on the set of strict rules in the knowledge base, we often write {a mathematical formula}X⊢RSl or {a mathematical formula}l∈CNRS(X) for {a mathematical formula}X⊢Kl or {a mathematical formula}l∈CNK(X) respectively.
      </paragraph>
      <paragraph label="Definition 4">
       Let {a mathematical formula}R=(RS,RD,⪯) be a rule-based system and {a mathematical formula}K=(R,BE) be a knowledge base.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}R and K are said to be closed under transposition[17] iff for each strict rule of the form {a mathematical formula}b1,…,bn→h in RS s.t. {a mathematical formula}h∈Ldom, all the rules of the forms {a mathematical formula}b1,…,bi−1,¬h,bi+1,…,bn→¬bi, {a mathematical formula}1≤i≤n, also belong to RS.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}R and K are said to be closed under contraposition[47], [44] iff for each set {a mathematical formula}S⊆Ldom, each {a mathematical formula}λ∈Ldom, if {a mathematical formula}S⊢RSλ then for each {a mathematical formula}σ∈S, {a mathematical formula}S∖{σ}∪{¬λ}⊢RS¬σ.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}R and K are said to satisfy the self-contradiction property[27] iff for each minimal inconsistent set {a mathematical formula}X⊆Ldom, for each {a mathematical formula}x∈X, it holds: {a mathematical formula}X⊢RS¬x.
       </list-item>
      </list>
      <paragraph label="Lemma 1">
       Let{a mathematical formula}Rbe a rule-based system that is closed under transposition or contraposition. Then{a mathematical formula}Rsatisfies the property of self-contradiction.
      </paragraph>
      <paragraph label="Proof">
       A proof is given in [23]. To keep the paper self-contained, we recall the proof in Appendix A.  □
      </paragraph>
      <paragraph label="Definition 5">
       Attack relationAn attack relation for a knowledge base K is a relation {a mathematical formula}att⊆ARK×ARK such that there is no attack against strict arguments, i.e. for each strict argument {a mathematical formula}B∈ARK, there is no argument {a mathematical formula}A∈ARK such that {a mathematical formula}(A,B)∈att.For convenience, we often say A attacks B wrt att for {a mathematical formula}(A,B)∈att.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Basic postulates
      </section-title>
      <paragraph>
       We recall the postulates of consistency and closure from [17] and of subargument closure from [43], [1], [42].
      </paragraph>
      <paragraph label="Definition 6">
       Let att be an attack relation for a knowledge base K.
       <list>
        att is said to satisfy the consistency postulate iff for each complete extension E of {a mathematical formula}(ARK,att), the set {a mathematical formula}cnl(E) of conclusions of arguments in E is consistent.att is said to satisfy the closure postulate iff for each complete extension E of {a mathematical formula}(ARK,att), the set {a mathematical formula}cnl(E) of conclusions of arguments in E is closed.att is said to satisfy the subargument closure postulate iff for each complete extension E of {a mathematical formula}(ARK,att), E contains all subarguments of its arguments.For ease of reference, the above three postulates are often referred to as
       </list>
       <paragraph>
        basic postulates.
       </paragraph>
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Sufficient properties for basic postulates
     </section-title>
     <paragraph>
      As the basic postulates are more about the “output” of attack relations rather than about their structure, we present below two simple properties about the structure of attack relation that ensure the satisfaction of the basic postulates. We first recall two key notions of undercut and rebut from the literature [43], [45], [17].
     </paragraph>
     <paragraph label="Definition 7">
      <list>
       <list-item label="–">
        We say A undercuts B (at {a mathematical formula}B′) iff {a mathematical formula}B′ is a basic defeasible subargument of B and {a mathematical formula}cnl(A)=ablast(B′).We say A rebuts B (at {a mathematical formula}B′) iff {a mathematical formula}B′ is a basic defeasible subargument of B and the conclusions of A and {a mathematical formula}B′ are contradictory.
       </list-item>
       <list-item label="–">
        We say A directly attacks B iff A attacks B and A does not attack any proper subargument of B.
       </list-item>
       <list-item label="–">
        An argument A is said to be generated by a set S of arguments iff all basic defeasible subarguments of A are subarguments of arguments in S.
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      For an illustration of the notion of “being generated by a set of arguments”, consider {a mathematical formula}S={B0,B1} (see Fig. 5) and {a mathematical formula}A0. The set of basic defeasible subarguments of {a mathematical formula}A0 is {a mathematical formula}{[d0]}. It is clear that {a mathematical formula}[d0] is a subargument of {a mathematical formula}B0. Hence {a mathematical formula}A0 is generated by S. Similarly, {a mathematical formula}A1 is also generated by S.
     </paragraph>
     <paragraph label="Definition 8">
      Strong subargument structure{sup:10} Attack relation att is said to satisfy the property of strong subargument structure for K iff for all {a mathematical formula}A,B∈ARK, following conditions hold:
     </paragraph>
     <list>
      <list-item label="1.">
       A attacks B (wrt att) iff A attacks a basic defeasible subargument of B (wrt att).
      </list-item>
      <list-item label="2.">
       If A undercuts B then A attacks B wrt att.
      </list-item>
      <list-item label="3.">
       If A directly attacks B (wrt att) then A undercuts B (at B) or rebuts B (at B).
      </list-item>
     </list>
     <paragraph>
      We present the first result showing that strong subargument property is sufficient to guarantee the postulate of closure.
     </paragraph>
     <paragraph label="Lemma 2">
      Let att be an attack relation for knowledge base K satisfying the property of strong subargument structure. Further let E be a complete extension of{a mathematical formula}(ARK,att).
     </paragraph>
     <list>
      <list-item label="1.">
       E contains all arguments generated by E, and
      </list-item>
      <list-item label="2.">
       att satisfies the postulates of closure and subargument closure.
      </list-item>
     </list>
     <paragraph label="Proof">
      Let {a mathematical formula}E′ be the set of all arguments generated by E. It is clear that
     </paragraph>
     <list>
      <list-item label="–">
       {a mathematical formula}E⊆E′, and
      </list-item>
      <list-item label="–">
       the sets of basic defeasible subarguments of arguments in E and {a mathematical formula}E′ coincide.
      </list-item>
     </list>
     <paragraph>
      A set S of arguments of a knowledge base K is said to be inconsistent (resp. consistent) (wrt K) if the set of the conclusions of its arguments, {a mathematical formula}cnl(S), is inconsistent (resp. consistent) (wrt K). We often ignore K if there are no possibilities for misunderstanding.
     </paragraph>
     <paragraph>
      We introduce below a new simple property of inconsistency resolving that could be viewed as an adaptation of the consistency-covering property in [27] to structured argumentation systems.
     </paragraph>
     <paragraph label="Definition 9">
      Inconsistency resolvingWe say attack relation att satisfies the inconsistency-resolving property for K iff for each finite set of arguments {a mathematical formula}S⊆ARK, if S is inconsistent then S is attacked (wrt att) by some argument generated by S.
     </paragraph>
     <paragraph>
      As we will show later, the inconsistency-resolving property is satisfied by common conditions like closure under transposition or contradiction or the property of self-contradiction.
     </paragraph>
     <paragraph label="Example 4">
      Consider the basic knowledge base K consisting of just the rules appearing in arguments in Fig. 5. The set {a mathematical formula}S={B0,B1} is inconsistent. The argument {a mathematical formula}A0 is generated by S. Let {a mathematical formula}att={(X,Y)|X rebuts Y}. It is obvious that S is attacked by {a mathematical formula}A0.We show that att is inconsistency-resolving. Let {a mathematical formula}A⊆ARK. Suppose {a mathematical formula}A is inconsistent. It is clear that if only one defeasible rule appears in arguments in {a mathematical formula}A then {a mathematical formula}A is not inconsistent. Therefore both {a mathematical formula}d0,d1 appear in {a mathematical formula}A. Therefore {a mathematical formula}A0 is generated by {a mathematical formula}A. {a mathematical formula}A0 rebuts any argument containing {a mathematical formula}d1. Hence att is inconsistency-resolving.
     </paragraph>
     <paragraph>
      We present now the first important result.
     </paragraph>
     <paragraph label="Theorem 1">
      Let{a mathematical formula}att,att′be attack relations for knowledge base K.
     </paragraph>
     <list>
      <list-item label="1.">
       If{a mathematical formula}att⊆att′and att is inconsistency-resolving for K then{a mathematical formula}att′is also inconsistency-resolving for K.
      </list-item>
      <list-item label="2.">
       If att satisfies the strong subargument structure and inconsistency-resolving then att satisfies the postulate of consistency.
      </list-item>
     </list>
     <paragraph label="Proof">
      Assertion 1 follows easily from the definition of inconsistency-resolving. We show assertion 2. Suppose E is a complete extension of {a mathematical formula}(ARK,att). From condition 1 in Lemma 2, each argument generated by E belongs to E. Since att is inconsistency-resolving, if E is inconsistent then E is not conflict-free. Since E is conflict-free, E is hence consistent.  □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Regular attack relation assignments
     </section-title>
     <paragraph>
      In general, attack relations satisfying the basic postulates do not capture the semantics of prioritized rules. To see this point, consider a simple knowledge base consisting of exactly two defeasible rules {a mathematical formula}d0:⇒a and {a mathematical formula}d1⇒¬a with {a mathematical formula}d0≺d1. There are only two arguments {a mathematical formula}A0,A1 as given in Fig. 6.
     </paragraph>
     <paragraph>
      The attack relation {a mathematical formula}att={(A0,A1),(A1,A0)} has two preferred (also stable) extensions {a mathematical formula}Ei={Ai}, {a mathematical formula}i=0,1. It is obvious that {a mathematical formula}E0 satisfies both properties of inconsistency-resolving and strong subargument structure. As the prime purpose of the preference of {a mathematical formula}d1 over {a mathematical formula}d0 is to rule out extension {a mathematical formula}E0, attack relation att does not capture the expected semantics.
     </paragraph>
     <paragraph>
      Dung [30], [23] has proposed several simple properties referred to as ordinary properties, to capture the intuition of prioritized rules. We recall and adapt them below. We also motivate and explain their intuitions. We then present two novel concepts of regular attack relations and regular attack relation assignments that lie at the heart of the semantics of prioritized rules.
     </paragraph>
     <section label="4.1">
      <section-title>
       A minimal interpretation of priorities
      </section-title>
      <paragraph>
       We first recall from [23] the effective rebut property stating a “minimal interpretation” of a preference {a mathematical formula}d0≺d1 that in situations when both are applicable but accepting both {a mathematical formula}d0,d1 is not possible, {a mathematical formula}d1 should be preferred.
      </paragraph>
      <paragraph label="Definition 10">
       Effective rebutWe say that attack relation att satisfies the effective rebut property for a knowledge base K iff for all arguments {a mathematical formula}A0,A1∈ARK such that each {a mathematical formula}Ai, {a mathematical formula}i=0,1, contains exactly one defeasible rule {a mathematical formula}di (i.e. {a mathematical formula}dr(Ai)={di}), and {a mathematical formula}A0 rebuts {a mathematical formula}A1, it holds that {a mathematical formula}A0 attacks {a mathematical formula}A1 wrt att iff {a mathematical formula}d0⊀d1.
      </paragraph>
      <paragraph>
       In Fig. 6, the effective rebut property dictates that {a mathematical formula}A1 attacks {a mathematical formula}A0 but not vice versa.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Propagating attacks
      </section-title>
      <paragraph label="Example 5">
       Consider the knowledge base in Example 3.While the effective rebut property determines that {a mathematical formula}A3 attacks {a mathematical formula}A2′ (see Fig. 4) but not vice versa (because {a mathematical formula}d2≺d3), it does not say whether {a mathematical formula}A3 attack {a mathematical formula}A2.Looking at the structure of {a mathematical formula}A2,A2′, we can say that {a mathematical formula}A2 is a weakening of {a mathematical formula}A2′ as the undisputed fact P on which {a mathematical formula}A2′ is based is replaced by a defeasible belief P (supported by argument {a mathematical formula}A1). Therefore if {a mathematical formula}A3 attacks {a mathematical formula}A2′ then it is natural to expect that {a mathematical formula}A3 should attack {a mathematical formula}A2 too.The above analysis also shows that attacks generated by the effective rebut property, could be propagated to other arguments based on a notion of weakening of arguments. We recall this notion as well as the associated property of attack monotonicity from [23] below.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}A,B∈ARK and {a mathematical formula}AS⊆ARK. Intuitively, B is a weakening of A by AS if B is obtained by replacing zero, one or more premises of A by arguments in AS whose conclusions coincide with the premises.
      </paragraph>
      <paragraph label="Definition 11">
       Let {a mathematical formula}A,B∈ARK and {a mathematical formula}AS⊆ARK. B is said to be a weakening of A by AS iff
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}A=[α] for {a mathematical formula}α∈BE, and ({a mathematical formula}B=[α] or {a mathematical formula}B∈AS with {a mathematical formula}cnl(B)=α), or
       </list-item>
       <list-item label="2.">
        {a mathematical formula}A=[A1,…,An,r] and {a mathematical formula}B=[B1,…,Bn,r] where each {a mathematical formula}Bi is a weakening of {a mathematical formula}Ai by AS.By {a mathematical formula}A↓AS we denote the set of all weakenings of A by AS.For simplicity, we often say that A is a strengthening of B by AS if B is a weakening of A by AS.
       </list-item>
      </list>
      <paragraph>
       For an illustration, consider again the arguments in Fig. 4. It is clear that {a mathematical formula}[P]↓{A1}={[P],A1}, {a mathematical formula}A2′↓{A1}={A2′,A2}. In Fig. 1, {a mathematical formula}Ni↓{[⇒inno(S)]}={Ni,Ni′}, {a mathematical formula}i=1,2.
      </paragraph>
      <paragraph>
       The attack monotonicity property states that if an argument A attacks an argument B then A also attacks all weakenings of B. Moreover if a weakening of A attacks B then A also attacks B.
      </paragraph>
      <paragraph label="Definition 12">
       Attack monotonicityWe say attack relation att satisfies the property of attack monotonicity for knowledge base K iff for all {a mathematical formula}A,B∈ARK and for each weakening C of A, for each weakening D of B, the following assertions hold:
      </paragraph>
      <list>
       <list-item label="1.">
        If {a mathematical formula}(A,B)∈att then {a mathematical formula}(A,D)∈att.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}(C,B)∈att then {a mathematical formula}(A,B)∈att.
       </list-item>
      </list>
      <paragraph>
       We introduce below the property of attack modularity that can be intuitively related to the fact that in a real world conversation, if you claim that my argument is wrong, I would naturally ask which part of my argument is wrong. For an illustration, consider Fig. 7. Suppose C is the argument consisting of B and arguments {a mathematical formula}B0,B1 that support some premises of B. It follows that {a mathematical formula}C∈B↓{B0,B1}. Suppose A attacks C. As C is composed by {a mathematical formula}B,B0,B1, we would expect that A would attack one of the components {a mathematical formula}B,B0,B1 of C. In other words, we expect the attack to be modular in the sense if A attacks an argument then A should attack one of its components. The link-oriented property introduced in [23] represents this intuition. As the formal definition of the “link-orientation” property does not reflect directly the modularity intuition of the property, we introduce an equivalent version of it below and then show their equivalence.
      </paragraph>
      <paragraph label="Definition 13">
       Modularity of attacksWe say that attack relation att satisfies the property of modularity for K iff for all arguments {a mathematical formula}A,B,C∈ARK such that A attacks C where
      </paragraph>
      <list>
       <list-item label="1.">
        C is a weakening of B by {a mathematical formula}AS⊆ARK, and
       </list-item>
       <list-item label="2.">
        C is not a weakening of B by any proper subset of AS,
       </list-item>
      </list>
      <paragraph>
       We recall the property of link-orientation below and then show its equivalence to the property of modularity of attacks.
      </paragraph>
      <paragraph label="Definition 14">
       Link-orientationWe say that attack relation att satisfies the property of link-orientation for K iff for all arguments {a mathematical formula}A,B,C∈ARK such that C is a weakening of B by {a mathematical formula}AS⊆ARK, it holds that if A attacks C (wrt att) and A does not attack any argument in AS (wrt att) then A attacks B (wrt att).
      </paragraph>
      <paragraph label="Lemma 3">
       An attack relation att satisfies the property of modularity for K iff att satisfies the property of link-orientation for K.
      </paragraph>
      <paragraph label="Proof">
       If A attacks some argument in AS, we are done. Suppose A does not attack any argument in AS. From the link-orientation property, we have A attacks B (wrt att), i.e. the modularity is satisfied if link-orientation holds.  □
      </paragraph>
      <paragraph label="Example 6">
       Consider again arguments in Fig. 4. Suppose {a mathematical formula}d2 is now preferred to {a mathematical formula}d3 (i.e. {a mathematical formula}d3≺d2). The effective rebut property dictates that {a mathematical formula}A3 does not attack {a mathematical formula}A2′. Does {a mathematical formula}A3 attack {a mathematical formula}A2? Suppose {a mathematical formula}A3 attacks {a mathematical formula}A2. Since {a mathematical formula}A3 does not attack {a mathematical formula}A1 that is a subargument of {a mathematical formula}A2, we expect that {a mathematical formula}A3 should attack some other part of {a mathematical formula}A2. In other words, we expect that {a mathematical formula}A3 attacks {a mathematical formula}A2′. But this is a contradiction to the effective rebut property stating that {a mathematical formula}A2′ attack {a mathematical formula}A3 but not vice versa. Hence {a mathematical formula}A3 does not attack {a mathematical formula}A2.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Attack relation assignments: propagating attacks across knowledge bases
      </section-title>
      <paragraph>
       While the properties of inconsistency-resolving, strong subargument structure, effective rebuts, attack monotonicity and link-orientation are natural and intuitive, they are still not sufficient for determining an intuitive attack relations wrt prioritized rules. The example below illustrates this point.
      </paragraph>
      <paragraph label="Example 7">
       Consider a knowledge base {a mathematical formula}K0 obtained from knowledge base K in Example 3 by revising the evidence base to {a mathematical formula}BE={D}. It is clear that arguments {a mathematical formula}A1,A2,A3 belong to {a mathematical formula}ARK0 while {a mathematical formula}A2′ is not an argument in {a mathematical formula}ARK0.As {a mathematical formula}A2′ does not belong to {a mathematical formula}ARK0, the effective rebut property does not “generate” any attacks between arguments in {a mathematical formula}ARK0. How could we determine the attack relation for {a mathematical formula}K0?As both {a mathematical formula}A2,A3 belong to both {a mathematical formula}ARK, {a mathematical formula}ARK0 and the two knowledge bases {a mathematical formula}K0,K have identical rule-based system, we expect that the attack relations between their common arguments should be identical. In other words, because {a mathematical formula}A3 attacks {a mathematical formula}A2 wrt K (see Example 5), {a mathematical formula}A3 should attack {a mathematical formula}A2 also wrt {a mathematical formula}K0. This intuition is captured by the context-independence property [23] linking attack relations between arguments across the boundary of knowledge bases.The example also indicates that attack relations of knowledge bases with the same rule-based system should be considered together. This motivates the introduction of the attack relation assignment in Definition 15, Definition 16.
      </paragraph>
      <paragraph label="Definition 15">
       Let {a mathematical formula}R=(RS,RD,⪯) be a rule-based system. The class consisting of all consistent knowledge bases of the form {a mathematical formula}(R,BE) is denoted by {a mathematical formula}CR.
      </paragraph>
      <paragraph label="Assumption">
       From now on, whenever we mention a rule-based system {a mathematical formula}R, we mean a consistent one, i.e. {a mathematical formula}CR≠∅.{sup:12}
      </paragraph>
      <paragraph label="Definition 16">
       Attack relation assignmentAn attack relation assignment atts for a rule-based system {a mathematical formula}R is a function assigning to each knowledge base {a mathematical formula}K∈CR an attack relation {a mathematical formula}atts(K)⊆ARK×ARK.{sup:13}{sup:,}{sup:14}
      </paragraph>
      <paragraph>
       We next recall the context-independence property from [23] stating that the attack relation between two arguments depends only on the rules appearing in them and their preferences.
      </paragraph>
      <paragraph label="Definition 17">
       Context-independenceWe say attack relation assignment atts for a rule-based system {a mathematical formula}R satisfies the property of context-independence iff for any two knowledge bases {a mathematical formula}K,K′∈CR and for any two arguments A, B from {a mathematical formula}ARK∩ARK′, it holds that {a mathematical formula}(A,B)∈atts(K) iff (A,B)∈atts(K′).
      </paragraph>
      <paragraph>
       The context-independence property is commonly accepted in many well-known argument-based systems like the assumption-based framework [12], [32] and the ASPIC+ approach [47], [43].
      </paragraph>
      <paragraph label="Notation 2">
       <list>
        <list-item label="–">
         For ease of reference, we refer to the property of context-independence as well as the properties of inconsistency-resolving, strong subargument structure, effective rebuts, attack monotonicity and link-orientation as regular properties.
        </list-item>
        <list-item label="–">
         Let P be a regular property different to the context-independence one.We say an attack relation assignment atts satisfies P iff for each knowledge base {a mathematical formula}K∈CR, {a mathematical formula}atts(K) satisfies P.
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       We can now present two novel concepts of weakly regular and regular attack relation assignments.
      </paragraph>
      <paragraph label="Definition 18">
       <section-title>
        Regular attack relation assignments
       </section-title>
      </paragraph>
      <list>
       <list-item label="1.">
        An attack relation assignment {a mathematical formula}atts for a rule-based system {a mathematical formula}R is said to be weakly regular iff it satisfies the regular properties of context-independence, strong subargument structure, effective rebuts, attack monotonicity and link-orientation.The set of all weakly regular attack relation assignments for {a mathematical formula}R is denoted by {a mathematical formula}WRAAR.
       </list-item>
       <list-item label="2.">
        A weakly regular attack relation assignment {a mathematical formula}atts for a rule-based system {a mathematical formula}R is said to be regular iff it satisfies the inconsistency-resolving property.The set of all regular attack relation assignments for {a mathematical formula}R is denoted by {a mathematical formula}RAAR.
       </list-item>
      </list>
      <paragraph>
       It is obvious that {a mathematical formula}RAAR⊆WRAAR holds.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      The complete upper-semilattice of regular attack relation assignments
     </section-title>
     <section label="5.1">
      <section-title>
       Preliminaries: complete semilattice
      </section-title>
      <paragraph>
       We introduce the concept of semilattice. A partial order{sup:15} ≤ on a set S is a upper-semilattice (resp. lower-semilattice) [21], [53] iff each pair of elements {a mathematical formula}x,y from S has a supremum (resp. infimum) wrt ≤.
      </paragraph>
      <paragraph>
       An upper-semilattice (resp. lower-semilattice) is complete iff each non-empty subset of S has a supremum (resp. infimum).{sup:16}
      </paragraph>
      <paragraph>
       It follows immediately that each complete upper (resp. lower) semilattice S has a unique greatest (resp. least) element.{sup:17}
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Semilattice structure of regular attack relation assignments
      </section-title>
      <paragraph>
       From now on until the end of this section, we assume an arbitrary but fixed rule-based system {a mathematical formula}R=(RS,RD,⪯).
      </paragraph>
      <paragraph label="Definition 19">
       Let {a mathematical formula}A be a non-empty set of attack relation assignments. Define {a mathematical formula}⋃A by:{a mathematical formula}
      </paragraph>
      <paragraph>
       The following simple lemma and theorem present a deep insight into the structure of regular attack assignments.
      </paragraph>
      <paragraph label="Lemma 4">
       Let{a mathematical formula}Abe a non-empty set of attack relation assignments.
      </paragraph>
      <list>
       <list-item label="1.">
        Suppose P is a regular property and every attack relation assignment{a mathematical formula}atts∈Asatisfies P. Then{a mathematical formula}⋃Aalso satisfies P.
       </list-item>
       <list-item label="2.">
        If the attack relation assignments in{a mathematical formula}Aare regular then{a mathematical formula}⋃Ais also regular.
       </list-item>
       <list-item label="3.">
        If the attack relation assignments in{a mathematical formula}Aare weakly regular then{a mathematical formula}⋃Ais also weakly regular.
       </list-item>
      </list>
      <paragraph label="Proof">
       See Appendix B.  □
      </paragraph>
      <paragraph>
       For attack relation assignments {a mathematical formula}atts,atts′, define {a mathematical formula}atts⊆atts′ iff {a mathematical formula}∀K∈CR, {a mathematical formula}atts(K)⊆atts′(K).
      </paragraph>
      <paragraph>
       From Lemma 4, the following Theorem 2 holds obviously.
      </paragraph>
      <paragraph label="Theorem 2">
       Suppose the set{a mathematical formula}RAARof regular attack relation assignments is not empty. Then{a mathematical formula}(RAAR,⊆)is a complete upper-semilattice. □
      </paragraph>
      <paragraph label="Definition 20">
       Suppose the set {a mathematical formula}RAAR of all regular attack relation assignments for {a mathematical formula}R is not empty. The canonical attack relation assignment of {a mathematical formula}R denoted by {a mathematical formula}AttR is defined by: {a mathematical formula}AttR=⋃RAAR.
      </paragraph>
      <paragraph>
       Even though in general, regular attack relation assignments (and hence the canonical one) may not exist (as the Example 8 below shows), they exist under natural conditions that we believe most practical rule-based systems satisfy, like the property of self-contradiction or closure under transposition or contraposition as proved in Theorem 3 below.
      </paragraph>
      <paragraph label="Example 8">
       Consider a rule-based system {a mathematical formula}R consisting of {a mathematical formula}d0:⇒ad1:⇒br:a→¬b and {a mathematical formula}d0≺d1. Suppose atts be a regular attack relation assignment for {a mathematical formula}CR. Let {a mathematical formula}K=(R,∅). The contradicting arguments for K are given in Fig. 8. From the property of effective rebut, it is clear that {a mathematical formula}(A,B)∉atts(K). Hence {a mathematical formula}atts(K)=∅. The inconsistency-resolving property is not satisfied by {a mathematical formula}atts(K), contradicting the assumption that atts is regular. Therefore there exists no regular attack relation assignment for {a mathematical formula}CK.
      </paragraph>
      <paragraph>
       While regular attack relation assignments may not exist, weakly regular ones always exist. It turns out that a special type of attack relations, the normal attack relations introduced in [23] are always weakly regular. If the rule-based systems is closed under transposition or contraposition or self-contradiction then normal attack relation assignments are regular.
      </paragraph>
      <paragraph label="Definition 21">
       Let K be a knowledge base and {a mathematical formula}A,B∈ARK.
      </paragraph>
      <list>
       <list-item label="1.">
        We say that A normal-rebuts B (at X) iff A rebuts B (at X) and there is no defeasible rule {a mathematical formula}d∈ldr(A) such that {a mathematical formula}d≺last(X).
       </list-item>
       <list-item label="2.">
        The normal attack relation assignment{a mathematical formula}attsnr is defined by: For any knowledge base {a mathematical formula}K∈R and any arguments {a mathematical formula}A,B∈ARK, {a mathematical formula}(A,B)∈attsnr(K) if and only if A undercuts B or A normal-rebuts B.
       </list-item>
      </list>
      <paragraph>
       Before presenting a central result in Theorem 3 below, let us introduce some helpful notations.
      </paragraph>
      <paragraph label="Notation 3">
       <list>
        <list-item label="–">
         A maximal basic defeasible subargument of B is a basic defeasible subargument of B that is not a proper subargument of any basic defeasible subargument of B.
        </list-item>
        <list-item label="–">
         A maximal proper subargument of B is a proper subargument of B that is not a proper subargument of any proper subargument of B.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Theorem 3">
       <list>
        <list-item label="1.">
         For any rule-based system{a mathematical formula}R, the normal attack relation assignment{a mathematical formula}attsnris weakly regular.
        </list-item>
        <list-item label="2.">
         Suppose the rule-based system{a mathematical formula}Rsatisfies the self-contradiction property. Then the normal attack relation assignment{a mathematical formula}attsnris regular and the canonical assignment{a mathematical formula}AttRexists and{a mathematical formula}attsnr⊆AttR.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       See Appendix B.  □
      </paragraph>
      <paragraph>
       The following lemma follows immediately from the above Theorem 3.
      </paragraph>
      <paragraph label="Lemma 5">
       <list>
        <list-item label="1.">
         {a mathematical formula}(WRAAR,⊆)is a complete upper-semilattice whose supremum is denoted by{a mathematical formula}WattR.
        </list-item>
        <list-item label="2.">
         If the canonical attack relation assignment{a mathematical formula}AttRexists, it holds:{a mathematical formula}
        </list-item>
        <list-item label="3.">
         If{a mathematical formula}Rsatisfies the self-contradiction property then{a mathematical formula}AttRexists and{a mathematical formula}AttR=WattR.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       As normal attack relation assignments are weakly regular (Theorem 3). {a mathematical formula}WRAAR is hence not empty. Assertion 1 follows then from Lemma 4.We prove assertion 2. If {a mathematical formula}AttR exists then it is weakly regular and hence {a mathematical formula}AttR⊆WattR. From the first assertion in Theorem 1, it follows immediately that {a mathematical formula}WattR also satisfies the inconsistency-resolving property. Therefore {a mathematical formula}WattR is regular. Hence {a mathematical formula}WattR⊆AttR. Thus {a mathematical formula}WattR=AttR.Assertion 3 follows immediately from second assertion and the second statement in Theorem 3.  □
      </paragraph>
      <paragraph>
       The following lemma follows immediately from the second statement of Theorem 3.
      </paragraph>
      <paragraph label="Lemma 6">
       Suppose the rule-based system{a mathematical formula}Rsatisfies the self-contradiction property. Let{a mathematical formula}K∈CRand{a mathematical formula}A,B∈ARKsuch that A rebuts B (at B) and{a mathematical formula}(A,B)∉AttR(K). Then there is{a mathematical formula}d∈ldr(A)such that{a mathematical formula}d≺last(B).
      </paragraph>
      <paragraph>
       We show below that when all defeasible rules are “equal”, i.e. there are no preferences among them, the canonical attack relations coincide with the basic attack relations that are fully determined by undercuts and rebuts. We study further characteristics of canonical attack relations in the following two sections.
      </paragraph>
      <paragraph label="Definition 22">
       The basic attack relation assignment for a rule-based system {a mathematical formula}R, denoted by {a mathematical formula}Batts is defined by:{a mathematical formula}
      </paragraph>
      <paragraph label="Lemma 7">
       <list>
        <list-item label="1.">
         {a mathematical formula}Battssatisfies all regular properties except the inconsistency-resolving and effective rebut properties.
        </list-item>
        <list-item label="2.">
         If{a mathematical formula}Rsatisfies the self-contradiction property then{a mathematical formula}Battssatisfies the inconsistency-resolving property.
        </list-item>
        <list-item label="3.">
         If{a mathematical formula}Ris basic then{a mathematical formula}Battssatisfies the effective rebut property and hence is weakly regular and{a mathematical formula}Batts=WattR.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       See Appendix B.  □
      </paragraph>
      <paragraph>
       From Lemma 7, the following theorem holds obviously.
      </paragraph>
      <paragraph label="Theorem 4">
       If{a mathematical formula}Ris basic and satisfies the self-contradiction property then{a mathematical formula}Battscoincides with the canonical attack relation assignment of{a mathematical formula}R. □
      </paragraph>
      <paragraph>
       The following Lemma 8 states that {a mathematical formula}(RAAR,⊆) is not a complete lattice by showing that it is not a lower-semilattice.
      </paragraph>
      <paragraph label="Lemma 8">
       In general,{a mathematical formula}(RAAR,⊆)is not a lower-semilattice.
      </paragraph>
      <paragraph label="Proof">
       Consider a rule-based system {a mathematical formula}R consisting of only four defeasible rules{a mathematical formula} and there is no preferences between the defeasible rules.Let {a mathematical formula}A,B,D,C be the arguments given in Fig. 9.Define two attack relation assignments {a mathematical formula}atts,atts′ for {a mathematical formula}R as follows.
       <list>
        For {a mathematical formula}K∈CR, {a mathematical formula}atts(K)=Batts(K)∖{(D,A),(D,B)}.For {a mathematical formula}K∈CR, {a mathematical formula}atts′(K)=Batts(K)∖{(A,D),(A,C)}.In
       </list>
       <paragraph>
        Appendix G, we show that both {a mathematical formula}atts,atts′ are regular.We show now that there exists no infimum of {a mathematical formula}atts,atts′ in {a mathematical formula}(RAAR,⊆).Suppose on the contrary the infimum of {a mathematical formula}atts,atts′ in {a mathematical formula}(RAAR,⊆) exists. Let it be denoted by {a mathematical formula}atts0. It is clear that for any {a mathematical formula}K∈CR, {a mathematical formula}{(A,D),(D,A)}∩atts0(K)=∅.Let {a mathematical formula}BE0={a,d} and {a mathematical formula}K0=(R,BE0).It is clear that {a mathematical formula}ARK0 consists only of arguments in Fig. 10.Therefore {a mathematical formula}atts0(K0)=∅. It is obvious that {a mathematical formula}atts0(K0) does not satisfy the inconsistency-resolving property. Thus {a mathematical formula}atts0 is not regular. Contradiction. □
       </paragraph>
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Minimal removal semantics: a least-fixed-point characterization of canonical attack relation
     </section-title>
     <paragraph>
      From the strong subargument structure property, it is clear that {a mathematical formula}AttR⊆Batts. In other words, {a mathematical formula}∀K∈CR, the set {a mathematical formula}Batts(K)∖AttR(K) could be viewed as the set of attacks removed from {a mathematical formula}Batts(K) due to the priorities between defeasible rules.
     </paragraph>
     <paragraph label="Example 9">
      In general, a contra-positive reading of the regular properties propagates the removal of attacks that are at first removed by the introduction of priorities between defeasible rules.
     </paragraph>
     <paragraph>
      The discussion illustrates the idea that applying the regular properties in contrapositive forms could be viewed as “attack removal functions”. This view leads naturally to a least fixed-point characterization of canonical attack relation assignments. We formalize this insight in this section.
     </paragraph>
     <section label="6.1">
      <section-title>
       Preliminaries: complete lattice
      </section-title>
      <paragraph>
       A partial order ≤ on a set S is a complete lattice[21] iff each subset X of S has a supremum and infimum wrt ≤ denoted by ⊔X and ⊓X respectively. The greatest and least element of S are often denoted by ⊤, ⊥ respectively.
      </paragraph>
      <paragraph>
       A set {a mathematical formula}X⊆S is said to be directed[21] iff for each pair {a mathematical formula}x,y∈X there exists {a mathematical formula}z∈X such that {a mathematical formula}x≤z and {a mathematical formula}y≤z.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}(P,≤) be a complete lattice. A function {a mathematical formula}f:P→P is said to be
      </paragraph>
      <list>
       <list-item label="–">
        monotone iff for each {a mathematical formula}x,y∈P, if {a mathematical formula}x≤y then {a mathematical formula}f(x)≤f(y);
       </list-item>
       <list-item label="–">
        continuous iff for each directed subset {a mathematical formula}Δ⊆P, it holds:{a mathematical formula} where {a mathematical formula}f(Δ)={f(x)|x∈Δ}.
       </list-item>
      </list>
      <paragraph>
       It is not difficult to see that continuous functions are monotone.
      </paragraph>
      <paragraph>
       The following fixpoint theorem for continuous function is well-known. To keep the paper self-contained, we also recall the proof.
      </paragraph>
      <paragraph label="Theorem 5">
       Let{a mathematical formula}(P,≤)be a complete lattice and{a mathematical formula}f:P→Pbe continuous. Then f has a least fixpoint, denoted by lfp(f), of the form{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       It is obvious that {a mathematical formula}⊥≤f(⊥). Therefore {a mathematical formula}⊥≤f(⊥)≤f2(⊥)≤…. Let {a mathematical formula}γ=⊔i=0∞fi(⊥). Since f is continuous, it follows {a mathematical formula}f(γ)=f(⊔i=0∞fi(⊥))=⊔i=0∞f(fi(⊥))=⊔i=1∞fi(⊥)=γ. It is obvious that γ is the least fixpoint of f.  □
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Least-fixed-point minimal-removal
      </section-title>
      <paragraph>
       For {a mathematical formula}K∈CR, let {a mathematical formula}REBUTK be the set of all rebuts between arguments in {a mathematical formula}ARK, i.e.{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 23">
       A removal assignment is defined as a mapping assigning to each {a mathematical formula}K∈CR, a subset of {a mathematical formula}REBUTK representing a set of rebuts that should be removed.The set of all removal assignments is denoted by {a mathematical formula}REMASR.
      </paragraph>
      <paragraph>
       For {a mathematical formula}π,π′∈REMASR, define {a mathematical formula}π⊆π′ by: {a mathematical formula}π(K)⊆π′(K) for each {a mathematical formula}K∈CR;
      </paragraph>
      <paragraph>
       Further let {a mathematical formula}A⊆REMASR. Define {a mathematical formula}⋃A, {a mathematical formula}⋂A by
      </paragraph>
      <list>
       <list-item label="–">
        {a mathematical formula}∀K∈CR:(⋃A)(K)=⋃{π(K)|π∈A}
       </list-item>
       <list-item label="–">
        {a mathematical formula}∀K∈CR:(⋂A)(K)=⋂{π(K)|π∈A}
       </list-item>
      </list>
      <paragraph>
       It is obvious that {a mathematical formula}(REMASR,⊆)is a complete lattice where {a mathematical formula}⋃A, {a mathematical formula}⋂A represent the supremum and infimum of {a mathematical formula}A⊆REMASR wrt ⊆. The infimum of {a mathematical formula}(REMASR,⊆), that assigns the empty set of rebuts to each knowledge base {a mathematical formula}K∈CR, is denoted by {a mathematical formula}∅‾.
      </paragraph>
      <paragraph>
       We introduce below the attack removal functions according to a contra-positive reading of the regular properties.
      </paragraph>
      <paragraph>
       Let ER, AM, LO, SA, CI stand for effective rebuts, attack monotonicity, link-orientation, strong subargument structure and context-independence respectively.
      </paragraph>
      <paragraph label="Definition 24">
       The attack removal functions{a mathematical formula} are defined as follows:Let {a mathematical formula}K∈CR and {a mathematical formula}π∈REMASR.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}FER(π)(K) is the set of rebuts that have become ineffective (according to the effective rebut property) due to the introduction of the priorities between defeasible rules, i.e.{a mathematical formula}(A0,A1)∈FER(π)(K) iff {a mathematical formula}A0,A1∈ARK and each {a mathematical formula}Ai, {a mathematical formula}i=0,1, contains exactly one defeasible rule {a mathematical formula}di and {a mathematical formula}A0 rebuts {a mathematical formula}A1 and {a mathematical formula}d0≺d1.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}FAM(π)(K) is the set of rebuts that should be removed as the consequence of the removal of the rebuts in {a mathematical formula}π(K) according to a contrapositive reading of the attack monotonicity property, i.e.{a mathematical formula} where{a mathematical formula}
       </list-item>
       <list-item label="3.">
        {a mathematical formula}FLO(π)(K) is the set of rebuts that should be removed as the consequence of the removal of the rebuts in {a mathematical formula}π(K) according to a contrapositive reading of the link-orientation property, i.e.{a mathematical formula}
       </list-item>
       <list-item label="4.">
        {a mathematical formula}FCI(π)(K) is the set of rebuts that should be removed as the consequence of the removal of the rebuts in {a mathematical formula}π(K′) according to a contrapositive reading of the context-independence property, i.e.{a mathematical formula}
       </list-item>
       <list-item label="5.">
        {a mathematical formula}FSA(π)(K) is the set of rebuts that should be removed as the consequence of the removal of the rebuts in {a mathematical formula}π(K) according to a contrapositive reading of the strong subargument structure property, i.e.{a mathematical formula}
       </list-item>
      </list>
      <paragraph label="Example 10">
       Continuing Example 9, let {a mathematical formula}π1=FER(∅‾). It holds: {a mathematical formula}π1(K)={(A2′,A3)} and {a mathematical formula}π1(K′)=∅.Let {a mathematical formula}π2=FAM(π1). Since {a mathematical formula}A2 is a weakening of {a mathematical formula}A2′, and {a mathematical formula}(A2′,A3)∈π1(K), it follows directly from the definition of FAM that {a mathematical formula}(A2,A3)∈π2(K).It is not difficult to see that {a mathematical formula}π2(K′)=∅.Let {a mathematical formula}π3=FCI(π2). From {a mathematical formula}(A2,A3)∈π2(K), it follows {a mathematical formula}(A2,A3)∈π3(K′).Suppose the preference is revised to {a mathematical formula}d3≺d2.Let {a mathematical formula}π1=FER(∅‾). It holds: {a mathematical formula}π1(K)={(A3,A2′)} and {a mathematical formula}π1(K′)=∅.Let {a mathematical formula}π2=FLO(π1). From {a mathematical formula}A2∈A2′↓{A1} and {a mathematical formula}A3 rebuts {a mathematical formula}A2′ and {a mathematical formula}(A3,A2′)∈π1(K) and {a mathematical formula}A3 does not rebut {a mathematical formula}A1, it follows {a mathematical formula}(A3,A2)∈π2(K).Consider the knowledge base KB in Example 1 (Fig. 1).Let {a mathematical formula}π1=FER(∅‾). It is clear that {a mathematical formula}π1(KB)={(N1,A2),(N1,N2)}.It holds that {a mathematical formula}FSA(π1)(KB)={(N1,A2),(N1,N2),(N1,N2′)}.
      </paragraph>
      <paragraph>
       It is easy to see that all functions FER, FAM, FLO, FSA, FCI are monotone.
      </paragraph>
      <paragraph label="Lemma 9">
       Let{a mathematical formula}π,π′∈REMASRsuch that{a mathematical formula}π⊆π′. Further let{a mathematical formula}X∈{FER,FAM,FLO,FSA,FCI}. Then{a mathematical formula}X(π)⊆X(π′).
      </paragraph>
      <paragraph label="Proof">
       Follows immediately from Definition 24.  □
      </paragraph>
      <paragraph>
       We define the operator ⊔ on functions of removal assignments. Let {a mathematical formula}X,Y:REMASR⟶REMASR. Define{a mathematical formula} by{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 25">
       Define{a mathematical formula}
      </paragraph>
      <paragraph>
       The following Lemma 9 holds obviously:
      </paragraph>
      <paragraph label="Lemma 10">
       REMOVE is monotone, i.e. for all{a mathematical formula}π,π′∈REMASRsuch that{a mathematical formula}π⊆π′,{a mathematical formula}REMOVE(π)⊆REMOVE(π′).
      </paragraph>
      <paragraph>
       We show next the continuity of removal functions.
      </paragraph>
      <paragraph label="Lemma 11">
       <list>
        <list-item label="1.">
         All removal functions{a mathematical formula}FER,FAM,FLO,FCI,FSAare continuous, i.e. for each directed{a mathematical formula}Δ⊆REMASR, for each{a mathematical formula}X∈{FER,FAM,FLO,FCI,FSA}, it holds:{a mathematical formula}
        </list-item>
        <list-item label="2.">
         REMOVE is continuous and{a mathematical formula}
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       See Appendix C.  □
      </paragraph>
      <paragraph label="Lemma 12">
       {a mathematical formula}Batts∖lfp(REMOVE)is weakly regular and coincides with{a mathematical formula}WattR, i.e.{sup:18}{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       See Appendix C.  □
      </paragraph>
      <paragraph>
       Theorem 6 below gives a least-fixed point characterization of the canonical attack relation assignment.
      </paragraph>
      <paragraph label="Theorem 6">
       <list>
        <list-item label="1.">
         If the canonical attack relation assignment{a mathematical formula}AttRexists, it holds:{a mathematical formula}
        </list-item>
        <list-item label="2.">
         If{a mathematical formula}Rsatisfies the self-contradiction property then{a mathematical formula}AttRexists and{a mathematical formula}
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       Follows immediately from Lemma 5, Lemma 12.  □
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Canonical attack relations and normal attack relations
     </section-title>
     <paragraph>
      There is a close relationship between canonical and normal attack relations. Even though they are different as illustrated in the following Example 11, they coincide for a relevant class of well-prioritized rule-based systems. Moreover, normal and canonical attack relations are equivalent wrt stable semantics in general.
     </paragraph>
     <paragraph label="Example 11">
      Let {a mathematical formula}R consist of the following rules:{a mathematical formula} and {a mathematical formula}d2≺d3 (a graphical presentation of the rules is given in Fig. 11 where a bar on an arrow indicates that the conclusion of the rule is negated).Let {a mathematical formula}K0=(R,∅).Consider the arguments {a mathematical formula}A0=[d0], {a mathematical formula}A1=[d1], {a mathematical formula}A2=[[d0],d2], {a mathematical formula}A3=[[d1],d3], {a mathematical formula}B0=[[d0],r0], {a mathematical formula}B1=[[d1],r1].We show that the basic attack relation assignment {a mathematical formula}Batts is also the canonical attack relation assignment. It is clear that {a mathematical formula}R is closed under transposition. Hence from Lemma 7, it follows that all regular properties except the effective rebut one are satisfied.Since the set {a mathematical formula}{a,b} is inconsistent, there is no knowledge base {a mathematical formula}K∈CR such that {a mathematical formula}{a,b}⊆BEK. Therefore arguments {a mathematical formula}[[a],d2] and {a mathematical formula}[[b],d3] never coexist in the same knowledge base. Hence the effective rebut property is always satisfied. Therefore {a mathematical formula}Batts is a regular attack relation assignment for {a mathematical formula}R. {a mathematical formula}Batts is hence also the canonical attack relation assignment.It is not difficult to see that for any {a mathematical formula}K∈CR, {a mathematical formula}attsnr(K)⊆Batts(K)∖{(A2,A3)} (Note that for each {a mathematical formula}K∈CR, {a mathematical formula}(A2,A3)∈Batts(K)).Looking closely at {a mathematical formula}A2,A3,B0,B1, we can say that the rebutting between arguments {a mathematical formula}A2,A3 is “redundant” as “their conflict” lies deeper down between {a mathematical formula}B0,B1. Resolving the conflict between {a mathematical formula}B0,B1 would lead to a resolution of the conflict between {a mathematical formula}A2,A3. Introducing a priority between {a mathematical formula}d2,d3 is unnecessary and unhelpful. This observation raises two interesting questions:
     </paragraph>
     <list>
      <list-item label="–">
       We study this question by introducing a class of well-prioritized systems where priorities are sensible. We show that for well-prioritized knowledge bases, the canonical and normal attack relations coincide.
      </list-item>
      <list-item label="–">
       We do not have a comprehensive answer to this question. We will show that in general, for any knowledge base, the canonical and normal attack relations are equivalent wrt stable semantics, i.e. they deliver the same stable extensions. We let it open the question whether the same can be said for other semantics like the preferred extension semantics. In a way, the coincidence of the two attack relations for the class of well-prioritized systems could be viewed as providing a partial answer to this open question.
      </list-item>
     </list>
     <paragraph>
      Before showing the coincidence of normal and canonical attack relations for well-prioritized knowledge bases as well as their equivalence wrt stable semantics, we first present a result to shed further light on the structure of regular attack relations with regards to the strengthening operation.{sup:19}
     </paragraph>
     <paragraph>
      Let A be a defeasible argument and {a mathematical formula}d∈ldr(A). Let X be a maximal basic defeasible subargument of A whose last link is d.{sup:20} It is clear that X is of the form {a mathematical formula}X=[X1,…,Xn,d].
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Y1,…,Ym be the maximal basic defeasible subarguments of A that are different to X.{sup:21}
     </paragraph>
     <paragraph>
      We define a d-strengthening of A, denoted by {a mathematical formula}str(A,d) to be a strengthening of A where the subarguments {a mathematical formula}X1,…,Xn,Y1,…,Ym are replaced by their conclusions.{sup:22}
     </paragraph>
     <paragraph label="Lemma 13">
      Let atts be a regular attack relation assignment for{a mathematical formula}R. Further let{a mathematical formula}K∈CR,{a mathematical formula}A,B∈ARKand{a mathematical formula}d∈ldr(A)such that the following properties hold:
      <list>
       A attacks B (wrt atts(K)).A rebuts B (at B) and A does not rebut any proper subargument of B.Both{a mathematical formula}str(B,last(B))and{a mathematical formula}str(A,d)belong to{a mathematical formula}ARK.The following conditions hold:
      </list>
      <list>
       <list-item label="1.">
        {a mathematical formula}str(A,d)attacks{a mathematical formula}str(B,last(B))(wrt atts(K)).
       </list-item>
       <list-item label="2.">
        {a mathematical formula}d⊀last(B).
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      See Appendix D.  □
     </paragraph>
     <section label="7.1">
      <section-title>
       Well-prioritized rule-based systems
      </section-title>
      <paragraph>
       For this section, let {a mathematical formula}R=(RS,RD,⪯) be an arbitrary but fixed rule-based system. Further let {a mathematical formula}λ,β∈L.
      </paragraph>
      <paragraph>
       We say that λ directly depends on β iff there is a rule {a mathematical formula}r∈RS∪RD such that {a mathematical formula}λ=hd(r) and {a mathematical formula}β∈bd(r).
      </paragraph>
      <paragraph>
       λ depends on β iff {a mathematical formula}λ=β or λ depends on α that directly depends on β.
      </paragraph>
      <paragraph>
       The set of all sentences in {a mathematical formula}L on which λ depends is denoted by {a mathematical formula}Δ(λ). For a set {a mathematical formula}S⊆L, {a mathematical formula}Δ(S) is the union of {a mathematical formula}Δ(λ) for {a mathematical formula}λ∈S.
      </paragraph>
      <paragraph label="Definition 26">
       Well-prioritized systemsA rule-based system {a mathematical formula}R=(RS,RD,⪯) is said to be well-prioritized iff for each defeasible rule {a mathematical formula}d∈RD, the following condition holds:If there exists {a mathematical formula}d′≺d then the set {a mathematical formula}Δ(bd(d))∪Δ(¬hd(d)) is consistent.
      </paragraph>
      <paragraph label="Example 12">
       <list>
        <list-item label="–">
         Consider defeasible rule {a mathematical formula}d3 in Example 11 again. Since {a mathematical formula}Δ(bd(d3))∪Δ(¬hd(d3))=Δ(b)∪Δ(c)={a,b,c} is inconsistent and {a mathematical formula}d2≺d3, the rule-based system not well-prioritized.
        </list-item>
        <list-item label="–">
         Consider rule {a mathematical formula}d2 in Example 1. {a mathematical formula}Δ(bd(d2))∪Δ(¬hd(d2))=Δ(¬Inno(P2))={¬Inno(P2),Inno(P1),Inno(S)} is consistent. Since {a mathematical formula}d1≺d2 is the only preference, the concerned rule-based system is well-prioritized.
        </list-item>
        <list-item label="–">
         Consider rule {a mathematical formula}d3 in Example 3. {a mathematical formula}Δ(bd(d3))∪Δ(¬hd(d3))=Δ(A)∪Δ(T)={A,D,T,P} is consistent. Since {a mathematical formula}d2≺d3 is the only preference, the concerned rule-based system is well-prioritized.
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       To see the intuition of the idea of well-prioritized systems, let us remember that the “minimal interpretation” of a preference {a mathematical formula}d′≺d is that in situations when both {a mathematical formula}d′,d are applicable but accepting both {a mathematical formula}d′,d is not possible, d should be preferred. In other words, in situations where {a mathematical formula}d′ is not applicable, a preference {a mathematical formula}d′≺d is redundant and unnecessary.
      </paragraph>
      <paragraph>
       For simplicity, let us assume that the heads of {a mathematical formula}d′,d are contrary.
      </paragraph>
      <paragraph>
       It is obvious that in situation when {a mathematical formula}bd(d′)∪bd(d) hold, but {a mathematical formula}bd(d′)∪bd(d)∪{hd(d′)}=bd(d′)∪bd(d)∪{¬hd(d)} is inconsistent, {a mathematical formula}d′ would not be applicable. Hence imposing a preference of d over {a mathematical formula}d′ is unnecessary and unhelpful in this case.
      </paragraph>
      <paragraph>
       Therefore we can say that imposing a preference of defeasible rule d over some defeasible rule {a mathematical formula}d′ would be only helpful and sensible if {a mathematical formula}bd(d′)∪bd(d)∪{¬hd(d)} is consistent.
      </paragraph>
      <paragraph>
       From {a mathematical formula}bd(d′)∪bd(d)∪{¬hd(d)}⊆Δ(bd(d))∪Δ(¬hd(d)), we can say that in well-prioritized systems, preferences between defeasible rules are sensible.
      </paragraph>
      <paragraph>
       Before showing the coincidence of normal and canonical attack relations for well-prioritized knowledge bases, we first show a lemma stating in essence that for well-prioritized systems, the direct attacks wrt normal and canonical attack relations coincide.
      </paragraph>
      <paragraph label="Lemma 14">
       Suppose{a mathematical formula}Rbe a well-prioritized rule-based system such that the canonical attack relation assignment{a mathematical formula}AttRexists. Further let{a mathematical formula}K∈CRand{a mathematical formula}A,B∈ARKand{a mathematical formula}d∈ldr(A)such that A rebuts B (at B) and{a mathematical formula}d≺last(B). Then{a mathematical formula}(A,B)∉AttR(K).
      </paragraph>
      <paragraph label="Proof">
       See Appendix D.  □
      </paragraph>
      <paragraph>
       From Lemma 6 and the above Lemma 14, it follows immediately
      </paragraph>
      <paragraph label="Lemma 15">
       Suppose{a mathematical formula}Rbe a well-prioritized rule-based system satisfying the self-contradiction property. Further let{a mathematical formula}K∈CRand{a mathematical formula}A,B∈ARKsuch that A rebuts B (at B). It holds that A does not attack B wrt{a mathematical formula}AttR(K)iff there exists{a mathematical formula}d∈ldr(A)s.t.{a mathematical formula}d≺last(B).
      </paragraph>
      <paragraph>
       We can now prove the coincidence of canonical and normal attack relations for well-prioritized systems.
      </paragraph>
      <paragraph label="Theorem 7">
       Let{a mathematical formula}Rbe a well-prioritized rule-based system satisfying the self-contradiction property. The canonical attack relation assignment{a mathematical formula}AttRand the normal attack relation assignment{a mathematical formula}attsnrcoincide.
      </paragraph>
      <paragraph label="Proof">
       Because {a mathematical formula}attsnr⊆AttR, we only need to show that for each {a mathematical formula}K∈CR, if {a mathematical formula}(A,B)∉attsnr(K) then {a mathematical formula}(A,B)∉AttR(K).Let {a mathematical formula}K∈CR and {a mathematical formula}(A,B)∉attsnr(K). It is clear that A does not undercut B. If A does not rebut B then the theorem holds obviously.Suppose A rebuts B. Therefore for all basic defeasible subarguments X of B, if A rebuts X (at X) then {a mathematical formula}∃dX∈ldr(A) s.t. {a mathematical formula}dX≺last(X). From Lemma 15, it holds that for all basic defeasible subarguments X of B, if A rebuts X (at X) then A does not attack X wrt {a mathematical formula}AttR(K).We show that A does not attack B wrt {a mathematical formula}AttR(K). Suppose the contrary that A attacks B wrt {a mathematical formula}AttR(K). Since {a mathematical formula}AttR is regular, it satisfies the strong subargument structure property. Let {a mathematical formula}X0 be a basic defeasible subargument of B s.t. A directly attacks {a mathematical formula}X0 (wrt {a mathematical formula}AttR). As A rebuts B, it follows A rebuts {a mathematical formula}X0 (at {a mathematical formula}X0). Therefore A does not attack {a mathematical formula}X0 wrt {a mathematical formula}AttR(K). Contradiction. □
      </paragraph>
      <paragraph>
       It is not difficult to see that checking the well-prioritizedness of a rule-based system is polynomial wrt number n of rules in it.
      </paragraph>
      <list>
       <list-item label="1.">
        For each {a mathematical formula}λ∈L, computing {a mathematical formula}Δ(λ) is polynomial as the computation of {a mathematical formula}Δ(λ) could be done with maximal n iterations to check which rules could be backward-applied to generate {a mathematical formula}Δ(λ) and once such a rule is found, it will be removed from the set of rules that have not been applied yet.
       </list-item>
       <list-item label="2.">
        For any defeasible rule d, checking whether {a mathematical formula}Δ(¬hd(d))∪Δ(bd(d)) is consistent is polynomial as it could be done in two steps:
       </list-item>
       <list-item label="3.">
        For any defeasible rule d, checking whether there exists {a mathematical formula}d′≺d is linear.
       </list-item>
      </list>
     </section>
     <section label="7.2">
      <section-title>
       Equivalence of canonical and normal attack relations wrt stable semantics
      </section-title>
      <paragraph>
       Even though in general canonical attack relations and normal attack relations are different, they turn out to be equivalent for stable semantics in the sense that their stable extensions coincide as we will prove shortly below.
      </paragraph>
      <paragraph>
       We first introduce some useful lemmas.
      </paragraph>
      <paragraph label="Lemma 16">
       Let{a mathematical formula}atts,atts′be regular attack relation assignments for{a mathematical formula}R. Further let{a mathematical formula}K∈CRand{a mathematical formula}S⊆ARKsuch that S contains all arguments generated from its arguments. Then S is conflict-free wrt{a mathematical formula}atts(K)iff S is also conflict-free wrt{a mathematical formula}atts′(K).
      </paragraph>
      <paragraph label="Proof">
       Suppose S is conflict-free wrt {a mathematical formula}atts(K) and S is not conflict-free wrt {a mathematical formula}atts′(K). Since {a mathematical formula}atts(K) and {a mathematical formula}atts′(K) have the same set of undercuts, some argument in S rebuts another. Since all subarguments of arguments in S belong to S, S is inconsistent. Because {a mathematical formula}atts(K) satisfies the inconsistency-resolving property, some argument in S is attacked (wrt atts(K)) by some generated by S. Since S contains all arguments generated from its arguments, S is not conflict-free wrt atts(K). Contradiction. Therefore S is also conflict-free wrt {a mathematical formula}atts′(K). □
      </paragraph>
      <paragraph label="Lemma 17">
       Let{a mathematical formula}atts,atts′be regular attack relation assignments for{a mathematical formula}Rsuch that{a mathematical formula}atts⊆atts′. Then
      </paragraph>
      <list>
       <list-item label="1.">
        each stable extension of{a mathematical formula}(ARK,atts(K))is a stable extension of{a mathematical formula}(ARK,atts′(K)); and
       </list-item>
       <list-item label="2.">
        each stable extension of{a mathematical formula}(ARK,atts(K))is a stable extension of{a mathematical formula}(ARK,AttR(K)).
       </list-item>
      </list>
      <paragraph label="Proof">
       It is clear that assertion (2) follows immediately from assertion (1) and the definition of {a mathematical formula}AttR. We hence need only to prove assertion (1).Let E be a stable extension of {a mathematical formula}(ARK,atts(K)). From Lemma 2, Lemma 16, it is clear that E is also conflict-free wrt {a mathematical formula}atts′(K). As E attacks each argument in {a mathematical formula}ARK∖E wrt {a mathematical formula}atts(K) and {a mathematical formula}atts(K)⊆atts′(K), it is obvious that E attacks each argument in {a mathematical formula}ARK∖E wrt {a mathematical formula}atts′(K). E is hence stable wrt {a mathematical formula}atts′(K). □
      </paragraph>
      <paragraph label="Lemma 18">
       Let{a mathematical formula}Rbe a rule-based system satisfying the self-contradiction property and{a mathematical formula}attsbe a regular attack relation assignment of{a mathematical formula}R. Further let{a mathematical formula}K∈CR. Each stable extension of{a mathematical formula}(ARK,atts(K))is also a stable extension of{a mathematical formula}(ARK,attsnr(K)).
      </paragraph>
      <paragraph label="Proof">
       See Appendix D. □
      </paragraph>
      <paragraph label="Theorem 8">
       Suppose the rule-based system{a mathematical formula}Rsatisfies the property of self-contradiction. Then for each{a mathematical formula}K∈CR, each stable extension wrt{a mathematical formula}attsnr(K)is also a stable extension wrt{a mathematical formula}AttR(K)and vice versa.
      </paragraph>
      <paragraph label="Proof">
       From Theorem 3, the canonical attack relation assignment {a mathematical formula}AttR exists. From Lemma 18, every stable extension wrt {a mathematical formula}AttR(K) is a stable extension wrt {a mathematical formula}attsnr(K). Since {a mathematical formula}attsnr(K)⊆AttR(K), every stable extension wrt {a mathematical formula}attsnr(K) is a stable extension wrt {a mathematical formula}AttR(K) (Lemma 17).  □
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Discussion
     </section-title>
     <section label="8.1">
      <section-title>
       The lower-semilattice structure of value-based semantics
      </section-title>
      <paragraph>
       The value-based approaches to argumentation [4], [10], [47], [43], [44] define the semantics of defeasible knowledge bases by first defining a preference relation between arguments and then using the preference relation to define attack relation between arguments. We show in this section that the preference relations between arguments have a complete lower-semilattice structure and hence a least preference relation exists that captures the canonical semantics.
      </paragraph>
      <paragraph>
       We first introduce a new operator about a “structured intersection” of relations that is needed to characterize the structure of preference relations between arguments.
      </paragraph>
      <paragraph>
       Any relation {a mathematical formula}R⊆X×X over a set X could be partitioned into a strict core, denoted by {a mathematical formula}Rst and symmetric core, denoted by {a mathematical formula}Rsy as follows: {a mathematical formula}R=Rst∪Rsy where {a mathematical formula}Rst={(a,b)∈R|(b,a)∉R} and {a mathematical formula}Rsy={(a,b)∈R|(b,a)∈R}.
      </paragraph>
      <paragraph>
       For any relations {a mathematical formula}R,R′⊆X×X, we introduce a “strong intersection”-operator {a mathematical formula}R⊓R′ by: {a mathematical formula}R⊓R′=(Rst∩Rst′)∪(Rsy∩Rsy′).
      </paragraph>
      <paragraph>
       Further, we define a partial order {a mathematical formula}R≪R′ by: {a mathematical formula}R≪R′ iff {a mathematical formula}Rst⊆Rst′ and {a mathematical formula}Rsy⊆Rsy′.
      </paragraph>
      <paragraph label="Definition 27">
       An argument preference assignment (or ap-assignment for short) for a rule-based system {a mathematical formula}R is a function Γ assigning to each knowledge base {a mathematical formula}K∈CR, a relation {a mathematical formula}⊑Γ,K⊆ARK×ARK (whose strict core is {a mathematical formula}⊏Γ,K) representing a preference relation between arguments in {a mathematical formula}ARK where strict arguments are not strictly less preferred than any other arguments.
      </paragraph>
      <paragraph>
       For ap-assignments {a mathematical formula}Γ0,Γ1, we write {a mathematical formula}Γ0≪Γ1 iff for each {a mathematical formula}K∈CR, {a mathematical formula}Γ0(K)≪Γ1(K).
      </paragraph>
      <paragraph>
       We recall the definition of attack relations from the argument preferences [43], [44] below.
      </paragraph>
      <paragraph label="Definition 28">
       Let Γ be an ap-assignment defined for {a mathematical formula}R. The attack relation assignment derived fromΓ and denoted by {a mathematical formula}attsΓ, is defined by: For each {a mathematical formula}K∈CR and all {a mathematical formula}A,B∈ARK, {a mathematical formula}(A,B)∈attsΓ(K) iff A undercuts B or A rebuts B (at {a mathematical formula}B′) and {a mathematical formula}A⊏̸Γ,KB′.
      </paragraph>
      <paragraph>
       It is easy to see that the following lemma holds.
      </paragraph>
      <paragraph label="Lemma 19">
       Let{a mathematical formula}Γ0,Γ1be ap-assignments defined for{a mathematical formula}Rsuch that{a mathematical formula}Γ0≪Γ1. It holds{a mathematical formula}attsΓ1⊆attsΓ0.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}K∈CR and {a mathematical formula}A,B∈ARK such that {a mathematical formula}(A,B)∈attsΓ1(K).If A undercuts B then it is obvious that {a mathematical formula}(A,B)∈attsΓ0(K).Suppose A rebuts B (at {a mathematical formula}B′) and {a mathematical formula}A⊏̸Γ1,KB′. Since {a mathematical formula}Γ0≪Γ1 it holds that {a mathematical formula}⊑Γ0,K≪⊑Γ1,K. Therefore {a mathematical formula}⊏Γ0,K⊆⊏Γ1,K. Therefore {a mathematical formula}A⊏̸Γ1,KB′ implies {a mathematical formula}A⊏̸Γ0,KB′. Since A rebuts B (at {a mathematical formula}B′) and {a mathematical formula}A⊏̸Γ0,KB′, it follows that {a mathematical formula}(A,B)∈attsΓ0(K).  □
      </paragraph>
      <paragraph label="Definition 29">
       An ap-assignment Γ is regular for {a mathematical formula}R iff its derived attack relation assignment {a mathematical formula}attsΓ is regular.The set of all regular ap-assignments for {a mathematical formula}R is denoted by {a mathematical formula}APR.
      </paragraph>
      <paragraph label="Notation 4">
       The “strong intersection”-operator is extended to non-empty set {a mathematical formula}P of ap-assignments and denoted by {a mathematical formula}⊓P as follows: {a mathematical formula}(⊓P)(K)=⊓{Γ(K)|Γ∈P}.
      </paragraph>
      <paragraph>
       The following lemma shows that the “strong intersection” forms an infimum operation for regular ap-assignments.
      </paragraph>
      <paragraph label="Lemma 20">
       Let{a mathematical formula}Pbe a non-empty set of regular apr-assignments for{a mathematical formula}R. Then{a mathematical formula}⊓Pis regular.
      </paragraph>
      <paragraph label="Proof">
       See Appendix E.  □
      </paragraph>
      <paragraph label="Theorem 9">
       <list>
        <list-item label="1.">
         If{a mathematical formula}APRis non-empty then{a mathematical formula}(APR,≪,⊓)forms a complete lower-semilattice with{a mathematical formula}CAR=⊓APRbeing the least regular ap-assignment for{a mathematical formula}Rand is referred to as thecanonical ap-assignment.
        </list-item>
        <list-item label="2.">
         If the rule-based system{a mathematical formula}Rsatisfies the self-contradiction property then the set of regular ap-assignments{a mathematical formula}APRis not empty and{a mathematical formula}attsCAR=AttR.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       See Appendix E. □
      </paragraph>
      <paragraph>
       One of the arguably most influential representatives of the value-based approach could be said to be ASPIC+ [43], [44] where four ap-assignments are introduced and studied.
      </paragraph>
      <paragraph label="Definition 30">
       [43], [44] Let K be a knowledge base and ⪯ be the preference relation over defeasible rules of K and {a mathematical formula}Δ,Δ′ be two finite sets of defeasible rules of K and {a mathematical formula}y∈{E,D},{sup:23} define:{a mathematical formula}
       <list>
        {a mathematical formula}Δ′=∅.{a mathematical formula}y=E and {a mathematical formula}∃d∈Δs.t.∀d′∈Δ′:d⪯d′.{a mathematical formula}y=D and {a mathematical formula}∀d∈Δ∃d′∈Δ′:d⪯d′.{a mathematical formula}◁y
       </list>
       <paragraph>
        denotes the strict core of {a mathematical formula}⊴y.
       </paragraph>
      </paragraph>
      <paragraph label="Definition 31">
       [43], [44] Let K be a knowledge base, {a mathematical formula}A,B be two arguments in {a mathematical formula}ARK and {a mathematical formula}y∈{E,D}.
      </paragraph>
      <list>
       <list-item label="1.">
        B is preferred toA according to the last link principle and the y-ordering (or y-principle), denoted by {a mathematical formula}A⊑lyB if and only if {a mathematical formula}ldr(A)⊴yldr(B).
       </list-item>
       <list-item label="2.">
        B is preferred toA according to the weakest link principle and the y-ordering (or y-principle), denoted by {a mathematical formula}A⊑wyB if and only if {a mathematical formula}dr(A)⊴ydr(B).
       </list-item>
      </list>
      <paragraph>
       As we have mentioned in Example 1, attack relations derived from ASPIC+ ap-assignments based on democratic principle do not satisfy the attack monotonicity property. To see this point, consider arguments {a mathematical formula}N1,N1′ and {a mathematical formula}A2 in Fig. 1. It is not difficult to see that {a mathematical formula}N1◁xDA2, but {a mathematical formula}N1′◁̸xDA2 for both {a mathematical formula}x=l and {a mathematical formula}x=w. Therefore, with respect to the democratic principle, {a mathematical formula}N1′ attacks {a mathematical formula}A2, but {a mathematical formula}N1 does not attack {a mathematical formula}A2. A clear violation of the property of attack monotonicity. In other words, ASPIC+ ap-assignments based on democratic principle are not regular. This helps in explaining why applying the democratic principle leads to semantics that are counter-intuitive to commonsense in Example 1 as we have discussed before.
      </paragraph>
      <paragraph>
       The following example taken from [23] shows that ASPIC+ ap-assignments based on elitist principle are not regular because their derived attack relations do not satisfy the consistency postulate.
      </paragraph>
      <paragraph label="Example 13">
       Consider the knowledge base K consisting of
       <list>
        It is clear that ⪯ is a preorder and the knowledge base is consistent and closed under transposition.There are in total 8 arguments:
       </list>
       <paragraph>
        {a mathematical formula} and{a mathematical formula}We first show{a mathematical formula} From {a mathematical formula}d1⪯d2, it is clear that {a mathematical formula}{d1,d3,d4}⊴E{d2}. From {a mathematical formula}d2⪯̸d3, it is obvious that {a mathematical formula}{d2}⋬E{d1,d3,d4}.Similarly, it holds:{a mathematical formula}Therefore for {a mathematical formula}1≤i≤4, {a mathematical formula}Bi does not attack {a mathematical formula}Ai according to the ASPIC+ argument preferences based on the elitist principle. Therefore both attack relations based on ASPIC+ elitist ap-assignments equal the empty set. It is obvious that the grounded extension (that is also stable) is {a mathematical formula}{A1,…,A4,B1,…,B4} whose set of conclusions {a mathematical formula}{a1,…,a4,¬a1,…,¬a4} is obviously inconsistent. Hence the consistency postulate is violated.{sup:24}
       </paragraph>
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Ordinary attack relations
      </section-title>
      <paragraph>
       A class of ordinary attack relation assignments defined on sensible classes of knowledge bases as well as their relationship to other approaches on reasoning with prioritized rules has been studied in [30], [23].
      </paragraph>
      <paragraph>
       Formally, a class {a mathematical formula}K of knowledge bases [23] is said to be sensible iff {a mathematical formula}K is not empty, and every knowledge base in {a mathematical formula}K is consistent, and for each knowledge base {a mathematical formula}K=(R,BE) belonging to {a mathematical formula}K, all consistent knowledge bases of the form {a mathematical formula}(R,BE′) also belong to {a mathematical formula}K.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}K be a sensible class of knowledge bases. Further let CR be the set of all rule-based systems of knowledge bases in {a mathematical formula}K. It is not difficult to see that {a mathematical formula}K=⋃{CR|R∈CR}.
      </paragraph>
      <paragraph>
       It follows immediately that for each consistent rule-based system {a mathematical formula}R, {a mathematical formula}CR is a sensible class of knowledge bases.
      </paragraph>
      <paragraph>
       To relate regular attack relations to ordinary ones, we will first consider only ordinary attack relation assignments defined on {a mathematical formula}CR. We will discuss the situations when attack relation assignments should be considered wrt sensible classes of knowledge bases at the end of this section.
      </paragraph>
      <paragraph>
       An attack relation assignment att (defined for {a mathematical formula}CR) is ordinary [23] if it is weakly regular and also satisfies the important property of credulous cumulativity stating intuitively that if some beliefs in your belief set are confirmed in the reality then your belief set will not change because of it. Credulous cumulativity is a key property satisfied by many argument-based and non-argument-based approaches to reasoning with prioritized rules [30], [23]. We give the formal definition of credulous cumulativity below.
      </paragraph>
      <paragraph>
       A set {a mathematical formula}S⊆L is said to be a belief set of knowledge base K wrt an attack relation assignment atts iff there is a stable extension E of {a mathematical formula}(ARK,atts(K)) such that {a mathematical formula}S=cnl(E).
      </paragraph>
      <paragraph label="Definition 32">
       Credulous cumulativity[23] We say attack relation assignment {a mathematical formula}atts satisfies the property of credulous cumulativity if and only if for each {a mathematical formula}K∈CR, for each belief set S of K wrt {a mathematical formula}atts and for each finite subset {a mathematical formula}Ω⊆S of domain literals, S is a belief set of {a mathematical formula}K+Ω=(RSK,RDK,⪯K,BEK∪Ω) wrt {a mathematical formula}atts.
      </paragraph>
      <paragraph>
       For an illustration, consider again Example 3. Let {a mathematical formula}K′=(R,BE′) where {a mathematical formula}BE′={D}. As {a mathematical formula}{D,P,A,¬T} is a belief set of {a mathematical formula}K′, the property of credulous cumulativity dictates that {a mathematical formula}{D,P,A,¬T} is also a belief set of {a mathematical formula}K=K′+{P}=(RSK,RDK,⪯K,{D,P}).
      </paragraph>
      <paragraph>
       We show below that regular attack relation assignments are ordinary by showing that they satisfy the credulous cumulativity property.
      </paragraph>
      <paragraph label="Theorem 10">
       The credulous cumulativity property is satisfied by all regular attack relation assignments.
      </paragraph>
      <paragraph label="Proof">
       See Appendix E. □
      </paragraph>
      <paragraph>
       In [23], a natural property of irrelevance of redundant defaults stating that adding a defeasible rule of the form ⇒f to a knowledge base K for any evidence {a mathematical formula}f∈BEK should not change its semantics is presented and shown that it is satisfied by attack relation assignments satisfying the properties of attack monotonicity and context-independence. Adding rules to knowledge bases change their underlining rule-based systems. Therefore attack relation assignments for sensible classes of knowledge bases should be considered when studying the semantics of knowledge base revisions involving adding or deleting rules from the rule-based systems.
      </paragraph>
      <paragraph>
       In this paper we do not discuss the problems concerning revisions of knowledge bases involving adding or deleting rules from the rule-based systems. Hence we could safely restrict our consideration on sensible classes of knowledge bases sharing the same rule-based system.
      </paragraph>
     </section>
     <section label="8.3">
      Remark on the underlying domain language {a mathematical formula}Ldom
      <paragraph>
       We assume until now that the underlying language of knowledge bases consists only of literals. In contrast, the underlying language of ASPIC+ systems [43] could be any logical language. Similarly, assumption-based systems [31], [32] do not put any restriction on their underlying language.
      </paragraph>
      <paragraph>
       From our own experiences in research on application of structured argumentation [33], [28], [26], [40], [46], we believe that many applications will be based on language of literals. Hence, from a pragmatic point of view, it is sensible to focus on an underlying language of literals first.
      </paragraph>
      <paragraph>
       Anyway, readers who prefer to work with a general underlying language, could simply assume that the domain language {a mathematical formula}Ldom be any logical language containing a classical negation operator ¬ (note that non-domain atoms of the form {a mathematical formula}abd do not belong to {a mathematical formula}Ldom). In all definitions, notations, lemmas and theorems in this paper starting from Definition 1 up to the last definition, references are always made to {a mathematical formula}Ldom, and not to a specific language of literals. Hence all theorems and lemmas in this paper are also correct with respect to a general language {a mathematical formula}Ldom. More formally, we extend in the section 9 our framework to allow a general language {a mathematical formula}Ldom together with negation-as-failure assumptions.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Extending knowledge bases with assumptions
     </section-title>
     <paragraph>
      Assumption-based argumentation [31], [32] is a well-known approach to structured argumentation based on the concept that assumptions are acceptable if there is no evidence to the contrary. We show in this section that assumptions could naturally be incorporated into our framework.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Ldom be a logical language possibly containing a classical negation operator ¬. Further {a mathematical formula}L be the language consisting of sentences in {a mathematical formula}Ldom and non-domain atoms of the form {a mathematical formula}abd.
     </paragraph>
     <paragraph label="Definition 33">
      <list>
       <list-item label="1.">
        An extended rule-based system over {a mathematical formula}L is a triple {a mathematical formula}(R,A,A‾) where
       </list-item>
       <list-item label="2.">
        An extended knowledge base consists of an extended rule-based system {a mathematical formula}(R,A,A‾) and a set of evidences {a mathematical formula}BE⊆Ldom disjoint to {a mathematical formula}A.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Remark 1">
      Abusing slightly the notation for simplicity, we often denote an extended rule-based system {a mathematical formula}(R,A,A‾) simply by the pair {a mathematical formula}(R,A) or just {a mathematical formula}R if no misunderstanding is possible.Similarly, an extended knowledge base {a mathematical formula}(R,A,A‾,BE) is often denoted by the triple {a mathematical formula}(R,A,BE) or just the pair {a mathematical formula}(R,BE) if no misunderstanding is possible.
     </paragraph>
     <paragraph label="Remark 2">
      Extended knowledge bases could also be viewed as extended assumption-based systems where defeasible rules together with two new types of attacks, rebuts and undercuts, are added. As illustrated in the following example, such additions could provide a more flexible platform for developers for representing their domains.
     </paragraph>
     <paragraph label="Example 14">
      An extended knowledge base {a mathematical formula}(RS,RD,⪯,BE) representing the well-known example of “penguins don't fly while birds and super-penguins do” is given by:
      <list>
       RS consisting of the strict rules{a mathematical formula} stating that super-penguins are penguins, penguins are birds and penguins are abnormal birds, andRD containing three defeasible rules:{a mathematical formula} stating that super-penguins fly by default while penguin normally do not fly and birds normally fly.⪯ consisting of an unique preference{a mathematical formula} stating that the rule “super-penguins fly (by default)” has higher priority than the rule “penguins normally do not fly”, and{a mathematical formula}BE={sp}.The relevant arguments are given in
      </list>
      <paragraph>
       Fig. 12.
      </paragraph>
     </paragraph>
     <paragraph label="Notation 5">
      <section-title>
       Adaptations for extended knowledge bases
      </section-title>
     </paragraph>
     <list>
      <list-item label="1.">
       Arguments wrt extended knowledge base {a mathematical formula}K=(R,A,BE) are defined as in Definition 2 where condition 1 is revised as follows:{a mathematical formula}Arguments of the form {a mathematical formula}[α], {a mathematical formula}α∈A, are also called assumption-arguments.
      </list-item>
      <list-item label="2.">
       Note that a non-strict argument could also be non-defeasible if it contains some assumptions but no defeasible rules.
      </list-item>
      <list-item label="3.">
       Let {a mathematical formula}X⊆L and {a mathematical formula}l∈L. Further let {a mathematical formula}Xdom=X∩Ldom.We say that l is strictly derived from X wrt K, denoted by {a mathematical formula}X⊢Kl, iff {a mathematical formula}l∈X or l is the conclusion of an argument constructed using only elements from {a mathematical formula}Xdom and the strict rules from K.{sup:25}The closure of a set {a mathematical formula}X⊆L wrt knowledge base K, denoted by {a mathematical formula}CNK(X), is defined by {a mathematical formula}CNK(X)={l|X⊢Kl}.X is said to be closed wrt K iff {a mathematical formula}X=CNK(X). X is said to be inconsistent wrt K iff its closure {a mathematical formula}CNK(X) is contradictory. X is consistent wrt K iff it is not inconsistent wrt K.K is said to be consistent iff its base of evidence {a mathematical formula}BEK is consistent wrt K.
      </list-item>
      <list-item label="4.">
       Attack relations are defined as in Definition 5.
      </list-item>
      <list-item label="5.">
       The basic postulates are defined as in Definition 6.
      </list-item>
      <list-item label="6.">
       {a mathematical formula}R and K are said to satisfy the self-contradiction property iff for each minimal inconsistent set {a mathematical formula}X⊆Ldom, for each {a mathematical formula}x∈X, it holds:
      </list-item>
     </list>
     <paragraph label="Notation 6">
      <list>
       <list-item label="–">
        We say an argument A undermines an argument B (at {a mathematical formula}[α]) iff {a mathematical formula}conl(A)=α‾, {a mathematical formula}α∈A and {a mathematical formula}[α] is a subargument of B.
       </list-item>
       <list-item label="–">
        The notions of undercut and rebut for extended knowledge bases are defined as in Definition 7.
       </list-item>
       <list-item label="–">
        An argument A is said to be generated by a set S of arguments iff all basic defeasible subarguments of A as well as all assumption-subarguments of A are subarguments of arguments in S.
       </list-item>
       <list-item label="–">
        Given an extended rule-based system {a mathematical formula}(R,A), the class of all consistent extended knowledge bases of the form {a mathematical formula}(R,A,BE) is denoted by {a mathematical formula}ER,A or just simply {a mathematical formula}ER if no misunderstanding is possible.
       </list-item>
       <list-item label="–">
        The notion of attack relation assignments are defined for extended knowledge bases in the same way as for knowledge bases (see Definition 16) where {a mathematical formula}CR is replaced by {a mathematical formula}ER.
       </list-item>
       <list-item label="–">
        The notion of weakening is defined for extended knowledge bases in the same way as for knowledge bases (see Definition 11).
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      It is not difficult to see that in Example 14, B undermines {a mathematical formula}A3 while {a mathematical formula}A1,A2 as well as {a mathematical formula}A2,A3 rebut each other.
     </paragraph>
     <paragraph label="Notation 7">
      Adaptations for extended knowledge basesAll regular properties (see Definition 9, Definition 12, Definition 14, Definition 17), except the properties of effective rebuts and strong subargument structure, can be directly adopted for extended knowledge bases. We give the revised definition of properties of effective rebuts and strong subargument structure below.
     </paragraph>
     <paragraph>
      We give an example explaining the reason for a slight revision of the effective rebut property.
     </paragraph>
     <paragraph label="Example 15">
      Let {a mathematical formula}R be an extended rule-based system consisting only of two defeasible rules{a mathematical formula} and a preference {a mathematical formula}d0≺d1 where {a mathematical formula}not_a is an assumption s.t. {a mathematical formula}not_a‾=a.It is clear that argument {a mathematical formula}A0≡[d0] undermines argument {a mathematical formula}A1≡[[not_a],d1]. Therefore even though {a mathematical formula}d0≺d1, {a mathematical formula}A0 still attacks {a mathematical formula}A1.
     </paragraph>
     <paragraph label="Definition 34">
      Effective rebut for extended knowledge baseWe say that attack relation att satisfies the effective rebut property for an extended knowledge base K iff for all arguments {a mathematical formula}A0,A1∈ARK such that
     </paragraph>
     <list>
      <list-item label="–">
       each {a mathematical formula}Ai, {a mathematical formula}i=0,1, contains exactly one defeasible rule {a mathematical formula}di (i.e. {a mathematical formula}dr(Ai)={di}), and
      </list-item>
      <list-item label="–">
       {a mathematical formula}A0 rebuts {a mathematical formula}A1, and
      </list-item>
      <list-item label="–">
       {a mathematical formula}A0 does not undermine {a mathematical formula}A1,{sup:26}
      </list-item>
     </list>
     <paragraph label="Definition 35">
      Strong subargument structure for extended knowledge baseAttack relation att of an extended knowledge base K is said to satisfy the property of strong subargument structure iff for all {a mathematical formula}A,B∈ARK, the following conditions hold:
     </paragraph>
     <list>
      <list-item label="1.">
       A attacks B (wrt att) iff A attacks a basic defeasible subargument or an assumption-subargument of B (wrt att).
      </list-item>
      <list-item label="2.">
       If A undercuts or undermines B then A attacks B wrt att.
      </list-item>
      <list-item label="3.">
       A directly attacks B (wrt att) then A undercuts or undermines or rebuts B (at B).
      </list-item>
     </list>
     <paragraph>
      It is not difficult to see that in Example 14, for any regular attack relation, {a mathematical formula}A1 attacks {a mathematical formula}A2 (from the effective rebut property) and B attacks {a mathematical formula}A3 (from the strong subargument property).
     </paragraph>
     <paragraph>
      It is straightforward to see that both Lemma 2 and Theorem 1 hold for extended knowledge bases.
     </paragraph>
     <paragraph label="Lemma 21">
      Let att be an attack relation for extended knowledge base K satisfying the property of strong subargument structure. Further let E be a complete extension of{a mathematical formula}(ARK,att).
     </paragraph>
     <list>
      <list-item label="1.">
       E contains all arguments generated by E, and
      </list-item>
      <list-item label="2.">
       att satisfies the postulates of closure and subargument closure.
      </list-item>
     </list>
     <paragraph label="Proof">
      Similar to the proof of Lemma 2.  □
     </paragraph>
     <paragraph label="Theorem 11">
      Let{a mathematical formula}att,att′be attack relations for knowledge base K.
     </paragraph>
     <list>
      <list-item label="1.">
       If{a mathematical formula}att⊆att′and att is inconsistency-resolving for K then{a mathematical formula}att′is also inconsistency-resolving for K.
      </list-item>
      <list-item label="2.">
       If att satisfies the strong subargument structure and inconsistency-resolving properties then att satisfies the postulate of consistency.
      </list-item>
     </list>
     <paragraph label="Proof">
      Identical to the proof of Theorem 1. □
     </paragraph>
     <paragraph>
      For any non-empty set {a mathematical formula}S of attack relation assignments of extended rule-based system {a mathematical formula}R, define {a mathematical formula}⋃S by:{a mathematical formula}
     </paragraph>
     <paragraph>
      The notions of weakly regular and regular attack relations assignments are defined for extended knowledge bases in the same way as for knowledge bases (see Definition 18).
     </paragraph>
     <paragraph>
      The set of all regular attack relation assignments of an extended rule-based system {a mathematical formula}R is denoted by {a mathematical formula}RAER.
     </paragraph>
     <paragraph label="Lemma 22">
      Let{a mathematical formula}Rbe an extended rule-based system and P be a regular property. Further let{a mathematical formula}Sbe a non-empty set of attack relation assignments wrt{a mathematical formula}Rsatisfying P. Then{a mathematical formula}⋃Salso satisfies P.
     </paragraph>
     <paragraph label="Proof">
      See Appendix F.  □
     </paragraph>
     <paragraph>
      From Lemma 22, the following Theorem 12 holds obviously.
     </paragraph>
     <paragraph label="Theorem 12">
      Suppose{a mathematical formula}RAERis not empty. Then{a mathematical formula}(RAER,⊆)is a complete upper-semilattice.The greatest element in{a mathematical formula}(RAER,⊆)is referred to as the canonical attack relation assignment of{a mathematical formula}Rand denoted by{a mathematical formula}AteR=⋃RAER.  □
     </paragraph>
     <paragraph>
      For extended rule-based systems, we define normal attack relation assignments in the same way as before, namely, for any extended knowledge base {a mathematical formula}K∈ER and any arguments {a mathematical formula}A,B∈ARK, {a mathematical formula}(A,B)∈attsenr(K) if and only if A undercuts or undermines B or A normal-rebuts B where the definition of normal-rebuts is the same like in section 5.2.
     </paragraph>
     <paragraph label="Theorem 13">
      <list>
       <list-item label="1.">
        For any extended rule-based system{a mathematical formula}R, the normal attack relation assignment{a mathematical formula}attsenris weakly regular.
       </list-item>
       <list-item label="2.">
        Suppose the extended rule-based system{a mathematical formula}Rsatisfies the self-contradiction property. Then the normal attack relation assignment{a mathematical formula}attsenris regular and the canonical assignment{a mathematical formula}AteRexists and{a mathematical formula}attsenr⊆AteR.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      See Appendix F.  □
     </paragraph>
     <paragraph label="Notation 8">
      The notion of well-prioritized rule-based system (Definition 26) is adopted directly for extended rule-based systems.
     </paragraph>
     <paragraph label="Theorem 14">
      Let{a mathematical formula}Rbe a well-prioritized extended rule-based system satisfying the self-contradiction property. The canonical attack relation assignment{a mathematical formula}AteRand the normal attack relation assignment{a mathematical formula}attsenrcoincide.
     </paragraph>
     <paragraph label="Proof">
      See Appendix F.  □
     </paragraph>
     <paragraph>
      We show next that canonical attack relations and normal attack relations for extended knowledge bases are also equivalent for stable semantics.
     </paragraph>
     <paragraph label="Theorem 15">
      Suppose an extended rule-based system{a mathematical formula}Rsatisfies the property of self-contradiction. Then for each{a mathematical formula}K∈CR, each stable extension wrt{a mathematical formula}attsenr(K)is also a stable extension wrt{a mathematical formula}AteR(K)and vice versa.
     </paragraph>
     <paragraph label="Proof">
      See Appendix F.  □
     </paragraph>
     <paragraph>
      It is not difficult to generalize the results on least-fixed point characterization of canonical attack relation assignment for extended knowledge bases. While the removal functions REMOVE as well as FER, FAM, FLO, FSA, FCI could be adopted directly for the extended case, Lemma 12, Lemma 26, Lemma 25 as well as Theorem 6 need to be revised slightly by {a mathematical formula}AteR=WateR=Battsuu∪(Battsrb∖lfp(REMOVE)) where {a mathematical formula}WateR is the supremum of weakly regular attack relation assignments for extended rule-based system, {a mathematical formula}Battsuu(K)={(A,B)|A,B∈ARK,A undercuts or undermines B} and {a mathematical formula}Battsrb(K)={(A,B)|A,B∈ARK,A rebuts B}. The reason for the slight modification is illustrated in Example 15. We omit the detailed proofs to avoid an unnecessarily long and repetitive presentation.
     </paragraph>
    </section>
    <section label="10">
     <section-title>
      Conclusion
     </section-title>
     <paragraph>
      Ii essence, one can say that a key purpose of introducing preferences between defeasible rules is to rule out undesired attacks [4], [43], [47], [30], [25], [23], [24]. We develop this idea further by introducing the principle of minimal-removal of attacks stating that the removed attacks should be kept to a minimum. This principle is captured declaratively by the canonical attack relation assignment that is the greatest element in the complete upper-semilattice of regular attack relations. We also provide a least-fixed point characterization of the canonical attack relation assignment. We further show that for well-prioritized rule-based systems, canonical attack relation assignment coincides with the normal attack relation assignments providing an efficient characterization of canonical attack relations. It is also worthwhile to note that our framework could easily and naturally extended for general underlining language with negation-as-failure assumptions.
     </paragraph>
     <paragraph>
      Other well-known approaches to structured argumentation are deductive argumentation of Besnard&amp;Hunter [11], defeasible logic programming of Garcia&amp;Simari [36], [5] and assumption-based argumentation [32]. As the question of how and by which principles and guidelines a user of structured argumentation selects an attack relation for her/his domain is a common and fundamental problem for all approaches to structured argumentation with preferences, and as the regular properties are defined at an abstraction level easily applicable to other approaches of structured argumentation{sup:27} and as the results we obtained in this paper hold for general underlining languages that could also include assumptions, we have convincing reasons to believe that the key results of this paper also hold in other approaches though their formal development could be different. This expectation is confirmed for assumption-based argumentation and ASPIC+ by our study of extended knowledge bases.{sup:28} Further, section 8.1 also provides an in depth discussion about the relationship between our approach and the other line of research that is based on defining pre-order between arguments before resolving their conflicts.
     </paragraph>
     <paragraph>
      Brewka and Eiter [15] have proposed two principles for the evaluation of semantics of prioritized default reasoning. These principles, referred to as BE-principles, have been adapted to our framework in [23] and showed that both of them are satisfied by the ordinary attack relation assignments. As regular attack relation assignments are ordinary, they hence are also satisfied by regular attack relation assignments.{sup:29}
     </paragraph>
     <paragraph>
      A more liberal notion of unrestricted rebut where a basic defeasible argument could attack a non-basic defeasible argument is studied in [18], [17]. Intuitively an unrestricted rebut is a rebut against a set of defeasible rules without explicitly rebutting any individual rule in it. As the notion of unrestricted rebut leads to counter-intuitive semantics wrt complete or stable extensions [17], the semantics of unrestricted rebuts is based on grounded extension. In [17], [18], it is proved that grounded semantics wrt attack relations generated by the Aspic+ argument preference relations recalled in Definition 30, Definition 31, satisfies the consistency postulate if the preference relation ⪯ between defeasible rules is either empty or a total preorder. We show shortly below that in general when the preference relation ⪯ is neither empty nor a total preorder, the grounded semantics of unrestricted rebuts wrt ASPIC+ ap-assignments that are based on the elitist principle fails to satisfy the consistency postulate.
     </paragraph>
     <paragraph>
      Consider the knowledge base K in Example 13. From {a mathematical formula}{d2,d3,d4}◁E{d1}, {a mathematical formula}{d1,d3,d4}◁E{d2}, {a mathematical formula}{d1,d2,d4}◁E{d3}, {a mathematical formula}{d1,d2,d3}◁E{d4}, it follows that for {a mathematical formula}1≤i≤4, {a mathematical formula}Ai attacks {a mathematical formula}Bi but {a mathematical formula}Bi does not attack {a mathematical formula}Ai according to the ASPIC+ argument preferences based on the elitist principle and unrestricted rebuts. Therefore both attack relations based on ASPIC+ elitist principle equal {a mathematical formula}{(Ai,Bi)|1≤i≤4}.
     </paragraph>
     <paragraph>
      It is obvious that the grounded extension (that is also stable) is {a mathematical formula}{A1,…,A4} whose set of conclusion {a mathematical formula}{a1,…,a4} is obviously inconsistent. Hence the consistency postulate is violated.
     </paragraph>
     <paragraph>
      In general, the requirement that preference relation ⪯ should be total preorder is rather strong if we consider that the purpose of introducing preferences between rules is to resolve conflicts among them. Hence there is nothing wrong when there is no preference between rules if there are no conflicts to be resolved. Further imposing artificial priorities between rules could lead to contradictory semantics. For an illustration, consider again the arguments in Fig. 1. Two of the possible total preorders that are consistent with the preference {a mathematical formula}d1≺d2 are {a mathematical formula}d1≺d2≺d and {a mathematical formula}d≺d1≺d2. Let us consider each of them.
     </paragraph>
     <list>
      <list-item label="–">
       {a mathematical formula}d≺d1≺d2. It is obvious that {a mathematical formula}N1′◁DA2 and {a mathematical formula}N1◁DA2. Therefore there is only one stable extension E that is also grounded consisting of {a mathematical formula}[S],[d],A2,N2,N2′.
      </list-item>
      <list-item label="–">
       {a mathematical formula}d1≺d2≺d. It is obvious that {a mathematical formula}N1′◁̸DA2. Therefore {a mathematical formula}N1′ attacks {a mathematical formula}A2. Hence apart from the stable extension E, the set {a mathematical formula}{A1,N1,N1′} is part of another stable extension. The grounded extension consists only of the arguments {a mathematical formula}[S] and {a mathematical formula}[d].
      </list-item>
     </list>
     <paragraph>
      The above discussion raises several interesting questions: Which one of the two cases should be viewed as “natural and intuitive”? What are the criteria for picking the “right total preorders” from a partial preorder of priorities between defeasible rules? Nevertheless, it would be interesting to see how the notion of unrestricted rebut interacts with the regular properties.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Recall proof of Lemma 1
     <paragraph>
      Note that for a strict argument A over a set {a mathematical formula}X⊆Ldom, the set of premises of A, {a mathematical formula}Prem(A), is defined by {a mathematical formula}Prem(A)={α∈X|[α]is a subargument of A}.
     </paragraph>
     <paragraph label="Lemma 23">
      Let{a mathematical formula}Rbe a knowledge base closed under contraposition or transposition and A be a strict argument wrt{a mathematical formula}K=(R,X)with conclusion σ. Then for each{a mathematical formula}α∈Prem(A), there is a strict argument B wrt{a mathematical formula}(R,X∪{¬σ})with{a mathematical formula}Prem(B)⊆Prem(A)∪{¬σ}and conclusion ¬α.
     </paragraph>
     <paragraph label="Proof">
      If {a mathematical formula}R is closed under contraposition, the lemma is obvious. We prove the lemma for the case of closure under transposition by induction on the structure of A.Base Case: {a mathematical formula}A=[α], {a mathematical formula}α∈X. Obvious.Inductive Case: Suppose A is of the form {a mathematical formula}[A1,…,An→σ] where {a mathematical formula}cnl(Ai)=αi. Let {a mathematical formula}α∈Prem(A). Without loss of generality, let {a mathematical formula}α∈Prem(An). From the closure under transposition, the rule {a mathematical formula}α1,…,αn−1,¬σ→¬αn also belongs to RS. Let B be the argument {a mathematical formula}A1,…,An−1,¬σ→¬αn.From the induction hypothesis, there is an argument T whose premises are in {a mathematical formula}Prem(An)∪{¬αn} and whose conclusion is ¬α.Let {a mathematical formula}T′ be the argument obtained from T by replacing each occurrence of premise {a mathematical formula}¬αn by the argument B. It is clear that {a mathematical formula}Prem(T′)⊆Prem(A)∪{¬σ} and {a mathematical formula}cnl(T′)=¬α.  □
     </paragraph>
     <paragraph label="Lemma 1">
      If{a mathematical formula}Ris closed under transposition or contraposition then{a mathematical formula}Rsatisfies the self-contradiction property.
     </paragraph>
     <paragraph label="Proof">
      Let X be a minimal inconsistent subset of {a mathematical formula}Ldom. Since X is inconsistent, there is a {a mathematical formula}λ∈Ldom such that {a mathematical formula}X⊢Rλ and {a mathematical formula}X⊢R¬λ.
     </paragraph>
     <list>
      <list-item label="–">
       Let {a mathematical formula}R be closed under contraposition. Let {a mathematical formula}x∈X. It is clear {a mathematical formula}{x,λ}⊢Rλ. Since {a mathematical formula}R is closed under contraposition, it follows obviously {a mathematical formula}{λ,¬λ}⊢R¬x. Therefore {a mathematical formula}X⊢R¬x.
      </list-item>
      <list-item label="–">
       Let {a mathematical formula}R be closed under transposition. There are two arguments {a mathematical formula}A0,A1 with premises in X and conclusions {a mathematical formula}λ,¬λ respectively. From the minimality of X, it holds: {a mathematical formula}X=Prem(A0)∪Prem(A1). Let {a mathematical formula}x∈X. Without loss of generality, suppose {a mathematical formula}x∈Prem(A0). From the Lemma 23, it follows that there exists an argument B with conclusion ¬x and {a mathematical formula}Prem(B)⊆Prem(A0)∪{¬λ}. Let A be the argument obtained by replacing each subargument of the form {a mathematical formula}[¬λ] in B by argument {a mathematical formula}A1. It is clear that {a mathematical formula}Prem(A)⊆X and the conclusion of A is ¬x. □
      </list-item>
     </list>
    </section>
    <section label="Appendix B">
     <section-title>
      Upper semilattice of regular attack relations
     </section-title>
     <paragraph label="Lemma 4">
      Let{a mathematical formula}Abe a non-empty set of attack relation assignments.
     </paragraph>
     <list>
      <list-item label="1.">
       Suppose P is a regular property and every attack relation assignment{a mathematical formula}atts∈Asatisfies P. Then{a mathematical formula}⋃Aalso satisfies P.
      </list-item>
      <list-item label="2.">
       If the attack relations assignments in{a mathematical formula}Aare regular then{a mathematical formula}⋃Ais also regular.
      </list-item>
      <list-item label="3.">
       If the attack relation assignments in{a mathematical formula}Aare weakly regular then{a mathematical formula}⋃Ais also weakly regular.
      </list-item>
     </list>
     <paragraph label="Proof">
      As statements 2, 3 follow immediately from (1), we need only to prove statement (1). Let {a mathematical formula}atts0=⋃A.
     </paragraph>
     <list>
      <list-item label="–">
       Suppose every attack relation assignment {a mathematical formula}atts∈A satisfies the property of strong subargument structure. We show that {a mathematical formula}atts0 also satisfies the property of strong subargument structure. Let {a mathematical formula}K∈CR and {a mathematical formula}A,B∈ARK.
      </list-item>
      <list-item label="–">
       Suppose every attack relation assignment {a mathematical formula}atts∈A satisfies the inconsistency-resolving property. From Theorem 1, it follows immediately that {a mathematical formula}atts0 also satisfies the inconsistency-resolving property.
      </list-item>
      <list-item label="–">
       It is obvious that {a mathematical formula}atts0 satisfies the effective rebut property if each attack relation assignment in {a mathematical formula}A satisfies this property.
      </list-item>
      <list-item label="–">
       Suppose every attack relation assignment {a mathematical formula}atts∈A satisfies the attack monotonicity property. We show that {a mathematical formula}atts0 also satisfies this property. Let {a mathematical formula}K∈CR and {a mathematical formula}A,B,C,D∈ARK such that C is a weakening of A and D is a weakening of B.
      </list-item>
      <list-item label="–">
       Suppose every attack relation assignment {a mathematical formula}atts∈A satisfies the link-orientation property. We show that {a mathematical formula}atts0 also satisfies this property. Let {a mathematical formula}K∈CR and {a mathematical formula}A,B,C∈ARK such that C is a weakening of B by {a mathematical formula}AS⊆ARK (i.e. {a mathematical formula}C∈B↓AS) and A attacks C (wrt {a mathematical formula}atts0(K)) and A does not attack AS (wrt {a mathematical formula}atts0(K)). We show that A attacks B (wrt {a mathematical formula}atts0(K)).From A attacks C (wrt {a mathematical formula}atts0(K)), it follows that there exists {a mathematical formula}atts∈A s.t. {a mathematical formula}(A,C)∈atts(K).Because A does not attack AS (wrt {a mathematical formula}atts0(K)), A does not attack AS (wrt {a mathematical formula}atts′(K) for any {a mathematical formula}atts′∈A). Therefore A does not attack AS (wrt {a mathematical formula}atts(K). Since {a mathematical formula}atts satisfies the link-orientation property, it follows that A attacks B (wrt {a mathematical formula}atts(K)). Therefore A attacks B (wrt {a mathematical formula}atts0(K)).
      </list-item>
      <list-item label="–">
       Suppose every attack relation assignment {a mathematical formula}atts∈A satisfies the context-independence property. We show that {a mathematical formula}atts0 also satisfies this property. Let {a mathematical formula}K,K′∈CR and {a mathematical formula}A,B∈ARK∩ARK′.It is clear that {a mathematical formula}(A,B)∈atts0(K) iff there exists {a mathematical formula}atts∈A s.t. {a mathematical formula}(A,B)∈atts(K) iff {a mathematical formula}(A,B)∈atts(K′) (since {a mathematical formula}atts satisfies the context-independence property) iff {a mathematical formula}(A,B)∈atts0(K′). □
      </list-item>
     </list>
     <paragraph label="Theorem 3">
      <list>
       <list-item label="1.">
        For any rule-based system{a mathematical formula}R, the normal attack relation assignment{a mathematical formula}attsnris weakly regular.
       </list-item>
       <list-item label="2.">
        Suppose the rule-based system{a mathematical formula}Rsatisfies the self-contradiction property. Then the normal attack relation assignment{a mathematical formula}attsnris regular and the canonical assignment{a mathematical formula}AttRexists and{a mathematical formula}attsnr⊆AttR.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Let {a mathematical formula}R be a rule-based system and {a mathematical formula}K∈CR.It is straightforward to see that {a mathematical formula}attsnr satisfies the property of context-independence. It is also obvious that {a mathematical formula}attsnr(K) satisfies the properties of strong subargument structure, effective rebuts.We show that {a mathematical formula}attsnr(K) satisfies the property of link-orientation.Let {a mathematical formula}A,B,C∈ARK for a knowledge base K such that C is a weakening of B by {a mathematical formula}AS⊆ARK (i.e. {a mathematical formula}C∈B↓AS) and A does not attack AS wrt {a mathematical formula}attsnr(K) and {a mathematical formula}(A,C)∈attsnr(K). There is a basic defeasible subargument {a mathematical formula}C′ of C such that either {a mathematical formula}cnl(A)=ablast(C′) or {a mathematical formula}cnl(A)=¬cnl(C′) and there is no {a mathematical formula}d∈ldr(A) s.t. {a mathematical formula}d≺last(C′). Since A does not attack AS wrt {a mathematical formula}attsnr(K), the defeasible rule {a mathematical formula}last(C′) does not occur in any argument belonging to AS. Hence {a mathematical formula}last(C′) occurs in B. Therefore {a mathematical formula}(A,B)∈attsnr(K).We next show that {a mathematical formula}attnr(K) satisfies the property of attack monotonicity.Let {a mathematical formula}K∈K and C attacks B wrt {a mathematical formula}attsnr(K) and C is a weakening of A. It is not difficult to see that if C undercuts B then A also undercuts B. Suppose now that C rebuts B (at {a mathematical formula}B′) and there is no {a mathematical formula}d∈ldr(C) s.t. {a mathematical formula}d≺last(B′). From {a mathematical formula}ldr(A)⊆ldr(C) and cnl(C) = cnl(A), it follows obviously that A rebuts B (at {a mathematical formula}B′) and there is no {a mathematical formula}d∈ldr(A) s.t. {a mathematical formula}d≺last(B′). We have proved that A also attacks B wrt {a mathematical formula}attnr.Suppose A attacks B wrt {a mathematical formula}attsnr(K) and D is a weakening of B. It is easy to see that there exists a basic defeasible subargument {a mathematical formula}B′ of B such that either {a mathematical formula}last(A)=ablast(B′) or A normal-rebuts {a mathematical formula}B′ (at {a mathematical formula}B′). It is easy to see that there is a subargument {a mathematical formula}D′ of D such that {a mathematical formula}D′ is also a weakening of {a mathematical formula}B′. Hence {a mathematical formula}last(D′)=last(B′) and {a mathematical formula}D′ is basic defeasible. It holds obviously that either {a mathematical formula}last(A)=ablast(D′) or A normal-rebuts {a mathematical formula}D′ (at {a mathematical formula}D′). A thus attacks D wrt {a mathematical formula}attsnr(K).
       </list-item>
       <list-item label="2.">
        We only need to show that {a mathematical formula}attsnr(K) satisfies the inconsistency-resolving property.Let {a mathematical formula}K∈CR. Let {a mathematical formula}S⊆ARK s.t. S is inconsistent.Let {a mathematical formula}BE0=cnl(S). Since S is inconsistent, there are two strict arguments {a mathematical formula}A,B of the knowledge base {a mathematical formula}(R,BE0) with contradictory conclusions. Let {a mathematical formula}A′ be weakening of A by replacing each subargument {a mathematical formula}[e], {a mathematical formula}e∈BE0, of A by an argument in S with conclusion e. {a mathematical formula}B′ is obtained by weakening B in the similar way. Let {a mathematical formula}BE1 be the set of premises of arguments {a mathematical formula}A′,B′. It is clear that {a mathematical formula}BE1⊆BEK.Let {a mathematical formula}MDA,MDB be the sets of maximal basic defeasible subarguments of {a mathematical formula}A′,B′ respectively.Since {a mathematical formula}A′,B′ have contradictory conclusion, it follows immediately that the set {a mathematical formula}cnl(MDA∪MDB)∪BE1 is inconsistent.Let C be a minimal inconsistent subset of {a mathematical formula}cnl(MDA∪MDA)∪BE1. Because K is consistent and {a mathematical formula}BE1⊆BEK, {a mathematical formula}C∖BE1≠∅.Let {a mathematical formula}S0 be a minimal subset of {a mathematical formula}MDA0∪MDA1 such that {a mathematical formula}cnl(S0)=C∖BE1. {a mathematical formula}S0 therefore is non-empty and finite. Because {a mathematical formula}S0 is minimal and rules do not contain non-domain atoms in their bodies, {a mathematical formula}cnl(S0) does not contain any non-domain atom.Let {a mathematical formula}LD={last(X)|X∈S0}. LD is hence finite and non-empty. From the transitivity of ⪯, it follows that ≺ is a strict partial order. Therefore ≺ is a strict partial order on LD. Thus there exists a minimal element wrt ≺ in LD. Let {a mathematical formula}A∈S0 s.t. last(A) is minimal (wrt ≺) in LD. Since {a mathematical formula}cnl(S0) does not contain any non-domain atom, {a mathematical formula}hd(last(A))∈Ldom. From the self-contradiction property, {a mathematical formula}C⊢¬hd(last(A)). We could then construct an argument B such that B rebuts A (at A) and all maximal basic defeasible subarguments of B are arguments in {a mathematical formula}S0. Therefore {a mathematical formula}ldr(B)⊆LD. Since last(A) is minimal (wrt ≺) in LD, there is no {a mathematical formula}d∈ldr(B) s.t. {a mathematical formula}d≺last(A). Therefore B normal-rebuts A, i.e. B attacks A wrt {a mathematical formula}attsnr(K) (what we need to prove). □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Lemma 7">
      <list>
       <list-item label="1.">
        {a mathematical formula}Battssatisfies all regular properties except the inconsistency-resolving and effective rebut properties.
       </list-item>
       <list-item label="2.">
        If{a mathematical formula}Rsatisfies the self-contradiction property then{a mathematical formula}Battssatisfies the inconsistency-resolving property.
       </list-item>
       <list-item label="3.">
        If{a mathematical formula}Ris basic then{a mathematical formula}Battssatisfies the effective rebut property and hence is weakly regular and{a mathematical formula}Batts=WattR.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}R=(RS,RD,⪯). Further let {a mathematical formula}R′=(RS,RD,∅). Let {a mathematical formula}attsnr′ be the normal attack relation assignment wrt {a mathematical formula}R′. It is clear that {a mathematical formula}attsnr′=Batts. From Theorem 3 (note that Batts satisfies the effective rebut property for {a mathematical formula}R′, not for {a mathematical formula}R), it is clear that assertions 1,2 hold. If {a mathematical formula}R is basic, {a mathematical formula}R=R′. Hence assertion 3 also holds. □
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Minimal removal semantics
     </section-title>
     <paragraph label="Lemma 11">
      <list>
       <list-item label="1.">
        All removal functions{a mathematical formula}FER,FAM,FLO,FCI,FSAare continuous, i.e. for each directed{a mathematical formula}Δ⊆REMASR, for each{a mathematical formula}X∈{FER,FAM,FLO,FCI,FSA}, it holds:{a mathematical formula}
       </list-item>
       <list-item label="2.">
        REMOVE is continuous and{a mathematical formula}
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      Assertion 2 follows directly from assertion 1. We prove assertion 1 below.From the definition of FER, it is easy to see that {a mathematical formula}FER(π) is constant, i.e. for any removal assignments {a mathematical formula}π,π′, {a mathematical formula}FER(π)=FER(π′). It is hence obvious that {a mathematical formula}FER(⋃Δ)=⋃FER(Δ).Let {a mathematical formula}X∈{FAM,FLO,FCI,FSA}.From Lemma 9, it is clear that {a mathematical formula}X(⋃Δ)⊇⋃X(Δ).It remains to be shown that {a mathematical formula}X(⋃Δ)⊆⋃X(Δ).
     </paragraph>
     <list>
      <list-item label="1.">
       Let {a mathematical formula}X=FAM and {a mathematical formula}K∈CR, {a mathematical formula}(A,B)∈FAM(⋃Δ)(K).Therefore
       <list>
        there is a weakening {a mathematical formula}B′ of B such that {a mathematical formula}(A,B′)∈⋃π∈Δπ(K), orthere exists a strengthening X of A such that {a mathematical formula}(X,B)∈⋃π∈Δπ(K).Hence
       </list>
       <list>
        <list-item label="–">
         there is a weakening {a mathematical formula}B′ of B and a {a mathematical formula}π∈Δ such that {a mathematical formula}(A,B′)∈π(K), or
        </list-item>
        <list-item label="–">
         there exists a strengthening X of A and a {a mathematical formula}π′∈Δ such that {a mathematical formula}(X,B)∈π′(K).
        </list-item>
       </list>
       <paragraph>
        Thus
       </paragraph>
       <list>
        <list-item label="–">
         there is a {a mathematical formula}π∈Δ such that {a mathematical formula}(A,B)∈FAM(π)(K), or
        </list-item>
        <list-item label="–">
         there exists a {a mathematical formula}π′∈Δ such that {a mathematical formula}(A,B)∈FAM(π′)(K).
        </list-item>
       </list>
       <paragraph>
        It is obvious {a mathematical formula}(A,B)∈⋃π∈ΔFAM(π)(K).
       </paragraph>
      </list-item>
      <list-item label="2.">
       Let {a mathematical formula}X=FLO and {a mathematical formula}K∈CR.{a mathematical formula} Without loss of generality, we could assume that AS is finite. Further, due to the directedness of Δ, there exists {a mathematical formula}π∈Δ s.t. {a mathematical formula}π0⊆π and {a mathematical formula}∀X∈AS:πX⊆π. Therefore it holds:{a mathematical formula}
      </list-item>
      <list-item label="3.">
       Let {a mathematical formula}X=FCI and {a mathematical formula}K∈CR.{a mathematical formula}
      </list-item>
      <list-item label="4.">
       {a mathematical formula} □
      </list-item>
     </list>
     <paragraph label="Lemma 12">
      {a mathematical formula}WattR=Batts∖lfp(REMOVE), i.e.{a mathematical formula}WattR(K)=Batts(K)∖lfp(REMOVE)(K)for each{a mathematical formula}K∈CR.
     </paragraph>
     <paragraph label="Proof">
      The lemma follows directly from Lemma 26, Lemma 25 below.  □
     </paragraph>
     <paragraph>
      Before proving Lemma 26, Lemma 25 below, we need another lemma.
     </paragraph>
     <paragraph>
      From now until the end of this section, let{a mathematical formula}
     </paragraph>
     <paragraph label="Lemma 24">
      For each i, for each{a mathematical formula}K∈CR, for all{a mathematical formula}A,B∈ARKif{a mathematical formula}(A,B)∈πi(K)then for each basic defeasible subargument X of B, if A rebuts X then{a mathematical formula}(A,X)∈πi(K).
     </paragraph>
     <paragraph label="Proof">
      By induction. It is obvious that the assertion holds for {a mathematical formula}i=0.Suppose the assertion holds for i. We show that it holds for {a mathematical formula}i+1.Let {a mathematical formula}K∈CR and {a mathematical formula}A,B∈ARK such that {a mathematical formula}(A,B)∈πi+1(K). It follows immediately that A rebuts B. From {a mathematical formula}πi+1=REMOVE(πi), it follows {a mathematical formula}(A,B)∈REMOVE(πi).
     </paragraph>
     <list>
      <list-item label="1.">
       “{a mathematical formula}(A,B)∈FER(πi)(K)”. Let X be a basic defeasible subargument of B such that A rebuts X. It is clear that {a mathematical formula}dr(B)=dr(X). Therefore from the definition of FER, {a mathematical formula}(A,X)∈FER(πi)(K).
      </list-item>
      <list-item label="2.">
       “{a mathematical formula}(A,B)∈FAM(πi)(K)”.Therefore
       <list>
        there is a weakening {a mathematical formula}B′ of B such that {a mathematical formula}(A,B′)∈πi(K), orthere exists a strengthening Z of A such that {a mathematical formula}(Z,B)∈πi(K).We consider each case in turn.
       </list>
       <list>
        <list-item label="–">
         Suppose there is a weakening {a mathematical formula}B′ of B such that {a mathematical formula}(A,B′)∈πi(K).From the induction hypothesis, for each basic defeasible subargument Y of {a mathematical formula}B′, if A rebuts Y then {a mathematical formula}(A,Y)∈πi(K).Let X be a basic defeasible subargument of B such that A rebuts X. Therefore there is a basic defeasible subargument Y of {a mathematical formula}B′ that is a weakening of X. Therefore A rebuts Y. From {a mathematical formula}(A,Y)∈πi(K), it follows that {a mathematical formula}(A,X)∈FAM(πi)(K). Thus {a mathematical formula}(A,X)∈πi+1(K).
        </list-item>
        <list-item label="–">
         Suppose there exists a strengthening Z of A such that {a mathematical formula}(Z,B)∈πi(K). From the induction hypothesis, for all basic defeasible subargument X of B, if Z rebuts X then {a mathematical formula}(Z,X)∈πi(K). It is clear that Z rebuts some argument iff A rebuts the same argument. Since Z is a strengthening of A, it follows that for each basic defeasible subargument X of B, if A rebuts X then {a mathematical formula}(Z,X)∈πi(K). Since Z is a strengthening of A, from the definition of FAM, it follows directly {a mathematical formula}(A,X)∈FAM(πi)(K)⊆πi+1(K).
        </list-item>
       </list>
      </list-item>
      <list-item label="3.">
       A rebuts B and{a mathematical formula}∃B0∈ARK,AS⊆ARK such that{a mathematical formula}B∈B0↓AS, and if A rebuts {a mathematical formula}B0 then {a mathematical formula}(A,B0)∈πi(K), and{a mathematical formula}∀Z∈AS:if A rebuts Z then(A,Z)∈πi(K).Let X be a basic defeasible subargument of B such that A rebuts X. There are two cases:
      </list-item>
      <list-item label="4.">
       “{a mathematical formula}(A,B)∈FCI(πi)(K)”. Therefore A rebuts B and {a mathematical formula}∃K′∈CR:(A,B)∈πi(K′).Let X be a basic defeasible subargument of B such that A rebuts X. From the induction hypothesis, {a mathematical formula}(A,X)∈πi(K′). Therefore {a mathematical formula}(A,X)∈FCI(πi)(K).
      </list-item>
      <list-item label="5.">
       “{a mathematical formula}(A,B)∈FSA(πi)(K)”.Therefore A rebuts B and for each basic defeasible subargument Z of B: if A rebuts Z (at Z) then {a mathematical formula}(A,Z)∈πi(K).Let X be a basic defeasible subargument of B s.t. A rebuts X. Thus for each basic defeasible subargument Y of X: if A rebuts Y (at Y) then {a mathematical formula}(A,Y)∈πi(K). Hence {a mathematical formula}(A,X)∈FSA(πi)(K). □
      </list-item>
     </list>
     <paragraph label="Lemma 25">
      For each weakly regular attack relation{a mathematical formula}atts∈WRAAR, it holds:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      Let atts be a weakly regular attack relation assignment for {a mathematical formula}R. It is clear that {a mathematical formula}atts⊆Batts∖lfp(REMOVE) iff {a mathematical formula}atts∩lfp(REMOVE)=∅‾.We show below that for each {a mathematical formula}K∈CR, {a mathematical formula}atts(K)∩π(K)=∅.We show by induction that for each {a mathematical formula}K∈CR, {a mathematical formula}atts(K)∩πi(K)=∅ holds.As {a mathematical formula}π0=∅‾, it is clear that {a mathematical formula}atts(K)∩π0(K)=∅.Suppose {a mathematical formula}atts(K)∩πi(K)=∅ holds. We want to show that {a mathematical formula}atts(K)∩πi+1(K)=∅ also holds.Suppose {a mathematical formula}∃(X,Y)∈atts(K)∩πi+1(K). From {a mathematical formula}πi+1=REMOVE(πi), there are five cases to consider.
      <list>
       Suppose {a mathematical formula}(X,Y)∈FER(πi)(K). Therefore each of {a mathematical formula}X,Y contains exactly one defeasible rule. Let the defeasible rules in X, Y be respectively {a mathematical formula}d,d′. Since X rebuts Y, it holds that {a mathematical formula}d≺d′.Since {a mathematical formula}atts satisfies the effective rebut property, it follows that {a mathematical formula}(X,Y)∉atts(K). Contradiction. Hence {a mathematical formula}(X,Y)∉FER(πi).Suppose {a mathematical formula}(X,Y)∈FAM(πi)(K).Thereforethere is a weakening {a mathematical formula}Y′ of Y such that {a mathematical formula}(X,Y′)∈πi(K), orthere exists a strengthening Z of X such that {a mathematical formula}(Z,Y)∈πi(K).From the induction hypothesis that {a mathematical formula}atts(K)∩πi(K)=∅, it follows thatthere is a weakening {a mathematical formula}Y′ of Y such that {a mathematical formula}(X,Y′)∉atts(K), orthere exists a strengthening Z of X such that {a mathematical formula}(Z,Y)∉atts(K).Since {a mathematical formula}atts satisfies the attack monotonicity (and hence also a contrapositive reading of it), it holds that {a mathematical formula}(X,Y)∉atts(K). Contradiction. Hence {a mathematical formula}(X,Y)∉FAM(πi).Suppose {a mathematical formula}(X,Y)∈FLO(πi)(K).It follows that{a mathematical formula} From the induction hypothesis that {a mathematical formula}atts(K)∩πi(K)=∅, it follows that{a mathematical formula} It follows that {a mathematical formula}(X,Y0)∉atts(K) and {a mathematical formula}∀Z∈AS:(X,Z)∉atts(K).Since {a mathematical formula}atts satisfies the link-orientation property (and hence also a contrapositive reading of it), it holds that {a mathematical formula}(X,Y)∉atts(K). Contradiction. Hence {a mathematical formula}(X,Y)∉FLO(πi).Suppose {a mathematical formula}(X,Y)∈FCI(πi)(K).Therefore X rebuts Y and {a mathematical formula}∃K′∈CR,∃i:(X,Y)∈πi(K′).From the induction hypothesis, it holds that X rebuts Y and {a mathematical formula}∃K′∈CR:X,Y∈ARK′and(X,Y)∉atts(K′).Since {a mathematical formula}atts satisfies the context-independence property (and hence also a contrapositive reading of it), it holds that {a mathematical formula}(X,Y)∉atts(K). Contradiction. Hence {a mathematical formula}(X,Y)∉FCI(πi).Suppose {a mathematical formula}(X,Y)∈FSA(πi)(K).Therefore X rebuts Y and for each basic defeasible subargument Z of Y: if X rebuts Z (at Z) then {a mathematical formula}(X,Z)∈πi(K).From the induction hypothesis that {a mathematical formula}atts(K)∩πi(K)=∅, it follows that(*) X rebuts Y and for each basic defeasible subargument Z of Y: if X rebuts Z (at Z) then {a mathematical formula}(X,Z)∉atts(K).Since {a mathematical formula}(X,Y)∈atts(K) and {a mathematical formula}atts satisfies the strong subargument structure property, X directly attacks (wrt atts(K)) some basic defeasible subargument C of Y. Therefore X rebuts C (at C). Hence {a mathematical formula}(X,C)∈atts(K). Contradiction to assertion (*). Hence {a mathematical formula}(X,Y)∉FSA(πi).Therefore
      </list>
      <paragraph>
       {a mathematical formula}(X,Y)∉πi+1(K). Contradiction. Therefore there exists no {a mathematical formula}(X,Y)∈atts(K)∩πi+1(K).  □
      </paragraph>
     </paragraph>
     <paragraph label="Lemma 26">
      {a mathematical formula}Batts∖lfp(REMOVE)is weakly regular.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}watt=Batts∖lfp(REMOVE).It is not difficult to see that for each {a mathematical formula}K∈CR, for all arguments {a mathematical formula}A,B, if A undercuts B then {a mathematical formula}(A,B)∈watt(K).
     </paragraph>
     <list>
      <list-item label="1.">
       We have proved that watt satisfies the effective rebut property.
      </list-item>
      <list-item label="2.">
       Suppose watt does not satisfy the attack monotonicity property. Let {a mathematical formula}K∈CR and {a mathematical formula}A,A′,B,B′∈ARK such that {a mathematical formula}A′ is a weakening of A and {a mathematical formula}B′ is a weakening of B and
       <list>
        {a mathematical formula}(A,B)∈watt(K) and {a mathematical formula}(A,B′)∉watt(K), or{a mathematical formula}(A′,B)∈watt(K) and {a mathematical formula}(A,B)∉watt(K).We consider each case in turn.
       </list>
       <list>
        <list-item label="–">
         Suppose {a mathematical formula}(A,B)∈watt(K) and {a mathematical formula}(A,B′)∉watt(K). Since A rebuts B and {a mathematical formula}B′ is a weakening of B, it follows that A also rebuts {a mathematical formula}B′. From {a mathematical formula}(A,B′)∉watt(K), it follows {a mathematical formula}(A,B′)∈π(K). Hence {a mathematical formula}(A,B′)∈πi(K) for some i. From the definition of REMOVE and FAM, {a mathematical formula}(A,B)∈FAM(πi)(K)⊆πi+1(K)⊆π(K). Thus {a mathematical formula}(A,B)∉watt(K). Contradiction.
        </list-item>
        <list-item label="–">
         {a mathematical formula}(A′,B)∈watt(K) and {a mathematical formula}(A,B)∉watt(K). Since A rebuts B and {a mathematical formula}A′ is a weakening of A, it follows that {a mathematical formula}A′ also rebuts B. From {a mathematical formula}(A,B)∉watt(K), it follows {a mathematical formula}(A,B)∈π(K). Hence {a mathematical formula}(A,B)∈πi(K) for some i. From the definition of REMOVE and FAM, {a mathematical formula}(A′,B)∈FAM(πi)(K)⊆πi+1(K)⊆π(K). Thus {a mathematical formula}(A′,B)∉watt(K). Contradiction.
        </list-item>
       </list>
      </list-item>
      <list-item label="3.">
       Suppose watt does not satisfy the link-orientation property. Therefore there exists {a mathematical formula}K∈CR and there are arguments {a mathematical formula}A,B,C∈ARK such that C is a weakening of B by {a mathematical formula}AS⊆ARK (i.e. {a mathematical formula}C∈B↓AS) and A attacks C (wrt watt(K)) and A does not attack AS (wrt watt(K)) and A does not attack B (wrt watt(K)).It is obvious that A does not undercut C (otherwise, A would undercut B or some in AS, and hence attacks B or some in AS). Therefore A rebuts C. Since A does not attack AS (wrt watt(K)), it follows obviously that if A rebuts any argument {a mathematical formula}X∈AS then {a mathematical formula}(A,X)∉watt(K). From {a mathematical formula}watt=Batts∖π, it holds that if A rebuts any argument {a mathematical formula}X∈AS then {a mathematical formula}(A,X)∈π(K). As A does not attack B (wrt watt(K)), it follows that if A rebuts B then {a mathematical formula}(A,B)∈π(K). Therefore {a mathematical formula}(A,C)∈FLO(π)(K)⊆π(K). From {a mathematical formula}watt=Batts∖π, it follows that {a mathematical formula}(A,C)∉watt(K). Contradiction. Hence we have proved that watt satisfies the link-orientation property.
      </list-item>
      <list-item label="4.">
       We have proved that watt satisfies the context-independence property.
      </list-item>
      <list-item label="5.">
       We show that watt satisfies the strong subargument property by showing that each of the three assertions in Definition 8 holds.
      </list-item>
     </list>
    </section>
    <section label="Appendix D">
     <section-title>
      Canonical and normal attack relation assignment
     </section-title>
     <paragraph label="Lemma 13">
      Let atts be a regular attack relation assignment for{a mathematical formula}R. Further let{a mathematical formula}K∈CR,{a mathematical formula}A,B∈ARKand{a mathematical formula}d∈ldr(A)such that the following properties hold:
     </paragraph>
     <list>
      <list-item label="–">
       A attacks B (wrt atts(K)).
      </list-item>
      <list-item label="–">
       A rebuts B (at B) and A does not rebut any proper subargument of B.
      </list-item>
      <list-item label="–">
       Both{a mathematical formula}str(B,last(B))and{a mathematical formula}str(A,d)belong to{a mathematical formula}ARK.
      </list-item>
     </list>
     <paragraph>
      The following conditions hold:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}str(A,d) attacks {a mathematical formula}str(B,last(B)) (wrt atts(K)).
      </list-item>
      <list-item label="2.">
       {a mathematical formula}d⊀last(B).
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        From the attack monotonicity, {a mathematical formula}str(A,d) attacks B. Since A does not rebut any proper subargument of B and the conclusion of A (and hence also of {a mathematical formula}str(A,d)) belongs to {a mathematical formula}Ldom, {a mathematical formula}str(A,d) does not attack any proper subargument of B. Therefore from the link-orientation property, {a mathematical formula}str(A,d) attacks {a mathematical formula}str(B,last(B)).
       </list-item>
       <list-item label="2.">
        Since atts is regular and {a mathematical formula}str(A,d) attacks {a mathematical formula}str(B,last(B)), the effective rebut property directly implies {a mathematical formula}d⊀last(B).  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Lemma 14">
      Suppose{a mathematical formula}Rbe a well-prioritized rule-based system. Further let{a mathematical formula}K∈CRand{a mathematical formula}A,B∈ARKand{a mathematical formula}d∈ldr(A)such that A rebuts B (at B) and{a mathematical formula}d≺last(B). Then{a mathematical formula}(A,B)∉AttR(K).
     </paragraph>
     <paragraph label="Proof">
      Suppose {a mathematical formula}(A,B)∈AttR(K). Let {a mathematical formula}BE0 be the set of evidences from {a mathematical formula}BEK on which arguments A,B are based, i.e. {a mathematical formula}BE0={e∈BEK|[e]is a subargument of A or B}.Let {a mathematical formula}A0=str(A,d) and {a mathematical formula}B0=str(B,last(B)). Let {a mathematical formula}BE1 be the set of evidences on which the arguments {a mathematical formula}A0,B0 are based.Since {a mathematical formula}d≺last(B), it follows from the well-prioritizedness of {a mathematical formula}R that {a mathematical formula}Δ(bd(last(B)))∪Δ(¬hd(last(B))) is consistent. Therefore {a mathematical formula}hd(last(B))∉Δ(bd(last(B))). Since {a mathematical formula}cnl(A)=¬hd(last(B)), it follows that A does not rebut any proper subargument of B.From {a mathematical formula}bd(last(B))⊆Δ(bd(last(B))), it follows {a mathematical formula}BE′=BE0∪BE1⊆Δ(cnl(A))∪Δ(bd(last(B))=Δ(¬hd(last(B)))∪Δ(bd(last(B)).From the well-prioritizedness of {a mathematical formula}R, {a mathematical formula}BE′ is consistent. Therefore {a mathematical formula}K′=(R,BE′)∈CR and the arguments {a mathematical formula}A,B,A0,B0 belong to {a mathematical formula}ARK′. From the context-independence property, it follows that A attacks B wrt {a mathematical formula}AttR(K′) by rebut at B.We have proved that A attacks B wrt {a mathematical formula}AttR(K′), A rebuts B (at B), and A does not rebut any proper subargument of B and {a mathematical formula}A,B,A0,B0 belong to {a mathematical formula}ARK′. From assertion 2 of Lemma 13, it follows that {a mathematical formula}d⊀last(B). Contradiction. We have proved that {a mathematical formula}(A,B)∉AttR(K) holds.  □
     </paragraph>
     <paragraph label="Lemma 18">
      Let{a mathematical formula}Rbe a rule-based system satisfying the self-contradiction property and{a mathematical formula}attsbe a regular attack relation assignment of{a mathematical formula}R. Further let{a mathematical formula}K∈CR. Each stable extension of{a mathematical formula}(ARK,atts(K))is also a stable extension of{a mathematical formula}(ARK,attsnr(K)).
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}K=(R,BE) and E be a stable extension of {a mathematical formula}(ARK,atts(K)).
     </paragraph>
     <list>
      <list-item label="–">
       From Theorem 3, Lemma 2 and Lemma 16, it is clear that E is conflict-free wrt {a mathematical formula}attsnr(K).
      </list-item>
      <list-item label="–">
       Suppose that A rebuts B. Therefore A rebuts B (at B) and A does not rebut any proper subargument of B.There are two cases:
      </list-item>
     </list>
    </section>
    <section label="Appendix F">
     <section-title>
      Extended knowledge bases
     </section-title>
     <paragraph label="Lemma 22">
      Let{a mathematical formula}Rbe an extended rule-based system and P be a regular property. Further let{a mathematical formula}Sbe a non-empty set of attack relation assignments wrt{a mathematical formula}Rsatisfying P. Then{a mathematical formula}⋃Salso satisfies P.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}atts0=⋃S.
     </paragraph>
     <list>
      <list-item label="–">
       Let P be the strong subargument property. We show that {a mathematical formula}atts0 also satisfies the strong subargument property. Let {a mathematical formula}K∈ER and {a mathematical formula}A,B∈ARK.
      </list-item>
      <list-item label="–">
       The proofs for other regular properties are identical to the ones in the proof of Lemma 4.  □
      </list-item>
     </list>
     <paragraph label="Theorem 13">
      <list>
       <list-item label="1.">
        For any extended rule-based system{a mathematical formula}R, the normal attack relation assignment{a mathematical formula}attsenris weakly regular.
       </list-item>
       <list-item label="2.">
        Suppose the extended rule-based system{a mathematical formula}Rsatisfies the self-contradiction property. Then the normal attack relation assignment{a mathematical formula}attsenris regular and the canonical assignment{a mathematical formula}AteRexists and{a mathematical formula}attsenr⊆AteR.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        We show that {a mathematical formula}attsenr is weakly regular. Let {a mathematical formula}K∈ER.
       </list-item>
       <list-item label="2.">
        To show that {a mathematical formula}attsenr is regular, we need to show that {a mathematical formula}attsenr(K) satisfies the inconsistency-resolving property.We first introduce a helpful notation. An assumption argument {a mathematical formula}[α] is said to be maximal assumption-subargument of an argument A iff {a mathematical formula}[α] is an assumption-subargument of A and {a mathematical formula}[α] is not a subargument of any basic defeasible argument of A.Let {a mathematical formula}S⊆ARK s.t. S is inconsistent. Let {a mathematical formula}BE0=cnl(S)∖A. Since S is inconsistent, there are two non-defeasible arguments {a mathematical formula}A0,A1 of the knowledge base {a mathematical formula}(R,BE0) with contradictory conclusions. Let {a mathematical formula}Ai′, {a mathematical formula}i=0,1, be weakening of {a mathematical formula}Ai by replacing each subargument {a mathematical formula}[e], {a mathematical formula}e∈BE0, of {a mathematical formula}Ai by an argument in S with conclusion e. Let {a mathematical formula}BE1 be the set of (non-assumption) premises of arguments {a mathematical formula}A0′,A1′. It is clear that {a mathematical formula}BE1⊆BEK.Let {a mathematical formula}MDAi={X|X is a maximal basic defeasible subargument ofAi′}∪{[α]|[α]is a maximal assumption-subargumentofAi′} for {a mathematical formula}i=0,1.Since {a mathematical formula}A0′,A1′ have contradictory conclusion, it follows immediately that the set {a mathematical formula}cnl(MDA0∪MDA1)∪BE1 is inconsistent.Let C be a minimal inconsistent subset of {a mathematical formula}cnl(MDA0∪MDA1)∪BE1. Because K is consistent and {a mathematical formula}BE1⊆BEK, {a mathematical formula}C∖BE1≠∅.Let {a mathematical formula}S0 be a minimal subset of {a mathematical formula}MDA0∪MDA1 such that {a mathematical formula}cnl(S0)=C∖BE1. {a mathematical formula}S0 therefore is non-empty and finite. Because {a mathematical formula}S0 is minimal and rules do not contain non-domain atoms in their bodies, {a mathematical formula}cnl(S0) does not contain any non-domain atom.Let {a mathematical formula}LD={last(X)|X∈S0,Xis basic defeasible}∪{α|α∈A,[α]∈S0}.LD is hence finite and non-empty.There are two cases:
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Theorem 14">
      Let{a mathematical formula}Rbe a well-prioritized extended rule-based system satisfying the self-contradiction property. The canonical attack relation assignment{a mathematical formula}AteRand the normal attack relation assignment{a mathematical formula}attsenrcoincide.
     </paragraph>
     <paragraph label="Proof">
      Because {a mathematical formula}attsenr⊆AteR, we only need to show that for each {a mathematical formula}K∈CR, if {a mathematical formula}(A,B)∉attsenr(K) then {a mathematical formula}(A,B)∉AteR(K).Let {a mathematical formula}K∈CR, {a mathematical formula}(A,B)∉attsenr(K).Suppose that {a mathematical formula}(A,B)∈AteR(K).From {a mathematical formula}(A,B)∉attsenr(K), it is clear that A neither undercuts nor undermines B. From {a mathematical formula}(A,B)∈AteR(K), it follows that A rebuts B. From {a mathematical formula}(A,B)∉attsenr(K), it holds immediately that A does not normal-rebut B.Therefore for all basic defeasible subarguments Y of B, if A rebuts Y (at Y) then {a mathematical formula}∃dY∈ldr(A) s.t. {a mathematical formula}dY≺last(Y).From {a mathematical formula}(A,B)∈AteR(K) and the regularity of {a mathematical formula}AteR, A directly attacks a basic defeasible subargument X of B wrt {a mathematical formula}AteR(K). Since A neither undercuts B nor undermines B, it follows that A neither undercuts X nor undermines X. From the property of strong subargument structure, it holds directly that A rebuts X (at X). Therefore {a mathematical formula}dX≺last(X).Let {a mathematical formula}BE0 be the set of evidences from {a mathematical formula}BEK on which arguments A,X are based, i.e. {a mathematical formula}BE0={e∈BEK|[e]is a subargumentof A or X}.Let {a mathematical formula}A0=str(A,d) and {a mathematical formula}X0=str(X,last(X)). Let {a mathematical formula}BE1 be the set of (non-assumption) evidences on which the arguments {a mathematical formula}A0,X0 are based.Since {a mathematical formula}dX≺last(X), it follows from the well-prioritizedness of {a mathematical formula}R that {a mathematical formula}Δ(bd(last(X)))∪Δ(¬hd(last(X))) is consistent. Therefore {a mathematical formula}hd(last(X))∉Δ(bd(last(X))). Since {a mathematical formula}cnl(A)=¬hd(last(X)), it follows that A does not rebut any proper subargument of X.From {a mathematical formula}bd(last(X))⊆Δ(bd(last(X))), it follows {a mathematical formula}BE′=BE0∪BE1⊆Δ(cnl(A))∪Δ(bd(last(X))=Δ(¬hd(last(X)))∪Δ(bd(last(X)).From the well-prioritizedness of {a mathematical formula}R, {a mathematical formula}BE′ is consistent. Therefore {a mathematical formula}K′=(R,BE′)∈CR and the arguments {a mathematical formula}A,X,A0,X0 belong to {a mathematical formula}ARK′. From the context-independence property, it follows that A attacks X wrt {a mathematical formula}AteR(K′).We have proved that A attacks X wrt {a mathematical formula}AteR(K′), A does not undermine X, A rebuts X (at X), and A does not rebut any proper subargument of X and {a mathematical formula}A,X,A0,X0 belong to {a mathematical formula}ARK′. From assertion 2 of Lemma 27, it follows that {a mathematical formula}dX⊀last(X). Contradiction.Therefore the assumption that {a mathematical formula}(A,B)∈AteR(K) is false.  □
     </paragraph>
     <paragraph label="Lemma 27">
      Let atts be a regular attack relation assignment for extended rule-based system{a mathematical formula}R. Further let{a mathematical formula}K∈CR,{a mathematical formula}A,B∈ARKand{a mathematical formula}d∈ldr(A)such that the following properties hold:
      <list>
       A attacks B (wrt atts(K)).A does not undermine B.A rebuts B (at B) and A does not rebut any proper subargument of B.Both{a mathematical formula}str(B,last(B))and{a mathematical formula}str(A,d)belong to{a mathematical formula}ARK.The following conditions hold:
      </list>
      <list>
       <list-item label="1.">
        {a mathematical formula}str(A,d)attacks{a mathematical formula}str(B,last(B))(wrt atts(K)).
       </list-item>
       <list-item label="2.">
        {a mathematical formula}d⊀last(B).
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        From the attack monotonicity, {a mathematical formula}str(A,d) attacks B. Since A rebuts B, A does not undercut B. Therefore A neither undercuts not undermines B. Thus {a mathematical formula}str(A,d) neither undercut not undermines B. It is also clear that {a mathematical formula}str(A,d) rebuts B and does not rebut any proper subargument of B. Therefore {a mathematical formula}str(A,d) does not attack any proper subargument of B. Therefore from the link-orientation property, {a mathematical formula}str(A,d) attacks {a mathematical formula}str(B,last(B)).
       </list-item>
       <list-item label="2.">
        Since atts is regular and {a mathematical formula}str(A,d) attacks {a mathematical formula}str(B,last(B)) and {a mathematical formula}str(A,d) does not undermine {a mathematical formula}str(B,last(B)), the effective rebut property directly implies {a mathematical formula}d⊀last(B).  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Theorem 15">
      Suppose the extended rule-based system{a mathematical formula}Rsatisfies the property of self-contradiction. Then for each{a mathematical formula}K∈CR, each stable extension wrt{a mathematical formula}attsenr(K)is also a stable extension wrt{a mathematical formula}AteR(K)and vice versa.
     </paragraph>
     <paragraph label="Proof">
      From Theorem 13, the canonical attack relation assignment {a mathematical formula}AteR exists. Since {a mathematical formula}attsenr(K)⊆AteR(K), every stable extension wrt {a mathematical formula}attsenr(K) is a stable extension wrt {a mathematical formula}AteR(K) (Lemma 28).Let {a mathematical formula}atts be a regular attack relation assignment of {a mathematical formula}R. Further let {a mathematical formula}K=(R,BE)∈CR and E be a stable extension of {a mathematical formula}(ARK,atts(K)).To show that every stable extension wrt {a mathematical formula}AteR(K) is a stable extension wrt {a mathematical formula}attsenr(K), we show that E is a stable extension wrt {a mathematical formula}attsenr(K).
     </paragraph>
     <list>
      <list-item label="–">
       From Theorem 13, Lemma 21 and Lemma 28, it is clear that E is conflict-free wrt {a mathematical formula}attsenr(K).
      </list-item>
      <list-item label="–">
       Suppose that A rebuts B and A does not undermine B. Therefore A rebuts B (at B) and A does not rebut any proper subargument of B.If A is strict then it is obvious that {a mathematical formula}(A,B)∈attsenr(K). Hence E attacks B (wrt {a mathematical formula}attsenr(K)).Suppose A is defeasible. Let S be the set consisting of all (non-assumption) evidences on which all arguments of the form {a mathematical formula}str(A,d), {a mathematical formula}d∈ldr(A) and {a mathematical formula}str(B,last(B)) are based. It is clear that {a mathematical formula}S⊆cnl(E). Let {a mathematical formula}BE′=BEK∪S. Since {a mathematical formula}BEK⊆cnl(E), it is clear {a mathematical formula}BE′⊆cnl(E). Therefore {a mathematical formula}K′=(R,BE′)∈CR. Therefore {a mathematical formula}str(A,d), {a mathematical formula}d∈ldr(A) and {a mathematical formula}str(B,last(B)) all belong to {a mathematical formula}ARK′.Since atts is regular and hence satisfies the context-independence property, A attacks B wrt {a mathematical formula}atts(K′). We have proved that A rebuts B (at B) and A does not rebut any proper subargument of B and A does not undermine B. Further for each {a mathematical formula}d∈ldr(A), both {a mathematical formula}str(A,d) and {a mathematical formula}str(B,last(B)) all belong to {a mathematical formula}ARK′.From Lemma 27, it follows that there is no {a mathematical formula}d∈ldr(A) s.t. {a mathematical formula}d≺last(B). Therefore A normal-rebuts B, i.e. A attacks B wrt normal attack relation {a mathematical formula}attsenr(K).
      </list-item>
     </list>
     <paragraph label="Lemma 28">
      Let{a mathematical formula}atts,atts′be regular attack relation assignments for an extended rule-based system{a mathematical formula}R.
     </paragraph>
     <list>
      <list-item label="1.">
       Let{a mathematical formula}K∈CRand{a mathematical formula}S⊆ARKsuch that S contains all arguments generated from its arguments. Then S is conflict-free wrt{a mathematical formula}atts(K)iff S is also conflict-free wrt{a mathematical formula}atts′(K).
      </list-item>
      <list-item label="2.">
       Suppose{a mathematical formula}atts⊆atts′. Then
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Suppose S is conflict-free wrt {a mathematical formula}atts(K) and S is not conflict-free wrt {a mathematical formula}atts′(K). Since {a mathematical formula}atts(K) and {a mathematical formula}atts′(K) have the same set of undercuts and undermines, some argument in S rebuts another. Since all subarguments of arguments in S belong to S, S is inconsistent. Because {a mathematical formula}atts(K) satisfies the inconsistency-resolving property, some argument in S is attacked (wrt atts(K)) by some generated by S. Since S contains all arguments generated from its arguments, S is not conflict-free wrt atts(K). Contradiction. Therefore S is also conflict-free wrt {a mathematical formula}atts′(K).
       </list-item>
       <list-item label="2.">
        Identical to the proof of Lemma 17. □
       </list-item>
      </list>
     </paragraph>
    </section>
    <section label="Appendix G">
     <section-title>
      Infimum of regular attack relation assignments
     </section-title>
     <paragraph>
      We only need to show that {a mathematical formula}atts is regular as the proof of the regularity of {a mathematical formula}atts′ is identical.
     </paragraph>
     <paragraph>
      It is obvious that {a mathematical formula}atts satisfies the properties of context-independence, effective rebut.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}K∈CR.
     </paragraph>
     <list>
      <list-item label="1.">
       We show that {a mathematical formula}atts(K) satisfies the property of inconsistency-resolving.Let {a mathematical formula}S⊆ARK be inconsistent. Since {a mathematical formula}R contains no strict rule, there are two arguments {a mathematical formula}X,Y∈S with contradictory conclusions. Since K is consistent and {a mathematical formula}R contains no strict rule, one of {a mathematical formula}X,Y is basic defeasible. Let Y be basic defeasible. Therefore X rebuts Y (at Y).If {a mathematical formula}X≠D then from Lemma 29 (below), {a mathematical formula}(X,Y)∈atts(K).Suppose {a mathematical formula}X=D. Since D rebuts Y (at Y), Y rebuts D (at D). It is obvious {a mathematical formula}Y≠D. From Lemma 29, {a mathematical formula}(Y,D)∈atts(K).
      </list-item>
      <list-item label="2.">
       We show that {a mathematical formula}atts(K) satisfies the property of link-orientation.Let {a mathematical formula}X,Y,Z∈ARK such that Z is a weakening of Y by {a mathematical formula}AS⊆ARK and X attacks Z (wrt {a mathematical formula}atts(K)) and X does not attack any argument in AS (wrt {a mathematical formula}atts(K)). We show that X attacks Y (wrt {a mathematical formula}atts(K)).From {a mathematical formula}(X,Z)∈atts(K) and Lemma 29, it follows that {a mathematical formula}X≠D and X rebuts Z.Since X does not attack any argument in AS (wrt {a mathematical formula}atts(K)) and {a mathematical formula}X≠D, it follows from Lemma 29 that X does not rebut any argument in AS.Therefore X rebuts Y. From {a mathematical formula}X≠D and X rebuts Y, it follows {a mathematical formula}(X,Y)∈atts(K) (Lemma 29).
      </list-item>
      <list-item label="3.">
       We show that {a mathematical formula}atts(K) satisfies the property of attack-monotonicity.Let {a mathematical formula}X,X′,Y,Y′∈ARK such that {a mathematical formula}X′ is a weakening of X and {a mathematical formula}Y′ is a weakening of Y.
      </list-item>
      <list-item label="4.">
       We show that {a mathematical formula}atts(K) satisfies the property of strong subargument structure.Let {a mathematical formula}X,Y∈ARK.
      </list-item>
     </list>
     <paragraph label="Lemma 29">
      Let{a mathematical formula}K∈CRand{a mathematical formula}X,Y∈ARK. The following assertions hold.
     </paragraph>
     <list>
      <list-item label="1.">
       X rebuts Y iff{a mathematical formula}(X,Y)∈Batts(K).
      </list-item>
      <list-item label="2.">
       {a mathematical formula}(X,Y)∈atts(K)iff{a mathematical formula}X≠Dand X rebuts Y.
      </list-item>
      <list-item label="3.">
       Let{a mathematical formula}X≠D.{a mathematical formula}(X,Y)∈atts(K)iff X rebuts Y.
      </list-item>
     </list>
     <paragraph label="Proof">
      The other direction follows obviously from the definition of atts.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>