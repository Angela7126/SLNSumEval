<html>
<head>
<meta name="TextLength" content="SENT_NUM:44, WORD_NUM:1078">
</head>
<body bgcolor="white">
<a href="#0" id="0">The importance of having trust models has been emphasized in the literature.</a>
<a href="#1" id="1">As stated in [44], two elements have contributed to substantially increase the interest on trust in this area: the multi-agent system paradigm and the spectacular evolution of e-commerce.</a>
<a href="#2" id="2">The study of trust has many applications in Information and Communication Technologies.</a>
<a href="#3" id="3">For instance, trust has been recognized as a key factor for successful electronic commerce adoption.</a>
<a href="#4" id="4">These systems are used by intelligent software agents as a mechanism to search for trustworthy exchange partners and as an incentive in decision-making about whether or not to honor contracts.</a>
<a href="#5" id="5">Our proposal can be applied to any system requiring that trust or credibility of informants be taken into account.</a>
<a href="#6" id="6">In this work, we have introduced a trust model for a multi-agent setting.</a>
<a href="#7" id="7">In this model agents can share information representing trust assigned to its peers (called witness information in the literature).</a>
<a href="#8" id="8">We have defined an epistemic model where credibility objects include not only trust information but also the informant source.</a>
<a href="#9" id="9">These objects are maintained in a credibility base which represents a strict partial order among informant agents together with the source of the information.</a>
<a href="#10" id="10">Thus, upon arrival of new information regarding the credibility of its peers, an agent will be capable of revising this strict partial order, and in this manner change the trust in its peers accordingly.</a>
<a href="#11" id="11">In this paper we have introduced four operators for credibility bases: expansion, contraction, prioritized and non-prioritized revision.</a>
<a href="#12" id="12">The contraction operator uses the reliability stored in credibility objects for deciding which information prevails.</a>
<a href="#13" id="13">Then, based on our contraction and expansion operators, a prioritized revision was defined using Levi identity.</a>
<a href="#14" id="14">The non-prioritized revision operator uses the reliability of the input and the information stored in the credibility base in order to decide if the input is accepted or rejected.</a>
<a href="#15" id="15">These operators provide the capability of dynamically modifying the credibility of informants to reflect a new perception of the informant's trust, or when necessary to extend the set of informants by admitting the arrival of new informant agents.</a>
<a href="#16" id="16">These four change operators were defined through construction and postulates.</a>
<a href="#17" id="17">Note that the operators were defined following the constructive and black box approaches.</a>
<a href="#18" id="18">In the constructive approach, a concrete mechanism for change was explicitly defined, and in the black box approach, the properties that the operator should satisfy were specified regardless of how the operator will be built [27].</a>
<a href="#19" id="19">Representation theorems connected the two approaches improving our understanding of the constructions and the postulates.</a>
<a href="#20" id="20">It is important to note that we have proved representation theorems only for contraction and prioritized revision because they need the specification of a “selection mechanism” that represents a criterion used to define which credibility objects are preserved or discarded.</a>
<a href="#21" id="21">Non-prioritized revision is not fully characterized, and its complete characterization is subject of future work.</a>
<a href="#22" id="22">We will also consider the broadening of the results obtained here to deal with different contexts.</a>
<a href="#23" id="23">In [44] they offer the following example to show that trust is context dependent: “if we trust a doctor when she is recommending a medicine it does not mean we have to trust her when she is suggesting a bottle of wine”; here we have considered trust in a unique context.</a>
<a href="#24" id="24">Our proposed model was designed to associate a single trust value per agent in the multi-agent system without taking into account the context.</a>
<a href="#25" id="25">Since this last aspect has received little attention in the literature, as future research we propose to extend the results obtained here toward a multi-context model that will have the mechanisms to deal with several contexts simultaneously.</a>
<a href="#26" id="26">Another research line we consider as future work is to extend our operators assuming that the epistemic input is a set of credibility objects {a mathematical formula}{[T1,A1],…,[Tk,Ak]} where {a mathematical formula}Ti is a credibility tuple and {a mathematical formula}Ai is the informant that provides {a mathematical formula}Ti, for every {a mathematical formula}1⩽i⩽k.</a>
<a href="#27" id="27">In Definition 3 we have established the restriction that in a credibility object {a mathematical formula}[T,S] the source S cannot appear in any place in T. The motivation for that decision is illustrated by the following example.</a>
<a href="#28" id="28">Let {a mathematical formula}CQ={[(B,A),B]} be the credibility base of an agent Q, that is, agent B regards agent A as more credible than itself.</a>
<a href="#29" id="29">Now consider the revision of {a mathematical formula}CQ by the credibility object {a mathematical formula}[(A,B),A] using the non-prioritized revision operator.</a>
<a href="#30" id="30">The new information expresses that, according to agent A, agent B is more credible than itself.</a>
<a href="#31" id="31">Using the information contained in {a mathematical formula}CQ the new information is accepted and the revised base should be {a mathematical formula}CQ={[(A,B),A]}.</a>
<a href="#32" id="32">This opens the question over if either the old information or the new information should be used for deciding acceptance or rejection.</a>
<a href="#33" id="33">However, from a positive point of view, there are particular situations where some interesting examples can be represented if the restriction is lifted.</a>
<a href="#34" id="34">For instance, consider a situation where an agent A interacts with his doctor D. It is natural that D considers himself less credible than a specialist S in some medical topic; consequently, D can inform A the credibility object {a mathematical formula}[(D,S),D].</a>
<a href="#35" id="35">Consider a situation involving two researchers A and B, and that A has read several articles written by B on a certain topic.</a>
<a href="#36" id="36">Since A regards B as a specialist in the subject in question, he believes that he is less credible than B, i.e., {a mathematical formula}CA={[(A,B),A]}, also A and B are in a situation where they interact with each other.</a>
<a href="#37" id="37">Because B knows that A is well read, he knows that A has read not only his own publications but also is acquainted with other approaches; therefore, B considers that A is more credible than himself in that topic.</a>
<a href="#38" id="38">Then, it is natural that now A accepts himself as more credible than B. If A receives the credibility object {a mathematical formula}[(B,A),B] then according to the non-prioritized operator the agent would accept the new information, and hence, {a mathematical formula}CA={[(B,A),B]}.</a>
<a href="#39" id="39">The discussion above, clearly motivates further research focussed in operators that are able to handle this more general situation.</a>
<a href="#40" id="40">Finally, it is interesting to observe the natural phenomenon of retransmission of information is related to our formalism.</a>
<a href="#41" id="41">This was previously considered in the work presented in [33], [48] using a different context.</a>
<a href="#42" id="42">The research reported there can be adapted and expanded using the framework presented here.</a>
<a href="#43" id="43">We will also explore the interesting issues related to this particular action in our future work.</a>
</body>
</html>