<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Semi-equilibrium models for paracoherent answer set programs.
   </title>
   <abstract>
    The answer set semantics may assign a logic program to model, due to logical contradiction or unstable negation, which is caused by cyclic dependency of an atom on its negation. While logical contradictions can be handled with traditional techniques from paraconsistent reasoning, instability requires other methods. We consider resorting to a paracoherent semantics, in which 3-valued interpretations are used where a third truth value besides true and false expresses that an atom is believed true. This is at the basis of the semi-stable model semantics, which was defined using a program transformation. In this paper, we give a model-theoretic characterization of semi-stable models, which makes the semantics more accessible. Motivated by some anomalies of semi-stable model semantics with respect to basic epistemic properties, we propose an amendment that satisfies these properties. The latter has both a transformational and a model-theoretic characterization that reveals it as a relaxation of equilibrium logic, the logical reconstruction of answer set semantics, and is thus called the semi-equilibrium model semantics. We consider refinements of this semantics to respect modularity in the rules, based on splitting sets, the major tool for modularity in modeling and evaluating answer set programs. In that, we single out classes of canonical models that are amenable for customary bottom-up evaluation of answer set programs, with an option to switch to a paracoherent mode when lack of an answer set is detected. A complexity analysis of major reasoning tasks shows that semi-equilibrium models are harder than answer sets (i.e., equilibrium models), due to a global minimization step for keeping the gap between true and believed true atoms as small as possible. Our results contribute to the logical foundations of paracoherent answer set programming, which gains increasing importance in inconsistency management, and at the same time provide a basis for algorithm development and integration into answer set solvers.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Answer Set Programming (ASP) is a premier formalism for nonmonotonic reasoning and knowledge representation, mainly because of the existence of efficient solvers and well-established relationships with common nonmonotonic logics. It is a declarative programming paradigm with a model-theoretic semantics, where problems are encoded into a logic program using rules, and its models, called answer sets (or stable models) [26], encode solutions; see [6], [11], [24].
     </paragraph>
     <paragraph>
      As is well-known, not every logic program has some answer set. This can be due to different reasons: (1) an emerging logical contradiction, as e.g. for the program{a mathematical formula} where “−” denotes strong (sometimes also called classical) negation and “{a mathematical formula}not” denotes weak (or default) negation; according to the first rule, a door is locked unless it is known to be open, and according to the second rule it is not locked. The problem here is a missing connection from {a mathematical formula}−locked(door) to {a mathematical formula}open(door).{sup:1} (2) Due to cyclic dependencies which pass through negation, as e.g. in the following simplistic program.
     </paragraph>
     <paragraph label="Example 1">
      Consider the barber paradox, which can be regarded as an alternative form of Russell's famous paradox in naive set theory{sup:2}: in some town, the barber is a man who shaves all men in town, and only those, who do not shave themselves. The paradox arises when we ask “Who shaves the barber?”. Assuming that Joe is the barber, the knowledge about who is shaving him is captured by the logic program{a mathematical formula} (where joe is the barber), which informally states that Joe shaves himself if we can assume that he is not shaving himself. Under answer set semantics, P has no model; the problem is a lack of stability, as either assumption on whether {a mathematical formula}shaves(joe,joe) is true or false cannot be justified by the rule.
     </paragraph>
     <paragraph>
      In general, the absence of an answer set may be well-accepted and indicates that the rules cannot be satisfied under stable negation. There are nonetheless many cases when this is not intended and one might want to draw conclusions also from a program without answer sets, e.g., for debugging purposes, or in order to keep a system (partially) responsive in exceptional situations; in particular, if the contradiction or instability is not affecting the parts of a system that intuitively matter for a reasoning problem.
     </paragraph>
     <paragraph>
      In order to deal with this, Inoue and Sakama [49] have introduced a paraconsistent semantics for answer set programs. While dealing with logical contradictions can be achieved with similar methods as for (non-) classical logic (cf. also [9], [1], [37]), dealing with cyclic default negation turned out to be tricky. We concentrate in this article on the latter, in presence of constraints, and refer to it as paracoherent reasoning, in order to distinguish reasoning under logical contradictions from reasoning on programs without strong negation that lack stability in models.
     </paragraph>
     <paragraph>
      With the idea that atoms may also be possibly true (i.e., believed true), Inoue and Sakama defined a semi-stable semantics which, for the program in Example 1, has a model in which {a mathematical formula}shaves(joe,joe) is believed true; this is (arguably) reasonable, as {a mathematical formula}shaves(joe,joe) cannot be false while satisfying the rule. Note however that believing {a mathematical formula}shaves(joe,joe) is true does not provide a proof or founded justification that this fact is actually true; as a mere belief it is regarded to be weaker than if {a mathematical formula}shaves(joe,joe) would be known as a fact or derived from a rule.
     </paragraph>
     <paragraph>
      In fact, semi-stable semantics approximates answer set semantics and coincides with it whenever a program has some answer set; otherwise, under Occam's razor, it yields models with a smallest set of atoms believed to be true. That is, the intrinsic closed world assumption (CWA) of logic programs is slightly relaxed for achieving stability of models.
     </paragraph>
     <paragraph>
      In a similar vein, we can regard many semantics for non-monotonic logic programs that relax answer sets as paracoherent semantics, e.g. [4], [19], [39], [43], [44], [47], [48], [51], [56], [59]. Ideally, such a relaxation meets for a program P the following properties: (D1)Every (consistent) answer set of P corresponds to a model (answer set coverage).(D2)If P has some (consistent) answer set, then its models correspond to answer sets (congruence).(D3)If P has a classical model, then P has a model (classical coherence).
     </paragraph>
     <paragraph>
      In particular, (D3) intuitively says that in the extremal case, a relaxation should renounce to the selection principles imposed by the semantics on classical models (in particular, if a single classical model exists).
     </paragraph>
     <paragraph>
      Widely-known semantics, such as 3-valued stable models [47], L-stable models [19], revised stable models [43], regular models [59], and pstable models [39], satisfy only part of these requirements (see Section 8.2 for more details). Semi-stable models however, satisfy all three properties and thus have been the prevailing paracoherent semantics.
     </paragraph>
     <section label="1.1">
      <section-title>
       Use case scenarios
      </section-title>
      <paragraph>
       Paracoherent semantics may be fruitfully employed in different use cases of ASP, such as model building respectively scenario generation, but also traditional reasoning from the models of a logical theory. The semi-stable model semantics is attractive as it (1) brings in “unsupported” assumptions as being believed, (2) remains close to answer sets in model building, but distinguishes atoms that require such assumptions from atoms derivable without them, not creating justified truth from positive beliefs, and (3) keeps the CWA/LP spirit of minimal assumptions.
      </paragraph>
      <paragraph>
       Let us consider two possible use cases for illustration.
      </paragraph>
      <section label="1.1.1">
       <section-title>
        Model building
       </section-title>
       <paragraph>
        In ASP, one of the principal reasoning tasks is model building, which means to compute some, multiple or even all answer sets of a given program. Each answer set encodes a possible world or solution to a problem that is represented by the program.
       </paragraph>
       <paragraph>
        The standard answer set semantics may be regarded as appropriate when a knowledge base, i.e., logic program, is properly specified adopting the CWA principle to deal with incomplete information. It may then be perfectly ok that no answer set exists, as e.g. in the Gedanken-Experiment of the barber paradox. However, sometimes the absence of an answer set is unacceptable as a possible world is known to exist, and in this case a relaxation of the answer set semantics is desired.
       </paragraph>
       <paragraph label="Example 2">
        Suppose we have a program that captures knowledge about friends of a person regarding visits to a party, where {a mathematical formula}go(X) informally means that X will go:{a mathematical formula}It happens that P has no answer set. This is unacceptable as we know that there is a model in reality, regardless of who will go to the party, and we need to cope with this situation. Semi-stable semantics is a tool that allows us to gain an answer set, by relaxing the CWA and adopting beliefs without further justifications. In particular, the semi-stable models of this program are {a mathematical formula}I1κ={Kgo(Mark)} and {a mathematical formula}I2κ={go(John), {a mathematical formula}Kgo(John), {a mathematical formula}Kgo(Bill)}. Informally, the key difference between {a mathematical formula}I1κ and {a mathematical formula}I2κ concerns the beliefs on Mark and John. In {a mathematical formula}I2κ Mark does not go, and, consequently, John will go (moreover, Bill is believed to go, and Peter will not go). In {a mathematical formula}I1κ, instead, we believe Mark will go, thus John will not go (likewise Peter and Bill). Notably, and different from other related formalisms (cf. Section 8.2), positive beliefs do not create justified truth: if we had a further rule {a mathematical formula}fun←go(Mark) in P, then from just believing that Mark will go we cannot derive that fun is true; {a mathematical formula}I1κ would remain a semi-stable model.
       </paragraph>
       <paragraph>
        As already mentioned, paracoherent semantics can serve as a starting point for debugging and also repairing a program. Indeed, if all believed atoms were justified true, then we would obtain an answer set of the program.{sup:3} Therefore, we might investigate reasons for the failure to derive these atoms justified, and possibly add new rules or modify existing ones. However, dealing with this issue and linking it to existing work on debugging and repair of answer set programs (e.g., [50], [52], [25], [4], [38]) is beyond the scope of this article; we will briefly address it in Section 8.2.
       </paragraph>
      </section>
      <section label="1.1.2">
       <section-title>
        Inconsistency-tolerant query answering
       </section-title>
       <paragraph>
        Query answering over a knowledge base resorts usually to brave or cautious inference from the answer sets of a knowledge base, where the query has to hold in some or in every answer set, respectively; let us focus on the latter here. However, if incoherence of the knowledge base arises, then we lose all information and query answers are trivial, since every query is vacuously true. This, however, may not be satisfactory and be problematic, especially if one cannot modify the knowledge base, which may be due to various reasons (no permission for change, the designer or administrator of the knowledge base might be unavailable, no clear way to fix the problem etc). Paracoherent semantics can be exploited to overcome this problem and to render query answering operational, without trivialization. We illustrate this on an extension to the barber paradox (but could equally well consider other scenarios).
       </paragraph>
       <paragraph label="Example 3">
        Consider a variant of the barber paradox, cf. [49]:{a mathematical formula} While this program has no answer set, the semi-stable model semantics gives us the model {a mathematical formula}{man(joe),{a mathematical formula}shaves(joe,paul), {a mathematical formula}man(paul), {a mathematical formula}Kshaves(joe,joe)}, in which {a mathematical formula}shaves(joe,joe) is believed to be true (as expressed by the prefix ‘K’); here the incoherent rule {a mathematical formula}shaves(joe,joe)←notshaves(joe,joe),man(joe), which is an instance of the rule in P for joe, is isolated from the rest of the program to avoid the absence of models{sup:4}; this treatment allows us to derive, for instance, that {a mathematical formula}shaves(joe,paul) and {a mathematical formula}man(paul) are true; furthermore, we can infer that {a mathematical formula}shaves(joe,joe) cannot be false. Such a capability seems to be very attractive in query answering: to tolerate inconsistency (that is, incoherence) without a “knowledge explosion.”
       </paragraph>
       <paragraph label="Example 4">
        The well-founded semantics (WFS) [56]is the most prominent approximation of the answer set semantics and in particular useful for query answering, since an atom that is true (resp. false) under WFS is true (resp. false) in every answer set of a program. The WFS has similar capabilities, but takes intuitively a coarser view on the truth value of an atom, which can be either true, false, or undefined; in semi-stable semantics, however, undefinedness has a bias towards truth, expressed by “believed true” (or stronger, by “must be true”); in the example above, under WFS {a mathematical formula}shaves(joe,joe) would be undefined. Furthermore, undefinedness is cautiously propagated under WFS, which may prevent one from drawing expected conclusions. Consider the following extension of Russell's paraphrase:{a mathematical formula}Arguably one expects that {a mathematical formula}visits_barber(joe) is concluded false from this program: to satisfy the first rule, {a mathematical formula}shaves(joe,joe) cannot be false, and thus the second rule cannot be applied; thus under CWA, {a mathematical formula}visits_barber(joe) should be false. However, under well-founded semantics all atoms are undefined; in particular, the undefinedness of {a mathematical formula}shaves(joe,joe) is propagated to {a mathematical formula}visits_barber(joe) by the second rule.The single semi-stable model of P from its epistemic transformation is {a mathematical formula}{Kshaves(joe,joe)}, according to which {a mathematical formula}shaves(joe,joe) is believed true while {a mathematical formula}visits_barber(joe) is false.
       </paragraph>
       <paragraph>
        Furthermore, it is well-known that the well-founded semantics has problems with reasoning by cases.
       </paragraph>
       <paragraph label="Example 5">
        From the program{a mathematical formula} which is still incoherent with respect to answer set semantics, we cannot conclude that {a mathematical formula}smokes(joe) is true under WFS: as {a mathematical formula}angry(joe) and {a mathematical formula}happy(joe) mutually define each other by negation, WFS remains agnostic and leaves both atoms undefined; their undefinedness is propagated to {a mathematical formula}smokes(joe) by the rules for this atom. In contrast, we can conclude that {a mathematical formula}smokes(joe) is true under semi-stable semantics and its relatives: we have two semi-stable models, one in which {a mathematical formula}angry(joe) is true and {a mathematical formula}happy(joe) is false, and one in which {a mathematical formula}angry(joe) is false and {a mathematical formula}happy(joe) is true; in both models, however, {a mathematical formula}smokes(joe) is true. Moreover, under these semantics we can e.g. not derive that {a mathematical formula}angry(joe) is true, which means that trivialization is avoided.
       </paragraph>
       <paragraph>
        We elucidate the relationship between paracoherent semantics and WFS in more detail in Section 8.
       </paragraph>
      </section>
     </section>
     <section label="1.2">
      <section-title>
       Contributions
      </section-title>
      <paragraph>
       Despite the model-theoretic nature of ASP, semi-stable models have been defined by means of a program transformation, called epistemic transformation. A semantic characterization in the style of equilibrium models for answer sets [41] was still missing. Such a characterization is desired because working with program transformations becomes cumbersome, if properties of semi-stable models should be assessed; and moreover, while the program transformation is declarative and the intuition behind is clear, the interaction of rules does not make it easy to understand or to see how the semantics works in particular cases.
      </paragraph>
      <paragraph>
       Starting out from these observations, we have addressed the problem making the following main contributions.
      </paragraph>
      <list>
       <list-item>
        We characterize semi-stable models by pairs of 2-valued interpretations of the original program, similar to so-called here-and-there (HT) models in equilibrium logic [40], [41]. Equilibrium logic is the logical reconstruction of the answer set semantics and has proven immensely useful to understand it better from a proof-theoretic perspective based on intuitionistic logic, and to characterize important properties such as strong equivalence of answer set programs [32]; furthermore, it naturally extends to richer classes of programs. The logic of here-and-there, on which equilibrium logic is based, can be seen as the monotonic core of answer set semantics; its semantics is captured by HT-models, which are pairs {a mathematical formula}(X,Y), where {a mathematical formula}X⊆Y are sets of atoms that are true and believed true, respectively. Thus, to characterize the semi-stable models in terms of HT-models or similar structures is a natural and important issue. In the course of this, we point out some anomalies of the semi-stable semantics with respect to basic rationality properties in modal logics (K and N) which essentially prohibit a 1-to-1 characterization{sup:5} in terms of HT-models. Roughly speaking, the epistemic transformation misses some links between atoms encoding truth values of atoms, which may lead in some cases to counterintuitive results.
       </list-item>
       <list-item>
        These anomalies of the semi-stable model semantics lead us to propose an alternative paracoherent semantics, called semi-equilibrium ({a mathematical formula}SEQ) model semantics, which remedies them. It satisfies the properties (D1)–(D3) from above and is fully characterized using HT-models. Informally, semi-equilibrium models are 3-valued interpretations in which atoms can be true, false or believed true; the gap between believed and (derivably) true atoms is globally minimized. That is, {a mathematical formula}SEQ-models can be seen as relaxed equilibrium models respectively answer sets where a smallest set of atoms is believed to be true, without further justification, such that an answer set can be built. Note that the semantic distinction between believed true and true atoms in models is important. Other approaches, e.g. CR-Prolog [4], make a syntactic distinction at the rule level which does not semantically discriminate believed atoms; due to truth propagation, this may lead to more models. Notably, {a mathematical formula}SEQ-models can be obtained by an extension of the epistemic transformation that adds further rules which take care of the anomalies; we thus have both an appealing model-theoretic and a declarative-operational view of the semantics.
       </list-item>
       <list-item>
        Different from equilibrium models, semi-equilibrium models do in general not obey a well-known syntactic modularity property that allows one to build all models of a program by extending the models of a bottom part to the rest of the program. More precisely, splitting sets [31], the major tool for modularity in ASP, cannot be blindly used to decompose an arbitrary program under semi-equilibrium semantics. This shortcoming affects in fact two aspects: (1) program evaluation, which for answer set programs in practice proceeds from bottom to top modules, and (2) problem modeling, where user-defined subprograms are hierarchically organized. To address this, we define split{a mathematical formula}SEQ-models, where a concrete sequence {a mathematical formula}S=(S1,…,Sn) of splitting sets {a mathematical formula}Si, called splitting sequence, is used to decompose the program into hierarchically organized subprograms {a mathematical formula}P1,…,Pn that are evaluated bottom up.
       </list-item>
       <list-item>
        In general, the resulting split {a mathematical formula}SEQ-models depend on the particular splitting sequence. E.g., the party program in Example 2 has two {a mathematical formula}SEQ-models, which result from different splitting sequences (see Section 6). This is a drawback, as e.g. in program evaluation a solver may use one of many splitting sequences. In order to make the semantics robust, we thus introduce canonical splitting sequences, with the property that the models are independent of any particular member from a class of splitting sequences, and thus obtain canonical models (Section 6). This is analogous to the perfect models of a (disjunctive) stratified program, which are independent of a concrete stratification [3], [46]. We concentrate on program evaluation and show that for programs P with a benign form of constraints, the class derived from the strongly connected components (SCCs) of P warrants this property, as well as modularity properties. For the party program in Example 2, the single canonical {a mathematical formula}SEQ-model is {a mathematical formula}I2κ, as there is no rule from which {a mathematical formula}go(Mark) can be derived. For arbitrary programs, independence is held by a similar class derived from the maximal joined components (MJCs) of P, which intuitively merge SCCs that are involved in malign constraints. A compact summary of the relationships of the different notions of models is shown in Fig. 1 in Section 6.3.
       </list-item>
       <list-item>
        We study major reasoning tasks for the semantics above and provide precise characterizations of their computational complexity for various classes of logic programs. Besides brave and cautious reasoning, deciding whether a program has a model, respectively recognizing models, is considered. Briefly, the results show that semi-stable and {a mathematical formula}SEQ-model semantics reside in the polynomial hierarchy one level above the answer set semantics, and is for brave and cautious reasoning from disjunctive programs {a mathematical formula}Σ3p- respectively {a mathematical formula}Π3p-complete; for normal programs, the problems are {a mathematical formula}Σ2p- respectively {a mathematical formula}Π2p-complete. This increase in complexity is intuitively explained by the congruence property (D2), which imposes another layer of optimization. Notably, split {a mathematical formula}SEQ- and canonical {a mathematical formula}SEQ-models have the same complexity as {a mathematical formula}SEQ-models for these problems, but the model existence problem (which is NP-complete for {a mathematical formula}SEQ-models) is harder ({a mathematical formula}Σ3p- resp. {a mathematical formula}Σ2p-complete). Intuitively, this is explained by the fact that classical coherence (D3) already ensures {a mathematical formula}SEQ-model existence, but split {a mathematical formula}SEQ- and canonical {a mathematical formula}SEQ-models must fulfill further conditions that are a source of complexity.
       </list-item>
       <list-item>
        We compare the {a mathematical formula}SEQ-model semantics to a number of related semantics in the literature. It turns out that it coincides with the evidential stable model semantics for disjunctive logic programs [51]. The latter has been defined like the semi-stable model semantics in terms of a two stage program transformation, but using a rather different program. Thus our results provide as a byproduct also a semantic and computational characterization of the evidential stable model semantics. Another notable result is that the {a mathematical formula}SEQ-model semantics of a slightly enriched program {a mathematical formula}Pwf refines the WFS of a given program P, by making in general more atoms true resp. false; hence the query answers from {a mathematical formula}SEQ-models are in general more informative than under WFS (cf. Example 5). Moreover, the same holds for split {a mathematical formula}SEQ-models.
       </list-item>
      </list>
      <paragraph>
       Our results contribute to enhanced logical foundations of paracoherent answer set programming, which gains increasing importance in inconsistency management. They provide a model-theoretic characterization and an amendment of the semi-stable semantics, given by the semi-equilibrium semantics, linking it to the view of answer sets semantics in equilibrium logic; this also provides the basis for immediate extensions to richer classes of logic programs (see Section 9.3 and Section 10). Furthermore, the split {a mathematical formula}SEQ-model semantics, and in particular the {a mathematical formula}SCC-models semantics, lends itself for a modular use and bottom up evaluation of programs. Cautious merging of components, as done for {a mathematical formula}MJC-models, aims at preserving independence of components and thus possible parallel evaluation. This makes the refined semantics attractive for incorporation into answer set solvers and evaluation frameworks, in order to offer paracoherent features. Notably, the bottom-up evaluation allows one to switch on the fly to a paracoherent mode when facing an incoherence, i.e., no answer set exists. Furthermore the notions and main results for {a mathematical formula}SCC-models can be generalized to user-defined subprograms (Section 9.2).
      </paragraph>
      <section label="1.2.1">
       <section-title>
        Organization
       </section-title>
       <paragraph>
        The remainder of this article is organized as follows. In the next section, we review answer set programs, equilibrium logic and semi-stable model semantics. After that, we provide in Section 3 the semantic characterization of semi-stable models and point out some anomalies, which leads us to introduce semi-equilibrium models in Section 4. The refinement of the latter relative to splitting sets and arbitrary splitting sequences is considered in Section 5, while canonical semi-equilibrium models are introduced in Section 6. Section 7 is devoted to characterize the complexity of various semantics and to computational issues in this context. Related work is discussed in Section 8, followed by Section 9 that addresses possible extensions. Section 10 concludes the article with open issues and an outlook. In order not to disrupt the flow of reading, most proofs have been moved to the Appendix.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this paper, we consider a propositional setting of logic programs; extensions to the usual non-ground setting are straightforward. Since we are primarily interested in paracoherence, we also disregard aspects devoted to paraconsistency, i.e., logical contradictions; more specifically, we exclude strong negation. A discussion of how the work extends to non-ground programs and strong negation is given in Section 9.3.
     </paragraph>
     <paragraph>
      We first recall the answer set semantics of disjunctive logic programs, and then its reconstruction as equilibrium logic based on a non-classical logic.
     </paragraph>
     <section label="2.1">
      <section-title>
       Answer set programs
      </section-title>
      <paragraph>
       Given a propositional signature, i.e., a set of propositional atoms Σ, a (disjunctive) rule r is of the form{a mathematical formula} where {a mathematical formula}l+m+n&gt;0, such that all {a mathematical formula}ai, {a mathematical formula}bj and {a mathematical formula}ck are atoms.{sup:6} As usual, “{a mathematical formula}not” stands for weak or default negation. The head of r is the set {a mathematical formula}H(r)={a1,…,al}, and the positive (respectively negative) body is the set {a mathematical formula}B+(r)={b1,…,bm} (respectively {a mathematical formula}B−(r)={c1,…,cn}); the body of r is {a mathematical formula}B(r)=B+(r)∪notB−(r), where for any set S of atoms, {a mathematical formula}notS={nota|a∈S}. By abuse of notation, we will denote r also by{a mathematical formula} A rule r is a (disjunctive) fact, if {a mathematical formula}B(r)=∅ (we then omit ←); a constraint, if {a mathematical formula}H(r)=∅; normal, if {a mathematical formula}|H(r)|≤1; and positive, if {a mathematical formula}B−(r)=∅.
      </paragraph>
      <paragraph>
       A (disjunctive logic) program P is a finite set of disjunctive rules (over Σ). A program P is called normal (resp. positive) if each {a mathematical formula}r∈P is normal (resp. positive); P is constraint-free, if P contains no constraints.
      </paragraph>
      <paragraph label="Example 6">
       Several programs have already been considered in the Introduction. As an example of a disjunctive program, consider{a mathematical formula} It intuitively captures that in some department members who are not known to be professors are assistants or students, and a student who is not known to be assistant gets a discount for coffee.
      </paragraph>
      <paragraph>
       We now recall the stable models (also called answers sets) of a program; intuitively, these are models that can be reconstructed from the rules if negation is pre-evaluated according to the model itself. An interpretation is any set {a mathematical formula}I⊆Σ of atoms. An interpretation I satisfies a rule r, denoted {a mathematical formula}I⊨r, if {a mathematical formula}I∩H(r)≠∅ whenever {a mathematical formula}B+(r)⊆I and {a mathematical formula}B−(r)∩I=∅, and I is a model of a program P (denoted {a mathematical formula}I⊨P), if {a mathematical formula}I⊨r for each rule {a mathematical formula}r∈P. A model I of P is minimal, if no model {a mathematical formula}J⊂I of P exists; {a mathematical formula}MM(P) denotes the set of all minimal models of P.
      </paragraph>
      <paragraph>
       An interpretation I is a stable model (or answer set) of P, if {a mathematical formula}I∈MM(PI), where {a mathematical formula}PI is the well-known Gelfond–Lifschitz (GL) reduct[26] of P w.r.t. I, which is the positive program {a mathematical formula}PI={H(r)←B+(r)|r∈P,B−(r)∩I≠∅}. The program {a mathematical formula}PI incorporates the value of negation given by I into the program; if {a mathematical formula}I∈MM(PI) holds, I can be reconstructed under the “guess” for negation given by I. We denote by {a mathematical formula}AS(P) the set of all answer sets of P.
      </paragraph>
      <paragraph label="Example 7">
       continuedReconsider the program P in Example 6, where for simplicity we use a, b, c and d for professor, student, assistant, and discount, respectively; that is, we have {a mathematical formula}P={b∨c←nota;d←c,notb}. This program has the minimal models {a mathematical formula}MM(P)={{a},{b}, {a mathematical formula}{c,d}} and the answer sets {a mathematical formula}AS(P)={{b},{c,d}}. Note that {a mathematical formula}I={a} is not an answer set, as I is not a minimal model of {a mathematical formula}PI={d←c}; intuitively the truth of a in I is unfounded, as it cannot be derived from rules.
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Stratified and headcycle-free programs
       </section-title>
       <paragraph>
        Among various syntactic classes of programs that are important for the use in practice are stratified programs[3], [46] and headcycle-free (hcf) program[8]. In the following, we characterize these notions in terms of the strongly connected components of a logic program.
       </paragraph>
       <paragraph>
        The dependency graph of a program P is the directed graph {a mathematical formula}DG(P)=〈VDG,EDG〉 whose nodes {a mathematical formula}VDG are the atoms in P and with an edge {a mathematical formula}(a,b) if a occurs in the head of a rule r and either b occurs in the body of r or in the head of r and is different from a, i.e., {a mathematical formula}EDG={(a,b)|a∈H(r),b∈B+(r)∪B−(r)∪(H(r)∖{a}),r∈P}. The strongly connected components (SCCs) of P, denoted {a mathematical formula}SCC(P), are the SCCs of {a mathematical formula}DG(P), i.e., the maximal node sets {a mathematical formula}C⊆At(P) such that every pair of nodes {a mathematical formula}v,v′∈C is connected by some path in G with nodes only from C. Informally, the dependency graph captures dependencies of the truth of an atom a that occurs in the head of a rule r from the other occurrences of atoms in r; their value potentially influences the value of a.
       </paragraph>
       <paragraph>
        A program P is stratified, if for each {a mathematical formula}r∈P and {a mathematical formula}C∈SCC(P) either {a mathematical formula}H(r)∩C=∅ or {a mathematical formula}B−(r)∩C=∅. Note that the notion of stratified program introduced here applies also to programs with constraints, while the original notion [3], [46] considers only constraint-free normal respectively disjunctive logic programs. It conservatively generalizes the traditional notion and simply disregards constraints, as {a mathematical formula}H(r)∩C=∅ trivially holds for each constraint r. If all other rules r satisfy the condition, then no atom a can depend via rules in P on its negation: no path {a mathematical formula}a=a0,a1,…,ak=a where every {a mathematical formula}(ai,ai+1), {a mathematical formula}0≤i&lt;k, is an edge in {a mathematical formula}DG(P) exists thats leads from a in the head of some rule through a literal {a mathematical formula}a1 resp. {a mathematical formula}nota1 in its body recursively to {a mathematical formula}nota in some rule body. This makes it possible to evaluate negation in layers (also called strata). Indeed, every constraint-free stratified normal program P has a unique stable model which coincides with the perfect (stratified) model of P that is defined along strata (see [3], [46]).
       </paragraph>
       <paragraph>
        A program P is headcycle-free (hcf), if {a mathematical formula}|H(r)∩C|≤1 for each {a mathematical formula}r∈P and {a mathematical formula}C∈SCC(P′), where {a mathematical formula}P′={a←B+(r)|r∈P,a∈H(r)}. Headcycle-freeness means that distinct atoms a and b that occur in the head of the same rule do not mutually depend on each other by recursion through the positive parts of the rule bodies; this allows for tractable minimal model checking, which is intractable for arbitrary disjunctive logic programs.
       </paragraph>
       <paragraph label="Example 8">
        continuedThe program {a mathematical formula}P={b∨c←nota;d←c,notb} is stratified and also headcycle-free. Informally, the value of a, which does not depend on any other atom, can be determined first, next the value of b and c, and finally the value of d; this gives rise to three respective strata. The program is headcycle-free, as b and c do not mutually depend on each other through positive rule bodies. This also holds for the extended program {a mathematical formula}P′=P∪{b←d}: while b positively depends on c (via {a mathematical formula}b←d and {a mathematical formula}d←c), c does not positively depend on b.
       </paragraph>
       <paragraph>
        Notation. It is convenient to introduce further notation. For any rule r, we denote by {a mathematical formula}At(r)=H(r)∪B+(r)∪B−(r) the set of all atoms occurring in r, and for any program P, we let {a mathematical formula}At(P)=⋃r∈PAt(r). We assume as usual that by default {a mathematical formula}Σ=At(P), i.e., the signature is the one generated by the considered program P.
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        Splitting sets and sequences
       </section-title>
       <paragraph>
        Stratified programs come with the modularity property that atoms in lower layers (in Example 8 e.g. a) have their value solely determined by rules there. This modularity property in fact generalizes to a more abstract view of a program that is based on splitting sets of program [31]. Informally, a splitting set allows one to divide a program P into a lower and a higher part which can be evaluated bottom up. More formally, a set {a mathematical formula}S⊆Σ is a splitting set of P, if for every rule r in P such that {a mathematical formula}H(r)∩S≠∅ we have that {a mathematical formula}At(r)⊆S. We denote by {a mathematical formula}bS(P)={r∈P|At(r)⊆S} the bottom part of P, and by {a mathematical formula}tS(P)=P∖bS(P) the top part of P relative to S. Note that the union {a mathematical formula}S=S1∪S2 of splitting sets {a mathematical formula}S1, {a mathematical formula}S2 of a program P is also a splitting set of P.
       </paragraph>
       <paragraph>
        As shown in [31], it holds that{a mathematical formula} where as usual, “∪M” means adding all atoms in M as facts, and S is a splitting set of P. That is, we can obtain the answer sets of a program P by first evaluating its bottom part {a mathematical formula}bS(P) with respect to a splitting set S; this part contains rules that are entirely formulated over atoms from S. After that, we evaluate the remaining part of the program, {a mathematical formula}tS(P), in which the atoms from S can only occur in rule bodies but not in rule heads, augmented with facts for the atoms that are found true in an answer set.
       </paragraph>
       <paragraph label="Example 9">
        continuedFor the program {a mathematical formula}P={b∨c←nota;d←c,notb}, the set {a mathematical formula}S={a,b,c} is a splitting set, and we have {a mathematical formula}bS(P)={b∨c←nota} and {a mathematical formula}tS(P)={d←c,notb}; as {a mathematical formula}AS(bS(P))={{b},{c}}, we get {a mathematical formula}AS(P)=AS(tS(P)∪{b})∪AS(tS(P)∪{c})={{b},{c,d}}.
       </paragraph>
       <paragraph>
        Splitting sets naturally lead to splitting sequences. A splitting sequence{a mathematical formula}S=(S1,…,Sn) of P is a sequence of splitting sets {a mathematical formula}Si of P such that {a mathematical formula}Si⊆Sj for each {a mathematical formula}i&lt;j; note that usually {a mathematical formula}Sn⊂Σ; the characterization in (2) can be extended accordingly.
       </paragraph>
       <paragraph label="Example 10">
        continuedA splitting sequence for {a mathematical formula}P={b∨c←nota;d←c,notb} is {a mathematical formula}S=(S1,S2) where {a mathematical formula}S1={a} and {a mathematical formula}S2={a,b,c}; {a mathematical formula}bS1(P)=∅, {a mathematical formula}bS2(P)={b∨c←nota} and {a mathematical formula}tS2(P)={d←c,notb}.
       </paragraph>
       <paragraph>
        With an eye on practical implementation, we do not consider infinite splitting sequences here, but will comment on them at the end of Section 5. An important note is that splitting sets and sequences are an important tool not only for modular representation, but also for the implementation of answer set semantics. Advanced answer set solvers such as DLV and clasp exploit this tool heavily, and while the SCCs yield the most fine-grained splitting sequences, in practice coarser splittings may be more advantageous.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Equilibrium logic
      </section-title>
      <paragraph>
       The definition of answer set in Section 2.1 uses the GL-reduct, and thus in a sense has an operational flavor. This raised the question whether a characterization of answer sets in terms of a suitable logic is possible; and as constructibility of answer sets by rules is crucial, whether in particular (a variant of) intuitionistic logic could serve this purpose. David Pearce showed that the answer is positive and presented equilibrium logic[40], [41], which is a natural non-monotonic extension of Heyting's logic of here-and-there (HT) [27]. The latter is an intermediate logic between (full) intuitionistic and classical logic, and it coincides with 3-valued Gödel logic. As it turned out, HT-logic serves as a valuable basis for characterizing semantic properties of answer set semantics and equilibrium logic can be regarded as a logical reconstruction of answer set semantics that has many attractive features.
      </paragraph>
      <paragraph>
       As such, HT-logic considers a full language {a mathematical formula}LΣ of formulas built over a propositional signature Σ with the connectives ¬, ∧, ∨, →, and ⊥. We restrict our attention here to formulas of the form{a mathematical formula} which correspond in a natural way to rules of form (1) where for {a mathematical formula}l=0, the formula {a mathematical formula}a1∨⋯∨al is ⊥; every program P corresponds then similarly to a theory (set of formulas) {a mathematical formula}ΓP.
      </paragraph>
      <paragraph label="Example 11">
       For example, the program {a mathematical formula}P={a←b;b←notc;c←nota}, corresponds to the theory {a mathematical formula}ΓP={b→a;¬c→b;¬a→c}, while {a mathematical formula}P={b∨c←nota;d←c,notb} corresponds to {a mathematical formula}ΓP={¬a→b∨c;¬b∧c→d}.
      </paragraph>
      <paragraph>
       In the rest of the article, we tacitly use this correspondence. We note, however, that the key notions extend to the full language {a mathematical formula}LΣ, and in this way some of the results to extensions of the rule language that we consider (see Section 9.3) also apply to the full language.
      </paragraph>
      <paragraph>
       As a restricted intuitionistic logic, HT can be semantically characterized by Kripke models, in particular using just two worlds, namely “here” and “there” (assuming that the here world is ordered before the there world). An HT-interpretation is a pair {a mathematical formula}(X,Y) of interpretations {a mathematical formula}X,Y⊆Σ such that {a mathematical formula}X⊆Y; it is total, if {a mathematical formula}X=Y. Intuitively, atoms in X (the here part) are considered to be true, atoms not in Y (the there part) to be false, while the remaining atoms (from {a mathematical formula}Y∖X) are undefined.
      </paragraph>
      <paragraph>
       Assuming that {a mathematical formula}X⊨ϕ denotes satisfaction of a formula ϕ by an interpretation X in classical logic, satisfaction of ϕ in HT-logic (thus, an HT-model), denoted {a mathematical formula}(X,Y)⊨ϕ, is defined recursively as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(X,Y)⊨a if {a mathematical formula}a∈X, for any atom a,
       </list-item>
       <list-item label="2.">
        {a mathematical formula}(X,Y)⊭⊥,
       </list-item>
       <list-item label="3.">
        {a mathematical formula}(X,Y)⊨¬ϕ if {a mathematical formula}Y⊭ϕ (that is, Y satisfies ¬ϕ classically),
       </list-item>
       <list-item label="4.">
        {a mathematical formula}(X,Y)⊨ϕ∧ψ if {a mathematical formula}(X,Y)⊨ϕ and {a mathematical formula}(X,Y)⊨ψ,
       </list-item>
       <list-item label="5.">
        {a mathematical formula}(X,Y)⊨ϕ∨ψ if {a mathematical formula}(X,Y)⊨ϕ or {a mathematical formula}(X,Y)⊨ψ,
       </list-item>
       <list-item label="6.">
        {a mathematical formula}(X,Y)⊨ϕ→ψ if (i) {a mathematical formula}(X,Y)⊭ϕ or {a mathematical formula}(X,Y)⊨ψ, and (ii) {a mathematical formula}Y⊨ϕ→ψ.
       </list-item>
      </list>
      <paragraph label="Proposition 1">
       Note that the condition in item 3 is equivalent to {a mathematical formula}(X,Y)⊨ϕ→⊥, thus we can view negation ¬ϕ as implication {a mathematical formula}ϕ→⊥. Then, an HT-interpretation {a mathematical formula}(X,Y) is a model of a theory Γ, denoted {a mathematical formula}(X,Y)⊨Γ, if {a mathematical formula}(X,Y)⊨ϕ for every formula {a mathematical formula}ϕ∈Γ. As regards negative literals and rules, the following is not hard to see. Given a HT-interpretation{a mathematical formula}(X,Y), for an atom a it holds that{a mathematical formula}(X,Y)⊨¬aiff{a mathematical formula}a∉Y, and{a mathematical formula}(X,Y)⊨rfor a rule r of form(1)iff either{a mathematical formula}H(r)∩X≠∅, or{a mathematical formula}B+(r)⊈Y, or{a mathematical formula}B−(r)∩Y≠∅.
      </paragraph>
      <paragraph>
       In terms of the GL-reduct, we have {a mathematical formula}(X,Y)⊨P for a program P iff {a mathematical formula}Y⊨P and {a mathematical formula}X⊨PY[54].
      </paragraph>
      <paragraph>
       A total HT-interpretation {a mathematical formula}(Y,Y) is an equilibrium model ({a mathematical formula}EQ-model) of a theory Γ, if {a mathematical formula}(Y,Y)⊨Γ and for every HT-interpretation {a mathematical formula}(X,Y), such that {a mathematical formula}X⊂Y, it holds that {a mathematical formula}(X,Y)⊭Γ; the set of all {a mathematical formula}EQ-models of Γ is denoted by {a mathematical formula}EQ(Γ). The equilibrium models of a program P are then those of {a mathematical formula}ΓP, i.e., {a mathematical formula}EQ(P)=EQ(ΓP). For further details and background see, e.g., [41].
      </paragraph>
      <paragraph label="Example 12">
       continuedFor the program {a mathematical formula}P={b∨c←nota;d←c,notb}, the sets {a mathematical formula}(∅,a), {a mathematical formula}(a,a), {a mathematical formula}(b,b), {a mathematical formula}(∅,ab), {a mathematical formula}(a,ab), {a mathematical formula}(b,bc), {a mathematical formula}(c,bc), {a mathematical formula}(cd,cd) are some HT-models {a mathematical formula}(X,Y) of the corresponding theory {a mathematical formula}ΓP.{sup:7} The equilibrium models of P resp. {a mathematical formula}ΓP are {a mathematical formula}(b,b) and {a mathematical formula}(cd,cd), i.e., {a mathematical formula}EQ(P)=EQ(ΓP)={(b,b),(cd,cd)}.
      </paragraph>
      <paragraph>
       In the previous example, the program P has the answer sets {a mathematical formula}I1={b} and {a mathematical formula}I2={c,d}, which amount to the equilibrium models {a mathematical formula}(b,b) and {a mathematical formula}(cd,cd), respectively. In fact, the answer sets and equilibrium models of a program always coincide.
      </paragraph>
      <paragraph label="Proposition 2">
       (See[40].) For every program P and{a mathematical formula}M⊆At(P), it holds that{a mathematical formula}M∈AS(P)iff{a mathematical formula}(M,M)is an{a mathematical formula}EQ-model of{a mathematical formula}ΓP.
      </paragraph>
      <paragraph>
       In particular, as {a mathematical formula}AS(P)=MM(P) for any positive program P, we have {a mathematical formula}EQ(P)={(M,M)|M∈MM(P)} in this case.
      </paragraph>
      <paragraph>
       We call a logic program incoherent, if it lacks answer sets due to cyclic dependency of atoms among each other by rules through negation; that is, no answer set (equivalently, no equilibrium model) exists even if all constraints are dismissed from the program.
      </paragraph>
      <paragraph label="Example 13">
       Reconsider the barber paradox; the HT-models of the corresponding program {a mathematical formula}P={a←nota}, where a stands for {a mathematical formula}shaves(joe,joe), are {a mathematical formula}(∅,a) and {a mathematical formula}(a,a); the single total HT-model is {a mathematical formula}(a,a), which however is not an equilibrium model. Similarly, the program {a mathematical formula}P={a←b;b←nota} has the HT-models {a mathematical formula}(∅,a), {a mathematical formula}(∅,ab), {a mathematical formula}(a,a), {a mathematical formula}(a,ab), and {a mathematical formula}(ab,ab); likewise, the total HT-models {a mathematical formula}(a,a) and {a mathematical formula}(ab,ab) are not equilibrium models.
      </paragraph>
      <paragraph>
       We next recall the semi-stable model semantics which deals with such incoherence.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Semi-stable models
      </section-title>
      <paragraph>
       Inoue and Sakama [49] introduced semi-stable models as an extension of paraconsistent answer set semantics (called PAS semantics, respectively p-stable models by them) for extended disjunctive logic programs. Their aim was to provide a framework which is paraconsistent for incoherence, i.e., in situations where stability fails due to cyclic dependencies of a literal on its default negation.
      </paragraph>
      <paragraph label="Definition 1">
       We consider an extended signature {a mathematical formula}Σκ=Σ∪{Ka|a∈Σ}. Intuitively, Ka can be read as a is believed to hold. Semantically, we resort to subsets of {a mathematical formula}Σκ as interpretations {a mathematical formula}Iκ and the truth values false ⊥,{sup:8} believed true bt, and true t, which are ordered by a binary relation ⪯ (a truth ordering) such that {a mathematical formula}⊥⪯bt⪯t. The truth value assigned by {a mathematical formula}Iκ to a propositional variable a is defined by{a mathematical formula} The semi-stable models of a program P are obtained from its epistemic transformation{a mathematical formula}Pκ. Epistemic Transformation {a mathematical formula}Pκ[49]Let P be a disjunctive program. Then its epistemic transformation is defined as the positive disjunctive program {a mathematical formula}Pκ obtained from P by replacing each rule r of the form (1) in P, such that {a mathematical formula}B−(r)≠∅, with:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} for {a mathematical formula}1≤i,k≤l and {a mathematical formula}1≤j≤n, where the {a mathematical formula}λr,i, {a mathematical formula}λr,k are fresh atoms. Intuitively, the atom {a mathematical formula}Kcj means that {a mathematical formula}cj must be believed to be true, and {a mathematical formula}λr,i means that in the rule r, the atom {a mathematical formula}ai in the head must be true. With this meaning, the rule (1) is naturally translated into the rule (4): if all atoms in {a mathematical formula}B(r) are true, then either some atom in {a mathematical formula}H(r) is true, and thus some {a mathematical formula}λr,i is true, or some atom {a mathematical formula}ci in {a mathematical formula}B−(r) must be believed to be true (then {a mathematical formula}notci is false). The rule (5) propagates the value of {a mathematical formula}λr,i to {a mathematical formula}ai, which then is visible also in other rules. The rules (6) and (7) restrict the choice of {a mathematical formula}λr,i for making the head of r true: if {a mathematical formula}cj is true, the rule r is inapplicable and no atom in {a mathematical formula}H(r) has to be true (6). Furthermore, if the atom {a mathematical formula}ai in the head is true (via some other rule of P or by (5)), then whenever some atom {a mathematical formula}ak in {a mathematical formula}H(r) must be true, also {a mathematical formula}ai must be true (7); the minimality of answer set semantics effects that only {a mathematical formula}ai must be true.
      </paragraph>
      <paragraph label="Example 14">
       Reconsider the barber paradox program {a mathematical formula}P={a←nota}, where a stands for {a mathematical formula}shaves(joe,joe). Then{a mathematical formula} Consider the similar program {a mathematical formula}P={b←nota}, which is stratified. Its epistemic transformation is{a mathematical formula} Finally, let us also reconsider the stratified program {a mathematical formula}P={b∨c←nota;d←c,notb}. Its epistemic transformation is{a mathematical formula} where {a mathematical formula}r1 and {a mathematical formula}r2 name the first and second rule, respectively.
      </paragraph>
      <paragraph>
       Note that for any program P, its epistemic transformation {a mathematical formula}Pκ is a positive program. Models of {a mathematical formula}Pκ are defined in terms of a fixpoint operator in [49], with the property that for positive programs, according to Theorem 2.9 in [49], minimal fixpoints coincide with minimal models of the program. Therefore, for any program P, minimal fixpoints of {a mathematical formula}Pκ coincide with answer sets of {a mathematical formula}Pκ.
      </paragraph>
      <paragraph label="Definition 2">
       Semi-stable models are then defined as maximal canonical interpretations among the minimal fixpoints (answer sets) of {a mathematical formula}Pκ as follows. For every interpretation {a mathematical formula}Iκ over {a mathematical formula}Σ′⊇Σκ, let {a mathematical formula}gap(Iκ)={Ka∈Iκ|a∉Iκ} denote the atoms that are believed true but not assigned true. maximal canonicalGiven a set {a mathematical formula}S of interpretations over {a mathematical formula}Σ′, an interpretation {a mathematical formula}Iκ∈S is maximal canonical in{a mathematical formula}S, if no {a mathematical formula}Jκ∈S exists such that {a mathematical formula}gap(Iκ)⊃gap(Jκ). By {a mathematical formula}mc(S) we denote the set of maximal canonical interpretations in {a mathematical formula}S. Then we can equivalently paraphrase the definition of semi-stable models in [49] as follows.
      </paragraph>
      <paragraph label="Definition 3">
       semi-stable modelsLet P be a program over Σ. An interpretation {a mathematical formula}Iκ over {a mathematical formula}Σκ is a semi-stable model of P, if {a mathematical formula}Iκ=S∩Σκ for some maximal canonical answer set S of {a mathematical formula}Pκ. The set of all semi-stable models of P is denoted by {a mathematical formula}SST(P), i.e., {a mathematical formula}SST(P)={S∩Σκ|S∈mc(AS(Pκ))}.
      </paragraph>
      <paragraph label="Example 15">
       continuedFor {a mathematical formula}P={a←nota}, the epistemic transformation {a mathematical formula}Pκ, has the single answer set {a mathematical formula}M={Ka}; hence, {a mathematical formula}{Ka} is the single semi-stable model of P, in which a is believed true. For the program {a mathematical formula}P={b←nota}, the epistemic transformation {a mathematical formula}Pκ has the answers sets {a mathematical formula}M1={Ka} and {a mathematical formula}M2={λ1,b}; as {a mathematical formula}gap(M1)={a} and {a mathematical formula}gap(M2)=∅, among them {a mathematical formula}M2 is maximal canonical, and hence {a mathematical formula}M2∩Σκ={b} is the single semi-stable model of P. This is in fact also the unique answer set of P.Finally, the epistemic transformation of {a mathematical formula}P={b∨c←nota;d←c,notb} has the answer sets {a mathematical formula}M1={λr1,1,b}, {a mathematical formula}M2={λr1,2,c, {a mathematical formula}λr2,1,d}, {a mathematical formula}M3={λr1,2,c,Kb}, and {a mathematical formula}M4={Ka}, as may be checked using an ASP solver. Among them as {a mathematical formula}gap(M1)=gap(M2)=∅ while {a mathematical formula}M3 and {a mathematical formula}M4 have nonempty gap, {a mathematical formula}M1 and {a mathematical formula}M2 are maximal canonical and hence the semi-stable models of P; they correspond with the answer sets of P, {a mathematical formula}{b} and {a mathematical formula}{c,d}, as expected.
      </paragraph>
      <paragraph>
       For a study of the semi-stable model semantics, we refer to [49]; notably,
      </paragraph>
      <paragraph label="Proposition 3">
       (See[49].) The{a mathematical formula}SST-models semantics, given by{a mathematical formula}SST(P)for arbitrary programs P, satisfies properties (D1)–(D3).
      </paragraph>
      <paragraph>
       Arguably, the transformational definition of semi-stable models makes it difficult to grasp at the semantic level what makes an interpretation of a semi-stable model, in particular if we focus on the original language and forget about the auxiliary symbols. This raises the question of a characterization of semi-stable models from first principles that can serve as an alternative definition under a pure model-theoretic view. In the next section, we present such a characterization.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Semantic characterization of semi-stable models
     </section-title>
     <paragraph label="Example 16">
      As opposed to its transformational definition, we aim in this section at a model-theoretic characterization of semi-stable models. Given that equilibrium logic and HT-models have been successfully used to characterize stable models, it is natural to attempt to give such a characterization in the line of model-theoretic characterizations of the answer set semantics by means of HT models. Recall that in such a model {a mathematical formula}(X,Y), the set X contains the atoms that are true while Y contains the atoms that are believed true. Let us reconsider how HT-models work on the barber paradox. Reconsider {a mathematical formula}P={a←nota} in Example 13, Example 14, and recall that HT-models of P are {a mathematical formula}(∅,a) and {a mathematical formula}(a,a). One might aim at characterizing the semi-stable model {a mathematical formula}{Ka} by {a mathematical formula}(∅,a). Indeed, while {a mathematical formula}(a,a) is inappropriate, {a mathematical formula}(∅,a) perfectly describes the situation: a is believed true but not assigned true, as this cannot be proven.
     </paragraph>
     <paragraph>
      However, resorting to HT-interpretations will not allow us to uniquely characterize semi-stable models, as illustrated by the following example.
     </paragraph>
     <paragraph label="Example 17">
      Consider the program{a mathematical formula} The program is coherent, with a single answer set {a mathematical formula}{a,b,c}, while {a mathematical formula}SST(P)={{a,b,c,Kb}, {a mathematical formula}{a,b,c, {a mathematical formula}Ka,Kc}}. This is due to the fact that the epistemic transformation {a mathematical formula}Pκ contains rules {a mathematical formula}λr3,1∨Ka∨Kb← and {a mathematical formula}λr4,1∨Kb∨Kc← and the constraints (6), given that a, b, and c are true by facts, enforce that all {a mathematical formula}λr,i are false; thus, either Kb or {a mathematical formula}Ka,Kc must be true in every answer set of {a mathematical formula}Pκ. Note that neither {a mathematical formula}(abc,b) nor {a mathematical formula}(abc,ac) is a HT-interpretation.
     </paragraph>
     <paragraph>
      Hence, for a 1-to-1 characterization we have to resort to different structures. Sticking to the requirement that, given a program P over Σ, pairs of two-valued interpretations over Σ should serve as the underlying semantic structures, we say that a bi-interpretation of a program P over Σ is any pair {a mathematical formula}(I,J) of interpretations over Σ, and define:
     </paragraph>
     <paragraph label="Definition 4">
      bi-modelLet ϕ be a formula over Σ, and let {a mathematical formula}(I,J) be a bi-interpretation over Σ. Then, {a mathematical formula}(I,J) is a bi-model of ϕ, denoted {a mathematical formula}(I,J)⊨βϕ, if
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}(I,J)⊨βa if {a mathematical formula}a∈I, for any atom a,
      </list-item>
      <list-item label="2.">
       {a mathematical formula}(I,J)⊭β⊥,
      </list-item>
      <list-item label="3.">
       {a mathematical formula}(I,J)⊨β¬ϕ if {a mathematical formula}J⊭ϕ,
      </list-item>
      <list-item label="4.">
       {a mathematical formula}(I,J)⊨βϕ∧ψ if {a mathematical formula}(I,J)⊨βϕ and {a mathematical formula}(I,J)⊨βψ,
      </list-item>
      <list-item label="5.">
       {a mathematical formula}(I,J)⊨βϕ∨ψ if {a mathematical formula}(I,J)⊨βϕ or {a mathematical formula}(I,J)⊨βψ,
      </list-item>
      <list-item label="6.">
       {a mathematical formula}(I,J)⊨βϕ→ψ if (i) {a mathematical formula}(I,J)⊭βϕ, or (ii) {a mathematical formula}(I,J)⊨βψ and {a mathematical formula}I⊨ϕ.
      </list-item>
     </list>
     <paragraph>
      Note that the only difference in the recursive definition of bi-models and HT-models is in item 6, i.e., the case of implication. While HT-models require that the material implication {a mathematical formula}ϕ→ψ holds in the there-world, bi-models miss such a connection between ϕ and ψ. This makes it possible that a bi-interpretation {a mathematical formula}(I,J) such that {a mathematical formula}I⊆J is a bi-model but not an HT-model of an implication (3); a simple example is given by {a mathematical formula}(∅,a) and {a mathematical formula}a→b. On the other hand, each HT-model of an implication (3) is also a bi-model of it.
     </paragraph>
     <paragraph>
      Similar to the condition for HT-models in Proposition 1, we can alternatively characterize satisfaction of rules by bi-models as follows.
     </paragraph>
     <paragraph label="Proposition 4">
      Let r be a rule over Σ, and let{a mathematical formula}(I,J)be a bi-interpretation over Σ. Then,{a mathematical formula}(I,J)⊨βrif and only if{a mathematical formula}B+(r)⊆Iand{a mathematical formula}J∩B−(r)=∅implies that{a mathematical formula}I∩H(r)≠∅and{a mathematical formula}I∩B−(r)=∅.
     </paragraph>
     <paragraph>
      We now link bi-interpretations to interpretations of the extended signature {a mathematical formula}Σκ and the epistemic transformation of a program P, respectively. To every bi-model of a program P, we associate a corresponding interpretation {a mathematical formula}(I,J)κ over {a mathematical formula}Σκ by {a mathematical formula}(I,J)κ=I∪{Ka|a∈J}. Conversely, given an interpretation {a mathematical formula}Iκ over {a mathematical formula}Σκ its associated bi-interpretation {a mathematical formula}β(Iκ) is given by {a mathematical formula}(Iκ∩Σ,{a|Ka∈Iκ}).
     </paragraph>
     <paragraph>
      For illustration consider the following example.
     </paragraph>
     <paragraph label="Example 18">
      Let {a mathematical formula}P={a←b;b←notb}. Its bi-models are all pairs {a mathematical formula}(I,J), where {a mathematical formula}I∈{∅,{a},{a,b}} and {a mathematical formula}J∈{{b},{a,b}}. Then for {a mathematical formula}(∅,b), we have {a mathematical formula}(∅,b)κ={Kb}, and for {a mathematical formula}(a,ab) we have {a mathematical formula}(a,ab)κ={a,Ka,Kb}. Conversely, for {a mathematical formula}Iκ={a,Kb} we have {a mathematical formula}β(Iκ)=(a,b).
     </paragraph>
     <paragraph label="Example 19">
      In order to relate these constructions to models of the epistemic transformation {a mathematical formula}Pκ, which builds on additional atoms of the form {a mathematical formula}λr,i, we construct an interpretation {a mathematical formula}(I,J)κ,P of {a mathematical formula}Pκ from a given bi-interpretation {a mathematical formula}(I,J) of P as follows:{a mathematical formula} where r is of the form (1). continuedReconsider {a mathematical formula}P={a←b;b←notb} in Example 18 and {a mathematical formula}(∅,b). Then {a mathematical formula}(∅,b)κ,P=(∅,b)κ∪{λr2,1}={Kb,λr2,1}, as the rule {a mathematical formula}b←notb fulfills the conditions for {a mathematical formula}I=∅ and {a mathematical formula}J={b}.
     </paragraph>
     <paragraph>
      We now can establish the following correspondence between bi-models of a program P and models of the epistemic transformation {a mathematical formula}Pκ.
     </paragraph>
     <paragraph label="Proposition 5">
      Let P be a program over Σ. Then,
     </paragraph>
     <list>
      <list-item>
       if{a mathematical formula}(I,J)is a bi-model of P, then{a mathematical formula}(I,J)κ,P⊨Pκ;
      </list-item>
      <list-item>
       if{a mathematical formula}M⊨Pκthen{a mathematical formula}β(M∩Σκ)is a bi-model of P.
      </list-item>
     </list>
     <paragraph>
      Based on bi-models, we obtain a 1-to-1 characterization of semi-stable models by imposing suitable minimality criteria.
     </paragraph>
     <paragraph label="Theorem 1">
      Let P be a program over Σ. Then,
     </paragraph>
     <list>
      <list-item>
       if{a mathematical formula}(I,J)is a bi-model of P such that (i){a mathematical formula}(I′,J)⊭βP, for all{a mathematical formula}I′⊂I, (ii){a mathematical formula}(I,J′)⊭βP, for all{a mathematical formula}J′⊂J, and (iii) there is no bi-model{a mathematical formula}(I′,J′)of P that satisfies (i) and{a mathematical formula}gap(I′,J′)⊂gap(I,J), then{a mathematical formula}(I,J)κ∈SST(P);
      </list-item>
      <list-item>
       if{a mathematical formula}Iκ∈SST(P), then{a mathematical formula}β(Iκ)is a bi-model of P that satisfies (i)–(iii).
      </list-item>
     </list>
     <paragraph>
      Intuitively, Conditions (i) and (ii) filter bi-models that uniquely correspond to (some but not all) answer sets of {a mathematical formula}Pκ: due to minimality every answer set satisfies (i); there may be answer sets of {a mathematical formula}Pκ that do not satisfy (ii), but they are certainly not maximal canonical. Eventually, Condition (iii) ensures that maximal canonical answer sets are selected. More formally, the proof of this theorem builds on the following relationship between bi-models of P and answer sets of {a mathematical formula}Pκ.
     </paragraph>
     <paragraph label="Corollary 1">
      Let P be a program over Σ. If{a mathematical formula}M∈AS(Pκ), then{a mathematical formula}β(M∩Σκ)satisfies (i). If{a mathematical formula}(I,J)is a bi-model of P that satisfies (i) and (ii), then there exists{a mathematical formula}M∈AS(Pκ), such that{a mathematical formula}β(M∩Σκ)=(I,J).
     </paragraph>
     <paragraph>
      For illustration, we consider the following example.
     </paragraph>
     <paragraph label="Example 20">
      continuedRecall that {a mathematical formula}P={a←b;b←notb} has as bi-models all pairs {a mathematical formula}(I,J) where {a mathematical formula}I∈{∅,{a},{a,b}} and {a mathematical formula}J∈{{b},{a,b}}. Condition (i) of Theorem 1 holds for bi-models such that {a mathematical formula}I=∅, and Condition (ii) holds only if {a mathematical formula}J={b}. Thus, {a mathematical formula}{Kb} is the unique semi-stable model of P.
     </paragraph>
     <paragraph>
      The examples given so far also exhibit some anomalies of the semi-stable semantics with respect to basic rationality properties considered in epistemic logics. In particular, knowledge generalization (or necessitation, resp. modal axiom N) is a basic principle in respective modal logics. For a semi-stable model {a mathematical formula}Iκ, it would require that Property N:{a mathematical formula}a∈Iκ implies {a mathematical formula}Ka∈Iκ, for all {a mathematical formula}a∈Σ. This property does not hold as witnessed by Example 17.
     </paragraph>
     <paragraph>
      Another basic requirement is the distribution axiom (modal axiom K). Assuming that we belief the rules of a given program (which might also be seen as the consequence of adopting knowledge generalization) the distribution property can be paraphrased for a rule of the form (1) as follows: Property K:If {a mathematical formula}Iκ⊨Kb1∧…∧Kbm and {a mathematical formula}Iκ⊭Kc1∨…∨Kcn, then {a mathematical formula}Iκ⊨Ka1∨…∨Kal. Note that this does not hold for the rule {a mathematical formula}a←b in Example 18, as the single semi-stable model of the program P is {a mathematical formula}{Kb} (see Example 20).
     </paragraph>
     <paragraph>
      Arguably, these anomalies should be avoided. This leads us to propose an amendment to the semi-stable model semantics, which we present in the next section.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Semi-equilibrium models
     </section-title>
     <paragraph>
      In this section, we define and characterize an alternative paracoherent semantics which we call semi-equilibrium semantics (for reasons which will become clear immediately). The aim for semi-equilibrium models is to enforce Properties N and K on them.
     </paragraph>
     <paragraph>
      Let us start considering bi-models of a program P which satisfy these properties. It turns out that such structures are exactly given by HT-models.
     </paragraph>
     <paragraph label="Proposition 6">
      Let P be a program over Σ. Then,
     </paragraph>
     <list>
      <list-item>
       if{a mathematical formula}(I,J)is a bi-model of P, such that{a mathematical formula}(I,J)κsatisfies Property N and Property K, for all{a mathematical formula}r∈P, then{a mathematical formula}(I,J)is an HT-model of P;
      </list-item>
      <list-item>
       if{a mathematical formula}(H,T)is an HT-model of P, then{a mathematical formula}(H,T)κsatisfies Property N and Property K, for all{a mathematical formula}r∈P.
      </list-item>
     </list>
     <paragraph>
      In order to define semi-equilibrium models, we follow the basic idea of the semi-stable semantics and select subset minimal models that are maximal canonical. For any program P, let us define {a mathematical formula}HTκ(P)={(H,T)κ|(H,T)⊨P} and denote by {a mathematical formula}MM(HTκ(P)) the minimal elements of {a mathematical formula}HTκ(P) with respect to subset inclusion.
     </paragraph>
     <paragraph label="Definition 5">
      semi-equilibrium modelsLet P be a program over Σ. An interpretation {a mathematical formula}Iκ over {a mathematical formula}Σκ is a semi-equilibrium ({a mathematical formula}SEQ) model of P, if {a mathematical formula}Iκ∈mc(MM(HTκ(P))). The set of semi-equilibrium models of P is denoted by {a mathematical formula}SEQ(P).
     </paragraph>
     <paragraph>
      Let us revisit some examples from the previous section.
     </paragraph>
     <paragraph label="Example 21">
      For {a mathematical formula}P={a←nota}, its semi-stable-model {a mathematical formula}{Ka} corresponds to the HT-interpretation {a mathematical formula}(∅,a); thus {a mathematical formula}{Ka} is the single minimal element of {a mathematical formula}HTκ(P) and the single {a mathematical formula}SEQ-model of P.For the program {a mathematical formula}P={a;b;c;d←nota,notb;d←notb,notc} in Example 17, every HT-model of P must be of the form {a mathematical formula}(X,Y) such that {a mathematical formula}{a,b,c}⊆X; hence, {a mathematical formula}{a,b,c,Ka,Kb,Kc} is the single minimal element of {a mathematical formula}HTκ(P) and the single semi-equilibrium model of P.Finally, for the program {a mathematical formula}P={a←b;b←notb} in Example 18, by the rule {a mathematical formula}b←notb every HT-model {a mathematical formula}(X,Y) of P must fulfill {a mathematical formula}b∈Y, and thus by the rule {a mathematical formula}a←b also {a mathematical formula}a∈Y; the single minimal element of {a mathematical formula}HTκ(P) is then {a mathematical formula}{Ka,Kb}, which is also the single {a mathematical formula}SEQ-model of P.
     </paragraph>
     <paragraph>
      A model-theoretic characterization for the semi-equilibrium semantics is obtained as before, by replacing bi-models with HT-models and dropping Condition (ii). Intuitively, Condition (ii) is not needed as it is subsumed by Condition (iii) (i.e., Condition {a mathematical formula}(ii′) below) if Property N and Condition (i) hold.
     </paragraph>
     <paragraph>
      To formulate the result, we extend the notion of gap from {a mathematical formula}Σκ-interpretations to HT-interpretations as follows. For any HT-interpretation {a mathematical formula}(X,Y), let {a mathematical formula}gap(X,Y)=Y∖X, i.e., {a mathematical formula}gap(X,Y)=gap(β((X,Y)κ)){a mathematical formula}={a|Ka∈gap((X,Y)κ)}.
     </paragraph>
     <paragraph label="Theorem 2">
      Let P be a program over Σ. Then,
     </paragraph>
     <list>
      <list-item>
       if{a mathematical formula}(H,T)is an HT-model of P such that (i′){a mathematical formula}(H′,T)⊭P, for all{a mathematical formula}H′⊂H, and (ii′) no HT-model{a mathematical formula}(H′,T′)of P exists that satisfies{a mathematical formula}(i′)and{a mathematical formula}gap(H′,T′)⊂gap(H,T), then{a mathematical formula}(H,T)κ∈SEQ(P);
      </list-item>
      <list-item>
       if{a mathematical formula}Iκ∈SEQ(P), then{a mathematical formula}β(Iκ)is an HT-model of P that satisfies{a mathematical formula}(i′)and{a mathematical formula}(ii′).
      </list-item>
     </list>
     <paragraph>
      We refer to the condition {a mathematical formula}(i′) as h-minimality and to the condition {a mathematical formula}(i″) as gap-minimality of an HT-model of a program P. Informally, this characterization says that the {a mathematical formula}SEQ-models are obtained by relaxing the condition for {a mathematical formula}EQ-models in that a globally smallest set of atoms, expressed by gap-minimality, may be believed true without further justification, where justification is expressed by h-minimality. Note that the {a mathematical formula}EQ-models are obtained if we just would require that {a mathematical formula}H=T.
     </paragraph>
     <paragraph>
      Like semi-stable models, semi-equilibrium models may be computed as maximal canonical answer sets, i.e., equilibrium models, of an extension of the epistemic program transformation.
     </paragraph>
     <paragraph label="Definition 6">
      {a mathematical formula}PHTLet P be a program over Σ. Then its epistemic HT-transformation {a mathematical formula}PHT is defined as the union of {a mathematical formula}Pκ with the set of rules:{a mathematical formula} for {a mathematical formula}a∈Σ, respectively for every rule {a mathematical formula}r∈P of the form (1).
     </paragraph>
     <paragraph>
      The extensions of the transformation naturally ensure Properties N and K on its models and its maximal canonical answer sets coincide with semi-equilibrium models.
     </paragraph>
     <paragraph label="Theorem 3">
      Let P be a program over Σ, and let{a mathematical formula}Iκbe an interpretation over{a mathematical formula}Σκ. Then,{a mathematical formula}Iκ∈SEQ(P)if and only if{a mathematical formula}Iκ∈{M∩Σκ|M∈mc(AS(PHT))}.
     </paragraph>
     <paragraph>
      We note at this point that an alternative, less involving encoding of semi-equilibrium models can be found in Section 8.
     </paragraph>
     <paragraph>
      The resulting semantics is classically coherent, i.e., fulfills property (D3) from the Introduction.
     </paragraph>
     <paragraph label="Proposition 7">
      Let P be a program over Σ. If P has a classical model, then it has a semi-equilibrium model.
     </paragraph>
     <paragraph>
      Another simple property is a 1-to-1 correspondence between answer sets and semi-equilibrium models.
     </paragraph>
     <paragraph label="Proposition 8">
      Let P be a coherent program over Σ. Then,
     </paragraph>
     <list>
      <list-item>
       if{a mathematical formula}Y∈AS(P), then{a mathematical formula}(Y,Y)κis a semi-equilibrium model of P;
      </list-item>
      <list-item>
       if{a mathematical formula}Iκis a semi-equilibrium model of P, then{a mathematical formula}β(Iκ)is an equilibrium model of P, i.e.,{a mathematical formula}β(Iκ)is of the form{a mathematical formula}(Y,Y)and{a mathematical formula}Y∈AS(P).
      </list-item>
     </list>
     <paragraph>
      An illustration of the 1-to-1 relationship between answer sets and semi-equilibrium modelsis given by Example 17, which we reconsidered in Example 21. Note that this example also gave evidence that semi-stable models do not satisfy Property N, which in contrast is the case for semi-equilibrium models.
     </paragraph>
     <paragraph>
      From Proposition 7, Proposition 8, we thus obtain that semi-equilibrium models behave similarly as semi-stable models with respect to the properties (D1)–(D3) in the Introduction.
     </paragraph>
     <paragraph label="Proposition 9">
      The{a mathematical formula}SEQ-models semantics, given by{a mathematical formula}SEQ(P)for arbitrary programs P, satisfies properties (D1)–(D3).
     </paragraph>
     <paragraph>
      Furthermore, an immediate consequence of Proposition 8 is the following property.
     </paragraph>
     <paragraph label="Corollary 2">
      For every positive program P,{a mathematical formula}SEQ(P)={(X,Y)κ|(X,Y)∈EQ(P)}={(M,M)κ|M∈MM(P)}.
     </paragraph>
     <paragraph>
      As a consequence of Property K, semi-equilibrium semantics differs from semi-stable semantics not only with respect to believed consequences.
     </paragraph>
     <paragraph label="Example 22">
      Consider the program {a mathematical formula}P={a←b;b←notb;c←nota}, which extends the program in Example 18 with the rule {a mathematical formula}c←nota. The single semi-stable model of P is {a mathematical formula}{c,Kb} (which corresponds to the bi-model {a mathematical formula}(c,b)), while the single {a mathematical formula}SEQ-model is {a mathematical formula}{Ka,Kb} (which corresponds to the HT-model {a mathematical formula}(∅,ab)). Thus while c is true under {a mathematical formula}SST-model semantics, it is false under {a mathematical formula}SEQ-model semantics: due to lacking belief propagation, the CWA assigns a false in the {a mathematical formula}SST-model which in turn causes c to get true; in the {a mathematical formula}SEQ-model, as a is believed to be true the rule with c in the head is defeated. As there is no other way to derive c, the CWA assigns it false.
     </paragraph>
     <paragraph>
      Convention. As each {a mathematical formula}SEQ-model {a mathematical formula}Iκ of P is uniquely determined by the HT-model {a mathematical formula}β(Iκ), we shall in the rest of this article also identify these models and refer to the set {a mathematical formula}{β(Iκ)|Iκ∈SEQ(P)} as the {a mathematical formula}SEQ-models of P and denote it in abuse of notation by {a mathematical formula}SEQ(P). For illustration, the programs in Example 21 have the {a mathematical formula}SEQ-models {a mathematical formula}{Ka}, {a mathematical formula}{a,b,c,Ka,Kb,Kc}, and {a mathematical formula}{Ka,Kb}, respectively, which are identified with the HT-models {a mathematical formula}(∅,a), {a mathematical formula}(abc,abc), and {a mathematical formula}(∅,ab), respectively.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Split semi-equilibrium semantics
     </section-title>
     <paragraph>
      While the {a mathematical formula}SEQ-semantics has nice properties and fulfills the properties (D1)–(D3) from the Introduction, it does not ensure the modularity property of answer sets respectively equilibrium models that is expressed by Equation (2). To illustrate this, consider the following examples.
     </paragraph>
     <paragraph label="Example 23">
      Recall the party program from Example 2:{a mathematical formula}The semi-equilibrium models of P are {a mathematical formula}I1κ={Kgo(Mark)} and {a mathematical formula}I2κ={go(John), {a mathematical formula}Kgo(John), {a mathematical formula}Kgo(Bill)}, or written as HT-models, {a mathematical formula}M1=(∅,{go(Mark)}), and {a mathematical formula}M2=({go(John)},{go(John),go(Bill)}). None of the two models provides a fully coherent view (on the other hand, the program is incoherent, having no answer set). Nevertheless, {a mathematical formula}M2 appears preferable over {a mathematical formula}M1, since, according with a layering (stratification) principle, which is widely agreed in LP, one should prefer {a mathematical formula}go(John) rather than {a mathematical formula}go(Mark), as there is no way to derive {a mathematical formula}go(Mark) (which does not appear in the head of any rule of the program). We remark that according to the well-founded semantics of P, {a mathematical formula}go(Mark) is false and {a mathematical formula}go(John) is true, while all other atoms are undefined; the {a mathematical formula}SEQ-model {a mathematical formula}M2 is more informative since it tells us in addition that {a mathematical formula}go(Peter) is false.
     </paragraph>
     <paragraph label="Example 24">
      Consider the following simplistic program capturing knowledge about workers in a company:{a mathematical formula} Informally, the rules state that employees with a social security registry number (SSNR) have social security, that managers are employees and core staff, and that Sam is a manager. The constraints enforce that all core staff employees must have social security, and that SSNRs range over integers, where #int is a builtin predicate. This program has (over its Herbrand universe{sup:9}) no answer set: while {a mathematical formula}employee(sam) and {a mathematical formula}core_staff(sam) can be proven from the rules, this is not the case for {a mathematical formula}has_social_sec(sam), and thus the constraint in P is violated. The program has the {a mathematical formula}SEQ-model {a mathematical formula}Iκ={manager(sam), {a mathematical formula}employee(sam), {a mathematical formula}core_staff(sam), {a mathematical formula}Khas_social_sec(sam)} in which Sam is believed to have social security.It is not hard to see that {a mathematical formula}S={manager(sam), {a mathematical formula}employee(sam), {a mathematical formula}ssnr(sam,sam), {a mathematical formula}has_social_sec(sam)}, is a splitting set for P. The bottom part {a mathematical formula}bS(P) has the single answer set (thus single {a mathematical formula}SEQ-model) {a mathematical formula}M={manager(sam), {a mathematical formula}employee(sam)}, according to which {a mathematical formula}ssnr(sam,sam), {a mathematical formula}has_social_sec(sam) are false. Based on this, in the top part {a mathematical formula}tS(P) we obtain that {a mathematical formula}core_staff(sam) is true; however, this means that the constraint {a mathematical formula}←employee(sam),nothas_social_sec(sam),core_staff(sam), is violated. Consequently, no {a mathematical formula}SEQ-model for the top part exists and Equation (2) (adapted for {a mathematical formula}SEQ-models) is violated.
     </paragraph>
     <paragraph>
      Modularity via rule dependency as it emerges from Equation (2) is widely used in ASP for two related but different purposes: (1) for efficient evaluation of programs by ASP solvers and (2) for problem modeling, where a program is structured into modules that are organized in a hierarchical fashion.
     </paragraph>
     <paragraph>
      As for (1), program decomposition is in fact crucial for efficient answer set computation in practice. For the program P above, advanced answer set solvers like DLV and clasp immediately set {a mathematical formula}go(Mark) to false, as {a mathematical formula}go(Mark) does not occur in any rule head. In a customary bottom up computation along program components, solvers gradually extend answer sets until the whole program is covered, or an incoherence is detected at some component (in our example for the last two rules). But rather than to abort the computation, we would like to switch to a paracoherent mode and continue with building semi-equilibrium models, as an approximation of answer sets. Such a behavior would be desirable, as computationally, we do not waste effort for obtaining such an approximation, and conceptually, we relax the equilibrium condition under Occam's razor as little as possible along the hierarchy of components.
     </paragraph>
     <paragraph>
      As regards (2), it is customary and natural in modeling that a program P is divided into subprograms {a mathematical formula}P1,…,Pm which serve to define the values of specific sets of atoms respectively properties in a way such that each subprogram {a mathematical formula}Pi is considered as a module whose rules should be evaluated en bloc. These modules are then evaluated bottom-up exploiting Equation (2) repeatedly to obtain the answer sets of the program P. For example, the program in Example 2, possibly extended to further persons, could be the bottom part of a program {a mathematical formula}P′ that based on the go predicate determines which location to pick for the party, e.g. using{a mathematical formula} here {a mathematical formula}#count({X:go(X)})&gt;3 is an aggregate that evaluates to true if more than 3 persons go to the party.
     </paragraph>
     <paragraph>
      Similarly, we can imagine that the last three rules of the program in Example 24 form a subprogram about employees and staff, and the other rules cover social security aspects on top of it. The single {a mathematical formula}SEQ-model {a mathematical formula}Iκ of P is in fact compatible with this view, and would be an intuitive result.
     </paragraph>
     <paragraph>
      To overcome this limitation, we introduce a refined paracoherent semantics, called split semi-equilibrium semantics. It coincides with the answer sets semantics in case of coherent programs, and it selects a subset of the {a mathematical formula}SEQ-models otherwise based on a given splitting sequence that induces a modular decomposition of a program at hand. The main results of this section are two model-theoretic characterizations which identify necessary and sufficient conditions for deciding whether a {a mathematical formula}SEQ-model is selected according to a splitting sequence. As it turns out (and can be seen from the examples above), different splitting sequences can yield different selection results, which is not the case for {a mathematical formula}EQ-models. Based on the results of this section, we will present in Section 6 canonical {a mathematical formula}SEQ-models that are independent of a particular splitting sequence. The canonical {a mathematical formula}SEQ-models ensure robustness of modular evaluation, as like for the {a mathematical formula}EQ-models the concrete bottom-up evaluation order taken by a solver does not matter; furthermore, the notion can be easily generalized to programs that are hierarchically organized in user-defined subprograms, which we shall briefly address in Section 9.2.
     </paragraph>
     <section label="5.1">
      <section-title>
       Split semi-equilibrium models
      </section-title>
      <paragraph label="Definition 7">
       We now introduce the notion of {a mathematical formula}SEQ-models relative to a splitting set. First given a splitting set S for a program P and an HT-interpretation {a mathematical formula}(I,J) for {a mathematical formula}bS(P), we let{a mathematical formula} Informally, the bottom part of P w.r.t. S is replaced with rules and constraints which fix in any {a mathematical formula}SEQ-model of the remainder ({a mathematical formula}=tS(P)) the values of the atoms in S to {a mathematical formula}(I,J). Semi-equilibrium models relative to a splitting setLet S be a splitting set of a program P. Then the semi-equilibrium models of P relative to S are defined as{a mathematical formula}
      </paragraph>
      <paragraph label="Example 25">
       Reconsider the party program in Example 2, {a mathematical formula}P={b←nota;d←b,notc;c←d}, where a, b, and c, d stand for {a mathematical formula}go(Mark), {a mathematical formula}go(John), {a mathematical formula}go(Bill), and {a mathematical formula}go(Peter), respectively. We have {a mathematical formula}SEQ(P)={(∅,a), {a mathematical formula}(b,bc)}, where {a mathematical formula}(b,bc) is more appealing than {a mathematical formula}(∅,a) because a is not derivable, as no rule has a in the head. Moreover, intuitively, {a mathematical formula}P1={b←nota} is a lower (coherent) part feeding into the upper part {a mathematical formula}P2={d←b,notc;c←d}. This is formally captured by the splitting set {a mathematical formula}S={a,b}, which yields {a mathematical formula}bS(P)=P1 and {a mathematical formula}SEQ(bS(P))={(b,b)}. Hence, {a mathematical formula}PS(b,b)={d←b,notc;c←d;b;←a} and {a mathematical formula}SEQS(P)=SEQ(PS(b,b))={(b,bc)}.
      </paragraph>
      <paragraph>
       In what follows, we establish a semantic characterization of the {a mathematical formula}SEQ-models relative to a splitting set as those {a mathematical formula}SEQ-models of the program that extend {a mathematical formula}SEQ-models of the bottom part.
      </paragraph>
      <paragraph>
       Notation. For any HT-model {a mathematical formula}(X,Y) and set S of atoms, we define the restriction of{a mathematical formula}(X,Y)to S as {a mathematical formula}(X,Y)|S=(X∩S,Y∩S).
      </paragraph>
      <paragraph label="Proposition 10">
       Let S be a splitting set of a program P. If{a mathematical formula}(X,Y)∈SEQS(P), then{a mathematical formula}(X,Y)|S∈SEQ(bS(P)).
      </paragraph>
      <paragraph>
       The following result shows that each semi-equilibrium model relative to a given splitting set is always a semi-equilibrium model of the program.
      </paragraph>
      <paragraph label="Proposition 11">
       SoundnessLet S be a splitting set of a program P. If{a mathematical formula}(X,Y)∈SEQS(P), then{a mathematical formula}(X,Y)∈SEQ(P).
      </paragraph>
      <paragraph>
       This result is proven by establishing first that HT-models of the program {a mathematical formula}PS(I,J) are HT-models of the program P, and then the h-minimality and gap-minimality of {a mathematical formula}(X,Y). More precisely, the first step uses the following lemma:
      </paragraph>
      <paragraph label="Lemma 1">
       Let S be a splitting set of a program P and let{a mathematical formula}(I,J)∈SEQ(bS(P)). If{a mathematical formula}(X,Y)is an HT-model of{a mathematical formula}PS(I,J), then{a mathematical formula}(X,Y)is an HT-model of P.
      </paragraph>
      <paragraph>
       However, the converse of Proposition 11 does not hold in general; in fact if we consider the program of Example 25 and the splitting set {a mathematical formula}S={a,b} we have {a mathematical formula}SEQS(P)={(b,bc)}, while {a mathematical formula}SEQ(P)={(∅,a),(b,bc)}. Clearly, {a mathematical formula}SEQS(P) depends on the choice of S; in fact if we choose {a mathematical formula}S=∅, then {a mathematical formula}SEQ∅(P)=SEQ(P).
      </paragraph>
      <paragraph label="Example 26">
       Moreover for Proposition 11 to hold, the selection of maximal canonical HT-models is necessary. For {a mathematical formula}P={a←notb;b←nota;c←b,notc} and the splitting set {a mathematical formula}S={a,b}, we have {a mathematical formula}SEQ(bS(P))={(a,a),(b,b)}; hence {a mathematical formula}SEQ(PS(a,a))∪SEQ(PS(b,b))={(a,a),(b,bc)}, while {a mathematical formula}SEQ(P)={(a,a)}.
      </paragraph>
      <paragraph>
       So far, we have presented two properties of an HT-model that are necessary conditions to qualify as a {a mathematical formula}SEQ-model relative to a given splitting set. The natural question is whether these conditions are also sufficient; this is indeed the case.
      </paragraph>
      <paragraph label="Proposition 12">
       CompletenessLet S be a splitting set of a program P. If{a mathematical formula}(X,Y)∈SEQ(P)and{a mathematical formula}(X,Y)|S∈SEQ(bS(P)), then{a mathematical formula}(X,Y)∈SEQS(P).
      </paragraph>
      <paragraph>
       Putting the results above together, we obtain the following semantic characterization of {a mathematical formula}SEQ-models relative to a splitting set.
      </paragraph>
      <paragraph label="Theorem 4">
       SEQ-model characterizationLet S be a splitting set of a program P. Then{a mathematical formula}(X,Y)∈SEQS(P)iff{a mathematical formula}(X,Y)∈SEQ(P)and{a mathematical formula}(X,Y)|S∈SEQ(bS(P)).
      </paragraph>
      <paragraph label="Proof">
       The only-if direction follows from Proposition 10, Proposition 11; the if direction holds by Proposition 12.  □
      </paragraph>
      <paragraph>
       Like the ordinary {a mathematical formula}SEQ-models, also the split {a mathematical formula}SEQ-models coincide with the answer sets of a program if some answer set exists.
      </paragraph>
      <paragraph label="Corollary 3">
       Let P be a program such that{a mathematical formula}EQ(P)≠∅. Then for every splitting set S of P,{a mathematical formula}SEQS(P)=EQ(P); in particular, if P is positive, then{a mathematical formula}SEQS(P)={(M,M)|M∈MM(P)}.
      </paragraph>
      <paragraph>
       We observe that a program which has some model does not necessarily have split semi-equilibrium models (but always semi-equilibrium models) as seen in Example 24. We give another example of a much simpler program.
      </paragraph>
      <paragraph label="Example 27">
       Let us consider {a mathematical formula}P={←b;b←nota} and the splitting set {a mathematical formula}S={a}. Then we obtain {a mathematical formula}SEQ(bS(P))={(∅,∅)} and so {a mathematical formula}SEQS(P)=∅. However {a mathematical formula}(a,a) and {a mathematical formula}(∅,a) are HT-models of P.
      </paragraph>
      <paragraph>
       Note that occurrence of a constraint in the previous example is not accidental; in fact,
      </paragraph>
      <paragraph label="Proposition 13">
       For every constraint-free program P and splitting set S of P, it holds that{a mathematical formula}SEQ(PS)≠∅.
      </paragraph>
      <paragraph>
       In summary, the split {a mathematical formula}SEQ-models have the following profile with respect to the properties (D1)–(D3).
      </paragraph>
      <paragraph label="Proposition 14">
       The split{a mathematical formula}SEQ-models semantics of a program P relative to a splitting set S of P, given by{a mathematical formula}SEQS(P), satisfies properties (D1)–(D2), and if P is constraint-free, also (D3).
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Split sequence semi-equilibrium models
      </section-title>
      <paragraph>
       Now we generalize the use of splitting sets to {a mathematical formula}SEQ-models of a program via splitting sequences. To this end, we naturally reduce a splitting sequence to its head and its remainder and apply splitting sets recursively.
      </paragraph>
      <paragraph label="Example 28">
       Semi-equilibrium models relative to a splitting sequenceLet {a mathematical formula}S=(S1,…,Sn), {a mathematical formula}n≥1, be a splitting sequence for a program P. Then the semi-equilibrium models of P relative to S are given by{a mathematical formula} where {a mathematical formula}S′=(S2,…,Sn) and {a mathematical formula}SEQ()(P)=SEQ(P) (recall that {a mathematical formula}PS1(I,J) adds rules to P that fix the truth values of all atoms in {a mathematical formula}S1 according to {a mathematical formula}(I,J)).Reconsider the program in Example 2, Example 25, {a mathematical formula}P={b←nota;d←b,notc;c←d}. Then {a mathematical formula}S=({a},{a,b},{a,b,c,d}) is a splitting sequence for P, and we obtain that {a mathematical formula}SEQS(P)={(b,bc)}. Indeed {a mathematical formula}bS1(P)=∅ and thus {a mathematical formula}SEQ(bS1(P))={(∅,∅)}; for the remainder sequence {a mathematical formula}S′=({a,b},{a,b,c,d}) and {a mathematical formula}P′=PS1(∅,∅)=P∪{←a}, we get {a mathematical formula}bs1′(P′)={b←nota,←a} and thus {a mathematical formula}SEQ(bS1′(P′))={(b,b)}. Finally, for {a mathematical formula}S″=({a,b,c,d}) and {a mathematical formula}P″=PS1′(b,b)=P∪{←a;b←}, we obtain {a mathematical formula}bS1″(P″)=P″ and thus {a mathematical formula}SEQ(bS1″(P″)={(b,bc}), which is the final result. The {a mathematical formula}SEQ-models relative to a splitting sequence can be characterized similarly as those relative to a splitting set, namely as {a mathematical formula}SEQ-models of the program that remain by filtering the {a mathematical formula}SEQ-models along the splitting sequence.
      </paragraph>
      <paragraph>
       To ease presentation, for a given program P and splitting sequence {a mathematical formula}S=(S1,…,Sn), we let {a mathematical formula}P0=P and {a mathematical formula}Pk=(Pk−1)Sk(Ik,Jk), where {a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1)), {a mathematical formula}k=1,…,n; that is, {a mathematical formula}Pk is not uniquely defined but ranges over a set of programs.
      </paragraph>
      <paragraph>
       The main result of this section is now as follows.
      </paragraph>
      <paragraph label="Theorem 5">
       Let{a mathematical formula}S=(S1,…,Sn)be a splitting sequence of a program P. Then{a mathematical formula}(X,Y)∈SEQS(P)iff{a mathematical formula}(X,Y)∈SEQ(P)and{a mathematical formula}(X,Y)|Sk∈SEQ(bSk(Pk−1)), for some{a mathematical formula}Pk, for{a mathematical formula}k=1,…,n.
      </paragraph>
      <paragraph>
       The proof proceeds by induction using Theorem 4. Corollary 3 of Theorem 4 also generalizes to splitting sequences.
      </paragraph>
      <paragraph label="Proof">
       Let P be a program such that{a mathematical formula}EQ(P)≠∅. Then for every splitting sequence S of P,{a mathematical formula}SEQS(P)=EQ(P); in particular, if P is positive, then{a mathematical formula}SEQS(P)={(M,M)|M∈MM(P)}.[Sketch] Using Theorem 5, this can be shown by induction, using Corollary 2, Corollary 3.  □
      </paragraph>
      <paragraph>
       Another consequence of Theorem 5 is that, written in other form, the split sequence {a mathematical formula}SEQ-models of a program can be bottom up constructed, taking into account that at each stage only the respective rules (i.e., {a mathematical formula}bSj+1(P)∖bSj(P)) need to be considered. More formally,
      </paragraph>
      <paragraph label="Corollary 5">
       For every splitting sequence{a mathematical formula}S=(S1,…,Sn)of a program P, it holds that{a mathematical formula}SEQS(P)=Sn, where for{a mathematical formula}j=n,…,1we have{a mathematical formula}where{a mathematical formula}Qj=bSj+1(P)∖bSj(P)with{a mathematical formula}bSn+1(P)=Pand{a mathematical formula}S0=SEQ(bS1(P)).
      </paragraph>
      <paragraph>
       This form is in fact a suitable starting point for computation; we refer to Section 6.1 for further discussion.
      </paragraph>
      <paragraph>
       Regarding the existence of split sequence {a mathematical formula}SEQ-models, we obtain a generalization of Proposition 13.
      </paragraph>
      <paragraph label="Proposition 15">
       For every splitting sequence S of a constraint-free program P, it holds that{a mathematical formula}SEQ(PS)≠∅.
      </paragraph>
      <paragraph label="Proof">
       [Sketch] This can be shown by an inductive argument, along the lines of the proof of Proposition 13, using Proposition 7, Proposition 13.  □
      </paragraph>
      <paragraph>
       In particular, we obtain from this the following result for stratified programs.
      </paragraph>
      <paragraph label="Corollary 6">
       For every splitting sequence S of a stratified program P that is constraint-free, it holds that{a mathematical formula}SEQS(P)=EQ(P).
      </paragraph>
      <paragraph>
       In conclusion, we obtain the following profile of split sequence {a mathematical formula}SEQ-models with respect to the properties (D1)–(D3).
      </paragraph>
      <paragraph label="Proposition 16">
       The split sequence{a mathematical formula}SEQ-models semantics of a program P relative to a splitting sequence S of P, given by{a mathematical formula}SEQS(P), satisfies properties (D1)–(D2), and if P is constraint-free, also (D3).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Canonical semi-equilibrium models
     </section-title>
     <paragraph label="Example 29">
      As we have pointed out in the discussion at the beginning of the previous section, the split semi-equilibrium semantics depends in general on the choice of the particular splitting sequence. For illustration, let us revisit the examples there. In the party program of Example 2, we obtain the first {a mathematical formula}SEQ-model of P with respect to the splitting set {a mathematical formula}S={go(Mark)}, but not the second {a mathematical formula}SEQ-model. Similarly, in the company Example 24 we obtained with respect to the considered splitting set S no {a mathematical formula}SEQ-model, while we obtain the single {a mathematical formula}SEQ-model of the program with respect to {a mathematical formula}S′={manager(sam), {a mathematical formula}employee(sam), {a mathematical formula}core_staff(sam,sam)}. This behavior is unfortunate, the more as in program evaluation, it is not known which splitting sequence is actually used by a solver for the evaluation, and this aspect should not matter from user perspective. Likewise, it should not matter in which order independent subprograms of a program are evaluated.
     </paragraph>
     <paragraph>
      We thus consider a way to obtain a refined split {a mathematical formula}SEQ-semantics that is independent of a particular splitting sequence, but imposes conditions on sequences that come naturally with the program and can be easily tested. Along with this the question rises what information about the splitting sequences that are (potentially) used for evaluation is available. If we just have a plain program P and no further information, in principle any splitting sequence needs to be considered; if the program P is composed of subprograms {a mathematical formula}P1,…,Pm, then only splitting sequences that are “compatible” with the hierarchical ordering of the subprograms need to be respected.
     </paragraph>
     <paragraph>
      We base our development on the first setting, as it is at the core of program evaluation, and moreover a generalization to the setting with subprograms is not hard to accomplish, once the notions and results for this setting are established; we shall address this in Section 9.2.
     </paragraph>
     <paragraph>
      The smallest possible splitting sets of a program are strongly connected components (SCCs) of the program, which are at the heart of bottom up evaluation algorithms in ASP systems. Thus in lack of further information on program decomposition, we shall base our development on splitting sequences that are formed from SCCs of the program.
     </paragraph>
     <paragraph label="Example 30">
      We then get the desired independence of a particular splitting sequence, such that we can then talk about the {a mathematical formula}SCC-models of a program. The program in the party Example 2 has two SCCs, namely {a mathematical formula}C1={go(Mark)} and {a mathematical formula}C2={go(John),go(Bill),go(Peter)}), which form a single splitting sequence {a mathematical formula}S=(C1,C2); thus, the model {a mathematical formula}I1κ is selected as the single {a mathematical formula}SCC-model of the program.
     </paragraph>
     <paragraph>
      However, a closer look reveals that independence might fail in presence of certain constraints that join information in unrelated SCCs of a program. An illustration is given by the company program in Example 24.
     </paragraph>
     <paragraph label="Example 31">
      The SCCs of the program in Example 24 are all singleton sets {a mathematical formula}{a} where a is a ground atom. For the emerging splitting sequences {a mathematical formula}S=(S1,…,Sn) where {a mathematical formula}core_staff(sam) occurs before {a mathematical formula}has_social_sec(sam) (i.e., {a mathematical formula}core_staff(sam)∈Si and {a mathematical formula}has_social_sec(sam)∈Sj∖Si with {a mathematical formula}i&lt;j), we obtain no {a mathematical formula}SEQ-model, but we obtain the single {a mathematical formula}SEQ-model {a mathematical formula}Iκ in the other cases. Intuitively, the constraint in P accesses unrelated information from independent SCCs; if {a mathematical formula}has_social_sec(sam) has already been evaluated (to false), no beliefs help to make the constraint body false; otherwise, believing that {a mathematical formula}has_social_sec(sam) is true achieves this.
     </paragraph>
     <paragraph>
      For this reason, we present a split {a mathematical formula}SEQ-model semantics where the selected {a mathematical formula}SEQ-models are truly independent of the concrete admissible splitting sequence. The semantics is the maximal joinable components ({a mathematical formula}MJC) model semantics, which results by a lean merging of SCCs that violate independence due to interaction with constraints. In the company example, the SCCs {a mathematical formula}{core_staff(sam)} and {a mathematical formula}{has_social_sec(sam)} will be merged; this prevents that the constraint on social security is considered only after {a mathematical formula}has_social_sec(sam) has already been decided. The single {a mathematical formula}MJC-model of the program is then its single {a mathematical formula}SEQ-model.
     </paragraph>
     <section label="6.1">
      {a mathematical formula}SCC-split sequences and models
      <paragraph>
       We start with recalling further notions. The supergraph of a program P is the graph {a mathematical formula}SG(P)=〈VSG,ESG〉, whose nodes {a mathematical formula}VSG are the SCCs of P and with an edge from an SCC C to a distinct SCC {a mathematical formula}C′ iff the dependency graph of P has an edge from some atom in C to one in {a mathematical formula}C′; i.e., formally {a mathematical formula}VSG=SCC(P) and {a mathematical formula}ESG={(C,C′)|C≠C′∈SCC(P),∃a∈C,∃b∈C′,(a,b)∈EDG}. Note that {a mathematical formula}SG(P) is a directed acyclic graph (dag); recall that a topological ordering of a dag {a mathematical formula}G=〈V,E〉 is an ordering {a mathematical formula}v1,v2,…,vn of its vertices, denoted ≤, such that for every {a mathematical formula}(vi,vj)∈E we have {a mathematical formula}i&gt;j. Such an ordering always exists, and the set {a mathematical formula}O(G) of all topological orderings of G is nonempty. Any such ordering of {a mathematical formula}SG(P) naturally induces a splitting sequence as follows.
      </paragraph>
      <paragraph label="Definition 9">
       Let P be a program and let {a mathematical formula}≤=(C1,…,Cn) be a topological ordering of {a mathematical formula}SG(P). Then the splitting sequence induced by ≤ is {a mathematical formula}S≤=(S1,…,Sn), where {a mathematical formula}S1=C1 and {a mathematical formula}Sj=Sj−1∪Cj, for {a mathematical formula}j=2,…,n.
      </paragraph>
      <paragraph>
       We call any such {a mathematical formula}S≤ a {a mathematical formula}SCC-splitting sequence; note that {a mathematical formula}S≤ is indeed a splitting sequence of P.
      </paragraph>
      <paragraph>
       We now show that for constraint-free programs, the split {a mathematical formula}SEQ-models relative to {a mathematical formula}SCC-split sequence are independent of the concrete such sequence; in fact, we establish this result for programs in which certain constraints do not occur.
      </paragraph>
      <paragraph label="Definition 10">
       A constraint r in P is a cross-constraint, if r intersects distinct SCCs {a mathematical formula}Ci,Cj in {a mathematical formula}SCC(P) that are incomparable in {a mathematical formula}SG(P), i.e., {a mathematical formula}Ci∩At(r)≠∅, {a mathematical formula}Cj∩At(r)≠∅, and {a mathematical formula}SG(P) has topological orderings of the forms {a mathematical formula}(…,Ci,…,Cj,…) and {a mathematical formula}(…,Cj,…,Ci,…).
      </paragraph>
      <paragraph label="Example 32">
       For example, the constraint ←b in the program P of Example 27 is trivially not a cross-constraint, and likewise an additional constraint {a mathematical formula}←a,b. However, an additional constraint {a mathematical formula}←b,c would be a cross-constraint. Intuitively, a cross-constraint joins information from different parts {a mathematical formula}Ci and {a mathematical formula}Cj of the program that might be evaluated in either order under {a mathematical formula}EQ-model semantics. If under {a mathematical formula}SEQ-model semantics the literals in the constraint over {a mathematical formula}Ci evaluate to true, then making some atoms in {a mathematical formula}Cj believed true may effect that the constraint body becomes false, and we thus obtain a {a mathematical formula}SEQ-model; if we proceed in the other order and start with {a mathematical formula}Cj, those atoms might be simply set to false and then there is no chance to arrive at a {a mathematical formula}SEQ-model when processing {a mathematical formula}Ci. We illustrate this on a simple example. Consider the program {a mathematical formula}P={b;←b,nota}. It has the SCCs {a mathematical formula}{a} and {a mathematical formula}{b} which are incomparable in the supergraph {a mathematical formula}SG(P); we may now set {a mathematical formula}Ci={a} and {a mathematical formula}Cj={b}. If we evaluate P along the {a mathematical formula}SCC-sequence {a mathematical formula}S=({a},{b}), we obtain no {a mathematical formula}SEQS-model; however, if we evaluate P along {a mathematical formula}S′=({b},{a}), then we obtain the (single) {a mathematical formula}SEQS′-model {a mathematical formula}(b,ba).
      </paragraph>
      <paragraph>
       We obtain the following result.
      </paragraph>
      <paragraph label="Theorem 6">
       Let P be a program without cross-constraints. Then for every{a mathematical formula}≤,≤′∈O(SG(P)), we have that{a mathematical formula}SEQS≤(P)=SEQS≤′(P).
      </paragraph>
      <paragraph label="Corollary 7">
       For every constraint-free program P, the{a mathematical formula}SEQ-models of P relative to an{a mathematical formula}SCC-split sequence S are independent of the choice of S.
      </paragraph>
      <paragraph>
       The proof of Theorem 6 is technically involving as it needs to be shown that changes in the ordering of the SCCs do not matter in the end. It uses a series of lemmas which assert certain properties of semi-equilibrium models {a mathematical formula}(Ik,Jk) of the programs {a mathematical formula}Pk that emerge in the bottom up characterization of Theorem 5, and independence properties in certain cases; in particular, where for any sets {a mathematical formula}M and {a mathematical formula}M′ of HT-models, their product is given by {a mathematical formula}M×M′={(X∪X′,Y∪Y′)|(X,Y)∈M, {a mathematical formula}(X′,Y′)∈M′}:
      </paragraph>
      <paragraph label="Proposition 17">
       Let P be a program in which each constraint r fulfills either{a mathematical formula}At(r)⊆Sor{a mathematical formula}At(r)⊆At(P)∖S. If{a mathematical formula}S⊆At(P)is such that both S and{a mathematical formula}At(P)∖Sare splitting sets of P, then{a mathematical formula}Theorem 6 is an analog of the Stratification Theorem [3], [46] which states that the perfect (stratified) model of a logic program relative to a stratification is independent of the concrete stratification, and thus one can simply refer to the perfect model of a stratified program; similarly, we thus can define the strongly connected components models of a program as follows.
      </paragraph>
      <paragraph label="Definition 11">
       {a mathematical formula}SCC-modelsFor every program P without cross-constraints, the {a mathematical formula}SCC-models of P are given as {a mathematical formula}MSCC(P)=SEQS≤(P) for an arbitrary topological ordering ≤ of {a mathematical formula}SG(P).
      </paragraph>
      <paragraph label="Example 34">
       Let us consider some examples. The party program P in the Example 25 is constraint-free; hence, it has some {a mathematical formula}SCC-model. The splitting sequence S for P given in Example 27 is in fact an {a mathematical formula}SCC-splitting sequence, and thus the single {a mathematical formula}SEQS-model {a mathematical formula}(b,bc) is the singe {a mathematical formula}SCC-model of P.The program {a mathematical formula}P={←b;b←nota} in Example 27 is cross-constraint free. It has the SCCs {a mathematical formula}{a} and {a mathematical formula}{b}, and for the single {a mathematical formula}SCC-split sequence {a mathematical formula}S=({a},{a,b}), no split sequence {a mathematical formula}SEQ-model exists; does P has no {a mathematical formula}SCC-model. As this example shows, SCCs may be too fine-grained sometimes to obtain modular {a mathematical formula}SEQ-models in the presence of constraints. This can be remedied by using coarser modules that are defined by the user (cf. Section 9.2).
      </paragraph>
      <paragraph label="Example 35">
       Consider the program{a mathematical formula} Its SCCs are {a mathematical formula}C1={a}, {a mathematical formula}C2={b,f}, {a mathematical formula}C3={c,g,h}, {a mathematical formula}C4={d} and {a mathematical formula}C5={e}; as a depends on d, the single constraint {a mathematical formula}←a,d is not a cross-constraint. For the ordering {a mathematical formula}≤=(C4,C5,C3,C2,C1), we obtain that{a mathematical formula} hence {a mathematical formula}MSCC(P)={(bc,abcf)}. For {a mathematical formula}≤′=(C5,C2,C4,C3,C1), we obtain {a mathematical formula}SEQS≤′(P)={(bc,abcf)}, in line with Theorem 6. Note that {a mathematical formula}SEQ(P)={(bc,abcf), {a mathematical formula}(b,bdf),(ac,ace)}.
      </paragraph>
      <paragraph>
       Regarding the properties (D1)–(D3) of a paracoherent semantics in the Introduction, we obtain from Proposition 16 immediately
      </paragraph>
      <paragraph label="Corollary 8">
       The{a mathematical formula}SCC-models semantics, given by{a mathematical formula}MSCC(P)for programs P without cross-constraints, satisfies properties (D1)–(D2), and it satisfies (D3) for programs without constraints.
      </paragraph>
      <paragraph>
       As for the properties of {a mathematical formula}SCC-models, we focus here on a particular aspect that is important with respect to an envisaged exploitation for paracoherent answer set construction; computational aspects are considered in Section 7.
      </paragraph>
      <section label="6.1.1">
       Modularity of {a mathematical formula}SCC-models
       <paragraph>
        In the definition of split {a mathematical formula}SEQ-models, we made use of splitting sets as a major tool for modular computation of equilibrium models (answer sets) of a logic program. Indeed, for any splitting set S of P, as follows from [31] we have that{a mathematical formula} Note the similarity to the equation in (9) which we used to define{a mathematical formula}SEQ-models of a program relative to a splitting set; the major difference is that we use the {a mathematical formula}mc(⋅) operator to single out smallest gaps at a global level. And, in general for different S we shall obtain different {a mathematical formula}SEQ-models from (9). However, if we confine to {a mathematical formula}SCC-models, then an analog to (11) and its generalization to splitting sequences holds.
       </paragraph>
       <paragraph>
        That is, if we replace in Equation (10){a mathematical formula}SEQ, {a mathematical formula}SEQS, and {a mathematical formula}SEQS′ all by {a mathematical formula}MSCC, then the resulting equation holds.
       </paragraph>
       <paragraph label="Theorem 7">
        Let S be a splitting set of a program P without cross-constraints. Then{a mathematical formula}
       </paragraph>
       <paragraph>
        Thanks to this result, we can compute the {a mathematical formula}SCC-models of a given program modularly bottom up along an arbitrary splitting sequence (using always {a mathematical formula}MSCC); in particular, if an algorithm has processed a bottom part {a mathematical formula}bS(P) of a program P and found equilibrium models (answer sets) for it, and it encounters that an extension of these equilibrium models using (11) does not yield any answer set, then it can switch to a “paracoherent mode” and apply (7); as {a mathematical formula}MSCC(bS(P))=EQ(bS(P)), we obtain the same result as if we would compute the {a mathematical formula}SCC-models of P from scratch. That is, no backtracking or restarting of the computation is necessary.
       </paragraph>
       <paragraph label="Proposition 18">
        We note none of the occurrences of {a mathematical formula}MSCC in the equation (12) can be replaced with {a mathematical formula}SEQ or an arbitrary {a mathematical formula}SEQS′ in general, that is compute and use simply the semi-equilibrium models respectively the split semi-equilibrium models of the bottom part and/or the remainder of the program relative to {a mathematical formula}S′; in addition to all {a mathematical formula}SCC-models, we might get some semi-equilibrium models of the program P where the particular splitting sequence {a mathematical formula}S′ matters. Formally, the following property holds, which is an easy consequence of Theorem 5. Let S be a splitting sequence of a program P without cross-constraints. Then{a mathematical formula}where{a mathematical formula}SQ(P)is the set of all splitting sequences of P.
       </paragraph>
      </section>
     </section>
     <section label="6.2">
      {a mathematical formula}MJC-split sequences and models
      <paragraph>
       Unfortunately, Theorem 6 fails if we allow arbitrary constraints in P, as witnessed e.g. by the programs in Example 32, Example 24. To deal with this situation, different ways are possible.
      </paragraph>
      <list>
       <list-item>
        One way is to exclude constraints (or less restrictive, cross-constraints), and resort instead to the usage of rules which create unstable negation; that is{a mathematical formula} is replaced with{a mathematical formula} where f is a fresh atom. Indeed, on some (early) implementations of answer set solvers constraints have been provided in this way. The {a mathematical formula}SEQ-model semantics is able to distinguish between (13) and (14); this can be exploited to use (14) as a soft constraint that may intuitively be violated if needed to achieve an {a mathematical formula}EQ-model resp. answer set; indeed, this rule can always be satisfied by considering f as believed true.
       </list-item>
       <list-item>
        Another possibility is to remedy situations in which constraints are not embedded in ordered SCCs. To this end, we consider merging of SCCs in such a way that (i) independence of concrete topological orderings is preserved and, furthermore, (ii) merging is performed conservatively, that is only if it is deemed necessary. This is embodied by the maximal joinable components of a program, which lead to so called {a mathematical formula}MJC-split sequences and models. Informally, relevant SCCs that are incomparable (thus unproblematic in evaluation if we disregard cross-constraints) are merged if they both intersect with a constraint. The merging is repeated until no cross-constraint violation exists with respect to the new (merged) components. In the rest of this subsection, we formalize this approach on a declarative basis.
       </list-item>
      </list>
      <paragraph>
       We start with introducing the notions of related pairs and joinable pairs of SCCs. We call a pair {a mathematical formula}(K1,K2) of SCCs of P a related pair, if either {a mathematical formula}K1=K2 or some constraint {a mathematical formula}r∈P intersects both {a mathematical formula}K1 and {a mathematical formula}K2, i.e., {a mathematical formula}At(r)∩K1≠∅ and {a mathematical formula}At(r)∩K2≠∅. By {a mathematical formula}C(K1,K2)(P) we denote the set of all such constraints r.
      </paragraph>
      <paragraph label="Definition 12">
       A related pair {a mathematical formula}(K1,K2) is a joinable pair, if {a mathematical formula}K1=K2 or some ordering {a mathematical formula}(C1,…,Cn) in {a mathematical formula}O(SG(P)) exists such that (i) {a mathematical formula}K1=Cs and {a mathematical formula}K2=Cs+1 for some {a mathematical formula}1≤s&lt;n, (ii) {a mathematical formula}(K2,K1)∉ESG and (iii) some {a mathematical formula}r∈C(K1,K2)(P) exists such that {a mathematical formula}At(r)⊆C1∪…∪Cs+1. By {a mathematical formula}JP(P) we denote the set of all joinable pairs of P.
      </paragraph>
      <paragraph>
       Intuitively item (i) states that in some topological ordering {a mathematical formula}K1 immediately precedes {a mathematical formula}K2; item (ii) states that no atom in {a mathematical formula}K2 directly depends on an atom from {a mathematical formula}K1. If this does not hold, joining {a mathematical formula}K1 and {a mathematical formula}K2 to achieve independence is not necessary as their ordering is fixed. Finally item (iii) requires that some constraint must access the two SCCs (which thus must be a cross-constraint) and appear in the evaluation in the bottom of the program computed so far.
      </paragraph>
      <paragraph label="Example 36">
       Reconsider the program {a mathematical formula}P={b;←b,nota} in Example 32 with the incomparable SCCs {a mathematical formula}{a}, {a mathematical formula}{b} and the cross-constraint {a mathematical formula}←b,nota. The pair {a mathematical formula}(K1,K2) for {a mathematical formula}K1={a} and {a mathematical formula}K2={a,b} is related and also joinable.
      </paragraph>
      <paragraph label="Example 37">
       For {a mathematical formula}P={←b,nota;←b,notc;d←nota;c←note;b←c}, we have {a mathematical formula}SCC(P)={{a},{b}, {a mathematical formula}{c},{d},{e}}. We observe that {a mathematical formula}({c},{b}) is a related, but not a joinable pair, because {a mathematical formula}({c},{b}) satisfies conditions (i) and (iii), but not (ii). On the other hand, {a mathematical formula}({a},{b}) is a joinable pair.
      </paragraph>
      <paragraph label="Example 38">
       Reconsider the company program P in Example 24, and recall that the SCCs (of the ground version) of P are all sets {a mathematical formula}{a}, where a is a ground atom; for brevity, we abbreviate predicate names to the first letter. In the supergraph {a mathematical formula}SG(P), we then have the edges {a mathematical formula}({c(sam)},{m(sam)), {a mathematical formula}({e(sam)},{m(sam)), {a mathematical formula}({h(sam)},{e(sam)}), and {a mathematical formula}({h(sam)},{s(sam,sam)}).{sup:10} For {a mathematical formula}K1={c(sam)} and {a mathematical formula}K2={h(sam)}, we obtain that {a mathematical formula}(K1,K2) is a related and also joinable pair. Similarly, {a mathematical formula}({c(sam)},{e(sam)}) is a related and joinable pair; while {a mathematical formula}({h(sam)},{e(sam)}) is a related pair, it is not joinable (condition (ii) fails).
      </paragraph>
      <paragraph label="Definition 13">
       We now extend joinability from pairs to any number of SCCs. Let P be a program. Then {a mathematical formula}K1,…,Km∈SCC(P) are joinable, if {a mathematical formula}m=2 and some {a mathematical formula}K∈SCC(P) exists such that {a mathematical formula}(K1,K),(K,K2)∈JP(P), or otherwise {a mathematical formula}Ki,Kj are joinable for each {a mathematical formula}i,j=1,…,m. We let {a mathematical formula}JC(P)={⋃i=1mKi|K1,…,Km∈SCC(P) are joinable} and call{a mathematical formula} the set of all maximal joined components ({a mathematical formula}MJCs) of P. Note that {a mathematical formula}(K1,K2)∈JP(P) implies that {a mathematical formula}K1 and {a mathematical formula}K2 are joinable (choose {a mathematical formula}K=K1).
      </paragraph>
      <paragraph label="Example 41">
       continuedThe program {a mathematical formula}P={b;←b,nota} has the single joinable pair {a mathematical formula}({a},{b}) and thus the single maximal joined component {a mathematical formula}{a,b}.continuedIn Example 37, {a mathematical formula}({a},{b}) is the only nontrivial joinable pair; hence {a mathematical formula}MJC(P)={{a,b},{c}, {a mathematical formula}{d},{e}}.continuedFor the company program P in Example 24, the nontrivial joinable components are {a mathematical formula}({c(sam)},{h(sam)}) and {a mathematical formula}({c(sam)},{e(sam)}); hence {a mathematical formula}MJC(P)={{e(sam),h(sam),c(sam)}, {a mathematical formula}{m(sam)}, {a mathematical formula}{s(sam)}}. As easily seen, {a mathematical formula}MJC(P) is a partitioning of {a mathematical formula}At(P) that results from merging SCCs. We define a dependency graph on them, called the {a mathematical formula}MJCgraph of P and denoted {a mathematical formula}JG(P), that is analogous to the supergraph on the SCCs. Formally, {a mathematical formula}JG(P)=〈VJG,EJG〉, where {a mathematical formula}VJG=MJC(P) and {a mathematical formula}EJG={(J,J′)|J≠J′∈MJC(P),∃a∈J,∃b∈J′,(a,b)∈EDG}. Note that {a mathematical formula}JG(P) is like {a mathematical formula}SG(P) a directed acyclic graph, and hence admits a topological ordering; we denote by {a mathematical formula}O(JG(P)) the set of all such orderings. We thus define
      </paragraph>
      <paragraph label="Definition 14">
       Let P be a program and {a mathematical formula}≤=(J1,…,Jm) be a topological ordering of {a mathematical formula}JG(P). Then the splitting sequence induced by ≤ is {a mathematical formula}S≤=(S1,…,Sm), where {a mathematical formula}S1=J1 and {a mathematical formula}Sk=Sk−1∪Jk, for {a mathematical formula}k=2,…,m.
      </paragraph>
      <paragraph>
       The sequence {a mathematical formula}S≤ is again indeed a splitting sequence, which we call a {a mathematical formula}MJC-splitting sequence. We obtain a result analogous to Theorem 6, but in presence of constraints.
      </paragraph>
      <paragraph label="Theorem 8">
       Let P be a program. For every{a mathematical formula}≤,≤′∈O(JG(P)), we have{a mathematical formula}SEQS≤(P)=SEQS≤′(P).
      </paragraph>
      <paragraph>
       The proof of this result is similar to the one of Theorem 6, but uses different lemmas.
      </paragraph>
      <paragraph>
       Similarly as {a mathematical formula}SCC-models, we thus can define the {a mathematical formula}MJC-models of a program.
      </paragraph>
      <paragraph label="Definition 15">
       {a mathematical formula}MJC-modelsFor any program P, the {a mathematical formula}MJC-models of P are given as {a mathematical formula}MMJC(P)=SEQS≤(P) for an arbitrary topological ordering ≤ of {a mathematical formula}JG(P).
      </paragraph>
      <paragraph label="Example 42">
       continuedReconsider P in Example 37. Then for the ordering {a mathematical formula}≤=({a},{d},{e},{c},{b}) we obtain {a mathematical formula}SEQS≤(P)=∅, while for {a mathematical formula}≤′=({e},{c},{b},{a},{d}) we obtain {a mathematical formula}SEQS≤′(P)={(bc,abc)}. On the other hand, {a mathematical formula}JG(P) has the single topological ordering {a mathematical formula}≤=({e},{c},{a,b},{d}), and {a mathematical formula}SEQS≤(P)={(bc,abc)}; hence {a mathematical formula}MMJC(P)={(bc,abc)}. Note that {a mathematical formula}SEQ(P)={(bc,abc), {a mathematical formula}(d,de)}.
      </paragraph>
      <paragraph>
       The problem in Section 6.2 disappears when we use the MJCs.
      </paragraph>
      <paragraph label="Example 43">
       continuedFor {a mathematical formula}P={b;←b,nota} in Example 32, the graph {a mathematical formula}JG(P) has the single node {a mathematical formula}{a,b} and {a mathematical formula}SEQS(P)={(b,ab)} for {a mathematical formula}S={a,b}. Thus the single {a mathematical formula}MJC-model of P is {a mathematical formula}(b,ab), as desired.
      </paragraph>
      <paragraph label="Example 44">
       continuedFor the company program P in Example 24, the join graph {a mathematical formula}JG(P) has the edges ({a mathematical formula}{e(sam),h(sam),c(sam)}, {a mathematical formula}{m(sam)}) and ({a mathematical formula}{e(sam),h(sam),c(sam)}, {a mathematical formula}{s(sam)}). Thus two {a mathematical formula}MJC-split sequences are possible, viz. {a mathematical formula}S=(S1,S2,S3) where {a mathematical formula}S1={m(sam)}, {a mathematical formula}S2={m(sam), {a mathematical formula}s(sam)}, and {a mathematical formula}S3={m(sam), {a mathematical formula}s(sam), {a mathematical formula}e(sam), {a mathematical formula}h(sam), {a mathematical formula}c(sam)}; and {a mathematical formula}S′=(S1′,S2′,S3′) where {a mathematical formula}S1′={s(sam)}, and {a mathematical formula}S2′=S2, and {a mathematical formula}S3′=S3. Both {a mathematical formula}SEQS(P) and {a mathematical formula}SEQS′(P) have the single {a mathematical formula}SEQ-model {a mathematical formula}Iκ={m(sam), {a mathematical formula}e(sam), {a mathematical formula}c(sam), {a mathematical formula}Kh(sam)}, which is then the single {a mathematical formula}MJC-model of P.
      </paragraph>
      <paragraph>
       Note that trivially, the {a mathematical formula}MJC- and the {a mathematical formula}SCC-semantics coincide for constraint-free programs (in fact, also in absence of cross-constraints). As for the properties (D1)–(D3), again from Proposition 16 we obtain:
      </paragraph>
      <paragraph label="Corollary 9">
       The{a mathematical formula}MJC-models semantics, given by{a mathematical formula}MMJC(P)for any program P, satisfies (D1)–(D2), and if P is cross-constraint-free, also (D3).
      </paragraph>
      <paragraph>
       Program coherence (D3) is not ensured by {a mathematical formula}MJC-models, due to lean component merging that fully preserves dependencies. To obtain a {a mathematical formula}SEQ-model, blurring strict dependencies can be necessary, where two aspects need to be taken into account.
      </paragraph>
      <paragraph label="Example 45">
       (A1) Inconsistency may still emerge from cross-constraints. Consider the program {a mathematical formula}P={←b,nota;b;b←a}. It has the SCCs {a mathematical formula}{a} and {a mathematical formula}{b}; as they are not joinable, {a mathematical formula}MJC(P)={{b},{a}}. The single {a mathematical formula}MJC-splitting sequence is {a mathematical formula}({a},{a,b}), which however does not admit a split {a mathematical formula}SEQ-model; consequently, P has no {a mathematical formula}MJC model. This can be remedied by suitably merging components that intersect the same constraint.
      </paragraph>
      <paragraph>
       (A2) A second, orthogonal aspect is dependence.
      </paragraph>
      <paragraph label="Example 46">
       The program {a mathematical formula}P={←b;b←nota} has no {a mathematical formula}MJC-model, as the {a mathematical formula}MJC-splitting sequence {a mathematical formula}S=({a},{a,b}) admits no split {a mathematical formula}SEQ-model; the culprit is a, which does not occur in the constraint.
      </paragraph>
      <paragraph>
       Clearly, the problem extends to dependence via an (arbitrarily long) chain of rules; e.g. change in Example 46 the rule {a mathematical formula}b←nota to {a mathematical formula}b←c1, {a mathematical formula}c1←c2, …, {a mathematical formula}cn−1←cn, {a mathematical formula}cn←nota. Again, this can be remedied by merging components. Many merging policies to ensure (D3) are conceivable; however, such a policy should ideally not dismiss structure unless needed, and it should be efficiently computable; we defer a discussion to Section 8, as the complexity results in the next section will provide useful insight for it.
      </paragraph>
      <section label="6.2.1">
       Modularity of {a mathematical formula}MJC-models
       <paragraph>
        A naive generalization of the modularity property of {a mathematical formula}SCC-models in Theorem 7 fails, as it does not hold for arbitrary splitting sets. To wit, for {a mathematical formula}P={b;←b,nota} and the splitting set {a mathematical formula}S={a}, the modular computation (similar as in the right hand side of (12)) yields no models, while {a mathematical formula}MMJC(P)={(b,ba)}. However, if we properly restrict S, then the generalization holds.
       </paragraph>
       <paragraph label="Proposition 19">
        Let S be a splitting set of a program P such that{a mathematical formula}S=⋃Mfor some{a mathematical formula}M⊆MJC(P). Then{a mathematical formula} Thus, the same evaluation strategy as for {a mathematical formula}SCC-models can be applied. Furthermore, we have an analogue to Proposition 18. We say that a split-sequence {a mathematical formula}S=(S1,…,Sn) of a program P is {a mathematical formula}MJC-compatible, if for every {a mathematical formula}J∈MJC(P) and {a mathematical formula}1≤i≤n, either {a mathematical formula}J⊆Si or {a mathematical formula}J∩Si=∅ holds; intuitively, no maximal joint component of P is split across different layers of S. Then, Let S be an{a mathematical formula}MJC-compatible splitting sequence of a program P. Then{a mathematical formula}where{a mathematical formula}MSQ(P)is the set of all{a mathematical formula}MJC-compatible splitting sequences of P.
       </paragraph>
      </section>
     </section>
     <section label="6.3">
      <section-title>
       Summary of model relationships
      </section-title>
      <paragraph>
       At the end of this section, we summarize the relationships between the various semantics introduced in this paper. Fig. 1 shows the inclusion relation between different notions of models, viewed as HT-models respectively bi-models. Notably all inclusions collapse if the program has equilibrium models ({a mathematical formula}EQ(P)≠∅); otherwise, the semi-stable ({a mathematical formula}SST) models are in general incomparable to the semi-equilibrium {a mathematical formula}(SEQ) models and any of its refinements, as can be seen e.g. from Example 22. The {a mathematical formula}SCC-models are only defined for programs without cross-constraints; each of them is a split {a mathematical formula}SEQ-model with respect to an arbitrary splitting sequence; in fact, the {a mathematical formula}SCC-models are exactly the HT-models which are split models under every splitting sequence. Furthermore, they coincide with the {a mathematical formula}MJC-models, which for programs with cross-constraints may not all be split {a mathematical formula}SEQ-models with respect to an arbitrary splitting sequence. However, the inclusion holds for {a mathematical formula}MJC-compatible splitting sequences (dashed symbol), and the {a mathematical formula}MJC-models are exactly the HT-models which are split models under every {a mathematical formula}MJC-compatible splitting sequence.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Complexity and computation
     </section-title>
     <paragraph>
      In this section, we turn to the computational complexity of the paracoherent model semantics that we have considered in the previous sections. In this, we deal with the {a mathematical formula}SEQ-model and the split {a mathematical formula}SEQ-model semantics in detail, while we treat the {a mathematical formula}SST-model semantics more in passing; the reason is that the complexity of {a mathematical formula}SST-model semantics has been elucidated in more detail in [17], while the {a mathematical formula}SEQ-model semantics has been only briefly considered there.
     </paragraph>
     <paragraph>
      Regarding {a mathematical formula}SEQ-model semantics, we study the following major reasoning tasks: (MCH)Given a program P and an HT-interpretation {a mathematical formula}(X,Y), decide whether {a mathematical formula}(X,Y)∈SEQ(P).(INF)Given a program P, an atom a and {a mathematical formula}v∈{t,f,bt}, decide whether a is a brave [resp. cautious] {a mathematical formula}SEQ-consequence of P with value v, denoted {a mathematical formula}P⊨SEQb,va [resp. {a mathematical formula}P⊨SEQc,va], i.e., a has value v in some (every) {a mathematical formula}(X,Y)∈SEQ(P) value v.(COH)Given a program P, decide whether {a mathematical formula}SEQ(P)≠∅.
     </paragraph>
     <paragraph>
      The generalizations of these problems to split {a mathematical formula}SEQ-semantics, where in addition a split sequence S is part of the input and {a mathematical formula}SEQ is replaced with {a mathematical formula}SEQS, are denoted with MCH-S, INF-S, and COH-S, respectively. We consider all problems for several classes of programs, viz. normal, disjunctive, stratified, and headcycle-free programs{sup:11} and the split {a mathematical formula}SEQ-models problems also for {a mathematical formula}SCC- and {a mathematical formula}MJC-splitting sequences S.
     </paragraph>
     <paragraph>
      The attentive reader might ask why positive programs are not considered here; they are of less interest, as the (split sequence) {a mathematical formula}SEQ-models coincide with the minimal models of P (see Corollary 2, Corollary 4). Furthermore, we note that hcf-programs are under {a mathematical formula}SEQ-semantics sensitive to body shifts; e.g., {a mathematical formula}P={a∨b;a←nota;b←notb} has the {a mathematical formula}SEQ-models {a mathematical formula}(a,ab) and {a mathematical formula}(b,ab), while its shift {a mathematical formula}P→={a←notb;b←nota;a←nota;b←notb} has the single {a mathematical formula}SEQ-model {a mathematical formula}(∅,ab). Thus results for hcf-programs do not immediately carry over to normal program.
     </paragraph>
     <section label="7.1">
      <section-title>
       Overview of complexity results
      </section-title>
      <paragraph>
       Our complexity results are summarized in Table 1, Table 2. They show that {a mathematical formula}SEQ-model semantics is with respect to model checking (MCH) and inference (INF) one level higher up in the polynomial hierarchy than the {a mathematical formula}EQ-model (i.e., answer set) semantics; this is not surprising as the characterization of a {a mathematical formula}SEQ-model in Theorem 2 involves besides h-minimality also gap-minimality, while the {a mathematical formula}EQ-model definition involves only h-minimality. As gap-minimality is a global property and has to be checked across all h-minimal HT-models of a program, intuitively an (additional) quantifier is needed to express that no h-minimal HT-model with smaller gap exists; in particular, this causes {a mathematical formula}SEQ-model checking for normal programs to become intractable. The additional quantifier is then also needed for brave and cautious reasoning, where we need to find a suitable {a mathematical formula}SEQ-model that establishes respectively refutes the query atom, with one exception (this will be discussed below). For the coherence problem, however, the complexity is different compared to the {a mathematical formula}EQ-models semantics as it resorts to classical coherence, and thus to SAT; for some programs it is lower (e.g., for programs without constraints, where {a mathematical formula}EQ-model existence is NP-complete resp. {a mathematical formula}Σ2p-complete, while COH is polynomial), while for others it is higher (e.g., for normal stratified programs with constraints COH is NP-complete, while {a mathematical formula}EQ-model existence is polynomial).
      </paragraph>
      <paragraph>
       The results in Table 2 show that split {a mathematical formula}SEQ-models have the same complexity as {a mathematical formula}SEQ-models (i.e., structural information does not affect complexity) except on Problem COH, which is harder. Problems MCH and INF do not become harder, as MCH reduces to polynomially many MCH instances without splitting; the hardness results for arbitrary splitting sequences are inherited from respective results without splitting.
      </paragraph>
      <paragraph>
       The reason for the complexity increase of COH is that coherence (D3) no longer holds for split {a mathematical formula}SEQ-model semantics. In particular, this means that imposing a structural condition on building {a mathematical formula}SEQ-models along SCCs may eliminate such models. The increase in complexity has a further important implication. Namely, that under usual complexity hypotheses, no polynomial-time method μ exists that associates with P a splitting sequence {a mathematical formula}S=μ(P), using a polynomial-time checkable criterion on P, such that (i) μ respects structure and does not become trivial, i.e., {a mathematical formula}μ(P)≠(At(P)) if {a mathematical formula}SEQS(P)≠∅ for some {a mathematical formula}S≠(At(P)), and (ii) μ preserves coherence, i.e., {a mathematical formula}SEQ(P)≠∅ implies {a mathematical formula}SEQS(P)≠∅. This negative result holds even if the method μ is allowed to be nondeterministic, i.e., can for example “guess” a suitable splitting sequence S for P. In other words, the price for ensuring coherence of a splitting sequence with tractable (or NP) effort is to merge sometimes more components than necessary.
      </paragraph>
      <paragraph>
       For {a mathematical formula}SCC and {a mathematical formula}MJC splitting sequences, we obtain analogous results; informally, the problems do not get easier as splitting (which is a purely syntactic notion) can be blocked by irrelevant rules.
      </paragraph>
      <section label="7.1.1">
       <section-title>
        Semi-stable models
       </section-title>
       <paragraph>
        For semi-stable models, similar results hold as for {a mathematical formula}SEQ-models in Table 1. The reason is that model checking for semi-stable models amounts, by the characterization of Theorem 1, to a test that is similar to the one for {a mathematical formula}SEQ-models according to Theorem 2: testing {a mathematical formula}(I,J)⊨βP is like testing {a mathematical formula}(I,J)⊨P feasible in polynomial time, and the conditions (i) and (ii) are analog to the conditions {a mathematical formula}(i′) and {a mathematical formula}(ii′). Similar arguments as for {a mathematical formula}SEQ-models establish then the membership results for {a mathematical formula}SST-models. The matching hardness results are derived, however, using different reductions, which can be found in [17]. Noticeably, the proofs there establish hardness also under the restrictions to hcf, stratified normal, and disjunctive stratified programs; for hcf-programs, membership of model checking in coNP follows from the fact that deciding item (i) in Theorem 1 is feasible in polynomial time: as easily seen, this test amounts to deciding whether {a mathematical formula}I∈MM(PJ); as {a mathematical formula}PJ is hcf and minimal model checking for hcf programs is polynomial [8], the tractability follows.
       </paragraph>
      </section>
     </section>
     <section label="7.2">
      <section-title>
       Derivation of the results
      </section-title>
      <paragraph>
       In the following, we formally state and derive the results in Table 1, Table 2. Rather than going into tiring technical details, we shall confine in the membership parts to the essential points and describe in the hardness parts the constructed programs without proving the correctness in each case, which is routine.
      </paragraph>
      <paragraph>
       We exploit that in most cases the split-variant Π-S of a problem Π features its full complexity already for the trivial split sequence {a mathematical formula}S=(At(P)); thus Π-S and Π have the same complexity.
      </paragraph>
      <paragraph label="Theorem 10">
       Given a program P, a splitting sequence S and an HT-interpretation{a mathematical formula}(X,Y)recognizing if{a mathematical formula}(X,Y)∈SEQS(P)is
      </paragraph>
      <list>
       <list-item>
        coNP-complete for each of normal, stratified, and headcycle free P, and
       </list-item>
       <list-item>
        {a mathematical formula}Π2p-complete for disjunctive and stratified disjunctive P.
       </list-item>
      </list>
      <paragraph label="Proof">
       The membership parts for MCH can be derived as follows. Given an HT-interpretation {a mathematical formula}(X,Y) of a program P, we can verify by Theorem 2 whether it is a {a mathematical formula}SEQ-model of P by checking that {a mathematical formula}(X,Y)⊨P, which obviously is feasible in polynomial time, and proving h-minimality (item {a mathematical formula}(i′)) and gap-minimality (item {a mathematical formula}(ii′)) of {a mathematical formula}(X,Y); as for {a mathematical formula}(i′), a guess for a HT-model {a mathematical formula}(X′,Y) of P such that {a mathematical formula}X′⊂X can be verified in polynomial time; thus h-minimality can be tested in coNP. Condition {a mathematical formula}(ii′) on top can be decided using an oracle for {a mathematical formula}Π2p that no h-minimal model {a mathematical formula}(X′,Y′) with {a mathematical formula}gap(X′,Y′)⊂gap(X,Y) exists; this establishes membership in {a mathematical formula}Π2p. In case that P is hcf or normal, deciding h-minimality is polynomial, since {a mathematical formula}(i′) amounts to {a mathematical formula}X∈MM(PY); if P is hcf then also {a mathematical formula}PY is hcf, and minimal model checking for such programs is polynomial [8]; if P is normal, then {a mathematical formula}PY is Horn and minimal model checking is well-known to be polynomial.As for split {a mathematical formula}SEQ-models, by Theorem 5 deciding whether {a mathematical formula}(X,Y) is a {a mathematical formula}SEQ-model of P w.r.t. {a mathematical formula}S=(S1,…,Sn) reduces to checking whether {a mathematical formula}(X,Y) and all {a mathematical formula}(X,Y)|Sk are {a mathematical formula}SEQ-models of P resp. {a mathematical formula}bSk(Pk−1), for {a mathematical formula}k=1,…,n. Each program {a mathematical formula}bSk(Pk−1) is normal (stratified normal, hcf, stratified disjunctive) if P has this property. Hence the already established membership results for {a mathematical formula}SEQ-models generalize to the case of splitting sequences.The matching hardness results for item (ii) and {a mathematical formula}SEQ-models are proved in Appendix C.1; for stratified normal programs, which covers also normal and hfc-programs, we give a simple reduction from minimal model checking of positive programs P (which is well-known to be coNP-complete, cf. [16]). For any rule r, let {a mathematical formula}cs(r) be its constraint rewriting, i.e., {a mathematical formula}cs(r)=←B+(r),notB−(r),notH(r), and let {a mathematical formula}cs(P)={cs(r)|r∈P}. Then {a mathematical formula}M∈MM(P) iff {a mathematical formula}(∅,M)∈SEQ(cs(P)). All hardness results trivially extend to arbitrary splitting sequences, which establishes the result.  □
      </paragraph>
      <paragraph label="Theorem 11">
       Given a program P, a splitting sequence S, an atom a and a value{a mathematical formula}v∈{t,f,bt}, deciding whether
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}P⊨SEQSb,vais{a mathematical formula}Σ2p-complete for each of normal, stratified normal, and hcf P and{a mathematical formula}Σ3p-complete for disjunctive and stratified disjunctive P;
       </list-item>
       <list-item>
        {a mathematical formula}P⊨SEQSc,vais{a mathematical formula}Π2p-complete for each of normal, normal stratified, and hcf P and{a mathematical formula}Π3p-complete for disjunctive and stratified disjunctive P.
       </list-item>
      </list>
      <paragraph label="Proof">
       Membership of brave (resp. cautious) reasoning from {a mathematical formula}SEQ-models w.r.t. S in {a mathematical formula}Σ3p (resp. {a mathematical formula}Π3p) for disjunctive programs follows from Theorem 10, and similarly membership for normal, normal stratified and hcf-programs in {a mathematical formula}Σ2p [resp. {a mathematical formula}Π2p]. The {a mathematical formula}Σ3p/{a mathematical formula}Π3p-hardness for brave [resp. cautious] reasoning from {a mathematical formula}SEQ-models from stratified disjunctive programs is proven in Appendix C.1 resp. Appendix C.2. The {a mathematical formula}Σ2p/{a mathematical formula}Π2p-hardness for stratified normal programs (and thus for normal and hcf-programs) follows by a reduction from brave (resp. cautious) reasoning from positive disjunctive programs P, which is {a mathematical formula}Σ2p- resp. {a mathematical formula}Π2p-hard (see Appendix C.1). For every such P and atom a, we have that {a mathematical formula}a∈M for some {a mathematical formula}M∈MM(P) iff {a mathematical formula}cs(P)⊨Sb,bta (resp. {a mathematical formula}P⊨cfa iff {a mathematical formula}cs(P)⊨SEQc,fa); indeed, the {a mathematical formula}SEQ-models of P and {a mathematical formula}cs(P) are the HT-models {a mathematical formula}(M,M) resp. {a mathematical formula}(∅,M), where {a mathematical formula}M∈MM(P).  □
      </paragraph>
      <paragraph>
       Notably brave reasoning has the same complexity in all cases, if we fix the truth value v arbitrarily, already for {a mathematical formula}S=At(P) (i.e., for {a mathematical formula}SEQ-models). For cautious reasoning, this similarly holds, except that for {a mathematical formula}v=bt and {a mathematical formula}S=At(P), the complexity drops to coNP resp. {a mathematical formula}Π2P (see Appendix C.2).
      </paragraph>
      <paragraph label="Theorem 12">
       Given a program P and a splitting sequence S, deciding whether{a mathematical formula}SEQS(P)≠∅is
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}Σ2p-complete for each of normal, stratified normal, and hcf P; and
       </list-item>
       <list-item>
        {a mathematical formula}Σ3p-complete for stratified disjunctive and disjunctive P; and
       </list-item>
       <list-item>
        NP-complete for all program classes considered, if{a mathematical formula}S=(Σ)(i.e., for{a mathematical formula}SEQin place of{a mathematical formula}SEQS).
       </list-item>
      </list>
      <paragraph label="Proof">
       The membership parts of (i) and (ii) follow easily from the results for MCH in Theorem 10, as a candidate {a mathematical formula}SEQ-model of P w.r.t. S can be guessed and checked with an NP resp. {a mathematical formula}Σ2p oracle in polynomial time. The hardness parts of (i) and (ii) can be obtained via a reduction from brave reasoning {a mathematical formula}P⊨bva in Problem INF. The {a mathematical formula}Σ3p-hard (resp. {a mathematical formula}Σ2p-hard) instances are of a form such that {a mathematical formula}P⊨bva iff some {a mathematical formula}SEQ-model {a mathematical formula}(X,Y) of P exists with {a mathematical formula}a∈Y. Let b be a fresh atom and define then {a mathematical formula}P′=P∪{←b;b←nota}. Then {a mathematical formula}P′ has a {a mathematical formula}SEQ-model w.r.t. {a mathematical formula}S=(At(P),At(P′)) iff {a mathematical formula}P⊨bva; this proves the {a mathematical formula}Σ3p- (resp. {a mathematical formula}Σ2p-) hardness.The result in (iii) is an immediate consequence of the NP-completeness of SAT (satisfiability of a clause set) in propositional logic and the classical coherence property (D3) of {a mathematical formula}SEQ-model semantics.  □
      </paragraph>
      <paragraph>
       Canonical split{a mathematical formula}SEQ-semantics. For {a mathematical formula}SCC- and {a mathematical formula}MJC-splitting sequences, we have
      </paragraph>
      <paragraph label="Theorem 13">
       The results on Problems MCH, INF and COH inTable 2continue to hold if S is restricted to{a mathematical formula}SCC- (resp.{a mathematical formula}MJC-) splitting sequences.
      </paragraph>
      <paragraph label="Proof">
       Indeed, the respective hardness proofs are extended to this setting. For a program P, let p be a fresh atom and let {a mathematical formula}Pcl=P∪{a←a,p;p←p,a|a∈Σ}. Clearly, P and {a mathematical formula}Pcl have the same {a mathematical formula}SEQ-models, and {a mathematical formula}Pcl has the single {a mathematical formula}SCC{a mathematical formula}Σ′=Σ∪{p}. Exploiting this, the programs for MCH and INF have the single splitting sequence {a mathematical formula}S=(Σ′) and those for Problem COH have {a mathematical formula}S′=(Σ′,Σ′∪{b}); these are {a mathematical formula}SCC- and {a mathematical formula}MJC-splitting sequences. Furthermore, from {a mathematical formula}S′ we conclude that no method μ as in Subsection 7.1 exists (under usual complexity hypotheses).  □
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Constructing and recognizing canonical splitting sequences
      </section-title>
      <paragraph>
       It is well-known that {a mathematical formula}SCC(P) and {a mathematical formula}SG(P) are efficiently computable from P (using Tarjan's [53] algorithm even in linear time); hence, it is not hard to see that one can recognize a {a mathematical formula}SCC-splitting sequence S in polynomial time, and that every such S can be (nondeterministically) generated in polynomial time (in fact, in linear time). We obtain similar tractability results for {a mathematical formula}MJC(P) and {a mathematical formula}MJC-splitting sequences. To this end, we first note the following useful proposition.
      </paragraph>
      <paragraph label="Proposition 20">
       Let P be a program and let{a mathematical formula}K1,K2∈SCC(P). Then{a mathematical formula}K1and{a mathematical formula}K2satisfy (i) and (ii) ofDefinition 12iff they are disconnected in{a mathematical formula}SG(P), i.e., no path from{a mathematical formula}K1to{a mathematical formula}K2and vice versa exists.
      </paragraph>
      <paragraph>
       Based on this proposition, we can characterize the joinable pairs that are witnessed by a constraint from r as follows. As usual, let us call a SCC {a mathematical formula}Ci in a set {a mathematical formula}C⊆SCC(P) of SCCs maximal, if no {a mathematical formula}Cj in {a mathematical formula}C exists that is comparable to {a mathematical formula}Ci in {a mathematical formula}SG(P) and ordered after {a mathematical formula}Ci, i.e., every topological ordering of {a mathematical formula}SG(P) is of the form {a mathematical formula}(…,Cj,…,Ci,…).
      </paragraph>
      <paragraph label="Corollary 10">
       Given a constraint{a mathematical formula}r∈P, let{a mathematical formula}C1,…,Clbe the maximal SCCs C of P in{a mathematical formula}SG(P)such that{a mathematical formula}At(r)∩C≠∅. Then{a mathematical formula}(K1,K2)where{a mathematical formula}K1≠K2is a joinable pair of P witnessed by r (i.e., satisfies (iii) for r) iff{a mathematical formula}K1,K2∈{C1,…,Cl}.
      </paragraph>
      <paragraph>
       By exploiting this characterization, we can construct {a mathematical formula}MJC(P) and furthermore {a mathematical formula}JG(P) by the following steps:
      </paragraph>
      <list>
       <list-item label="1.">
        compute {a mathematical formula}DG(P), {a mathematical formula}SCC(P) and {a mathematical formula}SG(P);
       </list-item>
       <list-item label="2.">
        for every constraint {a mathematical formula}r∈P, determine all maximal {a mathematical formula}C1r,…,Clr in {a mathematical formula}SCC(P) such that {a mathematical formula}Cir∩At(r)≠∅;
       </list-item>
       <list-item label="3.">
        let {a mathematical formula}Cr=C1r∪⋯∪Clr, and set {a mathematical formula}MC:={Cr|r∈P,H(r)=∅} and {a mathematical formula}NMI:=SCC(P)∖{C1r,…,Clr|r∈P,H(r)=∅};
       </list-item>
       <list-item label="4.">
        merge {a mathematical formula}J1,J2∈MC such that {a mathematical formula}J1∩J2≠∅ (i.e., set {a mathematical formula}MC:=(MC∖{J1,J2})∪{J1∪J2}) until no longer possible;
       </list-item>
       <list-item label="5.">
        set {a mathematical formula}MJC(P):=MC∪NMI and {a mathematical formula}JG(P)=(VJG,EJG) where {a mathematical formula}VJG=MJC(P) and {a mathematical formula}EJG={(J1,J2)|J1≠J2∈MJC(P),∃a∈J1,∃b∈J2,(a,b)∈EDG}.
       </list-item>
      </list>
      <paragraph label="Example 47">
       Reconsider the program P from Example 37, which contains the constraints {a mathematical formula}r1:←b,nota and {a mathematical formula}r2:←b,notc. We recall that {a mathematical formula}SCC(P)={{a},{b}, {a mathematical formula}{c},{d},{e}}. In Step 2 of the procedure, the maximal SCCs of {a mathematical formula}r1 are {a mathematical formula}{a},{b} and the single maximal one of {a mathematical formula}r2 is {a mathematical formula}{b}; thus in Step 3, we have {a mathematical formula}MC={{a,b},{b}} and {a mathematical formula}NMI={{c},{d},{e}}. In Step 4, {a mathematical formula}{a,b} and {a mathematical formula}{b} are merged, resulting in {a mathematical formula}MC={{a,b}}. Finally, in Step 5 {a mathematical formula}MJC(P) is assigned {a mathematical formula}MC∪NMI={{a,b},{c},{d},{e}}; this is the correct result.
      </paragraph>
      <paragraph>
       The following result states the correctness of the procedure and that it can be implemented to run in bilinear time.
      </paragraph>
      <paragraph label="Theorem 14">
       Given a program P,{a mathematical formula}MJC(P)and{a mathematical formula}JG(P)are computable in time{a mathematical formula}O(cs⋅‖P‖), where{a mathematical formula}cs=|{r∈P|H(r)=∅}|is the number of constraints in P and{a mathematical formula}‖P‖is the size of P.
      </paragraph>
      <paragraph>
       In particular, the algorithm runs in linear time if the number of constraints is bounded by a constant. It remains as an interesting open issue whether the same time bound is feasible without this constraint.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section, we first review some general principles for logic programs with negation, and we then consider the relationship of semi-stable and semi-equilibrium semantics to other semantics of logic programs with negation. Finally, we address some possible extensions of our work.
     </paragraph>
     <section label="8.1">
      <section-title>
       General principles
      </section-title>
      <paragraph>
       In the context of logic programs with negation, several principles have been identified which a semantics desirably should satisfy. Among them are:
      </paragraph>
      <list>
       <list-item label="•">
        the principle of minimal undefinedness[59], which says that a smallest set of atoms should be undefined (i.e., neither true nor false);
       </list-item>
       <list-item label="•">
        the principle of justifiability (or foundedness)[59]: every atom which is true must be derived from the rules of the program, possibly using negative literals as additional axioms;
       </list-item>
       <list-item label="•">
        the principle of the closed world assumption (CWA), for models of disjunctive logic programs (Eiter et al. [19]): “If every rule with an atom a in the head has a false body, or its head contains a true atom distinct from a w.r.t. an acceptable model, then a must be false in that model.”
       </list-item>
      </list>
      <paragraph>
       It can be shown that both the semi-stable and the semi-equilibrium semantics satisfy the first two principles (properly rephrased and viewing bt as undefined), but not the CWA principle; this is shown by the simple program {a mathematical formula}P={a←nota} and the acceptable model {a mathematical formula}{Ka}. However, this is due to the particular feature of making, as in this example, assumptions about the truth of atoms; if the CWA condition is restricted to atoms a that are not believed by assumption, i.e., {a mathematical formula}Iκ(a)≠bt in a semi-stable resp. semi-equilibrium model {a mathematical formula}Iκ, then the CWA property holds.
      </paragraph>
      <paragraph>
       We eventually remark that Property N can be enforced on semi-stable models by adding constraints {a mathematical formula}←a,nota for all atoms a to the (original) program. However, enforcing Property K on semi-stable models is more involved and efficient encodings seem to require an extended signature.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Related semantics
      </section-title>
      <paragraph>
       In this section, we relate the semi-stable and semi-equilibrium semantics to several semantics in the literature that allow for models even if a no answer set of a program exists.
      </paragraph>
      <section label="8.2.1">
       <section-title>
        Evidential stable models
       </section-title>
       <paragraph>
        Motivated by the fact that a disjunctive deductive database (DDDB) may lack stable models or even P-stable models, Seipel [51] presented a paracoherent semantics, called the evidential stable model (ESM) semantics, which assigns some model to every DDDB (that is, to every constraint-free disjunctive logic program), such that the properties (D1)–(D3) in the Introduction are satisfied. Similar to [49], but guided by slightly different intuition, he defined the evidential stable models of a program P in a two-step process. First P is transformed into a positive disjunctive program {a mathematical formula}PE, called the evidential transform of P, whose answer sets, i.e., its minimal models are considered. Among them are in the second step those selected that are informally preferred according to the amount of reasoning by contradiction that they involve. While Seipel did not consider constraints, his approach naturally extends to programs with constraints, and we consider this extension in the sequel.
       </paragraph>
       <paragraph>
        Formally, for a given Σ let {a mathematical formula}ΣE=Σ∪{Ea|a∈Σ}, where {a mathematical formula}Ea intuitively means that there is evidence that a is true. Given a program P, its evidential transformation {a mathematical formula}PE consists of the following rules:
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}H(r)∪EB−(r)←B+(r) and
        </list-item>
        <list-item label="2.">
         {a mathematical formula}EH(r)∪EB−(r)←EB+(r), for each rule {a mathematical formula}r∈P of form (1), and
        </list-item>
        <list-item label="3.">
         {a mathematical formula}Ea←a, for each {a mathematical formula}a∈Σ,
        </list-item>
       </list>
       <paragraph>
        where for every set {a mathematical formula}S⊆Σ of atoms, {a mathematical formula}ES={Ea|a∈S}. Intuitively, the rules in (2) and (3) correspond to the rules that are added to Sakama and Inoue's program {a mathematical formula}Pκ in the epistemic transformation to ensure the Properties N and K (see Definition 6); the rules in (2), however, are quite different from {a mathematical formula}Pκ. They intuitively infer evidence for the truth of some atom {a mathematical formula}bj under negation ({a mathematical formula}m&lt;j≤n) from the violation of the positive part of the rule (i.e., if all {a mathematical formula}bj, {a mathematical formula}1≤j≤m are true and no {a mathematical formula}ai, {a mathematical formula}1≤i≤l is true).
       </paragraph>
       <paragraph>
        An interpretation I over {a mathematical formula}ΣE is an evidential stable model, if (1) I is a minimal model of {a mathematical formula}PE, and (2) I has among all minimal models of {a mathematical formula}PE a ⊆-minimal {a mathematical formula}E-violation set {a mathematical formula}VE(I), which is defined as {a mathematical formula}V(I)={a∈Σ|Ea∈I,a∉I}.
       </paragraph>
       <paragraph>
        Now the following can be shown. For every bi-interpretation {a mathematical formula}(X,Y) let {a mathematical formula}(X,Y)E=X∪EY, and for every {a mathematical formula}I⊆ΣE, let {a mathematical formula}β(I) be the inverse of {a mathematical formula}⋅E, i.e., {a mathematical formula}β(I)=(X,Y) such that {a mathematical formula}(X,Y)E=I.
       </paragraph>
       <paragraph label="Theorem 15">
        Let P be a program over Σ. Then for every bi-interpretation{a mathematical formula}(X,Y)over Σ, it holds that{a mathematical formula}(X,Y)∈SEQ(P)iff{a mathematical formula}(X,Y)Eis an evidential stable model of P.
       </paragraph>
       <paragraph>
        Thus the {a mathematical formula}SEQ-model semantics coincides with the evidential stable model semantics for disjunctive logic programs. The theorem above gives a characterization of evidential stable models in terms of HT-logic, and in turn we obtain with {a mathematical formula}PE a simpler program to describe the {a mathematical formula}SEQ-models than the epistemic transformation {a mathematical formula}Pκ in Section 4. Note, however, that the program is not a straightforward encoding of the semantic characterization of {a mathematical formula}SEQ-models in Theorem 2; the class of {a mathematical formula}PE-models does not contain all h-minimal HT-models of P, but sufficiently many to single out all the {a mathematical formula}SEQ-models by gap minimization.
       </paragraph>
      </section>
      <section label="8.2.2">
       <section-title>
        CR-Prolog
       </section-title>
       <paragraph>
        In order to deal with inconsistency in answer set programs, Balduccini and Gelfond introduced CR-Prolog [4] as a declarative approach for inconsistency removal from program. Roughly speaking, each program P is equipped with a further set of rules CR of the form{a mathematical formula} where intuitive reading is: if {a mathematical formula}l1,…,lm are accepted beliefs while {a mathematical formula}lm+1,…,ln are not, then one of {a mathematical formula}h1,…,hk “may possibly” be believed. In addition, a preference relation on the rules may be provided.
       </paragraph>
       <paragraph>
        Rules from this pool CR can be added to restore consistency of the program P if no answer set exists, applying Occam's razor. Informally, a subset-minimal set {a mathematical formula}R⊆CR of rules is chosen such that {a mathematical formula}P′=P∪R′ is coherent, where {a mathematical formula}R′ is R cast to the ASP syntax; the answer sets of {a mathematical formula}P′ are then accepted as CR-answer sets of P. Formally, P and CR are compiled into a single abductive logic program where an abducible atom {a mathematical formula}appl(r) is used for the each rule r from CR to control (and be aware of) its applicability; a minimal set of abducibles may be assumed to be true without further justification. For simplicity, however, we use the abstract description from above.
       </paragraph>
       <paragraph>
        The CR-Prolog approach is different from semi-stable and {a mathematical formula}SEQ-model semantics in several respects. First, it provides a (syntactic) inconsistency management strategy, not a semantic treatment of incoherence at the semantic level of interpretations. Second, it remains with the user to ensure coverage of all cases of incoherence; this bears risk that some cases are overlooked. On the other hand, depending on the application it might be preferred that this is pointed out.
       </paragraph>
       <paragraph>
        Even if CR consists of all atoms in P, CR-answer sets and {a mathematical formula}SEQ-models may disagree, as adding facts, as done in this case by CR-Prolog, is stronger than blocking negated atoms as in semi-stable and {a mathematical formula}SEQ-models semantics (which then admits more answer sets).
       </paragraph>
       <paragraph label="Example 48">
        Consider the program {a mathematical formula}P={a←nota;c←notb;b∨c←a}. This program has the unique {a mathematical formula}SEQ-model {a mathematical formula}(c,ac); i.e., c is true, b is false, and a is believed true.Let {a mathematical formula}CR={ra:a←+;rb:b←+;rc:c←+} and assume that there are no preferences. Then {a mathematical formula}R′={ra} is the single minimal subset of CR such that {a mathematical formula}P′=P∪R′ is coherent, and {a mathematical formula}P′={a←nota;c←notb;b∨c←a;a←} has two answer sets, viz. {a mathematical formula}{a,c} and {a mathematical formula}{a,b}, which are then both CR answer sets.
       </paragraph>
       <paragraph>
        The program in the previous example shows that adding a as a fact is stronger than blocking the use of a under negation. We remark that this similarly applies to the generalized stable model semantics [30], in which abducible facts may be added to the program P in order to obtain a stable model.
       </paragraph>
      </section>
      <section label="8.2.3">
       <section-title>
        Well-founded semantics
       </section-title>
       <paragraph>
        The most prominent approximation of the stable semantics is the well-founded semantics (WFS) [56]. It assigns each normal logic program P, in our terminology, an HT-model {a mathematical formula}WF(P)=(I,J) (called the well-founded model) such that all atoms in I are regarded as being true and all atoms not in J being false; all the remaining atoms (i.e., those in {a mathematical formula}gap(WF(P))) are regarded as undefined (rather than possibly true, as in HT-logic). Intuitively, the false atoms are those which can never become true, regardless of how the undefined atoms will be assigned. Extending WFS to disjunctive program is non-trivial and many proposals have been made, but there is no general consensus on the “right” such extension (see [57], [13] for more recent proposals); we comment on the proposal of Cabalar et al. [13] in the subsection on partial stable models below.
       </paragraph>
       <paragraph>
        The well-founded semantics has many different characterizations; among them is the well-known alternating fixpoint-characterization, cf. [55], [5]: for normal constraint-free programs P, the operator {a mathematical formula}γP(X)=LM(PX), {a mathematical formula}X⊆Σ is anti-monotonic, where {a mathematical formula}LM(Q) denotes the unique minimal model of Q (which for {a mathematical formula}Q=PX exists). We then have {a mathematical formula}WF(P)=(I,J) where I is the least fixpoint of the monotonic operator {a mathematical formula}γP2(X)=γP(γP(X)), and {a mathematical formula}J=γP(I). Furthermore, the well-founded model is the least partial stable model (see Section 8.2.4 below); it has been characterized in the logic HT{sup:2} in terms of the partial equilibrium model that leaves the most atoms undefined [14].
       </paragraph>
       <paragraph>
        With regard to Section 8.1, WFS does not satisfy minimal undefinedness, but justifiability and naturally the CWA principle. It does not satisfy answer set coverage (D1) nor congruence (D2) (even if a single answer set exists), but coherence (D3). Roughly speaking, the well-founded model remains agnostic about atoms that are involved in cycles through negation whose truth value cannot be determined from other parts of the program, and it propagates undefinedness. This may effect that all atoms remain undefined; e.g., the program in Example 22 has this property.
       </paragraph>
       <paragraph>
        It is well-known that the well-founded model {a mathematical formula}WF(P)=(I,J) approximates the answer sets of P in the sense that {a mathematical formula}I⊆M⊆J for each answer set M of P; it is thus geared towards approximating cautious inference of literals from all answer sets of P, rather than towards approximating individual answer sets. If no answer set exists, WFS avoids trivialization and still yields a model; however, the notion of undefinedness and the associated propagation may lead to less informative results, as shown in Example 4.
       </paragraph>
       <paragraph>
        {a mathematical formula}SEQ-refinement of the WFS. A closer look at the WFS reveals that the {a mathematical formula}SEQ-model semantics refines it in the following sense.
       </paragraph>
       <paragraph>
        Notation. Let for HT-interpretations {a mathematical formula}M=(X,Y) and {a mathematical formula}M′=(X′,Y′) denote {a mathematical formula}M⊑M′ that {a mathematical formula}X′⊆X and {a mathematical formula}Y⊆Y′, i.e., M is a refinement of {a mathematical formula}M′ that results by assigning atoms in {a mathematical formula}gap(M′) either true of false.{sup:12}
       </paragraph>
       <paragraph>
        Recall that an HT-interpretation {a mathematical formula}(X,Y) of a program P is h-minimal, if no HT-model {a mathematical formula}(X′,Y) exists such that {a mathematical formula}X′⊂X; for normal P, this means that X is the least model of {a mathematical formula}PY.
       </paragraph>
       <paragraph label="Proposition 21">
        Let{a mathematical formula}M=(X,Y)be an h-minimal model of a (constraint-free) normal program P. If{a mathematical formula}gap(M)⊆gap(WF(P)), then{a mathematical formula}M⊑WF(P), i.e., M is a refinement of the well-founded model of P.
       </paragraph>
       <paragraph>
        Note that this proposition is not immediate as we just compare gaps, not models themselves. The result follows from some well-known properties of {a mathematical formula}WF(P) and its relationship to the answer set semantics.
       </paragraph>
       <paragraph>
        First, as already mentioned above, WFS is an approximation of the stable semantics:
       </paragraph>
       <paragraph label="Lemma 2">
        For every equilibrium (stable) model{a mathematical formula}M=(Y,Y)of P, it holds that{a mathematical formula}M⊑WF(P).
       </paragraph>
       <paragraph>
        Furthermore, WF is such that by making yet unassigned atoms true, the values of the already assigned atoms are not affected. That is,
       </paragraph>
       <paragraph label="Lemma 3">
        For every set{a mathematical formula}G⊆gap(WF(P)), it holds that{a mathematical formula}WF(P∪G)⊑WF(P).
       </paragraph>
       <paragraph>
        Intuitively, this is because for each atom a outside {a mathematical formula}gap(WF(P)), a rule already fires resp. all rules are definitely not applicable. Next, h-minimality allows for unsupported atoms (the gap). By making them facts, we get an answer set:
       </paragraph>
       <paragraph label="Lemma 4">
        If{a mathematical formula}M=(X,Y)is a h-minimal model of P, then{a mathematical formula}M′=(Y,Y)is an answer set of{a mathematical formula}P′=P∪gap(M).
       </paragraph>
       <paragraph>
        Indeed, X is the least model of {a mathematical formula}PY, so each atom in X can be derived from {a mathematical formula}PY; by adding {a mathematical formula}gap(M)=Y−X, all atoms of Y can be derived from {a mathematical formula}PY∪gap(M)=P′Y, and clearly no proper subset can be derived.
       </paragraph>
       <paragraph>
        Armed with these lemmas, we now prove the proposition.
       </paragraph>
       <paragraph label="Proof of Proposition 21">
        Let {a mathematical formula}M=(X,Y) be a h-minimal model of P such that {a mathematical formula}gap(M)⊆gap(WF(P)), and let {a mathematical formula}WF(P)=(I,J). By Lemma 4, {a mathematical formula}N=(Y,Y) is an answer set of {a mathematical formula}P′=P∪gap(M). By Lemma 2, {a mathematical formula}N⊑WF(P′), and by Lemma 3, {a mathematical formula}WF(P′)⊑WF(P). As refinement is transitive, we obtain {a mathematical formula}N⊑WF(P); it follows that {a mathematical formula}Y⊆J.Regarding X, by the alternating fixpoint characterization of {a mathematical formula}WF(P) we have {a mathematical formula}I=LM(PJ), and thus {a mathematical formula}WF(P) is a h-minimal model of P; as M is a h-minimal model of P, we have {a mathematical formula}X=LM(PY). As {a mathematical formula}γP(I)=LM(PI) is anti-monotonic and {a mathematical formula}Y⊆J, it follows that {a mathematical formula}X⊇I.Thus, we get {a mathematical formula}M=(X,Y)⊑(I,J)=WF(P). This proves the proposition.  □
       </paragraph>
       <paragraph>
        From this proposition, we obtain a refinement result for arbitrary normal programs, i.e., programs that may contain constraints. For such a program P, we define its well-founded model as {a mathematical formula}WF(P)=WF(P′), where {a mathematical formula}P′ is the constraint-free part of P, if {a mathematical formula}WF(P′)⊨P∖P′; otherwise, {a mathematical formula}WF(P) does not exist. Note that each constraint r in P must have a false body in {a mathematical formula}WF(P), i.e., either some {a mathematical formula}bi∈B+(r) is false in {a mathematical formula}WF(P) or some {a mathematical formula}cj∈B−(r) is true in {a mathematical formula}WF(P) (this can be seen from the alternating fixpoint characterization).
       </paragraph>
       <paragraph label="Corollary 11">
        of Proposition 21Every normal program P such that{a mathematical formula}WF(P)exists has a{a mathematical formula}SEQ-model M such that{a mathematical formula}M⊑WF(P). In fact, every{a mathematical formula}SEQ-model M of P such that{a mathematical formula}gap(M)⊆gap(WF(P))satisfies{a mathematical formula}M⊑WF(P).
       </paragraph>
       <paragraph label="Proof">
        Indeed, {a mathematical formula}SEQ-models are special h-minimal models (global gap-minimization), so the result follows from Proposition 21 and the fact that {a mathematical formula}WF(P)=WF(P′)=(I,J) is h-minimal (as {a mathematical formula}I=LM(PJ)=LM(P′J)), where {a mathematical formula}P′ is the constraint-free part of P.  □
       </paragraph>
       <paragraph>
        Note, however, that not every {a mathematical formula}SEQ-model refines the well-founded model. E.g., take {a mathematical formula}P={a←nota,notb}. Then {a mathematical formula}WF(P)=(∅,{a}) but the {a mathematical formula}SEQ-models are {a mathematical formula}M1=(∅,{a}) and {a mathematical formula}M2=(∅,{b}), and {a mathematical formula}M2 has a gap outside the gap of {a mathematical formula}WF(P).
       </paragraph>
       <paragraph>
        If desired, one can easily restrict the {a mathematical formula}SEQ-models of a program P to those which refine its well-founded model {a mathematical formula}WF(P)=(I,J), by replacing P with{a mathematical formula} Note that {a mathematical formula}WF(Pwf) exists whenever {a mathematical formula}WF(P) exists. We then obtain the following result.
       </paragraph>
       <paragraph label="Proposition 22">
        For every normal program P such that{a mathematical formula}WF(P)exists,{a mathematical formula}SEQ(Pwf)={M∈SEQ(P)|gap(M)⊆gap(WF(P))}.
       </paragraph>
       <paragraph>
        By combining Corollary 11 and Proposition 22, we get a paracoherent way to refine the well-founded semantics for query answering, which coincides with the answer set semantics for coherent programs and provides in general more informative results and reasoning by cases (see Example 4, Example 5).
       </paragraph>
      </section>
      <section label="8.2.4">
       <section-title>
        Partial stable model semantics
       </section-title>
       <paragraph>
        P-stable (partial stable) models, which coincide with the 3-valued stable models of [47], are one of the best known approximation of answer sets. Like the well-founded model, P-stable models can be characterized in several ways (cf. [19]); with respect to equilibrium logic, Cabalar et al. [14] semantically characterized P-stable models in the logic HT{sup:2} in terms of partial equilibrium models. For the concerns of our discussion, we use here a characterization of P-stable models {a mathematical formula}(X,Y) in terms of the multi-valued operator {a mathematical formula}γˆP(X)=MM(PX) as the HT-interpretations {a mathematical formula}(X,Y) such that {a mathematical formula}Y∈γˆP(X) and {a mathematical formula}X∈γˆP(Y); this characterization is easily obtained from [19]. In particular, for normal programs {a mathematical formula}WF(P) is a P-stable model of P (and in fact the least refined such model w.r.t. ⊑), and every answer set M of P (as {a mathematical formula}M=LM(PM)) amounts to a P-stable model {a mathematical formula}(M,M) of P; in this vein, according to Cabalar et al. [13], [14] the well-founded models of a disjunctive program P are the least refined P-stable models M of P (i.e., no P-stable model {a mathematical formula}M′≠M of P exists such that {a mathematical formula}M⊑M′); however, no well-founded model might exist.
       </paragraph>
       <paragraph>
        The P-stable models, while more fine-grained than the well-founded model, behave similarly with regard to the properties in Subsection 8.1 and the properties (D1)–(D3) in the Introduction. Among the refinements of P-stable models in [19], the one that is closest in spirit to semi-stable and {a mathematical formula}SEQ-models are the L-stable models, which are the P-stable models that leave a minimal set of atoms undefined.
       </paragraph>
       <paragraph>
        In fact, L-stable models satisfy all properties in Subsection 8.1 and (D1)–(D3), with the exception that coherence (D3) fails for disjunctive programs, as such programs may lack a P-stable model, and thus also an L-stable model.
       </paragraph>
       <paragraph label="Example 49">
        The program{a mathematical formula} has no P-stable models, while it has multiple {a mathematical formula}SEQ-models, viz. {a mathematical formula}(a,ac), {a mathematical formula}(b,ab), and {a mathematical formula}(c,bc), which coincide with the {a mathematical formula}SST-models. Intuitively, one of the atoms in the disjunctive fact {a mathematical formula}a∨b∨c, say a, must be true; then c must be false and in turn b must be true. The resulting (total) interpretation {a mathematical formula}(ab,ab), however, does not fulfill that {a mathematical formula}{a,b} is a minimal model of {a mathematical formula}P{a,b}={b←;a∨b∨c}. With a symmetric argument for b and c, we conclude that no P-stable model of P exists. However, by adopting in addition that c is believed true, we arrive at the {a mathematical formula}SEQ-model {a mathematical formula}(a,ac).
       </paragraph>
       <paragraph>
        The main difference between that L-stable semantics and semi-stable resp. semi-equilibrium semantics is that the former takes—like P-stable semantics—a neutral position on undefinedness, which in combination with negation may lead to weaker conclusions.
       </paragraph>
       <paragraph>
        For example, the program P in Example 4 has a single P-stable model, and thus P has a single L-stable model which coincides with its well-founded model; thus we cannot conclude under L-stable semantics from P that {a mathematical formula}visits_barber(joe) is false.
       </paragraph>
       <paragraph>
        Also the program in Example 22 has a single P-stable (and L-stable) model in which all atoms are undefined, while c is true under {a mathematical formula}SEQ-model semantics. Similarly, the program{a mathematical formula} has a single P-stable (and thus L-stable) model in which all atoms are undefined; if we add the rules {a mathematical formula}d←a, {a mathematical formula}d←b, and {a mathematical formula}d←c to P, the new program cautiously entails under both semi-stable and {a mathematical formula}SEQ-model semantics that d is true, but not under L-stable semantics.
       </paragraph>
       <paragraph>
        Possible{a mathematical formula}SEQ-refinement of the L-stable semantics. As the {a mathematical formula}SEQ-semantics refines the WFS as shown in Section 8.2.3, the natural question is whether a similar refinement property holds for L-stable models. Unfortunately this is not the case, even for normal programs without constraints (which always possess L-stable models); this is witnessed e.g. by the following example.
       </paragraph>
       <paragraph label="Example 50">
        Consider the program{a mathematical formula} Intuitively, the rules with heads a and b make a guess a or b, if d is true; c must be undefined as there is no other way to derive c than from its negation; d is true if one of a and b is false but not both, i.e., we have a guess for a and b. Thus proper guessing on a and b makes the gap smallest.Under WFS, all atoms must be undefined as each atom occurs in P only on cycles with negation. Furthermore, {a mathematical formula}N1=(ad,acd) and {a mathematical formula}N2=(bd,bcd) are L-stable models, because they are partially stable and no smaller gap than {a mathematical formula}gap(N1)=gap(N2)={c} is possible. There is no further L-stable model (d would need to be true in it, which means that e must be false and hence either a false or b false; thus we end up with {a mathematical formula}N1 or {a mathematical formula}N2), and actually also no other P-stable model.As one can check, {a mathematical formula}M=(e,ec) is a h-minimal model of P, and {a mathematical formula}gap(M)={c}. Thus M is an “additional” h-minimal model of P, and M does neither refine {a mathematical formula}N1 nor {a mathematical formula}N2.If we slightly extend P in (17) to{a mathematical formula} then we get a similar situation. Again, as c only occurs in the head of the rule {a mathematical formula}c←notc, it must be undefined in each partial stable model, and hence the same follows also for {a mathematical formula}c′. Thus we obtain that {a mathematical formula}N1′=(ad,acc′d) and {a mathematical formula}N2′=(bd,bcc′d) are the L-stable models of {a mathematical formula}P′, and they have {a mathematical formula}gap(N1′)=gap(N2′)={c,c′}. On the other hand, M is also an h-minimal model of {a mathematical formula}P′, and {a mathematical formula}gap(M)={c}; thus M is the unique {a mathematical formula}SEQ-model of {a mathematical formula}P′, and the models are unrelated.
       </paragraph>
       <paragraph>
        Possible{a mathematical formula}SEQ-refinement of disjunctive P-stable models. The previous example showed that {a mathematical formula}SEQ-models with smaller gaps than L-stable models do not necessarily refine them. However, as they refine always some P-stable model (the WFM) of a normal program, it does not rule out that they refine some P-stable model of a disjunctive program P, and in particular a well-founded model (i.e., a least refined (w.r.t. ⊑) P-stable model). It appears that this refinement property does not hold.
       </paragraph>
       <paragraph label="Example 51">
        Consider the following variant of the program on line (16) in Example 49:{a mathematical formula} By the disjunctive fact {a mathematical formula}d∨e, either d or e must be true in each h-minimal model (and thus in each P-stable resp. {a mathematical formula}SEQ-model of P). If d is true, then the clauses containing {a mathematical formula}a,b,c, do not admit a P-stable model; if e is true, the single P-stable model is {a mathematical formula}M=(e,abcde). On the other hand, the {a mathematical formula}SEQ-models of P are {a mathematical formula}M1=(ad,acd), {a mathematical formula}M2=(bd,abd), and {a mathematical formula}M3=(cd,bcd); note that each h-minimal model of P in which e is true must have d and some atom from {a mathematical formula}a,b,c believed true but not true, and thus cannot be gap-minimal. As each {a mathematical formula}Mi has smaller gap than M but does not refine it, the refinement property does not hold.
       </paragraph>
       <paragraph>
        Note that the example shows even more: different from normal programs, for disjunctive programs the {a mathematical formula}SEQ-models do not refine the intersection of all P-stable models (i.e., the HT-interpretation {a mathematical formula}(X,Y) where X resp. {a mathematical formula}Σ∖Y is what is true resp. false in every P-stable model of P). Thus in conclusion, for disjunctive programs, P-stable and {a mathematical formula}SEQ-models are in general unrelated.
       </paragraph>
      </section>
      <section label="8.2.5">
       <section-title>
        Further semantics
       </section-title>
       <paragraph>
        The regular model semantics [59] is another 3-valued approximation of answer set semantics that satisfies least undefinedness and foundedness, but not the CWA principle. However, it is classically coherent (satisfies (D3)). For the odd loop program P in (17) the regular models coincide with the L-stable models; the program {a mathematical formula}P′ in (18) has the regular models {a mathematical formula}{a}, {a mathematical formula}{b}, and {a mathematical formula}{c}. While regular models fulfill answer set coverage, they do not fulfill congruence. For more discussion of 3-valued stable and regular models as well as many other semantics coinciding with them, see [19].
       </paragraph>
       <paragraph>
        Revised stable models [43] are a 2-valued approximation of answer sets; negated literals are assumed to be maximally true, where assumptions are revised if they would lead to self-incoherence through odd loops or infinite proof chains. For example, the odd-loop program P in (17) has three revised stable models, viz. {a mathematical formula}{a,b}, {a mathematical formula}{a,c}, and {a mathematical formula}{b,c}. The semantics is only defined for normal logic programs, and fulfills answer set coverage (D1) but not congruence (D2), cf. [43]. Similarly, the so called pstable models in [39], which should not be confused with P-stable models, have a definition for disjunctive programs however, satisfy answer set coverage (D1) (but just for normal programs) and congruence (D2) fails. Moreover, every pstable model of a program is a minimal model of the program, but there are programs, e.g. P in (17) again, that have models but no pstable model, thus classical coherence does not hold.
       </paragraph>
      </section>
     </section>
     <section label="8.3">
      <section-title>
       Modularity
      </section-title>
      <paragraph>
       To our knowledge, modularity aspects of paracoherent semantics have not been studied extensively. A noticeable exception is [19], which studied the applicability of splitting sets for several partial models semantics, among them the P-stable and the L-stable semantics that were already considered above. While for P-stable models a splitting property similar to the one of answer sets holds, this is not the case for L-stable models, due to global gap-minimization however, an analogue to Theorem 7, with L-stable models in place of {a mathematical formula}SCC-models is expected to hold.
      </paragraph>
      <paragraph>
       Huang et al. [28] showed that hybrid knowledge bases, which generalize logic programs, have modular paraconsistent semantics for stratified knowledge bases; however, the semantics aims at dealing with classical contradictions and not with incoherence in terms of instability through cyclic negation.
      </paragraph>
      <paragraph>
       Pereira and Pinto [45], using a layering notion that is similar to SCC-split sequences, introduce layered models (LM) semantics which is an alternative semantics that extends the stable models semantics for normal logic programs. The layered models of a program P are a superset of its answer sets, and this inclusion can be strict even if P is coherent; thus, property (D2) does not hold. In a sense, the CWA is relaxed more than necessary in the model construction process.
      </paragraph>
      <paragraph>
       Faber et al. [20] introduced a notion of modularity for answer set semantics, based on syntactic relevance, which has paracoherent features. However, this notion was geared towards query answering rather than model building, and did not incorporate gap minimization at a semantic level.
      </paragraph>
      <paragraph>
       Finally, we look at models related to a splitting sequence. Not every {a mathematical formula}SEQ-model of P that is a refinement of {a mathematical formula}WF(P) is a {a mathematical formula}SCC-model of P; we might “lose” {a mathematical formula}SEQ-models by splitting. E.g.,{a mathematical formula} has the SCCs {a mathematical formula}C1={a}, {a mathematical formula}C2={b} and {a mathematical formula}C3={c}, and {a mathematical formula}WF(P)=(∅,abc); the single {a mathematical formula}SCC-model of P is {a mathematical formula}M=(∅,ac), while P has a further {a mathematical formula}SEQ-model {a mathematical formula}M′=(∅,ab); the latter is lost along the splitting sequence {a mathematical formula}S=(a,ab,abc), as restricted to {a mathematical formula}C1, M has smaller gap (viz. {a mathematical formula}{a}) than {a mathematical formula}M′ (whose gap is {a mathematical formula}{a,b}). However, we get an analogue to Corollary 11 (recall that normal programs with constraints lack a well-founded model if the constraints are violated).
      </paragraph>
      <paragraph label="Proposition 23">
       Let P be a normal program (possibly containing constraints) such that{a mathematical formula}WF(P)exists and let S be an arbitrary splitting sequence of P. Then P has some{a mathematical formula}SEQS-model M such that{a mathematical formula}M⊑WF(P), and moreover every{a mathematical formula}SEQS-model M of P such that{a mathematical formula}gap(M)⊆gap(WF(P))satisfies{a mathematical formula}M⊑WF(P).
      </paragraph>
      <paragraph>
       The reason is that the well-founded semantics satisfies modularity with respect to splitting sequences. This is a consequence of the following lemma.
      </paragraph>
      <paragraph label="Lemma 5">
       For every splitting set S of a normal program P (possibly containing constraints) such that{a mathematical formula}WF(P)exists, it holds that
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}WF(P)|Sis a partial stable model of{a mathematical formula}bS(P)(recall that{a mathematical formula}|Sdenotes restriction to S), and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}WF(P)=WF(tS(P)∪I∪{A←notA|A∈J∖I}), where{a mathematical formula}WF(bS(P))=(I,J).
       </list-item>
      </list>
      <paragraph>
       This lemma in turn follows from Proposition 12 in [19], which states this property for partial stable models of constraint-free (even disjunctive) programs, and {a mathematical formula}WF(P) is the least partial stable model; note also that constraints in P merely determine the existence of {a mathematical formula}WF(P) but do not influence the truth valuation of atoms.
      </paragraph>
      <paragraph>
       An immediate corollary to Proposition 23 is that normal programs P for which the well-founded model exists and the {a mathematical formula}SCC-model semantics is applicable have some {a mathematical formula}SCC-model that refines the well-founded model {a mathematical formula}WF(P), and moreover that every {a mathematical formula}SCC-model of P which adopts some the undefined atoms in {a mathematical formula}WF(P) as believed true refines {a mathematical formula}WF(P); the same holds for {a mathematical formula}MJC-models.
      </paragraph>
      <paragraph>
       We finally note that we can, as in the case of all {a mathematical formula}SEQ-models of P, restrict the split {a mathematical formula}SEQ-models of P to those which refine {a mathematical formula}WF(P) by adding respective constraints; recall that {a mathematical formula}Pwf=P∪I∪{←A|A∉J} where {a mathematical formula}WF(P)=(I,J).
      </paragraph>
      <paragraph label="Proposition 24">
       Let P be a normal program (possibly containing constraints) such that{a mathematical formula}WF(P)exists. Then for every splitting sequence S of P, it holds that{a mathematical formula}SEQS(Pwf)={M∈SEQS(P)|gap(M)⊆gap(WF(P))}.
      </paragraph>
      <paragraph label="Proof">
       [Sketch] By Proposition 22, {a mathematical formula}SEQ(Pwf)={M∈SEQ(P)|gap(M)⊆gap(WF(P))}. The result can then be shown by induction along the split sequence S, using Theorem 5 and Lemma 5.  □
      </paragraph>
      <paragraph>
       As a consequence of Proposition 23, Proposition 24, in particular the {a mathematical formula}SCC- and {a mathematical formula}MJC-models of a normal program can be easily restricted such that they refine its well-founded semantics in a paracoherent manner, as discussed at the end of Subsection 8.2.3.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Further issues
     </section-title>
     <section label="9.1">
      <section-title>
       Infinite splitting sequences
      </section-title>
      <paragraph>
       As mentioned earlier, we concentrate in this article on finite splitting sequences; however split {a mathematical formula}SEQ-models can be easily extended to infinite splitting sequences {a mathematical formula}S=(S1,S2,…,Si,…). To this end, we can define the split-{a mathematical formula}SEQ models of P relative to a splitting sequence S by {a mathematical formula}SEQS(P)=⋂i≥1∞SEQS[1..i](P), where {a mathematical formula}S[1..i]=(S1,…,Si) is the initial segment of S of length i. Indeed, any extension of the finite sequence {a mathematical formula}S[1..i] by some {a mathematical formula}Si+1 may lead to the loss of {a mathematical formula}SEQ-models; on the other hand, after passing {a mathematical formula}Si, no new model candidates relative to {a mathematical formula}Si will be encountered.
      </paragraph>
     </section>
     <section label="9.2">
      <section-title>
       User-defined subprograms and focusing
      </section-title>
      <paragraph>
       In the previous sections, we were considering the issue of paracoherence at a principled level without further input from the user. Important such input could be, for example, an intended modular structure of the program and/or a focus of attention when looking for a paracoherent model. As we briefly discuss, our notions and results can be easily extended to such settings.
      </paragraph>
      <section label="9.2.1">
       <section-title>
        User-defined subprograms
       </section-title>
       <paragraph>
        In the design of an ASP program, users often proceed by defining (implicitly) subprograms that are composed in a hierarchically manner to a global program. That is, the latter is of the form {a mathematical formula}P=P1∪⋯∪Pm where each {a mathematical formula}Pi is a subprogram that “defines” atoms in a signature {a mathematical formula}Σi, such that {a mathematical formula}Σ=Σ1∪⋯∪Σm, where the {a mathematical formula}Σi are pairwise disjoint, and {a mathematical formula}S=(S1,…,Sm), {a mathematical formula}Si=⋃j≤iΣj, {a mathematical formula}1≤i≤m, is a splitting sequence of P.{sup:13} A particular example are stratified logic programs, where each {a mathematical formula}Pi is meant to define atoms {a mathematical formula}Σi that form the i-th layer.
       </paragraph>
       <paragraph label="Example 52">
        A more elaborated version of the company program in Example 24 could have more complex subprograms that define different categories of workers (core staff, employees), and social security regulations; the current program P just contains single-rule definitions of the concepts. Note that P is stratified, and it is reasonable to expect that more elaborated versions will also have this property.
       </paragraph>
       <paragraph>
        However, the programs {a mathematical formula}Pi may, in general, also include unstratified negation.
       </paragraph>
       <paragraph label="Example 53">
        The barber program in Example 3, extended with a rule {a mathematical formula}shaved(X)←shaves(Y,X) might be a subprogram {a mathematical formula}P1 defining shaved, and {a mathematical formula}P2 a subprogram on top that classifies persons, e.g., with rules{a mathematical formula}
       </paragraph>
       <paragraph label="Example 54">
        As mentioned earlier in Section 5, the program P composed of {a mathematical formula}P1 being the party program in Example 2 and {a mathematical formula}P2={←balcony,#count({X:go(X)})&gt;3;balcony∨living_room} could be used to determine the location for the party. Each of the {a mathematical formula}SEQ-models of the given {a mathematical formula}P1 would be extended to two {a mathematical formula}SEQ-models of P, one with balcony true and one with living_room true, as the constraint is not violated.
       </paragraph>
       <paragraph>
        Exploiting the notions of Section 5, we can readily define the {a mathematical formula}SEQ-models of P, viewing subprograms as atomic blocks, as the {a mathematical formula}SEQS-models of P for the sequence S above. However, if subprograms {a mathematical formula}Pi and {a mathematical formula}Pj are mutually independent, i.e., {a mathematical formula}Σi has empty intersection with each rule body in {a mathematical formula}Pj and vice versa, the order of {a mathematical formula}Pi and {a mathematical formula}Pj may matter for the result. As in the case of SCCs, we can make the semantics robust by requiring that {a mathematical formula}SEQS(P)=SEQSπ(P) for every {a mathematical formula}Sπ=(Sπ(1),…,Sπ(m)) where {a mathematical formula}π(1),π(2),…,π(m) is a permutation of {a mathematical formula}1,…,m, and {a mathematical formula}Sπ(i)=Σπ(1)∪⋯∪Σπ(i), {a mathematical formula}1≤i≤m; then, every constraint-free program P has well-defined subprogram{a mathematical formula}SEQ-models that are induced by {a mathematical formula}{Σ1,…,Σm}. Furthermore, this can be extended to programs P that have no cross-module constraints, i.e., no constraints r that have nonempty intersection with “incomparable”{sup:14}{a mathematical formula}Σi and {a mathematical formula}Σj, and one can define maximal joinable subprograms{a mathematical formula}SEQ-models analogous as for SCCs.
       </paragraph>
       <paragraph>
        Note that the SCCs {a mathematical formula}C1,…,Cm of a program P can be viewed as atom sets {a mathematical formula}Σi=Ci defined by subprograms {a mathematical formula}Pi that contain all rules r from P with nonempty head contained in {a mathematical formula}Σi. The subprogram {a mathematical formula}SEQ-models of P induced by {a mathematical formula}{C1,…,Cm} coincide then with the {a mathematical formula}SCC-models of P. Thus, we can view the “syntactic” {a mathematical formula}SCC-models as extremal case of a user definition with no information about modules.
       </paragraph>
       <paragraph>
        Furthermore, we can reduce the subprogram semantics of program P w.r.t. {a mathematical formula}Σ1,…,Σm to {a mathematical formula}SCC-semantics of another program {a mathematical formula}P′ by a simple rewriting. For each {a mathematical formula}Pi, we use a fresh atom {a mathematical formula}pi and let {a mathematical formula}Pi′=P∪{a←pi,a;pi←pi,a|a∈Σi}. Clearly, the rules added to {a mathematical formula}Pi are tautologic and thus have no semantic effect on {a mathematical formula}Σi; however they enforce that all atoms in {a mathematical formula}Σi are in the same SCC of {a mathematical formula}P′=P1′∪⋯∪Pm′.
       </paragraph>
      </section>
      <section label="9.2.2">
       <section-title>
        Focusing
       </section-title>
       <paragraph>
        Another aspect is focusing the use of paracoherence at the semantic level. One natural way to incorporate this is to constrain the atoms that can be believed true without further justification to a set B of atoms. This corresponds to adopting a set of assumptions or hypotheses in abduction. The effect of such focusing is that simply all {a mathematical formula}SEQ-models {a mathematical formula}(X,Y) of a program are pruned which do not satisfy {a mathematical formula}gap(X,Y)⊆B.
       </paragraph>
       <paragraph label="Example 55">
        Let us reconsider the party visit program in Example 2 again. It may perfectly make sense to question for each person whether we are comfortable with adopting an unjustified belief. If we require provable evidence for Mark and Peter, then {a mathematical formula}B={go(John),go(Bill)} and from the original {a mathematical formula}SEQ-models {a mathematical formula}M2=({go(John)},{go(John),go(Bill)}) remains. If on the other hand, we would simply require provable evidence for all persons but Mark, then the {a mathematical formula}SEQ-model {a mathematical formula}M1=(∅,{go(Mark)}) remains.
       </paragraph>
       <paragraph label="Example 56">
        In the company Example 24, it is natural to put a focus on {a mathematical formula}B={has_social_sec(sam)}, as it does not make sense to believe the (syntactic) atom {a mathematical formula}ssnr(sam,sam); furthermore, even if we would have considered a modeling in which realistic social security numbers are considered, to believe any particular social security number (SSNR) out of a (big) range might be too strong an assumption; believing {a mathematical formula}has_social_sec(sam), which would be implied by the former releases us from adopting a particular SSNR.
       </paragraph>
       <paragraph>
        In general, such pruning can be easily accomplished. The computational complexity of the reasoning tasks that we considered in Section 7 (Table 1, Table 2) remains the same except that Problem COH is {a mathematical formula}Σ2p-complete for disjunctive and disjunctive stratified programs (the problem amounts to deciding whether some h-minimal HT-model {a mathematical formula}(X,Y) of the program P exists such that {a mathematical formula}gap(X,Y)⊆B, which is in {a mathematical formula}Σ2p; the matching hardness follows immediately from the results on answer set existence in [16]).
       </paragraph>
      </section>
     </section>
     <section label="9.3">
      <section-title>
       Language extensions
      </section-title>
      <paragraph>
       As already mentioned, semi-stable semantics has originally been developed as an extension to p-minimal model semantics [49], a paraconsistent semantics for extended disjunctive logic programs, i.e., programs which besides default negation also allow for strong (classical) negation. A declarative characterization of p-minimal models by means of frames was given by Alcantara et al. [1], who coined the term Paraconsistent Answer-set Semantics (PAS) for it. This characterization has been further simplified and underpinned with a logical axiomatization in [37] by using Routley models, i.e., a simpler possible worlds model.
      </paragraph>
      <paragraph>
       Our characterizations for both, semi-stable models and semi-equilibrium models, can be easily extended to this setting if they are applied to semantic structures which are given by quadruples of interpretations rather than bi-interpretations, respectively to Routley here-and-there models rather than HT-models. Intuitively, this again amounts to considering two ‘worlds’, each of which consists of a pair of interpretations: one for positive literals (atoms), and one for negative literals (strongly negated atoms). The respective epistemic transformations are unaffected except for the fact that literals are considered rather than atoms. One can also show for both semantics that there is a simple 1-to-1 correspondence to the semi-stable (resp. semi-equilibrium) models of a transformed logic program without strong negation: A given extended program P is translated into a program {a mathematical formula}P′ over {a mathematical formula}Σ∪{a′|a∈Σ} without strong negation by replacing each negative literal of the form −a by {a mathematical formula}a′. If {a mathematical formula}(I,J) is a semi-stable (semi-equilibrium) model of {a mathematical formula}P′, then{a mathematical formula} is a semi-stable (semi-equilibrium) model of P. Note that semi-stable (semi-equilibrium) models of extended logic programs obtained in this way generalize the PAS semantics, which means that they are paraconsistent as well as paracoherent. Logically this amounts to distinguishing nine truth values rather than three, with the additional truth values undefined, believed false, believed inconsistent, true with contradictory belief, false with contradictory belief, and inconsistent. The computational complexity for extended programs is the same.
      </paragraph>
      <paragraph>
       Compared to [49], we have confined here to propositional programs, as opposed to programs with variables (non-ground programs). However, respective semantics for non-ground programs via their grounding are straightforward. Alternatively, in case of semi-equilibrium models one can simply replace HT-models by Herbrand models of quantified equilibrium logic [41]. Similarly for the other semantics, replacing interpretations in the semantic structures by Herbrand interpretations over a given function-free first-order signature, yields a characterization of the respective models.
      </paragraph>
      <paragraph>
       Finally, as equilibrium logic is a conservative extension of answer sets of programs consisting of rules to the full propositional language, the notion of {a mathematical formula}SEQ-model immediately extends to richer classes of programs with propositional connectives, e.g., to programs with negation in the head [34] and nested logic programs [33]. Furthermore, it can also be easily extended to programs with weight constraints [22], aggregates [21], or more general external atoms [18], and to hybrid knowledge bases [12] (for the latter, see [23]).
      </paragraph>
     </section>
     <section label="9.4">
      <section-title>
       Parametric merging semantics
      </section-title>
      <paragraph>
       By the results of Section 7, tractable merging policies that ensure classical coherence (D3) will sometimes merge more components than necessary. To deal with the issues (1) and (2) in Section 6.2, i.e., with all cross-constraints and dependence, a parametric approach that gradually merges more SCCs seems attractive. We briefly outline here one possible such approach, which merges components within bounded distance.
      </paragraph>
      <paragraph>
       Denote for every {a mathematical formula}C∈SCC(P) by {a mathematical formula}Dk(C) the set of all descendants of C in {a mathematical formula}SG(P) within distance {a mathematical formula}k≥0; then we may proceed as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        Create a graph {a mathematical formula}Gk with a node {a mathematical formula}vr for each constraint r in P, which is labeled with the set{a mathematical formula} of SCCs; that is, all SCCs within distance k to a SCC {a mathematical formula}Ci that intersects with r are collected into one set, and on the resulting collection D of SCCs a function {a mathematical formula}clp(D) is applied. The latter closes D with respect to SCCs C that are on some path between members {a mathematical formula}C1 and {a mathematical formula}C2 of D in {a mathematical formula}SG(P).
       </list-item>
       <list-item label="2.">
        Merge then nodes {a mathematical formula}vr and {a mathematical formula}vr′ (and their labels, using {a mathematical formula}clp) such that {a mathematical formula}λ(vr)∩λ(vr′)≠∅ as long as possible.
       </list-item>
       <list-item label="3.">
        After that, create a node v for each SCC C that does not occur in any label of the graph, and set {a mathematical formula}λ(v)={C};
       </list-item>
       <list-item label="4.">
        add an edge from v to {a mathematical formula}v′, if {a mathematical formula}v≠v′ and {a mathematical formula}SG(P) has some edge {a mathematical formula}(Ci,Cj) where {a mathematical formula}Ci∈λ(v) and {a mathematical formula}Cj∈λ(v′).
       </list-item>
      </list>
      <paragraph>
       The resulting graph {a mathematical formula}Gk is acyclic and distinct nodes have disjoint labels. Similar as for {a mathematical formula}JG(P), any topological ordering ≤ of {a mathematical formula}Gk induces a splitting sequence {a mathematical formula}S≤ (via the node labels {a mathematical formula}λ(v), which are taken as union {a mathematical formula}⋃λ(v) of the SCCs they contain); thanks to an analog of Theorem 8, one can define the {a mathematical formula}Mk-models of P as {a mathematical formula}Mk(P)=SEQS≤(P) for an arbitrary ≤.
      </paragraph>
      <paragraph>
       For {a mathematical formula}k=0, we have {a mathematical formula}Dk(C)={C} and thus the node {a mathematical formula}vr in the initial graph {a mathematical formula}G0 contains in its label {a mathematical formula}λ(vr) the SCCs that intersect r; the final graph {a mathematical formula}G0 is such that each {a mathematical formula}Jx&lt;∈MJC(P) is included in some node label (i.e., {a mathematical formula}J⊆λ(v) for some node v). Hence, {a mathematical formula}MMJC(P)⊆M0(P) holds. As clearly {a mathematical formula}Mk(P)⊆Mk+1(P) holds for every {a mathematical formula}k≥0, and {a mathematical formula}Mk(P)=SEQ(P) for large enough k; as holds, we have a hierarchy of models between {a mathematical formula}MMJC(P) and {a mathematical formula}SEQ(P) which eventually establishes (D3); however, the results of Section 7 imply that predicting the least k such that {a mathematical formula}Mk(P)≠∅ is intractable.
      </paragraph>
      <paragraph>
       Other relaxed notions of models (using different parameters for cross-constraints and direct dependency) are conceivable; we leave this for future study.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Appendix: proofs
     </section-title>
     <section label="A.1">
      Section 3
      <paragraph label="Proof of Proposition 4">
       Let r be a rule over Σ, and let {a mathematical formula}(I,J) be a bi-interpretation over Σ.(⇐) Suppose that {a mathematical formula}(I,J) satisfies (a), i.e., {a mathematical formula}B+(r)⊆I and {a mathematical formula}J∩B−(r)=∅ implies {a mathematical formula}I∩H(r)≠∅ and {a mathematical formula}I∩B−(r)=∅. We prove that {a mathematical formula}(I,J)⊨βr, considering three cases:
       <list>
        Assume that {a mathematical formula}B+(r)⊈I. Then {a mathematical formula}(I,J)⊭βa, for some atom {a mathematical formula}a∈B+(r), and thus {a mathematical formula}(I,J)⊭βB(r) which implies {a mathematical formula}(I,J)⊨βr.Assume that {a mathematical formula}J∩B−(r)≠∅. Then {a mathematical formula}(I,J)⊭β¬a, for some atom {a mathematical formula}a∈B−(r), and thus {a mathematical formula}(I,J)⊭βB(r) which implies {a mathematical formula}(I,J)⊨βr.Assume that {a mathematical formula}B+(r)⊆I and {a mathematical formula}J∩B−(r)=∅. Then, since {a mathematical formula}(I,J) satisfies (a), it also holds that {a mathematical formula}I∩H(r)≠∅ and {a mathematical formula}I∩B−(r)=∅. From {a mathematical formula}B+(r)⊆I and {a mathematical formula}I∩B−(r)=∅, we conclude that {a mathematical formula}I⊨B(r). Moreover, {a mathematical formula}I∩H(r)≠∅ implies {a mathematical formula}(I,J)⊨βH(r). Thus, {a mathematical formula}(I,J)⊨βr.(⇒) Suppose that
       </list>
       <paragraph>
        {a mathematical formula}(I,J)⊨βr. We prove that {a mathematical formula}(I,J) satisfies (a), distinguishing two cases:
       </paragraph>
       <list>
        <list-item label="1)">
         Assume that {a mathematical formula}(I,J)⊭βB(r). Then either {a mathematical formula}(I,J)⊭βa, for some atom {a mathematical formula}a∈B+(r), or {a mathematical formula}(I,J)⊭β¬a, for some atom {a mathematical formula}a∈B−(r). Hence, {a mathematical formula}B+(r)⊈I or {a mathematical formula}J∩B−(r)≠∅, which implies that {a mathematical formula}(I,J) satisfies (a).
        </list-item>
        <list-item label="2)">
         Assume that {a mathematical formula}(I,J)⊨βH(r) and {a mathematical formula}I⊨B(r). Then {a mathematical formula}I∩H(r)≠∅ and {a mathematical formula}I∩B−(r)=∅, and thus {a mathematical formula}(I,J) satisfies (a).
        </list-item>
       </list>
       <paragraph>
        By our assumption, one of the two cases applies for {a mathematical formula}(I,J), which proves the claim.  □
       </paragraph>
      </paragraph>
      <paragraph label="Proof of Proposition 5">
       Let P be a program over Σ. Part (1). First, let {a mathematical formula}(I,J) be a bi-model of P. We prove that {a mathematical formula}(I,J)κ,P⊨Pκ.Towards a contradiction assume the contrary. Then there exists a rule {a mathematical formula}r′ in {a mathematical formula}Pκ, such that {a mathematical formula}(I,J)κ,P⊭r′. Suppose that {a mathematical formula}r′ is not transformed, i.e., {a mathematical formula}r′∈P and {a mathematical formula}B−(r′)=∅. Since {a mathematical formula}(I,J)⊨βr′, by Proposition 4 we conclude that {a mathematical formula}B+(r′)⊆I implies {a mathematical formula}I∩H(r′)≠∅ (recall that {a mathematical formula}B−(r′)=∅). By construction {a mathematical formula}(I,J)κ,P restricted to Σ coincides with I. Therefore, {a mathematical formula}B+(r′)⊆(I,J)κ,P implies {a mathematical formula}(I,J)κ,P∩H(r′)≠∅, i.e., {a mathematical formula}(I,J)κ,P⊨r′, a contradiction.Next, suppose that {a mathematical formula}r′ is obtained by the epistemic transformation of a corresponding rule {a mathematical formula}r∈P of the form (1), and consider the following cases:
       <list>
        {a mathematical formula}r′ is of the form (3): then {a mathematical formula}{b1,…,bm}⊆(I,J)κ,P, which implies {a mathematical formula}B+(r)⊆I. Moreover, {a mathematical formula}H(r′)∩(I,J)κ,P=∅ by the assumption that {a mathematical formula}(I,J)κ,P⊭r′. By construction of {a mathematical formula}(I,J)κ,P, this implies {a mathematical formula}J∩B−(r)=∅. Since {a mathematical formula}(I,J)⊨βr, we also conclude that {a mathematical formula}I∩H(r)≠∅ and that {a mathematical formula}I∩B−(r)=∅. Consequently, {a mathematical formula}J⊨B−(r), {a mathematical formula}ai∈I for some {a mathematical formula}ai∈H(r), and {a mathematical formula}I⊨B(r). Note also, that {a mathematical formula}B−(r)≠∅ by definition of the epistemic transformation. According to the construction of {a mathematical formula}(I,J)κ,P, it follows that {a mathematical formula}λr,i∈(I,J)κ,P, a contradiction to {a mathematical formula}H(r′)∩(I,J)κ,P=∅.{a mathematical formula}r′ is of the form (4): in this case, {a mathematical formula}(I,J)κ,P⊭r′ implies {a mathematical formula}λr,i∈(I,J)κ,P and {a mathematical formula}ai∉(I,J)κ,P. However, by construction {a mathematical formula}λr,i∈(I,J)κ,P implies {a mathematical formula}ai∈I; from the latter, again by construction, we conclude {a mathematical formula}ai∈(I,J)κ,P, a contradiction.{a mathematical formula}r′ is of the form (5): in this case, {a mathematical formula}(I,J)κ,P⊭r′ implies {a mathematical formula}λr,i∈(I,J)κ,P and {a mathematical formula}bj∈(I,J)κ,P. Note that {a mathematical formula}bj∈(I,J)κ,P iff {a mathematical formula}bj∈I. A consequence of the latter is that {a mathematical formula}I⊭B(r), contradicting a requirement for {a mathematical formula}λr,i∈(I,J)κ,P (cf. the construction of {a mathematical formula}(I,J)κ,P).{a mathematical formula}r′ is of the form (6): by the assumption that {a mathematical formula}(I,J)κ,P⊭r′, it holds that {a mathematical formula}λr,k∈(I,J)κ,P and {a mathematical formula}ai∈(I,J)κ,P, but {a mathematical formula}λr,i∉(I,J)κ,P. From the latter we conclude, by the construction of {a mathematical formula}(I,J)κ,P, that {a mathematical formula}ai∉I, since all other requirements for the inclusion of {a mathematical formula}λr,i (i.e., {a mathematical formula}r∈P, {a mathematical formula}B−(r)≠∅, {a mathematical formula}I⊨B(r), and {a mathematical formula}J⊨B−(r)) must be satisfied as witnessed by {a mathematical formula}λr,k∈(I,J)κ,P. However, if {a mathematical formula}ai∉I, then {a mathematical formula}ai∉(I,J)κ,P (again by construction), contradiction.This concludes the proof of the fact that if
       </list>
       <paragraph>
        {a mathematical formula}(I,J) is a bi-model of P, then {a mathematical formula}(I,J)κ,P⊨Pκ.Part (2). Let M be a model of {a mathematical formula}Pκ. We prove that {a mathematical formula}β(M∩Σκ)=(I,J) is a bi-model of P. Note that by construction {a mathematical formula}I=M∩Σ and {a mathematical formula}J={a|Ka∈M}. First, we consider any rule r in P such that {a mathematical formula}B−(r)=∅. Then {a mathematical formula}r∈Pκ, {a mathematical formula}J∩B−(r)=∅ and {a mathematical formula}I∩B−(r)=∅. Hence, by Proposition 4, we need to show that {a mathematical formula}B+(r)⊆(M∩Σ) implies {a mathematical formula}(M∩Σ)∩H(r)≠∅. Since {a mathematical formula}r∈Pκ, this follows from the assumption, i.e., {a mathematical formula}M⊨Pκ implies {a mathematical formula}M⊨r, and therefore if {a mathematical formula}B+(r)⊆M, then {a mathematical formula}M∩H(r)≠∅. Since r is over Σ, this proves the claim for all {a mathematical formula}r∈P such that {a mathematical formula}B−(r)=∅.It remains to show that {a mathematical formula}(I,J)⊨βr for all {a mathematical formula}r∈P such that {a mathematical formula}B−(r)≠∅. Towards a contradiction assume that this is not the case, i.e., (i) {a mathematical formula}B+(r)⊆(M∩Σ), (ii) {a mathematical formula}J∩B−(r)=∅, and either [(iii)] {a mathematical formula}(M∩Σ)∩H(r)=∅ or (iv) {a mathematical formula}(M∩Σ)∩B−(r)≠∅ hold for some {a mathematical formula}r∈P of the form (1), such that {a mathematical formula}B−(r)≠∅. Conditions (i) and (ii), together with {a mathematical formula}M⊨Pκ, imply that {a mathematical formula}λr,i is in M, for some {a mathematical formula}1≤i≤l (cf. the rule of the form (3) in the epistemic transformation of r). Consequently, {a mathematical formula}ai is in M (cf. the corresponding rule of the form (4) in the epistemic transformation of r), and hence {a mathematical formula}ai∈(M∩Σ). This rules out (iii), so (iv) must hold, i.e., {a mathematical formula}bj∈(M∩Σ), for some {a mathematical formula}m+1≤j≤n. But then, M satisfies the body of a constraint in {a mathematical formula}Pκ (cf. the corresponding rule of the form (5) in the epistemic transformation of r), contradicting {a mathematical formula}M⊨Pκ. This proves that there exists no {a mathematical formula}r∈P such that {a mathematical formula}B−(r)≠∅ and {a mathematical formula}(I,J)⊭βr, and thus concludes our proof of {a mathematical formula}(I,J)⊨βr. Since {a mathematical formula}r∈P was arbitrary, it follows that {a mathematical formula}β(M∩Σκ) is a bi-model of P.  □
       </paragraph>
      </paragraph>
      <paragraph label="Proof">
       Let P be a program over Σ. The proof uses the following lemmas. If{a mathematical formula}M∈AS(Pκ), then{a mathematical formula}β(M∩Σκ)satisfies (i).Towards a contradiction assume that {a mathematical formula}M∈AS(Pκ) and {a mathematical formula}β(M∩Σκ)=(I,J) does not satisfy (i). Then, there exists a bi-model {a mathematical formula}(I′,J) of P, such that {a mathematical formula}I′⊂I. By Proposition 5, {a mathematical formula}(I′,J)κ,P⊨Pκ. Note that {a mathematical formula}(I′,J)κ⊂(M∩Σκ). Let {a mathematical formula}S′={λr,i|λr,i∈(I′,J)κ,P} and let {a mathematical formula}S={λr,i|λr,i∈M}. We show that {a mathematical formula}S′⊆S. Suppose that this is not the case and assume that {a mathematical formula}λr,i∈S′ and {a mathematical formula}λr,i∉S, for some {a mathematical formula}r∈P of the form (1) and {a mathematical formula}1≤i≤l. By the construction of {a mathematical formula}(I′,J)κ,P, we conclude that {a mathematical formula}ai∈I′, {a mathematical formula}I′⊨B(r), and {a mathematical formula}J⊨B−(r). Since {a mathematical formula}I′⊂I, it also holds that {a mathematical formula}ai∈I and that {a mathematical formula}I⊨B+(r). Consider the rule of the form (3) of the epistemic transformation of r. We conclude that {a mathematical formula}{b1,…,bm}⊆M (due to {a mathematical formula}I⊨B+(r)), and that {a mathematical formula}M⊭Kc1∨…∨Kcn (due to {a mathematical formula}J⊨B−(r)). But {a mathematical formula}M⊨Pκ, hence {a mathematical formula}λr,k is in M, for some {a mathematical formula}1≤k≤l. However, considering the corresponding rule of the form (6) of the epistemic transformation of r, we also conclude that {a mathematical formula}λr,i∈M, a contradiction. Therefore {a mathematical formula}S′⊆S holds, and since {a mathematical formula}(I′,J)κ⊂(M∩Σκ), we conclude that {a mathematical formula}(I′,J)κ,P⊂M. The latter contradicts the assumption that M is an answer-set, i.e., a minimal model, of {a mathematical formula}Pκ. This concludes the proof of the lemma.  □If{a mathematical formula}(I,J)is a bi-model of P that satisfies (i) and (ii), then there exists some{a mathematical formula}M∈AS(Pκ), such that{a mathematical formula}β(M∩Σκ)=(I,J).Let {a mathematical formula}(I,J) be a bi-model of P that satisfies (i) and (ii). If {a mathematical formula}(I,J)κ,P∈AS(Pκ), then (c) holds since {a mathematical formula}β((I,J)κ,P∩Σκ)=(I,J). If {a mathematical formula}(I,J)κ,P∉AS(Pκ), then there exists a minimal model, i.e. an answer set, {a mathematical formula}M′ of {a mathematical formula}Pκ, such that {a mathematical formula}M′⊂(I,J)κ,P. Let {a mathematical formula}(I′,J′)=β(M′∩Σκ). Then {a mathematical formula}I′⊆I and {a mathematical formula}J′⊆J hold by construction and the fact that {a mathematical formula}M′⊂(I,J)κ,P. Towards a contradiction, assume that {a mathematical formula}I′⊂I. We show that then {a mathematical formula}(I′,J) is a bi-model of P. Suppose that {a mathematical formula}(I′,J) is not a bi-model of P. Then, by Proposition 4, there exists {a mathematical formula}r∈P, such that {a mathematical formula}B+(r)⊆I′, {a mathematical formula}J∩B−(r)=∅, and either {a mathematical formula}I′∩H(r)=∅ or {a mathematical formula}I′∩B−(r)≠∅. Note that {a mathematical formula}B+(r)⊆I′ implies {a mathematical formula}B+(r)⊆I, and since {a mathematical formula}(I,J) is a bi-model of P, we conclude {a mathematical formula}I∩H(r)≠∅ and {a mathematical formula}I∩B−(r)=∅. The latter implies {a mathematical formula}I′∩B−(r)=∅, hence {a mathematical formula}I′∩H(r)=∅ holds. If {a mathematical formula}B−(r)=∅, then r is in {a mathematical formula}Pκ and {a mathematical formula}M′⊭r, contradiction. Thus, {a mathematical formula}B−(r)≠∅. However, in this case the epistemic transformation of r is in {a mathematical formula}Pκ. Since {a mathematical formula}J∩B−(r)=∅ and {a mathematical formula}J′⊆J together imply {a mathematical formula}J′∩B−(r)=∅, we conclude that for the rule of the form (3) of the epistemic transformation of r, it holds that {a mathematical formula}{b1,…,bm}⊆M′ (due to {a mathematical formula}B+(r)⊆I′), and that {a mathematical formula}M′⊭Kc1∨…∨Kcn (due to {a mathematical formula}J′∩B−(r)=∅). Moreover {a mathematical formula}M′⊨Pκ, hence {a mathematical formula}λr,i is in {a mathematical formula}M′, for some {a mathematical formula}1≤i≤l. Considering the corresponding rule of the form (4) of the epistemic transformation of r, we also conclude that {a mathematical formula}ai∈M′, a contradiction to {a mathematical formula}I′∩H(r)=∅. This proves that {a mathematical formula}(I′,J) is a bi-model of P, and thus contradicts the assumption that {a mathematical formula}(I,J) satisfies (i). Consequently, {a mathematical formula}I′=I. Now if {a mathematical formula}J′⊂J, then we obtain a contradiction with the assumption that {a mathematical formula}(I,J) satisfies (ii). Therefore also {a mathematical formula}J′=J, which concludes the proof of the lemma.  □The proof of Theorem 1 is then as follows.Part (1). Let {a mathematical formula}(I,J) be a bi-model of P that satisfies (i)–(iii). We prove that {a mathematical formula}(I,J)κ∈SST(P). By Lemma 7, we conclude that there exists some {a mathematical formula}M∈AS(Pκ) such that {a mathematical formula}β(M∩Σκ)=(I,J). It remains to show that M is maximal canonical. Towards a contradiction assume the contrary. Then, there exists {a mathematical formula}M′∈AS(Pκ) such that {a mathematical formula}gap(M′)⊂gap(M). Let {a mathematical formula}(I′,J′)=β(M′∩Σκ). By Lemma 6, {a mathematical formula}(I′,J′) satisfies (i), and by construction since {a mathematical formula}gap(M′)⊂gap(M), it holds that {a mathematical formula}J′∖I′⊂J∖I. However, this contradicts the assumption that {a mathematical formula}(I,J) satisfies (iii). Therefore, M is maximal canonical, and hence {a mathematical formula}(I,J)κ∈SST(P).Part (2). Let {a mathematical formula}Iκ∈SST(P). We show that {a mathematical formula}β(Iκ) is a bi-model of P that satisfies (i)–(iii). Let {a mathematical formula}(I,J)=β(Iκ) and let M be a maximal canonical answer set of {a mathematical formula}Pκ corresponding to {a mathematical formula}Iκ. Then, {a mathematical formula}β(M∩Σκ)=(I,J) by construction, and {a mathematical formula}(I,J) satisfies (i) by Lemma 6.Towards a contradiction first assume that {a mathematical formula}(I,J) does not satisfy (iii). Then there exists a bi-model {a mathematical formula}(I′,J′) of P such that {a mathematical formula}(I′,J′) satisfies (i) and {a mathematical formula}J′∖I′⊂J∖I. Let {a mathematical formula}M′=(I′,J′)κ,P and note that if {a mathematical formula}M′∈AS(Pκ), we arrive at a contradiction to {a mathematical formula}M∈mc(AS(Pκ)), since {a mathematical formula}gap(M′)⊂gap(M). Thus, there exists {a mathematical formula}M″∈AS(Pκ), such that {a mathematical formula}M″⊂M′. Let {a mathematical formula}(I″,J″)=β(M″∩Σκ). We show that {a mathematical formula}(I″,J′) is a bi-model of P, and thus by (i) it follows that {a mathematical formula}I″=I′. Towards a contradiction, suppose that {a mathematical formula}(I″,J′) is not a bi-model of P. Then, by Proposition 4, there exists {a mathematical formula}r∈P, such that {a mathematical formula}B+(r)⊆I″, {a mathematical formula}J′∩B−(r)=∅, and either {a mathematical formula}I″∩H(r)=∅ or {a mathematical formula}I″∩B−(r)≠∅. Note that {a mathematical formula}B+(r)⊆I″ implies {a mathematical formula}B+(r)⊆I′, and since {a mathematical formula}(I′,J′) is a bi-model of P, we conclude {a mathematical formula}I′∩H(r)≠∅ and {a mathematical formula}I′∩B−(r)=∅. The latter implies {a mathematical formula}I″∩B−(r)=∅, hence {a mathematical formula}I″∩H(r)=∅ holds. If {a mathematical formula}B−(r)=∅, then r is in {a mathematical formula}Pκ and {a mathematical formula}M″⊭r, contradiction. Thus, {a mathematical formula}B−(r)≠∅. However, in this case the epistemic transformation of r is in {a mathematical formula}Pκ. Since {a mathematical formula}J′∩B−(r)=∅ and {a mathematical formula}J″⊆J′ together imply {a mathematical formula}J″∩B−(r)=∅, we conclude that for the rule of the form (3) of the epistemic transformation of r, it holds that {a mathematical formula}{b1,…,bm}⊆M″ (due to {a mathematical formula}B+(r)⊆I″), and that {a mathematical formula}M″⊭Kc1∨…∨Kcn (due to {a mathematical formula}J″∩B−(r)=∅). Moreover {a mathematical formula}M″⊨Pκ, hence {a mathematical formula}λr,i is in {a mathematical formula}M″, for some {a mathematical formula}1≤i≤l. Considering the corresponding rule of the form (4) of the epistemic transformation of r, we also conclude that {a mathematical formula}ai∈M″, a contradiction to {a mathematical formula}I″∩H(r)=∅. This proves that {a mathematical formula}(I″,J′) is a bi-model of P. From the assumption that {a mathematical formula}(I′,J′) satisfies (i), it follows that {a mathematical formula}I″=I′. Therefore {a mathematical formula}gap(M″)⊆gap(M′) holds, which implies {a mathematical formula}gap(M″)⊂gap(M), a contradiction to {a mathematical formula}M∈mc(AS(Pκ)). This proves {a mathematical formula}(I,J) satisfies (iii).Next assume that {a mathematical formula}(I,J) does not satisfy (ii). Then, there exists a bi-model {a mathematical formula}(I,J′) of P, such that {a mathematical formula}J′⊂J. We show that {a mathematical formula}(I,J′) satisfies (i). Otherwise, there exists a bi-model {a mathematical formula}(I′,J′) of P, such that {a mathematical formula}I′⊂I; but then also {a mathematical formula}(I′,J) is a bi-model of P. To see the latter, assume that there exists a rule {a mathematical formula}r∈P, such that {a mathematical formula}B(r)⊆I′, {a mathematical formula}J∩B−(r)=∅ and either {a mathematical formula}I′∩H(r)=∅ or {a mathematical formula}I′∩B−(r)≠∅. Since {a mathematical formula}J′⊂J, it then also holds that {a mathematical formula}J′∩B−(r)=∅. This contradicts the assumption that {a mathematical formula}(I′,J′) is a bi-model of P, hence {a mathematical formula}(I′,J)⊨βP. The latter is a contradiction to the assumption that {a mathematical formula}(I,J) satisfies (i), proving that {a mathematical formula}(I,J′) satisfies (i). Since {a mathematical formula}(I,J) satisfies (iii), we conclude that {a mathematical formula}J′∖I=J∖I. Now let {a mathematical formula}S′={λr,i|λr,i∈(I,J′)κ,P} and let {a mathematical formula}S={λr,i|λr,i∈M}. It holds that {a mathematical formula}S′⊈S (otherwise {a mathematical formula}(I,J′)κ,P⊂M, a contradiction to {a mathematical formula}M∈AS(Pκ)), i.e., there exists {a mathematical formula}r∈P of the form (1) and {a mathematical formula}1≤i≤l, such that {a mathematical formula}λr,i∈S and {a mathematical formula}λr,i∉S′. From the former, since M is a minimal model of {a mathematical formula}Pκ, we conclude that {a mathematical formula}I⊨B+(r), {a mathematical formula}ai∈I, and {a mathematical formula}J∩B−(r)=∅. Since {a mathematical formula}J′⊂J, also {a mathematical formula}J′∩B−(r)=∅. This implies that {a mathematical formula}λr,k∈S′, for some {a mathematical formula}1≤k≠i≤l (otherwise {a mathematical formula}(I,J′)κ,P does not satisfy the rule of form (3) corresponding to r in {a mathematical formula}Pκ, a contradiction to {a mathematical formula}(I,J′)κ,P⊨Pκ). However, since {a mathematical formula}ai∈I, and thus {a mathematical formula}ai∈(I,J′)κ,P, and since {a mathematical formula}λr,k∈(I,J′)κ,P, we conclude that {a mathematical formula}λr,i∈(I,J′)κ,P (cf. the respective rule of form (6) of the epistemic transformation of r). This contradicts {a mathematical formula}λr,i∉S′, and thus proves that {a mathematical formula}(I,J) satisfies (ii).  □
      </paragraph>
     </section>
     <section label="A.2">
      Section 4
      <paragraph label="Proof of Proposition 6">
       Let P be a program over Σ.Part (1). Let {a mathematical formula}(I,J) be a bi-model of P, such that {a mathematical formula}(I,J)κ satisfies Property N and Property K, for all {a mathematical formula}r∈P. We show that {a mathematical formula}(I,J) is an HT-model of P. Since {a mathematical formula}(I,J)κ satisfies Property N, it holds that {a mathematical formula}a∈I implies {a mathematical formula}a∈J, therefore {a mathematical formula}I⊆J, i.e., {a mathematical formula}(I,J) is an HT-interpretation. For every rule {a mathematical formula}r∈P, {a mathematical formula}(I,J)⊨βr implies {a mathematical formula}(I,J)⊭βB(r), or {a mathematical formula}(I,J)⊨βH(r) and {a mathematical formula}I⊨B(r). First suppose that {a mathematical formula}(I,J)⊭βB(r). Then {a mathematical formula}(I,J)⊭B(r) (note that for a conjunction of literals, such as {a mathematical formula}B(r), the satisfaction relations do not differ). Moreover, since {a mathematical formula}(I,J)κ satisfies Property K for r, it holds that {a mathematical formula}J⊨r. To see the latter, let Kr denote the rule obtained from r by replacing every {a mathematical formula}a∈Σ occurring in r by Ka, and let KJ denote the set {a mathematical formula}{Ka∈(I,J)κ|a∈Σ}. Then, {a mathematical formula}(I,J)κ satisfies Property K for r iff {a mathematical formula}KJ⊨Kr. Observing that {a mathematical formula}KJ={Ka|a∈J}, we conclude that {a mathematical formula}J⊨r. This proves {a mathematical formula}(I,J)⊨r, if {a mathematical formula}(I,J)⊭βB(r). Next assume that {a mathematical formula}(I,J)⊨βH(r) and {a mathematical formula}I⊨B(r). We conclude that {a mathematical formula}(I,J)⊨H(r) (the satisfaction relations also coincide for disjunctions of atoms). As {a mathematical formula}(I,J)κ satisfies Property K for r, it follows {a mathematical formula}J⊨r. This proves {a mathematical formula}(I,J)⊨r, for every {a mathematical formula}r∈P; in other words, {a mathematical formula}(I,J) is an HT-model of P.Part (2). Let {a mathematical formula}(H,T) be an HT-model of P. We show that {a mathematical formula}(H,T)κ satisfies Property N and Property K, for all {a mathematical formula}r∈P. As a consequence of {a mathematical formula}H⊆T, for every {a mathematical formula}a∈(H,T)κ such that {a mathematical formula}a∈Σ, it also holds that {a mathematical formula}Ka∈(H,T)κ, i.e., {a mathematical formula}(H,T)κ satisfies Property N. Moreover, {a mathematical formula}(H,T)⊨P implies {a mathematical formula}T⊨r, for all {a mathematical formula}r∈P. Let {a mathematical formula}KT={Ka|a∈T} and let Kr be as above; {a mathematical formula}T⊨r implies {a mathematical formula}KT⊨Kr, for all {a mathematical formula}r∈P. By construction of {a mathematical formula}(H,T)κ and definition of Property K for r, we conclude that {a mathematical formula}(H,T)κ satisfies Property K for all {a mathematical formula}r∈P.  □
      </paragraph>
      <paragraph label="Proof of Theorem 2">
       Let P be a program over Σ.Part (1). Let {a mathematical formula}(H,T) be an HT-model of P that satisfies {a mathematical formula}(i′) and {a mathematical formula}(ii′). We show that {a mathematical formula}(H,T)κ∈SEQ(P). Towards a contradiction, first assume that {a mathematical formula}(H,T)κ∉MM(HTκ(P)). Then, there exists an HT-model {a mathematical formula}(H′,T′) of P, such that {a mathematical formula}H′⊆H, {a mathematical formula}T′⊆T, and at least one of the inclusions is strict. Suppose that {a mathematical formula}H′⊂H. Then {a mathematical formula}(H′,T) is an HT-model of P (by a well-known property of HT), a contradiction to the assumption that {a mathematical formula}(H,T) satisfies {a mathematical formula}(i′). Hence, {a mathematical formula}H′=H and {a mathematical formula}T′⊂T must hold. Moreover, by the same argument {a mathematical formula}(H′,T′) also satisfies {a mathematical formula}(i′). But, since {a mathematical formula}T′∖H′⊂T∖H, this is in contradiction to the assumption that {a mathematical formula}(H,T) satisfies {a mathematical formula}(ii′). Consequently, {a mathematical formula}(H,T)κ∈MM(HTκ(P)). We continue the indirect proof assuming that {a mathematical formula}(H,T)κ∉mc(MM(HTκ(P))), i.e., there exists an HT-model {a mathematical formula}(H′,T′) of P, such that {a mathematical formula}T′∖H′⊂T∖H and {a mathematical formula}(H′,T′)κ∈MM(HTκ(P)). The latter obviously implies that {a mathematical formula}(H′,T′) satisfies {a mathematical formula}(i′). Again, this contradicts that {a mathematical formula}(H,T) satisfies {a mathematical formula}(ii′), which proves that {a mathematical formula}(H,T)κ∈SEQ(P).Part (2). Let {a mathematical formula}Iκ∈SEQ(P). We show that {a mathematical formula}β(Iκ) is an HT-model of P that satisfies {a mathematical formula}(i′) and {a mathematical formula}(ii′). Let {a mathematical formula}β(Iκ)=(H,T). Towards a contradiction first assume that {a mathematical formula}(H,T) is not an HT-model of P. Then by the definition of {a mathematical formula}SEQ(P), and the fact that {a mathematical formula}Iκ uniquely corresponds to sets H and T, we conclude that {a mathematical formula}Iκ∉mc(MM(HTκ(P))), i.e., {a mathematical formula}Iκ∉SEQ(P); contradiction. Next, suppose that {a mathematical formula}(H,T) does not satisfy {a mathematical formula}(i′). Then, {a mathematical formula}Iκ∉MM(HTκ(P)), as witnessed by {a mathematical formula}(H′,T)κ for an HT-model {a mathematical formula}(H′,T) such that {a mathematical formula}H′⊂H, which exists if {a mathematical formula}(H,T) does not satisfy {a mathematical formula}(i′). Therefore, {a mathematical formula}Iκ∉mc(MM(HTκ(P))), i.e., {a mathematical formula}Iκ∉SEQ(P); contradiction. Eventually assume that {a mathematical formula}(H,T) does not satisfy {a mathematical formula}(ii′). Then, {a mathematical formula}Iκ∉mc(MM(HTκ(P))), as witnessed by {a mathematical formula}(H′,T′)κ for an HT-model {a mathematical formula}(H′,T′), such that {a mathematical formula}T′∖H′⊂T∖H and {a mathematical formula}(H′,T′) satisfies {a mathematical formula}(i′)—note that {a mathematical formula}(H′,T′) exists if {a mathematical formula}(H,T) does not satisfy {a mathematical formula}(ii′). To see that {a mathematical formula}(H′,T′)κ is a witness for {a mathematical formula}Iκ∉mc(MM(HTκ(P))), observe that either {a mathematical formula}(H′,T′)κ∈MM(HTκ(P)) or there exists an HT-model {a mathematical formula}(H′,T″), such that {a mathematical formula}(H′,T″)κ∈MM(HTκ(P)) and {a mathematical formula}T″⊂T′ (which implies {a mathematical formula}T″∖H′⊂T′∖H′⊂T∖H). This proves that {a mathematical formula}Iκ∉SEQ(P), again a contradiction. This concludes the proof that {a mathematical formula}β(Iκ) is an HT-model of P that satisfies {a mathematical formula}(i′) and {a mathematical formula}(ii′).  □
      </paragraph>
      <paragraph label="Proof">
       Let P be a program over Σ, and let {a mathematical formula}Iκ be an interpretation over {a mathematical formula}Σκ. The proof uses the following lemmas. If{a mathematical formula}M⊨PHT, then{a mathematical formula}β(M∩Σκ)is an HT-model of P.Let {a mathematical formula}(I,J)=β(M∩Σκ). Since {a mathematical formula}M⊨Pκ, {a mathematical formula}(I,J) is a bi-model of P by Proposition 5. Moreover, {a mathematical formula}M∩Σκ=(I,J)κ and {a mathematical formula}(I,J)κ satisfies Property N, otherwise there is an atom {a mathematical formula}a∈M such that {a mathematical formula}Ka∉M, a contradiction to {a mathematical formula}M⊨Ka←a. Also, {a mathematical formula}(I,J)κ satisfies Property K for all {a mathematical formula}r∈P; otherwise, if Property K does not hold for some {a mathematical formula}r∈P of the form (1), then {a mathematical formula}M⊨Kb1∧…∧Kbm and {a mathematical formula}M⊭Ka1∨…∨Kal∨Kc1∨…∨Kcn, i.e., {a mathematical formula}M⊭PHT; contradiction. Hence by Proposition 6, {a mathematical formula}(I,J) is a HT-model of P.  □Next, we prove: If{a mathematical formula}(H,T)is an HT-model of P, then{a mathematical formula}(H,T)κ,P⊨PHT.Note that every HT-model of P is a bi-model of P. Assume the contrary; then {a mathematical formula}(H,T)⊨r and {a mathematical formula}(H,T)⊭βr, for some {a mathematical formula}r∈P. Then, {a mathematical formula}H⊭B(r), while {a mathematical formula}(H,T)⊨B(r), must hold. However, {a mathematical formula}(H,T)⊨B(r) implies {a mathematical formula}B+(r)⊆H and {a mathematical formula}B−(r)∩H=∅, and therefore {a mathematical formula}H⊨B(r); contradiction. This proves that {a mathematical formula}(H,T) is a bi-model of P. Consequently, {a mathematical formula}(H,T)κ,P⊨Pκ by Proposition 5. Moreover, since {a mathematical formula}(H,T) is an HT-model, {a mathematical formula}(H,T)κ satisfies Property N (and Property K for all {a mathematical formula}r∈P) by Proposition 6. Because {a mathematical formula}(H,T)κ,P∩Σκ=(H,T)κ, this implies that {a mathematical formula}(H,T)κ,P⊨r, for all rules of the form {a mathematical formula}Ka←a in {a mathematical formula}PHT∖Pκ (this is an obvious consequence of Property N). For the remaining rules r in {a mathematical formula}PHT∖Pκ, {a mathematical formula}(H,T)κ,P⊨r is a simple consequence of {a mathematical formula}T⊨P. This proves {a mathematical formula}(H,T)κ,P⊨PHT.  □For every{a mathematical formula}M∈AS(PHT),{a mathematical formula}β(M∩Σκ)satisfies{a mathematical formula}(i′)inTheorem 2.Towards a contradiction assume the contrary. Then there exists an HT-model {a mathematical formula}(H′,T) of P such that {a mathematical formula}H′⊂H. Note that {a mathematical formula}M∈AS(PHT) implies {a mathematical formula}M=β(M∩Σκ)κ,P. Since the latter is a model of {a mathematical formula}PHT by Lemma 9, M must be a subset thereof; however it obviously cannot be a strict subset on {a mathematical formula}Σκ. By construction of {a mathematical formula}β(M∩Σκ)κ,P and the rules of form (6) of the epistemic transformation, we also conclude that {a mathematical formula}λr,i∈β(M∩Σκ)κ,P implies {a mathematical formula}λr,i∈M, for any {a mathematical formula}r∈P of the form (1) and {a mathematical formula}1≤i≤l. This proves {a mathematical formula}M=β(M∩Σκ)κ,P. Now consider {a mathematical formula}M′=(H′,T)κ,P. Then, {a mathematical formula}M′⊂M by construction, and {a mathematical formula}M′⊨PHT by Lemma 9. This is a contradiction to the assumption that {a mathematical formula}M∈AS(PHT), and thus proves that {a mathematical formula}β(M∩Σκ) satisfies {a mathematical formula}(i′).  □For every HT-model{a mathematical formula}(H,T)of P that satisfies{a mathematical formula}(i′)ofTheorem 2, there exists some{a mathematical formula}M∈AS(PHT)such that{a mathematical formula}gap(M)⊆gap((H,T)κ).Since {a mathematical formula}(H,T)κ,P⊨PHT by Lemma 9, there exists {a mathematical formula}M∈AS(PHT), such that {a mathematical formula}M⊆(H,T)κ,P. To prove the lemma, it suffices to show that {a mathematical formula}M∩Σ=H. Assume the contrary; then by (d) there exists an HT-model {a mathematical formula}(H′,T′) of P, such that {a mathematical formula}H′⊂H and {a mathematical formula}T′⊆T. However, then {a mathematical formula}(H′,T)⊨P, which contradicts the assumption that {a mathematical formula}(H,T) satisfies {a mathematical formula}(i′).  □The proof of Theorem 3 is then as follows.(⇐) Suppose that {a mathematical formula}Iκ∈{M∩Σκ|M∈mc(AS(PHT))}. We prove {a mathematical formula}Iκ∈SEQ(P) via Theorem 2. Let {a mathematical formula}M∈mc(AS(PHT)), such that {a mathematical formula}Iκ=M∩Σκ, and let {a mathematical formula}(I,J)=β(M∩Σκ). Then, {a mathematical formula}(I,J) is an HT-model of P by Lemma 8 and {a mathematical formula}(I,J) satisfies {a mathematical formula}(i′) in Theorem 2 by Lemma 10. We prove that {a mathematical formula}(I,J) satisfies {a mathematical formula}(ii′) in Theorem 2. Towards a contradiction, assume that this is not the case, then there exists an HT-model {a mathematical formula}(H,T) of P, such that {a mathematical formula}T∖H⊂J∖I and {a mathematical formula}(H,T) satisfies {a mathematical formula}(i′). According to Lemma 11, there exists {a mathematical formula}M′∈AS(PHT), such that {a mathematical formula}gap(M′)⊆gap((H,T)κ), which implies {a mathematical formula}gap(M′)⊂gap(M) due to {a mathematical formula}T∖H⊂J∖I. This contradicts the assumption that {a mathematical formula}M∈mc(AS(PHT)), and thus proves that {a mathematical formula}(I,J) satisfies {a mathematical formula}(ii′) in Theorem 2. We conclude that {a mathematical formula}Iκ∈SEQ(P).(⇒) Suppose that {a mathematical formula}Iκ∈SEQ(P). We prove {a mathematical formula}Iκ∈{M∩Σκ|{a mathematical formula}M∈mc(AS(PHT))}. Let {a mathematical formula}(H,T)=β(Iκ). By Theorem 2, {a mathematical formula}(H,T) is an HT-model of P that satisfies {a mathematical formula}(i′) and {a mathematical formula}(ii′). We show that there exists {a mathematical formula}M∈mc(AS(PHT)) such that {a mathematical formula}β(M∩Σκ)=(H,T). Since {a mathematical formula}(H,T)κ,P⊨PHT, there exists {a mathematical formula}M∈AS(PHT) such that {a mathematical formula}M⊆(H,T)κ,P. Since {a mathematical formula}(H,T) satisfies {a mathematical formula}(i′), it holds that {a mathematical formula}M∩Σ=H. Moreover, {a mathematical formula}M∩Σκ⊂(H,T)κ contradicts the fact that {a mathematical formula}(H,T) satisfies {a mathematical formula}(ii′), because then {a mathematical formula}β(M∩Σκ)=(H,T′) is an HT-model of P, such that {a mathematical formula}T′∖H⊂T∖H and {a mathematical formula}(H,T′) satisfies {a mathematical formula}(i′) due to Lemma 10. Hence, {a mathematical formula}β(M∩Σκ)=(H,T). It remains to show that {a mathematical formula}M∈mc(AS(PHT)). If this is not the case, then some HT-model {a mathematical formula}(H′,T′) of P exists such that {a mathematical formula}T′∖H′⊂T∖H. Since {a mathematical formula}(H′,T′)=β(M′∩Σκ) for some {a mathematical formula}M′∈AS(PHT), we conclude by Lemma 10 that {a mathematical formula}(H′,T′) satisfies {a mathematical formula}(i′), which again leads to a contradiction of the fact that {a mathematical formula}(H,T) satisfies {a mathematical formula}(ii′). This proves that {a mathematical formula}M∈mc(AS(PHT)). As {a mathematical formula}M∩Σκ=Iκ, we conclude that {a mathematical formula}Iκ∈{M∩Σκ|M∈mc(AS(PHT))}.  □
      </paragraph>
      <paragraph label="Proof of Proposition 7">
       Let P be a program over Σ. If P has a model M, then {a mathematical formula}(M,M) is an HT-model of P. Therefore {a mathematical formula}HTκ(P)≠∅, which implies {a mathematical formula}MM(HTκ(P))≠∅, and thus {a mathematical formula}mc(MM(HTκ(P)))≠∅. We conclude that {a mathematical formula}SEQ(P)≠∅, i.e., P has a semi-equilibrium model.  □
      </paragraph>
      <paragraph label="Proof of Proposition 8">
       Let P be a coherent program over Σ, and let {a mathematical formula}Y∈AS(P). Then {a mathematical formula}(Y,Y) is an HT-model of P that satisfies {a mathematical formula}(i′) in Theorem 2, since it is in equilibrium. Moreover, it trivially satisfies also {a mathematical formula}(ii′) because {a mathematical formula}Y∖Y=∅. Hence, {a mathematical formula}(Y,Y)κ∈SEQ(P).As P is coherent, there exists {a mathematical formula}(T,T)∈HT(P) that satisfies {a mathematical formula}(i′) in Theorem 2 and (trivially) {a mathematical formula}(ii′). Hence, {a mathematical formula}gap(Iκ)=∅ for all {a mathematical formula}Iκ∈SEQ(P). Moreover, {a mathematical formula}β(Iκ) is of the form {a mathematical formula}(Y,Y), and {a mathematical formula}Y∈AS(P).  □
      </paragraph>
     </section>
     <section label="A.3">
      Section 5
      <paragraph label="Proof of Proposition 10">
       If {a mathematical formula}(X,Y)∈SEQS(P), then there exists some {a mathematical formula}(I,J)∈SEQ(bS(P)) such that {a mathematical formula}(X,Y)∈SEQ(PS(I,J)). We will prove that {a mathematical formula}(I,J)=(X,Y)|S. Obviously {a mathematical formula}I⊆J⊆S. Moreover because {a mathematical formula}(X,Y)⊨a for each {a mathematical formula}a∈I, we have {a mathematical formula}a∈X for all {a mathematical formula}a∈I, so {a mathematical formula}I⊆X; because {a mathematical formula}(X,Y)⊨{←nota|a∈J}, then {a mathematical formula}a∈Y for all {a mathematical formula}a∈J, so {a mathematical formula}J⊆Y; and because {a mathematical formula}(X,Y)⊨{←a|a∈S∖J}, then {a mathematical formula}a∉Y for all {a mathematical formula}a∈S∖J, so {a mathematical formula}(S∖J)∩Y=∅. In particular we obtain that {a mathematical formula}I⊆X∩S and {a mathematical formula}J⊆Y∩S. We know that {a mathematical formula}(X,Y)⊨PS(I,J). So if we consider {a mathematical formula}a∈X∩S, then {a mathematical formula}a∈H(r) for some rule {a mathematical formula}r∈P∖bS(P)∪{a|a∈I}. But because {a mathematical formula}a∈S, it follows that {a mathematical formula}r∉P∖bS(P), so {a mathematical formula}r∈{a|a∈I}. Therefore {a mathematical formula}a∈I, that is {a mathematical formula}I=X∩S. Moreover if we consider an atom {a mathematical formula}a∈Y∩S, then {a mathematical formula}a∈Y and {a mathematical formula}a∈S, and because {a mathematical formula}(S∖J)∩Y=∅, we obtain that {a mathematical formula}a∈J, that is {a mathematical formula}J=Y∩S. In conclusion, we have that {a mathematical formula}(X∩S,Y∩S)=(I,J) is a semi-equilibrium model of {a mathematical formula}bS(P).  □
      </paragraph>
      <paragraph label="Proof of Lemma 1">
       Suppose that {a mathematical formula}(X,Y) is an HT-model of {a mathematical formula}PS(I,J). Hence, {a mathematical formula}(X,Y)⊨P∖bS(P). It remains to show that {a mathematical formula}(X,Y)⊨r for every {a mathematical formula}r∈bS(P). Suppose that r has the form (1). By assumption {a mathematical formula}(I,J)∈SEQ(bS(P)), hence we conclude that {a mathematical formula}(I,J)⊨bS(P).If {a mathematical formula}(I,J)⊨ai for some {a mathematical formula}ai∈H(r), then {a mathematical formula}ai∈I and because {a mathematical formula}(X,Y)⊨PS(I,J), we have {a mathematical formula}(X,Y)⊨ai, i.e. {a mathematical formula}(X,Y)⊨r.If we assume that {a mathematical formula}(I,J)⊭b1∧…∧bm∧¬c1∧…∧¬cn, then there exists some {a mathematical formula}bj∈B+(r) such that {a mathematical formula}(I,J)⊭bj or some {a mathematical formula}ck∈B−(r) such that {a mathematical formula}(I,J)⊭¬ck, that is, by definition of HT-satisfaction that {a mathematical formula}bj∉I respectively {a mathematical formula}ck∈J.In the first case, {a mathematical formula}bj is not in the head of any other rule in {a mathematical formula}P∖bS(P), for which {a mathematical formula}bj∉X and so {a mathematical formula}(X,Y)⊨r.In the second case, we have in {a mathematical formula}PS(I,J) the rule {a mathematical formula}←notck; this implies {a mathematical formula}ck∈Y, and therefore, also in this case, {a mathematical formula}(X,Y)⊨r.  □
      </paragraph>
      <paragraph label="Proof of Proposition 11">
       Moreover, we suppose that(3) {a mathematical formula}gap(X,Y) is minimal among the gaps of the HT-models that satisfy (1) and (2).Because {a mathematical formula}(X′,Y′)⊨P, it holds that {a mathematical formula}(X′,Y′)⊨tS(P) and {a mathematical formula}(X′,Y′)⊨bS(P). From this we obtain that {a mathematical formula}(X′∩S,Y′∩S)⊨bS(P) and by condition (2) we obtain that{a mathematical formula} Moreover {a mathematical formula}(X′,Y′)|S satisfies the h-minimality with respect to {a mathematical formula}bS(P). In fact if by contradiction there exists {a mathematical formula}(I′,Y′∩S)⊨bS(P), such that {a mathematical formula}I′⊂X′∩S, then {a mathematical formula}(I′∪(X′∖S),Y′)⊨P and {a mathematical formula}I′∪(X′∖S)⊂(X′∩S)∪(X′∖S)=X′ against the condition (1). By Proposition 10, {a mathematical formula}(X∩S,Y∩S)∈SEQ(bS(P)), so we have necessarily that {a mathematical formula}(Y′∩S)∖(X′∩S)=(Y∩S)∖(X∩S)=J∖I. Otherwise {a mathematical formula}(X,Y)|S could not be a semi-equilibrium model of {a mathematical formula}bS(P), because {a mathematical formula}(X′,Y′)|S contradicts the gap-minimality of {a mathematical formula}(X,Y)|S. Therefore {a mathematical formula}(X′,Y′)|S∈SEQ(bS(P)), because if there exists {a mathematical formula}(Iˆ,Jˆ)⊨bS(P), that satisfies the h-minimality property and {a mathematical formula}Jˆ∖Iˆ⊂(Y′∩S)∖(X′∩S), then {a mathematical formula}Jˆ∖Iˆ⊂(Y∩S)∖(X∩S), and therefore {a mathematical formula}(X,Y)|S∉SEQ(bS(P)), contrary to what is assumed. Now we show that {a mathematical formula}(X′,Y′) must be a semi-equilibrium model of {a mathematical formula}PS(X′∩S,Y′∩S). First since {a mathematical formula}(X′,Y′)⊨tS(P) and {a mathematical formula}(X′,Y′)|S∈SEQ(bS(P)), it follows that {a mathematical formula}(X′,Y′)⊨PS(X′∩S,Y′∩S). We prove the h-minimality of {a mathematical formula}(X′,Y′) with respect to {a mathematical formula}PS(X′∩S,Y′∩S). If by contradiction there exists {a mathematical formula}(Xˆ,Y′)⊨PS(X′∩S,Y′∩S) with {a mathematical formula}Xˆ⊂X′, then, by Lemma 1, {a mathematical formula}(Xˆ,Y′)⊨P against the hypothesis (1). Finally we prove the gap-minimality of {a mathematical formula}(X′,Y′) respect to {a mathematical formula}PS(X′∩S,Y′∩S). If by contradiction there exists {a mathematical formula}(Xˆ,Yˆ)⊨PS(X′∩S,Y′∩S), that satisfies the h-minimality property and, moreover, {a mathematical formula}Yˆ∖Xˆ⊂Y′∖X′, then there exists {a mathematical formula}(Xˆ,Yˆ)⊨P (by Lemma 1) that satisfies the h-minimality property and {a mathematical formula}Yˆ∖Xˆ⊂Y′∖X′, against the hypothesis (3). In conclusion we have proved that {a mathematical formula}(X′,Y′)∈SEQ(PS(X′∩S,Y′∩S)) and since hypothesis (2), {a mathematical formula}Y′∖X′⊂Y∖X, it follows that {a mathematical formula}(X,Y) would not be a semi-equilibrium model relative to S. And so we come to a contradiction, so a supposed {a mathematical formula}(X′,Y′) cannot exist. Therefore {a mathematical formula}(X,Y) satisfies the gap-minimality property respect to P, so that {a mathematical formula}(X,Y)∈SEQ(P).  □
      </paragraph>
      <paragraph label="Proof of Proposition 12">
       Let {a mathematical formula}(X,Y)∈SEQ(P) and {a mathematical formula}(X,Y)|S∈SEQ(bS(P)). To demonstrate that {a mathematical formula}(X,Y)∈SEQS(P), first we will prove that {a mathematical formula}(X,Y) is a semi-equilibrium model of {a mathematical formula}PS(X∩S,Y∩S). Since {a mathematical formula}(X,Y)∈SEQ(P), we obtain in particular that {a mathematical formula}(X,Y)⊨tS(P). Now because {a mathematical formula}X∩S⊆X then {a mathematical formula}(X,Y)⊨{a|a∈X∩S}, because {a mathematical formula}Y∩S⊆Y then {a mathematical formula}(X,Y)⊨{←nota|a∈Y∩S}, and because {a mathematical formula}(S∖(Y∩S))∩Y=∅ then {a mathematical formula}(X,Y)⊨{←a|a∈S∖(Y∩S)}. So that {a mathematical formula}(X,Y) is an HT-model of {a mathematical formula}PS(X∩S,Y∩S). So it remains to prove the h-minimality and the gap-minimality of {a mathematical formula}(X,Y) as regards to {a mathematical formula}PS(X∩S,Y∩S). If, by contradiction, we suppose that there exists {a mathematical formula}X′ such that {a mathematical formula}X′⊂X and {a mathematical formula}(X′,Y)⊨PS(X∩S,Y∩S), then, by Lemma 1, {a mathematical formula}(X′,Y)⊨P and this contradicts the h-minimality of {a mathematical formula}(X,Y) as regards to P. Similarly if, by contradiction, we assume that there exists {a mathematical formula}(X′,Y′)⊨PS(X∩S,Y∩S) that satisfies the h-minimality property and {a mathematical formula}Y′∖X′⊂Y∖X, then by Lemma 1, we obtain that {a mathematical formula}(X′,Y′)⊨P and this contradicts the gap-minimality of {a mathematical formula}(X,Y) as regards to P. Finally, it must be shown that there is no {a mathematical formula}(Xˆ,Yˆ)∈SEQ(PS(I,J)) with {a mathematical formula}(I,J)∈SEQ(bS(P)), such that {a mathematical formula}gap(Xˆ,Yˆ)⊂gap(X,Y). In fact if, by contradiction, there exists such a {a mathematical formula}(Xˆ,Yˆ), then {a mathematical formula}(Xˆ,Yˆ)⊨P (by Lemma 1), {a mathematical formula}(Xˆ,Yˆ) satisfies the h-minimality property respect to P and {a mathematical formula}gap(Xˆ,Yˆ)⊂gap(X,Y); i.e. {a mathematical formula}(X,Y) does not satisfy the gap-minimality property respect to P, against the hypothesis. Therefore, in conclusion, {a mathematical formula}(X,Y)∈SEQS(P).  □
      </paragraph>
      <paragraph label="Proof of Corollary 3">
       By Theorem 4, {a mathematical formula}SEQS(P)={(X,Y)∈SEQ(P)|(X,Y)|S∈SEQ(bS(P))}. As {a mathematical formula}SEQ(P)≠∅, by Proposition 8{a mathematical formula}SEQ(P)=EQ(P), and {a mathematical formula}SEQ(bS(P))=EQ(bS(P)); by Proposition 2 and the identity (2) (i.e., by identity (11), it follows that {a mathematical formula}SEQS(P){(X,Y)∈EQ(P)|(X,Y)|S∈EQ(bS(P))}=EQ(P). As for any positive program P, {a mathematical formula}EQ(P)={(M,M)|M∈MM(P)}, the result follows.  □
      </paragraph>
      <paragraph label="Proof of Proposition 13">
       If P is constraint-free, then P has some model, hence also {a mathematical formula}bS(P) (⊆P) has some model, and thus by Proposition 7, {a mathematical formula}SEQ(bS(P))≠∅. For any {a mathematical formula}(I,J)∈SEQ(bS(P)), the program {a mathematical formula}PS(I,J) also has a model, e.g. {a mathematical formula}J∪(Σ∖S). Thus, {a mathematical formula}SEQ(PS(I,J))≠∅ by Proposition 7, and hence it follows {a mathematical formula}SEQ(PS)≠∅.  □
      </paragraph>
      <paragraph label="Proof of Theorem 5">
       We proceed by induction on the length {a mathematical formula}n≥1 of the splitting sequence. If {a mathematical formula}n=1, then we have {a mathematical formula}S=(S1) and {a mathematical formula}S′=∅, so {a mathematical formula}SEQS(P)=SEQS1(P) and, by Theorem 4, we obtain that {a mathematical formula}(X,Y)∈SEQS(P) if and only if {a mathematical formula}(X,Y)∈SEQ(P) and {a mathematical formula}(X,Y)|S∈SEQ(bS(P)), that is {a mathematical formula}(X,Y)|S1∈SEQ(bS1(P)). We assume that the statement is valid for a splitting sequence of length {a mathematical formula}n−1 and consider a splitting sequence {a mathematical formula}S=(S1,…,Sn) of length n. As usual, we put {a mathematical formula}S′=(S2,…,Sn). Then {a mathematical formula}(X,Y)∈SEQS(P) if and only if there exists {a mathematical formula}(I1,J1)∈SEQ(bS1(P)) such that {a mathematical formula}(X,Y)∈SEQS′(P1) and {a mathematical formula}(X,Y) is a maximal canonical HT-interpretation. Applying the induction hypothesis to {a mathematical formula}(X,Y)∈SEQS′(P1), we know that {a mathematical formula}(X,Y)∈SEQ(P1) and {a mathematical formula}(X,Y)|Sk∈SEQ(bSk(Pk−1)), for {a mathematical formula}k=2,…,n. Now {a mathematical formula}(X,Y)∈SEQ(P1) with {a mathematical formula}(I1,J1)∈SEQ(bS1(P)) and {a mathematical formula}(X,Y) is a maximal canonical HT-interpretation is equivalent, by definition, to {a mathematical formula}(X,Y)∈SEQS1(P). So that, by Theorem 4, {a mathematical formula}(X,Y)∈SEQ(P) and {a mathematical formula}(X,Y)|S1∈SEQ(bS1(P)). In conclusion we have demonstrated that {a mathematical formula}(X,Y)∈SEQS(P) if and only if {a mathematical formula}(X,Y)∈SEQ(P) and {a mathematical formula}(X,Y)|Sk∈SEQ(bSk(Pk−1)), for some {a mathematical formula}Pk−1, for {a mathematical formula}k=1,…,n.  □
      </paragraph>
      <paragraph label="Proof of Corollary 6">
       This is immediate from Proposition 15 and Corollary 4, given that as well-known {a mathematical formula}EQ(P)≠∅ for every stratified program.  □
      </paragraph>
     </section>
    </section>
    <section label="Appendix B">
     Section 6
     <paragraph label="Proof">
      The proof uses the following lemmas.Let P be a program and let{a mathematical formula}S=(S1,…,Sn)be a splitting sequence of P. We let as above{a mathematical formula}P0=Pand{a mathematical formula}Pk=(Pk−1)Sk(Ik,Jk), where{a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1)), with{a mathematical formula}k=1,…,n. Furthermore, we let{a mathematical formula}Ak={a|a∈Ik}∪{←nota|a∈Jk}∪{←a|a∈Sk∖Jk}. Then{a mathematical formula}for{a mathematical formula}k=1,…,n.We will prove this statement by induction on {a mathematical formula}k≥1. If {a mathematical formula}k=1, we obtain by definition that{a mathematical formula}We assume that the statement is true for {a mathematical formula}k=j−1 and consider {a mathematical formula}Pj. By definition we have that {a mathematical formula}Pj=(Pj−1)Sj(Ij,Jj)=Pj−1∖bSj(Pj−1)∪Aj. Now we can apply the inductive hypothesis on {a mathematical formula}Pj−1 and we obtain that{a mathematical formula} Since {a mathematical formula}Sj−1⊆Sj, we have that {a mathematical formula}bSj(Aj−1)=Aj−1, and so{a mathematical formula} Moreover since {a mathematical formula}bSj−1(P)⊆bSj(P), we can conclude that{a mathematical formula}  □Let P be a program. Let{a mathematical formula}S=(S1,…,Sn)be a splitting sequence of P. Let{a mathematical formula}P0=Pand let{a mathematical formula}Pkand{a mathematical formula}(Ik,Jk)for{a mathematical formula}k=1,…,n−1be defined as above. If{a mathematical formula}(X,Y)∈SEQ(Sk+1,…,Sn)(Pk), then{a mathematical formula}Ik⊆X,{a mathematical formula}Jk⊆Yand{a mathematical formula}(Sk∖Jk)∩Y=∅for{a mathematical formula}k=1,…,n−1.Let {a mathematical formula}(X,Y)∈SEQ(Sk+1,…,Sn)(Pk). We remember that {a mathematical formula}Pk=(Pk−1)Sk(Ik,Jk), where {a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1)), for {a mathematical formula}k=1,…,n and {a mathematical formula}P0=P. By Theorem 5 we have that {a mathematical formula}(X,Y)∈SEQ(Pk) and by Lemma 12,{a mathematical formula} So that {a mathematical formula}Ik⊆X, {a mathematical formula}Jk⊆Y and {a mathematical formula}(Sk∖Jk)∩Y=∅.  □Let P be a program. Let{a mathematical formula}S=(S1,…,Sn)be a splitting sequence of P such that{a mathematical formula}At(P)=Sn. If{a mathematical formula}(X,Y)∈SEQ(S1,…,Sn)(P), then there exists{a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1))for{a mathematical formula}k=1,…,nsuch that{a mathematical formula}with{a mathematical formula}(Ik∖Ik−1)⊆(Jk∖Jk−1)⊆(Sk∖Sk−1), for{a mathematical formula}k=2,…,n.We proceed by induction on the length {a mathematical formula}n≥1 of the splitting sequence. If {a mathematical formula}n=1, then {a mathematical formula}At(P)=S1 and {a mathematical formula}(X,Y)∈SEQS1(P) imply that there exists some {a mathematical formula}(I1,J1)∈SEQ(bS1(P)) such that {a mathematical formula}(X,Y)∈SEQ(PS1(I1,J1)), but {a mathematical formula}PS1(I1,J1)=P∖bS1(P)∪A1=A1, so that{a mathematical formula} that is {a mathematical formula}(X,Y)=(I1,J1).Now we suppose that the statement is valid for splitting sequence of length {a mathematical formula}n−1 and we consider {a mathematical formula}(X,Y)∈SEQ(S1,…,Sn)(P). Then there exists {a mathematical formula}(I1,J1)∈SEQ(bS1(P)) such that {a mathematical formula}(X,Y)∈SEQ(S2,…,Sn)(P1) and {a mathematical formula}At(P1)=Sn, so by the inductive hypothesis there exists {a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1)) for {a mathematical formula}k=2,…,n such that {a mathematical formula}(X,Y)=(I2∪(I3∖I2)∪…∪(In∖In−1),J2∪(J3∖J2)∪…∪(Jn∖Jn−1)) with {a mathematical formula}Ik∖Ik−1⊆Jk∖Jk−1⊆Sk∖Sk−1, for {a mathematical formula}k=3,…,n. Moreover, by Lemma 13, {a mathematical formula}I1⊆X, {a mathematical formula}J1⊆Y and {a mathematical formula}(S1∖J1)∩Y=∅ and because {a mathematical formula}(I2,J2)∈SEQ(bS2(P1)) we obtain that {a mathematical formula}I1⊆I2, {a mathematical formula}J1⊆J2 and {a mathematical formula}(S1∖J1)∩J2=∅. These last results imply that {a mathematical formula}I2∖I1⊆J2∖J1⊆S2∖S1.  □Let P be a program and let{a mathematical formula}S⊆At(P)such that both S and{a mathematical formula}At(P)∖Sare splitting sets of P. If for each constraint r,{a mathematical formula}At(r)⊆Sor{a mathematical formula}At(r)⊆At(P)∖S, then{a mathematical formula}The inclusion {a mathematical formula}SEQS(P)⊆SEQ(P) follows from Proposition 11. So we have just to prove that {a mathematical formula}SEQ(P)⊆SEQS(P).Let {a mathematical formula}(X,Y)∈SEQ(P). We want to prove that {a mathematical formula}(X∩S,Y∩S)∈SEQ(bS(P)).We know that {a mathematical formula}(X,Y)⊨bS(P). As S is a splitting set of P, {a mathematical formula}At(bS(P))⊆S and so {a mathematical formula}(X∩S,Y∩S)⊨bS(P).Now we prove the claim showing that {a mathematical formula}(X∩S,Y∩S) satisfies h-minimality and gap-minimality.If by contradiction some {a mathematical formula}I⊂X∩S exists such that {a mathematical formula}(I,Y∩S)⊨bS(P), then {a mathematical formula}X′=I∪(X∩(At(P)∖S))⊂X and {a mathematical formula}(X′,Y)⊨P which contradicts the h-minimality of {a mathematical formula}(X,Y).Similarly, if by contradiction, some {a mathematical formula}(I,J)⊨bS(P) exists such that {a mathematical formula}(I,J) satisfies h-minimality and {a mathematical formula}J∖I⊂(Y∩S)∖(X∩S), then having set {a mathematical formula}X′=I∪(X∩(At(P)∖S)) and {a mathematical formula}Y′=J∪(Y∩(At(P)∖S)), we obtain that {a mathematical formula}(X′,Y′)⊨P, satisfies the h-minimality and {a mathematical formula}Y′∖X′⊂Y∖X in contradiction to the gap-minimality of {a mathematical formula}(X,Y).Therefore {a mathematical formula}(X∩S,Y∩S)∈SEQ(bS(P)). Then, by Theorem 4, {a mathematical formula}(X,Y)∈SEQS(P); hence {a mathematical formula}SEQ(P)=SEQS(P).  □For any sets {a mathematical formula}M and {a mathematical formula}M′ of HT-models, define their product {a mathematical formula}M×M′ as the set of HT-models given by {a mathematical formula}M×M′={(X∪X′,Y∪Y′)|(X,Y)∈M, {a mathematical formula}(X′,Y′)∈M′}. Let P be a program in which each constraint r fulfills either{a mathematical formula}At(r)⊆Sor{a mathematical formula}At(r)⊆At(P)∖S. If both S and{a mathematical formula}At(P)∖Sare splitting sets of P, then{a mathematical formula}If {a mathematical formula}SEQ(bS(P))=∅, then{a mathematical formula} and{a mathematical formula}Let {a mathematical formula}(I,J)∈SEQ(bS(P)). For each rule {a mathematical formula}r∈bS(P), no atom of r is in some rule of {a mathematical formula}tS(P) and vice versa, that is {a mathematical formula}At(bS(P))∩At(tS(P))=∅. Hence{a mathematical formula} Then{a mathematical formula}  □The proof follows immediately from Lemma 15, Lemma 16.  □Let P be a program without cross-constraints. Let{a mathematical formula}(C1,…,Cn)and{a mathematical formula}(C1,…,Ci−1,Ci+1,Ci,Ci+2,…,Cn)be two topological orderings of{a mathematical formula}SCC(P). If we put{a mathematical formula}Sk=C1∪…∪Ckfor{a mathematical formula}k=1,…,nand{a mathematical formula}Si′=Si−1∪Ci+1then{a mathematical formula}In general we know that {a mathematical formula}bSi(P)∖bSi−1(P)=bSi(P∖bSi−1(P)). Hence it is sufficient to prove that {a mathematical formula}bSi+1(P)∖bSi(P)=bSi′(P)∖bSi−1(P).Let {a mathematical formula}r∈P, and assume that {a mathematical formula}r∈bSi+1(P) and {a mathematical formula}r∉bSi(P). If r is a constraint, then {a mathematical formula}At(r)∩Ci+1≠∅. As P has no cross-constraints, it follows that {a mathematical formula}At(r)∩Ci=∅. If r is not a constraint, then there exists some {a mathematical formula}a∈H(r) such that {a mathematical formula}a∈Ci+1. But because there is no edge between {a mathematical formula}Ci and {a mathematical formula}Ci+1, we obtain again that {a mathematical formula}At(r)∩Ci=∅. Therefore {a mathematical formula}r∈bSi−1∪Ci+1(P) and clearly {a mathematical formula}r∉bSi−1(P).Conversely, assume that {a mathematical formula}r∈bSi−1∪Ci+1(P) and {a mathematical formula}r∉bSi−1(P). Then {a mathematical formula}r∈bSi−1∪Ci+1(P)⊆bSi+1(P). Moreover {a mathematical formula}r∈bSi−1∪Ci+1(P) implies that {a mathematical formula}At(r)∩Ci=∅, and because {a mathematical formula}r∉bSi−1(P), it follows that {a mathematical formula}r∉bSi(P).  □Let P be a program without cross-constraints. Let{a mathematical formula}(C1,…,Cn)and{a mathematical formula}(C1,…,Ci−1,Ci+1,Ci,Ci+2,…,Cn)be two topological orderings of{a mathematical formula}SCC(P). If we put{a mathematical formula}Sk=C1∪…∪Ckfor{a mathematical formula}k=1,…,nand{a mathematical formula}Si′=Si−1∪Ci+1then{a mathematical formula}Let {a mathematical formula}(X,Y)∈SEQ(S1,…,Si−1,Si,Si+1,Si+2,…,Sn)(P). Since {a mathematical formula}At(P)=C1∪…∪Cn=Sn, by Lemma 14 we obtain that{a mathematical formula} where {a mathematical formula}(Ik,Jk)∈SEQ(bSk(Pk−1)) for {a mathematical formula}k=1,…,n, with{a mathematical formula} for {a mathematical formula}k=2,…,n.First we show that{a mathematical formula} We know that{a mathematical formula}Moreover, using Lemma 17, we obtain{a mathematical formula} And we note that{a mathematical formula} Now in the program {a mathematical formula}bSi+1(Pi) both {a mathematical formula}Si−1∪Ci+1 and {a mathematical formula}Ci are splitting sets and in particular{a mathematical formula} and{a mathematical formula} Therefore by Proposition 17 we obtain that{a mathematical formula} So we have that{a mathematical formula} and since{a mathematical formula} it follows{a mathematical formula}By Theorem 5, we know that if {a mathematical formula}(X,Y)∈SEQ(S1,…,Si−1,Si,Si+1,Si+2,…,Sn)(P), then{a mathematical formula}We want to prove that {a mathematical formula}(X,Y)∈SEQ(S1,…,Si−1,Si′,Si+1,Si+2,…,Sn)(P). That is, by Theorem 5:{a mathematical formula} So it remains to prove that{a mathematical formula}We know that{a mathematical formula} Now in this program both {a mathematical formula}Si and {a mathematical formula}Ci+1 are splitting sets and in particular{a mathematical formula} and{a mathematical formula} Therefore by Proposition 17 we obtain that{a mathematical formula} Now since {a mathematical formula}(Ii,Ji)∈SEQ(bSi(Pi−1)), we obtain that{a mathematical formula} In conclusion, we have proved that{a mathematical formula} The proof of the reverse inclusion is similar. □Theorem 6 is then proven as follows. Let {a mathematical formula}(Ci1,…,Cin)∈O(SG(P)). We define a function{a mathematical formula} Let {a mathematical formula}(Cj1,…,Cjn)∈O(SG(P)). If {a mathematical formula}Cir=Cjr for {a mathematical formula}r=1,…,l, {a mathematical formula}Cil+1≠Cjl+1 and there exists {a mathematical formula}k+1&gt;l+1 such that {a mathematical formula}Cjk+1=Cil+1, then{a mathematical formula} else {a mathematical formula}t(Ci1,…,Cin)(Cj1,…,Cjn)=(Cj1,…,Cjn)=(Ci1,…,Cin). This function is well-defined because there are no edges from {a mathematical formula}Cim to {a mathematical formula}Cil+1 for {a mathematical formula}m=l+2,…,n. That is there are no edges from {a mathematical formula}Cjk to {a mathematical formula}Cil+1, therefore {a mathematical formula}(Ci1,…,Cil,Cjl+1,…,Cjk−1,Cil+1,Cjk,Cjk+2,…,Cjn) is another topological ordering of {a mathematical formula}SCC(P). Moreover for each {a mathematical formula}(Cj1,…,Cjn)∈O(SG(P)), there exists some finite N such that{a mathematical formula} During the proof, in order not to introduce additional symbols, we shall denote the splitting sequence {a mathematical formula}Si with {a mathematical formula}(Ci1,…,Cin) and {a mathematical formula}Sj with {a mathematical formula}(Cj1,…,Cjn).Let N be such that {a mathematical formula}t(Ci1,…,Cin)N(Cj1,…,Cjn)=(Ci1,…,Cin). We will prove the theorem using induction on N. If {a mathematical formula}N=1, then {a mathematical formula}t(Ci1,…,Cin)(Cj1,…,Cjn)=(Ci1,…,Cin), i.e. {a mathematical formula}(Cj1,…,Cjn) and {a mathematical formula}(Ci1,…,Cin) differ at most by the exchange of two consecutive strongly connected components. Then, by Lemma 18, {a mathematical formula}SEQ(Ci1,…,Cin)(P)=SEQ(Cj1,…,Cjn)(P). Now we suppose that the theorem is valid for topological orderings {a mathematical formula}(Cs1,…,Csn) such that {a mathematical formula}t(Ci1,…,Cin)N−1(Cs1,…,Csn)=(Ci1,…,Cin). We consider {a mathematical formula}(Cj1,…,Cjn) such that {a mathematical formula}t(Ci1,…,Cin)N(Cj1,…,Cjn)=(Ci1,…,Cin). By definition of the function {a mathematical formula}t(Ci1,…,Cin), we know that{a mathematical formula} Therefore, by Lemma 18, we have that{a mathematical formula} But now {a mathematical formula}t(Ci1,…,Cin)N−1(t(Ci1,…,Cin)(Cj1,…,Cjn))=(Ci1,…,Cin) such that, by the induction hypothesis, we obtain that{a mathematical formula} In conclusion, we have proved that {a mathematical formula}SEQ(Cj1,…,Cjn)(P)=SEQ(Ci1,…,Cin)(P).  □
     </paragraph>
     <paragraph label="Proof of Theorem 7">
      First we observe that for every splitting set S of a program P, we can always write S as the union of some SCCs of P. More in detail, if {a mathematical formula}SCC(P)={C1,…,Cn}, then we can assume that {a mathematical formula}S=C1∪…∪Ck, where {a mathematical formula}C1, …, {a mathematical formula}Ck are consecutive in some topological ordering {a mathematical formula}(C1,…,Ck,…,Cn) of {a mathematical formula}SCC(P).By definition, we have that{a mathematical formula} where {a mathematical formula}Sj=∪i=1jCi, for {a mathematical formula}1≤j≤n; note that {a mathematical formula}S=Sk.If we explicate the computation of {a mathematical formula}SEQ(S1,…,Sn)(P) up to k-th union, we obtain{a mathematical formula} where {a mathematical formula}Mk is last in a sequence {a mathematical formula}Mi, {a mathematical formula}1≤i≤k of sets {a mathematical formula}Mi of HT-models {a mathematical formula}Mi=(Ii,Ji), over {a mathematical formula}Si, such that {a mathematical formula}M1=SEQ(bS1(P)) and {a mathematical formula}Mi+1=mc(⋃Mi∈MiSEQ((bSi+1(P)∖bSi(P))∪Mi), {a mathematical formula}1≤i&lt;k, where in abuse of notation “{a mathematical formula}∪Mi” stands for {a mathematical formula}∪{a|a∈Ii}∪{←nota|a∈Ji}∪{←a|a∈Si∖Ji}. Note that all {a mathematical formula}Mi≠Mi′∈Mi have incomparable gaps, i.e., {a mathematical formula}gap(Mi)⊈gap(Mi′).Now we show that the set {a mathematical formula}Mk coincides with {a mathematical formula}MSCC(bS(P)). Indeed, by definition, we know that{a mathematical formula} Therefore, applying k-times the definition of semi-equilibrium models relative to a splitting sequence, we obtain{a mathematical formula} where {a mathematical formula}Mk′ and {a mathematical formula}Mk′ are analogously defined to {a mathematical formula}Mk and {a mathematical formula}Mk using {a mathematical formula}bS(P) instead of P, i.e., {a mathematical formula}M1′=SEQ(bS1(bS(P))) and {a mathematical formula}Mi+1′=mc(⋃Mi′∈Mi′SEQ((bSi+1(bS(P))∖bSi(bS(P)))∪Mi′), {a mathematical formula}1≤i&lt;k. As {a mathematical formula}bSi(bS(P))=bSi(P) for each i, the {a mathematical formula}Mi and the {a mathematical formula}Mi′ coincide; as {a mathematical formula}bS(P)=bSk(P), we thus obtain from (B.2){a mathematical formula} here we use that the {a mathematical formula}Mk have incomparable gaps. This proves the claim that {a mathematical formula}Mk=MSCC(bS(P)).To prove the result, it remains by (B.1) to show that for each {a mathematical formula}Mk∈Mk,{a mathematical formula} We observe that the programs {a mathematical formula}Q=P∖bS(P)∪Mk and P have the same atoms but in general different SCCs. However it is easy to see that every atom in {a mathematical formula}a∈Sk induces a {a mathematical formula}SCC{a mathematical formula}Ca={a} w.r.t. Q, and thus {a mathematical formula}Sk=Ca1∪⋯∪Caℓ where {a mathematical formula}Sk={a1,…,aℓ}. Furthermore, Q contains only constraints r such that either {a mathematical formula}At(Q)⊆Sk or {a mathematical formula}At(Q)∩Sk=∅. As {a mathematical formula}(Ca1,…,Caℓ,Ck+1,…Cn) is a topological ordering of {a mathematical formula}SCC(Q), we obtain{a mathematical formula} where {a mathematical formula}Sai=⋃j≤iCaj. The last equality can be seen by noting that, for each {a mathematical formula}j=1,…,ℓ, we have {a mathematical formula}SEQ(bSaj(Q))={Mk|Saj} (where {a mathematical formula}Mk|Saj denotes the restriction of {a mathematical formula}Mk to {a mathematical formula}Saj) and thus for each {a mathematical formula}(Xj,Yj)∈SEQ(bSaj(Q)),{a mathematical formula} In conclusion, by replacing in Equation (B.1){a mathematical formula}Mk∈Mk with {a mathematical formula}(I,J)∈MSCC(bSk(P)) and {a mathematical formula}SEQ(Sk+1,…,Sn)(P∖bSk(P)∪Mk) with {a mathematical formula}MSCC(P∖bSk(P)∪(I,J)) and reminding that {a mathematical formula}Sk=S and {a mathematical formula}PS(I,J)=P∖bSk(P)∪(I,J), we have proved that{a mathematical formula}  □
     </paragraph>
     <paragraph label="Proof of Proposition 18">
      Suppose that {a mathematical formula}S=(S1,…,Sn), where {a mathematical formula}n≥1. Then there exists a splitting sequence {a mathematical formula}S≤′=(S1′,…,Sn′) induced by some topological ordering ≤ of {a mathematical formula}SG(P) such that {a mathematical formula}Si=Ski′, for some {a mathematical formula}1≤ki≤n′, for every {a mathematical formula}1≤i≤n; such a sequence can be obtained by refining {a mathematical formula}Si∖Si−1, {a mathematical formula}1≤i≤n where {a mathematical formula}S0=∅ along strongly connected components in {a mathematical formula}SG(P) to {a mathematical formula}Si,1,…,Si,ji such that {a mathematical formula}Si,ji=Si. As {a mathematical formula}MSCC(P)=SEQS′(P), the inclusion {a mathematical formula}MSCC(P)⊆SEQS(P) is then an immediate consequence of Theorem 5 (for given {a mathematical formula}(X,Y), {a mathematical formula}S′ imposes more conditions for membership in {a mathematical formula}SEQS′(P) than S for membership in {a mathematical formula}SEQS(P)); the equation {a mathematical formula}MSCC(P)=⋂S∈SQ(P)SEQS(P) follows as {a mathematical formula}S′∈SQ(P).  □
     </paragraph>
     <paragraph label="Proof">
      For the proof of Theorem 8, we use the following lemmas.Let P be a program. Let{a mathematical formula}MJC(P)={J1,…,Jm}. Let{a mathematical formula}(J1,…,Ji−1,Ji,Ji+1,Ji+2,…,Jm)and{a mathematical formula}(J1,…,Ji−1,Ji+1,Ji,Ji+2,…,Jm)be two topological orderings. If we put{a mathematical formula}Sk=J1∪…∪Jkfor{a mathematical formula}k=1,…,mand{a mathematical formula}Si′=Si−1∪Ji+1then{a mathematical formula}In general we know that {a mathematical formula}bSi(P)∖bSi−1(P)=bSi(P∖bSi−1(P)). So that is sufficient to prove that {a mathematical formula}bSi+1(P)∖bSi(P)=bSi′(P)∖bSi−1(P).Let {a mathematical formula}r∈P. We assume that {a mathematical formula}r∈bSi+1(P) and {a mathematical formula}r∉bSi(P).If r is not a constraint, then there exists some {a mathematical formula}a∈H(r) such that {a mathematical formula}a∈Ji+1. But because there is no edge among {a mathematical formula}Ji and {a mathematical formula}Ji+1, we obtain that {a mathematical formula}At(r)∩Ji=∅. Therefore {a mathematical formula}r∈bSi−1∪Ji+1(P) and clearly {a mathematical formula}r∉bSi−1(P).If r is a constraint then there exists {a mathematical formula}a∈(B+(r)∪B−(r))∩Ji+1. If, by contradiction, we assume that there exists some {a mathematical formula}b∈(B+(r)∪B−(r))∩Ji, then there exist {a mathematical formula}Ki,Ki+1∈SCC(P) such that {a mathematical formula}Ki+1⊆Ji+1 and {a mathematical formula}Ki⊆Ji with {a mathematical formula}r∈CKi,Ki+1(P). But because there is no edge among {a mathematical formula}Ji and {a mathematical formula}Ji+1, then there exists a topological ordering of strongly connected components of P that are in {a mathematical formula}Ji and {a mathematical formula}Ji+1, such that {a mathematical formula}Ki precedes {a mathematical formula}Ki+1. So there exists {a mathematical formula}(C1,…,Cn)∈O(P) in which {a mathematical formula}Cl=Ki and {a mathematical formula}Cl+1=Ki+1 for some {a mathematical formula}l=1,…,n−1 and moreover {a mathematical formula}At(r)⊆C1∪…∪Cl+1. Then {a mathematical formula}(Ki,Ki+1) is a joinable pair and therefore {a mathematical formula}Ki,Ki+1 are joinable components, but this contradicts the maximality of {a mathematical formula}Ji and {a mathematical formula}Ji+1. So that {a mathematical formula}(B+(r)∪B−(r))∩Ji=∅. That is {a mathematical formula}r∈bSi−1∪Ji+1(P) and clearly {a mathematical formula}r∉bSi−1(P).Conversely we assume that {a mathematical formula}r∈bSi−1∪Ci+1(P) and {a mathematical formula}r∉bSi−1(P). Then {a mathematical formula}r∈bSi−1∪Ci+1(P)⊆bSi+1(P). Moreover {a mathematical formula}r∈bSi−1∪Ci+1(P) implies that {a mathematical formula}At(r)∩Ci=∅, and because {a mathematical formula}r∉bSi−1(P), then {a mathematical formula}r∉bSi(P).  □Let P be a program. Let{a mathematical formula}MJC(P)={J1,…,Jm}. Let{a mathematical formula}(J1,…,Ji−1,Ji,Ji+1,Ji+2,…,Jm)and{a mathematical formula}(J1,…,Ji−1,Ji+1,Ji,Ji+2,…,Jm)be two topological orderings. If we put{a mathematical formula}Sk=J1∪…∪Jkfor{a mathematical formula}k=1,…,mand{a mathematical formula}Si′=Si−1∪Ji+1then{a mathematical formula}The proof is mutatis mutandis the same as that of Lemma 18, and one identifies {a mathematical formula}bSi′(P∖bSi−1(P)) and {a mathematical formula}bSi+1(P∖bSi(P)) using Lemma 19 instead of Lemma 15.  □The proof of Theorem 8 is the same as that of Theorem 6, but uses Lemma 20 instead of Lemma 18.  □
     </paragraph>
     <paragraph label="Proof of Theorem 9">
      The proof is very similar to the one of Theorem 7: under the premise, the MJCs which form S respectively the SCCs constituting them are in the initial segment of some topologic ordering, like the SCCs in the proof of Theorem 7. Thus the same line of argumentation applies.  □
     </paragraph>
     <paragraph label="Proof of Proposition 19">
      The proof is analogous to the one of Proposition 18. Similarly, for every {a mathematical formula}MJC-compatible split sequence {a mathematical formula}S=(S1,…,Sn), {a mathematical formula}n≥1, an {a mathematical formula}MJC-split sequence {a mathematical formula}S≤′=(S1′,…,Sn′) induced by some topological ordering ≤ of {a mathematical formula}JG(P) exists such that {a mathematical formula}Si=Ski′, for some {a mathematical formula}1≤ki≤n′, for every {a mathematical formula}1≤i≤n; we can obtain {a mathematical formula}S′ by refining {a mathematical formula}Si∖Si−1, {a mathematical formula}1≤i≤n where {a mathematical formula}S0=∅ along maximal joined components in {a mathematical formula}JP(P) to {a mathematical formula}Si,1,…,Si,ji such that {a mathematical formula}Si,ji=Si. As {a mathematical formula}MMJC(P)=SEQS′(P), {a mathematical formula}MMJC(P)⊆SEQS(P) follows from Theorem 5, and {a mathematical formula}MMJC(P)=⋂S∈MSQ(P)SEQS(P) follows as {a mathematical formula}S′∈MSQ(P).  □
     </paragraph>
    </section>
    <section label="Appendix C">
     Section 7
     <section label="C.1">
      <section-title>
       Hardness results for semi-equilibrium semantics
      </section-title>
      <paragraph>
       Several results about Problem MCH and INF for disjunctive program under semi-equilibrium model semantics ({a mathematical formula}S=(At(P))) can be shown using a reduction from deciding the validity of a quantified Boolean formula (QBF) of the form{a mathematical formula} where {a mathematical formula}X={x1…xr}, {a mathematical formula}Y={y1…ys} and {a mathematical formula}Z={z1…zt}. We may assume without loss of generality that {a mathematical formula}E(X,Y,Z)=⋀i=1m(li1∨li2∨li3) where each {a mathematical formula}lij is a literal over {a mathematical formula}X∪Y∪Z (i.e., 3-CNF form). We define a program {a mathematical formula}P0 with the following rules:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}p←li1⁎,li2⁎,li3⁎, where {a mathematical formula}lij⁎={v‾,if lij=vv,if lij=¬v and {a mathematical formula}v∈X∪Y∪Z;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}x←p and {a mathematical formula}x‾←p for each {a mathematical formula}x∈X;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}y∨y‾ for each {a mathematical formula}y∈Y;
       </list-item>
       <list-item label="4.">
        {a mathematical formula}x∨x‾ for each {a mathematical formula}x∈X.
       </list-item>
      </list>
      <paragraph>
       We assume for the moment that Z is void (i.e., {a mathematical formula}Z=∅); then one can show the following property [16]:{a mathematical formula} As {a mathematical formula}P0 is positive, {a mathematical formula}SEQ(P0)={(M,M)|M∈MM(P0)}; it follows from this that brave reasoning from the {a mathematical formula}SEQ-models of a positive disjunctive program, i.e., deciding {a mathematical formula}P⊨SEQb,tp, is {a mathematical formula}Σ2P-hard; furthermore, cautious reasoning {a mathematical formula}P⊨SEQc,fp, is {a mathematical formula}Π2P-hard.
      </paragraph>
      <paragraph>
       Now we construct a new program {a mathematical formula}P1 that is obtained by adding a fresh atom q in each rule head of {a mathematical formula}P0 and the following rules:
      </paragraph>
      <list>
       <list-item label="5.">
        {a mathematical formula}p′←p and
       </list-item>
       <list-item label="6.">
        {a mathematical formula}←notp′.
       </list-item>
      </list>
      <paragraph>
       It is easy to see that {a mathematical formula}{q} is a minimal model of {a mathematical formula}P1. Now the following property holds:{a mathematical formula} Clearly, the program is stratified; consequently, Problem MCH under {a mathematical formula}SEQ-semantics is {a mathematical formula}Π2P-hard for disjunctive and stratified disjunctive programs, which proves the hardness part of item (ii) in Theorem 10.
      </paragraph>
      <paragraph>
       Eventually, we consider the target case in which {a mathematical formula}Z≠∅. We construct a final program P given by the union of {a mathematical formula}P1 with the following rules:
      </paragraph>
      <list>
       <list-item label="7.">
        {a mathematical formula}z∨z‾ for each {a mathematical formula}z∈Z and
       </list-item>
       <list-item label="8.">
        {a mathematical formula}←z,notbz and {a mathematical formula}←z‾,notbz‾ for each {a mathematical formula}z∈Z where {a mathematical formula}bz and {a mathematical formula}bz‾ are fresh atoms.
       </list-item>
      </list>
      <paragraph>
       Intuitively, the effect of these rules is that in each {a mathematical formula}SEQ-model {a mathematical formula}(I,J), either {a mathematical formula}bz or {a mathematical formula}bz‾ but not both must be contained in {a mathematical formula}gap(I,J), for each {a mathematical formula}z∈Z; this serves to emulate quantification over Z. For each {a mathematical formula}Z′⊆Z, the HT-interpretation {a mathematical formula}(IZ,JZ)=({bz|z∈Z′}∪{q},{q,p′}∪{bz‾|z∈Z∖Z′}) is a HT-model of P; it will be a {a mathematical formula}SEQ-model of P precisely if {a mathematical formula}∀Y∃X.E(X,Y,Z=Z′) is true. Formally, one can show:{a mathematical formula} Note that the program P is stratified; it follows that brave reasoning under {a mathematical formula}SEQ-semantics is {a mathematical formula}Σ3P-hard for disjunctive and stratified disjunctive programs; this proves the respective hardness parts of item (i) in Theorem 11. For cautious reasoning from disjunctive and stratified disjunctive programs under {a mathematical formula}SEQ-semantics, {a mathematical formula}Π3P-hardness of item (ii) in Theorem 11 is shown by a slight extension of the reduction, which is carried out in Appendix C.2 to derive this result for fixed truth value v.
      </paragraph>
     </section>
     <section label="C.2">
      <section-title>
       Hardness results for problem INF with fixed truth value
      </section-title>
      <section label="C.2.1">
       <section-title>
        Brave reasoning
       </section-title>
       <paragraph>
        The construction in Section 7.2 for normal, stratified normal and hcf programs uses bt, but in no {a mathematical formula}SEQ-model any atom is true (all rules are constraints); thus we can add {a mathematical formula}b←nota and ask for b about the truth value f, and add further {a mathematical formula}c←notb and ask for c about the truth value t.
       </paragraph>
       <paragraph>
        For disjunctive programs, we consider the {a mathematical formula}Σ3P-hardness proof for brave reasoning under {a mathematical formula}SEQ-semantics in Appendix C.1. Then for the program P constructed from the QBF Φ and the particular atom q, we have that {a mathematical formula}P⊨SEQb,tq iff the QBF Φ evaluates to true, and {a mathematical formula}P⊨SEQb,tq is equivalent to {a mathematical formula}P⊨SEQb,btp′. Furthermore, q has never value bt in the {a mathematical formula}SEQ-models of the program P; if we let {a mathematical formula}P′=P∪{q′←notq}, then {a mathematical formula}P′⊨SEQb,fq′ iff {a mathematical formula}P⊨SEQb,tq. So for each fixed value v, brave inference from the {a mathematical formula}SEQ-models of a (stratified) disjunctive program is {a mathematical formula}Σ3P-hard; this trivially generalizes to {a mathematical formula}SEQ-models relative to arbitrary splitting sequences S.
       </paragraph>
      </section>
      <section label="C.2.2">
       <section-title>
        Cautious reasoning
       </section-title>
       <paragraph>
        For fixed truth value {a mathematical formula}v=bt, the cautious inference problem is for {a mathematical formula}SEQ-models easier than for a truth value given in the input:
       </paragraph>
       <paragraph label="Proposition 25">
        Given a program P and an atom a, deciding whether{a mathematical formula}P⊨SEQc,btais (i) in coNP for each of normal, normal stratified, and hcf P and (ii) in{a mathematical formula}Π2pfor disjunctive P.
       </paragraph>
       <paragraph>
        This holds because in this case, {a mathematical formula}P⊭SEQc,bta iff some h-minimal HT-model {a mathematical formula}(X,Y) of P exists such that {a mathematical formula}a∉Y∖X; such a h-minimal model can be guessed and verified in polynomial time in case (i) resp. in polynomial time with an NP oracle in case (ii).
       </paragraph>
       <paragraph>
        For the other truth values, the construction in Section 7.2 for normal, stratified normal and hcf programs uses truth value f for cautious reasoning, and as in no {a mathematical formula}SEQ-model any atom is true, we can add {a mathematical formula}b←nota and ask whether b has cautiously value t; if we add another split layer with a rule {a mathematical formula}b←notb,nota (such that {a mathematical formula}S=(S1,S2) and {a mathematical formula}b∈S2∖S1), then we can ask whether b has cautiously value bt.
       </paragraph>
       <paragraph>
        Regarding disjunctive programs, we had above in the programs P and {a mathematical formula}P′ for brave reasoning with fixed truth values t and f query atoms q resp. {a mathematical formula}q′ whose truth values are opposite in the {a mathematical formula}SEQ-models of {a mathematical formula}P′ and always true or false; so we immediately obtain the {a mathematical formula}Π3P-hardness for cautious reasoning. If we add another split layer with {a mathematical formula}b←notb,p similarly as above, then we can ask whether b has cautiously value bt.
       </paragraph>
      </section>
     </section>
     <section label="C.3">
      <section-title>
       Constructing and recognizing canonical splitting sequences
      </section-title>
      <paragraph label="Proof of Proposition 20">
       Let P be a program. First we prove that conditions (i) and (ii) in Definition 12 imply that there is no path from {a mathematical formula}K1 to {a mathematical formula}K2 and vice versa. By contradiction, first suppose that there is a path from {a mathematical formula}K1 to {a mathematical formula}K2, i.e., there exist {a mathematical formula}K1′,…,Km′∈SCC(P) such that {a mathematical formula}K1=K1′, {a mathematical formula}Km′=K2 and {a mathematical formula}(Ki′,Ki+1′)∈ESG for {a mathematical formula}1≤i&lt;m. As in each topological ordering {a mathematical formula}(C1,…,Cn)∈O(SG(P)){a mathematical formula}Ki+1′ must precede {a mathematical formula}Ki′, for {a mathematical formula}1≤i&lt;m, it follows that {a mathematical formula}K2 precedes {a mathematical formula}K1, which contradicts condition (i). Otherwise, suppose that there exists some path from {a mathematical formula}K2 to {a mathematical formula}K1. Let {a mathematical formula}K1′,…,Km′∈SCC(P) be an arbitrary such path, i.e., {a mathematical formula}K1′=K2, {a mathematical formula}(Ki′,Ki+1′)∈ESG for {a mathematical formula}1≤i&lt;m and {a mathematical formula}Km′=K1. By condition (ii) we know that {a mathematical formula}(K2,K1)∉ESG. Hence {a mathematical formula}m&gt;2 and {a mathematical formula}Km−1′≠K1, {a mathematical formula}Km−1′≠K2; thus in every topological ordering {a mathematical formula}(C1,…,Cn)∈O(SG(P)), {a mathematical formula}K1 precedes {a mathematical formula}Km−i′ and {a mathematical formula}Km−i′ precedes {a mathematical formula}K2, which contradicts condition (i).Now we prove that the disconnectedness hypothesis implies conditions (i) and (ii). As there is no path from {a mathematical formula}K2 to {a mathematical formula}K1, condition (ii) trivially holds. Moreover for each topological ordering of {a mathematical formula}SCC(P) there exist maximal (possibly empty) sets {a mathematical formula}Ai⊆SCC(P) such that for each {a mathematical formula}Ki′∈Ai, {a mathematical formula}Ki′ precedes {a mathematical formula}Ki, {a mathematical formula}i=1,2. Because there is no path from {a mathematical formula}K1 to {a mathematical formula}K2, it follows that {a mathematical formula}K2∉A1 and because there is no path from {a mathematical formula}K2 to {a mathematical formula}K1, it follows that {a mathematical formula}K1∉A2. Therefore we can construct a topological ordering in which all strongly connected components in {a mathematical formula}A1∪A2 precede {a mathematical formula}K1 (this is possible because if there exists some {a mathematical formula}K∈A2 such that {a mathematical formula}K1 precedes K, then {a mathematical formula}K1 precedes K and K precedes {a mathematical formula}K2; this contradicts the hypothesis that no path from {a mathematical formula}K2 to {a mathematical formula}K1 exists), and {a mathematical formula}K1 precedes immediately {a mathematical formula}K2, i.e., condition (i) holds (this is possible because there is no {a mathematical formula}K∈A1 such that {a mathematical formula}K2 precedes K).  □
      </paragraph>
      <paragraph label="Proof of Corollary 10">
       (⇒) If {a mathematical formula}(K1,K2) is a joinable pair witnessed by r, then by Proposition 20{a mathematical formula}K1 and {a mathematical formula}K2 are disconnected in {a mathematical formula}SG(P); i.e., they are incomparable in the partial order on {a mathematical formula}SCC(P) induced by {a mathematical formula}SG(P). By condition (iii), {a mathematical formula}At(r)⊆C1∪⋯∪Cs+1 holds with {a mathematical formula}Cs=K1 and {a mathematical formula}Cs+1=K2; as every SCC {a mathematical formula}C≠K1,K2 such that {a mathematical formula}At(r)∩C≠∅ occurs in {a mathematical formula}C1,…,Cs−1, no path in {a mathematical formula}SG(P) from C can reach {a mathematical formula}K1 or {a mathematical formula}K2; consequently, {a mathematical formula}K1 and {a mathematical formula}K2 are maximal SCCs in {a mathematical formula}SG(P) such that {a mathematical formula}At(r)∩C≠∅.(⇐) Suppose without loss of generality that {a mathematical formula}K1=C1 and {a mathematical formula}K2=C2. Then, {a mathematical formula}K1 and {a mathematical formula}K2 must be disconnected; hence by Proposition 20, {a mathematical formula}K1 and {a mathematical formula}K2 satisfy condition (i) and (ii) of a joinable pair. Furthermore, as all {a mathematical formula}Ci,Cj, {a mathematical formula}1≤i≠j≤l, must be pairwise disconnected, by extending the argument in the proof of Proposition 20, we can build from a topological ordering {a mathematical formula}≤=(C1,…,Cn) of {a mathematical formula}SG(P) another topological ordering of {a mathematical formula}SG(P) in which all SCCs in {a mathematical formula}A=⋃i=1lAi∪{C3,…,Cl} precede {a mathematical formula}K1 and {a mathematical formula}K1 immediately precedes {a mathematical formula}K2, where {a mathematical formula}Ai={K∈SCC(P)|K&lt;Ci}; this is possible since no {a mathematical formula}K∈A exists such that {a mathematical formula}K2 precedes K. As {a mathematical formula}A∪{C1,C2} must contain all SCCs C such that {a mathematical formula}At(r)∩C≠∅, it follows that condition (iii) holds; hence {a mathematical formula}(K1,K2) is a joinable pair.  □
      </paragraph>
      <paragraph label="Proof of Theorem 14">
       Regarding the time complexity, we note the following:In Step 1, {a mathematical formula}DG(P), {a mathematical formula}SCC(P) and {a mathematical formula}SG(P) are constructable in linear time;We can compute the SCCs {a mathematical formula}C1r,…,Clr efficiently, e.g. by using a stratified program {a mathematical formula}Pr with the following rules:
       <list>
        {a mathematical formula}rj←, for each {a mathematical formula}Cj∈VSG such that {a mathematical formula}Cj∩At(r)≠∅;{a mathematical formula}rj←ri and {a mathematical formula}n_max_rj←ri, for each {a mathematical formula}(Ci,Cj)∈ESG;{a mathematical formula}max_rj←rj,notn_max_rj, for each {a mathematical formula}Ci∈VSG.Step 3 is clearly feasible in linear time; also Step 4 (iterative merging the
       </list>
       <paragraph>
        {a mathematical formula}J1, {a mathematical formula}J2) is feasible (if properly done) in linear time, and similarly Step 5 given {a mathematical formula}MJC(P) and {a mathematical formula}SG(P).Thus in total, {a mathematical formula}MJC(P) and {a mathematical formula}JG(P) are computable in time {a mathematical formula}O(cs⋅‖P‖), which proves the result.  □
       </paragraph>
      </paragraph>
     </section>
    </section>
    <section label="Appendix D">
     Section 8
     <paragraph label="Proof of Theorem 15">
      The proof proceeds as follows. We first show that (1) the models of {a mathematical formula}PE correspond to the HT-models {a mathematical formula}(X,Y) of P via {a mathematical formula}⋅E; next, we establish that (2) for every minimal model {a mathematical formula}PE, the corresponding HT-model of P is h-minimal and (3) that every {a mathematical formula}SEQ-model of P is among the models in (2), i.e., {a mathematical formula}{(X,Y)E|(X,Y)∈SEQ(P)}⊆MM(PE). As the {a mathematical formula}E-violation set {a mathematical formula}V(I) of any model {a mathematical formula}I=(X,Y)E of {a mathematical formula}PE corresponds to the gap of {a mathematical formula}(X,Y) (precisely, {a mathematical formula}V(I)=Egap(X,Y)), it follows that {a mathematical formula}I∈MM(PE) has a ⊆-minimal {a mathematical formula}E-violation set, i.e., is an evidential stable model of P, iff {a mathematical formula}(X,Y) is a {a mathematical formula}SEQ-model of P.As for (1), it is readily seen that for every HT-model {a mathematical formula}(X,Y) of P, {a mathematical formula}I=(X,Y)E=X∪EY is a model of {a mathematical formula}PE: all rules (2) are satisfied as {a mathematical formula}Y⊨P, and all rules (3) as {a mathematical formula}X⊆Y. Finally for the rules (1), as {a mathematical formula}(X,Y)⊨r, either {a mathematical formula}H(r)∩X≠∅, or {a mathematical formula}B+(r)⊈Y (which implies {a mathematical formula}B+(r)⊈X), or {a mathematical formula}B−(r)∩Y≠∅; hence I satisfies the rules (1). The proof of the converse, for every model I of {a mathematical formula}PE, {a mathematical formula}β(I) is a HT-model of P, is similar.Regarding (2), if {a mathematical formula}I∈MM(PE), in particular no model {a mathematical formula}J⊂I of {a mathematical formula}PE exists such that {a mathematical formula}I∖Σ=J∖Σ; thus if {a mathematical formula}β(I)=(X,Y), no HT-model {a mathematical formula}(X′,Y) of P exists such that {a mathematical formula}X′⊂X.As for (3), towards a contradiction assume that some {a mathematical formula}(X,Y)∈SEQ(P) fulfills {a mathematical formula}I=(X,Y)E∉MM(PE). Hence, some {a mathematical formula}J=(X′,Y′)E∈MM(PE) exists such that {a mathematical formula}J⊂I. As {a mathematical formula}X′⊆X, {a mathematical formula}Y′⊆Y, and {a mathematical formula}(X,Y) is h-minimal, it follows that {a mathematical formula}Y′⊂Y. As {a mathematical formula}PY⊆PY′ it follows that {a mathematical formula}X′⊨PY; since {a mathematical formula}X∈MM(PY) and {a mathematical formula}X′⊆X, it follows {a mathematical formula}X′=X. Therefore, {a mathematical formula}gap(X′,Y′)⊂gap(X,Y); as by (2) {a mathematical formula}(X′,Y′) is h-minimal, {a mathematical formula}(X,Y)∉SEQ(P), which is a contradiction. This proves the result.  □
     </paragraph>
     <paragraph label="Proof of Proposition 22">
      {a mathematical formula}(⊆) If {a mathematical formula}M=(X,Y) is a {a mathematical formula}SEQ-model of {a mathematical formula}Pwf, then M is a h-minimal model of {a mathematical formula}Pwf and {a mathematical formula}gap(M)⊆gap(WF(Pwf))=gap(WF(P)). Corollary 11 implies that {a mathematical formula}M⊑WF(Pwf))=WF(P)=(I,J), and thus {a mathematical formula}Y⊆J. By antimonotonicity of {a mathematical formula}γP(.), we have {a mathematical formula}γP(Y)⊇γP(J)=I, and thus {a mathematical formula}γPwf(Y)=γP(Y)∪I=γP(Y)=X. Thus M is also a h-minimal model of P. If M were not a {a mathematical formula}SEQ-model of P, then by Corollary 11 some refinement {a mathematical formula}M′ of {a mathematical formula}WF(P) with {a mathematical formula}gap(M′)⊂gap(M) would be a {a mathematical formula}SEQ-model of P. But {a mathematical formula}M′ would then be a h-minimal model of {a mathematical formula}Pwf and contradict that M is a {a mathematical formula}SEQ-model of {a mathematical formula}Pwf. Thus M is a {a mathematical formula}SEQ-model of P.{a mathematical formula}(⊇) Let M be a {a mathematical formula}SEQ-model of P such that {a mathematical formula}gap(M)⊆gap(WF(P)). Then by Corollary 11M refines {a mathematical formula}WF(P) and thus is clearly a model of {a mathematical formula}Pwf, and moreover h-minimal. If M were not a {a mathematical formula}SEQ-model of {a mathematical formula}Pwf, then some {a mathematical formula}SEQ-model {a mathematical formula}M′ of {a mathematical formula}Pwf with smaller gap exists; we can then as in the case {a mathematical formula}(⊆) infer that {a mathematical formula}M′ is also a h-minimal model of P, which contradicts that M is a {a mathematical formula}SEQ-model of P.  □
     </paragraph>
     <paragraph label="Proof of Proposition 23">
      Consider any splitting sequence {a mathematical formula}S=(S1,S2,…) of the program P and let {a mathematical formula}M=(X,Y) be any {a mathematical formula}SEQ-model of P such that {a mathematical formula}M⊑WF(P) (by Corollary 11 such an M exists). Let {a mathematical formula}M1=M|S1 and {a mathematical formula}P1=bS1(P).Then, {a mathematical formula}M1 is a HT-model of {a mathematical formula}P1 and moreover h-minimal for {a mathematical formula}P1 (for otherwise, M would not be h-minimal for P: we could make X on {a mathematical formula}S1 smaller, as we can keep the same valuation for the atoms in {a mathematical formula}Σ∖S1; note that {a mathematical formula}PY is positive and atoms from {a mathematical formula}S1 occur in {a mathematical formula}tS1(P) only in rule bodies). Furthermore, we have {a mathematical formula}M1⊑WF(P)|S1. Now some {a mathematical formula}SEQ-model {a mathematical formula}N1=(X1,Y1) of {a mathematical formula}P1 must exist such that {a mathematical formula}gap(N1)⊆gap(M1); as {a mathematical formula}gap(M1)⊆gap(WF(P)|S1), Corollary 11 and Lemma 5 imply that {a mathematical formula}N1⊑WF(P1) (observe that {a mathematical formula}WF(P)|S1=WF(P1), which follows from items 1 and 2 of Lemma 5).If we consider the program {a mathematical formula}P2=PS1(X1,Y1), then by an inductive argument on the length of the splitting sequence it has some {a mathematical formula}SCC-model {a mathematical formula}N2 w.r.t. {a mathematical formula}S′=(S2,…,Sn) such that {a mathematical formula}N2⊑WF(P2), provided {a mathematical formula}WF(P2) exists; however, {a mathematical formula}PS1(X1,Y1) adds a constraint {a mathematical formula}←nota for each {a mathematical formula}a∈Y1∖X1, and as a does not occur in any rule head of {a mathematical formula}P2, {a mathematical formula}WF(P2) does not exist if {a mathematical formula}X1⊂Y1. To address this, we use in the argument a variant of the transformation {a mathematical formula}PS1(X1,Y1), denoted {a mathematical formula}PˆS1(X1,Y1), that adds a rule {a mathematical formula}a←nota for each {a mathematical formula}a∈Y1 to {a mathematical formula}PS1(X1,Y1); clearly, {a mathematical formula}PS1(X1,Y1) and {a mathematical formula}PˆS1(X1,Y1) have the same splitting sets and the same {a mathematical formula}SEQ-models w.r.t. any splitting sequence; let {a mathematical formula}Pˆ2=PˆS1(X1,Y1). Then we claim that {a mathematical formula}WF(Pˆ2) exists and {a mathematical formula}WF(Pˆ2)⊑WF(P) holds. Indeed, consider the constraint-free part {a mathematical formula}P′ of P; then {a mathematical formula}WF(P′)=WF(P) and, if {a mathematical formula}Q′ denotes the (constraint-free) program for {a mathematical formula}P′ according to item 2 of Lemma 5, we have {a mathematical formula}WF(Q′)=WF(P′)=WF(P). If we add to {a mathematical formula}Q′ all constraints of P, then the resulting program Q fulfills {a mathematical formula}WF(Q)=WF(P). If we modify Q by (i) adding from {a mathematical formula}PˆS1(X1,Y1) all facts {a mathematical formula}a∈X1 and all constraints {a mathematical formula}{a←nota|a∈Y1}∪{←a|a∈S1∖Y1}, and (ii) remove all rules {a mathematical formula}a←nota such that {a mathematical formula}a∈S1∖Y1, the resulting program {a mathematical formula}Q″ is such that {a mathematical formula}WF(Q″)⊑WF(Q)=WF(P) if {a mathematical formula}WF(Q″) exists, as assigning any atoms in {a mathematical formula}gap(WF(P)) true or false does not affect the already assigned atoms. But as every constraint r in P has some body literal that is false in {a mathematical formula}WF(P), this holds also for {a mathematical formula}Q″, and thus {a mathematical formula}WF(Q″) exists. Now we note that {a mathematical formula}Q″=Pˆ2; this proves the claim.Consequently, {a mathematical formula}N2 is an {a mathematical formula}SCC-model of {a mathematical formula}Pˆ2 and {a mathematical formula}N2⊑WF(Pˆ2)⊑WF(P) holds. Now the {a mathematical formula}SEQS-models of P are, by definition,{a mathematical formula} If the model {a mathematical formula}N2 appears in this set, then it is an {a mathematical formula}SEQS-model of P that refines {a mathematical formula}WF(P) and proves the first claim of the proposition. Otherwise, some {a mathematical formula}SEQS-model {a mathematical formula}N′ of P must exist such that {a mathematical formula}gap(N′)⊂gap(N2); as {a mathematical formula}N′ is a {a mathematical formula}SEQ-model of P and {a mathematical formula}gap(N′)⊆gap(WF(P)), it follows from Corollary 11 that {a mathematical formula}N′⊑WF(P), and also in this case an {a mathematical formula}SEQS-model of P that refines {a mathematical formula}WF(P) exists; this proves the first claim of the proposition. As for the second claim, by Corollary 11 every {a mathematical formula}SEQ-model M of P, and thus in particular every {a mathematical formula}SEQS-model M of P such that {a mathematical formula}gap(M)⊆gap(WF(P)) satisfies {a mathematical formula}M⊑WF(P); thus if we let M in the argument above be an arbitrary {a mathematical formula}SEQS-model of P, we arrive at {a mathematical formula}N2=M and thus the second claim holds. This proves the result.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>