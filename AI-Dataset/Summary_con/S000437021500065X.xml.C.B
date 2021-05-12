<html>
<head>
<meta name="TextLength" content="SENT_NUM:39, WORD_NUM:850">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we investigate in detail the skyline pattern mining problem by studying the theoretical relationships between condensed representations of patterns and skypatterns.</a>
<a href="#1" id="1">Based on the concept of skylineability, we have devised the static method Aetheris and the dynamic method {a mathematical formula}CP+Sky.</a>
<a href="#2" id="2">Aetheris exploits the condensed representations of patterns to provide a proper superset of skypatterns on which to apply the {a mathematical formula}Sky operator.</a>
<a href="#3" id="3">{a mathematical formula}CP+Sky iteratively refines the skyline constraints using the extracted patterns.</a>
<a href="#4" id="4">This leads to better pruning of the search space.</a>
<a href="#5" id="5">Our approach generates the complete set of skypatterns in a generic manner (i.e. with a large set of measures that includes statistical assessments such as the p-value).</a>
<a href="#6" id="6">The practical goal is to make the result of pattern mining useful from a user-preference point of view.</a>
<a href="#7" id="7">One strength of the approach lies in the fact that no threshold has to be set, the end-user only needs to specify as input the dataset and the set of measures she is interested in.</a>
<a href="#8" id="8">An extensive empirical study as well as a case study from chemoinformatics show the efficiency and effectiveness of our two algorithms according to both quantitative and qualitative aspects.</a>
<a href="#9" id="9">Despite the gain in generality brought by the CSP framework and the fact that Aetheris benefits from the pruning strategies based on the anti-monotonicity to extract patterns, {a mathematical formula}CP+Sky competes with Aetheris and even outperforms it in some cases.</a>
<a href="#10" id="10">However, with {a mathematical formula}CP+Sky, the search order of the patterns may significantly impact the efficiency of the CSP solver.</a>
<a href="#11" id="11">Investigating the most beneficial order in which patterns are enumerated is a promising research direction to maximize the effectiveness of the strategy of dynamically posting constraints.</a>
<a href="#12" id="12">Skypattern mining can generally be applied to a wide range of problems by adapting either the language or the dominance relation.</a>
<a href="#13" id="13">For instance, the language of sequences or graphs can also produce skypatterns.</a>
<a href="#14" id="14">The dominance relation can be changed or extended to take into account different other criteria for user-preferences.</a>
<a href="#15" id="15">We sketch now these two issues.</a>
<a href="#16" id="16">Our formalization, and especially the skylineability notion, is general enough to be applied to a large set of languages (sequences, trees and graph for instance).</a>
<a href="#17" id="17">However, a change in the language can impact the efficiency of the extraction methods.</a>
<a href="#18" id="18">Regarding Aetheris, the efficiency of the approach is based on Theorem 1 involving the distinct and indistinct operators.</a>
<a href="#19" id="19">As aforementioned, with itemset patterns and the frequency measure, the distinct operator corresponds to the well-known closed or free condensed representations of frequent patterns.</a>
<a href="#20" id="20">Consequently, the efficient extraction of skypatterns for more complex languages (i.e. skyline sequential patterns or skyline graph patterns) is strongly tied to the advances and progress on complex condensed representations of patterns.</a>
<a href="#21" id="21">Evaluating the distinct operator on more complex patterns efficiently such as sequences, trees and graphs implies additional challenges.</a>
<a href="#22" id="22">To cite one, in the case of sequences, convenient properties such as the free patterns apriori property[61], which implies effective search space pruning, cannot be used.</a>
<a href="#23" id="23">However, there are already many methods of extraction dedicated to closed sequential patterns, closed graphs and so on.</a>
<a href="#24" id="24">Extending {a mathematical formula}CP+Sky to other languages is a challenging task due to the difficulty of modeling complex patterns.</a>
<a href="#25" id="25">To the best of our knowledge, only certain types of pattern in sequence mining have been successfully studied [62], [63].</a>
<a href="#26" id="26">The dominance relation contains two components: the measures for which basic preferences are expressed (e.g., frequency, area) and the combination of these basic preferences (here, the Pareto composition).</a>
<a href="#27" id="27">Primitive-based measures are flexible enough to allow the user to express a wide variety of criteria.</a>
<a href="#28" id="28">Indeed, classical interestingness measures for pattern mining (such as frequency, growth rate), utility functions and measures of statistical significance (like the p-value) fall within this framework.</a>
<a href="#29" id="29">Of course, Aetheris, as mentioned above, depends again on condensed representations that are well-adapted for the desired measures.</a>
<a href="#30" id="30">Conversely, all interestingness measures are easily expressible with {a mathematical formula}CP+Sky.</a>
<a href="#31" id="31">Through its declarative nature, {a mathematical formula}CP+Sky offers via CSP a very flexible way to change the dominance relationship.</a>
<a href="#32" id="32">For instance the strict dominance (i.e. a pattern is dominated by another pattern when the latter has a better value for all measures in M), is easily configurable with CSP and this relaxation of the dominance relation leads to the mining of soft-skypatterns [2].</a>
<a href="#33" id="33">We think that the skypattern mining is particularly well suited to exploratory research.</a>
<a href="#34" id="34">Indeed, a strength of our approach is to propose a reduced collection of patterns to the data expert who can quickly analyze it.</a>
<a href="#35" id="35">It would be interesting to integrate the user feedbacks to make skypattern mining more iterative and more exploratory.</a>
<a href="#36" id="36">An interesting avenue is to offer an interactive way to refine the preference criteria by computing the skypattern cube according to all possible subsets of measures [64] and then assist the user with an intuitive navigation.</a>
<a href="#37" id="37">We claim that the skypattern cube exploration will provide a better understanding of the impact of the measures on the problem at hand.</a>
<a href="#38" id="38">Other kinds of interactions are also possible, such as discarding a skypattern to reveal patterns that were previously dominated and could become interesting.</a>
</body>
</html>