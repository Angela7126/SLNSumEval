<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Predicting Grammaticality on an Ordinal Scale.
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
       Automated methods for identifying whether sentences are grammatical
have various potential applications (e.g., machine translation, automated essay scoring,
computer-assisted language learning).
In this work, we construct a statistical model of grammaticality using various linguistic features
(e.g., misspelling counts, parser outputs,
       n
       -gram language model scores).
We also present a new publicly available dataset
of learner sentences judged for grammaticality on an ordinal scale.
In evaluations, we compare our system to the one from
       Post (2011)
       and find that our approach yields state-of-the-art performance.
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
        In this paper, we develop a system
for the task of predicting the grammaticality of sentences,
and present a dataset of learner sentences rated for grammaticality.
Such a system could be used, for example,
to check or to rank outputs from systems for text summarization,
natural language generation, or machine translation.
It could also be used in educational applications
such as essay scoring.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Much of the previous research
on predicting grammaticality has focused on identifying (and possibly correcting) specific types of grammatical errors
that are typically made by English language learners,
such as prepositions
        [19]
        , articles
        [11]
        , and collocations
        [7]
        .
While some applications (e.g., grammar checking) rely on such fine-grained predictions,
others might be better addressed by sentence-level grammaticality judgments (e.g., machine translation evaluation).
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Regarding sentence-level grammaticality, there has been much work on rating the grammaticality of machine translation outputs
        [10, 14]
        , such as the MT Quality Estimation Shared Tasks
        [2, §6]
        ,
but relatively little on
evaluating the grammaticality of naturally occurring text.
Also, most other research on evaluating grammaticality
involves
        artificial
        tasks or datasets
        [18, 13, 22, 16]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Here, we make the following contributions.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <ul class="ltx_itemize" id="I1">
        [itemsep=0em]
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           We develop a state-of-the-art approach for predicting the grammaticality of sentences on an ordinal scale, adapting various techniques from the previous work described above.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           We create a dataset of grammatical and ungrammatical sentences written by English language learners, labeled on an ordinal scale for grammaticality. With this unique data set, which we will release to the research community, it is now possible to conduct realistic evaluations for predicting sentence-level grammaticality.
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
       Dataset Description
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We created a dataset consisting of 3,129 sentences randomly selected from essays written by non-native speakers of English as part of a test of English language proficiency. We oversampled lower-scoring essays to increase the chances of finding ungrammatical sentences. Two of the authors of this paper, both native speakers of English with linguistic training, annotated the data. We refer to these annotators as expert judges. When making judgments of the sentences, they saw the previous sentence from the same essay as context. These two authors were not directly involved in development of the system in §
        3
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Each sentence was annotated on a scale from 1 to 4 as described below, with 4 being the most grammatical. We use an ordinal rather than binary scale, following previous work such as that of
        Clark et al. (2013)
        and
        Crocker and Keller (2005)
        who argue that the distinction between grammatical and ungrammatical is not simply binary. Also, for practical applications, we believe that it is useful to distinguish sentences with minor errors from those with major errors that may disrupt communication. Our annotation scheme was influenced by a translation rating scheme by
        Coughlin (2003)
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Every sentence judged on the 1–4 scale must be a clause. There is an extra category (“Other”) for sentences that do not fit this criterion. We exclude instances of “Other” in our experiments (see §
        4
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <dl class="ltx_description" id="I2">
        [leftmargin=*]
        <dt class="ltx_item" id="I2.ix1">
         <span class="ltx_tag ltx_tag_description">
          4. Perfect
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.ix1.p1">
          <p class="ltx_p">
           The sentence is native-sounding. It has no grammatical errors, but may contain very minor typographical and/or collocation errors, as in Example (
           1
           ).
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.i1">
         <span class="ltx_tag ltx_tag_description">
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           For instance, i stayed in a dorm when i went to collge.
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.ix2">
         <span class="ltx_tag ltx_tag_description">
          3. Comprehensible
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.ix2.p1">
          <p class="ltx_p">
           The sentence may contain one or more minor grammatical errors, including subject-verb agreement, determiner, and minor preposition errors that do not make the meaning unclear, as in Example (
           2
           ).
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.i2">
         <span class="ltx_tag ltx_tag_description">
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           We know during Spring Festival, Chinese family will have a abundand family banquet with family memebers.
          </p>
         </div>
         <div class="ltx_para" id="I2.i2.p2">
          <p class="ltx_p">
           “Chinese family”, which could be corrected to “Chinese families”, “each Chinese family”, etc., would be an example of a minor grammatical error involving determiners.
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.ix3">
         <span class="ltx_tag ltx_tag_description">
          2. Somewhat Comprehensible
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.ix3.p1">
          <p class="ltx_p">
           The sentence may contain one or more serious grammatical errors, including missing subject, verb, object, etc., verb tense errors, and serious preposition errors. Due to these errors, the sentence may have multiple plausible interpretations, as in Example (
           3
           ).
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.i3">
         <span class="ltx_tag ltx_tag_description">
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           I can gain the transportations such as buses and trains.
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.ix4">
         <span class="ltx_tag ltx_tag_description">
          1. Incomprehensible
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.ix4.p1">
          <p class="ltx_p">
           The sentence contains so many errors that it would be difficult to correct, as in Example (
           4
           ).
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.i4">
         <span class="ltx_tag ltx_tag_description">
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           Or you want to say he is only a little boy do not everything clearly? 

The phrase “do not everything” makes the sentence practically incomprehensible since the subject of “do” is not clear.
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.ix5">
         <span class="ltx_tag ltx_tag_description">
          O. Other/Incomplete
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.ix5.p1">
          <p class="ltx_p">
           This sentence is incomplete. These sentences, such as Example (
           5
           ), appear in our corpus due to the nature of timed tests.
          </p>
         </div>
        </dd>
        <dt class="ltx_item" id="I2.i5">
         <span class="ltx_tag ltx_tag_description">
         </span>
        </dt>
        <dd class="ltx_item">
         <div class="ltx_para" id="I2.i5.p1">
          <p class="ltx_p">
           The police officer handed the 

This sentence is cut off and does not at least include one clause.
          </p>
         </div>
        </dd>
       </dl>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        We measured interannotator agreement on a subset of 442 sentences that were independently annotated by both expert annotators. Exact agreement was 71.3%, unweighted
        κ=0.574
        , and Pearson’s
        r=0.759
        .
        For our experiments, one expert annotator was arbitrarily selected, and for the doubly-annotated sentences, only the judgments from that annotator were retained.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        The labels from the expert annotators are distributed as follows: 72 sentences are labeled 1; 538 are 2; 1,431 are 3; 978 are 4; and 110 are “O”.
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        We also gathered 5 additional judgments using Crowdflower.
        For this, we excluded the “Other” category and any sentences that had been marked as such by the expert annotators. We used 100 (3.2%) of the judged sentences as “gold” data
in Crowdflower to block contributors who were not following the annotation guidelines.
For those sentences, only disagreements within 1 point of the expert annotator judgment were accepted.
In preliminary experiments, averaging the six judgments (1 expert, 5 crowdsourced) for each item led to higher human-machine agreement.
For all experiments reported later, we used this average of six judgments as our gold standard.
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <p class="ltx_p">
        For our experiments (§
        4
        ), we randomly split the data into training (50%), development (25%), and testing (25%) sets.
We also excluded all instances labeled “Other”.
These are relatively uncommon and less interesting to this study.
Also, we believe that simpler, heuristic approaches could be used
to identify such sentences.
       </p>
      </div>
      <div class="ltx_para" id="S2.p9">
       <p class="ltx_p">
        We use “GUG” (“Grammatical” versus “UnGrammatical”) to refer to this dataset. The dataset is available for research at
        https://github.com/EducationalTestingService/gug-data
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       System Description
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        This section describes the statistical model (§
        3.1
        )
and features (§
        3.2
        ) used by our system.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Statistical Model
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We use
         ℓ2
         -regularized linear regression (i.e., ridge regression)
to learn a model of sentence grammaticality from a variety of linguistic features.
         <span class="ltx_note ltx_role_footnote">
          <sup class="ltx_note_mark">
           4
          </sup>
          <span class="ltx_note_outer">
           <span class="ltx_note_content">
            <sup class="ltx_note_mark">
             4
            </sup>
            Regression models typically produce conservative predictions
with lower variance than the original training data.
So that predictions better match the distribution of labels in the training data,
the system rescales its predictions.
It saves the mean and standard deviation
of the training data gold standard (
            <math alttext="M_{gold}" class="ltx_Math" display="inline" id="S3.SS1.p1.m2" xmlns="http://www.w3.org/1998/Math/MathML">
             <msub>
              <mi>
               M
              </mi>
              <mrow>
               <mi>
                g
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                o
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                l
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                d
               </mi>
              </mrow>
             </msub>
            </math>
            and
            <math alttext="SD_{gold}" class="ltx_Math" display="inline" id="S3.SS1.p1.m3" xmlns="http://www.w3.org/1998/Math/MathML">
             <mrow>
              <mi>
               S
              </mi>
              <mo>
               ⁢
              </mo>
              <msub>
               <mi>
                D
               </mi>
               <mrow>
                <mi>
                 g
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 o
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 l
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 d
                </mi>
               </mrow>
              </msub>
             </mrow>
            </math>
            , respectively)
and of its own predictions on the training data
(
            <math alttext="M_{pred}" class="ltx_Math" display="inline" id="S3.SS1.p1.m4" xmlns="http://www.w3.org/1998/Math/MathML">
             <msub>
              <mi>
               M
              </mi>
              <mrow>
               <mi>
                p
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                r
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                e
               </mi>
               <mo>
                ⁢
               </mo>
               <mi>
                d
               </mi>
              </mrow>
             </msub>
            </math>
            and
            <math alttext="SD_{pred}" class="ltx_Math" display="inline" id="S3.SS1.p1.m5" xmlns="http://www.w3.org/1998/Math/MathML">
             <mrow>
              <mi>
               S
              </mi>
              <mo>
               ⁢
              </mo>
              <msub>
               <mi>
                D
               </mi>
               <mrow>
                <mi>
                 p
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 r
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 e
                </mi>
                <mo>
                 ⁢
                </mo>
                <mi>
                 d
                </mi>
               </mrow>
              </msub>
             </mrow>
            </math>
            , respectively).
During cross-validation, this is done for each fold.
From an initial prediction
            <math alttext="\hat{y}" class="ltx_Math" display="inline" id="S3.SS1.p1.m6" xmlns="http://www.w3.org/1998/Math/MathML">
             <mover accent="true">
              <mi>
               y
              </mi>
              <mo stretchy="false">
               ^
              </mo>
             </mover>
            </math>
            , it produces the final prediction:
            <math alttext="\hat{y}^{\prime}=\frac{\hat{y}-M_{pred}}{SD_{pred}}*SD_{gold}+M_{gold}" class="ltx_Math" display="inline" id="S3.SS1.p1.m7" xmlns="http://www.w3.org/1998/Math/MathML">
             <mrow>
              <msup>
               <mover accent="true">
                <mi>
                 y
                </mi>
                <mo stretchy="false">
                 ^
                </mo>
               </mover>
               <mo>
                ′
               </mo>
              </msup>
              <mo>
               =
              </mo>
              <mrow>
               <mrow>
                <mrow>
                 <mfrac>
                  <mrow>
                   <mover accent="true">
                    <mi>
                     y
                    </mi>
                    <mo stretchy="false">
                     ^
                    </mo>
                   </mover>
                   <mo>
                    -
                   </mo>
                   <msub>
                    <mi>
                     M
                    </mi>
                    <mrow>
                     <mi>
                      p
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      r
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      e
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      d
                     </mi>
                    </mrow>
                   </msub>
                  </mrow>
                  <mrow>
                   <mi>
                    S
                   </mi>
                   <mo>
                    ⁢
                   </mo>
                   <msub>
                    <mi>
                     D
                    </mi>
                    <mrow>
                     <mi>
                      p
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      r
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      e
                     </mi>
                     <mo>
                      ⁢
                     </mo>
                     <mi>
                      d
                     </mi>
                    </mrow>
                   </msub>
                  </mrow>
                 </mfrac>
                 <mo>
                  *
                 </mo>
                 <mi>
                  S
                 </mi>
                </mrow>
                <mo>
                 ⁢
                </mo>
                <msub>
                 <mi>
                  D
                 </mi>
                 <mrow>
                  <mi>
                   g
                  </mi>
                  <mo>
                   ⁢
                  </mo>
                  <mi>
                   o
                  </mi>
                  <mo>
                   ⁢
                  </mo>
                  <mi>
                   l
                  </mi>
                  <mo>
                   ⁢
                  </mo>
                  <mi>
                   d
                  </mi>
                 </mrow>
                </msub>
               </mrow>
               <mo>
                +
               </mo>
               <msub>
                <mi>
                 M
                </mi>
                <mrow>
                 <mi>
                  g
                 </mi>
                 <mo>
                  ⁢
                 </mo>
                 <mi>
                  o
                 </mi>
                 <mo>
                  ⁢
                 </mo>
                 <mi>
                  l
                 </mi>
                 <mo>
                  ⁢
                 </mo>
                 <mi>
                  d
                 </mi>
                </mrow>
               </msub>
              </mrow>
             </mrow>
            </math>
            .
This transformation does not affect Pearson’s
            <math alttext="r" class="ltx_Math" display="inline" id="S3.SS1.p1.m8" xmlns="http://www.w3.org/1998/Math/MathML">
             <mi>
              r
             </mi>
            </math>
            correlations or rankings,
but it would affect binarized predictions.
           </span>
          </span>
         </span>
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         To tune the
         ℓ2
         -regularization hyperparameter
         α
         ,
the system performs 5-fold cross-validation on the data used for training.
The system evaluates
         α∈10{-4,…,4}
         and selects the one
that achieves the highest cross-validation correlation
         r
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Next, we describe the four types of features.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.1
         </span>
         Spelling Features
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS1.p1">
         <p class="ltx_p">
          Given a sentence with with
          n
          word tokens, the model filters out tokens containing nonalphabetic characters and then computes the number of misspelled words
          nm⁢i⁢s⁢s
          (later referred to as
          num_misspelled
          ), the proportion of misspelled words
          nm⁢i⁢s⁢sn
          , and
          log⁡(nm⁢i⁢s⁢s+1)
          as features. To identify misspellings, we use a freely available spelling dictionary for U.S. English.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.2
         </span>
         n
         -gram Count and Language Model Features
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS2.p1">
         <p class="ltx_p">
          Given each sentence, the model obtains the counts of
          n
          -grams (
          n=1⁢…⁢3
          ) from English Gigaword and computes the following features:
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS2.p2">
         <ul class="ltx_itemize" id="I3">
          [itemsep=0em]
          <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i1.p1">
            <p class="ltx_p">
             ∑s∈Snlog⁡(count⁢(s)+1)∥Sn∥
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i2.p1">
            <p class="ltx_p">
             maxs∈Sn⁡log⁡(count⁢(s)+1)
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I3.i3.p1">
            <p class="ltx_p">
             mins∈Sn⁡log⁡(count⁢(s)+1)
            </p>
           </div>
          </li>
         </ul>
         <p class="ltx_p">
          where
          Sn
          represents the
          n
          -grams of order
          n
          from the given sentence.
The model computes the following features from a
          5
          -gram language model trained on the same three sections of English Gigaword using the SRILM toolkit
          [17]
          :
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS2.p3">
         <ul class="ltx_itemize" id="I4">
          [itemsep=0em]
          <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I4.i1.p1">
            <p class="ltx_p">
             the average log-probability of the given sentence (referred to as
             gigaword_avglogprob
             later)
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I4.i2.p1">
            <p class="ltx_p">
             the number of out-of-vocabulary words in the sentence
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS2.p4">
         <p class="ltx_p">
          Finally, the system computes the average log-probability and number of out-of-vocabulary words from a language model trained on a collection of essays written by non-native English speakers
          (“non-native LM”).
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.3
         </span>
         Precision Grammar Features
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS3.p1">
         <p class="ltx_p">
          Following
          Wagner et al. (2007)
          and
          Wagner et al. (2009)
          , we use features extracted from precision grammar parsers. These grammars have been hand-crafted and designed to only provide complete syntactic analyses for grammatically correct sentences. This is in contrast to treebank-trained grammars, which will generally provide
          some
          analysis regardless of grammaticality. Here, we use (1) the Link Grammar Parser
          and (2) the HPSG English Resource Grammar
          [4]
          and PET parser.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS3.p2">
         <p class="ltx_p">
          We use a binary feature,
          complete_link
          , from the Link grammar that indicates whether at least one complete linkage can be found for a sentence. We also extract several features from the HPSG analyses.
          They mostly reflect information about unification success or failure and the associated costs. In each instance, we use the logarithm of one plus the frequency.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS4">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.4
         </span>
         PCFG Parsing Features
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS4.p1">
         <p class="ltx_p">
          We find phrase structure trees and basic dependencies with the Stanford Parser’s English PCFG model
          [12, 8]
          .
          We then compute the following:
         </p>
         <ul class="ltx_itemize" id="I5">
          [itemsep=0em]
          <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i1.p1">
            <p class="ltx_p">
             the parse score as provided by the Stanford PCFG Parser, normalized for sentence length, later referred to as
             parse_prob
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i2.p1">
            <p class="ltx_p">
             a binary feature that captures whether the top node of the tree is sentential or not (i.e. the assumption is that if the top node is non-sentential, then the sentence is a fragment)
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I5.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I5.i3.p1">
            <p class="ltx_p">
             features binning the number of
             dep
             relations returned by the dependency conversion. These
             dep
             relations are underspecified for function and indicate that the parser was unable to find a standard relation such as
             subj
             , possibly indicating a grammatical error.
            </p>
           </div>
          </li>
         </ul>
        </div>
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
        Next, we present evaluations on the GUG dataset.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Feature Ablation
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We conducted a feature ablation study to identify the contributions
of the different types of features described in §
         3.2
         .
We compared the performance of the full model with all of the features to
models with all but one type of feature. For this experiment,
all models were estimated
from the training set and evaluated on the development set.
We report performance
in terms of Pearson’s
         r
         between the averaged 1–4 human labels and unrounded system predictions.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         The results are shown in Table
         1
         .
From these results, the most useful features appear to be
the
         n
         -gram frequencies
from Gigaword and whether the link parser can fully parse the sentence.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Test Set Results
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         In this section, we present results on the held-out test set for the full model and various baselines, summarized in Table
         2
         .
For test set evaluations,
we trained on the combination of the training and development sets (§
         2
         ), to maximize the amount of training data for the final experiments.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         We also trained and evaluated on binarized versions of the ordinal GUG labels:
a sentence was labeled 1 if the average judgment was at least 3.5 (i.e., would round to 4), and 0 otherwise.
Evaluating on a binary scale allows us to measure how well the system
distinguishes grammatical sentences from ungrammatical ones.
For some applications, this two-way distinction may be more relevant than the more fine-grained 1–4 scale.
To train our system on binarized data, we replaced the
         ℓ2
         -regularized linear
regression model with an
         ℓ2
         -regularized logistic regression
and used Kendall’s
         τ
         rank correlation between the
predicted probabilities of the positive class
and the binary gold standard labels
as the grid search metric (§
         3.1
         )
instead of Pearson’s
         r
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         For the ordinal task, we report Pearson’s
         r
         between the averaged human judgments and each system.
For the binary task, we report percentage accuracy.
Since the predictions from the binary and ordinal systems are on different scales,
we include the nonparametric statistic Kendall’s
         τ
         as a secondary evaluation metric
for both tasks.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         We also evaluated the binary system for the ordinal task by computing correlations
between its estimated probabilities and the averaged human scores,
and we evaluated the ordinal system for the binary task
by binarizing its predictions.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         We compare our work to a modified version
of the publicly available
         system
from
         Post (2011)
         , which performed very well on an artificial dataset. To our knowledge, it is the only publicly available system for grammaticality prediction.
It is very different from our system since it
relies on partial tree-substitution grammar derivations as features.
We use the feature computation components of that system but replace its
statistical model.
The system was designed for use with a dataset
consisting of 50% grammatical and 50% ungrammatical sentences,
rather than data with ordinal or continuous labels.
Additionally, its classifier implementation does not output scores or probabilities.
Therefore, we used the same learning algorithms as for our system (i.e., ridge regression for the ordinal task
and logistic regression for the binary task).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         To create further baselines for comparison,
we selected the following
features that represent ways one might approximate grammaticality
if a comprehensive model was unavailable:
whether the link parser can fully parse the sentence (
         complete_link
         ),
the Gigaword language model score (
         gigaword_avglogprob
         ),
and the number of misspelled tokens (
         num_misspelled
         ).
Note that we expect the number of misspelled tokens to be negatively correlated
with grammaticality.
We flipped the sign of the misspelling feature when computing accuracy for the binary task.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p7">
        <p class="ltx_p">
         To identify whether the differences in performance for the ordinal task
between our system and each of the baselines are statistically significant,
we used the BC
         a
         Bootstrap
         [9]
         with 10,000 replications
to compute 95% confidence intervals
for the absolute value of
         r
         for our system minus
the absolute value of
         r
         for each of the alternative methods.
For the binary task, we used the sign test to test for significant differences in accuracy.
The results are in Table
         2
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
