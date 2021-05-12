<html>
 <head>
  <meta content="SENT_NUM:9, WORD_NUM:304" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we have shown that while using parse accuracy in a simple reranking strategy for self-monitoring fails to improve BLEU scores over a state-of-the-art averaged perceptron realization ranking model, it is possible to significantly increase BLEU scores using an SVM ranker that combines the realizer s model score together with features from multiple parsers, including ones designed to make the ranker more robust to parsing mistakes that human readers would be unlikely to make.
  </a>
  <a href="#1" id="1">
   Additionally, via a targeted manual analysis, we showed that the SVM reranker frequently manages to avoid egregious errors involving vicious ambiguities, of the kind that would mislead human readers as to the intended meaning.
  </a>
  <a href="#2" id="2">
   As noted in Reiter s [ 30 ] survey, many NLG systems use surface realizers as off-the-shelf components.
  </a>
  <a href="#3" id="3">
   In this paper, we have focused on broad coverage surface realization using widely-available PTB data where there are many sentences of varying complexity with gold-standard annotations following the common assumption that experiments with broad coverage realization are (or eventually will be) relevant for NLG applications.
  </a>
  <a href="#4" id="4">
   Of course, the kinds of ambiguity that can be problematic in news text may or may not be the same as the ones encountered in particular applications.
  </a>
  <a href="#5" id="5">
   Moreover, for certain applications (e.g., ones with medical or legal implications), it may be better to err on the side of ambiguity avoidance, even at some expense to fluency, thereby requiring training data reflecting the desired trade-off to adapt the methods described here.
  </a>
  <a href="#6" id="6">
   We leave these application-centered issues for investigation in future work.
  </a>
  <a href="#7" id="7">
   The current approach is primarily suitable for offline use, for example in report generation where there are no real-time interaction demands.
  </a>
  <a href="#8" id="8">
   In future work, we also plan to investigate ways that self-monitoring might be implemented more efficiently as a combined process, rather than running independent parsers as a post-process following realization.
  </a>
 </body>
</html>