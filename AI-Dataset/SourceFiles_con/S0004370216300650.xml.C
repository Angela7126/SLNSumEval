<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Learning general constraints in CSP.
   </title>
   <abstract>
    We present a new learning scheme for solvers of the Constraint Satisfaction Problem (CSP), which is based on learning (general) constraints rather than the generalized no-goods or signed-clauses that were used in the past. The new scheme is integrated in a conflict-analysis algorithm reminiscent of a modern systematic propositional satisfiability (SAT) solver: it traverses the conflict graph backwards and gradually builds an asserting conflict constraint. This construction is based on new inference rules that are tailored for various pairs of constraints types, e.g., x≤y1+k1 and x≥y2+k2, or y1≤x and [x,y2]⊈[a,b]. The learned constraint is stronger than what can be learned via signed resolution. Our experiments show that our solver HCSP backtracks orders of magnitude less than other state-of-the-art solvers, and is overall on par with the winner of this year's MiniZinc challenge.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Numerous industrial and academic decision and/or optimization problems can be modeled naturally as a Constraint Satisfaction Problems (CSP) [1]. Indeed, problems in scheduling, planning, verification, test generation and more are solved regularly with such tools. The common definition of this problem refers to a set of variables over finite and discrete domains, and a set of constraints over these variables. The decision variant of the CSP (we only refer to this variant in the article and ignore the optimization variant) is to find whether there exists an assignment to the variables from their respective domains that satisfies all the constraints, and emit such an assignment as output if indeed such an assignment exists. For example, we can define five variables {a mathematical formula}x1,…,x5, each with the domains {a mathematical formula}{1..5} and ask whether the constraint AllDifferent{a mathematical formula}(x1,…,x5)∧x3&lt;x1 is satisfiable, where AllDifferent is a constraint requiring its input variables to be assigned different values. There is a common set of constraints that is supported by many CSP solvers called FlatZinc [2], which includes over a hundred constraint types, including Boolean connectives. The decision variant of the CSP is NP-complete. While theoretically it has the same expressive power as propositional satisfiability (SAT) [3], its rich modeling language leads to easier, more succinct modeling, and furthermore, certain types of constraints can be solved efficiently (polynomially) whereas solving their translation to propositional logic is exponential. In practice the benefit of these two differences is not always apparent, because frequently the modeling is done once and then instances are generated automatically and do not need to be readable; furthermore, in practice almost all CSPs combine many types of constraints that at least some of them cannot be solved efficiently, hence the NP-hardness of the problem is evident in practice. The tremendous progress in efficient SAT solving as of the introduction of the SAT solver Chaff [4] in 2001 has led to the development of several competitive CSP solvers (at the time they were developed) that translate the input CSP to SAT, e.g., see [5].
     </paragraph>
     <paragraph>
      The ability of CSP solvers to learn new constraints during the solving process possibly shortens run-time by an exponential factor (see, e.g., [6]). Learning in a limited form was present in early CSP solvers, where it was called nogood learning[7]. Nogoods are defined as partial assignments that cannot be extended to a full solution. Later generalized nogoods[6] (g-nogoods for short) were proposed, which allow non-assignments as well, e.g., a g-nogood ({a mathematical formula}x↚1,y←1) means that an assignment in which x is assigned anything but 1 and y is assigned 1 cannot be extended to a solution. This formalism is convenient for representing knowledge obtained during the search for a solution. The g-nogood above, for example, can result from removing 1 from the domain of x, which leads the solver to remove 1 from the domain of y. G-nogoods may be exponentially stronger than nogoods, as shown in [6]. Another extension is c-nogoods [8], which are like g-nogoods, but a literal can reify a general constraint. c-nogoods are implemented in minion[9] for a few types of constraints.
     </paragraph>
     <paragraph>
      A more general and succinct representation of learned knowledge is in the form of signed clauses. Such clauses are disjunctions of signed literals, where a signed literal has the form {a mathematical formula}v∈D or {a mathematical formula}v∉D (called positive and negative signed literals, respectively), where v is a variable and D is a domain. Beckert et al. [10] studied the satisfiability problem of signed CNF, i.e., satisfiability of a conjunction of signed clauses. Their inference system is based on simplification rules and a rule for binary resolution of signed clauses:{a mathematical formula} where X and Y consist of a disjunction of zero or more literals, A and B are sets of values, and v is called the pivot variable. Note that in case v is Boolean and {a mathematical formula}A,B are complementary Boolean domains (e.g., {a mathematical formula}A={0},B={1}) then this rule simplifies to the standard resolution rule for propositional clauses that is used in SAT, namely the consequent becomes {a mathematical formula}(X∨Y).
     </paragraph>
     <paragraph>
      As we showed in [11], we used this rule in our CSP solver HCSP (short for HaifaCSP),{sup:1} as part of a general learning scheme based on signed clauses. Using a special inference rule for each type of non-clausal constraint, HCSP inferred a signed clause e that explains a propagation by that constraint. This means that e is implied by the constraint, but at the same time is strong enough to make the same propagation as the constraint, at the same state. Using such explanations in combination with rule (1) for resolving signed clauses, HCSP can generate a signed conflict clause via conflict analysis. By construction this clause is asserting (i.e., it necessarily leads to additional propagation after backtracking). In contrast to the CSP solver EFC [6], which generates a g-nogood eagerly for each removed value, HCSP generates a signed explanation clause lazily, only as part of conflict analysis. Lazy learning of g-nogoods was also implemented on top of minion[9]. In [12] propositional explanations are generated for highly active constraints. There has also been work on extending explanations with new Boolean variables, which encode equalities and inequalities [13], [14], lazy model expansion [15] where the formula is lazily grounded (i.e., not related to conflicts), learning non-ground rules in the context of answer-set programming [16], and constraint-specific inference [17], such as partial sums in the case of linear constraints. In all these works there is no direct inference between general constraints.
     </paragraph>
     <paragraph>
      In this article we study a different learning scheme, which is based on inference rules with non-clausal consequents. Non-clausal learning has been studied before in the context of several first-order quantifier-free theories: Pseudo-Boolean constraints (see, e.g., Sect. 22.6.4 in [18] and [19]), difference constraints [20], and integer linear constraints, e.g., [21], [22]. The congruence-closure algorithm for equality logic with uninterpreted functions, which is implemented in most SMT solvers, can also be seen as inferring non-clausal constraints, since it infers new equalities. In all of these cases such learning was shown to improve the search, which motivated us to develop such a scheme for CSP, that is strongly tied to the conflict-analysis procedure. What we suggest here is very general, as it can be used with most of the constraints that are supported by modern CSP solvers, and allows non-clausal inference between different types of constraints.
     </paragraph>
     <paragraph>
      Our main goal in introducing this scheme is to learn a conflict constraint that is logically stronger and not harder to compute than its clausal counterpart. The emphasis is on the first of these goals as it may improve the search itself. To that end, we propose a generic inference rule called Combine that for many popular (pairs of) constraints indeed fulfills these two goals. For example, suppose that a CSP has Boolean variables {a mathematical formula}x,y1,y2,y3, and two constraints (⊕ denotes XOR){a mathematical formula} At a state defined by{a mathematical formula}{a mathematical formula}c1 propagates {a mathematical formula}x∈{1}, and then {a mathematical formula}c2 detects a contradiction. Without going into the details of how clausal explanation works (this will be the subject of Sect. 2.3), in this case it produces the explanation clause{a mathematical formula} whereas our rule Combine produces{a mathematical formula} which is logically stronger. One may argue that this consequent is easy to infer without any general pattern, but the point about our rule is that, in addition to the fact that it is general,
     </paragraph>
     <list>
      <list-item label="•">
       the consequent is in the form of a disjunction where each of the literals has at least one variable less than the original premises,
      </list-item>
      <list-item label="•">
       the inference is guaranteed to be strong enough to contradict the current state,
      </list-item>
      <list-item label="•">
       it frequently generates consequents that are difficult to infer otherwise in an ad-hoc manner, and
      </list-item>
      <list-item label="•">
       the consequent is the strongest possible in a well-defined sense, as we will prove in Lemma 4.2.
      </list-item>
     </list>
     <paragraph>
      The example above had two premises of the same type (xor), but we also use the rule for inferring combinations of constraints of different types, such as {a mathematical formula}y1≤x with {a mathematical formula}[x,y2]⊈[a,b] (here {a mathematical formula}[a,b] denotes a range between two constants a and b). For some combinations of premises, however, we do not use Combine since the result is too complicated to derive or too computationally expensive to support. In such cases we revert to clausal explanations.
     </paragraph>
     <paragraph>
      Our experimental results indicate that indeed the new scheme is better than clausal explanation. For reference, we also compared HCSP to Mistral[23], CPX[24] and iZplus[25], where the last two won the second and first places, respectively, in the ‘free-search, single-core’ track of the 2014 ‘MiniZinc Challenge’ [26] (a CSP competition). HCSP performs better than these tools in terms of average run-time and the number of instances it is able to complete within the given time limit, although in optimization problems iZplus typically finds better solutions. HCSP performs an order of magnitude less backtracks than Mistral and three orders of magnitudes less backtracks than CPX, which proves that the constraints it learns are far more effective in pruning the search.
     </paragraph>
     <paragraph>
      Our contributions in this article can be summarized as follows:
     </paragraph>
     <list>
      <list-item label="•">
       A new learning scheme based on inference of general constraints.
      </list-item>
      <list-item label="•">
       New inference rules for some popular pairs of constraints, used by this scheme.
      </list-item>
      <list-item label="•">
       A new scheme for developing inference rules, called Combine.
      </list-item>
      <list-item label="•">
       A fallback solution for the case when a pair of constraints are not directly supported.
      </list-item>
      <list-item label="•">
       A new competitive CSP solver, HCSP, that is based on this learning scheme.
      </list-item>
      <list-item label="•">
       An empirical study comparing HCSP with other leading solvers.
      </list-item>
     </list>
     <paragraph>
      Compared to the proceedings version of this article [27], we added here more background material about our solver, a more elaborate discussion of conflict analysis in SAT solvers, and soundness proofs of several inference rules derived from Combine. We left some of the longer and more tedious proofs out — those can be found in a technical report [28].
     </paragraph>
     <paragraph>
      The rest of the article is structured as follows. The next section covers background material, including the learning framework that we use and clausal explanations [11]. Sections 3 and 4 describe the new set of inference rules, the requirements from them and the proofs that they fulfill these requirements. In Sec. 3 we also explain how we use clausal explanations as a fallback solution when we are unable to infer a general constraint that satisfies the required properties. We conclude in Sec. 5 with an empirical evaluation and some proposals for future research.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      A CSP is a 3-tuple {a mathematical formula}ϕ=〈V,D,C〉, where {a mathematical formula}V=〈v1,…,vn〉 is the set of problem variables, {a mathematical formula}D=〈D1,…,Dn〉 is the set of their respective domains and {a mathematical formula}C is the set of constraints over these variables. An assignment α satisfies a CSP ϕ if it satisfies all the constraints in {a mathematical formula}C and {a mathematical formula}∀vi∈V.α(vi)∈Di. A CSP is unsatisfiable if there is no assignment that satisfies it.
     </paragraph>
     <paragraph label="Definition 2.1">
      For a CSP solver to support a constraint type, it needs to be able to identify whether constraints of that type are satisfied by a particular assignment to their variables, and to detect what is implied by that constraint in a given state. The algorithm that implements these capabilities is called a propagator of the constraint. More formally: PropagatorGiven a constraint c, a propagator for c is an algorithm satisfying the following requirements:
     </paragraph>
     <list>
      <list-item label="•">
       In a state corresponding to a full assignment, it returns falseif and only if c contradicts the assignment;
      </list-item>
      <list-item label="•">
       Otherwise, if it returns false, then the current state contradicts c;
      </list-item>
      <list-item label="•">
       Otherwise, it may remove (but not add) elements from the domains of some of the variables that c refers to. None of the removed elements is supported by c in the current state.
      </list-item>
     </list>
     <paragraph label="Definition 2.2">
      As an example, consider a constraint {a mathematical formula}c≐x≤y and a state {a mathematical formula}x∈{1,2},y∈{0,1}. Then a propagator of c can remove ‘2’ from the domain of x and ‘0’ from the domain of y, leading to a new state {a mathematical formula}x∈{1},y∈{1}. Had the domain of x been {a mathematical formula}{2,3} the propagator may return false. An ideal propagator has the following property: Precise propagatorA precise propagator is a propagator that
     </paragraph>
     <list>
      <list-item label="•">
       returns falseif and only if c contradicts the current state.
      </list-item>
      <list-item label="•">
       removes all elements from the variables that c refers to, that are not supported by c in the current state.
      </list-item>
     </list>
     <paragraph>
      Specifically, precise propagators guarantee Global Arc Consistency (GAC), which means that every value in the domain of each variable has support in the constraints in which it participates. Not all implemented propagators are precise because of complexity. These are called imprecise propagators. From the perspective of logic, focusing on the role of the propagator as deciding whether c is consistent with the current state, all propagators are sound, but only the precise ones are also complete. We emphasize that the incompleteness of some of the propagators does not imply incompleteness of the CSP solver, because of the first requirement in Definition 2.1.
     </paragraph>
     <section label="2.1">
      Essentials of HCSP
      <paragraph>
       Our solver HCSP supports all the constraint types specified in the FlatZinc format [2]. The engine of HCSP adopts classical ideas from the CSP and SAT literature. We assume the reader is mostly familiar with those, and only mention several highlights briefly. It makes a decision (variable ordering) by selecting a variable with the highest ratio of {a mathematical formula}score to domain-size, where {a mathematical formula}score is calculated similarly to Chaff's VSIDS technique [29]. This can be seen as a variant of the {a mathematical formula}dom/wdeg strategy [30]. The value is initially chosen to be the minimal value in the domain, and after that according to the last assigned value, a technique that is typically referred to by the name phase saving in SAT [31]. It includes restarts, learning, and deletion of learnt-constraints with low activity.
      </paragraph>
      <paragraph>
       HCSP has precise propagators for the following types of constraints (where {a mathematical formula}xi denote variables, {a mathematical formula}bi Boolean variables, {a mathematical formula}ai constants, and {a mathematical formula}⋄∈{=,≤,≥}): {a mathematical formula}x0=x1,x0=−x1, {a mathematical formula}x0⋄abs(x1), {a mathematical formula}x0⋄x1+x2 (with wrap on overflow),{sup:2}{a mathematical formula}x0≤x1⁎x2, {a mathematical formula}x0≥x1⁎x2, {a mathematical formula}x0=min⁡(x1,x2,…), {a mathematical formula}x0=max⁡(x1,x2,…), {a mathematical formula}x0=(b0?x2:x3), {a mathematical formula}x≠0↔y=z, {a mathematical formula}x0∈Set↔x1&lt;x2, {a mathematical formula}x0−x1≥a0, {a mathematical formula}(x0+a0≤x1∨x1+a1≥x0), {a mathematical formula}x0≠x1, {a mathematical formula}AllDifferent(x0,x1,…), {a mathematical formula}[x0,x1+a0]⊆[a1,a2], {a mathematical formula}[x0,x1+a0]⊈[a1,a2], {a mathematical formula}a0⁎x0+a1⁎x1+....≥ak, signed-clauses, and a disjunction of any of the above when there are no shared variables. It has imprecise propagators for {a mathematical formula}x0=x1⁎x2, {a mathematical formula}x0=x1/x2, {a mathematical formula}x0=x1%x2, {a mathematical formula}x0=pow(x1,x2), and table constraints. Complex constraints modeled by a language such as XCSP [32] are rewritten into more basic ones. The rest of this section is focused on the learning mechanism.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Conflict analysis
      </section-title>
      <paragraph>
       An implication graph{a mathematical formula}G(N,E) is a directed acyclic graph in which each node {a mathematical formula}n∈N represents a literal (a variable domain) and each edge {a mathematical formula}c∈E represents a constraint. Incoming edges to a node n can only be labeled with the same constraint. Let {a mathematical formula}(n1,n),…,(nk,n) be the incoming edges of n, all of which are labeled with a constraint c. This represents the fact that starting with domains {a mathematical formula}n1,…,nk the propagator of c inferred the domain in n. The constraint c is called the antecedent of n. Each node is also associated with the decision level in which the domain reduction occurred.
      </paragraph>
      <paragraph>
       When an implication graph ends with a conflict (a node labeled with ⊥), it is called a conflict graph. We will follow a convention by which this graph is depicted with the roots at the left and the sink at the right, and the horizontal position of a node indicates the time it occurred. Examples of conflict graphs can be seen in Fig. 1 (the reader is advised to ignore at this stage the distinction between filled and empty nodes in that figure).
      </paragraph>
      <paragraph>
       HCSP analyzes the conflict graph in order to learn a new constraint, called accordingly a conflict constraint (or a conflict clause in SAT). A conflict constraint is called asserting if there exists a backtrack level in which this constraint necessarily leads to additional propagation. The conflict-analysis function, AnalyzeConflict, indeed computes this level and returns it to the solver, which backtracks accordingly.
      </paragraph>
      <paragraph>
       Conflict-analysis and learning in HCSP is based on the familiar pattern of traversing backward the conflict graph and computing an asserting constraint. Conflict-analysis was used in CSP before, but only while assuming that the constraints are signed clauses, as in MVS [33], or made into signed clauses via explanations (to be described in Sect. 2.3), as in [34], [35]. The conflict-analysis in HCSP is not restricted to clausal inference, and includes various adaptations and optimizations as we describe now. Algorithm 1 shows pseudo-code of AnalyzeConflict as implemented in HCSP. It maintains a set of nodes F, which is initialized to the set of nodes that contradict the input constraint cc. In line 4 it performs a relaxation of F. Relaxation appeared first in our technical report [34]; A similar idea appeared also in [36]. Relaxation means that each node in F is ‘pushed’ to the left as long as the constraint {a mathematical formula}Cons remains conflicting. Generally this is possible when domain reductions are redundant, as demonstrated in the following example.
      </paragraph>
      <paragraph label="Example 2.1">
       Consider the constraints{a mathematical formula} and the conflict graph in Fig. 1 (left).In Algorithm 1, initially {a mathematical formula}Cons=c3, and hence after line 2 {a mathematical formula}F={x∈{2},y∈{2},u∈{0}} (those are marked with empty circles). Relaxation in line 4 replaces in F the node {a mathematical formula}y∈{2} with the node {a mathematical formula}y∈{2,3}, because the new F also contradicts the current constraint {a mathematical formula}Cons. Fig. 1(right) shows this. The reason that this is possible is that the domain reduction by {a mathematical formula}c2 is redundant in the current state, because when {a mathematical formula}u=0, {a mathematical formula}c3 is capable of removing this value by itself. Such cases appear frequently, because the order in which constraints are processed is not optimal.  □
      </paragraph>
      <paragraph>
       Relaxation is necessary for several reasons: a) preventing a situation in which the learned clause is still conflicting immediately after backtracking, instead of being asserting, b) in Sec. 4.3 we rely on relaxation in the development of some of the inference rules, and c) our experiments show that without it many more cases fall back to clausal explanations, because relaxation enables to circumvent them.
      </paragraph>
      <paragraph>
       Let us return to the description of Algorithm 1. In lines 5–9 AnalyzeConflict gradually updates the constraint {a mathematical formula}Cons. It does so by traversing the conflict graph backwards (i.e., going left, from the conflict node towards the decision node) while updating F and the constraint {a mathematical formula}Cons such that the following loop invariants are maintained:
      </paragraph>
      <list>
       <list-item label="1.">
        Invar1.{a mathematical formula}Cons contradicts the domains defined by F, and is able to detect it via propagation.{sup:3}
       </list-item>
       <list-item label="2.">
        Invar2. No two nodes in F refer to the same variable.
       </list-item>
      </list>
      <paragraph>
       It should be clear that these invariants are maintained at the entry to the loop, because of the definition of F, {a mathematical formula}Cons, and relaxation. Infer and GetNewSet are targeted towards maintaining it as will be evident later. The traversal stops in line 5 once the function stop detects that {a mathematical formula}Cons is asserting, or that it conflicts the domains at decision level 0. In the latter case the function AssertingLevel returns −1 to the solver, which accordingly declares the CSP to be unsatisfiable. In line 8 the current constraint {a mathematical formula}Cons is replaced with a constraint that is inferred from {a mathematical formula}Cons itself and the antecedent constraint of a node in F. The function Infer is the main contribution of this article and will be discussed in later sections.
      </paragraph>
      <paragraph>
       Let us now shift our focus to GetNewSet, which updates the set F. Initially it replaces {a mathematical formula}pivot with its parents. In case there is more than one node in F representing the same variable, in line 16 the function distinct leaves only the right-most one. There may be multiple entries of a variable in F because a parent of {a mathematical formula}pivot may represent a variable that already labels a different node in F owing to relaxation (line 11) in a previous iteration.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Clausal explanations
      </section-title>
      <paragraph label="Definition 2.3">
       Generic explanations were used in the past (e.g., [6], [9]) for learning of g-nogoods. The scheme we describe here uses inference rules specialized for each constraint type, resulting in signed clauses. Such clausal explanations are important in our context both for understanding the alternative mechanism that we used in [11] (we use it as one of the points of reference for comparing the results), and because we still use it as a fallback solution when, e.g., we reach pairs of constraints for which we do not have an inference rule. Let us begin by formally defining the notion of explanation. Clausal explanationLet {a mathematical formula}l1,…,ln be signed literals at the current state (each literal represents the current domain of a variable), and let c be a constraint that propagates the new signed literal l, i.e., {a mathematical formula}(l1∧…∧ln∧c)→l. Then a clause e is an explanation of this propagation if the following two conditions hold:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph label="Example 2.2">
       Eq. (3) guarantees that the new clause e is logically implied by an existing constraint, hence we do not lose soundness. Eq. (4) guarantees that it is still strong enough to imply the same literal. It is always possible to derive an explanation from a constraint, regardless of the constraint type [11]. The following rule from [11] provides a clausal explanation for an inequality constraint:{a mathematical formula} where m is a parameter instantiating it (the rule is sound for any m). It is perhaps more intuitive to rewrite the consequent as {a mathematical formula}x&gt;m→y≥m+1, which is obviously implied by the premise for any m. Note that the consequent is a signed clause. Now consider two literals:{a mathematical formula} and the constraint{a mathematical formula} which implies in the context of {a mathematical formula}l1,l2 the literal{a mathematical formula} (note that {a mathematical formula}y∈[1,2] is also propagated, but we build an explanation for a particular implied literal). Using (5) with {a mathematical formula}m=max⁡(y)=2 we obtain the explanation{a mathematical formula} and indeed (3) and (4) hold, since {a mathematical formula}c→e and {a mathematical formula}(l1∧l2∧e)→l. In [11] alternatives to choosing {a mathematical formula}m=max⁡(y) are discussed.  □
      </paragraph>
      <paragraph>
       In [11] we showed how HCSP generates a signed conflict clause with an inference system based on signed resolution (1), that is reminiscent of how SAT solvers use binary resolution. Explanations are used for bridging between non-clausal constraints and a signed clause (as in the example above), and (1) is used for resolving signed clauses.
      </paragraph>
      <paragraph label="Example 2.3">
       The following demonstrates conflict analysis with clausal explanations. In addition to (5), we will use a variant of this rule for strict inequality:{a mathematical formula} We will use the observation that if {a mathematical formula}c→e, then {a mathematical formula}(l∨c)→(l∨e), to handle disjunctions. Let {a mathematical formula}Dx={0,1}, {a mathematical formula}Dy={0,1}, {a mathematical formula}Dz={0..100}, and{a mathematical formula}{an inline-figure} The conflict graph on the left shows the decision ({a mathematical formula}Dz={0}), and then that {a mathematical formula}c1 propagates {a mathematical formula}Dx={0}, {a mathematical formula}Dy={1} in this order, and finally that {a mathematical formula}c2 detects a conflict. Now {a mathematical formula}F={z∈{0},x∈{0},y∈{1}} and {a mathematical formula}pivot={y∈{1}}. Then {a mathematical formula}c2 generates the explanation{a mathematical formula} based on {a mathematical formula}LE(0) (see (5)), and {a mathematical formula}c1 generates the explanation{a mathematical formula} based on {a mathematical formula}L(0) (see (6)). Resolving the two explanations on y yields{a mathematical formula} Now {a mathematical formula}pivot=x∈{0}. {a mathematical formula}c1 explains the propagation of x with the clause{a mathematical formula} based on {a mathematical formula}L(1). Resolving it with (7) on x yields{a mathematical formula}Now F is equal to the three nodes on the left. (8) is now asserting, since e.g., at the previous decision level {a mathematical formula}z∈{9,10} is implied.  □
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Non-clausal inference: requirements
     </section-title>
     <paragraph>
      In Algorithm 1Infer takes as input the constraints {a mathematical formula}Cons(x,y→) and {a mathematical formula}antecedent(x,y→) with a joint variable x that appears at the node {a mathematical formula}pivot, and some set of variables {a mathematical formula}y→, which may or may not be common to both.{sup:4} It outputs a new constraint over {a mathematical formula}x,y→ that is assigned back into {a mathematical formula}Cons. In what follows we will use {a mathematical formula}c1(x,y→) to denote {a mathematical formula}Cons(x,y→), {a mathematical formula}c2(x,y→) to denote {a mathematical formula}antecedent(x,y→), and {a mathematical formula}c⁎(x,y→) to denote the output constraint. We also define{a mathematical formula} Typically, we will discard the parameters and write {a mathematical formula}c1,c2,c⁎,c1∧2 instead.
     </paragraph>
     <paragraph>
      Our first requirement from {a mathematical formula}c⁎ is that it preserves soundness:{a mathematical formula} This guarantees that the constraint eventually learned in line 12 is inferred via sound derivations, and is hence implied by the original CSP.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Dx′,Dy‾′ denote the domains of {a mathematical formula}x,y→ right before the propagation of {a mathematical formula}c1. Also, let {a mathematical formula}⊢cp denote the provability relation by constraint propagation, i.e., {a mathematical formula}ϕ⊢cpψ denotes that starting with a set of constraints and domains ϕ, the set of literals ψ is derivable through constraint propagation. Then to preserve Invar1 (see Sec. 2), our second requirement from {a mathematical formula}c⁎ is:{a mathematical formula} In words, constraint propagation is capable of detecting unsatisfiability based on {a mathematical formula}c⁎,Dx′, and {a mathematical formula}Dy‾′. Finally, we aspire to find the strongest {a mathematical formula}c⁎ that satisfies the above requirements, and which is easy to propagate.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Non-clausal inference: rules and their proofs
     </section-title>
     <paragraph>
      Rules R1–R7 in Table 1 are triples {a mathematical formula}〈c1,c2,c⁎〉 that satisfy the two requirements (9) and (10). Rules R8 and R9 satisfy (9) but not necessarily (10). We use them to infer constraints, and then test whether they happen to satisfy (10). In addition, we use the following meta-rule for handling disjunctions:{a mathematical formula} If {a mathematical formula}〈c1,c2,c⁎〉 satisfies (9) and (10), then so does (11). Detailed proofs for all of these rules can be found in a technical report extending this article [28].
     </paragraph>
     <paragraph label="Example 4.1">
      We now show two examples in which the rules lead to stronger learning than explanation-based learning
     </paragraph>
     <list>
      <list-item label="•">
       Recall Example 2.3, which yielded the conflict clause (8). Given the same conflict graph but using the meta rule (11) with pivot y, we learn instead {a mathematical formula}z∈{9,10}, which is clearly stronger. Here is the derivation:{a mathematical formula} According to rule (11){a mathematical formula} where in this case {a mathematical formula}c⁎≡false. This last fact is detected trivially by our solver, but it can also be detected by applying rule R8 with {a mathematical formula}k1=0,k2=−1.
      </list-item>
      <list-item label="•">
       Consider the domains{a mathematical formula} and constraints{a mathematical formula} Suppose we make a decision {a mathematical formula}z∈{0}. Then {a mathematical formula}c1 propagates {a mathematical formula}x∈{10} and {a mathematical formula}c2 detects a conflict. Using rule R2 with {a mathematical formula}k1=k2=0, and the meta rule (11) we obtain:{a mathematical formula}Using explanations instead, {a mathematical formula}c2's explanation via {a mathematical formula}LE(9) is{a mathematical formula}{a mathematical formula}c1's explanation via {a mathematical formula}LE(7) is{a mathematical formula} and resolving these explanations on the pivot x yields{a mathematical formula} Note that the right two disjuncts of (13) are equal to {a mathematical formula}y1≤7∨y2≥10, whereas the predicate {a mathematical formula}[y1,y2]⊈[8,9] in (12) is equal to {a mathematical formula}(y1≤7∨y2≥10)∧y1≤y2, which is stronger. This is because if {a mathematical formula}y1&gt;y2 then {a mathematical formula}[y1,y2]=∅, and {a mathematical formula}∅⊆[8,9]).  □
      </list-item>
     </list>
     <paragraph>
      Most of the entries in the table were developed by instantiating a general inference rule called Combine (see Sec. 4.1 below), which satisfies these requirements. In some other cases instantiating it turned out to be too complicated and we found {a mathematical formula}c⁎ without it. Sec. 4.3 includes proofs for some of these other rules.
     </paragraph>
     <paragraph>
      In some cases plain conjunction is the best alternative we found. For example, the conjunction of {a mathematical formula}x≠y and {a mathematical formula}x≠z can be efficiently propagated and if, later, in conflict analysis, the constraint {a mathematical formula}y≠z is encountered, then it is possible to infer {a mathematical formula}AllDifferent(x,y,z). This is stronger that what Combine can infer.
     </paragraph>
     <paragraph>
      Infer uses explanation-based inference (see Sec. 2.3) as a fallback solution. This is necessary because not all combinations of rule types are supported, not all propagators are precise (i.e., logically complete) and not all rules are precise (see R8, R9 in the table). Pseudocode of Infer, which is rather self-explanatory, appears in Algorithm 2.
     </paragraph>
     <section label="4.1">
      A generic inference rule: Combine
      <paragraph>
       Let S be some set of values. Then it is not hard to see that the following is a contradiction for any constraint {a mathematical formula}c(x,y→):{a mathematical formula} or, equivalently, that the following implication is valid:{a mathematical formula} Let {a mathematical formula}X denote the set of values of x which have no support in {a mathematical formula}Dy‾′:{a mathematical formula} Instantiating (15) with {a mathematical formula}c1∧2 for c and with {a mathematical formula}X for S yields the inference rule that we call Combine:{a mathematical formula}
      </paragraph>
      <paragraph>
       Since (17) is just an instantiation of (15), then (17) is clearly sound, and hence (9) is satisfied. To satisfy (10) we first prove logical entailment {a mathematical formula}(⊨), which is weaker than the requirement of (10) for provability ({a mathematical formula}⊢cp).
      </paragraph>
      <paragraph label="Proof">
       For{a mathematical formula}c⁎≐(x∉X∨∃x′∈X.c1∧2(x′,y→)), the following relation holds:{a mathematical formula}c⁎,Dx′,Dy‾′⊨⊥.Falsely assume that {a mathematical formula}c⁎ is satisfied for an assignment of values {a mathematical formula}a∈Dx′,b→∈Dy‾′ to {a mathematical formula}x,y→, respectively. Consider the two disjuncts of {a mathematical formula}c⁎:
      </paragraph>
      <list>
       <list-item label="•">
        Suppose {a mathematical formula}x∉X is satisfied. Considering the definition of {a mathematical formula}X in (16), this implies that a is supported in {a mathematical formula}c1∧2, or formally{a mathematical formula} Based on Invar1 we know that {a mathematical formula}c1∧2(x,y→),Dx′,Dy‾′⊨⊥, and hence {a mathematical formula}∀x∈Dx′¬∃y→∈Dy‾′.c1∧2(x,y→), and particularly for {a mathematical formula}x=a, {a mathematical formula}¬∃y→∈Dy‾′.c1∧2(a,y→), which contradicts (18).
       </list-item>
       <list-item label="•">
        Now suppose {a mathematical formula}∃x′∈X.c1∧2(x′,y→) is satisfied. Expanding {a mathematical formula}X and substituting {a mathematical formula}y→ with its assignment {a mathematical formula}b→ yields{a mathematical formula} Since {a mathematical formula}b→∈Dy‾′ and {a mathematical formula}¬c1∧2(x′,y→′) is satisfied for all {a mathematical formula}y→′∈Dy‾′, then it is satisfied for {a mathematical formula}y→′=b→. This implies a contradiction: {a mathematical formula}∃x′.¬c1∧2(x′,b→)∧c1∧2(x′,b→).
       </list-item>
      </list>
      <paragraph>
       It is trivial to see that this lemma implies (10) when {a mathematical formula}⊢cp is precise constraint propagation. When imprecise propagation is involved, e.g., {a mathematical formula}⊢cp is defined by bounds consistency [37], HCSP checks whether the constraint happens to be conflicting, and if not it falls back to clausal explanation.
      </paragraph>
      <section label="4.1.1">
       The relative strength of Combine
       <paragraph>
        We prove below two observations about the strength of Combine:
       </paragraph>
       <list>
        <list-item label="•">
         There is no alternative to {a mathematical formula}X for replacing S in (15) that makes the resulting constraint stronger, and
        </list-item>
        <list-item label="•">
         The signed clause that we obtain through the explanation mechanism—see Sec. 2.3—cannot yield a stronger consequent.
        </list-item>
       </list>
       <paragraph label="Proof">
        Consider all possible formulas of the form{a mathematical formula}ψ(x,y→)≡(x∉P∨φ(y→)), for a given set P. The strongest possible{a mathematical formula}φ(y→), which meets all the requirements is{a mathematical formula}∃x′∈P.c1∧2(x′,y→). In other words, for any{a mathematical formula}φ(y→)which makes{a mathematical formula}ψ(x,y→)meet the requirements, the following is satisfied:{a mathematical formula}By negation, assume that there is an assignment {a mathematical formula}b→ to {a mathematical formula}y→ which satisfies {a mathematical formula}∃x′∈P.c1∧2(x′,b→) but not {a mathematical formula}φ(b→). This means that there is an {a mathematical formula}a∈P which satisfies {a mathematical formula}c1∧2(a,b→) when {a mathematical formula}¬φ(b→). Because {a mathematical formula}c1∧2(a,b→) is satisfied, (9) mandate that {a mathematical formula}ψ(a,b→) should also be satisfied. According to the definition of ψ we conclude that either {a mathematical formula}a∉P or {a mathematical formula}φ(b→) have to be satisfied. But since {a mathematical formula}¬φ(b→) and, as defined, {a mathematical formula}a∈P we conclude that ψ is unsatisfied with {a mathematical formula}a,b→. This conflict the initial assumption. This leads to the conclusion that if {a mathematical formula}∃x′∈P.c1∧2(x′,y→) is satisfied, then {a mathematical formula}φ(y→) must also be satisfied.  □
       </paragraph>
       <paragraph label="Proof">
        Note that this lemma refers to P, and not {a mathematical formula}X. This means that it does not rule out the possibility where {a mathematical formula}∃x′∈P.c1∧2(x′,y→) is stronger than {a mathematical formula}∃x′∈X.c1∧2(x′,y→). It is quite possible that the smaller the set P is and the weaker the literal {a mathematical formula}x∉P is, the stronger {a mathematical formula}∃x′∈P.c1∧2(x′,y→) becomes. Consider all possible{a mathematical formula}ψ(x,y→)≡(x∉P∨∃x′∈P.c1∧2(y→))which satisfy the requirements. P must satisfy{a mathematical formula}By negation assume that {a mathematical formula}Dx′⊈P, i.e., there is a value a such that {a mathematical formula}a∈Dx′ and {a mathematical formula}a∉P. Consider how this affects (10). According to (10),{a mathematical formula} Since {a mathematical formula}a∈Dx′ then we can replace x with a in the above formula, and get{a mathematical formula} But since a was defined such that {a mathematical formula}a∉P then the above formula becomes{a mathematical formula} This basically says {a mathematical formula}true⊢cp⊥, which is impossible. It implies that the assumption that {a mathematical formula}Dx′⊈P is incorrect.  □
       </paragraph>
       <paragraph label="Proof">
        Consider all possible{a mathematical formula}ψ(x,y→)≡(x∉P∨∃x′∈P.c1∧2(y→))which satisfy the requirements. P must satisfy{a mathematical formula}Where{a mathematical formula}Xwas defined above as{a mathematical formula}According to the definition of {a mathematical formula}X, the lemma can be reformulated as{a mathematical formula} Assume, by negation, that this is not correct. In other words there are {a mathematical formula}a∈P and {a mathematical formula}b→∈Dy‾′ such that {a mathematical formula}c1∧2(a,b→). We will show that this conflicts (10).From (10) we know that{a mathematical formula} Since {a mathematical formula}b→∈Dy‾′, the formula above implies{a mathematical formula}Assuming {a mathematical formula}⊢cp is precise this implies{a mathematical formula} We now push the negation down, and get{a mathematical formula} First, we see that this implies {a mathematical formula}Dx′⊆P. Since x is independent in the formula we conclude that{a mathematical formula} Now we go back to {a mathematical formula}a∈P and {a mathematical formula}b→∈Dy‾′ which guarantee {a mathematical formula}c1∧2(a,b→), and combine it with the formula above. This means that we can assign {a mathematical formula}x′=a, which leads to {a mathematical formula}¬c1∧2(a,b→), which conflicts with the guarantee of {a mathematical formula}c1∧2(a,b→). This means that our assumption that the lemma is incorrect was wrong, hence {a mathematical formula}P⊆X.  □
       </paragraph>
       <paragraph>
        This lemma implies that the literal {a mathematical formula}x∉X is the strongest possible. This does not imply anything regarding the strength of the second part of the formula, i.e., {a mathematical formula}∃x′∈X.[c1∧2(x′,y→)] may be weakened by strengthening {a mathematical formula}x∉P.
       </paragraph>
       <paragraph label="Proof">
        Also note that the previous lemmas bound P to {a mathematical formula}Dx′⊆P⊆X. There is no alternative{a mathematical formula}ψ(x,y→), different than{a mathematical formula}c⁎, which is stronger than{a mathematical formula}c⁎with{a mathematical formula}X. In other words{a mathematical formula}Recall that we require that {a mathematical formula}ψ(x,y→) to be of the form {a mathematical formula}x∉P∨φ(y→). Lemma 4.2 shows that for a given P, the strongest possible {a mathematical formula}φ(y→) is {a mathematical formula}∃x′∈P.c1∧2(x′,y→). This leaves us to prove that{a mathematical formula} is not stronger than{a mathematical formula} According to Lemma 4.4 because P complies with the given requirements then {a mathematical formula}P⊆X. If {a mathematical formula}P=X the two formulas are equivalent and neither are stronger, otherwise {a mathematical formula}P⊂X.Assume that {a mathematical formula}P⊂X, this means that there is a such that {a mathematical formula}a∈X and {a mathematical formula}a∉P. As a result, for {a mathematical formula}x=a the literal {a mathematical formula}x∉P is true and the literal {a mathematical formula}x∉X is false. In this situation the P based formula, i.e., {a mathematical formula}x∉P∨∃x′∈P.c1∧2(x′,y→) is true, but the {a mathematical formula}X based formula depends solely on{a mathematical formula}We look for a case where this formula is falsified when {a mathematical formula}x=a. It can be falsified, i.e., not a tautology, since otherwise this would conflict (10). This means that there is an assignment {a mathematical formula}b→ to {a mathematical formula}y→ such that the formula is falsified. We have found {a mathematical formula}x=a and {a mathematical formula}y=b→ for which the P-based formula is satisfied and the {a mathematical formula}X-based formula is falsified. This means that the P-based formula is not stronger than the {a mathematical formula}X-based formula.Because the P-based formula is the strongest possible form of {a mathematical formula}x∉P∨φ(y→), any {a mathematical formula}ψ(x,y→) that satisfies the requirements is not stronger than{a mathematical formula} □
       </paragraph>
       <paragraph>
        Note that this theorem does not say that, with {a mathematical formula}X, the resulting constraint is stronger than any other possibility; it says that no other constraint is stronger. In other words, there need not be a strict ordering of constraints.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      Selected rules based on instantiating Combine
      <paragraph>
       We now instantiate Combine(17) with several specific constraints of interest. The derivations rely on various properties of the domains before propagation {a mathematical formula}Dx′,Dy‾′ and right after it {a mathematical formula}Dx″,Dy‾″. By definition{a mathematical formula} We make the following observations about these domains:
      </paragraph>
      <list>
       <list-item label="1.">
        The domain of x, and possibly domains of variables in {a mathematical formula}y→, are reduced by {a mathematical formula}c1:{a mathematical formula}
       </list-item>
       <list-item label="2.">
        Owing to Invar1, in the context of {a mathematical formula}Dx″,Dy‾″, {a mathematical formula}c2 detects a conflict:{a mathematical formula}
       </list-item>
       <list-item label="3.">
        {a mathematical formula}c1 cannot detect a conflict on its own in the context of {a mathematical formula}Dx′,Dy‾′:{a mathematical formula}
       </list-item>
      </list>
      <paragraph>
       We now use these observations when instantiating Combine.
      </paragraph>
      <section label="4.2.1">
       Rule R1: {a mathematical formula}c1≐x∈X1∨A1(y→)c2≐x∈X2∨A2(y→)
       <paragraph>
        {a mathematical formula}A1 and {a mathematical formula}A2 are disjunctions of zero or more literals over the variables of {a mathematical formula}y→. Expanding {a mathematical formula}c1∧2 in (16) yields{a mathematical formula} From (19) and (20) we know that {a mathematical formula}c1(x,y→),Dx′,Dy‾′⊢cpx∈Dx″ and {a mathematical formula}Dx′≠Dx″, which implies that {a mathematical formula}A1(y→),Dy‾′⊨⊥, and consequently simplifies the above to{a mathematical formula} Note that the propagation of {a mathematical formula}c1 in the context of {a mathematical formula}Dy‾′,Dx′ results in {a mathematical formula}Dx″=X1∩Dx′ and {a mathematical formula}Dy‾′=Dy‾″.
       </paragraph>
       <paragraph>
        Since {a mathematical formula}Dy‾′=Dy‾″ and, according to (21), {a mathematical formula}c2(x,y→),Dx″,Dy‾″⊢cp⊥, then {a mathematical formula}A2(y→),Dy‾′⊨⊥. This means that {a mathematical formula}∀y→′∈Dy‾′.¬A2(y→), which simplifies the above formula to{a mathematical formula} Since the inner part does not depend on {a mathematical formula}y→ we can further simplify it to{a mathematical formula} Using this definition of {a mathematical formula}X we examine {a mathematical formula}c⁎:{a mathematical formula} Let {a mathematical formula}A′=∃x′∉(X1∩X2).c1∧2(x′,y→). This simplifies the above to{a mathematical formula} We split the quantifier in {a mathematical formula}A′ into three cases:{a mathematical formula} After taking the definitions of {a mathematical formula}c1∧2, {a mathematical formula}c1, and {a mathematical formula}c2 into account:{a mathematical formula} Next, we eliminate the ∃ quantifier and get{a mathematical formula} We simplify this further by showing that {a mathematical formula}X1∖X2≠∅ and {a mathematical formula}X2∖X1≠∅, which leads to {a mathematical formula}A′=(A1(y→)∨A2(y→)).
       </paragraph>
       <paragraph>
        According to (19), (20), {a mathematical formula}(x∈X1∨A1(y→)),Dx′,Dy‾′⊨x∈Dx″, where {a mathematical formula}Dx″⊂Dx′, which implies that {a mathematical formula}A1(y→),Dy‾′⊨⊥. Similarly {a mathematical formula}(x∈X1∨A1(y→)),Dx″,Dy‾′⊨⊥ implies that {a mathematical formula}A2(y→),Dy‾′⊨⊥. These facts show that {a mathematical formula}A1 and {a mathematical formula}A2 are falsified in this context, meaning that we can focus only on {a mathematical formula}x∈X1 and {a mathematical formula}x∈X2 parts of {a mathematical formula}c1 and {a mathematical formula}c2 there.
       </paragraph>
       <paragraph>
        For the following we assume that {a mathematical formula}⊢cp for signed-clauses is precise, i.e., {a mathematical formula}ψ⊨ϕ iff {a mathematical formula}ψ⊢cpϕ.
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}X2∖X1≠∅. Because {a mathematical formula}c2(x,y→),Dx′,Dy‾′⊬cp⊥ and {a mathematical formula}⊢cp is assumed to be precise then there is an assignment {a mathematical formula}a∈Dx′, {a mathematical formula}b→∈Dy‾′ such that {a mathematical formula}c2(a,b→) is satisfied. Since {a mathematical formula}A2(y→),Dy‾′⊨⊥ and {a mathematical formula}b→∈Dy‾′ we know that {a mathematical formula}A2(b→)⊨⊥, which implies that {a mathematical formula}a∈X2. Further, since {a mathematical formula}(c1(x,y→)∧c2(x,y→)),Dx′,Dy‾′⊨⊥ and {a mathematical formula}c2(a,b→) is satisfied then {a mathematical formula}c1(a,b→)⊨⊥, i.e., {a mathematical formula}(a∈X1∨A1(b→)),Dy‾′⊨⊥. This leads to {a mathematical formula}a∉X1, which together with {a mathematical formula}c∈X2 implies {a mathematical formula}X2∖X1≠∅.
        </list-item>
        <list-item label="•">
         {a mathematical formula}X1∖X2≠∅. Because {a mathematical formula}c1(x,y→),Dx′,Dy‾′⊭⊥ and since {a mathematical formula}A1(y→),Dy‾′⊨⊥ we know that there is at least one element {a mathematical formula}a∈Dx′ such that {a mathematical formula}a∈X1. Again, since {a mathematical formula}(c1(a,y→)∧c2(a,y→)),Dy‾′⊨⊥ and {a mathematical formula}c1(a,y→),Dy‾′⊭⊥ then we know that {a mathematical formula}c2(a,y→),Dy‾′⊨⊥. This implies that {a mathematical formula}a∈X2⊨⊥, i.e., {a mathematical formula}a∉X2. Since {a mathematical formula}a∉X2 and {a mathematical formula}a∈X1 then it follows that {a mathematical formula}X1∖X2≠∅.
        </list-item>
       </list>
       <paragraph>
        These two facts simplify {a mathematical formula}A′ to{a mathematical formula} and correspondingly, according to (23),{a mathematical formula} Note the equivalence of (24) and the result of signed resolution in (1).
       </paragraph>
      </section>
      <section label="4.2.2">
       Rule R2: {a mathematical formula}c1≐y2−x≥k2c2≐x−y1≥k1
       <paragraph>
        Expanding {a mathematical formula}c1∧2 in (16) yields{a mathematical formula} The complement of {a mathematical formula}X can be written as{a mathematical formula} Recall (16): {a mathematical formula}x∉X∨∃x′∈X.c1∧2(x′,y→). The right disjunct is equal to:{a mathematical formula} We use (25) to rewrite (26):{a mathematical formula} which implies{a mathematical formula} Hence, the rule is{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.2.3">
       Rule R6: {a mathematical formula}c1≐[x,y]⊈[a1,b1]c2≐[y,x]⊈[a2,b2]
       <paragraph>
        We have {a mathematical formula}c1∧c2→x=y, because otherwise, e.g., if {a mathematical formula}x&lt;y, then {a mathematical formula}c2 is trivially false. Since {a mathematical formula}x=y then their joint value cannot be contained in either of the ranges {a mathematical formula}[a1,b1],[a2,b2]. Hence,{a mathematical formula} which implies{a mathematical formula} The consequent of Combine is{a mathematical formula} Hence, the resulting rule in this case is{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.2.4">
       Rule R7: {a mathematical formula}c1≐xor(x,y→)c2≐xor(x,z→)
       <paragraph>
        Here {a mathematical formula}y→≐y1,…,yn and {a mathematical formula}z→≐z1,…,zm. We assume that {a mathematical formula}y→ and {a mathematical formula}z→ are fully assigned and x is not; we further assume that, without lose of generality, {a mathematical formula}c1 propagates the value of x and {a mathematical formula}c2 detects a conflict.
       </paragraph>
       <paragraph>
        Under these assumptions it is clear that {a mathematical formula}c1 and {a mathematical formula}c2 cannot be simultaneously satisfied by either {a mathematical formula}x=0 or {a mathematical formula}x=1, and hence by definition {a mathematical formula}X={0,1}, and Combine amounts to:{a mathematical formula} We can replace {a mathematical formula}x∉{0,1} with false and obtain:{a mathematical formula}
       </paragraph>
       <paragraph>
        It is not hard to see that the consequent is equivalent to {a mathematical formula}xor(y→)=xor(z→), and hence also to {a mathematical formula}xor(y→,z→,1), which brings us to the desired rule:{a mathematical formula} Note that variables that are shared by {a mathematical formula}y→ and {a mathematical formula}z→ can be removed from the xor predicate without changing its value.
       </paragraph>
      </section>
     </section>
     <section label="4.3">
      Selected rules not based on Combine
      <paragraph>
       We now describe several rules that are not based on Combine.
      </paragraph>
      <section label="4.3.1">
       Rule R3: {a mathematical formula}c1≐y1≤xc2≐[x,y2]⊈[a,b]
       <paragraph>
        We assume that at the point of conflict, replacing {a mathematical formula}c2 with {a mathematical formula}x≤y2 makes {a mathematical formula}c1∧2 too weak to detect the conflict. Otherwise we simply use rule R2. Based on this assumption, which we denote by ψ, we now develop {a mathematical formula}X. ψ means that {a mathematical formula}[x,y2]⊈[a,b] removes at least one value from {a mathematical formula}Dx′ more than {a mathematical formula}x≤y2. The extra value removed α should satisfy{a mathematical formula} This means that{a mathematical formula} From this we conclude that{a mathematical formula} We require that neither constraints detect a conflict by themselves with {a mathematical formula}Dy1′, {a mathematical formula}Dy2′, and {a mathematical formula}Dx′, but when propagated consecutively they reach a conflict. This means that there is at least one value {a mathematical formula}α∈Dx′ such that{a mathematical formula} This can be simplified to{a mathematical formula} If such α exists then it can be equal to {a mathematical formula}max⁡(Dx′) such that{a mathematical formula}
       </paragraph>
       <paragraph>
        To summarize, we have concluded that{a mathematical formula} The interval expression can be expanded such that{a mathematical formula} This is simplified to{a mathematical formula} Since {a mathematical formula}a≤max⁡(Dy2′) then if {a mathematical formula}max⁡(Dx′)&gt;max⁡(Dy2′) is satisfied then {a mathematical formula}max⁡(Dx′)&gt;max⁡(Dy2′)≥a, i.e., {a mathematical formula}Dx′≥a, is implied. This means that {a mathematical formula}max⁡(Dx′)&gt;max⁡(Dy2′) is redundant in the above expression, generating:{a mathematical formula} We will depict this as{a mathematical formula}
       </paragraph>
       <paragraph>
        We require that the resulting constraint be of the form{a mathematical formula} and meet the soundness and completeness requirements. First we look for {a mathematical formula}X which is defined by{a mathematical formula} We expand the interval operator to{a mathematical formula} Since {a mathematical formula}y1 is bounded only from below and {a mathematical formula}y2 only from above then we can safely rewrite this expression for the worse cases of {a mathematical formula}y1 and {a mathematical formula}y2 which are {a mathematical formula}min⁡(Dy1′) and {a mathematical formula}max⁡(Dy2′):{a mathematical formula}
       </paragraph>
       <paragraph>
        From the initial assumptions, as expressed by Equation (30), we know that {a mathematical formula}max⁡(Dy2′)≤b is true. From, this we conclude that {a mathematical formula}(a≤x′∧max⁡(Dy2′)≤b) can be simplified to {a mathematical formula}a≤x′. This yields{a mathematical formula} Equation (30) also states that {a mathematical formula}a≤max⁡(Dy2′) which makes {a mathematical formula}x′&gt;max⁡(Dy2′) redundant in {a mathematical formula}x′&gt;max⁡(Dy2′)∨a≤x. So the expression becomes{a mathematical formula} We propose the following consequent:{a mathematical formula}{a mathematical formula} Note that {a mathematical formula}c⁎ still follows our general pattern, by which the pivot is separated and not referred-to by the other disjunct. Since we cannot rely on the correctness of the general rule, we now prove that (33) satisfies (9) and (10):
       </paragraph>
       <list>
        <list-item label="•">
         Eq. (9): Falsely assume the contrary, i.e., there are {a mathematical formula}x,y1,y2 such that{a mathematical formula} Expanding {a mathematical formula}X yields{a mathematical formula} If {a mathematical formula}x&lt;min⁡(Dy1′) then {a mathematical formula}y1≤x implies {a mathematical formula}y1&lt;min⁡(Dy1′) which conflicts {a mathematical formula}[y1,y2]⊆[min⁡(Dy1′),b]. Otherwise, {a mathematical formula}x≥a and {a mathematical formula}[x,y2]⊈[a,b] implies {a mathematical formula}y2&gt;b which conflicts {a mathematical formula}[y1,y2]⊆[min⁡(Dy1′),b].
        </list-item>
        <list-item label="•">
         Eq. (10): We need to check that{a mathematical formula} where {a mathematical formula}ψ′ is an expression defined by Equation (30). Falsely assume that{a mathematical formula} The part of x can be simplified such that{a mathematical formula} But according to the construction of {a mathematical formula}X we know that {a mathematical formula}Dx′∖X=∅, so the expression is further simplified to{a mathematical formula} or{a mathematical formula} Since {a mathematical formula}y1 is bounded only from above and {a mathematical formula}y2 is bounded from below then we can replace {a mathematical formula}y1 with {a mathematical formula}min⁡(Dy1′) and {a mathematical formula}y2 with {a mathematical formula}max⁡(Dy2′):{a mathematical formula}{a mathematical formula}min⁡(Dy1′)&lt;min⁡(Dy1′) is clearly false, and from the definition of {a mathematical formula}ψ′ we know that {a mathematical formula}b&lt;max⁡(Dy2′) is false. This falsifies {a mathematical formula}min⁡(Dy1′)&lt;min⁡(Dy1′)∨b&lt;max⁡(Dy2′) from the expression, hence the whole expression is also falsified. Hence our assumption was wrong, i.e., (10) is not violated.
        </list-item>
       </list>
       <paragraph>
        To summarize, the rule is{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.3.2">
       Rule R8: {a mathematical formula}c1≐(y≤x+k1)c2=(x≤y+k2)
       <paragraph>
        Isolating {a mathematical formula}x−y on both sides yields {a mathematical formula}c1∧2(x,y)=−k1≤x−y≤k2, which is false if {a mathematical formula}k1+k2&lt;0. Since it is simply a conjunction of the input constraints, then (9) and (10) are satisfied trivially.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      We performed two sets of experiments as described below. All experiments were ran on a 4 core Intel® Xeon® 2.5 GHz.
     </paragraph>
     <paragraph>
      The 2009 CSP solver competition benchmarks. Here we used a subset of benchmarks of the Fourth International CSP Solver competition [32] (this was the last CSP competition, before the MiniZinc challenge started). Specifically out of over 7000 in the competition's satisfiability benchmark-set, we focused on the 2162 benchmarks that have at least one comparison operator from {a mathematical formula}{&lt;,≤,≥,&gt;} (the reason being that the rules in Table 1 refer to combinations of constraints based on these operators and constraints that are consequents of these rules). The CPU time limit was set to 1200 seconds. Out-of-memory and time-outs are called ‘fails’ in the discussion below.
     </paragraph>
     <paragraph>
      We compared three different settings: (1) HCSP with general constraints learning based on Combine (from here on— HCSP), (2) HCSP using only clause-based learning with explanations, as described in Sec. 2 (from here on—Explain),{sup:5} and (3) Mistral[23] latest version (1.550).
     </paragraph>
     <paragraph>
      Fig. 2 compares these three engines. Memory was limited to 1 GiB. Number of fails in HCSP was 25% less than Mistral. Number of fails of HCSP was 4.9% less than Explain.
     </paragraph>
     <paragraph>
      {an inline-figure} The figure on the right compares the number of backtracks considering only non-failing runs in all solvers (log-scale). The average number of backtracks in HCSP is 2045, in Explain 4389, and in Mistral 49562. This drastic difference in the average backtrack-count indicates that the cost of learning is compensated-for by a better search.
     </paragraph>
     <paragraph>
      We also checked whether the difference between HCSP and Explain is affected by whether the instance is satisfiable or not. Table 2 summarizes this comparison.
     </paragraph>
     <paragraph>
      MiniZinc benchmarks. Given the recent results of the MiniZinc challenge, we compared HCSP and Explain to CPX and iZplus, which won the second and first places, respectively, of the ‘free-search/single-core’ track of the MiniZinc challenge [26].{sup:6}iZplus is based on the iZ-C constraint programming library, and includes stochastic local search for optimization problems. CPX is based on lazy clause generation (i.e., lazy reduction to SAT). We used all the 100 benchmarks of the competition, 75 of which are optimization problems. The time-limit was set to 1800 sec., and the memory limit to 3 GB. All benchmarks were converted to the FlatZinc format prior to benchmarking. Table 3, Table 4 summarize the results. More detailed results can be found in [38].
     </paragraph>
     <paragraph>
      The columns should be interpreted as follows: time (avg. and median) – the number of seconds in all benchmarks, including time-out and memout cases (in which the time-out of 1800 sec. was assumed); backtracks – the number of backtracks in benchmarks in which all engines finished successfully before the time-out (i.e., in the case of Table 3 which is dedicated to the 75 optimization problems, all engines found the optimal value){sup:7}; success – the number of instances solved within time and memory limits, and in the case of optimization problems found a feasible solution (but not necessarily optimal); In Table 3 we also have Opt. – the number of instances, out of the 75 optimization problems, in which the solver reached optimality and proved it; and wins – the number of optimization instances in which the solver reached the best value among the four contenders (ties are counted).
     </paragraph>
     <paragraph>
      The results show that in the optimization problems iZplus has more wins than HCSP and a slightly smaller run-time in the instances that all solvers solved, and in all other criteria HCSP is better (the wins column depends on the contenders. If HCSP and Explain are on their own, the former wins 65 times and the latter only 62). It is likely that iZplus's wins are due to its local search part that improves the objective function once a solution is found, a component that HCSP does not have. It is worth noting that CPX requires on average more than three orders of magnitude more backtracks compared to HCSP, which we attribute to the fact that CPX learns purely through SAT, and is limited to clauses it already generated. These clauses are not necessarily optimal for conflict analysis. Overall in these experiments 40% of the cases explanation was used as a fall-back solution.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>