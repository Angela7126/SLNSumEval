<html>
<head>
<meta name="TextLength" content="SENT_NUM:46, WORD_NUM:903">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented three different methods for analysing the complexity of qualitative CSPs extended with finite unary relations.</a>
<a href="#1" id="1">Assume we have a constraint language Γ over domain D and we want to analyse the complexity of CSP{a mathematical formula}(Γ∪Dc) or CSP{a mathematical formula}(Γ∪Df).</a>
<a href="#2" id="2">Which method should we use?</a>
<a href="#3" id="3">If Γ is ω-categorical, then methods I (model-complete cores) and II (homogeneity) should be considered first.</a>
<a href="#4" id="4">If there is a way of efficiently computing orbit-defining formulas, then method I is typically the easiest method to use and it gives polynomial-time equivalence of CSP(Γ) and CSP{a mathematical formula}(Γ∪Dc).</a>
<a href="#5" id="5">However, if {a mathematical formula}B⊆Γ and Γ is quantifier-free definable in {a mathematical formula}B for some partition scheme {a mathematical formula}B, then one should always check whether Γ is homogeneous or not.</a>
<a href="#6" id="6">If so, one can apply method II and circumvent the need for computing orbit-defining formulas.</a>
<a href="#7" id="7">Note, though, that one does not always get polynomial-time equivalence of CSP(Γ) and CSP{a mathematical formula}(Γ∪Dc) in this case.</a>
<a href="#8" id="8">If Γ is not ω-categorical (or there are other problems in applying method I and/or II), then one has to resort to method III (small solutions).</a>
<a href="#9" id="9">We exemplify this approach by taking a closer look at the cardinal relation algebra (CRA) [29], [50].</a>
<a href="#10" id="10">Here, the domain elements are points in the plane and we have nine basic relations (N, NE, E, SE, S, SW, W, NW and the equality relation EQ) that describe cardinal directions.</a>
<a href="#11" id="11">For instance, {a mathematical formula}(x,x′) SW {a mathematical formula}(y,y′) holds if and only if {a mathematical formula}x<x′ and {a mathematical formula}y<y′.</a>
<a href="#12" id="12">Let {a mathematical formula}B denote this set of relations over the set {a mathematical formula}Q2.</a>
<a href="#13" id="13">Li et al. [48] have shown that {a mathematical formula}B∨= extended with constants and/or finite unary relations give rise to an NP-complete constraint satisfaction problem.</a>
<a href="#14" id="14">We will now give a more fine-grained analysis in the case when we add constants to constraint languages.</a>
<a href="#15" id="15">Hirsch [32, Corollary 8] has shown that CRA is ω-categorical so method I is in principle applicable.</a>
<a href="#16" id="16">However, given a constraint language {a mathematical formula}Γ⊆B∨=, we do not know right away whether it is a model-complete core or not, and we do not know how to compute orbit-defining formulas.</a>
<a href="#17" id="17">This can probably be worked out quite easily since CRA is closely related to the point algebra PA.</a>
<a href="#18" id="18">A simpler way, though, is to note that Hirsch [32, Theorem 1] has proved that CRA is homogeneous.</a>
<a href="#19" id="19">If we combine this with the fact that CRA is a partition scheme, we can easily apply method II and conclude the following: if {a mathematical formula}B⊆Γ⊆B∨=, then CSP(Γ) and CSP{a mathematical formula}(Γ∪(Q2)c) are polynomial-time equivalent problems.</a>
<a href="#20" id="20">Methods I and II are based on exploiting model-theoretical properties of the underlying constraint languages.</a>
<a href="#21" id="21">While methods based on model theory and universal algebra have been very common when studying CSPs from the viewpoint of theoretical computer science [3], [13], [20], such methods have been less popular within the AI community (with some notable exceptions such as Hirsch [32] and Huang [35]).</a>
<a href="#22" id="22">Thus, we take the opportunity to discuss these methods in slightly more detail.</a>
<a href="#23" id="23">Method I. The main obstacle for applying method I is the need for computing orbit-defining formulas efficiently.</a>
<a href="#24" id="24">In fact, it is not even known if this problem is decidable or not in the general case.</a>
<a href="#25" id="25">Studying this problem is a very important future research direction.</a>
<a href="#26" id="26">In cases where we do not know how to efficiently generate orbit-defining formulas, there are (at least) two possible workarounds.</a>
<a href="#27" id="27">We have already encountered the first workaround in Corollary 16: the restriction to finite sets of constant relations.</a>
<a href="#28" id="28">Another workaround is to sacrifice polynomial-time equivalence and allow more time for computing the orbit-defining formula.</a>
<a href="#29" id="29">If the problem at hand is NP-hard, then a (preferably mildly) exponential algorithm can be acceptable.</a>
<a href="#30" id="30">In both cases, algorithmic methods for generating orbit-defining formulas would be helpful.</a>
<a href="#31" id="31">We note, on the positive side, that related definability problems have recently been successfully addressed, cf.</a>
<a href="#32" id="32">Bodirsky et al. [15].</a>
<a href="#33" id="33">Their methods are interesting since they combine methods taken from universal algebra, Ramsey theory, and topological dynamics.</a>
<a href="#34" id="34">Method II.</a>
<a href="#35" id="35">Given a structure Γ, it may be difficult to verify that it is indeed homogeneous.</a>
<a href="#36" id="36">Here, one should note that if Γ contains a finite number of relations, the domain of Γ is countably infinite, and Γ is homogeneous, then Γ is ω-categorical, cf.</a>
<a href="#37" id="37">Macpherson [53].</a>
<a href="#38" id="38">This explains why one should always check ω-categoricity first, and this can quite often be accomplished by using Theorem 11.</a>
<a href="#39" id="39">If Γ is ω-categorical, then Γ is homogeneous if and only if every formula in {a mathematical formula}Th(Γ) is equivalent to a quantifier-free formula (see, for instance, Macpherson [53]).</a>
<a href="#40" id="40">This gives an alternative way of proving homogeneity than using the automorphism-based definition directly.</a>
<a href="#41" id="41">This also clarifies the connections between method I and method II: recall that Γ is model-complete if and only if every formula in {a mathematical formula}Th(Γ) is equivalent to an existential formula.</a>
<a href="#42" id="42">Another approach for using homogeneity is to construct suitable homogeneous structures “from scratch”.</a>
<a href="#43" id="43">The main tool for this is Fraïssé amalgamation.</a>
<a href="#44" id="44">The details are outside the scope of this article: Macpherson [53] outlines the approach and concrete constructions for RCC-5 and RCC-8 can be found in Bodirsky and Chen [7] and Bodirsky and Wölfl [16], respectively.</a>
<a href="#45" id="45">One should note that amalgamation is quite common in the literature on CSPs and related problems; however, it is often referred to as the patchwork property[35], [52], [61].</a>
</body>
</html>