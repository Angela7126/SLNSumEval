<html>
 <head>
  <meta content="SENT_NUM:9, WORD_NUM:143" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   Accurate scoring of syntactic structures such as head-modifier arcs in dependency parsing typically requires rich, high-dimensional feature representations.
  </a>
  <a href="#1" id="1">
   We introduce a low-rank factorization method that enables to map high dimensional feature vectors into low dimensional representations.
  </a>
  <a href="#2" id="2">
   Our method maintains the parameters as a low-rank tensor to obtain low dimensional representations of words in their syntactic roles, and to leverage modularity in the tensor for easy training with online algorithms.
  </a>
  <a href="#3" id="3">
   We implement the approach on first-order to third-order dependency parsing.
  </a>
  <a href="#4" id="4">
   Our parser outperforms the Turbo and MST parsers across 14 languages.
  </a>
  <a href="#5" id="5">
   Future work involves extending the tensor component to capture higher-order structures.
  </a>
  <a href="#6" id="6">
   In particular, we would consider second-order structures such as grandparent-head-modifier by increasing the dimensionality of the tensor.
  </a>
  <a href="#7" id="7">
   This tensor will accordingly be a four or five-way array.
  </a>
  <a href="#8" id="8">
   The online update algorithm remains applicable since each dimension is optimized in an alternating fashion.
  </a>
 </body>
</html>