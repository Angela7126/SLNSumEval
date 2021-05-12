<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:175">
</head>
<body bgcolor="white">
<a href="#0" id="0">Our work achieves comparable accuracy with , although they adopt the higher-order model of .</a>
<a href="#1" id="1">Different from traditional self/co/tri-training which only use 1-best parse trees on unlabeled data, our approach adopts ambiguous labelings, represented by parse forest, as gold-standard for unlabeled sentences.</a>
<a href="#2" id="2">We suspect the reason is that the model is likely to distribute the probability mass to these parse trees produced by itself instead of those by Berkeley Parser or ZPar under this setting.</a>
<a href="#3" id="3">Instead, we can use the classic inside-outside algorithm to efficiently compute the model expectations within O⁢(n3) time complexity, where n is the input sentence length.</a>
<a href="#4" id="4">For English, we follow the popular practice to split data into training (sections 2-21), development (section 22), and test (section 23).</a>
<a href="#5" id="5">Therefore, we can conclude that co-training helps dependency parsing, especially when using a more divergent parser .</a>
<a href="#6" id="6">∂⁡ℒ⁢(𝒟′;𝐰)∂⁡𝐰=∑i=1M(∑𝐝′∈𝒱ip~(𝐝′|𝐮i,𝒱i;𝐰)𝐟(𝐮i,𝐝′)-∑𝐝′∈𝒴⁢(𝐮i)p(𝐝′|𝐮i;𝐰)𝐟(𝐮i,𝐝′)) (3) where p~(𝐝′|𝐮i,𝒱i;𝐰) is the probability of 𝐝′ under the space constrained by the parse forest 𝒱i .</a>
<a href="#7" id="7">show that SGD achieves optimal test performance with far fewer iterations than other optimization routines such as L-BFGS.</a>
</body>
</html>