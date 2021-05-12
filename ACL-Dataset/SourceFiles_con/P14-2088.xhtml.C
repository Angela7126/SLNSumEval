<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Fast Easy Unsupervised Domain Adaptationwith Marginalized Structured Dropout.
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
       Unsupervised domain adaptation often relies on transforming the instance representation. However, most such approaches are designed for bag-of-words models, and ignore the structured features present in many problems in NLP. We propose a new technique called
       marginalized structured dropout
       , which exploits feature structure to obtain a remarkably simple and efficient feature projection. Applied to the task of fine-grained part-of-speech tagging on a dataset of historical Portuguese, marginalized structured dropout yields state-of-the-art accuracy while increasing speed by more than an order-of-magnitude over previous work.
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
        Unsupervised domain adaptation is a fundamental problem for natural language processing, as we hope to apply our systems to datasets unlike those for which we have annotations. This is particularly relevant as labeled datasets become stale in comparison with rapidly evolving social media writing styles
        [8]
        , and as there is increasing interest in natural language processing for historical texts
        [23]
        . While a number of different approaches for domain adaptation have been proposed
        [21, 26]
        , they tend to emphasize bag-of-words features for classification tasks such as sentiment analysis. Consequently, many approaches rely on each instance having a relatively large number of active features, and fail to exploit the structured feature spaces that characterize syntactic tasks such as sequence labeling and parsing
        [25]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        As we will show, substantial efficiency improvements can be obtained by designing domain adaptation methods for learning in structured feature spaces. We build on work from the deep learning community, in which
        denoising autoencoders
        are trained to remove synthetic noise from the observed instances
        [11]
        . By using the autoencoder to transform the original feature space, one may obtain a representation that is less dependent on any individual feature, and therefore more robust across domains.
        Chen et al. (2012)
        showed that such autoencoders can be learned even as the noising process is analytically marginalized; the idea is similar in spirit to feature noising
        [29]
        . While the marginalized denoising autoencoder (mDA) is considerably faster than the original denoising autoencoder, it requires solving a system of equations that can grow very large, as realistic NLP tasks can involve
        105
        or more features.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper we investigate noising functions that are explicitly designed for
        structured feature spaces
        , which are common in NLP. For example, in part-of-speech tagging,
        Toutanova et al. (2003)
        define several feature “templates”: the current word, the previous word, the suffix of the current word, and so on. For each feature template, there are thousands of binary features. To exploit this structure, we propose two alternative noising techniques: (1)
        feature scrambling
        , which randomly chooses a feature template and randomly selects an alternative value within the template, and (2)
        structured dropout
        , which randomly eliminates all but a single feature template. We show how it is possible to marginalize over both types of noise, and find that the solution for structured dropout is substantially simpler and more efficient than the mDA approach of
        Chen et al. (2012)
        , which does not consider feature structure.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We apply these ideas to fine-grained part-of-speech tagging on a dataset of Portuguese texts from the years 1502 to 1836
        [9]
        , training on recent texts and evaluating on older documents. Both structure-aware domain adaptation algorithms perform as well as standard dropout — and better than the well-known structural correspondence learning (SCL) algorithm
        [1]
        — but structured dropout is more than an order-of-magnitude faster. As a secondary contribution of this paper, we demonstrate the applicability of unsupervised domain adaptation to the syntactic analysis of historical texts.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Model
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        In this section we first briefly describe the denoising autoencoder
        [12]
        , its application to domain adaptation, and the analytic marginalization of noise
        [4]
        . Then we present three versions of marginalized denoising autoencoders (mDA) by incorporating different types of noise, including two new noising processes that are designed for structured features.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Denoising Autoencoders
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Assume instances
         𝐱1,…,𝐱n
         , which are drawn from both the source and target domains. We will “corrupt” these instances by adding different types of noise, and denote the corrupted version of
         𝐱i
         by
         𝐱~i
         . Single-layer denoising autoencoders reconstruct the corrupted inputs with a projection matrix
         𝐖
         :
         ℝd→ℝd
         ,
which is estimated by minimizing the squared reconstruction loss
        </p>
        ℒ=12⁢∑i=1n||𝐱i-𝐖⁢𝐱~i||2.

(1)
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         If we write
         𝐗=[𝐱1,…,𝐱n]∈ℝd×n
         , and we write its corrupted version
         𝐗~
         , then the loss in (
         1
         ) can be written as
        </p>
        ℒ⁢(𝐖)=12⁢n⁢t⁢r⁢[(𝐗-𝐖⁢𝐗~)⊤⁢(𝐗-𝐖⁢𝐗~)].

(2)
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         In this case, we have the well-known closed-form solution for this ordinary least square problem:
        </p>
        𝐖=𝐏𝐐-1,

(3)
        <p class="ltx_p">
         where
         𝐐=𝐗~⁢𝐗~⊤
         and
         𝐏=𝐗⁢𝐗~⊤
         . After obtaining the weight matrix
         𝐖
         , we can insert nonlinearity into the output of the denoiser, such as
         tanh⁡(𝐖𝐗)
         . It is also possible to apply stacking, by passing this vector through another autoencoder
         [4]
         . In pilot experiments, this slowed down estimation and had little effect on accuracy, so we did not include it.
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         High-dimensional setting
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          Structured prediction tasks often have much more features than simple bag-of-words representation, and performance relies on the rare features. In a naive implementation of the denoising approach, both
          𝐏
          and
          𝐐
          will be dense matrices with dimensionality
          d×d
          , which would be roughly
          1011
          elements in our experiments.
To solve this problem,
          Chen et al. (2012)
          propose to use a set of pivot features, and train the autoencoder to reconstruct the pivots from the full set of features. Specifically,
the corrupted input is divided to
          S
          subsets
          𝐱~i=[(𝐱~)i1⊤,…,(𝐱~)iS⊤]⊤
          .
We obtain a projection matrix
          𝐖s
          for each subset by reconstructing the pivot features from the features in this subset; we can then use the sum of all reconstructions as the new features,
          tanh⁡(∑s=1S𝐖s⁢𝐗s)
          .
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Marginalized Denoising Autoencoders
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          In the standard denoising autoencoder, we need to generate multiple versions of the corrupted data
          𝐗~
          to reduce the
variance of the solution
          [12]
          . But
          Chen et al. (2012)
          show that it is possible to marginalize over the noise, analytically computing expectations of both
          𝐏
          and
          𝐐
          , and computing
         </p>
         𝐖=E⁢[𝐏]⁢E⁢[𝐐]-1,

(4)
         <p class="ltx_p">
          where
          E⁢[𝐏]=∑i=1nE⁢[𝐱i⁢𝐱~i⊤]
          and
          E⁢[𝐐]=∑i=1nE⁢[𝐱~i⁢𝐱~i⊤]
          . This is equivalent to
corrupting the data
          m→∞
          times. The computation of these expectations depends on the type of noise.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Noise distributions
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Chen et al. (2012)
         used dropout noise for domain adaptation, which we briefly review. We then describe two novel types of noise that are designed for structured feature spaces, and explain how they can be marginalized to efficiently compute
         𝐖
         .
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Dropout noise
        </h4>
        <div class="ltx_para" id="S2.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          In dropout noise, each feature is set to zero with probability
          p&gt;0
          .
If we define the scatter matrix of the uncorrupted input as
          𝐒=𝐗𝐗⊤
          , the solutions under dropout noise are
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P1.p2">
         E⁢[𝐐]α,β={(1-p)2⁢𝐒α,βif ⁢α≠β(1-p)⁢𝐒α,βif ⁢α=β,

(5)
         <p class="ltx_p">
          and
         </p>
         E⁢[𝐏]α,β=(1-p)⁢𝐒α,β,

(6)
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P1.p3">
         <p class="ltx_p">
          where
          α
          and
          β
          index two features. The form of these solutions means that computing
          𝐖
          requires solving a system of equations equal to the number of features (in the naive implementation), or several smaller systems of equations (in the high-dimensional version). Note also that
          p
          is a tunable parameter for this type of noise.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Structured dropout noise
        </h4>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          In many NLP settings, we have several feature templates, such as previous-word, middle-word, next-word, etc, with only one feature per template firing on any token. We can exploit this structure by using an alternative dropout scheme: for each token, choose exactly one feature template to keep, and zero out all other features that consider this token (transition feature templates such as
          ⟨yt,yt-1⟩
          are not considered for dropout). Assuming we have
          K
          feature templates, this noise leads to very simple solutions for the marginalized matrices
          E⁢[𝐏]
          and
          E⁢[𝐐]
          ,
         </p>
         E⁢[𝐐]α,β={0if ⁢α≠β1K⁢𝐒α,βif ⁢α=β

(7)
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p2">
         E⁢[𝐏]α,β=1K⁢𝐒α,β,

(8)
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p3">
         <p class="ltx_p">
          For
          E⁢[𝐏]
          , we obtain a scaled version of the scatter matrix, because in each instance
          𝐱~
          , there is exactly a
          1/K
          chance that each individual feature survives dropout.
          E⁢[𝐐]
          is diagonal, because for any off-diagonal entry
          E⁢[𝐐]α,β
          , at least one of
          α
          and
          β
          will drop out for every instance. We can therefore view the projection matrix
          𝐖
          as a row-normalized version of the scatter matrix
          𝐒
          . Put another way, the contribution of
          β
          to the reconstruction for
          α
          is equal to the co-occurence count of
          α
          and
          β
          , divided by the count of
          β
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p4">
         <p class="ltx_p">
          Unlike standard dropout, there are no free hyper-parameters to tune for structured dropout. Since
          E⁢[𝐐]
          is a diagonal matrix, we eliminate the cost of matrix inversion (or of solving a system of linear equations). Moreover, to extend mDA for high dimensional data, we no longer need to divide the corrupted input
          𝐱~
          to several subsets.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p5">
         <p class="ltx_p">
          For intuition, consider standard feature dropout with
          p=K-1K
          . This will look very similar to structured dropout: the matrix
          E⁢[𝐏]
          is identical, and
          E⁢[𝐐]
          has off-diagonal elements which are scaled by
          (1-p)2
          , which goes to zero as
          K
          is large. However, by including these elements, standard dropout is considerably slower, as we show in our experiments.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS2.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Scrambling noise
        </h4>
        <div class="ltx_para" id="S2.SS2.SSS0.P3.p1">
         <p class="ltx_p">
          A third alternative is to “scramble” the features by randomly selecting alternative features within each template. For a feature
          α
          belonging to a template
          F
          , with probability
          p
          we will
draw a noise feature
          β
          also belonging to
          F
          , according to some distribution
          q
          . In this work, we use an uniform distribution,
in which
          qβ=1|F|
          . However, the below solutions will also hold for other scrambling distributions, such as mean-preserving distributions.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P3.p2">
         <p class="ltx_p">
          Again, it is possible to analytically marginalize over this noise. Recall that
          E⁢[𝐐]=∑i=1nE⁢[𝐱~i⁢𝐱~i⊤]
          . An off-diagonal entry in the
matrix
          𝐱~⁢𝐱~⊤
          which involves features
          α
          and
          β
          belonging to different templates (
          Fα≠Fβ
          ) can
take four different values (
          𝐱i,α
          denotes feature
          α
          in
          𝐱i
          ):
         </p>
         <ul class="ltx_itemize" id="I1">
          <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i1.p1">
            <p class="ltx_p">
             𝐱i,α⁢𝐱i,β
             if both features are unchanged, which happens with probability
             (1-p)2
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
             1
             if both features are chosen as noise features, which happens with probability
             p2⁢qα⁢qβ
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i3.p1">
            <p class="ltx_p">
             𝐱i,α
             or
             𝐱i,β
             if one feature is unchanged and the other one is chosen as the noise feature, which happens with probability
             p⁢(1-p)⁢qβ
             or
             p⁢(1-p)⁢qα
             .
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P3.p3">
         <p class="ltx_p">
          The diagonal entries take the first two values above, with probability
          1-p
          and
          p⁢qα
          respectively. Other entries will be all
zero (only one feature belonging to the same template will fire in
          𝐱i
          ). We can use similar reasoning to compute the expectation of
          𝐏
          . With probability
          (1-p)
          , the original features are preserved, and we add the outer-product
          𝐱i⁢𝐱i⊤
          ; with probability
          p
          , we add the outer-product
          𝐱i⁢q⊤
          . Therefore
          E⁢[𝐏]
          can be computed as the sum of these terms.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We compare these methods on historical Portuguese part-of-speech tagging, creating domains over historical epochs.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Experiment setup
       </h3>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Datasets
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          We use the Tycho Brahe corpus to evaluate our methods. The corpus contains a total of 1,480,528 manually tagged words. It uses a set of 383 tags and is composed of various texts from historical Portuguese, from 1502 to 1836. We divide the texts into fifty-year periods to create different domains. Table
          1
          presents some statistics of the datasets. We hold out 5% of data as development data to tune parameters. The two most recent domains (1800-1849 and 1750-1849) are treated as source domains, and the other domains are target domains. This scenario is motivated by training a tagger on a modern newstext corpus and applying it to historical documents.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         CRF tagger
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          We use a conditional random field tagger, choosing CRFsuite because it supports arbitrary real valued features
          [20]
          , with SGD optimization. Following the work of
          Nogueira Dos Santos et al. (2008)
          on this dataset, we apply the feature set of
          Ratnaparkhi (1996)
          . There are
          16
          feature templates and
          372,902
          features in total.
Following
          Blitzer et al. (2006)
          , we consider pivot features that appear more than
          50
          times in all the domains. This
leads to a total of
          1572
          pivot features in our experiments.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Methods
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P3.p1">
         <p class="ltx_p">
          We compare mDA with three alternative approaches. We refer to
          baseline
          as training a CRF tagger
on the source domain and testing on the target domain with only base features. We also include
          PCA
          to project
the entire dataset onto a low-dimensional sub-space (while still including the original features). Finally, we compare against Structural Correspondence Learning
(
          SCL
          ; Blitzer et al., 2006)
          , another feature learning algorithm. In all cases, we include the entire dataset to compute the feature projections; we also conducted experiments using only the test and training data for feature projections, with very similar results.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P4">
        <h4 class="ltx_title ltx_title_paragraph">
         Parameters
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P4.p1">
         <p class="ltx_p">
          All the hyper-parameters are decided with our development data on the training set. We try different low dimension
          K
          from
          10
          to
          2000
          for PCA. Following
          Blitzer (2008)
          we perform feature centering/normalization, as well as rescaling for SCL. The best parameters for SCL are dimensionality
          K=25
          and rescale factor
          α=5
          , which are the same as in the original paper. For mDA, the best corruption level is
          p=0.9
          for dropout noise, and
          p=0.1
          for scrambling noise. Structured dropout noise has no free hyper-parameters.
         </p>
        </div>
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
         Table
         2
         presents results for different domain adaptation tasks. We also compute the
         transfer ratio
         , which is defined as
         adaptation accuracybaseline accuracy
         , shown in Figure
         1
         . The generally positive trend of these graphs indicates that adaptation becomes progressively more important as we select test sets that are more temporally remote from the training data.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         In general, mDA outperforms SCL and PCA, the latter of which shows little improvement over the base features. The various noising approaches for mDA give very similar results. However, structured dropout is orders of magnitude faster than the alternatives, as shown in Table
         3
         . The scrambling noise is most time-consuming, with cost dominated by a matrix multiplication.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Related Work
      </h2>
      <div class="ltx_paragraph" id="S4.SS2.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Domain adaptation
       </h4>
       <div class="ltx_para" id="S4.SS2.SSS0.P1.p1">
        <p class="ltx_p">
         Most previous work on domain adaptation focused on the supervised setting, in which some labeled data is available in the target domain
         [16, 5, 10]
         . Our work focuses on unsupervised domain adaptation, where no labeled data is available in the target domain. Several representation learning methods have been proposed to solve this problem. In structural correspondence learning (SCL), the induced representation is based on the task of predicting the presence of pivot features. Autoencoders apply a similar idea, but use the denoised instances as the latent representation
         [28, 12, 4]
         . Within the context of denoising autoencoders, we have focused on dropout noise, which has also been applied as a general technique for improving the robustness of machine learning, particularly in neural networks
         [13, 29]
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.SSS0.P1.p2">
        <p class="ltx_p">
         On the specific problem of sequence labeling,
         Xiao and Guo (2013)
         proposed a supervised domain adaptation method by using a log-bilinear language adaptation model.
         Dhillon et al. (2011)
         presented a spectral method to estimate low dimensional context-specific word representations for sequence labeling. Huang and Yates
         [14, 15]
         used an HMM model to learn latent representations, and then leverage the Posterior Regularization framework to incorporate specific biases. Unlike these methods, our approach uses a standard CRF, but with transformed features.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS2.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Historical text
       </h4>
       <div class="ltx_para" id="S4.SS2.SSS0.P2.p1">
        <p class="ltx_p">
         Our evaluation concerns syntactic analysis of historical text, which is a topic of increasing interest for NLP
         [23]
         .
         Pennacchiotti and Zanzotto (2008)
         find that part-of-speech tagging degrades considerably when applied to a corpus of historical Italian.
         Moon and Baldridge (2007)
         tackle the challenging problem of tagging Middle English, using techniques for projecting syntactic annotations across languages. Prior work on the Tycho Brahe corpus applied supervised learning to a random split of test and training data
         [17, 7]
         ; they did not consider the domain adaptation problem of training on recent data and testing on older historical text.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
