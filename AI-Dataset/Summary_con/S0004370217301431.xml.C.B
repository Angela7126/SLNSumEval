<html>
<head>
<meta name="TextLength" content="SENT_NUM:38, WORD_NUM:900">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we introduced the Strong Temporal Planning with Uncontrollable Durations (STPUD ) problem, which extends Temporal Planning to deal with actions having uncontrollable duration.</a>
<a href="#1" id="1">We search for temporally strong solutions, i.e. plans that are guaranteed to achieve the goal regardless of the actual duration of the actions that are under the control of the execution environment.</a>
<a href="#2" id="2">We presented two complementary approaches.</a>
<a href="#3" id="3">The first one is based on the integration of a “classical” temporal planner with a solver for temporal networks with uncertainty.</a>
<a href="#4" id="4">The second approach reduces any STPUD problem to a “classical” temporal planning problem, where the actions have controllable durations.</a>
<a href="#5" id="5">Finally, we proposed a technique that is able to eliminate some of the uncontrollable durations by reasoning in terms of worst case execution.</a>
<a href="#6" id="6">We implemented and experimentally evaluated the approaches.</a>
<a href="#7" id="7">The results demonstrate the complementarity of the two planning methods, and of the effectiveness of the proposed optimizations.</a>
<a href="#8" id="8">This work is a first step in a more comprehensive research effort on real-wold planning with durative actions.</a>
<a href="#9" id="9">The target is a richer domain description language based on ANML [31], extended with uncertain durations, uncertain resource usage, and uncontrollable effects, all of which allow more natural representation of real-world domains and overcome the many limitations of PDDL.</a>
<a href="#10" id="10">In particular, several directions can be explored.</a>
<a href="#11" id="11">First, some interesting features, such as timed initial literals with uncontrollable time windows and conditional effects, are not included in the abstract language used in this paper because they are not fundamental to explain the characteristics of the approach.</a>
<a href="#12" id="12">Timed initial literals have been modeled as fixed-time effects that happen exogenously in every plan, but we can allow TILs having a time window in which they can controllably or uncontrollably occur.</a>
<a href="#13" id="13">Such a feature could be useful to model unpredictable events and can be easily handled in our framework by considering each TIL as the end effect of an action (controllable or uncontrollable) that must be started at time 0.</a>
<a href="#14" id="14">In this view, both the approaches we presented can be extended to deal with non-fixed or even uncontrollable TILs.</a>
<a href="#15" id="15">Conditional effects are another useful feature that can be included in our language.</a>
<a href="#16" id="16">Unlike uncertainty in TILs, this feature requires more adaptation in order to be included in our framework.</a>
<a href="#17" id="17">The compilation approach we presented is based on the assumption that at each point in time while executing a plan, each variable can be either certain, meaning that we know the exact value, or uncertain between exactly two values.</a>
<a href="#18" id="18">Moreover, we know that outside of uncertainty intervals, all the variables are certain.</a>
<a href="#19" id="19">The introduction of conditional effects changes this situation: if a conditional effect with a condition on variable f takes place while f is uncertain, the outcome of the effect is uncertain.</a>
<a href="#20" id="20">This uncertainty is not removed at the end of the uncertainty intervals and multiple conditional effects can increase the cardinality of the set of possible uncertain values.</a>
<a href="#21" id="21">One possible idea to deal with this problem is to extend our compilation to allow a bounded number of uncertain values for each variable, so that we can accommodate a finite number of uncertain effect occurrences.</a>
<a href="#22" id="22">This approach would maintain the soundness of the compilation, but sacrifice completeness.</a>
<a href="#23" id="23">Another interesting question is whether a compilation approach can be developed to handle (uncertain) resource usage.</a>
<a href="#24" id="24">In this paper we do not consider resources, but they are important in many planning applications.</a>
<a href="#25" id="25">Resources can be uncertain due to different factors.</a>
<a href="#26" id="26">Either the production or consumption of a resource depends on the duration of some uncontrollable action (e.g. the amount of fuel consumed in a trip depends on its duration, which is uncontrollable because of uncontrollable traffic conditions), or the amount being added or removed for a resource is uncertain by itself (e.g. the amount of energy produced by a solar panel depends on uncontrollable weather conditions).</a>
<a href="#27" id="27">One idea to extend our work in this direction is to encode the resource profile with the upper and lower bounds and modifying conditions accordingly.</a>
<a href="#28" id="28">This compilation would probably be sound but incomplete, but more research is needed to fully understand the issues.</a>
<a href="#29" id="29">In terms of planning problems, another challenge is to deal with the ability of the executor to observe the end of actions with uncontrollable duration.</a>
<a href="#30" id="30">This amounts to lifting to the level of planning the TNU notion of dynamic controllability.</a>
<a href="#31" id="31">We would like to produce plans that are able to change their course of action based on the duration of activities observed at run-time.</a>
<a href="#32" id="32">Notice that in STPUD the start of actions is decided a-priori, and plans must achieve the goal “blindly” (which is the planning counterpart of strong controllability in TNU ).</a>
<a href="#33" id="33">On the experimental side, we would like to better understand the impact of the intermediate effect constructions (such as clip-actions) by modifying a PDDL temporal planner to natively understand such constructions.</a>
<a href="#34" id="34">Another direction we would like to pursue is to study the compilation technique performance using a native ANML planner.</a>
<a href="#35" id="35">Finally, we intend to study the planand domain-validation problems for the case of STPUD, by using techniques based on formal verification.</a>
<a href="#36" id="36">In fact, validating a plan when uncertainty is present is no trivial task, and so is the development of domain models for complex applications.</a>
<a href="#37" id="37">We want to investigate automated techniques that can help domain experts in the creation and debugging of planning models to foster the applicability of the planning technologies presented in this paper.</a>
</body>
</html>