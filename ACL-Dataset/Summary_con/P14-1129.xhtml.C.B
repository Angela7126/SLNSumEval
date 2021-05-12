<html>
 <head>
  <meta content="SENT_NUM:16, WORD_NUM:306" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We have described a novel formulation for a neural network-based machine translation joint model, along with several simple variations of this model.
  </a>
  <a href="#1" id="1">
   When used as MT decoding features, these models are able to produce a gain of +3.0 BLEU on top of a very strong and feature-rich baseline, as well as a +6.3 BLEU gain on top of a simpler system.
  </a>
  <a href="#2" id="2">
   Our model is remarkably simple u'\u2013' it requires no linguistic resources, no feature engineering, and only a handful of hyper-parameters.
  </a>
  <a href="#3" id="3">
   It also has no reliance on potentially fragile outside algorithms, such as unsupervised word clustering.
  </a>
  <a href="#4" id="4">
   We consider the simplicity to be a major advantage.
  </a>
  <a href="#5" id="5">
   Not only does this suggest that it will generalize well to new language pairs and domains, but it also suggests that it will be straightforward for others to replicate these results.
  </a>
  <a href="#6" id="6">
   Overall, we believe that the following factors set us apart from past work and allowed us to obtain such significant improvements.
  </a>
  <a href="#7" id="7">
   The ability to use the NNJM in decoding rather than rescoring.
  </a>
  <a href="#8" id="8">
   The use of a large bilingual context vector, which is provided to the neural network in u'\u201c' raw u'\u201d' form, rather than as the output of some other algorithm.
  </a>
  <a href="#9" id="9">
   The fact that the model is purely lexicalized, which avoids both data sparsity and implementation complexity.
  </a>
  <a href="#10" id="10">
   The large size of the network architecture.
  </a>
  <a href="#11" id="11">
   The directional variation models.
  </a>
  <a href="#12" id="12">
   One of the biggest goals of this work is to quell any remaining doubts about the utility of neural networks in machine translation.
  </a>
  <a href="#13" id="13">
   We believe that there are large areas of research yet to be explored.
  </a>
  <a href="#14" id="14">
   For example, creating a new type of decoder centered around a purely lexicalized neural network model.
  </a>
  <a href="#15" id="15">
   Our short term ideas include using more interesting types of context in our input vector (such as source syntax), or using the NNJM to model syntactic/semantic structure of the target.
  </a>
 </body>
</html>