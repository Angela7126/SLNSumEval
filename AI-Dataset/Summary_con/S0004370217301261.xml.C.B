<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:458">
</head>
<body bgcolor="white">
<a href="#0" id="0">We discussed two schemes for decreasing the computational resources used to evaluate heuristics.</a>
<a href="#1" id="1">{a mathematical formula}LA⁎ and {a mathematical formula}LIDA⁎ are very simple to implement, and are as informed as {a mathematical formula}A⁎MAX and {a mathematical formula}IDA⁎MAX, respectively, with the caveat that {a mathematical formula}LIDA⁎ could lead to extra iterations.</a>
<a href="#2" id="2">While these can significantly speed up the search in some cases, such as when {a mathematical formula}t2 dominates the other time costs, additional benefit can be gained by using the rational metareasoning framework [1] to decide when computing the expensive heuristic is worth the time spent on it.</a>
<a href="#3" id="3">The resulting algorithms, {a mathematical formula}RLA⁎ and {a mathematical formula}RLIDA⁎, achieve better performance than their non-rational counterparts on many different problems.</a>
<a href="#4" id="4">In particular, {a mathematical formula}RLA⁎ is simpler to implement than its direct competitor, selective max, but its decision can be more informed.</a>
<a href="#5" id="5">When {a mathematical formula}RLA⁎ has to decide whether to compute {a mathematical formula}h2 for some node n, it already knows that {a mathematical formula}f1(n)≤C⁎.</a>
<a href="#6" id="6">In contrast, although selective max uses a much more complicated decision rule, it chooses which heuristic to compute when n is first generated, and does not know whether {a mathematical formula}h1 will be informative enough to prune n.</a>
<a href="#7" id="7">{a mathematical formula}RLA⁎ outperforms selective max in our planning experiments.</a>
<a href="#8" id="8">Furthermore, {a mathematical formula}RLIDA⁎ can make even better decisions than {a mathematical formula}RLA⁎, because it knows the “target value” for {a mathematical formula}f2 — the current threshold, T, in addition to the value of {a mathematical formula}f1(n).</a>
<a href="#9" id="9">This also means that {a mathematical formula}RLIDA⁎ knows whether {a mathematical formula}h2 is helpful immediately after evaluating it, while {a mathematical formula}RLA⁎ can only know that {a mathematical formula}h2 was not helpful for a node it expands, but will know if {a mathematical formula}h2 is helpful only when the search terminates.</a>
<a href="#10" id="10">Additionally, the decision rule for {a mathematical formula}RLA⁎ and {a mathematical formula}RLIDA⁎ only considers search time, not memory.</a>
<a href="#11" id="11">This not an issue for {a mathematical formula}RLIDA⁎, which only requires linear memory, but could cause {a mathematical formula}RLA⁎ to expand too many nodes and exhaust available memory.</a>
<a href="#12" id="12">Our analysis and empirical evaluation also shed some light on the question of when using rational metareasoning is worthwhile: Whenever we have multiple heuristics, where one of the heuristics is informative but expensive to compute, using rational metareasoning is likely a good idea.</a>
<a href="#13" id="13">In fact, in some cases the informative heuristic is so expensive that using it only becomes beneficial in conjunction with rational metareasoning.</a>
<a href="#14" id="14">However, if we only have heuristics which are relatively cheap to compute, the overhead of rational metareasoning, as well as the probability of making a mistake, are not worth the potential benefit.</a>
<a href="#15" id="15">In such cases, {a mathematical formula}LA⁎ or {a mathematical formula}LIDA⁎ are probably better choices.</a>
</body>
</html>