<html>
 <head>
  <meta content="SENT_NUM:16, WORD_NUM:358" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper we proposed a method for automatic detection of cognates based on orthographic alignment.
  </a>
  <a href="#1" id="1">
   We employed the Needleman-Wunsch algorithm [ 29 ] for sequence alignment widely-used in computational biology and we used aligned pairs of words to extract rules for lexical changes occurring when words enter new languages.
  </a>
  <a href="#2" id="2">
   We applied our method on an automatically extracted dataset of cognates for four pairs of languages.
  </a>
  <a href="#3" id="3">
   As future work, we plan to extend our method on a few levels.
  </a>
  <a href="#4" id="4">
   In this paper we used a very simple substitution matrix for the alignment algorithm, but the method can be adapted to integrate historical information regarding language evolution.
  </a>
  <a href="#5" id="5">
   The substitution matrix for the alignment algorithm can be customized with language-specific information, in order to reflect the probability of a character to change into another.
  </a>
  <a href="#6" id="6">
   An important achievement in this direction belongs to Delmestri and Cristianini ( 2010 ) , who introduced PAM-like matrices, linguistic-inspired substitution matrices which are based on information regarding orthographic changes.
  </a>
  <a href="#7" id="7">
   We plan to investigate the contribution of using this type of substitution matrices for our method.
  </a>
  <a href="#8" id="8">
   We intend to investigate other approaches to string alignment, such as local alignment [ 33 ] , and other learning algorithms for discriminating between cognates and non-cognates.
  </a>
  <a href="#9" id="9">
   We plan to extend our analysis with more language-specific features, where linguistic knowledge is available.
  </a>
  <a href="#10" id="10">
   First, we intend to use the part of speech as an additional feature.
  </a>
  <a href="#11" id="11">
   We assume that some orthographic changes are dependent on the part of speech of the words.
  </a>
  <a href="#12" id="12">
   Secondly, we want to investigate whether accounting for the common ancestor language influences the results.
  </a>
  <a href="#13" id="13">
   We are interested to find out if the orthographic rules depend on the source language, or if they are rather specific to the target language.
  </a>
  <a href="#14" id="14">
   Finally, we plan to make a performance comparison on cognate pairs versus word-etymon pairs and to investigate false friends [ 27 ].
  </a>
  <a href="#15" id="15">
   We further intend to adapt our method for cognate detection to a closely related task, namely cognate production, i.e.,, given an input word w , a related language L and a set of learned rules for orthographic changes, to produce the cognate pair of w in L.
  </a>
 </body>
</html>