<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:480">
</head>
<body bgcolor="white">
<a href="#0" id="0">Uniformly accurate votes.</a>
<a href="#1" id="1">Motivated by crowdsourcing settings, we considered the case where the average error in the input votes is guaranteed to be low.</a>
<a href="#2" id="2">Instead, suppose we know that every vote in the input profile π is at distance at most t from the ground truth {a mathematical formula}σ⁎, i.e., {a mathematical formula}maxσ∈π⁡d(σ,σ⁎)≤t.</a>
<a href="#3" id="3">If t is small, this is a stronger assumption because it means that there are no outliers, which is implausible in crowdsourcing settings but plausible if the input votes are expert opinions.</a>
<a href="#4" id="4">In this setting, it is immediate that any vote in the given profile is at distance at most {a mathematical formula}d↓(t) from the ground truth.</a>
<a href="#5" id="5">Moreover, the proof of Theorem 4 goes through, so this bound is tight in the worst case; however, returning a ranking from the profile is not optimal for every profile.</a>
<a href="#6" id="6">Randomization.</a>
<a href="#7" id="7">We did not consider randomized rules, which may return a distribution over rankings.</a>
<a href="#8" id="8">If we take the error of a randomized rule to be the expected distance of the returned ranking from the ground truth, it is easy to obtain an upper bound of t. Again, the proof of Theorem 4 can be extended to yield an almost matching lower bound of {a mathematical formula}d↓(t).</a>
<a href="#9" id="9">While randomized rules provide better guarantees, they are often impractical: low error is only guaranteed when rankings are repeatedly selected from the output distribution of the randomized rule on the same profile; however, most social choice settings see only a single outcome realized.</a>
<a href="#10" id="10">{sup:6}</a>
<a href="#11" id="11">Complexity.</a>
<a href="#12" id="12">A potential drawback of the proposed approach is computational complexity.</a>
<a href="#13" id="13">For example, consider the Kendall tau distance.</a>
<a href="#14" id="14">When t is small enough, only the Kemeny ranking would be a possible ground truth, and {a mathematical formula}OPTdKT or any finite approximation thereof must return the Kemeny ranking, if it is unique.</a>
<a href="#15" id="15">The {a mathematical formula}NP-hardness of computing the Kemeny ranking [6] therefore suggests that computing or approximating {a mathematical formula}OPTdKT is {a mathematical formula}NP-hard.</a>
<a href="#16" id="16">One way to circumvent this computational obstacle is picking a ranking from the given profile, which provides a weaker bound of 3t instead of 2t on the distance from the unknown ground truth (see Theorem 2).</a>
<a href="#17" id="17">However, in practice the optimal ranking can also be computed using various fixed-parameter tractable algorithms, integer programming solutions, and other heuristics, which are known to provide good performance for these types of computational problems (see, e.g., [8], [7]).</a>
<a href="#18" id="18">More importantly, the crowdsourcing settings that motivate our work inherently restrict the number of alternatives to a relatively small constant: a human would find it difficult to effectively rank more than, say, 10 alternatives.</a>
<a href="#19" id="19">With a constant number of alternatives, we can simply enumerate all possible rankings in polynomial time, making each and every computational problem considered in this paper tractable.</a>
<a href="#20" id="20">In fact, this is what we did in our experiments.</a>
<a href="#21" id="21">Therefore, we do not view computational complexity as an insurmountable obstacle.</a>
</body>
</html>