<html>
 <head>
  <meta content="SENT_NUM:13, WORD_NUM:452" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   This paper showed that the word segmentation accuracy of a state-of-the-art Adaptor Grammar model is significantly improved by extending it so that it explicitly models some properties of function words.
  </a>
  <a href="#1" id="1">
   We also showed how Bayesian model selection can be used to identify that function words appear on the left periphery of phrases in English, even though the input to the model only consists of an unsegmented sequence of phones.
  </a>
  <a href="#2" id="2">
   Of course this work only scratches the surface in terms of investigating the role of function words in language acquisition.
  </a>
  <a href="#3" id="3">
   It would clearly be very interesting to examine the performance of these models on other corpora of child-directed English, as well as on corpora of child-directed speech in other languages.
  </a>
  <a href="#4" id="4">
   Our evaluation focused on word-segmentation, but we could also evaluate the effect that modelling function words has on other aspects of the model, such as its ability to learn syllable structure.
  </a>
  <a href="#5" id="5">
   The models of function words we investigated here only capture two of the 7 linguistic properties of function words identified in section 1 (i.e.,, that function words tend to be monosyllabic, and that they tend to appear phrase-peripherally), so it would be interesting to develop and explore models that capture other linguistic properties of function words.
  </a>
  <a href="#6" id="6">
   For example, following the suggestion by that human learners use frequency cues to identify function words, it might be interesting to develop computational models that do the same thing.
  </a>
  <a href="#7" id="7">
   In an Adaptor Grammar the frequency distribution of function words might be modelled by specifying the prior for the Pitman-Yor Process parameters associated with the function words adapted nonterminals so that it prefers to generate a small number of high-frequency items.
  </a>
  <a href="#8" id="8">
   It should also be possible to develop models which capture the fact that function words tend not to be topic-specific and show how Adaptor Grammars can model the association between words and non-linguistic topics ; perhaps these models could be extended to capture some of the semantic properties of function words.
  </a>
  <a href="#9" id="9">
   It would also be interesting to further explore the extent to which Bayesian model selection is a useful approach to linguistic parameter setting .
  </a>
  <a href="#10" id="10">
   In order to do this it is imperative to develop better methods than the problematic Harmonic Mean estimator used here for calculating the evidence (i.e.,, the marginal probability of the data) that can handle the combination of discrete and continuous hidden structure that occur in computational linguistic models.
  </a>
  <a href="#11" id="11">
   As well as substantially improving the accuracy of unsupervised word segmentation, this work is interesting because it suggests a connection between unsupervised word segmentation and the induction of syntactic structure.
  </a>
  <a href="#12" id="12">
   It is reasonable to expect that hierarchical non-parametric Bayesian models such as Adaptor Grammars may be useful tools for exploring such a connection.
  </a>
 </body>
</html>