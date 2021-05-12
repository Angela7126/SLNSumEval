<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   ConnotationWordNet: Learning Connotation over the Word+Sense Network.
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
       We introduce
       ConnotationWordNet
       , a connotation lexicon over the network of
       words
       in conjunction with
       senses
       . We formulate the lexicon induction problem as collective inference over pairwise-Markov Random Fields, and present a loopy belief propagation algorithm for inference.
The key aspect of our method is that it is the
       first unified
       approach that assigns the polarity of
       both
       word- and sense-level connotations, exploiting the innate bipartite graph structure encoded in WordNet.
We present comprehensive evaluation to demonstrate the quality and utility of the resulting lexicon in comparison to existing connotation and sentiment lexicons.
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
        We introduce
        ConnotationWordNet
        , a connotation lexicon over the network of
        words
        in conjunction with
        senses
        , as defined in WordNet.
A connotation lexicon, as introduced first by
        Feng et al. (2011)
        , aims to encompass subtle shades of sentiment a word may conjure, even for seemingly objective words such as
        “sculpture”
        ,
        “Ph.D.”
        ,
        “rosettes”
        . Understanding the rich and complex layers of connotation remains to be a challenging task. As a starting point, we study a more feasible task of learning the
        polarity
        of connotation.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        For non-polysemous words, which constitute a significant portion of English vocabulary, learning the
        general
        connotation at the
        word-level
        (rather than at the
        sense-level
        ) would be a natural operational choice. However, for polysemous words, which correspond to most frequently used words, it would be an overly crude assumption that the same connotative polarity should be assigned for all senses of a given word. For example, consider
        “abound”
        , for which lexicographers of WordNet prescribe two different senses:
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           (v)
           abound
           : (be abundant of plentiful; exist in large quantities)
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           (v)
           abound, burst, bristle
           : (be in a state of movement or action)
           “The room abounded with screaming children”
           ;
           “The garden bristled with toddlers”
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        For the first sense, which is the most commonly used sense for
        “abound”
        , the general overtone of the connotation would seem positive. That is, although one can use this sense in both positive and negative contexts, this sense of
        “abound”
        seems to collocate more often with items that are good to be abundant (e.g.,
        “resources”
        ), than unfortunate items being abundant (e.g.,
        “complaints”
        ).
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        However, as for the second sense, for which
        “burst”
        and
        “bristle”
        can be used interchangeably with respect to this particular sense,
        the general overtone is slightly more negative with a touch of unpleasantness, or at least not as positive as that of the first sense. Especially if we look up the WordNet entry for
        “bristle”
        , there are noticeably more negatively connotative words involved in its gloss and examples.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        This word sense issue has been a universal challenge for a range of Natural Language Processing applications, including sentiment analysis. Recent studies have shown that it is fruitful to tease out subjectivity and objectivity corresponding to different senses of the same word, in order to improve computational approaches to sentiment analysis (e.g.
        Pestian et al. (2012)
        ,
        Mihalcea et al. (2012)
        Balahur et al. (2014)
        ). Encouraged by these recent successes, in this study, we investigate if we can attain similar gains if we model the connotative polarity of senses separately.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        There is one potential practical issue we would like to point out in building a sense-level lexical resource, however. End-users of such a lexicon may not wish to deal with Word Sense Disambiguation (WSD), which is known to be often too noisy to be incorporated into the pipeline with respect to other NLP tasks. As a result, researchers often would need to aggregate labels across different senses to derive the word-level label. Although such aggregation is not entirely unreasonable, it does not seem to be the most optimal and principled way of integrating available resources.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        Therefore, in this work, we present the first unified approach that learns
        both
        sense- and word-level connotations simultaneously. This way, end-users will have access to more accurate sense-level connotation labels if needed, while also having access to more general word-level connotation labels.
We formulate the lexicon induction problem as collective inference over pairwise-Markov Random Fields (pairwise-MRF) and derive a loopy belief propagation algorithm for inference.
       </p>
      </div>
      <div class="ltx_para" id="S1.p9">
       <p class="ltx_p">
        The key aspect of our approach is that we exploit the innate bipartite graph structure between words and senses encoded in WordNet. Although our approach seems conceptually natural, previous approaches, to our best knowledge, have not directly exploited these relations between words and senses for the purpose of deriving lexical knowledge over words and senses collectively. In addition, previous studies
(for both sentiment and connotation lexicons) aimed to produce only either of the two aspects of the polarity: word-level or sense-level, while we address both.
       </p>
      </div>
      <div class="ltx_para" id="S1.p10">
       <p class="ltx_p">
        Another contribution of our work is the introduction of loopy belief propagation (loopy-BP) as a lexicon induction algorithm. Loopy-BP in our study achieves statistically significantly better performance over the constraint optimization approaches previously explored. In addition, it runs much faster and it is considerably easier to implement.
Last but not least, by using probabilistic representation of pairwise-MRF in conjunction with Loopy-BP as inference, the resulting solution has the natural interpretation as the intensity of connotation. This contrasts to approaches that seek discrete solutions such as Integer Linear Programming
        [21]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p11">
       <p class="ltx_p">
        ConnotationWordNet
        , the final outcome of our study, is a new lexical resource that has connotation labels over both words and senses following the structure of WordNet. The lexicon is publicly available at:
        http://www.cs.sunysb.edu/~junkang/connotation_wordnet
        .)
       </p>
      </div>
      <div class="ltx_para" id="S1.p12">
       <p class="ltx_p">
        In what follows, we will first describe the network of words and senses (Section
        2
        ), then introduce the representation of the network structure as pairwise Markov Random Fields, and a loopy belief propagation algorithm as collective inference (Section
        3
        ). We then present comprehensive evaluation (Section
        4
        &amp;
        5
        &amp;
        6
        ), followed by related work (Section
        7
        ) and conclusion (Section
        8
        ).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Network of Words and Senses
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The connotation graph, called
        GWord+Sense
        , is a heterogeneous graph with multiple types of nodes and edges. As shown in Figure
        1
        , it contains two types of nodes; (i) lemmas (i.e., words, 115K) and (ii) synsets (63K), and four types of edges; (
        t1
        ) predicate-argument (179K), (
        t2
        ) argument-argument (144K), (
        t3
        ) argument-synset (126K), and (
        t4
        ) synset-synset (3.4K) edges.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        The predicate-argument edges, first introduced by
        Feng et al. (2011)
        , depict the selectional preference of connotative predicates (i.e., the polarity of a predicate indicates the polarity of its arguments)
and encode their co-occurrence relations based on the Google Web 1T corpus.
The argument-argument edges are based on the distributional similarities among the arguments.
The argument-synset edges capture the synonymy between argument nodes through the corresponding synsets.
Finally, the synset-synset edges depict the antonym relations between synset pairs.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        In general, our graph construction is similar to that of
        Feng et al. (2013)
        , but there are a few important differences. Most notably, we model both words and synsets explicitly, and exploit the membership relations between words and senses. We expect that edges between words and senses will encourage
        senses that belong to the same word
        to receive the same connotation label. Conversely, we expect that these edges will also encourage
        words that belong to the same sense
        (i.e., synset definition) to receive the same connotation label.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Another benefit of our approach is that for various WordNet relations (e.g., antonym relations), which are defined over synsets (not over words), we can add edges directly between corresponding synsets, rather than projecting (i.e., approximating) those relations over words. Note that the latter, which has been employed by several previous studies (e.g.,
        Kamps et al. (2004)
        ,
        Takamura et al. (2005)
        ,
        Andreevskaia and Bergler (2006)
        ,
        Su and Markert (2009)
        ,
        Lu et al. (2011)
        ,
        Kaji and Kitsuregawa (2007)
        ,
        Feng et al. (2013)
        ), could be a source of noise, as one needs to assume that the semantic relation between a pair of synsets transfers over the pair of words corresponding to that pair of synsets. For polysemous words, this assumption may be overly strong.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Pairwise Markov Random Fields and Loopy Belief Propagation
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We formulate the task of learning sense- and word-level connotation lexicon as a graph-based classification task
        [26]
        .
More formally, we denote the connotation graph
        GWord+Sense
        by
        G=(V,E)
        ,
in which a total of
        n
        word and synset nodes
        V={v1,…,vn}
        are connected with typed edges
        e⁢(vi,vj,t)∈E
        , where edge types
        t∈{pred
        -
        a⁢r⁢g,a⁢r⁢g
        -
        a⁢r⁢g,s⁢y⁢n
        -
        a⁢r⁢g,s⁢y⁢n
        -
        syn}
        depict the four edge types as described in Section
        2
        .
A neighborhood function
        𝒩
        , where
        𝒩v={u| e⁢(u,v)∈E}⊆V
        , describes the underlying network structure.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        In our collective classification formulation, each node in
        V
        is represented as a random variable that takes a value from an appropriate class label domain; in our case,
        ℒ={+,-}
        for positive and negative connotation.
In this classification task, we denote by
        𝒴
        the nodes the labels of which need to be assigned, and let
        yi
        refer to
        Yi
        ’s label.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Pairwise Markov Random Fields
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We next define our objective function.
We propose to use an objective formulation that utilizes pairwise Markov Random Fields (MRFs)
         [14]
         , which we adapt to our problem setting.
MRFs are a class of probabilistic graphical models that are suited for solving inference problems in networked data.
An MRF consists of an undirected graph where each node can be in any of a finite number of states (i.e., class labels).
The state of a node is assumed to be dependent on each of its neighbors and independent of other nodes in the graph.
         In pairwise MRFs, the joint probability of the graph can be written as a product of pairwise factors, parameterized over the edges.
These factors are referred to as clique potentials in general MRFs, which are essentially functions that collectively determine the graph’s joint probability.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Specifically, let
         G=(V,E)
         denote a network of random variables,
where
         V
         consists of the unobserved variables
         𝒴
         that need to be assigned values from
label set
         ℒ
         . Let
         Ψ
         denote a set of clique potentials that consists of two types of factors:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            For each
            Yi∈𝒴
            ,
            ψi∈Ψ
            is a
            prior
            mapping
            ψi:ℒ→ℝ≥0
            , where
            ℝ≥0
            denotes non-negative real numbers.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            For each
            e⁢(Yi,Yj,t)∈E
            ,
            ψi⁢jt∈Ψ
            is a
            compatibility
            mapping
            ψi⁢jt:ℒ×ℒ→ℝ≥0
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Objective formulation
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          Given an assignment
          𝐲
          to all the
unobserved variables
          𝒴
          and
          𝐱
          to observed ones
          𝒳
          (variables with known labels, if any), our objective function is associated with the following joint probability distribution
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p2">
         P(𝐲|𝐱)=1Z⁢(𝐱)∏Yi∈𝒴ψi(yi)∏e⁢(Yi,Yj,t)∈Eψi⁢jt(yi,yj)

(1)
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p3">
         <p class="ltx_p">
          where
          Z⁢(𝐱)
          is the normalization function.
Our goal is then to infer the maximum likelihood assignment of states (i.e., labels) to unobserved variables (i.e., nodes) that will maximize Equation (
          1
          ).
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Problem Definition
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          Having introduced our graph-based classification task and objective formulation, we define our problem more formally.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p2">
         <p class="ltx_p">
          Given
         </p>
         <ul class="ltx_itemize" id="I3">
          <li class="ltx_item" id="I3.ix1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            -
           </span>
           <div class="ltx_para" id="I3.ix1.p1">
            <p class="ltx_p">
             a connotation graph
             G=(V,E)
             of words and synsets connected with
             typed
             edges,
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.ix2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            -
           </span>
           <div class="ltx_para" id="I3.ix2.p1">
            <p class="ltx_p">
             prior
             knowledge (i.e., probabilities) of (some or all) nodes belonging to each class,
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.ix3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            -
           </span>
           <div class="ltx_para" id="I3.ix3.p1">
            <p class="ltx_p">
             compatibility
             of two nodes with a given pair of labels
being connected to each other;
            </p>
           </div>
          </li>
         </ul>
         <p class="ltx_p">
          Classify
          the nodes
          Yi∈𝒴
          , into one of two classes;
          ℒ={+,-}
          ,
such that the class assignments
          yi
          maximize our objective in Equation (
          1
          ).
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p3">
         <p class="ltx_p">
          We can further
          rank
          the network objects by the probability of their connotation polarity.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Loopy Belief Propagation
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Finding the best assignments to unobserved variables in our objective function is the inference problem.
The brute force approach through enumeration of all possible assignments is exponential and thus intractable.
In general, exact inference is known to be NP-hard and there is no known algorithm which can be theoretically shown to solve the inference problem for general MRFs.
Therefore in this work, we employ a computationally tractable (in fact linearly scalable with network size)
approximate inference algorithm called Loopy Belief Propagation (LBP)
         [37]
         , which we extend to handle typed graphs like our connotation graph.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Our inference algorithm is based on iterative message passing and the core of it can be concisely expressed as the following two equations:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           mi→j
          </td>
          <td class="ltx_td ltx_align_left">
           (yj)=α∑yi∈ℒ(ψi⁢jt(yi,yj)ψi(yi)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           ∏Yk∈𝒩i∩𝒴\Yjmk→i(yi)),∀yj∈ℒ
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (2)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        bi⁢(yi)=β⁢⁢ψi⁢(yi)⁢∏Yj∈𝒩i∩𝒴mj→i⁢(yi),∀yi∈ℒ

(3)
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         A message
         mi→j
         is sent from node
         i
         to node
         j
         and captures the belief of
         i
         about
         j
         , which is the probability distribution over the labels of
         j
         ; i.e. what
         i
         “thinks”
         j
         ’s label is, given the current label of
         i
         and the
         type
         of the edge that connects
         i
         and
         j
         . Beliefs refer to marginal probability distributions of nodes over labels; for example
         bi⁢(yi)
         denotes the
         belief
         of node
         i
         having label
         yi
         .
         α
         and
         β
         are the normalization constants, which respectively ensure that each message and each set of marginal probabilities sum to
         1
         .
At every iteration, each node computes its belief based on messages received from its neighbors, and uses the compatibility mapping to transform its belief into messages for its neighbors. The key idea is that after enough iterations of message passes between the nodes, the “conversations” are likely to come to a consensus, which determines the marginal probabilities of all the unknown variables.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         [!ht]
         <span class="ltx_ERROR undefined">
          \SetAlgorithmName
         </span>
         AlgorithmprocedureList of procedures
         Connotation Inference
         -5
         Input:
         Connotation graph
         G
         =
         (V,E)
         , prior potentials
         ψs
         for seed words
         s∈S
         , and compatibility potentials
         ψi⁢jt
         Output:
         Connotation label probabilities for each node
         i∈V\P
         (//
         initialize msg.s
         )
         e⁢(Yi,Yj,t)∈E
         <math alttext="y_{j}\in\mathcal{L}" class="ltx_Math" display="inline" id="S3.SS2.p6.m8" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             y
            </mi>
            <mi>
             j
            </mi>
           </msub>
           <mo>
            ∈
           </mo>
           <mi class="ltx_font_mathcaligraphic">
            ℒ
           </mi>
          </mrow>
         </math>
         mi→j⁢(yj)←1
         (//
         initialize priors
         )
         i∈V
         <math alttext="y_{j}\in\mathcal{L}" class="ltx_Math" display="inline" id="S3.SS2.p6.m11" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             y
            </mi>
            <mi>
             j
            </mi>
           </msub>
           <mo>
            ∈
           </mo>
           <mi class="ltx_font_mathcaligraphic">
            ℒ
           </mi>
          </mrow>
         </math>
         <math alttext="i\in S" class="ltx_Math" display="inline" id="S3.SS2.p6.m12" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            i
           </mi>
           <mo>
            ∈
           </mo>
           <mi>
            S
           </mi>
          </mrow>
         </math>
         ϕi⁢(yj)←ψi⁢(yj)
         ϕi⁢(yj)←1/|ℒ|
         ( //
         iterative message passing
         )
         all messages stop changing
         <math alttext="e(Y_{i},Y_{j},t)\in E" class="ltx_Math" display="inline" id="S3.SS2.p6.m15" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             e
            </mi>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mrow>
              <msub>
               <mi>
                Y
               </mi>
               <mi>
                i
               </mi>
              </msub>
              <mo>
               ,
              </mo>
              <msub>
               <mi>
                Y
               </mi>
               <mi>
                j
               </mi>
              </msub>
              <mo>
               ,
              </mo>
              <mi>
               t
              </mi>
             </mrow>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
           <mo>
            ∈
           </mo>
           <mi>
            E
           </mi>
          </mrow>
         </math>
         ,
         Yj∈𝒴V\S
         <math alttext="y_{j}\in\mathcal{L}" class="ltx_Math" display="inline" id="S3.SS2.p6.m17" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             y
            </mi>
            <mi>
             j
            </mi>
           </msub>
           <mo>
            ∈
           </mo>
           <mi class="ltx_font_mathcaligraphic">
            ℒ
           </mi>
          </mrow>
         </math>
         Use Equation (
         3.2
         )
         (//
         compute final beliefs
         )
         Yi∈𝒴V\S
         <math alttext="y_{i}\in\mathcal{L}" class="ltx_Math" display="inline" id="S3.SS2.p6.m19" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             y
            </mi>
            <mi>
             i
            </mi>
           </msub>
           <mo>
            ∈
           </mo>
           <mi class="ltx_font_mathcaligraphic">
            ℒ
           </mi>
          </mrow>
         </math>
         Use Equation (
         3
         )
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         The pseudo-code of our method is given in Algorithm
         3.2
         . It first initializes all messages to
         1
         and
         prior
         s to unbiased (i.e., equal) probabilities for all nodes except the seed nodes for which the sentiment is known (lines 3-9).
It then proceeds by making each
         Yi∈𝒴
         communicate messages with their neighbors in an iterative fashion until the messages stabilize (lines 10-14), i.e. convergence is reached.
         At convergence, we calculate the marginal probabilities, that is of assigning
         Yi
         with label
         yi
         , by computing the final beliefs
         bi⁢(yi)
         (lines 15-17).
We use these maximum likelihood probabilities for label assignment; for each node
         i
         , we assign the label
         ℒi←maxyi⁡bi⁢(yi)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p8">
        <p class="ltx_p">
         To completely define our algorithm, we need to instantiate the potentials
         Ψ
         , in particular the priors and the compatibilities, which we discuss next.
        </p>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Priors
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          The
          prior
          beliefs
          ψi
          of nodes can be suitably initialized if there is any prior knowledge for their connotation sentiment (e.g.,
          enjoy
          is positive,
          suffer
          is negative).
As such, our method is flexible to integrate available side information.
In case there is no prior knowledge available, each node is
initialized equally likely to have any of the possible labels, i.e.,
          1|ℒ|
          as in Algorithm
          3.2
          (line 9).
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Compatibilities
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          The
          compatibility
          potentials can be thought of as matrices, with entries
          ψi⁢jt⁢(yi,yj)
          that give the likelihood of a node having
label
          yi
          , given that it has a neighbor with label
          yj
          to which it is connected through a type
          t
          edge.
A key difference of our method from earlier models is that we use clique potentials that differ for edge types, since the connotation graph is heterogeneous.
This is exactly because the compatibility of class labels of two adjacent nodes depends on the type of the edge connecting them: e.g.,
          +
          →s⁢y⁢n⁢-⁢a⁢r⁢g
          +
          is highly compatible, whereas
          +
          →s⁢y⁢n⁢-⁢s⁢y⁢n
          +
          is unlikely; as
          s⁢y⁢n
          -
          a⁢r⁢g
          edges capture synonymy; i.e., words-sense memberships, while
          s⁢y⁢n
          -
          s⁢y⁢n
          edges depict antonym relations.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS0.P2.p2">
         <p class="ltx_p">
          A sample instantiation of the compatibilities is shown in Table
          1
          .
Notice that the potentials for
          p⁢r⁢e⁢d⁢-⁢a⁢r⁢g
          ,
          a⁢r⁢g⁢-⁢a⁢r⁢g
          , and
          s⁢y⁢n⁢-⁢a⁢r⁢g
          capture homophily, i.e., nodes with the same label are likely to connect to each other through these types of edges.
          On the other hand,
          s⁢y⁢n⁢-⁢s⁢y⁢n
          edges connect nodes that are antonyms of each other, and thus the compatibilities capture the reverse relationship among their labels.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Complexity analysis
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P3.p1">
         <p class="ltx_p">
          Most demanding component of Algorithm
          3.2
          is the iterative message passing over the edges (lines 10-14),
with time complexity
          O⁢(m⁢l2⁢r)
          , where
          m=|E|
          is the number of edges in the connotation graph,
          l=|ℒ|
          , the classes, and
          r
          , the iterations until convergence. Often,
          l
          is quite small (in our case,
          l=2
          ) and
          r≪m
          . Thus running time grows linearly with the number of edges and is scalable to large datasets.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Evaluation I: Agreement with Sentiment Lexicons
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        ConnotationWordNet
        is expected to be the superset of a sentiment lexicon, as it is highly likely for any word with positive/negative sentiment to carry connotation of the same polarity. Thus, we use two conventional sentiment lexicons, General Inquirer (
        GenInq
        )
        [27]
        and
        MPQA
        [36]
        , as surrogates to measure the performance of our inference algorithm.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Variants of Graph Construction
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         The construction of the connotation graph, denoted by
         GWord+Sense
         , which includes words and synsets, has been described in Section
         2
         . In addition to this graph, we tried several other graph constructions, the first three of which have previously been used in
         [10]
         . We briefly describe these graphs below, and compare performance on all the graphs in the proceeding.
        </p>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         GWord
         w/ Pred-Arg
         :
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          This is a (bipartite) subgraph of
          GWord+Sense
          , which only includes the connotative predicates and their arguments. As such, it contains only type
          t1
          edges.
The edges between the predicates and the arguments can be weighted by their Point-wise Mutual Information (PMI)
          based on the Google Web 1T corpus.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         GWord
         w/ Overlay
         :
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          The second graph is also a proper subgraph of
          GWord+Sense
          , which includes the predicates and all the argument words. Predicate words are connected to their arguments as before. In addition, argument pairs (
          a1
          ,
          a2
          ) are connected if they occurred together in the “
          a1
          and
          a2
          ” or “
          a2
          and
          a1
          ” coordination
          [11, 24]
          .
This graph contains both type
          t1
          and
          t2
          edges.
The edges can also be weighted based on the distributional similarities of the word pairs.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         GWord
         :
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P3.p1">
         <p class="ltx_p">
          The third graph is a super-graph of
          GWord
          w/ Overlay
          , with additional edges, where argument pairs in synonym and antonym relation are connected to each other.
Note that unlike the connotation graph
          GWord+Sense
          , it does
          not
          contain any synset nodes. Rather, the words that are synonyms or antonyms of each other are directly linked in the graph.
As such, this graph contains all edge types
          t1
          through
          t4
          .
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P4">
        <h4 class="ltx_title ltx_title_paragraph">
         GWord+Sense
         w/ SynSim
         :
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p1">
         <p class="ltx_p">
          This is a super-graph of our original
          GWord+Sense
          graph; that is, it has all the predicate, arguments, and synset nodes, as well as the four types of edges between them.
In addition, we add edges of a fifth type
          t5
          between the synset nodes to capture their similarity. To define similarity, we use the glossary definitions of the synsets and derive three different scores. Each score utilizes the
          count
          (
          s1,s2
          ) of overlapping nouns, verbs, and adjectives/adverbs among the glosses of the two synsets
          s1
          and
          s2
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p2">
         <p class="ltx_p">
          GWord+Sense
          w/ SynSim1
          : We discard edges with
          count
          less than 3. The weighted version has the
          count
          s normalized between 0 and 1.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p3">
         <p class="ltx_p">
          GWord+Sense
          w/ SynSim2
          : We normalize the
          count
          s by the length of the gloss (the avg of two lengths), that is,
          p=
          count / avg(len_gloss(s1), len_gloss(s2))
          and discard edges with
          p&lt;0.5
          . The weighted version contains
          p
          values as edge weights.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p4">
         <p class="ltx_p">
          GWord+Sense
          w/ SynSim3
          : To further sparsify the graph we discard edges with
          p&lt;0.6
          . To weigh the edges, we use the cosine similarity between the gloss vectors of the synsets based on the TF-IDF values of the words the glosses contain.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p5">
         <p class="ltx_p">
          Note that the connotation inference algorithm, as given in Algorithm
          3.2
          , remains exactly the same for all the graphs described above.
The only difference is the set of parameters used; while
          GWord
          w/ Pred-Arg
          and
          GWord
          w/ Overlay
          contain one and two edge types, respectively and only use compatibilities
          (t1)
          and
          (t2)
          ,
          GWord
          uses all four as given in Table
          1
          . The
          GWord+Sense
          w/ SynSim
          graphs use an additional compatibility matrix for the synset similarity edges of type
          t5
          , which is the same as the one used for
          t1
          , i.e., similar synsets are likely to have the same connotation label.
This flexibility is one of the key advantages of our algorithm as new types of nodes and edges can be added to the graph seamlessly.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Sentiment-Lexicon based Performance
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         In this section, we first compare the performance of our connotation graph
         GWord+Sense
         to graphs that do not include synset nodes but only words.
Then we analyze the performance when the additional synset similarity edges are added.
First, we briefly describe our performance measures.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         The sentiment lexicons we use as gold standard are small, compared to the size (i.e., number of words) our graphs contain. Thus, we first find the
         overlap
         between each graph and a sentiment lexicon. Note that the
         overlap
         size may be smaller than the
         lexicon size
         , as some sentiment words may be missing from our graphs.
Then, we calculate the number of
         correct
         label assignments. As such,
precision is defined as (
         correct
         /
         overlap
         ), and
recall as (
         correct
         /
         lexicon size
         ). Finally, F1-score is their harmonic mean and reflects the overall accuracy.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         As shown in Table
         2
         (top), we first observe that including the synonym and antonym relations in the graph, as with
         GWord
         and
         GWord+Sense
         , improve the performance significantly, almost by an order of magnitude, over graphs
         GWord
         w/ Pred-Arg
         and
         GWord
         w/ Overlay
         that do not contain those relation types.
Furthermore, we
notice that the performances on the
         GWord+Sense
         graph are better than those on the word-only graphs.
This shows that including the synset nodes explicitly in the graph structure is beneficial. What is more, it gives us a means to obtain connotation labels for the synsets themselves, which we use in the evaluations in the next sections.
Finally, we note that using the unweighted versions of the graphs provide relatively more robust performance, potentially due to noise in the relative edge weights.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         Next we analyze the performance when the new edges between synsets are introduced, as given in Table
         2
         (bottom). We observe that connecting the synset nodes by their gloss-similarity (at least in the ways we tried) does not yield better performance than on our original
         GWord+Sense
         graph. Different from earlier, the weighted versions of the similarity based graphs provide better performance than their unweighted counterparts. This suggests that glossary similarity would be a more robust means to correlate nodes; we leave it as future work to explore this direction for predicate-argument and argument-argument relations.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Parameter Sensitivity
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         Our belief propagation based connotation sentiment inference algorithm has one user-specified parameter
         ϵ
         (see Table
         1
         ).
To study the sensitivity of its performance to the choice of
         ϵ
         , we reran our experiments for
         ϵ={0.02,0.04,…,0.24}
         and report the accuracy results on our
         GWord+Sense
         in Figure
         2
         for the two lexicons. The results indicate that the performances remain quite stable across a wide range of the parameter choice.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Evaluation II: Human Evaluation on ConnotationWordNet
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In this section, we present the result of human evaluation we executed using Amazon Mechanical Turk (AMT).
We collect two separate sets of labels: a set of labels at the word-level, and another set at the sense-level. We first describe the labeling process of sense-level connotation:
We selected 350 polysemous words and one of their senses, and each Turker was asked to rate the connotative polarity of a given word (or of a given sense), from -5 to 5, 0 being the neutral.
        For each word, we asked 5 Turkers to rate and we took the average of the 5 ratings as the connotative intensity score of the word. We labeled a word as
        negative
        if its intensity score is less than 0 and
        positive
        otherwise.
For word-level labels we apply similar procedure as above.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Word-Level Evaluation
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We first evaluate the word-level assignment of connotation, as shown in Table
         3
         .
The agreement between the new lexicon and human judges varies between 84% and 86.98%.
Sentiment lexicons such as SentiWordNet (
         Baccianella et al. (2010)
         ) and OpinionFinder (
         Wilson et al. (2005a)
         ) show low agreement rate with human, which is somewhat as expected: human judges in this study are labeling for subtle connotation, not for more explicit sentiment.
OpinionFinder’s low agreement rate was mainly due to the low hit rate of the words (successful look-up rate, 33.43%). Feng2013 is the lexicon presented in
         [10]
         and it showed a relatively higher 72.13% hit rate.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Note that belief propagation was run until 95% and 99% of the nodes were converged in their beliefs.
In addition, the seed words with known connotation labels originally consist of 20 positive and 20 negative predicates.
We also extended the seed set with the sentiment lexicon words and denote these runs with
         e-
         for ‘
         e
         xtended’.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Sense-Level Evaluation
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We also examined the agreement rates on the sense-level. Since OpinionFinder and Feng2013 do not provide the polarity scores at the sense-level, we excluded them from this evaluation.
Because sense-level polarity assignment is a harder (more subtle) task, the performance of all lexicons decreased to some degree in comparison to that of word-level evaluations.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Pair-wise Intensity Ranking
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         A notable goodness of our induction algorithm is that the outcome of the algorithm can be interpreted as an
         intensity
         of the corresponding connotation. But are these values meaningful? We answer this question in this section.
We formulate a pair-wise ranking task as a binary decision task as follows: given a pair of words, we ask which one is more positive (or more negative) than the other. Since we collect human labels based on
         scales
         , we already have this information at hand. Because different human judges have different notion of scales however, subtle differences are more likely to be noisy. Therefore, we experiment with varying degrees of differences in their scales, as shown in Figure
         3
         . Threshold values (ranging from 0.5 to 3.0) indicate the minimum differences in scales for any pair of words, for the pair to be included in the test set. As expected, we observe that the performance improves as we increase the threshold (as pairs get better separated). Within range [0.5, 1.5] (249 pairs examined), the accuracies are as high as 68.27%, which shows that even the subtle differences of the connotative intensities are relatively well reflected in the new lexicons.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         The results for pair-wise intensity evaluation (threshold=2.0, 1,208 pairs) are given in Table
         4
         .
Despite that intensity is generally a harder property to measure (than the coarser binary categorization of polarities), our connotation lexicons perform surprisingly well, reaching up to 74.83% accuracy.
Further study on the incorrect cases reveals that SentiWordNet has many pair of words with the same polarity score (23.34%). Such cases seems to be due to the limited score patterns of SentiWordNet. The ratio of such cases are accounted as
         Undecided
         in Table
         4
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
       Evaluation III: Sentiment Analysis using ConnotationWordNet
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        Finally, to show the utility of the resulting lexicon in the context of a concrete sentiment analysis task, we perform lexicon-based sentiment analysis.
We experiment with SemEval dataset
        [28]
        that includes the human labeled dataset for predicting whether a news headline is a
        good news
        or a
        bad news
        , which we expect to have a correlation with the use of
        connotative
        words that we focus on in this paper.
The good/bad news are annotated with scores (ranging from -100 to 87). We construct several data sets by applying different thresholds on scores. For example, with the threshold set to 60, we discard the instances whose scores lie between -60 and 60. For comparison, we also test the connotation lexicon from
        [10]
        and the combined sentiment lexicon
        GenInq
        +
        MPQA
        .
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Note that there is a difference in how humans judge the orientation and the degree of connotation for a given word out of context, and how the use of such words in context can be perceived as
        good/bad
        news. In particular, we conjecture that humans may have a bias toward the use of positive words, which in turn requires calibration from the readers’ minds
        [22]
        .
That is, we might need to tone down the level of positiveness in order to correctly measure the actual intended positiveness of the message.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        With this in mind, we tune the appropriate calibration from a small training data, by using 1 fold from
        N
        fold cross validation, and using the remaining
        N-1
        folds as testing. We simply learn the mixture coefficient
        λ
        to scale the contribution of positive and negative connotation values. We tune this parameter
        λ
        for other lexicons we compare against as well. Note that due to this parameter learning, we are able to report better performance for the connotation lexicon of
        [10]
        than what the authors have reported in their paper (labeled with *) in Table
        5
        .
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Table
        5
        shows the results for
        N
        =
        15
        , where the new lexicon consistently outperforms other competitive lexicons. In addition, Figure
        4
        shows that the performance does not change much based on the size of training data used for parameter tuning (
        N
        =
        {5,10,15,20}
        ).
       </p>
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
        Several previous approaches explored the use of graph propagation for sentiment lexicon induction
        [32]
        and connotation lexicon induction
        [10]
        . Our work introduces the use of loopy belief propagation over pairwise-MRF as an alternative solution to these tasks. At a high-level, both approaches share the general idea of propagating confidence or belief over the graph connectivity. The key difference, however, is that in our MRF representation, we can explicitly model various types of word-word, sense-sense and word-sense relations as edge potentials. In particular, we can naturally encode relations that encourage the same assignment (e.g., synonym) as well as the opposite assignment (e.g., antonym) of the polarity labels. Note that integration of the latter is not straightforward in the graph propagation framework.
       </p>
      </div>
      <div class="ltx_para" id="S7.p2">
       <p class="ltx_p">
        There have been a number of previous studies that aim to construct a word-level sentiment lexicon
        [34, 25]
        and a sense-level sentiment lexicon
        [8]
        . But none of these approaches considered to induce the polarity labels at both the word-level and sense-level. Although we focus on learning connotative polarity of words and senses in this paper, the same approach would be applicable to constructing a sentiment lexicon as well.
       </p>
      </div>
      <div class="ltx_para" id="S7.p3">
       <p class="ltx_p">
        There have been recent studies that address word sense disambiguation issues for sentiment analysis.
SentiWordNet
        [8]
        was the very first lexicon developed for sense-level labels of sentiment polarity. In recent years,
        Akkaya et al. (2009)
        report a successful empirical result where WSD helps improving sentiment analysis, while
        Wiebe and Mihalcea (2006)
        study the distinction between objectivity and subjectivity in each different sense of a word, and their empirical effects in the context of sentiment analysis. Our work shares the high-level spirit of accessing the sense-level polarity, while also deriving the word-level polarity.
       </p>
      </div>
      <div class="ltx_para" id="S7.p4">
       <p class="ltx_p">
        In recent years, there has been a growing research interest in investigating more fine-grained aspects of lexical sentiment beyond positive and negative sentiment. For example,
        Mohammad and Turney (2010)
        study the affects words can
        evoke
        in people’s minds, while
        Bollen et al. (2011)
        study various moods, e.g., “tension”, “depression”, beyond simple dichotomy of positive and negative sentiment. Our work, and some recent work by
        Feng et al. (2011)
        and
        Feng et al. (2013)
        share this spirit by targeting more subtle, nuanced sentiment even from those words that would be considered as objective in early studies of sentiment analysis.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
