<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   A practical and linguistically-motivated approachto
compositional distributional semantics.
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
       Distributional semantic methods to approximate word meaning with
context vectors have been very successful empirically, and the last
years have seen a surge of interest in their compositional extension
to phrases and sentences. We present here a new model that, like
those of
       Coecke et al. (2010)
       and
       Baroni and Zamparelli (2010)
       , closely mimics the standard
Montagovian semantic treatment of composition in distributional
terms. However, our approach avoids a number of issues that have
prevented the application of the earlier linguistically-motivated
models to full-fledged, real-life sentences. We test the model on
a variety of empirical tasks, showing that it consistently
outperforms a set of competitive rivals.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Compositional distributional semantics
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        The research of the last two decades has established empirically that
distributional vectors for words obtained from corpus statistics can
be used to represent word meaning in a variety of tasks
        [25]
        . If distributional vectors encode certain
aspects of word meaning, it is natural to expect that similar aspects
of sentence meaning can also receive vector representations, obtained
compositionally from word vectors. Developing a practical model of
compositionality is still an open issue, which we address in this
paper. One approach is to use simple, parameter-free models that
perform operations such as pointwise multiplication or summing
        [20]
        . Such models turn out to be surprisingly
effective in practice
        [6]
        , but they have obvious
limitations. For instance, symmetric operations like vector addition
are insensitive to syntactic structure, therefore meaning
differences encoded in word order are lost in composition:
        pandas eat bamboo
        is identical to
        bamboo eats
pandas
        .
        Guevara (2010)
        ,
        Mitchell and Lapata (2010)
        ,
        Socher et al. (2011)
        and
        Zanzotto et al. (2010)
        generalize
the simple additive model by applying structure-encoding operators to
the vectors of two sister nodes before addition, thus breaking the
inherent symmetry of the simple additive model. A related approach
        [24]
        assumes richer lexical representations where
each word is represented with a vector and a matrix that encodes its
interaction with its syntactic sister. The training proposed in this
model estimates the parameters in a supervised setting. Despite
positive empirical evaluation, this approach is hardly practical for
general-purpose semantic language processing, since it requires
computationally expensive approximate parameter optimization
techniques, and it assumes task-specific parameter learning whose
results are not meant to generalize across tasks.
       </p>
      </div>
      <div class="ltx_subsection" id="S1.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.1
        </span>
        The lexical function model
       </h3>
       <div class="ltx_para" id="S1.SS1.p1">
        <p class="ltx_p">
         None of the proposals mentioned above, from simple to elaborate,
incorporates in its architecture the intuitive idea (standard in
theoretical linguistics) that semantic composition is more than a
weighted combination of words. Generally one of the components of a
phrase, e.g., an adjective, acts as a function affecting the other
component (e.g., a noun). This underlying intuition, adopted from
formal semantics of natural language, motivated the creation of the
         lexical function
         model of composition (
         lf
         )
         [4, 9]
         . The lf model can be
seen as a projection of the symbolic Montagovian approach to semantic
composition in natural language onto the domain of vector spaces and
linear operations on them
         [3]
         . In lf, arguments
are vectors and functions taking arguments (e.g., adjectives that
combine with nouns) are tensors, with the number of arguments (n)
determining the order of tensor (n+1). For example, adjectives, as
unary functors, are modeled with 2-way tensors, or matrices.
Tensor by vector multiplication formalizes function application and serves as the general composition method.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p2">
        <p class="ltx_p">
         Baroni and Zamparelli (2010)
         propose a practical and empirically
effective way to estimate matrices representing adjectival modifiers
of nouns by linear regression from corpus-extracted examples of noun
and adjective-noun vectors. Unlike the neural network approach of Socher et
al.
         [23, 24]
         , the Baroni and
Zamparelli method does not require manually labeled data nor costly
iterative estimation procedures, as it relies on automatically
extracted phrase vectors and on the analytical solution of the
least-squares-error problem.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p3">
        <p class="ltx_p">
         The same method was later applied to
matrix representations of intransitive verbs and determiners
         [5, 10]
         , always with good empirical results.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p4">
        <p class="ltx_p">
         The full range of semantic types required for natural language
processing, including those of adverbs and transitive verbs, has to
include, however, tensors of greater rank. The estimation method
originally proposed by Baroni and Zamparelli has been extended to
3-way tensors representing transitive verbs by
         Grefenstette et al. (2013)
         with preliminary success. Grefenstette et al.’s method works in two steps. First, one estimates matrices of verb-object
phrases from subject and subject-verb-object vectors; next, transitive
verb tensors are estimated from verb-object matrices and object
vectors.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S1.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.2
        </span>
        Problems with the extension of the lexical function model
to sentences
       </h3>
       <div class="ltx_para" id="S1.SS2.p1">
        <p class="ltx_p">
         With all the advantages of lf, scaling it up to arbitrary sentences, however, leads to several issues. In particular, it is desirable for all
practical purposes to limit representation size. For example, if noun
meanings are encoded in vectors of
         300
         dimensions, adjectives become
matrices of
         3002
         cells, and transitive verbs are represented as
tensors with
         3003
         =
         27,000,000
         dimensions.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p2">
        <p class="ltx_p">
         Estimating tensors of this size runs into data sparseness issues
already for less common transitive verbs. Indeed, in order to train a
transitive verb tensor (e.g.,
         eat
         ), the method of
         Grefenstette et al. (2013)
         requires a sufficient number of
distinct verb object phrases with that verb (e.g.,
         eat cake
         ,
         eat fruits
         ), each attested in combination with a certain
number of subject nouns with sufficient frequency to extract sensible
vectors. It is not feasible to obtain enough data points for all verbs
in such a training design.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p3">
        <p class="ltx_p">
         Things get even worse for other categories. Adverbs like
         quickly
         that modify intransitive verbs have to be represented
with
         30022
         =
         8,100,000,000
         dimensions. Modifiers of transitive
verbs would have even greater representation size, which may not be
possible to store and learn efficiently.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p4">
        <p class="ltx_p">
         Another issue is that the same or similar items that occur in
different syntactic contexts are assigned different semantic types
with incomparable representations. For example, verbs like
         eat
         can be used in transitive or intransitive constructions
(
         children eat meat
         /
         children eat
         ), or in passive
(
         meat is eaten
         ). Since predicate arity is encoded in the
order of the corresponding tensor,
         eat
         and the like have to
be assigned different representations (matrix or tensor) depending on
the context. Deverbal nouns like
         demolition
         , often used
without mention of who demolished what, would have to get vector
representations while the corresponding verbs (
         demolish
         )
would become tensors, which makes immediately related verbs and nouns
incomparable. Nouns in general would oscillate between vector and
matrix representations depending on argument vs. predicate vs. modifier position (
         an animal runs
         vs.
         this is an
animal
         vs.
         animal shelter
         ). Prepositions are the hardest,
as the syntactic positions in which they occur are most diverse
(
         park in the dark
         vs.
         play in the dark
         vs.
         be in the dark
         vs.
         a light glowing in the dark
         ).
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p5">
        <p class="ltx_p">
         In all those cases, the same word has to be mapped to tensors of
different orders. Since each of these tensors must be learned from
examples individually, their obvious relation is missed. Besides
losing the comparability of the semantic contribution of a word across
syntactic contexts, we also worsen the data
sparseness
issues.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p6">
        <p class="ltx_p">
         The last, and related, point is that for the tensor calculus to
work, one needs to model, for each word, each of the constructions in
the corpus that the word is attested in. In its pure form lf does not
include an emergency backoff strategy when unknown words or
constructions are encountered. For example, if we only observe
transitive usages of
         to eat
         in the training corpus, and
encounter an intransitive or passive example of it in testing data,
the system would not be able to compose a sentence vector at all. This
issue is unavoidable since we don’t expect to find all words in all
possible constructions even in the largest corpus.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       The practical lexical function model
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        As follows from section
        1.2
        , it would be desirable to have a
compositional distributional model that encodes function-argument
relations but avoids the troublesome high-order tensor representations
of the pure lexical function model, with all the practical problems
that come with them. We may still want to represent word meanings in
different syntactic contexts differently, but at the same time we need
to incorporate a formal connection between those representations,
e.g., between the transitive and the intransitive instantiations of
the verb
        to eat
        . Last but not least, all items need to
include a common aspect of their representation (e.g., a vector) to
allow comparison across categories (the case of
        demolish
        and
        demolition
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        To this end, we propose a new model of composition that maintains the
idea of function application, while avoiding the complications and
rigidity of lf. We call our proposal
        practical lexical function
        model, or
        plf
        . In plf, a functional word is not represented by
a single tensor of arity-dependent order, but by a vector plus an
ordered set of matrices, with one matrix for each argument the function
takes. After applying the matrices to the corresponding argument
vectors, a single representation is obtained by summing across all
resulting vectors.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Word meaning representation
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         In plf, all words are represented by a vector, and functional words,
such as predicates and modifiers, are also assigned one or more
matrices. The general form of a semantic representation for a
linguistic unit is an ordered tuple of a vector and
         n∈ℕ
         matrices:
        </p>
        ⟨x→,x□1,…,x□n⟩
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The number of matrices in the representation encodes the arity of a
linguistic unit, i.e., the number of other units to which it applies
as a function. Each matrix corresponds to a function-argument
relation, and words have as many matrices as many arguments they take:
none for (most) nouns, one for adjectives and intransitive verbs, two
for transitives, etc. The matrices formalize argument slot
saturation, operating on an argument vector representation through
matrix by vector multiplication, as described in the next section.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         Modifiers of n-ary functors are represented by n+1-ary structures. For
instance, we treat adjectives that modify nouns (0-ary) as unary
functions, encoded in a vector-matrix pair. Adverbs have different semantic types depending on their syntactic role. Sentential adverbs are unary, while adverbs that modify
adjectives (
         very
         ) or verb phrases (
         quickly
         ) are
encoded as binary functions, represented by a vector and two matrices.
The form of semantic
representations we are using is shown in Table
         1
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Semantic composition
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Our system incorporates semantic composition via two composition
rules, one for combining structures of different arity and the other
for symmetric composition of structures with the same arity. These
rules incorporate insights of two empirically successful models,
lexical function and the simple additive approach, used as the default
structure merging strategy.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         The first rule is
         function application
         , illustrated in Figure
         1
         . Table
         2
         illustrates simple cases
of function application. For transitive verbs semantic composition
applies iteratively as shown in the derivation of Figure
         2
         . For ternary predicates such as
         give
         in a
ditransitive construction, the first step in the derivation absorbs
the innermost argument by multiplying its vector by the third
         give
         matrix, and then composition proceeds like for transitives.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         The second composition rule,
         symmetric composition
         applies when
two syntactic sisters are of the same arity (e.g., two vectors, or two
vector-matrix pairs). Symmetric composition simply sums the objects in
the two tuples: vector with vector,
         n
         -th matrix with
         n
         -th matrix.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         Symmetric composition is reserved for structures in which the
function-argument distinction is problematic. Some candidates for
such treatment are coordination and nominal compounds, although we
recognize that the headless analysis is not the only possible one
here. See two examples of Symmetric Composition application in Table
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p5">
        <p class="ltx_p">
         Note that the
         sing and dance
         composition in Table
         3
         skips the conjunction. Our current plf
implementation treats most grammatical words, including conjunctions,
as “empty” elements, that do not project into semantics. This choice
leads to some interesting “serendipitous” treatments of various
constructions. For example, since the copula is empty, a sentence with
a predicative adjective (
         cars are red
         ) is treated in the same
way as a phrase with the same adjective in attributive position
(
         red cars
         ) – although the latter, being a phrase and not a
full sentence, will later be embedded as argument in a larger
construction. Similarly, leaving the relative pronoun empty makes
         cars that run
         identical to
         cars run
         , although, again,
the former will be embedded in a larger construction later in the
derivation.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p6">
        <p class="ltx_p">
         We conclude our brief exposition of plf with an alternative intuition
for it: the plf model is also a more sophisticated version of the
additive approach, where argument words are adapted by matrices that
encode the relation to their functors before the sentence vector is
derived by summing.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Satisfying the desiderata
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         Let us now outline how plf addresses the shortcomings of lf listed in
Section
         1.2
         . First, all issues caused by representation
size disappear. An n-ary predicate is no longer encoded as an n+1-way
tensor; instead we have a sequence of n matrices. The representation
size grows linearly, not exponentially, for higher semantic types,
allowing for simpler and more efficient parameter estimation, storage,
and computation.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         As a consequence of our architecture, we no longer need to perform the
complicated step-by-step estimation for elements of higher
arity. Indeed, one can estimate each matrix of a complex
representation individually using the simple method of
         Baroni and Zamparelli (2010)
         . For instance, for transitive verbs
we estimate the verb-subject combination matrix from subject and
verb-subject vectors, the verb-object combination matrix from object
and verb-object vectors. We expect a reasonably large corpus to
feature many occurrences of a verb with a variety of subjects and a
variety of objects (but not necessarily a variety of subjects with
each of the objects as required by Grefenstette et al.’s training),
allowing us to avoid the data sparseness issue.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         The semantic representations we propose include a semantic vector for
constituents of any semantic type, thus enabling semantic comparison
for words of different parts of speech (the case of
         demolition
         vs.
         demolish
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         Finally, the fact that we represent the predicate interaction with
each of its arguments in a separate matrix allows for a natural and
intuitive treatment of argument alternations. For instance, as shown
in Table
         4
         , one can distinguish the transitive and
intransitive usages of the verb
         to eat
         by the presence of the
object-oriented matrix of the verb while keeping the rest of the
representation intact. To model passive usages, we insert the object
matrix of the verb only, which will be multiplied by the syntactic
subject vector, capturing the similarity between
         eat
meat
         and
         meat is eaten
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p5">
        <p class="ltx_p">
         So keeping the verb’s interaction with subject and object encoded in
distinct matrices not only solves the issues of representation size
for arbitrary semantic types, but also provides a sensible built-in
strategy for handling a word’s occurrence in multiple
constructions. Indeed, if we encounter a verb used intransitively
which was only attested as transitive in the training corpus, we can
simply omit the object matrix to obtain a type-appropriate
representation. On the other hand, if the verb occurs with more
arguments than usual in testing materials, we can add a default
diagonal identity matrix to its representation, signaling agnosticism
about how the verb relates to the unexpected argument. This
flexibility makes our model suitable to compute vector representations
of sentences without stumbling at unseen syntactic usages of words.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p6">
        <p class="ltx_p">
         To summarize, plf is an extension of the lexical function model that
inherits its strengths and overcomes its weaknesses. We still employ a
linguistically-motivated notion of semantic composition as function
application and use distinct kinds of representations for different
semantic types. At the same time, we avoid high order tensor
representations, produce semantic vectors for all syntactic
constituents, and allow for an elegant and transparent correspondence
between different syntactic usages of a lexeme, such as the
transitive, the intransitive, and the passive usages of the verb
         to eat
         . Last but not least, our implementation is suitable
for realistic language processing since it allows to produce vectors
for sentences of arbitrary size, including those containing novel
syntactic configurations.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Evaluation
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Evaluation materials
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We consider 5 different benchmarks that focus on different aspects of
sentence-level semantic composition. The first data set, created by Edward
Grefenstette and Mehrnoosh Sadrzadeh and introduced in
         Kartsaklis et al. (2013)
         , features 200 sentence pairs that were
rated for similarity by 43 annotators. In this data set, sentences
have fixed adjective-noun-verb-adjective-noun (anvan) structure, and
they were built in order to crucially require context-based verb
disambiguation (e.g.,
         young woman filed long nails
         is paired
with both
         young woman smoothed long nails
         and
         young woman
registered long nails
         ). We also consider a similar data set
introduced by
         Grefenstette (2013)
         , comprising 200 sentence
pairs rated by 50 annotators. We will call these benchmarks
         anvan1
         and
         anvan2
         , respectively. Evaluation is
carried out by computing the Spearman correlation between the
annotator similarity ratings for the sentence pairs and the cosines of
the vectors produced by the various systems for the same sentence
pairs.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         The benchmark introduced by
         Pham et al. (2013)
         at the TFDS
workshop (
         tfds
         below) was specifically designed to test
compositional methods for their sensitivity to word order and the
semantic effect of determiners. The tfds benchmark contains 157 target
sentences that are matched with a set of (approximate) paraphrases (8
on average), and a set of “foils” (17 on average). The foils have
high lexical overlap with the targets but very different meanings, due
to different determiners and/or word order. For example, the target
         A man plays an acoustic guitar
         is matched with paraphrases such
as
         A man plays guitar
         and
         The man plays the guitar
         , and
foils such as
         The man plays no guitar
         and
         A guitar plays
a man
         . A good system should return higher similarities for the
comparison with the paraphrases with respect to that with the
foils. Performance is assessed through the
         t
         -standardized
cross-target average of the difference between mean cosine with
paraphrases and mean cosine with foils (Pham and colleagues,
equivalently, reported non-standardized average and standard
deviations).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         The two remaining data sets are larger and more ‘natural’, as they were not constructed by
linguists under controlled conditions to focus on specific
phenomena. They are aimed at evaluating systems on the sort of
free-form sentences one encounters in real-life applications. The
         msrvid
         data set from the SemEval-2012 Semantic Textual
Similarity (STS) task
         [2]
         consists of 750 sentence
pairs that describe brief videos. Sentence pairs were scored for
similarity by 5 subjects each. Following standard practice in
paraphrase detection studies (e.g.,
         Blacoe and Lapata (2012)
         ), we
use cosine similarity between sentence pairs as computed by one of our
systems together with two shallow similarity cues: word overlap
between the two sentences and difference in sentence length. We obtain
a final similarity score by weighted addition of the 3 cues, with the
optimal weights determined by linear regression on separate msrvid
train data that were also provided by the SemEval task organizers
(before combining, we checked that the collinearity between cues was
low). System scores are evaluated by their Pearson correlation with
the human ratings.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         The final set we use is
         onwn
         , from the *SEM-2013 STS shared
task
         [1]
         . This set contains 561 pairs of glosses
(from the WordNet and OntoNotes databases), rated by 5 judges for
similarity. Our main interest in this set stems from the fact that
glosses are rarely well-formed full sentences (consider, e.g.,
         cause something to pass or lead somewhere
         ;
         coerce by
violence, fill with terror
         ). For this reason, they are very
challenging for standard parsers. Indeed, we estimated from a sample
of 40 onwn glosses that the C&amp;C parser (see below) has only 45%
accuracy on this set. Since
         plf
         needs syntactic information to
construct sentence vectors compositionally, we test it on onwn to make
sure that it is not overly sensitive to parser noise. Evaluation
proceeds as with msrvid (cue weights are determined by 10-fold
cross-validation).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Semantic space construction and composition model
implementation
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Our source corpus was given by the concatenation of ukWaC
(
         wacky.sslmit.unibo.it
         ), a mid-2009 dump of the English
Wikipedia (
         en.wikipedia.org
         ) and the British National Corpus
(
         www.natcorp.ox.ac.uk
         ), for a total of about 2.8 billion words.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         We collected a 30K-by-30K matrix by counting co-occurrence of the 30K
most frequent content lemmas (nouns, adjectives and verbs) within a
3-word window. The raw count vectors were transformed into positive
Pointwise Mutual Information scores and reduced to 300 dimensions by
the Singular Value Decomposition. All vectors were normalized to length 1. This setup was picked without tuning, as we
found it effective in previous, unrelated experiments.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         We consider four composition models. The
         add
         (additive) model
produces the vector of a sentence by summing the vectors of all content words
in it. Similarly,
         mult
         uses component-wise
multiplication of vectors for composition. While these models are very
simple, a long experimental tradition has proven their effectiveness
         [19, 20, 21, 6]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         For the
         lf
         (lexical function) model, we construct functional
matrix representations of adjectives, determiners and intransitive
verbs. These are trained using Ridge regression with generalized
cross-validation from corpus-extracted vectors of nouns, as input, and
phrases including those nouns as output (e.g., the matrix for
         red
         is trained from corpus-extracted
         ⟨noun,red-noun⟩
         vector pairs). Transitive verb tensors are
estimated using the two-step regression procedure outlined by
         Grefenstette et al. (2013)
         . We did not attempt to train a lf
model for the larger and more varied msrvid and onwn data sets, as
this would have been extremely time consuming and impractical for all
the reasons we discussed in Section
         1.2
         above.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         Training
         plf
         (practical lexical function) proceeds similarly,
but we also build preposition matrices (from
         ⟨noun,preposition-noun⟩
         vector pairs), and for verbs we prepare
separate subject and object matrices.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         Since syntax guides lf and plf composition, we supplied all test
sentences with categorial grammar parses. Every sentence in the anvan1
and anvan2 datasets has the form (subject) Adjective + Noun +
Transitive Verb + (object) Adjective + Noun, so parsing them is
trivial. All sentences in tfds have a predictable structure that
allows perfect parsing with simple finite state rules. In all these
cases, applying a general-purpose parser to the data would have, at
best, had no impact and, at worst, introduced parsing errors. For
msrvid and onwn, we used the output of the C&amp;C parser
         [8]
         .
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
         Table
         5
         summarizes the performance of our models on
the chosen tasks, and compares it to the state of the art reported in
previous work, as well as to various strong baselines.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         The plf model performs very well on both anvan benchmarks,
outperforming not only add and mult, but also the full-fledged lf
model. Given that these data sets contain, systematically, transitive
verbs, the major difference between plf and lf lies in their
representation of the latter. Evidently, the separately-trained
subject and object matrices of plf, being less affected by data
sparseness than the 3-way tensors of lf, are better able to capture
how verbs interact with their arguments. For anvan1, plf is just below
the state of the art, which is based on disambiguating the verb vector
in context
         [18]
         , and lf outperforms the
baseline, which consists in using the verb vector only as a proxy to
sentence similarity.
         On anvan2, plf outperforms the
best model reported by
         Grefenstette (2013)
         (an implementation
of the lexical function ideas along the lines of Grefenstette and
Sadrzadeh
         [12, 13]
         ). And
lf is, again, the only model, besides plf, that performs better than
the baseline.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         In the tfds task, not surprisingly the add and mult models, lacking
determiner representations and being order-insensitive, fail to
distinguish between true paraphrases and foils (indeed, for the mult
model foils are significantly
         closer
         to the targets than the
paraphrases, probably because the latter have lower content word
overlap than the foils, that often differ in word order and
determiners only). Our plf approach is able to handle determiners and
word order correctly, as demonstrated by a highly significant
(
         p&lt;0.01
         ) difference between paraphrase and foil similarity (average difference in cosine .017, standard deviation .077). In this
case, however, the traditional lf model (average difference .044, standard deviation .092) outperforms plf. Since
determiners are handled identically under the two approaches, the
culprit must be word order. We conjecture that the lf 3-way tensor
representation of transitive verbs leads to a stronger asymmetry
between sentences with inverted arguments, and thus makes this model
particularly sensitive to word order differences. Indeed, if we limit
evaluation to those foils characterized by word order changes only, lf
discriminates between paraphrases and foils even more clearly, whereas
the plf difference, while still significant, decreases slightly.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         The state-of-the-art row for tfds reports the lf implementation by
         Pham et al. (2013)
         , which outperforms ours. The main
difference is that Pham and colleagues do not normalize vectors
like we do. If we don’t normalize, we do get larger differences
for our models as well, but consistently lower performance in all
other tasks. More worryingly, the simple word overlap baseline reported in the
table sports a larger difference than our best model. Clearly, this
baseline is exploiting the systematic determiner differences in the
foils and, indeed, when it is evaluated on foils where only word order
changes its performance is no longer
significant.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p5">
        <p class="ltx_p">
         On
msrvid, the plf approach outperforms add and mult, although the difference between the three is not big. Our result stands in contrast with
         Blacoe and Lapata (2012)
         , the only study we are aware of that
compared a sophisticated composition model (Socher et al.’s 2011
model) to add and mult on realistic sentences, which attained the top
performance with the simple models for both figures of merit they
used.
         The
best 2012 STS system
         [7]
         , obtained 0.87 correlation,
but with many more and considerably more complex features than the
ones we used here. Indeed, our simple system would have obtained a
respectable 25/89 ranking in the STS 2012 msrvid task. Still, we must
also stress the impressive performance of our baseline, given by the
combination of the word overlap and sentence length cues. This
suggests that the msrvid benchmark lacks the lexical and
syntactic variety we would like to test our systems on.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p6">
        <p class="ltx_p">
         Our plf model is again the best on the onwn set (albeit by a small margin
over add). This is a very positive result, in the light of the fact that
the parser has very low performance on the onwn glosses, thus
suggesting that plf can produce sensible semantic vectors from noisy
syntactic representations. Here the overlap+length baseline does not
perform so well, and again the best STS 2013 system
         [16]
         uses considerably richer knowledge sources and
algorithms than ours. Our plf-based method would have reached a
respectable 20/90 rank in the STS 2013 onwn task.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p7">
        <p class="ltx_p">
         As a final remark, in all experiments the running time of plf was only
slightly larger than for the simpler models, but orders of magnitude
smaller than lf, confirming another practical side of our approach.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
