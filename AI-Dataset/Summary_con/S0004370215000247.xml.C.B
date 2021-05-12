<html>
<head>
<meta name="TextLength" content="SENT_NUM:33, WORD_NUM:786">
</head>
<body bgcolor="white">
<a href="#0" id="0">While the composition of Web services is yet another example of the hierarchical organisation of the world, HTN planning provides the means to represent such hierarchies and to compose Web services into value-added functionalities.</a>
<a href="#1" id="1">Beside appearing practically convenient, hierarchical planning is a long-lived technique characterised with controversy and confusion related to both theory and its use in the practice.</a>
<a href="#2" id="2">We have shown that such a situation can be remedied.</a>
<a href="#3" id="3">First of all, HTN planners are categorised based on the space they search in.</a>
<a href="#4" id="4">We find that plan-based HTN planners need to search more complex spaces than state-based HTN planners.</a>
<a href="#5" id="5">Then, several concepts that affect the planners' search space are identified.</a>
<a href="#6" id="6">Most plan-based HTN planners lack the clarity and purpose of their concepts, especially the task decomposition and task interactions.</a>
<a href="#7" id="7">We show that those concepts can be simplified but clarified, and logically interconnected.</a>
<a href="#8" id="8">On the other hand, the concepts in state-based HTN planners are simple and coherent, but with some limitation – these planners lack the non-determinism in the task decomposition and commit early to variable bindings.</a>
<a href="#9" id="9">However, the planners avoid most of task interactions and the confusion they may cause.</a>
<a href="#10" id="10">Above all, we provide two formal models of HTN planning that comprise general ideas of the two categories of hierarchical planners.</a>
<a href="#11" id="11">Further analysis enabled us to interpret several practical issues of HTN planners.</a>
<a href="#12" id="12">On an exemplifying domain, we found that plan-based HTN planners require smaller domain knowledge than state-based HTN planners, but that a prerequisite to encode the knowledge for the former ones is the comprehension of their underlying mechanisms.</a>
<a href="#13" id="13">We know that HTN planning is more expressive than STRIPS-like planning in theory, but none of the hierarchical planners can achieve such expressiveness in practice.</a>
<a href="#14" id="14">We show that both categories of planners have similar levels of expressiveness: they support a fragment of first-order logic, quality constraints are only partially addressed, and resource and temporal constraints are supported by few planners up to a certain level.</a>
<a href="#15" id="15">The underlying problem-solving mechanisms of plan-based HTN planners are more complex than the ones of state-based HTN planners, and that only few planers show flexibility for incorporating alternative techniques.</a>
<a href="#16" id="16">Furthermore and based on the systems of three hierarchical planners, we propose a general architecture for execution monitoring and replanning suitable for modern planners.</a>
<a href="#17" id="17">With respect to scalability and efficiency of HTN planners, we stress that little is reported on their performance and pairwise comparison.</a>
<a href="#18" id="18">As for the applicability, we find that HTN planning has been used in at least 50 domains, and SHOP2 is the most applied HTN planner, while O-Plan2 is the most applied plan-based HTN planner.</a>
<a href="#19" id="19">From the set of real-world applications, we select Web service composition and demonstrate its strong relationship with HTN planning.</a>
<a href="#20" id="20">We show that HTN-based approaches to service composition must pre-process the external service representation in order to create a possibly correct internal presentation suitable for HTN planners.</a>
<a href="#21" id="21">A large majority of approaches employ state-based HTN planners to compose Web services.</a>
<a href="#22" id="22">Although suitable, all approaches appear to be limited in addressing the properties and issues of Web service environments.</a>
<a href="#23" id="23">Our theoretical framework, upon which we defined the two formal models, can support new models and algorithms for HTN planning, such as those recently proposed in [50].</a>
<a href="#24" id="24">New concepts, such as landmarks in HTN planning, can be later easily plugged into the framework of concepts as well.</a>
<a href="#25" id="25">Our analysis shows that a common syntax and semantics for specifying HTN domains and problems is missing.</a>
<a href="#26" id="26">A single description language for both categories of HTN planners seems illusory ambitious, but each category may make use of a description language à la PDDL.</a>
<a href="#27" id="27">In this way, research improvements and performance evaluation of HTN planners can be stimulated, a direct comparison of the planners on possibly standardised set of problems can be enabled, and finally, help in understanding the expressive power of HTN planners can be provided.</a>
<a href="#28" id="28">Furthermore, we recognise that HTN planners can be improved in the area of goals, such as extended goals, hybrid goals [156], and active goal reasoning [157].</a>
<a href="#29" id="29">The composition of Web services witness the need for 1) planners able to deal better with uncertainty, and 2) using planning before and during plan execution.</a>
<a href="#30" id="30">The second point is in-line with the principles of continual planning [158].</a>
<a href="#31" id="31">Future HTN planners should monitor, refine, modify and repair their plans during the whole time of acting [159].</a>
<a href="#32" id="32">Many interesting research questions related to this subject remain open, such as a formalisation of execution semantics under the framework of HTN planning that define valid repairs of a solution plan at execution time, and development of an algorithm for plan repair (e.g., similar to the orchestration algorithm in [160]) that is sound and complete with respect to the execution semantics.</a>
</body>
</html>