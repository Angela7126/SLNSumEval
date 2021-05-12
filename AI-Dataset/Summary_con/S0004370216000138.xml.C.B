<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:359">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have presented a novel way to sample graphs from an empirical probability distribution.</a>
<a href="#1" id="1">The approach merges the expressiveness of a novel context-sensitive graph grammar with the computational efficiency and robustness to noisy inputs of one-class support vector machines.</a>
<a href="#2" id="2">Applications to molecular synthesis are encouraging.</a>
<a href="#3" id="3">Interestingly, as shown in the experimental section, the generated samples can be used to “virtually” augment the size of the available data to enhance the performance of traditional machine learning classification algorithms.</a>
<a href="#4" id="4">A related notion was presented in Schölkopf et al. [41] where samples are generated on the basis of some desired invariance (e.g. rotations for images).</a>
<a href="#5" id="5">The fact that in our experimental case, the predictive performance of a discriminative learner trained on the augmented set increases, indicates that the generator is capable to construct instances that are characteristic of the class being modeled.</a>
<a href="#6" id="6">Differently from Schölkopf et al. [41], here we are not injecting domain specific knowledge in the problem (encoded in the chosen type of class preserving invariance), but rather, we believe that the sampling augmentation works as an effective variance reduction technique using a sort of “general purpose” bias encoded in the locally substitutable graph grammar, namely that similar instances can be produced by replacing parts occurring in the same context.</a>
<a href="#7" id="7">In future work we will investigate non-linear kernelized quantile estimation techniques (as done in Muandet and Schölkopf [35]) to better characterize the empirical probability distribution of graphs.</a>
<a href="#8" id="8">A further element of the proposed approach that we will explore in more details is the “convergence issue”, i.e. the fact that the sampling procedure identifies instances belonging to a distribution that differs from the desired one if the Markov Chain has not properly converged.</a>
<a href="#9" id="9">The issue is a research subject in the ordinary unstructured case and definitely needs further investigation in the structured case.</a>
<a href="#10" id="10">Finally we will explore applications of the proposed approach to a variety of design tasks in different application domains.</a>
<a href="#11" id="11">Interestingly the sampling process can be interpreted as a way to iteratively improve pre-existing designs and can be used as a computer aided creativity tool.</a>
<a href="#12" id="12">A software implementation of the graph sampler is available at: https://github.com/fabriziocosta/GraphLearn.</a>
</body>
</html>