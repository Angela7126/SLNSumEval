<html>
 <head>
  <meta content="SENT_NUM:9, WORD_NUM:185" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this work, we propose a semantic parsing framework for single-relation questions.
  </a>
  <a href="#1" id="1">
   Compared to the existing work, our key insight is to match relation patterns and entity mentions using a semantic similarity function rather than lexical rules.
  </a>
  <a href="#2" id="2">
   Our similarity model is trained using convolutional neural networks with letter-trigrams vectors.
  </a>
  <a href="#3" id="3">
   This design helps the model go beyond bag-of-words representations and handles the OOV issue.
  </a>
  <a href="#4" id="4">
   Our method achieves higher precision on the QA task than the previous work, Paralex , consistently at different recall points.
  </a>
  <a href="#5" id="5">
   Despite the strong empirical performance, our system has room for improvement.
  </a>
  <a href="#6" id="6">
   For instance, due to the variety of entity mentions in the real world, the parallel corpus derived from the WikiAnswers data and ReVerb KB may not contain enough data to train a robust entity linking model.
  </a>
  <a href="#7" id="7">
   Replacing this component with a dedicated entity linking system could improve the performance and also reduce the number of pattern/mention candidates when processing each question.
  </a>
  <a href="#8" id="8">
   In the future, we would like to extend our method to other more structured KBs, such as Freebase, and to explore approaches to extend our system to handle multi-relation questions.
  </a>
 </body>
</html>