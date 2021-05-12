<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Ambiguity-aware Ensemble Training for Semi-supervised Dependency Parsing.
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
       This paper proposes a simple yet effective framework for semi-supervised dependency parsing at entire tree level, referred to as
       ambiguity-aware ensemble training
       .
Instead of only using 1-best parse trees in previous work, our core idea is to utilize parse forest (
       ambiguous labelings
       ) to combine multiple 1-best parse trees generated from diverse parsers on unlabeled data.
With a conditional random field based probabilistic dependency parser, our training objective is to maximize mixed likelihood of labeled data and auto-parsed unlabeled data with ambiguous labelings.
This framework offers two promising advantages.
1) ambiguity encoded in parse forests compromises noise in 1-best parse trees.
During training, the parser is aware of these ambiguous structures, and has the flexibility to distribute probability mass to its preferred parse trees as long as the likelihood improves.
2) diverse syntactic structures produced by different parsers can be naturally compiled into forest,
offering complementary strength to our single-view parser.
Experimental results on benchmark data show that our method significantly outperforms the baseline supervised parser and other entire-tree based semi-supervised methods, such as self-training, co-training and tri-training.
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
        Supervised dependency parsing has made great progress during the past decade.
However, it is very difficult to further improve performance of supervised parsers. For example,
        and
        show that incorporating higher-order features into a graph-based parser only leads to modest increase in parsing accuracy.
In contrast, semi-supervised approaches, which can make use of large-scale unlabeled data, have attracted more and more interest.
Previously, unlabeled data is explored to derive useful local-context features such as word clusters
        []
        , subtree frequencies
        []
        , and
word co-occurrence counts
        []
        .
A few effective learning methods are also proposed for dependency parsing to implicitly utilize distributions on unlabeled data
        []
        .
All above work leads to significant improvement on parsing accuracy.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Another line of research is to pick up some high-quality auto-parsed training instances from unlabeled data using bootstrapping methods, such as self-training
        []
        , co-training
        []
        , and tri-training
        []
        . However, these methods gain limited success in dependency parsing.
Although working well on constituent parsing
        []
        ,
self-training is shown unsuccessful for dependency parsing
        []
        . The reason may be that dependency parsing models are prone to amplify previous mistakes during training on self-parsed unlabeled data.
        apply a variant of co-training to dependency parsing and report positive results on out-of-domain text.
        combine tri-training and parser ensemble to boost parsing accuracy. Both work employs two parsers to process the unlabeled data, and only select as extra training data sentences on which the 1-best parse trees of the two parsers are identical.
In this way, the auto-parsed unlabeled data becomes more reliable.
However, one obvious drawback of these methods is that they are unable to
exploit unlabeled data with divergent outputs from different parsers.
Our experiments show that unlabeled data with identical outputs from different parsers tends to be short (18.25 words per sentence on average), and only has a small proportion of 40% (see Table
        6
        ).
More importantly, we believe that unlabeled data with divergent outputs is equally (if not more) useful.
Intuitively, an unlabeled sentence with divergent outputs should contain some ambiguous syntactic structures (such as preposition phrase attachment) that are very hard to resolve and lead to the disagreement of different parsers.
Such sentences can provide more discriminative instances for training
which may be unavailable in labeled data.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        To solve above issues,
this paper proposes a more general and effective framework for semi-supervised dependency parsing, referred to as
        ambiguity-aware ensemble training
        .
Different from traditional self/co/tri-training which only use 1-best parse trees on unlabeled data,
our approach adopts ambiguous labelings, represented by parse forest, as gold-standard for unlabeled sentences.
Figure
        1
        shows an example sentence with an ambiguous parse forest.
The forest is formed by two parse trees, respectively shown at the upper and lower sides of the sentence.
The differences between the two parse trees are highlighted using dashed arcs.
The upper tree take
        “deer”
        as the subject of
        “riding”
        ,
whereas the lower one indicates that
        “he”
        rides the bicycle.
The other difference is where the preposition phrase (PP)
        “in the park”
        should be attached, which is also known as the PP attachment problem, a notorious challenge for parsing.
Reserving such uncertainty has three potential advantages.
First, noise in unlabeled data is largely alleviated, since parse forest encodes only a few highly possible parse trees with high oracle score.
Please note that the parse forest in Figure
        1
        contains four parse trees after combination of the two different choices.
Second, the parser is able to learn useful features from the unambiguous parts of the parse forest.
Finally, with sufficient unlabeled data, it is possible that the parser can learn to resolve such uncertainty
by biasing to more reasonable parse trees.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        To construct parse forest on unlabeled data,
we employ three supervised parsers based on different paradigms, including
our baseline graph-based dependency parser, a transition-based dependency parser
        []
        , and a generative constituent parser
        []
        .
The 1-best parse trees of these three parsers are aggregated in different ways.
Evaluation on labeled data shows the oracle accuracy of parse forest is much higher than that of 1-best outputs of single parsers (see Table
        3
        ).
Finally, using a conditional random field (CRF) based probabilistic parser,
we train a better model by
maximizing mixed likelihood of labeled data and auto-parsed unlabeled data with ambiguous labelings.
Experimental results on both English and Chinese datasets demonstrate that the proposed ambiguity-aware ensemble training outperforms other entire-tree based methods such as self/co/tri-training.
In summary, we make following contributions.
       </p>
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           We propose a generalized ambiguity-aware ensemble training framework for semi-supervised dependency parsing, which can make better use of unlabeled data, especially when parsers from different views produce divergent syntactic structures.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           We first employ a generative constituent parser for semi-supervised dependency parsing. Experiments show that the constituent parser is very helpful since it produces more divergent structures for our semi-supervised parser than discriminative dependency parsers.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           We build the first state-of-the-art CRF-based dependency parser. Using the probabilistic parser, we benchmark and conduct systematic comparisons among ours and all previous bootstrapping methods, including self/co/tri-training.
          </p>
         </div>
        </li>
       </ol>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Supervised Dependency Parsing
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Given an input sentence
        𝐱=w0⁢w1⁢…⁢wn
        ,
the goal of dependency parsing is to build a dependency tree as depicted in Figure
        1
        ,
denoted by
        𝐝={(h,m):0≤h≤n,0&lt;m≤n}
        ,
where
        (h,m)
        indicates a directed arc
from the
        head
        word
        wh
        to the
        modifier
        wm
        , and
        w0
        is an artificial node linking to the root of the sentence.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        In parsing community,
two mainstream methods tackle the dependency parsing problem from different perspectives but achieve comparable accuracy on a variety of languages.
The graph-based method views the problem as finding an optimal tree from a fully-connected directed graph
        []
        ,
while the transition-based method tries to find a highest-scoring transition sequence that leads to a legal dependency tree
        []
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Graph-based Dependency Parser (GParser)
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         In this work, we adopt the graph-based paradigm because it allows us to naturally derive conditional probability of a dependency tree
         𝐝
         given a sentence
         𝐱
         , which is required to compute likelihood of both labeled and unlabeled data.
Under the graph-based model, the score of a dependency tree is factored into the scores of small subtrees
         𝐩
         .
        </p>
        S⁢c⁢o⁢r⁢e⁢(𝐱,𝐝;𝐰)=𝐰⋅𝐟⁢(𝐱,𝐝)=∑𝐩⊆𝐝S⁢c⁢o⁢r⁢e⁢(𝐱,𝐩;𝐰)
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         We adopt the second-order graph-based dependency parsing model of
         as our core parser, which incorporates features from the two kinds of subtrees in Fig.
         2
         .
         Then the score of a dependency tree is:
        </p>
        S⁢c⁢o⁢r⁢e⁢(𝐱,𝐝;𝐰)=∑{(h,m)}⊆𝐝𝐰d⁢e⁢p⋅𝐟d⁢e⁢p⁢(𝐱,h,m)+∑{(h,s),(h,m)}⊆𝐝𝐰s⁢i⁢b⋅𝐟s⁢i⁢b⁢(𝐱,h,s,m)
        <p class="ltx_p">
         where
         𝐟d⁢e⁢p⁢(𝐱,h,m)
         and
         𝐟s⁢i⁢b⁢(𝐱,h,s,m)
         are the feature vectors of the two subtree in Fig.
         2
         ;
         𝐰d⁢e⁢p/s⁢i⁢b
         are feature weight vectors; the dot product gives scores contributed by corresponding subtrees.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         For syntactic features, we adopt those of
         which
include two categories corresponding to the two types of scoring subtrees in Fig.
         2
         .
We summarize the atomic features used in each feature category in Table
         1
         .
These atomic features are concatenated in different combinations to compose rich feature sets.
Please refer to Table 4 of
         for the complete feature list.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        CRF-based GParser
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Previous work on graph-based dependency parsing mostly adopts linear models and perceptron based training procedures,
which lack probabilistic explanations of dependency trees and do not need to compute likelihood of labeled training data.
Instead, we build a log-linear CRF-based dependency parser, which is similar to the CRF-based constituent parser of
         .
Assuming the feature weights
         𝐰
         are known, the probability of a dependency tree
         𝐝
         given an input sentence
         𝐱
         is defined as:
        </p>
        p(𝐝|𝐱;𝐰)=e⁢x⁢p⁢{S⁢c⁢o⁢r⁢e⁢(𝐱,𝐝;𝐰)}Z⁢(𝐱;𝐰)Z(𝐱;𝐰)=∑𝐝′∈𝒴⁢(𝐱)exp{Score(𝐱,𝐝′;𝐰)}

(1)
        <p class="ltx_p">
         where
         Z⁢(𝐱)
         is the normalization factor and
         𝒴⁢(𝐱)
         is the set of all legal dependency trees for
         𝐱
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         Suppose the labeled training data is
         𝒟={(𝐱i,𝐝i)}i=1N
         .
Then the log likelihood of
         𝒟
         is:
        </p>
        ℒ(𝒟;𝐰)=∑i=1Nlogp(𝐝i|𝐱i;𝐰)
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         The training objective is to maximize the log likelihood of the training data
         ℒ⁢(𝒟)
         .
The partial derivative with respect to the feature weights
         𝐰
         is:
        </p>
        ∂⁡ℒ⁢(𝒟;𝐰)∂⁡𝐰=∑i=1N(𝐟⁢(𝐱i,𝐝i)-∑𝐝′∈𝒴⁢(𝐱i)p(𝐝′|𝐱i;𝐰)𝐟(𝐱i,𝐝′))

(2)
        <p class="ltx_p">
         where the first term is the empirical counts and the second term is the model expectations.
Since
         𝒴⁢(𝐱i)
         contains exponentially many dependency trees, direct calculation of the second term is
prohibitive.
Instead, we can use the classic inside-outside algorithm to efficiently
compute the model expectations within
         O⁢(n3)
         time complexity, where
         n
         is the input sentence length.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Ambiguity-aware Ensemble Training
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In standard entire-tree based semi-supervised methods such as self/co/tri-training,
automatically parsed unlabeled sentences are used as additional training data, and
noisy 1-best parse trees are considered as gold-standard.
To alleviate the noise, the tri-training method only uses unlabeled data on which multiple parsers from different views produce identical parse trees.
However, unlabeled data with divergent syntactic structures should be more useful.
Intuitively, if several parsers disagree on an unlabeled sentence,
it implies that the unlabeled sentence contains some difficult syntactic phenomena which are not sufficiently covered in manually labeled data.
Therefore, exploiting such unlabeled data may introduce more discriminative syntactic knowledge,
largely compensating labeled training data.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        To address above issues, we propose
        ambiguity-aware ensemble training
        , which can be interpreted as
a
        generalized tri-training
        framework.
The key idea is the use of
        ambiguous labelings
        for the purpose of aggregating multiple 1-best parse trees produced by several diverse parsers.
Here, “ambiguous labelings” mean an unlabeled sentence may have multiple parse trees as gold-standard reference, represented by parse forest (see Figure
        1
        ).
The training procedure aims to maximize mixed likelihood of both manually labeled and auto-parsed unlabeled data with ambiguous labelings.
For an unlabeled instance, the model is updated to maximize the probability of its parse forest, instead of a single parse tree in traditional tri-training.
In other words, the model is free to distribute probability mass among the trees in the parse forest to its liking,
as long as the likelihood improves
        []
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Likelihood of the Unlabeled Data
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The auto-parsed unlabeled data with ambiguous labelings is denoted as
         𝒟′={(𝐮i,𝒱i)}i=1M
         , where
         𝐮i
         is an unlabeled sentence, and
         𝒱i
         is the corresponding parse forest.
Then the log likelihood of
         𝒟′
         is:
        </p>
        ℒ(𝒟′;𝐰)=∑i=1Mlog(∑𝐝′∈𝒱ip(𝐝′|𝐮i;𝐰))
        <p class="ltx_p">
         where
         p(𝐝′|𝐮i;𝐰)
         is the conditional probability of
         𝐝′
         given
         𝐮i
         , as defined in Eq. (
         1
         ).
For an unlabeled sentence
         𝐮i
         ,
the probability of its parse forest
         𝒱i
         is the summation of the probabilities of all the parse trees contained in the forest.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Then we can derive the partial derivative of the log likelihood with respect to
         𝐰
         :
        </p>
        ∂⁡ℒ⁢(𝒟′;𝐰)∂⁡𝐰=∑i=1M(∑𝐝′∈𝒱ip~(𝐝′|𝐮i,𝒱i;𝐰)𝐟(𝐮i,𝐝′)-∑𝐝′∈𝒴⁢(𝐮i)p(𝐝′|𝐮i;𝐰)𝐟(𝐮i,𝐝′))

(3)
        <p class="ltx_p">
         where
         p~(𝐝′|𝐮i,𝒱i;𝐰)
         is the probability of
         𝐝′
         under the space constrained by the parse forest
         𝒱i
         .
        </p>
        p~(𝐝′|𝐮i,𝒱i;𝐰)=exp⁡{S⁢c⁢o⁢r⁢e⁢(𝐮i,𝐝′;𝐰)}Z⁢(𝐮i,𝒱i;𝐰)Z(𝐮i,𝒱i;𝐰)=∑𝐝′∈𝒱iexp{Score(𝐮i,𝐝′;𝐰)}
        <p class="ltx_p">
         The second term in Eq. (
         3
         ) is the same with the second term in Eq. (
         2
         ). The first term in Eq. (
         3
         ) can be efficiently computed by running the inside-outside algorithm in the constrained search space
         𝒱i
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Stochastic Gradient Descent (SGD) Training
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We apply L2-norm regularized SGD training to iteratively learn feature weights
         𝐰
         for our CRF-based baseline and semi-supervised parsers.
We follow the implementation in CRFsuite.
         At each step, the algorithm approximates a gradient with a small subset of the training examples,
and then updates the feature weights.
         show that SGD achieves optimal test performance with far fewer iterations than other optimization routines such as L-BFGS.
Moreover, it is very convenient to parallel SGD
since computations among examples in the same batch is mutually independent.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Training with the combined labeled and unlabeled data, the objective is to maximize the mixed likelihood:
        </p>
        ℒ⁢(𝒟;𝒟′)=ℒ⁢(𝒟)+ℒ⁢(𝒟′)
        <p class="ltx_p">
         Since
         𝒟′
         contains much more instances than
         𝒟
         (1.7M vs. 40K for English, and 4M vs. 16K for Chinese),
it is likely that the unlabeled data may overwhelm the labeled data during SGD training.
Therefore, we propose a simple corpus-weighting strategy, as shown in Algorithm
         3.2
         ,
where
         𝒟i,kb
         is the subset of training data used in
         kt⁢h
         update and
         b
         is the batch size;
         ηk
         is the update step, which is adjusted following the simulated annealing procedure
         []
         .
The idea is to use a fraction of training data (
         𝒟i
         ) at each iteration, and do corpus weighting by randomly sampling labeled and unlabeled instances in a certain proportion (
         N1
         vs.
         M1
         ).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Once the feature weights
         𝐰
         are learnt, we can parse the test data to find the optimal parse tree.
        </p>
        𝐝*=arg⁢max𝐝′∈𝒴⁢(𝐱)p(𝐝′|𝐱;𝐰)=arg⁢max𝐝′∈𝒴⁢(𝐱)Score(𝐱,𝐝′;𝐰)
        <p class="ltx_p">
         This can be done with the Viterbi decoding algorithm described in
         in
         O⁢(n3)
         parsing time.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         [tb]
         SGD training with mixed labeled and unlabeled data.
         [1]
Input: Labeled data 𝒟={(𝐱i,𝐝i)}i=1N, and unlabeled data 𝒟′={(𝐮i,𝒱i)}j=1M; Parameters: I, N1, M1, b
Output: 𝐰
Initialization: 𝐰(0)=𝟎, k=0;
[iterations]i=1 I
Randomly select N1 instances from 𝒟 and M1 instances from 𝒟′ to compose a new dataset 𝒟i, and shuffle it.
Traverse 𝒟i: a small batch 𝒟i,kb⊆𝒟i at one step.
 𝐰k+1=𝐰k+ηk⁢1b⁢∇⁡ℒ⁢(𝒟i,kb;𝐰k)
 k=k+1
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Forest Construction with Diverse Parsers
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         To construct parse forests for unlabeled data, we employ three diverse parsers,
i.e., our baseline GParser, a transition-based parser (ZPar
         )
         []
         , and a generative constituent parser (Berkeley Parser
         )
         []
         .
These three parsers are trained on labeled data and then used to parse each unlabeled sentence.
We aggregate the three parsers’ outputs on unlabeled data in different ways and evaluate the effectiveness through experiments.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiments and Analysis
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        To verify the effectiveness of our proposed approach,
we conduct experiments on Penn Treebank (PTB) and Penn Chinese Treebank 5.1 (CTB5).
For English, we follow the popular practice to split data into training (sections 2-21), development (section 22), and test (section 23).
For CTB5, we adopt the data split of
        []
        .
We convert original bracketed structures into dependency structures using Penn2Malt with its default head-finding rules.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        For unlabeled data, we follow
        and use the BLLIP WSJ corpus
        []
        for English and Xinhua portion of Chinese Gigaword Version 2.0 (LDC2009T14)
        []
        for Chinese.
We build a CRF-based bigram part-of-speech (POS) tagger with the features described in
        []
        , and produce POS tags for all train/development/test/unlabeled sets (10-way jackknifing for training sets).
The tagging accuracy on test sets is
        97.3⁢%
        on English and
        94.0⁢%
        on Chinese.
Table
        2
        shows the data statistics.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        We measure parsing performance using the standard unlabeled attachment score (UAS),
excluding punctuation marks.
For significance test, we adopt Dan Bikel’s randomized parsing evaluation comparator
        []
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Parameter Setting
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         When training our CRF-based parsers with SGD, we use the batch size
         b=100
         for all experiments.
We run SGD for
         I=100
         iterations and choose the model that performs best on development data.
For the semi-supervised parsers trained with Algorithm
         3.2
         , we use
         N1=20
         K and
         M1=50
         K for English, and
         N1=15
         K and
         M1=50
         K for Chinese,
based on a few preliminary experiments.
To accelerate the training, we adopt parallelized implementation of SGD and employ 20 threads for each run.
For semi-supervised cases, one iteration takes about 2 hours on an IBM server having 2.0 GHz Intel Xeon CPUs and 72G memory.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Default parameter settings are used for training ZPar and Berkeley Parser.
We run ZPar for 50 iterations, and choose the model that achieves highest accuracy on the development data.
For Berkeley Parser, we use the model after 5 split-merge iterations to avoid over-fitting the training data according to the manual.
The phrase-structure outputs of Berkeley Parser are converted into dependency structures using the same
head-finding rules.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Methodology Study on Development Data
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Using three supervised parsers, we have many options to construct parse forest on unlabeled data.
To examine the effect of different ways for forest construction, we conduct extensive methodology study on development data.
Table
         3
         presents the results.
We divide the systems into three types: 1) supervised single parsers; 2) CRF-based GParser with conventional self/co/tri-training; 3) CRF-based GParser with our approach.
For the latter two cases, we also present the oracle accuracy and averaged head number per word (“Head/Word”) of parse forest when applying different ways to construct forests on development datasets.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         The first major row
         presents performance of the three supervised parsers.
We can see that the three parsers achieve comparable performance on English, but the performance of ZPar is largely inferior on Chinese.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         The second major row
         shows the results when we use single 1-best parse trees on unlabeled data.
When using the outputs of GParser itself (“Unlabeled
         ←
         G”), the experiment reproduces traditional self-training.
The results on both English and Chinese re-confirm that
         self-training may not work for dependency parsing
         , which is
consistent with previous studies
         []
         .
The reason may be that dependency parsers are prone to amplify previous mistakes on unlabeled data during training.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         The next two experiments in the second major row reimplement
         co-training
         , where
another parser’s 1-best results are projected into unlabeled data to help the core parser.
Using unlabeled data with the results of ZPar (“Unlabeled
         ←
         Z”) significantly outperforms the baseline GParser by 0.30% (93.15-82.85) on English. However, the improvement on Chinese is not significant.
Using unlabeled data with the results of Berkeley Parser (“Unlabeled
         ←
         B”) significantly improves parsing accuracy by 0.55% (93.40-92.85) on English and 1.06% (83.34-82.28) on Chinese.
We believe the reason is that being a generative model designed for constituent parsing,
Berkeley Parser is more different from discriminative dependency parsers, and therefore can
provide more divergent syntactic structures.
This kind of syntactic divergence is helpful because it can provide complementary knowledge from a different perspective.
         also show that the diversity of parsers is important for performance improvement when integrating different parsers in the supervised track.
Therefore, we can conclude that
         co-training helps dependency parsing, especially when using a more divergent parser
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         The last experiment in the second major row is known as
         tri-training
         , which only uses unlabeled sentences on which Berkeley Parser and ZPar produce identical outputs (“Unlabeled
         ←
         B=Z”).
We can see that with the verification of two views, the oracle accuracy is much higher than using single parsers (97.52% vs. 92.85% on English, and 95.06% vs. 82.46% on Chinese).
Although using less unlabeled sentences (0.7M for English and 1.2M for Chinese),
         tri-training achieves comparable performance to co-training
         (slightly better on English and slightly worse on Chinese).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         The third major row
         shows the results of the semi-supervised GParser with our proposed approach.
We experiment with different combinations of the 1-best parse trees of the three supervised parsers.
The first three experiments combine 1-best outputs of two parsers
to compose parse forest on unlabeled data.
“Unlabeled
         ←
         B+(Z
         ∩
         G)” means that the parse forest is initialized with the Berkeley parse and augmented with the intersection of dependencies of the 1-best outputs of ZPar and GParser.
In the last setting, the parse forest contains all three 1-best results.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p7">
        <p class="ltx_p">
         When the parse forests of the unlabeled data are the union of the outputs of GParser and ZPar, denoted as “Unlabeled
         ←
         Z+G”,
each word has 1.053 candidate heads on English and 1.136 on Chinese, and
the oracle accuracy is higher than using 1-best outputs of single parsers (94.97% vs. 92.85% on English, 86.66% vs. 82.46% on Chinese).
However, we find that although the parser significantly outperforms the supervised GParser on English,
it does not gain significant improvement over co-training with ZPar (“Unlabeled
         ←
         Z”) on both English and Chinese.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p8">
        <p class="ltx_p">
         Combining the outputs of Berkeley Parser and GParser (“Unlabeled
         ←
         B+G”),
we get higher oracle score (96.37% on English and 89.72% on Chinese) and higher syntactic divergence (1.085 candidate heads per word on English, and 1.188 on Chinese) than “Unlabeled
         ←
         Z+G”, which verifies our earlier discussion that Berkeley Parser produces more different structures than ZPar.
However, it leads to slightly worse accuracy than co-training with Berkeley Parser (“Unlabeled
         ←
         B”).
This indicates that adding the outputs of GParser itself does not help the model.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p9">
        <p class="ltx_p">
         Combining the outputs of Berkeley Parser and ZPar (“Unlabeled
         ←
         B+Z”),
we get the best performance on English,
which is also significantly better than both co-training (“Unlabeled
         ←
         B”) and tri-training (“Unlabeled
         ←
         B=Z”) on both English and Chinese.
This demonstrates that
         our proposed approach can better exploit unlabeled data than traditional self/co/tri-training
         . More analysis and discussions are in Section
         4.4
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p10">
        <p class="ltx_p">
         During experimental trials, we find that “Unlabeled
         ←
         B+(Z
         ∩
         G)” can further boost performance on Chinese. A possible explanation is that by using the intersection of the outputs of GParser and ZPar, the size of the parse forest is better controlled, which is helpful considering that ZPar performs worse on this data than both Berkeley Parser and GParser.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p11">
        <p class="ltx_p">
         Adding the output of GParser itself (“Unlabeled
         ←
         B+Z+G”) leads to accuracy drop,
although the oracle score is higher (96.95% on English and 91.50% on Chinese) than “Unlabeled
         ←
         B+Z”.
We suspect the reason is that the model is likely to distribute the probability mass to these parse trees produced by itself instead of those by Berkeley Parser or ZPar under this setting.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p12">
        <p class="ltx_p">
         In summary, we can conclude that
         our proposed ambiguity-aware ensemble training is significantly better than both the supervised approaches and the semi-supervised approaches that use 1-best parse trees
         .
Appropriately composing the forest parse, our approach outperforms the best results of co-training or tri-training by 0.28% (93.78-93.50) on English and 0.92% (84.26-83.34) on Chinese.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Comparison with Previous Work
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We adopt the best settings on development data for semi-supervised GParser with our proposed approach, and make comparison with
previous results on test data.
Table
         4
         shows the results.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         The first major row lists several state-of-the-art supervised methods.
         propose a second-order graph-based parser, but use a smaller feature set than our work.
         propose a third-order graph-based parser.
         explore higher-order features for graph-based dependency parsing,
and adopt beam search for fast decoding.
         propose a feature-rich transition-based parser.
All work in the second major row adopts semi-supervised methods.
The results show that our approach achieves comparable accuracy with most previous semi-supervised methods.
Both
         and
         adopt the higher-order parsing model of
         , and
         also incorporate word cluster features proposed by
         in their system.
We expect our approach may achieve higher performance with such enhancements, which we leave for future work.
Moreover, our method may be combined with other semi-supervised approaches,
since they are orthogonal in methodology and utilize unlabeled data from different perspectives.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         Table
         5
         make comparisons with previous results on Chinese test data.
         and
         use joint models for POS tagging and dependency parsing, significantly outperforming their pipeline counterparts.
Our approach can be combined with their work to utilize unlabeled data to improve both POS tagging and parsing simultaneously.
Our work achieves comparable accuracy with
         , although they adopt the higher-order model of
         . Again, our method may be combined with their work to achieve higher performance.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Analysis
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         To better understand the effectiveness of our proposed approach, we make detailed analysis using the semi-supervised GParser with “Unlabeled
         ←
         B+Z” on English datasets.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p2">
        <p class="ltx_p">
         Contribution of unlabeled data with regard to syntactic divergence:
         We divide the unlabeled data into three sets according to the divergence of the 1-best outputs of Berkeley Parser and ZPar.
The first set contains those sentences that the two parsers produce identical parse trees, denoted by “consistent”, which corresponds to the setting for tri-training.
Other sentences are split into two sets according to averaged number of heads per word in parse forests, denoted by “low divergence” and “high divergence” respectively.
Then we train semi-supervised GParser using the three sets of unlabeled data.
Table
         6
         illustrates the results and statistics.
We can see that unlabeled data with identical outputs from Berkeley Parser and ZPar tends to be short sentences (18.25 words per sentence on average).
Results show all the three sets of unlabeled data can help the parser.
Especially, the unlabeled data with highly divergent structures leads to slightly higher improvement.
This demonstrates that
         our approach can better exploit unlabeled data on which parsers of different views produce divergent structures
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p3">
        <p class="ltx_p">
         Impact of unlabeled data size:
         To understand how our approach performs with regards to the unlabeled data size,
we train semi-supervised GParser with different sizes of unlabeled data.
Fig.
         3
         shows the accuracy curve on the test set.
We can see that the parser consistently achieves higher accuracy with more unlabeled data,
demonstrating the effectiveness of our approach. We expect that our approach has potential to achieve higher accuracy with more additional data.
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
        Our work is originally inspired by the work of
        .
They first apply the idea of ambiguous labelings to multilingual parser transfer in the unsupervised parsing field, which
aims to build a dependency parser for a resource-poor target language by making use of source-language treebanks.
Different from their work, we explore the idea for semi-supervised dependency parsing where a certain amount of labeled training data is available.
Moreover, we for the first time build a state-of-the-art CRF-based dependency parser and conduct in-depth comparisons with previous methods.
Similar ideas of learning with ambiguous labelings are previously explored for classification
        []
        and sequence labeling problems
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Our work is also related with the parser ensemble approaches such as stacked learning and re-parsing in the supervised track.
Stacked learning uses one parser’s outputs as guide features for another parser, leading to improved performance
        []
        .
Re-parsing merges the outputs of several parsers into a dependency graph, and then apply Viterbi decoding to find a better tree
        []
        .
One possible drawback of parser ensemble is that several parsers are required to parse the same sentence during the test phase.
Moreover, our approach can benefit from these methods in that we can get parse forests of higher quality on unlabeled data
        []
        .
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
