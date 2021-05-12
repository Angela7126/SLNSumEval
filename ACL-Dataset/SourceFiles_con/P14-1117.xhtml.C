<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Approximation Strategies for Multi-Structure Sentence Compression.
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
       Sentence compression has been shown to benefit from
joint inference involving both n-gram and dependency-factored objectives
but this typically requires expensive integer programming.
We explore instead the use of Lagrangian relaxation
to decouple the two subproblems and solve them separately.
While dynamic programming is viable for bigram-based sentence compression,
finding optimal compressed trees within graphs is NP-hard.
We recover approximate solutions to this problem using
LP relaxation and maximum spanning tree algorithms, yielding
techniques that can be combined with the efficient
bigram-based inference approach using Lagrange multipliers.
Experiments show that these approximation strategies produce results
comparable to a state-of-the-art integer linear programming formulation
for the same joint inference task along with a significant improvement
in runtime.
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
        Sentence compression is a text-to-text generation task
in which an input sentence must be transformed into a shorter
output sentence which accurately reflects the meaning in the input
and also remains grammatically well-formed.
The compression task has received increasing attention in recent years, in
part due to the availability of datasets such as the
Ziff-Davis corpus
        [24]
        and the Edinburgh compression
corpora
        [5]
        , from which the following example is
drawn.
       </p>
       <table class="ltx_tabular ltx_align_middle">
        <tbody class="ltx_tbody">
         <tr class="ltx_tr">
          <td class="ltx_td ltx_align_justify" style="width:210.0pt;" width="210.0pt">
           Original: In 1967 Chapman, who had cultivated a
conventional image with his ubiquitous tweed jacket and pipe, by his own
later admission stunned a party attended by his friends and future Python
colleagues by coming out as a homosexual.
          </td>
         </tr>
         <tr class="ltx_tr">
          <td class="ltx_td ltx_align_justify" style="width:210.0pt;" width="210.0pt">
           Compressed: In 1967 Chapman, who had cultivated a
conventional image, stunned a party by coming out as a homosexual.
          </td>
         </tr>
        </tbody>
       </table>
       Following an assumption often used in compression systems,
the compressed output in this corpus
is constructed by dropping tokens from the input sentence without any
paraphrasing or reordering.
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        A number of diverse approaches have been proposed for deletion-based
sentence compression, including techniques that assemble the output
text under an n-gram factorization over the input
text
        [36, 7]
        or an arc factorization over input dependency
parses
        [16, 17, 15]
        . Joint methods have also been
proposed that invoke integer linear programming (ILP) formulations to
simultaneously consider multiple structural inference
problems—both over n-grams and input dependencies
        [34]
        or n-grams and all possible dependencies
        [45]
        .
However, it is well-established that the utility of
ILP for optimal inference in structured problems
is often outweighed by the worst-case performance of ILP solvers on
large problems without unique integral solutions. Furthermore,
approximate solutions can often be adequate for real-world
generation systems, particularly in the
presence of linguistically-motivated constraints such as those
described by
        Clarke and Lapata (2008)
        , or domain-specific pruning strategies
such as the use of sentence templates to constrain the output.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this work, we develop approximate inference strategies to
the joint approach of
        Thadani and McKeown (2013)
        which trade the optimality
guarantees of exact ILP for faster inference by separately solving
the n-gram and dependency subproblems and using
Lagrange multipliers to enforce consistency between their solutions.
However, while the former
problem can be solved efficiently using the dynamic programming
approach of
        McDonald (2006)
        , there are no efficient
algorithms to recover maximum
weighted non-projective subtrees in a general directed graph.
Maximum spanning tree algorithms, commonly used in non-projective
dependency parsing
        [35]
        , are not easily adaptable
to this task since the maximum-weight subtree is not necessarily a
part of the maximum spanning tree.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We therefore consider methods to recover approximate solutions for the
subproblem of finding the maximum weighted subtree in a graph, common
among which is the use of a linear programming relaxation.
This linear program (LP) appears empirically tight for
compression problems and our experiments indicate that simply using the
non-integral solutions of this LP in Lagrangian relaxation can empirically
lead to reasonable compressions.
In addition, we can recover approximate solutions to this problem by
using the Chu-Liu Edmonds algorithm for recovering
maximum spanning trees
        [4, 14]
        over the relatively sparse subgraph defined by a solution to the relaxed LP.
Our proposed approximation strategies are evaluated using automated
metrics
in order to address the question: under what conditions should
a real-world sentence compression system implementation consider
exact inference with an ILP or approximate inference?
The contributions of this work include:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           An empirically-useful technique for approximating the
maximum-weight subtree in a weighted graph using LP-relaxed inference.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Multiple approaches to generate good approximate solutions for
joint multi-structure compression, based on Lagrangian
relaxation to enforce equality between the sequential
and syntactic inference subproblems.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           An analysis of the tradeoffs incurred by joint
approaches with regard to runtime
as well as performance under automated measures.
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Multi-Structure Sentence Compression
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Even though compression is typically formulated as a token deletion task,
it is evident that dropping tokens independently from an input
sentence will likely not result in fluent and meaningful compressive text.
Tokens in well-formed sentences participate in
a number of syntactic and semantic relationships with other tokens,
so one might expect that accounting for heterogenous structural relationships
between tokens will improve the coherence of the output sentence.
Furthermore, much recent work has focused on
the challenge of joint sentence extraction and
compression, also known as
        compressive summarization
        [34, 2, 1, 30, 41]
        ,
in which questions of efficiency are paramount due to the larger
problems involved; however, these approaches largely
restrict compression to pruning parse trees, thereby
imposing a dependency on parser performance.
We focus in this work on a sentence-level compression system
to approximate the ILP-based inference of
        Thadani and McKeown (2013)
        which does not restrict compressions to follow input parses but
permits the generation of novel dependency relations in output
compressions.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        The rest of this section is organized as follows: §
        2.1
        provies an overview of the joint sequential and syntactic objective
for compression from
        Thadani and McKeown (2013)
        while §
        2.2
        discusses the use of Lagrange multipliers to enforce consistency
between the different structures considered. Following this,
§
        2.3
        discusses a dynamic program to find maximum
weight bigram subsequences from the input sentence, while
§
        2.4
        covers LP relaxation-based approaches for approximating
solutions to the problem of finding a maximum-weight subtree in
a graph of potential output dependencies.
Finally, §
        2.5
        discusses the features
and model training approach used in our experimental results which
are presented in §
        3
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Joint objective
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         We begin with some notation. For an input sentence
         S
         comprised of
         n
         tokens including duplicates, we denote the set of tokens in
         S
         by
         T≜{ti:1≤i≤n}
         . Let
         C
         represent a compression of
         S
         and let
         xi∈{0,1}
         denote an
indicator variable whose value corresponds to
whether token
         ti∈T
         is present in the compressed sentence
         C
         .
In addition, we define bigram indicator variables
         yi⁢j∈{0,1}
         to represent whether
a particular order-preserving bigram
         ⟨ti,tj⟩
         from
         S
         is present as a contiguous bigram in
         C
         as well as dependency indicator variables
         zi⁢j∈{0,1}
         corresponding to whether the dependency arc
         ti→tj
         is present in the dependency parse of
         C
         .
The score for a given compression
         C
         can now be defined to factor over
its tokens, n-grams and dependencies as follows.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           s⁢c⁢o⁢r⁢e⁢(C)
          </td>
          <td class="ltx_td ltx_align_left">
           =∑ti∈Txi⋅θtok(ti)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +∑ti∈T∪{start},tj∈T∪{end}yi⁢j⋅θbgr⁢(⟨ti,tj⟩)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +∑ti∈T∪{root},tj∈Tzi⁢j⋅θdep(ti→tj)
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
         θtok
         ,
         θbgr
         and
         θdep
         are feature-based scoring functions for tokens,
bigrams and dependencies respectively. Specifically, each
         θv⁢(⋅)≡𝐰v⊤⁢ϕv⁢(⋅)
         where
         ϕv⁢(⋅)
         is a feature map for a given
variable type
         v∈{tok, bgr, dep}
         and
         𝐰v
         is
the corresponding vector of learned parameters.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The inference task involves recovering the highest
scoring compression
         C*
         under a particular set of model parameters
         𝐰
         .
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           C*
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢maxCs⁢c⁢o⁢r⁢e⁢(C)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           =arg⁢max𝐱,𝐲,𝐳⁡𝐱⊤⁢𝜽tok+𝐲⊤⁢𝜽bgr+𝐳⊤⁢𝜽dep
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
        <p class="ltx_p">
         where the incidence vector
         𝐱≜⟨xi⟩ti∈T
         represents an
entire token configuration over
         T
         , with
         𝐲
         and
         𝐳
         defined analogously to represent configurations of bigrams and dependencies.
         𝜽v≜⟨θv⁢(⋅)⟩
         denotes a corresponding vector of scores for each variable type
         v
         under the current model parameters.
In order to recover meaningful compressions by optimizing
(
         2
         ), the inference step must ensure:
        </p>
        <ol class="ltx_enumerate" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            The configurations
            𝐱
            ,
            𝐲
            and
            𝐳
            are
            consistent
            with each other, i.e., all configurations cover
the same tokens.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            The structural configurations
            𝐲
            and
            𝐳
            are
            non-degenerate
            , i.e, the bigram configuration
            𝐲
            represents an acyclic path while the dependency configuration
            𝐳
            forms a tree.
           </p>
          </div>
         </li>
        </ol>
        <p class="ltx_p">
         These requirements naturally rule out simple approximate inference
formulations such as search-based approaches for the joint
objective.
         An ILP-based inference solution is demonstrated in
         Thadani and McKeown (2013)
         that makes use of linear constraints over the boolean variables
         xi
         ,
         yi⁢j
         and
         zi⁢j
         to guarantee consistency, as well as
auxiliary real-valued variables and constraints representing the flow of
commodities
         [31]
         in order to establish structure in
         𝐲
         and
         𝐳
         . In the following section, we propose
an alternative formulation that exploits the modularity of this
joint objective.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Lagrangian relaxation
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Dual decomposition
         [26]
         and Lagrangian relaxation in general
are often used for solving joint inference problems
which are decomposable into individual subproblems linked by
equality
constraints
         [27, 44, 43, 13, 32, 11, 1]
         .
This approach permits sub-problems to be solved separately
using problem-specific efficient algorithms, while
consistency over the structures produced is enforced through
Lagrange multipliers via iterative optimization. Exact solutions are
guaranteed when the algorithm converges on a consistent primal solution,
although this convergence itself is not guaranteed and depends on the
tightness of the underlying LP relaxation.
The primary advantage of this technique is the ability to leverage the
underlying structure of the problems in inference rather than relying on a
generic ILP formulation while still often producing exact solutions.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         The multi-structure inference problem described in the previous
section seems in many ways
to be a natural fit to such an approach since output scores factor
over different types of structure that comprise the output
compression.
Even if ILP-based approaches perform reasonably at the scale of
single-sentence compression problems, the exponential worst-case
complexity of general-purpose ILPs will inevitably pose challenges
when scaling up to (a) handle larger inputs,
(b) use higher-order structural
fragments, or (c) incorporate additional models.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         Consider once more the optimization problem characterized by
(
         2
         )
The two structural problems that need to be
solved in this formulation are
the extraction of a maximum-weight acyclic
subsequence of bigrams
         𝐲
         from the lattice of all
order-preserving bigrams from
         S
         and the recovery of a maximum-weight
directed subtree
         𝐳
         .
Let
         𝜶⁢(𝐲)∈{0,1}n
         denote the incidence vector of tokens
contained in the n-gram sequence
         𝐲
         and
         𝜷⁢(𝐳)∈{0,1}n
         denote the incidence vector of words contained in the dependency tree
         𝐳
         .
We can now rewrite the objective in (
         2
         )
while enforcing the constraint that the words contained in the
sequence
         𝐲
         are
the same as the words contained in the tree
         𝐳
         , i.e.,
         𝜶⁢(𝐲)=𝜷⁢(𝐳)
         ,
by introducing a vector of Lagrange multipliers
         𝝀∈ℝn
         .
In addition, the token configuration
         𝐱
         can be rewritten in
the form of a weighted combination of
         𝜶⁢(𝐲)
         and
         𝜷⁢(𝐳)
         to ensure its consistency with
         𝐲
         and
         𝐳
         .
This results in the following Lagrangian:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           L⁢(𝝀,𝐲,𝐳)=
          </td>
          <td class="ltx_td ltx_align_left">
           ⁢𝐲⊤⁢𝜽bgr+𝐳⊤⁢𝜽dep
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +𝜽tok⊤⁢(ψ⋅𝜶⁢(𝐲)+(1-ψ)⋅𝜷⁢(𝐳))
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +𝝀⊤⁢(𝜶⁢(𝐲)-𝜷⁢(𝐳))
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
         Finding the
         𝐲
         and
         𝐳
         that maximize
this Lagrangian above yields a dual objective, and the dual problem
corresponding to
the primal objective specified in (
         2
         ) is therefore
the minimization of this objective over the Lagrange multipliers
         𝝀
         .
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx4">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           min𝝀⁡max𝐲,𝐳⁡L⁢(𝝀,𝐲,𝐳)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           min𝝀⁡max𝐲⁡𝐲⊤⁢𝜽bgr+(𝝀+ψ⋅𝜽tok)⊤⁢𝜶⁢(𝐲)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +max𝐳⁡𝐳⊤⁢𝜽dep-(𝝀+(ψ-1)⋅𝜽tok)⊤⁢𝜷⁢(𝐳)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           =
          </td>
          <td class="ltx_td ltx_align_left">
           min𝝀⁡max𝐲⁡f⁢(𝐲,𝝀,ψ,𝜽)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +max𝐳⁡g⁢(𝐳,𝝀,ψ,𝜽)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (4)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         This can now be solved with the iterative subgradient algorithm illustrated
in Algorithm
         2.2
         .
In each iteration
         i
         , the algorithm solves for
         𝐲(i)
         and
         𝐳(i)
         under
         𝝀(i)
         , then
generates
         𝝀(i+1)
         to penalize inconsistencies between
         𝜶⁢(𝐲(i))
         and
         𝜷⁢(𝐳(i))
         .
When
         𝜶⁢(𝐲(i))=𝜷⁢(𝐳(i))
         ,
the resulting primal solution is exact, i.e.,
         𝐲(i)
         and
         𝐳(i)
         represent the optimal structures under
(
         2
         ).
Otherwise, if the algorithm starts oscillating between a few primal
solutions, the underlying LP must have a non-integral solution in
which case approximation heuristics can be employed.
         The application of this Lagrangian relaxation strategy
is contingent upon the existence of algorithms to solve the
maximization subproblems for
         f⁢(𝐲,𝝀,ψ,𝜽)
         and
         g⁢(𝐳,𝝀,ψ,𝜽)
         .
The following sections discuss our approach to these problems.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p4">
        <p class="ltx_p">
         [t]
         Subgradient-based joint inference
         [1]
         <span class="ltx_text ltx_font_bold">
          Input:
         </span>
         scores
         𝜽
         , ratio
         ψ
         ,
repetition limit
         lmax
         , iteration limit
         imax
         ,
learning rate schedule
         𝜼
         <span class="ltx_text ltx_font_bold">
          Output
         </span>
         : token configuration
         𝐱
         <span class="ltx_ERROR undefined">
          \State
         </span>
         𝝀(0)←⟨0⟩n
         <math alttext="M\leftarrow\varnothing,M_{\text{repeats}}\leftarrow\varnothing" class="ltx_Math" display="inline" id="S2.SS2.p4.m8" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             M
            </mi>
            <mo>
             ←
            </mo>
            <mi mathvariant="normal">
             ∅
            </mi>
           </mrow>
           <mo>
            ,
           </mo>
           <mrow>
            <msub>
             <mi>
              M
             </mi>
             <mtext>
              repeats
             </mtext>
            </msub>
            <mo>
             ←
            </mo>
            <mi mathvariant="normal">
             ∅
            </mi>
           </mrow>
          </mrow>
         </math>
         iteration
         i&lt;imax
         <math alttext="\hat{\mathbf{y}}\leftarrow\operatorname*{arg\,max}_{\mathbf{y}}f(\mathbf{y},%
\boldsymbol{\lambda},\psi,\boldsymbol{\theta})" class="ltx_Math" display="inline" id="S2.SS2.p4.m10" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mover accent="true">
            <mi>
             𝐲
            </mi>
            <mo stretchy="false">
             ^
            </mo>
           </mover>
           <mo>
            ←
           </mo>
           <mrow>
            <mrow>
             <msub>
              <mrow>
               <mpadded width="+1.7pt">
                <mi>
                 arg
                </mi>
               </mpadded>
               <mo>
                ⁢
               </mo>
               <mi>
                max
               </mi>
              </mrow>
              <mi>
               𝐲
              </mi>
             </msub>
             <mo>
              ⁡
             </mo>
             <mi>
              f
             </mi>
            </mrow>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mrow>
              <mi>
               𝐲
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               𝝀
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               ψ
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               𝜽
              </mi>
             </mrow>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <math alttext="\hat{\mathbf{z}}\,\leftarrow\operatorname*{arg\,max}_{\mathbf{z}}\,g(\mathbf{z%
},\boldsymbol{\lambda},\psi,\boldsymbol{\theta})" class="ltx_Math" display="inline" id="S2.SS2.p4.m11" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mpadded width="+1.7pt">
            <mover accent="true">
             <mi>
              𝐳
             </mi>
             <mo stretchy="false">
              ^
             </mo>
            </mover>
           </mpadded>
           <mo>
            ←
           </mo>
           <mrow>
            <mrow>
             <mpadded width="+1.7pt">
              <msub>
               <mrow>
                <mpadded width="+1.7pt">
                 <mi>
                  arg
                 </mi>
                </mpadded>
                <mo>
                 ⁢
                </mo>
                <mi>
                 max
                </mi>
               </mrow>
               <mi>
                𝐳
               </mi>
              </msub>
             </mpadded>
             <mo>
              ⁡
             </mo>
             <mi>
              g
             </mi>
            </mrow>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mrow>
              <mi>
               𝐳
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               𝝀
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               ψ
              </mi>
              <mo>
               ,
              </mo>
              <mi>
               𝜽
              </mi>
             </mrow>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <math alttext="\boldsymbol{\alpha}(\hat{\mathbf{y}})=\boldsymbol{\beta}(\hat{\mathbf{z}})" class="ltx_Math" display="inline" id="S2.SS2.p4.m12" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             𝜶
            </mi>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mover accent="true">
              <mi>
               𝐲
              </mi>
              <mo stretchy="false">
               ^
              </mo>
             </mover>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
           <mo>
            =
           </mo>
           <mrow>
            <mi>
             𝜷
            </mi>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mover accent="true">
              <mi>
               𝐳
              </mi>
              <mo stretchy="false">
               ^
              </mo>
             </mover>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <math alttext="\boldsymbol{\alpha}(\hat{\mathbf{y}})" class="ltx_Math" display="inline" id="S2.SS2.p4.m13" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            𝜶
           </mi>
           <mo>
            ⁢
           </mo>
           <mrow>
            <mo>
             (
            </mo>
            <mover accent="true">
             <mi>
              𝐲
             </mi>
             <mo stretchy="false">
              ^
             </mo>
            </mover>
            <mo>
             )
            </mo>
           </mrow>
          </mrow>
         </math>
         <span class="ltx_ERROR undefined">
          \If
         </span>
         𝜶⁢(𝐲^)∈M
         <math alttext="M_{\text{repeats}}\leftarrow M_{\text{repeats}}\cup\{\boldsymbol{\alpha}(\hat{%
\mathbf{y}})\}" class="ltx_Math" display="inline" id="S2.SS2.p4.m15" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             M
            </mi>
            <mtext>
             repeats
            </mtext>
           </msub>
           <mo>
            ←
           </mo>
           <mrow>
            <msub>
             <mi>
              M
             </mi>
             <mtext>
              repeats
             </mtext>
            </msub>
            <mo>
             ∪
            </mo>
            <mrow>
             <mo>
              {
             </mo>
             <mrow>
              <mi>
               𝜶
              </mi>
              <mo>
               ⁢
              </mo>
              <mrow>
               <mo>
                (
               </mo>
               <mover accent="true">
                <mi>
                 𝐲
                </mi>
                <mo stretchy="false">
                 ^
                </mo>
               </mover>
               <mo>
                )
               </mo>
              </mrow>
             </mrow>
             <mo>
              }
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <span class="ltx_ERROR undefined">
          \If
         </span>
         𝜷⁢(𝐳^)∈M
         <math alttext="M_{\text{repeats}}\leftarrow M_{\text{repeats}}\cup\{\boldsymbol{\beta}(\hat{%
\mathbf{z}})\}" class="ltx_Math" display="inline" id="S2.SS2.p4.m17" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msub>
            <mi>
             M
            </mi>
            <mtext>
             repeats
            </mtext>
           </msub>
           <mo>
            ←
           </mo>
           <mrow>
            <msub>
             <mi>
              M
             </mi>
             <mtext>
              repeats
             </mtext>
            </msub>
            <mo>
             ∪
            </mo>
            <mrow>
             <mo>
              {
             </mo>
             <mrow>
              <mi>
               𝜷
              </mi>
              <mo>
               ⁢
              </mo>
              <mrow>
               <mo>
                (
               </mo>
               <mover accent="true">
                <mi>
                 𝐳
                </mi>
                <mo stretchy="false">
                 ^
                </mo>
               </mover>
               <mo>
                )
               </mo>
              </mrow>
             </mrow>
             <mo>
              }
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <span class="ltx_ERROR undefined">
          \State
         </span>
         if
         |Mrepeats|≥lmax
         then break
         <math alttext="M\leftarrow M\cup\{\boldsymbol{\alpha}(\hat{\mathbf{y}}),\boldsymbol{\beta}(%
\hat{\mathbf{z}})\}" class="ltx_Math" display="inline" id="S2.SS2.p4.m19" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            M
           </mi>
           <mo>
            ←
           </mo>
           <mrow>
            <mi>
             M
            </mi>
            <mo>
             ∪
            </mo>
            <mrow>
             <mo>
              {
             </mo>
             <mrow>
              <mrow>
               <mi>
                𝜶
               </mi>
               <mo>
                ⁢
               </mo>
               <mrow>
                <mo>
                 (
                </mo>
                <mover accent="true">
                 <mi>
                  𝐲
                 </mi>
                 <mo stretchy="false">
                  ^
                 </mo>
                </mover>
                <mo>
                 )
                </mo>
               </mrow>
              </mrow>
              <mo>
               ,
              </mo>
              <mrow>
               <mi>
                𝜷
               </mi>
               <mo>
                ⁢
               </mo>
               <mrow>
                <mo>
                 (
                </mo>
                <mover accent="true">
                 <mi>
                  𝐳
                 </mi>
                 <mo stretchy="false">
                  ^
                 </mo>
                </mover>
                <mo>
                 )
                </mo>
               </mrow>
              </mrow>
             </mrow>
             <mo>
              }
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <math alttext="\boldsymbol{\lambda}^{(i+1)}\leftarrow\boldsymbol{\lambda}^{(i)}-\eta_{i}\left%
(\boldsymbol{\alpha}(\hat{\mathbf{y}})-\boldsymbol{\beta}(\hat{\mathbf{z}})\right)" class="ltx_Math" display="inline" id="S2.SS2.p4.m20" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <msup>
            <mi>
             𝝀
            </mi>
            <mrow>
             <mo>
              (
             </mo>
             <mrow>
              <mi>
               i
              </mi>
              <mo>
               +
              </mo>
              <mn>
               1
              </mn>
             </mrow>
             <mo>
              )
             </mo>
            </mrow>
           </msup>
           <mo>
            ←
           </mo>
           <mrow>
            <msup>
             <mi>
              𝝀
             </mi>
             <mrow>
              <mo>
               (
              </mo>
              <mi>
               i
              </mi>
              <mo>
               )
              </mo>
             </mrow>
            </msup>
            <mo>
             -
            </mo>
            <mrow>
             <msub>
              <mi>
               η
              </mi>
              <mi>
               i
              </mi>
             </msub>
             <mo>
              ⁢
             </mo>
             <mrow>
              <mo>
               (
              </mo>
              <mrow>
               <mrow>
                <mi>
                 𝜶
                </mi>
                <mo>
                 ⁢
                </mo>
                <mrow>
                 <mo>
                  (
                 </mo>
                 <mover accent="true">
                  <mi>
                   𝐲
                  </mi>
                  <mo stretchy="false">
                   ^
                  </mo>
                 </mover>
                 <mo>
                  )
                 </mo>
                </mrow>
               </mrow>
               <mo>
                -
               </mo>
               <mrow>
                <mi>
                 𝜷
                </mi>
                <mo>
                 ⁢
                </mo>
                <mrow>
                 <mo>
                  (
                 </mo>
                 <mover accent="true">
                  <mi>
                   𝐳
                  </mi>
                  <mo stretchy="false">
                   ^
                  </mo>
                 </mover>
                 <mo>
                  )
                 </mo>
                </mrow>
               </mrow>
              </mrow>
              <mo>
               )
              </mo>
             </mrow>
            </mrow>
           </mrow>
          </mrow>
         </math>
         <span class="ltx_ERROR undefined">
          \Return
         </span>
         arg⁢max𝐱∈𝐌repeats⁡s⁢c⁢o⁢r⁢e⁢(𝐱)
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Bigram subsequences
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         McDonald (2006)
         provides a Viterbi-like
dynamic programming algorithm to recover
the highest-scoring sequence of order-preserving bigrams from a
lattice, either in unconstrained form or with a specific
length constraint.
The latter requires a
dynamic programming table
         Q⁢[i]⁢[r]
         which represents the best score
for a compression of length
         r
         ending at token
         i
         . The table can
be populated using the following recurrence:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx5">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           Q⁢[i]⁢[1]
          </td>
          <td class="ltx_td ltx_align_left">
           =s⁢c⁢o⁢r⁢e⁢(S,start,i)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           Q⁢[i]⁢[r]
          </td>
          <td class="ltx_td ltx_align_left">
           =maxj&lt;i⁡Q⁢[j]⁢[r-1]+s⁢c⁢o⁢r⁢e⁢(S,i,j)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           Q⁢[i]⁢[R+1]
          </td>
          <td class="ltx_td ltx_align_left">
           =Q⁢[i]⁢[R]+s⁢c⁢o⁢r⁢e⁢(S,i,end)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         R
         is the required number of output tokens and the scoring function is
defined as
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx6">
         <tr class="ltx_equation ltx_align_baseline" id="S2.Ex13">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           s⁢c⁢o⁢r⁢e⁢(S,i,j)
          </td>
          <td class="ltx_td ltx_align_left">
           ≜θbgr⁢(⟨ti,tj⟩)+λj+ψ⋅θtok⁢(tj)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         so as to solve
         f⁢(𝐲,𝝀,ψ,𝜽)
         from (
         4
         ). This approach requires
         O⁢(n2⁢R)
         time in
order to identify the highest scoring sequence
         𝐲
         and
corresponding token configuration
         𝜶⁢(𝐲)
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Dependency subtrees
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         The maximum-weight non-projective subtree problem over general graphs is not
as easily solved.
Although the maximum
         spanning
         tree for a given token configuration
can be recovered efficiently, Figure
         1
         illustrates that
the maximum-scoring subtree is not necessarily found within it.
The problem of recovering a maximum-weight subtree in a graph has been
shown to be NP-hard even with uniform edge weights
         [29]
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p2">
        <p class="ltx_p">
         In order to produce a solution to this
subproblem, we use an LP relaxation of the relevant portion of
the ILP from
         Thadani and McKeown (2013)
         by omitting integer constraints over
the token and dependency variables in
         𝐱
         and
         𝐳
         respectively. For simplicity, however, we describe the ILP version
rather than the relaxed LP in order to motivate the constraints with their
intended purpose rather than their effect in the relaxed problem.
The objective for this LP is given by
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx7">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           max𝐱,𝐳⁡𝐱⊤⁢𝜽′tok+𝐳⊤⁢𝜽dep
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (5)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where the vector of token scores is redefined as
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx8">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           𝜽′tok≜(1-ψ)⋅𝜽tok-𝝀
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (6)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         in order to solve
         g⁢(𝐳,𝝀,ψ,𝜽)
         from (
         4
         ).
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p3">
        <p class="ltx_p">
         Linear constraints are introduced to
produce dependency structures that are close to the optimal dependency trees.
First, tokens in the solution must only be active if they
have a single active incoming dependency edge.
In addition, to avoid producing multiple disconnected subtrees,
only one dependency is permitted to attach to the
         root
         pseudo-token.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx9">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           xj-∑izi⁢j
          </td>
          <td class="ltx_td ltx_align_left">
           =0,∀tj∈T
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
           ∑jzi⁢j
          </td>
          <td class="ltx_td ltx_align_left">
           =1,ifti=root
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (8)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         In order to avoid cycles in the dependency tree,
we include additional variables to establish
         single-commodity flow
         [31]
         between all pairs of tokens. These
         γi⁢j
         variables
carry non-negative real values which must be consumed by active
tokens that they are incident to.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx10">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           γi⁢j≥0,
          </td>
          <td class="ltx_td ltx_align_left">
           ∀ti,tj∈T
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (9)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S2.E10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ∑iγi⁢j-∑kγj⁢k=xj,
          </td>
          <td class="ltx_td ltx_align_left">
           ∀tj∈T
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (10)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         These constraints ensure that cyclic structures are not possible
in the non-relaxed ILP. In addition, they serve to establish
connectivity for the dependency structure
         𝐳
         since
commodity can only originate in one location—at the pseudo-token
         root
         which has no incoming commodity variables.
However, in order to enforce these properties on the output
dependency structure,
this acyclic, connected commodity structure must constrain the activation
of the
         z
         variables.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx11">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           γi⁢j-Cmax⁢zi⁢j
          </td>
          <td class="ltx_td ltx_align_left">
           ≤0,∀ti,tj∈T
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (11)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         Cmax
         is an arbitrary upper bound on the value of
         γi⁢j
         variables.
Figure
         2
         illustrates how these commodity flow variables
constrain the output of the ILP to be a tree. However, the effect of
these constraints is diminished when solving an LP relaxation of the above
problem.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p4">
        <p class="ltx_p">
         In the LP relaxation,
         xi
         and
         zi⁢j
         are redefined as real-valued variables in
         [0,1]
         , potentially resulting
in fractional values for dependency and token indicators. As a result,
the commodity flow network is able to establish connectivity but
cannot enforce a tree structure, for instance,
directed acyclic structures are possible and token indicators
         xi
         may be partially be assigned to the solution structure. This poses
a challenge in implementing
         𝜷⁢(𝐳)
         which
is needed to recover a token configuration from the solution of this
subproblem.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p5">
        <p class="ltx_p">
         We propose two alternative solutions to address this issue in the
context of the joint inference strategy. The first is to simply
use the relaxed token configuration identified by the LP in
Algorithm
         2.2
         , i.e., to set
         𝜷⁢(𝐳~)=x~
         where
         𝐱~
         and
         𝐳~
         represent
the real-valued counterparts of the incidence vectors
         𝐱
         and
         𝐳
         . The viability of this approximation strategy
is due to the following:
        </p>
        <ul class="ltx_itemize" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            The relaxed LP is empirically fairly tight, yielding integral solutions
89% of the time on the compression datasets described
in §
            3
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            The bigram subproblem is guaranteed to return a well-formed integral
solution which obeys the imposed compression rate, so we are
assured of a source of valid—if non-optimal—solutions in
line 13 of Algorithm
            2.2
            .
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         We also consider another strategy that attempts to approximate a valid
integral solution to the dependency subproblem. In order to do this,
we first include an additional constraint in the relaxed LP which
restrict the number of tokens in the
output to a specific number of tokens
         R
         that is given by an input
compression rate.
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx12">
         <tr class="ltx_equation ltx_align_baseline" id="S2.E12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ∑ixi=R
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (12)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         The addition of this constraint to the relaxed LP reduces the rate of
integral solutions drastically—from 89% to approximately 33%—but
it serves to ensure that the resulting token configuration
         𝐱~
         has at least as many non-zero elements as
         R
         , i.e.,
there are at least as many tokens activated in the LP
solution as are required in a valid solution.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p6">
        <p class="ltx_p">
         We then construct a subgraph
         G⁢(𝐳~)
         consisting of all
dependency edges that were assigned non-zero values in the solution,
assigning to each edge a score equal to the score of that edge in the
LP as well as the score of its dependent word,
i.e., each
         zi⁢j
         in
         G⁢(𝐳~)
         is assigned a score
of
         θdep⁢(⟨ti,tj⟩)-λj+(1-ψ)⋅θtok⁢(tj)
         .
Since the
commodity flow constraints in
(
         9
         )–(
         11
         )
ensure a connected
         𝐳~
         , it is therefore possible to
recover a maximum-weight spanning tree from
         G⁢(𝐳~)
         using the Chu-Liu Edmonds algorithm
         [4, 14]
         .
         Although the runtime of this algorithm is cubic in the size of
the input graph, it is fairly speedy when
applied on relatively sparse graphs such as the solutions to the LP
described above.
The resulting spanning tree is a useful integral
approximation of
         𝐳~
         but, as mentioned previously,
may contain more nodes than
         R
         due to fractional values in
         𝐱~
         ; we therefore repeatedly prune leaves with the lowest
incoming edge weight in the current tree until exactly
         R
         nodes remain.
The resulting tree is assumed to be a reasonable approximation of the
optimal integral solution to this LP.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p7">
        <p class="ltx_p">
         The Chu-Liu Edmonds algorithm is also employed
for another purpose:
when the underlying LP for the joint inference problem is not
tight—a frequent occurrence in our compression
experiments—Algorithm
         2.2
         will not converge on a single primal solution and will instead oscillate
between solutions that are close to the dual optimum. We identify this
phenomenon by counting repeated solutions and, if they exceed some
threshold
         lmax
         with at least one repeated solution from either
subproblem, we terminate the update procedure for Lagrange multipliers
and instead attempt to identify a good solution from the repeating
ones by scoring them under (
         2
         ).
It is straightforward to recover and score a bigram configuration
         𝐲
         from a token configuration
         𝜷⁢(𝐳)
         .
However, scoring
solutions produced by the dynamic program from §
         2.3
         also
requires the score over a corresponding parse tree;
this can be recovered by constructing a dependency subgraph containing
across only the tokens that are active in
         𝜶⁢(𝐲)
         and retrieving the maximum spanning tree for that subgraph using
the Chu-Liu Edmonds algorithm.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.5
        </span>
        Learning and Features
       </h3>
       <div class="ltx_para" id="S2.SS5.p1">
        <p class="ltx_p">
         The features used in this work are largely based on the features from
         Thadani and McKeown (2013)
         .
        </p>
        <ul class="ltx_itemize" id="I4">
         <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i1.p1">
           <p class="ltx_p">
            ϕtok
            contains features for
part-of-speech (POS) tag sequences of length up to 3 around the
token, features for the dependency label of the token
conjoined with its POS, lexical features for verb stems and non-word
symbols and morphological features that identify capitalized
sequences, negations and words in parentheses.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i2.p1">
           <p class="ltx_p">
            ϕbgr
            contains features for
POS patterns in a bigram, the labels of dependency
edges incident to it, its likelihood under a
Gigaword language model (LM) and an indicator for whether it
is present in the input sentence.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I4.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I4.i3.p1">
           <p class="ltx_p">
            ϕdep
            contains features for the
probability of a dependency edge under a smoothed dependency grammar
constructed from the Penn Treebank and various conjunctions of
the following features: (a) whether the edge appears as a dependency
or ancestral relation in the input parse (b)
the directionality of the dependency (c) the label of the edge
(d) the POS tags of the tokens incident to the edge and (e) the
labels of their surrounding chunks and whether the edge remains
within the chunk.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         For the experiments in the following section, we trained models using
a variant of the structured perceptron
         [10]
         which incorporates minibatches
         [50]
         for easy parallelization and
faster convergence.
         Overfitting was avoided by averaging parameters and monitoring performance
against a held-out development set during training.
All models were trained using variants of the ILP-based inference
approach of
         Thadani and McKeown (2013)
         .
We followed
         Martins et al. (2009)
         in
using LP-relaxed inference during learning,
assuming algorithmic separability
         [28]
         for these problems.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We ran compression experiments over the newswire (NW) and
broadcast news transcription (BN) corpora compiled by
        Clarke and Lapata (2008)
        which contain gold compressions
produced by human annotators using only word deletion.
The datasets were filtered to eliminate instances with less than 2 and more
than 110 tokens for parser compatibility and divided into
training/development/test sections following the splits
from
        Clarke and Lapata (2008)
        , yielding 953/63/603 instances
for the NW corpus and 880/78/404 for the BN corpus.
Gold dependency parses were approximated
by running the Stanford dependency
parser
        over reference compressions.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Following evaluations in machine translation as well as previous work in
sentence
compression
        [47, 7, 34, 39, 45]
        ,
we evaluate system performance
using F
        1
        metrics over n-grams and dependency edges produced by parsing
system output with RASP
        [3]
        and the Stanford parser.
All ILPs and LPs were solved using
Gurobi,
        a high-performance
commercial-grade solver. Following a recent analysis of compression
evaluations
        [39]
        which revealed a strong correlation between
system compression rate and human judgments of compression quality,
we constrained all systems to produce compressed
output at a specific rate—determined by the the gold
compressions available for each instance—to ensure that the
reported differences between the systems under study are meaningful.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Systems
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We report results over the following systems grouped into three
categories of models:
tokens + n-grams, tokens + dependencies, and joint models.
        </p>
        <ul class="ltx_itemize" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            3-LM:
            A reimplementation of the unsupervised ILP
of
            Clarke and Lapata (2008)
            which infers order-preserving trigram variables
parameterized with log-likelihood under an LM and
a significance score for token variables inspired by
            Hori and Furui (2004)
            , as well as various linguistically-motivated
constraints to encourage fluency in output compressions.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            DP:
            The bigram-based dynamic program of
            McDonald (2006)
            described in §
            2.3
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i3.p1">
           <p class="ltx_p">
            LP→MST:
            An approximate inference approach
based on an LP relaxation of
            ILP-Dep
            . As discussed
in §
            2.4
            , a maximum spanning tree is recovered
from the output of the LP and greedily pruned in order to generate a
valid integral solution while observing the imposed compression rate.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i4.p1">
           <p class="ltx_p">
            ILP-Dep:
            A version of the joint ILP of
            Thadani and McKeown (2013)
            without n-gram variables and corresponding features.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i5.p1">
           <p class="ltx_p">
            DP+LP→MST:
            An approximate joint inference approach
based on Lagrangian relaxation that uses
            DP
            for the maximum
weight subsequence problem and
            LP→MST
            for the
maximum weight subtree problem.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i6.p1">
           <p class="ltx_p">
            DP+LP:
            Another Lagrangian relaxation approach that pairs
            DP
            with the non-integral solutions from an LP relaxation of the
maximum weight subtree problem (cf. §
            2.4
            ).
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i7.p1">
           <p class="ltx_p">
            ILP-Joint:
            The full ILP from
            Thadani and McKeown (2013)
            ,
which provides an upper bound on the performance of the proposed
approximation strategies.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The learning rate schedule for the Lagrangian relaxation approaches
was set as
         ηi≜τ/(τ+i)
         ,
         while the hyperparameter
         ψ
         was tuned using the development
split of each corpus.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Tables
         1
         and
         2
         summarize
the results from our compression experiments on the BN and NW corpora
respectively.
Starting with the n-gram approaches, the performance of
         3-LM
         leads us to observe that the gains of supervised learning far outweigh
the utility of higher-order
n-gram factorization, which is also responsible for a significant
increase in wall-clock time.
In contrast,
         DP
         is an order of magnitude faster than all other approaches
studied here although it is not
competitive under parse-based measures such as RASP F
         %1
         which is known
to correlate with human judgments of grammaticality
         [5]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         We were surprised by the strong performance of the dependency-based
inference techniques, which yielded results that approached the
joint model in both n-gram and parse-based measures. The exact
         ILP-Dep
         approach halves the runtime of
         ILP-Joint
         to produce compressions that have similar (although statistically
distinguishable) scores.
Approximating dependency-based inference with
         LP→MST
         yields similar performance for a further halving of runtime;
however, the performance of this approach is notably worse.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Turning to the joint approaches, the strong performance of
         ILP-Joint
         is expected; less so is the
relatively high but yet practically reasonable runtime that it requires.
We note, however, that these ILPs are solved using a highly-optimized
commercial-grade solver that can utilize all CPU cores
         while our approximation approaches are implemented as
single-processed Python code without significant effort toward optimization.
Comparing the two approximation strategies shows a clear performance
advantage for
         DP+LP
         over
         DP+LP→MST
         : the
latter approach entails slower inference due to the overhead of running
the Chu-Liu Edmonds algorithm at every dual update, and furthermore, the
error introduced by approximating an integral solution results in
a significant decrease in dependency recall.
In contrast,
         DP+LP
         directly optimizes the dual problem
by using the relaxed dependency solution to update Lagrange multipliers
and achieves the best performance on parse-based F
         1
         outside of the slower ILP approaches.
Convergence rates
also vary for these two techniques:
         DP+LP
         has a lower rate
of empirical convergence (15% on BN and 4% on NW) when compared to
         DP+LP→MST
         (19% on BN and 6% on NW).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Figure
         3
         shows the effect of input sentence length on inference
time and performance for
         ILP-Joint
         and
         DP+LP
         over the
NW test corpus.
         The timing results reveal that the approximation strategy is consistently
faster than the ILP solver.
The variation in RASP F
         1
         % with input size
indicates the viability of a hybrid approach which could balance accuracy
and speed by using
         ILP-Joint
         for smaller problems and
         DP+LP
         for larger ones.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Sentence compression is one of the better-studied text-to-text generation
problems and has been observed to play a significant role in
human summarization
        [23, 22]
        .
Most approaches to sentence compression are supervised
        [25, 42, 46, 36, 47, 18, 40, 9, 17, 19, 38, 15]
        following the release of
datasets such as the Ziff-Davis corpus
        [24]
        and the
Edinburgh compression corpora
        [5, 7]
        , although
unsupervised approaches—largely based on ILPs—have
also received consideration
        [6, 7, 16]
        .
Compression has also been used as a tool for document
summarization
        [12, 49, 6, 34, 2, 48, 1, 37, 30, 41]
        , with recent work
formulating the summarization task as joint sentence extraction and
compression and often employing ILP or Lagrangian relaxation.
Monolingual compression also faces many obstacles
common to decoding in machine translation, and
a number of approaches which have been proposed to combine
phrasal and syntactic models
        [21, 43]
        inter alia
        offer directions for future research into
compression problems.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
