<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    SAT Race 2015.
   </title>
   <abstract>
    Boolean satisfiability (SAT) solving is one of the most competitive research areas of theoretical computer science. The performance of state-of-the-art SAT solvers has been continuously improving in the last decades and has reached a level where SAT solvers can be employed to solve real world problems in fields such as hardware and software verification, automated planning and many others. One of the important driving forces of this progress are the yearly organized (since 2002) SAT competitions. In this paper we describe the 2015 SAT Race that featured the traditional sequential and parallel tracks (with 64 core computers) and introduced the Incremental Library Track, which is particularly interesting for developers of SAT based applications. We describe the 2015 SAT Race and provide a detailed analysis of its results.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      One of the most studied problems of theoretical computer science is the Boolean satisfiability (SAT) problem. SAT solving has many practical applications, and SAT solvers are used in the background as high performance reasoning engines in several A.I. applications such as automated planning and scheduling [1], formal verification [2] or automated theorem proving [3]. Despite the fact, that SAT is NP-complete [4] the performance of state-of-the-art SAT solvers has increased dramatically in the last decades thanks to the invention of advanced heuristics [5], preprocessing and inprocessing techniques [6] and data structures that allow efficient implementation of search space pruning [5].
     </paragraph>
     <paragraph>
      One of the ways to keep up the driving force in improving SAT solvers is the organization of SAT competitions. The first SAT competition was organized in 1992 [7] followed by the second in 1993 [8] and the third in 1996. Since 2002 a SAT competition – sometimes under the names SAT Race and SAT Challenge – is organized every year and is associated with the SAT conference.{sup:1}
     </paragraph>
     <paragraph>
      SAT Races – the first being organized in 2006 – put a strong emphasis on application benchmarks and are generally on a smaller scale (fewer benchmarks, smaller time limits) than SAT Competitions, which also include tracks for random and “crafted” formulas, the latter being purposefully built to challenge current SAT algorithms. A more detailed overview of the history of the SAT competitions can be found in [9].
     </paragraph>
     <paragraph>
      Even though sharing the same motivation, the SAT Race organized in 2015 was different from previous competitions in several aspects.
     </paragraph>
     <list>
      <list-item label="•">
       Five runs were performed for each benchmark/solver pair in the Main Track (in previous competitions only one).
      </list-item>
      <list-item label="•">
       We used a higher number of cores (64) in the Parallel Track than previous competitions (16–32).{sup:2}
      </list-item>
      <list-item label="•">
       For the first time an Incremental Library Track was organized and a new standard interface for incremental SAT solving (IPASIR) was introduced.
      </list-item>
     </list>
     <paragraph>
      This paper describes the 2015 SAT Race, its organizational details and results. Large part of the paper is devoted to the Incremental Track and the detailed description of the proposed incremental interface – IPASIR. We hope that IPASIR (or its extension) becomes a standard interface for incremental SAT solver implementations.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      A Boolean variable is a variable with two possible values True and False. By a literal of a Boolean variable x we mean either x or {a mathematical formula}x‾ (positive or negative literal). A clause is a disjunction (OR) of literals. A conjunctive normal form(CNF)formula is a conjunction (AND) of clauses. A clause can be also interpreted as a set of literals and a formula as a set of clauses. A truth assignment ϕ of a formula F assigns a truth value to its variables. The assignment ϕ satisfies a positive (negative) literal if it assigns the value True (False) to its variable and ϕ satisfies a clause if it satisfies at least one of its literals. Finally, ϕ satisfies a CNF formula if it satisfies all of its clauses. A formula F is said to be satisfiable if there is a truth assignment ϕ that satisfies F. Such an assignment is called a satisfying assignment. The satisfiability problem (SAT) is to find a satisfying assignment of a given CNF formula or determine that it is unsatisfiable.
     </paragraph>
     <paragraph>
      Most current complete state-of-the-art SAT solvers are based on the conflict-driven clause learning (CDCL) algorithm [10]. For a detailed description of CDCL refer to [11].
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Competition overview
     </section-title>
     <paragraph>
      The 2015 SAT Race featured three tracks. Two traditional tracks – the Sequential and Parallel Tracks and the Incremental Library Track, which had its debut. An overview of all participants and their solvers is presented in Table 1. Each participant was allowed to submit at most two solvers (or two versions of one solver) to each track. Except for the Incremental Library Track the submission of source code was optional. The following sections describe organizational aspects of the tracks.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Main Track
     </section-title>
     <paragraph>
      The Main Track is the most popular track of each SAT competition. In total 28 solvers (solver versions) developed by 18 different groups participated in the 2015 SAT Race. Except for CBPeneLoPe each solver had at least one version participating in the Main Track. See Table 1 for a complete list of solvers and their authors.
     </paragraph>
     <paragraph>
      In the remainder of the section we describe the benchmarks submitted for the competition, the method we used to select the final set of benchmark problems and how the results were evaluated.
     </paragraph>
     <section label="4.1">
      <section-title>
       Submitted benchmarks
      </section-title>
      <paragraph>
       In the following text we briefly describe the 6 benchmark families submitted for 2015 SAT Race. All of them are – in the spirit of the SAT Races – considered application or industrial benchmarks. The detailed descriptions of the benchmarks can be found on the website of the SAT Race.{sup:3}
      </paragraph>
      <paragraph>
       Factorization by Joe Bebel  These satisfiable instances encode the factorization of the products of pairs of large prime numbers. The generator is based on Karatsuba multiplication.
      </paragraph>
      <paragraph>
       Pseudo-industrial random by Jesús Giráldez-Cru and Jordi Levy  The generator is using the Community Attachment model to create random instances with high modularity (a property characteristic for “real-world” problems).
      </paragraph>
      <paragraph>
       Modulo game solving by Tobias Sebastian Hahn, Norbert Manthey and Tobias Philipp  The Modulo game is a combinatorial puzzle where tiles are to be placed on a field such that the sum of all overlaying values of a cell sums up to a multiple of a predefined value.
      </paragraph>
      <paragraph>
       Single Track gray codes by Norbert Manthey  These instances allow the construction of (Single Track) Gray codes by searching a solution to a specification.
      </paragraph>
      <paragraph>
       Multi-robot path planning by Pavel Surynek  The instances model the question whether a set of robots can find paths in a grid with obstacles in a given number of time steps.
      </paragraph>
      <paragraph>
       Verification of cryptographic algorithms by Aaron Tomb  These benchmarks are derived from the problem of comparing reference and production implementations of cryptographic algorithms.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Benchmark selection
      </section-title>
      <paragraph>
       Since the number of available benchmark problems for SAT solving is huge while computational resources are limited it is necessary to somehow select a subset of the instances to be used for a competition. A good competition benchmark collection should have the following properties.
      </paragraph>
      <list>
       <list-item label="•">
        The instances are not too easy – Comparing solvers on trivial instances that any solver can solve is not interesting and can be disadvantageous for complex solvers using advanced and novel techniques.
       </list-item>
       <list-item label="•">
        The instances are not too hard – Instances that none of the participating solvers can solve in the given time limit do not provide any information about the relative performance of the competing solvers.
       </list-item>
       <list-item label="•">
        The selection is unbiased and fair – A selection can be favoring a certain solver or group of solvers and/or being disadvantageous for others.
       </list-item>
       <list-item label="•">
        Many new instances are included – Using the same (or very similar) instances every year could result in solvers being over-optimized for competition benchmarks and not performing well on other problems of interest.
       </list-item>
      </list>
      <paragraph>
       We used the following selection algorithm to select 300 instances for the Main (and 100 for the Parallel) Track from among the newly submitted benchmarks and the benchmarks used in the last years (2014) SAT competition. The selection method is similar to the ones used in the previous competitions.
      </paragraph>
      <list>
       <list-item label="•">
        First we randomly selected 3 out of the top 7 solvers from the previous competition (participants of the Sequential and Application {a mathematical formula}SAT+UNSAT Tracks of the SAT Competition 2014).
       </list-item>
       <list-item label="•">
        We ran the selected solvers on all the benchmarks (newly submitted and 2014 SAT Competition) with a 1 hour time limit.
       </list-item>
       <list-item label="•">
        Let us define the hardness of an instance as the total time the three solvers spent on it (maximum is 3 hours in the case that none of the solvers could solve the instance within the time limit). Using the hardness value, we randomly selected 300 instances based on the normal distribution with mean 1.5 and standard deviation 1.
       </list-item>
       <list-item label="•">
        Those 300 instances were used for the Main Track and the hardest 100 among them for the Parallel Track.
       </list-item>
      </list>
      <paragraph>
       The final selection contained 167 new and 133 old benchmark problems. Therefore the goal of including many new benchmarks was satisfied. As for the fairness, this selection method is not ideal. Its main drawback is that we are using the previous winning solvers to select new benchmarks. Therefore instances that are too hard for them are not selected which can be disadvantageous for other (innovative) solvers that might be able to solve them. On the other hand, benchmarks that are easy for the previous winners but hard for others are also omitted resulting in a disadvantage for the previous winners. Designing a fair benchmark selection method is a complex issue which should be studied further and improved in the following competitions.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Evaluation and prizes
      </section-title>
      <paragraph>
       In this year's SAT Race we did five runs for each solver benchmark pair.{sup:4} The solvers were compared based on the average number of problem instances solved within the time limit of one hour in the five runs.
      </paragraph>
      <paragraph>
       The evaluation was performed using the StarExec cross community logic solving service developed at the University of Iowa{sup:5}[12]. StarExec consists of 192 nodes with Intel{sup:®} Xeon{sup:®} CPU E5-2609 processors, having four compute cores (no hyper-threading) running at 2.40 GHz (2393 MHZ) and 256 GB of main memory using the Red Hat Enterprise Linux{sup:6} operating system. The participants uploaded their solvers in the form of binary executables using a web interface, therefore the compilation was performed by the participants. Our experience with StarExec was very positive, it is a very convenient tool for organizing a SAT (or other) competitions.
      </paragraph>
      <paragraph>
       Three prizes were given out to the top three solvers (solving the highest number of instances) and a fourth (special) prize to the “most innovative” solver. The special prize was selected by a ranking method that uses the number of solved instances not solved by the top three solvers of the track. Each solver received for each instance it solved:
      </paragraph>
      <list>
       <list-item label="•">
        4 points if none of the top three solvers solved the instance.
       </list-item>
       <list-item label="•">
        2 points if exactly one of the top three solvers solved the instance.
       </list-item>
       <list-item label="•">
        1 point if exactly two of the top three solvers solved the instance.
       </list-item>
       <list-item label="•">
        0 points if all the top three solvers solved the instance.
       </list-item>
      </list>
      <paragraph>
       The special prize was awarded to the solver receiving the highest number of points.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Parallel track
     </section-title>
     <paragraph>
      Parallel computing is a hot research topic in computer science, especially since parallel computers became ubiquitous.
     </paragraph>
     <paragraph>
      However, there are inherent limitations to the efficient parallelizability of resolution-based SAT procedures. This is in part due to the structure of resolution proofs [13], but also due to the fact that most sequential SAT solvers spend 80% of their runtime by doing unit propagation [14] which is a P-complete problem [15]. Still, modern parallel solvers such as ManySat [16] or Plingeling [17] often achieve superlinear speedups for many benchmarks.
     </paragraph>
     <section label="5.1">
      <section-title>
       Portfolios
      </section-title>
      <paragraph>
       A common way of designing a parallel SAT solver is the so called portfolio approach. A portfolio is a collection of SAT solvers (different SAT solvers or different versions of the same SAT solver). The solvers are ran on the same problem in parallel until one of them finds a solution. The solvers can additionally exchange useful information such as learned clauses or variable activity statistics. All current state-of-the-art parallel SAT solvers are based on this approach (judging by the results of recent SAT competitions).
      </paragraph>
      <paragraph>
       Nevertheless, in the context of SAT competitions the portfolio approach is somewhat problematic. As demonstrated by the solver PPfolio in the 2011 SAT Competition, it is possible to win several tracks of the competition by just taking the best solvers from the previous competition and trivially combine them using a shell script into a portfolio. The author of PPfolio argues that such a simple portfolio solver can serve as approximating the “virtual best solver” (see Sec. 7). But he also “shamelessly claims” [18] that “it's probably the laziest and most stupid solver ever written” which “does not even parse the CNF” and “knows nothing about the clauses”. A portfolio solver winning the competition can be very demotivating for the developers of core solvers since someone else is winning with their solver.{sup:7}
      </paragraph>
      <paragraph>
       To avoid this situation in the 2012 SAT Challenge and 2013 SAT Competition a special track was created for portfolio solvers, which were not allowed to enter any of the other tracks. In the 2014 Sat Competition portfolio solvers were not allowed to participate in any of the tracks. In our competition we took a different approach. Portfolio SAT solvers were allowed to participate in each track provided that the authors of the portfolio had consulted all the authors of the used core solvers and received permission for such usage.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Benchmarks and evaluation
      </section-title>
      <paragraph>
       The hardest 100 instances of the 300 instances selected for the Main Track (see Section 4.2) were used as benchmarks for the Parallel Track. The hardness is defined in Section 4.2. Eleven solvers (solver versions) participated in the Parallel Track. The list of participating solvers is displayed in Table 1.
      </paragraph>
      <paragraph>
       Due to limited computation resources only one evaluation run was performed for each solver-benchmark pair. The wall-clock time (as opposed to CPU time) was measured for each run. The evaluation was performed on a computer with four octa-core Intel Xeon E5-4640 (2.4 GHz) processors (in total 32 physical and 32 hyper-threading cores) with 512 GB of main memory. This is the highest level of parallelism used in the history of SAT competitions.{sup:8} It should be noted, though, that the virtual cores provided by hyper-threading are not equivalent to physical cores, as they benefit only from wait states of a physical core to execute instructions of another thread. In fact, some solvers decided to use only 32 worker threads. We expect that for those solvers the authors experimentally determined that they do not profit from the additional virtual cores. Solvers using only 32 worker threads in the 2015 SAT Race were Plingeling and one version of Glucose (glucose-default). For the solvers pcasso-bb and pcasso it could not be determined how many worker threads they employed.
      </paragraph>
      <paragraph>
       Three prizes were awarded in the Parallel Track based on the number of solved instances in the time limit of one hour per instance. The actual runtimes were not considered for the ranking.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Incremental Library Track
     </section-title>
     <paragraph>
      In the 2015 SAT Race we introduced a new track for solvers supporting interactive incremental SAT solving – the Incremental Library Track (ILT). The ILT differs significantly from all the other (traditional) tracks of the SAT competitions in the following aspects:
     </paragraph>
     <list>
      <list-item label="•">
       In the traditional tracks we evaluate command line applications which take text files as input and produce text output. In the ILT we evaluate software libraries and communicate with them via function calls.
      </list-item>
      <list-item label="•">
       The benchmarks for the traditional tracks are text files specifying a CNF formula. A benchmark for the ILT is an application (and inputs for it) that uses SAT solvers interactively.
      </list-item>
     </list>
     <paragraph>
      In this section we first describe the motivation for the ILT and then give the detailed specification of the application program interface (API) that we designed and used to evaluate the incremental SAT solvers. The section is concluded by describing the benchmark programs used in the ILT (which also serve as demonstration of the API usage) and discussing the evaluation process of the ILT participants.
     </paragraph>
     <section label="6.1">
      <section-title>
       Motivation
      </section-title>
      <paragraph>
       Many applications of SAT are based on solving a sequence of similar SAT formulas. The next formula in a sequence is usually generated by adding/removing a few clauses or variables to/from the previous formula. It is possible to solve such problems by solving the incrementally generated instances independently, however this might be very inefficient compared to an incremental SAT solver, which can reuse knowledge acquired while solving the previous instances (for example the learned clauses and variable activity statistics).
      </paragraph>
      <paragraph>
       Most of the current state-of-the-art SAT solvers support incremental SAT solving, however each has its own interface, which differs from the others. That makes comparing them difficult. We believe it would be beneficial to have a single universal interface implemented by all the solvers supporting incremental SAT solving. Users who need to use incremental SAT solvers in their applications would strongly benefit from such a unified interface. Applications could be written without selecting a concrete incremental SAT solver in advance and migrating to a different solver would be just a matter of updating linking parameters.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       The proposed interface – IPASIR
      </section-title>
      <paragraph>
       The name of the interface proposed for the 2015 SAT Race is IPASIR, which is the reversed acronym for “Re-entrant Incremental Satisfiability Application Program Interface.{sup:9}”
      </paragraph>
      <paragraph>
       The interface was designed to have the following properties:
      </paragraph>
      <list>
       <list-item label="•">
        Easy to implement by SAT solver developers.
       </list-item>
       <list-item label="•">
        Easy to use, so that anyone can easily build SAT based applications (for industrial, scientific, educational or other purposes).
       </list-item>
       <list-item label="•">
        Universal and powerful, i.e., usable in a broad range of applications.
       </list-item>
      </list>
      <paragraph>
       The interface consists of nine C language functions which are inspired by the incremental interfaces of PicoSAT and Lingeling. The declarations of the functions along with short descriptions are displayed in Fig. 1. The detailed specifications are given below.
      </paragraph>
      <paragraph>
       The nine functions of the IPASIR interface can be split into two groups. The first group (service functions) contains four functions: ipasir_signature, ipasir_init, ipasir_release and ipasir_set_terminate.
      </paragraph>
      <paragraph>
       ipasir_signature  The function ipasir_signature is used to identify the solver implementing the interface. The SAT solver is expected to return a C-style string containing its name and version.
      </paragraph>
      <paragraph>
       ipasir_init  The purpose of the ipasir_init function is to create a new instance of the solver and return a pointer to it. This pointer is used as the first argument in all of the remaining seven functions.
      </paragraph>
      <paragraph>
       ipasir_release  To destroy a solver, i.e., release all its resources and deallocate the memory it used we provide the ipasir_release function. The solver pointer cannot be used for any purposes after calling this function.
      </paragraph>
      <paragraph>
       ipasir_set_terminate  The ipasir_set_terminate function can be used to specify a callback function which indicates whether the search should be aborted. The signature of the callback function is “int terminate(void* state)”. It returns a non-zero value if the search is to be terminated. The solver is required to call this function periodically during the search process and abort it as soon as possible when a non-zero value is returned. The value of the parameter state in the calls of the callback function is identical to value received as the second argument of ipasir_set_terminate.
      </paragraph>
      <paragraph>
       The second group of functions is used for SAT solving and contains the remaining five functions of the IPASIR interface. To better understand the semantics of these functions we define four states of the solver – UNKNOWN, SOLVING, SAT and UNSAT. After the ipasir_init call the solver is in the UNKNOWN state and is ready to receive input in the form of clauses and assumptions (see below). When the ipasir_solve function is called the state of the solver changes into SOLVING. When the search process is completed the state changes to SAT or UNSAT depending on the result. The search might also get aborted (via returning a non-zero value in the callback function), then the state of the solver changes back to UNKNOWN. Fig. 2 contains a diagram with the states and the allowed transitions between them. The label of each edge contains the names of the functions that can achieve the given transition.
      </paragraph>
      <paragraph>
       ipasir_add  The formula to be solved is specified using the ipasir_add function. The clauses are added one literal at a time. Calling the ipasir_add function with a non-zero second argument adds a literal (specified by the argument) to the current clause. If the argument is zero, then the current clause is finalized and the next ipasir_add function call will initialize a new clause and add one literal to it. Literals are encoded as (non-zero) integers as in the DIMACS formats. They have to be smaller or equal to INT_MAX and strictly larger than INT_MIN (to avoid negation overflow). This applies to all the literal arguments in API functions. For example adding the clauses {a mathematical formula}(x1∨¬x3) and {a mathematical formula}(x2) is achieved by the following sequence of calls: ipasir_add(s, 1), ipasir_add(s, -3), ipasir_add(s, 0), ipasir_add(s, 2), ipasir_add(s, 0). Clauses added this way cannot be removed. The addition of removable clauses can be simulated using activation literals and assumptions.{sup:10} The ipasir_add function may be called in any of the UNKNOWN, SAT and UNSAT states and it always results in the UNKNOWN state.
      </paragraph>
      <paragraph>
       ipasir_assume  Assumptions in incremental SAT solving can be viewed as temporary unit clauses. Assumptions can be specified by calling the ipasir_assume function, which takes literals encoded as integers in the same way as the add function. All the added assumptions are valid only for the next ipasir_solve call. When the ipasir_solve call is finished all the assumptions are removed and a new set of assumptions can be specified. The removal of assumptions happens regardless of whether the search was aborted or completed. Similarly to ipasir_add the ipasir_assume function may be called in the UNKNOWN, SAT and UNSAT states and always results in the UNKNOWN state.
      </paragraph>
      <paragraph>
       ipasir_solve  The most important function of the interface is ipasir_solve. It is used to solve the formula specified using the ipasir_add calls under the assumptions given by the ipasir_assume calls. When called, the solver changes to the SOLVING state until the formula is solved or the search is interrupted. If a satisfying assignment is found it returns the value 10 and the state of the solver is changed to SAT. In the case, that the problem is proven to be unsatisfiable, the function returns the value 20 and changes the state to UNSAT. If the search process was interrupted the return value is 0 and the solver returns to the UNKNOWN state. In each of the three cases the assumptions added before the ipasir_solve call are erased.
      </paragraph>
      <paragraph>
       ipasir_val  In the case that ipasir_solve found a satisfying assignment and therefore the solver is in the SAT state we can call the ipasir_val function to retrieve the value of a variable (or literal). The return value of ipasir_val(s,lit) is {a mathematical formula}+lit if lit is true/satisfied under the solution and {a mathematical formula}−lit otherwise. The return value might be zero in the case that the truth value of the given variable (literal) is not assigned in the satisfying partial truth assignment. By calling ipasir_val for each variable we can retrieve the complete satisfying assignment. A call to ipasir_add or ipasir_assume invalidates the current solution and changes the state of the solver to UNKNOWN therefore calling ipasir_val is not allowed anymore.
      </paragraph>
      <paragraph>
       ipasir_failed  If a formula is determined to be unsatisfiable under certain assumptions it is of interest to know which of the assumptions were actually used to prove the unsatisfiability. The conjunction of all used assumptions is already sufficient to prove unsatisfiability of the formula (see, e.g., [19]). This information can be retrieved by calling the ipasir_failed function using the assumption in question as the argument. The return value is 1 if the assumption was used and 0 otherwise. Analogously to ipasir_val the function ipasir_failed may only be called in the UNSAT state, i.e., between the call of ipasir_solve (which returned 20) and the first following call of ipasir_add or ipasir_assume.
      </paragraph>
      <paragraph>
       The reader might wonder why is it allowed to call ipasir_solve from the SAT and UNSAT states. In the case of SAT it makes, indeed, no sense while the formula cannot change its satisfiability status without new input in the form of clauses or new assumptions from the user. However, in the case of UNSAT the unsatisfiability might be caused by the assumptions. Since after each ipasir_solve call the assumptions are cleared the input has changed in a way that the formula might be satisfiable now.
      </paragraph>
      <paragraph>
       We have described all the nine functions of the IPASIR interface. Examples of IPASIR usage can be found in Section 6.4 where we describe the benchmark applications used in the ILT.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Participation
      </section-title>
      <paragraph>
       For the participants of the ILT we prepared a package (ipasir.zip{sup:11}) containing three SAT solvers (MiniSat, PicoSat and Sat4j) adapted to IPASIR and four simple IPASIR based applications for demonstration and benchmarking purposes. One of the adapted SAT solvers included in the package was the Java SAT solver Sat4j. We included Sat4j to demonstrate that although IPASIR is specified as a set of C functions it is possible to implement it in other languages than C/C++. The package also contains a simple Java binding and Java application to show how any IPASIR compatible SAT solver can be used in a Java application. The description of the example applications contained in the ipasir package, which were later also used as benchmark applications, can be found in the next subsection.
      </paragraph>
      <paragraph>
       In order to participate in the ILT the participants were required to implement all nine functions (see Fig. 1) of IPASIR following the specifications given in the previous section. The participants were asked to prepare a makefile that compiles their solver and generates a Linux static library (.a file – object code archive file). Detailed instructions and examples on how to do this were included in the ipasir.zip package.
      </paragraph>
      <paragraph>
       Eight solvers (solver versions) were submitted for the ILT, which we consider a very nice number considering that the ILT was organized for the first time. The list of participating solvers can be seen in Table 1.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Benchmarks
      </section-title>
      <paragraph>
       This section has two purposes. One is to describe the benchmark applications used in the ILT and the other is to demonstrate the usage of the IPASIR interface on simple examples.
      </paragraph>
      <paragraph>
       In general, the benchmarks for the ILT consist of a command line application that solves some kind of a problem and a set of inputs for it. An example is a MaxSAT solver and a collection of MaxSAT instances.
      </paragraph>
      <paragraph>
       We start with a very detailed description of the first ILT benchmark application – Essentials. The remaining three benchmarks are described only briefly. The source codes of all the applications can be found in the ipasir.zip package on the website of the 2015 SAT Race [20].
      </paragraph>
      <section label="6.4.1">
       <section-title>
        Essentials
       </section-title>
       <paragraph>
        Essentials is a detector of variables essential for satisfiability. For a satisfiable formula F and a variable x we say that x is essential for the satisfiability of F if x has to be assigned to True or False in each (partial) satisfying assignment of F.
       </paragraph>
       <paragraph>
        Essentials is based on the so called dual-rail encoding of Boolean formulas [21] which works the following way. For each variable x occurring in a formula F we define two new variables {a mathematical formula}xT and {a mathematical formula}xF. These variables represent the fact that x is assigned to the value True ({a mathematical formula}xT) or False ({a mathematical formula}xF). If both {a mathematical formula}xT and {a mathematical formula}xF are False then x is unassigned, the case that they are both True is not allowed which can be expressed via binary clauses of the form {a mathematical formula}(¬xT∨¬xF).
       </paragraph>
       <paragraph>
        To construct the dual-rail encoding of a CNF formula F we replace each positive occurrence of x by {a mathematical formula}xT and each negative occurrence by {a mathematical formula}xF in all the clauses of F for each variable x that occurs in F. Additionally we add a binary clause of the form {a mathematical formula}(¬xT∨¬xF) for each variable (see previous paragraph). For example the dual rail encoding of the formula {a mathematical formula}(x∨¬y∨z)∧(¬x∨¬y)∧(¬z) would be {a mathematical formula}(xT∨yF∨zT)∧(xF∨yF)∧(zF)∧(¬xT∨¬xF)∧(¬yT∨¬yF)∧(¬zT∨¬zF).
       </paragraph>
       <paragraph>
        In Fig. 3 we present the full code of the main function of the Essentials application. We assume that the input formula (which is satisfiable) is already parsed and we receive it as the parameter. The formula is represented as a struct containing the number of variables and clauses (as integers) and an array of clauses. Clauses are represented as structs containing the number of literals and an array of literals represented as integers.{sup:12}
       </paragraph>
       <paragraph>
        In the first three lines we have helper functions computing the indices of the dual rail variables. The function pdr represents the translation of x to {a mathematical formula}xT and ndr the translation of x to {a mathematical formula}xF. The function dr translates literals by checking whether they are positive or negative and then calling pdr or ndr respectively.
       </paragraph>
       <paragraph>
        The solver is initialized on line 6. On lines 7–12 we do the dual-rail encoding of the original clauses of the formula. On lines 13–17 we add the binary clauses ensuring that the variables cannot be both True and False at the same time.
       </paragraph>
       <paragraph>
        The checking of the essentiality property happens on lines 18–26. For each of the variables we assume that they are not assigned. On line 19 we assume that the variable is not assigned to True and on 20 that not to False. Then we check the satisfiability of the formula under these assumptions. If the formula is unsatisfiable then the variable is essential for satisfiability. Note, that in the next iteration of the for loop the previous assumptions are removed.
       </paragraph>
       <paragraph>
        The input of the Essentials application is CNF Boolean formulas – same as SAT solvers. In the 2015 SAT Race we selected the 50 easiest instances of the Main Track as benchmarks.
       </paragraph>
      </section>
      <section label="6.4.2">
       <section-title>
        Partial MaxSAT solver
       </section-title>
       <paragraph>
        The benchmark application PMaxSAT is an iterative strengthening based partial MaxSAT solver. A partial MaxSAT formula consists of two kinds of clauses – soft and hard. The goal of partial MaxSAT solving is to find a truth assignment that satisfies all the hard clauses and as many as possible soft clauses in a given formula.
       </paragraph>
       <paragraph>
        The pseudo-code of PMaxSAT is displayed in Fig. 4. The program returns the maximum number of soft clauses that can be satisfied while satisfying all the hard clauses. If the set of hard clauses is unsatisfiable it returns zero.
       </paragraph>
       <paragraph>
        After the initialization of the solver we add the hard clauses using ipasir_add calls. The next step is to add the soft clauses. We add each soft clause with an extra variable called an activation variable. The activation variable is unique for each soft clause and does not appear anywhere in the original formula. Then we check the satisfiability status of the formula. At this point this is equivalent to checking that the hard clauses are satisfiable since all the soft clauses can be easily satisfied by setting all the activation literals to True. If the formula is satisfiable we count the number of soft clauses that are satisfied by at least one of their original literals, i.e., not by their activation variable. We save this value as the best solution so far and try to improve it. We do this by adding a cardinality constraint which says that the number of activation literals set to True must be strictly less than the best solution found so far. The cardinality constraint is translated into CNF and added using ipasir_add calls. For this translation we employ the PBLib Library [22]. After the cardinality constraint is added we solve the formula again. We repeat the cycle of solving and strengthening as long as the formula is satisfiable.
       </paragraph>
       <paragraph>
        The PMaxSAT takes input in the form of WCNF files which is the standard input of MaxSAT solvers. For the ILT we used the 568 PMaxSat problems from the Industrial Track of the 2014 International MaxSat Competition.
       </paragraph>
      </section>
      <section label="6.4.3">
       <section-title>
        Parallel portfolio
       </section-title>
       <paragraph>
        The next benchmark application is a simplistic parallel portfolio SAT solver. The Portfolio application creates four instances of the incremental solver and adds all the input clauses to each of them. In order to achieve some degree of diversification the ordering of the clauses is randomly shuffled for each of the solver instances. A callback function for termination is added to each of the solver instances (by calling ipasir_set_terminate). The callback function is the same for each solver and all it does is return the value of a global variable which is initialized to zero. Any solver instance that solves the problem will set this variable to the value 1, which results in aborting the search by the still running solver instances. Finally four threads are created which call the ipasir_solve function of the corresponding solver instance.
       </paragraph>
       <paragraph>
        This application is not really an incremental SAT application since it calls the solve function only once (in each thread). Nevertheless it is useful for testing whether the solver is functioning properly and efficiently in a multithreaded environment.
       </paragraph>
       <paragraph>
        The input of the Portfolio application is CNF Boolean formulas. As input we used the 100 instances from the Parallel Track of the SAT Race.
       </paragraph>
      </section>
      <section label="6.4.4">
       <section-title>
        Incremental file interpreter
       </section-title>
       <paragraph>
        The incremental file interpreter benchmark application is the only benchmark in the ILT that was not created by the organizers of the 2015 SAT Race. It was submitted by Florian Lonsing, Johannes Oetsch and Uwe Egly from the Vienna University of Technology.
       </paragraph>
       <paragraph>
        The application is used to solve arbitrary sequences of formulas incrementally. For a given sequence of formulas, an input file describes how to update a formula to obtain its successor. The application then interprets these update instructions and translates them into IPASIR calls.
       </paragraph>
       <paragraph>
        A detailed description of this approach, in particular the algorithm to generate update instructions based on a sequence of related formulas as well as the used file format, is presented in [23].
       </paragraph>
       <paragraph>
        We used 50 input files which correspond to some benchmark problems used for the last Hardware Model Checking Competition (HWMCC 2014). Competition benchmarks are originally given as And-Inverter Graphs (AIGs). By means of the bounded model checking (BMC) based tool aigbmc, which is part of the AIGER package, CNFs are generated for checking AIGs incrementally. Each CNF corresponds to one unrolling step in BMC. An input file of the benchmarking application contains update instructions for the whole sequence of CNFs of one model checking problem. Therefore this benchmark application makes it possible to compare the incremental SAT solvers that are part of the IPASIR framework on the CNFs of the BMC workflow.
       </paragraph>
      </section>
     </section>
     <section label="6.5">
      <section-title>
       Evaluation
      </section-title>
      <paragraph>
       When announcing the ILT we stated that the winners will be determined based on the number of solved problems in a given time limit (like in the other tracks). However, after selecting the actual benchmarks this did not seem completely fair. For example the partial MaxSAT benchmark has much more input files than the other benchmarks and therefore it would influence the overall results more significantly. This is not fair, since different benchmark applications should contribute equally to the evaluation.
      </paragraph>
      <paragraph>
       Our first attempt to solve this issue was to consider the relative number of solved inputs, i.e., the average percentage of solved inputs to the number of all inputs in each application. This approach is problematic if some of the applications contain inputs with high variance in the sense of solver performance. For example an application where the performance of the solvers is dissimilar has a much higher influence than an application where all the solvers solve almost the same number of problems.
      </paragraph>
      <paragraph>
       Another way of evaluation, which resolves the issues mentioned above, is the ranking based comparison. We assign a rank to each solver for each application separately (based on the number of solved instances). The solvers are then compared based on their average rank. In this case each benchmark application has the same influence on the final ranking. Nevertheless, this ranking does not consider how much better or worse a given solver is compared to the others, which might be considered unfair.
      </paragraph>
      <paragraph>
       When deciding how the first three prizes would be awarded in the ILT we considered several possible ranking methods and selected the solvers that ranked high in all of them. The final results are given in the next section. For future competitions the evaluation method should be fixed in the beginning.
      </paragraph>
      <paragraph>
       The ILT evaluation was run on computers with two quad-core Intel Xeon X5355 (2.66 GHz, 8 cores in total) processors and 24 GB of main memory. The benchmark applications were executed in parallel, i.e., eight instances of a solver-application pair were running at the same time on eight different input files.{sup:13} Two different solvers or two different applications were not allowed to run at the same time, therefore each solver-application pair could only interfere with itself (on different input files). The runtime limit for each application-solver-input triplet was 10 minutes.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Competition results
     </section-title>
     <paragraph>
      In this section we provide the results of the 2015 SAT Race. That includes the rankings and runtimes of the participating solvers in the different competition tracks and a summary of the technical novelties that have been implemented in the award winning solvers. We later analyze the results regarding trends. The detailed system descriptions provided by the authors of the participating solvers are available on the 2015 SAT Race website [20].
     </paragraph>
     <paragraph>
      In the results for the Main and Parallel Tracks we included a special solver – the virtual best solver (VBS). The VBS (by definition) achieves the best result among the participating solvers for each benchmark. This hypothetical solver can be imagined as the perfect portfolio, which is able to select the best solver (among the participating solvers) for each benchmark in the competition in zero time.
     </paragraph>
     <section label="7.1">
      <section-title>
       Main Track results
      </section-title>
      <paragraph>
       Table 2 shows the ranking of the solvers of the competition's Main Track. The ranking is based on the number of solved instances regardless of the satisfiability status. The first two prizes went to the solvers abcdSAT and MiniSAT_BCD written by Jingchao Chen from Donghua University in Shanghei (Sections 7.1.1 and 7.1.2) and the third price went to the solver RISS (Section 7.1.3) written by Norbert Manthey from the Technical University of Dresden.
      </paragraph>
      <paragraph>
       The runtime distribution of the top 12 solvers is displayed in Fig. 5 for all benchmarks and separately for SAT and UNSAT benchmarks in Fig. 6. We can observe that the solvers are very close to each other. Only the winning solvers abcdSAT and MiniSAT_BCD stand out noticeably, especially on the UNSAT instances. The VBS outperforms all the solvers very significantly for the SAT problems, while for UNSAT problems it solves only a few extra instances (however with better runtimes).
      </paragraph>
      <section label="7.1.1">
       <section-title>
        abcdSAT
       </section-title>
       <paragraph>
        The solver abcdSAT is built upon Glucose 2.3 and uses Lingeling 587f as pre-processor. Major improvements are an extended Fourier–Motzkin based variable elimination procedure that is based on cardinality constraint detection of up to {a mathematical formula}4≤-constraints. Previous approaches applied this kind of formula simplification in conjunction with detection of up to {a mathematical formula}2≤-constraints [17]. Furthermore they introduced a fast and bounded clause-based implementation of Hyper Binary Resolution [24].
       </paragraph>
       <paragraph>
        abcdSAT introduces an original approach of using the results of a preceding phase of Blocked Clause Decomposition (BCD) [25] in CDCL search. For decision levels 1 to 3 the original pickBranchLit method is overridden and a BCD-based decision policy is used instead. Using the large blocked set and the clause order that is imposed by their possible elimination [26] they use the first decision literal (at level 0) as root and try to satisfy the adjacent blocked clauses in their reverse elimination order. This localizes search in some sense regarding possibly functional variable relations [27].
       </paragraph>
      </section>
      <section label="7.1.2">
       <section-title>
        Minisat_BCD
       </section-title>
       <paragraph>
        Minisat_BCD incorporates all the advances of abcdSAT (Section 7.1.1). The difference lies in the applied learned clause database management policy. While abcdSAT uses the clause management of Glucose 2.3, Minisat_BCD applies the hybrid policy of MiniSat_HACK_999ED which has been very successful in the past and is now introduced in several shapes in other winning solvers of the 2015 competition. As a clause's LBD (Glue) value has been shown to be a good quality measure for learned clauses [28] only the clauses with an LBD value up to the threshold of 5 are kept permanently in the database. To establish a kind of short-term memory and to break ties another pool of clauses is managed by the original Minisat activity-based heuristic [29].
       </paragraph>
      </section>
      <section label="7.1.3">
       <section-title>
        RISS
       </section-title>
       <paragraph>
        RISS is built upon MiniSAT and also incorporates the improvements that have been introduced with Glucose 2.2. An important part of RISS is its pre-processor Coprocessor that can perform recent formula simplification techniques. Coprocessor is used for preprocessing as well as inprocessing [6].
       </paragraph>
       <paragraph>
        RISS now includes a form of restricted extended resolution with gate-recognition based clause minimization techniques [30], [31]. Its learned clause removal strategy is an individual combination of the Glucose 2.2 LBD-based and the Minisat 2.2 activity-based strategy.
       </paragraph>
       <paragraph>
        Coprocessor is now capable of adding resolution asymmetric tautologies (RAT)[6] that subsume other clauses. Such subsuming clauses can also be blocked clauses and covered clauses.
       </paragraph>
       <paragraph>
        RISS uses an automatic configuration routine that projects 382 formula features to 40 eigenvectors by application of Principal Component Analysis (PCA). Based on the features of the formula one of the 40 best configurations is selected using a k-nearest neighbor algorithm.
       </paragraph>
      </section>
     </section>
     <section label="7.2">
      <section-title>
       Parallel Track
      </section-title>
      <paragraph>
       The overview of the Parallel Track results is provided in Table 3. The first prize went to the solver Glucose 4 (Section 7.2.1) written by Gilles Audemard from the University of Lille-Nord and Laurent Simon from the University of Bordeaux in France. The second and third prizes went to plingeling and treengeling (Sections 7.2.2 and 7.2.3) written by Armin Biere from the Johannes Kepler University in Linz, Austria.
      </paragraph>
      <paragraph>
       The distribution of runtimes (wall-clock time) is plotted in Fig. 7. As in the Main Track the VBS is a clear winner. By looking at the number of solved instances in Table 3 we can see that this is again mostly due to the satisfiable instances. As for the other solvers we can notice that they are split into two clusters – five solvers solving over 62 instances and six solvers solving less than 38 instances. Five solvers in low-performance cluster perform particularly bad on unsatisfiable instances. This could be due to having set the restrictions on clause-sharing too strong or due to performing too little restarts [32]. In contrast to the other five solvers in the low-performance cluster the parallel versions of CryptoMinisat are highly competitive on unsatisfiable problems (even among the top three solvers) but perform really bad on the given satisfiable instances. By checking the results in the Main Track (Table 2) we can see that already the sequential version of the solver shows a similar performance gap. So CryptoMinisat seems to be specifically tuned to find proofs in contrast to finding counter-examples.
      </paragraph>
      <section label="7.2.1">
       <section-title>
        Glucose 4
       </section-title>
       <paragraph>
        The winner of the Parallel Track is the adaptive version of Glucose 4. Most winning solvers have adopted Glucose's LBD-based [28] ultra-rapid restarts and a lean clause database management. While other authors use hybrid strategies to balance the performance of their solver on unsatisfiable and satisfiable instances (see [32] for details), the authors of Glucose decided to introduce a dynamic adaptive strategy that is capable of switching heuristics online.
       </paragraph>
       <paragraph>
        In contrast to other adaptive approaches that focus on problem feature extraction Glucose 4 records its runtime parameters (while running in default configuration for a constant amount of conflicts) which then are used as indicators for a strategy switch.
       </paragraph>
       <paragraph>
        The parallel version of Glucose a.k.a. Glucose Syrup uses a lazy clause sharing approach [33] that shares only clauses that have been seen at least twice in recent conflicts and imposes common restrictions on their size and LBD-value. Glucose limits clause sharing on 32 cores even more in order to satisfy memory constraints. Only half of the cores use the adaptive strategy while the others stick to the default configuration.
       </paragraph>
      </section>
      <section label="7.2.2">
       <section-title>
        Plingeling
       </section-title>
       <paragraph>
        Plingeling[34] is based on the award winning solver Lingeling[34] that now knows 13 different optimized parameter settings for different buckets or families of problems. While in the sequential version the problem at hand is classified by a k-nearest neighbor algorithm the parallel version runs all of these experimentally determined “best” configurations.
       </paragraph>
       <paragraph>
        Plingeling traditionally shares unit clauses and equivalences. Since 2013 also clauses with low LBD values are shared. Clauses containing eliminated variables are rejected by the instances.
       </paragraph>
      </section>
      <section label="7.2.3">
       <section-title>
        Treengeling
       </section-title>
       <paragraph>
        Treengeling[34] is based on the “Cube &amp; Conquer” idea [35]. It uses look-ahead for splitting the CNF instance into multiple independent sub-problems. Those are simplified independently and split again. As soon as a sub-problem becomes simple enough to be solved more efficiently by CDCL solving, the original idea was to switch to CDCL solving. Treengeling improves on that by using “Concurrent Cube &amp; Conquer” [36], which interleaves CDCL search with look-ahead in parallel. Actually, the simplest unsolved sub-problems are all split (using look-ahead and cloning), simplified (through preprocessing) and searched (CDCL) in parallel, until all sub-problems are proved to be unsatisfiable or one satisfiable sub-problem is found. In addition few parallel instances of Lingeling are started using the call-back infrastructure existing in Lingeling to implement Plingeling. These parallel solvers interact with the “Cube &amp; Conquer” part in a Portfolio style manner, exporting unit clauses and importing the negation of unsatisfiable cubes. Otherwise there is no sharing of learned clauses among “Cube &amp; Conquer” solver instances. For the parallel portfolio solvers the integration of the local search solver YalSAT [34] is enabled, which is run in intervals. Treengeling is expected to work very well for hard combinatorial problems, where sharing of learned clauses is less useful.
       </paragraph>
      </section>
     </section>
     <section label="7.3">
      <section-title>
       Incremental Library Track
      </section-title>
      <paragraph>
       As discussed in Subsection 6.5 the evaluation criteria for the ILT are not as simple as for the other two tracks and there are several alternative ways to define them. Since the exact evaluation criteria were not announced ahead the actual selection of the winning solvers was done “manually” by the organizers with the goal to be as fair as possible.
      </paragraph>
      <paragraph>
       Firstly, we decided that different versions of a solver will be considered as one solver. Then, by looking at the rankings of the solvers for each benchmark separately (displayed in Table 4), we decided that the prizes will be distributed between the solvers CoMinisatPS, CryptoMiniSat and Glucose. The reason is that the remaining solvers never appear between the top three solvers for any of the benchmarks (the solver picosat was entering hors concours).
      </paragraph>
      <paragraph>
       Based on the total number of solved problems, percentage of problems solved and relative ranking in each benchmark category we decided to award two first prizes to the solvers CoMinisatPS and CryptoMiniSat and the third prize to the solver Glucose.
      </paragraph>
      <paragraph>
       The solver CoMinisatPS was submitted by Chanseok Oh from New York University, USA. The authors of CryptoMiniSat 4.4 are Mate Soos and Marius Lindauer. Glucose is developed by Gilles Audemard from the University of Lille-Nord and Laurent Simon from the University of Bordeaux in France. Brief descriptions of the winning solvers follow.
      </paragraph>
      <section label="7.3.1">
       <section-title>
        CoMinisatPS
       </section-title>
       <paragraph>
        CoMiniSatPS comes with a three-tiered learned clause database management that was first described by its author in [32]. The strategy keeps a core of learned clauses with extremely low LBD value (1–3) and manages clauses with slightly higher but still low LBD (4–6) in a so called mid-tier database that keeps only recently used clauses. A constant amount of clauses is managed by the classical MiniSat[29] clause activity heuristic.
       </paragraph>
       <paragraph>
        CoMiniSatPS applies a hybrid restart strategy with alternating phases of Luby-style restarts [37], [29] and Glucose-style ultra-rapid restarts [28]. In the ultra-rapid phase a lower variable decay factor is used than in the Luby-phase, thus respecting the finding that ultra-rapid restarts and lower variable decay factors both correlate positively with high performance on unsatisfiable problems [32] and vice versa.
       </paragraph>
       <paragraph>
        Specific to the incremental version of CoMiniSatPS is its incremental variable elimination procedure that has already been described in [38]. At the end of each incremental run a phase of extreme clause learning is started and a majority of the learned clauses that accumulated in the database during the solver run is cleared.
       </paragraph>
      </section>
      <section label="7.3.2">
       <section-title>
        CryptoMiniSat 4.4
       </section-title>
       <paragraph>
        CryptoMiniSat now comes with hybrid clause database management like it was introduced by the solver SWDiA5BY which is the predecessor of CoMinisatPS (Section 7.3.1), i.e. it keeps a core of clauses with low LBD value and manages a constant amount of recently learned clauses by MiniSat's activity score. Also like in SWDiA5BY a Glucose-style restart strategy is used (with LBD-based ultra-rapid restarts in conjunction with restart blocking phases).
       </paragraph>
       <paragraph>
        CryptoMiniSat is an inprocessing SAT solver [6] and the new version comes with optimized data-structures for that, specifically the watcher data structure is used to store occurrence lists and data related to recognized gates.
       </paragraph>
       <paragraph>
        In order to make CryptoMiniSat adaptive, the top 5 parameter configurations were experimentally determined and then a classifier has been trained with benchmark problems from the previous SAT Competitions to select the best configuration for the problem at hand. The resulting decision tree is compiled into the CryptoMiniSat source code.
       </paragraph>
      </section>
      <section label="7.3.3">
       <section-title>
        Glucose 4
       </section-title>
       <paragraph>
        For a description of the base version see Section 7.2.1. The incremental version introduced special handling of so called selector literals (due to assumption-based clause removal) [19]. As selector literals could not be known in advance in the competition scenario, these optimizations specific to the incremental version of Glucose were ineffective in the competition.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="8">
     <section-title>
      Analysis of results
     </section-title>
     <section label="8.1">
      <section-title>
       Essential improvements in most winning solvers
      </section-title>
      <paragraph>
       One major result of the competition is that hybrid heuristics have established themselves widely among the best performing solvers, thus providing a trade-off between heuristics that perform well on unsatisfiable problems and those that perform well on satisfiable problems [32].
      </paragraph>
      <paragraph>
       One of these hybrid approaches is lean clause database management that is based on the learned clauses LBD-values, which is combined with another clause-database of constant size that is managed by the classic activity-based cleanup procedure. Another widely adopted hybrid approach is the rapid Luby [37] style restarts in combination with the ultra-rapid restarts based on LBD-values of learned clauses.
      </paragraph>
      <paragraph>
       Most winning solvers perform a kind of automatic adaption of heuristics based on automatic feature extraction of the problem at hand or using runtime parameters.
      </paragraph>
      <paragraph>
       One novelty in this competition was introduced by the winner of the Main Track, abcdSAT (Section 7.1.1), that makes creative use of blocked clause decomposition to restrict variable selection for a constant amount of decision levels to a set of variables that satisfies clauses that are adjacent in the order imposed by blocked clause elimination. The success of this method might be due to the strong connection between blocked clauses and functional dependencies among variables [27] and it shows that structure based solving can elevate performance of SAT solvers considerably.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Similarity of solvers
      </section-title>
      <paragraph>
       We evaluated the similarity of the solvers using the notion of Spearman's rank correlation coefficient [39]. The basic idea of this comparison is that two solvers are similar if the same instances are easy (resp. hard) for both. More precisely, if we sort the list of benchmarks for solver a based on the runtimes required to solve them and do the same for solver b then the more similar these lists are the more similar are the solvers a and b.
      </paragraph>
      <paragraph>
       Spearman's rank correlation coefficient is defined as:{a mathematical formula} where n is the size of the sample (in our case the number of benchmarks) and {a mathematical formula}ra, {a mathematical formula}rb are pairs of ranks for a given benchmark and two solvers a and b. The sum is over the set of benchmarks.
      </paragraph>
      <paragraph>
       Let us consider the following simple example. We compare three solvers a, b and c on five benchmarks {a mathematical formula}b1,…,b5. The measured runtimes of each solver for each benchmark are displayed in Table 5 (columns {a mathematical formula}ta, {a mathematical formula}tb and {a mathematical formula}tc). Based on these runtimes we assign the ranks of the benchmarks for each solver (columns {a mathematical formula}ra, {a mathematical formula}rb and {a mathematical formula}rc). Next, using Equation (1), we compute for each pair of solvers the sum of the squares of rank differences for each benchmark. These values are multiplied by 6, divided by 120 ({a mathematical formula}=5(52−1)) and subtracted from 1 to obtain the resulting correlation coefficient ρ. In our example solvers b and c are the most similar to each other while c and a are the most different.
      </paragraph>
      <paragraph>
       We calculated Spearman's rank correlation coefficient (ρ) for all the solver pairs in the Main and Parallel Tracks. These results are displayed in Fig. 8 and Fig. 9 in the form of heat-maps. The figures also contain a dendrogram to illustrate the arrangement of solver clusters produced by hierarchical clustering based on ρ.
      </paragraph>
      <paragraph>
       By looking at the Main Track solvers (Fig. 8) we can observe high similarity mostly between the different versions of the same solver (lingeling, GlueMiniSat, Nigma) or solvers from the same author (the winning solvers MiniSatBCD and abcdSAT by Jingchao Chen). Actually the two versions of GlueMiniSat have {a mathematical formula}ρ=1, which means they are perfectly monotonically related. The solver most different from all the others is Ratselfax followed by or-tools. Both these solvers are more general combinatorial optimization tools with SAT solving being just one of the problems they can be used for. Overall, the solvers participating in the Main Track are very similar to each other with an average ρ of 0.786 (average over all pairs).
      </paragraph>
      <paragraph>
       One possible explanation for this high similarity of SAT solvers is that it is a negative side-effect of SAT competitions, in particular their benchmark selection method. The benchmarks of a competition are selected to be similar to previous competitions and therefore the solvers are trying to be similar to previous winning solvers. Indeed, most of the solvers are built on top of these successful solvers such as Glucose, which itself is based on MiniSat. The benchmark selection methods should be revised to address this issue.
      </paragraph>
      <paragraph>
       On the other hand, the solvers participating in the Parallel Track (Fig. 9) are much less similar with an average ρ of 0.411. High similarity is again observed between different versions of the same solvers (CryptoMiniSat, glucose, pcasso). Surprisingly the outliers of this track are the two versions of CryptoMiniSat. The correlation coefficient of both CryptoMiniSat versions is actually negative with SatUZK and Treengeling.
      </paragraph>
      <paragraph>
       The decreased similarity of the solvers in the Parallel Track might be the result of introducing a new execution environment (in the sense of relatively high parallelism, i.e., 64 cores compared to at most 16 cores used in previous competitions).
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Stability of performance
      </section-title>
      <paragraph>
       Thanks to the fact, that we performed five runs of each solver on each benchmark in the Main Track we can now analyze the difference in the performance of the solvers across these five runs.
      </paragraph>
      <paragraph>
       For each benchmark and solver we took the five runtime values and computed their standard deviation (sd) and the more robust median absolute deviation (mad), which are defined as:{a mathematical formula} where n is the number of values (in our case five) while μ is the average and M the median of the runtime values.
      </paragraph>
      <paragraph>
       Table 6 contains the average sd and mad over all the benchmarks. We can observe, that the two winning solvers (abcdSAT and MinisatBCD) have very stable performance throughout the five runs while the performance of Riss - blackbox (which finished as third) is highly variable. Actually, for the satisfiable instances abcdSAT is the most stable solver while Riss - blackbox is the least. Based on the results of abcdSAT and MinisatBCD we can draw a positive conclusion that it is possible to have SAT solvers that consistently deliver high performance.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>