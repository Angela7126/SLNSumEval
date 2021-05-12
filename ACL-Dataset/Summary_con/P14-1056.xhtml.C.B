<html>
 <head>
  <meta content="SENT_NUM:7, WORD_NUM:171" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We introduce a novel modification to the standard projected subgradient dual decomposition algorithm for performing MAP inference subject to hard constraints to one for performing MAP in the presence of soft constraints.
  </a>
  <a href="#1" id="1">
   In addition, we offer an easy-to-implement procedure for learning the penalties on soft constraints.
  </a>
  <a href="#2" id="2">
   This method drives many penalties to zero, which allows users to automatically discover discriminative constraints from large families of candidates.
  </a>
  <a href="#3" id="3">
   We show via experiments on a recent substantial dataset that using soft constraints, and selecting which constraints to use with our penalty-learning procedure, can lead to significant gains in accuracy.
  </a>
  <a href="#4" id="4">
   We achieve a 17% gain in accuracy over a chain-structured CRF model, while only needing to run MAP in the CRF an average of less than 2 times per example.
  </a>
  <a href="#5" id="5">
   This minor incremental cost over Viterbi, plus the fact that we obtain certificates of optimality on 100% of our test examples in practice, suggests the usefulness of our algorithm for large-scale applications.
  </a>
  <a href="#6" id="6">
   We encourage further use of our Soft-DD procedure for other structured prediction problems.
  </a>
 </body>
</html>