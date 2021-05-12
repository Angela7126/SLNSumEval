<html>
<head>
<meta name="TextLength" content="SENT_NUM:37, WORD_NUM:928">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have proposed an alternative representation for the rational dependencies among sentences in assumption-based argumentation (ABA): argument graphs.</a>
<a href="#1" id="1">An argument graph is analogous both to a single traditional, tree-based argument in ABA, and also to a set of such arguments.</a>
<a href="#2" id="2">In so doing, it constrains the rational structures represented to be free from certain properties possible in the tree-based representation—the properties of circularity, flabbiness, and bloatedness.</a>
<a href="#3" id="3">We argued these correspond to nothing possible or desirable in the case of the relations of support identified by a rational agent.</a>
<a href="#4" id="4">We showed that the existence of our argument graphs corresponds both individually, and at the level of extensions in the admissible and grounded semantics, to the existence of arguments and extensions in the tree-based approach.</a>
<a href="#5" id="5">We defined new notions of attack and, on that basis, new notions of semantics for argument graphs.</a>
<a href="#6" id="6">We also introduced two kinds of graph-based dispute derivations, which we proved to be sound and complete with respect to the admissible and grounded semantics of such argument graphs respectively.</a>
<a href="#7" id="7">Thus, although we believe that argument graphs are a superior representation of the structures which an agent brings to bear in argumentation, the argument-graph approach may also be used, computationally, as a leaner way of proving admissibility or groundedness of a sentence with respect to the traditional extension-based semantics.</a>
<a href="#8" id="8">Another advantage of our work here is a completeness result for derivations.</a>
<a href="#9" id="9">We also conducted experiments to investigate the computational efficiency of our new approach, and concluded that although there is a consistent minor advantage of speed in the case where tree-based and graph-based approaches both terminate, there appear to be many more instances of tree-based derivations where the existing best implementation fails owing to memory resources having been exceeded.</a>
<a href="#10" id="10">Thus there may be computational benefits in switching to argument graphs.</a>
<a href="#11" id="11">The graph-DDs we define borrow from the work of Thang et al. [26] the use of a graph whose acyclicity is an essential prerequisite of success.</a>
<a href="#12" id="12">However, whereas Thang et al. [26] provide a computational machinery for abstract argumentation [11], we have focused on structured argumentation in the form of ABA.</a>
<a href="#13" id="13">Moreover, Thang et al. [26] consider several argumentation semantics; we have focused on the admissible and grounded semantics.</a>
<a href="#14" id="14">We see many directions for future work.</a>
<a href="#15" id="15">In the present paper we have taken ABA as the basic formalism, and applied the graph-based approach to it.</a>
<a href="#16" id="16">However, as noted, tree-based arguments are widely used in many forms of structured argumentation.</a>
<a href="#17" id="17">We believe that the motivation for the present work—that of outlawing circularity, flabbiness and bloatedness—applies just as much to these other forms of structured argumentation, and would support converting to argument graphs as the underlying representation.</a>
<a href="#18" id="18">We intend to investigate this further, with respect to the structured argumentation frameworks of [23], [20], [4], [1].</a>
<a href="#19" id="19">We believe that an absence of rule-minimality in tree-based approaches to argumentation should not confusedly be thought to correspond to the representation of aggregated reasons for belief.</a>
<a href="#20" id="20">In the present paper we have not attempted to incorporate aggregation into the graph-based approach.</a>
<a href="#21" id="21">However, this is evidently of crucial importance.</a>
<a href="#22" id="22">We therefore intend to broaden our work to allow for aggregation.</a>
<a href="#23" id="23">In the present work we have introduced new graph-based semantics, defining notions of admissible, complete and grounded argument graphs.</a>
<a href="#24" id="24">Our main focus was on establishing fundamental concepts, relating them to traditional approaches in ABA, and in showing the computational efficacy of our approach.</a>
<a href="#25" id="25">However, it would be of great interest to conduct a more comprehensive investigation into forms of semantics possible with argument graphs.</a>
<a href="#26" id="26">That would involve looking at equivalents for other leading semantics of argumentation—preferred, stable, semi-stable, ideal extensions [11], [7], [14]—as well as investigating whether the use of argument graphs allows other forms of semantics which have no direct equivalent in the use of sets of tree-based arguments.</a>
<a href="#27" id="27">The computational complexity of several reasoning tasks in ABA, e.g., that of determining membership in admissible and grounded extensions, or the existence of extensions, is known [10], [15].</a>
<a href="#28" id="28">An interesting question for future work is whether the computational complexity of the same reasoning tasks changes when argument graphs rather than sets of argument trees are adopted.</a>
<a href="#29" id="29">We have focused on flat ABA frameworks.</a>
<a href="#30" id="30">Although they are of restricted form, these admit several interesting instances, notably logic programming and default logic [6].</a>
<a href="#31" id="31">Another interesting topic for future research is the extension of our novel semantics and procedure to the case of non-flat ABA frameworks, as defined in [6].</a>
<a href="#32" id="32">Finally, we intend to investigate further the properties of our implementation of the graph-DDs we have defined, and to see whether the performance can be improved.</a>
<a href="#33" id="33">As noted in §6, there are patterns in the comparison of abagraph with proxdd that deserve additional study; we also wish to implement any derivations for alternative semantics that we will define.</a>
<a href="#34" id="34">There are also several respects in which we wish to make the experimental analysis of the performance of abagraph more thorough.</a>
<a href="#35" id="35">First, it would be desirable to vary parameters for random framework generation which relate to the contrary of assumptions, such as how many different contraries there are, and the distribution of contraries amongst {a mathematical formula}R. We also want to conduct experiments on real-world data, in order to see whether the indications of respects in which abagraph gives a better performance are borne out on realistic problem areas.</a>
<a href="#36" id="36">It would also be desirable to obtain measures, for some of the randomly-generated ABA frameworks we have used, on the ‘ideal’ number of solutions for given queries, in order to test how far abagraph approximates to that idea.</a>
</body>
</html>