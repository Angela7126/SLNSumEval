<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   A Robust Approach to Aligning Heterogeneous Lexical Resources.
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
       Lexical resource alignment has been an active field of research over the last decade.
However, prior methods for aligning lexical resources have been either specific to a particular pair of resources, or heavily dependent on the availability of hand-crafted alignment data for the pair of resources to be aligned.
Here we present a unified approach that can be applied to an arbitrary pair of lexical resources, including machine-readable dictionaries with no network structure.
Our approach leverages a similarity measure that enables the structural comparison of senses across lexical resources, achieving state-of-the-art performance on the task of aligning WordNet to three different collaborative resources: Wikipedia, Wiktionary and OmegaWiki.
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
        Lexical resources are repositories of machine-readable knowledge that can be used in virtually any Natural Language Processing task. Notable examples are WordNet, Wikipedia and, more recently, collaboratively-curated resources such as OmegaWiki and Wiktionary
        [13]
        . On the one hand, these resources are heterogeneous in design, structure and content, but, on the other hand, they often provide complementary knowledge which we would like to see integrated. Given the large scale this intrinsic issue can only be addressed automatically, by means of lexical resource alignment algorithms.
Owing to its ability to bring together features like multilinguality and increasing coverage, over the past few years resource alignment has proven beneficial to a wide spectrum of tasks, such as Semantic Parsing
        [33]
        , Semantic Role Labeling
        [28]
        , and Word Sense Disambiguation
        [25]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Nevertheless, when it comes to aligning textual definitions in different resources, the lexical approach
        [32, 5, 11]
        falls short because of the potential use of totally different wordings to define the same concept. Deeper approaches leverage semantic similarity to go beyond the surface realization of definitions
        [26, 20, 27]
        .
While providing good results in general, these approaches fail when the definitions of a given word are not of adequate quality and expressiveness to be distinguishable from one another.
When a lexical resource can be viewed as a semantic graph, as with WordNet or Wikipedia, this limit can be overcome by means of alignment algorithms that exploit the network structure to determine the similarity of concept pairs.
However, not all lexical resources provide explicit semantic relations between concepts and, hence, machine-readable dictionaries like Wiktionary have first to be transformed into semantic graphs before such graph-based approaches can be applied to them.
To do this, recent work has proposed graph construction by monosemous linking, where a concept is linked to all the concepts associated with the monosemous words in its definition
        [17]
        .
However, this alignment method still involves tuning of parameters which are highly dependent on the characteristics of the generated graphs and, hence, requires hand-crafted sense alignments for the specific pair of resources to be aligned, a task which has to be replicated every time the resources are updated.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper we propose a unified approach to aligning arbitrary pairs of lexical resources which is independent of their specific structure.
Thanks to a novel modeling of the sense entries and an effective ontologization algorithm, our approach also fares well when resources lack relational structure or pair-specific training data is absent, meaning that it is applicable to arbitrary pairs without adaptation.
We report state-of-the-art performance when aligning WordNet to Wikipedia, OmegaWiki and Wiktionary.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Resource Alignment
      </h2>
      <div class="ltx_paragraph" id="S2.SS0.SSS0.P1">
       <h5 class="ltx_title ltx_title_paragraph">
        Preliminaries.
       </h5>
       <div class="ltx_para" id="S2.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         Our approach for aligning lexical resources exploits the graph structure of each resource. Therefore, we assume that a lexical resource
         L
         can be represented as an undirected graph
         G=(V,E)
         where
         V
         is the set of nodes, i.e., the concepts defined in the resource, and
         E
         is the set of undirected edges, i.e., semantic relations between concepts. Each concept
         c∈V
         is associated with a set of lexicalizations
         ℒG⁢(c)={w1,w2,…,wn}
         .
For instance, WordNet can be readily represented as an undirected graph
         G
         whose nodes are synsets and edges are modeled after the relations between synsets defined in WordNet (e.g., hypernymy, meronymy, etc.), and
         ℒG
         is the mapping between each synset node and the set of synonyms which express the concept.
However, other resources such as Wiktionary do not provide semantic relations between concepts and, therefore, have first to be transformed into semantic networks before they can be aligned using our alignment algorithm.
We explain in Section
         3
         how a semi-structured resource which does not exhibit a graph structure can be transformed into a semantic network.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S2.SS0.SSS0.P2">
       <h5 class="ltx_title ltx_title_paragraph">
        Alignment algorithm.
       </h5>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         Given a pair of lexical resources
         L1
         and
         L2
         , we align each concept in
         L1
         by mapping it to its corresponding concept(s) in the target lexicon
         L2
         .
Algorithm
         2
         formalizes the alignment process: the algorithm takes as input the semantic graphs
         G1
         and
         G2
         corresponding to the two resources, as explained above, and produces as output an alignment in the form of a set
         A
         of concept pairs.
The algorithm iterates over all concepts
         c1∈V1
         and, for each of them, obtains the set of concepts
         C⊂V2
         , which can be considered as alignment candidates for
         c1
         (line
         2
         ).
For a concept
         c1
         , alignment candidates in
         G2
         usually consist of every concept
         c2∈V2
         that shares at least one lexicalization with
         c1
         in the same part of speech tag, i.e.,
         ℒG1⁢(c1)∩ℒG2⁢(c2)≠∅
         [31, 20]
         .
Once the set of target candidates
         C
         for a source concept
         c1
         is obtained, the alignment task can be cast as that of identifying those concepts in
         C
         to which
         c1
         should be aligned.
To do this, the algorithm calculates the similarity between
         c1
         and each
         c2∈C
         (line
         2
         ).
If their similarity score exceeds a certain value denoted by
         θ
         (line
         2
         ), the two concepts
         c1
         and
         c2
         are aligned and the pair
         (c1,c2)
         is added to
         A
         (line
         2
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         Different resource alignment techniques usually vary in the way they compute the similarity of a pair of concepts across two resources (line
         2
         in Algorithm
         2
         ).
In the following, we present our novel approach for measuring the similarity of concept pairs.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p3">
        <p class="ltx_p">
         [t!]
         Lexical Resource Aligner
         <span class="ltx_text ltx_font_small">
          [1]
          <span class="ltx_ERROR undefined">
           \REQUIRE
          </span>
          graphs
          <math alttext="H=(V_{H},E_{H})" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m1" xmlns="http://www.w3.org/1998/Math/MathML">
           <mrow>
            <mi mathsize="normal" stretchy="false">
             H
            </mi>
            <mo mathsize="normal" stretchy="false">
             =
            </mo>
            <mrow>
             <mo mathsize="small" stretchy="false">
              (
             </mo>
             <mrow>
              <msub>
               <mi mathsize="normal" stretchy="false">
                V
               </mi>
               <mi mathsize="normal" stretchy="false">
                H
               </mi>
              </msub>
              <mo mathsize="small" stretchy="false">
               ,
              </mo>
              <msub>
               <mi mathsize="normal" stretchy="false">
                E
               </mi>
               <mi mathsize="normal" stretchy="false">
                H
               </mi>
              </msub>
             </mrow>
             <mo mathsize="small" stretchy="false">
              )
             </mo>
            </mrow>
           </mrow>
          </math>
          ,
          <math alttext="G_{1}=(V_{1},E_{1})" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m2" xmlns="http://www.w3.org/1998/Math/MathML">
           <mrow>
            <msub>
             <mi mathsize="normal" stretchy="false">
              G
             </mi>
             <mn mathsize="normal" stretchy="false">
              1
             </mn>
            </msub>
            <mo mathsize="normal" stretchy="false">
             =
            </mo>
            <mrow>
             <mo mathsize="small" stretchy="false">
              (
             </mo>
             <mrow>
              <msub>
               <mi mathsize="normal" stretchy="false">
                V
               </mi>
               <mn mathsize="normal" stretchy="false">
                1
               </mn>
              </msub>
              <mo mathsize="small" stretchy="false">
               ,
              </mo>
              <msub>
               <mi mathsize="normal" stretchy="false">
                E
               </mi>
               <mn mathsize="normal" stretchy="false">
                1
               </mn>
              </msub>
             </mrow>
             <mo mathsize="small" stretchy="false">
              )
             </mo>
            </mrow>
           </mrow>
          </math>
          and
          <math alttext="G_{2}=(V_{2},E_{2})" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m3" xmlns="http://www.w3.org/1998/Math/MathML">
           <mrow>
            <msub>
             <mi mathsize="normal" stretchy="false">
              G
             </mi>
             <mn mathsize="normal" stretchy="false">
              2
             </mn>
            </msub>
            <mo mathsize="normal" stretchy="false">
             =
            </mo>
            <mrow>
             <mo mathsize="small" stretchy="false">
              (
             </mo>
             <mrow>
              <msub>
               <mi mathsize="normal" stretchy="false">
                V
               </mi>
               <mn mathsize="normal" stretchy="false">
                2
               </mn>
              </msub>
              <mo mathsize="small" stretchy="false">
               ,
              </mo>
              <msub>
               <mi mathsize="normal" stretchy="false">
                E
               </mi>
               <mn mathsize="normal" stretchy="false">
                2
               </mn>
              </msub>
             </mrow>
             <mo mathsize="small" stretchy="false">
              )
             </mo>
            </mrow>
           </mrow>
          </math>
          , the similarity threshold
          <math alttext="\theta" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m4" xmlns="http://www.w3.org/1998/Math/MathML">
           <mi mathsize="normal" stretchy="false">
            θ
           </mi>
          </math>
          , and the combination parameter
          <math alttext="\beta" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m5" xmlns="http://www.w3.org/1998/Math/MathML">
           <mi mathsize="normal" stretchy="false">
            β
           </mi>
          </math>
          <span class="ltx_ERROR undefined">
           \ENSURE
          </span>
          <math alttext="A" class="ltx_Math" display="inline" id="S2.SS0.SSS0.P2.p3.m6" xmlns="http://www.w3.org/1998/Math/MathML">
           <mi mathsize="normal" stretchy="false">
            A
           </mi>
          </math>
          , the set of all aligned concept pairs
         </span>
        </p>
       </div>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p4">
        <p class="ltx_p">
         A←∅
        </p>
       </div>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p5">
        <p class="ltx_p">
         concept c1∈V1
C ← getCandidates(c1,V2)
concept c2∈C
s⁢i⁢m ← calculateSimilarity(H,G1,G2,c1,c2,β)
s⁢i⁢m&gt;θ
A ← A ∪ {(c1,c2)}
\ENDFOR
        </p>
       </div>
       <span class="ltx_ERROR undefined">
        \RETURN
       </span>
       <div class="ltx_para" id="S2.SS0.SSS0.P2.p6">
        <p class="ltx_p">
         A
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Measuring the Similarity of Concepts
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Figure
         1
         illustrates the procedure underlying our cross-resource concept similarity measurement technique.
As can be seen, the approach consists of two main components:
         definitional similarity
         and
         structural similarity
         .
Each of these components gets, as its input, a pair of concepts belonging to two different semantic networks and produces a similarity score.
These two scores are then combined into an overall score (part (e) of Figure
         1
         ) which quantifies the semantic similarity of the two input concepts
         c1
         and
         c2
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The definitional similarity component computes the similarity of two concepts in terms of the similarity of their definitions, a method that has also been used in previous work for aligning lexical resources
         [27, 12]
         .
In spite of its simplicity, the mere calculation of the similarity of concept definitions provides a strong baseline, especially for cases where the definitional texts for a pair of concepts to be aligned are lexically similar, yet distinguishable from the other definitions.
However, as mentioned in the introduction, definition similarity-based techniques fail at identifying the correct alignments in cases where different wordings are used or definitions are not of high quality.
The structural similarity component, instead, is a novel graph-based similarity measurement technique which calculates the similarity between a pair of concepts across the semantic networks of the two resources by leveraging the semantic structure of those networks.
This component goes beyond the surface realization of concepts, thus providing a deeper measure of concept similarity.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The two components share the same backbone (parts (b) and (d) of Figure
         1
         ), but differ in some stages (parts (a) and (c) in Figure
         1
         ).
In the following, we explain all the stages involved in the two components (gray blocks in the figure).
        </p>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.1
         </span>
         Semantic signature generation
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS1.p1">
         <p class="ltx_p">
          The aim of this stage is to model a given concept or set of concepts through a vectorial semantic representation, which we refer to as the
          semantic signature
          of the input.
We utilized Personalized PageRank
          [10, ppr]
          , a random walk graph algorithm, for calculating semantic signatures.
The original PageRank (
          pr
          ) algorithm
          [3]
          computes, for a given graph, a single vector wherein each node is associated with a weight denoting its structural importance in that graph.
          ppr
          is a variation of
          pr
          where the computation is biased towards a set of initial nodes in order to capture the notion of importance with respect to those particular nodes.
          ppr
          has been previously used in a wide variety of tasks such as definition similarity-based resource alignment
          [27]
          , textual semantic similarity
          [14, 30]
          , Word Sense Disambiguation
          [1, 6]
          and semantic text categorization
          [24]
          .
When applied to a semantic graph by initializing the random walks from a set of concepts (nodes),
          ppr
          yields a vector in which each concept is associated with a weight denoting its semantic relevance to the initial concepts.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS1.p2">
         <p class="ltx_p">
          Formally, we first represent a semantic network consisting of
          N
          concepts as a row-stochastic transition matrix
          𝐌∈ℝN×N
          .
The cell
          (i,j)
          in the matrix denotes the probability of moving from a concept
          i
          to
          j
          in the graph: 0 if no edge exists from
          i
          to
          j
          and
          1/d⁢e⁢g⁢r⁢e⁢e⁢(i)
          otherwise.
Then the
          ppr
          vector, hence the semantic signature
          𝒮𝐯
          of vector
          𝐯
          is the unique solution to the linear system:
          𝒮𝐯=(1-α)⁢𝐯+α⁢𝐌⁢𝒮𝐯
          , where
          𝐯
          is the personalization vector of size
          N
          in which all the probability mass is put on the concepts for which a semantic signature is to be computed and
          α
          is the damping factor, which is usually set to 0.85
          [3]
          .
We used the
          ukb
          off-the-shelf implementation of
          ppr
          .
         </p>
        </div>
        <div class="ltx_paragraph" id="S2.SS1.SSS1.P1">
         <h5 class="ltx_title ltx_title_paragraph">
          Definitional similarity signature.
         </h5>
         <div class="ltx_para" id="S2.SS1.SSS1.P1.p1">
          <p class="ltx_p">
           In the definitional similarity component, the two concepts
           c1
           and
           c2
           are first represented by their corresponding definitions
           d1
           and
           d2
           in the respective resources
           L1
           and
           L2
           (Figure
           1
           (a), top).
To improve expressiveness, we follow
           Niemann and Gurevych (2011)
           and further extend
           di
           with all the word forms associated with concept
           ci
           and its neighbours, i.e., the union of all lexicalizations
           ℒGi⁢(x)
           for all concepts
           x∈{c′∈Vi:(c,c′)∈Ei}∪{c}
           , where
           Ei
           is the set of edges in
           Gi
           .
In this component the personalization vector
           𝐯i
           is set by uniformly distributing the probability mass over the nodes corresponding to the senses of all the content words in the extended definition of
           di
           according to the sense inventory of a semantic network
           H
           .
We use the same semantic graph
           H
           for computing the semantic signatures of both definitions.
Any semantic network with a dense relational structure, providing good coverage of the words appearing in the definitions, is a suitable candidate for
           H
           .
For this purpose we used the WordNet
           [7]
           graph which was further enriched by connecting each concept to all the concepts appearing in its disambiguated gloss.
          </p>
         </div>
        </div>
        <div class="ltx_paragraph" id="S2.SS1.SSS1.P2">
         <h5 class="ltx_title ltx_title_paragraph">
          Structural similarity signature.
         </h5>
         <div class="ltx_para" id="S2.SS1.SSS1.P2.p1">
          <p class="ltx_p">
           In the structural similarity component (Figure
           1
           (b), bottom), the semantic signature for each concept
           ci
           is computed by running the
           ppr
           algorithm on its corresponding graph
           Gi
           , hence a different
           𝐌i
           is built for each of the two concepts.
          </p>
         </div>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.2
         </span>
         Signature unification
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS2.p1">
         <p class="ltx_p">
          As mentioned earlier, semantic signatures are vectors with dimension equal to the number of nodes in the semantic graph.
Since the structural similarity signatures
          𝒮𝐯1
          and
          𝒮𝐯2
          are calculated on different graphs and thus have different dimensions, we need to make them comparable by unifying them.
We therefore propose an approach (part (c) of Figure
          1
          ) that finds a common ground between the two signatures: to this end we consider all the concepts associated with monosemous words in the two signatures as landmarks and restrict the two signatures exclusively to those common concepts. Leveraging monosemous words as bridges between two signatures is a particularly reliable technique as typically a significant portion of all words in a lexicon are monosemous.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS2.p2">
         <p class="ltx_p">
          Formally, let
          ℐG⁢(w)
          be an inventory mapping function that maps a term
          w
          to the set of concepts which are expressed by
          w
          in graph
          G
          .
Then, given two signatures
          𝒮𝐯1
          and
          𝒮𝐯2
          , computed on the respective graphs
          G1
          and
          G2
          , we first obtain the set
          ℳ
          of words that are monosemous according to both semantic networks, i.e.,
          ℳ={w:|ℐG1⁢(w)|=1∧|ℐG2⁢(w)|=1}
          .
We then transform each of the two signatures
          𝒮𝐯i
          into a new sub-signature
          𝒮𝐯i′
          whose dimension is
          |ℳ|
          :
the
          kt⁢h
          component of
          𝒮𝐯i′
          corresponds to the weight in
          𝒮𝐯i
          of the only concept of
          wk
          in
          ℐGi⁢(wk)
          .
As an example, assume we are given two semantic signatures computed for two concepts in WordNet and Wiktionary.
Also, consider the noun
          tradeoff
          which is monosemous according to both these resources.
Then, each of the two unified sub-signatures will contain a component whose weight is determined by the weight of the only concept associated with
          tradeoffn
          in the corresponding semantic signature.
As a result of the unification process, we obtain a pair of equally-sized semantic signatures with comparable components.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.3
         </span>
         Signature comparison
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS3.p1">
         <p class="ltx_p">
          Having at hand the semantic signatures for the two input concepts, we proceed to comparing them (part (d) in Figure
          1
          ).
We leverage a non-parametric measure proposed by
          Pilehvar et al. (2013)
          which first transforms each signature into a list of sorted elements and then calculates the similarity on the basis of the average ranking of elements across the two lists:
         </p>
         S⁢i⁢m⁢(𝒮𝐯1,𝒮𝐯2)=∑i=1|T|(ri1+ri2)-1∑i=1|T|(2⁢i)-1

(1)
         <p class="ltx_p">
          where
          T
          is the intersection of all concepts with non-zero probability in the two signatures and
          rij
          is the rank of the
          it⁢h
          entry in the
          jt⁢h
          sorted list.
The denominator is a normalization factor to guarantee a maximum value of one.
The method penalizes the differences in the higher rankings more than it does for the lower ones.
The measure was shown to outperform the conventional cosine distance when comparing different semantic signatures in multiple textual similarity tasks
          [30]
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS4">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.4
         </span>
         Score combination
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS4.p1">
         <p class="ltx_p">
          Finally (part (e) of Figure
          1
          ), we calculate the overall similarity between two concepts as a linear combination of their definitional and structural similarities:
          β⁢S⁢i⁢md⁢e⁢f⁢(𝒮𝐯1,𝒮𝐯2)+(1-β)⁢S⁢i⁢ms⁢t⁢r⁢(𝒮𝐯1,𝒮𝐯2).
          In Section
          4.2.1
          , we explain how we set, in our experiments, the values of
          β
          and the similarity threshold
          θ
          (cf. alignment algorithm in Section
          2
          ).
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
       Lexical Resource Ontologization
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In Section
        2
        , we presented our approach for aligning lexical resources.
However, the approach assumes that the input resources can be viewed as semantic networks, which seems to limit its applicability to structured resources only.
In order to address this issue and hence generalize our alignment approach to any given lexical resource, we propose a method for transforming a given machine-readable dictionary into a semantic network, a process we refer to as
        ontologization
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Our ontologization algorithm takes as input a lexicon
        L
        and outputs a semantic graph
        G=(V,E)
        where, as already defined in Section
        2
        ,
        V
        is the set of concepts in
        L
        and
        E
        is the set of semantic relations between these concepts.
Introducing relational links into a lexicon can be achieved in different ways.
A first option is to extract binary relations between pairs of words from raw text. Both words in these relations, however, should be disambiguated according to the given lexicon
        [29]
        , making the task particularly prone to mistakes due to the high number of possible sense pairings.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Here, we take an alternative approach which requires disambiguation on the target side only, hence reducing the size of the search space significantly.
We first create the empty undirected graph
        GL=(V,E)
        such that
        V
        is the set of concepts in
        L
        and
        E=∅
        .
For each source concept
        c∈V
        we create a bag of content words
        W={w1,…,wn}
        which includes all the content words in its definition
        d
        and, if available, additional related words obtained from lexicon relations (e.g., synonyms in Wiktionary).
The problem is then cast as a disambiguation task whose goal is to identify the intended sense of each word
        wi∈W
        according to the sense inventory of
        L
        : if
        wi
        is monosemous, i.e.,
        |{ℐGL⁢(wi)}|=1
        , we connect our source concept
        c
        to the only sense
        cwi
        of
        wi
        and set
        E:=E∪{{c,cwi}}
        ; else,
        wi
        has multiple senses in
        L
        . In this latter case, we choose the most appropriate concept
        ci∈ℐGL⁢(wi)
        by finding the maximal similarity between the definition of
        c
        and the definitions of each sense of
        wi
        .
To do this, we apply our definitional similarity measure introduced in Section
        2.1
        .
Having found the intended sense
        c^wi
        of
        wi
        , we add the edge
        {c,c^wi}
        to
        E
        .
As a result of this procedure, we obtain a semantic graph representation
        G
        for the lexicon
        L
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        As an example, consider the 4
        t⁢h
        sense of the noun
        cone
        in Wiktionary (i.e.,
        cone4n
        ) which is defined as
        “The fruit of a conifer”
        .
The definition contains two content words:
        fruitn
        and
        conifern
        .
The latter word is monosemous in Wiktionary, hence we directly connect
        cone4n
        to the only sense of
        conifern
        .
The noun
        fruit
        , however, has 5 senses in Wiktionary.
We therefore measure the similarity between the definition of
        cone4n
        and all the 5 definitions of
        fruit
        and introduce a link from
        cone4n
        to the sense of fruit which yields the maximal similarity value (defined as
        “(botany) The seed-bearing part of a plant…”
        ).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiments
      </h2>
      <div class="ltx_paragraph" id="S4.SS1.SSS4.P1">
       <h5 class="ltx_title ltx_title_paragraph">
        Lexical resources.
       </h5>
       <div class="ltx_para" id="S4.SS1.SSS4.P1.p1">
        <p class="ltx_p">
         To enable a comparison with the state of the art, we followed
         Matuschek and Gurevych (2013)
         and performed an alignment of WordNet synsets (
         wn
         ) to three different collaboratively-constructed resources: Wikipedia (
         wp
         ), Wiktionary (
         wt
         ), and OmegaWiki (
         ow
         ).
We utilized the DKPro software
         [35, 9]
         to access the information in the foregoing three resources.
For
         wp
         ,
         wt
         ,
         ow
         we used the dump versions
         20090822
         ,
         20131002
         , and
         20131115
         , respectively.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS1.SSS4.P2">
       <h5 class="ltx_title ltx_title_paragraph">
        Evaluation measures.
       </h5>
       <div class="ltx_para" id="S4.SS1.SSS4.P2.p1">
        <p class="ltx_p">
         We followed previous work
         [25, 17]
         and evaluated the alignment performance in terms of four measures: precision, recall, F1, and accuracy.
Precision is the fraction of correct alignment judgments returned by the system and recall is the fraction of alignment judgments in the gold standard dataset that are correctly returned by the system.
F1 is the harmonic mean of precision and recall.
We also report results for accuracy which, in addition to true positives, takes into account true negatives, i.e., pairs which are correctly judged as unaligned.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS1.SSS4.P3">
       <h5 class="ltx_title ltx_title_paragraph">
        Lexicons and semantic graphs.
       </h5>
       <div class="ltx_para" id="S4.SS1.SSS4.P3.p1">
        <p class="ltx_p">
         Here, we describe how the four semantic graphs for our four lexical resources (i.e.,
         wn
         ,
         wp
         ,
         wt
         ,
         ow
         ) were constructed.
As mentioned in Section
         2.1.1
         , we build the
         wn
         graph by including all the synsets and semantic relations defined in WordNet (e.g., hypernymy and meronymy) and further populate the relation set by connecting a synset to all the other synsets that appear in its disambiguated gloss.
For
         wp
         , we used the graph provided by
         Matuschek and Gurevych (2013)
         , constructed by directly connecting an article (concept) to all the hyperlinks in its first paragraph, together with the category links.
Our
         wn
         and
         wp
         graphs have 118K and 2.8M nodes, respectively, with the average node degree being roughly 9 in both resources.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.SSS4.P3.p2">
        <p class="ltx_p">
         The other two resources, i.e.,
         wt
         and
         ow
         , do not provide a reliable network of semantic relations, therefore we used our ontologization approach to construct their corresponding semantic graphs.
We report, in the following subsection, the experiments carried out to assess the accuracy of our ontologization method, together with the statistics of the obtained graphs for
         wt
         and
         ow
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Ontologization Experiments
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         For ontologizing
         wt
         and
         ow
         , the bag of content words
         W
         is given by the content words in sense definitions and, if available, additional related words obtained from lexicon relations (see Section
         3
         ).
In
         wt
         , both of these are in word surface form and hence had to be disambiguated.
For
         ow
         , however, the encoded relations, though relatively small in number, are already disambiguated and, therefore, the ontologization was just performed on the definition’s content words.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         The resulting graphs for
         wt
         and
         ow
         contain 430K and 48K nodes, respectively, each providing more than 95% coverage of concepts, with the average node degree being around 10 for both resources.
We present in Table
         1
         , for
         wt
         and
         ow
         , the total number of edges together with their distribution across types (i.e., ambiguous and unambiguous) and sources (i.e., definitions and relations) from which candidate words were obtained.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         The edges obtained from unambiguous entries are essentially sense disambiguated on both sides whereas those obtained from ambiguous terms are a result of our similarity-based disambiguation.
Hence, given that a large portion of edges came from ambiguous words (see Table
         1
         ), we carried out an experiment to evaluate the accuracy of our disambiguation method.
To this end, we took as our benchmark the dataset provided by
         Meyer and Gurevych (2010)
         for evaluating relation disambiguation in
         wt
         .
The dataset contains 394 manually-disambiguated relations.
We compared our similarity-based disambiguation approach against the state of the art on this dataset, i.e., the
         wktwsd
         system, which is a
         wt
         relation disambiguation algorithm based on a series of rules
         [22]
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         Table
         2
         shows the performance of our disambiguation method, together with that of
         wktwsd
         , in terms of Precision (P), Recall (R), F1, and accuracy.
The “Human” row corresponds to the inter-rater F1 and accuracy scores, i.e., the upperbound performance on this dataset, as calculated by
         Meyer and Gurevych (2010)
         .
As can be seen, our method proves to be very accurate, surpassing the performance of the
         wktwsd
         system in terms of precision, F1, and accuracy.
This is particularly interesting as the
         wktwsd
         system uses a rule-based technique specific to relation disambiguation in
         wt
         , whereas our method is resource independent and can be applied to arbitrary words in the definition of any concept.
We also note that the graph constructed by
         Meyer and Gurevych (2010)
         had an average node degree of around 1.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         More recently,
         Matuschek and Gurevych (2013)
         leveraged monosemous linking (cf. Section
         5
         ) in order to create denser semantic graphs for
         ow
         and
         wt
         .
Our approach, however, thanks to the connections obtained through ambiguous words, can provide graphs with significantly higher coverage.
As an example, for
         wt
         ,
         Matuschek and Gurevych (2013)
         generated a graph where around 30% of the nodes were in isolation, whereas this number drops to around 5% in our corresponding graph.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p6">
        <p class="ltx_p">
         These results show that our ontologization approach can be used to obtain dense semantic graph representations of lexical resources, while at the same time preserving a high level of accuracy.
Now that all the four resources are transformed into semantic graphs, we move to our alignment experiments.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Alignment Experiments
       </h3>
       <div class="ltx_subsubsection" id="S4.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.2.1
         </span>
         Experimental setup
        </h4>
        <div class="ltx_paragraph" id="S4.SS2.SSS1.P1">
         <h5 class="ltx_title ltx_title_paragraph">
          Datasets.
         </h5>
         <div class="ltx_para" id="S4.SS2.SSS1.P1.p1">
          <p class="ltx_p">
           As our benchmark we tested on the gold standard datasets used in
           Matuschek and Gurevych (2013)
           for three alignment tasks: WordNet-Wikipedia (
           wn
           -
           wp
           ), WordNet-Wiktionary (
           wn
           -
           wt
           ), and WordNet-OmegaWiki (
           wn
           -
           ow
           ).
However, the dataset for
           wn
           -
           ow
           was originally built for the German language and, hence, was missing many English
           ow
           concepts that could be considered as candidate target alignments.
We therefore fixed the dataset for the English language and reproduced the performance of previous work on the new dataset.
The three datasets contained 320, 484, and 315
           wn
           concepts that were manually mapped to their corresponding concepts in
           wp
           ,
           wt
           , and
           ow
           , respectively.
          </p>
         </div>
        </div>
        <div class="ltx_paragraph" id="S4.SS2.SSS1.P2">
         <h5 class="ltx_title ltx_title_paragraph">
          Configurations.
         </h5>
         <div class="ltx_para" id="S4.SS2.SSS1.P2.p1">
          <p class="ltx_p">
           Recall from Section
           2
           that our resource alignment technique has two parameters: the similarity threshold
           θ
           and the combination parameter
           β
           , both defined in [0, 1].
We performed experiments with three different configurations:
          </p>
         </div>
         <div class="ltx_para" id="S4.SS2.SSS1.P2.p2">
          <ul class="ltx_itemize" id="I1">
           <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
            <span class="ltx_tag ltx_tag_itemize">
             •
            </span>
            <div class="ltx_para" id="I1.i1.p1">
             <p class="ltx_p">
              Unsupervised
              , where the two parameters are set to their middle values (i.e., 0.5), hence, no tuning is performed for either of the parameters. In this case, both the definitional and structural similarity scores are treated as equally important and two concepts are aligned if their overall similarity exceeds the middle point of the similarity scale.
             </p>
            </div>
           </li>
           <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
            <span class="ltx_tag ltx_tag_itemize">
             •
            </span>
            <div class="ltx_para" id="I1.i2.p1">
             <p class="ltx_p">
              Tuning
              , where we follow
              Matuschek and Gurevych (2013)
              and tune the parameters on a subset of the dataset comprising 100 items.
             </p>
            </div>
           </li>
           <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
            <span class="ltx_tag ltx_tag_itemize">
             •
            </span>
            <div class="ltx_para" id="I1.i3.p1">
             <p class="ltx_p">
              Cross-validation
              , where a 5-fold cross validation is carried out to find the optimal values for the parameters, a technique used in most of the recent alignment methods
              [27, 21, 17]
              .
             </p>
            </div>
           </li>
          </ul>
         </div>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS2.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.2.2
         </span>
         Results
        </h4>
        <div class="ltx_para" id="S4.SS2.SSS2.p1">
         <p class="ltx_p">
          We show in Table
          3
          the alignment performance of different systems on the task of aligning
          wn
          -
          wp
          ,
          wn
          -
          wt
          , and
          wn
          -
          ow
          in terms of Precision (P), Recall (R), F1, and Accuracy.
The
          sb
          system corresponds to the state-of-the-art definition similarity approaches for
          wn
          -
          wp
          [27]
          ,
          wn
          -
          wt
          [20]
          , and
          wn
          -
          ow
          [9]
          .
          dwsa
          stands for Dijkstra-WSA, the state-of-the-art graph-based alignment approach of
          Matuschek and Gurevych (2013)
          .
The authors also provided results for SB+Dijkstra-WSA, a hybrid system where
          dwsa
          was tuned for high precision and, in the case when no alignment target could be found, the algorithm fell back on
          sb
          judgments.
We also show the results for this system as
          sb+dwsa
          in the table.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS2.p2">
         <p class="ltx_p">
          For our approach (SemAlign) we show the results of six different runs each corresponding to a different setting.
The first three (middle part of the table) correspond to the results obtained with the three configurations of SemAlign: unsupervised, with tuning on subset, and cross-validation (see Section
          4.2.1
          ).
In addition to these, we performed experiments where the two parameters of SemAlign were tuned on pair-independent training data, i.e., a training dataset for a pair of resources different from the one being aligned.
For this setting, we used the whole dataset of the corresponding resource pair to tune the two parameters of our system.
We show the results for this setting in the bottom part of the table (last three lines).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS2.p3">
         <p class="ltx_p">
          The main feature worth remarking upon is the consistency in the results across different resource pairs:
the unsupervised system gains the best recall among the three configurations (with the improvement over
          sb+dwsa
          being always statistically significant
          ) whereas tuning, both on a subset or through cross-validation, consistently leads to the best performance in terms of F1 and accuracy (with the latter being statistically significant with respect to
          sb+dwsa
          on
          wn
          -
          wp
          and
          wn
          -
          wt
          ).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS2.p4">
         <p class="ltx_p">
          Moreover, the unsupervised system proves to be very robust inasmuch as it provides competitive results on all the three datasets, while it surpasses the performance of
          sb+dwsa
          on
          wn
          -
          wt
          .
This is particularly interesting as the latter system involves tuning of several parameters, whereas SemAlign, in its unsupervised configuration, does not need any training data nor does it involve any tuning.
In addition, as can be seen in the table, SemAlign benefits from pair-independent training data in most cases across the three resource pairs with performance surpassing that of
          sb+dwsa
          , a system which is dependent on pair-specific training data.
The consistency in the performance of SemAlign in its different configurations and across different resource pairs indicates its robustness and shows that our system can be utilized effectively for aligning any pair of lexical resources, irrespective of their structure or availability of training data.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS2.p5">
         <p class="ltx_p">
          The system performance is generally higher on the alignment task for
          wp
          compared to
          wt
          and
          ow
          .
We attribute this difference to the dictionary nature of the latter two, where sense distinctions are more fine-grained, as opposed to the relatively concrete concepts in the
          wp
          encyclopedia.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Similarity Measure Analysis
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We explained in Section
         2.1
         that our concept similarity measure consists of two components: the definitional and the structural similarities.
Measuring the similarity of two concepts in terms of their definitions has been investigated in previous work
         [27, 12]
         .
The structural similarity component of our approach, however, is novel, but at the same time one of the very few measures which enables the computation of the similarity of concepts across two resources directly and independently of the similarity of their definitions.
A comparable approach is the Dijkstra-WSA proposed by
         Matuschek and Gurevych (2013)
         which, as also mentioned earlier in the Introduction, first connects the two resources’ graphs by leveraging monosemous linking and then aligns two concepts across the two graphs on the basis of their shortest distance.
To gain more insight into the effectiveness of our structural similarity measure in comparison to the Dijkstra-WSA method, we carried out an experiment where our alignment system used only the structural similarity component, a variant of our system we refer to as SemAlign
         s⁢t⁢r
         .
Both systems (i.e., SemAlign
         s⁢t⁢r
         and Dijkstra-WSA) were tuned on 100-item subsets of the corresponding datasets.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         We show in Table
         4
         the performance of the two systems on our three datasets.
As can be seen in the table, SemAlign
         s⁢t⁢r
         consistently improves over Dijkstra-WSA according to recall, F1 and accuracy with all the differences in recall and accuracy being statistically significant (p
         &lt;
         0.05).
The improvement is especially noticeable for pairs involving either
         wt
         or
         ow
         where, thanks to the relatively denser semantic graphs obtained by means of our ontologization technique, the gap in F1 is about 0.23 (
         wn
         -
         wt
         ) and 0.15 (
         wn
         -
         ow
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         In addition, as we mentioned earlier, for
         wn
         -
         wp
         we used the same graph as that of Dijkstra-WSA, since both
         wn
         and
         wp
         provide a full-fledged semantic network and thus neither needed to be ontologized.
Therefore, the considerable performance improvement over Dijkstra-WSA on this resource pair shows the effectiveness of our novel concept similarity measure independently of the underlying semantic network.
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
      <div class="ltx_paragraph" id="S5.SS3.SSS2.P1">
       <h5 class="ltx_title ltx_title_paragraph">
        Resource ontologization.
       </h5>
       <div class="ltx_para" id="S5.SS3.SSS2.P1.p1">
        <p class="ltx_p">
         Having lexical resources represented as semantic networks is highly beneficial.
A good example is WordNet, which has been exploited as a semantic network in dozens of NLP tasks
         [7]
         . A recent prominent case is Wikipedia
         [18, 13]
         which, thanks to its inter-article hyperlink structure, provides a rich backbone for structuring additional information
         [2, 34, 23, 8]
         .
However, there are many large-scale resources, such as Wiktionary for instance, which by their very nature are not in the form of a graph.
This is usually the case with machine-readable dictionaries, where structuring the resource involves the arduous task of connecting lexicographic senses by means of semantic relations.
Surprisingly, despite their vast potential, little research has been conducted on the automatic ontologization of collaboratively-constructed dictionaries like Wiktionary and OmegaWiki.
         Meyer and Gurevych (2012a)
         and
         Matuschek and Gurevych (2013)
         provided approaches for building graph representations of Wiktionary and OmegaWiki.
The resulting graphs, however, were either sparse or had a considerable portion of the nodes left in isolation.
Our approach, in contrast, aims at transforming a lexical resource into a full-fledged semantic network, hence providing a denser graph with most of its nodes connected.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS3.SSS2.P2">
       <h5 class="ltx_title ltx_title_paragraph">
        Resource alignment.
       </h5>
       <div class="ltx_para" id="S5.SS3.SSS2.P2.p1">
        <p class="ltx_p">
         Aligning lexical resources has been a very active field of research in the last decade.
One of the main objectives in this area has been to enrich existing ontologies by means of complementary information from other resources.
As a matter of fact, most efforts have been concentrated on aligning the
         de facto
         community standard sense inventory, i.e. WordNet, to other resources. These include: the Roget’s thesaurus and Longman Dictionary of Contemporary English
         [15]
         , FrameNet
         [16]
         , VerbNet
         [33]
         or domain-specific terminologies such as the Unified Medical Language System
         [4]
         .
More recently, the growth of collaboratively-constructed resources has seen the development of alignment approaches with Wikipedia
         [32, 2, 34, 31, 25]
         , Wiktionary
         [20]
         and OmegaWiki
         [9]
         .
Last year
         Matuschek and Gurevych (2013)
         proposed Dijkstra-WSA, a graph-based approach relying on shortest paths between two concepts when the two corresponding resources graphs were combined by leveraging monosemous linking.
Their method when backed off with other definition similarity based approaches
         [27, 20]
         , achieved state-of-the-art results on the mapping of WordNet to different collaboratively-constructed resources.
This approach, however, in addition to setting the threshold for the definition similarity component by means of cross validation, also required other parameters to be tuned, such as the allowed path length (
         λ
         ) and the maximum number of edges in a graph.
The optimal value for the
         λ
         parameter varied from one resource pair to another, and even for a specific resource pair it had to be tuned for each configuration.
This made the approach dependent on the training data for the specific pair of resources that were to be aligned.
Instead of measuring the similarity of two concepts on the basis of their distance in the combined graph, our approach models each concept through a rich vectorial representation we refer to as semantic signature and compares the two concepts in terms of the similarity of their semantic signatures.
This rich representation leads to our approach having a good degree of robustness such that it can achieve competitive results even in the absence of training data.
This enables our system to be applied effectively for aligning new pairs of resources for which no training data is available, with state-of-the-art performance.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
