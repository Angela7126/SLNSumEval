<html>
 <head>
  <meta content="SENT_NUM:14, WORD_NUM:301" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We formulated the task of recognizing implied predicate-argument relationships within textual inference scenarios.
  </a>
  <a href="#1" id="1">
   We compared this task to the labeling task of SemEval 2010, where no prior information about candidate arguments in the text is available.
  </a>
  <a href="#2" id="2">
   We point out that in textual inference scenarios the candidate predicate and argument are given by the Hypothesis, while the challenge is only to verify that a predicate-argument relationship between these candidates is implied from the given Text.
  </a>
  <a href="#3" id="3">
   Accordingly, some complex steps necessitated in the SemEval task can be avoided, while additional relevant cases are covered.
  </a>
  <a href="#4" id="4">
   Moreover, we have shown that this simpler task is more feasibly solvable, where our 15 features achieved more than 80% accuracy.
  </a>
  <a href="#5" id="5">
   While our dataset and algorithm were presented in the context of RTE, the same challenge and methods are applicable to other textual inference tasks as well.
  </a>
  <a href="#6" id="6">
   Consider, for example, the Question Answering (QA) task.
  </a>
  <a href="#7" id="7">
   Typically QA systems detect a candidate predicate that matches the question s predicate.
  </a>
  <a href="#8" id="8">
   Similarly, candidate arguments, which match either the expected answer type or other arguments in the question are detected too.
  </a>
  <a href="#9" id="9">
   Consequently, our methods which exploit the availability of the candidate predicate and argument can be adapted to this scenario as well.
  </a>
  <a href="#10" id="10">
   Similarly, a typical approach for Event Extraction (a sub task of Information Extraction ) is to start by applying an entity extractor, which identifies argument candidates.
  </a>
  <a href="#11" id="11">
   Accordingly, candidate predicate and arguments are detected in this scenario too, while the remaining challenge is to assess the likelihood that a predicate-argument relationship holds between them.
  </a>
  <a href="#12" id="12">
   Following this observation, we propose future work of applying our methods to other tasks.
  </a>
  <a href="#13" id="13">
   An additional direction for future work is to further develop new methods for our task, possibly by incorporating SRL resources and/or linguistically oriented rules, in order to improve the results we achieved so far.
  </a>
 </body>
</html>