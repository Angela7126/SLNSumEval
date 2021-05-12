<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Unsupervised Dependency Parsing with Transferring Distribution via Parallel Guidance and Entropy Regularization.
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
       We present a novel approach for inducing unsupervised dependency parsers for languages that have no labeled training data, but have
translated text in a resource-rich language. We train probabilistic parsing models for resource-poor languages by transferring cross-lingual
knowledge from resource-rich language with entropy regularization. Our method can be used as a purely monolingual dependency parser,
requiring no human translations for the test data, thus making it applicable to a wide range of resource-poor languages.
We perform experiments on three Data sets — Version 1.0 and version 2.0 of Google Universal Dependency Treebanks and Treebanks from CoNLL
shared-tasks, across ten languages. We obtain state-of-the art performance of all the three data sets when compared with
previously studied unsupervised and projected parsing systems.
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
        In recent years, dependency parsing has gained universal interest due to its usefulness in a
wide range of applications such as synonym generation
        [43]
        , relation extraction
        [37]
        and machine translation
        [21, 51]
        . Several supervised dependency parsing algorithms
        [39, 30, 32, 33, 8, 24, 27, 52]
        have been proposed and achieved high parsing accuracies on several treebanks, due in large part to the availability
of dependency treebanks in a number of languages
        [31]
        . However, the manually annotated treebanks that
these parsers rely on are highly expensive to create, in particular when we want to build treebanks for resource-poor languages.
This led to a vast amount of research on unsupervised grammar induction
        [9, 22, 47, 12, 48, 4, 29, 49]
        , which appears to be a natural solution to this problem, as unsupervised methods require only unannotated text for training parsers.
Unfortunately, the unsupervised grammar induction systems’ parsing accuracies often significantly fall behind those of supervised
systems
        [34]
        . Furthermore, from a practical standpoint, it is rarely the case that we are
completely devoid of resources for most languages.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper, we consider a practically motivated scenario, in which we want to build statistical parsers for resource-poor target
languages, using existing resources from a resource-rich source language (like English).
        We assume that there are absolutely no labeled training data for the target language, but we have access to parallel data with a
resource-rich language and a sufficient amount of labeled training data to build an accurate parser for the resource-rich language.
This scenario appears similar to the setting in bilingual text parsing. However, most bilingual text parsing approaches require
bilingual treebanks — treebanks that have manually annotated tree structures on both sides of source and target languages
        [45, 7]
        , or have tree structures on the source side and translated
sentences in the target languages
        [18, 10]
        . Obviously, bilingual treebanks
are much more difficult to acquire than the resources required in our scenario, since the labeled training data and the parallel text
in our case are completely separated. What is more important is that most studies on bilingual text parsing assumed that the parser is
applied only on bilingual text. But our goal is to develop a parser that can be used in completely monolingual setting for each
target language of interest.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        This scenario is applicable to a large set of languages and many research studies
        [19]
        have
been made on it. Ganchev et al.
        [14]
        presented a parser projection approach
via parallel text using the posterior regularization framework
        [16]
        .
McDonald et al.
        [34]
        proposed two parser transfer approaches between
two different languages — one is directly transferred parser from delexicalized parsers, and the other parser is transferred using
constraint driven learning algorithm where constraints are drawn from parallel corpora. In that work, they demonstrate that
even the directly transferred delexicalized parser produces significantly higher accuracies than unsupervised parsers.
Cohen et al.
        [11]
        proposed an approach for unsupervised dependency parsing with non-parallel
multilingual guidance from one or more helper languages, in which parallel data is not used.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In this work, we propose a learning framework for transferring dependency grammars from a resource-rich language to resource-poor
languages via parallel text. We train probabilistic parsing models for resource-poor languages by maximizing a combination of
likelihood on parallel data and confidence on unlabeled data. Our work is based on the learning framework used in
Smith and Eisner
        [44]
        , which is originally designed for parser bootstrapping.
We extend this learning framework so that it can be used to transfer cross-lingual knowledge between different languages.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Throughout this paper, English is used as the source language and we evaluate our approach on ten target
languages — Danish (da), Dutch (nl), French (fr), German (de), Greek (el), Italian (it), Korean (ko), Portuguese (pt),
Spanish (es) and Swedish (sv).
Our approach achieves significant improvement over previous state-of-the-art unsupervised and projected parsing systems
across all the ten languages, and considerably bridges the gap to fully supervised dependency parsing performance.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Our Approach
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Dependency trees represent syntactic relationships through labeled directed edges between heads and their dependents.
For example, Figure
        1
        shows a dependency tree for the sentence,
        Economic news had little effect on financial markets
        , with the sentence’s root-symbol as its root.
The focus of this work is on building dependency parsers for target languages, assuming that an accurate English dependency parser
and some parallel text between the two languages are available. Central to our approach is a maximizing likelihood learning framework,
in which we use an English parser and parallel text to estimate the “transferring distribution” of the target language
parsing model (See Section
        2.2
        for more details).
Another advantage of the learning framework is that it combines both the likelihood on parallel data and confidence on unlabeled data,
so that both parallel text and unlabeled data can be utilized in our approach.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Edge-Factored Parsing Model
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         In this paper, we will use the following notation:
         𝒙
         represents a generic input sentence,
and
         𝒚
         represents a generic dependency tree.
         T⁢(𝒙)
         is used to denote the set of
possible dependency trees for sentence
         𝒙
         . The probabilistic model for dependency parsing defines a family of
conditional probability
         pλ(𝒚|𝒙)
         over all
         𝒚
         given
sentence
         𝒙
         , with a log-linear form:
        </p>
        pλ(𝒚|𝒙)=1Z⁢(𝒙)exp{∑jλjFj(𝒚,𝒙)}

(1)
        <p class="ltx_p">
         where
         Fj
         are feature functions,
         λ=(λ1,λ2,…)
         are parameters of the model,
and
         Z⁢(𝒙)
         is a normalization factor, which is commonly referred to as the
         partition function
         :
        </p>
        Z⁢(𝒙)=∑𝒚∈T⁢(𝒙)exp⁡{∑jλj⁢Fj⁢(𝒚,𝒙)}

(2)
        <p class="ltx_p">
         A common strategy to make this parsing model efficiently computable is to
         factor
         dependency trees into sets of edges:
        </p>
        Fj⁢(𝒚,𝒙)=∑e∈yfj⁢(e,𝒙).

(3)
        <p class="ltx_p">
         That is, dependency tree
         y
         is treated as a set of edges
         e
         and each feature function
         Fj⁢(𝒚,𝒙)
         is equal to the sum of all the features
         fj⁢(e,𝒙)
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         We denote the
         weight function
         of each edge
         e
         as follows:
        </p>
        w⁢(e,𝒙)=exp⁡{∑jλj⁢fj⁢(e,𝒙)}

(4)
        <p class="ltx_p">
         and the conditional probability
         pλ(𝒚|𝒙)
         has the following form:
        </p>
        pλ(𝒚|𝒙)=1Z⁢(𝒙)∏e∈yw(e,𝒙)

(5)
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Model Training
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         One of the most common model training methods for supervised dependency parser is Maximum conditional likelihood estimation.
For a supervised dependency parser with a set of training data
         {(𝒙i,𝒚i)}
         ,
the logarithm of the likelihood (a.k.a. the log-likelihood) is given by:
        </p>
        L(λ)=∑ilogpλ(𝒚i|𝒙i)

(6)
        <p class="ltx_p">
         Maximum likelihood training chooses parameters such that the log-likelihood
         L⁢(λ)
         is maximized.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         However, in our scenario we have no labeled training data for target languages but we have some parallel and unlabeled data plus an
English dependency parser. For the purpose of transferring cross-lingual information from the English parser via parallel text,
we explore the model training method proposed by Smith and Eisner
         [44]
         , which presented
a generalization of
         K
         function
         [1]
         , and related it to another semi-supervised learning technique,
entropy regularization
         [20, 28]
         . The objective
         K
         function to be minimized is actually the
         expected
         negative log-likelihood:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           K
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           -∑i∑𝒚ip~(𝒚i|𝒙i)logpλ(𝒚i|𝒙i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="2">
           <span class="ltx_tag ltx_tag_equation">
            (7)
           </span>
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
           ∑iD(p~i||pλ,i)+H(p~i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         p~i(⋅)=d⁢e⁢fp~(⋅|𝒙i)
         and
         pλ,i(⋅)=d⁢e⁢fpλ(⋅|𝒙i)
         .
         p~(𝒚|𝒙)
         is the “transferring distribution” that reflects our uncertainty
about the true labels, and we are trying to learn a parametric model
         pλ(𝒚|𝒙)
         by
minimizing the
         K
         function.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         In our scenario, we have a set of aligned parallel data
         P={𝒙is,𝒙it,ai}
         where
         ai
         is the word alignment for the pair of source-target sentences
         (𝒙is,𝒙it)
         ,
and a set of unlabeled sentences of the target language
         U={𝒙it}
         . We also have a trained English
parsing model
         pλE(𝒚|𝒙)
         . Then the
         K
         in equation (
         7
         ) can be divided
into two cases, according to whether
         𝒙i
         belongs to parallel data set
         P
         or unlabeled data set
         U
         .
For the unlabeled examples
         {𝒙i∈U}
         , some previous studies (e.g.,
         [1]
         ) simply use a
uniform distribution over labels (e.g., parses), to reflect that the label is unknown. We follow the method in
Smith and Eisner
         [44]
         and take the transferring distribution
         p~i
         to be
the
         actual
         current belief
         pλ,i
         . The total contribution of the
         unsupervised
         examples to
         K
         then
simplifies to
         KU=∑𝒙i∈UH⁢(pλ,i)
         , which may be regarded as the entropy item used
to constrain the model’s uncertainty
         H
         to be low, as presented in the work on
entropy regularization
         [20, 28]
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         But how can we define the transferring distribution for the parallel examples
         {𝒙it∈P}
         ?
We define the transferring distribution by defining the
         transferring weight
         utilizing the
English parsing model
         pλE(𝒚|𝒙)
         via parallel data with word alignments:
        </p>
        w~⁢(et,𝒙it)={wE⁢(es,𝒙is),if ⁢et⟶a⁢l⁢i⁢g⁢neswE⁢(ed⁢e⁢l⁢e⁢xt,𝒙is),otherwise

(8)
        <p class="ltx_p">
         where
         wE(⋅,⋅)
         is the weight function of the English parsing model
         pλE(𝒚|𝒙)
         ,
and
         ed⁢e⁢l⁢e⁢xt
         is the delexicalized form
         of the edge
         et
         .
From the definition of the transferring weight, we can see that, if an edge
         et
         of the target language sentence
         𝒙it
         is aligned to an edge
         es
         of the English sentence
         𝒙is
         , we transfer the weight of edge
         et
         to the
corresponding weight of edge
         es
         in the English parsing model
         pλE(𝒚|𝒙)
         .
If the edge
         et
         is not aligned to any edges of the English sentence
         𝒙is
         , we reduce the edge
         et
         to
the delexicalized form and calculate the transferring weight in the English parsing model. There are two advantages for this
definition of the transferring weight. First, by transferring the weight function to the corresponding weight in the well-developed
English parsing model, we can project syntactic information across language boundaries.
Second, McDonald et al.
         [34]
         demonstrates that parsers with
only delexicalized features produce considerably high parsing performance. By reducing unaligned edges to their delexicalized forms,
we can still use those delexicalized features, such as part-of-speech tags, for those unaligned edges, and can address problem that
automatically generated word alignments include errors.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p5">
        <p class="ltx_p">
         From the definition of transferring weight in equation (
         8
         ), the transferring distribution can be defined in the following way:
        </p>
        p~(𝒚|𝒙)=1Z~⁢(𝒙)∏e∈yw~(e,𝒙)

(9)
        <p class="ltx_p">
         where
        </p>
        Z~⁢(𝒙)=∑y∏e∈yw~⁢(e,𝒙)

(10)
        <p class="ltx_p">
         Due to the normalizing factor
         Z~⁢(𝒙)
         , the transferring distribution is a valid one.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p6">
        <p class="ltx_p">
         We introduce a multiplier
         γ
         as a trade-off between the two contributions (parallel and unsupervised) of the objective function
         K
         ,
and the final objective function
         K′
         has the following form:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           K′
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           -∑xi∈P∑yip~(𝒚i|𝒙i)logpλ(𝒚i|𝒙i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="3">
           <span class="ltx_tag ltx_tag_equation">
            (11)
           </span>
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           +γ∑xi∈UH(pλ,i)
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
           KP+γ⁢KU
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         KP
         and
         KU
         are the contributions of the parallel and unsupervised data, respectively.
One may regard
         γ
         as a Lagrange multiplier that is used to constrain the parser’s uncertainty H to be low,
as presented in several studies on entropy regularization
         [5, 17, 20]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Algorithms and Complexity for Model Training
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         To train our parsing model, we need to find out the parameters
         λ
         that minimize the objective function
         K′
         in equation (
         11
         ).
This optimization problem is typically solved using quasi-Newton numerical methods such as L-BFGS
         [36]
         ,
which requires efficient calculation of the objective function and the gradient of the objective function.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         The first item (
         KP
         ) of the
         K′
         function in equation (
         11
         ) can be rewritten in the following form:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           KP
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           -∑𝒙i∈P[∑yip~(𝒚i|𝒙i)∑e∈𝒚ilogw(e,𝒙i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="2">
           <span class="ltx_tag ltx_tag_equation">
            (12)
           </span>
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           -logZ(𝒙i)]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         and according to equation (
         1
         ) and (
         3
         ) the gradient of
         KP
         can be written as:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx4">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ∂⁡KP∂⁡λj
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑xi∈P∂p~(𝒚i|𝒙i)logpλ(𝒚i|𝒙i)∂⁡λj
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="3">
           <span class="ltx_tag ltx_tag_equation">
            (13)
           </span>
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
           ∑xi∈P[∑yip~(𝒚i|𝒙i)∑e∈yifj(e,𝒙i)
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
          </td>
          <td class="ltx_td ltx_align_left">
           -∑yipλ(𝒚i|𝒙i)∑e∈yifj(e,𝒙i)]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         According to equation (
         9
         ),
         p~(𝒚|𝒙)
         can also be factored into the multiplication of
the weight of each edge, so both
         KP
         and its gradient can be calculated by running the
         O⁢(n3)
         inside-outside
algorithm
         [2, 41]
         for projective parsing. For non-projective parsing, the analogy to the inside algorithm
is the
         O⁢(n3)
         matrix-tree algorithm based on Kirchhoff’s Matrix-Tree Theorem, which is dominated asymptotically by a
matrix determinant
         [25, 46]
         . The gradient of a determinant may be computed by matrix inversion,
so evaluating the gradient again has the same
         O⁢(n3)
         complexity as evaluating the function.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         The second item (
         KU
         ) of the
         K′
         function in equation (
         11
         ) is the Shannon entropy of the posterior distribution over
parsing trees, and can be written into the following form:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx5">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E14">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           KU
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           -∑𝒙i∈U[∑yipλ(𝒚i|𝒙i)∑e∈𝒚ilogw(e,𝒙i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="2">
           <span class="ltx_tag ltx_tag_equation">
            (14)
           </span>
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           -logZ(𝒙i)]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         and the gradient of
         KU
         is in the following:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx6">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E15">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ∂⁡KU∂⁡λj
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑xi∈U∂pλ(𝒚i|𝒙i)logpλ(𝒚i|𝒙i)∂⁡λj
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="4">
           <span class="ltx_tag ltx_tag_equation">
            (15)
           </span>
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
           -∑yipλ(𝒚i|𝒙i)logpλ(𝒚i|𝒙i)Fj(𝒚i,𝒙i)
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
           +
          </td>
          <td class="ltx_td ltx_align_left">
           (∑yipλ(𝒚i|𝒙i)logpλ(𝒚i|𝒙i))
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
           ⋅
          </td>
          <td class="ltx_td ltx_align_left">
           (∑yipλ(𝒚i|𝒙i)Fj(𝒚i,𝒙i))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Similar with the calculation of
         KP
         ,
         KU
         can also be computed by running the inside-outside
algorithm
         [2, 41]
         for projective parsing.
For the gradient of
         KU
         , both the two multipliers of the second item in equation (
         15
         ) can be computed using the same
inside-outside algorithm. For the first item in equation (
         15
         ), an
         O⁢(n3)
         dynamic programming algorithm that
is closely related to the forward-backward algorithm
         [28]
         for the entropy regularized CRF
         [20]
         can be used for projective parsing. For non-projective parsing, however, the runtime rises to
         O⁢(n4)
         . In this paper, we focus on
projective parsing.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Summary of Our Approach
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         To summarize the description in the previous sections, our approach is performed in the following steps:
        </p>
        <ol class="ltx_enumerate" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Train an English parsing model
            pλE(𝒚|𝒙)
            , which is used to estimate
the transferring distribution
            p~(𝒚|𝒙)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Prepare parallel text by running word alignment method to obtain word alignments,
            and prepare the unlabeled data.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            Train a parsing model for the target language by minimizing the objective
            K′
            function which is the
combination of expected negative log-likelihood on parallel and unlabeled data.
           </p>
          </div>
         </li>
        </ol>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Data and Tools
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section, we illustrate the data sets used in our experiments and the tools for data preparation.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Choosing Target Languages
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Our experiments rely on two kinds of data sets: (i) Monolingual Treebanks with consistent annotation schema — English treebank is used
to train the English parsing model, and the Treebanks for target languages are used to evaluate the parsing performance of our approach.
(ii) Large amounts of parallel text with English on one side. We select target languages based on the availability of these resources.
The monolingual treebanks in our experiments are from the Google Universal Dependency Treebanks
         [31]
         , for
the reason that the treebanks of different languages in Google Universal Dependency Treebanks have consistent syntactic representations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         The parallel data come from the Europarl corpus version 7
         [23]
         and Kaist Corpus
         . Taking the intersection of languages in
the two kinds of resources yields the following seven languages: French, German, Italian, Korean, Portuguese, Spanish and
Swedish.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         The treebanks from CoNLL shared-tasks on dependency parsing
         [6, 38]
         appear to be another reasonable choice.
However, previous studies
         [34, 31]
         have demonstrated that a homogeneous
representation is critical for multilingual language technologies that require consistent cross-lingual analysis for downstream
components, and the heterogenous representations used in CoNLL shared-tasks treebanks weaken any conclusion that can be
drawn.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         For comparison with previous studies, nevertheless, we also run experiments on
CoNLL treebanks (see Section
         4.4
         for more details). We evaluate our approach on three target
languages from CoNLL shared task treebanks, which do not appear in Google Universal Treebanks.
The three languages are Danish, Dutch and Greek. So totally we have ten target languages. The parallel data for these three languages
are also from the Europarl corpus version 7.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Word Alignments
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         In our approach, word alignments for the parallel text are required. We perform word alignments with the open source
GIZA++ toolkit
         . The parallel corpus was preprocessed in standard ways, selecting
sentences with the length in the range from 3 to 100. Then we run GIZA++ with the default setting to generate word alignments in both
directions. We then make the intersection of the word alignments of two directions to generate one-to-one alignments.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Part-of-Speech Tagging
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Several features in our parsing model involve part-of-speech (POS) tags of the input sentences. The set of POS tags needs to be consistent
across languages and treebanks. For this reason we use the universal POS tag set of Petrov et al.
         [42]
         .
This set consists of the following 12 coarse-grained tags: NOUN (nouns), VERB (verbs), ADJ (adjectives), ADV (adverbs), PRON (pronouns),
DET (determiners), ADP (prepositions or postpositions), NUM (numerals), CONJ (conjunctions), PRT (particles), PUNC (punctuation marks) and
X (a catch-all for other categories such as abbreviations or foreign words).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         POS tags are not available for parallel data in the Europarl and Kaist corpus, so we need to provide the POS tags for these data.
In our experiments, we train a Stanford POS Tagger
         [50]
         for each language.
The labeled training data for each POS tagger are extracted from the training portion of each Treebanks.
The average tagging accuracy is around 95%.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         Undoubtedly, we are primarily interested in applying our approach to build statistical parsers for resource-poor target languages
without any knowledge. For the purpose of evaluation of our approach and comparison with previous work, we need to exploit the gold
POS tags to train the POS taggers. As part-of-speech tags are also a form of syntactic analysis, this assumption weakens the applicability
of our approach. Fortunately, some recently proposed POS taggers, such as the POS tagger of Das and
Petrov
         [13]
         , rely only on labeled training data for English and the same kind of parallel
text in our approach. In practice we can use this kind of POS taggers to predict POS tags, whose tagging accuracy is around 85%.
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
        In this section, we will describe the details of our experiments and compare our results with previous methods.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Data Sets
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         As presented in Section
         3.1
         , we evaluate our parsing approach on both version 1.0 and version 2.0 of Google Univereal
Treebanks for seven languages
         .
We use the standard splits of the treebank for each language as specified in the release of the
data
         .
Table
         1
         presents the statistics of the two versions of Google Universal Treebanks.
We strip all the dependency annotations off the training portion of each treebank, and use that as the unlabeled data for that target language.
We train our parsing model with different numbers of parallel sentences to analyze the influence of the amount of parallel data
on the parsing performance of our approach. The parallel data sets contain 500, 1000, 2000, 5000, 10000 and 20000 parallel sentences, respectively.
We randomly extract parallel sentences from each corpora, and smaller data sets are subsets of larger ones.
Table
         2
         shows the number of tokens in the parallel data used in the experiments.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        System performance and comparison
        on Google Universal Treebanks
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         For the comparison of parsing performance, we run experiments on the following systems:
        </p>
        <dl class="ltx_description" id="I2">
         <dt class="ltx_item" id="I2.ix1">
          <span class="ltx_tag ltx_tag_description">
           DTP:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix1.p1">
           <p class="ltx_p">
            The direct transfer parser (DTP) proposed by McDonald et al.
            [34]
            ,
who train a delexicalized parser on English labeled training data with no lexical features, then apply this parser to parse target
languages directly. It is based on the transition-based dependency parsing paradigm
            [40]
            .
We directly cite the results reported in McDonald et al.
            [31]
            . In addition to their original results,
we also report results by re-implementing the direct transfer parser based on the first-order projective dependency parsing
model
            [30]
            (DTP†).
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix2">
          <span class="ltx_tag ltx_tag_description">
           PTP
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix2.p1">
           <p class="ltx_p">
            The projected transfer parser (PTP) described in McDonald et al.
            [34]
            . The results of the
projected transfer parser re-implemented by us is marked as “PTP†”.
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix3">
          <span class="ltx_tag ltx_tag_description">
           -U:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix3.p1">
           <p class="ltx_p">
            Our approach training on only parallel data without unlabeled data for the target language. The parallel data set for each language contains 20,000 sentences.
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix4">
          <span class="ltx_tag ltx_tag_description">
           +U:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix4.p1">
           <p class="ltx_p">
            Our approach training on both parallel and unlabeled data. The parallel data sets are the ones contains 20,000 sentences.
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix5">
          <span class="ltx_tag ltx_tag_description">
           OR:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix5.p1">
           <p class="ltx_p">
            the supervised first-order projective dependency parsing model
            [30]
            , trained on
the original treebanks with maximum likelihood estimation (equation
            6
            ). One may regard this system as an oracle of transfer parsing.
           </p>
          </div>
         </dd>
        </dl>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Parsing accuracy is measured with unlabeled attachment score (UAS): the percentage of words with the correct head.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         Table
         3
         and Table
         4
         shows the parsing results of our approach, together with the results of the baseline
systems and the oracle, on version 1.0 and version 2.0 of Google Universal Treebanks, respectively.
Our approaches significantly outperform all the baseline systems across all the seven target languages. For the results on
Google Universal Treebanks version 1.0, the improvement on average over the projected transfer paper (PTP†) is 3.96% and up to
6.22% for Korean and 4.80% for German. For the other three languages, the improvements are remarkable,
too — 2.33% for French, 3.03% for Spanish and 3.40% for Swedish.
By adding entropy regularization from unlabeled data, our full model achieves average improvement of 0.29% over the
“-U” setting. Moreover, our approach considerably bridges the gap to fully supervised dependency parsers, whose average UAS is 84.67%.
For the results on treebanks version 2.0, we can get similar observation and draw the same conclusion.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Effect of the Amount of Parallel Text
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         Table
         5
         illustrates the UAS of our approach trained on different amounts of parallel data,
together with the results of the projected transfer parser re-implemented by us (PTP†).
We run two versions of our approach for each of the parallel data sets, one with unlabeled data (+U) and the other without them (-U).
From table
         5
         we can get three observations. First, even the parsers trained with only 500 parallel sentences achieve
considerably high parsing accuracies (average 70.10% for version 1.0 and 71.59% for version 2.0).
This demonstrates that our approach does not rely on a large amount of parallel data.
Second, when gradually increasing the amount of parallel data, the parsing performance continues improving.
Third, entropy regularization with unlabeled data makes modest improvement on parsing performance over the parsers without unlabeled data.
This proves the effectiveness of the entropy regularization from unlabeled data.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Experiments on CoNLL Treebanks
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         To make a thorough empirical comparison with previous studies, we also evaluate our system without unlabeled data (-U)
on treebanks from CoNLL shared task on dependency parsing
         [6, 38]
         .
To facilitate comparison, we use the same eight Indo-European languages as target
languages: Danish, Dutch, German, Greek, Italian, Portuguese, Spanish and Swedish,
and same experimental setup as McDonald et al.
         [34]
         .
We report both the results of the direct transfer and projected transfer parsers directly cited from McDonald
et al.
         [34]
         (DTP and PTP) and re-implemented by us (DTP†and PTP†).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p2">
        <p class="ltx_p">
         Table
         6
         gives the results comparing the model without unlabeled data (-U) presented in this work to those
five baseline systems and the oracle (OR).
The results of unsupervised DMV model
         [22]
         are from Table 1 of
McDonald et al.
         [34]
         .
Our approach outperforms all these baseline systems and achieves state-of-the-art performance on all the eight languages.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p3">
        <p class="ltx_p">
         In order to compare with more previous methods, we also report parsing performance on sentences of length 10 or less after punctuation
has been removed. Table
         7
         shows the results of our system and the results of baseline systems. “USR†” is the
weakly supervised system of Naseem et al.
         [35]
         . “PGI” is the phylogenetic grammar induction
model of Berg-Kirkpatrick and Klein
         [3]
         . Both the results of the two systems are cited from
Table 4 of McDonald et al.
         [34]
         . We also include the results of the
unsupervised dependency parsing model with non-parallel multilingual guidance (NMG) proposed by
Cohen et al.
         [11]
         , and “PR” which is the posterior regularization approach presented
in Gillenwater et al.
         [15]
         . All the results are shown in Table
         7
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p4">
        <p class="ltx_p">
         From Table
         7
         , we can see that among the eight target languages, our approach achieves best parsing
performance on six languages — Danish, German, Greek, Italian, Portuguese and Swedish. It should be noted that
the “NMG” system utilizes more than one helper languages. So it is not directly comparable to our work.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.5
        </span>
        Extensions
       </h3>
       <div class="ltx_para" id="S4.SS5.p1">
        <p class="ltx_p">
         In this section, we briefly outline a few extensions to our approach that we want to explore in future work.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S4.SS5.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.5.1
         </span>
         Non-Projective Parsing
        </h4>
        <div class="ltx_para" id="S4.SS5.SSS1.p1">
         <p class="ltx_p">
          As mentioned in section
          2.3
          , the runtime to compute
          KU
          and its gradient is
          O⁢(n4)
          . One reasonable speedup,
as presented in Smith and Eisner
          [44]
          , is to replace Shannon entropy with
Rényi entropy. The
          Rényi entropy
          is parameterized by
          α
          :
         </p>
         Rα⁢(p)=11-α⁢log⁡(∑yp⁢(y)α)

(16)
         <p class="ltx_p">
          With Rényi entropy, the computation of
          KU
          and its gradient is
          O⁢(n3)
          , even for non-projective case.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS5.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.5.2
         </span>
         Higher-Order Models for Projective Parsing
        </h4>
        <div class="ltx_para" id="S4.SS5.SSS2.p1">
         <p class="ltx_p">
          Our learning framework can be extended to higher-order dependency parsing models. For example, if we want to make our model capable of
utilizing more contextual information, we can extend our transferring weight to higher-order parts:
         </p>
         w~⁢(pt,𝒙it)={wE⁢(ps,𝒙is),if ⁢pt⟶a⁢l⁢i⁢g⁢npswE⁢(pd⁢e⁢l⁢e⁢xt,𝒙is),otherwise

(17)
         <p class="ltx_p">
          where
          p
          is a small
          part
          of tree
          𝒚
          that has limited interactions. For projective parsing,
several algorithms
          [33, 8, 24, 27]
          have been proposed to solve the model training problems (calculation of objective function and gradient) for different factorizations.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS5.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.5.3
         </span>
         IGT Data
        </h4>
        <div class="ltx_para" id="S4.SS5.SSS3.p1">
         <p class="ltx_p">
          One possible direction to improve our approach is to replace parallel text with Interlinear Glossed Text (IGT)
          [26]
          ,
which is a semi-structured data type encoding more syntactic information than parallel data. By using IGT Data, not only can we obtain
more accurate word alignments, but also extract useful cross-lingual information for the resource-poor language.
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
