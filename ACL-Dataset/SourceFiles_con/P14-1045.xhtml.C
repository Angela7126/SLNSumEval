<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Predicting the relevance of distributional semantic similarity with contextual information.
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
       Using distributional analysis methods to compute semantic proximity links between words has become commonplace in NLP.
The resulting relations are often noisy or difficult to interpret in general.
This paper focuses on the issues of evaluating a distributional resource and filtering
the relations it contains, but instead of considering it in abstracto, we focus on pairs of words in context.
In a discourse, we are interested in knowing if the semantic link between two items is
a by-product of textual coherence or is irrelevant.
We first set up a human annotation of semantic links with or without contextual information to show the importance
of the textual context in evaluating the relevance of semantic similarity, and to assess the prevalence of actual semantic
relations between word tokens. We then built an experiment to automatically
predict this relevance, evaluated on the reliable reference data set which was the outcome of the first annotation.
We show that in-document information greatly improve the prediction made by the similarity level alone.
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
        The goal of the work presented in this paper is to improve distributional thesauri, and to help evaluate the content of such resources.
A distributional thesaurus is a lexical network that lists semantic neighbours, computed from a corpus and a similarity measure between
lexical items, which generally captures the similarity of contexts in which the items occur. This way of building
a semantic network has been very popular since
        []
        , even though the nature of the information it contains is
hard to define, and its evaluation is far from obvious. A distributional thesaurus includes a lot of “noise” from a semantic point of view,
but also lists relevant lexical pairs that escape classical lexical relations such as synonymy or hypernymy.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        There is a classical dichotomy when evaluating NLP components between extrinsic and intrinsic evaluations
        []
        , and this applies to
distributional thesauri
        []
        . Extrinsic evaluations measure the capacity of a system in which a resource or a component to evaluate has been
used, for instance in this case information retrieval
        []
        or word sense disambiguation
        []
        .
Intrinsic evaluations try to measure the resource itself with respect to some human standard or judgment, for instance by comparing a distributional resource with respect
to an existing synonym dictionary or similarity judgment produced by human subjects
        []
        . The shortcomings of these methods
have been underlined in
        []
        .
Lexical resources designed for other objectives put the spotlight on specific areas of the distributional thesaurus. They are not suitable for the evaluation of the whole range of semantic relatedness that is exhibited by distributional similarities, which exceeds the limits of classical lexical relations, even though
researchers have tried to collect equivalent resources manually, to be used as a gold standard
        []
        .
One advantage of distributional similarities is to exhibit a lot of different semantic relations, not necessarily standard lexical relations. Even with respect to established lexical resources,
distributional approaches may improve coverage, complicating the evaluation even more.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The method we propose here has been designed as an intrinsic evaluation with a view to validate semantic proximity links in a broad perspective, to cover what
        []
        call “non classical lexical semantic relations”. For instance, agentive relations (author/publish, author/publication) or associative relations (actor/cinema) should be considered. At the same time, we want to filter associations that can be considered as accidental in a semantic perspective (e.g. flag and composer are similar because they
appear a lot with nationality names). We do this by judging the relevance of a lexical relation in a context where both elements of a lexical pair occur. We show not only that this improves the reliability of human judgments, but also that it gives a framework where this relevance can be predicted automatically. We hypothetize that evaluating and filtering semantic relations in texts where lexical items occur would help
tasks that naturally make use of semantic similarity relations, but assessing this goes beyond the present work.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In the rest of this paper, we describe the resource we used as a case study, and the data we collected to evaluate its content (section
        2
        ).
We present the experiments we set up to automatically filter semantic relations in context, with various groups of features that take into account
information from the corpus used to build the thesaurus and contextual information related to occurrences of semantic neighbours
        3
        ).
Finally we discuss some related work on the evaluation and improvement of distributional resources (section
        4
        ).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Evaluation of lexical similarity in context
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Data
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         We use a distributional resource for French, built on a 200M word corpus extracted from the French Wikipedia, following principles laid out in
         []
         from
a structured model
         []
         , i.e. using syntactic contexts. In this approach, contexts are triples (governor,relation,dependent) derived from syntactic dependency structures.
Governors and dependents are verbs, adjectives and nouns. Multiword units are available, but they form a very small subset of the resulting neighbours. Base elements in the thesaurus are of two types: arguments (dependents’ lemma) and predicates (governor+relation). This is to keep the predicate/argument distinction since
similarities will be computed between predicate pairs or argument pairs, and a lexical item can appear in many predicates and as an argument (e.g.
         interest
         as argument,
         interest_for
         as one predicate).
The similarity of distributions was computed with Lin’s score
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         We will talk of lexical neighbours or distributional neighbours to label pairs of predicates or arguments, and in the rest of the paper we consider only lexical pairs with a
Lin score of at least 0.1, which means about 1.4M pairs. This somewhat arbitrary level is an
         a priori
         threshold to limit the resulting database, and it is conservative
enough not to exclude potential interesting relations.
The distribution of scores is given figure
         1
         ; 97% of the selected pairs have a score between 0.1 and 0.29.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         To ease the use of lexical neighbours in our experiments, we merged together predicates that include the same lexical unit,
         a posteriori
         . Thus there is no need
for a syntactic analysis of the context considered when exploiting the resource, and sparsity is less of an issue
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Annotation
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         In order to evaluate the resource, we set up an annotation in context: pairs of lexical items are to be judged in their context of use, in texts where they occur together.
To verify that this methodology is useful, we did a preliminary annotation to contrast judgment on lexical pairs with or without this contextual information.
Then we made a larger annotation in context once we were assured of the reliability of the methodology.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         For the preliminary test, we asked three annotators to judge the similarity of pairs of lexical items without any context (
         no-context
         ), and to judge the similarity of pairs presented within a paragraph where they both occur (
         in context
         ).
The three annotators were linguists, and two of them (1 and 3) knew about the resource and how it was built.
For each annotation,
         100
         pairs were randomly selected, with the following constraints:
        </p>
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            for the
            no-context
            annotation, candidate pairs had a Lin score above
            0.2
            , which placed them in the top
            14⁢%
            of lexical neighbours with respect to the similarity level.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            for the
            in context
            annotation, the only constraint was that the pairs occur in the same paragraph somewhere in the corpus used to build the resource. The example paragraph was chosen at random.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         The guidelines given in both cases were the same: “Do you think the two words are semantically close ? In other words, is there a semantic relation between them, either classical (synonymy, hypernymy, co-hyponymy, meronymy, co-meronymy) or not (the relation can be paraphrased but does not belong to the previous cases) ?”
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         For the pre-test, agreement was rather moderate without context (the average of pairwise kappas was .46), and much better with a context (average = .68), with agreement rates
above 90%.
This seems to validate the feasability of a reliable annotation of relatedness in context, so we went on for a larger annotation with two of the previous annotators.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p5">
        <p class="ltx_p">
         For the larger annotation, the protocol was slightly changed: two annotators were given 42 full texts from the original corpus where lexical neighbours occurred. They were asked to judge
the relation between two items types, regardless of the number of occurrences in the text. This time there was no filtering of the lexical pairs beyond the 0.1 threshold of the original resource.
We followed the well-known postulate
         []
         that all occurrences of a word in the same discourse tend to have the same sense (“one sense per discourse”),
in order to decrease the annotator workload. We also assumed that the relation between these items remain stable within the document, an arguably strong
hypothesis that needed to be checked against inter-annotator agreement before beginning the final annotation .
It turns out that the kappa score (
         0.80
         ) shows a better inter-annotator agreement than during the preliminary test, which can be explained by the larger context given to the annotator (the whole text),
and thus more occurrences of each element in the pair to judge, and also because the annotators were more experienced after the preliminary test.
Agreement measures are summed-up table
         1
         .
An excerpt of an example text, as it was presented to the annotators, is shown figure
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p6">
        <p class="ltx_p">
         Overall, it took only a few days to annotate 9885 pairs of lexical items. Among the pairs that were presented to the annotators, about 11% were judged as relevant by the annotators.
It is not easy to decide if the non-relevant pairs are just noise, or context-dependent associations that were not present in the actual text considered (for polysemy reasons for instance), or just low-level associations.
An important aspect is thus to guarantee that there is a correlation between the similarity score (Lin’s score here), and the evaluated relevance of the neighbour pairs.
Pearson correlation factor shows that Lin score is indeed significantly correlated to the annotated relevance of lexical pairs, albeit not strongly (
         r=0.159
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p7">
        <p class="ltx_p">
         The produced annotation
         can be used as a reference to explore various aspects of distributional resources, with the caveat
that it is as such a bit dependent on the particular resource used. We nonetheless assume that some of the relevant pairs would appear in other thesauri, or would be of interest in an evaluation of another resource.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p8">
        <p class="ltx_p">
         The first thing we can analyse from the annotated data is the impact of a threshold on Lin’s score to select relevant lexical pairs.
The resource itself is built by choosing a cut-off which is supposed to keep pairs with a satisfactory similarity, but this threshold is rather arbitrary.
Figure
         3
         shows the influence of the threshold value to select relevant pairs, when considering precision and recall
of the pairs that are kept when choosing the threshold, evaluated against the human annotation of relevance in context.
In case one wants to optimize the F-score (the harmonic mean of precision and recall) when extracting relevant pairs, we can see that the optimal point is at .24 for a threshold of .22 on Lin’s score.
This can be considered as a baseline for extraction of relevant lexical pairs, to which we turn in the following section.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Experiments: predicting relevance in context
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The outcome of the contextual annotation presented above is a rather sizeable dataset of validated semantic links, and we showed these linguistic judgments to be reliable.
We used this dataset to set up a supervised classification experiment in order to automatically predict the relevance of a semantic link in a given discourse.
We present now the list of features that were used for the model. They can be divided in three groups, according to their origin: they are computed from the whole corpus, gathered from the distributional resource, or extracted from the considered text which contains the semantic pair to be evaluated.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         For each pair
         neighboura
         /
         neighbourb
         , we computed a set of features from Wikipedia (the corpus used to derive the distributional similarity):
We first computed the frequencies of each item in the corpus,
         f⁢r⁢e⁢qa
         and
         f⁢r⁢e⁢qb
         , from which we derive
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            f⁢r⁢e⁢qm⁢i⁢n
            ,
            f⁢r⁢e⁢qm⁢a⁢x
            : the min and max of
            f⁢r⁢e⁢qa
            and
            f⁢r⁢e⁢qb
            ;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            f⁢r⁢e⁢q×
            : the combination of the two, or
            log⁡(f⁢r⁢e⁢qa×f⁢r⁢e⁢qb)
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         We also measured the syntagmatic association of
         neighboura
         and
         neighbourb
         , with a mutual information measure
         []
         , computed from the cooccurrence of two tokens within the same paragraph
in Wikipedia. This is a rather large window, and thus gives a good coverage with respect to the neighbour database (70% of all pairs).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         A straightforward parameter to include to predict the relevance of a link is of course the similarity
measure itself, here Lin’s information measure.
But this can be complemented by additional information on the similarity of the neighbours, namely:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <ul class="ltx_itemize" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            each neighbour productivity :
            p⁢r⁢o⁢da
            and
            p⁢r⁢o⁢db
            are defined as the numbers of
neighbours of respectively
            neighboura
            and
            neighbourb
            in the database (thus related tokens with a similarity above the threshold), from which we derive three features as for frequencies: the min, the max, and the log of the product. The idea is that neighbours whith very high productivity give rise to less reliable relations.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            the ranks of tokens in other related items neighbours:
            r⁢a⁢n⁢ka-b
            is defined
as the rank of
            neighboura
            among neighbours of
            neighbourb
            ordered with respect to Lin’s score;
            r⁢a⁢n⁢gb-a
            is defined similarly and again we consider as features the min, max and log-product of these ranks.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         We add two categorial features, of a more linguistic nature:
        </p>
        <ul class="ltx_itemize" id="I4">
         <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i1.p1">
           <p class="ltx_p">
            c⁢a⁢t⁢s
            is the pair of part-of-speech for the related items, e.g. to distinguish the relevance of NN or VV pairs.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i2.p1">
           <p class="ltx_p">
            p⁢r⁢e⁢d⁢a⁢r⁢g
            is related to the predicate/argument distinction:
are the related items predicates or arguments ?
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         The last set of features derive from the occurrences of related tokens in the considered discourses:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         First, we take into account the frequencies of items within the text, with three features as before: the min of the frequencies of the two related items, the max, and the log-product.
Then we consider a
         tf⋅idf
         []
         measure, to evaluate the specificity and arguably the importance
of a word in a document or within a document. Several variants of
         tf⋅idf
         have been proposed to adapt the measure to more local areas in a text with respect to the whole document.
For instance
         []
         propose a
         tf⋅isf
         (
         term frequency ⋅ inverse sentence frequency
         ), for topic segmentation. We similarly defined a
         tf⋅ipf
         measure based on the
frequency of a word within a paragraph with respect to its frequency within the text. The resulting feature we used is the product of this measure for
         neighboura
         and
         neighbourb
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p7">
        <p class="ltx_p">
         A few other contextual features are included in the model: the distances between pairs of related items, instantiated as:
        </p>
        <ul class="ltx_itemize" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            distance in words between occurrences of related word types:
           </p>
           <ul class="ltx_itemize" id="I5.I1">
            <li class="ltx_item" id="I5.I1.i1" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I5.I1.i1.p1">
              <p class="ltx_p">
               minimal distance between two occurrences (
               s⁢d
               )
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I5.I1.i2" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I5.I1.i2.p1">
              <p class="ltx_p">
               maximal distance between two occurrences (
               g⁢d
               )
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I5.I1.i3" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I5.I1.i3.p1">
              <p class="ltx_p">
               average distance (
               a⁢d
               ) ;
              </p>
             </div>
            </li>
           </ul>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            boolean features indicating whether
            neighboura
            and
            neighbourb
            appear in the same sentence (
            c⁢o⁢p⁢rs
            ) or the same paragraph (
            c⁢o⁢p⁢rp⁢a⁢r⁢a
            ).
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS1.p8">
        <p class="ltx_p">
         Finally, we took into account the network of related lexical items, by considering the largest sets of words present in the text and connected in the database (self-connected components), by adding
the following features:
        </p>
        <ul class="ltx_itemize" id="I6">
         <li class="ltx_item" id="I6.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i1.p1">
           <p class="ltx_p">
            the degree of each lemma, seen as a node in this similarity graph, combined as above in minimal degree of the pair, maximal degree, and product of degrees (
            p⁢r⁢o⁢d⁢t⁢x⁢tmin
            ,
            p⁢r⁢o⁢d⁢t⁢x⁢tmax
            ,
            p⁢r⁢o⁢d⁢t⁢x⁢t×
            ).
This is the number of pairs (present in the text) where a lemma appears in.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I6.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i2.p1">
           <p class="ltx_p">
            a boolean feature
            c⁢c
            saying whether a lexical pair belongs to a connected component of the text, except the largest. This reflects the fact that a small component may concern a lexical field which is more specific and thus more relevant to the text.
           </p>
          </div>
          <div class="ltx_para" id="I6.i2.p2">
           <p class="ltx_p">
            Figure
            4
            shows examples of self-connected components in an excerpt of the page on
            Gorille
            (gorilla), e.g. the set {
            pelage, dos, fourrure
            } (coat, back, fur).
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The last feature is probably not entirely independent from the productivity of an item, or from the tf.ipf measure.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p9">
        <p class="ltx_p">
         Table
         2
         sums up the features used in our model.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Model
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Our task is to identify relevant similarities between lexical items, between all possible related pairs, and
we want to train an inductive model, a classifier, to extract the relevant links.
We have seen that the relevant/not relevant classification is very imbalanced, biased towards the “not relevant” category
(about 11%/89%), so we applied methods dedicated to counter-balance this, and will focus on the precision and recall
of the predicted relevant links.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Following a classical methodology, we made a 10-fold cross-validation to evaluate robustly the performance of the classifiers.
We tested a few popular machine learning methods, and report on two of them, a naive bayes model and the best method on our dataset, the Random Forest classifier
         []
         . Other popular methods (maximum entropy, SVM) have shown slightly inferior combined F-score, even though precision and recall might yield
more important variations. As a baseline, we can also consider a simple threshold on the lexical similarity score, in our case Lin’s measure, which we have shown
to yield the best F-score of 24% when set at 0.22.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         To address class imbalance, two broad types of methods can be applied to help the model focus on the minority class. The first one
is to resample the training data to balance the two classes, the second one is to penalize differently the two classes during training when the model makes
a mistake (a mistake on the minority class being made more costly than on the majority class).
We tested the two strategies, by applying the classical Smote method of
         []
         as a kind of resampling, and the ensemble method MetaCost of
         []
         as
a cost-aware learning method. Smote synthetizes and adds new instances similar to the minority class instances and is more efficient than a mere resampling.
MetaCost is an interesting meta-learner that can use any classifier as a base classifier.
We used Weka’s implementations of these methods
         []
         , and our experiments and comparisons are thus easily replicated on our dataset, provided with this paper,
even though they can be improved by refinements of these techniques.
We chose the following settings for the different models: naive bayes uses a kernel density estimation for numerical features, as this generally improves performance.
For Random Forests, we chose to have ten trees, and each decision is taken on a randomly chosen set of five features.
For resampling, Smote advises to double the number of instances of the minority class, and we observed that a bigger resampling degrades performances.
For cost-aware learning, a sensible choice is to invert the class ratio for the cost ratio, i.e. here the cost of a mistake on a relevant link (false negative) is exactly 8.5 times higher than
the cost on a non-relevant link (false positive), as non-relevant instances are 8.5 times more present than relevant ones.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         We are interested in the precision and recall for the “relevant” class. If we take the best simple classifier (random forests), the precision and recall are
         68.1⁢%
         and
         24.2⁢%
         for an F-score of
         35.7⁢%
         , and this is significantly beaten
by the Naive Bayes method as precision and recall are more even (F-score of 41.5%). This is already a big improvement on the use of the similarity measure alone (24%).
Also note that predicting every link as relevant would result in a 2.6% precision, and thus a 5% F-score.
The random forest model is significantly improved by the balancing techniques: the overall best F-score of 46.3% is reached with Random Forests and the cost-aware learning method.
Table
         3
         sums up the scores for the different configurations, with precision, recall, F-score and the confidence interval on the F-score. We analysed the learning curve by doing a cross-validation on reduced set of instances (from 10% to 90%); F1-scores range from 37.3% with 10% of instances and stabilize at 80%, with small increment in every case.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         The filtering approach we propose seems to yield good results, by augmenting the similarity built on the whole corpus with signals from
the local contexts and documents where related lexical items appear together.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         To try to analyse the role of each set of features, we repeated the experiment but changed the set of features used during training, and
results are shown table
         4
         for the best method (RF with cost-aware learning).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         We can see that similarity-related features (measures, ranks) have the biggest impact, but the other ones also seem to play a significant role.
We can draw the tentative conclusion that the quality of distributional relations depends on the contextualizing of the related lexical items, beyond just the similarity score and the ranks of items as neighbours of other items.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Related work
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Our work is related to two issues: evaluating distributional resources, and improving them.
Evaluating distributional resources is the subject of a lot of methodological reflection
        []
        , and
as we said in the introduction, evaluations can be divided between extrinsic and intrinsic evaluations.
In extrinsic evaluations, models are evaluated against benchmarks focusing on a single task or a single aspect
of a resource: either discriminative, TOEFL-like tests
        []
        , analogy production
        []
        ,
or synonym selection
        []
        .
In intrinsic evaluations, associations norms are used, such as the 353 word-similarity dataset
        []
        , e.g.
        []
        , or specifically designed test cases, as in
        []
        .
We differ from all these evaluation procedures as we do not focus on an
        essential
        view of the relatedness of two lexical items, but evaluate the link
in a context where the relevance of the link is in question, an “existential” view of semantic relatedness.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        As for improving distributional thesauri, outside of
numerous alternate approaches to the construction,
there is a body of work focusing on
improving an existing resource, for instance
reweighting context features once an initial thesaurus is built
        []
        ,
or post-processing the resource to filter bad neighbours or re-ranking neighbours of a given
target
        []
        . They still use “essential” evaluation measures (mostly synonym extraction),
although the latter comes close to our work since it also trains a model to detect (intrinsically) bad neighbours by using example sentences with the words to discriminate.
We are not aware of any work that would try to evaluate differently semantic neighbours according to the context they appear in.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
