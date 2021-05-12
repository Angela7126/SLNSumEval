<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Algorithm runtime prediction: Methods &amp; evaluation.
   </title>
   <abstract>
    Perhaps surprisingly, it is possible to predict how long an algorithm will take to run on a previously unseen input, using machine learning techniques to build a model of the algorithmʼs runtime as a function of problem-specific instance features. Such models have important applications to algorithm analysis, portfolio-based algorithm selection, and the automatic configuration of parameterized algorithms. Over the past decade, a wide variety of techniques have been studied for building such models. Here, we describe extensions and improvements of existing models, new families of models, and—perhaps most importantly—a much more thorough treatment of algorithm parameters as model inputs. We also comprehensively describe new and existing features for predicting algorithm runtime for propositional satisfiability (SAT), travelling salesperson (TSP) and mixed integer programming (MIP) problems. We evaluate these innovations through the largest empirical analysis of its kind, comparing to a wide range of runtime modelling techniques from the literature. Our experiments consider 11 algorithms and 35 instance distributions; they also span a very wide range of SAT, MIP, and TSP instances, with the least structured having been generated uniformly at random and the most structured having emerged from real industrial applications. Overall, we demonstrate that our new models yield substantially better runtime predictions than previous approaches in terms of their generalization to new problem instances, to new algorithms from a parameterized space, and to both simultaneously.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      NP-complete problems are ubiquitous in AI. Luckily, while these problems may be hard to solve on worst-case inputs, it is often feasible to solve even large problem instances that arise in practice. Less luckily, state-of-the-art algorithms often exhibit extreme runtime variation across instances from realistic distributions, even when problem size is held constant, and conversely the same instance can take dramatically different amounts of time to solve depending on the algorithm used [31]. There is little theoretical understanding of what causes this variation. Over the past decade, a considerable body of work has shown how to use supervised machine learning methods to build regression models that provide approximate answers to this question based on given algorithm performance data; we survey this work in Section 2. In this article, we refer to such models as empirical performance models (EPMs).{sup:1} These models are useful in a variety of practical contexts:
     </paragraph>
     <list>
      <list-item label="•">
       Algorithm selection. This classic problem of selecting the best from a given set of algorithms on a per-instance basis [95], [104] has been successfully addressed by using EPMs to predict the performance of all candidate algorithms and selecting the one predicted to perform best [18], [79], [26], [45], [97], [119], [70].
      </list-item>
      <list-item label="•">
       Parameter tuning and algorithm configuration. EPMs are useful for these problems in at least two ways. First, they can model the performance of a parameterized algorithm dependent on the settings of its parameters; in a sequential model-based optimization process, one alternates between learning an EPM and using it to identify promising settings to evaluate next [65], [7], [59], [55], [56]. Second, EPMs can model algorithm performance dependent on both problem instance features and algorithm parameter settings; such models can then be used to select parameter settings with good predicted performance on a per-instance basis [50].
      </list-item>
      <list-item label="•">
       Generating hard benchmarks. An EPM for one or more algorithms can be used to set the parameters of existing benchmark generators in order to create instances that are hard for the algorithms in question [74], [76].
      </list-item>
      <list-item label="•">
       Gaining insights into instance hardness and algorithm performance. EPMs can be used to assess which instance features and algorithm parameter values most impact empirical performance. Some models support such assessments directly [96], [82]. For other models, generic feature selection methods, such as forward selection, can be used to identify a small number of key model inputs (often fewer than five) that explain algorithm performance almost as well as the whole set of inputs [76], [57].
      </list-item>
     </list>
     <paragraph>
      While these applications motivate our work, in the following, we will not discuss them in detail; instead, we focus on the models themselves. The idea of modelling algorithm runtime is no longer new; however, we have made substantial recent progress in making runtime prediction methods more general, scalable and accurate. After a review of past work (Section 2) and of the runtime prediction methods used by this work (Section 3), we describe four new contributions.
     </paragraph>
     <list>
      <list-item label="1.">
       We describe new, more sophisticated modelling techniques (based on random forests and approximate Gaussian processes) and methods for modelling runtime variation arising from the settings of a large number of (both categorical and continuous) algorithm parameters (Section 4).
      </list-item>
      <list-item label="2.">
       We introduce new instance features for propositional satisfiability (SAT), travelling salesperson (TSP) and mixed integer programming (MIP) problems—in particular, novel probing features and timing features—yielding comprehensive sets of 138, 121, and 64 features for SAT, MIP, and TSP, respectively (Section 5).
      </list-item>
      <list-item label="3.">
       To assess the impact of these advances and to determine the current state of the art, we performed what we believe is the most comprehensive evaluation of runtime prediction methods to date. Specifically, we evaluated all methods of which we are aware on performance data for 11 algorithms and 35 instance distributions spanning SAT, TSP and MIP and considering three different problems: predicting runtime on novel instances (Section 6), novel parameter configurations (Section 7), and both novel instances and configurations (Section 8).
      </list-item>
      <list-item label="4.">
       Techniques from the statistical literature on survival analysis offer ways to better handle data from runs that were terminated prematurely. While these techniques were not used in most previous work—leading us to omit them from the comparison above—we show how to leverage them to achieve further improvements to our best-performing model, random forests (Section 9).{sup:2}
      </list-item>
     </list>
    </section>
    <section label="2">
     <section-title>
      An overview of related work
     </section-title>
     <paragraph>
      Because the problems have been considered by substantially different communities, we separately consider related work on predicting the runtime of parameterless and parameterized algorithms, and applications of these predictions to gain insights into instance hardness and algorithm parameters.
     </paragraph>
     <section label="2.1">
      <section-title>
       Related work on predicting runtime of parameterless algorithms
      </section-title>
      <paragraph>
       The use of statistical regression methods for runtime prediction has its roots in a range of different communities and dates back at least to the mid-1990s. In the parallel computing literature, Brewer used linear regression models to predict the runtime of different implementations of portable, high-level libraries for multiprocessors, aiming to automatically select the best implementation on a novel architecture [17], [18]. In the AI planning literature, Fink [26] used linear regression to predict how the performance of three planning algorithms depends on problem size and used these predictions for deciding which algorithm to run for how long. In the same community, Howe and co-authors [45], [97] used linear regression to predict how both a plannerʼs runtime and its probability of success depend on various features of the planning problem; they also applied these predictions to decide, on a per-instance basis, which of a finite set of algorithms should be run in order to optimize a performance objective such as expected runtime. Specifically, they constructed a portfolio of planners that ordered algorithms by their expected success probability divided by their expected runtime. In the constraint programming literature, Leyton-Brown et al. [75], [76] studied the winner determination problem in combinatorial auctions and showed that accurate runtime predictions could be made for several different solvers and a wide variety of instance distributions. That work considered a variety of different regression methods (including lasso regression, multivariate adaptive regression splines, and support vector machine regression) but in the end settled on a relatively simpler method: ridge regression with preprocessing to select an appropriate feature subset, a quadratic basis function expansion, and a log-transformation of the response variable. (We formally define this and other regression methods in Section 3.) The problem-independent runtime modelling techniques from that work were subsequently applied to the SAT problem [90], leading to the successful portfolio-based algorithm selection method SATzilla[89], [90], [117], [119]. Most recently, in the machine learning community, Huang et al. [47] applied linear regression techniques to the modelling of algorithms with low-order polynomial runtimes.
      </paragraph>
      <paragraph>
       Due to the extreme runtime variation often exhibited by algorithms for solving combinatorial problems, it is common practice to terminate unsuccessful runs after they exceed a so-called captime. Capped runs only yield a lower bound on algorithm runtime, but are typically treated as having succeeded at the captime. Fink [26] was the first to handle such right-censored data points more soundly for runtime predictions of AI planning methods and used the resulting predictions to compute captimes that maximize a given utility function. Gagliolo et al. [28], [27] made the connection to the statistical literature on survival analysis to handle right-censored data in their work on dynamic algorithm portfolios. Subsequently, similar techniques were used for SATzillaʼs runtime predictions [117] and in model-based algorithm configuration [54].
      </paragraph>
      <paragraph>
       Recently, Smith-Miles et al. published a series of papers on learning-based approaches for characterizing instance hardness for a wide variety of hard combinatorial problems [104], [108], [106], [105]. Their work considered a range of tasks, including not only performance prediction, but also clustering, classification into easy and hard instances, as well as visualization. In the context of performance prediction, on which we focus in this article, theirs is the only work known to us to use neural network models. Also recently, Kotthoff et al. [70] compared regression, classification, and ranking algorithms for algorithm selection and showed that this choice matters: poor regression and classification methods yielded worse performance than the single best solver, while good methods yielded better performance.
      </paragraph>
      <paragraph>
       Several other veins of performance prediction research deserve mention. Haim &amp; Walsh [37] extended linear methods to the problem of making online estimates of SAT solver runtimes. Several researchers have applied supervised classification to select the fastest algorithm for a problem instance [33], [29], [34], [30], [120] or to judge whether a particular run of a randomized algorithm would be good or bad [43] (in contrast to our topic of predicting performance directly using a regression model). In the machine learning community, meta-learning aims to predict the accuracy of learning algorithms [111]. Meta-level control for anytime algorithms computes estimates of an algorithmʼs performance in order to decide when to stop it and act on the solution found [38]. Algorithm scheduling in parallel and distributed systems has long relied on low-level performance predictions, for example based on source code analysis [88]. In principle, the methods discussed in this article could also be applied to meta-level control and algorithm scheduling.
      </paragraph>
      <paragraph>
       Other research has aimed to identify single quantities that correlate with an algorithmʼs runtime. A famous early example is the clauses-to-variables ratio for uniform-random 3-SAT [19], [83]. Earlier still, Knuth showed how to use random probes of a search tree to estimate its size [69]; subsequent work refined this approach [79], [68]. We incorporated such predictors as features in our own work and therefore do not evaluate them separately. (We note, however, that we have found Knuthʼs tree-size estimate to be very useful for predicting runtime in some cases, e.g., for complete SAT solvers on unsatisfiable 3-SAT instances [90].) The literature on search space analysis has proposed a variety of quantities correlated with the runtimes of (mostly) local search algorithms. Prominent examples include fitness distance correlation [66] and autocorrelation length (ACL) [113]. With one exception (ACL for TSP) we have not included such measures in our feature sets, as computing them can be quite expensive.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Related work on predicting runtime of parameterized algorithms
      </section-title>
      <paragraph>
       In principle, it is not particularly harder to predict the runtimes of parameterized algorithms than the runtimes of their parameterless cousins: parameters can be treated as additional inputs to the model (notwithstanding the fact that they describe the algorithm rather than the problem instance, and hence are directly controllable by the experimenter), and a model can be learned in the standard way. In past work, we pursued precisely this approach, using both linear regression models and exact Gaussian processes to model the dependency of runtime on both instance features and algorithm parameter values [50]. However, this direct application of methods designed for parameterless algorithms is effective only for small numbers of continuous-valued parameters (e.g., the experiments in [50] considered only two parameters). Different methods are more appropriate when an algorithmʼs parameter space becomes very large. In particular, a careful sampling strategy must be used, making it necessary to consider issues raised in the statistics literature on experimental design. Separately, models must be adjusted to deal with categorical parameters: parameters with finite, unordered domains (e.g., selecting which of various possible heuristics to use, or activating an optional preprocessing routine).
      </paragraph>
      <paragraph>
       The experimental design literature uses the term response surface model (RSM) to refer to a predictor for the output of a process with controllable input parameters that can generalize from observed data to new, unobserved parameter settings (see, e.g., [14], [13]). Such RSMs are at the core of sequential model-based optimization methods for blackbox functions [65], which have recently been adapted to applications in automated parameter tuning and algorithm configuration (see, e.g., [7], [6], [58], [59], [55]).
      </paragraph>
      <paragraph>
       Most of the literature on RSMs of algorithm performance has limited its consideration to algorithms running on single problem instances and algorithms only with continuous input parameters. We are aware of a few papers beyond our own that relax these assumptions. Bartz-Beielstein &amp; Markon [8] support categorical algorithm parameters (using regression tree models), and two existing methods consider predictions across both different instances and parameter settings. First, Ridge &amp; Kudenko [96] applied an analysis of variance (ANOVA) approach to detect important parameters, using linear and quadratic models. Second, Chiarandini &amp; Goegebeur [20] noted that in contrast to algorithm parameters, instance characteristics cannot be controlled and should be treated as so-called random effects. Their resulting mixed-effects models are linear and, like Ridge &amp; Kudenkoʼs ANOVA model, assume Gaussian performance distributions. We note that this normality assumption is much more realistic in the context of predicting solution quality of local search algorithms (the problem addressed in [20]) than in the context of the algorithm runtime prediction problem we tackle here.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Related work on applications of runtime prediction to gain insights into instance hardness and algorithm parameters
      </section-title>
      <paragraph>
       Leyton-Brown and co-authors [75], [90], [76] employed forward selection with linear regression models to determine small sets of instance features that suffice to yield high-quality predictions, finding that often as little as five to ten features yielded predictions as good as the full feature set. Hutter et al. [57] extended that work to predictions in the joint space of instance features and algorithm parameters, using arbitrary models. Two model-specific approaches for this joint identification of instance features and algorithm parameters are the ANOVA approach of Ridge &amp; Kudenko [96] and the mixed-effects model of Chiarandini &amp; Goegebeur [20] mentioned previously. Other approaches for quantifying parameter importance include an entropy-based measure [85], and visualization methods for interactive parameter exploration [6].
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Methods used in related work
     </section-title>
     <paragraph>
      We now define the different machine learning methods that have been used to predict algorithm runtimes: ridge regression (used by [17], [18], [75], [76], [89], [90], [50], [117], [119], [47]), neural networks (see [107]), Gaussian process regression (see [50]), and regression trees (see [8]). This section provides the basis for the experimental evaluation of different methods in Sections 6, 7, and 8; thus, we also discuss implementation details.
     </paragraph>
     <section label="3.1">
      <section-title>
       Preliminaries
      </section-title>
      <paragraph>
       We describe a problem instance by a list of m features {a mathematical formula}z=[z1,…,zm]T, drawn from a given feature space{a mathematical formula}F. These features must be computable by a piece of problem-specific code (usually provided by a domain expert) that efficiently extracts characteristics for any given problem instance (typically, in low-order polynomial time w.r.t. to the size of the given problem instance). We define the configuration space of a parameterized algorithm with k parameters {a mathematical formula}θ1,…,θk with respective domains {a mathematical formula}Θ1,…,Θk as a subset of the cross-product of parameter domains: {a mathematical formula}Θ⊆Θ1×⋯×Θk. The elements of Θ are complete instantiations of the algorithmʼs k parameters, and we refer to them as configurations. Taken together, the configuration and the feature spaces define the input space: {a mathematical formula}I=Θ×F.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}Δ(R) denote the space of probability distributions over the real numbers; we will use these real numbers to represent an algorithm performance measure, such as runtime in seconds on some reference machine. (In principle, EPMs can predict any type of performance measure that can be evaluated in single algorithm runs, such as runtime, solution quality, memory usage, energy consumption, or communication overhead.) Given an algorithm {a mathematical formula}A with configuration space Θ and a distribution of instances with feature space {a mathematical formula}F, an EPM is a stochastic process {a mathematical formula}f:I↦Δ(R) that defines a probability distribution over performance measures for each combination of a parameter configuration {a mathematical formula}θ∈Θ of {a mathematical formula}A and a problem instance with features {a mathematical formula}z∈F. The prediction of an entire distribution allows us to assess the modelʼs confidence at a particular input, which is essential, e.g., in model-based algorithm configuration [7], [6], [58], [55]. Nevertheless, since many of the methods we review yield only point-valued runtime predictions, our experimental analysis focuses on the accuracy of mean predicted runtimes. For the models that define a predictive distribution (Gaussian processes and our variant of random forests), we study the accuracy of confidence values separately in the online appendix, with qualitatively similar results as for mean predictions.
      </paragraph>
      <paragraph>
       To construct an EPM for an algorithm {a mathematical formula}A with configuration space Θ on an instance set Π, we run {a mathematical formula}A on various combinations of configurations {a mathematical formula}θi∈Θ and instances {a mathematical formula}πi∈Π, and record the resulting performance values {a mathematical formula}yi. We record the k-dimensional parameter configuration {a mathematical formula}θi and the m-dimensional feature vector {a mathematical formula}zi of the instance used in the ith run, and combine them to form a {a mathematical formula}p=k+m-dimensional vector of predictor variables{a mathematical formula}xi=[θiT,ziT]T. The training data for our regression models is then simply {a mathematical formula}{(x1,y1),…,(xn,yn)}. We use X to denote the {a mathematical formula}n×p matrix containing {a mathematical formula}[x1,…,xn]T (the so-called design matrix) and y for the vector of performance values {a mathematical formula}[y1,…,yn]T.
      </paragraph>
      <paragraph>
       Various transformations can make this data easier to model. In this article, we focus on runtime as a performance measure and use a log-transformation, thus effectively predicting log runtime.{sup:3} In our experience, we have found this transformation to be very important due to the large variation in runtimes for hard combinatorial problems. We also transformed the predictor variables, discarding those input dimensions constant across all training data points and normalizing the remaining ones to have mean 0 and standard deviation 1 (i.e., for each input dimension we subtracted the mean and then divided by the standard deviation).
      </paragraph>
      <paragraph>
       For some instances, certain feature values can be missing because of timeouts, crashes, or because they are undefined (when preprocessing has already solved an instance). These missing values occur relatively rarely, so we use a simple mechanism for handling them. We disregard missing values for the purposes of normalization, and then set them to zero for training our models. This means that missing feature values are effectively assumed to be equal to the mean for the respective distribution and thus to be minimally informative. In some models (ridge regression and neural networks), this mechanism leads us to ignore missing features, since their weight is multiplied by zero.
      </paragraph>
      <paragraph>
       Most modelling methods discussed in this paper have free hyperparameters that can be set by minimizing some loss function, such as cross-validation error. We point out these hyperparameters, as well as their default setting, when discussing each of the methods. While, to the best of our knowledge, all previous work on runtime prediction has used fixed default hyperparameters, we also experimented with optimizing them for every method in our experiments. For this purpose, we used the gradient-free optimizer DIRECT [64] to minimize 2-fold cross-validated root mean squared error (RMSE) on the training set with a budget of 30 function evaluations. This simple approach is a better alternative than the frequently-used grid search and random search [9].
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Ridge regression
      </section-title>
      <paragraph>
       Ridge regression (see, e.g., [12]) is a simple regression method that fits a linear function {a mathematical formula}fw(x) of its inputs x. Due to its simplicity (both conceptual and computational) and its interpretability, combined with competitive predictive performance in most scenarios we studied, this is the method that has been used most frequently in the past for building EPMs [26], [45], [75], [76], [90], [50], [115].
      </paragraph>
      <paragraph>
       Ridge regression works as follows. Let X and y be as defined above, let {a mathematical formula}Ip be the {a mathematical formula}p×p identity matrix, and let ϵ be a small constant. Then, compute the weight vector{a mathematical formula} Given a new feature vector, {a mathematical formula}xn+1, ridge regression predicts {a mathematical formula}fw(xn+1)=wTxn+1. Observe that with {a mathematical formula}ϵ=0, we recover standard linear regression. The effect of {a mathematical formula}ϵ&gt;0 is to regularize the model by penalizing large coefficients w; it is equivalent to a Gaussian prior favouring small coefficients under a Bayesian model (see, e.g., [12]). A beneficial side effect of this regularization is that numerical stability improves in the common case where X is rank deficient, or nearly so. The computational bottleneck in ridge regression with p input dimensions is the inversion of the {a mathematical formula}p×p matrix {a mathematical formula}A=XTX+ϵIp, which requires time cubic in p.
      </paragraph>
      <paragraph>
       Algorithm runtime can often be better approximated by a polynomial function than by a linear one, and the same holds for log runtimes. For that reason, it can make sense to perform a basis function expansion to create new features that are products of two or more original features. In light of the resulting increase in the number of features, a quadratic expansion is particularly appealing. Formally, we augment each model input {a mathematical formula}xi=[xi,1,…,xi,p]T with pairwise product inputs {a mathematical formula}xi,j⋅xi,l for {a mathematical formula}j=1,…,p and {a mathematical formula}l=j,…,p.
      </paragraph>
      <paragraph>
       Even with ridge regularization, the generalization performance of linear regression (and, indeed, many other learning algorithms) can deteriorate when some inputs are uninformative or highly correlated with others; in our experience, it is difficult to construct sets of instance features that do not suffer from these problems. Instead, we reduce the set of input features by performing feature selection. Many different methods exist for feature expansion and selection; we review two different ridge regression variants from the recent literature that only differ in these design decisions.{sup:4}
      </paragraph>
      <section label="3.2.1">
       Ridge regression variant RR: Two-phase forward selection [117,119]
       <paragraph>
        For more than half a decade, we used a simple and scalable feature selection method based on forward selection (see e.g., [36]) to build the regression models used by SATzilla[117], [119]. This iterative method starts with an empty input set, greedily adds one linear input at a time to minimize cross-validation error at each step, and stops when l linear inputs have been selected. It then performs a full quadratic expansion of these l linear features (using the original, unnormalized features, and then normalizing the resulting quadratic features again to have mean zero and standard deviation one). Finally, it carries out another forward selection with the expanded feature set, once more starting with an empty input set and stopping when q features have been selected. The reason for the two-phase approach is scalability: this method prevents us from ever having to perform a full quadratic expansion of our features. (For example, we have often employed over 100 features and a million runtime measurements; in this case, a full quadratic expansion would involve over 5 billion feature values.)
       </paragraph>
       <paragraph>
        Our implementation reduces the computational complexity of forward selection by exploiting the fact that the inverse matrix {a mathematical formula}(A′)−1 resulting from including one additional feature can be computed incrementally by two rank-one updates of the previous inverse matrix {a mathematical formula}A−1, requiring quadratic time rather than cubic time [103].
       </paragraph>
       <paragraph>
        In our experiments, we fixed the number of linear inputs to {a mathematical formula}l=30 in order to keep the result of a full quadratic basis function expansion manageable in size (with 1 million data points, the resulting matrix has {a mathematical formula}((302)+30)⋅1000000, or about 500 million elements). The maximum number of quadratic terms q and the ridge penalizer ϵ are free parameters of this method; by default, we used {a mathematical formula}q=20 and {a mathematical formula}ϵ=10−3.
       </paragraph>
      </section>
      <section label="3.2.2">
       Ridge regression variant SPORE-FoBa: Forward–backward selection [47]
       <paragraph>
        Recently, Huang et al. [47] described a method for predicting algorithm runtime that they called Sparse POlynomial REgression (SPORE), which is based on ridge regression with forward–backward (FoBa) feature selection.{sup:5} Huang et al. concluded that SPORE-FoBa outperforms lasso regression, which is consistent with the comparison to lasso by Leyton-Brown et al. [76]. In contrast to the RR variants above, SPORE-FoBa employs a cubic feature expansion (based on its own normalizations of the original predictor variables). Essentially, it performs a single pass of forward selection, at each step adding a small set of terms determined by a forward–backward phase on a featureʼs candidate set. Specifically, having already selected a set of terms T based on raw features S, SPORE-FoBa loops over all raw features {a mathematical formula}r∉S, constructing a candidate set {a mathematical formula}Tr that consists of all polynomial expansions of {a mathematical formula}S∪{r} that include r with non-zero degree and whose total degree is bounded by 3. For each such candidate set {a mathematical formula}Tr, the forward–backward phase iteratively adds the best term {a mathematical formula}t∈T∖Tr, if its reduction of root mean squared error (RMSE) exceeds a threshold γ (forward step), and then removes the worst term {a mathematical formula}t∈T, if its reduction of RMSE is below 0.5γ (backward step). This phase terminates when no single term {a mathematical formula}t∈T∖Tr can be added to reduce RMSE by more than γ. Finally, SPORE-FoBaʼs outer forward selection loop chooses the set of terms T resulting from the best of its forward–backward phases, and iterates until the number of terms in T reach a prespecified maximum of {a mathematical formula}tmax terms. In our experiments, we used the original SPORE-FoBa code; its free parameters are the ridge penalizer ϵ, {a mathematical formula}tmax, and γ, with defaults {a mathematical formula}ϵ=10−3, {a mathematical formula}tmax=10, and {a mathematical formula}γ=0.01.
       </paragraph>
      </section>
     </section>
     <section label="3.3">
      <section-title>
       Neural networks
      </section-title>
      <paragraph>
       Neural networks are a well-known regression method inspired by information processing in the human brain. The multilayer perceptron (MLP) is a particularly popular type of neural network that organizes single computational units (“neurons”) in layers (input, hidden, and output layers), using the outputs of all units in a layer as the inputs of all units in the next layer. Each neuron {a mathematical formula}ni in the hidden and output layers with k inputs {a mathematical formula}ai=[ai,1,…,ai,k] has an associated weight term vector {a mathematical formula}wi=[wi,1,…,wi,k] and a bias term {a mathematical formula}bi, and computes a function {a mathematical formula}wiTai+bi. For neurons in the hidden layer, the result of this function is further propagated through a nonlinear activation function {a mathematical formula}g:R→R (which is often chosen to be tanh). Given an input {a mathematical formula}x=[x1,…,xp], a network with a single hidden layer of h neurons {a mathematical formula}n1,…,nh and a single output neuron {a mathematical formula}nh+1 then computes output{a mathematical formula} The {a mathematical formula}p⋅h+h weight terms and {a mathematical formula}h+1 bias terms can be combined into a single weight vector w, which can be set to minimize the networkʼs prediction error using any continuous optimization algorithm (e.g., the classic “backpropagation” algorithm performs gradient descent to minimize squared prediction error).
      </paragraph>
      <paragraph>
       Smith-Miles &amp; van Hemert [107] used an MLP with one hidden layer of 28 neurons to predict the runtime of local search algorithms for solving timetabling instances. They used the proprietary neural network software Neuroshell, but advised us to compare to an off-the-shelf Matlab implementation instead. We thus employed the popular Matlab neural network package NETLAB [84]. NETLAB uses activation function {a mathematical formula}g=tanh and supports a regularizing prior to keep weights small, minimizing the error metric {a mathematical formula}∑iN(fˆ(xi)−yi)2+αwTw, where α is a parameter determining the strength of the prior. In our experiments, we used NETLABʼs default optimizer (scaled conjugate gradients, SCG) to minimize this error metric, stopping the optimization after the default of 100 SCG steps. Free parameters are the regularization factor α and the number of hidden neurons h; we used NETLABʼs default {a mathematical formula}α=0.01 and, like Smith-Miles &amp; van Hemert [107], {a mathematical formula}h=28.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Gaussian process regression
      </section-title>
      <paragraph>
       Stochastic Gaussian processes (GPs) [94] are a popular class of regression models with roots in geostatistics, where they are also called Kriging models [71]. GPs are the dominant modern approach for building response surface models [98], [65], [99], [6]. They were first applied to runtime prediction by Hutter et al. [50], who found them to yield better results than ridge regression, albeit at greater computational expense.
      </paragraph>
      <paragraph>
       To construct a GP regression model, we first need to select a kernel function {a mathematical formula}k:I×I↦R+, characterizing the degree of similarity between pairs of elements of the input space {a mathematical formula}I. A variety of kernel functions are possible, but the most common choice for continuous inputs is the squared exponential kernel{a mathematical formula} where {a mathematical formula}λ1,…,λp are kernel parameters. It is based on the idea that correlations decrease with weighted Euclidean distance in the input space (weighing each dimension l by a kernel parameter {a mathematical formula}λl). In general, such a kernel defines a prior distribution over the type of functions we expect. This distribution takes the form of a Gaussian stochastic process: a collection of random variables such that any finite subset of them has a joint Gaussian distribution. What remains to be specified is the tradeoff between the strength of this prior and fitting observed data, which is set by specifying the observation noise. Standard GPs assume normally distributed observation noise with mean zero and variance {a mathematical formula}σ2, where {a mathematical formula}σ2, like the kernel parameters {a mathematical formula}λl, can be optimized to improve the fit. Combining the prior specified above with the training data {a mathematical formula}D={(x1,y1),…,(xn,yn)} yields the posterior distribution at a new input point {a mathematical formula}xn+1 (see the book by Rasmussen &amp; Williams [94] for a derivation):{a mathematical formula} with mean and variance{a mathematical formula}{a mathematical formula} where{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The GP equations above assume fixed kernel parameters {a mathematical formula}λ1,…,λp and fixed observation noise variance {a mathematical formula}σ2. These constitute the GPʼs hyperparameters. In contrast to hyperparameters in other models, the number of GP hyperparameters grows with the input dimensionality, and their optimization is an integral part of fitting a GP: they are typically set by maximizing the marginal likelihood{a mathematical formula}p(y1:n) of the data with a gradient-based optimizer (again, see Rasmussen &amp; Williams [94] for details). The choice of optimizer can make a big difference in practice; we used the minFunc[101] implementation of a limited-memory version of BFGS [87].
      </paragraph>
      <paragraph>
       Learning a GP model from data can be computationally expensive. Inverting the {a mathematical formula}n×n matrix {a mathematical formula}[K+σ2In] takes {a mathematical formula}O(n3) time and has to be done in every of the h hyperparameter optimization steps, yielding a total complexity of {a mathematical formula}O(h⋅n3). Subsequent predictions at a new input require only time {a mathematical formula}O(n) and {a mathematical formula}O(n2) for the mean and the variance, respectively.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Regression trees
      </section-title>
      <paragraph>
       Regression trees [16] are simple tree-based regression models. They are known to handle discrete inputs well; their first application to the prediction of algorithm performance was by Bartz-Beielstein &amp; Markon [8]. The leaf nodes of regression trees partition the input space into disjoint regions {a mathematical formula}R1,…,RM, and use a simple model for prediction in each region {a mathematical formula}Rm; the most common choice is to predict a constant {a mathematical formula}cm. This leads to the following prediction for an input point x:{a mathematical formula} where the indicator function {a mathematical formula}Iz takes value 1 if the proposition z is true and 0 otherwise. Note that since the regions {a mathematical formula}Rm partition the input space, this sum will always involve exactly one non-zero term. We denote the subset of training data points in region {a mathematical formula}Rm as {a mathematical formula}Dm. Under the standard squared error loss function {a mathematical formula}∑i=1n(yi−μˆ(xi))2, the error-minimizing choice of constant {a mathematical formula}cm in region {a mathematical formula}Rm is then the sample mean of the data points in {a mathematical formula}Dm:{a mathematical formula}
      </paragraph>
      <paragraph>
       To construct a regression tree, we use the following standard recursive procedure, which starts at the root of the tree with all available training data points {a mathematical formula}D={(x1,y1),…,(xn,yn)}. We consider binary partitionings of a given nodeʼs data along split variables j and split points s. For a real-valued split variable j, s is a scalar and data point {a mathematical formula}xi is assigned to region {a mathematical formula}R1(j,s) if {a mathematical formula}xi,j⩽s and to region {a mathematical formula}R2(j,s) otherwise. For a categorical split variable j, s is a set, and data point {a mathematical formula}xi is assigned to region {a mathematical formula}R1(j,s) if {a mathematical formula}xi,j∈s and to region {a mathematical formula}R2(j,s) otherwise. At each node, we select split variable j and split point s to minimize the sum of squared differences to the regionsʼ means,{a mathematical formula} where {a mathematical formula}c1 and {a mathematical formula}c2 are chosen according to Eq. (3) as the sample means in regions {a mathematical formula}R1(j,s) and {a mathematical formula}R2(j,s), respectively. We continue this procedure recursively, finding the best split variable and split point, partitioning the data into two child nodes, and recursing into the child nodes. The process terminates when all training data points in a node share the same x values, meaning that no more splits are possible. This procedure tends to overfit data, which can be mitigated by recursively pruning away branches that contribute little to the modelʼs predictive accuracy. We use cost-complexity pruning with 10-fold cross-validation to identify the best tradeoff between complexity and predictive quality; see the book by Hastie et al. [39] for details.
      </paragraph>
      <paragraph>
       In order to predict the response value at a new input, {a mathematical formula}xi, we propagate x down the tree, that is, at each node with split variable j and split point s, we continue to the left child node if {a mathematical formula}xi,j⩽s (for real-valued variable j) or {a mathematical formula}xi,j∈s (for categorical variable j), and to the right child node otherwise. The predictive mean for {a mathematical formula}xi is the constant {a mathematical formula}cm in the leaf that this process selects; there is no variance predictor.
      </paragraph>
      <section label="3.5.1">
       <section-title>
        Complexity of constructing regression trees
       </section-title>
       <paragraph>
        If implemented efficiently, the computational cost of fitting a regression tree is small. At a single node with n data points of dimensionality p, it takes {a mathematical formula}O(p⋅nlogn) time to identify the best combination of split variable and point, because for each continuous split variable j, we can sort the n values {a mathematical formula}x1,j,…,xn,j and only consider up to {a mathematical formula}n−1 possible split points between different values. The procedure for categorical split variables has the same complexity: we consider each of the variableʼs k categorical values {a mathematical formula}ul, compute score {a mathematical formula}sl=mean({yi|xi,j=ul}) across the nodeʼs data points, sort {a mathematical formula}(u1,…,uk) by these scores, and only consider the k binary partitions with consecutive scores in each set. For the squared error loss function we use, the computation of {a mathematical formula}l(j,s) (see Eq. (4)) can be performed in amortized {a mathematical formula}O(1) time for each of jʼs split points s, such that the total time required for determining the best split point of a single variable is {a mathematical formula}O(nlogn). The complexity of building a regression tree depends on how balanced it is. In the worst case, one data point is split off at a time, leading to a tree of depth {a mathematical formula}n−1 and a complexity of {a mathematical formula}O(p∑i=1n(n−i)log(n−i)), which is {a mathematical formula}O(p⋅n2logn). In the best case—a balanced tree—we have the recurrence relation {a mathematical formula}T(n)=v⋅nlogn+2T(n/2), leading to a complexity of {a mathematical formula}O(p⋅nlog2n). In our experience, trees are not perfectly balanced, but are much closer to the best case than to the worst case. For example, {a mathematical formula}10000 data points typically led to tree depths between 25 and 30 (whereas {a mathematical formula}log2(10000)≈13).
       </paragraph>
       <paragraph>
        Prediction with regression trees is cheap; we merely need to propagate new query points {a mathematical formula}xn+1 down the tree. At each node with continuous split variable j and split point s, we only need to compare {a mathematical formula}xn+1,j to s, an {a mathematical formula}O(1) operation. For categorical split variables, we can store a bit mask of the values in s to enable {a mathematical formula}O(1) member queries. In the worst case (where the tree has depth {a mathematical formula}n−1), prediction thus takes {a mathematical formula}O(n) time, and in the best (balanced) case it takes {a mathematical formula}O(logn) time.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="4">
     <section-title>
      New modelling techniques for EPMs
     </section-title>
     <paragraph>
      In this section we extend existing modelling techniques for EPMs, with the primary goal of improving runtime predictions for highly parameterized algorithms. The methods described here draw on advanced machine learning techniques, but, to the best of our knowledge, our work is the first to have applied them for algorithm performance prediction. More specifically, we show how to extend all models to handle categorical inputs (required for predictions in partially categorical configuration spaces) and describe two new model families well-suited to modelling the performance of highly parameterized algorithms based on potentially large amounts of data: the projected process approximation to Gaussian processes and random forests of regression trees.
     </paragraph>
     <section label="4.1">
      <section-title>
       Handling categorical inputs
      </section-title>
      <paragraph>
       Empirical performance models have historically been limited to continuous-valued inputs; the only approach that has so far been used for performance predictions based on discrete-valued inputs is regression trees [8]. In this section, we first present a standard method for encoding categorical parameters as real-valued parameters, and then present a kernel for handling categorical inputs more directly in Gaussian processes.
      </paragraph>
      <section label="4.1.1">
       Extension of existing methods using 1-in-{a mathematical formula}K encoding
       <paragraph>
        A standard solution for extending arbitrary modelling techniques to handle categorical inputs is the so-called 1-in-{a mathematical formula}K encoding scheme (see, e.g., [12]), which encodes categorical inputs with finite domain size {a mathematical formula}K as {a mathematical formula}K binary inputs. Specifically, if the ith column of the design matrix X is categorical with domain {a mathematical formula}Di, we replace it with {a mathematical formula}|Di| binary indicator columns, where the new column corresponding to each {a mathematical formula}d∈Di contains values {a mathematical formula}[Ix1,i=d,…,Ixn,i=d]T; for each data point, exactly one of the new columns is 1, and the rest are all 0. After this transformation, the new columns are treated exactly like the original real-valued columns, and arbitrary modelling techniques for numerical inputs become applicable.
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        A weighted hamming distance kernel for categorical inputs in GPs
       </section-title>
       <paragraph label="Definition 1">
        A problem with the 1-in-{a mathematical formula}K encoding is that using it increases the size of the input space considerably, causing some regression methods to perform poorly. We now define a kernel for handling categorical inputs in GPs more directly. Our kernel is similar to the standard squared exponential kernel of Eq. (1), but instead of measuring the (weighted) squared distance, it computes a (weighted) Hamming distance:{a mathematical formula} For a combination of continuous and categorical input dimensions {a mathematical formula}Pcont and {a mathematical formula}Pcat, we combine the two kernels:{a mathematical formula} Although {a mathematical formula}Kmixed is a straightforward adaptation of the standard kernel in Eq. (1), we are not aware of any prior use of it. To use this kernel in GP regression, we have to show that it is positive definite. Positive definite kernelA function {a mathematical formula}k:I×I↦R is a positive definite kernel iff it is (1) symmetric: for any pair of inputs {a mathematical formula}xi,xj∈I, k satisfies {a mathematical formula}k(xi,xj)=k(xj,xi); and (2) positive definite: for any n inputs {a mathematical formula}x1,…,xn∈I and any n constants {a mathematical formula}c1,…,cn∈R, k satisfies {a mathematical formula}∑i=1n∑j=1n(ci⋅cj⋅k(xi,xj))⩾0.
       </paragraph>
       <paragraph label="Proposition 2">
        {a mathematical formula}Kmixed is positive definiteFor any combination of continuous and categorical input dimensions{a mathematical formula}Pcontand{a mathematical formula}Pcat,{a mathematical formula}Kmixedis a positive definite kernel function.
       </paragraph>
       <paragraph>
        Appendix B in the online appendix provides the proof, which shows that {a mathematical formula}Kmixed can be constructed from simpler positive definite functions, and uses the facts that the space of positive definite kernel functions is closed under addition and multiplication.
       </paragraph>
       <paragraph>
        Our new kernel can be understood as implicitly performing a 1-in-{a mathematical formula}K encoding. Note that Kernel {a mathematical formula}Kmixed has one hyperparameter {a mathematical formula}λi for each input dimension. By using a 1-in-{a mathematical formula}K encoding and kernel {a mathematical formula}Kcont instead, we end up with one hyperparameter {a mathematical formula}λi for each encoded dimension; if we then reparameterize {a mathematical formula}Kcont to share a single hyperparameter {a mathematical formula}λl across the encoded dimensions resulting from a single original input dimension l, we recover {a mathematical formula}Kmixed.
       </paragraph>
       <paragraph>
        Since {a mathematical formula}Kmixed is rather expressive, one may worry about overfitting. Thus, we also experimented with two variations: (1) sharing the same hyperparameter λ across all input dimensions; and (2) sharing {a mathematical formula}λ1 across algorithm parameters and {a mathematical formula}λ2 across instance features. We found that neither variation outperformed {a mathematical formula}Kmixed.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Scaling to large amounts of data with approximate Gaussian processes
      </section-title>
      <paragraph>
       The time complexity of fitting Gaussian processes is cubic in the number of data points, which limits the amount of data that can be used in practice to fit these models. To deal with this obstacle, the machine learning literature has proposed various approximations to Gaussian processes (see, e.g., [93]). To the best of our knowledge, these approximate GPs have previously been applied to runtime prediction only in our work on parameter optimization [59] (considering parameterized algorithms, but only single problem instances). We experimented with the Bayesian committee machine [110], the informative vector machine [72], and the projected process (PP) approximation [94]. All of these methods performed similarly, with the PP approximation having a slight edge. Below, we give the equations for the PPʼs predictive mean and variance; for a derivation, see the Rasmussen &amp; Williams [94].
      </paragraph>
      <paragraph>
       The PP approximation to GPs uses a subset of a of the n training data points, the so-called active set. Let v be a vector consisting of the indices of these a data points. We extend the notation for exact GPs (see Section 3.4) as follows: let {a mathematical formula}Kaa denote the a by a matrix with {a mathematical formula}Kaa(i,j)=k(xv(i),xv(j)) and let {a mathematical formula}Kan denote the a by n matrix with {a mathematical formula}Kan(i,j)=k(xv(i),xj). The predictive distribution of the PP approximation is then a normal distribution with mean and variance{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       We perform h steps of hyperparameter optimization based on a standard GP, trained using a set of a data points sampled uniformly at random without replacement from the n input data points. We then use the resulting hyperparameters and another independently sampled set of a data points (sampled in the same way) for the subsequent PP approximation. In both cases, if {a mathematical formula}a&gt;n, we only use n data points.
      </paragraph>
      <paragraph>
       The complexity of the PP approximation is superlinear only in a; therefore, the approach is much faster when we choose {a mathematical formula}a≪n. The hyperparameter optimization based on a data points takes time {a mathematical formula}O(h⋅a3). In addition, there is a one-time cost of {a mathematical formula}O(a2⋅n) for evaluating the PP equations. Thus, the time complexity for fitting the approximate GP model is {a mathematical formula}O([h⋅a+n]⋅a2), as compared to {a mathematical formula}O(h⋅n3) for the exact GP model. The time complexity for predictions with this PP approximation is {a mathematical formula}O(a) for the mean and {a mathematical formula}O(a2) for the variance of the predictive distribution [94], as compared to {a mathematical formula}O(n) and {a mathematical formula}O(n2), respectively, for the exact version. In our experiments, we set {a mathematical formula}a=300 and {a mathematical formula}h=50 to achieve a good compromise between speed and predictive accuracy.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Random forest models
      </section-title>
      <paragraph>
       Regression trees, as discussed in Section 3.5, are a flexible modelling technique that is particularly effective for discrete input data. However, they are also well known to be sensitive to small changes in the data and are thus prone to overfitting. Random forests [15] overcome this problem by combining multiple regression trees into an ensemble. Known for their strong predictions for high-dimensional and discrete input data, random forests are an obvious choice for runtime predictions of highly parameterized algorithms. Nevertheless, to the best of our knowledge, they have not been used for algorithm runtime prediction except in our own recent work on algorithm configuration [59], [55], [54], [56], which used a prototype implementation of the models we describe here.{sup:6} In the following, we describe the standard RF framework and some non-standard implementation choices we made.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        The standard random forest framework
       </section-title>
       <paragraph>
        A random forest (RF) consists of a set of regression trees. If grown to sufficient depths, regression trees are extraordinarily flexible predictors, able to capture very complex interactions and thus having low bias. However, this means they can also have high variance: small changes in the data can lead to a dramatically different tree. Random forests [15] reduce this variance by aggregating predictions across multiple different trees. (This is an alternative to the pruning procedure described previously; thus, the trees in random forests are not pruned, but are rather grown until each node contains no more than {a mathematical formula}nmin data points.) These trees are made to be different by training them on different subsamples of the training data, and/or by permitting only a random subset of the variables as split variables at each node. We chose the latter option, using the full training set for each tree. (We did experiment with a combination of the two approaches, but found that it yielded slightly worse performance.)
       </paragraph>
       <paragraph>
        Mean predictions for a new input x are trivial: predict the response for x with each tree and average the predictions. The predictive quality improves as the number of trees, B, grows, but computational cost also grows linearly in B. We used {a mathematical formula}B=10 throughout our experiments to keep computational costs low. Random forests have two additional hyperparameters: the percentage of variables to consider at each split point, perc, and the minimal number of data points required in a node to make it eligible to be split further, {a mathematical formula}nmin. We set {a mathematical formula}perc=0.5 and {a mathematical formula}nmin=5 by default.
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Modifications to standard random forests
       </section-title>
       <paragraph>
        We introduce a simple, yet effective, method for quantifying predictive uncertainty in random forests. (Our method is similar in spirit to that of Meinshausen [81], who recently introduced quantile regression trees, which allow for predictions of quantiles of the predictive distribution; in contrast, we predict a mean and a variance.) In each leaf of each regression tree, in addition to the empirical mean of the training data associated with that leaf, we store the empirical variance of that data. To avoid making deterministic predictions for leaves with few data points, we round the stored variance up to at least the constant {a mathematical formula}σ2min; we set {a mathematical formula}σ2min=0.01 throughout. For any input, each regression tree {a mathematical formula}Tb thus yields a predictive mean {a mathematical formula}μb and a predictive variance {a mathematical formula}σb2. To combine these estimates into a single estimate, we treat the forest as a mixture model of B different models. We denote the random variable for the prediction of tree {a mathematical formula}Tb as {a mathematical formula}Lb and the overall prediction as L, and then have {a mathematical formula}L=Lb if {a mathematical formula}Y=b, where Y is a multinomial variable with {a mathematical formula}p(Y=i)=1/B for {a mathematical formula}i=1,…,B. The mean and variance for L can then be expressed as:{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Thus, our predicted mean is simply the mean across the means predicted by the individual trees in the random forest. To compute the variance prediction, we used the law of total variance (see, e.g., [114]), which allows us to write the total variance as the variance across the means predicted by the individual trees (predictions are uncertain if the trees disagree), plus the average variance of each tree (predictions are uncertain if the predictions made by individual trees tend to be uncertain).
       </paragraph>
       <paragraph>
        A second non-standard ingredient in our models concerns the choice of split points. Consider splits on a real-valued variable j. Note that when the loss in Eq. (4) is minimized by choosing split point s between the values of {a mathematical formula}xk,j and {a mathematical formula}xl,j, we are still free to choose the exact location of s anywhere in the interval {a mathematical formula}(xk,j,xl,j). Traditionally, s is chosen as the midpoint between {a mathematical formula}xk,j and {a mathematical formula}xl,j. Instead, here we draw it uniformly at random from {a mathematical formula}(xk,j,xl,j). In the limit of an infinite number of trees, this leads to a linear interpolation of the training data instead of a partition into regions of constant prediction. Furthermore, it causes variance estimates to vary smoothly and to grow with the distance from observed data points.
       </paragraph>
      </section>
      <section label="4.3.3">
       <section-title>
        Complexity of fitting random forests
       </section-title>
       <paragraph>
        The computational cost for fitting a random forest is relatively low. We need to fit B regression trees, each of which is somewhat easier to fit than a normal regression tree, since at each node we only consider {a mathematical formula}v=max(1,⌊perc⋅p⌋) out of the p possible split variables. Building B trees simply takes B times as long as building a single tree. Thus—by the same argument as for regression trees—the complexity of learning a random forest is {a mathematical formula}O(B⋅v⋅n2⋅logn) in the worst case (splitting off one data point at a time) and {a mathematical formula}O(B⋅v⋅n⋅log2n) in the best case (perfectly balanced trees). Our random forest implementation is based on a port of Matlabʼs regression tree code to C, which yielded speedups of between one and two orders of magnitude.
       </paragraph>
       <paragraph>
        Prediction with a random forest model entails predicting with B regression trees (plus an {a mathematical formula}O(B) computation to compute the mean and variance across those predictions). The time complexity of a single prediction is thus {a mathematical formula}O(B⋅n) in the worst case and {a mathematical formula}O(B⋅logn) for perfectly balanced trees.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Problem-specific instance features
     </section-title>
     <paragraph>
      While the methods we have discussed so far could be used to model the performance of any algorithm for solving any problem, in our experiments, we investigated specific NP-complete problems. In particular, we considered the propositional satisfiability problem (SAT), mixed integer programming (MIP) problems, and the travelling salesperson problem (TSP). Our reasons for choosing these three problems are as follows. SAT is the prototypical NP-hard decision problem and is thus interesting from a theory perspective; modern SAT solvers are also one of the most prominent approaches in hardware and software verification [92]. MIP is a canonical representation for constrained optimization problems with integer-valued and continuous variables, which serves as a unifying framework for NP-complete problems and combines the expressive power of integrality constraints with the efficiency of continuous optimization. As a consequence, it is very widely used both in academia and industry [61]. Finally, TSP is one of the most widely studied NP-hard optimization problems, and also of considerable interest for industry [21].
     </paragraph>
     <paragraph>
      We tailor EPMs to a particular problem through the choice of instance features.{sup:7} Here we describe comprehensive sets of features for SAT, MIP, and TSP. For each of these problems, we summarize sets of features found in the literature and introduce many novel features. While all these features are polynomial-time computable, we note that some of them can be computationally expensive for very large instances (e.g., taking cubic time). For some applications such expensive features will be reasonable—in particular, we note that for applications that take features as a one-time input, but build models repeatedly, it can even make sense to use features whose cost exceeds that of solving the instance; examples of such applications include model-based algorithm configuration [55] and complex empirical analyses based on performance predictions [53], [57]. In runtime-sensitive applications, on the other hand, it may make sense to use only a subset of the features described here. To facilitate this, we categorize all features into one of four “cost classes”: trivial, cheap, moderate, and expensive. In our experimental evaluation, we report the empirical cost of these feature classes and the predictive performance that can be achieved using them (see Table 3 on page 97). We also identify features introduced in this work and quantify their contributions to model performance.
     </paragraph>
     <paragraph>
      Probing features are a generic family of features that deserves special mention. They are computed by briefly running an existing algorithm for the given problem on the given instance and extracting characteristics from that algorithmʼs trajectory—an idea closely related to that of landmarking in meta-learning [91]. Probing features can be defined with little effort for a wide variety of problems; indeed, in earlier work, we introduced the first probing features for SAT [90] and showed that probing features based on one type of algorithm (e.g., local search) are often useful for predicting the performance of another type of algorithm (e.g., tree search). Here we introduce the first probing features for MIP and TSP. Another new, generic family of features are timing features, which measure the time other groups of features take to compute. Code and binaries for computing all our features, along with documentation providing additional details, are available online at http://www.cs.ubc.ca/labs/beta/Projects/EPMs/.
     </paragraph>
     <section label="5.1">
      <section-title>
       Features for Propositional Satisfiability (SAT)
      </section-title>
      <paragraph>
       Fig. 1 summarizes 138 features for SAT. Since various preprocessing techniques are routinely used before applying a general-purpose SAT solver and typically lead to substantial reductions in instance size and difficulty (especially for industrial-like instances), we apply the preprocessing procedure SATElite[23] on all instances first, and then compute instance features on the preprocessed instances. The first 90 features, with the exception of features 22–26 and 32–36, were introduced in our previously published work on SATzilla[90], [119]. They can be categorized as problem size features (1–7), graph-based features (8–36), balance features (37–49), proximity to Horn formula features (50–55), DPLL probing features (56–62), LP-based features (63–68), and local search probing features (69–90).
      </paragraph>
      <paragraph>
       Our new features (devised over the last five years in our ongoing work on SATzilla and so far only mentioned in short solver descriptions [118], [121]) fall into four categories. First, we added two additional subgroups of graph-based features. Our new diameter features 22–26 are based on the variable graph [41]. For each node i in that graph, we compute the longest shortest path between i and any other node. As with most of the features that follow, we then compute various statistics over this vector (e.g., mean, max); we do not state the exact statistics for each vector below but list them in Fig. 1. Our new clustering coefficient features 32–36 measure the local cliqueness of the clause graph. For each node in the clause graph, let p denote the number of edges present between the node and its neighbours, and let m denote the maximum possible number of such edges; we compute {a mathematical formula}p/m for each node.
      </paragraph>
      <paragraph>
       Second, our new clause learning features (91–108) are based on statistics gathered in 2-second runs of Zchaff_rand[80]. We measure the number of learned clauses (features 91–99) and the length of the learned clauses (features 100–108) after every 1000 search steps. Third, our new survey propagation features (109–126) are based on estimates of variable bias in a SAT formula obtained using probabilistic inference [46]. We used VARSATʼs implementation to estimate the probabilities that each variable is true in every satisfying assignment, false in every satisfying assignment, or unconstrained. Features 109–117 measure the confidence of survey propagation (that is, {a mathematical formula}max(Ptrue(i)/Pfalse(i),Pfalse(i)/Ptrue(i)) for each variable i) and features 118–126 are based on the {a mathematical formula}Punconstrained vector.
      </paragraph>
      <paragraph>
       Finally, our new timing features (127–138) measure the time taken by 12 different blocks of feature computation code: instance preprocessing by SATElite, problem size (1–6), variable-clause graph (clause node) and balance features (7, 13–17, 37–41, 47–49); variable-clause graph (variable node), variable graph and proximity to Horn formula features (8–12, 18–21, 42–46, 50–55); diameter-based features (22–26); clause graph features (27–36); unit propagation features (56–60); search space size estimation (61–62); LP-based features (63–68); local search probing features (69–90) with SAPS and GSAT; clause learning features (91–108); and survey propagation features (109–126).
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Features for mixed integer programs
      </section-title>
      <paragraph>
       Fig. 2 summarizes 121 features for mixed integer programs (i.e., MIP instances). These include 101 features based on existing work [76], [48], [67], 15 new probing features, and 5 new timing features. Features 1–101 are primarily based on features for the combinatorial winner determination problem from our past work [76], generalized to MIP and previously only described in a Ph.D. thesis [48]. These features can be categorized as problem type &amp; size features (1–25), variable-constraint graph features (26–49), linear constraint matrix features (50–73), objective function features (74–91), and LP-based features (92–95). We also integrated ideas from the feature set used by Kadioglu et al. [67] (right-hand side features (96–101) and the computation of separate statistics for continuous variables, non-continuous variables, and their union). We extended existing features by adding richer statistics where applicable: medians, variation coefficients (vc), and percentile ratios (q90/q10) of vector-based features.
      </paragraph>
      <paragraph>
       We introduce two new sets of features. Firstly, our new MIP probing features 102–116 are based on 5-second runs of CPLEX with default settings. They are obtained via the CPLEX API and include 6 presolving features based on the output of CPLEXʼs presolving phase (102–107); 5 probing cut usage features describing the different cuts CPLEX used during probing (108–112); and 4 probing result features summarizing probing runs (113–116). Secondly, our new timing features 117–121 capture the CPU time required for computing five different groups of features: variable-constraint graph, linear constraint matrix, and objective features for three subsets of variables (“continuous”, “non-continuous”, and “all”, 26–91); LP-based features (92–95); and CPLEX probing features (102–116). The cost of computing the remaining features (1–25, 96–101) is small (linear in the number of variables or constraints).
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Features for the travelling salesperson problem (TSP)
      </section-title>
      <paragraph>
       Fig. 3 summarizes 64 features for the travelling salesperson problem (TSP). Features 1–50 are new, while features 51–64 were introduced by Smith-Miles et al. [108]. Features 51–64 capture the spatial distribution of nodes (features 51–61) and clustering of nodes (features 62–64); we used the authorsʼ code (available at http://www.vanhemert.co.uk/files/TSP-feature-extract-20120212.tar.gz) to compute these features.
      </paragraph>
      <paragraph>
       Our 50 new TSP features are as follows.{sup:8} The problem size feature (1) is the number of nodes in the given TSP. The cost matrix features (2–4) are statistics of the cost between two nodes. Our minimum spanning tree features (5–11) are based on constructing a minimum spanning tree over all nodes in the TSP: features 5–8 are the statistics of the edge costs in the tree and features 9–11 are based on its node degrees. Our cluster distance features (12–14) are based on the cluster distance between every pair of nodes, which is the minimum bottleneck cost of any path between them; here, the bottleneck cost of a path is defined as the largest cost along the path. Our local search probing features (15–32) are based on 20 short runs (1000 steps each) of LK [78], using the implementation available from [22]. Specifically, features 15–17 are based on the tour length obtained by LK; features 18–20, 21–23, and 24–26 are based on the tour length of local minima, the tour quality improvement per search step, and the number of search steps to reach a local minimum, respectively; features 27–29 measure the Hamming distance between two local minima; and features 30–32 describe the probability of edges appearing in any local minimum encountered during probing. Our branch and cut probing features (33–43) are based on 2-second runs of Concorde. Specifically, features 33–35 measure the improvement of lower bound per cut; feature 36 is the ratio of upper and lower bound at the end of the probing run; and features 37–43 analyze the final LP solution. Feature 44 is the autocorrelation coefficient: a measure of the ruggedness of the search landscape, based on an uninformed random walk (see, e.g., [42]). Finally, our timing features 45–50 measure the CPU time required for computing feature groups 2–7 (the cost of computing the number of nodes can be ignored).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Performance predictions for new instances
     </section-title>
     <paragraph>
      We now study the performance of the models described in Sections 3 and 4 (see Table 1 for an overview), based on (various subsets of) the features described in Section 5. In this section, we consider the (only) problem considered by most past work: predicting the performance achieved by the default configuration of a given algorithm on new instances. (We go on to consider making predictions for novel algorithm configurations in Sections 7 and 8.) For brevity, we only present representative empirical results. The full results of our experiments are available in an online appendix at http://www.cs.ubc.ca/labs/beta/Projects/EPMs. All of our data, features, and source code for replicating our experiments is available from the same site.
     </paragraph>
     <section label="6.1">
      <section-title>
       Instances and solvers
      </section-title>
      <paragraph>
       For SAT, we used a wide range of instance distributions: INDU, HAND, and RAND are collections of industrial, handmade, and random instances from the international SAT competitions and races, and COMPETITION is their union; SWV and IBM are sets of software and hardware verification instances, and SWV-IBM is their union; RANDSAT is a subset of RAND containing only satisfiable instances. We give more details about these distributions in Appendix A.1. For all distributions except RANDSAT, we ran the popular tree search solver, Minisat 2.0[24]. For INDU, SWV and IBM, we also ran two additional solvers: CryptoMinisat[109] (which won SAT Race 2010 and received gold and silver medals in the 2011 SAT Competition) and SPEAR[5] (which has shown state-of-the-art performance on IBM and SWV with optimized parameter settings [49]). Finally, to evaluate predictions for local search algorithms, we used the RANDSAT instances, and considered two solvers: tnm[112] (which won the random satisfiable category of the 2009 SAT Competition) and the dynamic local search algorithm SAPS[60] (a baseline).
      </paragraph>
      <paragraph>
       For MIP, we used two instance distributions from computational sustainability (RCW and CORLAT), one from winner determination in combinatorial auctions (REG), two unions of these (CR := CORLAT ∪ RCW and CRR := CORLAT ∪ REG ∪ RCW), and a large and diverse set of publicly available MIP instances (BIGMIX). Details about these distributions are given in Appendix A.2. We used the two state-of-the-art commercial solvers CPLEX[62] and Gurobi[35] (versions 12.1 and 2.0, respectively) and the two strongest non-commercial solvers, SCIP[11] and lp_solve[10] (versions 1.2.1.4 and 5.5, respectively).
      </paragraph>
      <paragraph>
       For TSP, we used three instance distributions (detailed in Appendix A.3): random uniform Euclidean instances (RUE), random clustered Euclidean instances (RCE), and TSPLIB, a heterogeneous set of prominent TSP instances. On these instance sets, we ran the state-of-the-art systematic and local search algorithms, Concorde[2] and LK-H[40]. For the latter, we computed runtimes as the time required to find an optimal solution.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Experimental setup
      </section-title>
      <paragraph>
       To collect algorithm runtime data, for each algorithm–distribution pair, we executed the algorithm using default parameters on all instances of the distribution, measured its runtimes, and collected the results in a database. All algorithm runs were executed on a cluster of 55 dual 3.2 GHz Intel Xeon PCs with 2 MB cache and 2 GB RAM, running OpenSuSE Linux 11.1; runtimes were measured as CPU time on these reference machines. We terminated each algorithm run after one CPU hour; this gave rise to capped runtime observations, because for each run that was terminated in this fashion, we only observed a lower bound on the runtime. Like most past work on runtime modelling, we simply counted such capped runs as having taken one hour. (In Section 9 we investigate alternatives and conclude that a better treatment of capped runtime data improves predictive performance for our best-performing model.) Basic statistics of the resulting runtime distributions are given in Table 3; Table C.1 in the online appendix lists all the details.
      </paragraph>
      <paragraph>
       We evaluated different model families by building models on a subset of the data and assessing their performance on data that had not been used to train the models. This can be done visually (as, e.g., in the scatterplots in Fig. 4 on page 96, which show cross-validated predictions for a random subset of up to 1000 data points), or quantitatively. We considered three complementary quantitative metrics to evaluate mean predictions {a mathematical formula}μ1,…,μn and predictive variances {a mathematical formula}σ12,…,σn2 given true performance values {a mathematical formula}y1,…,yn. Root mean squared error (RMSE) is defined as {a mathematical formula}1/n∑i=1n(yi−μi)2; Pearsonʼs correlation coefficient (CC) is defined as {a mathematical formula}(∑i=1n(μiyi)−n⋅μ¯⋅y¯)/((n−1)⋅sμ⋅sy), where {a mathematical formula}x¯ and {a mathematical formula}sx denote sample mean and standard deviation of x; and log likelihood (LL) is defined as {a mathematical formula}∑i=1nlogφ(yi−μiσi), where φ denotes the probability density function (PDF) of a standard normal distribution. Intuitively, LL is the log probability of observing the true values {a mathematical formula}yi under the predicted distributions {a mathematical formula}N(μi,σi2). For CC and LL, higher values are better, while for RMSE lower values are better. We used 10-fold cross-validation and report means of these measures across the 10 folds. We assessed the statistical significance of our findings using a Wilcoxon signed-rank test (we use this paired test, since cross-validation folds are correlated).
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Predictive quality
      </section-title>
      <paragraph>
       Table 2 provides quantitative results for all benchmarks, and Fig. 4 visualizes results. At the broadest level, we can conclude that most of the methods were able to capture enough about algorithm performance on training data to make meaningful predictions on test data, most of the time: easy instances tended to be predicted as being easy, and hard ones as being hard. Take, for example the case of predicting the runtime of Minisat 2.0 on a heterogeneous mix of SAT competition instances (see the leftmost column in Fig. 2 and the top row of Table 2). Minisat 2.0 runtimes varied by almost six orders of magnitude, while predictions with the better models rarely were off by more than one order of magnitude (outliers may draw the eye in the scatterplot, but quantitatively, the RMSE for predicting {a mathematical formula}log10 runtime was low—e.g., 0.47 for random forests, which means an average misprediction of a factor of {a mathematical formula}100.47&lt;3). While the models were certainly not perfect, note that even the relatively poor predictions of ridge regression variant RR tended to be accurate within about an order of magnitude, which was enough to enable the portfolio-based algorithm selector SATzilla[119] to win five medals in each of the 2007 and 2009 SAT competitions. (Switching to random forest models after 2009 further improved SATzillaʼs performance [120].)
      </paragraph>
      <paragraph>
       In our experiments, random forests were the overall winner among the different methods, yielding the best predictions in terms of all our quantitative measures.{sup:9} For SAT, random forests were always the best method, and for MIP they yielded the best performance for the most heterogeneous instance set, BIGMIX (see Column 2 of Fig. 4). We attribute the strong performance of random forests on highly heterogeneous data sets to the fact that, as a tree-based approach, they can model very different parts of the data separately; in contrast, the other methods allow the fit in a given part of the space to be influenced more by data in distant parts of the space. Indeed, the ridge regression variants made extremely bad predictions for some outlying points on BIGMIX. For the more homogeneous MIP data sets, either random forests or projected processes performed best, often followed closely by ridge regression variant RR. The performance of CPLEX on set RCW was a special case in that it could be predicted extremely well by all models (see Column 3 of Fig. 4). Finally, for TSP, projected processes and ridge regression had a slight edge for the homogeneous RUE and RCE benchmarks, whereas tree-based methods (once again) performed best on the most heterogeneous benchmark, TSPLIB. The last column of Fig. 4 shows that, in the case where random forests performed worst, the qualitative differences in predictions were small. In terms of computational requirements, random forests were among the cheapest methods, taking between 0.1 and 11 seconds to learn a model.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Results based on different classes of instance feature
      </section-title>
      <paragraph>
       While the previous experiments focused on the performance of the various models based on our entire feature set, we now study the performance of different subsets of features when using the overall best-performing model, random forests. Table 3 presents the results and also lists the cost of the various feature subsets (which in most cases is much smaller than the runtime of the algorithm being modelled). On the broadest level, we note that predictive performance improved as we used more computationally expensive features: e.g., while the trivial features were basically free, they yielded rather poor performance, whereas using the entire feature set almost always led to the best performance. Interestingly, however, for all SAT benchmarks, using at most moderately expensive features yielded results statistically insignificantly different from the best, with substantial reductions in feature computation time. The same was even true for several SAT benchmarks when considering at most cheap features. Our new features clearly showed value: for example, our cheap feature set yielded similar predictive performance as the set of previous features at a much lower cost; and our moderate feature set tended to yield better performance than the previous one at comparable cost. Our new features led to especially clear improvements for MIP, yielding significantly better predictive performance than the previous features in 11/12 cases. Similarly, for TSP, our new features improved performance significantly in 4/6 cases (TSPLIB was too small to achieve reliable results in the two remaining cases, with even the trivial features performing insignificantly worse than the best).
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Impact of hyperparameter optimization
      </section-title>
      <paragraph>
       Table 4 shows representative results for the optimization of hyperparameters: it improved robustness somewhat for the ridge regression methods (decreasing the number of extreme outlier predictions) and improved most models slightly across the board. However, these improvements came at the expense of dramatically slower training.{sup:10} In practice, the small improvements in predictive performance that can be obtained via hyperparameter optimization appear likely not to justify this drastic increase in computational cost (e.g., consider model-based algorithm configuration procedures, which iterate between model construction and data gathering, constructing thousands of models during typical algorithm configuration runs [55]). Thus, we evaluate model performance based on fixed default hyperparameters in the rest of this article. For completeness, our online appendix reports analogous results for models with optimized hyperparameters.
      </paragraph>
     </section>
     <section label="6.6">
      <section-title>
       Predictive quality with sparse training data
      </section-title>
      <paragraph>
       We now study how the performance of EPM techniques changes based on the quantity of training data available. Fig. 5 visualizes this relationship for six representative benchmarks; data for all benchmarks appears in the online appendix. Here and in the following, we use CC rather than RMSE for such scaling plots, for two reasons. First, RMSE plots are often cluttered due to outlier instances for which prediction accuracy is poor (particularly for the ridge regression methods). Second, plotting CC facilitates performance comparisons across benchmarks, since CC {a mathematical formula}∈[−1,1].
      </paragraph>
      <paragraph>
       Overall, random forests performed best across training set sizes. Both versions of ridge regression (SP and RR) performed poorly for small training sets. This observation is significant, since most past work employed ridge regression with large amounts of data (e.g., in SATzilla[119]), only measuring its performance in what turns out to be a favourable condition for it.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Performance predictions for new parameter configurations
     </section-title>
     <paragraph>
      We now move from predicting a single algorithmʼs runtime across a distribution of instances to predicting runtime across a family of algorithms (achieved by changing a given solverʼs parameter settings or configurations). For parameterized algorithms, there are four ways in which we can assess the prediction quality achieved by a model:
     </paragraph>
     <list>
      <list-item label="1.">
       Predictions for training configurations on training instances. Predictions for this most basic case are useful for succinctly modelling known algorithm performance data. Interestingly, several methods already perform poorly here.
      </list-item>
      <list-item label="2.">
       Predictions for training configurations on test instances. Such predictions can be used to make a per-instance decision about which of a set of given parameter configurations will perform best on a previously unseen test instance, for example in algorithm selection [104], [119], [116], [67].
      </list-item>
      <list-item label="3.">
       Predictions for test configurations on training instances. This case is important in algorithm configuration, where the goal is to find high-quality parameter configurations for the given training instances [55], [56].
      </list-item>
      <list-item label="4.">
       Predictions for test configurations on test instances. This most general case is the most natural “pure prediction” problem (see [96], [20]). It is also important for per-instance algorithm configuration, where one could use a model to search for the configuration that is most promising for a previously-unseen test instance [50].
      </list-item>
     </list>
     <paragraph>
      We can understand the evaluation in the previous section as a special case of 2, where we only consider an algorithmʼs default configuration, but vary instances. We now consider the converse case 3, where instances do not vary, but configurations do. We consider case 4, in which we aim to generalize across both parameter configurations and instances, in Section 8.
     </paragraph>
     <section label="7.1">
      <section-title>
       Parameter configuration spaces
      </section-title>
      <paragraph>
       {a mathematical formula}
      </paragraph>
      <paragraph>
       Here and in Section 8, we study two highly parameterized algorithms for two different problems: SPEAR for SAT and CPLEX for MIP.
      </paragraph>
      <paragraph>
       For the industrial SAT solver SPEAR[3], we used the same parameter configuration space as in previous work [49]. This includes 26 parameters, out of which ten are categorical, four are integral, and twelve are continuous. The categorical parameters mainly control heuristics for variable and value selection, clause sorting, and resolution ordering, and also enable or disable optimizations, such as the pure literal rule. The continuous and integer parameters mainly deal with activity, decay, and elimination of variables and clauses, as well as with the randomized restart interval and percentage of random choices; we discretized each of them to between three and eight values. In total, and based on our discretization of continuous parameters, SPEAR has {a mathematical formula}8.34×1017 different configurations.
      </paragraph>
      <paragraph>
       For the commercial MIP solver IBM ILOG CPLEX, we used the same configuration space with 76 parameters as in previous work [52]. These parameters exclude all CPLEX settings that change the problem formulation (e.g., the optimality gap below which a solution is considered optimal). They include 12 preprocessing parameters (mostly categorical); 17 MIP strategy parameters (mostly categorical); 11 categorical parameters deciding how aggressively to use which types of cuts; 9 real-valued MIP “limit” parameters; 10 simplex parameters (half of them categorical); 6 barrier optimization parameters (mostly categorical); and 11 further parameters. In total, and based on our discretization of continuous parameters, these parameters gave rise to {a mathematical formula}1.90×1047 unique configurations.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Experimental setup
      </section-title>
      <paragraph>
       For the experiments in this and the next section, we gathered runtime data for SPEAR and CPLEX by executing each of them with 1000 randomly sampled parameter configurations. We ran each solver on instances from distributions for which we expected it to yield state-of-the-art performance: SPEAR on SWV and IBM; CPLEX on all MIP instance distributions discussed in the previous section. The runtime data for this and the next section was gathered on the 840-node Westgrid cluster Glacier (each of whose nodes is equipped with two 3.06 GHz Intel Xeon 32-bit processors and 2–4 GB RAM). Due to the large number of algorithm runs required for the experiments described in Section 8, we restricted the cutoff time of each single algorithm run to 300 seconds (compared to the 3000 seconds for the runs with the default parameter setting used in Section 6). In the following, we consider the performance of EPMs as parameters vary, but instance features do not; thus, here we used only one instance from each distribution and have no use for instance features. For each dataset, we selected the easiest benchmark instance amongst the ones for which the default parameter configuration required more than ten seconds on our reference machines. As before, we used 10-fold cross validation to assess the accuracy of our model predictions for previously unseen parameter configurations.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Predictive quality
      </section-title>
      <paragraph>
       Table 6 quantifies the performance of all models on all benchmark problems, and Fig. 6 visualizes predictions. Again, we see that qualitatively, solver runtime as a function of parameter settings could be predicted quite well by most methods, even as runtimes varied by factors of over 1000 (see Fig. 6). We observe that projected processes, random forests, and ridge regression variant RR consistently outperformed regression trees; this is significant, as regression trees are the only model that has previously been used for predictions in configuration spaces with categorical parameters [8]. On the other hand, the poor performance of neural networks and of SPORE-FoBa (which mainly differs from variant RR in its feature expansion and selection) underlines that selecting the right (combinations of) features is not straightforward. Overall, the best performance was achieved by projected processes (applying our kernel function for categorical parameters from Section 4.1.2). As in the previous section, however, random forests were also either best or very close to the best for every data set.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Predictive quality with sparse training data
      </section-title>
      <paragraph>
       Results remained similar when varying the number of training configurations. As Fig. 7 shows, projected processes performed best overall, closely followed by random forests. Ridge regression variant RR often produced poor predictions when trained using a relatively small number of training data points, but performed well when given sufficient data. Finally, both SPORE-FoBa and neural networks performed relatively poorly regardless of the amount of data given.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Performance predictions in the joint space of instance features and parameter configurations
     </section-title>
     <paragraph>
      We now consider more challenging prediction problems for parameterized algorithms. In the first experiments discussed here (Sections 8.2 Predictive quality, 8.3 Predictive quality with sparse training data) we tested predictions on the most challenging case, where both configurations and instances are previously unseen. Later in the section (Section 8.4) we evaluate predictions made on all four combinations of training/test instances and training/test configurations.
     </paragraph>
     <section label="8.1">
      <section-title>
       Experimental setup
      </section-title>
      <paragraph>
       For the experiments in this section, we used SPEAR and CPLEX with the same configuration spaces as in Section 7 and the same {a mathematical formula}M=1000 randomly sampled configurations. We ran each of these configurations on all of the P problem instances in each of our instance sets (with P ranging from 604 to 2000), generating runtime data that can be thought of as a {a mathematical formula}M×P matrix. We split both the M configurations and the P instances into training and test sets of equal size (using uniform random permutations). We then trained our EPMs on a fixed number of n randomly selected combinations of the {a mathematical formula}P/2 training instances and {a mathematical formula}M/2 training configurations.
      </paragraph>
      <paragraph>
       We note that while a sound empirical evaluation of our methods required gathering a very large amount of data, such extensive experimentation is not required to use them in practice. The execution of the runs used in this section (between 604 000 and 2  000 000 per instance distribution) took over 60 CPU years, with time requirements for individual data sets ranging between 1.3 CPU years (SPEAR on SWV, where many runs took less than a second) and 18 CPU years (CPLEX on RCW, where most runs timed out). However, as we will demonstrate in Section 8.3, our methods often yield surprisingly accurate predictions based on data that can be gathered overnight on a single machine.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Predictive quality
      </section-title>
      <paragraph>
       We now examine the most interesting case, where test instances and configurations were both previously unseen. Table 7 provides quantitative results of model performance based on {a mathematical formula}n=10000 training data points, and Fig. 8 visualizes performance. Overall, we note that the best models generalized to new configurations and to new instances almost as well as to either alone (compare to Sections 6 and 7, respectively). On the most heterogeneous data set, CPLEX-BIGMIX, we once again witnessed extremely poorly predicted outliers for the ridge regression variants, but in all other cases, the models captured the large spread in runtimes (above 5 orders of magnitude) quite well. As in the experiments in Section 6.3, the tree-based approaches, which are able to model different regions of the input space independently, performed best on the most heterogeneous data sets. Fig. 8 also shows some qualitative differences in predictions: for example, ridge regression, neural networks, and projected processes sometimes overpredicted the runtime of the shortest runs, while the tree-based methods did not have this problem. Random forests performed best in all cases, which is consistent with their robust predictions in both the instance and the configuration space observed earlier.
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Predictive quality with sparse training data
      </section-title>
      <paragraph>
       Next, we studied the amount of data that was actually needed to obtain good predictions, varying the number n of randomly selected combinations of training instances and configurations. Fig. 9 shows the correlation coefficients achieved by the various methods as a function of the amount of training data available. Overall, we note that most models already performed remarkably well (yielding correlation coefficients of 0.9 and higher) based on a few hundred training data points. This confirmed the practicality of our methods: on a single machine, it takes at most 12.5 hours to execute 150 algorithm runs with a cutoff time of 300 seconds. Thus, even users without access to a cluster can expect to be able to execute sufficiently many algorithm runs overnight to build a decent empirical performance model for their algorithm and instance distribution of interest. Examining our results in some more detail, the ridge regression variants again had trouble on the most heterogeneous benchmark CPLEX -BIGMIX, but otherwise performed quite well. Overall, random forests performed best across different training set sizes. Naturally, all methods required more data to make good predictions for heterogeneous benchmarks (e.g., CPLEX-BIGMIX) than for relatively homogeneous ones (e.g., CPLEX-CORLAT, for which the remarkably low number of 30 data points already yielded correlation coefficients exceeding 0.9).
      </paragraph>
     </section>
     <section label="8.4">
      <section-title>
       Evaluating generalization performance in instance and configuration space
      </section-title>
      <paragraph>
       Now, we study all four combinations of predictions on training/test instances and training/test configurations. (See the beginning of Section 7 for a description of each scenario.) Our results are summarized in Table 8 and Fig. 10, Fig. 11. For the figures, we sorted instances by average hardness (across configurations), and parameter configurations by average performance (across instances), generating a heatmap with instances on the x-axis, configurations on the y-axis, and greyscale values representing algorithm runtime for given configuration/instance combinations. We compare heatmaps representing true runtimes against those based on the predictions obtained from each of our models. Here, we only show results for the two scenarios where the performance advantage of random forests (the overall best method based on our results reported so far) over the other methods was highest (the heterogeneous data set SPEAR-SWV-IBM) and lowest (the homogeneous data set CPLEX-CORLAT); heatmaps for all data sets and model types are given in Figs. D.21–D.29 in the online appendix.
      </paragraph>
      <paragraph>
       Fig. 10 shows the results for benchmark SPEAR-SWV-IBM. It features one column for each of the four combinations of training/test instances and training/test configurations, allowing us to visually assess how well the respective generalization works for each of the models. We note that in this case, the true heatmaps are almost indistinguishable from those predicted by random forests (and regression trees). Even for the most challenging case of unseen problem instances and parameter configurations, the tree-based methods captured the non-trivial interaction pattern between instances and parameter configurations. On the other hand, the non-tree-based methods (ridge regression variants, neural networks, and projected processes) only captured instance hardness, failing to distinguish good from bad configurations even in the simplest case of predictions for training instances and training configurations.
      </paragraph>
      <paragraph>
       Fig. 11 shows the results for benchmark CPLEX-CORLAT. For the simplest case of predictions on training instances and configurations, the tree-based methods yielded predictions close to the true runtimes, capturing both instance hardness and performance of parameter configurations. In contrast, even in this simple case, the other methods only captured instance hardness, predicting all configurations to be roughly equal in performance. Random forests generalized better to test instances than to test configurations (compare the 3rd and 2nd columns of Fig. 11); this trend is also evident quantitatively in Table 8 for all CPLEX benchmarks. Regression tree predictions were visually indistinguishable from those of random forests; this strong qualitative performance is remarkable, considering that quantitatively they performed worse than other methods in terms of measures such as RMSE (see the results for CPLEX-CORLAT in Table 8).
      </paragraph>
      <paragraph>
       Finally, we investigated once more how predictive quality depends on the quantity of training data, focusing on random forests (Fig. 12). For SPEAR-SWV-IBM, 100 training data points sufficed to obtain random forest models that captured the most salient features (e.g., they correctly determined the simplicity of the roughly 20% easiest instances); more training data points gradually improved qualitative predictions, especially in distinguishing good from bad configurations. Likewise, for CPLEX-CORLAT, salient features (e.g., the simplicity of the roughly 25% easiest instances) could be detected based on 100 training data points, and more training data improved qualitative predictions to capture some of the differences between good and bad configurations. Overall, increases in the training set size yielded diminishing returns, and even predictions based on the entire cross-product of training instances and parameter configurations (i.e., between 151 000 and 500 000 runs) were not much different from those based on a subset of 10 000 samples (representing 2% to 6.6% of the entire training data).
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Improved handling of censored runtimes in random forests
     </section-title>
     <paragraph>
      Most past work on predicting algorithm runtime has treated algorithm runs that were terminated prematurely at a so-called captime κ as if they finished at time κ. Thus, we adopted the same practice in the model comparisons we have described so far (using captimes of 3000 seconds for the runs in Section 6 and 300 seconds for the runs in Sections 7 and 8). Now, we revisit this issue for random forests.
     </paragraph>
     <paragraph>
      Formally, terminating an algorithm run after a captime (or censoring threshold) κ yields a right-censored data point: we learn that κ is a lower bound on the actual time the algorithm run required. Let {a mathematical formula}yi denote the actual (unknown) runtime of algorithm run i. Under partial right censoring, our training data is {a mathematical formula}(xi,zi,ci)i=1n, where {a mathematical formula}xi is our usual input vector (a vector of instance features, parameter values, or both combined), {a mathematical formula}zi∈R is a (possibly censored) runtime observation, and {a mathematical formula}ci∈{0,1} is a censoring indicator such that {a mathematical formula}zi=yi if {a mathematical formula}ci=0 and {a mathematical formula}zi&lt;yi if {a mathematical formula}ci=1.
     </paragraph>
     <paragraph>
      Observe that the typical, simplistic strategy for dealing with censored data produces biased models; intuitively, treating slow runs as though they were faster than they really were biases our training data downwards, and hence likewise biases predictions. Statisticians, mostly in the literature on so-called “survival analysis” from actuarial science, have developed strategies for building unbiased regression models based on censored data [86]. (Actuaries need to predict when people will die, given mortality data and the ages of people still living.) Gagliolo et al. [28], [27] were the first to use techniques from this literature for runtime prediction. Specifically, they used a method for handling censored data in parameterized probabilistic models and employed the resulting models to construct dynamic algorithm portfolios. In the survival analysis literature, Schmee &amp; Hahn [100] described an iterative procedure for handling censored data points in linear regression models. We employed this technique to improve the runtime predictions made by our portfolio-based algorithm selection method SATzilla[117]. While to the best of our knowledge, no other methods from this literature have been applied to algorithm runtime prediction, there exist several candidates for consideration in future work. In Gaussian processes, one could use approximations to handle the non-Gaussian observation likelihoods resulting from censorship; for example, Ertin [25] described a Laplace approximation for handling right-censored data. Random forests (RFs) have previously been adapted to handle censored data [102], [44], but the classical methods yield non-parametric Kaplan–Meier estimators that are undefined beyond the largest uncensored data point. Here, we describe a simple improvement of the method by Schmee &amp; Hahn [100] for use with random forests that we developed in the context of handling censored data in model-based algorithm configuration [54], [51].
     </paragraph>
     <paragraph>
      We denote the probability density function (PDF) and cumulative distribution function (CDF) of a Normal distribution by φ and Φ, respectively. Let {a mathematical formula}xi be an input with censored runtime {a mathematical formula}κi. Given a Gaussian predictive distribution {a mathematical formula}N(μi,σi2), the truncated Gaussian distribution {a mathematical formula}N(μi,σi2)⩾κi is defined by the PDF{a mathematical formula}
     </paragraph>
     <paragraph>
      The method of Schmee &amp; Hahn [100] is an Expectation Maximization (EM) algorithm. Applied to an RF model as its base model, that algorithm would first fit an initial RF using only uncensored data and then iterate between the following steps:
     </paragraph>
     <list>
      <list-item label="(E)">
       For each tree T in the RF and each i s.t. {a mathematical formula}ci=1: {a mathematical formula}yˆi(T)←mean of N(μi,σi2)⩾zi;
      </list-item>
      <list-item label="(M)">
       Refit the RF using {a mathematical formula}(θi,yiˆ(T))i=1n as the basis for tree T.
      </list-item>
     </list>
     <paragraph>
      Here, {a mathematical formula}N(μi,σi2)⩾zi denotes the predictive distribution of the current RF for data point i, truncated at{a mathematical formula}zi, that is, conditioned on the fact that it is at least as large as{a mathematical formula}zi. While the mean of {a mathematical formula}N(μi,σi2)⩾zi is the best single value to impute for the ith data point, in the context of RF models this approach yields overly confident predictions: all trees would perfectly agree on the predictions for censored data points. To preserve our uncertainty about the true runtime of censored runs, we can change the E step to:
     </paragraph>
     <list>
      <list-item>
       For each tree T in the RF and each i s.t. {a mathematical formula}ci=1: {a mathematical formula}yˆi(T)← sample from N(μi,σi2)⩾zi.
      </list-item>
     </list>
     <paragraph>
      In order to guarantee convergence, we also keep the assignment of bootstrap data points to each of the forestʼs trees fixed across iterations and draw the samples for each censored data point in a stratified manner; for brevity, we refer the reader to [51] for the precise details. Our resulting modified variant of Schmee &amp; Hahnʼs algorithm takes our prior uncertainty into account when computing the posterior predictive distribution, thereby avoiding overly confident predictions. As an implementation detail, to avoid potentially large outlying predictions above the known maximal runtime of {a mathematical formula}κmax=300 seconds, we ensure that the mean imputed value does not exceed {a mathematical formula}κmax.{sup:11} (In the absence of censored runs—the case addressed in the major part of our work—this mechanism is not needed, since all predictions are linear combinations of observed runtimes and are thus upper-bounded by their maximum.)
     </paragraph>
     <section label="9.1">
      <section-title>
       Experimental setup
      </section-title>
      <paragraph>
       We now experimentally compare Schmee &amp; Hahnʼs procedure and our modified version to two baselines: ignoring censored data points altogether and treating data points that were censored at the captime κ as uncensored data points with runtime κ. We only report results for the most interesting case of predictions for previously unseen parameter configurations and instances. We used the 9 benchmark distributions from Section 8, artificially censoring the training data at different thresholds below the actual threshold. We experimented with two different types of capped data: (1) data with a fixed censoring threshold across all data points, and (2) data in which the thresholds were instance-specific (specifically, we set the threshold for all runs on an instance to the runtime of the best of the 1000 configurations on that instance). The fixed threshold represents the sort of data generated by experimental studies like those from the previous sections of this paper, while the instance-specific threshold models practical applications of EPMs in model-based algorithm configuration procedures [54]. For both types of capped data and for all prediction strategies, we measured both predictive error (using RMSE as in the rest of the paper) and the quality of uncertainty estimates (using log likelihood, LL, as defined in Section 6.2) on the uncensored part of the test data.
      </paragraph>
     </section>
     <section label="9.2">
      <section-title>
       Experimental results
      </section-title>
      <paragraph>
       Fig. 13 illustrates the raw predictions for one benchmark, demonstrating the qualitative differences between the four methods for treating capped data. In the case of a fixed censoring threshold κ, simply dropping censored data yielded consistent underestimates (see the top-left plot of Fig. 13), while treating censored data as uncensored at κ yielded good predictions up to κ (but not above); this strategy is thus reasonable when no predictions beyond κ are required (which is often the case; e.g., throughout the main part of this article). The Schmee &amp; Hahn variants performed similarly up to κ, but yielded unbiased predictions up to about two times κ. We note that a factor of two is not very much compared to the orders of magnitude variation we observe in our data. Much better predictions of larger runtimes can be achieved by using the instance-specific captimes discussed above (see the lower half of Fig. 13), and we thus advocate the use of such varying captimes in order to enable better scaling to larger captimes.
      </paragraph>
      <paragraph>
       A quantitative analysis (described in Section D.4 of the online appendix) showed that in the fixed-threshold case, dropping censored data led to the worst prediction errors; treating censored data as uncensored improved results; and using the Schmee &amp; Hahn variants further reduced prediction errors. However, with fixed thresholds, the Schmee &amp; Hahn variants often yielded poor uncertainty estimates because they imputed similar values (close to the fixed threshold) for all censored data points, yielding too little variation across trees, and thus also yielded overconfident predictions. In contrast, for data with varying captimes, treating censored data as uncensored often performed worse than simply dropping it, and the Schmee &amp; Hahn variants (in particular our new one) yielded both competitive uncertainty estimates and the lowest prediction error. Finally, we found these qualitative findings to be robust with respect to how aggressively (i.e., how low) the captimes were chosen. Overall, random forests handled censored data reasonably well. We note that other models might be better suited to extrapolating from training data with short captimes to obtain accurate runtime predictions for long algorithm runs.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Details on benchmark instance sets
     </section-title>
     <paragraph>
      This appendix gives more information about our instance benchmarks. For the SAT benchmarks, the number of variables and clauses are given for the original instance (before preprocessing). (In contrast, [48] reported these numbers after preprocessing, explaining the differences in reported values for IBM and SWV.)
     </paragraph>
     <section label="A.1">
      <section-title>
       SAT benchmarks
      </section-title>
      <paragraph>
       INDU This benchmark data set comprises 1676 instances from the industrial categories of the 2002–2009 SAT competitions as well as from the 2006, 2008 and 2010 SAT Races. These instances contain an average of {a mathematical formula}111000 variables and {a mathematical formula}689187 clauses, with respective standard deviations of {a mathematical formula}318955 and {a mathematical formula}1510764, and respective maxima of {a mathematical formula}9685434 variables and {a mathematical formula}14586886 clauses.
      </paragraph>
      <paragraph>
       HAND This benchmark data set comprises 1955 instances from the handmade categories of the 2002–2009 SAT Competitions. These instances contain an average of 4968 variables and {a mathematical formula}82594 clauses, with respective standard deviations of {a mathematical formula}21312 and {a mathematical formula}337760, and respective maxima of {a mathematical formula}270000 variables and {a mathematical formula}4333038 clauses.
      </paragraph>
      <paragraph>
       RAND This benchmark data set comprises 3381 instances from the random categories of the 2002–2009 SAT Competitions. These instances contain an average of 1048 variables and 6626 clauses, with respective standard deviations of 2593 and {a mathematical formula}11221, and respective maxima of {a mathematical formula}19000 variables and 79 800 clauses.
      </paragraph>
      <paragraph>
       COMPETITION This set is the union of INDU, HAND, and RAND.
      </paragraph>
      <paragraph>
       IBM This set of SAT-encoded bounded model checking instances comprises 765 instances generated by Zarpas [122]; these instances were selected as the instances in 40 randomly-selected folders from the IBM Formal Verification Benchmarks Library. These instances contained an average of {a mathematical formula}96454 variables and {a mathematical formula}413143 clauses, with respective standard deviations of {a mathematical formula}169859 and {a mathematical formula}717379, and respective maxima of {a mathematical formula}1621756 variables and {a mathematical formula}6359302 clauses.
      </paragraph>
      <paragraph>
       SWV This set of SAT-encoded software verification instances comprises 604 instances generated with the CALYSTO static checker [4], used for the verification of five programs: the spam filter Dspam, the SAT solver HyperSAT, the Wine Windows OS emulator, the gzip archiver, and a component of xinetd (a secure version of inetd). These instances contain an average of {a mathematical formula}68935 variables and {a mathematical formula}206147 clauses, with respective standard deviations of {a mathematical formula}56966 and {a mathematical formula}181714, and respective maxima of {a mathematical formula}280972 variables and {a mathematical formula}926872 clauses.
      </paragraph>
      <paragraph>
       RANDSAT This set contains 2076 satisfiable instances (proved by at least one winning solver from the previous SAT competitions) from data set RAND. These instances contain an average of 1380 variables and 8042 clauses, with respective standard deviations of 3164 and {a mathematical formula}13434, and respective maxima of {a mathematical formula}19000 variables and 79 800 clauses.
      </paragraph>
     </section>
     <section label="A.2">
      <section-title>
       MIP benchmarks
      </section-title>
      <paragraph>
       BIGMIX This highly heterogeneous mix of publicly available Mixed Integer Linear Programming (MILP) benchmarks comprises 1510 MILP instances. The instances in this set have an average of 8610 variables and 4250 constraints, with respective standard deviations of {a mathematical formula}34832 and {a mathematical formula}21009, and respective maxima of {a mathematical formula}550539 variables and {a mathematical formula}550339 constraints.
      </paragraph>
      <paragraph>
       CORLAT This set comprises 2000 MILP instances based on real data used for the construction of a wildlife corridor for grizzly bears in the Northern Rockies region (the instances were described by Gomes et al. [32] and made available to us by Bistra Dilkina). All instances had 466 variables; on average they had 486 constraints (with standard deviation 25.2 and a maximum of 551).
      </paragraph>
      <paragraph>
       RCW This set comprises 1980 MILP instances from a computational sustainability project. These instances model the spread of the endangered red-cockaded woodpecker, conditional on decisions about certain parcels of land to be protected. We generated 1980 instances (20 random instances for each combination of 9 maps and 11 budgets), using the generator from [1] with the same parameter setting as used in that paper, except a smaller sample size of 5. All instances have {a mathematical formula}82346 variables; on average, they have {a mathematical formula}328816 constraints (with a standard deviation of only 3 and a maximum of {a mathematical formula}328820).
      </paragraph>
      <paragraph>
       REG This set comprises 2000 MILP-encoded instances of the winner determination problem in combinatorial auctions. We generated 2000 instances using the regions generator from the Combinatorial Auction Test Suite [77], with the number of bids selected uniformly at random from between 750 and 1250, and a fixed bids/goods ratio of 3.91 (following [76]). They have an average of 1129 variables and 498 constraints, with respective standard deviations of 73 and 32 and respective maxima of 1255 variables and 557 constraints.
      </paragraph>
     </section>
     <section label="A.3">
      <section-title>
       TSP benchmarks
      </section-title>
      <paragraph>
       RUE This set comprises 4993 uniform random Euclidean 2-dimensional TSP instances generated by the random TSP generator, portgen[63]. The number of nodes was randomly selected from 100 to 1600, and the generated TSP instances contain an average of 849 nodes with a standard deviation of 429 and a maximum of 1599 nodes.
      </paragraph>
      <paragraph>
       RCE This set comprises 5001 random clustered Euclidean 2-dimensional TSP instances generated by the random TSP generator, portcgen [63]. The number of nodes was randomly selected from 100 to 1600, and the number of clusters was set to 1% of the number of nodes. The generated TSP instances contain an average of 852 nodes with a standard deviation of 432 and a maximum of 1599 nodes.
      </paragraph>
      <paragraph>
       TSPLIB This set contains a subset of the prominent TSPLIB (http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/) repository. We only included the 63 instances for which both our own feature computation code and the code by Smith-Miles &amp; van Hemert [107] completed successfully (ours succeeded on 23 additional instances). These 63 instances have {a mathematical formula}931±1376 nodes, with a range from 100 to 5934.
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>