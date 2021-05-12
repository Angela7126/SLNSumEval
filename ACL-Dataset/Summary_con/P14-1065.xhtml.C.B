<html>
 <head>
  <meta content="SENT_NUM:13, WORD_NUM:298" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper we have shown that discourse structure can be used to improve automatic MT evaluation.
  </a>
  <a href="#1" id="1">
   First, we defined two simple discourse-aware similarity metrics (lexicalized and un-lexicalized), which use the all-subtree kernel to compute similarity between discourse parse trees in accordance with the Rhetorical Structure Theory.
  </a>
  <a href="#2" id="2">
   Then, after extensive experimentation on WMT12 and WMT11 data, we showed that a variety of existing evaluation metrics can benefit from our discourse-based metrics, both at the segment- and the system-level, especially when the discourse information is incorporated in an informed way (i.e., using supervised tuning.
  </a>
  <a href="#3" id="3">
   Our results show that discourse-based metrics can improve the state-of-the-art MT metrics, by increasing correlation with human judgments, even when only sentence-level discourse information is used.
  </a>
  <a href="#4" id="4">
   Addressing discourse-level phenomena in MT is a relatively new research direction.
  </a>
  <a href="#5" id="5">
   Yet, many of the ongoing efforts have been moderately successful according to traditional evaluation metrics.
  </a>
  <a href="#6" id="6">
   There is a consensus in the MT community that more discourse-aware metrics need to be proposed for this area to move forward.
  </a>
  <a href="#7" id="7">
   We believe this work is a valuable contribution towards this longer-term goal.
  </a>
  <a href="#8" id="8">
   The tuned combined metrics tested in this paper are just an initial proposal, i.e., a simple adjustment of the relative weights for the individual metrics in a linear combination.
  </a>
  <a href="#9" id="9">
   In the future, we plan to work on integrated representations of syntactic, semantic and discourse-based structures, which would allow us to train evaluation metrics based on more fine-grained features.
  </a>
  <a href="#10" id="10">
   Additionally, we propose to use the discourse information for MT in two different ways.
  </a>
  <a href="#11" id="11">
   First, at the sentence-level, we can use discourse information to re-rank alternative MT hypotheses; this could be applied either for MT parameter tuning, or as a post-processing step for the MT output.
  </a>
  <a href="#12" id="12">
   Second, we propose to move in the direction of using discourse information beyond the sentence-level.
  </a>
 </body>
</html>