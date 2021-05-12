<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:701">
</head>
<body bgcolor="white">
<a href="#0" id="0">The Fifth ASP Competition has been jointly organized by the University of Calabria (Italy), Aalto University (Finland), and the University of Genova (Italy), affiliated with the 30th International Conference on Logic Programming (ICLP 2014).</a>
<a href="#1" id="1">The main goals were to evaluate the progress of the state of the art in ASP solving and to further push the adoption of the standard language ASP-Core-2.</a>
<a href="#2" id="2">This paper contributes a detailed account of the competition design, participants, and results, and locates the ASP Competition in the spectrum of related events.</a>
<a href="#3" id="3">The results were orally presented at ICLP 2014 in Vienna, part of the Federated Logic Conference at the Vienna Summer of Logic, where the winners were announced and awarded in a FLoC Olympic Games ceremony on Monday, 21st July 2014.</a>
<a href="#4" id="4">The system clasp is the overall winner in the SP category, and its multi-threaded version clasp-mt won the MP category.</a>
<a href="#5" id="5">Different from previous competition editions, the Model&Solve track was an informal event held on-site: the team consisting of Mario Alviano (University of Calabria), Carmine Dodaro (University of Calabria), and Wolfgang Faber (University of Huddersfield) won the first place in this newly established ASP Modeling Competition.</a>
<a href="#6" id="6">Organizing and running the Fifth ASP Competition required a significant effort, and during this journey we faced several issues.</a>
<a href="#7" id="7">It was impossible to settle all of them in this edition of the ASP Competition, and in the following we share central aspects deserving further consideration in the future.</a>
<a href="#8" id="8">It would be a service to the community to create a common repository of domains and instances (say, ASP-LIB), similar to what is done in neighboring fields, e.g. SAT-LIB [80], SMT-LIB [84], and QBF-LIB [76].</a>
<a href="#9" id="9">Current benchmark sources include Asparagus and competition homepages, but none of them provides a comprehensive and maintained benchmark collection.</a>
<a href="#10" id="10">The lack of a standard language had been an obstacle for the general acceptance of a repository in the past, which is now abolished by the ASP-Core-2 standard.</a>
<a href="#11" id="11">There is a clear need for more domains stemming from real-world applications.</a>
<a href="#12" id="12">Similarly, the current benchmarks do not comprehensively cover ASP modeling concepts; e.g. only two out of seventeen Decision problems in Tracks #1 and #2 take significant advantage of non-tightness (cf.</a>
<a href="#13" id="13">Table 1).</a>
<a href="#14" id="14">The next call for benchmarks should, in our opinion, explicitly target real-world domains as well as modeling concepts.</a>
<a href="#15" id="15">We also feel that the classification by language features was useful in the analysis of competition results and should be maintained.</a>
<a href="#16" id="16">Regarding instance selection, generators for random or crafted instances should always be made publicly available for reference and reusability, while methods to focus on “meaningful” instances only, e.g. [53], should be taken into account as well.</a>
<a href="#17" id="17">ASP Competitions are inherently multifaceted and thus complex events, but the need to compare systems and evaluate the progress in the field is of course still central.</a>
<a href="#18" id="18">In this regard, tracks for non-ground (i.e. as of now) and ground (via a common format) inputs could be considered.</a>
<a href="#19" id="19">Moreover, additional tasks such as cautious and brave reasoning could give rise to new tracks.</a>
<a href="#20" id="20">The traditional scoring scheme of ASP Competitions accumulates the results of multiple tracks to determine an overall winner per category.</a>
<a href="#21" id="21">Although track winners are also awarded separately, newcomer and specialized systems that cannot compete in all tracks are penalized by global rankings, which may discourage their participation.</a>
<a href="#22" id="22">An option to be considered in the future is whether to keep tracks separate, in analogy to SAT Competitions where first places are awarded in each track, while there is no overall competition winner.</a>
<a href="#23" id="23">The diversity of ASP Competitions, featuring Decision, Optimization, and Query answering tasks, led to several output formats that solvers must comply with [59].</a>
<a href="#24" id="24">Multiple formats result in a significant burden to both organizers and developers.</a>
<a href="#25" id="25">We thus encourage future simplifications, e.g. by reducing the number of exit codes or making the usage of admitted ones more uniform and independent from specific reasoning tasks.</a>
<a href="#26" id="26">The Model&Solve track of past competition editions has been replaced with an on-site event, the ASP Modeling Competition [17], in the spirit of the Prolog Programming Contest.</a>
<a href="#27" id="27">This event attracted a significant number of participants, even though it was not widely advertised, as well as the interest of the community, thus calling for future continuation.</a>
</body>
</html>