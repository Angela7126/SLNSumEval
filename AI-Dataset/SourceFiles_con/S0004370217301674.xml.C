<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Decentralized Reinforcement Learning of Robot Behaviors.
   </title>
   <abstract>
    A multi-agent methodology is proposed for Decentralized Reinforcement Learning (DRL) of individual behaviors in problems where multi-dimensional action spaces are involved. When using this methodology, sub-tasks are learned in parallel by individual agents working toward a common goal. In addition to proposing this methodology, three specific multi agent DRL approaches are considered: DRL-Independent, DRL Cooperative-Adaptive (CA), and DRL-Lenient. These approaches are validated and analyzed with an extensive empirical study using four different problems: 3D Mountain Car, SCARA Real-Time Trajectory Generation, Ball-Dribbling in humanoid soccer robotics, and Ball-Pushing using differential drive robots. The experimental validation provides evidence that DRL implementations show better performances and faster learning times than their centralized counterparts, while using less computational resources. DRL-Lenient and DRL-CA algorithms achieve the best final performances for the four tested problems, outperforming their DRL-Independent counterparts. Furthermore, the benefits of the DRL-Lenient and DRL-CA are more noticeable when the problem complexity increases and the centralized scheme becomes intractable given the available computational resources and training time.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Reinforcement Learning (RL) is commonly used in robotics to learn complex behaviors [43]. However, many real-world applications feature multi-dimensional action spaces, i.e. multiple actuators or effectors, through which the individual actions work together to make the robot perform a desired task. Examples are multi-link robotic manipulators [7], [31], mobile robots [11], [26], aerial vehicles [2], [16], multi-legged robots [47], and snake robots [45]. In such applications, RL suffers from the combinatorial explosion of complexity, which occurs when a Centralized RL (CRL) scheme is used [31]. This leads to problems in terms of memory requirements or learning time and the use of Decentralized Reinforcement Learning (DRL) helps to alleviate these problems. In this article, we will use the term DRL for decentralized approaches to the learning of a task which is performed by a single robot.
     </paragraph>
     <paragraph>
      In DRL, the learning problem is decomposed into several sub-problems, whose resources are managed separately, while working toward a common goal. In the case of multidimensional action spaces, a sub-task corresponds to controlling one particular variable. For instance, in mobile robotics, a common high-level motion command is the desired velocity vector (e.g., {a mathematical formula}[vx,vy,vθ]), and in the case of a robotic arm, it can be the joint angle setpoint (e.g., {a mathematical formula}[θshoulder,θelbow,θwrist]). If each component of this vector is controlled individually, a distributed control scheme can be applied. Through coordination of the individual learning agents, it is possible to use decentralized methods [7], taking advantage of parallel computation and other benefits of Multi-Agent Systems (MAS) [42], [5].
     </paragraph>
     <paragraph>
      In this work, a Multi-Agent (MA) methodology is proposed for modeling the DRL in problems where multi-dimensional action spaces are involved. Each sub-task (e.g., actions of one effector or actuator) is learned by a separate agent and the agents work in parallel on the task. Since most of the MAS reported studies do not validate the proposed approaches with multi-state, stochastic, and real world problems, our goal is to show empirically that the benefits of MAS are also applicable to complex problems like robotic platforms, by using DRL systems. In this paper, three Multi-Agent Learning (MAL) algorithms are considered and tested: the independent DRL, the Cooperative Adaptive (CA) Learning Rate, and a Lenient learning approach extended to multi-state DRL problems.
     </paragraph>
     <paragraph>
      The independent DRL (DRL-Ind) does not consider any kind of cooperation or coordination among the agents, applying single-agent RL methods to the MA task. The Cooperative Adaptive Learning Rate DRL (DRL-CA) and the extended Lenient DRL (DRL-Lenient) algorithms add coordination mechanisms to the independent DRL scheme. These two MAL algorithms are able to improve the performance of those DRL systems in which complex scenarios with several agents with different models or limited state space observability appear. Lenient RL was originally proposed by Panait, Sullivan, and Luke [35] for stateless MA games; we have adopted it to multi-state and stochastic DRL problems based on the work of Schuitema [39]. On the other hand, the DRL-CA algorithm uses similar ideas to those of Bowling and Veloso [3], and Kaisers and Tuyls [19] for having a variable learning rate, but we are introducing direct cooperation between agents without using joint actions information and not increasing the memory consumption or the state space dimension.
     </paragraph>
     <paragraph>
      The proposed DRL methodology and the three MAL algorithms considered are validated through an extensive empirical study. For that purpose, four different problems are modeled, implemented, and tested; two of them are well-known problems: an extended version of the Three-Dimensional Mountain Car (3DMC) [46], and a SCARA Real-Time Trajectory Generation (SCARA-RTG) [31]; and two correspond to noisy and stochastic real-world mobile robot problems: Ball-Dribbling in soccer performed with an omnidirectional biped robot [25], and the Ball-Pushing behavior performed with a differential drive robot [28].
     </paragraph>
     <paragraph>
      In summary, the main contributions of this article are threefold. First, we propose a methodology to model and implement a DRL system. Second, three MAL approaches are detailed and implemented, two of them including coordination mechanisms. These approaches, DRL-Ind, DRL-CA, and DRL-Lenient, are evaluated on the above-mentioned four problems, and conclusions about their strengths and weaknesses are drawn according to each validation problem and their characteristics. Third, to the best of our knowledge, our work is the first one that applies a decentralized modeling to the learning of individual behaviors on mobile robot platforms, and compares it with a centralized RL scheme. Further, we expect that our proposed extension of the 3DMC can be used in future work as a test-bed for DRL and multi-state MAL problems. Finally, all the source codes are shared at our code repository [23], including our custom hill-climbing algorithm for optimizing RL parameters.
     </paragraph>
     <paragraph>
      This remainder of this paper is organized as follows: Section 2 presents the preliminaries and an overview of related work. In Section 3, we propose a methodology for modeling DRL systems, and in Section 4, three MA based DRL algorithms are detailed. In Section 5, validation problems are specified and the experiments, results, and discussion are presented. Finally, Section 6 concludes the paper.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      This section introduces the main concepts and background based on the works of Sutton and Barto [43], and Busoniu, Babuska, De-Schutter, and Ernst [6] for single-agent RL; Busoniu, Babuska, and De Schutter [5], and Vlassis [52] for Multi-Agent RL (MARL); Laurent, Matignon, and Fort-Piat [22] for independent learning; and Busoniu, De-Schutter, and Babuska [7] for decentralized RL. Additionally, an overview of related work is presented.
     </paragraph>
     <section label="2.1">
      <section-title>
       Single-agent reinforcement learning
      </section-title>
      <paragraph>
       RL is a family of machine learning techniques in which an agent learns a task by directly interacting with the environment. In the single-agent RL, studied in the remainder of this article, the environment of the agent is described by a Markov Decision Process (MDP), which considers stochastic state transitions, discrete time steps {a mathematical formula}k∈N and a finite sampling period.
      </paragraph>
      <paragraph label="Definition 1">
       A finite Markov decision process is a 4-tuple {a mathematical formula}〈S,A,T,R〉 where: S is a finite set of environment states, A is a finite set of agent actions, {a mathematical formula}T:S×A×S→[0,1] is the state transition probability function, and {a mathematical formula}R:S×A×S→R is the reward function [5].
      </paragraph>
      <paragraph>
       The stochastic state transition function T models the environment. The state of the environment at discrete time-step k is denoted by {a mathematical formula}sk∈S. At each time step, the agent can take an action {a mathematical formula}ak∈A. As a result of that action, the environment changes its state from {a mathematical formula}sk to {a mathematical formula}sk+1, according {a mathematical formula}T(sk,ak,sk+1), which is the probability of ending up in {a mathematical formula}sk+1 given that action {a mathematical formula}ak is applied in {a mathematical formula}sk. As an immediate feedback on its performance, the agent receives a scalar reward {a mathematical formula}rk+1∈R, according to the reward function: {a mathematical formula}rk+1=R(sk,ak,sk+1). The behavior of the agent is described by its policy π, which specifies how the agent chooses its actions given the state.
      </paragraph>
      <paragraph>
       This work is about tasks that require several simultaneous actions (e.g., a robot with multiple actuators), where such tasks are learned by using separate agents, one for each action. In this setting, the state transition probability depends on the actions taken by all the individual agents. We consider on-line and model-free algorithms, as they are convenient for practical implementations.
      </paragraph>
      <paragraph>
       Q-Learning [53] is one of the most popular model-free, on-line learning algorithms. It turns Bellman equation into an iterative approximation procedure which updates the Q-function by the following rule:{a mathematical formula} in which {a mathematical formula}s′ and {a mathematical formula}a′ correspond to {a mathematical formula}sk+1 and {a mathematical formula}ak+1 respectively, with {a mathematical formula}α∈(0,1] the learning rate, and {a mathematical formula}γ∈(0,1) the discount factor. The sequence of Q-functions provably converges to {a mathematical formula}Q⁎ under certain conditions, including that the agent keeps trying all actions in all states with non-zero probability.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Multi-agent learning
      </section-title>
      <paragraph>
       The generalization of the MDP to the multi-agent case is the stochastic game.
      </paragraph>
      <paragraph label="Definition 2">
       A stochastic game is the tuple {a mathematical formula}〈S,A1,⋯,AM,T,R1…RM〉 with M the number of agents; S the discrete set of environment states; {a mathematical formula}Am,m=1,⋯,M the discrete sets of actions available to the agents, yielding the joint action set {a mathematical formula}A=A1×⋯×AM; {a mathematical formula}T:S×A×S→[0,1] the state transition probability function, such that, {a mathematical formula}∀s∈S,∀a∈A,∑sk+1∈ST(sk,ak,sk+1)=1; and {a mathematical formula}Rm:S×A×S→R,m=1,⋯,M the reward functions of the agents [5], [22].
      </paragraph>
      <paragraph>
       In the multi-agent case, the state transitions depend on the joint action of all the agents, {a mathematical formula}ak=[ak1,⋯,akM],ak∈A,akm∈Am. Each agent may receive a different reward {a mathematical formula}rk+1m. The policies {a mathematical formula}πm:S×Am→[0,1] form together the joint policy π. The Q-function of each agent depends on the joint action and is conditioned on the joint policy, {a mathematical formula}Qmπ:S×A→R.
      </paragraph>
      <paragraph>
       If {a mathematical formula}R1=⋯=RM, all the agents have the same goal, and the stochastic game is fully cooperative. If {a mathematical formula}M=2, {a mathematical formula}R1=−R2, and they sum-up to zero, the two agents have opposite goals, and the game is fully competitive. Mixed games are stochastic games that are neither fully cooperative nor fully competitive [52]. In the general case, the reward functions of the agents may differ. Formulating a good learning goal in situations where the agents' immediate interests are in conflict is a difficult open problem [7].
      </paragraph>
      <section label="2.2.1">
       <section-title>
        Independent learning
       </section-title>
       <paragraph>
        Claus and Boutilier [8] define two fundamental classes of agents: joint-action learners and Independent Learners (ILs). Joint-action learners are able to observe the other agents actions and rewards; those learners are easily generalized from standard single-agent RL algorithms as the process stays Markovian. On the contrary, ILs do not observe the rewards and actions of the other learners, they interact with the environment as if no other agents exist [22].
       </paragraph>
       <paragraph>
        Most MA problems violate the Markov property and are non-stationary. A process is said non-stationary if its transition probabilities change with the time. A non-stationary process can be Markovian if the evolution of their transition and reward functions depends only on the time step and not on the history of actions and states [22].
       </paragraph>
       <paragraph>
        For ILs, which is the focus of the present paper, the individual policies change as the learning progresses. Therefore, the environment is non-stationary and non-Markovian. Laurent, Matignon and Fort-Piat [22] give an overview of strategies for mitigating convergence issues in such a case. The effects of agents' non-stationarity are less observable in weakly coupled distributed systems, which makes ILs more likely to converge. The observability of the actions' effects may influence the convergence of the algorithms. To ensure convergence, these approaches require the exploration rate to decay as the learning progresses, in order to avoid too much concurrent exploration. In this way, each agent learns the best response to the behavior of the others. Another alternative is to use coordinated exploration techniques that exclude one or more actions from the agent's action space, to efficiently search in a shrinking joint action space. Both approaches reduce the exploration, the agents evolve slower and the non-Markovian effects are reduced [22].
       </paragraph>
      </section>
     </section>
     <section label="2.3">
      <section-title>
       Decentralized Reinforcement Learning
      </section-title>
      <paragraph>
       DRL is concerned with MAS and Distributed Problem Solving [42]. In DRL, a problem is decomposed into several subproblems, managing their individual information and resources in parallel and separately, by a collection of several agents which are part of a single entity, such as a robot. For instance, consider a quadcopter learning to perform a maneuver: each rotor can be considered as a subproblem rather than an entirely independent problem; each subproblem's information and resources (sensors, actuators, effectors, etc.) can be managed separately by four agents; so, four individual policies will be learned to perform the maneuver in a collaborative way.
      </paragraph>
      <paragraph>
       One of the first mentions of DRL is by Busoniu, De-Schutter, and Babuska [7], where it was used to differentiate a decentralized system from a MAL system composed of individual agents [34]. The basic DRL architecture is shown in Fig. 1 where M individual agents are interacting within an environment. According to Tuyls, Hoen, and Vanschoenwinkel [49], single-agents working on a multi-agent task are able to converge to a coordinate equilibrium under certain parameters and for some particular behaviors. In this work we validate that assumption empirically with several problems in which multi-dimensional action spaces are present. Thus, a methodology for modeling those problems by using a DRL system is a primary contribution of this work.
      </paragraph>
      <section label="2.3.1">
       <section-title>
        Potential advantages of DRL
       </section-title>
       <paragraph>
        One of the main drawbacks of classical RL is the exponential increase of complexity with the number of state variables. Moreover, problems with multi-dimensional action spaces suffer from the same drawback in the action space, too. This makes the learning process highly complex, or even intractable, in terms of memory requirements or learning time [31]. This problem can be overcome by addressing it from a DLR perspective. For instance, by considering a system with M actuators (an M-dimensional action space) and N discrete actions in each one, a DRL modeling leads to evaluating and storing NM values per state instead of {a mathematical formula}NM as a centralized RL does. This result in a linear increase with the number of actuators instead of an exponential one. A generalized expression for memory requirements and a computation time reduction factor during action selection can be determined [39], this is one of the main benefits of using DRL over CRL schemes, expressed by the following ratio:{a mathematical formula} where actuator m has {a mathematical formula}|Nm| discrete actions.
       </paragraph>
       <paragraph>
        The MAS perspective grants several potential advantages if the problem is approached with decentralized learners:
       </paragraph>
       <list>
        <list-item label="–">
         Since from a computational point of view, all the individual agents in a DRL system can operate in parallel acting upon their individual and reduced action spaces, the learning speed is typically higher compared to a centralized agent which searches an exponentially larger action space {a mathematical formula}N=N1×⋯×NM, as expressed in (2)[39].
        </list-item>
        <list-item label="–">
         The state space can be reduced for an individual agent, if not all the state information is relevant to that agent.
        </list-item>
        <list-item label="–">
         Different algorithms, models or configurations could be used by each individual agent.
        </list-item>
        <list-item label="–">
         Parallel or distributed computing implementations are suitable.
        </list-item>
       </list>
       <paragraph>
        There are various alternatives to decentralize a system performed with a single robot, for example, task decomposition [54], behavior fusion [17], and layered learning [44]. However, in this work we are proposing the multi-dimensional action space decomposition, where each action dimension is learned-controlled by one agent. In this way, the aforementioned potential advantages can be exploited.
       </paragraph>
      </section>
      <section label="2.3.2">
       <section-title>
        Challenges in DRL
       </section-title>
       <paragraph>
        DRL also has several challenges which must be resolved efficiently in order to take advantage of the benefits already mentioned. Agents have to coordinate their individual behaviors toward a desired joint behavior. This is not a trivial goal since the individual behaviors are correlated and each individual decision influences the environment. Furthermore, as pointed out in Section 2.2.1, an important aspect to deal with is the Markov property violation. The presence of multiple concurrent learners, makes the environment non-stationary from a single agent's perspective [5]. The evolution of its transition probabilities do not only depend on time, the process evolution is led by the agents' actions and their own history. Therefore, from a single agent's perspective, the environment no longer appears Markovian [22]. In Section 4, two MAL algorithms for addressing some of these open issues in DRL implementations, are presented: the Cooperative Adaptive Learning Rate, and an extension of the Lenient RL algorithm applied to multi-state DRL problems.
       </paragraph>
      </section>
     </section>
     <section label="2.4">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       Busoniu et al. [7] present centralized and multi-agent learning approaches for RL, tested on a two-link manipulator, and compared them in terms of performance, convergence time, and computational resources. Martin and De Lope [31] present a distributed RL modeling for generating a real-time trajectory of both a three-link planar robot and the SCARA robot; experimental results showed that it is not necessary for decentralized agents to perceive the whole state space in order to learn a good global policy. Probably, the most similar work to ours is reported by Troost, Schuitema, and Jonker [48], this paper uses an approach in which each output is controlled by an independent {a mathematical formula}Q(λ) agent. Both simulated robotic systems tested showed and almost identical performance and learning time between the single-agent and MA approaches, while this last one requires less memory and computation time. A Lenient RL implementation was also tested showing a significant performance improvement for one of the case studied. Some of these experiments and results were extended and presented by Schuitema [39]. Moreover, the DRL of the soccer ball-dribbling behavior is accelerated by using knowledge transfer [26], where, each component of the omnidirectional biped walk {a mathematical formula}(vx,vy,vθ) is learned by separate agents working in parallel on a multi-agent task. This learning approach for the omnidirectional velocity vector is also reported by Leottau, Ruiz-del-Solar, MacAlpine, and Stone [27], in which some layered learning strategies are studied for developing individual behaviors, and one of these strategies, the concurrent layered learning involves the DRL. Similarly, a MARL application for the multi-wheel control of a mobile robot is presented by Dziomin, Kabysh, Golovko, and Stetter [11]. The robotic platform is separated into driving module agents that are trained independently, in order to provide energy consumption optimization. A multi-agent RL approach is presented by Kabysh, Golovko, and Lipnickas [18], which uses agents' influences to estimate learning error among all the agents; it has been validated with a multi-joint robotic arm. On the other hand, Kimura [20] presents a coarse coding technique and an action selection scheme for RL in multi-dimensional and continuous state-action spaces following conventional and sound RL manners; and Pazis and Lagoudakis [38] present an approach for efficiently learning and acting in domains with continuous and/or multidimensional control variables, in which the problem of generalizing among actions is transformed to a problem of generalizing among states in an equivalent MDP, where action selection is trivial. A different application is reported by Matignon, Laurent, and Fort-Piat [32], where a semi-decentralized RL control approach for controlling a distributed-air-jet micro-manipulator is proposed. This showed a successful application of decentralized Q-learning variant algorithms for independent agents. Finally, a well-known related work was reported by Crites and Barto [9], an application of RL to the real world problem of elevator dispatching, its states are not fully observable and they are non-stationary due to changing passenger arrival rates. So, a team of RL agents is used, each of which is responsible for controlling one elevator car. Results showed that in simulation surpass the best of the heuristic elevator control tested algorithms.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Decentralized Reinforcement Learning methodology
     </section-title>
     <paragraph>
      In this section, we present a methodology for modeling and implementing a DRL system. Aspects such as what kind of problem is a candidate for being decentralized, which sub-tasks, actions, or states should or could be decomposed, and what kind of reward functions and RL learning algorithms should be used are addressed. The 3D mountain car is used as an example in this section. The following methodology is proposed for identifying and modeling a DRL system.
     </paragraph>
     <section label="3.1">
      <section-title>
       Determining if the problem is decentralizable
      </section-title>
      <paragraph>
       First of all, it is necessary to determine if the problem addressed is decentralizable via action space decomposition, and, if it is, to determine into how many subproblems the system can be separated. In robotics, a multi-dimensional action space usually implies multiple controllable inputs, i.e., multiple actuators or effectors. For instance, an M-joint robotic arm or an M-copter usually has at least one actuator (e.g., a motor) per joint or rotor, respectively, while a differential drive robot has two end-effectors (right and left wheels), and an omnidirectional biped gait has a three-dimensional commanded velocity vector ({a mathematical formula}[vx,vy,vθ]). Thus, for the remainder of this approach, we are going to assume as a first step that:
      </paragraph>
      <paragraph label="Proposition 1">
       A system with an M-dimensional action space is decentralizable if each of these action dimensions are able to operate in parallel and their individual information and resources can be managed separately. In this way, it is possible to decentralize the problem by using M individual agents, which will learn together toward a common goal.
      </paragraph>
      <paragraph>
       This concept will be illustrated with the 3DMC problem. A basic description of this problem is given below, and it will be detailed in depth in Section 5.1.
      </paragraph>
      <paragraph>
       3-Dimensional mountain car: mountain car is one of the canonical RL tasks where an agent must drive an under-powered car up a mountain to reach a goal state. In the 3D modification originally proposed by Taylor and Stone [46], the mountain's curve is extended to a 3D surface as is shown in Fig. 2. The state has four continuous state variables: {a mathematical formula}[x,x˙,y,y˙]. The agent selects from five actions: {a mathematical formula}{Neutral,West,East,South,North}, where the x axis of the car points toward the north. The reward is −1 for each time step until the goal is reached, at which point the episode ends and the reward is 0.
      </paragraph>
      <paragraph>
       This problem can also be described by a decentralized RL modeling. It has a bi-dimensional action space, where {a mathematical formula}{West,East} actions modify speed {a mathematical formula}x˙ onto the x axis (dimension 1), and {a mathematical formula}{South,North} actions modify speed {a mathematical formula}y˙ onto the y axis (dimension 2). These two action dimensions can act in parallel, and they can be controlled separately. So, Proposition 1 is fulfilled, and 3DMC is a decentralizable problem by using two RL separate agents: {a mathematical formula}Agentx and {a mathematical formula}Agenty.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Identifying common and individual goals
      </section-title>
      <paragraph>
       In a DRL system, a collection of separate agents learn, individual policies in parallel, in order to perform a desired behavior together to reach a common goal.
      </paragraph>
      <paragraph>
       A common goal is always present in a DRL problem, and for some cases it is the same for all the individual agents, especially when they share identical state spaces, similar actions, and common reward functions. But, there are problems in which a particular sub-problem can be assigned to a determined agent in order to reach that common goal. To identify each agent's individual goal is a non-trivial design step, that requires knowledge of the problem. This is not an issue for centralized schemes, but it is an advantage of a decentralized modeling because it allows addressing the problem more deeply.
      </paragraph>
      <paragraph>
       There are two types of individual goals for DRL agents: those which are intrinsically generated by the learning system when an agent has different state or action spaces with respect to the others, and those individual goals which are assigned by the designer to every agent, defining individual reward functions for that purpose. For the remainder of this manuscript, the concept of individual goals and individual reward functions will refer to those kinds of goals assigned by the designer.
      </paragraph>
      <paragraph>
       At this time, there is no general rule for modeling the goals' system of a DRL problem, and still it is necessary spending time in designing it for each individual problem. Since individual goals imply individual rewards, it is a decision which depends on how specific the sub-task performed by each individual agent is, and to what extent the designer is familiar with the problem and each decentralized sub-problem. If there is only a common goal, this is directly related with the global task or desired behavior and guided by the common reward function. Otherwise, if individual goals are considered, their combination must guarantee to achieve the common goal.
      </paragraph>
      <paragraph>
       For instance, the common goal for the 3DMC problem is reaching the goal state at the north-east corner in the Fig. 2. Individual goals can be identified, {a mathematical formula}Agentx should reach the east top, and {a mathematical formula}Agenty should reach the north top.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Defining the reward functions
      </section-title>
      <paragraph>
       If no individual goals have been assigned in the former stage, this step just consists of defining a global reward function according to the common goal and the desired behavior which the DRL system is designed for. If this is not the case, individual reward functions must be designed according to each individual goal.
      </paragraph>
      <paragraph>
       Design considerations for defining the global or each individual reward function are the same for classical RL systems [43]. This is the most important design step requiring experience, knowledge, and creativity. A well-known rule is that the RL agent must be able to observe or control every variable involved in the reward function {a mathematical formula}R(S,A). Then, the next stage of this methodology consists of determining the state spaces.
      </paragraph>
      <paragraph>
       In the centralized modeling for the 3DMC problem, a global reward function is proposed as: {a mathematical formula}r=0 if the common goal is reached, {a mathematical formula}r=−1otherwise. In the DRL scheme, individual reward functions can be defined as: {a mathematical formula}rx=0 if East top is reached, {a mathematical formula}rx=−1otherwise, for the {a mathematical formula}Agentx, and {a mathematical formula}ry=0 if north top is reached; {a mathematical formula}ry=−1otherwise, for the {a mathematical formula}Agenty. In this way, each single sub-task is more specific.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Determining if the problem is fully decentralizable
      </section-title>
      <paragraph>
       The next stage in this methodology consists of determining if it is necessary and/or possible to decentralize the state space too. In Section 3.1 it was determined that at least the action space will be split according to its number of dimensions. Now we are going to determine if it is also possible to simplify the state space using one separate state vector per each individual agent. This is the particular situation in which a DRL architecture offers the maximum benefit.
      </paragraph>
      <paragraph label="Proposition 2">
       A DRL problem is fully decentralizable if not all the state information is relevant to all the agents, thus, individual state vectors can be defined for each agent.
      </paragraph>
      <paragraph>
       If a system is not fully decentralizable, and it is necessary that all the agents observe the whole state information, the same state vector must be used for all the individual agents, and will be called a joint state vector. However, if a system is fully decentralizable, the next stage is to determine which state variables are relevant to each individual agent. This decision depends on the transition function {a mathematical formula}Tm of each individual goal defined as in Section 3.2, as well as on each individual reward function designed as in Section 3.3. For example, for a classical RL system, the definition of the state space must include every state variable involved in the reward function, as well as other states relevant to accomplishing the assigned goal.
      </paragraph>
      <paragraph>
       Note that individual reward functions do not imply individual state spaces per agent. For instance, the 3DMC example can be designed with those two individual rewards ({a mathematical formula}rx and {a mathematical formula}ry) defined as in Section 3.3, observing the full joint state space {a mathematical formula}[x,x˙,y,y˙]. Also, note that state space could be reduced for practical effects, {a mathematical formula}Agentx could eventually work without observing {a mathematical formula}y˙ speed, as well as {a mathematical formula}Agenty without observing {a mathematical formula}x˙ speed. So, a simplified 3DMC could be modeled as a fully decentralized problem with two individual agents with their own independent state vectors, {a mathematical formula}sx=[x,x˙,y],sy=[x,y,y˙]. Furthermore, we have implemented an extreme case with incomplete observations in which {a mathematical formula}sx=[x,x˙],sy=[y,y˙]. Implementation details as well as experimental results can be seen in Section 5.1.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Completing RL single modelings
      </section-title>
      <paragraph>
       Once the global DRL modeling has been defined and the tuples state, action, and reward {a mathematical formula}[Sm,Am,Rm] are well identified per every agent {a mathematical formula}m=1,⋯,M, it is necessary to complete each single RL modeling. Implementation and environmental details such as ranges and boundaries of features, terminal states, and reset conditions must be defined, as well as RL algorithms and parameters selected. If individual sub-tasks and their goals are well identified, modeling each individual agent implies the same procedure as in a classical RL system. Some problems can share some of these design details among all or some of their DRL agents. This is one of the most interesting aspects of using a DRL system: flexibility to implement completely different modelings, RL algorithms, and parameters per each individual agent; or the simplicity of just using the same scheme for all the agents.
      </paragraph>
      <paragraph>
       An important design issue at this stage, is choosing the RL algorithm to be implemented per each agent properly. Considerations for modeling a classical RL single agent are also applicable here. For instance, for a discrete state-action space problem it could be more useful to use algorithms like tabular Q-Learning [53] or R-MAX [4]; for a continuous state and discrete action space problem, a SARSA with function approximation [43] might be more useful; for a continuous state-action space problem, a Fuzzy Q-Learning [13] or an actor critic scheme [15] could be more convenient. These cases are only examples to give an idea about the close relationship between modeling and designing classical RL agents versus each individual DRL agent. As already mentioned, differences are based on determining terminal states separately, resetting conditions, and establishing environment limitations, among other design settings, which can be different among agents and must be well set to coordinate the parallel learning procedure under the joint environmental conditions. Of course, depending on the particular problem, the designer has to model and define the most convenient scheme. Also note that if well-known RL algorithms are used, no extra considerations must be taken into account in designing and modeling a DRL system. Thereby, a strong background in MAS and/or MAL is not necessary.
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       Summary
      </section-title>
      <paragraph>
       A methodology for modeling and implementing a DRL system has been presented in this section by following a five stage design procedure. It is important to mention that some of these stages must not necessarily be applied in the same order in which they were presented. That depends on the particular problem and its properties. For instance, for some problems it could be necessary or more expeditious to define the state spaces in advance in Stage 3.4 rather than to determine individual goals in Stage 3.2. However, this is a methodology which guides the design of DRL systems in a general way. A block diagram of the proposed procedure is shown in Fig. 3.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Multi-agent learning methods
     </section-title>
     <paragraph>
      In this section, we examine some practical DRL algorithms to show that the benefits of MAS are also applicable to complex and real-world problems (such as robotic platforms) by using DRL systems. For this, we have implemented and tested some relevant MAL methods from state-of-the-art which accomplish the three basic requirements of our interest: (i) no prior coordination, (ii) no teammates models estimation, and (iii) non-exponential increasing of computational resources when more agents are added. Based on our initial experiments, a brief note on our preliminary results from the selected methods is provided below:
     </paragraph>
     <list>
      <list-item label="(a)">
       Distributed Q-Learning[21]: asymptotic convergence was not observed for all the trials, which can be explained by the stochasticity of the studied scenarios.
      </list-item>
      <list-item label="(b)">
       Frequency Adjusted Multi-Agent Q-Learning[19]: we observed poor performance since parameter β is too sensitive and thus it was difficult to adjust; however, the idea of an adjustable learning rate from the Boltzmann probability distribution is of relevant interest.
      </list-item>
      <list-item label="(c)">
       Adaptations of the Infinitesimal Gradient Ascent algorithm (IGA) [41] and the Win or Learn Fast (WoLF) principle [3]: not a trivial implementation in the case of more than two agents and non-competitives environments; however, a cooperative and variable learning rate is a promising approach.
      </list-item>
      <list-item label="(d)">
       Lenient Frequency Adjusted Q-learning (LFAQ) [1]: it exposed poor performance due to both the tabular nature to handle lenience, and the high complexity to adjust individual FA parameters.
      </list-item>
      <list-item label="(e)">
       Independent Multi-Agent Q-Learning without sharing information (e.g., the one reported by Sen, Sekaran, and Hale [40]): it mostly showed asymptotic convergence but poor final performances.
      </list-item>
      <list-item label="(f)">
       Lenient Multi-Agent Reinforcement Learning[35]: it showed asymptotic convergence when applied to multi-state DRL problems.
      </list-item>
     </list>
     <paragraph>
      From the above, in the present study we have decided to use the following three algorithms: (i) Independent DRL (DRL-Independent), similar to (a) but implemented with SARSA; (ii) Lenient Multi-Agent Reinforcement Learning (DRL-Lenient), as in (f) but extended to multi-state DRL problems; and (iii) Cooperative Adaptive Learning Rate (DRL-CA) algorithm, our proposed approach, inspired by (b) and (c). These approaches will be addressed in detail in the following subsections, and the corresponding performance will be discussed in Section 5.
     </paragraph>
     <section label="4.1">
      <section-title>
       DRL-Independent
      </section-title>
      <paragraph>
       This scheme aims for applying single-agent RL methods to the MARL task, and it does not consider any of the following features: cooperation or coordination among agents; adaptation to the other agents; estimated models of their policies; special action-selection mechanisms, such as communication among agents, prior knowledge, etc. The computational complexity of this DRL scheme is the same as that for a single RL agent (e.g., a Q-Learner).
      </paragraph>
      <paragraph>
       According to the MAL literature, a single-agent RL can be applicable to stochastic games, although success is not necessarily guaranteed as the non-stationarity of the MARL problem invalidates most of the single-agent RL theoretical guarantees. However, it is considered a practical method due to its simplicity, and it has been used in several applications to robot systems [7], [33], [28]. The implementation of this scheme is presented in Algorithm 1, which depicts an episodic MA-SARSA algorithm for continuous states with Radial Basis Function (RBF) approximation [37], and ϵ-greedy exploration [43], where a learning system is modeled with an {a mathematical formula}M−dimensional action space and M single SARSA learners acting in parallel.
      </paragraph>
      <paragraph>
       Algorithm 1 is described for the most general case of a fully-decentralized system with individual rewards, where states and rewards are annotated as {a mathematical formula}sm and {a mathematical formula}rm respectively, but it is also possible to implement a joint state vector or common reward DRL systems. In addition, note that RL parameters could have been defined separately per agent ({a mathematical formula}αm,γm), which is one of the DRL properties remarked in Section 2.3, but in Algorithm 1 they appear unified just for the sake of simplicity.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       DRL-Lenient
      </section-title>
      <paragraph>
       Originally proposed by Panait et al. [35], the argument of lenient learning is that each agent should be lenient with its teammates at early stages of the concurrent learning processes. Later, Panait, Tuyls, and Luke [36] suggested that the agents should ignore lower rewards (observed upon performing their actions), and only update the utilities of actions based on the higher rewards. This can be achieved in a simple manner if the learners compare the observed reward with the estimated utility of an action and update the utility only if it is lower than the reward, namely, by making use of the rule{a mathematical formula} where {a mathematical formula}urnd∈[0,1] is a random variable, κ is the lenience exponent coefficient, and {a mathematical formula}τ(a⁎) is the lenience temperature of the selected action. Lenience may be reduced as learning progresses and agents start focusing on a solution that becomes more critical with respect to joint rewards (ignoring fewer of them) during advanced stages of the learning process, which can be incorporated in Eq. (3) by using a discount factor β each time that action is performed.
      </paragraph>
      <paragraph>
       Lenient learning was initially proposed in state-less MA problems. According to Troost et al. [48] and Schuitema [39], a multi-state implementation of Lenient Q-learning can be accomplished by combining the Q-Learning update rule (i.e. Eq. (1)) with the optimistic assumption proposed by Lauer and Riedmiller [21]. Accordingly, the action-value function is updated optimistically at the beginning of the learning trial, taking into account the maximum utility previously received along with each state-action pair visited. Then, lenience toward other agents is refined smoothly, returning to the original update function (this is, Eq. (1)):{a mathematical formula} with the state-action pair dependent lenience {a mathematical formula}ℓ(s,a) defined as{a mathematical formula} where κ is the lenience coefficient, and {a mathematical formula}τ(s,a) is the lenience temperature of the state action pair {a mathematical formula}(s,a), which decreases with a discount factor β each time the state-action pair is visited.
      </paragraph>
      <paragraph>
       In our study, we implement lenient learning by adapting the update rule (4) to multi-state, stochastic, continuous state-action DRL problems, as reported by Troost et al. [48] and Schuitema [39]. The DRL-Lenient algorithm presented in Algorithm 2, which is implemented by replacing traces, incorporates a tabular MA-SARSA(λ) method, and uses softmax action selection from Sutton and Barto [43].
      </paragraph>
      <paragraph>
       In Algorithm 2, individual temperatures are managed separately by each state-action pair. These temperatures (line 20) are used to later compute the Boltzmann probability distribution Pa (line 26), which is the basis for the softmax action selection mechanism. Note that only the corresponding temperature {a mathematical formula}τ(st,ai) is decayed in line 29 after the state-action pair {a mathematical formula}(st,ai) is visited. This is a difference with respect to the usual softmax exploration which uses a single temperature for the entire learning process. Value function is updated only if the learning procedure is either optimistic or lenient, otherwise it is not updated. It is either optimistically updated whenever the last performed action increases the current utility function, or leniently updated if the agent has explored that action sufficiently. Since lenience (line 30) is also computed from temperature, every state-action pair has an individual lenience degree as well. The agent is more lenient (and it thus ignores low rewards) if the temperature associated with the current state-action pair is high. Such a leniency is reduced as long as its respective state-action pair is visited; in that case, the agent will tend to be progressively more critical in refining the policy.
      </paragraph>
      <paragraph>
       In order to extend DRL-Lenient to continuous states, it is necessary to implement a function approximation strategy for the lenient temperature {a mathematical formula}τ(s,a), the eligibility traces {a mathematical formula}e(s,a), and the action-value functions. Following a linear gradient-descent strategy with RBF-features, similar to that presented in Algorithm 1, function approximations can be expressed as:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} where Φ is the size of the feature vector {a mathematical formula}ϕs. Equations (5a), (5c), (5d), (5e) and (5f) would approximate lines 19, 29, 28, 33 and 36, respectively. For practical implementations, {a mathematical formula}τa must be set between {a mathematical formula}(0,1).
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       DRL-CA
      </section-title>
      <paragraph>
       In this paper, we introduce the DRL Cooperative Adaptive Learning Rate algorithm (DRL-CA), which mainly takes inspiration from the MARL approaches with a variable learning rate [3], and Frequency Adjusted Q-Learning (FAQL) [19]. We have used the idea of a variable learning rate from the WoLF principle [3] and the IGA algorithm [41], in which agents learn quickly when losing, and cautiously when winning. The WoLF-IGA algorithm requires knowing the actual distribution of the actions the other agents are playing, in order to determine if an agent is winning. This requirement is hard to accomplish for some MA applications in which real-time communication is a limitation (e.g., decentralized multi-robot systems), but it is not a major problem for DRL systems performing single robot behaviors. Thus, DRL-CA uses a cooperative approach to adapt the learning rate, sharing the actual distribution of actions per-each agent. Unlike the original WoLF-IGA, where gradient ascent is derived from the expected pay-off, or unlike the current utility function from the update rule [3], DRL-CA directly uses the probability of the selected actions, having a common normalized measure of partial quality of the policy performed per agent. This idea is similar to FAQ-Learning [19], in which the Q update rule{a mathematical formula} is modified by the adjusted frequency parameter ({a mathematical formula}min⁡(β/xi,1)). In our DRL-CA approach, we replace such term by a cooperative adaptive factor ς defined as{a mathematical formula}
      </paragraph>
      <paragraph>
       The main principle of DRL-CA is supported on this cooperative factor that adapts a global learning rate on-line, which is based on a simple estimation of the partial quality of the joint policy performed. So, ς is computed from the probability of selected action ({a mathematical formula}Pa⁎), according to the “weakest” among the M agents.
      </paragraph>
      <paragraph>
       A variable learning rate based on the gradient ascent approach presents the same properties as an algorithm with an appropriately decreasing step size [41]. In this way, DRL-CA shows a decreasing step size if a cooperative adaptive factor ς such as (7) is used. We refer to this decremental variation as DRL-CAdec. So, an agent should adapt quickly during the early learning process, trying to collect experience and learn fast while there is a mis-coordinated joint policy. In this case, we have that {a mathematical formula}ς→1 and the learning rate tends to α. Once the agents progressively obtain better rewards, they should be cautious since the other players are refining their policies and, eventually, they will explore unknown actions which can produce temporal mis-coordination. In this case, we have {a mathematical formula}ς→0 and a decreasing learning rate, while better decisions are being made. Note that DRL-CAdec acts contrarily to the DRL-Lenient principle.
      </paragraph>
      <paragraph>
       We also introduce the DRL-CAinc, a variation in which a cooperative adaptive factor increases during the learning process if a coordinated policy is learned gradually. This variation uses{a mathematical formula} instead of (7). Here, a similar lenient effect occurs, and the agents update their utilities cautiously during the early learning process, being lenient with weaker agents while they learn better policies. In this case, ς starts from the lowest probability among all the agents, making the learning rate tend to a small but non-zero value. Once the agents are progressively obtaining better rewards, they learn and update from their coordinated joint policy. Then, in this case, {a mathematical formula}ς→1 and the learning rate tends toward a high value.
      </paragraph>
      <paragraph>
       DRL-CAdec and DRL-CAinc show opposite principles. A detailed analysis of their properties is presented in Section 5. The common principle behind both variants is the cooperative adaptation based on the current weakest learner's performance. We also have empirically tested other cooperative adaptive factors, but they resulted in no success: (i) based on individual factors, {a mathematical formula}ςm=Pa⁎,m for each {a mathematical formula}agentm; (ii) based on the best agent, {a mathematical formula}ς=maxm⁡Pa⁎,m; and (iii) based on the mean of their qualities, {a mathematical formula}ς=meanmPa⁎,m.
      </paragraph>
      <paragraph>
       The chosen approach (based on the weakest agent) coordinates the learning evolution awaiting similar skills among the agents. This is possible since ς comes from a Boltzmann distribution, which is a probability always bounded between {a mathematical formula}[0,1], and thus it is possible to consider ς as a measure of the current learned skill by an agent. This is desirable for the cooperation among the agents, and is an advantage over methods based on the Temporal Difference (TD) or instant reward, in which their gradients are not normalized and extra parameters must be adjusted. Concerning DRL-CAinc, the most skilled agents wait for the less skilled one, showing leniency by adapting the learning rate according to the current utility function of the weakest learner. This makes sense because the policy of the most skilled agents could change when the less skilled one improves its policy, so the agents should be cautious. Once all the agents have similar skills, the learning rate is gradually increased for faster learning while the joint policy is improved. In the case of DRL-CAdec, the less-skilled agents motivate their teammates to extract more information from the joint-environment and joint-actions, in order to find a better common decision which can quickly improve such a weak policy.
      </paragraph>
      <paragraph>
       Algorithm 3 presents the DRL-CA implementation for multi-state, stochastic, continuous state-action DRL problems. It is an episodic MA-SARSA(λ) algorithm with RBF approximation and softmax action selection. The incremental cooperative adaptive factor (Eq. (8)) is calculated in line 32, and the decremental cooperative adaptive factor (Eq. (7)) is calculated in line 34.
      </paragraph>
      <paragraph>
       Note that, for practical implementations in which agents have different numbers of discrete actions, each {a mathematical formula}Pa⁎,m must be biased to {a mathematical formula}Pa⁎′,m in order to have equal initial probabilities among the individual agents, i.e. {a mathematical formula}Pas=0⁎′,1=⋯=Pas=0⁎′,M, and then {a mathematical formula}Pa⁎′,m=Fbias(Pa⁎,m), where {a mathematical formula}∀Pa⁎′,m∈[0,1]. A simple alternative to calculate this is by computing {a mathematical formula}Pa⁎′,m=max⁡(1/Nm,Pa⁎,m), or{a mathematical formula} which is a more accurate approach. This bias must be computed after line 28, and then σ in line 32 must be computed by using {a mathematical formula}Pa⁎′,m instead of the non-biased {a mathematical formula}Pa⁎,m.
      </paragraph>
      <paragraph>
       Note that both Algorithm 2, Algorithm 3 have been described with a softmax action selection mechanism. Other exploration methods such as ϵ-greedy can be easily implemented, but it must be taken into account that both methods DRL-Lenient and DRL-CA are based on the Boltzmann probability distribution, Pa, which must bee calculated as well. However, this only requires on-line and temporary computations, and no extra memory consumption.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Experimental validation
     </section-title>
     <paragraph>
      In order to validate MAS benefits and properties of the DRL systems, four different problems have been carefully selected: the 3DMC, a three-Dimensional extension of the mountain car problem [46]; the SCARA-RTG, a SCARA robot generating a real-time trajectory for navigating towards a 3D goal position [31]; the Ball-Pushing performed with a differential drive robot [28]; and the soccer Ball-Dribbling task [25]. The 3DMC and SCARA-RTG are well known and are already proposed test-beds. The Ball-Dribbling and Ball-Pushing problems are noisy and stochastic real-world applications that have been tested already with physical robots.
     </paragraph>
     <paragraph>
      The problem descriptions and results are presented in a manner of increasing complexity. 3DMC is a canonical RL test-bed; it allows splitting the action space, as well as the state space for evaluating from a centralized system, up to a fully decentralized system with limited observability of the state space. The Ball-Pushing problem also allows carrying out a performance comparison between a centralized and a decentralized scheme. The best CRL and DRL learned policies are transferred and tested with a physical robot. The Ball-Dribbling and SCARA-RTG problems are more complex systems (implemented with 3 and 4 individual agents respectively). Ball-dribbling is a very complex behavior which involves three parallel sub-tasks in a highly dynamic and non-linear environment. The SCARA-RTG has four joints acting simultaneously in a 3-Dimensional space, in which the observed state for the whole system is only the error between the current end-effector position, {a mathematical formula}[x,y,z], and a random target position.
     </paragraph>
     <paragraph>
      Some relevant parameters of the RL algorithms implemented are optimized by using a customized version of the hill-climbing method. It is carried out independently for each approach and problem tested. Details about the optimization procedure and the pseudo-code of the implemented algorithm can be found in Appendix A. Finally, 25 runs are performed by using the best parameter settings obtained in the optimization procedure. Learning evolution results are plotted by averaging those 25 runs, and error bars show the standard error. In addition, the averaged final performance is also measured: it considers the last 10% of the total learning episodes.
     </paragraph>
     <paragraph>
      A description of each problem tested and some implementation and modeling details are presented in the next sub-sections, following the methodology described in Section 3. The experimental results and analysis are then discussed. All the acronyms of the implemented methods and problems are listed in Table 1. We used the following terminology: CRL means a Centralized RL scheme; DRL-Ind is an independent learners scheme implemented without any kind of MA coordination; DRL-CAdec, DRL-CAinc, and DRL-Lenient are respectively a DRL system coordinated with Decremental Cooperative Adaptation, Incremental Cooperative Adaptation, and a Lenient approach. In the case of the 3DMC, CRL-5a and CRL-9a are Centralized RL schemes implemented with 5 actions (the original 3DMC modeling [46]) and 9 actions (our extended version) respectively. ObsF and ObsL are Full Observability and Limited observability of the joint state space respectively. In the case of the Ball-Pushing problem, DRL-Hybrid is a hybrid DRL-Ind scheme implemented with a SARSA(λ) + a Fuzzy Q-Learning RL algorithm without any kind of MAS coordination (please see a detailed description in subsection 5.2). In the case of the Ball-Dribbling problem, DRL-Transfer is a DRL system accelerated by using the NASh transfer knowledge learning approach [26]; RL-FLC is an implementation reported by Leottau, Celemin, and Ruiz del Solar [25], which combines a Fuzzy Logic Controller (FLC) and an RL single agent; and eRL-FLC is an enhanced version of RL-FLC (please see their detailed descriptions in Subsection 5.3).
     </paragraph>
     <section label="5.1">
      <section-title>
       Three-dimensional mountain car
      </section-title>
      <paragraph>
       Mountain car is one of the canonical RL tasks in which an agent must drive an under-powered car up a mountain to reach a goal state. In the 3D modification originally proposed by Taylor and Stone [46], the mountain's curve is extended to a 3D surface as is shown in Fig. 2.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Centralized modelings
       </section-title>
       <paragraph>
        CRL-5a: The state has four continuous state variables: {a mathematical formula}[x,x˙,y,y˙]. The positions ({a mathematical formula}x,y) have the range of {a mathematical formula}[−1.2,0.6] and the speeds ({a mathematical formula}x˙,y˙) are constrained to {a mathematical formula}[−0.07,0.07]. The agent selects from five actions: {Neutral, West, East, South, North}. West and East on {a mathematical formula}x˙ are modified by −0.001 and +0.001 respectively, while South and North on {a mathematical formula}y˙ are modified by −0.001 and +0.001 respectively. On each time step {a mathematical formula}x˙ is updated by {a mathematical formula}−0.025(cos⁡(3x)) and {a mathematical formula}y˙ is updated by {a mathematical formula}−0.025(cos⁡(3y)) due to gravity. The goal state is {a mathematical formula}x≥0.5 and {a mathematical formula}y≥0.5. The agent begins at rest at the bottom of the hill. The reward is −1 for each time step until the goal is reached, at which point the episode ends and the reward is 0. The episode also ends, and the agent is reset to the start state, if the agent fails to find the goal within 5000 time steps.
       </paragraph>
       <paragraph>
        CRL-9a: The original centralized modeling (CRL-5a) [46] limits the agent's vehicle moves. It does not allow acting onto both action dimensions at the same time step. In order to make this problem fully decentralizable, more realistic, and challenging, we have extended the problem, augmenting the action space to nine actions (CRL-9a), adding {NorthWest, NorthEast, SouthWest, SouthEast} to the original CRL-5a. Since the car is now able to move on x and y axes at the same time, {a mathematical formula}x˙, and {a mathematical formula}y˙ updates must be multiplied by {a mathematical formula}1/2 for the new four actions because of the diagonal moves.
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Proposed decentralized modelings
       </section-title>
       <paragraph>
        We are going to follow the methodology proposed in Section 3, resuming and extending the 3DMC DRL modeling:
       </paragraph>
       <paragraph>
        Stage3.1 — Determining if the problem is decentralizable: since CRL-9a modeling is decentralizable because of its bi-dimensional action space ({a mathematical formula}x˙,y˙), a decentralized approach can be adopted by selecting two independent agents: {a mathematical formula}Agentx which action space is {a mathematical formula}{Neutral,West,East}, and {a mathematical formula}Agenty which action space is {a mathematical formula}{Neutral,South,North}.
       </paragraph>
       <paragraph>
        Stages3.2and3.3 — Identifying individual goals and defining reward functions: individual goals are considered, reaching east top for {a mathematical formula}Agentx and reaching north top for {a mathematical formula}Agenty. In this way, individual reward functions are defined as: {a mathematical formula}rx=0 if east top is reached, {a mathematical formula}rx=−1otherwise; and {a mathematical formula}ry=0 if north top is reached, {a mathematical formula}ry=−1otherwise.
       </paragraph>
       <paragraph>
        Stage3.4 — Determining if the problem is fully decentralizable: one of the goals of this work is evaluating and comparing the response of an RL system under different centralized–decentralized schemes. Thus, splitting the state vector is also proposed in order to have a fully decentralized system, and a very limited state observability for validating the usefulness of coordination of the presented MA DRL algorithms (Lenient and CA). In this case, {a mathematical formula}agentx only state variables {a mathematical formula}[x,x˙] can be observed, as well as {a mathematical formula}agenty only {a mathematical formula}[y,y˙]. This corresponds to a very complex scenario because both agents have incomplete observations, and do not even have free or indirect coordination due to different state spaces, decentralized action spaces, and individual reward functions. Moreover, the actions of each agent directly affect the joint environment, and both of the agents' next state observations.
       </paragraph>
       <paragraph>
        A description of the implemented modelings is shown below, in which X can be CAdec, CAinc, or Lenient, and RBF cores are the number of Radial Basis Function centers used per state variable to approximate action value functions as continuous functions. Please see Table 1 for the full list of acronyms.
       </paragraph>
       <list>
        <list-item label="–">
         CRL Original Modeling (CRL-5a):Actions: {a mathematical formula}{Neutral,West,East,South,North};Global reward function: {a mathematical formula}r=0 if goal, {a mathematical formula}r=−1 otherwise. Joint state vector: {a mathematical formula}[x,x˙,y,y˙], with {a mathematical formula}[9,6,9,6] RBF cores per state variable respectively;
        </list-item>
        <list-item label="–">
         CRL Extended Modeling (CRL-9a):Actions: {a mathematical formula}{Neutral,West,NorthWest,North,NorthEast,East,SouthEast,South,SouthWest};Global reward function: {a mathematical formula}r=0 if goal, {a mathematical formula}r=−1 otherwise. Joint state vector: {a mathematical formula}[x,x˙,y,y˙], with {a mathematical formula}[9,6,9,6] RBF cores;
        </list-item>
        <list-item label="–">
         DRL Full Observability (DRL-ObsF-X):Actions {a mathematical formula}agentx: {a mathematical formula}{Neutral,West,East},Actions {a mathematical formula}agenty: {a mathematical formula}{Neutral,South,North};Individual reward functions: {a mathematical formula}rx=0 if {a mathematical formula}x≥0.5, {a mathematical formula}rx=−1 otherwise, and {a mathematical formula}ry=0 if {a mathematical formula}y≥0.5, {a mathematical formula}ry=−1 otherwise.Joint state vector: {a mathematical formula}[x,x˙,y,y˙], with {a mathematical formula}[9,6,9,6] RBF cores;
        </list-item>
        <list-item label="–">
         DRL Limited Observability (DRL-ObsL-X):Actions {a mathematical formula}agentx: {a mathematical formula}{Neutral,West,East},Actions {a mathematical formula}agenty: {a mathematical formula}{Neutral,South,North};Individual reward functions: {a mathematical formula}rx=0 if {a mathematical formula}x≥0.5, {a mathematical formula}rx=−1 otherwise, and {a mathematical formula}ry=0 if {a mathematical formula}y≥0.5, {a mathematical formula}ry=−1 otherwise.Individual state vectors: {a mathematical formula}agentx=[x,x˙], with {a mathematical formula}[9,6] RBF cores; {a mathematical formula}agenty=[y,y˙], with {a mathematical formula}[9,6] RBF cores.
        </list-item>
       </list>
       <paragraph>
        Stage3.5 — Completing RL single modelings: this is detailed in the following two subsections. Implementation and environmental details have been already mentioned in the centralized modeling description, because most of them are in common with the decentralized modeling.
       </paragraph>
      </section>
      <section label="5.1.3">
       <section-title>
        Performance index
       </section-title>
       <paragraph>
        The evolution of the learning process is evaluated by measuring and averaging 25 runs. The performance index is the cumulative reward per episode, where {a mathematical formula}−5,000 is the worst case and zero, though unreachable, is the best case.
       </paragraph>
      </section>
      <section label="5.1.4">
       <section-title>
        RL algorithm and optimized parameters
       </section-title>
       <paragraph>
        SARSA(λ) with Radial Basis Function (RBF) approximation with ϵ-greedy exploration [43] was implemented for these experiments. The exploration rate ϵ is decayed by 0.99 at the end of each learning episode. The following parameters are obtained after the hill-climbing optimization procedure: learning rate (α), eligibility traces decay factor (λ), and exploration probability (ϵ). These parameters are detailed in Table 1 for each experiment. The number of Gaussian RBF cores per state variable were also optimized: 9 cores to x and y, 6 cores to {a mathematical formula}x˙ and {a mathematical formula}y˙, and a standard deviation per core of {a mathematical formula}1/2|featuremax−featuremin|/nCores. For all the experiments {a mathematical formula}γ=0.99.
       </paragraph>
      </section>
      <section label="5.1.5">
       <section-title>
        Results and analysis
       </section-title>
       <paragraph>
        Fig. 4 (top) shows a performance comparison between: the original implementation of 3DMC, CRL-5a; the extension of that original problem in which 9 actions are considered, CRL-9a; a decentralized scheme with full observability of the joint space state, DRL-ObsF-Ind; and a decentralized scheme with limited observability, DRL-ObsL-Ind. Please remember that the performance index starts from {a mathematical formula}−5,000 and it improves toward zero. Table 2 shows averaged final performances. Our results for CRL-5a converge considerably faster than the results presented by Taylor and Stone [46], which could be due to parameter optimization, and because we have implemented an RBF approach instead of CMAC for continuous state generalization. CRL-9a converges more slowly than the original one, as is expected because of the augmented action space. Note that DRL-ObsF-Ind speeds-up convergence and outperforms both centralized schemes. On the other hand, DRL-ObsL-Ind achieves a good performance quickly but is not stable during the whole learning process due to ambiguity between observed states and lack of coordination among the agents. However, it opens a question about potential benefits of DRL implementations with limited or incomplete state spaces which is discussed below.
       </paragraph>
       <paragraph>
        Regarding computational resources, from the optimized parameters definition presented above, the DRL-ObsF-Ind scheme uses two Q functions which consume {a mathematical formula}2⋅9⋅6⋅9⋅6⋅3=17496 memory cells, versus the {a mathematical formula}9⋅6⋅9⋅6⋅9=26244 of its CRL-9a counterpart; and DRL-ObsF-Ind consumes 1/3 less memory. Moreover, we measured the elapsed time of both learning process along the 25 performed runs, and founds that the DRL took 0.62 hour, while the CRL took 0.97 hour. We also measured only the action-selection+Q-function-update elapsed times, obtaining an average of 306.81 seconds per run for the DRL, being 1.43 times faster than the CRL scheme, which took 439.59s. These times are referential; experiments with an Intel{sup:®} Core™ i7-4774 CPU @ 3.40 GHz with 4 GB in RAM were performed. Note than even for this simple problem with only two agents, there are considerable memory consumption and processing time savings.
       </paragraph>
       <paragraph>
        Fig. 4 (middle) shows a performance comparison between schemes implemented considering full observability (ObsF) of the joint space state, these schemes are: the same response of CRL-9a presented in Fig. 4 (top); once again the DRL-ObsF-Ind; a Decremental Cooperative Adaptive DRL-ObsF-CAdec scheme; an Incremental Cooperative Adaptive DRL-ObsF-CAinc scheme; and, a DRL-ObsF-Lenient implementation. As noticed in Fig. 4, all the DRL systems accelerate the asymptotic convergence considerably and outperform the CRL one. Note also that all the DRL systems show similar learning times, while in Table 2, DRL-ObsF-CAdec shows the best performance, overcoming the −200 performance threshold with DRL-ObsF-Lenient.
       </paragraph>
       <paragraph>
        Fig. 4 (bottom) shows a performance comparison between schemes implemented considering limited observability (ObsL) of the joint space state, these schemes are: CRL-9a; DRL-ObsL-Ind; a Decremental Cooperative Adaptive DRL-ObsL-CAdec scheme; an Incremental Cooperative Adaptive DRL-ObsL-CAinc scheme; and a DRL-ObsL-Lenient implementation. Benefits of proposed Lenient and CA algorithms are more noticeable in these experiments, in which the DRL-ObsL-Ind scheme without coordination did not achieve a stable final performance. With the exception of DRL implementation (green line), all the DRL systems have dramatically accelerated convergence times regarding the CRL scheme. This is empirical evidence of proposed MAS based algorithm benefits (CAdec, CAinc, and Lenient), even if incomplete observations are used. These benefits are not evident for those experiments with full observation, in which convergence time and performance are similar to the DRL-Ind scheme. DRL-ObsL-Lenient indirectly achieves a coordinated policy. Although for this particular case leniency is not directly involved in the ϵ-greedy action-selection mechanism, it is involved during the action-value function updating, which of course, affects the action-selection mechanism afterwards. On the other hand, DRL-ObsL-CAdec collects experience and, while a coordinated policy is gradually reached, the learning rate is decreased and the action-value function updates have progressively less weight. It just avoids the poor final performance of the DRL-ObsL-Ind scheme. Also DRL-ObsL-CAinc achieves a good performance; it has a similar effect to that of the Lenient algorithm. Also, note in Table 2 that DRL-ObsL-CAinc and DRL-ObsL-Lenient outperform the −200 threshold, even beating its DRL-ObsF counterparts, and beating the DRL-ObsF-Ind as well. This is an interesting result, taking into account DRL-ObsL schemes are able to reach similar performance as the DRL-ObsF-CAdec and DRL-ObsF-Lenient, the best schemes implemented with full observability.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Ball-Pushing
      </section-title>
      <paragraph>
       We consider the Ball-Pushing behavior, a basic robot soccer skill similar to that studied by Takahashi and Asada [44] and Emery and Balch [12]. A differential robot player attempts to push the ball and score a goal. The MiaRobot Pro is used for this implementation (see Fig. 5). In the case of a differential robot, the complexity of this task comes from its non-holonomic nature, limited motion and accuracy, and especially the highly dynamic and non-linear physical interaction between the ball and the robot's irregular front shape. The description of the desired behavior will use the following variables: {a mathematical formula}[vl,vw], the velocity vector composite by linear and angular speeds; {a mathematical formula}aw, the angular acceleration; γ, the robot-ball angle; ρ, the robot-ball distance; and, ϕ, the robot-ball-target complementary angle. These variables are shown in Fig. 5 at the left, where the center of the goal is located in ⊕, and a robot's egocentric reference system is considered with the x axis pointing forwards.
      </paragraph>
      <paragraph>
       The RL procedure is carried out episodically. After a reset, the ball is placed in a fixed position 20 cm in front of the goal, and the robot is set at a random position behind the ball and the goal. The successful terminal state is reached if the ball crosses the goal line. If the robot leaves the field, it is also considered a terminal state. The RL procedure is carried out in a simulator, and the best learned policy obtained between the 25 runs for the CRL and DRL-Ind implementations is directly transferred and tested on the MiaBot Pro robot in the experimental setup.
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Centralized modeling
       </section-title>
       <paragraph>
        For this implementation, proposed control actions are twofold {a mathematical formula}[vl,aw], the requested linear speed and the angular acceleration, where {a mathematical formula}Aaw=[positive,neutral,negative]. Our expected policy is to move fast and push the ball toward the goal; that is, to minimize {a mathematical formula}ρ,γ,ϕ, and to maximize {a mathematical formula}vl. Thus, this centralized approach considers all possible action combinations {a mathematical formula}A=AvlAaw and the robot learns {a mathematical formula}[vl,aw] actions from the observed joint state {a mathematical formula}[ρ,γ,ϕ,vw], where {a mathematical formula}[vw=vw(k−1)+aw]. States and actions are detailed in Table 3.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Decentralized modeling
       </section-title>
       <paragraph>
        Stage3.1 — Determining if the problem is decentralizable: the differential robot velocity vector can be split into two independent actuators: right and left wheel speeds {a mathematical formula}[vr,vl], or linear and angular speeds {a mathematical formula}[vl,vw]. To keep parity with the centralized model, our decentralized modeling considers two individual agents for learning {a mathematical formula}vl and {a mathematical formula}aw in parallel as is shown in Table 3.
       </paragraph>
       <paragraph>
        Stage3.2 — Identifying common and individual goals: the Ball-Pushing behavior can be separated into two sub-tasks, ball-shooting and ball-goal-aligning, which are performed respectively by {a mathematical formula}agentvl and {a mathematical formula}agentaw.
       </paragraph>
       <paragraph>
        Stage3.3 — Defining the reward functions: a common reward function is considered for both CRL and DRL implementations, as is shown in Expression (10), where max features are normalization values taken from Table 3.{a mathematical formula}
       </paragraph>
       <paragraph>
        Stage3.4 — Determining if the problem is fully decentralizable: the joint state vector {a mathematical formula}[ρ,γ,ϕ,vw] is identical to the one proposed for the centralized case.
       </paragraph>
       <paragraph>
        Stage3.5 — Completing RL single modelings: one of the main goals of this work is also validating DRL system benefits. And an interesting property of those kinds of systems is the flexibility to implement various algorithms or modelings independently by each individual agent. In this way, we have implemented a hybrid DRL scheme (DRL-Hybrid) with a Fuzzy Q-Learning (FQL) to learn {a mathematical formula}vl, in parallel with a SARSA(λ) algorithm to learn {a mathematical formula}aw. This is a good example for depicting Stage 3.5 of the proposed methodology. The continuous state but discrete actions RBF SARSA(λ) is adequate for learning the discrete angular acceleration. Meanwhile, the continuous state-action FQL algorithm is adequate for learning the continuous linear speed control action of the agent {a mathematical formula}vl. For simplicity, the DRL-Hybrid scheme is implemented with a greedy exploration policy, the same previously mentioned joint state vector, and 3 bins in the action space. It is also important to mention that any kind of MA coordination or algorithm (e.g., DRL-Lenient or DRL-CA) is implemented for this scheme.
       </paragraph>
       <paragraph>
        In summary, we have the following implemented schemes for the Ball-Pushing problem: CRL, DRL-Ind, DRL-CAdec/CAinc/Lenient, and DRL-Hybrid. Please see Table 1 for the full list of acronyms. Other details about Stage 3.5 are detailed in the next two subsections. Implementation and environmental details have been already mentioned in the centralized modeling description, because most of them are common with the decentralized modeling.
       </paragraph>
      </section>
      <section label="5.2.3">
       <section-title>
        Performance index
       </section-title>
       <paragraph>
        The evolution of the learning process is also evaluated by measuring and averaging 25 runs. The percentage of scored goals across the trained episodes is considered as the performance index: {a mathematical formula}%of Scored Goals=scoredGoals/Episode, where scoredGoals are the number of scored goals until the current training Episode. Final performance is also measured by running a thousand episodes again with the best policy (among 25) obtained per each scheme tested.
       </paragraph>
      </section>
      <section label="5.2.4">
       <section-title>
        RL algorithm and optimized parameters
       </section-title>
       <paragraph>
        An RBF SARSA(λ) algorithm with softmax action selection is implemented for these experiments. The Boltzmann exploration temperature is decayed as: {a mathematical formula}τ=τ0exp⁡(−dec⋅episode/maxEpisodes), where episode is the current episode index and {a mathematical formula}maxEpisodes=1000 trained episodes per run. Thus, the following parameters are optimized: the learning rate (α), the eligibility traces decay factor (λ), the Boltzmann exploration initial temperature ({a mathematical formula}τ0), and the exploration decay factor (dec). For the particular case of Lenient RL, the gain (κ) and decay factor (β) are optimized instead of {a mathematical formula}τ0 and dec respectively. Obtained values after optimizations are listed in Table 1. Additionally, the number of discrete actions for the linear velocity are optimized obtaining {a mathematical formula}Nvl=5 for the CRL scheme, and {a mathematical formula}Nvl=7 for the DRL-Ind. For all the experiments {a mathematical formula}γ=0.99.
       </paragraph>
      </section>
      <section label="5.2.5">
       <section-title>
        Physical setup
       </section-title>
       <paragraph>
        An experimental setup is implemented in order to test learned policies onto a physical setup, which is shown in Fig. 5 (right). The Miabot Pro is connected wirelessly to a central computer close to the robot soccer platform which measures {a mathematical formula}1.5m×1m. A web camera above the platform provides the positions and orientations of the robot, ball, and goal. The state observation is processed from the vision system, while the speed of the wheels is transmitted through Bluetooth from the computer. These speeds are computed from the Q tables by using a greedy search policy.
       </paragraph>
      </section>
      <section label="5.2.6">
       <section-title>
        Results and analysis
       </section-title>
       <paragraph>
        Fig. 6 presents learning evolution plots and Table 4 shows the best policy final performances. All the DRL systems implemented improved the {a mathematical formula}%ofScoredGoals of the centralized one as in the learning evolution traces (Fig. 6), as well as in the final performance test (Table 4). Except from the Incremental Cooperative Adaptive implementation, DRL-CAinc, the DRL implementations accelerated the learning time of the CRL scheme. Although DRL-CAinc achieves better performances than CRL after episode 500, the slower learning of the DRL-CAinc can be explained by taking the incremental cooperative adaptation effect into account, which updates the Q function conservatively during early episodes in which the agents do not have good policies. The hybrid SARSA+Fuzzy-Q-Learning decentralized implementation, DRL-Hybrid, shows the fastest asymptotic convergence, evidencing the feasibility of using decentralized systems with various algorithms and/or modelings for each individual agent, which means flexibility, property indicated in Section 2.3 and described in Stage 3.5. The Decremental Cooperative Adaptive implementation, DRL-CAdec, obtains the best final performance and the second fastest asymptotic convergence, followed closely by the DRL-Lenient scheme, and the independent and no coordinated DRL-Ind implementation. Note that coordinated DRL schemes (CA and Lenient) do not show considerable outperforming or accelerating with respect to the DRL-Ind implementation. This is an interesting point to analyze and discuss in the following sections, taking the previous results of the 3DMC problem into account, and the fact that this particular problem also uses two agents with full observability of the joint state space.
       </paragraph>
       <paragraph>
        As was mentioned in Section 5.2, the number of discretized actions for the linear velocity was optimized, obtaining {a mathematical formula}Nvl=5 for the CRL scheme, and {a mathematical formula}Nvl=7 for the DRL-Ind. So, total discrete actions are: {a mathematical formula}NT=NvlNaw=15 for the CRL scheme, and {a mathematical formula}NT=7+3 for the DRL-Ind. Note that the DRL-Ind implementation allows a finer discretization than the CRL. For the CRL, increasing the number of actions of {a mathematical formula}vl from 5 to 7 implies increasing the joint action space from 15 to 21 actions, taking into account {a mathematical formula}Naw=3 (please check Table 3), which implies an exponential increase in the search space that could increase learning time, thus affecting the final performance since only 1000 episodes were trained. Although the DRL-Ind scheme uses more discrete actions for {a mathematical formula}vl, its search space is still smaller than the CRL combined one. This is one of the interesting properties of decentralized systems, which is validated by these optimization results. Since the agents are independent, separate modelings or configurations can be implemented per agent. Additionally, in order to perform a fair comparison of computing time, we have also carried out a second evaluation, implementing and testing a DRL system with {a mathematical formula}Nvl=5 actions. Once again, we have measured simulation times and action-selection+Q-function-update times, obtaining 59.63 s for the CRL (12.47% of the global time), and 59.67 for the DRL scheme (15.11% of the global time). However the DRL five actions final performance was 68.97%, still higher than the 57.14% of its CRL counterpart, although lower than the 75.28% of the DRL with {a mathematical formula}Nvl=7 actions.
       </paragraph>
       <paragraph>
        The best CRL and DRL-Ind learned policies are transferred and tested in the experimental setup. The results from experiments with the physical robot are also presented in Table 4, in which performance is presented in percentages of success at scoring a goal within the seventy attempts. Cases where the mark of the robot was lost in the vision system were disregarded.
       </paragraph>
       <paragraph>
        In Table 4 it is observed that DRL-Ind performs on average 11.43% better than CRL. Simulation and physical setup performances are similar, which validates the simulation experiments and results. Some experiments for centralized and decentralized RL were recorded and can be seen online at Leottau's video repository [50]. In this video actions are a bit abrupt as it can be seen, due to no smoothing or extrapolation of the discrete actions where carried out, policies were transferred directly from Q functions to the physical robot. Also, cases where the mark of the robot or some tracker was lost in the vision system were disregarded. These aspects should be improved for future implementations, however, the purpose of this experiments is more focused on comparing CRL and DRL approaches, than on achieving an optimal performance.
       </paragraph>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Ball-dribbling
      </section-title>
      <paragraph>
       Ball-dribbling is a complex behavior during which a robot player attempts to maneuver the ball in a very controlled way, while moving toward a desired target. In the case of biped robots the complexity of this task is very high, because it must take into account the physical interaction between the ball, the robot's feet, and the ground. Thus, the action is highly dynamic, non-linear, and influenced by several sources of uncertainty. Fig. 7 (left) shows the RoboCup SPL soccer environment where the NAO humanoid robot [14] is used. As proposed by Leottau et al. [25], the description of this dribbling behavior uses the following variables: {a mathematical formula}[vx,vy,vθ], the velocity vector; γ, the robot-ball angle; ρ, the robot-ball distance; and, ϕ, the robot-ball-target complementary angle. These variables are shown in Fig. 7 (right), where the global coordinate system is {a mathematical formula}OG, the desired target (⊕) is located in the middle of the opponent's goal, and a robot's egocentric reference system is indicated with the {a mathematical formula}xr axis pointing forwards.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Proposed decentralized modeling
       </section-title>
       <paragraph>
        Stage3.1 — Determining if the problem is decentralizable: since the requested velocity vector of the biped walk engine is {a mathematical formula}[vx,vy,vθ], it is possible to decentralize this 3-Dimensional action space by using three individual agents, {a mathematical formula}Agentx, {a mathematical formula}Agenty, and {a mathematical formula}Agentθ.
       </paragraph>
       <paragraph>
        Stage3.2 — Identifying common and individual goals: our expected common goal is to walk fast toward the desired target while keeping possession of the ball. That means: to maintain {a mathematical formula}ρ&lt;ρth; to minimize {a mathematical formula}γ,ϕ,vy,vθ; and to maximize {a mathematical formula}vx. In this way, this Ball-Dribbling behavior can be separated into three sub-tasks or individual goals, which have to be executed in parallel: ball-turning, which keeps the robot tracking the ball-angle {a mathematical formula}(γ=0); alignment, which keeps the robot aligned to the ball-target line {a mathematical formula}(ϕ=0); and ball-pushing, whose objective is for the robot to walk as fast as possible and hit the ball in order to change its speed, but without losing possession of it. So, the proposed control actions are {a mathematical formula}[vx,vy,vθ] respectively involved with ball-pushing, alignment, and ball-turning.
       </paragraph>
       <paragraph>
        Stage3.3 — Defining the reward functions: the proposed dribbling modeling has three well-defined individual goals, ball-pushing, alignment, and ball-turning. Thus, individual rewards are proposed for each agent as:{a mathematical formula} where {a mathematical formula}[ρth,γth,ϕth] are desired thresholds at which the ball is considered to be controlled, while {a mathematical formula}vx.max′ reinforces walking forward at maximum speed. Fault-state constraints are set as: {a mathematical formula}[ρth,γth,ϕth]=[250mm,15°,15°], and {a mathematical formula}vx.max′=0.9vx.max. This is a good example for depicting how and why to define individual rewards; for instance, since only {a mathematical formula}Agentx involves {a mathematical formula}vx for the ball-pushing sub-task, {a mathematical formula}Agenty, and {a mathematical formula}Agentθ reward functions do not include this variable. Since alignment, and ball-turning strongly involve γ and ϕ, {a mathematical formula}Agenty and {a mathematical formula}Agentθ rewards consider more accurate thresholds for these angles, {a mathematical formula}γth/3,ϕth/3 and ρ is also not considered.
       </paragraph>
       <paragraph>
        Stage3.4 — Determining if the problem is fully decentralizable: since the three state variables, {a mathematical formula}[ρ,γ,ϕ] of the joint vector state are required, this problem is not considered to be fully decentralizable. So, the proposed modeling for learning the 3-Dimensional velocity vector from the joint observed state is detailed in Table 5.
       </paragraph>
      </section>
      <section label="5.3.2">
       <section-title>
        Centralized modeling
       </section-title>
       <paragraph>
        Since 17 discrete actions per agent are implemented for the DRL system, if an equivalent CRL system were implemented, that centralized agent would search in an action space of {a mathematical formula}173=4913 possible actions, which would be enormous for most of the RL algorithms. Even though we tried to reduce the number of discrete actions, the performance decreased dramatically. Finally, the only way to achieve asymptotic convergence was using a noiseless model in which observations were taken from the ground truth system. Thus, this CRL implementation is only for academic and comparison purposes. Discrete actions must have been reduced up to five per action dimension, i.e. a {a mathematical formula}53=125 combined action space. The same joint state vector was used and the global reward function is similar to {a mathematical formula}rx in (11), but using {a mathematical formula}γth/3 and {a mathematical formula}ϕth/3.
       </paragraph>
       <paragraph>
        Stage3.5 — Completing RL single modelings: the Ball-Dribbling DRL procedure is carried out episodically. After a reset, the robot is set in the center of its own goal (black right arrow in Fig. 7 (right)), the ball is placed {a mathematical formula}ρthmm in front of the robot, and the desired target is defined in the center of the opponent's goal. The terminal state is reached if the robot loses the ball, if the robot leaves the field, or if the robot crosses the goal line and reaches the target, which is the expected terminal state. The training field is {a mathematical formula}6×4 meters. In order to compare our proposed methods with similar state-of-the-art works, three additional schemes, previously reported in the literature, are included:
       </paragraph>
       <list>
        <list-item label="–">
         {a mathematical formula}DRL+Transfer, a DRL system accelerated by using the Nearby Action-State Sharing (NASh) knowledge transfer approach proposed by Leottau and Ruiz-del-Solar [26]. NASh is introduced for transferring knowledge from continuous action spaces, when no information different from the suggested action in an observed state is available from the source of knowledge. In the early training episodes, NASh transfers actions suggested by the source of knowledge but progressively explores its surroundings looking for better nearby actions for the next layer.
        </list-item>
        <list-item label="–">
         RL-FLC method introduced by Leottau et al. [25], which proposes a methodology for modeling dribbling behavior by splitting it in two sub problems: alignment, which is achieved by using an off-line tuned fuzzy controller, and ball-pushing, which is learned by using an RL based controller reducing the state vector only to ρ. These strategies reduce the complexity of the problem making it more tractable and achievable for learning with physical robots. The RL-FLC approach was the former dribbling engine used by the UChile Robotics Team [55] in the RoboCup [51] Standard Platform League (SPL) soccer competition.
        </list-item>
        <list-item label="–">
         eRL-FLC proposed by Leottau et al. [27], is an enhanced version of the RL-FLC which learns the ball-pushing sub-task mapping the whole state space {a mathematical formula}[ρ,γ,ϕ] by using a Layered RL approach. It is designed to improve ball control because the former RL-FLC approach assumes the ideal case in which the target, ball, and robot are always aligned, ignoring {a mathematical formula}[γ,ϕ] angles, which is not the case during a real game situation. However, as in RL-FLC, the alignment sub-task must still be learned off-line, resigning optimal performances instead of reducing modeling complexity.
        </list-item>
       </list>
       <paragraph>
        In summary, for implemented schemes for the Ball-Dribbling problem, we have: DRL-Ind, DRL-CAdec/CAinc/Lenient, DRL+Transfer, CRL, RL-FLC, and eRL-FLC. Please see Table 1 for the full list of acronyms. Other details about Stage 3.5 are detailed in the next two subsections.
       </paragraph>
      </section>
      <section label="5.3.3">
       <section-title>
        Performance indices
       </section-title>
       <paragraph>
        The evolution of the learning process is evaluated by measuring and averaging 25 runs. The following performance indices are considered to measure dribbling-speed and ball-control respectively:
       </paragraph>
       <list>
        <list-item label="–">
         % of maximum forward speed{a mathematical formula}(%SFmax): given {a mathematical formula}SFavg, the average dribbling forward speed of the robot, and {a mathematical formula}SFmax, the maximum forward speed: {a mathematical formula}%SFmax=SFavg/SFmax. {a mathematical formula}%SFmax=100% is the best performance.
        </list-item>
        <list-item label="–">
         % of time in fault-state{a mathematical formula}(%TFS): the accumulated time in fault-state{a mathematical formula}tFS during the whole episode time {a mathematical formula}tDP. The fault-state is defined as the state when the robot loses possession of the ball, i.e. {a mathematical formula}ρ&gt;ρth∨|γ|&gt;γth∨|ϕ|&gt;ϕth, then: {a mathematical formula}%TFS=tFS/tDP. {a mathematical formula}%TFS=0 is the best performance.
        </list-item>
        <list-item label="–">
         Global Fitness (F): this index is introduced for the sole purpose of evaluating and comparing both performance indices together. The global fitness is computed as follows: {a mathematical formula}F=1/2[(100%SFmax)+%TFS], where {a mathematical formula}F=0 is the optimal but non-reachable policy.
        </list-item>
       </list>
      </section>
      <section label="5.3.4">
       <section-title>
        RL algorithm and optimized parameters
       </section-title>
       <paragraph>
        A SARSA(λ) algorithm with softmax action selection is implemented for these experiments. The Boltzmann exploration temperature is decayed as: {a mathematical formula}τ=τ0exp⁡(-dec⋅episode/maxEpisodes), where episode is the current episode index and {a mathematical formula}maxEpisodes=2000 trained episodes per run. As a result, the following parameters are optimized: learning rate (α), Boltzmann exploration initial temperature ({a mathematical formula}τ0), and exploration decay factor (dec). For the particular case of Lenient RL, gain (κ) and decay factor (β) are optimized instead of {a mathematical formula}τ0 and dec respectively. This can be considered as the last stage of the methodology, Stage3.5Completing RL single modelings. For all the experiments {a mathematical formula}γ=0.99.
       </paragraph>
      </section>
      <section label="5.3.5">
       <section-title>
        Results and analysis
       </section-title>
       <paragraph>
        Fig. 8 shows learning evolution plots for: an independent decentralized learners scheme, DRL-Ind; a Decremental Cooperative Adaptive scheme, DRL-CAdec; a lenient DRL implementation; and, a DRL system accelerated with transfer knowledge, DRL+Transfer, and a centralized scheme, CRL. Plots for the Incremental Cooperative Adaptive, DRL-CAinc scheme are not included because of their poor performance and high standard error bars. Table 6 shows averaged final performances. Although CRL implementation was modeled with only 5 actions per dimension, the DRL-ind scheme which uses 17 actions per dimension has been more than 22% faster. Besides, the CRL has used a noiseless model with ground truth observations, even so DRL outperforms it by almost 12% using a more realistic model. The DRL+Transfer implementation uses a source of knowledge with an initial performance at about 25% (see [26]), achieving a final performance near 16% after the RL transfer procedure. DRL-Lenient and DRL-CAdec approaches are able to reach a similar final performance, approximately 18% and 20% learning from scratch without any kind of previous knowledge. The Lenient approach presents the best results, the best final performance, and the fastest asymptotic convergence among the implemented methods with no transfer knowledge. The DRL-CAdec outperforms the DRL-Ind scheme, and also takes 201 less episodes to reach the defined time to threshold (35%). Plots for forward speed and fault performance indexes are also included in order to follow the same results format as Leottau and Ruiz-del-Solar [26], in which this dribbling problem was originally proposed based on a DRL modeling. Note that the main benefit of MAS based algorithms (Lenient and CAdec) versus the DRL-Ind scheme is to achieve a higher forward speed, keeping a low rate of faults.
       </paragraph>
       <paragraph>
        The effectiveness and benefits of the RL-FLC and eRL-FLC approaches have been pointed out by Leottau et al. [27]. However, significant human effort and knowledge from the controller designer are required for implementing all the proposed stages. DRL approaches are able to learn the whole Ball-Dribbling behavior almost autonomously, achieving best performances compared to those of the RL-FLC and eRL-FLC which require more human effort and previous knowledge. An advantage of the RL-FLC and eRL-FLC methods is the considerably lower RL training time, with regard to all the DRL systems (please see time to thresholds in Table 6). The DRL-Lenient and DRL-CA schemes proposed in this work are able to reduce the learning time down to 585 and 771 episodes respectively, opening the door to making future implementations for learning similar behaviors achievable by physical robots.
       </paragraph>
       <paragraph>
        Some videos showing the learned policies for dribbling can be seen online at Leottau's video repository [24]. Currently the learned policy is transferred directly to the physical robots, thus, the final performance is dependent on how realistic the simulation platform is.
       </paragraph>
      </section>
     </section>
     <section label="5.4">
      <section-title>
       SCARA real-time trajectory generation
      </section-title>
      <paragraph>
       The Selective Compliance Articulated Robot Arm (SCARA) is used extensively in the industry for assembly tasks and small parts insertion, among the other uses. It has well-known properties and there is sufficient literature [29], [10]. This problem has been selected because it is one of the first DRL applications reported by Martin and De Lope [31]. Its simulation implementation is available online at Martin's repository [30] and it can be used as a test-bed for DRL systems.
      </paragraph>
      <paragraph>
       A simulated three dimensional robotic manipulator with four joints, in which the system tried to reach an objective configuration in a 3D space, was used, while being able to generate an approaching real-time trajectory when the system was completely trained. A diagram of the physical model of the SCARA-RTG problem is shown in Fig. 9. The Denavit–Hartenberg parameters, the direct kinematic matrix, and more implementation details can be checked in the paper of Martin and De Lope [31], and the source files can be downloaded from Martin's repository [30].
      </paragraph>
      <section label="5.4.1">
       <section-title>
        Decentralized modeling
       </section-title>
       <paragraph>
        Stage3.1 — Determining if the problem is decentralizable: since the SCARA arm has four joints, we can identify a 4-dimensional action space, and separate the problem into four individual agents: {a mathematical formula}Agent1,⋯,Agent4, or {a mathematical formula}Agentm, with {a mathematical formula}m=1,..,4. Five actions are implemented per agent, among which the four action spaces are identical, but act independently: {a mathematical formula}A1=A2=A3=A4=[−0.02;−0.01;0.0;0.01;0.02]. Selected action {a mathematical formula}[a1,⋯,a4] modifies the current angle in radians of each joint of the arm {a mathematical formula}[θ1,⋯,θ4]. Thus, {a mathematical formula}θ(t+1)m=θm+am.
       </paragraph>
       <paragraph>
        Since this problem is modeled with four agents and five discrete actions per agent, a centralized scheme is not implemented for this experiment because an action-space of {a mathematical formula}54=625 discrete actions is computationally expensive to our current resources and purposes.
       </paragraph>
       <paragraph>
        Stages3.2and3.3 — Identifying individual goals and defining reward functions: the common goal consists of reaching a continuously changing goal position of the robot end-effector by means of a random procedure. That way, a global reward function is implemented as Expression (12), where {a mathematical formula}eDist is the Euclidean distance between the current end-effector position and the goal position, and {a mathematical formula}θ2 is the joint angle {a mathematical formula}m=2 in degrees. In Martin's repository [30], this Euclidean distance based and continuous reward function is detailed and its effectively is validated.{a mathematical formula}
       </paragraph>
       <paragraph>
        Stage3.4 — Determining if the problem is fully decentralizable: three state variables compose the joint state vector{a mathematical formula}S=[ex,ey,ez], the error between the current end-effector position with respect to the 3-Dimensional goal position point {a mathematical formula}[xg,yg,zg]. Each state variable considers three values {a mathematical formula}[−1,0,1], depending if the error is negative, near to zero, or positive.
       </paragraph>
       <paragraph>
        Stage3.5 — Completing RL single modelings the learning procedure is defined as follows: goal positions are defined in such a way that they are always reachable for the robot; thus, the learning process needs to develop an internal model of the inverse kinematics of the robot which is not directly injected by the designer; through the different trials, a model of the robot inverse kinematics is learned by the system; when a goal position is generated, the robot tries to reach it; each trial can finish as a success episode, i.e. the robot reaches the target at a previously determined time, or as a failed episode, i.e. the robot is not able to adopt a configuration to reach the goal position before 400 time steps; in both cases the system parameters are updated using the previously defined method and a new goal position is generated randomly.
       </paragraph>
       <paragraph>
        In summary, we have the following implemented schemes for the SCARA-RTG problem: DRL-Ind, DRL-CAdec/CAinc/Lenient. Please see Table 1 for the full list of acronyms. Other details about Stage 3.5 are detailed in the next two subsections.
       </paragraph>
      </section>
      <section label="5.4.2">
       <section-title>
        Performance index
       </section-title>
       <paragraph>
        Time steps are considered as the performance index, where 400 is the maximum and worst case, and zero is the best but non-reachable performance.
       </paragraph>
      </section>
      <section label="5.4.3">
       <section-title>
        RL algorithm and optimized parameters
       </section-title>
       <paragraph>
        As Martin and De Lope [31] report, a SARSA tabular algorithm with ϵ-greedy is implemented for these experiments. The following parameters are optimized: learning rate (α) and exploration (ϵ), which is multiplied by 0.99 at the end of each learning episode. For the particular case of Lenient RL, gain (κ) and decay factor (β) are also optimized. For all the experiments {a mathematical formula}γ=1.
       </paragraph>
      </section>
      <section label="5.4.4">
       <section-title>
        Results and analysis
       </section-title>
       <paragraph>
        Fig. 10 shows learning evolution plots and Table 7 shows averaged final performances. The DRL-Lenient scheme shows the fastest asymptotic convergence and the best performance, followed closely by the Incremental Cooperative Adaptive DRL-CAinc implementation. Those schemes respectively outperform about 25 and 14 steps with respect to the original implementation presented by Martin and De Lope [31]. Note that DRL-Lenient reaches a performance of ≈230 in about 10 episodes, and the independent and non-coordinated scheme, DRL-Ind in 16 episodes. Further, due to the leniency effect during early episodes, which tries to avoid uncoordinated and ambiguous information among the interaction of the four agents, DRL-Lenient keeps improving its performance until the final episode. There is a similar lenient effect in the case of DRL-CAinc; reaches the 230 performance threshold in about 25 episodes, on average 15 and 9 episodes slower than DRL-Lenient and DRL-Ind respectively. However, DRL-CAinc shows a comparable performance with respect to the Lenient after that and also shows the tendency to keep improving its performance during the learning procedure.
       </paragraph>
      </section>
     </section>
     <section label="5.5">
      <section-title>
       Discussion
      </section-title>
      <paragraph>
       Our first goal is demonstrating empirically that an independent DRL system is able to achieve similar learning times and comparable or slightly lower performances (because of lack of coordination) compared to CRL schemes. Thus, a trade-off between DRL benefits indicated in Section 2.3 and performance may be expected. Experiments of 3DMC and Ball-Pushing were the first presented. Results for those two problems have evidenced surprisingly that DRL-Ind implementations show better performances and faster learning times than their CRL counterparts. Only in the case of 3DMC, the DRL-ObsL-Ind approach shows a lower final performance, which was expected when taking into account that complex scenario with lack of coordination and limited observability. Nevertheless, the DRL-ObsL-Ind approach should be compared with a CRL-ObsL implementation for an equitable comparison; however, this CRL implementation with limited observability is simply non-feasible because the CRL scheme does not support incomplete observations. All the same, as is demonstrated in Subsection 5.1, our proposed MAL algorithms (Lenient and CA) are able to resolve that issue. Furthermore, implementations with these MAL algorithms also showed better or comparable averaged performances and faster learning times compared with CRL implementations. Only in the ball-pushing case, DRL-CAinc shows slower convergence than CRL. This result, however, is because of the nature of CA: DRL-CAinc and DRL-CAdec can be mutually exclusive in certain cases, as was introduced in Section 4.3 and discussed below. In short, thirteen different DRL implementations have been implemented and compared with their CRL counterparts for these two initially discussed problems: eight for the 3DMC and five for the Ball-Pushing. Eleven of those thirteen DRL implementations have evidenced better or comparable averaged performances as well as faster asymptotic convergences when compared to their CRL counterparts, one has shown faster convergence but lower final performance, and one has shown better performance but slightly slower asymptotic convergence.
      </paragraph>
      <paragraph>
       Two more MA algorithms have been presented, Lenient and Cooperative Adaptive Learning Rate, which have been considered in order to include a coordination mechanism among decentralized agents learning in parallel. The effects of these algorithms are mentioned briefly below in general terms:
      </paragraph>
      <list>
       <list-item label="–">
        For DRL-Lenient, leniency helps the agents to explore and find a partially coordinated joint policy before starting to update the action-value function. Since no communication among the agents is performed, and they modify their action-selection mechanisms, a coordinated policy is achieved indirectly. The agents visit relevant states repetitively, searching for the best individual actions, which accomplishes a desired joint behavior; meanwhile, action-value functions are updated gradually once the agents' visit states are known.
       </list-item>
       <list-item label="–">
        For DRL-CAinc/dec, a measure of the current quality of each individually performed action is communicated among the agents; then, a joint adaptive learning rate is computed according to the “worst” agent. If the CAinc approach is performed, a similar lenient effect occurs, and each individual action-value function is updated with that cooperative adaptive learning rate, thereby increasing the learning rate while a joint policy is improved during the learning process. Otherwise, if CAdec is used, the agents try to collect information during the early learning process, thereby decreasing the learning rate while a joint policy is learned.
       </list-item>
      </list>
      <paragraph>
       The benefits of the Lenient and CA algorithms are more noticeable in those implementations of the 3DMC with limited observability, in which the DRL-ObsL-Ind scheme without coordination did not achieve a stable final performance. This particular case is highly complex because the actions of each agent affect the joint environment and next state observation for both agents directly, and not even free or indirect coordination occurs. However, Lenient and CA schemes were able to resolve that issue. As was mentioned in Section 5.1, this 3DMC problem with ObsL presents different state spaces, decentralized action spaces, and individual reward functions. So, by using our proposed MA algorithms, with their indirect coordination and communication among agents of the CA approaches, an equilibria can be found for every state which is visited along a successful path enough times to achieve the mountaintop.
      </paragraph>
      <paragraph>
       Lenient and CA algorithms have evidenced the best averaged final performances for the four tested problems. These methods outperformed their DRL-Ind counterparts implemented without coordination in all the problems tested. The two best averaged performances per problem are listed in Table 8. DRL-Lenient is the most recurrent winning approach, appearing in all five cases. Lenient benefits are particularly remarkable in the Ball-Dribbling and SCARA-RTG problems, where it achieves both the best performance and the fastest asymptotic convergence. According to the results, the benefits of the proposed MAS methods are more noticeable as the problem complexity increases — such as occurs in the 3DMC ObsL and Ball-Dribbling cases — in which a CRL scheme was intractable according to our available computational resources.
      </paragraph>
      <paragraph>
       Note in Table 8 that DRL-CAdec and DRL-CAinc never appear together as the best approaches. This verifies that DRL-CAinc and DRL-CAdec can be mutually exclusive for certain cases due to their inverse variable learning rates policy. For instance, DRL-ObsF-CAdec is the best, and DRL-ObsF-CAinc is the worst, in the 3DMC with full observability and Ball-Dribbling cases; and DRL-CAinc is the second best, and DRL-CAdec is the worst, in the SCARA-RTG case. As a preliminary and empirical hypothesis about DRL-CAxxx methods, it can be said that the DRL-CAinc method potentiates its benefits on learning problems implemented with the ϵ-greedy action-selection mechanism, but shows poor performances on problems implemented with softmax action selection. On the other hand, the DRL-CAdec method potentiates its benefits on learning systems implemented with a softmax action-selection strategy. Of course this is just an empirical conclusion which must be validated with more problems in future studies. Also, note in Fig. 4, Fig. 5, Fig. 6, Fig. 7, Fig. 8, Fig. 9, Fig. 10 that DRL-CAxxx approaches do not usually obtain the fastest asymptotic convergences, and as such it is possible to conclude that accelerating learning is not a strength of those methods.
      </paragraph>
      <paragraph>
       For the sake of simplicity, we have used a unique set of RL parameters for each of the DRL implemented problems. If we had optimized individual sets of parameters per each individual agent, results may have been outperformed for those DRL schemes in which the agents are heterogeneous such as ball-pushing and dribbling.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Optimization procedure
     </section-title>
     <paragraph>
      As it was mentioned, RL parameters like learning rate, eligibility traces, exploration factor, number of discrete actions, number of cores, are optimized by using a customized version of the hill-climbing method. This is a very important step in order to guarantee that every scheme tested uses the best parameter settings. In this way our comparisons and evaluations are carried out based on the best performance potentially achievable by each method, according to our optimization results. Before each set of optimizations, we try to achieve a good set of parameters by hand-tuning, such as seed, and then we determined the quantity of learning episodes empirically procuring asymptotic convergence for 2/3 of the total trained episodes.
     </paragraph>
     <paragraph>
      The relative simplicity and fast convergence of hill climbing algorithm make it one of the most popular algorithms for finding the best set of parameters in RL [3], [5], [34], [46]. However, since only local optima are guaranteed, we have implemented some variants to cure that without evaluating too much extra trials. In this way three ideas are included: to evaluate more than one neighbor per parameter dimension; the option of evaluating one neighbor per dimension or exploring the same dimension until finding the best evaluation; and to store every evaluated set of parameters in order to avoid repeated trials. The pseudo-code is detailed in Algorithm 4, where paramListV is a structure which stores every parameter combination and its respective evaluation value. We have used {a mathematical formula}neighbors=4 and oneDimPerTry enabled for all the experiments in this work. The source code is also shared on-line at Leottau's code repository [23].
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>