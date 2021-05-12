<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Fast and Robust Neural Network Joint Models for Statistical Machine Translation.
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
       Recent work has shown success in using neural network language models (NNLMs) as features in MT systems. Here, we present a novel formulation for a neural network
       joint
       model (NNJM), which augments the NNLM with a source context window. Our model is purely lexicalized and can be integrated into any MT decoder. We also present several variations of the NNJM which provide significant additive improvements.
      </p>
      <p class="ltx_p">
       Although the model is quite simple, it yields strong empirical results. On the NIST OpenMT12 Arabic-English condition, the NNJM features produce a gain of +3.0 BLEU on top of a powerful, feature-rich baseline which already includes a target-only NNLM. The NNJM features also produce a gain of +6.3 BLEU on top of a simpler baseline equivalent to Chiang’s
       [5]
       original Hiero implementation.
      </p>
      <p class="ltx_p">
       Additionally, we describe two novel techniques for overcoming the historically high cost of using NNLM-style models in MT decoding. These techniques speed up NNJM computation by a factor of 10,000x, making the model as fast as a standard back-off LM.
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
        In recent years, neural network models have become increasingly popular in NLP. Initially, these models were primarily used to create
        n
        -gram neural network language models (NNLMs) for speech recognition and machine translation
        [2, 23]
        . They have since been extended to translation modeling, parsing, and many other NLP tasks.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper we use a basic neural network architecture and a lexicalized probability model to create a powerful MT decoding feature. Specifically, we introduce a novel formulation for a neural network joint model (NNJM), which augments an
        n
        -gram target language model with an
        m
        -word source window. Unlike previous approaches to joint modeling
        [13]
        , our feature can be easily integrated into any statistical machine translation (SMT) decoder, which leads to substantially larger improvements than
        k
        -best rescoring only. Additionally, we present several variations of this model which provide significant additive BLEU gains.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We also present a novel technique for training the neural network to be
        self-normalized
        , which avoids the costly step of posteriorizing over the entire vocabulary in decoding. When used in conjunction with a
        pre-computed
        hidden layer, these techniques speed up NNJM computation by a factor of 10,000x, with only a small reduction on MT accuracy.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Although our model is quite simple, we obtain strong empirical results. We show primary results on the NIST OpenMT12 Arabic-English condition. The NNJM features produce an improvement of +3.0 BLEU on top of a baseline that is already better than the 1st place MT12 result and includes a powerful NNLM. Additionally, on top of a simpler decoder equivalent to Chiang’s
        [5]
        original Hiero implementation, our NNJM features are able to produce an improvement of +6.3 BLEU – as much as all of the other features in our strong baseline system combined.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We also show strong improvements on the NIST OpenMT12 Chinese-English task, as well as the DARPA BOLT (Broad Operational Language Translation) Arabic-English and Chinese-English conditions.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Neural Network Joint Model (NNJM)
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Formally, our model approximates the probability of target hypothesis
        T
        conditioned on source sentence
        S
        . We follow the standard
        n
        -gram LM decomposition of the target, where each target word
        ti
        is conditioned on the previous
        n-1
        target words. To make this a
        joint
        model, we also condition on source context vector
        𝒮i
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S8.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(T|S)
         </td>
         <td class="ltx_td ltx_align_center">
          ≈
         </td>
         <td class="ltx_td ltx_align_left">
          Πi=1|T|P(ti|ti-1,⋯,ti-n+1,𝒮i)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Intuitively, we want to define
        𝒮i
        as the window that is most relevant to
        ti
        . To do this, we first say that each target word
        ti
        is
        affiliated
        with exactly one source word at index
        ai
        .
        𝒮i
        is then the
        m
        -word source window centered at
        ai
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S8.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S2.Ex2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          𝒮i
         </td>
         <td class="ltx_td ltx_align_center">
          =
         </td>
         <td class="ltx_td ltx_align_left">
          sai-m-12,⋯,sai,⋯,sai+m-12
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        This notion of
        affiliation
        is derived from the word alignment, but unlike word alignment, each target word must be affiliated with exactly one non-NULL source word. The affiliation heuristic is very simple:
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <ol class="ltx_enumerate" id="I1">
        [label=(0),noitemsep]
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           If
           ti
           aligns to exactly one source word,
           ai
           is the index of the word it aligns to.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           If
           ti
           align to multiple source words,
           ai
           is the index of the aligned word in the middle.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           If
           ti
           is unaligned, we inherit its affiliation from the closest aligned word, with preference given to the right.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        An example of the NNJM context model for a Chinese-English parallel sentence is given in Figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        For all of our experiments we use
        n=4
        and
        m=11
        . It is clear that this model is effectively an
        (n+m)
        -gram LM, and a 15-gram LM would be far too sparse for standard probability models such as Kneser-Ney back-off
        [12]
        or Maximum Entropy
        [21]
        . Fortunately, neural network language models are able to elegantly scale up and take advantage of arbitrarily large context sizes.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Neural Network Architecture
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Our neural network architecture is almost identical to the original feed-forward NNLM architecture described in
         Bengio et al. (2003)
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The input vector is a 14-word context vector (3 target words, 11 source words), where each word is mapped to a 192-dimensional vector using a shared mapping layer. We use two 512-dimensional hidden layers with
         t⁢a⁢n⁢h
         activation functions. The output layer is a softmax over the entire output vocabulary.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The input vocabulary contains 16,000 source words and 16,000 target words, while the output vocabulary contains 32,000 target words. The vocabulary is selected by frequency-sorting the words in the parallel training data. Out-of-vocabulary words are mapped to their POS tag (or
         OOV
         , if POS is not available), and in this case
         P(POSi|ti-1,⋯)
         is used directly without further normalization. Out-of-bounds words are represented with special tokens
         &lt;src&gt;
         ,
         &lt;/src&gt;
         ,
         &lt;trg&gt;
         ,
         &lt;/trg&gt;
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         We chose these values for the hidden layer size, vocabulary size, and source window size because they seemed to work best on our data sets – larger sizes did not improve results, while smaller sizes degraded results. Empirical comparisons are given in Section
         6.5
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Neural Network Training
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         The training procedure is identical to that of an NNLM, except that the parallel corpus is used instead of a monolingual corpus. Formally, we seek to maximize the log-likelihood of the training data:
        </p>
        L=∑ilog⁡(P⁢(xi))
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         where
         xi
         is the training sample, with one sample for every target word in the parallel corpus.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         Optimization is performed using standard back propagation with stochastic gradient ascent
         [14]
         . Weights are randomly initialized in the range of
         [-0.05,0.05]
         . We use an initial learning rate of
         10-3
         and a minibatch size of 128.
         At every epoch, which we define as 20,000 minibatches, the likelihood of a validation set is computed. If this likelihood is worse than the previous epoch, the learning rate is multiplied by 0.5. The training is run for 40 epochs. The training data ranges from 10-30M words, depending on the condition. We perform a basic weight update with no L2 regularization or momentum. However, we have found it beneficial to clip each weight update to the range of [-0.1, 0.1], to prevent the training from entering degenerate search spaces
         [19]
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         Training is performed on a single Tesla K10 GPU, with each epoch (128*20k = 2.6M samples) taking roughly 1100 seconds to run, resulting in a total training time of
         ∼12
         hours. Decoding is performed on a CPU.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Self-Normalized Neural Network
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         The computational cost of NNLMs is a significant issue in decoding, and this cost is dominated by the output softmax over the entire target vocabulary. Even class-based approaches such as
         Le et al. (2012)
         require a 2-20k shortlist vocabulary, and are therefore still quite costly.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Here, our goal is to be able to use a fairly large vocabulary without word classes, and to simply avoid computing the entire output layer at decode time.
         To do this, we present the novel technique of
         self-normalization
         , where the output layer scores are close to being probabilities without explicitly performing a softmax.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         Formally, we define the standard softmax log likelihood as:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S8.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           log⁡(P⁢(x))
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           log⁡(eUr⁢(x)Z⁢(x))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           Ur⁢(x)-log⁡(Z⁢(x))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           Z⁢(x)
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           Σr′=1|V|⁢eUr′⁢(x)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         where
         x
         is the sample,
         U
         is the raw output layer scores,
         r
         is the output layer row corresponding to the observed target word, and
         Z⁢(x)
         is the softmax normalizer.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p5">
        <p class="ltx_p">
         If we could guarantee that
         log⁡(Z⁢(x))
         were always equal to 0 (i.e.,
         Z⁢(x)
         = 1) then at decode time we would only have to compute row
         r
         of the output layer instead of the whole matrix. While we cannot train a neural network with this guarantee, we can
         explicitly encourage
         the log-softmax normalizer to be as close to 0 as possible by augmenting our training objective function:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S8.EGx4">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           L
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑i[log⁡(P⁢(xi))-α⁢(log⁡(Z⁢(xi))-0)2]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑i[log⁡(P⁢(xi))-α⁢log2⁡(Z⁢(xi))]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS3.p6">
        <p class="ltx_p">
         In this case, the output layer bias weights are initialized to
         log⁡(1/|V|)
         , so that the initial network is self-normalized. At decode time, we simply use
         Ur⁢(x)
         as the feature score, rather than
         log⁡(P⁢(x))
         . For our NNJM architecture, self-normalization increases the lookup speed during decoding by a factor of
         ∼
         15x.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p7">
        <p class="ltx_p">
         Table
         1
         shows the neural network training results with various values of the free parameter
         α
         . In all subsequent MT experiments, we use
         α=10-1
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p8">
        <p class="ltx_p">
         We should note that
         Vaswani et al. (2013)
         implements a method called Noise Contrastive Estimation (NCE) that is also used to train self-normalized NNLMs. Although NCE results in faster training time, it has the downside that there is no mechanism to control the degree of self-normalization. By contrast, our
         α
         parameter allows us to carefully choose the optimal trade-off between neural network accuracy and mean self-normalization error. In future work, we will thoroughly compare self-normalization vs. NCE.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Pre-Computing the Hidden Layer
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         Although self-normalization significantly improves the speed of NNJM lookups, the model is still several orders of magnitude slower than a back-off LM. Here, we present a “trick” for pre-computing the first hidden layer, which further increases the speed of NNJM lookups by a factor of 1,000x.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p2">
        <p class="ltx_p">
         Note that this technique only results in a significant speedup for self-normalized, feed-forward, NNLM-style networks with
         one
         hidden layer. We demonstrate in Section
         6.6
         that using one hidden layer instead of two has minimal effect on BLEU.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p3">
        <p class="ltx_p">
         For the neural network described in Section
         2.1
         , computing the first hidden layer requires multiplying a
         2689
         -dimensional input vector
         with a
         2689×512
         dimensional hidden layer matrix. However, note that there are only 3 possible positions for each target word, and 11 for each source word. Therefore, for every word in the vocabulary, and for each position, we can pre-compute the dot product between the word embedding and the first hidden layer. These are computed offline and stored in a lookup table, which is
         &lt;
         500MB in size.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p4">
        <p class="ltx_p">
         Computing the first hidden layer now only requires 15 scalar additions for each of the 512 hidden rows – one for each word in the input vector, plus the bias. This can be reduced to just 5 scalar additions by pre-summing each 11-word source window when starting a test sentence. If our neural network has only one hidden layer and is self-normalized, the only remaining computation is 512 calls to
         t⁢a⁢n⁢h⁢()
         and a single 513-dimensional dot product for the final output score.
         Thus, only
         ∼
         3500 arithmetic operations are required per
         n
         -gram lookup, compared to
         ∼
         2.8M for self-normalized NNJM without pre-computation, and
         ∼
         35M for the standard NNJM.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p5">
        <p class="ltx_p">
         Table
         2
         shows the speed of self-normalization and pre-computation for the NNJM. The decoding cost is based on a measurement of
         ∼
         1200 unique NNJM lookups per source word for our Arabic-English system.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p6">
        <p class="ltx_p">
         By combining self-normalization and pre-computation, we can achieve a speed of 1.4M lookups/second, which is on par with fast back-off LM implementations
         [27]
         . We demonstrate in Section
         6.6
         that using the self-normalized/pre-computed NNJM results in only a very small BLEU degradation compared to the standard NNJM.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Decoding with the NNJM
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Because our NNJM is fundamentally an
        n
        -gram NNLM with additional source context, it can easily be integrated into any SMT decoder. In this section, we describe the considerations that must be taken when integrating the NNJM into a hierarchical decoder.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Hierarchical Parsing
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         When performing hierarchical decoding with an
         n
         -gram LM, the leftmost and rightmost
         n-1
         words from each constituent must be stored in the state space. Here, we extend the state space to also include the index of the affiliated source word for these edge words. This does not noticeably increase the search space. We also train a separate lower-order
         n
         -gram model, which is necessary to compute estimate scores during hierarchical decoding.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Affiliation Heuristic
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         For aligned target words, the normal affiliation heuristic can be used, since the word alignment is available within the rule. For unaligned words, the normal heuristic can also be used,
         except
         when the word is on the edge of a rule, because then the target neighbor words are not necessarily known.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         In this case, we infer the affiliation from the rule structure. Specifically, if unaligned target word
         t
         is on the right edge of an arc that covers source span
         [si,sj]
         , we simply say that
         t
         is affiliated with source word
         sj
         . If
         t
         is on the left edge of the arc, we say it is affiliated with
         si
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
       Model Variations
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Recall that our NNJM feature can be described with the following probability:
       </p>
       Πi=1|T|P(ti|ti-1,ti-2,⋯,sai,sai-1,sai+1,⋯)
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        This formulation lends itself to several natural variations. In particular, we can reverse the translation direction of the languages, as well as the direction of the language model.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        We denote our original formulation as a source-to-target, left-to-right model (
        S2T/L2R
        ). We can train three variations using target-to-source (T2S) and right-to-left (R2L) models:
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p ltx_align_center">
        S2T/R2L
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       Πi=1|T|P(ti|ti+1,ti+2,⋯,sai,sai-1,sai+1,⋯)
       <p class="ltx_p ltx_align_center">
        T2S/L2R
       </p>
       Πi=1|S|P(si|si-1,si-2,⋯,tai′,tai′-1,tai′+1,⋯)
       <p class="ltx_p ltx_align_center">
        T2S/R2L
       </p>
       Πi=1|S|P(si|si+1,si+2,⋯,tai′,tai′-1,tai′+1,⋯)
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        where
        ai′
        is the target-to-source affiliation, defined analogously to
        ai
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        The T2S variations cannot be used in decoding due to the large target context required, and are thus only used in
        k
        -best rescoring. The S2T/R2L variant could be used in decoding, but we have not found this beneficial, so we only use it in rescoring.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Neural Network Lexical Translation Model (NNLTM)
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         One issue with the S2T NNJM is that the probability is computed over every
         target
         word, so it does not explicitly model NULL-aligned source words. In order to assign a probability to every source word during decoding, we also train a neural network lexical translation model (NNLMT).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Here, the input context is the 11-word source window centered at
         si
         , and the output is the target token
         tsi
         which
         si
         aligns to. The probability is computed over every
         source
         word in the input sentence. We treat NULL as a normal target word, and if a source word aligns to multiple target words, it is treated as a single concatenated token. Formally, the probability model is:
        </p>
        Πi=1|S|P(tsi|si,si-1,si+1,⋯)
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         This model is trained and evaluated like our NNJM. It is easy and computationally inexpensive to use this model in decoding, since only one neural network computation must be made for each source word.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         In rescoring, we also use a T2S NNLTM model computed over every target word:
        </p>
        Πi=1|T|P(sti|ti,ti-1,ti+1,⋯)
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       MT System
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In this section, we describe the MT system used in our experiments.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        MT Decoder
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We use a state-of-the-art string-to-dependency hierarchical decoder
         [25]
         . Our baseline decoder contains a large and powerful set of features, which include:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <ul class="ltx_itemize" id="I2">
         [noitemsep]
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            Forward and backward rule probabilities
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            4-gram Kneser-Ney LM
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            Dependency LM
            [25]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            Contextual lexical smoothing
            [8]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i5.p1">
           <p class="ltx_p">
            Length distribution
            [25]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i6.p1">
           <p class="ltx_p">
            Trait features
            [7]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i7.p1">
           <p class="ltx_p">
            Factored source syntax
            [10]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i8" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i8.p1">
           <p class="ltx_p">
            7 sparse feature types, totaling 50k features
            [4]
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i9" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i9.p1">
           <p class="ltx_p">
            LM adaptation
            [26]
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         We also perform 1000-best rescoring with the following features:
        </p>
        <ul class="ltx_itemize" id="I3">
         [noitemsep]
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            5-gram Kneser-Ney LM
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Recurrent neural network language model (RNNLM)
            [16]
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Although we consider the RNNLM to be part of our baseline, we give it special treatment in the results section because we would expect it to have the highest overlap with our NNJM.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Training and Optimization
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         For Arabic word tokenization, we use the MADA-ARZ tokenizer
         [9]
         for the BOLT condition, and the Sakhr
         tokenizer for the NIST condition. For Chinese tokenization, we use a simple longest-match-first lexicon-based approach.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         For word alignment, we align all of the training data with both GIZA++
         [18]
         and NILE
         [20]
         , and concatenate the corpora together for rule extraction.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         For MT feature weight optimization, we use iterative
         k
         -best optimization with an ExpectedBLEU objective function
         [22]
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
       Experimental Results
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        We present MT primary results on Arabic-English and Chinese-English for the NIST OpenMT12 and DARPA BOLT conditions. We also present a set of auxiliary results in order to further analyze our features.
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        NIST OpenMT12 Results
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         Our NIST system is fully compatible with the OpenMT12 constrained track, which consists of 10M words of high-quality parallel training for Arabic, and 25M words for Chinese.
         The Kneser-Ney LM is trained on 5B words of data from English GigaWord. For test, we use the “Arabic-To-English Original Progress Test” (1378 segments) and “Chinese-to-English Original Progress Test + OpenMT12 Current Test” (2190 segments), which consists of a mix of newswire and web data.
         All test segments have 4 references. Our tuning set contains 5000 segments, and is a mix of the MT02-05 eval set as well as held-out parallel training.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         Results are shown in the second section of Table
         3
         . On Arabic-English, the primary S2T/L2R NNJM gains +1.4 BLEU on top of our baseline, while the S2T NNLTM gains another +0.8, and the directional variations gain +0.8 BLEU more. This leads to a total improvement of +3.0 BLEU from the NNJM and its variations. Considering that our baseline is already +0.3 BLEU better than the 1st place result of MT12 and contains a strong RNNLM, we consider this to be quite an extraordinary improvement.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p3">
        <p class="ltx_p">
         For the Chinese-English condition, there is an improvement of +0.8 BLEU from the primary NNJM and +1.3 BLEU overall. Here, the baseline system is already +0.8 BLEU better than the best MT12 system. The smaller improvement on Chinese-English compared to Arabic-English is consistent with the behavior of our baseline features, as we show in the next section.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        “Simple Hierarchical” NIST Results
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         The baseline used in the last section is a highly-engineered research system, which uses a wide array of features that were refined over a number of years, and some of which require linguistic resources. Because of this, the baseline BLEU scores are much higher than a typical MT system – especially a real-time, production engine which must support many language pairs.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         Therefore, we also present results using a simpler version of our decoder which emulates Chiang’s original Hiero implementation
         [5]
         . Specifically, this means that we don’t use dependency-based rule extraction, and our decoder only contains the following MT features: (1) rule probabilities, (2)
         n
         -gram Kneser-Ney LM, (3) lexical smoothing, (4) target word count, (5) concat rule penalty.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         Results are shown in the third section of Table
         3
         . The “Simple Hierarchical” Arabic-English system is -6.4 BLEU worse than our strong baseline, and would have ranked 10th place out of 11 systems in the evaluation. When the NNJM features are added to this system, we see an improvement of +6.3 BLEU, which would have ranked 1st place in the evaluation.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p4">
        <p class="ltx_p">
         Effectively, this means that for Arabic-English, the NNJM features are equivalent to the combined improvements from the string-to-dependency model plus all of the features listed in Section
         5.1
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p5">
        <p class="ltx_p">
         For Chinese-English, the “Simple Hierarchical” system only degrades by -3.2 BLEU compared to our strongest baseline, and the NNJM features produce a gain of +2.1 BLEU on top of that.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.3
        </span>
        BOLT Web Forum Results
       </h3>
       <div class="ltx_para" id="S6.SS3.p1">
        <p class="ltx_p">
         DARPA BOLT is a major research project with the goal of improving translation of informal, dialectical Arabic and Chinese into English. The BOLT domain presented here is “web forum,” which was crawled from various Chinese and Egyptian Internet forums by LDC. The BOLT parallel training consists of all of the high-quality NIST training, plus an additional 3 million words of translated forum data provided by LDC. The tuning and test sets consist of roughly 5000 segments each, with 2 references for Arabic and 3 for Chinese.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS3.p2">
        <p class="ltx_p">
         Results are shown in Table
         4
         . The baseline here uses the same feature set as the strong NIST system. On Arabic, the total gain is +2.6 BLEU, while on Chinese, the gain is +1.3 BLEU.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.4
        </span>
        Effect of
        k
        -best Rescoring Only
       </h3>
       <div class="ltx_para" id="S6.SS4.p1">
        <p class="ltx_p">
         Table
         5
         shows performance when our S2T/L2R NNJM is used only in 1000-best rescoring, compared to decoding. The primary purpose of this is as a comparison to
         Le et al. (2012)
         , whose model can only be used in
         k
         -best rescoring.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS4.p2">
        <p class="ltx_p">
         We can see that the rescoring-only NNJM performs very well when used on top of a baseline without an RNNLM (+1.5 BLEU), but the gain on top of the RNNLM is very small (+0.3 BLEU). The gain from the decoding NNJM is large in both cases (+2.6 BLEU w/o RNNLM, +1.6 BLEU w/ RNNLM). This demonstrates that the full power of the NNJM can only be harnessed when it is used in decoding. It is also interesting to see that the RNNLM is no longer beneficial when the NNJM is used.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.5
        </span>
        Effect of Neural Network Configuration
       </h3>
       <div class="ltx_para" id="S6.SS5.p1">
        <p class="ltx_p">
         Table
         6
         shows results using the S2T/L2R NNJM with various configurations. We can see that reducing the source window size, layer size, or vocab size will all degrade results. Increasing the sizes beyond the default NNJM has almost no effect (102%). Also note that the target-only NNLM (i.e., Source Window=0) only obtains 33% of the improvements of the NNJM.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS6">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.6
        </span>
        Effect of Speedups
       </h3>
       <div class="ltx_para" id="S6.SS6.p1">
        <p class="ltx_p">
         All previous results use a self-normalized neural network with two hidden layers. In Table
         7
         , we compare this to using a standard network (with two hidden layers), as well as a pre-computed neural network.
         The “Simple Hierarchical” baseline is used here because it more closely approximates a real-time MT engine. For the sake of speed, these experiments only use the S2T/L2R NNJM+S2T NNLTM.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS6.p2">
        <p class="ltx_p">
         Each result from Table
         7
         corresponds to a row in Table
         2
         of Section
         2.4
         . We can see that going from the standard model to the pre-computed model only reduces the BLEU improvement from +6.4 to +6.1, while increasing the NNJM lookup speed by a factor of 10,000x.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS6.p3">
        <p class="ltx_p">
         In Table
         2
         we showed that the cost of unique lookups for the pre-computed NNJM is only
         ∼
         0.001 seconds per source word. This does not include the cost of
         n
         -gram creation or cached lookups, which amount to
         ∼
         0.03 seconds per source word in our current implementation.
         However, the
         n
         -grams created for the NNJM can be shared with the Kneser-Ney LM, which reduces the cost of that feature. Thus, the total cost
         increase
         of using the NNJM+NNLTM features in decoding is only
         ∼
         0.01 seconds per source word.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS6.p4">
        <p class="ltx_p">
         In future work we will provide more detailed analysis regarding the usability of the NNJM in a low-latency, high-throughput MT engine.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S7">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        7
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S7.p1">
       <p class="ltx_p">
        Although there has been a substantial amount of past work in lexicalized joint models
        [15, 6]
        , nearly all of these papers have used older statistical techniques such as Kneser-Ney or Maximum Entropy. However, not only are these techniques intractable to train with high-order context vectors, they also lack the neural network’s ability to semantically generalize
        [17]
        and learn non-linear relationships.
       </p>
      </div>
      <div class="ltx_para" id="S7.p2">
       <p class="ltx_p">
        A number of recent papers have proposed methods for creating neural network translation/joint models, but nearly all of these works have obtained much smaller BLEU improvements than ours. For each related paper, we will briefly contrast their methodology with our own and summarize their BLEU improvements using scores taken directly from the cited paper.
       </p>
      </div>
      <div class="ltx_para" id="S7.p3">
       <p class="ltx_p">
        Auli et al. (2013)
        use a
        fixed
        continuous-space source representation, obtained from LDA
        [3]
        or a source-only NNLM. Also, their model is recurrent, so it cannot be used in decoding. They obtain +0.2 BLEU improvement on top of a target-only NNLM (25.6 vs. 25.8).
       </p>
      </div>
      <div class="ltx_para" id="S7.p4">
       <p class="ltx_p">
        Schwenk (2012)
        predicts an entire target phrase at a time, rather than a word at a time. He obtains +0.3 BLEU improvement (24.8 vs. 25.1).
       </p>
      </div>
      <div class="ltx_para" id="S7.p5">
       <p class="ltx_p">
        Zou et al. (2013)
        estimate context-free bilingual lexical similarity scores, rather than using a large context. They obtain an +0.5 BLEU improvement on Chinese-English (30.0 vs. 30.5).
       </p>
      </div>
      <div class="ltx_para" id="S7.p6">
       <p class="ltx_p">
        Kalchbrenner and Blunsom (2013)
        implement a convolutional recurrent NNJM. They score a 1000-best list using only their model and are able to achieve the same BLEU as using all 12 standard MT features (21.8 vs 21.7). However, additive results are not presented.
       </p>
      </div>
      <div class="ltx_para" id="S7.p7">
       <p class="ltx_p">
        The most similar work that we know of is
        Le et al. (2012)
        . Le’s basic procedure is to re-order the source to match the linear order of the target, and then segment the hypothesis into minimal bilingual phrase pairs. Then, he predicts each target word given the previous bilingual phrases. However, Le’s formulation could only be used in
        k
        -best rescoring, since it requires long-distance re-ordering and a large target context.
       </p>
      </div>
      <div class="ltx_para" id="S7.p8">
       <p class="ltx_p">
        Le’s model does obtain an impressive +1.7 BLEU gain on top of a baseline without an NNLM (25.8 vs. 27.5). However, when compared to the strongest baseline which includes an NNLM, Le’s best models (S2T + T2S) only obtain an +0.6 BLEU improvement (26.9 vs. 27.5). This is consistent with our rescoring-only result, which indicates that
        k
        -best rescoring is too shallow to take advantage of the power of a joint model.
       </p>
      </div>
      <div class="ltx_para" id="S7.p9">
       <p class="ltx_p">
        Le’s model also uses minimal phrases rather than being purely lexicalized, which has two main downsides: (a) a number of complex, hand-crafted heuristics are required to define phrase boundaries, which may not transfer well to new languages, (b) the effective vocabulary size is much larger, which substantially increases data sparsity issues.
       </p>
      </div>
      <div class="ltx_para" id="S7.p10">
       <p class="ltx_p">
        We should note that our best results use six separate models, whereas all previous work only uses one or two models. However, we have demonstrated that we can obtain 50%-80% of the total improvement with only one model (S2T/L2R NNJM), and 70%-90% with only two models (S2T/L2R NNJM + S2T NNLTM). Thus, the one and two-model conditions still significantly outperform any past work.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
