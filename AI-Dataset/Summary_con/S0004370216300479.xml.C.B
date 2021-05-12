<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:549">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have defined the notion of bounded action theory in the situation calculus, where the number of fluent atoms that hold remains bounded.</a>
<a href="#1" id="1">We have shown that this restriction is sufficient to ensure that verification of an expressive class of temporal properties remains decidable, and is in fact EXPTIME-complete, despite the fact that we have an infinite domain and state space.</a>
<a href="#2" id="2">Our result holds even in the presence of incomplete information.</a>
<a href="#3" id="3">We have also argued that this restriction can be adhered to in practical applications, by identifying interesting classes of bounded action theories and showing that these can be used to model typical example dynamic domains.</a>
<a href="#4" id="4">Decidability is important from a theoretical standpoint, but we stress also that our result is fully constructive being based on a reduction to model checking of an (abstract) finite-state transition system.</a>
<a href="#5" id="5">An interesting future enterprise is to build on such a result to develop an actual situation calculus verification tool.</a>
<a href="#6" id="6">A future research direction of particular interest is a more systematic investigation of specification patterns for obtaining boundedness.</a>
<a href="#7" id="7">This includes patterns that provide bounded persistence and patterns that model bounded/fading memory.</a>
<a href="#8" id="8">These questions should be examined in light of different approaches that have been proposed for modeling knowledge, sensing, and revision in the situation calculus and related temporal logics [79], [35], [84], [89].</a>
<a href="#9" id="9">This work has already started.</a>
<a href="#10" id="10">In particular, as mentioned earlier, the approach of this paper has been extended in [31], [30] to allow verification of temporal properties over online executions of an agent, where the agent may acquire new information through sensing as it executes and only performs actions that are feasible according to its beliefs.</a>
<a href="#11" id="11">In that work, the agent's belief state is modeled meta-theoretically, as an action theory that is progressed as actions are performed and sensing results are obtained.</a>
<a href="#12" id="12">In [28], temporal epistemic verification is tackled within a language-theoretic viewpoint, where the situation calculus is extended with a knowledge modality [79].</a>
<a href="#13" id="13">The form of boundedness studied in that case requires that the number of object tuples that the agent thinks may belong to any given fluent be bounded.</a>
<a href="#14" id="14">In [31], [30], instead, it is only required that number of distinct tuples entailed to belong to a fluent is bounded, while the number of tuples that are in the extension of a fluent in some model of the theory need not be bounded.</a>
<a href="#15" id="15">More work is needed to fully reconcile these meta-theoretic and language-theoretic approaches.</a>
<a href="#16" id="16">Finally, an important topic to address is verification of agent programs [34] expressed in a high-level language, like Golog[58] or ConGolog[26], which are based on the situation calculus.</a>
<a href="#17" id="17">Some cases where verification of ConGolog programs is decidable are identified in [22].</a>
<a href="#18" id="18">More recently, the framework presented here has been extended to support verification of ConGolog programs, without recursive procedures, over bounded situation calculus action theories [29].</a>
<a href="#19" id="19">Note that this extension is not immediate, as a temporal property may hold over all executions of a program without holding over all branches of the situation tree.</a>
<a href="#20" id="20">However it can be shown that the whole program configuration, formed by the situation and the remaining part of the program to execute, is bounded (if we disallow recursion), and hence the approach presented in this paper can be applied to show decidability of verification [29].</a>
</body>
</html>