<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:647">
</head>
<body bgcolor="white">
<a href="#0" id="0">Symbolic Perimeter Abstractions (SPA ) are a novel kind of admissible heuristics for cost-optimal planning that extends previous definitions of perimeter abstraction heuristics in order to consider multiple perimeters in different abstract state spaces, instead of only one.</a>
<a href="#1" id="1">Applying perimeter abstractions in planning poses some challenges, such as how to perform efficient regression search or how to obtain the set of abstract states that correspond to all states in the perimeter to initialize the abstract search.</a>
<a href="#2" id="2">SPA addresses these challenges by using symbolic search in order to traverse the abstract state spaces.</a>
<a href="#3" id="3">In summary, SPA uses abstractions to relax a symbolic backward search, keeping only partial information about some variables of the task.</a>
<a href="#4" id="4">An abstraction hierarchy determines a set of abstract state spaces to search, ranging from the original non-abstracted state space to one small enough to be explored by explicit-state search.</a>
<a href="#5" id="5">Every abstraction reduces the size of the abstract state space, so that there is a trade-off between the abstract search complexity and the heuristic informativeness.</a>
<a href="#6" id="6">Searching all these abstractions is clearly redundant, since heuristics of less relaxed abstractions are strictly more informed than more relaxed ones.</a>
<a href="#7" id="7">Predicting which abstraction has the best benefit/effort relation is a hard task, which SPA addresses by using perimeter abstraction heuristics.</a>
<a href="#8" id="8">The search is performed in the less relaxed state spaces while it is feasible and coarser state spaces are used to continue the search afterwards.</a>
<a href="#9" id="9">SPA can be used both with hierarchies of PDB and M&S abstractions.</a>
<a href="#10" id="10">M&S represents abstract state spaces explicitly, which limits the size of M&S abstractions.</a>
<a href="#11" id="11">In order to obtain hierarchies with arbitrarily large M&S abstractions, we define SM&S abstractions as larger M&S abstractions based on the smaller explicitly represented M&S abstractions.</a>
<a href="#12" id="12">SM&S abstractions can be searched with symbolic search, in an attempt to combine the strengths of symbolic PDBs and the flexibility of M&S abstractions.</a>
<a href="#13" id="13">We prove that, for any abstraction derived using M&S with a linear merge strategy, it is possible to represent any set of abstract states as a decision diagram of polynomial size in the number of abstract states used to derive such abstraction.</a>
<a href="#14" id="14">Not only this bounds the size of BDDs in the symbolic search of M&S abstractions, but it may also have other uses such as extracting polynomial certificates of unsolvability in the form of BDDs [76].</a>
<a href="#15" id="15">Symbolic abstraction heuristics have been used mainly by symbolic search planners we advocate their use in explicit-state search planners.</a>
<a href="#16" id="16">Experimental results show that the symbolic perimeter heuristic is competitive with other state-of-the-art heuristics such as LM-cut even without any abstraction strategy.</a>
<a href="#17" id="17">SPA successfully uses abstractions to relax the perimeter in order to derive more informed heuristics, improving the performance even further.</a>
<a href="#18" id="18">Despite the greater generality of M&S abstractions, the simplicity of PDBs allows for more efficient symbolic operations and thus better heuristics.</a>
<a href="#19" id="19">Our algorithm is not necessarily limited to PDB or M&S abstractions, and could also potentially be used in combination with Cartesian abstractions [77], [78], or abstractions induced by BDD minimization methods that have been successfully used for model-checking [79].</a>
<a href="#20" id="20">Finding good abstraction hierarchies for the task at hand is still an open problem.</a>
<a href="#21" id="21">We partially address this problem by using multiple hierarchies.</a>
<a href="#22" id="22">SPA with multiple abstraction hierarchies is competitive with (and complementary to) symbolic PDB approaches that perform a search on the space of possible patterns, like the one used by the symbolic search planner Gamer.</a>
<a href="#23" id="23">We also analyzed the potential of using the perimeter to initialize abstract searches in Gamer 's pattern selection algorithm, substantially improving the results in many domains, but being detrimental in those domains where additivity is indirectly exploited by the symbolic search.</a>
<a href="#24" id="24">Analyzing the use of additive ensembles of perimeter PDBs is a promising line of research for future work.</a>
<a href="#25" id="25">Finally, another interesting avenue for future research is the study of symbolic perimeter abstractions outside optimal planning, e.g. in the context of proving unsolvability [80].</a>
</body>
</html>