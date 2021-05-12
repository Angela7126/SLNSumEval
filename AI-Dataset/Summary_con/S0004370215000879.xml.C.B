<html>
<head>
<meta name="TextLength" content="SENT_NUM:25, WORD_NUM:492">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we studied the problem of learning the CTRs of ads in sponsored search auctions with truthful mechanisms.</a>
<a href="#1" id="1">This problem is highly challenging since it requires the combination of online learning tools (i.e., regret minimization algorithms) and economic tools (i.e., truthful mechanisms).</a>
<a href="#2" id="2">While almost all the literature focused on single-slot scenarios, here we focused on multi-slot scenarios.</a>
<a href="#3" id="3">With multiple slots it is necessary to adopt a user model to characterize how the CTR of an ad varies as the allocation of displayed ads varies.</a>
<a href="#4" id="4">Here, we adopted the cascade model, that is the most common model used in the literature.</a>
<a href="#5" id="5">In the paper, we studied a number of scenarios, each with a specific information setting of unknown parameters.</a>
<a href="#6" id="6">For each scenario, we designed a truthful learning mechanism, studied its economic properties, derived an upper bound over the regret, and, for some mechanisms, also a lower bound.</a>
<a href="#7" id="7">We considered both the regret over the auctioneer's revenue and the SW.</a>
<a href="#8" id="8">We showed that for the cascade model with only position-dependent externalities it is possible to design a truthful no-regret learning mechanism for the general case in which all the parameters are unknown.</a>
<a href="#9" id="9">Our mechanism presents a regret {a mathematical formula}O˜(T23) and it is DSIC in expectation w.r.t.</a>
<a href="#10" id="10">the realization of the random component of the mechanism.</a>
<a href="#11" id="11">However, it remains open whether or not it is possible to obtain a regret {a mathematical formula}O˜(T12).</a>
<a href="#12" id="12">For specific cases, in which some parameters are known to the auctioneer, we obtained better results in terms of either incentive compatibility, obtaining dominant strategy truthfulness, or regret, obtaining a regret of zero.</a>
<a href="#13" id="13">We showed that for the cascade model with the positionand ad-dependent externalities it is possible to design a DSIC a posteriori mechanism with a regret {a mathematical formula}O˜(T23) when only the quality is unknown.</a>
<a href="#14" id="14">Instead, even when the cascade model is only with ad-dependent externalities and no parameter is known, it is not possible to obtain a no-regret DSIC a posteriori mechanism.</a>
<a href="#15" id="15">The proof of this result would seem to suggest that the same result holds also when a random mechanism is adopted and the truthfulness is in expectation w.r.t.</a>
<a href="#16" id="16">its realizations.</a>
<a href="#17" id="17">However, we did not produce any proof for that, leaving it for future works.</a>
<a href="#18" id="18">Finally, we empirically evaluated the bounds we provided, showing that the dependency of the regret on the parameters is mostly correct in a worst-case scenario.</a>
<a href="#19" id="19">Two main questions deserve future investigation.</a>
<a href="#20" id="20">The first question concerns the study of a lower bound for the case in which there are only position-dependent externalities and truthfulness is in expectation in expectation w.r.t.</a>
<a href="#21" id="21">only the realizations of the random component of the mechanism or also w.r.t.</a>
<a href="#22" id="22">the click realizations.</a>
<a href="#23" id="23">Furthermore, it is open whether the separation of exploration and exploitation phases is necessary and, in the negative case, whether it is possible to obtain a regret {a mathematical formula}O˜(T12).</a>
<a href="#24" id="24">The second question concerns a similar study related to the case with only ad-dependent externalities.</a>
</body>
</html>