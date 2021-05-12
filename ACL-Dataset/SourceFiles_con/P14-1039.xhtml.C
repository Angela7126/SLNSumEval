<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   That’s Not What I Meant! Using Parsers to Avoid Structural Ambiguities in Generated Text.
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
       We investigate whether parsers can be used for self-monitoring in
surface realization in order to avoid egregious errors involving
“vicious” ambiguities, namely those where the intended
interpretation fails to be considerably more likely than alternative
ones. Using parse accuracy in a simple reranking strategy for
self-monitoring, we find that with a state-of-the-art averaged
perceptron realization ranking model, BLEU scores cannot be improved
with any of the well-known Treebank parsers we tested, since these
parsers too often make errors that human readers would be unlikely
to make. However, by using an SVM ranker to combine the realizer’s
model score together with features from multiple parsers, including
ones designed to make the ranker more robust to parsing mistakes, we
show that significant increases in BLEU scores can be achieved.
Moreover, via a targeted manual analysis, we demonstrate that the
SVM reranker frequently manages to avoid vicious ambiguities, while
its ranking errors tend to affect fluency much more often than
adequacy.
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
        Rajkumar &amp;
White
        [28, 36]
        have recently shown that some rather egregious surface realization
errors—in the sense that the reader would likely end up with the
wrong interpretation—can be avoided by making use of features
inspired by psycholinguistics research together with an otherwise
state-of-the-art averaged perceptron realization ranking model
        [35]
        , as reviewed in the next
section. However, one is apt to wonder: could one use a parser
to check whether the intended interpretation is easy to recover,
either as an alternative or to catch additional mistakes? Doing so
would be tantamount to self-monitoring in
Levelt’s
        [21]
        model of language production.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Neumann &amp; van Noord
        [22]
        pursued
the idea of self-monitoring for generation in early work with
reversible grammars. As Neumann &amp; van Noord observed, a simple,
brute-force way to generate unambiguous sentences is to enumerate
possible realizations of an input logical form, then to parse each
realization to see how many interpretations it has, keeping only those
that have a single reading; they then went on to devise a more
efficient method of using self-monitoring to avoid generating
ambiguous sentences, targeted to the ambiguous portion of the output.
We might question, however, whether it is really possible to avoid
ambiguity entirely in the general case, since
Abney
        [1]
        and others have argued that
nearly every sentence is potentially ambiguous, though we (as human
comprehenders) may not notice the ambiguities if they are
unlikely. Taking up this issue, Khan et
al.
        [18]
        —building on Chantree et
al.’s
        [5]
        approach to identifying
“innocuous” ambiguities—conducted several experiments to test
whether ambiguity could be balanced against length or fluency in the
context of generating referring expressions involving coordinate
structures. Though Khan et al.’s study was limited to this one kind of
structural ambiguity, they do observe that generating the brief
variants when the intended interpretation is clear instantiates Van
Deemter’s
        [33]
        general strategy of only avoiding
        vicious ambiguities
        —that is, ambiguities where the intended
interpretation fails to be considerably more likely than any other
distractor interpretations—rather than trying to avoid all
ambiguities.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we investigate whether Neumann &amp; van Noord’s
brute-force strategy for avoiding ambiguities in surface realization
can be updated to only avoid vicious ambiguities, extending (and
revising) Van Deemter’s general strategy to all kinds of structural
ambiguity, not just the one investigated by Khan et al. To do so—in
a nutshell—we enumerate an
        n
        -best list of realizations and rerank
them if necessary to avoid vicious ambiguities, as determined by one
or more automatic parsers. A potential obstacle, of course, is that
automatic parsers may not be sufficiently representative of human
readers, insofar as errors that a parser makes may not be problematic
for human comprehension; moreover, parsers are rarely
successful in fully recovering the intended interpretation for
sentences of moderate length, even with carefully edited news text.
Consequently, we examine two reranking strategies, one a simple
baseline approach and the other using an SVM reranker
        [17]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Our simple reranking strategy for self-monitoring is to rerank the
realizer’s
        n
        -best list by parse accuracy, preserving the original
order in case of ties. In this way, if there is a realization in the
        n
        -best list that can be parsed more accurately than the top-ranked
realization—even if the intended interpretation cannot be recovered
with 100% accuracy—it will become the preferred output of the
combined realization-with-self-monitoring system. With this simple
reranking strategy and each of three different Treebank parsers, we
find that it is possible to improve BLEU scores on Penn Treebank
development data with White &amp;
Rajkumar’s
        [28, 36]
        baseline generative model, but not with their averaged perceptron
model. In inspecting the results of reranking with this strategy, we
observe that while it does sometimes succeed in avoiding egregious
errors involving vicious ambiguities, common parsing mistakes such as
PP-attachment errors lead to unnecessarily sacrificing conciseness or
fluency in order to avoid ambiguities that would be easily tolerated
by human readers. Therefore, to develop a more nuanced
self-monitoring reranker that is more robust to such parsing mistakes,
we trained an SVM using dependency precision and recall features for
all three parses, their
        n
        -best parsing results, and per-label
precision and recall for each type of dependency, together with the
realizer’s normalized perceptron model score as a feature. With the
SVM reranker, we obtain a significant improvement in BLEU scores over
White &amp; Rajkumar’s averaged perceptron model on both development and
test data. Additionally, in a targeted manual analysis, we find that
in cases where the SVM reranker improves the BLEU score, improvements
to fluency and adequacy are roughly balanced, while in cases where the
BLEU score goes down, it is mostly fluency that is made worse (with
reranking yielding an acceptable paraphrase roughly one third of the
time in both cases).
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        The paper is structured as follows. In Section
        2
        ,
we review the realization ranking models that serve as a starting
point for the paper. In Section
        3
        , we report on
our experiments with the simple reranking strategy, including a
discussion of the ways in which this method typically fails. In
Section
        4
        , we describe how we trained an SVM
reranker and report our results using BLEU scores
        [24]
        .
In Section
        5
        , we present a targeted manual analysis
of the development set sentences with the greatest change in BLEU
scores, discussing both successes and errors. In
Section
        6
        , we briefly review related work on broad
coverage surface realization. Finally, in Section
        7
        , we
sum up and discuss opportunities for future work in this direction.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Background
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We use the OpenCCG
        surface
realizer for the experiments reported in this paper. The OpenCCG
realizer generates surface strings for input semantic dependency
graphs (or logical forms) using a chart-based algorithm
        [37]
        for Combinatory Categorial Grammar
        [31]
        together with a “hypertagger” for
probabilistically assigning lexical categories to lexical predicates
in the input
        [10]
        . An example
input appears in Figure
        1
        . In the figure, nodes
correspond to discourse referents labeled with lexical predicates, and
dependency relations between nodes encode argument structure (gold
standard CCG lexical categories are also shown); note that
semantically empty function words such as infinitival-
        to
        are
missing. The grammar is extracted from a version of the CCGbank
        [15]
        enhanced for realization; the enhancements include:
better analyses of punctuation
        [34]
        ; less
error prone handling of named entities
        [26]
        ;
re-inserting quotes into the CCGbank; and assignment of consistent
semantic roles across diathesis alternations
        [4]
        , using PropBank
        [23]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        To select preferred outputs from the chart, we use White &amp;
Rajkumar’s
        [35, 36]
        realization ranking model, recently augmented with a large-scale
5-gram model based on the Gigaword corpus. The ranking model makes
choices addressing all three interrelated sub-tasks traditionally
considered part of the surface realization task in natural language
generation research
        [29, 30]
        : inflecting
lemmas with grammatical word forms, inserting function words and
linearizing the words in a grammatical and natural order. The model
takes as its starting point two probabilistic models of syntax that
have been developed for CCG parsing, Hockenmaier &amp; Steedman’s
        [14]
        generative model and Clark &amp;
Curran’s
        [7]
        normal-form model. Using the
averaged perceptron algorithm
        [8]
        , White &amp;
Rajkumar
        [35]
        trained a structured
prediction ranking model to combine these existing syntactic models
with several
        n
        -gram language models. This model improved upon the
state-of-the-art in terms of automatic evaluation scores on held-out
test data, but nevertheless an error analysis revealed a surprising
number of word order, function word and inflection errors. For each
kind of error, subsequent work investigated the utility of employing
more linguistically motivated features to improve the ranking model.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        To improve word ordering decisions, White &amp;
Rajkumar
        [36]
        demonstrated that
incorporating a feature into the ranker inspired by
Gibson’s
        [12]
        dependency locality theory
can deliver statistically significant improvements in automatic
evaluation scores, better match the distributional characteristics of
sentence orderings, and significantly reduce the number of serious
ordering errors (some involving vicious ambiguities) as confirmed by a
targeted human evaluation. Supporting Gibson’s theory, comprehension
and corpus studies have found that the tendency to
        minimize
dependency length
        has a strong influence on constituent ordering
choices; see
        Temperley (2007)
        and
        Gildea and Temperley (2010)
        for an overview.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Table
        1
        shows examples from
        White and Rajkumar (2012)
        of how the dependency length
feature (
        deplen
        ) affects the OpenCCG realizer’s output even
in comparison to a model (
        depord
        ) with a rich set of
discriminative syntactic and dependency ordering features, but no
features directly targeting relative weight. In wsj_0015.7, the
dependency length model produces an exact match, while the
        depord
        model fails to shift the short temporal adverbial
        next year
        next to the verb, leaving a confusingly repetitive
        this year next year
        at the end of the sentence. Note how
shifting
        next year
        from its canonical VP-final position to
appear next to the verb shortens its dependency length considerably,
while barely lengthening the dependency to
        based on
        ; at the
same time, it avoids ambiguity in what
        next year
        is
modifying. In wsj_0020.1 we see the reverse case: the dependency
length model produces a nearly exact match with just an equally
acceptable inversion of
        closely watching
        , keeping the direct
object in its canonical position. By contrast, the
        depord
        model mistakenly shifts the direct object
        South Korea, Taiwan
and Saudia Arabia
        to the end of the sentence where it is difficult
to understand following two very long intervening phrases.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        With function words,
        Rajkumar and White (2011)
        showed
that they could improve upon the earlier model’s predictions for when
to employ
        that
        -complementizers using features inspired by
Jaeger’s
        [16]
        work on using the principle
of
        uniform information density
        , which holds that human
language use tends to keep information density relatively constant in
order to optimize communicative efficiency. In news text,
complementizers are left out two times out of three, but in some cases
the presence of
        that
        is crucial to the
interpretation. Generally, inserting a complementizer makes the onset
of a complement clause more predictable, and thus less information
dense, thereby avoiding a potential spike in information density that
is associated with comprehension difficulty. Rajkumar &amp; White’s
experiments confirmed the efficacy of the features based on Jaeger’s
work, including information density–based features, in a local
classification model.
        Their experiments also showed that the improvements in
prediction accuracy apply to cases in which the presence of a
        that
        -complementizer arguably makes a substantial difference to
fluency or intelligiblity. For example, in (1), the
presence of
        that
        avoids a local ambiguity, helping the reader
to understand that
        for the second month in a row
        modifies the
reporting of the shortage; without
        that
        , it is very easy to
mis-parse the sentence as having
        for the second month in a
row
        modifying the saying event.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.ix1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          (1)
         </span>
         <div class="ltx_para" id="I1.ix1.p1">
          <p class="ltx_p">
           He said
           that
           /
           ∅
           ? for
the second month in a row, food processors reported a shortage of
nonfat dry milk. (PTB WSJ0036.61)
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        Finally, to reduce the number of subject-verb agreement errors,
        Rajkumar and White (2010)
        extended the earlier model with features
enabling it to make correct verb form choices in sentences involving
complex coordinate constructions and with expressions such as
        a lot of
        where the correct choice is not determined solely
by the head noun. They also improved animacy agreement with
relativizers, reducing the number of errors where
        that
        or
        which
        was chosen to modify an animate noun rather than
        who
        or
        whom
        (and vice-versa), while also allowing
both choices where corpus evidence was mixed.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Simple Reranking
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Methods
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We ran two OpenCCG surface realization models on the CCGbank dev set
(derived from Section 00 of the Penn Treebank) and obtained
         n
         -best
(
         n=10
         ) realizations. The first one is the baseline generative
model (hereafter, generative model) used in training the averaged
perceptron model. This model ranks realizations using the product of
the Hockenmaier syntax model,
         n
         -gram models over words, POS tags and
supertags in the training sections of the CCGbank, and the large-scale
5-gram model from Gigaword. The second one is the averaged perceptron
model (hereafter, perceptron model), which uses all the features
reviewed in Section
         2
         . In order to experiment with
multiple parsers, we used the Stanford dependencies
         [9]
         , obtaining gold dependencies from the
gold-standard PTB parses and automatic dependencies from the automatic
parses of each realization. Using dependencies allowed us to measure
parse accuracy independently of word order. We chose the Berkeley
parser
         [25]
         , Brown parser
         [6]
         and
Stanford parser
         [19]
         to parse the realizations
generated by the two realization models and calculated precision,
recall and F
         1
         of the dependencies for each realization by comparing
them with the gold dependencies. We then ranked the realizations by
their F
         1
         score of parse accuracy, keeping the original ranking in
case of ties. We also tried using unlabeled (and unordered)
dependencies, in order to possibly make better use of parses that were
close to being correct. In this setting, as long as the right pair of tokens
occur in a dependency relation, it was counted as a correctly
recovered dependency.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Simple ranking with the Berkeley parser of the generative model’s
         n
         -best realizations raised the BLEU score from 85.55 to 86.07,
well below the averaged perceptron model’s BLEU score of 87.93.
However, as shown in Table
         2
         , none of the parsers
yielded significant improvements on the top of the perceptron model.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Inspecting the results of simple ranking revealed that while simple
ranking did successfully avoid vicious ambiguities in some cases,
parser mistakes with PP-attachments, noun-noun compounds and
coordinate structures too often blocked the gold realization from
emerging on top. To illustrate, Figure
         2
         shows an example
with a PP-attachment mistake. In the figure, the key gold
dependencies of the reference sentence are shown in (a), the
dependencies of the realization selected by the simple ranker are
shown in (b), and the dependencies of the realization selected by the
perceptron ranker (same as gold) appear in (c), with the parsing mistake indicated by
the dashed line. The simple ranker ends up choosing (b) as the best
realization because it has the most accurate parse compared to the
reference sentence, given the mistake with (c).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Other common parse errors are illustrated in Figure
         3
         . Here,
(b) ends up getting chosen by the simple ranker as the realization
with the most accurate parse given the failures in (c), where
         the additional technology, personnel training
         is mistakenly
analyzed as one noun phrase, a reading unlikely to be considered by
human readers.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         In sum, although simple ranking helps to avoid vicious ambiguity in
some cases, the overall results of simple ranking are no better than
the perceptron model (according to BLEU, at least), as parse failures
that are not reflective of human intepretive tendencies too often lead
the ranker to choose dispreferred realizations. As such, we turn now
to a more nuanced model for combining the results of multiple parsers
in a way that is less sensitive to such parsing mistakes, while also
letting the perceptron model have a say in the final ranking.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Reranking with SVMs
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Methods
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Since different parsers make different errors, we conjectured that
dependencies in the intersection of the output of multiple parsers may
be more reliable and thus may more reliably reflect human
comprehension preferences. Similarly, we conjectured that large
differences in the realizer’s perceptron model score may more reliably
reflect human fluency preferences than small ones, and thus we
combined this score with features for parser accuracy in
an SVM ranker. Additionally, given that parsers may more reliably
recover some kinds of dependencies than others, we included features
for each dependency type, so that the SVM ranker might learn how to
weight them appropriately. Finally, since the differences among the
         n
         -best parses reflect the least certain parsing decisions, and thus
ones that may require more common sense inference that is easy for
humans but not machines, we conjectured that including features from the
         n
         -best
parses may help to better match human performance. In more detail, we
made use of the following feature classes for each candidate
realization:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <dl class="ltx_description" id="I2">
         <dt class="ltx_item" id="I2.ix1">
          <span class="ltx_tag ltx_tag_description">
           perceptron model score
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix1.p1">
           <p class="ltx_p">
            the score from the realizer’s model,
normalized to [0,1] for the realizations in the
            n
            -best list
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix2">
          <span class="ltx_tag ltx_tag_description">
           precision and recall
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix2.p1">
           <p class="ltx_p">
            labeled and unlabeled precision and recall
for each parser’s best parse
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix3">
          <span class="ltx_tag ltx_tag_description">
           per-label precision and recall (
           dep
           )
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix3.p1">
           <p class="ltx_p">
            precision and recall for each type of
dependency obtained from each parser’s best parse (using zero if not
defined for lack of predicted or gold dependencies with a given label)
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix4">
          <span class="ltx_tag ltx_tag_description">
           n
           -best precision and recall (
           nbest
           )
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix4.p1">
           <p class="ltx_p">
            labeled and
unlabeled precision and recall for each parser’s top five parses,
along with the same features for the most accurate of these parses
           </p>
          </div>
         </dd>
        </dl>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         In training, we used the BLEU scores of each realization compared with
its reference sentence to establish a preference order over pairs of
candidate realizations, assuming that the original corpus sentences are generally better than
related alternatives, and that BLEU can somewhat reliably predict
human preference judgments.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         We trained the SVM ranker
         [17]
         with a linear kernel and
chose the hyper-parameter
         c
         , which tunes the trade-off between
training error and margin, with 6-fold cross-validation on the
devset. We trained different models to investigate the contribution
made by different parsers and different types of features, with the
perceptron model score included as a feature in all models. For each
parser, we trained a model with its overall precision and recall
features, as shown at the top of Table
         3
         . Then we
combined these three models to get a new model (Bkl+Brw+St in the
table) . Next, to this combined model we separately added (i) the
per-label precision and recall features from all the parsers
(BBS+dep), and (ii) the
         n
         -best features from the parsers
(BBS+nbest). The full model (BBS+dep+nbest) includes all the features
listed above. Finally, since the Berkeley parser yielded the best
results on its own, we also tested models using all the feature
classes but only using this parser by itself.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Table
         3
         shows the results of different SVM ranking
models on the devset. We calculated significance using paired bootstrap resampling
         [20]
         .
         Both the per-label precision &amp; recall features and the
         n
         -best parse
features contributed to achieving a significant improvement compared
to the perceptron model. Somewhat surprisingly, the Berkeley parser
did as well as all three parsers using just the overall precision and
recall features, but not quite as well using all features.
The complete model, BBS+dep+nbest, achieved a BLEU score of 88.73,
significantly improving upon the perceptron model (
         p&lt;0.02
         ). We
then confirmed this result on the final test set, Section 23 of the
CCGbank, as shown in Table
         4
         (
         p&lt;0.02
         as well).
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Analysis and Discussion
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Targeted Manual Analysis
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         In order to gain a better understanding of the successes and failures
of our SVM ranker, we present here a targeted manual analysis of the
development set sentences with the greatest change in BLEU scores,
carried out by the second author (a native speaker). In this
analysis, we consider whether the reranked realization improves upon
or detracts from realization quality—in terms of adequacy, fluency,
both or neither—along with a linguistic categorization of the
differences between the reranked realization and the original
top-ranked realization according to the averaged perceptron model.
Unlike the broad-based and objective evaluation in terms of BLEU
scores presented above, this analysis is narrowly targeted and
subjective, though the interested reader is invited to review the
complete set of analyzed examples that accompany the paper as a
supplement. We leave a more broad-based human evaluation by naive
subjects for future work.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Table
         5
         shows the results of the analysis, both
overall and for the most frequent categories of changes. Of the 50
sentences where the BLEU score went up the most, 15 showed an
improvement in adequacy (i.e., in conveying the intended meaning), 22
showed an improvement in fluency (with 3 cases also improving
adequacy), and 16 yielded no discernible change in fluency or
adequacy. By contrast, with the 50 sentences where the BLEU score
went down the most, adequacy was only affected 4 times, though fluency
was affected 32 times, and 15 remained essentially
unchanged.
         The table
also shows that differences in the order of VP constituents usually
led to a change in adequacy or fluency, as did ordering changes within
NPs, with noun-noun compounds and named entities as the most frequent
subcategories of NP-ordering changes. Of the cases where adequacy and
fluency were not affected, contractions and subject-verb inversions
were the most frequent differences.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         Examples of the changes yielded by the SVM ranker appear in
Table
         6
         . With wsj_0036.54, the averaged
perceptron model selects a realization that regrettably (though
amusingly) swaps
         purchasing
         and
         more than
250
         —yielding a sentence that suggests that the executives have
been purchased!—while the SVM ranker succeeds in ranking the
original sentence above all competing realizations. With
wsj_0088.25, self-monitoring with the SVM ranker yields a realization
nearly identical to the original except for an extra comma, where it
is clear that
         in public
         modifies
         do this
         ; by
contrast, in the perceptron-best realization,
         in public
         mistakenly appears to modify
         be disclosed
         . With
wsj_0041.18, the SVM ranker unfortunately prefers a realization where
         presumably
         seems to modify
         shows
         rather than
         of two politicians
         as in the original, which the averaged
perceptron model prefers. Finally, wsj_0044.111 is an example where
a subject-inversion makes no difference to adequacy or fluency.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Discussion
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         The BLEU evaluation and targeted manual analysis together show that
the SVM ranker increases the similarity to the original corpus of
realizations produced with self-monitoring, often in ways that are
crucial for the intended meaning to be apparent to human readers.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         A limitation of the experiments reported in this paper is that
OpenCCG’s input semantic dependency graphs are not the same as the
Stanford dependencies used with the Treebank parsers, and thus we have
had to rely on the gold parses in the PTB to derive gold dependencies
for measuring accuracy of parser dependency recovery. In a realistic
application scenario, however, we would need to measure parser
accuracy relative to the realizer’s input. We initially tried using
OpenCCG’s parser in a simple ranking approach, but found that it did
not improve upon the averaged perceptron model, like the three parsers
used subsequently. Given that with the more refined SVM ranker, the
Berkeley parser worked nearly as well as all three parsers together
using the complete feature set, the prospects for future work on a
more realistic scenario using the OpenCCG parser in an SVM ranker for
self-monitoring now appear much more promising, either using OpenCCG’s
reimplementation of Hockenmaier &amp; Steedman’s generative CCG model, or
using the Berkeley parser trained on OpenCCG’s enhanced version of the
CCGbank, along the lines of
         Fowler and Penn (2010)
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        Approaches to surface realization have been developed for LFG, HPSG,
and TAG, in addition to CCG, and recently statistical dependency-based
approaches have been developed as well; see the report from the first
surface realization shared task
        [3, 2]
        for an overview. To
our knowledge, however, a comprehensive investigation of avoiding
vicious structural ambiguities with broad coverage statistical parsers
has not been previously explored. As our SVM ranking model does not
make use of CCG-specific features, we would expect our
self-monitoring method to be equally applicable to realizers using
other frameworks.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
