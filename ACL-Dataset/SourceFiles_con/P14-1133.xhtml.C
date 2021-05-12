<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Semantic Parsing via Paraphrasing.
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
       A central challenge in semantic parsing is handling the myriad ways in which
knowledge base predicates can be expressed.
Traditionally, semantic parsers are trained primarily from text paired with
knowledge base information.
Our goal is to exploit the much larger amounts of raw text not tied to
any knowledge base.
In this paper, we turn semantic parsing on its head.
Given an input utterance, we first use a
simple method to deterministically generate a set of candidate logical forms
with a canonical realization in natural language for each.
Then, we use a paraphrase model to choose the realization
that best paraphrases the input, and output the corresponding logical form.
We present two simple paraphrase models,
an
       association
       model and a
       vector space
       model, and train them
jointly from question-answer pairs. Our system
       ParaSempre
       improves state-of-the-art
accuracies on two recently released question-answering datasets.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       leftmargin=0cm,labelindent=0cm
      </p>
     </div>
     <span class="ltx_ERROR undefined">
      \isundefined
     </span>
     <span class="ltx_ERROR undefined">
      \ifthenelse
     </span>
     <span class="ltx_ERROR undefined">
      \assumption
     </span>
     <span class="ltx_ERROR undefined">
      \isundefined
     </span>
     <span class="ltx_ERROR undefined">
      \ifthenelse
     </span>
     <span class="ltx_ERROR undefined">
      \theorem
     </span>
     <span class="ltx_ERROR undefined">
      \isundefined
     </span>
     <span class="ltx_ERROR undefined">
      \ifthenelse
     </span>
     <span class="ltx_ERROR undefined">
      \corollary
     </span>
     <span class="ltx_ERROR undefined">
      \isundefined
     </span>
     <span class="ltx_ERROR undefined">
      \ifthenelse
     </span>
     <span class="ltx_ERROR undefined">
      \example
     </span>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Introduction
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        We consider the semantic parsing problem of mapping natural language utterances into
logical forms to be executed on a knowledge base (KB)
        [35, 36, 34, 20]
        .
Scaling semantic parsers to large knowledge bases
has attracted substantial attention recently
        [2, 1, 19]
        ,
since it drives applications such as question answering (QA) and information
extraction (IE).
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Semantic parsers need to somehow associate natural language phrases with logical
predicates, e.g., they must learn that the constructions
        “What does X do for a living?”
        ,
        “What is X’s profession?”
        , and
        “Who is X?”
        , should all map to the logical predicate
        Profession
        .
To learn these mappings,
traditional semantic parsers use data
which pairs natural language with the KB.
However, this leaves untapped a vast amount of text not related to the KB.
For instance, the utterances
        “Where is ACL in 2014?”
        and
        “What is the location of ACL 2014?”
        cannot
be used in traditional semantic parsing methods, since the KB does not contain
an entity
        ACL2014
        , but this pair clearly
contains valuable linguistic information.
As another reference point, out of 500,000 relations
extracted by the ReVerb Open IE system
        [9]
        , only
about 10,000 can be aligned to
Freebase
        [1]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we present a novel approach for semantic parsing based on
paraphrasing
that can exploit large amounts of text not
covered by the KB (Figure
        1
        ).
Our approach targets factoid questions with a modest amount of
compositionality.
Given an input utterance,
we first use a simple deterministic procedure
to construct a manageable set of candidate logical forms
(ideally, we would generate canonical utterances
for all possible logical forms, but this is intractable).
Next, we heuristically generate
        canonical utterances
        for each logical
form based on the text descriptions of predicates from the KB.
Finally, we choose the canonical utterance that best paraphrases the input
utterance, and thereby the logical form that generated it.
We use two complementary
paraphrase models: an
        association model
        based on
aligned phrase pairs extracted from a monolingual parallel corpus, and a
        vector space model
        , which represents each utterance as a vector and
learns a similarity score between them. The entire system is trained jointly
from question-answer pairs only.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Our work relates to recent lines of research in semantic parsing and question answering.
        Kwiatkowski et al. (2013)
        first maps
utterances to a domain-independent
        intermediate logical form
        , and then performs ontology matching to produce
the final logical form.
In some sense, we approach the problem from the opposite end,
using an
        intermediate utterance
        ,
which allows us to employ paraphrasing methods (Figure
        2
        ).
        Fader et al. (2013)
        presented a QA system
that maps questions onto simple queries against Open IE extractions,
by learning paraphrases from a large monolingual parallel corpus, and
performing a single paraphrasing step.
We adopt the idea of using paraphrasing
for QA, but suggest a more general paraphrase model and work against a formal
KB (Freebase).
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We apply our semantic parser on two datasets:
        WebQuestions
        [1]
        , which contains
5,810 question-answer pairs with common questions
asked by web users; and
        Free917
        [2]
        ,
which has 917 questions manually authored by annotators.
On
        WebQuestions
        , we obtain a relative improvement of 12% in accuracy over
the state-of-the-art, and on
        Free917
        we match the current best performing system.
The source code of our system
        ParaSempre
        is released at
        http://www-nlp.stanford.edu/software/sempre/
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Setup
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Our task is as follows: Given
(i) a knowledge base
        𝒦
        , and (ii) a training set of question-answer pairs
        {(xi,yi)}i=1n
        ,
output a semantic parser that maps new questions
        x
        to answers
        y
        via latent logical forms
        z
        .
Let
        ℰ
        denote a set of
        entities
        (e.g.,
        BillGates
        ),
and let
        𝒫
        denote a set of
        properties
        (e.g.,
        PlaceOfBirth
        ).
A
        knowledge base
        𝒦
        is a set of
        assertions
        (e1,p,e2)∈ℰ×𝒫×ℰ
        (e.g.,
        (𝙱𝚒𝚕𝚕𝙶𝚊𝚝𝚎𝚜,𝙿𝚕𝚊𝚌𝚎𝙾𝚏𝙱𝚒𝚛𝚝𝚑,𝚂𝚎𝚊𝚝𝚝𝚕𝚎)
        ).
We use the Freebase KB
        [13]
        ,
which has 41M entities, 19K properties, and 596M
assertions.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        To query the KB, we use a logical language called
        simple λ-DCS
        .
In simple
        λ
        -DCS, an entity (e.g.,
        Seattle
        ) is a unary predicate (i.e., a subset
of
        ℰ
        ) denoting a singleton set containing that entity.
A property (which is a binary predicate) can be joined with a unary predicate;
e.g.,
        Founded.Microsoft
        denotes the entities that are Microsoft
founders. In
        PlaceOfBirth.Seattle⊓Founded.Microsoft
        ,
an intersection operator allows us to
denote
the set of Seattle-born Microsoft founders. A reverse operator reverses
the order of arguments:
        𝐑[PlaceOfBirth].BillGates
        denotes
Bill Gates’s birthplace (in contrast to
        PlaceOfBirth.Seattle
        ). Lastly,
        𝚌𝚘𝚞𝚗𝚝(𝙵𝚘𝚞𝚗𝚍𝚎𝚍.𝙼𝚒𝚌𝚛𝚘𝚜𝚘𝚏𝚝)
        denotes set cardinality,
in this case, the number of Microsoft founders.
The denotation of a logical form
        z
        with respect to a KB
        𝒦
        is given by
        \llbracket⁢z⁢\rrbracket𝒦
        .
For a formal description of simple
        λ
        -DCS,
see
        Liang (2013)
        and
        Berant et al. (2013)
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Model overview
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We now present the general framework for semantic parsing via
paraphrasing, including the model and the learning algorithm.
In Sections
        4
        and
        5
        ,
we provide the details of our implementation.
       </p>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Canonical utterance construction
       </h4>
       <div class="ltx_para" id="S3.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         Given an utterance
         x
         and the
KB, we construct a set of candidate logical forms
         𝒵x
         ,
and then for each
         z∈𝒵x
         generate a small set of canonical
natural language utterances
         𝒞z
         . Our goal at this point is only to generate
a manageable set of logical forms containing the correct one, and then generate
an appropriate canonical utterance from it. This strategy
is feasible in factoid QA where compositionality is
low, and so the size of
         𝒵x
         is limited (Section
         4
         ).
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Paraphrasing
       </h4>
       <div class="ltx_para" id="S3.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         We score the canonical utterances in
         𝒞z
         with respect to the input
utterance
         x
         using a paraphrase model, which offers two advantages.
First, the paraphrase model is decoupled from the KB, so we can
train it from large text corpora. Second,
natural language utterances often do not express predicates explicitly, e.g.,
the question
         “What is Italy’s money?”
         expresses the binary predicate
         CurrencyOf
         with a possessive
construction. Paraphrasing methods are well-suited for handling such
text-to-text gaps.
Our framework accommodates any paraphrasing method,
and in this paper we propose an
         association model
         that learns to
associate natural language phrases that co-occur frequently in a monolingual
parallel corpus, combined with a
         vector space model
         , which learns to
score the similarity between vector representations
of natural language utterances (Section
         5
         ).
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P3">
       <h4 class="ltx_title ltx_title_paragraph">
        Model
       </h4>
       <div class="ltx_para" id="S3.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         We define a discriminative log-linear model that places a probability
distribution over pairs of logical forms and canonical utterances
         (c,z)
         ,
given an utterance
         x
         :
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           pθ(c,z∣x)=exp⁡{ϕ⁢(x,c,z)⊤⁢θ}∑z′∈𝒵x,c′∈𝒞zexp⁡{ϕ⁢(x,c′,z′)⊤⁢θ},
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         θ∈ℝb
         is the vector of parameters to be learned,
and
         ϕ⁢(x,c,z)
         is a feature vector extracted from the input utterance
         x
         , the
canonical utterance
         c
         , and the logical form
         z
         .
Note that the candidate set of logical forms
         𝒵x
         and canonical utterances
         𝒞x
         are constructed during the canonical utterance
construction phase.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P3.p2">
        <p class="ltx_p">
         The model score decomposes into two terms:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ϕ⁢(x,c,z)⊤⁢θ=ϕpr⁢(x,c)⊤⁢θpr+ϕlf⁢(x,z)⊤⁢θlf,
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where the parameters
         θpr
         define the paraphrase model (Section
         5
         ), which is based on features
extracted from text only (the input and canonical utterance). The parameters
         θlf
         correspond to semantic parsing features based on the logical form and input utterance, and
are briefly described in this section.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P3.p3">
        <p class="ltx_p">
         Many existing paraphrase models introduce latent variables to describe the
         derivation
         of
         c
         from
         x
         , e.g., with transformations
         [16, 29]
         or alignments
         [14, 6, 3]
         .
However, we opt for a simpler paraphrase model without latent variables
in the interest of efficiency.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P4">
       <h4 class="ltx_title ltx_title_paragraph">
        Logical form features
       </h4>
       <div class="ltx_para" id="S3.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         The parameters
         θlf
         correspond to the following
features adopted from
         Berant et al. (2013)
         . For a logical form
         z
         , we
extract the size of its denotation
         \llbracket⁢z⁢\rrbracket𝒦
         . We also add all binary predicates
in
         z
         as features. Moreover, we extract a popularity feature for predicates based on
the number of instances they have in
         𝒦
         . For Freebase entities, we extract a popularity
feature based on the entity frequency in an entity linked subset of Reverb
         [22]
         . Lastly, Freebase formulas have types (see Section
         4
         ),
and we conjoin the type of
         z
         with the first
word of
         x
         , to capture the correlation between a word (e.g.,
         “where”
         )
with the Freebase type (e.g.,
         Location
         ).
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P5">
       <h4 class="ltx_title ltx_title_paragraph">
        Learning
       </h4>
       <div class="ltx_para" id="S3.SS0.SSS0.P5.p1">
        <p class="ltx_p">
         As our training data consists of question-answer pairs
         (xi,yi)
         ,
we maximize the log-likelihood of the correct answer.
The probability of an answer
         y
         is obtained by marginalizing over
canonical utterances
         c
         and logical forms
         z
         whose denotation is
         y
         .
Formally, our objective function
         𝒪⁢(θ)
         is as follows:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           𝒪(θ)=∑i=1nlogpθ(yi∣xi)-λ∥θ∥1,
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           pθ(y∣x)=∑z∈𝒵x:y=\llbracket⁢z⁢\rrbracket𝒦∑c∈𝒞zpθ(c,z∣x).
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         The strength
         λ
         of the
         L1
         regularizer is set based on
cross-validation.
We optimize the objective by initializing the parameters
         θ
         to zero
and running AdaGrad
         [8]
         .
We approximate the set of pairs of logical forms and canonical utterances with
a beam of size 2,000.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Canonical utterance construction
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We construct canonical utterances in two steps.
Given an input utterance
        x
        ,
we first construct a set of logical forms
        𝒵x
        , and then
generate canonical utterances from each
        z∈𝒵x
        .
Both steps are performed
with a small and simple set of deterministic rules,
which suffices for our datasets,
as they consist of factoid questions with a modest amount of compositional
structure.
We describe these rules below for completeness.
Due to its soporific effect though,
we advise the reader to skim it quickly.
       </p>
      </div>
      <div class="ltx_paragraph" id="S4.SS0.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Candidate logical forms
       </h4>
       <div class="ltx_para" id="S4.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         We consider logical forms
defined by a set of templates, summarized in Table
         1
         .
The basic template is a join of a binary and an entity,
where a binary can either be one property
         p.e
         (#1 in the table) or two properties
         p1.p2.e
         (#2). To handle cases of events involving multiple arguments
(e.g.,
         “Who did Brad Pitt play in Troy?”
         ), we introduce the template
         p.(p1.e1⊓p2.e2)
         (#3), where the main event
is modified by more than one entity. Logical forms
can be further modified by a unary “filter”, e.g., the answer to
         “What composers spoke French?”
         is a set
of composers, i.e., a subset of all people (#4). Lastly, we handle
aggregation formulas for utterances such as
         “How many teams are in the
NCAA?”
         (#5).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P1.p2">
        <p class="ltx_p">
         To construct candidate logical forms
         𝒵x
         for a given
utterance
         x
         , our strategy is to find an entity in
         x
         and grow the logical form from that entity.
As we show later, this procedure actually produces a
set with better coverage than constructing logical forms recursively from spans of
         x
         ,
as is done in traditional semantic parsing.
Specifically, for every span of
         x
         ,
we take at most 10 entities whose Freebase descriptions approximately match the
span.
Then, we join each entity
         e
         with all type-compatible
         binaries
         b
         , and add these logical forms to
         𝒵x
         (#1 and #2).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P1.p3">
        <p class="ltx_p">
         To construct logical forms with multiple entities (#3) we do the following:
For any logical form
         z=p.p1.e1
         , where
         p1
         has type signature
         (t1, *)
         ,
we look for other entities
         e2
         that were matched in
         x
         . Then, we add the
logical form
         p.(p1.e1⊓p2.e2)
         ,
if there exists a binary
         p2
         with a compatible type signature
         (t1,t2)
         , where
         t2
         is one of
         e2
         ’s types.
For example, for the logical form
         Character.Actor.BradPitt
         , if we match the entity
         Troy
         in
         x
         , we obtain
         Character.(Actor.BradPitt ⊓ Film.Troy)
         . We further modify
logical forms by intersecting with a unary filter (#4): given
a formula
         z
         with some Freebase type (e.g.,
         People
         ),
we look at all Freebase sub-types
         t
         (e.g.,
         Composer
         ), and check whether
one of their Freebase descriptions (e.g.,
         “composer”
         ) appears in
         x
         .
If so, we add the formula
         𝚃𝚢𝚙𝚎.t⊓z
         to
         𝒵x
         . Finally, we check whether
         x
         is an aggregation formula by identifying whether it
starts with phrases such as
         “how many”
         or
         “number of”
         (#5).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P1.p4">
        <p class="ltx_p">
         On
         WebQuestions
         , this results in 645 formulas per utterance on average.
Clearly, we can increase the expressivity of this step by expanding the
template set.
For example,
we could handle superlative utterances (
         “What NBA player
is tallest?”
         ) by adding a template with an
         argmax
         operator.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS0.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Utterance generation
       </h4>
       <div class="ltx_para" id="S4.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         While mapping general language utterances to logical forms is hard,
we observe that it is much easier to
generate a
         canonical
         natural language utterances of our choice
given a logical form.
Table
         2
         summarizes the rules used to generate canonical utterances from the template
         p.e
         . Questions begin with a question word, are followed by the Freebase
description of the expected answer type (
         d⁢(t)
         ), and followed by Freebase
descriptions of the entity (
         d⁢(e)
         ) and binary (
         d⁢(p)
         ).
To fill in auxiliary verbs, determiners, and prepositions,
we parse the description
         d⁢(p)
         into one of
         NP
         ,
         VP
         ,
         PP
         ,
or
         NP VP
         .
This determines the generation rule to be used.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         Each Freebase property
         p
         has an explicit property
         p′
         equivalent to the reverse
         𝐑⁢[p]
         (e.g.,
         ContainedBy
         and
         𝐑⁢[𝙲𝚘𝚗𝚝𝚊𝚒𝚗𝚜]
         ).
For each logical form
         z
         , we also generate using equivalent logical forms
where
         p
         is replaced with
         𝐑⁢[p′]
         .
Reversed formulas have different generation rules,
since entities in these formulas are in the subject position rather than object position.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P2.p3">
        <p class="ltx_p">
         We generate the description
         d⁢(t)
         from the Freebase description of the type of
         z
         (this handles #4).
For the template
         p1.p2.e
         (#2), we have a similar set of rules, which
depends on the syntax of
         d⁢(p1)
         and
         d⁢(p2)
         and is omitted for brevity.
The template
         p.(p1.e1⊓p2.e2)
         (#3) is generated by
appending the prepositional phrase
         in d⁢(e2)
         ,
e.g,
         “What character is the character of Brad Pitt in Troy?”
         .
Lastly, we choose the question phrase
         “How many”
         for aggregation formulas (#5), and
         “What”
         for all other formulas.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS0.SSS0.P2.p4">
        <p class="ltx_p">
         We also generate canonical utterances using an alignment lexicon,
released by
         Berant et al. (2013)
         , which maps text phrases to Freebase
binary predicates. For a binary predicate
         b
         mapped from text phrase
         d⁢(b)
         , we generate the utterance
         WH d⁢(t) d⁢(b) d⁢(e) ?
         . On the
         WebQuestions
         dataset,
we generate an average of 1,423 canonical
utterances
         c
         per input utterance
         x
         .
In Section
         6
         , we show that an even simpler
method of generating canonical utterances by concatenating Freebase
descriptions hurts accuracy by only a modest amount.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Paraphrasing
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Once the candidate set of logical forms paired with canonical utterances is constructed,
our problem is reduced to scoring pairs
        (c,z)
        based on a paraphrase model.
The NLP paraphrase literature is vast and ranges from simple methods employing surface
features
        [32]
        , through vector space models
        [28]
        , to
latent variable models
        [6, 33, 29]
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        In this paper, we focus on two paraphrase models that emphasize simplicity and efficiency.
This is important since for each question-answer pair,
we consider thousands of canonical utterances as potential paraphrases.
In contrast, traditional paraphrase detection
        [7]
        and Recognizing Textual Entailment (RTE) tasks
        [4]
        consider examples consisting of only a single pair of
candidate paraphrases.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Our paraphrase model decomposes into an
        association model
        and a
        vector space model
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx4">
        <tr class="ltx_equation ltx_align_baseline" id="S5.Ex5">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          ϕpr⁢(x,c)⊤⁢θpr=ϕas⁢(x,c)⊤⁢θas+ϕvs⁢(x,c)⊤⁢θvs.
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Association model
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         The goal of the association model is to determine whether
         x
         and
         c
         contain phrases that are likely to be paraphrases.
Given an utterance
         x=⟨x0,x1,..,xn-1⟩
         , we denote by
         xi:j
         the
span from token
         i
         to token
         j
         . For each pair of utterances
         (x,c)
         ,
we go through all spans of
         x
         and
         c
         and identify
a set of pairs
of potential paraphrases
         (xi:j,ci′:j′)
         ,
which we call
         associations
         .
(We will describe how associations are identified shortly.)
We then define features on each association;
the weighted combination of these features yields a score.
In this light, associations can be viewed as soft paraphrase rules.
Figure
         3
         presents examples of associations extracted
from a paraphrase pair and visualizes the learned scores.
We can see that our model
learns a positive score for associating
         “type”
         with
         “genres”
         ,
and a negative score for associating
         “is”
         with
         “play”
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         We define associations in
         x
         and
         c
         primarily by looking up phrase
pairs in a phrase table constructed using the
         Paralex
         corpus
         [10]
         .
         Paralex
         is a large monolingual parallel corpora,
containing 18 million pairs of question paraphrases from
         wikianswers.com
         ,
which were tagged as having the same meaning by users.
         Paralex
         is suitable for our needs
since it focuses on
         question
         paraphrases.
For example, the phrase
         “do for a living”
         occurs mostly in questions, and we can extract associations for this phrase from
         Paralex
         .
Paraphrase pairs in
         Paralex
         are word-aligned using standard machine translation methods.
We use the word alignments to construct a phrase table
by applying the consistent phrase pair heuristic
         [24]
         to all 5-grams.
This results in a phrase table with
approximately 1.3 million phrase pairs.
We let
         𝒜
         denote this set of mined candidate associations.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         For a pair
         (x,c)
         , we also consider as candidate associations the set
         ℬ
         (represented implicitly),
which contains token pairs
         (xi,ci′)
         such that
         xi
         and
         ci′
         share the
same lemma, the same POS tag, or are linked through a
         derivation
         link on WordNet
         [11]
         .
This allows us to learn paraphrases for words that appear in our datasets but are not covered
by the phrase table, and to handle nominalizations for phrase pairs such as
         “Who designed the
game of life?”
         and
         “What game designer is the designer of the game of life?”
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Our model goes over all possible spans of
         x
         and
         c
         and constructs all possible associations from
         𝒜
         and
         ℬ
         .
This results in many poor associations (e.g.,
         “play”
         and
         “the”
         ),
but as illustrated in Figure
         3
         ,
we learn weights that discriminate good from bad associations.
Table
         3
         specifies the full set of features.
Note that unlike standard paraphrase detection
and RTE systems, we use lexicalized features,
firing approximately 400,000 features on
         WebQuestions
         .
By extracting POS features, we obtain soft syntactic rules, e.g., the feature
“
         JJ N
         ∧
         N
         ” indicates that omitting adjectives before nouns is possible. Once associations are constructed, we mark tokens in
         x
         and
         c
         that were
not part of any association, and extract deletion features for their lemmas and POS tags. Thus, we learn that
deleting pronouns is acceptable, while deleting nouns is not.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p5">
        <p class="ltx_p">
         To summarize, the association model links phrases of two utterances in multiple overlapping ways.
During training, the model learns which associations are characteristic of
paraphrases and which are not.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Vector space model
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         The association model relies on having a good set of candidate associations,
but mining associations suffers from coverage issues.
We now introduce a vector space (VS) model,
which assigns a vector representation for each utterance, and learns a scoring
function that ranks paraphrase candidates.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         We start by constructing vector representations of words.
We run the
         word2vec
         tool
         [23]
         on lower-cased Wikipedia text
(1.59 billion tokens), using the CBOW model with a window of 5 and hierarchical softmax.
We also experiment with publicly released word embeddings
         [17]
         , which were trained using both local and global
context. Both result in
         k
         -dimensional vectors (
         k=50
         ).
Next, we construct a vector
         vx∈ℝk
         for each utterance
         x
         by simply averaging the vectors of all content words (nouns,
verbs, and adjectives) in
         x
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         We can now estimate a paraphrase score for
two utterances
         x
         and
         c
         via a weighted combination of the components of the vector representations:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx5">
         <tr class="ltx_equation ltx_align_baseline" id="S5.Ex6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           vx⊤⁢W⁢vc=∑i,j=1kwi⁢j⁢vx,i⁢vc,j
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         W∈ℝk×k
         is a parameter matrix.
In terms of our earlier notation,
we have
         θvs=vec⁢(W)
         and
         ϕvs⁢(x,c)=vec⁢(vx⁢vc⊤)
         ,
where
         vec⁢(⋅)
         unrolls a matrix into a vector.
In Section
         6
         , we experiment with
         W
         equal to the identity matrix,
constraining
         W
         to be diagonal, and learning a full
         W
         matrix.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         The VS model can identify correct paraphrases in cases where it is hard to directly associate phrases from
         x
         and
         c
         . For example, the answer to
         “Where is made Kia car?”
         (from
         WebQuestions
         ), is given
by the canonical utterance
         “What city is Kia motors a headquarters of?”
         . The association model does not associate
         “made”
         and
         “headquarters”
         , but the VS model is able to determine that these utterances are semantically related.
In other cases, the VS model cannot distinguish correct paraphrases from incorrect ones.
For example, the association model identifies
that the paraphrase for
         “What type of music did Richard Wagner Play?”
         is
         “What is the musical genres of Richard Wagner?”
         , by relating phrases such as
         “type of music”
         and
         “musical genres”
         .
The VS model ranks the canonical utterance
         “What composition has Richard Wagner as lyricist?”
         higher, as this utterance is also in the music domain.
Thus, we combine the two models to benefit from their complementary nature.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p5">
        <p class="ltx_p">
         In summary, while the association model aligns particular phrases to one
another, the vector space model provides a soft vector-based representation for
utterances.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Empirical evaluation
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        In this section, we evaluate our system on
        WebQuestions
        and
        Free917
        .
After describing the setup (Section
        6.1
        ), we
present our main empirical results
and analyze the components of the system (Section
        6.2
        ).
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        Setup
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         We use the
         WebQuestions
         dataset
         [1]
         , which
contains 5,810 question-answer pairs. This dataset was created by crawling
questions through the Google Suggest API, and then obtaining answers using
Amazon Mechanical Turk. We use the original train-test split, and divide the
training set into 3 random 80%–20% splits for development. This dataset is
characterized by questions that are commonly asked on the web (and are
not necessarily grammatical), such as
         “What
character did Natalie Portman play in Star Wars?”
         and
         “What kind of money to
take to Bahamas?”
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         The
         Free917
         dataset contains 917 questions, authored by two annotators and annotated with logical forms.
This dataset contains questions on rarer topics (for example,
         “What is the engine in a 2010 Ferrari California?”
         and
         “What was the cover price of the X-men Issue 1?”
         ),
but the phrasing of questions tends to be more rigid compared to
         WebQuestions
         . Table
         4
         provides some statistics on
the two datasets.
Following
         Cai and Yates (2013)
         , we hold out 30% of the data for the final test, and perform 3 random 80%-20% splits of the training set for development. Since we train from question-answer pairs, we collect answers by executing the gold logical forms against Freebase.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p3">
        <p class="ltx_p">
         We execute
         λ
         -DCS queries by converting them into SPARQL and executing them against a copy of Freebase using the Virtuoso database engine. We evaluate our system with accuracy, that is, the proportion of questions we answer correctly. We run all questions through the Stanford CoreNLP pipeline
         [30, 12, 18]
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p4">
        <p class="ltx_p">
         We tuned the
         L1
         regularization strength,
developed features,
and ran analysis experiments on the development set (averaging across random splits).
On
         WebQuestions
         ,
without
         L1
         regularization, the number of non-zero features was 360K;
         L1
         regularization brings it down to 17K.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         We compare our system to
         Cai and Yates (2013)
         (
         CY13
         ),
         Berant et al. (2013)
         (
         BCFL13
         ), and
         Kwiatkowski et al. (2013)
         (
         KCAZ13
         ).
For
         BCFL13
         , we obtained results using the
         Sempre
         package
         and running
         Berant et al. (2013)
         ’s system on the datasets.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         Table
         5
         presents results on the test set.
We achieve a substantial relative improvement of 12% in accuracy
on
         WebQuestions
         , and match the best results on
         Free917
         .
Interestingly, our system gets an
         oracle accuracy
         of 63% on
         WebQuestions
         compared to 48% obtained by
         BCFL13
         , where
the oracle accuracy is the fraction of questions for which at least
one logical form in the candidate set produced by the system is correct.
This demonstrates that our method for constructing candidate logical forms is
reasonable. To further examine this, we ran
         BCFL13
         on the development
set, allowing it to use only predicates from logical forms suggested by
our logical form construction step. This improved oracle accuracy on the development set to 64.5%, but accuracy was 32.2%. This shows that the improvement in accuracy should not be attributed only to better logical form generation, but also to the paraphrase model.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         We now perform more extensive analysis of our system’s components and compare it to various baselines.
        </p>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Component ablation
        </h4>
        <div class="ltx_para" id="S6.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          We ablate the association model,
the VS model, and the entire paraphrase model (using only logical form features).
Table
          5
          shows that our full system obtains highest accuracy,
and that removing the association model results in a much larger degradation
compared to removing the VS model.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Utterance generation
        </h4>
        <div class="ltx_para" id="S6.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          Our system generates relatively natural utterances from logical forms using simple rules based on Freebase descriptions (Section
          4
          ).
We now consider simply concatenating Freebase descriptions.
For example, the logical form
          𝐑
          [PlaceOfBirth].ElvisPresley
          would generate the utterance
          “What location Elvis Presley place of birth?”
          .
Row
          SimpleGen
          in Table
          6
          demonstrates that we still get good results in this setup.
This is expected given that our paraphrase models are not sensitive to the
syntactic structure of the generated utterance.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         VS model
        </h4>
        <div class="ltx_para" id="S6.SS2.SSS0.P3.p1">
         <p class="ltx_p">
          Our system learns parameters for a full
          W
          matrix. We now examine
results when learning parameters for a full matrix
          W
          , a diagonal
matrix
          W
          , and when setting
          W
          to be the identity matrix.
Table
          6
          (third section) illustrates that learning a full matrix substantially improves accuracy.
Figure
          4
          gives an example for a
correct paraphrase pair, where the full matrix model boosts the overall model score.
Note that the full matrix assigns
a high score for the phrases
          “official language”
          and
          “speak”
          compared to the simpler models,
but other pairs are less interpretable.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS0.P4">
        <h4 class="ltx_title ltx_title_paragraph">
         Baselines
        </h4>
        <div class="ltx_para" id="S6.SS2.SSS0.P4.p1">
         <p class="ltx_p">
          We also compared our system to the following implemented baselines:
         </p>
         <ul class="ltx_itemize" id="I1">
          [noitemsep,topsep=0pt]
          <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i1.p1">
            <p class="ltx_p">
             Jaccard
             : We compute the Jaccard score between the tokens of
             x
             and
             c
             and
define
             ϕpr⁢(x,c)
             to be this single feature.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i2.p1">
            <p class="ltx_p">
             Edit
             : We compute the token edit distance between
             x
             and
             c
             and
define
             ϕpr⁢(x,c)
             to be this single feature.
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i3.p1">
            <p class="ltx_p">
             WDDC06
             : We re-implement 13 features from
             Wan et al. (2006)
             , who obtained close to state-of-the-art performance on the Microsoft Research paraphrase corpus.
            </p>
           </div>
          </li>
         </ul>
        </div>
        <div class="ltx_para" id="S6.SS2.SSS0.P4.p2">
         <p class="ltx_p">
          Table
          6
          demonstrates that we improve performance over all baselines. Interestingly,
          Jaccard
          and
          WDDC06
          obtain reasonable performance on
          Free917
          but perform much worse on
          WebQuestions
          .
We surmise this is because questions in
          Free917
          were generated by annotators
prompted by Freebase facts, whereas questions in
          WebQuestions
          originated independently of Freebase.
Thus, word choice in
          Free917
          is often close to the generated Freebase descriptions, allowing simple baselines to perform well.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS0.P5">
        <h4 class="ltx_title ltx_title_paragraph">
         Error analysis
        </h4>
        <div class="ltx_para" id="S6.SS2.SSS0.P5.p1">
         <p class="ltx_p">
          We sampled examples from the development set to examine the main reasons
          ParaSempre
          makes errors. We notice
that in many cases the paraphrase model can be further improved. For example,
          ParaSempre
          suggests that
the best paraphrase for
          “What company did Henry Ford work for?”
          is
          “What written work novel by Henry Ford?”
          rather than
          “The employer of Henry Ford”
          , due to the exact match of the word
          “work”
          . Another example is the question
          “Where is the Nascar hall of fame?”
          , where
          ParaSempre
          suggests that
          “What hall of fame discipline has Nascar hall of fame as halls of fame?”
          is the best canonical utterance. This is because
our simple model allows to associate
          “hall of fame”
          with the canonical utterance three times. Entity recognition also accounts
for many errors, e.g., the entity chosen in
          “where was the gallipoli campaign waged?”
          is
          Galipoli
          and not
          GalipoliCampaign
          . Last,
          ParaSempre
          does not handle temporal information, which causes errors in questions like
          “Where did Harriet Tubman live after the civil war?”
         </p>
        </div>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
