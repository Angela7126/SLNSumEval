<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:396">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have studied the three issues of term translation in the context of SMT and proposed three different term translation models to address these issues.</a>
<a href="#1" id="1">The term translation disambiguation model enables the decoder to favor the most suitable domain-specific translations with document-level information for source terms.</a>
<a href="#2" id="2">The term translation consistency model encourages the decoder to translate source terms with a high topic-dependent translation consistency strength into consistent target terms.</a>
<a href="#3" id="3">Finally, the term unithood model rewards hypotheses that translate terms into continuous target strings as a whole unit.</a>
<a href="#4" id="4">We integrate the three models into a hierarchical phrase-based SMT system{sup:7} and evaluate their effectiveness on NIST Chinese–English translation with large-scale training data.</a>
<a href="#5" id="5">Experiment results show that</a>
<a href="#6" id="6">The term translation disambiguation model is able to obtain a substantial improvement of 0.58 BLEU points over the baseline on the test set.</a>
<a href="#7" id="7">The term translation consistency model outperforms the baseline by 0.72 BLEU points.</a>
<a href="#8" id="8">We also observe 1) that topic information improves the model as term translation consistency is topic-sensitive and 2) that modeling how terms are translated consistently in training data is better than counting the number of times that they are translated consistently in a test set.</a>
<a href="#9" id="9">The term unithood model is also better than the baseline by 0.79 BLEU points on the test set.</a>
<a href="#10" id="10">Additionally, we find that document-level topic information cannot improve the model.</a>
<a href="#11" id="11">The combination of the three models can obtain further improvement, which is 0.92 BLEU points over the baseline on the final test set.</a>
<a href="#12" id="12">Our experiments also disclose 1) that the more bilingual terms we extract, the better translation quality will be, 2) and that the LLR method is marginally better than the C-value/NC-value method in the bilingual term extraction and the combination of the two methods achieves the best performance.</a>
<a href="#13" id="13">Our in-depth analyses further validate that the proposed three term translation models are indeed able to improve term translation.</a>
<a href="#14" id="14">As shown in our analysis with translation examples, noises of extracted bilingual terms will guide our models to wrong translations.</a>
<a href="#15" id="15">Therefore, we want to improve the procedure of bilingual term extraction so that we can further improve the performance of our method in the future.</a>
<a href="#16" id="16">Additionally, we also plan to extend our models for the purpose of multilingual text analysis as well as multilingual terminology and ontology construction for specific domains as terms are able to convey concepts of a text or a domain.</a>
</body>
</html>