<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Don’t count, predict! A systematic comparison of context-counting vs. context-predicting semantic vectors.
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
       Context-predicting models (more commonly known as embeddings or
neural language models) are the new kids on the distributional
semantics block. Despite the buzz surrounding these models, the
literature is still lacking a systematic comparison of the
predictive models with classic, count-vector-based distributional
semantic approaches. In this paper, we perform such an extensive
evaluation, on a wide range of lexical semantics tasks and across
many parameter settings. The results, to our own surprise, show that
the buzz is fully justified, as the context-predicting models obtain
a thorough and resounding victory against their count-based
counterparts.
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
        A long tradition in computational linguistics has shown that
contextual information provides a good approximation to word meaning,
since semantically similar words tend to have similar contextual
distributions
        [36]
        . In concrete,
        distributional semantic models
        (DSMs) use vectors that keep
track of the contexts (e.g., co-occurring words) in which target terms
appear in a large corpus as proxies for meaning representations, and
apply geometric techniques to these vectors to measure the similarity in meaning of the corresponding words
        [13, 16, 45]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        It has been clear for decades now that raw co-occurrence counts don’t
work that well, and DSMs achieve much higher performance when various
transformations are applied to the raw vectors, for example by
reweighting the counts for context informativeness and smoothing them
with dimensionality reduction techniques. This vector optimization
process is generally unsupervised, and based on independent
considerations (for example, context reweighting is often justified by
information-theoretic considerations, dimensionality reduction
optimizes the amount of preserved variance, etc.). Occasionally, some kind
of indirect supervision is used: Several parameter settings are tried,
and the best setting is chosen based on performance on a semantic task
that has been selected for tuning.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The last few years have seen the development of a new generation of
DSMs that frame the vector estimation problem directly as a supervised
task, where the weights in a word vector are set to maximize the
probability of the contexts in which the word is observed in the
corpus
        [6, 15, 14, 25, 32, 44]
        . The
traditional construction of context vectors is turned on its head:
Instead of first collecting context vectors and then reweighting these
vectors based on various criteria, the vector weights are directly set
to optimally predict the contexts in which the corresponding words
tend to appear. Since similar words occur in similar contexts, the
system naturally learns to assign similar vectors to similar words.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        This new way to train DSMs is attractive because it replaces the
essentially heuristic stacking of vector transforms in earlier models
with a single, well-defined supervised learning step. At the same
time, supervision comes at no manual annotation cost, given that the
context windows used for training can be automatically extracted from
an unannotated corpus (indeed, they are the very same data used to
build traditional DSMs). Moreover, at least some of the relevant
methods can efficiently scale up to process very large amounts of
input data.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We will refer to DSMs built in the traditional way as
        count
        models (since they initialize vectors with co-occurrence counts), and
to their training-based alternative as
        predict(ive)
        models.
        Now,
the most natural question to ask, of course, is which of the two
approaches is best in empirical terms. Surprisingly, despite the long
tradition of extensive evaluations of alternative count DSMs on
standard benchmarks
        [1, 5, 10, 11, 41, 37]
        ,
the existing literature contains very little in terms of direct
comparison of count vs. predictive DSMs. This is in part due to the
fact that context-predicting vectors were first developed as an
approach to language modeling and/or as a way to initialize feature
vectors in neural-network-based “deep learning” NLP architectures,
so their effectiveness as semantic representations was initially seen
as little more than an interesting side effect. Sociological reasons
might also be partly responsible for the lack of systematic
comparisons: Context-predictive models were developed within the
neural-network community, with little or no awareness of recent DSM
work in computational linguistics.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Whatever the reasons, we know of just three works reporting direct
comparisons, all limited in their scope.
        Huang et al. (2012)
        compare, in passing, one count model and several predict DSMs on the
standard WordSim353 benchmark (Table 3 of their paper). In this
experiment, the count model actually outperforms the best predictive
approach. Instead, in a word-similarity-in-context task (Table 5), the
best predict model outperforms the count model, albeit not by a large
margin.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Blacoe and Lapata (2012)
        compare count and predict representations
as input to composition functions. Count vectors make for better
inputs in a phrase similarity task, whereas the two representations
are comparable in a paraphrase classification experiment.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        Finally,
        Mikolov et al. (2013d)
        compare their predict models to
“Latent Semantic Analysis” (LSA) count vectors on syntactic and
semantic analogy tasks, finding that the predict models are highly
superior. However, they provide very little details about the LSA
count vectors they use.
       </p>
      </div>
      <div class="ltx_para" id="S1.p9">
       <p class="ltx_p">
        In this paper, we overcome the comparison scarcity problem by
providing a direct evaluation of count and predict DSMs across many
parameter settings and on a large variety of mostly standard lexical
semantics benchmarks. Our title already gave away what we discovered.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Distributional semantic models
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Both count and predict models are extracted from a corpus of about 2.8
billion tokens constructed by concatenating
ukWaC,
        the English
Wikipedia
        and the British
National Corpus.
        For both
model types, we consider the top 300K most frequent words in the
corpus both as target and context elements.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Count models
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         We prepared the count models using the DISSECT
toolkit.
         We extracted count vectors from symmetric context windows of two and
five words to either side of target. We considered two weighting
schemes: positive Pointwise Mutual Information and Local Mutual
Information (akin to the widely used Log-Likelihood Ratio scheme)
         [17]
         . We used both full and compressed vectors. The
latter were obtained by applying the Singular Value Decomposition
         [20]
         or Non-negative Matrix Factorization
         [29]
         ,
         Lin (2007)
         algorithm, with reduced sizes ranging from 200 to 500 in
steps of 100. In total, 36 count models were evaluated.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Count models have such a long and rich history that we can only
explore a small subset of the counting, weighting and compressing
methods proposed in the literature. However, it is worth pointing out
that the evaluated parameter subset encompasses settings (narrow
context window, positive PMI, SVD reduction) that have been found to
be most effective in the systematic explorations of the parameter
space conducted by Bullinaria and Levy
         [10, 11]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Predict models
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         We trained our predict models with the word2vec
toolkit.
         The
toolkit implements both the skip-gram and CBOW approaches of Mikolov
et al.
         [32, 34]
         . We
experimented only with the latter, which is also the more computationally-efficient
model of the two, following
         Mikolov et al. (2013b)
         which recommends CBOW as more suitable for larger datasets.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         The CBOW model learns to predict the word in the middle of a symmetric
window based on the sum of the vector representations of the words in
the window. We considered context windows of
         2
         and
         5
         words to
either side of the central element. We vary vector dimensionality
within the
         200
         to
         500
         range in steps of
         100
         . The word2vec
toolkit implements two efficient alternatives to the standard
computation of the output word probability distributions by a softmax
classifier. Hierarchical softmax is a computationally efficient way to
estimate the overall probability distribution using an output layer
that is proportional to
         log(unigram.perplexity(W))
         instead of
         W
         (for
         W
         the vocabulary size).
As an alternative, negative sampling estimates the probability of an
output word by learning to distinguish it from draws from a noise
distribution. The number of these draws (number of
         negative
samples
         ) is given by a parameter
         k
         . We test both hierarchical
softmax and negative sampling with
         k
         values of
         5
         and
         10
         . Very frequent words such as
         the
         or
         a
         are not very
informative as context features. The word2vec toolkit implements a
method to downsize their effect (and simultaneously improve speed
performance). More precisely, words in the training data are discarded
with a probability that is proportional to their frequency (capturing
the same intuition that motivates traditional count vector weighting
measures such as PMI). This is controlled by a parameter
         t
         and words
that occur with higher frequency than
         t
         are aggressively
subsampled. We train models without subsampling and with subsampling
at
         t=1⁢e-5
         (the toolkit page suggests
         1⁢e-3-1⁢e-5
         as a
useful range based on empirical observations).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         In total, we evaluate 48 predict models, a number comparable to that
of the count models we consider.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Out-of-the-box models
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         Baroni and Lenci (2010)
         make the vectors of their best-performing
         Distributional Memory
         (dm) model
available.
         This model,
based on the same input corpus we use, exemplifies a “linguistically
rich” count-based DSM, that relies on lemmas instead or raw word
forms, and has dimensions that encode the syntactic relations and/or
lexico-syntactic patterns linking targets and contexts. Baroni and
Lenci showed, in a large scale evaluation, that dm reaches
near-state-of-the-art performance in a variety of semantic tasks.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         We also experiment with the popular predict vectors made available by
Ronan Collobert.
         Following the earlier literature, with refer to them as
         Collobert and Weston
         (cw) vectors. These are 100-dimensional
vectors trained for two months (!) on the Wikipedia. In particular,
the vectors were trained to optimize the task of choosing the right
word over a random alternative in the middle of an 11-word context
window
         [14]
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Evaluation materials
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We test our models on a variety of benchmarks, most of them already
widely used to test and compare DSMs. The following benchmark
descriptions also explain the figures of merit and state-of-the-art
results reported in Table
        2
        .
       </p>
      </div>
      <div class="ltx_paragraph" id="S3.SS3.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Semantic relatedness
       </h4>
       <div class="ltx_para" id="S3.SS3.SSS0.P1.p1">
        <p class="ltx_p">
         A first set of semantic benchmarks
was constructed by asking human subjects to rate the degree of
semantic similarity or relatedness between two words on a numerical
scale. The performance of a computational model is assessed in terms
of correlation between the average scores that subjects assigned to
the pairs and the cosines between the corresponding vectors in the
model space (following the previous art, we use Pearson correlation
for rg, Spearman in all other cases). The classic data set of
         Rubenstein and Goodenough (1965)
         (rg) consists of 65 noun
pairs. State of the art performance on this set has been reported by
         Hassan and Mihalcea (2011)
         using a technique that exploits the
Wikipedia linking structure and word sense disambiguation
techniques.
         Finkelstein et al. (2002)
         introduced the widely used
WordSim353 set (ws) that, as the name suggests, consists of 353
pairs. The current state of the art is reached by
         Halawi et al. (2012)
         with a method that is in the spirit of the
predict models, but lets synonymy information from WordNet constrain
the learning process (by favoring solutions in which WordNet synonyms
are near in semantic space).
         Agirre et al. (2009)
         split the ws
set into similarity (wss) and relatedness (wsr) subsets. The first
contains tighter taxonomic relations, such as synonymy and co-hyponymy
(
         king/queen
         ) whereas the second encompasses broader, possibly
topical or syntagmatic relations (
         family/planning
         ). We report
state-of-the-art performance on the two subsets from the work of
Agirre and colleagues, who used different kinds of count vectors
extracted from a very large corpus (orders of magnitude larger than
ours). Finally, we use (the test section of) MEN (men), that comprises
1,000 word pairs.
         Bruni et al. (2013)
         , the developers of this
benchmark, achieve state-of-the-art performance by extensive tuning on
         ad-hoc
         training data, and by using both textual and
image-extracted features to represent word meaning.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS3.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Synonym detection
       </h4>
       <div class="ltx_para" id="S3.SS3.SSS0.P2.p1">
        <p class="ltx_p">
         The classic TOEFL (toefl) set was
introduced by
         Landauer and Dumais (1997)
         . It contains 80
multiple-choice questions that pair a target term with 4 synonym
candidates. For example, for the target
         levied
         one must choose
between
         imposed
         (correct),
         believed
         ,
         requested
         and
         correlated
         . The DSMs compute cosines of each candidate
vector with the target, and pick the candidate with largest cosine as
their answer. Performance is evaluated in terms of correct-answer
accuracy.
         Bullinaria and Levy (2012)
         achieved 100% accuracy by a
very thorough exploration of the count model parameter space.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS3.SSS0.P3">
       <h4 class="ltx_title ltx_title_paragraph">
        Concept categorization
       </h4>
       <div class="ltx_para" id="S3.SS3.SSS0.P3.p1">
        <p class="ltx_p">
         Given a set of nominal concepts,
the task is to group them into natural categories (e.g.,
         helicopters
         and
         motorcycles
         should go to the
         vehicle
         class,
         dogs
         and
         elephants
         into the
         mammal
         class). Following previous art, we tackle categorization
as an unsupervised clustering task. The vectors produced by a model
are clustered into
         n
         groups (with
         n
         determined by the gold
standard partition) using the CLUTO toolkit
         [26]
         , with
the repeated bisections with global optimization method and CLUTO’s
default settings otherwise (these are standard choices in the
literature). Performance is evaluated in terms of
         purity
         , a
measure of the extent to which each cluster contains concepts from a
single gold category. If the gold partition is reproduced perfectly,
purity reaches 100%; it approaches 0 as cluster quality
deteriorates. The Almuhareb-Poesio (ap) benchmark contains 402
concepts organized into 21 categories
         [2]
         . State-of-the-art purity was reached by
         Rothenhäusler and Schütze (2009)
         with a count model based on
carefully crafted syntactic links. The ESSLLI 2008 Distributional
Semantic Workshop shared-task set (esslli) contains 44 concepts
to be clustered into 6 categories
         [4]
         (we ignore
here the 3- and 2-way higher-level partitions coming with this
set).
         Katrenko and Adriaans (2008)
         reached top performance on this
set using the full Web as a corpus and manually crafted,
linguistically motivated patterns. Finally, the Battig (battig) test
set introduced by
         Baroni et al. (2010)
         includes 83 concepts from
10 categories. Current state of the art was reached by the
window-based count model of
         Baroni and Lenci (2010)
         .
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS3.SSS0.P4">
       <h4 class="ltx_title ltx_title_paragraph">
        Selectional preferences
       </h4>
       <div class="ltx_para" id="S3.SS3.SSS0.P4.p1">
        <p class="ltx_p">
         We experiment with two data sets
that contain verb-noun pairs that were rated by subjects for the
typicality of the noun as a subject or object of the verb (e.g.,
         people
         received a high average score as subject of
         to
eat
         , and a low score as object of the same verb). We follow the
procedure proposed by
         Baroni and Lenci (2010)
         to tackle this
challenge: For each verb, we use the corpus-based tuples they make
available to select the 20 nouns that are most strongly associated to
the verb as subjects or objects, and we average the vectors of these
nouns to obtain a “prototype” vector for the relevant argument
slot. We then measure the cosine of the vector for a target noun with
the relevant prototype vector (e.g., the cosine of
         people
         with
the
         eating
         subject prototype vector). Systems are evaluated by
Spearman correlation of these cosines with the averaged human
typicality ratings. Our first data set was introduced by Ulrike
         Padó (2007)
         and includes 211 pairs (up). Top-performance was
reached by the supervised count vector system of
         Herdağdelen and Baroni (2009)
         (supervised in the sense that they
directly trained a classifier on gold data, as opposed to the 0-cost
supervision of the context-learning methods). The mcrae set
         [31]
         consists of 100 noun–verb pairs, with top
performance reached by the DepDM system of
         Baroni and Lenci (2010)
         , a count DSM relying on syntactic
information.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS3.SSS0.P5">
       <h4 class="ltx_title ltx_title_paragraph">
        Analogy
       </h4>
       <div class="ltx_para" id="S3.SS3.SSS0.P5.p1">
        <p class="ltx_p">
         While all the previous data sets are relatively
standard in the DSM field to test traditional count models, our last
benchmark was introduced in
         Mikolov et al. (2013a)
         specifically
to test predict models. The data-set contains about 9K semantic and
10.5K syntactic analogy questions. A semantic question gives an
example pair (
         brother
         -
         sister
         ), a test word
(
         grandson
         ) and asks to find another word that instantiates the
relation illustrated by the example with respect to the test word
(
         granddaughter
         ). A syntactic question is similar, but in this
case the relationship is of a grammatical nature
(
         work
         –
         works
         ,
         speak
         …
         speaks
         ). Mikolov and colleagues tackle the challenge by
subtracting the second example term vector from the first, adding the
test term, and looking for the nearest neighbour of the resulting
vector (what is the nearest neighbour of
         b⁢r⁢o⁢t⁢h⁢e⁢r→-s⁢i⁢s⁢t⁢e⁢r→+g⁢r⁢a⁢n⁢d⁢s⁢o⁢n→
         ?). Systems are evaluated
in terms of proportion of questions where the nearest neighbour from
the whole semantic space is the correct answer (the given example and
test vector triples are excluded from the nearest neighbour
search).
         Mikolov et al. (2013a)
         reach top accuracy on the
syntactic subset (ansyn) with a CBOW predict model akin to ours
(but trained on a corpus twice as large). Top accuracy on the entire
data set (an) and on the semantic subset (ansem) was
reached by
         Mikolov et al. (2013c)
         using a skip-gram predict
model. Note however that, because of the way the task is framed,
performance also depends on the size of the vocabulary to be searched:
         Mikolov et al. (2013a)
         pick the nearest neighbour among vectors
for 1M words,
         Mikolov et al. (2013c)
         among 700K words, and we
among 300K words.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.SSS0.P5.p2">
        <p class="ltx_p">
         Some characteristics of the benchmarks we use are summarized in Table
         1
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
       Results
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Table
        2
        summarizes the evaluation results. The first
block of the table reports the maximum per-task performance (across
all considered parameter settings) for count and predict vectors. The
latter emerge as clear winners, with a large margin over count vectors
in most tasks. Indeed, the predictive models achieve an impressive
overall performance, beating the current state of the art in several
cases, and approaching it in many more. It is worth stressing that, as
reviewed in Section
        3
        , the state-of-the-art results
were obtained in almost all cases using specialized approaches that
rely on external knowledge, manually-crafted rules, parsing, larger
corpora and/or task-specific tuning. Our predict results were instead
achieved by simply downloading the word2vec toolkit and running it
with a range of parameter choices recommended by the toolkit
developers.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The success of the predict models cannot be blamed on poor performance
of the count models. Besides the fact that this would not explain the
near-state-of-the-art performance of the predict vectors, the count
model results are actually quite good in absolute terms. Indeed, in
several cases they are close, or even better than those attained by
dm, a linguistically-sophisticated count-based approach that was shown
to reach top performance across a variety of tasks by
        Baroni and Lenci (2010)
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Interestingly, count vectors achieve performance comparable to that of
predict vectors only on the selectional preference tasks. The up task
in particular is also the only benchmark on which predict models are
seriously lagging behind state-of-the-art and dm performance. Recall
from Section
        3
        that we tackle selectional
preference by creating average vectors representing typical verb
arguments. We conjecture that this averaging approach, that worked
well for dm vectors, might be problematic for prediction-trained
vectors, and we plan to explore alternative methods to build the
prototypes in future research.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Are our results robust to parameter choices, or are they due to very
specific and brittle settings? The next few blocks of Table
        2
        address this question. The second block reports
results obtained with single count and predict models that are best in
terms of average performance rank across tasks (these are the models
on the top rows of tables
        3
        and
        4
        , respectively). We see that, for both
approaches, performance is not seriously affected by using the single
best setup rather than task-specific settings, except for a
considerable drop in performance for the best predict model on esslli
(due to the small size of this data set?), and an even more dramatic
drop of the count model on ansem. A more cogent and interesting
evaluation is reported in the third block of Table
        2
        ,
where we see what happens if we use the single models with
        worst
        performance across tasks (recall from Section
        2
        above that, in any case, we are exploring a space of
reasonable parameter settings, of the sort that an experimenter might
be tempted to choose without tuning). The count model performance is
severely affected by this unlucky choice (2-word window, Local Mutual
Information, NMF, 400 dimensions, mean performance rank: 83), whereas
the predict approach is much more robust: To put its worst
instantiation (2-word window, hierarchical softmax, no subsampling,
200 dimensions, mean rank: 51) into perspective, its performance is
more than 10% below the
        best
        count model only for the an and
ansem tasks, and actually higher than it in 3 cases (note how on
esslli the worst predict models performs much better than the best
one, confirming our suspicion about the brittleness of this small data
set). The fourth block reports performance in what might be the most
realistic scenario, namely by tuning the parameters on a development
task. Specifically, we pick the models that work best on the small rg
set, and report their performance on all tasks (we obtained similar
results by picking other tuning sets). The selected count model is the
third best overall model of its class as reported in Table
        3
        . The selected predict model is the fourth best
model in Table
        4
        . The overall count performance is
not greatly affected by this choice. Again, predict models confirm
their robustness, in that their rg-tuned performance is always close
(and in 3 cases better) than the one achieved by the best overall
setup.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        Tables
        3
        and
        4
        let us take a
closer look at the most important count and predict parameters, by
reporting the characteristics of the best models (in terms of average
performance-based ranking across tasks) from both classes. For the
count models, PMI is clearly the better weighting scheme, and SVD
outperforms NMF as a dimensionality reduction technique. However, no
compression at all (using all 300K original dimensions) works
best. Compare this to the best overall predict vectors, that have 400
dimensions only, making them much more practical to use. For the
predict models, we observe in Table
        4
        that
negative sampling, where the task is to distinguish the target output word from samples drawn from the noise distribution, outperforms the more costly hierarchical softmax method. Subsampling frequent words, which downsizes the importance of these words similarly to PMI weighting in count models, is also bringing significant improvements.
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        Finally, we go back to Table
        2
        to point out the poor
performance of the out-of-the-box cw model. We must leave the
investigation of the parameters that make our predict vectors so much
better than cw (more varied training corpus? window size? objective
function being used? subsampling? …) to further work. Still, our
results show that it’s not just training by context prediction that
ensures good performance. The cw approach is very popular (for example
both
        Huang et al. (2012)
        and
        Blacoe and Lapata (2012)
        used
it in the studies we discussed in Section
        1
        ). Had
we also based our systematic comparison of count and predict vectors
on the cw model, we would have reached opposite conclusions from the
ones we can draw from our word2vec-trained vectors!
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
