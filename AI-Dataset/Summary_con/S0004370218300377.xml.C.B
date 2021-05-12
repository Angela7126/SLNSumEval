<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:618">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we present a technique for automatically finding mutual exclusion invariants in lifted temporal planning domains expressed in PDDL2.1.</a>
<a href="#1" id="1">Our technique builds on Helmert's invariant synthesis [33], but generalises it and extends it to temporal domains.</a>
<a href="#2" id="2">Synthesising invariants for temporal tasks is much more complex than for tasks with instantaneous actions because actions can occur simultaneously or concurrently and interfere with each other.</a>
<a href="#3" id="3">For this reason, a simple generalisation of Helmert's approach does not work in temporal settings.</a>
<a href="#4" id="4">In extending the theory to capture the temporal case, we have had to formulate invariance conditions that take into account the full temporal structure of the actions as well as the possible interactions between them.</a>
<a href="#5" id="5">As a result, we have constructed a technique that is significantly more comprehensive than related techniques.</a>
<a href="#6" id="6">Our technique is presented here formally and proofs are offered that support its soundness.</a>
<a href="#7" id="7">In contrast to the majority of related approaches, our technique works at the lifted level of the representation, so it is very efficient.</a>
<a href="#8" id="8">The experimental results show that its run time is negligible, while it allows us to find a wider set of invariants, which in turn results in synthesising a smaller number of state variables to represent a domain.</a>
<a href="#9" id="9">The experiments also indicate that the temporal planners that use state variables to represent the world may benefit from dealing with a smaller number of state variables.</a>
<a href="#10" id="10">Our approach to finding invariants can be incorporated in any translation from PDDL2.1 to a language based on multi-valued state variables.</a>
<a href="#11" id="11">For example, we have used (a simplified version of) the temporal invariant synthesis described in this paper in our translator from PDDL2.1 to NDDL [5], which is the domain specification language of the EUROPA2 planner [38].</a>
<a href="#12" id="12">EUROPA2 has been the core planning technology for several NASA space mission operations.</a>
<a href="#13" id="13">It uses a language based on multi-valued state variables that departs from PDDL2.1 in several ways.</a>
<a href="#14" id="14">The use of our translator from PDDL2.1 to NDDL has facilitated the testing of EUROPA2 against domains of the IPCs originally expressed in PDDL2.1 [3], [4].</a>
<a href="#15" id="15">This originally motivated our work on temporal invariant synthesis.</a>
<a href="#16" id="16">In future work, we plan to extend our experimental evaluation by incorporating our invariant synthesis in other planners that use a multi-valued variable representation and that are not currently publicly available.</a>
<a href="#17" id="17">This will allow us to assess more exhaustively the impact that handling fewer state variables has on the performance of temporal planners.</a>
<a href="#18" id="18">The experimental results shown in this paper provide evidence that more research on this is needed.</a>
<a href="#19" id="19">In addition, we plan to exploit the metric information encoded in planning domains to find a broader range of invariants.</a>
<a href="#20" id="20">Invariants for domains with metric fluents are interesting and challenging.</a>
<a href="#21" id="21">We envisage that there are two kinds of situations to be considered: those in which it can be shown that a linear combination of fluents is invariant (relevant to domains with linear effects on variables) and those in which metric fluents interact with propositional fluents in a more complex way.</a>
<a href="#22" id="22">For example, one might think of a domain encoding the act of juggling in which the number of balls in the air plus the number in the hands is a constant, but the balls in the hand might be encoded propositionally (for example, by a literal holding_left and so on), while those in the air might be encoded as a count.</a>
<a href="#23" id="23">Finding the invariant in this case is a challenging problem since it crosses the propositional and metric fluent spaces.</a>
<a href="#24" id="24">Finally, as shown in Example 19, our technique can be a valuable tool for debugging temporal planning domains.</a>
<a href="#25" id="25">We intend to work in this direction by incorporating our technique in validation tools such as VAL [36].</a>
</body>
</html>