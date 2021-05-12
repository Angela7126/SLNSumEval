<html>
<head>
<meta name="TextLength" content="SENT_NUM:36, WORD_NUM:995">
</head>
<body bgcolor="white">
<a href="#0" id="0">The importance of having trust models has been widely emphasized in the literature.</a>
<a href="#1" id="1">In multi-agent systems, representing and making possible the evaluation of the credibility associated with a piece of information is important, especially when the agents have their own beliefs and can obtain new information from other sources [12].</a>
<a href="#2" id="2">As stated in [28], [32], two elements have contributed to substantially increase the interest on trust in this area: the dissemination of the multi-agent paradigm to implement distributed systems and the dramatic evolution of e-commerce.</a>
<a href="#3" id="3">The study of trust has many applications in Information and Communication Technologies; e.g., trust has been recognized as a key factor for successful e-commerce adoption.</a>
<a href="#4" id="4">These systems are used by autonomous software agents as a mechanism to search for trustworthy exchange partners and as an incentive in decision-making about whether or not to honor contracts.</a>
<a href="#5" id="5">Our proposal can be applied to any system requiring that trust or credibility of informants be taken into account or in approaches in which users can review or provide opinions about other users, as we mentioned in Section 5.</a>
<a href="#6" id="6">In this work, we have proposed an argumentative framework with recursive attacks to address a trust model in a collaborative open multi-agent system.</a>
<a href="#7" id="7">We have focused in scenarios where agents share information about the credibility or informational trust they have assigned to their peers (referred to as witness information in the literature).</a>
<a href="#8" id="8">We have represented informants' credibility through credibility objects which include not only trust information (credibility element) but also the informant source.</a>
<a href="#9" id="9">These objects are maintained in a credibility base which can store information in conflict.</a>
<a href="#10" id="10">Thus, when an agent needs to determine the credibility of its peers to make decisions, the agent needs an ordered set of informants without information in conflict.</a>
<a href="#11" id="11">Here, we have presented a system capable of building a partially ordered credibility relation from a potentially contradictory credibility base by using argumentative inference.</a>
<a href="#12" id="12">Such relation is not any arbitrary subset of partially ordered credibility elements obtained from the credibility base; actually, the output of our system is a subset of credibility elements that can be justified after an argumentation process.</a>
<a href="#13" id="13">In this process, we aimed to select the most reliable information when conflicts are analyzed.</a>
<a href="#14" id="14">In the formalism, an argument is a reason why an agent may infer that an informant is preferred over other; these reasons are tentative and can be challenged for other reasons through attacks.</a>
<a href="#15" id="15">As we have shown, the reliability measure in our approach depends only on the credibility relation, leading to a recursive scenario where this credibility can be also in conflict or challenged.</a>
<a href="#16" id="16">To capture these recursive relations, we have introduced different forms of attacks to attacks.</a>
<a href="#17" id="17">The key element for this are the reliability-attacks, whose goal is to capture the intuition that an argument or an attack based on potentially more credible sources can not be defeated by another with lesser credible sources.</a>
<a href="#18" id="18">These attacks are considered by the argumentation mechanism to decide which arguments are accepted, which in turn are the arguments that support the credibility elements that we consider as justified.</a>
<a href="#19" id="19">To reason argumentatively with the recursive interactions, we instantiated an AFRA [3], [4] with the arguments and attacks of a credibility base, and used the notions of acceptability semantics already defined for such framework.</a>
<a href="#20" id="20">This framework was selected because it was conceived and equipped with tools that naturally deal with recursive attacks and regards attacks as defeasible entities.</a>
<a href="#21" id="21">As pointed out in [7] the defeasibility of attacks can be a useful modeling tool when we are dealing with meta-argumentation such as in our case: an argument producing a reliability-attack to a trust-attack is arguing about the acceptability status of arguments involved in the trust-attacks.</a>
<a href="#22" id="22">Alternatively, we could have used another argumentation framework such as [14]; however, that would have lead us to use an artificial encoding of the recursive relations using special arguments and to formalize the intuition of the acceptance status of these special arguments.</a>
<a href="#23" id="23">We used the notion of acceptability semantics to determine which are the acceptance status of the arguments in our system; in particular, we committed to the extensional approach of the preferred semantics.</a>
<a href="#24" id="24">We have formally shown that extensions are sound, i.e., there is no pair of arguments holding contradictory conclusions in an extension, and we have shown that the conclusions of an extension from a credibility base constitute a partial order with respect to the credibility relation.</a>
<a href="#25" id="25">We have also shown that when a credibility base has several extensions, each one corresponds to a choice of arguments and attacks involved in conflicts that could not be resolved using reliability.</a>
<a href="#26" id="26">As future work, we intent to develop a complete implementation of our proposal.</a>
<a href="#27" id="27">Our idea is to develop tools for generating the arguments and attacks of a credibility base and integrate them with some of the recent methods for extension enumeration in abstract argumentation (such as jArgSemSAT [10]).</a>
<a href="#28" id="28">For such an integration, as previously mentioned in Section 4, we could use the existing methods for transforming AFRAs into classical argumentation frameworks.</a>
<a href="#29" id="29">Having such implementation will allow us to throughly evaluate our approach using real world data, in the context of the applications described in Section 5.</a>
<a href="#30" id="30">We also want to integrate the notion of distrust along to the credibility relation, in non collaborative scenarios.</a>
<a href="#31" id="31">Our idea in this regard is to use another type of attack to model the inherent conflicts between these two notions, and to consider the problem of identity theft.</a>
<a href="#32" id="32">Also we will study how to integrate our credibility bases with the efficacy measure used in [18], [19] to reason with trust and distrust relations.</a>
<a href="#33" id="33">In addition, we want to study how our approach can be combined with other argumentation frameworks that use trust as a decision support mechanism, such as [38].</a>
<a href="#34" id="34">Finally, it is also clear that a bootstrapping mechanism is needed; one alternative to effect this process could be to use direct experience [32].</a>
<a href="#35" id="35">Such alternative is left as future work.</a>
</body>
</html>