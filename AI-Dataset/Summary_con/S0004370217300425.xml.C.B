<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:258">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper deals with the set-inversion problem {a mathematical formula}X=f−1(Y) in the case where both f and {a mathematical formula}Y are uncertain, i.e., f belongs to the interval of functions {a mathematical formula}[f−,f+] and {a mathematical formula}Y belongs to a thick set, i.e., an interval of sets {a mathematical formula}〚Y〛=〚Y⊂,Y⊃〛.</a>
<a href="#1" id="1">After introducing the new notions of thick intervals and thick boxes, a new algorithm for set inversion has been proposed.</a>
<a href="#2" id="2">It is able to compute a thick solution set {a mathematical formula}〚X〛=〚X⊂,X⊃〛 containing all feasible solution sets.</a>
<a href="#3" id="3">From the computational point of view, thick intervals allow us to have a better understanding of the uncertainty.</a>
<a href="#4" id="4">For instance, for the set inversion problem, we are able to detect that a box is included in the penumbra {a mathematical formula}X⊃\X⊂.</a>
<a href="#5" id="5">In this penumbra, we can conclude that any bisection would be useless.</a>
<a href="#6" id="6">This could not have not been detected using classical intervals.</a>
<a href="#7" id="7">As a consequence, the accumulation zone (i.e., the part of the search space where tiny boxes are still bisected) for thick interval based algorithms has a zero volume, since it corresponds to the boundary of the penumbra.</a>
<a href="#8" id="8">Using classical intervals instead, we could obtain similar results, but the accumulation zone would correspond to the whole penumbra, which has a nonzero volume.</a>
<a href="#9" id="9">As a result, a large part of the computational burden made by traditional interval algorithms is done on a part of the search space which has no influence on the final result.</a>
<a href="#10" id="10">Note.</a>
<a href="#11" id="11">The Python programs, associated with the test-case are given at the following link.</a>
<a href="#12" id="12">www.ensta-bretagne.fr/jaulin/thick.html</a>
</body>
</html>