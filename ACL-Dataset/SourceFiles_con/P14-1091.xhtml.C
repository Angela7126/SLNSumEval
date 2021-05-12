<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Knowledge-Based Question Answering as Machine Translation.
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
       A typical knowledge-based question answering (KB-QA) system faces two challenges:
one is to transform natural language questions into their meaning representations (MRs);
the other is to retrieve answers from knowledge bases (KBs) using generated MRs.
Unlike previous methods which treat them in a cascaded manner, we present a translation-based approach to solve these two tasks in one unified framework.
We translate questions to answers based on CYK parsing.
Answers as translations of the span covered by each CYK cell are obtained by a question translation method, which first generates formal triple queries as MRs for the span based on question patterns and relation expressions, and then retrieves answers from a given KB based on triple queries generated.
A linear model is defined over derivations, and minimum error rate training is used to tune feature weights based on a set of question-answer pairs.
Compared to a KB-QA system using a state-of-the-art semantic parser, our method achieves better results.
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
        Knowledge-based question answering (KB-QA) computes answers to natural language (NL) questions based on existing knowledge bases (KBs).
Most previous systems tackle this task in a cascaded manner:
First, the input question is transformed into its meaning representation (MR) by an independent semantic parser
        [26, 20, 2, 17, 4, 22, 1, 14, 3]
        ;
Then, the answers are retrieved from existing KBs using generated MRs as queries.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Unlike existing KB-QA systems which treat semantic parsing and answer retrieval as two cascaded tasks,
this paper presents a unified framework that can integrate semantic parsing into the question answering procedure directly.
Borrowing ideas from machine translation (MT), we treat the QA task as a translation procedure.
Like MT, CYK parsing is used to parse each input question, and answers of the span covered by each CYK cell are considered the translations of that cell; unlike MT, which uses offline-generated translation tables to translate source phrases into target translations, a semantic parsing-based question translation method is used to translate each span into its answers on-the-fly, based on question patterns and relation expressions.
The final answers can be obtained from the root cell.
Derivations generated during such a translation procedure are modeled by a linear model, and minimum error rate training (MERT)
        [21]
        is used to tune feature weights based on a set of question-answer pairs.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Figure 1 shows an example: the question
        director of movie starred by Tom Hanks
        is translated to one of its answers
        Robert Zemeckis
        by three main steps:
(i) translate
        director of
        to
        director of
        ;
(ii) translate
        movie starred by Tom Hanks
        to one of its answers
        Forrest Gump
        ;
(iii) translate
        director of
        Forrest Gump
        to a final answer
        Robert Zemeckis
        .
Note that the updated question covered by Cell[0, 6] is obtained by combining the answers to question spans covered by Cell[0, 1] and Cell[2, 6].
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The contributions of this work are two-fold:
(1) We propose a translation-based KB-QA method that integrates semantic parsing and QA in one unified framework.
The benefit of our method is that we don’t need to explicitly generate complete semantic structures for input questions.
Besides which, answers generated during the translation procedure help significantly with search space pruning.
(2) We propose a robust method to transform single-relation questions into formal triple queries as their MRs,
which trades off between transformation accuracy and recall using question patterns and relation expressions respectively.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Translation-Based KB-QA
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Overview
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Formally, given a knowledge base
         𝒦⁢ℬ
         and an NL question
         𝒬
         ,
our KB-QA method generates a set of formal triples-answer pairs
         {⟨𝒟,𝒜⟩}
         as derivations,
which are scored and ranked by the distribution
         P(⟨𝒟,𝒜⟩|𝒦ℬ,𝒬)
         defined as follows:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           e⁢x⁢p⁢{∑i=1Mλi⋅hi⁢(⟨𝒟,𝒜⟩,𝒦⁢ℬ,𝒬)}∑⟨𝒟′,𝒜′⟩∈ℋ⁢(𝒬)e⁢x⁢p⁢{∑i=1Mλi⋅hi⁢(⟨𝒟′,𝒜′⟩,𝒦⁢ℬ,𝒬)}
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            𝒦⁢ℬ
            denotes a knowledge base
            that stores a set of assertions.
Each assertion
            t∈𝒦⁢ℬ
            is in the form of
            {es⁢b⁢jI⁢D,p,eo⁢b⁢jI⁢D}
            , where
            p
            denotes a predicate,
            es⁢b⁢jI⁢D
            and
            eo⁢b⁢jI⁢D
            denote the subject and object entities of
            t
            , with unique
            I⁢D
            s
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            ℋ⁢(𝒬)
            denotes the search space
            {⟨𝒟,𝒜⟩}
            .
            𝒟
            is composed of a set of
            ordered
            formal triples
            {t1,…,tn}
            .
Each triple
            t={es⁢b⁢j,p,eo⁢b⁢j}ij∈𝒟
            denotes an assertion in
            𝒦⁢ℬ
            ,
where
            i
            and
            j
            denotes the beginning and end indexes of the question span from which
            t
            is transformed.
The order of triples in
            𝒟
            denotes the order of translation steps from
            𝒬
            to
            𝒜
            .
E.g.,
            ⟨
            director of, Null, director of⟩01
            ,
            ⟨
            Tom Hanks, Film.Actor.Film, Forrest Gump⟩26
            and
            ⟨
            Forrest Gump, Film.Film.Director, Robert Zemeckis⟩06
            are three ordered formal triples corresponding to the three translation steps in Figure 1.
We define the task of transforming question spans into formal triples as
            question translation
            .
            𝒜
            denotes one final answer of
            𝒬
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i3.p1">
           <p class="ltx_p">
            hi⁢(⋅)
            denotes the
            it⁢h
            feature function.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i4.p1">
           <p class="ltx_p">
            λi
            denotes the feature weight of
            hi⁢(⋅)
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         According to the above description, our KB-QA method can be decomposed into four tasks as:
(1) search space generation for
         ℋ⁢(𝒬)
         ;
(2) question translation for transforming question spans into their corresponding formal triples;
(3) feature design for
         hi⁢(⋅)
         ; and
(4) feature weight tuning for
         {λi}
         .
We present details of these four tasks in the following subsections one-by-one.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Search Space Generation
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         We first present our translation-based KB-QA method in Algorithm 1, which is used to generate
         ℋ⁢(𝒬)
         for each input NL question
         𝒬
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         Translation-based KB-QA
         IndexIndex
         l=1 to |𝒬|
all i,j s.t. j-i=l
ℋ⁢(𝒬ij)=∅ 
T=Q⁢T⁢r⁢a⁢n⁢s⁢(𝒬ij,𝒦⁢ℬ)
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         formal triple t∈T

create a new derivation d 
d.𝒜=t.eo⁢b⁢j 
d.𝒟={t} 
update the model score of d 
insert d to ℋ⁢(𝒬ij) 



l=1 to |𝒬|
all i,j s.t. j-i=l
all m s.t. i≤m&lt;j
dl∈ℋ⁢(𝒬im) and dr∈ℋ⁢(𝒬m+1j)
𝒬u⁢p⁢d⁢a⁢t⁢e=dl.𝒜+dr.𝒜 
T=Q⁢T⁢r⁢a⁢n⁢s⁢(𝒬u⁢p⁢d⁢a⁢t⁢e,𝒦⁢ℬ) 
formal triple t∈T

create a new derivation d 
d.𝒜=t.eo⁢b⁢j 
d.𝒟=dl.𝒟⁢⋃dr.𝒟⁢⋃{t} 
update the model score of d 
insert d to ℋ⁢(𝒬ij) 





ℋ⁢(𝒬).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         The first half (from Line 1 to Line 13) generates a formal triple set
         T
         for each unary span
         𝒬ij∈𝒬
         , using the question translation method
         Q⁢T⁢r⁢a⁢n⁢s⁢(𝒬ij,𝒦⁢ℬ)
         (Line 4), which takes
         𝒬ij
         as the input.
Each triple
         t∈T
         returned is in the form of
         {es⁢b⁢j,p,eo⁢b⁢j}
         ,
where
         es⁢b⁢j
         ’s mention occurs in
         𝒬ij
         ,
         p
         is a predicate that denotes the meaning expressed by the context of
         es⁢b⁢j
         in
         𝒬ij
         ,
         eo⁢b⁢j
         is an answer of
         𝒬ij
         based on
         es⁢b⁢j
         ,
         p
         and
         𝒦⁢ℬ
         .
We describe the implementation detail of
         Q⁢T⁢r⁢a⁢n⁢s⁢(⋅)
         in Section 2.3.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p5">
        <p class="ltx_p">
         The second half (from Line 14 to Line 31) first updates the content of each bigger span
         𝒬ij
         by concatenating the answers to its any two consecutive smaller spans covered by
         𝒬ij
         (Line 18).
Then,
         Q⁢T⁢r⁢a⁢n⁢s⁢(𝒬ij,𝒦⁢ℬ)
         is called to generate triples for the updated span (Line 19).
The above operations are equivalent to answering a simplified question, which is obtained by replacing the answerable spans in the original question with their corresponding answers.
The search space
         ℋ⁢(𝒬)
         for the entire question
         𝒬
         is returned at last (Line 31).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Question Translation
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         The purpose of question translation is to translate a span
         𝒬
         to a set of formal triples
         T
         .
Each triple
         t∈T
         is in the form of
         {es⁢b⁢j,p,eo⁢b⁢j}
         , where
         es⁢b⁢j
         ’s mention
         occurs in
         𝒬
         ,
         p
         is a predicate that denotes the meaning expressed by the context of
         es⁢b⁢j
         in
         𝒬
         ,
         eo⁢b⁢j
         is an answer to
         𝒬
         retrieved from
         𝒦⁢ℬ
         using a triple query
         q={es⁢b⁢j,p,?}
         .
Note that if no predicate
         p
         or answer
         eo⁢b⁢j
         can be generated,
         {𝒬,N⁢u⁢l⁢l,𝒬}
         will be returned as a special triple,
which sets
         eo⁢b⁢j
         to be
         𝒬
         itself, and
         p
         to be
         N⁢u⁢l⁢l
         .
This makes sure the un-answerable spans can be passed on to the higher-level operations.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Question translation assumes each span
         𝒬
         is a
         single-relation question
         (Fader et al., 2013).
Such assumption simplifies the efforts of semantic parsing to the minimum question units,
while leaving the capability of handling multiple-relation questions (Figure 1 gives one such example) to the outer CYK-parsing based translation procedure.
Two question translation methods are presented in the rest of this subsection, which are based on question patterns and relation expressions respectively.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S2.SS3.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.3.1
         </span>
         Question Pattern-based Translation
        </h4>
        <div class="ltx_para" id="S2.SS3.SSS1.p1">
         <p class="ltx_p">
          𝒬⁢𝒫-based Question Translation
          IndexIndex
          T=∅ 
entity mention e𝒬∈𝒬
𝒬p⁢a⁢t⁢t⁢e⁢r⁢n = replace e𝒬 in 𝒬 with [S⁢l⁢o⁢t] 
question pattern 𝒬⁢𝒫
𝒬p⁢a⁢t⁢t⁢e⁢r⁢n == 𝒬⁢𝒫p⁢a⁢t⁢t⁢e⁢r⁢n
ℰ=D⁢i⁢s⁢a⁢m⁢b⁢i⁢g⁢u⁢a⁢t⁢e⁢(e𝒬,𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e) 
e∈ℰ

create a new triple query q 
q={e,𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e,?} 
{𝒜i}=A⁢n⁢s⁢w⁢e⁢r⁢R⁢e⁢t⁢r⁢i⁢e⁢v⁢e⁢(q,𝒦⁢ℬ) 
𝒜∈{𝒜i}

create a new formal triple t 
t={q.es⁢b⁢j,q.p,𝒜} 
t.s⁢c⁢o⁢r⁢e=1.0 
insert t to T
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS1.p2">
         <p class="ltx_p">
          T
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS1.p3">
         <p class="ltx_p">
          A question pattern
          𝒬⁢𝒫
          includes
a pattern string
          𝒬⁢𝒫p⁢a⁢t⁢t⁢e⁢r⁢n
          , which is composed of words and a slot symbol
          [S⁢l⁢o⁢t]
          , and
a KB predicate
          𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e
          , which denotes the meaning expressed by the context words in
          𝒬⁢𝒫p⁢a⁢t⁢t⁢e⁢r⁢n
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS1.p4">
         <p class="ltx_p">
          Algorithm 2 shows how to generate formal triples for a span
          𝒬
          based on question patterns (
          𝒬⁢𝒫
          -based question translation).
For each entity mention
          e𝒬∈𝒬
          , we replace it with
          [S⁢l⁢o⁢t]
          and obtain a pattern string
          𝒬p⁢a⁢t⁢t⁢e⁢r⁢n
          (Line 3).
If
          𝒬p⁢a⁢t⁢t⁢e⁢r⁢n
          can match one
          𝒬⁢𝒫p⁢a⁢t⁢t⁢e⁢r⁢n
          ,
then we construct a triple query
          q
          (Line 9) using
          𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e
          as its predicate and
one of the KB entities returned by
          D⁢i⁢s⁢a⁢m⁢b⁢i⁢g⁢u⁢a⁢t⁢e⁢(e𝒬,𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e)
          as its subject entity (Line 6).
Here, the objective of
          D⁢i⁢s⁢a⁢m⁢b⁢i⁢g⁢u⁢a⁢t⁢e⁢(e𝒬,𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e)
          is to output a set of disambiguated KB entities
          ℰ
          in
          𝒦⁢ℬ
          .
The name of each entity returned equals the input entity mention
          e𝒬
          and occurs in some assertions where
          𝒬⁢𝒫p⁢r⁢e⁢d⁢i⁢c⁢a⁢t⁢e
          are the predicates.
The underlying idea is to use the context (predicate) information to help entity disambiguation.
The answers of
          q
          are returned by
          A⁢n⁢s⁢w⁢e⁢r⁢R⁢e⁢t⁢r⁢i⁢e⁢v⁢e⁢(q,𝒦⁢ℬ)
          based on
          q
          and
          𝒦⁢ℬ
          (Line 10), each of which is used to construct a formal triple and added to
          T
          for
          𝒬
          (from Line 11 to Line 16).
Figure 2 gives an example.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS1.p5">
         <p class="ltx_p">
          Question patterns are collected as follows: First,
          5W
          queries, which begin with What, Where, Who, When, or Which, are selected from a large scale query log of a commercial search engine; Then, a cleaned entity dictionary is used to annotate each query by replacing all entity mentions it contains with the symbol
          [S⁢l⁢o⁢t]
          . Only high-frequent query patterns which contain one
          [S⁢l⁢o⁢t]
          are maintained;
Lastly, annotators try to manually label the most-frequent 50,000 query patterns with their corresponding predicates, and 4,764 question patterns with single labeled predicates are obtained.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS1.p6">
         <p class="ltx_p">
          From experiments (Table 3 in Section 4.3) we can see that, question pattern based question translation can achieve high end-to-end accuracy.
But as human efforts are needed in the mining procedure, this method cannot be extended to large scale very easily.
Besides, different users often type the questions with the same meaning in different NL expressions.
For example, although the question
          Forrest Gump was directed by which moviemaker
          means the same as the question
          𝒬
          in Figure 2, no question pattern can cover it.
We need to find an alternative way to alleviate such coverage issue.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS3.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.3.2
         </span>
         Relation Expression-based Translation
        </h4>
        <div class="ltx_para" id="S2.SS3.SSS2.p1">
         <p class="ltx_p">
          Aiming to alleviate the coverage issue occurring in
          𝒬⁢𝒫
          -based method, an alternative relation expression (
          ℛ⁢ℰ
          ) -based method is proposed, and will be used when the
          𝒬⁢𝒫
          -based method fails.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS2.p2">
         <p class="ltx_p">
          We define
          ℛ⁢ℰp
          as a relation expression set for a given KB predicate
          p∈𝒦⁢ℬ
          .
Each relation expression
          ℛ⁢ℰ∈ℛ⁢ℰp
          includes
an expression string
          ℛ⁢ℰe⁢x⁢p⁢r⁢e⁢s⁢s⁢i⁢o⁢n
          , which must contain at least one content word, and
a weight
          ℛ⁢ℰw⁢e⁢i⁢g⁢h⁢t
          , which denotes the confidence that
          ℛ⁢ℰe⁢x⁢p⁢r⁢e⁢s⁢s⁢i⁢o⁢n
          can represent
          p
          ’s meaning in NL.
For example,
          is the director of
          is one relation expression string for the predicate
          Film.Film.Director
          ,
which means it is usually used to express this relation (predicate) in NL.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS2.p3">
         <p class="ltx_p">
          ℛ⁢ℰ-based Question Translation
          IndexIndex
          T=∅ 
entity mention e𝒬∈𝒬
e∈𝒦⁢ℬ s.t. e.n⁢a⁢m⁢e==e𝒬
predicate p∈𝒦⁢ℬ related to e
s⁢c⁢o⁢r⁢e=S⁢i⁢m⁢(e𝒬,𝒬,ℛ⁢ℰp) 
s⁢c⁢o⁢r⁢e&gt;0

create a new triple query q 
q={e,p,?} 
{𝒜i}=A⁢n⁢s⁢w⁢e⁢r⁢R⁢e⁢t⁢r⁢i⁢e⁢v⁢e⁢(q,𝒦⁢ℬ) 
𝒜∈{𝒜i}

create a new formal triple t 
t={q.es⁢b⁢j,q.p,𝒜} 
t.s⁢c⁢o⁢r⁢e=s⁢c⁢o⁢r⁢e 
insert t to T 





sort T based on the score of each t∈T 
T.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS2.p4">
         <p class="ltx_p">
          Algorithm 3 shows how to generate triples for a question
          𝒬
          based on relation expressions.
For each possible entity mention
          e𝒬∈𝒬
          and a KB predicate
          p∈𝒦⁢ℬ
          that is related to a KB entity
          e
          whose name equals
          e𝒬
          ,
          S⁢i⁢m⁢(e𝒬,𝒬,ℛ⁢ℰp)
          is computed (Line 5) based on the similarity between question context and
          ℛ⁢ℰp
          ,
which measures how likely
          𝒬
          can be transformed into a triple query
          q={e,p,?}
          .
If this score is larger than
          0
          , which means there are overlaps between
          𝒬
          ’s context and
          ℛ⁢ℰp
          , then
          q
          will be used as the triple query of
          𝒬
          , and a set of formal triples will be generated based on
          q
          and
          𝒦⁢ℬ
          (from Line 7 to Line 15).
The computation of
          S⁢i⁢m⁢(e𝒬,𝒬,ℛ⁢ℰp)
          is defined as follows:
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx2">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex2">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            ∑n1|𝒬|-n+1⋅{∑ωn∈𝒬,ωn⁢⋂e𝒬=ϕP(ωn|ℛℰp)}
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
          n
          is the n-gram order which ranges from 1 to 5,
          ωn
          is an n-gram occurring in
          𝒬
          without overlapping with
          e𝒬
          and containing at least one content word,
          P(ωn|ℛℰp)
          is the posterior probability which is computed by:
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx3">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex3">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            P(ωn|ℛℰp)=C⁢o⁢u⁢n⁢t⁢(ωn,ℛ⁢ℰp)∑ωn′∈ℛ⁢ℰpC⁢o⁢u⁢n⁢t⁢(ωn′,ℛ⁢ℰp)
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          C⁢o⁢u⁢n⁢t⁢(ω,ℛ⁢ℰp)
          denotes the weighted sum of times that
          ω
          occurs in
          ℛ⁢ℰp
          :
         </p>
         <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx4">
          <tr class="ltx_equation ltx_align_baseline" id="S2.Ex4">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            C⁢o⁢u⁢n⁢t⁢(ω,ℛ⁢ℰp)=∑ℛ⁢ℰ∈ℛ⁢ℰp{#ω⁢(ℛ⁢ℰ)⋅ℛ⁢ℰw⁢e⁢i⁢g⁢h⁢t}
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
          #ω⁢(ℛ⁢ℰ)
          denotes the number of times that
          ω
          occurs in
          ℛ⁢ℰe⁢x⁢p⁢r⁢e⁢s⁢s⁢i⁢o⁢n
          , and
          ℛ⁢ℰw⁢e⁢i⁢g⁢h⁢t
          is decided by the relation expression extraction component.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS2.p5">
         <p class="ltx_p">
          Figure 3 gives an example, where n-grams with rectangles are the ones that occur in both
          𝒬
          ’s context and the relation expression set of a given predicate
          p=F⁢i⁢l⁢m.F⁢i⁢l⁢m.D⁢i⁢r⁢e⁢c⁢t⁢o⁢r
          .
Unlike the
          𝒬⁢𝒫
          -based method which needs a perfect match, the
          ℛ⁢ℰ
          -based method allows fuzzy matching between
          𝒬
          and
          ℛ⁢ℰp
          , and records this (Line 13) in generated triples, which is used as features later.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS2.p6">
         <p class="ltx_p">
          Relation expressions are mined as follows:
Given a set of KB assertions with an identical predicate
          p
          , we first extract all sentences from English Wiki pages
          , each of which contains at least one pair of entities occurring in one assertion.
Then, we extract the shortest path between paired entities in the dependency tree of each sentence as an
          ℛ⁢ℰ
          candidate for the given predicate.
The intuition is that any sentence containing such entity pairs occur in an assertion is likely to express the predicate of that assertion in some way.
Last, all relation expressions extracted are filtered by heuristic rules, i.e., the frequency must be larger than 4, the length must be shorter than 10, and then weighted by the pattern scoring methods proposed in
          [10, 11]
          . For each predicate, we only keep the relation expressions whose pattern scores are larger than a pre-defined threshold.
Figure 4 gives one relation expression extraction example.
The statistics and overall quality of the relation expressions are listed in Section 4.1.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS3.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.3.3
         </span>
         Question Decomposition
        </h4>
        <div class="ltx_para" id="S2.SS3.SSS3.p1">
         <p class="ltx_p">
          Sometimes, a question may provide multiple constraints to its answers.
          movie starred by Tom Hanks in 1994
          is one such question.
All the films as the answers of this question should satisfy the following two constraints:
(1) starred
          by Tom Hanks
          ; and
(2) released
          in 1994
          .
It is easy to see that such questions cannot be translated to single triples.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS3.p2">
         <p class="ltx_p">
          We propose a dependency tree-based method to handle such multiple-constraint questions by
(i) decomposing the original question into a set of
          sub-questions
          using syntax-based patterns; and
(ii) intersecting the answers of all sub-questions as the final answers of the original question.
Note, question decomposition only operates on the original question and question spans covered by complete dependency subtrees.
Four syntax-based patterns (Figure 5) are used for question decomposition.
If a question matches any one of these patterns, then sub-questions are generated by collecting the paths between
          n0
          and each
          ni(i&gt;0)
          in the pattern,
where each
          n
          denotes a complete subtree with a noun, number, or question word as its root node,
the symbol
          *
          above
          p⁢r⁢e⁢p*
          denotes this preposition can be skipped in matching.
For the question mentioned at the beginning, its two sub-questions generated are
          movie starred by Tom Hanks
          and
          movie starred in 1994
          ,
as its dependency form matches pattern (a).
Similar ideas are used in IBM Watson
          [13]
          as well.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS3.SSS3.p3">
         <p class="ltx_p">
          As dependency parsing is not perfect, we generate single triples for such questions without considering constraints as well,
and add them to the search space for competition.
          hs⁢y⁢n⁢t⁢a⁢x⁢_⁢c⁢o⁢n⁢s⁢t⁢r⁢a⁢i⁢n⁢t⁢(⋅)
          is used to boost triples that are converted from sub-questions generated by question decomposition.
The more constraints an answer satisfies, the better.
Obviously, current patterns used can’t cover all cases but most-common ones.
We leave a more general pattern mining method for future work.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Feature Design
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         The objective of our KB-QA system is to seek the derivation
         ⟨𝒟^,𝒜^⟩
         that maximizes the probability
         P(⟨𝒟,𝒜⟩|𝒦ℬ,𝒬)
         described in Section 2.1 as:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx5">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ⟨𝒟^,𝒜^⟩
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           a⁢r⁢g⁢m⁢a⁢x⟨𝒟,𝒜⟩∈ℋ⁢(𝒬)P(⟨𝒟,𝒜⟩|𝒦ℬ,𝒬)
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
           =
          </td>
          <td class="ltx_td ltx_align_left">
           a⁢r⁢g⁢m⁢a⁢x⟨𝒟,𝒜⟩∈ℋ⁢(𝒬)∑i=1Mλi⋅hi⁢(⟨𝒟,𝒜⟩,𝒦⁢ℬ,𝒬)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         We now introduce the feature sets
         {hi⁢(⋅)}
         that are used in the above linear model:
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p2">
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            hq⁢u⁢e⁢s⁢t⁢i⁢o⁢n⁢_⁢w⁢o⁢r⁢d⁢(⋅)
            ,
which counts the number of original question words occurring in
            𝒜
            .
It penalizes those partially answered questions.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            hs⁢p⁢a⁢n⁢(⋅)
            ,
which counts the number of spans in
            𝒬
            that are converted to formal triples.
It controls the granularity of the spans used in question translation.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            hs⁢y⁢n⁢t⁢a⁢x⁢_⁢s⁢u⁢b⁢t⁢r⁢e⁢e⁢(⋅)
            ,
which counts the number of spans in
            𝒬
            that are
(1) converted to formal triples, whose predicates are not
            N⁢u⁢l⁢l
            , and
(2) covered by complete dependency subtrees at the same time.
The underlying intuition is that, dependency subtrees of
            𝒬
            should be treated as units for question translation.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            hs⁢y⁢n⁢t⁢a⁢x⁢_⁢c⁢o⁢n⁢s⁢t⁢r⁢a⁢i⁢n⁢t⁢(⋅)
            ,
which counts the number of triples in
            𝒟
            that are converted from sub-questions generated by the question decomposition component.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i5.p1">
           <p class="ltx_p">
            ht⁢r⁢i⁢p⁢l⁢e⁢(⋅)
            ,
which counts the number of triples in
            𝒟
            , whose predicates are not
            N⁢u⁢l⁢l
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i6.p1">
           <p class="ltx_p">
            ht⁢r⁢i⁢p⁢l⁢ew⁢e⁢i⁢g⁢h⁢t⁢(⋅)
            ,
which sums the scores of all triples
            {ti}
            in
            𝒟
            as
            ∑ti∈𝒟ti.s⁢c⁢o⁢r⁢e
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i7.p1">
           <p class="ltx_p">
            h𝒬⁢𝒫c⁢o⁢u⁢n⁢t⁢(⋅)
            ,
which counts the number of triples in
            𝒟
            that are generated by
            𝒬⁢𝒫
            -based question translation method.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i8" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i8.p1">
           <p class="ltx_p">
            hℛ⁢ℰc⁢o⁢u⁢n⁢t⁢(⋅)
            ,
which counts the number of triples in
            𝒟
            that are generated by
            ℛ⁢ℰ
            -based question translation method.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i9" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i9.p1">
           <p class="ltx_p">
            hs⁢t⁢a⁢t⁢i⁢c⁢r⁢a⁢n⁢ks⁢b⁢j⁢(⋅)
            ,
which sums the static rank scores of all subject entities in
            𝒟
            ’s triple set as
            ∑ti∈𝒟ti.es⁢b⁢j.s⁢t⁢a⁢t⁢i⁢c⁢_⁢r⁢a⁢n⁢k
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i10" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i10.p1">
           <p class="ltx_p">
            hs⁢t⁢a⁢t⁢i⁢c⁢r⁢a⁢n⁢ko⁢b⁢j⁢(⋅)
            ,
which sums the static rank scores of all object entities in
            𝒟
            ’s triple set as
            ∑ti∈𝒟ti.eo⁢b⁢j.s⁢t⁢a⁢t⁢i⁢c⁢_⁢r⁢a⁢n⁢k
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i11" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i11.p1">
           <p class="ltx_p">
            hc⁢o⁢n⁢f⁢i⁢d⁢e⁢n⁢c⁢eo⁢b⁢j⁢(⋅)
            ,
which sums the confidence scores of all object entities in
            𝒟
            ’s triple set as
            ∑t∈𝒟t.eo⁢b⁢j.c⁢o⁢n⁢f⁢i⁢d⁢e⁢n⁢c⁢e
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S2.SS4.p3">
        <p class="ltx_p">
         For each assertion
         {es⁢b⁢j,p,eo⁢b⁢j}
         stored in
         𝒦⁢ℬ
         ,
         es⁢b⁢j.s⁢t⁢a⁢t⁢i⁢c⁢_⁢r⁢a⁢n⁢k
         and
         eo⁢b⁢j.s⁢t⁢a⁢t⁢i⁢c⁢_⁢r⁢a⁢n⁢k
         denote the static rank scores
         for
         es⁢b⁢j
         and
         eo⁢b⁢j
         respectively;
         eo⁢b⁢j.c⁢o⁢n⁢f⁢i⁢d⁢e⁢n⁢c⁢e⁢_⁢r⁢a⁢n⁢k
         represents the probability
         p(eo⁢b⁢j|es⁢b⁢j,p)
         .
These three scores are used as features to rank answers generated in QA procedure.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.5
        </span>
        Feature Weight Tuning
       </h3>
       <div class="ltx_para" id="S2.SS5.p1">
        <p class="ltx_p">
         Given a set of question-answer pairs
         {𝒬i,𝒜ir⁢e⁢f}
         as the development (dev) set, we use the minimum error rate training (MERT)
         [21]
         algorithm to tune the feature weights
         λiM
         in our proposed model. The training criterion is to seek the feature weights that can minimize the accumulated errors of the top-1 answer of questions in the dev set:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx6">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           λ^1M
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           a⁢r⁢g⁢m⁢i⁢nλ1M∑i=1NE⁢r⁢r⁢(𝒜ir⁢e⁢f,𝒜i^;λ1M)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         N
         is the number of questions in the dev set,
         𝒜ir⁢e⁢f
         is the correct answers as references of the
         it⁢h
         question in the dev set,
         𝒜i^
         is the top-1 answer candidate of the
         it⁢h
         question in the dev set based on feature weights
         λ1M
         ,
         E⁢r⁢r⁢(⋅)
         is the error function which is defined as:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S5.EGx7">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           E⁢r⁢r⁢(𝒜ir⁢e⁢f,𝒜i^;λ1M)
          </td>
          <td class="ltx_td ltx_align_center">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           1-δ⁢(𝒜ir⁢e⁢f,𝒜i^)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         δ⁢(𝒜ir⁢e⁢f,𝒜i^)
         is an indicator function which equals 1 when
         𝒜i^
         is included in the reference set
         𝒜ir⁢e⁢f
         , and 0 otherwise.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Comparison with Previous Work
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Our work intersects with two research directions: semantic parsing and question answering.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Some previous works on semantic parsing
        [25, 26, 23, 27, 24, 15, 16]
        require manually annotated logical forms as supervision,
and are hard to extend resulting parsers from limited domains, such as GEO, JOBS and ATIS, to open domains.
Recent works
        [5, 18]
        have alleviated such issues using question-answer pairs as weak supervision,
but still with the shortcoming of using limited lexical triggers to link NL phrases to predicates.
        Poon (2013)
        has proposed an unsupervised method by adopting grounded-learning to leverage the database for indirect supervision. But transformation from NL questions to MRs heavily depends on dependency parsing results. Besides, the KB used (ATIS) is limited as well.
        Kwiatkowski et al. (2013)
        use Wiktionary and a limited manual lexicon to map POS tags to a set of predefined CCG lexical categories, which aims to reduce the need for learning lexicon from training data. But it still needs human efforts to define lexical categories, which usually can not cover all the semantic phenomena.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Berant et al. (2013)
        have not only enlarged the KB used for Freebase
        [12]
        , but also used a bigger lexicon trigger set extracted by the open IE method
        [19]
        for NL phrases to predicates linking.
In comparison, our method has further advantages:
(1) Question answering and semantic parsing are performed in an joint way under a unified framework;
(2) A robust method is proposed to map NL questions to their formal triple queries, which trades off the mapping quality by using question patterns and relation expressions in a cascaded way; and
(3) We use domain independent feature set which allowing us to use a relatively small number of question-answer pairs to tune model parameters.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Fader et al. (2013)
        map questions to formal (triple) queries over a large scale, open-domain database of facts extracted from a raw corpus by ReVerb
        [8]
        .
Compared to their work, our method gains an improvement in two aspects:
(1) Instead of using facts extracted using the open IE method, we leverage a large scale, high-quality knowledge base;
(2) We can handle multiple-relation questions, instead of single-relation queries only, based on our translation based KB-QA framework.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Espana-Bonet and Comas (2012)
        have proposed an MT-based method for factoid QA.
But MT in there work means to translate questions into
        n
        -best translations, which are used for finding similar sentences in the document collection that probably contain answers.
        Echihabi and Marcu (2003)
        have developed a noisy-channel model for QA,
which explains how a sentence containing an answer to a given question can be rewritten into that question through a sequence of stochastic operations.
Compared to the above two MT-motivated QA work, our method uses MT methodology to translate questions to answers directly.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiment
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Data Sets
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Following
         Berant et al. (2013)
         ,
we use the same subset of WEBQUESTIONS (3,778 questions) as the development set (Dev) for weight tuning in MERT,
and use the other part of WEBQUESTIONS (2,032 questions) as the test set (Test).
Table 1 shows the statistics of this data set.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Table 2 shows the statistics of question patterns and relation expressions used in our KB-QA system.
As all question patterns are collected with human involvement as we discussed in Section 2.3.1, the quality is very high (
         98⁢%
         ).
We also sample 1,000 instances from the whole relation expression set and manually label their quality.
The accuracy is around
         89⁢%
         .
These two resources can cover 566 head predicates in our KB.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        KB-QA Systems
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Since
         Berant et al. (2013)
         is one of the latest work which has reported QA results based on a large scale, general domain knowledge base (Freebase),
we consider their evaluation result on WEBQUESTIONS as our baseline.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Our KB-QA system generates the
         k
         -best derivations for each question span, where
         k
         is set to 20.
The answers with the highest model scores are considered the best answers for evaluation.
For evaluation, we follow
         Berant et al. (2013)
         to allow partial credit and score an answer using the F1 measure, comparing the predicted set of entities to the annotated set of entities.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         One difference between these two systems is the KB used.
Since Freebase is completely contained by our KB, we disallow all entities which are not included by Freebase.
By doing so, our KB provides the same knowledge as Freebase does,
which means we do not gain any extra advantage by using a larger KB.
But we still allow ourselves to use the static rank scores and confidence scores of entities as features, as we described in Section 2.4.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Evaluation Results
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We first show the overall evaluation results of our KB-QA system and compare them with baseline’s results on Dev and Test.
Note that we do not re-implement the baseline system, but just list their evaluation numbers reported in the paper.
Comparison results are listed in Table 3.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         Table 3 shows our KB-QA method outperforms baseline on both Dev and Test.
We think the potential reasons of this improvement include:
        </p>
        <ul class="ltx_itemize" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Different methods are used to map NL
            phrases
            to KB predicates.
            Berant et al. (2013)
            have used a lexicon extracted from a subset of ReVerb triples
            [19]
            , which is similar to the relation expression set used in question translation.
But as our relation expressions are extracted by an in-house extractor, we can record their extraction-related statistics as extra information, and use them as features to measure the mapping quality.
Besides, as a portion of entities in our KB are extracted from Wiki, we know the one-to-one correspondence between such entities and Wiki pages, and use this information in relation expression extraction for entity disambiguation.
A lower disambiguation error rate results in better relation expressions.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Question patterns are used to map NL
            context
            to KB predicates.
Context can be either continuous or discontinues phrases.
Although the size of this set is limited, they can actually cover head questions/queries
            very well.
The underlying intuition of using patterns is that those high-frequent questions/queries should and can be treated and solved in the QA task, by involving human effort at a relative small price but with very impressive accuracy.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         In order to figure out the impacts of question patterns and relation expressions,
another experiment (Table 4) is designed to evaluate their independent influences,
where
         𝒬⁢𝒫o⁢n⁢l⁢y
         and
         ℛ⁢ℰo⁢n⁢l⁢y
         denote the results of KB-QA systems which only allow question patterns and relation expressions in question translation respectively.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p4">
        <p class="ltx_p">
         From Table 4 we can see that the accuracy of
         ℛ⁢ℰo⁢n⁢l⁢y
         on Test (
         32.5⁢%
         ) is slightly better than baseline’s result (
         31.4⁢%
         ).
We think this improvement comes from two aspects:
(1) The quality of the relation expressions is better than the quality of the lexicon entries used in the baseline; and
(2) We use the extraction-related statistics of relation expressions as features, which brings more information to measure the confidence of mapping between NL phrases and KB predicates, and makes the model to be more flexible.
Meanwhile,
         𝒬⁢𝒫o⁢n⁢l⁢y
         perform worse (
         11.8⁢%
         ) than
         ℛ⁢ℰo⁢n⁢l⁢y
         , due to coverage issue.
But by comparing the precisions of these two settings, we find
         𝒬⁢𝒫o⁢n⁢l⁢y
         (97.5%) outperforms
         ℛ⁢ℰo⁢n⁢l⁢y
         (73.2%) significantly, due to its high quality.
This means how to extract high-quality question patterns is worth to be studied for the question answering task.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p5">
        <p class="ltx_p">
         As the performance of our KB-QA system relies heavily on the
         k
         -best beam approximation,
we evaluate the impact of the beam size and list the comparison results in Figure 6.
We can see that as we increase
         k
         incrementally, the accuracy increase at the same time.
However, a larger
         k
         (e.g. 200) cannot bring significant improvements comparing to a smaller one (e.g., 20), but using a large
         k
         has a tremendous impact on system efficiency.
So we choose
         k=20
         as the optimal value in above experiments, which trades off between accuracy and efficiency.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p6">
        <p class="ltx_p">
         Actually, the size of our system’s search space is much smaller than the one of the semantic parser used in the baseline.This is due to the fact that, if triple queries generated by the question translation component cannot derive any answer from KB, we will discard such triple queries directly during the QA procedure.
We can see that using a small
         k
         can achieve better results than baseline, where the beam size is set to be 200.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.4
        </span>
        Error Analysis
       </h3>
       <div class="ltx_subsubsection" id="S4.SS4.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.4.1
         </span>
         Entity Detection
        </h4>
        <div class="ltx_para" id="S4.SS4.SSS1.p1">
         <p class="ltx_p">
          Since named entity recognizers trained on Penn TreeBank usually perform poorly on web queries,
We instead use a simple string-match method to detect entity mentions in the question using a cleaned entity dictionary dumped from our KB.
One problem of doing so is the entity detection issue.
For example, in the question
          who was Esther’s husband ?
          , we cannot detect
          Esther
          as an entity, as it is just part of an entity name.
We need an ad-hoc entity detection component to handle such issues, especially for a web scenario,
where users often type entity names in their partial or abbreviation forms.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS4.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.4.2
         </span>
         Predicate Mapping
        </h4>
        <div class="ltx_para" id="S4.SS4.SSS2.p1">
         <p class="ltx_p">
          Some questions lack sufficient evidences to detect predicates.
          where is Byron Nelson 2012 ?
          is an example.
Since each relation expression must contain at least one content word, this question cannot match any relation expression.
Except for
          Byron Nelson
          and
          2012
          , all the others are non-content words.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS4.SSS2.p2">
         <p class="ltx_p">
          Besides, ambiguous entries contained in relation expression sets of different predicates can bring mapping errors as well.
For the following question
          who did Steve Spurrier play pro football for?
          as an example,
since the unigram
          play
          exists in both
          Film.Film.Actor
          and
          American_Football.Player.Current_Team
          ’s relation expression sets, we made a wrong prediction, which led to wrong answers.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS4.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.4.3
         </span>
         Specific Questions
        </h4>
        <div class="ltx_para" id="S4.SS4.SSS3.p1">
         <p class="ltx_p">
          Sometimes, we cannot give exact answers to superlative questions like
          what is the first book Sherlock Holmes appeared in?
          .
For this example, we can give all book names where
          Sherlock Holmes
          appeared in, but we cannot rank them based on their publication date
, as we cannot learn the alignment between the constraint word
          first
          occurred in the question and the predicate
          Book.Written_Work.Date_Of_First_Publication
          from training data automatically.
Although we have followed some work
          [22, 18]
          to handle such special linguistic phenomena by defining some specific operators, it is still hard to cover all unseen cases. We leave this
to future work as an independent topic.
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
