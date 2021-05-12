<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:397">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we considered the task of uniform interpolation – reformulation of an ontology into an alternative one that uses only a specific subset Σ of the initial signature and preserves all logical consequences about concept and role symbols from Σ. We proposed an approach to computing uniform interpolants of general {a mathematical formula}EL terminologies based on proof theory and regular tree languages.</a>
<a href="#1" id="1">One of our results is a representation of {a mathematical formula}EL TBoxes as regular tree grammars.</a>
<a href="#2" id="2">These grammars reduce the computation of logical consequences of ontologies to replacement of concept symbols within concepts by their subsumees/subsumers, which can serve as a basis for efficient ontology reformulation algorithms as demonstrated, for instance, in a follow-up work within the context of module extraction [23].</a>
<a href="#3" id="3">While the grammars were designed to enable forgetting-related ontology reformulation, they can also serve as a basis for computing equivalent, but syntactically different ontologies.</a>
<a href="#4" id="4">For instance, they can be used as a starting point for computing structurally simpler, equivalent ontologies, i.e., ontologies containing fewer DL constructs such as conjunction and existential restriction and fewer references to concept and role symbols [41], [42], since the grammars capture all logical consequences that might be part of the less complex ontology.</a>
<a href="#5" id="5">A further result obtained within this paper is a tight triple exponential bound on the size of uniform {a mathematical formula}EL interpolants: we showed that, if a finite uniform {a mathematical formula}EL interpolant exists, then there exists one of at most triple exponential size in terms of the original TBox, and that, in the worst case, no shorter interpolant exists.</a>
<a href="#6" id="6">This insight reveals the effect of structure sharing in the basic logic {a mathematical formula}EL and demonstrates the worst-case behaviour of uniform interpolation algorithms used for the purpose of module extraction.</a>
<a href="#7" id="7">It should be noted that this result does not constitute a fundamental technical obstacle for uniform interpolation in practice as demonstrated by Nikitina and Glimm [23], but rather contributes towards a higher stability of the corresponding tool support through the awareness of the theoretically possible triple exponential blowup.</a>
<a href="#8" id="8">Further, this result reveals the theoretic extent, to which we may be able to increase the succinctness of ontologies by introducing additional vocabulary.</a>
<a href="#9" id="9">Some ideas discussed within this paper inspired a follow-up work on refactoring of large and complex ontologies in order to reduce the maintenance effort by simplifying their structure and eliminating redundancy.</a>
</body>
</html>