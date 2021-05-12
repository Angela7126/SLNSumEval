<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:600">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we tackled a novel problem in the area of abstract argumentation.</a>
<a href="#1" id="1">We initiated a study on the characteristics the sets of extensions w.r.t.</a>
<a href="#2" id="2">a given semantics satisfy.</a>
<a href="#3" id="3">For the semantics naive, stable, stage, preferred, and semi-stable we have an exact picture fully describing their signatures.</a>
<a href="#4" id="4">These results also tell about the limits of global disagreement (a notion introduced in [12]) that can be modeled within afs, e.g. our results show that preferred and semi-stable semantics are able to express more disagreement than stage semantics: {a mathematical formula}Σstage⊂Σpref=Σsem.</a>
<a href="#5" id="5">Besides an exact characterization of the signature of complete semantics, future work includes an investigation of other important semantics, in particular cf2-semantics [2] and resolution-based grounded (RBG) [4]; for the latter semantics recent results [25] show a quite different behavior.</a>
<a href="#6" id="6">More specifically, these results show that the signature of RBG is a proper subset of {a mathematical formula}Σpref (and thus of {a mathematical formula}Σsem) but incomparable to {a mathematical formula}Σstb (resp.</a>
<a href="#7" id="7">to {a mathematical formula}Σstage).</a>
<a href="#8" id="8">Moreover, one can easily show that it is a proper superset of {a mathematical formula}Σnaive.</a>
<a href="#9" id="9">However, an exact characterization is still open.</a>
<a href="#10" id="10">We also plan an according extension of our complexity analysis.</a>
<a href="#11" id="11">Furthermore, exact bounds for some of the decision problems considered are still missing for the case of naive extensions.</a>
<a href="#12" id="12">Since we have viewed semantics here only in an extension-based way, it would also be of high interest to extend our studies to labeling-based semantics [13].</a>
<a href="#13" id="13">Preliminary work in this direction has recently been done by Dyrkolbotn [26].</a>
<a href="#14" id="14">Another interesting direction is to restrict the concepts of signatures and realizability in such a way that no additional arguments are allowed (recall that we made heavy use of such arguments, for instance in the canonical defense-argumentation-framework, cf.</a>
<a href="#15" id="15">Definition 14).</a>
<a href="#16" id="16">A first step towards this direction has recently been undertaken in [9].</a>
<a href="#17" id="17">That paper also presents alternative characterizations for some of the signatures we have presented here.</a>
<a href="#18" id="18">A further question is based on the fact that signatures address single semantics in isolation.</a>
<a href="#19" id="19">The fact that many semantics are often non-coincident, e.g. semi-stable and preferred as discussed in the introduction, does motivate a far more general concept of “realizability”.</a>
<a href="#20" id="20">Suppose we are given two (or, indeed, more) collections of subsets of arguments, {a mathematical formula}(S,T) say.</a>
<a href="#21" id="21">Consider two extension-based semantics, σ and τ, for which there are afs F in which {a mathematical formula}σ(F)≠τ(F).</a>
<a href="#22" id="22">Then, in this context, it is natural to raise questions such as: What conditions defined on pairs of sets, {a mathematical formula}(S,T) describe when a singleafF can be constructed for which {a mathematical formula}σ(F)=Sand{a mathematical formula}τ(F)=T.</a>
<a href="#23" id="23">Prior to embarking on any analysis of such multiple characterization issues, an essential first step is to glean some understanding of behavior with respect to single semantics.</a>
<a href="#24" id="24">That is exactly what we have done in this paper.</a>
<a href="#25" id="25">Also recall that our concept of signatures allows the realization of set {a mathematical formula}S as the σ-extensions of some af.</a>
<a href="#26" id="26">However, we have not investigated the properties of individual frameworks that witness such realizations.</a>
<a href="#27" id="27">Typically one might expect that when {a mathematical formula}S∈Σσ holds there may be many different choices for F within which {a mathematical formula}σ(F)=S.</a>
<a href="#28" id="28">In this light, a number of interesting questions arise: (a) how many such frameworks (over a given set of arguments) do exist?</a>
<a href="#29" id="29">(b) how large is a minimal such framework?</a>
<a href="#30" id="30">(c) can we find such frameworks meeting desirable structural conditions, e.g. being acyclic or bipartite given the algorithmic advantages of these forms.</a>
<a href="#31" id="31">Finally, we also want to explore how our results allow for pruning the search space in algorithms for abstract argumentation.</a>
</body>
</html>