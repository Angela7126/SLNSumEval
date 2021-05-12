<html>
<head>
<meta name="TextLength" content="SENT_NUM:36, WORD_NUM:794">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we are concerned with only knowing, and how that extends to the multiagent case.</a>
<a href="#1" id="1">Only knowing rationally reconstructs nonmonotonicity, AEL's flavor in particular, in a monotonic modal logic.</a>
<a href="#2" id="2">Besides providing a clean model theory for a first-order language, the notion of only knowing is a very intuitive concept, allowing for a succinct and natural formulation for the beliefs and non-beliefs of an agent.</a>
<a href="#3" id="3">An extension to the many agent case, then, seems pertinent.</a>
<a href="#4" id="4">In stark contrast to Levesque's simple logic, however, previous treatments of multiagent only knowing are surprisingly complex with undesirable features.</a>
<a href="#5" id="5">They are also propositional.</a>
<a href="#6" id="6">In this work, we looked at a first-order proposal.</a>
<a href="#7" id="7">In order to do so, we had to deviate from the usual Kripke-based semantics, and appeal to a depth-of-KB based account.</a>
<a href="#8" id="8">But as far as entailments are concerned, we showed that for finite KBs, such as in practical applications, sentences about what is believed and not believed at any depth can be reasoned with.</a>
<a href="#9" id="9">We then argued that this proposal maintains our intuitions about {a mathematical formula}OL.</a>
<a href="#10" id="10">For the propositional case, the logic can be characterized also in terms of a proof theory, which goes beyond the language restrictions of the axiomatization from [10].</a>
<a href="#11" id="11">In contrast to the work of [12], our proof theory does not bring concepts from the semantics to the axiomatization.</a>
<a href="#12" id="12">Using the proof theory we gave example derivations exhibiting multiagent nonmonotonic reasoning.</a>
<a href="#13" id="13">Interestingly, the axiomatization corresponds to the work of [12] but without having to resort to their complications.</a>
<a href="#14" id="14">Finally, as an extension to Levesque's insight that only knowing captures AEL, we considered a multiagent generalization of AEL and showed that a similar relationship holds with our framework.</a>
<a href="#15" id="15">In general, {a mathematical formula}OL can also be thought as a formal foundation for a knowledge representation service, where we query the KB on what the agent knows and does not know [3].</a>
<a href="#16" id="16">For this, a fundamental result called the representation theorem[38] shows how reasoning about knowledge can be reduced to first-order reasoning.</a>
<a href="#17" id="17">We believe a similar move is possible with {a mathematical formula}OLn, and we would like to investigate this in the future.</a>
<a href="#18" id="18">For preliminary results on a representation theorem for {a mathematical formula}OLn, see [39].</a>
<a href="#19" id="19">A second major direction for future work is extending the semantics to handle unbounded modalities, as required, for example, with the notion of common knowledge.</a>
<a href="#20" id="20">Perhaps an approach similar to the knowledge structures proposal [29] would prove fruitful.</a>
<a href="#21" id="21">As discussed above, they too have epistemic states of various depths, and so a model of their language has epistemic states of every depth, including infinitary ones, allowing them to define a semantics for common knowledge.</a>
<a href="#22" id="22">Following such an account, an analysis of the computational complexity for deciding the validity of formulas in the propositional case would also be insightful.</a>
<a href="#23" id="23">On a different front, as pointed out in [40], when imagining knowledge-based agents in dynamical worlds, non-beliefs play an important role in informing the agent about what it is ignorant about.</a>
<a href="#24" id="24">The agent then may be persuaded to deliberate on ways to complete its knowledge, say by sensing[41].</a>
<a href="#25" id="25">This intuition has encouraged extensions of {a mathematical formula}OL towards the design of practical cognitive agents [40], [42], [43], by introducing the appropriate variants of K and O in the language of the situation calculus [41], [44], [45].</a>
<a href="#26" id="26">Then, by stipulating all that is known initially, only knowing exhibits the desired behavior for how beliefs should change as a result of physical and sensing actions.</a>
<a href="#27" id="27">Recently, this only knowing variant of the situation calculus has also been extended to capture defaults over actions [46], and reasoning about noisy effectors [22], [47].</a>
<a href="#28" id="28">In similar spirit, work on an amalgamation of actions and {a mathematical formula}OLn is under way [48].</a>
<a href="#29" id="29">Here too, only knowing offers a simple system to reason about the beliefs and the defaults of agents, especially in the context of how knowledge and ignorance changes as agents perceive and act in complex dynamical domains.</a>
<a href="#30" id="30">From a practical standpoint, in dynamical systems, we would need to reason about knowledge and actions.</a>
<a href="#31" id="31">Fortunately, there are well-known methodologies for resolving actions, either by reducing queries about the future to queries about the initial state or by updating the knowledge base [7], [41], [46], [49].</a>
<a href="#32" id="32">This would then mean that we would only need to reason about knowledge.</a>
<a href="#33" id="33">Here is perhaps a second use of a representation theorem: it would provide the computational means for realizing such first-order reasoners.</a>
<a href="#34" id="34">To see this in action, we refer interested readers to [39].</a>
<a href="#35" id="35">Epistemic logics play an important role in the investigations on multiagent interactions in knowledge representation applications, and we think the above line of work contributes to the area, especially in providing a formal specification for knowledge-based reasoners operating in an incompletely known world.</a>
</body>
</html>