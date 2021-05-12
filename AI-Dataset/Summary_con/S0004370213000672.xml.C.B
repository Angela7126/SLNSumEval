<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:643">
</head>
<body bgcolor="white">
<a href="#0" id="0">The aim of this paper was to study the core principles underlying interpolative and extrapolative reasoning about categorization rules.</a>
<a href="#1" id="1">We have argued that sets of categorization rules can be seen as partial specifications of a linear mapping between conceptual spaces.</a>
<a href="#2" id="2">This view has allowed us to describe interpolation and extrapolation at a purely qualitative level, relying on qualitative spatial relations to encode knowledge about conceptual spaces rather than on degrees of similarity.</a>
<a href="#3" id="3">From a practical point of view, the approach is motivated from the observation that sufficient data to estimate the conceptual relationship between labels from the same attribute domain is often available, e.g. relying on statistical techniques such as multi-dimensional scaling or singular-value decomposition, while knowledge about how different attribute domains are related is often sparse and is usually encoded in a symbolic form.</a>
<a href="#4" id="4">The techniques presented in this paper show how knowledge about conceptual relations between labels of the same attribute domain may be leveraged to refine whatever symbolic knowledge of this kind we have.</a>
<a href="#5" id="5">Although the general inference problem we have considered is PSPACE-hard, we have shown that efficient implementations in polynomial time are possible if the number of attribute domains is sufficiently small.</a>
<a href="#6" id="6">We may expect that the full generality of our framework would not be needed in many applications.</a>
<a href="#7" id="7">In [34], for instance, an approach is presented to complete rule bases purely based on analogical proportions.</a>
<a href="#8" id="8">The proposal from [34] in fact corresponds to a special case of the approach presented in this paper, where the only non-trivial information in Σ are assertions of the form {a mathematical formula}par[1,1]̲(a,b,c;d) and {a mathematical formula}par[1,1]¯(a,b,c;d).</a>
<a href="#9" id="9">In [34] it is moreover assumed that all labels correspond to intervals in a uni-dimensional space, which implies that the relations {a mathematical formula}par[1,1]̲ and {a mathematical formula}par[1,1]¯ coincide, and moreover that they exhibit a number of symmetry and transitivity properties that are not generally valid (e.g. {a mathematical formula}par[1,1]̲(a,b,c;d) iff {a mathematical formula}par[1,1]̲(c,d,a;b)).</a>
<a href="#10" id="10">These simplifications lead to an inference process which is easier to use in practice, but which is based on assumptions that are not always realistic.</a>
<a href="#11" id="11">By putting the approach from [34] in relation to the approach from this paper, however, it immediately becomes apparent when these simplifications make sense, or how the approach should be adapted when they do not.</a>
<a href="#12" id="12">In contrast, some applications may require further generalizations of the approach we have presented here.</a>
<a href="#13" id="13">At the level of the conceptual spaces, we have restricted ourselves to Euclidean spaces, whereas arbitrary metric spaces might be considered instead.</a>
<a href="#14" id="14">Moreover, a better understanding is needed of which sets of assertions Σ are actually realizable, either in a Euclidean space or in an arbitrary metric space.</a>
<a href="#15" id="15">Currently, no sound and complete procedures are available to check the consistency of such a set.</a>
<a href="#16" id="16">Although this poses no problems when conceptual relations are obtained from geometric representations, consistency checking procedures may be important when other forms of acquisition are used (e.g. based on natural language processing).</a>
<a href="#17" id="17">In addition to betweenness and parallelism, other types of conceptual relations may also be considered, as the same methodology may be applied to any type of spatial relation that is invariant under linear transformations.</a>
<a href="#18" id="18">At the semantic level (Section 5), we have restricted ourselves to situations where only information about conceptual relation between individual labels is available.</a>
<a href="#19" id="19">If, however, information would be available about the betweenness or parallelism of disjunctions of labels, a refined definition of {a mathematical formula}bet̲ and {a mathematical formula}par̲ should be used, as e.g. {a mathematical formula}reg(b) may geometrically be between {a mathematical formula}reg(a1)∪⋯∪reg(ap) and {a mathematical formula}reg(c1)∪⋯∪reg(cq) even if {a mathematical formula}reg(b) is not between {a mathematical formula}reg(ai) and {a mathematical formula}reg(cj) for any i and j. In such a case, the syntactic characterization of Section 6 should be adapted as well.</a>
<a href="#20" id="20">Given the presented setting, however, such a generalization should be straightforward to formalize.</a>
</body>
</html>