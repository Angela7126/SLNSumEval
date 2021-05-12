<html>
<head>
<meta name="TextLength" content="SENT_NUM:25, WORD_NUM:647">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have introduced a novel language for logical and relational learning called kLog.</a>
<a href="#1" id="1">It tightly integrates logical and relational learning with kernel methods and constitutes a principled framework for statistical relational learning based on kernel methods rather than on graphical models.</a>
<a href="#2" id="2">kLog uses a representation that is based on E/R modeling, which is close to representations being used by contemporary statistical relational learners.</a>
<a href="#3" id="3">kLog first performs graphicalization, that is, it computes a set of labeled graphs that are equivalent to the original representation, and then employs a graph kernel to realize statistical learning.</a>
<a href="#4" id="4">We have shown that the kLog framework can be used to formulate and address a wide range of learning tasks, that it performs at least comparably to state-of-the-art statistical relational learning techniques, and also that it can be used as a programming language for machine learning.</a>
<a href="#5" id="5">The system presented in this paper is a first step towards a kernel-based language for relational learning but there are unanswered questions and interesting open directions for further research.</a>
<a href="#6" id="6">One important aspect is the possibility of performing collective classification (or structured output prediction).</a>
<a href="#7" id="7">Structured output learning problems can be naturally defined within kLog's semantics: graphicalization followed by a graph kernel yields a joint feature vector {a mathematical formula}ϕ(x,y) where y are the groundings of the output predicates.</a>
<a href="#8" id="8">Collective prediction amounts to maximizing {a mathematical formula}w⊤ϕ(x,y) with respect to y. There are two important cases to consider.</a>
<a href="#9" id="9">If groundings in y do not affect the graph structure (because they never affect the intensional signatures) then the collective classification problem is not more complicated than in related SRL systems.</a>
<a href="#10" id="10">For example, if dependencies have a regular sequential structure, dynamic programming can be used for this step, exactly as in conditional random fields (indeed, collective classification has been successfully exploited within kLog in an application to natural language test segmentation [83]).</a>
<a href="#11" id="11">However, in general, changing y during search will also change the graph structure.</a>
<a href="#12" id="12">In principle it is feasible to redo graphicalization from scratch during search, apply the graph kernel again and eventually evaluate {a mathematical formula}w⊤ϕ(x,y), but such a naive approach would of course be very inefficient.</a>
<a href="#13" id="13">Developing clever and faster algorithms for this purpose is an interesting open issue.</a>
<a href="#14" id="14">It should be remarked, however, that even without collective classification, kLog achieves good empirical results thanks to the fact that features produced by the graph kernel provide a wide relational context.</a>
<a href="#15" id="15">Better understanding of generalization for structured prediction models has begun to emerge (see [84] and references therein) and a theoretical analysis of learning within the present kLog setting is another potential direction for future research.</a>
<a href="#16" id="16">The graph kernel that is currently employed in kLog makes use of the notion of topological distances to define the concept of neighborhoods.</a>
<a href="#17" id="17">In this way, given a predicate of interest, properties of “nearby” tuples are combined to generate features relevant for that predicate.</a>
<a href="#18" id="18">As a consequence, when topological distances are not informative (e.g., in the case of dense graphs with small diameter) then large fractions of the graph become accessible to any neighborhood and the features induced for a specific predicate cease to be discriminative.</a>
<a href="#19" id="19">In these cases (typical when dealing with small-world networks), kernels with a different type of bias (e.g., flow-based kernels) are more appropriate.</a>
<a href="#20" id="20">The implementation of a library of kernels suitable for different types of graphs, as well as the integration of other existing graph kernels (such as [40], [41], [42]) in the kLog framework, is therefore an important direction for future development.</a>
<a href="#21" id="21">Furthermore, even though kLog's current implementation is quite performant, there are interesting implementation issues to be studied.</a>
<a href="#22" id="22">Many of these are similar to those employed in statistical relational learning systems such as Alchemy [7] and ProbLog [85].</a>
<a href="#23" id="23">kLog is being actively used for developing applications.</a>
<a href="#24" id="24">We are currently exploring applications of kLog in natural language processing [86], [83], [87] and in computer vision [88], [89], [90].</a>
</body>
</html>