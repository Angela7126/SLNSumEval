<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Empirical Study of Unsupervised Chinese Word Segmentation Methods for SMT on Large-scale Corpora.
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
       Unsupervised word segmentation (UWS) can provide domain-adaptive segmentation for statistical machine translation (SMT) without annotated data, and bilingual UWS can even optimize segmentation for alignment. Monolingual UWS approaches of explicitly modeling the probabilities of words through Dirichlet process (DP) models or Pitman-Yor process (PYP) models have achieved high accuracy, but their bilingual counterparts have only been carried out on small corpora such as basic travel expression corpus (BTEC) due to the computational complexity. This paper proposes an efficient unified PYP-based monolingual and bilingual UWS method. Experimental results show that the proposed method is comparable to supervised segmenters on the in-domain NIST OpenMT corpus, and yields a 0.96 BLEU relative increase on NTCIR PatentMT corpus which is out-of-domain.
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
        Many languages, especially Asian languages such as Chinese, Japanese and
Myanmar, have no explicit word boundaries, thus word segmentation (WS),
that is, segmenting the continuous texts of these languages into
isolated words, is a prerequisite for many natural language processing
applications including SMT.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Though supervised-learning approaches which involve training segmenters on manually segmented corpora are widely used
        []
        , yet the criteria for manually annotating words are arbitrary, and the available annotated corpora are limited in both quantity and genre variety. For example, in machine translation, there
are various parallel corpora such as BTEC for tourism-related
dialogues
        []
        and PatentMT in the patent
domain
        []
        ,
but researchers working on Chinese-related tasks often use the Stanford Chinese
segmenter
        []
        which is
trained on a small amount of annotated news text.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In contrast, UWS, spurred by the findings that infants are able to use
statistical cues to determine word
boundaries
        []
        , relies on statistical criteria
instead of manually crafted standards. UWS learns from unsegmented raw
text, which are available in large quantities, and thus it has the potential
to provide more accurate and adaptive segmentation than supervised
approaches with less development effort being required.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The approaches of explicitly modeling the probability of
words
        []
        significantly outperformed a heuristic approach
        []
        on the monolingual Chinese SIGHAN-MSR corpus
        []
        ,
which inspired the work of this paper.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        However, bilingual approaches that model word probabilities suffer from
computational complexity. Xu et al.
        []
        proposed
a bilingual method by adding alignment into the generative model, but
was only able to test it on small-scale BTEC data. Nguyen et al.
        []
        used the local best alignment to increase the speed of the Gibbs sampling in training but the impact
on accuracy was not explored.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        This paper is dedicated to bilingual UWS on large-scale corpora to
support SMT. To this end, we model bilingual UWS under a similar framework
with monolingual UWS in order to improve efficiency,
and replace Gibbs sampling with expectation maximization (EM) in training.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        We aware that variational bayes (VB) may be used for speeding up the
training of DP-based or PYP-based bilingual UWS. However, VB requires
formulating the
        m
        expectations of
        (m-1)
        -dimensional marginal
distributions, where
        m
        is the number of hidden variables. For UWS, the
hidden variables are indicators that identify substrings of sentences in
the corpus as words. These variables are large in number and it is not
clear how to apply VB to UWS, and as far the authors aware there is
no previous work related to the application of VB to monolingual UWS.
Therefore, we have not explored VB methods in this paper, but we do show
that our method is superior to the existing methods.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        The contributions of this paper include,
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           state-of-the-art accuracy in monolingual UWS;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           the first bilingual UWS method practical for large corpora;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           improvement of BLEU scores compared to supervised Stanford Chinese word segmenter.
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Methods
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        This section describes our unified monolingual and bilingual UWS scheme.
Table
        1
        lists the main notation. The set
        ℱ
        is
chosen to represent an unsegmented foreign language sentence (a
sequence of characters), because an unsegmented sentence can be seen as the
set of all possible segmentations of the sentence denoted
        F
        , i.e.
        F∈ℱ
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Monolingual and bilingual WS can be formulated as follows, respectively,
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S2.E1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          F^(ℱ)=a⁢r⁢g⁢m⁢a⁢xF∈ℱP(F|ℱ,ℳ),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (1)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S2.E2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          F^(ℱ,E)=a⁢r⁢g⁢m⁢a⁢xF∈ℱ∑aP(F,a|ℱ,E,ℬ),
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
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        where
        a
        is an alignment between
        F
        and
        E
        . The English sentence
        E
        is used in the generation of a segmented sentence
        F
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        UWS learns models by maximizing the likelihood of the unsegmented corpus, formulated as,
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S2.E3">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          ℳ^=argmaxℳ∏ℱ∈𝔽(∑F∈ℱP(F|ℳ)),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (3)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S2.E4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          ℬ^=argmaxℬ∏(ℱ,E)∈𝔹(∑F∈ℱ∑aP(F,a|ℱ,E,ℬ)).
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
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Our method of learning
        ℳ
        and
        ℬ
        proceeds in a similar manner to the
EM algorithm. The following two operations are performed iteratively for
each sentence (pair).
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           Exclude the previous expected counts of the current sentence (pair) from the model, and then derive the current sentence in all possible ways, calculating the new expected counts for the words (see Section
           2.1
           ), that is, we calculate the expected probabilities of the
           ℱkk′
           being words given the data excluding
           ℱ
           , i.e.
           𝐄𝔽/{ℱ}(P(ℱkk′|ℱ))=P(ℱkk′|ℱ,ℳ)
           in a similar manner
to the marginalization in the Gibbs sampling process which we are replacing;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           Update the respective model
           ℳ
           or
           ℬ
           according to these expectations (see Section
           2.2
           ).
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Expectation
       </h3>
       <div class="ltx_subsubsection" id="S2.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.1
         </span>
         Monolingual Expectation
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS1.p1">
         <p class="ltx_p">
          P(ℱkk′|ℱ,ℳ)
          is the marginal probability of all the possible
          F∈ℱ
          that contain
          ℱkk′
          as a word,
which can be calculated efficiently through dynamic programming (the process is similar to the foreward-backward algorithm in training a hidden Markov model (HMM)
          []
          ):
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx3">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            ⁢Pa⁢(k)=∑u=1UPa⁢(k-u)⁢Pℳ⁢(ℱk-uk)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex2">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            ⁢Pb⁢(k′)=∑u=1UPb⁢(k′+u)⁢Pℳ⁢(ℱk′k′+u)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.E5">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            P(ℱkk′|ℱ,ℳ)=Pa(k)Pℳ(ℱkk′)Pb(k′),
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
          U
          is the predefined maximum length of foreign language words,
          Pa⁢(k)
          and
          Pb⁢(k′)
          are the forward and backward probabilities, respectively.
This section uses a unigram model for description convenience, but the method can be extended to
          n
          -gram models.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.2
         </span>
         Bilingual Expectation
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS2.p1">
         <p class="ltx_p">
          P(ℱkk′|ℱ,E,ℬ)
          is the marginal probability of all the possible
          F∈ℱ
          that contain
          ℱkk′
          as a word and are aligned with
          E
          , formulated as:
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx4">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex3">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            P(ℱkk′|ℱ,E,ℬ)=∑F∈ℱℱkk′∈F∑aP(F,a|E,ℬ)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex4">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            ≈∑F∈ℱFjk=ℱkk′∑a∏j=1JP(aj|j,I,J)Pℬ(fj|eaj)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.E6">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            =∑F∈ℱfjk=ℱkk′∏j=1J∑aP(aj|j,I,J)Pℬ(fj|eaj),
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (6)
            </span>
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
          J
          and
          I
          are the number of foreign and English words, respectively, and
          aj
          is the position of the English word that is aligned to
          fj
          in the alignment
          a
          . For the alignment we employ an approximation to IBM model 2
          []
          described below.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS2.p2">
         <p class="ltx_p">
          We define the conditional probability of
          fj
          given the corresponding English sentence
          E
          and the model
          ℬ
          as:
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx5">
          <tr class="ltx_equation ltx_align_baseline" id="S2.E7">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            Pℬ(fj|E)
           </td>
           <td class="ltx_td ltx_align_left">
            =∑aP(aj|j,I,J)Pℬ(fj|eaj)
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
        </div>
        <div class="ltx_para" id="S2.SS1.SSS2.p3">
         <p class="ltx_p">
          Then, the previous dynamic programming method can be extended to the bilingual expectation
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx6">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex5">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            Pa(k|E)=∑u=1UPa(k-u|E)Pℬ(ℱk-uk|E)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex6">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            Pb(k′|E)=∑u=1UPb(k′+u|E)Pℬ(ℱk′k′+u|E)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.E8">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            P(Fkk′|ℱ,E,ℬ)=Pa(k|E)Pℬ(ℱkk′|E)Pb(k′|E).
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (8)
            </span>
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS2.p4">
         <p class="ltx_p">
          Eq.
          7
          can be rewritten (as in IBM model 2):
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx7">
          <tr class="ltx_equation ltx_align_baseline" id="S2.E9">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            Pℬ(fj|E)
           </td>
           <td class="ltx_td ltx_align_left">
            =∑i=1IP*(i|j,I,J)Pℬ(fj|ei)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (9)
            </span>
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex7">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            P*(i|j,I,J)
           </td>
           <td class="ltx_td ltx_align_left">
            =∑a:aj=iP(aj|,j,I,J)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          In order to maintain both speed and accuracy, the following window function is adopted
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx8">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex8">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            P*(i|j,I,J)≈P*(i|k,I,K)=
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S2.E10">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            ⁢{e-|i-k⁢I/K|/σ|i-k⁢I/K|⩽δb/2λϕei⁢ is empty word0otherwise
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (10)
            </span>
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
          K
          is the number of characters in
          ℱ
          , and the
          k
          -th character
is the start of the word
          fj
          , since
          j
          and
          J
          are unknown during
the computation of dynamic programming.
          δb
          is the window size,
          λϕ
          is the prior probability of an empty English word, and
          σ
          ensures all the items sum to 1.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Maximization
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Inspired by
         []
         , we employ a Pitman-Yor process model to build
the segmentation model
         ℳ
         or
         ℬ
         . The monolingual
model
         ℳ
         is
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx9">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           Pℳ⁢(fj)=
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           max⁢(n⁢(fj)-d,0)+(θ+d⋅nℳ)⁢G0⁢(fj)∑fj′n⁢(fj′)+θ
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           ⁢nℳ=|{fj| n⁢(fj)⩾d}|,
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (11)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         fj
         is a foreign language word, and
         n⁢(fj)
         is the observed counts of
         fj
         ,
         θ
         is named the strength parameter,
         G0⁢(fj)
         is named the base distribution of
         fj
         , and
         d
         is the discount.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         The bilingual model is
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx10">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           Pℬ(fj|ei)=
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           ⁢max(n(fj,ei)-d,0)+(θ+d⋅nei)G0(fj|ei)∑fj′n⁢(fj′,ei)+θ
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           nei=|{x| n⁢(x,ei)⩾d}|.
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (12)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         In Eqs.
         11
         and
         12
         ,
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx11">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           n(fj)=∑ℱ∈𝔽P(fj|ℱ,ℳ)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (13)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           n⁢(fj,ei)=
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E14">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           ∑(ℱ,E)∈𝔹P(fj|ℱ,E,ℬ)P*(i|j,I,J)Pℬ(fj|ei)∑i′=1IP*(i′|j,I,J)Pℬ(fj|ei′).
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (14)
           </span>
          </td>
         </tr>
        </table>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Complexity Analysis
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The computational complexity of our method is linear in the number of
iterations, the size of the corpus, and the complexity of calculating
the expectations on each sentence or sentence pair. In practical
applications, the size of the corpus is fixed, and we found empirically that the number of
iterations required by the proposed method for convergence is usually small (less than five
iterations). We now look in more detail at the complexity of the expectation calculation in
monolingual and bilingual models.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The monolingual expectation is calculated according to Eq.
        5
        ; the
complexity is linear in the length of sentences and the square of the
predefined maximum length of words. Thus its overall complexity is
       </p>
       Omonolingunigram=O⁢(Ni⁢|𝔽|⁢K⁢U2),

(15)
       <p class="ltx_p">
        where
        Ni
        is the number of iterations,
        K
        is the average number of characters per sentence, and
        U
        is the predefined maximum length of words.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        For the monolingual bigram model, the number of states in the HMM is
        U
        times more than that of the monolingual unigram model, as the
states at specific position of
        F
        are not only related to the length of
the current word, but also related to the length of the word before it.
Thus its complexity is
        U2
        times the unigram model’s complexity:
       </p>
       Omonolingbigram=O⁢(Ni⁢|𝔽|⁢K⁢U4).

(16)
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The bilingual expectation is given by Eq.
        8
        , whose
complexity is the same as the monolingual case. However, the
complexity of calculating the transition probability, in
Eqs.
        9
        and
        10
        , is
        O⁢(δb)
        .
Thus its overall complexity is:
       </p>
       Obilingunigram=O⁢(Ni⁢|𝔽|⁢K⁢U2⁢δb).

(17)
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
        In this section, the proposed method is first validated on
monolingual segmentation tasks, and then evaluated in the context of SMT to study whether
the translation quality, measured by BLEU, can be improved.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Experimental Settings
       </h3>
       <div class="ltx_subsubsection" id="S4.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.1.1
         </span>
         Experimental Corpora
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS1.p1">
         <p class="ltx_p">
          Two monolingual corpora and two bilingual corpora are
used (Table
          2
          ). CHILDES
          []
          is the most common test corpus for UWS methods.
The SIGHAN-MSR corpus
          []
          consists of manually segmented simplified Chinese news text, released in the SIGHAN bakeoff
2005 shared tasks.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS1.p2">
         <p class="ltx_p">
          The first bilingual corpus: OpenMT06 was used in the NIST open machine translation 2006
Evaluation
          .
We removed the United Nations corpus and the traditional Chinese
data sets from the constraint training resources. The data sets of NIST
Eval 2002 to 2005 were used as the development for MERT
tuning
          []
          . This data set mainly consists of news
text
          . PatentMT9
is from the shared task of NTCIR-9 patent machine translation
. The training set consists of 1 million parallel sentences extracted from
patent documents, and the development set and test set both consist of
2000 sentences.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.1.2
         </span>
         Performance Measurement and Baseline Methods
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS2.p1">
         <p class="ltx_p">
          For the monolingual tasks, the F
          1
          score against the gold annotation
is adopted to measure the accuracy. The results reported in related
papers are listed for comparison.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS2.p2">
         <p class="ltx_p">
          For the bilingual tasks, the publicly available system of
Moses
          []
          with default settings is employed to perform
machine translation, and BLEU
          []
          was used to
evaluate the quality. Character-based segmentation, LDC segmenter and
Stanford Chinese segmenters were used as the baseline methods.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS1.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.1.3
         </span>
         Parameter settings
        </h4>
        <div class="ltx_para" id="S4.SS1.SSS3.p1">
         <p class="ltx_p">
          The parameters are tuned on held-out data sets. The maximum length of foreign language words is set to 4. For the PYP model, the base distribution adopts the formula in
          []
          , and the strength parameter is set to
          1.0
          , and the discount is set to
          1.0×10-6
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS3.p2">
         <p class="ltx_p">
          For bilingual segmentation,the
size of the alignment window is set to
          6
          ; the
probability
          λϕ
          of foreign language words being generated by an empty
English word, was set to
          0.3
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS1.SSS3.p3">
         <p class="ltx_p">
          The training was started from assuming that there was no previous segmentations on each sentence (pair), and the number of iterations was fixed. It was set to 3 for the monolingual unigram model, and 2 for the bilingual unigram model, which provided slightly higher BLEU scores on the development set than the other settings. The monolingual bigram model, however, was slower to converge, so we started it from the segmentations of the unigram model, and using 10 iterations.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Monolingual Segmentation Results
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         In monolingual segmentation, the proposed methods with both unigram and
bigram models were tested. Experimental results show that they are
competitive to state-of-the-art baselines in both accuracy and speed
(Table
         <span class="ltx_ref ltx_ref_self">
          LABEL:tab:mono:acc
         </span>
         ). Note that the comparison of speed is only
for reference because the times are obtained
from their respective papers.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Bilingual Segmentation Results
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         Table
         4
         presents the BLEU scores for Moses using
different segmentation methods. Each experiment was performed three
times. The proposed method with monolingual bigram model performed poorly on the
Chinese monolingual segmentation task; thus, it was not tested. We intended to test
         []
         , but found it impracticable on large-scale corpora.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         The experimental results show that the proposed UWS methods are comparable to the Stanford segmenters on the OpenMT06 corpus, while achieves a 0.96 BLEU increase on the PatentMT9 corpus. This is because this corpus is out-of-domain for the supervised segmenters. The CTB and PKU Stanford segmenter were both trained on annotated news text, which was the major domain of OpenMT06.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         Table
         5
         presents the run times of the proposed methods on
the bilingual corpora. The program is single threaded and implemented in C++. The time cost of the bilingual models is about
5 times that of the monolingual model, which is consistent with
the complexity analysis in Section
         3
         .
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
