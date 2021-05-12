<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Feature assembly method for extracting relations in Chinese.
   </title>
   <abstract>
    The goal of relation extraction is to detect relations between two entities in free text. In a sentence, a relation instance usually comprises a small number of words, which yields a sparse feature representation. To make better use of limited information in a relation instance, parsing trees and combined features are employed widely to capture the local dependencies of relation instances. However, the performance of parsing tree-based systems is often degraded by chunking or parsing errors. Combined features are used widely, but few studies have addressed how features can be combined to achieve optimal performance. Thus, in this study, we propose a feature assembly method for relation extraction. Six types of candidate features (head noun, POS tag, n-gram, omni-word, etc.) are employed as atomic features and six constraint conditions (singleton, position, syntax, etc.) are used to combine these features in different settings. Depending on the utilization of candidate features, different constraint conditions can be explored to achieve the optimal extraction performance. Our method is effective for capturing local dependencies and it reduces the errors caused by inaccurate parsing. We tested the proposed method using the ACE 2005 Chinese and English corpora, and it achieved state-of-the-art performance, where it was significantly superior to existing methods.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The goal of relation extraction is to recognize and extract relations among entities and semantic concepts. It is expected that relation extraction can locate specific information desired by users, so users do not have to browse the many hundreds of documents returned by traditional information retrieval systems. The extracted relations can directly answer questions such as: “who is the founder of this company?”, “where was he born?”, etc. Finding the relations of an entity is an effective method for previewing an entity and it can be used to construct a knowledge base or to build a question answering system [33], [26]. Recently, relation extraction has been a very active field and the research community has developed some standard methods for simple system assessment, e.g., ACE evaluation.{sup:1}
     </paragraph>
     <paragraph>
      At present, relation extraction is often formulated as a classification problem, where a relation takes two entities as arguments (referred to as E1 and E2). Given two entities in a relation mention,{sup:2} the task is to classify the relation type between them. The major challenge for relation extraction is that most relation instances occur within a sentence or clause, and they usually consist of only a few words, which often leads to a sparse feature representation. Therefore, it is important to make better use of the available information (e.g., local dependency) contained in a relation instance. Tree kernel-based methods use parsing trees to capture the local dependencies of relation instances [62], [13]. However, even in English where an abundance of tools is available, studies have shown that “deeper” analysis may result in worse performance due to inaccurate chunking or parsing [73]. Instead, previous research has shown that the local dependency context around relation arguments is often more helpful for avoiding the errors introduced by imperfect tools, e.g., the path-enclosed tree [68].
     </paragraph>
     <paragraph>
      In the present study, we focus mainly on relation extraction from free Chinese text. Some previous studies of English relation extraction are also described in Section 6.2. In Chinese natural language processing (NLP), an additional challenge is that Chinese words are written next to each other without delimiters in between. The lack of orthographic words makes Chinese word segmentation very difficult. In Chinese, a single sentence often has several segmentation paths, which leads to the problem of segmentation ambiguity [29]. Moreover, the missing delimiters between Chinese words can also cause the out-of-vocabulary (OOV) problem [21]. For example, in the ACE corpus ‘大安森林公园’ (Daan Forest Park) is annotated as a “Facilities” entity, which can be processed as a single word, where ‘大安’ is the name of city where the forest park is located. However, if a Chinese word segmenter fails to recognize this phrase, it may be falsely segmented into four words ‘大/安/森林/公园’ (big/safe/forest/park), which is fundamentally flawed (‘大/安/’, ‘Big/Safe’). The problem becomes worse when considering the large number of Chinese characters and words. For example, the Modern Chinese Dictionary includes 13,000 characters and 69,000 words. State-of-the-art Chinese OOV extraction systems can achieve only 75% recall [74]. Thus, any errors caused by false segmentation and OOV will accumulate and propagate to subsequent processing (e.g., parsing, part-of-speech tagging, and chunking).
     </paragraph>
     <paragraph>
      Based on the characteristics of Chinese, we proposed an omni-word feature and a soft constraint method for Chinese relation extraction in our previous study [9], but many details of the omni-word feature and soft constraint were not fully explored. First, several critical issues related to the omni-word feature (e.g., lexicon size and comparing with n-grams) were not discussed. Second, the omni-word feature and soft constraint were employed together, and their individual effects were not studied. Third, the method was only evaluated using a Chinese corpus.
     </paragraph>
     <paragraph>
      The proposed method is an extension of that reported in [9]. To facilitate a systematic investigation, we also propose a feature assembly method to explore the utilization of combined features for Chinese and English relation extraction. Moreover, the constraint conditions are extended to include more patterns for capturing local dependency information. In particular, the main contributions of this study are as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       A feature assembly method is proposed that uses constraint conditions to generate combined features for capturing local dependency information.
      </list-item>
      <list-item label="2.">
       We discuss four issues related to the feature assembly method: omni-word feature, constraint conditions, feature assembly, and negative instances.
      </list-item>
      <list-item label="3.">
       A feature assembly method is developed to explore the utilization of combined features for Chinese and English relation extraction.
      </list-item>
     </list>
     <paragraph>
      The rest of this paper is organized as follows. Section 2 introduces related research. Section 3 introduces the candidate features. Section 4 presents the feature assembly method and a discussion of the constraint conditions is provided. In Section 5, we described multiple experiments, which we conducted to extensively explore several important features of our approach. In Section 6, we compare our method with other existing techniques using ACE 2005 Chinese and English corpora. Our conclusions are given in Section 7.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Two paradigms are employed to extract the relationships between entities: open relation extraction (ORE) and traditional relation extraction (TRE) [4].
     </paragraph>
     <paragraph>
      In the ORE paradigm, ORE systems often deal with massive and heterogeneous corpora to extract undefined relations in a dynamic manner (e.g., plain text [2], tables [61], or Wikipedia [55], [18], [11]). Based on this paradigm, various techniques have been proposed, e.g., distant supervision [37], [56], [53] and bootstrapping algorithms [25], [34], [54], matrix factorization [46], and tree kernels [57]. External sources are often used to guide the extraction process, e.g., Freebase [37], patterns [5], [39], ontologies [38], or integrated analysis [40]. ORE systems often benefit from the adequateness of information in an open field [5] and thousands of relations can be generated dynamically [18]. In general, additional strategies are employed to filter uninformative extraction results, e.g., syntactic or semantic constraints [14], a discriminative clustering framework [16], partial supervision [3], and matrix completion [15].
     </paragraph>
     <paragraph>
      TRE usually extracts relation instances with predefined relation types, where supervised techniques are commonly used, e.g., kernel methods [69], [62], [12], [52], belief network [47], linear programming [48], maximum entropy [24], support vector machines [76], deep neural networks [63], or predefined rules [35]. They can be roughly classified into feature-based methods and kernel-based methods. TRE systems are often trained using a manually annotated corpus, so they are can generally achieve robust performance. However, the scalability of TRE is limited by the requirement for an annotated corpus. To address this deficiency, domain adaptation is used to compensate for the mismatch between source domains and target domains [44], [42], [41]. Many techniques have been proposed to include and induce more features for classification [44], [42], [76], [24].
     </paragraph>
     <paragraph>
      Many kernel-based methods have been developed in the field of Chinese relation extraction. For example, Liu et al. [31], [32] presented a convolution tree kernel-based method that incorporates semantic similarity measures. Zhang et al. [66] proposed a composite kernel method that merges an entity kernel and string semantic similarity kernel, while Che et al. [7] proposed an improved edit-distance kernel. However, despite the popularity of kernel-based methods, after experimenting with different kernel methods, Huang et al. [22] found that simply migrating kernel methods from English to Chinese relation extraction does not work well. Li et al. [28] and Chen et al. [10] also noted that the degradation in performance may be due to the inaccuracy of Chinese segmentation and parsing processes.
     </paragraph>
     <paragraph>
      For Chinese feature-based methods, Che et al. [8] proposed a feature-based model that utilizes lexical information around entities. Zhang et al. [71] explored structure features between two entities. Li et al. [28] presented a model that includes nine structures between two entities (“nested”, “separated”, etc.). Lin et al. [30] employed a mixed model that combines both feature-based and tree kernel-based methods. Zhang et al. [72] employed a memory-based learning method and their approach is sufficiently flexible to accommodate additional linguistic features. In order to reduce the errors introduced by syntactic or semantic analysis, Chen et al. [10] proposed a model for Chinese relation extraction based on a deep belief network. A Chinese ORE system was also developed by Qiu et al. [45], which filters relation candidates with a double propagation algorithm.
     </paragraph>
     <paragraph>
      In the present study, we propose a feature assembly method. Before providing the details of this method, we introduce the candidate feature sets in the next section.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Feature sets
     </section-title>
     <paragraph>
      Relation extraction can be formulated as a classification problem, where the construction and selection of discriminative features are critical for classification. Many features have been explored [24], [76] and the proposed features are often used directly without distinguishing the roles they play in the overall feature set. For example, some features may be more “atomic” and they can be combined with other features. In our method, we use “candidate features” to denote features that are atomic and inseparable, and that can be used to generate combined features. We use the following candidate features: entity type and subtype, head noun, entity structure, POS tag, n-gram, and omni-word. These features are used with relevant information (e.g., position information or other features) to generate combined features (as discussed in Section 4).
     </paragraph>
     <paragraph>
      Entity type and subtype: In the ACE 2005 Chinese corpus, there are seven entity types (person, organization, GPE, location, facility, weapon, and vehicle) and 44 subtypes (e.g., group, government, and continent). These entity types and subtypes are manually annotated and they are provided in an evaluation corpus. They are critical for relation extraction and are used widely in this field.
     </paragraph>
     <paragraph>
      Head noun: According to the annotation guidelines, an entity is an object or set of objects in the world. An entity mention is a reference to an entity. An entity mention is annotated with its full extent and its head. An extent mention includes both the head and its modifiers (if present). After data pretreatment, we used 33,932 extent mentions in our experiments. Many of these extent mentions are nested or nominal and they have a complex constitution, whereas head mentions are simpler in structure. Therefore, head mentions are adopted in our approach instead of extent mentions.
     </paragraph>
     <paragraph>
      Entity structure: An entity structure is the structure of two entity mentions{sup:3} in a relation mention [71]. In a sentence, two entity mentions have two coarse structures: “nested” and “separated”. “Nested” means that the two entity mentions are nested within each other; otherwise, they are “separated”. Entity mentions are order sensitive, so four entity structures can be generated: two separated and two nested (e.g., E1 is nested in E2). For example, the Chinese sentence ‘第三届台北艺术节今天晚上在台北大安森林公园登场’ (Tonight, the Third Taipei Arts Festival will be held in the Taipei Daan Forest Park) contains three entity mentions: the first ‘台北’ (Taipei), the second ‘台北’, and ‘台北大安森林公园’ (Taipei Daan Forest Park). The first ‘台北’ and the second ‘台北’ are separated. The second ‘台北’ and ‘台北大安森林公园’ are nested.
     </paragraph>
     <paragraph>
      POS tag: We use the POS tags of adjacent words, which lie on two sides of entity mentions. In order to extract POS tags, a POS tagger must be employed. In Chinese NLP, the challenge of Chinese word segmentation makes chunking and parsing Chinese even more difficult and error-prone. Therefore, to reduce the errors caused by a POS tagger, instead of parsing a whole sentence, we first use annotated entity mentions to segment a sentence into smaller phrases, before parsing each phrase separately.
     </paragraph>
     <paragraph>
      N-gram: n-gram features are used widely in natural language processing. One limitation of n-gram features is that most n-gram features are fractional, which may result in a large feature space. Due to the data sparsity problem, {a mathematical formula}n=4 would degrade the experimental performance, so in our settings, we used {a mathematical formula}n={1,2,3} to determine the performance of unigrams, bigrams, and trigrams.
     </paragraph>
     <paragraph>
      Omni-word: Omni-words are words that can be segmented from a sentence. In Chinese, the notion of a “word” is vague and it has played an unimportant role in the Chinese philological tradition [51]. It was reported that Chinese segmentation can reach a precision greater than 95% [43], [58], [65], but this high performance is achievable in a carefully controlled environment where the training and testing data come from the same annotated corpus. In practice, even native Chinese speakers often disagree on word boundaries [19], [60]. Sproat et al. [51] showed that only 75% inter-agreement is reached among native Chinese speakers, which is usually considered the upper bound for any automated system. Another distinct feature of the Chinese language is word formation, which means that the meaning of a Chinese compound word is derived from the meanings of the words it contains [20]. Therefore, fragments of a phrase are also informative in Chinese. Simple lexical features often have significant effects on the precision of extraction [24], [28], so making better use of fragments in phrases is important for relation extraction.
     </paragraph>
     <paragraph>
      In traditional segmentation-based methods, each relation instance is segmented by a segmenter. In general, the output of a segmenter is a phrase, which is a partition of a relation instance. These phrases are used directly, which limits the utilization of fragments in a phrase. After carefully examining the characteristics of Chinese, we decided to use every potential word in a relation mention as lexical features. Omni-word features can reduce the errors caused by Chinese word segmentation and make better use of fragments in a Chinese phrase. For example, the relation mention ‘台北大安森林公园’ (Taipei Daan Forest Park) has a “PART-WHOLE” relation type with two arguments: ‘台北大安森林公园’ (E1, “FAC”) and ‘台北’ (E2, “GPE”). A “perfect” segmenter may recognize the whole string as a phrase, and thus only one lexical feature is generated {‘台北大安森林公园’}. Some segmenters may generate four lexical features: {‘台北’, ‘大安’, ‘森林’, and ‘公园’}.{sup:4}
     </paragraph>
     <paragraph>
      By utilizing every possible word in the mention as lexical features, our omni-word feature approach can generate the following features:
     </paragraph>
     <list>
      <list-item>
       {‘台’, ‘北’, ‘大’, ‘安’, ‘森’, ‘林’, ‘公’, ‘园’, ‘台北’, ‘大安’, ‘森林’, ‘公园’, ‘森林公园’, ‘大安森林公园’} {sup:5}
      </list-item>
     </list>
     <paragraph>
      Unlike traditional segmentation-based lexical features, which are partitions of one sentence, many omni-word features may overlap or nest within each other in the same sentence. The number of features generated can be very high, which reduces the problem caused by the sparse feature representation. In this example, it can be seen that ‘森林’ (forest) and ‘公园’ (park) are informative for relation extraction (e.g., ‘森林’ represents the type of the park). In Chinese, ‘森’ (many trees) or ‘林’ (forest) also have almost the same meaning.
     </paragraph>
     <paragraph>
      In an omni-word feature, most of the words are nested or they overlap with each other. Thus, traditional character-based or word-based features only comprise a subset of the omni-word feature set. The omni-word feature set itself is a subset of the n-gram features that can be filtered by matching lexicon entries. To extract omni-word features, a lexicon is required to scan a sentence and to identify every word.
     </paragraph>
     <paragraph>
      In summary, six candidate feature sets are used: entity type and subtype, head noun, entity structure, POS tag, n-gram, and omni-word feature. Entity-related information (e.g., entity type and head noun) is provided by the corpus. The POS tag is generated by a tagger and an omni-word feature is generated using a lexicon.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Assembling features using constraint conditions
     </section-title>
     <paragraph>
      During open relation extraction, weak supervision or bootstrapping methods usually employ syntactic and semantic constraints to reduce the impact of “semantic drift” caused by error accumulation. These constraints can be viewed as structural constraints based on their local dependency and most of these constraints are hard constraints. Any relation instance that violates these constraints (e.g., below a predefined threshold) should be abandoned. For example, Agichtein et al. [1] selected patterns according to a confidence threshold ({a mathematical formula}τt), while Fader et al. [14] utilized a confidence function. Carlson et al. [6] filtered candidate instances and patterns using the number of times an instance co-occurs with a pattern.
     </paragraph>
     <paragraph>
      Discarding some relation instances is acceptable for open relation extraction because a large amount of data is usually available. However, this approach is not suitable for traditional relation extraction and it may result in a lower recall rate. Instead, combined features are used to capture local dependency information [76], [24]. If a high frequency feature is evenly distributed among different relation types, the occurrences of this feature will exhibit no predictable preferences. If it is combined with relevant information, the distribution of this feature is changed. Combined features can change the distribution of candidate features, thereby resulting in a skewed distribution.{sup:6} Previous studies have shown that features with skewed distributions are more useful [49], [50].
     </paragraph>
     <paragraph>
      Combined features are widely used, but few studies have considered their effects on performance when different approaches are employed to generate them. Most studies of relation extraction have focused on testing high numbers of new features. However, our studies have shown that using more features does not always improve performance, even if the classifier used claims to control these features independently. This is because features may interact with each other indirectly. Thus, for the same candidate features, different combination strategies may have a significant influence on the discrimination power.
     </paragraph>
     <paragraph>
      In this section, we use the phrase “constraint condition” to denote how to assemble candidate features with specific relevant information. Constraint conditions are employed to generate combined features and to capture local dependency information. For every candidate feature, an appropriate constraint condition is selected for its assembly with relevant information to maximize the discrimination power. Based on the constraint conditions, our feature assembly method summarizes the techniques used in feature combinations, thereby providing a more systematic way to assemble the candidate features.
     </paragraph>
     <paragraph>
      During Chinese relation extraction, six constraint conditions are investigated: singleton, position constraint, syntax constraint, multiplication constraint, bin constraint, and collection constraint.
     </paragraph>
     <paragraph>
      Singleton: A feature is used as a singleton feature if it is used without being combined with any other information. In the feature set, only the entity structure is used as a singleton feature.
     </paragraph>
     <paragraph>
      Position constraint: A position-sensitive feature has a mark that indicates the entity mention which it is adhered. Entity type and subtype, head noun, and POS tag can be used as position-sensitive features, which are encoded by combining the candidate feature with the adhered entity mention. For example, ‘台北_E1’ means that the head noun ‘台北’ depends on the first entity mention (E1). The POS tag is combined with positional information and encoded as: ‘Ei_Location_POS’. The two location labels are: “R” (right) and “L” (left). For example, ‘E1_R_noun’ means that the right (“R”) word's POS in the first entity mention is a noun.
     </paragraph>
     <paragraph>
      Syntax constraint: The utilization of syntax constraints is based on the fact that people tend to use similar sentence patterns to express their ideas. For example, a preposition near a location entity may have a high probability of indicating a “physical” relation. Many syntax constraints can be developed to capture the syntactical dependency, e.g., parsing trees, dependency trees, or POS tagging. In the present study, the syntax constraint is constructed by combining POS tags with selected candidate features (e.g., entity type or head noun). For example, ‘v_E1’ means that the POS tag on the left side of the first entity mention is a ‘v’ (verb).
     </paragraph>
     <paragraph>
      Parsing or tagging a sentence itself is a difficult and error-prone task. A more effective approach to using the syntax constraint is to utilize accurate linguistic units in a sentence and to assemble these linguistic units with syntactic information, thereby reducing the errors caused by parsing or tagging. For example, entity mentions are manually annotated and they can segment a sentence in an appropriate manner; therefore, they are a better choice. Thus, we assemble syntactic information using the annotated entity mentions. In real-world applications, it is better to use linguistic units with higher automatic extraction performance, such as function words [23].
     </paragraph>
     <paragraph>
      Multiplication constraint: A multiplication constraint is generated by assembling two features in order, which is the traditional way to generate combined features (conjunctive features or product features). Many multiplication constraints can be used, e.g., two entity types or subtypes can be combined such as ‘person_location’, where ‘person_location’ means that the type of the first relation argument is a “person” and the second is a “location”. Features generated by multiplying two entity types (or subtypes) can capture syntactic and semantic dependency information.
     </paragraph>
     <paragraph>
      Bin constraint: Omni-word features are not added as bag-of-words features; instead, each relation mention is segmented into several substrings based on the boundaries of two entity mentions. Each segmented substring is taken as an independent bin for extracting omni-word features. Every omni-word feature is marked by a label to indicate the bin in which it is located. Depending on the entity structure of two entity mentions and the two entity mentions themselves, five (or less) substrings may be collected. Table 1 shows an example of the possible outcomes generated by two entity mentions.
     </paragraph>
     <paragraph>
      In this example, entity mentions{sup:7} in solid (or dashed) lines are denoted by E1 (or E2). In Row 1, five bins are generated: left bin (‘B_L’), middle bin (‘B_M’), right bin (‘B_R’), and two entity mentions (‘B_E1’ and ‘B_E2’). In Row 4, only two bins are generated (‘B_E1’ and ‘B_E2’). These bin-sensitive features are encoded as: “bin + omni-word”. For example, ‘B_E1_台北’ and ‘B_E2_台北’ mean that the lexical feature ‘台北’ appears in ‘B_E1’ and ‘B_E2’. They are used as two independent features.
     </paragraph>
     <paragraph>
      Collection constraint: Another way to generate combined features is to use an “addition rule”, where the order of the two features is ignored (e.g., {a mathematical formula}{father,son}{sup:8}). This method can reduce the space required for the combined features if space complexity is an issue. For example, the feature {a mathematical formula}{father,son} may indicate that a “family” relation will occur with higher probability. We can use a label to denote each feature generated by this constraint. For example, {a mathematical formula}{father,son} can be encoded as ‘C_father_son’ when both ‘father_son’ and ‘son_father’ occur, where “C” indicates that it is a collective feature.
     </paragraph>
     <paragraph>
      The multiplication constraint is used widely to generate combined features [76], [24], where candidate features are ordered in this method. However, the space of the combined features may grow exponentially. Two feature sets with cardinality n and m can generate {a mathematical formula}n×m combined features. Sometimes, a large feature space can make features randomly distributed, thereby leading to more sparse data. Based on the “addition rule”, the collection constraint can reduce the data sparseness.
     </paragraph>
     <paragraph>
      Using the sentence given above (‘第三届台北艺术节今天晚上在台北大安森林公园登场’), examples of candidate features and constraint conditions are shown in Table 2.
     </paragraph>
     <paragraph>
      In this table, × means that a candidate feature is not assembled under this constraint condition. HM1 is the first entity head mention ‘台北’ (the first ‘台北’ in the sentence) and HM2 is the second head mention ‘大安森林公园’. ‘E2_L_prep’ means that on the left side of ‘台北大安森林公园’ (E2), the word's POS tag is a preposition (‘在’, “in”). In Table 2, entity structures are not listed because they are only used as singleton features. In Column 4, the syntax constraint is expressed by features combined with POS tags.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      In this section, we first describe the experimental settings. Next, four issues related to the feature assembly method are discussed: omni-word feature, constraint conditions, feature assembly and negative instances, which are key issues when training a relation extractor based on the feature assembly method.
     </paragraph>
     <section label="5.1">
      <section-title>
       Experimental settings
      </section-title>
      <paragraph>
       We used the ACE 2005 Chinese corpus in our experiments, which was collected from newswires, broadcasts, and weblogs. It contains 633 documents annotated with 6 major relation types and 18 relation subtypes. There are 8023 relations and 9317 relation mentions (sentences or clauses where relations are mentioned). After deleting five documents with incorrect annotations,{sup:9} 9244 relation mentions were collected as positive instances.
      </paragraph>
      <paragraph>
       If there is no relation between two entities, then a relation instance that takes them as arguments is a negative instance. To obtain negative instances for training a relation extractor, we segmented each document into sentences. Sentences with no entity mention pairs were deleted. For every remaining sentence, all of the entity mention pairs in the sentence were collected as relation instances. Thus, if a sentence had three entity mentions (A,B,C), then because relation arguments (entity) are order sensitive, six entity mention pairs could be generated: [A,B], [A,C], [B,C], [B,A], [C,A], and [C,B]. After discarding entity mention pairs that had already been used as positive instances, 93,283 negative relation instances were generated and labeled as “negative”. Finally, there were seven major relation types and 19 relation subtypes for training and testing. Using these settings, the data were highly unbalanced.{sup:10}
      </paragraph>
      <paragraph>
       In our experiments, information about entity mentions was manually annotated in the corpus, e.g., entity types, subtypes, and head nouns. The POS tags were output by a POS tagger (ICTCLAS package{sup:11}). Only a lexicon is required to extract omni-word features (as discussed in Section 5.2). Two maximum entropy classifiers were trained and tested with the seven relation types and 19 relation subtypes, respectively. In this field, it is usual to only focus on positive relation types and most studies have only reported the performance based on positive instances; therefore, only the results based on positive relations (6 types and 18 subtypes) are included in the present study.
      </paragraph>
      <paragraph>
       We used the traditional Precision/Recall/{a mathematical formula}F-score (P/R/F) measurements to evaluate the performance. Precision is computed by {a mathematical formula}CorrectNumExtractNum, and Recall is computed by {a mathematical formula}CorrectNumRealNum, where Correct Num is the number of correctly recognized relation instances, Extract Num is the number of instances that have been extracted, and Real Num denotes the number of annotated relation instances. The F-score is computed as follows.{a mathematical formula}
      </paragraph>
      <paragraph>
       A fivefold cross-validation was utilized for training and testing. We averaged the results from five runs using the 6 types and 18 subtypes (positive relation types) to determine the final performance (the macro-average):{a mathematical formula} where q is the number of relation type and B represents P, R, or F.
      </paragraph>
      <paragraph>
       To implement the maximum entropy classifiers, we used the toolkit provided by Zhang [67]. In this toolkit, four parameters are required to train the classifiers: iteration, method, sigma, and tolerance. In our experiments, the number of iterations was set to 30. For method, the “L-BFGS” algorithm was selected. sigma is a coefficient used in Gaussian prior smoothing, which turns off Gaussian smoothing when it is set to 0. The tolerance is used for detecting model convergence and it is set to 0.00001 by default. In a maximum entropy model, the weighting parameters of features are estimated from the training data to calculate the conditional probability of a relation type containing these features. In all of the tables, the number of weighting parameters is denoted by “Par”, which indicates the complexity of a model. Theoretically, a large value for “Par” means that the model is more flexible at segmenting evaluation data.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Performance with omni-word features
      </section-title>
      <paragraph>
       In this section, we consider the impact of the lexicon size on the omni-word features and we compare them with traditional features. In order to assess the performance in a realistic scenario, only the annotated boundaries about entity mentions were used from the annotation information. Therefore, the bin constraint was suitable.
      </paragraph>
      <paragraph>
       The size of a lexicon entry determines the dimension of the feature space, so the performance of the omni-word features is affected by the lexicon employed. In this experiment, five lexicons were employed to assess the impact of various lexicon sizes. The first lexicon was obtained by segmenting every relation instance using a segmenter (ICTCLAS package{sup:12}) and we collected every word produced by the segmenter. This lexicon is referred to as “By ICTCLAS” and it contained 13,028 lexicon entries. The ICTCLAS package was trained using an annotated corpus, which contained many lexical entries, so we expected that this lexicon would significantly improve the relation extraction performance. The second lexicon was the Lexicon of Common Words in Contemporary Chinese (referred to as “LCWCC”) published by the Ministry of Education of the People's Republic of China in 2008, which contained 55,732 entries. The “Medium Lexicon” was constructed from the internet and it contained 298,032 words. The majority of the “Medium Lexicon” was collected by the R&amp; D Center of SOHU{sup:13} and it contained more than 150,000 words. We also added lexicons such as locations, scenic spots, idioms, and names of mountains and rivers. The “Maximum Lexicon” was generated by merging the “Medium Lexicon” and the Great Dictionary of Chinese, and it had 542,240 lexicon entries, including ancient Chinese. The results are shown in Table 3. In all of the tables presented in this study, the results are shown for 6 types and 18 subtypes, where the numbers in parentheses represent the 18 subtypes.
      </paragraph>
      <paragraph>
       Table 3 compares the performance using five different lexicons (Rows 1, 2, 3, 4, and 5), where the results demonstrate that a larger lexicon does not guarantee better performance (e.g., Row 5). In Row 6 to Row 8, three combined lexicons are compared, which are based on the lexicon “By ICTCLAS”. The performance only improved marginally, although the size of lexicon increased tremendously. A comparison of Row 1 and Row 8 shows that the lexicon size increased by at least 50 times, but the performance change little. Many words in a lexicon collection did not appear in relation instances, so they did not contribute to the relation extraction performance.
      </paragraph>
      <paragraph>
       Thus, the problem is how to generate an optimal lexicon for omni-word feature construction. The simplest method is to use a conventional dictionary plus a domain dictionary. The conventional dictionary can ensure that many common words are included, while the domain dictionary can reduce the impact of unknown words when applying our method in a specific domain. In this study, we merged “By ICTCLAS” with “LCWCC” and the combined lexicon was used as default lexicon in our experiments (the lexicon used in Row 6).
      </paragraph>
      <paragraph>
       In Table 4, the traditional segmentation-based method and the n-gram features are compared with omni-word features. “By-Segmentation” denotes the traditional segmentation-based feature set generated using a segmenter.
      </paragraph>
      <paragraph>
       Our omni-word method outperformed the traditional segmentation-based method (“By Segmentation”) by 7.43% with 6 relation types and by 10.61% with 18 relation subtypes in terms of the F-score. For the n-gram features with {a mathematical formula}n=1, the performance was still high, although “Par” was low. The highest performance using n-gram features was achieved when {a mathematical formula}n=1,2. When {a mathematical formula}n=1,2,3, “Par” increased considerably but the performance decreased. Compared with “By Segmentation”, the results showed that the n-gram features with the bin constraint also improved the performance considerably.
      </paragraph>
      <paragraph>
       One advantage of omni-word features is that they can be used to filter the fragmented and noisy features caused by large n-gram features. For example, “Par” was reduced considerably when we compared the omni-word features with n-gram features ({a mathematical formula}n=1,2 or {a mathematical formula}n=1,2,3), but the performance was still similar. Furthermore, the omni-word and n-gram features can be used simultaneously. N-gram achieved robust performance when n was small, but the omni-word features could reduce the errors caused by fragmented and noisy features generated by n-grams, as shown by “Omni-word+1,2-Gram”. Every Chinese character can be either a morpheme or a word [27], so the performance did not improve when a 1-gram was added.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Performance with constraint conditions
      </section-title>
      <paragraph>
       In Section 3, six candidate feature sets were introduced: entity type and subtype, head noun, POS tag, entity structure, omni-word, and n-gram. Instead of using them as independent features, we combined them with relevant information (e.g., position information or other candidate features). The combined features were generated by candidate features restricted with constraint conditions, where six constraint conditions were studied: singleton, position constraint, syntax constraint, multiplication constraint, bin constraint, and collection constraint.
      </paragraph>
      <paragraph>
       Table 5 shows the impact of the candidate features when different constraint conditions were applied. In Column 3 (Ref), {a mathematical formula}F(⁎_#) refers to the candidate feature under the corresponding constraint condition, where the ⁎ and # denote the candidate features (Column 1) and constraint condition (Column 2), respectively.
      </paragraph>
      <paragraph>
       First, it can be observed that the combined features were more powerful than singleton features. “Par” increased when combined features were used. Increasing “Par” projects the relation extraction problem into a higher dimensional space, thereby making the decision boundary more flexible.
      </paragraph>
      <paragraph>
       In most cases, increasing “Par” yielded better performance, except for {a mathematical formula}F(PH_M), where the POS tag and head nouns were combined. A comparison of {a mathematical formula}F(PH_M) and {a mathematical formula}F(PE_M) shows that increasing “Par” degraded the performance for {a mathematical formula}F(PH_M). This may be because a large feature space distributes the features more randomly, thereby leading to more sparse data.
      </paragraph>
      <paragraph>
       In Table 5, the weak performance of the collection constraint is because relation arguments (entity) are order sensitive, so the collective features cannot capture local dependency information in this situation. For example, in entity type and subtype, each collective feature (e.g., {person, location}) appears in both the positive and negative instances with almost identical distributions. Therefore, it is difficult to distinguish them using only this feature.
      </paragraph>
      <paragraph>
       Five constraint conditions are explicitly listed in Table 5. Syntax constraint is used by combining POS tag features with head noun, entity type, etc. Entity structure can be assembled with other constraints, such as entity type and subtype or head noun. In this experiment, we only used singleton conditions. In the POS tag columns, it can be seen that the six constraint conditions are not independent. Thus, they can be combined with each other to generate more complex features. For example, {a mathematical formula}F(PH_M) combines POS tags with head nouns, where both multiplication constraint and syntax constraint are used.
      </paragraph>
      <paragraph>
       In summary, Table 5 shows that the entity type and subtype and head noun could maximize the performance when used as a multiplication constraint. The POS tag obtained better performance when combined with entity type and subtype and entity structure. The omni-word feature and n-gram with bin information could increase the performance considerably.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Performance with feature assembly
      </section-title>
      <paragraph>
       The candidate features may behave differently when different constraint conditions are applied. Thus, each type of candidate feature will have a maximized contribution depending on the optimal constraint conditions. Table 6 shows the feature assembly performance when all of the candidate features were used, where {a mathematical formula}F(Seg_B) is the segmentation-based method with bin constraint.
      </paragraph>
      <paragraph>
       Rows 1, 2, and 3 compare the performance of the segmented feature ({a mathematical formula}F(Seg_B)), the n-gram feature ({a mathematical formula}F(N_B)), and the omni-word feature ({a mathematical formula}F(O_B)), respectively. Row 1 shows that when utilizing other candidate features, the segmentation-based feature with the bin constraint also performed well and it even outperformed the omni-word feature with 6 relation types. This result is interesting because Table 4 shows that without other candidate features, the omni-word feature outperformed the segmentation-based method by 7.43% with 6 types and by 10.61% with 18 subtypes.
      </paragraph>
      <paragraph>
       These results indicate that using more features does not always improve the performance, even if the classifier employed claims to control these features independently (e.g., the maximum entropy) because features may interact with each other indirectly. Using the same candidate features, different combined approaches may have significant effects on the discrimination power. The introduction of new features also affects the discrimination power of the other features used. In fact, {a mathematical formula}F(Seg_B) is a subset of {a mathematical formula}F(O_B). In this case, feature selection methods such as variable ranking, wrappers, and embedded methods can be used to improve the performance further [17].
      </paragraph>
      <paragraph>
       Rows 4, 5, and 6 show the impact of different constraint conditions. Row 4 shows the performance when all of the candidate features were used as singleton features, which indicates that the performance decreased considerably, thereby demonstrating that the lack of local dependency information for relation extraction can degrade the performance. In Row 5, all of the candidate features were assembled with the constraint conditions that maximized the performance in Table 5, but the performance was reduced compared with Row 6. Therefore, maximizing the performance of each candidate feature cannot guarantee the best overall performance.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Performance with negative instances
      </section-title>
      <paragraph>
       In ancient Chinese, there is no punctuation between sentences. In modern Chinese, symbols such as the period (“。”), question mark (“？”), exclamation mark (“！”), semicolon (“；”), or comma (“，”) are used to indicate sentence boundaries. In our study, these five types of punctuation were used as the default settings to segment sentences because they are used commonly in Chinese NLP. However, the use of commas is ambiguous [59] because they may indicate sentence boundaries or the separation of clauses. In general, four types of punctuation (“。”, “？”, “！” and “；”) are used to segment sentences. However, even for native speakers, the comma is frequently treated as a sentence boundary in Chinese. For example, in the ACE2005 corpus, document “VOM20001026.1800.0795” contains a “sentence” where 937 characters are divided only by commas. Therefore, it is difficult to define a standard criterion.
      </paragraph>
      <paragraph>
       In a distantly supervised relation extraction system, the impact of “negative” instances was discussed by Min et al. [36], but this issue has not been studied in Chinese relation extraction. When different systems are considered, the ambiguity of sentence boundaries can make comparisons difficult. In this experiment, various numbers of negative instances were generated to determine their impact on performance and Table 7 shows the results obtained, where the details of each row are explained in the following.
      </paragraph>
      <list>
       <list-item label="1.">
        Using the default settings employed in our experiment, each sentence was obtained with five types of punctuations as sentence boundaries (“。”, “？”, “！”, “；”, and “，”). The positive instances comprised the annotated relation mentions{sup:14} and the negative instances were collected from the segmented sentences (see Section 5.1). In this experiment, most of the positive relation mentions had longer sentences than the negative instances.
       </list-item>
       <list-item label="2.">
        The manually annotated positive instances with 6 types and 18 subtypes were used for training and testing, but no negative instances were added. It can be seen that performance of the default settings in Row 1 is similar to that in Row 2. In addition to the proposed features, the good performance in Row 1 is also because the features for the positive instances were extracted from annotated relation mentions, whereas the features for the negative instances were extracted from sentences divided by five types of punctuation. The latter contained less contextual clues, so their influence on the final performance was reduced.
       </list-item>
       <list-item label="3.">
        The documents were segmented into sentences using five types of punctuation. These sentences were used to collect positive and negative instances. The annotated relation mentions had longer sentences so some positive instances were absent. Compared with the annotated relation mentions, the shorter sentence lengths of these positive instances led to the loss of information, thereby degrading the performance.
       </list-item>
       <list-item label="4.">
        Instead of collecting sentences from all of the documents, only the annotated relation mentions were employed to collect positive and negative instances. Both the positive and negative instances shared similar sentence contexts, so the features were distributed more uniformly among the positive and negative relation types, and thus the discrimination power of the features was reduced.
       </list-item>
       <list-item label="5.">
        Four types of punctuation (“。”, “？”, “！”, and “；”) were used as sentence boundaries, but the other settings were the same as those used for Row 1. Many of the annotated relation mentions were clauses divided by “，” so in this experiment, many negative instances had longer sentences than the annotated relation mentions. The data were severely unbalanced, but a longer sentence length appeared to be informative for classification.
       </list-item>
       <list-item label="6.">
        The documents were segmented into sentences using four types of punctuation and the positive and negative instances were then collected. All of the instances had the same sentence boundaries, which resulted in long sentences and the data were severely unbalanced. The positive instances used longer sentences and thus large amounts of noise could be introduced. The presence of the same sentence contexts in the positive and negative instances was also problematic for the classifiers.
       </list-item>
      </list>
      <paragraph>
       The results showed that the sentence boundaries and the number of negative instances had significant effects on the relation extraction performance. The performance was worse when positive and negative instances had the same sentence context (they shared the same lexical features). The best performance with negative instances is shown in Column 5 of Table 7.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Comparisons with existing methods and discussion
     </section-title>
     <section label="6.1">
      <section-title>
       Comparisons with Chinese relation extraction methods
      </section-title>
      <paragraph>
       We compared our approach with other Chinese relation extraction methods. We focused on systems that are trained and tested using the ACE corpus. Table 8 compares the performance of several Chinese relation extraction systems, including both kernel-based and feature-based models.
      </paragraph>
      <paragraph>
       The models followed by ⁎ denote systems tested using the ACE 2005 corpus, where 6 types and 18 subtypes were employed in fivefold cross-validations. ⋆ denotes the ACE 2005 corpus tested with seven types and 19 subtypes using 75% of the data for training and 25% for testing. ⋄ denotes the ACE 2004 corpus tested with seven types where two-thirds of the data were used for training and one-third for testing. The methods of Liu et al. [31] and Zhang et al. [66] are kernel-based models. The methods of Che et al. [8] and Zhang et al. [70] are feature-based models. That of Lin et al. [30] is a mixed model that combines both kernel- and feature-based methods.
      </paragraph>
      <paragraph>
       Using the same settings and datasets employed in our previous experiments, we compared the methods described by Che et al. [8] and Zhang et al. [70].
      </paragraph>
      <paragraph>
       The features used by the method of Che et al. [8] were: Ei.TYPE, Ei.SUBTYPE, Order, {a mathematical formula}WordEi±1, {a mathematical formula}WordEi±2, {a mathematical formula}POSEi±1, and {a mathematical formula}POSEi±2. Order comprised four types of Entity Structure features. {a mathematical formula}WordEi±k and {a mathematical formula}POSEi±k were the words and POS tags for Ei, where “±k” denotes the kth word (of POS) after (+) or before (-) the corresponding entity mention. In the method of Che et al. [8], {a mathematical formula}k=1 and {a mathematical formula}k=2, which yielded better performance.
      </paragraph>
      <paragraph>
       In the method of Zhang et al. [70], Ei.TYPE, Ei.SUBTYPE, 9 Entity Structure, Uni-(Internal and External), and Bi-(Internal and External) were used. Uni-(Internal and External) was the unigram feature for internal and external character sequences. The internal character sequences were the four extend and head mentions.{sup:15} Five external character sequences were used: one In-Between character sequence between E1 and E2, and four character sequences around two extend mentions in the given window size w_s.{sup:16}w_s was set to 4. Bi-(Internal and External) was a 2-gram feature such as Uni-(Internal and External). Instead of four Entity Structures, nine Entity Structures are used.
      </paragraph>
      <paragraph>
       The results are shown in Table 9, where the settings for “Positive/Negative” were the same as those used for Row 1 and Row 5 in Table 7.
      </paragraph>
      <paragraph>
       The model proposed by Che et al. [8] employs segmentation-based word features, but without a bin constraint. The model proposed by Zhang et al. [70] uses n-gram features, but instead of a bin constraint, the n-gram features are extracted from character sequences around two extend mentions in a window of size {a mathematical formula}w_s=4. Both of these methods also use the notion of constraint conditions. For example, a position constraint is used for the entity type, word, and POS tag. In the method proposed by Zhang et al. [70], the internal and external character sequences are similar to a bin constraint. However, these methods did not investigate the constraint conditions in depth or combine these features in a systematic manner.
      </paragraph>
      <paragraph>
       Table 9 shows that our system clearly outperformed the other systems in both conditions. According to the comparison with different “positive/negative” settings, a larger number of negative instances degraded the performance of the methods compared, but our system still exhibited robust performance. In particular, our method outperformed the others by 19.57% with 6 relation types and 22.06% with 18 relation subtypes.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Comparison with English relation extraction methods
      </section-title>
      <paragraph>
       The central idea of feature assembly is that features can be grouped into candidate feature sets according to linguistic functions. The grouped features satisfy certain properties and they can be manipulated to capture structural and functional information using a relation instance. Our method was originally designed for Chinese relation extraction, but this idea can be extended to other languages. In this section, we describe the application of the feature assembly method to English relation extraction. Various techniques have been applied to extract English relations, e.g., tree kernels [75] and deep neural networks [64]. Table 10 presents two feature-based English relation extraction systems.
      </paragraph>
      <paragraph>
       In Kambhatla [24], only the performance based on subtypes was reported. In Zhou et al. [76], external resources (e.g., WordNet and gazetteers) were used to extract semantic features. Both of these studies used dependency trees and parse trees to capture the local dependency of relation instances, but they used another strategy to control the asymmetric relation problem, i.e., a new inverted relation type was introduced for each asymmetric relation type. Therefore, they evaluated their methods based only on annotated “true” relation mentions, which yielded more balanced evaluation data.{sup:17}
      </paragraph>
      <paragraph>
       In this experiment, we implemented the method described by Kambhatla [24] as the baseline and the constraint conditions were then applied gradually to determine the impact of feature assembly. The ACE 2005 English corpus was used. After filtering documents with error annotations, we obtained 506 documents. Using the approach described in Section 5.1, 6583 positive instances (6 types or 18 subtypes) and 86,777 negative instances were generated. The methods described in Section 5.1 were used, i.e., fivefold cross-validation, P/R/F measurements, etc.
      </paragraph>
      <paragraph>
       Six types of features were used by Kambhatla [24]: words, entity type (subtype), mention level, overlap, dependency tree and parse tree. The words features comprise the words in the entity mentions and all of the words in between, which are combined with the entity mention information, e.g., ‘chairman_E1’ means that the word is part of the first entity mention. Entity type (subtype) and mention level (e.g., nominal) all use the position constraint (e.g., ‘PERSON_E1’). Overlap is the same as our entity structure. To parse the sentence, we used the Stanford parser.{sup:18} An example of these features is: ‘NNP_E1_dep’ (POS of a word on which E1 is dependent). The results are shown in Table 11.
      </paragraph>
      <list>
       <list-item label="1.">
        The performance of the method proposed by Kambhatla [24] was based only on 6583 positive instances. The results were higher than those reported by Kambhatla [24] because the asymmetric relation problem was not considered.
       </list-item>
       <list-item label="2.">
        The baseline performance was obtained based on all of the evaluation data using the same features as those for Row 1. It can be seen that the addition of negative relation instances degraded the performance considerably.
       </list-item>
       <list-item label="3.">
        Based on Row 2, we changed the entity types (subtypes) from position constraints into multiplication constraints, and we combined head nouns with the position information. The results obtained demonstrated the impact of different constraint conditions.
       </list-item>
       <list-item label="4.">
        Each relation instance was segmented into a maximum of five bins (see Table 1). All of the words in each bin were assembled with the bin constraint.
       </list-item>
       <list-item label="5.">
        We used an English word root list containing 986 roots. If a root occurred in a bin, then it was assembled with the bin constraint. For example, if a root “saurus” occurred in the left bin, then the feature ‘saurus_B_L’ was added.
       </list-item>
      </list>
      <paragraph>
       Table 11 shows two main results. The first occurs in Row 4 where words with the bin constraint were added. In fact, words in three of the five bins were used in Row 2 with other constraint conditions (the words in two entity mentions and the words in between). Only the words in ‘B_L’ and ‘B_R’ (see Table 1) are “new” features. However, the performance was clearly improved, possibly because after a feature was combined with another constraint, the distribution of this feature was changed, thereby improving the prediction performance.
      </paragraph>
      <paragraph>
       The second main result is shown in Row 5, where word roots were used, and this performance improvement was the highest. To the best of our knowledge, this feature has never been used for English relation extraction. We use the omni-word feature for Chinese relation extraction because the sub-phrases in Chinese words are also meaningful. In English, the words also consist of roots, so the omni-word feature is also helpful. For example, “Argentinosaurus” and “Tyrannosaurus” rarely occur in normal sentences. However, if “saurus” occurs, then it indicates some species of dinosaur. This result demonstrates the possibility of applying the omni-word feature to English relation extraction.
      </paragraph>
      <paragraph>
       A comparison of Rows 2 and 5 demonstrates that our method outperformed the baseline by about 20.96% with 6 relation types and by 22.18% with 18 relation subtypes.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Discussion
      </section-title>
      <paragraph>
       The utilization of feature assembly is based mainly on the fact that a relation mention has two entity mentions. By using entity mentions as “reference objects” to segment a relation mention, the extracted candidate features can reduce the errors caused by tagging or parsing. Two entity mentions also structure a relation mention. Depending on the structural characteristics of languages, features can be grouped into different sets, where the grouped features satisfy certain properties and they can be manipulated to capture structural and functional information in a relation instance. Guided by experience or prior knowledge, suitable constraint conditions can be applied to candidate features to generate combined features and to capture the local dependency information. The feature assembly method maps the feature space into a higher dimensional space. A hyperplane in higher dimensional space can yield a flexible decision boundary, and thus a classifier can be more effective in finding a decision boundary to segment the evaluation data.
      </paragraph>
      <paragraph>
       In addition, improvements can be made using constraint conditions, which have the ability to capture local dependency information. Most previous studies have focused on using large numbers of new features, where combined features are generated based on prior knowledge or via simple greedy feature combination. However, as shown in Table 6, the use of more features does not always improve the performance because the combined features may be mutually dependent. Thus, when different constraint conditions are employed, they may exhibit different behaviors and influence the overall performance. Using the same candidate features, different combined approaches may have significant effects on the discrimination power. Indeed, the introduction of new features will also affect the discrimination power of any other features that are used. If all of the candidate features are used at the same time, the performance might not increase as expected, so it is important to select suitable candidate features and assemble them in an appropriate manner.
      </paragraph>
      <paragraph>
       Another advantage of our method is the use of omni-word features with the bin constraint. In many languages, fragments of phrases are also informative, such as characters in Chinese and word roots in English. Three properties of omni-word features are important. First, the sub-phrases of a word are informative. Second, most relation instances have a limited context, so using omni-word features based on every possible word or root is a better way to capture this information. Third, the boundaries of entity mentions are manually annotated, which means that they can precisely segment one relation instance into corresponding bins. The combination of omni-word features with the bin constraint is effective for capturing the local dependency information of a sentence.
      </paragraph>
      <paragraph>
       Most relation mentions have a sparse feature representation, but utilizing every linguistic unit can make omni-word features more effective at capturing syntactic and semantic information. To a certain extent, omni-word features can be formulated as a subset of n-gram features, where the fragments are filtered by a lexicon. Omni-word features and n-gram features can be used simultaneously, as shown in Table 4. The performance of n-grams is robust when n is small, and the omni-word features can reduce the errors caused by the fragmented and noisy features generated by n-grams when n is higher.
      </paragraph>
      <paragraph>
       To extract relations at the sentence level, a limited number of words is often involved, which yields a sparse feature representation. This limited number of words also leads to feature sparsity when extracting targeted units at the sentence level. Therefore, utilizing the structural and functional information in a relation instance is important for relation extraction. The feature assembly model provides a flexible framework for capturing the local dependency of relation instances, thereby enhancing the utilization of candidate features. The feature assembly model focuses on generating features that capture syntactic and semantic information from a relation mention. However, processing a large number of features is also expensive. Thus, after generating the features, feature selection methods such as variable ranking, wrappers, and embedded methods can be employed to further improve the performance [17].
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>