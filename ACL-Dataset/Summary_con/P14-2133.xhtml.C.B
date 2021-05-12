<html>
 <head>
  <meta content="SENT_NUM:8, WORD_NUM:247" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   With the goal of exploring how much useful syntactic information is provided by unsupervised word embeddings, we have presented three variations on a state-of-the-art parsing model, with extensions to the out-of-vocabulary model, lexicon, and feature set.
  </a>
  <a href="#1" id="1">
   Evaluation of these modified parsers revealed modest gains on extremely small training sets, which quickly vanish as training set size increases.
  </a>
  <a href="#2" id="2">
   Thus, at least restricted to phenomena which can be explained by the experiments described here, our results are consistent with two claims.
  </a>
  <a href="#3" id="3">
   1) unsupervised word embeddings do contain some syntactically useful information, but (2) this information is redundant with what the model is able to determine for itself from only a small amount of labeled training data.
  </a>
  <a href="#4" id="4">
   It is important to emphasize that these results do not argue against the use of continuous representations in a parser s state space, nor argue more generally that constituency parsers cannot possibly benefit from word embeddings.
  </a>
  <a href="#5" id="5">
   However, the failure to uncover gains when searching across a variety of possible mechanisms for improvement, training procedures for embeddings, hyperparameter settings, tasks, and resource scenarios suggests that these gains (if they do exist) are extremely sensitive to these training conditions, and not nearly as accessible as they seem to be in dependency parsers.
  </a>
  <a href="#6" id="6">
   Indeed, our results suggest a hypothesis that word embeddings are useful for dependency parsing (and perhaps other tasks) because they provide a level of syntactic abstraction which is explicitly annotated in constituency parses.
  </a>
  <a href="#7" id="7">
   We leave explicit investigation of this hypothesis for future work.
  </a>
 </body>
</html>