<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:452">
</head>
<body bgcolor="white">
<a href="#0" id="0">In our setting, we have {a mathematical formula}k=n (since coalition structures are allowed to contain up to n coalitions) and {a mathematical formula}fi=v for all {a mathematical formula}i∈{1,…,k} (since all coalitions are evaluated using the same function, v).</a>
<a href="#1" id="1">Furthermore, the set of possible coalition structures will often be referred to as the “search space”.</a>
<a href="#2" id="2">Of course, it would be possible to avoid all redundant operations by simply considering all movements, and checking them one by one to identify (and avoid) any movements that lead to an already-examined split.</a>
<a href="#3" id="3">As mentioned in the introduction, this is theoretically the state-of-the-art set partitioning algorithm in terms of worst-case runtime; it runs in time {a mathematical formula}O(2n).</a>
<a href="#4" id="4">In this section, we show how to modify IP so that it searches multiple subspaces simultaneously and thus avoids repeating certain operations.</a>
<a href="#5" id="5">By repeating this process for every size s, sb-ODP gradually evaluates more and more subspaces, until it eventually searches the entire space.</a>
<a href="#6" id="6">In such games, the value of a coalition depends on the coalition structure it appears in.</a>
<a href="#7" id="7">Using these bounds, the algorithm computes an upper bound {a mathematical formula}UB⁎=maxI∈In⁡UBI and a lower bound {a mathematical formula}LB⁎=maxI∈In⁡LBI on the value of an optimal coalition structure {a mathematical formula}CS⁎.</a>
<a href="#8" id="8">Thus, when we say “in practice”, we do not mean “on average”.</a>
<a href="#9" id="9">We have shown that DP evaluates all the movements in the coalition structure graph, stores the best ones in the table t, and then selects from t the movements that together form a path from the bottom node to an optimal node.</a>
<a href="#10" id="10">Therefore,{a mathematical formula}</a>
<a href="#11" id="11">We remark that, unlike {a mathematical formula}DPM⁎⁎, sb-ODP is an anytime algorithm: at any point in time {a mathematical formula}CS⁎⁎ stores the best coalition structure identified so far, and the value of this coalition structure goes up as s increases.</a>
<a href="#12" id="12">As for the remaining subspaces, the algorithm searches them one at a time.</a>
<a href="#13" id="13">However, when both techniques are activated, it is faster to run ODP-IP (sometimes by nearly two orders of magnitude, e.g., given the modified-normal distribution) than to run ODP or IP alone, or even run them both in parallel.</a>
<a href="#14" id="14">The first modification is when {a mathematical formula}|I∖I⁎|<d.</a>
<a href="#15" id="15">Next, we explain how a subspace is searched.</a>
<a href="#16" id="16">{a mathematical formula}</a>
<a href="#17" id="17">Improving the DP algorithm</a>
<a href="#18" id="18">To be more precise, for every coalition value, {a mathematical formula}v(C), the algorithm needs to use the following number: {a mathematical formula}(nn)v(C).</a>
<a href="#19" id="19">While this is clearly the most efficient data structure, for large problem instances the available memory might not be sufficient, in which case other data structures must be explored.</a>
<a href="#20" id="20">Against this background, we present in Section 5.1 a new representation of the search space, which provides the corner stone upon which our hybrid algorithm is built.</a>
</body>
</html>