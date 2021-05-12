<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:907">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented a computational model that takes into account semantics for language learning.</a>
<a href="#1" id="1">We have shown that a system can learn to comprehend and generate utterances from pairs consisting on a situation and an utterance denoting one of the objects in that situation.</a>
<a href="#2" id="2">Unlike previous approaches, there is no explicit semantic annotation of the utterances, the learner constructs the meanings of the utterances from scratch.</a>
<a href="#3" id="3">The learner collects information about the co-occurrence of words and predicates, and uses the semantic situation to help it translate the teacher's utterances to meanings.</a>
<a href="#4" id="4">The teacher's meanings are generalized via the semantic categories to general forms that are the basis of the learner's own utterances.</a>
<a href="#5" id="5">The learner refines its ability to use the general forms to produce grammatical utterances by collecting data from alignments of the teacher's utterances with the general forms.</a>
<a href="#6" id="6">This data is used to construct decision trees to choose sequences of words for parts of an intended meaning.</a>
<a href="#7" id="7">Thus, the learner's grammar is represented by its initial semantic categories and the information it has collected about co-occurrence of words and predicates, about what general forms represent meanings, and about how to choose sequences of words for parts of an intended meaning.</a>
<a href="#8" id="8">Decomposing the learner's task into learning a grammar of meanings (in our system, the general forms) and a set of rules for expressing meanings in words (in our system, the decision trees) seems to simplify the learning task.</a>
<a href="#9" id="9">For the tasks we consider, simply accumulating a list of general forms (with a mechanism to “age out” incorrect ones) and translating the atoms and gaps of the meaning into consecutive sequences of words provides a feasible solution.</a>
<a href="#10" id="10">However, it is likely that more complex language learning tasks require a more complex model of the relationship between meanings and utterances.</a>
<a href="#11" id="11">Our model of language is very simplified, and there are many issues it does not deal with properly, including multi-word phrases bearing meaning, morphological relations between words, phonological rules for word choice, words with more than one meaning and meanings that can be expressed in more than one way, languages with free word-orders and meaning components expressed by non-contiguous sequences of words.</a>
<a href="#12" id="12">Questions of generality, scalability and noise tolerance should also be addressed.</a>
<a href="#13" id="13">Other desirable directions to explore include more sophisticated use of co-occurrence information, more powerful methods of learning the grammars of meanings, feedback to allow the learning of productions to improve comprehension, better methods of alignment between utterances and meanings, and methods to allow the learner's semantic categories to evolve in response to language learning.</a>
<a href="#14" id="14">Our model and results have also allowed us to demonstrate that a relatively simple model of a teacher can offer meaning-preserving corrections to the learner, and that for certain learning tasks such corrections can significantly reduce the number of interactions for the learner to reach a high level of performance.</a>
<a href="#15" id="15">Moreover, this improvement does not depend on the learner's ability to detect corrections: the effect depends on the change in the distribution of teacher utterances in the correcting versus non-correcting conditions.</a>
<a href="#16" id="16">This result suggests re-visiting discussions in linguistics that assume that the learner must detect a teacher correction as a correction in order for it to have an influence on the learning process.</a>
<a href="#17" id="17">In fact, in our model the learner can detect meaning-preserving corrections of the teacher.</a>
<a href="#18" id="18">A future direction of research is to see if a learner can use the ability to detect corrections to accelerate the learning process further.</a>
<a href="#19" id="19">Interestingly, preliminary experiments in assigning greater weight to detected corrections in the decision tree construction process did not seem to have a significant positive effect on the attainment of high levels of performance.</a>
<a href="#20" id="20">Our model of a teacher is very simple and purely “reactive.” That is, the teacher does not keep any history for the learner that it is interacting with (other than accumulating summary statistics), and reacts to learner utterances using the same procedures each time.</a>
<a href="#21" id="21">The only dimension along which teachers differ is their propensity to correct the learner (that is, the probability of correction).</a>
<a href="#22" id="22">An interesting future direction would be to explore the effects of making the teacher “more responsive” to the learner, possibly taking into account the history of interactions with this learner.</a>
<a href="#23" id="23">One possibility would be to try a simple model of “motherese” in which the distribution on the teacher's utterances might be weighted toward utterances slightly more complex than the current average for learner utterances.</a>
<a href="#24" id="24">Another possibility would be to have the teacher keep track of learner errors, and weight its distribution of utterances to provide more models of correct utterances in regions of learner error.</a>
<a href="#25" id="25">It would be very interesting to extend our results to more practical domains such as data mining and information retrieval.</a>
<a href="#26" id="26">In the framework of data mining, semantic information might allow us to tackle the problem of scalability by reducing the amount of data the algorithms must consider.</a>
<a href="#27" id="27">In information retrieval, specifically in the context of web search, a search guided by semantic information might allow users to get results more relevant to their queries when the desired information is hard to find purely syntactically.</a>
<a href="#28" id="28">Semantics might also facilitate communication between the user and the search engine; the user could ask for information in a more natural way (not just using keywords), and the search engine could understand the query, even if it is not completely grammatically correct.</a>
<a href="#29" id="29">We believe that incorporating semantics is crucial for future search engines.</a>
</body>
</html>