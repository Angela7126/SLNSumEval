<html>
 <head>
  <meta content="SENT_NUM:8, WORD_NUM:265" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We introduced an approach to compositional distributional semantics based on a linguistically-motivated syntax-to-semantics type mapping, but simple and flexible enough that it can produce representations of English sentences of arbitrary size and structure.
  </a>
  <a href="#1" id="1">
   We showed that our approach is competitive against the more complex lexical function model when evaluated on the simple constructions the latter can be applied to, and it outperforms the additive and multiplicative compositionality models when tested on more realistic benchmarks (where the full-fledged lexical function approach is difficult or impossible to use), even in presence of strong noise in its syntactic input.
  </a>
  <a href="#2" id="2">
   While our results are encouraging, no current benchmark combines large-scale, real-life data with the syntactic variety on which a syntax-driven approach to semantics such as ours could truly prove its worth.
  </a>
  <a href="#3" id="3">
   The recently announced SemEval 2014 Task 1 7 7 http://alt.qcri.org/semeval2014/task1/ is filling exactly this gap, and we look forward to apply our method to this new benchmark, as soon as it becomes available.
  </a>
  <a href="#4" id="4">
   One of the strengths of our framework is that it allows for incremental improvement focused on specific constructions.
  </a>
  <a href="#5" id="5">
   For example, one could add representations for different conjunctions ( and vs or ), train matrices for verb arguments other than subject and direct object, or include new types of modifiers into the model, etc.
  </a>
  <a href="#6" id="6">
   While there is potential for local improvements, our framework, which extends and improves on existing compositional semantic vector models, has demonstrated its ability to account for full sentences in a principled and elegant way.
  </a>
  <a href="#7" id="7">
   Our implementation of the model relies on simple and efficient training, works fast, and shows good empirical results.
  </a>
 </body>
</html>