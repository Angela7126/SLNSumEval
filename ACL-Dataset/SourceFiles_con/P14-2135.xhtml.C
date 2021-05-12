<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improving Multi-Modal Representations Using Image Dispersion: Why Less is Sometimes More.
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
       Models that learn semantic representations from both linguistic and perceptual input outperform text-only models in many contexts and better reflect human concept acquisition. However, experiments suggest that while the inclusion of perceptual input improves representations of certain concepts, it degrades the representations of others. We propose an unsupervised method to determine whether to include perceptual input for a concept, and show that it significantly improves the ability of multi-modal models to learn and represent word meanings. The method relies solely on image data, and can be applied to a variety of other NLP tasks.
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
        Multi-modal models that learn semantic concept representations from both linguistic and perceptual input were originally motivated by parallels with human concept acquisition, and evidence that many concepts are
        grounded
        in the perceptual system
        [3]
        . Such models extract information about the perceptible characteristics of words from data collected in property norming experiments
        [22, 24]
        or directly from ‘raw’ data sources such as images
        [11, 6]
        . This input is combined with information from linguistic corpora to produce enhanced representations of concept meaning. Multi-modal models outperform language-only models on a range of tasks, including modelling conceptual association and predicting compositionality
        [6, 24, 22]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Despite these results, the advantage of multi-modal over linguistic-only models has only been demonstrated on concrete concepts, such as
        chocolate
        or
        cheeseburger
        , as opposed to abstract concepts such as such as
        guilt
        or
        obesity
        . Indeed, experiments indicate that while the addition of perceptual input is generally beneficial for representations of concrete concepts
        [13, 7]
        , it can in fact be detrimental to representations of abstract concepts
        [13]
        . Further, while the theoretical importance of the perceptual modalities to concrete representations is well known, evidence suggests this is not the case for more abstract concepts
        [21, 14]
        . Indeed, perhaps the most influential characterization of the abstract/concrete distinction, the Dual Coding Theory
        [21]
        , posits that concrete representations are encoded in both the linguistic and perceptual modalities whereas abstract concepts are encoded only in the linguistic modality.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Existing multi-modal architectures generally extract and process all the information from their specified sources of perceptual input. Since perceptual data sources typically contain information about both abstract and concrete concepts, such information is included for both concept types. The potential effect of this design decision on performance is significant because the vast majority of meaning-bearing words in everyday language correspond to abstract concepts. For instance, 72% of word tokens in the British National Corpus
        [17]
        were rated by contributors to the University of South Florida dataset (USF)
        [20]
        as more abstract than the noun
        war
        , a concept that many would consider quite abstract.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In light of these considerations, we propose a novel algorithm for approximating conceptual concreteness. Multi-modal models in which perceptual input is filtered according to our algorithm learn higher-quality semantic representations than previous approaches, resulting in a significant performance improvement of up to 17% in capturing the semantic similarity of concepts. Further, our algorithm constitutes the first means of quantifying conceptual concreteness that does not rely on labor-intensive experimental studies or annotators. Finally, we demonstrate the application of this unsupervised concreteness metric to the semantic classification of adjective-noun pairs, an existing NLP task to which concreteness data has proved valuable previously.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Experimental Approach
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Our experiments focus on multi-modal models that extract their perceptual input automatically from images. Image-based models more naturally mirror the process of human concept acquisition than those whose input derives from experimental datasets or expert annotation. They are also more scalable since high-quality tagged images are freely available in several web-scale image datasets.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        We use
        Google Images
        as our image source, and extract the first
        n
        image results for each concept word. It has been shown that images from Google yield higher-quality representations than comparable sources such as
        Flickr
        [4]
        . Other potential sources, such as ImageNet
        [9]
        or the ESP Game Dataset
        [30]
        , either do not contain images for abstract concepts or do not contain sufficient images for the concepts in our evaluation sets.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Image Dispersion-Based Filtering
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Following the motivation outlined in Section 1, we aim to distinguish visual input corresponding to concrete concepts from visual input corresponding to abstract concepts. Our algorithm is motivated by the intuition that the diversity of images returned for a particular concept depends on its concreteness (see Figure 1). Specifically, we anticipate greater congruence or similarity among a set of images for, say,
         elephant
         than among images for
         happiness
         . By exploiting this connection, the method approximates the concreteness of concepts, and provides a basis to filter the corresponding perceptual information.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Formally, we propose a measure,
         image dispersion
         d
         of a concept word
         w
         , defined as the average pairwise cosine distance between all the image representations
         {w1→⁢…⁢wn→}
         in the set of images for that concept:
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        d⁢(w)=12⁢n⁢(n-1)⁢∑i&lt;j≤n1-wi→⋅wj→|wi→|⁢|wj→|

(1)
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         We use an average pairwise distance-based metric because this emphasizes the total variation more than e.g. the mean distance from the centroid. In all experiments we set
         n=50
         .
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Generating Visual Representations
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          Visual vector representations for each image were obtained using the well-known
          bag of visual words
          (BoVW) approach
          [25]
          . BoVW obtains a vector representation for an image by mapping each of its local descriptors to a cluster histogram using a standard clustering algorithm such as k-means.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS0.P1.p2">
         <p class="ltx_p">
          Previous NLP-related work uses
          SIFT
          [11, 6]
          or
          SURF
          [22]
          descriptors for identifying points of interest in an image, quantified by 128-dimensional local descriptors. We apply
          Pyramid Histogram Of visual Words
          (PHOW) descriptors, which are particularly well-suited for object categorization, a key component of image similarity and thus dispersion
          [5]
          . PHOW is roughly equivalent to running SIFT on a dense grid of locations at a fixed scale and orientation and at multiple scales (see Fig 2), but is both more efficient and more accurate than regular (dense) SIFT approaches
          [5]
          . We resize the images in our dataset to 100x100 pixels and compute PHOW descriptors using
          VLFeat
          [29]
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS0.P1.p3">
         <p class="ltx_p">
          The descriptors for the images were subsequently clustered using mini-batch
          k
          -means
          [23]
          with
          k=50
          to obtain histograms of visual words, yielding 50-dimensional visual vectors for each of the images.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Generating Linguistic Representations
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          We extract continuous vector representations (also of 50 dimensions) for concepts using the continuous log-linear skipgram model of
          Mikolov et al. (2013a)
          , trained on the 100M word British National Corpus
          [17]
          . This model learns high quality lexical semantic representations based on the distributional properties of words in text, and has been shown to outperform simple distributional models on applications such as semantic composition and analogical mapping
          [19]
          .
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Evaluation Gold-standards
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         We evaluate models by measuring the Spearman correlation of model output with two well-known gold-standards reflecting semantic proximity – a standard measure for evaluating the quality of representations (see e.g.
         Agirre et al. (2009)
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         To test the ability of our model to capture concept similarity, we measure correlations with WordSim353
         [12]
         , a selection of 353 concept pairs together with a similarity rating provided by human annotators. WordSim has been used as a benchmark for distributional semantic models in numerous studies (see e.g.
         [15, 6]
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         As a complementary gold-standard, we use the University of South Florida Norms (USF)
         [20]
         . This dataset contains scores for
         free association
         , an experimental measure of cognitive association, between over 40,000 concept pairs. The USF norms have been used in many previous studies to evaluate semantic representations
         [2, 11, 24, 22]
         . The USF evaluation set is particularly appropriate in the present context because concepts in the dataset are also rated for conceptual concreteness by at least 10 human annotators.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         We create a representative evaluation set of USF pairs as follows. We randomly sample 100 concepts from the upper quartile and 100 concepts from the lower quartile of a list of all USF concepts ranked by concreteness. We denote these sets
         C
         , for
         concrete
         , and
         A
         for abstract respectively. We then extract all pairs
         (w1,w2)
         in the USF dataset such that both
         w1
         and
         w2
         are in
         A∪C
         . This yields an evaluation set of 903 pairs, of which 304 are such that
         w1,w2∈C
         and 317 are such that
         w1,w2∈A
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p5">
        <p class="ltx_p">
         The images used in our experiments and the evaluation gold-standards can be downloaded from
         http://www.cl.cam.ac.uk/~dk427/dispersion.html
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
       Improving Multi-Modal Representations
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We apply
        image dispersion-based filtering
        as follows: if both concepts in an evaluation pair have an image dispersion below a given threshold, both the linguistic and the visual representations are included. If not, in accordance with the Dual Coding Theory of human concept processing
        [21]
        , only the linguistic representation is used. For both datasets, we set the threshold as the median image dispersion, although performance could in principle be improved by adjusting this parameter. We compare dispersion filtered representations with linguistic, perceptual and standard multi-modal representations (concatenated linguistic and perceptual representations). Similarity between concept pairs is calculated using cosine similarity.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        As Figure
        3
        shows, dispersion-filtered multi-modal representations significantly outperform standard multi-modal representations on both evaluation datasets. We observe a 17% increase in Spearman correlation on WordSim353 and a 22% increase on the USF norms. Based on the correlation comparison method of
        Steiger (1980)
        , both represent significant improvements (WordSim353,
        t=2.42
        ,
        p&lt;0.05
        ; USF,
        t=1.86
        ,
        p&lt;0.1
        ). In both cases, models with the dispersion-based filter also outperform the purely linguistic model, which is not the case for other multi-modal approaches that evaluate on WordSim353 (e.g.
        Bruni et al. (2012)
        ).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Concreteness and Image Dispersion
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The filtering approach described thus far improves multi-modal representations because image dispersion provides a means to distinguish concrete concepts from more abstract concepts. Since research has demonstrated the applicability of concreteness to a range of other NLP tasks
        [28, 16]
        , it is important to examine the connection between image dispersion and concreteness in more detail.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Quantifying Concreteness
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         To evaluate the effectiveness of image dispersion as a proxy for concreteness we evaluated our algorithm on a binary classification task based on the set of 100 concrete and 100 abstract concepts
         A∪C
         introduced in Section 2. By classifying concepts with image dispersion below the median as concrete and concepts above this threshold as abstract we achieved an abstract-concrete prediction accuracy of 81%.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         While well-understood intuitively, concreteness is not a formally defined notion. Quantities such as the USF concreteness score depend on the subjective judgement of raters and the particular annotation guidelines. According to the Dual Coding Theory, however, concrete concepts are precisely those with a salient perceptual representation. As illustrated in Figure
         4
         , our binary classification conforms to this characterization. The importance of the visual modality is significantly greater when evaluating on pairs for which both concepts are classified as concrete than on pairs of two abstract concepts.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         Image dispersion is also an effective predictor of concreteness on samples for which the abstract/concrete distinction is less clear. On a different set of 200 concepts extracted by random sampling from the USF dataset stratified by concreteness rating (including concepts across the concreteness spectrum), we observed a high correlation between abstractness and dispersion (Spearman
         ρ=0.61,p&lt;0.001
         ). On this more diverse sample, which reflects the range of concepts typically found in linguistic corpora, image dispersion is a particularly useful diagnostic for identifying the very abstract or very concrete concepts. As Table 1 illustrates, the concepts with the lowest dispersion in this sample are, without exception, highly concrete, and the concepts of highest dispersion are clearly very abstract.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         It should be noted that all previous approaches to the automatic measurement of concreteness rely on annotator ratings, dictionaries or manually-constructed resources.
         Kwong (2008)
         proposes a method based on the presence of hard-coded phrasal features in dictionary entries corresponding to each concept. By contrast,
         Sánchez et al. (2011)
         present an approach based on the position of word senses corresponding to each concept in the WordNet ontology
         [10]
         .
         Turney et al. (2011)
         propose a method that extends a large set of concreteness ratings similar to those in the USF dataset. The Turney et al. algorithm quantifies the concreteness of concepts that lack such a rating based on their proximity to rated concepts in a semantic vector space. In contrast to each of these approaches, the image dispersion approach requires no hand-coded resources. It is therefore more scalable, and instantly applicable to a wide range of languages.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Classifying Adjective-Noun Pairs
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Finally, we explored whether image dispersion can be applied to specific NLP tasks as an effective proxy for concreteness.
         Turney et al. (2011)
         showed that concreteness is applicable to the classification of adjective-noun modification as either literal or non-literal. By applying a logistic regression with noun concreteness as the predictor variable, Turney et al. achieved a classification accuracy of 79% on this task. This model relies on significant supervision in the form of over 4,000 human lexical concreteness ratings.
         Applying image dispersion in place of concreteness in an identical classifier on the same dataset, our entirely unsupervised approach achieves an accuracy of 63%. This is a notable improvement on the largest-class baseline of 55%.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
