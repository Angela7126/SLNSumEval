<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:443">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have introduced a CP approach to solve the SMPTSP, along with a new set of challenging instances.</a>
<a href="#1" id="1">This model outperforms previous exact approaches on state-of-the-art benchmarks.</a>
<a href="#2" id="2">Furthermore, it provides very good lower and upper bounds, even on large instances, in a short time.</a>
<a href="#3" id="3">Thus, the CP approach competes with both exact and metaheuristic state-of-the-art approaches.</a>
<a href="#4" id="4">Furthermore, we have provided the notation {a mathematical formula}AMNV〈G|F|R〉, to describe a family of AtMostNValue propagators.</a>
<a href="#5" id="5">In particular, we introduced a new propagator, {a mathematical formula}AMNV〈GCI|MD,Rk|R1,3〉, to filter the conjunction of an AtMostNValue constraint and disequalities.</a>
<a href="#6" id="6">This propagator keeps close to the existing AtMostNValue propagator because it is fast to propagate, but also to capitalise over previous work in order to reduce implementation and maintenance issues.</a>
<a href="#7" id="7">{a mathematical formula}AMNV〈GCI|MD,Rk|R1,3〉 relies on a more appropriate graph structure ({a mathematical formula}GCI), as well as refined filtering rules ({a mathematical formula}R3), and a simple way to diversify filtering ({a mathematical formula}Rk), in order to improve the overall approach.</a>
<a href="#8" id="8">Moreover, this propagator gives control over the tradeoff between filtering and runtime.</a>
<a href="#9" id="9">As it is simple to implement, effective and relevant for many applications, we believe that this propagator would benefit the CP community.</a>
<a href="#10" id="10">Nevertheless, the maximum independent set is not a tight relaxation for AtMostNValue, and there are several leads to achieve a stronger filtering.</a>
<a href="#11" id="11">One of these is the Lovász number [45], a real number introduced in Graph Theory as an upper bound over the Shannon capacity of a graph.</a>
<a href="#12" id="12">Lovász's sandwich theorem indicates that the Lovász number of {a mathematical formula}GCI provides a valid lower bound over the number of distinct values to be taken by {a mathematical formula}X, which is greater or equal to the maximum independent set relaxation.</a>
<a href="#13" id="13">This number can be approximated with Semi Definite Programming (SDP) solvers (e.g.[8], [11]), which are unfortunately not yet fast enough to allow an integration into a global constraint.</a>
<a href="#14" id="14">Therefore, future improvement in SDP may have a positive impact on CP applications related to the SMPTSP.</a>
<a href="#15" id="15">Another research perspective would be to investigate the application of this propagator in the context of dynamic difference constraints, which occurs in many disjunctive scheduling problems.</a>
<a href="#16" id="16">Finally, we introduced an original way to enhance search by introducing and reifying a global constraint.</a>
<a href="#17" id="17">The success of this dedicated and naive attempt draw new perspectives regarding search heuristics.</a>
<a href="#18" id="18">We believe this concept may be generalised toward new black-box search strategies [9], [46], [49], based on global constraint reification.</a>
<a href="#19" id="19">This may reduce the need of designing dedicated search procedures [53], which still restricts the diffusion of CP.</a>
<a href="#20" id="20">Past work on both symmetry breaking [26] and global constraint learning [6] may be a good lead.</a>
</body>
</html>