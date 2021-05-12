<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:531">
</head>
<body bgcolor="white">
<a href="#0" id="0">Properties of entities in a relational domain can depend on complex combinatorial count-of-count features characterizing the entitiesʼ relational neighborhood.</a>
<a href="#1" id="1">Examples of properties that are directly defined in terms of count-of-count features are the h-index of an author, and certain relevance measures widely used in information retrieval.</a>
<a href="#2" id="2">Type Extension Trees are a simple, but highly expressive representation language for count-of-count features.</a>
<a href="#3" id="3">In this article we have presented a method for learning Type Extension Trees in supervised learning settings as a means of discovering count-of-count features that are informative for the prediction of a class label.</a>
<a href="#4" id="4">Most existing frameworks for statistical relational learning either are only based on simpler, “flat”, count features, or their use of count-of-count features is only implicit in the specification of conditional probability distributions, and does not include an interpretable representation of the underlying features.</a>
<a href="#5" id="5">Examples of frameworks of the first kind are Markov Logic Networks [36] (cf.</a>
<a href="#6" id="6">Example 2.10), and systems providing simple aggregation operators [1], [13], [18].</a>
<a href="#7" id="7">Examples of frameworks of the second kind are probabilistic relational models that allow the specification of conditional probability distribution using nested combination functions [16], [30].</a>
<a href="#8" id="8">Kernel methods can be also applied to (implicitly) extract features from relational data.</a>
<a href="#9" id="9">The general framework of convolution kernels [12] has originated a wealth of different approaches for defining the similarity between structured objects (see e.g. [45] and references therein).</a>
<a href="#10" id="10">Features defined by these kernels essentially count fragments or substructures, but not counts of counts.</a>
<a href="#11" id="11">In most cases, these methods aim to develop a suitable representation of structured data for subsequent learning, not to discover features.</a>
<a href="#12" id="12">There are previous works, however, where the feature space itself is learned from relational data [23], [29] and is interpretable in terms of definite clauses.</a>
<a href="#13" id="13">In most of these previous works relational feature construction is an integral part of a particular learning paradigm.</a>
<a href="#14" id="14">Relational features in their own right have previously been investigated in [32].</a>
<a href="#15" id="15">Here a systematic view of aggregation-based features at different levels of complexity is developed.</a>
<a href="#16" id="16">However, the focus still is on aggregation over a single level of relational dependencies.</a>
<a href="#17" id="17">Discovered TET features can be used in a variety of classification models, and could be integrated into existing models such as relational probability trees [31], or inductive logic programming systems, for which simpler types of count features have already been used [1].</a>
<a href="#18" id="18">In this paper we have considered two approaches for directly augmenting TET features into full prediction models.</a>
<a href="#19" id="19">The simple discriminant function is fast to learn and evaluate, but only makes limited use of the count-of-count information provided by a TET feature value.</a>
<a href="#20" id="20">We have therefore also introduced a metric on TET values defined by a recursive application of the Wasserstein–Kantorovich metric.</a>
<a href="#21" id="21">With this metric, distance-based methods for supervised or unsupervised learning become directly applicable.</a>
<a href="#22" id="22">Our experiments have shown that our TET learning algorithm is able to discover non-trivial and interpretable count-of-count features.</a>
<a href="#23" id="23">A comparison of the classification accuracies achieved with the discriminant function model and k-nearest neighbor classification based on the TET metric indicates that TET features learned using the discriminant function can also support other classification models, and that a model that exploits the complex count-of-count information outperforms models only using flat counts.</a>
</body>
</html>