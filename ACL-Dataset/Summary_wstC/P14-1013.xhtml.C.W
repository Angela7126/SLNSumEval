<html>
 <head>
  <meta content="SENT_NUM:15, WORD_NUM:430" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   The most important conclusion we draw from this work is the most appropriate agreement metric for syntactic annotation.
  </a>
  <a href="#1" id="1">
   First of all, we disqualify the LAS metric, primarily due to the methodological inadequacies of using an uncorrected measure.
  </a>
  <a href="#2" id="2">
   While our experiments did not reveal any serious shortcomings (unlike those of [] who in the case of categorisation showed that for large p the uncorrected measure can be increasing ), the methodological problems of uncorrected metrics makes us wary of LAS as an agreement metric.
  </a>
  <a href="#3" id="3">
   Next, of the three metrics, p l a i n is clearly the best; d i f f is extremely sensitive to even moderate amounts of disagreement, while n o r m is overly lenient.
  </a>
  <a href="#4" id="4">
   Looking solely at Figure 3 , one might be led to believe that LAS and p l a i n are interchangeable, but this is not the case.
  </a>
  <a href="#5" id="5">
   As shown by Figures 4 and 5 , the paraboloid shape of the LAS curve in Figure 3 is simply the combination of the metric s linear responses to both label and structural perturbations.
  </a>
  <a href="#6" id="6">
   The behaviour of on the other hand is more complex, with structural noise being penalised harder than perturbations of the labels.
  </a>
  <a href="#7" id="7">
   Thus, the similarity of LAS and p l a i n is not at all assured when the amounts of structural and labelling disagreements differ.
  </a>
  <a href="#8" id="8">
   Additionally, we consider this imbalanced weighting of structural and labelling disagreements a benefit, as structure is the larger part of syntactic annotation compared to the labelling of the dependencies/bracketings.
  </a>
  <a href="#9" id="9">
   Finally our experiments show that is a single metric that is applicable to both dependencies and phrase structure trees.
  </a>
  <a href="#10" id="10">
   Furthermore, metrics are far more flexible than simple accuracy metrics.
  </a>
  <a href="#11" id="11">
   The use of a distance function to define the metric means that more fine-grained distinctions can be made; for example, if the set of labels on the structures is highly structured, partial credit can be given for differing annotations that overlap.
  </a>
  <a href="#12" id="12">
   For example, if different types of adverbials (temporal, negation, etc.) receive different relations, as is the case in the Swedish Talbanken05 [] corpus, confusion of different adverbial types can be given less weight than confusion between subject and object.
  </a>
  <a href="#13" id="13">
   The -based metrics are also far easier to apply to a more complex annotation task such as the tectogrammatical annotation of the PCEDT.
  </a>
  <a href="#14" id="14">
   In this task inserting and deleting nodes is an integral part of the annotation, and if two annotators insert or delete different nodes the all-or-nothing requirement of identical yield of the LAS metric makes it impossible as an evaluation metric in this setting.
  </a>
 </body>
</html>