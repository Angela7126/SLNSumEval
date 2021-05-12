<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:334">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we presented a framework for envisioning the effects of everyday robot manipulation actions using physics-based simulations.</a>
<a href="#1" id="1">Within this framework, we designed and implemented components for asserting the initial conditions of a manipulation scenario and for utilizing a simulation-based approach for making temporal projections about parameterized robot control programs.</a>
<a href="#2" id="2">We conducted experiments for three scenarios in which the formal parameters of robot control programs were systematically selected from ranges of possible values.</a>
<a href="#3" id="3">These experiments, or more precisely their resulting timelines, were evaluated with respect to specified performance criteria, e.g. desired and undesired effects.</a>
<a href="#4" id="4">We also discussed the demands of equipping robots with means to perform naive physics reasoning and provided arguments for basing this reasoning on detailed physical simulation.</a>
<a href="#5" id="5">In future work, we will continue our research on how we can extract information from human demonstrations performed in a virtual manipulation environment to automatically determine the parameter space of robot manipulation actions from timelines [38].</a>
<a href="#6" id="6">Furthermore, to cope with the uncertainty inherent in robot manipulation tasks we will extend our approach by integrating probabilistic representations over timelines as briefly outlined in Section 3.1.</a>
<a href="#7" id="7">Finally, we will also integrate our system with a real robot.</a>
<a href="#8" id="8">This integration will pose several challenges.</a>
<a href="#9" id="9">For instance, a robot has to recognize task-related objects and it has to estimate their poses in order to assert and instantiate a new scenario within the framework.</a>
<a href="#10" id="10">Secondly, during the execution of an action plan the robot has to observe the objects in the real world and it has to continuously estimate their states in order to allow the framework to generate timelines.</a>
<a href="#11" id="11">For some types of objects, such as fluids, this would be very challenging.</a>
<a href="#12" id="12">However, as a first step towards an integrated system we will start with a rigid object manipulation scenario.</a>
<a href="#13" id="13">We believe that the presented framework provides important functionality for robots by giving them the ability to autonomously determine the action parameterizations for underspecified and ambiguous instructions by the means of logic programs using simulation-based temporal projections.</a>
</body>
</html>