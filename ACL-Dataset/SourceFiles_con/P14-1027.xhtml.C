<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Modelling function words improves unsupervised word segmentation.
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
       Inspired by experimental psychological findings suggesting that
function words play a special role in word learning, we make a
simple modification to an Adaptor Grammar based Bayesian word
segmentation model to allow it to learn sequences of monosyllabic
“function words” at the beginnings and endings of collocations of
(possibly multi-syllabic) words. This modification improves
unsupervised word segmentation on the standard
       corpus of child-directed English by more
than 4% token f-score compared to a model identical except that it
does not special-case “function words”, setting a new
state-of-the-art of 92.4% token f-score.
Our function word model assumes that function words appear at the
left periphery, and while this is true of languages such as
English, it is not true universally. We show that a learner can
use Bayesian model selection to determine the location of function
words in their language, even though the input to the model only
consists of unsegmented sequences of phones. Thus our computational
models support the hypothesis that function words play a special
role in word learning.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       SIL/I”
      </p>
     </div>
     <div class="ltx_para" id="p2">
      <svg height="50" version="1.1" viewbox="192 -236 65 50" width="65" xmlns="http://www.w3.org/2000/svg">
       <g transform="matrix(1 0 0 -1 0 -422)">
        <g>
         <g stroke="#000000">
          <g fill="#000000">
           <g stroke-width="0.4pt">
            <g>
             <g>
              <path d="M225-206L206-213" style="fill:none">
              </path>
             </g>
             <g>
              <path d="M225-206L244-213" style="fill:none">
              </path>
             </g>
             <g>
              <g>
               <g transform="matrix(1 0 0 1 220 -200)">
                <g class="ltx_svg_fog" transform="matrix(1 0 0 -1 0 10)">
                 <switch>
                  <foreignobject color="#000000" height="12" overflow="visible" width="10">
                   <p class="ltx_p" xmlns="http://www.w3.org/1999/xhtml">
                    X
                   </p>
                  </foreignobject>
                 </switch>
                </g>
               </g>
              </g>
             </g>
             <g>
              <g>
               <g transform="matrix(1 0 0 1 197 -225)">
                <g class="ltx_svg_fog" transform="matrix(1 0 0 -1 0 10)">
                 <switch>
                  <foreignobject color="#000000" height="16" overflow="visible" width="19">
                   <p class="ltx_p" xmlns="http://www.w3.org/1999/xhtml">
                    t1
                   </p>
                  </foreignobject>
                 </switch>
                </g>
               </g>
              </g>
             </g>
             <g>
              <g>
               <g transform="matrix(1 0 0 1 234 -225)">
                <g class="ltx_svg_fog" transform="matrix(1 0 0 -1 0 10)">
                 <switch>
                  <foreignobject color="#000000" height="16" overflow="visible" width="19">
                   <p class="ltx_p" xmlns="http://www.w3.org/1999/xhtml">
                    tn
                   </p>
                  </foreignobject>
                 </switch>
                </g>
               </g>
              </g>
             </g>
             <g>
              <g>
               <g transform="matrix(1 0 0 1 225 -225)">
                <g class="ltx_svg_fog" transform="matrix(1 0 0 -1 0 0)">
                 <switch>
                  <foreignobject color="#000000" height="0" overflow="visible" width="0">
                   <p class="ltx_p" xmlns="http://www.w3.org/1999/xhtml">
                    …
                   </p>
                  </foreignobject>
                 </switch>
                </g>
               </g>
              </g>
             </g>
            </g>
           </g>
          </g>
         </g>
        </g>
       </g>
      </svg>
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
        Over the past two decades psychologists have investigated the role
that function words might play in human language acquisition. Their
experiments suggest that function words play a special role in the
acquisition process: children learn function words before they learn
the vast bulk of the associated content words, and they use function
words to help identify context words.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The goal of this paper is to determine whether computational models of
human language acquisition can provide support for the hypothesis that
function words are treated specially in human language acquisition.
We do this by comparing two computational models of word segmentation
which differ solely in the way that they model function words.
Following
        and
        our word segmentation
models identify word boundaries from unsegmented sequences of phonemes
corresponding to utterances, effectively performing unsupervised
learning of a lexicon. For example, given input consisting of unsegmented
utterances such as the following:
       </p>
       <p class="ltx_p ltx_align_center">
        j  u  w  É  n  t  t  u  s  i  Ã°  É  b  Ê  k
       </p>
       <p class="ltx_p">
        a word segmentation model should segment this as ju wÉnt tu si
Ã°É bÊk, which is the IPA representation of “you want to see the book”.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We show that a model equipped with the ability to learn some rudimentary
properties of the target language’s function words is able to learn the
vocabulary of that language more accurately than a model that is identical
except that it is incapable of learning these generalisations about
function words.

This suggests that there are
acquisition advantages to treating function words specially that human
learners could take advantage of (at least to the extent that they are
learning similar generalisations as our models), and thus supports the
hypothesis that function words are treated specially in human lexical
acquisition.

As a reviewer points out, we present no evidence that children use function
words in the way that our model does, and we want to emphasise we make no such claim.

While absolute accuracy is not directly relevant to the
main point of the paper, we note that the models that learn
generalisations about function words perform unsupervised word
segmentation at 92.5% token f-score on the standard
        corpus, which improves the previous
state-of-the-art by more than 4%.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        As a reviewer points out, the changes we make to our models to incorporate
function words can be viewed as “building in” substantive information
about possible human languages.

The model that achieves the best token f-score expects function words
to appear at the left edge of phrases. While this is true for
languages such as English, it is not true universally. By comparing
the posterior probability of two models — one in which function
words appear at the left edges of phrases, and another in which
function words appear at the right edges of phrases — we show that a
learner could use Bayesian posterior probabilities to determine that
function words appear at the left edges of phrases in English, even
though they are not told the locations of word boundaries or which
words are function words.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        This paper is structured as follows. Section
        2
        describes the
specific word segmentation models studied in this paper, and the way we
extended them to capture certain properties of function words. The
word segmentation experiments are presented in section
        3
        ,
and section
        4
        discusses how a learner could determine
whether function words occur on the left-periphery or the
right-periphery in the language they are learning.
Section
        5
        concludes and describes possible future work.
The rest of this introduction provides background on function words,
the Adaptor Grammar models we use to describe lexical acquisition and
the Bayesian inference procedures we use to infer these models.
       </p>
      </div>
      <div class="ltx_subsection" id="S1.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.1
        </span>
        Psychological evidence for the role of function words in word learning
       </h3>
       <div class="ltx_para" id="S1.SS1.p1">
        <p class="ltx_p">
         Traditional descriptive linguistics distinguishes
         function words
         ,
such as determiners and prepositions, from
         content words
         , such
as nouns and verbs, corresponding roughly to the distinction between
functional categories and lexical categories of modern generative
linguistics
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p2">
        <p class="ltx_p">
         Function words differ from content words in at least the following
ways:
        </p>
        <ol class="ltx_enumerate" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            there are usually far fewer function word types than content
word types in a language
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            function word types typically have much higher token frequency
than content word types
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            function words are typically morphologically and phonologically
simple (e.g., they are typically monosyllabic)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           4.
          </span>
          <div class="ltx_para" id="I1.i4.p1">
           <p class="ltx_p">
            function words typically appear in peripheral positions of
phrases (e.g., prepositions typically appear at the beginning of
prepositional phrases)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           5.
          </span>
          <div class="ltx_para" id="I1.i5.p1">
           <p class="ltx_p">
            each function word class is associated with specific content
word classes (e.g., determiners and prepositions are associated with
nouns, auxiliary verbs and complementisers are associated with main
verbs)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           6.
          </span>
          <div class="ltx_para" id="I1.i6.p1">
           <p class="ltx_p">
            semantically, content words denote sets of objects or events, while
function words denote more complex relationships over the entities denoted
by content words
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           7.
          </span>
          <div class="ltx_para" id="I1.i7.p1">
           <p class="ltx_p">
            historically, the rate of innovation of function words is much
lower than the rate of innovation of content words (i.e., function
words are typically “closed class”, while content words are “open
class”)
           </p>
          </div>
         </li>
        </ol>
        <p class="ltx_p">
         Properties 1–4 suggest that function words might play a special role
in language acquisition because they are especially easy to identify,
while property 5 suggests that they might be useful for identifying
lexical categories. The models we study here focus on properties 3
and 4, in that they are capable of learning specific sequences of
monosyllabic words in peripheral (i.e., initial or final) positions of
phrase-like units.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p3">
        <p class="ltx_p">
         A number of psychological experiments have shown that infants are
sensitive to the function words of their language within their first
year of life
         []
         , often before they have
experienced the “word learning spurt”.

Crucially for our purpose, infants of this age were shown to
exploit frequent function words to segment neighboring content words
         []
         .

In addition, 14 to 18-month-old children
were shown to exploit function words to constrain lexical access to
known words â- for instance, they expect a noun after a determiner
         []
         .

In addition, it is plausible that function words play a crucial role
in children’s acquisition of more complex syntactic phenomena
         []
         , so it is interesting to investigate
the roles they might play in computational models of language
acquisition.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S1.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.2
        </span>
        Adaptor grammars
       </h3>
       <div class="ltx_para" id="S1.SS2.p1">
        <p class="ltx_p">
         Adaptor grammars are a framework for Bayesian inference of a certain
class of hierarchical non-parametric models
         []
         . They
define distributions over the trees specified by a context-free
grammar, but unlike probabilistic context-free grammars, they
“learn” distributions over the possible subtrees of a user-specified
set of “adapted” nonterminals. (Adaptor grammars are
non-parametric, i.e., not characterisable by a finite set of
parameters, if the set of possible subtrees of the adapted
nonterminals is infinite). Adaptor grammars are useful when the goal
is to learn a potentially unbounded set of entities that need to
satisfy hierarchical constraints. As section
         2
         explains in
more detail, word segmentation is such a case: words are composed of
syllables and belong to phrases or collocations, and modelling this
structure improves word segmentation accuracy.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p2">
        <p class="ltx_p">
         Adaptor Grammars are formally defined in
         , which
should be consulted for technical details. Adaptor Grammars (AGs) are
an extension of Probabilistic Context-Free Grammars (PCFGs), which we
describe first. A
         Context-Free Grammar
         (CFG)
         G=(N,W,R,S)
         consists of disjoint finite sets of
         nonterminal symbols
         N
         and
         terminal symbols
         W
         , a finite set of
         rules
         R
         of the
form
         A⁢→⁡α
         where
         A∈N
         and
         α∈(N∪W)⋆
         , and
a
         start symbol
         S∈N
         . (We assume there are no
“
         ϵ
         -rules” in
         R
         , i.e., we require that
         |α|≥1
         for each
         A⁢→⁡α∈R
         ).
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p3">
        <p class="ltx_p">
         A
         Probabilistic Context-Free Grammar
         (PCFG) is a quintuple
         (N,W,R,S,𝜽)
         where
         N
         ,
         W
         ,
         R
         and
         S
         are the
nonterminals, terminals, rules and start symbol of a CFG respectively,
and
         𝜽
         is a vector of non-negative reals indexed by
         R
         that
satisfy
         ∑α∈RAθA⁢→⁡α=1
         for each
         A∈N
         , where
         RA={A⁢→⁡α:A⁢→⁡α∈R}
         is the set of rules
expanding
         A
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p4">
        <p class="ltx_p">
         Informally,
         θA⁢→⁡α
         is the probability of a node
labelled
         A
         expanding to a sequence of nodes labelled
         α
         , and
the probability of a tree is the product of the probabilities of the
rules used to construct each non-leaf node in it. More precisely, for
each
         X∈N∪W
         a PCFG associates distributions
         GX
         over the set of
trees
         𝒯X
         generated by
         X
         as follows:
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p5">
        <p class="ltx_p">
         If
         X∈W
         (i.e., if
         X
         is a terminal) then
         GX
         is the
distribution that puts probability 1 on the single-node tree labelled
         X
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p6">
        <p class="ltx_p">
         If
         X∈N
         (i.e., if
         X
         is a nonterminal) then:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S1.E1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           GX
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑X⁢→⁡B1⁢…⁢Bn∈RXθX⁢→⁡B1⁢…⁢Bn⁢TDX⁢(GB1,…,GBn)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (1)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         RX
         is the subset of rules in
         R
         expanding nonterminal
         X∈N
         , and:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S1.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           TDX⁢(G1,…,Gn)⁢(11)
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∏i=1nGi⁢(ti).
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         That is,
         TDX⁢(G1,…,Gn)
         is a distribution over the
set of trees
         𝒯X
         generated by nonterminal
         X
         , where each subtree
         ti
         is generated independently from
         Gi
         . The PCFG generates the
distribution
         GS
         over the set of trees
         𝒯S
         generated by the start
symbol
         S
         ; the distribution over the strings it generates is obtained
by marginalising over the trees.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p7">
        <p class="ltx_p">
         In a Bayesian PCFG one puts Dirichlet priors
         Dir⁢(𝜶)
         on the
rule probability vector
         𝜽
         , such that there is one Dirichlet
parameter
         αA⁢→⁡α
         for each rule
         A⁢→⁡α∈R
         .
There are Markov Chain Monte Carlo (MCMC) and Variational Bayes procedures for estimating the posterior
distribution over rule probabilities
         𝜽
         and parse trees
given data consisting of terminal strings alone
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p8">
        <p class="ltx_p">
         PCFGs can be viewed as recursive mixture models over trees.
While PCFGs are expressive enough to describe a range of
linguistically-interesting phenomena, PCFGs are
         parametric
models
         , which limits their ability to describe phenomena where the
set of basic units, as well as their properties, are the target of
learning. Lexical acqusition is an example of a phenomenon that is
naturally viewed as
         non-parametric inference
         , where the number
of lexical entries (i.e., words) as well as their properties must be
learnt from the data.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p9">
        <p class="ltx_p">
         It turns out there is a straight-forward modification to
the PCFG distribution (
         1
         ) that makes it suitably non-parametric. As
         explain, by inserting a Dirichlet Process (DP) or
Pitman-Yor Process (PYP) into the generative mechanism (
         1
         )
the model “concentrates” mass on a subset of trees
         []
         .
Specifically, an Adaptor Grammar identifies a subset
         A⊆N
         of
         adapted nonterminals
         . In an Adaptor Grammar the unadapted
nonterminals
         N∖A
         expand via (
         1
         ), just as in a
PCFG, but the distributions of the adapted nonterminals
         A
         are
“concentrated” by passing them through a DP or PYP:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S1.Ex2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           HX
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           ∑X⁢→⁡B1⁢…⁢Bn∈RXθX⁢→⁡B1⁢…⁢Bn⁢TDX⁢(GB1,…,GBn)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S1.Ex3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           GX
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           PYP⁢(HX,aX,bX)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Here
         aX
         and
         bX
         are parameters of the PYP associated with the
adapted nonterminal
         X
         . As
         explain, such
Pitman-Yor Processes naturally generate power-law distributed data.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p10">
        <p class="ltx_p">
         Informally, Adaptor Grammars can be viewed as caching entire subtrees
of the adapted nonterminals. Roughly speaking, the probability of
generating a particular subtree of an adapted nonterminal is
proportional to the number of times that subtree has been generated
before. This “rich get richer” behaviour causes the distribution of
subtrees to follow a power-law (the power is specified by the
         aX
         parameter of the PYP). The PCFG rules expanding an adapted nonterminal
         X
         define the “base distribution” of the associated DP or PYP, and the
         aX
         and
         bX
         parameters determine how much mass is reserved for
“new” trees.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p11">
        <p class="ltx_p">
         There are several different procedures for inferring the parse trees
and the rule probabilities given a corpus of strings:
         describe a MCMC sampler and
         describe a Variational Bayes procedure. We use the MCMC procedure
here since this has been successfully applied to word segmentation
problems in previous work
         []
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
       Word segmentation with Adaptor Grammars
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Perhaps the simplest word segmentation model is the
        unigram
model
        , where utterances are modeled as sequences of words, and
where each word is a sequence of segments
        []
        .
A unigram model can be expressed as an Adaptor Grammar with one
adapted non-terminal
        𝖶𝗈𝗋𝖽¯
        (we indicate adapted nonterminals
by underlining them in grammars here; regular expressions are expanded
into right-branching productions).
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx4">
        <tr class="ltx_equation ltx_align_baseline" id="S2.E2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          𝖲𝖾𝗇𝗍𝖾𝗇𝖼𝖾
         </td>
         <td class="ltx_td ltx_align_left">
          →⁡𝖶𝗈𝗋𝖽+
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (2)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S2.E3">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          𝖶𝗈𝗋𝖽¯
         </td>
         <td class="ltx_td ltx_align_left">
          →⁡𝖯𝗁𝗈𝗇𝖾+
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (3)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        The first rule (
        2
        ) says that a sentence consists of one
or more
        𝖶𝗈𝗋𝖽
        s, while the second rule (
        3
        ) states
that a
        𝖶𝗈𝗋𝖽
        consists of a sequence of one or more
        𝖯𝗁𝗈𝗇𝖾
        s;
we assume that there are rules expanding
        𝖯𝗁𝗈𝗇𝖾
        into all possible
phones. Because
        𝖶𝗈𝗋𝖽
        is an adapted nonterminal, the adaptor
grammar memoises
        𝖶𝗈𝗋𝖽
        subtrees, which corresponds to learning
the phone sequences for the words of the language.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        The more sophisticated Adaptor Grammars discussed below can be
understood as specialising either the first or the second of the rules
in (
        2
        –
        3
        ). The next two subsections
review the Adaptor Grammar word segmentation models presented in
        and
        : section
        2.1
        reviews how phonotactic syllable-structure constraints can be
expressed with Adaptor Grammars, while section
        2.2
        reviews
how phrase-like units called “collocations” capture inter-word
dependencies. Section
        2.3
        presents the major novel
contribution of this paper by explaining how we modify these adaptor
grammars to capture some of the special properties of function words.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Syllable structure and phonotactics
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         The rule (
         3
         ) models words as sequences of independently
generated phones: this is what
         called the
“monkey model” of word generation (it instantiates the metaphor that
word types are generated by a monkey randomly banging on the keys of a
typewriter). However, the words of a language are typically composed
of one or more syllables, and explicitly modelling the internal
structure of words typically improves word segmentation considerably.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         suggested replacing (
         3
         ) with the
following model of word structure:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx5">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖶𝗈𝗋𝖽¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾1:4
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (4)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖮𝗇𝗌𝖾𝗍)⁢𝖱𝗁𝗒𝗆𝖾
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (5)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖮𝗇𝗌𝖾𝗍¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (6)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖱𝗁𝗒𝗆𝖾
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖭𝗎𝖼𝗅𝖾𝗎𝗌⁢(𝖢𝗈𝖽𝖺)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (7)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖭𝗎𝖼𝗅𝖾𝗎𝗌¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖵𝗈𝗐𝖾𝗅+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (8)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝖽𝖺¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (9)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Here and below superscripts indicate iteration (e.g., a
         𝖶𝗈𝗋𝖽
         consists of 1 to 4
         𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾
         s), while an
         𝖮𝗇𝗌𝖾𝗍
         consists of
an unbounded number of
         𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍
         s), while parentheses indicate
optionality (e.g., a
         𝖱𝗁𝗒𝗆𝖾
         consists of an obligatory
         𝖭𝗎𝖼𝗅𝖾𝗎𝗌
         followed by an optional
         𝖢𝗈𝖽𝖺
         ). We assume that there are rules
expanding
         𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍
         and
         𝖵𝗈𝗐𝖾𝗅
         to the set of all consonants
and vowels respectively (this amounts to assuming that the learner
can distinguish consonants from vowels). Because
         𝖮𝗇𝗌𝖾𝗍
         ,
         𝖭𝗎𝖼𝗅𝖾𝗎𝗌
         and
         𝖢𝗈𝖽𝖺
         are adapted, this model learns the
possible syllable onsets, nucleii and coda of the language, even
though neither syllable structure nor word boundaries are explicitly
indicated in the input to the model.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The model just described assumes that word-internal syllables have the
same structure as word-peripheral syllables, but in languages such as
English word-peripheral onsets and codas can be more complex than the
corresponding word-internal onsets and codas. For example, the word
“string” begins with the onset cluster str, which is relatively rare
word-internally.
         showed that word
segmentation accuracy improves if the model can learn different
consonant sequences for word-inital onsets and word-final codas. It
is easy to express this as an Adaptor Grammar: (
         4
         ) is
replaced with (
         10
         –
         11
         ) and
(
         12
         –
         17
         ) are added to the grammar.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx6">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖶𝗈𝗋𝖽¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (10)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖶𝗈𝗋𝖽¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨⁢𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾0:2⁢𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (11)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖮𝗇𝗌𝖾𝗍𝖨)⁢𝖱𝗁𝗒𝗆𝖾𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (12)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖮𝗇𝗌𝖾𝗍𝖨)⁢𝖱𝗁𝗒𝗆𝖾
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (13)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E14">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖥
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖮𝗇𝗌𝖾𝗍)⁢𝖱𝗁𝗒𝗆𝖾𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (14)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E15">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖮𝗇𝗌𝖾𝗍𝖨¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (15)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E16">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖱𝗁𝗒𝗆𝖾𝖥
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖭𝗎𝖼𝗅𝖾𝗎𝗌⁢(𝖢𝗈𝖽𝖺𝖥)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (16)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E17">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝖽𝖺𝖥¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗇𝗌𝗈𝗇𝖺𝗇𝗍+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (17)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         In this grammar the suffix “
         𝖨
         ” indicates a word-initial
element, and “
         𝖥
         ” indicates a word-final element. Note that
the model simply has the ability to learn that different clusters can
occur word-peripherally and word-internally; it is not given any
information about the relative complexity of these clusters.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Collocation models of inter-word dependencies
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         point out the detrimental effect that inter-word
dependencies can have on word segmentation models that assume that the
words of an utterance are independently generated. Informally, a
model that generates words independently is likely to incorrectly
segment multi-word expressions such as “the doggie” as single words
because the model has no way to capture word-to-word dependencies,
e.g., that “doggie” is typically preceded by “the”. Goldwater et
al show that word segmentation accuracy improves when the model is
extended to capture bigram dependencies.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         Adaptor grammar models cannot express bigram dependencies, but they
can capture similiar inter-word dependencies using phrase-like units
that
         calls collocations.
         showed
that word segmentation accuracy improves further if the model learns a
nested hierarchy of collocations. This can be achieved by replacing
(
         2
         ) with (
         18
         –
         21
         ).
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx7">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E18">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖲𝖾𝗇𝗍𝖾𝗇𝖼𝖾
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗅𝗅𝗈𝖼𝟥+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (18)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E19">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟥¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗅𝗅𝗈𝖼𝟤+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (19)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E20">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟤¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖢𝗈𝗅𝗅𝗈𝖼𝟣+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (20)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E21">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟣¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖶𝗈𝗋𝖽+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (21)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Informally,
         𝖢𝗈𝗅𝗅𝗈𝖼𝟣
         ,
         𝖢𝗈𝗅𝗅𝗈𝖼𝟤
         and
         𝖢𝗈𝗅𝗅𝗈𝖼𝟥
         define a
nested hierarchy of phrase-like units. While not designed to
correspond to syntactic phrases, by examining the sample parses induced
by the Adaptor Grammar we noticed that the collocations often
correspond to noun phrases, prepositional phrases or verb phrases.
This motivates the extension to the Adaptor Grammar discussed below.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Incorporating “function words” into collocation models
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         The starting point and baseline for our extension is the adaptor
grammar with syllable structure phonotactic constraints and three
levels of collocational structure (
         5
         -
         21
         ), as
prior work has found that this yields the highest word segmentation
token f-score
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Our extension assumes that the
         𝖢𝗈𝗅𝗅𝗈𝖼𝟣-𝖢𝗈𝗅𝗅𝗈𝖼𝟥
         constituents
are in fact phrase-like, so we extend the rules
(
         19
         –
         21
         ) to permit an optional sequence of
monosyllabic words at the left edge of each of these constituents.
Our model thus captures two of the properties of function words
discussed in section
         1.1
         : they are monosyllabic (and
thus phonologically simple), and they appear on the periphery of
phrases. (We put “function words” in scare quotes below because
our model only approximately captures the linguistic
properties of function words).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         Specifically, we replace rules (
         19
         –
         21
         )
with the following sequence of rules:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx8">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E22">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟥¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟥)⁢𝖢𝗈𝗅𝗅𝗈𝖼𝟤+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (22)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E23">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟤¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟤)⁢𝖢𝗈𝗅𝗅𝗈𝖼𝟣+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (23)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E24">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖢𝗈𝗅𝗅𝗈𝖼𝟣¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡(𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟣)⁢𝖶𝗈𝗋𝖽+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (24)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E25">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟥¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟥+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (25)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E26">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟥¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (26)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E27">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟤¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟤+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (27)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E28">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟤¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (28)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E29">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝗌𝟣¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟣+
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (29)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E30">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟣¯
          </td>
          <td class="ltx_td ltx_align_left">
           →⁡𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (30)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         This model memoises (i.e., learns) both the individual “function
words” and the sequences of “function words” that modify the
         𝖢𝗈𝗅𝗅𝗈𝖼𝟣-𝖢𝗈𝗅𝗅𝗈𝖼𝟥
         constituents. Note also that “function
words” expand directly to
         𝖲𝗒𝗅𝗅𝖺𝖻𝗅𝖾𝖨𝖥
         , which in turn expands to
a monosyllable with a word-initial onset and word-final coda. This
means that “function words” are memoised independently of the
“content words” that
         𝖶𝗈𝗋𝖽
         expands to; i.e., the model learns
distinct “function word” and “content word” vocabularies.
Figure
         1
         depicts a sample parse generated by
this grammar.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         This grammar builds in the fact that function words appear on the
left periphery of phrases. This is true of languages such as
English, but is not true cross-linguistically. For comparison
purposes we also include results for a mirror-image model that
permits “function words” on the right periphery, a model which
permits “function words” on both the left and right periphery
(achieved by changing rules
         22
         –
         24
         ),
as well as a model that analyses all words as monosyllabic.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p5">
        <p class="ltx_p">
         Section
         4
         explains how a learner could use Bayesian
model selection to determine that function words appear on the left
periphery in English by comparing the posterior probability of the
data under our “function word” Adaptor Grammar to that obtained
using a grammar which is identical except that rules
(
         22
         –
         24
         ) are replaced with the
mirror-image rules in which “function words” are attached to the
right periphery.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Word segmentation results
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        This section presents results of running our Adaptor Grammar models on
subsets of the
        corpus of child-directed
English. We use the Adaptor Grammar software available from
http://web.science.mq.edu.au/~mjohnson/ with the same settings as
described in
        , i.e., we perform Bayesian inference
with “vague” priors for all hyperparameters (so there are no
adjustable parameters in our models), and perform 8 different MCMC
runs of each condition with table-label resampling for 2,000 sweeps of the training data.
At every 10th sweep of the last 1,000 sweeps we use the model to segment
the entire corpus (even if it is only trained on a subset of it),
so we collect 800 sample segmentations of each utterance. The
most frequent segmentation in these 800 sample segmentations is the
one we score in the evaluations below.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Word segmentation with “function word” models
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Here we evaluate the word segmentations found by the “function word”
Adaptor Grammar model described in section
         2.3
         and
compare it to the baseline grammar with collocations and phonotactics
from
         .

Figure
         2
         presents the standard token and
lexicon (i.e., type) f-score evaluations for word segmentations proposed
by these models
         []
         , and
Table
         1
         summarises
the token and lexicon f-scores for the major models discussed in this
paper. It is interesting to note that adding “function words”
improves token f-score by more than 4%, corresponding to a 40%
reduction in overall error rate.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         When the training data is very small the Monosyllabic grammar produces
the highest accuracy results, presumably because a large proportion of
the words in child-directed speech are monosyllabic. However, at
around 25 sentences the more complex models that are capable of
finding multisyllabic words start to become more accurate.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         It’s interesting that after about 1,000 sentences the model that
allows “function words” only on the right periphery is considerably
less accurate than the baseline model. Presumably this is because it
tends to misanalyse multi-syllabic words on the right periphery as
sequences of monosyllabic words.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         The model that allows “function words” only on the left periphery is
more accurate than the model that allows them on both the left and
right periphery when the input data ranges from about 100 to
about 1,000 sentences, but when the training data is larger than
about 1,000 sentences both models are equally accurate.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Content and function words found by “function word” model
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         As noted earlier, the “function word” model generates function words
via adapted nonterminals other than the
         𝖶𝗈𝗋𝖽
         category.

In order
to better understand just how the model works, we
give the 5 most frequent words in each word category found during
8 MCMC runs of the left-peripheral “function word” grammar above:
        </p>
        <dl class="ltx_description" id="I2">
         <dt class="ltx_item" id="I2.ix1">
          <span class="ltx_tag ltx_tag_description">
           𝖶𝗈𝗋𝖽:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix1.p1">
           <p class="ltx_p">
            book, doggy, house, want, I
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix2">
          <span class="ltx_tag ltx_tag_description">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟣:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix2.p1">
           <p class="ltx_p">
            a, the, your, little
            ,
            in
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix3">
          <span class="ltx_tag ltx_tag_description">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟤:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix3.p1">
           <p class="ltx_p">
            to, in, you, what, put
           </p>
          </div>
         </dd>
         <dt class="ltx_item" id="I2.ix4">
          <span class="ltx_tag ltx_tag_description">
           𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟥:
          </span>
         </dt>
         <dd class="ltx_item">
          <div class="ltx_para" id="I2.ix4.p1">
           <p class="ltx_p">
            you, a, what, no, can
           </p>
          </div>
         </dd>
        </dl>
        <p class="ltx_p">
         Interestingly, these categories seem fairly reasonable. The
         𝖶𝗈𝗋𝖽
         category includes open-class nouns and verbs, the
         𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟣
         category includes noun modifiers such as determiners,
while the
         𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟤
         and
         𝖥𝗎𝗇𝖼𝖶𝗈𝗋𝖽𝟥
         categories include
prepositions, pronouns and auxiliary verbs.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Thus, the present model, initially aimed at segmenting words from
continuous speech, shows three interesting characteristics that are
also exhibited by human infants: it distinguishes between function
words and content words
         []
         , it allows learners to
acquire at least some of the function words of their language (e.g.
         []
         );
and furthermore, it may also allow them to start grouping together
function words according to their category
         []
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Are “function words” on the left or right periphery?
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We have shown that a model that expects function words on the left
periphery performs more accurate word segmentation on English, where
function words do indeed typically occur on the left periphery, leaving
open the question: how could a learner determine whether
function words generally appear on the left or the right periphery of
phrases in the language they are learning?
This question is important because
knowing the side where function words preferentially occur is related
to the question of the direction of syntactic headedness in the
language, and an accurate method for identifying the location of
function words might be useful for initialising a syntactic learner.
Experimental evidence suggests that infants as young
as 8 months of age already expect function words on the correct side
for their language — left-periphery for Italian infants and
right-periphery for Japanese infants
        []
        — so it
is interesting to see whether purely distributional learners such as
the ones studied here can identify the correct location of function
words in phrases.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We experimented with a variety of approaches that use a single adaptor
grammar inference process, but none of these were successful. For
example, we hoped that given an Adaptor Grammar that permits
“function words” on both the left and right periphery, the inference
procedure would decide that the right-periphery rules simply are not
used in a language like English. Unfortunately we did not find this
in our experiments; the right-periphery rules were used almost as often
as the left-periphery rules (recall that a large fraction of the words
in English child-directed speech are monosyllabic).
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        In this section, we show that learners could
use Bayesian model selection to determine that function words appear
on the left periphery in English by comparing the marginal probability
of the data for the left-periphery and the right-periphery models.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Instead, we used Bayesian model
selection techniques to determine whether left-peripheral or a
right-peripheral model better fits the unsegmented utterances that
constitute the training data.
        While Bayesian model selection is in
principle straight-forward, it turns out to require the ratio of two
integrals (for the “evidence” or marginal likelihood) that are often
intractable to compute.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        Specifically, given a training corpus
        D
        of unsegmented sentences and
model families
        G1
        and
        G2
        (here the “function word” adaptor
grammars with left-peripheral and right-peripheral attachment
respectively), the Bayes factor
        K
        is the ratio of the marginal
likelihoods of the data:
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx9">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          K
         </td>
         <td class="ltx_td ltx_align_center">
          =
         </td>
         <td class="ltx_td ltx_align_left">
          P(D∣G1)P(D∣G2)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where the marginal likelihood or “evidence” for a model
        G
        is
obtained by integrating over all of the hidden or latent structure
and parameters
        𝜽
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx10">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E31">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(D∣G)
         </td>
         <td class="ltx_td ltx_align_center">
          =
         </td>
         <td class="ltx_td ltx_align_left">
          ∫ΔP(D,𝜽∣G)d𝜽
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (31)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        Here the variable
        𝜽
        ranges over the space
        Δ
        of all
possible parses for the utterances in
        D
        and all possible
configurations of the Pitman-Yor processes and their parameters that
constitute the “state” of the Adaptor Grammar
        G
        . While the
probability of any specific Adaptor Grammar configuration
        𝜽
        is not too hard to calculate (the MCMC sampler for Adaptor Grammars
can print this after each sweep through
        D
        ), the integral in
(
        31
        ) is in general intractable.
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        Textbooks such as
        describe a number of methods for
calculating
        P(D∣G)
        , but most of them assume that the parameter
space
        Δ
        is continuous and so cannot be directly applied here.
The Harmonic Mean estimator (
        4
        ) for (
        31
        ), which
we used here, is a popular estimator for (
        31
        ) because it
only requires the ability to calculate
        P(D,𝜽∣G)
        for
samples from
        P(𝜽∣D,G)
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx11">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex5">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P(D∣G)
         </td>
         <td class="ltx_td ltx_align_center">
          ≈
         </td>
         <td class="ltx_td ltx_align_left">
          (1n⁢∑i=1n1P(D,𝜽i∣G))-1
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        𝜽i,…,𝜽n
        are
        n
        samples from
        P(𝜽∣D,G)
        , which can be generated by the MCMC
procedure.
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        Figure
        3
        depicts how the Bayes factor in favour of
left-peripheral attachment of “function words” varies as a function
of the number of utterances in the training data
        D
        (calculated from
the last 1000 sweeps of 8 MCMC runs of the corresponding adaptor
grammars). As that figure shows, once the training data contains more
than about 1,000 sentences the evidence for the left-peripheral
grammar becomes very strong. On the full training data the estimated
log Bayes factor is over 6,000, which would constitute overwhelming
evidence in favour of left-peripheral attachment.
       </p>
      </div>
      <div class="ltx_para" id="S4.p8">
       <p class="ltx_p">
        Unfortunately, as Murphy and others warn, the Harmonic Mean estimator
is extremely unstable (Radford Neal calls it “the worst MCMC method
ever” in his blog), so we think it is important to confirm these results
using a more stable estimator. However, given the magnitude of the differences
and the fact that the two models being compared are of similar complexity,
we believe that these results suggest
that Bayesian model selection can be used to determine properties
of the language being learned.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
