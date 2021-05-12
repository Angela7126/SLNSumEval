<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:437">
</head>
<body bgcolor="white">
<a href="#0" id="0">We present a computational approach for conceptual blending and implement the generalisation of algebraic specifications using a transition system semantics of preconditions and postconditions within ASP.</a>
<a href="#1" id="1">This allows us to access generalised and commonalised versions of the input specifications, which let us find useful blends.</a>
<a href="#2" id="2">By using theorem solvers, we are able to generate only logically consistent blends.</a>
<a href="#3" id="3">To the best of our knowledge, there exists currently no other blending framework that can resolve logical inconsistencies.</a>
<a href="#4" id="4">Except for [13], we have not seen another blending framework that automatically finds a generic space, while using a similarly expressive representation language.</a>
<a href="#5" id="5">On top of the ASP-based implementation, we propose metrics to evaluate the quality of blends, based on the cognitive optimality principles by Fauconnier and Turner [27].</a>
<a href="#6" id="6">As overviewed in our related work section, a number of researchers in the field of computational creativity have recognised the value of conceptual blending, and particular implementations of this cognitive theory have been proposed [83], [63], [64], [33], [36], [20].</a>
<a href="#7" id="7">The existing approaches that we investigated lack a sophisticated evaluation to determine formally how ‘good’ a blend is, with the exception of [63], [64], which also use optimality criteria based on [27]'s theory.</a>
<a href="#8" id="8">The described amalgam-based workflow for conceptual blending is part of a bigger computational framework, the Cobble system,{sup:9} implementated within the COINVENT project [73].</a>
<a href="#9" id="9">A fairly comprehensive overview of the results of the COINVENT project can be found in [15].</a>
<a href="#10" id="10">{sup:10} A prototypical implementation of the system can be accessed online.</a>
<a href="#11" id="11">{sup:11}</a>
<a href="#12" id="12">While the proof-of-concept in Section 4 demonstrates some interesting examples, it is by no means close to a solid empirical evaluation.</a>
<a href="#13" id="13">Running the system on a multitude of concept definitions, e.g. from ontology databases such as Ontohub[50], [5], and developing an evaluation method to quantify the quality of generated blends is subject to future work.</a>
<a href="#14" id="14">Another more theoretical branch of future work is to generalise our approach to discover creative ‘eureka lemmas’ in mathematics for more elaborated data structures.</a>
<a href="#15" id="15">For example, a general form of describing a data structure is to define a constructor as {a mathematical formula}c:list(τ)×list(σ)→σ.</a>
<a href="#16" id="16">This is to say that a constructor can take any number of non-recursive and recursive arguments to form another version of itself.</a>
<a href="#17" id="17">In the example of naturals, the constructor is {a mathematical formula}s([],[x])≡s(x) and for lists {a mathematical formula}cons([h],[l])≡cons(h,l).</a>
<a href="#18" id="18">For binary trees with data at the nodes where the constructor is {a mathematical formula}t::([h],[l1,l2]) since there are two recursive arguments.</a>
<a href="#19" id="19">This allows us to find a mapping in the generic space between constructors, and hence to use the techniques expressed in this paper to discover eureka lemmas in new theories.</a>
</body>
</html>