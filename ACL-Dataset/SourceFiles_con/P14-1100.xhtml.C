<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Spectral Unsupervised Parsing with Additive Tree Metrics.
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
       We propose a spectral approach for unsupervised constituent parsing that comes with theoretical guarantees on latent structure recovery. Our approach is grammarless – we directly learn the bracketing structure of a given sentence without using a grammar model. The main algorithm is based on lifting the concept of additive tree metrics for structure learning of latent trees in the phylogenetic and machine learning communities to the case where the tree structure varies across examples. Although finding the “minimal” latent tree is NP-hard in general, for the case of projective trees we find that it can be found using bilexical parsing algorithms. Empirically, our algorithm performs favorably compared to the constituent context model of Klein and Manning (2002) without the need for careful initialization.
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
        Solutions to the problem of grammar induction have been long sought after since the early days of computational linguistics and are interesting both from cognitive and engineering perspectives. Cognitively, it is more plausible to assume that children obtain only terminal strings of parse trees and not the actual parse trees. This means the unsupervised setting is a better model for studying language acquisition. From the engineering perspective, training data for unsupervised parsing exists in abundance (i.e. sentences and part-of-speech tags), and is much cheaper than the syntactically annotated data required for supervised training.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Most existing solutions treat the problem of unsupervised parsing by assuming a generative process over parse trees e.g. probabilistic context free grammars
        [Jelinek et al.1992]
        , and the constituent context model
        [Klein and Manning2002]
        . Learning then reduces to finding a set of parameters that are estimated by identifying a local maximum of an objective function such as the likelihood
        [Klein and Manning2002]
        or a variant of it
        [Smith and Eisner2005, Cohen and Smith2009, Headden et al.2009, Spitkovsky et al.2010b, Gillenwater et al.2010, Golland et al.2012]
        . Unfortunately, finding the global maximum for these objective functions is usually intractable
        [Cohen and Smith2012]
        which often leads to severe local optima problems (but see Gormley and Eisner, 2013
        ). Thus, strong experimental results are often achieved by initialization techniques
        [Klein and Manning2002, Gimpel and Smith2012]
        , incremental dataset use
        [Spitkovsky et al.2010a]
        and other specialized techniques to avoid local optima such as count transforms
        [Spitkovsky et al.2013]
        . These approaches, while empirically promising, generally lack theoretical justification.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        On the other hand, recently proposed spectral methods approach the problem via restriction of the PCFG model
        [Hsu et al.2012]
        or matrix completion
        [Bailly et al.2013]
        . These novel perspectives offer strong theoretical guarantees but are not designed to achieve competitive empirical results.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In this paper, we suggest a different approach, to provide a first step to bridging this theory-experiment gap. More specifically, we approach unsupervised constituent parsing from the perspective of
        structure learning
        as opposed to parameter learning. We associate each sentence with an undirected latent tree graphical model, which is a tree consisting of both observed variables (corresponding to the words in the sentence) and an additional set of latent variables that are unobserved in the data. This undirected latent tree is then directed via a
        direction mapping
        to give the final constituent parse.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        In our framework, parsing reduces to finding the best latent structure for a given sentence. However, due to the presence of latent variables, structure learning of latent trees is substantially more complicated than in observed models. As before, one solution would be local search heuristics.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Intuitively, however, latent tree models encode low rank dependencies among the observed variables permitting the development of “spectral” methods that can lead to provably correct solutions. In particular we leverage the concept of additive tree metrics
        [Buneman1971, Buneman1974]
        in phylogenetics and machine learning that can create a special distance metric among the observed variables as a function of the underlying spectral dependencies
        [Choi et al.2011, Song et al.2011, Anandkumar et al.2011, Ishteva et al.2012]
        . Additive tree metrics can be leveraged by “meta-algorithms” such as neighbor-joining
        [Saitou and Nei1987]
        and recursive grouping
        [Choi et al.2011]
        to provide consistent learning algorithms for latent trees.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Moreover, we show that it is desirable to learn the “minimal” latent tree based on the tree metric (“minimum evolution” in phylogenetics). While this criterion is in general NP-hard
        [Desper and Gascuel2005]
        , for projective trees we find that a bilexical parsing algorithm can be used to find an exact solution efficiently
        [Eisner and Satta1999]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        Unlike in phylogenetics and graphical models, where a single latent tree is constructed for all the data, in our case, each part of speech sequence is associated with its own parse tree. This leads to a severe data sparsity problem even for moderately long sentences. To handle this issue, we present a strategy that is inspired by ideas from kernel smoothing in the statistics community
        [Zhou et al.2010, Kolar et al.2010b, Kolar et al.2010a]
        . This allows principled sharing of samples from different but similar underlying distributions.
       </p>
      </div>
      <div class="ltx_para" id="S1.p9">
       <p class="ltx_p">
        We provide theoretical guarantees on the recovery of the correct underlying latent tree and characterize the associated sample complexity under our technique. Empirically we evaluate our method on data in English, German and Chinese. Our algorithm performs favorably to Klein and Manning’s (2002) constituent-context model (CCM), without the need for careful initialization. In addition, we also analyze CCM’s sensitivity to initialization, and compare our results to Seginer’s algorithm
        [Seginer2007]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Learning Setting and Model
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        In this section, we detail the learning setting and a conditional tree model we learn the structure for.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Learning Setting
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Let
         𝒘=(w1,…,wℓ)
         be a vector of words corresponding to a sentence of length
         ℓ
         . Each
         wi
         is represented by a vector in
         ℝp
         for
         p∈ℕ
         . The vector is an embedding of the word in some space, chosen from a fixed dictionary that maps word types to
         ℝp
         .
In addition, let
         𝒙=(x1,…,xℓ)
         be the associated vector of part-of-speech (POS) tags (i.e.
         xi
         is the POS tag of
         wi
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         In our learning algorithm, we assume that examples of the form
         (𝒘(i),𝒙(i))
         for
         i∈[N]={1,…,N}
         are given, and the goal is to predict
a bracketing parse tree for each of these examples. The word embeddings are used during the learning process, but the final decoder that the learning algorithm outputs
maps a POS tag sequence
         𝒙
         to a parse tree. While ideally we would want to use the word information in decoding as well, much of the syntax of a sentence
is determined by the POS tags, and relatively high level of accuracy can be achieved by learning, for example, a supervised parser from POS tag sequences.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         Just like our decoder, our model assumes that the bracketing of a given sentence is a function of its POS tags. The POS tags are generated from some distribution,
followed by a deterministic generation of the bracketing parse tree. Then, latent states are generated for each bracket, and finally, the latent states at the yield of the bracketing
parse tree generate the words of the sentence (in the form of embeddings). The latent states are represented by vectors
         z∈ℝm
         where
         m&lt;p
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Intuition
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         For intuition, consider the simple tag sequence
         𝒙=(𝚅𝙱𝙳,𝙳𝚃,𝙽𝙽)
         .
Two candidate constituent parse structures are shown in Figure
         2
         and the correct one is boxed in green (the other in red).
Recall that our training data contains word phrases that have the tag sequence
         𝒙
         e.g.
         𝒘(1)=(𝚑𝚒𝚝,𝚝𝚑𝚎,𝚋𝚊𝚕𝚕)
         ,
         𝒘(2)=(𝚊𝚝𝚎,𝚊𝚗,𝚊𝚙𝚙𝚕𝚎)
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         Intuitively, the words in the above phrases exhibit dependencies that can reveal the parse structure. The determiner (
         w2
         ) and the direct object (
         w3
         ) are correlated in that the choice of determiner depends on the plurality of
         w3
         . However, the choice of verb (
         w1
         ) is mostly independent of the determiner. We could thus conclude that
         w2
         and
         w3
         should be closer in the parse tree than
         w1
         and
         w2
         , giving us the correct structure. Informally, the latent state
         z
         corresponding to the
         (w2,w3)
         bracket would store information about the plurality of
         z
         , the key to the dependence between
         w2
         and
         w3
         . It would then be reasonable to assume that
         w2
         and
         w3
         are independent given
         z
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        A Conditional Latent Tree Model
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         Following this intuition, we propose to model the distribution over the latent bracketing states and words for each tag sequence
         𝒙
         as a latent tree graphical model, which encodes conditional independences among the words given the latent states.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Let
         𝒱:={w1,…,wℓ,z1,…,zH}
         , with
         wi
         representing the word embeddings, and
         zi
         representing
the latent states of the bracketings. Then, according to our base model it holds that:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="A0.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           p(𝒘,𝒛|𝒙)
          </td>
          <td class="ltx_td ltx_align_left">
           =∏i=1Hp(zi|π𝒙(zi),θ(𝒙))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           ×∏i=1ℓ⁢(𝒙)p(wi|π𝒙(wi),θ(𝒙))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (1)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         where
         π𝒙⁢(⋅)
         returns the parent node index of the argument in the latent tree corresponding to tag sequence
         𝒙
         .
         If
         z
         is the root, then
         π𝒙⁢(z)=∅
         . All the
         wi
         are assumed to be leaves while all the
         zi
         are internal (i.e. non-leaf) nodes.
The parameters
         θ⁢(𝒙)
         control the conditional probability tables. We do not commit to a certain parametric family, but see more about the assumptions we make about
         θ
         in §
         3.2
         . The parameter space is denoted
         Θ
         . The model assumes a factorization according to a latent-variable tree. The latent variables can incorporate
various linguistic properties, such as head information, valence of dependency being generated, and so on. This information is expected to be learned automatically from data.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         Our generative model deterministically maps a POS sequence to a bracketing via an undirected latent-variable tree.
The orientation of the tree is determined by a
         direction mapping
         hdir⁢(u)
         , which is fixed during learning and decoding.
This means our decoder first identifies (given a POS sequence) an undirected tree, and then orients it by applying
         hdir
         on the resulting tree (see below).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p5">
        <p class="ltx_p">
         Define
         𝒰
         to be the set of undirected latent trees where all internal nodes have degree exactly
         3
         (i.e. they correspond to binary bracketing), and in addition
         hdir⁢(u)
         for any
         u∈𝒰
         is projective (explained in the
         hdir
         section). In addition, let
         𝒯
         be the set of binary bracketings. The complete generative model that we follow is then:
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p6">
        <ul class="ltx_itemize">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Generate a tag sequence
            𝒙=(x1,…,xℓ)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Decide on
            u⁢(𝒙)∈𝒰
            , the undirected latent tree that
            𝒙
            maps to.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            Set
            t∈𝒯
            by computing
            t=hdir⁢(u)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i4.p1">
           <p class="ltx_p">
            Set
            θ∈Θ
            by computing
            θ=θ⁢(𝒙)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i5.p1">
           <p class="ltx_p">
            Generate a tuple
            𝒗=(w1,…,wℓ,z1,…,zH)
            where
            wi∈ℝp,zj∈ℝm
            according to Eq.
            1
            .
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         See Figure 1 (left) for an example.
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS3.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         The Direction Mapping
         hdir
         .
        </h4>
        <div class="ltx_para" id="S2.SS3.SSS0.P1.p1">
         <p class="ltx_p">
          Generating a bracketing via an undirected tree enables us to build on existing
methods for structure learning of latent-tree graphical models
          [Choi et al.2011, Anandkumar et al.2011]
          .
Our learning algorithm focuses on recovering the undirected tree based for the generative model that was described above. This undirected tree
is converted into a directed tree by applying
          hdir
          . The mapping
          hdir
          works in three steps:
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS0.P1.p2">
         <ul class="ltx_itemize">
          <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i1.p1">
            <p class="ltx_p">
             It first chooses a top bracket
             ([1,R-1],[R,ℓ])
             where
             R
             is the mid-point of the bracket and
             ℓ
             is the length of the sentence.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i2.p1">
            <p class="ltx_p">
             It marks the edge
             ei,j
             that splits the tree according to the top bracket as the “root edge” (marked in red in Figure
             1
             (center))
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i3.p1">
            <p class="ltx_p">
             It then creates
             t
             from
             u
             by directing the tree outward from
             ei,j
             as shown in Figure
             1
             (center)
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS0.P1.p3">
         <p class="ltx_p">
          The resulting
          t
          is a binary bracketing parse tree.
As implied by the above definition of
          hdir
          , selecting which edge is the root can be interpreted as determining the top bracket of the constituent parse.
For example, in Figure
          1
          , the top bracket is
          ([1,2],[3,5])=([𝙳𝚃,𝙽𝙽],[𝚅𝙱𝙳,𝙳𝚃,𝙽𝙽])
          . Note that the “root” edge
          ez1,z2
          partitions the leaves into precisely this bracketing. As indicated in the above section, we restrict the set of undirected trees to be those such that after applying
          hdir
          the resulting
          t
          is projective i.e. there are no crossing brackets. In §
          4.1
          , we discuss an effective heuristic to find the top bracket without supervision.
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
       Spectral Learning Algorithm based on Additive Tree Metrics
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Our goal is to recover
        t∈𝒯
        for tag sequence
        𝒙
        using the data
        𝒟=[(𝒘(i),𝒙(i))]i=1N
        . To get an intuition about the algorithm, consider a partition of the set of examples
        𝒟
        into
        𝒟⁢(𝒙)={(𝒘(i),𝒙(i))∈𝒟|𝒙(i)=𝒙}
        , i.e. each section in the partition has an identical sequence of part of speech tags. Assume for this section
        |𝒟⁢(𝒙)|
        is large (we address the data sparsity issue in §
        3.4
        ).
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We can then proceed by learning how to map a POS sequence
        𝒙
        to a tree
        t∈𝒯
        (through
        u∈𝒰
        ) by focusing only on examples in
        𝒟⁢(𝒙)
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Directly attempting to maximize the likelihood unfortunately results in an intractable optimization problem and greedy heuristics are often employed
        [Harmeling and Williams2011]
        . Instead we propose a method that is provably consistent and returns a tree that can be mapped to a bracketing using
        hdir
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        If all the variables were observed, then the Chow-Liu algorithm
        [Chow and Liu1968]
        could be used to find the most likely tree structure
        u∈𝒰
        . The Chow-Liu algorithm essentially computes the distances among all pairs of variables (the negative of the mutual information) and then finds the minimum cost tree. However, the fact that the
        zi
        are latent variables makes this strategy substantially more complicated. In particular, it becomes challenging to compute the distances among pairs of latent variables. What is needed is a “special” distance function that allows us to reverse engineer the distances among the latent variables given the distances among the observed variables. This is the key idea behind additive tree metrics that are the basis of our approach.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        In the following sections, we describe the key steps to our method. §3.1 and §3.2 largely describe existing background on additive tree metrics and latent tree structure learning, while §3.3 and §3.4 discuss novel aspects that are unique to our problem.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Additive Tree Metrics
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Let
         u⁢(𝒙)
         be the true undirected tree of sentence
         𝒙
         and assume the nodes
         𝒱
         to be indexed by
         [M]={1,…,M}
         such that
         M=|𝒱|=H+ℓ
         . Furthermore, let
         v∈𝒱
         refer to a node in the undirected tree (either observed or latent). We assume the existence of a distance function that allows us to compute distances between pairs of nodes. For example, as we see in §
         3.2
         we will define the distance
         d⁢(i,j)
         to be a function of the covariance matrix
         𝔼[vivj⊤|u(𝒙),θ(𝒙)]
         . Thus if
         vi
         and
         vj
         are both observed variables, the distance can be directly computed from the data.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Moreover, the metrics we construct are such that they are
         tree additive
         , defined below:
        </p>
       </div>
       <div class="ltx_theorem ltx_theorem_definition" id="Thmdefinition1">
        <h6 class="ltx_title ltx_runin ltx_font_bold ltx_title_theorem">
         <span class="ltx_tag ltx_tag_theorem">
          Definition 1
         </span>
        </h6>
        <div class="ltx_para" id="Thmdefinition1.p1">
         <p class="ltx_p">
          A function du⁢(𝐱):[M]×[M]→ℝ is an additive tree metric [Erdõs et al.1999] for the undirected tree u⁢(𝐱) if it is a distance metric, and furthermore, ∀i,j∈[M] the following relation holds:
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="A0.EGx2">
          <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            du⁢(𝒙)⁢(i,j)=∑(a,b)∈pathu⁢(𝒙)⁢(i,j)du⁢(𝒙)⁢(a,b)
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
         <p class="ltx_p">
          where pathu⁢(𝐱)⁢(i,j) is the set of all the edges in the (undirected) path from i to j in the tree u⁢(𝐱).
         </p>
        </div>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         As we describe below, given the tree structure, the additive tree metric property allows us to compute “backwards” the distances among the latent variables as a function of the distances among the observed variables.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Define
         𝑫
         to be the
         M×M
         distance matrix among the
         M
         variables, i.e.
         Di⁢j=du⁢(𝒙)⁢(i,j)
         . Let
         𝑫W⁢W
         ,
         𝑫Z⁢W
         (equal to
         𝑫W⁢Z⊤
         ), and
         𝑫Z⁢Z
         indicate the word-word, latent-word and latent-latent sub-blocks of
         𝑫
         respectively. In addition, since
         u⁢(𝒙)
         is assumed to be known from context, we denote
         du⁢(𝒙)⁢(i,j)
         just by
         d⁢(i,j)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         Given the fact that the distance between a pair of nodes is a function of the random variables they represent (according to the true model), only
         𝑫W⁢W
         can be empirically estimated
from data. However, if the underlying tree structure is known, then Definition
         1
         can be leveraged to compute
         𝑫Z⁢Z
         and
         𝑫Z⁢W
         as we show below.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         We first show how to compute
         d⁢(i,j)
         for all
         i,j
         such that
         i
         and
         j
         are adjacent to each other in
         u⁢(𝒙)
         , based only on observed nodes.
It then follows that the other elements of the distance matrix can be computed based on Definition
         1
         . To show how to compute distances
between adjacent nodes, consider the two cases:
         (1)
         (i,j)
         is a leaf edge;
         (2)
         (i,j)
         is an internal edge.
        </p>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Case 1 (leaf edge, figure
         3
         )
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          Assume without loss of generality that
          j
          is the leaf and
          i
          is an internal latent node.
Then
          i
          must have exactly two other neighbors
          a∈[M]
          and
          b∈[M]
          . Let
          A
          denote the set of nodes that are closer to
          a
          than
          i
          and similarly let
          B
          denote the set of nodes that are closer to
          b
          than
          i
          . Let
          A∗
          and
          B∗
          denote all the leaves (word nodes) in
          A
          and
          B
          respectively. Then using path additivity (Definition
          1
          ), it can be shown that for any
          a∗∈A∗,b∗∈B∗
          it holds that:
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx3">
          <tr class="ltx_equation ltx_align_baseline" id="S3.E3">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            d⁢(i,j)=12⁢(d⁢(j,a∗)+d⁢(j,b∗)-d⁢(a∗,b∗))
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (3)
            </span>
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P1.p2">
         <p class="ltx_p">
          Note that the right-hand side only depends on distances between observed random variables.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Case 2 (internal edge, figure
         3
         )
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          Both
          i
          and
          j
          are internal nodes. In this case,
          i
          has exactly two other neighbors
          a∈[M]
          and
          b∈[M]
          , and similarly,
          j
          has exactly other two neighbors
          g∈[M]
          and
          h∈[M]
          . Let
          A
          denote the set of nodes closer to
          a
          than
          i
          , and analogously for
          B
          ,
          G
          , and
          H
          .
Let
          A∗
          ,
          B∗
          ,
          G∗
          , and
          H∗
          refer to the leaves in
          A,B,G
          , and
          H
          respectively. Then for any
          a∗∈A∗
          ,
          b∗∈B∗
          ,
          g∗∈G∗
          , and
          h∗∈H∗
          it can be shown that:
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx4">
          <tr class="ltx_equation ltx_align_baseline" id="S3.Ex2">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_center">
            d(i,j)=14(d(a∗,g∗)+d(a∗,h∗)+d(b∗,g∗)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S3.E4">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_center">
            +d(b∗,h∗)-2d(a∗,b∗)-2d(g∗,h∗))
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (4)
            </span>
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS0.P2.p2">
         <p class="ltx_p">
          Empirically, one can obtain a more robust empirical estimate
          d^⁢(i,j)
          by averaging over all valid choices of
          a∗,b∗
          in Eq.
          3
          and all valid choices of
          a∗,b∗,g∗,h∗
          in Eq.
          4
          [Desper and Gascuel2005]
          .
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Constructing a Spectral Additive Metric
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         In constructing our distance metric, we begin with the following assumption on the distribution in Eq.
         1
         (analogous to the assumptions made in Anandkumar et al., 2011
         ).
        </p>
       </div>
       <div class="ltx_theorem ltx_theorem_assumption" id="Thmassumption1">
        <h6 class="ltx_title ltx_runin ltx_font_bold ltx_title_theorem">
         <span class="ltx_tag ltx_tag_theorem">
          Assumption 1
         </span>
         (Linear, Rank
         m
         , Means)
        </h6>
        <div class="ltx_para" id="Thmassumption1.p1">
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx5">
          <tr class="ltx_equation ltx_align_baseline" id="S3.Ex3">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            𝔼[zi|π𝒙(zi),𝒙]=𝑨(zi|zπ𝒙⁢(zi),𝒙)π𝒙(zi)∀i∈[H]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where 𝐀(zi|π𝐱(zi),𝐱)∈ℝm×m has rank m.
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx6">
          <tr class="ltx_equation ltx_align_baseline" id="S3.Ex4">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            𝔼[wi|π𝒙(wi),𝒙]=𝑪(wi|π𝒙(wi),𝒙)π𝒙(wi)∀i∈[ℓ(𝒙)]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where 𝐂(wi|π𝐱(wi),𝐱)∈ℝp×m has rank m.
         </p>
        </div>
        <div class="ltx_para" id="Thmassumption1.p2">
         <p class="ltx_p">
          Also assume that 𝔼[zizi⊤|𝐱] has rank m ∀i∈[H].
         </p>
        </div>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Note that the matrices
         𝑨
         and
         𝑪
         are a direct function of
         θ⁢(𝒙)
         , but we do not specify a model family for
         θ⁢(𝒙)
         . The only restriction
is in the form of the above assumption. If
         wi
         and
         zi
         were discrete, represented as binary vectors, the above assumption would correspond to requiring all conditional probability tables in the latent tree to have rank
         m
         .
Assumption
         1
         allows for the
         wi
         to be high dimensional features, as long as the expectation requirement above is satisfied.
Similar assumptions are made with spectral parameter learning methods e.g.
         Hsu et al.2009
         ,
         Bailly et al.2009
         ,
         Parikh et al.2011
         , and
         Cohen et al.2012
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Furthermore, Assumption
         1
         makes it explicit that regardless of the size of
         p
         , the relationships among the variables in the latent tree are restricted to be of rank
         m
         , and are thus
         low rank
         since
         p&gt;m
         .
To leverage this low rank structure, we propose using the following additive metric, a normalized variant of that in
         Anandkumar et al.2011
         :
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx7">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_center">
           dspectral⁢(i,j)=-log⁡Λm⁢(𝚺𝒙⁢(i,j))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_center">
           +12⁢log⁡Λm⁢(𝚺𝒙⁢(i,i))+12⁢log⁡Λm⁢(𝚺𝒙⁢(j,j))
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
         where
         Λm⁢(𝑨)
         denotes the product of the top
         m
         singular values of
         𝑨
         and
         𝚺𝒙(i,j):=𝔼[vivj⊤|𝒙]
         , i.e. the uncentered cross-covariance matrix.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         We can then show that this metric is additive:
        </p>
       </div>
       <div class="ltx_theorem ltx_theorem_lemma" id="Thmlemma1">
        <h6 class="ltx_title ltx_runin ltx_font_bold ltx_title_theorem">
         <span class="ltx_tag ltx_tag_theorem">
          Lemma 1
         </span>
        </h6>
        <div class="ltx_para" id="Thmlemma1.p1">
         <p class="ltx_p">
          If Assumption 1 holds then, dspectral is an additive tree metric (Definition 1).
         </p>
        </div>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         A proof is in the supplementary for completeness.
From here, we use
         d
         to denote
         dspectral
         , since that is the metric
we use for our learning algorithm.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Recovering the Minimal Projective Latent Tree
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         It has been shown
         [Rzhetsky and Nei1993]
         that for any additive tree metric,
         u⁢(𝒙)
         can be recovered by solving
         arg⁢minu∈𝒰⁡c⁢(u)
         for
         c⁢(u)
         :
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        c⁢(u)=∑(i,j)∈ℰud⁢(i,j).

(6)
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         where
         ℰu
         is the set of pairs of nodes which are adjacent to each other in
         u
         and
         d⁢(i,j)
         is computed using Eq.
         3
         and Eq.
         4
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         Note that the metric
         d
         we use in defining
         c⁢(u)
         is based on the expectations from the true distribution. In practice, the true distribution is unknown, and therefore we use an approximation for the distance metric
         d^
         . As we discussed in §
         3.1
         all elements of the distance matrix are functions of observable quantities if the underlying tree
         u
         is known. However, only the word-word sub-block
         𝑫W⁢W
         can be directly estimated from the data without knowledge of the tree structure.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p5">
        <p class="ltx_p">
         This subtlety makes solving the minimization problem in Eq.
         6
         NP-hard
         [Desper and Gascuel2005]
         if
         u
         is allowed to be an arbitrary undirected tree. However, if we restrict
         u
         to
be in
         𝒰
         , as we do in the above, then maximizing
         c^⁢(u)
         over
         𝒰
         can be solved
using the bilexical parsing algorithm from
         Eisner and Satta1999
         . This is because the computation of the other sub-blocks of the distance matrix only depend on the partitions of the nodes shown in Figure
         3
         into
         A
         ,
         B
         ,
         G
         , and
         H
         , and not on the entire tree structure.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p6">
        <p class="ltx_p">
         Therefore, the procedure to find a bracketing for a given POS tag
         𝒙
         is to first estimate the distance matrix sub-block
         𝑫^W⁢W
         from raw text data (see §
         3.4
         ),
and then solve the optimization problem
         arg⁢minu∈𝒰⁡c^⁢(u)
         using a variant of the Eisner-Satta algorithm where
         c^⁢(u)
         is identical to
         c⁢(u)
         in Eq.
         6
         , with
         d
         replaced with
         d^
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p7">
        <p class="ltx_p">
         [t!]
         Inputs:
         Set of examples
         (𝒘(i),𝒙(i))
         for
         i∈[N]
         , a kernel
         Kγ(j,k,j′,k′|𝒙,𝒙′)
         , an integer
         m
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p8">
        <p class="ltx_p">
         Data structures:
         For each
         i∈[N],j,k∈ℓ⁢(𝒙(i))
         there is a (uncentered) covariance matrix
         𝚺^𝒙(i)⁢(j,k)∈ℝp×p
         ,
and a distance
         d^spectral⁢(j,k)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p9">
        <p class="ltx_p">
         Algorithm:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p10">
        <p class="ltx_p">
         (Covariance estimation)
         ∀i∈[N],j,k∈ℓ⁢(𝒙(i))
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p11">
        <ul class="ltx_itemize">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Let
            Cj′,k′|i′=wj′(i′)⁢(wk′(i′))⊤
            ,
            kj,k,j′,k′,i,i′=Kγ(j,k,j′,k′|𝒙(i),𝒙(i′))
            and
            ℓi′=ℓ⁢(𝒙(i′))
            , and estimate each
            p×p
            covariance matrix as:
           </p>
           <table class="ltx_equationgroup ltx_eqn_align" id="A0.EGx8">
            <tr class="ltx_equation ltx_align_baseline" id="S3.Ex6">
             <td class="ltx_eqn_center_padleft">
             </td>
             <td class="ltx_td ltx_align_right">
              𝚺^𝒙⁢(j,k)=
             </td>
             <td class="ltx_eqn_center_padright">
             </td>
            </tr>
            <tr class="ltx_equation ltx_align_baseline" id="S3.Ex7">
             <td class="ltx_eqn_center_padleft">
             </td>
             <td class="ltx_td ltx_align_right">
             </td>
             <td class="ltx_td ltx_align_left">
              ∑i′=1N∑j′=1ℓi′∑k′=1ℓi′kj,k,j′,k′,i,i′⁢Cj′,k′|i′∑i′=1N∑j′=1ℓi′∑k′=1ℓi′kj,k,j′,k′,i,i′
             </td>
             <td class="ltx_eqn_center_padright">
             </td>
            </tr>
           </table>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Compute
            d^spectral⁢(j,k)⁢∀j,k∈ℓ⁢(𝒙(i))
            using Eq.
            5
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS3.p12">
        <p class="ltx_p">
         (Uncover structure)
         ∀i∈[N]
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p13">
        <ul class="ltx_itemize">
         <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i1.p1">
           <p class="ltx_p">
            Find
            u^(i)=arg⁢minu∈𝒰⁡c^⁢(u)
            , and for the
            i
            th example, return the structure
            hdir⁢(u^(i))
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS3.p14">
        <p class="ltx_p">
         The learning algorithm for finding the latent structure from a set of examples (𝒘(i),𝒙(i)), i∈[N].
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p15">
        <p class="ltx_p">
         Summary.
         We first defined a generative model that describes how a sentence, its sequence of POS tags, and its bracketing is generated (§
         2.3
         ).
First an undirected
         u∈𝒰
         is generated (only as a function of the POS tags), and then
         u
         is mapped to a bracketing using a direction mapping
         hdir
         . We then showed that we can define a distance metric between nodes in the undirected tree, such that minimizing
it leads to a recovery of
         u
         . This distance metric can be computed based only on the text, without needing to identify the latent information (§
         3.2
         ).
If the true distance metric is known, with respect to the true distribution that generates the words in a sentence, then
         u
         can be fully recovered
by optimizing the cost function
         c⁢(u)
         . However, in practice the distance metric must be estimated from data, as discussed below.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Estimation of
        d
        from Sparse Data
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         We now address the data sparsity problem, in particular that
         𝒟⁢(𝒙)
         can be very small, and therefore estimating
         d
         for each POS sequence separately can be problematic.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         In order to estimate
         d
         from data, we need to estimate the covariance matrices
         𝚺𝒙⁢(i,j)
         (for
         i,j∈{1,…,ℓ⁢(𝒙)}
         ) from Eq.
         5
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p3">
        <p class="ltx_p">
         To give some motivation to our solution, consider estimating the covariance matrix
         𝚺𝒙⁢(1,2)
         for the tag sequence
         𝒙=(𝙳𝚃𝟷,𝙽𝙽𝟸,𝚅𝙱𝙳𝟹,𝙳𝚃𝟺,𝙽𝙽𝟻)
         .
         𝒟⁢(𝒙)
         may be insufficient for an accurate empirical estimate. However, consider another sequence
         𝒙′=(𝚁𝙱𝟷,𝙳𝚃𝟸,𝙽𝙽𝟹,𝚅𝙱𝙳𝟺,𝙳𝚃𝟻,𝙰𝙳𝙹𝟼,𝙽𝙽𝟽)
         . Although
         𝒙
         and
         𝒙′
         are not identical, it is likely that
         𝚺𝒙′⁢(2,3)
         is similar to
         𝚺𝒙⁢(1,2)
         because the determiner and the noun appear in similar syntactic context.
         𝚺𝒙′⁢(5,7)
         also may be somewhat similar,
but
         𝚺𝒙′⁢(2,7)
         should not be very similar to
         𝚺𝒙⁢(1,2)
         because the noun and the determiner appear in a different syntactic context.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p4">
        <p class="ltx_p">
         The observation that the covariance matrices depend on local syntactic context is the main driving force behind our solution. The local syntactic context acts as an “anchor,” which
enhances or replaces a word index in a sentence with local syntactic context.
More formally, an anchor is a function
         G
         that maps a word index
         j
         and a sequence of POS tags
         𝒙
         to a local context
         G⁢(j,𝒙)
         . The anchor we use
is
         G⁢(j,𝒙)=(j,xj)
         . Then, the covariance matrices
         𝚺𝒙
         are estimated using kernel smoothing
         [Hastie et al.2009]
         , where the smoother
tests similarity between the different anchors
         G⁢(j,𝒙)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p5">
        <p class="ltx_p">
         The full learning algorithm is given in Figure
         3.3
         . The first step in the algorithm is to estimate the covariance matrix block
         𝚺^𝒙(i)⁢(j,k)
         for each
training example
         𝒙(i)
         and each pair of preterminal positions
         (j,k)
         in
         𝒙(i)
         . Instead of computing this block by computing the empirical covariance matrix for positions
         (j,k)
         in
the data
         𝒟⁢(𝒙)
         , the algorithm uses all of the pairs
         (j′,k′)
         from all of
         N
         training examples. It averages the empirical covariance matrices from these contexts using a kernel
weight, which gives a similarity measure for the position
         (j,k)
         in
         𝒙(i)
         and
         (j′,k′)
         in another example
         𝒙(i′)
         .
         γ
         is the kernel “bandwidth”, a user-specified parameter that controls how inclusive the kernel will be with respect to examples in
         𝒟
         (see §
         4.1
         for a concrete example). Note that the learning algorithm is such that it ensures that
         𝚺^𝒙(i)⁢(j,k)=𝚺^𝒙(i′)⁢(j′,k′)
         if
         G⁢(j,𝒙(i))=G⁢(j′,𝒙(i′))
         and
         G⁢(k,𝒙(i))=G⁢(k′,𝒙(i′))
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p6">
        <p class="ltx_p">
         Once the empirical estimates for the covariance matrices are obtained, a variant of the Eisner-Satta algorithm is used, as mentioned in §
         3.3
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.5
        </span>
        Theoretical Guarantees
       </h3>
       <div class="ltx_para" id="S3.SS5.p1">
        <p class="ltx_p">
         Our main theoretical guarantee is that Algorithm 1 will recover the correct tree
         u∈𝒰
         with high probability, if the given top bracket is correct and if we obtain enough examples
         (𝒘(i),𝒙(i))
         from the model in §2. We give the theorem statement below. The constants lurking in the
         O
         -notation and the full proof are in the supplementary.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS5.p2">
        <p class="ltx_p">
         Denote
         σ𝒙⁢(j,k)(r)
         as the
         rt⁢h
         singular value of
         𝚺𝒙⁢(j,k)
         . Let
         σ∗⁢(x):=minj,k∈ℓ⁢(𝒙)⁡min⁡(σ𝒙⁢(j,k)(m))
         .
        </p>
       </div>
       <div class="ltx_theorem ltx_theorem_theorem" id="Thmtheorem1">
        <h6 class="ltx_title ltx_runin ltx_font_bold ltx_title_theorem">
         <span class="ltx_tag ltx_tag_theorem">
          Theorem 1
         </span>
        </h6>
        <div class="ltx_para" id="Thmtheorem1.p1">
         <p class="ltx_p">
          Define u^ as the estimated tree for tag sequence 𝐱 and u⁢(𝐱) as the correct tree. Let
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx9">
          <tr class="ltx_equation ltx_align_baseline" id="S3.Ex8">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            △⁢(𝒙):=minu′∈𝒰:u′≠u⁢(𝒙)⁡(c⁢(u⁢(𝒙))-c⁢(u′))/(8⁢|ℓ⁢(𝒙)|)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="Thmtheorem1.p2">
         <p class="ltx_p">
          Assume that
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="A0.EGx10">
          <tr class="ltx_equation ltx_align_baseline" id="S3.Ex9">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            N≥𝒪⁢(m2⁢log⁡(p2⁢ℓ⁢(𝒙)2δ)min⁡(σ∗⁢(𝒙)2⁢△⁢(𝒙)2,σ∗⁢(𝒙)2)⁢ν𝒙⁢(γ)2)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          Then with probability 1-δ, u^=u⁢(𝐱).
         </p>
        </div>
       </div>
       <div class="ltx_para" id="S3.SS5.p3">
        <p class="ltx_p">
         where
         ν𝒙⁢(γ)
         , defined in the supplementary, is a function of the underlying distribution over the tag sequences
         𝒙
         and the kernel bandwidth
         γ
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS5.p4">
        <p class="ltx_p">
         Thus, the sample complexity of our approach depends on the dimensionality of the latent and observed states (
         m
         and
         p
         ), the underlying singular values of the cross-covariance matrices (
         σ∗⁢(𝒙)
         ) and the difference in the cost of the true tree compared to the cost of the incorrect trees (
         △⁢(𝒙)
         ).
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
        We report results on three different languages: English, German, and Chinese. For English we use the Penn treebank
        [Marcus et al.1993]
        , with sections 2–21 for training and section 23 for final testing. For German and Chinese we use the Negra treebank and the Chinese treebank respectively and the first 80% of the sentences are used for training and the last 20% for testing. All punctuation from the data is removed.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We primarily compare our method to the constituent-context model (CCM) of
        Klein and Manning2002
        . We also compare our method to the algorithm of
        Seginer2007
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Experimental Settings
       </h3>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Top bracket heuristic
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          Our algorithm requires the top bracket in order to direct the latent tree. In practice, we employ the following heuristic to find the bracket using the following three steps:
         </p>
         <ul class="ltx_itemize">
          <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i1.p1">
            <p class="ltx_p">
             If there exists a comma/semicolon/colon at index
             i
             that has at least a verb before
             i
             and both a noun followed by a verb after
             i
             , then return
             ([0,i-1],[i,ℓ⁢(x)])
             as the top bracket. (Pick the rightmost comma/semicolon/colon if multiple satisfy the criterion).
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i2.p1">
            <p class="ltx_p">
             Otherwise find the first non-participle verb (say at index
             j
             ) and return
             ([0,j-1],[j,ℓ⁢(𝒙)])
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I5.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i3.p1">
            <p class="ltx_p">
             If no verb exists, return
             ([0,1],[1,ℓ⁢(𝒙)])
             .
            </p>
           </div>
          </li>
         </ul>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Word embeddings
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          As mentioned earlier, each
          wi
          can be an arbitrary feature vector. For all languages we use Brown clustering
          [Brown et al.1992]
          to construct a
          log⁡(C)+C
          feature vector where the first
          log⁡(C)
          elements indicate which mergable cluster the word belongs to, and the last
          C
          elements indicate the cluster identity. For English, more sophisticated word embeddings are easily obtainable, and we experiment with neural word embeddings
          Turian et al.2010
          of length 50. We also explored two types of CCA embeddings: OSCCA and TSCCA, given in
          Dhillon et al.2012
          . The OSCCA embeddings behaved better, so we only report its results.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Choice of kernel
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P3.p1">
         <p class="ltx_p">
          For our experiments, we use the kernel
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="A0.EGx11">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex10">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            Kγ(j,k,j′,k′|𝒙,𝒙′)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex11">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            =max⁡{0,1-κ(j,k,j′,k′|𝒙,𝒙′)γ}
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
          γ
          denotes the user-specified bandwidth, and
          κ(j,k,j′,k′|𝒙,𝒙′)=|j-k|-|j′-k′||j-k|+|j′-k′|
          if
          𝒙⁢(j)=𝒙⁢(j′)
          and
          𝒙⁢(k′)=𝒙⁢(k)
          , and
          sign⁢(j-k)=sign⁢(j′-k′)
          (and
          ∞
          otherwise).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P3.p2">
         <p class="ltx_p">
          The kernel is non-zero if and only if the tags at position
          j
          and
          k
          in
          𝒙
          are identical to the ones in position
          j′
          and
          k′
          in
          𝒙′
          , and if the direction between
          j
          and
          k
          is identical to the one between
          j′
          and
          k′
          . Note that the kernel is not binary, as opposed to the theoretical kernel in the supplementary material.
Our experiments show that using a non-zero value different than 1 that is a function of the distance between
          j
          and
          k
          compared to the distance between
          j′
          and
          k′
          does better in practice.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P4">
        <h4 class="ltx_title ltx_title_paragraph">
         Choice of data
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p1">
         <p class="ltx_p">
          For CCM, we found that if the full dataset (all sentence lengths) is used in training, then performance degrades when evaluating on sentences of length
          ≤10
          . We therefore restrict the data used with CCM to sentences of length
          ≤ℓ
          , where
          ℓ
          is the maximal sentence length being evaluated. This does not happen with our algorithm, which manages to leverage lexical information whenever more data is available. We therefore use the full data for our method for all lengths.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p2">
         <p class="ltx_p">
          We also experimented with the original POS tags and the universal POS tags of
          Petrov et al.2011
          . Here, we found out that our method does better with the universal part of speech tags. For CCM, we also experimented with the original parts of speech, universal tags (CCM-U), the cross-product of the original parts of speech with the Brown clusters (CCM-OB), and the cross-product of the universal tags with the Brown clusters (CCM-UB). The results in Table
          1
          indicate that the vanilla setting is the best for CCM.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS0.P4.p3">
         <p class="ltx_p">
          Thus, for all results, we use universal tags for our method and the original POS tags for CCM. We believe that our approach substitutes the need for fine-grained POS tags with the lexical information. CCM, on the other hand, is fully unlexicalized.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P5">
        <h4 class="ltx_title ltx_title_paragraph">
         Parameter Selection
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS0.P5.p1">
         <p class="ltx_p">
          Our method requires two parameters, the latent dimension
          m
          and the bandwidth
          γ
          .
CCM also has two parameters, the number of extra constituent/distituent counts used for smoothing. For both methods we chose the best parameters for sentences of length
          ℓ≤10
          on the English Penn Treebank (training) and used this set for all other experiments.
This resulted in
          m=7,γ=0.4
          for our method and
          2
          ,
          8
          for CCM’s extra constituent/distituent counts respectively. We also tried letting CCM choose different hyperparameters for different sentence lengths based on dev-set likelihood, but this gave worse results than holding them fixed.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Results
       </h3>
       <div class="ltx_paragraph" id="S4.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Test I: Accuracy
        </h4>
        <div class="ltx_para" id="S4.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          Table
          2
          summarizes our results.
CCM is used with the initializer proposed in
          Klein and Manning2002
          .
          NN, CC, and BC indicate the performance of our method
for neural embeddings, CCA embeddings, and Brown clustering respectively, using the heuristic for
          hdir
          described in §
          4.1
          . NN-O, CC-O, and BC-O indicate that the oracle (i.e. true top bracket) was used for
          hdir
          . For our method, test set results can be obtained by using Algorithm
          3.3
          (except the distances are computed using the training data).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS0.P1.p2">
         <p class="ltx_p">
          For English, while CCM behaves better for short sentences (
          ℓ≤10
          ), our algorithm is more robust with longer sentences.
This is especially noticeable for length
          ≤40
          ,
where CCM breaks down and our algorithm is more stable.
We find that the neural embeddings modestly outperform the CCA and Brown cluster embeddings.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS0.P1.p3">
         <p class="ltx_p">
          The results for German are similar, except CCM breaks down earlier at sentences of
          ℓ≤30
          . For Chinese, our method substantially outperforms CCM for all lengths. Note that CCM performs very poorly, obtaining only around
          20⁢%
          accuracy even for sentences of
          ℓ≤20
          . We didn’t have neural embeddings for German and Chinese (which worked best for English) and thus only used Brown cluster embeddings.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS0.P1.p4">
         <p class="ltx_p">
          For English, the disparity between NN-O (oracle top bracket) and NN (heuristic top bracket) is rather low suggesting that our top bracket heuristic is rather effective. However, for German and Chinese note that the “BC-O” performs substantially better, suggesting that if we had a better top bracket heuristic our performance would increase.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Test II: Sensitivity to initialization
        </h4>
        <div class="ltx_para" id="S4.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          The EM algorithm with the CCM requires very careful initialization, which is described in
          Klein and Manning2002
          . If, on the other hand, random initialization is used, the variance of the
performance of the CCM varies greatly. Figure
          4
          shows a histogram of the performance level for sentences of length
          ≤10
          for different random
initializers. As one can see, for some restarts, CCM obtains accuracies lower than
          30⁢%
          due to local optima.
Our method does not suffer from local optima and thus does not require careful initialization.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS2.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Test III: Comparison to Seginer’s algorithm
        </h4>
        <div class="ltx_para" id="S4.SS2.SSS0.P3.p1">
         <p class="ltx_p">
          Our approach is not directly comparable to Seginer’s because he uses punctuation, while we use POS tags. Using Seginer’s parser we were able to get results on the training sets. On English:
          75.2⁢%
          (
          ℓ≤10
          ),
          64.2⁢%
          (
          ℓ≤20
          ),
          56.7⁢%
          (
          ℓ≤40
          ). On German:
          57.8⁢%
          (
          ℓ≤10
          ),
          45.0⁢%
          (
          ℓ≤20
          ), and
          39.9⁢%
          (
          ℓ≤40
          ). On Chinese:
          56.6⁢%
          (
          ℓ≤10
          ),
          45.1⁢%
          (
          ℓ≤20
          ), and
          38.9⁢%
          (
          ℓ≤40
          ).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS0.P3.p2">
         <p class="ltx_p">
          Thus, while Seginer’s method performs better on English, our approach performs 2-3 points better on German, and both methods give similar performance on Chinese.
         </p>
        </div>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
