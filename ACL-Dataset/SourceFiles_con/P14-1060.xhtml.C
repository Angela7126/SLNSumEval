<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Vector space semantics with frequency-driven motifs.
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
       Traditional models of distributional semantics suffer from computational issues such as data sparsity for individual lexemes and complexities of modeling semantic composition when dealing with structures larger than single lexical items. In this work, we present a frequency-driven paradigm for robust distributional semantics in terms of semantically cohesive lineal constituents, or
       motifs
       . The framework subsumes issues such as differential compositional as well as non-compositional behavior of phrasal consituents, and circumvents some problems of data sparsity by design. We design a segmentation model to optimally partition a sentence into lineal constituents, which can be used to define distributional contexts that are less noisy, semantically more interpretable, and linguistically disambiguated. Hellinger PCA embeddings learnt using the framework show competitive results on empirical tasks.
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
        Meaning in language is a confluence of experientially acquired semantics of words or multi-word phrases, and their semantic composition to create new meanings. For instance, successfully interpreting a sentence such as
       </p>
       <p class="ltx_p ltx_align_center">
        The old senator kicked the bucket.
       </p>
       <p class="ltx_p">
        requires the knowledge that the semantic connotations of ‘kicking the bucket’ as a unit are the same as those for ‘dying’. Short of explicit supervision, such semantic mappings must be inferred by a new language speaker through inductive mechanisms operating on observed linguistic usage. This perspective of acquired meaning aligns with the ‘meaning is usage’ adage, consonant with Wittgenstein’s view of semantics. At the same time, the ability to adaptively communicate elaborate meanings can only be conciled through Frege’s principle of compositionality, i.e., meanings of larger linguistic constructs can be derived from the meanings of individual components, modulated by their syntactic interrelations. Indeed, most linguistic usage appears compositional. This is supported by the fact even with very limited vocabulary, children and non-native speakers can often communicate surprisingly effectively.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        It can be argued that to be sustainable, inductive aspects of meaning must be recurrent enough to be learnable by new users. That is, a non-compositional phrase such as ‘kick the bucket’ is likely to persist in common parlance only if it is frequently used with its associated semantic mapping. If a usage-driven meaning of a motif is not recurrent enough, learning this mapping is inefficient in two ways. First, the sparseness of observations would severely limit accurate inductive acquisition by new observers. Second, the value of learning a very infrequent semantic mapping is likely marginal. This motivates the need for a frequency-driven view of lexical semantics. In particular, such a perspective can be especially advantageous for distributional semantics for reasons we outline below.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Distributional semantic models (DSMs) that represent words as distributions over neighbouring contexts have been particularly effective in capturing fine-grained lexical semantics
        [26]
        . Such models have engendered improvements in diverse applications such as selectional preference modeling
        [8]
        , word-sense discrimination
        [15]
        , automatic dictionary building
        [7]
        , and information retrieval
        [14]
        . However, while conventional DSMs consider collocation strengths (through counts and PMI scores) of word neighbourhoods, they disregard much of the regularity in human language. Most significantly, word tokens that act as latent dimensions are often derived from arbitrary tokenization. The example given in Table 1 succinctly describes this. The first row in the table shows a representation of the meaning of the token ‘crisis’ that a conventional DSM might extract from the given sentence after stopword removal. While helpful, the representation seems unsatisfying since words such as ‘press’, ‘wake’ and ‘shores’ seem to have little to do with a crisis. From a semantic perspective, a representation similar to the second is more valuable: not only does it represent a semantic mapping for a more specific meaning, but the latent dimensions of the representation have are less noisy (e.g., while ‘wake’ is semantically ambiguous, its surrounding context in ‘in wake of’ disambiguates it) and more intuitive in regards of semantic interepretability. This is the overarching theme of this work: we present a frequency driven paradigm for extending distributional semantics to phrasal and sentential levels in terms of such semantically cohesive, recurrent lexical units or
        motifs
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We propose to identify such semantically cohesive motifs in terms of features inspired from frequency-characteristics, linguistic idiosyncrasies, and shallow syntactic analysis; and explore both supervised and semi-supervised models to optimally segment a sentence into such motifs. Through exploiting regularities in language usage, the framework can efficiently account for both compositional and non-compositional word usage, while avoiding the issue of data-sparsity by design. Our principal contributions in this paper are:
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           We present a framework for extending distributional semantics to learn semantic representations of both words and phrases in terms of recurrent motifs, rather than arbitrary word tokens
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           We present a simple model to segment a sentence into such motifs using a feature-set drawing from frequency statistics, information theory, linguistic theories and shallow syntactic analysis
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Word and phrasal representations learnt through the approach outperform conventional DSM representations on empirical tasks
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        This paper is organized as follows: In Section 2, we briefly review related work in the domain of compositional distributional semantics, and motivate our formulation. Section 3 describes our methodology, which consists of a frequency-driven segmentation model to partition text into semantically meaningful recurring lineal-subunits, a representation learning framework for learning new semantic embeddings based on this segmentation, and an approach to use such embeddings in downstream applications. We present experiments and empirical evaluations for our method in Section 4. Finally, we conclude in Section 5 with a summary of our principal findings, and a discussion of possible directions for future work.
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
        While DSMs have been valuable in representing semantics of single words, approaches to extend them to represent the semantics of phrases and sentences has met with only marginal success. While there is considerable variety in approaches and formulations, existing approaches for phrasal level and sentential semantics can broadly be partitioned into two categories.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Compositional approaches
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         These have aimed at using semantic representations for individual words to learn semantic representations for larger linguistic structures. These methods implicitly make an assumption of compositionality, and often include explicit computational models of compositionality. Notable among such models are the additive and multiplicative models of composition by
         Mitchell and Lapata (2008)
         ,
         Grefenstette et al. (2010)
         , Baroni and Zamparelli’s
         [2]
         model that differentially models content and function words for semantic composition, and Goyal et al.’s SDSM model
         [9]
         that incorporates syntactic roles to model semantic composition. Notable among the most effective distributional representations are the recent deep-learning approaches by
         Socher et al. (2012)
         , that model vector composition through non-linear transformations. While word embeddings and language models from such methods have been useful for tasks such as relation classification, polarity detection, event coreference and parsing; much of existing literature on composition is based on abstract linguistic theory and conjecture, and there is little evidence to support that learnt representations for larger linguistic units correspond to their semantic meanings. While works such as the SDSM model suffer from the
         problem of sparsity
         in composing structures beyond bigrams and trigrams, methods such as
         Mitchell and Lapata (2008)
         and
         [22]
         and
         Grefenstette and Sadrzadeh (2011)
         are restricted by significant
         model biases
         in representing semantic composition by generic algebraic operations. Finally, the assumption that semantic meanings for sentences could have representations similar to those for smaller individual tokens is in some sense unintuitive, and not supported by linguistic or semantic theories.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Tree kernels
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Tree Kernel methods have gained popularity in the last decade for capturing syntactic information in the structure of parse trees
         [3, 17]
         . Instead of procuring explicit representations, the kernel paradigm directly focuses on the larger goal of quantifying semantic similarity of larger linguistic units. Structural kernels for NLP are based on matching substructures within two parse trees , consisting of word-nodes with similar labels. These methods have been useful for eclectic tasks such as parsing, NER, semantic role labeling, and sentiment analysis. Recent approaches such as by
         Croce et al. (2011)
         and
         Srivastava et al. (2013)
         have attempted to provide formulations to incorporate semantics into tree kernels through the use of distributional word vectors at the individual word-nodes. While this framework is attractive in the lack of assumptions on representation that it makes, the use of distributional embeddings for individual tokens means that it suffers from the same shortcomings as described for the example in Table 1, and hence these methods model semantic relations between word-nodes very weakly. Figure 1 shows an example of the shortcomings of this general approach.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         While the two sentences in consideration have near-identical syntax and could be argued to have semantically aligned words in similar positions, the semantics of the complete sentences are widely divergent. Specifically, the ‘bag of words’ assumption in tree kernels doesn’t suffice for these lexemes, and a stronger semantic model is needed to capture phrasal semantics as well as diverging inter-word relations such as in ‘coffee table’ and ‘water table’. Our hypothesis is that a model that can even weakly identify recurrent motifs such as ‘water table’ or ‘breaking a fall’ would be helpful in building more effective semantic representations. A significant advantage of a frequency driven view is that it makes the concern of compositionality of recurrent phrases immaterial. If a motif occurs frequently enough in common parlance, its semantics could be captured with distributional models irrespective of whether its associated semantics are compositional or acquired.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Identifying multi-word expressions
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         Several approaches have focused on supervised identification of multi-word expressions (MWEs) through statistical
         [19, 27]
         and linguistically motivated
         [20]
         techniques. More recently, hybrid methods based on both statistical as well as linguistic features have been popular
         [25]
         . Ramisch et al.
         [21]
         demonstrate that adding part-of-speech tags to frequency counts substantially improves performance. Other methods have attempted to exploit morphological, syntactic and semantic characteristics of MWEs. In particular, approaches such as
         Bannard (2007)
         use syntactic rigidity to characterize MWEs. While existing work has focused on the classification task of categorizing a phrasal constituent as a MWE or a non-MWE, the general ideas of most of these works are in line with our current framework, and the feature-set for our motif segmentation model is designed to subsume most of these ideas. It is worthwhile to point out that the task of motif segmentation is slightly different from MWE identification. Specifically, the onus on recurrent occurrences means that non-decomposibility is not an essential consideration for a word to be considered a motif. In line with the proposed paradigm, typical MWEs such as ‘shoot the breeze’, ‘sour note’ and ‘hot dog’ would be considered valid lineal motifs.
         In addition, even decomposable recurrent lineal phrases such as ‘love story’, ‘federal government’, and ‘millions of people’ are marked as meaningful recurrent motifs. Finally, and least interestingly, we include common named entities such as ‘United States’ and ‘Java Virtual Machine’ within the ambit of motifs.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Method
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section, we define our frequency-driven framework for distributional semantics in detail. As just described above, our definition for motifs is less specific than MWEs. With such a working definition, contiguous motifs are likely to make distributional representations less noisy and also assist in disambiguating context. Also, the lack of specificity ensures that such motifs are common enough to meaningfully influence distributional representation beyond single tokens. A method towards frequency-driven distributional semantics could involve the following principal components:
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Linear segmentation model
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The segmentation model forms the core of the framework. Ideally, it fragments a given sentence into non-overlapping, semantically meaningful, empirically frequent contiguous sub-units or motifs. The model accounts for possible segmentations of a sentence into potential motifs, and prefers recurrent and cohesive motifs through features that capture frequency-based and statistical features, as well as linguistic idiosyncracies. This is accomplished using a very simple linear chain model and a rich feature set consisting of a combination of frequency-driven, information theoretic and linguistically motivated features.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Let an observed sentence be denoted by
         𝐱
         , with the individual tokens
         xi
         denoting the i’th token in the sentence. The segmentation model is a chain LVM (latent variable model) that aims to maximize a linear objective defined by:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        J=∑iwi⁢fi⁢(yk,yk-1,𝐱)
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         where
         fi
         are arbitrary Markov features that can depend on segments (potential motifs) of the observed sentence
         𝐱
         , and contiguous latent states. The features are chosen so as to best represent frequency-based, statistical as well as linguistic considerations for treating a segment as an agglutinative unit, or a motif. In specific, these features could encode characteristics such as frequency statistics, collocation strengths and syntactic distinctness, or inflectional rigidity of the considered segments; described in detail in Section 3.2. The model is an instantiation of a simple featurized HMM, and the weighted sum of features corresponding to a segment is cognate with an affinity score for the ‘stickiness’ of the segment, i.e., the affinity for the segment to be treated as holistic unit or a single motif.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         We also associate a penalizing cost for each non unary-motif to avoid aggressive agglutination of tokens. In particular, for an ngram occurrence to be considered a motif, the marginal contribution due to the affinity of the prospective motif should at minimum exceed this penalty. The weights for the affinity functions as well as these penalties are learnt from data using full as well as partial annotations. The latent state-variables
         yk
         denotes the membership of the token
         𝐱𝐤
         to a unary or a larger motif; and the state-sequence collectively gives the segmentation of the sentence. An individual state-variable
         yk
         encodes a pairing of the size of the encompassing ngram motif, and the position of the word
         xk
         within it. For instance,
         yk=T3
         denotes that the token
         𝐱𝐤
         is the final position in a trigram motif.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.1
         </span>
         Inference of optimal segmentation
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS1.p1">
         <p class="ltx_p">
          If the optimal weights
          wi
          are known, inference for the best motif segmentation can be performed in linear time (in the number of tokens) following the generalized Viterbi algorithm. A slightly modified version of Viterbi could also be used to find segmentations that are constrained to agree with some given motif boundaries, but can segment other parts of the sentence optimally under these constraints. This is necessary for the scenario of semi-supervised learning of weights with partially annotated sentences, as described later.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Learning motif affinities and penalties
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We briefly discuss data-driven learning of weights for features that define the motif affinity scores and penalties. We describe learning of the model parameters with fully annotated training data, as well as an approach for learning motif segmentation that requires only partial supervision.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Supervised learning:
         In the supervised case, optimal state sequences
         𝐲(𝐤)
         are fully observed for the training set. For this purpose, we created a dataset of 1000 sentences from the Simple English Wikipedia and the Gigaword Corpus, and manually annotated it with motif boundaries using BRAT
         [24]
         . In this case, learning can follow the online structured perceptron learning procedure by
         Collins (2002)
         , where weights updates for the k’th training example
         (𝐱(k),𝐲(k))
         are given as:
        </p>
        wi←wi+α⁢(fi⁢(𝐱(k),𝐲(k))-fi⁢(𝐱(k),𝐲′))
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Here
         𝐲′=D⁢e⁢c⁢o⁢d⁢e⁢(𝐱(k),𝐰)
         is the optimal Viterbi decoding using the current estimates of the weights. Updates are run for a large number of iterations until the change in objective drops below a threshold, and the learning rate
         α
         is adaptively modified as described in Collins et al. Implicitly, the weight learning algorithm can be seen as a gradient descent procedure minimizing the difference between the scores of highest scoring (Viterbi) state sequences, and the label state sequences.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Semi-supervised learning:
         In the semi-supervised case, the labels
         yi(k)
         are known only for some of the tokens in
         𝐱(𝐤)
         . This is a commonplace scenario, where a part of a sentence has clear motif-boundaries, whereas the rest of the sentence is not annotated. For accumulating such data, we looked for occurrences of 2500 expressions from the WikiMWE dataset in sentences from the combined Simple English Wikipedia and Gigaword corpora. The query expressions in the retrieved sentences were marked with motif boundaries, while the remaining tokens in the sentences were left unannotated.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         While the Viterbi algorithm can be used for tagging optimal state-sequences given the weights, the structured perceptron can learn optimal model weights given gold-standard sequence labels. Hence, in this case, we use a variation of the hard EM algorithm for learning. The algorithm proceeds as follows: in the E-step, we use the current values of weights to compute hard-expectations, i.e., the best scoring Viterbi sequences among those consistent with the observed state labels. In the M-step, we take the decoded state-sequences in the E-step as observed, and run perceptron learning to update feature weights
         wi
         . Pseudocode of the learning algorithm for the partially labeled case is given in Algorithm 1.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         [h!]
         [1]
         <span class="ltx_text ltx_font_bold">
          Input:
         </span>
         Partially labeled data
         D={(x,y)i}
         <span class="ltx_text ltx_font_bold">
          Output:
         </span>
         Weights
         w
         <span class="ltx_text ltx_font_bold">
          Initialization:
         </span>
         Set
         wi
         randomly,
         ∀i
         <math alttext="i:1" class="ltx_Math" display="inline" id="S3.SS2.p6.m5" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            i
           </mi>
           <mo>
            :
           </mo>
           <mn>
            1
           </mn>
          </mrow>
         </math>
         to
         m⁢a⁢x⁢I⁢t⁢e⁢r
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         Decode
         D
         with current
         w
         to find optimal Viterbi paths that agree with (partial) ground truths.
         Run Structured Perceptron algorithm with decoded tag-sequences to update weights
         w
         <span class="ltx_ERROR undefined">
          \State
         </span>
         return
         w
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p8">
        <p class="ltx_p">
         The semi-supervised approach enables incorporation of significantly more training data. In particular, this method could be used in conjunction with a supervised approach. This would involve initializing the weights prior to the semi-supervised procedure with the weights from the supervised learning model, so as to seed the semi-supervised approach with reasonable model, and use the partially annotated data to fine-tune the supervised model. The sequential approach, akin to annealing weights, can efficiently utilize both full and partial annotations.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.1
         </span>
         Feature engineering
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS1.p1">
         <p class="ltx_p">
          In this section, we describe the principal features used in the segmentation model
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS1.p2">
         <p class="ltx_p">
          Transitional features and penalties:
         </p>
         <ul class="ltx_itemize" id="I2">
          <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i1.p1">
            <p class="ltx_p">
             Transitional features
             ft⁢r⁢a⁢n⁢s⁢(yi-1,yi)=Iyi-1,yi
             describing the transitional affinities of state pairs. Since our state definitions preclude certain transitions (such as from state
             T2
             to
             T1
             ), these weights are initialized to
             -∞
             to expedite training.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i2.p1">
            <p class="ltx_p">
             N-gram penalties:
             fn⁢g⁢r⁢a⁢m
             We define a penalty for tagging each non-unary motif as described before. For a motif to be tagged, the improvement in objective score should at least exceed the corresponding penalty. e.g.,
             fq⁢g⁢r⁢a⁢m⁢(yi)=Iyi=Q4
             denotes the penalty for tagging a tetragram.
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS1.p3">
         <p class="ltx_p">
          Frequency-based, information theoretic, and POS features:
         </p>
         <ul class="ltx_itemize" id="I3">
          <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i1.p1">
            <p class="ltx_p">
             Absolute and log-normalized motif frequencies
             fn⁢g⁢r⁢a⁢m⁢(xi-n+1,…⁢xi-1,xi,yi)
             . This feature is associated with a particular token-sequence and ngram-tag, and takes the value of the motif-frequency if the motif token-sequence matches the feature token-sequence, and is marked as with a matching tag. e.g.,
             fb⁢g⁢r⁢a⁢m(xi-1=love,xi=story,yi=B2)
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i2.p1">
            <p class="ltx_p">
             Absolute and log-normalized motif frequencies for a particular POS-sequence. This feature is associated with a particular POS-tag sequence and ngram-tag, and takes the value of the motif-frequency if the motif token-sequence gets a matching tag, and is marked as with a matching ngram tag. e.g.,
             fb⁢g⁢r⁢a⁢m(pi-1=VB,pi=NN,yi=B2)
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i3.p1">
            <p class="ltx_p">
             Medians and maxima of pairwise collocation statistics for tokens for a particular size of ngram motifs: we use the following statistics: pointwise mutual information, Chi-square statistic, and conditional probability. We also used POS sensitive versions of these, which performed much better than plain versions in our evaluations.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i4.p1">
            <p class="ltx_p">
             Histogram counts of inflectional forms of token sequence for the corresponding ngram motif and POS sequence: this features takes the value of the count of inflectional forms of an ngram that account for 90% of occurrences of all inflectional forms.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i5" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i5.p1">
            <p class="ltx_p">
             Entropies of histogram distributions of inflectional variants (described above).
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i6" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i6.p1">
            <p class="ltx_p">
             Features encoding syntactic rigidity: ratios and log-ratios of frequencies of an ngram motif and variations by replacing a token using near synonyms from its synset.
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS1.p4">
         <p class="ltx_p">
          Additionally, a few feature for the segmentations model contained minor orthographic features based on word shape (length and capitalization patterns). Also, all numbers, URLs, and currency symbols were normalized to the special NUMERIC, URL, and CURRENCY tokens respectively. Finally, a gazetteer feature checked for occurrences of motifs in a gazetteer of named entities.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Representation learning
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         With the segmentation model described in the previous section, we process text from the English Gigaword corpus and the Simple English Wikipedia to partition sentences into motifs. Since the segmentation model accounts for the contexts of the entire sentence in determining motifs, different instances of the same token could evoke different meaning representations. Consider the following sentences tagged by the segmentation model, that would correspond to different representations of the token ‘remains’: once as a standalone motif, and once as part of an encompassing bigram motif (‘remains classified’).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         Hog prices have declined sharply , while the cost of corn remains relatively high.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         Even with the release of such documents, questions are not answered, since only the agency knows what remains classified
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         Given constituent motifs of each sentence in the data, we can now define neighbourhood distributions for unary or phrasal motifs in terms of other motifs (as envisioned in Table 1). In our experiments, we use a window-length of 5 adjoining motifs on either side to define the neighbourhood of a constituent. Naturally, in the presence of multi-word motifs, the neighbourhood boundary could be more extended than in a conventional DSM.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p5">
        <p class="ltx_p">
         With such neighbourhood contexts, the distributional paradigm posits that semantic similarity between a pair of motifs can be given by a sense of ‘distance’ between the two distributions. Most popularly, traditional measures of vector distance such as the cosine similarity, Euclidean distance and City-block distance have been used in several distributional approaches. Additionally, several distance measures between discrete distributions exist in statistical literature, most famously the Kullback Leibler divergence, Bhattacharyya distance and the Hellinger distance. Recent work
         [13]
         has shown that the Hellinger distance is an especially effective measure in learning distributional embeddings, with Hellinger PCA being much more computationally inexpensive than neural language modeling approaches, while performing much better than standard PCA, and competitive with the state-of-the-art in downstream evaluations. Hence, we use the Hellinger measure between neighbourhood motif distributions in learning representations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p6">
        <p class="ltx_p">
         The Hellinger distance between two categorical distributions
         P=(p1⁢…⁢pk)
         and
         Q=(q1⁢…⁢qk)
         is defined as:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p7">
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           H⁢(P,Q)
          </td>
          <td class="ltx_td ltx_align_left">
           =12⁢∑i=1k(pi-qi)2
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           =12⁢∥P-Q∥2
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S3.SS3.p8">
        <p class="ltx_p">
         The Hellinger measure has intuitively desirable properties: specifically, it can be seen as the Euclidean distance between the square-roots transformed distributions, where both vectors
         P
         and
         Q
         are length-normalized under the same(Euclidean) norm. Finally, we perform SVD on the motif similarity matrix (with size of the order of the total vocabulary in the corpus), and retain the first
         k
         principal eigenvectors to obtain low-dimensional vector representations that are more convenient to work with. In our preliminary experiments, we found that
         k=300
         gave quantitatively good results, with marginal change with added dimensionality. We use this setting for all our experiments.
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
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section, we describe some experimental evaluations and findings for our approach. We first quantitatively and qualitatively analyze the performance of the segmentation model, and then evaluate the distributional motif representations learnt by the model through two downstream applications.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Motif segmentation
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         In an evaluation of the motif segmentations model within the perspective of our framework, we believe that exact correspondence to human judgment is unrealistic, since guiding principles for defining motifs, such as semantic cohesion, are hard to define and only serve as working principles. However, for purposes of relative comparison, we quantitatively evaluate the performance of the motif segmentation models on the fully annotated dataset. For this experiment, the gold-annotated corpus was split into a training and test sets in a 9:1 proportion. A small fraction of the training split was set apart for development and validation. For this evaluation, we considered a motif boundary as correct only for an exact match, i.e., when both its boundaries (left and right) were correctly predicted. Also, since a majority of motifs are unary tokens, including them into consideration artificially boosts the accuracy, whereas we are more interested in the prediction of larger n-gram tokens. Hence we report results on the performance on only non-unary motifs.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Table
         2
         shows the performance of the segmentation model with the three proposed learning approaches described earlier. For a baseline, we consider a rule-based model that simply learns all ngram segmentations seen in the training data, and marks any occurrence of a matching token sequence as a motif; without taking neighbouring context into account. We observe that this model has a very high precision (since many token sequences marked as motifs would recur in similar contexts, and would thus have the same motif boundaries). However, the rule-based method has a very row recall due to lack of generalization capabilities. We see that while all three learning algorithms perform better than the baseline, the performance of the purely unsupervised system is inferior to supervised approaches. This is not unexpected: the supervision provided to the model is very weak due to a lack of negative examples (which leads to spurious motif taggings, leading to a low precision), as well as no examples of transitions between adjacent motifs (to learn transitional weights and penalties). The supervised model expectedly outperforms both the rule-based and the semi-supervised systems. However, the supervised learning model with subsequent annealing outperforms the supervised model in terms of both precision and recall; showing the utility of the semi-supervised method when seeded with a good initial model, and the additive value of partially labeled data.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         Qualitative analysis of motif-segmented sentences shows that our designed feature-set is effective and helpful in identifying semantically cohesive ngrams. Table 3 provides four examples. The first example correctly identifies ‘went public’, while missing out on the potential motif ‘cheered her on’. In general, these examples illustrate that the model can identify idiomatic and idiosyncratic themes as well as commonly recurrent ngrams (in the second example, the model picks out ‘has become’ which is highly recurrent, but doesn’t have the semantic cohesiveness of some of the other motifs). In particular, consider the second example, where the model picks ‘white elephant’ as a motif. In such cases, the disambiguating influence of context incorporated by the motif is apparent.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         The above table shows some of the top results for the unary token ‘elephant’ by frequency, and frequent unary and non-unary motifs for the motif ‘white elephant’ retrieved by the segmentation model.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Distributional representations
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         For evaluating distributional representations for motifs (in terms of other motifs) learnt by the framework, we test these representations in two downstream tasks: sentence polarity classification and metaphor detection. For sentence polarity, we consider the Cornell Sentence Polarity corpus by
         Pang and Lee (2005)
         , where the task is to classify the polarity of a sentence as positive or negative. The data consists of 10662 sentences from movie reviews that have been annotated as either positive or negative. For composing the motifs representations to get judgments on semantic similarity of sentences, we use our recent Vector Tree Kernel approach The VTK approach defines a convolutional kernel over graphs defined by the dependency parses of sentences, using a vector representation at each graph node that representing a single lexical token. For our purposes, we modify the approach to merge the nodes of all tokens that constitute a motif occurrence, and use the motif representation as the vector associated with the node. Table 4 shows results for the sentence polarity task.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         For this task, the motif based distributional embeddings vastly outperform a conventional distributional model (DSM) based on token distributions, as well as additive (AVM) and multiplicative (MVM) models of vector compositionality, as proposed by Lapata et al. The model is competitive with the state-of-the-art VTK
         [23]
         that uses the SENNA neural embeddings by
         Collobert et al. (2011)
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         On the metaphor detection task, we use the Metaphor dataset
         [12]
         . The data consists of sentences with defined phrases, and the task consists of identifying the linguistic use in these phrases as metaphorical or literal. For this task, the motif based model is expected to perform well as common metaphorical usage is generally through idiosyncratic MWEs, which the motif based models is specially geared to capture through the features of the segmentation model. For this task, we again use the VTK formalism for combining vector representations of the individual motifs. Table 5 shows that the motif-based DSM does better than discriminative models such as CRFs and SVMs, and also slightly improves on the VTK kernel with distributional embeddings.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
