<html>
<head>
<meta name="TextLength" content="SENT_NUM:34, WORD_NUM:934">
</head>
<body bgcolor="white">
<a href="#0" id="0">The uniqueness of the analysis given in the paper is two-fold.</a>
<a href="#1" id="1">First, the joint search model it uses does not rely on the notion of a “representative agent” that searches on behalf of the group, as in prior work, but rather utilizes the fact that several agents can execute individual search in parallel.</a>
<a href="#2" id="2">This use of parallel search improves the group's performance whenever the search horizon is finite, which is the case in most real-life settings.</a>
<a href="#3" id="3">Second, it allows agents to be self-interested, which makes the model more applicable (than the fully cooperative one used in prior work) whenever the agents represent different individuals with different goals or that cannot be forced to obey some external solution which is “socially beneficial”.</a>
<a href="#4" id="4">The model is, of course, applicable to any multi-agent search application in which findings can benefit all agents, information can be shared (either throughout or at the end of the process) and costs and benefits are additive.</a>
<a href="#5" id="5">From the practical aspect, the research of joint search has gained increasing importance with the rapid growth of ad-hoc cooperation and group formation over the Internet.</a>
<a href="#6" id="6">Many new web-sites are now allowing users to achieve their goals by sharing their knowledge and information.</a>
<a href="#7" id="7">The results reported in this paper are important inputs for such markets and system designers by enabling them to predict the strategies that will be used and the resulting system's performance.</a>
<a href="#8" id="8">These primarily facilitate the proper design of the system and the determination of what elements should and should not be included in such systems in order to achieve specific goals and promote certain behavior.</a>
<a href="#9" id="9">In particular, the introduction of some seemingly beneficial elements may actually be counterproductive.</a>
<a href="#10" id="10">The paper illustrates the failure of several such “enhancers” when used with self-interested agents.</a>
<a href="#11" id="11">The failure of these enhancers is explained by the stability requirement.</a>
<a href="#12" id="12">That is, while better solutions that improve both individual and overall expected utilities by making use of these enhancers can be extracted, these solutions cannot hold as some of the agents have an incentive to individually deviate from them.</a>
<a href="#13" id="13">The solutions that are stable in the latter case are based on an overall search to a lesser extent, resulting in degradation of overall and individual performance.</a>
<a href="#14" id="14">The implication of these somehow non-intuitive results is that cooperation-enhancers should not be taken for granted and used as a default whenever some of the agents are self-interested.</a>
<a href="#15" id="15">The idea of sub-optimal behavior resulting from self-interestedness is not new in itself and has been demonstrated in other various domains as discussed earlier in this paper.</a>
<a href="#16" id="16">Nonetheless, the model and analysis given in this paper are totally different from the above mentioned and reveal the effect of unique properties of the costly search problem in such context.</a>
<a href="#17" id="17">There are numerous extensions to the basic joint search model presented in this paper that are worth pursuing.</a>
<a href="#18" id="18">For example, each individual agent may be interested in more than a single item.</a>
<a href="#19" id="19">Similarly, the communication between the agents does not necessarily have to be reliable, and in some cases the agents may incur costs due to such communication.</a>
<a href="#20" id="20">For some standard cost structures, the changes are straightforward, as discussed in the relevant analysis sections.</a>
<a href="#21" id="21">For others, and for the case of noisy communication, substantial changes may be required.</a>
<a href="#22" id="22">In fact, the introduction of noisy and/or costly communication can actually turn out to be beneficial, based on the examples given for the disadvantages of communication in these settings.</a>
<a href="#23" id="23">Similarly, for the case where the agents are heterogeneous in terms of their goals, the amount of changes required in the analysis depends on the specific model variant used.</a>
<a href="#24" id="24">For example, consider the case where each agent values differently the different opportunities and the agents may use any of the findings of others.</a>
<a href="#25" id="25">In the fully cooperative joint search, the optimal joint-search strategy is no longer reservation-value based, but now relies on a reservation frontier [10].</a>
<a href="#26" id="26">This is because the state of the agents along their search, as a group, depends on the different values assigned to the attributes upon which the valuation functions are defined.</a>
<a href="#27" id="27">As for the case of joint search with self-interested agents, here the change is simpler and mainly applies to the way the distribution of values obtained by others are calculated.</a>
<a href="#28" id="28">The individual strategies remain reservation-value-based.</a>
<a href="#29" id="29">In other cases, e.g., when using continuous communication or when all agents are constrained to eventually pick the same opportunity, among those searched, the changes are substantial, and many additional aspects need to be clarified first (e.g., how the agents decide on the opportunity that will be eventually selected in settings with conflicting preferences).</a>
<a href="#30" id="30">Finally, the analysis given in the paper can be augmented for designing and testing methods and mechanisms that will increase the overall and/or individual welfare in joint search with self-interested agent settings.</a>
<a href="#31" id="31">For the most part, the goal is to induce increased cooperation and individual search in cases where such cooperation is beneficial for the system as a whole, but strategically disadvantageous for the individual self-interested agent.</a>
<a href="#32" id="32">Among these are methods for restructuring the incentives to promote cooperation and increase overall utility (e.g., by requiring all agents to pay a fee to the agent that found the lowest price), partitioning the agents into separate groups – each sharing its results only within the group – or limiting communication between agents.</a>
<a href="#33" id="33">Other methods may include adding enforcement mechanisms into the system, which will require the agents to follow some prescribed behavior (e.g. search some fixed number of opportunities), achieved by allowing only the agents that agree to the enforcement to enjoy the results of other such agents.</a>
</body>
</html>