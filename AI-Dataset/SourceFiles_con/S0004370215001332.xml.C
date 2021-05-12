<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    An extension of metric temporal planning with application to AC voltage control.
   </title>
   <abstract>
    In this paper we explore the deployment of planning techniques to solve a new class of metric temporal planning problems, characterised by the need to manage both plan trajectory constraints and uncontrollable numeric events. This combination gives rise to challenges not previously solved in state-of-the-art planners. We introduce new planning methods to handle these challenges, and demonstrate our approach using a real application domain: voltage control in Alternating Current (AC) electrical networks. Embedding electricity networks in a domain description presents important modelling challenges. We introduce an encapsulated type, Network, the implementation of which is hidden from the planner. The effects of actions trigger complex updates to the state of the network. We distinguish between the direct effects of planned actions, and the indirect effects triggered by them, and we propose a method for integrating a specialised external AC power equation solver with a planner. We consider a new heuristic function that takes into account the next uncontrollable event, and its interaction with active trajectory constraints, when determining the actions that are helpful in a state. This lookahead heuristic also exploits an abstraction of the encapsulated Network type to obtain more informative distance estimates. We conduct experiments to evaluate the benefits of the lookahead heuristic, showing that our approach scales very well with the size of the network and the number of controllable components of the network.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In this paper we introduce a general class of metric temporal planning problems characterised by the presence of timed numeric events. Here we present, in detail, the treatment of a specific example: the management of voltages over time, within an AC power system, given predicted patterns of demand and generation. We use AI planning as a general framework to tackle the temporal voltage control problem in an active distribution network.
     </paragraph>
     <paragraph>
      AI planning is the branch of AI that is concerned with finding a sequence of activities to reach a given goal. In this context, given a distribution network and the predicted future demand and generation profiles, AI planning is used to decide which operations to apply to the power system, at what times, to maintain the voltage within the desired bounds. The operations that can be applied include changing transformer tap settings, turning capacitors on and off, ramping generation and other operations on network components. The problem of voltage control has several features that present new challenges to AI planning. The voltage, and other physical quantities involved, are subject to variability in the electrical output. When operations are applied locally, effects propagate globally across the entire network. This incurs a substantial computational burden and requires extensions to existing metric temporal planning languages and methods.
     </paragraph>
     <paragraph>
      We base our work upon the partially-ordered forward temporal planning framework of popf2[1], [2]. In this framework, the planner maintains a linear program consisting of temporal and metric constraints, and it can delay commitment to the ordering of actions in the plan head until the constraints enforce ordering decisions. This allows planned actions to be timed with respect to numeric events. We extend popf2 to support improved search in the presence of numeric events expressed as Timed Initial Fluents (TIFs). To handle the global propagation of non-linear effects, we connect our planner to an external solver that performs AC power flow calculations. The resulting modular planner is called popf-tif[3].
     </paragraph>
     <section label="1.1">
      <section-title>
       Map of content
      </section-title>
      <paragraph>
       The paper is organised as follows. Section 2 motivates our problem and highlights our contributions. Section 3 discusses related methods for managing AC power flow, explored in the literature. Section 4 defines a new class of metric temporal problems representing one dimension of the AC voltage control problem. In Section 5 we present the necessary fundamentals of power systems, with emphasis on the voltage control problem for distribution systems. This leads to the identification of a second dimension to our problem, and motivates the need for attachment to an external solver which is then described in Section 6. In Section 6 we also describe our (extended) pddl model of the AC voltage control problem. Section 7 describes our approach to solving the two dimensions of the problem.
      </paragraph>
      <paragraph>
       The results of our experiments are presented in Section 8, where we solve the voltage control problem for different distribution networks and we examine the scalability of our approach. We also compare our approach with a modern reactive control strategy that is used in industrial power systems management.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Motivation and contributions
     </section-title>
     <paragraph>
      Power Systems are nationwide infrastructures that supply electrical energy to consumers over large geographical areas in real time [4]. Before reaching the consumers, the electricity needs to be generated, transmitted and distributed. Decisions about which generators to use, over which time periods and at what levels of output, are determined centrally, in line with predicted consumer demand, market forces and other pressures.
     </paragraph>
     <paragraph>
      In the future, fundamental changes are anticipated, as a consequence of environmental, political and economic considerations, global warming, population and load growth and increased dependence on imports. A shift in technology and operational philosophy is expected, in response to an increased penetration of renewables, the electrification of transport and heating and a new role for the consumer, who will actively participate in managing the network.
     </paragraph>
     <paragraph>
      In order to deal with the increase in complexity, one technique that can be adopted is to decompose the entire power network into smaller zones[5]. A zone is a physically connected collection of power elements, chosen to be strongly self-contained in terms of the effects of actions applied to those elements, and largely unaffected by the effects of the same control actions applied to elements outside the zone boundaries. The reduced complexity of the zones allows the application of AI planning, and other pro-active techniques, to manage the operations inside them, considering temporal and metric constraints.
     </paragraph>
     <paragraph>
      In the electricity network there are different elements such as busbars, lines, generators, transformers and loads and several numeric quantities that must be reasoned about. Busbars are metal connecting components, linking elements of the electrical network. The most important numeric quantities are voltages and phase angles on the busbars, power and current. Changes to these quantities are effected by stepping transformers up and down, ramping generators up and down, shedding load, and other actions. These actions take time to achieve their full effects. Choosing and coordinating actions to achieve desired effects in the network over time is a challenging temporal and numeric planning problem.
     </paragraph>
     <paragraph>
      The AC voltage control problem is one aspect of the autonomous management of an electricity network. In addressing this problem we face new issues for planning. The domain is characterised by local actions (such as stepping up a transformer) that have global effects and non-linear numeric effects. Furthermore, all planning must take place against background demand curves, which describe how the load and supply at each node of the network vary over time. These predictions are based on historical data. These curves can be represented as discretised sequences of timed events, specified in the initial state, each event describing how the load and generation changes at a time point.
     </paragraph>
     <paragraph>
      The AC voltage control domain is also characterised by the presence of trajectory constraints, since the voltages at all of the network busbars must be maintained within a safe range over the entire period of the plan. The voltage trajectory constraint holds over the whole plan, while other constraints, such as thermal constraints, must generally be maintained, but may be relaxed over windows of time during the plan.
     </paragraph>
     <section label="2.1">
      <section-title>
       New challenges for planning
      </section-title>
      <paragraph>
       In the AC voltage control domain, the behaviours of the numeric quantities are affected by every single element of the network. This implies that every time we change a parameter of the network, the numeric effects propagate all over the system. The planning task is to serve a given demand, maintaining the balance between the power generated and the power consumed and satisfying other constraints on the voltages of the busbars and the power flowing into the lines. An important difference between this and the benchmark domains considered so far in planning, is that the calculation of the numeric quantities requires the solution of a set of non-linear (in this case, power flow) equations. This calculation needs to be performed every time a change in the system occurs and it affects every element of the system.
      </paragraph>
      <paragraph>
       We propose that the features that characterise the AC voltage control problem are common to a class of interesting temporal and numeric problems which currently lies outside the scope of other pddl temporal and numeric planners. The planner popf-tif was developed to solve challenging problems in this class. We identify two dimensions to this class of problems: the management of background events and their interaction with trajectory constraints, and the management of global propagation of effects. These dimensions are separately characterised in Sections 4 and 6.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Contributions
      </section-title>
      <paragraph>
       The key contributions of the paper are to:
      </paragraph>
      <list>
       <list-item label="1.">
        introduce a new class of metric temporal planning problems, in which the effects of actions interact with background events and trajectory constraints;
       </list-item>
       <list-item label="2.">
        extend the syntax of pddl2.2 to allow the specification of Timed Initial Fluents (TIFs), encapsulated types, and an external solver interface;
       </list-item>
       <list-item label="3.">
        develop a novel, informative heuristic method that looks ahead over TIFs to take background events into account;
       </list-item>
       <list-item label="4.">
        present the planner popf-tif, which handles all of the new syntactic features and can solve problems currently unsolvable by other planners;
       </list-item>
       <list-item label="5.">
        demonstrate a temporal planning-based method for AC voltage control over time, for active distribution networks, and investigate the scalability of its features.
       </list-item>
      </list>
     </section>
    </section>
    <section label="3">
     <section-title>
      Related work in power systems
     </section-title>
     <paragraph>
      AI Planning has already been applied to problems involving distribution networks. For example, Bell et al. [6], present an application of planning to managing voltage control in a power station. Restricting attention to a power substation, without the presence of generators, and considering only a small portion of the distribution network, allowed some simplifications of the effects of the other numeric quantities on the voltage. In practice, the constraints imposed by the Equations (2), in Section 5, are not considered, while it is assumed that each variation in consumed power leads to a constant effect on the voltage. In the work of Cao et al. [7] an entire distribution network is considered. In this case the power flow equations cannot be ignored, but they are not implemented directly in the planner. The authors adopt a linearisation of the effects of power flow in the planning model and only after the planner finds a solution, is it verified against the power flow equations. In case the solution is not valid, the model is modified with refined values and re-solved.
     </paragraph>
     <paragraph>
      Another example of the use of AI Planning in Power Systems is the Power Supply and Restoration (PSR) domain [8]. In that work the authors consider a distribution network and the objective is to maximise the load connected to the generators without passing through a faulty line. In that case the power flow equations are not considered and the domain is expressed entirely using propositional variables.
     </paragraph>
     <paragraph>
      More recent work on the PSR problem, by Thiébaux et al. [9], formulates the problem as a mixed integer program (MIP) exploiting the use of a Direct Current (DC) simplification of the power flow equations.
     </paragraph>
     <paragraph>
      An approach to optimising power flow in microgrids, which considers the power flow equations, can be found in a later work of Scott and Thiébaux [10]. This work uses better approximations than the DC simplification. To optimise the efficiency of the network, they use the Alternating Direction Method of Multipliers (ADMM), which is a refinement of the use of Lagrangian multipliers. This approach was also used for a similar purpose by Phan and Kalagnanam [11]. The resulting optimisation problem is solved using a combination of linear and non-linear solution methods. In these problem formulations, voltage is not controllable but instead imposes constraints on the power flow.
     </paragraph>
     <paragraph>
      Work by Tischer et al. [12] addresses the problem of demand response within a power flow model. This impacts on voltage control, but is not the same problem. Consumers are modelled as participants who will change their own behaviour in response to financial and comfort considerations. Real time pricing signals are used to drive consumer behaviour towards optimal power flow distributions.
     </paragraph>
     <paragraph>
      Coffrin et al. [13] introduce a more sophisticated approximation of the power flow equations using a Linear Programming Approximation of the AC Equations. Here, the non-linearity of the AC power flow equations is overcome by using a piecewise-linear approximation of the cosine. In this formulation, the values of active and reactive power can be decision variables and the model can be embedded in a MIP solver for making discrete decisions about the power system. The weakness of this formulation comes from the non-linear behaviour of transformers, that introduces a loss of accuracy in the power flow calculations.
     </paragraph>
     <paragraph>
      The problem of power management within buildings has been addressed as a temporal plan execution problem by Ono et al. [14]. The plan manages the control of a Heating, Ventilation and Air Conditioning (HVAC) system to satisfy temporal constraints imposed by the occupants of the building. The plan respects a measure of risk associated with a probabilistic model of occupancy.
     </paragraph>
     <paragraph>
      A possible approach to the active management of networks is to formulate the problem as a constraint satisfaction problem (CSP), as presented in the work of, for example, Davidson et al. [15]. In this work the control variables determine the outputs of a set of generators, which have discretised domains. Contractual and preference constraints are taken into account. Although this approach produces feasible solutions for quite small problems, for larger networks the combinatorial size of the network and the absence of a heuristic evaluation to guide the search, limit the possible applications. Moreover, the authors consider single instants of time, and temporal constraints are not addressed.
     </paragraph>
     <paragraph>
      While CSP and SAT-based approaches, including CSP-based planning [16], are typically based on the discretisation of time, AI planning can exploit continuous time. In planning, once an action is selected, the time at which it is applied becomes an additional decision variable. Although in our model we discretise the functions that represent both load and supply, and describe them by giving values at specific timepoints, using TIFs, we do not discretise time, and actions can be applied whenever the planner chooses.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      A new class of problems
     </section-title>
     <paragraph>
      In this section we define a new class of metric temporal problems, characterised by numeric background events and a trajectory constraint.
     </paragraph>
     <paragraph>
      Numeric background events can be modelled similarly to the Timed Initial Literals (TILs) introduced by Edelkamp et al. [17], extending the syntactic definition as follows:{a mathematical formula}{a mathematical formula} These syntax rules are added to those defining the rest of pddl. In this way, it is possible to model changes to the levels of numeric resources independently of actions in the plan.
     </paragraph>
     <paragraph>
      We now introduce a number of definitions which support the class of problems that we address.
     </paragraph>
     <paragraph label="Definition 1">
      Uncontrollable numeric fluentA numeric fluent is called uncontrollable if it appears in Timed Initial Fluents, but is not modified by any effects of actions.
     </paragraph>
     <paragraph label="Definition 2">
      Controllable numeric fluentA numeric fluent is called controllable if it is modified by the effects of actions but not by any TIFs.
     </paragraph>
     <paragraph label="Definition 3">
      Mixed metric expressionA mixed metric expression is a function of terms in which both controllable and uncontrollable numeric fluents appear.
     </paragraph>
     <paragraph>
      Mixed metric expressions can also be used to indirectly model relative changes of numeric fluents with TIFs. For example, we might wish to express something of the form (at 5 (increase (x) 5)), even though we do not have the syntax to express this. It is always possible to decompose the fluent (x) into two fluents, an uncontrollable fluents {a mathematical formula}(xu) and a controllable fluent {a mathematical formula}(xc), and replace (x) with the mixed metric expression {a mathematical formula}(+ (xu) (xc)). It is now possible to write the relative increase effect on (x) as the TIF {a mathematical formula}(at 5 (= (xu) 5)).
     </paragraph>
     <paragraph>
      When a mixed metric expression is used in a comparison we have a mixed metric constraint, defined as follows:
     </paragraph>
     <paragraph label="Definition 4">
      Mixed metric constraintA mixed metric constraint is a comparison of numeric values in which both controllable and uncontrollable numeric fluents appear.
     </paragraph>
     <paragraph>
      Any mixed metric constraint can be written as a comparison between a mixed metric expression and a constant.
     </paragraph>
     <paragraph label="Definition 5">
      Universal bounded trajectory management problemA universal bounded trajectory management problem (UBTMP) is a planning problem in which all metric fluents are controllable or uncontrollable and there is a single trajectory constraint of the form:{a mathematical formula} where each {a mathematical formula}Pi is a mixed metric constraint specifying an upper or lower bound on a mixed metric expression.
     </paragraph>
     <paragraph>
      One way of specifying the goal of a UBTMP is to define a time horizon, and require the planner to construct a valid trajectory of states that will maintain the always condition (i.e. maintain the fluents within their bounds) up to that horizon. This is how the goals of the voltage control problems considered here are defined.
     </paragraph>
     <paragraph>
      We can generalise the UBTMP for cases in which a trajectory constraint does not have to be true for the entire plan execution, but must hold during an extended period of time. We call this class of problems localised bounded trajectory management problems.
     </paragraph>
     <paragraph label="Definition 6">
      Localised bounded trajectory management problemA localised bounded trajectory management problem (LBTMP) is a planning problem in which all metric fluents are controllable or uncontrollable and there are invariant constraints (flexible trajectory constraints), {a mathematical formula}ci, of the form:{a mathematical formula}{a mathematical formula}∀t∈(ti,min,ti,max), where each {a mathematical formula}Pi is a mixed metric constraint specifying an upper or lower bound on a mixed metric expression.
     </paragraph>
     <paragraph>
      The constraints {a mathematical formula}ci must hold at some point during the plan, but their start and end points need not coincide with the start and the end of the plan. These problems model constraints of the type {a mathematical formula}(hold-aftertP or {a mathematical formula}(hold-duringtt′P), for some mixed metric constraint P and times t, {a mathematical formula}t′, that we choose. This is particularly useful when the initial state does not satisfy the constraints, but we give the planner time to react to the situation by finding a state that satisfies the constraints before the start of the trajectory. When referring to problems in either class we will call them BTMPs (Bounded Trajectory Management Problems).
     </paragraph>
     <paragraph>
      A further generalisation is to consider metric fluents that are directly assigned to, by both actions and TIFs. This generalisation is only required for the case when actions assign to variables, as the case of relative changes to a numeric variable is handled by decomposition to the controllable and uncontrollable components of the effect, as described above. When we allow actions to assign to a variable that is also modified by TIFs, the effect is to break a plan into periods in which the variable is under control of the planner, punctuated by TIFs that “reset” the value of the variable. This is a special case of a BTMP which we do not consider further in this paper, but which can be solved using the planning methods of popf-tif.
     </paragraph>
     <paragraph>
      Examples of BTMPs are: managing the speed of a vehicle so that it remains within safe speed limits, managing the temperature of a room or building so that it remains within a comfortable range and, as in our problem, managing network voltage so that it stays within safe bounds. These problems can also be treated as control problems, for example: thermostatically controlling heating and cooling systems to maintain room temperature. These problems are interesting for planning if the control actions take a significant amount of time relative to variations generated by the background processes (or, equivalently, if the control system is slow to react to changes in the background processes), or if the BTMP appears in the context of additional goals that require discrete causal reasoning alongside the management of the trajectory constraints. In the case of the AC voltage control problem, the slow mechanical behaviour of the tap-changing operation, combined with the requirement to minimise wear on components, leads to a durative tap-changing operation which delays the response of the control system.
     </paragraph>
     <paragraph>
      BTMPs fall into two sub-classes: those in which no actions, or durative actions, have mixed metric constraints as conditions and those in which at least one action, or durative action, does have such a condition.
     </paragraph>
     <paragraph>
      Any problem that contains background numeric curves expressed using TIFs, and a trajectory constraint expressed as an always constraint (either directly or using the translation into an envelope action, described in Section 4.2), is a BTMP and is amenable to the methods presented in this paper.
     </paragraph>
     <section label="4.1">
      <section-title>
       Simple example
      </section-title>
      <paragraph>
       A simple example of a BTMP is the following Simple Voltage problem. In this domain, the voltage in some system must be maintained between upper and lower bounds, over a time period. During the period, there are a number of TIFs representing an uncontrollable discretised background voltage curve. The controllable part of the system voltage can be managed using actions. The system voltage comprises the sum of the background voltage and voltage-changing effects of two actions. These are: an increase-voltage action and a decrease-voltage action. Both of these are durative actions of duration 1 time unit, and both have a step function effect which is to increase (decrease) the controllable voltage by 2 at their ends.{sup:1}
      </paragraph>
      <paragraph>
       In the initial state, the background voltage curve is specified, using TIFs, and an initial value for the controllable voltage is given. The goal is to reach the end of the time period without violating the upper and lower bounds. The task of the planner is to keep the system voltage inside the envelope defined by the bounds, even though the background voltage might exceed the bounds if suitable actions are not selected and executed at appropriate times. Fig. 3 shows the kind of plan that we hope to build automatically using a planner.
      </paragraph>
      <paragraph>
       It is easy to confirm that this problem is a BTMP. The pddl model of the Simple Voltage domain is shown in Fig. 1.
      </paragraph>
      <paragraph>
       The role of the finish action is to ensure that the plan extends to the required horizon (in this case, time 10). Fig. 2 shows the profile of the background voltage, which increases above the upper bound, requiring the plan to include three actions to decrease the voltage adjustment in order to keep the total voltage value within the bounds. The mixed metric constraints in this problem are:{a mathematical formula} and{a mathematical formula}
      </paragraph>
      <paragraph>
       The system voltage is expressed as a function (in this case simply the sum) of the background voltage and voltage adjustment. System voltage is therefore a mixed metric expression.
      </paragraph>
      <paragraph>
       The propositional variable, (p), acts as a resource lock and is used to prevent concurrent modification of the voltage adjustment: both the increase and decrease actions lock this variable while executing, preventing concurrent execution of additional instances of these actions.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Compilations
      </section-title>
      <paragraph>
       The combination of temporal planning, TIFs and trajectory constraints represents a challenge that no pre-existing planners can overcome. However, it is possible to compile the always constraint and TIFs into features that some temporal planners can manage. We now describe these compilations.
      </paragraph>
      <section label="4.2.1">
       Modelling always constraints in pddl2.2
       <paragraph>
        The pddl3 language [18] supports the specification of trajectory constraints such as {a mathematical formula}(alwaysP), {a mathematical formula}(sometimesP), {a mathematical formula}(hold-aftertP) etc. However, no earlier variant of pddl supports this feature directly, so such constraints need to be compiled into other constructs. In our model, we capture {a mathematical formula}(alwaysP) by constructing a durative action which enforces P as an over all constraint. Because P must be true over the whole plan trajectory (at least, the part of the trajectory where actions could affect the satisfaction of the constraint), it is essential that this action which, following Fox et al. [19] we call an envelope action, starts before any other action in the plan (including TIFs), and ends after every other action. To ensure that the envelope starts at the beginning of the plan it must have, as an at start precondition, a proposition that is provided in the initial state and removed by a TIL at time 2ϵ. This gives just enough time for the envelope to start before the condition is deleted. The envelope action must have a start effect that asserts a proposition that is specified as a precondition of every other action, to prevent other actions starting before the envelope opens. Finally, the end of the envelope must not occur until the goal of the problem is achieved. This might be at the time horizon, if specified, or when some condition becomes available. This condition must correspond to the fact that the goal is achieved. Fig. 4 shows how this translation is achieved.
       </paragraph>
       <paragraph>
        It might seem sufficient to require that the envelope contain all actions of the plan, without forcing it to start at the beginning of the plan timeline. However, if the planner can delay the start of the envelope until after the TIFs, it will be able to avoid the always constraint interacting with all but the last TIF, which is clearly not what is intended.
       </paragraph>
       <paragraph>
        The compiled representation of the domain in Fig. 1 is shown in Fig. 5.
       </paragraph>
      </section>
      <section label="4.2.2">
       <section-title>
        Compilation of TIFs into TILs
       </section-title>
       <paragraph>
        Although TIFs present a simple way to express numeric background events, it is possible to compile TIFs into a series of TILs. One possible compilation can be achieved as follows:
       </paragraph>
       <paragraph>
        A new type of object, dt, is created to represent a time point at which a TIF occurs. For each TIF in the problem file, {a mathematical formula}TIFi, an object {a mathematical formula}dti is created.
       </paragraph>
       <paragraph>
        For each fluent that is changed by a TIF, {a mathematical formula}fTIF(x_), where {a mathematical formula}x_ represents the pddl object arguments of the pddl function encoding the fluent, a copy function is created with the same arguments and an additional argument of the type dt. This is {a mathematical formula}fTIF⁎(x_,dti). These are initialised to their respective values in the initial state.
       </paragraph>
       <paragraph>
        An action (shown in Fig. 6) is added to the domain to enforce the updating of the value of the {a mathematical formula}fTIF(x_) functions. This action takes as parameters the two consecutive objects {a mathematical formula}dti and {a mathematical formula}dtj that are added and negated by TILs in the problem file at the same time as the corresponding TIF. It also updates the proposition (tif-done ?dt) that keeps track of the TIF time. This action requires the propositions (allowed ?dt) for the two values of ?dt, {a mathematical formula}dti and {a mathematical formula}dtj, to be simultaneously true at the point at which it is executed. This is achieved using TILs that set the windows over which these conditions hold, as illustrated in Fig. 7. Using this compilation, the no-moving-targets rule [20] prevents the planner from applying an action that relies on {a mathematical formula}(tif-done dti) at the same time as {a mathematical formula}(apply-tif dtidtj) is applied. The proposition {a mathematical formula}(tif-done dtk), where {a mathematical formula}dtk is the last TIF (in the example dt2) is added to the goal to ensure that the functions {a mathematical formula}fTIF(x_) are correctly updated all the way to the end of the plan.
       </paragraph>
       <paragraph>
        In the resulting plan, a series of apply-tif actions will appear alongside the proper actions, managing the behaviour of the TIFs by the compiled process. This compilation is correct, but adds a burden to the planner, which must reconstruct the behaviour of the TIFs alongside the construction of its plan. This can add combinatorial choices to the search space (depending on the strategy the planner uses) that can prevent the planner from finding a plan. In fact, in our experiments with this compilation (see Section 8) we found no planner capable of handling the compiled domain encoding for anything other than the most trivial of problems. There are other ways to achieve the TIF-to-TIL compilation, but all of them force the planner to reconstruct the timeline of TIFs alongside the choices of actions to apply. This can lead to the combinatorial choices that we observe.
       </paragraph>
       <paragraph>
        A very significant difference between TIFs and TILs, and the reason for preferring to model numeric background events using TIFs, arises when actions have over all mixed metric constraints (including the envelope action modelling an always constraint as shown in Section 4.2.2). In the propositional case, when a TIL makes false a proposition that appears as an over all condition of an action, it can be deduced that the TIL cannot lie inside the window over which the action is active. The same is not true with a TIF, since multiple possible values of the fluent can satisfy the same constraint. We shall see, in Section 7.1, that the use of TIFs allows us to improve the heuristic guidance of the planner in a way that cannot be achieved if the model is constructed using TILs.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Fundamentals of power systems
     </section-title>
     <paragraph>
      In this section we introduce the main components of power systems, and the fundamentals necessary for understanding the AC voltage control problem tackled in this paper.
     </paragraph>
     <paragraph>
      A power system comprises several distinct parts, as schematically represented in Fig. 8:
     </paragraph>
     <list>
      <list-item label="–">
       Generation units: the traditional generation process is based on a relatively small number of plants that convert thermal or mechanical energy into electricity. The electricity produced by these units is then stepped-up to high voltage and fed to the transmission network.
      </list-item>
      <list-item label="–">
       Transmission network: the electrical energy produced in power plants is transmitted over long distances at high voltage through the transmission network. Increasing the voltage reduces cost because the wires can be of smaller diameter. From an operational perspective, within a particular wire or line of a given diameter, increasing voltage reduces resistance losses (this is linear for small deviations).
      </list-item>
      <list-item label="–">
       Distribution network: from the transmission network the electrical energy is transferred from high-voltage to medium- and low-voltage distribution networks and it is then delivered to the consumers. A fragment of a distribution network is shown in Fig. 9.
      </list-item>
      <list-item label="–">
       Consumers: the electrical energy consumption is the electrical energy absorbed by the final user. Consumers can be residential, commercial or industrial, each connected to the appropriate voltage level.
      </list-item>
     </list>
     <paragraph>
      In contrast with other infrastructures, such as water and gas, power system generation must meet the energy demand instant by instant, because electrical energy cannot be easily and conveniently stored in large quantities. Although individual consumer demand is unpredictable, the combination of various load patterns follows a more smooth and predictable trend. This property makes it possible to use AI planning for the control of the operations of the network given an average load profile. In current power systems, generation can also be treated as predictable so that, over a 24-hour period, it can be assumed that both load and generation profiles are known. The transmission and distribution networks are constrained to maintain given standards to guarantee an efficient transportation, safety and usability of the electrical current, as well as guarantee high reliability of the supply.
     </paragraph>
     <section label="5.1">
      <section-title>
       Voltage control in distribution networks
      </section-title>
      <paragraph>
       In the UK, the voltage level to be maintained is established in the Electricity Safety, Quality and Continuity Regulations [21]. Distribution networks supply electricity at 132 kV and below. Technical and economic considerations impose certain bounds on voltage nominal values. In networks operating below 132 kV, voltages can exceed their nominal values by 6 per cent, while for networks operating above 132 kV, the tolerance limit is 10 per cent. The low voltage supply is set to be at 230 volts, with a maximum variation of 10 per cent above and 6 per cent below the declared voltage at the declared frequency.
      </paragraph>
      <paragraph>
       In an AC power system, current and voltage follow sinusoidal waves. The root mean square of the product of current and voltage gives the apparent power flow on the network. The difference between the origins of the current and voltage curves is called the phase angle, giving the complex number {a mathematical formula}(r,θ) where θ is the phase angle and r is the magnitude of the apparent power. The real and imaginary parts of this number correspond to the real and reactive power components, referred to as P and Q respectively. The reactive power Q refers to the maximum value of the instantaneous power absorbed by the reactive component of the load (such as refrigerators, air conditioners, clothes dryers, and other devices with electric motors). Resistive loads, such as heating elements, absorb only real power, P.
      </paragraph>
      <paragraph>
       Transformers are used to control their output voltage. There are different types of transformers: step-up transformers, typically found in generation plants, used to step up the voltage from low to high transmission voltage levels; step-down transformers, used to step voltage down to levels appropriate for consumers, and regulating transformers, used to maintain voltage within a proper range. All transformers have the same working principles: they are composed of two coils of wire and a voltage source. The current flowing in the coil on one side of the transformer induces a voltage in the coil on the other side. The voltage on the opposite side changes directly proportionally to the ratio of the number of turns in the transformer. The regulation of the ratio of turns is realised by a tap-changer, a device that adjusts the number of windings in the output coil, by selecting among a small number of discrete positions.
      </paragraph>
      <paragraph>
       Capacitors have the property of delaying the phase of the alternating current with respect to the alternating voltage. For this reason they can be considered as sources of reactive power. In substations, capacitors are connected in capacitor banks that can be switched on or off to reduce system losses and to provide voltage support.
      </paragraph>
      <paragraph>
       Reactors are high-voltage inductors and they delay the voltage with respect to the electric current. They can be considered as absorbers of reactive power. Reactors are used to help with the regulation of the voltage, absorbing the excess reactive power or reducing fault current in distribution lines.
      </paragraph>
      <paragraph>
       Static VAR Compensators (SVC) are composed of several capacitors and inductors (reactors) and a switching system that can inject or absorb reactive power in the power system, helping in the regulation of the voltage at their terminals.
      </paragraph>
      <paragraph>
       In our approach we treat transformers and capacitors as controllable, and generators and loads as uncontrollable. Capacitors and reactors are very similar, with the only difference being that they deal with over-voltages and under-voltages respectively. SVCs have much faster response during dynamic conditions compared to capacitor/reactor banks, but otherwise their operation is similar. Reactors and SVCs are therefore abstracted into a single controllable component that can be used to control reactive power within some specified bounds. We use the term capacitor as a generic label to include capacitors, reactors and SVCs, and we do not make any further reference to reactors or SVCs in this paper.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Network topology
      </section-title>
      <paragraph>
       A radial network is a tree-structured network with a single generation source at the root. All of the network structure “radiates” from this single source. The main branches of this radial structure are referred to as feeders. Consumers (loads) are at the leaves of the tree. An active meshed network can contain cycles and there might be multiple sources of generation distributed around the network. When there is ad hoc generation attached at the distribution level (for example, when consumers also participate in electricity generation), a meshed network results. Unless islanded, such a network remains attached to the grid.
      </paragraph>
      <paragraph>
       In distribution networks with a typical radial configuration, voltage control strategies are based on changing the settings of transformer taps and the local regulation of capacitor banks connected along the feeder. The penetration of distributed generators has an impact on the voltage profile along the feeder, because they inject active and reactive power and change the configuration of flows in the network. This means that the voltage does not drop along the feeder as in the current passive network, creating the need for different voltage control mechanisms. Several solutions are presented in the literature [22], [15], [23], [24], [25], which range from a reconfiguration of the network (requiring massive investment) to the use of proactive management of the elements in the distribution network. AI planning provides a means by which proactive management can be achieved.
      </paragraph>
      <paragraph>
       The AC voltage control problem is concerned with maintaining the voltage at each busbar of a distribution network (or a zone of the network) within a given bound, for an extended period of time, assuming that the load profile of consumers and the schedule of the power system generators are known over this period. We assume deterministic generation. The inclusion of solar or wind generation would potentially increase forecasting errors and would make a long-horizon plan less robust.{sup:2} The voltage at each point of the power system is influenced by different factors: the topology of the network, the load consumption and the power generated. The decision variables are the tap ratios of transformers, the status of the capacitors and reactors and the level of power demand that can be shed from the network, while the network has to respect the voltage constraint:{a mathematical formula} where N is the total number of busbars present in the network. The voltage {a mathematical formula}Vk at busbar k can be obtained using the power flow equations:{a mathematical formula} These are a set of non-linear equations where {a mathematical formula}Pk and {a mathematical formula}Qk are respectively the real and the reactive power injected/absorbed in the busbar k, {a mathematical formula}δk is the phase angle of the alternating voltage, and {a mathematical formula}Gkn and {a mathematical formula}Bkn are called, respectively, the reactance and susceptance of the line between busbars k and n. Further details of the power flow equations can be found in Appendix C.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       The hierarchical tap changing method
      </section-title>
      <paragraph>
       A well established method in AC voltage control is the Hierarchical Tap Changing (HTC) approach [26]. This is a reactive control{sup:3} approach using indirect coordination without the need for communications. The structure of the hierarchy determines the order in which transformers respond to changes in the voltages at the busbars. Power normally flows downstream from the main source of generation. Each transformer maintains the voltage of its adjacent downstream busbar within the specified bounds by adjusting its tap ratio according to the following equation:{a mathematical formula} where {a mathematical formula}tnew and {a mathematical formula}told are the tap ratios of the transformer, before and after the operation, and {a mathematical formula}Ve,target and {a mathematical formula}Ve,measured are the nominal voltage and the actual measured voltage at the downstream busbar for the transformer. The indirect coordination is achieved through the use of fixed time delays, in the order of one minute [26] from the moment a change is triggered, on the operation of the transformer. This means that each transformer measures voltage but then is allowing a slack period equal to its time delay before it acts, with the hope that a transformer higher in the hierarchy might clear the violation. When the respective time delay passes, the transformer will act if the voltage is still outside the bounds, based on the real-time measurement (not the old measurement). The order in which the transformers in this hierarchy are triggered is determined by time delays which are longer for transformers at the bottom of the hierarchy than for those at the top. HTC is a well established technique adopted by industry. It performs particularly well in radial networks with no distributed generation, where the direction of the voltage drop is fixed. In meshed networks, and particularly when these include distributed generators, one might derive a logical hierarchy of the delays based on the most common pattern of the direction of voltage drop. However, in certain operational states, direction of flows might change the direction of voltage drop. In such cases, the hierarchy of the time delays might not be appropriate and can result in voltage violations on the buses that are not directly monitored.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      PDDL model of the AC voltage domain
     </section-title>
     <paragraph>
      To handle the complexity of the voltage control problem we introduce a modular structure consisting of the following components:
     </paragraph>
     <list>
      <list-item label="•">
       a pddl model describing the elements of the problem that are directly reasoned about by the planner;
      </list-item>
      <list-item label="•">
       an encapsulated type, representing a structured object that is manipulated by the planner without knowledge of how it is implemented;
      </list-item>
      <list-item label="•">
       an interface between the planner and a specialised external solver that implements the encapsulated type.
      </list-item>
     </list>
     <paragraph>
      The AC power flow equations cannot be expressed in pddl, so we use a specialised external solver to compute their effects when actions are applied. The network topology is encapsulated and the interface contains the control parameters that are passed between the planner and the solver. The encapsulation of the network means that the pddl model does not contain any network connectivity information or any representation of the network structure. The management of the network, ensuring that it respects the necessary electrical properties whenever any action is applied by the planner, is handled completely by the external solver. The implementation of the interface requires the pddl model to contain some variables, predicates and functions that support the necessary communication between planner and solver. The details of this infrastructure are described in Section 6.2.
     </paragraph>
     <section label="6.1">
      <section-title>
       Modelling the network topology
      </section-title>
      <paragraph>
       In pddl2.2,{sup:4} each component of the distribution system is represented as an object of a different type. In particular, the model specifies the types of Network, Busbar, Load, Generator and Device. The Device type breaks down into two subtypes: Tap and Capacitor. The Network type is encapsulated and there is only one object, called thenetwork, of this type.
      </paragraph>
      <paragraph>
       Our solution to the encapsulation of the Network type has not yet been shown to be fully general, but generalising our approach to other domains is straightforward, as discussed in Section 6.2. popf-tif is a first proof-of-concept of the temporal extensions of the PMT architecture described by Gregory et al. [27]. In the following we describe a solution that is specific to the power management problem where only one encapsulated object and one external solver are needed.
      </paragraph>
      <paragraph>
       Given background load and generation profiles over the period, and safety constraints on maximum and minimum voltages, the planning problem is to manipulate network components, such as transformers, in time to interact with background profiles in such a way that the voltages at the busbars of the network always remain within their specified safety bounds. This requirement is expressed as the trajectory constraint:{a mathematical formula}
      </paragraph>
      <paragraph>
       The problem is defined in terms of controllable and uncontrollable variables. The load and generation real and reactive power values are uncontrollable, while the transformer tap-levels and capacitor status settings (on/off) are controllable.
      </paragraph>
      <paragraph>
       The action of stepping up the tap of a transformer is shown in Fig. 10, and a similar action is available for the stepping down of the tap. We want to avoid frequent oscillation of tap settings so, after a step-up (or step-down) operation is performed, we impose a slack time period before a subsequent step-change in the opposite direction can be performed on the same tap. In the absence of actions with intermediate effects in pddl2.2, this constraint is enforced by ensuring that the tap is released between step actions. The duration of this release action represents the slack-period. The motivation for avoiding frequent oscillation of tap settings is partly to reduce mechanical wear (low frequency oscillation) and partly to avoid mechanical failure (high frequency oscillation). The first of these can also be modelled as an optimisation criterion, with action costs representing the wear on components [6].
      </paragraph>
      <paragraph>
       Capacitors in the distribution networks can be switched to regulate voltage to desired targets and bounds. The pddl2.2 model of the action which describes the switch of a capacitor is shown in Fig. 11. The effect of this action is the change of the status of the capacitor from inactive to active. An analogous action is available for the deactivation of the capacitors.
      </paragraph>
      <paragraph>
       We now have the elements of a BTMP (Definition 5), because the voltage is a function of both the controllable and uncontrollable metric fluents, and hence is a mixed metric expression. All of the metric fluents in the problem are controllable or uncontrollable. We have an always trajectory constraint as specified in Definition 5. Therefore the AC voltage control problem is a BTMP.
      </paragraph>
      <paragraph>
       Our problem is complicated by the fact that voltage is not a variable of the problem, but is a label for the mixed metric expression obtained as a function of the controllable and uncontrollable variables of the problem. In the Simple Voltage problem, described in Section 4.1, the voltage was expressed as the sum of the background voltage (bgvoltage) and the voltage adjustment. By contrast, as shown in Equations (2), the function determining the linkage between system voltage and the component variables in the AC case is very complex. In particular, the tap-levels and capacitor-settings determine the values of reactance and susceptance on the lines on which those components appear. Voltage is also a function of the precise network topology defining how the components are linked. The role of the external solver is to compute the voltages at different components of the network whenever it is invoked by the planner. The planner therefore requires no knowledge of the complex physical impacts of performing tap and capacitor operations. The way in which the planner notifies thenetwork that it has changed state, as a result of the application of an action, is by means of the effect (increase (thenetwork) (δ)) (or (decrease (thenetwork) (δ))), where δ is a function of the tap or capacitor affected, and increase or decrease reflects whether a tap (capacitor) was stepped up or down (switched on or off). The external solver is responsible for computing the new network state so that the planner has access to the updated busbar voltages.
      </paragraph>
      <paragraph>
       The interface between the planner and external solver must therefore contain the functions that are implemented by the external solver. The pddl keywords increase and decrease are overloaded to refer to an encapsulated object, and the precise meaning of the expression (increase (thenetwork) (δ)) depends on the implementation of the Network type. The implementations of the functions (step-up-effect ?t - tap), (step-down-effect ?t - tap) and (capacitor-effect ?c - capacitor) are provided by the external solver, and the signatures of these functions are part of the interface between the planner and the solver.
      </paragraph>
      <paragraph>
       The power of the abstraction is that the planner knows that it is applying an action that changes the network state, and can access the values of mixed metric expressions that are affected by the solver, but does not require a declarative description of the effects of those changes on the network. An abstraction of this kind is required whenever planned actions have effects that cannot be conveniently modelled in an action-based declarative language such as pddl. An important advantage of the encapsulation we propose, is that we can define a relaxation of the Network type for the planner to use during the heuristic evaluation of a state. This means that the planner does not simply apply actions in a way that is blind to the physical effects, but instead has a way of approximating the physical effects in order to evaluate alternative states in the search space. The relaxation we use is a first order linear approximation of the actual physical effects of tap-changing and capacitor-switching operations, and is defined in Section 7.
      </paragraph>
      <paragraph>
       Dornhege et al. [28] propose an alternative way to achieve the semantic attachment of external solvers to planners, using the pddl/m language. In pddl/m, domains relying on the computation of conditions and effects by external solvers contain two types of modules: condition-checker modules and effect-applicator modules. Condition-checker modules confirm, by invoking the external solver, that a planned action can be successfully applied in the current state. The effect-applicator modules then compute the effects of applying the planned action, and update both the external state and the plan state accordingly. In this way, pddl/m specifies the actions that can be planned, together with the external variables that will be required for the external solver to correctly update the state. The example Dornhege et al. [28] focus on the integration of a planner with a robot arm, and the domain contains an action to put-down an object from a grasp. To achieve this, the requirement that the grasp is a suitable one for putting down the object in its intended location, is checked by invoking the condition-checker module from within the action preconditions. If the condition is satisfied, then the effects of putting the object down in the correct place are computed by an invocation of the effect-applicator module from within the effects of the action. To successfully invoke the external solver, the pddl/m effect-applicator module must pass the necessary external state variables to the solver, even though these variables are not part of the plan state. When a state is evaluated, the external solver is called in a relaxed mode in which some of the effects of the actions it performs are abstracted away.
      </paragraph>
      <paragraph>
       This example shows that the pddl/m interface with the external solver is action-oriented, rather than type-oriented as in our case. Using our approach to model the same domain, we would define an encapsulated type, RobotArm, with an object such as therobotarm, and invoke the external solver to update the state of therobotarm whenever actions such as put-down are applied in state progression. Thus, the planner would have a representation of the encapsulated type, and a name for its object, and an abstracted knowledge of how the state of the object was being changed. This type-based abstraction is no less informed than the action-based abstraction of pddl/m, which delegates condition-checking and effect-application to the external solver. In the type-based approach, an abstraction of the RobotArm, encoded in the pddl2.2 domain, would be used for heuristic evaluation (as in the AC Voltage domain).
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Formalising the interface
      </section-title>
      <paragraph>
       In this section we present a formalism for achieving the interface between the planner and the external solver. We distinguish between the direct effects of the actions, which are modelled in pddl, and the indirect effects, which affect the encapsulated implementation of thenetwork and are the responsibility of the external solver.
      </paragraph>
      <paragraph>
       We distinguish three categories of numeric fluents:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Vspecial: numeric variables that record the indirect effects and are calculated by an external solver linked to the planner;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Vdep: variables that are affected by actions, resulting in the external update of {a mathematical formula}Vspecial variables;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Vindep: variables that are affected by actions without resulting in any external computation.
       </list-item>
      </list>
      <paragraph>
       The pddl actions can directly affect only the variables in {a mathematical formula}Vdep∪Vindep, while goals and conditions can be expressed in terms of all of the variables in {a mathematical formula}Vdep∪Vindep∪Vspecial. Whenever a change in at least one of the {a mathematical formula}Vdep variables occurs, the state is also updated by calculating the values of the {a mathematical formula}Vspecial variables according to the new values of the {a mathematical formula}Vdep variables. For example, in the AC voltage control domain, the {a mathematical formula}Vdep variables are the tap settings which are changed when the planner applies an action to step a transformer up (or down). The {a mathematical formula}Vspecial variables are the busbar voltages. The {a mathematical formula}Vindep variables are the maximum-voltage and minimum-voltage bounds, and the max-tap-level and min-tap-level bounds, none of which are relevant to the external solver but are only used by the planner. When the tap setting is changed by a planned action, the external solver recomputes all the busbar voltages. The behaviour of {a mathematical formula}Vspecial variables represents a numeric analogue of derived variables expressed through axioms in pddl2.2[29], [17]. In contrast to axioms, in which the computation of the derived variables can be described declaratively, the functions that determine the values of {a mathematical formula}Vspecial variables might be defined as non-trivial algebraic operations. The use of an encapsulated type and an external solver allows the state update to depend on such computations.
      </paragraph>
      <paragraph>
       Given the three categories of variables defined above, the state can be written as{a mathematical formula} We identify two types of transition functions, one describing the effects of actions and the other describing the resulting indirect effects.
      </paragraph>
      <paragraph label="Definition 8">
       The effects of an action, a, are represented by a function:{a mathematical formula} such that{a mathematical formula} so that the effects of the action are restricted to the variables {a mathematical formula}Vdep∪Vindep.An indirect effect ϕ is a function:{a mathematical formula} such that{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 9">
       An instantaneous state transition triggered by action a, {a mathematical formula}effect(a)ϕ, is defined as a function:{a mathematical formula} such that{a mathematical formula}
      </paragraph>
      <paragraph>
       Whenever an action, a, is applied to a state, s, in a domain that includes an indirect effect function ϕ, s is updated by the corresponding instantaneous state transition {a mathematical formula}effect(a)ϕ(s). Here, ϕ is the function that is implemented by the external solver and is therefore an external function in the domain description.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Solving the planning problem
     </section-title>
     <paragraph>
      The problem class we have described is a subclass of temporal numeric problems. The Simple Voltage problem, with the always constraint compiled into an envelope action, but leaving the TIFs uncompiled, is in a form that can be tackled using popf2 (although its heuristic is largely blind to the impact of TIFs). There are two limitations of popf2 in solving the AC voltage control problem that we address in the remainder of this paper. The first is the lack of an efficient management of TIFs, and the second is the inability to manage the complex numeric constraints that arise in the AC power flow model.
     </paragraph>
     <paragraph>
      When the solution of a BTMP requires the integration of the planner and an external solver, we have an instance of a two-dimensional problem class with controllable and uncontrollable variables on one axis and {a mathematical formula}Vdep and {a mathematical formula}Vspecial variables on the other. Fig. 12 shows this two-dimensional space, divided into four regions. Classical temporal and metric planning problems occupy the bottom left quadrant, as they require neither uncontrollable variables nor external solvers. The Simple Voltage problem discussed in Section 4 is in the top left quadrant, being an instance of a BTMP but not requiring any external solver integration. By contrast, the AC Voltage Control problem is in the top right quadrant. It is a BTMP in which the values of mixed constraints depend on non-linear functions and are computed by an external solver. We can also identify problems in the bottom right quadrant: the robot manipulation problem considered by Dornhege et al. [28] requires an external solver but no uncontrollable variables.
     </paragraph>
     <paragraph>
      We begin with a brief summary of the key features of popf2 that are relevant to understanding the extensions we add in popf-tif. popf2[1], [2] provides the underpinning temporal and metric planning framework, in particular the ability to maintain a partial order over actions in the developing plan and the management of deadlines encoded using TILs. popf2 handles both TILs and TIFs as special actions that are forced to be applied at the appropriate times. popf2 also identifies compression-safe actions [30]. A compression-safe action is a durative action that can be abstracted into a single point and associated post-hoc with its temporal extent. Distinguishing between compression-safe and non-compression-safe actions allows a more refined temporal reasoning when a plan involves concurrent activities.
     </paragraph>
     <paragraph>
      popf2 supports a version of the Metric-FF heuristic, extracted from a Temporal Relaxed Planning Graph (TRPG), that uses infinity handling, as proposed by Hoffmann [31] but not implemented in the Metric-FF planner. Infinity handling allows increasing effects on metric fluents to be applied arbitrarily often once the effect appears in the reachability analysis. In relaxed plan extraction, the number of applications of the effect required to satisfy the goal is computed by considering the necessary increase over the current value of the fluent in order to reach the goal threshold. To see why infinity analysis is necessary in popf2, we consider the case in which a durative action has an increase effect on a metric fluent at its end point. Without infinity analysis, once the action can be applied in the TRPG, the end point would have to be applied at multiple time points (to obtain the accumulated effects of multiple applications of the increase effect) and these would be separated only by ϵ since the relaxation would allow the same action end point to be applied repeatedly once its preconditions were satisfied (ϵ separation is required, because the TRPG must advance time by a minimum amount before constructing the next layer of the graph). As a result, if the duration of the relaxed plan in the TRPG is d, the TRPG would require approximately {a mathematical formula}d/ϵ layers, which will usually be many thousands, making the TRPG impractical to construct.
     </paragraph>
     <paragraph>
      popf2 implements an Enforced Hill Climbing search, using the TRPG-based heuristic, and switches to best-first search if the EHC search fails.
     </paragraph>
     <section label="7.1">
      <section-title>
       Heuristic evaluation
      </section-title>
      <paragraph>
       The heuristic function of popf2 evaluates a temporal-numeric state. Given that popf2 manages a partial order, the constraints on the structure of the plan head in a state are weaker than they would be if enforcing a total order, so the heuristic function is able to exploit the union of all of the states reachable along all of the total orders consistent with the temporal constraints applying to the plan head [1]. Fig. 13 shows an example of the use of the plan head in popf2 to generate the temporal relaxed plan graph in the Simple Voltage domain from a state during the search.
      </paragraph>
      <paragraph>
       The TRPG of popf2 is an extension of the RPG [32] adapted to reason about time. Each action a is divided into two snap-actions, {a mathematical formula}as and {a mathematical formula}ae, the start point and end point of the action, respectively. The RPG is augmented by assigning a time stamp to each fact and action layer. To capture the duration of action a, the snap-action {a mathematical formula}ae is assigned to an action layer labelled with the earliest time in which it can appear, following its associated {a mathematical formula}as. This constraint is also applied to the ends of actions that are already executing. The heuristic value is the length of the plan extracted from the TRPG, counting the number of increasing (or decreasing) actions required to achieve the goal numeric values as described above.
      </paragraph>
      <paragraph>
       As described in Coles et al. [1], TILs are added at the specified layers during the TRPG construction. If a TIL deletes a proposition, popf2 prevents actions that precondition on that proposition from being newly added to the TRPG after that point. If the action was applicable before the TIL occurred it continues to be applicable, as demanded by the monotonicity of the reachability analysis (monotonicity cannot be abandoned without loss of tractability of the relaxed plan computation). TIFs are handled slightly differently in popf2: adding a TIF implies the widening of the interval of the numeric variable involved, which is always an accumulating effect, and popf2 therefore does not prevent any action from being applied after a TIF has appeared.
      </paragraph>
      <section label="7.1.1">
       <section-title>
        Limitations of the standard relaxation
       </section-title>
       <paragraph>
        In the instance of the Simple Voltage domain presented in Fig. 1, Section 4, the controllable voltage is initialised to a value that lies within the specified bounds, and the only changes to the system voltage are brought about by TIFs. Once the constraint envelope action is started, the mixed metric constraint becomes active. If popf2 evaluates a state in which the constraint is not satisfied then the state must be considered a dead-end (by definition, a state must satisfy the condition to be valid). The monotonicity of the relaxed reachability construction will ensure that the condition remains satisfied throughout the TRPG constructed from any state in which the condition is already satisfied. Thus, the relaxed plan will include no actions to react to TIFs and the heuristic will not see the cost of responding to future TIFs.
       </paragraph>
       <paragraph>
        In the Simple Voltage problem, the heuristic distance from any state to the goal is therefore given by the number of TIFs and TILs that remain to be executed. No actions are needed and the only helpful actions proposed are the application of the next TIL or TIF. The consequence of this is that the planner steps forward past the next TIL or TIF and only discovers the violation of the always constraint as a result of progressing the state into one that fails to satisfy the condition. EHC fails immediately and the planner performs a best-first search of the search space. The Simple Voltage problem is very small, so this behaviour still allows a plan to be found exploring 31 states. As is seen in Fig. 14, this leads to 31 states being explored. Examination of the search tree shows that the planner never sees the next TIF until it is reached, so it cannot distinguish between the relative values of increasing and decreasing the voltage — indeed, the heuristic values of states generated using increase actions are the same as those generated using decrease actions, because the effect on the state in either case is equivalent under the relaxation. To solve this particular Simple Voltage problem, the planner has to decrease voltage quite aggressively (three successive decreases are required), but it has to search its way to this solution by backtracking out of bounds violations caused by increasing voltage instead. The key issue is that the heuristic provides no guidance and it does not see starting a decrease-voltage action as helpful.
       </paragraph>
      </section>
      <section label="7.1.2">
       <section-title>
        Lookahead method
       </section-title>
       <paragraph>
        In pursuing a more informative heuristic, we need to take into account the effects of TIFs during the heuristic evaluation. We do this by performing a reduced relaxation (a “de-relaxation”) in order to obtain better guidance for problems with TIFs.
       </paragraph>
       <paragraph>
        Keyder et al. [33] observe that the FF relaxed plan heuristic sometimes oversimplifies the structure of a problem, resulting in an inaccuracy of the heuristic value. Our objective is to de-relax to gain more information. It might be thought that treating TIFs in the same way as TILs, during the construction of the TRPG, would increase the heuristic information available. Using this approach, instead of widening the interval of accessible system voltages, the TIF effect would reduce the interval to the range of numeric values actually achievable at each time point. No actions depending on values outside this range would be applicable after that layer, although they would continue to be applicable if they had been applicable earlier, in order to retain monotonicity. While this narrowing of the TRPG at each TIF layer might provide additional heuristic information for some problems, by leading to longer relaxed plans, it does not help for BTMPs in which there are no mixed metric constraints in the preconditions of actions, since in this case the reachable actions are not influenced by the uncontrollable variables and the relaxed plan therefore cannot be affected either.
       </paragraph>
       <paragraph label="Definition 10">
        An over all constraint {a mathematical formula}c=(over allP), in action a, is active in a plan state s, with respect to a TIF {a mathematical formula}(att(=vα)) if P depends on v, {a mathematical formula}as is in the plan head in s, {a mathematical formula}ae is not in the plan head and does not appear in the TRPG before layer t.
       </paragraph>
       <paragraph label="Definition 11">
        If {a mathematical formula}c=(over allP) is an active constraint with respect to a TIF {a mathematical formula}T=(att(=vα)), a TIF-grounded goal for T is {a mathematical formula}P[v/α] at t.
       </paragraph>
       <paragraph>
        To improve the heuristic for search guidance in BTMPs, the TRPG is constructed in exactly the same way as in popf2, but we modify the relaxed plan extraction phase. In popf-tif, in addition to the goals in the final layer of the TRPG (representing the final goals of the planning problem), goals are set at the earliest layer in which TIF effects are added. For each active over all condition that includes a mixed metric constraint, referring to one of the fluents modified by a TIF in this layer, the constraint is added as a goal. The newly assigned TIF value is substituted into the constraint. For example, in the Simple Voltage problem, when evaluating the state following the application of the start of the envelope action, the first TIF is (at 5 (= (bgvoltage) 21)). Two active constraints are present. Therefore, two TIF-grounded goals are added at time 5, formed by evaluating these active constraints with bgvoltage set to 21. These are:{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        More generally, when evaluating a state, TIF-grounded goals are added at the next time point at which TIFs appear in the TRPG, corresponding to all active constraints in the state being evaluated with respect to those TIFs. In the case where v is a {a mathematical formula}Vdep variable and P refers to a {a mathematical formula}Vspecial variable, the TIF-grounded goal is formed by evaluating the {a mathematical formula}Vspecial variable as a function of the TIF-assigned {a mathematical formula}Vdep variable.
       </paragraph>
       <paragraph>
        These goals are managed in the same way as any other preconditions of actions added during the relaxed plan extraction phase: new actions are added to achieve them and counted in the heuristic. In this example, these goals will lead to the addition of one decrease-voltage start snap-action in the initial layer of the plan (followed by its end snap-action at time 1), to ensure that the total voltage is reduced below 20 (the upper bound). The heuristic value is then the sum of the number of remaining TIFs and TILs together with these two end points of the decrease-voltage action. Furthermore, the decrease-voltage start snap-action is then a helpful action.
       </paragraph>
       <paragraph>
        An effect of this mechanism in general is to both enhance the heuristic value by accounting for actions required to meet the over all conditions and also to ensure that helpful actions are added to achieve these goals which are essential for the planner to avoid the violations caused by the TIFs. Without this modification, the relaxed plan would not contain these helpful actions and the planner would often choose the wrong action to apply. This mechanism can be seen as a lookahead over the upcoming TIFs, enabling the heuristic to identify the actions that will be helpful in avoiding the violations they might cause. The question of precisely how many TIFs to look ahead is one that we consider in future work: in this work we concentrate on looking ahead only to the next TIF relevant to that variable, which is a safe strategy since we can be sure that the plan must respond to this TIF before it arrives.
       </paragraph>
       <paragraph>
        As can be seen in Fig. 15, this mechanism has a significant effect on the search behaviour of the planner. Our Simple Voltage problem instance is solved visiting just 15 states. Looking in detail at the search tree, it can be seen that the EHC encounters a plateau at the outset (where the heuristic value of the initial state is 6, but its successors are a state of value 7 and a dead-end state). The search crosses this successfully when it encounters state 6, with value 5. Thereafter, there is no further search (although the heuristic does increase as the next TIF is encountered). We can see that the heuristic has identified the decrease-voltage actions as being the helpful ones. The plan first starts the check action, which is our always-enforcing envelope action, then a TIL closes the opportunity for this by deleting the envelope precondition. Next, the plan starts, and then ends, a decrease-voltage action, in order to lower the system voltage to avoid a violation when the first TIF occurs. Two further decrease-voltage actions are started and ended before the next TIF, to avoid the anticipated violation. Finally, a TIL asserts the end condition of the check action, so the check-end is applied and the goal state is reached.
       </paragraph>
      </section>
     </section>
     <section label="7.2">
      <section-title>
       Integrating the planner with an external solver
      </section-title>
      <paragraph>
       The external solver is implemented as a dynamically loaded shared library, that is passed as input to the planner. The planner calls the external solver through an interface consisting of variables in {a mathematical formula}Vdep∪Vspecial. In order to perform the voltage calculations, the external solver needs as input the configuration of the network (the links between the different elements) and information about the resistance and impedance of lines. It therefore receives the network configuration as a Matpower file (a standard file system format used by power systems software tools, [34]). An additional advantage to using an external solver, instead of trying to capture everything in the pddl model, is that we do not need to express variables in the domain that are not relevant to the search (such as impedance), but are necessary to perform the power flow calculations.
      </paragraph>
      <paragraph>
       When the planner updates a state, if one of the {a mathematical formula}Vdep variables changes, then the external solver is invoked via the instantaneous update effect described in Definition 9. The corresponding instantaneous update function, ϕ, is implemented in the external solver.
      </paragraph>
      <paragraph>
       The general architecture of the integration is shown in Fig. 16.
      </paragraph>
      <paragraph>
       When an action or a TIF modifies a {a mathematical formula}Vdep variable, ordering constraints must be added to the plan head between the times at which these modifications occur and any actions that have preconditions or effects referring to either the affected {a mathematical formula}Vdep variables or the {a mathematical formula}Vspecial variables that will be changed as a result. This extends the partial order management, inherited from popf2, to include numeric variables in the interface between the planner and the external solver.
      </paragraph>
      <paragraph>
       We experimented with using the IPSA power flow tool [35] as the external solver in our architecture. IPSA is a licensed software specialised to perform power flow calculations for power engineering. However, due to the computational cost of communicating with IPSA, we decided to model and solve the power flow equations using the Newton–Raphson algorithm [36], an iterative numeric algorithm that allows us to find successively better approximations to the zeros of a function. As shown in Fig. 17, this dedicated solver outperforms the IPSA software for networks of up to 300 busbars. This is due to the fact that a great deal of time is required to initialise IPSA on each call, regardless of the network size.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       External solver in the heuristic evaluation
      </section-title>
      <paragraph>
       For the baseline heuristic evaluation, the relaxation of numeric state variables used in popf-tif is based on the same principle introduced in Metric-FF [31] of relaxing the decreasing effects on numeric fluents. The reachable values of the {a mathematical formula}Vspecial variables are not accessible to the planner, so in order to obtain any heuristic information from the external solver, the planner requires a relaxation of the Network encapsulated type.
      </paragraph>
      <paragraph>
       In our work, this relaxation is a simplification of the effects of tap-changing and capacitor-switching actions on the voltages at the busbars. We relax these effects into simple linear first order effects. We treat as zero the effects on any busbars that are far away from the transformer or capacitor that is acted upon. This relaxation is sufficiently simple to express that it can be declaratively described in pddl2.2. We therefore provide a collection of constants in the initial state, one for each capacitor, tap and busbar, of the form (step-min ?d - device ?b - busbar) and (step-max ?d - device ?b - busbar), to represent the relaxed voltage updates, and we translate the increase and decrease (thenetwork) (δ) expressions into quantified simple effects of the tap-changing and capacitor-switching actions. For example, for heuristic evaluation, the (step-up-tap ?t - tap) action contains the quantified effect:
      </paragraph>
      <list>
       <list-item>
        (forall(?b-bus)(and(atstart(increase(thenetwork.voltage?b)(step-max?t?b)))))
       </list-item>
      </list>
      <paragraph>
       These constants and effects are exploited only during the heuristic evaluation of states. In this expression, we use the syntax thenetwork.voltage to access the value of the mixed metric expression, voltage, from the Network object being affected. We only use this dot notation when it is not already clear in the context which object is being affected. This way of achieving the first-order relaxation is an implementation device enabling us to express the Network relaxation in pddl2.2, and exploit it using the standard TRPG construction, without need for additional implementation machinery. In this way, the quantified simple effect specified by the step-up-tap action is a relaxed interpretation of the (increase (thenetwork)δ) effect.
      </paragraph>
      <paragraph>
       We experimented with an alternative heuristic, in which the external solver is invoked during the heuristic evaluation to recalculate the first order effects of the actions in the state being evaluated. For example, in the (step-up-tap ?t - tap) action, the quantity (step-max ?d - device ?b - busbar) is reapproximated by the external solver, for each busbar. For efficiency reasons, the (step-min ?d - device ?b - busbar) and (step-max ?d - device ?b - busbar) fluents are only computed during the relaxed plan extraction. This heuristic provides better distance estimates but is expensive. We report our experimental results in Section 8.4.
      </paragraph>
      <paragraph>
       The external solver plays an additional role in the heuristic, during the computation of TIF-grounded goals. This arises in the AC voltage control problem in the following way. Since the over all constraint, in the constraint-check action, refers to the Network voltage, the computation of {a mathematical formula}P[v/α] (Definition 11) exploits the external solver to determine the actual value of the Network voltage for the particular p-level and q-level load and generation settings. That is, when P is a condition on a {a mathematical formula}Vspecial variable, the external solver must compute the new value of the variable using the newly TIF-assigned {a mathematical formula}Vdep values, then evaluate P for the particular instance of the encapsulated type.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      In this section we present and discuss results of the application of popf-tif to the AC voltage control domain. First we present an illustrative example where our planner finds a sequence of actions to manage AC voltage control in a 33 kV network used as a benchmark in the AuRA-NMS project [37]. Our control strategy is compared with a modern reactive control approach, where transformers are reactively controlled and co-ordinated through the use of sensors and time-delays. We then examine the scalability of the planner in terms of the size of the network, showing that the integrated architecture supports good scaling behaviour. Although, in principle, we can reduce the size of a zone in order to make it amenable to planning, larger zones offer lower variance in the predicted load and generation profiles as the number of generators and consumers attached to the zone increases. It is therefore an important benefit to be able to scale the performance of the planner to larger networks. To demonstrate the robustness of plans in the presence of uncertainty in the predicted load and generation profiles, we perform experiments in simulation which are reported below. Finally we present a brief study of the accuracy of the first order approximation of the effects of actions on the {a mathematical formula}Vspecial variables in the heuristic evaluation. All the experiments are performed on a 3.4 GHz Intel Core i7-2600 machine, limited to 20 minutes and 4 GB of memory. The 20 minute limit reflects the fact that, given the half-hour resolution of the predicted load and generation profiles, decision-making can only be responsive if planning can be done within this granularity.
     </paragraph>
     <section label="8.1">
      <section-title>
       Case study: a 33 kV network
      </section-title>
      <paragraph>
       As a case study we use the 33 kV interconnected AuRA-NMS network taken from Davidson et al. [37] and shown in Fig. 18. A reminder of the meaning of the symbols used is given in Fig. 19. This network contains 39 busbars, 9 distributed generators and 17 transformers. The substation (buses 1 and 3) connects the 33 kV network to the rest of the grid represented by Generator G1. In contrast to a traditional radial distribution, where the busbars are usually located in sequence, the topology of this network presents a meshed configuration.
      </paragraph>
      <paragraph>
       We consider the AC voltage control problem over the period of 24 hours, given that the load and generation profiles are described at 30 minute intervals. All loads have the same profile scaled by a different factor. Each load corresponds to a different demand level, but they all follow the same pattern of variation. This assumption is commonly used in the Power Systems literature, as it is usually not feasible to find data for each individual user. All generators, other than G1, are assumed to be Combined Heat and Power Plants with different capacities, but with deterministic output. Fig. 20 shows a typical load profile.
      </paragraph>
      <paragraph>
       The output plan generated by popf-tif, using the domain described in Appendix A, is shown below. The problem instance is too large to supply here, but is given in online appendix, where each line indicates the time at which the action starts, the name of the action, and, in square brackets, the duration of the action. In this simple example, few control actions are required and there is no oscillation of tap-settings. Therefore, the slack-period does not affect the timings of the actions. The actions on different taps overlap where possible, in order to interact successfully with the TIFs. It should be noted that the first action is the start of the envelope action that ensures that the constraints are met. The unit of time corresponds to one hour.
      </paragraph>
      <paragraph>
       popf-tif with a lookahead of one TIF, solves this problem by searching 66 states in 0.59 seconds. In contrast, the same problem is solved by popf-tif without any lookahead, after searching 7610 states in 15.3 seconds. A different plan is found. The relative efficiency of the search shows the benefit obtained from the information provided by the lookahead.
      </paragraph>
      <paragraph>
       Figs. 22a and 22b show the tap operations of the transformers 0, 4, 7 and 9 and the maximum and minimum voltage profiles of the relevant busbars in the network operating according to the plan in Fig. 21, and solving the problem in online appendix.
      </paragraph>
      <paragraph>
       To show what happens when we require the same tap to be stepped up and down, and therefore need to release the tap before stepping it in the other direction, we present the following plan which is obtained using the same domain description and the small problem example in Appendix B.
      </paragraph>
      <list>
       <list-item>
        0.000:(constraint-check)[24.001]0.000:(step-down-taptap0)[0.100]0.101:(release-decreasingtap0)[3.000]9.901:(step-up-taptap0)[0.100]14.901:(step-up-taptap0)[0.100]15.002:(release-increasingtap0)[3.000]19.901:(step-down-taptap0)[0.100]
       </list-item>
      </list>
      <paragraph>
       We see that, having stepped-down tap 0 at time 0, we have to complete the release-decreasing action before being able to step the same tap up. We note that tap 0 is actually not stepped up again until time 9.901, followed by another step-up at 14.901. The tap is prevented from being stepped down until 17.902, but is not actually stepped-down until 19.901. These delays are in response to the TIFs of the problem, which occur at times 5, 10, 15, 16, 20 and 22. The stepping actions of the plan are timed to respond to these while satisfying the slack period constraints enforced by the release-increasing and release-decreasing actions.
      </paragraph>
      <paragraph>
       Our first experiment compares the popf-tif approach with the Hierarchical Tap Changing Method (see Section 5.3). In the AuRA-NMS network, the hierarchical structure used is as follows:
      </paragraph>
      <list>
       <list-item label="(i)">
        Tap 5, Tap 6, Tap 8 and Tap 14 are transformers that perform voltage step down from the grid to the distribution network and provide regulation of the voltage at this level. These are at the top of the hierarchy.
       </list-item>
       <list-item label="(ii)">
        Tap 1, Tap 0 and Tap 11 are the transformers that control the load variation when distributed generation is inactive or providing low output. These taps operate after the taps in the first group.
       </list-item>
       <list-item label="(iii)">
        Tap 15 regulates the voltage due to load variations.
       </list-item>
       <list-item label="(iv)">
        The remaining transformers are the last ones to act, being the ones responsible for ensuring that distributed generators are safely connected to the rest of the network.
       </list-item>
      </list>
      <paragraph>
       Using the HTC approach, when the direction of power flow opposes the normal flow from the main generation sources, voltages on the upstream busbars might fall outside their safety bounds. An example of such a case is shown in Figs. 22c and 22d, where the HTC approach is applied to our example. As we can see from the plots, the HTC approach violates some voltage constraints, while the planning approach finds a solution that does not violate any constraint and changes a smaller number of taps. The above observation demonstrates the advantage of the planning approach over the HTC approach in meshed networks with distributed generation.
      </paragraph>
      <paragraph>
       The performance of the planning approach depends on the accuracy of the load-series predictions. We now explore the extent to which this is the case.
      </paragraph>
      <paragraph>
       The assumption that we can obtain adequately accurate predictions is valid in current networks for which we have a large amount of historical data. It is, however, challenged by the expected structure of future networks. There will be more ad hoc generation and more load variability than in current networks. In particular, zoning will increase variance by reducing the number of consumers connected to the supply sources in any zone.
      </paragraph>
      <paragraph>
       For this reason we test the robustness of the generated plan, starting from a known load profile and applying the same plan to the network with random variations of the load profile. The different profiles are obtained by scaling all the loads at each time point using a random number that follows a normal distribution with parameters {a mathematical formula}μ=1, {a mathematical formula}σ2=0.001, as shown in Fig. 23. The comparison with the HTC approach, which is run for each new load profile generated, is done by measuring the sum of total violations of voltage for each busbar in the network. This experiment is performed by generating 500 variations of each of 12 different load profiles. The total violation {a mathematical formula}Vtot of a plan with respect to a load profile is measured as the sum of the violations of voltage level at each busbar:{a mathematical formula} where times is the set of timepoints in the execution trace resulting from applying the plan, or HTC approach, over the 24-hour period, and:{a mathematical formula} The quantity {a mathematical formula}Vtk is the total violation at time t and busbar k. The quantity {a mathematical formula}Vt,k is the voltage at time t at busbar k. As is standard in power systems, all voltage measurements are given in per unit volts, meaning that the voltages at a busbar are scaled relative to the nominal target voltage at that busbar. The comparison between the total violations incurred by the planning approach and the reactive approach is shown in Table 1, where the columns represent the total violation of the original load profile, the mean and standard deviation of the total violation and of the number of tap changes operated for the different variation of the load profiles.
      </paragraph>
      <paragraph>
       In the planning approach the same plan is applied to the set of 500 instances for each of the 12 load profiles. This is why the number of tap changes remains constant and the standard deviation is zero. As shown in the table, the planning approach never violates the constraints when there is perfect knowledge of the load-series. However, when there is imperfect prediction, there are cases where it fails to stay within the specified bounds. The HTC approach always performs more tap changes than the planning approach and, despite not relying on any forecast, there are cases in which voltage limits are violated on some of the busbars. Within the range of profiles examined, the total violations incurred by the planning approach are always lower than those incurred by the HTC approach. The above results indicate the need for carefully decomposed zones in conjunction with improved forecasting techniques and show the merit of developing more sophisticated reasoning techniques for solving the AC voltage control problem.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Scalability with respect to the size of the network
      </section-title>
      <paragraph>
       To test the scalability of our approach with respect to network size, we consider problems with networks with an increasing number of busbars and lines. We take as our test network the distribution network described by Prenc et al. [38]. The original network, shown in Fig. 24, consists of 4 feeders with a total of 30 busbars. Bus0 represents a medium voltage busbar of a high/medium voltage (HV/MV) primary substation. An additional generation unit is connected to Bus13. A plan is required for a 24-hour period, given a load profile at half-hour granularity. We run the model with a load profile taken from the National Grid data set for a winter's day of 2012 [39]. In order to see how our system scales in terms of the size of the network, we solve the problem with networks with a decreasing number of busbars. Results are shown in Fig. 25. In the left plot, Fig. 25a, the number of states evaluated as a function of the number of busbars (the complexity of the network) is shown and it indicates that, apart from smaller networks, the number of states evaluated during the search is constant. In the right plot, Fig. 25b, the total execution time and the time consumed by the external solver are presented. In this plot we can see that the execution time increases slightly super-linearly as the network size increases. It can also be seen that the time taken by both the external solver and the planner are well within feasible bounds for a real-time solution approach. The planner time includes the external solver time and all communications between the planner and the solver.
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Scalability with respect to the number of control points
      </section-title>
      <paragraph>
       We now explore the scalability of popf-tif with respect to the number of control points present in the network. For this test we take the 33 kV AuRA-NMS [40] network shown in Fig. 18.
      </paragraph>
      <paragraph>
       For this domain we generated different problems changing the load profiles and the number of transformers present in the network. We start with two transformers, increasing incrementally until the configuration in Fig. 18 is reached.
      </paragraph>
      <paragraph>
       We run popf-tif using two different heuristic settings:
      </paragraph>
      <list>
       <list-item label="•">
        a lookahead of one TIF (1 lookahead);
       </list-item>
       <list-item label="•">
        no lookahead (0 lookahead, corresponding to the standard heuristic setting of popf2).
       </list-item>
      </list>
      <paragraph>
       In Fig. 26 we can see how the search scales with the number of control points. The dots represent the number of states explored during the search for solutions to problems with an increasing number of control points (transformers) and with increasing difficulty measured in terms of the variability of the load profile. In the left plot (Fig. 26a) 1 lookahead is used, while in the right plot (Fig. 26b) 0 lookahead is used.
      </paragraph>
      <paragraph>
       We also consider versions of these problems in which the changes of load and generation profiles are modelled using TILs and dummy actions, rather than TIFs, according to the compilation presented in Section 4.2. Fig. 27 shows the results. In this case, only the easiest problem is solved for all the networks and one other problem is solved for a network with only 2 transformers.
      </paragraph>
      <paragraph>
       We used the Wilcoxon signed-rank test to measure the significance of the difference in performance obtained using the lookahead heuristic as opposed to using the standard heuristic setting of popf2.
      </paragraph>
      <paragraph>
       For the 192 problems we calculate the absolute difference in execution time of the planner with and without the lookahead heuristic. We exclude the 21 problems for which the difference is 0. The remaining {a mathematical formula}Nr=171 problems are ordered from the smallest to the largest absolute difference, and a rank, {a mathematical formula}Ri, is assigned to each pair.
      </paragraph>
      <paragraph>
       The test statistic W is calculated as:{a mathematical formula}
      </paragraph>
      <paragraph>
       Then, the z-score is calculated as{a mathematical formula} where{a mathematical formula}
      </paragraph>
      <paragraph>
       This procedure gives a z-score of {a mathematical formula}z=10.25, which means that the difference in performance is highly significant. Of course, the Wilcoxon signed-rank test assumes that each pair is independent, which is not entirely true in our sample. The problems are all independently generated variations of the same basic problem, with different load profiles and different numbers of transformers.
      </paragraph>
     </section>
     <section label="8.4">
      <section-title>
       Evaluation of the network abstraction
      </section-title>
      <paragraph>
       In this section we test the effectiveness of the network abstraction in four different configurations of the planner. Our problem is a Localised BTMP as defined in Definition 6. For this evaluation we start with the four-feeder distribution system, shown in Fig. 28 and based on the network described by Su and Lee [41]. We then create a problem set by increasing difficulty along two dimensions. On one dimension we increase the number of capacitors. On the other, we increase the variability of the load profile. The problems using 5 and 6 capacitors are obtained by removing capacitors C1 and C3 from the network in Fig. 28. The problems with more than 7 capacitors are obtained by successively adding capacitors to busbars B3, B4, B7, B8, B9, B10 and B15. All of the problems are subjected to the same 6 load variations. This gives us a collection of 60 problems in total. The purpose of the experiment is to investigate the trade-off between the informativeness of the heuristic and the time spent computing it. The four configurations considered are the following:
      </paragraph>
      <list>
       <list-item label="(a)">
        0 lookahead and no use of the network abstraction (i.e. {a mathematical formula}(step-max ?c ?b)=(step-min ?c ?b)=0, for all capacitors and busbars);
       </list-item>
       <list-item label="(b)">
        1 lookahead and a simple network abstraction in which capacitor effects are treated as an identical constant for all capacitors that have a non-negligible effect on a busbar, 0 otherwise (neighbourhood abstraction);
       </list-item>
       <list-item label="(c)">
        1 lookahead and a network abstraction defined in the initial state (static first order approximation);
       </list-item>
       <list-item label="(d)">
        1 lookahead and state-dependent update of the network abstraction. That is, the capacitor effects are treated as {a mathematical formula}Vspecial variables and updated in each state by a call to the external solver (dynamic first order approximation).
       </list-item>
      </list>
      <paragraph>
       In case (a) the heuristic contains no information about the effects of actions or TIFs on the voltage. It is not necessary to consider 0 lookahead in any of the other cases, since the network abstraction would be ignored if 0 lookahead were used.
      </paragraph>
      <paragraph>
       The results are shown in Fig. 29. The plots show the number of states evaluated in the four different configurations of the heuristic for the different load profiles and for problems with an increasing number of capacitors. The number of transformers and generators is fixed throughout. As we can see, configurations (a) and (b) lead to many states being explored. The approximation of the indirect effects is highly accurate for both configurations (c) and (d). The difference between these two configurations in terms of states explored is minimal. Configuration (d) searches slightly fewer states in the middle difficulty problems, although this cannot be seen in the figure. It searches more states in the hardest problems, which is an artefact of the tie-breaking between equal-valued states in the search for a plan.
      </paragraph>
      <paragraph>
       Fig. 30 shows the CPU time required by the four configurations of popf-tif on the 6 problem sets corresponding to each of the 6 load profiles. Configuration (a) is very expensive in all cases, and cannot solve the harder problems. In problem sets 1, 2, 3 and 4, the neighbourhood-based heuristic, configuration (b), is just as good as a more accurate approximation. However, in problem sets 5 and 6 this ceases to be the case. Configuration (c) performs well in all of the problems, while configuration (d) becomes too expensive as the problem difficulty and number of capacitors grow.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     The extended pddl2.2 domain description for the AC voltage control problem
     <paragraph>
      In the following, we present the AC voltage control domain, as used by popf-tif. We introduce some new syntax to allow us to define the external (encapsulated) type, Network, and a collection of external functions which form the interface between the planner and external solver. In fact, this syntax can be pre-processed into pddl2.2 with TIFs, combined with a suitably defined external library module. This is shown in the domain model presented in the online appendix. Our approach is to do this pre-processing, but we show the intended domain representation as a first step towards a clean interface between popf-tif and its external solvers.
     </paragraph>
     <list>
      <list-item>
       (define(domainAPS)(:requirements:strips:typing:fluents:universal-preconditions:disjunctive-preconditions:conditional-effects:duration-inequalities:durative-actions:timed-initial-literals:preferences:constraints)(:external-typeNetwork)(:typesshedding-load-loadload-objectswitch-lineline-objectp-gen-genq-gen-genslack-gen-p-genslack-gen-q-genextern-gen-genintern-gen-genpv-gen-q-gengen-objectbus-objectdevice-objecttap-devicecapacitor-device)(:predicates(is-available?t-tap)(is-before-end)(is-end)(S)(F)(is-active?c-capacitor)(is-not-active?c-capacitor)(is-not-increasing?t-tap)(is-not-decreasing?t-tap)(is-increasing?t-tap)(is-decreasing?t-tap)(can-increase?t-tap)(can-decrease?t-tap))(:functions(p-level?l-load)(q-level?l-load)(p-shedding?l-shedding-load)(q-shedding?l-shedding-load)(p-minimum-shedding?l-shedding-load)(tap-level?t-tap)(switch-level?s-switch)(line-power?l-line)(gen-p-level?g-gen)(gen-q-level?g-gen)(slack-p?g-p-gen)(slack-q?g-q-gen)(p-maximum-gen?g-gen)(p-minimum-gen?g-gen)(q-maximum-gen?g-gen)(q-minimum-gen?g-gen)(can-import?g-extern-gen)(cost-gen)(cost-slack)(cost-shedding)(total-cost-gen)(total-cost-slack)(total-cost-shedding)(step-min?t-device?b-bus)(step-max?t-device?b-bus)(capacitor-level?c-capacitor)(maximum-voltage?b-bus)(minimum-voltage?b-bus)(slack-period?t-device)(maximum-outage?t-shedding-load)(max-tap-level?t-tap)(min-tap-level?t-tap))(:external-functions(step-up-effect?t-tap)(step-down-effect?t-tap)(capacitor-effect?c-capacitor)(voltage?b-busbar))(:constantsthenetwork-Network)(:durative-actionstep-down-tap:parameters(?t-tap):duration(=?duration0.1):condition(and(atstart(is-not-increasing?t))(atstart(is-available?t))(atstart(&gt;(tap-level?t)(min-tap-level?t)))):effect(and(atstart(not(is-not-decreasing?t)))(atstart(not(is-available?t)))(atend(is-available?t))(atend(is-decreasing?t))(atend(decrease(tap-level?t)1))(atend(decrease(thenetwork)(step-down-effect?t)))))(:durative-actionrelease-decreasing:parameters(?t-tap):duration(=?duration(slack-period?t)):condition(and(atstart(is-decreasing?t))):effect(and(atend(is-not-decreasing?t))(atstart(not(is-decreasing?t)))))(:durative-actionrelease-increasing:parameters(?t-tap):duration(=?duration(slack-period?t)):condition(and(atstart(is-increasing?t))):effect(and(atend(is-not-increasing?t))(atstart(not(is-increasing?t)))))(:durative-actionstep-up-tap:parameters(?t-tap):duration(=?duration0.1):condition(and(atstart(is-not-decreasing?t))(atstart(&lt;(tap-level?t)(max-tap-level?t)))(atstart(is-available?t))):effect(and(atstart(not(is-not-increasing?t)))(atend(is-increasing?t))(atstart(not(is-available?t)))(atend(is-available?t))(atend(increase(tap-level?t)1))(atend(increase(thenetwork)(step-up-effect?t)))))(:durative-actionrelease-capacitor:parameters(?t-capacitor):duration(=?duration3):condition(and(atstart(is-available?t))):effect(and(atend(is-available?t))(atstart(not(is-available?t)))))(:durative-actionactivate-capacitor:parameters(?c-capacitor):duration(=?duration0.1):condition(and(atstart(is-not-active?c))(atstart(is-available?c))):effect(and(atstart(not(is-not-active?c)))(atstart(not(is-available?c)))(atend(is-active?c))(atend(increase(thenetwork)(capacitor-effect?t)))))(:durative-actiondeactivate-capacitor:parameters(?c-capacitor):duration(=?duration0.1):condition(and(atstart(is-active?c))(atstart(is-available?c))):effect(and(atstart(not(is-active?c)))(atstart(not(is-available?c)))(atend(is-not-active?c))(atend(decrease(thenetwork)(capacitor-effect?t)))))(:durative-actionconstraint-check:parameters():duration(&lt;=?duration1000):condition(and(atstart(S))(atend(F))(overall(forall(?b-Bus)(and(&lt;=(thenetwork.voltage?b)(maximum-voltage?b))(&gt;=(thenetwork.voltage?b)(minimum-voltage?b)))))):effect(and(atend(is-end)))))
      </list-item>
     </list>
    </section>
    <section label="Appendix B">
     <section-title>
      A small problem instance for the AC voltage control problem
     </section-title>
     <list>
      <list-item>
       (define(problemAPS-problem)(:domainAPS)(:objectsbusbar1-busload0-loadtap0-tap)(:init(S)(at0.1(not(S)))(at24(F))(=(tap-leveltap0)0)(is-availabletap0)(is-not-increasingtap0)(is-not-decreasingtap0)(=(ipsa-voltagebusbar1)0.95)(=(maximum-voltagebusbar1)1)(=(minimum-voltagebusbar1)0.94)(=(max-tap-leveltap0)4)(=(min-tap-leveltap0)-9)(=(slack-periodtap0)3)(=(step-mintap0busbar1)0.0031);0.0035)(=(step-maxtap0busbar1)-0.0031)(=(p-levelload0)3.5)(=(q-levelload0)0.5)(at5(=(p-levelload0)8.5))(at5(=(q-levelload0)0.5))(at10(=(p-levelload0)3.5))(at10(=(q-levelload0)0.5))(at15(=(p-levelload0)3.3))(at15(=(q-levelload0)0.5))(at16(=(p-levelload0)2))(at16(=(q-levelload0)0.5))(at20(=(p-levelload0)5))(at22(=(p-levelload0)7))(at22(=(q-levelload0)0.5)))(:goal(and(is-end))))
      </list-item>
     </list>
    </section>
    <section label="Appendix C">
     <section-title>
      A more detailed explanation of the power flow equations
     </section-title>
     <paragraph>
      The computation of the voltage at each node of the network, for specified loads and generation configurations, is called the power flow (or load flow) problem. The nodes of the networks are called busbars (or buses). They are strips of electrical conductors with the main purpose of conducting electricity between two branches (lines and cables) of the network.
     </paragraph>
     <paragraph>
      There are four variables associated with a busbar k: voltage magnitude, {a mathematical formula}Vk, phase angle, {a mathematical formula}δk, real power, {a mathematical formula}Pk, and reactive power, {a mathematical formula}Qk. Real (sometimes called active) power and reactive power are two complementary forms of power. Real power is the quantity associated with the total energy absorbed by a load during a time interval of one cycle of the sinusoidal voltage.
     </paragraph>
     <paragraph>
      The goal of a power-flow study is to obtain complete voltage angle and magnitude information for each bus in a power system for specified load and generator real power and voltage conditions. Once this information is known, real and reactive power flow on each branch as well as generator reactive power output can be analytically determined. Due to the non-linear nature of this problem, numerical methods are employed to obtain a solution that is within an acceptable tolerance.
     </paragraph>
     <paragraph>
      In general, the total power delivered to a busbar k is divided into two parts, the generation and the load:{a mathematical formula} For the power flow computation two of these variables are given as input data, while the other two are computed. Each busbar k is then categorised into different bus types, according to the input variables:
     </paragraph>
     <list>
      <list-item label="•">
       Slack busbar (or swing busbar): one bus in the network is defined to balance the active and reactive power of the system. The voltage magnitude{sup:5}{a mathematical formula}Vk and the phase angle {a mathematical formula}δk are assumed to be known and they are generally {a mathematical formula}Vk=1 pu (per unit Volts) and {a mathematical formula}δk=0. The power flow equations are over-constrained (the matrix of coefficients is singular), so the slack bus is needed to provide an additional degree of freedom. It corresponds physically to the freedom of choice about initial phase angle.
      </list-item>
      <list-item label="•">
       Load busbar (or PQ):{a mathematical formula}Pk and {a mathematical formula}Qk are given as input, while {a mathematical formula}Vk and {a mathematical formula}δk are calculated by the power flow.
      </list-item>
      <list-item label="•">
       Voltage controlled busbar (or PV): for this busbar {a mathematical formula}Pk and {a mathematical formula}Vk are input data and {a mathematical formula}Qk and {a mathematical formula}δk are computed.
      </list-item>
     </list>
     <paragraph>
      In order to perform the power flow calculation, the admittance matrix {a mathematical formula}Ybus must be constructed from the line and transformer input data, where {a mathematical formula}Ykk is the sum of admittances of lines connected to bus k, and {a mathematical formula}Ykn is the negation of the sum of admittances connected between buses k and n (with {a mathematical formula}k≠n).
     </paragraph>
     <paragraph>
      The steady state AC power flow for the busbar k is then given by:{a mathematical formula} where {a mathematical formula}Vk is the complex voltage {a mathematical formula}Vkejδk and j is the complex square root of −1. In rectangular coordinates the power flow equations are expressed as:{a mathematical formula} where {a mathematical formula}Ykn=Yknejθkn=Gkn+jBkn. The quantities {a mathematical formula}Gkn and {a mathematical formula}Bkn are called respectively reactance and susceptance of the line between busbars k and n.
     </paragraph>
     <paragraph>
      The generalisation of the power flow equations (C.3), which includes transformers, is modelled by modifying the admittance matrix Y. Given a transformer connected between busbars k and n:{a mathematical formula}
     </paragraph>
     <paragraph>
      Due to the non-linearity of the power flow equations, their integration through traditional decision-support tools is very limited. Instead, different linear approximations can be applied in situations in which it is possible to consider only the active power. This is the case of transmission networks, where the ratio {a mathematical formula}Gkn/Bkn is very small, the phase angle difference is small enough and the voltage magnitudes are close to 1.0 pu, so that the Equations (C.3) reduce to:{a mathematical formula}
     </paragraph>
     <paragraph>
      A recent review by Stott et al. [42], considers a different approximation, called DC power flow. The approximations differ in the definition of the admittance matrix and the expression of the power flow equation. At the distribution level, however, the voltage ratio between the conductance and the susceptance is non-negligible, and the reactive power needs to be taken into account in the computation of the voltage variables.
     </paragraph>
    </section>
    <section label="Appendix D">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>