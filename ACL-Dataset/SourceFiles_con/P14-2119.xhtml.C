<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Infusion of Labeled Data into Distant Supervision for Relation Extraction.
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
       Distant supervision usually utilizes only unlabeled data and existing knowledge bases to learn relation extraction models.
However, in some cases a small amount of human labeled data is available. In this paper, we demonstrate how a state-of-the-art
multi-instance multi-label model can be modified to make use of these reliable sentence-level labels in addition
to the relation-level distant supervision from a database. Experiments show that our approach achieves a statistically significant increase of 13.5% in
F-score and 37% in area under the precision recall curve.
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
        Relation extraction is the task of tagging semantic relations between pairs of entities from free text. Recently, distant supervision has
emerged as an important technique for relation extraction and has attracted increasing attention because of its effective use of readily
available databases
        []
        .
It automatically labels its own training data by heuristically aligning a knowledge base of facts
with an unlabeled corpus. The intuition is that any sentence which mentions a pair of entities (
        e1
        and
        e2
        ) that
participate in a relation,
        r
        , is likely to express the fact
        r⁢(e1,e2)
        and thus forms a positive training example of
        r
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        One of most crucial problems in distant supervision is the inherent errors in the automatically generated training data
        []
        . Table
        1
        illustrates this problem
with a toy example.
Sophisticated multi-instance learning algorithms
        []
        have been proposed to
address the issue by loosening the distant supervision assumption. These approaches consider all mentions of the same pair
        (e1,e2)
        and assume
that
        a⁢t
        -
        l⁢e⁢a⁢s⁢t
        -
        o⁢n⁢e
        mention actually expresses the relation.
On top of that, researchers further improved performance by explicitly adding preprocessing
steps
        []
        or additional layers inside the model
        []
        to reduce the effect of training noise.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        However, the potential of these previously proposed approaches is limited by the inevitable gap between the relation-level knowledge and the instance-level
extraction task. In this paper, we present the first effective approach,
        𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
        (distant supervision), to incorporate labeled data into distant
supervision for extracting relations from sentences. In contrast to simply taking the union of the hand-labeled data and the corpus labeled by
distant supervision as in the previous work by Zhang et al.
        []
        , we generalize the labeled data through feature selection and
model this additional information directly in the latent variable approaches. Aside from previous semi-supervised work that employs labeled and unlabeled data
        [, and others]
        , this is a learning scheme that combines unlabeled text and two training sources whose quantity and quality are radically different
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        To demonstrate the effectiveness of our proposed approach, we extend
        𝖬𝖨𝖬𝖫
        []
        , a state-of-the-art distant supervision model
and show a significant improvement of 13.5% in F-score on the relation extraction benchmark TAC-KBP
        []
        dataset. While prior work employed tens
of thousands of human labeled examples
        []
        and only got a 6.5% increase in F-score over a logistic regression baseline, our approach
uses much less labeled data (about 1/8) but achieves much higher improvement on performance over stronger baselines.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       The Challenge
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Simply taking the union of the hand-labeled data and the corpus labeled by distant supervision is not effective since hand-labeled
data will be swamped by a larger amount of distantly labeled data. An effective approach must recognize that the hand-labeled data
is more reliable than the automatically labeled data and so must take precedence
in cases of conflict. Conflicts cannot be limited to those cases where all the
features in two examples are the same; this would almost never occur, because of the dozens of features used by a typical relation
extractor
        []
        .
Instead we propose to perform feature selection to generalize human labeled data into
        training guidelines
        , and integrate them into latent variable model.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Guidelines
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         The sparse nature of feature space dilutes the discriminative capability of useful features.
Given the small amount of hand-labeled data, it is important to
identify a small set of features that are general enough while being capable of
predicting quite accurately the type of relation that may hold
between two entities.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         We experimentally tested alternative feature sets by building
supervised Maximum Entropy (MaxEnt) models using the hand-labeled data (Table
         3
         ), and selected
an effective combination of three features from the full feature set used by Surdeanu et al.,
         []
         :
        </p>
        <ul class="ltx_itemize" id="I1">
         [leftmargin=*]
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            the semantic types of the two arguments (e.g. person, organization, location, date, title, …)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            the sequence of dependency relations along the path
connecting the heads of the two arguments in the dependency tree.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            a word in the sentence between the two arguments
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         These three features are strong indicators of the type
of relation between two entities. In some cases the
semantic types of the arguments alone narrows the
possibilities to one or two relation types.
For example, entity types such as
         𝗉𝖾𝗋𝗌𝗈𝗇
         and
         𝗍𝗂𝗍𝗅𝖾
         often implies the relation
         𝗉𝖾𝗋𝗌𝗈𝗇𝖳𝗂𝗍𝗅𝖾
         .
Some lexical items
are clear indicators of particular relations, such as “brother” and “sister” for a sibling relationship
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         We extract guidelines from hand-labeled data. Each guideline
         g
         ={
         gi|i
         =1,2,3} consists of a pair of
semantic types, a dependency path, and optionally
a span word and is associated with a particular relation
         r⁢(g)
         . We keep only those guidelines which make the correct
prediction for
         a⁢l⁢l
         and at least
         k
         =3 examples in the training
corpus (threshold 3 was obtained by running experiments on the development dataset). Table
         2
         shows some examples in the final set
         𝐆
         of extracted guidelines.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Guided DS
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Our goal is to jointly model human-labeled ground truth and structured data from a knowledge base in distant supervision. To do this, we extend the MIML model
        []
        by adding a new layer as shown in Figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The input to the model consists of (1) distantly supervised data, represented as a list of
        n
        bags
        with a vector
        𝐲𝐢
        of binary gold-standard labels,
either
        P⁢o⁢s⁢i⁢t⁢i⁢v⁢e⁢(P)
        or
        N⁢e⁢g⁢a⁢t⁢i⁢v⁢e⁢(N)
        for each relation
        r∈R
        ; (2) generalized human-labeled ground truth, represented as a set
        G
        of feature conjunctions
        g
        ={
        gi|i
        =1,2,3} associated with a unique relation
        r⁢(g)
        .
Given a bag of sentences,
        𝐱𝐢
        , which mention an
        i
        th entity pair (
        e1
        ,
        e2
        ),
our goal is to correctly predict which relation is mentioned in each sentence, or
        N⁢R
        if none of the relations under consideration are mentioned.
The vector
        𝐳𝐢
        contains the latent mention-level classifications for the
        i
        th entity pair.
We introduce a set of latent variables
        𝐡𝐢
        which model human ground truth for each mention in the
        i
        th bag
and take precedence over the current model assignment
        𝐳𝐢
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Let
        i,j
        be the index in the bag and the mention level, respectively.
We model mention-level extraction
        p(zi⁢j|𝐱i⁢j;𝐰z)
        ,
human relabeling
        hi⁢j⁢(𝐱i⁢j,zi⁢j)
        and multi-label aggregation
        p(yir|𝐡i;𝐰𝐲)
        .
We define:
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <ul class="ltx_itemize" id="I2">
        [leftmargin=*]
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           yir∈{P,N}:r
           holds for the
           i
           th bag or not.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           𝐱i⁢j
           is the feature representation of the
           j
           th relation mention in the
           i
           th bag. We use the same set of features as in Surdeanu et al. (2012).
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           zi⁢j∈R∪N⁢R
           : a latent variable that denotes the relation of the
           j
           th mention in the
           i
           th bag
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           hi⁢j∈R∪N⁢R
           : a latent variable that denotes the refined relation of the mention
           𝐱i⁢j
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        We define relabeled relations
        hi⁢j
        as following:
       </p>
       hi⁢j⁢(xi⁢j,zi⁢j)={r(g),if∃!g∈𝐆s.t.g={gk}⊆{𝐱i⁢j}zi⁢j,otherwise
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Thus, relation
        r⁢(g)
        is assigned to
        hi⁢j
        iff there exists a unique guideline
        g∈𝐆
        ,
such that the feature vector
        𝐱i⁢j
        contains all constituents of
        g
        , i.e.
entity types, a dependency path and maybe a span word, if
        g
        has one.
We use mention relation
        zi⁢j
        inferred by the model
only in case no such a guideline exists or there is more than one matching guideline.
We also define:
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <ul class="ltx_itemize" id="I3">
        [leftmargin=*]
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           𝐰z
           is the weight vector for the multi-class relation mention-level classifier
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           𝐰yr
           is the weight vector for the
           r
           th binary top-level aggregation classifier (from mention labels to bag-level prediction).
We use
           𝐰y
           to represent
           𝐰y1,𝐰y2,…,𝐰y|R|
           .
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        Our approach is aimed at improving the mention-level classifier, while keeping the multi-instance multi-label
framework to allow for joint modeling.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Training
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We use a hard expectation maximization algorithm to train the model.
Our objective function is to maximize log-likelihood of the data:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          LL(𝐰𝐲,𝐰𝐳)=∑i=1nlogp(𝐲𝐢|𝐱𝐢,𝐰𝐲,𝐰𝐳,𝐆)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex3">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          =∑i=1nlog∑𝐡𝐢p(𝐲𝐢,𝐡𝐢|𝐱𝐢,𝐰𝐲,𝐰𝐳,𝐆)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          =∑i=1nlog∑𝐡𝐢∏j=1|𝐡𝐢|p(hi⁢j|𝐱i⁢j,𝐰𝐳,𝐆)∏r∈Pi∪Nip(yir|𝐡i,𝐰𝐲r)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where the last equality is due to conditional independence.
Because of the non-convexity of
        L⁢L⁢(𝐰𝐲,𝐰𝐳)
        we approximate and maximize the joint log-probability
        p(𝐲𝐢,𝐡𝐢|𝐱𝐢,𝐰𝐲,𝐰𝐳,𝐆)
        for each entity pair in the database:
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex5">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          logp(𝐲𝐢,𝐡𝐢|𝐱𝐢,𝐰𝐲,𝐰𝐳,𝐆)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex6">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          =∑j=1|𝐡𝐢|logp(hi⁢j|𝐱i⁢j,𝐰𝐳,𝐆)+∑r∈Pi∪Nilogp(yir|𝐡i,𝐰𝐲r).
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        [h!]
        : Guided DS training
        [1]
        Phase 1: build set
        G
        of guidelines
        Phase 2: EM training
        iteration=1,…,T
        <math alttext="i=1,\dots,n" class="ltx_Math" display="inline" id="S4.p3.m2" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mi>
           i
          </mi>
          <mo>
           =
          </mo>
          <mrow>
           <mn>
            1
           </mn>
           <mo>
            ,
           </mo>
           <mi mathvariant="normal">
            …
           </mi>
           <mo>
            ,
           </mo>
           <mi>
            n
           </mi>
          </mrow>
         </mrow>
        </math>
        <math alttext="j=1,\dots,|{\bf x_{i}}|" class="ltx_Math" display="inline" id="S4.p3.m3" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mi>
           j
          </mi>
          <mo>
           =
          </mo>
          <mrow>
           <mn>
            1
           </mn>
           <mo>
            ,
           </mo>
           <mi mathvariant="normal">
            …
           </mi>
           <mo>
            ,
           </mo>
           <mrow>
            <mo fence="true">
             |
            </mo>
            <msub>
             <mi>
              𝐱
             </mi>
             <mi>
              𝐢
             </mi>
            </msub>
            <mo fence="true">
             |
            </mo>
           </mrow>
          </mrow>
         </mrow>
        </math>
        <math alttext="\!\!\!\!\!\!z_{ij}^{*}\!\!={\rm argmax}_{z_{ij}}p(z_{ij}|{\bf x_{i},\!y_{i},\!%
w_{z},\!w_{y}}\!)" class="ltx_Math" display="inline" id="S4.p3.m4" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mpadded width="-3.4pt">
           <msubsup>
            <mpadded lspace="-10.2pt" width="-10.2pt">
             <mi>
              z
             </mi>
            </mpadded>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
            <mo>
             *
            </mo>
           </msubsup>
          </mpadded>
          <mo>
           =
          </mo>
          <msub>
           <mi>
            argmax
           </mi>
           <msub>
            <mi>
             z
            </mi>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
           </msub>
          </msub>
          <mi>
           p
          </mi>
          <mrow>
           <mo>
            (
           </mo>
           <msub>
            <mi>
             z
            </mi>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
           </msub>
           <mo>
            |
           </mo>
           <msub>
            <mi>
             𝐱
            </mi>
            <mi>
             𝐢
            </mi>
           </msub>
           <mo rspace="0.8pt">
            ,
           </mo>
           <msub>
            <mi>
             𝐲
            </mi>
            <mi>
             𝐢
            </mi>
           </msub>
           <mo rspace="0.8pt">
            ,
           </mo>
           <msub>
            <mi>
             𝐰
            </mi>
            <mi>
             𝐳
            </mi>
           </msub>
           <mo rspace="0.8pt">
            ,
           </mo>
           <mpadded width="-1.7pt">
            <msub>
             <mi>
              𝐰
             </mi>
             <mi>
              𝐲
             </mi>
            </msub>
           </mpadded>
           <mo>
            )
           </mo>
          </mrow>
         </mrow>
        </math>
        <math alttext="\!\!\!\!\!\!h_{ij}^{*}\!\!\!=\!\!\left\{\begin{array}[]{l}\!\!\!\!r(g),\!\ {%
\rm if\ }\exists!\ \!g\!\in\!{\bf G}\!:\!\{g_{k}\!\}\!\!\subseteq\!\!\{{\bf x}%
_{ij}\!\}\\
\!\!\!{z_{ij}}^{*}\ ,{\rm\ otherwise}\end{array}\right." class="ltx_Math" display="inline" id="S4.p3.m5" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mpadded width="-5.1pt">
           <msubsup>
            <mpadded lspace="-10.2pt" width="-10.2pt">
             <mi>
              h
             </mi>
            </mpadded>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
            <mo>
             *
            </mo>
           </msubsup>
          </mpadded>
          <mo rspace="0pt">
           =
          </mo>
          <mrow>
           <mo>
            {
           </mo>
           <mtable align="center" columnspacing="0.4em" rowspacing="0.2ex">
            <mtr>
             <mtd columnalign="left">
              <mrow>
               <mrow>
                <mrow>
                 <mrow>
                  <mpadded lspace="-6.8pt" width="-6.8pt">
                   <mi>
                    r
                   </mi>
                  </mpadded>
                  <mo>
                   ⁢
                  </mo>
                  <mrow>
                   <mo>
                    (
                   </mo>
                   <mi>
                    g
                   </mi>
                   <mo>
                    )
                   </mo>
                  </mrow>
                 </mrow>
                 <mo>
                  ,
                 </mo>
                 <mrow>
                  <mpadded width="+5.0pt">
                   <mi>
                    if
                   </mi>
                  </mpadded>
                  <mo>
                   ⁢
                  </mo>
                  <mrow>
                   <mo>
                    ∃
                   </mo>
                   <mi mathvariant="normal">
                    !
                   </mi>
                  </mrow>
                 </mrow>
                 <mo separator="true">
                 </mo>
                 <mpadded width="-1.7pt">
                  <mi>
                   g
                  </mi>
                 </mpadded>
                </mrow>
                <mo rspace="0.8pt">
                 ∈
                </mo>
                <mpadded width="-1.7pt">
                 <mi>
                  𝐆
                 </mi>
                </mpadded>
               </mrow>
               <mo rspace="0.8pt">
                :
               </mo>
               <mrow>
                <mrow>
                 <mo>
                  {
                 </mo>
                 <mpadded width="-1.7pt">
                  <msub>
                   <mi>
                    g
                   </mi>
                   <mi>
                    k
                   </mi>
                  </msub>
                 </mpadded>
                 <mo>
                  }
                 </mo>
                </mrow>
                <mo rspace="0pt">
                 ⊆
                </mo>
                <mrow>
                 <mo>
                  {
                 </mo>
                 <mpadded width="-1.7pt">
                  <msub>
                   <mi>
                    𝐱
                   </mi>
                   <mrow>
                    <mi>
                     i
                    </mi>
                    <mo>
                     ⁢
                    </mo>
                    <mi>
                     j
                    </mi>
                   </mrow>
                  </msub>
                 </mpadded>
                 <mo>
                  }
                 </mo>
                </mrow>
               </mrow>
              </mrow>
             </mtd>
            </mtr>
            <mtr>
             <mtd columnalign="left">
              <mrow>
               <mpadded width="+5.0pt">
                <mmultiscripts>
                 <mpadded lspace="-5.1pt" width="-5.1pt">
                  <mi>
                   z
                  </mi>
                 </mpadded>
                 <mrow>
                  <mi>
                   i
                  </mi>
                  <mo>
                   ⁢
                  </mo>
                  <mi>
                   j
                  </mi>
                 </mrow>
                 <none>
                 </none>
                 <none>
                 </none>
                 <mo>
                  *
                 </mo>
                </mmultiscripts>
               </mpadded>
               <mo separator="true">
                ,
               </mo>
               <mi>
                otherwise
               </mi>
              </mrow>
             </mtd>
            </mtr>
           </mtable>
          </mrow>
         </mrow>
        </math>
        <span class="ltx_text ltx_font_bold">
         update
         <math alttext="\bf h_{i}" class="ltx_Math" display="inline" id="S4.p3.m6" xmlns="http://www.w3.org/1998/Math/MathML">
          <msub>
           <mi>
            𝐡
           </mi>
           <mi>
            𝐢
           </mi>
          </msub>
         </math>
         with
        </span>
        hi⁢j*
        <span class="ltx_ERROR undefined">
         \EndFor
        </span>
        <math alttext="{\bf w}_{\bf z}^{*}\!\!=\!\!{\rm argmax}_{\bf w}\!\sum_{i=1}^{n}\!\sum_{j=1}^{%
|{\bf x_{i}}|}\!\log p(h_{ij}|{\bf x}_{ij},\!\!{\bf w}\!)" class="ltx_Math" display="inline" id="S4.p3.m8" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mpadded width="-3.4pt">
           <msubsup>
            <mi>
             𝐰
            </mi>
            <mi>
             𝐳
            </mi>
            <mo>
             *
            </mo>
           </msubsup>
          </mpadded>
          <mo rspace="0pt">
           =
          </mo>
          <mpadded width="-1.7pt">
           <msub>
            <mi>
             argmax
            </mi>
            <mi>
             𝐰
            </mi>
           </msub>
          </mpadded>
          <mpadded width="-1.7pt">
           <msubsup>
            <mo largeop="true" symmetric="true">
             ∑
            </mo>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              =
             </mo>
             <mn>
              1
             </mn>
            </mrow>
            <mi>
             n
            </mi>
           </msubsup>
          </mpadded>
          <mpadded width="-1.7pt">
           <msubsup>
            <mo largeop="true" symmetric="true">
             ∑
            </mo>
            <mrow>
             <mi>
              j
             </mi>
             <mo>
              =
             </mo>
             <mn>
              1
             </mn>
            </mrow>
            <mrow>
             <mo fence="true">
              |
             </mo>
             <msub>
              <mi>
               𝐱
              </mi>
              <mi>
               𝐢
              </mi>
             </msub>
             <mo fence="true">
              |
             </mo>
            </mrow>
           </msubsup>
          </mpadded>
          <mi>
           log
          </mi>
          <mi>
           p
          </mi>
          <mrow>
           <mo>
            (
           </mo>
           <msub>
            <mi>
             h
            </mi>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
           </msub>
           <mo>
            |
           </mo>
           <msub>
            <mi>
             𝐱
            </mi>
            <mrow>
             <mi>
              i
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              j
             </mi>
            </mrow>
           </msub>
           <mo rspace="0pt">
            ,
           </mo>
           <mpadded width="-1.7pt">
            <mi>
             𝐰
            </mi>
           </mpadded>
           <mo>
            )
           </mo>
          </mrow>
         </mrow>
        </math>
        <math alttext="r\in R" class="ltx_Math" display="inline" id="S4.p3.m9" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mi>
           r
          </mi>
          <mo>
           ∈
          </mo>
          <mi>
           R
          </mi>
         </mrow>
        </math>
        <math alttext="{\bf w_{y}^{r*}}\!\!=\!{\rm argmax}_{\bf w}\!\!\!\!\!\!\!\!\!\!\!\sum\limits_{%
1\leq i\leq n\ s.t.\ r\in P_{i}\cup N_{i}}\!\!\!\!\!\!\!\!\!\!\!\log p(y_{i}^{%
r}|{\bf h_{i}},\!\!{\bf w}\!)" class="ltx_Math" display="inline" id="S4.p3.m10" xmlns="http://www.w3.org/1998/Math/MathML">
         <mrow>
          <mpadded width="-3.4pt">
           <msubsup>
            <mi>
             𝐰
            </mi>
            <mi>
             𝐲
            </mi>
            <mrow>
             <mi>
              𝐫
             </mi>
             <mo>
              ⁣
             </mo>
             <mo>
              *
             </mo>
            </mrow>
           </msubsup>
          </mpadded>
          <mo rspace="0.8pt">
           =
          </mo>
          <mpadded width="-18.7pt">
           <msub>
            <mi>
             argmax
            </mi>
            <mi>
             𝐰
            </mi>
           </msub>
          </mpadded>
          <mpadded width="-18.7pt">
           <munder>
            <mo largeop="true" movablelimits="false" symmetric="true">
             ∑
            </mo>
            <mrow>
             <mrow>
              <mn>
               1
              </mn>
              <mo>
               ≤
              </mo>
              <mi>
               i
              </mi>
              <mo>
               ≤
              </mo>
              <mrow>
               <mpadded width="+5.0pt">
                <mi>
                 n
                </mi>
               </mpadded>
               <mo>
                ⁢
               </mo>
               <mi>
                s
               </mi>
              </mrow>
             </mrow>
             <mo separator="true">
              .
             </mo>
             <mi>
              t
             </mi>
             <mo separator="true">
              .
             </mo>
             <mrow>
              <mi>
               r
              </mi>
              <mo>
               ∈
              </mo>
              <mrow>
               <msub>
                <mi>
                 P
                </mi>
                <mi>
                 i
                </mi>
               </msub>
               <mo>
                ∪
               </mo>
               <msub>
                <mi>
                 N
                </mi>
                <mi>
                 i
                </mi>
               </msub>
              </mrow>
             </mrow>
            </mrow>
           </munder>
          </mpadded>
          <mi>
           log
          </mi>
          <mi>
           p
          </mi>
          <mrow>
           <mo>
            (
           </mo>
           <msubsup>
            <mi>
             y
            </mi>
            <mi>
             i
            </mi>
            <mi>
             r
            </mi>
           </msubsup>
           <mo>
            |
           </mo>
           <msub>
            <mi>
             𝐡
            </mi>
            <mi>
             𝐢
            </mi>
           </msub>
           <mo rspace="0pt">
            ,
           </mo>
           <mpadded width="-1.7pt">
            <mi>
             𝐰
            </mi>
           </mpadded>
           <mo>
            )
           </mo>
          </mrow>
         </mrow>
        </math>
        <span class="ltx_ERROR undefined">
         \EndFor
        </span>
        <span class="ltx_text ltx_font_bold">
         return
        </span>
        𝐰𝐳,𝐰𝐲
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        The pseudocode is presented as algorithm 1.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        The following approximation is used for inference at step 6:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx3">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex7">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          p(zi⁢j|
         </td>
         <td class="ltx_td ltx_align_left">
          𝐱𝐢,𝐲𝐢,𝐰𝐳,𝐰𝐲)∝p(𝐲𝐢,zi⁢j|𝐱𝐢,𝐰𝐲,𝐰𝐳)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex8">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          ≈p(zi⁢j|xi⁢j,𝐰𝐳)p(𝐲𝐢|𝐡𝐢′,𝐰𝐲)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex9">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          =p(zi⁢j|xi⁢j,𝐰𝐳)∏r∈Pi∪Nip(yir|𝐡𝐢′,𝐰𝐲𝐫),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        where
        𝐡𝐢′
        contains previously inferred and maybe further relabeled mention labels for group
        i
        (steps 5-10), with the exception of component
        j
        whose label is replaced by
        zi⁢j
        .
In the M-step (lines 12-15) we optimize model parameters
        𝐰𝐳,𝐰𝐲
        , given the current assignment
of mention-level labels
        𝐡𝐢
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        Experiments show that
        𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
        efficiently learns new model,
resulting in a drastically decreasing
number of needed relabelings for further iterations (Table
        4
        ).
At the inference step we first classify all mentions:
       </p>
       zi⁢j*=argmaxz∈R∪N⁢Rp(z|xi⁢j,𝐰𝐳)
       <p class="ltx_p">
        Then final relation labels for
        i
        th entity tuple are obtained via the top-level classifiers:
       </p>
       yir⁣*=argmaxy∈{P,N}p(y|𝐳𝐢*,𝐰𝐲𝐫)
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Data
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We use the KBP
         []
         dataset
         which is preprocessed by Surdeanu et al.
         []
         using the Stanford parser
         []
         .
This dataset is generated by mapping Wikipedia
infoboxes into a large unlabeled corpus that consists of 1.5M documents from KBP source corpus and a complete snapshot of Wikipedia.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         The KBP 2010 and 2011 data includes 200 query named entities with the relations they are involved in.
We used 40 queries as development set and the rest 160 queries (3334 entity pairs that express a relation) as the test set.
The official KBP evaluation is performed by pooling the system responses and manually reviewing each response,
producing a hand-checked assessment data. We used KBP 2012 assessment data to generate guidelines since
queries from different years do not overlap. It contains about 2500
labeled sentences of 41 relations, which
is less than 0.09% of the size of the distantly labeled dataset of 2M sentences.
The final set
         G
         consists of 99 guidelines (section
         2.1
         ).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Models
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We implement
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         on top of the
         𝖬𝖨𝖬𝖫
         []
         code base
         .
Training
         𝖬𝖨𝖬𝖫
         on a simple fusion of distantly-labeled and human-labeled datasets does not improve the maximum F-score since
this hand-labeled data is swamped by a much larger amount of distant-supervised data of much lower quality. Upsampling the labeled data did not improve the performance either.
We experimented with different upsampling ratios and report best results using ratio 1:1 in Figure
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Our baselines: 1)
         𝖬𝖺𝗑𝖤𝗇𝗍
         is a supervised maximum entropy baseline trained on a human-labeled data;
2)
         𝖣𝖲
         +
         𝗎𝗉𝗌𝖺𝗆𝗉𝗅𝗂𝗇𝗀
         is an upsampling experiment, where
         𝖬𝖨𝖬𝖫
         was trained on a
mix of a distantly-labeled and human-labeled data;
3)
         𝖲𝖾𝗆𝗂
         -
         𝖬𝖨𝖬𝖫
         is a recent semi-supervised extension.
We also compare
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         with three state-of-the-art models:
1)
         𝖬𝗎𝗅𝗍𝗂𝖱
         and 2)
         𝖬𝖨𝖬𝖫
         are two distant supervision models that support multi-instance learning
and overlapping relations;
3)
         𝖬𝗂𝗇𝗍𝗓
         ++ is a single-instance learning algorithm for distant supervision.
The difference between
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         and all other systems is significant
with
         p
         -value less than 0.05 according to a paired
         t
         -test assuming a normal distribution.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         We scored our model against all 41 relations and thus replicated the actual KBP evaluation.
Figure
         2
         shows that our model consistently outperforms all six algorithms at almost all recall levels and
improves the maximum
         F
         -score by more than 13.5
         %
         relative to
         𝖬𝖨𝖬𝖫
         (from 28.35
         %
         to 32.19
         %
         ) as well as increases the area under precision-recall curve by more than 37% (from 11.74 to 16.1).
Also,
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         improves the overall recall by more than 9% absolute
(from 30.9% to 39.93%) at a comparable level of precision
(24.35% for
         𝖬𝖨𝖬𝖫
         vs 23.64% for
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         ), while increases the running time of
         𝖬𝖨𝖬𝖫
         by only 3%.
Thus, our approach outperforms state-of-the-art model for relation extraction using much less labeled data
that was used by Zhang et al.,
         []
         to outperform logistic regression baseline.
Performance of
         𝐆⁢𝗎𝗂𝖽𝖾𝖽⁢𝖣𝖲
         also compares favorably with best scored hand-coded systems for a similar task such as Sun et al.,
         []
         system for KBP 2011, which reports an F-score of 25.7%.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
