<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:650">
</head>
<body bgcolor="white">
<a href="#0" id="0">We started this paper by listing a number of CASP languages and systems acsolver, clingcon, ezcsp, idp, inca, and mingo that recently have come into use as an attempt to broaden the applicability of automated reasoning methods.</a>
<a href="#1" id="1">Distinguishing feature of such CASP solvers as acsolver, clingcon, ezcsp is combining the inferences stemming from traditionally different research fields.</a>
<a href="#2" id="2">This general interest towards hybrid solving illustrates the importance of developing synergistic approaches in the automated reasoning community.</a>
<a href="#3" id="3">A clear picture of the distinguishing features of CASP-like languages and underlying systems is of importance in order to facilitate further developments of the field.</a>
<a href="#4" id="4">This is the prime focus of this work that (a) formally states the relation between the CASP languages of acsolver, clingcon, and ezcsp and (b) provides a systematic account on the algorithmic differences between the underlying solvers.</a>
<a href="#5" id="5">For example, one take home lesson is that the languages of clingcon and ezcsp are the syntactic variants of {a mathematical formula}AC−.</a>
<a href="#6" id="6">Another lesson is that despite all the technological differences in the newly developed solvers such as acsolver, clingcon, and ezcsp they have a lot in common.</a>
<a href="#7" id="7">This alludes to a possibility of creating a general-purpose platform that would assist the creation of new architectures of CASP-like technology.</a>
<a href="#8" id="8">To summarize the technical contributions of this paper: we demonstrated a formal relation between the AC and clingcon languages and the algorithms behind acsolver and clingcon.</a>
<a href="#9" id="9">We designed transition systems {a mathematical formula}ACΠ and {a mathematical formula}conlF,Π for describing algorithms for computing (subsets of) answer sets of weakly-simple AC programs.</a>
<a href="#10" id="10">We used these graphs to specify the acsolver, clingcon and ezcsp algorithms.</a>
<a href="#11" id="11">Compared with traditional pseudocode descriptions of algorithms, transition systems use a more uniform (i.e., graph-based) language and offer more modular proofs.</a>
<a href="#12" id="12">The graphs {a mathematical formula}ACΠ and {a mathematical formula}conF,Π offer a convenient tool to describe, compare, analyze, and prove correctness for a class of algorithms.</a>
<a href="#13" id="13">In fact we formally show the relation between the subgraphs of {a mathematical formula}ACΠ and {a mathematical formula}conF,Π, namely that the graphs {a mathematical formula}ACΠ− and {a mathematical formula}conComp(Π),Π− are equal.</a>
<a href="#14" id="14">Furthermore, the transition systems for acsolver and clingcon result in new algorithms for solving a larger class of AC programs – weakly-simple programs introduced in this paper.</a>
<a href="#15" id="15">Neither the acsolver nor clingcon systems, respectively, can deal with such programs.</a>
<a href="#16" id="16">In the future we will consider ways to use current ASP/CLP technologies to design a solver for weakly-simple programs.</a>
<a href="#17" id="17">Work by Balduccini et al. [33] is a step in that direction.</a>
<a href="#18" id="18">In the future we would like to uncover the precise relationship with idp, and the translational solvers introduced in [8], [9], [10].</a>
<a href="#19" id="19">The idp language builds on top of the formalism called PC(ID) [34] that is strongly related to logic programs under answer set semantics [32].</a>
<a href="#20" id="20">As of this point there is no formal account describing the insides of the idp system supporting a CASP language.</a>
<a href="#21" id="21">The translational solvers developed in [8], [9] rely on transformations from a CASP language to an ASP formalism.</a>
<a href="#22" id="22">A graph underlying an ASP solver (for instance, {a mathematical formula}sml(asp)F,Π for the case of clasp[32]) applied to a transformation devised in [8], [9] can be used to characterize such a solver.</a>
<a href="#23" id="23">Even though we introduced similar graphs, ac and conl, for capturing hybrid solvers these graphs are not appropriate to formally compare translational and hybrid solvers.</a>
<a href="#24" id="24">The transition rule Query Propagate of AC and conl is too crude to capture the details of solving that occurs on the side of specialized solvers (such as gecode or sicstus Prolog).</a>
<a href="#25" id="25">To point at exact differences between a translational solver and its hybrid counterpart the computation done in a specialized solver has to be unfolded.</a>
<a href="#26" id="26">The mingo solver [10] implements CASP by translating its programs into integer linear programs.</a>
<a href="#27" id="27">It is an interesting direction of research to study how the technology of integer linear programming compares to the technology of ASP and CASP.</a>
</body>
</html>