<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:500">
</head>
<body bgcolor="white">
<a href="#0" id="0">Recursive, syntax-directed methods for CTL update confront two dual difficulties: The removal of a transition may dissatisfy an already-treated existential subformula.</a>
<a href="#1" id="1">Similarly, the addition of a transition may dissatisfy an already-treated universal subformula.</a>
<a href="#2" id="2">A direct way of dealing with this situation would be to repetitively model-check (i.e., test) a modified (i.e., generated) model w.r.t.</a>
<a href="#3" id="3">already-treated subformulas, yielding a method similar to generate-and-test techniques.</a>
<a href="#4" id="4">Another way would be to record information (e.g., a protection) of already-treated subformulas allowing only certain changes on the model to be modified so as to preserve the truth value of the already-treated subformulas.</a>
<a href="#5" id="5">We showed that with appropriate protections it is possible to avoid the model-checking stage of the direct approach, thus producing a more efficient method.</a>
<a href="#6" id="6">We exhibited the behavior of our method, {a mathematical formula}Updprot, on several examples.</a>
<a href="#7" id="7">In all cases {a mathematical formula}Updprot behaved favorably compared with a generate-and-test method.</a>
<a href="#8" id="8">First, we synthesized the synchronization skeleton of Emerson and Clarke's mutual-exclusion example [15] from a dummy model (having the identity relation as its accessibility relation).</a>
<a href="#9" id="9">Next, we formalized an informal specification of Clarke et al.'s microwave-oven example [11].</a>
<a href="#10" id="10">By gradually removing parts of a correct model and gradually augmenting the complexity of the input formula, we obtained different instances of this problem.</a>
<a href="#11" id="11">To measure the performance of {a mathematical formula}Updprot on larger examples, we employed two sets of problems.</a>
<a href="#12" id="12">First, we used models representing counters of different sizes that either count or are externally reset.</a>
<a href="#13" id="13">{a mathematical formula}Updprot was able to completely synthesize (from a dummy model) instances with up to 256 states in less than one hour, and repair a faulty model with 512 states, making 768 changes in the process, in around one hour of CPU time.</a>
<a href="#14" id="14">Fewer changes would mean the possibility of handling larger instances.</a>
<a href="#15" id="15">Subsequently, we used randomly generated models and formulas.</a>
<a href="#16" id="16">We showed the behavior of {a mathematical formula}Updprot, first fixing the model and varying the formula, and then fixing the formula and varying the model.</a>
<a href="#17" id="17">We obtained results in a reasonable time with up to 1024 states.</a>
<a href="#18" id="18">These two sets of examples (counters and random models and formulas) show the possible usefulness of our method in abstractions of models with many more states.</a>
<a href="#19" id="19">Finally, we proved the soundness and completeness of {a mathematical formula}XUpdprot(Appendix A), and we provided a complexity analysis of {a mathematical formula}Updprot(Appendix B).</a>
<a href="#20" id="20">There are several possible avenues for future research.</a>
<a href="#21" id="21">First, we believe that our protections could potentially benefit from ideas used in other update methods, including LTL update.</a>
<a href="#22" id="22">For example, Jobstmann et al. [18] employ games to perform LTL model update.</a>
<a href="#23" id="23">The system to be corrected is converted to an infinite game played between the system (the protagonist) and the environment (the antagonist).</a>
<a href="#24" id="24">Second, the close connections between model update and reasoning about actions and change (e.g., [14]) suggest investigating the possibility of adapting our approach to methods developed for such reasoning.</a>
<a href="#25" id="25">Finally, a better scaling might be achieved by codifying protected models and protections with symbolic techniques, such as BDDs.</a>
</body>
</html>