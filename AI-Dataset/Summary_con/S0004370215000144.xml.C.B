<html>
<head>
<meta name="TextLength" content="SENT_NUM:48, WORD_NUM:1217">
</head>
<body bgcolor="white">
<a href="#0" id="0">Although most of the IPC organizational efforts are carried out by the competition organizers, the IPC series is a collaborative work.</a>
<a href="#1" id="1">Our feeling is that this is one of the most (if not the most) important factors that explain its success.</a>
<a href="#2" id="2">Other factors include its fostering of the development of new planners and its setting of deadlines for their completion.</a>
<a href="#3" id="3">The IPC also contributes a number of planners to the public domain, as well as new benchmarking sets for performing new experiments.</a>
<a href="#4" id="4">Overall, the IPC improves our understanding in a few specific ways.</a>
<a href="#5" id="5">However, the competition might also have some undesirable effects arising from the assumption that the IPC portrays the current state of the art in automated planning.</a>
<a href="#6" id="6">Our view is that although IPC-2011 evaluated the largest number of planners for the largest number of domains ever, the competition results cannot be taken as an analysis of the current state of the art.</a>
<a href="#7" id="7">Our analysis only reflects the performance of the participant planners in a subset of planning tasks under a particular evaluation set-up.</a>
<a href="#8" id="8">Interesting planning tasks such as timeline-based planning, continuous planning, and real-time approximate reasoning were not included in the competition, and other useful evaluation set-ups, such as planning with small time bounds and exploiting further computational resources such as GPUs, were ignored.</a>
<a href="#9" id="9">Comparisons among the same planners performed with different criteria might yield different results.</a>
<a href="#10" id="10">This observation refers not only to formulae such as those discussed in Section 6 but also to the goal of the competition itself; for example, disproving plan existence has never been addressed in the IPC series [46], [47].</a>
<a href="#11" id="11">Moreover, the benchmark domains do not cover the full range of possible planning tasks and the number of realistic domains is still low.</a>
<a href="#12" id="12">In addition, it is very hard to come up with an unbiased selection of planning domains that does not favor any paradigm in particular.</a>
<a href="#13" id="13">All of this should be carefully taken into account since one of the main dangers of the IPC being understood as a study of the current state of the art is that the community might concentrate research too much around the few issues usually considered in the IPC and the successful methods distinguished in the most recent IPC edition.</a>
<a href="#14" id="14">In other words, the IPC might induce some form of standardization that would make “our innovation to become boring and predictable” (anonymous comment in a poll conducted among the planning community, October 2011).</a>
<a href="#15" id="15">As mentioned above, another advantage of the IPC is that it makes apparent the importance of contributing with standardized tools for automating the experimentation,{sup:17} or creating public repositories for storing the best known results, among others.</a>
<a href="#16" id="16">Our impression is that work should move away from organization of the IPC to focus on assisting in daily research.</a>
<a href="#17" id="17">A highly desirable situation would be to run the IPC with the same or similar software that researchers use to conduct their own experiments.</a>
<a href="#18" id="18">Again, this is not without risks and in the current context, standardized tools should be understood as readily available software for performing in the IPC the same (or similar) tasks that are performed by the research community.</a>
<a href="#19" id="19">In this regard, tools can be useful, but distributors should be “begged to put a bold and prominent disclaimer, explaining that these tools are not a replacement for analysis, effectively reminding researchers to perform their due diligence” (anonymous comment in a poll conducted among the planning community, October 2011).</a>
<a href="#20" id="20">The IPC series represents a good opportunity to perform large-scale experiments from which it is possible, if not to draw definitive conclusions, at least to derive data for some questions that are often controversial because they might bias the competition.</a>
<a href="#21" id="21">Let us discuss just a few that we feel are important.</a>
<a href="#22" id="22">One of these is memory management.</a>
<a href="#23" id="23">Automated planning systems are nothing more than computing systems.</a>
<a href="#24" id="24">Thus, we extended the concern about the time bound to the memory bound and for the first time obtained data on memory consumption.</a>
<a href="#25" id="25">Our recommendation, from a general point of view, is to offer as much memory as possible within reasonable limits (affordable memory in typical architectures at the time of organizing a new competition).</a>
<a href="#26" id="26">Again, this prevents experimentation and selection of the best adapted planners to small devices such as mobile phones and tablets, which are already very common.</a>
<a href="#27" id="27">To shed some light on the most controversial issues, we carefully examined the scoring schema of the last two IPCs.</a>
<a href="#28" id="28">There have been several criticisms of the scoring schema itself and the way it was applied in IPC-2008, and a few alternatives have been considered.</a>
<a href="#29" id="29">Although different metrics might produce different rankings (as observed in the temporal satisficing track), strong correlations were found across all metrics, although it should be noted that Score and Time generally exhibited lower correlation.</a>
<a href="#30" id="30">As noted elsewhere, this could result from the evaluation set-up for the competition, announced well ahead of the submission deadline.</a>
<a href="#31" id="31">We have two recommendations for this issue: (i) research should be dedicated to this question to gain new insights; and (ii) a repository should be set up in which the community could submit and query best known solutions for a number of planning tasks to improve the evaluation of every planner with regard to the same planning tasks [48].</a>
<a href="#32" id="32">Another interesting question often regarded as controversial is selection of the benchmarking problems.</a>
<a href="#33" id="33">We contributed here with specific means for automatically reusing problems from previous competitions.</a>
<a href="#34" id="34">In the absence of a better understanding of the difficulty of planning tasks, a measure such as the Glicko rating system (Section 3.2 and Appendix D) might produce rankings of this difficulty.</a>
<a href="#35" id="35">The key observation here is that problems can be compared with regard to their performance against planners.</a>
<a href="#36" id="36">This is not without problems and generalizing this idea poses some interesting challenges.</a>
<a href="#37" id="37">For example, maintaining a global list of the Glicko score for every planner might be difficult, because different versions of the same planner might easily proliferate, making it hard to trace the results and to compute the final score consistently across all versions.</a>
<a href="#38" id="38">Likewise, there is another issue related to credibility, and the only results to be taken into account for updating the Glicko score should be from official events such as the IPC series.</a>
<a href="#39" id="39">From a technical point of view, IPC-2011 also contributed by introducing a brand new track, the sequential satisficing multi-core track.</a>
<a href="#40" id="40">A comparison of the performance of the winner of this track with the winner of its single-core counterpart, the sequential satisficing track, was performed.</a>
<a href="#41" id="41">The results clearly indicate that research in this field is not yet mature and more research is needed to exploit additional computational resources.</a>
<a href="#42" id="42">The arrangement of any competition series is intimately linked to the desire to show progress.</a>
<a href="#43" id="43">As in other IPCs, a study on scalability was conducted and comparisons were made with the latest versions of the winners of IPC-2008.</a>
<a href="#44" id="44">Overall, evidence of significant progress was found in the sequential optimal and satisficing tracks.</a>
<a href="#45" id="45">However, progress seems to be more limited in the temporal satisficing track, for which quality improved but no evidence of enhanced coverage was observed.</a>
<a href="#46" id="46">Again, these results should be considered only with regard to the selection of problems in the last two IPCs.</a>
<a href="#47" id="47">To conclude, we hope that we have contributed to highlighting the importance of the IPC series.</a>
</body>
</html>