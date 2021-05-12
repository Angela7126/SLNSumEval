<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Adaptive Quality Estimation for Machine Translation.
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
       The automatic estimation of machine translation (MT) output quality is a hard task in which the selection of the appropriate algorithm and the most predictive features over reasonably sized training sets plays a crucial role. When moving from controlled lab evaluations to real-life scenarios the task becomes even harder. For current MT quality estimation (QE) systems, additional complexity comes from the difficulty to model user and domain changes. Indeed, the instability of the systems with respect to data coming from different distributions calls for adaptive solutions that react to new operating conditions. To tackle this issue we propose an online framework for adaptive QE that targets reactivity and robustness to user and domain changes. Contrastive experiments in different testing conditions involving user and domain changes demonstrate the effectiveness of our approach.
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
        After two decades of steady progress, research in statistical machine translation (SMT) started to cross its path with translation industry with tangible mutual benefit. On one side, SMT research brings to the industry improved output quality and a number of appealing solutions useful to increase translators’ productivity. On the other side, the market needs suggest concrete problems to solve, providing real-life scenarios to develop and evaluate new ideas with rapid turnaround. The evolution of computer-assisted translation (CAT) environments is an evidence of this trend, shown by the increasing interest towards the integration of suggestions obtained from MT engines with those derived from translation memories (TMs).
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The possibility to speed up the translation process and reduce its costs by post-editing good-quality MT output raises interesting research challenges. Among others, these include deciding
        what
        to present as a suggestion, and
        how
        to do it in the most effective way.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In recent years, these issues motivated research on automatic QE, which addresses the problem of estimating the quality of a translated sentence given the source and without access to reference translations
        [4, 30, 22]
        . Despite the substantial progress done so far in the field and in successful evaluation campaigns
        [6, 5]
        , focusing on concrete market needs makes possible to further define the scope of research on QE. For instance, moving from controlled lab testing scenarios to real working environments poses additional constraints in terms of adaptability of the QE models to
the variable conditions of a translation job.
Such variability is due to two main reasons:
       </p>
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           The notion of MT output quality is highly subjective
           [16, 33, 34]
           . Since the quality standards of individual users may vary considerably (
           e.g.
           according to their knowledge of the source and target languages), the estimates of a static QE model trained with data collected from a group of post-editors might not fit with the actual judgements of a new user;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Each translation job has its own specificities
           (domain, complexity of the source text, average target quality). Since data from a new job may differ from those used to train the QE model, its estimates on the new instances might result to be biased or uninformative.
          </p>
         </div>
        </li>
       </ol>
       <p class="ltx_p">
        The ability of a system to self-adapt to the behaviour of specific users and domain changes is a facet of the QE problem that so far has been disregarded. To cope with these issues and deal with the erratic conditions of real-world translation workflows, we propose
        an adaptive approach to QE
        that is sensitive and robust to differences between training and test data. Along this direction, our main contribution is a framework in which QE models can be trained and can continuously evolve over time accounting for knowledge acquired from post editors’ work.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Our approach is
        based on the online learning paradigm
        and exploits a key difference between such framework and the batch learning methods currently used.
On one side, the QE models obtained with batch methods are learned exclusively from a predefined set of training examples under the assumption that they have similar characteristics with respect to the test data. This makes them suitable for controlled evaluation scenarios where such condition holds. On the other side, online learning techniques are designed to learn in a stepwise manner (either from scratch, or by refining an existing model) from new, unseen test instances by taking advantage of external feedback.
This makes them suitable for real-life scenarios where the new instances to be labelled can considerably differ from the data used to train the QE model.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        To develop our approach, different online algorithms have been embedded in the backbone of a QE system. This required the adaptation of its standard batch learning workflow to:
       </p>
       <ol class="ltx_enumerate" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           Perform online feature extraction from a source–target pair (
           i.e.
           one instance at a time instead of processing an entire training set);
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           Emit a prediction for the input instance;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           Gather user feedback for the instance (
           i.e.
           calculating a “true label” based on the amount of user post-editions);
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          4.
         </span>
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           Send the true label back to the model to update its predictions for future instances.
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        Focusing on the adaptability to user and domain changes, we report the results of comparative experiments with two online algorithms and the standard batch approach. The evaluation is carried out by measuring the global error of each algorithm on test sets featuring different degrees of similarity with the data used for training. Our results show that the sensitivity of online QE models to different distributions of training and test instances makes them more suitable than batch methods for integration in a CAT framework.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Our adaptive QE infrastructure has been released as open source. Its C++ implementation is available at
        http://hlt.fbk.eu/technologies/aqet
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        QE is generally cast as a supervised machine learning task, where a model trained from a collection of (
        source, target, label
        ) instances is used to predict labels
        for new, unseen test items
        [31]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        In the last couple of years, research in the field received a strong boost by the shared tasks organized within the WMT workshop on SMT,
        which is also the framework of our first experiment in §
        5
        . Current approaches to the tasks proposed at WMT have mainly focused on three main directions, namely:
        i)
        feature engineering, as in
        [12, 10, 11, 26]
        ,
        ii)
        model learning with a variety of classification and regression algorithms, as in
        [3, 1, 29]
        ,
and
        iii)
        feature selection as a way to overcome sparsity and overfitting issues, as in
        [29]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Being optimized to perform well on specific WMT sub-tasks and datasets, current systems reflect variations along these directions but leave important aspects of the QE problem still partially investigated or totally unexplored.
        Among these, the necessity to model the diversity of human quality judgements and correction strategies
        [16, 15]
        calls for solutions that:
        i)
        account for annotator-specific behaviour, thus being capable of learning from inherently noisy datasets produced by multiple annotators, and
        ii)
        self-adapt to changes in data distribution, learning from user feedback on new, unseen test items.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        These interconnected issues are particularly relevant in the CAT framework, where translation jobs from different domains are routed to professional translators with different idiolect, background and quality standards.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        The first aspect, modelling annotators’ individual behaviour and interdependences,
has been addressed by Cohn and Specia
        [8]
        , who explored multi-task Gaussian Processes as a way to jointly learn from the output of multiple annotations. This technique is suitable to cope with the unbalanced distribution of training instances and yields better models when heterogeneous training datasets are available.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        The second problem, the adaptability of QE models, has not been explored yet.
A common trait of all current approaches, in fact, is the reliance on batch learning techniques, which assume a “static” nature of the world where new unseen instances that will be encountered
will be similar to the training data.
        However, similarly to translation memories that incrementally store translated segments and evolve over time incorporating users style and terminology,
all components of a CAT tool (the MT engine and the mechanisms to assign quality scores to the suggested translations) should take advantage of translators feedback.
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        On the MT system side, research on adaptive approaches tailored to interactive SMT and CAT scenarios explored the online learning protocol
        [17]
        to improve various aspects of the decoding process
        [7, 23, 19, 20, 21, 2]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <p class="ltx_p">
        As regards QE models, our work represents the first investigation on incremental adaptation by exploiting users feedback to provide targeted (system, user, or project specific) quality judgements.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Online QE for CAT environments
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        When operating with advanced CAT tools, translators are presented with suggestions (either matching fragments from a translation memory or automatic translations produced by an MT system) for each sentence of a source document. Before being approved and published, translation suggestions may require different amounts of post-editing operations depending on their quality.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Each post-edition brings a wealth of dynamic knowledge about the whole translation process and the involved actors. For instance, adaptive QE components could exploit information about the distance between automatically assigned scores and the quality standards of individual translators (inferred from the amount of their corrections) to “profile” their behaviour.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The online learning paradigm fits well with this research objective. In the online framework, differently from the batch mode, the learning algorithm sequentially processes an unknown sequence of instances
        X=x1,x2,…,xn
        , returning a prediction
        p⁢(xi)
        as output at each step. Differences between
        p⁢(xi)
        and the true label
        p^⁢(xi)
        obtained as feedback are used by the learner to refine the next prediction
        p⁢(xi+1)
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        In our experiments on adaptive QE we aim to predict the quality of the suggested translations in terms of HTER, which measures the minimum edit distance between the MT output and its manually post-edited version in the [0,1] interval.
        In this scenario:
       </p>
       <ul class="ltx_itemize" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           The set of instances
           X
           is represented by (
           source, target
           ) pairs;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           The prediction
           p⁢(xi)
           is the automatically estimated HTER score;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           The true label
           p^⁢(xi)
           is the actual HTER score calculated over the target and its post-edition.
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        At each step of the process, the goal of the learner is to exploit user post-editions to reduce the difference between the predicted HTER values and the true labels for the following (
        source, target
        ) pairs.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        As depicted in Figure
        1
        , this is done as follows:
       </p>
       <ol class="ltx_enumerate" id="I4">
        <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I4.i1.p1">
          <p class="ltx_p">
           At step
           i
           , an unlabelled (
           source, target
           ) pair
           xi
           is sent to a feature extraction component. To this aim, we used an adapted version
           [27]
           of the open-source QuEst
           tool
           [32]
           . The tool, which implements a large number of features proposed by participants in the WMT QE shared tasks, has been modified to process one sentence at a time as requested for integration in a CAT environment;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I4.i2.p1">
          <p class="ltx_p">
           The extracted features are sent to an online regressor, which returns a QE prediction score
           p⁢(xi)
           in the [0,1] interval (set to 0 at the first round of the iteration);
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          3.
         </span>
         <div class="ltx_para" id="I4.i3.p1">
          <p class="ltx_p">
           Based on the post-edition done by the user, the true HTER label
           p^⁢(xi)
           is calculated by means of the TERCpp
           open source tool;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          4.
         </span>
         <div class="ltx_para" id="I4.i4.p1">
          <p class="ltx_p">
           The true label is sent back to the online algorithm for a stepwise model improvement. The updated model is then ready to process the following instance
           xi+1
           .
          </p>
         </div>
        </li>
       </ol>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        This new paradigm for QE makes it possible to:
        i)
        let the QE system learn from one point at a time without complete re-training from scratch,
        ii)
        customize the predictions of an existing QE model with respect to a specific situation (post-editor or domain), or even
        iii)
        build a QE model from scratch when training data is not available.
       </p>
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        For the sake of clarity it is worth observing that, at least in principle, a model built in a batch fashion could also be adapted to new test data. For instance, this could be done by running periodic re-training routines once a certain amount of new labelled instances has been collected (
        de facto
        mimicking an online process). Such periodic updates, however, would not represent a viable solution in the CAT framework where post-editors’ work cannot be slowed by time-consuming procedures to re-train core system components from scratch.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Evaluation framework
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        To measure the adaptation capability of different QE models, we experiment with a range of conditions defined by variable degrees of similarity between training and test data.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The degree of similarity depends on several factors: the MT engine used, the domain of the documents to be translated, and the post-editing style of individual translators. In our experiments, the degree of similarity is measured in terms of
        Δ
        HTER, which is computed as the absolute value of the difference between the average HTER of the training and test sets. Large values indicate a low similarity between training and test data and a more challenging scenario for the learning algorithms.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Experimental setup
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         In the range of possible evaluation scenarios, our experiments cover:
        </p>
        <ul class="ltx_itemize" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            One artificial setting (§
            5
            ) obtained from the WMT12 QE shared task data, in which training/test instances are arranged to reflect homogeneous distributions of the HTER labels.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            Two settings obtained from data collected with a CAT tool in real working conditions, in which different facets of the adaptive QE problem interact with each other. In the first (
            user_change
            , §
            6.1
            ), training and test data from the same domain are obtained from different users. In the second (
            user+domain_change
            , §
            6.2
            ), training and test data are obtained from different users and domains.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         For each setting, we compare an
         adaptive
         and an
         empty
         model against a system trained in
         batch
         mode. The
         adaptive
         model is built on top of an existing model created from the training data and exploits the new test instances to refine its predictions in a stepwise manner. The
         empty
         model only learns from the test set, simulating the worst condition where training data is not available. The
         batch
         model is built by learning only from the training data and is evaluated on the test set without exploiting information from the test instances.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         Each model is also compared against a common baseline for regression tasks, which is particularly relevant in settings featuring different data distributions between training and test sets. This baseline (
         μ
         henceforth) is calculated by labelling each instance of the test set with the mean HTER score of the training set. Previous works
         [25]
         demonstrated that its results can be particularly hard to beat.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Performance indicator and feature set
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         To measure the adaptability of our model to a given test set we compute the Mean Absolute Error (MAE), a metric for regression problems also used in the WMT QE shared tasks. The MAE is the average of the absolute errors
         ei=|fi-yi|
         , where
         fi
         is the prediction of the model and
         yi
         is the true value for the
         it⁢h
         instance.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         As our focus is on the algorithmic aspect, in all experiments we use the same feature set, which consists of the seventeen features proposed in
         [30]
         . This feature set, fully described in
         [6]
         , takes into account the complexity of the source sentence (
         e.g.
         number of tokens, number of translations per source word) and the fluency of the target translation (
         e.g.
         language model probabilities). The results of previous WMT QE shared tasks have shown that these baseline features are particularly competitive in the regression task
(with only few systems able to beat them at WMT12).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Online algorithms
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         In our experiments we evaluate two online algorithms, OnlineSVR
         [24]
         and Passive-Aggressive Perceptron
         [9]
         ,
         by comparing their performance with a batch learning strategy based on the Scikit-learn implementation of Support Vector Regression (SVR).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p2">
        <p class="ltx_p">
         The choice of the OnlineSVR and Passive-Aggressive (OSVR and PA henceforth) is motivated by different considerations.
From a
         performance
         point of view, as an adaptation of
         ϵ
         -SVR which proved to be one of the top performing algorithms in the regression QE tasks at WMT, OSVR seems to be the best candidate. For this reason, we use the online adaptation of
         ϵ
         -SVR proposed by
         [18]
         . The goal of OnlineSVR is to find a way to add each new sample to one of three sets (support, empty, error) maintaining the consistency of a set of conditions known as Karush-Kuhn Tucker (KKT) conditions. For each new point, OSVR starts a cycle where the samples are moved across the three sets until the KKT conditions are verified and the new point is assigned to one of the sets. If the point is identified as a support vector, the parameters of the model are updated. This allows OSVR to benefit from the prediction capability of
         ϵ
         -SVR in an online setting.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.p3">
        <p class="ltx_p">
         From a
         practical
         point of view, providing the best trade off between accuracy and computational time
         [13]
         , PA represents a good solution to meet the demand of efficiency posed by the CAT framework. For each instance
         i
         , after emitting a prediction and receiving the true label, PA computes the
         ϵ
         -insensitive hinge loss function. If its value is larger than the tolerance parameter (
         ϵ
         ), the weights of the model are updated as much as the aggressiveness parameter
         C
         allows. In contrast with OSVR, which keeps track of the most important points seen in the past (support vectors), the update of the weights is done without considering the previously processed
         i-1
         instances. Although it makes PA faster than OSVR, this is a riskier strategy because it may lead the algorithm to change the model to adapt to outlier points.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments with WMT12 data
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        The motivations for experiments with training and test data featuring homogeneous label distributions are twofold. First, since in this artificial scenario adaptation capabilities are not required for the QE component, batch methods operate in the ideal conditions (as training and test are independent and identically distributed). This makes possible to obtain from batch models the best possible performance to compare with. Second, this scenario provides the fairest conditions for such comparison because, in principle, online algorithms are not favoured by the possibility to learn from the diversity of the test instances.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        For our controlled experiments we use the WMT12 English-Spanish corpus, which consists of 2,254 source-target pairs (1,832 for training, 422 for test). The HTER labels for our regression task are calculated from the post-edited version and the target sentences provided in the dataset.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        To avoid biases in the label distribution, the WMT12 training and test data have been merged, shuffled, and eventually separated to generate three training sets of different size (200, 600, and 1500 instances), and one test set with 754 instances. For each algorithm, the training sets are used for learning the QE models, optimizing parameters (
        i.e.
        C
        ,
        ϵ
        , the kernel and its parameters for SVR and OSVR; tolerance and aggressiveness for PA) through grid search in 10-fold cross-validation.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        Evaluation is carried out by measuring the performance of the
        batch
        (learning only from the training set), the
        adaptive
        (learning from the training set and adapting to the test set), and the
        empty
        (learning from scratch from the test set) models in terms of global MAE scores on the test set.
       </p>
      </div>
      <div class="ltx_para" id="S5.p5">
       <p class="ltx_p">
        Table
        1
        reports the results achieved by the best performing algorithm for each type of model (
        batch
        ,
        adaptive
        ,
        empty
        ). As can be seen, close MAE values show a similar behaviour for the three types of models.
        With the same amount of training data, the performance of the batch and the adaptive models (in this case always obtained with OSVR) is almost identical. This demonstrates that, as expected, the online algorithms do not take advantage of test data with a label distribution similar to the training set. All the models outperform the baseline, even if the minimal differences confirm the competitiveness of such a simple approach.
       </p>
      </div>
      <div class="ltx_para" id="S5.p6">
       <p class="ltx_p">
        Overall, these results bring some interesting indications about the behaviour of the different online algorithms.
First, the good results achieved by the empty models (less than one MAE point separates them from the best ones built on the largest training set) suggest their high potential when training data are not available.
Second, our results show that OSVR is always the best performing algorithm for the adaptive and empty models. This suggests a lower capability of PA to learn from instances similar to the training data.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Experiments with CAT data
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        To experiment with adaptive QE in more realistic conditions we used a CAT tool
        to collect two datasets of (
        source
        ,
        target
        ,
        post_edited target
        ) English-Italian tuples.The source sentences in the datasets come from two documents from different domains, respectively legal (L) and information technology (IT). The L document, which was extracted from a European Parliament resolution published on the EUR-Lex platform,
        contains 164 sentences. The IT document, which was taken from a software user manual, contains 280 sentences. The source sentences were translated with two SMT systems built by training the Moses toolkit
        [14]
        on parallel data from the two domains (about 2M sentences for IT and 1.5M for L). Post-editions were collected from eight professional translators (four for each document) operating with the CAT tool in real working conditions.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        According to the way they are created, the two datasets allow us to evaluate the adaptability of different QE models with respect to user changes within the same domain (§
        6.1
        ), as well as user and domain changes at the same time (§
        6.2
        ).
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        For each document
        D
        (L or IT), these two scenarios are obtained by dividing
        D
        into two parts of equal size (80 instances for L and 140 for IT). The result is one training set and one test set for each post-editor within the same domain. For the
        user_change
        experiments, training and test sets are selected from different post-editors within the same domain. For the
        user+domain_change
        experiments, training and test sets are selected from different post-editors in different domains.
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        On each combination of training and test sets, the
        batch
        ,
        adaptive
        , and
        empty
        models are trained and evaluated in terms of global MAE scores on the test set.
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        Dealing with user changes
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         Among the possible combinations of training and test data from different post-editors in the same domain, Table
         2
         refers to two opposite scenarios.
For each domain, these respectively involve the most dissimilar and the most similar post-editors according to the
         Δ
         HTER. Also in this case, for each model (
         batch
         ,
         adaptive
         and
         empty
         ) we only report the MAE of the best performing algorithm.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         The first scenario defines a challenging situation where two post-editors (
         rad
         and
         cons
         ) are characterized by opposite behaviour. As evidenced by the high
         Δ
         HTER values, one of them (
         rad
         ) is the most “radical” post-editor (performing more corrections) while the other (
         cons
         ) is the most “conservative” one. As shown in Table
         2
         , global MAE scores for the online algorithms (both
         adaptive
         and
         empty
         ) indicate their good adaptation capabilities. This is evident from the significant improvements both over the baseline (
         μ
         ) and the batch models. Interestingly, the best results are always achieved by the
         empty
         models (with MAE reductions up to 10 points when tested on
         rad
         in the L domain, and 3.2 points when tested on
         rad
         in the IT domain). These results (MAE reductions are always statistically significant) suggest that, when dealing with datasets with very different label distributions, the evident limitations of batch methods are more easily overcome by learning from scratch from the feedback of a new post-editor. This also holds when the amount of test points to learn from is limited, as in the L domain where the test set contains only 80 instances. From the application-oriented perspective that motivates our work, considering the high costs of acquiring large and representative QE training data, this is an important finding.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p3">
        <p class="ltx_p">
         The second scenario defines a less challenging situation where the two post-editors (
         sim1
         and
         sim2
         ) are characterized by the most similar behaviour (small
         Δ
         HTER). This scenario is closer to the situation described in Section
         §
         5
         . Also in this case MAE results for the
         adaptive
         and
         empty
         models are slightly worse, but not significantly, than those of the batch models and the baseline. However, considering the very small amount of “uninformative” instances to learn from (especially for the
         empty
         models), these lower results are not surprising.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p4">
        <p class="ltx_p">
         A closer look at the behaviour of the online algorithms in the two domains leads to other observations. First, OSVR always outperforms PA for the
         empty
         models and when post-editors have similar behaviour, which are situations where the algorithm does not have to quickly adapt or react to sudden changes.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p5">
        <p class="ltx_p">
         Second, PA seems to perform better for the
         adaptive
         models when the post-editors have significantly different behaviour and a quick adaptation to the incoming points is required. This can be motivated by the fact that PA relies on a simpler and less robust learning strategy that does not keep track of all the information coming from the previously processed instances, and can easily modify its weights taking into consideration the last seen point (see Section
         §⁢3
         ). For OSVR the addition of new points to the support set may have a limited effect on the whole model, in particular if the number of points in the set is large. This also results in a different processing time for the two algorithms.
         For instance, in the
         empty
         configurations on IT data, OSVR devotes
         6.0⁢m⁢s
         per instance to update the model, while PA devotes
         4.8⁢m⁢s
         , which comes at the cost of lower performance.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        Dealing with user and domain changes
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         In the last round of experiments we evaluate the reactivity of different online models to simultaneous user and domain changes.
To this aim, our QE models are created using a training set coming from one domain (L or IT), and then used to predict the HTER labels for the test instances coming from the other domain (
         e.g.
         training on L, testing on IT).
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         Among the possible combinations of training and test data, Table
         3
         refers to scenarios involving the most conservative and radical post-editors in each domain (previously identified with
         cons
         and
         rad
         )
         . In the table, results are ordered according to the
         Δ
         HTER computed between the selected post-editor in the training domain (
         e.g.
         L cons
         ) and the selected post-editor in the test domain (
         e.g.
         IT rad
         ). For the sake of comparison, we also report (grey rows) the results of the experiments within the same domain presented in §
         6.1
         . For each type of model (
         batch
         ,
         adaptive
         and
         empty
         ) we only show the MAE obtained by the best performing algorithm.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         Intuitively, dealing with simultaneous user and domain changes represents a more challenging problem compared to the previous setting where only post-editors changes were considered. Such intuition is confirmed by the results of the
         adaptive
         models that outperform both the baseline (
         μ
         ) and the
         batch
         models even for low
         Δ
         HTER values. Although in these cases the distance between training and test data is comparable to the experiments with similar post-editors working in the same domain (
         sim1
         and
         sim2
         ), here the predictive power of the
         batch
         models seems in fact to be lower.
The same holds also for the
         empty
         models except in two cases where the
         Δ
         HTER is the smallest (2.2 and 5.0).
This is a strong evidence of the fact that, in case of domain changes, online models can still learn from new test instances even if they have a label distribution similar to the training set.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p4">
        <p class="ltx_p">
         When the distance between training and test increases, our results confirm our previous findings about the potential of the
         empty
         models. The observed MAE reductions range in fact from 10.4 to 12.9 points for the two combinations with the highest
         Δ
         HTER.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p5">
        <p class="ltx_p">
         From the algorithmic point of view, our results indicate that OSVR achieves the best performance for all the combinations involving user and domain changes. This contrasts with the results of most of the combinations involving only user changes with post-editors characterized by opposite behaviour (grey rows in Table
         3
         ). However, it has to be remarked that in the case of heterogeneous datasets the difference between the two algorithms is always very high. In our experiments, when PA outperforms OSVR, its MAE results are significantly lower and vice-versa (respectively up to 1.5 and 1.7 MAE points). This suggests that, although PA is potentially capable of achieving higher results and better adapt to the new test points, its instability makes it less reliable for practical use.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p6">
        <p class="ltx_p">
         As a final analysis of our results, we investigated how the performance of the different types of models (
         batch
         ,
         adaptive
         ,
         empty
         ) relates to the distance between training and test sets. To this aim, we computed the Pearson correlation between the
         Δ
         HTER (column 3 in Table
         3
         ) and the MAE of each model (columns 5, 6 and 8), which respectively resulted in 0.9 for the
         batch
         , 0.63 for the
         adaptive
         and -0.07 for the
         empty
         model. These values confirm that
         batch
         models are heavily affected by the dissimilarity between training and test data: large differences in the label distribution imply higher MAE results and vice-versa. This is in line with our previous findings about
         batch
         models that, learning only from the training set, cannot leverage possible dissimilarities of the test set. The lower correlation observed for the
         adaptive
         models also confirms our intuitions: adapting to the new test points, these models are in fact more robust to differences with the training data. As expected, the results of the
         empty
         models are completely uncorrelated with the
         Δ
         HTER since they only use the test set.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p7">
        <p class="ltx_p">
         This analysis confirms that, even when dealing with different domains, the similarity between the training and test data is one of the main factors that should drive the choice of the QE model. When this distance is minimal,
         batch
         models can be a reasonable option, but when the gap between training and test data increases,
         adaptive
         or
         empty
         models are a preferable choice to achieve good results.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
