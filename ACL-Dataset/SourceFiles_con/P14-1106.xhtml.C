<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   A Unified Model for Soft Linguistic Reordering Constraintsin Statistical Machine Translation.
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
       This paper explores a simple and effective unified framework for incorporating soft linguistic reordering constraints into a hierarchical phrase-based translation system: 1) a syntactic reordering model that explores reorderings for context free grammar rules; and 2) a semantic reordering model that focuses on the reordering of predicate-argument structures. We develop novel features based on both models and use them as soft constraints to guide the translation process. Experiments on Chinese-English translation show that the reordering approach can significantly improve a state-of-the-art hierarchical phrase-based translation system. However, the gain achieved by the semantic reordering model is limited in the presence of the syntactic reordering model, and we therefore provide a detailed analysis of the behavior differences between the two.
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
        Reordering models in statistical machine translation (SMT) model the word order difference when translating from one language to another. The popular distortion or lexicalized reordering models in phrase-based SMT make good local predictions by focusing on reordering on word level, while the synchronous context free grammars in hierarchical phrase-based (HPB) translation models are capable of handling non-local reordering on the translation phrase level. However, reordering, especially without any help of external knowledge, remains a great challenge because an accurate reordering is usually beyond these word level or translation phrase level reordering models’ ability. In addition, often these translation models fail to respect linguistically-motivated syntax and semantics. As a result, they tend to produce translations containing both syntactic and semantic reordering confusions. In this paper our goal is to take advantage of syntactic and semantic parsing to improve translation quality. Rather than introducing reordering models on either the word level or the translation phrase level, we propose a unified approach to modeling reordering on the linguistic unit level, e.g., syntactic constituents and semantic roles. The reordering unit falls into multiple granularities, from single words to more complex constituents and semantic roles, and often crosses translation phrases. To show the effectiveness of our reordering models, we integrate both syntactic constituent reordering models and semantic role reordering models into a state-of-the-art HPB system
        [4, 7]
        . We further contrast it with a stronger baseline, already including fine-grained soft syntactic constraint features
        [24, 3]
        . The general ideas, however, are applicable to other translation models, e.g., phrase-based model, as well.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Our syntactic constituent reordering model considers context free grammar (CFG) rules in the source language and predicts the reordering of their elements on the target side, using word alignment information. Due to the fact that a constituent, especially a long one, usually maps into multiple discontinuous blocks in the target language, there is more than one way to describe the monotonicity or swapping patterns; we therefore design two reordering models: one is based on the leftmost aligned target word and the other based on the rightmost target word.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        While recently there has also been some encouraging work on incorporating semantic structure (or, more specifically, predicate-argument structure: PAS) reordering in SMT, it is still an open question whether semantic structure reordering strongly overlaps with syntactic structure reordering, since the semantic structure is closely tied to syntax. To this end, we employ the same reordering framework as syntactic constituent reordering and focus on semantic roles in a PAS. We then analyze the differences between the syntactic and semantic features.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The contributions of this paper include the following:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           We introduce novel soft reordering constraints, using syntactic constituents or semantic roles, composed over word alignment information in translation rules used during decoding time;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           We introduce a unified framework to incorporate syntactic and semantic reordering constraints;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           We provide a detailed analysis providing insight into why the semantic reordering model is significantly less effective when syntactic reordering features are also present.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        The rest of the paper is organized as follows. Section
        2
        provides an overview of HPB translation model. Section
        3
        describes the details of our unified reordering models. Section
        4
        gives our experimental results and Section
        5
        discusses the behavior difference between syntactic constituent reordering and semantic role reordering. Section
        6
        reviews related work and, finally Section
        7
        concludes the paper.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       HPB Translation Model: an Overview
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        In HPB models
        [4]
        , synchronous rules take the form
        X→⟨γ,α,∼⟩
        , where
        X
        is the non-terminal symbol,
        γ
        and
        α
        are strings of lexical items and non-terminals in the source and target side, respectively, and
        ∼
        indicates the one-to-one correspondence between non-terminals in
        γ
        and
        α
        . Each such rule is associated with a set of translation model features
        {ϕi}
        , such as phrase translation probability
        p(α∣γ)
        and its inverse
        p(γ∣α)
        , the lexical translation probability
        pl⁢e⁢x(α∣γ)
        and its inverse
        pl⁢e⁢x(γ∣α)
        , and a rule penalty that affects preference for longer or shorter derivations. Two other widely used features are a target language model feature and a target word penalty.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Given a derivation
        d
        , its translation log-probability is estimated as:
       </p>
       <table class="ltx_equationgroup" id="S2.E1">
        <tr class="ltx_equation ltx_align_baseline" id="S2.E1X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          log⁡P⁢(d)∝∑iλi⁢ϕi⁢(d)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equationgroup">
           (1)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        λi
        is the corresponding weight of feature
        ϕi
        . See
        [4]
        for more details.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Unified Linguistic Reordering Models
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        As mentioned earlier, the linguistic reordering unit is the syntactic constituent for syntactic reordering, and the semantic role for semantic reordering. The syntactic reordering model takes a CFG rule (e.g.,
        VP→VP⁢PP⁢PP
        ) and models the reordering of the constituents on the left hand side by examining their translation or visit order according to the target language. For the semantic reordering model, it takes a PAS and models its reordering on the target side. Figure
        1
        shows an example of a PAS where the predicate (Pre) has two core arguments (A0 and A1) and one adjunct (TMP). Note that we refer all core arguments, adjuncts, and predicates as semantic roles; thus we say the PAS in Figure
        1
        has 4 roles. According to the annotation principles in (Chinese) PropBank
        [28, 42]
        , all the roles in a PAS map to a corresponding constituent in the parse tree, and these constituents (e.g., NPs and VBD in Figure
        1
        ) do not overlap with each other.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Next, we use a CFG rule to describe our syntactic reordering model. Treating the two forms of reorderings in a unified way, the semantic reordering model is obtainable by regarding a PAS as a CFG rule and considering a semantic role as a constituent.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Because the translation of a source constituent might result in multiple discontinuous blocks, there can be several ways to describe or group the reordering patterns. Therefore, we design two general constituent reordering sub-models. One is based on the leftmost aligned word (leftmost reordering model) and the other is based on the rightmost aligned word (rightmost reordering model), as follows. Figure
        2
        shows the modeling steps for the leftmost reordering model. Figure
        2
        (a) is an example of a CFG rule in the source parse tree and its word alignment links to the target language. Note that constituent
        𝑋𝑃4
        , which covers word
        f8
        , has no alignment. Then for each
        𝑋𝑃i
        , we find the leftmost target word which is aligned to a source word covered by
        𝑋𝑃i
        . Figure
        2
        (b) shows that the leftmost target words for
        𝑋𝑃1
        ,
        𝑋𝑃2
        , and
        𝑋𝑃3
        are
        e2
        ,
        e5
        , and
        e3
        , respectively, while
        𝑋𝑃4
        has no aligned target word. Then we get visit order
        V={vi}
        for
        {𝑋𝑃i}
        in the transformation from Figure
        2
        (b) to Figure
        2
        (c), with the following strategies for special cases:
       </p>
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           if the first constituent
           𝑋𝑃1
           is unaligned, we add a NULL word at the beginning of the target side and link
           𝑋𝑃1
           to the NULL word;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           if a constituent
           𝑋𝑃i
           (
           i&gt;1
           ) is unaligned, we add a link to the target word which is aligned to
           𝑋𝑃i-1
           , e.g.,
           𝑋𝑃4
           will be linked to
           e3
           ; and
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           if
           k
           constituents
           𝑋𝑃m1⁢…⁢𝑋𝑃mk
           (
           m1&lt;…&lt;mk
           ) are linked to the same target word, then
           vmi=vmi+1-1
           , e.g., since
           𝑋𝑃3
           and
           𝑋𝑃4
           are both linked to
           e3
           , then
           v3=v4-1
           .
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Finally Figure
        2
        (d) converts the visit order
        V={v1,…⁢vn}
        into a sequence of leftmost reordering types
        L⁢R⁢T={l⁢r⁢t1,…,l⁢r⁢tn-1}
        . For every two adjacent constituents
        𝑋𝑃i
        and
        𝑋𝑃i+1
        with corresponding visit order
        vi
        and
        vi+1
        , their reordering could be one of the following:
       </p>
       <ul class="ltx_itemize" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           Monotone (M)
           if
           vi+1=vi+1
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           Discontinuous Monotone (DM)
           if
           vi+1&gt;vi+1
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           Swap (S)
           if
           vi+1=vi-1
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i4.p1">
          <p class="ltx_p">
           Discontinuous Swap (DS)
           if
           vi+1&lt;vi-1
           .
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Up to this point, we have generated a sequence of leftmost reordering types
        𝐿𝑅𝑇={l⁢r⁢t1,…,l⁢r⁢tn-1}
        for a given CFG rule
        cfg
        :
        𝑋𝑃→𝑋𝑃1⁢…⁢𝑋𝑃n
        . The leftmost reordering model takes the following form:
       </p>
       <table class="ltx_equationgroup" id="S3.E2">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E2X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          scorel⁢r⁢t(𝑐𝑓𝑔)=Pl(lrt1,…,lrtn-1∣ψ(𝑐𝑓𝑔))
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equationgroup">
           (2)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        ψ⁢(𝑐𝑓𝑔)
        indicates the surrounding context of the CFG. By assuming that any two reordering types in
        𝐿𝑅𝑇={l⁢r⁢t1,…,l⁢r⁢tn-1}
        are independent of each other, we reformulate Eq.
        2
        into:
       </p>
       <table class="ltx_equationgroup" id="S3.E3">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E3X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          scorel⁢r⁢t(𝑐𝑓𝑔)=∏i=1n-1Pl(lrti∣ψ(𝑐𝑓𝑔))
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equationgroup">
           (3)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        Similarly, the sequence of rightmost reordering types
        RRT
        can be decided for a CFG rule
        𝑋𝑃→𝑋𝑃1⁢…⁢𝑋𝑃n
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        Accordingly, for a PAS
        pas
        :
        𝑃𝐴𝑆→𝑅1⁢…⁢𝑅n
        , we can obtain its sequences of leftmost and rightmost reordering types by using the same way described above.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Probability Estimation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In order to predict either the leftmost or rightmost reordering type for two adjacent constituents, we use a maximum entropy classifier to estimate the probability of the reordering type
         r⁢t∈{M,D⁢M,S,D⁢S}
         as follows:
        </p>
        <table class="ltx_equationgroup" id="S3.E4">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E4X">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           P(rt∣ψ(𝑐𝑓𝑔))=
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="2">
           <span class="ltx_tag ltx_tag_equationgroup">
            (4)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E4Xa">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           e⁢x⁢p⁢(∑kθk⁢fk⁢(r⁢t,ψ⁢(𝑐𝑓𝑔)))∑r⁢t′e⁢x⁢p⁢(∑kθk⁢fi⁢(r⁢t′,ψ⁢(𝑐𝑓𝑔)))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         fk
         are binary features,
         θk
         are the weights of these features. Most of our features
         fk
         are syntax-based. For
         𝑋𝑃i
         and
         𝑋𝑃i+1
         in
         cfg
         , the features are aimed to examine which of them should be translated first. Therefore, most features share two common components: the syntactic categories of
         𝑋𝑃i
         and
         𝑋𝑃i+1
         . Table
         1
         shows the features used in syntactic leftmost and rightmost reordering models. Note that we use the same features for both.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Although the semantic reordering model is structured in precisely the same way, we use different feature sets to predict the reordering between two semantic roles. Given the two adjacent roles
         𝑅i
         and
         𝑅i+1
         in a PAS
         pas
         , Table
         2
         shows the features that are used in the semantic leftmost and rightmost reordering models.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Integrating into the HPB Model
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         For models with syntactic reordering, we add two new features (i.e., one for the leftmost reordering model and the other for the rightmost reordering model) into the log-linear translation model in Eq.
         1
         . Unlike the conventional phrase and lexical translation features, whose values are phrase pair-determined and thus can be calculated offline, the value of the reordering features can only be obtained during decoding time, and requires word alignment information as well. Before we present the algorithm integrating the reordering models, we define the following functions by assuming
         XPi
         and
         XPi+1
         are the constituent pair of interest in CFG rule
         cfg
         ,
         H
         is the translation hypothesis and
         a
         is its word alignment:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <ul class="ltx_itemize" id="I4">
         <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i1.p1">
           <p class="ltx_p">
            ℱ1⁢(w1, w2, 𝑋𝑃)
            : returns
            true
            if constituent
            XP
            is within the span from word
            w1
            to
            w2
            ; otherwise returns
            false
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i2.p1">
           <p class="ltx_p">
            ℱ2⁢(H, 𝑐𝑓𝑔, 𝑋𝑃i, 𝑋𝑃i+1)
            returns
            true
            if the reordering of the pair
            ⟨
            XPi
            ,
            XPi+1⟩
            in rule
            cfg
            has not been calculated yet; otherwise returns
            false
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i3.p1">
           <p class="ltx_p">
            ℱ3⁢(H, a, 𝑋𝑃i, 𝑋𝑃i+1)
            returns the leftmost and rightmost reordering types for the constituent pair
            ⟨
            XPi
            ,
            XPi+1⟩
            , given alignment
            a
            , according to Section
            3
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i4.p1">
           <p class="ltx_p">
            ℱ4⁢(r⁢t, 𝑐𝑓𝑔, 𝑋𝑃i, 𝑋𝑃i+1)
            returns the probability of leftmost reordering type
            r⁢t
            for the constituent pair
            ⟨
            XPi
            ,
            XPi+1⟩
            in rule
            cfg
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i5.p1">
           <p class="ltx_p">
            ℱ5⁢(r⁢t, 𝑐𝑓𝑔, 𝑋𝑃i, 𝑋𝑃i+1)
            returns the probability of rightmost reordering type
            r⁢t
            for the constituent pair
            ⟨
            XPi
            ,
            XPi+1⟩
            in rule
            cfg
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Algorithm 1 integrates the syntactic leftmost and rightmost reordering models into a CKY-style decoder whenever a new hypothesis is generated. Given a hypothesis
         H
         with its alignment
         a
         , it traverses all CFG rules in the parse tree and sees if two adjacent constituents are conditioned to trigger the reordering models (lines 2-4). For each pair of constituents, it first extracts its leftmost and rightmost reordering types (line 6) and then gets their respective probabilities returned by the maximum entropy classifiers defined in Section
         3.1
         (lines 7-8). Then the algorithm returns two log-probabilities of the syntactic reordering models.
Note that Function
         ℱ1
         returns true if hypothesis
         H
         fully covers, or fully contains, constituent
         X⁢Pi
         , regardless of the reordering type of
         X⁢Pi
         . Do not confuse any parsing tag
         X⁢Pi
         with the nameless variables
         Xi
         in Hiero or cdec rules.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         For the semantic reordering models, we also add two new features into the log-linear translation model. To get the two semantic reordering model feature values, we simply use Algorithm 1 and its associated functions from
         ℱ1
         to
         ℱ5
         replacing a CFG rule
         cfg
         with a PAS
         pas
         , and a constituent
         𝑋𝑃i
         with a semantic role
         𝑅i
         . Algorithm 1 therefore permits a unified treatment of syntactic and PAS-based reordering, even though it is expressed in terms of syntactic reordering here for ease of presentation.
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
        We have presented our unified approach to incorporating syntactic and semantic soft reordering constraints in an HPB system. In this section, we test its effectiveness in Chinese-English translation.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Experimental Settings
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         For training we use 1.6M sentence pairs of the non-UN and non-HK Hansards portions of NIST MT training corpora, segmented with the Stanford segmenter
         [33]
         . The English data is lowercased, tokenized and aligned with GIZA++
         [27]
         to obtain bidirectional alignments, which are symmetrized using the
         grow-diag-final-and
         method
         [16]
         . We train a 4-gram LM on the English side of the corpus with 600M additional words from non-NYT and non-LAT, randomly selected portions of the Gigaword v4 corpus, using modified Kneser-Ney smoothing
         [1]
         . We use the HPB decoder cdec
         [7]
         , with Mr. Mira
         [8]
         , which is a
         k
         -best variant of MIRA
         [3]
         , to tune the parameters of the system.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         We use NIST MT 06 dataset (1664 sentence pairs) for tuning, and NIST MT 03, 05, and 08 datasets (919, 1082, and 1357 sentence pairs, respectively) for evaluation.
         We use BLEU
         [29]
         for both tuning and evaluation.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         To obtain syntactic parse trees and semantic roles on the tuning and test datasets, we first parse the source sentences with the Berkeley Parser
         [30]
         , trained on the Chinese Treebank 7.0
         [43]
         . We then pass the parses to a Chinese semantic role labeler
         [22]
         , trained on the Chinese PropBank 3.0
         [42]
         , to annotate semantic roles for all verbal predicates (part-of-speech tag
         VV
         ,
         VE
         , or
         VC
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         Our basic baseline system employs 19 basic features: a language model feature, 7 translation model features, word penalty, unknown word penalty, the glue rule, date, number and 6 pass-through features.
Our stronger baseline employs, in addition, the fine-grained syntactic soft constraint features of Marton and Resnik
         [24]
         , hereafter MR08. The syntactic soft constraint features include both MR08 exact-matching and cross-boundary constraints (denoted
         XP
         = and
         XP
         +). Since the syntactic parses of the tuning and test data contain 29 types of constituent labels and 35 types of POS tags, we have 29 types of
         XP
         + features and 64 types of
         XP
         = features.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Model Training
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         To train the syntactic and semantic reordering models, we use a gold alignment dataset.
         It contains 7,870 sentences with 191,364 Chinese words and 261,399 English words. We first run syntactic parsing and semantic role labeling on the Chinese sentences, then train the models by using MaxEnt toolkit with L1 regularizer
         [34]
         .
         Table
         3
         shows the reordering type distribution over the training data. Interestingly, about 17% of the syntactic instances and 16% of the semantic instances differ in their leftmost and rightmost reordering types, indicating that the leftmost/rightmost distinction is informative. We also see that the number of semantic instances is about 1/3 of that of syntactic instances, but the entropy of the semantic reordering classes is higher, indicating the reordering of semantic roles is harder than that of syntactic constituents.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         A deeper examination of the reordering model’s training data reveals that some constituent pairs and semantic role pairs have a preference for a specific reordering type (monotone or swap). In order to understand how well the MR08 system respects their reordering preference, we use the gold alignment dataset LDC2006E86, in which the source sentences are from the Chinese Treebank, and thus both the gold parse trees and gold predicate-argument structures are available. Table
         4
         presents examples comparing the reordering distribution between gold alignment and the output of the MR08 system. For example, the first row shows that based on the gold alignment, for
         ⟨PP,VP⟩
         , 16% are in monotone and 76% are in swap reordering. However, our MR08 system outputs 46% of them in monotone and and 50% in swap reordering. Hence, the reordering accuracy for
         ⟨PP,VP⟩
         is 54%. Table
         4
         also shows that the semantic reordering between core arguments and predicates (e.g.,
         ⟨𝑃𝑟𝑒𝑑,A1⟩
         ,
         ⟨A0,𝑃𝑟𝑒𝑑⟩
         ) has a less ambiguous pattern than that between adjuncts and other roles (e.g.,
         ⟨LOC,Pred⟩
         ,
         ⟨A0,TMP⟩
         ), indicating the higher reordering flexibility of adjuncts.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Translation Experiment Results
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         Our first group of experiments investigates whether the syntactic reordering models are able to improve translation quality in terms of BLEU. To this end, we respectively add our syntactic reordering models into both the baseline and MR08 systems. The effect is shown in the rows of “+ syn-reorder” in Table
         5
         . From the table, we have the following two observations.
        </p>
        <ul class="ltx_itemize" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            Although the HPB model is capable of handling non-local phrase reordering using synchronous context free grammars, both our syntactic leftmost reordering model and rightmost model are still able to achieve improvement over both the baseline and MR08. This suggests that our syntactic reordering features interact well with the MR08 syntactic soft constraints: the XP+ and XP= features focus on a single constituent each, while our reordering features focus on a pair of constituents each.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            There is no clear indication of whether the leftmost reordering model works better than the other. In addition, integrating both the leftmost and rightmost reordering models has limited improvement over a single reordering model.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         Our second group of experiments is to validate the semantic reordering models. Results are shown in the rows of “+ sem-reorder” in Table
         5
         . Here we observe:
        </p>
        <ul class="ltx_itemize" id="I6">
         <li class="ltx_item" id="I6.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i1.p1">
           <p class="ltx_p">
            The semantic reordering models also achieve significant gain of 0.8 BLEU on average over the baseline system, demonstrating the effectiveness of PAS-based reordering. However, the gain diminishes to 0.3 BLEU on the MR08 system.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I6.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i2.p1">
           <p class="ltx_p">
            The syntactic reordering models outperform the semantic reordering models on both the baseline and MR08 systems.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         Finally, we integrate both the syntactic and semantic reordering models into the final system. The two models collectively achieve a gain of up to 1.4 BLEU over the baseline and 1.0 BLEU over MR08 on average, which is shown in the rows of “+syn+sem” in Table
         5
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Discussion
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        The trend of the results, summarized as performance gain over the baseline and MR08 systems averaged over all test sets, is presented in Table
        6
        . The syntactic reordering models outperform the semantic reordering models, and the gain achieved by the semantic reordering models is limited in the presence of the MR08 syntactic features.
In this section, we look at MR08 system and the systems improving it to explore the behavior differences between the two reordering models.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Coverage analysis
        : Our statistics show that syntactic reordering features (either leftmost or rightmost) are called 24 times per sentence on average. This is compared to only 9 times per sentence for semantic reordering features. This is not surprising since the semantic reordering features are exclusively attached to predicates, and the span set of the semantic roles is a strict subset of the span set of the syntactic constituents; only 22% of syntactic constituents are semantic roles. On average, a sentences has 4 PASs and each PAS contains 3 semantic roles. Of all the semantic role pairs, 44% are in the same CFG rules, indicating that this part of semantic reordering has overlap with syntactic reordering. Therefore, the PAS model has fewer opportunities to influence reordering.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Reordering accuracy analysis
        : The reordering type distribution on the reordering model training data in Table
        3
        suggests that semantic reordering is more difficult than syntactic reordering. To validate this conjecture on our translation test data, we compare the reordering performance among the MR08 system, the improved systems and the maximum entropy classifiers. For the test set, we have four reference translations. We run GIZA++ on the data combination of our translation training data and test data to get the alignment for the test data and each reference translation. Once we have the (semi-)gold alignment, we compute the gold reordering types between two adjacent syntactic constituents or semantic roles. Then we evaluate the automatic reordering outputs generated from both our translation systems and maximum entropy classifiers. Table
        7
        shows the accuracy averaged over the four gold reordering sets (the four reference translations). It shows that 1) as expected, our classifiers do worse on the harder semantic reordering prediction than syntactic reordering prediction; 2) thanks to the high accuracy obtained by the maxent classifiers, integrating either the syntactic or the semantic reordering constraints results in better reordering performance from both syntactic and semantic perspectives; 3) in terms of the mutual impact, the syntactic reordering models help improving semantic reordering more than the semantic reordering models help improving syntactic reordering; and 4) the rightmost models have a learnability advantage over the leftmost models, achieving higher accuracy across the board.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        Feature weight analysis
        : Table
        8
        shows the syntactic and semantic reordering feature weights. It shows that the semantic feature weights decrease in the presence of the syntactic features, indicating that the decoder learns to trust semantic features less in the presence of the more accurate syntactic features. This is consistent with our observation that semantic reordering is harder than syntactic reordering, as seen in Tables
        3
        and
        7
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p5">
       <p class="ltx_p">
        Potential improvement analysis:
        Table
        7
        also shows that our current maximum entropy classifiers have room for improvement, especially for semantic reordering. In order to explore the error propagation from the classifiers themselves and explore the upper bound for improvement from the reordering models, we perform an “oracle” study, letting the classifiers be aware of the “gold” reordering type between two syntactic constituents or two semantic roles, and returning a higher probability for the gold reordering type and a smaller one for the others (i.e., we set 0.9 for the gold reordering type, and let the other non-gold three types share 0.1). Again, to get the gold reordering type, we run GIZA++ to get the alignment for tuning/test source sentences and each of four reference translations. We report the averaged performance by using the gold reordering type extracted from the four reference translations. Table
        9
        compares the performance between the non-oracle and oracle settings. We clearly see that using gold syntactic reordering types significantly improves the performance (e.g., 34.9 vs. 33.4 on average) and there is still some room for improvement by building a better maximum entropy classifiers (e.g., 34.9 vs. 34.3). To our surprise, however, the improvement achieved by gold semantic reordering types is still small (e.g., 33.9 vs. 33.4), suggesting that the potential improvement of semantic reordering models is much more limited. And we again see that the improvement achieved by semantic reordering models is limited in the presence of the syntactic reordering models.
       </p>
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
        Syntax-based reordering:
        Some previous work pre-ordered words in the source sentences, so that the word order of source and target sentences is similar. The reordering rules were either manually designed
        [6, 36, 41, 18]
        or automatically learned
        [39, 12, 35, 15, 19]
        , using syntactic parses.
Li et al.
        [20]
        focused on finding the
        n
        -best pre-ordered source sentences by predicting the reordering of sibling constituents, while Yang et al.
        [44]
        obtained word order by using a reranking approach to reposition nodes in syntactic parse trees. Both are close to our work; however, our model generates reordering features that are integrated into the log-linear translation model during decoding.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Another approach in previous work added soft constraints as weighted features in the SMT decoder to reward good reorderings and penalize bad ones. Marton and Resnik
        [24]
        employed soft syntactic constraints with weighted binary features and no MaxEnt model. They did not explicitly target reordering (beyond applying constraints on HPB rules). Although employing linguistically motivated labels in SCFG is capable of capturing constituent reorderings
        [5, 25]
        , the rules are sparser than SCFG with nameless non-terminals (i.e.,
        X
        s) and soft constraints.
Ge
        [11]
        presented a syntax-driven maximum entropy reordering model that predicted the source word translation order.
Gao et al.
        [10]
        employed dependency trees to predict the translation order of a word and its head word.
Huang et al.
        [13]
        predicted the translation order of two source words.
        Our work, which shares this approach, differs from their work primarily in that our syntactic reordering models are based on the constituent level, rather than the word level.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Semantics-based reordering:
        Semantics-based reordering has also seen an increase in activity recently. In the pre-ordering approach, Wu et al.
        [38]
        automatically learned pre-ordering rules from PAS. In the soft constraint or reordering model approach, Liu and Gildea
        [23]
        modeled the reordering/deletion of source-side semantic roles in a tree-to-string translation model.
Xiong et al.
        [40]
        and Li et al.
        [21]
        predicted the translation order between either two arguments or an argument and its predicate. Instead of decomposing a PAS into individual units, Zhai et al.
        [45]
        constructed a classifier for each source side PAS. Finally in the post-processing approach category, Wu and Fung
        [37]
        performed semantic role labeling on translation output and reordered arguments to maximize the cross-lingual match of the semantic frames between the source sentence and the target translation. To our knowledge, their semantic reordering models were PAS-specific. In contrast, our model is universal and can be easily adopted to model the reordering of other linguistic units (e.g., syntactic constituents). Moreover, we have studied the effectiveness of the semantic reordering model in different scenarios.
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Non-syntax-based reorderings in HPB:
        Recently we have also seen work on lexicalized reordering models without syntactic information in HPB
        [31, 14, 26]
        . The non-syntax-based reordering approach models the reordering of translation words/phrases while the syntax-based approach models the reordering of syntactic constituents. Although there are overlaps between translation phrases and syntactic constituents, it is reasonable to think that the two reordering approaches can work together well and even complement each other, as the linguistic patterns they capture differ substantially.
Setiawan et al.
        [32]
        modeled the orientation decisions between anchors and two neighboring multi-unit chunks which might cross phrase or rule boundaries. Last, we also note that recent work on non-syntax-based reorderings in (flat) phrase-based models
        [2, 9]
        can also be potentially adopted to hpb models.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
