<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Automatic Detection of Machine Translated Text and Translation Quality Estimation.
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
       We show that it is possible to automatically detect
machine translated text at sentence level from monolingual corpora,
using text classification methods. We show further that the accuracy with which a
learned classifier can detect text as machine translated is strongly correlated with
the translation quality of the machine translation system that generated it.
Finally, we offer a generic machine translation quality estimation technique based on this approach,
which does not require reference sentences.
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
        The recent success and proliferation of statistical machine translation (MT) systems raise a number of important questions. Prominent among these are how to evaluate the quality of such a system efficiently and how to detect the output of such systems (for example, to avoid using it circularly as input for refining MT systems).
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper, we will answer both these questions. First, we will show that using style-related linguistic features, such as frequencies of parts-of-speech n-grams and function words, it is possible to learn classifiers that distinguish machine-translated text from human-translated or native English text. While this is a straightforward and not entirely novel result, our main contribution is to relativize the result. We will see that the success of such classifiers are strongly correlated with the quality of the underlying machine translation system. Specifically, given a corpus consisting of both machine-translated English text (English being the target language) and native English text (not necessarily the reference translation of the machine-translated text), we measure the accuracy of the system in classifying the sentences in the corpus as machine-translated or not. This accuracy will be shown to decrease as the quality of the underlying MT system increases. In fact, the correlation is strong enough that we propose that this accuracy measure itself can be used as a measure of MT system quality, obviating the need for a reference corpus, as for example is necessary for BLEU
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The paper is structured as follows: In the next section, we review previous related work. In the third section, we describe experiments regarding the detection of machine translation and in the fourth section we discuss the use of detection techniques as a machine translation quality estimation method. In the final section we offer conclusions and suggestions for future work.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Previous Work
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Translationese
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         The special features of translated texts have been studied widely for many years. Attempts to define their characteristics, often called ”Translation Universals”, include
         []
         . The differences between native and translated texts found there go well beyond systematic translation errors and point to a distinct ”Translationese” dialect.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Using automatic text classification methods in the field of translation studies had many use cases in recent years, mainly as an empirical method of measuring, proving or contradicting translation universals. Several works
         []
         used text classification techniques in order to distinguish human translated text from native language text at document or paragraph level, using features like word and POS n-grams, proportion of grammatical words in the text, nouns, finite verbs, auxiliary verbs, adjectives, adverbs, numerals, pronouns, prepositions, determiners, conjunctions etc. Koppel and Ordan
         []
         classified texts to original or translated, using a list of 300 function words taken from LIWC
         []
         as features. Volanski et al.
         []
         also tested various hypotheses regarding ”Translationese”, using 32 different linguistically-informed features, to assess the degree to which different sets of features can distinguish between translated and original texts.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Machine Translation Detection
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Regarding the detection of machine translated text, Carter and Inkpen
         []
         translated the Hansards of the 36th Parliament of Canada using the Microsoft Bing MT web service, and conducted three detection experiments at document level, using unigrams, average token length, and type-token ratio as features. Arase and Zhou
         []
         trained a sentence-level classifier to distinguish machine translated text from human generated text on English and Japanese web-page corpora, translated by Google Translate, Bing and an in-house SMT system. They achieved very high detection accuracy using application-specific feature sets for this purpose, including indicators of the ”Phrase Salad”
         []
         phenomenon or ”Gappy-Phrases”
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         While Arase and Zhou
         []
         considered MT detection at sentence level, as we do in this paper, they did not study the correlation between the translation quality of the machine translated text and the ability to detect it. We show below that such detection is possible with very high accuracy only on low-quality translations. We examine this detection accuracy vs. quality correlation, with various MT systems, such as rule-based and statistical MT, both commercial and in-house, using various feature sets.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Detection Experiments
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We wish to distinguish machine translated English sentences from either human-translated sentences or native English sentences. Due to the sparseness of the data at the sentence level, we use common content-independent linguistic features for the classification task. Our features are binary, denoting the presence or absence of each of a set of part-of-speech n-grams acquired using the Stanford POS tagger
         []
         , as well as the presence or absence of each of 467 function words taken from LIWC
         []
         .
We consider only those entries that appear at least ten times in the entire corpus, in order to reduce sparsity in the data. As our learning algorithm we use SVM with sequential minimal optimization (SMO), taken from the WEKA machine learning toolkit
         []
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Detecting Different MT Systems
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         In the first experiment set, we explore the ability to detect outputs of machine translated text from different MT systems, in an environment containing both human generated and machine translated text. For this task, we use a portion of the Canadian Hansard corpus
         []
         , containing 48,914 parallel sentences from French to English. We translate the French portion of the corpus using several MT systems, respectively: Google Translate, Systran, and five other commercial MT systems available at the http://itranslate4.eu website, which enables to query example MT systems built by several european MT companies. After translating the sentences, we take 20,000 sentences from each engine output and conduct the detection experiment by labeling those sentences as MT sentences, and another 20,000 sentences, which are the human reference translations, labeled as reference sentences. We conduct a 10-fold cross-validation experiment on the entire 40,000 sentence corpus. We also conduct the same experiment using 20,000 random, non-reference sentences from the same corpus, instead of the reference sentences. Using simple linear regression, we also obtain an
         R2
         value (coefficient of determination) over the measurements of detection accuracy and BLEU score, for each of three feature set combinations (function words, POS tags and mixed) and the two data combinations (MT vs. reference and MT vs. non reference sentences). The detection and
         R2
         results are shown in Table
         1
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         As can be seen, best detection results are obtained using the full combined feature set. It can also be seen that, as might be expected, it is easier to distinguish machine-translated sentences from a non-reference set than from the reference set. In Figure
         1
         , we show the relationship of the observed detection accuracy for each system with the BLEU score of that system. As is evident, regardless of the feature set or non-MT sentences used, the correlation between detection accuracy and BLEU score is very high, as we can also see from the
         R2
         values in Table
         1
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        In-House SMT Systems
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         In the second experiment set, we test our detection method on SMT systems we created, in which we have control over the training data and the expected overall relative translation quality. In order to do so, we use the Moses statistical machine translation toolkit
         []
         . To train the systems, we take a portion of the Europarl corpus
         []
         , creating 7 different SMT systems, each using a different amount of training data, for both the translation model and language model. We do this in order to create different quality translation systems, details of which are described in Table
         3
         . For purposes of classification, we use the same content independent features as in the previous experiment, based on function words and POS tags, again with SMO-based SVM as the classifier. For data, we use 20,000 random, non reference sentences from the Hansard corpus, against 20,000 sentences from one MT system per experiment, again resulting in 40,000 sentence instances per experiment. The relationship between the detection results for each MT system and the BLEU score for that system, resulting in
         R2=0.774
         , is shown in Figure
         2
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
       Machine Translation Evaluation
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Human Evaluation Experiments
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         As can be seen in the above experiments, there is a strong correlation between the BLEU score and the MT detection accuracy of our method. In fact, results are linearly and negatively correlated with BLEU, as can be seen both on commercial systems and our in-house SMT systems. We also wish to consider the relationship between detection accuracy and a human quality estimation score. To do this, we use the French-English data from the 8th Workshop on Statistical Machine Translation - WMT13’
         []
         , containing outputs from 13 different MT systems and their human evaluations. We conduct the same classification experiment as above, with features based on function words and POS tags, and SMO-based SVM as the classifier. We first use 3000 reference sentences from the WMT13’ English reference translations, against the matching 3000 output sentences from one MT system at a time, resulting in 6000 sentence instances per experiment. As can be seen in Figure
         3
         , the detection accuracy is strongly correlated with the evaluations scores, yielding
         R2=0.774
         . To provide another measure of correlation, we compared every pair of data points in the experiment to get the proportion of pairs ordered identically by the human evaluators and our method, with a result of
         0.846
         (66 of 78). In the second experiment, we use 3000 random, non reference sentences from the newstest 2011-2012 corpora published in WMT12’
         []
         against 3000 output sentences from one MT system at a time, again resulting in 6000 sentence instances per experiment. While applying the same classification method as with the reference sentences, the detection accuracy rises, while the correlation with the translation quality yields
         R2=0.556
         , as can be seen in Figure
         4
         . Here, the proportion of identically ordered pairs is
         0.782
         (61 of 78).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Syntactic Features
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We note that the second leftmost point in Figures
         3
         ,
         4
         is an outlier: that is, our method has a hard time detecting sentences produced by this system although it is not highly rated by human evaluators. This point represents the Joshua
         []
         SMT system. This system is syntax-based, which apparently confound our POS and FW-based classifier, despite it’s low human evaluation score. We hypothesize that the use of syntax-based features might improve results. To verify this intuition, we create parse trees using the Berkeley parser
         []
         and extract the one-level CFG rules as features. Again, we represent each sentence as a boolean vector, in which each entry represents the presence or absence of the CFG rule in the parse-tree of the sentence. Using these features alone, without the FW and POS tag based features presented above, we obtain an
         R2=0.829
         with a proportion of identically ordered pairs at
         0.923
         (72 of 78), as shown in Figure
         5
         .
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
