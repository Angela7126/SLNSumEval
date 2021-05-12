<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:165">
</head>
<body bgcolor="white">
<a href="#0" id="0">Figure 6 shows that our approaches consistently outperform the baseline and the state-of-the-art methods with diverse feature sparsity degrees.</a>
<a href="#1" id="1">We thus define 𝐙=𝐙*+𝐄, where 𝐙* as the underlying low-rank matrix 𝐙*=[X*Y*]=[Xt⁢r⁢a⁢i⁢n*Yt⁢r⁢a⁢i⁢n*Xt⁢e⁢s⁢t*Yt⁢e⁢s⁢t*], and E is the error matrix 𝐄=[EXt⁢r⁢a⁢i⁢nEYt⁢r⁢a⁢i⁢nEXt⁢e⁢s⁢t0].</a>
<a href="#2" id="2">Shrinkage step:</a>
<a href="#3" id="3">We extract diverse textual features from all those relation mentions and combine them into a rich feature vector labeled by the relation names ( President-of and Born-in ) to produce a weak training corpus for relation classification.</a>
<a href="#4" id="4">C(u,v)=-logPr(u|v)=log(1+e-u⁢v),</a>
<a href="#5" id="5">To tolerate the noise entries in the error matrix 𝐄 , we minimize the cost functions Cx and Cy for features and labels respectively, rather than using the hard constraints in Formula (2).</a>
<a href="#6" id="6">We relax the feature filtering threshold ( θ=4,3,2 ) in Surdeanu et al.’s [24] open source program to generate more sparse features from NYT’10 dataset.</a>
<a href="#7" id="7">We use the gradient descents 𝐀=𝐙-τz⁢g⁢(𝐙) and 𝐛=𝐛-τb⁢g⁢(𝐛) to gradually find the global minima of the cost function terms in Formula (3), where τz and τb are step sizes.</a>
</body>
</html>