<html>
<head>
<meta name="TextLength" content="SENT_NUM:19, WORD_NUM:417">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented a framework for obtaining classes of hex-programs, which are ASP programs with external sources, that allow for finite groundings sufficient for evaluation over an infinite domain (which arises by “value invention” in external atoms).</a>
<a href="#1" id="1">It is based on term bounding functions (TBFs) and enables modular exchange and combination of such functions under the novel notion of liberal domain expansion (lde) safety.</a>
<a href="#2" id="2">Hitherto separate syntactic and semantic safety criteria can be combined, which pushes the class of hex-program with evaluation via finite grounding considerably.</a>
<a href="#3" id="3">We have provided sample TBFs that capture syntactic criteria similar to but more fine-grained than ones by [11], and semantic criteria related to those by [46] and [44], but target model generation (not query answering).</a>
<a href="#4" id="4">Deploying them, classes that strictly enlarger classes available through well-known safety notions for ASP programs are obtained, and other notions can be modularly integrated.</a>
<a href="#5" id="5">An implementation of lde-safety in the dlvhex-framework is available for use.</a>
<a href="#6" id="6">Together with lde-safety, we have also presented a new grounding algorithm for hex-programs.</a>
<a href="#7" id="7">In contrast to previous grounding techniques for ASP and hex-programs, it can handle all lde-safe programs directly and does not rely on program decomposition.</a>
<a href="#8" id="8">This is an advantage, as program splitting negatively affects learning techniques described by [17].</a>
<a href="#9" id="9">The worst case of the new algorithm can be effectively avoided as shown by [18].</a>
<a href="#10" id="10">An experimental evaluation of our implementation on synthetic and real applications shows a clear benefit.</a>
<a href="#11" id="11">Open issues and future work While lde-safe hex-programs are ready for use via the dlvhex-system, several issues remain naturally for future work.</a>
<a href="#12" id="12">One such issue is to identify further TBFs and suitable well-orderings of domains in practice.</a>
<a href="#13" id="13">Of particular interest are external atoms that provide built-in functions and simulate, in a straightforward manner, particular interpreted function symbols.</a>
<a href="#14" id="14">On the implementation side, further refinement and optimizations are an issue, as well as a library of TBFs and a plugin architecture that supports creating customized TBFs easily, to make our framework more broadly usable.</a>
<a href="#15" id="15">Connected with this are refinements of our algorithm and heuristics.</a>
<a href="#16" id="16">Here, meta-information about external sources to identify programs that allow for a better grounding and to reduce worst case costs of inputs are of interest.</a>
<a href="#17" id="17">A particular challenge is also a sensitive integration of grounding and solving under decomposition, which are currently not much aligned.</a>
<a href="#18" id="18">Finally, exploring on the application side the benefits of our results e.g. for domain-specific value invention (i.e., existential quantifiers under restrictions, which occurs prominently in configuration problems) appears to be an interesting direction.</a>
</body>
</html>