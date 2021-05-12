<html>
 <head>
  <meta content="SENT_NUM:10, WORD_NUM:219" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we presented an efficient text-level discourse parser with time complexity linear in the total number of sentences in the document.
  </a>
  <a href="#1" id="1">
   Our approach was to adopt a greedy bottom-up tree-building, with two linear-chain CRFs as local probabilistic models, and enforce reasonable constraints in the first CRF s Viterbi decoding.
  </a>
  <a href="#2" id="2">
   While significantly outperforming the state-of-the-art model by Joty et al.
  </a>
  <a href="#3" id="3">
   2013 ) , our parser is much faster in practice.
  </a>
  <a href="#4" id="4">
   In addition, we propose a novel idea of post-editing, which modifies a fully-built discourse tree by considering information from upper-level constituents.
  </a>
  <a href="#5" id="5">
   We show that, although doubling the time consumption, post-editing can further boost the parsing performance to close to 90% of human performance.
  </a>
  <a href="#6" id="6">
   In future work, we wish to further explore the idea of post-editing, since currently we use only the depth of the subtrees as upper-level information.
  </a>
  <a href="#7" id="7">
   Moreover, we wish to study whether we can incorporate constraints into the relation models, as we do to the structure models.
  </a>
  <a href="#8" id="8">
   For example, it might be helpful to train the relation models using additional criteria, such as Generalized Expectation [ 11 ] , to better take into account some prior knowledge about the relations.
  </a>
  <a href="#9" id="9">
   Last but not least, as reflected by the low MAFS in our experiments, some particularly difficult relation types might need specifically designed features for better recognition.
  </a>
 </body>
</html>