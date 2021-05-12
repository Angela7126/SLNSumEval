<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Evaluating epistemic negation in answer set programming.
   </title>
   <abstract>
    Epistemic negation not along with default negation ¬ plays a key role in knowledge representation and nonmonotonic reasoning. However, the existing epistemic approaches such as those by Gelfond [13], [15], [14], Truszczynski [33] and Kahl et al. [18] behave not satisfactorily in that they suffer from the problems of unintended world views due to recursion through the epistemic modal operator K or M ( KF and MF are shorthands for ¬notF and not¬F, respectively). In this paper we present a new approach to handling epistemic negation which is free of unintended world views and thus offers a solution to the long-standing problem of epistemic specifications which were introduced by Gelfond [13] over two decades ago. We consider general logic programs consisting of rules of the form H←B, where H and B are arbitrary first-order formulas possibly containing epistemic negation, and define a general epistemic answer set semantics for general logic programs by introducing a novel program transformation and a new definition of world views in which we apply epistemic negation to minimize the knowledge in world views. The general epistemic semantics is applicable to extend any existing answer set semantics, such as those defined in [26], [27], [32], [1], [8], [12], [29], with epistemic negation. For illustration, we extend FLP answer set semantics of Faber et al. [8] for general logic programs with epistemic negation, leading to epistemic FLP semantics. We also extend the more restrictive well-justified FLP semantics of Shen et al. [29], which is free of circularity for default negation, to an epistemic well-justified semantics. We consider the computational complexity of epistemic FLP semantics and show that for a propositional program Π with epistemic negation, deciding whether Π has epistemic FLP answer sets is Σ3p-complete and deciding whether a propositional formula F is true in Π under epistemic FLP semantics is Σ4p-complete in general, but has lower complexity for logic programs that match normal epistemic specifications, where the complexity of world view existence and query evaluation drops by one level in the polynomial hierarchy.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Answer set programming (ASP) is a major logic programming paradigm rooted in knowledge representation and reasoning (KR) for modeling and solving knowledge-intensive search and optimization problems such as product configuration and planning [2]. In ASP, the semantics of a logic program is given by a set of intended models, called stable models or answer sets [16], [17]. Such answer sets can be defined in different ways; Lifschitz [21] listed thirteen of them in the literature. These semantics agree for normal logic programs, but show discrepancies for more general logic programs such as logic programs with aggregates [30], [8], with external sources such as description logic programs (dl-programs) [7], and with propositional or first-order formulas [26], [27], [32], [1], [12]. Most recently Shen et al. [29] introduced a new one called the well-justified FLP answer set semantics, which is fundamentally distinct from other existing answer set semantics in that every answer set of a general logic program is justified by having a level mapping and thus is free of circular justifications. This semantics has been implemented over the well-known ASP reasoner dlvhex.{sup:1}
     </paragraph>
     <paragraph>
      Negation is a key mechanism in ASP for reasoning with incomplete knowledge. There are two major types of negation, default negation and epistemic negation. A third, called strong negation, also appears in the literature; when default negation is available, strong negation is easily compiled away using new predicate symbols [17] and thus it can be omitted. By abuse of notation, in this paper we use ¬, not and ∼ to denote the three negation operators, respectively.{sup:2} For a formula F, the default negation ¬F of formula F expresses that there is no justification for adopting F in an answer set and thus F can be assumed false by default in the answer set; in contrast, the epistemic negation notF of F expresses that there is no evidence proving that F is true, i.e., F is false in some answer set. Justification in ASP is a concept defined over every individual answer set, while provability is a meta-level concept defined over a collection of answer sets, called a world view. This means the two types of negation are orthogonal operations, where default negation works locally on each individual answer set, and epistemic negation works globally at a meta level on each world view.
     </paragraph>
     <paragraph>
      With both default and epistemic negation, ASP is enabled to reason with different incomplete knowledge. For example, we can use the rule{a mathematical formula} to concisely express the presumption of innocence, which states that one is presumed innocent if there is no evidence proving s/he is guilty. We can also use rules of the form{a mathematical formula} to explicitly state Reiter's closed-world assumption (CWA) [28], i.e., if there is no evidence proving {a mathematical formula}p(X) is true we jump to the conclusion that {a mathematical formula}p(X) is false.
     </paragraph>
     <paragraph>
      However, observe that most of the existing answer set semantics, such as those defined in [17], [26], [27], [32], [1], [8], [12], [29], only support default negation and they do not allow for epistemic negation.
     </paragraph>
     <paragraph>
      Epistemic negation and specifications. In fact, the need for epistemic negation was long recognized in ASP by Gelfond in the early 1990s [13], [15] and recently revisited in [14], [33], [19], [18], [4]. In particular, Gelfond [13] showed that formalization of CWA using default and strong negations with rules of the form{a mathematical formula} as presented in [17], is problematic.{sup:3} He then proposed to address the problem using two epistemic modal operators K and M. Informally, for a formula F, {a mathematical formula}KF expresses that F is true in every answer set, and {a mathematical formula}MF expresses that F is true in some answer set. Note that {a mathematical formula}MF can be viewed as shorthand for {a mathematical formula}¬K¬F.{sup:4}
     </paragraph>
     <paragraph>
      In the sequel, by an object literal we refer to an atom A or its strong negation ∼A; a default negated literal is of the form ¬L, and a modal literal is of the form {a mathematical formula}KL, {a mathematical formula}¬KL, {a mathematical formula}ML or {a mathematical formula}¬ML, where L is an object literal.
     </paragraph>
     <paragraph>
      Gelfond [13] considered disjunctive logic programs with modal literals, called epistemic specifications, which consist of rules of the form{a mathematical formula} where each L is an object literal and each G is an object literal, a default negated literal, or a modal literal. A normal epistemic specification consists of rules of the above form with {a mathematical formula}m=1. Given a collection {a mathematical formula}A of interpretations as an assumption, a logic program Π is transformed into a modal reduct{a mathematical formula}ΠA w.r.t. the assumption {a mathematical formula}A by first removing all rules with a modal literal G that is not true in {a mathematical formula}A, then removing the remaining modal literals. The assumption {a mathematical formula}A is defined to be a world view of Π if it coincides with the collection of answer sets of {a mathematical formula}ΠA under the semantics defined in [17].
     </paragraph>
     <paragraph>
      The problem with recursion through K. More recently, Gelfond [14] addressed the problem that applying the above approach to handle modal literals may produce unintuitive world views due to recursion through K. For example, consider a logic program {a mathematical formula}Π={p←Kp}. The rule expresses that for any collection {a mathematical formula}A of answer sets of Π and any {a mathematical formula}I∈A, if p is true in all answer sets in {a mathematical formula}A, then p is true in I. This amounts to saying that if p is true in all answer sets, then p is always true (in particular in all answer sets). Obviously, this rule is not informative and does not contribute to constructively building any answer set; thus it can be eliminated from Π, leading to {a mathematical formula}Π=∅. As a result, Π is expected to have a unique answer set ∅. However, {a mathematical formula}{p} would be an answer set of Π when applying the approach of Gelfond [13]. To illustrate, consider an assumption {a mathematical formula}A={{p}}, i.e., p is assumed to be true in all interpretations in {a mathematical formula}A. Then, {a mathematical formula}Kp is true in {a mathematical formula}A and we obtain the modal reduct {a mathematical formula}ΠA={p}. This reduct has a unique answer set {a mathematical formula}{p}, which coincides with the assumption {a mathematical formula}A. Thus {a mathematical formula}A is a world view of Π under Gelfond [13]. Observe that this world view has an epistemic circular justification that can be expressed as{a mathematical formula} where the arrow ⇐ stands for “is due to.” That is, p being true in an interpretation {a mathematical formula}I={p} of the world view {a mathematical formula}A is due to {a mathematical formula}Kp being treated true in the program transformation for the modal reduct {a mathematical formula}ΠA (via the rule {a mathematical formula}p←Kp), which in turn is due to p being assumed to be true in all interpretations of {a mathematical formula}A.
     </paragraph>
     <paragraph>
      In general, a world view {a mathematical formula}A is said to have an epistemic circular justification if some object literal L being true in some interpretation {a mathematical formula}I∈A is due to {a mathematical formula}KL (or its equivalent modal literals expressing that L is true in every interpretation {a mathematical formula}J∈A) being treated true in the program transformation for the modal reduct of Π w.r.t. {a mathematical formula}A. This means that L being true in some interpretation of {a mathematical formula}A is due to L being assumed to be true in all interpretations of {a mathematical formula}A.
     </paragraph>
     <paragraph>
      To remedy the epistemic circular justification problem with recursion through K, Gelfond [14] revised the program transformation such that a modal reduct {a mathematical formula}ΠA is obtained from Π by first removing all rules of form (1) with a modal literal G that is not true in {a mathematical formula}A, then removing all modal literals {a mathematical formula}¬KL and {a mathematical formula}ML, and finally replacing all modal literals {a mathematical formula}KL by L and {a mathematical formula}¬ML by ¬L.
     </paragraph>
     <paragraph>
      It is easy to check that the logic program {a mathematical formula}Π={p←Kp} has a unique world view {a mathematical formula}{∅} when applying the revised program transformation. Unfortunately, the epistemic circular justification problem persists in other logic programs, such as {a mathematical formula}Π={q←¬Kp,p←¬q}. Consider an assumption {a mathematical formula}A={{p}}. Since {a mathematical formula}Kp is true in {a mathematical formula}A, the modal literal {a mathematical formula}¬Kp is not true in {a mathematical formula}A and thus the first rule is removed, yielding the modal reduct {a mathematical formula}ΠA={p←¬q}. This reduct has a unique answer set {a mathematical formula}{p}, which coincides with {a mathematical formula}A, hence {a mathematical formula}A is a world view of Π. Note that this world view has also an epistemic circular justification{a mathematical formula} i.e., p being true in an interpretation {a mathematical formula}I={p} of the world view {a mathematical formula}A is (via the rule {a mathematical formula}p←¬q) due to q being false in I, which in turn (via the rule {a mathematical formula}q←¬Kp) is due to {a mathematical formula}Kp being treated true and thus {a mathematical formula}¬Kp treated false in the program transformation, which is due to p being assumed to be true in all interpretations of {a mathematical formula}A.
     </paragraph>
     <paragraph>
      The problem with recursion through M. In addition to the problem of unintended world views due to recursion through K, the approaches of Gelfond [14], [13] also suffer from the problem of unintended world views due to recursion through M. Consider the logic program {a mathematical formula}Π={p←Mp}, which expresses that for any world view {a mathematical formula}A and any {a mathematical formula}I∈A, if p is true in some answer set in {a mathematical formula}A, then p is true in I. This amounts to saying that if p is true in some answer set, then p is always true, in particular in every answer set. Under the approaches of Gelfond [14], [13] this program has two world views, {a mathematical formula}{{p}} and {a mathematical formula}{∅}. Naturally, the question is whether both are intuitive; ideally, we have only one world view. If, for example, p expresses “something goes wrong,” then the program could be viewed as a paraphrase of Murphy's law: “if something can go wrong, it will go wrong,” and accordingly, the intuitive world view would be {a mathematical formula}{{p}}.
     </paragraph>
     <paragraph>
      Recent advance. Recent work of Kahl et al. [19], [18] and del Cerro et al. [4] suggests that indeed {a mathematical formula}{{p}} should be the only world view of the program {a mathematical formula}Π={p←Mp}. The supporting intuition is twofold. First, there seems no justification that this program has two world views, one derived from treating the modal literal {a mathematical formula}Mp to be true and the other from treating it false. Second, Kahl et al. [18] observed that there is a preference order over {a mathematical formula}Kp, p and {a mathematical formula}Mp in terms of the degree of conviction in establishing them w.r.t. a world view {a mathematical formula}A: in order to establish {a mathematical formula}Kp, it must be demonstrated that p belongs to all answer sets in {a mathematical formula}A; to establish p, it must be demonstrated that p belongs to a particular answer set in {a mathematical formula}A; and to establish {a mathematical formula}Mp, it is sufficient to demonstrate that p belongs to some answer set in {a mathematical formula}A. This means {a mathematical formula}Kp is of the highest conviction and thus is harder to establish than p that is harder than {a mathematical formula}Mp that is of the lowest conviction. Then, intuitively stronger literals are expected to be established from or supported by weaker ones, i.e., {a mathematical formula}Kp can be supported by p that can be supported by {a mathematical formula}Mp without incurring epistemic circular justifications. This suggests that the case that some object literal L being true in a particular answer set {a mathematical formula}I∈A is due to {a mathematical formula}ML (or its equivalent modal literals expressing that L is true in some answer set {a mathematical formula}J∈A) being treated true in the program transformation for the modal reduct of Π w.r.t. {a mathematical formula}A does not make an epistemic circular justification. Kahl et al. [18] then used this intuition to justify {a mathematical formula}{{p}} to be a world view of the logic program {a mathematical formula}{p←Mp}, where p is supported by {a mathematical formula}Mp.
     </paragraph>
     <paragraph>
      In fact, Kahl et al. [19], [18] extensively studied the problems of unintended world views due to recursion through K and M with the approaches of Gelfond [14], [13] and proposed a new program transformation by appealing to nested expressions defined by Lifschitz et al. [22]. Let Π be a logic program with rules of form (1) and {a mathematical formula}A a collection of interpretations as an assumption. The Kahl modal reduct{a mathematical formula}ΠA of Π w.r.t. {a mathematical formula}A is a nested logic program (i.e., a logic program with nested expressions), which is obtained from Π by replacing all modal literals or deleting rules according to Table 1. The assumption {a mathematical formula}A is defined to be a world view of Π if it coincides with the collection of answer sets of the nested logic program {a mathematical formula}ΠA under the semantics of Lifschitz et al. [22].
     </paragraph>
     <paragraph>
      Kahl [19] collected sixty-two interesting logic programs with modal literals and illustrated the approach with these programs. As a typical example, given an assumption {a mathematical formula}A={∅}, the Kahl modal reduct of the logic program {a mathematical formula}Π={p←Mp} w.r.t. {a mathematical formula}A is {a mathematical formula}ΠA={p←¬¬p}, which has two answer sets ∅ and {a mathematical formula}{p} under the semantics of Lifschitz et al. [22]. Thus {a mathematical formula}{∅} is not a world view. Consequently this program has a unique world view {a mathematical formula}{{p}} under the approach of Kahl et al. [19], [18].
     </paragraph>
     <paragraph>
      However, our careful study reveals three critical shortcomings of this approach:
     </paragraph>
     <list>
      <list-item label="(1)">
       The definition of the Kahl program transformation/modal reduct looks a bit ad hoc, and the variety of replacements for modal literals (see Table 1) lacks a deeper discussion or justification.{sup:5}
      </list-item>
      <list-item label="(2)">
       It is undesired to transform a logic program into a reduct containing nested expressions. As shown in Shen et al. [29], the existing semantics for nested expressions, such as those defined in [22], [11], [12], suffer from circular justifications. For example, for the logic program {a mathematical formula}Π={p←¬¬p}, {a mathematical formula}I={p} is an answer set under these semantics. Observe that this answer set has a circular justification via the self-supporting loop{a mathematical formula} i.e., p being true in I is due to I satisfying {a mathematical formula}¬¬p (via the rule {a mathematical formula}p←¬¬p), which in turn is due to p being true in I.{sup:6}For a logic program with rules of form (1), it is desirable to transform it to a regular disjunctive logic program so that the standard answer set semantics by Gelfond and Lifschitz [16], [17] can be applied.
      </list-item>
      <list-item label="(3)">
       We observe that applying the Kahl program transformation to some logic programs with recursion through M may also produce unintended world views, as illustrated in the following example.
      </list-item>
     </list>
     <paragraph label="Example 1">
      Consider the following logic program, which is borrowed from Example 29 in Appendix D of Kahl [19]:{a mathematical formula} This program is very similar to {a mathematical formula}{p←Mp} in the way that the modal operator M is used to recursively support the rule heads. Under the approaches of Gelfond [14], [13] this program has two world views, viz. {a mathematical formula}A1={{p},{q}} and {a mathematical formula}A2={∅}, where {a mathematical formula}A1 is derived from treating {a mathematical formula}Mp and {a mathematical formula}Mq to be true and {a mathematical formula}A2 derived from treating them false.Following the same intuition of Kahl et al. [19], [18] for {a mathematical formula}{p←Mp} as described above, {a mathematical formula}A1 is expected to be the only world view of this program. However, applying the Kahl program transformation to this program will produce the two world views {a mathematical formula}A1 and {a mathematical formula}A2.
     </paragraph>
     <paragraph>
      Our contributions. The goal of this paper is to address the above problems of unintended world views and provide a satisfactory solution to epistemic negation as well as epistemic specifications of Gelfond [13]. Our main contributions are summarized as follows:
     </paragraph>
     <list>
      <list-item label="(1)">
       We use modal operator not to directly express epistemic negation and define general logic programs consisting of rules of the form {a mathematical formula}H←B, where H and B are arbitrary first-order formulas possibly containing epistemic negation. Modal formulas {a mathematical formula}KF and {a mathematical formula}MF are viewed as shorthands for {a mathematical formula}¬notF and {a mathematical formula}not¬F, respectively, and thus epistemic specifications of Gelfond [13] are a special class of general logic programs.
      </list-item>
      <list-item label="(2)">
       We propose to apply epistemic negation to minimize the knowledge in world views of a general logic program Π, i.e., we apply epistemic negation to arbitrary closed first-order formulas F w.r.t. a world view and assume notF in Π to be true in the world view whenever possible; we refer to this idea as knowledge minimization with epistemic negation. It is analogous to applying default negation to minimize the knowledge in answer sets, i.e., one applies default negation to arbitrary ground atoms A w.r.t. an answer set and assumes ¬A to be true in the answer set whenever possible (CWA or minimal models); this is referred to as knowledge minimization with default negation. To this end, we introduce a novel and very simple program transformation based on epistemic negation and present a new definition of world views. Given a subset Φ of the epistemic negations notF in Π, called a guess, we transform Π into an epistemic reduct based on Φ, denoted {a mathematical formula}ΠΦ, by replacing every notF with ⊤ if it is in Φ, and with ¬F, otherwise. Let {a mathematical formula}A be the set of all answer sets of {a mathematical formula}ΠΦ. Then we call {a mathematical formula}A a candidate world view w.r.t. Φ if it agrees with Φ in the sense that every notF in Π is true in {a mathematical formula}A if it is in Φ, and false, otherwise. A candidate world view {a mathematical formula}A w.r.t. a guess Φ is defined to be a world view under our approach if Φ is maximal, i.e., there is no other candidate world view {a mathematical formula}A′ w.r.t. a guess {a mathematical formula}Φ′⊃Φ. Note that it is by applying a maximal guess Φ that we realize knowledge minimization with epistemic negation. Obviously, our definitions of program transformations and world views fundamentally differ from those of Gelfond [13], [14], and Kahl et al. [19], [18].
      </list-item>
      <list-item label="(3)">
       The approaches of Gelfond [13], [14] are said to suffer from the problem with recursion through M because they yield for the logic program {a mathematical formula}Π={p←Mp} two world views, viz. {a mathematical formula}A1={{p}} and {a mathematical formula}A2={∅}; however, although Kahl et al. [18] presented a preference order over {a mathematical formula}Kp, p and {a mathematical formula}Mp as an intuitive justification, to the best of our knowledge there has been no deeper discussion or principled justification in the literature on why {a mathematical formula}A1 is the right world view of this program and {a mathematical formula}A2 is not. In fact, there has been no formal characterization of the problem with recursion through M in the literature [14], [33], [19], [18], [4]. In this paper, we provide a formal definition of this problem in terms of knowledge minimization with epistemic negation and show that our approach to evaluating epistemic negation is free of both the problem of unintended world views due to recursion through K and the problem due to M.
      </list-item>
      <list-item label="(4)">
       The proposed approach to evaluating epistemic negation can be used to extend any existing answer set semantics with epistemic negation, such as those semantics defined in [26], [27], [32], [1], [8], [12], [29]. For illustration, we extend as a simple showcase the well-known FLP semantics of Faber et al. [8], yielding a new semantics called epistemic FLP semantics. We also extend the more restrictive well-justified FLP semantics of Shen et al. [29], which is free of circularity for default negation, to an epistemic well-justified semantics.
      </list-item>
      <list-item label="(5)">
       As satisfiability of an arbitrary general logic program is undecidable, we address the computational complexity of epistemic FLP semantics for propositional programs. In particular, we show that deciding whether a propositional program Π has epistemic FLP answer sets is {a mathematical formula}Σ3p-complete. Furthermore, we show that query evaluation, i.e., deciding whether a propositional formula is true in every epistemic FLP answer set of some world view of Π, is {a mathematical formula}Σ4p-complete in general; important fragments, e.g. programs that match normal epistemic specifications, have lower complexity.
      </list-item>
     </list>
     <paragraph>
      The paper is organized as follows. In Section 2 we introduce a first-order logic language and define logic programs with first-order formulas and epistemic negation. In Section 3 we present a novel program transformation and define epistemic reducts. In Section 4 we present a general framework for defining epistemic answer set semantics. As a simple showcase of this general semantics, in Section 5 we extend FLP answer set semantics with epistemic negation and study in depth the computational complexity of the extended semantics. In Section 6 we extend the well-justified FLP semantics with epistemic negation. In Section 7 we discuss related work, and in Section 8 we conclude with some future work.
     </paragraph>
     <paragraph>
      In order not to distract from the flow of reading, proofs of theorems are in the appendix.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this section, we introduce a first-order logic language and define logic programs with first-order formulas and epistemic negation.
     </paragraph>
     <paragraph>
      In the sequel, for a set S, {a mathematical formula}|S| denotes the number of elements in S; for two sets I and J, {a mathematical formula}I⊆J or {a mathematical formula}J⊇I denotes I is a subset of J; in particular, {a mathematical formula}I⊂J or {a mathematical formula}J⊃I denotes I is a proper subset of J.
     </paragraph>
     <section label="2.1">
      <section-title>
       A first-order logic language
      </section-title>
      <paragraph>
       We follow the notation in [29] and define a first-order logic language {a mathematical formula}LΣ with equality over a signature{a mathematical formula}Σ=(P,F), where {a mathematical formula}P and {a mathematical formula}F are countable sets of predicate and function symbols, respectively; {a mathematical formula}C⊆F denotes the set of 0-ary function symbols, which are called constants. Variables, terms, atoms and literals are defined as usual. We denote variables with strings starting with X, Y or Z.
      </paragraph>
      <paragraph>
       First-order formulas (briefly formulas) are constructed as usual from atoms using connectives ¬, ∧, ∨, ⊃, ⊤, ⊥, ∃ and ∀, where ⊤ and ⊥ are two 0-place logical connectives expressing true and false, respectively. Formulas are closed if they contain no free variables, i.e., each variable occurrence is in the scope of some quantifier. A first-order theory (or theory) is a set of closed formulas. Terms, atoms and formulas are ground if they have no variables, and propositional if they contain no variables, no function symbols except constants, and no equalities. By {a mathematical formula}NΣ we denote the set of all ground terms of Σ, and by {a mathematical formula}HΣ the set of all ground atoms.
      </paragraph>
      <paragraph>
       In this paper we consider SNA interpretations, i.e., interpretations which employ the well-known standard names assumption (SNA) [3], [24]. An SNA interpretation (or interpretation for short) I of {a mathematical formula}LΣ is a subset of {a mathematical formula}HΣ such that for any ground atom A, I satisfies A if {a mathematical formula}A∈I, and I satisfies ¬A if {a mathematical formula}A∉I. The notion of satisfaction/models of a formula/theory in I is defined as usual. A theory T is consistent or satisfiable if T has a model. We say that T entails a closed formula F, denoted {a mathematical formula}T⊨F, if all models of T are models of F. Furthermore F is true (resp. false) in an interpretation I if I satisfies (resp. does not satisfy) F.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Logic programs with epistemic negation
      </section-title>
      <paragraph>
       Based on the first-order logic language {a mathematical formula}LΣ defined above, we introduce the syntax of a logic program with epistemic negation and define its grounding, satisfaction and models.
      </paragraph>
      <section label="2.2.1">
       <section-title>
        Syntax
       </section-title>
       <paragraph>
        As in [29] and early AI literature, default negation will be expressed by giving the connective ¬ a special meaning; i.e., we use ¬ to denote the default negation operator. We further extend the language {a mathematical formula}LΣ to include the epistemic negation operator not and the rule operator ←.
       </paragraph>
       <paragraph>
        Epistemic formulas are constructed from atoms using the connectives {a mathematical formula}¬,∧,∨,⊃,⊤,⊥, {a mathematical formula}∃,∀ together with the operator not in the same way as first-order formulas. An epistemic negation is an epistemic formula of the form notF, where F is an epistemic formula; it is non-nested if F contains no epistemic negation, and nested, otherwise. An epistemic formula is closed if it contains no free variables.
       </paragraph>
       <paragraph>
        Let E be an epistemic formula and {a mathematical formula}E′ be E with every free variable replaced by a constant (this process is called grounding). E is instance-closed (w.r.t. epistemic negation) if for every epistemic negation notF in {a mathematical formula}E′, F itself is a closed epistemic formula. For instance, {a mathematical formula}person(X)∧notguilty(X) is an instance-closed epistemic formula, as when the free variable X is replaced by a constant, the epistemic negation {a mathematical formula}notguilty(X) will become closed; however, {a mathematical formula}∀X(person(X)∧notguilty(X)) is not instance-closed because X is not a free variable and the epistemic negation {a mathematical formula}notguilty(X) will not become closed after grounding.
       </paragraph>
       <paragraph>
        We use instance-closed epistemic formulas to construct rules and logic programs.
       </paragraph>
       <paragraph label="Definition 1">
        General logic programA general logic program (logic program for short) is a finite set of rules of the form {a mathematical formula}H←B, where H and B are instance-closed epistemic formulas without nested epistemic negations.
       </paragraph>
       <paragraph>
        Note that like the approaches of Gelfond [14] and Kahl et al. [18], where modal operators K and M are not nested in logic programs, we do not consider logic programs with nested epistemic negations (not is also a modal operator); a nested epistemic negation like {a mathematical formula}not(notF) intuitively expresses “That F cannot be proved to be true cannot be proved to be true” and such expressions seem to have rare applications in practical scenarios.
       </paragraph>
       <paragraph>
        For convenience, for a rule {a mathematical formula}r:H←B we refer to B and H as the body and head of r, denoted {a mathematical formula}body(r) and {a mathematical formula}head(r), respectively. When {a mathematical formula}head(r) is empty, we rewrite the rule as {a mathematical formula}⊥←body(r); when {a mathematical formula}body(r) is empty, we omit the rule operator ←.
       </paragraph>
       <paragraph label="Definition 2">
        Normal epistemic programA normal epistemic program is a logic program consisting of rules of the form{a mathematical formula} where {a mathematical formula}n≥m≥0 and each {a mathematical formula}Ai is an atom without equality and function symbols except constants.
       </paragraph>
       <paragraph>
        Furthermore, as usual a normal logic program consists of rules of the above form (4) except that epistemic negation not is replaced by default negation ¬; a positive logic program is a ¬-free normal logic program.
       </paragraph>
       <paragraph label="Definition 3">
        Propositional programA propositional program Π is a logic program which contains no variables, no function symbols except constants, and no equalities. The Herbrand base of Π is defined as usual. Any subset of the Herbrand base is a Herbrand interpretation of Π.
       </paragraph>
      </section>
      <section label="2.2.2">
       <section-title>
        Grounding
       </section-title>
       <paragraph>
        In a logic program Π, some rules may contain free variables. In ASP, these free variables will be instantiated by constants from a finite set − usually the set {a mathematical formula}CΠ of constants occurring in Π. Without loss of generality, we assume that {a mathematical formula}CΠ consists of all constants in Π (in case that some constant a of the domain does not appear in Π, we may have it by adding to Π a dummy rule {a mathematical formula}p(a)←p(a)). Then for any logic program Π, {a mathematical formula}CΠ is unique.
       </paragraph>
       <paragraph>
        A closed instance of a rule is the rule with all free variables replaced by constants in {a mathematical formula}CΠ. The grounding of Π, denoted {a mathematical formula}ground(Π), is the set of all closed instances of all rules in Π.
       </paragraph>
       <paragraph>
        Note that each rule {a mathematical formula}H←B with the set S of free variables may also be viewed as a globally universally quantified rule {a mathematical formula}∀S(H←B), where the domain of each variable in S is {a mathematical formula}CΠ while the domain of the other (locally quantified) variables is {a mathematical formula}NΣ. Only globally universally quantified variables will be instantiated over their domain {a mathematical formula}CΠ for the grounding {a mathematical formula}ground(Π).
       </paragraph>
       <paragraph>
        To sum up, a logic program Π is viewed as shorthand for {a mathematical formula}ground(Π), where each free variable in Π is viewed as shorthand for constants in {a mathematical formula}CΠ.
       </paragraph>
       <paragraph>
        As rule bodies and heads in Π are instance-closed epistemic formulas, for every epistemic negation notF in {a mathematical formula}ground(Π), F itself is a closed epistemic formula. Therefore, in the sequel unless otherwise stated, for any epistemic negation notF we assume F is a closed epistemic formula.
       </paragraph>
      </section>
      <section label="2.2.3">
       <section-title>
        Satisfaction and models
       </section-title>
       <paragraph>
        Next, we extend the satisfaction relation of {a mathematical formula}LΣ to logic programs. As epistemic negation works at a meta level over a collection of interpretations, the definition of satisfaction/models of epistemic formulas should be based on a collection of interpretations.
       </paragraph>
       <paragraph label="Definition 4">
        Let {a mathematical formula}A be a collection of interpretations and {a mathematical formula}I∈A.
       </paragraph>
       <list>
        <list-item label="(1)">
         Let F be a closed formula. Then notF is true in {a mathematical formula}A (or {a mathematical formula}A satisfies notF) if F is false in some {a mathematical formula}J∈A, and false, otherwise. Furthermore I satisfies notF w.r.t. {a mathematical formula}A if notF is true in {a mathematical formula}A.
        </list-item>
        <list-item label="(2)">
         I satisfies a closed epistemic formula E w.r.t. {a mathematical formula}A if I satisfies E as in first-order logic except that the satisfaction of epistemic negations in E is determined by (1).
        </list-item>
        <list-item label="(3)">
         I satisfies a closed instance r of a rule w.r.t. {a mathematical formula}A if I satisfies {a mathematical formula}head(r) w.r.t. {a mathematical formula}A once I satisfies {a mathematical formula}body(r) w.r.t. {a mathematical formula}A.
        </list-item>
        <list-item label="(4)">
         {a mathematical formula}A is a collection of models of a logic program Π if every {a mathematical formula}J∈A satisfies all rules in {a mathematical formula}ground(Π) w.r.t. {a mathematical formula}A. In this case, every {a mathematical formula}J∈A is a model of Π (w.r.t. {a mathematical formula}A). The program Π is consistent if it has a model.
        </list-item>
       </list>
       <paragraph>
        Observe the following properties of satisfaction of a logic program Π.
       </paragraph>
       <paragraph>
        First, when Π contains no epistemic negation, satisfaction in Definition 4 reduces to that in first-order logic. In this case, we omit {a mathematical formula}A. Then I satisfies a closed rule instance r if I satisfies {a mathematical formula}head(r) or I does not satisfy {a mathematical formula}body(r), and I is a model of Π if it satisfies all rules in {a mathematical formula}ground(Π); moreover, a model I is minimal if Π has no model J that is a proper subset of I.
       </paragraph>
       <paragraph>
        Second, satisfaction of an epistemic negation notF in I w.r.t. {a mathematical formula}A is determined only by {a mathematical formula}A, i.e., I can be ignored.
       </paragraph>
       <paragraph>
        Finally, when {a mathematical formula}A consists of a single interpretation I, the notions of satisfaction, models and consistency are the same as in first-order logic, i.e., they are determined only by I and {a mathematical formula}A can be ignored. In this special case, the epistemic negation operator not coincides with the operator ¬, i.e., I satisfies notF w.r.t. {a mathematical formula}A iff I satisfies ¬F iff F is false in I, where F is a closed formula. Hence the following proposition is immediate.
       </paragraph>
       <paragraph label="Proposition 1">
        Let Π be a logic program and{a mathematical formula}Π¬be Π with all epistemic negationsnotF replaced by default negations ¬F. For any interpretation I,{a mathematical formula}A={I}is a collection of models of Π iff I is a model of{a mathematical formula}Π¬.
       </paragraph>
       <paragraph>
        The following theorem is important, as it lays a theoretical basis for the introduction of our novel program transformation, which is described in the next section.
       </paragraph>
       <paragraph label="Theorem 1">
        Let Π be a logic program such that for everynotF in{a mathematical formula}ground(Π), F is true in every model of Π. Let{a mathematical formula}Π¬be Π with each epistemic negationnotF replaced by default negation ¬F. Then Π and{a mathematical formula}Π¬have the same models.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Program transformation and epistemic reducts
     </section-title>
     <paragraph>
      In ASP, it is common to transform a logic program into a reduct which is free of negation or modal operators. For instance, for a normal logic program Π, the seminal GL-reduct{a mathematical formula}ΠI w.r.t. a given interpretation I is obtained from {a mathematical formula}ground(Π) by removing first all rules whose bodies contain a default negation ¬A with {a mathematical formula}A∈I, and then all ¬A from the remaining rules [16]. Similarly, when Π is a logic program extended with modal operators K and M, Gelfond [13], [14], Truszczynski [33] and Kahl [19] defined a transformation w.r.t. a given set {a mathematical formula}A of interpretations by eliminating/replacing all modal literals in {a mathematical formula}ground(Π) in terms of whether or not they are true in {a mathematical formula}A.
     </paragraph>
     <paragraph>
      Note that these existing definitions of program transformations are based on an assumption, which is either a given interpretation or a given set of interpretations, and default negations or modal literals in a logic program are evaluated against the assumption.
     </paragraph>
     <paragraph>
      In this paper we aim to apply epistemic negation to minimize the knowledge in a world view of a general logic program Π by assuming every epistemic negation notF in Π to be true in the world view whenever possible. To this end, we define program transformations in an alternative way, which is based on an assumption that is a given set of epistemic negations, instead of a given set of interpretations.
     </paragraph>
     <paragraph label="Definition 5">
      For a logic program Π, let {a mathematical formula}Ep(Π) denote the set of all epistemic negations notF in {a mathematical formula}ground(Π). A guess of epistemic negations for Π is a subset Φ of {a mathematical formula}Ep(Π).
     </paragraph>
     <paragraph>
      Intuitively for every {a mathematical formula}notF∈Φ, it is guessed that F couldn't be proved true, and for every {a mathematical formula}notF∈Ep(Π)∖Φ, it is guessed that F would be proved true. Recall that an epistemic negation notF expresses that there is no evidence proving that F is true, where F is proved true if it is true in every answer set of some world view.
     </paragraph>
     <paragraph>
      Once a guess Φ is given, we can transform program Π by replacing all epistemic negations in terms of Φ. There would be different replacements for epistemic negations, which would lead to different program transformations. The simplest yet naive one is to replace notF with ⊤ if {a mathematical formula}notF∈Φ, and with ⊥, otherwise. It turns out that this transformation incurs both the problem of unintended world views due to recursion through K and the problem due to recursion through M, analogously to the cases in [13].
     </paragraph>
     <paragraph>
      The key idea of our program transformation is as follows. We first assume that the guess on all {a mathematical formula}notF∈Φ is correct and thus replace them with ⊤. Then, for every {a mathematical formula}notF∈Ep(Π)∖Φ, instead of replacing it with ⊥, we replace it with ¬F. The intuition and rationale for the latter replacement is as follows: if Φ is a correct guess, once all epistemic negations {a mathematical formula}notF∈Φ in {a mathematical formula}ground(Π) are replaced with ⊤, which leads to a new program {a mathematical formula}Π⊤, for every notF in {a mathematical formula}Π⊤, the formula F is supposed to be true in every answer set of {a mathematical formula}Π⊤. Let {a mathematical formula}ΠΦ be {a mathematical formula}Π⊤ with each notF replaced by ¬F; then by Theorem 1, where model is analogously replaced by answer set, we expect that {a mathematical formula}Π⊤ and {a mathematical formula}ΠΦ have the same answer sets. This rational justification of the replacements for epistemic negations leads to the following novel program transformation.
     </paragraph>
     <paragraph label="Definition 6">
      Epistemic reductsLet Π be a logic program and let {a mathematical formula}Φ⊆EP(Π) be a guess of epistemic negations for Π. The epistemic reduct{a mathematical formula}ΠΦ of Π w.r.t. Φ is obtained from {a mathematical formula}ground(Π) by replacing every {a mathematical formula}notF∈Φ with ⊤, and every {a mathematical formula}notF∈Ep(Π)∖Φ with ¬F. We call Π consistent w.r.t. Φ if {a mathematical formula}ΠΦ is consistent.
     </paragraph>
     <paragraph>
      In the Introduction we mentioned that a world view {a mathematical formula}A is said to have an epistemic circular justification if some object literal L being true in some interpretation {a mathematical formula}I∈A is due to {a mathematical formula}KL (or its equivalent modal literals expressing that L is true in every interpretation {a mathematical formula}J∈A) being treated true in the program transformation w.r.t. {a mathematical formula}A. In our language, {a mathematical formula}KL is shorthand for {a mathematical formula}¬notL, and in our program transformation w.r.t. a guess Φ, {a mathematical formula}¬notL will be either treated ¬⊤ (when {a mathematical formula}notL∈Φ), which evaluates to false, or treated {a mathematical formula}¬¬L (when {a mathematical formula}notF∈Ep(Π)∖Φ), which evaluates to L. This means that our definition of the program transformation would never incur epistemic circular justifications and thus guarantees that world views based on the epistemic reducts will be free of the problem with recursion through K.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      A general epistemic answer set semantics
     </section-title>
     <paragraph>
      Now that all epistemic negations have been removed from a logic program Π, leading to an epistemic reduct {a mathematical formula}ΠΦ w.r.t. a guess Φ, we can apply any answer set semantics for logic programs without epistemic negation to compute all answer sets {a mathematical formula}A of {a mathematical formula}ΠΦ. For {a mathematical formula}A to be a world view, it must agree with the guess Φ, i.e., every {a mathematical formula}notF∈Φ is true and every {a mathematical formula}notF∈Ep(Π)∖Φ is false in {a mathematical formula}A; it should also satisfy the property of knowledge minimization with epistemic negation, as defined below.
     </paragraph>
     <paragraph label="Definition 7">
      A world view {a mathematical formula}A of a logic program Π is said to have the property of knowledge minimization with epistemic negation if {a mathematical formula}A satisfies a maximal set Φ of epistemic negations in {a mathematical formula}Ep(Π) (i.e., no other world view satisfies a set {a mathematical formula}Φ′⊃Φ of epistemic negations in {a mathematical formula}Ep(Π)).
     </paragraph>
     <paragraph>
      In this section, we present a general framework for defining epistemic answer set semantics, thus called a general epistemic answer set semantics, which is applicable to extend any existing answer set semantics with epistemic negation.
     </paragraph>
     <paragraph label="Definition 8">
      General epistemic semanticsLet Π be a logic program and let Φ be a guess such that {a mathematical formula}ΠΦ is a consistent epistemic reduct. Let {a mathematical formula}X be an answer set semantics for logic programs without epistemic negation. The collection {a mathematical formula}A of all answer sets of {a mathematical formula}ΠΦ under {a mathematical formula}X is a candidate world view of Π w.r.t. Φ if (a) {a mathematical formula}A≠∅, (b) every {a mathematical formula}notF∈Φ is true in {a mathematical formula}A, and (c) every {a mathematical formula}notF∈Ep(Π)∖Φ is false in {a mathematical formula}A. A candidate world view {a mathematical formula}A w.r.t. a guess Φ is a world view if Φ is maximal (i.e., there is no other candidate world view w.r.t. a guess {a mathematical formula}Φ′⊃Φ).
     </paragraph>
     <paragraph>
      The condition “Φ is maximal” implies that world views under the general epistemic semantics have the property of knowledge minimization with epistemic negation.
     </paragraph>
     <paragraph>
      In this paper, when we say that a formula F is true in a logic program Π, we mean that F is proved true in Π. Recall that a formula is proved true if it is true in every answer set of some world view. Therefore, we define the following form of query evaluation.{sup:7}
     </paragraph>
     <paragraph label="Definition 9">
      Query evaluationLet Π be a logic program and F a closed formula. We say F is true in Π under the general epistemic semantics if Π has a world view {a mathematical formula}A such that F is true in every answer set in {a mathematical formula}A.
     </paragraph>
     <paragraph>
      Now we are ready to introduce the following formal definition of the problem of unintended world views with recursion through M, which was informally described in the Introduction.
     </paragraph>
     <paragraph label="Definition 10">
      The problem with recursion through MAn epistemic answer set semantics is said to have the problem of unintended world views due to recursion throughM if its world views do not satisfy the property of knowledge minimization with epistemic negation.
     </paragraph>
     <paragraph>
      The above formulation shows that in essence, an epistemic answer set semantics with the problem with recursion through M fails to make full use of the epistemic negations notF occurring in a logic program to minimize the knowledge by allowing these epistemic negations to be true in world views whenever possible. This will be further illustrated in Example 6.
     </paragraph>
     <paragraph>
      Obviously, our general epistemic answer set semantics is free of the problem with recursion through M.
     </paragraph>
     <paragraph label="Remark 1">
      We stress that default negation and epistemic negation are used to minimize the knowledge at the answer set level and the world view level, respectively, and the notion of positive knowledge to be minimized at the answer set level is different from that at the world view level. At the answer set level, where default negation ¬ is used, any ground atom is the positive knowledge to be minimized in answer sets; but at the world view level, where epistemic negation not is used, any closed (first-order) formula is the positive knowledge to be minimized in world views. Specifically, at the answer set level, for any ground atom A we assume its default negation ¬A to be true in every answer set whenever possible (knowledge minimization with default negation); analogously at the world view level, for any closed formula F we assume its epistemic negation notF occurring in a logic program to be true in every world view whenever possible (knowledge minimization with epistemic negation). As a result, by applying default negation we minimize the knowledge in every answer set, and by applying epistemic negation we minimize the knowledge in every world view. Since epistemic negation is at a meta level, in our approach the minimization with epistemic negation has higher priority and is done before the minimization with default negation.Note that if one intends to apply epistemic negation to a formula F by assuming notF to be true in every world view whenever possible, one must explicitly express the epistemic negation notF in a logic program. Thus the following four programs{a mathematical formula} are entirely different and have different world views: {a mathematical formula}Π1 has a unique world view {a mathematical formula}{{p}{q}}, {a mathematical formula}Π2 has a unique one {a mathematical formula}{{p}}, {a mathematical formula}Π3 has a unique one {a mathematical formula}{{q}}, and {a mathematical formula}Π4 has two world views {a mathematical formula}{{p}} and {a mathematical formula}{{q}}.In contrast, for any ground atom A its default negation ¬A is implicitly assumed to be true in every answer set whenever possible, whether or not ¬A is present in a logic program. Thus the following four programs{a mathematical formula} have the same answer sets {a mathematical formula}{p} and {a mathematical formula}{q} under the existing answer set semantics defined in [17], [26], [27], [32], [1], [8], [12], [29].
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      FLP answer set semantics with epistemic negation
     </section-title>
     <paragraph>
      The general framework of Definition 8 is applicable to extend any existing answer set semantics, such as those defined in [26], [27], [32], [1], [8], [12], [29], with epistemic negation; as a simple showcase, we extend in this section the well-known FLP answer set semantics of Faber et al. [8] to logic programs with epistemic negation. The FLP semantics coincides with the stable model respectively answer set semantics for normal and disjunctive logic programs in [16], [17], and can be regarded as a base semantics for extensions of logic programs beyound aggregates [6]. The following definition is from Shen et al. [29], which lifts Faber et al.'s FLP semantics to general logic programs without epistemic negation.
     </paragraph>
     <paragraph label="Definition 11">
      Let Π be a logic program without epistemic negation and I an interpretation. The FLP-reduct of Π w.r.t. I is {a mathematical formula}fΠI={r∈ground(Π)|I satisfies body(r)}, and I is an FLP answer set of Π if I is a minimal model of {a mathematical formula}fΠI.
     </paragraph>
     <paragraph>
      By replacing {a mathematical formula}X with FLP in Definition 8, we obtain an epistemic FLP answer set semantics (EFLP semantics for short).
     </paragraph>
     <paragraph label="Definition 12">
      EFLP semanticsLet Π be a logic program and Φ a guess such that {a mathematical formula}ΠΦ is a consistent epistemic reduct. The collection {a mathematical formula}A of all FLP answer sets of {a mathematical formula}ΠΦ is a candidate world view, resp. a world view, of Π w.r.t. Φ if {a mathematical formula}A satisfies the conditions of Definition 8. Every FLP answer set in a world view is called an EFLP answer set.
     </paragraph>
     <paragraph>
      Obviously, for logic programs without epistemic negation, {a mathematical formula}Ep(Π)=∅ and EFLP semantics reduces to FLP semantics.
     </paragraph>
     <paragraph>
      The following result shows that EFLP answer sets of Π are models of Π.
     </paragraph>
     <paragraph label="Theorem 2">
      Let Π be a logic program and let{a mathematical formula}Abe a world view of Π w.r.t. a guess Φ under EFLP semantics. Then{a mathematical formula}Ais a collection of models of Π.
     </paragraph>
     <paragraph>
      Let Π be a normal epistemic program and {a mathematical formula}Π¬ be the normal logic program obtained from Π by replacing epistemic negation not with default negation ¬. Let I be an interpretation and {a mathematical formula}(Π¬)I be the GL-reduct of {a mathematical formula}Π¬; then I is a standard answer set of {a mathematical formula}Π¬ if I is the least model of {a mathematical formula}(Π¬)I[16].
     </paragraph>
     <paragraph>
      The following result shows that answer sets of a normal epistemic program Π under EFLP semantics coincide with those of {a mathematical formula}Π¬ under the standard answer set semantics.
     </paragraph>
     <paragraph label="Theorem 3">
      Let Π be a normal epistemic program and let{a mathematical formula}Π¬be the normal logic program obtained from Π by replacingnotwith ¬. Then (1) every world view{a mathematical formula}Aof Π fulfills{a mathematical formula}|A|=1(i.e.,{a mathematical formula}Ais a singleton), and (2){a mathematical formula}A={I}is a world view of Π iff I is an FLP answer set of{a mathematical formula}Π¬iff I is a standard answer set of{a mathematical formula}Π¬.
     </paragraph>
     <paragraph>
      Next we consider a few simple examples to illustrate the novelty and suitability of our approach. Interested readers may apply the approach to more examples collected in [19], [18].
     </paragraph>
     <paragraph label="Example 2">
      The following logic program uses epistemic negation to formalize the well-known presumption of innocence:{a mathematical formula} Rule {a mathematical formula}r1 says that John is either innocent or guilty, and rule {a mathematical formula}r2 asserts that one is presumed innocent if there is no evidence proving s/he is guilty. From this program we intend to arrive at the conclusion that John is innocent; specifically, {a mathematical formula}innocent(John) is expected to be in every answer set of every world view of {a mathematical formula}Π1.The grounding of {a mathematical formula}Π1 is{a mathematical formula} It contains only one epistemic negation, thus {a mathematical formula}Ep(Π1)={notguilty(John)}. So we have two guesses: {a mathematical formula}Φ1={notguilty(John)} and {a mathematical formula}Φ2=∅.We start with the largest guess {a mathematical formula}Φ1 and check if there is a world view w.r.t. {a mathematical formula}Φ1. Note {a mathematical formula}Ep(Π1)∖Φ1=∅. The epistemic reduct w.r.t. {a mathematical formula}Φ1 is{a mathematical formula}{a mathematical formula}Π1Φ1 is consistent and has a unique FLP answer set {a mathematical formula}I={innocent(John)}. Let {a mathematical formula}A={I}. As {a mathematical formula}guilty(John) is false in I, {a mathematical formula}notguilty(John) is true in {a mathematical formula}A, thus {a mathematical formula}A is a candidate world view of {a mathematical formula}Π1. Since {a mathematical formula}Φ1 is the largest guess, {a mathematical formula}A is a world view of {a mathematical formula}Π1 w.r.t. {a mathematical formula}Φ1.As {a mathematical formula}Φ2⊂Φ1, there would be no world view w.r.t. {a mathematical formula}Φ2. Hence, {a mathematical formula}Π1 has only one world view {a mathematical formula}A={{innocent(John)}}. Therefore, the formula {a mathematical formula}innocent(John) is true in {a mathematical formula}Π1, meaning that John is innocent. This conforms to our expectation.
     </paragraph>
     <paragraph label="Example 3">
      To demonstrate the necessity of epistemic reasoning with epistemic negation, Gelfond [13] introduced the well-known college scholarship awarding problem with the following logic program:{a mathematical formula} Gelfond argued that Mike was intended to be interviewed, i.e., {a mathematical formula}interview(Mike) should be included in every answer set of {a mathematical formula}Π2; however, he observed that the fourth rule {a mathematical formula}r4 was not powerful enough to formalize the intended statement that the students whose eligibility is not determined by the college rules should be interviewed by the scholarship committee. It was due to this observation that Gelfond [13], [14] proposed his modal formalism in which {a mathematical formula}r4 was replaced by the rule{a mathematical formula}Next, we show that this problem can be suitably handled using epistemic negation under EFLP semantics. As shown in [17], for any atom {a mathematical formula}p(X), the strong negation ∼{a mathematical formula}p(X) can be compiled away by introducing a fresh predicate {a mathematical formula}p′(X) along with a rule {a mathematical formula}⊥←p(X)∧p′(X). We formulate the above problem by rewriting {a mathematical formula}Π2 by replacing ¬ with not and ∼{a mathematical formula}eligible(X) with {a mathematical formula}eligible′(X), and adding the rule {a mathematical formula}⊥←eligible(X)∧eligible′(X); this yields a new program {a mathematical formula}Π2′ with the grounding{a mathematical formula}{a mathematical formula}Ep(Π2′)={noteligible(Mike), {a mathematical formula}noteligible′(Mike)}, so there are four guesses. We start with the largest guess {a mathematical formula}Φ1={noteligible(Mike),noteligible′(Mike)} and check if {a mathematical formula}Π2′ has a world view w.r.t. {a mathematical formula}Φ1.The epistemic reduct {a mathematical formula}Π2′Φ1 w.r.t. {a mathematical formula}Φ1 is {a mathematical formula}ground(Π2′) except that {a mathematical formula}r4′ is replaced by the rule{a mathematical formula}{a mathematical formula}Π2′Φ1 is consistent and has the following two FLP answer sets:{a mathematical formula} Let {a mathematical formula}A={I1,I2}. As {a mathematical formula}eligible(Mike) and {a mathematical formula}eligible′(Mike) are both false in {a mathematical formula}I1, both {a mathematical formula}noteligible(Mike) and {a mathematical formula}noteligible′(Mike) are true in {a mathematical formula}A. As {a mathematical formula}Ep(Π2′)∖Φ1=∅ and {a mathematical formula}Φ1 is the largest guess, {a mathematical formula}A is a unique world view of {a mathematical formula}Π2′.Note that {a mathematical formula}interview(Mike) appears in every answer set in {a mathematical formula}A and thus is true in this logic program. Therefore, Mike should be interviewed, as we expected.
     </paragraph>
     <paragraph label="Remark 2">
      We can also formulate the above problem without using strong negation by rewriting {a mathematical formula}Π2 with ¬ replaced by not, and ∼ by ¬; thus {a mathematical formula}r4 is rewritten as{a mathematical formula} This rule directly expresses that a student should be interviewed if we can neither prove s/he is eligible nor not eligible. Then, the grounding of the new program consists of {a mathematical formula}r1′,r2′,r5, and the following two rules:{a mathematical formula} It is easy to check that this new program has a unique world view {a mathematical formula}A={I1,I2} w.r.t. the largest guess {a mathematical formula}Φ1={noteligible(Mike),not¬eligible(Mike)}, where{a mathematical formula} which shows that Mike should be interviewed, as expected.
     </paragraph>
     <paragraph label="Example 4">
      Closed world rulesUnder EFLP semantics, we can directly formulate the closed world assumption using closed world rules of the form {a mathematical formula}¬p←notp, which expresses that when failing to prove p to be true, we assert ¬p. Moreover, we can also state its opposite using rules of the form {a mathematical formula}p←not¬p, which expresses that when failing to prove ¬p to be true, we assert p. We can further combine them, leading to the following interesting logic program.{a mathematical formula} It is easy to check that this program has two world views: {a mathematical formula}A1={∅} w.r.t. the guess {a mathematical formula}Φ1={notp} and {a mathematical formula}A2={{p}} w.r.t. {a mathematical formula}Φ2={not¬p}. This conforms to our intuition that either ¬p or p can be concluded from Π, depending on whether we choose to apply CWA on p (rule {a mathematical formula}r1) or on ¬p (rule {a mathematical formula}r2).
     </paragraph>
     <paragraph label="Remark 3">
      Gelfond and Lifschitz [17] used a rule ∼{a mathematical formula}p←¬p (instead of {a mathematical formula}¬p←notp) to formalize CWA on an atom p, which achieves the effect that if p is not in an answer set I, then ∼p is in I. As indicated by Gelfond [13], this formalization of CWA is problematic. For example, by this formalization the logic program {a mathematical formula}Π={p∨q} extended with the rule ∼{a mathematical formula}p←¬p would have two answer sets, viz. {a mathematical formula}I1={∼{a mathematical formula}p,q} and {a mathematical formula}I2={p}; thus both p and q are unknown in Π under the semantics of Gelfond and Lifschitz [17].{sup:8} In contrast, if Π is extended with the CWA rule {a mathematical formula}¬p←notp, we would obtain a unique world view {a mathematical formula}{{q}} under EFLP semantics, so p is false and q is true in Π, as expected.{sup:9}
     </paragraph>
     <paragraph label="Example 5">
      Let {a mathematical formula}Π={r←notp∧¬r, {a mathematical formula}p←¬q, {a mathematical formula}q←¬p}. Intuitively, the last two rules say that either {a mathematical formula}{p} or {a mathematical formula}{q} is an answer set of Π, and the first rule is a constraint that every answer set of Π should contain p. Therefore, Π intuitively should have a unique answer set {a mathematical formula}{p}. It is easy to check that under EFLP semantics this program has a unique world view {a mathematical formula}A={{p}} w.r.t. the guess {a mathematical formula}Φ=∅. Note that {a mathematical formula}A is not a world view under the approach of Gelfond [14], where notp in Π is replaced by {a mathematical formula}¬Kp.
     </paragraph>
     <paragraph label="Example 6">
      Consider again the logic program {a mathematical formula}Π={p←Mp}. As mentioned earlier, {a mathematical formula}Mp is shorthand for {a mathematical formula}not¬p, so this program can be rewritten as {a mathematical formula}Π={p←not¬p}. The set {a mathematical formula}Φ={not¬p} is the largest guess and it is easy to check that {a mathematical formula}{{p}} is a unique world view of Π w.r.t. Φ under EFLP semantics.Similarly, the logic program in Example 1 can be rewritten as{a mathematical formula} It has a unique world view {a mathematical formula}A={{p},{q}} w.r.t. the guess {a mathematical formula}Φ={not¬q,not¬p}. For this program, as shown in Example 1 applying the approaches of Gelfond [13], [14], and Kahl et al. [19], [18] will produce two world views, including the unintended one {a mathematical formula}{∅}.We remark that our epistemic answer set semantics minimizes the knowledge in world views by requiring that every world view should satisfy as many epistemic negations in a logic program as possible. It is this property of knowledge minimization with epistemic negation that provides a principled justification for the above two programs on why{a mathematical formula}A1={{p}}is the right world view and{a mathematical formula}A2={∅}is not.
     </paragraph>
     <paragraph label="Remark 4">
      A rule of the form{a mathematical formula} (or {a mathematical formula}p←Mp) expresses that if there is no evidence to prove ¬p to be true, we conclude p; put another way, we admit p unless we prove its contrary. Observe that such rules are commonly used in our daily life and our approach provides a suitable solution to such epistemic specifications. As an interesting example, the well-known Murphy's law{sup:10} says that anything that can go wrong, will go wrong; put another way, if something can go wrong and we cannot prove it will not go wrong, then it will go wrong. We can conveniently formalize this law by a rule{a mathematical formula} As another close example, our research group has a regular weekly meeting and our secretary Cathy reminds us every week by a no-reply email with the assumption that every member in the group will be present unless some notice of absence is available. This epistemic assumption can be suitably formalized by a rule of the form{a mathematical formula} i.e., any group member will be present unless we prove the contrary. Then for an individual member John without notice to Cathy, we would have a grounding{a mathematical formula} which has a unique world view {a mathematical formula}{{present(John)}} under EFLP semantics, meaning that John will be present in the meeting.
     </paragraph>
     <paragraph label="Example 7">
      Consider the logic program {a mathematical formula}Π={p←notp∨p}. Note that {a mathematical formula}notp∨p is a tautology in that for any collection {a mathematical formula}A of interpretations, every {a mathematical formula}I∈A satisfies {a mathematical formula}notp∨p w.r.t. {a mathematical formula}A. Then p can be inferred by applying the rule {a mathematical formula}p←notp∨p; thus Π is supposed to have a unique world view {a mathematical formula}A={{p}}.This program has two guesses: {a mathematical formula}Φ1={notp} and {a mathematical formula}Φ2=∅. It is easy to check that Π has no world view w.r.t. {a mathematical formula}Φ1, but has a world view {a mathematical formula}A={{p}} w.r.t. {a mathematical formula}Φ2.Note that the approaches of Gelfond [13], [14] and Kahl et al. [19], [18] are not applicable to this program.Observe that in our logic language {a mathematical formula}LΣ the formula {a mathematical formula}¬p∨p is also a tautology, and {a mathematical formula}p←¬p∨p is not equivalent to {a mathematical formula}{p←¬p, {a mathematical formula}p←p}. Under EFLP semantics the rule {a mathematical formula}p←notp∨p is not equivalent to {a mathematical formula}{p←notp, {a mathematical formula}p←p}.
     </paragraph>
     <section label="5.1">
      <section-title>
       Computational complexity
      </section-title>
      <paragraph>
       For a logic program Π, each guess Φ leads to at most one candidate world view w.r.t. Φ. As there are at most {a mathematical formula}2|Ep(Π)| guesses (where {a mathematical formula}|Ep(Π)| is the number of epistemic negations in {a mathematical formula}Ep(Π)), Π has at most {a mathematical formula}2|Ep(Π)| candidate world views. In view of the fact that if Π has a world view w.r.t. Φ then it will have no world view w.r.t. any {a mathematical formula}Φ′⊃Φ or {a mathematical formula}Φ′⊂Φ, the following result is immediate.
      </paragraph>
      <paragraph label="Proposition 2">
       A logic program Π has at most{a mathematical formula}(n⌊n/2⌋)many world views under EFLP semantics, where{a mathematical formula}n=|Ep(Π)|.
      </paragraph>
      <paragraph>
       Indeed, {a mathematical formula}(n⌊n/2⌋) is the maximal size of an antichain in the powerset lattice of a set of cardinality n[31]. In the two most extreme cases that Π has a world view w.r.t. Φ, where {a mathematical formula}Φ=Ep(Π) or {a mathematical formula}Φ=∅, Π has only one world view.
      </paragraph>
      <paragraph>
       As the satisfiability of arbitrary first-order theories is undecidable, we only address the computational complexity of EFLP answer sets for propositional programs under Herbrand interpretations. Recall that in this case, deciding the existence of FLP answer sets of a given logic program Π without epistemic negation is {a mathematical formula}Σ2p-complete [29], where the {a mathematical formula}Σ2p-hardness is inherited from disjunctive logic programs [8], [5].
      </paragraph>
      <paragraph>
       We first consider the complexity of recognizing a suitable guess.
      </paragraph>
      <paragraph label="Theorem 4">
       Given a propositional program Π and a guess Φ for it, deciding whether Π has a candidate world view w.r.t. Φ under EFLP semantics is{a mathematical formula}D2p-complete.
      </paragraph>
      <paragraph>
       The class {a mathematical formula}D2p consists of all problems {a mathematical formula}(P!,P2) whose instances are pairs {a mathematical formula}(I1,I2) of instances {a mathematical formula}I1 of a problem {a mathematical formula}P1 in {a mathematical formula}Σ2p and {a mathematical formula}I2 of a problem {a mathematical formula}P2 in {a mathematical formula}Π2p, respectively.
      </paragraph>
      <paragraph>
       Informally, we must check the conditions (a)–(c) of a candidate world view in Definition 8, where (a) establishes a fortiori also consistency of {a mathematical formula}ΠΦ; as {a mathematical formula}ΠΦ is constructible in polynomial time, we can solve (a) and (b) in {a mathematical formula}Σ2p and (c) in {a mathematical formula}Π2p, as deciding whether {a mathematical formula}ΠΦ has some FLP answer set that satisfies (resp. does not satisfy) a formula F is in {a mathematical formula}Σ2p; thus, the problem is in {a mathematical formula}D2p. The {a mathematical formula}D2p-hardness is shown by a reduction from deciding whether, given a pair {a mathematical formula}(Π1,Π2) of propositional programs, both {a mathematical formula}Π1 has some FLP-answer set and {a mathematical formula}Π2 has no FLP answer set; this problem is {a mathematical formula}D2p-complete. Informally, {a mathematical formula}Π2 is modified to a program {a mathematical formula}Π2′ whose answer sets amount to those of {a mathematical formula}Π2 plus an extra answer set {a mathematical formula}{A}, where A is a fresh atom; to this end, we add ¬A in the rule bodies of {a mathematical formula}Π2 and guessing clauses {a mathematical formula}A←¬A¯ and {a mathematical formula}A¯←¬A, where {a mathematical formula}A¯ is another fresh atom. The program Π contains {a mathematical formula}Π1 and {a mathematical formula}Π2′ and has a candidate world view w.r.t. {a mathematical formula}Φ=∅, where {a mathematical formula}EP(Π)={notA}, just if {a mathematical formula}Π1 has some FLP answer set and A is true in all FLP answer sets of {a mathematical formula}Π2′ (i.e., {a mathematical formula}Π2 has no FLP answer set). (For more details, see the proof in Appendix A.)
      </paragraph>
      <paragraph>
       From this result, we obtain that deciding program consistency under candidate world views is at the third level of the polynomial hierarchy. More precisely,
      </paragraph>
      <paragraph label="Theorem 5">
       Given a propositional program Π, deciding whether Π has (i) some candidate world view and (ii) some world view, i.e., deciding EFLP answer set existence, are both{a mathematical formula}Σ3p-complete.
      </paragraph>
      <paragraph>
       Indeed, a guess {a mathematical formula}Φ⊆Ep(Π) such that Π has some candidate world view w.r.t. Φ can be verified in polynomial time with an oracle for {a mathematical formula}D2p, and hence also with one for {a mathematical formula}Σ2p. This places the problem in {a mathematical formula}Σ3p. The matching {a mathematical formula}Σ3p-hardness can be shown by a reduction from evaluating quantified Boolean formulas of the form {a mathematical formula}∃Z∀Y∃Zϕ. Informally, epistemic negations notX, {a mathematical formula}notX¯ are used to guess an assignment to the X atoms, and some other epistemic negation serves to check that for each assignment to the Y atoms, some assignment to Z makes ϕ true; this test for Y and Z is encoded to cautious reasoning from the FLP answer set of a disjunctive logic program, which is {a mathematical formula}Π2p-complete [5].
      </paragraph>
      <paragraph>
       Note that some world view exists iff some candidate world view exists; this justifies the second part of Theorem 5, and consistency checking under candidate world view and world view semantics are equally hard. On the other hand, under EFLP semantics formula evaluation is harder.
      </paragraph>
      <paragraph label="Theorem 6">
       Given a propositional program Π and a propositional formula F, deciding whether F is true in Π under EFLP semantics (i) w.r.t. candidate world views is{a mathematical formula}Σ3p-complete and (ii) w.r.t. world views is{a mathematical formula}Σ4p-complete.
      </paragraph>
      <paragraph>
       While under candidate world views, it suffices to guess {a mathematical formula}Φ⊆EP(Π) such that Π has a candidate world view {a mathematical formula}A w.r.t. Φ and {a mathematical formula}ΠΦ cautiously entails F (i.e., F is true in all answer sets of {a mathematical formula}ΠΦ, which can be checked with an {a mathematical formula}Σ2p oracle), in case of world views under EFLP semantics, in addition maximality of Φ must be tested, i.e., no {a mathematical formula}Φ′⊃Φ has some candidate world view; this however turns out to be {a mathematical formula}Π3p-complete, which lifts the problem to the fourth level of the polynomial hierarchy.
      </paragraph>
      <paragraph>
       We note that the above results hold for propositional programs that amount to epistemic specifications, i.e., the rules match the syntax of form (1), where {a mathematical formula}KF amounts to {a mathematical formula}¬notF and {a mathematical formula}MF to {a mathematical formula}not¬F. In case of normal epistemic specifications, i.e., the rules of form (1) with {a mathematical formula}m=1, the complexity drops by one level of the polynomial hierarchy, and we obtain {a mathematical formula}D1p-, {a mathematical formula}Σ2p and {a mathematical formula}Σ3p-completeness in place of {a mathematical formula}D2p-, {a mathematical formula}Σ3p and {a mathematical formula}Σ4p-completeness, respectively (for details, see Appendix B). Indeed, as {a mathematical formula}¬¬A=A under FLP semantics, for normal epistemic specifications the reduct {a mathematical formula}ΠΦ amounts to a normal logic program, for which deciding FLP answer set existence is NP-complete. Furthermore, we remark that similar complexity results can be derived for other answer set semantics, and in particular for well-justified FLP answer sets [29].
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Epistemic well-justified answer set semantics
     </section-title>
     <paragraph>
      As shown in [29], FLP answer set semantics of Faber et al. [8] also suffers like other existing answer set semantics such as those defined in [26], [32], [1], [12] from circular justifications for some logic programs without epistemic negation. Consider the following program:{a mathematical formula} Here {a mathematical formula}I={p,q} is an FLP answer set of Π which has a circular justification via the self-supporting loop {a mathematical formula}p⇐q⇐¬q∨p⇐p, i.e., p being true in I is due to q being true in I (via rule {a mathematical formula}r1) that is due to I satisfying {a mathematical formula}¬q∨p (via rule {a mathematical formula}r2), which in turn is due to p being true in I.
     </paragraph>
     <paragraph>
      To the best of our knowledge, the well-justified FLP answer set semantics defined by Shen et al. [29] is the only one in the current literature whose answer sets are well justified by having a level mapping for any general logic programs without epistemic negation and thus are free of circular justifications. It is analogous to the standard answer set semantics of Gelfond and Lifschitz [16] for normal logic programs whose answer sets are well justified by having a level mapping [10]. Therefore, in this section we extend the well-justified FLP semantics to an epistemic one and discuss its relation with EFLP semantics.
     </paragraph>
     <paragraph>
      The well-justified FLP semantics is based on the one-step provability operator {a mathematical formula}TΠ(O,N), which is an extension of the van Emden–Kowalski one-step provability operator [34] from positive to general logic programs.
     </paragraph>
     <paragraph label="Definition 13">
      (See [29].) Let Π be a logic program without epistemic negation, and let O and N be two first-order theories. Define{a mathematical formula}
     </paragraph>
     <paragraph>
      Informally, {a mathematical formula}TΠ(O,N) collects all heads of rules in {a mathematical formula}ground(Π) whose bodies are entailed by {a mathematical formula}O∪N. When the parameter N is fixed, the entailment relation ⊨ is monotone in O, so {a mathematical formula}TΠ(O,N) is monotone w.r.t. O, i.e., for any first-order theories {a mathematical formula}O1⊆O2, we have {a mathematical formula}TΠ(O1,N)⊆TΠ(O2,N). Hence the sequence {a mathematical formula}〈TΠi(∅,N)〉i=0∞, where {a mathematical formula}TΠ0(∅,N)=∅ and for {a mathematical formula}i≥0{a mathematical formula}TΠi+1(∅,N)=TΠ(TΠi(∅,N),N), will converge to a least fixpoint, denoted {a mathematical formula}lfp(TΠ(∅,N)).
     </paragraph>
     <paragraph>
      The well-justified FLP answer set semantics, abbreviated as WJ semantics, is defined in terms of the least fixpoint {a mathematical formula}lfp(TΠ(∅,¬I−)) of an interpretation I.
     </paragraph>
     <paragraph label="Definition 14">
      (See [29].) Let I be a model of a logic program Π without epistemic negation. Then I is a WJ answer set if {a mathematical formula}lfp(TΠ(∅,¬I−))∪¬I−⊨A for every {a mathematical formula}A∈I.
     </paragraph>
     <paragraph>
      Then, by replacing {a mathematical formula}X with WJ in Definition 8 we obtain an epistemic well-justified answer set semantics (EWJ semantics for short).
     </paragraph>
     <paragraph label="Definition 15">
      EWJ semanticsLet Π be a logic program and Φ a guess such that {a mathematical formula}ΠΦ is a consistent epistemic reduct. The collection {a mathematical formula}A of all WJ answer sets of {a mathematical formula}ΠΦ is a candidate world view, resp. a world view, of Π w.r.t. Φ if {a mathematical formula}A satisfies the conditions of Definition 8. Every WJ answer set in a world view is called an EWJ answer set.
     </paragraph>
     <paragraph>
      As an exercise one may check that for the above Examples 2 to 7, their EWJ answer sets are the same as their EFLP answer sets.
     </paragraph>
     <paragraph>
      Note that a WJ answer set of a logic program without epistemic negation must be an FLP answer set, but the converse is not true; particularly an FLP answer set is a WJ answer set if and only if it is free of circular justifications (see Theorem 6 of Shen et al. [29]). Not surprisingly, such relations between FLP and WJ semantics do not convey to EFLP and EWJ semantics, as illustrated in the following example.
     </paragraph>
     <paragraph label="Example 8">
      As a result, a world view under EWJ semantics is not necessarily a world view under EFLP semantics, and vise versa. However, it is trivial to show that for programs matching normal epistemic specifications, the world views under EWJ and EFLP semantics coincide.
     </paragraph>
     <paragraph label="Remark 5">
      The above example demonstrates that while a semantics {a mathematical formula}X for logic programs without epistemic negation can be more restrictive than a semantics {a mathematical formula}Y in the sense that {a mathematical formula}X always yields a subcollection of the answer sets of {a mathematical formula}Y, this property will not be warranted when these semantics are extended to logic programs with epistemic negation by applying the general framework of Definition 8.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      The need for using epistemic negation in knowledge representation and reasoning was long recognized by Gelfond [13], [15] and recently further emphasized in [14], [33], [9], [35], [19], [18], [4], [37]. In particular, Gelfond [13] first introduced modal operators K and M to ASP and interpreted them in three-valued interpretations (called three-valued possible worlds). Formulas with such modal operators are called strongly introspective and logic programs with rules of form (1) called epistemic specifications. Truszczynski [33] revisited this formalism and redefined its semantics in two-valued interpretations.
     </paragraph>
     <paragraph>
      It turns out that the approaches of Gelfond [13] and Truszczynski [33] suffer from the problem of unintended world views due to recursion through K, i.e., they incur epistemic circular justifications for logic programs like {a mathematical formula}Π={p←Kp}, where an unintended world view {a mathematical formula}{{p}} is produced. To remedy this, Gelfond [14] further updated his program transformation. However, epistemic circular justifications persist for other logic programs such as {a mathematical formula}Π={q←¬Kp,p←¬q}, where an unintended world view {a mathematical formula}{{p}} is produced when applying the approaches of Gelfond [14], [13] and Truszczynski [33]. In addition, these approaches also suffer from the problem of unintended world views due to recursion through M for logic programs like {a mathematical formula}Π={p←Mp}, where an unintended world view {a mathematical formula}{∅} is produced.
     </paragraph>
     <paragraph>
      To address the problems of unintended world views due to recursion through K and M, Kahl et al. [19], [18] proposed a more involved program transformation by appealing to nested expressions of Lifschitz et al. [22]. However this approach has some clear shortcomings as listed in the Introduction. Specifically, as illustrated in Example 1 this approach also suffers from the problem of unintended world views due to recursion through M. Moreover, as shown in Shen et al. [29] answer sets of logic programs with nested expressions suffer from circular justifications under the existing semantics as defined in [22], [11], [12].
     </paragraph>
     <paragraph>
      In an alternative venue, Wang and Zhang [36] developed epistemic equilibrium models for epistemic specifications by introducing modal operators K and M to Pearce's equilibrium logic [25], [26]. This approach suffers from the problems of unintended world views due to recursion through K and M; for example, both {a mathematical formula}{{p}} and {a mathematical formula}{∅} are world views of {a mathematical formula}Π={p←Kp} and {a mathematical formula}Π={p←Mp}. Very recently, del Cerro et al. [4] presented a new definition of epistemic equilibrium models (EEMs) and further defined autoepistemic equilibrium models (AEEMs) as world views that are maximal EEMs under set inclusion and a special partial preorder over S5 models. A dozen of logic programs were listed all of which except for that program in Example 1 have the AEEMs that coincide with the world views of Kahl [19]; the AEEM of the program in Example 1 coincides with the world view under our EFLP semantics. On the one hand, it is unclear whether AEEMs are free of unintended world views due to recursion through K and M for general logic programs. On the other hand, as discussed by Shen et al. [29], Pearce's equilibrium semantics coincides with the answer set semantics of Ferraris [11] for propositional logic programs and with that of Ferraris [12] in the first-order case, and these semantics suffer from circular justifications. Since AEEMs are epistemic extensions of Pearce's equilibrium models, circular justifications inevitably convey to AEEMs, thus sometimes leading to undesired world views. For example, for the program {a mathematical formula}Π={p←¬¬p,p←¬p}, {a mathematical formula}{p} is a unique minimal equilibrium model/answer set under Pearce [26] and thus {a mathematical formula}{{p}} is an AEEM under del Cerro et al. [4]. This answer set/world view is undesired because it has a circular justification via the self-supporting loop {a mathematical formula}p⇐¬¬p⇐p. Finally, this approach may miss some desired world views; for instance, {a mathematical formula}{{p}} is expected to be a world view of the program {a mathematical formula}Π={p←notp∨p} (see Example 7), but it is not an AEEM of Π where notp is replaced by {a mathematical formula}¬Kp.
     </paragraph>
     <paragraph>
      Finally, we mention that Lifschitz [20] defined a modal logic of Minimal Knowledge and Negation as Failure (MKNF), which has two modal operators, viz. K as defined above and not like our epistemic negation operator. MKNF logic has recently been exploited for the integration of description logics and rules in the Semantic Web [24]. As indicated in the end of Lifschitz [20], “MKNF does not cover the important concept of strong introspection introduced in Gelfond [13].” Thus, applying it to handle epistemic negation would yield unintuitive results. For instance, the logic program {a mathematical formula}Π1 in Example 2 will be identified with a logic program {a mathematical formula}P1 consisting of the following formulas:{a mathematical formula} Under MKNF, {a mathematical formula}P1 has two possible collections of models (where each is viewed as an S5 structure):{a mathematical formula} The first collection means John is innocent, while the second says John is guilty, which violates our intuition.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <paragraph label="Proof of Theorem 1">
      Let {a mathematical formula}A=⋃iAi be the union of all collections {a mathematical formula}Ai of models of Π; then {a mathematical formula}A consists of all models of Π. By the condition that for every epistemic negation notF in {a mathematical formula}ground(Π), F is true in every model of Π, for every interpretation {a mathematical formula}I∈A, as I satisfies all rules in {a mathematical formula}ground(Π) w.r.t. some {a mathematical formula}Ai, I also satisfies these rules w.r.t. {a mathematical formula}A. This means {a mathematical formula}A itself is a collection of models of Π.For any interpretation I, if {a mathematical formula}AI={I} is a collection of models of Π, then {a mathematical formula}I∈A; conversely, if {a mathematical formula}I∈A, i.e., I satisfies all rules in {a mathematical formula}ground(Π) w.r.t. {a mathematical formula}A, then I also satisfies these rules w.r.t. {a mathematical formula}AI={I} and thus {a mathematical formula}AI={I} is a collection of models of Π. Hence for any interpretation I, {a mathematical formula}AI={I} is a collection of models of Π iff {a mathematical formula}I∈A iff I is a model of Π. Moreover, by Proposition 1, for any interpretation I, {a mathematical formula}AI={I} is a collection of models of Π iff I is a model of {a mathematical formula}Π¬. Thus I is a model of Π iff I is a model of {a mathematical formula}Π¬. This concludes the proof.  □
     </paragraph>
     <paragraph label="Proof of Proposition 2">
      Consider an EFLP answer set {a mathematical formula}I∈A w.r.t. guess Φ. As I is an FLP answer set of the epistemic reduct {a mathematical formula}ΠΦ, it is a model of {a mathematical formula}ΠΦ. Let {a mathematical formula}ΠΦnot be {a mathematical formula}ΠΦ with all ¬F replaced by notF. Since for every notF in {a mathematical formula}ΠΦnot, F is true in all {a mathematical formula}I∈A, by Theorem 1, {a mathematical formula}ΠΦnot and {a mathematical formula}ΠΦ have the same models. This means I is a model of {a mathematical formula}ΠΦnot w.r.t. {a mathematical formula}A. Note that {a mathematical formula}ΠΦnot is {a mathematical formula}ground(Π) with every {a mathematical formula}notF∈Φ replaced by ⊤. Then r is a rule in {a mathematical formula}ground(Π) iff {a mathematical formula}r⊤ is a rule in {a mathematical formula}ΠΦnot, where {a mathematical formula}r⊤ is r with every {a mathematical formula}notF∈Φ replaced by ⊤. Since for every {a mathematical formula}notF∈Φ, F is false in some {a mathematical formula}J∈A, I satisfies r w.r.t. {a mathematical formula}A iff I satisfies {a mathematical formula}r⊤ w.r.t. {a mathematical formula}A. This shows I is also a model of {a mathematical formula}ground(Π) w.r.t. {a mathematical formula}A. Hence {a mathematical formula}A is a collection of models of Π.  □
     </paragraph>
     <paragraph label="Proof of Theorem 3">
      (1) Let {a mathematical formula}A be a world view of Π w.r.t. a guess Φ. Then {a mathematical formula}A is also the set of all FLP answer sets of the epistemic reduct {a mathematical formula}ΠΦ. Rules in {a mathematical formula}ΠΦ are of the form{a mathematical formula} where every {a mathematical formula}Bi is true in every {a mathematical formula}I∈A because {a mathematical formula}notBi∈Ep(Π)∖Φ. This means {a mathematical formula}ΠΦ and {a mathematical formula}ΠΦ+ have the same set of FLP answer sets, where {a mathematical formula}ΠΦ+ is {a mathematical formula}ΠΦ with all rules containing a negative literal {a mathematical formula}¬Bi removed. Since {a mathematical formula}ΠΦ+ is a positive logic program, it has a unique FLP answer set. Hence {a mathematical formula}A has only one FLP answer set, i.e., {a mathematical formula}|A|=1.(2) For normal logic programs, FLP semantics coincides with the standard answer set semantics. So it suffices to show that {a mathematical formula}A={I} is a world view of Π iff I is a standard answer set of {a mathematical formula}Π¬.We first show that {a mathematical formula}A={I} is a candidate world view of Π iff I is a standard answer set of {a mathematical formula}Π¬.{a mathematical formula}(⟹) Assume {a mathematical formula}A={I} is a candidate world view of Π w.r.t. a guess Φ. Then I is also the FLP answer set of the epistemic reduct {a mathematical formula}ΠΦ, and for every notB in {a mathematical formula}ground(Π), {a mathematical formula}notB∈Φ iff B is false in I iff {a mathematical formula}B∉I. Let r be a rule in {a mathematical formula}ΠΦ. For every negative literal {a mathematical formula}¬Bi in the rule body of r, {a mathematical formula}Bi is true in I, i.e., {a mathematical formula}Bi∈I. Let {a mathematical formula}ΠΦ+ be {a mathematical formula}ΠΦ with all rules containing a negative literal {a mathematical formula}¬Bi removed. Then I is also the FLP answer set of {a mathematical formula}ΠΦ+, which is the least model of {a mathematical formula}ΠΦ+. Note that {a mathematical formula}ΠΦ+ is in fact the GL-reduct of {a mathematical formula}Π¬. This means I is also a standard answer set of {a mathematical formula}Π¬.{a mathematical formula}(⟸) Assume I is a standard answer set of {a mathematical formula}Π¬. Let Φ be a guess such that for every notB in {a mathematical formula}ground(Π), {a mathematical formula}notB∈Φ iff B is false in I iff {a mathematical formula}B∉I. Let r be a rule in {a mathematical formula}ground(Π) such that I satisfies {a mathematical formula}body(r) w.r.t. {a mathematical formula}A={I}. r must be of the form{a mathematical formula} with every {a mathematical formula}Ai∈I and every {a mathematical formula}Bi∉I (i.e., {a mathematical formula}notBi∈Φ). Then {a mathematical formula}Π¬ must have a rule {a mathematical formula}r′ of the form{a mathematical formula} Note that I satisfies {a mathematical formula}body(r′). As I is a model of {a mathematical formula}Π¬, H is in I. This means I satisfies r w.r.t. {a mathematical formula}A. Hence {a mathematical formula}A={I} is a candidate world view w.r.t. Φ.We have proved that {a mathematical formula}A={I} is a candidate world view of Π iff I is a standard answer set of {a mathematical formula}Π¬. To show that {a mathematical formula}A={I} is a world view of Π iff I is a standard answer set of {a mathematical formula}Π¬, it suffices to show that every candidate world view of Π is a world view of Π.Assume on the contrary that there are two guesses {a mathematical formula}Φ′⊃Φ such that {a mathematical formula}A′={I′} and {a mathematical formula}A={I} are candidate world views w.r.t. {a mathematical formula}Φ′ and Φ, respectively. For each {a mathematical formula}notB∈Φ′∖Φ, {a mathematical formula}B∉I′ and {a mathematical formula}B∈I. This means {a mathematical formula}I′≠I. By the above proof, {a mathematical formula}I′ and I are standard answer sets of {a mathematical formula}Π¬. We have the following two GL-reducts w.r.t. {a mathematical formula}I′ and I respectively:{a mathematical formula} As the two GL-reducts are positive logic programs, {a mathematical formula}I′ and I are their least fixpoints, respectively. As {a mathematical formula}Φ′⊃Φ, every rule in {a mathematical formula}(Π¬)I must be in {a mathematical formula}(Π¬)I′. This implies {a mathematical formula}I⊂I′ ({a mathematical formula}I′≠I, as shown above), which contradicts the fact that every standard answer set of a normal logic program is a minimal model of the program. We then conclude the proof.  □
     </paragraph>
     <paragraph label="Proof of Theorem 4">
      Membership. The proof of {a mathematical formula}D2p membership is in the discussion below Theorem 4.Hardness. The {a mathematical formula}D2p-hardness is shown by the reduction of the {a mathematical formula}D2p-complete problem where, given a pair {a mathematical formula}(Π1,Π2) of programs, we must decide whether {a mathematical formula}Π1 has some FLP answer set and {a mathematical formula}Π2 has no FLP answer set. (This result in turn is easily obtained by a reduction of evaluating QBFs of the form {a mathematical formula}∃X∀Yϕ to FLP answer set existence of disjunctive logic programs [5].)Assume w.l.o.g. that {a mathematical formula}Π1 and {a mathematical formula}Π2 are on disjoint signatures and let {a mathematical formula}A,A¯,C be fresh atoms. Then we claim that{a mathematical formula} has a candidate world view w.r.t. {a mathematical formula}Φ=∅ iff {a mathematical formula}Π1 has some FLP answer set and {a mathematical formula}Π2 has no FLP answer set. Notice that the epistemic reduct is{a mathematical formula}{a mathematical formula}(⟹) Suppose Π has a candidate world view {a mathematical formula}A w.r.t. {a mathematical formula}Φ=∅. Then {a mathematical formula}Π1 must have an FLP answer set. Furthermore, A must be true in every FLP answer set of {a mathematical formula}ΠΦ. In particular, this means that the guess {a mathematical formula}A¯ from {a mathematical formula}A←A¯, {a mathematical formula}A¯←A, does not lead to an FLP answer set of Π; this means that the program {a mathematical formula}{H←B∧¬A|H←B∈Π2} has no FLP answer set, from which in turn it follows that {a mathematical formula}Π2 has no FLP answer set.{a mathematical formula}(⟸) For each FLP answer set {a mathematical formula}I1 of {a mathematical formula}Π1, the set {a mathematical formula}I1∪{A} is an FLP answer set of {a mathematical formula}ΠΦ, and if since {a mathematical formula}Π2 has no FLP answer set, each answer set in the collection {a mathematical formula}A of FLP answer sets of {a mathematical formula}ΠΦ has this form. As {a mathematical formula}Π1 has some FLP answer set {a mathematical formula}I1, it follows that {a mathematical formula}A≠∅ and notA is false in {a mathematical formula}A; hence {a mathematical formula}A is a candidate world view of Π w.r.t {a mathematical formula}Φ=∅.  □
     </paragraph>
     <paragraph label="Proof of Theorem 5">
      (ii) Follows from (i), as some world view exists iff some candidate world view exists.  □
     </paragraph>
     <paragraph label="Proof of Theorem 6">
      (i) Membership. As in the discussion below Theorem 6, it suffices to guess {a mathematical formula}Φ⊆EP(Π) such that Π has a candidate world view {a mathematical formula}A w.r.t. Φ and {a mathematical formula}ΠΦ cautiously entails F. From Theorem 4 and [29] it follows that the guess can be verified with an {a mathematical formula}Σ2p oracle in polynomial time; this proves membership in {a mathematical formula}Σ3p.Hardness. {a mathematical formula}Σ3p-hardness is a trivial from Theorem 5: a given program Π has some candidate world view iff A is true in {a mathematical formula}Π∪{A} w.r.t. candidate world views, i.e., in some candidate world view of Π, where A is a fresh atom.(ii) Membership. For a guess Φ as in (i), we must in addition test that no {a mathematical formula}Φ′⊃Φ exists that has a candidate world view; by Theorem 5, the latter is in {a mathematical formula}Π3p. Thus in summary, a guess Φ that has a world view {a mathematical formula}A in which F is true can be verified with a {a mathematical formula}Σ3p oracle in polynomial; this proves {a mathematical formula}Σ4p membership.Hardness. {a mathematical formula}Σ4p-hardness is shown by generalizing the reduction in Theorem 5 to encode the evaluation of a QBF{a mathematical formula} where {a mathematical formula}ψ=⋁j=1kLj,1∧Lj,2∧Lj,3 is a DNF over atoms {a mathematical formula}W∪X∪Y∪Z. Without loss of generality, we assume that ψ is unsatisfiable if we assign each {a mathematical formula}Yi∈Y the value true, i.e., {a mathematical formula}∀W,Y,Z¬ψ[Y/⊤] evaluates to true.Assume for the moment that W is void; then the negation of the QBF {a mathematical formula}∀X∃Y∀Zψ, i.e., {a mathematical formula}∃X∀Y∃Zϕ were {a mathematical formula}ϕ=¬ψ, is encoded by the program Π in the proof of Theorem 5. That is, Π has some candidate world view iff {a mathematical formula}∀X∃Y∀Zψ evaluates to false. A modification of Π yields that maximality testing of a guess Φ is {a mathematical formula}Π3p-hard. To this end, let{a mathematical formula}{a mathematical formula}{a mathematical formula} where A is a fresh atom, and {a mathematical formula}Φ=∅. It is easy to see that Φ has a candidate world view: {a mathematical formula}I0=X∪X¯∪{V} is the single answer set of {a mathematical formula}Π0Φ, and for each epistemic negation notF in {a mathematical formula}EP(Π0)={notV, {a mathematical formula}not¬U, {a mathematical formula}not¬A, {a mathematical formula}notXi,{a mathematical formula}notXi¯|Xi∈X} the formula F is true in I.Furthermore, it holds that no guess {a mathematical formula}Φ′⊃Φ has a candidate world view iff Π has no candidate world view. To see the only if part, suppose some {a mathematical formula}Φ′⊃Φ has a candidate world view. Then {a mathematical formula}not¬A∈Φ′ must hold, as otherwise {a mathematical formula}I0 is the single answer set of {a mathematical formula}Π0Φ′; this would imply {a mathematical formula}Φ′=Φ, a contradiction. Now {a mathematical formula}Π0Φ′ contains A← and amounts to {a mathematical formula}ΠΦ′ (simply eliminate A); it follows that Π has a candidate world view w.r.t. {a mathematical formula}Φ′∩EP(Π). Conversely, if Π has a candidate world view w.r.t. Φ, then it is easy to see that {a mathematical formula}Π0 has a candidate world view w.r.t. {a mathematical formula}Φ′=Φ∪{not¬A}.Thus, {a mathematical formula}Π0 has a world view w.r.t. {a mathematical formula}Φ=∅ iff the QBF {a mathematical formula}∀X∃Y∀Zψ evaluates to true (which proves {a mathematical formula}Π3p-hardness of world view checking, i.e., deciding given a program Π and {a mathematical formula}Φ⊆EP(Π) whether Π has some world view w.r.t. Φ). Note that since any other guess {a mathematical formula}Φ′⊃Φ that has a candidate world view w.r.t. {a mathematical formula}Π0 must contain {a mathematical formula}not¬A, we can equivalently ask whether ¬A is true in {a mathematical formula}Π0 under EFLP semantics.Now we generalize {a mathematical formula}Π0 to accommodate non-void W, i.e., to encode evaluating the QBF (A.8). To this end, we let{a mathematical formula} where {a mathematical formula}Wi¯ is a fresh atom for {a mathematical formula}Wi and {a mathematical formula}Π0⁎ is constructed like {a mathematical formula}Π0 where in the construction of the rules (A.5) of Π each {a mathematical formula}Wi (resp. {a mathematical formula}¬Wi) literal is replaced by {a mathematical formula}Wi¯ (resp. {a mathematical formula}Wi).{sup:11} Note that {a mathematical formula}Wi and {a mathematical formula}Wi¯ do not occur in {a mathematical formula}Π0⁎ in rule heads; combined with the assumption that {a mathematical formula}∀W,X,Z¬ψ[Y/⊤] evaluates to true, by similar reasoning as in the proof of Theorem 5 for {a mathematical formula}Wi and {a mathematical formula}Wi¯ in place of {a mathematical formula}Xi and {a mathematical formula}Xi¯, we obtain that every guess {a mathematical formula}Φ⊆EP(Π1) such that {a mathematical formula}Π1 has a candidate world view w.r.t. Φ must contain exactly one of {a mathematical formula}notWi and {a mathematical formula}notWi¯, and thus Φ encodes a truth assignment ν to W where {a mathematical formula}ν(Wi)=true if {a mathematical formula}notWi¯∈Φ (as {a mathematical formula}Wi and {a mathematical formula}Wi¯←¬Wi are in {a mathematical formula}Π1Φ) and {a mathematical formula}ν(Wi)=false if {a mathematical formula}notWi∈Φ (as {a mathematical formula}Wi¯ and {a mathematical formula}Wi←¬Wi¯ are in {a mathematical formula}Π1Φ). Furthermore, if {a mathematical formula}not¬A∉Φ, then Φ contains no other epistemic negations, and we denote it by {a mathematical formula}Φν; if {a mathematical formula}not¬A∈Φ, then the QBF {a mathematical formula}∀X∃Y∀Zψ[W/ν] must evaluate to false. Thus, if {a mathematical formula}Φν has a world view, then {a mathematical formula}∀X∃Y∀Zψ[W/ν] evaluates to true. On the other hand, every truth assignment to W is encoded by some {a mathematical formula}Φν; thus, it follows that some {a mathematical formula}Φν has a world view iff the QBF (A.8) evaluates to true. As ¬A is true in the candidate world view of a guess Φ iff {a mathematical formula}Φ=Φν for some ν, it follows that ¬A is true in {a mathematical formula}Π1 under EFLP semantics iff the QBF (A.8) evaluates to true. As {a mathematical formula}Π1 is constructible in polynomial time from (A.8), this proves {a mathematical formula}Σ4p-hardness. □
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Programs matching normal epistemic specifications
     </section-title>
     <paragraph>
      We show that the complexity of world view existence drops by one level in the polynomial hierarchy for normal epistemic specifications with rules of the form{a mathematical formula} where {a mathematical formula}L0 is an atom and each {a mathematical formula}Li is an atom A or default negated atom ¬A; i.e., the rules match the syntax of (1) with {a mathematical formula}m=1 (the modal atom {a mathematical formula}MA amounts to {a mathematical formula}not¬A, and {a mathematical formula}¬¬A=A under FLP semantics).{sup:12}
     </paragraph>
     <paragraph label="Theorem 7">
      Formally, we obtain, were {a mathematical formula}Dp=D1p is the analog of {a mathematical formula}D2p where {a mathematical formula}Σ2p/Π2p is replaced by {a mathematical formula}NP/coNP: Given a propositional program Π that is a normal epistemic specification and a guess Φ for it, deciding whether Π has a candidate world view w.r.t. Φ is{a mathematical formula}Dp-complete.
     </paragraph>
     <paragraph label="Proof">
      Membership. The proof of {a mathematical formula}Dp membership is analogous to the one of Theorem 4, where {a mathematical formula}NP/coNP replaces {a mathematical formula}Σ2p/Π2p.Hardness. The {a mathematical formula}Dp-hardness follows from the reduction in the proof of Theorem 4: if the pair {a mathematical formula}(Π1,Π2) consists of normal logic programs, deciding whether {a mathematical formula}Π1 has some FLP answer set and {a mathematical formula}Π2 has no FLP answer set is {a mathematical formula}Dp-complete. Furthermore, the program Π constructed from {a mathematical formula}(Π1,Π2) matches a normal epistemic specification.  □
     </paragraph>
     <paragraph label="Theorem 8">
      Given a propositional program Π that is a normal epistemic specification, deciding whether Π has (i) some candidate world view and (ii) some world view are both{a mathematical formula}Σ2p-complete.
     </paragraph>
     <paragraph label="Proof">
      Membership. The membership proof is analogous to the one of Theorem 5, but uses Theorem 8 instead of Theorem 4.Hardness. The {a mathematical formula}Σ2p-hardness is inherited from the reduction in Theorem 5: if we consider a QBF (A.1) in which Z is void, the resulting program Π matches normal epistemic specifications, and has some candidate world view iff {a mathematical formula}∃X∀Y¬ϕ, where ϕ is a CNF, evaluates to true. Evaluating such QBFs is {a mathematical formula}Σ2p-complete, and remains {a mathematical formula}Σ2p-hard even if ϕ is unsatisfiable if each {a mathematical formula}Yi∈Y is assigned true, i.e., the QBF {a mathematical formula}∀X¬ϕ[Y/⊤] evaluates to true.  □
     </paragraph>
     <paragraph label="Theorem 9">
      Given a propositional program Π that is a normal epistemic specification and a propositional formula F, deciding whether F is true in Π (i) w.r.t. candidate world views is{a mathematical formula}Σsp-complete, and (ii) w.r.t. world views, i.e., under EFLP semantics, is{a mathematical formula}Σ3p-complete.
     </paragraph>
     <paragraph label="Proof">
      Membership. The membership proofs are analogous to the one of Theorem 6, but use Theorem 8 instead of Theorem 4 and the fact that for any guess Φ, {a mathematical formula}ΠΦ is a normal logic program, and cautious inference form the answer sets of such programs is coNP-complete [23].Hardness. The {a mathematical formula}Σ2p-hardness of (i) is immediate from the reduction in the proof of item (i) of Theorem 6 and Theorem 8. The {a mathematical formula}Σ3p-hardness of (ii) is shown by generalizing the encoding of evaluating a QBF {a mathematical formula}∃X∀Yψ to deciding candidate world existence for a program Π that matches normal epistemic specifications in Theorem 8 in the same way as in the proof of item (ii) in Theorem 6; note that all rules created match normal epistemic specifications.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>