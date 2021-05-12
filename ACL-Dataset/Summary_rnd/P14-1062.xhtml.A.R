<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:151">
</head>
<body bgcolor="white">
<a href="#0" id="0">The feature graph induced by the network is able to capture word relations of varying size.</a>
<a href="#1" id="1">Given an input sentence, to obtain the first layer of the DCNN we take the embedding 𝐰i∈ℝd for each word in the sentence and construct the sentence matrix 𝐬∈ℝd×s as in Eq.</a>
<a href="#2" id="2">Subsequent layers also have multiple feature maps computed by convolving filters with all the maps from the layer below.</a>
<a href="#3" id="3">We begin by specifying aspects of the implementation and the training of the network.</a>
<a href="#4" id="4">A convolutional layer in the network is obtained by convolving a matrix of weights 𝐦∈ℝd×m with the matrix of activations at the layer below.</a>
<a href="#5" id="5">The outline of the paper is as follows.</a>
<a href="#6" id="6">The network is topped by a softmax classification layer.</a>
<a href="#7" id="7">If we temporarily ignore the pooling layer, we may state how one computes each d -dimensional column a in the matrix 𝐚 resulting after the convolutional and non-linear layers.</a>
</body>
</html>