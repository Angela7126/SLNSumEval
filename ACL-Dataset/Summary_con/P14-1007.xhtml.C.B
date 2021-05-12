<html>
 <head>
  <meta content="SENT_NUM:12, WORD_NUM:361" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   Our motivation in this work was to take the design of the 2012 * SEM Shared Task on negation analysis at face value as an overtly semantic problem that takes a central role in our long-term pursuit of language understanding.
  </a>
  <a href="#1" id="1">
   Through both theoretical and practical reflection on the nature of representations at play in this task, we believe we have demonstrated that explicit semantic structure will be a key driver of further progress in the analysis of negation.
  </a>
  <a href="#2" id="2">
   We were able to closely align two independently developed semantic analyses the negation-specific annotations of \citeA Mor:Sch:Dae:11, on the one hand, and the broad-coverage, MRS meaning representations of the ERG, on the other hand.
  </a>
  <a href="#3" id="3">
   In our view, the conceptual correlation between these two semantic views on negation analysis reinforces their credibility.
  </a>
  <a href="#4" id="4">
   Unlike the rather complex top-performing systems from the original 2012 competition, our MRS Crawler is defined by a small set of general rules that operate over general-purpose, explicit meaning representations.
  </a>
  <a href="#5" id="5">
   Thus, our approach scores high on transparency, adaptability, and replicability.
  </a>
  <a href="#6" id="6">
   In isolation, the Crawler provides premium precision but comparatively low recall.
  </a>
  <a href="#7" id="7">
   Its limitations, we conjecture, reflect primarily on ERG parsing challenges and inconsistencies in the target data.
  </a>
  <a href="#8" id="8">
   In a sense, our approach pushes a larger proportion of the task into the parser, meaning (a) there should be good opportunities for parser adaptation to this somewhat idiosyncratic text type; (b) our results can serve to offer feedback on ERG semantic analyses and parse ranking; and (c) there is a much smaller proportion of very task-specific engineering.
  </a>
  <a href="#9" id="9">
   When embedded in a confidence-thresholded cascading architecture, our system advances the state of the art on this task, and oracle combination scores suggest there is much remaining room to better exploit the complementarity of approaches in our study.
  </a>
  <a href="#10" id="10">
   In future work, we will seek to better understand the division of labor between the systems involved through contrastive error analysis and possibly another oracle experiment, constructing gold-standard MRSs for part of the data.
  </a>
  <a href="#11" id="11">
   It would also be interesting to try a task-specific adaptation of the ERG parse ranking model, for example re-training on the pre-existing treebanks but giving preference to analyses that lead to correct Crawler results downstream.
  </a>
 </body>
</html>