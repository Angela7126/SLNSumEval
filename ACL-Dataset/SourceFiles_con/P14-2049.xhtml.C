<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improving sparse word similarity models with asymmetric measures.
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
       We show that asymmetric models based on Tversky
       [19]
       improve correlations with
human similarity judgments and nearest neighbor discovery for both
frequent and middle-rank words. In accord with Tversky’s discovery
that asymmetric similarity judgments arise when
comparing sparse and rich representations,
improvement on our two tasks can be traced to
heavily weighting the feature bias toward the rarer word
when comparing high- and mid-frequency words.
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
        A key assumption of most models of similarity
is that a similarity relation is symmetric.
This assumption is foundational for some conceptions,
such as the idea of a similarity space,
in which similarity is the inverse of distance; and it
is deeply embedded into many of the algorithms that
build on a similarity relation among objects, such
as clustering algorithms. The symmetry assumption
is not, however, universal, and it is not essential
to all applications of similarity, especially when
it comes to modeling human similarity judgments. Citing a number of empirical studies,
Tversky
        [19]
        calls symmetry
directly into question, and proposes two general models
that abandon symmetry.
The one most directly related to a large body of
word similarity work that followed is what he calls the
        ratio model
        ,
which defines
        sim⁢(a,b)
        as:
       </p>
       f⁢(A∩B)f⁢(A∩B)+α⁢f⁢(A\B)+β⁢f⁢(B\A)

(1)
       <p class="ltx_p">
        Here
        A
        and
        B
        represent feature sets for the
objects a and b respectively;
the term in the numerator is a function of
the set of shared features, a measure of similarity,
and the last two terms in the denominator measure dissimilarity:
        α
        and
        β
        are real-number weights;
when
        α≠β
        , symmetry is abandoned.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        To motivate such a measure, Tversky presents
experimental data with asymmetric similarity results,
including similarity comparisons of countries, line drawings of faces,
and letters.
Tversky shows that many similarity judgment tasks
have an inherent asymmetry; but he also
argues, following Rosch
        [17]
        , that certain
kinds of stimuli are more naturally used as foci or
standards than others.
Goldstone
        [8]
        summarizes
the results succinctly:
“Asymmetrical similarity occurs when an object with many features is judged as less similar to a sparser object than vice versa; for example, North Korea is judged to be more like China than China is [like] North Korea.”
Thus, one source of asymmetry is the comparison
of sparse and dense representations.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The relevance of such considerations to word similarity becomes clear when we
consider that for many applications, word similarity measures need to be
well-defined when comparing very frequent words with
infrequent words. To make this concrete, let us consider a word representation
in the
word-as-vector paradigm
        [11, 13]
        ,
using a dependency-based model.
Suppose we want to measure the semantic similarity
of
        boat
        , rank 682 among the nouns in the
BNC corpus studied below, which has
1057 nonzero dependency features based on 50 million words
of data, with
        dinghy
        , rank 6200,
which has only 113 nonzero features. At the level of the vector representations we are using,
these are events of very different dimensionality;
that is, there are ten times as many features in
the representation of
        boat
        as there are in the representation
of
        dinghy
        . If in Tversky/Rosch terms,
the more frequent word is also a more likely focus, then
this is exactly the kind of situation in which
asymmetric similarity judgments will arise.
Below we show that an asymmetric measure, using
        α
        and
        β
        biased in favor of the less frequent word,
greatly improves the performance of a dependency-based vector model
in capturing human similarity judgments.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Before presenting these results, it will be helpful to slightly reformulate
and slightly generalize Tversky’s ratio model. The reformulation will
allow us to directly draw the connection between the ratio model
and a set of similarity measures that have played key roles
in the similarity literature.
First, since Tversky has primarily additive
        f
        in mind, we can reformulate
        f⁢(A∩B)
        as follows
       </p>
       f⁢(A∩B)=∑f∈A∩Bwght⁢(f)

(2)
       <p class="ltx_p">
        Next, since we are interested in generalizing from sets
of features, to real-valued vectors of features,
        w1
        ,
        w2
        , we define
       </p>
       σsi⁢(w1,w2)=∑f∈w1∩w2si⁢(w1⁢[f],w2⁢[f]).

(3)
       <p class="ltx_p">
        Here
        si
        is some numerical operation on real-number feature values (
        si
        stands for
        shared information
        ).
If the operation is
        min
        and
        w1⁢[f]
        and
        w2⁢[f]
        both contain the feature weights for
        f
        , then
       </p>
       ∑f∈A∩Bwght⁢(f)⁢=σmin⁢(w1,w2)=∑f∈w1∩w2min⁢(w1⁢[f],w2⁢[f]),
       <p class="ltx_p">
        so with
        si
        set to
        min
        ,
Equation (
        3
        ) includes
Equation (
        2
        ) as a special case.
Similarly,
        σ⁢(w1,w1)
        represents the
summed feature weights of
        w1
        , and therefore,
       </p>
       f⁢(w1\w2)=σ⁢(w1,w1)-σ⁢(w1,w2)
       <p class="ltx_p">
        In this generalized form, then, (
        1
        )
becomes
       </p>
       σ⁢(w1,w2)σ⁢(w1,w2)+α⁢[σ⁢(w1,w1)-σ⁢(w1,w2)]+β⁢[σ⁢(w2,w2)-σ⁢(w1,w2)]=σ⁢(w1,w2)α⁢σ⁢(w1,w1)+β⁢σ⁢(w2,w2)+σ⁢(w1,w2)-(α+β)⁢σ⁢(w1,w2)

(4)
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Thus, if
        α+β=1
        , Tversky’s ratio model becomes simply:
       </p>
       sim⁢(w1,w2)=σ⁢(w1,w2)α⁢σ⁢(w1,w1)+(1-α)⁢σ⁢(w2,w2)

(5)
       <p class="ltx_p">
        The computational advantage of this reformulation is that the
core similarity operation
        σ⁢(w1,w2)
        is done on
what is generally only a small number of shared features,
and the
        σ⁢(wi,wi)
        calculations (which we
will call self-similarities), can be computed in advance.
Note that
        sim⁢(w1,w2)
        is
symmetric if and only if
        α=0.5
        .
When
        α&gt;0.5
        ,
        sim⁢(w1,w⁢2)
        is biased in favor of
        w1
        as the referent;
When
        α&lt;0.5
        ,
        sim⁢(w1,w⁢2)
        is biased in favor of
        w2
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Consider four similarity functions
that have played important roles in the literature on similarity:
       </p>
       dice prod⁢(w1,w2)=2*w1⋅w2∥w1∥2+∥w2∥2dice†⁢(w1,w2)=2*∑f∈w1∩w2min⁢(w1⁢[f], w2⁢[f])∑w1⁢[f]+∑w2⁢[f]lin⁢(w1,w2)=∑f∈w1∩w2w1⁢[f]+w2⁢[f]∑w1⁢[f]+∑w2⁢[f]cos⁢(w1,w2)=dice prod appliedto unit vectors

(6)
       <p class="ltx_p">
        The function
        dice
        prod
        is not well known in the word similarity literature, but in
the data mining literature it is
often just called Dice coefficient,
because it generalized the set comparison
function of Dice
        [5]
        .
Observe that cosine is a special
case of
        dice
        prod
        .
        dice†
        was introduced in Curran
        [3]
        and was the most successful function
in his evaluation.
Since
        lin
        was introduced in Lin
        [13]
        ; several different
functions have born that name. The version used here is the one used
in Curran
        [3]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        The three distinct functions
in Equation
        6
        have a similar form.
In fact, all can be defined in terms of
        σ
        functions differing
only in their
        si
        operation.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        Let
        σsi
        be a shared feature sum for operation
        si
        ,
as defined in Equation (
        3
        ). We
define the Tversky-normalized version of
        σsi
        ,
written
        Tsi
        , as:
       </p>
       Tsi⁢(w1,w2)=2⋅σsi⁢(w1,w2)σsi⁢(w1,w1)+σsi⁢(w2,w2)

(7)
       <p class="ltx_p">
        Note that
        Tsi
        is just the special case of Tversky’s ratio model (
        5
        )
in which
        α=0.5
        and the similarity measure is symmetric.
       </p>
      </div>
      <div class="ltx_para" id="S1.p9">
       <p class="ltx_p">
        We define three SI operations
        σprod
        ,
        σmin
        , and
        σavg
        as follows:
       </p>
       SIσsi⁢(w1,w2)prod∑f∈w1∩w2w1⁢[f]*w2⁢[f]avg∑f∈w1∩w2w1⁢[f]+w2⁢[f]2min∑f∈w1∩w2min⁢(w1⁢[f],w2⁢[f])
       <p class="ltx_p">
        This yields the three similarity functions cited above:
       </p>
       dice prod⁢(w1,w2)=Tprod⁢(w1,w2)dice†⁢(w1,w2)=Tmin⁢(w1,w2)lin⁢(w1,w2)=Tavg⁢(w1,w2)

(8)
       <p class="ltx_p">
        Thus, all three of these functions are special cases of
symmetric ratio models. Below, we investigate
asymmetric versions of all three, which we write
as
        Tα,si⁢(w1,w2)
        , defined as:
       </p>
       σsi⁢(w1,w2)α⋅σsi⁢(w1,w1)+(1-α)⋅σsi⁢(w2,w2)

(9)
       <p class="ltx_p">
        Following
Lee
        [11]
        , who investigates a different
family of asymmetric similarity functions,
we will refer to these
as
        α
        -skewed measures.
       </p>
      </div>
      <div class="ltx_para" id="S1.p10">
       <p class="ltx_p">
        We also will look at a
        rank-biased
        family of measures:
       </p>
       Rα,si⁢(w1,w2)=Tα,si⁢(wh,wl) where⁢wl= arg⁢min w∈{w1,w2}⁢Rank⁢(w)wh= arg⁢max w∈{w1,w2}⁢Rank⁢(w)

(10)
       <p class="ltx_p">
        Here,
        Tα,si⁢(wh,wl)
        is as defined
in (
        9
        ), and the
        α
        -weighted word is always the less frequent word.
For example, consider comparing the 100-feature vector for
        dinghy
        to the 1000 feature vector for
        boat
        : if
        α
        is high,
we give more weight to the proportion of
        dinghy
        ’s features
that are shared than we give to the proportion of
        boat
        ’s features that are shared.
       </p>
      </div>
      <div class="ltx_para" id="S1.p11">
       <p class="ltx_p">
        In the following sections we present data
showing that the performance of a dependency-based
similarity system in capturing human similarity judgments
can be greatly improved with rank-bias and
        α
        -skewing.
We will investigate the three asymmetric functions
defined above.
        We argue that the advantages of rank bias are tied
to improved similarity estimation when comparing
vectors of very different dimensionality. We then turn to the problem
of finding a word’s nearest semantic neighbors. The
nearest neighbor problem is a rather
a natural ground in which to try
out ideas on asymmetry, since the nearest neighbor
relation is itself not symmetrical. We
show that
        α
        -skewing can be used to
improve the quality of nearest neighbors found for both high-
and mid- frequency words.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Systems
      </h2>
      <div class="ltx_para" id="S2.p1">
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           We parsed the BNC with the Malt Dependency parser
           [16]
           and the Stanford parser
           [10]
           ,
creating two dependency DBs,
using basically the design in Lin
           [13]
           ,
with features weighted by PMI
           [2]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           For each of the 3 rank-biased similarity systems
(
           Rα,si
           ) and cosine, we computed correlations
with human judgments for the pairs in 2 standard wordsets:
the combined Miller-Charles/Rubenstein-Goodenough word sets
           [15, 18]
           and
the Wordsim 353 word set
           [6]
           ,
as well as to a subset of the Wordsim set restricted
to reflect semantic similarity judgments,
which we will refer to as Wordsim 201.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           For each of 3
           α
           -skewed similarity systems
(
           Tα,si
           )
and cosine, we found the nearest neighbor from among
BNC nouns (of any rank) for the 10,000 most frequent
BNC nouns using the the dependency DB created in step 2.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          4.
         </span>
         <div class="ltx_para" id="I1.i4.p1">
          <p class="ltx_p">
           To evaluate of the quality of
the nearest neighbors pairs found in Step 4, we
scored them using the Wordnet-based Personalized Pagerank system
described in Agirre
           [1]
           (UKB),
a non distributional WordNet based measure, and the best
system in Table
           1
           .
          </p>
         </div>
        </li>
       </ol>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Human correlations
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Table
        1
        presents the
Spearman’s correlation with human judgments for
Cosine, UKB, and our 3
        α
        -skewed
models using Malt-parser based vectors applied to
the combined Miller-Charles/Rubenstein-Goodenough word sets,
the Wordsim 353 word set,
and the Wordsim 202 word set.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The first of each of the column pairs is a symmetric system,
and the second a rank-biased variant,
based on Equation (
        10
        ). In all cases,
the biased system improves on the performance of its
symmetric counterpart; in the case of
        dice†
        and
        dice
        prod
        , that
improvement is enough for the biased system to outperform
cosine, the best of the symmetric distributionally based systems.
The value .97 was chosen for
        α
        because it produced the best
        α
        -system on the MC/RG corpus.
That value is probably probably an overtrained optimum.
The point is that
        α
        -skewing always helps:
For all three systems, the improvement
shown in raising
        α
        from .5 to whatever the optimum is is
monotonic. This is shown in Figure
        1
        .
Table
        2
        shows very similar results
using the Stanford parser, demonstrating the pattern
is not limited to a single parsing model.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        In Table
        3
        , we list the pairs whose reranking
on the MC/RG dataset
contributed most to the improvement of the
        α=.9
        system over
the default
        α=.5
        system. In the last column an approximation
of the amount of correlation improvement provided by that pair (
        δ
        ):
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Note the 3 of the 5 items contributing the most improvement this system were pairs
with a large difference in rank.
Choosing
        α=.9
        , weights recall toward
the rarer word. We conjecture that the reason
this helps is Tversky’s principle: It is natural
to use the sparser representation as the focus
in the comparison.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Nearest neighbors
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Figure
        2
        gives the results of our nearest neighbor
study on the BNC for the case of
        dice
        prod
        . The graphs for the other two
        α
        -skewed systems are nearly identical,
and are not shown due to space limitations. The target
word, the word whose
nearest neighbor is being found,
always receives the weight
        1-α
        .
The x-axis shows target word rank;
the y-axis shows the average UKB similarity scores assigned
to nearest neighbors every 50 ranks. All the systems show
degraded nearest neighbor quality as target words grow rare, but
at lower ranks,
the
        α=.04
        nearest neighbor system fares considerably better
than the symmetric
        α=.50
        system; the line across the bottom
tracks the score of a system with randomly generated nearest neighbors.
The symmetric
        dice
        prod
        system is as an excellent
nearest neighbor system at high ranks but drops below
the
        α=.04
        system at around rank 3500.
We see that the
        α=.8
        system
is even better than the symmetric system
at high ranks, but
degrades much more quickly.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We explain these results on the basis of the
principle developed for the human correlation
data: To reflect natural judgments of similarity for comparisons of
representations of differing sparseness,
        α
        should be tipped toward
the sparser representation.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Thus,
        α=.80
        works best for high rank
target words, because
most nearest neighbor candidates are less frequent,
and
        α=.8
        tips the balance toward the nontarget
words. On the other
hand, when the target word is a low ranking
word, a high
        α
        weight means it
never receives the highest weight,
and this is disastrous, since most good candidates are higher ranking.
Conversely,
        α=.04
        works better.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Previous work
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        The debt owed to Tversky
        [19]
        has been made clear in the introduction.
Less clear is the debt owed to Jimenez et al.
        [9]
        ,
which also proposes an asymmetric similarity framework based
on Tversky’s insights. Jimenez et al. showed
the continued relevance of Tversky’s work.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Motivated by the problem of measuring how well
the distribution of one word
        w1
        captures the distribution
of another
        w2
        , Weeds and Weir
        [21]
        also explore asymmetric models,
expressing similarity calculations as weighted combinations of
several variants of what they call precision and recall. Some of their models
are also Tverskyan
ratio models. To see this, we divide (
        9
        ) everywhere by
        σ⁢(w1,w2)
        :
       </p>
       Tsi⁢(w1,w2)=1α⋅σ⁢(w1,w1)σ⁢(w1,w2)+(1-α)⋅σ⁢(w2,w2)σ⁢(w1,w2)
       <p class="ltx_p">
        If the
        si
        is
        min
        , then the two terms in the denominator
are the inverses of what W&amp;W call difference-weighted precision and recall:
       </p>
       prec⁢(w1,w2)=σmin⁢(w1,w2)σmin⁢(w1,w1)rec⁢(w1,w2)=σmin⁢(w1,w2)σmin⁢(w2,w2),
       <p class="ltx_p">
        So for
        Tmin
        , (
        9
        ) can be rewritten:
       </p>
       1αprec⁢(w1,w2)+1-αrec⁢(w1,w2)
       <p class="ltx_p">
        That is,
        Tmin
        is a weighted
harmonic mean of precision and recall, the so-called weighted F-measure
        [14]
        . W&amp;W’s additive precision/recall
models appear not to be Tversky models, since they compute
separate sums for precision and recall from the
        f∈w1∩w2
        , one using
        w1⁢[f]
        ,
and one using
        w2⁢[f]
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Long before Weed and Weir, Lee
        [12]
        proposed an asymmetric similarity
measure as well. Like Weeds and
Weir, her perspective
was to calculate the effectiveness of
using one distribution
as a proxy for the other,
a fundamentally asymmetric problem.
For distributions
        q
        and
        r
        ,
Lee’s
        α
        -skew divergence takes
the KL-divergence of a mixture of
        q
        and
        r
        from
        q
        ,
using the
        α
        parameter to define
the proportions in the mixture.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
