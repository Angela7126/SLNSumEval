<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   How much do word embeddings encode about syntax?.
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
       Do continuous word embeddings encode any useful information for constituency
parsing?
We isolate
three ways in which word embeddings might augment a
state-of-the-art statistical parser: by connecting out-of-vocabulary
words to known ones, by encouraging common behavior among related
in-vocabulary words, and by directly providing
features for the lexicon.
We test each of these hypotheses with a targeted change to a state-of-the-art baseline.
Despite small gains on extremely small supervised
training sets, we find that extra information from embeddings appears to make
little or no difference to a parser with adequate training data. Our results
support an overall hypothesis that word embeddings import syntactic
information that is ultimately redundant with distinctions learned from
treebanks in other ways.
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
        This paper investigates a variety of ways in which word embeddings might augment
a constituency parser with a discrete state space. Word embeddings—representations of
lexical items as points in a real vector space—have a long history in natural
language processing, going back at least as far as work on latent semantic
analysis (LSA) for information retrieval
        [4]
        . While word
embeddings can be constructed directly from surface distributional statistics,
as in LSA, more sophisticated tools for unsupervised extraction of word
representations have recently gained popularity
        [3, 10]
        . Semi-supervised and
unsupervised models for a variety of core NLP tasks, including named-entity
recognition
        [5]
        , part-of-speech tagging
        [13]
        , and
chunking
        [15]
        have been shown to benefit
from the inclusion of word embeddings as features. In the other direction,
access to a syntactic parse has been shown to be useful for constructing word
embeddings for phrases compositionally
        [7, 1]
        .
        Dependency
        parsers have seen gains from distributional
statistics in the form of discrete word clusters
        [9]
        , and
recent work
        [2]
        suggests that similar gains can be
derived from embeddings like the ones used in this paper.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        It has been less clear how (and indeed whether) word embeddings in and of
themselves are useful for
        constituency
        parsing.
There certainly exist competitive parsers that internally represent lexical
items as real-valued vectors, such as the neural network-based parser of
        Henderson (2004)
        , and even parsers which use pre-trained word
embeddings to represent the lexicon, such as
        Socher et al. (2013)
        . In these
parsers, however,
use of word vectors is a structural choice, rather than an added feature,
and it is difficult to disentangle whether
vector-space lexicons are
actually more powerful than their discrete analogs—perhaps the performance of
neural network parsers comes entirely from the model’s extra-lexical syntactic
structure.
In order to isolate the contribution from word embeddings, it is useful to
demonstrate improvement over a parser that already
achieves state-of-the-art performance
        without
        vector representations.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The fundamental question we want to explore is whether embeddings provide any
information beyond what a conventional parser is able to induce from labeled
parse trees. It could be that the distinctions between lexical items that
embeddings capture are already modeled by parsers in other ways and therefore
provide no further benefit. In this paper, we investigate this question
empirically,
by isolating
three potential mechanisms for improvement
from pre-trained word embeddings.
Our result is mostly negative. With extremely limited training data,
parser extensions using word embeddings give modest improvements in accuracy
(relative error reduction on the order of 1.5%). However, with reasonably-sized
training corpora, performance does not improve even when a wide variety of
embedding methods, parser modifications, and parameter settings are considered.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The fact that word embedding features result in nontrivial gains for
discriminative dependency parsing
        [2]
        , but
do not appear to be effective for constituency parsing,
points to an interesting structural difference
between the two tasks. We hypothesize that dependency parsers benefit from the
introduction of features (like clusters and embeddings) that provide syntactic
abstractions; but that constituency parsers already have access to
such abstractions in the form of supervised preterminal tags.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Three possible benefits of word embeddings
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We are interested in the question of whether a state-of-the-art
discrete-variable constituency parser can be improved with word embeddings,
and, more precisely, what aspect (or aspects) of the parser can be altered to make effective use of embeddings.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        It seems clear that word embeddings exhibit some syntactic structure. Consider
Figure
        1
        , which shows embeddings for a variety of English
determiners, projected onto their first two principal components. We can see
that the quantifiers
        each
        and
        every
        cluster together, as do
        few
        and
        most
        . These are precisely the kinds of distinctions between
determiners that state-splitting in the Berkeley parser has shown to be useful
        [12]
        , and existing work
        [11]
        has
observed that such regular embedding structure extends to many other parts of speech. But we
don’t know how prevalent or important such “syntactic axes” are in practice.
Thus we have two questions: Are such groupings (learned on large data sets but
from less syntactically rich models) better than the ones the parser finds on
its own? How much data is needed to learn them without word embeddings?
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        We consider three general hypotheses about how embeddings might interact with
a parser:
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Vocabulary expansion hypothesis
           : Word embeddings are useful for
handling
           out-of-vocabulary
           words, because they automatically ensure
that unknown words are treated the same way as known words with similar
representations. Example: the infrequently-occurring treebank tag UH
dominates greetings (among other interjections). Upon encountering the
unknown word
           hey
           , the parser assigns a low posterior probability of
having been generated from UH. But its distributional representation is very
close to the known word
           hello
           ,
and a model capable of mapping
           hey
           to its neighbor should be able to
assign the right tag.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Statistic sharing hypothesis
           : Word embeddings are useful for
handling
           in-vocabulary
           words, by making it possible to pool
statistics for related words. Example: individual first names are also rare
in the treebank, but tend to cluster together in distributional
representations. A parser which exploited this effect could use this to
acquire a robust model of name behavior by sharing statistics from all first
names together, preventing low counts from producing noisy models of names.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Embedding structure hypothesis
           : The structure of the space used
for the embeddings directly encodes syntactic information in its coordinate
axes. Example: with the exception of
           a
           , the vertical axis in
Figure
           1
           seems to group words by definiteness. We would expect
a feature corresponding to a word’s position along this axis to be a useful
feature in a feature-based lexicon.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Note that these hypotheses are not all mutually exclusive, and two or all of
them might provide independent gains. Our first task is thus to design a set of
orthogonal experiments which make it possible to test each of the three
hypotheses in isolation. It is also possible that other mechanisms are at play
that are not covered by these three hypotheses, but we consider these three to
be likely central effects.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Parser extensions
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        For the experiments in this paper, we will use the Berkeley parser
        [12]
        and the related Maryland parser
        [8]
        . The Berkeley parser induces a latent,
state-split PCFG in which each symbol
        V
        of the (observed) X-bar grammar is
refined into a set of more specific symbols
        {V1,V2,…}
        which
capture more detailed grammatical behavior. This allows the parser to
distinguish between words which share the same tag but exhibit very different
syntactic behavior—for example, between articles and demonstrative pronouns.
The Maryland parser builds on the state-splitting parser, replacing its basic
word emission model with a feature-rich, log-linear representation of the
lexicon.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The choice of this parser family has two motivations. First, these parsers are
among the best in the literature, with a test performance of 90.7 F
        1
        for the
baseline Berkeley parser on the Wall Street Journal corpus (compared to 90.4 for
        Socher et al. (2013)
        and 90.1 for
        Henderson (2004)
        ). Second,
and more importantly, the fact that they use no continuous state representations
internally makes it easy to design experiments that isolate the contributions of
word vectors, without worrying about effects from real-valued operators higher
up in the model.
We consider the following extensions:
       </p>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Vocabulary expansion
        →
        OOV model
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         To evaluate the vocabulary expansion
hypothesis, we introduce a simple but targeted out-of-vocabulary (OOV) model in
which every unknown word is simply replaced by its nearest neighbor in the
training set. For OOV words which are not in the dictionary of embeddings, we
back off to the unknown word model for the underlying parser.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Statistic sharing
        →
        Lexicon pooling model
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         To evaluate the statistic sharing hypothesis, we
propose a novel smoothing technique. The Berkeley lexicon stores, for each
latent (tag, word) pair, the probability
         p(w|t)
         directly in a lookup table. If
we want to encourage similarly-embedded words to exhibit similar behavior in the
generative model, we need to ensure that the are preferentially mapped onto the
same latent preterminal tag. In order to do this, we replace this direct lookup
with a smoothed, kernelized lexicon, where:
        </p>
        p(w|t)=1Z∑w′αt,w′e-β⁢||ϕ⁢(w)-ϕ⁢(w′)||2

(1)
        <p class="ltx_p">
         with
         Z
         a normalizing constant to ensure that
         p(⋅|t)
         sums to one over
the entire vocabulary.
         ϕ⁢(w)
         is the vector representation of the word
         w
         ,
         αt,w
         are per-basis weights, and
         β
         is an inverse radius parameter
which determines the strength of the smoothing.
Each
         αt,w
         is learned
in the same way as its corresponding probability in the original parser
model—during each M step of the training procedure,
         αw,t
         is set to
the expected number of times the word
         w
         appears under the refined tag
         t
         .
Intuitively, as
         β
         grows small
groups of related words will be assigned increasingly similar probabilities of
being generated from the same tag (in the limit where
         β=0
         ,
Equation
         1
         is a uniform distribution over the entire
vocabulary). As
         β
         grows large words become more independent (and in
the limit where
         β=∞
         , each summand in Equation
         1
         is zero except where
         w′=w
         , and we recover the original direct-lookup model).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         There are computational concerns associated with this approach: the original
scoring procedure for a (word, tag) pair was a single (constant-time) lookup;
here it might take time linear in the size of the vocabulary. This causes
parsing to become unacceptably slow, so an approximation is necessary.
Luckily, the exponential decay of the kernel ensures that each word shares
most of its weight with a small number of close neighbors, and almost none with
words farther away. To exploit this, we pre-compute the
         k
         -nearest-neighbor
graph of points in the embedding space, and take the sum in
Equation
         1
         only over this set of nearest neighbors.
Empirically, taking
         k=20
         gives adequate performance, and increasing it does
not seem to alter the behavior of the parser.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P2.p3">
        <p class="ltx_p">
         As in the OOV model, we also need to worry about how to handle
words for which we have no vector representation. In these cases, we simply
treat the words as if their vectors were so far away from everything else they
had no influence, and report their weights as
         p(w|t)=αw
         . This
ensures that our model continues to include the original Berkeley parser model
as a limiting case.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        Embedding structure
        →
        embedding features
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         To evaluate the embedding structure hypothesis, we take the Maryland featured
parser, and replace the set of lexical template features used by that parser
with a set of indicator features on a discretized version of the embedding. For
each dimension
         i
         , we create an indicator feature corresponding to the
linearly-bucketed value of the feature at that index. In order to focus
specifically on the effect of word embeddings, we remove the morphological
features from the parser, but retain indicators on the identity of each lexical
item.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P4">
       <h3 class="ltx_title ltx_title_paragraph">
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         The extensions we propose are certainly not the only way to target the
hypotheses described above, but they have the advantage of being minimal and
straightforwardly interpretable, and each can be reasonably expected to improve
parser performance if its corresponding hypothesis is true.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experimental setup
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We use the Maryland implementation of the Berkeley parser as our baseline for
the kernel-smoothed lexicon, and the Maryland featured parser as our baseline
for the embedding-featured lexicon.
        For all experiments, we use 50-dimensional word embeddings. Embeddings labeled
        c&amp;w
        are from
        Collobert et al. (2011)
        ; embeddings labeled
        cbow
        are from
        Mikolov et al. (2013a)
        , trained with a context window of size 2.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Experiments are conducted on the Wall Street Journal portion of the
English Penn Treebank. We prepare three training sets: the complete training set of
39,832 sentences from the treebank (sections 2 through 21), a smaller training
set, consisting of the first 3000 sentences, and an even smaller set of the
first 300.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Per-corpus-size settings of the parameter
        β
        are set by searching over
several possible settings on the development set. For each training
corpus size we also
choose a different setting of the number of
splitting iterations over which the Berkeley parser is run; for 300 sentences
this is two splits, and for 3000 four splits. This is necessary to avoid
overfitting on smaller training sets. Consistent with the existing literature,
we stop at six splits when using the full training corpus.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Various model-specific experiments are shown in Table
        1
        .
We begin by investigating the OOV model. As can be seen, this model alone
achieves small gains over the baseline for a 300-word training corpus, but
these gains become statistically insignificant with more training data. This
behavior is almost completely insensitive to the choice of embedding.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Next we consider the lexicon pooling model. We began by searching over
exponentially-spaced values of
        β
        to determine an optimal setting for each
training set size; as expected, for small
settings of
        β
        (corresponding to aggressive smoothing) performance
decreased; as we increased the parameter, performance increased slightly before
tapering off to baseline parser performance. The first block in
Table
        1
        shows the best settings of
        β
        for
each corpus size; as can be seen, this also gives a small improvement on the
300-sentence training corpus, but no discernible once the system has access to a
few thousand labeled sentences.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Last we consider a model with a featured lexicon, as described in
        Huang and Harper (2011)
        . A baseline featured model (“ident”)
contains only indicator features on word identity (and performs considerably
worse than its generative counterpart on small data sets). As described above,
the full featured model adds indicator features on the bucketed value of each
dimension of the word embedding. Here, the trend observed in
the other two models is even more prominent—embedding features lead to
improvements over the featured baseline, but in no case outperform the standard
baseline with a generative lexicon.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        We take the best-performing combination of all of these models (based on
development experiments, a combination of the lexical pooling model with
        β=0.3
        , and OOV, both using
        c&amp;w
        word embeddings), and evaluate this on the WSJ
test set (Table
        2
        ). We observe very small (but
statistically significant) gains with 300 and 3000 train sentences, but a
decrease in performance on the full corpus.
       </p>
      </div>
      <div class="ltx_para" id="S5.p5">
       <p class="ltx_p">
        To investigate the possibility that improvements from embeddings are
exceptionally difficult to achieve on the Wall Street Journal corpus, or on
English generally, we perform (1) a domain adaptation experiment, in which we use
the OOV and lexicon pooling models to train on WSJ and test on the first 4000
sentences of the Brown corpus (the “WSJ
        →
        Brown” column in
Table
        3
        ), and (2) a multilingual experiment, in which we train and
test on the French treebank (the “French” column). Apparent gains from
the OOV and lexicon pooling models remain so small as to be statistically
indistinguishable.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
