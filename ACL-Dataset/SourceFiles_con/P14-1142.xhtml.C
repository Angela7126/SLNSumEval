<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   A Joint Graph Model for Pinyin-to-Chinese Conversion with Typo Correction.
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
       It is very import
for Chinese language processing
with the aid of an efficient
input method engine (IME),
of which pinyin-to-Chinese (PTC) conversion
is the core part.
Meanwhile, though typos are inevitable during user pinyin inputting,
existing IMEs paid little attention to such big inconvenience.
In this paper, motivated by a key equivalence of two decoding algorithms,
we propose a joint graph model to globally optimize PTC and typo correction for IME.
The evaluation results show that the proposed method outperforms both existing academic and commercial IMEs.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Introduction
      </h2>
      <div class="ltx_subsection" id="S1.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.1
        </span>
        Chinese Input Method
       </h3>
       <div class="ltx_para" id="S1.SS1.p1">
        <p class="ltx_p">
         The daily life of Chinese people
heavily depends on Chinese input method engine (IME),
no matter whether one is composing an E-mail,
writing an article,
or sending a text message.
However, every Chinese word
inputted into computer
or cellphone cannot be typed through
one-to-one mapping of key-to-letter inputting directly,
but has to go through an IME
as there are thousands of Chinese characters for inputting
while only 26 letter keys are available in the keyboard.
An IME is an essential software interface that maps
Chinese characters into English letter combinations.
An efficient IME will largely improve
the user experience of
Chinese information processing.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p2">
        <p class="ltx_p">
         Nowadays most of Chinese IMEs are pinyin based.
Pinyin is originally designed as the
phonetic symbol of a Chinese character
(based on the standard modern Chinese, mandarin)
, using Latin letters as its syllable notation.
For example, the pinyin of the Chinese character “
         爱”(love)
is “ài”.
Most characters usually have unique pinyin representations,
while a few Chinese characters may be pronounced in several different ways,
so they may have multiple pinyin representations.
The advantage of pinyin IME is
that it only adopts the pronunciation perspective of Chinese characters
so that it is simple and easy to learn.
But there are only less than 500 pinyin syllables in standard modern Chinese,
compared with over 6,000 commonly used Chinese characters,
which leads to serious ambiguities for pinyin-to-character mapping.
Modern pinyin IMEs mostly use a “
         sentence-based
         ”
decoding technique
         [4]
         to alleviate the ambiguities.
“
         Sentence based
         ” means that IME generates a
sequence of Chinese characters upon a sequence of pinyin inputs
with respect to certain statistical criteria.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S1.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.2
        </span>
        Typos and Chinese Spell Checking
       </h3>
       <div class="ltx_para" id="S1.SS2.p1">
        <p class="ltx_p">
         Written in Chinese characters but not alphabets, spell checking for Chinese language is quite different from the same task for other languages.
Since Chinese characters are entered via IME,
those user-made typos
do not immediately lead to spelling errors.
When a user types a wrong letter,
IME will be very likely to fail to generate the expected
Chinese character sequence.
Normally, the user may immediately notice the inputting error
and then make corrections,
which usually means doing a bunch of
extra operations like
cursor movement, deletion and re-typing.
Thus there are two separated sub-tasks for
Chinese spell checking:
1.
         typo checking
         for user typed pinyin sequences
which should be
a built-in module in IME,
and 2.
         spell checking
         for Chinese texts
in its narrow sense,
which is typically a module
of word processing applications
         [36]
         .
These two terms are often confused
especially in IME related works such as
         [4]
         and
         [34]
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p2">
        <p class="ltx_p">
         Pinyin typos have always been a serious problem for Chinese pinyin IMEs.
The user may fail to input the completely right pinyin simply because
he/she is a dialect speaker and does not know the exact pronunciation for the expected character.
This may be a very common situation
since there are about seven quite different dialects in Chinese,
among which being spoken languages,
six are far different from the standard modern Chinese, mandarin.
With the boom of smart-phones,
pinyin typos worsen
due to the limited size of soft keyboard,
and the lack of physical feedback on the touch screen.
However, existing practical IMEs only provide
small patches to deal with typos
such as
         Fuzzy Pinyin
         [33]
         and other language specific errors
         [45]
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS2.p3">
        <p class="ltx_p">
         Typo checking and correction has an important impact on
IME performance.
When IME fails to correct a typo and generate the expected sentence,
the user will have to take much extra effort to move the cursor back to the mistyped letter
and correct it,
which leads to very poor user experience
         [15]
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
       Related Works
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The very first approach for Chinese input
with typo correction was made by
        [4]
        ,
which was also the initial attempt of “sentence-based” IME.
The idea of “statistical input method” was proposed
by modeling PTC conversion as a hidden Markov model (HMM),
and using Viterbi
        [26]
        algorithm to decode the sequence.
They solved the typo correction problem by decomposing
the conditional probability
        P(H|P)
        of Chinese character sequence
        H
        given pinyin sequence
        P
        into
a language model
        P(wi|wi-1)
        and a typing model
        P(pi|wi)
        .
The typing model that was estimated on real user input data was
for typo correction.
However, real user input data can be very noisy
and not very convenient to obtain.
As we will propose a joint model in this paper,
such an individual typing model is not necessarily built in our approach.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        [44]
        developed an IME system
with typo correction called CHIME
using noisy channel error model and language-specific features.
However their model depended on a very strong assumption
that input pinyin sequence should have been segmented into pinyin words by the user.
This assumption does not really hold in modern “sentence-based” IMEs.
We release this assumption
since our model solves segmentation, typo correction and PTC conversion jointly.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Besides the common HMM approach for PTC conversion,
there are also various methods such as:
support vector machine
        [16]
        ,
maximum entropy (ME) model
        [30]
        ,
conditional random field (CRF)
        [19]
        and statistical machine translation (SMT)
        [35, 29, 38]
        , etc.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Spell checking or typo checking
was first proposed for English
        [24]
        .
        [23]
        addressed that
spell checking should be done
within a context, i.e., a sentence or a long phrase
with a certain meaning, instead of only in one word.
A recent spell correction work is
        [20]
        ,
where a distributional
similarity was introduced
for spell correction of web queries.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Early attempts for Chinese spelling checking could date back to
        [2]
        where character tables for similar shape,
pronunciation, meaning, and input-method-code characters
were proposed.
More recently, the 7th SIGHAN Workshop on Chinese Language Processing
        [37]
        held a shared task on Chinese spell checking.
Various approaches were made for the task including
language model (LM) based methods
        [3]
        ,
ME model
        [10]
        ,
CRF
        [31, 27]
        ,
SMT
        [5, 21]
        ,
and graph model
        [14]
        , etc.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Pinyin Input Method Model
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        From English Letter to Chinese Sentence
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         It is a rather long journey
from
the first English letter typed
on the keyboard
to finally a completed Chinese sentence generated by IME.
We will first take an overview of the entire process.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         The average length of pinyin syllables is about 3 letters.
There are about 410 pinyin syllables used in the current pinyin system.
Each pinyin syllable has a bunch of corresponding
Chinese characters which share the same
pronunciation represented by the syllable.
The number of those homophones ranges from 1 to over 300.
Chinese characters then form words.
But word in Chinese is a rather vague concept.
Without word delimiters,
linguists have argued on
what a Chinese word really is
for a long time
and that is why there is always
a primary word segmentation treatment
in most Chinese language processing tasks
         [40, 13, 41, 39, 42, 43]
         .
A Chinese word may contain from 1 to over 10 characters
due to different word segmentation conventions.
Figure
         1
         demonstrates the relationship of pinyin and word,
from pinyin letters “
         nihao
         ” to the word “
         <span class="ltx_text ltx_font_italic">
          你好 (hello)
         </span>
         ”.
Typically, an IME takes the pinyin input,
segments it into syllables,
looks up corresponding words in a dictionary
and generates a sentence with the candidate words.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Pinyin Segmentation and Typo Correction
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Non-Chinese users may feel confused or even surprised if they know that
when typing pinyin through an IME,
Chinese IME users will never enter delimiters
such as “Space” key
to segment either pinyin syllables or pinyin words,
but just input the entire un-segmented
pinyin sequence.
For example, if one wants to
input “
         <span class="ltx_text ltx_font_italic">
          你好世界 (Hello world)
         </span>
         ”,
he will just type “
         nihaoshijie
         ”
instead of segmented pinyin sequence “
         ni hao shi jie
         ”.
Nevertheless, pinyin syllable segmentation is a much easier
problem compared to Chinese word segmentation.
Since pinyin syllables have a very limited vocabulary
and follow a set of regularities strictly,
it is convenient to
perform pinyin syllable segmentation by using rules.
But as the pinyin input is not segmented,
it is nearly impossible to adopt
previous spell checking methods for English
to pinyin typo checking,
although techniques for English spell checking have been well developed.
A bit confusing but interesting,
pinyin typo correction and segmentation
come as two sides of one problem:
when a pinyin sequence is mistyped,
it is unlikely to be correctly segmented;
when it is segmented in an awkward way,
it is likely to be mistyped.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         Inspired by
         [36]
         and
         [14]
         ,
we adopt the graph model for Chinese spell checking
for pinyin segmentation and typo correction,
which is based on the shortest path word segmentation algorithm
         [1]
         .
The model has two major steps: segmentation
and correction.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.1
         </span>
         Pinyin Segmentation
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS1.p1">
         <p class="ltx_p">
          The shortest path segmentation algorithm is based on the idea that
a reasonable segmentation should
minimize the number of segmented units.
For a pinyin sequence
          p1⁢p2⁢…⁢pL
          ,
where
          pi
          is a letter,
first a directed acyclic graph (DAG)
          GS=(𝕍,𝔼)
          is built for pinyin segmentation step.
The vertex set
          𝕍
          consists of the following parts:
         </p>
         <ul class="ltx_itemize" id="I1">
          <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i1.p1">
            <p class="ltx_p">
             Virtual start vertex
             S0
             and end vertex
             SE
             ;
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i2.p1">
            <p class="ltx_p">
             Possible legal syllables fetched from dictionary
             𝔻p
             according to the input pinyin sequence:
            </p>
            {Si,j|Si,j=pi⁢…⁢pj∈𝔻p};
           </div>
          </li>
          <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I1.i3.p1">
            <p class="ltx_p">
             The letter itself as a fallback
no matter if it is a legal pinyin syllable or not:
            </p>
            {Si|Si=pi}.
           </div>
          </li>
         </ul>
         <p class="ltx_p">
          The vertex weights
          wS
          are all set to 0.
The edges are from a syllable to all syllables next to it:
         </p>
         𝔼={E(Si,j→Sj+1,k)|Si,j,Sj+1,k∈𝕍}.
         <p class="ltx_p">
          The edge weight the negative logarithm of conditional probability
          P(Sj+1,k|Si,j)
          that a syllable
          Si,j
          is followed by
          Sj+1,k
          ,
which is give by a bi-gram language model of pinyin syllables:
         </p>
         WE(Si,j→Sj+1,k)=-logP(Sj+1,k|Si,j)
         <p class="ltx_p">
          The shortest path
          P*
          on the graph is the path
          P
          with the least sum of weights:
         </p>
         P*=arg⁢min(v,E)∈G∧(v,E)∈P⁢∑vwv+∑EWE.
         <p class="ltx_p">
          Computing the shortest path from
          S0
          to
          SE
          on
          GS
          yields
the best segmentation.
This is the single source shortest path (SSSP) problem on DAG
which has an efficient algorithm
by preprocessing the DAG with topology sort,
then traversing vertices and edges in topological order.
It has the time complexity of
          O⁢(|𝕍|+|𝔼|)
          .
For example, one intends to input “
          <span class="ltx_text ltx_font_italic">
           你好世界 (Hello world)
          </span>
          ”
by typing “
          nihaoshijie
          ”,
but mistyped as “
          mihaoshiji w
          ”.
The graph for this input is shown in Figure
          2
          .
The shortest path, i.e., the best segmentation is “
          mi hao shi ji w
          ”.
We will continue to use this example in the rest of this paper.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.2
         </span>
         Pinyin Typo Correction
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS2.p1">
         <p class="ltx_p">
          Next in the correction step,
for the segmented pinyin sequence
          S1,S2,…,SM
          ,
a graph
          Gc
          is constructed to perform typo correction.
The vertex set
          𝕍
          consists of the following parts:
         </p>
         <ul class="ltx_itemize" id="I2">
          <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i1.p1">
            <p class="ltx_p">
             Virtual start vertex
             S0′
             and end vertex
             SE′
             with vertex weights of 0;
            </p>
           </div>
          </li>
          <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_itemize">
            •
           </span>
           <div class="ltx_para" id="I2.i2.p1">
            <p class="ltx_p">
             All possible syllables similar to original syllable in
             Gs
             .
If the adjacent syllables can be merged into a legal syllable,
the merged syllable is also added into
             𝕍
             :
            </p>
            <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx1">
             <tr class="ltx_equation ltx_align_baseline" id="S3.Ex6">
              <td class="ltx_eqn_center_padleft">
              </td>
              <td class="ltx_td ltx_align_right">
               {Si,j′|
              </td>
              <td class="ltx_td ltx_align_left">
               Si,j′=Si′⁢…⁢Sj′∈𝔻p,
              </td>
              <td class="ltx_eqn_center_padright">
              </td>
             </tr>
             <tr class="ltx_equation ltx_align_baseline" id="S3.Ex7">
              <td class="ltx_eqn_center_padleft">
              </td>
              <td class="ltx_td ltx_align_right">
              </td>
              <td class="ltx_td ltx_align_left">
               Sk′∼Sk,k=i≤j},
              </td>
              <td class="ltx_eqn_center_padright">
              </td>
             </tr>
            </table>
            <p class="ltx_p">
             where the similarity
             ∼
             is measured in Levenshtein distance
             [18]
             .
Syllables with Levenshtein distance under a certain threshold are considered as similar:
            </p>
            ℒ⁢(Si,Sj)&lt;T↔Si∼Sj.
            <p class="ltx_p">
             The vertex weight is the Levenshtein distance multiply by a normalization parameter:
            </p>
            wSi,j′=β⁢∑k-ijℒ⁢(Sk′,Sk).
           </div>
          </li>
         </ul>
         <p class="ltx_p">
          Similar to
          Gs
          ,
the edges are from one syllable to all syllables next to it
and edge weights are the conditional probabilities between them.
Computing the shortest path from
          S0′
          to
          SE′
          on
          Gc
          yields
the best typo correction result.
In addition, the result has been segmented so far.
Considering our running example, the graph
          Gc
          is shown in Figure
          3
          ,
and the typo correction result is “
          mi hao shi jie
          ”.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS2.p2">
         <p class="ltx_p">
          Merely using the above model, the typo correction result is not satisfying yet,
no matter how much effort is paid.
The major reason is that
the basic semantic unit of Chinese language is actually word (tough vaguely defined)
which is usually composed of several characters.
Thus the conditional probability between characters does not make much sense.
In addition, a pinyin syllable usually maps to dozens or even hundreds of corresponding homophonic characters,
which makes the conditional probability between syllables much more noisy.
However, using pinyin words instead of syllables is not a wise choice
because pinyin word segmentation is not so easy a task as syllable segmentation.
To make typo correction better,
we consider to integrate it with PTC conversion
using a joint model.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Hidden Markov Model for Pinyin-to-Chinese Conversion
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         PTC conversion has long been viewed as a decoding problem using HMM.
We continue to follow this formalization.
The best Chinese character sequence
         W*
         for a given pinyin syllable sequence
         S
         is the one with the highest conditional probability
         P(W|S)
         that
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           W*
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢maxWP(W|S)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢maxW⁡P(W)P(S|W)P⁢(S)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢maxWP(W)P(S|W)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢maxw1,ww,…,wM∏wiP(wi|wi-1)∏wiP(si|wi)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         In the HMM for pinyin IME,
observation states are pinyin syllables,
hidden states are Chinese words,
emission probability is
         P(si|wi)
         ,
and transition probability is
         P(wi|wi-1)
         .
Note the transition probability is
the conditional probability between words
instead of characters.
PTC conversion is to decode the Chinese word sequence
from the pinyin sequence.
The Viterbi algorithm
         [26]
         is
used for the decoding.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         The shortest path algorithm for typo correction
and Viterbi algorithm for PTC conversion
are very closely related.
It has been strictly proven by
         [8]
         that
the sequence decoding problem on HMM
is formally identical to finding a shortest path
on a certain graph,
which can be constructed in the following manner.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         Consider a first order HMM with
all possible observations
         𝕆={o1,o2,…,oM}
         ,
hidden states
         𝕊={s1,s2,…,sN}
         ,
a special start state
         s0
         ,
emission probabilities
         (ℰsi,ok)=P(ok|si)
         ,
transition probabilities
         (𝒯si,sj)=P(sj|si)
         ,
and start probabilities
         (𝒮si)=P(si|s0)
         .
For an observation sequence of
         T
         time periods
         Y={y1,y2,…,yT|yt∈𝕆,t=1,…,T}
         ,
the decoding problem is to find the best corresponding hidden state sequence
         X*
         with the highest probability, i.e.,
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           X*=arg⁢maxx1,xt∈𝕊⁡𝒮x1⁢ℰx1,y1⁢∏t=2Tℰxt,yt⁢𝒯xt-1,xt.
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
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         Then we will construct a DAG
         G=(𝕍,𝔼)
         upon the HMM.
The vertex set
         𝕍
         includes:
        </p>
        <ul class="ltx_itemize" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Virtual start vertex
            v0
            and end vertex
            vE
            with vertex weight of 0;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Normal vertices
            vxt
            , where
            t=1,…,T
            , and
            ∀xt∈𝕊
            .
The vertex weight is the negative logarithm of emission probability:
           </p>
           wvxt=-log⁡ℰxt,yt.
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The edge set
         𝔼
         includes:
        </p>
        <ul class="ltx_itemize" id="I4">
         <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i1.p1">
           <p class="ltx_p">
            Edges from the start vertex
            E(v0→vx1)
            with edge weight
           </p>
           WE(v0→vx1)=-log⁡𝒮x1,
           <p class="ltx_p">
            where
            ∀x1∈𝕊
            ;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i2.p1">
           <p class="ltx_p">
            Edges to the end vertex
            E(vxT→vE)
            with vertex weights of 0;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i3.p1">
           <p class="ltx_p">
            Edges between adjacent time periods
            E(vxt-1→vxt)
            with edge weight
           </p>
           WE(vxt-1→vxt)=-log⁡𝒯xt-1,xt,
           <p class="ltx_p">
            where
            t=2,…,T
            , and
            ∀xt,xt-1∈𝕊
            .
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The shortest path
         P*
         from
         v0
         to
         vE
         is the one
with the least sum of vertex and edge weights, i.e.,
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx4">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex17">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           P*=
          </td>
          <td class="ltx_td ltx_align_left">
           arg⁢minvxt∈𝕍⁢∑t=1T(wvxt+WE(vxt-1→vxt))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex18">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           arg⁢minvx1,vxt∈𝕍{-log𝒮x1-logℰx1,y1
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex19">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +∑t=2T(-logℰxt,yt-log𝒯xt-1,xt)}
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           arg⁢maxvx1,vxt∈𝕍⁡𝒮x1⁢ℰx1,y1⁢∏t=2Tℰxt,yt⁢𝒯xt-1,xt.
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (2)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S3.SS3.p5">
        <p class="ltx_p">
         The optimization goal of
         P*
         in Equation (
         3.3
         ) is identical to
that of
         X*
         in Equation (
         1
         ).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Joint Graph Model For Pinyin IME
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Given HMM decoding problem is identical to SSSP problem on DAG,
we propose a joint graph model for PTC conversion with typo correction.
The joint graph model aims to find the global optimal
for both PTC conversion and typo correction
on the entire input pinyin sequence.
The graph
         G=(𝕍,𝔼)
         is constructed
based on graph
         Gc
         for typo correction in Section
         3.2
         .
The vertex set
         𝕍
         consists of the following parts:
        </p>
        <ul class="ltx_itemize" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            Virtual start vertex
            V0
            and end vertex
            VE
            with vertex weight of 0;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            Adjacent pinyin syllables in
            Gc
            are merged into pinyin words.
Corresponding Chinese words are fetched from a PTC dictionary
            𝔻c
            ,
which is a dictionary maps pinyin words to Chinese words,
and added as vertices:
           </p>
           {Vi,j|∀Vi,j∈𝔻c⁢[Si′⁢…⁢Sj′],i≤j};
           <p class="ltx_p">
            The vertex weight consists of two parts:
1. the vertex weights of syllables in
            Gc
            ,
and 2. the emission probability:
           </p>
           <table class="ltx_equationgroup ltx_eqn_align" id="S5.EGx5">
            <tr class="ltx_equation ltx_align_baseline" id="S3.Ex21">
             <td class="ltx_eqn_center_padleft">
             </td>
             <td class="ltx_td ltx_align_right">
              wVi,j=
             </td>
             <td class="ltx_td ltx_align_left">
              β⁢∑k=ijℒ⁢(Sk′,Sk)
             </td>
             <td class="ltx_eqn_center_padright">
             </td>
            </tr>
            <tr class="ltx_equation ltx_align_baseline" id="S3.Ex22">
             <td class="ltx_eqn_center_padleft">
             </td>
             <td class="ltx_td ltx_align_right">
             </td>
             <td class="ltx_td ltx_align_left">
              -γlogP(Si′…Sj′|Vi,j);
             </td>
             <td class="ltx_eqn_center_padright">
             </td>
            </tr>
           </table>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         If the corresponding pinyin syllables in
         Gc
         have an edge between them,
the vertices in
         G
         also have an edge:
        </p>
        𝔼={E(Vi,j→Vj+1,k)|E(Si,j→Sj+1,k)∈𝔾c}.
        <p class="ltx_p">
         The edge weights are the negative logarithm of the transition probabilities:
        </p>
        WE(Vi,j→Vj+1,k)=-logP(Vj+1,k|Vi,j)
        <p class="ltx_p">
         Although the model is formulated on first order HMM,
i.e., the LM used for transition probability
is a bigram one,
it is easy to extend the model to take advantage of higher order
         n
         -gram LM,
by tracking longer history while traversing the graph.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         Computing the shortest path from
         V0
         to
         VE
         on
         G
         yields
the best pinyin-to-Chinese conversion with typo correction result.
Considering our running example, the graph
         G
         is shown in Figure
         4
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p3">
        <p class="ltx_p">
         The joint graph is rather huge and density.
According to our empirical statistics, when setting threshold
         T=2
         ,
for a sentence of
         M
         characters,
the joint graph will have
         |𝕍|=M×1,000
         ,
and
         |𝔼|=M×1,000,000
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.5
        </span>
        K
        -Shortest Paths
       </h3>
       <div class="ltx_para" id="S3.SS5.p1">
        <p class="ltx_p">
         To reduce the scale of graph
         G
         ,
we filter graph
         Gc
         by searching its
         K
         -shortest paths first
to get
         Gc′
         and construct
         G
         on top of
         Gc′
         .
Figure
         5
         shows the 3-shortest paths
filtered graph
         Gc′
         and Figure
         6
         shows
the corresponding
         G
         for our running example.
The scale of graph may be thus drastically reduced.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS5.p2">
        <p class="ltx_p">
         An efficient heap data structure is required in
         K
         -shortest paths algorithm
         [7]
         for backtracking the best paths to current vertex while traversing.
The heap is implemented as a priority queue of size
         K
         sorted according to path length
that should support efficient push and pop operations.
Fibonacci heap
         [9]
         is
adopted for the heap implementation
since it has a push complexity of
         O⁢(1)
         which
is better than the
         O⁢(K)
         for other heap structures.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS5.p3">
        <p class="ltx_p">
         Another benefit provided by
         K
         -shortest paths
is that it can be used for generating
         N
         -best candidates of PTC conversion,
which may
be helpful for further performance improvement.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiments
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Corpora, Tools and Experiment Settings
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         The corpus for evaluation is the one
provided in
         [35]
         ,
which is originally extracted from the
         People’s Daily
         corpus
and labeled with pinyin.
The corpus has already been split into training
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Train
         </span>
         ,
development
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         and test
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Test
         </span>
         sets
as shown in Table
         1
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         SRILM
         [25]
         is adopted for language model training
and KenLM
         [12, 11]
         for language model query.
The Chinese part of the corpus
is segmented into words before LM training.
Maximum matching word segmentation is used
with a large word vocabulary
         𝒱
         extracted from web data
provided by
         [28]
         .
The pinyin part is segmented according to the Chinese part.
This vocabulary
         𝒱
         also serves as the PTC dictionary.
The original vocabulary is not labeled with pinyin,
thus we use the PTC dictionary of
         sunpinyin
         which is an open source Chinese pinyin IME,
to label the vocabulary
         𝒱
         with pinyin.
The emission probabilities are estimated
using the lexical translation module of MOSES
         [17]
         as “translation probability” from pinyin to Chinese.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Evaluation Metrics
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We will use conventional sequence labeling evaluation metrics
such as sequence accuracy and character accuracy
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Chinese characters in a sentence may be separated
by digits, punctuation and alphabets which are directly inputted without the IME.
We follow the so-called term
         Max Input Unit
         (MIU), the longest consecutive
Chinese character sequence proposed by
         [15]
         .
We will mainly consider MIU accuracy (MIU-Acc)
which is the ratio of the number of completely corrected generated MIUs
over the number of all MIUs,
and character accuracy (Ch-Acc),
but the sentence accuracy (S-Acc) will also be reported in evaluation results.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         We will also report the conversion error rate (ConvER)
proposed by
         [44]
         ,
which is the ratio of
the number of mistyped pinyin word that is not converted to the right Chinese word
over the total number of mistyped pinyin words
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Baseline System without Typo Correction
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         Firstly we build a baseline system
without typo correction
which is a pipeline of pinyin syllable segmentation and PTC conversion.
The baseline system takes a pinyin input sequence,
segments it into syllables,
and then converts it to Chinese character sequence.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         The pinyin syllable segmentation
already has very high
(over 98%) accuracy
with a trigram LM using improved Kneser-Ney smoothing.
According to our empirical observation,
emission probabilities are mostly 1
since most Chinese words have unique pronunciation.
So in this step we set
         γ=0
         .
We consider different LM smoothing methods including
Kneser-Ney (KN), improved Kneser-Ney (IKN),
and Witten-Bell (WB).
All of the three smoothing methods
for bigram and trigram LMs
are examined both using back-off models and interpolated models.
The number of
         N
         -best candidates for PTC conversion is set to 10.
The results on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         are shown in Figure
         7
         in which the “-i” suffix indicates using interpolated model.
According to the results, we then choose the trigram LM using Kneser-Ney smoothing with interpolation.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         The choice of the number of
         N
         -best candidates for PTC conversion also has a strong impact on the results.
Figure
         8
         shows the results on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         with different
         N
         s,
of which the
         N
         axis is drawn in logarithmic scale.
We can observe that MIU-Acc slightly decreases while
         N
         goes up,
but Ch-Acc largely increases.
We therefore choose
         N=10
         as trade-off.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p4">
        <p class="ltx_p">
         The parameter
         γ
         determines emission probability.
Results with different
         γ
         on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         is shown in Figure
         9
         ,
of which the
         γ
         axis is drawn in logarithmic scale.
         γ=0.03
         is chosen at last.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p5">
        <p class="ltx_p">
         We compare our baseline system with several practical pinyin IMEs
including
         sunpinyin
         and
         Google Input Tools
         (Online version)
         .
The results on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         are shown in Table
         2
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        PTC Conversion with Typo Correction
       </h3>
       <div class="ltx_para" id="S4.SS4.p1">
        <p class="ltx_p">
         Based upon the baseline system,
we build the joint system of PTC conversion with typo correction.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p2">
        <p class="ltx_p">
         We simulate user typos by randomly generating errors
automatically on the corpus.
The typo rate is set according to previous Human-Computer Interaction (HCI) studies.
Due to few works have been done
on modeling Chinese text entry,
we have to refer to those corresponding results on
English
         [32, 22, 6]
         ,
which show that the average typo rate is about 2%.
         [44]
         performed an experiment
that 2,000 sentences of 11,968 Chinese words
were entered by 5 native speakers.
The collected data consists of 775 mistyped pinyin words caused by one edit operation,
and 85 caused by two edit operations.
As we observe on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Train
         </span>
         that the average pinyin word length is 5.24,
then typo rate in the experiment of
         [44]
         can be roughly estimated as:
        </p>
        775+85×211968×5.24=1.51⁢%,
        <p class="ltx_p">
         which is similar to the conclusion on English.
Thus we generate corpora
from
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Dev
         </span>
         with typo rate of
0% (
         0-P
         ), 2% (
         2-P
         ), and 5% (
         5-P
         )
to evaluate the system.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p3">
        <p class="ltx_p">
         According to
         [44]
         most mistyped pinyin words are caused by one edit operation.
Since pinyin syllable is much shorter than pinyin word,
this ratio can be higher for pinyin syllables.
From our statistics on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Train
         </span>
         , with 2% randomly generated typos,
         Pr(ℒ(S′,S)&lt;2)=99.86%
         .
Thus we set the threshold
         T
         for
         ℒ
         to 2.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p4">
        <p class="ltx_p">
         We first set
         K
         -shortest paths filter to
         K=10
         and tune
         β
         .
Results with different
         β
         are shown in Figure
         13
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p5">
        <p class="ltx_p">
         With
         β=3.5
         , we select
         K
         .
Results with different
         K
         are shown in Figure
         17
         .
We choose
         K=20
         since there is no significant improvement
when
         K&gt;20
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p6">
        <p class="ltx_p">
         The selection of
         K
         also directly guarantees the running time of the joint model.
With
         K=20
         , on a normal PC with Intel Pentium Dual-Core E6700 CPU,
the PTC conversion rate is over 2000 characters-per-minute (
         cpm
         ),
which is much faster than the normal typing rate of 200
         cpm
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p7">
        <p class="ltx_p">
         With all parameters
optimized, results on
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Test
         </span>
         using the proposed joint model are
shown in Table
         3
         and Table
         4
         .
Our results are compared to
the baseline system without typo correction
and
         Google Input Tool
         .
Since
         sunpinyin
         does not have typo correction module
and performs much poorer than our baseline system,
we do not include it in the comparison.
Though no direct proofs can be found
to indicate if Google Input Tool has
an independent typo correction component,
its outputs show that such a component is unlikely available.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p8">
        <p class="ltx_p">
         Since
         Google Input Tool
         has to be accessed
through a web interface and the network connection cannot be guaranteed.
we only take a subset of 10K sentences of
         <span class="ltx_text ltx_font_bold ltx_font_smallcaps">
          Test
         </span>
         to perform the experiments, and the results are shown in Table
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p9">
        <p class="ltx_p">
         The scores reported in
         [44]
         are not listed in Table
         4
         since the data set is different.
They reported a ConvER of 53.56%, which is given here for reference.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS4.p10">
        <p class="ltx_p">
         Additionally, to further inspect the robustness of our model,
performance with typo rate ranges from 0% to 5%
is shown in Figure
         18
         .
Although the performance decreases while typo rate goes up,
it is still quite satisfying around typo rate of
2% which is assumed to be the real world situation.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
