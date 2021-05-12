<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    ASlib: A benchmark library for algorithm selection.
   </title>
   <abstract>
    The task of algorithm selection involves choosing an algorithm from a set of algorithms on a per-instance basis in order to exploit the varying performance of algorithms over a set of instances. The algorithm selection problem is attracting increasing attention from researchers and practitioners in AI. Years of fruitful applications in a number of domains have resulted in a large amount of data, but the community lacks a standard format or repository for this data. This situation makes it difficult to share and compare different approaches effectively, as is done in other, more established fields. It also unnecessarily hinders new researchers who want to work in this area. To address this problem, we introduce a standardized format for representing algorithm selection scenarios and a repository that contains a growing number of data sets from the literature. Our format has been designed to be able to express a wide variety of different scenarios. To demonstrate the breadth and power of our platform, we describe a study that builds and evaluates algorithm selection models through a common interface. The results display the potential of algorithm selection to achieve significant performance improvements across a broad range of problems and algorithms.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Although NP-complete problems are widely believed to be intractable in the worst case, it is often possible to solve even very large instances of such problems that arise in practice. This is fortunate, because such problems are ubiquitous in Artificial Intelligence applications. There has thus emerged a large subfield of AI devoted to the advancement and analysis of heuristic algorithms for attacking hard computational problems. Indeed, quite surprisingly, this subfield has made consistent and substantial progress over the past few decades, with the newest algorithms quickly solving benchmark problems that were beyond reach until recently. The results of the international SAT competitions provide a paradigmatic example of this phenomenon. Indeed, the importance of this competition series has gone far beyond documenting the progress achieved by the SAT community in solving difficult and application-relevant SAT instances—it has been instrumental in driving research itself, helping the community to coalesce around a shared set of benchmark instances and providing an impartial basis for determining which new ideas yield the biggest performance gains.
     </paragraph>
     <paragraph>
      The central premise of events like the SAT competitions is that the research community ought to build, identify and reward single solvers that achieve strong across-the-board performance. However, this quest appears quixotic: most hard computational problems admit multiple solution approaches, none of which dominates all alternatives across multiple problem instances. In particular, this fact has been observed to hold across a wide variety of AI applications, including propositional satisfiability (SAT) [120], constraint satisfaction (CSP) [79], planning [42], [45], and supervised machine learning [26], [104], [112]. An alternative is to accept that no single algorithm will offer the best performance on all instances, and instead aim to identify a portfolio of complementary algorithms and a strategy for choosing between them [85]. To see the appeal of this idea, consider the results of the sequential application (SAT+UNSAT) track of the 2014 SAT Competition.{sup:1} The best of the 35 submitted solvers, Lingeling ayv[9], solved {a mathematical formula}77% of the 300 instances. However, if we could somehow choose the best among these 35 solvers on a per-instance basis, we would be able to solve {a mathematical formula}92% of the instances.
     </paragraph>
     <paragraph>
      Research on this algorithm selection problem[85] has demonstrated the practical feasibility of using machine learning for this task. In fact, although practical algorithm selectors occasionally choose suboptimal algorithms, their performance can get close to that of an oracle that always makes the best choice. The area began to attract considerable attention when methods based on algorithm selection began to outperform standalone solvers in SAT competitions [118]. Algorithm selectors have since come to dominate the state of the art on many other problems, including CSP [79], planning [42], Max-SAT [71], QBF [83], and ASP [31].
     </paragraph>
     <paragraph>
      To date, much of the progress in research on algorithm selection has been demonstrated in algorithm competitions originally intended for non-portfolio-based (“standalone”) solvers. This has given rise to a variety of challenges for the field. First, benchmarks selected for such competitions tend to emphasize problem instances that are currently hard for existing standalone algorithms (to drive new research on solving strategies) rather than the wide range of both easy and hard instances that would be encountered in practice (which would be appropriately targeted by researchers developing algorithm selectors). Relatedly, benchmark sets change from year to year, making it difficult to assess the progress of algorithm selectors over time. Second, although competitions often require entrants to publish their source code, none require entries based on algorithm selectors to publish the code used to construct the algorithm selector (e.g., via training a machine learning model) or to adhere to a consistent input format. Third, overwhelming competition victories by algorithm selectors can make it more difficult for new standalone solver designs to get the attention they deserve and can thus create resentment among solver authors. Such concerns have led to a backlash against the participation of portfolio-based solvers in competitions; for example, starting in 2013 solvers that explicitly combine more than two component algorithms have been excluded from the SAT competitions. For similar reasons, there is a specific prize for non-portfolio solvers in the learning track of the International Planning Competition [107].
     </paragraph>
     <paragraph>
      The natural solution to these challenges is to evaluate algorithm selectors on their own terms rather than trying to shoehorn them into competitions intended for standalone solvers. This article, written by a large set of authors active in research on algorithm selectors, aims to advance this goal by introducing a set of specifications and tools designed to standardize and facilitate such evaluations. Specifically, we propose a benchmark library, called ASlib, tailored to the cross-domain evaluation of algorithm selection techniques. In Section 3, we provide a summary of the data format specification used in ASlib that covers a wide variety of foreseeable evaluations. To date, we have instantiated this specification with benchmarks from six different problem domains, which we describe in Section 4. However, we intend for ASlib to grow and evolve over time. Thus, our article is accompanied by an online repository (http://aslib.net), which accepts submissions from any researcher. Indeed, we already included scenarios that have been submitted by contributors outside the core group of ASlib maintainers.
     </paragraph>
     <paragraph>
      Our system automatically checks newly submitted datasets to verify that they adhere to the specifications and then provides an overview of the data, including the results of some straightforward algorithm selection approaches based on regression, clustering and classification. We provide some examples of these automatically-generated overviews and benchmark results in Sections 5 and 6. All code used to parse the format files, explore the algorithm selection scenarios and run benchmark machine learning models on them is publicly available in a new R package dubbed aslib.{sup:2} In Section 7, we discuss two recent examples of competition settings using ASlib, along with their advantages and disadvantages.
     </paragraph>
     <paragraph>
      Overall, our main objective in creating ASlib is the same as that of an algorithm competition: to allow researchers to compare their algorithms systematically and fairly, without having to replicate someone else's system or to personally collect raw data. We hope that it will help the community to obtain an unbiased understanding of the strengths and weaknesses of different methodologies and thus to improve the current state of the art in per-instance algorithm selection.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      Rice [85] was the first to formalize the idea of selecting among different algorithms on a per-instance basis. While he referred to the problem simply as algorithm selection, we prefer the more precise term per-instance algorithm selection, to avoid confusion with the (simpler) task of selecting one of several given algorithms to optimize performance on a given set or distribution of instances.
     </paragraph>
     <paragraph label="Definition 1">
      Per-instance algorithm selection problemGiven
     </paragraph>
     <list>
      <list-item label="•">
       a set {a mathematical formula}I of problem instances drawn from a distribution {a mathematical formula}D,
      </list-item>
      <list-item label="•">
       a space of algorithms {a mathematical formula}A, and
      </list-item>
      <list-item label="•">
       a performance measure {a mathematical formula}m:I×A→R,
      </list-item>
     </list>
     <paragraph>
      In practice, the mapping s is often implemented by using so-called instance features, i.e., characterizations of the instances {a mathematical formula}i∈I. These instance features are then mapped to an algorithm using machine learning techniques. However, the computation of instance features incurs additional costs, which have to be considered in the performance measure m.
     </paragraph>
     <paragraph>
      There are many ways of tackling per-instance algorithm selection and related problems. Almost all contemporary approaches use machine learning to build predictors of the behavior of given algorithms as a function of instance features. This general strategy may involve a single learned model or a complex combination of several, which, given a new problem instance to solve, is used to decide which algorithm or which combination of algorithms to choose.
     </paragraph>
     <section label="2.1">
      <section-title>
       What to select and when
      </section-title>
      <paragraph>
       It is perhaps most natural to select a single algorithm for solving a given problem instance. This approach is, e.g., used in the SATzilla [77], [118], ArgoSmArT[75], SALSA [22] and Eureka[19] systems. Its main disadvantage is that there is no way of mitigating a poor selection—the system cannot recover if the algorithm it chose for a problem instance exhibits poor performance.
      </paragraph>
      <paragraph>
       Alternatively, we can seek a schedule that determines an ordering and time budget according to which we run all or a subset of the algorithms in the portfolio; usually, this schedule is chosen in a way that reflects the expected performance of the given algorithms (see, e.g., [44], [45], [56], [79], [83]). Under some of these approaches, the computation of the schedule is treated as an optimization problem that aims to maximize, e.g., the number of problem instances solved within a timeout. For stochastic algorithms, the further question of whether and when to restart an algorithm arises, opening the possibility of schedules that contain only a single algorithm, restarted several times (see, e.g., [18], [28], [37], [99]). Instead of performing algorithm selection only once before starting to solve a problem, selection can also be carried out repeatedly while the instance is being solved, taking into account information revealed during the algorithm run. Such methods monitor the execution of the chosen algorithm(s) and take remedial action if performance deviates from what is expected [29], [67], [72], or perform selection repeatedly for subproblems of the given instance [5], [64], [65], [90].
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       How to select
      </section-title>
      <paragraph>
       The kinds of decisions the selection process is asked to produce drive the choice of machine learning models that perform the selection. If only a single algorithm should be run, we can train a classification model that makes exactly that prediction. This renders algorithm selection conceptually quite simple—only a single machine learning model needs to be trained and run to determine which algorithm to choose (see, e.g., [33], [39], [73]).
      </paragraph>
      <paragraph>
       There are alternatives to using a classification model to select a single algorithm to be run on a given instance, such as using regression models to predict the performance of each algorithm in the portfolio. This regression approach was adopted by several systems [74], [77], [87], [92], [118]. Other approaches include the use of clustering techniques to partition problem instances in feature space and make decisions for each partition separately [57], [97], hierarchical models that make a series of decisions [46], [116], cost-sensitive support vector machines [15] and cost-sensitive decision forests [119].
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Selection enablers
      </section-title>
      <paragraph>
       In order to make their decisions, algorithm selection systems need information about the problem instance to solve and the performance of the algorithms in the given portfolio. The extraction of this information—the features used by the machine learning techniques used for selection—incurs overhead not required when only a single algorithm is used for all instances regardless of instance characteristics. It is therefore desirable to extract information as cheaply as possible, thus ensuring that the performance benefits of using algorithm selection are not outweighed by this overhead.
      </paragraph>
      <paragraph>
       Some approaches use only past performance of the algorithms in the portfolio as a basis for selecting the one(s) to be run on a given problem instance [29], [92], [98]. This approach has the benefit that the required data can be collected with minimal overhead as algorithms are executed. It can work well if the performance of the algorithms is similar on broad ranges of problem instances. However, when this assumption is not satisfied (as is often the case), more informative features are needed.
      </paragraph>
      <paragraph>
       Turning to richer instance-specific features, commonly used features include the number of variables of a problem instance and properties of the variable domains (e.g., the list of possible assignments in constraint problems, the number of clauses in SAT, the number of goals in planning). Deeper analysis can involve properties of graph representations derived from the input instance (such as the constraint graph [33], [68]) or properties of encodings into different problems (such as SAT features for SAT-encoded planning problems [25]).
      </paragraph>
      <paragraph>
       In addition, features can be extracted from short runs of one or more solvers on the given problem instance. Examples of such probing features include the number of search nodes explored within a certain time, the fraction of partial solutions that are disallowed by a certain constraint or clause, the average depth reached before backtracking is required, or characteristics of local minima found quickly using local search. Probing features are usually more expensive to compute than the features that can be obtained from shallow analysis of the instance specification, but they can also be more powerful and have thus been used by many authors (see, e.g., [54], [78], [79], [82], [118]). For continuous blackbox optimization, algorithm selection can be performed based on Exploratory Landscape Analysis [15], [60], [74]. The approach defines a set of numerical features (of different complexities and computational costs) to describe the landscapes of such optimization problems. Examples range from simple features that describe the distribution of sampled objective values to more expensive probing features based on local search.
      </paragraph>
      <paragraph>
       Finally, in the area of meta-learning (learning about the performance of machine learning algorithms; for an overview, see, e.g, [17]), these features are known as meta-features. They include statistical and information-theoretical measures (e.g., variable entropy), landmarkers (measurements of the performance of fast algorithms [80]), sampling landmarkers (similar to probing features) and model-based meta-features [111]. These meta-features, and the past performance measurements of many machine learning algorithms, are available from the online machine learning platform OpenML [113]. In contrast to ASlib, however, OpenML is not designed to allow cross-domain evaluation of algorithm selection techniques.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Algorithm selection and algorithm configuration
      </section-title>
      <paragraph>
       A problem closely related to algorithm selection is the algorithm configuration problem: given a parameterized algorithm A, a set of problem instances I and a performance measure m, find a parameter setting of A that optimizes m on I (see [52] for a formal definition). While algorithm selection operates on finite (usually small) sets of algorithms, algorithm configuration operates on the combinatorial space of an algorithm's parameter settings. General algorithm configuration methods, such as ParamILS [52], GGA [4], I/F-Race [11], and SMAC [50], have yielded substantial performance improvements (sometimes orders of magnitude speedups) of state-of-the-art algorithms for several benchmarks, including SAT-based formal verification [47], mixed integer programming [49], AI planning [88], [109], the combined selection and hyperparameter optimization of machine learning algorithms [104], and joint architecture and hyperparameter search in deep learning [23]. Algorithm configuration and selection are complementary since configuration can identify algorithms with peak performance for homogeneous benchmarks and selection can then choose from among these specialized algorithms. Consequently, several possibilities exist for combining algorithm configuration and selection [3], [27], [48], [57], [71], [89], [117], [119]. The algorithm configuration counterpart of ASlib is AClib [53] (http://aclib.net). In contrast to ASlib, it is infeasible in AClib to store performance data for all possible parameter configurations, which often number more than 10{sup:50}. Therefore, an experiment on AClib includes new (expensive) runs of the target algorithms with different configurations and hence, experiments on AClib are a lot more costly than experiments on ASlib, where no new algorithm runs are necessary.{sup:3} Furthermore, in contrast to AClib, ASlib does not include the actual instances and binaries of the algorithms. Therefore, ASlib does not provide a way to generate new performance data, as is required in AClib as a consequence of the need to assess the performance of new target algorithm configurations arising within the configuration process. However, ASlib and AClib can be combined by generating actual performance data based on the resources in AClib and then creating an ASlib scenario which selects between different solver configurations on a per-instance basis.
      </paragraph>
      <paragraph>
       A full coverage of the wide literature on algorithm selection is beyond the scope of this article, but we refer the interested reader to recent survey articles on the topic [63], [91], [93], [108].
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Summary of format specification
     </section-title>
     <paragraph>
      We propose a data format specification for algorithm selection scenarios, i.e., instances of the per-instance algorithm selection problem. This format and the resulting data repository allow a fair and convenient scientific evaluation and comparison of algorithm selectors.
     </paragraph>
     <paragraph>
      The format specification assumes a generic approach to algorithm selection, depicted in Fig. 1. The general approach is as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       A vector of instance features {a mathematical formula}f(i)∈F of i is computed. Feature computation may occur in several stages, each of which produces a group of (one or more) features. Furthermore, later stages may depend on the results of earlier ones. Each feature group incurs a cost, e.g., runtime. If no features are required, the cost is 0 (this occurs, e.g., for variants of algorithm selection that compute static schedules).
      </list-item>
      <list-item label="2.">
       A machine learning technique s selects an algorithm {a mathematical formula}a∈A based on the feature vector from Step 1.
      </list-item>
      <list-item label="3.">
       The selected algorithm a is applied to i.
      </list-item>
      <list-item label="4.">
       Performance measure m is evaluated, taking into account feature computation costs and the performance of the selected algorithm.
      </list-item>
      <list-item label="5.">
       Some algorithm selectors do not select a single algorithm, but compute a schedule of several algorithms: they apply a to i for a resource budget {a mathematical formula}r∈R (e.g., CPU time), evaluate the performance metric, evaluate a stopping criterion, and repeat as necessary, taking observations made during the run of a into account.{sup:4}
      </list-item>
     </list>
     <paragraph>
      The purpose of our library is to provide all information necessary for performing algorithm selection experiments using the given scenario data. The user does not need to actually run algorithms on instances, as all performance data is already precomputed. This drastically reduces the time required for executing studies, i.e., the runtime of studies is now dominated by the time required for learning s and not by applying algorithms to instances (e.g., solving SAT problems). It also means that results are perfectly reproducible; for example, the runtimes of algorithms do not depend on the hardware used; rather, they can be simply looked up in the performance data for a scenario.
     </paragraph>
     <paragraph>
      Table 1 shows the basic structure of a scenario definition in ASlib; the complete specification with all details can be found in an accompanying technical report [12] and on our online platform.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Algorithm selection scenarios provided in ASlib release 2.0
     </section-title>
     <paragraph>
      The set of algorithm selection scenarios in release version 2.0 of our library, shown in Table 2, has been assembled to represent a diverse set of selection problem settings that covers a wide range of problem domains, types of algorithms, features and problem instances. Our scenarios include both problems that have been broadly studied in the context of algorithm selection techniques (such as SAT and CSP), as well as more recent ones (such as the container pre-marshalling problem). Most of our scenarios were taken from publications that report performance improvements through algorithm selection and consist of algorithms where the virtual best solver (VBS){sup:5} is significantly better than the single best solver.{sup:6} Therefore, these are problems on which it makes sense to seek performance improvements via algorithm selection. All scenarios are available on our online platform (http://www.aslib.net/).
     </paragraph>
     <paragraph>
      We now briefly describe the scenarios we included and what makes them interesting.
     </paragraph>
     <section label="4.1">
      <section-title>
       SAT: propositional satisfiability
      </section-title>
      <paragraph>
       The propositional satisfiability problem (SAT) is a classic NP-complete problem that consists of determining the existence of an assignment of values to variables of a Boolean formula such that the formula is true. It is widely studied, with many applications including formal verification [81], scheduling [20], planning [59] and graph coloring [110]. Our SAT data mainly stems from different iterations of the SAT competition,{sup:7} which is split into three tracks: industrial (INDU), crafted (HAND), and random (RAND).
      </paragraph>
      <paragraph>
       The SAT scenarios are characterized by a high level of maturity and diversity in terms of their solvers, features and instances. Each SAT scenario involves a highly diverse set of solvers, many of which have been developed for several years. In addition, the set of SAT features is probably the best-studied feature set among our scenarios; it includes both static and probing features that are organized into as many as ten different feature groups. The instance sets used in our various SAT scenarios range from randomly-generated ones to real-world instances submitted by industry.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       QBF: quantified Boolean formula
      </section-title>
      <paragraph>
       A quantified Boolean formula (QBF) is a formula in propositional logic with universal or existential quantifiers on each variable in the formula. A QBF solver finds a set of variable assignments that makes the formula true or proves that no such set can exist. This is a PSPACE-complete problem for which solvers exhibit a wide range of performance characteristics. Our QBF-2011 data set comes from the QBF Solver Evaluation 2010{sup:8} and consists of instances from the main, small hard, 2QBF and random tracks. Our QBF-2014 data set comes from the application track of the QBF Gallery 2014.{sup:9} The instance features were computed using the AQME system and are described in more detail by Pulina et al. [83]. The solvers for QBF-2011 come from the AQME system as well, whereas the solvers for QBF-2014 are the ones submitted to the application track of the QBF Gallery.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       MAXSAT: maximum satisfiability
      </section-title>
      <paragraph>
       MaxSAT is the optimization version of the previously introduced SAT problem, and aims to find a variable assignment that maximizes the number of satisfied clauses. The MaxSAT problem representation can be used to effectively encode a number of real-world problems, such as FPGA routing [115], and software package installation [6], among others, as it permits reasoning about both optimality and feasibility. The particular scenarios focus on the partial MaxSAT (PMS) problem [10].
      </paragraph>
      <paragraph>
       The MAXSAT12-PMS scenario is composed of a collection of random, crafted and industrial instances from the 2012 MaxSAT Evaluation [7]. The techniques used to solve the various instances in this scenario are very complementary to each other, leading to a substantial performance gap between the single best and the virtual best solver. Furthermore, because there are only six solvers with very different performance characteristics, algorithm selection approaches must be very accurate in their choices, as any mistake is heavily penalized.
      </paragraph>
      <paragraph>
       The more recent MAXSAT15-PMS-INDU was built on the performance data of the industrial track on partial MAXSAT problems from the 2015 MAXSAT Evaluation.{sup:10} With 29 algorithms, it provides a larger set of solvers than MAXSAT12-PMS. However, there are different parameterizations of the same solvers, e.g., four different variants of ahms, such that there are some subsets of strongly correlated solvers. The performance gap between the single best and virtual best solver is larger in MAXSAT12-PMS than in MAXSAT15-PMS-INDU.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       CSP: constraint solving
      </section-title>
      <paragraph>
       The Constraint Satisfaction Problem (CSP; [100]) is concerned with finding solutions to constraint satisfaction problems—a task that is NP-complete. Learning in the context of constraint solving is a technique by which previously unknown constraints that are implied by the problem specification are uncovered during search and subsequently used to speed up the solving process.
      </paragraph>
      <paragraph>
       The scenario CSP-2010 contains only two solvers: one that employs lazy learning [33], [35] and one that does not [34]. The data set is heavily biased towards the non-learning solver, such that the baseline (the single best solver) is very good already. Improving on this is a challenging task and harder than in many of the other scenarios. Furthermore, both solvers share a common core, which results in a scenario that directly evaluates the efficacy of a specific technique in different contexts.
      </paragraph>
      <paragraph>
       The more recent scenario CSP-MZN-2013 provides a larger set of instances, algorithms and instance features. Instances and algorithms come from the MiniZinc challenge 2012 and the International Constraint Solver Competitions (ICSC) in 2009. Specifically, the instances come from the MiniZinc 1.6 benchmark suite and the algorithms in the scenario participated in the MiniZinc Challenge 2012. Algorithms, instances and instance features are described in more detail in [1], [2].
      </paragraph>
      <paragraph>
       Our final CSP scenario PROTEUS comes from [46] and includes an extremely diverse mix of well-known CSP solvers alongside competition-winning SAT solvers that have to solve (converted) XCSP instances.{sup:11} The SAT solvers can accept different conversions of the CSP problem into SAT (see, e.g., [66], [101], [102]), which in our format are provided as separate algorithms. This scenario is the only one in which solvers are tested with varying “views” of the same problem. The features of this scenario are also unique in that they include both the SAT and CSP features for a given instance. This potentially provides additional information to the selection approach that would normally not be available for solving CSPs. An algorithm selection system has a very high degree of flexibility here and may choose to perform only part of the possible conversions, thereby reducing the set of solvers and features, but also reducing the overhead of performing the conversions and feature computations. There are also synergies between feature computation and algorithm runs that can be exploited, e.g., if the same conversion is used for feature computation and to run the chosen algorithm then the cost of performing the conversion is only incurred once. In other cases, where features are computed on one representation and another one is solved, conversion costs are incurred both during feature computation and the running of the algorithm.
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       ASP: answer set programming
      </section-title>
      <paragraph>
       Answer Set Programming (ASP, [8], [30]) is a form of declarative programming with roots in knowledge representation, non-monotonic reasoning and constraint solving. In contrast to many other constraint solving domains (e.g., the satisfiability problem), ASP provides a rich yet simple declarative modeling language in which problems up to {a mathematical formula}Δ3p (disjunctive optimization problems) can be expressed. ASP has proven to be efficiently applicable to many real-world applications, e.g., product configuration [95], decision support for NASA shuttle controllers [76], synthesis of multiprocessor systems [55] and industrial team building [38].
      </paragraph>
      <paragraph>
       In contrast to the other scenarios, the algorithms in the scenario ASP-POTASSCO were automatically constructed by an adapted version of Hydra[117], i.e., the set of algorithms consists of complementary configurations of the solver clasp[32]. The instance features were generated by a light-weight version of clasp, including static and probing features organized into feature groups; they were previously used in the algorithm selector claspfolio[31], [43].
      </paragraph>
     </section>
     <section label="4.6">
      <section-title>
       PREMAR-ASTAR-2015: container pre-marshalling
      </section-title>
      <paragraph>
       The container pre-marshalling problem (CPMP) is an NP-hard container stacking problem from the container terminals literature [96]. We constructed an algorithm selection scenario from two recent A* and IDA* approaches for solving the CPMP presented in [106], using instances from the literature. The scenario is described in detail in [105].
      </paragraph>
      <paragraph>
       The pre-marshalling scenario differs from other scenarios in that the set of algorithms is highly homogeneous. All of the algorithms are parameterizations of a single symmetry breaking heuristic, either using the A* or IDA* search techniques, which stands in sharp contrast to the diversity of solvers present in most other scenarios. The scenario represents a real-world, time-sensitive problem from the operations research literature, where algorithm selection techniques can have a large impact.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Automated exploratory data analysis
     </section-title>
     <paragraph>
      The online platform for our benchmark repository offers not only the scenario data files themselves. It also provides many tables and figures that summarize them. These pages are automatically generated and currently consist (among others) of the following parts:
     </paragraph>
     <list>
      <list-item label="•">
       an overview table that lists, for example, the number of instances, algorithms and features for all available scenarios, similar to Table 2;
      </list-item>
      <list-item label="•">
       a summary of the algorithms' performance and run status data;
      </list-item>
      <list-item label="•">
       a summary of the feature values, as well as the run status and costs of the feature groups;
      </list-item>
      <list-item label="•">
       benchmark results for standard machine learning models for each scenario; see Section 6.
      </list-item>
     </list>
     <paragraph>
      Presenting this additional data offers the following advantages:
     </paragraph>
     <list>
      <list-item label="•">
       Researchers can quickly understand which scenarios are available and select those best suited to their needs.
      </list-item>
      <list-item label="•">
       Data can quickly be sanity-checked. It is common that data collection errors occur when scenario data is gathered and submitted for the first time.
      </list-item>
      <list-item label="•">
       Interesting or challenging properties of the data sets become visible, providing the researcher with a quick and informative first impression.
      </list-item>
     </list>
     <paragraph>
      The platform's summary page for the algorithms starts with a table listing summary statistics regarding their performance (e.g., mean values and standard variations) and run status (e.g., how many runs were successful). We also indicate whether one algorithm is dominated by another, i.e., an algorithm {a mathematical formula}a1 dominates another algorithm {a mathematical formula}a2 if and only if {a mathematical formula}a1 has performance at least equal to that of {a mathematical formula}a2 on all instances, and {a mathematical formula}a1 outperforms {a mathematical formula}a2 on at least one instance. This is useful, because there is no reason to include a dominated algorithm in a portfolio. Various visualizations, such as box plots, scatter plot matrices, correlation plots and density plots enable further inspection of the performance distribution and correlation between algorithms, allowing the reader to better understand the strengths and weaknesses of each algorithm. All of our plots can be configured to use log scales, which often improves visual understanding of heavy-tailed distributions (e.g., runtime distributions of hard combinatorial solvers [36]).
     </paragraph>
     <paragraph>
      Fig. 2 shows boxplots and cumulative distribution functions for the algorithms in the QBF-2011 scenario as an example. The boxplots summarize the runtimes of an algorithm by drawing a box between the 25%- and 75%-quantile of the sample, i.e., the smallest values that are greater or equal to 25% and 75% of the runtimes. In addition, each box contains a line showing the median runtime, as well as so-called whiskers, i.e., lines that connect the box with runtimes that are within 150% of the interquartile range (the length of the box) below the 25%- or above the 75%-quantile, respectively. Observations with even more extreme runtimes are considered to be outliers and are depicted by a single point per outlier. The cumulative distribution function plots on the other hand show runtimes on all instances for the algorithm. Each point within the plot consists of the observed runtime on the x-axis and the corresponding cumulative density, i.e., the percentage of instances that were solved at this or a smaller runtime, on the y-axis.
     </paragraph>
     <paragraph>
      Such plots show the location of the mean, distribution spread, density multimodality and other properties of the distribution. In addition, they reveal how long it took an algorithm to solve the given instances. For example, for the QBF-2011 scenario in Fig. 2, one can see that the algorithm quantor finds a solution very quickly on a few instances, i.e., it solves approximately {a mathematical formula}5% of the instances in less than a second. However, if it does not succeed quickly, it often does not succeed at all—it solved less than {a mathematical formula}30% of all the instances. In contrast, sSolve usually needs longer to find a solution, but by the time it does, it is one of the best algorithms. Such behavior can indicate that the algorithm requires a ‘warm-up’ stage, which should be considered when deploying it.
     </paragraph>
     <paragraph>
      The left panel of Fig. 3 shows pairwise scatterplots of the QBF-2011 scenario, allowing an easy comparison of algorithm pairs on all instances from a given scenario. Each point represents a problem instance within the scenario, and from the location of the point cloud one can see whether an algorithm is dominant over the majority of instances, or whether relative performance strongly varies across instances. The first case can be identified by a cloud that is located either in the upper-left or lower-right corner of a single scatterplot. In such a case, the dominated algorithm could be discarded from the portfolio. However, if this type of dominance relationship is not present, there is the potential to realize performance improvements by means of per-instance algorithm selection.
     </paragraph>
     <paragraph>
      Because detecting correlation in algorithm performance is also of interest when analyzing the strengths and weaknesses of a given portfolio-based solver [120], we also present a correlation matrix, cf. Fig. 3 (right panel). Algorithms that have a (high) positive correlation are more likely to be redundant in a portfolio, whereas pairs with a (high) negative correlation are more likely to complement each other. We calculate Spearman's correlation coefficient between ranks. Blue boxes represent positive correlation, red boxes represent negative correlation, and shading indicates the strength of correlation. The algorithms are also clustered according to these values (using Ward's method [114]) and then sorted, such that similar algorithms appear together in blocks. This type of clustering allows the identification of algorithms with highly correlated performance.
     </paragraph>
     <paragraph>
      Fig. 4 shows the correlation between algorithms for the SAT12-ALL scenario. The plot reveals four groups of algorithms (minisatpsm to restartsat, sattimep to tnm, marchrw and the three mphaseSAT-algorithms) with high correlations within each group. It may be desirable to include just a single representative from each group, reducing the size of the entire portfolio from 31 to four algorithms.
     </paragraph>
     <paragraph>
      As we do with algorithm runs, we characterize the features by giving summary statistics of the feature values, the run status and the cost of the feature groups. Table 3 shows the summary of the feature groups for the SAT12-RAND scenario. In this scenario, all 115 features have the feature group “Pre” as a requirement. While this preprocessing group succeeded in all cases, one other group did not: the feature group “CG” (which computes clause graph features) failed in 37.37% of cases due to exceeding time or memory limits, and even for instances where it succeeded, it was quite expensive (8.79 seconds on average). Such information is useful to understand the behavior of the features: how risky is it to compute a feature group, and how much time must one invest in order to obtain the corresponding features?
     </paragraph>
     <paragraph>
      We also check whether instances occur with exactly the same feature values, indicating that the experimenter might have erroneously run on the same instance twice.
     </paragraph>
     <paragraph>
      All of the above tables and figures and many more were generated by our online platform, and are also accessible through the R package aslib. The functions are highly configurable and customizable. We plan to extend our data analysis with additional techniques, such as more measures of algorithm performance [94].
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Study of algorithm selection techniques
     </section-title>
     <paragraph>
      In this section, we present an exploratory benchmark study that gives an indication of the diversity of our benchmarks. First, we evaluate the performance of algorithm selectors on our scenarios. We then perform a subset selection study to identify the important algorithms and instance features in each of the scenarios. We make no claim that the presented experimental settings are exhaustive or that we achieve state-of-the-art algorithm selection performance; rather, we provide results that can be used as a baseline comparison for other approaches. These results, and our framework in general, allow us to study which algorithm selection approaches work well for which of our scenarios.
     </paragraph>
     <paragraph>
      We use the LLAMA toolkit [62], version 0.9.1, in combination with the aslib package{sup:12} to run the algorithm selection study. LLAMA is an R [84] package that facilitates many common algorithm selection approaches. In particular, it enables access to classification, regression, and clustering models for algorithm selection—the three main approaches we use in our study. We use the mlr R package [14] as an interface to the machine learning models provided by other R packages. We parallelize all of our benchmark experiments through the BatchExperiments[13] R package.
     </paragraph>
     <paragraph>
      In this paper, we only present aggregated benchmark results, but the interested reader can access full benchmark results at http://aslib.net. Our study is fully reproducible as the complete code to generate these results is part of the aslib package.
     </paragraph>
     <paragraph>
      We use the subset of feature groups that are recommended by the authors of the respective scenario, called default feature set. For the feature subset selection study, we have used all feature groups. Detailed and continuously updated information (e.g., the names of the feature processing groups we selected and their average costs) is provided on the ASlib website.
     </paragraph>
     <section label="6.1">
      <section-title>
       Experimental setup
      </section-title>
      <paragraph>
       We consider three approaches to algorithm selection that have been studied extensively in the literature (cf. Section 2.2):
      </paragraph>
      <list>
       <list-item label="•">
        classification applies a multi-class classifier to directly predict the best performing algorithm of the k possible algorithms;
       </list-item>
       <list-item label="•">
        regression predicts each algorithm's performance via a regression model and then chooses the one with the best predicted performance;
       </list-item>
       <list-item label="•">
        clustering groups problem instances in feature space, then determines the cost-optimal solver for each cluster and finally assigns to each new instance the solver associated with the instance's predicted cluster.
       </list-item>
      </list>
      <paragraph>
       The specific machine learning algorithms we employed for our study are shown in Table 4. They include representatives of each of the three major approaches above.
      </paragraph>
      <paragraph>
       The linear model we employ is the best-studied regression method. In its most basic version, it models the data using the linear function {a mathematical formula}f(x)=βTx+β0; parameters are obtained by minimizing squared loss. The trees constructed by the CART algorithm, which can handle both classification and regression problem, are grown in a top-down manner and divide the training data into rectangular regions by axis-parallel splits at each interior node. Splits are selected by considering label impurity reduction measured by an impurity function, based, e.g., on the Gini index for classification or squared loss for regression. Leaf nodes associate the best, but constant, label with their feature region for prediction. Random forests form an ensemble of ntree simpler trees by bootstrapping multiple data sets from the original one and then fitting a tree for each. Predictions are made through majority voting for classification and averaging for regression. Furthermore, ensemble members are decorrelated by randomly selecting only a few candidate features for each split point (controlled by parameter mtry) in a tree and maximally growing trees without any early stopping or pruning. Support Vector Machines perform linear classification in a transformed feature space by maximizing the margin between the positive and negative examples. Parameter C controls the trade-off between the size of the margin and classification loss. The feature mapping is implicitly built into the algorithm by substituting the regular inner product of the Euclidean space with a so-called kernel. Parameter γ is a property of the radial basis function kernel used here. The XMeans clustering algorithm is the only unsupervised learning algorithm we study. It is an extension of the well known k-means method to adaptively select the number of clusters. k-means starts with k random cluster centroids, assigns each point to the nearest centroid, and then iteratively recomputes the cluster centroids and cluster assignments until convergence. For further details on all methods the reader is referred to the standard literature [41] and for XMeans to [21].
      </paragraph>
      <paragraph>
       We tuned the hyperparameters of ksvm and randomForest (classification and regression) within the listed parameter ranges, using random search with 250 iterations and a nested cross validation (with three internal folds) to ensure unbiased performance results. All other parameters were left at their default values. For the clustering algorithm, we set the (maximum) number of clusters to 30 after some preliminary experiments; the exact number of clusters is determined internally by XMeans.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Data preprocessing
      </section-title>
      <paragraph>
       We removed constant-valued (and therefore irrelevant) features and imputed missing feature values as the mean over all non-missing values of the feature.{sup:13} For the clustering methods, we normalized the range of each feature to the interval {a mathematical formula}[−1,1]. The scenarios we consider in this article contain only continuous features. The other machine learning methods that require normalized data perform this internally (for example the SVMs). Missing performance values were imputed using the timeout value of the scenario.
      </paragraph>
      <paragraph>
       For each problem instance, we calculated the total feature computation cost as the sum of the costs of all feature groups, in the order specified in the definition of the scenario. If the problem instance was solved during feature computation (e.g., using SLS-probing features [118]), we only considered the cost of the feature groups up to the one that solved it. Furthermore, we set the runtime for all algorithms to zero for instances solved during feature computation. If the instance was not solved during feature computation, we added the feature costs computed in this way to the runtimes of the individual algorithms on the respective instances ({a mathematical formula}c(fi)+t(i,a)). Given these new runtimes, we checked whether the specified timeout was now exceeded and set the run status of any corresponding algorithm accordingly. Preprocessing runtimes to include feature computation time in this way allows us to focus on an algorithm selection system's overall performance, and avoids overstating the fraction of instances that would be solved within a time budget in cases where features are expensive to compute.
      </paragraph>
      <paragraph>
       Each scenario specifies a partition into 10 folds for cross-validation to ensure consistent evaluation across different methods. We used this partition in our study.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Evaluation
      </section-title>
      <paragraph>
       We evaluated different algorithm selection models using three different measures:
      </paragraph>
      <list>
       <list-item label="•">
        the fraction of all instances solved within the timeout;
       </list-item>
       <list-item label="•">
        the penalized average runtime with a penalty factor of 10, i.e., a timeout counts as 10 times the timeout;
       </list-item>
       <list-item label="•">
        the average misclassification penalty, which, for a given instance, is the difference between the performance of the selected algorithm and the performance of the best algorithm.
       </list-item>
      </list>
      <paragraph>
       The performance of each algorithm selection model was compared to the virtual best solver (VBS) and the single best solver. The virtual best solver selects the best solver from {a mathematical formula}A for each instance ({a mathematical formula}∀i∈I:argmaxa∈Am(i,a)). Note that the misclassification penalty for VBS is zero by definition. The single best solver is the actual solver that has the overall best performance on the data set ({a mathematical formula}argmaxa∈A∑i∈Im(i,a)). Specifically, we consider the solver with the best PAR10 score over all problem instances in a scenario.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Results
      </section-title>
      <paragraph>
       Fig. 5 presents a summary of the results of our study. In most cases, the algorithm selection approaches performed better than the single best solver. We expected this, as most of our data sets come from publications that advocate algorithm selection systems.
      </paragraph>
      <paragraph>
       Nevertheless, there were significant differences between the scenarios. While almost all algorithm selection approaches outperformed the single best algorithm, there are some scenarios that seem to be much harder for algorithm selection. In particular, on the SAT12-INDU scenario, three approaches were not able to achieve a performance improvement.
      </paragraph>
      <paragraph>
       Random regression forests stood out quite clearly as the best overall approach, achieving the best performance on 13 of the 17 datasets. This is in line with recent results showing the strong performance of this model for algorithm runtime prediction [54]. The results are also consistent with those of the original papers introducing the datasets.
      </paragraph>
      <paragraph>
       XMeans performed worst on average. On some scenarios, it performed well, in particular SAT11-RAND, MAXSAT12-PMS, and PROTEUS-2014. However, on SAT12-ALL, SAT12-INDU, and SAT15-INDU XMeans performed worse than the single best solver. The default subset of instance features appears to be unfavorable for XMeans on industrial SAT instances.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Algorithm and feature subset selection
      </section-title>
      <paragraph>
       To provide further insight into our algorithm selection scenarios, we applied forward selection [61] to the algorithms and features to determine whether smaller subsets still achieve comparable performance. We performed forward search independently for algorithms and features for each scenario. Forward selection is an iterative selection algorithm whose the first iteration starts with an empty set of algorithms and features; in each subsequent iteration, it greedily adds the algorithm or feature to the set which most improves the cross-validated score (PAR10) of the predictor. The selection process terminates when the score does not improve by at least ε. We set {a mathematical formula}ε=1, which roughly corresponds to an improvement of 1 second per instance. In all other aspects, the experimental setup was the same as described before.
      </paragraph>
      <paragraph>
       We used random regression forests,{sup:14} as it was the best overall approach so far. We note that the selection results use standard cross validation rather than the nested version, which may result in overconfident performance estimates for the selected subsets [16]. We accept this caveat since our goal here is to study the ranking of the features and the size of the selected sets, and a more complex, nested approach would have resulted in multiple selected sets.
      </paragraph>
      <paragraph>
       Table 5, Table 6 present the results of forward selection for algorithms and features on all scenarios. Usually, the number of selected features is very small compared to the complete feature set. This is consistent with the observations of Roberts and Howe [86] and Hutter et al. [51] who found in their experiments that only a few instance features are necessary to reliably predict the runtime of their algorithms. For example, on SAT12-RAND, the only three features selected were a balance feature concerning the ratio of positive and negative occurrences of each variable in each clause and two features based on survey propagation.
      </paragraph>
      <paragraph>
       The number of algorithms after forward selection is also substantially reduced on most scenarios. On the SAT scenarios, we expected to see this because the scenarios consider a huge set of SAT solvers that were not pre-selected in any way. Xu et al. [120] showed that many SAT solvers are strongly correlated and make only very small contributions to the VBS, a finding that is corroborated by our results (see Fig. 4 in Section 5). For example, on the SAT12-RAND scenario, only two solvers were selected: sparrow and eagleup. We did not expect the set of algorithms to be reduced on the ASP-POTASSCO scenario, as the portfolio was automatically constructed using algorithm configuration to obtain a set of complementary parameter settings that are particularly amenable to portfolios; nevertheless only 5 of 11 configurations were chosen by the forward selection.
      </paragraph>
      <paragraph>
       Our results indicate that in real-world settings, selecting the most predictive features and the solvers that make the highest contributions can be important. More detailed and continuously updated results can be found on the ASlib website.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Competitions on ASlib
     </section-title>
     <paragraph>
      As described before and illustrated in Section 6, we designed ASlib to enable easy and fair comparison of different algorithm selection approaches. The next step to get unbiased performance comparisons of algorithm selectors is to organize competitions based on ASlib. In this section, we will briefly describe two exemplary competition settings based on ASlib.
     </paragraph>
     <paragraph>
      On-going evaluation on ASlib. In the on-going evaluation on ASlib,{sup:15} every participant can simply submit his/her performance for each scenario (using the provided cross validation splits) and the source code of their algorithm selector. The latter will only be used to verify the results in case of doubt. The results (i.e., (penalized) average performance on each scenario) will be added in an overview table and the system will be linked.
     </paragraph>
     <paragraph>
      In this setting, every system that can read the ASlib format can easily participate and no deadlines for submission are required. Therefore, the newest systems and results can always be added on-the-fly such that the on-going evaluation always reflects the most recent known state-of-the-art systems and their performances. Disadvantages of this setting are:
     </paragraph>
     <list>
      <list-item label="1.">
       the different participants use different amounts of computational resources to compute the results—for example, two well-performing systems in the on-going evaluation are SATzilla[118] and AutoFolio[70] but it is also well-known that these two systems use a lot more computation resources (several CPU days) than other systems;
      </list-item>
      <list-item label="2.">
       since the test and training data are published, the system will tend to overfit the scenarios if we will not regularly provide new scenarios to reveal such overfitting.
      </list-item>
     </list>
     <paragraph>
      ICON challenge on algorithm selection. The ICON Challenge on Algorithm Selection{sup:16} provided a comparative evaluation of state-of-the-art algorithm selection systems. The winner of the challenge was the zilla system [121]. In this competition, the algorithm selectors needed to be submitted before a fixed deadline and each system was executed on the organizers' hardware with some limitations (e.g., at most 12 CPU hours for training on one scenario). Although the used scenarios were also already published before (i.e., ASlib version 1.0.1), the organizers did not reveal the training-test splits to avoid overly strong overfitting on these scenarios. Furthermore, the ICON challenge assessed the performance of the algorithm selectors based on 3 different performance metrics (i.e., average number of solved instances, PAR10, and misclassification penalty (MCP)) which revealed some strengths and weaknesses of algorithm selectors, e.g., systems that used an algorithm schedule had better performance on solved instances and PAR10, but wasted some time with respect to MCP.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>