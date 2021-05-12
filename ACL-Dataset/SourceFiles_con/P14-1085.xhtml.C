<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Hierarchical Summarization: Scaling Up
Multi-Document Summarization.
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
       Multi-document summarization (MDS) systems have been designed for
short, unstructured summaries of 10-15
documents, and are inadequate for larger document collections.
We propose a new approach to scaling up summarization called
       hierarchical summarization
       ,
and present the first implemented system,
       Summa
       .
      </p>
      <p class="ltx_p">
       Summa
       produces a hierarchy of relatively short summaries,
in which the top level provides a general overview and users can
navigate the hierarchy to drill down for more details on topics
of interest.
       Summa
       optimizes for coherence as well as coverage
of salient information. In an Amazon Mechanical Turk evaluation,
users prefered
       Summa
       ten times as often as flat MDS and three
times as often as timelines.
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
        The explosion in the number of documents on the Web necessitates
automated approaches that organize and summarize large document
collections on a complex topic.
Existing methods for multi-document summarization (MDS) are
designed to produce short summaries of 10-15 documents.
        MDS systems do not scale to data sets ten times larger and proportionately
longer summaries: they either cannot run on large input
or produce a disorganized summary that is difficult to understand.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        We present a novel MDS paradigm,
        hierarchical
summarization
        , which operates on large document collections,
creating summaries that organize the information coherently.
It mimics how someone with a general interest in a
complex topic would learn about it from an expert – first, the expert
would provide an overview, and then more specific information about various
aspects. Hierarchical summarization has the following novel characteristics:
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
           The summary is hierarchically organized
along one or more organizational principles such as time, location,
entities, or events.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Each non-leaf summary is associated with a
set of child summaries where each gives details of an
element (e.g. sentence) in the parent summary.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           A user can navigate within the hierarchical summary
by clicking on an element of a parent summary to view the
associated child summary.
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        For example, given the topic, “1998 embassy bombings,” the first summary
(Figure
        1
        ) might mention that the US retaliated by
striking Afghanistan and Sudan. The user can click on this information to
learn more about these attacks. In this way, the system can present large
amounts of information without overwhelming the user, and the user can
tailor the output to their interests.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In this paper, we describe
        Summa
        , the first hierarchical summarization
system for multi-document summarization.
        It operates on a corpus
of related news articles.
        Summa
        hierarchically clusters the sentences by time, and then summarizes
the clusters using an objective function that optimizes salience and coherence.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We conducted an Amazon Mechanical Turk (AMT) evaluation where
AMT workers compared the output of
        Summa
        to that of timelines
and flat summaries.
        Summa
        output was judged superior more
than three times as often as timelines,
and users learned more in twice as many cases. Users overwhelmingly
preferred hierarchical summaries to flat summaries (92%) and learned
just as much.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Our main contributions are as follows:
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           We introduce and formalize the novel task of
hierarchical summarization.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           We present
           Summa
           , the first hierarchical summarization
system, which operates on news corpora and summarizes over an order
of magnitude more documents than traditional MDS systems, producing summaries
an order of magnitude larger.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           We present a user study which demonstrates
the value of hierarchical summarization over timelines
and flat multi-document summaries in learning about a
complex topic.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        In the next section, we formalize hierarchical summarization.
We then describe our methodology to implement the
        Summa
        hierarchical summarization system: hierarchical clustering in
Section
        3
        and creating summaries based on that
clustering in Section
        4
        .
We discuss our experiments in Section
        5
        ,
related work in Section
        6
        , and conclusions
in Section
        7
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Hierarchical Summarization
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We propose a new task for large-scale summarization
called
        hierarchical summarization
        .
Input to a hierarchical summarization system is a set of related documents
        D
        and a budget
        b
        for each summary within the hierarchy (in bytes,
words, or sentences). The output is the
hierarchical summary
        H
        , which we define formally as follows.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        A
        hierarchical summary
        H
        of a document collection
        D
        is a set of summaries
        X
        organized into a hierarchy.
The top of the hierarchy is a summary
        X1
        representing
all of
        D
        , and each summary
        Xi
        consists of summary
units
        xi,j
        (
        e.g.
        the
        j
        th sentence of summary
        i
        ) that
point to a child summary, except at the leaf nodes of the hierarchy.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        A child summary adds more detail to the information in its
parent summary unit. The child summary may include sub-events or
background and reactions to the event or topic in the parent.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        We define several metrics in Section
        4
        for a well-constructed hierarchical summary. Each summary should
maximize coverage of
        salient
        information; it should minimize
        redundancy
        ; and it should have
        intra-cluster coherence
        as well as
        parent-to-child coherence
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Hierarchical summarization has two important strengths in the context of
large-scale summarization.
First, the information presented at the start is small and grows only
as the user directs it, so as not to overwhelm the user.
Second, each user directs his or her own experience, so a user interested
in one aspect need only explore that section of the data without having to
view or understand the entire summary. The parent-to-child
links provide a means for
a user to navigate, drilling down for more details on topics
of interest.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        There are several possible organizing principles for the hierarchy –
by date, by entities, by locations, or by events.
Some organizing principles will fit the data in a document collection better
than others. A system may select different organization for different
portions of the hierarchy, for example, organizing first by location or
prominent entity and then by date for the next level.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Hierarchical Clustering
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Having defined the task, we now describe the methodology behind our
implementation,
        Summa
        .
In future work we intend to design a system that dynamically selects
the best organizing principle for each level of the hierarchy. In this
first implementation, we have opted for temporal organization, since this
is generally the most appropriate for news events.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The problem of hierarchical summarization as described in Section
        2
        has all of the requirements of MDS, and additional
complexities of inducing a hierarchical structure, processing an order of
magnitude bigger input, generating a much larger output, and enforcing
coherence between parent and child summaries.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        We simplify the problem by decomposing it into two steps:
hierarchical clustering and summarizing over the clustering
(see Figure
        2
        for an example).
A hierarchical clustering is a tree in which if a cluster
        gp
        is the parent of cluster
        gc
        , then each sentence in
        gc
        is also in
        gp
        . This organizes the information into manageable,
semantically-related sections and induces a hierarchical structure over
the input.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The hierarchical clustering serves as input to the second step
– summarizing given the hierarchy. The hierarchical summary follows the
hierarchical structure of the clustering. Each node in the hierarchy has an
associated flat summary, which summarizes the sentences in that cluster.
Moreover, the number of sentences in a flat summary is exactly equal to
the number of child clusters of the node, since the user will click a
sentence to get to the child summary. See Figure
        2
        for
an illustration of this correspondence.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Because we are interested in
        temporal
        hierarchical summarization,
we hierarchically cluster all the sentences in the input documents by
time. Unfortunately, neither agglomerative nor divisive clustering is
suitable, since both assume a binary split at each node
        [2]
        . The
number of clusters at each split should be what is most natural for the
input data. We design a recursive clustering algorithm
that automatically chooses the appropriate number of clusters at each
split.
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        Before clustering, we timestamp all sentences. We
use SUTime
        [6]
        to normalize temporal references, and
we parse the sentences with the Stanford parser
        [13]
        and use a set of
simple heuristics to determine if the timestamps in the sentence refer to
the root verb.

If no timestamp is given, we use the article date.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Temporal Clustering
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         After acquiring the timestamps, we must hierarchically cluster the
sentences into sets that make sense to summarize together.

Since we wish to partition along the temporal dimension, our problem
reduces to identifying the best dates at which to split a cluster into
subclusters. We identify these dates by looking for bursts of activity.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         News tends to be
         bursty
         – many articles on a topic appear at
once and then taper out
         [14]
         .
For example, Figure
         3
         shows the number of articles
per day related to the 1998 embassy bombings published in the New York Times
(identified using a key word search). There
were two main events – on the 7th, the embassies were bombed and on the
20th, the US retaliated through missile strikes. The figure shows a
correspondence between these events and news spikes.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Ideal splits for this example would occur just before each spike in
coverage. However, when there is little differentiation in news coverage,
we prefer clusters evenly spaced across time. We thus choose
clusters
         C={c1,…,ck}
         as follows:
        </p>
        <table class="ltx_equationgroup" id="S3.E1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E1X">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td">
          </td>
          <td class="ltx_td ltx_align_left">
           maximize𝐶
          </td>
          <td class="ltx_td">
          </td>
          <td class="ltx_td ltx_align_left">
           B⁢(C)+α⁢E⁢(C)
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
         C
         is a clustering,
         B⁢(C)
         is the burstiness of the
set of clusters,
         E⁢(C)
         is the evenness
of the clusters, and
         α
         is the tradeoff parameter.
        </p>
        B⁢(C)=∑c∈Cb⁢u⁢r⁢s⁢t⁢(c)

(2)
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         b⁢u⁢r⁢s⁢t⁢(c)
         is the difference in the number of sentences
published the day before the first date in
         c
         and the average number
of sentences published on the first and second date of
         c
         :
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        b⁢u⁢r⁢s⁢t⁢(c)=p⁢u⁢b⁢(di)+p⁢u⁢b⁢(di+1)2-p⁢u⁢b⁢(di-1)

(3)
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         where
         d
         is a date indexed over time,
such that
         dj
         is a day before
         dj+1
         , and
         di
         is the first date in
         c
         .
         p⁢u⁢b⁢(di)
         is the number of sentences published on
         di
         .
The evenness of the split is measured by:
        </p>
        E⁢(C)=minc∈C⁡s⁢i⁢z⁢e⁢(c)

(4)
       </div>
       <div class="ltx_para" id="S3.SS1.p7">
        <p class="ltx_p">
         where
         s⁢i⁢z⁢e⁢(c)
         is the number of dates in cluster
         c
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p8">
        <p class="ltx_p">
         We perform hierarchical clustering top-down, at
each point solving for Equation
         1
         .
         α
         was set
using a grid-search over a development set.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Choosing the number of clusters
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We cannot know
         a priori
         the number of clusters for a
given topic. However, when the number of clusters is too large for the
given summary budget, the sentences will have to be too short, and when the
number of clusters is too small, we will not use enough of the budget.
We set the maximum number of clusters
         km⁢a⁢x
         and minimum number of
clusters
         km⁢i⁢n
         to be a function of the budget
         b
         and the average
sentence length in the cluster
         sa⁢v⁢g
         , such that
         km⁢a⁢x⋅sa⁢v⁢g≤b
         and
         km⁢i⁢n⋅sa⁢v⁢g≥b/2
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Given a maximum and minimum number of clusters, we must determine the
appropriate number of clusters. At each level, we cluster the
sentences by the method described above and choose the number of clusters
         k
         according to the gap statistic
         [30]
         .
Specifically, for each level, the algorithm will cluster repeatedly with
         k
         varying from the minimum to the maximum. The algorithm will
return the
         k
         that maximizes the gap statistic:
        </p>
        G⁢a⁢pn⁢(k)=En∗⁢{log⁡(Wk)}-l⁢o⁢g⁢(Wk)

(5)
        <p class="ltx_p">
         where
         Wk
         is the score for the clusters computed with Equation
         1
         , and
         En∗
         is the expectation under a sample of size
         n
         from a reference distribution.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Ideally, the maximum depth of the clustering would be a function of the number of
sentences in each cluster, but in our implementation, we set the maximum
depth to three, which
works well for the size of the datasets we use (300 articles).
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Summarizing within the Hierarchy
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        After the sentences are clustered, we have a structure for the
hierarchical summary that dictates the number of summaries and the
number of sentences in each summary. We also have the set of sentences from
which each summary is drawn.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Intuitively, each cluster summary in the hierarchical summary
should convey the most
        salient
        information in that cluster. Furthermore, the hierarchical summary should
not include
        redundant
        sentences.
A hierarchical summary that is only salient and nonredundant may still not
be suitable if the sentences within a cluster
summary are disconnected or if the parent sentence for a
summary does not relate to the child summary. Thus, a hierarchical summary
must also have
        intra-cluster coherence
        and
        parent-to-child
coherence
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Salience
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Salience is the value of each sentence to the topic from which the
documents are drawn. We measure salience of a summary (
         S⁢a⁢l⁢(X)
         ) as the
sum of the saliences of individual sentences (
         ∑iS⁢a⁢l⁢(xi)
         ).
Following previous research in MDS, we computed individual saliences
using a linear regression classifier trained on ROUGE scores over the DUC’03
dataset
         [18, 8]
         . This method finds those sentences
more salient that mention nouns or verbs that occur frequently in the cluster.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         In preliminary experiments, we noticed that many sentences that were
         reaction
         sentences were given a higher salience than
         action
         sentences. For example, the reaction sentence, “President Clinton vowed
to track down the perpetrators behind the bombs that exploded outside the
embassies in Tanzania and Kenya on Friday,” would have a higher score
than the
         action
         sentence, “Bombs exploded outside the embassies in
Tanzania and Kenya on Friday.” This problem occurs because the first
sentence has a higher ROUGE score (it covers more important words than the
second sentence). To adjust for this problem, we use only words identified
in the main clause (heuristically identified via the parse tree) to compute our salience scores.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Redundancy
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We identify redundant sentences using a linear regression classifier
trained on a manually labeled subset of the DUC’03 sentences. The features
include shared noun counts, sentence length, TF*IDF cosine similarity,
timestamp difference, and features drawn from information extraction such
as number of shared tuples in Open IE
         [20]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Summary Coherence
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We require two types of coherence:
coherence between the parent and child summaries and coherence
within each summary
         Xi
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         We rely on the approximate discourse graph (ADG) that was
proposed in
         [8]
         as the basis for measuring
coherence. Each node in the ADG is a sentence from the dataset. An edge
from sentence
         si
         to
         sj
         with positive weight indicates that
         sj
         may
follow
         si
         in a coherent summary,
         e.g.
         continued mention of an event
or entity, or coreference link between
         si
         and
         sj
         .
A negative edge indicates an unfulfilled discourse cue or co-reference
mention.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         Parent-to-Child Coherence:
         Users navigate the hierarchical summary from parent sentence to child
summary, so if the parent sentence bears no relation to the child summary,
the user will be understandably confused.
The parent sentence must have positive evidence of coherence with the
sentences in its child summary.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p4">
        <p class="ltx_p">
         We estimate parent to child coherence as the coherence between a parent
sentence and each sentence in its child summary as:
        </p>
        PCoh(X)=∑c∈C∑i=1..⁢|Xc|wG+(xcp,xc,i))

(6)
        <p class="ltx_p">
         where
         xcp
         is the parent sentence for cluster
         c
         and
         wG+⁢(xcp,xc,i)
         is the sum of the positive
edge weights from
         xcp
         to
         xc,i
         in the ADG
         G
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p5">
        <p class="ltx_p">
         Intra-cluster Coherence:
         In traditional MDS, the documents are usually
quite focused, allowing for highly focused summaries. In hierarchical
summarization, however, a cluster summary may span hundreds of documents
and a wide range of information.
For this reason, we may consider a summary acceptable
even if it has limited positive evidence of coherence in the
ADG, as long as there is no negative evidence in the form of negative
edges.
For example, the following is a reasonable summary for events spanning
two weeks:
         <math alttext="s_{1}" class="ltx_Math" display="inline" id="S4.SS3.p5.m1" xmlns="http://www.w3.org/1998/Math/MathML">
          <msub>
           <mi>
            s
           </mi>
           <mn>
            1
           </mn>
          </msub>
         </math>
         Bombs exploded at two US embassies.
         <math alttext="s_{2}" class="ltx_Math" display="inline" id="S4.SS3.p5.m2" xmlns="http://www.w3.org/1998/Math/MathML">
          <msub>
           <mi>
            s
           </mi>
           <mn>
            2
           </mn>
          </msub>
         </math>
         US missiles struck in Afghanistan and Sudan.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p6">
        <p class="ltx_p">
         Our measure of intra-cluster coherence minimizes the number of
         missing references
         . These are coreference mentions or discourse
cues where none of the sentences read before (either in an ancestor
summary or in the current summary) contain an antecedent:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p7">
        C⁢C⁢o⁢h⁢(X)=-∑c∈C∑i=1..⁢|Xc|#⁢m⁢i⁢s⁢s⁢i⁢n⁢g⁢R⁢e⁢f⁢(xc,i)

(7)
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Objective Function
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         Having estimated salience, redundancy, and two forms of coherence,
we can now put this information together into a single objective function
that measures the quality of a candidate hierarchical summary.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p2">
        <p class="ltx_p">
         Intuitively, the objective function should
balance salience and coherence. Furthermore, the summary should not
contain redundant
information and each cluster summary should honor the given budget, i.e.,
maximum summary length
         b
         . We treat redundancy and budget as hard
constraints and coherence and salience as soft constraints. Lastly, we
require that sentences are drawn from the cluster that they represent and

that the number of sentences in the summary
corresponding to each non-leaf cluster
         c
         is equivalent to the number of child clusters of
         c
         . We optimize:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p3">
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S4.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           maximize:
          </td>
          <td class="ltx_td ltx_align_center">
           F⁢(x)≜S⁢a⁢l⁢(X)+β⁢P⁢C⁢o⁢h⁢(X)+γ⁢C⁢C⁢o⁢h⁢(X)
          </td>
          <td class="ltx_td">
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S4.Ex5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           s.t.
          </td>
          <td class="ltx_td ltx_align_center">
           ∀c∈C:∑i=1..⁢|Xc|l⁢e⁢n⁢(xc,i)&lt;b
          </td>
          <td class="ltx_td">
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
           ∀xi,xj∈X:redundant⁢(xi,xj)=0
          </td>
          <td class="ltx_td">
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
           ∀c∈C,∀xc∈Xc:xc∈c
          </td>
          <td class="ltx_td">
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
           ∀c∈C:|Xc|=#⁢c⁢h⁢i⁢l⁢d⁢r⁢e⁢n⁢(c)
          </td>
          <td class="ltx_td">
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S4.SS4.p4">
        <p class="ltx_p">
         The tradeoff parameters
         β
         and
         γ
         were set based on a development set.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.5
        </span>
        Algorithm
       </h3>
       <div class="ltx_para" id="S4.SS5.p1">
        <p class="ltx_p">
         Optimizing this objective function is NP-hard, so we approximate a
solution by using beam search over the space of partial hierarchical
summaries. Notice the contribution from a sentence depends on
individual salience, coherence (
         C⁢C⁢o⁢h
         ) based on sentences visible on the user
path down the hierarchy to this sentence, and coherence (
         P⁢C⁢o⁢h
         ) based on its
parent sentence and its child summary. Since most of the
sentence contributions depend on the path from the root to the sentence, we build our
partial summary by incrementally adding a sentence top-down in the
hierarchy and from first sentence to last within a cluster summary.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS5.p2">
        <p class="ltx_p">
         To account for
         P⁢C⁢o⁢h
         ,
we estimate the contribution of the sentence
by jointly identifying its best child summary. However, we do not fix the
child summary at this time – we simply use it to estimate
         P⁢C⁢o⁢h
         when
using that sentence. Since computing the best child summary is
also intractable we approximate a solution by a local search algorithm over the
child cluster.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS5.p3">
        <p class="ltx_p">
         Overall, our algorithm is a two level nested search algorithm – beam
search in the outer loop to search through the space of partial summaries
and local search (hill climbing with random restarts) in the inner loop to
pick the best sentence to add to the existing partial summary. We use a
beam of size ten in our implementation.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Our experiments are designed to evaluate how effective hierarchical
summarization is in summarizing a large, complex topic and how well this
helps users learn about the topic.
Our evaluation addresses the following questions:
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <ul class="ltx_itemize" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           Do users prefer hierarchical summaries
for topic exploration? (Section
           5.1
           )
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           Are hierarchical summaries more effective than other
methods for learning about complex events? (Section
           5.2
           )
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           How informative are the hierarchical summaries compared to the other
methods? (Section
           5.3
           )
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i4.p1">
          <p class="ltx_p">
           How coherent is the hierarchical structure in the summaries? (Section
           5.4
           )
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        We compared
        Summa
        against two baseline systems which represent the main
NLP methods for large-scale summarization: an algorithm for creating
timelines over sentences
        [7]
        ,
        and a state-of-the-art flat MDS system
        [19]
        .
        Each system was given the same budget (over 10 times the traditional MDS budget,
which is 665 bytes).
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        We evaluated the questions on ten news topics, representing a range of tasks: (1) Pope
John Paul II’s death and the 2005 Papal Conclave, (2) Bush v. Gore,
(3) the Tulip Revolution, (4) Daniel Pearl’s kidnapping, (5) the Lockerbie bombing handover
of suspects,
(6) the Kargil War, (7) NATO’s bombing of Yugoslavia in 1999, (8) Pinochet’s arrest in
London, (9) the 2005 London bombings, and (10) the crash and investigation of SwissAir
Flight 111. We chose topics
containing a set of related events that unfolded
over several months and were prominent enough to
be reported in at least 300 articles.
       </p>
      </div>
      <div class="ltx_para" id="S5.p5">
       <p class="ltx_p">
        We drew our articles from the
Gigaword corpus, which contains articles from the New York Times and other
major newspapers. For each topic, we used the 300 documents that best
matched a key word search. We selected topics which were between five and
fifteen years old so that evaluators would have relatively less
pre-existing knowledge about the topic.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        User Preference
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         In our first experiment, we simply wished to evaluate which system users most prefer.
We hired Amazon Mechanical Turk (AMT) workers and assigned two topics to
each worker. We paired up workers such that one worker would see output
from
         Summa
         for the first topic and a competing system for the second and
the other worker would see the reverse. For quality control, we asked workers to
complete a qualification task first, in which they were required to write
a short summary of a news article. We also manually removed spam from our
results.
Previous work has used AMT workers for summary evaluations and has shown high
correlations with expert ratings
         [8]
         .
Five workers were hired to view each topic-system pair.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         We asked the workers to choose which format they preferred and to explain why.
The results are as follows:
        </p>
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_left ltx_border_t">
            Summa
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            76%
           </td>
           <th class="ltx_td ltx_align_left ltx_border_t">
            Timeline
           </th>
           <td class="ltx_td ltx_align_center ltx_border_t">
            24%
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_left ltx_border_bb ltx_border_t">
            Summa
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            92%
           </td>
           <th class="ltx_td ltx_align_left ltx_border_bb ltx_border_t">
            Flat-MDS
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_t">
            8%
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         Users preferred the hierarchical summaries three times more often than
timelines and over ten times more often than flat summaries. When we
examined the reasons given by the users, we found that the people who
preferred the hierarchical summaries liked that they gave a big picture
overview and were then allowed to drill down deeper. Some also explained
that it was easier to remember information when presented with the
overview first. Typical responses included, “Could
gather and absorb the information at my own pace,” and, “Easier to follow
and understand.” When users preferred the timelines,
they usually remarked that it was more familiar, i.e. “I liked the familiarity of the format. I am used to these timelines
and they feel comfortable.”
Users complained that the
flat summaries were disjointed, confusing, and very frustrating to read.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Knowledge Acquisition
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         Evaluating how much a user learned is inherently
difficult, more so when the goal is to allow the user the freedom to
explore information based on individual interest. For this reason,
instead of asking a set of predefined questions, we assess the knowledge
gain by following the methodology of
         [26]
         – asking users
to write a paragraph summarizing the information learned.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Using the same setup as in the previous experiment, for each topic,
five AMT workers spent three minutes reading through a timeline or summary
and were then asked to write a description of what they had learned.
Workers were not allowed to see the timeline or summary while writing.
We collected five descriptions for each topic-system combination. We then
asked other AMT workers to read and compare the descriptions written by the first set
of workers. Each evaluator was presented with a corresponding Wikipedia
article and descriptions from a pair of users (timeline vs.
         Summa
         or flat MDS vs.
         Summa
         ). The descriptions were randomly ordered to remove bias. The workers were
asked which user appeared to have learned more and why. For each pair of
descriptions, four workers evaluated the pair.
Standard checks such as approval
rating, location filtering, etc. were used for
removing spam.
The results of this experiment are as follows:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_left ltx_border_t">
            Prefer
           </th>
           <th class="ltx_td ltx_border_r ltx_border_t">
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Indiff.
           </th>
           <th class="ltx_td ltx_align_left ltx_border_t">
            Prefer
           </th>
           <th class="ltx_td ltx_border_t">
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_tt">
            Summa
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            58%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            17%
           </td>
           <td class="ltx_td ltx_align_left ltx_border_tt">
            Timeline
           </td>
           <td class="ltx_td ltx_align_center ltx_border_tt">
            25%
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_bb ltx_border_t">
            Summa
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            40%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            22%
           </td>
           <td class="ltx_td ltx_align_left ltx_border_bb ltx_border_t">
            Flat-MDS
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_t">
            38%
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         Descriptions written by workers using
         Summa
         were preferred over twice as
often as those from timelines. We looked more closely at those
cases where the participants either preferred the timelines or were
indifferent and found that this preference was most common when the topic
was not dominated by a few major events, but was instead a series of
similarly important events. For example, in the kidnapping and beheading
of Daniel Pearl there were two or three obviously major events, whereas in
the Kargil War there were many smaller important events. In latter cases,
the hierarchical summaries provided little advantage over the timelines
because it was more difficult to arrange the sentences hierarchically.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p5">
        <p class="ltx_p">
         Since
         Summa
         was judged to be so much superior to flat MDS systems in
Section
         5.1
         , it is surprising that users descriptions
from flat MDS were preferred nearly as often as those from
         Summa
         .
While the flat summaries were disjointed, they were good at including
salient information, with the most salient tending to be near the start
of the summary. Thus, descriptions from both
         Summa
         and flat MDS generally
covered the most salient information.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Informativeness
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         In this experiment, we assess the salience of the information captured by the
different systems, and the ability of
         Summa
         to organize the information so
that more important information is placed at higher levels.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         ROUGE Evaluation:
         We first automatically assessed informativeness by calculating the ROUGE-1
scores of the output of each of the systems. For the gold standard comparison summary,
we use the Wikipedia articles for the topics.
         Note that there is no good translation of ROUGE for hierarchical summarization. Thus, we
simply use the traditional ROUGE metric, which will not capture any of the hierarchical
format. This score will essentially serve as a rough measure of coverage of the entire
summary to the Wikipedia article. The scores for each of the systems are as follows:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_border_rr ltx_border_t">
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            P
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            R
           </th>
           <th class="ltx_td ltx_align_center ltx_border_t">
            F1
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_tt">
            Summa
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            0.25
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            0.67
           </td>
           <td class="ltx_td ltx_align_center ltx_border_tt">
            0.31
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_t">
            Timeline
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            0.28
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            0.65
           </td>
           <td class="ltx_td ltx_align_center ltx_border_t">
            0.33
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_bb ltx_border_rr ltx_border_t">
            Flat-MDS
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            0.30
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            0.64
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_t">
            0.34
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         None of the differences are significant. From this evaluation, one can gather that the
systems have similar coverage of the Wikipedia articles.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         Manual Evaluation:
         While ROUGE serves as a rough measure of coverage, we were interested in gathering
more fine-grained information on the informativeness of each system.
We performed an additional manual evaluation that assesses the recall
of important events for each system.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p6">
        <p class="ltx_p">
         We first identified which events were most important in a news story.
Because reading 300 articles per topic is impractical, we asked AMT workers
to read a Wikipedia article on the same topic and then identify the three
most important events and the five most important secondary events. We
aggregated responses from ten workers per topic and chose the three most
common primary and five most common secondary events.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p7">
        <p class="ltx_p">
         One of the authors then manually identified the presence of these events in the
hierarchical summaries, the timelines and the flat MDS summaries. Below we show event
recall (the percentage of the events that were mentioned).
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p8">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_t">
            Events
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Summa
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Timeline
           </th>
           <th class="ltx_td ltx_align_center ltx_border_t">
            Flat-MDS
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_tt">
            Prim.
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            96%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            74%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_tt">
            93%
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_bb ltx_border_rr ltx_border_t">
            Sec.
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            76%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            53%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_t">
            64%
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS3.p9">
        <p class="ltx_p">
         The difference in recall between
         Summa
         and
         Timeline
         was significant in both cases,
and the difference between
         Summa
         and
         Flat-MDS
         was not.
In general, the flat summaries were quite redundant, which contributed to the slightly
lower event recall. The timelines, on the other hand, were both incoherent and at the
same time reported less important facts.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p10">
        <p class="ltx_p">
         We also evaluated at what level in the hierarchy the events were identified for the
hierarchical summaries. The event recall shows the percentage of events
mentioned at that level or above in the hierarchical summary:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p11">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_t">
            Events
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Level 1
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Level 2
           </th>
           <th class="ltx_td ltx_align_center ltx_border_t">
            Level 3
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_rr ltx_border_tt">
            Prim.
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            63%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_tt">
            81%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_tt">
            96%
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_bb ltx_border_rr ltx_border_t">
            Sec.
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            27%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_t">
            51%
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_t">
            76%
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS3.p12">
        <p class="ltx_p">
         81% of the primary events are
present in the first or second level, and 76% of the secondary events are
mentioned by the third level.
While recognizing primary events is relatively simple because they are repeated frequently,
identification of important secondary events often requires external knowledge.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Parent-to-Child Coherence
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         We next tested the hierarchical coherence. One of the authors graded how much each
non-leaf sentence in a summary was coherent with its child summary on a
scale of one to five, with one being incoherent and five being perfectly
coherent. We used the coherence scale from DUC’04.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_border_rr ltx_border_t">
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            Level 1
           </th>
           <th class="ltx_td ltx_align_center ltx_border_t">
            Level 2
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_bb ltx_border_rr ltx_border_tt">
            Coherence
           </th>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_r ltx_border_tt">
            3.8
           </td>
           <td class="ltx_td ltx_align_center ltx_border_bb ltx_border_tt">
            3.4
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS4.p3">
        <p class="ltx_p">
         We found that for the top level of the summary, the parent sentence generally
represented the most important event in the cluster and the child summary usually expressed
details or reactions of the event. The lower coherence scores were often the
result of too few lexical connections or lack of a theme or story.
While the facts of the sentences made sense together, the summaries sometimes
did not read as if they were written by a human, but as a series of disparate sentences.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p4">
        <p class="ltx_p">
         For the second level, the problems were more basic. The parent sentence
occasionally expressed a less important fact that the child summary did not then expand on
or, more commonly, the child summary was not focused enough. This result stems from two
problems in our algorithm. First, summarizing sentences are rare,
making good choices for parent sentences difficult to find.
The second problem relates to the difficulty in identifying
whether two sentences are on the same topic. For example, suppose the parent sentence is,
“A Swissair plane Wednesday night crashed off Nova Scotia, Canada.”
A very good child sentence is, “The airline confirmed that all passengers died.”
However, based on their surface features, the sentence, “A plane
made an unscheduled landing after a Swissair plane crashed off the coast of
Canada,” appears to be a better choice.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p5">
        <p class="ltx_p">
         Even though there is scope for improvement, we find these coherence scores encouraging
for a first algorithm for the task.
        </p>
       </div>
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
        Traditional approaches to large-scale summarization have included flat summaries and
timelines. There are two primary shortcomings to these approaches: first, they require
the user to sort through large amounts of potentially overwhelming information, and
second, the output is static –
users with different interests will see
the same information. Below we describe related work on traditional MDS,
structured summaries,
timelines,

discovering threads of documents and the uses of
hierarchies in generating summaries.
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        Traditional MDS
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         Traditionally, MDS systems have focused on three to six sentence summaries
covering 10-15 documents. Most extractive summarization research aims to maximize
coverage while reducing redundancy (e.g.
         [4, 24, 23]
         ). Lin and Bilmes
         [19]
         proposed a
state-of-the-art system that uses submodularity in sentence selection to accomplish
these goals. Christensen et al.
         [8]
         presented
an algorithm for coherent MDS, but it does not scale to larger output.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         Structured Summaries:
         Some research has explored generating structured summaries.
These approaches attempt to identify major aspects of a topic, but do not
compile content to describe those aspects. Rather, they rely on
pre-existing, labeled paragraphs (for example, a paragraph titled, “Symptoms of Meningitis”).
Aspects are identified either by a training corpus of articles in the same domain
         [25]
         , by an entity-aspect LDA model
         [17]
         , or by Wikipedia
templates of related topics
         [35]
         .
These methods assume a common structure for all topics in a category, and do
not allow for more than two levels in the structure.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p3">
        <p class="ltx_p">
         Timeline Generation:
         Recent papers in timeline generation have emphasized the relationship with
summarization. Yan et al.
         [33]
         balanced coherence and diversity to create
timelines, Yan et al.
         [32]
         used inter-date and intra-date sentence
dependencies, and Chieu and Lee
         [7]
         used sentence similarity.
Others have emphasized identifying important dates, primarily by
bursts of news
         [28, 1, 11, 12]
         .
While timelines can be useful for understanding events,
they do not generalize to other domains. Additionally,
long timelines can be overwhelming, short timelines have low
information content, and there is no method for personalized exploration.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p4">
        <p class="ltx_p">
         Document Threads:
         A related track of research investigates discovering threads of documents.
While we aim to summarize collections of information, this track
seeks to identify relationships between documents.
This research operates on the document level, while
ours operates on the sentence level.

Shahaf and Guestrin
         [27]
         formalized the characteristics of a
good chain of articles and proposed an algorithm to connect two specified articles.
Gillenwater et al.
         [9]
         proposed a probabilistic
technique for extracting a diverse set of threads from a given collection.
Shahaf et al.
         [26]
         extended work on coherent threads to finding coherent
maps of documents, where a map is set of intersecting threads representing how
the threads interact and relate.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p5">
        <p class="ltx_p">
         Summarization and Hierarchies:
         A few papers have examined the relationship between summarization and hierarchies.
Some focused on creating a hierarchical summary of a single document
         [3, 21]
         ,
relying on the structure inherent in single documents.
Others investigated creating hierarchies of words or phrases to
organize documents
         [15, 16, 29, 10]
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p6">
        <p class="ltx_p">
         Other research identifies the hierarchical structure
of the documents and generates a summary that prioritizes more general
information according to the structure
         [22, 5]
         , or gains coverage by drawing
sentences from different parts of the hierarchy
         [34, 31]
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
