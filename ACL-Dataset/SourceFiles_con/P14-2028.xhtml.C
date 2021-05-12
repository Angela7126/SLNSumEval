<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improved Iterative Correction for Distant Spelling Errors.
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
       Noisy channel models, widely used in modern spellers, cope with typical
misspellings, but do not work well with infrequent and difficult spelling
errors. In this paper, we have improved the noisy channel approach
by iterative stochastic search for the best correction. The proposed algorithm
allowed us to avoid local minima problem and improve the
       F1
       measure by 6.6%
on distant spelling errors.
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
        A speller is an essential part of any program associated with text input and
processing — e-mail system, search engine, browser, form editor etc. To
detect and correct spelling errors, the state of the art spelling correction
systems use the noisy channel approach
        [6, 8, 1]
        . Its models are
usually trained on large corpora and provide high effectiveness in correction
of typical errors (most of which consist of 1-2 wrong characters per word), but
does not work well for complex (multi-character) and infrequent errors.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper, we improved effectiveness of the noisy channel for the correction
of complex errors. In most cases, these are cognitive errors in
loan words (
        folsvagen
        →
        volkswagen
        ),
names of drugs (
        vobemzin
        →
        wobenzym
        ),
names of brands (
        scatcher
        →
        skechers
        ),
scientific terms (
        heksagidron
        →
        hexahedron
        ) and
last names (
        Shwartzneger
        →
        Schwarzenegger
        ). In all these
cases, the misspelled word contains many errors and the corresponding error
model penalty cannot be compensated by the LM weight of its proper form. As a
result, either the misspelled word itself, or the other (less complicated, more
frequent) misspelling of the same word wins the likelihood race.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        To compensate for this defect of the noisy channel, the iterative approach
        [3]
        is typically used. The search for the best variant
is repeated several times, what allows correcting rather complex errors, but
does not completely solve the problem of falling into local minima. To overcome
this issue we suggest to consider more correction hypotheses. For this purpose
we used a method based on the simulated annealing algorithm. We experimentally
demonstrate that the proposed method outperforms the baseline noisy channel and
iterative spellers.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Many authors employ machine learning to build rankers that compensate for the
drawbacks of the noisy channel model:
        [9, 5]
        .
These techniques can be combined with the proposed method by replacing
posterior probability of single correction in our method with an estimate
obtained via discriminative training method.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        In our work, we focus on isolated word-error correction
        [7]
        , which, in a sense, is a harder task, than
multi-word correction, because there is no context available for misspelled
words. For experiments we used single-word queries to a commercial search
engine.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Baseline speller
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Noisy channel spelling correction
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Noisy channel is a probabilistic model that defines posterior
probability
         P(q0|q1)
         of
         q0
         being the intended word, given the observed
word
         q1
         ; for such model, the optimal decision rule
         μ
         is the following:
        </p>
        μ(q1)=argmaxq0P(q0|q1);P(q0|q1)∝Pdist(q0→q1)PLM(q0),

(1)
        <p class="ltx_p">
         where
         PLM
         is the source (language) model, and
         Pdist
         is the error model. Given
         P(q0|q1)
         defined, to correct the word
         q1
         we
could iterate through all ever-observed words, and choose the one, that
maximizes the posterior probability. However, the practical considerations
demand that we do not rank the whole list of words, but instead choose between
a limited number of hypotheses
         h1,…,hK
         :
        </p>
        <ol class="ltx_enumerate" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Given
            q1
            , generate a set of hypotheses
            h1,…,hK
            , such that
           </p>
           ∑k=1KP(q0=hk|q1)≈1;

(2)
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Choose the hypothesis
            hk
            that maximizes
            P(q0=hk|q1)
            .
           </p>
          </div>
         </li>
        </ol>
        <p class="ltx_p">
         If hypotheses constitute a major part of the posterior probability mass, it is
highly unlikely that the intended word is not among them.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Baseline speller setup
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         In baseline speller we use a substring-based error model
         Pdist(q0→q1)
         described in
         [1]
         , the error
model training method and the hypotheses generator are similar to
         [4]
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         For building language (
         PLM′
         ) and error (
         Pdist′
         ) models, we
use words collected from the 6-months query log of a commercial search
engine.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         Hypotheses generator is based on A* beam search in a trie of words, and yields
         K
         hypotheses
         hk
         , for which the noisy channel scores
         Pdist(hk→q1)PLM(hk)
         are highest possible. Hypotheses
generator has high K-best recall (see Section
         4.2
         ) — in 91.8%
cases the correct hypothesis is found when
         K=30
         , which confirms the
assumption about covering almost all posterior probability mass
(see Equation
         2
         ).
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Improvements for noisy channel spelling correction
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        While choosing
        arg⁢max
        of the posterior probability is an optimal decision
rule in theory, in practice it might not be optimal, due to limitations of the
language and error modeling. For example,
        vobemzin
        is corrected to more
frequent misspelling
        vobenzin
        (instead of correct form
        wobenzym
        )
by the noisy channel, because
        Pdist(vobemzin→wobenzym)
        is too low
(see Table
        1
        ).
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        There have been attempts
        [3]
        to apply other rules,
which would overcome limitations of language and error models with compensating
changes described further.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Iterative correction
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Iterative spelling correction with
         E
         iterations uses standard noisy-channel
to correct the query
         q
         repeatedly
         E
         times. It is motivated by the
assumption, that we are more likely to successfully correct the query if we
take several short steps instead of one big step
         [3]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Iterative correction is hill climbing in the space of possible corrections:
on each iteration we make a transition to the best point in the neighbourhood,
i.e. to correction, that has maximal posterior probability
         P(c|q)
         . As any
local search method, iterative correction is prone to local minima, stopping
before reaching the correct word.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Stochastic iterative correction
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         A common method of avoiding local minima in optimization is the simulated
annealing algorithm, key ideas from which can be adapted for spelling correction
task. In this section we propose such an adaptation. Consider: we do not always
transition deterministically to the next best correction, but instead transition
randomly to a (potentially
         any
         ) correction with transition probability
being equal to the posterior
         P(ci|ci-1)
         , where
         ci-1
         is the
correction we transition from,
         ci
         is the correction we transition to, and
         P(⋅|⋅)
         is defined by Equation
         1
         . Iterative correction then
turns into a
         random walk
         : we start at word
         c0=q
         and stop after
         E
         random steps at some word
         cE
         , which becomes our answer.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         To turn random walk into deterministic spelling correction algorithm, we
de-randomize it, using the following transformation. Described random walk
defines, for each word
         w
         , a probability
         P(cE=w|q)
         of ending up in
         w
         after starting a walk from the initial query
         q
         . With that probability
defined, our correction algorithm is the following: given query
         q
         , pick
         c=argmaxcEP(cE|q)
         as a correction.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Probability of getting from
         c0=q
         to some
         cE=c
         is a sum, over all possible
paths, of probabilities of getting from
         q
         to
         c
         via specific path
         q=c0→c1→…→cE-1→cE=c
         :
        </p>
        P(cE|c0)=∑c1∈W…cE-1∈W∏i=1EP(ci|ci-1),

(3)
        P(ci|ci-1)=Pdist(ci→ci-1)PLM(ci)Pobserve⁢(ci-1),

(4)
        <p class="ltx_p">
         where
         W
         is the set of all possible words, and
         Pobserve⁢(w)
         is the probability of observing
         w
         as a query in the noisy-channel model.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Example: if we start a random walk from
         vobemzin
         and make 3 steps, we
most probably will end up in the correct form
         wobenzym
         with
         P=0.361
         .
A few of the most probable random walk paths are shown in Table
         2
         .
Note, that despite the fact that most probable path does not lead to the
correct word, many other paths to
         wobenzym
         sum up to 0.361, which is
greater than probability of any other word. Also note, that the method works
only because multiple misspellings of the same word are presented in our model;
for related research see
         [2]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         Also note, that while Equation
         3
         uses noisy-channel posteriors, the
method can use an arbitrary discriminative model, for example the one from
         [5]
         , and benefit from a more accurate posterior estimate.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Additional heuristics
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         This section describes some common heuristic improvements, that, where
possible, were applied both to the baseline methods and to the proposed
algorithm.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         Basic building block of every mentioned algorithm is one-step noisy-channel
correction. Each basic correction proceeds as described in
Section
         2.1
         : a small number of hypotheses
         h1,…,hK
         is
generated for the query
         q
         , hypotheses are scored, and scores are recomputed
into normalized posterior probabilities (see Equation
         5
         ).
Posterior probabilities are then either used to pick the best correction (in
baseline and simple iterative correction), or are accumulated to later compute
the score defined by Equation
         3
         .
        </p>
        score(hi)=Pdist(hi→q)λPLM(hi)P(hi|q)=score(hi)/∑j=1Kscore(hj)

(5)
        <p class="ltx_p">
         A standard log-linear weighing trick was applied to noisy-channel model
components, see e.g.
         [9]
         .
         λ
         is the parameter that
controls the trade-off between precision and recall (see
Section
         4.2
         ) by emphasizing the importance of either the high
frequency of the correction or its proximity to the query.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         We have also found, that resulting posterior probabilities emphasize the best
hypothesis too much: best hypothesis gets almost all probability mass and other
hypotheses get none. To compensate for that, posteriors were
         smoothed
         by
raising each probability to some power
         γ&lt;1
         and re-normalizing them
afterward:
        </p>
        Psmooth(hi|q)=P(hi|q)γ/∑j=1KP(hj|q)γ.

(6)
        <p class="ltx_p">
         In a sense,
         γ
         is like temperature parameter in simulated annealing – it
controls the entropy of the walk and the final probability distribution.
Unlike in simulated annealing, we fix
         γ
         for all iterations of the
algorithm.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         Finally, if posterior probability of the best hypothesis was lower than
threshold
         α
         , then the original query
         q
         was used as the spell-checker
output. (Posterior is defined by Equation
         6
         for the baseline and
simple iterative methods and by Equations
         3
         and
         6
         for
the proposed method). Parameter
         α
         controls precision/recall trade-off
(as well as
         λ
         mentioned above).
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
         To evaluate the proposed algorithm we have collected two datasets.
Both datasets were randomly sampled from single-word user queries from the
1-week query log of a commercial search engine. We annotated them with the help
of professional analyst. The difference between datasets is that one of them
contained only queries with low search performance: for which the number of
documents retrieved by the search engine was less than a fixed threshold (we
will address it as the ”hard” dataset), while the other dataset had no such
restrictions (we will call it ”common”). Dataset statistics are shown in
Table
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Increased average error model score and error rate of ”common” dataset
compared to ”hard” shows, that we have indeed managed to collect
hard-to-correct queries in the ”hard” dataset.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Experimental results
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         First of all, we evaluated the recall of hypotheses generator using
         K-best recall
         — the number of correct spelling corrections for
misspelled queries among
         K
         hypotheses divided by the total number of
misspelled queries in the test set. Resulting recall with
         K=30
         is 91.8% on
”hard” and 98.6% on ”common”.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Next, three spelling correction methods were tested: noisy channel, iterative
correction and our method (stochastic iterative correction).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         For evaluation of spelling correction quality, we use the following metrics:
        </p>
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            Precision
            : The number of correct spelling corrections for
misspelled words generated by the system divided by the total number of
corrections generated by the system;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            Recall
            : The number of correct spelling corrections for
misspelled words generated by the system divided by the total number of
misspelled words in the test set;
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         For hypotheses generator,
         K=30
         was fixed: recall of 91.8% was considered
big enough. Precision/recall tradeoff parameters
         λ
         and
         α
         (they
are applicable to each method, including baseline) were iterated by the grid
         (0.2,0.25,0.3,…,1.5)×(0,0.025,0.05,…,1.0)
         , and
         E
         (applicable to iterative and our method) and
         γ
         (just our method)
were iterated by the grid
         (2,3,4,5,7,10)×(0.1,0.15,…⁢1.0)
         ;
for each set of parameters, precision and recall were measured on both
datasets. Pareto frontiers for precision and recall are shown in
Figures
         1
         and
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         We were not able to reproduce superior performance of the iterative method over
the noisy channel, reported by
         [3]
         . Supposedly, it is
because the iterative method benefits primarily from the sequential application
of split/join operations altering query decomposition into words; since we are
considering only one-word queries, such decomposition does not matter.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         On the ”hard” dataset the performance of the noisy channel and the iterative
methods is inferior to our proposed method, see Figure
         1
         .
We tested all three methods on the ”common” dataset as well to evaluate if our
handling of hard cases affects the performance of our approach on the common
cases of spelling error. Our method performs well on the common cases as well,
as Figure
         2
         shows. The performance comparison for the
”common” dataset shows comparable performance for all considered methods.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         Noisy channel and iterative methods’ frontiers are considerably inferior to the
proposed method on ”hard” dataset, which means that our method works
better. The results on ”common” dataset show, that the proposed method doesn’t
work worse than baseline.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p7">
        <p class="ltx_p">
         Next, we optimized parameters for each method and each dataset separately to
achieve the highest
         F1
         measure. Results are shown in Tables
         4
         and
         5
         . We can see, that, given the proper tuning, our method
can work better on any dataset (but it cannot achieve the best performance on
both datasets at once). See Tables
         4
         and
         5
         for
details.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p8">
        <p class="ltx_p">
         Next, each parameter was separately iterated (by a coarser grid); initial
parameters for each method were taken from Table
         4
         . Such
iteration serves two purposes: to show the influence of parameters on algorithm
performance, and to show differences between datasets: in such setup parameters
are virtually tuned using ”hard” dataset and evaluated using ”common” dataset.
Results are shown in Table
         6
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p9">
        <p class="ltx_p">
         The proposed method is able to successfully correct distant spelling errors
with edit distance of 3 characters (see Table
         7
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p10">
        <p class="ltx_p">
         However, if our method is applied to shorter and more frequent queries (as
opposed to ”hard” dataset), it tends to suggest frequent words as
false-positive corrections (for example,
         grid
         is corrected to
         creed
         – Assassin’s Creed is popular video game). As can be seen in
Table
         5
         , in order to fix that, algorithm parameters need
to be tuned more towards precision.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
