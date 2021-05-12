<html>
 <head>
  <meta content="SENT_NUM:24, WORD_NUM:475" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this work, we approach the problem of semantic parsing from a paraphrasing viewpoint.
  </a>
  <a href="#1" id="1">
   A fundamental motivation and long standing goal of the paraphrasing and RTE communities has been to cast various semantic applications as paraphrasing/textual entailment [ 4 ].
  </a>
  <a href="#2" id="2">
   While it has been shown that paraphrasing methods are useful for question answering [ 15 ] and relation extraction [ 27 ] , this is, to the best of our knowledge, the first paper to perform semantic parsing through paraphrasing.
  </a>
  <a href="#3" id="3">
   Our paraphrase model emphasizes simplicity and efficiency, but the framework is agnostic to the internals of the paraphrase method.
  </a>
  <a href="#4" id="4">
   On the semantic parsing side, our work is most related to Kwiatkowski et al.
  </a>
  <a href="#5" id="5">
   2013.
  </a>
  <a href="#6" id="6">
   The main challenge in semantic parsing is coping with the mismatch between language and the KB.
  </a>
  <a href="#7" id="7">
   In both Kwiatkowski et al.
  </a>
  <a href="#8" id="8">
   2013 ) and this work, an intermediate representation is employed to handle the mismatch, but while they use a logical representation, we opt for a text-based one.
  </a>
  <a href="#9" id="9">
   Our choice allows us to benefit from the parallel monolingual corpus ParaLex and from word vectors trained on Wikipedia.
  </a>
  <a href="#10" id="10">
   We believe that our approach is particularly suitable for scenarios such as factoid question answering, where the space of logical forms is somewhat constrained and a few generation rules suffice to reduce the problem to paraphrasing.
  </a>
  <a href="#11" id="11">
   Our work is also related to Fader et al.
  </a>
  <a href="#12" id="12">
   2013 ) , who presented a paraphrase-driven question answering system.
  </a>
  <a href="#13" id="13">
   One can view this work as a generalization of Fader et al along three dimensions.
  </a>
  <a href="#14" id="14">
   First, Fader et al use a KB over natural language extractions rather than a formal KB and so querying the KB does not require a generation step u'\u2013' they paraphrase questions to KB entries directly.
  </a>
  <a href="#15" id="15">
   Second, they suggest a particular paraphrasing method that maps a test question to a question for which the answer is already known in a single step.
  </a>
  <a href="#16" id="16">
   We propose a general paraphrasing framework and instantiate it with two paraphrase models.
  </a>
  <a href="#17" id="17">
   Lastly, Fader et al handle queries with only one property and entity whereas we generalize to more types of logical forms.
  </a>
  <a href="#18" id="18">
   Since our generated questions are passed to a paraphrase model, we took a very simple approach, mostly ensuring that we preserved the semantics of the utterance without striving for the most fluent realization.
  </a>
  <a href="#19" id="19">
   Research on generation [ 5 , 26 , 31 , 25 ] typically focuses on generating natural utterances for human consumption, where fluency is important.
  </a>
  <a href="#20" id="20">
   In conclusion, the main contribution of this paper is a novel approach for semantic parsing based on a simple generation procedure and a paraphrase model.
  </a>
  <a href="#21" id="21">
   We achieve state-of-the-art results on two recently released datasets.
  </a>
  <a href="#22" id="22">
   We believe that our approach opens a window of opportunity for learning semantic parsers from raw text not necessarily related to the target KB.
  </a>
  <a href="#23" id="23">
   With more sophisticated generation and paraphrase, we hope to tackle compositionally richer utterances.
  </a>
 </body>
</html>