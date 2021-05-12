<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    The first international competition on computational models of argumentation: Results and analysis.
   </title>
   <abstract>
    We report on the First International Competition on Computational Models of Argumentation (ICCMA'15) which took place in the first half of 2015 and focused on reasoning tasks in abstract argumentation frameworks. Performance of submitted solvers was evaluated on four computational problems wrt. four different semantics relating to the verification of the acceptance status of arguments, and computing jointly acceptable sets of arguments. In this paper, we describe the technical setup of the competition, and give an overview on the submitted solvers. Moreover, we report on the results and discuss our findings.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Argumentation is a core technique for humans to reach conclusions in the presence of conflicting information and multiple alternatives. It is used both as a means for persuasion in dialogues as well as one owns deliberation mechanism. An argument can be regarded as some concise set of pieces of information that supports a certain conclusion, such as “As Tweety is a bird and birds usually fly, Tweety supposedly flies”. Arguments may support contradicting conclusions—consider e.g. “As Tweety is a penguin and penguins do not fly, Tweety does not fly despite the fact that he is a bird”—and the process of argumentation aims at comparing and weighing arguments and counterarguments and ultimately deciding which arguments prevail. While the field of argumentation theory[96] studies the structure and interaction of arguments from a philosophical perspective, within artificial intelligence, the field of computational models of argumentation[6], [8] has gained some attention in recent years. In general, this field is concerned with logical formalizations of models of argumentation that can be used by automatic reasoning systems to cope with uncertainty and inconsistency. Thus, these models are closely related to approaches to non-monotonic reasoning and offer a novel perspective on those. After some earlier works of e.g. Pollock [82] and Simari &amp; Louie [87], abstract argumentation frameworks have been proposed by Dung [35] as a general and abstract formalism to represent arguments and their interactions and have, since then, been most influential. In abstract argumentation frameworks, arguments are represented as vertices in a directed graph and an arc from a vertex {a mathematical formula}A to a vertex {a mathematical formula}B means that {a mathematical formula}A is a counterargument for {a mathematical formula}B or that {a mathematical formula}A “attacks” {a mathematical formula}B. Thus, this model abstracts from most issues of argumentation scenarios—including the inner structure of arguments—and provides a clean formal view on the issue of conflict between arguments. Given an abstract argumentation framework the central question is to decide whether arguments are acceptable, i.e., whether they “survive” the attacks of their counterarguments due to backing by other arguments. A set of jointly acceptable arguments is then also called extension.
     </paragraph>
     <paragraph>
      Abstract argumentation provides a nice framework to discuss issues of non-monotonic reasoning in general as many other non-monotonic formalisms such as default theory and logic programs under the stable model semantics can be cast into abstract argumentation frameworks, cf. [35]. On the other hand, the multitude of different semantics and extensions go beyond the expressivity of previous formalisms and provide a novel general approach to non-monotonic reasoning, cf. e.g. [39]. This makes abstract argumentation frameworks a versatile knowledge representation formalism. Many research topics have been spawned around these frameworks including, among others, semantical issues [4], extensions on support [31], quantitative approaches [38], [90], [65], and in particular algorithms [30]. The computational challenges of various reasoning problems are vast and range up to the second level of the polynomial hierarchy for certain semantics [40], [44]. Among the first implementations for reasoning with abstract argumentation frameworks—which appeared around 2008—were Dungine [88] and ASPARTIX [47]. More followed in the years after and, starting from 2013 up till now, a number of comparative analyses among argumentation solvers have been conducted, e.g., [42], [10], [43], [95], [11], [12], [14], [27], in order to address a systematic performance comparison. Following the tradition of the communities of other approaches to knowledge representation and reasoning, such as the SAT and the Answer Set Programming (ASP) communities, a public competition for solver evaluation was planned soon after.
     </paragraph>
     <paragraph>
      This paper reports on the First International Competition on Computational Models of Argumentation (ICCMA'15) which took place in the first half of 2015. The results of the competition had been officially presented at the International Workshop on Theory and Applications of Formal Argument (TAFA'15) which was co-located with the 24th International Joint Conference on Artificial Intelligence (IJCAI'15) in Buenos Aires, Argentina. The competition called for solvers on four classical computational problems in abstract argumentation frameworks wrt. the four classical semantics proposed in [35], including enumerating all extensions of a particular semantics and deciding whether a certain argument is contained in all of them. Submitted solvers were evaluated wrt. their runtime performance on these tasks on a series of artificially generated argumentation frameworks.
     </paragraph>
     <paragraph>
      Abstract argumentation frameworks are arguably the most investigated formalism for formal argumentation. However, there are also formalisms for structured argumentation, such as deductive argumentation [8] and defeasible logic programming [55]. In structured argumentation, arguments are a set of (e.g. propositional) formulas (the support of an argument) that derive a certain conclusion (the claim of an argument). The attack relation between arguments is then derived from logical inconsistency. For ICCMA'15 only problems of abstract argumentation have been considered as this is simple and well-understood formalism for representing computational argumentation. However, considering tracks on structured argumentation may be a worthwhile endeavor for future competitions.
     </paragraph>
     <paragraph>
      The competition received 18 solvers from research groups in Austria, China, Cyprus, Finland, France, Germany, Italy, Romania, and the UK. The solvers were based on different approaches and algorithmic design patterns to solve problems, ranging from reductions to SAT or ASP problems to novel heuristic algorithms. This paper gives an overview on the setup of the competition, the submitted solvers, and the results. More specifically, the remainder of this paper is organized as follows. In Section 2 we provide some necessary background on abstract argumentation and give an overview on the computational tasks considered in the competition. In Section 3 we describe the technical setup of the competition, including the approach for benchmark generation, the used evaluation methodology, and the technical interface requirements. In Section 4 we give an overview on the submitted solvers. Afterwards, we present and analyze the results of the competition in Section 5 and we discuss the lessons learned from this first experience in Section 6. We conclude with a summary in Section 7. Appendix A provides pseudo code of the graph generators used for creating the benchmark graphs of the competition. Appendix B gives detailed graph-theoretic statistics on the benchmark graphs.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background and competition overview
     </section-title>
     <paragraph>
      In the following, we give a brief overview on abstract argumentation, the computational problems considered in the competition, and some brief overviews on answer set programming and satisfiability solving. The latter are intended to provide some formal background on the inner workings of solvers based on reductions to those.
     </paragraph>
     <section label="2.1">
      <section-title>
       Abstract argumentation
      </section-title>
      <paragraph>
       Abstract argumentation frameworks[35] take a very simple view on argumentation as they do not presuppose any internal structure of an argument. Abstract argumentation frameworks only consider the interactions of arguments by means of an attack relation between arguments.
      </paragraph>
      <paragraph label="Definition 1">
       Abstract argumentation frameworkAn abstract argumentation framework{a mathematical formula}AF is a tuple {a mathematical formula}AF=(Arg,→) where {a mathematical formula}Arg is a set of arguments and → is a relation {a mathematical formula}→⊆Arg×Arg.
      </paragraph>
      <paragraph>
       For two arguments {a mathematical formula}A,B∈Arg the relation {a mathematical formula}A→B means that argument {a mathematical formula}A attacks argument {a mathematical formula}B. Abstract argumentation frameworks can be concisely represented by directed graphs, where arguments are represented as nodes and edges model the attack relation. Note that we only consider finite argumentation frameworks here, i.e., argumentation frameworks with a finite number of arguments.
      </paragraph>
      <paragraph label="Example 1">
       Consider the abstract argumentation framework {a mathematical formula}AF=(Arg,→ ) depicted in Fig. 1. Here it is {a mathematical formula}Arg={A1,A2,A3,A4,A5} and {a mathematical formula}→={(A2,A1),(A2,A3),(A3,A4),(A4,A5),(A5,A4),(A5,A3),(A5,A6),(A6,A6)}.
      </paragraph>
      <paragraph>
       Semantics are usually given to abstract argumentation frameworks by means of extensions [35]. An extension E of an argumentation framework {a mathematical formula}AF=(Arg,→) is a set of arguments {a mathematical formula}E⊆Arg that gives some coherent view on the argumentation underlying {a mathematical formula}AF.
      </paragraph>
      <paragraph>
       In the literature [35], [22] a wide variety of different types of semantics has been proposed. In the competition we focused on the four classical semantics of Dung [35], namely grounded, complete, preferred, and stable semantics. For a set of arguments {a mathematical formula}S⊆Arg let {a mathematical formula}S−={B|∃A∈S:B→A} denote the set of attackers of S and let {a mathematical formula}S+={B|∃A∈S:A→B} denote the set of attacked arguments of S.
      </paragraph>
      <paragraph label="Definition 2">
       Let {a mathematical formula}AF=(Arg,→) be an argumentation framework.
      </paragraph>
      <list>
       <list-item label="1.">
        A set of arguments {a mathematical formula}E⊆Arg is conflict-free iff there are no {a mathematical formula}A,B∈E with {a mathematical formula}A→B.
       </list-item>
       <list-item label="2.">
        An argument {a mathematical formula}A∈Arg is acceptable with respect to a set of arguments {a mathematical formula}E⊆Arg iff for every {a mathematical formula}B∈Arg with {a mathematical formula}B→A there is {a mathematical formula}A′∈E with {a mathematical formula}A′→B.
       </list-item>
       <list-item label="3.">
        A set of arguments {a mathematical formula}E⊆Arg is an admissible extension iff it is conflict-free and all {a mathematical formula}A∈E are acceptable with respect to E.
       </list-item>
       <list-item label="4.">
        A set of arguments {a mathematical formula}E⊆Arg is a complete extension (CO) iff it is admissible and there is no {a mathematical formula}A∈Arg∖E which is acceptable with respect to E.
       </list-item>
       <list-item label="5.">
        A set of arguments {a mathematical formula}E⊆Arg is a grounded extension (GR) iff it is complete and E is minimal with respect to set inclusion.
       </list-item>
       <list-item label="6.">
        A set of arguments {a mathematical formula}E⊆Arg is a preferred extension (PR) iff it is complete and E is maximal with respect to set inclusion.
       </list-item>
       <list-item label="7.">
        A set of arguments {a mathematical formula}E⊆Arg is a stable extension (ST) iff it is complete and {a mathematical formula}E∪E+=Arg.
       </list-item>
      </list>
      <paragraph>
       If E is some extension we say that each {a mathematical formula}A is accepted wrt. E. The intuition behind admissibility is that an argument can only be accepted if there are no attackers that are accepted and if an argument is not accepted then there has to be an acceptable argument attacking it. The idea behind the completeness property is that all acceptable arguments should be accepted. The grounded extension is the minimal set of acceptable arguments and uniquely determined [35]. A preferred extension is a maximal set of acceptable arguments and a stable extension is a complete extension that attacks all arguments not contained in it. Note that for complete, preferred, and stable semantics, their extensions are not necessarily uniquely defined and that for stable semantics an extension does not necessarily exist [35].
      </paragraph>
      <paragraph>
       For the remainder of the paper we use σ to denote any semantics of GR, CO, PR, ST.
      </paragraph>
      <paragraph label="Example 2">
       Consider again the argumentation framework {a mathematical formula}AF in Fig. 1. The complete extensions of {a mathematical formula}AF are {a mathematical formula}E1={A2}, {a mathematical formula}E2={A2,A4}, and {a mathematical formula}E3={A2,A5}. Furthermore, {a mathematical formula}E1 is the grounded extension, {a mathematical formula}E2 and {a mathematical formula}E3 are both preferred extensions, and only {a mathematical formula}E3 is stable.
      </paragraph>
      <paragraph label="Definition 3">
       An alternative approach to define the semantics of an argumentation framework is to use labelings instead of extensions [21]. ({a mathematical formula}AF-labeling) Let {a mathematical formula}AF=(Arg,→) be an abstract argumentation framework. An {a mathematical formula}AF-labeling is a total function {a mathematical formula}lab:Arg→{in,out,undec}. We define {a mathematical formula}in(lab)={ai∈Arg|lab(ai)=in}, {a mathematical formula}out(lab)={ai∈Arg|lab(ai)=out}, {a mathematical formula}undec(lab)={ai∈Arg|lab(ai)=undec}. While extensions only allow for a two-valued assessment of the justification status of an argument—either the argument is in the extension or it is not—labelings allow a three-valued assessment where the additional assessment value “undec” represents an undecided assessment. Similar conditions as in Definition 2 can be defined for labelings in order to formalize when a labeling is conflict-free, admissible, complete, etc., e.g., a labeling lab is conflict-free iff there are no {a mathematical formula}A,B∈in(lab) with {a mathematical formula}A→B. Indeed, labeling-based and extension-based semantics are equivalent [21] through the following transformations. If E is a conflict-free (admissible, complete, …) extension then the labeling lab defined through {a mathematical formula}in(lab)=E, {a mathematical formula}out(lab)=E+, and {a mathematical formula}undec(lab)=Arg∖(E∪E+) is a conflict-free (admissible, complete, …) labeling. Furthermore, if lab is a conflict-free (admissible, complete, …) labeling then {a mathematical formula}in(lab) is a conflict-free (admissible, complete, …) extension. For this reason we may use the terms labeling and extension interchangeably.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Computational problems
      </section-title>
      <paragraph>
       The most important decision problems discussed in the context of abstract argumentation are as follows (let σ be any semantics):{a mathematical formula} The decision problem Credσ is about credulous acceptance of an argument, i.e., whether it is contained in any σ-extension. The problem Skeptσ is about skeptical acceptance of an argument, i.e., whether it is contained in all σ-extensions. Furthermore, Verσ is about verifying whether a given set of arguments is indeed a σ-extension. Finally, the problems Existsσ and Exists{a mathematical formula}σ¬∅ relate to existence problems of extensions. Note that Existsσ is trivial for most semantics except stable semantics, as they guarantee the existence of at least one extension. The harder decision problem Exists{a mathematical formula}σ¬∅ is about checking whether there exist a non-empty σ-extension.
      </paragraph>
      <paragraph>
       Table 1 gives an overview on the computational complexity of the decision problems discussed above. The results on the grounded semantics as well as ExistsPR and ExistsCO follow immediately from the properties of these semantics shown in [35]. The remaining results for complete semantics are initially by [32]. The results for stable and preferred semantics follow from their corresponding results for logic programming [33], except the SkeptPR result which is from [36]. For a more detailed discussion of these results and the employed techniques see [41], [44]. As can be seen, grounded semantics is the only semantics where all five decision problems are tractable. A naive algorithm for computing the grounded extension can easily be given: first, all arguments that have no attackers are added to an empty extension E and those arguments and all arguments that are attacked by one of these arguments are removed from the framework; then this process is repeated; if one obtains a framework where there is no unattacked argument, the final set E is the grounded extension. Clearly, this is a polynomial algorithm that can be used to solve all the above decision problems wrt. grounded semantics. The problems related to complete and stable semantics usually reside on the first level of the polynomial hierarchy and are thus intractable in practice. Preferred semantics is usually assessed to be computationally harder than the other semantics and particularly the decision problem Skeptσ lies on the second level of the polynomial hierarchy.
      </paragraph>
      <paragraph>
       Functional problems, such as computing all σ-extensions of an argumentation framework {a mathematical formula}AF, have not been investigated much in the literature. This is in line with general research on computational complexity as functional problems may also heavily depend on the size of the output. However, the computational complexity of the corresponding decision problems are usually sufficient to judge the hardness for the functional problems as well.
      </paragraph>
      <paragraph>
       Still, solving functional problems is important for the actual usability of systems using abstract argumentation and have therefore been considered in the competition as well. More precisely, the problems considered in the competition are given as follows (with the actual naming convention used for the competition):{a mathematical formula} In the above notation, the abbreviation DC stands for “decide credulous”, DS for “decide skeptical”, “SE” for “some extension”, and “EE” for “enumerate extensions”. In the following, we refer to DC, DS, SE, and EE as computational problems (or simply problems) and to a combination of a problem and a semantics, e.g. SE-PR, as a track. In the competition we considered the four problems in combination with each of the four discussed semantics, resulting in a total of 16 tracks. For each track, the aim of the competition was to evaluate solvers on how fast instances of these tracks could be correctly solved. Solvers were permitted to enter the competition if they supported at least one of these 16 tracks, but were not obliged to support all of them.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Argumentation, answer-set programming and satisfiability solvers
      </section-title>
      <paragraph>
       In the following, we provide some basics about Answer-set Programming and Satisfiability solvers. This background is intended to support the reader in understanding the main insights of the competition solvers, described in Section 4, implementing such encodings.
      </paragraph>
      <section label="2.3.1">
       <section-title>
        Answer-set programming
       </section-title>
       <paragraph>
        Answer set programming (ASP) [57] is a modern approach to declarative programming, where a user focuses on declaratively specifying her problem. ASP has its roots in deductive databases, logic programming, logic-based knowledge representation and reasoning, constraint solving, and satisfiability testing. It can be applied in a uniform way to search problems in the classes P, NP, and {a mathematical formula}NPNP in applications like planning, decision support, model checking, and many more.
       </paragraph>
       <paragraph>
        As discussed in [93], ASP relies upon:
       </paragraph>
       <list>
        <list-item label="1.">
         the representation of knowledge in terms of disjunctive logic programs with negation as failure (possibly including explicit negation and various forms of constraints),
        </list-item>
        <list-item label="2.">
         the interpretation of these logic programs under the stable model/answer set semantics and its extensions (dealing with explicit negation and constraints), and
        </list-item>
        <list-item label="3.">
         efficient computational mechanisms, called ASP solvers, to compute answer sets for grounded logic programs.
        </list-item>
       </list>
       <paragraph>
        We fix a countable set {a mathematical formula}U of domain elements, called constants. An atom is an expression {a mathematical formula}p(t1,…,tn), where p is a predicate of arity {a mathematical formula}n≥0, and each {a mathematical formula}ti is either a variable or an element from {a mathematical formula}U. An atom is called ground if it is free of variables. {a mathematical formula}BU denotes the set of all ground atoms over {a mathematical formula}U.
       </paragraph>
       <paragraph>
        A disjunctive rule r is of the form{a mathematical formula} with {a mathematical formula}n≥0, {a mathematical formula}m≥k≥0, {a mathematical formula}n+m&gt;0, where {a mathematical formula}a1,…,an,b1,…,bm are literals, and not represents default negation. The head of r is the set {a mathematical formula}H(r)={a1,…,an} and the body of r is {a mathematical formula}B(r)={b1,…,bk,notbk+1,…,notbm}. Furthermore, we have that {a mathematical formula}B+(r)={b1,…,bk} and {a mathematical formula}B−(r)={bk+1,…,bm}. A rule r is normal if {a mathematical formula}n≤1 and a constraint is normal if {a mathematical formula}n=0. A rule r is safe if each variable in r occurs in {a mathematical formula}B+(r). A rule r is ground if no variable occurs in r. A fact is a ground rule without disjunction and empty body. An input database is a set of facts. A program is a finite set of disjunctive rules. For a program π and an input database D, we write {a mathematical formula}π(D) instead of {a mathematical formula}D∪π. If each rule in a program is normal (resp. ground), we call the program normal (resp. ground). For any program π, let {a mathematical formula}Uπ be the set of all constants appearing in π. {a mathematical formula}Gr(π) is the set of rules rσ obtained by applying, to each rule {a mathematical formula}r∈π, all possible substitutions σ from the variables in r to elements of {a mathematical formula}Uπ. An interpretation {a mathematical formula}I⊆BU satisfies a ground rule r iff {a mathematical formula}H(r)∩I≠∅ whenever {a mathematical formula}B+(r)⊆I and {a mathematical formula}B−(r)∩I=∅. An interpretation {a mathematical formula}I satisfies a ground program π, if each {a mathematical formula}r∈π is satisfied by {a mathematical formula}I. A non-ground rule r (resp., a program π) is satisfied by an interpretation {a mathematical formula}I iff {a mathematical formula}I satisfies all groundings of r (resp., {a mathematical formula}Gr(π)). We have that {a mathematical formula}I⊆BU is an answer set of π iff it is a subset-minimal set satisfying the Gelfond–Lifschitz reduct {a mathematical formula}πI={H(r)←B+(r)|I∩B−(r)=∅,r∈Gr(π)}. For a program π, we denote the set of its answer sets by {a mathematical formula}AS(π).
       </paragraph>
       <paragraph>
        ASP is particularly well-suited for enumeration problems since these systems enumerate by default all solutions of a given program, thus enabling the enumeration of extensions of an abstract argumentation framework in an easy manner. Moreover, disjunctive ASP is capable of expressing problems being even complete for the second level of the polynomial hierarchy, which is of interest for abstract argumentation considering that several semantics such as the preferred semantics are of this high complexity, cf. the previous section.
       </paragraph>
       <paragraph>
        Several approaches have been proposed in the literature for computing the extensions of abstract argumentation frameworks using ASP solvers, e.g., [76], [47], [53], [99]. All these approaches rely upon the mapping of an argumentation framework into a logic program whose answer sets are in one-to-one correspondence with the extensions of the original abstract argumentation framework. The approaches differ in the kinds of extensions they focus on, and in the mappings and correspondences they define. For an exhaustive overview, we refer the reader to [93]. In Section 4, we will provide the specific features of the ASP solvers which participated in the competition.
       </paragraph>
      </section>
      <section label="2.3.2">
       <section-title>
        Satisfiability solvers
       </section-title>
       <paragraph>
        A propositional formula over a set of Boolean variables is satisfiable iff there exists a truth assignment of the variables such that the formula evaluates to true. Checking whether such an assignment exists is the satisfiability (SAT) problem [101]. SAT solvers largely owe their success to efficient search heuristics (e.g., [75]) and conflict-driven back-tracking [86].
       </paragraph>
       <paragraph>
        Let us consider the standard setting of propositional logic over a set {a mathematical formula}P={a,b,c,…} of propositional atoms, and the standard logical connectives {a mathematical formula}∧,∨,¬, denoting conjunction, disjunction, and negation, respectively. A literal is an atom {a mathematical formula}p∈P or its negation ¬p. A clause C is a set of literals representing the disjunction {a mathematical formula}⋁l∈Cl. A propositional formula in Conjunctive Normal Form (CNF) is a conjunction of clauses. An interpretation {a mathematical formula}I:P→{true,false} maps atoms to Boolean values. An interpretation {a mathematical formula}I satisfies a formula φ ({a mathematical formula}I⊨φ) if φ evaluates to {a mathematical formula}true under the assignment determined by {a mathematical formula}I. A formula φ is satisfiable if there exists an interpretation {a mathematical formula}I such that {a mathematical formula}I⊨φ, and unsatisfiable otherwise. A satisfiability solver is a decision procedure which determines whether a given formula φ, in CNF, is satisfiable or not. State-of-the-art SAT solvers are capable of solving instances with hundreds of thousands of literals and clauses. SAT solvers operate in the following way: conflict clauses derived from a previous instance φ can be retained in a subsequent run of the solver on a formula ψ if {a mathematical formula}φ⊆ψ. Moreover, the back-tracking capabilities of SAT solvers make it possible to fix a tentative assignment (or assumption, respectively) for a subset S of A in form of a conjunction of literals over S. Assumptions can be discarded in subsequent calls. This capability to perform iterative calls is crucial to the performance of the SAT-based algorithms proposed for abstract argumentation problems.
       </paragraph>
       <paragraph>
        One method for using SAT solvers in abstract argumentation is to reduce the argumentation problem at hand to a formula in propositional logic. Reductions of this kind make sophisticated SAT solvers amenable for the field of argumentation. Using classical propositional logic to evaluate abstract argumentation frameworks was first advocated by [7] and then extended to quantified propositional logic [1], [49] to efficiently reduce abstract argumentation problems with complexity beyond NP. Several implementations show how modern SAT technology can be used for solving such hard problems in the area of argumentation. In Section 4, we will provide the specific features of the SAT solvers which participated to the competition.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Technical setup and evaluation
     </section-title>
     <paragraph>
      In this section, we give an overview on how the benchmarks for the competition were generated (Section 3.1), describe the evaluation measures (Section 3.2), and give some details on the execution of the competition (Section 3.3).
     </paragraph>
     <section label="3.1">
      <section-title>
       Benchmarks
      </section-title>
      <paragraph>
       The availability of real-world benchmarks for argumentation problems was, at the point of time of the competition, quite limited, some few exceptions are [20], [19] or AIFdb.{sup:1} However, these benchmarks are tailored towards problems of argument mining [102] and their representation as abstract argumentation frameworks usually lead to topologically simple graphs, such as cycle-free graphs. These kinds of graphs are not suitable for comparing the computational performance of solvers for abstract argumentation problems, as, e.g., all classical semantics coincide with grounded semantics on cycle-free graphs [35], for which all considered computational problems are tractable, cf. Section 2.3. Another possibility to obtain benchmark examples is to utilize other problem areas such as automatic planning, satisfiability, or other reasoning problems and encode these problems as abstract argumentation frameworks. Although these problem transformations generally lead to complex and challenging graphs, they are all structurally similar. As a consequence, solvers optimized for specific graph-theoretic features may have an advantage over other solvers. In order to be able to distinguish the computational performance on all considered semantics and on different graph-theoretic features, we decided to use artificially generated graphs as benchmarks, in line with the preliminary performance evaluation of [10].
      </paragraph>
      <paragraph>
       This graph generator aims at generating graphs with many stable extensions (and therefore also many complete and preferred extensions). Graphs generated by this generator pose huge combinatorial challenges for solvers addressing the computational tasks of determining (skeptical or credulous) acceptance of arguments and enumerating extensions.After having determined the number of arguments “A” as in GroundedGenerator, this generator first identifies a set of arguments grounded to form an acyclic subgraph which will contain the grounded extension. Afterwards another subset M (a candidate for a stable extension) of arguments is randomly selected and attacks are randomly added from some arguments within M to all arguments neither in M nor grounded. This process is repeated until a number of desired stable extensions M is reached.C:SccGeneratorThe third graph generator aims at generating graphs which feature many strongly-connected components and are therefore challenging for solvers which do not rely on decomposition techniques [72].After having determined the number of arguments “A” as in GroundedGenerator, in a first step these arguments are partitioned (with a uniform distribution) into a given number N of components {a mathematical formula}C1,…,Cn. Within each component attacks are added randomly with a high probability given as a parameter (and thus likely forming a strongly connected component). In-between components attacks are randomly added with less probability (also given as parameter), but only from a component {a mathematical formula}Ci to {a mathematical formula}Cj with {a mathematical formula}i&gt;j (in order to avoid having few large strongly connected components). The source code for the above generators can be found in the source code repository{sup:2} of probo[25], the benchmark suite used to run the competition, which will be discussed in more detail in Section 3.3. In contrast to the preliminary performance evaluation of [10], we decided to use these proprietary graph generators, instead of well-known graph models from network theory such as the Erdös–Rényi [52], Watts–Strogatz [100], or Barabási–Albert [3] models, because of the following reason. Graph models from network theory are designed to explain the topology of e.g. social networks. An important concept often (indirectly) implemented in graph models is that of triangle closure, i.e., the tendency of nodes directly connecting to the neighbors of its neighbors (as in the saying “the friend of my friend is also my friend”). From the perspective of challenging benchmarks for abstract argumentation, this feature often trivializes computation. Initial experiments suggest that the generated graphs contain empty or very small grounded extensions, usually no stable extensions, and very few and small complete and preferred extensions. The latter observation is also due to the fact that these graph models aim at modeling the “small world” property of many real-world graphs.{sup:3} This leads to many arguments directly or indirectly being in conflict with each other.
      </paragraph>
      <paragraph>
       For each of the three benchmark generators A, B, and C, we generated 72 argumentation graphs of different sizes and partitioned each set into three equal-sized subsets of small, medium, and large instances. This results in 9 test sets, each having 24 argumentation graphs (see Appendix B for the exact numbers of arguments and attacks). We conducted some preliminary experiments using alpha versions of available solvers in order to check whether these graphs are not too easy or too hard. There we discovered that the test set corresponding to the largest argumentation graphs generated by B was too difficult for every solver. As a consequence, the whole test set was removed from the evaluation. All other test sets seemed to be appropriate to be used for the actual competition. Therefore, the 192 instances used for the evaluation in the competition consisted of
      </paragraph>
      <list>
       <list-item label="•">
        24 small-sized argumentation graphs from generator A (test set 1)
       </list-item>
       <list-item label="•">
        24 medium-sized argumentation graphs from generator A (test set 2)
       </list-item>
       <list-item label="•">
        24 large-sized argumentation graphs from generator A (test set 3)
       </list-item>
       <list-item label="•">
        24 small-sized argumentation graphs from generator B (test set 4)
       </list-item>
       <list-item label="•">
        24 medium-sized argumentation graphs from generator B (test set 5)
       </list-item>
       <list-item label="•">
        24 small-sized argumentation graphs from generator C (test set 6)
       </list-item>
       <list-item label="•">
        24 medium-sized argumentation graphs from generator C (test set 7)
       </list-item>
       <list-item label="•">
        24 large-sized argumentation graphs from generator C (test set 8)
       </list-item>
      </list>
      <paragraph>
       All argumentation graphs of the competition can be downloaded from the competition website.{sup:4}Appendix B gives some more detailed statistics on the benchmark graphs. For a discussion on the relationships between these statistics and argumentation-specific properties see [95].
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Evaluation measures
      </section-title>
      <paragraph>
       The aim of the competition was to measure and compare the computational performance of the submitted solvers on solving instances of the problems presented in Section 2.3. For the problems SE (compute some extension) and EE (compute all extensions) we used every one of the 192 argumentation graphs (see previous section) as an individual instance for each semantics. For the problems DS (decide skeptical acceptance) and DC (decide credulous acceptance) we randomly selected three arguments from every argumentation graph, yielding in total 576 instances for each semantics.
      </paragraph>
      <paragraph>
       For each instance of a track, a solver was given 10 minutes time to compute the answer. In case of a timeout or a wrong answer, the solver received zero points for this instance.{sup:5} If it gave the correct answer within the time limit, it received one point and the actual runtime for solving the instance was saved separately. For each track, the cumulative number of points was used as the main ranking criterion (solvers which received more points were ranked higher than solvers with less points). If two or more solvers reached the same number of points, their cumulative runtimes on all correctly solved instances were compared to break ties (solver with smaller total runtime were ranked higher than solvers with larger total runtime). This procedure results in a total of 16 rankings of the solvers, one for each track.
      </paragraph>
      <paragraph>
       For those solvers, which supported all 16 tracks of the competition, we aggregated their scores in the individual tracks to obtain a global ranking using Borda count. For that, every solver received one point for every first place in any ranking, two points for every second place in any ranking, and so on. A global ranking was obtained by ordering the resulting total number of points from smallest to largest.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Competition details
      </section-title>
      <paragraph>
       The competition was realized using the benchmark framework probo[25], which provides the possibility to run the instances on the individual solvers, verify the results, measure the runtime, and log the results accordingly. The software probo is written in Java and requires the implementation of a simple command line interface from the participating solvers.{sup:6}
      </paragraph>
      <paragraph>
       All benchmark graphs were made available in two file formats. The trivial graph format{sup:7} (TGF) is a simple representation of a directed graph which simply lists all appearing vertices and edges. The ASPARTIX format (APX) [47] is an abstract argumentation-specific format which represents an argumentation framework as facts in a logic programming-like way.
      </paragraph>
      <paragraph>
       In order to verify the answers of solvers, the solutions for all instances were computed in advance using the Tweety libraries for logical aspects of artificial intelligence and knowledge representation[91]. Tweety contains naive algorithms for all considered semantics that implement the formal definitions of all semantics in a straightforward manner and thus provides verified reference implementations for all considered problems.
      </paragraph>
      <paragraph>
       Besides serving as the benchmark framework for executing the competition, probo also contains several abstract classes and interfaces for solver specification that could be used by participants in order to easily comply with the solver interface specification. We also provided a tutorial{sup:8} and a generic shell-script{sup:9} that implements the solver interface specification, in order to enable participants to implement their solvers in a way that is compatible with the competition requirements.
      </paragraph>
      <paragraph>
       The competition itself was executed on a cloud computing platform available at the University of Koblenz–Landau, which provides 320 cores with 2.9 GHz each and 2.2 TB of usable RAM. For each test set of benchmark graphs we used a single virtual machine with 1 CPU and 8 GB of RAM to run all tracks on the set. The results for all tracks were aggregated afterwards.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Participants
     </section-title>
     <paragraph>
      In this section, we provide a description of the solvers which participated in the competition, and we classify them with respect to their supported tracks. Note that the solvers are numbered according to their registration number.
     </paragraph>
     <paragraph>
      Table 2 gives an overview on the participating solvers, and their supported tracks.
     </paragraph>
     <paragraph>
      Table 3 gives some further information on the solvers, i.e., development country, programming language and paradigm, total number of lines of code, and a reference to contributions describing the solver in more detail. Most of the solvers have been developed in Europe with the exception of the ZJU-ARG solver from China and the ArgTools solver from Jordan. Moreover, we can note that solvers have been developed mainly using logic and object-oriented programming languages.
     </paragraph>
     <paragraph>
      Table 4 lists the solvers' license information (when available), and provides a link to their source code repositories. Most of the repositories are available under the GNU GPL license, while some of them chose more specific licenses like the MIT license. In general, however, the source code of all solvers participating in the competition has been made available for research purposes, which was also a requirement for participating.
     </paragraph>
     <paragraph>
      In the following, we give some details on the individual solvers that participated in the competition. For the complete system descriptions, we refer the reader to [92].
     </paragraph>
     <section>
      <section-title>
       LabSATSolver
      </section-title>
      <paragraph>
       The LabSAT solver [17] solves all tasks of the competition wrt. all semantics. It encodes the labeling approach [21] as a boolean satisfiability problem (SAT) following the proposal of Cerutti and colleagues [23]. Roughly, the approach proposed in [23], called PrefSAT, is a depth-first search in the space of complete extensions to identify those that are maximal, namely preferred extensions and enumerate them. Each step of the search process requires the solution of a SAT problem through the invocation of a SAT solver. The algorithm is based on the idea of encoding the constraints corresponding to complete labelings of an {a mathematical formula}AF[21] as a SAT problem, and then iteratively producing and solving modified versions of the initial SAT problem according to the needs of the search process. For more details about the encoding, we refer the reader to [23]. Complete and preferred extensions are computed by the LabSAT solver using the PrefSAT approach [23]. To compute the stable extension, additional clauses are added to the SAT solver (i.e., the label undec is excluded). The SAT solver used in LabSAT is lingeling [9]. It is worth noticing that the grounded semantics is computed without the use of the SAT solver, relying on a Java implementation of the algorithm proposed in [74].
      </paragraph>
     </section>
     <section>
      <section-title>
       ArgSemSAT
      </section-title>
      <paragraph>
       The ArgSemSAT solver [26], [23], [28], [29] implements a collection of algorithms for solving all tasks of the competition wrt. all semantics. ArgSemSAT-1.0 encodes the constraints corresponding to complete labelings of an {a mathematical formula}AF as a SAT problem, and then iteratively produces and solves modified versions of the initial SAT problem according to the needs of the search process. As for the LabSAT solver, also ArgSemSAT implements the PrefSAT approach [23] described above, for enumerating the preferred extensions. PrefSAT first solves a SAT problem whose solutions correspond to the complete extensions of an {a mathematical formula}AF, and second, a hill-climbing approach is used to find a maximal wrt. set inclusion complete extension, i.e., a preferred extension. Already computed extensions are excluded from subsequent search steps. In addition, ArgSemSAT-1.0 implements the SCC-P algorithm [24] exploiting the SCC-recursiveness schema [5] using the partial order of strongly connected components (SCCs). In SCC-P, the extensions of the frameworks restricted to the SCC not receiving any attack are computed and combined together. Then, each SCC which is attacked only by such unattacked SCCs is considered: the extensions of such a SCC are computed and merged with those already obtained. Finally, the subsequent (wrt. the partial order) SCCs are considered until no remaining SCCs are left. The schema is recursive, and the base of the recursion is reached when there is only one SCC: in this case a solver similar to PrefSAT is called. It is worth noticing that SCC-P resulted to be more efficient than PrefSAT on {a mathematical formula}AFs with numerous SCCs. ArgSemSAT-1.0 exploits the Glucose solver [2] and the PrecoSAT{sup:10} solver.
      </paragraph>
     </section>
     <section>
      <section-title>
       ArgTools
      </section-title>
      <paragraph>
       The ArgTools solver (Argumentation Tools) [79], [78] is a system based on backtracking algorithms for solving all tasks of the competition wrt. all semantics. The backtracking algorithms of ArgTools are based on exploration of an abstract binary search tree. The two key features of ArgTools are i) to enhance the backtracking search for sets of acceptable arguments by a new pruning strategy, called the global looking-ahead strategy, and ii) to set out a backtracking-based approach to decide acceptance under different semantics, i.e., whether an argument is in some/all set(s) of acceptable arguments of a given {a mathematical formula}AF, without necessarily enumerating all such sets. Roughly, the global looking-ahead pruning strategy enables a backtracking procedure during traversing the search space to regularly look-ahead for dead-ends, i.e., for paths that do not lead to solutions, early enough such that considerable time is saved. For more details about this strategy, we refer the reader to [80].
      </paragraph>
     </section>
     <section>
      <section-title>
       CEGARTIX
      </section-title>
      <paragraph>
       The CEGARTIX (Counter-Example Guided Argumentation Reasoning Tool) solver [45], [43] supports the computation of credulous acceptance under semi-stable, and stage semantics, the skeptical acceptance under preferred, semi-stable, and stage semantics, it returns an arbitrary preferred extension, and enumerates all preferred extensions. Note that only the part regarding the preferred semantics is relevant for the participation in the competition. Each step in the exploration is delegated to a complete Boolean satisfiability (SAT) solver. The strategy exploited by this solver consists first in the identification of first-level fragments (NP/coNP layer) of second-level reasoning tasks for two main reasons: i) such fragments present particular sources of complexity of the considered problems, and ii) NP fragments can be efficiently reduced to the SAT problem. CEGARTIX uses the NP decision procedures as NP oracles in an iterative way. For problems complete for the second level of the polynomial hierarchy, this leads to general procedures which, in the worst case, require an exponential number of calls to the NP oracle, which is indeed unavoidable under the assumption that the polynomial hierarchy does not collapse. Nevertheless, such procedures can be designed to behave adequately on input instances that fall into the considered NP fragment and on instances for which a relatively low number of oracle calls is sufficient. CEGARTIX exploits current state-of-the-art conflict-driven clause learning (CDCL) SAT-solver technology as the underlying NP oracle. CEGARTIX employs the CDCL SAT-solver Minisat [46]. For more details about the NP decision procedure, we refer the reader to [43].
      </paragraph>
     </section>
     <section>
      <section-title>
       Dungell
      </section-title>
      <paragraph>
       The Dungell solver [97], [98] supports the computation of some and all grounded, complete, preferred and stable extensions. The characterizing feature of Dungell consists in providing a solver that is as close to the mathematical definitions as possible. The rationale behind this feature is to tackle the problem of implementing structured argumentation models and their translations by providing a framework that allows implementation close to the mathematical specification and thus facilitates checking and formal proof of properties. Dungell implements two steps in the pipeline: first, it allows for the translation of a Carneades [59] structured argumentation framework into an abstract one, and second, it computes the extensions for the grounded, complete, preferred and stable semantics. Given an {a mathematical formula}AF, it is possible to verify whether a list of arguments is conflict-free by checking that the list of attacks between those arguments is empty. Acceptability of an argument with respect to a set of arguments in an {a mathematical formula}AF can be determined by verifying that all its attackers are in turn attacked by an attacker in that set. This solver is one of the very few ones using functional programming, specifically Haskell, for the implementation of structured and abstract models of argumentation.
      </paragraph>
     </section>
     <section>
      <section-title>
       ZJU-ARG
      </section-title>
      <paragraph>
       The ZJU-ARG solver [62], [70] enumerates all preferred extensions, and the grounded extension of an {a mathematical formula}AF. It adopts a divide-and-conquer strategy. As for the LabSATSolver, the grounded extension of an {a mathematical formula}AF is computed directly by following the algorithm proposed by [74]. The main feature of the ZJU-ARG solver is the application of the notion of modularity to an argumentation framework, close to the SCC concept, as for other solvers like ArgTools. To overcome the fact that the efficiency of the SCC approach is highly limited by the maximal SCC of an {a mathematical formula}AF, the solver implements a solution by exploiting the most skeptically rejected arguments of an {a mathematical formula}AF. Roughly, given an {a mathematical formula}AF, its grounded labeling [21] is first generated. Then, the attacks between the undecided arguments and the rejected arguments are removed. It turns out that the modified {a mathematical formula}AF has the same preferred labeling as the original {a mathematical formula}AF, but the maximal SCC in it could be much smaller than that of the original {a mathematical formula}AF. Since the ZJU-ARG solver adopts a divide-and-conquer strategy without employing more efficient algorithms to compute the semantics of each sub-framework, its efficiency highly depends on the topologies of the argumentation frameworks in input.
      </paragraph>
     </section>
     <section>
      <section-title>
       ASPARTIX-V
      </section-title>
      <paragraph>
       The ASPARTIX-V solver (Answer Set Programming Argumentation Reasoning Tool–Vienna version) [85], [48] supports the computation of skeptical acceptance under preferred semantics, returns a single preferred extension, and enumerates all preferred extensions. Together with an ASP encoding for preferred semantics, the answer-sets are in a 1-to-1 correspondence with the preferred extensions of the given argumentation framework {a mathematical formula}AF. ASP solvers themselves offer enumeration of all answer-sets and returning an arbitrary one. In ASPARTIX-V, a single program is used to encode a particular argumentation semantics, while the instance of an argumentation framework is given as an input database. ASPARTIX-V improves the performances of its predecessor ASPARTIX{sup:11} as follows. While preferred semantics is encoded as a disjunctive logic program making heavy use of so-called loop constructs in ASP in the ASPARTIX system, ASPARTIX-V is able to do without and uses conditional literals for enhancing the performance. Intuitively, conditional literals allow to use, e.g., a dynamic head in a disjunctive rule that contains a literal iff its condition is true. The loop constructs can be avoided by alternative characterizations of preferred semantics. ASPARTIX-V employs the so-called saturation technique: in the encodings for preferred semantics, a first “guess” is made for a set of arguments in the {a mathematical formula}AF, and then the solver verifies if this set is admissible. To verify if this set is also a subset-maximal admissible one, ASPARTIX-V performs a second guess and verifies if this second guess is an admissible set that is a superset of the first guess. The idea is to keep this second guess small to overcome computational overhead. Additional rules then verify if the witness set represents an admissible set that may be combined with the first guess to result in a larger admissible set. If this is the case, the first guess does not represent a preferred extension. The underlying ASP solver is Clingo 4.4 [56].
      </paragraph>
     </section>
     <section>
      <section-title>
       CoQuiAAS
      </section-title>
      <paragraph>
       The CoQuiAAS solver [66], [67] solves all tasks of the competition wrt. all semantics by exploiting constraint programming techniques. More precisely, it takes advantage of the encodings proposed by [7]. CoQuiAAS deals with encodings in Negation Normal Form (NNF) formulae, meaning some propositional formulae where the negation operator is only applied on variables. As CoQuiAAS uses SAT solvers, which are only able to tackle propositional formulae in CNF, a translation step from NNF to CNF is required between the encodings which exist in the literature and the ones that used in the system. An interesting question for SAT solvers is to determine an interpretation which maximizes the number of satisfied constraints: this problem is called Max-SAT. We can generalize this problem, giving a weight to each constraint (Weighted Max-SAT), and if some constraints have an infinite weight (i.e., they have to be satisfied), then the problems are said to be “partial” (Partial Max-SAT). CoQuiAAS uses CNF formulae to solve problems from the first level of the polynomial hierarchy, and some encodings in the Partial Max-SAT formalism for higher complexity problems. Discovering an optimal solution of a Max-SAT instance allows to determine a set of constraints from the initial formula which is consistent, such that adding any other constraint from the initial problem makes this new problem inconsistent: a set of constraints which has this property is called a maximal satisfiable subset (MSS). The optimal solutions of the Max-SAT problem are only a subset of all the MSS of a formula. The solver approaches argumentation semantics exploiting SAT and MSS extraction. CoQuiAAS incorporates the software coMSSExtractor [60] to perform the constraint-based process.
      </paragraph>
     </section>
     <section>
      <section-title>
       ASPARTIX-D
      </section-title>
      <paragraph>
       The ASPARTIX-D solver (Answer Set Programming Argumentation Reasoning Tool–Dresden version) [54] is a collection of ASP encodings together with dedicated solvers to solve all tasks of the competition wrt. all semantics. The general approach of ASPARTIX-D is the same the approach of ASPARTIX-V described above but differs in several details. In particular, the ASP encodings used by ASPARTIX-D are those described in [48] and the optimization applied has been presented in [42]. The main aim of the solver is to find the most suitable encodings and solver configuration. ASPARTIX-D exploits the potassco ASP solvers.{sup:12}
      </paragraph>
     </section>
     <section>
      <section-title>
       ConArg
      </section-title>
      <paragraph>
       The ConArg (Argumentation with Constraints) solver (version 2.0) [13], [15] allows to enumerate all conflict-free, admissible, complete, stable, grounded, preferred, semi-stable, ideal, and stage extensions, to return one extension given one of these semantics, to check the credulous and skeptical acceptance for the conflict-free, admissible, complete, and stable semantics. It is a constraint programming tool where the properties of the semantics are encoded into constraints, and arguments are assigned to 1 (true) if they belong to a valid extension for that semantics, and 0 otherwise. Searching for solutions takes advantage of classical techniques, such as local consistency through constraint propagation, different heuristics for trying to assign values to variables, and a complete search-tree with branch-and-bound. To map an argumentation framework {a mathematical formula}AF to a Constraint Satisfaction Problem (CSP),{sup:13} which is defined by a set of constraints defined over the a set of variables each with domain D, ConArg defines a variable for each argument in the {a mathematical formula}AF, and each of these arguments can be taken or not in an extension, i.e., the domain of each variable is {a mathematical formula}D={1,0}. As an example, preferred extensions are found by assigning as more arguments as possible to 1 while searching for complete extensions. The solver exploits a toolkit called Gecode 4.4.0{sup:14} defined for developing constraint-based systems and applications.
      </paragraph>
     </section>
     <section>
      <section-title>
       GRIS
      </section-title>
      <paragraph>
       The GRIS (Gabbay–Rodrigues Iterative Solver) solver [83], [84] allows to produce one or all of the extensions of the argumentation framework under the grounded and preferred semantics, and given an argument a to decide whether it is accepted credulously or skeptically according to one of these two semantics. The peculiarity of the GRIS solver is that it works with numerical argumentation networks where arguments are given initial values in the interval {a mathematical formula}[0,1] from which equilibrium values are calculated iteratively yielding traditional extensions through the use of a characterization result [83]. An argumentation framework is represented in GRIS by means of a set of equations. As for ArgTools and the ZJU-ARG solver, also GRIS exploits strongly connected components to compute the extensions. More precisely, the solver starts by computing the strongly connected components of the network and arranging them into layers that can be used in successive computation steps, following the idea of [71]. Once the layers are computed, the solver can identify the deepest layer of computation needed according to the layer depth of the input argument and this can be used to terminate the computation of decision problems as early as possible.
      </paragraph>
     </section>
     <section>
      <section-title>
       ASGL
      </section-title>
      <paragraph>
       The ASGL solver [89] solves all tasks of the competition wrt. all semantics. ASGL uses an extension-based encoding for solutions. As for ConArg, also ASGL casts the argumentation framework as a CSP. Constraints are formalized in a so-called computation space and the algorithm is based on propagation methods to reach a fixpoint. The task of computing some preferred extension is implemented in ASGL like a classical optimization problem with branch-and-bound search (already part of standard Gecode). As soon as one solution is found, all further solutions are constrained to be better than the current solution. If no more solution can be found, the current solution is maximal. To efficiently enumerate all preferred extensions, a filtering over all complete extensions for maximality is performed. The ASGL solver, in one out of the two solvers participating to the Competition, that were written using a functional language (Lisp). It also features an interface to the Lingeling SAT Solver as an alternative solver backend. Also ASGL, together with ConArg, exploits the Gecode generic CSP solver library.
      </paragraph>
     </section>
     <section>
      <section-title>
       LamatzSolver
      </section-title>
      <paragraph>
       The LamatzSolver system [68] is a solver for computing the grounded extension of argumentation frameworks based on a direct implementation of the characteristic function[35]. Sets like attacks are implemented as a HashMap in Java. More precisely, the computation of the grounded extension is addressed along with the following steps: it checks if the HashMap typeZero (containing unattacked arguments) is empty. If the answer is positive, than an empty HashMap called the grounded is returned, otherwise the algorithm copies each argument of typeZero to the HashMap grounded. The size of grounded is stored in a parameter prev and for each argument the defended arguments will be determined and added to the grounded. According to this process, the algorithm keeps track of the arguments attacked by the arguments in grounded. These arguments are stored in a HashMap out, and the attacks of these arguments are candidates for the grounded extension. The algorithm checks if all attackers of a candidate are defeated. These steps are repeated for the grounded until it does not grow anymore. Finally, the grounded Hash Map is returned.
      </paragraph>
     </section>
     <section>
      <section-title>
       ProGraph
      </section-title>
      <paragraph>
       The ProGraph solver [61] allows to compute some extension and decides whether an argument is credulously inferred, both with respect to the stable semantics. The key feature of the ProGraph solver is that of relying on bipartite graphs. More precisely, the set of arguments is partitioned in two classes: in and out. The idea behind is that determining an extension which attacks every argument which is not in that extension can be reduced to a relaxed partitioning problem in which the initial set of arguments is split in two partitions, with the arguments from the second partition being free to attack each other. Arguments are sorted such that they will be placed from the one who attacks the most to the one who attacks the less arguments. The algorithm starts by picking a non-attacked argument and adds it to the attackers extension, and then checks if any of the arguments attacked by the selected one is in the first partition. If this is the case, the algorithm starts backtracking. Otherwise, the arguments attacked by the current argument are added to the second partition. These steps are repeated until all arguments are partitioned or until all paths fail. If only attacked arguments are left, the algorithm chooses one of them and supposes it is not attacked. A verification step stops the algorithm if at some point the attacker is to be placed in the second partition.
      </paragraph>
     </section>
     <section>
      <section-title>
       DIAMOND
      </section-title>
      <paragraph>
       The DIAMOND solver [51], [50] solves all tasks of the competition wrt. all semantics. DIAMOND employs the declarative programming paradigm of ASP, and the knowledge representation languages implemented in the solver are Abstract Dialectical Frameworks (ADFs) [16], which are a generalization of {a mathematical formula}AFs. In addition to the computation of the semantics of an {a mathematical formula}AF, DIAMOND can also compute the semantics for (bipolar) ADFs in various different input formats, decide whether a given ADF is bipolar, or transform an ADF from one representation into another. The encodings for DIAMOND are built in a modular way. To compute the models of an ADF with respect to a semantics, different modules need to be grounded together to get the desired behavior. As for other solvers described above, DIAMOND exploits the potassco ASP solvers.{sup:15}
      </paragraph>
     </section>
     <section>
      <section-title>
       Carneades
      </section-title>
      <paragraph>
       The Carneades solver [58], [59] solves all tasks of the competition wrt. all semantics. Note that Carneades originally included an implementation of a solver for Dung-like abstract argumentation frameworks, using grounded semantics, despite the focus of the Carneades project has not been abstract argumentation, but rather structured argumentation. The implementation closely follows high-level specifications of abstract argumentation frameworks, and has not been optimized with the exception of the grounded semantics where the implementation keeps track of whether a mutable labeling has changed, in its main loop, and exits the loop when no changes are made, without having to explicitly test whether two labelings are equivalent. The solver's procedures are implemented for finding the first subset of arguments which satisfy a given predicate and for applying some procedure to each subset. Using functions implementing predicates for complete and stable extensions, Carneades finds the first or all complete extensions and filter the complete extensions to find one or more which are also stable. Argument sets are represented as Hash tables, from arguments to Boolean values.
      </paragraph>
     </section>
     <section>
      <section-title>
       prefMaxSAT
      </section-title>
      <paragraph>
       The prefMaxSAT solver [94], [24] allows to compute the extension enumeration problem for the preferred semantics. It implements an encoding of preferred extensions search using unweighted MaxSAT. The algorithm exploited in prefMaxSAT is based on the idea of encoding the constraints corresponding to admissible labelings of an {a mathematical formula}AF as a MaxSAT problem, and then iteratively producing and solving modified versions of the initial problem. If at any one step a variable assignment that maximally satisfies the formula is returned, the corresponding labeling is saved in the list of found preferred extensions. Then a hard clause for eliminating the solution is added to the formula and the process is repeated. If no further solution could be found, prefMaxSAT ends and provides the set of found preferred extensions. Each step of the search process requires the solution of a MaxSAT problem. The {a mathematical formula}AF is encoded in a CNF and is then provided to the MaxSAT solver. If a variable assignment that maximally satisfies the formula is returned, then i) the corresponding labeling is saved in the list of found preferred extensions; ii) a clause for eliminating the solution is added to the CNF; iii) a clause forcing to include different arguments is added to the CNF, and finally, iv) the process is repeated. If the MaxSAT solver returns that no variable assignment satisfies the constraints, prefMaxSAT ends and provides the set of found preferred extensions. As for ArgSemSAT, also prefMaxSAT exploits the Glucose solver [2].
      </paragraph>
     </section>
     <section>
      <section-title>
       ASSA
      </section-title>
      <paragraph>
       The {a mathematical formula}ASSA solver [63], [64] computes one or all extensions and decide whether an argument is credulously or skeptically inferred with respect to the stable semantics. The solver implements an approach based on mathematical matrix operations to solve abstract argumentation problems. The system first creates a matrix representation of an {a mathematical formula}AF. Then, all possible instances of the selected arguments are created and combined into another matrix S. Based on matrix operations, and more specifically, on left and right matrix multiplication, it is possible to navigate inside the {a mathematical formula}AF to find which arguments attack the other arguments and which arguments are under attack. By constructing a matrix multiplication, it is possible to determine whether a given set of arguments is conflict-free. Using this method, all conflict-free sets are extracted, and based on some comparison to the system output matrices and the matrix S, the system is able to find all stable extensions.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Results and analysis
     </section-title>
     <paragraph>
      We now report on the results of the competition, which evaluated the participating solvers from Section 4 using the methodology described in Section 3.{sup:16}Table 5, Table 6, Table 7, Table 8 show the obtained rankings of all solvers per track. Each table gives the rank of the solver per semantics, the number of instances where the solver had a timeout (column “#TO”), the number of incorrectly classified instances (column “#−”), the number of correctly classified instances (column “#+”), and the total runtime for all classified instances (column “RT in ms”). The column “Significant” indicates whether the performance of a solver is significantly superior to the solver ranked right after it, according to a standard Student's T-Test with significance level 95%, cf. [18]. A “YES” indicates that the solver in the row is indeed significantly superior than the next one, a “NO” indicates that is not the case, and a “–” indicates that a significance test is not applicable—and not necessary—as the next solver correctly solved strictly less instances. Solvers are grouped by the number of correctly classified instances and ranked in each group by runtime. Therefore, note that the column on runtime is not sorted across the whole table, as solvers, which solved fewer instances within the time limit, may have a smaller total runtime on the remaining instances as solvers which solved more instances. Furthermore, solvers with identical number of solved instances and identical runtime performance are ranked equally. Table 9 shows the aggregated ranking of solvers participating in all sixteen tracks, where the column “Borda count” gives the sum of all ranks of the particular solver in all tracks.
     </paragraph>
     <paragraph>
      Due to the results depicted in Table 9, the International Competition of Computational Models of Argumentation awarded the following solvers with first, second, and third place, respectively:
     </paragraph>
     <list>
      <list-item label="1.">
       CoQuiAAS
      </list-item>
      <list-item label="2.">
       ArgSemSAT
      </list-item>
      <list-item label="3.">
       LabSATSolver
      </list-item>
     </list>
     <paragraph>
      Furthermore, the solver Cegartix additionally received the award “Honorable mention” as it achieved the two first places and one second place in the three tracks it participated in (SE-PR, EE-PR, DS-PR).
     </paragraph>
     <paragraph>
      The statistics on timeouts and runtime performances given in Table 5, Table 6, Table 7, Table 8 show that there is a large diversity between solvers. For example, from the results of the problem SE-PR (Table 5) one can see that there are solvers without any timeout (places 1–3) and solvers not solving any instance within the time limit (place 12). Moreover, the first place (Cegartix) for this track achieved an average runtime of roughly 4,5 seconds on any instance, which is way below the timeout of 10 minutes. Similar observations can be made for the other tracks. Furthermore, many solvers performed quite differently in different tracks, compared to other solvers. For example, solver no. 16 (Carneades) achieved second place for all tracks related to grounded semantics, but only last place in all other tracks. This behavior stems from the fact that some solvers have been developed for a specific semantics (grounded semantics for Carneades), and have not been tailored towards other semantics.
     </paragraph>
     <paragraph>
      All four tracks related to stable semantics have been won by ASPARTIX-D, often with great lead to the second place. For example, for the problem EE-ST it solved one more instance than the second place (ArgSemSAT) but still needed only roughly a third of the total time, cf. Table 6. ASPARTIX-D is based on reductions of abstract argumentation problems to answer set programming—see also Section 4—and therefore exploits the equivalence of stable semantics in abstract argumentation to answer set semantics in a direct way. Note, that also the solver DIAMOND is based on an answer set programming reduction. In contrast to ASPARTIX-D, its approach is, however, actually a two-level reduction. In a first step, abstract argumentation problems are reduced to an equivalent formalization using Abstract Dialectical Frameworks[16]. In the second step, the latter is then reduced to an answer set program. This overhead is a probable cause for the lower ranking of this solver. In addition, DIAMOND shows the higher total runtime for all incorrect classified instances, meaning that this two-level approach has a serious impact on the performances of the solver. Notice that the second solver for higher total runtime for all incorrect classified instances is ASPARTIX-D, even if the impact on the overall performance of the solver is less significant than for DIAMOND.
     </paragraph>
     <paragraph>
      Despite the exception from above, it can be seen that solvers that rely on a reduction to other established formalisms, such as SAT solving, constraint satisfaction problems, or, as mentioned, answer set programming, performed better than solvers implementing a direct algorithm for abstract argumentation. In fact, the first three places in Table 9 (CoQuiAAS, ArgSemSAT, and LabSATSolver) and the honorable mention Cegartix rely on reductions to (maximum) satisfiability problems and make use of mature SAT solvers for solving argumentation problems, and all first places in all tracks use one of the three reductions mentioned above. Solvers using direct algorithms—i.e. solvers not using any other formalism than abstract argumentation—such as ArgTools and Carneades usually performed below average.
     </paragraph>
     <paragraph>
      Table 10, Table 11 show the performance of the solvers wrt. the different test sets, accumulated over all tracks. For each solver, the column N in each indicates the number of instances solved for each test set (be reminded that each test set contains 24 benchmark graphs and that for DS and DC problems each benchmark graph was tested three times). For each test set generated by the generators A, B, and C the corresponding cells contain the number of incorrectly classified instances and timeouts wrt. the given total number of instances N. Table 10 gives several interesting insights into the behavior of the solvers wrt. different characteristics. For example, considering solver no. 9 (ASPARTIX-D), it can be seen that it had a hard time solving instances generated by the graph generator A (which featured large graphs with a large grounded extension), but was significantly better in solving instances of graph generators B and C (both generated smaller graphs but with a more complex attack structure). However, other solvers such as no. 3 (ArgTools) and no. 10 (ConArg) featured quite the opposite behavior, solving instances of generator A usually easier than instances of B and C. Furthermore, the average behavior of solvers on the different test sets—indicated by the summed values in the last row of the table—is quite homogeneous, where data sets 4 and 5 (generator B) are slightly harder on average. But the individual different behavior of the solvers also justifies the decision to use different graph models and challenging graph features for the competition, as otherwise some solvers would have been at an advantage.
     </paragraph>
     <paragraph>
      Table 12 reports on the percentage of correctly classified instances for each solver for each of the tracks it participated in. We report with {a mathematical formula}0% when the solver participated in the track but without providing any correct answer, and we leave the cell empty when the solver did not participate in that specific track. From this view on the results of the competition it emerges that systems employing SAT-solvers perform better wrt. instance classifications than those employing ASP. Only few systems have participated in tasks where they were unable to provide correct answers, i.e., Carneades, Dungell, and ASSA. It must be noted that the common point of these three systems is of being ad-hoc implementations of abstract argumentation frameworks. These negative results are explained by the fact that these systems take too much time to compute the extensions, and thus they time out before returning any answer, e.g., Carneades is optimized for grounded semantics only.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Lessons learned
     </section-title>
     <paragraph>
      The competition has substantially contributed to the advancement of the state-of-the-art of abstract argumentation solvers, but also made apparent where optimizations and new developments may take root. The best solvers of ICCMA'15 were based on reductions to other formalisms and thus used general multi-purpose tools. Although these solvers benefit from the maturity of e.g., current SAT solvers, the approach of reduction still adds some overhead. For one, translating a possibly huge abstract argumentation problem into an equivalent SAT instance and calling a SAT solver using a specific syntax may be time-consuming, despite the fact that the translation is polynomial from the perspective of computational complexity. Furthermore, the strategies of SAT solvers to solve SAT instances are tailored towards general or “typical” problems expressed in SAT instances. It is not apparent that SAT instances compiled from abstract argumentation problems are included in these sets of problems. To give an analogy, consider the problem of finding shortest paths in a graph. It is possible to phrase this problem as a combinatorial optimization problem and use general-purpose methods such as simulated annealing [69]. However, domain-specific algorithms such as Dijkstra's algorithm [34] clearly outperform these general-purpose methods in their domain.{sup:17} Still, in the competition, the introduced overhead of reduction-based approaches did not significantly outweigh the maturity of the utilized tools. This fact indicates that focused research and development of domain-specific approaches to abstract argumentation may outperform reduction-based approaches in the future. Whilst on the one side, we expect the next generation of solvers to outperform the general purpose SAT-solvers exploited by the systems participating in the competition, on the other side, we should question about the actual necessity of doing so. Applications of such abstract argumentation solvers to concrete usage scenarios are hard to find, and recent results in the argument mining community [19] show that existing graphs extracted from real natural language argumentation interactions, e.g., online dialogues in blogs, do not (almost) present cycles among the arguments. Moreover, such dialogues end up with pretty small graphs (e.g., 40 nodes for an online debate about a specific topic). These observations seem to suggest that the actual need of the community is not to outperform SAT-based solvers. However, it must be noticed that the results provided by the argument mining community are still preliminary, and there is actually a potential in mining for huge argumentation graphs reporting the views of hundreds of users about a certain topic widely discussed on the Web (e.g., including the opinions reported on blogs, social networks, online debate platforms). In conclusion, even if the fact of outperforming existing solvers does not answer a present need in the community, it will in the near future in combination with argument mining techniques.
     </paragraph>
     <paragraph>
      Concerning the semantics, being ICCMA'15 the first edition of such a competition, it was decided to focus on the four standard semantics [35]. Given the results, this appears to be a reasonable choice, as many of the solvers were unable to tackle the whole range of tracks. It would have been useless to provide even more semantics, as it would affected only very few solvers. The next ICCMA competition scheduled for 2017 will consider also ideal, semi-stable and stage semantics, in addition to the four standard semantics.
     </paragraph>
     <paragraph>
      Concerning the input graphs, we believe that we covered a sufficient range of graph structures in order to avoid penalizing some implementations over others. In general, we conclude that one of the main insights of the competition is that there is still great potential for developing new sophisticated algorithmic approaches to abstract argumentation problems.
     </paragraph>
     <paragraph>
      Finally, the ASPARTIX format has emerged as the standard format for the input data, and almost all participants have adapted their solvers to accept such an input format. This is in line with other well-known competitions like for instance the SAT solver competition, where the standard input format is the DIMACS CNF format.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Algorithms of benchmark generators
     </section-title>
     <paragraph>
      We now provide pseudo code for the algorithms used to generate the benchmark graphs of the competition. Algorithm 1 shows the code for GroundedGenerator (Generator A), Algorithm 2 shows the code for StableGenerator (Generator B), and Algorithm 3 shows the code for SccGenerator (Generator C).
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Statistics on benchmark graphs
     </section-title>
     <paragraph>
      Table B.13, Table B.14, Table B.15, Table B.16 give a detailed overview on the structure and properties of the benchmark graphs considered for ICCMA'15. In particular, the table show for each graph of each test set the number of arguments and number of attacks, the average in-degree (=number of attackers), the (global) clustering coefficient CC, the number of strongly connected components (SCCs), its density, the number of complete, preferred, and stable extensions, the size of the grounded extension, and the average size of its complete, preferred, and stable extensions. For an argumentation framework {a mathematical formula}AF=(Arg,→), the global clustering coefficient [73] is defined as (let {a mathematical formula}A⇌B denote “{a mathematical formula}A→Bor{a mathematical formula}B→A” for any {a mathematical formula}A,B∈Arg):{a mathematical formula} In other words, {a mathematical formula}CC(AF) is the ratio of the number of undirected triangles in {a mathematical formula}AF and the number of connected triples of arguments and is thus a value in {a mathematical formula}[0,1]. Large values indicate a high clustering of the arguments. For an argumentation framework {a mathematical formula}AF=(Arg,→), its density is defined as{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>