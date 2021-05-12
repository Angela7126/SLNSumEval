<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Overview and analysis of the SAT Challenge 2012 solver competition.
   </title>
   <abstract>
    Programs for the Boolean satisfiability problem (SAT), i.e., SAT solvers, are nowadays used as core decision procedures for a wide range of combinatorial problems. Advances in SAT solving during the last 10–15 years have been spurred by yearly solver competitions. In this article, we report on the main SAT solver competition held in 2012, SAT Challenge 2012. Besides providing an overview of how SAT Challenge 2012 was organized, we present an in-depth analysis of key aspects of the results obtained during the competition.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The problem of Boolean satisfiability (or propositional satisfiability, SAT) is that of determining whether a given propositional logic formula has a solution, or in other words, is satisfiable [1]. SAT is the canonical NP-complete problem [2] — and among the most fundamental ones in computer science. In addition to its theoretical importance, SAT has become a central declarative approach to formulating and solving combinatorial problems, due to major advances in robust implementations of SAT solvers. Modern SAT solvers are now routinely used in a vast number of different AI and industrial applications, of which hardware and software verification [3], [4], [5] and planning [6], [7] are classical examples. Besides using SAT solvers “directly” to solve a given problem, they are also — often iteratively — employed as core NP-solvers within procedures for more complex decision or optimization problems such as Satisfiability Modulo Theories (SMT) [8], [9], [10], Quantified Boolean Formulas (QBF) [11], [12], Answer Set Programming (ASP) [13], [14], [15], [16], Maximum Satisfiability (MaxSAT) [17], [18], [19], [20], and Minimal Unsatisfiable Subformula (MUS) extraction [21], [22], [23], [24], as well as various SAT-based counterexample-guided abstraction refinement (CEGAR) approaches [25], [26], [11], [12], [27], [28], [29], [30], [31], [32] to solving problems within and beyond NP.
     </paragraph>
     <paragraph>
      The SAT solver competitions (see [33] for an overview, and [34], [35], [36], [37], [38] for individual competition reports) organized during the last 10–15 years have progressed SAT solver technology by providing incentives for pushing the efficiency of SAT solvers further. SAT Challenge 2012 (SC 2012, in short), the main SAT solver competition held in 2012, was organized as a satellite event to the 15th International Conference on Theory and Applications of Satisfiability Testing (SAT 2012, Trento, Italy) and stands in the tradition of the SAT Competitions{sup:5}[33] held yearly from 2002 to 2005 and biannually starting from 2007, and the SAT-Races held in 2006, 2008, and 2010.{sup:6} This article provides an overview of SC 2012. It summarizes the rules and organization, and gives a detailed analysis of the results. This article does not give algorithmic or implementation details of the participating solvers. Readers interested in these details are referred to [39], which includes short descriptions written by the solver developers as part of their SC 2012 submission, as well as descriptions of benchmark instances submitted to SC 2012. General information about SC 2012 is available through the competition website.{sup:7}
     </paragraph>
     <paragraph>
      The rest of this article is organized as follows. We start with an overview of organizational issues of SC 2012, including descriptions of the competition rules, tracks, ranking scheme, and the computing environment used for running the competition (Section 2). We then turn to describing in detail the competition benchmark selection and generation process used for the different benchmark categories (Section 3). We also provide a review of the benchmark selection methods used for various related (constraint solving) competitions. This is followed by statistics on the participating solvers and their authors (Section 4), and a brief overview of the results of SC 2012 in terms of solver rankings (Section 5). An in-depth analysis of the results of the competition is then presented (Section 6). Before we conclude, we briefly outline some lessons learned and suggestions for improvements of future SAT competitions (Section 7),
     </paragraph>
     <section label="1.1">
      <section-title>
       The Boolean satisfiability problem in short
      </section-title>
      <paragraph>
       For each Boolean variable x, there are two literals, x and ¬x. A clause is a disjunction of literals; a formula in conjunctive normal form (CNF) is a conjunction of clauses. A truth assignment α is a function from Boolean variables to {a mathematical formula}{0,1}. A clause C is satisfied by α if {a mathematical formula}α(x)=1 for some literal {a mathematical formula}x∈C, or {a mathematical formula}α(x)=0 for some literal {a mathematical formula}¬x∈C. A CNF formula F is satisfiable if there is an assignment that satisfies all clauses in F, and unsatisfiable otherwise. The NP-complete Boolean satisfiability (SAT) problem asks whether a given CNF formula F is satisfiable.
      </paragraph>
      <paragraph>
       CNF provides the standard input language for most off-the-shelf SAT solvers available today. The DIMACS input format [35], specified in 1996 as a textual representation for formulas in CNF, is now widely used and was adopted by the SAT solver competitions from the beginning. Naturally, any propositional formula can be represented in CNF using a standard linear-size encoding [40] or one of the more intricate CNF encodings developed later (see, e.g., [41]).
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Overview of SAT Challenge 2012
     </section-title>
     <section label="2.1">
      <section-title>
       Organization
      </section-title>
      <paragraph>
       The main organizers of SC 2012 were Adrian Balint (Ulm University, Germany), Anton Belov (University College Dublin, Ireland), Matti Järvisalo (University of Helsinki, Finland), and Carsten Sinz (Karlsruhe Institute of Technology, Germany). Important technical assistance related to the execution of the competition was provided by the SC 2012 Technical Assistants, Daniel Diepold (Ulm University, Germany) and Simon Gerber (Ulm University, Germany).
      </paragraph>
      <paragraph>
       Open calls for participation (for both solver and benchmark submissions) were issued and advertised on various mailing lists. Researchers from both academia and industry were openly invited to submit their solvers — in either source code or binary format — to SAT Challenge 2012. We did not make submission of source code mandatory, as we also wanted to attract solvers from industrial participants, for whom disclosing the source code was not feasible. This followed the tradition of previous SAT-Races, but was different from the previous SAT Competitions that required open source solver submissions.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Participation and evaluation
      </section-title>
      <paragraph>
       An entrant to the SAT Challenge 2012 was a SAT solver submitted in either source code or as a binary. In order to obtain reproducible results, the submitters were asked to refrain from using non-deterministic program constructs to the extent possible. Solvers making stochastic decisions during execution were required to provide a command-line option for random seed initialization.
      </paragraph>
      <paragraph>
       The input and output format requirements were the same as those used for the SAT Competitions and SAT-Races in previous years, specified, e.g., in the 2011 SAT Competition rules, Sections 4.1 and 5.1–5.2.{sup:8} Solvers were required to provide a satisfying truth assignment for satisfiable instances. Any solver that either claimed that an unsatisfiable instance is satisfiable, or produced a truth assignment that does not satisfy an instance, was deemed incorrect and was hence disqualified.
      </paragraph>
      <paragraph>
       Solvers were assessed based on the number of instances solved within the runtime limit. If several solvers solved the same number of instances, as a secondary criterion, the cumulated runtime (CPU time for sequential solvers, wall-clock time for parallel solvers) of all solved instances was used to rank the solvers.
      </paragraph>
      <paragraph>
       The organization committee reserved the right to restrict participation of a solver to certain tracks, to allow only a limited number of solvers submitted by the same person, and to submit their own systems or other systems of interest to the competition. Systems submitted by one of the organizers were not considered in the official ranking and were not eligible to win awards.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Benchmark categories and competition tracks
      </section-title>
      <paragraph>
       All competition entrants had to solve a set of benchmark instances in DIMACS CNF format drawn from a larger pool of instances. This pool included benchmarks from previous SAT Competitions and SAT-Races, as well as additional instances, both submitted in response to the call for benchmarks and benchmarks generated by the organizers. The exact benchmark set was not disclosed in advance. The instances from the benchmark pool used in SC 2012 were manually categorized beforehand into three different categories: application, hard combinatorial, and random; Sections 3 and 7.4 provide more details on the benchmark selection and categorization.
      </paragraph>
      <paragraph>
       The following competition tracks, characterized by the type of benchmarks used in the tracks, were organized.
      </paragraph>
      <paragraph>
       Three main tracks for sequential solvers:
      </paragraph>
      <list>
       <list-item label="•">
        Application SAT+UNSAT: problem encodings (both satisfiable and unsatisfiable) from real-world applications.
       </list-item>
       <list-item label="•">
        Hard Combinatorial SAT+UNSAT: hard combinatorial problems (both satisfiable and unsatisfiable) to challenge current SAT solving algorithms (similar to the previous SAT Competitions' category “crafted”).
       </list-item>
       <list-item label="•">
        Random SAT: satisfiable k-SAT instances generated uniformly at random for different clause lengths k.
       </list-item>
      </list>
      <paragraph>
       Two special tracks:
      </paragraph>
      <list>
       <list-item label="•">
        One track for Parallel Solvers: In this track, the same problem instances as in the Application Main Track were used. However, solvers could use up to eight computing cores.
       </list-item>
       <list-item label="•">
        One track for Sequential Portfolio Solvers: A portfolio solver is a solver that combines different (sequential) SAT algorithms. It may have, e.g., run multiple solvers in a time-slicing manner on a given SAT instance, or selected one solver out of a set of given ones (e.g., determined by a machine-learning approach based on some metric) to tackle the problem. In this track, one third of the benchmarks was selected from the application, one third from the hard combinatorial, and one third from the random category. Within each category (except Random SAT), a mixture of satisfiable and unsatisfiable instances was used.
       </list-item>
      </list>
      <paragraph>
       This collection of tracks was the end-result of an attempt to find a balance between the very large number of tracks (pure SAT, pure UNSAT, SAT+UNSAT for each of the categories, Application, Crafted, and Random; and instantiation-specific special tracks) organized in the SAT Competitions, and the strict application orientation of the SAT-Races (only “industrial” Application SAT+UNSAT). Unsatisfiable instances were ruled out from the SC 2012 Random Track based on the observation that there has been little progress as well as very few solvers; the dominating solver on Random UNSAT in the SAT Competitions has repeatedly been the lookahead solver March [42]. The 2009 SAT competition and the 2010 SAT-Race had benchmark category specific special tracks for parallel solvers, while the 2011 SAT Competition included a wall-clock based timeout (in addition to CPU-time based), intuitively favoring parallel solvers. While the SC 2012 special track for parallel solvers similarly employed a wall-clock based timeout, the benchmarks in the track were evenly selected from the three main tracks. The SC 2012 special track for sequential portfolio solvers was the first of its kind.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Computing environment
      </section-title>
      <paragraph>
       Evaluation of solvers was performed on identical nodes of the bwGrid cluster [43] of State of Baden-Württemberg, Germany. Each cluster node had the following specification:
      </paragraph>
      <list>
       <list-item label="•">
        Hardware: Two 4-core Intel Xeon E5440 processors (2.83 GHz with 12 MB L2 cache per CPU), 16-GB RAM.
       </list-item>
       <list-item label="•">
        Software: Scientific Linux OS, kernel 2.6.18, glibc 2.5, GCC 4.1.2, javac 1.6.0, 32-bit and 64-bit executables supported.
       </list-item>
      </list>
      <paragraph>
       In the three Main Tracks and the Sequential Portfolio Solvers Track, a solver could use one core of one CPU and 6 GB of main memory. Two solvers were executed in parallel on each computing node (i.e., one solver per physical CPU). A runtime limit of 900 seconds CPU time was enforced per solver and benchmark instance, with the help of the runsolver tool [44] also used in previous competitions. In the Parallel Solvers Track, all eight cores and 12 GB of main memory were available. Only one solver was executed on each cluster node. A runtime limit of 900 seconds wall-clock time was enforced. A total of 2.2 CPU years were used to run SC 2012 — not counting the testing of solvers and the filtering of instances beforehand, which also used around the same amount of computing resources.
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       EDACC: Experiment Design and Administration for Computer Clusters
      </section-title>
      <paragraph>
       The EDACC system [45], [46] was utilized for organizing SC 2012.{sup:9} EDACC is a distributed computing system similar to the BOINC project [47]. It was inspired by the SatEx system [48] used in earlier SAT Competitions. EDACC consists of a central database (DB), a graphical user interface, a computation client, and a web front-end. All data, including solvers and their parameters, instances, and solver output, was stored in the DB. The computation client is responsible for the execution of experiments (running the solvers on the instances). The graphical user interface was used by the organizers to create the tracks and monitor the experiments. The web front-end was used for providing an automated submission and testing platform for the submitters. A submitted solver was automatically tested on a small representative set of instances and the results were automatically reported to the submitter. The participants could then analyze the results of their solver and submit a bug-fixed version of their solver when necessary. After running the competition, the participants could analyze their results within the web front-end that provides a wide range of statistical and graphical analysis possibilities, including:
      </paragraph>
      <list>
       <list-item label="•">
        generation of box plots and cactus plots{sup:10} (for comparing the results of multiple solvers), scatter plots (for pair-wise comparisons of solvers), and runtime matrix plots (for analyzing the variance of solver performances);
       </list-item>
       <list-item label="•">
        comparison of distributions (Kolmogorow–Smirnow test, Wilcoxon rank sum test);
       </list-item>
       <list-item label="•">
        distribution and kernel density estimation;
       </list-item>
       <list-item label="•">
        probabilistic domination comparison of two solvers;
       </list-item>
       <list-item label="•">
        computation of rankings using different ranking schemes; and
       </list-item>
       <list-item label="•">
        SOTA (state-of-the-art-contributor) and VBS (virtual best solver) analysis (for definitions of SOTA and VBS, see Sections 3.1.1 and 3.2, respectively).
       </list-item>
      </list>
      <paragraph>
       EDACC offers all major functionalities to organize algorithmic competitions and is freely available online{sup:11} under an MIT license.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Benchmark selection and generation
     </section-title>
     <paragraph>
      In this section we first briefly survey and analyze the benchmark selection methods used in solver competitions related to SC 2012. We then outline the selection (for Application and Hard Combinatorial tracks) and generation (for Random tracks) processes for benchmarks used in SC 2012, and describe the benchmark set selected for SC 2012.
     </paragraph>
     <section label="3.1">
      <section-title>
       Review of benchmark selection methods
      </section-title>
      <paragraph>
       In the following, we will review benchmark selection methods applied in four related constraint solver competition series: the CADE ATP System Competitions (CASC) [49],{sup:12} the SAT Competitions [33],{sup:13} the SMT Competitions [50],{sup:14} and the ASP Competitions [51], [52], [53].{sup:15} A common theme among the selection processes is a (sometimes implicit) two-stage selection: in the first stage the benchmarks are ranked according to their perceived difficulty; in the second stage the benchmarks are selected based on some combination of their rank and other properties, such as whether or not the benchmark is new (i.e., not used in previous competitions).
      </paragraph>
      <section label="3.1.1">
       <section-title>
        CADE ATP System Competitions (CASC)
       </section-title>
       <paragraph>
        The Automated Theorem Prover (ATP) Competitions are perhaps the longest continuously running series of system competitions in our field. The first competition close to the current form was held at the CADE-13 conference in 1996. The design of the competition is presented in [54]. The paper also contains the original methodology for the ranking of the benchmarks (and the solvers). The methodology has been slightly modified with the introduction of the concepts of system ranking by subsumption and the state-of-the-art (SOTA) system[49]. The benchmark selection methodology used in the most recent competition, CASC-J6, follows [49], and overviewed here next.
       </paragraph>
       <paragraph>
        The benchmark problems for the competition are taken from the TPTP Problem Library,{sup:16} which is an online repository of problem instances used for evaluation of theorem provers in the ATP community, and which is split into thematic categories. The library is “frozen” prior to the start of the competition. The ATP systems submitted for the competition itself, are used to rank the benchmarks. The difficulty of benchmarks is determined by the ability of so-called SOTA contributors to solve them. Let {a mathematical formula}B={b1,…,bn} be the set (pool) of available benchmarks, and let {a mathematical formula}S={s1,…,sk} be the set of solvers submitted to the competition. For a solver {a mathematical formula}si∈S, let {a mathematical formula}Bi⊆B denote the set of benchmarks solved by {a mathematical formula}si within a timeout. Solver {a mathematical formula}si is said to subsume solver {a mathematical formula}sj if {a mathematical formula}Bi⊃Bj. Furthermore, {a mathematical formula}si is a SOTA contributor if no other solver subsumes it (i.e., there is no j with {a mathematical formula}Bi⊂Bj). In other words, given that the sets {a mathematical formula}Bi, {a mathematical formula}1≤i≤k, form a partially ordered set (poset, ordered by set inclusion), SOTA contributors are the maximal elements in the poset. The SOTA problem rating{a mathematical formula}ri for a benchmark {a mathematical formula}bi is then{a mathematical formula} The benchmarks are rated within their corresponding categories. In case the number of SOTA contributors is less than a certain threshold (3), the non-SOTA contributors that solve the most problems are used. The benchmarks with SOTA rating of 0 are referred to as easy, those with a rating strictly between 0 and 1 are difficult, and those with rating 1 are unsolved. For CASC-J6, the problems with a rating in the interval {a mathematical formula}[0.21,0.99] were selected [55]. Note that this implies that the unsolved benchmarks are not used in the competition.
       </paragraph>
      </section>
      <section label="3.1.2">
       <section-title>
        SAT competitions
       </section-title>
       <paragraph>
        The benchmark selection process used in SAT Competitions is presented in detail on the SAT Competition 2009 website.{sup:17} Similar to SMT-COMP (discussed later), the benchmarks for the application and the crafted categories are rated based on the performance of the top three solvers from the previous competition. In the 2011 competition, the benchmarks were rated using “SAT 2009 reference solvers” [56]. A benchmark is rated as (i) easy, if it is solved within 30 seconds by all solvers; (ii) hard, if its not solved by any solver within the timeout value of the first phase of the competition (1200 sec); (iii) medium, in all other cases. The competition benchmark sets are then selected given the following constraints. Rating distribution: 10% easy, 40% medium, 50% hard; new vs existing (i.e., used in previous competitions): 45% existing, 55% new; source distribution: not more than 10% from the same source.
       </paragraph>
       <paragraph>
        The instances in the random category of SAT Competition 2011 were taken from (uniform random) k-CNF distributions for {a mathematical formula}k=3,5,7, i.e., for each clause, k variables were drawn uniformly at random from the set of all variables, and each variable drawn was negated with probability {a mathematical formula}12. The medium instances were taken very close to the clause-variable phase transition ratio[57], [58] to ensure approximately 50 % of UNSAT instances; the large instances were taken slightly below the phase transition. The medium instances where classified into SAT and UNKNOWN (probably UNSAT) using the SLS solver gnovelty+[59] – the instances that are solved within the timeout are classified as SAT. Note, however, that the organizers indicate that in most cases the instances were solved “within seconds”. The proportion of SAT/UNKNOWN instances among the medium instances of the final benchmark set is 50/50. The satisfiability status of the large instances was presumed to be SAT, due to their clause density below the threshold (cf. Section 3.3.3). The final set of benchmarks consisted of approximately {a mathematical formula}23 of medium and {a mathematical formula}13 of large benchmarks.
       </paragraph>
      </section>
      <section label="3.1.3">
       <section-title>
        SMT competitions
       </section-title>
       <paragraph>
        The benchmark rating system used in the recent SMT Competition (SMT-COMP 2012) is described in [60]. The rating system differs from the previously discussed systems in two aspects: (i) the solvers that “finished in good standing” in the previous year's competition (SMT-COMP 2011) were used rather than the solvers submitted to the 2012 competition,{sup:18} and (ii) the solving time is taken into account. The problem rating r is given by {a mathematical formula}r=5ln⁡(1+A2)ln⁡(1+302), where A is the average time over all solvers, in minutes, to solve the problem. 30 is the timeout value used in the 2011 competition. If a solver fails to solve the problem within the timeout, its solving time is taken to be 30 minutes. Thus, according to [60], the rating system recognizes the fact that problems that require more time by more solvers are more difficult. The logarithm is used to mark a larger change in difficulty at smaller time values than at larger ones, and the square is used to “flatten the curve slightly at the end”. Given the problem rating, the benchmarks for the competition are then selected by choosing the same number of problems uniformly at random from each of the five intervals {a mathematical formula}[0,1], {a mathematical formula}(1,2], {a mathematical formula}(2,3], {a mathematical formula}(3,4], {a mathematical formula}(4,5]. For each of the subdivisions of benchmarks (i.e., for the different theories), 5% of benchmarks are chosen from the random category, 10% from crafted, and the rest from the industrial applications category.
       </paragraph>
      </section>
      <section label="3.1.4">
       <section-title>
        ASP solver competitions
       </section-title>
       <paragraph>
        All ASP competitions to date appear to be using the benchmark selection process proposed for the first competition, held in 2007. The process is outlined in Section 4 of [51]. After fixing a set of five solvers for evaluating benchmark hardness (details for the set of solvers used in SC 2012 are provided in Section 3.3) a benchmark is considered suitable if at least one solver is capable of solving it within the timeout (600 seconds), and at most three solvers can solve it within 1 second. The set of benchmarks used for ranking the solvers in the competition is constructed by choosing random benchmarks from the pool of available benchmarks, until the desired number (100 overall) of suitable benchmarks is obtained. Similarly to CASC, the benchmarks are ranked using the solvers submitted to the competition.
       </paragraph>
      </section>
     </section>
     <section label="3.2">
      <section-title>
       Analysis of benchmark ranking and selection methods
      </section-title>
      <paragraph>
       It is well-known that the hardness of satisfiable random k-SAT instances close to the phase transition point increases as the number of variables is increased. However, for the heterogeneous sets of application and hard combinatorial instances, instance size does not correlate well with the hardness of the instances. Hence empirical testing is required in order to rate the practical hardness of such instances. In the ASP and CASC competitions, the solvers submitted to the competition are used to rate the benchmarks, so rating/selection is done a posteriori. For SAT competitions, including SC 2012, such an a posteriori rating is not computationally feasible due to the large number of participating solvers. So both SAT and SMT competitions revert to the evaluation of hardness using some, typically few, best-performers from previous years. As we demonstrate later, a problem that might arise in this setting is that the selected benchmark set can be (strongly) biased towards a particular solver. So the selection must be done carefully, taking this potential bias into account. However, we do want to point out that, as further discussed in Section 7, eliminating such bias is not entirely unproblematic.
      </paragraph>
      <paragraph>
       In the SOTA problem rating system used in CASC, the difficulty of any particular problem is proportional to the number of SOTA contributors that fail to solve it. This allows to reduce the influence of weak systems, since the fact that many weak (i.e., non-SOTA) systems fail to solve the problem does not necessarily mean that the problem is difficult. The SMT-COMP rating system also takes into account the time used by the solvers. However, given that all problems with solving times in the range {a mathematical formula}(0.5⋅timeout,timeout] (i.e., including the unsolved problems) get the rating of {a mathematical formula}(4,5], no more than 20% of difficult benchmarks (with very few unsolved ones) get into the selected problem set. As a result, in SMT-COMP 2011,{sup:19} for example, the top solver in many cases managed to solve all, or close to all, of the selected benchmarks. The rating system used in previous SAT Competitions also takes into account the solving time, though in a less refined manner than SMT-COMP. However, the difficulty of benchmarks is judged using three solvers only, chosen from the top performing solvers in the competition of the previous year. Additionally, it appears that the number of hard benchmarks in SAT Competitions is too large, especially for the crafted category. Table 1 shows the percentages of the benchmarks solved by the virtual best solver (VBS) and the top-3 solvers in each of the categories in the 2009 and 2011 SAT Competitions. For each benchmark instance, the running time of the virtual best solver (VBS) is defined as the running time of the fastest solver out of all solvers participating in a competition. For example, the fact that the VBS solved 77% of benchmarks in the 2011 SAT Competition crafted category implies that almost {a mathematical formula}14 of the benchmark set was not solved by any participating solver. Given the fact that the solver ranking system used in the competition is based on the number of instances solved by at least one solver (i.e., solution-count ranking), {a mathematical formula}14 of the experiments in this category were a posteriori redundant in terms of determining the final result.
      </paragraph>
      <paragraph>
       Another important factor influencing benchmark rating in competitions are resource limitations, such as CPU time and memory. For competitions that can afford rating of the benchmarks using the competing systems (e.g., CASC and ASP Competition) the resource limits used in the competition itself is an obvious choice. However, when the systems used to rate benchmarks are chosen from the top performers of the previous competition (as in the SAT and SMT Competitions), the choice becomes less clear: how does one account for the possible, and expected, progress of the systems since the previous competition? Applying the resource limits of the competition itself might result in a benchmark set that is too “easy”.
      </paragraph>
      <paragraph>
       Clearly, one of the objectives of the benchmark selection process is to create a heterogeneous set of benchmarks. While for the Random track this objective can be achieved by varying the parameters of the instance generator, for the Application and the Hard Combinatorial tracks this issue is quite challenging. A typical approach, taken for example in CASC and SAT Competitions, is to limit the proportion of benchmarks that come from a single submitter. Previous SAT competitions enforced a limit of 10% on the fraction of benchmarks contributed by one submitter. CASC competitions use an undocumented algorithm to determine a “fair” proportion, thus making the somewhat arbitrary 10% limit more refined [61]. However, a benchmark submitter can contribute multiple benchmark sets that often differ significantly in structure and in the application context — this makes the author-based grouping of benchmarks somewhat limited. A possible way to address this problem is to group the benchmarks into manually-defined “buckets” that cluster benchmarks according to a specific application domain (see Table 2 for an example of such clustering). In [62], the authors propose to cluster the benchmarks according to their feature-vectors, such as those used by portfolio-based solvers (cf. [63]) to determine which solver to run on a particular benchmark. This approach, however, also has drawbacks: for one, it presumes that the feature vectors capture the structure correctly. In addition, it to some extent complicates certain analysis tasks, such as finding a solver that performs best in a specific application domain. A possible solution to this is to combine the “bucket”-based method with feature vectors — this is a topic for further research.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       SAT Challenge 2012 benchmark selection
      </section-title>
      <paragraph>
       The benchmark selection process is noticeably influenced by the solution-count ranking scheme used. Under this scheme, a central requirement is that the selected set of benchmarks should contain as few as possible benchmarks that would not be solved by any submitted solver. At the same time, the set should contain as few as possible benchmarks that would be solved by all — including the weakest — submitted solvers. In order to level out the playing field for competitors who do not have the resources to tune their solvers on all benchmark sets used in the previous competitions, an additional requirement is that the selected set should contain as many benchmarks as possible that were not used in previous SAT Competitions — we refer to these benchmarks as unused from now on. Finally, the selected set should not contain a dominating number of benchmarks from one source (domain, benchmark submitter).
      </paragraph>
      <paragraph>
       The benchmarks for the Application and the Hard Combinatorial tracks were drawn from a pool containing benchmarks that were either (i) used in the past five competitive SAT events (SAT Competitions 2007, 2009, 2011 and SAT Races 2008, 2010); (ii) submitted to these five events but not used (unused benchmarks); or (iii) new benchmarks submitted to SC 2012 (the descriptions for these benchmarks can be found in [39]). As elaborated in Section 7.4, the categorization of benchmarks into the Application vs. the Hard Combinatorial category is far from straightforward, and might need to be revised in the future competitions. For SAT Challenge 2012 we used a traditional categorization, following the previous SAT competitions. As with the previous SAT competitions, the benchmarks for the Random track were generated from scratch. We used a new generation and filtering procedure described in Section 3.3.3.
      </paragraph>
      <paragraph>
       The empirical hardness of the benchmarks (used to rate the benchmarks for the Application and Hard Combinatorial tracks, and to filter the generated benchmarks in the Random track) was evaluated using a selection of well-performing SAT solvers from the 2011 SAT Competition. Our first attempt to select the state-of-the-art (SOTA) contributors [49], as in the CASC and ASP competitions, from the second phase of the 2011 SAT Competition failed due to the fact that all solvers from the second phase turned out to be SOTA contributors. Driven by the restrictions on computational resources, we ultimately selected five SAT solvers among the best performing solvers from the Application, the Crafted and the Random tracks of the 2011 SAT competition. Among the best performing solvers, preference was given to solvers that solved the highest number of benchmarks uniquely. We also tried to diversify the original code-bases of the solvers (so that, for example, not all solvers were based on Minisat). Clearly, this is not an ideal solution. However, we did not arrive at a better one within the resourcesavailable at the time The selected solvers for each track are listed in the subsequent sections.
      </paragraph>
      <paragraph>
       The hardness of the benchmarks was evaluated using the same cluster on which the actual solver evaluation was run. The rating of a benchmark within the Application and Hard Combinatorial categories was defined as follows:
      </paragraph>
      <list>
       <list-item>
        — benchmarks that were solved by all 5 solvers in under 90 seconds. These benchmarks are extremely unlikely to contribute to the (solution-count) ranking of SAT solvers in SC 2012, as all reasonably efficient solvers are expected to solve these instances within the 900-second timeout.
       </list-item>
       <list-item>
        — benchmarks not in easy that were solved by all 5 solvers in under 900 seconds. Though these benchmarks are expected to be solved by the best-performing solvers, they can help to rank the weaker solvers.
       </list-item>
       <list-item>
        — benchmarks that were not solved by any of the 5 solvers within 2700 seconds (3 times the timeout). Most of these benchmarks are expected to be unsolved by all competing solvers. Inclusion of (many of) such benchmarks was infeasible due to limited computational resources.
       </list-item>
       <list-item>
        — the remaining benchmarks, i.e., the benchmarks not in easy or medium that were solved by at least one solver within 2700 seconds. These are expected to be the most useful for ranking the best-performing solvers.
       </list-item>
      </list>
      <paragraph>
       This rating of the benchmarks is similar to the one used in the 2009 and 2011 SAT Competitions,{sup:20} except that by singling out and disregarding the benchmarks that would almost certainly not be solved by any submitted solver (these are the too-hard benchmarks), we aimed at increasing the effectiveness of the selected sets for ranking the solvers.
      </paragraph>
      <paragraph>
       Once the hardness of the benchmarks in the pool was established, 600 benchmarks were selected from the pool. During the selection we attempted to keep the 50–50 ratio between the medium and hard benchmarks, and, at the same time, to make sure that no benchmarks from the same source were over-represented ({a mathematical formula}&gt;10% of the selected set). Benchmarks from the sources that were over-represented in the pool were selected by uniform random sampling from each over-represented source, taking into account the benchmark hardness. Due to the shortage of available benchmarks, this latter requirement forced us to select about {a mathematical formula}10%easy as well as a number of too-hard benchmarks. The details for each selected set differ, and are provided in the following sections. Section 3.3.3 provides additional details for the generation and filtering of Random benchmarks.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Application benchmarks
       </section-title>
       <paragraph>
        The five SAT solvers used to evaluate the hardness of the application instances were CryptoMiniSat (ver. Strange-Night2-st), Lingeling (ver. 587f), glucose (ver. 2), QuteRSat (ver. 2011-05-12), RestartSAT (ver. B95). All solvers were obtained from the SAT Competition 2011 website.{sup:21} The set of application benchmarks was drawn from a pool of 5472 instances. Some statistics on the set of the 600 selected instances are presented in Table 2.
       </paragraph>
       <paragraph>
        Overall, we achieved a fairly balanced mix between medium and hard benchmarks, SAT and UNSAT benchmarks, and a reasonable distribution among the various sources. The proportion of previously used benchmarks was quite high. While undesirable, as explained in the beginning of Section 3.3, this was unavoidable due to the small number of new benchmark submissions.
       </paragraph>
      </section>
      <section label="3.3.2">
       <section-title>
        Hard combinatorial benchmarks
       </section-title>
       <paragraph>
        The five SAT solvers used to evaluate the hardness of the application instances were clasp_2.0 (ver. R4092-crafted), SArTagnan (ver. 2011-05-15), MPhaseSAT (ver. 2011-02-15), sattime (ver. 2011-03-02), Sparrow UBC (ver. SATComp11). Note that we added the SLS-based solver Sparrow UBC to the set — this is due to the fact that some of the benchmarks in the Hard Combinatorial category are “random-like”. However, since this solver is incomplete, it was not considered for determining the hardness of UNSAT instances. All solvers were obtained from the SAT Competition 2011 website. The set of hard combinatorial benchmarks was drawn from a pool of 1743 instances. Table 3 presents some statistics on the set of the 600 selected instances.
       </paragraph>
       <paragraph>
        Note that while the selected benchmarks are balanced well among various sources, the proportion of hard benchmarks is very high. This is due to the fact that, among the 1743 benchmarks in the pool, there are only 39 instances of medium difficulty. Approximately {a mathematical formula}13 of the pool consists of easy instances, {a mathematical formula}13 of hard, and {a mathematical formula}13 of too-hard. Thus, the selected set is more difficult for the solvers in SC 2012 than the set of Application instances. The imbalance between SAT and UNSAT instances is explained by the fact that a large proportion of the hard instances were satisfiable, and we were forced to take almost all hard benchmarks from the pool.
       </paragraph>
      </section>
      <section label="3.3.3">
       <section-title>
        Random SAT benchmarks
       </section-title>
       <paragraph>
        The benchmark set for the Random SAT track contains 600 instances, generated according to the uniform random k-SAT model. The instances were divided into five major classes: k-SAT for {a mathematical formula}k=3,4,5,6,7. Each class contains ten subclasses with varying clauses-to-variables ratios and numbers of variables. Each subclass contains 12 instances. In the following we assume that n denotes the number of variables in a k-SAT formula, m is the number of clauses, and {a mathematical formula}α=mn is the clause density. The satisfiability status of a random k-SAT instance is not known a priori, although for each k there is a threshold value {a mathematical formula}αk for the clause density such that all instances generated with an {a mathematical formula}α&lt;αk are with high probability satisfiable, and all instances generated with an {a mathematical formula}α&gt;αk are with high probability unsatisfiable (as {a mathematical formula}m,n tend to infinity). Instances generated at the threshold ratios or near them are the most challenging for complete and local search methods [57], [58]. For large n, the best approximations of the threshold ratios are given in [64] and listed in Table 4.
       </paragraph>
       <paragraph>
        Previous SAT Competitions also used the uniform random generation model (with a small exception: the {a mathematical formula}2+p instances [65] used in 2007). Note that only k-SAT instances for {a mathematical formula}k=3,5,7 were used in these competitions, and for each k only two different ratios were considered (one also containing unsatisfiable instances). For further background, we refer to [66] for details on the random instances used in the 2005 SAT Competition.
       </paragraph>
       <paragraph>
        For SC 2012, we generated k-SAT instances for {a mathematical formula}k=3,4,5,6,7. Starting from these values, we applied the following generation model: For each k, two extreme points {a mathematical formula}(αk,nk) and {a mathematical formula}(αnt,nnt), with {a mathematical formula}αnt&lt;αk and {a mathematical formula}nnt&gt;nk, were fixed:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}nk: the largest number of variables a formula generated at the threshold {a mathematical formula}αk was allowed to have (such that the top three best solvers for the random category in SAT Competition 2011 were still able to solve these problems in 2700 seconds).
        </list-item>
        <list-item label="•">
         {a mathematical formula}αnt: the largest clauses-to-variables ratio for the number of variables {a mathematical formula}nnt (again based on our estimate of the behavior of best known solvers).
        </list-item>
       </list>
       <paragraph>
        The values of the extreme points used in SC 2012 are presented in Table 5. For each k, ten combinations of {a mathematical formula}(α,n) were chosen on the line between {a mathematical formula}(αk,nk) and {a mathematical formula}(αnt,nnt), giving a total of 50 combinations (for the full listing, see Appendix A). The intuition behind this generation scheme is twofold. First, we wanted to allow an analysis of the influence of the clause-to-variable ratio on the performance of different solvers. On the other hand, we also wanted to keep the difficulty of the instances at a certain level, which means that by lowering the clause-to-variable ratio we have to increase the number of variables. In the previous competitions instances generated on the threshold ratio where solved by all SLS solvers and had no influence on the ranking scheme.
       </paragraph>
       <paragraph>
        For each chosen combination {a mathematical formula}(α,n), we generated 100 instances, resulting in a total of 1000 instances per k-value, and thus a total of 5000 instances.
       </paragraph>
       <paragraph>
        We have opted to use a new generator because existent generators used in previous competitions did not meet our quality criteria; especially (i) clauses produced should be unique, and (ii) the used random number generators should pass several currently known randomness tests. Consequently, our new generator (freely available online{sup:22}) uses the SHA1PRNG generator (part of the Sun Java implementation) that has passed all randomness tests considered by L'Ecuyer and Simard in [67, p. 22].
       </paragraph>
       <paragraph>
        To filter out the unsatisfiable instances within the generated set of 5000 instances, we used the best performing solvers from the SAT Competition 2011 random track: Sparrow2011, sattime2011, EagleUP and adaptG2WSAT2011. Additionally, we used survey propagation v 1.4[68], adaptiveWalkSAT[69], adaptive probSAT[69] and adaptnovelty+ from UBCSAT [70]. Each solver was run only once on each instance using a cutoff of 2700 seconds (3 times the SC 2012 timeout). If an instance was solved by at least one solver, it was declared satisfiable. Otherwise, the satisfiability status of the instance was marked as UNKNOWN. From each of the 50 sets of instances generated for each {a mathematical formula}(α,n) combination, we randomly chose 12 instances that were determined satisfiable in the filtering phase. The resulting set of a total of 600 instances constitutes the benchmark set used in the Random SAT Track.
       </paragraph>
      </section>
     </section>
     <section label="3.4">
      <section-title>
       Solver bias in benchmark selection
      </section-title>
      <paragraph>
       We now discuss potential pitfalls of the SC 2012 benchmark selection process. Recall that the ranking of the benchmarks in the benchmark pool was done using a small set of SAT solvers that were known to perform well in the previous competitions. Once the benchmarks were ranked, a subset of benchmarks was selected, based on a set of requirements, such as the distribution of hardness, satisfiability status, etc. Since the best-performing SAT solvers were used for rating, the solvers might have been expected to perform somewhat similarly across the benchmark pool. The number of instances in the pool solved by any two solvers used for ranking should be close. However, this might not be the case across the set of selected benchmarks. As an extreme, consider the case where only two solvers A and B are used for ranking of the benchmarks in the pool S, and assume that the set of benchmarks {a mathematical formula}SA⊂S solved by A and the set {a mathematical formula}SB⊂S solved by B are disjoint, and that {a mathematical formula}|SA|=|SB|. If the set {a mathematical formula}S′⊂S of benchmarks selected for the competition is drawn uniformly from S, then we should expect that the number of instances in {a mathematical formula}S′ solved by A and B is similar. However, since {a mathematical formula}S′ might be constructed under various additional constraints (such as satisfiability status, old vs new, etc), it might be the case that {a mathematical formula}S′⊂SA, and so the selected set is strongly biased towards solver A.
      </paragraph>
      <paragraph>
       To our knowledge, such solver bias in the selected benchmarks has not been brought to light in the existing literature and has not been investigated in prior competitions. However, this issue has the potential to significantly affect the competition's results. In SAT Challenge 2012, the problem surfaced during the analysis of the results of the Application SAT+UNSAT track (see Table 6 for the preview), where the 2011 reference solver lingeling (SAT Comp. 2011 Bronze) showed an unexpectedly high performance on the benchmark set selected for the competition. The fact that this solver was one of the five solvers used for the ranking of the benchmarks suggested a possible bias towards the reference solvers. Further analysis of the evaluation data confirmed our hypothesis. To evaluate the impact of the bias on the competition results, we corrected the bias by removing 100 benchmarks from the selected set, so that the performance of the five solvers used for ranking of the benchmarks was relatively even. The rankings were then re-calculated using this corrected benchmark set — the results are presented in Table 6. Since the (original) results of the competition have already been presented to the community, and since the selection bias did not affect the rankings of the winners, we have opted to keep the results on the original set. However, as demonstrated in Table 6, the effect of the bias was close to being dramatic: the 4th and the 5th ranked solvers switched their positions (although, since one of these two solvers (glucose) is single-engine, and the other one (interactSAT) a multi-engine, this would not have changed the final standings). The solver linge_dyphase dropped from the 9th place to 15th, with the solver glue_dyphase, previously ranked 11th, taking its place. Also, notice that on the corrected set the comparative performance of the reference solver lingeling (SAT Comp. 2011 Bronze) is just above the 10th ranked competition solver, as opposed to being 4th.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Entrants
     </section-title>
     <paragraph>
      In total, 65 solvers were submitted to SC 2012 by 55 authors from 27 research groups with 12 different countries of affiliation. Eight solvers had to be disqualified due to erroneous results they produced; thus 57 solvers participated in SC 2012.{sup:23} The number of authors per country of origin is provided in Table 7. Apart from five solver submissions with co-authors from IBM Research, all solver authors had academic affiliations.
     </paragraph>
     <paragraph>
      The number of solver submissions to each competition track is provided in Table 8. A clear majority of the solvers were submitted as pre-compiled binaries; only three solvers were submitted in source-code. Notice, however, that this number does not tell the true number of open-source solvers participating in SC 2012. Most of the winning solvers are publicly available after the competition.
     </paragraph>
     <paragraph>
      After the submission deadline, we categorized the solver submissions into three different types of approaches based solely on the solver descriptions provided by the authors (i.e., without taking additional input from the solver submitters into account):
     </paragraph>
     <list>
      <list-item label="•">
       Single-engine solvers: An implementation of a white-box{sup:24} solver consisting of a single main algorithmic approach (e.g., conflict-driven clause learning [71], [72], [73], [74], [75], lookahead [76], stochastic local search [77]). We note that preprocessors are not considered individual algorithms, and are allowed in this category as well.
      </list-item>
      <list-item label="•">
       Interacting multi-engine approaches: An implementation that combines multiple different solver implementations/different types of algorithms in an interleaving fashion, possibly (but not necessarily) with information exchange between the different executed solvers.
      </list-item>
      <list-item label="•">
       Portfolio approaches: Based on a predefined set of solver implementations. For each input, execute one or more solvers in a black-box fashion. Solver selection may be based e.g. on pre-trained machine learning models.
      </list-item>
     </list>
     <paragraph>
      We acknowledge that this categorization is somewhat rough, and only one possible way of categorizing the solver submissions; this issue is discussed further in Section 7.5.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Overview of results
     </section-title>
     <paragraph>
      This section provides the solver rankings of SAT Challenge 2012, highlighting the best-performing solvers that were awarded, as well as a discussion of the detailed results of each track. Full rankings are provided in Appendix B. The complete results can be found online.{sup:25}
     </paragraph>
     <section label="5.1">
      <section-title>
       Awarded solvers
      </section-title>
      <paragraph>
       For each competition track and solver category, the best-performing solvers, with a listing of their developers and the main algorithmic approach applied by the solvers, were:
      </paragraph>
      <list>
       <list-item>
        Authors: Lin Xu, Frank Hutter, Jonathan Shen, Holger H. Hoos, and Kevin Leyton-Brown.Type of algorithm: Portfolio including a large range of both systematic and local search solvers. Solver selection based on pre-trained cost-sensitive classification models [63].
       </list-item>
       <list-item>
        Type of algorithm: Portfolio including a large range of both systematic and local search solvers. Solver selection based on pre-trained cost-sensitive classification models.
       </list-item>
       <list-item>
        Authors: Shaowei Cai, Chuan Luo, and Kaile Su.Type of algorithm: Local search, employing “configuration checking with aspiration” (CCA) [79].
       </list-item>
       <list-item>
        Type of algorithm: Portfolio including a range of both systematic and local search solvers, inspired by the ppfolio portfolio. Simple solver selection, based on a combination of “uniformity-based selection” (depending on whether all clauses of a formula have exactly the same length) and a static solver configuration setup, allocating one solver to each available CPU core.
       </list-item>
       <list-item>
        Type of algorithm: Portfolio including a large range of both systematic and local search solvers. Solver selection based on pre-trained cost-sensitive classification models.
       </list-item>
      </list>
      <paragraph>
       For more details on the algorithmic and implementation-level details of the individual solvers, we refer the reader to the solver descriptions collection released as a technical report [39].
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Detailed results
      </section-title>
      <paragraph>
       Cactus plots{sup:26} — representing for each solver the number of instances that can be solved (x-axis) within a given timeout (y-axis) — for each competition track, including for clarity only the Top-10 best performing solvers and the reference solvers, are provided in Fig. 1, Fig. 2, Fig. 3, Fig. 4, Fig. 5. Similarly, numerical data for the Top-10 solvers and the reference solvers is provided in Table 9, Table 10, Table 11, Table 12, Table 13, and the full tables are provided in Appendix B.
      </paragraph>
      <paragraph>
       In the result tables, solvers are ordered by the number of solved instances, and ties are broken taking the cumulative runtime into account. We also provide a second ranking (T-Rank), where only solvers of the same type (portfolio, single-engine, etc.) are taken into consideration. Besides the number of solved instances (#solved), we also give the percentage of solved instances (%solved), the cumulative runtime over all solved instances (time (cum.)), as well as the median runtime over all solved instances (time (med.)).
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Application SAT+UNSAT track
       </section-title>
       <paragraph>
        The Application SAT+UNSAT Track was dominated by portfolio and multi-engine solvers. They took the first four places (not taking the reference solver lingeling from SAT Competition 2011 into account). The winner, SATzilla2012 APP, even comes close to the virtual best solver. This suggests that high variability and adaptability in solver heuristics is extremely advantageous.
       </paragraph>
       <paragraph>
        glucose was the best single-engine solver, exhibiting clearly improved performance over its 2011 version, now solving 79.2% of the instances compared to only 75.2% in 2011. It is also interesting to observe that the median runtime of the 2011 version of glucose is much lower than that of any other solver. The exact reason for this behavior is unclear, and may be caused by a different adjustment of solver heuristics compared to previous versions (see [39, p. 21]).
       </paragraph>
       <paragraph>
        As reference solvers we have selected the best solvers from the 2011 SAT Competition, as well as additional solvers of general interest (such as the well-known and popular solver minisat).
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Hard combinatorial SAT+UNSAT track
       </section-title>
       <paragraph>
        Similarly to the Application SAT+UNSAT Track, this track was dominated by portfolio and multi-engine solvers (see Fig. 2 on page 133 and Table 10 on page 135). The best single-engine solver, clasp-crafted, comes in only on place seven, solving approximately 18% less instances than the best solver, SATzilla2012 COMB.
       </paragraph>
       <paragraph>
        There is a quite considerable gap between the second and third best solver (over 12% in number of solved instances), as well as between the first five and the following solvers (over 8% in number of solved instances). Perhaps even more severe is the difference in median runtime between the first five and the sixth best solver, with a factor of almost 3.5.
       </paragraph>
      </section>
      <section label="5.2.3">
       <section-title>
        Random SAT track
       </section-title>
       <paragraph>
        In the Random SAT Track, portfolio solvers also fared quite well, but were beaten by a new single-engine solver, CCASat. The local-search solver CCASat employs configuration checking that originates from local search algorithms for the Minimum Vertex Cover problem, and combines it with the aspiration mechanism from tabu search. This new algorithm solves over 30% more instances in the competition than the second best solver. Compared to the best solver of 2011, it solved almost 40% more instances. The median runtime of CCASat is also much lower than that of the other solvers. The success of CCASat also impressively shows that improving core algorithms is of prime importance, being even more successful than competing portfolios.
       </paragraph>
      </section>
      <section label="5.2.4">
       <section-title>
        Special tracks
       </section-title>
       <paragraph>
        The SC 2012 special tracks were the Parallel Track Application SAT+UNSAT and the Sequential Portfolio Track.
       </paragraph>
       <paragraph>
        In the Parallel Track, concurrent and parallel solving algorithms could make use of all eight cores of a cluster node. Here, the runtimes are given as wall-clock times, which means that each solver had approximately eight times the compute resources available compared to the (sequential) Application SAT+UNSAT Track.
       </paragraph>
       <paragraph>
        One would expect that — by having more compute power available — the solvers are much stronger now and solve more instances. However, this turned out not to be the case. The best performing solver in the Parallel Track, pfolioUZK, solved exactly the same number of instances (531) as the best solver in the sequential Application SAT+UNSAT Track, SATzilla2012 APP — although, the median wall-clock runtime of pfolioUZK is 65% lower than that of SATzilla2012 APP.
       </paragraph>
       <paragraph>
        Comparing the sequential and parallel versions of pfolioUZK, the improvement by the additional CPU power becomes more obvious. Whereas the sequential version of pfolioUZK ranked 16th in the sequential Application SAT+UNSAT Track, solving 404 instances, the parallel version fared much better, solving 531 instances. The median solving time also improved by a factor of five. This can be assumed to be close to the expected gain of 700% on the instances solved by both versions of the solver.
       </paragraph>
       <paragraph>
        Unfortunately, among the Top-10 solvers from the sequential Application SAT+UNSAT Track, only one (ZENN) participated (in a slightly different version, ZENNfork) in the parallel track, which makes an assessment of the state-of-the-art in parallel SAT solver technology harder. It is also quite surprising that the parallel version, ZENNfork, solved only 3.5% more instances than the sequential ZENN solver.
       </paragraph>
       <paragraph>
        The solver claspmt ranked 5th in the 2011 SAT Competition Application Track. clasp is the follow-up version of claspmt of 2012, in which multi-threading support has been built in. clasp solved 35% more instances, which, for this solver at least, shows the considerable progress made over one year.
       </paragraph>
       <paragraph>
        In the Sequential Portfolio Track, one third of the competition benchmark instances came from each of the three categories Application, Hard Combinatorial, and Random. Unfortunately, only three solvers participated in this “mixed” track, even though we believe the track would have been rather interesting for showcasing the potential of portfolio solvers as generic SAT solvers. SATzilla2012 ALL, which is optimized for such a mixed set of problem instances, could outperform the other two solvers, solving 17% more instances than the second best solver ppfolio2012. It is noteworthy that the generic mixed heuristics of SATzilla2012 ALL performed quite well also in the tracks specialized on only one category of benchmarks, where it consistently ranked just one place behind the more specialized versions of SATzilla2012, namely SATzilla2012 APP, SATzilla2012 COMB, and SATzilla2012 RAND.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="6">
     <section-title>
      Analysis
     </section-title>
     <paragraph>
      In this section we provide a more detailed analysis of the results of SC 2012.
     </paragraph>
     <section label="6.1">
      <section-title>
       Impact of ranking schemes
      </section-title>
      <paragraph>
       The solution-count ranking scheme (SCR) used in SC 2012 ranks solvers according to the number of solved instances. Ties are broken by the cumulative CPU time. The SCR scheme has been used in the SAT Competitions and SAT-Race since 2009, replacing the purse-based ranking (PBR) [80] after a questionnaire about the preferred ranking scheme was done by the organizers of the 2009 SAT Competition. In addition to being easy to understand, SCR defines a transitive relation between solvers, i.e. the relative ranking of two solvers cannot be influenced by a third solver, which is not true for PBR.
      </paragraph>
      <paragraph>
       However, SCR clearly also has disadvantages. One is that the produced rankings can be highly dependent of the enforced timeout. Another is that the runtime of the solvers plays only a marginal role within the ranking and is taken into account only in case of ties in the number of instances solver: a solver S that solves n instances will lose against a solver {a mathematical formula}S′ that solves {a mathematical formula}n+1 instances independent of the average runtime of S and {a mathematical formula}S′. Due to this, SCR has been criticized in multiple papers [80], [81]. One proposed alternative is the careful-ranking scheme (CR) [80] which is based on pairwise comparisons of solvers inspired by statistical tests. However, the CR scheme does not define a transitive relation. Another possibility is to rank solvers by their penalized average runtime (PAR)[82]. This idea gives a family of PARx ranking schemes over different penalization factors x. Denoting the imposed timeout limit by t, the PARx measure computes the average runtime by counting timeouts as having value {a mathematical formula}x⋅t. The parameter x controls the balance between the average runtime (over the successful runs) and the number of solved instances. Notice that SCR is equivalent to PARx in the limit {a mathematical formula}x→∞. Therefore, it is to be expected that the correlation between PARx and SCR approaches 1 as x grows.
      </paragraph>
      <paragraph>
       Here we study correlations between the rankings produced by the ranking schemes SCR, CR, and PARx for {a mathematical formula}x=1,2,10 using the SC 2012 data. Two possible correlation coefficients of interest are Kendall's τ and Spearman's ρ coefficients. Whereas the former measures the relative number of the number of disagreements and agreements between two rankings, the latter takes also into account the absolute differences in the disagreements. Intuitively, if two ranking methods rank a solver very differently, Spearman's ρ coefficient will be lower than Kendall's τ. One should note here that small differences between two rankings are not relevant as long as the big picture remains unchanged, i.e, a solver ranked among the best-performing solvers by one scheme should not be ranked as one of the worse/worst-performing solvers. Keeping this in mind, we use Spearman's ρ correlation coefficient for our analysis.
      </paragraph>
      <paragraph>
       The results are shown in Table 14, Table 15, Table 16 for the Application, Hard Combinatorial, and Random SAT main track data, respectively. The SCR scheme correlates well with the PARx rankings; this correlation increases with x, as the higher the value of x, the more the unsuccessful runs are penalized. Even when runs are penalized with a factor of 10 (PAR10), some solvers could compensate this penalization with overall short runtimes, ranking higher under PAR10 than under SCR. The CR scheme (using noise of 5 seconds) correlates better with PAR10 and SCR than with PAR1 and PAR2, which is to some extent surprising, as we would have expected that CR emphasizes more the average runtime than the number of successful runs. We note to the interested reader that the EDACC SC 2012 web front-end provides (under “Ranking”) all the aforementioned ranking methods (except PBR), allowing anyone to analyze further the rankings of one's interest.
      </paragraph>
      <paragraph>
       Ranking the solvers from the different tracks according to the before mentioned ranking schemes would have changed the ranking of the top three solvers only when using CR and in this case only slightly (i.e. a change of the second or third solver would have occurred).
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Stability of rankings with respect to the timeout
      </section-title>
      <paragraph>
       The ranking of the solvers within each track also depends on the selected timeout, which in SC 2012 was 900 seconds. The EDACC web front end allows to simulate the ranking with lower timeouts. To measure the stability of the ranking with respect to different timeouts, we have computed the ranking for timeouts of 450, 180 and 90 seconds, which corresponds to 1/2, 1/5 and 1/10 of the original timeout. For each ranking we then computed the Spearman correlation coefficient between the original ranking and the simulated ones with lower timeout; the results are shown in Table 17.
      </paragraph>
      <paragraph>
       The rankings for the sequential tracks remain quite stable if we reduce the timeout to 450 seconds, implying that we would have obtained almost the same results (rankings) by using only half of the resources in these tracks. Only the sequential Application track would have produced a different 3rd ranking. However, for the parallel track, the disagreement is already on the first ranked solver, suggesting that the results in this track are very sensitive to the timeout value (see also Section 6.3). Using 180 seconds as the timeout resulted in considerably larger changes in the rankings, especially for the Application tracks. These changes are even more pronounced when using only 90 seconds. Interestingly, the ranking variations are very low for the Hard Combinatorial and Random tracks even when using only 1/10 of the original timeout.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Stability of rankings with respect to the benchmarks set
      </section-title>
      <paragraph>
       To evaluate the impact of the selected benchmark set on the solver rankings, we performed the following experiment. For each track, we sub-sampled 300 out of 600 benchmarks uniformly at random, and ranked the participating solvers on the resulting sample; we refer to the resulting ranking as sub-sample ranking. This procedure was repeated 1000 times. The descriptive statistics of the resulting distribution of the solver's sub-sample rankings are presented in Table 18. With the exception of the Application Parallel track, the rankings of the top performing solvers are quite stable: the median sub-sample rankings match the original rankings. However, in the Application Parallel track, the sub-sample rankings of the top two solvers vary to a very large degree. Hence the solvers would likely have switched ranks on a smaller set of benchmarks. A similar observation can be made for solvers ranked 9–14 in the Application track, 10–15 in the Hard Combinatorial track, and even 5–6 in the Parallel track. Many of the solvers ranked below 15 (not shown in the table) are in a similar situation as well. The only track that is very stable with respect to the selected set of benchmarks is the Random track. This is likely due to the fact that the random benchmark set is very homogeneous in terms of structural properties of the instances.
      </paragraph>
      <paragraph>
       Regarding categorization of benchmarks, we note that some benchmark instances have both Application and Hard Combinatorial benchmarks characteristics. One notable example is the class of SAT encoded cryptographic problems, such as attacks against the block ciphers AES and DES. The computational hardness assumptions underlying the construction of these ciphers might suggest categorizing the resulting benchmarks as Hard Combinatorial, while the domain and the typically weak performance of the solvers in the Hard Combinatorial track on these instances suggest their classification as Application benchmarks. To evaluate the potential impact of re-classification of these benchmarks, we re-computed the rankings of the solvers in the Application track on the subset of the application benchmarks that excludes the cryptographic instances. The results are presented in Table 19. While the rankings of the winners have not been affected, already the solvers on the 4th and 5th position swapped their places. The changes in the rankings of lower-ranked solvers are even more dramatic with some solvers gaining or loosing up to three positions in the rankings. The results demonstrate that the issue of clear benchmark categorization has to be addressed in future competitions.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       How similar are the submitted solvers
      </section-title>
      <paragraph>
       As a measure of similarity between solvers, we computed the Spearman rank correlation between the results of all pairs of solvers. Rank correlation is better suited for analyzing the performance similarities of solvers than, e.g., Pearson correlation that would only reveal possible linear correlations. The resulting correlation matrix is clustered hierarchically (under average distance) and plotted as a heat map.{sup:27} This kind of plot was also used in [83] to analyze the contribution of solvers within a portfolio solver.
      </paragraph>
      <paragraph>
       Fig. 6, Fig. 7, Fig. 8, Fig. 9 show the obtained hierarchical clusterings as dendrograms (top) and the correlation matrices (bottom). In the correlation matrices, rows and columns correspond to solvers, and are ordered in such a way that “similar” solvers are adjacent. Each entry in the correlation matrices gives the degree of correlation between two solvers. Instead of numeric entries, a color code is used for displaying correlations: darker colors correspond to high correlations, whereas lighter colors indicate a low degree of correlation. Below the matrix, the translation from color codes to numerical values is shown, together with a histogram indicating the frequency with which each correlation value occurs.
      </paragraph>
      <section>
       <section>
        <section-title>
         Application track
        </section-title>
        <paragraph>
         Fig. 6 shows the correlation and clustering of the solvers from the Application track (excluding disqualified solvers). The dendrogram as well as the correlation matrix show clearly that March behaves quite differently from all the other solvers.{sup:28} As March implements a lookahead DPLL algorithm, whereas all other solvers are based on the CDCL approach, this is not very surprising.
        </paragraph>
        <paragraph>
         In contrast to March, the performance of CDCL solvers seems to be very similar. In particular, there are several pairs of solvers with almost identical behavior:
        </paragraph>
        <list>
         <list-item label="•">
          simpsat and CryptoMiniSat (the former has been implemented based on the latter);
         </list-item>
         <list-item label="•">
          satUZK and satUZKs (the latter is a version of the former with added preprocessing); and
         </list-item>
         <list-item label="•">
          glucose and glue_dyphase (the latter is a variant of the former with a slightly modified phase selection strategy).
         </list-item>
        </list>
        <paragraph>
         The dendrogram also reveals three larger clusters of related solvers, where the first ranges from SINN to riss, the second from caglue to satUZKs, and the third from pfolioUZK to simpsat. It can be assumed that solvers (excluding the reference solvers) in the first cluster are either based on or incorporate very similar techniques to minisat, in the second cluster similar to glucose, and in the third to the solvers lingeling or CryptoMiniSat.
        </paragraph>
       </section>
       <section>
        <section-title>
         Hard combinatorial track
        </section-title>
        <paragraph>
         Fig. 7 shows the results for the Hard Combinatorial track (excluding disqualified solvers). The two classes of SLS and CDCL/DPLL solvers can be easily detected in the clustering (solvers CCASat to EagleUp, and SINN to March, respectively). CDCL solvers are in the top-right part, and SLS solvers show up on bottom-left. Between the SLS and the CDCL class we can also recognize the set of portfolio approaches, ppfolio2012, pfolioUZK, SATzilla2012 COMB, and SATzilla ALL. Two other solvers, interactSAT_c and March, are strongly correlated (interactSAT_c uses the lookahead solver March as a sub-solver). Also worth noting is that all portfolio solvers are heavily using the MPhaseSAT solver from the 2011 SAT Competition added as a reference solver. This is not surprising as MPhaseSAT had the largest unique solver contribution (the number of instances solved only by MPhaseSAT) in the 2011 SAT Competition crafted category; this is also the case for the SC 2012 Hard Combinatorial track when disregarding the portfolio solvers. The MPhaseSAT solver [84] uses a phase heuristic inspired by lookahead solvers which is quite expensive to compute, but appears to provide a key to solving some of the harder instances. The solver EagleUP behaves quite differently from the other SLS solvers, which may be due to the incorporation of unit propagation, a feature that is missing from the other SLS solvers.
        </paragraph>
        <paragraph>
         It is also interesting that the performance of the portfolio solvers (ppfolio2012 to interactSAT_c) is quite similar to that of CDCL solvers in this track, although these portfolio solvers integrate both SLS and CDCL components. This might indicate that constituent CDCL solvers dominate the behavior of such portfolios on hard combinatorial problems.
        </paragraph>
        <paragraph>
         SLS solvers have an important contribution in the Hard Combinatorial track, being able to solve some satisfiable instances that the competing CDCL solver cannot solve. Analyzing the set of CDCL solvers together with only one single SLS solver, sattime2012, reveals that sattime2012 has a unique solver contribution of 39 instances. The VBS is using SLS solvers on 192 out of 516 instances.
        </paragraph>
       </section>
       <section>
        <section-title>
         Random
        </section-title>
        <paragraph>
         Fig. 8 shows the correlation and clustering of the solvers from the Random SAT track. There is a relatively large cluster around Sparrow2011, the winner of the Random SAT track of the 2011 SAT Competition. All portfolio solvers (SATzilla2012 ALL to ppfolio2012) and also the non-portfolio solver CCASat are relatively highly correlated with Sparrow2011, suggesting that the portfolio solvers often run Sparrow2011 or a solver exhibiting similar performance as Sparrow2011. CCASat tries to mimic the behavior of Sparrow2011 using a technique called configuration checking with aspiration (CCA). The portfolio solvers pfolioUZK and ppfolio are highly correlated, which might be due to the fact that the former is based on the latter. The SLS solver BossLS behaves quite differently from all other solvers. A reason for this might be the extensive preprocessing performed by this solver, including unit propagation, failed literal detection, and asymmetric blocked clause elimination. In general, the degree of correlation in the Random SAT track is much lower than in the Application and Hard Combinatorial track; the diversity of solving approaches submitted was much higher for this track.
        </paragraph>
       </section>
       <section>
        <section-title>
         Parallel application
        </section-title>
        <paragraph>
         Fig. 9 shows the correlation and clustering of the solvers from the Application Parallel track. Four major clusters can be detected here:
        </paragraph>
        <list>
         <list-item label="•">
          the set of parallel portfolio solvers (pfolioUZK to ppfolio2012);
         </list-item>
         <list-item label="•">
          the solver families CCC[n]eq (hybrid lookahead plus CDCL); and Plingeling/Treengeling (CDCL);
         </list-item>
         <list-item label="•">
          the parallelized versions of glucose and minisat (Sucrose to Minifork); and
         </list-item>
         <list-item label="•">
          the solvers claspmt, splitter, and CryptoMiniSat.
         </list-item>
        </list>
        <paragraph>
         The approaches used by these solvers are quite different. The portfolio solvers use different base solvers running in parallel with different strategies, with no or only minimal clause exchange. The solvers in the second class (CCC-variants and descendants of lingeling) are based on search space splitting, use forms of learned clause exchange, and, in the case of the cube-and-conquer solvers of the CCC family, combine a CDCL algorithm with a lookahead-approach for determining how to split the search space. Parallel derivations of glucose use competition parallelism (i.e., differently configured versions of a CDCL base solver running in parallel on the whole SAT instance) with forms of clause exchange. The solvers ZENNfork and Minifork, based on minisat, perform search space splitting, but no clause exchange. Solvers in the last group, consisting of claspmt, splitter and CryptoMiniSat, implement specialized algorithms, e.g., iterative partitioning in case of splitter.
        </paragraph>
        <paragraph>
         As with the Random SAT track, the degree of correlation in the Parallel Application track is much lower than in the Application and Hard Combinatorial track. It is also interesting to observe that the top seven solvers cover only two parallelization approaches, namely portfolio (pfolioUZK, ppfolio2012, ppfolio and ParaCIRMiniSAT) and competition parallelism with clause exchange, using glucose as the base solver (PeneLoPe, Cellulose and Sucrose).
        </paragraph>
       </section>
      </section>
     </section>
     <section label="6.5">
      <section-title>
       Minimum solver set(s)
      </section-title>
      <paragraph>
       Here we address the question What is a minimum set of solvers that would solve all instances solved by any solver within a track? More formally, consider the set of solvers and the instances they have solved within the given timeout as a collection of subsets {a mathematical formula}S={S1,S2,S3,…,Sn}, where {a mathematical formula}Si is the subset of instances that was solved by solver {a mathematical formula}Si. Let {a mathematical formula}I=⋃i=1nSi be the set of solved instances. Now we can formulate the question as a minimum set cover problem, where the task is to find the minimum number of subsets {a mathematical formula}Si to cover the set I. Note that all solvers that have a unique contribution will be part of the minimum solver set. Within the EDACC web front-end this problem is solved by encoding the problem as Max-SAT and using a branch-and-bound Max-SAT solver (akmaxsat[85]) to find all optimal solution. The unique solver contribution is also a measure of interest but is highly dependent on the set of solvers used to compute it. When analyzing the results, one should keep in mind that the inclusion of derivatives of a given solver in the set will reduce the unique solver contribution of this solver dramatically. In the following we provide the minimum solver sets for some of the tracks, excluding reference, offtrack, and disqualified solvers.
      </paragraph>
      <section>
       <section>
        <section-title>
         Application track
        </section-title>
        <paragraph>
         In the Application track there are six minimal sets of solvers, each of size 7, that do not differ significantly in terms of overall runtime (less than 5%). These sets consist of the solvers glucose, linge_dyphase, interactSAT, Industrial SAT Solver, SATzilla2012 APP, together with one solver from the set {Glucose++, glue_dyphase}, and one from {CCCeq, CCCneq, Lingeling}. Observe that the minimal sets include a large number of multi-engine solvers, as well as one portfolio solver. As these types of solvers include multiple solvers in their code-base, we also computed the minimal set over the sequential single-engine solvers only. The result was a single set of size 9, consisting of the solvers glucose, linge_dyphase, Glucose++, Lingeling, simpsat, TENN, contrasat12, riss, ZENN, suggesting, perhaps, a good portfolio composition. Notice, however, that the number of instances solved by the single-engine only solvers is 553 (vs. 562 for all). Interestingly, the solver linge_dyphase, ranked 9th overall in the Application track, is included in all minimal sets.
        </paragraph>
       </section>
       <section>
        <section-title>
         Hard combinatorial track
        </section-title>
        <paragraph>
         In this track, there is a single minimal set of solvers of size 7. This set consists of the solvers gNovelty+PCL, linge_dyphase, claspfolio-crafted, interactSAT_c, caglue, SATzilla2012 COMB, and Flegel. Three of the solvers are either portfolio or multi-engine, and are clearly important contributors to the set, since the minimal set computed over sequential solvers only contains 11 solvers gNovelty+PCL, linge_dyphase, sattime2011, BossLS, simpsat, sparrow2011-PCL, caglue, clasp-crafted, March, Lingeling, Sparrow2011, and solves only 511 instances, instead of 527 solved by the minimum set over all types of solvers. Observe that over a half of the minimum set sequential solvers are SLS solvers, i.e., these solvers show strong performance on some of the satisfiable benchmark instance in the track.
        </paragraph>
       </section>
       <section>
        <section-title>
         Random track
        </section-title>
        <paragraph>
         All solvers had a unique solver contribution, thus being part of the minimum solver set. This is to some extent surprising, especially in light of the relatively homogenous class of benchmarks. However, we were not able to pinpoint a simple explanation for this behavior, which we in fact believe to be due to a combination of (i) the intrinsically randomized search heuristics applied within the solvers (local search), (ii) the benchmark set being to some extent more heterogeneous than (e.g., in the recent SAT Competitions before SC 2012, the random tracks did not include instances for clause lengths {a mathematical formula}k=4,6), and (iii) in combination with point (ii), some of the solvers appeared to have been tuned to perform mainly on random instances generated using very similar parameter value combinations as the ones used in the recent SAT Competitions, witnessed e.g. by not being able to perform well on instances with even clause lengths. The fact that all solvers had a unique solver contribution explains also why portfolio approaches can be so successful on this type of instances. An optimal portfolio (of only core solvers) which is equivalent to the virtual best solver would solve 515 instances, which is almost 100 instances more than the best solver (423).
        </paragraph>
       </section>
       <section>
        <section-title>
         Summary
        </section-title>
        <paragraph>
         The minimum solver sets for the different main tracks differ in both the solver techniques used in the solvers, as well as the size of the minimum solver sets. For the Application track, the minimum solver sets are dominated by CDCL-based solvers, which is to be expected. We believe that the relatively small size of these minimum solver sets may be due to the fact that the CDCL-based solvers are relatively similar to each other. Interestingly, local search solvers do not contribute{sup:29} to the minimum solvers sets, although approximately half of the benchmarks in the track were satisfiable. This is in contrast with the Hard Combinatorial track, in which around half of the solvers within the minimum solver sets implement local search, evidently heavily contributing to solving the satisfiable benchmarks. This difference between the Application and Hard Combinatorial tracks may partly be explained by the fact that there were less local search solver submissions to the Application track than to the Hard Combinatorial track (which may suggest that there is currently less research effort put into improving local search techniques for application-type instances than for hard combinatorial type of instances). However, we believe that one should not underestimate the fact that local search solver offer a competitive approach to solving various types of satisfiable instances within the Hard Combinatorial track benchmarks. Unsurprisingly, the Random SAT track is dominated by local search solvers, and hence the minimum solver sets consist entirely of local search solvers.{sup:30} We believe that developing an improved understanding of the fact that all solvers had a unique solver contribution in the Random track might prove to be fruitful in light of developing new, perhaps more complex local search heuristics based on the SC 2012 solver submissions.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="6.6">
      <section-title>
       Impact of the computing environment
      </section-title>
      <paragraph>
       Before running the competition, we measured the variance in runtime when simultaneously running two ({a mathematical formula}(2/8) scenario), four ({a mathematical formula}(4/8) scenario) or eight ({a mathematical formula}(8/8) scenario) solvers on a node of the cluster used for the competition. The computing nodes have two sockets, each with a quad-core CPU that, in turn, consists of two dual-core dies. Note that, at least in principle, the {a mathematical formula}(1/8) scenario is identical to the {a mathematical formula}(2/8) scenario due to each node having two independent sockets (we have also confirmed this experimentally). The topology of the CPUs is represented in Fig. 10.{sup:31}
      </paragraph>
      <paragraph>
       The EDACC computation client is designed to perform a CPU architecture topology scan prior to starting the solvers (using Portable Hardware Locality hwloc) in an attempt to minimize the number of resource (cache and memory) collisions. When we start two solvers per node on the system (see Fig. 10), the client will guarantee to start the solvers on disjunctive sockets (to avoid memory and cache collisions). If we would start four solvers on a node, the client will start the solvers on cores that do not share L2 cache. While multi-core CPUs allow for running several solver instantiations on a single CPU/computing node in parallel, this may have a non-deterministic effect on the runtime behavior of the solvers. In the following, we provide results on experiments on the influence of the number of solvers per node on the runtimes of both CDCL and SLS solvers. These experiments were run before the SC 2012 benchmark selection. Based on the results, we decided to limit the number of simultaneous solver runs to two per node.{sup:32}
      </paragraph>
      <section label="6.6.1">
       <section-title>
        CDCL solvers
       </section-title>
       <paragraph>
        CDCL solvers are relatively memory intensive when compared to other solving techniques, and when it comes to cache sharing their performance is expected to drop. We evaluated two of the best performing CDCL solvers glucose and lingeling (the binary versions submitted to the 2011 SAT Competition) on the SAT-Race 2010 instances by running every solver on every instance five times. The multiple runs per instance are needed to measure the runtime variability on the same instance. The memory limit was set to 3.5 GB for the {a mathematical formula}(2/8) and {a mathematical formula}(4/8) scenario and 2 GB for the {a mathematical formula}(8/8) scenario. The 2-GB limit resulted in a memory problem on 2 instances that were very large.
       </paragraph>
       <paragraph>
        Fig. 11 shows a cactus plot for the CDCL solvers executed under the three different scenarios. Table 21 lists the detailed results. There is almost no difference between executing two or four solvers per node (the green and blue curves). The variation in runtime per instance though is larger for glucose, whereas lingeling shows almost no difference, which is probably due to better memory management. When using all eight cores, the performance of both solvers drops significantly, likely due to sharing of the same L2 cache. In the {a mathematical formula}(2/8) scenario we can see small conglomeration blocks in the runtime curves, which represent the five runs we have performed per instances.
       </paragraph>
       <paragraph>
        In the {a mathematical formula}(4/8) scenario these conglomerations loosen up, and in the {a mathematical formula}(8/8) scenario they are almost not identifiable. To analyze the variability in runtime, we have computed the average coefficient of variation which is ten times larger for the {a mathematical formula}(8/8) scenario than for the {a mathematical formula}(2/8) scenario independent of the solver (see Table 20 for more details).
       </paragraph>
      </section>
      <section label="6.6.2">
       <section-title>
        SLS solvers
       </section-title>
       <paragraph>
        SLS solvers are less memory intensive than CDCL-based solvers (since there is no clause learning involved), but still highly cache intensive due to frequent non-localized memory accesses. We ran the two best performing SLS solvers Sparrow2011 and sattime2011 from the 2011 SAT Competition on a set of 19 randomly generated k–SAT instances for {a mathematical formula}k=3,5,7, executing each solver four times on the same instance using different seeds. As can be seen from Fig. 12, there is almost no difference between the {a mathematical formula}(2/8) (green curve) and {a mathematical formula}(4/8) (blue curve), whereas the {a mathematical formula}(8/8) scenario shows significant degradation in the performance for both solvers.
       </paragraph>
       <paragraph>
        Performance degradation as a consequence of too many solvers per node appears to occur only when solvers have to share the cache hierarchy. Our analysis will also hold when the solvers get close to the memory limit but do not exceed it. Running four solvers per node would have been possible, but then the amount of memory available per solver would have dropped below 4 GB, which for some CDCL solvers could have been critical. Hence we ran only two solvers per node at a time, with a memory limit of 6 GB.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="7">
     <section-title>
      Lessons learned
     </section-title>
     <paragraph>
      In this section we discuss issues which were realized either during organizing SC 2012 or after the competition was run, and propose possible ways of dealing with these issues in forthcoming SAT and related solver competitions.
     </paragraph>
     <section label="7.1">
      <section-title>
       Progress with respect to previous competitions
      </section-title>
      <paragraph>
       Since the first SAT Competition in 2002, considerable progress has been made in improving both SAT solver performance and stability (see also [33] for a comparison of the best solvers from 2002 to 2011). Today, CDCL-based solvers are not only used within the SAT community, but are also widely employed as black-box solvers in many different projects and application areas (see, e.g., references mentioned in Section 1).
      </paragraph>
      <paragraph>
       Over the last years, and especially in 2012, we could see a continuing trend towards parallel and portfolio solvers. Whereas until 2009 Satzilla [63] was the only participating portfolio solver, and the first parallel solvers entered competitions only in 2007, in SC 2012 we had 19 solvers in the Parallel Track and 14 participating multi-engine or portfolio solvers. Multi-engine or portfolio solvers dominated the standard single-engine ones in both the Application and the Hard Combinatorial track in terms of runtime performance. Their success can be explained by their ability to overcome the shortcomings of a single, particular solving heuristic used in the single-engine solvers.
      </paragraph>
      <paragraph>
       However, considerable improvements could also be observed on basic algorithms for single-engine solvers. Especially the success of CCASat in the Random SAT Track, which implements a new local-search algorithm is remarkable. But also in the Application SAT+UNSAT Track, progress can be registered, for example in the case of glucose, the best single-engine solver, which has shown a considerably better performance than its 2011 version.
      </paragraph>
      <paragraph>
       To further illustrate the progress, let us take a closer look at two instances of the Application Track, which both had already been used in SAT-Race 2010. The problem bitverif/minxorminand128 (containing 153,834 variables and 459,965 clauses) could not be solved by any of the 20 solvers participating in SAT-Race 2010. In 2012, it was solved for the first time in less than 900 seconds (in 233 seconds by linge_dyphase). Similarly, the instance md5gen/gus-md5-10, encoding a cryptographic problem, and also not solved by any solver in 2010, was solved by six solvers in 2012.{sup:33}
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Benchmark selection
      </section-title>
      <paragraph>
       In Section 3.4 we pointed out a potential pitfall of the benchmark rating procedure that evaluates the empirical hardness of benchmarks using a limited set of SAT solvers: the selected set might be biased towards a particular solver used during evaluation, and thus a newer version of this solver used in the competition. Although increasing the number of evaluation solvers decreases this bias, it cannot fully eliminate it. In addition, such increase may be infeasible due to resource restrictions. Thus, the benchmark selection process must maintain a balance between the performance of the evaluation solvers on the selected benchmark set explicitly during the construction of the set. However, it is not entirely clear how possible attempts to “correct” bias towards particular solvers might affect the results of the competition. For example, eliminating bias towards a recently introduced, exceptionally well performing solver, might also lead to favoring already more established solver techniques implemented by many over new and highly potential techniques implemented by few. This in turn may lead to the competition results masking away potentially very important new solver techniques from becoming more standard ones.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Timeout and the number of benchmark instances
      </section-title>
      <paragraph>
       Enforcing a fixed limit on the computational resources (especially, the timeout in the case of SC 2012) poses challenges for any solver competition, and has connections to the number of benchmark instances used. Using a small timeout enables the use of more benchmark instances, and favors solvers which are geared towards solving relatively easy instances very fast but which may not perform well on harder instances. A large timeout favors solvers with robust performance in terms of solving instances of varying hardness and characteristics, but at the same time are likely to exhibit a higher average runtime on a smaller set of instances. In SC 2012 a somewhat small timeout of 900 seconds was enforced, while the number of benchmark instances per track per track was quite large (600). In contrast, in the past SAT Competitions a larger timeout (5000 seconds) and fewer instances (around 200-300) were used.
      </paragraph>
      <paragraph>
       Based on the analysis of the results presented in Section 6, at least in “short-timeout” competitions like SC 2012, the ranking of the top-performing sequential solvers can be established rather accurately using a smaller number of benchmark instances (300 instead of 600, cf. Section 6.3), and also with a somewhat smaller timeout value (450 seconds instead of 900, cf. Section 6.2). This is somehow surprising and puts the relatively high timeout of the SAT Competition (5000 seconds) into question.
      </paragraph>
      <paragraph>
       However, this is not the case for parallel solvers, whose ranking is affected to a very large degree by both the number of selected benchmarks and the cutoff. This is most likely due to the fact that the performance of these solvers is significantly less deterministic — due to nondeterminism caused by parallel execution, at the very least — than the performance of sequential solvers. Thus, it seems that resource allocation in future competitions should definitely favor parallel solvers to a large degree. Finally, elimination of a single fixed timeout as the basis of solver ranking could be another — perhaps more ambitious — goal, taking advantage of the fact that running experiments with a fixed timeout t easily produces results for any timeout {a mathematical formula}t′&lt;t.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Benchmark categorization
      </section-title>
      <paragraph>
       Specific benchmark instances may have both Application and Hard Combinatorial characteristics, with one notable example being the class of SAT encoded cryptographic problems, such as attacks against the block ciphers AES and DES (see discussion in Section 6.3), but other examples are abound — consider, for example, factoring vs. equivalence checking of multipliers. This means that the classification of benchmarks between the two classes is far from straightforward. Furthermore, as demonstrated by the results of the experiment described in Section 6.3, the changes in classification may have a dramatic effect on the rankings of the solvers. This is clearly an important issue that must be addressed in future competitions.
      </paragraph>
     </section>
     <section label="7.5">
      <section-title>
       Solver categorization
      </section-title>
      <paragraph>
       SAT Competitions have had to deal with different categories of solvers from the beginning. Initially, the main distinction was between complete DPLL/CDCL solvers, look-ahead solvers, and incomplete local-search algorithms. Each type of solver was specialized on certain benchmark instances, and thus the three categories of Application, Hard Combinatorial and (satisfiable) Random benchmarks emerged.
      </paragraph>
      <paragraph>
       Later, with the rise of multi-core CPUs, parallel SAT algorithms turned up, and in 2008 a special track for parallel solvers was added to the competitions. In 2007, a portfolio solver (SATzilla) won a medal for the first time, by combining different solvers (even different solver types), and applying machine learning techniques to detect the most suitable solver. The number of portfolio solvers submission has increased in the subsequent competitions. Lately, solvers combining ideas from different approaches and algorithms (which we called multi-engine solvers in SC 2012) also surfaced. With this growing diversity of SAT solving approaches, it becomes more and more complicated for competitions to choose the right tracks and benchmark sets to accommodate all solvers suitably, and to categorize solvers in the right way.
      </paragraph>
      <paragraph>
       One may wonder why solver categorization is needed at all. Why not have just one track with the union of all benchmarks on which the “globally best” solver is determined? One reason might be that a taxonomy of solvers is of scientific interest by itself (cf. Section 6.4). A more important rationale, in our opinion, is that by having different tracks, research on particular solver classes can be stimulated. Having, for example, a separate track for satisfiable random instances, gives stochastic local search solvers a chance to win a prize and thus furthers research in this area.
      </paragraph>
      <paragraph>
       In SC 2012, we mainly adopted the traditional categorization of solvers as laid down by previous competitions (CDCL vs. look-ahead vs. local search). We also kept the special track for Parallel Solvers introduced in 2008. For the first time, we introduced a special track for Sequential Portfolio Solvers, as these solvers had grown more important over the last years. This track was poorly accepted, though. Authors of solvers that we classified as “portfolio” pushed to get into the main tracks. We thus opened the main tracks for such solvers, too, at the same time adding a classification to the main tracks. We distinguished between (i) “traditional” solvers, which employ one core SAT algorithm (single-engine); (ii) simple combinations of existing solvers (portfolio), in which a focus is put on selecting the right solvers, e.g., by using machine-learning techniques; and (iii) more complex approaches using interacting combinations of different solvers (multi-engine), as described in Section 4. For SC 2012, we considered this distinction a good compromise between simplicity, historical evolution of categories, and separation of different solving techniques.
      </paragraph>
      <paragraph>
       As determination of solver categories allows, to some extent, to give a stimulus to particular research directions, we believe that it will remain a controversial topic in future competitions.
      </paragraph>
     </section>
     <section label="7.6">
      <section-title>
       Native implementations vs. building on existing solver source code
      </section-title>
      <paragraph>
       A recurring theme in recent SAT solver competitions has been that many competitors submit solvers which are relative small modifications of already available state-of-the-art open-source SAT solvers. In SC 2012, we saw a number of such solver submissions that were modifications or built on top of the successful Glucose solver. Here one should notice that Glucose itself is based on the successful Minisat solver. This raises the question of whom to give credit for a successful solver. As many SAT solvers are open source, it is quite easy to take existing solvers, and to either just modify them slightly or combine different such solvers into a new tool. One can argue whether the act of combining (or somewhat modifying) them is as significant a contribution to SAT solving technology as the ideas that went into the original solvers.
      </paragraph>
      <paragraph>
       This problem is aggravated by preprocessors (such as SatELite[86]) and similar tools, which are used as “add-on components” in existing solvers. Again, the question arises, how to handle such component-based solvers and whom to give credit for competition entrants that just replace or add a component.
      </paragraph>
      <paragraph>
       To partially deal with this problem, a MiniSat Hack Track was initiated in 2009, in which solvers that modify the source code of MiniSat by at most 5% could participate.{sup:34} By this construct, small contributions (with respect to implementation effort) to the state of the art in CDCL solvers were encouraged, while still giving credit to the original MiniSat authors.
      </paragraph>
      <paragraph>
       In SC 2012, there was no separation between native implementations of solvers and solver submissions that were heavily based on already available solver source code. We believe that more incentives should be provided for solver developers to actually implement their solvers from scratch, hence contributing to the maintenance of a heterogeneous set of publicly available SAT solvers. Apart from recognizing the overall best-performing solvers, giving formal recognition to solvers with large unique contributions to the VBS — of high interest to, e.g., portfolio solver developers — would be a good option to consider. This idea has also been suggested in [83].
      </paragraph>
      <paragraph>
       The MiniSAT Hack Track of the 2009 and 2011 SAT Competitions is one way of organizing a separate track for solvers heavily building on the source code of others. However, even irrespectively of whether the solvers are required to be submitted in open source to a competition, we foresee some difficulties to objectively evaluate to what extent a submitted solver relies on existing solver source code.
      </paragraph>
     </section>
     <section label="7.7">
      <section-title>
       Participation of portfolio solvers
      </section-title>
      <paragraph>
       The SAT Competition series was introduced to promote the practical development of SAT solvers and to provide a way to measure the utility of solving techniques and modifications proposed in the literature. The heterogeneity of the used benchmarks and the results produced by different solvers provide a perfect testbed for portfolio SAT solvers, which have shown remarkable performance in the last competitions. However, allowing portfolio solvers to compete in the same competition tracks as other solvers poses certain problems.
      </paragraph>
      <paragraph>
       One could argue that it is beneficial to enter portfolio solvers to the main competition tracks in order to measure the performance of the actual current state of the art in SAT solvers, often exhibited by portfolio solvers. However, portfolio SAT solvers use outdated core SAT solvers by default. This is due to the fact that the portfolio submitted to a competition cannot contain actual core solvers submitted to the same solver competition, since the core solver developers generally do not make their solvers available before the competition. Thus the performance of portfolio solvers submitted to a specific competition could likely be improved simply by including the best-performing new solvers, submitted to the same competition, to the portfolios.{sup:35} A fundamental question is what actually constitutes “state–of–the–art”, in case core solvers are made to directly compete with portfolio approaches. Assume, for example, that a portfolio solver using solvers from over two years back ends up winning a track. In our opinion, this does not directly imply that the improvements to the core solvers within the last two years have not been significant. However, we do believe that it is valuable to know how well the best portfolio solvers perform in comparison to the current state–of–the–art core SAT solvers.
      </paragraph>
      <paragraph>
       A more competition-oriented issue, arising from allowing portfolio solvers (and other types of multi-engine approaches using external core solvers in a black-box manner) to compete for the same awards as the core solvers, is fairness from the side of the core solver developers. This is due to the fact that the portfolio approaches directly capitalize on the advancements in the core SAT solvers by employing the core solvers in a black-box manner.
      </paragraph>
      <paragraph>
       A separate track for portfolio solvers would seem to be the correct way to measure the advances in portfolio solvers. The aim would be to objectively evaluate the core part of intelligent portfolio approaches, namely, the algorithms applied within the portfolio to select the solver that is run on a given input instance. In such a track, the set of solvers available, as well as the set of training instances, should be fixed by the organizers a priori. Entrants submitted to the track would consist of the solver selection methods only, without any a priori training. The solver selection methods would then be trained using the fixed set of training instances. The performance of the submitted solver selection methods should then be measured on a separate test set. This approach to evaluating portfolios would allow to more objectively measure the merits of the most important methods implemented within portfolios, namely, the SAT solver selection algorithms. Ideally, such a portfolio competition would be run immediately after the main core SAT solver competition of the same year, so that the most recent best-performing core solvers could be included in the set of solvers available in the portfolio.
      </paragraph>
     </section>
     <section label="7.8">
      <section-title>
       Ranking schemes
      </section-title>
      <paragraph>
       Our analysis of the correlation between the rankings established with different ranking schemes (see Section 6.1) suggests that the more elaborate careful ranking (CR) scheme would produce very similar results to the currently used solution count ranking (SCR) as well as the PARx ranking scheme family. On the other hand, SCR benefits from transitivity and, perhaps, from being more intuitive and accessible to researchers outside the SAT community. As such, in our opinion, SCR is an adequate scheme for future SAT competitions.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Values for generating the random SAT track benchmarks
     </section-title>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Results of SC 2012: full rankings
     </section-title>
     <paragraph>
      {a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>