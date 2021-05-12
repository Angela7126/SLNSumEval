<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Understanding Relation Temporality of Entities.
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
       This paper demonstrates the importance of relation equivalence for entity translation pair discovery.
Existing approach of understanding relation equivalence has focused on using
explicit features of co-occurring entities.
In this paper, we explore latent features of temporality
for understanding relation equivalence,
and empirically show that the explicit and latent features complement each other.
Our proposed hybrid approach of using both explicit and latent features
improves relation translation by 0.16 F1-score,
and in turn improves entity translation by 0.02.
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
        Understanding relations is important in entity tasks.
In this paper,
we illustrate such importance using named entity (NE) translation mining problem.
Early research on NE translation used phonetic similarities,
for example, to mine the translation ‘Mandelson’
        →
        ‘
        UTF8zhfsæ¼å¾·å°æ£®’[ManDeErSen] with similar
sounds
        [9, 15]
        .
However, not all NE translations are based on transliterations, but they might be
based on semantics (e.g., ‘WTO’
        →
        ‘
        UTF8zhfsä¸è´¸ç»ç»’[ShiMaoZuZhi]),
or even arbitrary (e.g., ‘Jackie Chan’
        →
        ‘
        UTF8zhfsæé¾’[ChengLong]).
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        To address this challenge,
current state-of-the-art approaches build an entity graph for each language corpus,
and align the two graphs by propagating the seed translation similarities (Figure
        1
        )
        [7, 17]
        .
For example, arbitrary translation pair such as (Jackie Chan,
        UTF8zhfsæé¾) can be obtained,
if he is connected to his film
‘Drunken Master’ (
        UTF8zhfséæ³) in both graphs.
That is, we can propagate the seed translation similarity of (Drunken Master,
        UTF8zhfséæ³)
to neighbor entities ‘Jackie Chan’ and ‘
        UTF8zhfsæé¾’ in each graph.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        When two graphs are obtained from parallel corpora,
graphs are symmetric and “blind propagation” described above is effective.
In contrast,
        Lee and Hwang ()
        propose “selective propagation”
for asymmetric graphs, of comparing the semantics of relations.
A key contribution of this paper is using relation temporality for determining relation equivalence.
Existing work
        [14, 12, 11]
        uses only co-occurring
entity pairs, or
        e
        xplicit
        f
        eatures (EF).
For example, for a relation
        <span class="ltx_inline-block ltx_transformed_outer" style="width:144.0pt;height:12.5px;vertical-align:-2.0pt;">
         <span class="ltx_transformed_inner" style="transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-webkit-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-ms-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;">
          <p class="ltx_p">
           pay an official visit to
          </p>
         </span>
        </span>
        ,
with a statement (Bush,
        <span class="ltx_inline-block ltx_transformed_outer" style="width:144.0pt;height:12.5px;vertical-align:-2.0pt;">
         <span class="ltx_transformed_inner" style="transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-webkit-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-ms-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;">
          <p class="ltx_p">
           pay an official visit to
          </p>
         </span>
        </span>
        , China),
an entity pair (Bush, China)
is in the “support set”, which is a set of co-occurring entity pairs of
        <span class="ltx_inline-block ltx_transformed_outer" style="width:144.0pt;height:12.5px;vertical-align:-2.0pt;">
         <span class="ltx_transformed_inner" style="transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-webkit-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;-ms-transform:translate(-18.0pt,0.0pt) scale(0.8,1.0) ;">
          <p class="ltx_p">
           pay an official visit to
          </p>
         </span>
        </span>
        .
When its support set is {(Bush, China), (Mandelson, Moscow), (Rice, Israel)},
and that of visit is {(Bush, China), (Rice, Israel), (Medvedev, Cuba)},
we can infer their semantic equivalence based on the set intersection:
{(Bush, China), (Rice, Israel)}.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In contrast, we propose to explore corpus
        l
        atent
        f
        eatures (LF), to complement the sparsity problem of
EF: Out of 158 randomly chosen correct relation translation pairs we labeled,
64% has only one co-occurring entity pair,
which makes EF not very effective to identify these relation translations.
Therefore, we leverage
        relation temporality
        , which is both orthogonal and complementary to
existing efforts leveraging
        entity temporality
        [8, 6, 16]
        .
In particular, we discover three new challenges on using temporality for relation understanding in comparable corpora,
which we discuss in detail in Section
        3.2
        .
Based on these challenges, we identify three new features for LF.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We observe the complementary nature of EF and LF,
then propose a hybrid approach combining both features.
Our new hybrid approach significantly improves the relation translation (0.16 higher F1-score than EF),
and in turn improves the entity translation (0.02 higher F1-score).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Preliminary: Entity Translation by Selective Propagation
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Selective propagation,
leveraging the statements extracted from bilingual comparable corpora, can be summarized by several steps.
       </p>
       <ul class="ltx_itemize" id="I1">
        [leftmargin=12mm,topsep=0.7ex]
        <li class="ltx_item" id="I1.ix1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          Step 1
         </span>
         <div class="ltx_para" id="I1.ix1.p1">
          <p class="ltx_p">
           Initialize entity translation function
           TN(0)
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          Step 2
         </span>
         <div class="ltx_para" id="I1.ix2.p1">
          <p class="ltx_p">
           Build relation translation function
           TR(t)
           using
           TN(t)
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          Step 3
         </span>
         <div class="ltx_para" id="I1.ix3.p1">
          <p class="ltx_p">
           Update entity translation function to acquire
           TN(t+1)
           using
           TR(t)
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          Step 4
         </span>
         <div class="ltx_para" id="I1.ix4.p1">
          <p class="ltx_p">
           Repeat
           Step 2
           and
           Step 3
           .
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        For
        Step 1
        , an existing method for entity translation is adopted.
In our experiments, we use a non-selective (hence not requiring relation translations) propagation approach
        [17]
        with
        [10]
        for a base translation matrix.
The focus of this paper is
        Step 2
        , building the translation score
        TR(t)⁢(rE,rC)
        of English relation
        rE
        and Chinese relation
        rC
        :
We will discuss the detailed procedure of
        Step 2
        and propose how to improve it in Section
        3
        .
        Step 3
        is the stage that selective propagation takes place.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Step 2
        and
        Step 3
        reinforce each other to improve the final entity translation function.
While
        Step 3
        is well-defined in
        [11]
        ,
to propagate entity translation scores when the relation semantics of the edges are equivalent,
        Step 2
        has been restricted to the explicit feature, i.e., co-occurring entities or shared context.
In clear contrast, by discovering novel latent features based on temporal properties,
we can increase the accuracy of both entity and relation translations.
Note that we omit
        t
        for readability in the following sections.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Relation Translation
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section, we present our approaches to obtain relations
of equivalent semantics across languages (e.g.,
        visit→UTF8zhfsè®¿é®
        ).
Formally, our goal is to build the relation translation score function
        TR⁢(rE,rC)
        for
English relation
        rE
        and Chinese relation
        rC
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Baseline: Explicit Feature Approach (EF)
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In this section, we briefly illustrate a baseline method EF
         [11]
         .
As we mentioned in the introduction, traditional approaches leverage common co-occurring entity-pairs.
This observation also holds in the bilingual environment by exploiting seed entity translations.
For example, let us say that we have two extracted statements:
(Bruce Willis, star in, The Sixth Sense)
and (
         UTF8zhfså¸é²æ¯
         ⋅
         UTF8zhfså¨å©æ¯ (Bruce Willis),
         UTF8zhfsä¸»æ¼ (star in),
         UTF8zhfsç¬¬å­æ (The Sixth Sense)).
Knowing a few seed entity translations using
         TN
         , ‘Bruce Willis’
         →
         ‘
         UTF8zhfså¸é²æ¯
         ⋅
         UTF8zhfså¨å©æ¯’ and
‘The Sixth Sense’
         →
         ‘
         UTF8zhfsç¬¬å­æ’,
we can find star in and
         UTF8zhfsä¸»æ¼ are semantically similar.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Specifically, we quantify this similarity based on
the number of such common entity pairs that we denote as
         |H⁢(rE,rC)|
         for an English relation
         rE
         and a Chinese relation
         rC
         .
The existing approaches are variations of using
         |H⁢(rE,rC)|
         .
Our baseline implementation uses the one by
         [11]
         ,
and we refer the reader to the paper for
formal definitions and processing steps we omitted due to the page limit.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Unfortunately, this approach suffers from sparsity of the common entity pairs
due to the incomparability of the corpora and those entities that cannot be translated by
         TN
         .
Therefore, we leverage corpus latent features as an additional signal to overcome this problem.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Latent Feature Approach (LF)
       </h3>
       <div class="ltx_subsubsection" id="S3.SS2.SSSx1">
        <h4 class="ltx_title ltx_title_subsubsection">
         Temporal Feature Discovery
        </h4>
        <div class="ltx_para" id="S3.SS2.SSSx1.p1">
         <p class="ltx_p">
          We exploit the temporal distribution
          d⁢[x]⁢(t)
          of textual element
          x
          during
          t
          -th week in statements;
we count the occurrences of the element
          x
          on a weekly basis, and normalize them to observe
          ∑td⁢[x]⁢(t)=1
          .
For example, Figure
          5
          shows
the relation temporal distribution
          d[
          visit
          ](t)
          against week
          t
          .
Unlike entities,
we can easily observe the dissimilarity of the temporal distributions of semantically equivalent relations.
We identify the three big challenges in exploiting the temporality in relation translations.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx1.p2">
         <p class="ltx_p">
          [C1] Considering temporal distributions
          d⁢[r]
          of relations alone is not sufficient.
For relations, such as visit, that involves diverse entities,
the temporal distributions are highly noisy (Figure
          5
          ).
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx1.p3">
         <p class="ltx_p">
          To address the first challenge, we use a finer-granularity unit for observing the temporality.
More specifically, we exploit a coupling of a relation and an entity:
          d[e,r,*]
          where
          e
          is an entity,
          r
          a relation, and * is a placeholder indicating
that any noun phrase is accepted for the second argument of a statement.
          As shown in Figure
          5
          ,
          d[e,r,*]
          is more distinctive and hence a key clue to find semantically equivalent relations.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx1.p4">
         <p class="ltx_p">
          [C2] Considering entity-relation coupling distribution
          d[e,r,*]
          alone is not sufficient due to the domination of individual temporality.
For example, Figure
          8
          shows
          entity-dominating
          entity-relation temporality.
If an entity has a peak at some period (Figure
          8
          ),
most relations that are coupled with the entity would have a peak at the very same period (Figure
          8
          ).
This makes all relations that appear with this entity very similar to each other regardlessly of semantics.
To address this challenge, we use features
to measure whether
          d[e,r,*]
          is too close to either of
          d⁢[e]
          or
          d⁢[r]
          .
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx1.p5">
         <p class="ltx_p">
          [C3]
Lastly, we have to eliminate false positives in relation temporality.
To illustrate, two relations deploy and
          UTF8zhfså¨…é¨ç½² (deploy at) have similar temporal behaviors (Figure
          5
          ).
However, the first relation takes [person], but the second relation [location] for the second argument.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx1.p6">
         <p class="ltx_p">
          To address this, we check the common co-occurring entity pair of the relations.
For example, we can obtain “Russia deployed an aircraft carrier”,
but not “Russia deployed at (
          UTF8zhfså¨…é¨ç½²) an aircraft carrier”.
Thus, we cannot acquire any common entity pair like (Russia, aircraft carrier) for deploy and
          UTF8zhfså¨…é¨ç½² (deploy at).
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSSx2">
        <h4 class="ltx_title ltx_title_subsubsection">
         Relation Similarity Computation
        </h4>
        <div class="ltx_para" id="S3.SS2.SSSx2.p1">
         <p class="ltx_p">
          We compute the similarity of two relations
          rE
          in English and
          rC
          in Chinese using the following 2-steps.
         </p>
         <ol class="ltx_enumerate" id="I2">
          [leftmargin=4mm,topsep=0.7ex]
          <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I2.i1.p1">
            <p class="ltx_p">
             Compute the similarity
             SC⁢P⁢(rE,rC,eE,eC)
             of temporal distributions of entity-relation couplings
for each bilingual entity pair
             (eE,eC)
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I2.i2.p1">
            <p class="ltx_p">
             Compute the translation score
             TRL⁢F⁢(rE,rC)
             by aggregating the coupling similarities.
            </p>
           </div>
          </li>
         </ol>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx2.p2">
         <p class="ltx_p">
          Considering the three challenges,
we produce a list of features
          {fx⁢(rE,rC,eE,eC)}
          to measure the coupling similarity
          SC⁢P⁢(rE,rC,eE,eC)
          as follows.
         </p>
         <ol class="ltx_enumerate" id="I3">
          [leftmargin=4mm,topsep=0.7ex]
          <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I3.i1.p1">
            <p class="ltx_p">
             [Base feature]
             fE⁢T
             :
             TN⁢(eE,eC)
             .
The entity translation score obtained in the previous iteration or the seed entity translation score.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I3.i2.p1">
            <p class="ltx_p">
             [C1]
             fE⁢R
             :
             1-JSD(d[eE,rE,*],d[eC,rC,*])
             .
The temporal similarity of the couplings, where
             J⁢S⁢D⁢(P,Q)
             is the Jensen-Shannon divergence of two distributions
             P
             and
             Q
             , defined as
             JSD(P,Q)=12D(P||M)+12D(Q||M)
             , with
             M=12⁢(P+Q)
             and
             D(P||M)=∑iP(i)logP⁢(i)M⁢(i)
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I3.i3.p1">
            <p class="ltx_p">
             [C2]
             fD⁢1,E
             ,
             fD⁢2,E
             ,
             fD⁢1,C
             ,
             fD⁢2,C
             :
            </p>
            <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
             <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
              <td class="ltx_eqn_center_padleft">
              </td>
              <td class="ltx_td ltx_align_right">
               J⁢S⁢D⁢(d⁢[eE],d⁢[eE,rE,*]), J⁢S⁢D⁢(d⁢[rE],d⁢[eE,rE,*])
              </td>
              <td class="ltx_eqn_center_padright">
              </td>
             </tr>
             <tr class="ltx_equation ltx_align_baseline" id="S3.Ex2">
              <td class="ltx_eqn_center_padleft">
              </td>
              <td class="ltx_td ltx_align_right">
               J⁢S⁢D⁢(d⁢[eC],d⁢[eC,rC,*]), J⁢S⁢D⁢(d⁢[rC],d⁢[eC,rC,*])
              </td>
              <td class="ltx_eqn_center_padright">
              </td>
             </tr>
            </table>
            <p class="ltx_p">
             Entity to entity-relation distribution difference (D1) and relation to entity-relation distribution difference (D2),
for English and Chinese respectively.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I3.i4.p1">
            <p class="ltx_p">
             [C3]
             fE⁢X
             : The existence of a common entity pair using the seed entity translations (boolean).
That is,
             fE⁢X=1
             if
             |H⁢(rE,rC)|≥1
             , and
             fE⁢X=0
             otherwise.
            </p>
           </div>
          </li>
         </ol>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx2.p3">
         <p class="ltx_p">
          Additionally, we use the following features to consider absolute frequencies
          f⁢r⁢e⁢q⁢(⋅)
          of textual elements as well
because 1) we are more confident with more evidence
and 2) in the comparable corpora, the equivalent elements are likely to show similar frequencies.
         </p>
         <ol class="ltx_enumerate" id="I4">
          [leftmargin=4mm,topsep=0.7ex]
          <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I4.i1.p1">
            <p class="ltx_p">
             fF⁢W,E
             ,
             fF⁢W,C
             :
             𝒮⁢(f⁢r⁢e⁢q⁢(eE,rE))
             and
             𝒮⁢(f⁢r⁢e⁢q⁢(eC,rC))
             .
             𝒮⁢(x)
             is a normalization function,
for which we use a sigmoid function over a linear transformation of
             x
             .
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_enumerate">
            ∙
           </span>
           <div class="ltx_para" id="I4.i2.p1">
            <p class="ltx_p">
             fF⁢S⁢1
             and
             fF⁢S⁢2
             :
            </p>
            min⁡(f⁢r⁢e⁢q⁢(eE,rE),f⁢r⁢e⁢q⁢(eC,rC))max⁡(f⁢r⁢e⁢q⁢(eE,rE),f⁢r⁢e⁢q⁢(eC,rC)),
            min⁡(f⁢r⁢e⁢q⁢(rE),f⁢r⁢e⁢q⁢(rC))max⁡(f⁢r⁢e⁢q⁢(rE),f⁢r⁢e⁢q⁢(rC))
           </div>
          </li>
         </ol>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx2.p4">
         <p class="ltx_p">
          With these features, we measure the similarity of a pair of couplings as follows.
         </p>
         SC⁢P⁢(rE,rC,eE,eC)=∏xfx⁢(rE,rC,eE,eC)

(1)
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx2.p5">
         <p class="ltx_p">
          By aggregating coupling similarities,
we measure the translation score of two relations:
         </p>
         TRLF⁢(rE,rC)=∑(eE,eC)∈TSC⁢P⁢(rE,rC,eE,eC)

(2)
         <p class="ltx_p">
          where
          T={(eE,eC)|TN⁢(eE,eC)≥θ}
          with
          θ=0.6
          ,
a set of translation pairs obtained in the seeds or previous iteration such as (Bush,
          UTF8zhfså¸ä»).
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSSx2.p6">
         <p class="ltx_p">
          We normalize the obtained function values for each English relations
using the top-
          k
          Chinese translations.
That is, for
          (rE,rC)
          , we redefine the score as
          TRL⁢F⁢(rE,rC)/∑i∈[1,k]TRL⁢F⁢(rE,rCr⁢a⁢n⁢ki)
          where
          rCr⁢a⁢n⁢ki
          is the
          i
          -th rank Chinese relation for
          rE
          by Equation
          2
          .
We empirically set
          k=4
          .
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Hybrid Approach LF+EF
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         We find that LF and EF are complementary.
Table
         1
         shows the examples of relations and their translations. In general, LF can translate more relations (e.g., support and capture).
However, in some cases like ratify, highly
         related
         relations may induce noise.
That is, we always
         UTF8zhfsè®¨è®º (discuss) before we
         UTF8zhfsæ¹å (ratify) something
and hence the temporal behavior of
         UTF8zhfsè®¨è®º (discuss) is also very similar to that of ratify.
On the other hand,
it
can be correctly translated using EF.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         Thus, we produce the hybrid relation translation, and we empirically set
         λ=0.4
         :
        </p>
        TR

LF+EF
⁢(rE,rC)=λ⁢TR

LF
⁢(rE,rC)⁢+(1-λ)⁢TR

EF
⁢(rE,rC)

(3)
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Evaluation
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section, we evaluate the proposed approach
on the entity translation task and the relation translation task.
We extract English and Chinese statements
from news articles in 2008 by Xinhua news who publishes news in both English and Chinese,
which were also used by
        Lee and Hwang ()
        .
The number of English articles is 100,746, and that of Chinese articles is 88,031.
As we can see from the difference in the numbers of the documents,
the news corpora are not direct translations, but they have asymmetry of entities and relations.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Entity Translation
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         In this section, we present experimental settings
and results on translating entities using our proposed approaches.
To measure the effectiveness, we use a set of gold standard entity translation pairs which consist of
221 person entities and 52 organization entities.
We measure precision, recall, and F1-score based on the returned translation pairs for each English entity
as it is done in
         [11]
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         We compare our hybrid approach, which is denoted by LF+EF with EF
         [11]
         ,
a combined approach PH+SM of phonetic similarity and letter-wise semantic translation for better accuracy for organizations
         [10]
         ,
and the seed translations Seed that we adopt
         [17]
         with
PH+SM as a base translation matrix.
         We process one iteration of the entire framework (
         Step 1-3
         )
for both LF+EF and EF.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         Table
         2
         shows the comparison of the methods.
Our proposed approach LF+EF
shows higher F1-score than the baselines.
In particular, our approach outperforms EF.
For example, ‘Matthew Emmons’ is a lesser known entity,
and we have only few statements mentioning him in the corpora.
The corpus explicit feature
EF alone cannot
translate the relation win and, in turn, ‘Matthew Emmons’.
However,
LF+EF translates him correctly into
         UTF8zhfsé©¬ä¿®Â·åèæ¯
through the relation win.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Relation Translation
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         This section considers
the relation translation task.
Each relation translation method translates an English relation
         rE
         into a list of Chinese relations, and we check
whether a Chinese relation
         rC
         with the highest translation score is the correct translation.
We consider the relation translation is correct
when the semantics are equivalent. For example,
         UTF8zhfså» (leave for/go to) is a correct
translation of leave for,
but
         UTF8zhfsç¦»å¼ (leave) is
         not
         .
Total 3342 English-Chinese relation translation pairs returned by our method and the baselines are randomly shown and labeled.
Out of 3342 pairs, 399 are labeled as correct.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Table
         3
         shows the comparisons of LF, EF and their hybrid LF+EF.
We can clearly see that LF shows higher recall than EF
while EF shows higher precision.
As we emphasized in Section
         3.3
         ,
we can see their complementary property.
Their hybrid LF+EF
has both high precision and recall,
thus has the highest F1-score.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         Note that the absolute numbers (due to the harsh evaluation criteria) may look low.
But the top translations are still relevant (e.g., fight is translated to
         UTF8zhfsé©» (deploy troops)).
In addition, the lower ranked but correct relation translations also affect entity translation.
Therefore, even lower-performing EF boosted the entity translations, and
in effect, our approach could achieve higher F1-score in the entity translation task.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         To illustrate the detailed effects of the corpus latent features,
Table
         4
         shows the ranks of correct Chinese translations for
English relations by methods using selected features for the challenges.
For comparison, the ranks of the correct translations when using EF are shown.
Our approach using the entity-relation coupling similarity feature for [C1] alone often
cannot find the correct translations.
But using all features removes such noise.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
