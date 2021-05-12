<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   The VerbCorner Project: Findings from Phase 1 of Crowd-Sourcing a Semantic Decomposition of Verbs.
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
       Any given verb can appear in some syntactic frames (
       Sally broke the vase
       ,
       The vase broke
       ) but not others (*
       Sally broke at the vase
       , *
       Sally broke the vase to John
       ). There is now considerable evidence that the syntactic behaviors of some verbs can be predicted by their meanings, and many current theories posit that this is true for most if not all verbs. If true, this fact would have striking implications for theories and models of language acquisition, as well as numerous applications in natural language processing. However, empirical investigations to date have focused on a small number of verbs. We report on early results from VerbCorner, a crowd-sourced project extending this work to a large, representative sample of English verbs.
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
        Verbs vary in terms of which syntactic frames they can appear in (Table 1). In principle, this could be an unpredictable fact about the verb that must be acquired, much like the phonological form of the verb.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        However, most theorists posit that there is a systematic relationship between the semantics of a verb and the syntactic frames in which it can appear
        [9]
        . For instance, it is argued that verbs like
        break
        , which describe a caused change of state, can appear in both the
        NP V NP
        form (
        Sally broke the vase
        ) and the
        NP V
        form (
        The vase broke
        ). Verbs such as
        hit
        and
        like
        do not describe a change of state and so cannot appear in both forms.
        Similarly, only verbs that describe propositional attitudes, such as
        like
        , can take a
        that
        complement (
        John liked that Sally broke the vase
        ).
       </p>
      </div>
      <div class="ltx_subsection" id="S1.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.1
        </span>
        The Semantic Consistency Hypothesis
       </h3>
       <div class="ltx_para" id="S1.SS1.p1">
        <p class="ltx_p">
         This account has a natural consequence, which we dub the Semantic Consistency Hypothesis: There is some set of semantic features such that verbs that share the same syntactic behavior are identical along those semantic features.
         Note that on certain accounts, this is a strong tendency rather than a strict necessity (e.g., Goldberg, 1995)
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p2">
        <p class="ltx_p">
         It is widely recognized that a principled relationship between syntax and semantics would have broad implications. It is frequently invoked in theories of language acquisition. For instance, Pinker (1984, 1989) has described how this correspondence could solve long-standing puzzles about how children learn syntax in the first place
         . Conversely, Gleitman (1990)
         has shown such a syntax-semantics relationship could solve significant problems in vocabulary acquisition. In fact, both researchers argue that a principled relationship between syntax and semantics is necessary for language to be learnable at all.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p3">
        <p class="ltx_p">
         In computational linguistics and natural language processing, some form of the Semantic Consistency Hypothesis is often included in linguistic resources and utilized in applications. We describe in detail one such resource, VerbNet, which is highly relevant to our investigation.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S1.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.2
        </span>
        VerbNet
       </h3>
       <div class="ltx_para" id="S1.SS2.p1">
        <p class="ltx_p">
         VerbNet (Kipper et al., 2008; based on Levin, 1993) lists over 6,000 verbs, categorized into 280 classes according to the syntactic frames they can appear in. That is, all verbs in the same class appear in the same set of syntactic frames. Importantly, in addition to characterizing the syntactic frames associated with each class, VerbNet also characterizes the semantics of each class.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p2">
        <p class="ltx_p">
         For instance, class 9.7, which comprises a couple dozen verbs, allows 7 different syntactic frames. The entry for one frame is shown below:
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p3">
        <p class="ltx_p">
         Syntactic Frame
         NP V NP PP.
         destination
         Example
         Jessica sprayed the wall.
         <span class="ltx_text ltx_font_bold">
          Syntax
         </span>
         Agent
         V
         Theme
         {+
         loc
         |+
         dest_conf
         }
         Destination
         <span class="ltx_text ltx_font_bold">
          Semantics
         </span>
         motion
         (
         during
         (E),
         Theme
         )
         <span class="ltx_text ltx_font_smallcaps">
          Not
         </span>
         (
         Prep
         (
         start
         (E),
         Theme
         ,
         Destination
         ))
         <span class="ltx_text ltx_font_smallcaps">
          Prep
         </span>
         (
         end
         (E),
         Theme
         ,
         Destination
         )
         <span class="ltx_text ltx_font_smallcaps">
          Cause
         </span>
         (
         Agent
         , E)
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p4">
        <p class="ltx_p">
         Importantly, the semantics listed here is not just for the verb
         spray
         but applies to all verbs from the Spray Class whenever they appear in that syntactic frame – that is, VerbNet assumes the Semantic Consistency Hypothesis.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p5">
        <p class="ltx_p">
         VerbNet and its semantic features have been used in a variety of NLP applications, such as semantic role labeling
         [18]
         , inferencing
         [20]
         , verb classification
         [8]
         , and information extraction
         [11]
         . It has also been employed in models of language acquisition
         [12, 2]
         . In general, there has been interest in the NLP literature in using these syntactially-relevant semantic features for shallow semantic parsing (e.g., Giuglea and Moschitti, 2006)
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Empirical Status of the Semantic Consistency Hypothesis
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Given the prominence of the Semantic Consistency Hypothesis in both theory and practice, one might expect that it was on firm empirical footing. That is, ideally there would be some database of semantic judgments for a comprehensive set of verbs from each syntactic class. In principle, these judgments would come from naive annotators, since researchers’ intuitions about subtle judgments may be unconsciously clouded by theoretical commitments
        [4]
        . The Semantic Consistency Hypothesis would be supported if, within that database, predicates with the same syntactic properties were systematically related semantically.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        No such database exists, whether consisting of the judgments of linguists or naive annotators. Most theoretical studies report researcher judgments for only a handful of examples; how many additional examples were considered by the researcher goes unreported. In any case, to our knowledge, of the 280 syntactic verb classes listed by VerbNet, only a handful have been studied in any detail.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The strongest evidence comes from experimental work on several so-called alternations (the passive, causative, locative, and dative alternations). Here, there does appear to be a systematic semantic distinction between the two syntactic frames in each alternation, at least most of the time. This has been tested with a reasonable sample of the relevant verbs and also in both children and adults
        [1, 15]
        . However, the relevant verbs make up a tiny fraction of all English verbs, and even for these verbs, the syntactic frames in question represent only a fraction of the syntactic frames available to those verbs.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        This is not an accidental oversight. The limiting factor is scale: with many thousands of verbs and over a hundred commonly-discussed semantic features and syntactic frames, it is not feasible for a single researcher, or even team of researchers, to check which verbs appear in which syntactic frames and carry which semantic entailments. Collecting data from naive subjects is even more laborious, particularly since the average Man on the Street is not necessarily equipped with metalinguistic concepts like
        caused change of state
        and
        propositional attitude
        .
The VerbCorner Project is aimed at filling that empirical gap.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       VerbCorner
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The VerbCorner Project
        is devoted to collecting semantic judgments for a comprehensive set of verbs along a comprehensive set of theoretically-relevant semantic dimension. These data can be used to test the Semantic Consistency Hypothesis. Independent of the validity of that hypothesis, the semantic judgments themselves should prove useful for any study of linguistic meaning or related application.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We address the issue of scale through crowd-sourcing: Recruiting large numbers of volunteers, each of whom may provide only a few annotations. Several previous projects have successfully crowd-sourced linguistic annotations, such as Phrase Detectives, where volunteers have contributed 2.5 million judgments on anaphoric relations
        [16]
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Integration with VerbNet
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         One significant challenge for any such project is first classifying verbs according to the syntactic frames they can appear in. Thus, at least initially, we are focusing on the 6,000+ verbs already cataloged in VerbNet. As such, the VerbCorner Project is also verifying and validating the semantics currently encoded in VerbNet. VerbNet will be edited as necessary based on the empirical results.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Integration with VerbNet has additional benefits, since VerbNet itself is integrated with a variety of linguistic resources, such as PropBank and Penn TreeBank. This amplifies the impact of any VerbCorner-inspired changes to VerbNet.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        The Tasks
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We selected semantic features of interest based on those most commonly cited in the linguistics literature, with a particular focus on those that – according to VerbNet – apply to many predicates.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Previous research has shown that humans find it easier to reason about real-world scenarios than make abstract judgments
         [3]
         . Thus, for each feature (e.g.,
         movement
         ), we converted the metalinguistic judgment (“Does this verb entail movement on the part of some entity?”) into a real-world problem.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         For example, in “Simon Says Freeze,” a task designed to elicit judgments about movement, the Galactic Overlord (Simon) decrees “Galactic Stay Where You Are Day,” during which nobody is allowed to move from their current location. Participants read descriptions of events and decide whether anyone violated the rule.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         In “Explode on Contact,” designed to elicit judgments about physical contact, objects and people explode when they touch one another. The participant reads descriptions of events and decides whether anything has exploded.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         Note that each task is designed to elicit judgments about entailments – things that must be true rather than are merely likely to be true. If John greeted Bill, they might have come into contact (e.g., by shaking hands), but perhaps they did not. Previous work suggests that it is the semantic
         entailments
         that matter, particularly for explaining the syntactic behavior of verbs
         [10]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        The Items
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         The exact semantics associated with a verb may depend on its syntactic frame. Thus
         Sally rolled the ball
         entails that somebody applied force to the ball (namely: Sally), whereas
         The ball rolled
         does not. Thus, we investigate the semantics of each verb in each syntactic frame available to it (as described by VerbNet). Below, the term
         item
         is the unit of annotation: a verb in a frame.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         In order to minimize unwanted effects of world knowledge, the verb’s arguments are replaced with nonsense words or randomly chosen proper names (
         Sally sprayed the dax onto the blicket
         ). The use of novel words is explained by the story for each task.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        The Phases
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Given the sheer scale of the project, data-collection is expected to take several years at least. Thus, data-collection has been broken up into a series of phases. Each phase focuses on a small number of classes and/or semantic entailments. This ensures that there are meaningful intermediate results that can be disseminated prior to the completion of the entire project. This manuscript reports the results of Phase 1.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The full data and annotations will be released in the near future and may be available now by request. Below, we summarize the main findings thus far.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Description of Phase 1
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         In Phase 1 of the project, we focused on 11 verb classes (Table 3) comprising 641 verbs and seven different semantic entailments (Table 2). While six of these entailments were chosen from among those features widely believed to be relevant for syntax, one was not: A Good World, which investigated evaluation (
         Is the event described by the verb positive or negative?
         ). Although evaluation of events is an important component of human psychology, to our knowledge no researcher has suggested that it is relevant for syntax. As such, this task provides a lower bound for how much semantic consistency one might expect within a syntactic verb class.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         In all, we collected 162,564 judgments from 1,983 volunteers (Table 2).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Inter-annotator Agreement
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Each task had been iteratively piloted and redesigned until inter-annotator reliability was acceptable, as described in a previous publication. However, these pilot studies involved a small number of items which were coded by all annotators. How good was the reliability in the crowd-sourcing context?
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Because we recruited large numbers of annotators, most of whom annotated only a few items, typical measures of inter-annotator agreement such as Cohen’s
         kappa
         are not easily calculated. Instead, for each item, we calculated the most common (modal) response. We then considered what proportion of all annotations were accounted for by the modal response: a mean of 100% would indicate that there was no disagreement among annotators for any item.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         As can be seen in Table 2, for every task, the modal response covered the bulk responses, ranging from a low of 72% for
         Evaluation
         to a high of 93% for
         Physical Contact
         . Since there were typically 4 or more possible answers per item, inter-annotator agreement was well above chance. This represents good performance given that the annotators were entirely untrained.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         In many cases, annotator disagreement seems to be driven by syntactic constructions that are only marginally grammatical. For instance, inter-annotator agreement was typically low for class 63. VerbNet suggests two syntactic frames for class 63, one of which (
         NP V that S
         ) appears to be marginal (?
         I control that Mary eats
         ). In fact, annotators frequently flagged these items as ungrammatical, which is a valuable result in itself for improving VerbNet.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Testing the Semantic Consistency Hypothesis
       </h3>
       <div class="ltx_subsubsection" id="S4.SS3.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.1
         </span>
         Calculating consistency
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS1.p1">
         <p class="ltx_p">
          We next investigated whether our results support the Semantic Consistency Hypothesis. As noted above, the question is not whether all verbs in the same syntactic class share the same semantic entailments. Even a single verb may have different semantic entailments when placed in different syntactic frames. Thus, calculating consistency of a
          class
          must take differing
          frames
          into account.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p2">
         <p class="ltx_p">
          There are many sophisticated rubrics for calculating consistency. However, for expository purposes here, we use one that is intuitive and easy to interpret. First, we determined the annotation for each item (i.e., each verb/frame combination) by majority vote. We then considered how many verbs in each class had the same annotation in any given syntactic frame.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p3">
         <p class="ltx_p">
          For example, suppose a class had 10 verbs and 2 frames. In the first frame, 8 verbs received the same annotation and 2 received others. The consistency for this class/frame combination is 80%. In the second frame, 6 verbs received the same annotation and 4 verbs received others. The consistency for this class/frame combination is 60%. The consistency for the class as a whole is the average across frames: 70%.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.2
         </span>
         Results
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS2.p1">
         <p class="ltx_p">
          Mean consistency averaged across classes is shown for each task in Table 2. As expected, consistency was lowest for
          Evaluation
          , which is not expected to necessarily correlate with syntax. Interestingly, consistency for
          Evaluation
          was nonetheless well above floor. This is perhaps not surprising: two sentences that have the same values for
          Physical Change, Application of Force, Physical Contact, Change of Mental State, Mental State
          , and
          Location Change
          are, on average, also likely to be both good or both bad.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS2.p2">
         <p class="ltx_p">
          Consistency was much higher for the other tasks, and in fact was close to ceiling for most of them. It remains to be seen whether the items that deviate from the mode represent true differences in semantics or reflect merely noise. One way of addressing this question is to collect additional annotations for those items that deviate from the mode.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Verb semantics
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         For each syntactic frame in each class, we determined the most common annotation. This is summarized in Table 3. The semantic annotation depended on syntactic frame nearly 1/4 of the time.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p2">
        <p class="ltx_p">
         These frequently matched VerbNet’s semantics, though not always. For instance, annotators judged that class 18.1 verbs in the
         NP V NP PP.instrument
         entailed movement on the part of the instrument (
         Sally hit the ball with the stick
         ) – something not reflected in VerbNet.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
