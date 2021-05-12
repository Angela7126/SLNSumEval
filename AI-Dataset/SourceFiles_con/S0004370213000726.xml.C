<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Complexity issues related to propagation completeness.
   </title>
   <abstract>
    Knowledge compilation is a process of adding more information to a knowledge base in order to make it easier to deduce facts from the compiled base than from the original one. One type of knowledge compilation occurs when the knowledge in question is represented by a Boolean formula in conjunctive normal form (CNF). The goal of knowledge compilation in this case is to add clauses to the input CNF until a logically equivalent propagation complete CNF is obtained. A CNF is called propagation complete if after any partial substitution of truth values all logically entailed literals can be inferred from the resulting CNF formula by unit propagation. The key to this type of knowledge compilation is the ability to generate so-called empowering clauses. A clause is empowering for a CNF if it is an implicate and for some partial substitution of truth values it enlarges the set of entailed literals inferable by unit propagation. In this paper we study several complexity issues related to empowering implicates, propagation completeness, and its relation to resolution proofs. We show several results: (a) given a CNF and a clause it is co-NP complete to decide whether the clause is an empowering implicate of the CNF, (b) given a CNF it is NP-complete to decide whether there exists an empowering implicate for it and thus it is co-NP complete to decide whether a CNF is propagation complete, and (c) there exist CNFs to which an exponential number of clauses must be added to make them propagation complete.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      One of the most studied problems in computer science, both theoretical and applied, is the satisfiability problem for CNF formulas (SAT). The difficulty of SAT depends on the class of CNF formulas to which the input formula belongs. There are various techniques and algorithms for SAT for different classes of CNF formulas ranging from linear algorithms for Horn, quadratic (2-CNF) and SLUR formulas [1], [2] to the very complex variants of the exponential DPLL [3], [4] and CDCL [5], [6], [7], [8] procedures implemented in general purpose SAT solvers. Even the most complicated SAT solvers usually perform a task called unit propagation [3]. The goal of unit propagation is to infer as many logically entailed literals as possible from a partial truth assignment and the input formula. Although in general unit propagation is not a complete method (it does not infer all logically entailed literals), it is complete for the class of propagation complete (PC) CNF formulas [9].
     </paragraph>
     <paragraph>
      PC formulas play an important role also in constraint programming, or more specifically, in CNF encodings of global constraints. There is a strong connection between propagation completeness of the CNF encoding and domain consistency of the encoded constraint [10], [11]. It has been studied for several concrete global constraints such as the AllDifferent constraint [12], the Sequence constraint [13], Regular, Among, and Generalized Sequence[10], or the Grammar constraints [14].
     </paragraph>
     <paragraph>
      Some SAT solvers try to avoid searching in the state subspaces with no solution by learning from conflicts, i.e. by performing conflict driven clause learning (CDCL) [5], [6], [7], [8], the name CDCL is also used for the complete algorithm solving SAT problem. It is useful to learn clauses (called empowering implicates[9], [15]) that allow unit propagation to infer more logically entailed literals after such a clause is added to the CNF formula than it was possible to infer before the addition. Therefore, to speed up the CDCL SAT solver search for a satisfying assignment, it is often very useful to learn (generate) empowering implicates and add them to the input CNF formula. Let us mention that todayʼs most successful SAT solvers for real-world applications are the ones using CDCL procedure.
     </paragraph>
     <paragraph>
      This process of adding empowering implicates to a CNF formula can be viewed as a special type of knowledge compilation where both the input and the output representation of the knowledge is a CNF formula. In general, knowledge compilation is a process of adding more information to a given knowledge representation in order to make it computationally easier to infer facts from the compiled representation [16], [17], or a process of transforming a given knowledge representation into another knowledge representation which is more tractable with respect to fact deduction, such as transforming a CNF into a BDD [18]. Nevertheless, in this paper we are interested only in the very limited case of knowledge compilation that rests in adding empowering implicates to a CNF.
     </paragraph>
     <paragraph>
      It has been shown in [9], along with other properties of PC formulas, that a formula φ is PC if and only if there is no empowering implicate for φ. However, several complexity issues directly connected to propagation completeness and empowering implicates are left open in [9]. A short list of such questions is the following:
     </paragraph>
     <list>
      <list-item label="1.">
       Given a CNF formula φ and a clause C, what is the complexity of deciding whether C is an empowering implicate for φ?
      </list-item>
      <list-item label="2.">
       Given a CNF formula φ that is not PC, how difficult is it to generate an empowering implicate for φ by resolution, where the “level of difficulty” is measured by the length of the resolution proof?
      </list-item>
      <list-item label="3.">
       Given a CNF formula φ, what is the complexity of deciding whether there exists an empowering implicate for φ?
      </list-item>
      <list-item label="4.">
       Given a CNF formula φ that is not PC, how many empowering implicates is it necessary to add to φ in order to make it PC?
      </list-item>
     </list>
     <paragraph>
      In this paper we tackle all of the above listed problems. After reviewing basic definitions and notation in Section 2, we derive several simple properties of empowering implicates in Section 3. We address the following four questions as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       In Section 3 we show that the first problem is co-NP complete. This is not a very difficult result, however, to the best of our knowledge, it was not stated in the related literature yet.
      </list-item>
      <list-item label="2.">
       In Section 4 we tackle the second problem. We prove that for a non-PC CNF formula with s occurrences of literals there always exists a resolution proof of length {a mathematical formula}O(s) of some empowering implicate. On the other hand, we construct examples of CNF formulas where a resolution proof of length {a mathematical formula}Ω(s) is needed for any empowering implicate, which means that {a mathematical formula}Θ(s) is an asymptotically tight bound for this problem. It is important to note that the upper bound result does not require the derived empowering implicate to be prime. We show (by a simple modification of results concerning refutation proofs [19], [20]) that there exist CNF formulas such that in order to derive any prime empowering implicate of such CNF a resolution proof of an exponential length is needed.
      </list-item>
      <list-item label="3.">
       Section 5 contains the main results of this paper which are connected to the third problem. It was proved in [9] that deciding about an existence of an empowering implicate is in {a mathematical formula}Σ2p. Using the results from Section 4 we strengthen this result by showing that the problem belongs to {a mathematical formula}Σ1p=NP. Given the equivalence between propagation completeness and non-existence of empowering implicates proved in [9], this immediately implies that testing propagation completeness belongs to co-NP. Then we proceed with the hardness proof for this problem. We present a reduction from a well-known NP-complete 3-dimensional matching problem which proves that deciding for a CNF formula whether there exists an empowering implicate for it is NP-hard (and thus testing propagation completeness is coNP-hard).
      </list-item>
      <list-item label="4.">
       The fourth question is answered in Section 5 as well by showing that there exist CNF formulas where an exponential number (both with respect to the number of variables and the number of clauses) of empowering implicates must be added in order to arrive at a PC formula. This strengthens the superpolynomial bound which follows from a combination of results in [9] and [21] using a superpolynomial lower bound for certain monotone circuits from [22]. The connection is discussed in detail in Section 2.5.
      </list-item>
     </list>
     <paragraph>
      We close the paper by giving few concluding remarks in Section 6.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Definitions
     </section-title>
     <section label="2.1">
      <section-title>
       Basic definitions
      </section-title>
      <paragraph>
       A Boolean function of n variables is a mapping {a mathematical formula}f:{0,1}n→{0,1}. We say that a Boolean function f is satisfiable if there is a vector {a mathematical formula}x→∈{0,1}n such that {a mathematical formula}f(x→)=1. A literal is either a variable (x, called positive literal) or its negation (¬x or {a mathematical formula}x¯, called negative literal). A clause is a disjunction of literals. We assume that no clause contains both positive and negative literals of the same variable. A clause which contains just one literal is called a unit clause. Formula φ is in conjunctive normal form (CNF) if it is a conjunction of clauses (we also say that φ is a CNF formula). We shall often treat a clause as a set of its literals and a CNF formula as a set of its clauses. It is a well-known fact that every Boolean function can be represented by a CNF formula (see e.g. [23]). A CNF formula φ is called a Horn formula if every clause in φ has at most one positive literal. A quadratic CNF formula (also called 2-CNF formula) is a CNF formula where each clause contains at most two literals. If two CNF formulas {a mathematical formula}φ1 and {a mathematical formula}φ2 define the same function, we say that they are equivalent and we denote this fact with {a mathematical formula}φ1≡φ2.
      </paragraph>
      <paragraph>
       Clause C is called an implicate of f if every assignment {a mathematical formula}x→∈{0,1}n satisfying f (i.e. {a mathematical formula}f(x→)=1) also satisfies C (i.e. {a mathematical formula}C(x→)=1). We use notation {a mathematical formula}f⊨C to denote that C is an implicate of f. We also say that C is logically entailed by f. Since every CNF formula φ represents a function, we shall often use {a mathematical formula}φ⊨C to denote the fact that C is an implicate of the function represented by φ. We shall also say that C is an implicate of φ or that it is logically entailed by φ. A clause is a special case of a CNF formula and thus for two clauses {a mathematical formula}C1 and {a mathematical formula}C2 we can also use {a mathematical formula}C1⊨C2. This is possible only if literals contained in {a mathematical formula}C1 are also contained in {a mathematical formula}C2. In this case we say that clause{a mathematical formula}C1subsumes clause{a mathematical formula}C2. C is a prime implicate of a function f if it is an implicate of f and there is no other implicate {a mathematical formula}C′ of f subsuming C. We say that CNF formula φ is prime if it contains only prime implicates. A special case of prime CNF formula is the canonical CNF formula of f (also called a canonical representation of f), which consists of all the prime implicates of f.
      </paragraph>
      <paragraph>
       Given a CNF formula φ and a clause C we define IsImplicate({a mathematical formula}φ,C) as the problem of deciding whether C is an implicate of φ. It is well known that this problem is co-NP complete (co-SAT is a special case of IsImplicate({a mathematical formula}φ,C) in which C is an empty clause).
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Resolution
      </section-title>
      <paragraph>
       We say that two clauses have a conflict in variable x if there is a positive occurrence of x in one clause and a negative occurrence in the other. Two clauses {a mathematical formula}C1=(C1˜∨x) and {a mathematical formula}C2=(C2˜∨x¯) are resolvable over x if {a mathematical formula}C1˜ and {a mathematical formula}C2˜ do not have a conflict in any variable. We write {a mathematical formula}R(C1,C2)=C1˜∨C2˜ and this disjunction is called a resolvent of the parent clauses{a mathematical formula}C1 and {a mathematical formula}C2. A resolution in which one of the parent clauses is a unit clause is called a unit resolution. A resolution in which the parent clauses have no common literal is called a non-merge resolution, otherwise it is a merge resolution.
      </paragraph>
      <paragraph>
       Let φ be a CNF formula representing a Boolean function f, we say that C can be derived from φ by a series of resolutions if there is a sequence of clauses {a mathematical formula}C1,…,Ck=C such that every {a mathematical formula}Ci, {a mathematical formula}1⩽i⩽k, either belongs to φ, or {a mathematical formula}Ci=R(Cj1,Cj2), where {a mathematical formula}j1,j2&lt;i. Such a series of resolutions is also called a resolution proof of C from φ. Resolution proof of a contradiction (i.e. an empty clause ⊥) from formula φ is also called a resolution refutation. A resolution proof in which every resolution is unit is called a unit resolution proof, a unit resolution proof of a contradiction ⊥ from φ is called a unit refutation and if such a proof exists for φ, then this formula is called unit refutable. This fact is denoted by {a mathematical formula}φ⊢1⊥. If a unit clause (literal) x can be derived by unit resolutions then we write {a mathematical formula}φ⊢1x. The length of a resolution proof is the number of clauses in the sequence.
      </paragraph>
      <paragraph>
       It is a well known fact that for any Boolean function the resolvent of two implicates is again an implicate (see e.g. [24]). Another well known fact is that every prime implicate of f can be derived from φ by a series of resolutions (see e.g. [24]).
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Unit propagation and refutation
      </section-title>
      <paragraph>
       Unit propagation is an iterative procedure which in each step selects a unit clause (a literal), removes each clause containing this literal, and removes the complementary literal from the remaining clauses (i.e. satisfies the selected literal). This process iterates until an empty clause (a contradiction) is derived or there is no unit clause in the formula. Unit propagation can be performed in linear time [25]. It is a well-known fact that if {a mathematical formula}φ⊢1x (where x is an arbitrary literal), then unit propagation on φ satisfies x or derives contradiction. On the other hand, if x is satisfied during unit propagation, then {a mathematical formula}φ⊢1x.
      </paragraph>
      <paragraph>
       We say that a literal x is logically entailed from φ by a partial assignment {a mathematical formula}l1,…,lk (by setting literals {a mathematical formula}l1,…,lk to true) if any assignment that extends {a mathematical formula}l1,…,lk and satisfies φ sets x to true. Note that this is equivalent to {a mathematical formula}φ∧l1∧⋯∧lk⊨x. Clearly, literals that form unit clauses in φ are logically entailed from φ. Also note that given clause {a mathematical formula}C=l1∨l2∨⋯∨lk, formula {a mathematical formula}φ∧⋀j=1k¬lj is by De Morganʼs laws equivalent to {a mathematical formula}φ∧¬C. In the subsequent text we shall use these notations interchangeably.
      </paragraph>
      <paragraph>
       A clause C is called 1-provable with respect to a CNF formula φ, if {a mathematical formula}φ∧¬C⊢1⊥. A clause C is thus 1-provable if it is an implicate of C and the fact that C is an implicate can be proved using unit propagation. The notion of 1-provability was introduced in [15]. A formula φ is called unit refutation complete if every implicate C of φ is 1-provable with respect to φ. The notion of unit refutation completeness was introduced in [26] and later inspired the definition of propagation completeness in [9], which we give in the following subsection.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Propagation completeness and empowerement
      </section-title>
      <paragraph label="Definition 2.1">
       Propagation Completeness (PC) [9]We call a CNF formula φ propagation complete (PC) if for any partial assignment {a mathematical formula}l1,…,lk and any literal d the following holds. If d is logically entailed from φ by {a mathematical formula}l1,…,lk, then d can be derived from φ by unit propagation after fixing values of {a mathematical formula}l1,…,lk, i.e., if {a mathematical formula}φ∧l1∧⋯∧lk⊨d, then {a mathematical formula}φ∧l1∧⋯∧lk⊢1d. The class PC is the class of all PC formulas.
      </paragraph>
      <paragraph label="Definition 2.2">
       Empowering implicate [15], [9], Absorption [27], [9]A clause {a mathematical formula}C=l1∨l2∨l3∨⋯∨lk is called an empowering implicate for a formula φ if it contains a literal {a mathematical formula}li called an empowered literal such that {a mathematical formula}φ∧⋀j∈1…k,j≠i¬lj⊬1⊥ and {a mathematical formula}φ∧⋀j∈1…k,j≠i¬lj⊨li but {a mathematical formula}φ∧⋀j∈1…k,j≠i¬lj⊬1li. An implicate C is called absorbed by φ if it has no empowered literal.
      </paragraph>
      <paragraph>
       It is known that a formula is propagation complete if and only if it has no empowering implicates [9]. Thus, any formula can be extended to a propagation complete one by repeatedly adding empowering implicates.
      </paragraph>
      <paragraph>
       The notion of empowering clauses is closely related to CDCL SAT solvers, see [15] and [26]. It is important to note that each asserting clause is empowering as observed in [15]. Since most CDCL SAT solvers learn only asserting clauses the notion of propagation completeness is important also in the context of CDCL SAT solvers.
      </paragraph>
      <paragraph label="Example 2.3">
       Consider the following formula{a mathematical formula} Formula φ is not propagation complete, because {a mathematical formula}φ∧¬b∧¬c⊨a but {a mathematical formula}φ∧¬b∧¬c⊬1a. Indeed, by falsifying b and c we get {a mathematical formula}(a∨x)∧(a∨¬x) and thus literal a can be obtained by resolution, but not by unit propagation.It follows that {a mathematical formula}(a∨b∨c) is an empowering implicate for φ with a being its empowered literal. By adding this implicate to φ we get a propagation complete formula{a mathematical formula} The fact that {a mathematical formula}φ′ is propagation complete follows from the fact that it consists of all prime implicates of φ. Consider for example a non-prime implicate {a mathematical formula}C=(a∨b∨c∨x), this implicate is absorbed by {a mathematical formula}φ′ because by falsifying any three literals from C we either get an unsatisfiable formula (such as if a, b, and x are falsified) or we obtain the remaining literal by unit propagation (such as if a, c, and x are falsified, b is obtained from the first clause of {a mathematical formula}φ′). We can observe that in fact, C is already absorbed by φ.
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       Relation of propagation completeness to constraint propagation
      </section-title>
      <paragraph>
       Propagation complete formulas play an important role in constraint propagation (for general reading on constraint propagation see Chapter 3 of [28]), where the notion appeared implicitly in earlier literature [10], [11], [12], [13], [14], [29] concentrated on CNF encodings of constraints both in general [10], [11], and for particular constraints (the sequence constraint [13], the grammar constraint [14], the Regular, the Among, and the Generalized sequence constraints [11], or the AllDifferent constraint [12]). A general idea which appeared in all these papers is to take a constraint C, encode it using a CNF and then use unit propagation to maintain some kind of domain consistency (e.g. generalized arc consistency (GAC) in [10], or (relational) {a mathematical formula}(i,j)-consistency in [29]). In general, these encodings are polynomial in table representation of a constraint, however in the case of a particular global constraint we can sometimes use its special properties to get a CNF representation of polynomial size with respect to the arity of a constraint with suitable properties, such as in [11] in case of the Regular constraint, the Among constraint, or the Generalized sequence constraint. On the other hand in some cases this is not possible as it is shown in [12] for the AllDifferent constraint.
      </paragraph>
      <paragraph>
       The idea of using unit propagation to maintain domain consistencies was formalized in [12], let us recall some of the results and the notation from [12] here. A constraint C is defined over a set of variables {a mathematical formula}X={X1,…,Xn}, each of which has a finite domain {a mathematical formula}D(Xi). An assignment to a variable {a mathematical formula}Xi is a mapping of {a mathematical formula}Xi to a value {a mathematical formula}j∈D(Xi), called a literal and written {a mathematical formula}Xi=j. {a mathematical formula}D(X) denotes the set of literals, i.e. {a mathematical formula}D(X)={Xi=j|Xi∈X∧j∈D(Xi)}. {a mathematical formula}P(D(X)) then denotes the set of all possible sets of literals. A constraint C is defined over a set of variables denoted as {a mathematical formula}scope(C)⊆X (scope of C) and it allows a subset of the possible assignments to the variables in {a mathematical formula}scope(C).
      </paragraph>
      <paragraph>
       Following [12], [30], [28] a propagator for a constraint C is an algorithm which takes as input the domains of variables in {a mathematical formula}scope(C) and returns restrictions of these domains. Formally a propagator for a constraint C can be defined as follows (definition is taken from [12], where they followed [30], see also Chapter 3 of [28]):
      </paragraph>
      <paragraph label="Definition 2.4">
       (See Definition 1 in [12].) A propagator f for a constraint C is a polynomial time computable function {a mathematical formula}f:P(D(X))↦P(D(X)), such that f is monotone, i.e. {a mathematical formula}D′(X)⊆D(X)⇒f(D′(X))⊆f(D(X)), contracting, i.e. {a mathematical formula}f(D(X))⊆D(X), and idempotent, i.e. {a mathematical formula}f(D(X))=f(f(D(X))). If f detects that C has no solutions under {a mathematical formula}D(X) then {a mathematical formula}f(D(X))=∅.
      </paragraph>
      <paragraph>
       We say that a propagator detects dis-entailment if {a mathematical formula}f(D(X))=∅ whenever C has no solution. A propagator enforces domain consistency (DC) when {a mathematical formula}Xi=j∈f(D(X)) implies that there exists a solution of C that contains {a mathematical formula}Xi=j. Other consistencies (such as GAC [10] which is equivalent to DC, or {a mathematical formula}(i,j)-consistency [29]) can be considered as well, we mention domain consistency here because later on we shall recall the results of [12] on domain consistency propagators.
      </paragraph>
      <paragraph>
       Let us recall a definition of a CNF decomposition of a propagator as it appeared in [12]. Before that let us recall a general way how a constraint satisfaction program (CSP) variables with multiple valued domains are usually encoded within a CNF. Given a variable {a mathematical formula}Xi∈X with domain {a mathematical formula}D(Xi) we encode it with a set of boolean variables {a mathematical formula}xi,j, {a mathematical formula}Xi∈X, {a mathematical formula}j∈D(Xi) such that {a mathematical formula}Xi≠j⇔x¯i,j. The property that a CSP variable {a mathematical formula}Xi has at most one value is enforced by the set of AMO (i.e. at most one) clauses {a mathematical formula}(x¯i,j∨x¯i,k) for all {a mathematical formula}j,k∈D(Xi), {a mathematical formula}k≠j, and the property that it has at least one value is enforced by the ALO (i.e. at least one) clause {a mathematical formula}⋁j∈D(Xi)xi,j. Following [12] we call the above described propositional representation of {a mathematical formula}D((X)) (i.e. set of all AMO and ALO clauses over all CSP variables) a direct encoding and denote it as {a mathematical formula}Dsat(X).
      </paragraph>
      <paragraph label="Definition 2.5">
       (See Definition 4 in [12].) A CNF decomposition of a propagation algorithm (propagator) {a mathematical formula}fP is a formula in CNF {a mathematical formula}φP over variables {a mathematical formula}x∪y such that
      </paragraph>
      <list>
       <list-item label="•">
        The input variablesx are the propositional representation {a mathematical formula}Dsat(X) of {a mathematical formula}D(X) and y is a set of auxiliary variables whose size is polynomial in {a mathematical formula}|x|.
       </list-item>
       <list-item label="•">
        {a mathematical formula}xi,j is set to 0 by a unit propagation if and only if {a mathematical formula}Xi=j∉fP(D(X)).
       </list-item>
       <list-item label="•">
        Unit propagation on {a mathematical formula}φP produces the empty clause when {a mathematical formula}fP(D(X))=∅.
       </list-item>
      </list>
      <paragraph>
       Before further discussion, let us look at an example from [12].
      </paragraph>
      <paragraph label="Example 2.6">
       (See Example 1 in [12].) Consider a Table constraint over the variables {a mathematical formula}X1,X2 with {a mathematical formula}D(X1)=D(X2)={a,b} and the satisfying assignments: {a mathematical formula}{〈a,a〉,〈b,b〉,〈a,b〉}. Using encoding introduced in [10] we can decompose a Table constraint into the following CNF {a mathematical formula}φT:{a mathematical formula} Here {a mathematical formula}y={y1,y2,y3} consists of auxiliary variables corresponding to the three possible solutions to the Table constraint ({a mathematical formula}y1 corresponds to {a mathematical formula}〈a,a〉, {a mathematical formula}y2 to {a mathematical formula}〈b,b〉, and {a mathematical formula}y3 to {a mathematical formula}〈a,b〉). Suppose the value a is removed from the domain of {a mathematical formula}X1. The assignment {a mathematical formula}x1a=0 forces the variable {a mathematical formula}y1 to 0, which in turn causes the variable {a mathematical formula}x2a to 0, removing the value a from the domain of {a mathematical formula}X2 as well.
      </paragraph>
      <paragraph>
       Now let us generalize the ideas presented in the above example. Let us consider a constraint C, its consistency propagator {a mathematical formula}fP, and a CNF decomposition of {a mathematical formula}fP via a CNF {a mathematical formula}φP.
      </paragraph>
      <list>
       <list-item label="•">
        By definition, if {a mathematical formula}fP detects dis-entailment, then {a mathematical formula}fP(D(X))=∅ whenever C restricted to {a mathematical formula}D(X) admits no solution. Passing {a mathematical formula}D(X) to {a mathematical formula}fP corresponds to setting all values {a mathematical formula}xi,j=0 for {a mathematical formula}Xi=j∉D(X). The third condition of Definition 2.5 thus requires that after this partial assignment {a mathematical formula}φP is not only unsatisfiable but this fact can be detected by unit propagation. In particular we require that for any {a mathematical formula}D(X):{a mathematical formula} What we in fact require here is that {a mathematical formula}φP is unit refutation complete with respect to the partial assignments to the input variables x. Although we admit here only assignments to 0, the direct encoding clauses {a mathematical formula}Dsat(X) allow us to use 1 as well (assigning {a mathematical formula}xi,j=1 forces {a mathematical formula}xi,k=0 for any {a mathematical formula}k≠j, {a mathematical formula}k∈D(Xi) by unit propagation on {a mathematical formula}Dsat(X)).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}fP is a domain consistency propagator then there is no solution to C containing {a mathematical formula}Xi=j if and only if {a mathematical formula}Xi=j∉f(D(X)). Using the second condition from Definition 2.5 it corresponds to the fact that {a mathematical formula}x¯i,j is a unit implicate of {a mathematical formula}φP under partial assignment given by {a mathematical formula}D(X) if and only if {a mathematical formula}xi,j is forced to 0 by unit propagation on {a mathematical formula}φP under this partial assignment. In particular we require that for any {a mathematical formula}D(X) and any {a mathematical formula}xi,j:{a mathematical formula} What we in fact require here is the fact that {a mathematical formula}φP is propagation complete with respect to partial assignments and literals on the input variables in x. In the above equation it is enough to consider only negative literals {a mathematical formula}xi,j due to presence of clauses of direct encoding {a mathematical formula}Dsat(X).
       </list-item>
      </list>
      <paragraph>
       The author of [10] suggests that a canonical CNF decomposition (i.e. CNF consisting of all prime implicates) is sufficient to encode both dis-entailment detecting propagator and domain consistency propagator. The above discussion shows that a shorter CNF is sufficient, in particular unit refutation completeness is sufficient for detecting dis-entailment and propagation completeness is sufficient for domain consistency propagator. This can be naturally generalized to other consistencies such as {a mathematical formula}(i,j)-consistency [29].
      </paragraph>
      <paragraph>
       It was shown in [21] that a polynomial sized decomposition of a consistency propagator {a mathematical formula}fP exists if and only if it can by computed by a monotone circuit of polynomial size. This result was used to derive the following corollary:
      </paragraph>
      <paragraph label="Corollary 2.7">
       (See Corollary 4 in[21].) There is no polynomial sized CNF decomposition of anyAllDifferentdomain consistency propagator.
      </paragraph>
      <paragraph>
       On the other hand we can get a polynomial sized CNF encoding of the AllDifferent constraint. Using such an encoding and Corollary 2.7 it follows that no propagation complete encoding of the AllDifferent constraint can have polynomial size. There are thus formulas such that any equivalent propagation complete formula has superpolynomial size. Let us have a more detailed look at the proof of Corollary 2.7 in [21]. It was shown in [31] that AllDifferent constraint has a solution if and only if the corresponding bipartite value graph has a perfect matching. From the aformentioned connection to monotone circuits proved in [21] it follows that based on an AllDifferent domain consistency propagator we can construct a monotone circuit that computes whether a bipartite graph has a perfect matching and such a circuit has a polynomial size with respect to the domain consistency propagator we start with. The proof is finished using an older result of Razborov [22] according to which the size of monotone circuit computing whether there is a perfect matching in a bipartite graph G on n vertices has size at least {a mathematical formula}nΩ(logn), which is a superpolynomial (in some literature called quasi-polynomial) but not an exponential bound. In Section 5 we strengthen the result of Corollary 2.7 for propagation complete formulas by showing that there are in fact formulas to which an exponential number of implicates have to be added in order to make them propagation complete.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Properties of empowering implicates
     </section-title>
     <paragraph>
      Let us start this section with a discussion on connection between unit refutation completeness introduced in [26] and propagation completeness introduced in [9]. First let us recall that a formula φ is unit refutation complete if for every implicate C of φ we have that {a mathematical formula}φ∧¬C⊢1⊥. This means that the fact that C is an implicate of φ can be proved using just unit resolution. It is not hard to see that if a formula φ is propagation complete, then it is unit refutation complete as well. Indeed, if {a mathematical formula}C=(l1∨⋯∨lk) is an implicate of φ, then either {a mathematical formula}φ∧⋀i=1k−1¬li⊢1⊥, or {a mathematical formula}φ∧⋀i=1k−1¬li⊢1lk which implies {a mathematical formula}φ∧⋀i=1k¬li⊢1⊥. On the other hand, it is not true that every unit refutation complete formula is also propagation complete. Consider the following formula φ:{a mathematical formula} This is a prime CNF which has only one more prime implicate {a mathematical formula}C=(a∨b∨c∨d) produced by resolving the two clauses in φ. We can observe that φ is unit refutation complete. If we add negation of C to φ, then unit resolution of {a mathematical formula}x¯ and x gives us the empty clause. However φ is not propagation complete and C is an empowering implicate of φ with empowered literal a (or b). Indeed, if we set b, c, and d to false in φ, we get CNF {a mathematical formula}(x¯∨a)∧(x∨a) from which it is not possible to derive a just using unit resolution.
     </paragraph>
     <paragraph>
      It follows from the above discussion that the set of propagation complete CNFs is a proper subset of unit refutation complete CNFs. The aim of this section is to recall several results about the class of unit refutation complete CNFs from [26] and observe that some of these results are in fact true already for the set of propagation complete formulas.
     </paragraph>
     <paragraph>
      We shall start with showing that adding a literal to a non-empowering implicate cannot make it empowering with respect to any of the original literals.
     </paragraph>
     <paragraph label="Lemma 3.1">
      Let φ be a CNF formula and let{a mathematical formula}C=l1∨⋯∨lkbe an implicate of φ which is not empowering. Let A be a clause and let{a mathematical formula}li∈Cbe an arbitrary literal. Then{a mathematical formula}C∨Ais not empowering implicate of φ with empowered literal{a mathematical formula}li.
     </paragraph>
     <paragraph label="Proof">
      Let us assume without loss of generality that {a mathematical formula}i=k (if not, then we can achieve this by renaming the variables). By definition, the fact that C is not empowering with empowered literal {a mathematical formula}lk implies that either {a mathematical formula}φ∧⋀j=1k−1¬lj⊢1⊥, or {a mathematical formula}φ∧⋀j=1k−1¬lj⊢1lk because C is an implicate of φ and thus {a mathematical formula}φ∧⋀j=1k−1¬lj⊨lk. Since {a mathematical formula}φ∧⋀j=1k−1¬lj is a subformula of {a mathematical formula}φ∧⋀j=1k−1¬lj∧⋀a∈A¬a, what we can derive by unit propagation from the former formula, can be derived from latter one as well. Thus we have that {a mathematical formula}φ∧⋀j=1k−1¬lj∧⋀a∈A¬a⊢1⊥ or {a mathematical formula}φ∧⋀j=1k−1¬lj∧⋀a∈A¬a⊢1lk. This means that by definition, {a mathematical formula}C∨A is not empowering implicate with empowered literal {a mathematical formula}lk.  □
     </paragraph>
     <paragraph>
      Note that in the previous proposition we cannot argue that {a mathematical formula}A∨C is not empowering because it could be empowering with an empowered literal from A, e.g. if A would itself be an empowering clause. That is why we consider only literals in C. Using Lemma 3.1, we can easily show that among empowering implicates the prime implicates are the only ones we need to consider.
     </paragraph>
     <paragraph label="Lemma 3.2">
      Let φ be a nonempty satisfiable CNF formula (i.e. it has at least one nonempty clause) and let C be an empowering implicate for φ. Then any implicate{a mathematical formula}C′of φ subsuming C is empowering for φ (this in particular includes the case when{a mathematical formula}C′is prime).
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}C′ be an arbitrary implicate subsuming C and let us assume that {a mathematical formula}C′≠C. If {a mathematical formula}C′ is not empowering, then {a mathematical formula}φ∧¬C′⊢1⊥ and thus C cannot be empowering with respect to a literal a, which is not in {a mathematical formula}C′. On the other hand, C cannot be empowering with respect to a literal in {a mathematical formula}C′ as well due to Lemma 3.1.  □
     </paragraph>
     <paragraph>
      As an easy corollary we now get that a canonical CNF formula is always propagation complete, although this can be easily deduced from properties of canonical CNFs as well.
     </paragraph>
     <paragraph>
      Now let us consider the problem of generating an empowering implicate for a given CNF formula. A natural method to consider is to generate an empowering implicate by the resolution procedure. In [26] it is shown that non-merge resolution cannot produce an empowering implicate with respect to unit refutation completeness. In case of propagation completeness the same is true. It follows from discussion at the beginning of Section 5 in [9]. We shall formulate this proposition as a lemma to be able to reference to it later.
     </paragraph>
     <paragraph label="Lemma 3.3">
      Let φ be a CNF formula and let C be produced from φ by a series of non-merge resolutions. Then C is not an empowering implicate of φ.
     </paragraph>
     <paragraph>
      Keeping in mind that a canonical formula is propagation complete, it follows that a CNF formula φ satisfying that every prime implicate of φ is either present in it or it can be derived from φ by a series of non-merge resolutions is always propagation complete. This property was already shown in form of Theorem 1 in [26] for unit refutation completeness and it is an easy corollary of arguments about non-merge resolution in [9] (here stated as Lemma 3.3) that it is true also for PC formulas.
     </paragraph>
     <paragraph>
      Since PC formulas allow easy inference, it is interesting to investigate classes which are contained in the class of PC CNF formulas. One such example is given by the following theorem which shows the desired property for the class of prime quadratic CNF formulas.
     </paragraph>
     <paragraph label="Theorem 3.4">
      If φ is a prime quadratic CNF formula, then it is propagation complete.
     </paragraph>
     <paragraph label="Proof">
      If φ is not satisfiable, then the proposition of the theorem is trivial. Let us assume that φ is a satisfiable prime quadratic CNF formula.By Lemma 3.2 it is enough to consider prime implicates as candidates for empowering implicates. Because φ is a prime CNF formula, it must contain all the unit prime implicates. Hence, if any other prime implicate should be added to φ to make it propagation complete, it must be a quadratic clause which is produced by resolving two other quadratic clauses. It is a simple observation that these resolutions have to be non-merge. Thus by Lemma 3.3 we have that φ must already be propagation complete.  □
     </paragraph>
     <paragraph>
      The following lemma shows that the primeness assumption in the statement of Theorem 3.4 is necessary.
     </paragraph>
     <paragraph label="Lemma 3.5">
      There is a (non-prime) quadratic CNF formula which is not PC.
     </paragraph>
     <paragraph label="Proof">
      Let us consider the following CNF formula:{a mathematical formula}φ is clearly a quadratic CNF formula. On the other hand, φ is not PC because {a mathematical formula}φ⊨a¯, but {a mathematical formula}φ⊬1a¯.  □
     </paragraph>
     <paragraph>
      Now let us turn our attention to the complexity of testing if a given clause C is an empowering implicate of a CNF formula φ. We shall denote this problem as IsEmpowering({a mathematical formula}φ,C). Note that co-NP completeness of IsEmpowering({a mathematical formula}φ,C) comes as no surprise since it is in essence very similar to another co-NP complete problem IsImplicate({a mathematical formula}φ,C). The hard part of checking whether given clause C is an empowering implicate of φ is in fact checking whether C is an implicate of φ at all. Thus the co-NP completeness of IsEmpowering({a mathematical formula}φ,C) is a direct consequence of co-NP completeness of IsImplicate({a mathematical formula}φ,C). The proof of the following theorem only formalizes this idea.
     </paragraph>
     <paragraph label="Theorem 3.6">
      The problemIsEmpowering({a mathematical formula}φ,C) is co-NP complete.
     </paragraph>
     <paragraph label="Proof">
      To show that a problem is in co-NP it suffices to have for every negative instance of the problem a polynomially verifiable certificate which allows to verify that the answer is no. We can distinguish two cases when a pair {a mathematical formula}(φ,C) forms a negative instance of IsEmpowering. In the first case C is not even an implicate of φ and the desired certificate is then an assignment of truth values to the variables which satisfies φ and falsifies C. The second case is when C is an implicate of φ but not an empowering one. In this case an empty certificate is good enough because one needs no additional information to be able to check in polynomial time that no literal in C is empowered. This can be done by running unit propagation and checking for every literal ℓ in C that {a mathematical formula}φ∧⋀ℓ′∈C,ℓ′≠ℓ¬ℓ′⊢1⊥ or {a mathematical formula}φ∧⋀ℓ′∈C,ℓ′≠ℓ¬ℓ′⊢1ℓ.For the co-NP hardness we reduce the co-NP complete problem IsImplicate to IsEmpowering. Let {a mathematical formula}(φ,C) be an arbitrary instance of IsImplicate. We start by a simple preprocessing step in which we run unit propagation to test whether {a mathematical formula}φ∧⋀ℓ∈C¬ℓ⊢1⊥. If yes, then C is an implicate of φ (in fact a 1-provable implicate), i.e. {a mathematical formula}(φ,C) is a positive instance of IsImplicate, and the reduction algorithm can terminate by answering yes. Note that this case includes the situation when C is a clause in φ. If no, i.e. if {a mathematical formula}φ∧⋀ℓ∈C¬ℓ⊬1⊥, we define an instance {a mathematical formula}(φ′,C′) of IsEmpowering by {a mathematical formula}φ′=φ∧(x∨y)∧(x∨y¯) and {a mathematical formula}C′=C∨x¯, where x and y are two new variables not appearing in {a mathematical formula}(φ,C). We shall show that C is an implicate of φ if and only if {a mathematical formula}C′ is an empowering implicate of {a mathematical formula}φ′ with {a mathematical formula}x¯ as the empowered literal.Let C be an implicate of φ. C is clearly an implicate of {a mathematical formula}φ′, and hence also {a mathematical formula}C′ is an implicate of {a mathematical formula}φ′. To see that {a mathematical formula}C′ is empowering with {a mathematical formula}x¯ as the empowered literal recall that {a mathematical formula}φ∧⋀ℓ∈C¬ℓ⊬1⊥ and thus {a mathematical formula}φ′∧⋀ℓ∈C¬ℓ⊬1x¯ because unit propagation does nothing on {a mathematical formula}(x∨y)∧(x∨y¯) and neither x nor y appear in φ and C.Let {a mathematical formula}C′ be an empowering implicate of {a mathematical formula}φ′ with {a mathematical formula}x¯ as the empowered literal. The fact that {a mathematical formula}C′ is an implicate of {a mathematical formula}φ′ means that any assignment that falsifies {a mathematical formula}C′ must also falsify {a mathematical formula}φ′. However, any assignment which falsifies {a mathematical formula}C′ sets x to 1, falsifies C and satisfies {a mathematical formula}(x∨y)∧(x∨y¯) regardless of the value of y. Thus, to falsify {a mathematical formula}φ′ it must falsify φ. Therefore any assignment which falsifies C must also falsify φ, which means that C is an implicate of φ.  □
     </paragraph>
     <paragraph>
      Let us recall the notion of a tied chain in a CNF formula used in [26] in case of unit refutation completeness.
     </paragraph>
     <paragraph label="Definition 3.7">
      (See [26], introduced in [32].) A tied chain in a CNF formula φ is a sequence of triples {a mathematical formula}(x1,C1,y1),(x2,C2,y2),…,(xn,Cn,yn) such that:
     </paragraph>
     <list>
      <list-item label="•">
       For {a mathematical formula}1⩽i⩽n, {a mathematical formula}Ci is a clause in φ and {a mathematical formula}xi,yi are two different literals in {a mathematical formula}Ci (i.e. {a mathematical formula}xi≠yi).
      </list-item>
      <list-item label="•">
       For {a mathematical formula}1⩽i⩽n−1, we have that {a mathematical formula}yi and {a mathematical formula}xi+1 are complementary literal (called link literals of the chain).
      </list-item>
      <list-item label="•">
       {a mathematical formula}x1=yn is called the tied literal of the chain.
      </list-item>
     </list>
     <paragraph>
      For example CNF formula {a mathematical formula}φ=(p∨q∨r)∧(r¯∨s)∧(s¯∨p) contains a tied chain with p as tied literal. In [32] it is shown that the absence of tied chains is a sufficient condition for unit refutation completeness. The following lemma was shown in [26] as Lemma 6.
     </paragraph>
     <paragraph label="Lemma 3.8">
      (See Lemma 6 of[26].) Let C be an implicate of a CNF formula φ which is produced from φ by a resolution proof D in which the last resolution made is a merge resolution. Let us assume that the parent clauses of C in D are{a mathematical formula}C1and{a mathematical formula}C2, where M denotes the set of common literals in{a mathematical formula}C1and{a mathematical formula}C2.{a mathematical formula}M≠∅since the last step in D is a merge resolution and every literal of M is contained in C. Then φ contains, for each literal{a mathematical formula}ℓ∈M, a tied chain{a mathematical formula}Tℓwith ℓ as its tied literal. Furthermore, each link literal in{a mathematical formula}Tℓhas a clause in D which is produced from its parent clauses by resolution upon ℓ.
     </paragraph>
     <paragraph>
      It is argued in [26] that if there are no tied chains in a CNF formula φ, there can be no merge resolutions and thus the formula φ has to be unit refutation complete. The same argument can be used for propagation completeness. We can argue in the same way using Lemma 3.3 that absence of tied chains in a CNF formula φ implies that φ is propagation complete. We shall use this property in proofs in the text and thus we shall formulate it as a lemma to be able to reference to it.
     </paragraph>
     <paragraph label="Lemma 3.9">
      If a CNF formula φ does not contain tied chains, then it is propagation complete.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Resolution derivations of empowering implicates
     </section-title>
     <paragraph>
      We have seen in Theorem 3.6 that it is hard to check whether a given clause C is an empowering implicate of a given formula φ. The hard part of this test is to check whether C is in the set S of all implicates of φ. The core of the proof of Theorem 3.6 shows that considering a smaller set {a mathematical formula}S′⊆S of all empowering implicates of φ does not make this test easier.
     </paragraph>
     <paragraph>
      We shall show now that the hard part of the test can be in some sense avoided by considering a suitable enlargement of the tested clause. In particular, we shall show that if a clause C is an empowering implicate of a CNF formula φ, we can always extend C by adding suitable literals to obtain clause {a mathematical formula}C′ which is still empowering and moreover we can check that {a mathematical formula}C′ is an implicate of φ simply by unit resolution. Let us recall that such a clause is called 1-provable (which is a notion introduced in [15]).
     </paragraph>
     <paragraph>
      Proof of Theorem 4.2 is significantly based on Proposition 2. The proposition is given in [15] and may be restated as follows.
     </paragraph>
     <paragraph label="Proposition 4.1">
      (See Proposition 2 of[15].) Let ψ be an unsatisfiable CNF such that{a mathematical formula}ψ⊬1⊥and Π be its resolution refutation. Then there exists a clause{a mathematical formula}Cψ∈Πwhich is both empowering and 1-provable.
     </paragraph>
     <paragraph>
      Let C be an empowering implicate of a formula φ which is not 1-provable. This means that if we falsify all the literals in C and add them to φ, thus producing {a mathematical formula}ψ=φ∧¬C, then we get a contradiction which is not provable by unit resolution. By using the previous proposition we show that we may add the clause C to the obtained clause {a mathematical formula}Cψ to obtain a clause which is both 1-provable and empowering.
     </paragraph>
     <paragraph>
      The following Theorem 4.2 is a consequence of Proposition 4.1. For readers familiar with CDCL SAT solvers, the idea remains the same as in the previous paragraph. By falsifying the literals in C any CDCL SAT solver must derive a contradiction. We add the solverʼs decisions to the input clause C, i.e. we add ¬C and the conjunction of literals corresponding to each assigned variable to the input formula. After such an addition, we obtain the desired 1-provable and empowering clause. As we shall show later in Proposition 4.3 we can even derive such a clause C using only linear number of resolution steps with respect to the number of literal occurrences in φ.
     </paragraph>
     <paragraph label="Theorem 4.2">
      Assume that C is an empowering implicate of a formula φ which is not 1-provable. Then there is an implicate{a mathematical formula}C′of φ such that{a mathematical formula}C⊂C′and C is both 1-provable and empowering.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}ψ=φ∧¬C and Π be a resolution refutation of ψ. Because C is not 1-provable for φ it holds that {a mathematical formula}ψ⊬1⊥. Then according to the proposition there is a clause {a mathematical formula}Cψ∈Π which is both empowering and 1-provable with respect to ψ. We consider a clause {a mathematical formula}Cφ=Cψ∨C.First, {a mathematical formula}Cφ is 1-provable for φ because {a mathematical formula}Cψ is 1-provable for ψ and all the possibly required literals were added to {a mathematical formula}Cφ. It follows from the following obvious chain of equivalence:{a mathematical formula}Let ℓ be an empowering literal of {a mathematical formula}Cψ for ψ. Then ℓ is trivially also an empowered literal of {a mathematical formula}Cφ for φ. The required properties for unit resolution and entailment come from the definitions of {a mathematical formula}Cφ and ψ using similar chain of equivalences as in 1.Thus {a mathematical formula}Cφ is the desired clause since it is both empowering and 1-provable with respect to φ.  □
     </paragraph>
     <paragraph>
      The following proposition shows that not only can we find a 1-provable and empowering implicate as in Theorem 4.2 but we can also derive some empowering implicate by a resolution derivation of linear length with respect to the number of literals occurring in given formula. The proof is based on ideas presented in [15] and [33], [34], [35] in the context of CDCL SAT solvers. More detailed discussion about this connection is presented just after the proof of the proposition.
     </paragraph>
     <paragraph label="Proposition 4.3">
      Let φ be a formula on n variables which is not propagation complete and s be the size of the CNF representation of φ (i.e. s is the total number of occurrences of literals in φ). Then there is an empowering implicate C of φ which can be derived by a series of resolutions of length at most s from φ.
     </paragraph>
     <paragraph label="Proof">
      From Theorem 4.2 it follows that there is an empowering 1-provable implicate {a mathematical formula}Cφ of φ with an empowered literal ℓ. Let {a mathematical formula}φ′ denote the formula which originates from φ after adding unit clauses formed by negated literals from {a mathematical formula}Cφ, i.e. {a mathematical formula}φ′≡φ∧¬Cφ. Since {a mathematical formula}Cφ is 1-provable it follows that {a mathematical formula}φ′⊢1⊥, i.e. we can derive contradiction from {a mathematical formula}φ′ by using only unit resolution.Due to the nature of unit resolutions, we can assume that the unit refutation proceeds in two phases.
      <list>
       In the first phase we take all unit clauses from {a mathematical formula}¬Cφ and perform unit resolutions only over the variables from {a mathematical formula}Cφ.In the second phase we continue with refutation proof without using unit clauses from {a mathematical formula}¬Cφ and we do not resolve over variables from {a mathematical formula}Cφ at all.Let us now assume that
      </list>
      <paragraph>
       {a mathematical formula}D1′,…,Dm′=⊥ is a unit refutation proof which proceeds in the above two phases. Since it is a unit refutation proof, it can be observed that {a mathematical formula}m⩽s. Let us assume that the first phase is formed by clauses {a mathematical formula}D1′,…,Dk′−1′ and the second phase is formed by clauses {a mathematical formula}Dk′′,…,Dm′. Each clause among {a mathematical formula}D1′,…,Dk′−1′ is therefore either a clause in {a mathematical formula}φ′ or it originates from two preceding clauses by unit resolution over variable from {a mathematical formula}Cφ. Similarly each clause among {a mathematical formula}Dk′′,…,Dm′ is either an original clause from φ or it originates from two preceding clauses by unit resolution over a variable which is not in {a mathematical formula}Cφ. Observe that if the resolution proof is irredundant, i.e. no clause can be dropped from it, no clause among {a mathematical formula}Dk′′,…,Dm′ contains a variable from {a mathematical formula}Cφ. This is because in the end we arrive at an empty clause and there is no way to remove a variable from {a mathematical formula}Cφ in the second phase.Let us now consider the situation in which we do not proceed with the first phase, in particular if we replace the first phase only with a list of corresponding clauses from φ. In this case the second phase can proceed as before (except that unit resolution steps are replaced by general resolution steps) only now the input clauses of phase 2 may contain some literals from {a mathematical formula}Cφ as these were not removed in missing phase 1. These literals propagate down to the end of the proof and ⊥ now becomes a subclause of {a mathematical formula}Cφ. In this way we shall obtain a resolution proof of a clause {a mathematical formula}C′⊆Cφ. Note that ℓ will be present in {a mathematical formula}C′ because otherwise the original unit refutation would actually prove that {a mathematical formula}φ∧¬(Cφ∖{ℓ})⊢1⊥ which would be in contradiction with the fact that {a mathematical formula}Cφ is an empowering implicate with empowered literal ℓ. Thus {a mathematical formula}C′ will be empowering by Lemma 3.1.Let us now formalize the above idea. If {a mathematical formula}Dj′ is a clause among the clauses {a mathematical formula}D1′,…,Dk′−1′, then it is either a unit literal from {a mathematical formula}¬Cφ or there is a clause {a mathematical formula}Dj∈φ, such that {a mathematical formula}Dj′ originates from {a mathematical formula}Dj by falsifying some literals from {a mathematical formula}Cφ. If {a mathematical formula}Dj′ is later used in the second phase of the unit refutation proof, the latter is the case and then {a mathematical formula}Dj′ originates from some clause {a mathematical formula}Dj∈φ by falsifying all literals of {a mathematical formula}Cφ which appear in {a mathematical formula}Dj.If {a mathematical formula}Dj′ is among {a mathematical formula}Dk′′,…,Dm′ then we shall define clause {a mathematical formula}Dj as follows. If {a mathematical formula}Dj′ is an original clause from φ, then {a mathematical formula}Dj=Dj′, if {a mathematical formula}Dj′=R(Da′,Db′) where {a mathematical formula}1⩽a,b&lt;j, then we define {a mathematical formula}Dj=R(Da,Db). Note that if {a mathematical formula}Da′ and {a mathematical formula}Db′ were two resolvable clauses, then the same is true about {a mathematical formula}Da and {a mathematical formula}Db. This is because if {a mathematical formula}Da contains more literals than {a mathematical formula}Da′ these literals are from {a mathematical formula}Cφ and the same is true for {a mathematical formula}Db and {a mathematical formula}Db′.In the end we get a resolution derivation of length at most {a mathematical formula}m⩽s of clause {a mathematical formula}C=Dm which is a subclause of {a mathematical formula}Cφ. As we have already mentioned ℓ must be present in C. Otherwise we would get that it was not necessary to use ℓ to derive ⊥ from {a mathematical formula}φ′ which would be in contradiction with the fact that {a mathematical formula}Cφ is an empowering implicate. According to Lemma 3.1C is an empowering implicate. In particular, if C would not be empowering, then by Lemma 3.1{a mathematical formula}Cφ would not be empowering with empowered literal ℓ.  □
      </paragraph>
     </paragraph>
     <paragraph>
      It is also possible to prove Proposition 4.3 by analyzing a run of a CDCL SAT solver. Let us describe the sketch of such proof, the precise definitions of the below mentioned properties can be found in [33], [34], [35]. Consider the situation during the run of a CDCL SAT solver solving φ when the partial assignment satisfies {a mathematical formula}¬Cφ. Clearly then unit propagation is able to derive a conflict. By Proposition 3 of [34] each conflict clause can be derived by a trivial resolution derivation of length at most s. From Proposition 2 of [33] it follows that each asserting clause is also empowering. Since for each conflict there is at least one asserting clause, e.g. 1-UIP [35], then we have found an empowering clause with a short resolution proof from φ.
     </paragraph>
     <paragraph>
      As the example in the following proposition shows, the linear upper bound on the length of resolution derivation of an empowering implicate is tight up to a multiplicative constant.
     </paragraph>
     <paragraph label="Theorem 4.4">
      For each n there is a formula on{a mathematical formula}2n+1variables with size{a mathematical formula}O(n)such that it is not propagation complete, but resolution derivation of length n is needed to find an empowering implicate.
     </paragraph>
     <paragraph label="Proof">
      This is actually a very simple corollary to Lemma 3.9. It is enough to construct a tied chain of length n. The following formula (for given n) contains such a chain:{a mathematical formula} Clearly both the number of variables and the number of clauses are linear in n. First, let us observe that {a mathematical formula}(A1∨A2∨⋯∨An∨z) is an empowering implicate with empowered literal z. This is because by falsifying all literals {a mathematical formula}A1,…,An we get a quadratic formula which has z as a unit implicate, but unit resolution cannot derive this fact. Since the only tied chain in {a mathematical formula}φn is composed by all the n clauses in {a mathematical formula}φn, by Lemma 3.9 we need all these clauses in order to derive an empowering implicate.  □
     </paragraph>
     <paragraph>
      Note also that formula {a mathematical formula}φn is anti-Horn (i.e. every clause contains at most one negative literal) and thus Theorem 4.4 holds also when restricted to anti-Horn or Horn formulas as we observe in the following corollary.
     </paragraph>
     <paragraph label="Corollary 4.5">
      For each n there is a Horn formula on{a mathematical formula}2n+1variables with n clauses that it is not propagation complete but resolution derivation of length n is needed to find an empowering implicate.
     </paragraph>
     <paragraph label="Proof">
      The formula {a mathematical formula}φn in the previous theorem had at most one negative literal in each clause. Therefore, switching all literals to their complement in {a mathematical formula}φn creates a Horn CNF formula with the desired property.  □
     </paragraph>
     <paragraph>
      The first idea which comes to mind when trying to find an empowering implicate of a CNF formula φ is to run resolution until one such implicate is generated. Of course, if φ already is propagation complete, it might be necessary to find all prime implicates before we can claim φ is propagation complete. On the other hand, Proposition 4.3 suggests that in some cases, we can find an empowering implicate relatively quickly in this way. However, the obtained empowering implicate is not guaranteed to be prime. So it is natural to ask what is the necessary length of resolution derivations of prime empowering implicates. As the following observation shows, when seeking to find a prime empowering implicate all the hardness results about resolution refutations apply in this case.
     </paragraph>
     <paragraph label="Lemma 4.6">
      Let φ be a CNF formula and let x be a new variable not appearing in φ. Then{a mathematical formula}φ⊨⊥if and only if{a mathematical formula}φ⊢1⊥or x is the only prime empowering implicate of{a mathematical formula}(φ∨x). Moreover, if{a mathematical formula}φ⊬1⊥, then there is a one-to-one correspondence between the resolution refutations of φ and resolution derivations of x from{a mathematical formula}(φ∨x).
     </paragraph>
     <paragraph label="Proof">
      The one-to-one correspondence is immediately seen from the above arguments.  □
     </paragraph>
     <paragraph>
      Lemma 4.6 is an easy observation which shows that all results about complexity of resolution refutations of CNF formulas can be repeated for resolution derivations of prime empowering implicates as well. There are many results that can be used in this context, let us mention at least some of them. In [19] (and in many papers and books that followed) it was shown that pigeon hole principle formulas on {a mathematical formula}n(n+1) variables and {a mathematical formula}O(n3) clauses ({a mathematical formula}PHPn) have minimal resolution refutation of size {a mathematical formula}cn for some {a mathematical formula}c&gt;0. If a formula {a mathematical formula}PHPn is used with Lemma 4.6, we get immediately that every resolution derivation of the single prime empowering implicate x from {a mathematical formula}(PHPn∨x) must have superpolynomial length as well. This is in contrast with Proposition 4.3 in which we showed that for a formula which is not propagation complete there always exists some empowering implicate that can be generated using only number of resolutions that is linear in the length of the formula i.e. {a mathematical formula}O(n4) for {a mathematical formula}(PHPn∨x). Of course, in case of {a mathematical formula}(PHPn∨x) such an implicate would not be prime.
     </paragraph>
     <paragraph>
      Note that in [9] the formula {a mathematical formula}(PHPn∨x) was used in Section 4.2 as an example of a formula in which we can generate superpolynomially many empowering implicates while the only meaningful empowering implicate is x. In this sense Lemma 4.6 can be viewed as a simple generalization of their example, where by meaningful implicates we now consider prime implicates.
     </paragraph>
     <paragraph>
      The lower bound on the length of a resolution refutation of a {a mathematical formula}PHPn formula is only superpolynomial with respect to the length of the formula. Examples of formulas on {a mathematical formula}Θ(n) variables consisting of {a mathematical formula}Θ(n) clauses were given in [20] for which the lower bound on the length of a minimal resolution refutation is truly exponential.
     </paragraph>
     <paragraph>
      Although we used Lemma 4.6 for general resolution in our example, it is more general than that, it shows that in fact any hardness result about resolution refutations can be used for similar results about resolution derivations of a prime empowering implicate. Thus we can consider formulas which require exponential tree resolution refutations though shortest general resolution refutations have only polynomial number of steps [36]. There are other resolution refinements inbetween tree and general resolution we can take into account as well [37]. Similarly, we can use results of [38] which show formulas with resolution refutations requiring almost linear depth, it can be observed that these formulas are even Horn. There are many other results about resolution refutations which we have omitted but all of them could be used for claims about resolution derivations of prime empowering implicates as well.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Hardness of generating an empowering implicate
     </section-title>
     <paragraph>
      In this section we prove that testing whether a given CNF formula has an empowering implicate is an NP-complete problem. We start by showing that it is in NP.
     </paragraph>
     <paragraph label="Lemma 5.1">
      The problem of testing whether a given CNF formula φ has an empowering implicate is in NP.
     </paragraph>
     <paragraph label="Proof">
      It follows from Theorem 4.2 that φ has an empowering implicate if and only if it has an empowering and 1-provable implicate. Thus the certificate for φ having an empowering implicate is a clause C which is both empowering and 1-provable. These properties can be checked in polynomial time using unit propagation. It follows that the problem is in NP.  □
     </paragraph>
     <paragraph>
      Now we shall show that the problem is NP-hard by a reduction from 3D Matching (3DM), which is a well-known NP-complete problem [39], [40]. In 3DM we are given three pairwise disjoint sets X, Y, Z of the same size {a mathematical formula}|X|=|Y|=|Z|=q and a set of triples {a mathematical formula}W⊆X×Y×Z. The question we seek to answer is whether W contains a matching of size q, i.e. whether there is a subset {a mathematical formula}M⊆W of size {a mathematical formula}|M|=q such that each element of X, Y, and Z is contained in exactly one triple in M (i.e. the triples in M are pairwise disjoint).
     </paragraph>
     <paragraph>
      Next, we present a reduction of a 3DM problem into the problem of testing the existence of an empowering implicate. The reduction is a slight modification of the proof of coNP-hardness of recognizing whether a given CNF formula is an SLUR formula [41]. Unfortunately, the reduction from [41] cannot be used directly and we have to modify it. This is because the SLUR class coincides with the class of unit refutation complete formulas (see [42]), and the class of propagation complete formulas forms a strict subclass of unit refutation formulas as we have argued at the beginning of Section 3. In [41] we have associated a formula {a mathematical formula}φW to an instance of 3DM for which it was true that it was SLUR (or unit refutation complete) if and only if W contained a perfect matching. In case W does not contain a perfect matching {a mathematical formula}φW is not unit refutation complete and thus it is not propagation complete as well. Unfortunately, the opposite implication was not true for formula {a mathematical formula}φW constructed in [41], i.e. if W contains a perfect matching, then {a mathematical formula}φW is unit refutation complete, but it still not propagation complete. Thus we have to modify the original reduction in order to get the opposite implication as well.
     </paragraph>
     <paragraph label="Definition 5.2">
      With every instance {a mathematical formula}X,Y,Z,W of 3DM we associate a CNF formula {a mathematical formula}φW as follows. We assume that {a mathematical formula}X={x1,…,xq}, {a mathematical formula}Y={y1,…,yq}, {a mathematical formula}Z={z1,…,zq}, and {a mathematical formula}W={E1,…,Ew} where {a mathematical formula}w=|W|. We also assume that {a mathematical formula}Ej=(xf(j),yg(j),zh(j)) where f, g, and h are functions determining which elements of X, Y, and Z belong to {a mathematical formula}Ej (i.e. given j with {a mathematical formula}Ej=[xi1,yi2,zi3], function f returns the index of the x member of triple {a mathematical formula}Ej, thus {a mathematical formula}f(j)=i1, similarly {a mathematical formula}g(j)=i2, and {a mathematical formula}h(j)=i3).
     </paragraph>
     <list>
      <list-item label="•">
       For every {a mathematical formula}i∈{1,…,q−1} let us denote {a mathematical formula}Ai=(ai∨ai+1¯) where {a mathematical formula}a1,…,aq are new variables, and let {a mathematical formula}Aq=(aq∨a1).
      </list-item>
      <list-item label="•">
       For every {a mathematical formula}i∈{1,…,q} and {a mathematical formula}j∈{1,…,w} let us denote {a mathematical formula}Bij=(bi1¯∨⋯∨bij−1¯∨bij∨bij+1¯∨⋯∨biw¯), i.e. {a mathematical formula}Bij denotes a clause on variables {a mathematical formula}bi1,…,biw in which every literal is negative except {a mathematical formula}bij.
      </list-item>
      <list-item label="•">
       For every {a mathematical formula}i∈{1,…,q} and {a mathematical formula}j∈{1,…,w} let us denote {a mathematical formula}Cij=(ci1¯∨⋯∨cij−1¯∨cij∨cij+1¯∨⋯∨ciw¯), i.e. {a mathematical formula}Cij denotes a clause on variables {a mathematical formula}ci1,…,ciw in which every literal is negative except {a mathematical formula}cij.
      </list-item>
      <list-item label="•">
       Given a triple {a mathematical formula}Ej∈W, let {a mathematical formula}Dj=(Af(j)∨Bg(j)j∨Ch(j)j).
      </list-item>
      <list-item label="•">
       Finally, let {a mathematical formula}φW=⋀j=1wDj.
      </list-item>
     </list>
     <paragraph label="Example 5.3">
      Let {a mathematical formula}X={x1,x2,x3}, {a mathematical formula}Y={y1,y2,y3}, {a mathematical formula}Z={z1,z2,z3}, and {a mathematical formula}W={[x1,y1,z1],[x2,y3,z2],[x3,y2,z3],[x1,y2,z3],[x3,y1,z1]}. Then there are two possible matchings {a mathematical formula}M1={[x1,y1,z1],[x2,y3,z2],[x3,y2,z3]} and {a mathematical formula}M2={[x1,y2,z3],[x2,y3,z2],[x3,y1,z1]}.The formula {a mathematical formula}φW for this 3DM instance would be{a mathematical formula}In the following, we shall show that the empowering implicates of {a mathematical formula}φW correspond to perfect matchings of W. In particular, given {a mathematical formula}φW in this example we shall have two possible empowering implicates corresponding to matchings {a mathematical formula}M1 and {a mathematical formula}M2 respectively.{a mathematical formula} and{a mathematical formula}
     </paragraph>
     <paragraph>
      We claim that {a mathematical formula}φW admits an empowering implicate if and only if the input 3DM instance has a perfect matching. The proof of this claim is split into the following two lemmas.
     </paragraph>
     <paragraph label="Lemma 5.4">
      Using the notation fromDefinition 5.2let{a mathematical formula}M⊆{1,…,w}be a perfect matching and let{a mathematical formula}G=⋁j∈MBg(j)j∨Ch(j)j∨a1be a clause. Then G is an empowering implicate of{a mathematical formula}φWwith{a mathematical formula}a1being the empowered literal.
     </paragraph>
     <paragraph label="Proof">
      Let us renumber the triples in W so that {a mathematical formula}M={1,…,q} and that {a mathematical formula}f(i)=i, i.e. {a mathematical formula}xi∈Ei, for {a mathematical formula}i=1,…,q. Now, let us consider the following chain of resolutions:{a mathematical formula} One can check that {a mathematical formula}Gq=G and thus G is an implicate of {a mathematical formula}φW. All clauses in this chain are resolvable because the triples in the matching are disjoint.It remains to prove that G is empowering. Let {a mathematical formula}φ′ denote the formula originating from {a mathematical formula}φW by falsifying (substituting the value false for) all literals in G except {a mathematical formula}a1. We are going to show that {a mathematical formula}φ′≡A1∧⋯∧Aq. To this end, let {a mathematical formula}Dj=(Af(j)∨Bg(j)j∨Ch(j)j) be an arbitrary clause in {a mathematical formula}φW and let us have a look on what happens with {a mathematical formula}Dj after falsifying the aformentioned literals. If {a mathematical formula}j∈M, then we have falsified all literals in {a mathematical formula}Dj except {a mathematical formula}Af(j). If {a mathematical formula}j∉M, then let {a mathematical formula}j′∈M be an index for which {a mathematical formula}g(j′)=g(j). Such an index exists because M as a matching covers element {a mathematical formula}yg(j). It follows that {a mathematical formula}Bg(j′)j′ has two conflict variables with {a mathematical formula}Bg(j)j (note that {a mathematical formula}j≠j′) and thus by falsifying all literals in {a mathematical formula}Bg(j′)j′ we necessarily satisfy the clause {a mathematical formula}Dj. By these considerations only clauses {a mathematical formula}A1,…,Aq remain in {a mathematical formula}φ′. Note that none of these clauses is missing since M is a matching. The CNF formula {a mathematical formula}φ′=A1∧⋯∧Aq has no unit clauses and thus unit propagation will not derive anything from it. It follows that G is an empowering implicate.  □
     </paragraph>
     <paragraph label="Example 5.5">
      Let us consider implicate {a mathematical formula}H1 from Example 5.3 and let us show how it can be derived by resolutions from formula {a mathematical formula}φW. Implicate {a mathematical formula}H1 corresponds to matching {a mathematical formula}M1={[x1,y1,z1],[x2,y3,z2],[x3,y2,z3]}. The clauses of {a mathematical formula}φW corresponding to triples in {a mathematical formula}M1 are:{a mathematical formula}{a mathematical formula}{a mathematical formula} By resolving {a mathematical formula}D1 with {a mathematical formula}D2 we get clause{a mathematical formula} By further resolving {a mathematical formula}G1 with {a mathematical formula}D3 we get desired implicate {a mathematical formula}H1. Observe that {a mathematical formula}G1 was produced by non-merge resolution and thus by Lemma 3.3 it is not an empowering implicate. On the other hand {a mathematical formula}H1=R(G1,D3) is produced using a merge resolution and it is hence a good candidate for an empowering implicate of {a mathematical formula}φW. If we falsify all literals in {a mathematical formula}H1 except {a mathematical formula}a1, we get clauses {a mathematical formula}D1′=(a1∨a2¯), {a mathematical formula}D2′=(a2∨a3¯), and {a mathematical formula}D3′=(a3∨a1) from clauses {a mathematical formula}D1, {a mathematical formula}D2, and {a mathematical formula}D3 respectively. The remaining two clauses in {a mathematical formula}φW are satisfied by this assignment. Thus {a mathematical formula}H1 is indeed an empowering implicate of {a mathematical formula}φW.
     </paragraph>
     <paragraph label="Lemma 5.6">
      Let{a mathematical formula}G=G′∨ube a prime empowering implicate of{a mathematical formula}φWwith u being the empowered literal. Then u must be{a mathematical formula}a1and{a mathematical formula}G′determines perfect matching in the same way as G inLemma 5.4.
     </paragraph>
     <paragraph label="Proof">
      The proof heavily relies on Lemma 3.8 and Lemma 3.9. Let us consider a resolution derivation of {a mathematical formula}G′∨u. By Lemma 3.8 and Lemma 3.9 this derivation contains a tied chain in which every link literal is resolved upon. Consider how such a tied chain in {a mathematical formula}φW may look like. The only possible tied literal is {a mathematical formula}a1, and the link literals are among {a mathematical formula}a2,…,aq. This is because, as we can observe, the c and b variables cannot be resolved upon (if two clauses have a conflict in a c or b variable, they are not resolvable as they have at least two conflicts). Thus a tied chain in {a mathematical formula}φW has to look as follows: {a mathematical formula}Di1,…,Diq, where {a mathematical formula}f(ij)=j, i.e. {a mathematical formula}Di1 contains {a mathematical formula}(a1∨a2¯), {a mathematical formula}Diq contains {a mathematical formula}(aq∨a1) or vice versa if we look at the tied chain in the opposite direction. We shall assume without loss generality that the former is the case (i.e. {a mathematical formula}Di1 contains {a mathematical formula}(a1∨a2¯) and {a mathematical formula}Diq contains {a mathematical formula}(aq∨a1)). For {a mathematical formula}1&lt;j&lt;q clause {a mathematical formula}Dij contains {a mathematical formula}(aj∨aj+1¯). The chain has to have the length q as this is necessary to get from {a mathematical formula}a1 back to {a mathematical formula}a1 through link literals among {a mathematical formula}a2,…,aq. Now, if we look at how clauses {a mathematical formula}Di1,…,Diq can be resolved upon, we get that triples {a mathematical formula}Ei1,…,Eiq must be disjoint to have each consecutive pair in the sequence {a mathematical formula}Di1,…,Diq resolvable. This is because if {a mathematical formula}Dij, {a mathematical formula}Dij+1 are resolvable, then they cannot have a conflict in any b or c variable, which implies that {a mathematical formula}Eij and {a mathematical formula}Eij+1 are disjoint. We can also observe that the b and c variables cannot be cancelled out by resolution and they are therefore all present in the resolvent. Thus, the only possibility is that {a mathematical formula}G′ itself contains all the B and C parts from {a mathematical formula}Di1,…,Diq and thus {a mathematical formula}G′ itself determines the matching.  □
     </paragraph>
     <paragraph label="Theorem 5.7">
      The problem of testing whether a given CNF formula has an empowering implicate is an NP-complete problem.
     </paragraph>
     <paragraph label="Proof">
      The NP membership is proved in Lemma 5.1. The NP-hardness follows from the reduction defined by Definition 5.2 using Lemma 5.4 and Lemma 5.6. Note that by Lemma 3.2 it is enough to consider prime empowering implicates and thus the assumption that G is a prime implicate in Lemma 5.6 is not restrictive.  □
     </paragraph>
     <paragraph>
      Using the reduction from Definition 5.2, we can also show that when trying to make a CNF formula propagation complete, we can in general observe an exponential blow up of the number of clauses. In particular we can show that there is a uniform and size increasing family of CNF formulas in which an exponential number of implicates has to be added to a member of this family in order to make it propagation complete. Here by “uniform” we mean that we have a uniform construction which constructs a formula on n variables from this family based only on a parameter n.
     </paragraph>
     <paragraph label="Theorem 5.8">
      There is a uniform and size increasing family of CNF formulas parameterized with the number of variables n and where the number of clauses is{a mathematical formula}O(n), such that the number of implicates that needs to be added to a CNF formula φ on n variables from this family to make it propagation complete is exponential in n (and thus in the size of the formula, too).
     </paragraph>
     <paragraph label="Proof">
      Let us consider an instance of 3DM where {a mathematical formula}|X|=|Y|=|Z|=q and {a mathematical formula}W=X×Y×Z. We claim that at least {a mathematical formula}(q!)2 implicates have to be added to {a mathematical formula}φW to make it propagation complete. First, let us observe that we can find {a mathematical formula}(q!)2 pairwise different perfect matchings in W. This is because each perfect matching in W can be viewed as a pair of perfect matchings in a complete bipartite graph with partities X and Y and a perfect matching in a complete bipartite graph with partities Y and Z. We have q! perfect matchings in each of these bipartite graphs and thus we have {a mathematical formula}(q!)2 possible pairs of them. Note, on the other hand, that {a mathematical formula}w=|W|=q3.Let {a mathematical formula}M={mr1,mr2,…,mrq}, {a mathematical formula}M⊆W be a perfect matching. Let us denote the clause{a mathematical formula} From Lemma 5.4 it follows that {a mathematical formula}HM is an empowering implicate. We claim that if we add {a mathematical formula}HM to {a mathematical formula}φW, then {a mathematical formula}HM′ remains empowering provided {a mathematical formula}M′ is a different matching than M. Since M and {a mathematical formula}M′ are different and {a mathematical formula}|M|=|M′|, we have that {a mathematical formula}M∖M′≠∅ and {a mathematical formula}M′∖M≠∅. Let {a mathematical formula}rℓ be an index of a triple such that {a mathematical formula}mrℓ∈M∖M′. Thus {a mathematical formula}Bg(rℓ)rℓ forms a subclause of {a mathematical formula}HM. Since {a mathematical formula}mrℓ does not belong to {a mathematical formula}M′, we have that {a mathematical formula}g(rℓ) is covered by a different triple {a mathematical formula}rℓ′ in {a mathematical formula}M′. Thus {a mathematical formula}Bg(rℓ′)rℓ′, where {a mathematical formula}g(rℓ′)=g(rℓ), forms a subclause of {a mathematical formula}HM′. If we falsify all literals in {a mathematical formula}HM′ except {a mathematical formula}a1, we get that {a mathematical formula}HM is satisfied, because {a mathematical formula}Bg(rℓ)rℓ and {a mathematical formula}Bg(rℓ′)rℓ′ have a conflict variable. Hence {a mathematical formula}HM plays no role in unit propagation used to possibly derive {a mathematical formula}a1. Whether {a mathematical formula}a1 can or cannot be derived by unit resolution from {a mathematical formula}φW∧HM after falsifying the literals in {a mathematical formula}HM′ except {a mathematical formula}a1 is thus equivalent to whether {a mathematical formula}a1 can be derived by unit resolution from {a mathematical formula}φW after falsifying the literals in {a mathematical formula}HM′ except {a mathematical formula}a1. Note that the above observation can be generalized to the case when we add more than one of these matching clauses to {a mathematical formula}φW and thus it is necessary to add all the clauses corresponding to perfect matchings to {a mathematical formula}φW to make it propagation complete.It follows that the number of implicates needed to be added to {a mathematical formula}φW to make it propagation complete is at least {a mathematical formula}(q!)2 which is exponential in the size of formula {a mathematical formula}φW consisting of {a mathematical formula}q3 clauses build on {a mathematical formula}q+qw+qw=Θ(q4) variables. Family of the formulas defined in this, with {a mathematical formula}n=Θ(q4), satisfies the proposition of the theorem.  □
     </paragraph>
     <paragraph>
      As we have already discussed in Section 2.5, the result contained in Theorem 5.8 is in tight connection to the results in [21] where the authors show in Corollary 4 that there is no polynomial sized CNF decomposition of any AllDifferent domain consistency propagator. As we have mentioned in Section 2.5, the quasi-polynomial shown in [12] is based on a quasi-polynomial lower bound of Razborov [22] on the size of a monotone circuit computing whether there is a perfect matching in a given graph. Quite interestingly, to the best of our knowledge, there is no stronger lower bound on the size of monotone circuit computing whether a bipartite graph contains perfect matching than the quasi-polynomial shown in [22]. It is thus an interesting question whether a stronger lower bound could not be shown using the connection between domain consistency propagators and monotone circuits shown in [21]. Note that in the proof of Theorem 5.8 we could use a bipartite matching instead of 3DM for constructing the family of CNF formulas with required properties (we used 3DM mainly to take advantage of Lemma 5.4). Thus, it might be possible to construct a domain consistency propagator for the AllDifferent constraint which contains such a modified family of CNF formulas. On the other hand, it would still be only one example of a domain consistency propagator which is not enough to argue about any domain consistency propagator for the AllDifferent constraint.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>