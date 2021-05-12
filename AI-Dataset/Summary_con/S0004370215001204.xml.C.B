<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:773">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we explored the complexity of computations using FODD and GFODD with min and max aggregation, providing a classification placing them within the polynomial hierarchy, where, roughly speaking, equivalence is one level higher in the hierarchy than evaluation and satisfiability.</a>
<a href="#1" id="1">These results are useful in that they characterize the complexity of the problems solved heuristically by implementations of GFODD systems [15], [17], [18] and can be used to partly motivate or justify the use of these heuristics.</a>
<a href="#2" id="2">For example, the “model checking reductions” of [15] replace equivalence tests with model evaluation on a “representative” set of models, and choosing this set heuristically leads to inference that is correct with respect to these models but otherwise incomplete.</a>
<a href="#3" id="3">Our results here show that this indeed leads to reduction of the complexity of the inference problem so that the loss in accuracy is traded for improved worst case run time.</a>
<a href="#4" id="4">As mentioned above, the proofs in the paper can be used (in simpler form) to show the same complexity results for the corresponding problems in first order logic.</a>
<a href="#5" id="5">To our knowledge the corresponding complexity questions for first order logic, with an explicit bound on model size, have not been studied before.</a>
<a href="#6" id="6">Yet they can be useful in many contexts where such a bound can be given in a practical setting.</a>
<a href="#7" id="7">For example, in such cases existing optimized QBF algorithms can be used for inference in this restricted form of first order logic.</a>
<a href="#8" id="8">There are several important directions for further investigation.</a>
<a href="#9" id="9">The first involves using a richer set of aggregation operators.</a>
<a href="#10" id="10">In particular the definition of GFODDs allows for any function to aggregate values, and functions such as sum, product, and average are both natural and useful for modeling and solving Markov Decision Processes, which have been the main application for FODDs.</a>
<a href="#11" id="11">The work of [18] extends the model checking reductions to GFODDs with average aggregation.</a>
<a href="#12" id="12">Clarifying the complexity of these problems and identifying the best algorithms for them is an important effort for the efficiency of such systems.</a>
<a href="#13" id="13">In this context, it is also interesting to clarify the relationship to query languages in databases that allow for similar aggregations and to formulations of logic with counting that have been developed in the context of database theory [24].</a>
<a href="#14" id="14">Considering this wider family of GFODDs also raises new computational questions beyond the ones explored in this paper.</a>
<a href="#15" id="15">One such question arises from the connection to statistical relational models and specifically to lifted inference in such models (see e.g. [28], [27], [5]).</a>
<a href="#16" id="16">In particular, consider Markov Logic Networks (MLN) [28] that can be seen to define a distribution over interpretations through a log linear probability model, where features of this model are defined by simple first order formula templates.</a>
<a href="#17" id="17">It is easy to show that such templates and their weights can be encoded using a GFODD with product aggregation, and that these can be combined using a variant of the Apply procedure.</a>
<a href="#18" id="18">The main computational question in this context has been to calculate the probability of a query given the MLN model, and the number of objects n in the domain.</a>
<a href="#19" id="19">Let {a mathematical formula}I be the set of interpretations with n objects over the relevant signature.</a>
<a href="#20" id="20">In our case, this question translates to calculating{a mathematical formula} for an appropriate B that combines the query and the MLN model.</a>
<a href="#21" id="21">This is closely related to the approaches that solve this problem via lifted weighted model counting [5].</a>
<a href="#22" id="22">A similarly interesting question would require us to calculate the best I for a particular B{a mathematical formula} In this case, if B captures say profit of some organization, then the computation optimizes the setting so as to maximize profit.</a>
<a href="#23" id="23">Thirdly, we have defined a logic-inspired language but did not define or study any notion of implication.</a>
<a href="#24" id="24">A natural notion of implication with numerical values, related to the one used by [7], is majorization:{a mathematical formula} Efficient algorithms and complexity analysis for these new questions will expand the scope and applicability of GFODDs.</a>
<a href="#25" id="25">Finally, efficient algorithms for model evaluation play an important role in GFODD implementations.</a>
<a href="#26" id="26">The work of [18] provides a generic algorithm inspired by the variable elimination algorithm from probabilistic inference.</a>
<a href="#27" id="27">Several application areas, including databases, AI, and probabilistic inference have shown that more efficient algorithms are possible when the input formula or graph have certain structural properties such as low graph width.</a>
<a href="#28" id="28">We therefore conjecture that similar notions can be developed to provide more efficient evaluation for GFODDs with some structural properties.</a>
<a href="#29" id="29">Coupled with model checking reductions, this can lead to realizations of GFODD systems that combine high expressive power going beyond first order logic with efficient algorithms.</a>
</body>
</html>