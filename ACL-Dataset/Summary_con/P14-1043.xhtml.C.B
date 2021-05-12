<html>
 <head>
  <meta content="SENT_NUM:7, WORD_NUM:177" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   This paper proposes a generalized training framework of semi-supervised dependency parsing based on ambiguous labelings.
  </a>
  <a href="#1" id="1">
   For each unlabeled sentence, we combine the 1-best parse trees of several diverse parsers to compose ambiguous labelings, represented by a parse forest.
  </a>
  <a href="#2" id="2">
   The training objective is to maximize the mixed likelihood of both the labeled data and the auto-parsed unlabeled data with ambiguous labelings.
  </a>
  <a href="#3" id="3">
   Experiments show that our framework can make better use of the unlabeled data, especially those with divergent outputs from different parsers, than traditional tri-training.
  </a>
  <a href="#4" id="4">
   Detailed analysis demonstrates the effectiveness of our approach.
  </a>
  <a href="#5" id="5">
   Specifically, we find that our approach is very effective when using divergent parsers such as the generative parser, and it is also helpful to properly balance the size and oracle accuracy of the parse forest of the unlabeled data.
  </a>
  <a href="#6" id="6">
   For future work, among other possible extensions, we would like to see how our approach performs when employing more diverse parsers to compose the parse forest of higher quality for the unlabeled data, such as the easy-first non-directional dependency parser [] and other constituent parsers [].
  </a>
 </body>
</html>