<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Unsupervised Solution Post Identification from Discussion Forums.
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
       Discussion forums have evolved into a dependable source of knowledge to solve common problems. However, only a minority of the posts in discussion forums are solution posts. Identifying solution posts from discussion forums, hence, is an important research problem. In this paper, we present a technique for unsupervised solution post identification leveraging a so far unexplored textual feature, that of lexical correlations between problems and solutions. We use translation models and language models to exploit lexical correlations and solution post character respectively. Our technique is designed to not rely much on structural features such as post metadata since such features are often not uniformly available across forums. Our clustering-based iterative solution identification approach based on the EM-formulation performs favorably in an empirical evaluation, beating the only unsupervised solution identification technique from literature by a very large margin. We also show that our unsupervised technique is competitive against methods that require supervision, outperforming one such technique comfortably.
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
        Discussion forums have become a popular knowledge source for finding solutions to common problems. StackOverflow
        , a popular discussion forum for programmers is among the top-100 most visited sites globally
        . Now, there are discussion forums for almost every major product ranging from automobiles
        to gadgets such as those of Mac
        or Samsung
        . These typically start with a registered user posting a question/problem
        to which other users respond. Typical response posts include solutions or clarification requests, whereas feedback posts form another major category of forum posts. As is the case with any community of humans, discussion forums have their share of inflammatory remarks too. Mining problem-solution pairs from discussion forums has attracted much attention from the scholarly community in the recent past. Since the first post most usually contains the problem description, identifying its solutions from among the other posts in the thread has been the focus of many recent efforts (e.g.,
        [8, 9]
        ). Extracting problem-solution pairs from forums enables the usage of such knowledge in knowledge reuse frameworks such as case-based reasoning
        [11]
        that use problem-solution pairs as raw material. In this paper, we address the problem of unsupervised solution post identification
        from discussion forums.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Among the first papers to address the solution identification problem was the unsupervised approach proposed by
        [4]
        . It employs a graph propagation method that prioritizes posts that are (a) more similar to the problem post, (b) more similar to other posts, and (c) authored by a more authoritative user, to be labeled as solution posts. Though seen to be effective in identifying solutions from travel forums, the first two assumptions, (a) and (b), were seen to be not very reliable in solution identification in other kinds of discussion boards.
        [3]
        reports a study that illustrates that non-solution posts are, on an average, as similar to the problem as solution posts in technical forums. The second assumption (i.e., (b) above) was also not seen to be useful in discussion forums since posts that are highly similar to other posts were seen to be complaints, repetitive content being more pervasive among complaint posts than solutions
        [2]
        . Having exhausted the two obvious textual features for solution identification, subsequent approaches have largely used the presence of lexical cues signifying solution-like narrative (e.g., instructive narratives such as
        ”check the router for any connection issues”
        ) as the primary content-based feature for solution identification.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        All solution identification approaches since
        [4]
        have used supervised methods that require training data in the form of labeled solution and non-solution posts. The techniques differ from one another mostly in the non-textual features that are employed in representing posts. A variety of high precision assumptions such as
        solution post typically follows a problem post
        [15]
        ,
        solution posts are likely to be within the first few posts
        ,
        solution posts are likely to have been acknowledged by the problem post author
        [3]
        ,
        users with high authoritativeness are likely to author solutions
        [9]
        , and so on have been seen to be useful in solution identification. Being supervised methods, the above assumptions are implicitly factored in by including the appropriate feature (e.g., post position in thread) in the feature space so that the learner may learn the correlation (e.g., solution posts typically are among the first few posts) using the training data. Though such assumptions on structural features, if generic enough, may be built into unsupervised techniques to aid solution identification, the variation in availability of such features across forums limits the usage of models that rely heavily on structural features. For example, some forums employ chronological order based flattening of threads
        [16]
        making reply-to information unavailable; models that harness reply-to features would then have limited utility on identifying solutions within such flattened threads. On medical forums, privacy considerations may force forum data to be dumped without author information, making a host of author-id based features unavailable. On datasets that contain data from across forums, the model may have to be aware of the absence of certain features in subsets of the data, or be modeled using features that are available on all threads.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Our Contribution:
        We propose an unsupervised method for solution identification. The cornerstone of our technique is the usage of a hitherto unexplored textual feature,
        lexical correlations between problems and solutions
        , that is exploited along with language model based characterization of solution posts. We model the lexical correlation and solution post character using regularized translation models and unigram language models respectively. To keep our technique applicable across a large variety of forums with varying availability of non-textual features, we design it to be able to work with
        minimal availability of non-textual features
        . In particular, we show that by using post position as the only non-textual feature, we are able to achieve accuracies comparable to supervision-based approaches that use many structural features
        [2]
        .
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
        In this section, we provide a brief overview of previous work related to our problem. Though most of the answer/solution identification approaches proposed so far in literature are supervised methods that require a labeled training corpus, there are a few that require limited or no supervision. Table
        1
        provides an overview of some of the more recent solution identification techniques from literature, with a focus on some features that we wish to highlight. The common observation that most problem-solving discussion threads have a problem description in the first post has been explicitly factored into many techniques; knowing the problem/question is important for solution identification since author relations between problem and other posts provide valuable cues for solution identification. Most techniques use a variety of such features as noted in Section
        1
        . SVMs have been the most popular method for supervised and semi-supervised learning for the task of solution identification.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Of particular interest to us are approaches that use limited or no supervision, since we focus on unsupervised solution identification in this paper. The
        only
        unsupervised approach for the task, that from
        [4]
        , uses a graph propagation method on a graph modeled using posts as vertices, and relies on the assumptions that posts that bear high similarity to the problem and other posts and those authored by authoritative users are more likely to be solution posts. Some of those assumptions, as mentioned in Section
        1
        , were later found to be not generalizable to beyond travel forums. The semi-supervised approach presented in
        [2]
        uses a few labeled threads to bootstrap SVM based learners which are then co-trained in an iterative fashion. In addition to various features explored in literature, they use acknowledgement modeling so that posts that have been acknowledged positively may be favored for being labeled as solutions.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        We will use translation and language models in our method for solution identification. Usage of translation models for modeling the correlation between textual problems and solutions have been explored earlier starting from the answer retrieval work in
        [18]
        where new queries were conceptually expanded using the translation model to improve retrieval. Translation models were also seen to be useful in segmenting incident reports into the problem and solution parts
        [5]
        ; we will use an adaptation of the generative model presented therein, for our solution extraction formulation. Entity-level translation models were recently shown to be useful in modeling correlations in QA archives
        [17]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Problem Definition
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Let a thread
        𝒯
        from a discussion forum be made up of
        t
        posts. Since we assume, much like many other earlier papers, that the first post is the problem post, the task is to identify which among the remaining
        t-1
        posts are solutions. There could be multiple (most likely, different) solutions within the same thread. We may now model the thread
        𝒯
        as
        t-1
        post pairs, each pair having the problem post as the first element, and one of the
        t-1
        remaining posts (i.e., reply posts in
        𝒯
        ) as the second element. Let
        𝒞={(p1,r1),(p2,r2),…,(pn,rn)}
        be the set of such problem-reply pairs from across threads in the discussion forum. We are interested in finding a subset
        𝒞′
        of
        𝒞
        such that most of the pairs in
        𝒞′
        are problem-solution pairs, and most of those in
        𝒞-𝒞′
        are not so. In short, we would like to find problem-solution pairs from
        𝒞
        such that the F-measure
        for solution identification is maximized.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Our Approach
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        The Correlation Assumption
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Central to our approach is the assumption of lexical correlation between the problem and solution texts. At the word level, this translates to assuming that there exist word pairs such that the presence of the first word in the problem part predicts the presence/absence of the second word in the solution part well. Though not yet harnessed for solution identification, the correlation assumption is not at all novel. Infact, the assumption that similar problems have similar solutions (of which the correlation assumption is an offshoot) forms the foundation of case-based reasoning systems
         [11]
         , a kind of knowledge reuse systems that could be the natural consumers of problem-solution pairs mined from forums. The usage of translation models in QA retrieval
         [18, 17]
         and segmentation
         [5]
         were also motivated by the correlation assumption. We use an IBM Model 1 translation model
         [1]
         in our technique; simplistically, such a model
         m
         may be thought of as a 2-d associative array where the value
         m⁢[w1]⁢[w2]
         is directly related to the probability of
         w1
         occuring in the problem when
         w2
         occurs in the solution.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Generative model for Solution Posts
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         Consider a unigram language model
         𝒮S
         that models the lexical characteristics of solution posts, and a translation model
         𝒯S
         that models the lexical correlation between problems and solutions. Our generative model models the reply part of a
         (p,r)
         pair (in which
         r
         is a solution) as being generated from the statistical models in
         {𝒮S,𝒯S}
         as follows.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            For each word
            ws
            occuring in
            r
            ,
           </p>
           <ol class="ltx_enumerate" id="I1.I1">
            <li class="ltx_item" id="I1.I1.i1" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_enumerate">
              (a)
             </span>
             <div class="ltx_para" id="I1.I1.i1.p1">
              <p class="ltx_p">
               Choose
               z∼U⁢(0,1)
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I1.I1.i2" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_enumerate">
              (b)
             </span>
             <div class="ltx_para" id="I1.I1.i2.p1">
              <p class="ltx_p">
               If
               z≤λ
               , Choose
               w∼M⁢u⁢l⁢t⁢(𝒮S)
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I1.I1.i3" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_enumerate">
              (c)
             </span>
             <div class="ltx_para" id="I1.I1.i3.p1">
              <p class="ltx_p">
               Else, Choose
               w∼M⁢u⁢l⁢t⁢(𝒯Sp)
              </p>
             </div>
            </li>
           </ol>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         where
         𝒯Sp
         denotes the multionomial distribution obtained from
         𝒯S
         conditioned over the words in the post
         p
         ; this is obtained by assigning each candidate solution word
         w
         a weight equal to
         a⁢v⁢g⁢{𝒯S⁢[w′]⁢[w]|w′∈p}
         , and normalizing such weights across all solution words.
         In short, each solution word is assumed to be generated from the language model or the translation model (conditioned on the problem words) with a probability of λ and 1-λ respectively, thus accounting for the correlation assumption
         . The generative model above is similar to the proposal in
         [5]
         , adapted suitably for our scenario. We model non-solution posts similarly with the sole difference being that they would be sampled from the analogous models
         𝒮N
         and
         𝒯N
         that characterize behavior of non-solution posts.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         Example:
         Consider the following illustrative example of a problem and solution post:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <ul class="ltx_itemize" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            Problem:
            I am unable to surf the web on the BT public wifi.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            Solution:
            Maybe, you should try disconnecting and rejoining the network.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         Of the solution words above, generic words such as
         try
         and
         should
         could probably be explained by (i.e., sampled from) the solution language model, whereas
         disconnect
         and
         rejoin
         could be correlated well with
         surf
         and
         wifi
         and hence are more likely to be supported better by the translation model.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Clustering-based Approach
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         We propose a clustering based approach so as to cluster each of the
         (p,r)
         pairs into either the
         solution
         cluster or the
         non-solution
         cluster. The objective function that we seek to maximize is the following:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        ∑(p,r)∈𝒞{F⁢((p,r),𝒮S,𝒯S)if label((p,r))=SF⁢((p,r),𝒮N,𝒯N)if label((p,r))=N

(1)
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         F⁢((p,r),𝒮,𝒯)
         indicates the conformance of the
         (p,r)
         pair (details in Section
         4.3.1
         ) with the generative model that uses the
         𝒮
         and
         𝒯
         models as the language and translation models respectively. The clustering based approach labels each
         (p,r)
         pair as either solution (i.e.,
         S
         ) or non-solution (i.e.,
         N
         ). Since we do not know the models or the labelings to start with, we use an iterative approach modeled on the EM meta-algorithm
         [6]
         involving iterations, each comprising of an E-step followed by the M-step. For simplicity and brevity, instead of deriving the EM formulation, we illustrate our approach by making an analogy with the popular K-Means clustering
         [13]
         algorithm that also uses the EM formulation and crisp assignments of data points like we do. K-Means is a clustering algorithm that clusters objects represented as multi-dimensional points into
         k
         clusters where each cluster is represented by the centroid of all its members. Each iteration in K-Means starts off with assigning each data object to its nearest centroid, followed by re-computing the centroid vector based on the assignments made. The analogy with K-Means is illustrated in Table
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p4">
        <p class="ltx_p">
         Though the analogy in Table
         2
         serves to provide a high-level picture of our approach, the details require further exposition. In short, our approach is a 2-way clustering algorithm that uses two pairs of models,
         [𝒮S,𝒯S]
         and
         [𝒮N,𝒯N]
         , to model solution pairs and non-solution pairs respectively. At each iteration, the post-pairs are labeled as either solution (
         S
         ) or non-solution (
         N
         ) based on which pair of models they better conform to. Within the same iteration, the four models are then re-learnt using the labels and other side information. At the end of the iterations, the pairs labeled
         S
         are output as solution pairs. We describe the various details in separate subsections herein.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.1
         </span>
         E-Step: Estimating Labels
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS1.p1">
         <p class="ltx_p">
          As outlined in Table
          2
          , each
          (p,r)
          pair would be assigned to one of the classes, solution or non-solution, based on whether it conforms better with the solution models (i.e.,
          𝒮S
          &amp;
          𝒯S
          ) or non-solution models (
          𝒮N
          &amp;
          𝒯N
          ), as determined using the
          F⁢((p,r),𝒮,𝒯)
          function, i.e.,
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p2">
         l⁢a⁢b⁢e⁢l⁢((p,r))=arg⁢maxi∈{S,N}F⁢((p,r),𝒮i,𝒯i)
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p3">
         <p class="ltx_p">
          F(.)
          falls out of the generative model:
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p4">
         F⁢((p,r),𝒮,𝒯)=∏w∈rλ×𝒮⁢[w]+(1-λ)×𝒯p⁢[w]
        </div>
        <div class="ltx_para" id="S4.SS3.SSS1.p5">
         <p class="ltx_p">
          where
          𝒮⁢[w]
          denotes the probability of
          w
          from
          𝒮
          and
          𝒯p⁢[w]
          denotes the probability of
          w
          from the multinomial distribution derived from
          𝒯
          conditioned over the words in
          p
          , as in Section
          4.2
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.2
         </span>
         E-Step: Estimating Reply Word Source
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS2.p1">
         <p class="ltx_p">
          Since the language and translation models operate at the word level, the objective function entails that we let the models learn based on their fractional contribution of the words from the language and translation models. Thus, we estimate the proportional contribution of each word from the language and translation models too, in the E-step. The fractional contributions of the word
          w∈r
          in the
          (p,r)
          pair labeled as solution (i.e.,
          S
          ) is as follows:
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS2.p2">
         f𝒮S(p,r)⁢(w)=𝒮S⁢[w]𝒮S⁢[w]+𝒯Sp⁢[w]
         f𝒯S(p,r)⁢(w)=𝒯Sp⁢[w]𝒮S⁢[w]+𝒯Sp⁢[w]
        </div>
        <div class="ltx_para" id="S4.SS3.SSS2.p3">
         <p class="ltx_p">
          The fractional contributions are just the actual supports for the word
          w
          , normalized by the total contribution for the word from across the two models. Similar estimates,
          f𝒮N(p,r)(.)
          and
          f𝒮N(p,r)(.)
          are made for reply words from pairs labeled
          N
          . In our example from Section
          4.2
          , words such as
          rejoin
          are likely to get higher
          f𝒯S(p,r)(.)
          scores due to being better correlated with problem words and consequently better supported by the translation model; those such as
          try
          may get higher
          f𝒮S(p,r)(.)
          scores.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS3">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.3
         </span>
         M-Step: Learning Models
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS3.p1">
         <p class="ltx_p">
          We use the labels and reply-word source estimates from the E-step to re-learn the language and translation models in this step. As may be obvious from the ensuing discussion, those pairs labeled as solution pairs are used to learn the
          𝒮S
          and
          𝒯S
          models and those labeled as non-solution pairs are used to learn the models with subscript
          N
          . We let each reply word contribute as much to the respective language and translation models according to the estimates in Section
          4.3.2
          . In our example, if the word
          disconnect
          is assigned a source probability of
          0.9
          and
          0.1
          for the translation and language models respectively, the virtual document-pair from
          (p,r)
          that goes into the training of the respective
          𝒯
          model would assume that
          disconnect
          occurs in
          r
          with a frequency of
          0.9
          ; similarly, the respective
          𝒮
          would account for
          disconnect
          with a frequency of
          0.1
          . Though fractional word frequencies are not possible in real documents, statistical models can accomodate such fractional frequencies in a straightforward manner. The language models are learnt only over the
          r
          parts of the
          (p,r)
          pairs since they are meant to characterize reply behavior; on the other hand, translation models learn over both
          p
          and
          r
          parts to model correlation.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS3.p2">
         <p class="ltx_p">
          Regularizing the 𝒯 models:
          In our formulation, the language and translation models may be seen as competing for ”ownership” of reply words. Consider the post and reply vocabularies to be of sizes
          A
          and
          B
          respectively; then, the translation model would have
          A×B
          variables, whereas the unigram language model has only
          B
          variables. This gives the translation model an implicit edge due to having more parameters to tune to the data, putting the language models at a disadvantage. To level off the playing field, we use a regularization
          operation in the learning of the translation models. The IBM Model 1 learning process uses an internal EM approach where the E-step estimates the alignment vector for each problem word; this vector indicates the distribution of alignments of the problem word across the solution words. In our example, an example alignment vector for
          wifi
          could be:
          {r⁢e⁢j⁢o⁢i⁢n:0.4,n⁢e⁢t⁢w⁢o⁢r⁢k:0.4,d⁢i⁢s⁢c⁢o⁢n⁢n⁢e⁢c⁢t:0.1,…}
          . Our regularization method uses a parameter
          τ
          to discard the long tail in the alignment vector by resetting entries having a value
          ≤τ
          to
          0.0
          followed by re-normalizing the alignment vector to add up to 1.0. Such pruning is performed at each iteration in the learning of the translation model, so that the following M-steps learn the probability matrix according to such modified alignment vectors.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS3.p3">
         <p class="ltx_p">
          The semantics of the
          τ
          parameter may be intuitively outlined. If we would like to allow alignment vectors to allow a problem word to align with upto two reply words, we would need to set
          τ
          to a value close to
          0.5(=12)
          ; ideally though, to allow for the mass consumed by an almost inevitable long tail of very low values in the alignment vector, we would need to set it to slightly lower than
          0.5
          , say
          0.4
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS3.p4">
         <p class="ltx_p">
          [t]
          Clustering-based Solution Identification
          Input. 𝒞, a set of (p,r) pairs 
Output. 𝒞′, the set of identified solution pairs
          Initialization
          \uln. ∀(p,r)∈𝒞
\uln.  if(r.postpos=2)label((p,r))=S
\uln.  e⁢l⁢s⁢e⁢l⁢a⁢b⁢e⁢l⁢((p,r))=N
\uln. Learn 𝒮S &amp; 𝒯S using pairs labeled S
\uln. Learn 𝒮N &amp; 𝒯N using pairs labeled N
          EM Iterations
          \uln. while(notconverged∧#Iterations&lt;10)
          E-Step:
          \uln.   ∀(p,r)∈𝒞
\uln.    l⁢a⁢b⁢e⁢l⁢((p,r))=arg⁢maxiF⁢((p,r),𝒮i,𝒯i)
\uln.    ∀w∈r
\uln.     E⁢s⁢t⁢i⁢m⁢a⁢t⁢e⁢f𝒮l⁢a⁢b⁢e⁢l⁢(p,r)(p,r)⁢(w),f𝒯l⁢a⁢b⁢e⁢l⁢(p,r)(p,r)⁢(w)
          M-Step:
          \uln.   Learn 𝒮S &amp; 𝒯S from pairs labeled S
  using the f𝒮S(p,r)(.) f𝒯S(p,r)(.) estimates 
\uln.   Learn 𝒮N &amp; 𝒯N from pairs labeled N
  using the f𝒮N(p,r)(.) f𝒯N(p,r)(.) estimates
          Output
          \uln. Output (p,r) pairs from 𝒞 with 
 l⁢a⁢b⁢e⁢l⁢((p,r))=S as 𝒞′
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS4">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.4
         </span>
         Initialization
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS4.p1">
         <p class="ltx_p">
          K-Means clustering mostly initializes centroid vectors randomly; however, it is non-trivial to initialize the complex translation and language models randomly. Moreover, an initialization such that the
          𝒮S
          and
          𝒯S
          models favor the solution pairs more than the non-solution pairs is critical so that they may progressively lean towards modeling solution behaviour better across iterations. Towards this, we make use of a structural feature; in particular, adapting the hypothesis that solutions occur in the first
          N
          posts (Ref.
          [3]
          ),
          we label the pairs that have the the reply from the second post (note that the first post is assumed to be the problem post) in the thread as a solution post, and all others as non-solution posts
          . Such an initialization along with uniform reply word source probabilities is used to learn the initial estimates of the
          𝒮S
          ,
          𝒯S
          ,
          𝒮N
          and
          𝒯N
          models to be used in the E-step for the first iteration. We will show that we are able to effectively perform solution identification using our approach by exploiting just one structural feature, the post position, as above. However, we will also show that we can exploit other features as and when available, to deliver higher accuracy clusterings.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S4.SS3.SSS5">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.3.5
         </span>
         Method Summary
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS5.p1">
         <p class="ltx_p">
          The overall method comprising the steps that have been described is presented in Algorithm
          4.3.3
          . The initialization using the post position (Ref. Sec
          4.3.4
          ) is illustrated in Lines 1-5, whereas the EM-iterations form Steps 6 through 12. Of these, the E-step incorporates labeling (Line 8) as described in Sec
          4.3.1
          and reply-word source estimation (Line 10) detailed in Sec
          4.3.2
          . The models are then re-learnt in the M-Step (Lines 11-12) as outlined in Sec
          4.3.3
          . At the end of the iterations that may run up to
          10
          times if the labelings do not stabilize earlier, the pairs labeled
          S
          are output as identified solutions (Line 13).
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS5.p2">
         <p class="ltx_p">
          Time Complexity:
          Let
          n
          denote
          |𝒞|
          , and the number of unique words in each problem and reply post be
          a
          and
          b
          respectively. We will denote the vocabulary size of problem posts as
          A
          and that of reply posts as
          B
          . Learning of the language and translation models in each iteration costs
          𝒪⁢(n⁢b+B)
          and
          𝒪⁢(k′⁢(n⁢a⁢b+A⁢B))
          respectively (assuming the translation model learning runs for
          k′
          iterations). The E-step labeling and source estimation cost
          𝒪⁢(n⁢a⁢b)
          each. For
          k
          iterations of our algorithm, this leads to an overall complexity of
          𝒪⁢(k⁢k′⁢(n⁢a⁢b+A⁢B))
          .
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experimental Evaluation
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        We use a crawl of 140k threads from Apple Discussion forums
        . Out of these, 300 threads (comprising 1440 posts) were randomly chosen and each post was manually tagged as either solution or non-solution by the authors of
        [2]
        (who were kind enough to share the data with us) with an inter-annotator agreement
        of 0.71. On an average,
        40⁢%
        of replies in each thread and
        77⁢%
        of first replies were seen to be solutions, leading to an F-measure of
        53⁢%
        for our initialization heuristic. We use the F-measure
        for solution identification, as the primary evaluation measure. While we vary the various parameters separately in order to evaluate the trends, we use a dataset of 800 threads (containing the 300 labeled threads) and set
        λ=0.5
        and
        τ=0.4
        unless otherwise mentioned. Since we have only 300 labeled threads, accuracy measures are reported on those (like in
        [2]
        ). We pre-process the post data by stemming words
        [14]
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Quality Evaluation
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         In this study, we compare the performance of our method under varying settings of
         λ
         against the only unsupervised approach for solution identification from literature, that from
         [4]
         . We use an independent implementation of the technique using Kullback-Leibler Divergence
         [12]
         as the similarity measure between posts; KL-Divergence was seen to perform best in the experiments reported in
         [4]
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Table
         3
         illustrates the comparative performance on various quality metrics, of which F-Measure is typically considered most important. Our pure-LM
         setting (i.e.,
         λ=1
         ) was seen to perform up to
         6
         F-Measure points better than the pure-TM
         setting (i.e.,
         λ=0
         ), whereas the uniform mix is seen to be able to harness both to give a
         1.4
         point (i.e.,
         2.2⁢%
         ) improvement over the pure-LM case. The comparison with the approach from
         [4]
         illustrates that our method is very clearly the superior method for solution identification outperforming the former by large margins on all the evaluation measures, with the improvement on F-measure being more than
         25
         points.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         Comparison wrt Methods from [2]:
         Table
         3
         also lists the performance of SVM-based methods from
         [2]
         that use supervised information for solution identification, to help put the performance of our technique in perspective. Of the two methods therein, ANS CT is a more general method that uses two views (structural and lexical) of solutions which are then co-trained. ANS-ACK PCT is an enhanced method that requires author-id information and a means of classifying posts as acknowledgements (which is done using additional supervision); a post being acknowledged by the problem author is then used as a signal to enhance the solution-ness of a post. In the absence of author information (such as may be common in privacy-constrained domains such as medical forums) and extrinsic information to enable identify acknowledgements, ANS CT is the only technique available. Our technique is seen to outperform ANS CT by a respectable margin (
         8.6
         F-measure points) while trailing behind the enhanced ANS-ACK PCT method with a reasonably narrow
         3.8
         F-measure point margin. Thus, our unsupervised method is seen to be a strong competitor even for techniques using supervision outlined in
         [2]
         , illustrating the effectiveness of LM and TM modeling of reply posts.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Across Iterations:
         For scenarios where computation is at a premium, it is useful to know how quickly the quality of solution identification stabilizes, so that the results can be collected after fewer iterations. Figure
         1
         plots the F-measure across iterations for the run with
         λ=0.5,τ=0.4
         setting, where the F-measure is seen to stabilize in as few as 4-5 iterations. Similar trends were observed for other runs as well, confirming that the run may be stopped as early as after the fourth iteration without considerable loss in quality.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p5">
        <p class="ltx_p">
         Example Estimates from LMs and TMs:
         In order to understand the behavior of the statistical models, we took the highest 100 entries from both
         𝒮S
         and
         𝒯S
         and attempted to qualitatively evaluate semantics of the words (or word pairs) corresponding to those. Though the stemming made it hard to make sense of some entries, we present some of the understandable entries from among the top-100 in Table
         4
         . The first three entries from
         𝒯S
         deal with connection issues for which
         adaptor
         or
         guest account
         related solutions are proposed, whereas the remaining have something to do with the
         mac translator app
         and
         rebuilding
         libraries after an
         update
         . The top words from
         𝒮S
         include imperative words and words from solutions to common issues that include actions pertaining to the
         router
         or
         password
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Varying Parameter Settings
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We now analyse the performance of our approach against varying parameter settings. In particular, we vary
         λ
         and
         τ
         values and the dataset size, and experiment with some initialization variations.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Varying λ:
         λ
         is the weighting parameter that indicates the fraction of weight assigned to LMs (vis-a-vis TMs). As may be seen from Figure
         4
         , the quality of the results as measured by the F-measure is seen to peak around the middle (i.e.,
         λ=0.5
         ), and decline slowly towards either extreme, with a sharp decline at
         λ=0
         (i.e., pure-TM setting). This indicates that a uniform mix is favorable; however, if one were to choose only one type of model, usage of LMs is seen to be preferable than TMs.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         Varying τ:
         τ
         is directly related to the extent of pruning of TMs, in the regularization operation; all values in the alignment vector
         ≤τ
         are pruned. Thus, each problem word is roughly allowed to be aligned with at most
         ∼1τ
         solution words. The trends from Figure
         4
         suggests that allowing a problem word to be aligned to up to
         2.5
         solution words (i.e.,
         τ=0.4
         ) is seen to yield the best performance though the quality decline is graceful towards either side of the
         [0.1,0.5]
         range.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         Varying Data Size:
         Though more data always tends to be beneficial since statistical models benefit from redundancy, the marginal utility of additional data drops to very small levels beyond a point; we are interested in the amount of data beyond which the quality of solution identification flattens out. Figure
         4
         suggests that there is a sharp improvement in quality while increasing the amount of data from
         300
         threads (i.e.,
         1440
         (p,r)
         pairs) to 550 (
         2454
         pairs), whereas the increment is smaller when adding another 250 pairs (total of
         3400
         pairs). Beyond
         800
         threads, the F-measure was seen to flatten out rapidly and stabilize at
         ∼64⁢%
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p5">
        <p class="ltx_p">
         Initialization:
         In Apple discussion forums, posts by Apple employees that are labeled with the
         Apple employees
         tag (approximately
         ∼7⁢%
         of posts in our dataset) tend to be solutions. So are posts that are marked
         Helpful
         (
         ∼3⁢%
         of posts) by other users. Being specific to Apple forums, we did not use them for initialization in experiments so far with the intent of keeping the technique generic. However, when such posts are initialized as solutions (in addition to first replies as we did earlier), the F-score for solution identification for our technique was seen to improve slightly, to
         64.5⁢%
         (from
         64⁢%
         ). Thus, our technique is able to exploit any extra solution identifying structural features that are available.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
