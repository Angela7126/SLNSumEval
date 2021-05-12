<html>
<head>
<meta name="TextLength" content="SENT_NUM:19, WORD_NUM:455">
</head>
<body bgcolor="white">
<a href="#0" id="0">As for classical planning, heuristic state-space search is a viable technique for multi-agent planning.</a>
<a href="#1" id="1">However, in contrast to the classical heuristic search, the multi-agent setup raises its own challenges.</a>
<a href="#2" id="2">The dilemma of highly informed but slow versus less informed but fast heuristic estimators is manifested in the dichotomy of projected heuristic restricted to the agent's local view of the problem versus distributed heuristic estimating the global heuristic value at the cost of significant communicational or computational overhead.</a>
<a href="#3" id="3">The MADLA Planner combines both fast local projection of the FF heuristic with a global distributed FF heuristic in an attempt to combine their benefits and mitigate their negative effects.</a>
<a href="#4" id="4">There are two contributions of this paper.</a>
<a href="#5" id="5">The main contribution is a novel distributed multi-heuristic multi-agent search scheme and its practical implementation.</a>
<a href="#6" id="6">A minor contribution is an improved approach to computing privacy-preserving distributed FF heuristic, while reducing the negative effect of overcounting.</a>
<a href="#7" id="7">The novel technique used in the MADLA Planner to combine the heuristic estimators is based on the classical multi-heuristic search, but it does not evaluate all states by both heuristics.</a>
<a href="#8" id="8">Instead, the local heuristic is used only while the distributed heuristic is busy (that is, waiting for replies from other agents).</a>
<a href="#9" id="9">The projected heuristic is used to fully utilize the computational resources of the agent, even for less-informed, but faster search of the state space of the individual agent.</a>
<a href="#10" id="10">When the estimation of the more-informed heuristic is finished, the evaluated state is used in both searches.</a>
<a href="#11" id="11">This principle was theoretically analyzed and practically evaluated in the form of a MA-STRIPS based planner, which on many domains outperforms all current multi-agent planners in the coverage metric over a common benchmark set.</a>
<a href="#12" id="12">Some research directions are left for future work.</a>
<a href="#13" id="13">First, whether the principle of MADLA Search can be used for optimal multi-agent planning with similarly promising results.</a>
<a href="#14" id="14">Second, as the results show, the planner does not perform well on domains with dead-ends, which relaxation heuristics are oblivious to.</a>
<a href="#15" id="15">We can ask what efficiency boost could be achieved by the combination not only of one heuristic as projected and distributed estimators, but also with other heuristics possibly orthogonal to the first heuristic pair; landmarks are an obvious choice.</a>
<a href="#16" id="16">Moreover, the open list selection scheme is by no means perfect and could be possibly improved, e.g., by occasionally evaluating the best state from {a mathematical formula}OLi by {a mathematical formula}hLi even if {a mathematical formula}ODi is not empty.</a>
<a href="#17" id="17">Also, the use of preferred operators might significantly improve the overall performance.</a>
<a href="#18" id="18">Generally, utilizing the principle of combining fast and less accurate and slow but more informed heuristics in an asynchronous manner may be also an interesting research direction in classical planning (especially on multicore machines) and in search in general.</a>
</body>
</html>