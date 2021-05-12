<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:324">
</head>
<body bgcolor="white">
<a href="#0" id="0">Over the last few years, logics for reasoning about strategic, resource-bounded agents and models have become a popular research topic, e.g. [1], [3], [6], [2], [14], [15], [4], [5], and, given current trends in the development of intelligent systems (e.g., driverless cars, unmanned vehicles, autonomous robots), the formal verification of resource-bounded systems will become even more important in the near future.</a>
<a href="#1" id="1">Unfortunately, formal, logic-based techniques for the verification of resource-bounded systems are often intractable or even undecidable.</a>
<a href="#2" id="2">In this paper we investigated the boundary of (un)decidable logics for verifying resource-bounded systems.</a>
<a href="#3" id="3">We identified a significant fragment of Resource Agent Logic ({a mathematical formula}RAL) with a decidable model checking property, and proved two new undecidability results.</a>
<a href="#4" id="4">We have shown that a rather natural property of models — that agents can always decide to do nothing — can make model checking decidable.</a>
<a href="#5" id="5">In particular, the positive proponent-restricted fragment of {a mathematical formula}RAL that we present, {a mathematical formula}pprRAL, is decidable in the presence of idle actions and undecidable without them.</a>
<a href="#6" id="6">However, the availability of idle actions is not sufficient on its own to make the model checking of {a mathematical formula}RAL, or even of the proponent-restricted fragment {a mathematical formula}prRAL, decidable.</a>
<a href="#7" id="7">We show that considering opponents acting under resource bounds makes model checking undecidable, as does allowing coalition modalities in the scope of negations.</a>
<a href="#8" id="8">The summary of known decidability and undecidability results is presented in Table 1.</a>
<a href="#9" id="9">Note that iRBMs are very similar to RBMs with finite semantics of [2] (see [8] and [9] for a formal statement of correspondence).</a>
<a href="#10" id="10">The result presented here, together with those of [8], [9] implies that {a mathematical formula}pprRAL is decidable over RBMs under finite semantics.</a>
<a href="#11" id="11">Finally, we did not discuss the complexity of the model checking problem for {a mathematical formula}pprRAL over iRBMs in this paper.</a>
<a href="#12" id="12">We conjecture that it is the same as the model checking problem for RB±ATL, which was recently shown in [35] to be 2exptime-complete.</a>
</body>
</html>