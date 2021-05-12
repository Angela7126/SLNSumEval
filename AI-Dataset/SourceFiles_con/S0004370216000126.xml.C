<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Empirical decision model learning.
   </title>
   <abstract>
    One of the biggest challenges in the design of real-world decision support systems is coming up with a good combinatorial optimization model. Often enough, accurate predictive models (e.g. simulators) can be devised, but they are too complex or too slow to be employed in combinatorial optimization. In this paper, we propose a methodology called Empirical Model Learning (EML) that relies on Machine Learning for obtaining components of a prescriptive model, using data either extracted from a predictive model or harvested from a real system. In a way, EML can be considered as a technique to merge predictive and prescriptive analytics. All models introduce some form of approximation. Citing G.E.P. Box [1] “Essentially, all models are wrong, but some of them are useful”. In EML, models are useful if they provide adequate accuracy, and if they can be effectively exploited by solvers for finding high-quality solutions. We show how to ground EML on a case study of thermal-aware workload dispatching. We use two learning methods, namely Artificial Neural Networks and Decision Trees and we show how to encapsulate the learned model in a number of optimization techniques, namely Local Search, Constraint Programming, Mixed Integer Non-Linear Programming and SAT Modulo Theories. We demonstrate the effectiveness of the EML approach by comparing our results with those obtained using expert-designed models.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Advances in Combinatorial Optimization methods in the last decades have enabled their successful application to a broad range of industrial problems. Many of such approaches rely on the availability of some declarative system description. This typically consists of a hand-crafted mathematical model, obtained after thorough discussion with the domain experts by introducing some simplifying assumptions.
     </paragraph>
     <paragraph>
      Devising a good model is a complex task, especially challenging when dealing with real-world systems. A good model finds a proper balance between model complexity and model accuracy: on the one hand, excessive simplification may lead to “optimal” – but completely useless – solutions. On the other hand, incorporating too many details results in extremely hard computational issues. Despite this, a number of successful optimization approaches have been proposed in the literature and applied to real-life industrial problems, enabling in many cases{sup:1} huge savings in terms of resources (time, money, machines, energy).
     </paragraph>
     <paragraph>
      Nevertheless, many systems are still impervious to approaches such as Mixed Integer Linear Programming (MILP), Constraint Programming (CP), or SAT (propositional SATisfiability) and this is often due to modeling issues. There are basically two kinds of “high-complexity systems” that are out-of-reach for traditional combinatorial approaches: (1) Complex Systems, which exhibit phenomena that emerge from a collection of interacting objects capable of self-organization and affected by memory or feedback; and (2) physical systems whose dynamic model is known, but its embedding in a combinatorial model is computationally intractable.
     </paragraph>
     <paragraph>
      A very common way for supporting decision-making in these systems is to design a predictive model (e.g., a simulator) based on real data and to use it via what-if analysis (see [2] for a recent reference). In what-if analysis, the decision maker repeatedly feeds scenarios (i.e. sets of decisions) to the predictive model to extract the values of certain observables of interest (e.g. quality measures). Inevitably, only a limited number of scenarios is investigated, and then the decision maker commits to the one showing the best behavior. In combinatorial problems the decision space might be so large that selecting scenarios manually or in isolation results in far-from-optimal choices.
     </paragraph>
     <paragraph>
      The aim of this paper is to bring such high-complexity systems within the reach of combinatorial decision making and optimization. The idea is to use Machine Learning (ML) to learn an approximate relation between decisions and their impact on the system. In particular, we devise a methodology, called Empirical Model Learning (EML) that: (1) learns relations between decidables and observables{sup:2} from data, and (2) encapsulates these relations into components of an optimization model, namely objective functions or constraints. The training data for the learning techniques can be harvested from the real system or extracted from a predictive model (e.g. simulator). The integration into model components is not merely a matter of encoding, since in some cases an operational semantics for the efficient use of the component should be defined.
     </paragraph>
     <paragraph>
      The ability to integrate Machine Learning models in combinatorial optimization has the potential to play a major role in bridging the gap between predictive and prescriptive analytics. An EML based system may be capable of suggesting optimal decisions in a complex real-world setting, by taking advantage of recent developments in big data analysis and predictive model design.
     </paragraph>
     <paragraph>
      This paper provides three main contributions. First, we introduce the Empirical Model Learning approach in a general fashion. Second, we present a number of methods for embedding Machine Learning models (namely Decision Trees and Artificial Neural Networks) into several optimization techniques (Local Search, Mixed Integer Non-Linear Programming, Constraint Programming, SAT Modulo Theories). Some of our embedding techniques have been presented in previous papers of ours [4], [5]. Third, we show that despite the main idea behind EML being very simple, its application requires some care for obtaining an effective optimization approach. We highlight the main difficulties and suggest possible solutions by applying the EML approach on two practical examples.
     </paragraph>
     <paragraph>
      As motivating (and running) examples, we use two thermal-aware workload dispatching problems, defined over an experimental multicore Intel CPU called “Single-chip Cloud Computer” (SCC, see [6]). Both problems consist in mapping a set of heterogeneous jobs on the platform cores so as to maximize some cost metric involving the platform efficiency. The efficiency of each core is affected by a number of complex factors including the thermal dynamics of the chip, the workload distribution, and the presence of low-level schedulers and thermal controllers. Although an accurate system simulator for the platform is available, it cannot be inserted into a decision model due to its high complexity and large run time. We show that EML allows considerable improvements over simpler optimization approaches either based on expert-designed heuristics, or on expert-designed models refined via function fitting.
     </paragraph>
     <paragraph>
      The paper is structured as follows: in Section 2 we provide a comparative analysis of related work. In Section 3 we introduce the example problems. In Section 4 we give a brief overview of the EML approach. Section 5 presents techniques for embedding Machine Learning models into Combinatorial Optimization models. Sections 6 and 7 discuss respectively how to design the core combinatorial structure of the optimization problem, and how to extract a system model from data: in both cases, our example problems are employed to present the process. We provide experimental results in Section 8 and concluding remarks in Section 9.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Comparative analysis of related work
     </section-title>
     <paragraph>
      The EML approach combines elements of Combinatorial Optimization, Machine Learning, and Complex Systems/Simulation. In this section we provide a brief overview of approaches related to the integration of such research fields.
     </paragraph>
     <paragraph>
      Loosely related approaches  Researchers have been interested for a long time in the integration of optimization techniques in Machine Learning. This is not surprising, given that training problems are fundamentally (very peculiar) optimization problems. Works such as [7], [8] have studied the core optimization problems in ML algorithms and proposed efficient methods for extracting knowledge from huge volumes of data. Other works (e.g. [9], [10] and those presented in [11]) have applied Constraint Programming to Machine Learning tasks.
     </paragraph>
     <paragraph>
      In the optimization community, a substantial effort has been recently dedicated to using learning to improve a solution approach. Clustering methods have been employed for automatic algorithm selection (e.g. [12]). Several Machine Learning techniques have been used for predicting the run time of optimization algorithms, once again with the aim to perform algorithm selection (e.g. [13], [14]). A few works have focused on learning customized optimization problem instances for testing new techniques (see [15]).
     </paragraph>
     <paragraph>
      Constraint acquisition  Some papers [16], [17], [18] have focused on learning a set of constraints that match a number of positive and negative examples, a task known as constraint acquisition. An extension to these approaches is represented by the QuAcq system [19], which requires only partial queries on subsets of problem variables (with no need of positive examples). Other constraint acquisition approaches are surveyed in [20]. All such approaches attempt to combine constraints from a given library to build a model that is compatible with the available data. Conversely, in EML the emphasis is on enabling the integration of a “standard” Machine Learning model (e.g. a Neural Network) into a combinatorial problem. Our approach requires an additional design effort, but it is also more flexible and better suited for dealing with practical applications, especially in cases where a good Machine Learning model is already available.
     </paragraph>
     <paragraph>
      Many constraint acquisition approaches make use of active learning: the candidate solutions found by a solver are evaluated (e.g. via a simulator) and then serve as new examples for the training set. This kind of approach allows one to tune the model for the specific instance being solved. As a drawback, the response times can become impractically large if evaluating a data point is expensive. Moreover, if a simulator is not available, then active learning would require one to deploy the intermediate solutions on the real system, which may be unreasonable in practice. In this work, we assume that the training is done entirely off-line. Integrating active learning in our method is possible, but left as a subject of future research.
     </paragraph>
     <paragraph>
      Surrogate models  Surrogate models (see [21] for an excellent overview) are approximate system models. They are typically employed on design problems for which declarative models are difficult to obtain, but simulation is viable. A surrogate model takes the form of a function with pre-defined structure and unknown parameters, or of a combination of kernel functions (e.g. Gaussian processes). Surrogate models are tuned over a training set and then are typically employed for blackbox optimization (see the next paragraph). In some approaches (e.g. ALAMO [22]) optimization and simulation are jointly employed to explore alternative surrogate model structures and tune the parameters.
     </paragraph>
     <paragraph>
      The idea of using surrogate models is closely related to the one we propose, but there are important differences in terms of focus, scope, and (ideal) generality. Most works on surrogate models focus: (1) on a specific class of Machine Learning techniques, e.g. relatively simple compositions of non-linear, continuous, functions (only a minority of works have considered Artificial Neural Networks [23], [24]); (2) on specific problems, typically with continuous variables and range constraints; and (3) on specific solution techniques, e.g. Genetic Algorithms, blackbox/derivative-free optimization, sometimes Mixed Integer Non-Linear Programming. Conversely, in EML we aim at enabling the use of as many Machine Learning techniques as possible, within as many optimization methods as possible: the goal is having the ability to choose the most adequate solution approach for each problem. As a consequence, our focus is mostly on handling the integration of Machine Learning models in optimization: for example, we emphasize the importance of model embedding techniques (in Section 5), and of methods to exploit the structure of the extracted model for boosting the search process. This paper will specifically focus on problems, Machine Learning models, and techniques that are outside the typical scope of surrogate models.
     </paragraph>
     <paragraph>
      The LION approach  Off-line learning is employed in the LION approach [25] to extract an approximate cost function from abundant data. The authors stress that there are practical cases (e.g. when user preferences are involved) where there is no obvious numeric approach to rank solutions. In this situation, using historical data is the only way to obtain an approximate cost function without repeatedly querying the user at solution time. The LION approach relies on model fitting to obtain close-to-optimal solutions: this makes it difficult to target decision problems with a complex combinatorial structure.
     </paragraph>
     <paragraph>
      Black box optimization  Black-box optimization approaches are concerned with finding solutions for optimization problems having cost or constraint functions with unknown structure: the typical case is that of systems lacking a declarative model, but for which a simulator is available. This is the same use case of surrogate models, which in fact are often employed in black box optimization.
     </paragraph>
     <paragraph>
      If the black box function is fast enough to evaluate, then local search approaches, meta-heuristics, or Genetic Algorithms can be directly applied (e.g. [26]). If the black box evaluation is expensive to evaluate (this is frequent with simulators), then it becomes necessary to employ more advanced techniques to limit the number of simulator calls.
     </paragraph>
     <paragraph>
      Most of the methods for black box optimization with expensive cost functions have been developed in the field of derivative free optimization. Within that field, the book [27] makes a distinction between Directional Search and Model-based approaches. Informally speaking, Directional Search methods (see the survey by [28]) rely on discretization to limit the number of black box evaluations. Model-based approaches, instead, employ active learning to fit an internal surrogate model (often referred to as response surface). The internal model is used to guide the search process. In [29] and in Simulation for Optimization [30] the internal model is a stochastic process, which allows the search algorithm to take into account both the estimated solution quality and the estimated model accuracy in order to identify promising solutions. The OptQuest [31] system integrates in a closed loop simulation and meta-heuristics and relies on a Neural Network for quick, approximate, solution checking.
     </paragraph>
     <paragraph>
      Black box optimization approaches differ from EML in three important regards. The most important difference is that most black-box optimization approaches are designed for problems without a complex combinatorial structure. Hence, they are likely to be ineffective (or inapplicable) for problems with discrete variables and non-trivial constraints. This is exactly the class of problems where techniques such as CP, MILP, or SAT (i.e. the most interesting for our technique) tend to provide the best results. Second, black-box optimization often relies on performing simulation during the search process: this may be excessively time-consuming, or even impossible if a simulator is not available. In EML, the simulation time has no direct impact on the solver performance, and the model extraction can rely on historical data, or on experiments performed on the real system. Third, in EML the function that describes the system behavior is not a black box: on the contrary, the structure of the Empirical Model is well known, and we wish to exploit it for boosting the search process.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Motivating example
     </section-title>
     <paragraph>
      As a case study and motivating example, we consider two problems related to thermal-aware workload dispatching over an experimental multicore CPU by Intel, called Single-chip Cloud Computer (SCC [6]). The two problems share the same combinatorial structure, but are different w.r.t. the objective function and the observables of interest. In this section we describe the problems, identify the critical difficulties for defining a model, and outline possible solution approaches.
     </paragraph>
     <paragraph>
      Problem description  The SCC platform has 24 dual-core tiles arranged in a {a mathematical formula}4×6 grid (overall, 48 cores in a {a mathematical formula}8×6 grid). Each core runs an independent instance of the Linux kernel. Inter-tile communication occurs via message passing on a network interface, hence tasks cannot easily migrate between cores. The chip is designed to accept job batches from an external node (e.g. a separate computer). Due to the large number of cores packed on a single silicon die, the platform is prone to overheating. Since the chip is a prototype, Intel has chosen to make it thermally stable via an overly large (and noisy) fan, rather than by implementing a more advanced thermal controller.
     </paragraph>
     <paragraph>
      With the aim of studying temperature control policies on SCC, researchers at the University of Bologna (the domain experts in our case) have devised an accurate simulator based on Matlab and the Hotspot thermal modeling tool [32]. The simulator characterizes the jobs in terms of their CPI value (Clocks Per Instruction) at maximum frequency: jobs with low CPI make a more intense use of the CPU and generate more heat, whereas jobs with high CPI are comparatively colder. On each core of the simulated platform, two thermal control approaches have been introduced:
     </paragraph>
     <list>
      <list-item label="1.">
       A preemptive thermal-aware scheduler that interleaves the execution of “hot” and “cold” jobs in an effort to keep the temperature stable. Jobs are classified at run time based on their effect on the current temperature.
      </list-item>
      <list-item label="2.">
       A thermal controller that dramatically lowers the core frequency if the temperature exceeds a safety threshold.
      </list-item>
     </list>
     <paragraph>
      The jobs are assumed to run indefinitely: hence, the domain experts have decided to avoid overloading by running the same number of jobs on each core.
     </paragraph>
     <paragraph>
      Problem variants  Both our dispatching problems consist in mapping a set of heterogeneous jobs on the platform cores so as to maximize an objective related to the core efficiencies. Due to the presence of a thermal controller, the efficiency of each core depends on its temperature, and on a number of complex factors including: (1) the workload, (2) the temperature of the other cores, (3) the core position on the die, (4) the action of the thermal-aware scheduler and of the threshold controller. As already mentioned, we consider two problem variants:
     </paragraph>
     <list>
      <list-item label="1.">
       In the first variant (referred to as {a mathematical formula}WDPbal), the goal is to balance the platform efficiency and to avoid the occurrence of hot spots (abnormally warm cores). Together with the domain experts, we have formalized this objective as that of maximizing the worst-case core efficiency.
      </list-item>
      <list-item label="2.">
       In the second variant (referred to as {a mathematical formula}WDPmax), the goal is to have a portion of the platform as large as possible that operates at high efficiency. Together with the domain experts, we have formalized this objective as that of maximizing the number of cores having an efficiency larger than a certain threshold.
      </list-item>
     </list>
     <paragraph>
      Base models  As a preliminary step for defining a solution approach, we introduce a base model for each of our example problems. In both the base models, the relation between the mapping decisions and the efficiency is captured by means of generic functions. Formally, let n and m respectively be the number of jobs and cores ({a mathematical formula}m=48 for SCC). Let us introduce a set of binary variables {a mathematical formula}xik such that {a mathematical formula}xik=1 iff job i is mapped on core k and 0 otherwise. Then a possible formulation for {a mathematical formula}WDPbal is:
     </paragraph>
     <paragraph>
      {a mathematical formula} Constraints (3) ensure that each job is mapped on a single core and Constraints (4) force the same number of jobs (i.e. {a mathematical formula}n/m) to run on each core.{sup:3}
     </paragraph>
     <paragraph>
      Constraints (2) define the behavior of the target CPU. This is done by relying on a set of functions {a mathematical formula}hkbal:{0,1}n→(0,1], each of which associates a mapping of all jobs to a value for the {a mathematical formula}effk variable, representing the efficiency of core k. A base model for the second problem variant can be formulated as follows:
     </paragraph>
     <paragraph>
      {a mathematical formula} The model is identical to the one for the {a mathematical formula}WDPbal, except for the cost function and the functions {a mathematical formula}hkmax that define the system behavior. In particular, we assume here that each {a mathematical formula}heffk is binary and such that {a mathematical formula}heffk=1 iff the efficiency of core k is above the threshold value. Therefore, we have that each {a mathematical formula}hkmax is a function {a mathematical formula}hkmax:{0,1}n→{0,1}.
     </paragraph>
     <paragraph>
      Modeling the system behavior  The critical step for defining a solution approach for the {a mathematical formula}WDPbal and the {a mathematical formula}WDPmax is finding a suitable embodiment of the {a mathematical formula}hbal and {a mathematical formula}hmax functions. Here we survey the main alternatives.
     </paragraph>
     <paragraph>
      First, the {a mathematical formula}hbal and {a mathematical formula}hmax functions can be evaluated in an exact fashion by simply running the SCC simulator. This is the typical scenario in black box optimization (see Section 2), and a viable approach when using GAs or Local Search as solution methods. Unfortunately, in our case each simulation run requires several minutes, while the acceptable response time for the dispatcher is in the order of (tens of) seconds. Amortizing the simulation time (by limiting simulator calls or relying on an internal model) is not enough to solve the issue, and therefore direct evaluations via the simulator are simply not viable.
     </paragraph>
     <paragraph>
      Second, it is possible to use a heuristic measure as a “proxy” for the exact system behavior. Heuristics of this kind are often easy to embed in a combinatorial model. More importantly, such heuristics are easy to define for domain experts, who typically base their decisions on some kind of simple rule. For example, in the case of the {a mathematical formula}WDPbal, the designer of the simulator suggested to use the average CPI (Clocks Per Instruction) of the jobs mapped on a core as a proxy for its efficiency. This approach has been considered in our experimentation in Section 8. The main drawback of using a heuristic is that it becomes usually impossible to a-priori quantify the degree of approximation. This is undesirable in general, and may have an adverse affect on the solution quality.
     </paragraph>
     <paragraph>
      Third, it is possible to define the {a mathematical formula}hbal and {a mathematical formula}hmax functions by using (e.g.) linear regression for fitting an expert-design model: we rely on the knowledge of the domain expert for defining the model structure, while we extract the parameter values from data. The accuracy of the model can be evaluated over the training set or on a separate test set. We have considered this approach (which is in fact a simple form of model learning) in our experimentation. Finally, we can use Empirical Model Learning and employ Machine Learning to extract from data both the structure and the parameters of the system model. This approach is applicable even when the structure of {a mathematical formula}hbal and {a mathematical formula}hmax is not obvious, and it will be discussed in detail in the remainder of the paper.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The Empirical Model Learning approach
     </section-title>
     <paragraph>
      In EML, we are interested in solving optimization problems defined over high-complexity systems, which typically have the following structure:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} where x is a vector of decision variables {a mathematical formula}xi with domain {a mathematical formula}Di, and z is a vector of observables related to the target system. We make no special assumption on the domains {a mathematical formula}Di in the general case. The cost function f may depend on both the decision variables and the observables.
     </paragraph>
     <paragraph>
      All problem variables may be subject to constraints, represented as logical predicates {a mathematical formula}gj(x,z). The predicates may correspond to classical inequalities from Mathematical Programming, or to combinatorial restrictions, such as Global Constraints in Constraint Programming (e.g. alldiff, element). Equations (9), (10), and (12) represent the core combinatorial structure of the optimization problem. The {a mathematical formula}h(x) function describes the (approximate) behavior of the high-complexity system and specifies how the observables depend on the decision variables. The function h corresponds to the encoding of the Empirical Model, obtained via Machine Learning.
     </paragraph>
     <paragraph>
      Designing an optimization approach based on EML requires to take care of three main activities:
     </paragraph>
     <list>
      <list-item label="1.">
       Defining the core combinatorial structure of the problem.
      </list-item>
      <list-item label="2.">
       Obtaining a Machine Learning model.
      </list-item>
      <list-item label="3.">
       Embedding the Empirical Model in the combinatorial problem.
      </list-item>
     </list>
     <paragraph>
      The third step is the critical one, and it will be the first to be presented (in Section 5). It is possible to embed a Machine Learning model into a combinatorial problem only if a suitable encoding has been defined. Such an encoding should be designed so that it can be exploited by the optimization approach for boosting the search process (e.g. via bound computation or constraint propagation).
     </paragraph>
     <paragraph>
      Step 1 consists in defining a combinatorial model and Step 2 is a classical Machine Learning task (regression or classification). Both activities are non-trivial and may be time consuming, but they have been extensively studied in the past. In the context of EML, they require some special attention: they will be discussed in Sections 6 and 7, using the {a mathematical formula}WDPbal and {a mathematical formula}WDPmax as running examples.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Embedding the Empirical Model
     </section-title>
     <paragraph>
      Embedding the extracted EM into an optimization model requires: (1) to encode the Empirical Model in terms of variables and constraints; (2) to define an operational semantics for such an encoding.
     </paragraph>
     <paragraph>
      By operational semantics we refer to any procedure that can improve the optimization process by reasoning over the EM. This operational semantics may be provided implicitly by the underlying solver (e.g. convex envelope bounding in some MINLP solvers) or may be defined explicitly together with the encoding (e.g. ad hoc filtering algorithms in CP).
     </paragraph>
     <paragraph>
      In this section, we will show embedding techniques for two types of Machine Learning models – namely Artificial Neural Networks (ANNs) and Decision Trees (DTs) – and four Combinatorial Optimization approaches – namely Local Search (LS), Mixed Integer Non-Linear Programming (MINLP), Constraint Programming (CP), and SAT Modulo Theories (SMT). The exact combinations that we consider are reported in Table 1: we provide no technique for integrating ANNs in SMT, because solvers with support for non-linear theories are not widely available. We did not try to encode Decision Trees in MINLP, because it would require extensive linearization of disjunctions, likely leading to poor bounds. Additionally, the interested reader may find a technique for embedding Random Forests in CP in work [5], by some of the authors of this paper. All our encoding techniques are general and not restricted to our example problems.
     </paragraph>
     <paragraph>
      As a baseline case, we consider embedding a Machine Learning model in Local Search. The core idea in Local Search is to improve iteratively an incumbent solution, by exploring (evaluating) a set of neighbor solutions. Local Search methods are originally designed for problems with discrete variables (unlike many blackbox optimization methods), and they can deal with non-trivial constraints (either via violation-based cost functions or by incorporating the constraints in the neighborhood definition).
     </paragraph>
     <paragraph>
      LS approaches require only the ability to evaluate the cost and constraint functions, and they always manipulate fully-instantiated solutions. For these reasons, embedding a Machine Learning model requires simply to implement a function evaluator. As a downside, LS approaches are limited in their ability to exploit the model structure for boosting the search process.
     </paragraph>
     <section label="5.1">
      <section-title>
       Embedding artificial neural networks in optimization methods
      </section-title>
      <paragraph>
       We briefly recall that ANNs (see [34] for a comprehensive reference) are computational systems consisting in networks of basic units called artificial neurons. Technically, an artificial neuron is a function with vector input x and scalar output y, corresponding to the equation:{a mathematical formula} where {a mathematical formula}xi denotes a single element in x, the {a mathematical formula}wi terms are the input weights (obtained via training), and b is a bias. The term ϕ is a monotonic, non-decreasing, often non-linear, activation function. Its argument is known as the neuron activity.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Embedding ANNs in MINLP
       </section-title>
       <paragraph>
        Mixed Integer Non-Linear Programming (MINLP, see [35]) is a field of Mathematical Programming that is concerned with finding extreme points of non-linear functions subject to linear, non-linear, or integrality constraints. Modern MINLP solvers can take advantage of the problem structure (constraints and cost function) via convex envelope approximation, linearization, cutting planes, constraint propagation, and branching.
       </paragraph>
       <paragraph>
        An ANN can be embedded in a MINLP model by introducing variables to model the input and output of each neuron, and then by directly inserting the neuron equations in the model. This is easy as long as the considered MINLP solver supports the activation functions employed in the neurons. Once the EM has been encoded, its equations will be automatically taken it into account by the solver for computing bounds and generating cuts.
       </paragraph>
       <paragraph>
        There are a few aspects that deserve some care. First, several MINLP solvers rely on convexity for providing globally optimal results. Any such MINLP solver will converge to a local optimum (possibly different from the global optimum), if the neurons use non-linear functions and the network has enough layers.
       </paragraph>
       <paragraph>
        Second, numerical stability may be an issue. For example, some MINLP solvers need at some point to invert the model functions. In principle, most activation function types can be inverted. In practice, however, due to the finite precision of the underlying machine, the inversion may be possible only on a restriction of the function domain, possibly leading to software crashes and missed solutions. The issue can be addressed by restricting the domain of the input/output variables of each neuron: this approach may accidentally eliminate a high-quality solution, but the risk should be very low.
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Embedding ANNs in CP
       </section-title>
       <paragraph>
        Constraint Programming (CP, see [36]) is an Artificial Intelligence technique designed to solve Constraint Satisfaction Problems (CSP) and Constraint Optimization Problems (COP). A CSP is defined as a set of variables, subject to a set of constraints. Each constraint has an associated filtering algorithm that can prune, at search time, provably infeasible values from the variable domains. Pruning a value may trigger other filtering algorithms in a process known as propagation. A constraint solver combines filtering, propagation, and search (which is highly customizable) to find solutions for a combinatorial problem. Optimization can be performed by dynamically adding bounding constraints whenever a feasible solution is found.
       </paragraph>
       <paragraph>
        We have shown in [4] that an ANN can be encoded in CP by introducing additional variables like in MINLP, and then by encoding each neuron as a global Neuron Constraint. A Neuron Constraint has signature:{a mathematical formula} where ϕ denotes the activation function type, y is the output variable, x is the vector of input variables, w is the vector of weights, and b is the bias. Using a constraint to model each neuron allows one to encode complex networks (even recurrent ones) with a limited number of basic modeling components (i.e. a constraint for each type of activation function).
       </paragraph>
       <paragraph>
        A Neuron Constraint maintains Bound Consistency on Equation (13), i.e. its filtering algorithm is capable of pruning the x and y variables so that the extremes of their domains are guaranteed to be consistent. Bound Consistency can be enforced for a Neuron Constraint by filtering the neuron activity and the activation function separately. Formally, we consider the decomposition:{a mathematical formula}{a mathematical formula} where {a mathematical formula}y′ is a real-valued variable representing the neuron activity. The variable is introduced to explain the filtering method, and typically it does not appear in the model. Equation (16) is a linear expression, for which classical filtering techniques exist. Since the activation function is monotonic and non-decreasing, Bound Consistency on Equation (15) can be enforced by means of the following rules:{a mathematical formula}{a mathematical formula} where the notation {a mathematical formula}y‾,y‾′ denotes the maximum in the domain of y and {a mathematical formula}y′. The key idea is that whenever the domain maximum of {a mathematical formula}y′ is narrowed, this triggers a reduction of the domain maximum of y, and vice-versa. The rules for filtering the domain minima are analogous.
       </paragraph>
       <paragraph>
        We recall that the ϕ function may be invertible in practice for a restricted range of values, due to the finite precision of the underlying machine. This issue can be addressed by replacing {a mathematical formula}ϕ−1(y‾) in Equation (18) with the expression {a mathematical formula}max⁡{v∈R:ϕ(v)=y‾}. Moreover, since many constraint solvers do not provide support for real-valued variables, it is often necessary to use integer variables and a finite-precision representation. More details about practical implementation issues can be found in [4].
       </paragraph>
       <paragraph>
        Using a global constraint for each neuron is not the only viable CP encoding. An alternative approach consists in using a single global constraint to capture a whole network: this method is less flexible, but can provide stronger filtering. In [37] one of the authors of this paper has devised a global propagator based on a Lagrangian relaxation for a very common class of networks, i.e. two-layer, feed-forward ANNs. For simplicity, however, in this paper we limit ourselves to the original approach using one constraint per neuron.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Embedding Decision Trees in optimization methods
      </section-title>
      <paragraph>
       Decision Trees (DT) are a type of Machine Learning model typically employed for classification tasks (see [38] for a comprehensive overview). Each leaf of a DT is labeled with a class. Each node is labeled with one of a set of attributes{a mathematical formula}xi that are used to described the DT input. Attributes can be numeric or symbolic. The outgoing branches of a node are labeled with conditions over its attribute. The conditions form a partition of the attribute domain: every branch {a mathematical formula}bj over a symbolic attribute is labeled with a set {a mathematical formula}L(bj) of acceptable symbolic values; every branch over a numeric attribute is labeled with a splitting condition over a threshold {a mathematical formula}θ(bj), in the form {a mathematical formula}xi≤θ(bj) or {a mathematical formula}xi&gt;θ(bj). A simple Decision Tree is depicted in Fig. 1. An example is classified by starting from the root node and traversing the tree, always taking the branches whose condition is satisfied by the values of the attributes. For a fully specified example, this process leads to a single leaf, corresponding to the predicted class.
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Embedding Decision Trees in SMT
       </section-title>
       <paragraph>
        Satisfiability Modulo Theories (SMT) is an extension of SAT that allows one to include non-boolean predicates (e.g. linear inequalities over integer variables) in a logical formula. An SMT solver [39] combines a SAT solver and one or more theory solvers, each providing support for some constraints via dedicated approaches (e.g. the Simplex algorithm). The SAT solver manages the boolean representation, taking care of (e.g.) unit propagation and conflict learning. Several search strategies are possible, ranging from lazy approaches where all the boolean decisions are instantiated before the theory variables, to more complex schemes where the SAT and theory solvers work in an interleaved fashion. Optimization can be performed by posting a bounding constraint whenever a solution is found, and then restarting the search process.
       </paragraph>
       <paragraph>
        SMT allows one to treat constraints over non-logical domains as boolean predicates, enabling a convenient encoding of DTs. First, we introduce variables to model the input attributes and the class (let them be x and y respectively). Symbolic attributes and classes can be modeled as integer variables. Then, we can obtain a simple rule-based encoding based on the observation that each path π from root to leaf can be viewed as a logical implication:{a mathematical formula} where the notation {a mathematical formula}〚−〛 refers to the boolean predicate corresponding to the constraint enclosed in the brackets. The term {a mathematical formula}C(π) is the class corresponding to the leaf in the path π, and each {a mathematical formula}bj is a branch along the path. Each expression {a mathematical formula}cst(bj) is in the form:{a mathematical formula} where {a mathematical formula}x(bj) refers in this case to the attribute variable associated to branch {a mathematical formula}bj.
       </paragraph>
       <paragraph>
        Posting Clause (19) for each path in the tree is sufficient to encode a DT. However, it is possible to obtain a formulation leading to stronger propagation. The key observation is that the set of leaves labeled with a certain class specifies all and only the input configurations that should be mapped to such class. This allows one to encode a whole tree as a set of clauses:{a mathematical formula} In other words, the class variable y takes the value {a mathematical formula}ch iff at least one of the implications associated to the paths {a mathematical formula}πk labeled with {a mathematical formula}ch is true. This formulation allows the SMT solver to perform more powerful deductions via unit propagation, and it is therefore the one we employ in the remainder of the paper.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Embedding Decision Trees in CP
       </section-title>
       <paragraph>
        If the Constraint Programming solver used for the implementation supports logical expressions, then it is possible to directly employ in CP the encoding from Equation (20). Indeed, such an encoding was originally designed for CP and presented by some of the authors of this paper in [5].
       </paragraph>
       <paragraph>
        If logical constraints are not supported, it is still possible to obtain an equivalent reformulation of Equation (20), by separately modeling the left-to-right and right-to-left implications associated with the ⇔ operator. In particular, the right-to-left implication corresponds to Equation (19) and for the whole DT translates to:{a mathematical formula} where the notation {a mathematical formula}〚−〛 refers here to a reified constraint, which denotes 1 if the expression between the double square brackets is true and 0 if the expression is false. Informally, Equation (21) forces the class variable y to take the value {a mathematical formula}C(πk) if the current domain of the attribute variables is such that all the {a mathematical formula}cst(bj) constraints are necessarily satisfied. Conversely, if y takes the value {a mathematical formula}C(πk), then at least one of the conjunctions of {a mathematical formula}cst(bj) constraints must be true. This leads to:{a mathematical formula} None of the presented encodings is capable of enforcing Generalized Arc Consistency (GAC). GAC can be actually achieved in CP using the two encodings that we have presented in [5] (respectively based on a table and an mdd constraint). For sake of simplicity in this paper we restrict ourselves to the simple encodings that we have presented, and we refer the interested reader to [5].
       </paragraph>
      </section>
     </section>
    </section>
    <section label="6">
     <section-title>
      Design of the optimization model
     </section-title>
     <paragraph>
      In this section we discuss Step 1 of the EML design process, i.e. the definition of the core combinatorial structure of the optimization problem. Informally, this is the part of the optimization model that can be designed by a domain expert in a traditional fashion. Defining the combinatorial structure requires one to identify the input and output of the Empirical Model, i.e. to define which part of the final model should be extracted from data. This decision affects the Machine Learning techniques that can be used to extract the Empirical Model. For our example problems, we have already provided a first definition of the core combinatorial structure in the two base models from Section 3. In both cases, the input of the Empirical Model is given by the mapping variables. The EM output for the {a mathematical formula}WDPbal is given by the efficiency of each core: this implies that some kind of regression technique must be used to obtain the Empirical Model. The output for the {a mathematical formula}WDPmax is a vector of binary variables ({a mathematical formula}effk=1 iff core k has “high” efficiency), hence in this case the Empirical Model is a classifier.
     </paragraph>
     <paragraph>
      In the remainder of this section we will present models for the core combinatorial structure of the {a mathematical formula}WDPbal and the {a mathematical formula}WDPmax, using a variety of optimization techniques (LS, MINLP, CP, and SMT). We refer to each model with the notation {a mathematical formula}Tp(h), where T identifies the solution technique, and p the problem type (bal for the {a mathematical formula}WDPbal and max for the {a mathematical formula}WDPmax). The h term identifies how the relation between the mapping and the efficiency variables is modeled, which is left unspecified in this section (the possible alternatives will be discussed in Sections 7 and then again in Section 8).
     </paragraph>
     <paragraph>
      Core model for Local Search  The Local Search model for the {a mathematical formula}WDPbal is identical to the base model presented in Section 3, and reported here for convenience:
     </paragraph>
     <paragraph>
      {a mathematical formula} where we recall that n is the number of jobs and m is the number of cores. The {a mathematical formula}hk functions represent the Empirical Model, which will be discussed in detail in Section 7. Analogously, the LS model for the {a mathematical formula}WDPmax is:
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      Core model for MINLP  A MINLP model for the {a mathematical formula}WDPbal can be obtained from the base model by linearizing the objective function:
     </paragraph>
     <paragraph>
      {a mathematical formula} We did not design a MINLP model for our second example problem, because we have not defined a technique for encoding in MINLP a Decision Tree, i.e. the Empirical Model that we employ for the {a mathematical formula}WDPmax (see Section 7).
     </paragraph>
     <paragraph>
      Core model for CP  We have designed CP models for the two dispatching problems presented in Section 3. Unlike the LS and MINLP case, in the CP models we represent the mapping decisions via integer variables {a mathematical formula}xi∈{0,..,m−1}, such that {a mathematical formula}xi=k iff job i is mapped on core k. This encoding ensures that a job is always mapped to a single core. The full model for {a mathematical formula}WDPbal is as follows:
     </paragraph>
     <paragraph>
      {a mathematical formula} Constraints (35) employ a gcc (Global Cardinality Constraint [40]) to ensure that the same number of jobs is mapped to each core. The gcc constraint forces each value of the set {a mathematical formula}{0,..m−1} to be taken by exactly {a mathematical formula}n/m of the x variables. The model for the {a mathematical formula}WDPmax is identical, except for the cost function and the definition of the efficiency variables:
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      Core model for SMT  We did not design an SMT model for the {a mathematical formula}WDPbal, because the Empirical Model that we employ in this case is a Neural Network and we have not devised a technique for embedding ANNs in SMT. We did however define an SMT model for the {a mathematical formula}WDPmax. In the model we represent the mapping decisions via integer variables {a mathematical formula}xi,k such that {a mathematical formula}xi,k=1 iff job i runs on core k, similarly to what was done for LS and MINLP. The resulting SMT model is:
     </paragraph>
     <paragraph>
      {a mathematical formula} where {a mathematical formula}〚xi,k=0〛 and {a mathematical formula}〚xi,k=1〛 are boolean predicates associated to non-boolean constraints (in this case, linear equations over integer variables). The boolean clauses (46) model the binary domain of the {a mathematical formula}xi,k variables.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Extracting an Empirical Model
     </section-title>
     <paragraph>
      In this section we discuss Step 2 of the EML design process, i.e. obtaining the Empirical Model. In principle, extracting the Empirical Model is simply a supervised learning task: given a training set containing known input/output pairs (i.e. examples) for the considered system, the goal is to obtain a function to predict the system behavior on unseen examples. This goal can be achieved via a number of powerful techniques from the Machine Learning domain. In this work, we will limit ourselves to Artificial Neural Networks (ANNs) and Decision Trees (DTs), i.e. the Machine Learning models for which an embedding technique has been provided in Section 5.
     </paragraph>
     <paragraph>
      In general, extracting a Machine Learning model requires one to: (1) obtain a training set, (2) choose the features to be used as input, (3) choose a Machine Learning technique, and then (4) proceed with the training and the evaluation. Extracting an Empirical Model is done in the same way, except that each step requires some special care because of the peculiarities of the EML context. In the remainder of this section we identify such peculiarities and how to deal with them, using the two dispatching problems from Section 3 as running examples.
     </paragraph>
     <section label="7.1">
      <section-title>
       EM extraction, step 1: obtaining a training set
      </section-title>
      <paragraph>
       In EML, a training set can be obtained either by collecting historical data or by running ad-hoc experiments. This can be a costly operation, but it needs to be performed only once,{sup:4} for obtaining the Empirical Model.
      </paragraph>
      <paragraph>
       A good training set should be representative of the instances (input configurations) for which a prediction needs to be made. In a classical Machine Learning scenario, the set should include instances that are likely to occur in practice, so as to introduce a controlled bias that simplifies the learning problem. In EML, however, the instances to be evaluated are generated by an optimization system: in our example problems, given a specific set of jobs, the search engine will try to explore the space of possible mappings as extensively as possible. In this kind of situation, defining which input configurations are more likely to be generated can be extremely difficult.
      </paragraph>
      <paragraph>
       We address this issue by designing a training set that is as unbiased as possible with respect to the decisions made by the search engine. For example, we can (1) collect groups of jobs that are likely to be submitted to the system, and then (2) build a training set by generating mappings at random so as to “cover” the set of possible mappings as uniformly as possible. This approach yields a training set that is biased towards likely sets of jobs, but unbiased w.r.t. how such jobs can be mapped.
      </paragraph>
      <paragraph>
       The training set for the example problems  For our dispatching problems, we learn a different Machine Learning model for each core. Using different models is necessary since the cores have non-homogeneous behavior, due to unique factors such as their position on the chip, or variability in the manufacturing process. Using a model for each core rather than a single model for the whole platform allowed us to obtain high accuracy using a limited number of inputs, leading to a dramatic reduction of the training set size.
      </paragraph>
      <paragraph>
       We built the training set for each core by generating random groups of mapped jobs. Then, the corresponding efficiency values were obtained via the simulator. The efficiency values were employed directly in the training set for the {a mathematical formula}WDPbal, while for the {a mathematical formula}WDPmax the efficiency was discretized into a 0-1 class using the value 0.97 (i.e. 97%) as a threshold. The threshold was chosen together with domain experts. The efficiency measure that we consider is the average efficiency of the mapped jobs, computed as:{a mathematical formula} where {a mathematical formula}n/m is the number of jobs mapped on the core, {a mathematical formula}cpii is the nominal CPI of job i (which assumes maximum operating frequency), and {a mathematical formula}cpiˆi is the job CPI as measured during simulation (which includes the slow-down due to the thermal controller). The formula provides an indication of the main factors that affect the core efficiency. In particular, we observe that:
      </paragraph>
      <list>
       <list-item label="1.">
        Because of the thermal controller, the efficiency of a core depends on its temperature, which is affected by how much the running jobs stress the CPU. In particular, there is a known correlation between the temperature of a core and the average CPI of the running jobs (see Section 8).
       </list-item>
       <list-item label="2.">
        The temperature of a core is also subject to thermal interactions from the other cores, in particular the nearest ones.
       </list-item>
       <list-item label="3.">
        The temperature of a core depends on its position on the silicon die, which affects its ability to disperse heat: this dependency is taken into account by learning a different model for each core.
       </list-item>
       <list-item label="4.">
        The temperature of a core is affected by that of the computer room. For sake of simplicity, we disregard this factor in the paper (it could be taken into account – for example – by learning different models for different room temperature ranges).
       </list-item>
       <list-item label="5.">
        Finally, not all jobs are affected by the thermal controller in the same way. Jobs with higher {a mathematical formula}cpii values spend a lot of clock cycles waiting for memory operations to conclude: as a consequence, their actual CPI value is less affected by the thermal controller (which acts on the frequency of the CPU and not of the memory). Conversely, jobs with low CPI are more affected by frequency reductions.
       </list-item>
      </list>
      <paragraph>
       Based on these observations, we obtained training sets via a factorial design (similarly to what is done for surrogate models [21]). In particular, for each core k we generated multiple random sets of 288 jobs (6 per core) so as to cover the possible values of some key parameters, reported in Table 2. Each parameter in the table is an approximation for one of the main factors affecting the core efficiency. The {a mathematical formula}p0, {a mathematical formula}p1, {a mathematical formula}p2 parameters are related to the average CPI of the jobs on each core, which is used as a proxy for the temperature. The actual CPI values on core k are randomly generated following a beta distribution, with 4 different parameterizations (see {a mathematical formula}p3 in the table). The CPI values on the remaining cores are also beta distributed, but a single parameterization is used in this case (chosen uniformly at random from those considered for core k).
      </paragraph>
      <paragraph>
       Overall, for each core we obtained (up to) {a mathematical formula}3×21×3×4=756 sets of mapped jobs, which were simulated in order to obtain the corresponding efficiency values. The process was quite time consuming, given that each simulation takes two-to-three minutes of computation time. However, the training set needs to be generated only once, during the system setup: the performance of the EML based solution approach is not affected by the training time, but rather by the complexity of the extracted model. All our training sets are publicly available.{sup:5}
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       EM extraction, step 2: choosing the input features
      </section-title>
      <paragraph>
       In EML, the input of the Empirical Model consists in principle of the decision variables themselves. In practice, feeding the decisions (e.g. the job-core mapping) directly to a Machine Learning model would make it dependent on the problem size and reduce the generality of the method. In Machine Learning, this issue is usually addressed by using aggregation functions (e.g. average, standard deviation...) to obtain features that are then fed to the model.
      </paragraph>
      <paragraph>
       In EML, this means that the Empirical Model constraints in the formulation from Section 4 are in fact a combination of two relations:{a mathematical formula} where y is a vector of variables representing the features, {a mathematical formula}hEM is the encoding of the Machine Learning model, and {a mathematical formula}hfeat are feature extraction constraints. The need to encode in the final model also the feature extraction constraints may lead to accuracy/effectiveness trade-offs: for example, an important feature may be difficult to encode in the optimization technique that is best suited for the combinatorial part of problem.
      </paragraph>
      <paragraph>
       Input features for the example problems  We designed and tested several input features, based on the factors affecting the efficiency that have been identified in Section 7.1. After several attempts, we settled for the following list:
      </paragraph>
      <list>
       <list-item label="1.">
        The average CPI of the jobs on core k: {a mathematical formula}avgcpik=1m∑job j on kcpij
       </list-item>
       <list-item label="2.">
        The minimum CPI of the jobs on core k: {a mathematical formula}mincpik=minjob j on k⁡(cpij)
       </list-item>
       <list-item label="3.">
        The average of the average CPI of the neighboring cores:{a mathematical formula}neighcpik=1|N(k)|∑core h∈N(k)avgcpih
       </list-item>
       <list-item label="4.">
        The average of the average CPI of all the other cores:{a mathematical formula}othercpik=1m−1−|N(k)|∑core h≠k,h∉N(k)avgcpih
       </list-item>
      </list>
      <paragraph>
       where {a mathematical formula}N(k) is the set of cores having {a mathematical formula}H∞ distance (i.e. the maximum between the distances along the x and y coordinates on the chip grid) equal to one from the target k. Most of the input features correspond directly to the parameters from Table 2, which is quite natural. The {a mathematical formula}mincpik feature was introduced (among other, eventually discarded, ones) to provide the Machine Learning model with information about the individual CPI values.
      </paragraph>
      <paragraph>
       The feature extraction constraints for the Local Search models are:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} where {a mathematical formula}avgcpik,mincpik,neighcpik,othercpik are real-valued variables, and {a mathematical formula}maxcpi is the maximum possible CPI (a constant). The feature extraction constraints for the CP models are identical to those used for Local Search, except that in place of the {a mathematical formula}xi,k variables we use reified constraints in the form {a mathematical formula}〚xi=k〛.
      </paragraph>
      <paragraph>
       Constraints (49), (51), and (52) can be directly inserted in a MINLP model. This is not the case for Constraints (50), because of the presence of the “min” operator. It may be possible to encode the minimum operator in a MINLP via integer variables and linearization, with adverse effects on the bound quality. For sake of simplicity, however, we have decided to extract two groups of Empirical Models, respectively with and without the {a mathematical formula}mincpik input feature. Only the second group has been embedded in MINLP.
      </paragraph>
      <paragraph>
       In the SMT model from Section 6, linear predicates that define {a mathematical formula}avgcpik, {a mathematical formula}neighcpik, {a mathematical formula}othercpik can be obtained from Constraints (49), (51), and (52) by replacing the {a mathematical formula}xi,k variables with the LIA (Linear Integer Arithmetic) predicates {a mathematical formula}〚xi,k=1〛. For defining the feature extraction constraints of {a mathematical formula}mincpik, we first build a vector s containing all job indices, sorted by increasing CPI value. Then, we post the hybrid linear/logical predicate:{a mathematical formula} where ite is an if-then-else statement: the first parameter is the condition to test, the second and third parameter are the expressions to be denoted if the condition is respectively true or false.
      </paragraph>
      <paragraph>
       Normalization  For many Machine Learning approaches (e.g. the Artificial Neural Networks that we will employ in the next section), it is beneficial to normalize the input features in a fixed range (typically {a mathematical formula}[−1,1]). In our case, this was done using the formula:{a mathematical formula} for {a mathematical formula}avgcpik and analogously for all other features. In the formula, {a mathematical formula}span0=(maxcpi+mincpi)/2 and {a mathematical formula}span1=(maxcpi−mincpi)/2. The value {a mathematical formula}mincpi represents the minimum possible CPI value, which is assumed to be 0 in a slightly conservative fashion (CPI values are always strictly positive). The normalization Formula (54) was included in the feature extraction constraints for all our approaches using ANNs for the Empirical Model.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       EM extraction, step 3: training and quality assessment
      </section-title>
      <paragraph>
       Designing and training a model are very well studied topics in Machine Learning (see [41] for an excellent overview). Both steps require one to assess the quality of the extracted model, which is measured via metrics such as the Mean Squared Error or the number of correctly classified instances. The assessment is typically done on a separate test set or via cross-validation.
      </paragraph>
      <paragraph>
       In EML, the fact that the input of the Machine Learning model is generated by a search approach makes the quality assessment more complicated. Suppose for example that the extracted model has a large prediction error for a certain range of values of the input features that is not very frequent in the training set. If the same values happen to be favorable in terms of cost in the problem model, then such input configurations, despite being uncommon in the training set, will be actively sought by the optimizer and will be much more likely to appear at search time. Because of this, the actual error in the final system has a chance to be similar to the maximum error on the test set.
      </paragraph>
      <paragraph>
       This issue could be addressed by using (for example) the maximum error as an evaluation metric during training. Alternatively, one could dynamically generate new examples that are similar to the ones leading to the largest errors, and then repeat the training. For sake of simplicity, in this paper we limit ourselves to classical training techniques: this means for example that we use the Mean Squared Error to evaluate the quality of ANNs at training time. Since the Mean Squared Error assigns a higher penalty to errors with large absolute value, it also tends to mitigate the issue that we have described.
      </paragraph>
      <paragraph>
       In traditional Machine Learning applications, evaluating the model (i.e. making a prediction) is usually a simple operation. In EML the extracted model is not simply evaluated, but rather it is exploited in a number of ways in order to boost the search process. This makes the size and complexity of the extracted model particularly important, since they determine the computation effort required for (e.g.) bounding or constraint propagation. This can lead to a trade-off between model size and accuracy, which may be critical if the final optimization system operates under tight time constraints. For our example problems, it was possible to obtain accurate and yet quite small EMs, and therefore we leave a thorough evaluation of this trade-off for future research.
      </paragraph>
      <paragraph>
       Empirical models for the{a mathematical formula}WDPbal  We used Artificial Neural Networks (ANNs) for the Empirical Model of the {a mathematical formula}WDPbal, for several reasons. First, we needed a regression technique because the EM output had to be an efficiency value. Moreover, ANNs are a classical technique in Machine Learning, they require little domain knowledge, and their modular nature makes them easier to embed in Combinatorial Optimization (see Section 5).
      </paragraph>
      <paragraph>
       We trained for each core a feed-forward network with one hidden layer. We used bipolar sigmoid neurons (with tanh activation function) in both the hidden and the output layers: the use of alternative activation functions (e.g. rectifiers) may be considered as part of future research. The output of each network is therefore in the {a mathematical formula}(−1,1) range, and must be scaled in order to obtain an easily understandable efficiency value. We used the Encog framework [42] for training the ANNs, via the Levenberg–Marquardt algorithm. After some experiments, we settled for using two neurons in the hidden layer (increasing the size did not significantly improve the accuracy).
      </paragraph>
      <paragraph>
       We trained two ANN variants for each core, both having the same number and type of neurons. The first variant, referred to as ANN0, takes as inputs all the features from Equations (49), (50), (51), (52). The second variant is referred to as ANN1 and lacks the {a mathematical formula}mincpik input, which is the most difficult to encode in Combinatorial Optimization.
      </paragraph>
      <paragraph>
       We evaluated the ANNs over their training sets and over separate test sets. The test set for each core was obtained by sampling 50 examples at random from the training sets of the other cores. Therefore, each test set contains {a mathematical formula}50×47=2350 unseen examples, it is considerably different from the corresponding training set and considerably challenging.
      </paragraph>
      <paragraph>
       Fig. 2 reports the mean absolute values of the prediction errors for ANN0 on each core. The cores are indexed by rows over an {a mathematical formula}8×6 grid, hence cores 0–5 refer to the first row, 6–11 to the second and so on. The errors refer to efficiency values in the range {a mathematical formula}(0,1], hence a mean error of 0.01 corresponds to a 1% efficiency difference. The mean prediction errors are very low for both the training and the test set. Moreover, the efficiency of the cores on the first row and of those on the left and right chip borders is considerably easier to predict.
      </paragraph>
      <paragraph>
       Fig. 3 reports the mean absolute values of the prediction errors for the ANN1 networks, i.e. those without the {a mathematical formula}mincpik input. Their average accuracy is still quite good, but definitely worse than ANN0 ({a mathematical formula}∼2.5% against {a mathematical formula}∼1%). On the other hand, the ANN1 networks are easier to embed and may be employed with more effective optimization techniques. This kind of trade-off is not unique to EML. Rather, it is common when dealing with real world problems that involve approximate models. In this context, EML provides a flexible approach to balance model accuracy and solver efficacy.
      </paragraph>
      <paragraph>
       Fig. 4 reports the error histogram over the training set for the ANN0 and ANN1 networks corresponding to core #20 (located close to the center of the chip). Actual errors are considered here rather than their absolute values. In most cases, both networks provide very accurate predictions, but larger error values (e.g. in the order of 10%) are more likely to occur for ANN1. This is potentially an issue, given the importance of maximum errors in EML (see the beginning of this Section 7.3).
      </paragraph>
      <paragraph>
       Finally, we have investigated the impact that changing the size of the training set has on the accuracy of the ANN1 networks. In particular, we have tried to: (1) decrease the size of each training set by removing a (varying) percentage of instances, chosen uniformly at random; and (2) increase the size of each training set, by adding a (varying) number of instances chosen uniformly at random from the other training sets. The networks trained on these modified sets have been tested on the original test sets. We have found that both removing and adding as little as 10% instances has a significant adverse effect on the accuracy, leading to much larger average errors for some cores. The rationale is that both removing and adding instances causes an alteration of the factorial designed employed in the original training sets, making some region of the input space either over- or under-represented. The accuracy plots for this experimentation are not reported in this paper, but they are available on-line.{sup:6}
      </paragraph>
      <paragraph>
       Empirical models for the{a mathematical formula}WDPmax  For the second dispatching problem, we can use a classifier as an Empirical Model, trained to distinguish low- and high-efficiency cores. Specifically, our Empirical Model consists of a Decision Tree (DT) for each core. We chose DTs for two main reasons: first, DTs were accurate enough for the problem at hand. Second, our choice gives the opportunity to discuss the EML approach on a Machine Learning technique that is radically different from Artificial Neural Networks.
      </paragraph>
      <paragraph>
       We trained our Decision Trees using the C4.5 algorithm [43], implemented in Weka [44] with the name J48, with the default parameters (in particular, all trees are pruned). The performance of the DTs was assessed both via 10-fold cross-validation over the training set, and via evaluation over the test sets used for the ANNs. The outcome of the two evaluations is reported in Fig. 5, which shows the percentage of correctly classified instances for the DT corresponding to each core. The accuracy is actually very high in both cases.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      In this section, we present an experimental evaluation of several solution methods for our example problems. We consider all the alternative modeling approaches discussed in Section 3, namely: (1) using a heuristic as a proxy for the efficiency values; (2) using fitting to adjust the parameters of an expert-designed model; and finally (3) several solution methods based on EML.
     </paragraph>
     <paragraph>
      The benchmark for the experimentation is a set of 20 instances, each with 288 jobs to be mapped on 48 cores (i.e. the full SCC platform). The instances were designed to be as diverse as possible. As a common trait, each instance includes a majority of low-CPI jobs, plus a small number of jobs with a relatively high CPI: this was done to make the benchmark challenging, leaving at the same time sufficient room for improvements. The instances and the detailed results are publicly available for download.{sup:7}
     </paragraph>
     <paragraph>
      All the solution approaches that we present are based on approximate models, since relying on the simulator during search would lead to unacceptable response times. As a consequence, it is necessary to distinguish two levels in our experimental comparisons:
     </paragraph>
     <list>
      <list-item label="1.">
       First, we compare the effectiveness of different solution approaches in terms of the value of the cost function, i.e. the predicted solution quality.
      </list-item>
      <list-item label="2.">
       Second, we compare solution approaches in terms of the “real” solution quality, which in our case is obtained from the simulator.
      </list-item>
     </list>
     <paragraph>
      The first level of comparison is the one adopted by many combinatorial optimization papers: it allows one to assess the effectiveness of a given approach in finding solutions for a given model. This comparison is meaningful only for solution approaches based on the same approximate system model. The second type of comparison evaluates the combined effectiveness of the solution method and the approximate model. We will use the first type of comparison in Section 8.3, in order to determine the best solution method for each modeling approach (heuristic, model fitting, EML); the second type of evaluation is used in Section 8.4 to compare optimization approaches based on different models.
     </paragraph>
     <section label="8.1">
      <section-title>
       Approximate system models
      </section-title>
      <paragraph>
       In this section, we briefly present/review the approximate system models considered in our experimentation.
      </paragraph>
      <paragraph>
       A heuristic as a proxy for the efficiency  The computation workload of each job is measured by its CPI value, and jobs are executed on each core in an interleaved fashion by the thermal aware scheduler from Section 3. As a consequence, it seems reasonable to expect on each core k a correlation between the efficiency and the average job CPI.
      </paragraph>
      <paragraph>
       The existence of such a correlation has been checked empirically by performing some pilot experiments. Fig. 6 shows the results for core #41, and contains a scatter plot with the efficiency on the y-axis and the average CPI of the jobs on the x-axis. Each point corresponds to a different set of jobs, and the color reflects the density of the data points (red denotes higher values, and hence the most typical region of operation). There is indeed a strong correlation between the efficiency and the average CPI, which is almost linear for low average CPI values (i.e. the most interesting region for the considered problems). The results for the other cores are not always as clean as those obtained for core #41, but a good degree of correlation is always present.
      </paragraph>
      <paragraph>
       Based on these observations, our domain experts (i.e. the authors of the platform simulator) have suggested to employ the average job CPI on each core as a proxy for its efficiency in the {a mathematical formula}WDPbal. The resulting system model is:{a mathematical formula} where avgcpi is the vector of the {a mathematical formula}avgcpik values, as specified in the feature definitions (i.e. Equation (49)), and w is a vector of weights that identifies how sensitive each core is to changes of the average CPI. Assuming we want to avoid the use of model fitting (which will be considered in the next paragraph), the value of w must be fixed based on the knowledge of the domain expert. In our experiments, we have considered two possibilities:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}w=1 for all cores;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}w=1 for internal cores, {a mathematical formula}w=0.75 for cores on the chip borders, {a mathematical formula}w=0.5 for cores on the chip corners.
       </list-item>
      </list>
      <paragraph>
       the first choice (referred to as ACPI model) is appropriate if reliable information is missing. The second choice (referred to as wACPI model) takes into account that heat dissipation is more efficient for the cores along the border of the silicon die. We have employed the heuristic approach only for the {a mathematical formula}WPDbal problem.
      </paragraph>
      <paragraph>
       Using fitting to adjust an expert-designed model  A compromise between using EML and relying on a heuristic consists in employing function fitting to adjust the parameters of an expert-designed model. With the aim to evaluate this approach, we have devised a linear model for the {a mathematical formula}WDPbal based on the features from Section 7. The idea is that pilot experiments and the observations from Section 7.1 should be sufficient to define this model structure, without relying on more powerful learning techniques. The resulting model is referred to as FEAT and is given by:{a mathematical formula} where wa, wm, wn, wo are vectors of weights that are obtained via linear regression. Linear regression makes it feasible to obtain values for all the parameters; however, it also requires one to build a training set, and therefore an overall design effort much closer to that of extracting an Artificial Neural Network. Still, in the FEAT model the cost function is linear, which may allow the optimization approach to get considerably closer to the optimum (predicted) cost. We have employed the model fitting approach only for the {a mathematical formula}WDPbal problem.
      </paragraph>
      <paragraph>
       Using an Empirical Model  Finally, we have modeled the system behavior via Empirical Model Learning. The details of our Empirical Models have already been given in Section 7. Here we simply recall that we employed the ANN0 and ANN1 Neural Networks for the {a mathematical formula}WDPbal, while we employed Decision Trees (referred to as DT) for the {a mathematical formula}WDPmax. We recall also that the ANN1 model differs from ANN0 because it lacks the {a mathematical formula}mincpik input feature.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       The solution approaches
      </section-title>
      <paragraph>
       A summary of the solution approaches considered in our experimentation is reported in Table 3. The table highlights the solution techniques, the problems they were applied to (i.e. {a mathematical formula}WDPbal and {a mathematical formula}WDPmax), and the models employed for the system behavior. Only two of the solution techniques (LS and CP) have been applied in all configurations: all the remaining ones were restricted to linear formulations (MILP) or to specific system models (MINLP and SMT).
      </paragraph>
      <paragraph>
       We used Localsolver v3.0 [45] to implement our LS approach. We defined our MINLP model in GAMS [46] and we solved it using BARON, via the Neos Servers for Optimization [47]. As a CP system, we chose Google or-tools,{sup:8} and we employed the Neuron Constraint implementation that we developed in [4]. In the CP model, we use integer variables with a fixed precision factor to represent real-valued variables. Finally, we chose Z3 by Microsoft Research for our SMT models [39] and IBM ILOG CPLEX{sup:9} v12.5 for the MILP models. All solvers were chosen based on their effectiveness (tested in some pilot experiments) and on the accessibility of their modeling interfaces.
      </paragraph>
      <paragraph>
       We use the default configuration of Localsolver, CPLEX, and BARON to solve our LS, MILP, and MINLP models. The CP and SMT models are instead solved via a Randomized Adaptive Decomposition approach, similar in spirit to Large Neighborhood Search and described in the next paragraph. This was done in order to boost their ability to find high quality solutions in a reasonably small time (a few tens of seconds in our case). The decomposition technique was not applied in LS (because Localsolver is already designed to be scalable), nor in MINLP (because we had access to BARON via a slow, http-based, API), nor in MILP (this could be a topic for future research).
      </paragraph>
      <paragraph>
       Randomized adaptive decomposition  Our CP and SMT approaches are wrapped in a decomposition method similar to Large Neighborhood Search to reduce the time for obtaining high-quality solutions. The method starts from an initial solution, which is obtained via the simple greedy heuristic presented in Algorithm 1. The heuristic works by iteratively mapping the most computation-intensive job (i.e. the one with lowest CPI) on the least loaded cores. A core {a mathematical formula}k0 is considered to be less loaded than a core {a mathematical formula}k1 if: (1) there are fewer jobs on {a mathematical formula}k0 than on {a mathematical formula}k1; (2) the number of jobs is identical, but the sum of job CPIs on {a mathematical formula}k0 is lower than the sum for {a mathematical formula}k1. This approach tries to balance the average CPI value on each core, essentially following the same idea at the basis of the ACPI model.
      </paragraph>
      <paragraph>
       Then, the decomposition method proceeds analogously to Large Neighborhood Search, by iteratively: (1) selecting a small set {a mathematical formula}CR of cores; (2) relaxing the mapping decisions for all jobs running on such cores; (3) solving a restricted problem to re-map the jobs within the cores in {a mathematical formula}CR, with the aim to improve the solution quality. The difference with LNS is that, when solving the restricted subproblem, we change the objective function to:{a mathematical formula} i.e. in the cost function we neglect the efficiency of all cores, except those in the set {a mathematical formula}CR. In other words, when solving the restricted problem at each iteration we look for local improvements rather than for global ones. This is particularly useful for the {a mathematical formula}WDPbal, for which it may happen that during search multiple cores have a similarly low efficiency. In this situation, the decomposition approach can focus on each of those critical cores individually.
      </paragraph>
      <paragraph>
       We stop each iteration as soon as one improving solution is found, or when a time limit is reached. In the SMT approach, the restricted subproblem is solved via Z3 with default parameters. In the CP case we use restarts and depth first search, with random variable and value selection.
      </paragraph>
      <paragraph>
       For choosing the cores to relax, we always select a number {a mathematical formula}nbad of “bad” cores, of which we want to improve the efficiency, plus a number {a mathematical formula}ngood of “good” cores, for which we can accept an efficiency reduction. In practice we employ a slightly different criterion on the two example problems. For the{a mathematical formula}WDPbal:the “bad” cores are chosen randomly (with uniform probability) among those with minimum efficiency; the “good” cores are chosen randomly among the rest, with a selection probability given by the (normalized) ratio {a mathematical formula}/avgcpik′keff, where {a mathematical formula}avgcpik′ is equal to {a mathematical formula}/maxcpiavgcpik.For the{a mathematical formula}WDPmax:the “bad” cores are chosen randomly (with uniform probability) among those having low efficiency; the “good” cores are chosen at random among the rest, with a selection probability given by the (normalized) value of {a mathematical formula}avgcpik. In our experiments, we have {a mathematical formula}nbad=1 and {a mathematical formula}ngood=3 for the {a mathematical formula}WDPbal, and we have {a mathematical formula}nbad=2 and {a mathematical formula}ngood=3 for the {a mathematical formula}WDPmax.
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Evaluation based on the predicted quality
      </section-title>
      <paragraph>
       In this section, we compare the solution approaches from Table 3 in terms of the predicted solution quality: this allow us to assess the effectiveness of each approach at finding good solutions for specific system models. The wACPI and FEAT models were solved via Local Search, since such an approach performed slightly better than MILP on the (very similar) ACPI model.
      </paragraph>
      <paragraph>
       Results for the{a mathematical formula}WDPbal  We obtained a LS approach based on the ACPI model for the {a mathematical formula}WDPbal by inserting the {a mathematical formula}hACPI(x) function into the core Local Search model from Section 6. An analogous process was followed to obtain a MILP approach. We solved the problem using a time limit of 90 seconds for Localsolver (after that time no significant improvement was obtained) and of 1 hour for CPLEX (in an effort to prove optimality).
      </paragraph>
      <paragraph>
       The results of this experimentation are reported in Table 4, in the ACPI columns. For both the approaches we report the minimum average CPI for each instance (i.e. the value of the objective function). For MILP we also report the value of the best upper bound at the end of the search process: as can be seen, it was not possible to prove optimality within the time limit in most cases. However, the bound values provide an indication that the solutions found by both approaches are indeed very good, with Localsolver having a slight edge.
      </paragraph>
      <paragraph>
       Table 4 presents also the results of the EML approaches, based on the ANN0 and ANN1 model, respectively in the ANN0 and ANN1 columns. The problem objective (lowest core efficiency) is reported as a percentage value. It is important to realize that only approaches operating on the same system model can be directly compared in terms of their predicted quality. Comparisons between approaches based on different system models will be taken into account in Section 8.4, and are meaningless at this stage: this is emphasized in the table by using double-lines to separate the ACPI, ANN0, and ANN1 columns.
      </paragraph>
      <paragraph>
       We recall that a MINLP model has not been designed for the “full” Artificial Neural Network (i.e. ANN0), but only for the simplified version without the {a mathematical formula}mincpik input (i.e. ANN1). Moreover, since we rely on a remote server for solving MILP problems, it was impossible for us to use the MINLP model within our Randomized Adaptive Decomposition scheme, which severely affected the performance of the approach.
      </paragraph>
      <paragraph>
       Eventually, we decided to make a different use of the MINLP model, namely we employed it for computing a bound on the solution quality. This was done by removing the integrality restriction from the mapping variables and by solving the resulting Non-Linear Programming model. The best bound found after 2 hours is shown in Table 4 in the {a mathematical formula}MINLPbal/UB column, where values in italic font denote optimal (non-integer) solutions. We believe this – somehow disappointing – result provides actually a good example of how the flexibility of EML allows one to obtain valuable information that would be inaccessible if a single solution technique was used.
      </paragraph>
      <paragraph>
       Localsolver makes use of a randomized search algorithm, and the decomposition method that we employ for solving our CP (and SMT) model is also randomized. Therefore, for the LS and CP approaches we performed 10 runs per instance with a time limit of 90 seconds. In CP, a timeout of 2 seconds was enforced on each iteration of the decomposition method. For LS and CP, the table reports in the obj columns the average value of the objective function (i.e. minimum core efficiency) over the 10 runs, and within round brackets the standard deviation of the objective value over the 10 runs.
      </paragraph>
      <paragraph>
       Both the CP and the LS approaches managed to obtain high quality solutions, as it can be seen on the instances for which an optimal NLP bound is available. The CP approach performed usually better, with gaps as large as {a mathematical formula}∼10% for the simplified model ANN1, and as large as {a mathematical formula}∼7% for the “full” model ANN0, which is significant enough for this application. The performance of the CP approach was also considerably more robust over different runs.
      </paragraph>
      <paragraph>
       The difference in performance stems from two main reasons: first, the propagation of Neuron Constraints often allows the CP solver to quickly terminate many iterations of the decomposition method. Second, the incorporation of expert knowledge in the selection of the cores to be relaxed allows one to steer the search toward promising regions of solution space.
      </paragraph>
      <paragraph>
       Results for the{a mathematical formula}WDPmax  Here we present the results for the second dispatching problem from Section 3. As we anticipated, on this setting we have tested a single Empirical Model, i.e. the Decision Trees extracted in Section 7. We solved the benchmark instances with LS, CP, and SMT. The CP and SMT approaches make use of the decomposition method described at the beginning of Section 8. Each instance was solved 10 times with different random seeds, and with a time limit of 90 seconds. Again a time limit of 2 seconds was enforced on each iteration of the decomposition method.
      </paragraph>
      <paragraph>
       Table 5 reports, like in previous cases, the average value of the problem objective over the 10 runs and its standard deviation. Similarly to the {a mathematical formula}WDPbal, propagation and domain knowledge allow the CP approach to perform generally better than LS, although the gap is smaller on this problem. LS seems to be slightly more stable than CP, as highlighted by the standard deviation values.
      </paragraph>
      <paragraph>
       The SMT approach was the worst performer, despite being based on the same decomposition method as CP. The reason is that the Z3 solver had difficulties in proving infeasibility when solving subproblems corresponding to an unlucky selection of the relaxed cores. The CP approach, conversely, was often able to close these subproblems within the 2 seconds time limit.
      </paragraph>
     </section>
     <section label="8.4">
      <section-title>
       Evaluation on the real system
      </section-title>
      <paragraph>
       In this section, we compare the solutions provided by different approaches in terms of their quality over the target system, i.e. the SCC simulator from Section 3. By doing so, we evaluate at the same time both the optimization approach and the accuracy of the system model. This allows one to compare radically different approaches designed to solve the same practical problem. This evaluation is restricted to the {a mathematical formula}WDPbal.
      </paragraph>
      <paragraph>
       We compare solutions obtained using the ACPI, wACPI, FEAT, ANN0, and ANN1 system models. For each of them, we employed the approach that worked best in terms of predicted solution quality, hence LS was used for ACPI, wACPI, and FEAT, while CP was used for ANN0 and ANN1. Each instance in the benchmark was solved only once, with a time limit of 90 seconds (and 2 seconds for each decomposition iteration).
      </paragraph>
      <paragraph>
       The results for this experimentation are reported in Table 6. For each approach we report the minimum (simulated) core efficiency as a percentage. We also report between brackets the standard deviation of the core efficiencies (this is not the standard deviation of the cost over different runs, as each instance is solved only once). The reason for showing this standard deviation is that the minimum core efficiency, when used as a quality measure of real solutions, is not very robust w.r.t. approximation errors: a very well balanced solution with a single large approximation error could appear as having very poor quality. Adding the standard deviation allows one to detect this kind of situation.
      </paragraph>
      <paragraph>
       The solution approaches based on ANN models obtained in general better results than those with a linear objective, including the FEAT model for which the coefficients were obtained via linear regression. The advantage is in terms of both the minimum efficiency and the standard deviation. The results obtained with the more accurate network (ANN0) tend in turn to be better than those obtained with the simplified ANN1.
      </paragraph>
      <paragraph>
       The results of the simulation for the ACPI and the ANN0 models can be observed in detail in Fig. 7 and Fig. 8. Each subfigure corresponds to an instance, and each tile within a subfigure corresponds to a core (we recall that the platform has an {a mathematical formula}8×6 layout). Green/red tiles respectively denote higher/lower efficiency values: a full red corresponds to 50% efficiency, while a full green to 100%. The {a mathematical formula}LSbal(ACPI) approach (Fig. 7) is often able to obtain fairly balanced workloads. However, the produced mappings do occasionally lead to abnormally low efficiency for some cores. This happens even in cases where the solution is close to optimal: by cross-checking the results with those of Table 4, it is possible to see for example that very low efficiency values occur on instance #15, where the cost function has value 2.76 against a bound of 2.80. The efficiency maps from Fig. 8, corresponding to the solutions provided by {a mathematical formula}CPbal(ANN0), are much more uniform.
      </paragraph>
      <paragraph>
       By comparing the results of Table 6 with those from Table 4, it can be seen that the predicted (minimum) efficiency levels tend to be 5–10% higher than the real values. On this regard, there are two interesting facts to observe: first, despite the significant error level, the CP solutions (with the ANN0 model) are very well balanced in terms of efficiency: this suggests that the overestimation tends to be similar over all cores. Second, the error level is of the same order of the largest errors in the EM evaluation from Section 7. This strengthens the idea that the optimizer may be attracted by solutions with a high predicted quality, but also a large margin of error. This behavior, although certainly not ideal, is actually not totally undesirable: in fact, it may provide a systematic approach to make the Empirical Model more robust by including the simulated solutions in the training set. This method may allow us to improve the model robustness without the need to increase dramatically the training set size. We leave the investigation of this idea as a topic for future research.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>