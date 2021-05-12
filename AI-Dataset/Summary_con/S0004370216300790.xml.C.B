<html>
<head>
<meta name="TextLength" content="SENT_NUM:37, WORD_NUM:979">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented in this paper an instance of a complete deliberative architecture designed for social robots.</a>
<a href="#1" id="1">While most of its sub-components have been independently presented in other publications, we offer here for the first time a perspective on the model of integration of these components into a coherent and consistent system for social human–robot interaction.</a>
<a href="#2" id="2">We have first exposed our underlying knowledge model based on Description Logics [28] and some of the resulting reasoning capabilities pertaining to disambiguation [17] and mental modelling [45] that are shown to effectively scaffold interaction using human-level semantics and cognitive skills.</a>
<a href="#3" id="3">We have then presented our approach to symbol grounding, build on an amodal situation assessment environment [61] that supports perspective taking [64], [67].</a>
<a href="#4" id="4">We combine it further with a situated natural language processor [74] to provide complete multi-modal interactive communication.</a>
<a href="#5" id="5">The paper also covers our symbolic social task planner [75], [76], [77]: it generates predictive plans of the human actions that enable the system to plan for joint human–robot tasks.</a>
<a href="#6" id="6">It can also make use of social heuristics to optimise plans for social acceptability.</a>
<a href="#7" id="7">We briefly mention our human-aware motion and manipulation planner [91], [105], [92], [97], [93], [95], and finally present two execution controller, the PRS-based Shary[83], [89], [2] and the event-driven pyRobots[85].</a>
<a href="#8" id="8">The integration of these components in a consistent, working and observable system builds upon the particular design of the interfaces between the cognitive components: the information streams use high-level semantics, represented as first-order logic statements.</a>
<a href="#9" id="9">In that sense, our deliberative architecture is similar to projects like cram[32], KeJia [35] or PEIS Ecology [106], [39], with however a stronger emphasise on the specificities of the interaction with humans.</a>
<a href="#10" id="10">Importantly, we distinguish ourselves from research on cognitive architectures: cognitive architectures are usually understood as an artificial yet principled model of (human) cognition.</a>
<a href="#11" id="11">While some have been deployed on autonomous robots, like HAMMER [107] or ACT-R/E [22], most are primarily concerned with the modelling of human cognition and are less focused on the effective deployment on socially interactive robots.</a>
<a href="#12" id="12">In that sense, our contribution in terms of architecture is a practical one: our integration model enables to consistently combine a large set of technically independent yet cognitively interdependent cognitive processes.</a>
<a href="#13" id="13">We bridge them through explicit, human-level semantics, and we show that this results in a fully implemented system, effectively deployed on several platforms and in several real interaction scenarios.</a>
<a href="#14" id="14">This work introduces several new contributions related to the representation and the management of humans in an autonomous robotic system.</a>
<a href="#15" id="15">Specifically, we mentioned in the introduction the following four points:</a>
<a href="#16" id="16">our system achieves multi-modal and interactive grounding in complex real environments involving one or several humans and a robot; it supports a distributed computation of symbolic knowledge for situated dialogue, thanks to the combination of perspective taking, affordances computation and logical inference; it provides generic mechanisms for the robot to reason about the mental state of its human partners; and, by reusing the computed affordances and inference, it generates, monitors and takes part to human–robot shared plans.</a>
<a href="#17" id="17">While several contributions in the literature provide insights and contributions on one aspect or another (references are in the corresponding subsections), we are not aware of a fully implemented architecture that effectively combines in a coherent manner all these points.</a>
<a href="#18" id="18">The novelty and relevance of this contribution to HRI is further underlined by the range of multi-disciplinary collaborations and studies that have been made possible by our architecture [15], [16], [17], [18], [19], [20].</a>
<a href="#19" id="19">The design choices and the results presented here are still preliminary.</a>
<a href="#20" id="20">While the general scheme we propose might be difficult to implement in a general sense, we believe that it is a reasonable challenge to implement it in the case of a personal robot assistant essentially devoted interactive manipulation tasks and associated activities.</a>
<a href="#21" id="21">One direction that we would like to further investigate is how to account for situations where divergent beliefs appear between the human and the robot.</a>
<a href="#22" id="22">Some preliminary results have been presented in [45], [108] where we consider divergent beliefs about the state of the world, and in [13] where the robot is able to deal with divergent beliefs related to the state of the task.</a>
<a href="#23" id="23">There is also extensive work to be done in order to refine the notion of “good shared plan” and “good/acceptable robot behaviour” in this context.</a>
<a href="#24" id="24">There are large avenues for learning and adaptation in this context.</a>
<a href="#25" id="25">Another direction to head to deals with context representation.</a>
<a href="#26" id="26">Contexts are currently often limited to the current spatial and temporal situation.</a>
<a href="#27" id="27">Some of our models offer the possibility to jump in the past or to switch to another agent's perspective, but in our current approach, selecting a context essentially consists in retrieving a set of beliefs corresponding to a situation, and temporarily replacing the current beliefs by those other ones.</a>
<a href="#28" id="28">This misses the fact that at a given moment, not one but many contexts co-exist at different scales.</a>
<a href="#29" id="29">We do not want to retrieve one monolithic set of beliefs, but instead carefully craft a context from several atomic contexts.</a>
<a href="#30" id="30">Techniques for representation of overlapping “pools” of knowledge largely remain to be developed, as well as efficient algorithms to retrieve (or discard) such context-related pools of knowledge.</a>
<a href="#31" id="31">This is a challenge not only for robotics, but more generally for artificial intelligence.</a>
<a href="#32" id="32">The ability to explicitly manage contexts and context switches would endow the robot with a cognitive capability similar to what is known as context-dependent memory in cognitive psychology.</a>
<a href="#33" id="33">This is also related to Tulving's autonoetic consciousness[109]: the ability to reflect upon its own past or future experiences.</a>
<a href="#34" id="34">Much remain to be done to this regard, starting with a formal analysis of what are the relevant contexts for our robots.</a>
<a href="#35" id="35">Human–Robot Interaction is and will remain a challenging field for Artificial Intelligence.</a>
<a href="#36" id="36">We hope that this contribution helps with clarifying these challenges and making them concrete decisional problems.</a>
</body>
</html>