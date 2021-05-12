<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    The QBF Gallery: Behind the scenes.
   </title>
   <abstract>
    Over the last few years, much progress has been made in the theory and practice of solving quantified Boolean formulas (QBF). Novel solvers have been presented that either successfully enhance established techniques or implement novel solving paradigms. Powerful preprocessors have been realized that tune the encoding of a formula to make it easier to solve. Frameworks for certification and solution extraction emerged that allow for a detailed interpretation of a QBF solver's results, and new types of QBF encodings were presented for various application problems. To capture these developments the QBF Gallery was established in 2013. The QBF Gallery aims at providing a forum to assess QBF tools and to collect new, expressive benchmarks that allow for documenting the status quo and that indicate promising research directions. These benchmarks became the basis for the experiments conducted in the context of the QBF Gallery 2013 and follow-up evaluations. In this paper, we report on the setup of the QBF Gallery. To this end, we conducted numerous experiments which allowed us not only to assess the quality of the tools, but also the quality of the benchmarks.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Quantified Boolean formulas (QBF) [28] provide a powerful framework for encoding any application problem located in the complexity class of PSPACE. Many important verification problems like bounded model checking [27] or artificial intelligence tasks like conformant planning [12] can be efficiently encoded as QBF (cf. [3] for a survey). The use of existential and universal quantifiers in QBF potentially allows for encodings which are exponentially more succinct than encodings in propositional logic (SAT). Given the success story of SAT solving [6], much emphasis and efforts have been spent in repeating this success story for QBF, with the aim to avoid the space explosion inherent in SAT encodings. So far, QBF based-technologies have not yet reached the mature state of modern SAT-based technology, but nevertheless continuous progress can be observed.
     </paragraph>
     <paragraph>
      Recently, several novel approaches emerged ranging from innovative solving techniques to effective preprocessing and new encodings of application problems. A major breakthrough has been achieved by solving the long open problem of calculating certificates for a solver's result, leading to elegant approaches based on the analysis of resolution proofs [1], [19], to name one example. Such advancements are often distributed over multiple publications and implemented in different tools with evaluations performed within different infrastructures, which makes them hard to compare. Due to this heterogeneity, QBF certainly has some entrance barrier for potential contributors and users. Therefore, we decided to set up the QBF Gallery as an annual or biannual event, which is open to all advancements in the field of QBF research.
     </paragraph>
     <paragraph>
      The first edition of the QBF Gallery was organized in 2013. We invited the QBF research community to contribute ideas on what kind of evaluations would be interesting, given a common infrastructure to perform experiments. The QBF Gallery 2013 [43] was a non-competitive, community-driven event affiliated with the First International Workshop on Quantified Boolean Formulas (QBF 2013).{sup:1} The overall goal was to evaluate the state-of-the-art of QBF-related technologies. This strongly distinguishes the QBF Gallery 2013 event from previous competitions [40], [44], where the main focus was set on the competitive comparison of solvers with the goal to crown winners. In the QBF Gallery 2013, we abstained from this competitive spirit. We were interested in performing comprehensive experiments that allow us to better understand the benefits and drawbacks of different techniques. We did not organize a competition in a traditional sense, so we awarded no prizes. Instead, we collected and analyzed data obtained during numerous experimental runs. The participants were immediately provided with all the results and their feedback was considered for follow-up experiments. Furthermore, in the case of discrepancies in the solving results, we immediately informed the respective participants who could then submit a fix and continue to participate without any consequences. Events like the QBF Gallery are important to give an overview on the state of the art and to provide a common forum for watching the progress in a research community. For potential users, the QBF Gallery should provide an easy entrance into QBF technology by collecting current research results manifesting in tools.
     </paragraph>
     <paragraph>
      We set up four different showcases for the QBF Gallery 2013. The four showcases are (1) solving, (2) preprocessing, (3) applications, and (4) certification. The solving showcase evaluates and compares different solvers in various scenarios in order to understand the solvers' suitability for given benchmarks. Naturally, solving also plays an important role in the other showcases. In the preprocessing showcase we were interested in studying the impact of individual and combined preprocessors on the behavior of the solvers. Recently published encodings of application problems and the ability of the solvers to handle those were studied in the dedicated application showcase. Here, we considered only newly committed benchmarks. Finally, the certification showcase was dedicated to the evaluation of trace producing solvers and to the evaluation of the performance of the certification frameworks. Obviously, the showcases are strongly related and results from one showcase might also be of relevance for the other showcases. However, the different showcases allowed us to focus on different aspects of the solving process.
     </paragraph>
     <paragraph>
      One piece of feedback we received several times for the organization of the QBF Gallery 2013 was that some important aspect is missing: the competition. Besides the scientific insights, research challenges and documentation of the state of the art, one motivation in participating in a competition is the fun factor and the direct comparison with competitors. Therefore, the participants asked for a competitive setup where prizes are awarded to the best solvers. As a follow-up event of the QBF Gallery 2013, we therefore organized the QBF Gallery 2014 as a traditional solver competition in the context of the FLoC Olympic Games,{sup:2} awarding different medals to the best performing solvers. For the benchmarks, we reused variants of the sets established during the QBF Gallery 2013, which were available to all participants.
     </paragraph>
     <paragraph>
      In this paper, we take a look behind the scenes of the QBF Gallery 2013 and we report on the experiments which yield the basis for the conducted tool evaluations. To this end, we first summarize the participating systems and the evaluated benchmarks submitted to the QBF Gallery 2013 in Section 2.1. We describe the four different showcases that we considered in our experiments: the solving showcase is presented in Section 3.1, followed by the preprocessing showcase in Section 3.2. In Section 3.3, we report on the application showcase, and finally, in Section 3.4 we summarize the certification showcase. In Section 4, we conclude this paper with a short summary of the QBF Gallery 2014, which was organized as a competition in the context of the FLoC Olympic games. Then we briefly discuss insights gained from the organization of the QBF Gallery and conclude with lessons learned.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Setup of the QBF Gallery 2013
     </section-title>
     <paragraph>
      In early 2013, we invited the QBF research community to participate in the first edition of the QBF Gallery by contributing ideas, tools, and benchmarks. Overall, 23 contributors from eight countries provided their tools for experiments. The submissions included 15 solvers for QBFs in conjunctive normal form (CNF), one non-CNF solver, three 2-QBF solvers,{sup:3} four preprocessors, two certification tools, and five new benchmark sets. Besides the newly submitted formulas we additionally considered more than 7,000 formulas provided by the QBFLIB [16], the community portal of QBF researchers. With these artifacts, we performed more than 114,000 runs in over 11,000 CPU hours. Details on the used infrastructure are given with the description of the different experiments. Benchmarks and log files of the runs are available at the website of the QBF Gallery 2013 [43].
     </paragraph>
     <paragraph>
      At the QBF Gallery event of 2013, we focused on general aspects of tools in the context of QBFs and not only on runtime performance. We set up four showcases where we addressed typical usage scenarios such as solving, preprocessing, novel applications, and strategies/certificates. We tried to identify trends and to gain insights into the performance of the tools. This is very different from previous QBFEVALs, which focused mainly on the competitive aspects in terms of solving performance. On purpose, we decided to use the simplest possible performance metrics like number of solved formulas, average and total runtimes. These simple metrics were sufficient for our goal of understanding how the different systems perform on different benchmark sets. However, in a competitive setting other metrics (cf. for example [45]) might have been more adequate.
     </paragraph>
     <section label="2.1">
      <section-title>
       Participating systems and benchmarks
      </section-title>
      <paragraph>
       In this section, we give an overview of the submitted tools and the benchmarks used in the experiments. We provide references to related literature describing the internals of each solvers. The benchmarks are available at the QBF Gallery 2013 website [43].
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Tools
       </section-title>
       <paragraph>
        An overview of the submitted tools and contributors is shown in Table 1. The submissions include four preprocessors, 15 solvers as well as two certification tools. Please note that it was allowed to submit up to three different configurations of one tool.
       </paragraph>
       <paragraph>
        Preprocessors. The goal of preprocessors is to rewrite a formula in prenex conjunctive normal form such that (1) its truth value is not changed and (2) it becomes easier to solve. To this end, preprocessors try to remove irrelevant information and to enhance the formula with additional structure useful for the solving process. Therefore, preprocessing might not only modify and eliminate clauses of a formula, but also add new clauses and even introduce new variables. Four preprocessors were submitted to the QBF Gallery: Bloqqer,{sup:4}Hiqqer3p, Hiqqer3e, and sQueezeBF. They all implement standard optimization techniques like pure and unit literal detection, universal reduction as well as equivalence substitution. Hiqqer3p is a tuned version of Bloqqer[7] that implements variable elimination, universal expansion and blocked clause elimination amongst other techniques. sQueezeBF[15] also uses variable elimination and additionally some special kind of equivalence rewriting that recovers structure lost during the normal form transformation. Hiqqer3e[47] uses an extension of failed literal detection.
       </paragraph>
       <paragraph>
        Solvers.Table 1 provides an overview of the submitted solvers. The icons shown are later used in the plots to indicate the performance of a solver. Previously, QBF competitions had a CNF track, a non-CNF track as well as a 2-QBF track. We also planned to organize these three different tracks, but due to the lack of submissions in the non-CNF track and the 2-QBF track, we focused on CNF solvers. Solver developers were allowed to submit three variants or configurations of each solver. Four contributors exercised this option, which includes versions of solvers that were enhanced by third-party preprocessors as well. The solver QuBE was the current version of QuBE [14], one of the dominators of the former QBF competitions. The preprocessor sQueezeBF is part of QuBE, where sQueezeBF was also submitted as a standalone tool (see above). The solver QuBE is based on the clause/cube learning (CDCL) variant for QBF. The solver DepQBF[34] also implements clause/cube learning and additionally it considers variable independencies reconstructed from the formula structure to gain more flexibility during the solving process. The variant DepQBF-lazy-qpup[36] uses a different learning approach. The solver Qoq[18] also implements clause and cube learning. Additionally, dual_Ooq implements dual propagation [20] by reconstructing structural information from the CNF. Finally, sDual_Ooq uses the preprocessor sQueezeBF before solving. The solver Hiqqer3 combines the preprocessor Bloqqer with failed literal detection [47]. If the formula is not solved by preprocessing, then an adopted version of the complete solver DepQBF is called. The GhostQ solver [30] aims at overcoming the loss of structural information imposed by the transformation to PCNF by introducing a concept called “ghost variables”. These ghost variables may be considered as a dual variant of the Tseitin variables and provide an efficient mechanism to simulate reasoning on disjunctive normal form. The solver GhostQ-CEGAR[22] extends GhostQ with an additional learning technique based on counterexample-guided abstraction-refinement (CEGAR). The variant bGhostQ-CEGAR calls the preprocessor Bloqqer in certain situations. The solver RAReQS applies CEGAR in an expansion-based approach [22].
       </paragraph>
       <paragraph>
        Certification frameworks.QBFcert[39] and ResQu[1] are tool suites to produce Skolem-function models of satisfiable QBFs and Herbrand-function countermodels of unsatisfiable QBFs. To this end, these tools extract a (counter)model from a resolution proof of (un)satisfiability. Since QBFcert and ResQu were the only certification tools submitted, we decided to consider additional publicly available tools and to run additional experiments as presented in Section 3.4.
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        Benchmarks
       </section-title>
       <paragraph>
        In the following, we describe the benchmark sets used in our experiments. New benchmark sets submitted by the participants as well as benchmarks from the public QBFLIB repository{sup:5} were considered. In our experiments, all formulas are in prenex conjunctive normal form (PCNF) with a quantifier prefix having an arbitrary number of quantifier alternations. Details on syntactic formula characteristics are shown in Table 2. For the showcase on applications we selected benchmark sets consisting of 150 formulas each.
       </paragraph>
       <list>
        <list-item label="•">
         Set eval2010: the complete set of 568 formulas used for QBFEVAL 2010[40].
        </list-item>
        <list-item label="•">
         Set eval2012r2: 345 formulas sampled from the collection of formulas available from QBFLIB. This set was also used for the QBF competition QBFEVAL 2012 Second Round, an unofficial repetition of the QBFEVAL 2012 with a new benchmark set.{sup:6}
        </list-item>
        <list-item label="•">
         Set eval2012r2-inc-preprocessed: Instances from the set eval2012r2 which were obtained by repeated, incremental preprocessing using the four preprocessors that were submitted to the showcase on preprocessing, as described in Section 3.2. We obtained the following two sets:
         <list>
          Set AABBCCDD: 234 instances resulting from the set eval2012r2 by incremental preprocessing, where the preprocessors are called in a tool chain in at most six rounds. From the 345 instances, 111 instances were solved during incremental preprocessing. In the tool chain, the formula produced by one preprocessor is forwarded to the next. A wall-clock time limit of 120 seconds was set for each call of a preprocessor. The preprocessors were executed in the ordering AABBCCDD, where “A” is Hiqqer3e, “B” is Bloqqer, “C” is Hiqqer3p, and “D” is SqueezeBF. Fixpoint detection was implemented so that preprocessing stops if the formula is no longer modified by any preprocessor.Set AADDBBCC: 241 instances resulting from the set eval2012r2 by incremental preprocessing. From the 345 instances, 104 instances were solved during preprocessing. This set was generated in similar fashion as the set AABBCCDD except that the execution ordering AADDBBCC was used.We selected the execution orderings AABBCCDD and AADDBBCC based on empirical findings we made in the showcase on preprocessing. For example, with ordering AABBCCDD the largest number of instances was solved. Due to the different characteristics of the techniques implemented in
         </list>
         <paragraph>
          Bloqqer (“B”) and SqueezeBF (“D”) we selected AADDBBCC, where SqueezeBF is executed before Bloqqer.
         </paragraph>
        </list-item>
        <list-item label="•">
         Set reduction-finding: formulas generated from instances of reduction finding [11], [25], [26], which is the problem to determine whether parametrized quantifier-free reductions exist between various decision problems in NL for one set of fixed parameters. A program to generate this set of benchmarks was also submitted by Charles Jordan and Lukasz Kaiser. The submitted set consists of 4608 QBF encodings of 2304 reduction problems, where each problem is encoded as a QBF with prefix ∀∃.
        </list-item>
        <list-item label="•">
         Set conformant-planning: 1750 instances from a planning domain with uncertainty in the initial state, contributed by Martin Kronegger, Andreas Pfandler, and Reinhard Pichler [31]. The consists of two different kinds of planning problems: dungeon and bomb.
        </list-item>
        <list-item label="•">
         Set planning-CTE: 150 instances resulting from compact tree encodings (CTE) of planning problems, contributed by Michael Cashmore [10].
        </list-item>
        <list-item label="•">
         Set sauer-reimer: 924 instances from QBF-based test generation, contributed by Paolo Marin [42].
        </list-item>
        <list-item label="•">
         Set qbf-hardness: 198 instances from bounded model checking of incomplete designs, contributed by Paolo Marin [38].
        </list-item>
        <list-item label="•">
         Set samples-eval12r2: ten sets containing 461 formulas each. The formulas in these sets were randomly selected from the instances available in QBFLIB. The random selection process was carried out with respect to families of instances, thus avoiding that instances from large families are overrepresented in the sampled set. In general it can often be observed that solvers perform either very good or very bad on a specific family. Therefore, data accumulated based on benchmark sets which are biased towards particular families is not expressive and may lead to misleading conclusions.
        </list-item>
       </list>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Showcases in the QBF Gallery 2013
     </section-title>
     <paragraph>
      We invited the participants to suggest the showcases to be considered. At the end, four different showcases were considered: (1) solving, (2) preprocessing, (3) applications, and (4) certification. In the following, we outline the setup of each showcase and summarize the most important results.
     </paragraph>
     <section label="3.1">
      <section-title>
       Showcase: solving
      </section-title>
      <paragraph>
       In this showcase, we evaluated the solvers on the benchmark set eval2012r2. We carried out separate runs with and without preprocessing using the preprocessor Bloqqer. All experiments were run on a 64-bit Linux Ubuntu 12.04 system with an Intel Core 2 Quad Q9550@2.83 GHz and 8 GB of memory. We used a time limit of 900 seconds and a memory limit of 7 GB. In the following, we focus on the results obtained for the set eval2012r2. Additional results for the set eval2010, including tables and plots, are reported in Appendix B (Table B.25, Table B.26, Table B.27, Table B.28, Table B.29). While some formulas appear in both sets eval2010 and eval2012r2, eval2012r2 contains formulas from more recent benchmark sets.
      </paragraph>
      <paragraph>
       Table 3 shows detailed results for the set eval2012r2 without preprocessing. Note that some solvers like dual_Ooq and Hiqqer3, for example, apply built-in preprocessing. Columns “runtime” report the average runtime of solved formulas and the total runtime spent on the entire benchmark set.
      </paragraph>
      <paragraph>
       This benchmark set is very suitable for search-based solvers such as bGhostQ-CEGAR (and its variants) and Hiqqer3, while the performance of expansion-based solvers like RAReQS and Nenofex is worse. However, both RAReQS and Nenofex solved five unique instances that no other solver could solve. Table 4 presents detailed numbers of solved instances for each benchmark family in the set eval2012r2. Fig. 1 shows a cactus plot of the runtimes of the solvers.
      </paragraph>
      <paragraph>
       We obtain a very different picture of the solver performance when the set eval2012r2 is preprocessed using Bloqqer. In the following experiment, every solver is run on the 276 instances that were preprocessed but not solved by Bloqqer. Some solvers additionally apply their built-in preprocessors. Table 5 shows the number of successfully solved formulas which, compared to Table 3, gives a very different picture. Notably, RAReQS and DepQBF-lazy-qpup (and its variants) are now more highly ranked than bGhostQ-CEGAR (and its variants). Although Nenofex still solved the smallest number of instances, as in Table 3, it solved eight instances uniquely, which is the largest number of uniquely solved instances among all solvers. Table 6 and Fig. 2 show detailed, family-based statistics and runtimes, respectively.
      </paragraph>
      <paragraph>
       As illustrated by the different rankings in Table 3, Table 5, the performance of the solvers varies depending on the use of preprocessing. On the original set eval2012r2 solvers with built-in preprocessing outperform solvers that do not have built-in preprocessing, as shown in Table 3. On the preprocessed set eval2012r2, another built-in preprocessing step using Bloqqer might have little effect, cause runtime overhead, and hence harm the performance of a solver. Solvers like dual_Ooq and GhostQ try to reconstruct part of the structure of a CNF formula as a preprocessing step. The purpose of this reconstruction step is to recover the structure that was obscured during the conversion of a non-CNF formula into CNF. Structural information might improve the performance of CNF-based solvers [18], [20]. However, structure reconstruction might be hindered when preprocessing by Bloqqer is applied upfront as in the experiment shown in Table 5. The solver bGhostQ-CEGAR dedicates some of its solving time to run Bloqqer in order to see if Bloqqer is able to solve a formula quickly. If this is not the case, then the original formula is considered for solving and the work spent for the preprocessing was useless.
      </paragraph>
      <section label="3.1.1">
       <section-title>
        Preprocessing and solving: “Best foot forward” analysis
       </section-title>
       <paragraph>
        On the one hand, solvers that do not apply built-in preprocessing might perform better on an instance that has been preprocessed using Bloqqer. On the other hand, solvers with built-in preprocessing or structure reconstruction might prefer the original instance.
       </paragraph>
       <paragraph>
        In order to analyze the performance of the solvers with and without prior preprocessing in more detail, we carried out the following experiments. We ran Bloqqer on all 345 instances in the benchmark set eval2012r2. From all these instances, 276 remained unsolved by Bloqqer. We ran each solver twice: once on the 276 instances after they have been preprocessed by Bloqqer, and once on the respective 276 original instances from the set eval2012r2 without preprocessing. That is, in this experiment we exclude instances from the set eval2012r2 that were solved already by Bloqqer.
       </paragraph>
       <paragraph>
        We classified the solvers into two categories, depending on the numbers of instances that were solved in these two runs. We classified a solver in the “NO Bloqqer” category if it performs better on the original instances than on the instances that have been preprocessed. If a solver performs better on the preprocessed instances than on the original ones, then we classified it in the “WANT Bloqqer” category.
       </paragraph>
       <paragraph>
        Table 7 shows the final classification of the solvers. In the category “WANT Bloqqer”, the columns “Best Foot” and “Worst Foot” report the numbers of instances that were solved by a solver with and without prior preprocessing by Bloqqer, respectively. In contrast to that, in the category “NO Bloqqer”, these columns report the numbers of instances that were solved by a solver without and with prior preprocessing by Bloqqer, respectively. That is, column “Best Foot” represents the best choice of a solver in terms of solved instances whether to run on the original instances or on the preprocessed ones. Contrary to the best choice, column “Worst Foot” represents the respective worst choice in each category.
       </paragraph>
       <paragraph>
        It is interesting to note that Hiqqer3 and QuBE do not have much preference whether to run on original instances or on preprocessed ones, because their respective best foot and worst foot statistics differ only by four and one formula(s). Recall that Hiqqer3 includes a modified variant of Bloqqer and that QuBE applies a powerful built-in preprocessor. We obtained different results when considering a different benchmark set (cf. Table B.29 in the appendix).
       </paragraph>
       <paragraph>
        The classification in Table 7 confirms the trend that is indicated by the different rankings of the solvers in Table 3, Table 5. Solvers in the “NO Bloqqer” category like bGhostQ-CEGAR (and its variants) perform better without prior preprocessing and thus are more highly ranked in Table 3 than solvers in the “WANT Bloqqer” category like RAReQS and DepQBF-lazy-qpup. In contrast to that, solvers in the “WANT Bloqqer” category perform better with prior preprocessing and thus dominate the solvers from the “NO Bloqqer” category in the ranking shown in Table 5.
       </paragraph>
       <paragraph>
        The best-foot-forward analysis presented above revealed that the performance of the solvers might heavily depend on the use of preprocessing when applied before the actual solving. In the related experiments, we preprocessed the instances by a single application of Bloqqer. We could also combine several preprocessing tools like sQueezeBF, for example, with Bloqqer to analyze their combined effects. However, here we decided to focus on Bloqqer since some of the submitted solvers like bGhostQ-CEGAR already apply Bloqqer as a built-in preprocessor. In the showcase on preprocessing to be presented below (Section 3.2), we report on a comprehensive evaluation of several preprocessing tools both independently from solvers and combinations thereof.
       </paragraph>
      </section>
      <section label="3.1.2">
       <section-title>
        Stratified sampling
       </section-title>
       <paragraph>
        In addition to the application of preprocessing prior to solving, the actual selection of benchmarks might have an influence on the performance of solvers and hence on the rankings in terms of solved instances. A ranking of solvers obtained by experiments might be skewed if certain families of instances are overrepresented in the benchmark set that underlies the experimental evaluation. In order to analyze the effect of the benchmark selection on the ranking of solvers, we carried out the following sampling experiment.
       </paragraph>
       <paragraph>
        From all benchmark instances available at QBFLIB, we randomly sampled seven benchmark sets containing 455 instances each in a stratified manner. The stratification consisted of randomly choosing six instances from each benchmark family. Thereby, as noted above, we consider a set of instances a family if this set was classified as such at the time the set was submitted to QBFLIB. The instances in the sampled sets were as contributed by users for use as benchmarks, and we did not apply preprocessing by Bloqqer.
       </paragraph>
       <paragraph>
        In this experiment, we deliberately do not disclose the actual names of the solvers, but used two-letter names. The intention was to put the focus on the experiment itself (which is the evaluation of the benchmark set) and not on the evaluation of a particular solving technique. Based on the best-foot-forward experiment described above, we selected the eight solvers that solved the largest number of formulas. Our focus was on understanding the effects that different selections of benchmark sets can have on the performance of the solvers. We do not declare a solver as the winner based on any ranking by the numbers of solved instances.
       </paragraph>
       <paragraph>
        Table 8 shows the rankings of the solvers for each of the seven randomly sampled benchmark sets according to the numbers of solved instances. Rather surprisingly, the rankings are identical for all seven benchmark sets. This also applies to the rankings by the penalized average runtime (PAR10) as shown in Table 9, where runs that timed out after 200 seconds were penalized with {a mathematical formula}10⋅200 seconds.
       </paragraph>
       <paragraph>
        Two factors that might have contributed to the rankings in Table 8, Table 9 are the relatively small time out of 200 seconds, and the stratified sampling that makes all the sampled benchmark sets fairly similar to each other. With longer time outs we expect to see more variation. The stratified sampling avoids that instances of certain benchmark families are overrepresented in the final set. Furthermore, solvers that perform particularly well on certain families no longer have an advantage when running on benchmark sets where the selection of instances is biased towards that family. Hence multiple solver runs on benchmark sets that were sampled in a stratified way together with different runtime cutoffs might help to obtain an unbiased ranking of solvers and finally to declare a winner in a competitive setting.
       </paragraph>
      </section>
     </section>
     <section label="3.2">
      <section-title>
       Showcase: preprocessing
      </section-title>
      <paragraph>
       The purpose of this showcase was to find out how many instances can be solved solely by preprocessing and to analyze the effects of preprocessing on the performance of solvers. The latter is closely related to the showcase on solving (Section 3.1). All experiments in this showcase were run on a 64-bit Linux Ubuntu 12.04 system with four 2.6 GHz 12-core AMD Opteron 6238 CPUs and 512 GB memory in total. The concrete memory limits varied for the different experiments.
      </paragraph>
      <paragraph>
       We carried out experiments in two settings: in the first setting, we ran each of the four submitted preprocessors shown in Table 1 individually on a given set of original instances. Then, we compared the sets of instances that were solved by a particular preprocessor. In this experiment, the preprocessors do not interfere with each other, which allows to analyze their individual strengths.
      </paragraph>
      <paragraph>
       In the second setting, we ran the four preprocessors incrementally in multiple rounds. For example, first preprocessor A is run, and its output, i.e. the preprocessed formula, is forwarded to preprocessor B, the output of B in turn is forwarded to C. Finally D is run on the output of C. Then a new round starts with A, B, C, and D. In this experiment the individual preprocessors influence each other, and hence their combined strengths can be analyzed. Given the number of available preprocessors, there multiple execution sequences like ABCD, ABDC, AABBCCDD, etc. We aimed at a comprehensive evaluation by considering as many execution sequences as possible given the available computational resources. When choosing the execution sequences, we also took the characteristics of the preprocessors into account. For example, it might be beneficial to run Hiqqer3e, which performs unit literal detection, before preprocessors that modify the structure of the formula as structure modifications might be prohibitive for the detection of unit literals.
      </paragraph>
      <paragraph>
       The time limits used in this showcase were smaller than the ones used in the other showcases. The choice of the time limits for preprocessing was based on the conjecture that if an instance can be solved solely by preprocessing, then it can be solved rather quickly.
      </paragraph>
      <section label="3.2.1">
       <section-title>
        Individual preprocessing
       </section-title>
       <paragraph>
        First, we address the question of how many instances can be solved solely by the individual preprocessors. Table 10 shows the results of running the four preprocessors on several benchmark sets described in Section 2.1.2. In these experiments, we used a wall-clock time limit of 300 seconds and a memory limit of 7 GB.
       </paragraph>
       <paragraph>
        Given the statistics in Table 10, the performance of the preprocessors varies with respect to the benchmark set. For example, in the benchmark set conformant-planning, Hiqqer3e solves the largest number of instances whereas Hiqqer3p solves the largest number of instances in the set reduction-finding. Note that by construction Hiqqer3e, unlike the other preprocessors, can only solve unsatisfiable formulas, since it does not apply variable elimination.
       </paragraph>
       <paragraph>
        Table 11 shows a combination of the statistics from Table 10: an instance is considered to be solved if it was solved by at least one of the four considered preprocessors. Interestingly, the total counts in Table 11 are not always clearly higher than the largest individual count from Table 10. This indicates that there are preprocessors that, regarding their effects, subsume other preprocessors on certain benchmark sets. For example, in the set planning-CTE, all instances that are solved by Bloqqer are also solved by Hiqqer3p. Further results including pairwise comparisons of the individual preprocessors can be found at the website of the QBF Gallery 2013.{sup:7}
       </paragraph>
      </section>
      <section label="3.2.2">
       <section-title>
        Incremental preprocessing
       </section-title>
       <paragraph>
        Motivated by the diverse performance of the individual preprocessors illustrated in the previous section, we investigate whether their individual strengths can be combined by incremental preprocessing. To this end, the preprocessors are run in multiple rounds. In our setting, at most six rounds were run for each instance. In each round, the instance preprocessed by one preprocessor is forwarded to another and hence the preprocessors influence each other. If an instance is solved by either preprocessor then the whole run terminates. In the following, “A” labels Hiqqer3e, “B” labels Bloqqer, “C” labels Hiqqer3p, and “D” labels SqueezeBF.
       </paragraph>
       <paragraph>
        A time limit of 120 seconds was imposed for each individual run of A, B, C, and D. Hence in total, given four preprocessors and six rounds, for each instance we allowed at most 2880 seconds for preprocessing. This time out is much larger than the time out of 900 seconds we chose in the showcases on solving and applications. Our motivation for the showcase on preprocessing was to analyze the power of preprocessing decoupled from solving. Therefore, we decided to allow more time for preprocessing than in a typical setting where a solver is combined with a preprocessor.
       </paragraph>
       <paragraph>
        If a preprocessor fails to process an instance within the given time limit or if it fails due to any other reason, then its input formula is passed on to the next preprocessor in the execution sequence without any modifications. We considered the benchmark set eval2012r2 and tested all {a mathematical formula}4!=24 possible execution sequences of A, B, C, and D.
       </paragraph>
       <paragraph>
        Table 12 shows the number of instances solved by each execution sequence. Each execution sequence solves more instances than any of the individual preprocessors (Table 10, Table 11). In total, 119 instances where solved by any of the execution sequences, which is 34% of the instances contained in the benchmark set eval2012r2. With individual preprocessing, in total 87 instances (25%) were solved by any of the preprocessors (first line in Table 11). These statistics clearly indicate the benefits of incremental preprocessing in terms of solved instances.
       </paragraph>
       <paragraph>
        However, the performance of incremental preprocessing is sensitive to the ordering of the preprocessors in an execution sequence. For example, the sequences ABCD and ABDC with the prefix AB solve the largest number of instances (107 and 106, respectively). In contrast to that, the sequences DCAB and DCBA with the prefix DC solve the smallest number of instances (96 each). This difference indicates that the techniques implemented in individual preprocessors might have a negative effect in incremental preprocessing. One preprocessor might destroy the structure of the formula, which in turn might restrict the effects of another preprocessor relying on that structure.
       </paragraph>
       <paragraph>
        According to the results shown in Table 12, the largest number of instances in the eval2012r2 were solved with the sequence ABCD. Based on this observation, we ran the sequence ABCD on the other benchmark sets for at most six rounds. Table 13 shows the results of these experiments. Except for the set qbf-hardness, incremental preprocessing solves considerably more instances than the individual preprocessors (Table 11). For example, for the sets planning-CTE and conformant-planning, 57% and 23% more instances are solved, respectively.
       </paragraph>
       <paragraph>
        In an additional experiment, we tested selected execution sequences from Table 12 on the benchmark set eval2012r2, where each preprocessor is run twice in a row. We selected the sequences to be tested according to the numbers of solved instances shown in Table 12 and the individual characteristics of the preprocessors.
       </paragraph>
       <paragraph>
        As in the previous experiments, we used a wall-clock time limit of 120 seconds for each individual call of a preprocessor and at most six rounds of incremental preprocessing. The results in Table 14 show a moderate increase in the number of solved instances, except for the sequences {a mathematical formula}(B2C2D2A2)6 and {a mathematical formula}(D2A2B2C2)6. These observations indicate that after some time preprocessing reaches a point where little or no progress at all is made. In the following, we analyze situations of this kind.
       </paragraph>
      </section>
      <section label="3.2.3">
       <section-title>
        Detection of fixpoints
       </section-title>
       <paragraph>
        When running incremental preprocessing in multiple rounds, it might happen that an instance is not modified anymore during a round. In this case, a fixpoint has been reached and hence preprocessing can be stopped.
       </paragraph>
       <paragraph>
        In the experimental evaluation of incremental preprocessing, we implemented the detection of fixpoints as follows. At the beginning of each round, before the first preprocessor in the execution sequence is run, the clause set of the current instance is normalized. Normalization discards tautological clauses and sorts the literals of each clause in the set. Then the set of clauses is sorted using the Linux command line tool sort. An MD5 hash value is computed for this normalized instance using the Linux command line tool openssl. The normalized instance is used only for the computation of the hash value and it is not forwarded to the preprocessors. Hence the detection of fixpoints does not interfere with preprocessing. At the end of the current round, after the last preprocessor in the execution sequence has been run, a hash value is computed for the normalized clause set of the instance produced by the last preprocessor. If the hash values at the beginning and at the end of a round are equal then the clause set was not modified by preprocessing in the current round. Hence a fixpoint has been reached and the run terminates.
       </paragraph>
       <paragraph>
        Due to normalization as described above, the detection of fixpoints we implemented does not distinguish between instances that differ in terms of the ordering of clauses or the ordering of the literals in the clauses. However, in practice different orderings might have an impact on the performance of the preprocessors as the heuristics internal to a preprocessor might be influenced. In the experimental analysis, we did not analyze the effects of different orderings of clauses or literals.
       </paragraph>
       <paragraph>
        Table 15 shows statistics on fixpoints and solved instances in each out of six rounds when running the five execution sequences from Table 14 on the set eval2012r2. The vast majority of instances is solved already in the first round. No instances are solved in rounds five and six. The number of fixpoints decreases considerably from round four up to round six. This indicates that it is justified to run a limited number of rounds of incremental preprocessing. For example, in a related experiment (not shown in the tables) where we ran the execution sequence ABCD in at most 12 rounds on the set eval2012r2, no instance was solved in rounds 7–12. Likewise, when increasing the number of rounds to 24, then no instance was solved in rounds 7–24.
       </paragraph>
      </section>
      <section label="3.2.4">
       <section-title>
        Solving performance of preprocessors
       </section-title>
       <paragraph>
        In contrast to the experiments conducted in the case of the best-foot-forward experiments above, in the following we are interested in the effects of applying different combinations of preprocessors in multiple rounds and assess the solving performance of preprocessors. As illustrated by Table 15, the numbers of instances solved by preprocessing using a particular execution sequence is sensitive to the ordering of the preprocessing tools in the sequence. To further analyze this effect, we tested the combination of incremental preprocessing and solving. Thereby, we preprocessed the benchmark set eval2012r2 (345 instances) using the execution sequences {a mathematical formula}(A2B2C2D2)6 and {a mathematical formula}(A2D2B2C2)6. This way, we obtained the two new benchmark sets AABBCCDD (234 instances remaining unsolved after preprocessing) and AADDBBCC (241 instances remaining) listed in Section 2.1.2, respectively. We selected the sequence {a mathematical formula}(A2B2C2D2)6 because it solved the largest number of instances (Table 15) and because {a mathematical formula}(ABCD)6 performed best according to Table 12. Since Bloqqer (“B”) and sQueezeBF (“D”) have different characteristics, we additionally selected the sequence {a mathematical formula}(A2D2B2C2)6 where the ordering of these two preprocessors is swapped and still Bloqqer is executed before Hiqqer3p (“C”). We did not consider the sequence {a mathematical formula}(A2D2C2B2)6 where only Bloqqer and SqueezeBF are swapped since, according to the results shown in Table 12, the execution ordering {a mathematical formula}(ADCB) solved one instance less than the execution ordering {a mathematical formula}(ADBC) in the sequence {a mathematical formula}(A2D2B2C2)6 we selected.
       </paragraph>
       <paragraph>
        Table 16, Table 17 show the performance of solvers on the two benchmark sets. The different rankings of the solvers in the tables indicate that their performance is sensitive to the execution ordering of the preprocessors. Furthermore, the total number of instances solved by preprocessing and by solving is different for the two benchmark sets. For the set AABBCCDD, 111 instances were solved by preprocessing (first line in Table 15) and 92 instances were solved by the best solver (first line in Table 16), giving a total of 203 solved instances. For the set AADDBBCC, 104 instances were solved by preprocessing (third line in Table 15) and 104 by the best solver (first line in Table 17), which gives 208 solved instances in total. That is, although preprocessing alone using the execution sequence {a mathematical formula}(A2D2B2C2)6 solves fewer instances than when using the sequence {a mathematical formula}(A2B2C2D2)6, solving performs better on the instances that were preprocessed using the former and results in a higher total number of instances solved by preprocessing and solving.
       </paragraph>
      </section>
     </section>
     <section label="3.3">
      <section-title>
       Showcase: applications
      </section-title>
      <paragraph>
       The purpose of the showcase on QBF applications was to evaluate the benchmark families submitted by the participants. The goal was to find out which types of solvers perform well on a specific family, what the reasons are for good or bad performance, and to identify future research directions to improve QBF solvers for benchmark families that arise from practical applications.
      </paragraph>
      <paragraph>
       From the benchmark sets listed in Section 2.1.2, the following five sets are related to practical applications: reduction-finding, conformant-planning, planning-CTE, sauer-reimer, and qbf-hardness. We split the set conformant-planning into the two subsets conformant-planning-bomb and conformant-planning-dungeon, containing instances with different characteristics. All the formulas considered in this showcase were newly submitted to the QBF Gallery. They have not been used in an evaluation before and are not available from QBFLIB.
      </paragraph>
      <paragraph>
       From the resulting six sets of application-related benchmarks, we randomly sampled 150 formulas each and tested the submitted solvers on each of these sampled sets. In the following experiments, a time limit of 900 seconds and a memory limit of 7 GB was used. We did not consider preprocessing in order to evaluate the solvers on the original instances as they were generated by the participants.
      </paragraph>
      <paragraph>
       Fig. 4 shows the run times of the solvers on each set. The plots indicate that the performance of the solvers greatly varies with respect to the benchmark set. Table A.19, Table A.20, Table A.21, Table A.22, Table A.23, Table A.24 show detailed solving statistics for each of the considered benchmark sets, illustrating the different rankings of the solvers in terms of the numbers of solved formulas. For example, Nenofex clearly outperforms the other solvers on the sets conformant-planning-dungeon and planning-CTE (except RAReQS), but is not competitive on the other sets. This observation is interesting because Nenofex and RAReQS rely on variable expansion. According to the experiments, expansion works particularly well on the considered formulas related to planning problems. On these problems, search-based solvers such as DepQBF, GhostQ-CEGAR, and Hiqqer3, for example, perform considerably worse. However, these solvers perform well on other benchmarks sets like qbf-hardness.
      </paragraph>
      <paragraph>
       The diverse solver performance on the different application benchmark families as illustrated by Fig. 4 motivates exploring potential combinations of the techniques implemented in search-based solvers and expansion-based solvers in future work. The difference in the performance depends on the considered benchmark family. In that respect, the difference is more pronounced in the showcase on applications than in the showcase on solving due to the homogeneity of instances within a particular application benchmark family.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Showcase: certificates
      </section-title>
      <paragraph>
       The goal of this showcase was to evaluate the current state of the art of the generation of proofs, certificates, and strategies, which has been a long standing problem in QBF research. Proofs, certificates, and strategies allow to verify the result produced by a QBF solver independently from the solving process and provide a deeper insight into the reasons for the (un)satisfiability of a QBF. This insight can be helpful for QBF applications where a mere “SAT/UNSAT” result produced by the solver is insufficient (e.g., QBF-based synthesis [8]).
      </paragraph>
      <paragraph>
       Given an unsatisfiable QBF ψ, a Q-resolution [29]proof of unsatisfiability is a sequence of Q-resolution steps that demonstrates the derivation of the empty clause from ψ. If the QBF ψ is satisfiable, then a variant of Q-resolution, called term resolution[17], [32], [49], can be applied to derive the empty cube{sup:8} from ψ by means of a Q-resolution proof of satisfiability. Once a proof Π (of unsatisfiability or satisfiability, respectively) has been found for a QBF ψ, a strategy[19] or a certificate[1] can be extracted from Π.
      </paragraph>
      <paragraph>
       The notion of a strategy is related to the game-oriented view of the semantics of QBF, where the universal and existential player, who assign the universally and existentially quantified variables, try to falsify and satisfy the formula, respectively. Thereby, the two players assign values to the variables in alternating fashion, starting at the left end of the quantifier prefix. The existential (universal) player wins if her selection of values satisfies (falsifies) the formula regardless of the values selected by the other player. A strategy for a satisfiable (unsatisfiable) QBF represents the winning choices of values the existential (universal) player must select depending on the values previously assigned by the universal (existential) player.
      </paragraph>
      <paragraph>
       A certificate of a satisfiable QBF ψ is a set {a mathematical formula}F={fx1(Dx1),…,fxn(Dxn)} of Skolem functions {a mathematical formula}fxi(Dxi) for the existential variables {a mathematical formula}x1,…,xn of ψ. A Skolem function {a mathematical formula}fxi(Dxi) of an existential variable {a mathematical formula}xi depends on the universal variables {a mathematical formula}Dxi that appear to the left of {a mathematical formula}xi in the quantifier prefix of ψ. In the process of Skolemization, each occurrence of an existential variable {a mathematical formula}xi in ψ is replaced by its Skolem function {a mathematical formula}fxi(Dxi). The QBF {a mathematical formula}ψ′ resulting from Skolemization contains only universal variables and is satisfiable, which can be checked using a propositional satisfiability (SAT) solver by checking whether the negated formula {a mathematical formula}¬ψ′ is unsatisfiable. Certificates of unsatisfiable QBFs are defined analogously in terms of Herbrand functions of universal variables. The process of Herbrandization results in an unsatisfiable formula containing only existential variables.
      </paragraph>
      <paragraph>
       Compared to strategies, which are based on a game-oriented view, certificates in terms of Skolem and Herbrand functions allow for a more explicit, functional representation of values of existential (universal) variables. Apart from that, the concepts of strategies and certificates are similar.
      </paragraph>
      <paragraph>
       In this showcase, we used the benchmark set eval2012r2 without preprocessing in order to evaluate the generation of proofs and certificates on original instances. Due to the lack of submissions of tools for the generation of strategies, we focused on proofs and certificates. Since only one proof-producing solver (i.e. DepQBF) and only two certificate extraction tools (i.e. ResQu and QBFcert) were officially submitted, we additionally considered further publicly available tools as shown in the lower part of Table 18.
      </paragraph>
      <paragraph>
       Due to the small number of tools submitted to this showcase, we refrain from ranking the tools according to their performance. Instead, we comment on the results of the experiments shown in Table 18 using various workflows consisting of different solvers and tools for the extraction and checking of certificates.
      </paragraph>
      <paragraph>
       All experiments were run using a wall-clock time limit of 600 seconds and a memory limit of 3 GB separately for solving (second column in Table 18) and the checking of proofs and the extraction and checking of the certificates (third column in Table 18).
      </paragraph>
      <paragraph>
       DepQBF solved and extracted proofs for 91 formulas. For about two thirds of these formulas, the tools QBFcert and ResQu successfully extracted and checked the certificates. These tools implement the same approach to certificate extraction based on Q-resolution proofs [1], [39] and show similar performance. However, the proofs produced by DepQBF had to be converted into a different format supported by ResQu. Both QBFcert and ResQu represent Skolem and Herbrand functions as and-inverter graphs (AIGs). In contrast to QBFcert, the workflow of ResQu includes simplification of AIGs using the tool ABC[9]. We attribute the difference in the number of instances certified by QBFcert and ResQu to the use of ABC. ResQu certified four instances which were not certified by QBFcert, and QBFcert certified eight instances not certified by ResQu.
      </paragraph>
      <paragraph>
       In the lower part of Table 18, the workflow implemented in QuBE-cert and ResQu is also based on Q-resolution proofs and certificates in terms of Skolem and Herbrand functions and thus is most closely related to DepQBF combined with QBFcert and ResQu. The tool checker does not extract certificates, but only checks the Q-resolution proofs produced by the solver QuBE-cert. The solvers sKizzo and squolem directly extract a certificate out of a given QBF, which is then checked using the tools ozziKs, qbv, or ResQu, respectively. The checker tool ozziKs is designed to check the certificates of satisfiable instances only. Errors were reported on 19 instances solved by squolem when converting the extracted certificates into the input format of ResQu.
      </paragraph>
      <paragraph>
       For the workflows that involve the extraction of Q-resolution proofs, we observed that not only run time but also memory is critical. For example, when solving an instance, DepQBF writes every Q-resolution step to a trace file stored on the hard disk. This trace file is analyzed by tools like QBFcert and ResQu to extract a certificate. On some instances, the trace file might become very large (up to several gigabytes) as it contains redundant information irrelevant for the proof. The subsequent certificate extraction step might fail due to memory limits. From the 91 instances solved by DepQBF, proofs were extracted from the trace files for 82 instances. The average (median) number of resolution steps in these proofs was 197,472 (2,439), ranging from one to 4,661,201 steps. For the files where the proofs were written to, the average (median) size was 94 MB (1 MB), with a range from 0.003 MB to 1,711 MB.
      </paragraph>
      <paragraph>
       Our experiments in the showcase on certificates showed that the power of available certification workflows lags behind the power of solvers. That is due to the fact that not every solved instance could be successfully certified within the given time and memory limits. In practice, the size of trace files written by solvers may hinder certification. As a remedy, solvers could maintain resolution proofs directly in memory rather than write trace files to the hard disk. The QRAT proof system [21], for example, may be used to generate proofs in a more compact way than Q-resolution.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Tables related to the showcase on applications (Section 3.3)
    </section>
    <section label="Appendix B">
     Tables related to the showcase on solving (Section 3.1)
    </section>
   </appendices>
  </root>
 </body>
</html>