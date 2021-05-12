<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   A Piece of My Mind: A Sentiment Analysis Approachfor Online Dispute Detection.
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
       We investigate the novel task of
       online dispute detection
       and propose a sentiment analysis solution to the problem: we aim to identify the sequence of sentence-level sentiments expressed during a discussion and to use them as features in a classifier that predicts the DISPUTE/NON-DISPUTE label for the discussion as a whole.
We evaluate dispute detection approaches on a newly created corpus of Wikipedia Talk page disputes and find that classifiers that rely on our sentiment tagging features outperform those that do not. The best model achieves a very promising F1 score of 0.78 and an accuracy of 0.80.
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
        As the web has grown in popularity and scope, so has the promise of collaborative information environments for the joint creation and exchange of knowledge
        [11, 18]
        . Wikipedia, a wiki-based online encyclopedia, is arguably the best example: its distributed editing environment allows readers to collaborate as content editors and has facilitated the production of over four billion articles
        of surprisingly high quality
        [6]
        in English alone since its debut in 2001.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Existing studies of collaborative knowledge systems have shown, however, that the quality of the generated content (e.g. an encyclopedia article) is highly correlated with the effectiveness of the online collaboration
        [12, 14]
        ; fruitful collaboration, in turn, inevitably requires dealing with the disputes and conflicts that arise
        [13]
        .
Unfortunately, human monitoring of the often massive social media and collaboration sites to detect, much less mediate, disputes is not feasible.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this work, we investigate the heretofore novel task of
        dispute detection in online discussions
        .
Previous work in this general area has analyzed dispute-laden content to discover features correlated with conflicts and disputes
        [13]
        . Research focused primarily on cues derived from the edit history of the jointly created content (e.g. the number of revisions, their temporal density
        [13, 23]
        ) and relied on small numbers of manually selected discussions known to involve disputes.
In contrast, we investigate methods for the automatic detection, i.e. prediction, of discussions involving disputes. We are also interested in understanding whether, and which, linguistic features of the discussion are important for dispute detection.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Drawing inspiration from studies of human mediation of online conflicts (e.g.
        Billings and Watts (2010)
        ,
        Kittur et al. (2007)
        ,
        Kraut and Resnick (2012)
        ), we hypothesize that effective methods for dispute detection should take into account the sentiment and opinions expressed by participants in the collaborative endeavor.
As a result, we propose a sentiment analysis approach for online dispute detection that identifies the sequence of sentence-level sentiments (i.e. very negative, negative, neutral, positive, very positive) expressed during the discussion and uses them as features in a classifier that predicts the
        dispute
        /
        non-dispute
        label for the discussion as a whole.
Consider, for example, the snippet in Figure
        1
        from the Wikipedia Talk page for the article on Philadelphia; it discusses the choice of a picture for the article’s “infobox”. The sequence of almost exclusively negative statements provides evidence of a dispute in this portion of the discussion.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Unfortunately, sentence-level sentiment tagging for this domain is challenging in its own right due to the less formal, often ungrammatical, language and the dynamic nature of online conversations.
“
        Really, grow up
        ” (segment 3) should presumably be tagged as a negative sentence as should the sarcastic sentences “
        Sounds good?
        ” (in the same turn) and “
        congrats
        ” and “
        thank you
        ” (in segment 2). We expect that these, and other, examples will be difficult for the sentence-level classifier unless the discourse context of each sentence is considered.
Previous research on sentiment prediction for online discussions, however, focuses on turn-level predictions
        [7, 24]
        .
        As the first work that predicts sentence-level sentiment for online discussions, we investigate isotonic Conditional Random Fields (CRFs)
        [16]
        for the sentiment-tagging task as they preserve the advantages of the popular CRF-based sequential tagging models
        [15]
        while providing an efficient mechanism for encoding domain knowledge — in our case, a sentiment lexicon — through isotonic constraints on model parameters.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        We evaluate our dispute detection approach using a newly created corpus of discussions from Wikipedia Talk pages (3609 disputes, 3609 non-disputes).
        We find that classifiers that employ the learned sentiment features outperform others that do not. The best model achieves a very promising F1 score of 0.78 and an accuracy of 0.80 on the Wikipedia dispute corpus. To the best of our knowledge, this represents the first computational approach to automatically identify online disputes on a dataset of scale.
       </p>
      </div>
      <div class="ltx_paragraph" id="S1.SS0.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Additional Related Work.
       </h4>
       <div class="ltx_para" id="S1.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         Sentiment analysis has been utilized as a key enabling technique in a number of conversation-based applications. Previous work mainly studies the attitudes in spoken meetings
         [5, 7]
         or broadcast conversations
         [21]
         using variants of Conditional Random Fields
         [15]
         and predicts sentiment at the turn-level, while our predictions are made for each sentence.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Data Construction: A Dispute Corpus
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We construct the first dispute detection corpus to date; it consists of dispute and non-dispute discussions from Wikipedia Talk pages.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Step 1: Get Talk Pages of Disputed Articles.
        Wikipedia articles are edited by different editors. If an article is observed to have disputes on its
        talk page
        , editors can assign dispute tags to the article to flag it for attention.
In this research, we are interested in talk pages whose corresponding articles are labeled with the following tags:
        disputed
        ,
        totallydisputed
        ,
        disputed-section
        ,
        totallydisputed-section
        ,
        pov
        .
The tags indicate that an article is disputed, or the neutrality of the article is disputed (
        pov
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        We use the 2013-03-04 Wikipedia data dump, and extract talk pages for articles that are labeled with dispute tags by checking the revision history. This results in 19,071 talk pages.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Step 2: Get Discussions with Disputes.
        Dispute tags can also be added to
        talk pages
        themselves. Therefore, in addition to the tags mentioned above, we also consider the “Request for Comment” (
        rfc
        ) tag on talk pages. According to Wikipedia
        ,
        rfc
        is used to request outside opinions concerning the disputes.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        3609 discussions are collected with dispute tags found in the revision history. We further classify dispute discussions into three subcategories:
        Controversy
        ,
        Request for Comment (RFC)
        , and
        Resolved
        based on the tags found in discussions (see Table
        1
        ).
The numbers of discussions for the three types are 42, 3484, and 105, respectively.
Note that dispute tags only appear in a small number of articles and talk pages. There may exist other discussions with disputes.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        Step 3: Get Discussions without Disputes.
        Likewise, we collect non-dispute discussions from pages that are never tagged with disputes. We consider non-dispute discussions with at least 3 distinct speakers and 10 turns. 3609 discussions are randomly selected with this criterion. The average turn numbers for dispute and non-dispute discussions are 45.03 and 22.95, respectively.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Sentence-level Sentiment Prediction
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        This section describes our sentence-level sentiment tagger, from which we construct features for dispute detection (Section
        4
        ).
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Consider a discussion comprised of sequential turns; each turn consists of a sequence of sentences. Our model takes as input the sentences
        𝐱={x1,⋯,xn}
        from a single turn, and outputs the corresponding sequence of sentiment labels
        𝐲={y1,⋯,yn}
        , where
        yi∈𝒪,𝒪={NN,N,O,P,PP}
        . The labels in
        𝒪
        represent very negative (NN), negative (N), neutral (O), positive (P), and very positive (PP), respectively.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Given that traditional Conditional Random Fields (CRFs)
        [15]
        ignore the ordinal relations among sentiment labels, we choose
        isotonic CRFs
        [16]
        for sentence-level sentiment analysis as they can enforce monotonicity constraints on the parameters consistent with the ordinal structure and domain knowledge (e.g. word-level sentiment conveyed via a lexicon).
Concretely, we take a lexicon
        ℳ=ℳp∪ℳn
        , where
        ℳp
        and
        ℳn
        are two sets of features (usually words) identified as strongly associated with positive and negative sentiment. Assume
        μ⟨σ,w⟩
        encodes the weight between label
        σ
        and feature
        w
        , for each feature
        w∈ℳp
        ; then the isotonic CRF enforces
        σ≤σ′⇒μ⟨σ,w⟩≤μ⟨σ′,w⟩
        .
For example, when “totally agree” is observed in training, parameter
        μ⟨PP,totally⁢agree⟩
        is likely to increase. Similar constraints are defined on
        ℳn
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Our lexicon is built by combining MPQA
        [22]
        , General Inquirer
        [19]
        , and SentiWordNet
        [3]
        lexicons. Words with contradictory sentiments are removed. We use the features in Table
        2
        for sentiment prediction.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Syntactic/Semantic Features.
        We have two versions of dependency relation features, the original form and a form that generalizes a word to its POS tag, e.g. “nsubj(wrong, you)” is generalized to “nsubj(
        ADJ
        , you)” and “nsubj(wrong,
        PRP
        )”.
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        Discourse Features.
        We extract the initial unigram, bigram, and trigram of each utterance as discourse features
        [9]
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        Sentiment Features.
        We gather connectives from the Penn Discourse TreeBank
        [17]
        and combine them with any sentiment word that precedes or follows it as new features. Sentiment dependency relations are the dependency relations that include a sentiment word. We replace those words with their polarity equivalents. For example, relation “nsubj(wrong, you)” becomes “nsubj(
        SentiWordn⁢e⁢g
        , you)”.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Online Dispute Detection
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Training A Sentiment Classifier
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Dataset.
         We train the sentiment classifier using the
         Authority and Alignment in Wikipedia Discussions (AAWD)
         corpus
         [1]
         on a 5-point scale (i.e. NN, N, O, P, PP).
AAWD consists of 221 English Wikipedia discussions with positive and negative alignment annotations.
Annotators either label each sentence as positive, negative or neutral, or label the full turn. For instances that have only a turn-level label, we assume all sentences have the same label as the turn. We further transform the labels into the five sentiment labels. Sentences annotated as being a positive alignment by at least two annotators are treated as very positive (PP). If a sentence is only selected as positive by one annotator or obtains the label via turn-level annotation, it is positive (P). Very negative (NN) and negative (N) are collected in the same way. All others are neutral (O). Among all 16,501 sentences in AAWD, 1,930 and 1,102 are labeled as NN and N. 532 and 99 of them are PP and P. The other 12,648 are considered neutral.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Evaluation.
         To evaluate the performance of the sentiment tagger, we compare to two baselines. (1)
         Baseline (Polarity)
         : a sentence is predicted as positive if it has more positive words than negative words, or negative if more negative words are observed. Otherwise, it is neutral. (2)
         Baseline (Distance)
         is extended from
         [8]
         . Each sentiment word is associated with the closest second person pronoun, and a surface distance is computed. An SVM classifier
         [10]
         is trained using features of the sentiment words and minimum/maximum/average of the distances.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         We also compare with two state-of-the-art methods that are used in sentiment prediction for conversations: (1) an SVM (RBF kernel) that is employed for identifying sentiment-bearing sentences
         [8]
         , and (dis)agreement detection
         [24]
         in online debates; (2) a
Linear
CRF for (dis)agreement identification in broadcast conversations
         [21]
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         We evaluate the systems using standard F1 on classes of positive, negative, and neutral, where samples predicted as PP and P are positive alignment, and samples tagged as NN and N are negative alignment.
Table
         3
         describes the main results on the AAWD dataset: our isotonic CRF based system significantly outperforms the alternatives for positive and negative alignment detection (paired-
         t
         test,
         p&lt;0.05
         ).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Dispute Detection
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We model dispute detection as a standard binary classification task, and investigate four major types of features as described below.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Lexical Features.
         We first collect
         unigram
         and
         bigram
         features for each discussion.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         Topic Features.
         Articles on specific topics, such as politics or religions, tend to arouse more disputes. We thus extract the
         category
         information of the corresponding article for each talk page. We further utilize
         unigrams
         and
         bigrams
         of the category as topic features.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         Discussion Features.
         This type of feature aims to capture the structure of the discussion. Intuitively, the more turns or the more participants a discussion has, the more likely there is a dispute. Meanwhile, participants tend to produce longer utterances when they make arguments. We choose
         number of turns
         ,
         number of participants
         ,
         average number of words in each turn
         as features. In addition, the frequency of revisions made during the discussion has been shown to be good indicator for controversial articles
         [20]
         , that are presumably prone to have disputes. Therefore, we encode the
         number of revisions
         that happened during the discussion as a feature.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         Sentiment Features.
         This set of features encode the sentiment distribution and transition in the discussion. We train our sentiment tagging model on the full AAWD dataset, and run it on the Wikipedia dispute corpus.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         Given that consistent negative sentiment flow usually indicates an ongoing dispute, we first extract features from
         sentiment distribution
         in the form of
         number/probability of sentiment per type
         .
We also estimate the
         sentiment transition
         probability
         P(St→St+1)
         from our predictions, where
         St
         and
         St+1
         are sentiment labels for the current sentence and the next.
We then have features as
         number/portion of sentiment transitions per type
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p7">
        <p class="ltx_p">
         Features described above mostly depict the
         global
         sentiment flow in the discussions. We further construct a
         local
         version of them, since sentiment distribution may change as discussion proceeds. For example, less positive sentiment can be observed as dispute being escalated.
We thus split each discussion into three equal length stages, and create sentiment distribution and transition features for each stage.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p8">
        <p class="ltx_p">
         Results and Error Analysis.
         We experiment with logistic regression, SVM with linear and RBF kernels, which are effective methods in multiple text categorization tasks
         [10, 25]
         . We normalize the features by standardization and conduct a 5-fold cross-validation. Two baselines are listed: (1) labels are randomly assigned; (2) all discussions have disputes.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p9">
        <p class="ltx_p">
         Main results for different classifiers are displayed in Table
         4
         . All learning based methods outperform the two baselines, and among them, SVM with the RBF kernel achieves the best F1 score and accuracy (0.78 and 0.80).
Experimental results with various combinations of features sets are displayed in Table
         5
         . As it can be seen, sentiment features obtains the best accuracy among the four types of features. A combination of topic, discussion, and sentiment features achieves the best performance on recall, F1, and accuracy. Specifically, the accuracy is significantly higher than all the other systems (paired-
         t
         test,
         p&lt;0.05
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p10">
        <p class="ltx_p">
         After a closer look at the results, we find two main reasons for incorrect predictions. Firstly, sentiment prediction errors get propagated into dispute detection. Due to the limitation of existing general-purpose lexicons, some opinionated dialog-specific terms are hard to catch. For example, “I told you over and over again…” strongly suggests a negative sentiment, but no single word shows negative connotation. Constructing a lexicon tuned for conversational text may improve the performance. Secondly, some dispute discussions are harder to detect than the others due to different dialog structures. For instance, the recalls for dispute discussions of “controversy”, “RFC”, and “resolved” are 0.78, 0.79, and 0.86 respectively. We intend to design models that are able to capture dialog structures in the future work.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p11">
        <p class="ltx_p">
         Sentiment Flow Visualization.
         We visualize the sentiment flow of two disputed discussions in Figure
         2
         .
The plots reveal persistent negative sentiment in unresolved disputes (top). For the resolved dispute (bottom), participants show gratitude when the problem is settled.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
