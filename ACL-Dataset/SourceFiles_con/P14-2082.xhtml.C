<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   An Annotation Framework for Dense Event Ordering.
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
       Today’s event ordering research is heavily dependent on the annotated corpora available to it.
The corpora influence shared evaluations and drive algorithm development.
Partly due to this dependence, most research focuses on
       partial orderings
       of a document’s events.
For instance, the TempEval competitions and the TimeBank only annotate small portions of the event graph.
They focus on the most salient events or on specific types of event pairs (e.g., only events in the same sentence).
Deeper temporal reasoners struggle with this sparsity because the entire temporal picture is not represented.
This paper proposes a new annotation process with a unique mechanism to force annotators to label connected graphs.
It generates 10 times more relations per document than the TimeBank and the corpus is larger than all current corpora.
We hope this new annotation framework will encourage research on new models, particularly global models with deep reasoning.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       noitemsep,topsep=0.25em
       vskip=0.25em
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
        The TimeBank Corpus
        [6]
        helped usher in a wave of event ordering research with data-driven algorithms.
It provided for a common dataset of annotations between events and time expressions that allowed the community to compare approaches.
Since its creation, other corpora and several competitions have based their tasks on the TimeBank setup.
This paper addresses one of the shortcomings of the TimeBank: sparse annotation.
We describe a new annotation framework (and corpus) that we believe is required to fulfill the data needs of deeper temporal reasoners.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The TimeBank includes a small subset of all possible relations in its documents.
The original annotators were instructed to label relations critical to the document’s understanding.
The result is a sparse labeling that leaves much of the document unlabeled.
The TempEval contests have largely followed suit and focused on specific types of event pairs.
For instance, TempEval
        [8]
        only labeled relations between events that syntactically dominated each other.
This paper is the first attempt to annotate a document’s entire temporal graph.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        A consequence of focusing on all relations is a shift from the traditional temporal relation
        classification
        task, where the system is given a pair of events and asked only to label the type of temporal relation, to a temporal relation
        identification
        task, where the system must determine for itself which events in the document to pair up.
For example, in TempEval-1 and 2
        [8, 9]
        , systems were given event pairs in specific syntactic constructions: events and times in the same noun phrase, main events in consecutive sentences, etc.
In contrast, we aim for a shift in the community wherein all pairs are considered candidates for temporal ordering, allowing researchers to ask questions such as: how must algorithms adapt to label the complete graph of pairs, and if the more difficult and ambiguous event pairs are included, how must feature-based learners change?
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We are not the first to propose these questions, but this paper is the first to directly propose the means by which they can be addressed.
The stated goal of TempEval-3
        [7]
        was to focus on relation identification instead of classification, but the training and evaluation data followed the TimeBank approach where only a subset of event pairs were labeled.
As a result, many systems focused on classification, with the top system classifying pairs in only three syntactic constructions
        [2]
        .
We describe the first annotation framework that forces annotators to annotate all pairs
        .
With this new process, we created a dense ordering of document events that can properly evaluate both relation identification and relation annotation.
        fig:dense illustrates one document before and after our new annotations.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Previous Annotation Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The majority of corpora and competitions for event ordering contain sparse annotations.
Annotators for the original TimeBank
        [6]
        only annotated relations judged to be salient by the annotator.
Subsequent TempEval competitions
        [8, 9, 7]
        mostly relied on the TimeBank, but also aimed to improve coverage by annotating relations between all events and times
        in the same sentence
        .
However, event tokens that were mentioned fewer than 20 times were excluded and only one TempEval task considered relations between events in different sentences.
In practical terms, the resulting evaluations remained sparse.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        A major dilemma underlying these sparse tasks is that the unlabeled event/time pairs are ambiguous.
Each unlabeled pair holds two possibilities:
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           The annotator looked at the pair of events and decided that no temporal relation exists.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           The annotator did not look at the pair of events, so a relation may or may not exist.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        The training of temporal reasoners is hampered by this ambiguity.
In the worst case scenario, evaluation results are untrustworthy.
To combat this, our annotation adopts the
        vague
        relation, introduced by TempEval 2007, and our approach forces annotators to use it.
This is the only work that includes such a requirement.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Finally, this paper is not the first to look into more dense annotations.
Some research has explored annotation schemes that encourage annotators to connect all events to the timeline.
Bramsen et al.
        [3]
        annotated multi-sentence segments of text to build directed acyclic graphs, but the work didn’t focus on events.
Kolomiyets et al.
        [5]
        annotated “temporal dependency structures”, though they only focused on relations between pairs of events.
Most relevant to this paper is
        .
They have the densest annotation, but “the annotator was not required to annotate all pairs of event mentions, but as many as possible”.This paper takes a different tack to annotation by
        requiring
        annotators to label every possible pair of events/times in a given window.
Thus this work is the first annotation effort that can guarantee its event/time graph to be strongly connected.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        We compare the size and density of our corpus to current corpora in
        tab:relation-ratios.
Our corpus is the densest annotation, and contains the largest number of temporal relations to date.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       A Framework for Dense Annotation
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Frameworks for annotating text typically have two independent facets: (1) the practical means of how to label the text, and (2) the higher-level rules about when something should be labeled.
The first is often accomplished through a markup language.
TimeML is used for most temporal corpora, and this paper is no different.
The second facet is the focus of this paper:
        when
        should an annotator label an ordering relation?
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Our proposal thus starts with documents that have been already been annotated with events, time expressions, and document creation times (DCT).
The following example sentence serves as our motivating example:
        Police confirmed Friday that the body found along a highway in this municipality 15 miles south of San Juan belonged to Jorge Hernandez.
        This sentence is represented by a 4 node graph (3 events and 1 time).
Its complete graph requires 6 edges to connect all nodes, but as already discussed, few of our current datasets contain complete graphs.
This particular sentence is from the TimeBank, and 3 of the 6 edges are labeled.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The impact of these annotation decisions (i.e., when to annotate a relation) can be significant.
In this example, a learner must somehow deal with the 3 unlabeled edges.
One option is to assume that they are
        vague
        or ambiguous.
However, all 6 edges have clear well-defined ordering relations:
        belonged
        before
        confirmed
belonged
        before
        found
found
        before
        confirmed
belonged
        before
        Friday
confirmed
        is included in
        Friday
found
        is included in
        Friday
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Learning algorithms handle these unlabeled edges by making incorrect assumptions, or by ignoring large parts of the temporal graph.
Several models with rich temporal reasoners have been published, but since they require more connected graphs, improvement over pairwise classifiers have been minimal
        [4, 10]
        .
This paper thus proposes an annotation process that builds denser graphs with formal properties that learners can rely on, such as locally complete subgraphs.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Ensuring Dense Graphs
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         While the ideal goal is to create a complete graph, the time it would take to hand-label
         n⁢(n-1)/2
         edges is prohibitive.
We approximate completeness by creating locally complete graphs over neighboring sentences.
The resulting event graph for a document is strongly connected, but not complete.
Specifically, the following edge types are included:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <ol class="ltx_enumerate" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            Event-Event, Event-Time, and Time-Time pairs in the same sentence
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            Event-Event, Event-Time, and Time-Time pairs between the current and next sentence
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            Event-DCT pairs for every event in the text (DCT is the document creation time).
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           4.
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            Time-DCT pairs for every time expression in the text.
           </p>
          </div>
         </li>
        </ol>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Our process
         requires
         annotators to annotate all of the above edge types.
This is achieved through an annotation tool that prohibits the skipping of relations.
We describe the target relation set and this tool next.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.1
         </span>
         Temporal Relations
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS1.p1">
         <p class="ltx_p">
          The TimeBank corpus uses 14 relations based on the Allen interval relations.
The TempEval contests have used both a small set of relations (TempEval-1) and the larger set of 14 relations (TempEval-3).
Published work has mirrored this trend, and different groups focus on different aspects of the semantics.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS1.p2">
         <p class="ltx_p">
          We chose a middle ground between coarse and fine-grained distinctions for annotation, settling on 6 relations:
          before, after, includes, is included, simultaneous
          , and
          vague
          .
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS1.p3">
         <p class="ltx_p">
          The main reason for not using a more fine-grained set is because we annotate pairs that are far more ambiguous than those considered in previous efforts.
Decisions between relations like
          before
          and
          immediately before
          can complicate an already difficult task.
The added benefit of a corpus (or working system) that makes fine-grained distinctions is also not clear.
We lean toward higher annotator agreement with relations that have greater separation between their semantics
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.2
         </span>
         Enforcing Annotation
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS2.p1">
         <p class="ltx_p">
          Imposing the above rules on annotators requires automated assistance.
We built a new tool that reads TimeML formatted text, and computes the set of required edges.
Annotators are prompted to assign a label for each edge, and skipping edges is prohibited.
The tool is unique in that it includes a transitive reasoner that infers relations based on the annotator’s latest annotations.
For example, if event
          e1
          is included
          in
          t1
          , and
          t1
          before
          e2
          , the tool automatically labels
          e1
          before
          e2
          .
The transitivity inference is run after each input label, and the human annotator cannot override the inferences.
This prohibits the annotator from entering edges that break transitivity.
As a result, several properties are ensured through this process: the graph
(1) is a strongly connected graph, (2) is consistent with no contradictions, and (3) has all required edges labeled.
These 3 properties are new to all current ordering corpora.
The annotation tool will be publicly available.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Annotation Guidelines
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Since the annotation tool frees the annotators from the decision of
         when
         to label an edge, the focus is now
         what
         to label each edge.
This section describes the annotation guidelines for dense annotation.
         <span class="ltx_text ltx_font_bold">
          The 80% confidence rule
         </span>
         : Since the annotators are forced to label all required edges, the decision to label an edge as
         vague
         instead of a defined temporal relation is critical. We adopted an
         80⁢%
         rule that instructed annotators to choose a specific non-vague relation if they are 80% confident that it was the writer’s intent that a reader infer that relation.
By not requiring 100% confidence, we allow for alternative interpretations that conflict with the chosen edge label as long as that alternative is sufficiently unlikely.
In practice, annotators had different interpretations of what constitutes 80% certainty, and this generated much discussion. We mitigated these disagreements with the following rule.
         <span class="ltx_text ltx_font_bold">
          Majority annotator agreement
         </span>
         : An edge’s final label is the relation that received a majority of annotator votes, otherwise it is marked
         vague
         .
If a document has 2 annotators, both have to agree on the relation or it is labeled
         vague
         .
A document with 3 annotators requires 2 to agree, and 4 annotators require 3 to agree.
This agreement rule acts as a check to our 80% confidence rule, backing off to
         vague
         when decisions are uncertain (arguably, this is the definition of
         vague
         ).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         In addition to the above, we created other guidelines to encourage consistent labelings.
Several of these are inspired by Bethard and Martin
         [1]
         .
         <span class="ltx_text ltx_font_bold">
          Modal and conditional events
         </span>
         : interpreted with a
         possible worlds
         analysis.
The core event was treated as having occurred, whether or not the text implied that it had occurred.
For example,
         They [EVENT expect] him to [EVENT cut] costs throughout the organization.

This event pair is ordered (expect
         before
         cut) since the expectation occurs before the cutting (in the possible world where the cutting occurs).
Negated events and hypotheticals are treated similarly.
One assumes the event does occur, and all other events are ordered accordingly.
Negated states like “is not anticipating” are interpreted as though the anticipation occurs, and surrounding events are ordered with regard to its presumed temporal span.
         <span class="ltx_text ltx_font_bold">
          Aspectual Events
         </span>
         : annotated as
         is included
         in their event arguments.
For instance, events that describe the manner in which another event is performed are considered encompassed by the broader event.
Consider the following example:
         The move may [EVENT help] [EVENT prevent] Martin Ackerman from making a run at the computer-services concern.

This event pair is assigned the relation (help
         is included
         in prevent) because the help event is not meaningful on its own. It describes the proportion of the preventing accounted for by the move. In TimeBank, the
         intentional action
         class is used instead of the
         aspectual
         class in this case, but we still consider it covered by this guideline.
         <span class="ltx_text ltx_font_bold">
          Events that attribute a property
         </span>
         to a person or event are interpreted to end when the entity ends.
For instance, ‘the talk is nonsense’ evokes a nonsense event with an end point that coincides with the end of the talk.
         <span class="ltx_text ltx_font_bold">
          Time Expressions
         </span>
         : the words
         now
         and
         today
         were given “long now” interpretations if the words could be replaced with
         nowadays
         and not change the meaning of their sentences.
The time’s duration starts sometime in the past and
         includes
         the DCT.
If nowadays is not suitable, then the now was
         included in
         the DCT.
         <span class="ltx_text ltx_font_bold">
          Generic Events
         </span>
         : finally, generic events were not skipped. Annotators followed the guideline that generic events can be ordered with respect to each other, but
         vague
         with respect to nearby non-generic events.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       TimeBank-Dense: corpus statistics
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We chose a subset of TimeBank documents for our new annotation: TimeBank-Dense.
This provided a reliable labeling of events and time expressions.
Using the tool described above, we annotated 36 random documents with at least two annotators each to create a training set, development set, and test set.
These 36 documents led to an annotation of 4 times as many relations as the entire 183 document TimeBank.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The four authors of this paper were the four annotators.
All four authors annotated the same initial document, conflicts and disagreements were discussed, and guidelines were updated accordingly.
The rest of the documents were then annotated independently.
Document annotation was not random, but we mixed pairs of authors where time constraints allowed.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Final annotator agreement is shown in
        tab:agree.
Average agreement was 65.1% (not far from the TimeBank’s 71% agreement, which did not include the more difficult
        vague
        relation).
By far, the most significant disagreements pertained to choosing between the
        vague
        relation and a specific temporal relation.
Since there were only 2 annotators for most documents (and since we require the majority of annotators to agree), in general, the
        vague
        label was applied to the final graph if either annotator chose it.
This seems appropriate since a disagreement between two annotators directly implies that the relation is vague.
        tab:specific-agree breaks down the individual disagreements.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        tab:relcounts shows the individual relation counts in the final corpus.
The vague relation makes up 46% of the relations.
This is the first empirical count of how many temporal relations in news articles tend to be truly vague.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
