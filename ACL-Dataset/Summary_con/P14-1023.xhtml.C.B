<html>
 <head>
  <meta content="SENT_NUM:22, WORD_NUM:650" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   This paper has presented the first systematic comparative evaluation of count and predict vectors.
  </a>
  <a href="#1" id="1">
   As seasoned distributional semanticists with thorough experience in developing and using count vectors, we set out to conduct this study because we were annoyed by the triumphalist overtones often surrounding predict models, despite the almost complete lack of a proper comparison to count vectors.
  </a>
  <a href="#2" id="2">
   12 12 Here is an example, where word2vec is called the crown jewel of natural language processing http://bit.ly/1ipv72M Our secret wish was to discover that it is all hype, and count vectors are far superior to their predictive counterparts.
  </a>
  <a href="#3" id="3">
   A more realistic expectation was that a complex picture would emerge, with predict and count vectors beating each other on different tasks.
  </a>
  <a href="#4" id="4">
   Instead, we found that the predict models are so good that, while the triumphalist overtones still sound excessive, there are very good reasons to switch to the new architecture.
  </a>
  <a href="#5" id="5">
   However, due to space limitations we have only focused here on quantitative measures.
  </a>
  <a href="#6" id="6">
   It remains to be seen whether the two types of models are complementary in the errors they make, in which case combined models could be an interesting avenue for further work.
  </a>
  <a href="#7" id="7">
   The space of possible parameters of count DSMs is very large, and it s entirely possible that some options we did not consider would have improved count vector performance somewhat.
  </a>
  <a href="#8" id="8">
   Still, given that the predict vectors also outperformed the syntax-based dm model, and often approximated state-of-the-art performance, a more proficuous way forward might be to focus on parameters and extensions of the predict models instead.
  </a>
  <a href="#9" id="9">
   After all, we obtained our already excellent results by just trying a few variations of the word2vec defaults.
  </a>
  <a href="#10" id="10">
   Add to this that, beyond the standard lexical semantics challenges we tested here, predict models are currently been successfully applied in cutting-edge domains such as representing phrases [ 34 , 43 ] or fusing language and vision in a common semantic space [ 19 , 42 ].
  </a>
  <a href="#11" id="11">
   Based on the results reported here and the considerations we just made, we would certainly recommend anybody interested in using DSMs for theoretical or practical applications to go for the predict models, with the important caveat that they are not all created equal (cf. the big difference between word2vec and cw models.
  </a>
  <a href="#12" id="12">
   At the same time, given the large amount of work that has been carried out on count DSMs, we would like to explore, in the near future, how certain questions and methods that have been considered with respect to traditional DSMs will transfer to predict models.
  </a>
  <a href="#13" id="13">
   For example, the developers of Latent Semantic Analysis [ 28 ] , Topic Models [ 21 ] and related DSMs have shown that the dimensions of these models can be interpreted as general latent semantic domains, which gives the corresponding models some a priori cognitive plausibility while paving the way for interesting applications.
  </a>
  <a href="#14" id="14">
   Another important line of DSM research concerns context engineering .
  </a>
  <a href="#15" id="15">
   There has been for example much work on how to encode syntactic information into context features [ 37 ] , and more recent studies construct and combine feature spaces expressing topical vs. functional information [ 46 ].
  </a>
  <a href="#16" id="16">
   To give just one last example, distributional semanticists have looked at whether certain properties of vectors reflect semantic relations in the expected way e.g.,, whether the vectors of hypernyms distributionally include the vectors of hyponyms in some mathematical precise sense.
  </a>
  <a href="#17" id="17">
   Do the dimensions of predict models also encode latent semantic domains.
  </a>
  <a href="#18" id="18">
   Do these models afford the same flexibility of count vectors in capturing linguistically rich contexts.
  </a>
  <a href="#19" id="19">
   Does the structure of predict vectors mimic meaningful semantic relations.
  </a>
  <a href="#20" id="20">
   Does all of this even matter, or are we on the cusp of discovering radically new ways to tackle the same problems that have been approached as we just sketched in traditional distributional semantics.
  </a>
  <a href="#21" id="21">
   Either way, the results of the present investigation indicate that these are important directions for future research in computational semantics.
  </a>
 </body>
</html>