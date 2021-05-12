<html>
<head>
<meta name="TextLength" content="SENT_NUM:25, WORD_NUM:625">
</head>
<body bgcolor="white">
<a href="#0" id="0">We embedded abstract dialectical frameworks into Denecker et al.ʼs lattice-theoretical formalism for the abstract study of nonmonotonic logical languages.</a>
<a href="#1" id="1">This provides useful insights into the relationship of abstract argumentation frameworks and abstract dialectical frameworks with other nonmonotonic knowledge representation formalisms.</a>
<a href="#2" id="2">In this last section, we will provide a concise overview over the results of our investigation.</a>
<a href="#3" id="3">First, for reference and as a completion of the table in Definition 2.2, we review the definitions of operator-based semantics in Table 1.</a>
<a href="#4" id="4">Fig. 1 then depicts the relationship between the different semantical notions explored in this paper.</a>
<a href="#5" id="5">If a semantics σ is seen as a function assigning to a knowledge base κ a set of models, then a partial order on semantics is given by {a mathematical formula}σ1⩽σ2 iff {a mathematical formula}σ1(κ)⊆σ2(κ) for all κ. In the figure, an arrow from {a mathematical formula}σ1 to {a mathematical formula}σ2 expresses {a mathematical formula}σ1⩽σ2 – in words, all {a mathematical formula}σ1-models are also {a mathematical formula}σ2-models.</a>
<a href="#6" id="6">Next, Table 2 shows the correspondences between different argumentation semantics and operator-based semantics.</a>
<a href="#7" id="7">The operator-based semantics lead to new semantics for default logic and autoepistemic logics via their respective consequence operators [12].</a>
<a href="#8" id="8">A discussion of these semantics is however out of the scope of this paper.</a>
<a href="#9" id="9">Finally, Fig. 2 on p.</a>
<a href="#10" id="10">68 shows the location of abstract dialectical frameworks with respect to different approaches in the area of nonmonotonic reasoning.</a>
<a href="#11" id="11">We use a very strong notion of one formalism being at least as expressive as another: the existence of a polynomial and modular translation that is faithful with respect to all operator-based semantics.</a>
<a href="#12" id="12">Such results existed previously for the translation from logic programs into default theories of Marek and Truszczyński [27], and the translation from default logic into autoepistemic logic of Konolige [26] – for details see Denecker et al. [11].</a>
<a href="#13" id="13">In this paper, we added argumentation frameworks and abstract dialectical frameworks to the picture.</a>
<a href="#14" id="14">In general, we are not aware of any works that address the relationship of abstract dialectical frameworks with other nonmonotonic knowledge representation formalisms, attempt a principled reconstruction of ADF semantics or generalise argumentation semantics to an abstract operator-based setting.</a>
<a href="#15" id="15">As we observed in Example 3.7, it is not entirely clear how to define the union of two ADFs that share statements.</a>
<a href="#16" id="16">Although for specific representations of acceptance conditions such a union should be straightforward to define, we want to devote some future work into abstracting from specific representations and develop a general method for combining ADFs.Corollary 3.13 has shown that Brewka and Woltran [3] defined not only the notion of an ADF model, but also the ultimate three-valued approximation of this notion.</a>
<a href="#17" id="17">In recent related work, Brewka et al. [5] introduced several new ultimate semantics for abstract dialectical frameworks.</a>
<a href="#18" id="18">In future research we will compare the different semantics defined by their work and in this paper.</a>
<a href="#19" id="19">Furthermore, Denecker et al. [13] study several other ultimate semantics.</a>
<a href="#20" id="20">It is an important aspect of future work to investigate these ultimate semantics in detail and to compare them with the ones investigated here and by Brewka et al. [5].We remarked on several occasions throughout the paper that we defined new semantics for default and autoepistemic logics (admissible, preferred, semi-stable, stage).</a>
<a href="#21" id="21">We plan to study these semantics in greater detail, especially their strengths and weaknesses in comparison to the standard semantics of these two nonmonotonic KR formalisms.</a>
<a href="#22" id="22">Additionally, in the same way we defined several semantics for normal logic programs (conflict-free, admissible, naive, stage).</a>
<a href="#23" id="23">In order to determine whether these semantics are new, it might be a good starting point to compare them to the semantics discussed by Eiter et al. [16].</a>
<a href="#24" id="24">Finally, it is of course in order to perform an analysis of the computational complexity of the newly introduced ADF semantics.</a>
</body>
</html>