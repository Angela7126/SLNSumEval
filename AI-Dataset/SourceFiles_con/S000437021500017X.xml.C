<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Continual curiosity-driven skill acquisition from high-dimensional video inputs for humanoid robots.
   </title>
   <abstract>
    In the absence of external guidance, how can a robot learn to map the many raw pixels of high-dimensional visual inputs to useful action sequences? We propose here Continual Curiosity driven Skill Acquisition (CCSA). CCSA makes robots intrinsically motivated to acquire, store and reuse skills. Previous curiosity-based agents acquired skills by associating intrinsic rewards with world model improvements, and used reinforcement learning to learn how to get these intrinsic rewards. CCSA also does this, but unlike previous implementations, the world model is a set of compact low-dimensional representations of the streams of high-dimensional visual information, which are learned through incremental slow feature analysis. These representations augment the robot's state space with new information about the environment. We show how this information can have a higher-level (compared to pixels) and useful interpretation, for example, if the robot has grasped a cup in its field of view or not. After learning a representation, large intrinsic rewards are given to the robot for performing actions that greatly change the feature output, which has the tendency otherwise to change slowly in time. We show empirically what these actions are (e.g., grasping the cup) and how they can be useful as skills. An acquired skill includes both the learned actions and the learned slow feature representation. Skills are stored and reused to generate new observations, enabling continual acquisition of complex skills. We present results of experiments with an iCub humanoid robot that uses CCSA to incrementally acquire skills to topple, grasp and pick-place a cup, driven by its intrinsic motivation from raw pixel vision.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Over the past decade, there has been a growing trend in humanoid robotics research towards robots with a large number of joints, or degrees of freedom, notably the ASIMO [1], PETMAN [2] and the iCub [3]. These robots demonstrate a high amount of dexterity and are potentially capable of carrying out complex human-like manipulation. When interacting with the real-world, these robots are faced with several challenges, not the least of which is the problem of how to solve tasks upon processing an abundance of high-dimensional sensory data.
     </paragraph>
     <paragraph>
      In the case of well structured environments, these robots can be carefully programmed by experts to solve a particular task. But real-world environments are usually unstructured and dynamic, which makes it a daunting task to program these robots manually. This problem can be substantially alleviated by using reinforcement learning (RL; [4], [5]), where a robot learns to acquire desired task-specific behaviors, by maximizing the accumulation of task-dependent external rewards through simple trial-and-error interactions with the environment.
     </paragraph>
     <paragraph>
      Unfortunately, for humanoid robots equipped with vision, the sensory and joint state space are so large that it is extremely difficult to procure the rewards (if any exist) by random exploration. For example, if the robot receives a reward for sorting objects, it could take an extremely long time to obtain the reward for the first time. Therefore, it becomes necessary to (a) build lower-dimensional representations of the state-space to make learning tractable and (b) to explore the environment efficiently. But how can these robots learn to do this in the presence of external rewards that are typically only sparsely available?
     </paragraph>
     <paragraph>
      Much of the human capacity to explore and solve problems is driven by self-supervised learning [6], [7], where we seek to acquire behaviors by creating novel situations and learning from them. As an example, consider a simple playroom scenario for a baby humanoid as shown in Fig. 1. Here, the robot is placed next to a table with a few moving objects. The robot has a limited field-of-view and encounters continuous streams of images as it holds or shifts its gaze. If the robot can learn compact representations and predictable behaviors (e.g., to grasp) from its interactions with the cup, then by using these learned behaviors, it can speed up the acquisition of external rewards related to some teacher-defined task, such as placing the cup at a particular location. Continually acquiring and reusing a repertoire of behaviors and representations of the world, learned through self-supervision, can therefore make the robot adept in solving many external tasks.
     </paragraph>
     <paragraph>
      But how can the robot (a) self-supervise its exploration, (b) build representations of the high-dimensional sensory inputs and (c) continually acquire skills that enable it to solve new tasks? These problems have individually been researched in the machine learning and robotics literature [8], [9], [10], [11], [12], [13], [14], [15], [16], [17], [18], [19], [20], [21], [22], [23], [24], [25], [26], [27], [28], [29]. However, to develop a single system that addresses all these important issues together is a challenging open problem in artificial intelligence (AI) research. We propose an online-learning framework that addresses this open problem.
     </paragraph>
     <paragraph>
      In order to make the robot self-supervised or intrinsically-motivated to explore new environments, we use the theory of Artificial Curiosity (AC; [30], [31]). AC mathematically describes curiosity and creativity. AC-driven agents are interested in the learnable but as-yet-unknown aspects of their environment, and are disinterested in the already learned and inherently unlearnable (noisy) aspects. Specifically, the agent receives intrinsic rewards for action sequences, and these rewards are proportional to the improvement of the agent's internal model or predictor of the environment. Using RL and the self-generated intrinsic rewards derived using AC [32], [33], [34], [35], [36], [25], the agent is motivated to explore the environment where it makes maximum learning progress.
     </paragraph>
     <paragraph>
      Most RL algorithms however, tend to work only if the dimensionality of the state space is small, or its structure is simple. In order to deal with massive high-dimensional streams of raw sensory information obtained, for example through vision, it is essential to reduce the input dimensionality by building low-dimensional but informative abstractions of the environment [37]. An abstraction maps the high-dimensional input to a low-dimensional output. The high-dimensional data sensed by a robot is often temporally correlated and can be greatly compressed if the temporal coherence in the data is exploited. Slow Feature Analysis (SFA; [14], [38], [39]) is an unsupervised learning algorithm that extracts temporal regularities from rapidly changing raw sensory inputs. SFA is based on the Slowness Principle [40], [41], [42], which states that the underlying causes of changing signals vary more slowly than the primary sensory stimulus. For example, individual retinal receptor responses or gray-scale pixel values of video may change quickly compared to latent abstract variables, such as the position of a moving object. SFA has achieved success in many problems and scenarios, e.g., extraction of driving forces of a dynamical system [43], nonlinear blind source separation [44], as a preprocessor for reinforcement learning [39], and learning of place-cells, head-direction cells, grid-cells, and spatial view cells from high-dimensional visual input [38].
     </paragraph>
     <paragraph>
      SFA techniques are not readily applicable to open-ended online learning agents, as they estimate covariance matrices from the data via batch processing. We instead use Incremental Slow Feature Analysis (IncSFA; [45], [46]), which does not need to store any input data or computationally expensive covariance matrix estimates. IncSFA makes it feasible to handle high-dimensional image data in an open-ended manner.
     </paragraph>
     <paragraph>
      IncSFA, like most online learning approaches, gradually forgets previously learned representations whenever the statistics of the input change, for example, when the robot shifts its gaze from perspective two to perspective one in Fig. 1. To address this issue, in our previous work, we proposed an algorithm called Curiosity-Driven Modular Incremental Slow Feature Analysis (Curious Dr. MISFA; [47], [48]), which retains what was previously learned in the form of expert modules[29]. From a set of input video streams, Curious Dr. MISFA actively learns multiple expert modules comprising slow feature abstractions, in the order of increasing learning difficulty. The algorithm continually estimates the initially unknown learning difficulty through intrinsic rewards generated by exploring the input streams.
     </paragraph>
     <paragraph>
      Using Curious Dr. MISFA, the robot in Fig. 1 finds its interactions with the plastic cup more interesting (easier to encode) than the complex movements of the other objects. This results in a compact slow feature abstraction that encodes its interactions with the cup. Eventually, the robot finds the cup-interaction boring and its interest shifts towards encoding other perspectives while retaining the learned abstraction. Can the robot simultaneously acquire re-usable skills while acquiring abstractions? Each abstraction learned encodes some previously unknown regularity in the input observations, which can therefore be used as a basis for acquiring new skills.
     </paragraph>
     <paragraph>
      Our contribution here is the Continual Curiosity-driven Skill Acquisition (CCSA) framework, for acquiring both abstractions and skills in an online and continual manner. In RL, the options framework [49] formalizes skills as RL policies, active within a subset of the state space, which can terminate at subgoals, after which another option takes over. When the agent has a high-dimensional input, like vision, an option requires a dimensionality reducing abstraction, so that policy learning becomes tractable. CCSA is a task-independent curiosity-driven learning algorithm that combines Curious Dr. MISFA with the options framework. Each slow feature abstraction learned by Curious Dr. MISFA augments the robot's default state space, which in our case is a set of low-level kinematic joint poses learned using Task Relevant Roadmaps [50]. This augmented state space is then clustered to create new distinct states. A Markovian transition model is learned by exploring the new state space. The reward function is also learned through exploration, with the agent being intrinsically rewarded for making state-transitions that produce a large variation in the slow-feature outputs. This specialized reward function is used to build the option's policies, to drive the robot to states where such transitions will occur. Such transitions are shown to correspond to bottleneck states, i.e., “doorways”, which are known to be good subgoals in the absence of externally imposed goals [51], [52]. Once the transition and reward functions are learned, the option's policy is learned via Least-Squares Policy Iteration [53]. Skills acquired by the robot in the form of options, are reused to generate new input observations, enabling acquisition of more complex skills in a continual open-ended manner [29], [54]. Using CCSA, in our experiments, an iCub humanoid robot addresses the open problems discussed earlier, acquiring a repertoire of skills (topple, grasp) from raw-pixel vision, driven purely by its intrinsic motivation.
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. Section 2 discusses related research work carried out prior to this paper. Sections 3 and 4 present an overview and a formulation of the learning problem associated with the CCSA framework. Section 5 discusses details of the internal workings of CCSA. Section 6 contains experiments and results conducted using an iCub humanoid robot; Sections 7 Discussion, 8 Conclusion present future work and conclusions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Existing intrinsically-motivated skill acquisition techniques in RL have been applied to simple domains. For example, Bakker and Schmidhuber [55] proposed a hierarchical RL framework called HASSLE in a grid world environment, where high-level policies discover subgoals from clustering distance-sensor outputs and low-level policies specialize on reaching the subgoals. Stout and Barto [24] explore the use of a competence-based intrinsic motivation as a developmental model for skill acquisition in simple artificial grid-world domains. Pape et al. [25] proposed a method for autonomous acquisition of tactile skills on a biomimetic robot finger, through curiosity-driven reinforcement learning.
     </paragraph>
     <paragraph>
      There have been attempts to find skills using feature-abstractions in domains such as those of humanoid robotics. Hart [56] proposed an intrinsically motivated hierarchical skill acquisition approach for a humanoid robot. The system combines discrete event dynamical systems[57] as a control basis and an intrinsic reward function [26] to learn a set of controllers. However, the intrinsic reward function used is task specific, and the system requires a teacher to design a developmental schedule for the robot.
     </paragraph>
     <paragraph>
      Konidaris et al. [58], [59] show how each option might be assigned with an abstraction from a library of many sensorimotor abstractions to acquire skills. The abstractions have typically been hand-designed and learning was assisted by human-demonstration. In their recent work [27], an intrinsic motivation system makes a robot acquire skills from one task to improve the performance on a second task. However, the robot used augmented reality tags to identify target objects and had access to a pre-existing abstraction library. CCSA autonomously learns a library of abstractions and control policies simultaneously from raw-pixel streams generated via exploration, without any prior-knowledge of the environment.
     </paragraph>
     <paragraph>
      Mugan and Kuipers's [60] Qualitative Learner of Action and Perception system discretizes low-level sensorimotor experience through defining landmarks in the variables and observing contingencies between landmarks. It builds predictive models on this low-level experience, which it later uses to generate plans of actions. It either selects its actions randomly (early) or such that it expects to make fast progress in the performance of the predictive models (artificial curiosity). The sensory channels are preprocessed so that the input variables, for example, track the positions of the objects in the scene. A major difference between this system and ours is that we operate upon the raw pixels directly, instead of assuming the existence of a low-level sensory model that can track the positions of the objects in the scene.
     </paragraph>
     <paragraph>
      Baranes and Oudeyer [61] proposed an intrinsic motivation architecture called SAGG-RIAC, for adaptive goal-exploration. The system comprises two learning parts, one for self-generation of subgoals within the task-space and the other for exploration of low-level actions to reach the subgoals selected. The subgoals are generated using heuristic methods based on a local measure of competence progress. The authors show results using a simulated quadruped robot on reaching tasks. The system however, assumes that a low-dimensional task-space is provided. CCSA is a task-independent approach, where subgoals are generated automatically by the slow feature abstractions that encode spatio-temporal regularities in the raw high-dimensional video inputs.
     </paragraph>
     <paragraph>
      Ngo et al. [62], [63] investigated an autonomous learning system that utilizes a progress-based curiosity drive to ground a given abstract action, e.g., placing an object. The general framework is formulated as a selective sampling problem in which an agent samples any action in its current situation as soon as it sees that the effects of this action are statistically unknown. If no available actions have a statistically unknown outcome, the agent generates a plan of actions to reach a new setting where it expects to find such an action. Experiments were conducted using a Katana robot arm with a fixed overhead camera, on a block-manipulation task. The authors show that the proposed method generates sample-efficient curious exploratory behavior and continual skill acquisition. However, unlike CCSA, the sensorimotor abstractions are hand-designed and not learned by the agent.
     </paragraph>
     <paragraph>
      CCSA uses IncSFA to find low-dimensional manifolds within the raw pixel inputs, providing a basis for coupled perceptual and skill learning. We emphasize the special utility of SFA for this task over similar methods such as principal component analysis [64], or predictive-projections [65], which are based on variance or nearest neighbor learning, while Slow features through IncSFA extract temporal invariance from input streams that represent “doorway” or “bottleneck” aspects (choke-points between two more fully connected subareas), similar to Laplacian-Eigen Maps [66], [67], [68]. The hierarchical reinforcement learning literature [69], [70], [71], [49], [51], [55], [67], [52] illustrates that such bottlenecks can be useful subgoals. Finding such bottlenecks in visual input spaces is a relatively new concept, and one we exploit in the iCub experiments. For example, while it moves its arm around a cup in the scene, the bottleneck state is where it topples the cup over, invariant to the arm position. The two subareas in this case are 1. the cup is upright (stable) while the arm moves around, 2. the cup is on its side (stable) while the arm moves around. More studies on the types of representations learned by the IncSFA algorithm can be found elsewhere [47], [46].
     </paragraph>
     <paragraph>
      An initial implementation of Curious Dr. MISFA for learning slow feature abstractions [48], a discussion on its neurophysiological correlates [47] and a prototypical construction of a skill from a slow feature abstraction [72] can be found in our previous work. The novel contribution of this paper is that we present an online learning algorithm (CCSA) that uses Curious Dr. MISFA for learning slow feature abstractions, such that it enables a robot to acquire, store and reuse skills in an open-ended continual manner. We also formally address the underlying learning problem of task-independent continual curiosity-driven skill acquisition. We demonstrate the working of our algorithm with iCub experiments and show the advantages of intrinsically motivated skill acquisition for solving an external task.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Overview of the proposed framework
     </section-title>
     <paragraph>
      In this section, we will briefly summarize the overall framework of the proposed algorithm, which we call Continual Curiosity driven Skill Acquisition (CCSA). Fig. 2 illustrates the overall framework. The learning problem associated with CCSA can be described as follows: From a set of pre-defined or previously acquired input exploratory behaviors, which generate potentially high-dimensional time-varying observation streams, the objective of the agent is to (a) acquire an easily learnable yet unknown target behavior and (b) re-use the target behavior to acquire more complex target behaviors. The target behaviors represent the skills acquired by the agent. A sample run of the CCSA framework to acquire a skill is as follows (see Fig. 2):
     </paragraph>
     <list>
      <list-item label="(a)">
       The agent starts with a set of pre-defined or previously acquired exploratory behaviors. We make use of the options framework [49] to formally represent the exploratory behaviors as exploratory options (see Section 4 for a formal definition of the terminology used here).
      </list-item>
      <list-item label="(b)">
       The agent makes high-dimensional observations through a sensor-function, such as a camera, upon actively executing the exploratory options.
      </list-item>
      <list-item label="(c)">
       Using our previously proposed curiosity-driven modular incremental slow feature analysis (Curious Dr. MISFA) algorithm, the agent learns a slow feature abstraction that encodes the easiest-to-learn yet unknown regularity in the observation streams (see Section 5.2).
      </list-item>
      <list-item label="(d)">
       The slow feature abstraction outputs are clustered to create feature states that are augmented to the agent's abstracted-state space, which contains previously encoded feature-states (see Section 5.3).
      </list-item>
      <list-item label="(e)">
       A Markovian transition model is learned by exploring the new abstracted-state space. The reward function is also learned through exploration, with the agent being intrinsically rewarded for making state-transitions that produce a large variation (high statistical variance) in the slow-feature outputs. This specialized reward function is used to learn action-sequences (policy) that drives the agent to states where such transitions will occur (see Section 5.3).
      </list-item>
      <list-item label="(f)">
       Once the transition and reward functions are learned, a deterministic policy is learned via model-based Least-Squares Policy Iteration (LSPI; [53]). The learned policy and the learned slow feature abstraction together constitute a target option, which represents the acquired skill (see Section 5.3).
      </list-item>
      <list-item label="(f)–(a)">
       The deterministic target-option's policy is modified to a stochastic policy in the agent's new abstracted states and is added to the set of exploratory options (see Section 5.4). This enables the agent to reuse the skills to acquire more complex skills in a continual open-ended manner [29], [54].
      </list-item>
     </list>
     <paragraph>
      CCSA is a task-independent algorithm, i.e., it does not require any design modifications when the environment is changed. However, CCSA makes the following assumptions: (a) The agent's default abstracted-state space contains low-level kinematic joint poses of the robot learned offline using Task Relevant Roadmaps [50]. This is done to limit the iCub's exploration of its arm to a plane parallel to the table. This assumption can be relaxed resulting in a larger space of arm-exploration of the iCub, and the skills thus developed may be different. (b) CCSA requires at least one input exploratory option. To minimize human inputs into the system, in our experiments at {a mathematical formula}t=0, the agent starts with only a single input exploratory option, which is a random-walk in the default abstracted-state space. However, environment or domain specific information can be used to design several input exploratory options in order to shape the resulting skills. For example, random-walk policies mapped to different sub-regions in the robot's joint space can be used.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Theoretical formulation of the learning problem
     </section-title>
     <paragraph>
      In this section, we present a theoretical formulation of the learning problem associated with our proposed CCSA framework. We first formalize the curiosity-driven skill acquisition problem and then later in the section we present a continual extension of it.
     </paragraph>
     <section label="4.1">
      <section-title>
       Curiosity-driven skill acquisition
      </section-title>
      <paragraph>
       Given a fixed set of input exploratory options, which generate potentially high dimensional observation streams that may or may-not be unique, the objective is to acquire a previously unknown target option corresponding to the easily-encodable observation stream. Fig. 3 illustrates the learning process. The learning process iterates over the following steps:
      </paragraph>
      <paragraph>
       (a) Estimate the easily-encodable yet unknown observation stream, while simultaneously learning a compact encoding (abstraction) for it.
      </paragraph>
      <paragraph>
       (b) Learn an option that maximizes the statistical variance of the encoded abstraction output. The problem is formalized as follows:
      </paragraph>
      <section label="4.1.1">
       <section-title>
        Notation
       </section-title>
       <section>
        <section-title>
         Environment
        </section-title>
        <paragraph>
         An agent is in an environment that has a state-space {a mathematical formula}S. It can take an action {a mathematical formula}a∈A and transition to a new state according to the transition-model (environment dynamics) {a mathematical formula}P:S×A→S. The agent observes the environment state s as a high-dimensional vector, {a mathematical formula}x∈RI,I∈N.
        </paragraph>
       </section>
       <section>
        <section-title>
         Abstraction
        </section-title>
        <paragraph>
         Let Θ denote some online abstraction-estimator that updates a feature-abstraction ϕ, where {a mathematical formula}Θ(x,ϕ) returns an updated abstraction for an input x. The abstraction {a mathematical formula}ϕ:x↦y maps a high-dimensional input observation stream {a mathematical formula}x(t)∈RI to a lower-dimensional output {a mathematical formula}y(t)∈RJ,J≪I,J∈N, such that {a mathematical formula}y(t)=ϕ(x(t)).
        </paragraph>
       </section>
       <section>
        <section-title>
         Abstracted-state space
        </section-title>
        <paragraph>
         The agent's abstracted-state space {a mathematical formula}SΦ contains the space spanned by the outputs y of all the abstractions that were previously learned using Θ.
        </paragraph>
       </section>
       <section>
        <section-title>
         Input exploratory options
        </section-title>
        <paragraph>
         The agent can execute an input set of pre-defined temporally extended action sequences, called the exploratory option set{a mathematical formula}Oe={O1e,…,One;n≥1}. Each exploratory option is defined as a tuple {a mathematical formula}〈Iie,βie,πie〉, where {a mathematical formula}Iie⊆SΦ is the initiation set comprising abstracted states where the option is available, {a mathematical formula}βie:SΦ→[0,1] is the option termination condition, which will determine where the option terminates (e.g., some probability in each state), and {a mathematical formula}πie:Iie×A→[0,1] is a pre-defined stochastic policy, such as a random walk within the applicable state space. Each exploratory-option's policy generates an observation stream via a sensor-function {a mathematical formula}U, such as an image-sensor like a camera:{a mathematical formula} where {a mathematical formula}P is the unknown transition model of the environment, {a mathematical formula}sΦ∈Iie is the agent's current abstracted state while executing the ith exploratory option {a mathematical formula}Oie at time t, {a mathematical formula}s∈S is the corresponding environment state, and {a mathematical formula}πie(sΦ) returns an action. Let {a mathematical formula}X={x1,…,xn} denote the set of n I-dimensional observation streams generated by the n exploratory-option's policies. At each time t however, the learning algorithm's input sample is from only one of the n observation-streams.
        </paragraph>
       </section>
       <section>
        <section-title>
         Curiosity function
        </section-title>
        <paragraph>
         Let {a mathematical formula}Ω:X→[0,1) denote a function indicating the speed of learning an abstraction by the abstraction-estimator Θ. Ω induces a total ordering among the observation streams making them comparable in terms of learning difficulty.{sup:1}
        </paragraph>
       </section>
       <section>
        <section-title>
         Target options
        </section-title>
        <paragraph>
         Unlike the pre-defined input exploratory-option set, a target-option set {a mathematical formula}OL is the outcome of the learning process. A target option {a mathematical formula}OL∈OL contains a learned abstraction {a mathematical formula}ϕi and a learned deterministic policy {a mathematical formula}πiL. It is defined as a tuple {a mathematical formula}〈IiL,βiL,ϕi,πiL〉. {a mathematical formula}IiL⊆(SΦ×SϕiΦ) is the target-option's initiation set defined over the augmented state-space {a mathematical formula}(SΦ×SϕiΦ), where {a mathematical formula}SϕiΦ denotes the space spanned by the abstraction {a mathematical formula}ϕi's output {a mathematical formula}y(t)=ϕ(xj(t)), {a mathematical formula}xj∈X. {a mathematical formula}βi is the option's termination condition, and {a mathematical formula}πiL:(SΦ×SϕiΦ)→A is the learned deterministic policy.
        </paragraph>
       </section>
       <section>
        <section-title>
         Encoded observation streams
        </section-title>
        <paragraph>
         Let {a mathematical formula}XOL(t) denote an ordered set (induced by time t) of pre-images of the learned abstractions outputs, {a mathematical formula}XOL(t)={ϕi←yi,∀OiL∈OL(t)}. {a mathematical formula}XOL(t) represents the set of encoded observation streams at time t.
        </paragraph>
       </section>
       <section>
        <section-title>
         Other notation
        </section-title>
        <paragraph>
         {a mathematical formula}|.| indicates cardinality of a set, {a mathematical formula}‖.‖ indicates Euclidean norm, {a mathematical formula}〈.〉t indicates averaging over time, {a mathematical formula}〈.〉tτ indicates windowed-average with a fixed window size τ over time. δ is a small scalar constant (≈0). {a mathematical formula}Var[.] represents statistical variance and ∀ indicates {a mathematical formula}forall.
        </paragraph>
       </section>
      </section>
      <section label="4.1.2">
       <section-title>
        Problem statement
       </section-title>
       <paragraph>
        With the above notation, curiosity-driven skill acquisition problem can be formalized as an optimization problem with the objective that: Given a fixed set of input exploratory options {a mathematical formula}Oe, find a target-option set {a mathematical formula}OL, such that the number of target options learned at any time t is maximized:{a mathematical formula} under the constraints,{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Constraint (1) requires that the abstraction-output components have zero mean and unit variance. This constraint enables the abstractions to be non-zero and avoids learning features for constant observation streams. Constraint (2) requires a unique abstraction be learned that encodes at least one of the input observation streams, avoiding redundancy. Constraint (3) imposes a total-ordering induced by Ω on the abstractions learned. Easier-to-learn observation streams are encoded first. And finally, Constraint (4) requires that each target-option's policy maximizes sensitivity, determined by the variance of the observed abstraction outputs [74]. In the rest of the paper, we interchangeably use the word skill to denote a learned target option {a mathematical formula}OiL and a skill-set to denote the target-option set {a mathematical formula}OL.
       </paragraph>
       <section>
        <section-title>
         Optimal solution
        </section-title>
        <paragraph>
         For the objective to be minimized, at any time t, the optimal solution is to learn a target option corresponding to the current easiest but not-yet-learned abstraction among the observation streams (to satisfy Constraints (1), (2), (3)) and a policy that maximizes the variance in the encoded abstraction output (to satisfy Constraint (4)).
        </paragraph>
        <paragraph>
         However, since Ω (see Constraint (3)) is not known a priori, it needs to be estimated online by actively exploring the input exploratory options over time. One possible approach is to find (a) an analytical expression{sup:2} of Ω for the particular abstraction-estimator Θ and (b) an observation stream selection technique that can estimate the Ω values for each observation stream. This approach would be dependent on the abstraction-estimator used. However, our proposed framework employs an abstraction-estimator independent approach by making use of reinforcement learning to estimate the Ω values, in the form of curiosity rewards generated through the learning progress made by Θ.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Continual curiosity-driven skill acquisition
      </section-title>
      <paragraph>
       In the above formulation, the agent has a fixed set of {a mathematical formula}n(≥1) input exploratory options. Therefore, the number of learnable target options is equal to the total number of learnable abstractions, which is at most equal to the number of input exploratory options:{a mathematical formula} To enable continual learning[29], the number of skills acquired by the agent should not necessarily be bounded and the agent needs to reuse the previously acquired skills to learn more complex skills. Therefore, continual curiosity-driven skill acquisition learning problem is a slightly modified version of the above formulation, such that the target options learned form a basis for new input exploratory options:{a mathematical formula} where {a mathematical formula}F(.) denotes some functional variation of a deterministic target option to make it stochastic (exploratory). Therefore, the number of input exploratory options (n) increases whenever a new skill is acquired by the agent.
      </paragraph>
      <section>
       <section-title>
        Sub-target options
       </section-title>
       <paragraph>
        Constraint (4) requires that each target-option's policy maximizes variance of the observed J-dimensional abstraction outputs. However in principle, the constraint can be re-written such that only a subset of J dimensions of the abstraction can be used to learn a policy. This results in a maximum number of {a mathematical formula}2J−1 learnable policies. We denote a set of target options that all share the same abstraction {a mathematical formula}{〈IiL,βiL,ϕi,πijL〉;j≤(2J−1)} as sub-target options. To keep it simple however, in the rest of the paper we use all the J dimensions, as presented in Constraint (4), to learn the target-option's policy and therefore limiting 1 target option for each learned abstraction.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Continual curiosity-driven skill acquisition (CCSA) framework
     </section-title>
     <paragraph>
      Section 3 presented an overview of our proposed framework. Here, we discuss each part of the framework in detail and also show how it addresses the learning problem formalized in Section 4.
     </paragraph>
     <section label="5.1">
      <section-title>
       Input exploratory options
      </section-title>
      <paragraph>
       As discussed in Section 4, we defined a set of input exploratory options that the agent can execute to interact with the environment. Here, we present details on how to construct these options.
      </paragraph>
      <paragraph>
       The simplest exploratory-option policy is a random walk. However, we present here a more sophisticated variant that uses a form of initial artificial curiosity, based on error-based rewards[22]. This exploratory-option's policy {a mathematical formula}πe is determined by the predictability of the observations {a mathematical formula}x(t), but can also switch to a random walk when the environment is too unpredictable.
      </paragraph>
      <paragraph>
       This policy {a mathematical formula}πe has two phases. If the estimation error of any already learned abstraction modules for the incoming observations is lower than threshold δ, the exploratory-option's policy is learned using Least-Squares Policy Iteration Technique (LSPI; [53]), with an estimation of the transition model actively updated over the option's state-space {a mathematical formula}Iie⊆SΦ, and an estimated reward function that rewards high estimation errors. Such a policy encourages the agent to explore its “unseen world” (Fig. 4(a)). But if the estimation error of already learned abstraction modules is higher than the threshold δ, then the exploratory-option's policy is a random-walk over the option's state-space. Fig. 4 illustrates this error seeking exploratory-option's policy. We denote this policy as LSPI-Exploration policy. When the agent selects an exploratory option {a mathematical formula}Oie to execute, it follows the option's policy, generating an observation stream {a mathematical formula}xi=U(P(s,πie(sΦ))), until the termination condition is met. To keep it general and non-specific to the environment, in all our experiments, each exploratory-option's termination condition is such that the option terminates after a fixed τ time-steps since its execution.
      </paragraph>
      <paragraph>
       Setting a different input exploratory-option set would influence the skills developed by CCSA. In our experiments at {a mathematical formula}t=0, the agent starts with only a single exploratory option as defined above. The LSPI-Exploration policy only speeds up the agent's exploration by acting deterministically in the predictable world and randomly in unseen world. Since at {a mathematical formula}t=0 the world is unexplored, LSPI-Exploration policy is just a random walk in the agent's abstracted states. Environment or domain specific information can be used to design the input exploratory-option set in order to shape the resulting skills. For example, exploratory options with random-walk policies mapped to different sub-regions in the robot's joint space can be used.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Curiosity-driven abstraction learning: Curious Dr. MISFA
      </section-title>
      <paragraph>
       At the core of the CCSA framework is the Curiosity Driven Modular Incremental Slow Feature Analysis Algorithm (Curious Dr. MISFA; [47], [48]).{sup:3} The order in which skills are acquired in the CCSA framework is a direct consequence of the order in which the abstractions are learned by the Curious Dr. MISFA algorithm. The input to the Curious Dr. MISFA algorithm is a set of high-dimensional observation streams {a mathematical formula}X={x1,…,xn:xi(t)∈RI,I∈N}, generated by the input exploratory-option's policies. The result is a slow feature abstraction {a mathematical formula}ϕi corresponding to the easiest yet unknown observation stream. Apart from learning the abstraction, the learning process also involves selecting the observation stream that is the easiest to encode. To this end, Curious Dr. MISFA uses reinforcement learning to learn an optimal observation-stream selection policy, based on the intrinsic rewards proportional to the progress made while learning the abstraction. In this section, we briefly review the architecture of Curious Dr. MISFA.
      </paragraph>
      <paragraph>
       Fig. 5 illustrates the architecture of Curious Dr. MISFA, which includes (a) a reinforcement learning (RL) agent that generates an observation-stream selection policy based on intrinsic rewards, (b) an adaptive Incremental Slow Feature Analysis coupled with Robust Online Clustering (IncSFA-ROC) module that updates an abstraction based on the incoming observations, and (c) a gating system that prevents encoding observations that have been previously encoded. The RL agent is within an internal environment that has a set of discrete states {a mathematical formula}Sint={s1int,…,snint}, equal to the number of observation streams. In each state {a mathematical formula}siint, the agent is allowed to take only one of the two actions ({a mathematical formula}Aint): stay or switch. The action stay makes the agent's state to be the same as the previous state, while switch randomly shifts the agent's state to one of the other internal states. The agent at each state {a mathematical formula}siint, receives a fixed τ time step sequence of observations (x) of the corresponding stream {a mathematical formula}xi.
      </paragraph>
      <paragraph>
       It maintains an adaptive abstraction {a mathematical formula}ϕˆ∈RI×J,ϕˆ∉Φt that updates based on the observations x via IncSFA-ROC abstraction-estimator. The agent receives intrinsic rewards proportional to the learning progress made by IncSFA-ROC. The observation stream selection policy {a mathematical formula}πint:Sint×Aint→[0,1] is learned from the intrinsic rewards and then used to select the observation stream for the next iteration, yielding new samples x. These new samples, if not encodable by previously learned abstractions, are used to update the adaptive abstraction. The updated abstraction {a mathematical formula}ϕˆ is added to the abstraction set {a mathematical formula}Φt, when the IncSFA-ROC's estimation error falls below a low threshold δ. If and when added, a new adaptive abstraction {a mathematical formula}ϕˆ is instantiated and the process continues. The rest of this section discusses more details on different parts of the Curious Dr. MISFA algorithm.
      </paragraph>
      <section>
       <section-title>
        Abstraction-estimator
       </section-title>
       <paragraph>
        Curious Dr. MISFA's abstraction estimator is the Incremental Slow Feature Analysis (IncSFA; [46]) coupled with a Robust Online Clustering (ROC; [75], [76]) algorithm. IncSFA is used to learn real-valued abstractions of the observations, while ROC is used to learn a discrete mapping between the abstraction outputs y and the agent's abstracted-state space {a mathematical formula}SΦ. In particular, each abstracted state {a mathematical formula}(sΦ∈SΦ) has an associated ROC implementation node that estimates multiple cluster centers within the slow-feature outputs.
       </paragraph>
       <paragraph>
        IncSFA is an incremental version of Slow feature analysis (SFA; [14]), which is an unsupervised learning technique that extracts features from an observation stream with the objective of maintaining an informative but slowly-changing feature response over time. SFA is concerned with the following optimization problem: Given an I-dimensional input signal {a mathematical formula}x(t)=[x1(t),…,xI(t)]T, find a set of J instantaneous real-valued functions {a mathematical formula}g(x)=[g1(x),…,gJ(x)]T, which together generate a J-dimensional output signal {a mathematical formula}y(t)=[y1(t),…,yJ(t)]T with {a mathematical formula}yj(t)=gj(x(t)), such that for each {a mathematical formula}j∈{1,…,J}{a mathematical formula} under the constraints{a mathematical formula}{a mathematical formula}{a mathematical formula} with {a mathematical formula}〈⋅〉 and {a mathematical formula}y˙ indicating temporal averaging and the derivative of y, respectively. The goal is to find instantaneous functions {a mathematical formula}gj generating different output signals that are as slowly varying as possible. The decorrelation constraint (10) ensures that different functions {a mathematical formula}gj do not code for the same features. The other constraints (8) and (9) avoid trivial constant output solutions. SFA operates on the covariance of observation derivatives, so it scales with the size of the observation vector instead of the number of states. SFA is originally realized as a batch method, requiring all data to be collected before processing. The algorithmic complexity is cubic in the input dimension I. By contrast, Incremental SFA (IncSFA) has a linear update complexity [46], and can adapt the features to new observations, achieving the slow feature objective robustly in open-ended learning environments.
       </paragraph>
       <paragraph>
        ROC is a clustering algorithm similar to an incremental K-means algorithm [77] — a set of cluster centers is maintained, and with each new input, the most similar cluster center (the winner) is adapted to become more like the input. Unlike K-means, with each input it follows the adaptation step by merging the two most similar cluster centers, and creating a new cluster center at the latest input. In this way, ROC can quickly adjust to non-stationary input distributions by directly adding a new cluster for the newest input sample, which may mark the beginning of a new input process.
       </paragraph>
      </section>
      <section>
       <section-title>
        Estimation error and curiosity reward
       </section-title>
       <paragraph>
        Each ROC-Estimator node j has an associated error {a mathematical formula}ξj. These errors are initialized to 0 and then updated whenever the node is activated by: {a mathematical formula}ξj(t)=minw⁡‖y(t)−vw‖, where {a mathematical formula}y(t) is the slow-feature output vector, {a mathematical formula}vw is the estimate of the wth cluster of the activated node and {a mathematical formula}‖.‖ represents {a mathematical formula}L2 norm. The total estimation error is calculated as the sum of stored errors of the nodes: {a mathematical formula}ξ(t)=∑j=1pξj(t). The agent receives rewards proportional to the derivative of the total estimation error, which motivates it to continue executing an option that is yielding a meaningful learnable abstraction. The agent's reward function is computed at every iteration from the curiosity rewards ({a mathematical formula}ξ˙) as follows:{a mathematical formula} where {a mathematical formula}0&lt;η&lt;1 is a discount factor, τ is the duration of the current option until its termination, {a mathematical formula}(sint,s−int)∈Sint and {a mathematical formula}aint∈{stay,switch}.
       </paragraph>
      </section>
      <section>
       <section-title>
        Observation-stream selection policy
       </section-title>
       <paragraph>
        The transition-probability model {a mathematical formula}Pint of the internal environment is similar to a complete graph and is given by:{a mathematical formula}{a mathematical formula}∀i,j∈[1,…,N]. Using the current updated model of the reward function {a mathematical formula}Rint and the internal-state transition-probability model {a mathematical formula}Pint, we use model-based Least Squares Policy Iteration [53] to generate the agent's internal-policy {a mathematical formula}πint:Sint→{stay,switch} for the next iteration. The agent uses decaying ϵ-greedy strategy [5] over the internal policy to carry out an internal-action (stay or switch) for the next iteration.
       </paragraph>
      </section>
      <section>
       <section-title>
        Module freezing and new module creation
       </section-title>
       <paragraph>
        Once the adaptive (training) module's {a mathematical formula}ϕˆ estimation error gets lower than a threshold δ, the agent freezes and saves the IncSFA-ROC module, resets the ϵ-greedy value and starts training a new module.
       </paragraph>
      </section>
      <section>
       <section-title>
        Gating system and abstraction assignment
       </section-title>
       <paragraph>
        The already trained (frozen) modules represent our learned library of abstractions {a mathematical formula}Φt. If a trained module's estimation error within an option is below the threshold δ, that option is assigned that module's abstraction and the adaptive training module {a mathematical formula}ϕˆ will be prevented from learning via a “gating signal” (see Fig. 5). There will no intrinsic reward in this case. Hence the training module {a mathematical formula}ϕˆ will encode only data from observation streams that were not encoded earlier. Input badly encoded by all other trained modules serve to train the adaptive module.
       </paragraph>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Learning a target option
      </section-title>
      <paragraph>
       From the set of observations streams generated by the input exploratory options, Curious Dr. MISFA learns a slow feature abstraction (say {a mathematical formula}ϕi) corresponding to the estimated easiest-yet-unlearned exploratory option stream (say {a mathematical formula}xj). The abstraction's output stream {a mathematical formula}yi=ϕi(xj) has a zero-mean and unit-variance over time [46], and is a lower-dimensional representation of the input {a mathematical formula}xj (satisfies Constraint (1); see Section 4.1.2). The output values {a mathematical formula}yi(t) are discretized to a set of abstraction states {a mathematical formula}SϕiΦ, which represent the newly discovered abstracted states of the agent. A deterministic target option is then constructed as follows:
      </paragraph>
      <section>
       Initiation set ({a mathematical formula}IL)
       <paragraph>
        The initiation set is simply the product state-space: {a mathematical formula}IiL=(Ije×SϕiΦ). Therefore, the option is now defined over a larger abstracted-state space that includes the newly discovered abstraction states.
       </paragraph>
      </section>
      <section>
       Target option policy ({a mathematical formula}πL)
       <paragraph>
        The target option policy {a mathematical formula}πiL:IiL→A must be done in such a way as to satisfy Constraint (4). To this end, we use Model-based Least-Squares Policy Iteration Technique (LSPI; [53]) over an estimated transition and reward models. The target-option's transition model {a mathematical formula}POiL has been continually estimated from the {a mathematical formula}(sΦ,a,s−Φ) samples generated via the exploratory-option's policy {a mathematical formula}πje. As to estimate the reward function, the agent uses rewards proportional to the difference of subsequent abstraction activations:{a mathematical formula}{a mathematical formula} where {a mathematical formula}yi(t)=ϕi(U(P(s−,πje(s−Φ)))) and {a mathematical formula}yi(t−1)=ϕi(U(P(s,πje(sΦ)))), {a mathematical formula}s− and s are the corresponding environment states, {a mathematical formula}P is the unknown transition-model of the environment. {a mathematical formula}0&lt;α&lt;1 is a constant smoothing factor. Once the estimated transition and reward models stabilize, LSPI follows the RL objective and learns a policy {a mathematical formula}πiL that maximizes the expected cumulative reward over time:{a mathematical formula} where γ is a discount factor close to 1. Therefore, {a mathematical formula}πiL maximizes the average activation differences, which is equivalent to maximizing variance of the activations [78] (approximately{sup:4} satisfying Constraint (4)).
       </paragraph>
      </section>
      <section>
       Termination condition ({a mathematical formula}βL)
       <paragraph>
        The option terminates whenever the agent reaches the abstracted-state where it observes the maximum reward {a mathematical formula}max(s,a)⁡ROiL.
       </paragraph>
       <paragraph>
        Each target option learned is added to the target-option set {a mathematical formula}OL and the learning process iterates until all the learnable exploratory option streams are encoded. Since the expected behavior of Curious Dr. MISFA ensures that the Constraints (1), (2), (3) are satisfied [47] and the learned target-option's policy satisfies Constraint (4), the target-option set {a mathematical formula}OL, at any time t, therefore satisfies the required constraints.
       </paragraph>
       <paragraph>
        In Section 4, we discussed an alternative to Constraint (4), where different dimensions of the learned abstraction may be used to learn multiple policies, resulting in a set of sub-target options. To keep it simple, we used all dimensions of an abstraction to learn a target-option's policy. However, a sub-target option set can be constructed by following the approach discussed above. Multiple reward functions can simultaneously be estimated from the {a mathematical formula}(sΦ,a,s−Φ) samples generated via exploratory-option's policy, and the set of sub-target options can be constructed via least-squares policy iteration in parallel.
       </paragraph>
      </section>
     </section>
     <section label="5.4">
      <section-title>
       Reusing target options
      </section-title>
      <paragraph>
       To make the skill acquisition open-ended and to acquire more complex skills (see Section 4.2), the learned target option {a mathematical formula}OL can be used to explore the newly discovered abstracted-state space (see Section 5.3). However, a target option may not be reused straight-away, since by definition, it differs from an exploratory option, wherein the target-option's policy is deterministic, while the exploratory-option's policy is stochastic (see Section 5.1). We construct two new exploratory options instead, which are based on the target option {a mathematical formula}OiL that was learned last (see Fig. 6).
      </paragraph>
      <paragraph>
       In the first option, called policy chunk and explore, the initiation-set is the same as that of learned target option {a mathematical formula}In+1e=IiL. The policy combines the target-option's policy {a mathematical formula}πiL, which terminates at the state where the variance of subsequent encoded observations is highest, with the LSPI-Exploration policy described in Section 5.1. Every time this policy is initiated, the policy-chunk (A policy chunk is a non-adaptive frozen policy) {a mathematical formula}πiL is executed, followed by the LSPI-Exploration policy. This can be beneficial if the target option terminates at a bottleneck state, after which the agent enters a “new world” of experience, within which the LSPI-Exploration policy is useful to explore.
      </paragraph>
      <paragraph>
       In the second option, called biased initialization and explore, the exploratory-option's policy uses the normalized value function of the target option as an initial reward function estimate. This initialization biases the agent to explore first the state-action tuples where it had previously received maximum intrinsic rewards. Otherwise it is the same as the standard initial error-seeking LSPI-Exploration policy.
      </paragraph>
      <paragraph>
       For each target option learned, these two exploratory options are added to the input exploratory-option set. In this way, the agent continues the process of curiosity-based skill acquisition by exploring among the new exploratory option set to discover unknown regularities. A complex skill {a mathematical formula}OkL=〈IkL,βkL,ϕk,πkL〉 can be learned as a consequence of chaining multiple skills that were learned earlier.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Pseudocode
      </section-title>
      <paragraph>
       The entire learning process involves determining three policies:
      </paragraph>
      <paragraph>
       1. {a mathematical formula}πe: Exploratory-option's stochastic policy that is determined (see Section 5.1) to generate high-dimensional observations.
      </paragraph>
      <paragraph>
       2. {a mathematical formula}πint: An internal policy that is learned (see Section 5.2) to determine for which exploratory option {a mathematical formula}Oe to encode a slow feature abstraction.
      </paragraph>
      <paragraph>
       3. {a mathematical formula}πL: Target-option's deterministic policy that is learned (see Section 5.3) to maximize variation in the slow feature abstraction output.
      </paragraph>
      <paragraph>
       The resultant target options (skills) are stored and reused as discussed above to facilitate open-ended continual learning. Algorithm 1, Algorithm 2 summarize the entire learning process.{sup:5}
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      We present here experimental results that focus on continual-learning of skills using an iCub humanoid platform. More studies on the types of representations learned by the IncSFA algorithm and curiosity-based abstraction learning with Curious Dr. MISFA can be found elsewhere [47], [48], [46], [68]. The results here are the first in which a humanoid robot such as an iCub, learns a repertoire of skills from raw-pixel data in an online manner, driven by its own curiosity, starting with low-level joint kinematic maps.{sup:6}
     </paragraph>
     <paragraph>
      Learning a skill-set largely depends on the environment that the robot is in. For the sake of developing specific types of skills such as toppling an object, grasping, etc., we pre-selected a safe environment for the iCub to explore, yet the iCub is mostly unaware of the environment properties.
     </paragraph>
     <paragraph label="Environment">
      Our iCub robot is placed next to a table, with an object (a plastic cup) in reach of its right arm and within its field-of-view (Fig. 7(a)). The cup topples over upon contact, and the resulting images after toppling are predictable. There is a human experimenter present, who monitors the robot's safety and replaces the cup in its original position after it is toppled. The iCub does not “know” that the plastic-cup and the experimenter exist. It continually observes the gray-scale pixel values from the high-dimensional images ({a mathematical formula}75×100) captured by the left and right camera eyes (Fig. 7(b)). In addition to the experimenter and the cup, it also cannot recognize its own moving hand in the incoming image stream, as shown in Fig. 7(b).
     </paragraph>
     <paragraph label="Task-relevant roadmap">
      <paragraph>
       We do not induce exploration at the level of joint angles, due to the complexity of the robot's joint space. Instead we give the robot a map of poses a priori. This compressed actuator joint-space representation is called a Task-Relevant Roadmap (TRM; [50]). This map contains a family of iCub postures that adhere to relevant constraints. The TRM is grown offline by repeatedly optimizing cost-functions that represent the constraints, using a Natural Evolution Strategies (NES; [79]) algorithm, such that the task-space is covered. This allows us to deal with complex cost-functions and the full 41 degrees-of-freedom of the iCub's upper body. The constraints used: (a) the iCub's hand is positioned on a 2D plane parallel to the table while keeping its palm oriented horizontally, (b) the left hand is kept within a certain region to keep it out of the way, and (c) the head is pointed towards the table. The task-space of the TRM comprises the x and y position of the hand, which forms the initial discretized {a mathematical formula}10×5 abstracted-state space {a mathematical formula}SΦ=SxΦ×SyΦ. The action space contains 6 actions: move North, East, South, West, Hand-close and Hand-open.
      </paragraph>
      <paragraph>
       Because the full body is used, the movements look more dynamic, but as a consequence, the head moves around and looks at the table from different directions, making the task a bit more difficult. Even so, IncSFA still finds the resulting regularities in the raw camera observation stream, and the skill learner continues to learn upon these regularities, without any external rewards.
      </paragraph>
     </paragraph>
     <paragraph label="Experiment parameters">
      We use a fixed parameter setting for the entire experiment.
     </paragraph>
     <paragraph label="IncSFA algorithm">
      IncSFA has two learning update rules [46]: Candid-Covariance free Incremental Principal Component Analysis (CCIPCA; [80]) for normalizing the input and Minor Component Analysis (MCA; [81]) for extracting slow features. For CCIPCA, we use learning rates {a mathematical formula}1/t with amnesic parameter 0.4, while for MCA the learning rate is set to 0.01. CCIPCA does variable size dimension reduction by calculating how many eigenvalues would be needed to keep {a mathematical formula}99% of the input variance — typically this was between {a mathematical formula}5–10 — so the 7500 pixels could be effectively reduced to only about 10 dimensions. The output dimension is set to 1, therefore, we use only the first IncSFA feature as an abstraction. However, more number of features can be used if desired.
     </paragraph>
     <paragraph label="Robust online clustering (ROC) algorithm">
      ROC algorithm maps slow-feature outputs to abstracted states (see Section 5.2). Each clustering implementation has its maximum number of clusters set to {a mathematical formula}Nmax=3, such that it can encode multiple slow feature values for each abstracted state. Higher values can be used, however, very high values may lead to spurious clusters. The estimation error threshold, below which the current module is saved and a new module is created, is set to a low value {a mathematical formula}δ=0.3. The amnesic parameter is set to {a mathematical formula}βamn=0.01. Higher values will make ROC adapt faster to the new data, however at the cost of being less stable.
     </paragraph>
     <paragraph label="Curious Dr. MISFA's internal reinforcement learner">
      To balance between exploration and exploitation, ϵ-greedy strategy is used (see Section 5.2). The initial ϵ-greedy value is set to 1.0 (1.0 for pure exploration, 0.0 for pure exploitation), with a 0.995 decay multiplier. The window-averaging time constant is set to {a mathematical formula}τ=20, that is, 20 sample images are used to compute the window-averaged progress error ξ and the corresponding curiosity-reward (see Section 5.2).
     </paragraph>
     <paragraph label="Target-option's reinforcement learner">
      Slow features abstractions have unit-variance and are typically in the range of {a mathematical formula}(−1.5,1.5)[46]. Since in our experiments we are expecting step-like slow features, to keep it simple, each abstraction-output values are discretized to either {a mathematical formula}(−1,1), therefore into two {a mathematical formula}|Sϕi|=2 abstracted states.
     </paragraph>
     <paragraph label="Experiment initialization">
      The iCub's abstracted-state space ({a mathematical formula}SΦ) at {a mathematical formula}t=0 is a {a mathematical formula}10×5 grid found using TRM. To minimize human input into the system, the input exploratory-option set ({a mathematical formula}Oe) has only one exploratory option to begin with (as defined in Section 5.1): {a mathematical formula}Oe={O1e}, which is a random-walk in the iCub's abstracted-state space. However, one may pre-define multiple input exploratory options, which could lead to a different result. The exploratory option terminates after {a mathematical formula}τ=20 time steps since its execution. The internal state-space at {a mathematical formula}t=0 is {a mathematical formula}Sint={s1int}, where {a mathematical formula}s1int corresponds to the exploratory option {a mathematical formula}O1e. The plastic cup is roughly placed around {a mathematical formula}(2,2) grid-point on the table.
     </paragraph>
     <section label="6.1">
      <section-title>
       iCub learns to topple the cup
      </section-title>
      <paragraph>
       The iCub starts the experiment without any learned modules, so the exploratory-option's policy {a mathematical formula}π1e is a random-walk over the abstracted state space {a mathematical formula}SΦ (see Section 5.4). It explores by taking one of the six actions: North, East, South, West, Hand-close and Hand-open and grabs high-dimensional images from its camera-eyes. The exploration causes the outstretched hand to eventually displace or topple the plastic-cup placed on the table. It continues to explore and after an arbitrary amount of time-steps the experimenter replaces the cup to its original position. After every τ time-steps, the currently executing option terminates. Since there is only one exploratory option, the iCub re-executes the same option. Fig. 8(a) shows a sample input image stream of only the left-camera.{sup:7}
      </paragraph>
      <paragraph>
       Fig. 8(b) shows the developing IncSFA output over the algorithm execution time, since the IncSFA abstraction was created. The outcome of IncSFA abstraction learning is a step-like function, which when discretized, indicates the pose of the cup (toppled vs non-toppled). Fig. 8(c) shows the ROC estimation error (blue solid line) and an Expected Moving Average (EMA) of the error (green dashed line) over the algorithm execution time. As the process continues, the error eventually drops below the threshold {a mathematical formula}δ=0.3 and the abstraction module {a mathematical formula}ϕ1 is saved. Fig. 9(a) shows the ROC cluster centers that map the feature outputs {a mathematical formula}(y) to each of the {a mathematical formula}10×5 abstracted states. There are two well separated clusters each representing the state of the plastic-cup.
      </paragraph>
      <paragraph>
       Immediately after the abstraction is saved, the cluster centers are discretized (red and yellow colors indicate the discretized feature states {a mathematical formula}Sϕ1Φ in Fig. 9(a)), the transition model (represented by the blue lines in Fig. 9(a)) and reward model of {a mathematical formula}O1L are learned, followed by a corresponding target-option's policy {a mathematical formula}π1L as discussed in Section 5.3. Fig. 9(b) shows a part of the learned policy {a mathematical formula}π1L before the cup is toppled. The arrows indicate the optimal action to be taken at each grid-location of the iCub's hand. They direct the iCub's hand to the grid point {a mathematical formula}(1,3), which will make the iCub topple the cup placed at {a mathematical formula}(2,2). Fig. 9(c) shows the part of the policy after the cup has been toppled. The policy directs the iCub's hand to move towards east. This is because, during the experiment the experimenter happened to replace the cup only when the iCub's hand is around far east. We label the learned target option {a mathematical formula}O1L, for the given environment, as a “Topple” skill.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       iCub learns to grasp the cup
      </section-title>
      <paragraph>
       The iCub continues its learning process by reusing the learned topple skill to construct two additional exploratory options as discussed in Section 5.4. One in which the topple policy (Fig. 9(b)) is executed prior to the LSPI-Exploration policy and the other, where the normalized value function (Fig. 10(b)) is used to initialize the reward-function of the LSPI-Explorer. Let {a mathematical formula}O2e and {a mathematical formula}O3e denote these two exploratory options respectively. Therefore, including the original exploratory option {a mathematical formula}O1e, a total of 3 exploratory options are an input to CCSA.
      </paragraph>
      <paragraph>
       Initially, the system explores by executing each of the options until termination, i.e., after τ time steps. When it selects either {a mathematical formula}O1e or {a mathematical formula}O2e, the cup gets toppled in the process (Fig. 10(a)-Top) and since there already exists a learned abstraction {a mathematical formula}ϕ1 that encodes the toppling outcome, it receives no internal reward for executing these options because of the gating system (see Section 5.2). This is also the case in the beginning while executing {a mathematical formula}O2e, because the LSPI-Exploration policy initially causes the iCub to topple the cup, yielding no rewards. The initialized values corresponding to the visited state-action tuples soon vanish and the iCub then explores the neighboring state action pairs. Eventually, as a result of the biased exploration, in a few algorithm iterations the iCub ends up grasping the cup (Fig. 10(a)-Bottom). This gives rise to a high estimation error because of the novelty of the event (Fig. 10(c)). Figs. 10(d)–(i) show the state-action LSPI-Exploration reward function after a few time steps. The hand-close action at {a mathematical formula}(2,2) generates the most novel event. This results in a LSPI-Exploration policy that increases the number of successful grasp trials (77 out of 91 total attempts, with most of the unsuccessful trials in the beginning) when the exploratory option {a mathematical formula}O3e is executed.
      </paragraph>
      <paragraph>
       Now, upon executing option {a mathematical formula}O3e, the adaptive abstraction {a mathematical formula}ϕˆ begins to make progress by encoding samples corresponding to the observation stream {a mathematical formula}x3. After a few algorithm iterations, the agent finds that the action stay at the internal state {a mathematical formula}s3int corresponding to the {a mathematical formula}O3e is rewarding due to the progress made by IncSFA and the ROC estimator (Fig. 11(a)). Fig. 11(b) shows the normalized internal reward function of Curious Dr. MISFA over algorithm iterations, since the new adaptive module was created. The internal policy {a mathematical formula}πint quickly converges to select and execute the option {a mathematical formula}O3e to receive more observations. When the estimation error drops below the threshold ({a mathematical formula}δ=0.3), it saves the module {a mathematical formula}ϕ2=ϕˆ. Fig. 11(c) shows the IncSFA output over the time since the new module was created. Fig. 11(d) shows the learned cluster centers mapping the slow-feature output to the abstracted-state space. Note that the abstracted states corresponding to the learned topple abstraction {a mathematical formula}Sϕ1Φ and not are shown in Fig. 11(d), because the grasp abstraction outputs are uncorrelated to the topple abstraction and it is difficult to illustrate a 4-D plot. The iCub then begins to learn the target policy {a mathematical formula}π2L by learning the target-option's transition and reward model. Fig. 12(a)–(f) show the target-option's state-action reward model developed after 8000 observation samples (module time = 8000). And finally, Fig. 12(g) shows the corresponding skill learned, i.e., to perform a Hand-Close at {a mathematical formula}(2,2) (the anti clockwise circular arrow represents the Hand Close action).
      </paragraph>
      <paragraph>
       This experiment demonstrated how the iCub reused the knowledge gained by the topple skill to learn a subsequent skill labeled as “Grasp”. The grasp skill includes an abstraction to represent whether the cup has been successfully grasped-or-not and a policy that directs the iCub's hand to move to {a mathematical formula}(2,2) and then to close its hand.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       iCub learns to pick and place the cup at the desired location
      </section-title>
      <paragraph>
       We present here an experiment to demonstrate the utility of intrinsic motivation in solving a subsequent external objective (see Fig. 13). The iCub is in a similar environment as discussed above. However, it is given an external reward if it picks the plastic cup and places (drops) it at a desired location (at any of the following grid locations {a mathematical formula}(sxΦ,syΦ): {a mathematical formula}(6,2),(6,3),(6,1),(5,2),(7,2)). The agent with no intrinsic motivation finds the reward almost inaccessible via random exploration over its abstracted-state space {a mathematical formula}SΦ, because the probability of a successful trial is low.{sup:8}{a mathematical formula}(≈10−5) However, a curiosity driven iCub greatly improves this by learning to pick/grasp the cup by itself and then reusing the skill to access the reward.
      </paragraph>
      <paragraph>
       Starting from the {a mathematical formula}10×5 abstracted-state space found via TRM, the iCub learns to topple and then grasp as discussed in the previous sections. The process continues and it adds two more exploratory options {a mathematical formula}(O4e,O5e) corresponding to the grasp skill as discussed in Section 5.4. The biased initialization and explore option {a mathematical formula}O4e results in the iCub dropping the cup close to where it has picked it up. Since it doesn't get any reward in this case, the initialized values to the visited state-actions tuples vanish and it explores the neighboring state-action tuples. This option will take a long time before it can execute the desired state-action tuple to drop the cup. The policy chunk and explore option {a mathematical formula}O5e, however, first executes the grasp policy and then randomly explores until it receives some novelty or curiosity reward. When, it drops the cup in one of the desired states while exploring, it gets an external reward, which results in a LSPI-Exploration policy that executes the rewarding behavior. Curious Dr. MISFA eventually finds the internal action stay at the internal-state {a mathematical formula}s5int corresponding to the option {a mathematical formula}O5e most rewarding. As soon as the experimenter replaces the cup, the iCub repeats the pick and place behavior until the external reward is removed.
      </paragraph>
      <paragraph>
       This experiment demonstrated how CCSA enabled the iCub to reuse the grasp skill, which was previously learned via intrinsic motivation, on learning to pick and place the cup to a desired location. Note that in our experiments, a human experimenter unknown to the robot, acted as a part of the environment to speed up the learning process. Without the experimenter, the robot might not have acquired the same set of skills, instead it might have learned to push the object (refer to our previous work [48] for an experiment where a simulated iCub learns a slow feature abstraction that encodes a push).
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      While, much of the research in humanoid robot learning has been based upon human demonstrations, human-given task-descriptions, or pre-processed inputs, CCSA makes an important step towards combining several aspects needed to develop an online, continual curiosity-driven humanoid robotic agent. In the following we briefly discuss these aspects along with current limitations of our framework and insights for future work:
     </paragraph>
     <section>
      <section-title>
       Raw high-dimensional information processing
      </section-title>
      <paragraph>
       CCSA uses a linear IncSFA algorithm updated online directly from raw-pixels to encode abstractions that lead to acquiring skills. To learn more complex skills however, CCSA might benefit from extracting non-linearities in the video inputs. Hierarchical extensions of IncSFA (H-IncSFA) over an expanded input in quadratic space [82] may remedy this. We plan to combine non-linear hierarchical structures to further improve the quality of the abstractions learned.
      </paragraph>
     </section>
     <section>
      <section-title>
       Invariant skills
      </section-title>
      <paragraph>
       The skill labeled “grasp” in our experiments actually represents “grasp the cylindrical cup from the particular location in the given environment, invariant to the experimenter's actions and the iCub's head/body movements”. The invariance picked up by the skills acquired in our system largely depend on the invariance learned by IncSFA from the observations sensed by the exploring iCub. Refer to our previous work [47], [46] for more details on invariance extracted by IncSFA. In our experiments however, if the human experimenter had replaced the cup at different locations whenever the cup was toppled or dropped, we expect IncSFA to learn an abstraction that encodes whether the cup has been grasped-or-not invariant to the cup's position (because the events are uncorrelated). This would result in a “grasp skill” that is invariant to the cup's position.
      </paragraph>
     </section>
     <section>
      <section-title>
       Continual learning
      </section-title>
      <paragraph>
       CCSA uses previously acquired knowledge in the form of biased explorations or policy-chunks, to learn more complex skills. This facilitates continual learning of skills. A previously acquired skill may be refined or adapted to suit to changing environments. For example, in our experiments, if the cup's position has changed after acquiring the grasp skill, the biased init. and explore exploratory-option corresponding to the grasp skill can speed up learning a new skill to grasp the cup from the new position. However, the old skills are still retained and reused if the cup's position is changed back to its original position. The complex skills acquired using CCSA are in the form of a chain-like hierarchy (Fig. 14(a)), i.e., there exists only a single chain-link connecting higher-order to lower-order skills. This is because, a target option in CCSA is learned using observations only from one of the exploratory options (see Section 4). Each node in the chain-like hierarchy has only a single input but can act as an input to many nodes (Fig. 14(b)). Whereas, a node in a general compositional hierarchy (Fig. 14(c)) can have multiple inputs. One way to achieve compositional hierarchy in CCSA is to add the learned target options to the primitive action set {a mathematical formula}A={North, East, South, West, Hand-close and Hand-open}.
      </paragraph>
     </section>
     <section>
      <section-title>
       Environment openness
      </section-title>
      <paragraph>
       CCSA could benefit from a larger set of pre-defined input exploratory options. However, to minimize human inputs into the system, in our experiments the iCub starts with only a single exploratory option (random-walk) and autonomously adds more exploratory options derived from the learned target options. Since CCSA acts directly on raw-pixels, no prior calibration of the robot cameras are required. Algorithm parameters are intuitive to tune. Refer to our previous work [47], [48], [46], [68] for a detailed description on tuning IncSFA and Curious Dr. MISFA algorithms. Therefore, CCSA can be used in different environments (and different humanoid robots) without making any design changes to the learning algorithm. On the motor end, we used a kinematic map that transforms the 41 degrees-of-freedom of the iCub joint configurations to 2D positions of its hand parallel to the table. For more complex manipulations, which are required for handling complicated objects, higher dimensional kinematic-maps could be used [50]. As our future work, we plan on using different approaches to tackle easier and safer manipulation with the iCub.
      </paragraph>
     </section>
     <section>
      <section-title>
       Quality of skills acquired
      </section-title>
      <paragraph>
       We presented formally the underlying learning problem as a constrained optimization problem. The objective function can be used as a metric to tune different parameters of the method. However, the metric does not sufficiently evaluate the quality of skills acquired. One major factor is the type of the abstraction-estimator used. For example, a method that uses a simpler abstraction learning algorithm may acquire a large number of skills, which could be functionally equivalent to acquiring a single skill of a more discriminative abstraction estimator. Therefore, evaluating different task-unrelated intrinsically-motivated (IM) approaches without providing an external goal is an ill-posed problem. As our future work, we plan to build realistic, task-independent, skill-acquisition benchmarks with hidden external tasks to evaluate multiple IM approaches.
      </paragraph>
     </section>
     <section>
      <section-title>
       Scalability
      </section-title>
      <paragraph>
       For each target option acquired by CCSA, the number of input exploratory options increases by a value of two (See Section 5.4). Observations from previously encoded exploratory options are automatically filtered out due to the gating system of Curious Dr. MISFA. Therefore, for each target option acquired, the number of unknown exploratory options increases by a value of only one. Hence, the space of input exploratory options scales linearly with respect to the number of skills acquired.
      </paragraph>
     </section>
     <section>
      <section-title>
       Sensor fusion
      </section-title>
      <paragraph>
       And finally, CCSA uses only visual inputs from the onboard cameras and joint angles of the iCub. A humanoid-robot's actions can be improved however, by using different sensory modalities such as tactile and audio in addition to the visual inputs. This should be straightforward addition to CCSA, since IncSFA is agnostic to the modality of sensory information. The raw inputs of different modalities can be concatenated as a single input and fed to the IncSFA algorithm, without causing too much computational overhead (since IncSFA has a linear update complexity [46]). Related work on combining sensory modalities using SFA methods have shown to achieve good results [83].
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>