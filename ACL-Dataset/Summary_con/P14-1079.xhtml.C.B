<html>
 <head>
  <meta content="SENT_NUM:7, WORD_NUM:175" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we contributed two noise-tolerant optimization models 17 17 The source code can be downloaded from https://github.com/nlpgeek/DRMC/tree/master , DRMC-b and DRMC-1, for distantly supervised relation extraction task from a novel perspective.
  </a>
  <a href="#1" id="1">
   Our models are based on matrix completion with low-rank criterion.
  </a>
  <a href="#2" id="2">
   Experiments demonstrated that the low-rank representation of the feature-label matrix can exploit the underlying semantic correlated information for relation classification and is effective to overcome the difficulties incurred by sparse and noisy features and incomplete labels, so that we achieved significant improvements on performance.
  </a>
  <a href="#3" id="3">
   Our proposed models also leave open questions for distantly supervised relation extraction task.
  </a>
  <a href="#4" id="4">
   First, they can not process new coming testing items efficiently, as we have to reconstruct the data matrix containing not only the testing items but also all the training items for relation classification, and compute in iterative fashion again.
  </a>
  <a href="#5" id="5">
   Second, the volume of the datasets we adopt are relatively small.
  </a>
  <a href="#6" id="6">
   For the future work, we plan to improve our models so that they will be capable of incremental learning on large-scale datasets [ 6 ].
  </a>
 </body>
</html>