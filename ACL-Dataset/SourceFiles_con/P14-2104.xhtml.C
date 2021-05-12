<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Training a Korean SRL System with Rich Morphological Features.
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
       In this paper we introduce a semantic role labeler for Korean, an agglutinative language with rich morphology. First, we create a novel training source by semantically annotating a Korean corpus containing fine-grained morphological and syntactic information. We then develop a supervised SRL model by leveraging morphological features of Korean that tend to correspond with semantic roles. Our model also employs a variety of latent morpheme representations induced from a larger body of unannotated Korean text. These elements lead to state-of-the-art performance of 81.07% labeled F1, representing the best SRL performance reported to date for an agglutinative language.
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
        Semantic Role Labeling (SRL) is the task of automatically annotating the predicate-argument structure in a sentence with semantic roles. Ever since Gildea and Jurafsky
        [9]
        , SRL has become an important technology used in applications requiring semantic interpretation, ranging from information extraction
        [8]
        and question answering
        [14]
        , to practical problems including textual entailment
        [4]
        and pictorial communication systems
        [10]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        SRL systems in many languages have been developed as the necessary linguistic resources become available
        [18, 20, 5, 12]
        . Seven languages were the subject of the CoNLL-2009 shared task in syntactic and semantic parsing
        [11]
        . These languages can be categorized into three broad morphological types: fusional (4), analytic (2), and one agglutinative language.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Björkelund et al.
        [2]
        report an average labeled semantic F1-score of 80.80% across these languages. The highest performance was achieved for the analytic language group (82.12%), while the agglutinative language, Japanese, yielded the lowest performance (76.30%). Agglutinative languages such as Japanese, Korean, and Turkish are computationally difficult due to word-form sparsity, variable word order, and the challenge of using rich morphological features.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In this paper, we describe a Korean SRL system which achieves 81% labeled semantic F1-score. As far as we know, this is the highest accuracy obtained for Korean, as well as any agglutinative language. Figure
        1
        displays a English/Korean sentence pair, highlighting the SOV word order of Korean as well as its rich morphological structure. Two factors proved crucial in the performance of our SRL system:
        (i)
        The analysis of fine-grained morphological tags specific to Korean, and
        (ii)
        the use of latent stem and morpheme representations to deal with sparsity. We incorporated both of these elements in a CRF
        [13]
        role labeling model.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Besides the contribution of this model and SRL system, we also report on the creation and availability of a new semantically annotated Korean corpus, covering over 8,000 sentences. We used this corpus to develop, train, and test our Korean SRL model. In the next section, we describe the process of corpus creation in more detail.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       A Semantically Annotated Korean Corpus
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We annotated predicate-argument structure of verbs in a corpus from the
Electronics and Telecommunications Research Institute of Korea
(ETRI).
        Our corpus
was developed over two years using a specialized annotation
tool
        [16]
        , resulting in more than 8,000 semantically
annotated sentences. As much as possible, annotations followed the PropBank
guidelines for English
        [3]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        We view our work as building on the efforts of the Penn Korean PropBank
(PKPB).
        Our corpus is
roughly similar in size to the PKPB, and taken together, the two Korean
corpora now total about half the size of the Penn English PropBank. One advantage
of our corpus is that it is built on top of the ETRI Korean corpus, which uses
a richer Korean morphological tagging scheme than the Penn Korean Treebank.
Our experiments will show that these finer-grained tags are crucial for
achieving high SRL accuracy.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        All annotations were performed by two people working in a team. At first, each
annotator assigns semantic roles independently and then they discuss to reduce
disagreement of their annotation results. Initially, the disagreement rate
between two annotators was about 14%. After 4 months of this process, the
disagreement rate fell to 4% through the process of building annotation rules
for Korean. The underlying ETRI syntactically-annotated corpus contains the
dependency tree structure of sentences with morpho-syntactic tags. It includes 101,602
multiple-clause sentences with 21.66 words on average.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        We encountered two major difficulties during annotation. First, the existing Korean frame files from the Penn Korean PropBank include 2,749 verbs, covering only 13.87% of all the verbs in the ETRI corpus. Secondly, no Korean PropBanking guidelines have previously been published, leading to uncertainty in the initial stages of annotation. These uncertainties were gradually resolved through the iterative process of resolving inter-annotator disagreements.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Table
        1
        shows the semantic roles considered in our annotated corpus. Although these are based on the general English PropBank guidelines
        [3]
        , they also differ in that we used only 4 numbered arguments from ARG0 to ARG3 instead of 5 numbered arguments. We thus consider 17 semantic roles in total. Four of them are numbered roles, describing the essential arguments of a predicate. The other roles are called modifier roles that play more of an adjunct role.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        We have annotated semantic roles by following the PropBank annotation guideline
        [3]
        and by using frame files of the Penn Korean PropBank
built by Palmer et al.
        [15]
        . The PropBank and our corpus are not
exactly compatible, because the former is built on
constituency-based parse trees, whereas our corpus uses dependency parses.
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        More importantly, the tagsets of these corpora are not fully compatible. The
PKPB uses much coarser morpho-syntactic tags than the ETRI corpus. For
example, the PCA tag in PKPB used for a case suffix covers four different
functioning tags used in our corpus. Using coarser suffix tags can seriously
degrade SRL performance, as we show in
Section
        6
        , where we compare the performance of our
model on both the new corpus and the older PKPB.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Previous Work
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Korean SRL research has been limited to domestically published Korean research
on small corpora. Therefore, the most direct precedent to the present work is
a section in Björkelund et al.
        [2]
        on
Japanese SRL. They build a classifier consisting of 3 stages: predicate
disambiguation, argument identification, and argument classification.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        They use an
        L2
        -regularized linear logistic regression model cascaded
through these three stages, achieving F1-score of 80.80% on average for 7
languages (Catalan, Chinese, Czech, English, German, Japanese and Spanish).
The lowest reported performance is for Japanese, the only agglutinative
language in their data set, achieving F1-score of 76.30%. This result
showcases the computational difficulty of dealing with morphologically rich
agglutinative languages. As we discuss in Section
        5
        , we utilize
these same features, but also add a set of Korean-specific features to capture
aspects of Korean morphology.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Besides these morphological features, we also employ latent continuous and
discrete morpheme representations induced from a larger body of unannotated
Korean text. As our experiments below show, these features improve
performance by dealing with sparsity issues. Such features have been
useful in a variety of English NLP models, including chunking, named entity
recognition
        [19]
        , and spoken language understanding
        [1]
        .
Unlike the English models, we use individual morphemes as our unit of analysis.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Model
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        For the semantic role task, the input is a sentence consisting of a sequence of words
        x=x1,…,xn
        and the output is a sequence of corresponding semantic tags
        y=y1,…,yn
        . Each word consists of a stem and some number of suffix morphemes, and the semantic tags are drawn from the set
        {none,arg⁢0,…,argm-tmp}
        .
We model the conditional probability
        p(y|x)
        using a CRF model:
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       Z⁢(x)-1⁢∏i=1xexp⁢∑mλm⁢fm⁢(yi-1,yi,x,i),
       <p class="ltx_p">
        where
        fm⁢(yi-1,yi,x,i)
        are the feature functions. These feature functions include transition features that identify the tag bigram
        (yi-1,yi)
        , and emission features that combine the current semantic tag
        (yi)
        with instantiated feature templates extracted from the sentence
        x
        and its underlying morphological and dependency analysis.
The function
        Z
        is the normalizing function, which ensures that
        p(y|x)
        is a valid probability distribution. We used 100 iteration of averaged perceptron algorithm to train the CRF.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Features
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        We detail the feature templates used for our experiments in Table
        2
        . These features are categorized as either general features, Korean-specific features, or latent morpheme representation features. Korean-specific features are built upon the morphological analysis of the suffix agglutination of the current word
        xi
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Korean suffixes are traditionally classified into two groups called
        Josa
        and
        Eomi
        . Josa is used to define nominal cases and modify
other phrases, while Eomi is an ending of a verb or an adjective to define a
tense, show an attitude, and connect or terminate a sentence. Thus, the Eomi
and Josa categorization plays an important role in signaling semantic roles.
Considering the functions of Josa and Eomi, we expect that numbered roles are
relevant to Josa while modifier roles are more closely related to Eomi. The
one exception is adverbial Josa, making the attached phrase an adverb that
modifies a verb predicate.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        For all feature templates, “A-” or “P-” are used respectively to signify that the
feature corresponds to the argument in question (
        xi
        ), or rather is derived from the
verbal predicate that the argument depends on.
       </p>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        General features:
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         We use and modify 18 features used for Japanese from the prior work of Björkelund et al.
         [2]
         , excluding SENSE, POSITION, and re-ranker features.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p2">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Stem: a stem without any attachment. For instance, the first word
            Poleun
            at the Figure
            1
            consists of a stem
            Pol
            plus Josa
            eun
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            POS_Lv1: the first level (coarse classification) of a POS tag such as noun, verb, adjective, or adverb.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            POS_Lv2: the second level (fine classification) of a POS tag. If POS_Lv1 is
            noun
            , either a proper noun, common noun, or other kinds of nouns is the POS_Lv2.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i4.p1">
           <p class="ltx_p">
            Case: the case type such as SBJ, OBJ, or COMP.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The above features are also applied to some dependency children, parents, and siblings of arguments as shown in Table
         2
         .
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Korean-specific features:
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         We have 11 different kinds of features for the Josa (5) and Eomi (6). We highlight several below:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p2">
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            A-JosaExist: an indicator feature checking any Josa whether or not exists in an argument. It is set to 1 if any Josa exists, otherwise 0.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            A-JosaClass: the linguistic classification of Josa with a total of 8 classes. These classes are adverbial, auxiliary, complemental, connective, determinative, objective, subjective, and vocative.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            A-JosaLength: the number of morphemes consisting of Josa. At most five morphemes are combined to consist of one Josa in our data set.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            A-JosaMorphemes: Each morpheme composing the Josa.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i5.p1">
           <p class="ltx_p">
            A-JosaIdentity: The Josa itself.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i6.p1">
           <p class="ltx_p">
            A-EomiClass_Lv1: the linguistic classification of Eomi with a total of 14 classes. These 14 classes are adverbial, determinative, coordinate, exclamatory, future tense, honorific, imperative, interrogative, modesty, nominal, normal, past tense, petitionary, and subordinate.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i7.p1">
           <p class="ltx_p">
            A-EomiClass_Lv2: Another linguistic classification of Eomi with a total of 4 classes. The four classes are closing, connection, prefinal, and transmutation. The EomiClass_Lv1 and Lv2 are combined to display the characteristic of Eomi such as ‘Nominal Transmutation Eomi’, but not all combinations are possible.
           </p>
          </div>
         </li>
        </ul>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        Latent morpheme representation features:
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         To alleviate the sparsity, a lingering problem in NLP, we employ three kinds of latent morpheme representations induced from a larger body of unsupervised text data. These are (i) linear continuous representation through Canonical Correlation Analysis
         [7]
         , (ii) non-linear continuous representation through Deep learning
         [6]
         , and (iii) discrete representation through Brown Clustering
         [17]
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P3.p2">
        <p class="ltx_p">
         The first two representations are 50 dimensional continuous vectors for each morpheme, and the latter is a set of 256 clusters over morphemes.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Experiments and Results
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        We categorized our experiments by the scenarios below, and all results are summarized in Table
        3
        . The F1-score results were investigated for each scenario. We randomly divided our data into 90% training and 10% test sets for all scenarios.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        For latent morpheme representations, we used the Donga news article corpus.
        The Donga corpus contains 366,636 sentences with 25.09 words on average. The Domain of this corpus covers typical news articles such as health, entertainment, technology, politics, world and others. We ran Kokoma Korean morpheme analyzer
        on each sentence of the Donga corpus to divide words into morphemes to build latent morpheme representations.
       </p>
      </div>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        1st Scenario:
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         We first tested on general features in previous work (2nd column in Table
         3
         ). We achieved 64.83% and 66.88% on the PKPB and our corpus. When the both corpora were combined, we had 64.86%.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        2nd Scenario:
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         We then added the Korean-specific morphological features to signify its appropriateness in this scenario. These features increased greatly performance improvements (3rd column in Table
         3
         ). Although both the PKPB and our corpus had improvements, the improvements were the most notable on our corpus. This is because PKPB POS tags might be too coarse. We achieved 75.17%, 80.33%, and 78.61% on the PKPB, our corpus, and the combined one, respectively.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        3rd Scenario:
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         This scenario is to reveal the effects of the different latent morpheme representations (4-6th columns in Table
         3
         ). These three representations are from CCA, deep learning, and Brown clustering. The results gave evidences that all representations increased the performance.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P4">
       <h3 class="ltx_title ltx_title_paragraph">
        4th Scenario:
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         We augmented our model with all kinds of features (the last column in Table
         3
         ). We achieved our best F1-score of 81.07% over all scenarios on our corpus.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
