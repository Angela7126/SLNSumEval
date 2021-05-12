<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Is this a wampimuk? Cross-modal mapping between distributional semanticsand the visual world.
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
       Following up on recent work on establishing a mapping between
vector-based semantic embeddings of words and the visual
representations of the corresponding objects from natural images, we
first present a simple approach to cross-modal vector-based
semantics for the task of
       zero-shot learning
       , in which an
image of a previously unseen object is mapped to a linguistic
representation denoting its word. We then introduce
       fast
mapping
       , a challenging and more cognitively plausible variant of
the zero-shot task, in which the learner is exposed to new objects
and the corresponding words in very limited linguistic contexts. By
combining prior linguistic and visual knowledge acquired about
words and their objects, as well as exploiting the
limited new evidence available, the learner must learn to associate
new objects with words. Our results on this task pave the way to
realistic simulations of how children or robots could use existing
knowledge to bootstrap grounded semantic knowledge about new
concepts.
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
        Computational models of meaning that rely on corpus-extracted context
vectors, such as LSA
        [31]
        , HAL
        [36]
        , Topic Models
        [20]
        and
more recent neural-network approaches
        [11, 38]
        have successfully
tackled a number of lexical semantics tasks, where context vector
similarity highly correlates with various indices of semantic
relatedness
        [53]
        . Given that these models are
learned from naturally occurring data using simple associative
techniques, various authors have advanced the claim that they might be
also capturing some crucial aspects of how humans acquire and use
language
        [31, 33]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        However, the models induce the meaning of words entirely from their
co-occurrence with other words, without links to the external
world. This constitutes a serious blow to claims of cognitive
plausibility in at least two respects. One is the
        grounding
problem
        [24, 43]
        . Irrespective of their
relatively high performance on various semantic tasks, it is debatable
whether models that have no access to visual and perceptual
information can capture the holistic, grounded knowledge that humans
have about concepts. However, a possibly even more serious pitfall of
vector models is
        lack of reference
        : natural language is,
fundamentally, a means to communicate, and thus our words must be able
to
        refer
        to objects, properties and events in the outside world
        [1]
        . Current vector models are purely
language-internal, solipsistic models of meaning. Consider the very
simple scenario in which visual information is being provided to an
agent about the current state of the world, and the agent’s task is to
determine the truth of a statement similar to
        There is a dog
in the room
        . Although the agent is equipped with a powerful
context vector model, this will not suffice to successfully complete
the task. The model might suggest that the concepts of
        dog
        and
        cat
        are semantically related, but it has no means to determine
the visual appearance of dogs, and consequently no way to verify the
truth of such a simple statement.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Mapping words to the objects they denote is such a core function of
language that humans are highly optimized for it, as shown by
the so-called
        fast mapping
        phenomenon, whereby children can
learn to associate a word to an object or property by a single
exposure to it
        [2, 8, 7, 25]
        . But
lack of reference is not only a theoretical weakness: Without the
ability to refer to the outside world, context vectors are arguably
useless for practical goals such as learning to execute natural
language instructions
        [3, 10]
        , that
could greatly benefit from the rich network of lexical
meaning such vectors encode, in order to scale up to real-life
challenges.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Very recently, a number of papers have exploited advances in automated
feature extraction form images and videos to enrich context vectors
with visual information
        [5, 16, 34, 42, 44]
        . This
line of research tackles the grounding problem: Word representations
are no longer limited to their linguistic contexts but also
encode visual information present in images associated with the
corresponding objects. In this paper, we rely on the same image
analysis techniques but instead focus on the reference problem: We do
not aim at enriching word representations with visual information,
although this might be a side effect of our approach, but we address
the issue of automatically mapping objects, as depicted in images, to
the context vectors representing the corresponding words. This is
achieved by means of a simple neural network trained to project
image-extracted feature vectors to text-based vectors through a hidden
layer that can be interpreted as a cross-modal semantic space.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We first test the effectiveness of our cross-modal semantic space on
the so-called
        zero-shot learning
        task
        [40]
        , which has recently been explored in
the machine learning community
        [18, 49]
        . In this setting, we assume
that our system possesses linguistic and visual information for a set
of concepts in the form of text-based representations of words
and image-based vectors of the corresponding objects, used for vision-to-language-mapping training.
The system is then provided with visual information for a previously
unseen object, and the task is to associate it with a word by cross-modal mapping.
Our approach is competitive
with respect to the recently proposed alternatives, while being overall
simpler.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        The aforementioned task is very demanding and interesting from an
engineering point of view. However, from a cognitive angle, it relies
on strong,
unrealistic assumptions: The learner is asked to establish a link
between a new object and a word for which they possess a full-fledged
text-based vector extracted from a billion-word corpus. On the
contrary, the first time a learner is exposed to a new object, the
linguistic information available is likely also very limited. Thus,
in order to consider vision-to-language mapping under more plausible
conditions, similar to the ones that children or robots in a new
environment are faced with, we next simulate a scenario akin to fast
mapping. We show that the induced cross-modal semantic space is
powerful enough that sensible guesses about the correct word denoting
an object can be made, even when the linguistic context vector
representing the word has been created from as little as 1 sentence
containing it.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        The contributions of this work are three-fold. First, we conduct
experiments with simple image- and text-based vector representations
and compare alternative methods to perform cross-modal mapping. Then,
we complement recent work
        [18]
        and show that
zero-shot learning scales to a large and noisy dataset. Finally, we
provide preliminary evidence that cross-modal projections can be used
effectively to simulate a fast mapping scenario, thus strengthening
the claims of this approach as a full-fledged, fully inductive theory
of meaning acquisition.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The problem of establishing word reference has been extensively
explored in computational simulations of cross-situational learning
(see
        Fazly et al. (2010)
        for a recent proposal and extended
review of previous work). This line of research has traditionally
assumed artificial models of the external world, typically a set of
linguistic or logical labels for objects, actions and possibly other
aspects of a scene
        [46]
        . Recently,
        Yu and Siskind (2013)
        presented a system that induces word-object
mappings from features extracted from short videos paired with
sentences. Our work complements theirs in two ways. First, unlike
        Yu and Siskind (2013)
        who considered a limited lexicon of 15 items
with only 4 nouns, we conduct experiments in a large search space
containing a highly ambiguous set of potential target words for every
object (see Section
        4.1
        ). Most importantly, by
projecting visual representations of objects into a shared
        semantic space
        , we do not limit ourselves to establishing a
link between objects and words. We induce a rich semantic
representation of the multimodal concept, that can lead, among other
things, to the discovery of important properties of an object even
when we lack its linguistic label. Nevertheless, Yu and Siskind’s
system could in principle be used to initialize the vision-language
mapping that we rely upon.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Closer to the spirit of our work are two very recent studies coming
from the machine learning community.
        Socher et al. (2013)
        and
        Frome et al. (2013)
        focus on zero-shot learning in the
vision-language domain by exploiting a shared visual-linguistic
semantic space.
        Socher et al. (2013)
        learn to project
unsupervised vector-based image representations onto a word-based
semantic space using a neural network architecture. Unlike us, Socher
and colleagues train an outlier detector to decide whether a test
image should receive a known-word label by means of a standard
supervised object classifier, or be assigned an unseen label by
vision-to-language mapping. In our zero-shot experiments, we assume no
access to an outlier detector, and thus, the search for the correct
label is performed in the full concept space. Furthermore, Socher and
colleagues present a much more constrained evaluation setup, where
only 10 concepts are considered, compared to our experiments with
hundreds or thousands of concepts.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Frome et al. (2013)
        use linear regression to transform
vector-based image representations onto vectors representing the same
concepts in linguistic semantic space.
Unlike
        Socher et al. (2013)
        and the current study that adopt
simple unsupervised techniques for constructing image representations,
        Frome et al. (2013)
        rely on a supervised state-of-the-art
method: They feed low-level features to a deep neural network trained
on a supervised object recognition task
        [29]
        .
Furthermore, their text-based vectors encode very rich
information, such as
        k⁢i⁢n⁢g→-m⁢a⁢n→+w⁢o⁢m⁢a⁢n→=q⁢u⁢e⁢e⁢n→
        [39]
        .
A natural question we aim to answer is whether the success of
cross-modal mapping is due to the high-quality embeddings or to
the general algorithmic design. If the latter is the case,
then these results could be extended to traditional distributional
vectors bearing other desirable properties, such as high
interpretability of dimensions.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Zero-shot learning and fast mapping
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        “We found a cute, hairy
        wampimuk
        sleeping behind the tree.”
Even though the previous statement is certainly the first time
one hears about
        wampimuks
        , the linguistic context
already creates some visual expectations: Wampimuks probably
resemble small animals (Figure
        1
        ).
This is the scenario of
        zero-shot learning
        .
Moreover, if this is also the first linguistic encounter
of that concept, then we refer to the task as
        fast mapping
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Concretely, we assume that concepts, denoted for convenience by word
labels, are represented in linguistic terms by vectors in a text-based
distributional semantic space (see Section
        4.3
        ).
Objects corresponding to concepts are represented in visual terms by vectors in an image-based
semantic space (Section
        4.2
        ).
For a subset of concepts (e.g., a set of animals, a set of vehicles),
we possess information related to both their linguistic and visual
representations.
During training, this cross-modal vocabulary is used to induce a
projection function (Section
        4.4
        ), which – intuitively –
represents a mapping between visual and linguistic dimensions. Thus, this
function, given a visual vector, returns its corresponding linguistic
representation.
At test time, the system is presented with a previously unseen object
(e.g.,
        wampimuk
        ). This object is projected onto the linguistic
space and associated with the word label of the nearest neighbor in that
space (
        degus
        in Figure
        1
        ).
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The fast mapping setting can be seen as a special case of the
zero-shot task. Whereas for the latter our system assumes that all
concepts have rich linguistic representations (i.e., representations
estimated from a large corpus), in the case of the former, new concepts
are assumed to be encounted in a limited linguistic context and therefore
lacking rich linguistic representations.
This is operationalized by constructing the
text-based vector for these concepts from a context of just
a few occurrences. In this way, we simulate the first encounter of a
learner with a concept that is new in both visual and linguistic
terms.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experimental Setup
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Visual Datasets
       </h3>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P1">
        <h5 class="ltx_title ltx_title_paragraph">
         CIFAR-100
        </h5>
        <div class="ltx_para" id="S4.SS1.SSS0.P1.p1">
         <p class="ltx_p">
          The CIFAR-100 dataset
          [30]
          consists of 60,000
32x32 colour images (note the extremely small size) representing 100
distinct concepts, with 600 images per concept. The dataset covers a
wide range of concrete domains and is organized into 20
broader categories. Table
          1
          lists the concepts
used in our experiments organized by category.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS1.SSS0.P2">
        <h5 class="ltx_title ltx_title_paragraph">
         ESP
        </h5>
        <div class="ltx_para" id="S4.SS1.SSS0.P2.p1">
         <p class="ltx_p">
          Our second dataset consists of 100K images from the ESP-Game data
set, labeled through a “game with a purpose”
          [55]
          .
          The ESP image tags form a vocabulary of 20,515 unique words. Unlike
other datasets used for zero-shot learning, it covers adjectives and
verbs in addition to nouns. On average, an image has 14 tags and a
word appears as a tag for 70 images. Unlike the CIFAR-100 images,
which were chosen specifically for image object recognition tasks
(i.e., each image is clearly depicting a single object in the
foreground), ESP contains a random selection of images from the Web.
Consequently, objects do not appear in most images in their
prototypical display, but rather as elements of complex scenes (see
Figure
          2
          ). Thus, ESP constitutes a more realistic,
and at the same time more challenging, simulation of how things are
encountered in real life, testing the potentials of cross-modal
mapping in dealing with the complex scenes that one would encounter in
event recognition and caption generation tasks.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Visual Semantic Spaces
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Image-based vectors are extracted using the unsupervised
bag-of-visual-words (BoVW) representational architecture
         [47, 12]
         , that has been widely and successfully
applied to computer vision tasks such as object recognition and image
retrieval
         [56]
         . First, low-level visual features
         [52]
         are extracted from a large collection of images
and clustered into a set of “visual words”. The low-level features
of a specific image are then mapped to the corresponding visual words,
and the image is represented by a count vector recording the number of
occurrences of each visual word in it. We do not attempt any parameter
tuning of the pipeline.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         As low-level features, we use Scale Invariant Feature Transform (SIFT)
features
         [35]
         . SIFT features are tailored to capture
object parts and to be invariant to several image transformations such
as rotation, illumination and scale change. These features are
clustered into vocabularies of 5,000 (ESP) and 4,096 (CIFAR-100)
visual words.
         To preserve spatial information in the BoVW representation, we use
the spatial pyramid technique
         [32]
         , which consists in
dividing the image into several regions, computing BoVW vectors for
each region and concatenating them.
In particular, we divide ESP images into 16 regions and the
smaller CIFAR-100 images into 4. The vectors resulting from region
concatenation have dimensionality
         5000×16=80,000
         (ESP) and
         4,096×4=16,384
         (CIFAR-100), respectively. We apply Local Mutual
Information (LMI,
         [13]
         ) as weighting scheme and reduce
the full co-occurrence space to 300 dimensions using the Singular
Value Decomposition.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         For CIFAR-100, we extract distinct visual vectors for single
images. For ESP, given the size and amount of noise in this dataset,
we build vectors for visual
         concepts
         , by normalizing and
summing the BoVW vectors of all the images that have the relevant
concept as a tag. Note that relevant
literature
         [41]
         has emphasized the importance of
learners self-generating multiple views when faced with new objects.
Thus, our multiple-image assumption should not be considered as
problematic in the current setup.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         We implement the entire visual pipeline with VSEM, an open library for
visual semantics
         [4]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Linguistic Semantic Spaces
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         For constructing the text-based vectors, we follow a standard pipeline in distributional semantics
         [53]
         without tuning its parameters and collect
co-occurrence statistics from the concatenation of
ukWaC
         and the Wikipedia,
amounting to 2.7 billion tokens in total.
Semantic vectors are constructed for a
set of 30K target words (lemmas), namely the top 20K most frequent
nouns, 5K most frequent adjectives and 5K most frequent verbs, and the
same 30K lemmas are also employed as contextual elements.
We collect co-occurrences in a symmetric context window of 20 elements around a
target word. Finally, similarly to the visual semantic space, raw
counts are transformed by applying LMI and then reduced to 300
dimensions with SVD.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Cross-modal Mapping
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         The process of learning to map objects to the their word label is
implemented by training a projection function
         fprojv→w
         from the visual onto the linguistic semantic space. For the learning,
we use a set of
         Ns
         seen
         concepts for which we have
both image-based visual representations
         𝐕s∈ℝNs×dv
         and text-based linguistic representations
         𝐖s∈ℝNs×dw
         . The
projection function is subject to an
objective that aims at minimizing some cost function between the
induced text-based representations
         𝐖^s∈ℝNs×dw
         and the gold ones
         𝐖s
         .
The induced
         fprojv→w
         is then
applied to the image-based representations
         𝐕u∈ℝNu×dv
         of
         Nu
         unseen objects to transform them
into text-based representations
         𝐖^u∈ℝNu×dw
         . We implement 4 alternative learning
algorithms for inducing the cross-modal projection function
         fprojv→w
         .
        </p>
       </div>
       <div class="ltx_paragraph" id="S4.SS4.SSS0.P1">
        <h5 class="ltx_title ltx_title_paragraph">
         Linear Regression (
         lin
         )
        </h5>
        <div class="ltx_para" id="S4.SS4.SSS0.P1.p1">
         <p class="ltx_p">
          Our first model is a very simple linear mapping between the two
modalities estimated by solving a least-squares problem. This method
is similar to the one introduced by
          Mikolov et al. (2013a)
          for
estimating a translation matrix, only solved analytically. In our
setup, we can see the two different modalities as if they were
different languages. By using least-squares regression, the projection function
          fprojv→w
          can be
derived as
         </p>
         fprojv→w=(𝐕sT⁢𝐕s)-1⁢𝐕sT⁢𝐖s

(1)
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS4.SSS0.P2">
        <h5 class="ltx_title ltx_title_paragraph">
         Canonical Correlation Analysis (
         CCA
         )
        </h5>
        <div class="ltx_para" id="S4.SS4.SSS0.P2.p1">
         <p class="ltx_p">
          CCA
          [22, 27]
          and variations thereof
have been successfully used in the past for annotation of
regions
          [48]
          and complete
images
          [21, 26]
          . Given two paired
observation matrices, in our case
          𝐕s
          and
          𝐖s
          , CCA aims at capturing the linear relationship that
exists between these variables. This is achieved by finding a pair
of matrices, in our case
          𝐂V∈ℝdv×d
          and
          𝐂W∈ℝdw×d
          , such that the
correlation between the projections of the two multidimensional
variables into a common, lower-rank space is maximized. The resulting
multimodal space has been shown to provide a good approximation to
human concept similarity judgments
          [45]
          . In our
setup, after applying CCA on the two spaces
          𝐕s
          and
          𝐖s
          , we obtain the two projection mappings onto the
common space and thus our projection function can be derived as:
         </p>
         fprojv→w=𝐂V⁢𝐂W-1

(2)
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS4.SSS0.P3">
        <h5 class="ltx_title ltx_title_paragraph">
         Singular Value Decomposition (
         SVD
         )
        </h5>
        <div class="ltx_para" id="S4.SS4.SSS0.P3.p1">
         <p class="ltx_p">
          SVD is the most
widely used dimensionality reduction technique in distributional
semantics
          [53]
          , and it has recently been
exploited to combine visual and linguistic dimensions in the multimodal
distributional semantic model of
          Bruni et al. (2014)
          . SVD
smoothing is also a way to infer values of unseen dimensions in
partially incomplete matrices, a technique that has been applied to
the task of inferring word tags of unannotated images
          [23]
          . Assuming that the concept-representing rows of
          𝐕s
          and
          𝐖s
          are ordered in the same way, we
apply the (
          k
          -truncated) SVD to the concatenated matrix
          [𝐕s⁢𝐖s]
          , such that
          [𝐕^s⁢𝐖^𝐬]=𝐔k⁢𝚺k⁢𝐙kT
          is
a
          k
          -rank approximation of the original matrix.
          The projection function is then:
         </p>
        </div>
        <div class="ltx_para" id="S4.SS4.SSS0.P3.p2">
         fprojv→w=𝐙k⁢𝐙kT

(3)
         <p class="ltx_p">
          where the input is appropriately padded with 0s (
          [𝐕u⁢𝟎N⁢u×W]
          ) and we discard the visual block of the
output matrix
          [𝐕^u⁢𝐖^u]
          .
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS4.SSS0.P4">
        <h5 class="ltx_title ltx_title_paragraph">
         Neural Network (
         NNet
         )
        </h5>
        <div class="ltx_para" id="S4.SS4.SSS0.P4.p1">
         <p class="ltx_p">
          The last model that we
introduce is a neural network with one hidden layer. The projection
function in this model can be described as:
         </p>
         fprojv→w=𝚯v→w

(4)
         <p class="ltx_p">
          where
          𝚯v→w
          consists of the model
weights
          𝜽(1)∈ℝdv×h
          and
          𝜽(2)∈ℝh×dw
          that map the
input image-based vectors
          𝐕s
          first to the hidden layer
and then to the output layer in order to obtain text-based vectors,
i.e.,
          𝐖^s=σ(2)⁢(σ(1)⁢(𝐕𝒔⁢𝜽(1))⁢𝜽(2))
          ,
where
          σ(1)
          and
          σ(2)
          are the non-linear activation
functions. We experimented with sigmoid, hyperbolic tangent and
linear; hyperbolic tangent yielded the highest performance. The
weights are estimated by minimizing the objective function
         </p>
         J⁢(𝚯v→w)=12⁢(1-s⁢i⁢m⁢(𝐖s,𝐖^s))

(5)
         <p class="ltx_p">
          where
          s⁢i⁢m
          is some similarity function. In our experiments we used
          cosine
          as similarity function, so that
          s⁢i⁢m⁢(𝐀,𝐁)=A⁢B∥A∥⁢∥B∥
          ,
thus penalizing parameter settings leading to a low cosine between the
target linguistic representations
          𝐖s
          and those produced
by the projection function
          𝐖^s
          . The cosine has been
widely used in the distributional semantic literature, and it has been
shown to outperform Euclidean distance
          [6]
          .
          Parameters were
estimated with standard backpropagation and L-BFGS.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Our experiments focus on the tasks of zero-shot learning (Sections
        5.1
        and
        5.2
        ) and fast mapping
(Section
        5.3
        ). In both tasks, the projected
vector of the unseen concept is labeled with the word associated to
its cosine-based nearest neighbor vector in the corresponding semantic
space.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        For the zero-shot task we report the
        accuracy
        of retrieving
the correct label among the top
        k
        neighbors from a semantic space
populated with the
        union of seen and unseen
        concepts. For fast
mapping, we report the
        mean rank
        of the correct concept among
fast mapping candidates.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Zero-shot Learning in CIFAR-100
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         For this experiment, we use the intersection of our linguistic space
with the concepts present in CIFAR-100, containing a total of 90 concepts.
For each concept category, we treat all concepts but one as seen
concepts (Table
         1
         ). The 71 seen concepts correspond
to 42,600 distinct visual vectors and are used to induce the projection
function. Table
         2
         reports results obtained by averaging
the performance on the 11,400 distinct vectors of the 19 unseen
concepts.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Our 4 models introduced in Section
         4.4
         are compared to a
theoretically derived baseline
         Chance
         simulating selecting a
label at random. For the neural network
         NN
         , we use prior
knowledge about the number of concept categories to set the number of
hidden units to 20 in order to avoid tuning of this parameter.
For the
         SVD
         model, we
set the number of dimensions to 300, a common choice in distributional
semantics, coherent with the settings we used for the visual and
linguistic spaces.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         First and foremost, all 4 models outperform
         Chance
         by a large
margin. Surprisingly, the very simple
         lin
         method outperforms
both
         CCA
         and
         SVD
         . However,
         NN
         , an architecture
that can capture more complex, non-linear relations in features across
modalities, emerges as the best performing model, confirming on a larger
scale the recent findings of
         Socher et al. (2013)
         .
        </p>
       </div>
       <div class="ltx_subsubsection" id="S5.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          5.1.1
         </span>
         Concept Categorization
        </h4>
        <div class="ltx_para" id="S5.SS1.SSS1.p1">
         <p class="ltx_p">
          In order to gain qualitative insights into the performance of the
projection process of
          NN
          , we attempt to investigate the role
and interpretability of the
          hidden layer
          . We achieve this by
looking at which visual concepts result in the
          highest
          hidden
unit activation.
          This is
inspired by analogous qualitative analysis conducted in Topic
Models
          [20]
          , where “topics” are interpreted in
terms of the words with the highest probability under each of them.
         </p>
        </div>
        <div class="ltx_para" id="S5.SS1.SSS1.p2">
         <p class="ltx_p">
          Table
          3
          presents both seen and unseen concepts
corresponding to visual vectors that trigger the highest activation for
a subset of hidden units. The table further reports, for each hidden unit,
the “correct” unseen concept for the category of the top seen concepts,
together with its rank in terms of activation of the unit.
The analysis demonstrates that, although
prior knowledge about categories was not explicitly used to train the
network, the latter induced an organization of concepts into superordinate
categories in which the hidden layer acts as a cross-modal concept
categorization/organization system.
When the induced projection function maps an object onto the linguistic space,
the derived text vector will inherit a mixture of textual features from
the concepts that activated the same hidden unit as the object.
This suggests a bias towards seen concepts. Furthermore, in many cases
of miscategorization, the concepts are still semantically coherent with the
induced category, confirming that the projection function is indeed capturing
a latent, cross-modal semantic space. A
          squirrel
          , although not a
“
          large
          omnivore”, is still an animal, while
          butterflies
          are not
          flowers
          but often feed on their nectar.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Zero-shot Learning in ESP
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         For this experiment, we focus on
         NN
         , the best performing model in the previous
experiment.
We use a set of approximately 9,500 concepts, the
intersection of the ESP-based visual semantic space with the
linguistic space. For tuning the number of hidden units of
         NN
         , we use the
MEN-concrete dataset of
         Bruni et al. (2014)
         . Finally, we randomly pick
70% of the concepts to induce the projection function
         fprojv→w
         and
report results on the remaining 30%. Note that the search space for
the correct label in this experiment is approximately 95 times larger than the one
used for the experiment presented in Section
         5.1
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Although our experimental setup differs from the one of
         Frome et al. (2013)
         , thus preventing a direct comparison, the
results reported in Table
         5
         are on a comparable scale to
theirs. We note that previous work on zero-shot learning has used
standard object recognition benchmarks. To the best of our knowledge,
this is the first time this task has been performed on a dataset as
noisy as ESP. Overall, the results suggest that cross-modal mapping
could be applied in tasks where images exhibit a more complex
structure, e.g., caption generation and event recognition.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Fast Mapping in ESP
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         In this section, we aim at simulating a fast mapping scenario in which
the learner has been just exposed to a new concept, and thus has
limited linguistic evidence for that concept. We operationalize this
by considering the 34 concrete concepts introduced by
         Frassinelli and Keller (2012)
         , and deriving their text-based
representations from just a few sentences randomly picked from the
corpus. Concretely, we implement 5 models:
         context 1
         ,
         context 5
         ,
         context 10
         ,
         context 20
         and
         context full
         , where the name of the model denotes the number
of sentences used to construct the text-based representations. The
derived vectors were reduced with the same SVD projection induced from
the complete corpus. Cross-modal mapping is done via
         NN
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         The zero-shot framework leads us to frame fast mapping as the task of
projecting visual representations of new objects onto language space
for retrieving their word labels (
         v→w
         ). This
mapping from visual to textual representations is arguably a more
plausible task than
         vice versa
         . If we think about how
linguistic reference is acquired, a scenario in which a learner
         first
         encounters a new object and
         then
         seeks its
reference in the language of the surrounding environment (e.g., adults
having a conversation, the text of a book with an illustration of an
unknown object) is very natural. Furthermore, since not all new
concepts in the linguistic environment refer to new objects (they
might denote abstract concepts or out-of-scene objects), it seems more
reasonable for the learner to be more alerted to linguistic cues about
a recently-spotted new object than
         vice versa
         . Moreover, once
the learner observes a new object, she can easily construct a full
visual representation for it (and the acquisition literature has shown
that humans are wired for good object segmentation and
recognition
         [50]
         ) – the more challenging task is to
scan the ongoing and very ambiguous linguistic communication for
contexts that might be relevant and informative about the new
object. However, fast mapping is often described in the psychological
literature as the opposite task: The learner is exposed to a new word
in context and has to search for the right object referring to it. We
implement this second setup (
         w→v
         ) by training
the projection function
         fprojw→v
         which
maps linguistic vectors to visual ones. The adaptation of
         NN
         is straightforward; the new objective function is derived as
        </p>
        J⁢(𝚯w→v)=12⁢(1-s⁢i⁢m⁢(𝐕s,𝐕^s))

(6)
        <p class="ltx_p">
         where
         𝐕^s=σ(2)⁢(σ(1)⁢(𝐖𝒔⁢𝜽(1))⁢𝜽(2))
         ,
         𝜽(1)∈ℝdw×h
         and
         𝜽(2)∈ℝh×dv
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         Table
         7
         presents the results. Not surprisingly,
performance increases with the number of sentences that are used to
construct the textual representations. Furthermore, all models
perform better than
         Chance
         , including those that are based on
just
         1
         or
         5
         sentences. This suggests that the system
can make reasonable inferences about object-word connections even when
linguistic evidence is very scarce.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         Regarding the sources of error, a qualitative analysis of predicted
word labels and objects as presented in Table
         6
         suggests that both textual and visual representations, although
capturing relevant “topical” or “domain” information, are not
enough to single out the properties of the target concept. As an
example, the textual vector of
         dishwasher
         contains
kitchen-related dimensions such as
         ⟨
         fridge
         ,
         oven
         ,
         gas
         ,
         hob
         , …,
         sink⟩
         . After projecting onto the visual space, its
nearest visual neighbours are the visual ones of the same-domain
concepts
         corkscrew
         and
         kettle
         . The latter is shown in
Figure
         5
         , with a
         gas hob
         well in evidence.
As a further example, the visual vector for
         cooker
         is extracted
from pictures such as the one in Figure
         5
         . Not
surprisingly, when projecting it onto the linguistic space, the
nearest neighbours are other kitchen-related terms, i.e.,
         potato
         and
         dishwasher
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
