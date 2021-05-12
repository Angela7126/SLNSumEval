<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:412">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we have defined the problem of exchanging knowledge between a source and a target KB connected through a mapping.</a>
<a href="#1" id="1">In particular, we have considered source KBs, target KBs, and mappings specified in the Description Logic DL-Lite{a mathematical formula}R, which is the logic underlying OWL 2 QL (one of the three profiles of the standard Web Ontology Language OWL 2), and we have studied some fundamental problems related to the exchange of knowledge in this context.</a>
<a href="#2" id="2">We have developed novel gameand automata-theoretic techniques, and have provided complexity results for these problems that range from NLogSpace to ExpTime.</a>
<a href="#3" id="3">As future work, we first note that the complexity of the non-emptiness problem has not been pinpointed in all cases (see Table 1).</a>
<a href="#4" id="4">In particular, it would be interesting to close the gap between the lower and upper bounds for the complexity of this problem for universal solutions and extended ABoxes, as we currently know it to be PSpace-hard and included in ExpTime.</a>
<a href="#5" id="5">Moreover, it would also be interesting to establish a lower bound for this problem for the case of universal {a mathematical formula}UCQ-solutions and simple ABoxes, and to prove it to be decidable for the case of universal {a mathematical formula}UCQ-solutions and extended ABoxes.</a>
<a href="#6" id="6">Second, the target signature in the non-emptiness problem is allowed to include new concepts or roles neither in universal solutions nor in universal {a mathematical formula}UCQ-solutions nor in {a mathematical formula}UCQ-representations.</a>
<a href="#7" id="7">The problem of allowing such additional symbols in these constructions is certainly interesting and worth investigating in the future.</a>
<a href="#8" id="8">Third, it is interesting to study the problem of knowledge exchange for richer ontology formalisms, such as the DLs of the {a mathematical formula}ALC-family, DLs with number restrictions or functionality, or existential rule languages/Datalog{sup:±}[66], [67], [68].</a>
<a href="#9" id="9">The aim would be to understand for which variants of such formalisms the existing techniques can be extended, and which variants instead would require a novel approach.</a>
<a href="#10" id="10">For example, the techniques based on reachability games and two-way alternating tree automata, both of which heavily rely on the canonical model property, can be extended to other Horn DLs, such as DL-Lite{a mathematical formula}hornH, {a mathematical formula}ELH, and Horn-{a mathematical formula}ALCHI, similarly to the approach in [30].</a>
<a href="#11" id="11">Finally, in this work we have not dealt with other standard data exchange reasoning tasks, such as composition and inversion of mappings [69], [70], [31], [20], [21].</a>
<a href="#12" id="12">These problems are certainly of interest in the KB exchange framework, and will be the subject of further investigation.</a>
</body>
</html>