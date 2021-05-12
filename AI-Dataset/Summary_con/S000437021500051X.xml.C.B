<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:563">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have presented an approach to hybrid planning for complex robotic platforms.</a>
<a href="#1" id="1">The approach is based on the concept of hybrid states, i.e. states that have both a symbolic component and a geometric component.</a>
<a href="#2" id="2">The former is used for causal and logical reasoning, whereas the latter is used for geometric reasoning tasks such as motion planning.</a>
<a href="#3" id="3">These states, together with the hybrid actions that transform them, constitute a combined search space where each symbolic state component can be paired with many different geometric state components.</a>
<a href="#4" id="4">When the planner selects an action, it also needs to determine how to perform that action geometrically.</a>
<a href="#5" id="5">For example, in a manipulation domain, the latter includes choosing how to grasp an object, exactly in what pose to put it down, and how to perform motions of the manipulators, both with or without objects being held.</a>
<a href="#6" id="6">As the geometric/kinematic space is continuous, these choices involve sampling points in this space.</a>
<a href="#7" id="7">These kinds of choices on the geometric level will constrain geometric choices later in the plan.</a>
<a href="#8" id="8">Still, these choices have to be made: motion planning requires specific geometric states.</a>
<a href="#9" id="9">Hence, it is necessary to be able to backtrack on the geometric level as well as on the symbolic level.</a>
<a href="#10" id="10">However, geometric backtracking can be prohibitively expensive, as the branching factor (determined by the sampling resolution for actions/predicates) may be very high, there can be many backtrack points, and each step may involve a motion planning problem.</a>
<a href="#11" id="11">Previous experiments have shown that geometric reasoning and in particular motion planning dominates the computation effort by several orders of magnitude [2].</a>
<a href="#12" id="12">During backtracking, each action in the current plan may actually induce a large number of motion planning problems.</a>
<a href="#13" id="13">For that reason, we have considered how to perform informed backtracking, where one selects backtrack points using heuristics based on statistics for kinematic violations and collisions with movable objects.</a>
<a href="#14" id="14">The idea is that certain preceding choices will be irrelevant to the present actions: in particular actions that involve other objects and distant positions.</a>
<a href="#15" id="15">We have demonstrated speedups of an order of magnitude using such techniques, the most successful one being a collision heuristic.</a>
<a href="#16" id="16">Our experiments in simulation show clearly that the propagation of constraints on the kinematics of the robot, on the regions in the work space, and on the feasible grasps can reduce the size of the geometric search space, in particular when specific orientations are imposed on the final poses of objects.</a>
<a href="#17" id="17">Geometric constraints also play an important role in the combined symbolic and geometric search.</a>
<a href="#18" id="18">By quickly detecting geometrically inconsistent partial plans (which would otherwise require a large amount of geometric backtracking), a larger part of the symbolic search space can be explored.</a>
<a href="#19" id="19">Our approach has been applied to a particularly challenging real robotic platform, the Justin robot at DLR.</a>
<a href="#20" id="20">We have demonstrated it in a range of different scenarios, with tasks involving multiple objects in small areas (trays), large obstacles (boxes), small movable obstacles, and using an intermediary position to regrasp an object.</a>
<a href="#21" id="21">We have also presented simulated experiments in a distinct domain with different kinematics: a forklift transporting pallets in a warehouse.</a>
<a href="#22" id="22">For the latter scenario, we have made comparisons to approaches with no or limited geometric backtracking.</a>
<a href="#23" id="23">We have found that geometric backtracking performs best, but lack of backtracking can to some extent be compensated for by carefully crafted domain-specific heuristics for geometric choices.</a>
</body>
</html>