<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:627">
</head>
<body bgcolor="white">
<a href="#0" id="0">Our work pioneers conflict-directed learning, of sound generalizable knowledge, from conflicts – dead-end states – in forward state space search.</a>
<a href="#1" id="1">The basis are critical-path heuristic functions {a mathematical formula}hC, that allow to consider an arbitrary set C of atomic conjunctions, and that detect all dead-ends in the limit.</a>
<a href="#2" id="2">Our key technical contributions are search methods identifying conflict states, and refinement methods extending C so that {a mathematical formula}hC recognizes these states.</a>
<a href="#3" id="3">The resulting technique is, in our humble opinion, quite elegant, and suggests that the learning from “true” conflicts in state space search, not necessitating a solution length bound, is worth the community's attention.</a>
<a href="#4" id="4">Beauty contests aside, from a pragmatical point of view our techniques certainly do not, as they stand, deliver an empirical breakthrough.</a>
<a href="#5" id="5">They require a rather specific kind of problem structure to work well, namely structure that allows for (1) quick conflict identification, (2) effective learning, and (3) strong generalization.</a>
<a href="#6" id="6">This kind of problem structure is typical of resource-constrained planning, as far as reflected by the current benchmarks from that area.</a>
<a href="#7" id="7">On other domains, as far as reflected by the competition benchmarks, this structure is scarce, though it does sometimes appear.</a>
<a href="#8" id="8">An interesting question in this context is the relation between requirement (1) vs.</a>
<a href="#9" id="9">a plan length bound.</a>
<a href="#10" id="10">The two requirements are correlated in that conflict identification will be easier on problems whose search paths are typically short.</a>
<a href="#11" id="11">Furthermore, if a bound is available, then manifold alternate conflict analysis techniques can be used, simply via the correspondence to constraint satisfaction.</a>
<a href="#12" id="12">However, having “typically” short search paths is a much weaker assumption than having a globally valid length bound, in particular a bound that is known a-priori before search begins.</a>
<a href="#13" id="13">In the non-resource domains where our techniques work well – Floortile, ParcPrinter, Pathways, Childsnack, Diagnosis, DocTransfer – it is completely unclear how an upper bound should be derived.</a>
<a href="#14" id="14">Even in the resource-constrained benchmarks, this is not obvious: not all actions consume resources, so some reasoning over the possible non-consuming action subsequences would be required.</a>
<a href="#15" id="15">Regarding future work, ours is merely a first foray into forward search conflict-learning techniques, and lots more remains to be explored.</a>
<a href="#16" id="16">We hope and expect our work to be the beginning of the story, not its end.</a>
<a href="#17" id="17">For conjunctions learning, important open questions pertain, e.g., to ranking criteria allowing a more informed choice of which new conjunctions to construct during refinement, as well as allowing to forget conjunctions learned previously in case they did not prove useful for the search.</a>
<a href="#18" id="18">For clause learning, exciting questions pertain to extending its, as yet, very limited role.</a>
<a href="#19" id="19">Can we learn easily testable criteria that, in conjunction, are sufficient and necessary for {a mathematical formula}uC=∞, thus matching the pruning power of {a mathematical formula}uC itself?</a>
<a href="#20" id="20">Can such criteria form building blocks for later learning steps, like the clauses in SAT?</a>
<a href="#21" id="21">Can we do some form of reasoning over clauses, deducing new knowledge from the old one, given the action specifications?</a>
<a href="#22" id="22">Critical-path heuristics are merely one means for dead-end detection, and an exciting big line of research is the design of refinement methods for other dead-end detectors.</a>
<a href="#23" id="23">Can we refine merge-and-shrink unsolvability heuristics on the fly?</a>
<a href="#24" id="24">What about potential heuristics?</a>
<a href="#25" id="25">If so, how to make the most out of the combination of all three methods?</a>
<a href="#26" id="26">Last but not least, one thing we would particularly like to see is the export of this (kind of) technique to game-playing and model checking, where dead-end detection is at least as, probably more, important than in classical planning.</a>
<a href="#27" id="27">For {a mathematical formula}hC refinement, this works “out of the box” modulo the applicability of Equation (1), i.e., the definition of critical-path heuristics.</a>
<a href="#28" id="28">As is, this requires conjunctive subgoaling behavior.</a>
<a href="#29" id="29">But more general logics (e.g. minimization to handle disjunctions) should be manageable.</a>
</body>
</html>