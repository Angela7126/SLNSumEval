<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:172">
</head>
<body bgcolor="white">
<a href="#0" id="0">In Table 7 , we compare this to using a standard network (with two hidden layers), as well as a pre-computed neural network.</a>
<a href="#1" id="1">However, note that there are only 3 possible positions for each target word, and 11 for each source word.</a>
<a href="#2" id="2">Our baseline decoder contains a large and powerful set of features, which include:</a>
<a href="#3" id="3">Intuitively, we want to define 𝒮i as the window that is most relevant to ti .</a>
<a href="#4" id="4">However, additive results are not presented.</a>
<a href="#5" id="5">[noitemsep] •</a>
<a href="#6" id="6">He obtains +0.3 BLEU improvement (24.8 vs. 25.1).</a>
<a href="#7" id="7">The input vocabulary contains 16,000 source words and 16,000 target words, while the output vocabulary contains 32,000 target words.</a>
<a href="#8" id="8">Therefore, for every word in the vocabulary, and for each position, we can pre-compute the dot product between the word embedding and the first hidden layer.</a>
<a href="#9" id="9">Increasing the sizes beyond the default NNJM has almost no effect (102%).</a>
<a href="#10" id="10">A number of recent papers have proposed methods for creating neural network translation/joint models, but nearly all of these works have obtained much smaller BLEU improvements than ours.</a>
</body>
</html>