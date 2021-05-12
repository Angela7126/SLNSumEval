<html>
 <head>
  <meta content="SENT_NUM:8, WORD_NUM:146" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we explored an active learning approach to improve data annotation quality for classification tasks.
  </a>
  <a href="#1" id="1">
   Instead of training the active learner using computationally expensive techniques (e.g.,, SVM-TF), we used a novel non-linear distribution spreading algorithm.
  </a>
  <a href="#2" id="2">
   This algorithm first weighs the features using the Delta-IDF technique, and then non-linearly spreads out the distribution of the feature scores to enhance the model s ability to discriminate at the feature level.
  </a>
  <a href="#3" id="3">
   The evaluation shows that our algorithm has the following advantages.
  </a>
  <a href="#4" id="4">
   1) It intelligently ordered the data points for annotators to annotate the most likely errors first.
  </a>
  <a href="#5" id="5">
   The accuracy was at least comparable with computationally expensive baselines (e.g., SVM-TF.
  </a>
  <a href="#6" id="6">
   2) The algorithm trained and ran much faster than SVM-TF, allowing annotators to finish more annotations than competitors.
  </a>
  <a href="#7" id="7">
   3) The annotation process improved the dataset quality by positively impacting the accuracy of classifiers that were built upon it.
  </a>
 </body>
</html>