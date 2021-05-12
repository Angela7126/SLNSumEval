<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Semantic Frame Identification with Distributed Word Representations.
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
       We present a novel technique for semantic frame identification
using distributed representations of predicates and their syntactic context;
this technique leverages
automatic syntactic parses and a generic set of
word embeddings. Given labeled
data annotated with frame-semantic
parses, we learn a model that projects the set of word representations for the
syntactic context around a predicate to a low dimensional representation.
The latter is used for semantic frame identification; with a standard
argument identification method inspired by prior work, we achieve
state-of-the-art results on FrameNet-style frame-semantic analysis.
Additionally, we report strong results on PropBank-style semantic role labeling
in comparison to prior work.
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
        Distributed representations of words have proved useful for a number of tasks. By providing richer representations of meaning than what can be encompassed in a discrete representation, such approaches have successfully been applied to tasks such as sentiment analysis
        [24]
        , topic classification
        [16]
        or word-word similarity
        [20]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        We present a new technique for semantic
        frame
        identification that leverages distributed word representations.
According to the theory of frame semantics
        [12]
        , a semantic frame represents an event or scenario, and possesses frame elements (or semantic
        roles
        ) that participate in the event. Most work on frame-semantic parsing
has usually divided the task into two major subtasks:
        frame identification
        , namely the disambiguation of a given predicate to a frame, and
        argument identification
        (or semantic role labeling), the analysis of words and phrases in the sentential context that satisfy the frame’s semantic roles
        [8, 7]
        .
        Here, we focus on the first subtask of frame identification for given predicates; we use our novel method (§
        3
        ) in conjunction with a standard argument identification model (§
        4
        ) to perform full frame-semantic parsing.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We present experiments on two tasks. First, we show that for frame identification on
the FrameNet corpus
        [2, 11]
        , we outperform the prior state of the art
        [7]
        .
Moreover, for full frame-semantic parsing, with the presented frame identification technique followed by our argument identification method, we report the best results on this task to date.
Second, we present results on PropBank-style semantic role labeling
        [22, 19, 21]
        , that
approach strong baselines, and are on par with prior state of the art
        [23]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Overview
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Early work in frame-semantic analysis was pioneered by
        Gildea and Jurafsky (2002)
        .
Subsequent work in this area focused on either the FrameNetor PropBankframeworks, and research
on the latter has been more popular. Since the CoNLL 2004-2005 shared
tasks
        [4, 5]
        on PropBank semantic role labeling (SRL), it has been
treated as an important NLP problem. However, research has mostly focused on
argument analysis, skipping the frame disambiguation step, and its interaction
with argument identification.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Frame-Semantic Parsing
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Closely related to SRL, frame-semantic parsing consists of the resolution of
predicate sense into a frame, and the analysis of the frame’s arguments.
Work in this area exclusively uses the FrameNet full text annotations.
         Johansson and Nugues (2007)
         presented the best performing system at SemEval
2007
         [1]
         , and
         Das et al. (2010)
         improved performance, and later
set the current state of the art on this task
         [7]
         .
We briefly discuss FrameNet, and subsequently PropBank annotation conventions here.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         FrameNet
         The FrameNetproject
         [2]
         is a lexical database that contains
information about words and phrases (represented as lemmas conjoined with
a coarse part-of-speech tag) termed as lexical units, with a set of semantic
frames that they could evoke. For each frame, there is a list of associated frame elements
(or roles, henceforth), that are also distinguished as core or non-core.
         Sentences are annotated using this universal frame inventory.
For example, consider the pair of sentences in Figure
         1
         (a).
         Commerce_buy
         is a frame that can be evoked by morphological variants
of the two example lexical units
         buy
         .
         V
         and
         sell
         .
         V
         .
         Buyer
         ,
         Seller
         and
         Goods
         are some example roles
for this frame.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         PropBank
         The PropBankproject
         [22]
         is
another popular resource related to semantic role labeling.
The PropBankcorpus has verbs annotated with sense frames and their arguments.
Like FrameNet, it also has a lexical database that stores type information about verbs, in the form
of sense frames and the possible semantic roles each frame could take. There are
modifier roles that are shared across verb frames, somewhat similar to the non-core
roles in FrameNet. Figure
         1
         (b) shows annotations for
two verbs “bought” and “sold”, with their lemmas (akin to the lexical units in FrameNet)
and their verb frames
         buy.01
         and
         sell.01
         . Generic core role labels (of which
there are seven, namely
         A0
         -
         A5
         and
         AA
         ) for the verb frames
are marked in the figure.
         A key difference between the two annotation systems is that PropBankuses a local frame inventory, where frames are predicate-specific. Moreover, role labels, although few in number,
take specific meaning for each verb frame.
Figure
         1
         highlights this difference:
while both
         sell
         .
         v
         and
         buy
         .
         v
         are members of the
same frame in FrameNet, they evoke different frames in PropBank.
In spite of this difference, nearly identical statistical models could be employed
for both frameworks.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         Modeling
         In this paper, we model the frame-semantic parsing problem in two stages:
         frame identification
         and
         argument identification
         . As mentioned in §
         1
         ,
these correspond to a frame disambiguation stage,
         and a stage that finds the various
arguments that fulfill the frame’s semantic roles within the sentence, respectively. This resembles the
framework of
         Das et al. (2014)
         , who solely focus on FrameNet corpora,
unlike this paper. The novelty of this paper lies in the frame identification stage (§
         3
         ).
Note that this two-stage approach is unusual for the PropBank corpora when compared
to prior work, where the vast majority of published papers have not focused on the
verb frame disambiguation problem at all, only focusing on the role labeling stage (see
the overview paper of
         Màrquez et al. (2008)
         for example).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Distributed Frame Identification
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         We present a model that takes word embeddings as input and
learns to identify semantic frames. A word embedding is a
distributed representation of meaning where each word is represented as a vector
in
         ℝn
         . Such representations allow a model to share meaning between
similar words, and have been used to capture semantic, syntactic and
morphological content
         [6, 25, inter alia]
         .
We use word embeddings to represent the syntactic context of a particular
predicate instance as a vector. For example, consider the sentence “He runs the
company.” The predicate
         runs
         has two syntactic dependents – a subject and direct
object (but no prepositional phrases or clausal complements). We could represent
the syntactic context of
         runs
         as a vector with blocks for all the possible
dependents warranted by a syntactic parser; for example, we could assume that
positions
         0⁢…⁢n
         in the vector correspond to the subject dependent,
         n+1⁢…⁢2⁢n
         correspond to the clausal complement dependent, and so forth. Thus, the context
is a vector in
         ℝn⁢k
         with the embedding of
         He
         at the subject position, the
embedding of
         company
         in direct object position and zeros everywhere else.
Given input vectors of this form for our training data, we learn a matrix that maps this high dimensional
and sparse representation into a lower dimensional space. Simultaneously, the model
learns an embedding for all the possible labels (i.e. the frames in a given
lexicon). At inference time, the predicate-context is mapped to the low dimensional space,
and we choose the nearest frame label as our classification. We next describe this model in detail.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Frame Identification with Embeddings
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        [25][t]
        <img alt="" class="ltx_graphics ltx_centering" height="134" id="S3.p1.g1" src="P14-1136/image002.png" width="318"/>
        Context representation extraction for the embedding model. Given a dependency
parse (1) the model extracts all words matching a set of paths from the frame
evoking predicate and its direct dependents (2). The model computes a composed
representation of the predicate instance by using distributed vector
representations for words (3) – the (red) vertical embedding vectors for each
word are concatenated into a long vector. Finally, we learn a
linear transformation function parametrized by the context blocks (4).
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We continue using the example sentence from
§
        2.2
        : “He runs the company.” where we want to
disambiguate the frame of
        runs
        in context. First, we extract
the words in the syntactic context of
        runs
        ; next, we concatenate
their word embeddings as described in §
        2.2
        to create an
initial vector space representation. Subsequently, we learn a
mapping from this initial representation into a low-dimensional space; we also learn an
embedding for each possible frame label in the same low-dimensional space. The goal of
learning is to make sure that the correct frame label is as close as possible to the
mapped context, while competing frame labels are farther away.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Formally, let
        x
        represent the actual sentence with a marked
predicate, along with the associated
syntactic parse tree; let our initial representation of the predicate context be
        g⁢(x)
        .
Suppose that the word
embeddings we start with are of dimension
        n
        . Then
        g
        is a function from a
parsed sentence
        x
        to
        ℝn⁢k
        , where
        k
        is the number of
possible syntactic context types. For example
        g
        selects some important
positions relative to the predicate, and reserves a block in its output space
for the embedding of words found at that position. Suppose
        g
        considers clausal complements and direct objects. Then
        g:X→ℝ2⁢n
        and for the example sentence it has zeros in positions
        0⁢…⁢n
        and the
embedding of the word
        company
        in positions
        n+1⁢…⁢2⁢n
        .
       </p>
       g⁢(x)=[0,…,0,embedding of company].
       <p class="ltx_p">
        Section
        3.1
        describes the context positions we use in our
experiments. Let the low dimensional space we map to be
        ℝm
        and the learned
mapping be
        M:ℝn⁢k→ℝm
        .
The mapping
        M
        is a linear transformation, and we learn it using the
        Wsabie
        algorithm
        [29]
        .
        Wsabie
        also learns an embedding for each frame label (
        y
        , henceforth).
In our setting, this means that each frame corresponds to a point in
        ℝm
        .
If we have
        F
        possible frames we can store those parameters in an
        F×m
        matrix, one
        m
        -dimensional point
for each frame, which we will refer to as the linear mapping
        Y
        .
Let the lexical unit (the lemma conjoined with a coarse POS tag) for the
marked predicate be
        ℓ
        . We denote the frames that associate
with
        ℓ
        in the frame lexicon
        and our training corpus as
        Fℓ
        .
        Wsabie
        performs gradient-based updates
on an objective that tries to minimize the distance between
        M⁢(g⁢(x))
        and the
embedding of the correct label
        Y⁢(y)
        , while maintaining a large distance
between
        M⁢(g⁢(x))
        and the other possible labels
        Y⁢(y¯)
        in the confusion
set
        Fℓ
        . At disambiguation time, we use a simple dot product similarity as
our distance metric, meaning that the model chooses a label by computing the
        argmaxy⁢s⁢(x,y)
        where
        s⁢(x,y)=M⁢(g⁢(x))⋅Y⁢(y)
        , where the
        argmax
        iterates over the possible frames
        y∈Fℓ
        if
        ℓ
        was
seen in the lexicon or the
training data, or
        y∈F
        , if it was unseen.
        Model learning is performed using the margin ranking loss function as described
in
        Weston et al. (2011)
        , and in more detail in section
        3.2
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Since
        Wsabie
        learns a single mapping from
        g⁢(x)
        to
        ℝm
        , parameters are
shared between different words and different frames. So for example “He
        runs
        the company” could help the model disambiguate “He
        owns
        the
company.” Moreover, since
        g⁢(x)
        relies on word embeddings rather than word
identities, information is shared between words. For example
“
        He
        runs
        the company
        ” could help us to learn about “
        She
        runs
        a corporation
        ”.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Context Representation Extraction
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In principle
         g⁢(x)
         could be any feature function, but we performed an
initial investigation of two particular variants. In both variants,
our representation is a block vector where each block corresponds to a syntactic position relative to the predicate, and each block’s values correspond to the embedding of the word at that position.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Direct Dependents
         The first context function we
considered corresponds to the examples in §
         3
         .
To elaborate, the positions of interest are the labels of the direct dependents of
the predicate, so
         k
         is the number of labels that the dependency parser can
produce. For example, if the label on the edge between
         runs
         and
         He
         is
         nsubj
         , we would put the embedding of
         He
         in the
block corresponding to
         nsubj
         . If a label occurs multiple times, then
the embeddings of the words below this label are averaged.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Unfortunately, using only the direct dependents can miss a lot of
useful information. For example, topicalization can place discriminating
information farther from the predicate. Consider “He
         runs
         the
         company
         .” vs.
“It was the
         company
         that he
         runs
         .” In the second sentence, the discriminating
word,
         company
         dominates the predicate
         runs
         . Similarly,
predicates in embedded clauses may have a distant agent which
cannot be captured using direct dependents.
Consider
“
         The athlete
         ran
         the marathon.” vs. “
         The athlete
         prepared himself for three months to
         run
         the marathon.”
In the second example, for the predicate
         run
         , the agent
         The athlete
         is not a direct dependent, but is connected via a longer dependency path.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Dependency Paths
         To capture more relevant context,
we developed a second context function as follows.
We scanned the training data for a given
task (either the PropBank or the FrameNet domains) for the
dependency paths that connected the gold predicates to the gold semantic arguments.
This set of dependency paths were deemed as possible positions
in the initial vector space representation. In addition, akin to the first context function,
we also added all dependency labels to the context set.
Thus for this context function, the block cardinality
         k
         was
the sum of the number of scanned gold dependency path types and the
number of dependency labels.
Given a predicate in its sentential context, we therefore extract only those
context words that appear in positions warranted by the above set.
See Figure
         3
         for an illustration of this process.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         We performed initial experiments using context extracted from 1) direct
dependents, 2) dependency paths, and 3) both. For all our experiments, setting
3) which concatenates the direct dependents and dependency path always dominated
the other two, so we only report results for this setting.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Learning
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         We model our objective function following
         Weston et al. (2011)
         , using a
weighted approximate-rank pairwise loss, learned with stochastic gradient
descent. The mapping from
         g⁢(x)
         to the low dimensional space
         ℝm
         is a
linear transformation, so the model parameters to be learnt are the
matrix
         M∈ℝn⁢k×m
         as well as the embedding of each possible frame label,
represented as another
matrix
         Y∈ℝF×m
         where there are
         F
         frames in total.
The training objective function minimizes:
        </p>
        ∑x∑y¯L⁢(r⁢a⁢n⁢ky⁢(x))⁢max⁡(0,γ+s⁢(x,y)-s⁢(x,y¯)).
        <p class="ltx_p">
         where
         x,y
         are the training inputs and their corresponding correct frames,
and
         y¯
         are negative frames,
         γ
         is the margin. Here,
         r⁢a⁢n⁢ky⁢(x)
         is the rank of the positive frame
         y
         relative to all the negative frames:
        </p>
        ranky(x)=∑y¯I(s(x,y)≤γ+s(x,y¯)),
        <p class="ltx_p">
         and
         L⁢(η)
         converts the rank to a weight. Choosing
         L⁢(η)=C⁢η
         for any positive constant
         C
         optimizes the mean rank,
whereas a weighting such as
         L⁢(η)=∑i=1η1/i
         (adopted here)
optimizes the top of the ranked list, as described
in
         [26]
         . To train with such an objective, stochastic gradient is employed.
For speed the computation of
         r⁢a⁢n⁢ky⁢(x)
         is then replaced with a sampled approximation:
sample
         N
         items
         y¯
         until a violation is found, i.e.
         max(0,γ+s(x,y¯)-s(x,y)))&gt;0
         and then approximate the rank with
         (F-1)/N
         , see
         Weston et al. (2011)
         for more details on this procedure.
For the choices of the stochastic gradient learning rate, margin (
         γ
         ) and dimensionality (
         m
         ), please
refer to §
         5.4
         -§
         5.5
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Note that an alternative approach
could learn only the matrix
         M
         , and then use a
         k
         -nearest
neighbor classifier in
         ℝm
         , as in
         Weinberger and Saul (2009)
         . The advantage
of learning
an embedding for the frame labels is that at inference time we
need to consider only the set of labels for classification rather than all training examples.
Additionally, since we use a frame lexicon that gives us the possible frames for
a given predicate, we usually only consider a handful of candidate labels.
If we used all training examples for a given predicate for finding a nearest-neighbor match
at inference time, we would have to consider many more candidates, making
the process very slow.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Argument Identification
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Here, we briefly describe the argument identification model used
in our frame-semantic parsing experiments, post frame identification.
Given
        x
        , the sentence with a marked predicate,
the argument identification model assumes that the predicate frame
        y
        has been disambiguated. From a frame lexicon, we look up the
set of semantic roles
        ℛy
        that associate with
        y
        .
This set also contains the null role
        r∅
        . From
        x
        ,
a rule-based candidate argument extraction algorithm extracts a set
of spans
        𝒜
        that could potentially serve as the overt
        arguments
        𝒜y
        for
        y
        (see §
        5.4
        -§
        5.5
        for the details of the
candidate argument extraction algorithms).
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Learning
        Given training data of the form
        ⟨⟨x(i),y(i),ℳ(i)⟩⟩i=1N
        , where,
       </p>
       ℳ={(r,a}:r∈ℛy,a∈𝒜∪𝒜y},

(1)
       <p class="ltx_p">
        a set of tuples that associates each role
        r
        in
        ℛy
        with a span
        a
        according to the gold data.
Note that this mapping associates spans with the null role
        r∅
        as well.
We optimize the following log-likelihood to train our model:
       </p>
       max𝜽∑i=1N∑j=1∣ℳ(i)∣logp𝜽((r,a)j|x,y,ℛy)-C∥𝜽∥22
       <p class="ltx_p">
        where
        p𝜽
        is a log-linear model normalized over the set
        ℛy
        , with features described in Table
        1
        . We
set
        C=1.0
        and use L-BFGS
        [18]
        for training.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Inference
        Although our learning mechanism uses
a local log-linear model, we perform inference globally on a per-frame basis by
applying hard structural constraints. Following
        Das et al. (2014)
        and
        Punyakanok et al. (2008)
        we use the
log-probability of the local classifiers as a score in an integer linear program
(ILP) to assign roles subject to hard constraints described in
§
        5.4
        and §
        5.5
        .
We use an off-the-shelf ILP solver for inference.
       </p>
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
        In this section, we present our experiments and the results achieved.
We evaluate our novel frame identification approach in isolation
and also conjoined with argument identification resulting in full
frame-semantic structures; before presenting our model’s performance
we first focus on the datasets, baselines and the experimental setup.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Data
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We evaluate our models on both FrameNet- and PropBank-style structures. For
FrameNet, we use the full-text annotations in the FrameNet 1.5
release
         which was
used by
         §3.2]das-etal-semafor-2013. We used the same test set as
Das et al. containing 23 documents with 4,458 predicates. Of the remaining 55
documents, 16 documents were randomly chosen for development.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         For experiments with PropBank, we used the Ontonotes corpus
         [14]
         , version
4.0, and only made use of the Wall Street Journal
documents; we used sections 2-21 for training, section 24 for development
and section 23 for testing. This resembles the setup used by
         Punyakanok et al. (2008)
         .
All the verb frame files in Ontonotes were used for creating our frame
lexicon.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Frame Identification Baselines
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         For comparison, we implemented a set of baseline models, with
varying feature configurations. The baselines use a
log-linear model that models the following probability at training time:
        </p>
        p(y|x,ℓ)=e𝝍⋅𝐟⁢(y,x,ℓ)∑y¯∈Fℓe𝝍⋅𝐟⁢(y¯,x,ℓ)

(2)
        <p class="ltx_p">
         At test time, this model chooses the best frame as
         argmaxy⁢𝝍⋅𝐟⁢(y,x,ℓ)
         where
         argmax
         iterates over the possible frames
         y∈Fℓ
         if
         ℓ
         was
seen in the lexicon or the training data, or
         y∈F
         , if it was unseen, like
the disambiguation scheme of §
         3
         . We train
this model by maximizing
         L2
         regularized log-likelihood, using L-BFGS;
the regularization constant was set to 0.1 in all experiments.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         For comparison with our model from §
         3
         ,
which we call
         Wsabie Embedding
         , we implemented two baselines
with the log-linear model. Both the baselines use features very similar to the
input representations described in §
         3.1
         . The first one
computes the direct dependents and dependency paths as described
in §
         3.1
         but conjoins them with the word identity rather
than a word embedding. Additionally, this model uses the un-conjoined words as
backoff features. This would be a standard NLP approach for the frame
identification problem, but is surprisingly competitive with the state of the
art. We call this baseline
         Log-Linear Words
         . The second
baseline, tries to decouple the
         Wsabie
         training from the embedding input, and
trains a log linear model using the embeddings. So the second baseline has the
same input representation as
         Wsabie Embedding
         but uses a
log-linear model instead of
         Wsabie
         . We call this model
         Log-Linear Embedding
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Common Experimental Setup
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         We process our PropBank and FrameNet training, development and test corpora
with a shift-reduce dependency parser that uses the Stanford conventions
         [9]
         and uses an arc-eager transition system with beam size of 8; the parser and its features
are described by
         Zhang and Nivre (2011)
         .
Before parsing the data, it is tagged with a POS tagger trained
with a conditional random field
         [17]
         with
the following emission features: word, the word cluster,
word suffixes of length 1, 2 and 3, capitalization, whether it has a hyphen,
digit and punctuation.
Beyond the bias transition feature, we have two cluster features for the left
and right words in the transition. We use Brown clusters learned
using the algorithm of
         Uszkoreit and Brants (2008)
         on
a large English newswire corpus for cluster features. We use the same word
clusters
for the argument identification features in Table
         1
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         We learn the initial embedding representations for our frame
identification model (§
         3
         ) using a deep neural language model
similar to the one proposed by
         Bengio et al. (2003)
         . We use 3 hidden
layers
each with 1024 neurons and learn a 128-dimensional embedding from a large corpus
containing over 100 billion tokens. In order to speed up learning,
we use an unnormalized output layer and a hinge-loss objective. The objective
tries to ensure that the correct word scores higher than a random incorrect
word, and we train with minibatch stochastic gradient descent.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Experimental Setup for FrameNet
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         Hyperparameters
         For our frame identification model with embeddings, we search for the
         Wsabie
         hyperparameters using the development data. We search for the
stochastic gradient learning rate in
         {0.0001¯,0.001,0.01}
         , the margin
         γ∈{0.001,0.01¯,0.1,1}
         and the dimensionality
of the final vector space
         m∈{256¯,512}
         , to maximize
the frame identification accuracy of
         ambiguous
         lexical units; by ambiguous,
we imply lexical units that appear in the training data or the lexicon with
more than one semantic frame. The underlined
values are the chosen hyperparameters used to analyze the test data.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <p class="ltx_p">
         Argument Candidates
         The candidate argument extraction method used for the FrameNet data,
(as mentioned in §
         4
         ) was adapted from the algorithm
of
         Xue and Palmer (2004)
         applied to dependency trees. Since the original
algorithm was designed for verbs, we added a few extra rules to
handle non-verbal predicates: we added 1) the predicate itself as a candidate
argument, 2) the span ranging from the sentence
position to the right of the predicate
to the rightmost index of the subtree headed by the predicate’s head; this helped
capture cases like “a
         few
         months
         ” (where
         few
         is
the predicate and
         months
         is the argument),
and 3) the span ranging from the leftmost index
of the subtree headed by the predicate’s head to the position immediately
before the predicate, for cases like “
         your gift
         to
         Goodwill” (where
         to
         is the predicate and
         your gift
         is the argument).
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p3">
        <p class="ltx_p">
         Frame Lexicon
         In our experimental setup,
we scanned the XML files in the “frames” directory of the FrameNet 1.5 release,
which lists all the frames, the corresponding roles and the associated lexical units,
and created a frame lexicon to be used in our frame and argument
identification models. We noted that this renders every lexical unit
as
         seen
         ; in other words, at frame disambiguation time on our test set,
for all instances, we only had to score the frames in
         Fℓ
         for a predicate with lexical unit
         ℓ
         (see §
         3
         and §
         5.2
         ). We call this setup
         Full Lexicon
         . While comparing with prior state of the art on the same corpus, we noted
that
         Das et al. (2014)
         found several unseen predicates at test time.
         For fair comparison,
we took the lexical units for the predicates that Das et al. considered as
seen, and constructed a lexicon with only those; training instances, if any,
for the unseen predicates under Das et al.’s setup were thrown out as well.
We call this setup
         Semafor Lexicon
         .
         We also experimented on the set of unseen instances
used by Das et al.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p4">
        <p class="ltx_p">
         ILP constraints
         For FrameNet, we used three ILP constraints
during argument identification (§
         4
         ). 1) each
span could have only one role, 2) each core role could be present only once,
and 3) all overt arguments had to be non-overlapping.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.5
        </span>
        Experimental Setup for PropBank
       </h3>
       <div class="ltx_para" id="S5.SS5.p1">
        <p class="ltx_p">
         Hyperparameters
         As in §
         5.4
         ,
we made a hyperparameter sweep in the same space. The chosen learning rate was
         0.01
         , while the other values were
         γ=0.01
         and
         m=512
         . Ambiguous
lexical units were used for this selection process.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS5.p2">
        <p class="ltx_p">
         Argument Candidates
         For PropBankwe use the algorithm of
         Xue and Palmer (2004)
         applied to dependency
trees.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS5.p3">
        <p class="ltx_p">
         Frame Lexicon
         For the PropBankexperiments
we scanned the frame files for propositions in Ontonotes 4.0, and stored
possible core roles for each verb frame. The lexical units were simply the verb
associating with the verb frames. There were no unseen verbs at test time.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS5.p4">
        <p class="ltx_p">
         ILP constraints
         We used the constraints of
         Punyakanok et al. (2008)
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS6">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.6
        </span>
        FrameNet Results
       </h3>
       <div class="ltx_para" id="S5.SS6.p1">
        <p class="ltx_p">
         Table
         2
         presents accuracy results on frame identification.
         We present results on all predicates, ambiguous
predicates seen in the lexicon or the training data, and rare ambiguous
predicates that appear
         ≤11
         times in the training data.
The
         Wsabie Embedding
         model from §
         3
         performs
significantly better than the
         Log-Linear Words
         baseline, while
         Log-Linear Embedding
         underperforms in every
metric.
For the
         Semafor Lexicon
         setup, we also compare with
the state of the art from
         Das et al. (2014)
         ,
who used a semi-supervised learning method to improve upon a supervised
latent-variable log-linear model.
For unseen predicates from the Das et al. system, we perform better as well.
Finally, for the
         Full Lexicon
         setting, the absolute accuracy numbers are even
better for our best model. Table
         3
         presents results
on the full frame-semantic parsing task (measured by a reimplementation
of the SemEval 2007 shared task evaluation script) when our argument identification model (§
         4
         )
is used after frame identification. We notice similar trends as in Table
         2
         ,
and our results outperform the previously published best results, setting a new
state of the art.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS7">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.7
        </span>
        PropBank Results
       </h3>
       <div class="ltx_para" id="S5.SS7.p1">
        <p class="ltx_p">
         Table
         4
         shows frame identification results on the
PropBankdata. On the development set, our best model performs with
the highest accuracy on all and ambiguous predicates, but performs worse
on rare ambiguous predicates. On the test set, the
         Log-Linear
Words
         baseline performs best by a very narrow margin. See
§
         6
         for a discussion.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS7.p2">
        <p class="ltx_p">
         Table
         5
         presents results where we measure
precision, recall and
         F1
         for frames and arguments together; this strict
metric penalizes arguments for mismatched frames, like in
Table
         3
         . We see the same trend as in
Table
         4
         .
Finally,
Table
         6
         presents SRL results that measures argument
performance only, irrespective of the frame; we use the evaluation script
from CoNLL 2005
         [5]
         . We note that with a better
frame identification model, our performance on SRL improves in general. Here, too, the embedding
model barely misses the performance of the best baseline, but we are at par and
sometimes
better than the single parser setting of a state-of-the-art SRL system
         [23]
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Discussion
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        For FrameNet, the
        Wsabie Embedding
        model we propose strongly
outperforms the baselines on all metrics, and sets a new state of the art.
We believe that the
        Wsabie
Embedding
        model performs better than the
        Log-Linear Embedding
        baseline (that uses the same input representation) because the former setting
allows examples
with different labels and confusion sets to share information; this is due to
the fact that all labels live in the same label space, and a single projection
matrix is shared across the examples to map the input features to this space.
Consequently, the
        Wsabie Embedding
        model can share more
information between different examples in the training data than the
        Log-Linear Embedding
        model. Since the
        Log-Linear Words
        model
always performs better than the
        Log-Linear Embedding
        model, we
conclude that the primary benefit does not come from the input embedding representation.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        On the PropBankdata, we see that the
        Log-Linear Words
        baseline has roughly the same performance as
our model on most metrics: slightly better on the test data and slightly worse
on the development data. This can be partially explained with the significantly
larger
training set size for PropBank, making features based on words more useful.
Another important distinction between PropBankand FrameNetis that
the latter shares frames between multiple lexical units. The effect of this is clearly
observable from the “Rare” column in
Table
        4
        .
        Wsabie Embedding
        performs
poorly in this setting while
        Log-Linear Embedding
        performs well. Part of the explanation has to do with the
specifics of
        Wsabie
        training. Recall that the
        Wsabie
Embedding
        model needs to estimate the label location in
        ℝm
        for each frame.
In other words, it must estimate 512 parameters based on at most 10 training examples.
However, since the input representation is shared across all frames, every other
training example from all the lexical units affects the optimal estimate, since
they all modify the joint parameter matrix
        M
        . By contrast, in the log-linear
models each label has its own set of parameters, and they interact only via the
normalization constant. The
        Log-Linear Words
        model does not
have this entanglement, but cannot share information between words. For
PropBank, these drawbacks and benefits balance out and we see similar
performance for
        Log-Linear Words
        and
        Log-Linear Embedding
        . For FrameNet, estimating
the label embedding is not as
much of a problem because even if a lexical unit is rare, the potential frames
can be frequent. For example, we might have seen the
        Sending
        frame many times,
even though
        telex
        .
        V
        is a rare lexical unit.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        In comparison to prior work on FrameNet, even our baseline models outperform the previous
state of the art. A particularly interesting comparison is between our
        Log-Linear Words
        baseline and the supervised model
of
        Das et al. (2014)
        . They also use a log-linear model, but they
incorporate a latent variable that uses WordNet
        [10]
        to get lexical-semantic
relationships and smooths over frames for ambiguous lexical units. It is
possible that this reduces the model’s power and causes it to over-generalize.
Another difference is that when training the log-linear model, they normalize
over all frames, while we normalize over the allowed frames for the current
lexical unit. This would tend to encourage their model to expend more of its
modeling power to rule out possibilities that will be pruned out at test time.
       </p>
      </div>
     </div>
     <div class="ltx_appendix" id="A1">
      <h2 class="ltx_title ltx_title_appendix">
       <span class="ltx_tag ltx_tag_appendix">
        Appendix A
       </span>
       Development Data
      </h2>
      <div class="ltx_para" id="A1.p1">
       <p class="ltx_p">
        Table
        7
        features a list of the 16 randomly selected
documents from the FrameNet 1.5 corpus, which we used for development. The
resultant development set consists of roughly 4,500 predicates.
We use the same test set as in
        Das et al. (2014)
        , containing 23
documents and 4,458 predicates.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
