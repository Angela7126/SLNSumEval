<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Design and results of the Fifth Answer Set Programming Competition.
   </title>
   <abstract>
    Answer Set Programming (ASP) is a well-established paradigm of declarative programming that has been developed in the field of logic programming and non-monotonic reasoning. Advances in ASP solving technology are customarily assessed in competition events, as it happens for other closely related problem solving areas such as Boolean Satisfiability, Satisfiability Modulo Theories, Quantified Boolean Formulas, Planning, etc. This paper reports about the fifth edition of the ASP Competition by covering all aspects of the event, ranging from the new design of the competition to an in-depth analysis of the results. The paper comprises also additional analyses that were conceived for measuring the progress of the state of the art, as well as for studying aspects orthogonal to solving technology, such as the effects of modeling. A detailed picture of the progress of the state of the art in ASP solving is drawn, and the ASP Competition is located in the spectrum of related events.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Answer Set Programming (ASP) [8], [13], [33], [31], [34], [47], [48], [49], [61], [65], [71] is a well-established declarative programming approach to knowledge representation and reasoning, proposed in the area of logic programming and non-monotonic reasoning. The idea of ASP is to represent a given problem by means of a logic program whose stable models or answer sets correspond to solutions, and then to use an ASP solver for computing solutions. The availability of high-performance implementations, e.g. [3], [26], [43], [45], [52], [57], [60], [62], [63], [66], [82], made ASP a powerful tool for developing advanced applications. Nowadays, ASP has been employed in many research areas ranging from Artificial Intelligence to Databases and Bioinformatics; moreover, it has already been used in industrial systems, e.g. [72], [78], [91].
     </paragraph>
     <paragraph>
      The advances in ASP solving technology are customarily assessed in competition events [14], [46], [27], [19], [2], as it happens for other closely related problem solving areas such as Boolean Satisfiability (SAT), Satisfiability Modulo Theories (SMT), Quantified Boolean Formulas (QBF), and Planning, to mention a few. ASP Competitions are (usually) biennial events; however, the fifth edition departed from tradition and took place in 2014, affiliated with the 30th International Conference on Logic Programming (ICLP 2014), in order to join the FLoC Olympic Games at the Vienna Summer of Logic.
     </paragraph>
     <paragraph>
      The Fifth ASP Competition [17] featured a revised setup with novelties involving every aspect of the design from the definition of tracks to the scoring scheme. The new design aims at lowering the efforts of participating in the event, and further pushes the adoption of the recent standard language ASP-Core-2[15] introduced in 2013. Indeed, in 2013, the ASP-Core-2 language was not fully supported yet by most implementations, and/or the participants did not have enough time to integrate new language features in a completely satisfactory way. Taking these considerations into account, the Fifth ASP Competition was based on the System track of the 2013 edition,{sup:2} reusing the available benchmarks but also adding novel problem encodings.
     </paragraph>
     <paragraph>
      The benchmark domains were classified by the language features used in encodings (e.g. choice rules, aggregates, presence of queries), rather than by problem “complexity” considered in past events [18]. The competition tracks were devised in accordance with the new benchmark classification and by carefully considering the increasing effort needed for the implementation of specific language features. This was intended not only to widen participation, but also to properly analyze benchmarks and solvers' performance from the perspective of the language. Concerning participants, competitors in the 2013 edition as well as newcomers were invited to participate.
     </paragraph>
     <paragraph>
      This paper provides a comprehensive report of the Fifth ASP Competition along with an in-depth analysis of results, originally published on the competition homepage [17]. For one, novel problem encodings were devised to furnish an extended benchmark collection and to assess the impact of modeling on the ASP solving process. For another, the most successful systems submitted in 2013 were run against new versions to evaluate the progress. Moreover, the competition setup is compared to those in other problem solving areas. As a result, this paper draws a detailed picture of the state of the art in ASP solving, and locates the ASP Competition in the spectrum of related events.
     </paragraph>
     <paragraph>
      The remainder of this paper is structured as follows. Section 2 provides the reader with proper preliminaries about the ASP-Core-2 language. The competition setup is discussed in Section 3, while Sections 4 and 5 present the domains and ASP systems, respectively, taking part in the competition. Section 6 announces the competition winners and analyzes the results. In Section 7, the competition design is compared to those of previous editions as well as related events. Section 8 concludes the paper, also pointing out some recommendations for future editions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      The ASP-Core-2 language: syntax and semantics
     </section-title>
     <paragraph>
      The input language for competition benchmarks, represented in terms of a uniform (first-order) problem encoding along with (ground) facts specifying a problem instance, follows the ASP-Core-2 standard [15]. The syntax of ASP-Core-2 includes elements from classical first-order logic, i.e. terms, atoms, and connectives, as well as extensions like integer arithmetic, aggregates, weak constraints, and queries. These constituents provide a conceptually simple yet powerful modeling language for expressing computational problems with diverse features and complexity. For example, a data representation of the directed graph with arc costs displayed in Fig. 1(a) is shown in Fig. 1(b), where nodes, arcs, and their associated costs are specified in terms of facts over corresponding predicates. Given such instance data, the following ASP-Core-2 program encodes the well-known Traveling Salesperson Problem (TSP):{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Without going into details yet, note that the rules in (1) and (2) express that, for every node, exactly one outgoing and one incoming arc must be part of a Hamiltonian cycle, i.e. a round trip that visits each node, and the selected arcs are represented by (true) atoms over the predicate hc. Then, starting from some arbitrary yet fixed node, taken to be the lexicographically smallest one in (3), further nodes reachable via selected arcs are derived by the rule in (4). Given that a round trip must visit all nodes, the so-called integrity constraint in (5) denies isolated subcycles, indicated by a node whose corresponding atom over the predicate reach does not hold. In turn, every node must be reached from the starting node, so that the true atoms over the predicate hc provide a Hamiltonian cycle. The objective of finding a Hamiltonian cycle with minimum cost is formulated in terms of the weak constraint in (6), which penalizes any selected arc by its cost. The (unique) optimal round trip for the example graph in Fig. 1(a) includes the arcs {a mathematical formula}(1,4), {a mathematical formula}(4,3), {a mathematical formula}(3,2), and {a mathematical formula}(2,1), yielding an accumulated cost of 7. However, note that the first-order ASP-Core-2 program in (1), (2), (3), (4), (5), (6) uniformly encodes the Optimization problem TSP for any directed graph specified by facts like those in Fig. 1(b).
     </paragraph>
     <paragraph>
      In what follows, we review the syntax and semantics of ASP-Core-2 programs, laying the ground for the classification of competition benchmarks into tracks (see Section 3). As usual, terms are composed of constants, variables, and functions. Dedicated arithmetic terms have the form {a mathematical formula}−(t) or {a mathematical formula}(t⋄u) with {a mathematical formula}⋄∈{+,−,⁎,/}. Terms and {a mathematical formula}≺∈{&lt;,≤,=,≠,&gt;,≥} are used to construct three kinds of atoms:
     </paragraph>
     <list>
      <list-item label="•">
       classical atoms {a mathematical formula}p(t1,…,tn) and {a mathematical formula}¬p(t1,…,tn) for a predicate name p and terms {a mathematical formula}t1,…,tn,
      </list-item>
      <list-item label="•">
       built-in atoms {a mathematical formula}t≺u for terms t and u, and
      </list-item>
      <list-item label="•">
       aggregate atoms {a mathematical formula}#agg{e1;…;ek}≺u for {a mathematical formula}#agg∈{#count,#sum,#max,#min}, where {a mathematical formula}ei ({a mathematical formula}1≤i≤k) is an aggregate element {a mathematical formula}t1,…,tn:l1,…,lm in which {a mathematical formula}t1,…,tn are terms and {a mathematical formula}l1,…,lm are naf-literals, i.e. built-in atoms {a mathematical formula}t≺u or expressions a and nota for classical atoms a.
      </list-item>
     </list>
     <paragraph>
      Note that not stands for default negation, and literals in general include naf-literals as well as a and nota for aggregate atoms a.
     </paragraph>
     <paragraph>
      ASP-Core-2 programs consist of rules, possibly accompanied by weak constraints or a query. A rule r is of the form {a mathematical formula}a1|…|am←b1,…,bn, where {a mathematical formula}a1,…,am are classical atoms for {a mathematical formula}m≥0 and {a mathematical formula}b1,…,bn are literals for {a mathematical formula}n≥0. If {a mathematical formula}m=1 and {a mathematical formula}n=0, r is also called a fact, and r is a disjunctive rule if {a mathematical formula}m&gt;1. Moreover, choice rules have the form {a mathematical formula}{e1;…;ek}≺u←b1,…,bn, where {a mathematical formula}ei ({a mathematical formula}1≤i≤k) is a choice element {a mathematical formula}a:l1,…,lm in which a is a classical atom and {a mathematical formula}l1,…,lm are naf-literals. A weak constraint{a mathematical formula}:∼b1,…,bn[w@l,t1,…,tm] associates literals {a mathematical formula}b1,…,bn with a weight w, a level l, and additional terms {a mathematical formula}t1,…,tm for {a mathematical formula}m≥0. Finally, a? is a query for a classical atom a.
     </paragraph>
     <paragraph>
      An atom, a rule, or an ASP-Core-2 program is ground if it does not contain any variables or arithmetic terms, and an interpretation I is a consistent set of ground classical atoms, i.e. {a mathematical formula}p(t1,…,tn) and {a mathematical formula}¬p(t1,…,tn) must not jointly occur in I for any predicate name p and terms {a mathematical formula}t1,…,tn. The satisfaction relation w.r.t. I is defined inductively by
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}I⊨a for a classical atom a, if {a mathematical formula}a∈I, otherwise {a mathematical formula}I⊨nota;
      </list-item>
      <list-item label="•">
       {a mathematical formula}I⊨t≺u, if {a mathematical formula}t≺u according to the definition in [15, Section 2.3];
      </list-item>
      <list-item label="•">
       {a mathematical formula}I⊨#agg{e1;…;ek}≺u for {a mathematical formula}#agg∈{#count,#sum,#max,#min}, if {a mathematical formula}#agg(T)≺u, where {a mathematical formula}T=⋃1≤i≤k,ei=t1,…,tn:l1,…,lm{(t1,…,tn)|I⊨l1,…,I⊨lm} is the (finite) set of tuples {a mathematical formula}(t1,…,tn) for aggregate elements {a mathematical formula}t1,…,tn:l1,…,lm whose naf-literals {a mathematical formula}l1,…,lm are satisfied w.r.t. I, and
      </list-item>
      <list-item label="•">
       {a mathematical formula}I⊨{e1;…;ek}≺u, if {a mathematical formula}|⋃1≤i≤k,ei=a:l1,…,lm{a∈I|I⊨l1,…,I⊨lm}|≺u;
      </list-item>
      <list-item label="•">
       {a mathematical formula}I⊨a1|…|am for classical atoms {a mathematical formula}a1,…,am, if {a mathematical formula}{a1,…,am}∩I≠∅.
      </list-item>
     </list>
     <paragraph>
      A rule of the form {a mathematical formula}A←b1,…,bn is satisfied w.r.t. I, if {a mathematical formula}I⊨b1,…,I⊨bn implies {a mathematical formula}I⊨A. Moreover, I is a model of a ground ASP-Core-2 program P, if every rule in P is satisfied w.r.t. I. Following [37], [38] in extending the original notion [49] to aggregates, the reduct{a mathematical formula}PI of P w.r.t. I is obtained in two steps:
     </paragraph>
     <list>
      <list-item label="1.">
       Delete all rules {a mathematical formula}A←b1,…,bi,…,bn from P such that {a mathematical formula}I⊭bi.
      </list-item>
      <list-item label="2.">
       Replace remaining choice rules {a mathematical formula}{e1;…;a:l1,…,lm;…;ek}≺u←b1,…,bn by rules {a mathematical formula}a←b1,…,bn,l1,…,lm for choice elements {a mathematical formula}a:l1,…,lm such that {a mathematical formula}a∈I and {a mathematical formula}I⊨l1,…,I⊨lm.
      </list-item>
     </list>
     <paragraph>
      Then, a model I of P is an answer set of P, if I is a ⊆-minimal model of {a mathematical formula}PI. That is, all rules of P have to be satisfied w.r.t. I, and the (true) atoms in I must be “derivable” from the applicable rules in {a mathematical formula}PI. A ground query a? holds for P, if a belongs to every answer set of P. Moreover, let {a mathematical formula}PlI denote the sum of integers w over all distinct tuples {a mathematical formula}(w,t1,…,tm) such that P contains some weak constraint {a mathematical formula}:∼b1,…,bn[w@l,t1,…,tm] with {a mathematical formula}I⊨b1,…,I⊨bn. An answer set I of P is optimal, if there is no answer set J of P such that {a mathematical formula}PlJ&lt;PlI for an integer l and {a mathematical formula}Pl′J=Pl′I for all integers {a mathematical formula}l′&gt;l.
     </paragraph>
     <paragraph>
      Depending on the class of programs under consideration, verifying ⊆-minimality w.r.t. {a mathematical formula}PI can be tractable or computationally complex [32]. The syntactic property of head-cycle-freeness[10] allows for distinguishing such cases based on the positive dependency graph of a ground program P, having the atoms in P as nodes and arcs from head atoms {a mathematical formula}a1,…,am of {a mathematical formula}a1|…|am←b1,…,bn or a in {a mathematical formula}{e1;…;a:l1,…,lm;…;ek}≺u←b1,…,bn to the classical atoms among {a mathematical formula}b1,…,bn as well as {a mathematical formula}l1,…,lm. Then, P is head-cycle-free (HCF), if there is no disjunctive rule {a mathematical formula}a1|…|am←b1,…,bn in P such that two or more of the head atoms {a mathematical formula}a1,…,am share some strongly connected component in the positive dependency graph of P; otherwise, P is non-HCF. Furthermore, P is non-tight, if some strongly connected component in its positive dependency graph contains an arc, and tight otherwise [40], [35]; if P is non-HCF, it is also non-tight, but not necessarily vice versa. The check whether a model is an answer set of P is tractable for HCF programs but coNP-complete for non-HCF programs. Also note that our account of head-cycle-freeness could disregard aggregate atoms, since ASP-Core-2 restrictions on their usage (see [15]) do not permit circular (positive) dependencies through aggregates.
     </paragraph>
     <paragraph>
      The semantics of a non-ground program P, possibly including arithmetic terms, is given by the answer sets of its ground instantiation. To this end, variables in a rule or weak constraint r are distinguished into global variables, appearing outside of aggregate and choice elements in r, while the remaining variables are local. A ground instance of r is obtained in two steps:
     </paragraph>
     <list>
      <list-item label="1.">
       Apply a global substitution σ that maps the global variables in r to ground terms yielding a rule rσ without global variables.
      </list-item>
      <list-item label="2.">
       Replace any aggregate or choice element e in rσ by the collection of all aggregate or choice elements eθ obtainable by applying local substitutions θ that map the local variables in e to ground terms.
      </list-item>
     </list>
     <paragraph>
      For example, applying the global substitution {a mathematical formula}{X↦1} to the rule in (1) gives {a mathematical formula}{hc(1,Y):arc(1,Y)}=1←node(1). Mapping the local variable Y to the nodes 1, 2, 3, and 4 then leads to the ground instance {a mathematical formula}{hc(1,1):arc(1,1);hc(1,2):arc(1,2);hc(1,3):arc(1,3);hc(1,4):arc(1,4)}=1←node(1). Note that applicable substitutions σ and θ are required to be well-formed (see [15]), that is, the arithmetic evaluation of arithmetic terms that do not contain variables must be well-defined. Global substitutions σ violating this condition cannot be used to obtain rσ from a rule r, while a respective local substitution θ does not yield an instance eθ of an aggregate or choice element e.
     </paragraph>
     <paragraph>
      The ground instantiation of a program P, denoted by {a mathematical formula}grnd(P), is the collection of all ground instances of rules or weak constraints in P obtainable by applying well-formed substitutions and evaluating arithmetic terms. Then, the (optimal) answer sets of P are the (optimal) answer sets of {a mathematical formula}grnd(P), possibly subject to a query in P, where the answer to a non-ground query a? consists of all ground instances of atom a that belong to every answer set of P. Taking the prerequisites of instantiation procedures like “intelligent grounding” [36] into account, non-ground ASP-Core-2 programs have to comply with additional requirements [15], such as finiteness of answer sets and safety. In a nutshell, these conditions require the availability of (positive) occurrences of variables within the bodies of rules as well as aggregate or choice elements in order to restrict the relevant substitutions and enable grounders to compute a (finite) ground program, which is typically much smaller yet equivalent to {a mathematical formula}grnd(P).
     </paragraph>
     <paragraph>
      Reconsidering the TSP instance in Fig. 1(b) along with the encoding in (1), (2), (3), (4), (5), (6), the choice rule in (1) expresses that exactly one outgoing arc must be selected per node for representing a Hamiltonian cycle in terms of (true) atoms over the predicate hc. While the local variable Y occurs in a choice element only, X is global, so that an instance of (1) is obtained for each of the nodes 1, 2, 3, and 4 in the example graph. On the other hand, Y is global in the integrity constraint in (2), i.e. a rule with an empty head that cannot be satisfied. Hence, the {a mathematical formula}#count atom requires that exactly one incoming arc per node is included in a Hamiltonian cycle. In (3), the lexicographically smallest node name, that is, 1 in our example, is determined by a {a mathematical formula}#min atom, assigned to X, and the node thus marked as initially reached. The idea of the rule in (4) is to derive further nodes as reached by tracing the arcs in a Hamiltonian cycle. Note that instances of (4) yield circular positive dependencies among ground atoms over the reach predicate, so that ground instantiations are non-tight (and HCF since there are no proper disjunctive rules). The requirement that all nodes must be reached is asserted by the integrity constraint in (5). In view of the ⊆-minimality of an answer set w.r.t. the reduct, models containing isolated subcycles, e.g. between nodes 1 and 4 as well as 2 and 3, are thus discarded, so that answer sets correspond one-to-one to Hamiltonian cycles in a directed graph given as instance. For the example graph in Fig. 1(a), there are two answer sets representing the Hamiltonian cycles {a mathematical formula}(1,2,3,4,1) and {a mathematical formula}(1,4,3,2,1). Their contained arcs are penalized by their costs (at the common level 1) via instances of the weak constraint in (6). Given that arc costs for {a mathematical formula}(1,2,3,4,1) and {a mathematical formula}(1,4,3,2,1) sum to 8 or 7, respectively, only the answer set representing {a mathematical formula}(1,4,3,2,1) in terms of the atoms {a mathematical formula}hc(1,4), {a mathematical formula}hc(4,3), {a mathematical formula}hc(3,2), and {a mathematical formula}hc(2,1) is optimal.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Format of the Fifth ASP Competition
     </section-title>
     <paragraph>
      The competition builds on the basis of the 2013 edition, offering former and new participants the chance to submit updated and/or novel solvers, and the focus is on the System track, i.e. fixed encodings. As already discussed in Section 1, particular emphasis is placed on ASP-Core-2 language features in order to establish a uniform setting for running and comparing participant systems.
     </paragraph>
     <paragraph>
      Starting from past experience, one objective was to simplify the scoring system w.r.t. the 2013 edition (see [2]), and to properly adjust it in the case of Optimization problems, while preserving the general idea of rewarding systems that perform well in a variety of domains and produce solutions of better quality. However, simplified scoring is just a starting point for fostering meaningful solver comparisons. Moreover, tracks are now conceived based on language features, rather than on a complexity basis. The rationale is to encourage the submission of solvers even if they are limited or specialized, respectively, to a language fragment. In addition, this track design paves the way to more detailed analyses of what (combinations of) techniques work well for particular language features. In our opinion, respective insights are, from a scientific point of view, more interesting than merely reporting track winners.
     </paragraph>
     <paragraph>
      In the remainder of this section, we describe the competition design, introduce categories and tracks, and present the scoring system. Further details about the ASP Competition series and past editions thereof are provided in Section 7.
     </paragraph>
     <section label="3.1">
      <section-title>
       Competition design
      </section-title>
      <paragraph>
       In view of the objective of comparing participant systems in a uniform setting, this edition of the ASP Competition did not include a Model&amp;Solve track, but took place in the spirit of the former System track: it was open to any general-purpose solving system, provided it was able to process ASP-Core-2 programs. The general input–output format followed the 2013 edition, so that previous System track submissions should (in principle) be able to participate again. However, the 2013 edition still made exceptions and admitted problem encodings in legacy formats, while the Fifth ASP Competition insisted on ASP-Core-2 compliance. Benchmark domains, encodings, and instances used to assess participant systems were selected by the Organizing Committee; they are detailed in Section 4.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Competition categories
      </section-title>
      <paragraph>
       The competition consists of two categories, depending on the computational resources allotted to each running system:
      </paragraph>
      <list>
       <list-item label="•">
        SP: One processor allowed;
       </list-item>
       <list-item label="•">
        MP: Multiple processors allowed.
       </list-item>
      </list>
      <paragraph>
       While the SP category aims at sequential solving systems, parallelism can be exploited in the MP category.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Competition tracks
      </section-title>
      <paragraph>
       Both categories of the competition are structured into four tracks, which are described next:
      </paragraph>
      <list>
       <list-item label="•">
        Track #1: Basic Decision. Encodings are normal logic programs, with simple arithmetic and comparison operators.
       </list-item>
       <list-item label="•">
        Track #2: Advanced Decision. Encodings exploit the full language, with queries, excepting optimization statements and non-HCF disjunction.
       </list-item>
       <list-item label="•">
        Track #3: Optimization. Encodings exploit the full language with optimization statements, excepting non-HCF disjunction.
       </list-item>
       <list-item label="•">
        Track #4: Unrestricted. Encodings exploit the full language.
       </list-item>
      </list>
     </section>
     <section label="3.4">
      <section-title>
       Scoring system
      </section-title>
      <paragraph>
       The adopted scoring system balances the following factors:
      </paragraph>
      <list>
       <list-item label="•">
        Domains are always weighted equally.
       </list-item>
       <list-item label="•">
        If a system outputs an incorrect answer to some instance in a domain, this invalidates its score for the whole domain, even if all other instances are correctly solved.
       </list-item>
       <list-item label="•">
        In case of Optimization problems, scoring is based on solution quality.
       </list-item>
      </list>
      <paragraph>
       In general, 100 points can be earned for each domain. The final score of a system consists of the sum of scores over all domains, and ties are broken by cumulative CPU times (timeouts included).
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Scoring details
      </section-title>
      <paragraph>
       For Decision and Query problems, the score of a solver S on a domain P featuring N instances is calculated as{a mathematical formula} where {a mathematical formula}NS is the number of instances solved within the allotted time and memory limits.
      </paragraph>
      <paragraph>
       For Optimization problems, solvers are ranked by solution quality. Let M be the number of participant systems; then, the score of a solver S for an instance I in a domain P featuring N instances is calculated as{a mathematical formula} where {a mathematical formula}MS(I) is
      </paragraph>
      <list>
       <list-item label="•">
        0, if S did neither provide a solution, nor report unsatisfiability, or
       </list-item>
       <list-item label="•">
        the number of participant systems that did not provide any strictly better solution than S, where a confirmed optimum solution is considered strictly better than an unconfirmed one, otherwise.
       </list-item>
      </list>
      <paragraph>
       The score {a mathematical formula}S(P) of a solver S for domain P consists of the sum of scores {a mathematical formula}S(P,I) over all N instances I featured by P. Note that, as with Decision and Query problems, {a mathematical formula}S(P) can range from 0 to 100.
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       Verification of answers
      </section-title>
      <paragraph>
       Each benchmark domain P is equipped with a checker program {a mathematical formula}CP that takes as input both an instance I and a corresponding witness solution A, and it is such that {a mathematical formula}CP(A,I)=true in case A is a valid witness for I w.r.t. P.
      </paragraph>
      <paragraph>
       There are two possible ways to detect incorrect behavior, and subsequently disqualify system S for P:
      </paragraph>
      <list>
       <list-item label="•">
        S produces an answer A, but A is not a correct solution for I. This case is detected by checking the outcome of {a mathematical formula}CP(A,I).
       </list-item>
       <list-item label="•">
        S recognizes instance I as unsatisfiable, but I actually has some witness solution. In this case, it is checked whether another system {a mathematical formula}S′ produced a solution {a mathematical formula}A′ for which {a mathematical formula}CP(A′,I) is true.{sup:4}
       </list-item>
      </list>
      <paragraph>
       A case of general failure (e.g. “out of memory” errors or other abrupt system failures) does not imply disqualification for a given benchmark domain.
      </paragraph>
      <paragraph>
       When dealing with Optimization problems, checkers produce also the cost of the (last) witness. For one, this value is considered when calculating scores and assessing answers of systems. For another, given an instance I of an Optimization problem P, the cost of a best valid witness found by any participant is taken as the imperfect optimum. In case a system S marks its witness A as optimal for I and the cost of A turns out to be different from the imperfect optimum, this is regarded as incorrect behavior, and S is disqualified for P.
      </paragraph>
     </section>
     <section label="3.7">
      <section-title>
       Solver I/O interface
      </section-title>
      <paragraph>
       Participant systems were required to support the same input–output format as used in 2013. Input programs are compliant with the ASP-Core-2 standard, and the expected system output depends on the kind of a problem, i.e. Decision, Query, or Optimization. Details on the output format can be found in [59].
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Benchmark suite
     </section-title>
     <paragraph>
      The benchmark domains used in this edition of the ASP Competition largely coincide with the ones from 2013. While respective ASP-Core-2 encodings were already available back then, most participants lacked preparation time and could not submit suitable systems. Hence, half of the systems were in 2013 run on “equivalent” encoding reformulations in legacy formats, and the Fifth ASP Competition is the first edition relying on common inputs in ASP-Core-2. Nowadays, the format is for instance supported by the grounder gringo-4[42], which thus offers an off-the-shelf front–end for solvers operating at the propositional level.
     </paragraph>
     <paragraph>
      As described in Section 3, the benchmarks in the Fifth ASP Competition are categorized into tracks based on the language features utilized by encodings. Table 1 provides an overview that groups benchmark domains in terms of language features in the ASP-Core-2 encodings from 2013. That is, the 2013 encodings for Labyrinth and Stable Marriage belong to the Basic Decision track (#1), and the “D” entries in the fourth column indicate that both domains deal with Decision problems. The Advanced Decision track (#2) includes the sixteen 2013 encodings for the domains in rows from Bottle Filling to Weighted-Sequence Problem. Among them, the Reachability domain aims at Query answering, as indicated by the “Q” in the fourth column. The next four rows marked with “O” provide the domains in the Optimization track (#3). Finally, the last four rows give the domains in the Unrestricted track (#4), where Abstract Dialectical Frameworks is an Optimization problem and Strategic Companies deals with Query answering.
     </paragraph>
     <paragraph>
      The second column of Table 1 summarizes the usage of particular language features, among the ones introduced in Section 2, for the encodings from the Fourth ASP Competition in 2013.{sup:5} While merely normal rules and comparison operators, considered as basic features, are used for Stable Marriage, the Basic Decision encoding for Labyrinth induces non-tight ground instantiations with positive recursion among atoms [40], [35]. Rules including aggregates like {a mathematical formula}#count, {a mathematical formula}#sum, {a mathematical formula}#max, and {a mathematical formula}#min in their bodies [39] are used, e.g. in the Advanced Decision encoding for Bottle Filling. Moreover, the Advanced Decision encoding for Graceful Graphs includes choice rules [82], where the superscript “” indicates non-trivial lower and/or upper bounds on the number of chosen atoms. Unlike that, the choice rules for Complex Optimization in the Unrestricted track are unbounded, and thus “” is omitted in its row. Proper disjunctions in rule heads [49], [32] are utilized, e.g. in the 2013 encoding for Graph Coloring. Finally, Abstract Dialectical Frameworks is the only Optimization problem in the Fifth ASP Competition for which more than one level, i.e. two levels of significance [82], [60], is used in weak constraints.
     </paragraph>
     <paragraph>
      In order to furnish an extended benchmark collection for this year, we devised new encoding variants for all domains but Reachability and Strategic Companies, whose 2013 encodings are relatively straightforward positive programs subject to ground queries. In particular, the encoding for Reachability is basic, yet categorized into the Advanced Decision track in view of queries. One motivation for providing alternative encodings was to circumvent grounding bottlenecks that previously hampered meaningful system evaluations for some domains, and thus to extend the collection of benchmarks suitable for solver development. Moreover, evaluating participant systems on previous encodings as well as alternative variants serves to validate competition results and to gain insights regarding the impact of encodings on system performance, where deviations may help to identify more or less successful modeling approaches.
     </paragraph>
     <paragraph>
      The language features utilized in the new encoding variants are indicated in the third column of Table 1. Given that the 2014 encodings for the domains marked with “{sup:⁎}” omit advanced language features of their 2013 counterparts, in addition to Labyrinth and Stable Marriage, the Basic Decision track on new encodings comprises four more benchmark domains: Graph Coloring, Hanoi Tower, Knight Tour with Holes, and Visit-all. The restriction to basic features is primarily achieved by rewriting disjunctive or choice rules like {a mathematical formula}p(X)|q(X)←d(X) and {a mathematical formula}{p(X):d(X)}=1← into normal rules such as {a mathematical formula}p(X)←d(X),notq(X) and {a mathematical formula}q(X)←d(X),p(Y),X≠Y. Such rewriting has also been applied to the 2013 encoding for Maximal Clique, which however includes weak constraints and remains in the Optimization track. Further variation is introduced by using the idea of explanatory frame axioms [77] for the planning problems Hanoi Tower and Visit-all. For two 2014 encodings with basic features only, those for Stable Marriage and Knight Tour with Holes, the size of ground instantiations is significantly smaller than before, due to the linearization of encoding parts that previously led to quadratic space consumption.
     </paragraph>
     <paragraph>
      In more detail, Knight Tour with Holes is a specialized version of the Hamiltonian cycle problem, so that rules similar to (3), (4), (5) can be used for checking reachability and are included in the alternative encoding variant for this domain. The encoding from 2013, however, is based on a quadratic representation of the full transitive closure of reachable nodes in terms of rules like the following:{a mathematical formula}{a mathematical formula}{a mathematical formula} Given n nodes, where n amounts to a square number determined by the dimension of a chessboard, a ground instantiation of the subprogram in (7), (8), (9) is of space complexity {a mathematical formula}O(n2), while the rules in (3), (4), (5) yield linear complexity {a mathematical formula}O(n).
     </paragraph>
     <paragraph>
      Moreover, the 2013 encoding for Stable Marriage includes a space-demanding integrity constraint of the form{a mathematical formula} for expressing that the marriages of a man M and a woman W to partners {a mathematical formula}W′ or {a mathematical formula}M′, respectively, are unstable if M has a higher preference for W than for {a mathematical formula}W′ and the preference of W for M is at least as high as for {a mathematical formula}M′. As a consequence, a ground instantiation lists all forbidden pairs of matches between men and women explicitly, yielding space complexity {a mathematical formula}O(n4) when n is the number of men as well as women. To avoid an explicit enumeration of such pairs, the 2014 encoding reformulates (10) in terms of a subprogram as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The idea of the rules in (11), (12), (13) is to derive preference values such that a man M or a woman W does not want to switch to any respective partner. The integrity constraint in (14) then denies situations in which a man and a woman would like to switch to each other, which in turn means that their marriages are unstable. Provided that preference values lie in the range from 1 to n, as sufficient to distinguish n men as well as women, a ground instantiation of the subprogram in (11), (12), (13), (14) is of space complexity {a mathematical formula}O(n2) and thus much more compact than (10).
     </paragraph>
     <paragraph>
      Regarding the revised Advanced Decision encodings, significant reductions in grounding size, by about one order of magnitude in comparison to their 2013 counterparts (as indicated in Table 15), were achieved for the domains Incremental Scheduling, Nomystery, Partner Units, and Weighted-Sequence Problem. These savings are due to more compact formulations of resource restrictions.
     </paragraph>
     <paragraph>
      In the Incremental Scheduling domain, jobs must be assigned to devices such that their executions do not overlap one another. By representing the starting times of jobs in terms of intervals [23], such mutual exclusion can be expressed conveniently and more concisely than with pairwise comparisons of exact starting times. Assuming that instances of {a mathematical formula}share(J1,J2) provide jobs {a mathematical formula}J1 and {a mathematical formula}J2 to be executed on a common device, the 2013 encoding includes a subprogram as follows for picking starting times and denying overlaps:{a mathematical formula}{a mathematical formula} Similar to (10), the integrity constraint in (16) lists all forbidden starting times {a mathematical formula}T2 for job {a mathematical formula}J2 relative to a starting time T and the length L of job {a mathematical formula}J1 explicitly. In view of instances with thousand and more time points, such pairwise combinations incur a significant space overhead. Hence, the 2014 encoding abstracts from exact starting times and utilizes a subprogram as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The rules in (17), (18), (19) represent an exact starting time T for a job J in terms of atoms {a mathematical formula}geq(J,t),…,geq(J,T) for some smallest time point t. Instead of a choice as in (15), an instance of atom {a mathematical formula}start(J,T) is then derived by the rule in (20). However, the exact starting time of a job {a mathematical formula}J1 is not needed in (21) to detect that {a mathematical formula}J1 must be executed before a job {a mathematical formula}J2, finishing at time {a mathematical formula}T+L, in view of the absence of {a mathematical formula}geq(J1,T+L), in case {a mathematical formula}J1 and {a mathematical formula}J2 share a device. That is, the exact starting times of {a mathematical formula}J1 and {a mathematical formula}J2 are not directly compared to figure out which order is needed and to deny impossible cases by means of the integrity constraint in (22), so that a ground instantiation saves space in comparison to (16).
     </paragraph>
     <paragraph>
      While the 2013 encoding for the planning problem Nomystery, which had been generated from PDDL [51], [50], was mostly kept as is, grounding benefits from the addition of built-in atoms to discard rules specifying redundant fluents. In particular, the fuel consumption of a truck driving from a location {a mathematical formula}L1 to {a mathematical formula}L2 at time T is expressed by rules like the following:{a mathematical formula}{a mathematical formula} The integrity constraint in (24) denies plans in which {a mathematical formula}F−C in {a mathematical formula}fuel(F−C,T) would become negative. Instances of the rule in (23) including such atoms are nevertheless produced by common grounders, as they do not utilize integrity constraints to restrict the required substitutions. As a consequence, atoms representing negative amounts of fuel are first included in a ground instantiation and then falsified by a solver. In order to avoid such redundancy, the 2014 encoding augments the rule in (23) with the precondition {a mathematical formula}F≥C, so that irrelevant instances can be directly discarded during grounding.
     </paragraph>
     <paragraph>
      The revised encodings for Partner Units and Weighted-Sequence Problem, both dealing with matching tasks involving budgets, are rewrites. The main principle for reducing the grounding size in comparison to their previously submitted counterparts is the usage of compact aggregates, {a mathematical formula}#count or {a mathematical formula}#sum, respectively, instead of basic subprograms to encode resource restrictions. In the Partner Units domain, a cubic integrity constraint of the form{a mathematical formula} has been reformulated as{a mathematical formula} to avoid an explicit enumeration of triples for expressing that at most two elements can be assigned to a common value V. The Weighted-Sequence Problem, on the other hand, involves a limitation of accumulated costs for elements denoted by numbers {a mathematical formula}1,…,n. In the 2013 encoding, the accumulation and limitation of costs is addressed by a subprogram as follows:{a mathematical formula} That is, basic rules describe the formation of total costs along n elements, whose individual costs depend on an interpretation at hand, and the limit is enforced by checking the existence of a viable outcome. Given that instances involve cost limitations to several hundreds and plenty (intermediate) sums are constructible, the above subprogram is responsible for large ground instantiations. Such a space blow-up is avoided by using a {a mathematical formula}#sum aggregate in an integrity constraint of the form{a mathematical formula} included in the 2014 encoding for the Weighted-Sequence Problem domain.
     </paragraph>
     <paragraph>
      New variants of encodings for domains in the Optimization track and the Unrestricted track are mainly obtained through local modifications and sometimes simplifications, while maintaining the underlying ideas. The only exception is the matching problem Crossing Minimization, dealing with the relative positions of endpoints connected by edges. Similar to the starting times of jobs in Incremental Scheduling, the 2014 encoding represents positions in terms of intervals. That is, for each endpoint of some edge, a predicate geq provides all positions preceding it w.r.t. the placement described by an answer set. This allows for a compact retrieval of the relative positions of endpoints X and Y by means of a rule{a mathematical formula} of the same pattern as (21), whereas the 2013 encoding relies on a rule of the form{a mathematical formula} whose ground instances enumerate pairs of candidate positions explicitly. Beyond reducing the size of ground instantiations (which is uncritical for Crossing Minimization instances used in the competition), the reformulation aims at an increased abstraction from exact placements for possibly improving search performance, especially when conflict-driven learning [81], [92] is applied.
     </paragraph>
     <paragraph>
      Finally, note that the instances run in the Fifth ASP Competition have been randomly selected from the suites submitted in 2013 (or 2011 for Partner Units), using the concatenation of winning numbers from the EuroMillions lottery of Tuesday, 22nd April 2014, as random seed. In this way, twenty instances were picked per domain in order to assess the participant systems both on the encodings from 2013 as well as their new variants.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Participants
     </section-title>
     <paragraph>
      In this section, we introduce the participants of the Fifth ASP Competition: 16 systems submitted by three teams.
     </paragraph>
     <paragraph>
      The Aalto team from Aalto University, Finland, submitted nine solvers, working by means of translations, whose detailed descriptions can be found in [12], [41], [63], [70]. Three systems, lp2sat3+glucose, lp2sat3+lingeling, and lp2sat3+plingeling-mt, rely on translation to SAT, which includes the normalization of aggregates as well as the encoding of level mappings for non-tight ground programs. The latter are expressed in terms of bit-vector logic or acyclicity checking, respectively, supported by the back-end SMT solvers of the lp2bv2+boolector and lp2graph systems. While the aforementioned systems do not support optimization and participate in the Basic and Advanced Decision tracks (#1 and #2) only, lp2maxsat+clasp, lp2mip2, and lp2mip2-mt, running clasp as a Max-SAT solver or the Mixed Integer Programming solver cplex as back-ends, respectively, compete in the Optimization track (#3) as well. Finally, lp2normal2+clasp normalizes aggregates (of up to certain size, following the rationale that introduced structural propositions may be useful in conflict-driven learning) and runs clasp as back-end ASP solver; lp2normal2+clasp participates in all four tracks and thus also in the Unrestricted track (#4). All systems by the Aalto team utilize gringo-4 for grounding, and none of them supports Query problems (Reachability and Strategic Companies). The systems lp2sat3+plingeling-mt and lp2mip2-mt exploit multi-threading and run in the MP category, while the other, sequential systems participate in the SP category.
     </paragraph>
     <paragraph>
      The Potassco team from the University of Potsdam, Germany, submitted the sequential system clasp[43], a native ASP solver for (extended) disjunctive logic programs based on conflict-driven learning, in the SP category and its multi-threaded version clasp-mt[44] in the MP category. Both systems utilize gringo-4 for grounding and participate in all four tracks, while they do not support Query problems.
     </paragraph>
     <paragraph>
      The Wasp team from the University of Calabria, Italy, submitted five incarnations of wasp[3], [4], a native ASP solver based on conflict-driven learning, yet extended with techniques specifically designed for solving disjunctive logic programs, in the SP category. Unlike wasp-1, utilizing a prototype version of DLV (to cope with the ASP-Core-2 language) for grounding, wasp-2 relies on gringo-4 and further differs from wasp-1 in the implementation of program simplifications and deterministic inferences. Moreover, wasp-1.5 is a hybrid system combining wasp-1 and wasp-2, basically switching between them depending on whether a logic program is non-HCF or subject to a query. While wasp-1 and wasp-1.5 compete in all domains and tracks, wasp-2 does not participate in the Unrestricted track (#4). Additionally, the wasp-wmsu1-only-weak and wasp-wpm1-only-weak systems are specifically designed for solving Optimization problems in the Optimization track (#3) plus the Abstract Dialectical Frameworks domain in the Unrestricted track only.
     </paragraph>
     <paragraph>
      Table 2 lists the submitted systems (in rows) along with their tracks and categories (in columns). The Advanced Decision track in column T#2 (other tracks denoted similarly) is further subdivided to indicate in subcolumn q the ability of dealing with Query problems, admitted within this as well as the Unrestricted track T#4. The last column reports whether a system falls into the SP or MP category. After a dry-run period, in which teams could test their submissions on the competition machine, the Wasp team withdrew wasp-wmsu1-only-weak (due to a bug that appeared after the submission deadline but before the competition started), so that 15 systems remained in the competition, 12 in the SP and 3 in the MP category.
     </paragraph>
     <paragraph>
      Regarding ASP solving approaches, similar to past competition editions, we can identify two main lines:
     </paragraph>
     <list>
      <list-item label="•">
       “native” systems, which exploit techniques purposely conceived for dealing with logic programs under the stable models semantics, and
      </list-item>
      <list-item label="•">
       “translation-based” systems, which at some stage of the evaluation process produce an intermediate specification in some different formalism that is then fed to a corresponding solver.
      </list-item>
     </list>
     <paragraph>
      Native systems include the ones submitted by the Potassco and Wasp teams as well as lp2normal2+clasp, while the remaining systems by the Aalto team utilize translations.
     </paragraph>
     <paragraph>
      It is also worth mentioning that, in order to assess improvements in system implementation, we reran a selection of the systems submitted to the Fourth ASP Competition in 2013. Section 6.2 compares their performance to current versions.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Competition results
     </section-title>
     <paragraph>
      The competition was run on a Debian Linux server (64bit kernel), equipped with Intel Xeon X5365 processors and 16 GB RAM. Time and memory per run were limited to 600 seconds and 6 GB, respectively. Participant systems could use up to 8 cores in the MP category, while the execution was limited to a single core in the SP category. The performance of systems was measured using the pyrunlim tool [1].
     </paragraph>
     <paragraph>
      We start by presenting performance results for the systems introduced in Section 5 on benchmarks consisting of 2013 problem encodings and twenty randomly selected instances per domain. This also includes the announcement of winners in tracks and categories. Then, Section 6.2 compares current systems to previous versions submitted in 2013 to give an account of the progress. The impact of modeling on the ASP solving process is assessed in Section 6.3 by comparing the performance on alternative encoding variants extending the benchmark collection.
     </paragraph>
     <section label="6.1">
      <section-title>
       Results of the Fifth ASP Competition
      </section-title>
      <paragraph>
       In the following, we report the official results of the Fifth ASP Competition track by track, and finally announce the category winners. We first present results for the SP category, and then we turn to the MP category.
      </paragraph>
      <paragraph>
       Table 3, Table 4, Table 5, Table 6 show the results for each track of the SP category. The tables are organized as follows: the first column provides systems, the second their scores, and the third cumulative CPU times. Systems are listed by scores in decreasing order with ties broken by CPU times, so that table positions correspond to the ranks of systems. For readability and since the ranks of systems are preserved, the reported CPU times account only for runs rewarded with positive scores, thus excluding 600 seconds penalty per failed solving attempt.
      </paragraph>
      <paragraph>
       The results for Track #1 are given in Table 3. This track includes only two domains, namely Labyrinth and Stable Marriage. The system clasp performs best by solving all but three of the forty instances, followed by lp2normal2+clasp and wasp-1.5. Another incarnation of wasp, i.e. wasp-2, as well as lp2graph have the same score as wasp-1.5, but with higher cumulative CPU times.
      </paragraph>
      <paragraph>
       Table 4 shows the results for Track #2, consisting of sixteen domains (cf. Table 1). Here lp2normal2+clasp is the best performing system, solving two instances more than clasp, which ranks second, and fifteen instances more than lp2maxsat+clasp, ranking third (closely followed by lp2sat3+lingeling). Notably, translation-based systems turn out to be competitive in this track, coming quite close to native solvers.
      </paragraph>
      <paragraph>
       The results for Track #3, including four Optimization problems, are presented in Table 5, where system scores, determined by relative solution quality (cf. Section 3.5), are for readability rounded to nearest integers; this also applies to the scores in Table 6, Table 7, Table 8, 14, and 15. The best performing systems are clasp, wasp-1, and wasp-2 as well as wasp-1.5 with identical scores and CPU times, given that wasp-1.5 always resorts to wasp-2 here. Somewhat unfortunately, the wrapper scripts of lp2normal2+clasp, lp2maxsat+clasp, and lp2mip2 failed to return their current best witnesses in case of timeouts, so that the scores draw an incomplete picture of the potential optimization capabilities of these systems.
      </paragraph>
      <paragraph>
       Finally, Table 6 provides the results for Track #4, containing non-HCF instances of the Decision problems Complex Optimization and Minimal Diagnosis, the Query problem Strategic Companies, and the Optimization problem Abstract Dialectical Frameworks. Note that wasp-wpm1-only-weak competed only in the latter domain, scored like the Optimization problems in Track #3, and that no instance of Strategic Companies was solved by any system. In the three effectively remaining domains, clasp performs best, closely followed by lp2normal2+clasp, which has some edge over wasp-1. Since wasp-1.5 always resorts to wasp-1 for non-HCF programs, it comes just a short time margin behind.
      </paragraph>
      <paragraph>
       We are now ready to announce the winners in the SP category, according to the accumulated results given in Table 7. Thus, the first place goes to clasp by the Potassco team, the second place to lp2normal2+clasp by the Aalto team, and the third place to wasp-1.5 by the Wasp team. That is, native systems are ahead of translation-based ones in the category ranking, which is partly explained by their versatility: while the winner systems competed in all four tracks, the translation-based systems by the Aalto team could only participate in Tracks #1 and #2 plus, in case of lp2maxsat+clasp and lp2mip2, the Optimization problems in Track #3.
      </paragraph>
      <paragraph>
       Similarly, Table 8 summarizes performance results for the MP category, in which clasp-mt by the Potassco team is followed by lp2sat3+plingeling-mt and lp2mip2-mt by the Aalto team. The native system clasp-mt participated and achieved first places in all four tracks, lp2sat3+plingeling-mt was more successful than lp2mip2-mt among translation-based systems in Tracks #1 and #2, while lp2mip2-mt became second (behind clasp-mt) in Track #3 dealing with Optimization problems; detailed results for each domain are given in Table 12. Albeit clasp-mt was disqualified in Abstract Dialectical Frameworks due to incorrect parallel optimization w.r.t. non-HCF programs, all three multi-threaded systems have a clear edge over their respective sequential counterparts and could thus take advantage of parallelism to solve more instances.
      </paragraph>
      <paragraph>
       Having announced the winners, in the following we give more detailed views of the performance of participant systems, focusing again on the SP category. To begin with, Fig. 2 displays a cactus plot for Decision problems (marked with “D” in Table 1). For each system, the x-axis gives the number of instances solved within a respective execution time on the y-axis. The performance curves exhibit three patterns: clasp and lp2normal2+clasp, based on the same solver, are close to each other on the right hand side, and lp2normal2+clasp turns out to be quite effective in still solving time-consuming instances; the majority of systems gathers in the center block led by wasp-1.5, and span over a range of about 60 instances with gradual performance differences; lp2mip2 remains on the left hand side of the plot, taking into account that its back-end solver cplex is less geared towards purely propositional settings than other solvers.
      </paragraph>
      <paragraph>
       The curves in Fig. 3 plot the score acquisition of systems for Optimization problems (marked with “O” in Table 1), where system runs are ordered by the achieved positive scores, and the sum of scores for the number of instances on the x-axis is given on the y-axis. In the first place, the plot indicates that clasp had more success in producing high-quality witnesses than the four incarnations of wasp whose curves are underneath. As mentioned above, due to malfunctioning wrapper scripts, the systems lp2normal2+clasp, lp2maxsat+clasp, and lp2mip2 failed to return their current best witnesses in case of timeouts, but produced confirmed optimum solutions only. Since the resulting curves are indistinguishable, lp2maxsat+clasp and lp2mip2, which solved fewer instances and are thus dominated by lp2normal2+clasp, are not displayed in Fig. 3. While lp2normal2+clasp returned optimal witnesses only, the other five systems gained (positive) scores in considerably more runs, and clasp earns roughly double the sum of scores using the same search back-end as lp2normal2+clasp.
      </paragraph>
      <paragraph>
       Table 9 gives an impression of the memory consumption of participant systems by providing the minimum, 25th percentile, median, 75th percentile, and maximum amounts of memory used in runs rewarded with positive scores along with respective average values and standard deviations. Apart from wasp-wpm1-only-weak, which dealt with Optimization problems in five domains only, the median and average values indicate that clasp and lp2graph, whose support for acyclicity checking admits a compact representation of non-tight programs, consume the least memory among systems in the SP category. The memory overhead incurred by the normalization of aggregates and/or translation to the formalisms of other back–end solvers can be observed in the second and fourth to eighth row. The three incarnations of wasp below consume relatively much memory on some specific instances (as witnessed by the high standard deviations), while still being comparable with other systems in terms of maximum allocation. Also note that the selection process implemented in wasp-1.5 requires more memory than wasp-1 and wasp-2, which is because the input instance is provided as unique stream that is buffered to allow for an efficient solver selection. Regarding the three systems in the MP category, clasp-mt and lp2sat3+plingeling-mt, which are based on conflict-driven learning, demand significantly more memory than their sequential counterparts. Unlike that, the multi-threaded version lp2mip2-mt of lp2mip2 scores on more instances, while consuming less memory on average.
      </paragraph>
      <paragraph>
       Finally, Table 10, Table 11, Table 12 report detailed results per solver and domain. Notably, the higher score of lp2normal2+clasp than clasp in Track #2 is due to the domains Hanoi Tower and Visit-all. Since their encodings do not involve substantial aggregates, we attribute these performance differences to the usage of different search parameters rather than normalization.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Comparison to previous competition edition
      </section-title>
      <paragraph>
       In the following, we compare the performance of the most successful 2013 submission by each team, rerun under the same conditions as this year's entries in order to obtain comparable results, to “updated” versions in the Fifth ASP Competition. We begin with wasp-1 by the Wasp team, which resembles a corresponding system submitted in 2013, and then proceed to systems by the Aalto and Potassco teams.
      </paragraph>
      <section>
       <section>
        <section-title>
         Wasp team
        </section-title>
        <paragraph>
         The system wasp-1 is a bug-fix version of the 2013 submission dlv+wasp[3]. Hence, we concentrate on the comparison between wasp-1, its successor wasp-2, and the hybrid system wasp-1.5. Regarding the Decision problems in Tracks #1 and #2, wasp-2 solves 10 or 27, respectively, more instances than wasp-1, and 16 instances of the Query problem Reachability are solved likewise by wasp-1 and wasp-1.5. The only domain in which wasp-1 solves (three) more instances of a Decision problem than wasp-1.5 and wasp-2 is Qualitative Spatial Reasoning. This outlier can be explained by the naive handling of disjunction implemented in wasp-2. Indeed, the encoding for Qualitative Spatial Reasoning involves long disjunctions, so that the straightforward application of shifting [10] causes a space blow-up resulting in five memory outs. Unlike that, wasp-1 handles disjunctions by means of dedicated data structures. In Track #3 dealing with Optimization problems, wasp-1 still has advantages over the more recent wasp-2 system. However, when disregarding Track #4 in which wasp-2 did not participate, it remains ahead of wasp-1 by a score difference of 67. This gap increases to 147 points when considering wasp-1.5, which resorts to wasp-1 for Query answering in the Reachability domain and to deal with non-HCF programs in Track #4. Notably, the overhead of switching between wasp-1 and wasp-2 stays negligible, as wasp-1.5 achieves the same score as the system it picks for each domain. Hence, by utilizing wasp-2 in domains where it is applicable, wasp-1.5 significantly improves on wasp-1.
        </paragraph>
       </section>
       <section>
        <section-title>
         Aalto team
        </section-title>
        <paragraph>
         The system lp2sat[56], relying on eager translation of logic programs to SAT and using the precosat solver as search back-end, has been the best performing 2013 submission by the Aalto team. Among this year's entries, lp2sat3+glucose and lp2sat3+lingeling are based on the same approach. In order to use common inputs, we compare the previous and this year's systems on Basic Decision encodings only, taking into account that lp2sat processes a legacy format that differs from ASP-Core-2 on advanced constructs such as aggregates. Given that the Basic Decision track on 2013 encodings merely includes two domains, we here also consider the six alternative encodings with basic features only, and Table 13 shows respective scores and cumulative CPU times for solved instances. Regardless of which encoding is used, lp2sat, lp2sat3+glucose, and lp2sat3+lingeling have difficulties with instances of Labyrinth and Knight Tour with Holes, since translation to SAT is particularly intricate for the non-tight programs in these domains. However, lp2sat3+glucose and lp2sat3+lingeling improve on lp2sat by solving from 5 to 8 instances of Labyrinth, depending on which encoding is used, whereas lp2sat times out on all non-tight instances. Another gap is observed on the 2013 encoding for Stable Marriage, while the differences on 2014 encodings are smaller. Nevertheless, lp2sat3+glucose and lp2sat3+lingeling have some advantages in Graph Coloring, but lp2sat solves more instances of Visit-all. In general, the performance differences between lp2sat, on the one hand, and lp2sat3+glucose as well as lp2sat3+lingeling, on the other hand, are owed to re-engineered translation tools and the use of other SAT solvers as search back-ends. Considering the overall picture, the solving approach based on translation to SAT has been clearly advanced since the Fourth ASP Competition in 2013.
        </paragraph>
       </section>
       <section>
        <section-title>
         Potassco team
        </section-title>
        <paragraph>
         The prototype system claspd2[45] has been the overall winner in the Fourth ASP Competition and evolved into clasp as submitted this year. Table 14 contrasts both systems on 2013 encodings for all but the domains aiming at Query answering (Reachability and Strategic Companies), where Decision problems are addressed in the upper part and Optimization problems in the lower part. With either kind of problem, the relative performance of claspd2 and clasp is quite mixed. That is, claspd2 solves two or three, respectively, more instances than clasp in Hanoi Tower, Nomystery, and Sokoban, and it also achieves higher scores for the Optimization problems Connected Still Life and Valves Location. Opposite behavior is in turn observed in Graceful Graphs, Labyrinth, Solitaire, and Weighted-Sequence Problem as well as Crossing Minimization and Maximal Clique. In total, the accumulated results amount to two more solved instances of Decision problems and a score difference of 8 for Optimization problems, both in favor of clasp. Albeit clasp is equipped with a refined implementation and fine-tuned search parameters, the 2013 submission claspd2 thus remains close to its successor on the competition benchmarks.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="6.3">
      <section-title>
       Impact of modeling
      </section-title>
      <paragraph>
       We further investigate revised encodings furnishing an alternative benchmark collection. To this end, Table 15 provides grounding parameters, obtained by running gringo-4 under the same time and memory limits as participant systems, along with the scores of systems in the SP category (except for wasp-wpm1-only-weak, which did not participate in the majority of domains) on previous and novel encoding variants, given in the upper or lower row, respectively, per domain.
      </paragraph>
      <paragraph>
       As described in Section 4, one objective of revising previous encodings was to reduce grounding bottlenecks that affected all participant systems and hampered a meaningful comparison. Crucial size reductions were achieved with the new encodings for Incremental Scheduling, Knight Tour with Holes, Nomystery, Partner Units, Stable Marriage, and Weighted-Sequence Problem. In particular, no system solved any instance of Incremental Scheduling or Knight Tour with Holes on their 2013 encodings, rendering system comparisons void in these cases. Unlike that, some systems earn scores on the corresponding revised encodings that aim at linear rather than quadratic space consumption w.r.t. instance data. Interestingly, lp2mip2 could benefit most from the revised encoding for Knight Tour with Holes and solved 18 out of 20 highly combinatorial instances, even though its translation to MIP is less effective for other domains; e.g. lp2mip2 solved no instance of Hanoi Tower or Ricochet Robots regardless of the encoding used. With the exception of Nomystery, where system scores remain roughly at the same level with the previous and the new encoding variant, savings in grounding generally paid off.
      </paragraph>
      <paragraph>
       The second aspect of investigating alternatives was to gain some impression of the impact of encodings on search performance. In this regard, the revised encodings turn out to boost several systems in the domains Crossing Minimization (cf. timeouts in the detailed results in Table 10, Table 11, Table 12, Table 16, Table 17, Table 18), Graph Coloring, Hanoi Tower, Minimal Diagnosis, and Solitaire. However, the opposite effect also applies in some cases, as observed on the scores of wasp variants in the Connected Still Life domain and declines for all systems in Graceful Graphs. Furthermore, different systems may react non-uniformly like in Visit-all, where lp2mip2 and the wasp variants perform better on the revised encoding, while lp2bv2+boolector and lp2sat3+lingeling behave the other way round.
      </paragraph>
      <paragraph>
       Apart from objective measures such as grounding size, the effect of encoding variants on system performance is difficult to predict, and different options shed some light on whether benchmarks are inherently hard or influenced by modeling. Arguably, more challenging instances would be desirable for domains in which some encoding variant enables a participant system to complete all its runs in time, as it happens in half of the domains listed in Table 15.
      </paragraph>
      <paragraph>
       The impact of modeling on performance is summarized in Fig. 4, which contrasts overall scores, displayed in decreasing order, of systems in the SP category on alternative encoding variants with corresponding scores on 2013 encodings (as listed in Table 7). Apart from the prototype system wasp-wpm1-only-weak, which failed on the new encodings for Optimization problems, all systems benefit more or less substantially from rewrites. However, the first three places remain the same, and gradual differences to the official ranking in the SP category concern systems whose performance is close on both previous and novel encoding variants. That is, relative performance is largely unaffected by modeling aspects, but primarily owed to solving technology and versatility, while encoding improvements can be highly effective in general.
      </paragraph>
      <paragraph>
       More detailed results of running systems in the SP category on alternative encodings can be found in Table 16, Table 17, Table 18.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Comparison to previous ASP and other competitions
     </section-title>
     <paragraph>
      In this section, we compare the format of the Fifth ASP Competition with past editions, discussing the differences with respect to several aspects, such as tracks or scoring systems. Furthermore, it is worth noting that ASP has a close relationship to other modeling paradigms and languages, such as SAT, SMT, QBF, and more, all of which aim at solving demanding AI problems. In the following, we locate this edition of the ASP Competition in the spectrum of related events.
     </paragraph>
     <section label="7.1">
      <section-title>
       The ASP Competition series
      </section-title>
      <paragraph>
       In September 2002, participants to the Dagstuhl Seminar on Nonmonotonic Reasoning, Answer Set Programming and Constraints [14] agreed that standardization was a key issue for the development of ASP; hence, they decided to establish an infrastructure for benchmarking ASP solvers, as already in use in the neighboring fields of SAT and Constraint Programming. A first informal competition took place during the workshop, featuring the five systems dlv[60], smodels[82], assat[62], cmodels[52], and aspps[29] from TU Vienna/Univ. of Calabria, Helsinki UT, Hong Kong UST, Univ. of Texas at Austin, and Univ. of Kentucky. Since then, and after a second informal edition in 2005, the ASP Competition series has been established as a reference event for the community. It takes usually place biennially, and results are officially announced at the International Conference on Logic Programming and Nonmonotonic Reasoning (LPNMR).
      </paragraph>
      <paragraph>
       Interestingly, the competition format was not definitely established from the beginning; rather, as research went on and the state of the art was pushed forward, it has been adjusted in order to foster advancements and grant benefits to the community. However, it is worth noting that language standardization has always been a crucial issue. A progress schema of the ASP Competition series is shown in Fig. 5. For further details, we refer the reader to [18].
      </paragraph>
      <paragraph>
       In the 2011 and 2013 editions, the format consisted of two different tracks, adopting the distinction between a Model&amp;Solve and a System track. Both tracks featured a selected suite of domains, chosen by means of an open Call for Problems stage. This edition omitted a benchmark submission phase and relied on available encodings and instances (mainly from 2013) in view of the short preparation period.
      </paragraph>
      <paragraph>
       The System track was essentially similar to the format of the current edition. It was conceived with the aim of fostering language standardization, and let the participants compete on given encodings under fixed conditions, e.g. excluding custom problem encodings and domain-tailored evaluation strategies. However, in previous editions, the track was subdivided on the basis of problem complexity, while this edition makes a more fine-grained distinction based on language features; the rationale for this change has been discussed in Section 3.
      </paragraph>
      <paragraph>
       Unlike the System track, the Model&amp;Solve track in previous editions was instead left open to any (bundle of) solver systems loosely based on a declarative specification language: no constraints were imposed on encodings apart from the requirement that the language had to be declarative. The aims were to encourage the development of new expressive declarative constructs and/or new modeling paradigms, to foster the exchange of ideas between communities in close relationship to ASP, and to stimulate the development of new ad-hoc solving methods. Model&amp;Solve track competitors received textual problem descriptions from a variety of domains and had several months to produce problem encodings together with one or multiple working systems of choice, which could be configured on a per domain basis.
      </paragraph>
      <paragraph>
       It is worth discussing why the Model&amp;Solve track has been detached from the system competition, and turned into an informal on-site event, summarized at [17], in the spirit of the Prolog Programming Contest. Although its goals were ambitious and definitely relevant, it requires a substantial amount of work to organize and, even more, participate in such a track. First of all, fine-tuning a system, or a bundle of systems, and an encoding for an individual domain is a hard task; this, in spite of the fact that contestants have always been encouraged to exchange their solutions freely, tends to give larger teams a clear advantage over others. In addition, the participation from neighboring communities was rather limited, probably due to corresponding genuine competitions and the non-negligible effort of participating. Compared to this, it is easier to compete in an event similar to the System track by submitting a solver system with appropriate support for the respective input language.
      </paragraph>
      <paragraph>
       Eventually, the scoring scheme has been significantly changed for the sake of simplicity. Indeed, the scoring has been refined throughout editions. At the beginning, it was mainly based on a weighted sum of the number of instances solved within given time and memory limits; in the 2011 and 2013 editions, the scoring scheme has been extended by awarding additional points to systems performing well in terms of elapsed time. For a Decision or Query problem P, each system gained a score {a mathematical formula}S(P)=Ssolve(P)+Stime(P), where {a mathematical formula}Ssolve and {a mathematical formula}Stime ranged from 0 to 50 each: while {a mathematical formula}Ssolve was linearly dependent on the number of solved instances, {a mathematical formula}Stime involved a logarithmic dependence on participants' running times, thus rendering time differences at a common order of magnitude less significant. For Optimization problems, the {a mathematical formula}Ssolve part was replaced with a scoring formula taking objective values associated with solutions into account, where distances from an (imperfect) optimum were penalized exponentially.
      </paragraph>
      <paragraph>
       We performed a number of ex-post analyses on the results of the 2011 and 2013 editions, experimenting with different scoring schemes. At first, we found that time quota did not make much difference and accordingly use {a mathematical formula}Ssolve(P) only (simply denoted {a mathematical formula}S(P) in Section 3.5), which as before linearly reflects the number of solved instances of a Decision or Query problem P. Furthermore, we pondered that absolute objective values are not adequate for scoring solutions for Optimization problems, given that they depend heavily on domains and are susceptible to perturbations; rather than that, relative rankings can draw a more reliable picture. Hence, for an Optimization problem P, we determine {a mathematical formula}Ssolve(P) by accumulating ranks by solution quality for instances of P. Interestingly, if employed in the latest editions, the winners would have been the same. The new scoring scheme is also closer to those of competitions in neighboring fields, which are considered next.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Related competitions
      </section-title>
      <paragraph>
       In the following, we briefly overview other competitions in neighboring fields and relate them to the ASP Competition series. Note that we do not aim at contrasting formalisms or respective systems, but are rather interested in the similarities and differences of competition setups. Comparisons of systems from different fields can be found, e.g. in [5], [19], [28], [64].
      </paragraph>
      <paragraph>
       We start by listing related competitions (in no particular order) along with acronyms, years of latest editions, and recent references, if available:
      </paragraph>
      <list>
       <list-item label="•">
        IJCAR ATP System Competition – CASC 2014 [20], [86]
       </list-item>
       <list-item label="•">
        Confluence Competition – CoCo 2014 [21]
       </list-item>
       <list-item label="•">
        Configurable SAT Solver Challenge – CSSC 2014 [25]
       </list-item>
       <list-item label="•">
        Hardware Model Checking Competition – HWMCC 2014 [54]
       </list-item>
       <list-item label="•">
        OWL Reasoner Evaluation – ORE 2014 [73], [7]
       </list-item>
       <list-item label="•">
        QBF Gallery – QBF 2014 [75]
       </list-item>
       <list-item label="•">
        SAT Competition – SAT-COMP 2014 [79], [58]
       </list-item>
       <list-item label="•">
        Satisfiability Modulo Theories Solver Competition – SMT-COMP 2014 [83], [9]
       </list-item>
       <list-item label="•">
        Competition on Software Verification – SV-COMP 2014 [87], [11]
       </list-item>
       <list-item label="•">
        Syntax-Guided Synthesis Competition – SyGuS-COMP 2014 [88]
       </list-item>
       <list-item label="•">
        Synthesis Competition – SYNTCOMP 2014 [89]
       </list-item>
       <list-item label="•">
        Termination Competition – termCOMP 2014 [90]
       </list-item>
       <list-item label="•">
        Max-SAT Evaluation – Max-SAT 2014 [67]
       </list-item>
       <list-item label="•">
        Mancoosi International Solver Competition – MISC 2012 [69]
       </list-item>
       <list-item label="•">
        Pseudo-Boolean Competition – PB 2012 [74], [58]
       </list-item>
       <list-item label="•">
        International CSP Solver Competition – CSC 2009 [24];MiniZinc Challenge 2014 [68], [85]
       </list-item>
       <list-item label="•">
        International Planning Competition – IPC 2014 [55], [22]
       </list-item>
      </list>
      <paragraph>
       A quick glance at competition characteristics is given in Table 19, displaying whether a standard input format, optimization tasks, non-ground problem descriptions, and industrial/real-world domains are featured; the last column reports the number of participant systems in latest editions. Notably, almost all competitions rely on a standard language, with the exception of SV-COMP in view of its applied nature. Considerable efforts in dealing with industrial/real-world problems are apparent too. The latter frequently demand for optimization capabilities, central in one third of the competitions, as well as non-ground representations, featured by half of the competitions. Both of these concepts are jointly addressed in the CSC, IPC, and ASP Competition series.
      </paragraph>
      <paragraph>
       Almost all competitions include tracks, also called divisions or categories. The way tracks are defined depends on the competition at hand, but three main criteria can be identified: language features of inputs, the kind of problem domains, and reasoning tasks to be accomplished. For instance, SAT-COMP distinguishes application, combinatorial, and random instances, and the kind of benchmarks has a major impact on participant and winner systems. Interestingly, none of the considered competitions conceives tracks on an intentional complexity basis.
      </paragraph>
      <paragraph>
       For scoring, almost all competitions rely on the number of solved instances, sometimes with particularities like bonus/malus points in case of errors, and ties are usually broken by taking resources spent into account. For instance, SMT-COMP adopts a rather complex scheme, based on correctness, number of queries answered, and running times. In case of Optimization problems, the quality of solutions matters, such as plan quality in IPC. The simplified scoring scheme adopted in this edition of the ASP Competition is in line with related competitions and pursues similar objectives. In particular, the relative ranking of systems by solution quality has been inspired by MISC, which deals with optimization in the context of software package management.
      </paragraph>
      <paragraph>
       Many communities (if not all) maintain benchmark repositories, often well-known, well-studied, and classified in terms of dimensions like language features or hardness. Even though the Asparagus platform [6] gathers a broad collection of benchmarks for ASP systems, it however appears less central to the ASP community than corresponding initiatives in neighboring fields. Moreover, almost all competitions make use of benchmarks from previous editions and are additionally accompanied by a call for benchmark submissions (which had to be omitted in this edition of the ASP Competition). Notably, benchmarks submitted to SV-COMP are reviewed and possibly revised by organizers and participants in order to improve the benchmark collection; our encoding variants partly go into that direction as well. A subset of the available instances to be fed to participant systems is then typically determined randomly, sometimes applying eligibility criteria, e.g. based on estimated hardness.
      </paragraph>
      <paragraph>
       Finally, we would like to acknowledge the minisat[30] “hack” track, featured by SAT-COMP since its 2009 edition. This track promotes ideas that can be integrated into a common base SAT solver with relatively modest development effort. Such a possibility lowers the threshold for entering the competition, especially for students or small research teams, and is one among several factors for the comparably high participation in SAT-COMP. If a corresponding baseline were available for ASP solving as well, it might encourage more teams to participate in future editions of the ASP Competition.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>