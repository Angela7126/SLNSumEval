<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Backdoors to tractable answer set programming.
   </title>
   <abstract>
    Answer Set Programming (ASP) is an increasingly popular framework for declarative programming that admits the description of problems by means of rules and constraints that form a disjunctive logic program. In particular, many AI problems such as reasoning in a nonmonotonic setting can be directly formulated in ASP. Although the main problems of ASP are of high computational complexity, complete for the second level of the Polynomial Hierarchy, several restrictions of ASP have been identified in the literature, under which ASP problems become tractable. In this paper we use the concept of backdoors to identify new restrictions that make ASP problems tractable. Small backdoors are sets of atoms that represent “clever reasoning shortcuts” through the search space and represent a hidden structure in the problem input. The concept of backdoors is widely used in theoretical investigations in the areas of propositional satisfiability and constraint satisfaction. We show that it can be fruitfully adapted to ASP. We demonstrate how backdoors can serve as a unifying framework that accommodates several tractable restrictions of ASP known from the literature. Furthermore, we show how backdoors allow us to deploy recent algorithmic results from parameterized complexity theory to the domain of answer set programming.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Answer Set Programming (ASP) is an increasingly popular framework for declarative programming [115], [122]. ASP admits the description of problems by means of rules and constraints that form a disjunctive logic program. Solutions to the program are so-called stable models or answer sets. Many important problems of AI and reasoning can be succinctly represented and successfully solved within the ASP framework. It has been applied to several large industrial applications, e.g., social networks [97], match making [74], planning in a seaport [129], optimization of packaging of Linux distributions [69], and general game playing [145].
     </paragraph>
     <paragraph>
      The main computational problems for ASP (such as deciding whether a program has a solution, or whether a certain atom is contained in at least one or in all solutions) are complete for the second level of the Polynomial Hierarchy [41]; thus, ASP problems are “harder than NP” and have a higher worst-case complexity than CSP and SAT. In the literature, several restrictions have been identified that make ASP tractable, most prominently the Horn fragment and the stratified fragment [78], [2], for a detailed trichotomy (tractable, first level, second level of PH) see [148].
     </paragraph>
     <section label="1.1">
      <section-title>
       Contribution
      </section-title>
      <paragraph>
       In this paper we use the concept of backdoors to identify new restrictions that make propositional ASP problems tractable. Small backdoors are sets of atoms that represent “clever reasoning shortcuts” through the search space and represent a hidden structure in the problem input. Backdoors were originally introduced by Williams, Gomes, and Selman [152], [153] as a tool to analyze the behavior of DPLL-based SAT solvers.
      </paragraph>
      <paragraph>
       Backdoors have been widely used in theoretical investigations in the area of propositional satisfiability [152], [135], [138], [103] and constraint satisfaction [84], and also for abductive reasoning [125], argumentation [40], and quantified Boolean formulas [137]. A backdoor is defined with respect to some fixed target class for which the computational problem under consideration is polynomial-time tractable. The size of the backdoor can be seen as a distance measure that indicates how far the instance is from the target class.
      </paragraph>
      <paragraph>
       In this paper we develop a rigorous theory of backdoors for answer set programming. We show that the concept of backdoors can be fruitfully adapted for this setting, and that backdoors can serve as a unifying framework that accommodates several tractable restrictions of propositional ASP known from the literature.
      </paragraph>
      <paragraph>
       For a worst-case complexity analysis of various problems involving backdoors such as finding a small backdoor or using it to solve the problem, it is crucial to investigate how the running time depends on the size of the backdoor, and how well running time scales with backdoor size. Parameterized Complexity[35], [55], [85] provides a most suitable theoretical framework for such an analysis. It provides the key notion of fixed-parameter tractability which, in our context, means polynomial-time tractability for fixed backdoor size, where the order of the polynomial does not depend on the backdoor size. We show how backdoors allow us to deploy recent algorithmic results from parameterized complexity theory to the domain of answer set programming.
      </paragraph>
      <paragraph>
       Parameterized complexity provides tools for a rigorous analysis of polynomial-time preprocessing in terms of kernelization[7], [58]. A kernelization is a polynomial-time self-reduction of a parameterized decision problem that outputs a decision equivalent problem instance whose size is bounded by a function f of the parameter (the kernel size). It is known that every decidable fixed-parameter tractable problem admits a kernelization, but some problems admit small kernels (of size polynomial in the parameter) and others do not. We provide upper and lower bounds for the kernel size of the problems backdoor evaluation and backdoor detection for disjunctive answer set programs. These bounds provide worst case guarantees and limits for polynomial-time preprocessing for the considered problems.
      </paragraph>
      <paragraph>
       Several algorithms in the literature are defined for disjunction-free (i.e., normal) programs only. We introduce a general method for lifting these parameters to disjunctive programs, preserving fixed-parameter tractability under certain conditions.
      </paragraph>
      <paragraph>
       Although our main focus is on a theoretical evaluation, we present some experimental results where we consider the backdoor size of structured programs and random programs of varied density.
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Background and related work
      </section-title>
      <section>
       <section>
        <section-title>
         Complexity of ASP problems
        </section-title>
        <paragraph>
         Answer set programming is based on the stable-model semantics for logic programs [78], [79]. The computational complexity of various problems arising in answer set programming has been subject of extensive studies. Eiter and Gottlob [41] have established that the main decision problems of (disjunctive) ASP are complete for the second level of the Polynomial Hierarchy ({a mathematical formula}Σ2P- or {a mathematical formula}Π2P-complete, respectively). Moreover, Bidoít and Froidevaux [5] and Marek and Truszczyński [114] have shown that the problems are NP-complete ({a mathematical formula}co-NP-complete respectively) for disjunction-free (so-called normal) programs. Several fragments of programs where the main reasoning problems are polynomial-time tractable have been identified, e.g., Horn programs [78], stratified programs [2] and programs without even cycles [156]. Dantsin et al. [27] survey the classical complexity of the main reasoning problems for various semantics of logic programming, including fragments of answer set programming.
        </paragraph>
       </section>
       <section>
        <section-title>
         ASP solvers
        </section-title>
        <paragraph>
         Various ASP solvers have been developed in recent years. Many of them utilize SAT solvers as black boxes or search techniques from SAT. There are solvers that deal with one or more fragments of disjunctive programs (normal, tight, or head-cycle-free), e.g., Smodels [141], Assat [111], Cmodels2 [82], and Clasp2 [71]. There are also solvers that deal with the full set of disjunctive programs, e.g., Clasp3 [37], Cmodels3 [108], DLV [107], and GnT [92]. Compilations to other problem domains and respective solvers have been considered for normal programs, e.g., propositional satisfiability [91], mixed integer programming [112], satisfiability modulo theories [93], [76]. We would like to point out that these solvers use heuristics without non-trivial worst-case performance guarantees. In contrast we provide for the main reasoning problems of answer set programming theoretical worst-case time bounds that take certain hidden structures in disjunctive programs into account.
        </paragraph>
        <paragraph>
         Preprocessing techniques and unit propagation used in solvers might be considered in a wider sense as implicitly exploiting Horn fragments. Grounders like Gringo [64] already solve Horn programs simply by propagating atoms which trivially (do not) belong to the minimal model, e.g., atoms that occur in the head of rules with an empty body, atoms that occur in the head of rules where all atoms in the positive body already belong to the minimal model, atoms that cannot belong to the minimal model according to some constraint, and atoms that cannot belong to the minimal model as they occur in no head. Moreover, SAT-based solvers like Clasp [62] transform the program into a propositional formula using Clark's completion (see e.g., [73]) where the resulting formula characterizes the classical models and necessary conditions for atoms to belong to a model. If the program contains no cycles in its positive dependency graph, unit propagation (as part of a DPLL-based algorithm) already solves Horn fragments. Otherwise, loop formulas are added which prevent the solver from assigning true to atoms that occur on a cycle unless some atom from outside is set to true. If there is an atom from outside that has been assigned to true, atoms on the cycle are set again to true by unit propagation and so forth.
        </paragraph>
       </section>
       <section>
        <section-title>
         Parameterizations of ASP
        </section-title>
        <paragraph>
         So far there has been no rigorous study of disjunctive ASP within the framework of parameterized complexity. However, several results known from the literature can be stated in terms of parameterized complexity and provide fixed-parameter tractability. The considered parameters include the number of atoms of a normal program that appear in negative rule bodies [4], the number of non-Horn rules of a normal program [4], the size of a smallest feedback vertex set in the dependency digraph of a normal program [85], the number of cycles of even length in the dependency digraph of a normal program [110], the treewidth of the incidence graph of a normal program [90], [119], and a combination of two parameters: the length of the longest cycle in the dependency digraph and the treewidth of the interaction graph of a head-cycle-free programs [3]. Very recently we established [48] an fpt-reduction that reduces disjunctive ASP to normal ASP; in other words, a reduction from the second level of the Polynomial Hierarchy to the first level. However, these results do not provide fixed-parameter tractability of the ASP reasoning problems, and hence are not directly comparable to the results presented in this paper. A general theoretical framework to classify parameterized problems on whether they admit an fpt-reduction to SAT or not has lately been introduced in [28]. Similar to our result in [48] this does not provide fixed-parameter tractability of the ASP reasoning problems, but in certain cases fixed-parameter tractability of the reduction to SAT.
        </paragraph>
       </section>
       <section>
        <section-title>
         Backdoors
        </section-title>
        <paragraph>
         The concept of a backdoor originates in SAT/CSP and was introduced by Williams et al. [152], [153]. Since then, backdoors have been used frequently in the literature for theoretical investigations. The study of the parameterized complexity of backdoor detection was initiated by Nishimura et al. [123] who considered satisfiability backdoors for the base classes Horn and 2CNF. Since then, the study has been extended to various other base classes, including clustering formulas [124], renamable Horn formulas [128], QHorn formulas [59], Nested formulas [56], acyclic formulas [54], and formulas of bounded incidence treewidth [57]; for a survey, see [55]. Several results extend the concept of backdoors to other problems, e.g., backdoor sets for constraint satisfaction problems [152], quantified Boolean formulas [137], abstract argumentation [40], and abductive reasoning [125]. Samer and Szeider [136] have introduced backdoor trees for propositional satisfiability which provide a more refined concept of backdoor evaluation and take the interaction of variables that form a backdoor into account. Dilkina et al. [31], [32] have considered strong backdoors with “empty clause detection” (empty clauses trivially yield satisfiability). Empty clause detection is present in many modern SAT solvers and often leads to much smaller backdoors in practice. However, they have also established that backdoor detection for the base classes Horn and 2CNF is already harder than NP when empty clause detection is added. Moreover, Szeider [144] has shown that (strong) backdoor detection is {a mathematical formula}W[1]-hard for almost all base classes when empty clause detection is added and thus unlikely to be fixed-parameter tractable.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="1.3">
      <section-title>
       Prior work and paper organization
      </section-title>
      <paragraph>
       This paper is an extended and updated version of the papers that appeared in the proceedings of the 22nd International Joint Conference on Artificial Intelligence [47] and in the selected papers proceedings of the Student Session of the 23rd European Summer School in Logic, Language, and Information [49]. The present paper provides a higher level of detail, in particular full proofs and more examples. Furthermore, the paper extends its previous versions in the following way: additional attention is payed to the minimality check (Lemma 3.7). Theorem 5.13 is extended to entail some very recent results in parameterized complexity theory. A completely new section (Section 6) is devoted to a rigorous analysis of preprocessing methods for the problems of backdoor detection and backdoor evaluation. We present a general method to lift parameters from rules of normal programs to disjunctive programs (Section 7). We extend the section on the theoretical comparison of parameters (Section 8) by additional comparisons to other parameters, e.g., weak feedback width and interaction graph treewidth, and to other classes of programs, e.g., head-cycle-free and tight programs. Additionally, we provide some empirical data on backdoor detection and discuss the evaluation of backdoors in a practical setting in Section 4.1.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <section label="2.1">
      <section-title>
       Answer set programming
      </section-title>
      <paragraph>
       We consider a universe U of propositional atoms. A literal is an atom {a mathematical formula}a∈U or its negation ¬a. A disjunctive logic program (or simply a program) P is a set of rules of the following form{a mathematical formula} where {a mathematical formula}x1,…,xl,y1,…,ym,z1,…,zn are atoms and {a mathematical formula}l,m,n are non-negative integers. Let r be a rule. We write {a mathematical formula}{x1,…,xl}=H(r) (the head of r), {a mathematical formula}{y1,…,ym}=B+(r) (the positive body of r) and {a mathematical formula}{z1,…,zn}=B−(r) (the negative body of r). We denote the sets of atoms occurring in a rule r or in a program P by {a mathematical formula}at(r)=H(r)∪B+(r)∪B−(r) and {a mathematical formula}at(P)=⋃r∈Pat(r), respectively. A rule r is negation-free if {a mathematical formula}B−(r)=∅, normal if {a mathematical formula}|H(r)|≤1, a constraint if {a mathematical formula}|H(r)|=0, constraint-free if {a mathematical formula}|H(r)&gt;0|, Horn if it is normal and negation-free or a constraint, positive if it is Horn and constraint-free, tautological if {a mathematical formula}B+(r)∩(H(r)∪B−(r))≠∅, and non-tautological if it is not tautological. We say that a program has a certain property if all its rules have the property. Horn refers to the class of all Horn programs. We denote the class of all normal programs by Normal. Let P and {a mathematical formula}P′ be programs. We say that {a mathematical formula}P′ is a subprogram of P (in symbols {a mathematical formula}P′⊆P) if for each rule {a mathematical formula}r′∈P′ there is some rule {a mathematical formula}r∈P with {a mathematical formula}H(r′)⊆H(r), {a mathematical formula}B+(r′)⊆B+(r), {a mathematical formula}B−(r′)⊆B−(r). We call a class {a mathematical formula}C of programs hereditary if for each {a mathematical formula}P∈C all subprograms of P are in {a mathematical formula}C as well. Note that many natural classes of programs (and all classes considered in this paper) are hereditary.
      </paragraph>
      <paragraph>
       A set M of atoms satisfies a rule r if {a mathematical formula}(H(r)∪B−(r))∩M≠∅ or {a mathematical formula}B+(r)∖M≠∅. M is a model of P if it satisfies all rules of P. The Gelfond–Lifschitz (GL) reduct of a program P under a set M of atoms is the program {a mathematical formula}PM obtained from P by first removing all rules r with {a mathematical formula}B−(r)∩M≠∅ and second removing all ¬z where {a mathematical formula}z∈B−(r) from the remaining rules r[79]. M is an answer set (or stable model) of a program P if M is a minimal model of {a mathematical formula}PM. We denote by {a mathematical formula}AS(P) the set of all answer sets of P.
      </paragraph>
      <paragraph label="Example 2.1">
       Consider the program P consisting of the following rules:{a mathematical formula} The set {a mathematical formula}M={b,c,f} is an answer set of P, since {a mathematical formula}PM={d←a,e;f←d,c;b←c;e∨c←f;c←d;f} and the minimal models of {a mathematical formula}PM are {a mathematical formula}{b,c,f} and {a mathematical formula}{e,f}.
      </paragraph>
      <paragraph>
       In this paper we generally assume that programs contain no tautological rules since one can simply remove tautological rules from a program without effecting the answer sets, i.e., {a mathematical formula}AS(P)=AS(P′) where {a mathematical formula}P′ is a program obtained from {a mathematical formula}P′ by removing all tautological rules [13, The. 5.5] or [42]. In one case we allow tautological rules and state that explicitly (Proposition 5.10). Moreover, we generally assume that programs contain no rules r where {a mathematical formula}H(r)∩B−(r)≠∅ since one can simply remove from those rules the head atoms in {a mathematical formula}H(r)∩B−(r) without effecting the answer sets, i.e., {a mathematical formula}AS(P)=AS(P′) where {a mathematical formula}P′ is a program obtained from {a mathematical formula}P′ by setting {a mathematical formula}H(r):=H(r)∖B−(r) for every rule r where {a mathematical formula}H(r)∩B−(r)≠∅[42].
      </paragraph>
      <paragraph>
       It is well known that normal Horn programs have a unique answer set or no answer set and that this set can be found in linear time. Van Emden and Kowalski [149] have shown that every constraint-free Horn program has a unique minimal model. Dowling and Gallier [33] have established a linear-time algorithm for testing the satisfiability of propositional Horn formulas which easily extends to Horn programs. In the following we state the well-known linear-time result.
      </paragraph>
      <paragraph label="Lemma 2.1">
       Every Horn program has at most one minimal model which can be found in linear time.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       ASP problems
      </section-title>
      <paragraph>
       We consider the following fundamental ASP problems.
      </paragraph>
      <list>
       Checking
       <list-item>
        A program P and a set {a mathematical formula}M⊆at(P).
       </list-item>
       <list-item>
        Decide whether M is an answer set of P.
       </list-item>
      </list>
      <list>
       Consistency
       <list-item>
        A program P.
       </list-item>
       <list-item>
        Decide whether P has an answer set.
       </list-item>
      </list>
      <list>
       Brave Reasoning
       <list-item>
        A program P and an atom {a mathematical formula}a∈at(P).
       </list-item>
       <list-item>
        Decide whether a belongs to some answer set of P.
       </list-item>
      </list>
      <list>
       Skeptical Reasoning
       <list-item>
        A program P and an atom {a mathematical formula}a∈at(P).
       </list-item>
       <list-item>
        Decide whether a belongs to all answer sets of P.
       </list-item>
      </list>
      <list>
       Counting
       <list-item>
        A program P.
       </list-item>
       <list-item>
        Compute the number of answer sets of P.
       </list-item>
      </list>
      <list>
       Enum
       <list-item>
        A program P.
       </list-item>
       <list-item>
        List all answer sets of P.
       </list-item>
      </list>
      <paragraph>
       We denote by {a mathematical formula}AspReason the family of the reasoning problems Checking, Consistency, Brave Reasoning, and Skeptical Reasoning. We denote by {a mathematical formula}AspFull the family of all the problems defined above. The family {a mathematical formula}AspReason consists of decision problems, and {a mathematical formula}AspFull adds to it a counting and an enumeration problem. In the sequel we will occasionally write {a mathematical formula}LNormal to denote a problem {a mathematical formula}L∈AspFull restricted to input programs from Normal.
      </paragraph>
      <paragraph>
       Checking is {a mathematical formula}co-NP-complete in general [41], but {a mathematical formula}CheckingNormal is polynomial [14]. Consistency and Brave Reasoning are {a mathematical formula}Σ2P-complete, Skeptical Reasoning is {a mathematical formula}Π2P-complete [41]. Both reasoning problems are NP-complete (or {a mathematical formula}co-NP-complete) for normal programs [113], but are polynomial-time solvable for Horn programs [78]. Counting is easily seen to be #P-hard{sup:1} as it entails the problem #SAT.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Parameterized complexity
      </section-title>
      <paragraph>
       Problem instances that originate from practical applications are often structured in a certain way that facilitates to obtain a solution relatively fast. Such instances seem to be harder in theory, where worst-case running times are given in terms of the input size in bits, than they are in practice. The framework of parameterized complexity, introduced by Downey and Fellows [34], takes structural properties of problem instances in form of a parameter into account. In consequence, it offers a framework for a more detailed theoretical analysis that is closer to the practical hardness of problems. In recent years parameterized complexity theory has become a very active research area. Since there are many ways of defining and capturing structure in a problem instance, there are various ways to parameterize a problem. A main concept of parameterized complexity theory is fixed-parameter tractability which relaxes classical polynomial-time tractability in such a way that all non-polynomial parts depend only on the size of the parameter and not on the size of the input.
      </paragraph>
      <paragraph>
       We briefly give some background on parameterized complexity. For more detailed information we refer to other sources [34], [35], [50], [84], [120]. An instance of a parameterized problem L is a pair {a mathematical formula}(I,k)∈Σ⁎×N for some finite alphabet Σ. For an instance {a mathematical formula}(I,k)∈Σ⁎×N we call I the main part and k the parameter. {a mathematical formula}‖I‖ denotes the size of I. L is fixed-parameter tractable if there exist a computable function f and a constant c such that we can decide whether {a mathematical formula}(I,k)∈L in time {a mathematical formula}O(f(k)‖I‖c). Such an algorithm is called an fpt-algorithm. If L is a decision problem, then we identify L with the set of all yes-instances {a mathematical formula}(I,k). FPT is the class of all fixed-parameter tractable decision problems.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}L⊆Σ⁎×N and {a mathematical formula}L′⊆Σ⁎×N be two parameterized decision problems for some finite alphabets Σ and {a mathematical formula}Σ′. An fpt-reduction r from L to {a mathematical formula}L′ is a many-to-one reduction from {a mathematical formula}Σ⁎×N to {a mathematical formula}Σ′⁎×N such that for all {a mathematical formula}I∈Σ⁎ we have {a mathematical formula}(I,k)∈L if and only if {a mathematical formula}r(I,k)=(I′,k′)∈L′ and {a mathematical formula}k′≤g(k) for a fixed computable function {a mathematical formula}g:N→N and there is a computable function f and a constant c such that r is computable in time {a mathematical formula}O(f(k)‖I‖c). Thus, an fpt-reduction is, in particular, an fpt-algorithm. It is easy to see that the class FPT is closed under fpt-reductions. It is clear for parameterized problems {a mathematical formula}L1, and {a mathematical formula}L2 that if {a mathematical formula}L1∈FPT and there is an fpt-reduction from {a mathematical formula}L2 to {a mathematical formula}L1, then {a mathematical formula}L2∈FPT.
      </paragraph>
      <paragraph>
       The Weft Hierarchy consists of parameterized complexity classes {a mathematical formula}W[1]⊆W[2]⊆⋯ which are defined as the closure of certain parameterized problems under parameterized reductions. There is strong theoretical evidence that parameterized problems that are hard for classes W[i] are not fixed-parameter tractable. A prominent {a mathematical formula}W[2]-complete problem is Hitting Set[34], [35] defined as follows:
      </paragraph>
      <list>
       Hitting Set
       <list-item>
        A family of sets {a mathematical formula}(S,k) where {a mathematical formula}S={S1,…,Sm} and an integer k.
       </list-item>
       <list-item>
        The integer k.
       </list-item>
       <list-item>
        Decide whether there exists set H of size at most k which intersects with all the {a mathematical formula}Si (H is a hitting set of {a mathematical formula}S).
       </list-item>
      </list>
      <paragraph>
       The class XP of non-uniform tractable problems consists of all parameterized decision problems that can be solved in polynomial time if the parameter is considered constant. That is, {a mathematical formula}(I,k)∈L can be decided in time {a mathematical formula}O(‖I‖f(k)) for some computable function f. The parameterized complexity class paraNP contains all parameterized decision problems L such that {a mathematical formula}(I,k)∈L can be decided non-deterministically in time {a mathematical formula}O(f(k)‖I‖c) for some computable function f and constant c. A parameterized decision problem is paraNP-complete if it is in NP and NP-complete when restricted to finitely many parameter values [50]. By co-paraNP we denote the class of all parameterized decision problems whose complement (yes and no instances swapped) is in paraNP. Using the concepts and terminology of Flum and Grohe [50], {a mathematical formula}co-paraNP=para-coNP.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Graphs
      </section-title>
      <paragraph>
       We recall some notations of graph theory. We consider undirected and directed graphs. An undirected graph or simply a graph is a pair {a mathematical formula}G=(V,E) where {a mathematical formula}V≠∅ is a set of vertices and {a mathematical formula}E⊆{{u,v}⊆V:u≠v} is a set of edges. We denote an edge {a mathematical formula}{v,w} by uv or vu. A graph {a mathematical formula}G′=(V′,E′) is a subgraph of G if {a mathematical formula}V′⊆V and {a mathematical formula}E′⊆E and an induced subgraph if additionally for any {a mathematical formula}u,v∈V′ and {a mathematical formula}uv∈E also {a mathematical formula}uv∈E′. A path of length k is a graph with {a mathematical formula}k+1 pairwise distinct vertices {a mathematical formula}v1,…,vk+1, and k distinct edges {a mathematical formula}vivi+1 where {a mathematical formula}1≤i≤k (possibly {a mathematical formula}k=0). A cycle of length k is a graph that consists of k distinct vertices {a mathematical formula}v1,v2,…,vk and k distinct edges {a mathematical formula}v1v2,…,vk−1vk,vkv1. Let {a mathematical formula}G=(V,E) be a graph. G is bipartite if the set V of vertices can be divided into two disjoint sets U and W such that there is no edge {a mathematical formula}uv∈E with {a mathematical formula}u,v∈U or {a mathematical formula}u,v∈W. G is complete if for any two vertices {a mathematical formula}u,v∈V there is an edge {a mathematical formula}uv∈E. G contains a clique on {a mathematical formula}V′⊆V if the induced subgraph {a mathematical formula}(V′,E′) of G is a complete graph. A connected component C of G is an inclusion-maximal subgraph {a mathematical formula}C=(VC,EC) of G such that for any two vertices {a mathematical formula}u,v∈VC there is a path in C from u to v.
      </paragraph>
      <paragraph>
       A directed graph or simply a digraph is a pair {a mathematical formula}G=(V,E) where {a mathematical formula}V≠∅ is a set of vertices and {a mathematical formula}E⊆{(u,v)∈V×V:u≠v} is a set of directed edges. A digraph {a mathematical formula}G′=(V′,E′) is a subdigraph of G if {a mathematical formula}V′⊆V and {a mathematical formula}E′⊆E and an induced subdigraph if additionally for any {a mathematical formula}u,v∈V′ and {a mathematical formula}(u,v)∈E also {a mathematical formula}(u,v)∈E′. A directed path of length k is a digraph with {a mathematical formula}k+1 pairwise distinct vertices {a mathematical formula}v1,…,vk+1, and k distinct edges {a mathematical formula}(vi,vi+1) where {a mathematical formula}1≤i≤k (possibly {a mathematical formula}k=0). A directed cycle of length k is a digraph that consists of k distinct vertices {a mathematical formula}v1,v2,…,vk and k distinct edges {a mathematical formula}(v1,v2),…,(vk−1,vk),(vk,v1).
      </paragraph>
      <paragraph>
       We sometimes denote a (directed) path or (directed) cycle as a sequence of vertices. Please observe that according to the above definitions, the length of an undirected cycle is at least 3, whereas the length of a directed cycle is at least 2.
      </paragraph>
      <paragraph>
       A strongly connected component C of a digraph {a mathematical formula}G=(V,E) is an inclusion-maximal directed subgraph {a mathematical formula}C=(VC,EC) of G such that for any two vertices {a mathematical formula}u,v∈VC there are paths in C from u to v and from v to u. The strongly connected components of G form a partition of the set V of vertices, we denote this partition by {a mathematical formula}SCC(G).
      </paragraph>
      <paragraph>
       For further basic terminology on graphs and digraphs we refer to a standard text [30], [11].
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       Satisfiability backdoors
      </section-title>
      <paragraph>
       We also need some notions from propositional satisfiability. A literal is an atom or its negation and a clause is a finite set of literals A CNF formula is a finite set of clauses. A truth assignment is a mapping {a mathematical formula}τ:X→{0,1} defined for a set {a mathematical formula}X⊆U of atoms. For {a mathematical formula}x∈X we put {a mathematical formula}τ(¬x)=1−τ(x). By {a mathematical formula}2X we denote the set of all truth assignments {a mathematical formula}τ:X→{0,1}. The truth assignment reduct of a CNF formula F with respect to {a mathematical formula}τ∈2X is the CNF formula {a mathematical formula}Fτ obtained from F by first removing all clauses c that contain a literal set to 1 by τ, and second removing from the remaining clauses all literals set to 0 by τ. τ satisfies F if {a mathematical formula}Fτ=∅, and F is satisfiable if it is satisfied by some τ.
      </paragraph>
      <paragraph label="Observation 2.2">
       The following is obvious from the definitions: Let F be a CNF formula and X a set of atoms. F is satisfiable if and only if{a mathematical formula}Fτis satisfiable for at least one truth assignment{a mathematical formula}τ∈2X.
      </paragraph>
      <paragraph>
       This leads to the definition of a strong backdoor relative to a class {a mathematical formula}C of polynomially solvable CNF formulas: a set X of atoms is a strong{a mathematical formula}C-backdoor of a CNF formula F if {a mathematical formula}Fτ∈C for all truth assignments {a mathematical formula}τ∈2X. Assume that the satisfiability of formulas {a mathematical formula}F∈C of size {a mathematical formula}‖F‖=n can be decided in time {a mathematical formula}O(nc). Then we can decide the satisfiability of an arbitrary formula F for which we know a strong {a mathematical formula}C-backdoor of size k in time {a mathematical formula}O(2knc) which is efficient as long as k remains small.
      </paragraph>
      <paragraph>
       A further variant of backdoors are deletion backdoors defined by removing literals from a CNF formula. {a mathematical formula}F−X denotes the formula obtained from F by removing all literals {a mathematical formula}x,¬x for {a mathematical formula}x∈X from the clauses of F. Then a set X of atoms is a deletion{a mathematical formula}C-backdoor of F if {a mathematical formula}F−X∈C. In general, deletion {a mathematical formula}C-backdoors are not necessarily strong {a mathematical formula}C-backdoors. If all subsets of a formula in {a mathematical formula}C also belong to {a mathematical formula}C ({a mathematical formula}C is clause-induced), then deletion {a mathematical formula}C-backdoors are strong {a mathematical formula}C-backdoors.
      </paragraph>
      <paragraph>
       Before we can use a backdoor we need to find it first. What we call the backdoor approach is a process consisting of the following two phases:
      </paragraph>
      <list>
       <list-item label="•">
        finding a backdoor (backdoor detection) and
       </list-item>
       <list-item label="•">
        using the backdoor to solve the problem (backdoor evaluation).
       </list-item>
      </list>
      <paragraph>
       For most reasonable target classes {a mathematical formula}C the detection of a strong {a mathematical formula}C-backdoor of size at most k is NP-hard if k is part of the input. However, as we are interested in finding small backdoors, it makes sense to parameterize the backdoor search by k and consider the parameterized complexity of backdoor detection. Indeed, with respect to the classes of Horn CNF formulas and 2-CNF formulas, the detection of strong backdoors of size at most k is fixed-parameter tractable [123]. The parameterized complexity of backdoor detection for many further target classes has been investigated [55].
      </paragraph>
      <paragraph>
       The purpose of this paper is to develop a backdoor approach for answer set programming. It turns out that the evaluation problem is more complicated than for propositional satisfiability (see Section 3.3) and various target classes for answer set programming require new algorithms for backdoor detection (see Section 5).
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Answer set backdoors
     </section-title>
     <section label="3.1">
      <section-title>
       Strong backdoors
      </section-title>
      <paragraph>
       In order to translate the notion of backdoors to the domain of ASP, we first need to come up with a suitable concept of a reduction with respect to a truth assignment. The following is a natural definition which generalizes a concept of Gottlob et al. [85].
      </paragraph>
      <paragraph label="Definition 3.1">
       Let P be a program, X a set of atoms, and {a mathematical formula}τ∈2X. The truth assignment reduct of P under τ is the logic program {a mathematical formula}Pτ obtained from P by
      </paragraph>
      <list>
       <list-item label="1.">
        removing all rules r with {a mathematical formula}H(r)∩τ−1(1)≠∅ or {a mathematical formula}H(r)⊆X;
       </list-item>
       <list-item label="2.">
        removing all rules r with {a mathematical formula}B+(r)∩τ−1(0)≠∅;
       </list-item>
       <list-item label="3.">
        removing all rules r with {a mathematical formula}B−(r)∩τ−1(1)≠∅;
       </list-item>
       <list-item label="4.">
        removing from the heads and bodies of the remaining rules all literals {a mathematical formula}a,¬a with {a mathematical formula}a∈X.
       </list-item>
      </list>
      <paragraph label="Definition 3.2">
       Let {a mathematical formula}C be a class of programs. A set X of atoms is a strong{a mathematical formula}C-backdoor of a program P if {a mathematical formula}Pτ∈C for all truth assignments {a mathematical formula}τ∈2X.
      </paragraph>
      <paragraph>
       By a minimal strong {a mathematical formula}C-backdoor of a program P we mean a strong {a mathematical formula}C-backdoor of P that does not properly contain a smaller strong {a mathematical formula}C-backdoor of P; a smallest strong {a mathematical formula}C-backdoor of P is one of smallest cardinality.
      </paragraph>
      <paragraph label="Example 3.1">
       We consider the program of Example 2.1. The set {a mathematical formula}{b,c} is a strong Horn-backdoor since all four truth assignment reducts {a mathematical formula}Pb¯c¯=Pb=0,c=0={d←a,e;a←d;e←f;f}, {a mathematical formula}Pb¯c={d←a,e;f←d;f}, {a mathematical formula}Pbc¯={d←a,e;e←f;f}, and {a mathematical formula}Pbc={d←a,e;f←d;f} are in the class Horn.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Deletion backdoors
      </section-title>
      <paragraph>
       Next we define a variant of answer set backdoors similar to satisfiability deletion backdoors. For a program P and a set X of atoms we define {a mathematical formula}P−X as the program obtained from P by deleting {a mathematical formula}a,¬a for {a mathematical formula}a∈X from the rules of P. The definition gives rise to deletion backdoors. We will see that finding deletion backdoors is in some cases easier than finding strong backdoors.
      </paragraph>
      <paragraph label="Definition 3.3">
       Let {a mathematical formula}C be a class of programs. A set X of atoms is a deletion{a mathematical formula}C-backdoor of a program P if {a mathematical formula}P−X∈C.
      </paragraph>
      <paragraph>
       In general, not every strong {a mathematical formula}C-backdoor is a deletion {a mathematical formula}C-backdoor, and not every deletion {a mathematical formula}C-backdoor is a strong {a mathematical formula}C-backdoor. But we can strengthen one direction requiring the base class to satisfy the very mild condition of being hereditary (see Section 2) which holds for all base classes considered in this paper.
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}Cis hereditary, then every deletion{a mathematical formula}C-backdoor is a strong{a mathematical formula}C-backdoor.Let P be a program, {a mathematical formula}X⊆at(P), and {a mathematical formula}τ∈2X. Let {a mathematical formula}r′∈Pτ. It follows from Definition 3.1 that {a mathematical formula}r′ is obtained from some {a mathematical formula}r∈P by deleting {a mathematical formula}a,¬a for all {a mathematical formula}a∈X from the head and body of r. Consequently {a mathematical formula}r′∈P−X. Hence {a mathematical formula}Pτ⊆P−X which establishes the proposition.  □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Backdoor evaluation
      </section-title>
      <paragraph>
       An analogue to Observation 2.2 does not hold for ASP, even if we consider the most basic problem Consistency. Take for example the program {a mathematical formula}P={x←y;y←x;←¬x;z←¬x} and the set {a mathematical formula}X={x}. Both reducts {a mathematical formula}Px=0={z} and {a mathematical formula}Px=1={y} have answer sets, but P has no answer set. However, we can show a somewhat weaker asymmetric variant of Observation 2.2, where we can map each answer set of P to an answer set of {a mathematical formula}Pτ for some {a mathematical formula}τ∈2X. This is made precise by the following definition and lemma (which are key for a backdoor approach to answer set programming).
      </paragraph>
      <paragraph label="Definition 3.5">
       Let P be a program and X a set of atoms. We define{a mathematical formula}
      </paragraph>
      <paragraph>
       In other words, the sets in {a mathematical formula}AS(P,X) are answer sets of {a mathematical formula}Pτ for truth assignments τ to {a mathematical formula}X∩at(P) extended by those atoms which are set to true by τ. In the following lemma we will see that the elements in {a mathematical formula}AS(P,X) are “answer set candidates” of the original program P.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}AS(P)⊆AS(P,X)holds for every program P and every set X of atoms.Let {a mathematical formula}M∈AS(P) be chosen arbitrarily. We put {a mathematical formula}X0=(X∖M)∩at(P) and {a mathematical formula}X1=X∩M and define a truth assignment {a mathematical formula}τ∈2X∩at(P) by setting {a mathematical formula}τ−1(i)=Xi for {a mathematical formula}i∈{0,1}. Let {a mathematical formula}M′=M∖X1. Observe that {a mathematical formula}M′∈AS(Pτ) implies {a mathematical formula}M∈AS(P,X) since {a mathematical formula}M=M′∪τ−1(1) by definition. Hence, to establish the lemma, it suffices to show that {a mathematical formula}M′∈AS(Pτ). We have to show that {a mathematical formula}M′ is a model of {a mathematical formula}PτM′, and that no proper subset of {a mathematical formula}M′ is a model of {a mathematical formula}PτM′.In order to show that {a mathematical formula}M′ is a model of {a mathematical formula}PτM′, choose {a mathematical formula}r′∈PτM′ arbitrarily. By construction of {a mathematical formula}PτM′ there is a corresponding rule {a mathematical formula}r∈P with {a mathematical formula}H(r′)=H(r)∖X0 and {a mathematical formula}B+(r′)=B+(r)∖X1 which gives rise to a rule {a mathematical formula}r″∈Pτ, and in turn, {a mathematical formula}r″ gives rise to {a mathematical formula}r′∈PτM′. Since {a mathematical formula}B−(r)∩X1=∅ (otherwise r would have been deleted forming {a mathematical formula}Pτ) and {a mathematical formula}B−(r)∩M′=∅ (otherwise {a mathematical formula}r″ would have been deleted forming {a mathematical formula}PτM′), it follows that {a mathematical formula}B−(r)∩M=∅. Thus, r gives rise to a rule {a mathematical formula}r⁎∈PM with {a mathematical formula}H(r)=H(r⁎) and {a mathematical formula}B+(r)=B+(r⁎). Since {a mathematical formula}M∈AS(P), M satisfies {a mathematical formula}r⁎, i.e., {a mathematical formula}H(r)∩M≠∅ or {a mathematical formula}B+(r)∖M≠∅. However, {a mathematical formula}H(r)∩M=H(r′)∩M′ and {a mathematical formula}B+(r)∖M=B+(r′)∖M′; thus, {a mathematical formula}M′ satisfies {a mathematical formula}r′. Since {a mathematical formula}r′∈PτM′ was chosen arbitrarily, we conclude that {a mathematical formula}M′ is a model of {a mathematical formula}PτM′.In order to show that no proper subset of {a mathematical formula}M′ is a model of {a mathematical formula}PτM′ choose arbitrarily a proper subset {a mathematical formula}N′⊊M′. Let {a mathematical formula}N=N′∪X1. Since {a mathematical formula}M′=M∖X1 and {a mathematical formula}X1⊆M it follows that {a mathematical formula}N⊊M. Since M is a minimal model of {a mathematical formula}PM, N cannot be a model of {a mathematical formula}PM. Consequently, there must be a rule {a mathematical formula}r∈P such that {a mathematical formula}B−(r)∩M=∅ (i.e., r is not deleted by forming {a mathematical formula}PM), {a mathematical formula}B+(r)⊆N and {a mathematical formula}H(r)∩N=∅. However, since M satisfies {a mathematical formula}PM and since {a mathematical formula}B+(r)⊆N⊆M, {a mathematical formula}H(r)∩M≠∅. Thus, r is not a constraint. Moreover, since {a mathematical formula}H(r)∩M≠∅ and {a mathematical formula}M∩X0=∅, it follows that {a mathematical formula}H(r)∖X0≠∅. Thus, since {a mathematical formula}H(r)∩X1=∅, {a mathematical formula}H(r)∖X≠∅. We conclude that r is not deleted when forming {a mathematical formula}Pτ and giving rise to a rule {a mathematical formula}r′∈Pτ, which in turn is not deleted when forming {a mathematical formula}PτM′, giving rise to a rule {a mathematical formula}r″, with {a mathematical formula}H(r″)=H(r)∖X0, {a mathematical formula}B+(r″)=B+(r)∖X1, and {a mathematical formula}B−(r″)=∅. Since {a mathematical formula}B+(r″)⊆N′ and {a mathematical formula}H(r″)∩N=∅, {a mathematical formula}N′ is not a model of {a mathematical formula}PτM′.Thus, we have established that {a mathematical formula}M′ is a stable model of {a mathematical formula}Pτ, and so the lemma follows.  □
      </paragraph>
      <paragraph>
       In view of Lemma 3.6 we shall refer to the elements in {a mathematical formula}AS(P,X) as “answer set candidates.”
      </paragraph>
      <paragraph label="Example 3.2">
       We consider program P of Example 2.1 and the strong Horn-backdoor {a mathematical formula}X={b,c} of Example 3.1. The answer sets of {a mathematical formula}Pτ are {a mathematical formula}AS(Pb¯c¯)={{e,f}}, {a mathematical formula}AS(Pb¯c)={{f}}, {a mathematical formula}AS(Pbc¯)={{e,f}}, and {a mathematical formula}AS(Pbc)={{f}} for {a mathematical formula}τ∈2{b,c}. We obtain the set {a mathematical formula}AS(P,X)={{e,f},{c,f},{b,e,f},{b,c,f}}.
      </paragraph>
      <paragraph>
       In view of Lemma 3.6, we can compute {a mathematical formula}AS(P) by (i) computing {a mathematical formula}AS(Pτ) for all {a mathematical formula}τ∈2X (this produces the set {a mathematical formula}AS(P,X) of candidates for {a mathematical formula}AS(P)), and (ii) checking for each {a mathematical formula}M∈AS(P,X) whether it is an answer set of P. The check (ii) entails (ii.a) checking whether {a mathematical formula}M∈AS(P,X) is a model of P and (ii.b) whether {a mathematical formula}M∈AS(P,X) is a minimal model of {a mathematical formula}PM. We would like to note that in particular any constraint contained in P is removed in the truth assignment reduct {a mathematical formula}Pτ but considered in check (ii.a). Clearly check (ii.a) can be carried out in polynomial time for each M. Check (ii.b), however, is {a mathematical formula}co-NP-complete in general [113], but polynomial for normal programs [14].
      </paragraph>
      <paragraph>
       Fortunately, for our considerations it suffices to perform check (ii.b) for programs that are “close to Normal,” and so the check is fixed-parameter tractable in the size of the given backdoor. More precisely, we consider the following parameterized problem and establish its fixed-parameter tractability in the next lemma.
      </paragraph>
      <list>
       Strong{a mathematical formula}C-Backdoor Asp Check
       <list-item>
        A program P, a strong {a mathematical formula}C-backdoor X of P and a set {a mathematical formula}M⊆at(P).
       </list-item>
       <list-item>
        The size {a mathematical formula}|X| of the backdoor.
       </list-item>
       <list-item>
        Decide whether M is an answer set of P.
       </list-item>
      </list>
      <paragraph label="Proof">
       Hence the second direction of the claim is established, and so the lemma follows.  □
      </paragraph>
      <paragraph>
       Fig. 1 illustrates how we can exploit a strong {a mathematical formula}C-backdoor to find answer sets. For a given program P and a strong {a mathematical formula}C-backdoor X of P we have to consider {a mathematical formula}|2X| truth assignments to the atoms in the backdoor X. For each truth assignment {a mathematical formula}τ∈2X we reduce the program P to a program {a mathematical formula}Pτ and compute the set {a mathematical formula}AS(Pτ). Finally, we obtain the set {a mathematical formula}AS(P) by checking for each {a mathematical formula}M∈AS(Pτ) whether it gives rise to an answer set of P.
      </paragraph>
      <paragraph label="Example 3.3">
       We consider the set {a mathematical formula}AS(P,X)={{e,f},{c,f},{b,e,f},{b,c,f}} of answer set candidates of Example 3.2 and check for each candidate {a mathematical formula}L={e,f}, {a mathematical formula}M={c,f}, {a mathematical formula}N={b,e,f}, and {a mathematical formula}O={b,c,f} whether it is an answer set of P. Therefore we solve the problem StrongHorn-Backdoor Asp Check by means of Lemma 3.7.First we test whether the sets L, M, N and O are models of P. We easily observe that N and O are models of P. But L and M are not models of P since they do not satisfy the rule {a mathematical formula}c←e,f,¬b and {a mathematical formula}b←c respectively, and we can drop them as candidates. Then we positively answer the question whether N and O are models of its GL-reducts {a mathematical formula}PN and {a mathematical formula}PO respectively.Next we consider the minimality and apply the algorithm of Lemma 3.7 for each subset of the backdoor {a mathematical formula}X={b,c}. We have the GL-reduct {a mathematical formula}PN={d←a,e;e∨c←f;f←d,c;c←d;b←c;f}. For {a mathematical formula}X1=∅ we obtain {a mathematical formula}PX1⊆XN={d←a,e;e←f;f←d,c;←d;←c;f}. The set {a mathematical formula}L={e,f} is the unique minimal model of {a mathematical formula}PX1⊆XN. Since {a mathematical formula}L⊆N∖X, {a mathematical formula}L∪X1⊊N, and {a mathematical formula}L∪X1 is a model of {a mathematical formula}PN, the algorithm returns False. We conclude that N is not a minimal model of {a mathematical formula}PN and thus N is not an answer set of P.We obtain the GL-reduct {a mathematical formula}PO={d←a,e;e∨c←f;f←d,c;c←d;b←c;f}. For {a mathematical formula}X1=∅ we have {a mathematical formula}PX1⊆XO={d←a,e;e←f;f←d,e;←d;←c;f}. The set {a mathematical formula}L={e,f} is the unique minimal model of {a mathematical formula}PX1⊆XO. Since {a mathematical formula}L∪X1⊊O, the algorithm returns True. For {a mathematical formula}X2={b} we get {a mathematical formula}PX2⊆XO={d←a,e;e←f;f←d,e;←d;f} and the unique minimal model {a mathematical formula}L={e,f}. Since {a mathematical formula}L⊆O∖X, the algorithm returns True. For {a mathematical formula}X3={c} we obtain {a mathematical formula}PX3⊆XO={d←a,e;f←d;←;f} and no minimal model. Thus, the algorithm returns True. For {a mathematical formula}X4={b,c} we have {a mathematical formula}PX4⊆XO={d←a,e;f←d;f} and the unique minimal model {a mathematical formula}L={f}. Since {a mathematical formula}L∪X1⊊O, the algorithm returns True. Since only {a mathematical formula}{b,c,f}∈AS(P,X) is an answer set of P, we obtain {a mathematical formula}AS(P)={{b,c,f}}.
      </paragraph>
      <paragraph label="Definition 3.8">
       In view of Lemma 3.6, Lemma 3.7, the computation of {a mathematical formula}AS(P) is fixed-parameter tractable for parameter k if we know a strong {a mathematical formula}C-backdoor X of size at most k for P, and each program in {a mathematical formula}C is normal and its stable sets can be computed in polynomial time. This consideration leads to the following definition and result. A class {a mathematical formula}C of programs is enumerable if for each {a mathematical formula}P∈C we can compute {a mathematical formula}AS(P) in polynomial time. If {a mathematical formula}AS(P) can be computed in linear time, then the class {a mathematical formula}C is linear-time enumerable.
      </paragraph>
      <paragraph>
       Please note, that this is a stronger property than being enumerable with polynomial-time delay; the latter is usually used in the context of enumeration problems and also mentioned in Section 8.4 for a certain parameter.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}Cbe an enumerable class of normal programs. The problems in{a mathematical formula}AspFullare all fixed-parameter tractable when parameterized by the size of a strong{a mathematical formula}C-backdoor, assuming that the backdoor is given as input.Let X be the given backdoor, {a mathematical formula}k=|X| and n the input size of P. Since {a mathematical formula}Pτ∈C and {a mathematical formula}C is enumerable, we can compute {a mathematical formula}AS(Pτ) in polynomial time for each {a mathematical formula}τ∈2X, say in time {a mathematical formula}O(nc) for some constant c. Observe that therefore {a mathematical formula}|AS(Pτ)|≤O(nc) for each {a mathematical formula}τ∈2X. Thus, we obtain {a mathematical formula}AS(P,X) in time {a mathematical formula}O(2knc), and {a mathematical formula}|AS(P,X)|≤O(2knc). By Lemma 3.6, {a mathematical formula}AS(P)⊆AS(P,X). By means of Lemma 3.7 we can decide whether {a mathematical formula}M∈AS(P) in time {a mathematical formula}O(2kn) for each {a mathematical formula}M∈AS(P,X). Thus, we determine from {a mathematical formula}AS(P,X) the set of all answer sets of P in time {a mathematical formula}O(2k⋅nc⋅2k⋅n+2k⋅nc)=O(22knc+1). Once we know {a mathematical formula}AS(P), then we can also solve all problems in {a mathematical formula}AspFull within polynomial time.  □
      </paragraph>
      <paragraph>
       Theorem 3.9 identifies conditions under which a small backdoor indeed reduces the search space for the main ASP reasoning problems, that is, to be exponential only in the backdoor size and not in the size of the entire instance. Hence under these conditions a small backdoor can be considered as a “clever reasoning shortcut” through the search space.
      </paragraph>
      <paragraph label="Remark">
       If we know that each program in {a mathematical formula}C has at most one answer set, and P has a strong {a mathematical formula}C-backdoor of size k, then we can conclude that P has at most {a mathematical formula}2k answer sets. Thus, we obtain an upper bound on the number of answer sets of P by computing a small strong {a mathematical formula}C-backdoor of P.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Backdoor detection
      </section-title>
      <paragraph>
       Theorem 3.9 draws our attention to enumerable classes of normal programs. Given such a class {a mathematical formula}C, is the detection of {a mathematical formula}C-backdoors fixed-parameter tractable? If the answer is affirmative, we can drop in Theorem 3.9 the assumption that the backdoor is given as an input for this class.
      </paragraph>
      <paragraph>
       Each class {a mathematical formula}C of programs gives rise to the following two parameterized decision problems:
      </paragraph>
      <list>
       Strong{a mathematical formula}C-Backdoor Detection
       <list-item>
        A program P and an integer k.
       </list-item>
       <list-item>
        The integer k.
       </list-item>
       <list-item>
        Decide whether P has a strong {a mathematical formula}C-backdoor X of size at most k.
       </list-item>
      </list>
      <list>
       Deletion{a mathematical formula}C-Backdoor Detection
       <list-item>
        A program P and an integer k.
       </list-item>
       <list-item>
        The integer k.
       </list-item>
       <list-item>
        Decide whether P has a deletion {a mathematical formula}C-backdoor X of size at most k.
       </list-item>
      </list>
      <paragraph>
       By a standard construction, known as self-reduction or self-transformation [139], [34], [35], one can use a decision algorithm for Deletion{a mathematical formula}C-Backdoor Detection to actually find the backdoor. We only require the base class to be hereditary.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}Cbe a hereditary class of programs. IfDeletion{a mathematical formula}C-Backdoor Detectionis fixed-parameter tractable, then also finding a deletion{a mathematical formula}C-backdoor of a given program P of size at most k is fixed-parameter tractable (for parameter k).We proceed by induction on k. If {a mathematical formula}k=0 the statement is clearly true. Let {a mathematical formula}k&gt;0. Given {a mathematical formula}(P,k) we check for all {a mathematical formula}x∈at(P) whether {a mathematical formula}P−{x} has a deletion {a mathematical formula}C-backdoor of size at most {a mathematical formula}k−1. If the answer is NO for all x, then P has no deletion {a mathematical formula}C-backdoor of size k. If the answer is YES for x, then by induction hypothesis we can compute a deletion {a mathematical formula}C-backdoor X of size at most {a mathematical formula}k−1 of {a mathematical formula}P−x, and {a mathematical formula}X∪{x} is a deletion {a mathematical formula}C-backdoor of P.  □
      </paragraph>
      <paragraph label="Remark">
       One could consider also target classes where empty rules are detected (an analogy to “empty clause detection” [31], [32] in the SAT setting) which would yield smaller backdoors. However, backdoor detection is already W[1]-hard for almost all base classes, including Horn, in the SAT setting when empty clause detection is added [144]. These W[1]-hardness results carry over to the ASP setting if empty rule detection is added.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Target class Horn
     </section-title>
     <paragraph>
      In this section we consider the important case Horn as the target class for backdoors. As a consequence of Lemma 2.1, Horn is linear-time enumerable. The following lemma shows that strong and deletion Horn-backdoors coincide.
     </paragraph>
     <paragraph label="Proof">
      A set X is a strongHorn-backdoor of a program P if and only it is a deletionHorn-backdoor of P.Since Horn is hereditary, Lemma 3.4 establishes the if-direction. For the only–if direction, we assume for the sake of a contradiction that X is a strong Horn-backdoor of P but not a deletion Horn-backdoor of P. Hence there is a rule {a mathematical formula}r′∈P−X that is neither tautological nor Horn. Let {a mathematical formula}r∈P be a rule from which {a mathematical formula}r′ was obtained in forming {a mathematical formula}P−X. We define {a mathematical formula}τ∈2X by setting all atoms in {a mathematical formula}X∩(H(r)∪B−(r)) to 0, all atoms in {a mathematical formula}X∩B+(r) to 1, and all remaining atoms in {a mathematical formula}X∖at(r) arbitrarily to 0 or 1. Since r is not tautological, this definition of τ is sound. It follows that {a mathematical formula}r′∈Pτ, contradicting the assumption that X is a strong Horn-backdoor of P.  □
     </paragraph>
     <paragraph label="Definition 4.2">
      Let P be a program. The negation dependency graph{a mathematical formula}NP is the graph defined on the set of atoms of the given program P, where two distinct atoms {a mathematical formula}x,y are joined by an edge xy if there is a rule {a mathematical formula}r∈P with {a mathematical formula}x∈H(r) and {a mathematical formula}y∈H(r)∪B−(r).
     </paragraph>
     <paragraph label="Example 4.1">
      Fig. 2 visualizes the negation dependency graph {a mathematical formula}NP of the program P of Example 2.1.
     </paragraph>
     <paragraph>
      The following lemma states how we can use recent results on the vertex cover problem to find deletion backdoors for the target class Horn. A vertex cover of a graph {a mathematical formula}G=(V,E) is a set {a mathematical formula}S⊆V such that for every edge {a mathematical formula}uv∈E we have {a mathematical formula}{u,v}∩S≠∅.
     </paragraph>
     <paragraph label="Lemma 4.3">
      Let P be a program. A set{a mathematical formula}X⊆at(P)is a deletionHorn-backdoor of P if and only if X is a vertex cover of the negation dependency graph{a mathematical formula}NP.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}X⊆at(P) be a deletion Horn-backdoor of P. Consider an edge uv of {a mathematical formula}NP. By construction of {a mathematical formula}NP there is a corresponding rule {a mathematical formula}r∈P with (i) {a mathematical formula}u,v∈H(r) and {a mathematical formula}u≠v or (ii) {a mathematical formula}u∈H(r) and {a mathematical formula}v∈B−(r). Since X is a deletion Horn-backdoor, {a mathematical formula}|H(r)−X|≤1 and {a mathematical formula}B−(r)−X=∅. Thus, if case (i) applies, {a mathematical formula}{u,v}∩X≠∅. If case (ii) applies, again {a mathematical formula}{u,v}∩X≠∅. We conclude that X is a vertex cover of {a mathematical formula}NP.Conversely, assume that X is a vertex cover of {a mathematical formula}NP. Consider a rule {a mathematical formula}r∈P−X for proof by contradiction assume that r is not Horn (in particular r is not a constraint). If {a mathematical formula}|H(r)|≥2 then there are two variables {a mathematical formula}u,v∈H(r) and an edge uv of {a mathematical formula}NP such that {a mathematical formula}{u,v}∩X=∅, contradicting the assumption that X is a vertex cover. Similarly, if {a mathematical formula}B−(r)≠∅ then we take a variable {a mathematical formula}u∈B−(r) and a variable {a mathematical formula}v∈H(r); such v exists since r is not a constraint. Thus, {a mathematical formula}NP contains the edge uv with {a mathematical formula}{u,v}∩X=∅, contradicting the assumption that X is a vertex cover. Hence the claim holds.  □
     </paragraph>
     <paragraph label="Example 4.2">
      For instance, the negation dependency graph {a mathematical formula}NP of the program P of Example 2.1 consists of the triangle {a mathematical formula}{a,b,c} and a path {a mathematical formula}(c,e). Then {a mathematical formula}{b,c} is a vertex cover of {a mathematical formula}NP. We observe easily that there exists no vertex cover of size 1. Thus, {a mathematical formula}{b,c} is a smallest strong Horn-backdoor of P.
     </paragraph>
     <paragraph label="Remark">
      Note that the unparameterized version{sup:2} of StrongHorn-Backdoor Detection is NP-hard. Since the reduction presented in the proof of Lemma 4.3 can be used straightforward as a reduction of the unparameterized version of the vertex cover problem to StrongHorn-Backdoor Detection.
     </paragraph>
     <paragraph label="Proof">
      StrongHorn-Backdoor Detectionis fixed-parameter tractable. In fact, given a program with n atoms we can find a strongHorn-backdoor of size at most k in time{a mathematical formula}O(1.2738k+kn)or decide that no such backdoor exists.Let P be a given program. Let {a mathematical formula}NP be the negation dependency graph of P. According to Lemma 4.3, a set {a mathematical formula}X⊆at(P) is a vertex cover of {a mathematical formula}NP if and only if X is a deletion Horn-backdoor of P. Then a vertex cover of size at most k, if it exists, can be found in time {a mathematical formula}O(1.2738k+kn) by Chen et al. [22]. By Lemma 4.1 this vertex cover is also a strong Horn-backdoor of P.  □
     </paragraph>
     <paragraph label="Corollary 4.5">
      Now we can use Theorem 4.4 to strengthen the fixed-parameter tractability result of Theorem 3.9 by dropping the assumption that the backdoor is given. All the problems in{a mathematical formula}AspFullare fixed-parameter tractable when parameterized by the size of a smallest strongHorn-backdoor of the given program.
     </paragraph>
     <section label="4.1">
      <section-title>
       Horn-backdoors of benchmark instances
      </section-title>
      <paragraph>
       The underlying idea for fixed-parameter tractability is that problem instances for which the parameter is small can be solved efficiently. It is therefore natural to ask how the values of a parameter are distributed in various problem instances. Hence, we investigate the size of backdoors for various benchmark programs, focusing on the target class Horn. As expected, structured programs, originating from application domains, have smaller backdoors than random instances. Since the direct implementation of our backdoor-based algorithms seems impracticable.
      </paragraph>
      <paragraph>
       We have determined strong Horn-backdoors for various benchmark programs by means of encodings into answer set programming, integer linear programming (ILP), local search (LS), and propositional satisfiability (SAT). We use the connection stated in Lemma 4.3 and compile the problem of finding a minimum vertex cover (k-vertex cover) into the respective domain. The encodings are straightforward: Let P be a program (without constraints or tautological rules) and let {a mathematical formula}Np=(V,E) be its negation dependency graph. For the ASP encoding we proceed as follows: Among the atoms of our ASP program will be atoms {a mathematical formula}{euw:uw∈E} and atoms {a mathematical formula}C={cv:v∈V}. The truth values of the atoms in C represent a subset {a mathematical formula}S⊆at(P) such that {a mathematical formula}cv is true if and only if {a mathematical formula}v∈S (a vertex cover). We introduce for every edge {a mathematical formula}vw∈E a constraint {a mathematical formula}←evw,¬cv,¬cw and a choice rule {a mathematical formula}1{cu,cv}←eu,v Moreover, we add a statement to minimize the number of atoms in C that belong to an answer set (see [141], [73] for choice rules and minimize statements). For the ILP encoding we proceed as follows: We introduce for every vertex {a mathematical formula}v∈V a binary variable {a mathematical formula}bv, we add for every edge {a mathematical formula}vw∈E a constraint {a mathematical formula}bv+bw≥1, and minimize the sum {a mathematical formula}∑v∈Vbv. For LS we ran designated local search based vertex cover solvers [15], [17], [16] on the graph {a mathematical formula}Np. For the SAT encoding we used an encoding similar to the encoding presented in [53]. We introduce for every edge {a mathematical formula}uv∈E a binary clause and add a sequential unary counter [142] to express that at most k vertices belong to a vertex cover.
      </paragraph>
      <paragraph>
       The answer set program that solves backdoor detection was generated by means of ASP meta programming [70] and solved using Clasp [71], [72] version 3.0.5 with an unsatisfiable-core based optimization strategy (the command line parameter “–opt-strategy=5” yields the behavior) [1]. The integer linear program was generated using the open source mathematics framework Sage [44] with Python [150], solved using ILOG CPLEX 12 [89] and Gurobi [87].
      </paragraph>
      <paragraph>
       The results obtained with ILP methods using modern solvers like CPLEX and Gurobi come along with a certain inaccuracy (see e.g., [25], [24], [140]). Therefore, we ran Clasp on the structured instances using the encoding of k-vertex cover problem described above to obtain optimality.
      </paragraph>
      <paragraph>
       Table 1 illustrates our results on the size of small strong Horn-backdoors of the considered benchmark instances. We mainly used benchmark sets from the first three Answer Set Programming Competitions [18], [29], [63], because most of the instances contain only normal and/or disjunctive rules and no extended rules (cardinality/weight-constraints).{sup:3} We reference in the caption of Table 1 from where the instances have been taken and indicate in the table the number of instances of each benchmark set.
      </paragraph>
      <paragraph>
       The structured instances have, as expected, significantly smaller strong Horn-backdoors than the random instances. We would like to mention that the random programs from the ASP competitions contain a rather small number of atoms. So far we have no good evidence why in particular the sets KnightTour and Solitaire have rather large strong Horn-backdoors compared to other structured instances.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Target classes based on acyclicity
     </section-title>
     <paragraph>
      There are two causes for a program to have a large number of answer sets: (i) disjunctions in the heads of rules, and (ii) certain cyclic dependencies between rules. Disallowing both yields enumerable classes.
     </paragraph>
     <paragraph>
      In order to define acyclicity we associate with each disjunctive program P its dependency digraph{a mathematical formula}DP and its (undirected) dependency graph{a mathematical formula}UP. The dependency digraph was defined by Apt et al. [2] which slight differs from our notion as no additional edges on head atoms are introduced. The following definition is closely related to the notion suggested by Gottlob et al. [85].
     </paragraph>
     <paragraph label="Definition 5.1">
      Let P be a program. The dependency digraph is the digraph {a mathematical formula}DP which has as vertices the atoms of P and a directed edge {a mathematical formula}(x,y) between any two distinct atoms x, y for which there is a rule {a mathematical formula}r∈P with {a mathematical formula}x∈H(r) and {a mathematical formula}y∈B+(r)∪B−(r) or {a mathematical formula}x,y∈H(r). We call the edge {a mathematical formula}(x,y)negative if there is a rule {a mathematical formula}r∈P with {a mathematical formula}x∈H(r) and {a mathematical formula}y∈B−(r) or {a mathematical formula}x,y∈H(r).
     </paragraph>
     <paragraph label="Definition 5.2">
      Let P be a program. The (undirected) dependency graph is the graph {a mathematical formula}UP obtained from the dependency digraph {a mathematical formula}Dp
     </paragraph>
     <list>
      <list-item label="1.">
       by replacing each negative edge {a mathematical formula}e=(x,y) with two edges {a mathematical formula}xve, {a mathematical formula}vey where {a mathematical formula}ve is a new negative vertex, and
      </list-item>
      <list-item label="2.">
       by replacing each remaining directed edge {a mathematical formula}(u,v) with an edge uv.
      </list-item>
     </list>
     <paragraph label="Example 5.1">
      Fig. 3 visualizes the dependency digraph {a mathematical formula}DP and the dependency graph {a mathematical formula}Up of the program P of Example 2.1.
     </paragraph>
     <paragraph label="Definition 5.3">
      Let P be a program.
     </paragraph>
     <list>
      <list-item label="1.">
       A directed cycle of P is a directed cycle in the dependency digraph {a mathematical formula}DP.
      </list-item>
      <list-item label="2.">
       A directed cycle is bad if it contains a negative edge, otherwise it is good.
      </list-item>
      <list-item label="3.">
       A directed cycle is even if it contains an even number of negative edges, otherwise it is odd.
      </list-item>
      <list-item label="4.">
       A cycle of P is a cycle in the dependency graph {a mathematical formula}UP.
      </list-item>
      <list-item label="5.">
       A cycle is bad if it contains a negative vertex, otherwise it is good.
      </list-item>
      <list-item label="6.">
       A cycle is even if it contains an even number of negative vertices, otherwise it is odd.
      </list-item>
     </list>
     <paragraph label="Definition 5.4">
      The following classes of programs are defined in terms of the absence of certain kinds of cycles:
     </paragraph>
     <list>
      <list-item label="•">
       no-C contains all programs that have no cycles,
      </list-item>
      <list-item label="•">
       no-BC contains all programs that have no bad cycles,
      </list-item>
      <list-item label="•">
       no-DC contains all programs that have no directed cycles,
      </list-item>
      <list-item label="•">
       no-DC2 contains all programs that have no directed cycles of length at least 3 and no directed bad cycles,
      </list-item>
      <list-item label="•">
       no-DBC contains all programs that have no directed bad cycles,
      </list-item>
      <list-item label="•">
       no-EC contains all programs that have no even cycles,
      </list-item>
      <list-item label="•">
       no-BEC contains all programs that have no bad even cycles,
      </list-item>
      <list-item label="•">
       no-DEC contains all programs that have no directed even cycles, and
      </list-item>
      <list-item label="•">
       no-DBEC contains all programs that have no directed bad even cycles.
      </list-item>
     </list>
     <paragraph label="Example 5.2">
      Consider the dependency graphs of the program P of Example 2.1 as depicted in Fig. 3. For instance the sequence {a mathematical formula}(d,e,f) is a cycle, {a mathematical formula}(d,a) is a directed cycle (of length 2), {a mathematical formula}(d,e,f) and {a mathematical formula}(c,e,f) are directed cycles (of length 3), {a mathematical formula}(a,v(a,c),c,d) is a bad cycle, {a mathematical formula}(b,c) is a directed bad cycle. The sequence {a mathematical formula}(d,e,f) is an even cycle and a directed even cycle, {a mathematical formula}(c,e) is a directed bad even cycle.The set {a mathematical formula}X={c} is a strong {a mathematical formula}no-DBEC-backdoor since the truth assignment reducts {a mathematical formula}Pc=0=P0={d←a,e;a←d,¬b;e←f;f} and {a mathematical formula}P1={d←a,e;f←d;b;f} are in the target class no-DBEC. X is also a strong {a mathematical formula}no-BEC-backdoor, since {a mathematical formula}P0∈no-BEC and {a mathematical formula}P1∈no-BEC. The answer sets of {a mathematical formula}Pτ are {a mathematical formula}AS(Pc¯)={{e,f}} and {a mathematical formula}AS(Pc)={{b,f}}. Thus, {a mathematical formula}AS(P,X)={{e,f},{b,c,f}}, and since only {a mathematical formula}{b,c,f} is an answer set of P, we obtain {a mathematical formula}AS(P)={{b,c,f}}.
     </paragraph>
     <paragraph>
      The dependency and dependency digraphs contain bad even cycles through head atoms for non-singleton heads. This has the following consequence.
     </paragraph>
     <paragraph label="Observation 5.5">
      {a mathematical formula}C⊆Normalholds for all{a mathematical formula}C∈Acyc.
     </paragraph>
     <paragraph>
      If we have two programs {a mathematical formula}P⊆P′, then clearly the dependency (di)graph of P is a sub(di)graph of the dependency (di)graph of {a mathematical formula}P′. This has the following consequence.
     </paragraph>
     <paragraph label="Observation 5.6">
      All{a mathematical formula}C∈Acycare hereditary.
     </paragraph>
     <paragraph label="Proof">
      The following is a direct consequence of the definitions of the various classes in {a mathematical formula}Acyc. If{a mathematical formula}C,C′∈Acyc∪{Horn}such that the digraph inFig. 4contains a directed path from the class{a mathematical formula}Cto the class{a mathematical formula}C′, then{a mathematical formula}C⊆C′. If no inclusion between two classes is indicated, then the classes are in fact incomparable.We first consider the acyclicity-based target classes. By definition we have {a mathematical formula}no-DC⊊no-DBC and {a mathematical formula}no-C⊊no-BC⊊no-DBC; it is easy to see that the inclusions are proper. However, contrary to what one expects, {a mathematical formula}no-C⊈no-DC, which can be seen by considering the program {a mathematical formula}P1={x←y,y←x}. But the class no-DC2 which requires that a program has no directed cycles but may have directed good cycles of length 2 (as in {a mathematical formula}P1) generalizes both classes {a mathematical formula}no-C and {a mathematical formula}no-DC. By definition we have {a mathematical formula}no-DBC⊊no-DBEC, {a mathematical formula}no-DEC⊊no-DBEC, {a mathematical formula}no-EC⊊no-BEC, {a mathematical formula}no-C⊊no-EC, and {a mathematical formula}no-DC⊊no-DEC.Next we consider the target class Horn. Let {a mathematical formula}C∈{no-C,no-DC,no-DC2,no-EC}. We easily observe that {a mathematical formula}Horn⊈C by considering the program {a mathematical formula}P2={a←b;b←c;c←a} which is obviously Horn but does not belong to {a mathematical formula}C. Conversely, we observe that {a mathematical formula}C⊈Horn by considering the program {a mathematical formula}P3={a←¬b} which belongs to {a mathematical formula}C but is obviously not Horn. Thus, {a mathematical formula}C and Horn are incomparable. We observe that {a mathematical formula}Horn⊊no-BC by again considering the program {a mathematical formula}P3 which belongs to {a mathematical formula}no-BC, but is obviously not Horn, and by considering the fact that all rules r in a Horn program P satisfy {a mathematical formula}|H(r)|≤1 and {a mathematical formula}B−(r)=∅ which yields that the dependency graph {a mathematical formula}UP contains no bad vertices and hence gives us that {a mathematical formula}UP contains no bad cycles.  □
     </paragraph>
     <paragraph>
      The class {a mathematical formula}no-DBC coincides with the well-known class of stratified programs [2], [77], [19]. A normal program P is stratified if there is a mapping {a mathematical formula}str:at(P)→N, called stratification, such that for each rule r in P the following holds: (i) if {a mathematical formula}x∈H(r) and {a mathematical formula}y∈B+(r), then {a mathematical formula}str(x)≤str(y) and (ii) if {a mathematical formula}x∈H(r) and {a mathematical formula}y∈B−(r), then {a mathematical formula}str(x)&lt;str(y).
     </paragraph>
     <paragraph label="Lemma 5.8">
      (See Apt et al.[2].){a mathematical formula}Strat=no-DBC.
     </paragraph>
     <paragraph>
      The class {a mathematical formula}no-DBEC, the largest class in {a mathematical formula}Acyc, has already been studied by Zhao and Lin [156], [110], who showed that every program in {a mathematical formula}no-DBEC has at most one answer set, and this answer set can be found in polynomial time. For {a mathematical formula}no-DBC the unique answer set can even be found in linear time [121].
     </paragraph>
     <paragraph label="Proposition 5.9">
      In our context this has the following important consequence. All classes in{a mathematical formula}Acycare enumerable, the classes{a mathematical formula}C∈Acycwith{a mathematical formula}C⊆no-DBCare even linear-time enumerable.
     </paragraph>
     <paragraph>
      In view of Observation 5.5 and Proposition 5.9, all classes in {a mathematical formula}Acyc satisfy the requirement of Theorem 3.9 and are therefore in principle suitable target classes of a backdoor approach. Therefore we will study the parameterized complexity of Strong{a mathematical formula}C-Backdoor Detection and Deletion{a mathematical formula}C-Backdoor Detection for {a mathematical formula}C∈Acyc. As we shall see in the next two subsections, the results for Strong{a mathematical formula}C-Backdoor Detection are throughout negative, however for Deletion{a mathematical formula}C-Backdoor Detection there are several (fixed-parameter) tractable cases.
     </paragraph>
     <section label="5.1">
      <section-title>
       Strong backdoor detection
      </section-title>
      <paragraph label="Proof">
       Assume that the input program may contain tautological rules. Then, for every target class{a mathematical formula}C∈Acyc, the problemStrong{a mathematical formula}C-Backdoor Detectionis{a mathematical formula}W[2]-hard, and hence unlikely to be fixed-parameter tractable.We give an fpt-reduction from the {a mathematical formula}W[2]-complete problem Hitting Set (see Section 2.3) to Strong{a mathematical formula}C-BackdoorDetection. Let {a mathematical formula}(S,k) be an instance of this problem with {a mathematical formula}S={S1,…,Sm}. We construct a program P as follows. As atoms we take the elements of {a mathematical formula}U=⋃i=1mSi and new atoms {a mathematical formula}aij and {a mathematical formula}bij for {a mathematical formula}1≤i≤m, {a mathematical formula}1≤j≤k+1. For each {a mathematical formula}1≤i≤m and {a mathematical formula}1≤j≤k+1 we take two rules {a mathematical formula}rij, {a mathematical formula}sij where {a mathematical formula}H(rij)={aij}, {a mathematical formula}B−(rij)=Si∪{bij}, {a mathematical formula}B+(rij)=Si (which is a tautological rule); {a mathematical formula}H(sij)={bij}, {a mathematical formula}B−(sij)={aij}, {a mathematical formula}B+(sij)=∅.We show that {a mathematical formula}S has a hitting set of size at most k if and only if P has a strong {a mathematical formula}C-backdoor of size at most k.(⇒) Let H an hitting set of {a mathematical formula}S of size at most k. We choose an arbitrary truth assignment {a mathematical formula}τ∈2H and show that {a mathematical formula}Pτ∈C. Since H is a hitting set, each rule {a mathematical formula}rij will be removed when forming {a mathematical formula}Pτ. Hence the only rules left in {a mathematical formula}Pτ are the rules {a mathematical formula}sij, and so {a mathematical formula}Pτ∈no-DC∩no-C⊆C. Thus, H is a strong {a mathematical formula}C-backdoor of P.(⇐) Let X be a strong {a mathematical formula}C-backdoor of P of size at most k. We show that {a mathematical formula}H=X∩U is a hitting set of {a mathematical formula}S. Choose {a mathematical formula}1≤i≤m and consider {a mathematical formula}Si. We first consider the case {a mathematical formula}no-DC⊆C. For each {a mathematical formula}1≤j≤k+1 the program P contains a bad even directed cycle {a mathematical formula}(aij,bij). In order to destroy these cycles, X must contain an atom from {a mathematical formula}Si, since otherwise, X would need to contain for each {a mathematical formula}1≤j≤k+1 at least one of the atoms from each cycle, but then {a mathematical formula}|X|≥k+1, contradicting the assumption on the size of X. Hence H is a hitting set of {a mathematical formula}S. Now we consider the case {a mathematical formula}no-C⊆C. For each {a mathematical formula}1≤j≤k+1 the program P contains a bad even cycle {a mathematical formula}(aij,vaij,bij,bij,vbij,aij). In order to destroy these cycles, X must contain an atom from {a mathematical formula}Si, since otherwise, X would need to contain an atom from each cycle, again a contradiction. Hence H is a hitting set of {a mathematical formula}S. Consequently, the {a mathematical formula}W[2]-hardness of Strong{a mathematical formula}C-Backdoor Detection follows.  □
      </paragraph>
      <paragraph>
       For the target classes in {a mathematical formula}D-Acyc we can avoid the use of tautological rules in the reduction and so strengthen Proposition 5.10 as follows (it would be interesting to know if this is also possible for the remaining classes mentioned in Proposition 5.10).
      </paragraph>
      <paragraph label="Proof">
       For every target class{a mathematical formula}C∈D-Acyc, the problemStrong{a mathematical formula}C-Backdoor Detectionis{a mathematical formula}W[2]-hard, and hence unlikely to be fixed-parameter tractable.In order to show that Strong{a mathematical formula}C-Backdoor Detection is {a mathematical formula}W[2]-hard for {a mathematical formula}C∈D-Acyc when we forbid tautological rules in the input, we modify the reduction used in the proof of Proposition 5.10 from Hitting Set by redefining the rules {a mathematical formula}rij, {a mathematical formula}sij. We put {a mathematical formula}H(rij)={aij}, {a mathematical formula}B−(rij)=Si∪{bij}, {a mathematical formula}B+(rij)=∅; {a mathematical formula}H(sij)={bij}, {a mathematical formula}B−(sij)={aij}, {a mathematical formula}B+(sij)=U. By the very same argument as in the proof of Proposition 5.10 we can show that {a mathematical formula}S has a hitting set of size at most k if and only if P has a strong {a mathematical formula}C-backdoor of size at most k. We would like to mention that this reduction does not work for the undirected cases as it yields undirected cycles {a mathematical formula}(bij,u,bi′j′,u′) for any {a mathematical formula}u,u′∈U.  □
      </paragraph>
      <paragraph>
       For the class {a mathematical formula}no-DBEC we can again strengthen the result and show that detecting a strong {a mathematical formula}no-DBEC-backdoor is already {a mathematical formula}co-NP-hard for backdoor size 0; hence the problem is co-paraNP-hard (see Section 2.3).
      </paragraph>
      <paragraph label="Proof">
       The problemStrong{a mathematical formula}no-DBEC-Backdoor Detectionis{a mathematical formula}co-paraNP-hard, and hence not fixed-parameter tractable unless{a mathematical formula}P=co-NP.Recall that a path does not visit the same vertex twice. We reduce from the following problem, which is NP-complete [52], [104],
       <list>
        Directed Path via a NodeA digraph G and {a mathematical formula}s,m,t∈V distinct vertices.Decide whether G contains a directed path from s to t via m.Let
       </list>
       <paragraph>
        {a mathematical formula}G=(V,E) be a digraph and {a mathematical formula}s,m,t∈V distinct vertices. We define a program P as follows: For each edge {a mathematical formula}e=(v,w)∈E where {a mathematical formula}w≠m we take a rule {a mathematical formula}re: {a mathematical formula}w←v. For each edge {a mathematical formula}e=(v,m) we take a rule {a mathematical formula}re: {a mathematical formula}m←¬v. Finally we add the rule {a mathematical formula}rs,t: {a mathematical formula}s←¬t. We observe that the dependency digraph of P is exactly the digraph we obtain from G by adding the “reverse” edge {a mathematical formula}(t,s) (if not already present), and by marking {a mathematical formula}(t,s) and all incoming edges of m as negative.We show that G has a path from s to t via m if and only if {a mathematical formula}P∉no-DBEC. Assume G has such a path. Then this path must contain exactly one incoming edge of m, and hence it contains exactly one negative edge. The path, together with the negative edge {a mathematical formula}(t,s), forms a directed bad even cycle of P, hence {a mathematical formula}P∉no-DBEC. Conversely, assume {a mathematical formula}P∉no-DBEC. Hence the dependency digraph of P contains a directed bad even cycle, i.e., a cycle that contains at least two negative edges. As it can contain at most one incoming edge of m, the cycle contains exactly one incoming edge of m and the reverse edge {a mathematical formula}(t,s). Consequently, the cycle induces in G a directed path from s to t via m.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Fig. 5 illustrates the known complexity results of the problem Strong{a mathematical formula}C-Backdoor Detection. An arrow from {a mathematical formula}C to {a mathematical formula}C′ indicates that {a mathematical formula}C′ is a proper subset of {a mathematical formula}C and hence the size of a smallest strong {a mathematical formula}C′-backdoor is at most the size of a smallest strong {a mathematical formula}C-backdoor.
      </paragraph>
      <paragraph label="Remark">
       Note that the unparameterized version of Strong{a mathematical formula}C-Backdoor Detection for the acyclicity-based target classes {a mathematical formula}C is NP-hard since W[2]-hardness implies NP-hardness and co-paraNP-hardness also implies {a mathematical formula}co-NP-hardness. Moreover, the reduction presented in the proof of Proposition 5.10 and Theorem 5.11, Theorem 5.12 can be used straightforward as a reduction of the unparameterized version of Hitting Set, Directed Path via a Node respectively, to Strong{a mathematical formula}C-Backdoor Detection.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Deletion backdoor detection
      </section-title>
      <paragraph>
       The {a mathematical formula}W[2]-hardness results of Theorem 5.11, Theorem 5.12 suggest to relax the problem and to look for deletion backdoors instead of strong backdoors. In view of Lemma 3.4 and Observation 5.6, every deletion backdoor is also a strong backdoor for the considered acyclicity-based target classes, hence the backdoor approach of Theorem 3.9 works.
      </paragraph>
      <paragraph>
       Fortunately, the results of this section show that the relaxation indeed gives us fixed-parameter tractability of backdoor detection for most considered classes. Fig. 6 illustrates these results that we obtain by making use of very recent progress in fixed-parameter algorithmics on various variants of feedback vertex set and cycle transversal problems.
      </paragraph>
      <paragraph>
       Consider a graph {a mathematical formula}G=(V,E) and a set {a mathematical formula}W⊆V. A cycle in G is a W-cycle if it contains at least one vertex from W. A set {a mathematical formula}T⊆V is a W-cycle transversal of G if every W-cycle of G is also a T-cycle. A set {a mathematical formula}T⊆V is an even-length W-cycle transversal of G if every W-cycle of G of even length is also a T-cycle. A V-cycle transversal is also called a feedback vertex set.
      </paragraph>
      <paragraph>
       We give analog definitions for a digraph {a mathematical formula}G=(V,E) and {a mathematical formula}W⊆V. A directed cycle in G is a directed W-cycle if it contains at least on vertex from W. A set {a mathematical formula}T⊆V is a directed W-cycle transversal of G if every directed W-cycle of G is also a directed T-cycle. A set {a mathematical formula}T⊆V is an directed even-length W-cycle transversal of G if every directed W-cycle of G of even length is also a directed T-cycle. A directed V-cycle transversal is also called a directed feedback vertex set.
      </paragraph>
      <paragraph label="Proof">
       The problemDeletion{a mathematical formula}C-Backdoor Detectionis fixed-parameter tractable for all{a mathematical formula}C∈Acyc∖{no-DEC,no-DBEC}.Let P be a program and {a mathematical formula}k≥0. Let {a mathematical formula}Up be the dependency graph and {a mathematical formula}Dp the dependency digraph of P, respectively. Next we consider the various target classes {a mathematical formula}C mentioned in the statement of the theorem, one by one, and show how we can decide whether P has a deletion {a mathematical formula}C-backdoor of size at most k.First we consider “undirected” target classes. Downey and Fellows [34], [35] have shown that finding a feedback vertex set of size at most k is fixed-parameter tractable. We apply their algorithm to the dependency graph {a mathematical formula}Up. If the algorithm produces a feedback vertex set S of size at most k, then we can form a deletion {a mathematical formula}no-C-backdoor of P of size at most k by replacing each negative vertex in S by one of its two neighbors, which always gives rise to an atom of P. If {a mathematical formula}Up has no feedback vertex set of size at most k, then P has no deletion {a mathematical formula}no-C-backdoor of size at most k. Hence Deletion{a mathematical formula}no-C-Backdoor Detection is fixed-parameter tractable. Similarly, Deletion{a mathematical formula}no-BC-Backdoor Detection is fixed-parameter tractable by finding a W-feedback vertex set of {a mathematical formula}Up, taking as W the set of bad vertices of {a mathematical formula}Up. Cygan et al. [26] and Kawarabayashi and Kobayashi [102] showed that finding a W-feedback vertex set is fixed-parameter tractable, hence so is Deletion{a mathematical formula}no-BC-Backdoor Detection.In order to extend this approach to Deletion{a mathematical formula}no-EC-Backdoor Detection, we would like to use fixed-parameter tractability of finding an even W-cycle transversal, which was established by Misra et al. [116] for {a mathematical formula}W=V, and by Kakimura et al. [98] for general W. In order to do this, we use the following trick of Aracena, Gajardo, and Montalva [117] that turns cycles containing an even number of bad vertices into cycles of even length. From {a mathematical formula}Dp we obtain a graph {a mathematical formula}Up′ by replacing each negative edge {a mathematical formula}e=(x,y) with three edges {a mathematical formula}xue, {a mathematical formula}ueve, and {a mathematical formula}vey where {a mathematical formula}ue and {a mathematical formula}ve are new negative vertices, and by replacing each remaining directed edge {a mathematical formula}(u,v) with two edges {a mathematical formula}uwe and {a mathematical formula}wev where {a mathematical formula}we is a new (non-negative) vertex. We observe that {a mathematical formula}Up′ can be seen as being obtained from {a mathematical formula}Dp by subdividing edges. Hence there is a natural 1-to-1 correspondence between cycles in {a mathematical formula}Up and cycles in {a mathematical formula}Up′. Moreover, a cycle of {a mathematical formula}Up containing an even number of negative vertices corresponds to a cycle of {a mathematical formula}Up′ of even length, and a bad cycle of {a mathematical formula}Up corresponds to a bad cycle of {a mathematical formula}Up′. Thus, when we have an even cycle transversal S of {a mathematical formula}Up′, we obtain a deletion {a mathematical formula}no-EC-backdoor by replacing each negative vertex {a mathematical formula}v∈S by its non-negative neighbor. Hence Deletion{a mathematical formula}no-EC-Backdoor Detection is fixed-parameter tractable. For Deletion{a mathematical formula}no-BEC-Backdoor Detection we proceed similarly, using a even W-cycle transversal of {a mathematical formula}Up′, letting W be the set of negative vertices of {a mathematical formula}Up′.We now proceed with the remaining “directed” target classes {a mathematical formula}no-DC, {a mathematical formula}no-DC2, and {a mathematical formula}no-DBC.Let {a mathematical formula}G=(V,E) be a digraph. Evidently, the directed feedback vertex sets of {a mathematical formula}Dp are exactly the deletion {a mathematical formula}no-DC-backdoors of P. Hence, by using the fixed-parameter algorithm of Chen et al. [21] for finding directed feedback vertex sets we obtain fixed-parameter tractability of Deletion{a mathematical formula}no-DC-Backdoor Detection.To make this work for Deletion{a mathematical formula}no-DC2-Backdoor Detection we consider instead of {a mathematical formula}Dp the digraph {a mathematical formula}Dp′ obtained from {a mathematical formula}Dp by replacing each negative edge {a mathematical formula}e=(u,v) by two (non-negative) edges {a mathematical formula}(u,we), {a mathematical formula}(we,v), where {a mathematical formula}we is a new vertex. The directed cycles of {a mathematical formula}Dp and {a mathematical formula}Dp′ are in a 1-to-1 correspondence. However, directed cycles of length 2 in {a mathematical formula}Dp′ correspond to good cycles of length 2 in {a mathematical formula}Dp. Bonsma and Lokshtanov [12] showed that finding a directed feedback vertex set that only needs to cut cycles of length at least 3 is fixed-parameter tractable. Applying this algorithm to {a mathematical formula}Dp′ (and replacing each vertex {a mathematical formula}we in a solution with one of its neighbors) yields fixed-parameter tractability of Deletion{a mathematical formula}no-DC2-Backdoor Detection.The approach for Deletion{a mathematical formula}no-DC-Backdoor Detection extends to Deletion{a mathematical formula}no-DBC-Backdoor Detection by considering directed W-feedback vertex sets of the digraph {a mathematical formula}Dp′ obtained from {a mathematical formula}Dp using a simple construction already mentioned by Cygan et al. [26] where we replace each negative edge {a mathematical formula}e=(u,v) by two (non-negative) edges {a mathematical formula}(u,we), {a mathematical formula}(we,v) and {a mathematical formula}W={we:e is a negative edge}. The directed W-cycles of {a mathematical formula}Dp′ and the directed bad cycles of {a mathematical formula}Dp are obviously in a 1-to-1 correspondence. Thus, when we have a directed W-feedback vertex set S of {a mathematical formula}Dp′, we obtain a deletion {a mathematical formula}no-DBC-backdoor by replacing each vertex {a mathematical formula}v∈S∩W by its neighbor. The fixed-parameter tractability of finding a directed W-feedback vertex set was shown by Chitnis et al. [23].  □
      </paragraph>
      <paragraph label="Theorem 5.14">
       According to Observation 5.6, the classes mentioned in Theorem 5.13 are hereditary. Hence using Theorem 5.13 we can drop the assumption in Theorem 3.9 that the backdoor is given. We obtain directly the following results: For all{a mathematical formula}C∈Acyc∖{no-DEC,no-DBEC}all problems in{a mathematical formula}AspFullare fixed-parameter tractable when parameterized by the size of a smallest deletion{a mathematical formula}C-backdoor.
      </paragraph>
      <paragraph>
       Let us now turn to the two classes {a mathematical formula}no-DEC, {a mathematical formula}no-DBEC excluded in Theorem 5.13. We cannot establish that Deletion{a mathematical formula}no-DEC-Backdoor Detection is fixed-parameter tractable, as the underlying even cycle transversal problem seems to be currently out of reach to be solved. However, in Theorem 5.15 below, we can at least show that for every constant k, we can decide in polynomial time whether a strong {a mathematical formula}no-DEC-backdoor of size at most k exists; thus, the problem is in XP. For Deletion{a mathematical formula}no-DBEC-Backdoor Detection the situation is different: here we can rule out fixed-parameter tractability under the complexity theoretical assumption {a mathematical formula}P≠co-NP (Theorem 5.16).
      </paragraph>
      <paragraph label="Proof">
       The problemDeletion{a mathematical formula}no-DEC-Backdoor Detectionis in XP.Let P be a program, n the input size of P, and k be a constant. We are interested in a deletion {a mathematical formula}no-DEC-backdoor of P of size at most k. We loop over all possible sets {a mathematical formula}X⊆at(P) of size at most k. Since k is a constant, there is a polynomial number {a mathematical formula}O(nk) of such sets X. To decide whether X is a deletion {a mathematical formula}no-DEC-backdoor of P, we need to check whether {a mathematical formula}P−X∈no-DEC. For the membership check {a mathematical formula}P−X∈no-DEC we have to decide whether {a mathematical formula}DP−X contains a bad even cycle. We use a directed variant of the trick in the proof of Theorem 5.13 (in fact, the directed version is slightly simpler). Let {a mathematical formula}DP−X be the dependency digraph of {a mathematical formula}P−X. From {a mathematical formula}DP−X we obtain a new digraph {a mathematical formula}DP−X′ by subdividing every non-negative edge, i.e., we replace each non-negative edge {a mathematical formula}e=(x,y) by two (non-negative) edges {a mathematical formula}(x,ue), {a mathematical formula}(ue,y) where {a mathematical formula}ue is a new vertex. Obviously, directed even cycles in {a mathematical formula}DP−X are in 1-to-1 correspondence with directed cycles of even length in {a mathematical formula}DP−X′. Whether a digraph contains a directed cycle of even length can be checked in polynomial time by means of the following results: Vazirani and Yannakakis [151] have shown that finding a cycle of even length in a digraph is equivalent to finding a so-called Pfaffian orientation of a graph. Robertson, Seymour, and Thomas [133] have shown that a Pfaffian orientation can be found in polynomial time, hence the test works in polynomial time.  □
      </paragraph>
      <paragraph label="Proof">
       The problemDeletion{a mathematical formula}no-DBEC-Backdoor Detectionis{a mathematical formula}co-paraNP-hard, and hence not fixed-parameter tractable unless{a mathematical formula}P=co-NPThe theorem follows from the reduction in the proof of Theorem 5.12.  □
      </paragraph>
      <paragraph label="Remark">
       We note that the unparameterized version of Deletion{a mathematical formula}C-Backdoor Detection for the acyclicity-based target classes {a mathematical formula}C is NP-hard and {a mathematical formula}co-NP-hard respectively, since the reduction presented in the proof of Theorem 5.13, Theorem 5.15 can be used straightforward as a reduction of the unparameterized version of the variants of the minimal feedback vertex set problem, Directed Path via a Node respectively, to Deletion{a mathematical formula}C-Backdoor Detection.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Backdoors of benchmark instances
      </section-title>
      <paragraph>
       For the acyclicity based target classes {a mathematical formula}C∈Acyc we have computed small deletion {a mathematical formula}C-backdoors only for very few selected instances with moderate size since the currently available algorithms can only deal with rather small instances within a reasonable computation time. The size of small deletion {a mathematical formula}no-C-backdoors of selected instances of Solitaire was about half of the size of small strong Horn-backdoors.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Kernelization
     </section-title>
     <paragraph>
      If we want to solve a hard problem, then in many settings, it is beneficial to first apply a polynomial preprocessing to a given problem instance. In particular, polynomial-time preprocessing techniques have been developed in ASP solving (see e.g., [45], [65], [68]). However, polynomial-time preprocessing for NP-hard problems has mainly been subject of empirical studies where provable performance guarantees are missing, mainly due to the fact, that if we can show that we can reduce in polynomial-time a problem instance by just one bit, then by iterating this reduction we can solve the instances in polynomial time. In contrast, the framework of parameterized complexity offers with the notion of kernelization a useful mathematical framework that admits the rigorous theoretical analysis of polynomial-time preprocessing for NP-hard problems. A kernelization is a polynomial-time reduction that replaces the input by a smaller input, called a “kernel”, whose size is bounded by some computable function of the parameter only. A well known result of parameterized complexity theory is that a decidable problem is fixed-parameter tractable if and only if it admits a kernelization [36]. The result leads us to the question of whether a problem also has a kernelization that reduces instances to a size which is polynomially bounded by the parameter, so-called polynomial kernels. Indeed, many NP-hard optimization problems admit polynomial kernels when parameterized by the size of the solution [134]. In the following we consider kernelizations for backdoor detection and backdoor evaluation in the context of ASP. We establish that for some target classes, backdoor detection admits a polynomial kernel. We further provide strong theoretical evidence that for all target classes considered, backdoor evaluation does not admit a polynomial kernel.
     </paragraph>
     <paragraph>
      We will later use the following problem:
     </paragraph>
     <list>
      Vertex Cover
      <list-item>
       A graph {a mathematical formula}G=(V,E) and an integer k.
      </list-item>
      <list-item>
       The integer k.
      </list-item>
      <list-item>
       Decide whether there is a vertex cover {a mathematical formula}S⊆V (see Section 4) of size at most k.
      </list-item>
     </list>
     <paragraph>
      Next we give a more formal definition of kernelization. Let {a mathematical formula}L,L′⊆Σ⁎×N be parameterized problems. A bi-kernelization is a polynomial-time many-to-one reduction from the problem L to problem {a mathematical formula}L′ where the size of the output is bounded by a computable function of the parameter. That is, a bi-kernelization is an algorithm that, given an instance {a mathematical formula}(I,k)∈Σ⁎×N outputs for a constant c in time {a mathematical formula}O((‖I‖+k)c) a pair {a mathematical formula}(I′,k′)∈Σ⁎×N, such that (i) {a mathematical formula}(I,k)∈L if and only if {a mathematical formula}(I′,k′)∈L′ and (ii) {a mathematical formula}‖I′‖+k′≤g(k) where g is an arbitrary computable function, called the size of the kernel. If {a mathematical formula}L′=L then the reduction is called a kernelization, the reduced instance a kernel. If g is a polynomial then we say that L admits a polynomial bi-kernel, or polynomial kernel if in addition {a mathematical formula}L=L′. For instance, the problem Vertex Cover has a kernel of at most 2k vertices and thus admits a polynomial kernel [22]. L is called compressible if it admits a polynomial bi-kernel.
     </paragraph>
     <paragraph>
      The following proposition states the connection between fixed-parameter tractable problems and kernels, as observed by Downey, Fellows, and Stege [36]:
     </paragraph>
     <paragraph label="Proposition 6.1">
      (See Downey et al.[36], Flum and Grohe[50].) A parameterized problem is fixed-parameter tractable if and only if it is decidable and has a kernelization.
     </paragraph>
     <paragraph>
      Thus, our fixed-parameter tractability results of Theorem 3.9, Theorem 4.4, Theorem 5.13 immediately provide that the mentioned problems admit a kernelization. In the following we investigate whether these problems admit polynomial kernels.
     </paragraph>
     <section label="6.1">
      <section-title>
       Backdoor detection
      </section-title>
      <paragraph>
       The first result of this section is quite positive.
      </paragraph>
      <paragraph label="Proof">
       For{a mathematical formula}C∈{Horn,no-C}the problemDeletion{a mathematical formula}C-Backdoor Detectionadmits a polynomial kernel. For{a mathematical formula}C=Hornthe kernel has a linear number of atoms, for{a mathematical formula}C=no-Cthe kernel has a quadratic number of atoms.First consider the case {a mathematical formula}C=Horn. Let {a mathematical formula}(P,k) be an instance of DeletionHorn-Backdoor Detection. We obtain in polynomial time the negation dependency graph {a mathematical formula}Np of P (see Definition 4.2) and consider {a mathematical formula}(Np,k) as an instance of Vertex Cover. We use the kernelization algorithm of Chen et al. [22] for Vertex Cover and reduce in polynomial time {a mathematical formula}(Np,k) to a Vertex Cover instance {a mathematical formula}(G,k′) where {a mathematical formula}G=(V,E) with at most 2k many vertices. It remains to translate G into a program {a mathematical formula}P′ where {a mathematical formula}Np′=G by taking for every edge {a mathematical formula}xy∈E a rule {a mathematical formula}x←¬y. Now {a mathematical formula}(P′,k′) is a polynomial kernel with a linear number of atoms.Second consider the case {a mathematical formula}C=no-C. Let {a mathematical formula}(P,k) be an instance of Deletion{a mathematical formula}no-C-Backdoor Detection. We obtain in polynomial time the dependency graph {a mathematical formula}Up of P and consider {a mathematical formula}(Up,k) as an instance of Feedback Vertex Set (see Section 5.2). We use the kernelization algorithm of Thomassé [146] for Feedback Vertex Set and reduce in polynomial time {a mathematical formula}(Up,k) to a Feedback Vertex Set instance {a mathematical formula}(G′,k′) with at most {a mathematical formula}4k2 vertices. As above we translate {a mathematical formula}G=(V,E) into a program {a mathematical formula}P′ where {a mathematical formula}Up′=G by taking for every edge {a mathematical formula}xy∈E a rule {a mathematical formula}x←¬y. Now {a mathematical formula}(P′,k′) is a polynomial kernel with a quadratic number of atoms.  □
      </paragraph>
      <paragraph>
       Similar to the construction in the proof of Theorem 5.13 we can reduce for the remaining classes the backdoor detection problem to variants of feedback vertex set. However, for the other variants of feedback vertex set no polynomial kernels are known.
      </paragraph>
      <paragraph>
       We would like to point out that the kernels obtained in the proof of Theorem 6.2 are equivalent to the input program with respect to the existence of a backdoor, hence the kernels can be used to find a backdoor. However the obtained kernels are not equivalent with respect to the decision of the problems in {a mathematical formula}AspReason, in consequence the kernel cannot be used for backdoor evaluation. In the next subsection we consider kernels with respect to problems in {a mathematical formula}AspReason.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Backdoor evaluation
      </section-title>
      <paragraph>
       Next we consider the problems in {a mathematical formula}AspReason. We will see that neither of them admits a polynomial kernel when parameterized by the size of a strong {a mathematical formula}C-backdoor for the considered target classes, subject to standard complexity theoretical assumptions.
      </paragraph>
      <paragraph>
       Our superpolynomial lower bounds for kernel size are based on a result by Fortnow and Santhanam [51] regarding satisfiability parameterized by the number of variables.
      </paragraph>
      <list>
       Sat[Vars]
       <list-item>
        A CNF formula F.
       </list-item>
       <list-item>
        The number k of variables of F.
       </list-item>
       <list-item>
        Decide whether F is satisfiable.
       </list-item>
      </list>
      <paragraph label="Proposition 6.3">
       (See Fortnow and Santhanam[51].) IfSat[Vars]is compressible, then{a mathematical formula}NP⊆co-NP/poly.
      </paragraph>
      <paragraph>
       The complexity class NP/poly consists of all problems that can be solved non-deterministically in non-uniform polynomial time, i.e., by a non-deterministic polynomial-time Turing machine with an additional polynomial-bounded input that depends only on the length of the input, but not on the input itself (advice function), for details see e.g., [100]. It is well-known from Yap's Theorem [154] that if {a mathematical formula}NP⊆co-NP/poly then the Polynomial Hierarchy collapses to its third level ({a mathematical formula}Σ3P=Π3p) which is considered unlikely by standard complexity theoretical assumptions.
      </paragraph>
      <paragraph>
       The following theorem extends a result for normal programs [58]. We need a different line of argument, as the technique used in [58] only applies to problems in NP or {a mathematical formula}co-NP.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}C∈Acyc∪{Horn}. Then no problem in{a mathematical formula}AspReasonadmits a polynomial kernel when parameterized by the size of a smallest strong{a mathematical formula}C-backdoor or deletion{a mathematical formula}C-backdoor, unless{a mathematical formula}NP⊆co-NP/poly.We show that the existence of a polynomial kernel for any of the above problems implies that Sat[Vars] is compressible, and hence by Proposition 6.3 the collapse would follow.First consider the problem Consistency. From a CNF formula F with k variables we use a reduction of Niemelä [122] and construct a program {a mathematical formula}P1 as follows: Among the atoms of our program {a mathematical formula}P1 will be two atoms {a mathematical formula}ax and {a mathematical formula}ax¯ for each variable {a mathematical formula}x∈var(F), an atom {a mathematical formula}bC for each clause {a mathematical formula}C∈F. We add the rules {a mathematical formula}ax¯←¬ax and {a mathematical formula}ax←¬ax¯ for each variable {a mathematical formula}x∈var(F). For each clause {a mathematical formula}C∈F we add for each {a mathematical formula}x∈C the rule {a mathematical formula}bC←ax and for each {a mathematical formula}¬x∈C the rule {a mathematical formula}bC←ax¯. Additionally, for each clause {a mathematical formula}C∈F we add the rule {a mathematical formula}←¬bC. Now it is easy to see that the formula F is satisfiable if and only if the program {a mathematical formula}P1 has an answer set. We observe that {a mathematical formula}X={ax:x∈var(F)} ({a mathematical formula}X={ax,ax¯:x∈var(F)}) is a smallest deletion (and smallest strong) {a mathematical formula}C-backdoor of {a mathematical formula}P1 for each {a mathematical formula}C∈Acyc ({a mathematical formula}C=Horn). Hence {a mathematical formula}(P1,k), {a mathematical formula}(P1,2k) respectively, is an instance of Consistency, parameterized by the size of a smallest strong {a mathematical formula}C-backdoor or deletion {a mathematical formula}C-backdoor, and if this problem would admit a polynomial kernel, this would imply that Sat[Vars] is compressible.For the problem Brave Reasoning we modify the reduction from above. We create a program {a mathematical formula}P2 that consists of all atoms and rules from {a mathematical formula}P1. Additionally, the program {a mathematical formula}P2 contains an atom t and a rule r with {a mathematical formula}H(r)={t}, {a mathematical formula}B+(r)=∅, and {a mathematical formula}B−(r)=∅. We observe that the formula F is satisfiable if and only if the atom t is contained in some answer set of {a mathematical formula}P2. Since X is still a backdoor of size k (2k), and a polynomial kernel for Brave Reasoning, again it would yield that Sat[Vars] is compressible.Let UnSat[Vars] denote the problem defined exactly like Sat[Vars], just with yes and no answers swapped. A bi-kernelization for UnSat[Vars] is also a bi-kernelization for Sat[Vars] (with yes and no answers swapped). Hence Sat[Vars] is compressible if and only if UnSat[Vars] is compressible. An argument dual to the previous one for Brave Reasoning shows that a polynomial kernel for Skeptical Reasoning, parameterized by backdoor size, would yield that UnSat[Vars] is compressible, which, as argued above, would yield that Sat[Vars] is compressible.  □
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Lifting parameters
     </section-title>
     <paragraph>
      In this section we will introduce a general method to lift ASP-parameters that are defined for normal programs to disjunctive programs. Thereby we extend several algorithms that have been suggested for normal programs to disjunctive programs. The lifting method also gives us an alternative approach to obtain some results of Section 5.
     </paragraph>
     <paragraph>
      The following definition allows us to speak about parameters for programs in a more abstract way.
     </paragraph>
     <paragraph label="Definition 7.1">
      An ASP-parameter is a function p that assigns to every program P some non-negative integer {a mathematical formula}p(P) such that {a mathematical formula}p(P′)≤p(P) holds whenever {a mathematical formula}P′ is obtained from P by deleting rules or deleting atoms from rules. If p is only defined for normal programs, we call it a normal ASP-parameter. For an ASP parameter p we write {a mathematical formula}p↓ to denote the ASP-parameter obtained by restricting p to normal programs.
     </paragraph>
     <paragraph>
      We impose the condition {a mathematical formula}p(P′)≤p(P) for technical reasons. This is not a limitation, as most reasonable parameters and all parameters considered in this paper satisfy this condition.
     </paragraph>
     <paragraph label="Definition 7.2">
      There are natural ASP-parameters associated with backdoors: For a class {a mathematical formula}C of programs and a program P let {a mathematical formula}sbC(P) denote the size of a smallest strong {a mathematical formula}C-backdoor and {a mathematical formula}dbC(P) denote the size of a smallest deletion {a mathematical formula}C-backdoor of P.
     </paragraph>
     <paragraph>
      We will “lift” normal ASP-parameters to general disjunctive programs as follows.
     </paragraph>
     <paragraph label="Definition 7.3">
      For a normal ASP-parameter p we define the ASP-parameter {a mathematical formula}p↑ by setting, for each disjunctive program P, {a mathematical formula}p↑(P) as the minimum of {a mathematical formula}|X|+p(P−X) over all inclusion-minimal deletion Normal-backdoors X of P.
     </paragraph>
     <paragraph>
      The next lemma shows that this definition is compatible with deletion {a mathematical formula}C-backdoors if {a mathematical formula}C⊆Normal. In other words, if {a mathematical formula}C is a class of normal programs, then we can divide the task of finding a deletion {a mathematical formula}C-backdoor for a program P into two parts: (i) to find a deletion Normal-backdoor X, and (ii) to find a deletion {a mathematical formula}C-backdoor of {a mathematical formula}P−X.
     </paragraph>
     <paragraph label="Proof">
      Self-liftingLet{a mathematical formula}Cbe a class of normal programs. Then{a mathematical formula}dbC(P)=(dbC↓)↑(P)for every program P.Let {a mathematical formula}C be a class of normal programs, and P a program. Let X be a deletion {a mathematical formula}C-backdoor of P of size {a mathematical formula}dbC(P). Thus, {a mathematical formula}P−X∈C⊆Normal. Hence X is a deletion Normal-backdoor of P. We select an inclusion-minimal subset {a mathematical formula}X′ of X that is still a deletion Normal-backdoor of P (say, by starting with {a mathematical formula}X′=X, and then looping over all the elements x of X, and if {a mathematical formula}X′∖{x} is still a deletion {a mathematical formula}C-backdoor, then setting {a mathematical formula}X′:=X′∖{x}). What we end up with is an inclusion-minimal deletion Normal-backdoor {a mathematical formula}X′ of P of size at most {a mathematical formula}dbC(P). Let {a mathematical formula}P′=P−X′ and {a mathematical formula}X″=X∖X′. {a mathematical formula}P′ is a normal program. Since {a mathematical formula}P′−X″=P−X, it follows that {a mathematical formula}P′−X″∈C. Hence {a mathematical formula}X″ is a deletion {a mathematical formula}C-backdoor of P. Thus, by the definition of {a mathematical formula}dbC↑, we have that {a mathematical formula}dbC↑(P)≤|X′|+|X″|=dbC(P).Conversely, let {a mathematical formula}dbC↑(P)=k. Hence there is a deletion Normal-backdoor {a mathematical formula}X′ of P such that {a mathematical formula}|X′|+dbC(P−X′)=k. Let {a mathematical formula}P′=P−X′. Since {a mathematical formula}dbC(P′)≤k−|X′|, it follows that {a mathematical formula}P′ has a deletion {a mathematical formula}C-backdoor {a mathematical formula}X″ of size {a mathematical formula}k−|X′|. We put {a mathematical formula}X=X′∪X″ and observe that {a mathematical formula}P−X=P′−X″∈C. Hence X is a deletion {a mathematical formula}C-backdoor of P. Since {a mathematical formula}dbC(P)≤|X|≤|X′|+|X″|≤dbC↑(P)≤k, the lemma follows.  □
     </paragraph>
     <paragraph label="Example 7.1">
      Consider the program P of Example 2.1 and let {a mathematical formula}#neg(P) denote the number of atoms that appear in negative rule bodies of a normal program (we will discuss this parameter in more detail in Section 8.2).We determine {a mathematical formula}#neg↑(P)=2 by the following observations: The set {a mathematical formula}X1={c} is a deletion Normal-backdoor of P since {a mathematical formula}P−X1={d←a,e;a←d,¬b;e←f;f←d;←f,e,¬b;←d;b;f} belongs to the class Normal. The set {a mathematical formula}X2={e} is a deletion Normal-backdoor of P since {a mathematical formula}P−X2={d←a;a←d,¬b,¬c;c←f;f←d,c;c←f,¬b;c←d;b←c;f} belongs to the class Normal. Observe that {a mathematical formula}X1 and {a mathematical formula}X2 are the only inclusion-minimal deletion Normal-backdoors of the program P. We obtain {a mathematical formula}#neg↑(P,X1)=2 since {a mathematical formula}#neg(P−X1)=1. We have {a mathematical formula}#neg↑(P,X2)=3 since {a mathematical formula}#neg(P−X2)=2. Thus, {a mathematical formula}#neg↑(P)=2.
     </paragraph>
     <paragraph>
      For every ASP-parameter p we consider the following problem.
     </paragraph>
     <list>
      {a mathematical formula}Bound[p]
      <list-item>
       A program P and an integer k.
      </list-item>
      <list-item>
       The integer k.
      </list-item>
      <list-item>
       Decide whether {a mathematical formula}p(P)≤k holds.
      </list-item>
     </list>
     <paragraph>
      For a problem {a mathematical formula}L∈AspFull and an ASP-parameter p we write {a mathematical formula}L[p] to denote the problem L parameterized by p. That is, the instance of the problem is augmented with an integer k, the parameter, and for the input program P it holds that {a mathematical formula}p(P)≤k. Moreover, we write {a mathematical formula}L[p]N to denote the restriction of {a mathematical formula}L[p] where instances are restricted to normal programs P. Similarly, {a mathematical formula}Bound[p]N is the restriction of {a mathematical formula}Bound[p] to normal programs. For all the problems {a mathematical formula}L[p]N, p only needs to be a normal ASP-parameter.
     </paragraph>
     <paragraph>
      Next we state the main result of this section.
     </paragraph>
     <paragraph label="Theorem 7.5">
      LiftingLet p be a normal ASP-parameter such that{a mathematical formula}Bound[p]Nand{a mathematical formula}Enum[p]Nare fixed-parameter tractable. Then for all{a mathematical formula}L∈AspFullthe problem{a mathematical formula}L[p↑]is fixed-parameter tractable.
     </paragraph>
     <paragraph>
      We need some definitions and auxiliary results to establish the theorem.
     </paragraph>
     <paragraph label="Definition 7.6">
      Let P be a disjunctive program. The head dependency graph{a mathematical formula}HP of the program P is the graph which has as vertices the atoms of P and an edge between any two distinct atoms if they appear together in the head of a rule of P.
     </paragraph>
     <paragraph label="Proof">
      Let P be a disjunctive program. A set{a mathematical formula}X⊆at(P)is a deletionNormal-backdoor of P if and only if X is a vertex cover of the head dependency graph{a mathematical formula}HP.Let X be a deletion Normal-backdoor of P. Consider an edge uv of {a mathematical formula}HP, then there is a rule {a mathematical formula}r∈P with {a mathematical formula}u,v∈H(r) and {a mathematical formula}u≠v. Since X is a deletion Normal-backdoor of P, we have {a mathematical formula}{u,v}∩X≠∅. We conclude that X is a vertex cover of {a mathematical formula}HP.Conversely, assume that X is a vertex cover of {a mathematical formula}HP. We show that X is a deletion Normal-backdoor of P. Assume to the contrary, that {a mathematical formula}P−X contains a rule r whose head contains two variables {a mathematical formula}u,v. Consequently, there is an edge uv in {a mathematical formula}HP such that {a mathematical formula}{u,v}∩X=∅, contradicting the assumption that X is a vertex cover.  □
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula}G=(V,E)be a graph,{a mathematical formula}n=|E|, and let k be a non-negative integer. G has at most{a mathematical formula}2kinclusion-minimal vertex covers of size at most k, and we can list all such vertex covers in time{a mathematical formula}O(2kn).We build a binary search tree T of depth at most k where each node t of T is labeled with a set {a mathematical formula}St. We build the tree recursively, starting with the root r with label {a mathematical formula}Sr=∅. If {a mathematical formula}St is a vertex cover of G we stop the current branch, and t becomes a “success” leaf of T. If t is of distance k from the root and {a mathematical formula}St is not a vertex cover of G, then we also stop the current branch, and t becomes a “failure” leaf of T. It remains to consider the case where {a mathematical formula}St is not a vertex cover and t is of distance smaller than k from the root. We pick an edge {a mathematical formula}uv∈E such that {a mathematical formula}u,v∉St (such edge exists, otherwise {a mathematical formula}St would be a vertex cover) and add two children {a mathematical formula}t′,t″ to t with labels {a mathematical formula}St′=St∪{u} and {a mathematical formula}St″=St∪{v}. It is easy to see that for every inclusion-minimal vertex cover S of G of size at most k there is a success leaf t with {a mathematical formula}St=S. Since T has {a mathematical formula}O(2k) nodes, the lemma follows.  □
     </paragraph>
     <paragraph>
      From Lemma 7.7, Lemma 7.8 we immediately obtain the next result.
     </paragraph>
     <paragraph label="Proof of Theorem 7.5">
      Every disjunctive program of input size n has at most{a mathematical formula}2kinclusion-minimal deletionNormal-backdoors of size at most k, and all these backdoors can be enumerated in time{a mathematical formula}O(2kn).Let p be a normal ASP-parameter such that {a mathematical formula}Enum[p]N and {a mathematical formula}Bound[p]N are fixed-parameter tractable. Let P be a given disjunctive program of input size n and k an integer such that {a mathematical formula}p↑(P)≤k. In the following, when we say some task is solvable in “fpt-time”, we mean that it can be solved in time {a mathematical formula}O(f(k)nc) for some computable function f and a constant c.By Proposition 7.9 we can enumerate all inclusion-minimal deletion Normal-backdoors of size at most k in time {a mathematical formula}O(2kn). We can check whether {a mathematical formula}p(P−X)≤k−|X| for each such backdoor X in fpt-time since {a mathematical formula}Bound[p]N is fixed-parameter tractable by assumption. Since {a mathematical formula}p↑(P)≤k, there is at least one such set X where the check succeeds.We pick such set X and compute {a mathematical formula}AS(P,X) in fpt-time. That this is possible can be seen as follows. Obviously, for each truth assignment {a mathematical formula}τ∈2X the program {a mathematical formula}Pτ is normal since {a mathematical formula}P−X is normal, and clearly {a mathematical formula}p(Pτ)≤p(P−X)≤k by Definition 7.1. We can compute {a mathematical formula}AS(Pτ) in fpt-time since {a mathematical formula}Enum[p]N is fixed-parameter tractable by assumption. Since there are at most {a mathematical formula}2k such programs {a mathematical formula}Pτ, we can indeed compute the set {a mathematical formula}AS(P,X) in fpt-time.By Lemma 3.6 we have {a mathematical formula}AS(P)⊆AS(P,X), hence it remains to check for each {a mathematical formula}M∈AS(P,X) whether it gives rise to an answer set of P. Since X is a deletion Normal-backdoor of P, and since one easily observes that Normal is hereditary, it follows by Lemma 3.4 that X is a strong Normal-backdoor of P. Hence Lemma 3.7 applies, and we can decide whether {a mathematical formula}M∈AS(P) in time {a mathematical formula}O(2kn). Hence we can determine the set {a mathematical formula}AS(P) in fpt-time. Once we know the set {a mathematical formula}AS(P), we obtain for every problem {a mathematical formula}L∈AspFull that {a mathematical formula}L[p↑] is fixed-parameter tractable.  □
     </paragraph>
     <paragraph label="Example 7.2">
      Consider the program P of Example 2.1 with the deletion Normal-backdoor {a mathematical formula}X1={c} from Example 7.1. We want to enumerate all answer sets of P. We obtain with Ben-Eliyahu's algorithm [4] the sets {a mathematical formula}AS(Pc¯)={{e,f}} and {a mathematical formula}AS(Pc)={{b,f}}, and so we get the set {a mathematical formula}AS(P,X)={{e,f},{b,c,f}} of answer set candidates. By means of the algorithm that solves the problem Strong{a mathematical formula}C-Backdoor Asp Check (see Lemma 3.7) we observe that {a mathematical formula}{b,c,f} is the only answer set of P.
     </paragraph>
     <paragraph label="Remark">
      Please note that Definition 4.2, Definition 5.1 introduce additional edges or certain cycles, respectively, on head atoms for non-singleton heads in the constructed graphs. This construction has the same effect on the size of smallest deletion backdoors into Horn or acyclicity-based target classes as the lifting of corresponding parameters from normal to disjunctive programs.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Theoretical comparison of ASP-parameters
     </section-title>
     <paragraph>
      In this section we compare several ASP-parameters in terms of their generality. Fig. 7 illustrates the results in terms of a lattice. Let p and q be ASP-parameters. We say that p dominates q (in symbols {a mathematical formula}p⪯q) if there is a function f such that {a mathematical formula}p(P)≤f(q(P)) holds for all programs P. The parameters p and q are similar (in symbols {a mathematical formula}p∼q) if {a mathematical formula}p⪯q and {a mathematical formula}q⪯p. The parameter p strictly dominates q (in symbols {a mathematical formula}p≺q) if {a mathematical formula}p⪯q but not {a mathematical formula}q⪯p, and p and q are incomparable (in symbols {a mathematical formula}p⋈q) if neither {a mathematical formula}p⪯q nor {a mathematical formula}q⪯p.
     </paragraph>
     <paragraph label="Observation 8.1">
      Let p and q be ASP-parameters and{a mathematical formula}L∈AspFull. If p dominates q and{a mathematical formula}L[p]∈FPT, then also{a mathematical formula}L[q]∈FPT.
     </paragraph>
     <paragraph label="Observation 8.2">
      Let p and q be normal ASP-parameters and{a mathematical formula}∘∈{⪯,≺,⋈}. Then{a mathematical formula}p∘qif and only if{a mathematical formula}p↑∘q↑.
     </paragraph>
     <paragraph label="Proof">
      Let p and q be normal ASP-parameters. We will show that {a mathematical formula}p↑⪯q↑ iff {a mathematical formula}p⪯q. Since ≺ and ⋈ can be defined in terms of ⪯, this shows the claimed observation.Assume {a mathematical formula}p↑⪯q↑. Hence there is a function f such that for all programs P we have {a mathematical formula}p↑(P)≤f(q↑(P)). In particular, if P is normal we have by Definition 7.3 that {a mathematical formula}p(P)=p↑(P) and {a mathematical formula}q(P)=q↑(P), hence {a mathematical formula}p(P)≤q(P), and so {a mathematical formula}p⪯q.Now assume {a mathematical formula}p⪯q. Hence there is a function f such that for all normal programs P we have {a mathematical formula}p(P)≤f(q(P)). Let {a mathematical formula}f′,f″ be the monotonic functions on non-negative integers defined by {a mathematical formula}f′(n)=max0≤i≤n⁡f(n) and {a mathematical formula}f″(n)=f′(n)+n. Let P be a program and X a minimal deletion Normal-backdoor of P. We have {a mathematical formula}|X|+p(P−X)≤|X|+f(q(P−X))≤|X|+q(P−X)+f′(q(P−X))≤|X|+q(P−X)+f′(|X|+q(P−X))≤f″(|X|+q(P−X)). Hence {a mathematical formula}p↑⪯q↑ follows by Definition 7.3.  □
     </paragraph>
     <paragraph>
      Let {a mathematical formula}C be a class of programs. In the following, we omit {a mathematical formula}⋅↓ (see Definition 7.1) for the parameters {a mathematical formula}dbC and {a mathematical formula}sbC whenever it is clear from the context that we compare {a mathematical formula}dbC or {a mathematical formula}sbC with a normal ASP-parameter.
     </paragraph>
     <paragraph>
      In the following we define various auxiliary programs which we will use as examples, to separate the parameters from each other and establish incomparability or strictness results.
     </paragraph>
     <paragraph label="Example 8.1">
      Let m and n be some large integers. We define the following programs:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <section label="8.1">
      <section-title>
       ASP-parameters based on backdoor size
      </section-title>
      <paragraph>
       Backdoor-based ASP-parameters can be related to each other in terms of their underlying base classes. We just need a very weak assumption stated in the following which holds for all target classes considered in the paper. Therefore, we need the following definition: A class {a mathematical formula}C of programs is closed under the union of disjoint copies if for every {a mathematical formula}P∈C and disjoint copies {a mathematical formula}P1,…,Pi of P also {a mathematical formula}P∪P1∪…∪Pi∈C. We say a program {a mathematical formula}P′ is a disjoint copy of P if {a mathematical formula}P′ is isomorphic to P and {a mathematical formula}at(P)∩at(P′)=∅.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}C,C′be classes of programs that are closed under the union of disjoint copies. If{a mathematical formula}C⊆C′, then{a mathematical formula}dbC′⪯dbCand{a mathematical formula}sbC′⪯sbC, even{a mathematical formula}dbC′(P)≤dbC(P)and{a mathematical formula}sbC′(P)≤sbC(P)for every program P. If{a mathematical formula}C′∖Ccontains a program with at least one atom, then{a mathematical formula}C⊆C′implies{a mathematical formula}dbC′≺dbCand{a mathematical formula}sbC′≺sbC.The first statement is obvious. For the second statement, let {a mathematical formula}P∈C′∖C with {a mathematical formula}|at(P)|≥1. We construct the program {a mathematical formula}Pn consisting of n disjoint copies of P and observe that {a mathematical formula}Pn∈C′ but {a mathematical formula}dbC(Pn),sbC(Pn)≥n.  □
      </paragraph>
      <paragraph>
       Hence the relationships between target classes as stated in Observation 5.7 carry over to the corresponding backdoor-based ASP-parameters that is, if {a mathematical formula}C⊆C′ then a smallest strong (deletion) {a mathematical formula}C′-backdoor is at most the size of a smallest strong (deletion) {a mathematical formula}C-backdoor.
      </paragraph>
      <paragraph label="Observation 8.4">
       According to Lemma 3.4 every deletion {a mathematical formula}C-backdoor is a strong {a mathematical formula}C-backdoor if {a mathematical formula}C is hereditary, hence it also holds for smallest backdoors and we immediately get from the definitions: If{a mathematical formula}Cis hereditary, then{a mathematical formula}sbCdominates{a mathematical formula}dbC.
      </paragraph>
      <paragraph label="Observation 8.5">
       According to Lemma 4.1, every strong Horn-backdoor of a program is a deletion Horn-backdoor and vice versa. Hence we obtain the following statement: {a mathematical formula}sbHorn∼dbHorn.
      </paragraph>
      <paragraph label="Observation 8.6">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider program{a mathematical formula}P31nand{a mathematical formula}P32nand let{a mathematical formula}P∈{P31n,P32n}. Since{a mathematical formula}P−{a}is Horn and contains no cycle and no directed cycle, we obtain{a mathematical formula}dbHorn(P)≤1,{a mathematical formula}dbno-C(P)≤1, and{a mathematical formula}dbno-DC(P)≤1. According toObservation 8.3, we have{a mathematical formula}dbC(P31n)≤1and{a mathematical formula}dbC(P32n)≤1where{a mathematical formula}C∈{Horn}∪Acyc.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P33n. Since{a mathematical formula}P33n−{a}is Horn and contains no directed cycle and no bad cycle, we obtain{a mathematical formula}dbHorn(P33n)=0,{a mathematical formula}dbno-DC(P33n)≤1, and{a mathematical formula}dbno-BC(P33n)≤1. According toObservation 8.3, we have{a mathematical formula}dbC(P33n)≤1where{a mathematical formula}C∈{Horn,no-BC,no-BEC}∪D-Acyc.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P34n. Since{a mathematical formula}P34n−{a}contains no even cycle,{a mathematical formula}dbno-EC(P34n)≤1.
       </list-item>
       <list-item label="4.">
        Consider program{a mathematical formula}P4n. The negation dependency graph of{a mathematical formula}P4ncontains 2n disjoint paths{a mathematical formula}aibiand{a mathematical formula}aici. Thus smallest deletionHorn-backdoor are of size at least n.{a mathematical formula}P4ncontains n disjoint bad cycles, n directed cycles of length at least 3, and n directed even cycles. Hence smallest deletion{a mathematical formula}C-backdoors are of size at least n and thus{a mathematical formula}dbC(P4n)≥nwhere{a mathematical formula}C∈{Horn,no-C,no-BC,no-DC,no-DC2,no-EC,no-BEC,no-DEC}.
       </list-item>
       <list-item label="5.">
        Consider program{a mathematical formula}P51n. The negation dependency graph of{a mathematical formula}P51ncontains n disjoint paths and thus{a mathematical formula}dbHorn(P51n)=n.{a mathematical formula}P51ncontains n disjoint directed bad even cycles and thus{a mathematical formula}dbno-DBEC(P51n)=n. According toObservation 8.3, we obtain{a mathematical formula}dbC(P51n)≥nwhere{a mathematical formula}C∈{Horn}∪Acyc.
       </list-item>
       <list-item label="6.">
        Consider program{a mathematical formula}P52n. Since{a mathematical formula}P52ncontains n disjoint directed bad cycles,{a mathematical formula}dbno-DBC(P52n)=n.
       </list-item>
       <list-item label="7.">
        Consider program{a mathematical formula}P54n. Since{a mathematical formula}P54ncontains n disjoint even cycles, n disjoint directed cycles of length at least 3, and n disjoint directed even cycles, we obtain byObservation 8.3{a mathematical formula}dbC(P54n)≥nwhere{a mathematical formula}C∈{no-C,no-DC,no-DC2,no-EC,no-DEC}.
       </list-item>
       <list-item label="8.">
        Consider program{a mathematical formula}P6n. Since{a mathematical formula}P6nis Horn and contains no cycle and no directed cycle,{a mathematical formula}dbHorn(P6n)=dbno-C(P6n)=dbno-DC(P6n)=0. According toObservation 8.3, we have{a mathematical formula}dbC(P6n)=0where{a mathematical formula}C∈{Horn}∪Acyc.
       </list-item>
       <list-item label="9.">
        Consider program{a mathematical formula}P7n. Since{a mathematical formula}P7nis Horn and contains no bad cycle and no directed cycle,{a mathematical formula}dbHorn(P7n)=dbno-BC(P7n)=dbno-DC(P7n)=0. According toObservation 8.3, we have{a mathematical formula}dbC(P7n)=0where{a mathematical formula}C∈{Horn,no-BC,no-BEC}∪D-Acyc.
       </list-item>
       <list-item label="10.">
        Consider program{a mathematical formula}P8m,n. Since{a mathematical formula}P8m,nis Horn and{a mathematical formula}P8m,n−{c1}contains no cycle and no directed cycle, we obtain{a mathematical formula}dbHorn(P8m,n)=0,{a mathematical formula}dbno-C(P8m,n)≤1,{a mathematical formula}dbno-DC(P8m,n)≤1. According toObservation 8.3, we have{a mathematical formula}dbC(P8m,n)≤1where{a mathematical formula}C∈{Horn}∪Acyc.
       </list-item>
       <list-item label="11.">
        Consider program{a mathematical formula}P9n. Since{a mathematical formula}P9n−{a2}is Horn and{a mathematical formula}P9n−{a1}contains no cycle and no directed cycle, we have{a mathematical formula}dbHorn(P9n)≤1,{a mathematical formula}dbno-C(P9n)≤1, and{a mathematical formula}dbno-DC(P9n)≤1. According toObservation 8.3, we have{a mathematical formula}dbC(P9n)≤1where{a mathematical formula}C∈{Horn}∪Acyc.
       </list-item>
       <list-item label="12.">
        Consider program{a mathematical formula}P11nand let{a mathematical formula}X={b}. Since{a mathematical formula}P11n−Xis normal, X is a deletionNormal-backdoor of{a mathematical formula}P11n. Since{a mathematical formula}P11n−Xis Horn, X is a deletionHorn-backdoor of{a mathematical formula}P11nand{a mathematical formula}dbHorn(P11n−X)=1. Since{a mathematical formula}P11n−Xcontains no cycle, no even cycle, and no directed cycle, we have{a mathematical formula}dbC(P11n−X)=1where{a mathematical formula}C∈Acyc. Consequently,{a mathematical formula}dbC(P11n−X)=1where{a mathematical formula}C∈{Horn,Normal}∪Acyc.
       </list-item>
      </list>
     </section>
     <section label="8.2">
      <section-title>
       ASP-parameters based on the distance from Horn
      </section-title>
      <paragraph>
       Our backdoor-based ASP-parameter {a mathematical formula}dbHorn can be considered as a parameter that measures the distance of a program from being a Horn program. In the literature some normal ASP-parameters have been proposed, that also can be considered as distance measures from Horn. In this section we compare them with {a mathematical formula}dbHorn. Since the ASP-parameters considered in the literature are normal, we compare the parameters for normal programs only. However, in view of Observation 8.2 the results also hold for the lifted parameters to disjunctive programs.
      </paragraph>
      <paragraph label="Definition 8.7">
       (See Ben-Eliyahu [4].) Let P be a normal program. Then{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 8.8">
       (See Ben-Eliyahu[4].) For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[#neg]N∈FPTand{a mathematical formula}L[#non-Horn]N∈FPT.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}Bound[p]N for {a mathematical formula}p∈{#neg,#non-Horn} is clearly solvable in polynomial time and thus fixed-parameter tractable, we can use the Lifting Theorem (Theorem 7.5) to obtain the following result.
      </paragraph>
      <paragraph label="Corollary 8.9">
       For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[#neg↑]∈FPTand{a mathematical formula}L[#non-Horn↑]∈FPT.
      </paragraph>
      <paragraph label="Observation 8.10">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider program{a mathematical formula}P1nwhich contains n atoms that occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈Pand exactly one non-Horn rule. Thus,{a mathematical formula}#neg(P1n)=nand{a mathematical formula}#non-Horn(P1n)=1.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P2nwhich contains only the atom b that occurs in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P2nand n non-Horn rules. Thus,{a mathematical formula}#neg(P2n)=1and{a mathematical formula}#non-Horn(P2n)=n.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P31nwhich contains for{a mathematical formula}1≤i≤nthe atoms a and{a mathematical formula}bithat occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P31nand the non-Horn rules{a mathematical formula}bi←¬aand{a mathematical formula}a←¬bi. Hence,{a mathematical formula}#neg(P31n)=n+1and{a mathematical formula}#non-Horn(P31n)=2n.
       </list-item>
       <list-item label="4.">
        Consider program{a mathematical formula}P32nwhich is Horn. Thus,{a mathematical formula}#neg(P32n)=#non-Horn(P32n)=0.
       </list-item>
       <list-item label="5.">
        Consider program{a mathematical formula}P35nwhich contains only the atom a that occurs in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P35nand exactly one non-Horn rule. So{a mathematical formula}#neg(P35n)=#non-Horn(P35n)=1.
       </list-item>
       <list-item label="6.">
        Consider program{a mathematical formula}P4nwhich contains for{a mathematical formula}1≤i≤nthe atoms{a mathematical formula}aithat occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P4nand the non-Horn rules{a mathematical formula}bi←¬aiand{a mathematical formula}ci←¬ai. Thus,{a mathematical formula}#neg(P4n)=nand{a mathematical formula}#non-Horn(P4n)=2n.
       </list-item>
       <list-item label="7.">
        Consider program{a mathematical formula}P51nwhich contains for{a mathematical formula}1≤i≤nthe atoms{a mathematical formula}aiand{a mathematical formula}bithat occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈Pand the non-Horn rules{a mathematical formula}bi←¬aiand{a mathematical formula}ai←¬bi. Hence,{a mathematical formula}#neg(P51n)=#non-Horn(P51n)=2n.
       </list-item>
       <list-item label="8.">
        Consider the program{a mathematical formula}P52nwhich contains the atoms{a mathematical formula}bithat occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P52nand the non-Horn rules{a mathematical formula}ai←¬bi. Hence,{a mathematical formula}#neg(P52n)=#non-Horn(P52n)=n.
       </list-item>
       <list-item label="9.">
        Consider programs{a mathematical formula}P54n,{a mathematical formula}P6n,{a mathematical formula}P7n, and{a mathematical formula}P8m,nwhich are Horn. Thus,{a mathematical formula}#neg(P54n)=#non-Horn(P54n)=#neg(P6n)=#non-Horn(P6n)=#neg(P7n)=#non-Horn(P7n)=#neg(P8m,n)=#non-Horn(P8m,n)=0.
       </list-item>
       <list-item label="10.">
        Consider the program{a mathematical formula}P9nwhich contains only the atoms{a mathematical formula}a1and{a mathematical formula}a2that occur in{a mathematical formula}B−(r)for some rule{a mathematical formula}r∈P9nand only the non-Horn rules{a mathematical formula}a2←¬a1and{a mathematical formula}a3←¬a2. Hence,{a mathematical formula}#neg(P9n)=#non-Horn(P9n)=2.
       </list-item>
       <list-item label="11.">
        Consider the program{a mathematical formula}P11n. The set{a mathematical formula}X={b}is a deletionNormal-backdoor of{a mathematical formula}P11n. Since{a mathematical formula}P11n−Xis Horn, we have{a mathematical formula}#neg(P11n−X)=#non-Horn(P11n−X)=0. Thus,{a mathematical formula}#neg↑(P11n)=|X|+#neg(P11n−X)=1and{a mathematical formula}#non-Horn↑(P11n)=|X|+#non-Horn(P11n−X)=1.
       </list-item>
      </list>
      <paragraph label="Proof">
       {a mathematical formula}#negand{a mathematical formula}#non-Hornare incomparable.The proposition directly follows from considering {a mathematical formula}P1n and {a mathematical formula}P2n where {a mathematical formula}#neg(P1n)=n and {a mathematical formula}#non-Horn(P1n)=1; and {a mathematical formula}#neg(P2n)=1 and {a mathematical formula}#non-Horn(P2n)=n by Observation 8.10.  □
      </paragraph>
      <paragraph>
       However, it is easy to see that {a mathematical formula}dbHorn dominates both parameters.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}dbHornstrictly dominates{a mathematical formula}#negand{a mathematical formula}#non-Horn.{a mathematical formula}dbCand{a mathematical formula}#neg; and{a mathematical formula}dbCand{a mathematical formula}#non-Hornare incomparable where{a mathematical formula}C∈{no-C,no-DC,no-DC2,no-EC,no-DEC}.For a normal program P define the sets {a mathematical formula}B−(P)={a∈at(P):a∈B−(r) for some rule r∈P} and {a mathematical formula}H(P)={a∈H(r):r∈P,r is not Horn}. We observe that {a mathematical formula}B−(P) and {a mathematical formula}H(P) are deletion Horn-backdoors of P, hence {a mathematical formula}dbHorn(P)≤#neg(P) and {a mathematical formula}dbHorn(P)≤#non-Horn(P). To show that {a mathematical formula}dbHorn strictly dominates the two parameters, consider {a mathematical formula}P31n where {a mathematical formula}dbHorn(P31n)≤1, but {a mathematical formula}#neg(P31n)=n+1 and {a mathematical formula}#non-Horn(P31n)=2n by Observation 8.6, Observation 8.10.The second statement follows from considering the programs {a mathematical formula}P31n and {a mathematical formula}P54n where {a mathematical formula}dbC(P31n)≤1 and {a mathematical formula}p(P31n)≥n+1; and {a mathematical formula}dbC(P54n)≥n and {a mathematical formula}p(P54n)=0 for {a mathematical formula}C∈{no-C,no-DC,no-DC2,no-EC,no-DEC} and {a mathematical formula}p∈{#neg,#non-Horn} by Observation 8.6, Observation 8.10. Hence {a mathematical formula}dbC⋈#neg and {a mathematical formula}dbC⋈#non-Horn for {a mathematical formula}C∈{no-C,no-DC,no-DC2,no-EC,no-DEC}.  □
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       ASP-parameters based on the distance from being stratified
      </section-title>
      <paragraph>
       Ben-Eliyahu [4] and Gottlob et al. [85] have considered ASP-parameters that measure in a certain sense how far away a program is from being stratified. In this section we will investigate how these parameters fit into our landscape of ASP-parameters. Similar to the last section the parameters have been considered for normal programs only, hence we compare the parameters for normal programs only. Again, in view of Observation 8.2 the results also hold for the lifted parameters to disjunctive programs.
      </paragraph>
      <paragraph>
       Recall from Section 2.4 that {a mathematical formula}SCC(G) denotes the partition of the vertex set of a digraph into strongly connected components.
      </paragraph>
      <paragraph label="Definition 8.13">
       (See Ben-Eliyahu [4].) Let P be a normal program, {a mathematical formula}DP its dependency digraph, and {a mathematical formula}A⊆at(P). {a mathematical formula}P/A denotes the program obtained from P by (i) deleting all rules r in the program P where {a mathematical formula}H(r)∩A=∅ and (ii) removing from the bodies of the remaining rules all literals ¬a with {a mathematical formula}a∉A (this corresponds to the well-known concept of a reduct). Then{a mathematical formula}{a mathematical formula}lstr(P) is called the level of stratifiability of P.
      </paragraph>
      <paragraph label="Proposition 8.14">
       (See Ben-Eliyahu[4].) For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[lstr]N∈FPT.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}Bound[lstr]N is clearly solvable in polynomial time and thus fixed-parameter tractable, we can use the Lifting Theorem (Theorem 7.5) to obtain the following result.
      </paragraph>
      <paragraph label="Corollary 8.15">
       For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[lstr↑]∈FPT.
      </paragraph>
      <paragraph label="Observation 8.16">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider program{a mathematical formula}P31nand let{a mathematical formula}P=P31n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P)and thus{a mathematical formula}P/C=P. ByObservation 8.10{a mathematical formula}#neg(P)=n+1and{a mathematical formula}#non-Horn(P)=2nand hence{a mathematical formula}lstr(P31n)=n+1.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P32nand let{a mathematical formula}P=P32n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P)and{a mathematical formula}P/C=P. Since{a mathematical formula}#neg(P)=0byObservation 8.10, we have{a mathematical formula}lstr(P32n)=0.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P35nand let{a mathematical formula}P=P35n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P). Thus,{a mathematical formula}P=P/C. Since{a mathematical formula}#neg(P35n)=1byObservation 8.10, we conclude{a mathematical formula}lstr(P35n)≤1.
       </list-item>
       <list-item label="4.">
        Consider program{a mathematical formula}P4nand let{a mathematical formula}P=P4n. We have{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ai={ai,ei,di},{a mathematical formula}Bi={bi}, and{a mathematical formula}Ci={ci}where{a mathematical formula}1≤i≤n. Hence{a mathematical formula}P/Ai={ai←ei;ei←di;di←ai}and{a mathematical formula}P/Bi={bi}and{a mathematical formula}P/Ci={ci;ci←bi}. Since{a mathematical formula}#neg(P/C)=0for every{a mathematical formula}C∈SCC(DP), we have{a mathematical formula}lstr(P4n)=0.
       </list-item>
       <list-item label="5.">
        Consider program{a mathematical formula}P51nand{a mathematical formula}P52nand let{a mathematical formula}P∈{P51n,P52n}. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ci={ai,bi}where{a mathematical formula}1≤i≤nand hence{a mathematical formula}P/Ci={bi←¬ai;ai←¬bi}and{a mathematical formula}P/Ci={bi←ai;ai←¬bi:1≤i≤n}, respectively. Since{a mathematical formula}#neg(P/Ci)=#non-Horn(P/Ci)=2, respectively{a mathematical formula}#neg(P/Ci)=#non-Horn(P/Ci)=1, and there are n components we obtain{a mathematical formula}lstr(P51n)=2nand{a mathematical formula}lstr(P52n)=n.
       </list-item>
       <list-item label="6.">
        Consider program{a mathematical formula}P6nand let{a mathematical formula}P=P6n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}A={a},{a mathematical formula}Bi={bi}, and{a mathematical formula}Ci={ci}where{a mathematical formula}1≤i≤n. Hence{a mathematical formula}P/A={a←b1,…,bn,ci:1≤i≤n}and{a mathematical formula}P/Bi=P/Ci=∅where{a mathematical formula}1≤i≤n. Since{a mathematical formula}#neg(P/C)=0for every{a mathematical formula}C∈SCC(DP), we have{a mathematical formula}lstr(P6n)=0.
       </list-item>
       <list-item label="7.">
        Consider program{a mathematical formula}P7nand let{a mathematical formula}P=P7n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ci={ai}where{a mathematical formula}1≤i≤n. Thus,{a mathematical formula}P/Ci={ai←aj:1≤j&lt;i}. Hence{a mathematical formula}#neg(P/Ci)=0for every{a mathematical formula}C∈SCC(DP). We obtain{a mathematical formula}lstr(P7n)=0.
       </list-item>
       <list-item label="8.">
        Consider program{a mathematical formula}P8m,nand let{a mathematical formula}P=P8m,n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ai={ai}where{a mathematical formula}1≤i≤m,{a mathematical formula}B={b}, and{a mathematical formula}C={ci:1≤i≤n}. Hence{a mathematical formula}P/Ai=∅where{a mathematical formula}1≤i≤m,{a mathematical formula}P/B={b←a1,…,am}, and{a mathematical formula}P/C={ci←ci+1:1≤i≤n}∪{cn+1←c1}. Since{a mathematical formula}#neg(P/Ai)=0where{a mathematical formula}1≤i≤m,{a mathematical formula}#neg(P/B)=0, and{a mathematical formula}#neg(P/C)=0, we obtain{a mathematical formula}lstr(P8m,n)=0.
       </list-item>
       <list-item label="9.">
        Consider program{a mathematical formula}P9nand let{a mathematical formula}P=P9n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P). Hence{a mathematical formula}P/C=P. Since{a mathematical formula}#neg(P)=#non-Horn(P)=2, we have{a mathematical formula}lstr(P9n)=2.
       </list-item>
       <list-item label="10.">
        Consider program{a mathematical formula}P11n. The set{a mathematical formula}X={b}is a deletionNormal-backdoor of{a mathematical formula}P11nbyObservation 8.6. We have{a mathematical formula}P=P11n−X={ai←c;c;←ai:1≤i≤n}. The partition{a mathematical formula}SCC(DP)contains the sets{a mathematical formula}Ai={ai}, where{a mathematical formula}1≤i≤n, and{a mathematical formula}C={c}. Hence{a mathematical formula}P/Ai={ai←c}, where{a mathematical formula}1≤i≤n, and{a mathematical formula}P/C={c}. Since{a mathematical formula}#neg(P/C)=0for every{a mathematical formula}C∈SCC(DP), we obtain{a mathematical formula}lstr(P)=0. Consequently,{a mathematical formula}lstr↑(P11n)=|X|+lstr(P11n−X)=1.
       </list-item>
      </list>
      <paragraph label="Proof">
       lstr strictly dominates{a mathematical formula}#negand{a mathematical formula}#non-Horn.Let P be a normal program. We first show that {a mathematical formula}∑C∈SCC(DP)#neg(P/C)≤#neg(P). Define the set {a mathematical formula}B−(P)={a∈at(P):a∈B−(r) for some rule r∈P}. By definition {a mathematical formula}B−(P/A)⊆B−(P) for some {a mathematical formula}A⊆at(P); thus, {a mathematical formula}⋃C∈SCC(DP)B−(P/C)⊆B−(P). Let {a mathematical formula}C,C′∈SCC(DP) and {a mathematical formula}C≠C′. By definition of a strongly connected component we have {a mathematical formula}C∩C′=∅ and by definition we have that {a mathematical formula}B−(P/C)⊆C and {a mathematical formula}B−(P/C′)⊆C′. Hence {a mathematical formula}B−(P/C)∩B−(P/C′)=∅. Consequently {a mathematical formula}∑C∈SCC(DP)#neg(P/C)≤#neg(P). A similar argument shows that {a mathematical formula}∑C∈SCC(DP)#non-Horn(P/C)≤#non−Horn(P). Since {a mathematical formula}lstr(P)=∑C∈SCC(DP)min⁡{#neg(P/C),#non-Horn(P/C)}, we have {a mathematical formula}lstr(P)≤#neg(P) and {a mathematical formula}lstr(P)≤#non-Horn(P). To show that lstr strictly dominates the two parameters, consider program {a mathematical formula}P4n where {a mathematical formula}lstr(P4n)=0, but {a mathematical formula}#neg(P4n)≥n and {a mathematical formula}#non−Horn(P4n)≥2n by Observation 8.10, Observation 8.16. Hence the observation is true.  □
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}dbno-DBCstrictly dominates lstr. Moreover,{a mathematical formula}dbCand lstr are incomparable for the remaining target classes namely{a mathematical formula}C∈Acyc∖{no-DBC,no-DBEC}∪{Horn}.We first show that {a mathematical formula}dbno-DBC dominates lstr. For a normal program P define the sets {a mathematical formula}B−(P)={a∈at(P):a∈B−(r) for some rule r∈P} and {a mathematical formula}H(P)={a∈H(r):r∈P,r is not Horn}. Let {a mathematical formula}C∈SCC(DP), we define{a mathematical formula} and {a mathematical formula}X={XC:C∈SCC(DP)}. We show that X is a deletion {a mathematical formula}no-DBC-backdoor of P. By definition for every directed bad cycle {a mathematical formula}c=(x1,…,xl) of {a mathematical formula}DP the atom {a mathematical formula}xi∈C′ where {a mathematical formula}1≤i≤l and {a mathematical formula}C′∈SCC(DP) (all vertices of c belong to the same strongly connected component). Moreover, by definition we have for every negative edge {a mathematical formula}(xi,xj)∈DP of the dependency digraph {a mathematical formula}DP a corresponding rule {a mathematical formula}r∈P such that {a mathematical formula}xj∈H(r) and {a mathematical formula}xi∈B−(r). Since {a mathematical formula}XC consists of either {a mathematical formula}B−(P/C) or {a mathematical formula}H(P/C), at least one of the atoms {a mathematical formula}xi,xj belongs to {a mathematical formula}XC. Thus, for every directed bad cycle c of the program P at least one atom of the cycle belongs to X. Hence {a mathematical formula}P−X∈no-DBC and X is a deletion {a mathematical formula}no-DBC-backdoor of P. We obtain {a mathematical formula}dbno-DBC(P)≤lstr(P). To show that {a mathematical formula}dbno-DBC strictly dominates lstr, consider program {a mathematical formula}P31n where {a mathematical formula}dbno-DBC(P31n)≤1 and {a mathematical formula}lstr(P31n)=n+1 by Observation 8.6, Observation 8.16. Hence {a mathematical formula}dbno-DBC≺lstr.Then we show that the parameters {a mathematical formula}dbC and lstr are incomparable. Consider the programs {a mathematical formula}P3n and {a mathematical formula}P4n where {a mathematical formula}dbC(P31n)≤1 and {a mathematical formula}lstr(P31n)=n+1; and {a mathematical formula}lstr(P4n)=0 and {a mathematical formula}dbC(P4n)≥n for {a mathematical formula}C∈{Horn,no-C,no-BC,no-DC,no-DC2,no-EC,no-BEC,no-DEC} by Observation 8.6, Observation 8.16. We conclude {a mathematical formula}dbC⋈lstr.  □
      </paragraph>
      <paragraph label="Definition 8.19">
       (See Gottlob et al. [85].) Let P be a normal program, {a mathematical formula}DP its dependency digraph, {a mathematical formula}UP its dependency graph, and {a mathematical formula}A⊆at(P). {a mathematical formula}Pˆ/A denotes the program obtained from {a mathematical formula}P/A by removing from the bodies of every rule all literals a with {a mathematical formula}a∉A. {a mathematical formula}at+(P) denotes the maximal set {a mathematical formula}W⊆at(P) such that there is no bad W-cycle in the dependency graph {a mathematical formula}UP, in other words the set of all atoms that do not lie on a bad cycle of P. Then{a mathematical formula}{a mathematical formula}fw(P) is called the feedback-width of P, and {a mathematical formula}wfw(P) is called the weak-feedback-width of P.
      </paragraph>
      <paragraph label="Observation 8.20">
       Let P be a normal program and{a mathematical formula}DPits dependency digraph. Then{a mathematical formula}fw(P)=dbno-C(P)and hence{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 8.21">
       (See Gottlob et al.[85].) For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[fw]N∈FPTand{a mathematical formula}L[wfw]N∈FPT.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}Bound[fw]N and {a mathematical formula}Bound[wfw]N is fixed-parameter tractable, we can use the Lifting Theorem (Theorem 7.5) to obtain the following result.
      </paragraph>
      <paragraph label="Corollary 8.22">
       For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[fw↑]∈FPTand{a mathematical formula}L[wfw↑]∈FPT.
      </paragraph>
      <paragraph label="Observation 8.23">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider the program{a mathematical formula}P31nand let{a mathematical formula}P=P31n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P). For every atom{a mathematical formula}a∈Cthe program P contains a bad{a mathematical formula}{a}-cycle and thus{a mathematical formula}at+(Pˆ/C)=∅. Consequently,{a mathematical formula}Pˆ/C−at+(Pˆ/C)=Pˆ/C=P. As{a mathematical formula}P∉no-DBC,{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C),C∈SCC(DP),Pˆ/C∉no-DBC}=P. We have{a mathematical formula}dbno-C(P)=1byObservation 8.6and according toObservation 8.20, we obtain{a mathematical formula}wfw(P31n)=1.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P32nand let{a mathematical formula}P=P32n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P),{a mathematical formula}Pˆ/C=P. For every atom{a mathematical formula}a∈Cwe have{a mathematical formula}Pˆ/C∈no-DBCand thus{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}=∅. Consequently,{a mathematical formula}wfw(P32n)=0.
       </list-item>
       <list-item label="3.">
        Consider the programs{a mathematical formula}P33n,{a mathematical formula}P34n, and{a mathematical formula}P35nand let{a mathematical formula}P∈{P33n,P34n,P35n}. We first observe that the dependency digraph of P contains only one strongly connected component. Hence the partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P). For every atom{a mathematical formula}a∈Cprogram P contains a bad{a mathematical formula}{a}-cycle and thus{a mathematical formula}at+(Pˆ/C)=∅. Consequently,{a mathematical formula}Pˆ/C−at+(Pˆ/C)=Pˆ/C=P. Since{a mathematical formula}P∉no-DBC, we obtain{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C),C∈SCC(DP),Pˆ/C∉no-DBC}=P. We have{a mathematical formula}dbno-C(P)=nsince P contains n disjoint{a mathematical formula}{bi}-cycles. According toObservation 8.20, we conclude{a mathematical formula}wfw(P33n)=wfw(P34n)=wfw(P35n)=n.
       </list-item>
       <list-item label="4.">
        Consider program{a mathematical formula}P4nand let{a mathematical formula}P=P4n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ai={ai,di,ei},{a mathematical formula}Bi={bi}, and{a mathematical formula}Ci={ci}, for{a mathematical formula}1≤i≤n. Hence{a mathematical formula}Pˆ/Ai={ai←ei;ei←di;di←ai},{a mathematical formula}Pˆ/Bi={bi}and{a mathematical formula}Pˆ/Ci={ci}. For every{a mathematical formula}C∈SCC(DP)the program{a mathematical formula}Pˆ/C∈no-DBC. Consequently,{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C),C∈SCC(DP),Pˆ/C∉no-DBC}=∅and we obtain{a mathematical formula}wfw(P4n)=0.
       </list-item>
       <list-item label="5.">
        Consider program{a mathematical formula}P51nand let{a mathematical formula}P=P51n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ci={ai,bi}, for{a mathematical formula}1≤i≤n, and thus{a mathematical formula}Pˆ/Ci={ai←¬bi;bi←¬ai}. Since{a mathematical formula}dbno-C(Pˆ/Ci)=1and there are n components we obtain{a mathematical formula}wfw(P51n)=n.
       </list-item>
       <list-item label="6.">
        Consider program{a mathematical formula}P52nand let{a mathematical formula}P=P52n. We observe that the partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ci={ai,bi}. For every atom{a mathematical formula}a∈Ciwhere{a mathematical formula}1≤i≤nthere is a bad{a mathematical formula}{a}-cycle in the dependency graph of{a mathematical formula}Pˆ/Ciand thus{a mathematical formula}at+(Pˆ/Ci)=∅. Consequently,{a mathematical formula}Pˆ/Ci−at+(Pˆ/Ci)=Pˆ/Ci. Since{a mathematical formula}Pˆ/Ci∉no-DBC,{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}=P. We observe that{a mathematical formula}dbno-C(P)=nand according toObservation 8.20, we obtain{a mathematical formula}wfw(P52n)=n.
       </list-item>
       <list-item label="7.">
        Consider program{a mathematical formula}P6nand let{a mathematical formula}P=P6n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}A={a},{a mathematical formula}Bi={bi}, and{a mathematical formula}Ci={ci}where{a mathematical formula}1≤i≤n. Hence{a mathematical formula}Pˆ/A={a}and{a mathematical formula}Pˆ/Bi=Pˆ/Ci=∅where{a mathematical formula}1≤i≤n. Since{a mathematical formula}dbno-C(Pˆ/C)=0for every{a mathematical formula}C∈SCC(DP), we obtain{a mathematical formula}wfw(P6n)=0.
       </list-item>
       <list-item label="8.">
        Consider program{a mathematical formula}P7nand let{a mathematical formula}P=P7n. Since the partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}{ai}where{a mathematical formula}1≤i≤n,{a mathematical formula}Pˆ/{ai}={ai}and thus{a mathematical formula}wfw(Pˆ/{ai})=0. We obtain{a mathematical formula}wfw(P7n)=0.
       </list-item>
       <list-item label="9.">
        Consider program{a mathematical formula}P8m,nand let{a mathematical formula}P=P8m,n. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}Ai={ai}for{a mathematical formula}1≤i≤m,{a mathematical formula}B={b}, and{a mathematical formula}C={ci:1≤i≤n}. Hence{a mathematical formula}Pˆ/Ai=∅for{a mathematical formula}1≤i≤m,{a mathematical formula}Pˆ/B=∅, and{a mathematical formula}Pˆ/C={ci←ci+1:1≤i≤n}∪{cn+1←c1}. The programs{a mathematical formula}Pˆ/Ai,{a mathematical formula}Pˆ/B, and{a mathematical formula}Pˆ/Cbelong to the class{a mathematical formula}no-DBCfor{a mathematical formula}1≤i≤m. Consequently{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}=∅. Hence we conclude that{a mathematical formula}wfw(P8m,n)=0.
       </list-item>
       <list-item label="10.">
        Consider program{a mathematical formula}P9nand let{a mathematical formula}P=P9n. The partition{a mathematical formula}SCC(DP)contains only the set{a mathematical formula}C=at(P). For every atom{a mathematical formula}a∈Cthere is a bad{a mathematical formula}{a}-cycle in the dependency graph of P and thus{a mathematical formula}at+(Pˆ/C)=∅. Consequently,{a mathematical formula}Pˆ/C−at+(Pˆ/C)=Pˆ/C=P. Since{a mathematical formula}P∉no-DBC,{a mathematical formula}{r∈Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}=P. ByObservation 8.6{a mathematical formula}dbno-C(P)≤1and according toObservation 8.20, we obtain{a mathematical formula}wfw(P9n)≤1.
       </list-item>
       <list-item label="11.">
        Consider program{a mathematical formula}P11nand let{a mathematical formula}P=P11n. The set{a mathematical formula}X={b}is a deletionNormal-backdoor of{a mathematical formula}P11nbyObservation 8.6and{a mathematical formula}P=P11n−X={ai←c;c;←ai:1≤i≤n}. The partition{a mathematical formula}SCC(DP)contains exactly the sets{a mathematical formula}{ai}for{a mathematical formula}1≤i≤nand{a mathematical formula}{c}. Hence{a mathematical formula}Pˆ/{ai}={ai}for{a mathematical formula}1≤i≤nand{a mathematical formula}Pˆ/{c}={c}. We observe that{a mathematical formula}dbno-C(Pˆ/C)=0for every{a mathematical formula}C∈SCC(DP)and according toObservation 8.20, we obtain{a mathematical formula}wfw(P)=0. Consequently,{a mathematical formula}wfw↑(P11n)=|X|+wfw(P11n−X)=1.
       </list-item>
      </list>
      <paragraph>
       In the following proposition we state the relationship between the parameter wfw and our backdoor-based ASP parameters. The first result ({a mathematical formula}dbno-DBC strictly dominates wfw) was anticipated by Gottlob et al. [85].
      </paragraph>
      <paragraph label="Proof">
       wfw strictly dominates{a mathematical formula}dbno-Cand{a mathematical formula}dbno-DBCstrictly dominates wfw. Moreover,{a mathematical formula}dbCand wfw are incomparable for the remaining target classes namely{a mathematical formula}C∈{Horn,no-BC,no-DC,no-DC2,no-EC,no-BEC,no-DEC}.We first show that wfw strictly dominates {a mathematical formula}dbno-C. Let P be a normal program and X be a deletion {a mathematical formula}no-C-backdoor of P. Define {a mathematical formula}Pˆ={Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}. Since {a mathematical formula}Pˆ⊆P and {a mathematical formula}no-C is hereditary (Observation 5.6), {a mathematical formula}Pˆ−X∈no-C and hence X is a deletion {a mathematical formula}no-C-backdoor of {a mathematical formula}Pˆ. Consequently, {a mathematical formula}wfw(P)≤dbno-C(Pˆ). To show that wfw is strictly more general than {a mathematical formula}dbno-C, consider the program {a mathematical formula}P4n where {a mathematical formula}wfw(P4n)=0 and {a mathematical formula}dbno-C(P4n)=n. Hence {a mathematical formula}wfw≺dbno-C by Proposition 8.3, Observation 8.23.Next, we show that {a mathematical formula}dbno-DBC strictly dominates wfw. Let P be a normal program and {a mathematical formula}Pˆ={Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC}. According to Observation 8.20, {a mathematical formula}wfw(P)=dbno-C(Pˆ) and thus it is sufficient to show that {a mathematical formula}dbno-DBC(P)&lt;dbno-C(Pˆ). Let X be an arbitrary deletion {a mathematical formula}no-C-backdoor of {a mathematical formula}Pˆ. Since {a mathematical formula}no-C⊆no-DBCObservation 8.3 yields that X is also a deletion {a mathematical formula}no-DBC-backdoor of {a mathematical formula}Pˆ. Let c be an arbitrary directed bad cycle of {a mathematical formula}DP. As all vertices of c belong to the same partition {a mathematical formula}C∈SCC(DP), {a mathematical formula}at(Pˆ/C)⊆C, and {a mathematical formula}DPˆ/C is an induced subdigraph of {a mathematical formula}DP on {a mathematical formula}at(Pˆ/C), we obtain c is a directed bad cycle in {a mathematical formula}DPˆ/C. Since {a mathematical formula}Pˆ={Pˆ/C−at+(Pˆ/C):C∈SCC(DP),Pˆ/C∉no-DBC} and by definition there is no {a mathematical formula}at+(Pˆ/C)-cycle in {a mathematical formula}UP, there is no directed bad {a mathematical formula}at+(Pˆ/C)-cycle in {a mathematical formula}DP and hence c is also a directed bad cycle in {a mathematical formula}DPˆ/C. Since X is a deletion {a mathematical formula}no-DBC-backdoor of {a mathematical formula}DPˆ/C and c is a directed bad X-cycle in {a mathematical formula}DPˆ/C, X is also a deletion {a mathematical formula}no-DBC-backdoor of P. Consequently, {a mathematical formula}dbno-DBC(P)≤dbno-C(Pˆ)=wfw(P). To show that {a mathematical formula}dbno-DBC is strictly more general than the parameter wfw, consider the program {a mathematical formula}P33n where {a mathematical formula}dbno-DBC(P33n)≤1 and {a mathematical formula}wfw(P33n)=n by Observation 8.6, Observation 8.23. Hence {a mathematical formula}dbno-DBC≺lstr.The third statement follows from considering the programs {a mathematical formula}P33n, {a mathematical formula}P34n, and {a mathematical formula}P4n where {a mathematical formula}dbC(P33n)≤1 for {a mathematical formula}C∈{Horn,no-BC,no-DC,no-DC2,no-BEC,no-DEC} and {a mathematical formula}dbno-EC(P34n)≤1 and {a mathematical formula}wfw(P33n)=wfw(P34n)=n; and {a mathematical formula}wfw(P4n)=0 and {a mathematical formula}dbC(P4n)=n by Observation 8.6, Observation 8.23. Hence {a mathematical formula}dbC⋈wfw for {a mathematical formula}C∈{Horn,no-BC,no-DC,no-DC2,no-EC,no-BEC,no-DEC}.  □
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}p∈{#neg,#non-Horn,lstr}, then p and wfw are incomparable.To show that p and wfw are incomparable consider the programs {a mathematical formula}P31n and {a mathematical formula}P35n where {a mathematical formula}p(P31n)≥n+1 and {a mathematical formula}wfw(P31n)=1; and {a mathematical formula}p(P35n)≤1 and {a mathematical formula}wfw(P35n)=n by Observation 8.10, Observation 8.16, Observation 8.23.  □
      </paragraph>
     </section>
     <section label="8.4">
      <section-title>
       Incidence treewidth
      </section-title>
      <paragraph>
       Treewidth is graph parameter introduced by Robertson and Seymour [130], [131], [132] that measures in a certain sense the tree-likeness of a graph. See [8], [9], [10], [86] for further background and examples on treewidth. Treewidth has been widely applied in knowledge representation, reasoning, and artificial intelligence [39], [86], [90], [118], [126].
      </paragraph>
      <paragraph label="Definition 8.26">
       Let {a mathematical formula}G=(V,E) be a graph, {a mathematical formula}T=(N,ET) a tree, and χ a labeling that maps any node t of T to a subset {a mathematical formula}χ(t)⊆V. We call the sets {a mathematical formula}χ(⋅)bags and denote the vertices of T as nodes. The pair {a mathematical formula}(T,χ) is a tree decomposition of G if the following conditions hold:
      </paragraph>
      <list>
       <list-item label="1.">
        for every vertex {a mathematical formula}v∈V there is a node {a mathematical formula}t∈N such that {a mathematical formula}v∈χ(t) (“vertices covered”);
       </list-item>
       <list-item label="2.">
        for every edge {a mathematical formula}vw∈E there is a node {a mathematical formula}t∈N such that {a mathematical formula}v,w∈χ(t) (“edges covered”); and
       </list-item>
       <list-item label="3.">
        for any three nodes {a mathematical formula}t1,t2,t3∈N, if {a mathematical formula}t2 lies on the unique path from {a mathematical formula}t1 to {a mathematical formula}t3, then {a mathematical formula}χ(t1)∩χ(t3)⊆χ(t2) (“connectivity”).
       </list-item>
      </list>
      <paragraph label="Lemma 8.27">
       We will use the following basic properties of treewidth. (Folklore, e.g.,[132].) Let G be a graph and{a mathematical formula}C1,…,Clits connected components, then{a mathematical formula}tw(G)=max⁡{tw(Cj):1≤i≤l}.
      </paragraph>
      <paragraph label="Lemma 8.28">
       (Folklore, e.g.,[6].) Let G be a graph. If G has a feedback vertex set size at most k, then{a mathematical formula}tw(G)≤k+1.
      </paragraph>
      <paragraph>
       Treewidth can be applied to programs by means of various graph representations.
      </paragraph>
      <paragraph label="Definition 8.29">
       (See Jakl et al. [90].) Let P be a normal program. The incidence graph{a mathematical formula}IP of P is the bipartite graph which has as vertices the atoms and rules of P and where a rule and an atom are joined by an edge if and only if the atom occurs in the rule. Then {a mathematical formula}inctw(P):=tw(IP). The parameter {a mathematical formula}inctw(P) is called the incidence treewidth of P.
      </paragraph>
      <paragraph>
       Fig. 8 illustrates the incidence graph {a mathematical formula}IP of the program P of Example 2.1.
      </paragraph>
      <paragraph label="Proposition 8.30">
       (See Jakl et al.[90].) For each{a mathematical formula}L∈AspFull∖{Enum},{a mathematical formula}L[inctw]N∈FPTand for{a mathematical formula}Enum[inctw]Nthe solutions can be enumerated with fixed-parameter linear delay between any two consecutive solutions.
      </paragraph>
      <paragraph label="Observation 8.31">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider the programs{a mathematical formula}P32nand{a mathematical formula}P51n. We observe that incidence graph of{a mathematical formula}P32nconsists of the cycles{a mathematical formula}a,ri,bi,r2ifor{a mathematical formula}1≤i≤nand the incidence graph of{a mathematical formula}P51nconsists of the cycles{a mathematical formula}ai,ri,bi,r2ifor{a mathematical formula}1≤i≤n. According toLemma 8.28, a cycle has treewidth at most 2 and according toLemma 8.27, we have{a mathematical formula}inctw(P32n)≤2and{a mathematical formula}inctw(P51n)≤2.
       </list-item>
       <list-item label="2.">
        Consider the programs{a mathematical formula}P6nand{a mathematical formula}P7n. Its incidence graph contains a clique on n vertices. Thus, by definition{a mathematical formula}inctw(P6n)≥n−1and{a mathematical formula}inctw(P7n)≥n−1.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P8m,n. The incidence graph consists of a tree on the vertices{a mathematical formula}r0,b,a1,…,amand a cycle{a mathematical formula}r1,c1,…,rn,cn,rn+1,cn+1,rn+2. By definition a tree has treewidth 1, according toLemma 8.28, a cycle has treewidth at most 2, and according toLemma 8.27, we obtain{a mathematical formula}inctw(P8m,n)≤2.
       </list-item>
      </list>
      <paragraph>
       The following observation states why we cannot apply our lifting theorem and extend the parameter treewidth from normal to disjunctive programs.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}Enum[inctw]N∉FPT.Consider the program {a mathematical formula}P51n where {a mathematical formula}inctw(P51n)≤2. Let {a mathematical formula}M⊆at(P) such that either {a mathematical formula}ai∈M or {a mathematical formula}bi∈M. According to the definitions, we obtain the GL-reduct {a mathematical formula}PM={ai:ai∈M}∪{bi:bi∈M}. Since M is a minimal model of {a mathematical formula}PM, M is also an answer set of P. Thus, the program P has {a mathematical formula}2n many answer sets. Consequently, enumerating the answer sets of P takes time {a mathematical formula}Ω(2n).  □
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}C∈{Horn}∪Acycand{a mathematical formula}p∈{dbC,#neg,#non-Horn,lstr,wfw}, then p and inctw are incomparable.We observe incomparability from the programs {a mathematical formula}P51n and {a mathematical formula}P6n where {a mathematical formula}p(P51n)≥n and {a mathematical formula}inctw(P51n)=2; and {a mathematical formula}p(P6n)≤1 and {a mathematical formula}inctw(P6n)≥n−1 by Observation 8.6, Observation 8.10, Observation 8.16, Observation 8.23, Observation 8.31.  □
      </paragraph>
     </section>
     <section label="8.5">
      <section-title>
       Dependency treewidth
      </section-title>
      <paragraph>
       One might ask whether it makes sense to consider restrictions on the treewidth of the dependency graph. In this section we show that the dependency treewidth strictly dominates the incidence treewidth and backdoors with respect to the target class {a mathematical formula}no-C, but unfortunately parameterizing the main ASP problems by the dependency treewidth does not yield fixed-parameter tractability.
      </paragraph>
      <paragraph label="Definition 8.34">
       Let P be a program, then {a mathematical formula}deptw(P)=tw(UP). We call {a mathematical formula}deptw(P) the dependency treewidth of P.
      </paragraph>
      <paragraph label="Observation 8.35">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider programs{a mathematical formula}P32nand{a mathematical formula}P6nwhere the dependency graph is a tree. Thus,{a mathematical formula}deptw(P32n)=deptw(P6n)=1.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P51n. We observe that its dependency graph consists of n disjoint cycles{a mathematical formula}bi,vbi,ai,ai,vai,bifor{a mathematical formula}1≤i≤n. According toLemma 8.28, a cycle has treewidth at most 2 and according toLemma 8.27, we obtain{a mathematical formula}deptw(P51n)≤2.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P7n. Its dependency graph contains a clique on n vertices as a subgraph. Hence{a mathematical formula}deptw(P7n)≥n−1.
       </list-item>
      </list>
      <paragraph label="Proof">
       deptw strictly dominates inctw and{a mathematical formula}dbno-C. Let{a mathematical formula}C∈{Horn}∪Acyc∖{no-C,no-EC}and{a mathematical formula}p∈{dbC,#neg,#non-Horn,lstr,wfw}, then p and deptw are incomparable.Let P be a normal program, and {a mathematical formula}IP its incidence graph. Let {a mathematical formula}(T,χ) be an arbitrary tree decomposition of {a mathematical formula}IP. We create a tree decomposition {a mathematical formula}(T,χ′) for {a mathematical formula}UP as follows: For every {a mathematical formula}r∈P let {a mathematical formula}vr be the corresponding vertex in {a mathematical formula}IP. We replace the occurrence of a {a mathematical formula}vr∈χ(t) by {a mathematical formula}H(r) for all nodes {a mathematical formula}t∈V(T). Then the pair {a mathematical formula}(T,χ′) satisfies Conditions 1 and 2 of a tree decomposition of {a mathematical formula}UP. Since all edges of {a mathematical formula}IP are covered in {a mathematical formula}(T,χ) for every {a mathematical formula}r∈P there is a {a mathematical formula}t∈V(T) such that {a mathematical formula}vr∈χ(T) and {a mathematical formula}h∈χ(T) where {a mathematical formula}H(r)={h}. Because all {a mathematical formula}vr are connected in the bags of the tree decomposition {a mathematical formula}(T,χ) and all corresponding elements h are connected in {a mathematical formula}(T,χ), Condition 3 holds for {a mathematical formula}(T,χ′). Thus, {a mathematical formula}(T,χ′) is a tree decomposition of the dependency graph {a mathematical formula}UP. Since the width of {a mathematical formula}(T,χ′) is less or equal to the width of {a mathematical formula}(T,χ) it follows {a mathematical formula}tw(UP)≤tw(IP) for a normal program P. To show that deptw strictly dominates inctw, consider the program {a mathematical formula}P6n where {a mathematical formula}deptw(P6n)≤1 and {a mathematical formula}inctw(P6n)≥n. Hence {a mathematical formula}deptw≺inctw.Let P be a normal program and X a deletion {a mathematical formula}no-C-backdoor of P. Thus, X is a feedback vertex set of the dependency graph {a mathematical formula}UP. According to Lemma 8.28, {a mathematical formula}tw(UP)≤k+1. Hence {a mathematical formula}deptw⪯dbno-C. To show that deptw strictly dominates {a mathematical formula}dbno-C consider the program {a mathematical formula}P51n where {a mathematical formula}deptw(P51n)≤2 and {a mathematical formula}dbno-C(P51n)≥n. Consequently, {a mathematical formula}deptw≺dbno-C and the proposition sustains.To show the last statement, consider again the programs {a mathematical formula}P51n and {a mathematical formula}P7n where {a mathematical formula}deptw(P51n)≤2 and {a mathematical formula}p(P51n)≥n; and {a mathematical formula}deptw(P7n)≥n−1 and {a mathematical formula}p(P7n)=0 by Observation 8.6, Observation 8.16, Observation 8.23, Observation 8.35.  □
      </paragraph>
      <paragraph label="Proposition 8.37">
       For each{a mathematical formula}L∈AspReason,{a mathematical formula}LNis NP-hard, even for programs that have dependency treewidth 2.
      </paragraph>
      <paragraph label="Proof">
       First consider the problem Consistency. From a 3-CNF formula F with k variables we construct a program P as follows: Among the atoms of our program P will be two atoms {a mathematical formula}ax and {a mathematical formula}ax¯ for each variable {a mathematical formula}x∈var(F) and a new atom f. We add the rules {a mathematical formula}ax¯←¬ax and {a mathematical formula}ax←¬ax¯ for each variable {a mathematical formula}x∈var(F). For each clause {a mathematical formula}{l1,l2,l3}∈F we add the rule {a mathematical formula}f←h(l1),h(l2),h(l3),¬f where {a mathematical formula}h(¬x)=ax and {a mathematical formula}h(x)=ax¯. Now it is easy to see that the formula F is satisfiable if and only if the program P has an answer set. Let {a mathematical formula}UP be the undirected dependency graph of P. We construct the following tree decomposition {a mathematical formula}(T,χ) for {a mathematical formula}UP: the tree T consists of the node {a mathematical formula}tf and for each {a mathematical formula}x∈var(F) of the nodes {a mathematical formula}tfx, {a mathematical formula}txx¯, and {a mathematical formula}tx¯x along with the edges {a mathematical formula}tftfx, {a mathematical formula}tfxtxx¯, and {a mathematical formula}txx¯tx¯x. We label the nodes by {a mathematical formula}χ(tf):={f,vf} and for each {a mathematical formula}x∈var(F) by {a mathematical formula}χ(tfx):={ax,ax¯,f}, {a mathematical formula}χ(txx¯):={ax,ax¯,vaxa¯x}, and {a mathematical formula}χ(tx¯x):={ax,ax¯,va¯xax}. We observe that the pair {a mathematical formula}(T,χ) satisfies Condition 1. The rules {a mathematical formula}ax¯←¬ax and {a mathematical formula}ax←¬ax¯ yield the edges {a mathematical formula}axvaxa¯x, {a mathematical formula}vaxa¯xa¯x, {a mathematical formula}axva¯xax, and {a mathematical formula}va¯xaxa¯x in {a mathematical formula}UP which are all “covered” by {a mathematical formula}χ(txx¯) and {a mathematical formula}χ(tx¯x). The rule {a mathematical formula}f←h(l1),h(l2),h(l3),¬f yields the edge {a mathematical formula}fvf which is covered by {a mathematical formula}χ(tf) and yields the edges {a mathematical formula}fax or {a mathematical formula}fax¯ which are covered by {a mathematical formula}χ(tfx). Thus, Condition 2 is satisfied. We easily observe that Condition 3 also holds for the pair {a mathematical formula}(T,χ). Hence {a mathematical formula}(T,χ) is a tree decomposition of the dependency graph {a mathematical formula}UP. Since {a mathematical formula}max⁡{|χ(t)|−1:t∈V(T)}=2, the tree decomposition {a mathematical formula}(T,χ) is of width 2 and {a mathematical formula}deptw(P)=2. Hence the problem {a mathematical formula}Consistency[deptw]N is NP-hard, even for programs that have dependency treewidth 2. We observe hardness for the problems Brave Reasoning and Skeptical Reasoning by the very same argument as in the proof of Theorem 6.4 and the proposition holds.  □
      </paragraph>
     </section>
     <section label="8.6">
      <section-title>
       Interaction treewidth
      </section-title>
      <paragraph>
       In this section we consider two parameters investigated by Ben-Eliyahu and Dechter [3]: the interaction treewidth introduced under the term “clique width”,{sup:4} and the feedback width of the interaction graph introduced under the term “cycle-cutset size”. The interaction graph represents “interactions” between head atoms and related body atoms (similar to the Gaifman graph). The interaction treewidth measures in a certain sense the tree-likeness of the interaction graph and the feedback width the distance of the interaction graph from being acyclic. Both parameters are considered together with the length of the longest cycle in the positive dependency digraph (which states dependencies between atoms in the head and atoms in the positive body).
      </paragraph>
      <paragraph label="Definition 8.38">
       (See Ben-Eliyahu and Dechter [3].) Let P be a normal program. The interaction graph is the graph {a mathematical formula}AP which has as vertices the atoms of P and an edge xy between any two distinct atoms x and y for which there are rules {a mathematical formula}r,r′∈P such that {a mathematical formula}x∈at(r), {a mathematical formula}y∈at(r′), and {a mathematical formula}H(r)∩H(r′)≠∅.{sup:5}
      </paragraph>
      <paragraph label="Definition 8.39">
       (See Kanchanasut and Stuckey [99], Ben-Eliyahu and Dechter [3].) Let P be a program. The positive dependency digraph{a mathematical formula}DP+ of P has as vertices the atoms {a mathematical formula}at(P) and a directed edge {a mathematical formula}(x,y) between any two atoms {a mathematical formula}x,y∈at(P) for which there is a rule {a mathematical formula}r∈P with {a mathematical formula}x∈H(r) and {a mathematical formula}y∈B+(r).{sup:6}
      </paragraph>
      <paragraph>
       Let {a mathematical formula}G=(V,E) be a graph and {a mathematical formula}c=(v1,…,vl) a cycle of length l in G. A chord of c is an edge {a mathematical formula}vivj∈E where {a mathematical formula}vi and {a mathematical formula}vj are not connected by an edge in c (non-consecutive vertices). G is chordal (triangulated) if every cycle in G of length at least 4 has a chord.
      </paragraph>
      <paragraph label="Definition 8.40">
       (See Ben-Eliyahu and Dechter [3].) Let G be a digraph and {a mathematical formula}G′ a graph. Then{a mathematical formula}{a mathematical formula} lc is the length of the longest cycle. cs is the clique size.{sup:7}Let P be a normal program, {a mathematical formula}AP its interaction graph, and {a mathematical formula}DP+ its positive dependency digraph. Then{a mathematical formula}{a mathematical formula}{a mathematical formula}cluster(P) is called the size of the tree clustering. {a mathematical formula}cyclecut(P) is called the size of the cycle cutset decomposition.
      </paragraph>
      <paragraph>
       In fact the definition of {a mathematical formula}cs(G) is related to the treewidth:
      </paragraph>
      <paragraph label="Proposition 8.43">
       (See Robertson and Seymour[132].) Let G be a graph. Then{a mathematical formula}tw(G)=cs(G)+1.Let P be a normal program,{a mathematical formula}APits interaction graph, and{a mathematical formula}DP+its dependency digraph. Then{a mathematical formula}(See Ben-Eliyahu and Dechter[3].) For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[cluster]N∈FPTand{a mathematical formula}L[cyclecut]N∈FPT.
      </paragraph>
      <paragraph label="Observation 8.44">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider programs{a mathematical formula}P51nand{a mathematical formula}P53nand let{a mathematical formula}P∈{P51n,P53n}. The interaction graph{a mathematical formula}Apcontains n disjoint paths{a mathematical formula}ai,bi, for{a mathematical formula}1≤i≤m. Hence{a mathematical formula}APcontains no cycles and{a mathematical formula}fw(AP)=0and according toLemma 8.28, we obtain{a mathematical formula}tw(AP)≤1. Moreover, the positive dependency digraph{a mathematical formula}DP+contains no edges, n disjoint cycles of length exactly 2 respectively. Thus,{a mathematical formula}lc(DP+)=2. Consequently,{a mathematical formula}cluster(P51n)≤1and{a mathematical formula}cyclecut(P51n)≤1; and{a mathematical formula}cluster(P53n)≤1and{a mathematical formula}cyclecut(P53n)≤1.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P8m,nand let{a mathematical formula}P=P8m,n. The interaction graph{a mathematical formula}APcontains a clique on m vertices and thus{a mathematical formula}tw(AP)≥m−1. According toLemma 8.41, we obtain{a mathematical formula}cs(AP)≥m−2. According toLemma 8.28, we have{a mathematical formula}fw(AP)≥m−2. Moreover, the positive dependency digraph{a mathematical formula}DP+contains the cycle{a mathematical formula}c1,c2,…,cn,cn+1. Thus,{a mathematical formula}lc(DP+)=n. Consequently,{a mathematical formula}cluster(P8m,n)≥(m−2)⋅log⁡nand{a mathematical formula}cyclecut(P8m,n)≥(m−2)⋅log⁡n.
       </list-item>
      </list>
      <paragraph label="Proof">
       cluster strictly dominates cyclecut.Let P be a normal program and {a mathematical formula}AP its interaction graph. According to Lemma 8.28, we obtain {a mathematical formula}tw(AP)≤fw(AP)+1. Hence {a mathematical formula}cluster(P)≺cyclecut(P).  □
      </paragraph>
      <paragraph label="Proof">
       inctw strictly dominates cluster. If{a mathematical formula}C∈{Horn}∪Acycand{a mathematical formula}p∈{dbC,#neg,#non-Horn,lstr,wfw}, then p and cluster are incomparable; and p and cyclecut are incomparable.We first show that inctw dominates cluster. Let P be a normal program, {a mathematical formula}IP its incidence graph, and {a mathematical formula}AP its interaction graph. Let {a mathematical formula}(T,χ) be an arbitrary tree decomposition of {a mathematical formula}AP. We create a tree decomposition {a mathematical formula}(T,χ′) for {a mathematical formula}IP as follows: For every {a mathematical formula}r∈P let {a mathematical formula}vr be the corresponding vertex in {a mathematical formula}IP. By definition for every {a mathematical formula}r∈P there is a bag {a mathematical formula}χ(t) where {a mathematical formula}t∈V(T) such that {a mathematical formula}at(r)⊂χ(t). We set {a mathematical formula}χ′(t)=χ(t)∪{vr}. Then the pair {a mathematical formula}(T,χ′) clearly satisfies Conditions 1 and 2 of a tree decomposition of {a mathematical formula}IP by definition. Since every {a mathematical formula}vr occurs in exactly one bag Condition 3 holds for {a mathematical formula}(T,χ′). Thus, {a mathematical formula}(T,χ′) is a tree decomposition of the interaction graph {a mathematical formula}AP. Since the width of {a mathematical formula}(T,χ′) is less or equal to the width of {a mathematical formula}(T,χ) plus one it follows {a mathematical formula}tw(IP)≤tw(AP)+1. To show that inctw strictly dominates cluster, consider the program {a mathematical formula}P8m,n where {a mathematical formula}inctw(P8m,n)≤2 and {a mathematical formula}cluster(P8m,n)=(m−2)log⁡n by Observation 8.31, Observation 8.44. Hence {a mathematical formula}inctw≺cluster.Let {a mathematical formula}p∈{dbC, {a mathematical formula}#neg, {a mathematical formula}#non-Horn, lstr, wfw} and {a mathematical formula}C∈{Horn}∪Acyc. We show the incomparability of the parameter p and cyclecut. In fact we show something stronger, there are programs P where p is of constant size, but both {a mathematical formula}tw(DP+) and {a mathematical formula}fw(DP+), respectively, and {a mathematical formula}lc(IP) can be arbitrarily large, and there are programs where the converse sustains. Therefore we consider the programs {a mathematical formula}P51n and {a mathematical formula}P8m,n where {a mathematical formula}p(P51n)≥n and {a mathematical formula}cluster(P51n)≤1 and {a mathematical formula}cyclecut(P51n)≤1; and {a mathematical formula}p(P8m,n)≤1 and {a mathematical formula}cyclecut(P8m,n)≥(m−2)⋅log⁡n and {a mathematical formula}cluster(P8m,n)≥(m−2)⋅log⁡n by Observation 8.6, Observation 8.10, Observation 8.16, Observation 8.23, Observation 8.44. Consequently, the second statement holds.  □
      </paragraph>
     </section>
     <section label="8.7">
      <section-title>
       Number of bad even cycles
      </section-title>
      <paragraph>
       Lin and Zhao [110] have considered the number of directed bad even cycles of a given program as a parameter which measures in a certain sense the distance of a program from being acyclic with respect to bad even cycles. This parameter relates to our notion of deletion {a mathematical formula}no-DEC-backdoors and deletion {a mathematical formula}no-DBEC-backdoors.
      </paragraph>
      <paragraph label="Definition 8.47">
       (See Lin and Zhao [110].) Let P be a normal program. Then{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 8.48">
       For each{a mathematical formula}L∈AspFull,{a mathematical formula}L[#badEvenCycles]N∈FPT.
      </paragraph>
      <paragraph label="Observation 8.49">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider program{a mathematical formula}P4nwhich contains no directed bad even cycle. Hence{a mathematical formula}#badEvenCycles(P4n)=0.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P51nwhich contains n disjoint directed bad even cycles. Thus,{a mathematical formula}#badEvenCycles(P51n)=n.
       </list-item>
       <list-item label="3.">
        Consider programs{a mathematical formula}P52n,{a mathematical formula}P7n, and{a mathematical formula}P8m,nwhich contain no directed bad even cycle. Consequently we obtain{a mathematical formula}#badEvenCycles(P52n)=#badEvenCycles(P7n)=#badEvenCycles(P8m,n)=0.
       </list-item>
       <list-item label="4.">
        Consider program{a mathematical formula}P9nwhich contains the directed bad even cycles{a mathematical formula}a1,a2,a3,bifor{a mathematical formula}1≤i≤n. Since there are n of those directed bad even cycles we obtain{a mathematical formula}#badEvenCycles(P9n)=n.
       </list-item>
      </list>
      <paragraph label="Proof">
       {a mathematical formula}dbno-DBECstrictly dominates{a mathematical formula}#badEvenCycles. Moreover,{a mathematical formula}dbCand{a mathematical formula}#badEvenCyclesare incomparable for the remaining target classes{a mathematical formula}C∈Acyc∖{no-DBEC}∪{Horn}. If{a mathematical formula}p∈{#neg,{a mathematical formula}#non-Horn, lstr, wfw, inctw, deptw, cluster, cyclecut}, then p and{a mathematical formula}#badEvenCyclesare incomparable.To see that {a mathematical formula}dbno-DBEC strictly dominates {a mathematical formula}#badEvenCycles. Let P be a normal program. If P has at most k directed bad even cycles, we can construct a deletion {a mathematical formula}no-DBEC-backdoor X for P by taking one element from each directed bad even cycle into X. Thus, {a mathematical formula}dbno-DBEC(P)≤#badEvenCycles(P). If a program P has a deletion {a mathematical formula}no-DBEC-backdoor of size 1, it can have arbitrarily many even cycles that run through the atom in the backdoor, e.g. program {a mathematical formula}P9n where {a mathematical formula}dbno-DBEC(P9n)≤1 and {a mathematical formula}#badEvenCycles(P9n)=n by Observation 8.6, Observation 8.49. It follows that {a mathematical formula}dbno-DBEC≺#badEvenCycles and the proposition holds.To show the second statement, consider the programs {a mathematical formula}P4n, {a mathematical formula}P52n, and {a mathematical formula}P9n where {a mathematical formula}dbC(P9n)=1 for {a mathematical formula}C∈Acyc∪{Horn} and {a mathematical formula}#badEvenCycles(P9n)=n; conversely {a mathematical formula}dbC(P4n)≥n for {a mathematical formula}C∈{Horn,no-C,no-BC,no-DC,no-DC2,no-EC,no-DEC,no-BEC}, {a mathematical formula}dbno-DBC(P52n)≥n, and {a mathematical formula}#badEvenCycles(P4n)=#badEvenCycles(P52n)=0. Hence {a mathematical formula}dbC⋈#badEvenCycles for {a mathematical formula}C∈Acyc∖{no-DBEC}∪{Horn} by Observation 8.6, Observation 8.49.To show the third statement, consider the programs {a mathematical formula}P51n, {a mathematical formula}P52n, {a mathematical formula}P7n, and {a mathematical formula}P8m,n, {a mathematical formula}P9n where {a mathematical formula}inctw(P7n)≥n−1 and {a mathematical formula}deptw(P7n)≥n−1, {a mathematical formula}p(P52n)≥n for {a mathematical formula}p∈{#neg, {a mathematical formula}#non-Horn, lstr, wfw}, {a mathematical formula}cyclecut(P8m,n)≥(m−2)log⁡n, {a mathematical formula}cluster(P8m,n)≥(m−2)log⁡n, and {a mathematical formula}#badEvenCycles(P7n)=#badEvenCycles(P8m,n)=#badEvenCycles(P52n)=0; conversely {a mathematical formula}p(P51n)≤2 for {a mathematical formula}p∈{inctw, deptw, cluster, cyclecut}, {a mathematical formula}p(P9n)≤2 for {a mathematical formula}p∈{#neg, {a mathematical formula}#non-Horn, lstr, wfw}, and {a mathematical formula}#badEvenCycles(P51n)=#badEvenCycles(P9n)=n by Observation 8.6, Observation 8.10, Observation 8.16, Observation 8.23, Observation 8.31, Observation 8.35, Observation 8.44, Observation 8.49. Hence {a mathematical formula}p⋈#badEvenCycles for {a mathematical formula}p∈{#neg, {a mathematical formula}#non-Horn, lstr, wfw, inctw, deptw, cluster, cyclecut}.  □
      </paragraph>
     </section>
     <section label="8.8">
      <section-title>
       Number of positive cycles (loop formulas)
      </section-title>
      <paragraph>
       Fages [46], Lin and Zhao [109], and Lee and Lifschitz [105] have introduced compilations of normal programs and disjunctive programs to SAT, respectively. Fages [46] has established the notion of being acyclic with respect to the positive dependency digraph of a given program, so-called tight programs. Lin and Zhao [109] have extended this to non-tight programs by adding additional formulas that prevent cycles in the positive dependency graph, so-called loop formulas. We would like to mention that loop formulas are used in some ASP solvers, e.g., Clasp3 [37] and Cmodels3 [108]. The concept of loop formulas is based on the observation that cycles in the positive dependency digraph yield additional models in the SAT formula which are in fact not answer sets and can be eliminated by forbidding a “circular justification” of atoms without having a “justification from outside”. The number of loop formulas depends on the number of cycles of the positive dependency digraph and yields the following parameter that measures in a certain sense the distance of a program from being tight.
      </paragraph>
      <paragraph label="Definition 8.51">
       (See Fages [46].) Let P be a normal program and {a mathematical formula}DP+ its positive dependency digraph. Then{a mathematical formula} The program P is called tight if {a mathematical formula}#posCycles=0.{sup:8}
      </paragraph>
      <paragraph>
       The parameter has been generalized to disjunctive programs by Lee and Lifschitz [105].
      </paragraph>
      <paragraph label="Proposition 8.52">
       (See Fages[46].) For{a mathematical formula}L∈AspReason,{a mathematical formula}L[#posCycles]Nis NP-hard or{a mathematical formula}co-NP-hard, even for tight programs.
      </paragraph>
      <paragraph label="Observation 8.53">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider programs{a mathematical formula}P32nand{a mathematical formula}P53nwhere the positive dependency digraphs contain n directed cycles. Hence{a mathematical formula}#posCycles(P32n)=#posCycles(P53n)=n.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P51nand{a mathematical formula}P7nwhere the positive dependency digraphs contain no cycle. Hence{a mathematical formula}#posCycles(P51n)=#posCycles(P7n)=0.
       </list-item>
       <list-item label="3.">
        Consider program{a mathematical formula}P8m,n. Its positive dependency digraph contains only the cycle{a mathematical formula}c1,c2,…,cn,cn+1; thus,{a mathematical formula}#posCycles(P8n)=1.
       </list-item>
      </list>
      <paragraph label="Proof">
       If{a mathematical formula}C∈{Horn}∪Acycand{a mathematical formula}p∈{dbC,#neg,#non-Horn,lstr,wfw,inctw,deptw,cluster,cyclecut,#badEvenCycles}, then p and{a mathematical formula}#posCyclesare incomparable.We observe incomparability from the programs {a mathematical formula}P32n, {a mathematical formula}P51n, {a mathematical formula}P53n, {a mathematical formula}P7n, and {a mathematical formula}P8n,m. We have {a mathematical formula}p(P51n)≥n for {a mathematical formula}p∈{dbC{a mathematical formula}#neg, {a mathematical formula}#non-Horn, lstr, wfw, {a mathematical formula}#badEvenCycles}, {a mathematical formula}inctw(P7n)≥n−1, {a mathematical formula}deptw(P7n)≥n−1, {a mathematical formula}cyclecut(P8n,m)≥(m−2)⋅log⁡n, {a mathematical formula}cluster(P8n,m)≥(m−2)⋅log⁡n, and {a mathematical formula}#posCycles(P51n)=#posCycles(P7n)=0 as well as {a mathematical formula}#posCycles(P8m,n)=1; conversely for {a mathematical formula}p∈{dbC, {a mathematical formula}#neg, {a mathematical formula}#non-Horn, lstr, wfw, inctw, deptw} we have {a mathematical formula}p(P32n)≤2, for {a mathematical formula}p∈{cluster,cyclecut} we have {a mathematical formula}p(P53n)≤2 and {a mathematical formula}#posCycles(P32n)=#posCycles(P53n)=n by Observation 8.6, Observation 8.10, Observation 8.16, Observation 8.23, Observation 8.31, Observation 8.35, Observation 8.44, Observation 8.49, Observation 8.53. Consequently, the proposition holds.  □
      </paragraph>
     </section>
     <section label="8.9">
      <section-title>
       Head-cycles
      </section-title>
      <paragraph>
       Ben-Eliyahu and Dechter [3] have considered programs that do not contain certain cycles in their positive dependency digraph, so-called head-cycle-free programs. Head-cycle-free programs can be compiled into normal programs in polynomial time. We would like to mention that connections to head-cycle-free programs are exploited in the implementation of ASP solvers (see e.g., [106]). In the following we consider the number of head cycles as a parameter which then measures in a certain sense the distance of a program from being head-cycle-free.
      </paragraph>
      <paragraph label="Definition 8.55">
       (See Ben-Eliyahu and Dechter [3].) Let P be a program and {a mathematical formula}DP+ its positive dependency digraph. A head-cycle of {a mathematical formula}DP+ is an {a mathematical formula}{x,y}-cycle{sup:9} where {a mathematical formula}x,y∈H(r) for some rule {a mathematical formula}r∈P. The program P is head-cycle-free if {a mathematical formula}DP+ contains no head-cycle.
      </paragraph>
      <paragraph label="Definition 8.56">
       One might consider the number of head-cycles as a parameter to tractability. Let P be a program and {a mathematical formula}DP+ its positive dependency digraph. Then{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 8.57">
       But as the following proposition states that the ASP-reasoning problems are already NP-complete for head-cycle-free programs. (See Ben-Eliyahu and Dechter[3].) Each{a mathematical formula}L∈AspReasonis NP-hard or{a mathematical formula}co-NP-hard, even for head-cycle-free programs.
      </paragraph>
      <paragraph label="Observation 8.58">
       We make the following observations about programs fromExample 8.1.
      </paragraph>
      <list>
       <list-item label="1.">
        Consider program{a mathematical formula}P51n. Since the positive dependency digraph of{a mathematical formula}P51ncontains no cycle,{a mathematical formula}#headCycles(P51n)=0.
       </list-item>
       <list-item label="2.">
        Consider program{a mathematical formula}P11n. The positive dependency digraph of{a mathematical formula}P11ncontains the head cycles{a mathematical formula}aibcfor{a mathematical formula}1≤i≤n. Thus,{a mathematical formula}#headCycles(P11n)=n.
       </list-item>
      </list>
      <paragraph>
       Even though the parameter {a mathematical formula}#headCycles does not yield tractability for the ASP-reasoning problems we are interested in the relationship between our lifted parameters and the parameter {a mathematical formula}#headCycles. We will first restrict the input programs to normal programs in Observation 8.59 and then consider disjunctive programs Observation 8.60.
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}C∈{Horn}∪Acycand{a mathematical formula}p∈{dbC,#neg,#non-Horn,lstr,wfw,inctw,deptw,cluster,cyclecut,#badEvenCycles,#posCycles}, then{a mathematical formula}#headCyclesstrictly dominates{a mathematical formula}p↓.By definition every normal program is head-cycle-free, hence {a mathematical formula}#headCycles strictly dominates p.  □
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}C∈{Horn}∪Acyc, then{a mathematical formula}dbCand{a mathematical formula}#headCyclesare incomparable. Moreover, if{a mathematical formula}p∈{#neg,#non-Horn,lstr,wfw}, then{a mathematical formula}p↑and{a mathematical formula}#headCyclesare incomparable.To see that the parameters are incomparable consider the programs {a mathematical formula}P51n and {a mathematical formula}P11n where {a mathematical formula}dbC≥n as well as {a mathematical formula}p(P51n)≥n and {a mathematical formula}#headCycles(P51n)=0; and {a mathematical formula}p(P11n)=1 and {a mathematical formula}#headCycles(P11n)=n by Observation 8.6, Observation 8.10, Observation 8.16, Observation 8.23, Observation 8.58.  □
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>