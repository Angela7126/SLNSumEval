<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Distant Supervision for Relation Extraction with Matrix Completion.
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
       The essence of distantly supervised relation extraction is that it is an
       incomplete
       multi-label classification problem with
       sparse
       and
       noisy
       features. To tackle the sparsity and noise challenges, we propose solving the classification problem using matrix completion on factorized matrix of minimized rank.
We formulate relation classification as completing the unknown labels of testing items (entity pairs) in a sparse matrix that concatenates training and testing textual features with training labels.
Our algorithmic framework is based on the assumption that the rank of item-by-feature and item-by-label joint matrix is low. We apply two optimization models to recover the underlying low-rank matrix leveraging the sparsity of feature-label matrix. The matrix completion problem is then solved by the fixed point continuation (FPC) algorithm, which can find the global optimum. Experiments on two widely used datasets with different dimensions of textual features demonstrate that our low-rank matrix completion approach significantly outperforms the baseline and the state-of-the-art methods.
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
        Relation Extraction (RE) is the process of generating structured relation knowledge from unstructured natural language texts. Traditional supervised methods
        [28, 1]
        on small hand-labeled corpora, such as MUC
        and ACE
        , can achieve high precision and recall. However, as producing hand-labeled corpora is laborius and expensive, the supervised approach can not satisfy the increasing demand of building large-scale knowledge repositories with the explosion of Web texts.
To address the lacking training data issue, we consider the distant
        [19]
        or weak
        [13]
        supervision paradigm attractive, and we improve the effectiveness of the paradigm in this paper.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The intuition of the paradigm is that one can take advantage of several knowledge bases, such as WordNet
        , Freebase
        and YAGO
        , to automatically label free texts, like Wikipedia
        and New York Times corpora
        , based on some heuristic alignment assumptions.
An example accounting for the basic but practical assumption is illustrated in Figure 1, in which we know that the two entities (
        &lt;
        Barack Obama, U.S.&gt;
        ) are not only involved in the
        relation instances
        coming from knowledge bases (
        President-of(Barack Obama, U.S.)
        and
        Born-in(Barack Obama, U.S.)
        ), but also co-occur in several
        relation mentions
        appearing in free texts (
        Barack Obama is the 44th and current President of the U.S.
        and
        Barack Obama was born in Honolulu, Hawaii, U.S.
        , etc.). We extract diverse textual features from all those
        relation mentions
        and combine them into a rich feature vector labeled by the
        relation names
        (
        President-of
        and
        Born-in
        ) to produce a
        weak
        training corpus for relation classification.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        This paradigm is promising to generate large-scale training corpora automatically. However, it comes up against three technical challeges:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Sparse features
           . As we cannot tell what kinds of features are effective in advance, we have to use NLP toolkits, such as Stanford CoreNLP
           , to extract a variety of textual features, e.g., named entity tags, part-of-speech tags and lexicalized dependency paths. Unfortunately, most of them appear only once in the training corpus, and hence leading to very sparse features.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Noisy features
           . Not all relation mentions express the corresponding relation instances. For example, the second relation mention in Figure 1 does not explicitly describe any relation instance, so features extracted from this sentence can be noisy. Such analogous cases commonly exist in feature extraction.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Incomplete labels
           . Similar to noisy features, the generated labels can be incomplete. For example, the fourth relation mention in Figure 1 should have been labeled by the relation
           Senate-of
           . However, the incomplete knowledge base does not contain the corresponding relation instance (
           Senate-of(Barack Obama, U.S.)
           ). Therefore, the distant supervision paradigm may generate incomplete labeling corpora.
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        In essence, distantly supervised relation extraction is an
        incomplete
        multi-label classification task with
        sparse
        and
        noisy
        features.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        In this paper, we formulate the relation-extraction task from a novel perspective of using matrix completion with low rank criterion. To the best of our knowledge, we are the first to apply this technique on relation extraction with distant supervision.
More specifically, as shown in Figure 2, we model the task with a sparse matrix whose rows present items (entity pairs) and columns contain noisy textual features and incomplete relation labels. In such a way, relation classification is transformed into a problem of completing the unknown labels for testing items in the sparse matrix that concatenates training and testing textual features with training labels, based on the assumption that the item-by-feature and item-by-label joint matrix is of low rank.
The rationale of this assumption is that noisy features and incomplete labels are semantically correlated. The low-rank factorization of the sparse feature-label matrix delivers the low-dimensional representation of de-correlation for features and labels.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We contribute two optimization models, DRMC
        -b and DRMC-1, aiming at exploiting the sparsity to recover the underlying low-rank matrix and to complete the unknown testing labels simultaneously. Moreover, the logistic cost function is integrated in our models to reduce the influence of noisy features and incomplete labels, due to that it is suitable for binary variables. We also modify the fixed point continuation (FPC) algorithm
        [16]
        to find the global optimum.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Experiments on two widely used datasets demonstrate that our noise-tolerant approaches outperform the baseline and the state-of-the-art methods. Furthermore, we discuss the influence of feature sparsity, and our approaches consistently achieve better performance than compared methods under different sparsity degrees.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The idea of distant supervision was firstly proposed in the field of bioinformatics
        [8]
        . Snow et al.
        [23]
        used WordNet as the knowledge base to discover more hpyernym/hyponym relations between entities from news articles. However, either bioinformatic database or WordNet is maintained by a few experts, thus hardly kept up-to-date.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        As we are stepping into the
        big data
        era, the explosion of unstructured Web texts simulates us to build more powerful models that can automatically extract relation instances from large-scale online natural language corpora without hand-labeled annotation.
Mintz et al.
        [19]
        adopted Freebase
        [3, 2]
        , a large-scale crowdsourcing knowledge base online which contains billions of relation instances and thousands of relation names, to
        distantly supervise
        Wikipedia corpus. The basic alignment assumption of this work is that if a pair of entities participate in a relation,
        all sentences
        that mention these entities are labeled by that relation name. Then we can extract a variety of textual features and learn a multi-class logistic regression classifier. Inspired by multi-instance learning
        [17]
        , Riedel et al.
        [22]
        relaxed the strong assumption and replaced
        all sentences
        with
        at least one sentence
        . Hoffmann et al.
        [13]
        pointed out that many entity pairs have more than one relation. They extended the multi-instance learning framework
        [22]
        to the multi-label circumstance. Surdeanu et al.
        [24]
        proposed a novel approach to multi-instance multi-label learning for relation extraction, which jointly modeled all the sentences in texts and all labels in knowledge bases for a given entity pair.
Other literatures
        [25, 18, 27, 26]
        addressed more specific issues, like how to construct the negative class in learning or how to adopt more information, such as name entity tags, to improve the performance.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Our work is more relevant to Riedel et al.’s
        [21]
        which considered the task as a matrix factorization problem. Their approach is composed of several models, such as PCA
        [7]
        and collaborative filtering
        [15]
        . However, they did not concern about the data noise brought by the basic assumption of distant supervision.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Model
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We apply a new technique in the field of applied mathematics, i.e., low-rank matrix completion with convex optimization. The breakthrough work on this topic was made by Candès and Recht
        [5]
        who proved that most low-rank matrices can be perfectly recovered from an incomplete set of entries. This promising theory has been successfully applied on many active research areas, such as computer vision
        [4]
        , recommender system
        [20]
        and system controlling
        [9]
        .
Our models for relation extraction are based on the theoretic framework proposed by Goldberg et al.
        [10]
        , which formulated the multi-label transductive learning as a matrix completion problem. The new framework for classification enhances the robustness to data noise by penalizing different cost functions for features and labels.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Formulation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         Suppose that we have built a training corpus for relation classification with
         n
         items (entity pairs),
         d
         -dimensional textual features, and
         t
         labels (relations), based on the basic alignment assumption proposed by Mintz et al.
         [19]
         . Let
         Xt⁢r⁢a⁢i⁢n∈ℝn×d
         and
         Yt⁢r⁢a⁢i⁢n∈ℝn×t
         denote the feature matrix and the label matrix for training, respectively. The linear classifier we adopt aims to explicitly learn the weight matrix
         𝐖∈ℝd×t
         and the bias column vector
         𝐛∈ℝt×1
         with the constraint of minimizing the loss function
         l
         ,
        </p>
        arg⁢min𝐖,𝐛l⁢(Yt⁢r⁢a⁢i⁢n,[𝟏Xt⁢r⁢a⁢i⁢n]⁢[𝐛T𝐖]),

(1)
        <p class="ltx_p">
         where
         1
         is the all-one column vector.
Then we can predict the label matrix
         Yt⁢e⁢s⁢t∈ℝm×t
         of
         m
         testing items with respect to the feature matrix
         Xt⁢e⁢s⁢t∈ℝm×d
         .
Let
        </p>
        𝐙=[Xt⁢r⁢a⁢i⁢nYt⁢r⁢a⁢i⁢nXt⁢e⁢s⁢tYt⁢e⁢s⁢t].
        <p class="ltx_p">
         This linear classification problem can be transformed into completing the unobservable entries in
         Yt⁢e⁢s⁢t
         by means of the observable entries in
         Xt⁢r⁢a⁢i⁢n
         ,
         Yt⁢r⁢a⁢i⁢n
         and
         Xt⁢e⁢s⁢t
         ,
based on the assumption that the rank of matrix
         𝐙∈ℝ(n+m)×(d+t)
         is low. The model can be written as,
        </p>
        arg⁢min𝐙∈ℝ(n+m)×(d+t)rank(𝐙)s.t.∀(i,j)∈ΩX,zi⁢j=xi⁢j,(1≤i≤n+m,1≤j≤d),∀(i,j)∈ΩY,zi⁢(j+d)=yi⁢j,(1≤i≤n,1≤j≤t),

(2)
        <p class="ltx_p">
         where we use
         ΩX
         to represent the index set of observable feature entries in
         Xt⁢r⁢a⁢i⁢n
         and
         Xt⁢e⁢s⁢t
         , and
         ΩY
         to denote the index set of observable label entries in
         Yt⁢r⁢a⁢i⁢n
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Formula (2) is usually impractical for real problems as the entries in the matrix
         𝐙
         are corrupted by noise. We thus define
        </p>
        𝐙=𝐙*+𝐄,
        <p class="ltx_p">
         where
         𝐙*
         as the underlying low-rank matrix
        </p>
        𝐙*=[X*Y*]=[Xt⁢r⁢a⁢i⁢n*Yt⁢r⁢a⁢i⁢n*Xt⁢e⁢s⁢t*Yt⁢e⁢s⁢t*],
        <p class="ltx_p">
         and
         E
         is the error matrix
        </p>
        𝐄=[EXt⁢r⁢a⁢i⁢nEYt⁢r⁢a⁢i⁢nEXt⁢e⁢s⁢t0].
        <p class="ltx_p">
         The rank function in Formula (2) is a non-convex function that is difficult to be optimized. The surrogate of the function can be the convex nuclear norm
         ||𝐙||*=∑σk⁢(𝐙)
         [5]
         , where
         σk
         is the
         k
         -
         t⁢h
         largest singular value of
         𝐙
         . To tolerate the noise entries in the error matrix
         𝐄
         , we minimize the cost functions
         Cx
         and
         Cy
         for features and labels respectively, rather than using the hard constraints in Formula (2).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         According to Formula (1),
         𝐙*∈ℝ(n+m)×(d+t)
         can be represented as
         [X*,𝐖⁢X*]
         instead of
         [X*,Y*]
         , by explicitly modeling the bias vector
         𝐛
         . Therefore, this convex optimization model is called
         DRMC-b
         ,
        </p>
        arg⁢min𝐙,𝐛μ⁢||𝐙||*+1|ΩX|⁢∑(i,j)∈ΩXCx⁢(zi⁢j,xi⁢j)+λ|ΩY|⁢∑(i,j)∈ΩYCy⁢(zi⁢(j+d)+bj,yi⁢j),

(3)
        <p class="ltx_p">
         where
         μ
         and
         λ
         are the positive trade-off weights. More specifically, we minimize the nuclear norm
         ||𝐙||*
         via employing the regularization terms, i.e., the cost functions
         Cx
         and
         Cy
         for features and labels.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         If we implicitly model the bias vector
         𝐛
         ,
         𝐙*∈ℝ(n+m)×(1+d+t)
         can be denoted by
         [𝟏,X*,𝐖′⁢X*]
         instead of
         [X*,Y*]
         , in which
         𝐖′
         takes the role of
         [𝐛T;𝐖]
         in DRMC-b. Then we derive another optimization model called
         DRMC-1
         ,
        </p>
        arg⁢min𝐙μ||𝐙||*+1|ΩX|∑(i,j)∈ΩXCx(zi⁢(j+1),xi⁢j)+λ|ΩY|∑(i,j)∈ΩYCy(zi⁢(j+d+1),yi⁢j)s.t.𝐙(:,1)=𝟏,

(4)
        <p class="ltx_p">
         where
         𝐙(:,1)
         denotes the first column of
         𝐙
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         For our relation classification task, both features and labels are binary. We assume that the actual entry
         u
         belonging to the underlying matrix
         𝐙*
         is randomly generated via a sigmoid function
         [14]
         :
         Pr(u|v)=1/(1+e-u⁢v)
         , given the observed binary entry
         v
         from the observed sparse matrix
         𝐙
         . Then, we can apply the log-likelihood cost function to measure the conditional probability and derive the
         logistic cost function
         for
         Cx
         and
         Cy
         ,
        </p>
        C(u,v)=-logPr(u|v)=log(1+e-u⁢v),
       </div>
       <div class="ltx_para" id="S3.SS1.p6">
        <p class="ltx_p">
         After completing the entries in
         Yt⁢e⁢s⁢t
         , we adopt the sigmoid function to calculate the conditional probability of relation
         rj
         , given entity pair
         pi
         pertaining to
         yi⁢j
         in
         Yt⁢e⁢s⁢t
         ,
        </p>
        Pr(rj|pi)=11+e-yi⁢j,yi⁢j∈Yt⁢e⁢s⁢t.
        <p class="ltx_p">
         Finally, we can achieve Top-N predicted relation instances via ranking the values of
         Pr(rj|pi)
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
       Algorithm
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The matrix rank minimization problem is NP-hard. Therefore, Candés and Recht
        [5]
        suggested to use a convex relaxation, the nuclear norm minimization instead. Then, Ma et al.
        [16]
        proposed the fixed point continuation (FPC) algorithm which is fast and robust. Moreover, Goldfrab and Ma
        [11]
        proved the convergence of the FPC algorithm for solving the nuclear norm minimization problem. We thus adopt and modify the algorithm aiming to find the optima for our noise-tolerant models, i.e., Formulae (3) and (4).
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Fixed point continuation for DRMC-b
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Algorithm 1 describes the modified FPC algorithm for solving DRMC-b, which contains two steps for each iteration,
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Gradient step:
         In this step, we infer the matrix gradient
         g⁢(𝐙)
         and bias vector gradient
         g⁢(𝐛)
         as follows,
        </p>
        g⁢(zi⁢j)={1|ΩX|⁢-xi⁢j1+exi⁢j⁢zi⁢j,(i,j)∈ΩXλ|ΩY|⁢-yi⁢(j-d)1+eyi⁢(j-d)⁢(zi⁢j+bj),(i,j-d)∈ΩY0,o⁢t⁢h⁢e⁢r⁢w⁢i⁢s⁢e
        <p class="ltx_p">
         and
        </p>
        g⁢(bj)=λ|ΩY|⁢∑i:(i,j)∈ΩY-yi⁢j1+eyi⁢j⁢(zi⁢(j+d)+bj).
        <p class="ltx_p">
         We use the gradient descents
         𝐀=𝐙-τz⁢g⁢(𝐙)
         and
         𝐛=𝐛-τb⁢g⁢(𝐛)
         to gradually find the global minima of the cost function terms in Formula (3), where
         τz
         and
         τb
         are step sizes.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         Shrinkage step:
         The goal of this step is to minimize the nuclear norm
         ||𝐙||*
         in Formula (3). We perform the singular value decomposition (SVD)
         [12]
         for
         𝐀
         at first, and then cut down each singular value. During the iteration, any negative value in
         𝚺-τ𝐳⁢μ
         is assigned by zero, so that the rank of reconstructed matrix
         𝐙
         will be reduced, where
         𝐙=𝐔⁢m⁢a⁢x⁢(𝚺-τ𝐳⁢μ,0)⁢𝐕𝐓
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         FPC algorithm for solving DRMC-b
         Initial matrix
         𝐙𝟎
         , bias
         𝐛𝟎
         ; Parameters
         μ,λ
         ;
         Step sizes
         τz,τb
         .
         <span class="ltx_rule" style="width:186.5pt;height:0.4pt;background:black;display:inline-block;">
         </span>
         Set
         𝐙=𝐙𝟎
         ,
         𝐛=𝐛𝟎.
         <math alttext="\mu=\mu_{1}&gt;\mu_{2}&gt;...&gt;\mu_{F}" class="ltx_Math" display="inline" id="S4.SS1.p4.m7" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            μ
           </mi>
           <mo>
            =
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mn>
             1
            </mn>
           </msub>
           <mo>
            &gt;
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mn>
             2
            </mn>
           </msub>
           <mo>
            &gt;
           </mo>
           <mi mathvariant="normal">
            …
           </mi>
           <mo>
            &gt;
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mi>
             F
            </mi>
           </msub>
          </mrow>
         </math>
         relative error
         &gt;ε
         Gradient step:
         <math alttext="{\bf A}={\bf Z}-\tau_{z}g({\bf Z}),{\bf b}={\bf b}-\tau_{b}g({\bf b})." class="ltx_Math" display="inline" id="S4.SS1.p4.m9" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mrow>
             <mi>
              𝐀
             </mi>
             <mo>
              =
             </mo>
             <mrow>
              <mi>
               𝐙
              </mi>
              <mo>
               -
              </mo>
              <mrow>
               <msub>
                <mi>
                 τ
                </mi>
                <mi>
                 z
                </mi>
               </msub>
               <mo>
                ⁢
               </mo>
               <mi>
                g
               </mi>
               <mo>
                ⁢
               </mo>
               <mrow>
                <mo>
                 (
                </mo>
                <mi>
                 𝐙
                </mi>
                <mo>
                 )
                </mo>
               </mrow>
              </mrow>
             </mrow>
            </mrow>
            <mo>
             ,
            </mo>
            <mrow>
             <mi>
              𝐛
             </mi>
             <mo>
              =
             </mo>
             <mrow>
              <mi>
               𝐛
              </mi>
              <mo>
               -
              </mo>
              <mrow>
               <msub>
                <mi>
                 τ
                </mi>
                <mi>
                 b
                </mi>
               </msub>
               <mo>
                ⁢
               </mo>
               <mi>
                g
               </mi>
               <mo>
                ⁢
               </mo>
               <mrow>
                <mo>
                 (
                </mo>
                <mi>
                 𝐛
                </mi>
                <mo>
                 )
                </mo>
               </mrow>
              </mrow>
             </mrow>
            </mrow>
           </mrow>
           <mo>
            .
           </mo>
          </mrow>
         </math>
         Shrinkage step:
         <math alttext="{\bf U}{\bf\Sigma}{\bf V^{T}}=\text{SVD}({\bf A})" class="ltx_Math" display="inline" id="S4.SS1.p4.m10" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             𝐔
            </mi>
            <mo>
             ⁢
            </mo>
            <mi>
             𝚺
            </mi>
            <mo>
             ⁢
            </mo>
            <msup>
             <mi>
              𝐕
             </mi>
             <mi>
              𝐓
             </mi>
            </msup>
           </mrow>
           <mo>
            =
           </mo>
           <mrow>
            <mtext>
             SVD
            </mtext>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mi>
              𝐀
             </mi>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         ,
         <math alttext="{\bf Z}={\bf U}~{}max({\bf\Sigma-\tau_{z}\mu},0)~{}{\bf V^{T}}." class="ltx_Math" display="inline" id="S4.SS1.p4.m11" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             𝐙
            </mi>
            <mo>
             =
            </mo>
            <mrow>
             <mpadded width="+3.3pt">
              <mi>
               𝐔
              </mi>
             </mpadded>
             <mo>
              ⁢
             </mo>
             <mi>
              m
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              a
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              x
             </mi>
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
                 𝚺
                </mi>
                <mo>
                 -
                </mo>
                <mrow>
                 <msub>
                  <mi>
                   τ
                  </mi>
                  <mi>
                   𝐳
                  </mi>
                 </msub>
                 <mo>
                  ⁢
                 </mo>
                 <mi>
                  μ
                 </mi>
                </mrow>
               </mrow>
               <mo>
                ,
               </mo>
               <mn>
                0
               </mn>
              </mrow>
              <mo>
               )
              </mo>
             </mrow>
             <mo>
              ⁢
             </mo>
             <msup>
              <mi>
               𝐕
              </mi>
              <mi>
               𝐓
              </mi>
             </msup>
            </mrow>
           </mrow>
           <mo>
            .
           </mo>
          </mrow>
         </math>
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         <span class="ltx_rule" style="width:186.5pt;height:0.4pt;background:black;display:inline-block;">
         </span>
         <span class="ltx_ERROR undefined">
          \ENSURE
         </span>
         Completed Matrix
         Z
         , bias
         b
         . 

To accelerate the convergence, we use a continuation method to improve the speed.
         μ
         is initialized by a large value
         μ1
         , thus resulting in the fast reduction of the rank at first. Then the convergence slows down as
         μ
         decreases while obeying
         μk+1=m⁢a⁢x⁢(μk⁢ημ,μF)
         .
         μF
         is the final value of
         μ
         , and
         ημ
         is the decay parameter.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p6">
        <p class="ltx_p">
         For the stopping criteria in inner iterations, we define the
         relative error
         to measure the residual of matrix
         𝐙
         between two successive iterations,
        </p>
        ||𝐙k+1-𝐙k||Fm⁢a⁢x⁢(1,||𝐙k||F)≤ε,
        <p class="ltx_p">
         where
         ε
         is the convergence threshold.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Fixed point continuation for DRMC-1
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Algorithm 2 is similar to Algorithm 1 except for two differences. First, there is no bias vector
         b
         . Second, a projection step is added to enforce the first column of matrix
         Z
         to be
         1
         . In addition, The matrix gradient
         g⁢(𝐙)
         for DRMC-1 is
        </p>
        g⁢(zi⁢j)={1|ΩX|⁢-xi⁢(j-1)1+exi⁢(j-1)⁢zi⁢j,(i,j-1)∈ΩXλ|ΩY|⁢-yi⁢(j-d-1)1+eyi⁢(j-d-1)⁢zi⁢j,(i,j-d-1)∈ΩY0,o⁢t⁢h⁢e⁢r⁢w⁢i⁢s⁢e.
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         FPC algorithm for solving DRMC-1
         Initial matrix
         𝐙𝟎
         ; Parameters
         μ,λ
         ;
         Step sizes
         τz
         .
         <span class="ltx_rule" style="width:186.5pt;height:0.4pt;background:black;display:inline-block;">
         </span>
         Set
         𝐙=𝐙𝟎.
         <math alttext="\mu=\mu_{1}&gt;\mu_{2}&gt;...&gt;\mu_{F}" class="ltx_Math" display="inline" id="S4.SS2.p2.m5" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mi>
            μ
           </mi>
           <mo>
            =
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mn>
             1
            </mn>
           </msub>
           <mo>
            &gt;
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mn>
             2
            </mn>
           </msub>
           <mo>
            &gt;
           </mo>
           <mi mathvariant="normal">
            …
           </mi>
           <mo>
            &gt;
           </mo>
           <msub>
            <mi>
             μ
            </mi>
            <mi>
             F
            </mi>
           </msub>
          </mrow>
         </math>
         relative error
         &gt;ε
         Gradient step:
         𝐀=𝐙-τz⁢g⁢(𝐙).
         Shrinkage step:
         <math alttext="{\bf U}{\bf\Sigma}{\bf V^{T}}=\text{SVD}({\bf A})" class="ltx_Math" display="inline" id="S4.SS2.p2.m8" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             𝐔
            </mi>
            <mo>
             ⁢
            </mo>
            <mi>
             𝚺
            </mi>
            <mo>
             ⁢
            </mo>
            <msup>
             <mi>
              𝐕
             </mi>
             <mi>
              𝐓
             </mi>
            </msup>
           </mrow>
           <mo>
            =
           </mo>
           <mrow>
            <mtext>
             SVD
            </mtext>
            <mo>
             ⁢
            </mo>
            <mrow>
             <mo>
              (
             </mo>
             <mi>
              𝐀
             </mi>
             <mo>
              )
             </mo>
            </mrow>
           </mrow>
          </mrow>
         </math>
         ,
         <math alttext="{\bf Z}={\bf U}~{}max({\bf\Sigma-\tau_{z}\mu},0)~{}{\bf V^{T}}." class="ltx_Math" display="inline" id="S4.SS2.p2.m9" xmlns="http://www.w3.org/1998/Math/MathML">
          <mrow>
           <mrow>
            <mi>
             𝐙
            </mi>
            <mo>
             =
            </mo>
            <mrow>
             <mpadded width="+3.3pt">
              <mi>
               𝐔
              </mi>
             </mpadded>
             <mo>
              ⁢
             </mo>
             <mi>
              m
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              a
             </mi>
             <mo>
              ⁢
             </mo>
             <mi>
              x
             </mi>
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
                 𝚺
                </mi>
                <mo>
                 -
                </mo>
                <mrow>
                 <msub>
                  <mi>
                   τ
                  </mi>
                  <mi>
                   𝐳
                  </mi>
                 </msub>
                 <mo>
                  ⁢
                 </mo>
                 <mi>
                  μ
                 </mi>
                </mrow>
               </mrow>
               <mo>
                ,
               </mo>
               <mn>
                0
               </mn>
              </mrow>
              <mo>
               )
              </mo>
             </mrow>
             <mo>
              ⁢
             </mo>
             <msup>
              <mi>
               𝐕
              </mi>
              <mi>
               𝐓
              </mi>
             </msup>
            </mrow>
           </mrow>
           <mo>
            .
           </mo>
          </mrow>
         </math>
         Projection step:
         𝐙(:,1)=1.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         <span class="ltx_rule" style="width:186.5pt;height:0.4pt;background:black;display:inline-block;">
         </span>
         <span class="ltx_ERROR undefined">
          \ENSURE
         </span>
         Completed Matrix
         Z
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In order to conduct reliable experiments, we adjust and estimate the parameters for our approaches, DRMC-b and DRMC-1, and compare them with other four kinds of landmark methods
        [19, 13, 24, 21]
        on two public datasets.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Dataset
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         The two widely used datasets that we adopt are both automatically generated by aligning Freebase to New York Times corpora.
The first dataset
         , NYT’10, was developed by Riedel et al.
         [22]
         , and also used by Hoffmann et al.
         [13]
         and Surdeanu et al.
         [24]
         . Three kinds of features, namely, lexical, syntactic and named entity tag features, were extracted from relation mentions.
The second dataset
         , NYT’13, was also released by Riedel et al.
         [21]
         , in which they only regarded the lexicalized dependency path between two entities as features.
Table 1 shows that the two datasets differ in some main attributes. More specifically, NYT’10 contains much higher dimensional features than NYT’13, whereas fewer training and testing items.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Parameter setting
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         In this part, we address the issue of setting parameters: the trade-off weights
         μ
         and
         λ
         , the step sizes
         τz
         and
         τb
         , and the decay parameter
         ημ
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         We set
         λ=1
         to make the contribution of the cost function terms for feature and label matrices equal in Formulae (3) and (4).
         μ
         is assigned by a series of values obeying
         μk+1=m⁢a⁢x⁢(μk⁢ημ,μF)
         .
We follow the suggestion in
         [10]
         that
         μ
         starts at
         σ1⁢ημ
         , and
         σ1
         is the largest singular value of the matrix
         Z
         . We set
         ημ=0.01
         . The final value of
         μ
         , namely
         μF
         , is equal to
         0.01
         .
Ma et al.
         [16]
         revealed that as long as the non-negative step sizes satisfy
         τz&lt;m⁢i⁢n⁢(4⁢|ΩY|λ,|ΩX|)
         and
         τb&lt;4⁢|ΩY|λ⁢(n+m)
         , the FPC algorithm will guarantee to converge to a global optimum. Therefore, we set
         τz=τb=0.5
         to satisfy the above constraints on both two datasets.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Rank estimation
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         Even though the FPC algorithm converges in iterative fashion, the value of
         ε
         varying with different datasets is difficult to be decided. In practice, we record the rank of matrix
         Z
         at each round of iteration until it converges at a rather small threshold
         ε=10-4
         . The reason is that we suppose the optimal low-rank representation of the matrix
         Z
         conveys the truly effective information about underlying semantic correlation between the features and the corresponding labels.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         We use the five-fold cross validation on the validation set and evaluate the performance on each fold with different ranks. At each round of iteration, we gain a recovered matrix and average the F1
         scores from Top-5 to Top-all predicted relation instances to measure the performance. Figure 3 illustrates the curves of average F1 scores. After recording the rank associated with the highest F1 score on each fold, we compute the mean and the standard deviation to estimate the range of optimal rank for testing. Table 2 lists the range of optimal ranks for DRMC-b and DRMC-1 on NYT’10 and NYT’13.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         On both two datasets, we observe an identical phenomenon that the performance gradually increases as the rank of the matrix declines before reaching the optimum. However, it sharply decreases if we continue reducing the optimal rank. An intuitive explanation is that the high-rank matrix contains much noise and the model tends to be overfitting, whereas the matrix of excessively low rank is more likely to lose principal information and the model tends to be underfitting.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Method Comparison
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         Firstly, we conduct experiments to compare our approaches with Mintz-09
         [19]
         , MultiR-11
         [13]
         , MIML-12 and MIML-at-least-one-12
         [24]
         on NYT’10 dataset. Surdeanu et al.
         [24]
         released the open source code
         to reproduce the experimental results on those previous methods. Moreover, their programs can control the feature sparsity degree through a threshold
         θ
         which filters the features that appears less than
         θ
         times. They set
         θ=5
         in the original code by default. Therefore, we follow their settings and adopt the same way to filter the features. In this way, we guarantee the fair comparison for all methods. Figure 4 (a) shows that our approaches achieve the significant improvement on performance.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <p class="ltx_p">
         We also perform the experiments to compare our approaches with the state-of-the-art NFE-13
         [21]
         and its sub-methods (N-13, F-13 and NF-13) on NYT’13 dataset. Figure 4 (b) illustrates that our approaches still outperform the state-of-the-art methods.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p3">
        <p class="ltx_p">
         In practical applications, we also concern about the precision on Top-N predicted relation instances. Therefore, We compare the precision of Top-100s, Top-200s and Top-500s for DRMC-1, DRMC-b and the state-of-the-art method NFE-13
         [21]
         . Table 3 shows that DRMC-b and DRMC-1 achieve 24.0% and 26.6% precision increments on average, respectively.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Discussion
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        We have mentioned that the basic alignment assumption of distant supervision
        [19]
        tends to generate noisy (noisy features and incomplete labels) and sparse (sparse features) data. In this section, we discuss how our approaches tackle these natural flaws.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Due to the noisy features and incomplete labels, the underlying low-rank data matrix with truly effective information tends to be corrupted and the rank of observed data matrix can be extremely high. Figure 5 demonstrates that the ranks of data matrices are approximately 2,000 for the initial optimization of DRMC-b and DRMC-1. However, those high ranks result in poor performance. As the ranks decline before approaching the optimum, the performance gradually improves, implying that our approaches filter the noise in data and keep the principal information for classification via recovering the underlying low-rank data matrix.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Furthermore, we discuss the influence of the feature sparsity for our approaches and the state-of-the-art methods. We relax the feature filtering threshold (
        θ=4,3,2
        ) in Surdeanu et al.’s
        [24]
        open source program to generate more sparse features from NYT’10 dataset. Figure 6 shows that our approaches consistently outperform the baseline and the state-of-the-art methods with diverse feature sparsity degrees.
Table 2 also lists the range of optimal rank for DRMC-b and DRMC-1 with different
        θ
        .
We observe that for each approach, the optimal range is relatively stable. In other words, for each approach, the amount of truly effective information about underlying semantic correlation keeps constant for the same dataset, which, to some extent, explains the reason why our approaches are robust to sparse features.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
