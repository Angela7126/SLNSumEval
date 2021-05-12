<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:444">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article we presented Nasari, a novel technique for the representation of concepts and named entities in arbitrary languages.</a>
<a href="#1" id="1">Our approach combines the structural knowledge from semantic networks with the statistical information derived from text corpora for effective representation of millions of BabelNet synsets, including WordNet nominal synsets and all Wikipedia pages.</a>
<a href="#2" id="2">We evaluated our representations in a wide range of NLP tasks and applications: semantic similarity, sense clustering, Word Sense Disambiguation, and domain labeling.</a>
<a href="#3" id="3">We reported state-of-the-art performance on several datasets across these tasks and in different languages.</a>
<a href="#4" id="4">Three type of sense representation were put forward: two explicit vector representations (unified and lexical), in which vector dimensions are interpretable, and a latent embedding-based representation.</a>
<a href="#5" id="5">Each representation has its own advantages and limitations.</a>
<a href="#6" id="6">In general, a combination of lexical and unified vectors led to the most reliable results in the semantic similarity and sense clustering experiments (Sections 6 and 7).</a>
<a href="#7" id="7">Among the three representations, the lexical representation (i.e., Nasarilexical) obtained the best performance in monolingual settings.</a>
<a href="#8" id="8">However, although the lexical vectors are sparse and hence computationally faster to process, their dimensionality is high and equal to the size of the vocabulary.</a>
<a href="#9" id="9">In contrast, our embedded representation (i.e., Nasariembed) has a fixed low number of latent dimensions.</a>
<a href="#10" id="10">Additionally, embedded synset vectors share the same space with the word embeddings used as input.</a>
<a href="#11" id="11">As regards our unified representation (i.e., Nasariunified), not only does it provide an effective way for representing word senses in different languages, but, thanks to its unified semantic space, it also enables a direct comparison of different representations across languages.</a>
<a href="#12" id="12">In addition to being multilingual, Nasari improves over the existing techniques by providing a high coverage for millions of concepts and named entities defined in the BabelNet sense inventory.</a>
<a href="#13" id="13">Release We are releasing the complete set of representations obtained using our technique for five different languages (English, Spanish, French, German and Italian) at http://lcl.uniroma1.it/nasari, and we plan to generate representations for more languages in the near future.</a>
<a href="#14" id="14">We also provide a Python script for the computation of lexical specificity.</a>
<a href="#15" id="15">Finally, domain labels are included in the BabelNet 3.5 release version{sup:47} and the gold standard domain-labeled datasets used for our experiments (Section 8.1.1) are provided in the website.</a>
<a href="#16" id="16">Future work As future work we plan to pursue three main directions.</a>
<a href="#17" id="17">Firstly, we aim to compute a global representation for each concept by exploiting the statistical information obtained from multiple languages.</a>
<a href="#18" id="18">Secondly, we plan to develop a framework for a more meaningful combination of our representations in a supervised system for improved joint WSD and Entity Linking.</a>
<a href="#19" id="19">Thirdly, we plan to integrate our multilingual semantic representations into different end-user applications, such as Machine Translation.</a>
</body>
</html>