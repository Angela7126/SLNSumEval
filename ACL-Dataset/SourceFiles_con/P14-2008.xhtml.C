<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improving Citation Polarity Classification with Product Reviews.
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
       Recent work classifying citations in scientific literature has shown
that it is possible to improve classification results with extensive
feature engineering. While this result confirms that citation
classification is feasible, there are two drawbacks to this
approach: (i) it requires a large annotated corpus for supervised
classification, which in the case of scientific literature is quite
expensive; and (ii) feature engineering that is too specific to one
area of scientific literature may not be portable to other domains,
even within scientific literature. In this paper we address these
two drawbacks. First, we frame citation classification as a domain
adaptation task and leverage the abundant labeled data available in
other domains. Then, to avoid over-engineering specific citation
features for a particular scientific domain, we explore a deep
learning neural network approach that has shown to generalize well
across domains using unigram and bigram features. We achieve better
citation classification results with this cross-domain approach than
using in-domain classification.
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
        Citations have been categorized and studied for a half-century
        [15]
        to better understand when and how citations are
used, and to record and measure how information is exchanged (e.g.,
networks of co-cited papers or authors
        [26]
        ).
Recently, the value of this information has been shown in practical
applications such as information retrieval (IR)
        [25]
        , summarization
        [24]
        , and
even identifying scientific breakthroughs
        [27]
        .
We expect that by identifying and labeling the
        function
        of
citations we can improve the effectiveness of these applications.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        There has been no consensus on what aspects or functions of a
citation should be annotated and how. Early citation classification
focused more on
        citation motivation
        [16]
        , while
later classification considered more the
        citation function
        [9]
        . Recent studies using automatic classification have continued this tradition of
introducing a new classification scheme with each new investigation
into the use of citations
        [22, 29, 13, 1]
        .
One distinction that has been more consistently annotated across
recent citation classification studies is between
        positive
        and
        negative
        citations
        [3, 2, 1]
        .
        The popularity of this
distinction likely owes to the prominence of sentiment analysis in NLP
        [20]
        . We follow much of the recent work on citation
classification and concentrate on citation polarity.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Domain Adaptation
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        By concentrating on citation polarity we are able to compare our
classification to previous citation polarity work. This choice
also allows us to access the wealth of existing data containing
polarity annotation and then frame the task as a domain adaptation
problem. Of course the risk in approaching the problem as domain
adaptation is that the domains are so different that the
representation of a positive instance of a movie or product review,
for example, will not coincide with that of a positive scientific
citation. On the other hand, because there is a limited amount of
annotated citation data available, by leveraging large amounts of
annotated polarity data we could potentially even improve citation
classification.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        We treat citation polarity classification as a sentiment analysis
domain adaptation task and therefore must be careful not to define
features that are too domain specific. Previous work in citation
polarity classification focuses on finding new citation features to
improve classification, borrowing a few from text classification in
general (e.g.,
        n
        -grams), and perhaps others from sentiment analysis
problems (e.g., the polarity lexicon from
        Wilson et al. (2005)
        ). We would
like to do as little feature engineering as possible to ensure that
the features we use are meaningful across domains. However, we do
still want features that somehow capture the inherent positivity or
negativity of our labeled instances, i.e., citations or Amazon product
reviews. Currently a popular approach for accomplishing this is to
use deep learning neural networks
        [4]
        , which have been
shown to perform well on a variety of NLP tasks using only bag-of-word
features
        [10]
        . More specifically related to our
work, deep learning neural networks have been successfully employed
for sentiment analysis
        [28]
        and for sentiment domain
adaptation
        [17]
        . In this paper we examine one of
these approaches, marginalized stacked denoising autoencoders (mSDA)
from
        Chen et al. (2012)
        , which has been successful in classifying
the polarity of Amazon product reviews across product domains. Since
mSDA achieved state-of-the-art performance in Amazon product domain
adaptation, we are hopeful it will also be effective when switching to a
more distant domain like scientific citations.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Experimental Setup
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Corpora
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We are interested in domain adaptation for citation classification and therefore need a
target dataset of citations and a non-citation source dataset. There
are two corpora available that contain citation function annotation,
the DFKI Citation Corpus
         [13]
         and the IMS Citation
Corpus
         [19]
         . Both corpora have only about 2000
instances; unfortunately, there are no larger corpora available with
citation annotation and this task would benefit from more annotated
data. Due to the infrequent use of negative
citations, a substantial annotation effort (annotating over 5 times more data)
would be necessary to reach 1000 negative citation instances, which is
the number of negative instances in a single domain in
the multi-domain corpus described below.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         The DFKI Citation
Corpus
         has been used for classifying citation function
         [13]
         , but the dataset also
includes polarity annotation. The dataset has 1768 citation sentences
with polarity annotation: 190 are labeled as
         positive
         , 57 as
         negative
         , and the vast majority, 1521, are left
         neutral
         .
The second citation corpus, the IMS Citation
Corpus
         contains 2008 annotated citations: 1836 are labeled
         positive
         and 172 are labeled
         negative
         .
         Jochim and Schütze (2012)
         use
annotation labels from
         Moravcsik and Murugesan (1975)
         where positive
instances are labeled
         confirmative
         , negative instances are
labeled
         negational
         , and there is no neutral class. Because each
of the citation corpora is of modest size we combine them to form one
citation dataset, which we will refer to as CITD. The two citation
corpora comprising CITD both come from the ACL Anthology
         [5]
         : the IMS corpus uses the ACL proceedings from 2004
and the DFKI corpus uses parts of the proceedings from 2007 and 2008.
Since mSDA also makes use of large amounts of unlabeled data, we
extend our CITD corpus with citations from the proceedings of the
remaining years of the ACL, 1979–2003, 2005–2006, and 2009.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         There are a number of non-citation corpora available that contain
polarity annotation. For these experiments we use the Multi-Domain
Sentiment
Dataset
         (henceforth MDSD), introduced by
         Blitzer et al. (2007)
         .
We use the version of the MDSD that includes
         positive
         and
         negative
         labels for product
reviews taken from Amazon.com in the following domains: books, dvd,
electronics, and kitchen. For each domain there are 1000 positive
reviews and 1000 negative reviews that comprise the “labeled” data,
and then roughly 4000 more reviews in the “unlabeled”
         data. Reviews
were preprocessed so that for each review you find a list of unigrams
and bigrams with their frequency within the review. Unigrams from a
stop list of 55 stop words are removed, but stop words in bigrams
remain.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Table
         1
         shows the distribution of polarity labels in the
corpora we use for our experiments. We combine the DFKI and IMS
corpora into the CITD corpus. We omit the citations labeled
         neutral
         from the DFKI corpus because the IMS corpus does not
contain neutral annotation nor does the MDSD. It is the case in many
sentiment analysis corpora that only positive and negative instances
are included, e.g.,
         [23]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         The citation corpora presented above are both unbalanced and both have
a highly skewed distribution. The MDSD on the other hand is
evenly balanced and an effort was even made to keep the data treated
as “unlabeled” rather balanced. For this reason, in line with
previous work using MDSD, we balance the labeled portion of the CITD
corpus. This is done by taking 179 unique negative sentences in the
DFKI and IMS corpora and randomly selecting an equal number of
positive sentences.
The IMS corpus can have multiple labeled citations per sentence: there are 122
sentences containing the 172 negative citations from Table
         1
         .
The final CITD corpus
comprises this balanced corpus of 358 labeled citation sentences plus another
22,093 unlabeled citation sentences.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         In our experiments, we restrict our features to unigrams and bigrams
from the product review or citation context (i.e., the sentence containing the citation). This follows previous
studies in domain adaptation
         [6, 17]
         .
         Chen et al. (2012)
         achieve
state-of-the-art results on MDSD by testing the 5000 and 30,000 most
frequent unigram and bigram features.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Previous work in citation classification has largely focused on
identifying new features for improving classification accuracy. A
significant amount of effort goes into engineering new features, in
particular for identifying cue phrases,
e.g.,
         [30, 13]
         . However, there seems to
be little consensus on which features help most for this task. For
example,
         Abu-Jbara et al. (2013)
         and
         Jochim and Schütze (2012)
         find the list of polar words from
         Wilson et al. (2005)
         to be useful,
and neither study lists dependency relations as significant features.
         Athar (2011)
         on the other hand reported significant improvement
using dependency relation features and found that the same list of
polar words slightly hurt classification accuracy. The classifiers
and implementation of features varies between these studies, but the
problem remains that there seems to be no clear set of features for
citation polarity classification.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         The lack of consensus on the most useful citation polarity features
coupled with the recent success of deep learning neural networks
         [10]
         further motivate our choice to limit our
features to the
         n
         -grams available in the product review or citation
context and not rely on external resources or tools for additional
features.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Classification with mSDA
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         For classification we use marginalized stacked denoising autoencoders
(mSDA) from
         Chen et al. (2012)
         plus a linear
SVM. mSDA takes the concept of
         denoising
         – introducing noise
to make the autoencoder more robust – from
         Vincent et al. (2008)
         ,
but does the optimization in closed form, thereby avoiding iterating
over the input vector to stochastically introduce noise. The result
of this is faster run times and currently state-of-the-art performance
on MDSD, which makes it a good choice for our domain adaptation task.
The mSDA implementation comes with LIBSVM, which we replace with
LIBLINEAR
         [14]
         for faster run times with no decrease in
accuracy. LIBLINEAR, with default settings, also serves as our
baseline.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Outline of Experiments
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Our initial experiments simply extend those of
         Chen et al. (2012)
         (and others who have used MDSD) by adding another domain, citations.
We train on each of the domains from the MDSD – books, dvd,
electronics, and kitchen – and test on the citation data. We split
the labeled data 80/20 following
         Blitzer et al. (2007)
         (cf.
         Chen et al. (2012)
         train on all “labeled” data and test on
the “unlabeled” data). These experiments should help answer two
questions: does a larger amount of training data, even if out of
domain, improve citation classification; and how well do the different
product domains generalize to citations (i.e., which domains are most
similar to citations)?
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         In contrast to previous work using MDSD,

a lot of the work in domain
adaptation also leverages a small amount of labeled target data. In
our second set of experiments, we follow the domain adaptation
approaches described in
         [12]
         and train on product review
and citation data before testing on citations.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Results and Discussion
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Citation mSDA
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Our initial results show that using mSDA for domain adaptation to citations actually outperforms in-domain classification. In Figure
         1
         we compare citation classification with mSDA to the SVM
baseline.
Each pair of vertical bars represents
training on a domain from MDSD (e.g., books) and testing on CITD. The
dark gray bar indicates the
         F1
         scores for the SVM baseline using
the 30,000 features and the lighter gray bar shows the mSDA results.
The black horizontal line indicates the
         F1
         score for in-domain
citation classification, which sometimes represents the goal for
domain adaptation. We can see that using a larger dataset, even if
out of domain, does improve citation classification. For books, dvd,
and electronics, even the SVM baseline improves on in-domain
classification. mSDA does better than the
baseline for all domains except dvd. Using a larger training set,
along with mSDA, which makes use of the unlabeled data, leads to the best
results for citation classification.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         In domain adaptation we would expect the domains most similar to the
target to lead to the highest results. Like
         Dai et al. (2007)
         , we measure the Kullback-Leibler divergence between the source and target domains’
distributions.
According to this measure, citations are most similar to the
books domain. Therefore, it is not surprising that training on books
performs well on citations, and intuitively, among the domains in the
Amazon dataset, a book review is most similar to a scientific
citation. This makes the good mSDA results for electronics a bit more
surprising.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Easy Domain Adaptation
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         The results in Section
         4.1
         are for
         semi-supervised
         domain
adaptation: the case where we have some large annotated corpus
(Amazon product reviews) and a large unannotated corpus (citations).
There have been a number of other successful attempts at
         fully
supervised
         domain adaptation, where it is assumed that some small amount of
data is annotated in the target domain
         [7, 12, 18]
         . To see how mSDA
compares to supervised domain adaptation we take the various approaches
presented by
         Daumé III (2007)
         . The results of this comparison can
be seen in Table
         2
         . Briefly, “All” trains on source
and target data; “Weight” is the same as “All” except that
instances may be weighted differently based on their domain (weights
are chosen on a development set); “Pred” trains on the source data,
makes predictions on the target data, and then trains on the target
data with the predictions; “LinInt” linearly interpolates
predictions using the source-only and target-only models (the
interpolation parameter is chosen on a development set); “Augment”

uses a larger feature set with source-specific and target-specific copies
of features; see
         [12]
         for further details.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         We are only
interested in citations as the target domain. Daumé’s source-only baseline
corresponds to the “Baseline” column for domains: books, dvd,
electronics, and kitchen; while his target-only baseline can be seen for citations
in the last row of the “Baseline” column in
Table
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         The semi-supervised mSDA performs quite well with
respect to the fully supervised approaches, obtaining the best
results for books and electronics, which are also the highest scores
overall. Weight and Pred have the highest
         F1
         scores for dvd and
kitchen respectively.
         Daumé III (2007)
         noted that the “Augment”
algorithm performed best when the target-only results were better than
the source-only results. When this was not the case in his experiments, i.e., for the
treebank chunking task, both Weight and Pred were among the best
approaches. In our experiments, training on source-only outperforms
target-only, with the exception of the kitchen domain.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         We have included the line for citations to see the results training
only on the target data (
         F1=51.9
         ) and to see the improvement when
using all of the unlabeled data with mSDA (
         F1=54.9
         ).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Discussion
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         These results are very promising. Although they are not quite as high as
other published results for citation polarity
         [1]
         , we have shown that you can improve citation polarity
classification by leveraging large amounts of annotated data from
other domains and using a simple set of features.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         mSDA and fully supervised approaches can also be straightforwardly
combined. We do not present those results here due to space
constraints. The combination led to mixed results: adding mSDA to
the supervised approaches tended to improve
         F1
         over those
approaches but results never exceeded the top mSDA numbers in
Table
         2
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Teufel et al. (2006b)
        introduced automatic citation function classification,
with classes that could be grouped as positive, negative,
and neutral. They relied in part on a manually compiled list of cue phrases
that
cannot easily be transferred to other classification schemes or
other scientific domains.
        Athar (2011)
        followed this and was the first to
specifically target polarity classification on scientific
citations. He found that dependency tuples contributed
the most significant improvement in results.
        Abu-Jbara et al. (2013)
        also looks at both citation
function and citation polarity. A big contribution of this work is
that they also train a CRF sequence tagger to find the citation
context, which significantly improves results over using only the
citing sentence. Their feature analysis indicates that lexicons for
negation, speculation, and polarity were most important for improving
polarity classification.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
