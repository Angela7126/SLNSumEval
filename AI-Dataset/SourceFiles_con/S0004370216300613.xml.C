<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Robust multilingual Named Entity Recognition with shallow semi-supervised features.
   </title>
   <abstract>
    We present a multilingual Named Entity Recognition approach based on a robust and general set of features across languages and datasets. Our system combines shallow local information with clustering semi-supervised features induced on large amounts of unlabeled text. Understanding via empirical experimentation how to effectively combine various types of clustering features allows us to seamlessly export our system to other datasets and languages. The result is a simple but highly competitive system which obtains state of the art results across five languages and twelve datasets. The results are reported on standard shared task evaluation data such as CoNLL for English, Spanish and Dutch. Furthermore, and despite the lack of linguistically motivated features, we also report best results for languages such as Basque and German. In addition, we demonstrate that our method also obtains very competitive results even when the amount of supervised data is cut by half, alleviating the dependency on manually annotated data. Finally, the results show that our emphasis on clustering features is crucial to develop robust out-of-domain models. The system and models are freely available to facilitate its use and guarantee the reproducibility of results.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A named entity can be mentioned using a great variety of surface forms (Barack Obama, President Obama, Mr. Obama, B. Obama, etc.) and the same surface form can refer to a variety of named entities. For example, according to the English Wikipedia, the form ‘Europe’ can ambiguously be used to refer to 18 different entities, including the continent, the European Union, various Greek mythological entities, a rock band, some music albums, a magazine, a short story, etc.{sup:1} Furthermore, it is possible to refer to a named entity by means of anaphoric pronouns and co-referent expressions such as ‘he’, ‘her’, ‘their’, ‘I’, ‘the 35 year old’, etc. Therefore, in order to provide an adequate and comprehensive account of named entities in text it is necessary to recognize the mention of a named entity and to classify it by a pre-defined type (e.g, person, location, organization). Named Entity Recognition and Classification (NERC) is usually a required step to perform Named Entity Disambiguation (NED), namely to link ‘Europe’ to the right Wikipedia article, and to resolve every form of mentioning or co-referring to the same entity.
     </paragraph>
     <paragraph>
      Nowadays NERC systems are widely being used in research for tasks such as Coreference Resolution [51], Named Entity Disambiguation [19], [27], [29], [38], [26] for which a lot of interest has been created by the TAC KBP shared tasks [32], Machine Translation [3], [33], [5], [35], Aspect Based Sentiment Analysis [37], [11], [50], [49], Event Extraction [22], [2], [31], [20], [30] and Event Ordering [41].
     </paragraph>
     <paragraph>
      Moreover, NERC systems are integrated in the processing chain of many industrial software applications, mostly by companies offering specific solutions for a particular industrial sector which require recognizing named entities specific of their domain. There is therefore a clear interest in both academic research and industry to develop robust and efficient NERC systems: For industrial vendors it is particularly important to diversify their services by including NLP technology for a variety of languages whereas in academic research NERC is one of the foundations of many other NLP end-tasks.
     </paragraph>
     <paragraph>
      Most NERC taggers are supervised statistical systems that extract patterns and term features which are considered to be indications of Named Entity (NE) types using the manually annotated training data (extracting orthographic, linguistic and other types of evidence) and often external knowledge resources. As in other NLP tasks, supervised statistical NERC systems are more robust and obtain better performance on available evaluation sets, although sometimes the statistical models can also be combined with specific rules for some NE types. For best performance, supervised statistical approaches require manually annotated training data, which is both expensive and time-consuming. This has seriously hindered the development of robust high performing NERC systems for many languages but also for other domains and text genres [45], [54], in what we will henceforth call ‘out-of-domain’ evaluations.
     </paragraph>
     <paragraph>
      Moreover, supervised NERC systems often require fine-tuning for each language and, as some of the features require language-specific knowledge, this poses yet an extra complication for the development of robust multilingual NERC systems. For example, it is well-known that in German every noun is capitalized and that compounds including named entities are pervasive. This also applies to agglutinative languages such as Basque, Korean, Finnish, Japanese, Hungarian or Turkish. For this type of languages, it had usually been assumed that linguistic features (typically Part of Speech (POS) and lemmas, but also semantic features based on WordNet, for example) and perhaps specific hand-crafted rules, were a necessary condition for good NERC performance as they would allow to capture better the most recurrent declensions (cases) of named entities for Basque [4] or to address problems such as sparsity and capitalization of every noun for German [23], [7], [8]. This language dependency was easy to see in the CoNLL 2002 and 2003 tasks, in which systems participating in the two available languages for each edition obtained in general different results for each language. This suggests that without fine-tuning for each corpus and language, the systems did not generalize well across languages [46].
     </paragraph>
     <paragraph>
      This paper presents a multilingual and robust NERC system based on simple, general and shallow features that heavily relies on word representation features for high performance. Even though we do not use linguistic motivated features, our approach also works well for inflected languages such as Basque and German. We demonstrate the robustness of our approach by reporting best results for five languages (Basque, Dutch, German, English and Spanish) on 12 different datasets, including seven in-domain and eight out-of-domain evaluations.
     </paragraph>
     <section label="1.1">
      <section-title>
       Contributions
      </section-title>
      <paragraph>
       The main contributions of this paper are the following: First, we show how to easily develop robust NERC systems across datasets and languages with minimal human intervention, even for languages with declension and/or complex morphology. Second, we empirically show how to effectively use various types of simple word representation features thereby providing a clear methodology for choosing and combining them. Third, we demonstrate that our system still obtains very competitive results even when the supervised data is reduced by half (even less in some cases), alleviating the dependency on costly hand annotated data. These three main contributions are based on:
      </paragraph>
      <list>
       <list-item label="1.">
        A simple and shallow robust set of features across languages and datasets, even in out-of-domain evaluations.
       </list-item>
       <list-item label="2.">
        The lack of linguistic motivated features, even for languages with agglutinative (e.g., Basque) and/or complex morphology (e.g., German).
       </list-item>
       <list-item label="3.">
        A clear methodology for using and combining various types of word representation features by leveraging public unlabeled data.
       </list-item>
      </list>
      <paragraph>
       Our approach consists of shallow local features complemented by three types of word representation (clustering) features: Brown clusters [10], Clark clusters [15] and K-means clusters on top of the word vectors obtained by using the Skip-gram algorithm [39]. We demonstrate that combining and stacking different clustering features induced from various data sources (Reuters, Wikipedia, Gigaword, etc.) allows to cover different and more varied types of named entities without manual feature tuning. Even though our approach is much simpler than most, we obtain the best results for Dutch, Spanish and English and comparable results in German (on CoNLL 2002 and 2003). We also report best results for German using the GermEval 2014 shared task data and for Basque using the Egunkaria testset [4].
      </paragraph>
      <paragraph>
       We report out-of-domain evaluations in three languages (Dutch, English and Spanish) using four different datasets to compare our system with the best publicly available systems for those languages: Illinois NER [52] for English, Stanford NER [24] for English and Spanish, SONAR-1 NERD for Dutch [21] and Freeling for Spanish [47]. We outperform every other system in the eight out-of-domain evaluations reported in Section 4.3. Furthermore, the out-of-domain results show that our clustering features provide a simple and easy method to improve the robustness of NERC systems.
      </paragraph>
      <paragraph>
       Finally, and inspired by previous work [34], [9] we measure how much supervision is required to obtain state of the art results. In Section 4.2 we show that we can still obtain very competitive results reducing the supervised data by half (and sometimes even more). This, together with the lack of linguistic features, means that our system considerably saves data annotation costs, which is quite convenient when trying to develop a NERC system for a new language and/or domain.
      </paragraph>
      <paragraph>
       Our system learns Perceptron models [17] using the Machine Learning machinery provided by the Apache OpenNLP project{sup:2} with our own customized (local and clustering) features. Our NERC system is publicly available and distributed under the Apache 2.0 License and part of the IXA pipes tools [1]. Every result reported in this paper is obtained using the conlleval script from the CoNLL 2002 and CoNLL 2003 shared tasks.{sup:3} To guarantee reproducibility of results we also make publicly available the models and the scripts used to perform the evaluations. The system, models and evaluation scripts can be found in the ixa-pipe-nerc website.{sup:4}
      </paragraph>
      <paragraph>
       Next Section reviews related work, focusing on best performing NERC systems for each language evaluated on standard shared evaluation task data. Section 3 presents the design of our system and our overall approach to NERC. In Section 4 we report the evaluation results obtained by our system for 5 languages (Basque, Dutch, German, English and Spanish) on 12 different datasets, distributed in 7 in-domain and 8 out-of-domain evaluations. Section 5 discusses the results and contributions of our approach. In Section 6 we highlight the main aspects of our work providing some concluding remarks and future work to be done using our NERC approach applied to other text genres, domains and sequence labeling tasks.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      The Named Entity Recognition and Classification (NERC) task was first defined for the Sixth Message Understanding Conference (MUC 6) [44]. The MUC 6 tasks focused on Information Extraction (IE) from unstructured text and NERC was deemed to be an important IE sub-task with the aim of recognizing and classifying nominal mentions of persons, organizations and locations, and also numeric expressions of dates, money, percentage and time. In the following years, research on NERC increased as it was considered to be a crucial source of information for other Natural Language Processing tasks such as Question Answering (QA) and Textual Entailment (RTE) [44]. Furthermore, while MUC 6 was solely devoted to English as target language, the CoNLL shared tasks (2002 and 2003) boosted research on language independent NERC for 3 additional target languages: Dutch, German and Spanish [57], [58].
     </paragraph>
     <paragraph>
      The various MUC, ACE and CoNLL evaluations provided a very convenient framework to test and compare NERC systems, algorithms and approaches. They provided manually annotated data for training and testing the systems as well as an objective evaluation methodology. Using such framework, research rapidly evolved from rule-based approaches (consisting of manually handcrafted rules) to language independent systems focused on learning supervised statistical models. Thus, while in the MUC 6 competition 5 out of 8 systems were rule-based, in CoNLL 2003 16 teams participated in the English task all using statistical-based NERC [44].
     </paragraph>
     <section label="2.1">
      <section-title>
       Datasets
      </section-title>
      <paragraph>
       Table 1 describes the 12 datasets used in this paper. The first half lists the corpora used for in-domain evaluation whereas the lower half contains the out-of-domain datasets. The CoNLL NER shared tasks focused on language independent machine learning approaches for 4 entity types: person, location, organization and miscellaneous entities. The 2002 edition provided manually annotated data in Dutch and Spanish whereas in 2003 the languages were German and English. In addition to the CoNLL data, for English we also use the formal run of MUC 7 and Wikigold for out-of-domain evaluation. Very detailed descriptions of CoNLL and MUC data can easily be found in the literature, including the shared task descriptions themselves [13], [57], [58], so in the following we will describe the remaining, newer datasets.
      </paragraph>
      <paragraph>
       The Wikigold corpus consists of 39K words of English Wikipedia manually annotated following the CoNLL 2003 guidelines [46]. For Spanish and Dutch, we also use Ancora 2.0 [56] and SONAR-1 [21] respectively. SONAR-1 is a one million word Dutch corpus with both coarse-grained and fine-grained named entity annotations. The coarse-grained level includes product and event entity types in addition to the four types defined in CoNLL data. Ancora adds date and number types to the CoNLL four main types. In Basque the only gold standard corpus is Egunkaria [4]. Although the Basque Egunkaria dataset is annotated with four entity types, the miscellaneous class is extremely sparse, occurring only in a proportion of 1 to 10. Thus, in the training data there are 156 entities annotated as MISC whereas each of the other three classes contain around 1200 entities.
      </paragraph>
      <paragraph>
       In the datasets described so far, named entities were assumed to be non-recursive and non-overlapping. During the annotation process, if a named entity was embedded in a longer one, then only the longest mention was annotated. The exceptions are the GermEval 2014 shared task data for German and MEANTIME, where nested entities are also annotated (both inner and outer spans).
      </paragraph>
      <paragraph>
       The GermEval 2014 NER shared task [7] aimed at improving the state of the art of German NERC which was perceived to be comparatively lower than the English NERC. Two main extensions were introduced in GermEval 2014; (i) fine grained named entity sub-types to indicate derivations and compounds; (ii) embedded entities (and not only the longest span) are annotated. In total, there are 12 types for classification: person, location, organization, other plus their sub-types annotated at their inner and outer levels.
      </paragraph>
      <paragraph>
       Finally, the MEANTIME corpus [42] is a multilingual (Dutch, English, Italian and Spanish) publicly available evaluation set annotated within the Newsreader project.{sup:5} It consists of 120 documents, divided into 4 topics: Apple Inc., Airbus and Boeing, General Motors, Chrysler and Ford, and the stock market. The articles are selected in such a way that the corpus contains different articles that deal with the same topic over time (e.g. launch of a new product, discussion of the same financial indexes). Moreover, it contains nested entities so the evaluation results will be provided in terms of the outer and the inner spans of the named entities. MEANTIME includes six named entity types: person, location, organization, product, financial and mixed.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Related approaches
      </section-title>
      <paragraph>
       Named entity recognition is a task with a long history in NLP. Therefore, we will summarize those approaches that are most relevant to our work, especially those we will directly compared with in Section 4. Since CoNLL shared tasks, the most competitive approaches have been supervised systems learning CRF, SVM, Maximum Entropy or Averaged Perceptron models. In any case, while the machine learning method is important, it has also been demonstrated that good performance might largely be due to the feature set used [16]. Table 2 provides an overview of the features used by previous best scoring approaches for each of the five languages we address in this paper.
      </paragraph>
      <paragraph>
       Traditionally, local features have included contextual and orthographic information, affixes, character-based features, prediction history, etc. As argued by the CoNLL 2003 organizers, no feature set was deemed to be ideal for NERC [58], although many approaches for English refer to Zhang and Johnson [61] as a useful general approach.
      </paragraph>
      <paragraph>
       Linguistic information. Some of the CoNLL participants use linguistic information (POS, lemmas, chunks, but also specific rules or patterns) for Dutch and English [12], [16], although these type of features was deemed to be most important for German, for which the use of linguistic features is pervasive [7]. This is caused by the sparsity caused by the declension cases, the tendency to form compounds containing named entities and by the capitalization of every noun [23]. For example, the best system among the 11 participants in GermEval 2014, ExB, uses morphological features and specific suffix lists aimed at capturing frequent patterns in the endings of named entities [28].
      </paragraph>
      <paragraph>
       In agglutinative languages such as Basque, which contains declension cases for named entities, linguistic features are considered to be a requirement. For example, the country name ‘Espainia’ (Spain in Basque) can occur in several forms, Espainian, Espainiera, Espainiak, Espainiarentzat, Espainiako, and many more.{sup:6} Linguistic information has been used to treat this phenomenon. The only previous work for Basque developed Eihera, a rule-based NERC system formalized as finite state transducers to take into account declension classes [4]. The features of Eihera include word, lemma, POS, declension case, capitalized lemma, etc. These features are complemented with gazetteers extracted from the Euskaldunon Egunkaria newspaper and semantic information from the Basque WordNet.
      </paragraph>
      <paragraph>
       Gazetteers. Dictionaries are widely used to inject world knowledge via gazetteer matches as features in machine learning approaches to NERC. The best performing systems carefully compile their own gazetteers from a variety of sources [12]. Ratinov and Roth [52] leverage a collection of 30 gazetteers and matches against each one are weighted as a separate feature. In this way they trust each gazetteer to a different degree. Passos et al. [48] carefully compiled a large collection of English gazetteers extracted from US Census data and Wikipedia and applied them to the process of inducing word embeddings with very good results.
      </paragraph>
      <paragraph>
       While it is possible to automatically extract them from various corpora or resources, they still require careful manual inspection of the target data. Thus, our approach only uses off the shelf gazetteers whenever they are publicly available. Furthermore, our method collapses every gazetteer into one dictionary. This means that we only add a feature per token, instead of a feature per token and gazetteer.
      </paragraph>
      <paragraph>
       Global features. The intuition behind non-local (or global) features is to treat similarly all occurrences of the same named entity in a text. Carreras et al. [12] proposed a method to produce the set of named entities for the whole sentence, where the optimal set of named entities for the sentence is the coherent set of named entities which maximizes the summation of confidences of the named entities in the set. Ratinov and Roth [52] developed three types of non-local features, analyzing global dependencies in a window of between 200 and 1000 tokens.
      </paragraph>
      <paragraph>
       Word representations. Semi-supervised approaches leveraging unlabeled text had already been applied to improve results in various NLP tasks. More specifically, it had been previously shown how to apply Brown clusters [10] for Chinese Word Segmentation [36], dependency parsing [34], NERC [55] and POS tagging [9].
      </paragraph>
      <paragraph>
       Ratinov and Roth [52] used Brown clusters as features obtaining what was at the time the best published result of an English NERC system on the CoNLL 2003 testset. Turian et al. [60] made a rather exhaustive comparison of Brown clusters, Collobert and Weston's embeddings [18] and HLBL embeddings [43] to improve chunking and NERC. They show that in some cases the combination of word representation features was positive but, although they used Ratinov and Roth's system as starting point, they did not manage to improve over the state of the art. Furthermore, they reported that Brown clustering features performed better than the word embeddings.
      </paragraph>
      <paragraph>
       Passos et al. [48] extend the Skip-gram algorithm to learn 50-dimensional lexicon infused phrase embeddings from 22 different gazetteers and the Wikipedia. The resulting embeddings are used as features by scaling them by a hyper-parameter which is a real number tuned on the development data. Passos et al. [48] report best results up to date for English NERC on CoNLL 2003 test data, 90.90 F1.
      </paragraph>
      <paragraph>
       The best German CoNLL 2003 system (an ensemble) was outperformed by Faruqui et al. [23]. They trained the Stanford NER system [24], which uses a linear-chain Conditional Random Field (CRF) with a variety of features, including lemma, POS tag, etc. Crucially, they included “distributional similarity” features in the form of Clark clusters [15] induced from large unlabeled corpora: the Huge German Corpus (HGC) of around 175M tokens of newspaper text and the deWac corpus [6] consisting of 1.71B tokens of web-crawled data. Using the clusters induced from deWac as a form of semi-supervision improved the results over the best CoNLL 2003 system by 4 points in F1.
      </paragraph>
      <paragraph>
       Ensemble systems. The best participant of the English CoNLL 2003 shared task used the results of two externally trained NERC taggers to create an ensemble system [25]. Passos et al. [48] develop a stacked linear-chain CRF system: they train two CRFs with roughly the same features; the second CRF can condition on the predictions made by the first CRF. Their “baseline” system uses a similar local featureset as Ratinov and Roth's [52] but complemented with gazetteers. Their baseline system combined with their phrase embeddings trained with infused lexicons allow them to report the best CoNLL 2003 result so far.
      </paragraph>
      <paragraph>
       The best system of the GermEval 2014 task built an ensemble of classifiers and pattern extractors to find the most likely tag sequence [28]. They paid special attention to out of vocabulary words which are addressed by semi-supervised word representation features and an ensemble of POS taggers. Furthermore, remaining unknown candidate mentions are tackled by look-up via the Wikipedia API.
      </paragraph>
      <paragraph>
       Apart from the feature types, the last two columns of Table 2 refer to whether the systems are publicly available and whether any external resources used for training are made available (e.g., induced word embeddings, gazetteers or corpora). This is desirable to be able to re-train the systems on different datasets. For example, we would have been interested in training the Stanford NER system with the full Ancora corpus for the evaluation presented in Table 16, but their Spanish cluster lexicon is not available. Alternatively, we would have liked to train our system with the same Ancora partition used to train Stanford NER, but that is not available either.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      System description
     </section-title>
     <paragraph>
      The design of ixa-pipe-nerc aims at establishing a simple and shallow feature set, avoiding any linguistic motivated features, with the objective of removing any reliance on costly extra gold annotations (POS tags, lemmas, syntax, semantics) and/or cascading errors if automatic language processors are used. The underlying motivation is to obtain robust models to facilitate the development of NERC systems for other languages and datasets/domains while obtaining state of the art results. Our system consists of:
     </paragraph>
     <list>
      <list-item label="•">
       Local, shallow features based mostly on orthographic, word shape and n-gram features plus their context.
      </list-item>
      <list-item label="•">
       Three types of simple clustering features, based on unigram matching.
      </list-item>
      <list-item label="•">
       Publicly available gazetteers, widely used in previous NERC systems [58], [44].
      </list-item>
     </list>
     <paragraph>
      Table 3 provides an example of the features generated by our system.{sup:7}
     </paragraph>
     <section label="3.1">
      <section-title>
       Local features
      </section-title>
      <paragraph>
       The local features constitute our baseline system on top of which the clustering features are added. We implement the following feature set, partially inspired by previous work [61]:
      </paragraph>
      <list>
       <list-item label="•">
        Token: Current lowercase token (w), namely, ekuadorko in Table 3.
       </list-item>
       <list-item label="•">
        Token Shape: Current lowercase token (w) plus current token shape (wc), where token shape consist of: (i) The token is either lowercase or a 2 digit word or a 4 digit word; (ii) If the token contains digits, then whether it also contains letters, or slashes, or hyphens, or commas, or periods or is numeric; (iii) The token is all uppercase letters or is an acronym or is a one letter uppercase word or starts with capital letter. Thus, in Table 31994an is a 4 digit word (4d), Ekuadorko has an initial capital shape (ic) and hiriburuan is lowercase (lc).
       </list-item>
       <list-item label="•">
        Previous prediction: the previous outcome (pd) for the current token. The previous predictions in our example are null because these words have not been seen previously, except for the comma.
       </list-item>
       <list-item label="•">
        Sentence: Whether the token is the beginning of the sentence. None of the tokens in our example is at the beginning of the sentence, so this feature is not active in Table 3.
       </list-item>
       <list-item label="•">
        Prefix: Two prefixes consisting of the first three and four characters of the current token: Eku and Ekua.
       </list-item>
       <list-item label="•">
        Suffix: The four suffixes of length one to four from the last four characters of the current token.
       </list-item>
       <list-item label="•">
        Bigram: Bigrams including the current token and the token shape.
       </list-item>
       <list-item label="•">
        Trigram: Trigrams including the current token and the token shape.
       </list-item>
       <list-item label="•">
        Character n-gram: All lowercase character bigrams, trigrams, fourgrams and fivegrams from the current token (ng).
       </list-item>
      </list>
      <paragraph>
       Token, token shape and previous prediction features are placed in a 5 token window, namely, for these three features we also consider the previous and the next two words, as shown in Table 3.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Gazetteers
      </section-title>
      <paragraph>
       We add gazetteers to our system only if they are readily available to use, but our approach does not fundamentally depend upon them. We perform a look-up in a gazetteer to check if a named entity occurs in the sentence. The result of the look-up is represented with the same encoding chosen for the training process, namely, the BIO or BILOU scheme.{sup:8} Thus, for the current token we add the following features:
      </paragraph>
      <list>
       <list-item label="1.">
        The current named entity class in the encoding schema. Thus, in the BILOU encoding we would have “unit”, “beginning”, “last”, “inside”, or if not match is found, “outside”, combined with the specific named entity type (LOC, ORG, PER, MISC, etc.).
       </list-item>
       <list-item label="2.">
        The current named entity class as above and the current token.
       </list-item>
      </list>
     </section>
     <section label="3.3">
      <section-title>
       Clustering features
      </section-title>
      <paragraph>
       The general idea is that by using some type of semantic similarity or word cluster induced over large unlabeled corpora it is possible to improve the predictions for unseen words in the test set. This type of semi-supervised learning may be aimed at improving performance over a fixed amount of training data or, given a fixed target performance level, to establish how much supervised data is actually required to reach such performance [34].
      </paragraph>
      <paragraph>
       So far the most successful approaches have only used one type of word representation [48], [23], [52]. However, our simple baseline combined with one type of word representation features are not able to compete with previous, more complex, systems. Thus, instead of encoding more elaborate features, we have devised a simple method to combine and stack various types of clustering features induced over different data sources or corpora. In principle, our method can be used with any type of word representations. However, for comparison purposes, we decided to use word representations previously used in successful NERC approaches: Brown clusters [52], [60], Word2vec clusters [48] and Clark clusters [24], [23]. As can be observed in Table 3, our clustering features are placed in a 5 token window.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Brown features
       </section-title>
       <paragraph>
        The Brown clustering algorithm [10] is a hierarchical algorithm which clusters words to maximize the mutual information of bigrams. Thus, it is a class-based bigram model in which:
       </paragraph>
       <list>
        <list-item label="•">
         the probability of a document corresponds to the product of the probabilities of its bigrams,
        </list-item>
        <list-item label="•">
         the probability of each bigram is calculated by multiplying the probability of a bigram model over latent classes by the probability of each class generating the actual word types in the bigram, and
        </list-item>
        <list-item label="•">
         each word type has non-zero probability only on a single class.
        </list-item>
       </list>
       <paragraph>
        The Brown algorithm takes a vocabulary of words to be clustered and a corpus of text containing these words. It starts by assigning each word in the vocabulary to its own separate cluster, then iteratively merges the pair of clusters which leads to the smallest decrease in the likelihood of the text corpus. This produces a hierarchical clustering of the words, which is usually represented as a binary tree, as shown in Fig. 1. In this tree every word is uniquely identified by its path from the root, and the path can be represented by a bit string. It is also possible to choose different levels of word abstraction by choosing different depths along the path from the root to the word. Therefore, by using paths of various lengths, we obtain clustering features of different granularities [40].
       </paragraph>
       <paragraph>
        We use paths of length 4, 6, 10 and 20 as features [52]. However, we introduce several novelties in the design of our Brown clustering features:
       </paragraph>
       <list>
        <list-item label="1.">
         For each feature which is token-based, we add a feature containing the paths computed for the current token. Thus, taking into account our baseline system, we will add the following Brown clustering features:
        </list-item>
        <list-item label="2.">
         Brown clustering features benefit from two additional features:
        </list-item>
       </list>
       <paragraph>
        For space reasons, Table 3 only shows the Brown Token (bt) and Brown Token Shape (c) features for paths of length 4 and 6. We use the publicly available tool{sup:9} implemented by Liang [36] with default settings. The input consists of a corpus tokenized and segmented one sentence per line, without punctuation. Furthermore, we follow previous work and remove all sentences which consist of less than 90% lowercase characters [36], [60] before inducing the Brown clusters.
       </paragraph>
      </section>
      <section label="3.3.2">
       <section-title>
        Clark features
       </section-title>
       <paragraph>
        Clark [15] presents a number of unsupervised algorithms, based on distributional and morphological information, for clustering words into classes from unlabeled text. The focus is on clustering infrequent words on a small numbers of clusters from comparatively small amounts of data. In particular, Clark [15] presents an algorithm combining distributional information with morphological information of words “by composing the Ney–Essen clustering model with a model for the morphology within a Bayesian framework”. The objective is to bias the distributional information to put words that are morphologically similar in the same cluster. We use the code released by Clark [15] off the shelf{sup:10} to induce Clark clusters using the Ney–Essen with morphological information method. The input of the algorithm is a sequence of lowercase tokens without punctuation, one token per line with sentence breaks.
       </paragraph>
       <paragraph>
        Our Clark clustering features are very simple: we perform a look-up of the current token in the clustering lexicon. If a match is found, we add as a feature the clustering class, or the lack of match if the token is not found (see Clark-a and Clark-b in Table 3).
       </paragraph>
      </section>
      <section label="3.3.3">
       <section-title>
        Word2vec features
       </section-title>
       <paragraph>
        Another family of language models that produces word representations are the neural language models. These approaches produce representation of words as continuous vectors [18], [43], also called word embeddings. Nowadays, perhaps the most popular among them is the Skip-gram algorithm [39]. The Skip-gram algorithm uses shallow log-linear models to compute vector representation of words which are more efficient than previous word representations induced on neural language models. Their objective is to produce word embeddings by computing the probability of each n-gram as the product of the conditional probabilities of each context word in the n-gram conditioned on its central word [39].
       </paragraph>
       <paragraph>
        Instead of using continuous vectors as real numbers, we induce clusters or word classes from the word vectors by applying K-means clustering. In this way we can use the cluster classes as simple binary features by injecting unigram match features. We use the Word2vec tool{sup:11} released by Mikolov et al. [39] with a 5 window context to train 50-dimensional word embeddings and to obtain the word clusters on top of them. The input of the algorithm is a corpus tokenized, lowercased, with punctuation removed and in one line. The Word2vec features are implemented exactly like the Clark features.
       </paragraph>
      </section>
      <section label="3.3.4">
       <section-title>
        Stacking and combining clustering features
       </section-title>
       <paragraph>
        We successfully combine clustering features from different word representations. Furthermore, we also stack or accumulate features of the same type of word representation induced from different data sources, trusting each clustering lexicon to a different degree, as shown by the five encoded clustering features in Table 3: two Clark and Word2vec features from different source data and one Brown feature. When using word representations as semi-supervised features for a task like NERC, two principal factors need to be taken into account: (i) the source data or corpus used to induce the word representations and (ii) the actual word representation used to encode our features which in turn modify the weight of our model's parameters in the training process.
       </paragraph>
       <paragraph>
        For the clustering features to be effective the induced clusters need to contain as many words appearing in the training, development and test sets as possible. This can be achieved by using corpora closely related to the text genre or domain of the data sets or by using very large unlabeled corpora which, although not closely domain-related, be large enough to include many relevant words. For example, with respect to the CoNLL 2003 English dataset an example of the former would be the Reuters corpus while the Wikipedia would be an example of the latter.
       </paragraph>
       <paragraph>
        The word representations obtained by different algorithms would capture different distributional properties of words in a given corpus or data source. Therefore, each type of clustering would allow us to capture different types of occurring named entity types. In other words, combining and stacking different types of clustering features induced over a variety of data sources should help to capture more similarities between different words in the training and test sets, increasing the contribution to the weights of the model parameters in the training process.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="4">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      In this Section we report on the experiments performed with the ixa-pipe-nerc system as described in the previous section. The experiments are performed in 5 languages: Basque, Dutch, English, German and Spanish. For comparison purposes, in-domain results are presented in Section 4.1 using the most common NERC datasets for each language as summarized in Table 1. Section 4.2 analyzes the performance when reducing training data and Section 4.3 presents eight out-of-domain evaluations for three languages: Dutch, English and Spanish.
     </paragraph>
     <paragraph>
      The results for Dutch, English and Spanish do not include trigrams and character n-grams in the local featureset described in Section 3.1, except for the models in each in-domain evaluation which are marked with “charngram 1:6”.
     </paragraph>
     <paragraph>
      We also experiment with dictionary features but, in contrast to previous approaches such as Passos et al. [48], we only use currently available gazetteers off-the-shelf. For every model marked with “dict” we use the thirty English Illinois NER gazetteers [52], irrespective of the target language. Additionally, the English models use six gazetteers about the Global Automotive Industry provided by LexisNexis to the Newsreader project,{sup:12} whereas the German models include, in addition to the Illinois gazetteers, the German dictionaries distributed in the CoNLL 2003 shared task. The gazetteers are collapsed into one large dictionary and deployed as described in Section 3.2.
     </paragraph>
     <paragraph>
      Finally, the clustering features are obtained by processing the following clusters from publicly available corpora: (i) 1000 Brown clusters; (ii) Clark and Word2vec clusters in the 100-600 range. To choose the best combination of clustering features we test the available permutations of Clark and Word2vec clusters with and without the Brown clusters on the development data. Table 4 provides details of every corpus used to induce the clusters. For example, the first row reads: “Reuters RCV1 was used; the original 63 million words were reduced to 35 million after pre-processing for inducing Brown clusters. Clark and Word2vec clusters were trained on the whole corpus”. The pre-processing and tokenization is performed with the IXA pipes tools [1].
     </paragraph>
     <paragraph>
      Every evaluation is carried out using the CoNLL NER evaluation script.{sup:13} The results are obtained with the BILOU encoding for every experimental setting except for German CoNLL 2003.
     </paragraph>
     <section label="4.1">
      <section-title>
       In-domain evaluation
      </section-title>
      <paragraph>
       In this section the results are presented by language. In two cases, Dutch and German, we use two different datasets, making it a total of seven in-domain evaluations.
      </paragraph>
      <section label="4.1.1">
       <section-title>
        English
       </section-title>
       <paragraph>
        We tested our system in the highly competitive CoNLL 2003 dataset. Table 5 shows that three of our models outperform previous best results reported for English in the CoNLL 2003 dataset [48]. Note that the best F1 score (91.36) is obtained by adding trigrams and character n-gram features to the best model (91.18). The results also show that these models improve the baseline provided by the local features by around 7 points in F1 score. The most significant gain is in terms of recall, almost 9 points better than the baseline.
       </paragraph>
       <paragraph>
        We also report very competitive results, only marginally lower than Passos et al. [48], based on the stacking and combination of clustering features as described in Section 3.3.4. Thus, both best cluster and comp models, based on local plus clustering features only, outperform very competitive and more complex systems such as those of Ratinov and Roth [52] and Turian et al. [60]. The stacking and combining effect manifests itself very clearly when we compare the single clustering feature models (BR, CW600, W2VG200 and W2VW400) with the light, comp and best cluster models which improve the overall F1 score by 1.30, 1.72 and 1.85 respectively over the best single clustering model (CW600).
       </paragraph>
       <paragraph>
        It is worth mentioning that our models do not score best in the development data. As the development data is closer in style and genre to the training data [52], this may suggest that our system generalizes better on test data that is not close to the training data; indeed, the results reported in Section 4.3 seem to confirm this hypothesis.
       </paragraph>
       <paragraph>
        We also compared our results with respect to the best two publicly available English NER systems trained on the same data. We downloaded the Stanford NER system distributed in the 2015-01-30 package. We evaluated their CoNLL model and, while the result is substantially better than their reference paper [24], our clustering models obtain better results. The Illinois NER tagger is used by Ratinov and Roth [52] and Turian et al. [60], both of which are outperformed by our system.
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        German
       </section-title>
       <paragraph>
        We tested our system in the GermEval 2014 dataset. Table 6 compares our results with the best two systems (ExB and UKP) by means of the M3 metric, which separately analyzes the performance in terms of the outer and inner named entity spans. Table 6 makes explicit the significant improvements achieved by the clustering features on top of the baseline system, particularly in terms of recall (almost 11 points in the outer level). The official results of our best configuration (de-cluster-dict) are reported in Table 7 showing that our system marginally improves the best systems' results on that task (ExB and UKP).
       </paragraph>
       <paragraph>
        We also compare our system, in the last three rows, with the publicly available GermaNER [8], which reports results for the 4 main outer level entity types (person, location, organization and other). For this experiment we trained the de-cluster and de-cluster + dict models on the four main classes, improving GermaNER's results by almost 3 F1 points. The GermaNER method of evaluation is interesting because allows researchers to directly compare their systems with a publicly available system trained on GermEval data.
       </paragraph>
       <paragraph>
        Table 8 compares our German CoNLL 2003 results with the best previous work trained on public data. Our best CoNLL 2003 model obtains results similar to the state of the art performance with respect to the best system published up to date [23] using public data. Faruqui et al. [23] also report 78.20 F1 with a model trained with Clark clusters induced using the Huge German Corpus (HGC). Unfortunately, the corpus or the induced clusters were not available.
       </paragraph>
      </section>
      <section label="4.1.3">
       <section-title>
        Spanish
       </section-title>
       <paragraph>
        The best system up to date on the CoNLL 2002 dataset, originally published by Carreras et al. [12], is distributed as part of the Freeling library [47]. Table 9 lists four models that improve over their reported results, almost by 3 points in F1 measure in the case of the es-cluster model (with our without trigram and character n-gram features).
       </paragraph>
      </section>
      <section label="4.1.4">
       <section-title>
        Dutch
       </section-title>
       <paragraph>
        Despite using clusters from one data source only (see Table 4), results in Table 10 show that our nl-cluster model outperforms the best result published on CoNLL 2002 [16] by 3.83 points in F1 score. Adding the English Illinois NER gazetteers [52] and trigram and character n-gram features increases the score to 85.04 F1, 5.41 points better than previous published work on this dataset.
       </paragraph>
       <paragraph>
        We also compared our system with the more recently developed SONAR-1 corpus and the companion NERD system distributed inside its release [21]. They report 84.91 F1 for the six main named entity types via 10-fold cross validation. For this comparison we chose the local, nl-cluster and nl-cluster-dict configurations from Table 10 and run them on SONAR-1 using the same settings. The results reported in Table 11 shows our system's improvement over previous results on this dataset.
       </paragraph>
      </section>
      <section label="4.1.5">
       <section-title>
        Basque
       </section-title>
       <paragraph>
        Table 12 reports on the experiments using the Egunkaria NER dataset provided by Alegria et al. [4]. Due to the sparsity of the MISC class mentioned in Section 2.1, we decided to train our models on three classes only (location, organization and person). Thus, the results are obtained training our models in the customary manner and evaluating on 3 classes. However, for direct comparison with previous work [4], we also evaluate our best eu-cluster model (trained on 3 classes) on 4 classes.
       </paragraph>
       <paragraph>
        The results show that our eu-cluster model clearly improves upon previous work by 4 points in F1 measure (75.40 vs 71.35). These results are particularly interesting as it had been so far assumed that complex linguistic features and language-specific rules were required to perform well for agglutinative languages such as Basque [4]. Finally, it is worth noting that the eu-cluster model increases the overall F1 score by 11.72 over the baseline, of which 10 points are gained in precision and 13 in terms of recall.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Reducing training data
      </section-title>
      <paragraph>
       So far, we have seen how, given a fixed amount of supervised training data, leveraging unlabeled data using multiple cluster sources helped to obtain state of the art results in seven different in-domain settings for five languages. In this section we will investigate to what extent our system allows to reduce the dependency on supervised training data.
      </paragraph>
      <paragraph>
       We first use the English CoNLL 2003 dataset for this experiment. The training set consists of around 204K words and we use various smaller versions of it to test the performance of our best cluster model reported in Table 5. Table 13 displays the F1 results of the baseline system consisting of local features and the best cluster model. The Δ column refers to the gains of our best cluster model with respect to the baseline model for every portion of the training set.
      </paragraph>
      <paragraph>
       While we have already commented the substantial gains obtained simply by adding our clustering features, it is also interesting to note that the gains are much substantial when less supervised training data is available. Furthermore, it is striking that training our clustering features using only one eight of the training data (30K words) allows to obtain similar performance to the baseline system trained on the full training set. Equally interesting is the fact that cutting by half the training data only marginally harms the overall performance. Finally, training on just a quarter of the training set (60K) results in a very competitive model when compared with other publicly available NER systems for English trained on the full training set: it roughly matches Stanford NER's performance, it outperforms models using external knowledge or non-local features reported by Ratinov and Roth [52], and also several models reported by Turian et al. [60], which use one type of word representations on top of the baseline system.
      </paragraph>
      <paragraph>
       We have also re-trained the Illinois NER system [52] and our best CoNLL 2003 model (en-91-18) for comparison. First, we can observe that for every portion of the training set, both our best cluster and en-91-18 model outperform the Illinois NER system. The best cluster results are noteworthy because, as opposed to Illinois NER, it does not use gazetteers or global features for extra performance.
      </paragraph>
      <paragraph>
       These results are mirrored by those obtained for the rest of the languages and datasets. Thus, Table 14 displays, for each language, the F1 results of the baseline system and of the best cluster models on top of the baseline.{sup:14} Overall, it confirms that our cluster-based models obtain state of the art results using just one half of the data. Furthermore, using just one quarter of the training data we are able to match results of other publicly available systems for every language, outperforming in some cases, such as Basque, much complex systems of classifiers exploiting linguistic specific rules and features (POS tags, lemmas, semantic information from WordNet, etc.). Considering that Basque is a low-resourced language, it is particularly relevant to be able to reduce as much as possible the amount of gold supervised data required to develop a competitive NERC system.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Out-of-domain evaluations
      </section-title>
      <paragraph>
       NERC systems are often used in out-of-domain settings, namely, to annotate data that greatly differs from the data from which the NERC models were learned. These differences can be of text genre and/or domain, but also because the assumptions of what constitutes a named entity might differ. It is therefore interesting to develop robust NERC systems across both domains and datasets. In this section we demonstrate that our approach, consisting of basic, general local features and the combination and stacking of clusters, produces robust NERC systems in three out-of-domain evaluation settings:
      </paragraph>
      <list>
       <list-item label="•">
        Class disagreements: Named entities are assigned to different classes in training and test.
       </list-item>
       <list-item label="•">
        Different text genre: The text genre of training and test data differs.
       </list-item>
       <list-item label="•">
        Annotation guidelines: The gold annotation of the test data follows different guidelines from the training data. This is usually reflected in different named entity spans.
       </list-item>
      </list>
      <paragraph>
       The datasets and languages chosen for these experiments are based on the availability of both previous results and publicly distributed NERC systems to facilitate direct comparison of our system with other approaches. Table 15 specifies the datasets used for each out-of-domain setting and language. Details of each dataset can be found Table 1.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Class disagreements
       </section-title>
       <paragraph>
        MUC 7 annotates seven entity types, including four that are not included in CoNLL data: DATE, MONEY, NUMBER and TIME entities. Furthermore, CoNLL includes the MISC class, which was absent in MUC 7. This means that there are class disagreements in the gold standard annotation between the training and test datasets. In addition to the four CoNLL classes, SONAR-1 includes PRODUCT and EVENT whereas Ancora also annotates DATE and NUMBER. For example, consider the following sentence of the MUC 7 gold standard (example taken from Ratinov and Roth [52]): “…baloon, called the Virgin Global Challenger.” The gold annotation in MUC 7 establishes that there is one named entity: “…baloon, called [ORG Virgin] Global Challenger.” However, according to CoNLL 2003 guidelines, the entire name should be annotated like MISC: “…baloon, called [MISC Virgin Global Challenger].” In this setting some adjustments are made to the NERC systems' output. Following previous work [52], every named entity that is not LOC, ORG, PER or MISC is labeled as ‘O’. Additionally for MUC 7 every MISC named entity is changed to ‘O’. For English we used the models reported in Section 4.1.1. For Spanish and Dutch we trained our system with the Ancora and SONAR-1 corpora using the configurations described in Sections 4.1.3 Spanish, 4.1.4 Dutch respectively. Table 16 compares our results with previous approaches: using MUC 7, Turian et al. [60] provide standard phrase results whereas Ratinov and Roth [52] score token based F1 results, namely, each token is considered a chunk, instead of considering multi-token spans too. For Spanish we use the Stanford NER Spanish model (2015-01-30 version) trained with Ancora. For Dutch we compare our SONAR-1 system with the companion system distributed with the SONAR-1 corpus [21]. The results are summarized in Table 16.
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Text genre
       </section-title>
       <paragraph>
        In this setting the out-of-domain character is given by the differences in text genre between the English CoNLL 2003 set and the Wikigold corpus. We compare our system with English models trained on large amounts of silver-standard text (3.5M tokens) automatically created from the Wikipedia [46]. They report results on Wikigold showing that they outperformed their own CoNLL 2003 gold-standard model by 10 points in F1 score. We compare their result with our best cluster model in Table 17. While the results of our baseline model confirms theirs, our clustering model score is slightly higher. This result is interesting because it is arguably more simple to induce the clusters we use to train ixa-pipe-nerc rather than create the silver standard training set from Wikipedia as described in Nothman et al. [46].
       </paragraph>
      </section>
      <section label="4.3.3">
       <section-title>
        Annotation guidelines
       </section-title>
       <paragraph>
        In this section the objective is studying not so much the differences in textual genre as the influence of substantially different annotation standards. We only use three classes (location, organization and person) to evaluate the best models presented for in-domain evaluations labeling ‘O’ every entity which is not LOC, ORG or PER.
       </paragraph>
       <paragraph>
        The text genre of MEANTIME is not that different from CoNLL data. However, differences in the gold standard annotation result in significant disagreements regarding the span of the named entities [59]. For example, the following issues are markedly different with respect to the training data we use for each language:
       </paragraph>
       <list>
        <list-item label="•">
         Different criteria to decide when a named entity is annotated: in the expression “40 billion US air tanker contract” the MEANTIME gold standard does not mark ‘US’ as location, whereas in the training data this is systematically annotated.
        </list-item>
        <list-item label="•">
         Mentions including the definite article within the name entity span: ‘the United States’ versus ‘United States’.
        </list-item>
        <list-item label="•">
         Longer extents containing common nouns: in the MEANTIME corpus there are many entities such as “United States airframer Boeing”, which in this case is considered an organization, whereas in the training data this span will in general consists of two entities: ‘United States’ as location and ‘Boeing’ as organization.
        </list-item>
        <list-item label="•">
         Common nouns modifying the proper name: ‘Spokeswoman Sandy Angers’ is annotated as a named entity of type PER whereas in the training data used the span of the named entity would usually be ‘Sandy Angers’.
        </list-item>
       </list>
       <paragraph>
        CoNLL NER phrase based evaluation punishes any bracketing error as both false positive and negative. Thus, these span-related disagreements make this setting extremely hard for models trained according to other annotation guidelines, as shown by Table 18. Our baseline models degrade around 40 F1 points and the cluster-based models around 35. Other systems' results worsen much more, especially for Spanish and Dutch. The token-based scores are in general better but the proportion in performance between systems across languages is similar.
       </paragraph>
       <paragraph>
        As an additional experiment, we also tested the English model recommended by Stanford NER which is trained for three classes (LOC, PER, ORG) using a variety of public and (not identified) private corpora (referred to as Stanford NER 3 class (ALL) in Table 19). The results with respect to their CoNLL model improved by around 3 points in F1 score across named entity labels and evaluation types (phrase or token based). In view of these results, we experimented with multi-corpora training data added to our best CoNLL 2003 model (en-91-18). Thus, we trained using three public training sets: MUC 7, CoNLL 2003 and Ontonotes 4.0. The local model with the three training sets (Local ALL) improved 12 and 17 points in F1 score across evaluations and entity types, outperforming our best model trained only with CoNLL 2003. Adding the clustering features gained between 2 and 5 points more surpassing the Stanford NER 3 class multi-corpora model in every evaluation. We believe that the main reason to explain these improvements is the variety and quantity of annotations provided by Ontonotes (1M word corpus), and to a lesser extent by MUC 7, which includes some spans containing common nouns and determiners making the model slightly more robust regarding the mention spans.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      Despite the simplicity of the ixa-pipe-nerc approach, we report best results for English in 4 different datasets: for CoNLL 2003 and for the three English out-of-domain evaluations. For German we improve the results of the best system in the GermEval 2014 task and obtain comparable results to previous work in the CoNLL 2003 dataset using publicly available data. In Spanish we provide results on CoNLL 2002 and in two out-of-domain evaluations clearly outperforming previous best results. For Dutch we improve over previous results in CoNLL 2002 and SONAR-1 data and two out-of-domain evaluations. Finally, for Basque (Egunkaria) the improvements are considerable.
     </paragraph>
     <paragraph>
      Simple and shallow features. These results are obtained without linguistic or global features. Instead, injecting unigram knowledge from the combination and stacking of clusters allows to obtain a robust NERC system across languages, outperforming other, more complex [52], [60], [21], [48] and language-specific systems. This is also the case for languages such as Basque or German, where the use of linguistic features (lemmas, POS tags, curated suffix lists and rules, etc.) has so far been pervasive [4], [7], [8].
     </paragraph>
     <paragraph>
      Minimal human intervention. Each of the datasets used displays an idiosyncratic annotation and genre. This is even the case for the NER tasks organized at CoNLL 2002 and 2003: “For instance, Spanish marks no lowercase adjectival nationalities and includes 192 instances where surrounding quotes are included in the entity annotation; Dutch has as PER the initials of photographers; and English has lots of financial and sports data in tables” [46].
     </paragraph>
     <paragraph>
      In despite of this, our best in-domain results were obtained using the same set of features for all seven evaluations, which included trigrams and character n-grams. The only variable across datasets and languages was the number of classes of the clustering lexicons used.
     </paragraph>
     <paragraph>
      However, the in-domain results also manifest that trigrams and character n-grams can be omitted for languages without declension cases or repeated suffixes in the named entities (e.g., Dutch, English and Spanish) without it being too detrimental. In fact, we started experimenting without trigrams and character n-grams for Dutch, English and Spanish. When we added them to the best model of each language (e.g, charngram 1:6 en-91-18 in Table 5), the in-domain results improved or remained quite similar but at the cost of making the models less robust in the out-of-domain evaluations. In contrast, trigrams and character n-grams were highly beneficial in both in-domain and out-of-domain settings for Basque and German.
     </paragraph>
     <paragraph>
      Our take on this issue is that trigram and character n-gram features would only be required to address inflected named entities (in Basque) or to learn repeated suffixes appearing in named entities and to tackle sparsity (in both Basque and German). For example, Table 3 shows the utility of character n-gram features capturing the Basque locative declension case -ko, which is repeated for many location entities in the training data.
     </paragraph>
     <paragraph>
      The emphasis on clustering features for good performance (as opposed to local features) produces an easily exportable and robust system for both in-domain and out-of-domain evaluations and across languages. It is therefore crucial, for competitive performance, to understand which clustering methods and corpora use as well as how to combine them effectively.
     </paragraph>
     <paragraph>
      Choosing the right corpus and clustering method. Contrary to previous suggestions that the larger the number of classes and the corpus used to induced the clusters the better [60], our results provide a number of interesting pointers to choose the appropriate type of corpus and clustering method required for optimal performance.
     </paragraph>
     <paragraph>
      With respect to Brown clusters, all our results are better when we induce 1000 classes. We systematically tried for every language and data source with less (320) and more (3200) classes without performance improvement. Moreover, in every evaluation setting the best results with Brown clusters were obtained when a corpus relatively closed in-domain, genre and date was used, even if significantly smaller. This is especially clear for Basque, English and Spanish where the best Brown clusters were induced over the smallest corpora (Egunkaria, Reuters RCV1 and El Periodico, respectively).
     </paragraph>
     <paragraph>
      In contrast, results show that Word2vec clusters, unlike Brown, always benefit from very large amounts of data, regardless of domain or temporal issues. Our experiments also suggest that Clark clusters seem to behave more robustly than Brown clusters with respect to the size and type of text, performing well with large unrelated and smaller domain-specific corpora. For best performance, Clark [15] recommends that the proportion of clusters k with respect to the source data should be of {a mathematical formula}k3≈n where n is the number of words in the corpus. Instead, we systematically induce, for every corpus, Clark clusters in the range of 100–600 classes, because preliminary experiments proved that over 600 classes, even if the proportion proposed by Clark holds, performance starts to deteriorate.{sup:15} Following this, we are now in better position to address the questions posed by Turian et al. [60]:
     </paragraph>
     <list>
      <list-item label="•">
       Brown clusters benefit from source data closely related to the testset, even if small in size.
      </list-item>
      <list-item label="•">
       Clark clusters behave robustly with respect to the size or type of data sources from which they are induced.
      </list-item>
      <list-item label="•">
       For Word2vec clusters size is the most important factor: the larger the corpus the better.
      </list-item>
     </list>
     <paragraph>
      Should we prefer certain word features? While Clark features seem to obtain the best results overall, our work provides a very simple method of effectively combining them, depending on the data sources we have available.
     </paragraph>
     <paragraph>
      Combination and stacking. We use three different data sources, namely, Wikipedia, Egunkaria and Berria (see Table 4 for the list of unlabeled corpora used) for the Basque experiments. In order to understand better our approach, we annotated the Basque testset with every model in Table 12 and manually inspected their output. The following two examples illustrate how our approach works:
     </paragraph>
     <list>
      <list-item label="•">
       Ekuadorko: In addition to the eu-cluster model, the Brown model (BE), and the Clark Wikipedia model (CW200) provide the correct annotation. The assigned clusters in BE and CW200 clustering lexicons clearly consist of locations. For example, the 176 cluster of CW200 contains Gasteizko, Arabako, Espainiako, etc., which, unlike Ekuadorko, do occur in the training set.{sup:16} Most interestingly, while Gasteizko is only labeled as location in the training set, both Arabako and Espainiako are labeled as, depending on the context, organization or location.
      </list-item>
      <list-item label="•">
       Ameriketara (to America): Only the Brown model (and the eu-cluster) correctly labels it as a location. In this case, the 011110011100 Brown path clusters Ameriketara with other locations such as Baionara and Espainiara, among others, which, unlike Ameriketara, are contained in the training set.{sup:17}
      </list-item>
     </list>
     <paragraph>
      The same phenomenon can be observed for languages quite different from Basque such as English or Spanish. For example, the named entity ‘Uzbekistan’ is not present in the English CoNLL 2003 training data, whereas in the test set can be found four times, all of them locations. The local model annotates all four occurrences as organization (see Table 5 for references to models). The Brown and the Word2vec models, two as locations and two as organizations, because the cluster companions of ‘Uzbekistan’ are of mixed nature. Finally, the Clark model (CW600) does correctly annotate them as locations (also best-cluster, en-91-18, en-91-36 …): ‘Uzbekistan’ is placed in the 145 cluster, which contains mostly locations contained in the training data (Spain, Ireland, etc.).
     </paragraph>
     <paragraph>
      Previous approaches to NERC combining clusters or word embeddings have obtained mixed results [60]. Up until now best results have been based on rather complex systems which also used one type clustering or embedding feature [48], [52], [23], [7]. In other sequence labeling tasks, Biemann [9] reports a slight improvement (from 97.33 to 97.43 word accuracy) in POS tagging combining two types of clustering methods (one of them was Clark [15]) for German.
     </paragraph>
     <paragraph>
      Our system displays two important differences with respect to previous approaches. First, the differences between our baseline system and the, for example, Clark features are much larger than in previous work (with the exception of Faruqui et al. [23]), ranging from 2.2 and 5.5 points in F1 measure across the in-domain evaluations to 2–8 points for out-of-domain results. For example, our English CoNLL 2003 single clustering models are similar to the best CoNLL 2003 model distributed by the Stanford NER. If we consider the combined clustering models, the differences over the baseline increase to 5–10 points of F1 measure for in-domain evaluations and between 4–22 in out-of-domain settings.
     </paragraph>
     <paragraph>
      Second, our combination of clustering features significantly increases the performance over the models using only one type of clustering feature. The improvements range over 2 to 6 points in F1 measure for in-domain and out-of-domain results.
     </paragraph>
     <paragraph>
      In our opinion, these results are quite interesting as previous experiments combining features of different word representations for NERC [60], while increasing the overall result, did not improve over the state of the art at the time [52]. The results also show that leaning heavily on the clustering features (instead of specific feature tuning) for performance proves very beneficial in out-of-domain settings.
     </paragraph>
     <paragraph>
      Robust in out-of-domain settings. The results of the eight out-of-domain evaluations undertaken suggest that differences regarding named entities spans as described in Section 4.3.3 are harder to overcome than disagreements in text genre (e.g. Section 4.3.2) or entity type (Section 4.3.1). Thus, our method using multiple clustering sources allow to overcome better any differences in named entity type or text genre. However, and even though our system obtains state of the art results in every evaluation, trying to adapt to differences in named entity shape and span proves to be a much more difficult task, hence the comparatively lower results obtained in the MEANTIME evaluations.
     </paragraph>
     <paragraph>
      Robust reducing training data. Koo et al. [34] present learning curves showing the increase in performance when using Brown clusters for dependency parsing whereas Biemann [9] provides learning curves to measure the impact of clusters for NERC and chunking. Inspired by those two previous works we measured the performance when training data is reduced. Unlike these two approaches, the differences between adding clusters or not to our system with less training data is huge. Table 14 shows that differences adding the clustering features with half the data is around 8 points in F1 score (for Spanish the difference is 3.42 F1).
     </paragraph>
     <paragraph>
      Another common point of our clustering features with Koo et al. [34] is that when gold training data is reduced, the system still obtains competitive results with respect to previous approaches or publicly available systems using only a fraction (half or a quarter) of the data. If we consider the ability of our system to be competitive with substantial reductions in gold training data plus the fact that no linguistic motivated features are required, we are providing a system which is much cheaper to train for new languages and/or domains contributing therefore to alleviate the dependency on gold training data to obtain good performing NERC systems for new languages, domains or genres.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>