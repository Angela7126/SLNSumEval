<html>
<head>
<meta name="TextLength" content="SENT_NUM:66, WORD_NUM:1192">
</head>
<body bgcolor="white">
<a href="#0" id="0">We presented the experiments we conducted in the context of the QBF Gallery 2013, an event for the evaluation of tools related to QBF solving.</a>
<a href="#1" id="1">In contrast to similar events, the QBF Gallery 2013 was not a competition but it was intended to be a platform for interested researchers to assess the state of the art of QBF technology.</a>
<a href="#2" id="2">In the following, we shortly summarize our findings.</a>
<a href="#3" id="3">Feedback from the participants.</a>
<a href="#4" id="4">While all participants agreed that it is important to have a shared forum to be able to compare tools in a uniform setting, it turned out that the involvement of most participants was mainly to provide tools and fixes.</a>
<a href="#5" id="5">There was a moderate discussion ongoing about benchmark selection and related organizational matters.</a>
<a href="#6" id="6">However, the main decisions remained with the organizers.</a>
<a href="#7" id="7">Finally, most participants asked for a competition.</a>
<a href="#8" id="8">The fun factor is a factor that may not be neglected, and especially when prizes are awarded, the motivation is even increased, although the event becomes more of a show than a scientific evaluation.</a>
<a href="#9" id="9">Benchmark selection.</a>
<a href="#10" id="10">We performed many experiments to assess the quality of the benchmark sets.</a>
<a href="#11" id="11">We came to the conclusion that the selected sets sufficiently represent the benchmark collection of the QBF research community, which consists of ten thousands of formulas.</a>
<a href="#12" id="12">We received new families of formulas stemming from various kinds of applications.</a>
<a href="#13" id="13">Overall, to compare solvers by their performance it is important that the formulas neither are too easy such that all solvers can solve them nor too hard.</a>
<a href="#14" id="14">We made the benchmarks used available to the community.</a>
<a href="#15" id="15">Preprocessing and solving.</a>
<a href="#16" id="16">We used all tools as black boxes as submitted by the authors, i.e., we did not consider other options than the default options of the tools.</a>
<a href="#17" id="17">Overall, we experienced that preprocessing has great impact on the solving performance and that the different preprocessors show diverse performance.</a>
<a href="#18" id="18">Further, it turned out that incremental preprocessing, i.e., multiple applications of a preprocessor until the formula does not change anymore, affects solving performance in a positive way.</a>
<a href="#19" id="19">Further, incremental preprocessing is more powerful than individual preprocessing and the solvers are sensitive to the order in which preprocessors are applied.</a>
<a href="#20" id="20">Although preprocessors usually do not implement complete decision procedures, often they can solve formulas directly.</a>
<a href="#21" id="21">Overall, different solvers perform differently well on different kinds of benchmarks, i.e., the solvers are sensitive to the structure of the considered problem.</a>
<a href="#22" id="22">This indicates that implementing a hybrid solver based on different solving paradigms might be promising.</a>
<a href="#23" id="23">In the current experiments, we used the preprocessors in the configurations suggested by their authors.</a>
<a href="#24" id="24">However, detailed parameter tuning might further speed up the overall solving process.</a>
<a href="#25" id="25">We found that on certain novel benchmarks “old” solvers like Nenofex perform very well (cf.</a>
<a href="#26" id="26">[37]).</a>
<a href="#27" id="27">Here a detailed evaluation would be of interest where systems available on the web are collected and run on recently generated encodings.</a>
<a href="#28" id="28">Solvers like Nenofex, Quantor, or sKizzo implement techniques orthogonal to approaches found in currently developed solvers, and explore the search space in a different manner.</a>
<a href="#29" id="29">For combining old and new techniques, hybrid solving or portfolio approaches might be one promising direction of future work (cf.</a>
<a href="#30" id="30">[33], [41]).</a>
<a href="#31" id="31">The drastic differences in the performance of solvers on certain benchmark families seem to be related to recent advances in QBF proof complexity.</a>
<a href="#32" id="32">In the QBF Gallery 2013 we did not run experiments to deliberately confirm theoretical results in proof complexity.</a>
<a href="#33" id="33">However, the global picture of our observations to some extent appears to reflect proof theoretical properties of approaches implemented in solvers.</a>
<a href="#34" id="34">Search-based solvers like QuBE and DepQBF, for example, are based on Q-resolution.</a>
<a href="#35" id="35">Traditional Q-resolution [29] allows to resolve on existential variables and rules out tautological clauses.</a>
<a href="#36" id="36">Long-distance Q-resolution[1], [48] generalizes Q-resolution by permitting the generation of certain tautological resolvents.</a>
<a href="#37" id="37">QU-resolution[46] generalizes Q-resolution by resolving also on universal variables.</a>
<a href="#38" id="38">The proof system LQU+resolution[2] combines long-distance Q-resolution and QU-resolution.</a>
<a href="#39" id="39">QU-resolution and long-distance Q-resolution were shown to be stronger than Q-resolution [5], [13], [46].</a>
<a href="#40" id="40">That is, there are classes of QBFs where any Q-resolution proof is exponentially larger than a proof in QUor long-distance Q-resolution.</a>
<a href="#41" id="41">Further, LQU+resolution was shown to be stronger than QUand long-distance Q-resolution [2].</a>
<a href="#42" id="42">From a practical perspective, only Q-resolution and long-distance Q-resolution are applied for QBF solving in a systematic way.</a>
<a href="#43" id="43">Hence the power of stronger proof systems like LQU+resolution is still left unused in practice.</a>
<a href="#44" id="44">A variant of DepQBF and the solver Quaffle [48]{sup:9} support long-distance Q-resolution, which however did not participate in the QBF Gallery 2013.</a>
<a href="#45" id="45">QU-resolution [46] is implicitly part of abstraction-based failed-literal detection for QBF [35], as implemented in the preprocessor Hiqqer3e[47].</a>
<a href="#46" id="46">Hence preprocessing makes QU-resolution available in current solving workflows.</a>
<a href="#47" id="47">This in turn may explain the benefits of preprocessing on solver performance, as QU-resolution is stronger than Q-resolution, which is typically applied in search-based solvers.</a>
<a href="#48" id="48">Expansion of universal variables is another successful approach to QBF solving, in addition to backtracking search and Q-resolution.</a>
<a href="#49" id="49">A variant of universal expansion was formalized as the proof system {a mathematical formula}∀Exp+Res[23], [24].</a>
<a href="#50" id="50">Thereby, initially all universal variables are expanded.</a>
<a href="#51" id="51">The resulting propositional formula contains only existential variables and can be solved by Q-resolution.</a>
<a href="#52" id="52">The proof system {a mathematical formula}∀Exp+Res was generalized to instantiation of universal variables by truth constants in the proof system IRM-calc [4].</a>
<a href="#53" id="53">It was shown that IRM-calc polynomially simulates the expansion-based proof system {a mathematical formula}∀Exp+Res.</a>
<a href="#54" id="54">That is, for any proof in {a mathematical formula}∀Exp+Res there is a proof in IRM-calc that is at most polynomially larger.</a>
<a href="#55" id="55">It was shown that Q-resolution and {a mathematical formula}∀Exp+Res are incomparable with respect to worst-case proof sizes [5], [24].</a>
<a href="#56" id="56">That is, there are classes of QBFs that have proofs in {a mathematical formula}∀Exp+Res of only exponential size but Q-resolution proofs of polynomial size, and vice versa.</a>
<a href="#57" id="57">This theoretical result conforms to our observations made in the experiments conducted in the QBF Gallery 2013.</a>
<a href="#58" id="58">On certain instances, expansion-based solvers clearly outperform search-based solver relying on Q-resolution.</a>
<a href="#59" id="59">For practical QBF solving, it may be worth combining both expansion and Q-resolution in a single solver to benefit from the strengths of both proof systems.</a>
<a href="#60" id="60">So far, the generalized proof systems IRM-calc and LQU + resolution [5] have not been implemented in solvers and hence applying them may further improve the state of the art.</a>
<a href="#61" id="61">Based on the experience gained from the QBF Gallery 2013, one year later, the follow-up event QBF Gallery 2014 was organized in the context of the FLoC Olympic Games.</a>
<a href="#62" id="62">As the 2014 edition of the Gallery was competitive, the organizing team was changed, because here no developer submitting a participating solver should be involved in the organization.</a>
<a href="#63" id="63">Many of the formulas collected for the QBF Gallery 2013 were used in the Gallery 2014 and from the showcases, three tracks were derived, namely (i) the QBFLIB track, (ii) the Preprocessing track, and (iii) the Application track.</a>
<a href="#64" id="64">Interestingly, all participants who gain benefits from using Bloqqer also submitted their tool with Bloqqer, what is in accordance with the license of version v35.</a>
<a href="#65" id="65">In 2014, no certification track was organized, because although there have been several application papers in 2014 using function extraction facilities for solving their application problems, there are still very few solvers supporting certification.</a>
</body>
</html>