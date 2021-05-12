<html>
<head>
<meta name="TextLength" content="SENT_NUM:42, WORD_NUM:948">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we have extended previously developed temporally flexible execution systems for discrete activity plans to work with hybrid discrete/continuous systems such as robots operating in unstructured environments.</a>
<a href="#1" id="1">We have achieved this by first developing a representation for temporally and spatially flexible tasks for hybrid systems, called a Qualitative State Plan (QSP), then developing a plan compiler that transforms the QSP to a QCP, which is easier to execute, and then developing a plan dispatcher that executes the QCP.</a>
<a href="#2" id="2">The plan compiler leverages a recently developed Linear Quadratic Regulator synthesis algorithm to compute flow tubes, and combines these with plan compilation techniques used in discrete activity systems.</a>
<a href="#3" id="3">The QCP produced by the plan compiler represents the set of feasible trajectories in an easily executable form.</a>
<a href="#4" id="4">The dispatcher is based on ones developed for discrete activity systems [9], but extends these to allow for indirect scheduling of events through control actions applied to a dynamic system, thus allowing the approach to be used for hybrid systems.</a>
<a href="#5" id="5">An important attractive property of this approach is that it clearly represents the boundaries between feasible and infeasible states and times with respect to successful plan execution.</a>
<a href="#6" id="6">This allows the system to detect that a plan will fail, sooner rather than later.</a>
<a href="#7" id="7">It is interesting that traditional control theory does not explicitly address the issue of temporal flexibility.</a>
<a href="#8" id="8">Traditional control theory deals with two basic kinds of problems: stabilization, and trajectory following [35].</a>
<a href="#9" id="9">Stabilization is an infinite-time concept; a system is stable if it converges to an equilibrium point at some time in the future, possibly, infinity.</a>
<a href="#10" id="10">Thus, stabilization has infinite temporal flexibility.</a>
<a href="#11" id="11">Reference trajectory following, on the other hand, has no temporal flexibility.</a>
<a href="#12" id="12">If the control system tracks the reference trajectory exactly, it will reach a goal state at a specific time.</a>
<a href="#13" id="13">We believe that this is a significant omission.</a>
<a href="#14" id="14">Temporal flexibility exists in most task specifications, and should be taken advantage of to achieve robust and efficient plan execution.</a>
<a href="#15" id="15">The approach described here is intended for inherently under-actuated systems, such as bipeds or aerial vehicles, where there are more degrees of freedom to be controlled than actuators to control them.</a>
<a href="#16" id="16">However, even systems that are fully actuated, such as most robot manipulators, can have actuation limits that become relevant for demanding tasks.</a>
<a href="#17" id="17">For example, moving a robot manipulator at high speeds so that it can perform tasks quickly exposes the velocity and acceleration limits of the joints.</a>
<a href="#18" id="18">The performance of model-based approaches, such as the one described here, are heavily dependent on the quality of the model.</a>
<a href="#19" id="19">Synthesis of appropriate models is beyond the scope of this report, but is an important, active area of research.</a>
<a href="#20" id="20">The approach described here is reactive to disturbances, in that when a disturbance occurs, optimal control actions are computed without taking into account the possibility of future disturbances.</a>
<a href="#21" id="21">A more pro-active approach is to incorporate a disturbance model and take this into consideration so that computed control actions have some buffer against future disturbances.</a>
<a href="#22" id="22">This is beyond the scope of this report, but is an active area of research for our group [36].</a>
<a href="#23" id="23">An important, unresolved question related to this type of approach is the computational trade-off between compile time and run time computation.</a>
<a href="#24" id="24">Our premise is that there are applications (walking bipeds, for example) that require very fast runtime decision making.</a>
<a href="#25" id="25">For these types of applications, moving computation to compile time is necessary for the system to work at all.</a>
<a href="#26" id="26">Further, we envision systems in which a higher-level control authority generates complex behavior in complex environments by selecting QSPs from a large pre-compiled library, and combining them as needed.</a>
<a href="#27" id="27">This may require some minor adjustment of the pre-compiled QSPs, but far less effort than the original compilation.</a>
<a href="#28" id="28">For example, the QSP for biped walking presented earlier represents a gait cycle.</a>
<a href="#29" id="29">Upon successful execution of such a gait cycle, the same plan (with minor adjustments offsetting time and goal position) can be executed again, without further compilation.</a>
<a href="#30" id="30">The general trade-off between compile time and runtime computation is still an open area of research, and is beyond the scope of this paper.</a>
<a href="#31" id="31">It involves investigation of important questions like how to parameterize QSPs so that they can be modified and re-used with minimal compilation, and the investigation of architectures that allow the weighting between compile time and run time effort to be varied.</a>
<a href="#32" id="32">It is clear that using “envelopes” as we have done, and as Pecora, et al. do [37], can be very beneficial to runtime performance.</a>
<a href="#33" id="33">The question is how much computational effort should be put into computing as tight an envelope as possible, and to what level of detail.</a>
<a href="#34" id="34">This depends on what is needed at runtime, and is a topic of ongoing research.</a>
<a href="#35" id="35">A related issue is how well our approach scales as problem size increases.</a>
<a href="#36" id="36">Although we do not yet have enough quantitative results to make strong statements about how compilation time scales as problem size grows, we have a high degree of confidence that there is a large class of problems for which our approach scales well.</a>
<a href="#37" id="37">A key idea in our work is decoupling of a hybrid system into loosely decoupled components.</a>
<a href="#38" id="38">The components may be different reaction points on a robot (such as CM, swing foot, and hand), or different robots, for example.</a>
<a href="#39" id="39">The loose coupling allows for these components to execute behavior using independent activities, synchronized by temporal constraints.</a>
<a href="#40" id="40">The approach is inspired by well-known decoupling approaches in control theory, such as feedback linearization, which are used to address the “curse of dimensionality”.</a>
<a href="#41" id="41">Similarly, by taking advantage of loose coupling, and separating component activities in a plan, we avoid combinatoric explosions in high degree of freedom systems.</a>
</body>
</html>