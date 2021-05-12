<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Learning Soft Linear Constraints with Application to Citation Field Extraction.
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
       Accurately segmenting a citation string into fields for authors, titles, etc. is a challenging task because the output typically obeys various global constraints. Previous work has shown that modeling
       soft constraints
       , where the model is encouraged, but not require to obey the constraints, can substantially improve segmentation performance. On the other hand, for imposing
       hard constraints
       , dual decomposition is a popular technique for efficient prediction given existing algorithms for unconstrained inference. We extend dual decomposition to perform prediction subject to soft constraints. Moreover, with a technique for performing inference given soft constraints, it is easy to automatically generate large families of constraints and learn their costs with a simple convex optimization problem during training. This allows us to obtain substantial gains in accuracy on a new, challenging citation extraction dataset.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       algorithmttop
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
        Citation field extraction, an instance of information extraction, is the task of segmenting and labeling research paper citation strings into their constituent parts, including authors, editors, year, journal, volume, conference venue, etc. This task is important because citation data is often provided only in plain text; however, having an accurate structured database of bibliographic information is necessary for many scientometric tasks, such as mapping scientific sub-communities, discovering research trends, and analyzing networks of researchers. Automated citation field extraction needs further research because it has not yet reached a level of accuracy at which it can be practically deployed in real-world systems.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Hidden Markov models and linear-chain conditional random fields (CRFs) have previously been applied to citation extraction
        [9, 14]
        . These models support efficient dynamic-programming inference, but only model
        local
        dependencies in the output label sequence. However citations have strong
        global
        regularities not captured by these models. For example many book citations contain both an
        author
        section and an
        editor
        section, but none have two disjoint
        author
        sections. Since linear-chain models are unable to capture more than Markov dependencies, the models sometimes mislabel the
        editor
        as a second author. If we could enforce the global constraint that there should be only one
        author
        section, accuracy could be improved.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        One framework for adding such global constraints into tractable models is
        constrained inference
        , in which at inference time the original model is augmented with restrictions on the outputs such that they obey certain global regularities. When hard constraints can be encoded as linear equations on the output variables, and the underlying model’s inference task can be posed as linear optimization, one can formulate this constrained inference problem as an
        integer linear program
        (ILP)
        [15]
        . Alternatively, one can employ
        dual decomposition
        [17]
        . Dual decompositions’s advantage over ILP is is that it can leverage existing inference algorithms for the original model as a black box. Such a modular algorithm is easy to implement, and works quite well in practice, providing certificates of optimality for most examples.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The above two approaches have previously been applied to impose
        hard
        constraints on a model’s output. On the other hand, recent work has demonstrated improvements in citation field extraction by imposing
        soft
        constraints
        [4]
        . Here, the model is not required obey the global constraints, but merely pays a penalty for their violation.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        This paper introduces a novel method for imposing soft constraints via dual decomposition. We also propose a method for learning the penalties the prediction problem incurs for violating these soft constraints. Because our learning method drives many penalties to zero, it allows practitioners to perform ‘constraint selection,’ in which a large number of automatically-generated candidate global constraints can be considered and automatically culled to a smaller set of useful constraints, which can be run quickly at test time.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Using our new method, we are able to incorporate not only all the soft global constraints of Chang et al.
        [4]
        , but also far more complex data-driven constraints, while also providing stronger optimality certificates than their beam search technique. On a new, more broadly representative, and challenging citation field extraction data set, we show that our methods achieve a 17.9% reduction in error versus a linear-chain conditional random field. Furthermore, we demonstrate that our inference technique can use and benefit from the constraints of Chang et al.
        [4]
        , but that including our data-driven constraints on top of these is beneficial. While this paper focusses on an application to citation field extraction, the novel methods introduced here would easily generalize to many problems with global output regularities.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Background
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Structured Linear Models
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         The overall modeling technique we employ is to add soft constraints to a simple model for which we have an existing efficient prediction algorithm. For this underlying model, we employ a chain-structured conditional random field (CRF), since CRFs have been shown to perform better than other simple unconstrained models like hidden markov models for citation extraction
         [14]
         . We produce a prediction by performing
         MAP inference
         [10]
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The MAP inference task in a CRF be can expressed as an optimization problem with a linear objective
         [21, 20]
         . Here, we define a binary indicator variable for each candidate setting
of each factor in the graphical model. Each of these indicator
variables is associated with the score that the factor takes on
when it has the indictor variable’s corresponding value. Since the
log probability of some
         y
         in the CRF is proportional to sum of
the scores of all the factors, we can concatenate the indicator
variables as a vector
         y
         and the scores as a vector
         w
         and write the MAP problem as
        </p>
        max.⟨w,y⟩s.t.y∈𝒰,

(1)
        <p class="ltx_p">
         where the set
         𝒰
         represents the set of valid configurations
of the indicator variables. Here, the constraints are that all neighboring factors agree on the components of
         y
         in their overlap.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         Structured Linear Models
         are the general family of models
where prediction requires solving a problem of the
form (
         1
         ), and they do not always correspond to a
probabilistic model. The algorithms we present in later sections
for handling soft global constraints and for learning the penalties of
these constraints can be applied to general structured linear models,
not just CRFs, provided we have an available algorithm for
performing MAP inference.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Dual Decomposition for Global Constraints
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         In order to perform prediction subject to various global constraints, we may need to augment the problem (
         1
         ) with additional constraints. Dual Decomposition is a popular method for performing MAP inference in this scenario, since it leverages known algorithms for MAP in the base problem where these extra constraints have not been added
         [11, 20, 18]
         . In this case, the MAP problem can be formulated as a structured linear model
similar to equation (
         1
         ), for which we have a MAP algorithm, but
where we have imposed some additional constraints
         A⁢y≤b
         that no longer allow us to use the algorithm. In other words,
we consider the problem
        </p>
        max.⟨w,y⟩s.t.y∈𝒰A⁢y≤b,

(2)
        <p class="ltx_p">
         for an arbitrary matrix
         A
         and vector
         b
         . We can write the
Lagrangian of this problem as
        </p>
        L⁢(y,λ)=⟨w,y⟩+λT⁢(A⁢y-b).

(3)
        <p class="ltx_p">
         Regrouping terms and maximizing over the primal variables, we have
the dual problem
        </p>
        𝐦𝐢𝐧.λD(λ)=maxy∈𝒰⟨w+ATλ,y⟩-λTb.

(4)
        <p class="ltx_p">
         For any
         λ
         , we can evaluate the dual objective
         D⁢(λ)
         , since the
maximization in (
         4
         ) is of the same form as the original
problem (
         1
         ), and we assumed
we had a method for performing MAP in this. Furthermore, a subgradient of
         D⁢(λ)
         is
         A⁢y*-b
         , for an
         y*
         which maximizes this inner optimization problem. Therefore, we
can minimize
         D⁢(λ)
         with the projected subgradient method
         [2]
         , and the optimal
         y
         can be obtained when
evaluating
         D⁢(λ*)
         . Note that the subgradient of
         D⁢(λ)
         is the amount by which each constraint is
violated by
         λ
         when maximizing over
         y
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         DD: projected subgradient for dual decomposition with hard constraints
         [1]
         has not converged
y(t)=argmaxy∈𝒰⁡⟨w+AT⁢λ,y⟩
λ(t)=Π0⁣≤⁣⋅⁢[λ(t-1)-η(t)⁢(A⁢y-b)]
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         Algorithm
         2.2
         depicts the basic projected subgradient
descent algorithm for dual decomposition. The projection operator
         Π
         consists of truncating all negative coordinates of
         λ
         to 0. This is necessary because
         λ
         is a vector of dual variables for
inequality constraints. The algorithm has converged when each constraint is
either satisfied by
         y(t)
         with equality or its corresponding component of
         λ
         is
0, due to complimentary slackness
         [2]
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Soft Constraints in Dual Decomposition
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We now introduce an extension of Algorithm
        2.2
        to
handle soft constraints. In our formulation, a soft-constrained model imposes a
penalty for each unsatisfied constraint, proportional to the
amount by which it is violated. Therefore, our derivation parallels how
soft-margin SVMs are derived from hard-margin SVMs by introducing
auxiliary slack variables
        [7]
        . Note that when performing MAP subject to soft constraints, optimal solutions might not satisfy some constraints, since doing so would reduce
the model’s score by too much.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Consider the optimization problems of the form:
       </p>
       max.⟨w,y⟩-⟨c,z⟩s.t.y∈𝒰A⁢y-b≤z-z≤0,

(5)
       <p class="ltx_p">
        For positive
        ci
        , it is clear that an optimal
        zi
        will be
equal to the degree to which
        aiT⁢y≤bi
        is
violated. Therefore, we pay a cost
        ci
        times the degree to which
the
        i
        th constraint is violated, which mirrors how slack
variables are used to represent the hinge loss for SVMs. Note that
        ci
        has to be positive, otherwise this linear program is
unbounded and an optimal value can be obtained by setting
        zi
        to
infinity.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Using a similar construction as in section
        2.2
        we write the Lagrangian as:
        L(y,z,λ,μ) = ⟨w,y ⟩ - ⟨c,z ⟩ + λ^T(Ay - b - z) + μ^T (-z).

The optimality constraints with respect to
        z
        tell us that
        -c-λ-μ=0
        , hence
        μ=-c-λ
        . Substituting, we have
       </p>
       L⁢(y,λ)=⟨w,y⟩+λT⁢(A⁢y-b),

(6)
       <p class="ltx_p">
        except the constraint that
        μ=-c-λ
        implies that for
        μ
        to be positive
        λ≤c
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Since this Lagrangian has the same form as equation (
        3
        ), we can also derive a dual problem, which is the same as in
equation (
        4
        ), with the additional constraint that each
        λi
        can not be bigger than its cost
        ci
        . In other
words, the dual problem can not penalize the violation of a
constraint more than the soft constraint model in the primal would penalize you if you violated
it.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        This optimization problem
can still be solved with projected subgradient
descent and is depicted in Algorithm
        3
        . The only modifications to Algorithm
        2.2
        are replacing the
coordinate-wise projection
        Π0⁣≤⁣⋅
        with
        Π0⁣≤⁣⋅⁣≤c
        and how we check for convergence. Now, we check for the KKT
conditions of (
        5
        ), where for every constraint
        i
        ,
either the constraint is satisfied with equality,
        λi=0
        , or
        λi=ci
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        Therefore, implementing soft-constrained
dual decomposition is as easy as implementing hard-constrained
dual decomposition, and the per-iteration complexity is the
same. We encourage further applications of soft-constraint dual
decomposition to existing and new NLP problems.
       </p>
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        Soft-DD: projected subgradient for dual decomposition with soft constraints
        [1]
        has not converged
y(t)=argmaxy∈𝒰⁡⟨w+AT⁢λ,y⟩
λ(t)=Π0⁣≤⁣⋅⁣≤c⁢[λ(t-1)-η(t)⁢(A⁢y-b)]
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Learning Penalties
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         One consideration when using soft v.s. hard constraints is that
soft constraints present a new training problem, since
we need to choose the vector
         c
         , the penalties for violating the
constraints.
An important property of problem (
         5
         ) in the previous
section is that it corresponds to a
structured linear model over
         y
         and
         z
         . Therefore, we can apply known training algorithms for
estimating the parameters of structured linear models to choose
         c
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         All we need to employ the structured perceptron algorithm
         [6]
         or the
structured SVM algorithm
         [23]
         is a
black-box procedure for performing MAP inference in the structured
linear model given an arbitrary cost vector. Fortunately, the MAP problem for  (
         5
         ) can be solved using Soft-DD, in Algorithm
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Each penalty
         ci
         has to be non-negative; otherwise, the
optimization problem in equation (
         5
         ) is ill-defined. This can be ensured by simple modifications of the perceptron and subgradient descent optimization of the structured SVM objective simply by truncating
         c
         coordinate-wise to be non-negative at every learning iteration.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Intuitively, the perceptron update increases the penalty for a constraint if it is satisfied in the ground truth and not in an inferred prediction, and decreases the penalty if the constraint is satisfied in the prediction and not the ground truth. Since we truncate penalties at 0, this suggests that we will learn a penalty of 0 for constraints in three categories: constraints that do not hold in the ground truth, constraints that hold in the ground truth but are satisfied in practice by performing inference in the base CRF model, and constraints that are satisfied in practice as a side-effect of imposing non-zero penalties on some other constraints . A similar analysis holds for the structured SVM approach.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         Therefore, we can view learning the values of the penalties not just as parameter tuning, but as a means to perform ‘constraint selection,’ since constraints that have a penalty of 0 can be ignored. This property allows us to consider large families of constraints, from which the useful ones are automatically identified.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         We found it beneficial, though it is not theoretically necessary,
to learn the constraints on a held-out development set, separately
from the other model parameters, as during training most
constraints are satisfied due to overfitting, which leads to an
underestimation of the relevant penalties.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Citation Extraction Data
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We consider the UMass citation dataset, first introduced in Anzaroot and McCallum
        [1]
        . It has over 1800 citation from many academic fields,
extracted from the arXiv. This dataset contains both coarse-grained
and fine-grained labels; for example it contains labels for the
segment of all authors, segments for each individual author, and
for the first and last name of each author. There are 660
citations in the development set and 367 citation in the test set.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The labels in the UMass dataset are a concatenation of labels from a hierarchically-defined schema. For example, a first name of an author is tagged as:
        authors/person/first
        . In addition, individual tokens are labeled using a BIO label schema for each level in the hierarchy.
BIO is a commonly used labeling schema for information extraction tasks. BIO labeling allows individual labels on tokens to label segmentation information as well as labels for the segments. In this schema, labels that begin segments are prepended with a
        B
        , labels that continue a segment are prepended with an
        I
        , and tokens that don’t have a labeling in this schema are given an
        O
        label. For example, in a hierarchical BIO label schema the first token in the first name for the second author may be labeled as:
        I-authors/B-person/B-first
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        An example labeled citation in this dataset can be viewed in figure
        1
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Global Constraints for Citation Extraction
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Constraint Templates
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We now describe the families of global constraints we consider for citation extraction.
Note these constraints are all
linear, since they depend only on the counts of each possible
conditional random field label. Moreover, since our labels are
BIO-encoded, it is possible, by counting B tags, to count how
often each citation tag itself appears in a sentence. The first two
families of constraints that we describe are general to any sequence
labeling task while the last is specific to hierarchical labeling
such as available in the UMass dataset.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Our sequence output is denoted as
         y
         and an element of this sequence is
         yk
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         We denote
         [[yk=i]]
         as the function
that outputs
         1
         if
         yk
         has a
         1
         at index
         i
         and
         0
         otherwise.
Here,
         yk
         represents an output tag of the CRF, so if
         [[yk=i]]
         = 1, then we have that
         yk
         was given a label with index
         i
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Singleton Constraints
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         Singleton constraints ensure that each label can appear at most once in a citation. These are same global constraints that were used for citation field extraction in Chang et al.
         [4]
         . We define
         s⁢(i)
         to be the number of times the label with index
         i
         is predicted in a citation, formally:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        s(i)=∑yk∈y[[yk=i]]
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         The constraint that each label can appear at most once takes the form:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        s⁢(i)≤1
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Pairwise Constraints
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         Pairwise constraints are constraints on the counts of two labels in a citation. We define
         z1⁢(i,j)
         to be
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        z1(i,j)=∑yk∈y[[yk=i]]+∑yk∈y[[yk=j]]
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         and
         z2⁢(i,j)
         to be
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        z2(i,j)=∑yk∈y[[yk=i]]-∑yk∈y[[yk=j]]
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         We consider all constraints of the forms:
         z⁢(i,j)≤0,1,2,3
         and
         z⁢(i,j)≥0,1,2,3
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p6">
        <p class="ltx_p">
         Note that some pairs of these constraints are redundant or logically incompatible. However, we are using them as soft constraints, so these constraints will not necessarily be satisfied by the output of the model, which eliminates concern over enforcing logically impossible outputs. Furthermore, in section
         3.1
         we described how our procedure for learning penalties will drive some penalties to 0, which effectively removes them from our set of constraints we consider. It can be shown, for example, that we will never learn non-zero penalties for certain pairs of logically incompatible constraints using the perceptron-style algorithm described in section
         3.1
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Hierarchical Equality Constraints
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         The labels in the citation dataset are hierarchical labels. This means that the labels are the concatenation of all the levels in the hierarchy. We can create constraints that are dependent on only one or couple of elements in the hierarchy.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <p class="ltx_p">
         We define
         C⁢(x,i)
         as the function that returns 1 if the output
         x
         contains the label
         i
         in the hierarchy and 0 otherwise. We define
         e⁢(i,j)
         to be
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p3">
        e⁢(i,j)=∑yk∈y[[C⁢(yk,i)]]-∑yk∈y[[C⁢(yk,j)]]
       </div>
       <div class="ltx_para" id="S5.SS4.p4">
        <p class="ltx_p">
         Hierarchical equality constraints take the forms:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S5.E7">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           e⁢(i,j)
          </td>
          <td class="ltx_td ltx_align_center">
           ≥
          </td>
          <td class="ltx_td ltx_align_left">
           0
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (7)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S5.E8">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           e⁢(i,j)
          </td>
          <td class="ltx_td ltx_align_center">
           ≤
          </td>
          <td class="ltx_td ltx_align_left">
           0
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
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.5
        </span>
        Local constraints
       </h3>
       <div class="ltx_para" id="S5.SS5.p1">
        <p class="ltx_p">
         We constrain the output labeling of the chain-structured CRF to be a valid BIO encoding. This both improves performance of the underlying model when used without global constraints, as well as ensures the validity of the global constraints we impose, since they operate only on
         B
         labels. The constraint that the labeling is valid BIO can be expressed as a collection of pairwise constraints on adjacent labels in the sequence. Rather than enforcing these constraints using dual decomposition, they can be enforced directly when performing MAP inference in the CRF by modifying the dynamic program of the Viterbi algorithm to only allow valid pairs of adjacent labels.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS6">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.6
        </span>
        Constraint Pruning
       </h3>
       <div class="ltx_para" id="S5.SS6.p1">
        <p class="ltx_p">
         While the techniques from section
         3.1
         can easily cope with a large numbers of constraints at training
time, this can be computationally costly, specially if one is
considering very large constraint families. This is problematic because the size of some constraint families we consider grows quadratically with the number of candidate labels, and there are about 100 in the UMass dataset. Such a family consists of constraints that the sum of the
counts of two different label types has to be bounded (a useful
example is that there can’t be more than one out of “phd
thesis” and “journal”). Therefore, quickly pruning bad constraints can save a substantial amount of training time, and can lead to better generalization.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS6.p2">
        <p class="ltx_p">
         To do so, we calculate a score that estimates how useful each
constraint is expected to be. Our score compares how often the
constraint is violated in the ground truth examples versus our predictions. Here, prediction is done with respect to the base chain-structured CRF tagger and does not include global constraints.
Note that it may make sense to consider a
constraint that is sometimes violated in the ground truth, as the penalty learning
algorithm can learn a small penalty for it, which will allow it to be
violated some of the time. Our importance score is defined as, for
each constraint
         c
         on labeled set
         D
         ,
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S5.E9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           i⁢m⁢p⁢(c)=∑d∈D[[m⁢a⁢xy⁢wdT⁢y]]c∑d∈D[[yd]]c,
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
         where
         [[y]]c
         is 1 if the constraint is violated on output
         y
         and 0 otherwise. Here,
         yd
         denotes the ground truth labeling and
         wd
         is the vector of scores for the CRF tagger.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS6.p3">
        <p class="ltx_p">
         We prune constraints by picking a cutoff value for
         i⁢m⁢p⁢(c)
         . A
value of
         i⁢m⁢p⁢(c)
         above 1 implies that the constraint is more
violated on the predicted examples than on the ground truth, and
hence that we might want to keep it.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS6.p4">
        <p class="ltx_p">
         We also find that the constraints that have the largest
         i⁢m⁢p
         values are semantically interesting.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        There are multiple previous examples of augmenting chain-structured sequence models with terms capturing global relationships by expanding the chain to a more complex graphical model with non-local dependencies between the outputs. Inference in these models can be performed, for example, with loopy belief propagation
        [3, 22]
        or Gibbs sampling
        [8]
        . Belief propagation is prohibitively expensive in our model due to the high cardinalities of the output variables and of the global factors, which involve all output variables simultaneously. There are various methods for exploiting the combinatorial structure of these factors, but performance would still have higher complexity than our method. While Gibbs sampling has been shown to work well tasks such as named entity recognition
        [8]
        , our previous experiments show that it does not work well for citation extraction, where it found only low-quality solutions in practice because the sampling did not mix well, even on a simple chain-structured CRF.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Recently, dual decomposition has become a popular method for solving complex structured prediction problems in NLP
        [12, 17, 18, 13, 5]
        . Soft constraints can be implemented inefficiently using hard constraints and dual decomposition— by introducing copies of output variables and an auxiliary graphical model, as in Rush et al.
        [16]
        . However, at every iteration of dual decomposition, MAP must be run in this auxiliary model. Furthermore the copying of variables doubles the number of iterations needed for information to flow between output variables, and thus slows convergence. On the other hand, our approach to soft constraints has identical per-iteration complexity as for hard constraints, and is a very easy modification to existing hard constraint code.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Initial work in machine learning for citation extraction used Markov models with no global constraints. Hidden Markov models (HMMs), were originally employed for automatically extracting information from research papers on the CORA dataset
        [19, 9]
        . Later, CRFs were shown to perform better on CORA, improving the results from the Hmm’s token-level F1 of 86.6 to 91.5 with a CRF
        [14]
        .
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Recent work on globally-constrained inference in citation extraction used an HMM
        C⁢C⁢M
        , which is an HMM with the addition of global features that are restricted to have positive weights
        [4]
        . Approximate inference is performed using beam search. This method increased the HMM token-level accuracy from 86.69 to 93.92 on a test set of 100 citations from the CORA dataset. The global constraints added into the model are simply that each label only occurs once per citation. This approach is limited in its use of an HMM as an underlying model, as it has been shown that CRFs perform significantly better, achieving 95.37 token-level accuracy on CORA
        [14]
        . In our experiments, we demonstrate that the specific global constraints used by Chang et al.
        [4]
        help on the UMass dataset as well.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S7">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        7
       </span>
       Experimental Results
      </h2>
      <div class="ltx_para" id="S7.p1">
       <p class="ltx_p">
        Our baseline is the one used in Anzaroot and McCallum
        [1]
        , with some labeling errors removed. This is a chain-structured CRF trained to maximize the conditional likelihood using L-BFGS with L2 regularization.
       </p>
      </div>
      <div class="ltx_para" id="S7.p2">
       <p class="ltx_p">
        We use the same features as Anzaroot and McCallum
        [1]
        , which include word type, capitalization, binned location in citation, regular expression matches, and matches into lexicons. In addition, we use a rule-based segmenter that segments the citation string based on punctuation as well as probable start or end segment words (e.g. ‘in’ and ‘volume’). We add a binary feature to tokens that correspond to the start of a segment in the output of this simple segmenter. This final feature improves the F1 score on the cleaned test set from 94.0 F1 to 94.44 F1, which we use as a baseline score.
       </p>
      </div>
      <div class="ltx_para" id="S7.p3">
       <p class="ltx_p">
        We then use the development set to learn the penalties for the soft constraints, using the perceptron algorithm described in section
        3.1
        . MAP inference in the model with soft constraints is performed using Soft-DD, shown in Algorithm
        3
        .
       </p>
      </div>
      <div class="ltx_para" id="S7.p4">
       <p class="ltx_p">
        We instantiate constraints from each template in section
        5.1
        , iterating over all possible labels that contain a
        B
        prefix at any level in the hierarchy and pruning all constraints with
        i⁢m⁢p⁢(c)&lt;2.75
        calculated on the development set. We asses performance in terms of field-level F1 score, which is the harmonic mean of precision and recall for predicted segments.
       </p>
      </div>
      <div class="ltx_para" id="S7.p5">
       <p class="ltx_p">
        Table
        1
        shows how each type of constraint family improved the F1 score on the dataset. Learning all the constraints jointly provides the largest improvement in F1 at 95.39. This improvement in F1 over the baseline CRF as well as the improvement in F1 over using only-one constraints was shown to be statistically significant using the Wilcoxon signed rank test with p-values
        &lt;0.05
        . In the all-constraints settings, 32.96% of the constraints have a learned parameter of
        0
        , and therefore only 421 constraints are active.
Soft-DD converges, and thus solves the constrained inference problem exactly, for all test set examples after at most 41 iterations. Running Soft-DD to convergence requires 1.83 iterations on average per example. Since performing inference in the CRF is by far the most computationally intensive step in the iterative algorithm, this means our procedure requires approximately twice as much work as running the baseline CRF on the dataset. On examples where unconstrained inference does not satisfy the constraints, Soft-DD converges after 4.52 iterations on average. For 11.99% of the examples, the Soft-DD algorithm satisfies constraints that were not satisfied during unconstrained inference, while in the remaining 11.72% Soft-DD converges with some constraints left unsatisfied, which is possible since we are imposing them as soft constraints.
       </p>
      </div>
      <div class="ltx_para" id="S7.p6">
       <p class="ltx_p">
        We could have enforced these constraints as hard constraints rather than soft ones. This experiment is shown in the last row of Table
        1
        , where F1 only improves to 94.6. In addition, running the DD algorithm with these constraints takes 5.21 iterations on average per example, which is 2.8 times slower than Soft-DD with learned penalties.
       </p>
      </div>
      <div class="ltx_para" id="S7.p7">
       <p class="ltx_p">
        In Figure
        2
        , we analyze the performance of Soft-DD when we don’t necessarily run it to convergence, but stop after a fixed number of iterations on each test set example. We find that a large portion of our gain in accuracy can be obtained when we allow ourselves as few as 2 dual decomposition iterations. However, this only amounts to 1.24 times as much work as running the baseline CRF on the dataset, since the constraints are satisfied immediately for many examples.
       </p>
      </div>
      <div class="ltx_para" id="S7.p8">
       <p class="ltx_p">
        In Figure
        2
        we consider two applications of our Soft-DD algorithm, and provide analysis in the caption.
       </p>
      </div>
      <div class="ltx_para" id="S7.p9">
       <p class="ltx_p">
        We train and evaluate on the UMass dataset instead of CORA, because it is significantly larger, has a useful finer-grained labeling schema, and its annotation is more consistent. We were able to obtain better performance on CORA using our baseline CRF than the
        H⁢M⁢MC⁢C⁢M
        results presented in Chang et al.
        [4]
        , which include soft constraints. Given this high performance of our base model on CORA, we did not apply our Soft-DD algorithm to the dataset. Furthermore, since the dataset is so small, learning the penalties for our large collection of constraints is difficult, and test set results are unreliable. Rather than compare our work to Chang et al.
        [4]
        via results on CORA, we apply their constraints on the UMass data using Soft-DD and demonstrate accuracy gains, as discussed above.
       </p>
      </div>
      <div class="ltx_subsection" id="S7.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         7.1
        </span>
        Examples of learned constraints
       </h3>
       <div class="ltx_para" id="S7.SS1.p1">
        <p class="ltx_p">
         We now describe a number of the useful constraints that receive non-zero learned penalties and have high importance scores, defined in Section
         5.6
         . The importance score of a constraint provides information about how often it is violated by the CRF, but holds in the ground truth, and a non-zero penalty implies we enforce it as a soft constraint at test time.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p2">
        <p class="ltx_p">
         The two singleton constraints with highest importance score are that there should only be at most one
         title
         segment in a citation and that there should be at most one
         author
         segment in a citation. The only one
         author
         constraint is particularly useful for correctly labeling
         editor
         segments in cases where unconstrained inference mislabels them as
         author
         segments. As can be seen in Table
         3
         ,
         editor
         fields are among the most improved with our new method, largely due to this constraint.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p3">
        <p class="ltx_p">
         The two hierarchical constraints with the highest importance scores with non-zero learned penalties constrain the output such that number of
         person
         segments does not exceed the number of
         first
         segments and vice-versa. Together, these constraints penalize outputs in which the number of
         person
         segments do not equal the number of
         first
         segments, i.e., every author should have a first name.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p4">
        <p class="ltx_p">
         One important pairwise constraint penalizes outputs in which
         thesis
         segments don’t co-occur with
         school
         segments.
         School
         segments label the name of the university that the thesis was submitted to. The application of this constraint increases the performance of the model on
         school
         segments dramatically, as can be seen in table
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p5">
        <p class="ltx_p">
         An interesting form of pairwise constraints penalize outputs in which some labels do not co-occur with other labels. Some examples of constraints in this form enforce that
         journal
         segments should co-occur with
         pages
         segments and that
         booktitle
         segments should co-occur with
         address
         segments. An example of the latter constraint being employed during inference is the first example in Figure
         2
         . Here, the constrained inference penalizes output which contains a
         booktitle
         segment but no
         address
         segment. This penalization leads allows the constrained inference to correctly label the
         booktitle
         segment as a
         title
         segment.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p6">
        <p class="ltx_p">
         The above example constraints are almost always satisfied on the ground truth, and would be useful to enforce as hard constraints. However, there are a number of learned constraints that are often violated on the ground truth but are still useful as soft constraints.
Take, for example, the constraint that the number of
         number
         segments does not exceed the number of
         booktitle
         segments, as well as the constraint that it does not exceed the number of
         journal
         segments. These constraints are moderately violated on ground truth examples, however. For example, when
         booktitle
         segments co-occur with
         number
         segments but not with
         journal
         segments, the second constraint is violated. It is still useful to impose these soft constraints, as strong evidence from the CRF allows us to violate them, and they can guide the model to good predictions when the CRF is unconfident.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
