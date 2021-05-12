<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Automatic Detection of Cognates Using Orthographic Alignment.
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
       Words undergo various changes when entering new languages. Based on the assumption that these linguistic changes follow certain rules, we propose a method for automatically detecting pairs of cognates employing an orthographic alignment method which proved relevant for sequence alignment in computational biology. We use aligned subsequences as features for machine learning algorithms in order to infer rules for linguistic changes undergone by words when entering new languages and to discriminate between cognates and non-cognates. Given a list of known cognates, our approach does not require any other linguistic information.
However, it can be customized to integrate historical information regarding language evolution.
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
        Cognates are words in different languages having the same etymology and a common ancestor. Investigating pairs of cognates is very useful in historical and comparative linguistics, in the study of language relatedness
        [30]
        , phylogenetic inference
        [1]
        and in identifying how and to what extent languages change over time. In other several research areas, such as language acquisition, bilingual word recognition
        [9]
        , corpus linguistics
        [32]
        , cross-lingual information retrieval
        [4]
        and machine translation
        [19]
        , the condition of common etymology is usually not essential and cognates are regarded as words with high cross-lingual meaning and orthographic or phonetic similarity.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The wide range of applications in which cognates prove useful attracted more and more attention on methods for detecting such related pairs of words. This task is most challenging for resource-poor
languages, for which etymologically related information is not accessible. Therefore, the research
        [17, 25, 16]
        focused on automatic identification of cognate pairs, starting from lists of known cognates.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we propose a method for automatically determining pairs of cognates across languages.
The proposed method requires a list of known cognates and, for languages for which additional linguistic information is available, it can be customized
to integrate historical information regarding the evolution of the language.
The rest of the paper is organized as follows: in Section 2 we present and analyze alternative methods and related work in this area. In Section 3 we introduce our approach for detection of cognates using orthographic alignment. In Section 4 we describe the experiments we conduct and we report and analyze the results, together with a comparison with previous methods. Finally, in Section 5 we draw the conclusions of our study and describe our plans for extending the method.
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
        There are three important aspects widely investigated in the task of cognate identification: semantic, phonetic and orthographic similarity. They were employed both individually
        [32, 17, 6]
        and combined
        [21, 34]
        in order to detect pairs of cognates across languages. For determining semantic similarity, external lexical resources, such as WordNet
        [10]
        , or large corpora, might be necessary. For measuring phonetic and orthographic proximity of cognate candidates, string similarity metrics can be applied, using the phonetic or orthographic word forms as input. Various measures were investigated and compared
        [17, 14]
        ; Levenshtein distance
        [22]
        , XDice
        [3]
        and the longest common subsequence ratio
        [24]
        are among the most frequently used metrics in this field.
        Gomes and Lopes (2011)
        proposed SpSim, a more complex method for computing the similarity of cognate pairs which tolerates learned transitions between words.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Algorithms for string alignment were successfully used for identifying cognates based on both their forms, orthographic and phonetic.
        Delmestri and Cristianini (2010)
        used basic sequence alignment algorithms
        [29, 33, 12]
        to obtain orthographic alignment scores for cognate candidates.
        Kondrak (2000)
        developed the ALINE system, which aligns words’ phonetic transcriptions based on multiple phonetic features and computes similarity scores using dynamic programming.
        List (2012)
        proposed a framework for automatic detection of cognate pairs, LexStat, which combines
different approaches to sequence comparison and alignment derived from those used in historical linguistics and evolutionary biology.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The changes undergone by words when entering from one language into another and the transformation rules they follow have been successfully employed in various approaches to cognate detection
        [18, 25, 28]
        .
These orthographic changes have also been used in cognate production, which is closely related to the task of cognate detection, but has not yet been as intensively studied. While the purpose of cognate detection is to determine whether two given words form a cognate pair, the aim of cognate production is, given a word in a source language, to automatically produce its cognate pair in a target language.
        Beinborn et al. (2013)
        proposed a method for cognate production relying on statistical character-based machine translation, learning orthographic production patterns, and
        Mulloni (2007)
        introduced an algorithm for cognate production based on edit distance alignment and the identification of orthographic cues when words enter a new language.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Our Approach
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Although there are multiple aspects that are relevant in the study of language relatedness, such as orthographic, phonetic, syntactic and semantic differences, in this paper we focus only on lexical evidence. The orthographic approach relies on the idea that sound changes leave traces in the orthography and alphabetic character correspondences represent, to a fairly large extent, sound correspondences
        [8]
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Words undergo various changes when entering new languages. We assume that rules for adapting foreign words to the orthographic system of the target languages might not have been very well defined in their period of early development, but they may have since become complex and probably language-specific. Detecting pairs of cognates based on etymology is useful and reliable, but, for resource-poor languages, methods which require less linguistic knowledge might be necessary.
According to
        Gusfield (1997)
        , an edit transcript (representing the conversion of one string to another) and an alignment are mathematically equivalent ways of describing relationships between strings. Therefore, because the edit distance was widely used in this research area and produced good results, we are encouraged to employ orthographic alignment for identifying pairs of cognates, not only to compute similarity scores, as was previously done, but to use aligned subsequences as features for machine learning algorithms. Our intuition is that inferring language-specific rules for aligning words will lead to better performance in the task of cognate identification.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Orthographic Alignment
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         String alignment is closely related to the task of sequence alignment in computational biology. Therefore, to align pairs of words we employ the Needleman-Wunsch global alignment algorithm
         [29]
         , which is mainly used for aligning sequences of proteins or nucleotides. Global sequence alignment aims at determining the best alignment over the entire length of the input sequences. The algorithm uses dynamic programming and, thus, guarantees to find the optimal alignment. Its main idea is that any partial path of the alignment along the optimal path should be the optimal path leading up to that point. Therefore, the optimal path can be determined by incremental extension of the optimal subpaths
         [31]
         . For orthographic alignment, we consider words as input sequences and we use a very simple substitution matrix, which gives equal scores to all substitutions,
disregarding diacritics (e.g., we ensure that
         e
         and
         è
         are matched).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Feature Extraction
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Using aligned pairs of words as input, we extract features around mismatches in the alignments. There are three types of mismatches, corresponding to the following operations: insertion, deletion and substitution. For example, for the Romanian word
         exhaustiv
         and its Italian cognate pair
         esaustivo
         , the alignment is as follows:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        𝚎𝚡𝚑𝚊𝚞𝚜𝚝𝚒𝚟-𝚎𝚜-𝚊𝚞𝚜𝚝𝚒𝚟𝚘
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         The first mismatch (between
         x
         and
         s
         ) is caused by a substitution, the second mismatch (between
         h
         and
         -
         ) is caused by a deletion from source language to target language, and the third mismatch (between
         -
         and
         o
         ) is caused by an insertion from source language to target language. The features we use are character
         n
         -grams around mismatches. We experiment with two types of features:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.ix1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           i)
          </span>
          <div class="ltx_para" id="I1.ix1.p1">
           <p class="ltx_p">
            n
            -grams around gaps, i.e., we account only for insertions and deletions;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.ix2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           ii)
          </span>
          <div class="ltx_para" id="I1.ix2.p1">
           <p class="ltx_p">
            n
            -grams around any type of mismatch, i.e., we account for all three types of mismatches.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         The second alternative leads to better performance, so we account for all mismatches. As for the length of the grams, we experiment with
         n∈{1,2,3}
         . We achieve slight improvements by combining
         n
         -grams, i.e., for a given
         n
         , we use all
         i
         -grams, where
         i∈{1,…,n}
         . In order to provide information regarding the position of the features, we mark the beginning and the end of the word with a
         $
         symbol. Thus, for the above-mentioned pair of cognates,
         (exhaustiv, esaustivo)
         , we extract the following features when
         n=2
         :
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        𝚡&gt;𝚜𝚎𝚡&gt;𝚎𝚜𝚡𝚑&gt;𝚜-𝚑&gt;-𝚡𝚑&gt;𝚜-𝚑𝚊&gt;-𝚊-&gt;𝚘𝚟-&gt;𝚟𝚘-$&gt;𝚘⁢$
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         For identical features we account only once. Therefore, because there is one feature (
         xh&gt;s-
         ) which occurs twice in our example, we have 8 features for the pair
         (exhaustiv, esaustivo)
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Learning Algorithms
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         We use Naive Bayes as a baseline and we experiment with Support Vector Machines (SVMs) to learn orthographic changes and to discriminate between pairs of cognates and non-cognates. We put our system together using the Weka
workbench
         [15]
         , a suite of machine learning algorithms and tools. For SVM, we use the wrapper provided by Weka for LibSVM
         [5]
         . We use the radial basis function kernel (RBF), which can handle the case when the relation between class labels and attributes is non-linear, as it maps samples non-linearly into a higher dimensional space. Given two instances
         xi
         and
         xj
         , where
         xi∈ℝn
         , the RBF kernel function for
         xi
         and
         xj
         is defined as follows:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        K⁢(xi,xj)=e⁢x⁢p⁢(-γ⁢||xi-xj||2),γ&gt;0,
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         where
         γ
         is a kernel parameter.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         We split the data in two subsets, for training and testing, with a 3:1 ratio, and we perform grid search and 3-fold cross validation over the training set in order to optimize hyperparameters
         c
         and
         γ
         . We search over
         {1,2,…,10}
         for
         c
         and over
         {10-5,10-4,…,10,410}5
         for
         γ
         . The values which optimize accuracy on the training set are reported, for each pair of languages, in Table
         3
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
       Experiments
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Data
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We apply our method on an automatically extracted dataset of cognates for four pairs of languages: Romanian-French, Romanian-Italian, Romanian-Spanish and Romanian-Portuguese. In order to build the dataset, we apply the methodology proposed by
         Ciobanu and Dinu (2014)
         on the DexOnline
         machine-readable dictionary for Romanian. We discard pairs of words for which the forms across languages are identical (i.e., the Romanian word
         matrice
         and its Italian cognate pair
         matrice
         , having the same form), because these pairs do not provide any orthographic changes to be learned. For each pair of languages we determine a number of non-cognate pairs equal to the number of cognate pairs.
Finally, we obtain 445 pairs of cognates for Romanian-French
         , 3,477 for Romanian-Italian, 5,113 for Romanian-Spanish and 7,858 for Romanian-Portuguese. Because we need sets of approximately equal size for comparison across languages, we keep 400 pairs of cognates and 400 pairs of non-cognates for each pair of languages. In Tables
         1
         and
         2
         we provide, for each pair of languages, the five most relevant 2-gram orthographic changes, determined using the
         χ2
         distribution implemented in Weka, and the five most frequent 2-gram orthographic changes in the cognate pairs from our dataset
         . None of the top ranked orthographic cues occurs at the beginning of the word, while many of them occur at the end of the word.
The most frequent operation in Tables
         1
         and
         2
         is substitution.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Results Analysis
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We propose a method for automatic detection of cognate pairs using orthographic alignment. We experiment with two machine-learning approaches: Naive Bayes and SVM. In Table
         3
         we report the results of our research. We report the
         n
         -gram values for which the best results are obtained and the hyperparameters for SVM,
         c
         and
         γ
         . The best results are obtained for French and Spanish, while the lowest accuracy is obtained for Portuguese. The SVM produces better results for all languages except Portuguese, where the accuracy is equal.
For Portuguese, both Naive Bayes and SVM misclassify more non-cognates as cognates than viceversa. A possible explanation might be the occurrence, in the dataset, of more remotely related words, which are not labeled as cognates. We plan to investigate this assumption and to apply the proposed method on other datasets in our future work.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Comparison with Previous Methods
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We investigate the performance of the method we propose in comparison to previous approaches for automatic detection of cognate pairs based on orthographic similarity. We employ several orthographic metrics widely used in this research area: the edit distance
         [22]
         , the longest common subsequence ratio
         [24]
         and the XDice metric
         [3]
         . In addition, we use SpSim
         [11]
         , which outperformed the longest common subsequence ratio and a similarity measure based on the edit distance in previous experiments.
To evaluate these metrics on our dataset, we use the same train/test sets as we did in our previous experiments and we follow the strategy described in
         [17]
         . First, we compute the pairwise distances between pairs of words for each orthographic metric individually, as a single feature
         . In order to detect the best threshold for discriminating between cognates and non-cognates, we run a decision stump classifier (provided by Weka) on the training set for each pair of languages and for each metric. A decision stump is a decision tree classifier with only one internal node and two leaves corresponding to our two class labels. Using the best threshold value selected for each metric and pair of languages, we further classify the pairs of words in our test sets as cognates or non-cognates. In Table
         4
         we report the results for each approach. Our method performs better than the orthographic metrics considered as individual features. Out of the four similarity metrics, SpSim obtains, overall, the best performance. These results support the relevance of accounting for orthographic cues in cognate identification.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
