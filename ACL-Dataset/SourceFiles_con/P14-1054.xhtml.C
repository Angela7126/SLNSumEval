<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Omni-word Feature and Soft Constraintfor Chinese Relation Extraction.
  </title>
 </head>
 <body>
  <div class="ltx_page_main">
   <div class="ltx_page_content">
    <div class="ltx_document ltx_authors_1line">
     <div class="ltx_abstract">
      <h6 class="ltx_title ltx_title_abstract">
       Abstract
      </h6>
      <p class="ltx_p">
       Chinese is an ancient hieroglyphic. It is inattentive to structure. Therefore, segmenting and parsing Chinese are more difficult and less accurate. In this paper, we propose an Omni-word feature and a soft constraint method for Chinese relation extraction. The Omni-word feature uses every potential word in a sentence as lexicon feature, reducing errors caused by word segmentation. In order to utilize the structure information of a relation instance, we discuss how soft constraint can be used to capture the local dependency. Both Omni-word feature and soft constraint make a better use of sentence information and minimize the influences caused by Chinese word segmentation and parsing. We test these methods on the ACE 2005 RDC Chinese corpus. The results show a significant improvement in Chinese relation extraction, outperforming other methods in F-score by 10% in 6 relation types and 15% in 18 relation subtypes.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Introduction
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        Information Extraction (IE) aims at extracting syntactic or semantic units with concrete concepts or linguistic functions
        []
        . Instead of dealing with the whole documents, focusing on designated information, most of the IE systems extract named entities, relations, quantifiers or events from sentences.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The relation recognition task is to find the relationships between two entities. Successful recognition of relation implies correctly detecting both the relation arguments and relation type. Although this task has received extensive research. The performance of relation extraction is still unsatisfactory with a F-score of 67.5% for English (23 subtypes)
        []
        . Chinese relation extraction also faces a weak performance having F-score about 66.6% in 18 subtypes
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The difficulty of Chinese IE is that Chinese words are written next to each other without delimiter in between. Lacking of orthographic word makes Chinese word segmentation difficult. In Chinese, a single sentence often has several segmentation paths leading to the segmentation ambiguity problem
        []
        . The lack of delimiter also causes the Out-of-Vocabulary problem (OOV, also known as
        new word detection
        )
        []
        . These problems are worsened by the fact that Chinese has a large number of characters and words. Currently, the state-of-the-art Chinese OOV recognition system has performance about 75% in recall
        []
        . The errors caused by segmentation and OOV will accumulate and propagate to subsequent processing (e.g. part-of-speech (POS) tagging or parsing).
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Therefore, the Chinese relation extraction is more difficult. According to our survey, compared to the same work in English, the Chinese relation extraction researches make less significant progress.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Based on the characteristics of Chinese, in this paper, an Omni-word feature and a soft constraint method are proposed for Chinese relation extraction. We apply these approaches in a maximum entropy based system to extract relations from the ACE 2005 corpus. Experimental results show that our method has made a significant improvement.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        The contributions of this paper include
       </p>
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Propose a novel Omni-word feature for Chinese relation extraction. Unlike the traditional segmentation based method, which is a partition of the sentence, the Omni-word feature uses every potential word in a sentence as lexicon feature.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Aiming at the Chinese inattentive structure, we utilize the soft constraint to capture the local dependency in a relation instance. Four constraint conditions are proposed to generate combined features to capture the local dependency and maximize the classification determination.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        The rest of this paper is organized as follows. Section
        2
        introduces the related work. The Omni-word feature and soft constrain are proposed in Section
        3
        . We give the experimental results in Section
        3.2
        and analyze the performance in Section
        4
        . Conclusions are given in Section
        5
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        There are two paradigms extracting the relationship between two entities: the Open Relation Extraction (ORE) and the Traditional Relation Extraction (TRE)
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Based on massive and heterogeneous corpora, the ORE systems deal with millions or billions of documents. Even strict filtrations or constrains are employed to filter the redundancy information, they often generate tens of thousands of relations dynamically
        []
        . The practicability of ORE systems depends on the adequateness of information in a big corpus
        []
        . Most of the ORE systems utilize weak supervision knowledge to guide the extracting process, such as: Databases
        []
        , Wikipedia
        []
        , Regular expression
        []
        , Ontology
        []
        or Knowledge Base extracted automatically from Internet
        []
        . However, when iteratively coping with large heterogeneous data, the ORE systems suffer from the “semantic drift” problem, caused by error accumulation
        []
        . Agichtein, Carlson and Fader et al.
        []
        propose syntactic and semantic constraints to prevent this deficiency. The soft constraints, proposed in this paper, are combined features like these syntactic or semantic constraints, which will be discussed in Section
        3.2
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The TRE paradigm takes hand-tagged examples as input, extracting predefined relation types
        []
        . The TRE systems use techniques such as: Rules (Regulars, Patterns and Propositions)
        []
        , Kernel method
        []
        , Belief network
        []
        , Linear programming
        []
        , Maximum entropy
        []
        or SVM
        []
        . Compared to the ORE systems, the TRE systems have a robust performance. Disadvantages of the TRE systems are that the manually annotated corpus is required, which is time-consuming and costly in human labor. And migrating between different applications is difficult. However, the TRE systems are evaluable and comparable. Different systems running on the same corpus can be evaluated appropriately.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        In the field of Chinese relation extraction, Liu et al.
        []
        proposed a convolution tree kernel. Combining with external semantic resources, a better performance was achieved. Che et al.
        []
        introduced a feature based method, which utilized lexicon information around entities and was evaluated on Winnow and SVM classifiers. Li and Zhang et al.
        []
        explored the position feature between two entities. For each type of these relations, a SVM was trained and tested independently. Based on
        Deep Belief Network
        , Chen et al.
        []
        proposed a model handling the high dimensional feature space. In addition, there are mixed models. For example, Lin et al.
        []
        employed a model, combining both the feature based and the tree kernel based methods.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Despite the popularity of kernel based method, Huang et al.
        []
        experimented with different kernel methods and inferred that simply migrating from English kernel methods can result in a bad performance in Chinese relation extraction. Chen and Li et al.
        []
        also pointed out that, due to the inaccuracy of Chinese word segmentation and parsing, the tree kernel based approach is inappropriate for Chinese relation extraction. The reason of the tree kernel based approach not achieve the same level of accuracy as that from English may be that segmenting and parsing Chinese are more difficult and less accurate than processing English.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        In our research, we proposed an Omni-word feature and a soft constraint method. Both approaches are based on the Chinese characteristics. Therefore, better performance is expected. In the following, we introduce the feature construction, which discusses the proposed two approaches.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Feature Construction
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section, the employed candidate features are discussed. And four constraint conditions are proposed to transform the candidate features into combined features. The soft constraint is the method to generate the combine features
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Candidate Feature Set
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In the ACE corpus, an
         entity
         is an object or set of objects in the world. An
         entity mention
         is a reference to an entity. The entity mention is annotated with its full
         extent
         and its
         head
         , referred to as the
         extend mention
         and the
         head mention
         respectively. The extent mention includes both the head and its modifiers. Each
         relation
         has two entities as arguments: Arg-1 and Arg-2, referred to as E1 and E2. A
         relation mention
         (or instance) is the embodiment of a relation. It is referred by the sentence (or clause) in which the relation is located in. In our work, we focus on the detection and recognition of relation mention.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Relation identification is handled as a classification problem. Entity-related information (e.g. head noun, entity type, subtype, CLASS, LDCTYPE, etc.) are supposed to be known and provided by the corpus. In our experiment, the entity type, subtype and the head noun are used.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         All the employed features are simply classified into five categories:
         Entity Type and Subtype
         ,
         Head Noun
         ,
         Position Feature
         ,
         POS Tag
         and
         Omni-word Feature
         . The first four are widely used. The last one is proposed in this paper and is discussed in detail.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Entity Type and Subtype
         : In ACE 2005 RDC Chinese corpus, there are 7 entity types (Person, Organization, GPE, Location, Facility, Weapon and Vehicle) and 44 subtypes (e.g. Group, Government, Continent, etc.).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         Head Noun
         : The head noun (or head mention) of entity mention is manually annotated. This feature is useful and widely used.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         Position Feature
         : The position structure between two entity mentions (extend mentions). Because the entity mentions can be nested, two entity mentions may have four coarse structures: “E1 is before E2”, “E1 is after E2”, “E1 nests in E2” and “E2 nests in E1”, encoded as: ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          E1_B_E2
         </code>
         ’, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          E1_A_E2
         </code>
         ’, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          E1_N_E2
         </code>
         ’ and ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          E2_N_E1
         </code>
         ’.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p7">
        <p class="ltx_p">
         POS Tag
         : In our model, we use only the adjacent entity POS tags, which lie in two sides of the entity mention. These POS tags are labelled by the ICTCLAS package
         . The POS tags are not used independently. It is encoded by combining the POS tag with the adjacent entity mention information. For example ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          E1_Right_n
         </code>
         ’ means that the right side of the first entity is a noun (“n”).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p8">
        <p class="ltx_p">
         Omni-word Feature
         : The notion of “word” in Chinese is vague and has never played a role in the Chinese philological tradition
         []
         . Some Chinese segmentation performance has been reported precision scores above 95%
         []
         . However, for the same sentence, even native peoples in China often disagree on word boundaries
         []
         . Sproat et al.
         []
         has showed that there is a consistence of 75% on the segmentation among different native Chinese speakers. The word-formation of Chinese also implies that the meanings of a compound word are made up, usually, by the meanings of words that contained in it
         []
         . So, fragments of phrase are also informative.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p9">
        <p class="ltx_p">
         Because high precision can be received by using simple lexical features
         []
         . Making better use of such information is beneficial. In consideration of the Chinese characteristics, we use
         every potential word in a relation mention
         as the lexical features.
         UTF8gbsn
For example, relation mention ‘å°åå¤§å®æ£®æå¬å­’ (Taipei Daan Forest Park) has a ”PART-WHOLE” relation type. The traditional segmentation method may generate four lexical features {‘å°å’, ‘å¤§å®’, ‘æ£®æ’, ‘å¬å­’}, which is a partition of the relation mention. On the other hand, the Omni-word feature denoting all the possible words in the relation mention may generate features as:
        </p>
        <ol class="ltx_enumerate" id="I2">
         <li class="ltx_item" id="I2.ix1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
          </span>
          <div class="ltx_para" id="I2.ix1.p1">
           <p class="ltx_p">
            {‘å°’, ‘å’, ‘å¤§’, ‘å®’, ‘æ£®’, ‘æ’, ‘å¬’, ‘å­’, ‘å°å’, ‘å¤§å®’, ‘æ£®æ’, ‘å¬å­’, ‘æ£®æå¬å­’, ‘å¤§å®æ£®æå¬å­’}
           </p>
          </div>
         </li>
        </ol>
        <p class="ltx_p">
         Most of these features are nested or overlapped mutually. So, the traditional character-based or word-based feature is only a subset of the Omni-word feature. To extract the Omni-word feature, only a lexicon is required, then scan the sentence to collect every word.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p10">
        <p class="ltx_p">
         Because the number of lexicon entry determines the dimension of the feature space, performance of Omni-word feature is influenced by the lexicon being employed. In this paper, we generate the lexicon by merging two lexicons. The first lexicon is obtained by segmenting every relation instance using the ICTCLAS package, collecting very word produced by ICTCLAS. Because the ICTCLAS package was trained on annotated corpus containing many meaningful lexicon entries. We expect this lexicon to improve the performance. The second lexicon is
         the Lexicon Common Words in Contemporary Chinese
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p11">
        <p class="ltx_p">
         Despite the Omni-word can be seen as a subset of n-Gram feature. It is not the same as the n-Gram feature. N-Gram features are more fragmented. In most of the instances, the n-Gram features have no semantic meanings attached to them, thus have varied distributions. Furthermore, for a single Chinese word, occurrences of 4 characters are frequent. Even 7 or more characters are not rare. Because Chinese has plenty of characters
         , when the corpus becoming larger, the n-Gram (n¿4) method is difficult to be adopted. On the other hand, the Omni-word can avoid these problems and take advantages of Chinese characteristics (the word-formation and the ambiguity of word segmentation).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Soft Constraint
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         The structure information (or dependent information) of relation instance is critical for recognition. However, even in English, “deeper” analysis (e.g. logical syntactic relations or predicate-argument structure) may suffer from a worse performance caused by inaccurate chunking or parsing. Hence, the local dependency contexts around the relation arguments are more helpful
         []
         . Zhang et al.
         []
         also showed that Path-enclosed Tree (PT) achieves the best performance in the kernel based relation extraction. In this field, the tree kernel based method commonly uses the parse tree to capture the structure information
         []
         . On the other hand, the feature based method usually uses the combined feature to capture such structure information
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         In the open relation extraction domain, syntactic and semantic constraints are widely employed to prevent the “semantic drift” problem. Such constraints can also be seen as structural constraint. Most of these constraints are hard constraints. Any relation instance violating these constraints (or below a predefined threshold) will be abandoned. For example, Agichtein and Gravano
         []
         generates patterns according to a
         confidence threshold
         (
         τt
         ). Fader et al.
         []
         utilizes a
         confidence function
         . And Carlson et al.
         []
         filters candidate instances and patterns using the number of times they co-occurs.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Deleting of relation instances is acceptable for open relation extraction because it always deals with a big data set. But it’s not suitable for traditional relation extraction, and will result in a low recall. Utilizing the notion of combined feature
         []
         , we replace the hard constraint by the soft constraint. Each soft constraint (combined feature) has a parameter trained by the classifier indicating the discrimination ability it has. No subjective or priori judgement is adopted to delete any potential determinative constraint (except for the reason of dimensionality reduction).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Most of the researches make use of the combined feature, but rarely analyze the influence of the approaches we combine them. In this paper, we use the soft constraint to model the local dependency. It is a subset of the combined feature, generated by four constraint conditions:
         singleton
         ,
         position sensitive
         ,
         bin sensitive
         and
         semantic pair
         . For every employed candidate feature, an appropriate constraint condition is selected to combine them with additional information to maximize the classification determination.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         UTF8gbsn
         Singleton
         : A feature is employed as a singleton feature when it is used without combining with any information. In our experiments, only the
         position feature
         is used as singleton feature.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         Position Sensitive
         : A position sensitive feature has a label indicating which entity mention it depends on. In our experiment, the
         Head noun
         and
         POS Tag
         are utilized as position sensitive features, which has been introduced in Section
         3.1
         . For example, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å_E1
         </code>
         ’ means that the head noun ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å
         </code>
         ’ depend on the first entity mention.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         Semantic Pair
         : Semantic pair is generated by combining two semantic units. Two kinds of semantic pair are employed. Those are generated by combining two entity types or two entity subtypes into a semantic pair. For example, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          Person_Location
         </code>
         ’ denotes that the type of the first relation argument is a “Person” (entity type) and the second is a “Location” (entity type). Semantic pair can capture both the semantic and structure information in a relation mention.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p8">
        <p class="ltx_p">
         Bin Sensitive
         : In our study,
         Omni-word feature
         is not added as “bag of words”. To use the Omni-word feature, we segment each relation mention by two entity mentions. Together with the two entity mentions, we get five parts: “FIRST”, “MIDDLE”, “END”, “E1” and “E2” (or less, if the two entity mentions are nested). Each part is taken as an independent bin. A flag is used to distinguish them. For example, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å_Bin_F
         </code>
         ’, ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å_Bin_E1
         </code>
         ’ and ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å_Bin_E
         </code>
         ’ mean that the lexicon entry ‘
         <code class="ltx_verbatim ltx_font_typewriter">
          å°å
         </code>
         ’ appears in three bins: the FIRST bin, the first entity mention (E1) bin and the END bin. They will be used as three independent features.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p9">
        <p class="ltx_p">
         To sum up, among the five candidate feature sets, the position feature is used as a singleton feature. Both head noun and POS tag are position sensitive. Entity types and subtypes are employed as semantic pair. Only Omni-word feature is bin sensitive. In the following experiments, focusing on Chinese relation extraction, we will analyze the performance of candidate feature sets and study the influence of the constraint conditions.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p10">
        <p class="ltx_p">
         sectionExperiments
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p11">
        <p class="ltx_p">
         In this section, methodologies of the Omni-word feature and the soft constraint are tested. Then they are compared with the state-of-the-art methods.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Settings and Results
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         We use the ACE 2005 RDC Chinese corpus, which was collected from newswires, broadcasts and weblogs, containing 633 documents with 6 major relation types and 18 subtypes. There are 8,023 relations and 9,317 relation mentions. After deleting 5 documents containing wrong annotations
         , we keep 9,244 relation mentions as positive instances.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         UTF8gbsn
To get the negative instances, each document is segmented into sentences
         . Those sentences that do not contain any entity mention pair are deleted. For each of the remained sentences, we iteratively extract every entity mention pair as the arguments of relation instances for predicting. For example, suppose a sentence has three entity mentions: A,B and C. Because the relation arguments are order sensitive, six entity mention pairs can be generated: [A,B], [A,C], [B,C], [B,A], [C,A] and [C,B]. After discarding the entity mention pairs that were used as positive instances, we generated 93,283 negative relation instances labelled as “OTHER”. Then, we have 7 relation types and 19 subtypes.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         A maximum entropy multi-class classifier is trained and tested on the generated relation instances. We adopt the five-fold cross validation for training and testing. Because we are interested in the 6 annotated major relation types and the 18 subtypes, we average the results of five runs on the 6 positive relation types (and 18 subtypes) as the final performance. F-score is computed by
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        2×(P⁢r⁢e⁢c⁢i⁢s⁢i⁢o⁢n×R⁢e⁢c⁢a⁢l⁢l)P⁢r⁢e⁢c⁢i⁢s⁢i⁢o⁢n+R⁢e⁢c⁢a⁢l⁢l
        <p class="ltx_p">
         To implement the maximum entropy model, the toolkit provided by Le
         []
         is employed. The iteration is set to
         30
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p5">
        <p class="ltx_p">
         Five candidate feature sets are employed to generate the combined features. The
         entity type and subtype
         ,
         head noun
         ,
         position feature
         are referred to as
         ℱt⁢h⁢p
         . The POS tags are referred to as
         ℱp⁢o⁢s
         . The Omni-word feature set is denoted by
         ℱo⁢w
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p6">
        <p class="ltx_p">
         Table
         1
         gives the performance of our system on the 6 types and 18 subtypes. Note that, in this paper, bare numbers and numbers in the parentheses represent the results of the 6 types and the 18 subtypes respectively.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p7">
        <p class="ltx_p">
         In Row 1, because
         ℱt⁢h⁢p
         are features directly obtained from annotated corpus, we take this performance as our referential performance. In Row 2, with only the
         ℱo⁢w
         feature, the F-score already reaches 77.74% in 6 types and 60.31% in 18 subtypes. The last row shows that adding the
         ℱp⁢o⁢s
         almost has no effect on the performance when both the
         ℱt⁢h⁢p
         and
         ℱo⁢w
         are in use. The results show that
         ℱo⁢w
         is effective for Chinese relation extraction.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p8">
        <p class="ltx_p">
         The superiorities of Owni-word feature depend on three reasons. First, the specificity of Chinese word-formation indicates that the subphrases of Chinese word (or phrase) are also informative. Second, most of relation instances have limited context. The Owni-word feature, utilizing every possible word in them, is a better way to capture more information. Third, the entity mentions are manually annotated. They can precisely segment the relation instance into corresponding bins. Segmentation of bins bears the sentence structure information. Therefore, the Owni-word feature with bin information can make a better use of both the syntactic information and the local dependency.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Comparison
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Various systems were proposed for Chinese relation extraction. We mainly focus on systems trained and tested on the ACE corpus. Table
         2
         lists three systems.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         Che et al.
         []
         was implemented on the ACE 2004 corpus, with 2/3 data for training and 1/3 for testing. The performance was reported on 7 relation types: 6 major relation types and the none relation (or negative instance). Zhang et al.
         []
         was based on the ACE 2005 corpus with 75% data for training and 25% for testing. Performances about the 7 types and 19 subtypes were given. Both of them are feature based methods. Liu et al.
         []
         is a kernel based method evaluated on the ACE 2005 corpus. The five-fold cross validation was used and declared the performances on 6 relation types and 18 subtypes.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p3">
        <p class="ltx_p">
         The data preprocessing makes differences from our experiments to others. In order to give a better comparison with the state-of-the-art methods, based on our experiment settings and data, we implement the two feature based methods proposed by Che et al.
         []
         and Zhang et al.
         []
         in Table
         2
         . The results are shown in Table
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p4">
        <p class="ltx_p">
         In Table
         3
         , Ei (
         i∈1,2
         ) represents entity mention. “Order” in Che et al.
         []
         denotes the position structure of entity mention pair. Four types of order are employed (the same as ours).
         W⁢o⁢r⁢d+-⁡E⁢i, k
         and
         P⁢O⁢S+-⁡E⁢i, k
         are the words and POS of Ei, “
         +-⁡k
         ” means that it is the
         k
         th word (of POS) after (+) or before (-) the corresponding entity mention. In this paper,
         k=1
         and
         k=2
         were set.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p5">
        <p class="ltx_p">
         In Row 2, the “Uni-Gram” represents the Uni-gram features of internal and external character sequences. Internal character sequences are the four entity extend and head mentions. Five kinds of external character sequences are used: one In-Between character sequence between E1 and E2 and four character sequences around E1 and E2 in a given window size w_s. The w_s is set to 4. The “Bi-Gram” is the 2-gram feature of internal and external character sequences. Instead of the 4 position structures, the 9 position structures are used. Please refer to Zhang et al.
         []
         for the details of these 9 position structures.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p6">
        <p class="ltx_p">
         In Table
         3
         , it is shown that our system outperforms other systems, in F-score, by 10% on 6 relation types and by 15% on 18 subtypes.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p7">
        <p class="ltx_p">
         For researchers who are interested in our work, the source code of our system and our implementations of Che et al.
         []
         and Zhang et al.
         []
         are available at
         https://github.com/YPench/CRDC
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Discussion
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section, we analyze the influences of employed feature sets and constraint conditions on the performances.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Most papers in relation extraction try to augment the number of employed features. In our experiment, we found that this does not always guarantee the best performance, despite the classifier being adopted is claimed to control these features independently. Because features may interact mutually in an indirect way, even with the same feature set, different constraint conditions can have significant influences on the final performance.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        In Section
        3
        , we introduced five candidate feature sets. Instead of using them as independent features, we combined them with additional information. We proposed four constraint conditions to generate the soft constraint features. In Table
        4
        , the performances of candidate features are compared when different constraint conditions was employed.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        In Column 3 of Table
        4
        (
        Constraint Condition
        ), (1), (2), (3), (4) and (5) stand for the referential feature sets
        in Table
        1
        . Symbol “/” means that the corresponding candidate features in the referential feature set are substituted by the new constraint condition.
        Par
        in Column 4 is the number of parameters in the trained maximum entropy model, which indicate the model complexity.
        I
        in Column 5 is the influence on performance. “-” and “+” mean that the performance is decreased or increased.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        The first observation is that the combined features are more powerful than used as
        singletons
        . Model parameters are increased by the combined features. Increasing of parameters projects the relation extraction problem into a higher dimensional space, making the decision boundaries become more flexible.
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        The named entities in the ACE corpus are also annotated with the CLASS and LDCTYPE labels. Zhou et al.
        []
        has shown that these labels can result in a weaker performance. Row 1, 2 and 3 show that, no matter how they are used, the performances decrease obviously. The reason of the performance degradation may be caused by the problem of over-fitting or data sparseness.
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        At most of the time, increase of model parameters can result in a better performance. Except in Row 8 and Row 11, when two
        head nouns
        of entity pair were combined as
        semantic pair
        and when
        POS tag
        were combined with the entity type, the performances are decreased. There are 7356 head nouns in the training set. Combining two head nouns may increase the feature space by
        7356×(7356-1)
        . Such a large feature space makes the occurrence of features close to a random distribution, leading to a worse data sparseness.
       </p>
      </div>
      <div class="ltx_para" id="S4.p8">
       <p class="ltx_p">
        In Row 4, 10 and 13, these features are used as
        singleton
        , the performance degrades considerably. This means that, the missing of sentence structure information on the employed features can lead to a bad performance.
       </p>
      </div>
      <div class="ltx_para" id="S4.p9">
       <p class="ltx_p">
        Row 9 and 12 show an interesting result. Comparing the reference set (5) with the reference set (3), the
        Head noun
        and
        adjacent entity POS tag
        get a better performance when used as
        singletons
        . These results reflect the interactions between different features. Discussion of this issue is beyond this paper’s scope. In this paper, for a better demonstration of the constraint condition, we still use the
        Position Sensitive
        as the default setting to use the
        Head noun
        and the
        adjacent entity POS tag
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p10">
       <p class="ltx_p">
        Row 13 and 14 compare the
        Omni-word feature
        (
        By-Omni-word
        ) with the traditional segmentation based feature (
        By-Segmentation
        ).
        By-Segmentation
        denotes the traditional segmentation based feature set generated by a segmentation tool, collecting every output of relation mention. In this place, the ICTCLAS package is adopted too.
       </p>
      </div>
      <div class="ltx_para" id="S4.p11">
       <p class="ltx_p">
        Conventionally, if a sentence is perfectly segmented,
        By-Segmentation
        is straightforward and effective. But, our experiment shows different observations. Row 13 and 14 show that the
        Omni-word
        method outperforms the traditional method. Especially, when the
        bin
        information is used (Row 15), the performance of
        Omni-word feature
        increases considerably.
       </p>
      </div>
      <div class="ltx_para" id="S4.p12">
       <p class="ltx_p">
        Row 14 shows that, compared with the traditional method, the Omni-word feature improves the performance by about 8.79% in 6 relation types and 11.83% in 18 subtypes in F-core. Such improvement may reside in the three reasons discussed in Section
        3.3
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p13">
       <p class="ltx_p">
        In short, from Table
        4
        we have seen that the
        entity type and subtype
        maximize the performance when used as
        semantic pair
        .
        Head noun
        and
        adjacent entity POS tag
        are employed to combine with positional information.
        Omni-word feature
        with bins information can increase the performance considerably. Our model (in Section
        3.3
        ) uses these settings. This insures that the performances of the candidate features are optimized.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
