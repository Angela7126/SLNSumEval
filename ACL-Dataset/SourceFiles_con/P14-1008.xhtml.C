<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Logical Inference on Dependency-based Compositional Semantics.
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
       Dependency-based Compositional Semantics (DCS) is a framework of
natural language semantics with easy-to-process structures as well as
strict semantics.
In this paper, we equip the DCS framework with logical inference, by defining
       abstract
denotations
       as an abstraction of the computing process of denotations in original DCS. An inference
engine is built to achieve inference on abstract denotations. Furthermore, we propose a way to
generate on-the-fly knowledge in logical inference, by combining our framework with the
idea of tree transformation. Experiments on FraCaS and PASCAL RTE datasets show
promising results.
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
        Dependency-based Compositional Semantics (DCS) provides an intuitive way to model semantics of
questions, by using simple dependency-like trees
        []
        .
It is expressive enough to represent complex natural language queries on a relational
database, yet
simple enough to be latently learned from question-answer pairs. In this paper, we equip DCS with
        logical inference
        ,
which, in one point of view, is “the best way of testing an NLP system’s semantic capacity”
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        It should be noted that, however, a framework primarily designed for question answering
is not readily suited for logical inference. Because, answers returned by a query
depend on the specific database, but implication is independent of any databases.
For example, answers to the question “
        What books are read by students?
        ”, should always
be a subset of answers to “
        What books are ever read by anyone?
        ”, no matter how we store
the data of students and how many records of books are there in our database.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Thus, our first step is to fix a notation which abstracts the calculation process of DCS trees,
so as to clarify its meaning without the aid of any existing database. The idea is to
borrow a minimal set of operators from relational algebra
        []
        , which is already able
to formulate
the calculation in DCS and define
        abstract denotation
        , which is an abstraction of
the
        computation
        of denotations guided by DCS trees. Meanings of sentences then can be represented
by primary relations among abstract denotations. This formulation keeps
the simpleness and computability of DCS trees mostly unaffected; for example, our semantic calculation
for DCS trees is parallel to the denotation computation in original DCS.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        An inference engine is built to handle inference on abstract denotations. Moreover, to compensate
the lack of background knowledge in practical inference, we combine our
framework with the idea of tree
transformation
        []
        , to propose a way of generating knowledge in
logical representation from entailment rules
        []
        , which are by now typically
considered as syntactic rewriting rules.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We test our system on FraCaS
        []
        and PASCAL RTE datasets
        []
        .
The experiments show: (i) a competitive performance on FraCaS dataset; (ii) a big impact of
our automatically generated on-the-fly knowledge in achieving high recall for a logic-based RTE system;
and (iii) a result that outperforms state-of-the-art RTE system on RTE5 data. Our
whole system is publicly released and can be downloaded from
        http://kmcs.nii.ac.jp/tianran/tifmo/
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       The Idea
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        In this section we describe the idea of representing natural
language semantics by DCS trees, and achieving inference by computing logical
relations among the corresponding abstract denotations.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        DCS trees
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         DCS trees has been proposed to
represent natural language semantics with a structure similar to
dependency trees
         []
         (Figure
         1
         ).
For the sentence “
         students read books
         ”, imagine a
database consists of three tables, namely, a set of students, a set
of books, and a set of “reading” events (Table
         1
         ).
The DCS tree in Figure
         1
         is interpreted as a command
for querying these tables, obtaining “reading” entries whose
“
         SUBJ
         ” field is
         student
         and whose “
         OBJ
         ”
field is
         book
         . The result is
a set
         {John reads Ulysses,…}
         , which is called a
         denotation
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         DCS trees can be extended to represent
linguistic phenomena such as quantification and coreference, with additional markers
introducing additional operations on tables.
Figure
         2
         shows an example with a quantifier “
         every
         ”,
which is marked as “
         ⊂
         ” on
the edge
         (𝐥𝐨𝐯𝐞)⁢OBJ-ARG⁢(𝐝𝐨𝐠)
         and interpreted
as a
         division operator
         q⊂𝙾𝙱𝙹
         (§
         2.2
         ).
Optimistically, we believe DCS can provide a framework of semantic representation with
sufficiently wide coverage for real-world texts.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The strict semantics of DCS trees brings us the idea of applying DCS
to logical inference. This is not trivial, however, because
DCS works under the assumption that databases are explicitly available.
Obviously this is unrealistic for logical inference on
unrestricted texts, because we cannot prepare a database for everything
in the world. This fact fairly restricts the applicable tasks of DCS.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         Our solution is to redefine DCS trees without the aid of any databases,
by considering each node of a DCS tree as a content word in a sentence
(but may no longer be a table in a specific database),
while each edge represents semantic relations between two words.
The labels on both ends of an edge, such as
         SUBJ
         (subject) and
         OBJ
         (object), are considered as
         semantic roles
         of the
corresponding words
         . To formulate the database querying process defined by a
DCS tree, we provide formal semantics to DCS trees by employing
         relational algebra
         []
         for representing the query.
As described below, we represent meanings of sentences with
         abstract denotations
         , and logical relations among sentences are computed
as relations among their abstract denotations. In this way, we can
perform inference over formulas of
relational algebra, without computing database entries explicitly.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Abstract denotations
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Abstract denotations
         are formulas constructed from a minimal set of relational
algebra
         []
         operators, which is already able to formulate the database queries
defined by DCS trees.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         For example, the semantics of “
         students read books
         ” is
given by the abstract denotation:
        </p>
        F1=𝐫𝐞𝐚𝐝∩(𝐬𝐭𝐮𝐝𝐞𝐧𝐭𝚂𝚄𝙱𝙹×𝐛𝐨𝐨𝐤𝙾𝙱𝙹),
        <p class="ltx_p">
         where
         read
         ,
         student
         and
         book
         denote sets
represented by these words respectively, and
         wr
         represents the set
         w
         considered as the domain of the semantic role
         r
         (e.g.
         𝐛𝐨𝐨𝐤𝙾𝙱𝙹
         is
the set of books considered as objects). The operators
         ∩
         and
         ×
         represent intersection and Cartesian product
respectively, both borrowed from relational algebra.
It is not hard to see the abstract denotation denotes the intersection of the
“
         reading
         ” set (as illustrated by the “
         read
         ” table in Table
         1
         )
with the product of “
         student
         ” set and “
         book
         ” set,
which results in the same denotation as computed by the DCS tree in Figure
         1
         ,
i.e.
         {John reads Ulysses,…}
         . However, the point is that
         F1
         itself is an algebraic formula that does not depend on any concrete databases.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         Formally, we introduce the following
         constants
         :
        </p>
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            W
            : a universal set containing all entities.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Content words: a content word (e.g.
            read
            ) defines a set
representing the word (e.g.
            𝐫𝐞𝐚𝐝={(x,y)| r⁢e⁢a⁢d⁢(x,y)}
            ).
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         In addition we introduce following
         functions
         :
        </p>
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            ×
            : the Cartesian product of two sets.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            ∩
            : the intersection of two sets.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            πr
            : projection onto domain of semantic role
            r
            (e.g.
            π𝙾𝙱𝙹⁢(𝐫𝐞𝐚𝐝)={y| ∃x;r⁢e⁢a⁢d⁢(x,y)}
            ). Generally
we admit projections onto multiple semantics roles, denoted by
            πR
            where
            R
            is
a set of semantic roles.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            ιr
            : relabeling (e.g.
            ι𝙾𝙱𝙹⁢(𝐛𝐨𝐨𝐤)=𝐛𝐨𝐨𝐤𝙾𝙱𝙹
            ).
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i5.p1">
           <p class="ltx_p">
            q⊂r
            : the division operator, where
            q⊂r⁢(A,B)
            is defined as the
largest set
            X
            which satisfies
            Br×X⊂A
            .
            This is used to formulate universal quantifiers, such as
“
            Mary loves every dog
            ” and “
            books read by all students
            ”.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         An
         abstract denotation
         is then defined as finite applications of functions on either constants
or other abstract denotations.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Statements
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         As the semantics of DCS trees is formulated by abstract denotations,
the meanings of declarative sentences are represented by
         statements
         on abstract denotations. Statements are declarations of some relations
among abstract denotations, for which we consider the following set relations:
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Non-emptiness
         A≠∅
         : the set
         A
         is not empty.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         Subsumption
         A⊂B
         : set
         A
         is subsumed by
         B
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         Roughly speaking, the relations correspond to
the logical concepts
         satisfiability
         and
         entailment
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p5">
        <p class="ltx_p">
         Abstract denotations and statements are convenient for
representing semantics of various types of expressions and linguistic
knowledge. Some examples are shown in
Table
         2
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Logical inference on DCS
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         Based on abstract denotations, we briefly describe our process to apply DCS to
textual inference.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S2.SS4.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.4.1
         </span>
         Natural language to DCS trees
        </h4>
        <div class="ltx_para" id="S2.SS4.SSS1.p1">
         <p class="ltx_p">
          To obtain DCS trees from natural language, we use Stanford
CoreNLP
          for dependency parsing
          []
          , and convert Stanford dependencies to DCS trees by pattern matching on POS tags and dependency
labels.
          Currently we use the following
semantic roles:
          ARG
          ,
          SUBJ
          ,
          OBJ
          ,
          IOBJ
          ,
          TIME
          and
          MOD
          . The semantic role
          MOD
          is used for any
restrictive modifiers. Determiners such as “all”, “every” and “each”
trigger quantifiers, as shown in Figure
          2
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS4.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.4.2
         </span>
         DCS trees to statements
        </h4>
        <div class="ltx_para" id="S2.SS4.SSS2.p1">
         <p class="ltx_p">
          A DCS tree
          𝒯=(𝒩,ℰ)
          is defined as a rooted tree,
where each node
          σ∈𝒩
          is labeled with a content word
          w⁢(σ)
          and each edge
          (σ,σ′)∈ℰ⊂𝒩×𝒩
          is labeled with a pair of semantic roles
          (r,r′)
          .
Here
          σ
          is the node nearer to the root. Furthermore, for each edge
          (σ,σ′)
          we
can optionally assign a quantification marker.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p2">
         <p class="ltx_p">
          Abstract denotation of a DCS tree can be calculated in a bottom-up manner.
For example, the abstract denotation of
          H
          in Figure
          2
          is
calculated from the leaf node
          Mary
          , and then:
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p3">
         <p class="ltx_p">
          Node
          love
          (
          Mary loves
          ):
          F2=𝐥𝐨𝐯𝐞∩(𝐌𝐚𝐫𝐲𝚂𝚄𝙱𝙹×W𝙾𝙱𝙹)
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p4">
         <p class="ltx_p">
          Node
          animal
          (
          Animal that Mary loves
          ):
          F3=𝐚𝐧𝐢𝐦𝐚𝐥∩π𝙾𝙱𝙹⁢(F2)
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p5">
         <p class="ltx_p">
          Node
          have
          (
          Tom has an animal that Mary loves
          ):
          F4=𝐡𝐚𝐯𝐞∩(𝐓𝐨𝐦𝚂𝚄𝙱𝙹×(F3)𝙾𝙱𝙹)
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p6">
         <p class="ltx_p">
          Formally, suppose the root
          σ
          of a DCS tree
          𝒯
          has children
          τ1,…,τn
          , and edges
          (σ,τ1),…,(σ,τn)
          labeled by
          (r1,r1′),…,(rn,rn′)
          , respectively.
The abstract denotation of
          𝒯
          is defined as:
         </p>
         [[𝒯]]=w⁢(σ)∩(⋂i=1nιri⁢(πri′⁢([[𝒯τi]]))×WRσ∖ri),
         <p class="ltx_p">
          where
          𝒯τi
          is the subtree of
          𝒯
          rooted at
          τi
          , and
          Rσ
          is the set of possible semantic roles for content word
          w⁢(σ)
          (e.g.
          R𝐥𝐨𝐯𝐞={𝚂𝚄𝙱𝙹,𝙾𝙱𝙹}
          ),
and
          WRσ∖ri
          is the product of
          W
          which has dimension
          Rσ∖ri
          (e.g.
          W{𝚂𝚄𝙱𝙹,𝙾𝙱𝙹}∖𝚂𝚄𝙱𝙹=W𝙾𝙱𝙹
          ).
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p7">
         <p class="ltx_p">
          When universal quantifiers are involved, we need to add division operators
to the formula. If
          (σ,τi)
          is assigned by a
quantification marker “
          ⊂
          ”
          , then the abstract denotation
is
         </p>
         [[𝒯]]=q⊂ri⁢(πRσ∖{r1,…,ri-1}⁢([[𝒯′]]),πri′⁢([[𝒯τi]])),
         <p class="ltx_p">
          where
          𝒯′
          is the same tree as
          𝒯
          except that
the edge
          (σ,τi)
          is removed. For example, the abstract
denotation of the first sentence of
          T
          in Figure
          2
          (
          Mary loves every dog
          ) is calculated from
          F2
          (
          Mary loves
          ) as
         </p>
         F5=q⊂𝙾𝙱𝙹⁢(π𝙾𝙱𝙹⁢(F2),𝐝𝐨𝐠).
        </div>
        <div class="ltx_para" id="S2.SS4.SSS2.p8">
         <p class="ltx_p">
          After the abstract denotation
          [[𝒯]]
          is calculated,
the statement representing the meaning of the sentence is defined as
          [[𝒯]]≠∅
          . For example, the statement of “
          students read books
          ”
is
          𝐫𝐞𝐚𝐝∩(𝐬𝐭𝐮𝐝𝐞𝐧𝐭𝚂𝚄𝙱𝙹×𝐛𝐨𝐨𝐤𝙾𝙱𝙹)≠∅
          , and
the statement of “
          Mary loves every dog
          ”
is
          q⊂𝙾𝙱𝙹⁢(π𝙾𝙱𝙹⁢(F2),𝐝𝐨𝐠)≠∅
          ,
which is logically equivalent to
          𝐝𝐨𝐠⊂π𝙾𝙱𝙹⁢(F2)
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS4.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.4.3
         </span>
         Logical inference
        </h4>
        <div class="ltx_para" id="S2.SS4.SSS3.p1">
         <p class="ltx_p">
          Since meanings of sentences are represented by
statements on abstract denotations, logical inference
among sentences is reduced to deriving new relations among
abstract denotations. This is done by applying axioms to known statements, and approximately
30 axioms are implemented (Table
          3
          ).
These are algebraic properties of abstract denotations,
among which we choose a set of axioms that can be handled efficiently and enable
most common types of inference seen in natural language.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS3.p2">
         <p class="ltx_p">
          For the example in Figure
          2
          , by constructing the following abstract denotations:
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS3.p3">
         <p class="ltx_p">
          Tom has a dog
          :
          F6=𝐡𝐚𝐯𝐞∩(𝐓𝐨𝐦𝚂𝚄𝙱𝙹×𝐝𝐨𝐠𝙾𝙱𝙹)
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS3.p4">
         <p class="ltx_p">
          Objects
          that Tom has
          :
          F7=π𝙾𝙱𝙹⁢(𝐡𝐚𝐯𝐞∩(𝐓𝐨𝐦𝚂𝚄𝙱𝙹×W𝙾𝙱𝙹))
          ,
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS3.p5">
         <p class="ltx_p">
          we can use the lexical knowledge
          𝐝𝐨𝐠⊂𝐚𝐧𝐢𝐦𝐚𝐥
          , the statements of
          T
          (i.e.
          𝐝𝐨𝐠⊂π𝙾𝙱𝙹⁢(F2)
          and
          F6≠∅
          ), and the axioms in
Table
          3
          ,
          to prove the statement of
          H
          (i.e.
          F4≠∅
          ) (Figure
          3
          ).
         </p>
        </div>
        <div class="ltx_para" id="S2.SS4.SSS3.p6">
         <p class="ltx_p">
          We built an inference engine to perform logical inference on abstract denotations
as above. In this logical system, we treat abstract denotations as
          terms
          and
statements as
          atomic sentences
          , which are far more easier to handle than
first order predicate logic (FOL) formulas. Furthermore, all implemented axioms are
horn clauses, hence we can employ forward-chaining, which is very efficient.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.5
        </span>
        Extensions
       </h3>
       <div class="ltx_para" id="S2.SS5.p1">
        <p class="ltx_p">
         Further extensions of our framework are made to deal with additional linguistic
phenomena, as briefly explained below.
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS5.SSS3.P1">
        <h5 class="ltx_title ltx_title_paragraph">
         Negation
        </h5>
        <div class="ltx_para" id="S2.SS5.SSS3.P1.p1">
         <p class="ltx_p">
          To deal with negation in our forward-chaining inference engine, we introduce
one more relation on abstract denotations, namely
          disjointness
          A∥B
          , meaning that
          A
          and
          B
          are disjoint sets. Using disjointness
we implemented two types of negations: (i) atomic negation, for each content word
          w
          we allow negation
          w¯
          of that word,
characterized by the property
          w∥w¯
          ; and (ii)
root negation, for a DCS tree
          𝒯
          and its denotation
          [[𝒯]]
          ,
the negation of
          𝒯
          is represented by
          𝒯∥𝒯
          ,
meaning that
          𝒯=∅
          in its effect.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS5.SSS3.P2">
        <h5 class="ltx_title ltx_title_paragraph">
         Selection
        </h5>
        <div class="ltx_para" id="S2.SS5.SSS3.P2.p1">
         <p class="ltx_p">
          Selection operators in relational algebra select a subset from a set to satisfy some specific
properties. This can be employed to represent linguistic phenomena such as
downward monotonicity and
generalized quantifiers. In the current system, we implement (i)
superlatives,
e.g.
          sh⁢i⁢g⁢h⁢e⁢s⁢t⁢(𝐦𝐨𝐮𝐧𝐭𝐚𝐢𝐧∩(W𝙰𝚁𝙶×𝐀𝐬𝐢𝐚𝙼𝙾𝙳))
          (the highest mountain in Asia) and (ii) numerics, e.g.
          st⁢w⁢o⁢(𝐩𝐞𝐭∩𝐟𝐢𝐬𝐡)
          (two pet fish), where
          sf
          is a selection marker.
Selection operators are implemented as markers assigned to abstract denotations,
with specially designed axioms. For example
superlatives satisfy the following property:
          A⊂B⁢&amp;⁢sh⁢i⁢g⁢h⁢e⁢s⁢t⁢(B)⊂A⇒sh⁢i⁢g⁢h⁢e⁢s⁢t⁢(B)=sh⁢i⁢g⁢h⁢e⁢s⁢t⁢(A)
          .
New rules can be added if necessary.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS5.SSS3.P3">
        <h5 class="ltx_title ltx_title_paragraph">
         Coreference
        </h5>
        <div class="ltx_para" id="S2.SS5.SSS3.P3.p1">
         <p class="ltx_p">
          We use Stanford CoreNLP to resolve coreferences
          []
          ,
whereas coreference is implemented as a special type of selection.
If a node
          σ
          in a DCS tree
          𝒯
          belongs to a mention cluster
          m
          ,
we take the abstract denotation
          [[𝒯σ]]
          and make a selection
          sm⁢([[𝒯σ]])
          , which is regarded as the abstract denotation
of that mention. Then all selections of the same mention cluster are declared to be equal.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Generating On-the-fly Knowledge
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Recognizing textual entailment (RTE) is the task of determining whether a given textual
statement
        H
        can be inferred by a text passage
        T
        . For this,
our primary textual inference system operates as:
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <ol class="ltx_enumerate" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           For a
           T
           -
           H
           pair, apply dependency parsing and coreference resolution.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           Perform rule-based conversion from dependency parses to DCS trees, which are
translated to statements on abstract denotations.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           Use statements of
           T
           and linguistic knowledge as premises, and try to prove
statements of
           H
           by our inference engine.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        However, this method does not work for real-world datasets
such as PASCAL RTE
        []
        , because of the knowledge bottleneck: it is often
the case that the lack of sufficient linguistic knowledge causes
failure of inference, thus the system outputs “no entailment”
for almost all pairs
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The transparent syntax-to-semantics interface of DCS enables us to
back off to NLP techniques during inference for catching
up the lack of knowledge. We extract fragments of DCS
trees as paraphrase candidates, translate them back
to linguistic expressions, and apply distributional similarity to judge their
validity. In this way, our
framework combines distributional and logical semantics, which is
also the main subject of
        and
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        As follows, our full system (Figure
        4
        ) additionally invokes
linguistic knowledge on-the-fly:
       </p>
       <ol class="ltx_enumerate" id="I4">
        <li class="ltx_item" id="I4.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          4.
         </span>
         <div class="ltx_para" id="I4.i4.p1">
          <p class="ltx_p">
           If
           H
           is not proven, compare DCS trees of
           T
           and
           H
           , and generate path alignments.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i5" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          5.
         </span>
         <div class="ltx_para" id="I4.i5.p1">
          <p class="ltx_p">
           Aligned paths are evaluated by a similarity score to estimate
their likelihood of being paraphrases. Path alignments with scores
higher than a threshold are accepted.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i6" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          6.
         </span>
         <div class="ltx_para" id="I4.i6.p1">
          <p class="ltx_p">
           Convert accepted path alignments into statements on
abstract denotations, use them in logical inference as new
knowledge, and try to prove
           H
           again.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Generating path alignments
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         On-the-fly knowledge is generated by aligning paths in DCS trees.
A path is considered as joining two
         germs
         in a DCS tree, where a
         germ
         is defined
as a specific semantic role of a node. For example, Figure
         5
         shows DCS
trees of the following sentences (a simplified pair from RTE2-dev):
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         T:
         Tropical storm Debby is blamed for deaths.
         H:
         A storm has caused loss of life.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         The germ
         𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)
         and
germ
         𝙰𝚁𝙶⁢(𝐝𝐞𝐚𝐭𝐡)
         in DCS tree of
         T
         are joined by the
underscored path. Two paths are aligned if the joined germs are aligned,
and we impose constraints on aligned germs to inhibit meaningless alignments,
as described below.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Aligning germs by logical clues
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Two germs are aligned if they are both at leaf nodes (e.g.
         𝙰𝚁𝙶⁢(𝐝𝐞𝐚𝐭𝐡)
         in
         T
         and
         𝙰𝚁𝙶⁢(𝐥𝐢𝐟𝐞)
         in
         H
         ,
Figure
         5
         ),
or they already have part of their meanings in common, by some logical clues.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         To formulate this properly, we define the abstract denotation of a germ, which,
intuitively, represents the meaning of the germ in the specific sentence.
The abstract denotation of a germ is defined in a top-down manner:
for the root node
         ρ
         of a DCS tree
         𝒯
         ,
we define its denotation
         [[ρ]]𝒯
         as the denotation
of the entire tree
         [[𝒯]]
         ; for a non-root node
         τ
         and its
parent node
         σ
         , let the edge
         (σ,τ)
         be labeled by semantic roles
         (r,r′)
         , then define
        </p>
        [[τ]]𝒯=[[𝒯τ]]∩(ιr′⁢(πr⁢([[σ]]𝒯))×WRτ∖r′).
        <p class="ltx_p">
         Now for a germ
         r⁢(σ)
         , the denotation is defined as the projection of the denotation of
node
         σ
         onto the specific semantic role
         r
         :
         [[r⁢(σ)]]𝒯=πr⁢([[σ]]𝒯)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         For example, the abstract denotation of germ
         𝙰𝚁𝙶⁢(𝐛𝐨𝐨𝐤)
         in
Figure
         1
         is defined as
         π𝙰𝚁𝙶⁢(𝐛𝐨𝐨𝐤∩π𝙾𝙱𝙹⁢(𝐫𝐞𝐚𝐝∩(𝐬𝐭𝐮𝐝𝐞𝐧𝐭𝚂𝚄𝙱𝙹×𝐛𝐨𝐨𝐤𝙾𝙱𝙹)))
         ,
meaning “
         books read by students
         ”.
Similarly, denotation of germ
         𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)
         in
         T
         of
Figure
         5
         indicates the object of “
         blame
         ” as in the sentence
“
         Tropical storm Debby is blamed for death
         ”, which is a
         tropical storm
         ,
is
         Debby
         , etc.
Technically, each germ in a DCS tree indicates a variable when the DCS tree is translated to
a FOL formula, and the abstract denotation of the germ corresponds to the set of
         consistent values
         []
         of that variable.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         The logical clue to align germs is: if there exists an abstract denotation, other than
         W
         , that is a superset of both abstract denotations of two germs, then the two germs
can be aligned. A simple example is that
         𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)
         in
         T
         can be aligned to
         𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)
         in
         H
         , because their denotations have a common
superset other than
         W
         , namely
         π𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)
         .
A more complicated example
is that
         𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)
         and
         𝚂𝚄𝙱𝙹⁢(𝐜𝐚𝐮𝐬𝐞)
         can be aligned, because inference can
induce
         [[𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)]]𝐓
         =
         [[𝙰𝚁𝙶⁢(𝐃𝐞𝐛𝐛𝐲)]]𝐓
         =
         [[𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)]]𝐓
         ,
as well as
         [[𝚂𝚄𝙱𝙹⁢(𝐜𝐚𝐮𝐬𝐞)]]𝐇
         =
         [[𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)]]𝐇
         ,
so they also have the common superset
         π𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)
         .
However, for example, logical clues can avoid aligning
         𝙰𝚁𝙶⁢(𝐬𝐭𝐨𝐫𝐦)
         to
         𝙰𝚁𝙶⁢(𝐥𝐨𝐬𝐬)
         , which
is obviously meaningless.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Scoring path alignments by similarity
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Aligned paths are evaluated by a similarity score, for which we use
distributional similarity of the words that appear in the paths (§
         4.1
         ).
Only path alignments with high similarity scores can be accepted.
Also, we only accept paths of length
         ≤5
         , to prevent too long paths to be aligned.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Applying path alignments
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         Accepted aligned paths are converted into statements, which are used as
new knowledge. The conversion is done by first performing a DCS tree transformation
according to the aligned paths, and then declare a subsumption relation between the
denotations of aligned germs.
For example, to apply the aligned path pair generated in Figure
         5
         , we use it
to transform
         T
         into a new tree
         T’
         (Figure
         6
         ), and then the aligned germs,
         OBJ
         (
         blame
         ) in
         T
         and
         SUBJ
         (
         cause
         ) in
         T’
         , will
generate the on-the-fly knowledge:
         [[𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)]]𝐓
         ⊂
         [[𝚂𝚄𝙱𝙹⁢(𝐜𝐚𝐮𝐬𝐞)]]T’
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         Similar to the tree transformation based approach to RTE
         []
         ,
this process can also utilize lexical-syntactic entailment rules
         []
         .
Furthermore, since the on-the-fly knowledge is generated by transformed
pairs of DCS trees, all contexts are preserved: in Figure
         6
         ,
though the tree transformation can be seen as generated from the entailment rule
“
         X is blamed for death → X causes loss of life
         ”, the generated
on-the-fly knowledge, as shown above the trees, only fires with the additional
condition that
         X
         is a
         tropical storm
         and is
         Debby
         . Hence, the
process can also be used to generate
knowledge from context sensitive rules
         []
         , which are known to have higher quality
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p3">
        <p class="ltx_p">
         However, it should be noted that using on-the-fly knowledge in logical inference is not a
trivial task. For example, the FOL formula of
the rule “
         X is blamed for death → X causes loss of life
         ” is:
        </p>
        ∀x;(∃a;b⁢l⁢a⁢m⁢e⁢(x,a)⁢&amp;⁢d⁢e⁢a⁢t⁢h⁢(a))→(∃b,c;c⁢a⁢u⁢s⁢e⁢(x,b)⁢&amp;⁢l⁢o⁢s⁢s⁢(b,c)⁢&amp;⁢l⁢i⁢f⁢e⁢(c)),
        <p class="ltx_p">
         which is not a horn clause. The FOL formula for the context-preserved rule in
Figure
         6
         is even more involved. Still, it can be efficiently treated by our inference engine because
as a statement, the formula
         [[𝙾𝙱𝙹⁢(𝐛𝐥𝐚𝐦𝐞)]]𝐓
         ⊂
         [[𝚂𝚄𝙱𝙹⁢(𝐜𝐚𝐮𝐬𝐞)]]T’
         is an atomic sentence,
more than a horn clause.
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
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section, we evaluate our system on FraCaS (§
        4.2
        ) and
PASCAL RTE datasets (§
        4.3
        ).
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Language Resources
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         The lexical knowledge we use are synonyms, hypernyms and
antonyms extracted from WordNet
         .
We also add axioms on named entities,
stopwords, numerics and superlatives. For example, named entities
are singletons, so we add axioms such as
         ∀x;(x⊂𝐓𝐨𝐦&amp;x≠∅)→𝐓𝐨𝐦⊂x
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         To calculate the similarity scores of path alignments, we use the sum of
word vectors of the words from each path, and calculate the cosine similarity.
For example, the similarity score of the path alignment
“
         OBJ
         (
         blame
         )
         IOBJ
         -
         ARG
         (
         death
         )
         ≈
         SUBJ
         (
         cause
         )
         OBJ
         -
         ARG
         (
         loss
         )
         MOD
         -
         ARG
         (
         life
         )” is calculated as the cosine similarity of vectors
         blame
         +
         death
         and
         cause
         +
         loss
         +
         life
         .
Other structures in the paths, such as semantic roles, are ignored in the calculation.
The word vectors we use are from
         (
         Mikolov13
         ),
and additional results are also shown using
         (
         Turian10
         ).
The threshold for accepted path alignments is set to
         0.4
         ,
based on pre-experiments on RTE development sets.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Experiments on FraCaS
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         The FraCaS test suite contains 346 inference problems divided into 9 sections, each focused on a category of semantic phenomena. We use the data by
         , and experiment on the first section,
         Quantifiers
         , following
         .
This section has 44 single premise and 30 multi premise problems.
Most of the problems do not require lexical knowledge, so we use our primary textual
inference system without on-the-fly knowledge nor WordNet, to test the performance
of the DCS framework as formal semantics. To obtain the three-valued output (i.e.
         yes
         ,
         no
         , and
         unknown
         ), we output “
         yes
         ” if
         H
         is proven, or try to
prove the negation of
         H
         if
         H
         is not proven. To negate
         H
         , we use the root
negation as described in §
         2.5
         . If the negation of
         H
         is proven, we
output “
         no
         ”, otherwise we output “
         unknown
         ”.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         The result is shown in Table
         4
         . Since
our system uses an off-the-shelf dependency parser, and semantic representations are obtained
from simple rule-based conversion from dependency trees, there will be only one (right or wrong) interpretation in face of ambiguous sentences.
Still, our system outperforms
         ’s probabilistic CCG-parser.
Compared to
         and
         ,
our system does not need a pre-trained alignment model,
and it improves by making multi-sentence inferences.
To sum up, the result shows that DCS is good at handling universal quantifiers and negations.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         Most errors are due to wrongly generated DCS trees (e.g. wrongly assigned semantic roles) or
unimplemented quantifier triggers (e.g. “
         neither
         ”) or generalized quantifiers
(e.g. “
         at least a few
         ”). These could be addressed by future work.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Experiments on PASCAL RTE datasets
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         On PASCAL RTE datasets, strict logical inference is known to have very low recall
         []
         ,
so on-the-fly knowledge is crucial in this setting. We test the effect of on-the-fly knowledge
on RTE2, RTE3, RTE4 and RTE5 datasets, and compare our system with other approaches.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.1
         </span>
         Impact of on-the-fly knowledge
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS1.p1">
         <p class="ltx_p">
          Results on test data are shown in Table
          5
          . When only
primary knowledge is used in inference (the first row), recalls are actually very low; After
we activate the on-the-fly knowledge, recalls jump to over 50%, with a moderate fall of precision.
As a result, accuracies significantly increase.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.2
         </span>
         Comparison to other RTE systems
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS2.p1">
         <p class="ltx_p">
          A comparison between our system and other RTE systems is shown in Table
          6
          .
Bos06
          []
          is a hybrid system combining deep features from a theorem prover and a model
builder, together with shallow features such as lexical overlap and text length. MacCartney08
          []
          uses natural logic to calculate inference relations between two superficially
aligned sentences.
Clark08
          []
          is a logic-based system utilizing various resources including WordNet and
DIRT paraphrases
          []
          , and is tolerant to partially unproven
          H
          sentences in some degree.
All of the three systems pursue a logical approach, while combining various techniques to achieve robustness.
The result shows that our system has comparable performance. On the other hand, Wang10
          []
          learns a tree-edit model from training data, and captures entailment relation by tree edit distance.
Stern11
          []
          and Stern12
          []
          extend this framework to utilize entailment
rules as tree transformations. These are more tailored systems using machine learning with many
handcrafted features. Still, our unsupervised system outperforms the state-of-the-art on RTE5 dataset.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.3
         </span>
         Analysis
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS3.p1">
         <p class="ltx_p">
          Summing up test data from RTE2 to RTE5, Figure
          7
          shows the proportion of
all proven pairs and their precision. Less than 5% pairs can be proven primarily,
with a precision of 77%. Over 40%
pairs can be proven by one piece of on-the-fly knowledge, yet pairs do exist
in which more than 2 pieces are necessary.
The precisions of 1 and 2 pieces on-the-fly knowledge application are over 60%, which is fairly
high, given our rough estimation of the similarity score. As a comparison,
          studied the proportion of proven pairs
and precision by applying DIRT rules to tree skeletons in RTE2 and RTE3 data. The proportion
is 8% with precision 65% on RTE2, and proportion 6% with precision 72% on RTE3. Applied
by our logical system, the noisy on-the-fly knowledge can achieve a precision comparable to higher
quality resources such as DIRT.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS3.p2">
         <p class="ltx_p">
          A major type of error is caused by the ignorance of semantic roles in calculation of
similarity scores. For example, though “
          Italy beats Kazakhstan
          ” is not primarily proven
from “
          Italy is defeated by Kazakhstan
          ”, our system does produce the path alignment
“
          SUBJ
          (
          beat
          )
          OBJ
          ≈
          OBJ
          (
          defeat
          )
          SUBJ
          ” with a high similarity score.
The impact of such errors depends on the data making methodology, though. It lowers
precisions in RTE2 and RTE3 data, particularly in “IE” subtask (where precisions drop under
          0.5
          ).
On the other hand, it occurs less often in “IR” subtask.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS3.p3">
         <p class="ltx_p">
          Finally, to see if we “get lucky” on RTE5 data in the choice of word vectors
and thresholds, we change the thresholds from
          0.1
          to
          0.7
          and draw the precision-recall curve,
using two types of word vectors,
          Mikolov13
          and
          Turian10
          . As shown in
Figure
          8
          , though the precision drops for
          Turian10
          , both curves
show the pattern that our system keeps gaining recall while maintaining precision to a certain level.
Not too much “magic” in
          Mikolov13
          actually: for over 80% pairs, every node in DCS
tree of
          H
          can be covered by a path of length
          ≤5
          that has a corresponding path of length
          ≤5
          in
          T
          with a similarity score
          &gt;0.4
          .
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
