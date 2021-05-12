<html>
 <head>
  <meta content="SENT_NUM:26, WORD_NUM:552" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we extensively examined state-of-the-art static approaches and proposed novel models with dynamic Bayesian updates for streaming personal analytics on Twitter.
  </a>
  <a href="#1" id="1">
   Because our streaming models rely on communications from Twitter users and content from various notions of user-local neighborhood they can be effectively applied to real-time dynamic data streams.
  </a>
  <a href="#2" id="2">
   Our results support several key findings listed below.
  </a>
  <a href="#3" id="3">
   Neighborhood content is useful for personal analytics.
  </a>
  <a href="#4" id="4">
   Content extracted from various notions of a user-local neighborhood can be as effective or more effective for political preference classification than user self-authored content.
  </a>
  <a href="#5" id="5">
   This may be an effect of sparseness of relevant user data, in that users talk about politics very sporadically compared to a random sample of their neighbors.
  </a>
  <a href="#6" id="6">
   Substantial signal for political preference prediction is distributed in the neighborhood.
  </a>
  <a href="#7" id="7">
   Querying for more neighbors per user is more beneficial than querying for extra content from the existing neighbors e.g.,, 5 tweets from 10 neighbors leads to higher accuracy than 25 tweets from 2 neighbors or 50 tweets from 1 neighbor.
  </a>
  <a href="#8" id="8">
   This may be also the effect of data heterogeneity in social media compared to e.g.,, political debate text [ 35 ].
  </a>
  <a href="#9" id="9">
   These findings demonstrate that a substantial signal is distributed over the neighborhood content.
  </a>
  <a href="#10" id="10">
   Neighborhoods constructed from friend, user mention and retweet relationships are most effective.
  </a>
  <a href="#11" id="11">
   Friend, user mention and retweet neighborhoods show the best accuracy for predicting political preferences of Twitter users.
  </a>
  <a href="#12" id="12">
   We think that friend relationships are more effective than e.g.,, follower relationships because it is very likely that users share common interests and preferences with their friends, e.g., Facebook friends can even be used to predict a user s credit score.
  </a>
  <a href="#13" id="13">
   13 13 http://money.cnn.com/2013/08/26/technology/social/ facebook-credit-score/ User mentions and retweets are two primary ways of interaction on Twitter.
  </a>
  <a href="#14" id="14">
   They both allow to share information e.g.,, political news, events with others and to be involved in direct communication e.g.,, live political discussions, political groups.
  </a>
  <a href="#15" id="15">
   Streaming models are more effective than batch models for personal analytics.
  </a>
  <a href="#16" id="16">
   The predictions made using dynamic models with Bayesian updates over user and joint user-neighbor communication streams demonstrate higher performance with lower resources spent compared to the batch models.
  </a>
  <a href="#17" id="17">
   Depending on user political involvement, expressiveness and activeness, the perfect prediction (approaching 100% accuracy) can be made using only 100 - 500 tweets per user.
  </a>
  <a href="#18" id="18">
   Generalization of the classifiers for political preference prediction.
  </a>
  <a href="#19" id="19">
   This work raises a very important but under-explored problem of the generalization of classifiers for personal analytics in social media, also recently discussed by Cohen and Ruth [ 6 ].
  </a>
  <a href="#20" id="20">
   For instance, the existing models developed for political preference prediction are all trained on Twitter data but report significantly different results even for the same baseline models trained using bag-of-word lexical features as shown in Table 1.
  </a>
  <a href="#21" id="21">
   In this work we experiment with three different datasets.
  </a>
  <a href="#22" id="22">
   Our results for both static and dynamic models show that the accuracy indeed depends on the way the data was constructed.
  </a>
  <a href="#23" id="23">
   Therefore, publicly available datasets need to be released for a meaningful comparison of the approaches for personal analytics in social media.
  </a>
  <a href="#24" id="24">
   In future work, we plan to incorporate iterative model updates from newly classified communications similar to online perceptron-style updates.
  </a>
  <a href="#25" id="25">
   In addition, we aim to experiment with neighborhood-specific classifiers applied towards the tweets from neighborhood-specific streams e.g.,, friend classifier used for friend tweets, retweet classifier applied to retweet tweets etc.
  </a>
 </body>
</html>