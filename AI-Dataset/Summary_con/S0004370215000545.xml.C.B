<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:240">
</head>
<body bgcolor="white">
<a href="#0" id="0">We proposed two approaches that allow exploiting weights in real-time heuristic search algorithms: weighted lookahead and weighted update.</a>
<a href="#1" id="1">We incorporated weighted lookahead in LSS-LRTA*, a standard real-time heuristic search algorithm, and showed it does not yield performance improvements.</a>
<a href="#2" id="2">On the other hand, we incorporated weighted update in LSS-LRTA* and showed it may yield superior performance of up to one order of magnitude in some path-finding benchmarks.</a>
<a href="#3" id="3">Performance gains were also observed when incorporating the technique to other algorithms like LRTA*-LS and daLSS-LRTA*, although improvements on the latter algorithm are less impressive.</a>
<a href="#4" id="4">In addition we thoroughly analyzed some desirable properties of wLSS-LRTA*.</a>
<a href="#5" id="5">In particular, we prove that it terminates when a solution exists.</a>
<a href="#6" id="6">Furthermore we proved wLSS-LRTA* finds w-optimal solutions on convergence, but we also found bounds that can be much tighter, and, indeed, under certain conditions, we found a bound on solution quality that does not depend on w but only on features of the search graph.</a>
<a href="#7" id="7">Future work includes the incorporation of these techniques to other real-time heuristic search algorithms that do not use the Modified Dijkstra algorithm, such as, for example, RTAA* [8].</a>
<a href="#8" id="8">Another line of research has to do with how to determine good values of w and whether or not good policies for adjusting the weight dynamically can be devised.</a>
<a href="#9" id="9">Regarding convergence behavior, it seems necessary to study whether or not using dynamic weights will produce faster convergence results at the expense of sacrificing solution quality.</a>
</body>
</html>