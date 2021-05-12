<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Learning to Predict Distributions of Words Across Domains.
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
       Although the distributional hypothesis has been applied successfully in many natural language processing tasks,
systems using distributional information have been limited to a single domain because
the distribution of a word can vary between domains as the word’s predominant meaning changes.
However, if it were possible to
       predict
       how the distribution
of a word changes from one domain to another, the predictions could be used to
adapt a system trained in one domain to work in another.
We propose an unsupervised method to predict the distribution of
a word in one domain, given its distribution in another domain.
We evaluate our method on two tasks: cross-domain part-of-speech tagging
and cross-domain sentiment classification. In both tasks, our method significantly outperforms
competitive baselines and returns results that are statistically comparable to current state-of-the-art methods,
while requiring no task-specific customisations.
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
        The Distributional Hypothesis, summarised by the memorable line of
        –
        You shall know a word by the company it keeps
        –
has inspired a diverse range of research in natural language processing.
In such work, a word is represented by the distribution of other words that co-occur with it.
Distributional representations of words have been successfully used in
many language processing tasks such as
entity set expansion
        []
        ,
part-of-speech (POS) tagging and chunking
        []
        ,
ontology learning
        []
        ,
computing semantic textual similarity
        []
        ,
and lexical inference
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        However, the distribution of a word often varies
from one domain
        to another.
For example, in the domain of portable computer reviews the word
        lightweight
        is often associated
with positive sentiment bearing words such as
        sleek
        or
        compact
        ,
whereas in the movie review domain the same word is often associated with negative sentiment-bearing words such as
        superficial
        or
        formulaic
        .
Consequently, the distributional representations of the word
        lightweight
        will differ considerably between the
two domains. In this paper, given the distribution
        w→\cS
        of a word
        w
        in the source domain
        \cS
        ,
we propose an unsupervised method for
        predicting
        its distribution
        w→\cT
        in a different target domain
        \cT
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The ability to predict how the distribution of a word varies from one domain to another is vital
for numerous adaptation tasks. For example, unsupervised cross-domain sentiment classification
        []
        involves using sentiment-labeled
user reviews from the source domain, and unlabeled reviews from both the source and the target domains
to learn a sentiment classifier for the target domain.
Domain adaptation (DA) of sentiment classification becomes extremely challenging
when the distributions of words in the source and the target domains are very different,
because the features learnt from the source domain labeled reviews might not appear in the
target domain reviews that must be classified. By predicting the distribution of a word
across different domains, we can find source domain features that are similar to the features in
target domain reviews, thereby reducing the mismatch of features between the two domains.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We propose a two-step unsupervised approach to predict the distribution of a word across domains.
First, we create two lower dimensional latent feature spaces separately for the source and the target domains
using Singular Value Decomposition (SVD).
Second, we learn a mapping from the source domain latent feature space to the target domain latent feature space
using Partial Least Square Regression (PLSR).
The SVD smoothing in the first step both reduces the data sparseness in distributional representations
of individual words, as well as the dimensionality of the feature space, thereby enabling us to efficiently
and accurately learn a prediction model using PLSR in the second step.
Our proposed cross-domain word distribution prediction method is unsupervised in the sense that
it does not require any labeled data in either of the two steps.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Using two popular multi-domain datasets, we evaluate the proposed method in two prediction tasks:
(a) predicting the POS of a word in a target domain,
and (b) predicting the sentiment of a review in a target domain.
Without requiring any task specific customisations, systems based on our distribution prediction method
significantly outperform competitive baselines in both tasks.
Because our proposed distribution prediction method is unsupervised and
task independent, it is potentially useful for a wide range of DA tasks
such entity extraction
        []
        or dependency parsing
        []
        .
Our contributions are summarised as follows:
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Given the distribution
           w→\cS
           of a word
           w
           in a source domain
           \cS
           , we propose a method for learning
its distribution
           w→\cT
           in a target domain
           \cT
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
           Using the learnt distribution prediction model, we propose a method to learn a cross-domain POS tagger.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Using the learnt distribution prediction model, we propose a method to learn a cross-domain sentiment classifier.
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        To our knowledge, ours is the first successful attempt to learn a model that predicts the distribution of a word
across different domains.
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
        Learning semantic representations for words using documents from a single domain has received much attention
lately
        []
        .
As we have already discussed, the semantics of a word varies across different domains, and
such variations are not captured by models that only learn a single semantic representation for
a word using documents from a single domain.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        The POS of a word is influenced both by its context (
        contextual bias
        ), and
the domain of the document in which it appears (
        lexical bias
        ). For example, the word
        signal
        is
predominately used as a noun in MEDLINE, whereas it appears predominantly as an adjective in the Wall Street Journal (WSJ)
        []
        .
Consequently, a tagger trained on WSJ would incorrectly tag
        signal
        in MEDLINE.
        append the source domain labeled data with predicted pivots (i.e. words that
appear in both the source and target domains)
to adapt a POS tagger to a target domain.
        propose a cross-domain POS tagging method by training two separate models:
a generalised model and a domain-specific model. At tagging time, a sentence is tagged by the model
that is most similar to that sentence.
        train a Conditional Random Field (CRF) tagger with features retrieved from
a smoothing model trained using both source and target domain unlabeled data.
Adding latent states to the smoothing model further improves the POS tagging accuracy
        []
        .
        propose a training set filtering method where they eliminate
shorter words from the training data based on the intuition that
longer words are more likely to be examples of productive linguistic processes than shorter words.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The sentiment of a word can vary from one domain to another.
In Structural Correspondence Learning (SCL)
        []
        ,
a set of pivots are chosen using pointwise mutual information.
Linear predictors are then learnt to predict the occurrence of those pivots, and SVD
is used to construct a lower dimensional representation in which a binary classifier is trained.
Spectral Feature Alignment (SFA)
        []
        also uses pivots to compute an alignment between
domain specific and domain independent features. Spectral clustering is performed on a bipartite
graph representing domain specific and domain independent features to find a lower-dimensional
projection between the two sets of features.
The cross-domain sentiment-sensitive thesaurus (SST)
        []
        groups together words that express similar sentiments in different domains. The created thesaurus is used
to expand feature vectors during train and test stages in a binary classifier.
However, unlike our method, SCL, SFA, or SST do
        not
        learn a prediction model between
word distributions across domains.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Prior knowledge of the sentiment of words, such as sentiment lexicons,
has been incorporated into cross-domain sentiment classification.
        propose a joint sentiment-topic model that imposes a sentiment-prior
depending on the occurrence of a word in a sentiment lexicon.
        represent source and target domain reviews as nodes in a graph
and apply a label propagation algorithm to predict the sentiment labels for target domain
reviews from the sentiment labels in source domain reviews. A sentiment lexicon is used
to create features for a document. Although incorporation of prior sentiment knowledge is
a promising technique to improve accuracy in cross-domain sentiment classification,
it is complementary to our task of distribution prediction across domains.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        The
        unsupervised
        DA setting that we consider does not assume
the availability of labeled data for the target domain. However, if a small amount of labeled data
is available for the target domain, it can be used to further improve the performance of DA
tasks
        []
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Distribution Prediction
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        In-domain Feature Vector Construction
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Before we tackle the problem of learning a model to predict the distribution of a word across domains,
we must first compute the distribution of a word from a single domain.
For this purpose, we represent a word
         w
         using unigrams and bigrams that co-occur with
         w
         in a sentence
as follows.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Given a document
         H
         , such as a user-review of a product, we split
         H
         into sentences,
and lemmatize each word in a sentence using the RASP system
         []
         .
Using a standard stop word list, we filter out frequent non-content unigrams and select
the remainder as unigram features to represent a sentence.
Next, we generate bigrams of word lemmas and remove any bigrams that consists only of stop words.
Bigram features capture negations more accurately than unigrams, and have been found to be useful
for sentiment classification tasks.
Table
         1
         shows the unigram and bigram features we extract for a sentence using this procedure.
Using data from a single domain, we construct a feature co-occurrence matrix
         \mat⁢A
         in which columns correspond to unigram features and rows correspond to either unigram or bigram features.
The value of the element
         ai⁢j
         in the co-occurrence matrix
         \mat⁢A
         is set to the number of sentences in which the
         i
         -th and
         j
         -th features co-occur.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Typically, the number of unique bigrams is much larger than that of unigrams.
Moreover, co-occurrences of bigrams are rare compared to co-occurrences of unigrams,
and co-occurrences involving a unigram and a bigram.
Consequently, in matrix
         \mat⁢A
         , we consider co-occurrences only between unigrams vs. unigrams,
and bigrams vs. unigrams. We consider each row in
         \mat⁢A
         as representing the distribution of a
feature (i.e. unigrams or bigrams) in a particular domain over the unigram features extracted from that domain
(represented by the columns of
         \mat⁢A
         ).
We apply Positive Pointwise Mutual Information (PPMI) to the co-occurrence
matrix
         \mat⁢A
         . This is a variation of the Pointwise Mutual Information (PMI)
         []
         ,
in which all PMI values that are less than zero are replaced with zero
         []
         .
Let
         \mat⁢F
         be the matrix that results when PPMI is applied to
         \mat⁢A
         .
Matrix
         \mat⁢F
         has the same number of rows,
         nr
         , and columns,
         nc
         ,
as the raw co-occurrence matrix
         \mat⁢A
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Note that in addition to the above-mentioned representation, there are many other ways to
represent the distribution of a word in a particular domain
         []
         .
For example, one can limit the definition of co-occurrence to words that are linked by some dependency relation
         []
         ,
or extend the window of co-occurrence to the entire document
         []
         .
Since the method we propose in Section
         3.2
         to predict the distribution of a word across domains
does not depend on the particular feature representation method, any of these alternative methods could be used.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         To reduce the dimensionality of the feature space, and create dense representations for words,
we perform SVD on
         \mat⁢F
         . We use the left singular vectors corresponding to the
         k
         largest
singular values to compute a rank
         k
         approximation
         \mat⁢F^
         , of
         \mat⁢F
         .
We perform truncated SVD using SVDLIBC
         .
Each row in
         \mat⁢F^
         is considered as representing a word in a
lower
         k(≪nc)
         dimensional feature space corresponding to a particular domain.
Distribution prediction in this lower dimensional feature space is preferrable
to prediction over the original feature space because there are reductions in overfitting, feature sparseness, and the learning time.
We created two matrices,
         \mat⁢F^\cS
         and
         \mat⁢F^\cT
         from the source and target domains, respectively, using the above mentioned procedure.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Cross-Domain Feature Vector Prediction
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We propose a method to learn a model that can predict the distribution
         w→\cT
         of a word
         w
         in the target domain
         \cT
         , given its distribution
         w→\cS
         in the source domain
         \cS
         .
We denote the set of features that occur in both domains by
         \cW={w(1),…,w(n)}
         .
In the literature, such features are often referred to as
         pivots
         ,
and they have been shown to be useful for DA, allowing the
weights learnt to be transferred from one domain to another.
Various criteria have been proposed for selecting a small set of pivots for
DA, such as the mutual information of a word with the two domains
         []
         .
However, we do not impose any further restrictions on the set of pivots
         \cW
         other than
that they occur in both domains.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         For each word
         w(i)∈\cW
         , we denote the corresponding rows in
         \mat⁢F^\cS
         and
         \mat⁢F^\cT
         by column vectors
         w→\cS(i)
         and
         w→\cT(i)
         .
Note that the dimensionality of
         w→\cS(i)
         and
         w→\cT(i)
         need not be equal,
and we may select different numbers of singular vectors to approximate
         \mat⁢F^\cS
         and
         \mat⁢F^\cT
         .
We model distribution prediction as a multivariate regression
problem where, given a set
         {(w→\cS(i),w→\cT(i))}i=1n
         consisting of pairs
of feature vectors selected from each domain for the pivots in
         \cW
         , we learn a mapping
from the inputs (
         w→\cS(i)
         ) to the outputs (
         w→\cT(i)
         ).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         We use Partial Least Squares Regression (PLSR)
         []
         to learn a regression model
using pairs of vectors. PLSR has been applied in Chemometrics
         []
         , producing
stable prediction models even when the number of samples is considerably smaller than the
dimensionality of the feature space. In particular, PLSR fits a smaller number of latent variables (
         10-100
         in practice)
such that the correlation between the feature vectors for pivots in the two domains
are maximised in this latent space.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Let
         \mat⁢X
         and
         \mat⁢Y
         denote matrices formed by arranging respectively the vectors
         w→\cS(i)
         s and
         w→\cT(i)
         in rows. PLSR decomposes
         \mat⁢X
         and
         \mat⁢Y
         into a series of products
between rank
         1
         matrices as follows:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S7.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           \mat⁢X≈∑l=1Lλ→l⁢p→l⁢\T=𝚲⁢\mat⁢P⁢\T
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (1)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           \mat⁢Y≈∑l=1Lγ→ł⁢q→l⁢\T=𝚪⁢\mat⁢Q⁢\T.
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (2)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Here,
         λ→l
         ,
         γ→l
         ,
         p→l
         , and
         q→l
         are column
vectors, and the summation is taken over the rank
         1
         matrices that result from the outer product of
those vectors. The matrices,
         𝚲
         ,
         𝚪
         ,
         \mat⁢P
         , and
         \mat⁢Q
         are constructed respectively by arranging
         λ→l
         ,
         γ→l
         ,
         p→l
         , and
         q→l
         vectors as columns.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         [t]
         Learning a prediction model.
         [1]
\mat⁢X, \mat⁢Y, L.
Prediction matrix \mat⁢M.
Randomly select γ→l from columns in \mat⁢Yl. 
v→l=\mat⁢Xl⁢\T⁢γ→l/\norm⁢\mat⁢Xl⁢\T⁢γ→l
λ→l=\mat⁢Xl⁢v→l
q→l=\mat⁢Yl⁢\T⁢λ→l/\norm⁢\mat⁢Yl⁢\T⁢λ→l
γ→l=\mat⁢Yl⁢q→l
If γ→l is unchanged go to Line 3.2; otherwise go to Line 3.2
cl=λ→l⁢\T⁢γ→l/\norm⁢λ→l⁢\T⁢γ→l
p→l=\mat⁢Xl⁢\T⁢λ→l/λ→l⁢\T⁢λ→l
\mat⁢Xl+1=\mat⁢Xl-λ→l⁢p→l⁢\T and \mat⁢Yl+1=\mat⁢Yl-cl⁢λ→l⁢q→l⁢\T.
Stop if l=L; otherwise l=l+1 and return to Line 3.2.
Let \mat⁢C=diag⁢(c1,…,cL), and \mat⁢V=[v→1⁢…⁢v→L]
\mat⁢M=\mat⁢V⁢(\mat⁢P⁢\T⁢\mat⁢V)⁢\inv⁢\mat⁢C⁢\mat⁢Q⁢\T
\mat⁢M
         Our method for learning a distribution prediction model is shown in Algorithm
         3.2
         .
It is based on the two block NIPALS routine
         []
         and
iteratively discovers
         L
         pairs of vectors (
         λ→l,γ→l)
         such that the covariances,
         Cov⁢(λ→l,γ→l)
         ,
are maximised under the constraint
         \norm⁢p→l=\norm⁢q→l=1
         .
Finally, the prediction matrix,
         \mat⁢M
         is computed using
         λ→l,γ→l,p→l,q→l
         .
The predicted distribution
         w→^\cT
         of a word
         w
         in
         \cT
         is given by
        </p>
        w→^\cT=\mat⁢M⁢w→\cS.

(3)
        <p class="ltx_p">
         Our distribution prediction learning method is unsupervised in the sense that
it does not require manually labeled data for a particular task from any of the domains.
This is an important point, and means that the distribution prediction method is
independent of the task to which it may subsequently be applied.
As we go on to show in Section
         6
         , this enables us to use the same
distribution prediction method for both POS tagging and sentiment classification.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Domain Adaptation
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The main reason that a model trained only on the source domain labeled data performs poorly in the target domain
is the
        feature mismatch
        – few features in target domain test instances appear
in source domain training instances. To overcome this problem, we use the proposed
distribution prediction method to find those related features in the source domain that
correspond to the features appearing in the target domain test instances.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We consider two DA tasks: (a) cross-domain POS tagging (Section
        4.1
        ), and (b) cross-domain sentiment classification (Section
        4.2
        ).
Note that our proposed distribution prediction method can be applied to numerous other NLP tasks that involve sequence labelling and document classification.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Cross-Domain POS Tagging
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We represent each word using a set of features such as capitalisation (whether the first letter of
the word is capitalised), numeric (whether the word contains digits), prefixes up to four letters,
and suffixes up to four letters
         []
         .
Next, for each word
         w
         in a source domain labeled (i.e. manually POS tagged) sentence,
we select its neighbours
         u(i)
         in the source domain as additional features.
Specifically, we measure the similarity,
         sim⁢(u→\cS(i),w→\cS)
         , between
the source domain distributions of
         u(i)
         and
         w
         , and select the top
         r
         similar neighbours
         u(i)
         for each word
         w
         as additional features for
         w
         . We refer to such features as
         distributional features
         in this work.
The value of a neighbour
         u(i)
         selected as a distributional feature is set to
its similarity score
         sim⁢(u→\cS(i),w→\cS)
         .
Next, we train a CRF model using all features (i.e. capitalisation, numeric, prefixes, suffixes, and
distributional features) on source domain labeled sentences.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         We train a PLSR model,
         \mat⁢M
         , that predicts the target domain distribution
         \mat⁢M⁢u→\cS(i)
         of a word
         u(i)
         in the source domain labeled sentences, given its distribution,
         u→\cS(i)
         .
At test time, for each word
         w
         that appears in a target domain test sentence, we measure the similarity,
         sim⁢(\mat⁢M⁢u→\cS(i),w→\cT)
         , and select the most similar
         r
         words
         u(i)
         in the source domain labeled sentences as the
distributional features for
         w
         , with their values set to
         sim⁢(\mat⁢M⁢u→\cS(i),w→\cT)
         .
Finally, the trained CRF model is applied to a target domain test sentence.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         Note that distributional features are always selected from the source domain during both train and test times, thereby
increasing the number of overlapping features between the trained model and test sentences.
To make the inference tractable and efficient, we use a first-order Markov factorisation, in which we consider all pairwise combinations
between the features for the current word and its immediate predecessor.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Cross-Domain Sentiment Classification
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Unlike in POS tagging, where we must individually tag each word in a target domain test sentence, in sentiment classification
we must classify the sentiment for the entire review. We modify the DA method presented in
Section
         4.1
         to satisfy this requirement as follows.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Let us assume that we are given a set
         {(x→\cS(i),y(i))}i=1n
         of
         n
         labeled reviews
         x→\cS(i)
         for the source domain
         \cS
         . For simplicity, let us consider binary sentiment classification where each review
         x→(i)
         is
labeled either as positive (i.e.
         y(i)=1
         ) or negative (i.e.
         y(i)=-1
         ).
Our cross-domain binary sentiment classification method can be easily extended to the multi-class setting as well.
First, we lemmatise each word in a source domain labeled review
         x→\cS(i)
         ,
and extract both unigrams and bigrams as features to represent
         x→\cS(i)
         by a binary-valued feature vector.
Next, we train a binary classification model,
         θ→
         , using those feature vectors.
Any binary classification algorithm can be used to learn
         θ→
         .
In our experiments, we used L2 regularised logistic regression.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         Next, we train a PLSR model,
         \mat⁢M
         , as described in Section
         3.2
         using unlabeled reviews in the
source and target domains. At test time, we represent a test target review
         H
         using a binary-valued feature vector
         h→
         of unigrams and bigrams of lemmas of the words in
         H
         , as we did for source domain labeled train reviews.
Next, for each feature
         w(j)
         extracted from
         H
         , we measure the similarity,
         sim⁢(\mat⁢M⁢u→\cS(i),w→\cT(j))
         ,
between the target domain distribution of
         w(j)
         ,
and each feature (unigram or bigram)
         u(i)
         in the source domain labeled reviews.
We score each source domain feature
         u(i)
         for its relatedness to
         H
         using
the formula:
        </p>
        score⁢(u(i),𝖧)=1|𝖧|⁢∑j=1|𝖧|sim⁢(\mat⁢M⁢u→\cS(i),w→\cT(j))

(4)
        <p class="ltx_p">
         where
         |𝖧|
         denotes the total number of features extracted from the test review
         H
         .
We select the top scoring
         r
         features
         u(i)
         as distributional features for
         H
         , and append those to
         h→
         .
The corresponding values of those distributional features are set to the scores given by Equation
         4
         .
Finally, we classify
         h→
         using the trained binary classifier
         θ→
         .
Note that given a test review, we find the distributional features that are similar to
         all
         the words in the test review from the source domain. In particular, we
         do not
         find distributional features
independently for each word in the test review. This enables us to find distributional features that are
consistent with all the features in a test review.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Model Choices
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         For both POS tagging and sentiment classification, we experimented with several alternative approaches for feature weighting,
representation, and similarity measures using development data, which we randomly selected from the
training instances from the datasets described in Section
         5
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         For feature weighting for sentiment classification, we considered using the number of occurrences of a feature in a review
and tf-idf weighting
         []
         . For representation, we considered distributional features
         u(i)
         in descending
order of their scores given by Equation
         4
         , and then taking the inverse-rank as the values for
the distributional features
         []
         .
However, none of these alternatives resulted in performance gains.
With respect to similarity measures, we experimented with cosine similarity and
the similarity measure proposed by
         ; cosine similarity performed
consistently well over all the experimental settings.
The feature representation was held fixed during these similarity measure comparisons.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         For POS tagging, we measured the effect of varying
         r
         , the number of distributional features,
using a development dataset. We observed that setting
         r
         larger than
         10
         did not result in significant
improvements in tagging accuracy, but only increased the train time due to the larger feature space.
Consequently, we set
         r=10
         in POS tagging.
For sentiment analysis, we used all features in the source domain
labeled reviews as distributional features, weighted by their scores given by Equation
         4
         ,
taking the inverse-rank.
In both tasks, we parallelised similarity computations using BLAS
         level-3 routines to speed up the computations.
The source code of our implementation is publicly available
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
       Datasets
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        To evaluate DA for POS tagging,
following
        , we use sections
        2-21
        from Wall Street Journal (WSJ) as the source domain
labeled data. An additional
        100,000
        WSJ sentences from the 1988 release of the WSJ corpus are used as
the source domain unlabeled data.
Following
        , we use the POS labeled sentences in the SACNL
dataset
        []
        for the five target domains: QA forums, Emails, Newsgroups, Reviews, and Blogs.
Each target domain contains around
        1000
        POS labeled test sentences and around
        100,000
        unlabeled sentences.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        To evaluate DA for sentiment classification,
we use the Amazon product reviews collected by
        for four different product categories:
books (
        B
        ), DVDs (
        D
        ), electronic items (
        E
        ), and kitchen appliances (
        K
        ).
There are
        1000
        positive and
        1000
        negative sentiment labeled reviews for each domain.
Moreover, each domain has on average
        17,547
        unlabeled reviews.
We use the standard split of
        800
        positive and
        800
        negative labeled reviews from each domain
as training data, and the remainder for testing.
       </p>
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
        For each domain
        \cD
        in the SANCL (POS tagging) and Amazon review (sentiment classification) datasets,
we create a PPMI weighted co-occurrence matrix
        \mat⁢F\cD
        .
On average,
        \mat⁢F\cD
        created for a target domain in the SANCL dataset contains
        104,598
        rows and
        65,528
        columns,
whereas those numbers in the Amazon dataset are
        27,397
        and
        35,200
        respectively.
In cross-domain sentiment classification, we measure the binary sentiment classification accuracy for the target domain
test reviews for each pair of domains (
        12
        pairs in total for
        4
        domains).
On average, we have
        40,176
        pivots for a pair of domains in the Amazon dataset.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        In cross-domain POS tagging, WSJ is always the source domain, whereas the five domains in SANCL dataset
are considered as the target domains. For this setting we have
        9822
        pivots on average.
The number of singular vectors
        k
        selected in SVD, and the number of PLSR dimensions
        L
        are set respectively to
        1000
        and
        50
        for the remainder of the experiments described in the paper.
Later we study the effect of those two parameters on the performance of the proposed method.
The L-BFGS
        []
        method is used to train the CRF and logistic regression models.
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        POS Tagging Results
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         Table
         2
         shows the token-level POS tagging accuracy for
         unseen
         words (i.e. words that appear in the target
domain test sentences but not in the source domain labeled train sentences). By limiting the evaluation to unseen words
instead of all words, we can evaluate the gain in POS tagging accuracy solely due to DA.
The
         NA
         (no-adapt) baseline simulates the effect of not performing any
DA. Specifically, in POS tagging, a CRF trained on source domain labeled sentences is applied
to target domain test sentences, whereas in sentiment classification, a logistic regression classifier
trained using source domain labeled reviews is applied to the target domain test reviews.
The
         \cS𝐩𝐫𝐞𝐝
         baseline directly uses the source domain
distributions for the words instead of projecting them to the target domain. This is equivalent to setting
the prediction matrix
         \mat⁢M
         to the unit matrix. The
         \cT𝐩𝐫𝐞𝐝
         baseline uses the
target domain distribution
         w→\cT
         for a word
         w
         instead of
         \mat⁢M⁢w→\cS
         .
If
         w
         does not appear in the target domain, then
         w→\cT
         is set to the zero vector.
The
         \cSp⁢r⁢e⁢d
         and
         \cTp⁢r⁢e⁢d
         baselines simulate the two alternatives of using source
and target domain distributions instead of learning a PLSR model.
The DA method proposed in Section
         4.1
         is shown as the
         Proposed
         method.
         Filter
         denotes the training set filtering method proposed by
         for the DA of POS taggers.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         From Table
         2
         , we see that the
         Proposed
         method achieves the best performance in all five domains,
followed by the
         \cTp⁢r⁢e⁢d
         baseline.
Recall that the
         \cTp⁢r⁢e⁢d
         baseline cannot find source domain words that do not appear in the target domain
as distributional features for the words in the target domain test reviews. Therefore, when the overlap between
the vocabularies used in the source and the target domains is small,
         \cTp⁢r⁢e⁢d
         cannot reduce the mismatch between the feature spaces.
Poor performance of the
         \cSp⁢r⁢e⁢d
         baseline shows that the distributions of a word in the source and target domains
are different to the extent that the distributional features found using source domain distributions are inadequate.
The two baselines
         \cSp⁢r⁢e⁢d
         and
         \cTp⁢r⁢e⁢d
         collectively motivate our
proposal to learn a distribution prediction model from the source domain to the target.
The improvements of
         Proposed
         over the previously proposed
         Filter
         are statistically significant in all domains except the Emails domain (denoted by
         †
         in Table
         2
         according to the Binomial exact test at
         95⁢%
         confidence).
However, the differences between the
         \cTp⁢r⁢e⁢d
         and
         Proposed
         methods are not statistically significant.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        Sentiment Classification Results
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         In Figure
         1
         , we compare the
         Proposed
         cross-domain sentiment classification method (Section
         4.2
         )
against several baselines and the current state-of-the-art methods.
The baselines
         NA
         ,
         \cS𝐩𝐫𝐞𝐝
         ,
and
         \cT𝐩𝐫𝐞𝐝
         are defined similarly as in Section
         6.1
         .
         SST
         is the Sentiment Sensitive Thesaurus proposed by
         .
         SST
         creates a single distribution for a word using both source and target domain reviews,
instead of two separate distributions as done by the
         Proposed
         method.
         SCL
         denotes the Structural Correspondence Learning method proposed by
         .
         SFA
         denotes the Spectral Feature Alignment
method proposed by
         .
         SFA
         and
         SCL
         represent the current state-of-the-art methods for
cross-domain sentiment classification.
All methods are evaluated under the same settings, including train/test split, feature spaces, pivots, and classification algorithms
so that any differences in performance can be directly attributable to their domain adaptability.
For each domain, the accuracy obtained by a classifier trained using labeled data from that domain
is indicated by a solid horizontal line in each sub-figure. This upper baseline represents the classification
accuracy we could hope to obtain if we were to have labeled data for the target domain.
Clopper-Pearson
         95⁢%
         binomial confidence intervals are superimposed on each vertical bar.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         From Figure
         1
         we see that the
         Proposed
         method reports the best results
in
         8
         out of the
         12
         domain pairs, whereas
         SCL
         ,
         SFA
         , and
         \cS𝐩𝐫𝐞𝐝
         report the best results in other cases.
Except for the
         D-E
         setting in which
         Proposed
         method significantly outperforms
both
         SFA
         and
         SCL
         , the performance of the
         Proposed
         method
is not statistically significantly different to that of
         SFA
         or
         SCL
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         The selection of pivots is vital to the performance of
         SFA
         .
However, unlike
         SFA
         , which requires us to carefully select a small subset of pivots (ca. less than
         500
         )
using some heuristic approach, our
         Proposed
         method does not require any pivot selection.
Moreover,
         SFA
         projects source domain reviews to a lower-dimensional latent space,
in which a binary sentiment classifier is subsequently trained. At test time
         SFA
         projects a target review
into this lower-dimensional latent space and applies the trained classifier.
In contrast, our
         Proposed
         method predicts the distribution of a word in the target domain,
given its distribution in the source domain, thereby explicitly
         translating
         the source domain reviews
to the target. This property enables us to apply the proposed distribution prediction method to tasks other than sentiment
analysis such as POS tagging where we must identify distributional features for individual words.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p4">
        <p class="ltx_p">
         Unlike our distribution prediction method, which is unsupervised,
         SST
         requires labeled data for the source domain to learn a feature mapping
between a source and a target domain in the form of a thesaurus.
However, from Figure
         1
         we see that in
         10
         out of the
         12
         domain-pairs the
         Proposed
         method returns higher accuracies than
         SST
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p5">
        <p class="ltx_p">
         To evaluate the overall effect of the number of singular vectors
         k
         used in the SVD step, and the number of
PLSR components
         L
         used in Algorithm
         3.2
         , we conduct two experiments.
To evaluate the effect of the PLSR dimensions, we fixed
         k=1000
         and measured the cross-domain
sentiment classification accuracy over a range of
         L
         values.
As shown in Figure
         2
         , accuracy remains stable across a wide range of PLSR dimensions.
Because the time complexity of Algorithm
         3.2
         increases linearly with
         L
         , it is desirable that
we select smaller
         L
         values in practice.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p6">
        <p class="ltx_p">
         To evaluate the effect of the SVD dimensions, we fixed
         L=100
         and measured the cross-domain sentiment
classification accuracy for different
         k
         values as shown in Figure
         3
         .
We see an overall decrease in classification accuracy when
         k
         is increased.
Because the dimensionality of the source and target domain feature spaces is equal to
         k
         ,
the complexity of the least square regression problem increases with
         k
         .
Therefore, larger
         k
         values result in overfitting to the train data and classification accuracy is reduced
on the target test data.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p7">
        <p class="ltx_p">
         As an example of the distribution prediction method,
in Table
         3
         we show the top
         3
         similar distributional features
         u
         in the
         books
         (source) domain,
predicted for the
         electronics
         (target) domain word
         w=𝑙𝑖𝑔ℎ𝑡𝑤𝑒𝑖𝑔ℎ𝑡
         , by
different similarity measures. Bigrams are indicted by a
         +
         sign and the similarity scores
of the distributional features are shown within brackets.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p8">
        <p class="ltx_p">
         Using the source domain distributions for both
         u
         and
         w
         (i.e.
         sim⁢(u\cS,w\cS)
         ) produces
distributional features that are specific to the books domain, or to the dominant adjectival sense of
         having no importance or influence
         .
On the other hand, using target domain distributions for
         u
         and
         w
         (i.e.
         sim⁢(u\cT,w\cT)
         )
returns distributional features
of the dominant nominal sense of
         lower in weight
         frequently associated with electronic devices.
Simply using source domain distributions
         u\cS
         (i.e.
         sim⁢(u\cS,w\cT)
         )
returns totally unrelated distributional features.
This shows that word distributions in source and target domains are
very different and some adaptation is required prior to computing distributional features.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p9">
        <p class="ltx_p">
         Interestingly, we see that by using the distributions predicted by the proposed method (i.e.
         sim⁢(\mat⁢M⁢u\cS,w\cT)
         )
we overcome this problem and find relevant distributional features from the source domain.
Although for illustrative purposes we used the word
         lightweight
         , which occurs in both the source and the target domains, our proposed method does not require the source domain distribution
         w\cS
         for a word
         w
         in a target domain document.
Therefore, it can find distributional features even for words occurring only in the target domain,
thereby reducing the feature mismatch between the two domains.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
