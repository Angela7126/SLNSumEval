<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   POS induction with distributional and morphological informationusing a distance-dependent Chinese restaurant process.
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
       We present a new approach to inducing the syntactic categories of words, combining their distributional and morphological properties in a joint nonparametric Bayesian model based on the distance-dependent Chinese Restaurant Process.
The prior distribution over word clusterings uses a log-linear model of morphological similarity;
the likelihood function is the probability of generating vector word embeddings. The weights of the morphology model are learned jointly while inducing part-of-speech clusters,
encouraging them to cohere with the distributional features. The resulting algorithm outperforms competitive alternatives on English POS induction.
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
        The morphosyntactic function of words is reflected in two ways: their distributional properties, and their morphological structure. Each information source has its own advantages and disadvantages. Distributional similarity varies smoothly with syntactic function, so that words with similar syntactic functions should have similar distributional properties. In contrast, there can be multiple paradigms for a single morphological inflection (such as past tense in English). But accurate computation of distributional similarity requires large amounts of data, which may not be available for rare words; morphological rules can be applied to any word regardless of how often it appears.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        These observations suggest that a general approach to the induction of syntactic categories should leverage both distributional and morphological features
        [9, 7]
        . But these features are difficult to combine because of their disparate representations. Distributional information is typically represented in numerical vectors, and recent work has demonstrated the utility of continuous vector representations, or “embeddings”
        [16, 15, 13, 24]
        . In contrast, morphology is often represented in terms of sparse, discrete features (such as morphemes), or via pairwise measures such as string edit distance. Moreover, the mapping between a surface form and morphology is complex and nonlinear, so that simple metrics such as edit distance will only weakly approximate morphological similarity.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper we present a new approach for inducing part-of-speech (POS) classes, combining morphological and distributional information in a non-parametric Bayesian generative model based on the
        distance-dependent Chinese restaurant process
        (ddCRP; Blei and Frazier, 2011)
        .
In the ddCRP, each data point (word type) selects another point to “follow”; this chain of following links corresponds to a partition of the data points into clusters. The probability of word
        w1
        following
        w2
        depends on two factors:
1) the
        distributional
        similarity between all words in the proposed partition containing
        w1
        and
        w2
        , which is encoded using a Gaussian likelihood function over the word embeddings; and
2) the
        morphological
        similarity between
        w1
        and
        w2
        , which
acts as a prior distribution on the induced clustering.
We use a log-linear model to capture suffix similarities between words, and learn the feature weights by iterating between sampling and weight learning.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We apply our model to the English section of the the Multext-East corpus
        [11]
        in order to evaluate both against the coarse-grained and fine-grained tags, where the fine-grained tags encode detailed morphological classes. We find that our model effectively combines morphological features with distributional similarity, outperforming comparable alternative approaches.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Unsupervised POS tagging has a long history in NLP. This paper focuses on the POS induction problem (i.e., no tag dictionary is available), and here we limit our discussion to very recent systems. A review and comparison of older systems is provided by
        Christodoulopoulos et al. (2010)
        , who found that imposing a one-tag-per-word-type constraint to reduce model flexibility tended to improve system performance; like other recent systems, we impose that constraint here.
Recent work also shows that the combination of morphological and distributional information yields the best results, especially cross-linguistically
        [9, 3]
        . Since then, most systems have incorporated morphology in some way, whether as an initial step to obtain prototypes for clusters
        [1]
        , or as features in a generative model
        [14, 8, 21]
        , or a representation-learning algorithm
        [27]
        . Several of these systems use a small fixed set of orthographic and/or suffix features, sometimes obtained from an unsupervised morphological segmentation system
        [1, 14, 8, 27]
        . Blunsom and Cohn’s
        [6]
        model learns an
        n
        -gram character model over the words in each cluster; we learn a log-linear model, which can incorporate arbitrary features.
        Berg-Kirkpatrick et al. (2010)
        also include a log-linear model of morphology in POS induction, but they use morphology in the likelihood term of a parametric sequence model, thereby encouraging all elements that share a tag to have the same morphological features. In contrast, we use
        pairwise morphological similarity
        as a prior in a non-parametric clustering model. This means that the membership of a word in a cluster requires only morphological similarity to some other element in the cluster, not to the cluster centroid; which may be more appropriate for languages with multiple morphological paradigms. Another difference is that our non-parametric formulation makes it unnecessary to know the number of tags in advance.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Distance-dependent CRP
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The ddCRP
        [5]
        is an extension of the CRP; like the CRP, it defines a distribution over partitions (“table assignments”) of data points (“customers”).
Whereas in the regular CRP each customer chooses a table with probability proportional to the number of customers already sitting there, in the ddCRP each customer chooses another
        customer
        to follow, and sits at the same table with that customer.
By identifying the connected components in this graph, the ddCRP equivalently defines a prior over clusterings.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        If
        ci
        is the index of the customer followed by customer
        i
        , then the ddCRP prior can be written
       </p>
       <table class="ltx_equationgroup" id="S3.E1">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E1X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(ci=j)∝{f⁢(di⁢j)if ⁢i≠jαif ⁢i=j,
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equationgroup">
           (1)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        di⁢j
        is the distance between customers
        i
        and
        j
        and
        f
        is a decay function. A ddCRP is
        sequential
        if customers can only follow previous customers, i.e.,
        di⁢j=∞
        when
        i&gt;j
        and
        f⁢(∞)=0
        . In this case, if
        di⁢j=1
        for all
        i&lt;j
        then the ddCRP reduces to the CRP.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Separating the distance and decay function makes sense for “natural” distances (e.g., the number of words between word
        i
        and
        j
        in a document, or the time between two events), but they can also be collapsed into a single similarity function. We wish to assign higher similarities to pairs of words that share meaningful suffixes. Because we do not know which suffixes are meaningful
        a priori
        , we use a maximum entropy model whose features include all suffixes up to length three that are shared by at least one pair of words. Our prior is then:
       </p>
       <table class="ltx_equationgroup" id="S3.E2">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E2X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(ci=j|𝐰,α)∝{e𝐰𝖳⁢𝐠⁢(i,j)if ⁢i≠jαif ⁢i=j,
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equationgroup">
           (2)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        gs⁢(i,j)
        is 1 if suffix
        s
        is shared by
        i
        th and
        j
        th words, and 0 otherwise.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        We can create an infinite mixture model by combining the ddCRP prior with a likelihood function defining the probability of the data given the cluster assignments. Since we are using continuous-valued vectors (word embeddings) to represent the distributional characteristics of words,
we use a multivariate Gaussian likelihood. We will marginalize over the mean
        μ
        and covariance
        Σ
        of each cluster, which in turn are drawn from Gaussian and inverse-Wishart (IW) priors respectively:
       </p>
       Σ∼IW(ν0,Λ0)μ∼𝒩(μ0,/κ0Σ)

(3)
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        The full model is then:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(𝐗,
         </td>
         <td class="ltx_td ltx_align_left">
          𝐜,𝝁,𝚺|Θ,𝐰,α)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (4)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          =
         </td>
         <td class="ltx_td ltx_align_left">
          ∏k=1KP(Σk|Θ)p(μk|Σk,Θ)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S3.Ex2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          ×∏i=1n(P(ci|𝐰,α)P(𝐱i|μzi,Σzi)),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        Θ
        are the hyperparameters for
        (𝝁,𝚺)
        and
        zi
        is the (implicit) cluster assignment of the
        i
        th word
        𝐱i
        .
With a CRP prior, this model would be an infinite Gaussian mixture model (IGMM; Rasmussen, 2000)
        , and we will use the IGMM as a baseline.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Inference
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The Gibbs sampler for the ddCRP integrates over
the Gaussian parameters,
sampling only follower variables. At each step, the follower link
        ci
        for a single customer
        i
        is sampled, which can implicitly shift the entire block of
        n
        customers
        fol⁢(i)
        who follow
        i
        into a new cluster. Since we marginalize over the cluster parameters, computing
        P(ci=j)
        requires computing the likelihood
        P(fol(i),𝐗j|Θ)
        , where
        𝐗j
        are the
        k
        customers already clustered with
        j
        .
However, if we do
        not
        merge
        fol⁢(i)
        with
        𝐗j
        , then we have
        P(𝐗j|Θ)
        in the overall joint probability. Therefore, we can decompose
        P(fol(i),𝐗j|Θ)=P(fol(i)|𝐗j,Θ)P(𝐗j|Θ)
        and need only compute the change in likelihood due to merging in
        fol⁢(i)
        :
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex3">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(fol(i)|𝐗j,Θ)
         </td>
         <td class="ltx_td ltx_align_left">
          =π-n⁢d/2⁢κkd/2⁢|Λk|νk/2κn+kd/2⁢|Λn+k|νn+k/2
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E5">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          ×∏i=1dΓ⁢(νn+k+1-i2)Γ⁢(νk+1-i2),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (5)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where the hyperparameters are updated as
        κn=κ0+n
        ,
        νn=ν0+n
        , and
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx3">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E6">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          μn
         </td>
         <td class="ltx_td ltx_align_left">
          =κ0⁢μ0+x¯κ0+n
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (6)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E7">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          Λn
         </td>
         <td class="ltx_td ltx_align_left">
          =Λ0+Q+κ0⁢μ𝟎⁢μ𝟎T-κn⁢μn⁢μnT,
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (7)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        Q=∑i=1n𝐱i⁢𝐱iT
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Combining this likelihood term with the prior, the probability of customer
        i
        following
        j
        is
       </p>
       P(ci=j|𝐗,Θ,𝐰,α)∝P(fol(i)|𝐗j,Θ)P(ci=j|𝐰,α).

(8)
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Our non-sequential ddCRP introduces cycles into the follower structure, which are handled in the sampler as described by
        Socher et al. (2011)
        . Also,
the block of customers being moved around can potentially be very large, which makes it easy for the likelihood term to swamp the prior. In practice we found that introducing an additional parameter
        a
        (used to exponentiate the prior) improved results—although we report results without this exponent as well.
This technique
was also used by
        Titov and Klementiev (2012)
        and
        Elsner et al. (2012)
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Inference also includes optimizing the feature weights for the log-linear model in the ddCRP prior
        [23]
        . We
interleave L-BFGS optimization within sampling, as in Monte Carlo Expectation-Maximization (Wei and Tanner, 1990)
        .
We do not apply the exponentiation parameter
        a
        when training the weights because this procedure affects the follower structure only, and we do not have to worry about the magnitude of the likelihood.
Before the first iteration we initialize the follower structure: for each word, we choose randomly a word to follow from amongst those with the longest shared suffix of up to 3 characters.
The number of clusters starts around 750, but decreases
substantially after the first sampling iteration.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments
      </h2>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Data
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         For our experiments we used the English word embeddings from the Polyglot project
         [2]
         , which provides embeddings trained on Wikipedia texts for 100,000 of the most frequent words in many languages.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p2">
        <p class="ltx_p">
         We evaluate on the English part of the Multext-East (MTE) corpus
         [11]
         ,
which provides both coarse-grained and fine-grained POS labels for the text of Orwell’s “1984”.
Coarse labels consist of 11 main word classes, while the fine-grained tags (104 for English) are sequences of detailed morphological attributes.
Some of these attributes are not well-attested in English (e.g. gender) and some are mostly distinguishable via semantic analysis (e.g. 1st and 2nd person verbs).
Many tags are assigned only to one or a few words.
Scores for the fine-grained tags will be lower for these reasons, but we argue below that they are still informative.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p3">
        <p class="ltx_p">
         Since Wikipedia and MTE are from different domains
their lexicons do not fully overlap;
we take the intersection of these two sets for training and evaluation.
Table
         1
         shows corpus statistics.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Evaluation
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         With a few exceptions
         [4, 25]
         , POS induction systems normally require the user to specify the number of desired clusters, and the systems are evaluated with that number set to the number of tags in the gold standard.
For corpora such as MTE with both fine-grained and coarse-grained tages, previous evaluations have scored against the coarse-grained tags. Though coarse-grained tags have their place
         [17]
         , in many cases the distributional and morphological distinctions between words are more closely aligned with the fine-grained tagsets, which typically distinguish between verb tenses, noun number and gender, and adjectival scale (comparative, superlative, etc.), so we feel that the evaluation against fine-grained tagset is more relevant here.
For better comparison with previous work, we also evaluate against the coarse-grained tags; however, these numbers are not strictly comparable to other scores reported on MTE because we are only able to train and evaluate on the subset of words that also have Polyglot embeddings. To provide some measure
of the difficulty of the task, we report baseline scores using K-means clustering, which is relatively strong baseline in this task
         [8]
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         There are several measures commonly used for unsupervised POS induction.
We report greedy one-to-one mapping accuracy (1-1)
         [12]
         and the information-theoretic score V-measure (V-m), which also varies from 0 to 100%
         [20]
         .
In previous work it has been common to also report many-to-one (m-1) mapping but this measure is particularly sensitive to the number of induced clusters (more clusters yield higher scores), which is variable for our models.
V-m can be somewhat sensitive to the number of clusters
         [19]
         but much less so than m-1
         [7]
         .
With different number of induced and gold standard clusters the 1-1 measure suffers because some induced clusters cannot be mapped to gold clusters or vice versa.
However, almost half the gold standard clusters in MTE contain just a few words and we do not expect our model to be able to learn them anyway, so the 1-1 measure is still useful for telling us how well the model learns the bigger and more distinguishable classes.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p3">
        <p class="ltx_p">
         In unsupervised POS induction it is standard to report accuracy on tokens even when the model itself works on types.
Here we report also type-based measures because these can reveal differences in model behavior even when token-based measures are similar.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        Experimental setup
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         For baselines we use K-means and the IGMM, which both only learn from the word embeddings.
The CRP prior in the IGMM has one hyperparameter (the concentration parameter
         α
         ); we report results for
         α=5
         and
         20
         .
Both the IGMM and ddCRP have four hyperparameters controlling the prior over the Gaussian cluster parameters:
         Λ0
         ,
         μ0
         ,
         ν0
         and
         κ0
         .
We set the prior scale matrix
         Λ0
         by using the average covariance from a K-means run with
         K=200
         .
When setting the average covariance as the expected value of the IW distribution the suitable scale matrix can be computed as
         Λ0=E⁢[X]⁢(ν0-d-1)
         ,
where
         ν0
         is the prior degrees of freedom (which we set to
         d
         + 10) and
         d
         is the data dimensionality (64 for the Polyglot embeddings).
We set the prior mean
         μ0
         equal to the sample mean of the data and
         κ0
         to 0.01.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P3.p2">
        <p class="ltx_p">
         We experiment with three different priors for the ddCRP model.
All our ddCRP models are non-sequential
         [22]
         , allowing cycles to be formed.
The simplest model,
         ddCRP uniform
         , uses a uniform prior that sets the distance between any two words equal to one.
         The second model,
         ddCRP learned
         , uses the log-linear prior with weights learned between each two Gibbs iterations as explained in section
         4
         .
The final model,
         ddCRP exp
         , adds the prior exponentiation.
The
         α
         parameter for the ddCRP is set to 1 in all experiments.
For
         ddCRP exp
         , we report results with the exponent
         a
         set to 5.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P4">
       <h3 class="ltx_title ltx_title_paragraph">
        Results and discussion
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         Table
         2
         presents all results.
Each number is an average of 5 experiments with different random initializations.
For each evaluation setting we provide two sets of scores—first are the 1-1 and V-m scores for the given model, second are the comparable scores for K-means run with the same number of clusters as induced by the non-parametric model.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p2">
        <p class="ltx_p">
         These results show that all non-parametric models perform better than K-means, which is a strong baseline in this task
         [8]
         .
The poor performace of K-means can be explained by the fact that it tends to find clusters of relatively equal size, although the POS clusters are rarely of similar size.
The common noun singular class is by far the largest in English, containing roughly a quarter of the word types.
Non-parametric models are able to produce cluster of different sizes when the evidence indicates so, and this is clearly the case here.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p3">
        <p class="ltx_p">
         From the token-based evaluation it is hard to say which IGMM hyperparameter value is better even though the number of clusters induced differs by a factor of 2.
The type-base evaluation, however, clearly prefers the smaller value with fewer clusters.
Similar effects can be seen when comparing IGMM and ddCRP uniform.
We expected these two models perform on the same level, and their token-based scores are similar,
but on the type-based evaluation the ddCRP is clearly superior.
The difference could be due to the non-sequentiality, or becuase the samplers are different—IGMM enabling resampling only one item at a time, ddCRP performing blocked sampling.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p4">
        <p class="ltx_p">
         Further we can see that the ddCRP uniform and learned perform roughly the same.
Although the prior in those models is different they work mainly using the the likelihood.
The ddCRP with learned prior does produce nice follower structures within each cluster but the prior is in general too weak compared to the likelihood to influence the clustering decisions.
Exponentiating
the prior reduces the number of induced clusters and improves
results, as it can change the cluster assignment for some words
where the likelihood strongly prefers one cluster but the prior clearly indicates another.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p5">
        <p class="ltx_p">
         The last column shows the token-based evaluation against the coarse-grained tagset.
This is the most common evaluation framework used previously in the literature.
Although our scores are not directly comparable with the previous results, our V-m scores are
similar to
the best published 60.5
         [7]
         and 66.7
         [21]
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p6">
        <p class="ltx_p">
         In preliminary experiments, we found that directly applying the
best-performing English model to other languages is not effective.
Different languages may require different parametrizations of the model.
Further study is also needed to verify that word embeddings effectively
capture syntax across languages, and to determine the amount of unlabeled
text necessary to learn good embeddings.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
