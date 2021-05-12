<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:377">
</head>
<body bgcolor="white">
<a href="#0" id="0">This is the first study to use the semantics underlying objects to enhance tensor factorization accuracy.</a>
<a href="#1" id="1">Semantic sensitive tensor factorization (SSTF) is critical to using semantics to analyze human activities in detail, a key AI goal.</a>
<a href="#2" id="2">It creates semantically enhanced tensors by assessing sparsely observed objects and factorizes the tensors simultaneously in the BPTF framework.</a>
<a href="#3" id="3">Experiments showed that SSTF is up to 12% more accurate than current methods and can support many applications.</a>
<a href="#4" id="4">We are now applying SSTF to link prediction in social networks (e.g. predicting the frequency of future communications among users).</a>
<a href="#5" id="5">Accordingly, we are applying our idea to VNTF, as described in the evaluation section, because the frequency of communications among users often follows an exponential family distribution.</a>
<a href="#6" id="6">Another interesting direction for future work is predicting user activities among cross-domain applications such as music and movie rating services.</a>
<a href="#7" id="7">We think our ideas have potential for cross-domain analysis because they can use semantic knowledge in the format of LOD shared among several service domains.</a>
<a href="#8" id="8">A third interesting direction is development of methods that handle more detailed semantic knowledge than simple vocabularies/taxonomies.</a>
<a href="#9" id="9">In the current study which follows the previous paper [1], we think the “genre” relationships seemed to be useful for solving the sparsity problem caused by the sparse item set.</a>
<a href="#10" id="10">Thus, we used this type of semantic relationship as a first step to solving the sparsity problem in tensor factorization.</a>
<a href="#11" id="11">However, that there are many other useful relationships between different classes in the ontologies.</a>
<a href="#12" id="12">Actually, some of those were heuristically selected in our conference paper [16] (e.g. values of instance properties such as “directedBy” and “actedBy” in the movie ontology).</a>
<a href="#13" id="13">They improved the prediction accuracy, because they reflected users' interests in the item objects.</a>
<a href="#14" id="14">We also think that there are many useless relationships (e.g. “<http://dbpedia.org/ontology/timeZone>” and “<http://dbpedia.org/ontology/spouse>”) that usually do not reflect users' interests in the item objects.</a>
<a href="#15" id="15">Developing a method that automatically selects useful relationships and incorporates semantics from them would improve the prediction accuracy and be an interesting direction of future work.</a>
<a href="#16" id="16">Furthermore, we are interested in improving the model design that reflects the merge strategy of object features and the features of its classes in Eq.</a>
<a href="#17" id="17">(2) more naturally in the way that samples features updated with semantic biases from the posteriors.</a>
</body>
</html>