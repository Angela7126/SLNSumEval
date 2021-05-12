<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:319">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work we investigated two issues:</a>
<a href="#1" id="1">To what extent can a QA system be designed in a language-independent way, by preserving its effectiveness?</a>
<a href="#2" id="2">Can Wikipedia and DBpedia serve as effective knowledge bases for answering WWBM game questions?</a>
<a href="#3" id="3">As regards the first issue, this work actually led to the definition of an effective language-independent framework for QA, in which both the Question Answering and Answer Scoring modules were defined using a set of filters that are not related to a specific language.</a>
<a href="#4" id="4">We also defined an effective strategy to combine different criteria for scoring candidate answers through machine learning techniques.</a>
<a href="#5" id="5">Experiments performed on Italian and English showed the effectiveness of the approach.</a>
<a href="#6" id="6">As regards the second issue, we built a virtual player for the WWBM game based on the following modules:</a>
<a href="#7" id="7">Question Answering: is able to retrieve passages of text relevant to a specific question expressed in natural language, by using Wikipedia and DBpedia open knowledge sources;</a>
<a href="#8" id="8">Answer Scoring: implements several heuristics based on the analysis of the results returned by the Question Answering module, in order to assign a score to the four candidate answers;</a>
<a href="#9" id="9">Decision Making: chooses the strategy to play the game, by exploiting the scores of the four candidate answers, the availability of lifelines, and the current level of the game.</a>
<a href="#10" id="10">The virtual player outperformed human players in terms of average accuracy in correctly answering to questions of the game, and in terms of ability to play real games with their rules.</a>
<a href="#11" id="11">We plan to enhance the decision making algorithm, in order to allow a smarter management of the lifelines, and a less conservative strategy which could lead to a more risk neutral player, with the hope that these refinements will further improve the overall accuracy of the system.</a>
<a href="#12" id="12">Moreover, specific heuristics could be devised to answer to questions which are currently unanswerable for our system (Section 8.1.1) in order to further improve its performance.</a>
</body>
</html>