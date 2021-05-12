<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:531">
</head>
<body bgcolor="white">
<a href="#0" id="0">A new family of search algorithms for DCOPs and Asymmetric DCOPs is presented.</a>
<a href="#1" id="1">All algorithms are based on combining two concepts: a pseudo-tree and forward (or backward) bounding.</a>
<a href="#2" id="2">A pseudo tree divides the problem into separate sub-problems, which can be solved simultaneously, independent of one another [1], [2], [3].</a>
<a href="#3" id="3">This allows for an inherently synchronous, yet concurrent, search of the problem.</a>
<a href="#4" id="4">A forward (or backward) bound is a method of pruning the search space by combining estimates from all agents.</a>
<a href="#5" id="5">In every step of the search the assigning agent broadcasts an estimate request to all relevant agents.</a>
<a href="#6" id="6">When all estimates have returned it combines them and can prune parts of the search space based on that information.</a>
<a href="#7" id="7">The first algorithm presented, Pseudo Tree Forward Bound (PT-FB), solves Distributed Constraints Optimization Problems (DCOPs).</a>
<a href="#8" id="8">It uses a variation of Forward Bounding (FB) on the structure of a pseudo-tree.</a>
<a href="#9" id="9">The algorithm has 3 major properties:</a>
<a href="#10" id="10">When possible, it divides the problem into sub-problems based on the pseudo-tree.</a>
<a href="#11" id="11">On parts of the tree which are essentially a chain, it performs FB synchronously.</a>
<a href="#12" id="12">This produces satisfactory results even when the pseudo tree is less than ideal.</a>
<a href="#13" id="13">It enforces a strict bound update, which increases the pruning of the search space.</a>
<a href="#14" id="14">An extensive experimental evaluation demonstrates that PT-FB greatly outperforms previous DCOP algorithms, both pseudo-tree based and forward bounding ones.</a>
<a href="#15" id="15">We have made several attempts to further extend the concepts of our algorithm, most notably we have tried to create a ConcFB[7] version on a pseudo tree.</a>
<a href="#16" id="16">We were surprised to find that it did not perform as well as we anticipated.</a>
<a href="#17" id="17">The ConcFB version outperformed PT-FB very slightly in terms of NCSCs, while performing much worse in terms of NCCCs.</a>
<a href="#18" id="18">We believe it may be due to the fact that in PT-FB each agent maintains a complex context, which is expensive to recreate for every new Search Process (SP).</a>
<a href="#19" id="19">This has led us to abandon the attempt for a concurrent version, which remains open for later studies.</a>
<a href="#20" id="20">Next, Asymmetric DCOPs (ADCOPs [10]) are addressed.</a>
<a href="#21" id="21">As stated before, no former algorithm for asymmetric DCOPs used pseudo-trees.</a>
<a href="#22" id="22">The only former ADCOP search algorithms used forward bounding.</a>
<a href="#23" id="23">The pseudo-tree approach is completely novel, in addition to its combination with forward bounding (e.g., AsymPT-FB).</a>
<a href="#24" id="24">In an ADCOP constraints have different costs for each of the constrained agents.</a>
<a href="#25" id="25">The ADCOP framework assumes that agents are cooperative and search for a solution that minimizes the sum of costs of all agents.</a>
<a href="#26" id="26">One specific aspect of ADCOP algorithms is their ability to maintain some of the privacy of the agents' constraints cost.</a>
<a href="#27" id="27">Every ADCOP algorithm keeps a balance between performance and maintaining privacy [10].</a>
<a href="#28" id="28">The asymmetric version of the PT-FB algorithm, AsymPT-FB, solves ADCOPs.</a>
<a href="#29" id="29">The modified algorithm uses the single phase approach, which means that for every assignment the cost of both sides of each constraint is added before proceeding to the next agent.</a>
<a href="#30" id="30">The method of achieving this is based on adding back-bounding to the original algorithm every time it performs forward-bounding.</a>
<a href="#31" id="31">This simple modification produces a complete ADCOP algorithm that is empirically shown to greatly outperform the original algorithms proposed in [10], while remaining competitive in terms of constraints privacy conservation.</a>
</body>
</html>