<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Polynomial Time Joint Structural Inference for Sentence Compression.
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
       We propose two polynomial time inference algorithms to compress sentences under bigram and dependency-factored objectives. The first algorithm is exact and requires
       O⁢(n6)
       running time. It extends Eisner’s cubic time parsing algorithm by using virtual dependency arcs to link deleted words. Two signatures are added to each span, indicating the number of deleted words and the rightmost kept word within the span. The second algorithm is a fast approximation of the first one. It relaxes the compression ratio constraint using Lagrangian relaxation, and thereby requires
       O⁢(n4)
       running time. Experimental results on the popular sentence compression corpus demonstrate the effectiveness and efficiency of our proposed approach.
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
        Sentence compression aims to shorten a sentence by removing uninformative words to reduce reading time.
It has been widely used in compressive summarization
        [9, 8, 10, 3, 15]
        .
To make the compressed sentence readable, some techniques consider the n-gram language models of the compressed sentence
        [4, 12]
        .
Recent studies used a subtree deletion model for compression
        [1, 13, 15]
        ,
which deletes a word only if its modifier in the parse tree is deleted.
Despite its empirical success, such a model fails to generate compressions that are not subject to the subtree constraint (see Figure
        1
        ).
In fact, we parsed the Edinburgh sentence compression corpus using the MSTparser
        ,
and found that
        2561
        of
        5379
        sentences (
        47.6⁢%
        ) do not satisfy the subtree deletion model.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Methods beyond the subtree model are also explored.
Trevor et al. proposed synchronous tree substitution grammar
        [5]
        , which allows local distortion of the tree topology and can thus naturally capture structural mismatches.
        [7, 17]
        proposed the joint compression model,
which simultaneously considers the n-gram model and dependency parse tree of the compressed sentence.
However, the time complexity greatly increases since the parse tree dynamically depends on the compression.
They used Integer Linear Programming (ILP) for inference which requires exponential running time in the worst case.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we propose a new exact decoding algorithm for the joint model using dynamic programming.
Our method extends Eisner’s cubic time parsing algorithm by adding signatures to each span,
which indicate the number of deleted words and the rightmost kept word within the span,
resulting in
        O⁢(n6)
        time complexity and
        O⁢(n4)
        space complexity.
We further propose a faster approximate algorithm based on Lagrangian relaxation, which has
        T⁢O⁢(n4)
        running time and
        O⁢(n3)
        space complexity (
        T
        is the iteration number in the subgradient decent algorithm).
Experiments on the popular Edinburgh dataset show that the proposed approach is 10 times faster than a high-performance commercial ILP solver.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Task Definition
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We define the sentence compression task as:
given a sentence composed of
        n
        words,
        𝐱=x1,…,xn
        , and a length
        L≤n
        ,
we need to remove
        (n-L)
        words from
        𝐱
        , so that the sum of the weights of the dependency tree and word bigrams of the remaining part is maximized.
Formally, we solve the following optimization problem:
       </p>
       <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S2.Ex1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          max𝐳,𝐲
         </td>
         <td class="ltx_td ltx_align_center">
         </td>
         <td class="ltx_td ltx_align_left">
          ∑iwitok⁢zi+∑i,jwi⁢jdep⁢zi⁢zj⁢yi⁢j
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="2">
          <span class="ltx_tag ltx_tag_equation">
           (1)
          </span>
         </td>
        </tr>
        <tr class="ltx_align_baseline">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_center">
         </td>
         <td class="ltx_td ltx_align_left">
          +∑i&lt;jwi⁢jbgr⁢zi⁢zj⁢∏i&lt;k&lt;j(1-zk)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S2.Ex4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          s.t.
         </td>
         <td class="ltx_td ltx_align_center">
         </td>
         <td class="ltx_td ltx_align_left">
          𝐳⁢ is binary ,∑izi=L
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
         </td>
         <td class="ltx_td ltx_align_left">
          𝐲⁢ is a projective parse tree over the
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
         </td>
         <td class="ltx_td ltx_align_left">
          ⁢subgraph: ⁢{xi|zi=1}
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        𝐳
        is a binary vector,
        zi
        indicates
        xi
        is kept or not.
        𝐲
        is a square matrix denoting the projective dependency parse tree over the remaining words,
        yi⁢j
        indicates if
        xi
        is the head of
        xj
        (note that each word has exactly one head).
        witok
        is the informativeness of
        xi
        ,
        wi⁢jbgr
        is the score of bigram
        xi⁢xj
        in an n-gram model,
        wdep
        is the score of dependency arc
        xi→xj
        in an arc-factored dependency parsing model.
Hence, the first part of the objective function is the total score of the kept words, the second and third parts are the scores of the parse tree and bigrams of the compressed sentence,
        zi⁢zj⁢∏i&lt;k&lt;j(1-zk)=1
        indicates both
        xi
        and
        xj
        are kept, and are adjacent after compression. A graph illustration of the objective function is shown in Figure
        2
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Proposed Method
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Eisner’s Cubic Time Parsing Algorithm
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Throughout the paper, we assume that all the parse trees are projective. Our method is a generalization of Eisner’s dynamic programming algorithm
         [6]
         , where two types of structures are used in each iteration, incomplete spans and complete spans. A span is a subtree over a number of consecutive words, with the leftmost or the rightmost word as its root. An incomplete span denoted as
         Iji
         is a subtree inside a single arc
         xi→xj
         , with root
         xi
         .
A complete span is denoted as
         Cji
         , where
         xi
         is the root of the subtree, and
         xj
         is the furthest descendant of
         xi
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Eisner’s algorithm searches the optimal tree in a bottom up order. In each step, it merges two adjacent spans into a larger one.
There are two rules for merging spans: one merges two complete spans into an incomplete span, the other merges an incomplete span and a complete span into a large complete span.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Exact
        O⁢(n6)
        Time Algorithm
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         First we consider an easy case, where the bigram scores
         wi⁢jbgr
         in the objective function are ignored.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         The scores of unigrams
         witok
         can be transfered to the dependency arcs, so that we can remove all linear terms
         witok⁢zi
         from the objective function. That is:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           ∑iwitok⁢zi+∑i,jwi⁢jdep⁢zi⁢zj⁢yi⁢j
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
           ∑i,j(wi⁢jdep+wjtok)⁢zi⁢zj⁢yi⁢j
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         This can be easily verifed.
If
         zj=0
         , then in both equations, all terms having
         zj
         are zero;
If
         zj=1
         , i.e.,
         xj
         is kept, since it has exactly one head word
         xk
         in the compressed sentence, the sum of the terms having
         zj
         is
         wjtok+wk⁢jdep
         for both equations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Therefore, we only need to consider the scores of arcs. For any compressed sentence, we could augment its dependency tree by adding a virtual arc
         i-1→i
         for each deleted word
         xi
         .
If the first word
         x1
         is deleted, we connect it to the root of the parse tree
         x0
         , as shown in Figure
         3
         .
In this way, we derive a full parse tree of the original sentence.
This is a one-to-one mapping. We can reversely get the the compressed parse tree by removing all virtual arcs from the full parse tree.
We restrict the score of all the virtual arcs to be zero, so that scores of the two parse trees are equivalent.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Now the problem is to search the optimal full parse tree with
         n-L
         virtual arcs.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <p class="ltx_p">
         We modify Eisner’s algorithm by adding a signature to each span indicating the number of virtual arcs within the span.
Let
         Iji⁢(k)
         and
         Cji⁢(k)
         denote the incomplete and complete spans with
         k
         virtual arcs respectively.
When merging two spans, there are 4 cases, as shown in Figure
         4
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Case 1
            Link two complete spans by a virtual arc :
            Ii+1i⁢(1)=Cii⁢(0)+Ci+1i+1⁢(0)
            .
           </p>
          </div>
          <div class="ltx_para" id="I1.i1.p2">
           <p class="ltx_p">
            The two complete spans must be single words, as the length of the virtual arc is 1.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Case 2
            Link two complete spans by a non-virtual arc:
            Iji⁢(k)=Cri⁢(k′)+Cr+1j⁢(k′′),k′+k′′=k
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
            Case 3
            Merge an incomplete span and a complete span. The incomplete span is covered by a virtual arc:
            Iji⁢(j-i)=Ii+1i⁢(1)+Cji+1⁢(j-i-1)
            .
The number of the virtual arcs within
            Cji+1
            must be
            j-i-1
            , since the descendants of the modifier of a virtual arc
            xj
            must be removed.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i4.p1">
           <p class="ltx_p">
            Case 4
            Merge an incomplete span and a complete span. The incomplete span is covered by a non-virtual arc:
            Cji⁢(k)=Iri⁢(k′)+Cjr⁢(k′′),k′+k′′=k
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         The score of the new span is the sum of the two spans.
For case 2, the weight of the dependency arc
         i→j
         ,
         wi⁢jdep
         is also added to the final score.
The root node is allowed to have two modifiers: one is the modifier in the compressed sentence, the other is the first word if it is removed.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p8">
        <p class="ltx_p">
         For each combination, the algorithm enumerates the number of virtual arcs in the left and right spans, and the split position
(e.g.,
         k′,k′′,r
         in case 2),
thus it takes
         O⁢(n3)
         running time.
The overall time complexity is
         O⁢(n5)
         and the space complexity is
         O⁢(n3)
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p9">
        <p class="ltx_p">
         Next, we consider the bigram scores. The following proposition is obvious.
        </p>
       </div>
       <div class="ltx_theorem ltx_theorem_theorem" id="Thmtheorem1">
        <h6 class="ltx_title ltx_runin ltx_font_bold ltx_title_theorem">
         <span class="ltx_tag ltx_tag_theorem">
          Proposition 1
         </span>
         .
        </h6>
        <div class="ltx_para" id="Thmtheorem1.p1">
         <p class="ltx_p">
          For any right-headed span Iji or Cji, i&gt;j, words xi,xj must be kept.
         </p>
        </div>
       </div>
       <div class="ltx_proof">
        <h6 class="ltx_title ltx_runin ltx_font_italic ltx_title_proof">
         Proof.
        </h6>
        <div class="ltx_para" id="S3.SS2.p10">
         <p class="ltx_p">
          Suppose
          xj
          is removed, there must be a virtual arc
          j-1→j
          which is a conflict with the fact that
          xj
          is the leftmost word.
As
          xj
          is a descendant of
          xi
          ,
          xi
          must be kept.
∎
         </p>
        </div>
       </div>
       <div class="ltx_para" id="S3.SS2.p11">
        <p class="ltx_p">
         When merging two spans, a new bigram is created, which connects the rightmost kept words in the left span and the leftmost kept word in the right span.
According to the proposition above, if the right span is right-headed, its leftmost word is kept.
If the right span is left-headed, there are two cases: its leftmost word is kept, or no word in the span is kept. In any case, we only need to consider the leftmost word in the right span.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p12">
        <p class="ltx_p">
         Let
         Iji⁢(k,p)
         and
         Cji⁢(k,p)
         denote the single and complete span with
         k
         virtual arcs and the rightmost kept word
         xp
         . According to the proposition above, we have, for any right-headed span
         p=i
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p13">
        <p class="ltx_p">
         We slightly modify the two merging rules above, and obtain:
        </p>
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            Case 2’
            Link two complete spans by a non-virtual arc:
            Iji⁢(k,j)=Cri⁢(k′,p)+Cr+1j⁢(k′′,j),k′+k′′=k
            .
The score of the new span is the sum of the two spans plus
            wi⁢jdep+wp,r+1bgr
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            Case 4’
            Merge an incomplete span and a complete span. The incomplete span is covered by a non-virtual arc.
For left-headed spans, the rule is
            Cji⁢(k,q)=Iri⁢(k′,p)+Cjr⁢(k′′,q),k′+k′′=k
            ,
and the score of the new span is the sum of the two spans plus
            wp⁢rbgr
            ;
for right-headed spans, the rule is
            Cji⁢(k,i)=Iri⁢(k′,i)+Cjr⁢(k′′,r)
            , and the score of the new span is the sum of the two spans.
           </p>
          </div>
         </li>
        </ul>
        <p class="ltx_p">
         The modified algorithm requires
         O⁢(n6)
         running time and
         O⁢(n4)
         space complexity.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Approximate
        O⁢(n4)
        Time Algorithm
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         In this section, we propose an approximate algorithm where the length constraint
         ∑izi=L
         is relaxed by Lagrangian Relaxation. The relaxed version of Problem (
         1
         ) is
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           minλ⁡max𝐳,𝐲
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           ∑iwitok⁢zi+∑i,jwi⁢jdep⁢zi⁢zj⁢yi⁢j
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="3">
           <span class="ltx_tag ltx_tag_equation">
            (2)
           </span>
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           +∑i&lt;jwi⁢jbgr⁢zi⁢zj⁢∏i&lt;k&lt;j(1-zk)
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
          </td>
          <td class="ltx_td ltx_align_left">
           +λ⁢(∑izi-L)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex11">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           s.t.
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           𝐳⁢ is binary
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
          </td>
          <td class="ltx_td ltx_align_left">
           𝐲⁢ is a projective parse tree over the
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
          </td>
          <td class="ltx_td ltx_align_left">
           ⁢subgraph: ⁢{xi|zi=1}
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Fixing
         λ
         , the optimal
         𝐳,𝐲
         can be found using a simpler version of the algorithm above.
We drop the signature of the virtual arc number from each span, and thus obtain an
         O⁢(n4)
         time algorithm.
Space complexity is
         O⁢(n3)
         . Fixing
         𝐳,𝐲
         , the dual variable is updated by
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx4">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex12">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           λ=λ+α⁢(L-∑izi)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         α&gt;0
         is the learning rate. In this paper, our choice of
         α
         is the same as
         [16]
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
       Experiments
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Data and Settings
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We evaluate our method on the data set from
         [4]
         . It includes 82 newswire articles with manually produced compression for each sentence. We use the same partitions as
         [10]
         , i.e., 1,188 sentences for training and 441 for testing.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Our model is discriminative – the scores of the unigrams, bigrams and dependency arcs are the linear functions of features,
that is,
         witok=𝐯T⁢𝐟⁢(xi)
         , where
         𝐟
         is the feature vector of
         xi
         , and
         𝐯
         is the weight vector of features. The learning task is to estimate the feature weight vector based on the manually compressed sentences.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         We run a second order dependency parser trained on the English Penn Treebank corpus to generate the parse trees of the compressed sentences. Then we augment these parse trees by adding virtual arcs and get the full parse trees of their corresponding original sentences. In this way, the annoation is transformed into a set of sentences with their augmented parse trees. The learning task is similar to training a parser. We run a CRF based POS tagger to generate POS related features.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         We adopt the compression evaluation metric as used in
         [10]
         that measures the macro F-measure for the retained unigrams (
         Fu⁢g⁢r
         ),
and the one used in
         [4]
         that calculates the F1 score of the grammatical relations labeled by RASP
         [2]
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         We compare our method with other 4 state-of-the-art systems. The first is linear chain CRFs, where the compression task is casted as a binary sequence labeling problem. It usually achieves high unigram F1 score but low grammatical relation F1 score since it only considers the local interdependence between adjacent words. The second is the subtree deletion model
         [1]
         which is solved by integer linear programming (ILP)
         . The third one is the bigram model proposed by McDonald
         [12]
         which adopts dynamic programming for efficient inference. The last one jointly infers tree structures alongside bigrams using ILP
         [17]
         . For fair comparison, systems were restricted to produce compressions that matched their average gold compression rate if possible.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Features
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Three types of features are used to learn our model: unigram features, bigram features and dependency features, as shown in Table
         1
         .
We also use the in-between features proposed by
         [11]
         , which were shown to be very effective for dependency parsing.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We show the comparison results in Table
         2
         .
As expected, the joint models (ours and TM13) consistently outperform the subtree deletion model,
since the joint models do not suffer from the subtree restriction.
They also outperform McDonald’s, demonstrating the effectiveness of considering the grammar structure for compression.
It is not surprising that CRFs achieve high unigram F scores but low syntactic F scores as they do not consider the fluency of the compressed sentence.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         Compared with TM13’s system, our model with exact decoding is not significantly faster due to the high order of the time complexity.
On the other hand, our approximate approach is much more efficient, about 10 times faster than TM13’ system,
and achieves competitive accuracy with the exact approach.
Note that it is worth pointing out that the exact approach can output compressed sentences of all lengths,
whereas the approximate method can only output one sentence at a specific compression rate.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
