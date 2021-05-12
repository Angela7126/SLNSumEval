<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:302">
</head>
<body bgcolor="white">
<a href="#0" id="0">Fig. 12 (top) shows that the algorithm was not very sensitive to the number of nearest neighbors (#nn).</a>
<a href="#1" id="1">Algorithm evaluation</a>
<a href="#2" id="2">Finally, most of the prior work in feature labeling evaluated algorithms under ideal conditions, such as feature labels obtained from an oracle [2], [33].</a>
<a href="#3" id="3">Fig. 8 and Table 4 depict the results of adding 10 oracle feature labels per class to the semi-supervised feature labeling algorithms.</a>
<a href="#4" id="4">{a mathematical formula} Putting these pieces together, we now have a distance function that incorporates the feature labels into LWLR.</a>
<a href="#5" id="5">Finally, note that 40% of participantsʼ feature choices were not known to the algorithm previously, as rows 2–5 in Table 3 show.</a>
<a href="#6" id="6">Semi-supervised learning (without feature labeling), on the other hand, resulted in worse performance than the baseline algorithm for four datasets (ModApte, RCV1, Industry sectors and WebKb).</a>
<a href="#7" id="7">Oracle study: supervised learning</a>
<a href="#8" id="8">The majority of the work in feature labeling took a semi-supervised approach.</a>
<a href="#9" id="9">This resulted in 40, 40, 50, 70, 30, and 20 oracle feature labels for 20 Newsgroups, ModApte, RCV1, Industry sectors, WebKb, and Movie review respectively.</a>
<a href="#10" id="10">We can describe GE as trying to maximize a score function S between a modelʼs expectation of {a mathematical formula}f(X) and a target value {a mathematical formula}f˜, as shown below:{a mathematical formula}</a>
<a href="#11" id="11">Apart from this, there are two other issues with the LWLR-SS-FL algorithm that need to be addressed in future work.</a>
<a href="#12" id="12">The class-irrelevant feature contribution refers to the sum of values of all class-irrelevant features in {a mathematical formula}xq.</a>
<a href="#13" id="13">Oracle study: semi-supervised learning</a>
<a href="#14" id="14">The participants were chosen to represent extreme conditions, one having highest, one having average, and one having lowest gains in macro-F1.</a>
<a href="#15" id="15">Hence, the label similarity component of the distance function is defined as:{a mathematical formula} The complete distance function now becomes:{a mathematical formula} The above function could turn out negative in some cases.</a>
</body>
</html>