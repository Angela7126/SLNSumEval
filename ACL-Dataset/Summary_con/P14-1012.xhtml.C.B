<html>
 <head>
  <meta content="SENT_NUM:9, WORD_NUM:274" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, instead of designing new features based on intuition, linguistic knowledge and domain, we have learned new features using the DAE for the phrase-based translation model.
  </a>
  <a href="#1" id="1">
   Using the unsupervised pre-trained DBN to initialize DAE s parameters and using the input original phrase features as the teacher for semi-supervised back-propagation, our semi-supervised DAE features are more effective and stable than the unsupervised DBN features [ Maskey and Zhou2012 ].
  </a>
  <a href="#2" id="2">
   Moreover, to further improve the performance, we introduce some simple but effective features as the input features for feature learning.
  </a>
  <a href="#3" id="3">
   Lastly, to learn high dimensional feature representation, we introduce a natural horizontal composition of two DAEs for large hidden layers feature learning.
  </a>
  <a href="#4" id="4">
   On two Chinese-English translation tasks, the results demonstrate that our solutions solve the two aforementioned shortcomings successfully.
  </a>
  <a href="#5" id="5">
   Firstly, our DAE features obtain statistically significant improvements of 1.34/2.45 (IWSLT) and 0.82/1.52 (NIST) BLEU points over the DBN features and the baseline features, respectively.
  </a>
  <a href="#6" id="6">
   Secondly, compared with the baseline phrase features X 1 , our introduced input original phrase features X significantly improve the performance of not only our DAE features but also the DBN features.
  </a>
  <a href="#7" id="7">
   The results also demonstrate that DNN (DAE and HCDAE) features are complementary to the original features for SMT, and adding them together obtain statistically significant improvements of 3.16 (IWSLT) and 2.06 (NIST) BLEU points over the baseline features.
  </a>
  <a href="#8" id="8">
   Compared with the original features, DNN (DAE and HCDAE) features are learned from the non-linear combination of the original features, they strong capture high-order correlations between the activities of the original features, and we believe this deep learning paradigm induces the original features to further reach their potential for SMT.
  </a>
 </body>
</html>