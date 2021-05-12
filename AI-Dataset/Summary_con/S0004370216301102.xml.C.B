<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:721">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work we studied several aspects concerning the fundamental concepts of rejected arguments and implicit conflicts in abstract argumentation frameworks.</a>
<a href="#1" id="1">For that, we focused on naive, stable, preferred, semi-stable and stage semantics, all of which satisfy the principle of I-maximality [1].</a>
<a href="#2" id="2">We omitted prominent basic semantics like complete, admissible and conflict-free sets from our studies as they do not align in this respect.</a>
<a href="#3" id="3">However, for the sake of completeness we provide a complete account of results for the issues tackled in this paper for these semantics in Appendix C.</a>
<a href="#4" id="4">The idea of avoiding rejected arguments or implicit conflicts, lead us to introduce and study the novel classes of compact and analytic argumentation frameworks, each parameterized by a particular semantics.</a>
<a href="#5" id="5">For both classes we obtained a similar picture for the relationship between semantics.</a>
<a href="#6" id="6">Concerning computational issues, we have analyzed the complexity of deciding whether a given af is compact (resp.</a>
<a href="#7" id="7">analytic) for a semantics σ. Our results range from tractability for naive semantics, over {a mathematical formula}NP-completeness for stable and preferred semantics, up to {a mathematical formula}Σ2P-completeness for semi-stable and stage semantics.</a>
<a href="#8" id="8">We also have argued that the problem of credulous acceptance becomes trivial and skeptical acceptance is often polynomial time computable when we restrict ourselves to the subclasses under consideration, while the verification problems remain as hard as in the general case.</a>
<a href="#9" id="9">The overall picture is now as follows: On the one hand we have illustrated that the classes of compact and analytic afs provide computational benefits both in practice and in terms of theoretical worst-case analysis.</a>
<a href="#10" id="10">On the other hand testing for membership in one of the classes is, for most of the semantics, of rather high complexity and thus these classes cannot be directly used to improve systems.</a>
<a href="#11" id="11">However, for future work, we plan to take the rather negative complexity results for deciding membership in the subclass of compact (resp.</a>
<a href="#12" id="12">analytic) afs into account and seek for efficiently checkable (but not necessarily complete) criteria in order to decide whether a given af (a) is compact (resp.</a>
<a href="#13" id="13">analytic); and (b) whether it can be easily transformed into a compact (resp.</a>
<a href="#14" id="14">analytic) one.</a>
<a href="#15" id="15">The ultimate goal remains to design pre-processing procedures that identify rejected arguments that can be removed and implicit conflicts that can be made explicit; in other words, simplifications of the given af into a semantically equivalent af with better computational properties.</a>
<a href="#16" id="16">One of our main results was the refutation of the Explicit Conflict Conjecture, originally proposed in [10] for stable semantics.</a>
<a href="#17" id="17">In fact, for each semantics σ among stable, preferred, semi-stable, and stage, we provided afs where it is not possible to find an equivalent (under σ) af where all conflicts become explicit.</a>
<a href="#18" id="18">As a consequence, this result shows that in order to express a certain set {a mathematical formula}S of extensions via an af, one cannot just draw attacks between any pair of arguments that do not occur jointly in any extension {a mathematical formula}E∈S.</a>
<a href="#19" id="19">We believe that this not only gives a new insight into the fundamental properties of argumentation semantics, but also is important to be taken into account in research about the dynamics and evolvement of afs.</a>
<a href="#20" id="20">In particular these results indicate that techniques similar to Conflict-Driven Clause Learning [35] in SAT-solvers cannot be directly applied in the argumentation setting, as it can happen that a solver identifies a conflict between two arguments but it is impossible to add this conflict to the af without changing the outcome.</a>
<a href="#21" id="21">This is in particular interesting as most of the leading abstract argumentation systems are built on top of SAT-solvers [37], [38].</a>
<a href="#22" id="22">Finally, we addressed the question of signatures and realizability.</a>
<a href="#23" id="23">We studied the relationship between signatures of compact and resp.</a>
<a href="#24" id="24">analytic afs.</a>
<a href="#25" id="25">Our results complement the analysis from [23] and give a more fine-grained landscape about the expressive power of different semantics when the shape of afs is restricted.</a>
<a href="#26" id="26">Building on initial research from [8], we also analyzed possible numbers of extensions afs can yield under a semantics at hand.</a>
<a href="#27" id="27">Extending these considerations to admissible and complete semantics will be part of future work (cf.</a>
<a href="#28" id="28">[9] for a conjecture regarding the maximal number of complete extensions).</a>
<a href="#29" id="29">Results of the latter kind can also be beneficial for argumentation systems, since they may allow af solvers to navigate more efficiently through the search space of possible extensions.</a>
</body>
</html>