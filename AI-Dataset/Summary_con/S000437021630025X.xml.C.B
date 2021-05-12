<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:507">
</head>
<body bgcolor="white">
<a href="#0" id="0">In order to function in service domains, a planning system should be equipped with a number of special features that enable it to dispose of the uncertainty deriving from the open world assumption as well as from unexpected service behaviors, deal with the abundance of data-intensive operations, and overcome inconsistencies due to changes caused by exogenous factors.</a>
<a href="#1" id="1">Most importantly, the applicability of the planning system should not be tailored to the specifics of a particular domain and task, but rather be in the position to fulfill a variety of diverse objectives with minimal manual reconfiguration.</a>
<a href="#2" id="2">To meet these requirements, we proposed and described the RuGPlanner, a planning framework which uses constraint satisfaction techniques and accommodates for complex goals, a knowledge-level representation to model lack of information, proactive sensing in the presence of variables that range over large domains, as well as an algorithm for monitoring execution and revising plans in a seamlessly changing environment.</a>
<a href="#3" id="3">The approach relies on a domain-independent representation, which consists of a set of loosely-coupled atomic service operations described as planning operators.</a>
<a href="#4" id="4">Data-intensive domains which involve many operations that work with numeric-valued variables, including the case of numeric-valued sensing outputs, are effectively dealt with.</a>
<a href="#5" id="5">Regarding goal expressivity, the RuGPlanner supports a number of constructs that impose constraints over the state traversal, but it does not accommodate for preferences.</a>
<a href="#6" id="6">No restrictive assumptions about the interdependencies between sensing and word-altering actions in the composition are made, and sensing actions are proactively planned for.</a>
<a href="#7" id="7">The approach performs continuous plan revisions to dispose of failure responses, long responses and timeouts, and with exogenous events.</a>
<a href="#8" id="8">The orchestration algorithm can address effectively many problematic situations, under certain assumptions regarding the kind of goal and the point at which the contingency occurs during execution.</a>
<a href="#9" id="9">Experimental evaluation confirms the feasibility of the approach in several situations, with complex goals, and diverse combinations of unknowns, failures and runtime inconsistencies.</a>
<a href="#10" id="10">Although our work is inspired by applications in the field of Web Services, the essence of the planning methodologies we describe is more general, and touches upon issues that concern a series of problems where domain-independence, uncertainty and dynamicity are at stake.</a>
<a href="#11" id="11">To improve the performance of the RuGPlanner one should consider planning-oriented rather than just CSP-based heuristics, which manage to extract additional constraints that reflect particular properties of the underlying planning problem.</a>
<a href="#12" id="12">Some of the reformulation techniques proposed in [8] could also be used to speed up search.</a>
<a href="#13" id="13">The RuGPlanner generates plans that are usually characterized by a high degree of parallelism, however, special heuristics need to be investigated if plan optimality is at stake.</a>
<a href="#14" id="14">Extending the planning system to deal with noisy data, i.e., sensing actions which return a set of possible values, is also an interesting direction for future work.</a>
<a href="#15" id="15">To this end techniques similar to the interval-valued function described in [99] and some sort of case-based reasoning can be adopted.</a>
<a href="#16" id="16">The capabilities of the orchestration framework can also be improved and extended.</a>
<a href="#17" id="17">For example, exploiting techniques used in the context of dynamic CSP for intelligent solution reuse probably benefit performance.</a>
</body>
</html>