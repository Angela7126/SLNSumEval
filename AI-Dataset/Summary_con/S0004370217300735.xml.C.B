<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:265">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have presented a novel method called HLTA for hierarchical topic detection.</a>
<a href="#1" id="1">The idea is to model patterns of word co-occurrence and co-occurrence of those patterns using a hierarchical latent tree model.</a>
<a href="#2" id="2">Each latent variable in an HLTM represents a soft partition of documents and the document clusters in the partitions are interpreted as topics.</a>
<a href="#3" id="3">Each topic is characterized using the words that occur with high probability in documents belonging to the topic and occur with low probability in documents not belonging to the topic.</a>
<a href="#4" id="4">Progressive EM is used to accelerate parameter learning for intermediate models created during model construction, and stepwise EM is used to accelerate parameter learning for the final model.</a>
<a href="#5" id="5">HLTA differs fundamentally from the LDA-based methods for hierarchical topic detection.</a>
<a href="#6" id="6">While both approaches define a probability distribution over documents, they use different types of observed and latent variables.</a>
<a href="#7" id="7">HLTA involves both structure learning and parameter learning, while the LDA-based methods involve only parameter learning.</a>
<a href="#8" id="8">The notions of topics and topic hierarchies are also different.</a>
<a href="#9" id="9">Empirical results show that HLTA outperforms the LDA-based methods in terms of overall model fit and quality of topics/topic hierarchies, while takes no more time than the latter.</a>
<a href="#10" id="10">HLTA treats words as binary variables and each word is allowed to appear in only one branch of a hierarchy.</a>
<a href="#11" id="11">For future work, it would be interesting to extend HLTA so that it can handle count data and that a word is allowed to appear in multiple branches of the hierarchy.</a>
<a href="#12" id="12">Another direction is to further scale up HLTA via distributed computing and by other means.</a>
</body>
</html>