<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improving Twitter Sentiment Analysis with Topic-Based Mixture Modeling and Semi-Supervised Training.
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
       In this paper, we present multiple approaches to improve sentiment analysis on Twitter data.
We first establish a state-of-the-art baseline with a rich feature set. Then we build a topic-based sentiment
mixture model with topic-specific data in a semi-supervised training framework. The topic information
is generated through topic modeling based on an efficient implementation of Latent Dirichlet Allocation (LDA).
The proposed sentiment model outperforms the top system in the task of
       Sentiment Analysis in Twitter
       in SemEval-2013 in terms of averaged F scores.
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
        Social media, such as Twitter and Facebook, has attracted significant attention in recent years.
The vast amount of data available online provides a unique opportunity to the people working on natural
language processing (NLP) and related fields. Sentiment analysis is one of the areas that has large potential
in real-world applications. For example, monitoring the trend of sentiment
for a specific company or product mentioned in social media can be useful in stock prediction and product marketing.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper, we focus on sentiment analysis of Twitter data (tweets). It is one of the
challenging tasks in NLP given the length limit on each tweet (up to 140 characters) and also
the informal conversation. Many approaches have been proposed previously to improve sentiment
analysis on Twitter data. For example, Nakov et al. (2013) provide an overview on the systems
submitted to one of the SemEval-2013 tasks,
        Sentiment Analysis in Twitter
        . A variety of
features have been utilized for sentiment classification on tweets. They include lexical features (e.g. word lexicon),
syntactic features (e.g. Part-of-Speech), Twitter-specific features (e.g. emoticons), etc.
However, all of these features only capture local information in the data and do not take into
account of the global higher-level information, such as topic information.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Two example tweets are given below, with the word “
        offensive
        ” appearing in both of them.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Im gonna post something that might be
           offensive
           to people in Singapore.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           #FSU
           offensive
           coordinator Randy Sanders coached for Tennessee in 1st #BCS title game.
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        Generally “
        offensive
        ” is used as a negative word (as in the first tweet), but it bears no sentiment
in the second tweet when people are talking about a football game.
Even though some local contextual features could be helpful to distinguish the two cases above,
they still may not be enough to get the sentiment on the whole message correct.
Also, the local features often suffer from the sparsity problem.
This motivates us to explore topic information explicitly in the task of sentiment analysis on Twitter data.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        There exists some work on applying topic information in sentiment analysis,
such as
        [Mei et al.2007]
        ,
        [Branavan et al.2008]
        ,
        [Jo and Oh2011]
        and
        [He et al.2012]
        .
All these work are significantly different from what we propose in this work. Also they are
conducted in a domain other than Twitter. Most recently, Si et al. (2013) propose a continuous Dirichlet Process
Mixture model for Twitter sentiment, for the purpose of stock prediction. Unfortunately there is no evaluation on the
accuracy of sentiment classification alone in that work. Furthermore, no standard
training or test corpus is used, which makes comparison with other approaches difficult.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Our work is organized in the following way:
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           We first propose a universal sentiment model that utilizes various features and resources. The universal
model outperforms the top system submitted to the SemEval-2013 task
           [Mohammad et al.2013]
           ,
which was trained and tested
on the same data. The universal model serves as a strong baseline and also provides an option for smoothing later.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           We introduce a topic-based mixture model for Twitter sentiment. The model is integrated in the framework of
semi-supervised training that takes advantage of large amount of un-annotated Twitter data. Such a mixture model
results in further improvement on the sentiment classification accuracy.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           We propose a smoothing technique through interpolation between universal model and topic-based mixture model.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           We also compare different approaches for topic modeling, such as cross-domain topic identification by
utilizing data from newswire domain.
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Universal Sentiment Classifier
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        In this section we present a universal topic-independent sentiment classifier to establish a state-of-the-art baseline.
The sentiment labels are either positive, neutral or negative.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        SVM Classifier
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Support Vector Machine (SVM) is an effective classifier that can achieve good performance in high-dimensional
feature space. An SVM model represents the examples as points in space, mapped so that the examples of the
different categories are separated by a clear margin as wide as possible. In this work an SVM classifier is trained
with LibSVM
         [Chang and Lin2011]
         , a widely used toolkit. The linear kernel is found to achieve higher accuracy than other
kernels in our initial experiments. The option of probability estimation in LibSVM is turned on so that it can produce the
probability of sentiment class
         c
         given tweet
         x
         at the classification time, i.e.
         P(c|x)
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         The training and testing data are run through tweet-specific tokenization, similar to that used in the CMU Twitter NLP
tool
         [Gimpel et al.2011]
         . It is shown in Section 5 that such customized tokenization is helpful.
Here are the features that we use for classification:
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <ul class="ltx_itemize" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Word N-grams: if certain N-gram (unigram, bigram, trigram or 4-gram) appears in the tweet, the corresponding
feature is set to 1, otherwise 0. These features are collected from training data, with a count cutoff to
avoid overtraining.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Manual lexicons: it has been shown in other work
            [Nakov et al.2013]
            that lexicons with positive and negative words
are important to sentiment classification. In this work, we adopt the lexicon from Bing Liu
            [Hu and Liu2004]
            which includes
about 2000 positive words and 4700 negative words. We also experimented with the popular MPQA
            [Wilson et al.2005]
            lexicon but
found no extra improvement on accuracies. A short list of Twitter-specific positive/negative words are also added to enhance
the lexicons. We generate two features based on the lexicons: total number of positive words or
negative words found in each tweet.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i3.p1">
           <p class="ltx_p">
            Emoticons: it is known that people use emoticons in social media data to express their
emotions. A set of popular emoticons are collected from the Twitter data we have. Two features are created to
represent the presence or absence of any positive/negative emoticons.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i4.p1">
           <p class="ltx_p">
            Last sentiment word: a “sentiment word” is any word in the positive/negative lexicons mentioned
above. If the last sentiment word found in the tweet is positive (or negative), this feature is set to 1 (or -1). If
none of the words in the tweet is sentiment word, it is set to 0 by default.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i5.p1">
           <p class="ltx_p">
            PMI unigram lexicons: in
            [Mohammad et al.2013]
            two lexicons were automatically generated based on pointwise mutual
information (PMI). One is
            NRC Hashtag Sentiment Lexicon
            with 54K unigrams, and the other is
            Sentiment140 Lexicon
            with 62K unigrams. Each word in the lexicon has an associated sentiment score.
We compute 7 features based on each of the two lexicons: (1) sum of sentiment score;
(2) total number of positive words (with score
            s&gt;1
            ); (3) total number of negative words (
            s&lt;-1
            );
(4) maximal positive score; (5) minimal negative score; (6) score of the last positive words;
(7) score of the last negative words.
Note that for the second and third features, we ignore those
with sentiment scores between -1 and 1, since we found that inclusion of those weak subjective words results in
unstable performance.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i6.p1">
           <p class="ltx_p">
            PMI bigram lexicon: there are also 316K bigrams in the
            NRC Hashtag Sentiment Lexicon
            . For bigrams,
we did not find the sentiment scores useful. Instead, we only compute two features based on counts only:
total number of positive bigrams; total number of negative bigrams.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i7.p1">
           <p class="ltx_p">
            Punctuations: if there exists exclamation mark or question mark in the tweet, the feature is set to 1, otherwise
set to 0.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i8" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i8.p1">
           <p class="ltx_p">
            Hashtag count: the number of hashtags in each tweet.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i9" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i9.p1">
           <p class="ltx_p">
            Negation: we collect a list of negation words, including some informal words frequently observed in
online conversations, such as “
            dunno
            ” (“don’t know”), “
            nvr
            ” (“never”), etc. For any sentiment words
within a window following a negation word and not after punctuations ‘.’, ‘,’, ‘;’, ‘?’, or ‘!’, we reverse
its sentiment from positive to negative, or vice versa, before computing the lexicon-based features
mentioned earlier. The window size was set to 4 in this work.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i10" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i10.p1">
           <p class="ltx_p">
            Elongated words: the number of words in the tweet that have letters repeated by at least 3 times in a row, e.g.
the word “
            gooood
            ”.
           </p>
          </div>
         </li>
        </ul>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Topic-Based Sentiment Mixture
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Topic Modeling
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Latent Dirichlet Allocation (LDA)
         [Blei et al.2003]
         is one of the widely adopted generative models for topic modeling.
The fundamental idea is that a document is a mixture of topics. For each document there is a multinomial
distribution over topics, and a Dirichlet prior
         D⁢i⁢r⁢(α)
         is introduced on such distribution.
For each topic, there is
another multinomial distribution over words. One of the popular algorithms for LDA model parameter
estimation and inference is Gibbs sampling
         [Griffiths and Steyvers2004]
         , a form of Markov Chain Monte Carlo.
We adopt the efficient implementation of Gibbs sampling as proposed in
         [Yao et al.2009]
         in this work.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Each tweet is regarded as one document. We conduct pre-processing by removing stop words and some of the frequent words
found in Twitter data. Suppose that there are
         T
         topics in total in the training data,
i.e.
         t1
         ,
         t2
         , …,
         tT
         . The posterior probability of each topic given tweet
         xi
         is computed as in Eq.
         1
         :
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        Pt(tj|xi)=Ci⁢j+αj∑k=1TCi⁢k+T⁢αj

(1)
        <p class="ltx_p">
         where
         Ci⁢j
         is the number of times that topic
         tj
         is assigned to some word in tweet
         xi
         , usually
averaged over multiple iterations of Gibbs sampling.
         αj
         is the
         j
         -th dimension of the hyperparameter of Dirichlet distribution that can be optimized during model estimation.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Sentiment Mixture Model
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Once we identify the topics for tweets in the training data, we can split the data into multiple subsets
based on topic distributions. For each subset, a separate sentiment model can be trained. There are many
ways of splitting the data. For example, K-means clustering can be conducted based on the similarity between
the topic distribution vectors or their transformed versions. In this work, we assign tweet
         xi
         to cluster
         j
         if
         Pt(tj|xi)&gt;τ
         or
         Pt(tj|xi)=maxkPt(tk|xi)
         . Note that this is a soft clustering, with some
tweets possibily assigned to multiple topic-specific clusters. Similar to the universal model, we train
         T
         topic-specific sentiment models with LibSVM.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         During classification on test tweets, we run topic inference
and sentiment classification with multiple sentiment models. They jointly determine the final probability
of sentiment class
         c
         given tweet
         xi
         as the following in a sentiment mixture model:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        P(c|xi)=∑j=1TPm(c|tj,xi)Pt(tj|xi)

(2)
        <p class="ltx_p">
         where
         Pm(c|tj,xi)
         is the probability of sentiment
         c
         from topic-specific sentiment model trained on topic
         tj
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Smoothing
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Additionally, we also experiment with a smoothing technique through linear interpolation between the universal
sentiment model and topic-based sentiment mixture model.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           P(c|xi)
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           θ×PU(c|xi)+(1-θ)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="2">
           <span class="ltx_tag ltx_tag_equation">
            (3)
           </span>
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
           ×
          </td>
          <td class="ltx_td ltx_align_left">
           ∑j=1TPm(c|tj,xi)Pt(tj|xi)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         θ
         is the interpolation parameter and
         PU(c|xi)
         is the probability of sentiment
         c
         given tweet
         xi
         from the universal sentiment model.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Semi-supervised Training
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section we propose an integrated framework of semi-supervised training that contains both topic modeling
and sentiment classification. The idea of semi-supervised training is to take advantage of large amount low-cost
un-annotated data (tweets in this case) to further improve the accuracy of sentiment classification. The algorithm
is as follows:
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <ol class="ltx_enumerate" id="I4">
        <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I4.i1.p1">
          <p class="ltx_p">
           Set training corpus
           D
           for sentiment classification to be the annotated training data
           Da
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I4.i2.p1">
          <p class="ltx_p">
           Train a sentiment model with current training corpus
           D
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I4.i3.p1">
          <p class="ltx_p">
           Run sentiment classification on the un-annotated data
           Du
           with the current sentiment model and
generate probabilities of sentiment classes for each tweet,
           P(c|xi)
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          4.
         </span>
         <div class="ltx_para" id="I4.i4.p1">
          <p class="ltx_p">
           Perform data selection. For those tweets with
           P(c|xi)&gt;p
           , add them to current training corpus
           D
           . The rest
is used to replace the un-annotated corpus
           Du
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i5" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          5.
         </span>
         <div class="ltx_para" id="I4.i5.p1">
          <p class="ltx_p">
           Train a topic model on
           D
           , and store the topic inference model and topic distributions of each tweet;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i6" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          6.
         </span>
         <div class="ltx_para" id="I4.i6.p1">
          <p class="ltx_p">
           Cluster data in
           D
           based on the topic distributions from Step 5 and train a separate sentiment model for
each cluster. Replace current sentiment model with the new sentiment mixture model;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i7" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          7.
         </span>
         <div class="ltx_para" id="I4.i7.p1">
          <p class="ltx_p">
           Repeat from Step 3 until finishing a pre-determined number of iterations or no more data is added to
           D
           in Step 4.
          </p>
         </div>
        </li>
       </ol>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experimental Results
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Data and Evaluation
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We conduct experiments on the data from the task B of
         Sentiment Analysis in Twitter
         in SemEval-2013. The distribution of positive, neutral and negative data is shown in Table
         1
         .
The development set is used to tune parameters and features. The test set is for the blind evaluation.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         For semi-supervised training experiments, we
explored two sets of additional data. The first one contains 2M tweets randomly sampled from the collection in January
and February 2014. The other
contains 74K news documents with 50M words collected during the first half year of 2013 from online newswire.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         For evaluation, we use macro averaged F score as in
         [Nakov et al.2013]
         , i.e. average of the F scores computed on
positive and negative classes only. Note that this does not make the task a binary classification problem.
Any errors related to neutral class (false positives or false negatives) will negatively impact the F scores.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Universal Model
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         In Table
         2
         , we show the incremental improvement in adding various features described in Section 2,
measured on the test set.
In addition to the features, we also find SVM weighting on the training samples is helpful. Due to the
skewness in class distribution in the training set, it is observed during error analysis on the development
set that subjective (positive/negative) tweets are more likely to be classified as neutral tweets. The
weights for positive, neutral and negative samples are set to be (1, 0.4, 1) based on the
results on the development set. As shown in Table
         2
         , weighting adds a 2% improvement.
With all features combined, the universal sentiment model achieves 69.7 on average F score.
The F score from the best system in SemEval-2013
         [Mohammad et al.2013]
         is also listed in the last row of
Table
         2
         for a comparison.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Topic-Based Mixture Model
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         For the topic-based mixture model and semi-supervised training, based on the experiments on the development set,
we set the parameter
         τ
         used in soft clustering to 0.4, the data selection parameter
         p
         to 0.96, and the
interpolation parameter for smoothing
         θ
         to 0.3. We found no more noticeable benefits after two iterations
of semi-supervised training. The number of topics is set to 100.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         The results on the test set are shown Table
         3
         , with the topic information
inferred from either Twitter data (second column) or newswire data (third column).
The first row shows the performance of the universal sentiment model as a baseline.
The second row shows the results from re-training the universal model by simply adding tweets
selected from two iterations of semi-supervised training (about 100K). It serves as another
baseline with more training data, for a fair comparison with the topic-based mixture modeling that uses
the same amount of training data.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         We also conduct an experiment by only considering the most likely topic for each tweet when computing the sentiment
probabilities. The results show that the topic-based mixture model outperforms both the baseline and the one
that considers the top topics only. Smoothing with the universal model adds further improvement in addition to
the un-smoothed mixture model. With the topic information inferred from Twitter data, the F score is 2 points
higher than the baseline without semi-supervised training and 1.4 higher than the baseline with semi-supervised data.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         As shown in the third column in Table
         3
         , surprisingly, the model with topic information inferred from the newswire
data works well on the Twitter domain. A 1.4 points of improvement can be obtained compared to the baseline.
This provides an opportunity for cross-domain topic identification when data from certain domain is more difficult
to obtain than others.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         In Table
         4
         , we provide some examples from the topics identified in tweets as well as the newswire
data. The most frequent words in each topic are listed in the table. We can clearly see that the topics are about
phones, sports, sales and politics, respectively.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
