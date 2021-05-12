<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Fractals and Ravens.
   </title>
   <abstract>
    We report a novel approach to visual analogical reasoning, one afforded expressly by fractal representations. We first describe the nature of visual analogies and fractal representations. Next, we exhibit the Fractal Ravens algorithm through a detailed example, describe its performance on all major variants of the Raven's Progressive Matrices tests, and discuss the implications and next steps. In addition, we illustrate the importance of considering the confidence of the answers, and show how ambiguity may be used as a guide for the automatic adjustment of the problem representation. To our knowledge, this is the first published account of a computational model's attempt at the entire Raven's test suite.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Despite references to its role as core to cognition [33], [35], analogy defies a singular definition [58]. In one way, analogy may be seen as a process of transference, a mapping of knowledge from one situation to another, based upon a judgment of the similarity between the two situations [12], [19], [20], [22], [23], [24], [25], [26], [27], [37], [40], [57], [67]. Gentner [24], for example, proposed that analogies entail transfer of relations from a source case to a target problem and that judgment of similarity between the target and the source depends on the correspondence between the structure of their representations. Holyoak and Thagard [37] proposed that judgments of similarity between a source case and a target problem depend on multiple criteria: structural correspondence, semantic similarity, and pragmatic constraints. Keane [40] proposed incremental mapping between the source case and the target problem. Dunbar [19] found a paradox in that humans appear to exhibit significant spontaneous use of analogies in their natural workflow but less so in laboratory settings. Kokinov and Petrov [42] describe several constraints to facilitate the integration of analogue retrieval from memory and analogical transfer. Holyoak and Hummel [36] similarly examine findings for recruiting memory, reasoning and learning in the service of analogy making. Clement [12] describes several processes of analogy such as the use of intermediate representations (or bridging analogies). Nersessian [57] similarly describes the use of generic mechanisms in scientific analogies. Our own work on model-based analogy[6], [28] has focused on the use of semantic similarity and pragmatics constraints for evaluating similarity between source cases and target problems, and identification and abstraction of generic mechanisms for transfer from a source case to a target problem in creative design [6], [28], [29].
     </paragraph>
     <paragraph>
      In contrast, case-based reasoning [1], [43], [49], [63] views within-domain analogical reasoning as a memory task in which memory supplies a source case containing an almost correct solution to the target problem. Hammond [32], for example, describes retrieval of plans based on semantic similarity to the target problem and modification of the retrieved plan to meet the target goal. Ashley and Rissland [3] describe the use of case-based reasoning in law. Smyth, Cunningham and Keane [65] describe hierarchical case-based reasoning, and Aha, Breslow and Munoz-Avila [2] describe conversational case-based reasoning. Our own work on case-based reasoning has focused in integration of case-based and model-based reasoning for adaptive design [30].
     </paragraph>
     <paragraph>
      Another line of research views analogy as a mechanism of perception, where one situation is recognized in terms of another [10], [34], [56] or as a mechanism of learning, where one situation is interpreted in terms of another [39]. Yet another line of research on analogy pertains to visual analogy [13], [14], [15], [16], [17], [69], [70]. In visual analogy, the source case and the target problem contain only modal, visual knowledge, and causality is (at most) implicit. For example, Yaner and Goel [69] describe a technique for retrieving design drawings from memory that are similar to a target drawing; Davies, Goel and Yaner [16] describe the technique of constructive analogy for incrementally transferred from the source drawing to the target drawing; and Yaner and Goel [70] describe the technique of compositional modeling that builds a causal model of the target drawing by analogy to the causal model of the source drawing.
     </paragraph>
     <paragraph>
      Each of these schools of thought emphasizes the importance of certain aspects of analogy making, and, in turn, establishes certain criteria that must be achieved by any associated methodologies through some combination of mechanism and representation. Our work concerns visual analogy, the act of forming analogies based upon purely visual perceptions, or, more formally, upon a purely visual perceptual history. We propose a new representation – the fractal representation – and corresponding mechanism for addressing a class of visual analogies that occur in computational psychometrics, and in particular, on the Raven's Progressive Matrices test of intelligence. Although we focus our remarks on representation, visual analogy, and psychometrics, we expressly make no claims as to whether our model may be extended to provide for a cognitive account.
     </paragraph>
     <section label="1.1">
      <section-title>
       Computational psychometrics
      </section-title>
      <paragraph>
       AI research on computational psychometrics dates at least as far back as Evans' Analogy program [21], which addressed geometric analogy problems on the Miller Geometric Analogies test of intelligence. Bringsjord and Schimanski [7] have proposed computational psychometrics, i.e., AI that can pass psychometric tests of intelligence, as a possible mechanism for measuring and comparing AI.
      </paragraph>
      <paragraph>
       Raven's Progressive Matrices Test suite is a set of standard and common tests of intelligence [61]. The standard version of the test consists of 60 geometric analogy problems. Fig. 1 illustrates a problem typical to those that appear on the test.{sup:1} The task in the problem is to pick one of the eight choices in the bottom of the figure for insertion in that bottom-right element of the {a mathematical formula}3×3 matrix in the top of the figure. The chosen element should best match the patterns in the rows and columns of the matrix.
      </paragraph>
      <paragraph>
       The Raven's Progressive Matrices (RPM) test paradigm is intended to measure eductive ability, the ability to extract and process information from a novel situation [61]. Eductive ability stands in contrast to reproductive ability, which is the ability to recall and use previously learned information.
      </paragraph>
      <paragraph>
       The problems from Raven's various tests are organized into five sets. Each successive set is generally interpreted to be more difficult than the prior set. Some of the problem sets are {a mathematical formula}2×2 matrices of images with six possible answers; the remaining sets are {a mathematical formula}3×3 matrices of images with eight possible answers.
      </paragraph>
      <paragraph>
       The tests are purely visual: no verbal information accompanies the tests. The test-taker is asked to select from the available possible answers the single answer that best completes the matrix [61].
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Prior approaches to RPM
      </section-title>
      <paragraph>
       Over the years, different models have proposed various combinations of representations and mechanisms for solving RPM problems. Hunt [38] gives a theoretical account of the information processing demands of certain problems from the Advanced Progressive Matrices (APM), in which he proposes two qualitatively different solution algorithms—“Gestalt,” which uses visual operations on analogical representations, and “Analytic,” which uses logical operations on conceptual representations.
      </paragraph>
      <paragraph>
       Carpenter, Just, and Shell [9] describe a computational model that simulates solving RPM problems using propositional representations. Their model is based on the traditional production system architecture, with a long-term memory containing a set of hand-authored productions and a working memory containing the current state of problem solving (e.g. current goals). Productions are based on the relations among the entities in an RPM problem, for example, the location of the dark component in a row, which might be the top half in the top row of a problem, bottom-half in the bottom row, and so on. They did not test their system on the Standard Progressive Matrices (SPM), but two different versions of their system solved 23 and 32 out of 34 attempted problems on the APM.
      </paragraph>
      <paragraph>
       Bringsjord and Schimanski [7] used a theorem-prover to solve selected RPM problems stated in first-order logic, though no results from this effort were reported.
      </paragraph>
      <paragraph>
       Lovett, Forbus and Usher [51] describe a model that extracts qualitative spatial representations from visually segmented representations of RPM problem inputs and then uses the analogy technique of structure mapping to find solutions and, where needed to achieve better analogies, to regroup or re-segment the initial inputs to form new problem representations. Again, while visual information from the RPM problems is implicit in the final representations, the structure-mapping engine is applied to these representations without any commitment to the visual nature of the encoded information. This system was tested against sets B through E of the SPM and correctly solved 44 out of 48 attempted problems.
      </paragraph>
      <paragraph>
       Cirillo and Ström [11] created a system for solving problems from the SPM that, like that of Lovett et al. [51], takes as inputs vector graphics representations of test problems and automatically extracts hierarchical propositional problem representations. Then, like the work of Carpenter et al. [9], the system draws from a set of predefined patterns, derived by the authors, to find the best-fit pattern for a given problem. This system was tested against Sets C through E of the SPM and solved 8, 10, and 10 problems, respectively.
      </paragraph>
      <paragraph>
       Schwering et al. [64] describe a gestalt method for addressing RPM problems. Rasmussen and Eliasmith [60] used a spiking neuron model to induce rules for solving RPM problems. Ragni, Stahl and Fangmeier [59] analyze the cognitive complexity of RPM problems. However, none of these report results from the addressing problems on any set of RPM problems.
      </paragraph>
      <paragraph>
       Our work on the RPM was initially motivated by trying to understand cognition in autism [45]: some individuals on the autism spectrum show RPM scores much higher than what would be predicted by their performance on other standardized IQ tests [18]. A recent neuroimaging study compared task-related brain activity between neurotypical individuals and individuals diagnosed with autism while solving RPM problems and found that, while both groups showed brain activation across a distributed network of regions, the individuals diagnosed with autism showed relatively greater activation in occipital regions, which are associated with visual processing, and relatively lower activation in prefrontal regions, associated with working memory and decision-making [66]. We analyzed behavioral and neuroimaging data across a range of cognitive tasks, including the RPM, and found that many empirical results cited in favor of other cognitive accounts of autism could be explained equally well by the hypothesis that certain individuals with autism are disposed towards thinking visually [45]. Thus, we hypothesized that it could be both feasible and useful to develop a computational model of RPM that used solely visual representations. Our first model, called the “affine” or “ASTI” model [46], [47], [48] operated directly on scanned image inputs from the test and used affine and set operations based on mental imagery (rotations, translations, image composition, etc.) to induce image transformations between images in the problem matrix and then predict an answer image based on the final induced transformation. We tested the first ASTI model on all 60 problems from the SPM and found that it correctly solves 38 of the problems.
      </paragraph>
     </section>
     <section label="1.3">
      <section-title>
       Outline of the argument in this paper
      </section-title>
      <paragraph>
       We divide our argument for the use of fractal representations and reasoning for visual analogy into three parts. In the first part, we describe the nature of visual analogies and develop fractal representations. Next, we exhibit a computational model for fractal analogical reasoning and illustrate its use through a detailed example. Lastly, we describe the performance of our model on all major variants of the Raven's Progressive Matrices tests – SPM, APM, CPM, and SPM Plus – and discuss the implications and next steps. We show that the performance of the fractal computational model matches or exceeds that of any published account. We note that all the source code and images used in these examples are readily available on our research group's website.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Visual analogies and representations
     </section-title>
     <paragraph>
      Suppose we have a visual analogy, expressed symbolically as {a mathematical formula}A:B::C:D, with the symbols representing images, as shown in Fig. 2. We can interpret this as suggesting that some operation T exists which captures the relationship between image A and image B (“A is to B”). Likewise, some other operation {a mathematical formula}T′ is proposed which captures the relationship between image C and image D (“C is to D”).
     </paragraph>
     <paragraph>
      In this manner, we may see that the analogy in such a problem rests not with the images themselves, but in the degree to which the two operations T and {a mathematical formula}T′ are analogous. We can express the problem to make plain this distinction thus:{a mathematical formula}
     </paragraph>
     <section label="2.1">
      <section-title>
       Similarity between operations
      </section-title>
      <paragraph>
       The nature of this similarity may be determined by a number of methods, many of which might associate visual or geometric features to points in a coordinate space, and compute similarity as a distance metric. Tversky developed an alternate approach by considering objects as collections of features, and similarity as a feature-matching process [68].
      </paragraph>
      <paragraph>
       We adopt Tversky's interpretation of similarity, and thus seek to express these operations T and {a mathematical formula}T′ in some representation which both is robust and affords sufficient feature production to permit feature matching [4]. A particular nuance of Tversky's approach, however, is that either the representation or the features derived from the representation must be formable into sets, as the calculation for similarity employed requires the counting of elements within sets (and their union and intersection).
      </paragraph>
      <paragraph>
       Thus, we may revisit the typical visual analogy {a mathematical formula}A:B::C:D, where T and {a mathematical formula}T′ are now representations which meet Tversky's featural requirement. To make a comparison between the two representations, we first derive features from each, and then calculate a measure of similarity based upon those features.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Similarity metric
      </section-title>
      <paragraph>
       We desire a metric of similarity that is normalized so that the value 0.0 means entirely dissimilar and the value 1.0 means identical. Accordingly, we use the ratio model of similarity as described by Tversky [68], wherein the measure of similarity between the two representations T and {a mathematical formula}T′ is calculated thus:{a mathematical formula} where the operator {a mathematical formula}F(Y) derives the number of features in some set Y. The particular sets involved may be considered as indicating, respectively, those features the two representations share ({a mathematical formula}T∩T′), those features in T but not in {a mathematical formula}T′ ({a mathematical formula}T−T′), and those features in {a mathematical formula}T′ but not in T ({a mathematical formula}T′−T).
      </paragraph>
      <paragraph>
       Tversky [68] notes that the ratio model for matching features generalizes several set-theoretical models of similarity proposed in the psychology literature (e.g. [8] and [31]), depending upon which values one chooses for the weights α and β. Later in this discussion, we shall revisit these weights, and illustrate the significance of their choice.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Fractals and the fractal representation
     </section-title>
     <paragraph>
      Benoit Mandelbrot coined the term “fractal” from the Latin adjective fractus and its corresponding verb (frangere, “to break” into irregular fragments), in response to his observation that shapes previously referred to as “grainy, hydralike, in between, pimply, pocky, ramified, seaweedy, strange, tangled, tortuous, wiggly, wispy, wrinkled, and the like” could be described by a set of compact, rigorous rules for their production [52]. Indeed, the computer graphics community has generated fractal imagery for several decades.
     </paragraph>
     <paragraph>
      While the techniques for generating artificial fractal imagery are quite well known, as Mandelbrot noted many images of real-world artifacts appear to have “fractal” properties. If these images are “fractal” in some sense, then what formula may underlie these images?
     </paragraph>
     <section label="3.1">
      <section-title>
       The mathematical basis for fractals as operations
      </section-title>
      <paragraph>
       As we have noted previously [55], the mathematical derivation of fractal representation as an operation over images expressly depends upon the notion of real world images, i.e. images that are two dimensional and continuous [5]. Every image received by the human visual system may be construed as meeting this requirement, with the proviso that the notion of continuity has a resolution limit, and that limit plays a significant role in visual abstraction, as shall be discussed later in this paper.
      </paragraph>
      <paragraph>
       Of particular relevance are two observations about images themselves, made by Mandelbrot [52]. The first is that all naturally occurring images appear to have similar, repeating patterns. The second observation is that no matter how closely one examines the real world, one may find instances of similar structures and repeating patterns. These observations suggested to Barnsley and Hurd [5] that it is possible to describe images in terms that capture the observed similarity and repetition alone, without regard to shape or traditional graphical elements.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Collage theorem
      </section-title>
      <paragraph>
       Computationally, the determination of the fractal representation of an image can be performed through the use of the fractal encoding algorithm. The collage theorem [5] at the heart of the algorithm can be stated concisely: For any particular real world image, there exists a finite set of affine transformations which, if applied repeatedly and indefinitely to any other real world image, will result in the convergence of the latter into the former. It is important to note that the collage theorem is describing a set of transformations that are derived by mapping an image into another. In other words, fractal encoding determines an iterated function system that is applied repeated to some source image, with the result that the encoded image emerges.
      </paragraph>
      <paragraph>
       Suppose {a mathematical formula}F() is the fractal encoding of image B. Then, given any other image A:{a mathematical formula}{a mathematical formula}F() is itself a finite set of affine transformations T that describe how to modify portions of an image such that convergence is assured.{a mathematical formula} Each affine transformation may affect some or all of the given image, but it is the unordered union of their actions that comprises the resultant image. Thus:{a mathematical formula}
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Dependencies
      </section-title>
      <paragraph>
       There are several, interrelated dependencies implied in the Collage theorem. These are specificity, partitioning, and search. We shall describe each in turn now, in the context of the theorem, and later, in the context of the algorithm and the subsequent representation.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Dependency upon the specificity of the source and the destination
       </section-title>
       <paragraph>
        A fractal encoding is dependent not only upon the destination image, but also upon the source image, from which the set of affine transformations T is discovered. However, once the fractal encoding has been determined, the application of that encoding to any source image will result in the target image. This dependency is to suggest that, a priori any application of the encoding, a particular fractal encoding is determined uniquely by a particular source image.
       </paragraph>
      </section>
      <section label="3.3.2">
       <section-title>
        Dependency upon the partitioning of the destination image
       </section-title>
       <paragraph>
        The cardinality of set of transformations is determined exactly and solely by the partitioning scheme chosen for the image being encoded. It is presumed that the image being encoded admits to being partitioned in some manner, however.
       </paragraph>
       <paragraph>
        Images may be partitioned using a variety of methods. In computer vision, one typically seeks to segment an image into regions or shapes [62], [71]. Another segmentation scheme would seek to segregate an image into two segments, a foreground and a background [41]. Other partitionings of images may be regular, such as the division of computer-based images into pixels, at some resolution. It must be noted that the choice of partitioning scheme affects the computational complexity of enacting the partitioning.
       </paragraph>
       <paragraph>
        The Collage theorem imposes no constraint upon the choice of partitioning save one, and that is that the union of all partitions wholly covers the image to be encoded. From a topological perspective, the image B is treated as a set, and the partitioning {a mathematical formula}P() of that image into a finite collection of subsets is a cover of that set if:{a mathematical formula}{a mathematical formula}
       </paragraph>
      </section>
      <section label="3.3.3">
       <section-title>
        Dependency upon the search of the source image
       </section-title>
       <paragraph>
        The essential implied step of the Collage theorem is that there is a match for each subimage of the destination, as determined by the partitioning, to be sought within the source image. Through this searching process, the affine transformation for that subimage is obtained. However, the quality and character of the match, as well as the computational complexity of the algorithm, depends upon the constraints selected for comparing the destination subimage with some portion of the source.
       </paragraph>
      </section>
     </section>
     <section label="3.4">
      <section-title>
       Fractal encoding algorithm
      </section-title>
      <paragraph>
       Given a target image B and a source image A, the fractal encoding algorithm seeks to discover this particular set of transformations T.
      </paragraph>
      <paragraph>
       As can be seen in Algorithm 1, the fractal encoding of image B in terms of image A consists of two phases: partitioning and searching. We shall now discuss each phase.
      </paragraph>
      <section label="3.4.1">
       <section-title>
        Partitioning
       </section-title>
       <paragraph>
        The target image B is first partitioned into a set of other images. As we are dealing with computer images, we may safely assume that the image B will have some finite resolution, and thus a limit as to the smallest achievable partition. Practically, this smallest resolvable unit is a unitary pixel, which would denote both a spatial location and a photometric value.
       </paragraph>
       <paragraph>
        As we noted above, the Collage theorem places a topological constraint on the partitioning scheme, and requires that the scheme should act as a topological cover over the image B. Such a constraint admits a wide variety of methods for partitioning the image, but many of these partitionings may prove computationally expensive.
       </paragraph>
       <paragraph>
        In the interest of reducing computational complexity, we may impose two additional constraints: each subimage in the partition must be simply connected to at least one other subimage, and the union of all of the subimages must be exactly equivalent to the image B. Stated formally:{a mathematical formula} where{a mathematical formula} One computationally inexpensive way to achieve such a constrained partitioning is to impose upon the image B a uniform, rectilinear grid, and select the subimages based upon some chosen grid size, as expressed in units of pixels.
       </paragraph>
       <paragraph>
        Thus, a stronger specification of the fractal encoding T may be thought of as a function of three variables, the source image A, the target image B, and the partitioning scheme P:{a mathematical formula} where the cardinality of the resulting set is determined solely by the partitioning P. That is, each subimage {a mathematical formula}bi that P extracts from B will be represented by exactly one element of the set T.
       </paragraph>
      </section>
      <section label="3.4.2">
       <section-title>
        Partitioning and level of detail
       </section-title>
       <paragraph>
        Choosing a partitioning determines the level of detail at which an image is encoded. Thus, the coarsest level of detail possible for an image is the partitioning into a single image (the whole image). The finest level of detail achievable is that set of images wherein each image is but a single pixel.
       </paragraph>
       <paragraph>
        The choosing of a grid size, and of a partitioning in general, may be interpreted as an indication of the level of detail at which an image may be encoded. Fig. 3 illustrates the effect of partitioning an image into a variety of levels of detail, using a regular rectangular grid.
       </paragraph>
       <paragraph>
        The ability to express level of detail as an artifact of partitioning, whether by controlling grid size, by altering the consistency of partition size, or by modification of the shape and nature of the underlying regions and their spatial arrangement (i.e. hexagonal versus rectilinear scaffolding, or polar versus Cartesian coordinates) is an important aspect of the encoding, and a key feature entailed by the fractal representation.
       </paragraph>
      </section>
      <section label="3.4.3">
       <section-title>
        Searching
       </section-title>
       <paragraph>
        The partitioning scheme P extracts a set of images {a mathematical formula}bi from the target image B. The next step of the algorithm is to perform a systematic examination of the source image A for fragments of A that can be said to best match a particular image {a mathematical formula}bi. The method by which the search is conducted may be varied, as can the meaning of what is said to be a “best match.”
       </paragraph>
       <section label="3.4.3.1">
        <section-title>
         Global and local coordinates
        </section-title>
        <paragraph>
         An image {a mathematical formula}bi extracted by the partitioning scheme can be considered as a region containing a number of pixels that are addressable in some fashion. The addressability of these pixels may be viewed as a local coordinate system imposed upon the region. Additionally, the region described by the image {a mathematical formula}bi has a location and orientation within the image B, strictly determined by the partitioning scheme. Thus, we may consider the image {a mathematical formula}bi as an ordered set of pixels, having both a local (intrinsic) coordinate system and extent, and a position and orientation within a global (within image B) coordinate system. Fig. 4 illustrates the local and global coordinate systems.
        </paragraph>
        <paragraph>
         However, the same partitioning scheme necessarily does not need to be applied to the source image. The entire source image A may be examined in any manner for a fragment that most closely matches {a mathematical formula}bi.
        </paragraph>
       </section>
       <section label="3.4.3.2">
        <section-title>
         Discovering the “best match”
        </section-title>
        <paragraph>
         The source image A is examined to determine which fragment of it, which we shall label {a mathematical formula}ak, can be said to “best match” the sought-for image {a mathematical formula}bi from the target image B. That is, the correspondence between {a mathematical formula}ak and {a mathematical formula}bi can be said to be “best” if it is the minimum value of the following function:{a mathematical formula} where AdmissibleTransformations is a finite set of spatial transformations applied by the operator Transform() to the pixel values contained within {a mathematical formula}ak, and PhotometricCorrespondence() is a pixel comparison operation. We shall define both of these momentarily.
        </paragraph>
       </section>
       <section label="3.4.3.3">
        <section-title>
         Photometric correspondence
        </section-title>
        <paragraph>
         The photometric correspondence between the fragment {a mathematical formula}ak from the source image and {a mathematical formula}bi from the destination image is calculated to be the difference between the photometric values found in those fragments under a given alignment of their pixels. We wish to propose a metric to ensure that this difference would be 0 if the two fragments were identical photometrically. Such an algorithm to calculate the photometric correspondence is given by Algorithm 2.
        </paragraph>
        <paragraph>
         The corresponding pixel in {a mathematical formula}ak is determined by imposing the same local coordinate system used in {a mathematical formula}bi upon {a mathematical formula}ak.
        </paragraph>
        <paragraph>
         The Photometric value of a pixel used in this calculation may vary according to the nature of the image itself. For example, if the image is in full color, the photometric value may be a triplet of actual values; if the image is monochromatic, then the photometric value will be single valued. Since it is desired to calculate a photometric correspondence that is single-valued, a mapping from multivariate photometry to a single value is typically employed. This can be seen, globally, as mapping from one color space into another. For example, to reconcile traditional computer graphics images given in triplets of red, green, and blue values into single grayscale values, a formula such as this may be used, which seeks to equate the colorimetric luminance of the RGB image to a corresponding grayscale rendition [54]:{a mathematical formula} Careful consideration of the underlying photometric nature of the image being encoded therefore must be given, but only at this particular moment in the overarching algorithm for encoding. The choice of the Photometric() function determines the interrelationship of the image's colorimetry and its constituent importance to the matching function.
        </paragraph>
       </section>
       <section label="3.4.3.4">
        <section-title>
         Affine transformations
        </section-title>
        <paragraph>
         The fractal encoding algorithm seeks to find the best matching fragment in a source image that corresponds to a given image partitioned from the target image. As shown above, this matching is achieved by calculating the photometric correspondence function between two fragments, while considering all admissible transformations of the fragment from the source. The set of admissible transformations is a subset of affine transformations known as similitude transformations.
        </paragraph>
        <paragraph>
         An affine transformation, in two dimensions, may be considered to be of the form:{a mathematical formula} where {a mathematical formula}a,b,c,d,e, and f are all real numbers. This equation, which maps one point in a two-dimensional plane into another point in a two-dimensional plane, may be rewritten into matrix form like so:{a mathematical formula} In this way it can be seen that an affine transformation is a combination of a linear transformation followed by a translation.
        </paragraph>
        <paragraph>
         Not all affine transformations are admissible for the fractal encoding transform, however. In particular, those that are admissible must be invertible [5]. Intuitively, this means that each point in space can be associated with exactly and only one other point in space. Mathematically, this means that the inverse has this form:{a mathematical formula} and the denominator must not be equal to zero to satisfy invertibility.
        </paragraph>
       </section>
       <section label="3.4.3.5">
        <section-title>
         Similitude transformations
        </section-title>
        <paragraph>
         An important group of affine transformations are those that are called similitudes [5].
        </paragraph>
        <paragraph>
         A similitude transformation may be expressed in one of these two forms:{a mathematical formula}{a mathematical formula} Thus, a similitude transformation is a composition of a dilation factor r, an orthonormal transformation (a rotation about the angle θ where {a mathematical formula}0≤θ&lt;2π), and a translation {a mathematical formula}(e,f). Similitude transformations are invertible except when {a mathematical formula}r=0.
        </paragraph>
       </section>
       <section label="3.4.3.6">
        <section-title>
         Defining the AdmissibleTransformations set
        </section-title>
        <paragraph>
         Given this formulation for similitude transformations, one can imagine having to consider a great many potential rotational angles to find the best match. Indeed, the computational complexity of the encoding would seem a function of the angles under consideration. In practice, we find that we may limit ourselves to considering only eight of these orthonormal transformations, as shown in Fig. 5.
        </paragraph>
        <paragraph>
         Consider the smallest region of pixels for which orthonormal transformations upon those pixels would result in a visible change. The size of this region is an area two pixels wide by two pixels high. This small region has four lines of symmetry. Taking into account each line of symmetry, and reflecting the pixels in the region about each in turn, we find that there are eight possible outcomes.
        </paragraph>
        <paragraph>
         Our implementation of the fractal encoding algorithm examines each potential correspondence under each of these possible transformations. These form the set of admissible transformations. The transformation from this set that yields the best photometric correspondence is noted by the search algorithm.
        </paragraph>
       </section>
       <section label="3.4.3.7">
        <section-title>
         Translation arises from searching
        </section-title>
        <paragraph>
         The searching process examines each potential fragment in a given source image for correspondence to a particular fragment of the target image. Let us presume that we may align the coordinate systems of the source and the target images such that their origins exactly coincide. Then, the relative location of a potential fragment in the source image can be mapped to a location within the target image. This mapping, from the potential fragment's local origin to the particular fragment's local origin, is a translation, and it is this mapping that forms the translation portion of the sought-for similitude transformation.
        </paragraph>
       </section>
       <section label="3.4.3.8">
        <section-title>
         Dilation and fractals
        </section-title>
        <paragraph>
         Taken together, the orthonormal transformation and the translation provide a sufficient means for describing self-similarity that may exist within an image. However, that self-similarity is not quite sufficient for describing how the similarity may occur at different levels of detail. The dilation factor, r, is used to invoke a contraction of space, whenever {a mathematical formula}r&lt;1.0. The fractal encoding algorithm prescribes that the dilation factor to be used when searching may be conveniently set as {a mathematical formula}r=0.5. In practice, this entails that the source image, as a whole, may be scaled to one-half its original size, and then searched for photometrically corresponding fragments.
        </paragraph>
        <paragraph>
         Mathematically, choosing {a mathematical formula}r&lt;1.0 ensures that the encoding derived for the entire image, if applied successively and indefinitely to an image, will cause the resulting image to converge upon the desired destination image [5].
        </paragraph>
       </section>
       <section label="3.4.3.9">
        <section-title>
         Colorimetric contraction
        </section-title>
        <paragraph>
         As a final step, having located the best photometrically corresponding source fragment, the algorithm determines a rate at which the two regions may be brought into colorimetric harmony. To do this, the average colorimetric description of both regions is calculated, and the distance between the two is multiplied by a dilation. The formula our present implementation uses to calculate the colorimetric contraction is:{a mathematical formula} where the colorMean of a region is the average of all colorimetric information available in that region, taking into account the multivariate nature of the underlying image as previously discussed. The derivation of the colorimetric dilation factor of 0.75 is given by Barnsley and Hurd [5], and is shown to be correlated to the spatial dilation factor of 0.5.
        </paragraph>
       </section>
       <section label="3.4.3.10">
        <section-title>
         Exhaustive searching
        </section-title>
        <paragraph>
         The search over the source image A for a matching fragment is exhaustive, in that each possible correspondence {a mathematical formula}ak is considered regardless of its prior use in other discovered transforms. By allowing for such reuse, the algorithm affords the first Mandelbrot fractal observation, the notion of repetition.
        </paragraph>
       </section>
       <section label="3.4.3.11">
        <section-title>
         Refining correspondence
        </section-title>
        <paragraph>
         We note that there may be many fragments in the source image which may have identical photometric correspondence to the sought for fragment {a mathematical formula}bi (for example, when all of the values in the two fragments are identical). To break these potential ties, a further refinement of the correspondence function is necessary.
        </paragraph>
        <paragraph>
         We compute a simple distance metric upon the images, and give it a weighting. Thus, the correspondence calculated between two fragments becomes:{a mathematical formula} where the weights {a mathematical formula}w1 and {a mathematical formula}w2 are chosen such that the calculation of correspondence is dominated by the value of the photometric correspondence. This can be ensured if the following relationship is held:{a mathematical formula} where maximalDistance is the longest possible distance between the origins of {a mathematical formula}bi and any fragment in the corresponding source image, and minimalJustNoticeablePhotometric is the PhotometricCorrespondence which would be calculated if the photometric difference between {a mathematical formula}bi and any fragment were so small as to be indistinguishable. Practically, we set this value such that this is as small as possible yet not zero, given the color system used in the images. For example, for 8-bit greyscale images where the value 0 represents “black” and the value 255 represents “white,” the minimalJustNoticeablePhotometric would be set to a value of 1.
        </paragraph>
       </section>
      </section>
      <section label="3.4.4">
       <section-title>
        Fractal codes
       </section-title>
       <paragraph>
        For each image {a mathematical formula}bi taken from a partitioning of the target image B, the fractal encoding algorithm locates, via exhaustive search over the source image A, a corresponding fragment {a mathematical formula}ak which the algorithm has deemed to be most minimally distant photometrically under a discovered transformation. The algorithm constructs a description of its discoveries, in a representation called a fractal code. A fractal code consists of six elements, as shown in Table 1.
       </paragraph>
       <paragraph>
        Note that the dilation factor, for both spatial and photometric properties, is not represented here. This is for efficiency, as these dilations are presumed to be global.
       </paragraph>
       <paragraph>
        Further efficiencies of expression also may be found by dropping the colorimetric operation (a way of describing how the colorimetric contraction value is to be combined into the region). Since the set of orthonormal transformations the search mechanism uses is finite, we may represent the transformation as a referent to that transformation's ordinal membership in the set. The size and shape of the region may be reduced itself, if the partitioning of the image is regular. In our implementation, we use a regular, uniform partitioning, which forms a grid. Thus, we can express the size and shape of the region with a single integer, which represents the width and height of the region in pixels.
       </paragraph>
      </section>
      <section label="3.4.5">
       <section-title>
        Arbitrary selection of source
       </section-title>
       <paragraph>
        The choice of source image A is arbitrary. Indeed, the target image B may be fractally encoded in terms of itself, by substituting B for A in the above algorithm. Although one might expect that this substitution would result in a trivial encoding (in which all fractal codes correspond to an identity transform), this is not the case, a fractal encoding of B will converge upon B regardless of chosen initial image. For this reason, the size of source fragments considered is taken to be twice the dimensional size of the target image fragment, resulting in a contractive affine transform. Similarly, as shown above, color shifts are made to contract. This contraction, enforced by setting the dilation of spatial transformations at 0.5, provides the second key fractal observation, that similarity and repetition occur at differing scales.
       </paragraph>
      </section>
      <section label="3.4.6">
       <section-title>
        Arbitrary ordinality of encoding
       </section-title>
       <paragraph>
        The ordinality of the set of fractal codes that comprise a fractal representation is similarly arbitrary. The partitioning P may be traversed in any order during the matching step of the encoding algorithm. Similarly, once discovered, the individual codes may be applied in any order, so long as all are applied in any particular iteration.
       </paragraph>
      </section>
      <section label="3.4.7">
       <section-title>
        Fractal representation is fractal encoding
       </section-title>
       <paragraph>
        The fractal encoding algorithm, while computationally expensive in its exhaustive search, represents the relationship between two images (or between an image and itself) as a much smaller set of fractal codes, an instruction set for reconstituting the relationship, with inherently strong spatial and photometric correspondence. It is through this encoding that the fractal representation of the relationship between those two images is derived. Indeed, the fractal representation is the fractal encoding.
       </paragraph>
      </section>
     </section>
     <section label="3.5">
      <section-title>
       Features from fractals
      </section-title>
      <paragraph>
       The fractal representation of an image is an unordered set of fractal codes, which compactly describe the geometric alteration and colorization of fragments of the source image that will collage to form the target image. While it is tempting to treat contiguous subsets of these fractal codes as features, we note that their derivation does not follow strictly Cartesian notions (e.g. adjacent material in the destination might arise from non-adjacent source material). Accordingly, we consider each of these fractal codes independently, and construct candidate fractal features from the individual codes themselves, and not from clusters of codes.
      </paragraph>
      <paragraph>
       Each fractal code yields a small set of features, formed by constructing subsets of its underlying six-tuple. These features are determined in a fashion to encourage spatial- and photometric-agnosticism, as well as specificity. Our algorithm creates features from fractal codes by constructing subsets of each of the six members of the fractal code's tuple.
      </paragraph>
      <paragraph>
       We further chose to represent each feature as a concatenated string in memory. We form these strings by attaching a character tag to each field in the fractal code and then converting that field into string format prior to concatenation, like so:{a mathematical formula} The choice of the particular tag is arbitrary, but tagging itself is not: tagging is necessary to avoid in-string matching between the different kinds of fields (e.g. a numerical value may appear in multiple fields of a fractal code). Doing so attributes a world grounding to each field, and collectively to the entire fractal code.
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       Mutuality
      </section-title>
      <paragraph>
       The analogical relationship between source and target images may be seen as mutual; that is, the source is to the destination as the destination is to the source. However, the fractal representation is decidedly one-way (e.g. from the source to the destination). To capture the bidirectional, mutual nature of the analogy between source and destination, we now introduce the notion of a mutual fractal representation. Let us label the representation of the fractal transformation from image A to image B as {a mathematical formula}TAB. Correspondingly, we would label the inverse representation as {a mathematical formula}TBA. We shall define the mutual analogical relationship between A and B by the symbol {a mathematical formula}MAB, given by this equation:{a mathematical formula} By exploiting the set-theoretic nature of fractal representations {a mathematical formula}TAB and {a mathematical formula}TBA to express {a mathematical formula}MAB as a union, we afford the mutual analogical representation the complete expressivity and utility of the fractal representation.
      </paragraph>
     </section>
     <section label="3.7">
      <section-title>
       Extended mutuality
      </section-title>
      <paragraph>
       We note that the mutual fractal representation of the pairings may be employed to determine similar mutual representations of triplets, quadruplets, or larger groupings of images. As a notational convention, we construct these additional representations for triplets ({a mathematical formula}Mijk) and quadruplets ({a mathematical formula}Mijkl) in a like manner:{a mathematical formula}{a mathematical formula} Thus, in a mutual fractal representation, we have the necessary apparatus for reasoning analogically about the relationships between images, in a manner that is dependent upon only features that describe the mutual visual similarity present in those images.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      A strategy for visual analogies
     </section-title>
     <paragraph>
      As we noted at the paper's outset, we can interpret visual analogies as suggesting that some operation T exists that captures the relationship between image A and image B (“A is to B”). Likewise, some other operation {a mathematical formula}T′ is proposed which captures the relationship between image C and image D (“C is to D”).
     </paragraph>
     <paragraph>
      Let us now consider a class of visual analogy puzzles, an example of which is shown in Fig. 6.
     </paragraph>
     <paragraph>
      In this problem, the image D is missing, and the challenge is to determine which of the offered candidate images would best fit into the matrix. That is, we must determine which of these candidate images, if selected as image D, would establish transformation {a mathematical formula}T′ as most analogous to transformation T.
     </paragraph>
     <paragraph>
      Analogies in a general sense are based on similarity and repetition e.g. [34]. We would seek to employ a suitable representation, one that affords the capture of these qualities as well as sanctions reasoning over them. As we showed in the prior sections of this paper, fractals capture self-similarity and repetition at multiple scales [52], and we propose that fractal representations are an appropriate choice for addressing certain classes of analogy problems.
     </paragraph>
     <paragraph>
      One method for solving this puzzle is this: from this set of candidates, we may form the fractal representations from the fractal encoding of the transformation of each candidate image X in terms of image C.{a mathematical formula}{a mathematical formula} This provides a set of possible transformations, which we shall label Ω, from which to seek the most analogous transformation {a mathematical formula}T′ and thereby find which candidate image was responsible for it.
     </paragraph>
     <section label="4.1">
      <section-title>
       The generality of representations
      </section-title>
      <paragraph>
       We wish to note that while in this paper we exclusively shall use fractal representations in our examples and subsequent discussion, our overall approach is agnostic with respect to representations, and may be used with any representation that affords the ability for objects thus represented to be decomposed into a set of features. The approach is distinguished from other analogical algorithms in that it presumes no explicit relationship between objects or between features of objects.
      </paragraph>
      <section label="4.1.1">
       <section-title>
        Preliminary remarks
       </section-title>
       <paragraph>
        Our approach compares each transform in the set Ω to the original transform T by means of recalling common features and calculating similarity metrics. First, however, we must make a few remarks on our present implementation. We chose data structures that facilitate the storage and retrieval of information based upon aspects of the data, specifically by using a hash table as a data structure surrogate for memory. As we will be hashing transformations into memory, we define two additional operators: {a mathematical formula}F(), a method to generate a set of features from a given transformation; and {a mathematical formula}K(), an injective hash function which operates solely over the domain of the features.
       </paragraph>
       <paragraph>
        We made the commitment to a hash table for two reasons beyond that of wishing to use features. First, we note that it is desirous to find some overlap in the features that occur between two transformations, such that a perfect overlap would deem the transformations perfectly analogous. The hash function {a mathematical formula}K() may result in hashing multiple transformations to the same feature, and therefore {a mathematical formula}K() must operate only upon a given feature, and not take into consideration the transformation which gave rise to that feature. Second, {a mathematical formula}F(), the method which generates features from a transformation, must do so in a manner such that each generated feature affords salience, or information content [68].
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        Indexing features
       </section-title>
       <paragraph>
        We wish to store each transformation in the hash table memory M. The set of possible analogous transformations Ω is combined with the original transformation T to form a new set {a mathematical formula}Ω⁎. The algorithm iterates over each member {a mathematical formula}τ∈Ω⁎, and from each member calculates a set of features using {a mathematical formula}F(τ). For each feature {a mathematical formula}fi∈F(τ), the transformation is indexed as an ordered pair ({a mathematical formula}K(fi), τ). That there likely will be hash collisions at key value {a mathematical formula}K(fi) is expected and desired.
       </paragraph>
      </section>
      <section label="4.1.3">
       <section-title>
        Calculating similarity
       </section-title>
       <paragraph>
        We must determine a measure of similarity between the original transformation T and each possible analogous transformation {a mathematical formula}Ti∈Ω. Our choice of metric reflects similarity as a comparison of the number of features shared between candidate pairs taken in contrast to the joint number of features found in each pair member [30]. We desire a metric that is normalized with respect to the number of features under consideration. In our implementation, the measure of similarity between the target transform T and a candidate transform {a mathematical formula}Ti is calculated using the ratio model [68]:{a mathematical formula} and {a mathematical formula}F(Y) is a function that determines the number of features that may be extracted from the set Y. We may calculate these values effectively, using hash table retrieval as a surrogate for distinguishing and counting common and distinct features within the sets {a mathematical formula}T∩Ti, {a mathematical formula}T−Ti, and {a mathematical formula}Ti−T respectively.
       </paragraph>
       <paragraph>
        Tversky notes that the ratio model for matching features generalizes several set-theoretical models of similarity proposed in the psychology literature, depending upon which values one chooses for the weights α and β[30]. We have found that significant discrimination between candidate answers may be found by using the Jaccard similarity; that is, by setting {a mathematical formula}α←β←1.0, and thus favoring features from either transformation equally. As Tversky notes, by equating α and β, we ensure that the calculation of similarity is symmetric with respect to the transformations under comparison.
       </paragraph>
       <paragraph>
        Once the algorithm has calculated the similarity function over all candidate transforms, it is a straightforward matter to determine which transformation has generated the maximal similarity. This transformation, {a mathematical formula}T′, is deemed by way of Tversky featural similarity, to be the most analogous to the original transformation T.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       An example
      </section-title>
      <paragraph>
       We now present an example of using fractal representations and our strategy to solve the visual analogy puzzle shown in Fig. 3 above.
      </paragraph>
      <section label="4.2.1">
       <section-title>
        The primary and candidate transformations
       </section-title>
       <paragraph>
        In this example, the problem is to determine for which of the candidate images the transformation {a mathematical formula}T′ is made most analogous to transformation T. We first will represent T as a fractal representation, and then generate a set of candidate transformations Ω as shown in Fig. 7.
       </paragraph>
       <paragraph>
        We arbitrarily may select any partitioning scheme, so long as that partitioning meets the criteria of coverage outlined above. For the purpose of this example, let us choose to partition each image into a series of {a mathematical formula}16×16 pixels, forming a regular grid. Each of our images is 134 pixels wide and 84 pixels high. Thus, each image is to be partitioned into 54 blocks.
       </paragraph>
       <paragraph>
        Each of these blocks will be represented by a single fractal code. In our present implementation, each fractal code generates 63 features. Therefore, at this partitioning, each primary transformation will be indexed into memory using the {a mathematical formula}54×63×2=6804 features generated from mutual fractal representation of that transformation.
       </paragraph>
      </section>
      <section label="4.2.2">
       <section-title>
        Calculating similarities and selecting the most analogous
       </section-title>
       <paragraph>
        After the primary transformation T is indexed into memory using features derived from the fractal codes, we may calculate a similarity value for each of the candidate transformations in the set Ω, using the Tversky formula as noted. Table 2 illustrates the values calculated for each of the candidate transformations.
       </paragraph>
       <paragraph>
        It may be seen that the fourth transformation is the most similar to the primary transformation T, with a value of 0.842. Therefore, for this puzzle, the answer is candidate answer 4.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Tackling Ravens with fractals
     </section-title>
     <paragraph>
      With this strategy in mind, let us illustrate the use of fractal representations for solving Raven's matrices problems. We shall use by way of example the {a mathematical formula}3×3 matrix problem shown in Fig. 1.
     </paragraph>
     <section label="5.1">
      <section-title>
       Simultaneous relationships, multiple constraints
      </section-title>
      <paragraph>
       An aspect of any Raven's problem, whether {a mathematical formula}2×2 or {a mathematical formula}3×3, is that there exist simultaneous horizontal and vertical relationships which must be maintained by the selection of the most analogous answer. In a {a mathematical formula}2×2 problem, there is one horizontal relationship and one vertical relationship that constrain the selection. In a {a mathematical formula}3×3 problem, there are two horizontal and two vertical relationships. In our implementation, we represent these relationships as mutual fractal representations.
      </paragraph>
      <paragraph>
       In Fig. 8, we illustrate these relationships using our example problem. As shown, relationships H1 and H2 constrain relationship H, while relationships V1 and V2 constrain relationship V. We note that there are other possible relationships that may be suggested by this problem: we have chosen to focus on these particular four relationships for clarity.
      </paragraph>
      <paragraph>
       To solve a Raven's problem, one must select the image from the set of possible answers for which the similarity to each of the problem's relationships is maximal. For our example, this involves the calculation of a set of similarity values {a mathematical formula}Θi for each answer {a mathematical formula}Ai:{a mathematical formula} where {a mathematical formula}S(X,Y) is the Tversky similarity between two sets X and Y, and {a mathematical formula}H(Ai) and {a mathematical formula}V(Ai) denote the relationship formed when the answer image {a mathematical formula}Ai is included.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Reconciling multiple analogical relationships
       </section-title>
       <paragraph>
        For each candidate answer, we consider the similarity of each potential analogical relationship as a value upon an axis in a large “relationship space.” The dimensionality of this space is determined by the problem at hand. Thus, for a {a mathematical formula}2×2 Raven's problem, the space is 2-dimensional; for a {a mathematical formula}3×3 Raven's problem, the space is 4-dimensional, using the relationships as shown above.
       </paragraph>
       <paragraph>
        We would like to determine a single value for the similarity. To do so, we treat these multidimensional sets as a vector, and determine its length, using a Euclidean distance formula:{a mathematical formula} Thus, the longer the vector, the more similar; the shorter the vector, the more dissimilar.
       </paragraph>
       <paragraph>
        Generally, we currently do not favor any particular relationship; that is, we do not, as an example, weight more decisively those values we find upon the horizontal relationships over those upon the vertical relationships. We note that giving preferential weighting to a relationship is a straightforward extension to the calculation above, but we also note that choosing which relationship to prefer may be non-trivial.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Confidence
      </section-title>
      <paragraph>
       As illustrated by the example above, a candidate representation can be found to be the most analogous by a straightforward calculation of its featural similarity, using the Tversky formula [68]. But a question quickly arises: how confident is the answer? That is, given the variety of answer choices, even though an answer may be selected based on maximal similarity, how may that choice be contrasted with its peers as the designated answer?
      </paragraph>
      <paragraph>
       A potential path would be to assess the given similarity calculation as a member of the set of all such similarity calculations for the collection of potential answers. Let us suppose that for a given collection of answers, we use a strategy such as ours to calculate a corresponding set of similarity values:{a mathematical formula} We may then select{a mathematical formula} as the maximal similarity value, and thereby deem the answer which generated that value as the most analogous. We may determine, additionally, how statistically distinct the value ζ is from its peers, by first calculating the mean, standard deviation, and standard error of the mean for the set of similarity values, and then, assuming a normal distribution, calculating the deviation of each of the values from the mean of the set:{a mathematical formula}{a mathematical formula} then{a mathematical formula} where the set Deviations is a t-distribution of the similarity values. We surmise that the most analogical answer, the one corresponding to the maximal similarity value ζ, would have the largest positive deviation value under this reformulation:{a mathematical formula} This, then, suggests that the most analogical answer would in a sense “stand apart” from the rest of the answers. The degree to which it “stands apart” may be interpreted as a metric of confidence in selecting the answer. Indeed, assuming a normal distribution, we may calculate a confidence interval based upon the standard deviation, and score each of these values along such a confidence scale, where 0.0 would indicate no variation at all from the answer, and 1.0 would indicate an utterly apparent and distinct value. Thus, the problem of selecting the most analogous answer is transformed into a problem of distinguishing which of the possible answers is a statistical outlier.
      </paragraph>
      <paragraph>
       Since the set of deviations determined is a t-distribution of the similarity values, the choice of a level of confidence in selecting the answer can be made using conventional statistics. If we assume a normal distribution of the deviations, then we may devise an interval such that with an expected confidence of C for any deviation d, the probability of d in that interval is C:{a mathematical formula} The set of deviations is a t-distribution of the similarity values. We know that if this is a normal distribution:{a mathematical formula} where {a mathematical formula}Φ() is the cumulative normal distribution function and {a mathematical formula}erf() is the error function. Therefore, given some value C, we can calculate the equation above to determine the boundary.
      </paragraph>
      <paragraph>
       Let us suppose, as an example, that we wished to say with {a mathematical formula}C=90% that some answer {a mathematical formula}Xi is the most analogous one. This would imply that the probability of that answer's corresponding deviation {a mathematical formula}Di obeys this:{a mathematical formula} Thus, if the deviation {a mathematical formula}Di is larger than 1.644853, we can say with 90% confidence that the answer {a mathematical formula}Xi is the most analogous. In our implementation, we chose a 95% confidence value, therefore we seek a deviation which is larger than 1.959964, approximately a 2-sigma signal.
      </paragraph>
      <paragraph>
       In this manner, we have the ability to determine mathematically not only which value may have the highest similarity, but also the degree to which that value is statistically distinct. We require this, for our approach considers the analogy problem at an array of levels of abstraction. In addition, in this way may be seen the specific interplay of confidence and abstraction when solving problems of analogy, a novel aspect of our work.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      The Fractal Raven Algorithm
     </section-title>
     <paragraph>
      We now present the Fractal Raven algorithm in pseudo-code form. We separate the algorithm into two parts: the preparatory stage (see Algorithm 3) and the execution stage (see Algorithm 4).
     </paragraph>
     <section label="6.1">
      <section-title>
       The Fractal Raven Algorithm: preparatory stage
      </section-title>
      <paragraph>
       In the first stage of our Fractal Raven Algorithm, an image containing the entire problem is first segmented into its component images (the matrix of images, and the possible answers). Next, based upon the complexity of the matrix, the algorithm determines the set of relationships to be evaluated. Then, a range of abstraction levels is determined.
      </paragraph>
      <paragraph>
       As we have implemented it, the abstraction levels are determined to be a partitioning of the given images into gridded sections at a prescribed size and regularity.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       The Fractal Ravens Algorithm: execution stage
      </section-title>
      <paragraph>
       The algorithm concludes by determining the confidence in the answers at each level, stopping when ambiguity is sufficiently resolved. Thus for each level of abstraction, the relationships implied by the kind of Raven's problem ({a mathematical formula}2×2 or {a mathematical formula}3×3) are re-represented into that partitioning. Then, for each of the candidate images, a potentially analogous relationship is determined for each of the existing relationships and a similarity value calculated. The vector of similarity values is reduced via a simple Euclidean distance formula to a single similarity. The balance of the algorithm, using the deviation from the mean of these similarities, continues through a variety of levels of abstraction, looking for an unambiguous answer that meets a specified confidence value.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Addressing the example
      </section-title>
      <paragraph>
       Table 3 shows the results of running the Fractal Ravens algorithm on the example problem, starting at an original gridded partitioning of {a mathematical formula}200×200 pixels (the maximal pixel dimension of the images), and then refining the partitioning down to a grid of {a mathematical formula}3×3 pixels. The table gives the mean (μ), standard deviation ({a mathematical formula}σμ), and number of features (f) for each level of abstraction (grid). The deviation and confidence for each candidate answer are given for each level of abstraction as well. A confidence level of 95% is sought. In the table, we color a cell yellow if it exceeds the desired confidence level, and red if it does so unambiguously for the given grid partitioning.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Discussion of the example results
      </section-title>
      <paragraph>
       The deviations presented in Table 3 appear to suggest that if one starts at the very coarsest level of abstraction, the answer is apparent (image choice 3). Indeed, the confidence in the answer never dips below 99.83%, across all levels of abstraction. As we have shown, while that answer has the highest similarity value, statistically there are other alternatives.
      </paragraph>
      <paragraph>
       We see evidence that operating with either too sparse a data set (at the coarsest) or with too homogeneous a data set (at the finest) may be problematic. The coarsest abstraction (200 pixel grid size) offers 378 features, whereas the finest abstraction (3 pixel grid size) offers more than 1.5 million features for consideration.
      </paragraph>
      <paragraph>
       The data in the table continues to suggest the possibility of automatically detecting these boundary situations. We note that the average similarity measurement at the coarsest abstraction is 0.589, but then falls, at the next level of abstraction, to 0.310, only to thereafter generally increase. This constitutes further evidence for an emergent boundary for coarse abstraction.
      </paragraph>
      <paragraph>
       We suspect that ambiguity exists for ranges of abstraction, only to vanish at some appropriate levels of abstraction, and then reemerges once those levels are surpassed. We see evidence of such behavior in this example, where there exists ambiguity at grid sizes 100, 50, 25, and 12, then the ambiguity vanishes for grid size 6, and then reemerges for grid size 3. This suggests that there are features within the image that are sufficiently discriminatory only at certain levels of abstraction.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Fractal Ravens results
     </section-title>
     <paragraph>
      We have tested our Fractal Ravens algorithm on all problems associated with the four main variations of the Raven's Progressive Matrices Tests: 60 problems of the Standard Progressive Matrices test, 48 problems of the Advanced Progressive Matrices test, 36 problems of the Coloured Progressive Matrices test, and 60 problems of the SPM Plus test. To our knowledge, this is the first published account of a computational model's attempt at the entire Raven's test. In this section, we present our results and discuss our findings.
     </paragraph>
     <section label="7.1">
      <section-title>
       Inputs used for the test
      </section-title>
      <paragraph>
       To create inputs for the Fractal Ravens algorithm, each page from the various Raven test booklets were scanned, and the resulting grayscale images were rotated to roughly correct for page alignment issues. Then, the images were sliced up to create separate image files for each entry in the problem matrix and for each answer choice. These separate images were the inputs to the technique for each problem. No further image processing or cleanup was performed, despite the presence of numerous pixel-level artifacts introduced by the scanning and minor inter-problem image alignment issues. Additionally, the fractal algorithm attempted to solve each problem independently: no information was carried over from problem to problem, or from test variant to test variant.
      </paragraph>
      <paragraph>
       The code used in conducted these runs is precisely the same code as used in the earlier example. This code is available for download from our lab website. The images scanned, however, are copyrighted and thus are not available for download. However, we believe that the instructions for preparing the images provided above will allow for someone with access to the Ravens materials to reproduce our results.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Levels of abstraction considered and calculations performed
      </section-title>
      <paragraph>
       The images associated with each problem had a maximum pixel dimension of between 150 and 250 pixels. Accounting for variation within each test problem, and setting a minimum grid size of 4 pixels, we therefore calculated five or six levels of abstraction for each problem, using the formula described above for determining maximum grid size and using a strategy of halving the pixel dimension at each successively finer level of abstraction.
      </paragraph>
      <paragraph>
       At each level of abstraction, we calculated the similarity value for each possible answer, as proscribed by the Fractal Ravens algorithm. For those calculations, we used the Tversky formula, and set alpha to 1.0 and beta equal to 0.0, conforming to values used in the coincidence model by Bush and Mosteller [8]. From those values, we calculated the mean and standard deviation, and then calculated the deviation and confidence for each answer. We made note of which answers provided a confidence above our chosen level, and whether for each abstraction level the answer was unambiguous or ambiguous, and if ambiguous, in what manner. In those cases where ambiguity was found, we explored several different data techniques to assist in the resolution. We describe those techniques after the presentation of the performance.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Assessment of Fractal Ravens performance against human norms
      </section-title>
      <paragraph>
       There are three main assessments that can be made following the administration of a Raven test to an individual: the total score, which is given simply as the number of correct answers; an estimate of consistency, which is obtained by comparing the given score distribution to the expected distribution for that particular total score; and the percentile range into which the score falls, for a given age and nationality [61]. A score is “consistent” if the difference between the actual score and the expected score for any given set is no more than ±2 [61].
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Performance on the Standard Progressive Matrices test
      </section-title>
      <paragraph>
       On the Raven's Standard Progressive Matrices test, the Fractal Ravens algorithm detected the correct answer at a 95% or higher level of confidence on 50 of the 60 problems. The number of problems with detected correct answers per set were 12 for set A, 10 for set B, 11 for set C, 9 for set D, and 8 for set E. Of the 50 problems where the correct answers detected, 38 were determinable by one or more of our ambiguity-resolution strategies. Of the remaining 12 problems noted answers, all but three were ambiguous between two or three particular answers. Table 4 provides a summarization of these results.
      </paragraph>
      <paragraph>
       As shown in Fig. 9, the score differences for Fractal Ravens on each set were no more than ±1. For a human test-taker, this score distribution generally would indicate that the test results do provide a valid measure of the individual's general intellectual capacity. This score pattern illustrates that the results achieved by the algorithm fall well within typical human norms on the SPM for all sets.
      </paragraph>
      <paragraph>
       Using norms from the United States, we note that a total score of 50 corresponds to the 95th percentile for children about 12 years old, the 75th percentile for children around 14 years old, and the 50th percentile for children older than 16 years old [61].
      </paragraph>
     </section>
     <section label="7.5">
      <section-title>
       Performance on the Advanced Progressive Matrices test
      </section-title>
      <paragraph>
       On the Raven's Advanced Progressive Matrices test, the Fractal Ravens algorithm detected the correct answer at a 95% or higher level of confidence on 42 of the 48 problems. The numbers of problems with detected correct answers per set were 10 for set A, and 32 for set B. Of the 42 problems where the correct answers detected, 28 were determinable by one or more of our ambiguity-resolution strategies. Of the remaining 14 problems noted answers, all but four were ambiguous between two or three particular answers. Table 5 provides a summarization of the APM results.
      </paragraph>
      <paragraph>
       The score differences for Fractal Ravens on both APM sets were no more than ±1, indicating consistency and that the results achieved by the algorithm fall well within typical human norms on the APM for both sets. We note that a total score of 42 corresponds to the 95th percentile for adults between 50 and 60 years old, and exceeds the 75th percentile performance for adults of all measured ages [61].
      </paragraph>
     </section>
     <section label="7.6">
      <section-title>
       Performance on the Coloured Progressive Matrices test
      </section-title>
      <paragraph>
       On the Raven's Coloured Progressive Matrices test, the Fractal Ravens algorithm detected the correct answer at a 95% or higher level of confidence on 30 of the 36 problems. The number of problems with detected correct answers per set were 12 for set A, 11 for set AB, and 7 for set B. Of the 30 problems where the correct answers detected, 24 were determinable by one or more of our ambiguity-resolution strategies. Of the remaining 6 problems noted answers, all were ambiguous between two or three particular answers. Table 6 provides a summarization of these results.
      </paragraph>
      <paragraph>
       As shown in Fig. 10, the score differences for Fractal Ravens on each set were no more than ±2, indicating consistency. This score pattern also illustrates that the results achieved by the algorithm fall well within typical human norms on the CPM for all sets.
      </paragraph>
      <paragraph>
       Using the United States norms, we note that a total score of 30 on the CPM test corresponds to the 95th percentile for children about 7 years old, the 75th percentile for children about 9 years old, and the 50th percentile for children about 11 years old [61].
      </paragraph>
     </section>
     <section label="7.7">
      <section-title>
       Performance on the SPM Plus test
      </section-title>
      <paragraph>
       On the Raven's Standard Progressive Matrices Plus test, the Fractal Ravens algorithm detected the correct answer at a 95% or higher level of confidence on 50 of the 60 problems. The number of problems with detected correct answers per set were 10 for set A, 9 for set B, 9 for set C, 11 for set D, and 11 for set E. Of the 50 problems where the correct answers detected, 39 were determinable by one or more of our ambiguity-resolution strategies. Of the remaining 11 problems noted answers, all but one were ambiguous between two or three particular answers. Table 7 provides a summarization of these results.
      </paragraph>
     </section>
     <section label="7.8">
      <section-title>
       Comparison to other computational models
      </section-title>
      <paragraph>
       While this is the first published account of a computational model's attempt at the entire suite of Raven's tests, as we noted in the introduction there are other computational models which have been used on some or all of certain tests. For those accounts that report scores, we compared their results with those achieved by the Fractal Raven algorithm. Table 8 documents the performance of the Fractal Ravens algorithm against those contemporaries.
      </paragraph>
      <paragraph>
       Carpenter et al. [9] report results of running two versions of their algorithm (FairRaven and BetterRaven) against a subset of the APM problems. The subset of problems chosen by Carpenter et al. reflect those whose rules and representations were deemed as inferable by their production rule based system [9].
      </paragraph>
      <paragraph>
       Lovett et al. [50], [51] report results from their computational model's approach to the Raven's SPM test. In each account, only a portion of the test was attempted, but Lovett et al. project an overall score based on the performance of the attempted sections. The latest published account by Lovett et al. [51] reports a score of 44 out of 48 attempted problems from sets B through E of the SPM test, but does not offer a breakdown of this score by problem set. Lovett et al. [51] project a score of 56 for the entire test, based on human normative data indicating a probable score of 12 on set A given their model's performance on the attempted sets.
      </paragraph>
      <paragraph>
       Cirillo and Ström [11] report that their system was tested against Sets C through E of the SPM and solved 8, 10, and 10 problems, respectively. Though unattempted, they predict that their system would score 19 on the APM (a prediction of 7 on set A, and 12 on set B).
      </paragraph>
      <paragraph>
       Kunda et al. [46], [47], [48] report the results of running their Affine algorithm against all of the problems on both the SPM and the APM tests, with a detailed breakdown of scoring per test. They report a score of 38 for the SPM and a score of 21 on the APM. More recently, this approach has given better results on the SPM, and it also has been used to address problems on the CPM [44].
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>