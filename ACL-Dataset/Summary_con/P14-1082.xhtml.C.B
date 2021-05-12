<html>
 <head>
  <meta content="SENT_NUM:23, WORD_NUM:545" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this study we have shown the feasibility of a classifier-based translation assistance system in which L1 fragments are translated in an L2 context, in which the classifier experts are built individually per word or phrase.
  </a>
  <a href="#1" id="1">
   We have shown that such a translation assistance system scores both above a context-insensitive baseline, as well as an L2 language model baseline.
  </a>
  <a href="#2" id="2">
   Furthermore, we found that combining this cross-language context-sensitive technique with an L2 language model boosts results further.
  </a>
  <a href="#3" id="3">
   The presence of a one-word right-hand side context proves crucial for good results, which has implications for practical translation assistance application that translate as soon as the user finishes an L1 fragment.
  </a>
  <a href="#4" id="4">
   Revisiting the translation when right context becomes available would be advisable.
  </a>
  <a href="#5" id="5">
   We tested various configurations and conclude that small context sizes work better than larger ones.
  </a>
  <a href="#6" id="6">
   Automated configuration selection had positive results, yet the system with context size one and an L2 language model component often produces the best results.
  </a>
  <a href="#7" id="7">
   In static configurations, the failure of a wider context window to be more succesful may be attributed to the increased sparsity that comes from such an expansion.
  </a>
  <a href="#8" id="8">
   The idea of a comprehensive translation assistance system may extend beyond the translation of L1 fragments in an L2 context.
  </a>
  <a href="#9" id="9">
   There are more NLP components that might play a role if such a system were to find practical application.
  </a>
  <a href="#10" id="10">
   Word completion or predictive editing (in combination with error correction) would for instance seem an indispensable part of such a system, and can be implemented alongside the technique proposed in this study.
  </a>
  <a href="#11" id="11">
   A point of more practically-oriented future research is to see how feasible such combinations are and what techniques can be used.
  </a>
  <a href="#12" id="12">
   An application of our idea outside the area of translation assistance is post-correction of the output of some MT systems that, as a last-resort heuristic, copy source words or phrases into their output, producing precisely the kind of input our system is trained on.
  </a>
  <a href="#13" id="13">
   Our classification-based approach may be able to resolve some of these cases operating as an add-on to a regular MT system or as a independent post-correction system.
  </a>
  <a href="#14" id="14">
   Our system allows L1 fragments to be of arbitrary length.
  </a>
  <a href="#15" id="15">
   If a fragment was not seen during training stage, and is therefore not covered by a classifier expert, then the system will be unable to translate it.
  </a>
  <a href="#16" id="16">
   Nevertheless, if a longer L1 fragment can be decomposed into subfragments that are known, then some recombination of the translations of said sub-fragments may be a good translation for the whole.
  </a>
  <a href="#17" id="17">
   We are currently exploring this line of investigation, in which the gap with MT narrows further.
  </a>
  <a href="#18" id="18">
   Finally, an important line of future research is the creation of a more representative test set.
  </a>
  <a href="#19" id="19">
   Lacking an interactive system that actually does what we emulate, we hypothesise that good approximations would be to use gap exercises, or cloze tests, that test specific aspects difficulties in language learning.
  </a>
  <a href="#20" id="20">
   Similarly, we may use L2 learner corpora with annotations of code-switching points or errors.
  </a>
  <a href="#21" id="21">
   Here we then assume that places where L2 errors occur may be indicative of places where L2 learners are in some trouble, and might want to fall back to generating L1.
  </a>
  <a href="#22" id="22">
   By then manually translating gaps or such problematic fragments into L1 we hope to establish a more realistic test set.
  </a>
 </body>
</html>