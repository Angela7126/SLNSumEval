<html>
 <head>
  <meta content="SENT_NUM:24, WORD_NUM:524" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We have presented a method of deriving abstract denotation from DCS trees, which enables logical inference on DCS, and we developed a textual inference system based on the framework.
  </a>
  <a href="#1" id="1">
   Experimental results have shown the power of the representation that allows both strict inference as on FraCaS data and robust reasoning as on RTE data.
  </a>
  <a href="#2" id="2">
   Exploration of an appropriate meaning representation for querying and reasoning on knowledge bases has a long history.
  </a>
  <a href="#3" id="3">
   Description logic, being less expressive than FOL but featuring more efficient reasoning, is used as a theory base for Semantic Web [].
  </a>
  <a href="#4" id="4">
   Ideas similar to our framework, including the use of sets in a representation that benefits efficient reasoning, are also found in description logic and knowledge representation community [].
  </a>
  <a href="#5" id="5">
   To our knowledge, however, their applications to logical inference beyond the use for database querying have not been much explored in the context of NLP.
  </a>
  <a href="#6" id="6">
   The pursue of a logic more suitable for natural language inference is not new.
  </a>
  <a href="#7" id="7">
   For instance, has implemented a model of natural logic [].
  </a>
  <a href="#8" id="8">
   While being computationally efficient, various inference patterns are out of the scope of their system.
  </a>
  <a href="#9" id="9">
   Much work has been done in mapping natural language into database queries [].
  </a>
  <a href="#10" id="10">
   Among these, the ( -)DCS [] framework defines algorithms that transparently map a labeled tree to a database querying procedure.
  </a>
  <a href="#11" id="11">
   Essentially, this is because DCS trees restrict the querying process to a very limited subset of possible operations.
  </a>
  <a href="#12" id="12">
   Our main contribution, the abstract denotation of DCS trees, can thus be considered as an attempt to characterize a fragment of FOL that is suited for both natural language inference and transparent syntax-semantics mapping, through the choice of operations and relations on sets.
  </a>
  <a href="#13" id="13">
   We have demonstrated the utility of logical inference on DCS through the RTE task.
  </a>
  <a href="#14" id="14">
   A wide variety of strategies tackling the RTE task have been investigated [] , including the comparison of surface strings [] , syntactic and semantic structures [] , semantic vectors [] and logical representations [].
  </a>
  <a href="#15" id="15">
   Acquisition of basic knowledge for RTE is also a huge stream of research [].
  </a>
  <a href="#16" id="16">
   These previous works include various techniques for acquiring and incorporating different kinds of linguistic and world knowledge, and further fight against the knowledge bottleneck problem, e.g., by back-off to shallower representations.
  </a>
  <a href="#17" id="17">
   Logic-based RTE systems employ various approaches to bridge knowledge gaps proposes features from a model builder; proposes an abduction process; shows handcrafted rules could drastically improve the performance of a logic-based RTE system.
  </a>
  <a href="#18" id="18">
   As such, our current RTE system is at a proof-of-concept stage, in that many of the above techniques are yet to be implemented.
  </a>
  <a href="#19" id="19">
   Nonetheless, we would like to emphasize that it already shows performance competitive to state-of-the-art systems on one data set (RTE5.
  </a>
  <a href="#20" id="20">
   Other directions of our future work include further exploitation of the new semantic representation.
  </a>
  <a href="#21" id="21">
   For example, since abstract denotations are readily suited for data querying, they can be used to verify newly generated assumptions by fact search in a database.
  </a>
  <a href="#22" id="22">
   This may open a way towards a hybrid approach to RTE wherein logical inference is intermingled with large scale database querying.
  </a>
  <a href="#23" id="23">
   This research was supported by the Todai Robot Project at National Institute of Informatics.
  </a>
 </body>
</html>