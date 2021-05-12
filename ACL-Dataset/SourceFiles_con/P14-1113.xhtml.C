<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Learning Semantic Hierarchies via Word Embeddings.
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
       Semantic hierarchy construction aims to build structures of concepts linked by hypernym–hyponym (“is-a”) relations.
A major challenge for this task is the automatic discovery of such relations.
This paper proposes a novel and effective method for the construction of semantic hierarchies based on word embeddings,
which can be used to measure the semantic relationship between words.
We identify whether a candidate word pair has hypernym–hyponym relation by using the word-embedding-based semantic projections between words and their hypernyms.
Our result, an F-score of 73.74%, outperforms the state-of-the-art methods on a manually labeled test dataset.
Moreover, combining our method with a previous manually-built hierarchy extension method can further improve F-score to 80.29%.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       UTF8gbsn
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
        Semantic hierarchies are natural ways to organize knowledge.
They are the main components of ontologies or semantic thesauri
        [16, 27]
        .
In the WordNet hierarchy, senses are organized according to the “is-a” relations.
For example, “
        dog
        ” and “
        canine
        ” are connected by a directed edge.
Here, “
        canine
        ” is called a hypernym of “
        dog
        .”
Conversely, “
        dog
        ” is a hyponym of “
        canine
        .”
As key sources of knowledge, semantic thesauri and ontologies can support many natural language processing applications.
However, these semantic resources are limited in its scope and domain, and their manual construction is knowledge intensive and time consuming.
Therefore, many researchers have attempted to automatically extract semantic relations or to construct taxonomies.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        A major challenge for this task is the automatic discovery of hypernym-hyponym relations.
        Fu et al. (2013)
        propose a distant supervision method to extract hypernyms for entities from multiple sources.
The output of their model is a list of hypernyms for a given enity (left panel, Figure
        1
        ).
However, there usually also exists hypernym–hyponym relations among these hypernyms.
For instance, “æ¤ç© (
        plant
        )” and “æ¯èç§ (
        Ranunculaceae
        )” are both hypernyms of the entity “ä¹å¤´ (
        aconit
        ),”
and “æ¤ç© (
        plant
        )” is also a hypernym of “æ¯èç§ (
        Ranunculaceae
        ).”
Given a list of hypernyms of an entity, our goal in the present work is to construct a semantic hierarchy of these hypernyms (right panel, Figure
        1
        ).
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Some previous works extend and refine manually-built semantic hierarchies by using other resources (e.g., Wikipedia)
        [27]
        .
However, the coverage is limited by the scope of the resources.
Several other works relied heavily on lexical patterns, which would suffer from deficiency because such patterns can only cover a small proportion of complex linguistic circumstances
        [10, 23]
        .
Besides, distributional similarity methods
        [11, 12]
        are based on the assumption that a term can only be used in contexts where its hypernyms can be used and that a term might be used in any contexts where its hyponyms are used.
However, it is not always rational.
Our previous method based on web mining
        [8]
        works well for hypernym extraction of entity names, but it is unsuitable for semantic hierarchy construction which involves many words with broad semantics.
Moreover, all of these methods do not use the word semantics effectively.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        This paper proposes a novel approach for semantic hierarchy construction based on word embeddings.
Word embeddings, also known as distributed word representations, typically represent words with dense, low-dimensional and real-valued vectors.
Word embeddings have been empirically shown to preserve linguistic regularities, such as the semantic relationship between words
        [15]
        .
For example,
        v(
        king)-v(queen)≈v(man)-v(woman)
        ,
where
        v⁢(w)
        is the embedding of the word
        w
        .
We observe that a similar property also applies to the hypernym–hyponym relationship (Section
        3.3
        ), which is the main inspiration of the present study.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        However, we further observe that hypernym–hyponym relations are more complicated than a single offset can represent.
To address this challenge, we propose a more sophisticated and general method — learning a linear projection which maps words to their hypernyms (Section
        3.3.1
        ).
Furthermore, we propose a piecewise linear projection method based on relation clustering to better model hypernym–hyponym relations (Section
        3.3.2
        ).
Subsequently, we identify whether an unknown word pair is a hypernym–hyponym relation using the projections (Section
        3.4
        ).
To the best of our knowledge, we are the first to apply word embeddings to this task.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        For evaluation, we manually annotate a dataset containing 418 Chinese entities and their hypernym hierarchies, which is the first dataset for this task as far as we know.
The experimental results show that our method achieves an F-score of 73.74% which significantly outperforms the previous state-of-the-art methods.
Moreover, combining our method with the manually-built hierarchy extension method proposed by
        Suchanek et al. (2008)
        can further improve F-score to 80.29%.
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
        As main components of ontologies, semantic hierarchies have been studied by many researchers.
Some have established concept hierarchies based on manually-built semantic resources such as WordNet
        [16]
        .
Such hierarchies have good structures and high accuracy,
but their coverage is limited to fine-grained concepts (e.g., “
        Ranunculaceae
        ” is not included in WordNet.).
We have made similar obsevation that about a half of hypernym–hyponym relations are absent in a Chinese semantic thesaurus.
Therefore, a broader range of resources is needed to supplement the manually built resources.
In the construction of the famous ontology YAGO,
        Suchanek et al. (2008)
        link the categories in Wikipedia onto WordNet.
However, the coverage is still limited by the scope of Wikipedia.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Several other methods are based on lexical patterns.
They use manually or automatically constructed lexical patterns to mine hypernym–hyponym relations from text corpora.
A hierarchy can then be built based on these pairwise relations.
The pioneer work by
        Hearst (1992)
        has found out that
linking two noun phrases (NPs) via certain lexical constructions often implies hypernym relations.
For example, NP
        1
        is a hypernym of NP
        2
        in the lexical pattern “such NP
        1
        as NP
        2
        .”
        Snow et al. (2005)
        propose to automatically extract large numbers of lexico-syntactic patterns and subsequently detect hypernym relations from a large newswire corpus.
Their method relies on accurate syntactic parsers, and the quality of the automatically extracted patterns is difficult to guarantee.
Generally speaking, these pattern-based methods often suffer from low recall or precision because of the coverage or the quality of the patterns.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The distributional methods assume that the contexts of hypernyms are broader than the ones of their hyponyms.
For distributional similarity computing, each word is represented as a semantic vector composed of the pointwise mutual information (PMI) with its contexts.
        Kotlerman et al. (2010)
        design a directional distributional measure to infer hypernym–hyponym relations based on the standard IR Average Precision evaluation measure.
        Lenci and Benotto (2012)
        propose another measure focusing on the contexts that hypernyms do not share with their hyponyms.
However, broader semantics may not always infer broader contexts.
For example, for terms “
        Obama
        ’ and “
        American people
        ”, it is hard to say whose contexts are broader.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Our previous work
        [8]
        applies a web mining method to discover the hypernyms of Chinese entities from multiple sources.
We assume that the hypernyms of an entity co-occur with it frequently.
It works well for named entities.
But for class names (e.g., singers in Hong Kong, tropical fruits) with wider range of meanings, this assumption may fail.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        In this paper, we aim to identify hypernym–hyponym relations using word embeddings, which have been shown to preserve good properties for capturing semantic relationship between words.
       </p>
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
        In this section, we first define the task formally.
Then we elaborate on our proposed method composed of three major steps, namely, word embedding training, projection learning, and hypernym–hyponym relation identification.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Task Definition
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Given a list of hypernyms of an entity, our goal is to construct a semantic hierarchy on it (Figure
         1
         ).
We represent the hierarchy as a directed graph
         G
         , in which the nodes denote the words, and the edges denote the hypernym–hyponym relations.
Hypernym-hyponym relations are
         asymmetric
         and
         transitive
         when words are unambiguous:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            ∀x,y∈L:x
            →𝐻
            y⇒¬(y
            →𝐻
            x)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            ∀x,y,z∈L:(x
            →𝐻
            z∧z
            →𝐻
            y)⇒x
            →𝐻
            y
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         Here,
         L
         denotes the list of hypernyms.
         x
         ,
         y
         and
         z
         denote the hypernyms in
         L
         .
We use
         →𝐻
         to represent a hypernym–hyponym relation in this paper.
Actually,
         x
         ,
         y
         and
         z
         are unambiguous as the hypernyms of a certain entity.
Therefore,
         G
         should be a directed acyclic graph (DAG).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Word Embedding Training
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Various models for learning word embeddings have been proposed, including neural net language models
         [1, 17, 15]
         and spectral models
         [6]
         .
More recently,
         Mikolov et al. (2013a)
         propose two log-linear models, namely the
         Skip-gram
         and
         CBOW
         model, to efficiently induce word embeddings.
These two models can be trained very efficiently on a large-scale corpus because of their low time complexity.
Additionally, their experiment results have shown that the
         Skip-gram
         model performs best in identifying semantic relationship among words.
Therefore, we employ the
         Skip-gram
         model for estimating word embeddings in this study.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         The
         Skip-gram
         model adopts log-linear classifiers to predict context words given the current word
         𝐰⁢(t)
         as input. First,
         𝐰⁢(t)
         is projected to its embedding. Then, log-linear classifiers are employed, taking the embedding as input and predict
         𝐰⁢(t)
         ’s context words within a certain range, e.g.
         k
         words in the left and
         k
         words in the right. After maximizing the log-likelihood over the entire dataset using stochastic gradient descent (SGD), the embeddings are learned.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Projection Learning
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Mikolov et al. (2013b)
         observe that word embeddings preserve interesting linguistic regularities, capturing a considerable amount of syntactic/semantic relations.
Looking at the well-known example:
         v(
         king)-v(queen)≈v(man)-v(woman)
         , it indicates that the embedding offsets indeed represent the shared semantic relation between the two word pairs.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         We observe that the same property also applies to some hypernym–hyponym relations.
As a preliminary experiment, we compute the embedding offsets between some randomly sampled hypernym–hyponym word pairs and measure their similarities. The results are shown in Table
         1
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         The first two examples imply that a word can also be mapped to its hypernym by utilizing word embedding offsets.
However, the offset from “
         carpenter
         ” to “
         laborer
         ” is distant from the one from “
         gold fish
         ” to “
         fish
         ,” indicating that hypernym–hyponym relations should be more complicated than a single vector offset can represent.
To verify this hypothesis, we compute the embedding offsets over all hypernym–hyponym word pairs in our training data and visualize them.
         Figure
         2
         shows that the relations are adequately distributed in the clusters, which implies that hypernym–hyponym relations indeed can be decomposed into more fine-grained relations.
Moreover, the relations about animals are spatially close, but separate from the relations about people’s occupations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         To address this challenge, we propose to learn the hypernym–hyponym relations using projection matrices.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS3.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.3.1
         </span>
         A Uniform Linear Projection
        </h4>
        <div class="ltx_para" id="S3.SS3.SSS1.p1">
         <p class="ltx_p">
          Intuitively, we assume that all words can be projected to their hypernyms based on a uniform transition matrix.
That is, given a word
          x
          and its hypernym
          y
          , there exists a matrix
          Φ
          so that
          y=Φ⁢x
          .
For simplicity, we use the same symbols as the words to represent the embedding vectors.
Obtaining a consistent exact
          Φ
          for the projection of all hypernym–hyponym pairs is difficult.
Instead, we can learn an approximate
          Φ
          using Equation
          1
          on the training data, which minimizes the mean-squared error:
         </p>
         Φ*=arg⁢minΦ⁡1N⁢∑(x,y)∥Φ⁢x-y∥2

(1)
         <p class="ltx_p">
          where
          N
          is the number of
          (x,y)
          word pairs in the training data.
This is a typical linear regression problem.
The only difference is that our predictions are multi-dimensional vectors instead of scalar values.
We use SGD for optimization.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS3.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.3.2
         </span>
         Piecewise Linear Projections
        </h4>
        <div class="ltx_para" id="S3.SS3.SSS2.p1">
         <p class="ltx_p">
          A uniform linear projection may still be under-representative for fitting all of the hypernym–hyponym word pairs, because the relations are rather diverse, as shown in Figure
          2
          .
To better model the various kinds of hypernym–hyponym relations, we apply the idea of piecewise linear regression
          [20]
          in this study.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS2.p2">
         <p class="ltx_p">
          Specifically, the input space is first segmented into several regions.
That is, all word pairs
          (x,y)
          in the training data are first clustered into several groups, where word pairs in each group are expected to exhibit similar hypernym–hyponym relations.
Each word pair
          (x,y)
          is represented with their vector offsets:
          y-x
          for clustering.
The reasons are twofold: (1) Mikolov’s work has shown that the vector offsets imply a certain level of semantic relationship.
(2) The vector offsets distribute in clusters well, and the word pairs which are close indeed represent similar relations, as shown in Figure
          2
          .
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS2.p3">
         <p class="ltx_p">
          Then we learn a separate projection for each cluster, respectively (Equation
          2
          ).
         </p>
         Φk*=arg⁢minΦk⁡1Nk⁢∑(x,y)∈Ck∥Φk⁢x-y∥2

(2)
         <p class="ltx_p">
          where
          Nk
          is the amount of word pairs in the
          kt⁢h
          cluster
          Ck
          .
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS2.p4">
         <p class="ltx_p">
          We use the
          k
          -means algorithm for clustering, where
          k
          is tuned on a development dataset.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS3.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.3.3
         </span>
         Training Data
        </h4>
        <div class="ltx_para" id="S3.SS3.SSS3.p1">
         <p class="ltx_p">
          To learn the projection matrices, we extract training data from a Chinese semantic thesaurus, Tongyi Cilin (Extended) (CilinE for short) which contains 100,093 words
          [3]
          .
          CilinE is organized as a hierarchy of five levels, in which the words are linked by hypernym–hyponym relations (right panel, Figure
          3
          ).
Each word in CilinE has one or more sense codes (some words are polysemous) that indicate its position in the hierarchy.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS3.p2">
         <p class="ltx_p">
          The senses of words in the first level, such as “ç© (
          object
          )” and “æ¶é´ (
          time
          ),” are very general.
The fourth level only has sense codes without real words.
Therefore, we extract words in the second, third and fifth levels to constitute hypernym–hyponym pairs (left panel, Figure
          3
          ).
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS3.p3">
         <p class="ltx_p">
          Note that mapping one hyponym to multiple hypernyms with the same projection (
          Φ⁢x
          is unique) is difficult.
Therefore, the pairs with the same hyponym but different hypernyms are expected to be clustered into separate groups.
Figure
          3
          shows that the word “
          dragonfly
          ” in the fifth level has two hypernyms: “
          insect
          ” in the third level and “
          animal
          ” in the second level.
Hence the relations
          dragonfly
          →𝐻
          insect
          and
          dragonfly
          →𝐻
          animal
          should fall into different clusters.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS3.p4">
         <p class="ltx_p">
          In our implementation, we apply this constraint by simply dividing the training data into two categories, namely,
          direct
          and
          indirect
          .
Hypernym-hyponym word pair
          (x,y)
          is classified into the
          direct
          category, only if there doesn’t exist another word
          z
          in the training data, which is a hypernym of
          x
          and a hyponym of
          y
          .
Otherwise,
          (x,y)
          is classified into the
          indirect
          category.
Then, data in these two categories are clustered separately.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Hypernym-hyponym Relation Identification
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Upon obtaining the clusters of training data and the corresponding projections, we can identify whether two words have a hypernym–hyponym relation.
Given two words
         x
         and
         y
         , we find cluster
         Ck
         whose center is closest to the offset
         y-x
         , and obtain the corresponding projection
         Φk
         .
For
         y
         to be considered a hypernym of
         x
         , one of the two conditions below must hold.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         Condition 1:
         The projection
         Φk
         puts
         Φk⁢x
         close enough to
         y
         (Figure
         4
         ).
Formally, the euclidean distance between
         Φk⁢x
         and
         y
         :
         d⁢(Φk⁢x,y)
         must be less than a threshold
         δ
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p3">
        d⁢(Φk⁢x,y)=∥Φk⁢x-y∥2&lt;δ

(3)
       </div>
       <div class="ltx_para" id="S3.SS4.p4">
        <p class="ltx_p">
         Condition 2:
         There exists another word
         z
         satisfying
         x
         →𝐻
         z
         and
         z
         →𝐻
         y
         .
In this case, we use the transitivity of hypernym–hyponym relations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p5">
        <p class="ltx_p">
         Besides, the final hierarchy should be a DAG as discussed in Section
         3.1
         .
However, the projection method cannot guarantee that theoretically, because the projections are learned from pairwise hypernym–hyponym relations without the whole hierarchy structure.
All pairwise hypernym–hyponym relation identification methods would suffer from this problem actually.
It is an interesting problem how to construct a globally optimal semantic hierarchy conforming to the form of a DAG.
But this is not the focus of this paper.
So if some conflicts occur, that is,
a relation circle exists, we remove or reverse the weakest path heuristically (Figure
         5
         ).
If a circle has only two nodes, we remove the weakest path.
If a circle has more than two nodes, we reverse the weakest path to form an
         indirect
         hypernym–hyponym relation.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experimental Setup
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Experimental Data
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         In this work, we learn word embeddings from a Chinese encyclopedia corpus named Baidubaike
         , which contains about 30 million sentences (about 780 million words).
The Chinese segmentation is provided by the open-source Chinese language processing platform LTP
         [3]
         .
Then, we employ the
         Skip-gram
         method (Section
         3.2
         ) to train word embeddings.
Finally we obtain the embedding vectors of 0.56 million words.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         The training data for projection learning is collected from CilinE (Section
         3.3.3
         ).
We obtain 15,247 word pairs of hypernym–hyponym relations (9,288 for
         direct
         relations and 5,959 for
         indirect
         relations).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         For evaluation, we collect the hypernyms for 418 entities, which are selected randomly from Baidubaike, following
         Fu et al. (2013)
         .
We then ask two annotators to manually label the semantic hierarchies of the correct hypernyms.
The final data set contains 655 unique hypernyms and 1,391 hypernym–hyponym relations among them.
We randomly split the labeled data into 1/5 for development and 4/5 for testing (Table
         2
         ).
The hierarchies are represented as relations of pairwise words.
We measure the inter-annotator agreement using the kappa coefficient
         [22]
         .
The kappa value is 0.96, which indicates a good strength of agreement.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Evaluation Metrics
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We use precision, recall, and F-score as our metrics to evaluate the performances of the methods.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Since hypernym–hyponym relations and its reverse (hyponym–hypernym) have one-to-one correspondence, their performances are equal.
For simplicity, we only report the performance of the former in the experiments.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Results and Analysis
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Varying the Amount of Clusters
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We first evaluate the effect of different number of clusters based on the development data.
We vary the numbers of the clusters both for the
         direct
         and
         indirect
         training word pairs.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         As shown in Figure
         6
         , the performance of clustering is better than non-clustering (when the cluster number is 1),
thus providing evidences that learning piecewise projections based on clustering is reasonable.
We finally set the numbers of the clusters of
         direct
         and
         indirect
         to 20 and 5, respectively, where the best performances are achieved on the development data.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Comparison with Previous Work
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         In this section, we compare the proposed method with previous methods, including manually-built hierarchy extension, pairwise relation extraction based on patterns, word distributions, and web mining (Section
         2
         ).
Results are shown in Table
         3
         .
        </p>
       </div>
       <div class="ltx_subsubsection" id="S5.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          5.2.1
         </span>
         Overall Comparison
        </h4>
        <div class="ltx_para" id="S5.SS2.SSS1.p1">
         <p class="ltx_p">
          M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          refers to the manually-built hierarchy extension method of
          Suchanek et al. (2008)
          .
In our experiment, we use the category taxonomy of Chinese Wikipedia
          to extend CilinE.
Table
          3
          shows that this method achieves a high precision but also a low recall, mainly because of the limited scope of Wikipedia.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p2">
         <p class="ltx_p">
          M
          P⁢a⁢t⁢t⁢e⁢r⁢n
          refers to the pattern-based method of
          Hearst (1992)
          .
We extract hypernym–hyponym relations in the Baidubaike corpus, which is also used to train word embeddings (Section
          4.1
          ).
We use the Chinese Hearst-style patterns (Table
          4
          ) proposed by
          Fu et al. (2013)
          , in which
          w
          represents a word, and
          h
          represents one of its hypernyms.
The result shows that only a small part of the hypernyms can be extracted based on these patterns
because only a few hypernym relations are expressed in these fixed patterns, and many are expressed in highly flexible manners.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p3">
         <p class="ltx_p">
          In the same corpus, we apply the method M
          S⁢n⁢o⁢w
          originally proposed by
          Snow et al. (2005)
          .
The same training data for projections learning from CilinE (Section
          3.3.3
          ) is used as seed hypernym–hyponym pairs.
Lexico-syntactic patterns are extracted from the Baidubaike corpus by using the seeds.
We then develop a logistic regression classifier based on the patterns to recognize hypernym–hyponym relations.
This method relies on an accurate syntactic parser, and the quality of the automatically extracted patterns is difficult to guarantee.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p4">
         <p class="ltx_p">
          We re-implement two previous distributional methods M
          b⁢a⁢l⁢A⁢p⁢i⁢n⁢c
          [11]
          and M
          i⁢n⁢v⁢C⁢L
          [12]
          in the Baidubaike corpus.
Each word is represented as a feature vector in which each dimension is the PMI value of the word and its context words.
We compute a score for each word pair and apply a threshold to identify whether it is a hypernym–hyponym relation.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p5">
         <p class="ltx_p">
          M
          F⁢u
          refers to our previous web mining method
          [8]
          .
This method mines hypernyms of a given word
          w
          from multiple sources and returns a ranked list of the hypernyms.
We select the hypernyms with scores over a threshold of each word in the test set for evaluation.
This method assumes that frequent co-occurrence of a noun or noun phrase
          n
          in multiple sources with
          w
          indicate possibility of
          n
          being a hypernym of
          w
          .
The results presented in
          Fu et al. (2013)
          show that the method works well when
          w
          is an entity, but not when
          w
          is a word with a common semantic concept.
The main reason may be that there are relatively more introductory pages about entities than about common words in the Web.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p6">
         <p class="ltx_p">
          M
          E⁢m⁢b
          is the proposed method based on word embeddings.
Table
          3
          shows that the proposed method achieves a better recall and F-score than all of the previous methods do.
It can significantly (
          p&lt;0.01
          ) improve the F-score over the state-of-the-art method M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          .
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p7">
         <p class="ltx_p">
          M
          E⁢m⁢b
          and M
          C⁢i⁢l⁢i⁢n⁢E
          can also be combined.
The combination strategy is to simply merge all positive results from the two methods together, and then to infer new relations based on the transitivity of hypernym–hyponym relations.
The F-score is further improved from 73.74% to 76.29%.
Note that, the combined method achieves a 4.43% recall improvement over M
          E⁢m⁢b
          , but the precision is almost unchanged.
The reason is that the inference based on the relations identified automatically may lead to error propagation.
For example, the relation
          x
          →𝐻
          y
          is incorrectly identified by M
          E⁢m⁢b
          .
When the relation
          y
          →𝐻
          z
          from M
          C⁢i⁢l⁢i⁢n⁢E
          is added, it will cause a new incorrect relation
          x
          →𝐻
          z
          .
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS1.p8">
         <p class="ltx_p">
          Combining M
          E⁢m⁢b
          with M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          achieves a 7% F-score improvement over the best baseline M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          .
Therefore, the proposed method is complementary to the manually-built hierarchy extension method
          [27]
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S5.SS2.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          5.2.2
         </span>
         Comparison on the Out-of-CilinE Data
        </h4>
        <div class="ltx_para" id="S5.SS2.SSS2.p1">
         <p class="ltx_p">
          We are greatly interested in the practical performance of the proposed method on the hypernym–hyponym relations outside of CilinE.
We say a word pair is outside of CilinE, as long as there is one word in the pair not existing in CilinE.
In our test data, about 62% word pairs are outside of CilinE.
Table
          5
          shows the performances of the best baseline method and our method on the out-of-CilinE data.
The method exploiting the taxonomy in Wikipedia, M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          , achieves the highest precision but has a low recall.
By contrast, our method can discover more hypernym–hyponym relations with some loss of precision, thereby achieving a more than 29% F-score improvement.
The combination of these two methods achieves a further 4.5% F-score improvement over M
          E⁢m⁢b+C⁢i⁢l⁢i⁢n⁢E
          .
Generally speaking, the proposed method greatly improves the recall but damages the precision.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS2.SSS2.p2">
         <p class="ltx_p">
          Actually, we can get different precisions and recalls by adjusting the threshold
          δ
          (Equation
          3
          ).
Figure
          7
          shows that M
          E⁢m⁢b+C⁢i⁢l⁢i⁢n⁢E
          achieves a higher precision than M
          W⁢i⁢k⁢i+C⁢i⁢l⁢i⁢n⁢E
          when their recalls are the same.
When they achieve the same precision, the recall of M
          E⁢m⁢b+C⁢i⁢l⁢i⁢n⁢E
          is higher.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Error Analysis and Discussion
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         We analyze error cases after experiments.
Some cases are shown in Figure
         8
         .
We can see that there is only one general relation “æ¤ç© (
         plant
         )”
         →𝐻
         “çç© (
         organism
         )” existing in CilinE.
Some fine-grained relations exist in Wikipedia, but the coverage is limited.
Our method based on word embeddings can discover more hypernym–hyponym relations than the previous methods can.
When we combine the methods together, we get the correct hierarchy.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         Figure
         8
         shows that our method loses the relation “ä¹å¤´å± (
         Aconitum
         )”
         →𝐻
         “æ¯èç§ (
         Ranunculaceae
         ).”
It is because they are very semantically similar (their cosine similarity is 0.9038).
Their representations are so close to each other in the embedding space
that we have not find projections suitable for these pairs.
The error statistics show that when the cosine similarities of word pairs are greater than 0.8, the recall is only 9.5%.
This kind of error accounted for about 10.9% among all the errors in our test set.
One possible solution may be adding more data of this kind to the training set.
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
        In addition to the works mentioned in Section
        2
        , we introduce another set of related studies in this section.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Evans (2004)
        ,
        Ortega-Mendoza et al. (2007)
        , and
        Sang (2007)
        consider web data as a large corpus and use search engines to identify hypernyms based on the lexical patterns of
        Hearst (1992)
        .
However, the low quality of the sentences in the search results negatively influence the precision of hypernym extraction.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Following the method for discovering patterns automatically
        [23]
        ,
        McNamee et al. (2008)
        apply the same method to extract hypernyms of entities in order to improve the performance of a question answering system.
        Ritter et al. (2009)
        propose a method based on patterns to find hypernyms on arbitrary noun phrases.
They use a support vector machine classifier to identify the correct hypernyms from the candidates that match the patterns.
As our experiments show, pattern-based methods suffer from low recall because of the low coverage of patterns.
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Besides
        Kotlerman et al. (2010)
        and
        Lenci and Benotto (2012)
        , other researchers also propose directional distributional similarity methods
        [30, 9, 2, 28, 4]
        .
However, their basic assumption that a hyponym can only be used in contexts where its hypernyms can be used and that a hypernym might be used in all of the contexts where its hyponyms are used may not always rational.
       </p>
      </div>
      <div class="ltx_para" id="S6.p5">
       <p class="ltx_p">
        Snow et al. (2006)
        provides a global optimization scheme for extending WordNet, which is different from the above-mentioned pairwise relationships identification methods.
       </p>
      </div>
      <div class="ltx_para" id="S6.p6">
       <p class="ltx_p">
        Word embeddings have been successfully applied in many applications, such as in sentiment analysis
        [26]
        , paraphrase detection
        [25]
        , chunking, and named entity recognition
        [29, 5]
        .
These applications mainly utilize the representing power of word embeddings to alleviate the problem of data sparsity.
        Mikolov et al. (2013a)
        and
        Mikolov et al. (2013b)
        further observe that the semantic relationship of words can be induced by performing simple algebraic operations with word vectors.
Their work indicates that word embeddings preserve some interesting linguistic regularities, which might provide support for many applications.
In this paper, we improve on their work by learning multiple linear projections in the embedding space, to model hypernym–hyponym relationships within different clusters.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
