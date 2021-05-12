<html>
<head>
<meta name="TextLength" content="SENT_NUM:44, WORD_NUM:1040">
</head>
<body bgcolor="white">
<a href="#0" id="0">Heuristic and symbolic search are two leading methods for cost-optimal planning.</a>
<a href="#1" id="1">There is no doubt that symbolic search has the effectiveness to explore large state sets, while the explicit-state heuristics are often more informed.</a>
<a href="#2" id="2">While the result of IPC 2011 suggested a clear advantage for heuristic explicit-state search, in this paper we introduced two orthogonal improvements to symbolic search planners that change this picture.</a>
<a href="#3" id="3">On the one hand, we have presented and analyzed image computation methods for symbolic search planning.</a>
<a href="#4" id="4">Our starting point was the state-of-the-art symbolic search planner Gamer that computes the image using a transition relation for each planning operator.</a>
<a href="#5" id="5">We proposed three different alternatives for image computation:</a>
<a href="#6" id="6">{a mathematical formula}TR1+: Instead of representing each planning operator by means of a single BDD, represent the preconditions and effects independently.</a>
<a href="#7" id="7">That way, no auxiliary set of variables is needed in order to represent the successor states.</a>
<a href="#8" id="8">{a mathematical formula}CT: Apply the preconditions of operators at the same time using the conjunction tree, an approach similar to the one used in explicit-state search planning.</a>
<a href="#9" id="9">{a mathematical formula}UT: Aggregate several operators in a single transition relation, controlling the memory used and avoiding to exceed a given memory limit.</a>
<a href="#10" id="10">Our analysis has shown that the three approaches improve the previous image computation of Gamer in terms of coverage and time score.</a>
<a href="#11" id="11">Moreover, the experimental results show a dominance across most domains, so that the new image computation methods can replace the previous image computation of Gamer.</a>
<a href="#12" id="12">We observed that it is better to avoid the usage of an auxiliary set of variables, representing conditions and effects separately.</a>
<a href="#13" id="13">Unfortunately, this cannot be done when more than one operator is represented in the same TR, so the best image computation techniques still need the auxiliary set of variables to represent the relation between the precondition and the effect of the operators.</a>
<a href="#14" id="14">In terms of time-efficiency, it is best to use a single monolithic TR to describe all the operators.</a>
<a href="#15" id="15">However, as already noticed by previous works, the TR that describes all the planning operators can easily exceed the available memory (that was the main reason to split it into one TR per operator).</a>
<a href="#16" id="16">Thus, one of the main conclusions of our analysis is that for efficient image computation, it is best to represent the planning operators with as few TRs as possible, using a monolithic TR for all operators with the same cost whenever possible.</a>
<a href="#17" id="17">When constructing a monolithic TR within a reasonable memory limit is impossible, a disjunctive partitioning of the TR is necessary.</a>
<a href="#18" id="18">Previous work in model checking had already suggested similar partitionings.</a>
<a href="#19" id="19">Here, we proposed an algorithm to derive the disjunctive partitioning automatically, according to several heuristic criteria.</a>
<a href="#20" id="20">Our analysis shows the importance of keeping the size of the TRs as balanced as possible, so we recommend the {a mathematical formula}UT100kDT method for future work.</a>
<a href="#21" id="21">On the other hand, we used state-invariant constraints in order to prune symbolic search.</a>
<a href="#22" id="22">We interpret state invariants as properties that must hold in any state that is part of a plan for the task, so that they can be used to prune forward and backward search.</a>
<a href="#23" id="23">Our main contribution is to study different methods to encode and use these constraints:</a>
<a href="#24" id="24">{a mathematical formula}MBDD: Encodes the constraints as BDDs and, during the search, uses a conjunction to compute the subset of valid states.</a>
<a href="#25" id="25">e-del: Encodes the constraints as additional conditions in the operators, i.e., in the TRs.</a>
<a href="#26" id="26">We proved which subset of constraints must be encoded in each TR to ensure that no invalid states are generated during the search.</a>
<a href="#27" id="27">Empirical results show that state-invariant pruning is tremendously effective in symbolic search, especially in regression.</a>
<a href="#28" id="28">According to our evaluation, e-deletion is recommended for taking advantage of constraints in symbolic search.</a>
<a href="#29" id="29">This has impact specially in regression search where there are more state-invariant constraints, and may also be relevant for encoding constraints from other sources, such as novel dead-end detection methods [68].</a>
<a href="#30" id="30">Our enhanced version of Gamer, cGamer, not only outperforms Gamer in most domains but also has superior performance compared to explicit-state search approaches.</a>
<a href="#31" id="31">The good results of symbolic blind search are especially surprising as after many years of research of finding refined heuristics for AI planning, this form of blind search still outperforms heuristic search planners on many domains, while being close on most others.</a>
<a href="#32" id="32">The impact of the directionality of the domains [69] explains why this configuration fares so well, as a simple alternating strategy allows choosing the direction in which the problem may be more easily solved, compensating the use of heuristics.</a>
<a href="#33" id="33">This highlights the importance of regression.</a>
<a href="#34" id="34">Progression is usually believed to be more robust than regression for search-based planning.</a>
<a href="#35" id="35">While the results on unidirectional search somewhat confirm the superiority of forward search, our improvements help to reduce the gap in symbolic search, beating the results of partial-state backward search.</a>
<a href="#36" id="36">An important conclusion to be drawn from our results is that symbolic backward search is a useful technique that can be complementary to standard heuristic search techniques.</a>
<a href="#37" id="37">In the last IPC in 2014 cGamer made the second place, outperforming other symbolic search based planners as well as explicit-state search based planners.</a>
<a href="#38" id="38">The winner of the competition, {a mathematical formula}SymBA⁎ was also built upon the ideas of cGamer, using the enhancements proposed in this paper with a combination of symbolic bidirectional search and abstraction heuristics.</a>
<a href="#39" id="39">This reflects the relevance of our enhancements, unifying operators based on the balanced disjunction tree up to a maximum memory limit of 100 000 nodes ({a mathematical formula}UT100kDT) for image computation and e-deletion for state-invariant pruning, to make symbolic search a state-of-the-art technique for cost-optimal planning.</a>
<a href="#40" id="40">A more detailed analysis of the impact of abstraction heuristics in bidirectional search shows that, while abstraction heuristics may be helpful in particular domains, the overall performance of {a mathematical formula}SymBA⁎ is similar to that of symbolic bidirectional uniform-cost search [66].</a>
<a href="#41" id="41">Bidirectional heuristic search has recently seen some possibilities [70] and limitations [71].</a>
<a href="#42" id="42">Insights have lead to variants like MM [72], [73] with a set-based parallel implementation on external memory [74].</a>
<a href="#43" id="43">Given the success of BDD-based bidirectional search documented in this work, the implementation of MM with BDDs and its application to AI planning domains is one tempting option for future research.</a>
</body>
</html>