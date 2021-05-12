<html>
<head>
<meta name="TextLength" content="SENT_NUM:49, WORD_NUM:1365">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we captured the dynamics of publicly observable private resolution of distributed knowledge.</a>
<a href="#1" id="1">Resolution operators (based on update semantics) are both an alternative and a complement to the standard distributed knowledge operators (which are based on standard modal semantics).</a>
<a href="#2" id="2">Resolution operators let us reason about the relationship between common knowledge and distributed knowledge in general, and in particular about distributed knowledge as potential common knowledge.</a>
<a href="#3" id="3">When can distributed knowledge become common knowledge?</a>
<a href="#4" id="4">A naive idea would be that {a mathematical formula}DGφ should imply that {a mathematical formula}RGCGφ, that any information that is distributed can become common knowledge through resolution.</a>
<a href="#5" id="5">This does not hold in general, however, φ might even become false after resolution (an example is the formula {a mathematical formula}D{1,2}(p∧¬K1p) discussed in the introduction).</a>
<a href="#6" id="6">We do, however, have the following (Proposition 9(2) with {a mathematical formula}G=H):{a mathematical formula} – a fact can become common knowledge after the group have shared their information if and only if it was distributed knowledge before the event that the fact would be true after the event.</a>
<a href="#7" id="7">This is exactly the distributed knowledge that can become common knowledge (in our special case of publicly observable private resolution of distributed knowledge).</a>
<a href="#8" id="8">If the grand coalition resolves its distributed knowledge, there is no distinction between distributed and common knowledge any more: {an inline-figure} (Proposition 8).</a>
<a href="#9" id="9">Although the model transformation expressed by the resolution operators is similar to those found in the simplest dynamic epistemic logics [34] such as public announcement logics [27], as we have seen it cannot be expressed in those logics.</a>
<a href="#10" id="10">Resolution is not a public announcement, rather it bears a resemblance to semi-private announcements (sometimes called semi-public announcements) [6], [37], [8], [36], such as the action of showing a card to another player while the remaining players look on (without seeing what the card is), which have been modeled in more general dynamic epistemic logic frameworks such as action model logic [7], [6] and epistemic action logic [35], [36], [37].</a>
<a href="#11" id="11">However, although resolution has the flavor of a semi-private announcement, there clearly are important differences (for example, resolution requires no preconditions), and indeed it is easy to see that resolution operators cannot be expressed as either action models nor epistemic actions (see Fact 3).</a>
<a href="#12" id="12">The full relationship between resolution and semi-private announcements is not completely clear, and we leave that for future work.</a>
<a href="#13" id="13">As discussed in the introduction, it has been argued that distributed knowledge in general does not comply with the following principle of full communication[33]: if {a mathematical formula}DGφ is true, then φ should follow logically from the set of all formulas known by the individual agents in the group.</a>
<a href="#14" id="14">This can be seen as a problem: that agents can have distributed knowledge without being able to establish it “through communication” [33].</a>
<a href="#15" id="15">Several works [33], [16], [28] have tried to characterize classes of models on which the principle of full communication does hold; the class of all such models is called full communication models[28].</a>
<a href="#16" id="16">This may seem related to the distinction between distributed knowledge and resolution operators: the latter is intuitively related to internal “full” communication in the group.</a>
<a href="#17" id="17">However, this similarity is superficial: the notion of full communication in the sense of [33] is about expressive power of the communication language and the limits that puts on the resulting possible epistemic states under certain assumptions about how information is shared.</a>
<a href="#18" id="18">The key point of the resolution operators, on the other hand, compared with the standard distributed knowledge operators, is to make a distinction between before and after the information sharing event.</a>
<a href="#19" id="19">That distinction is not made in standard distributed knowledge, even when restricted to full communication models: it is easy to see that, e.g., {a mathematical formula}D{1,2}(p∧¬K1p) is satisfiable also on full communication models.</a>
<a href="#20" id="20">The two ideas, of limiting models to full communication models and of modeling group information sharing events using model updates, are orthogonal, and we could very well restrict our logics with resolution operators to full communication models.</a>
<a href="#21" id="21">We leave that for future work.</a>
<a href="#22" id="22">Furthermore, it would be interesting to look at a combined variant: “update by full communication”, which takes the communication language into account when defining the updated model.</a>
<a href="#23" id="23">Also of interest for future work is to look at other assumptions about the other agents' knowledge about the group communication event taking place.</a>
<a href="#24" id="24">In this paper we only studied the case that it is common knowledge that the event takes place (but not what the agents in the group learn).</a>
<a href="#25" id="25">That was naturally modeled using a “global” model update: in every state, replace accessibility for each agent in the group with the group accessibility (intersection).</a>
<a href="#26" id="26">An interesting and also natural alternative is doing only a “local” model update: change accessibility in the same way, but only in the current state.</a>
<a href="#27" id="27">That would correspond to it being common knowledge that if this is the current state, then the group resolves their knowledge.</a>
<a href="#28" id="28">When looking at the interaction of the resolution and common knowledge operators one might be reminded of relativized common knowledge[31], [32].</a>
<a href="#29" id="29">Languages with a (generalized variant of) relativized common knowledge and distributed knowledge were recently studied [39].</a>
<a href="#30" id="30">Here is an open question: can {a mathematical formula}RGCHφ be expressed using relativized common knowledge, in combination with other operators?</a>
<a href="#31" id="31">We mentioned related work on the interaction of knowledge and ability in the introduction, and the fact that {a mathematical formula}RGφ can be read as G having the joint ability to make φ come about.</a>
<a href="#32" id="32">The conceptually probably closest work in this area is group announcement logic[2], where formulas of the form {a mathematical formula}〈G〉φ say that G can make a joint public announcement such that φ will become true.</a>
<a href="#33" id="33">A significant difference to the resolution operators in this paper is that the latter model private communication.</a>
<a href="#34" id="34">Yet, the exact relationship between these operators is interesting for future work.</a>
<a href="#35" id="35">Considering knowledge and ability more generally, in our formalization of resolution there is indeed a distinction between ability to achieve something (by resolving distributed knowledge), and knowledge of that ability.</a>
<a href="#36" id="36">It might be that {a mathematical formula}RGφ holds without either {a mathematical formula}KiRGφ ({a mathematical formula}i∈G), {a mathematical formula}DGRGφ, or {a mathematical formula}CGRGφ holds.</a>
<a href="#37" id="37">For distributed knowledge of ability we have observed an exact principle: {a mathematical formula}DGRGφ holds if and only if {a mathematical formula}RGDGφ holds.</a>
<a href="#38" id="38">However, for resolution there is no distinction between knowing that and knowing how: there is only one way to resolve.</a>
<a href="#39" id="39">That distinction may be relevant for possible future formalizations of non-public resolution.</a>
<a href="#40" id="40">Knowledge, ability, knowing-how and coordination have also been considered in situation calculus, with several approaches formalizing notions of joint ability under incomplete information in a multi-agent setting [20], [17].</a>
<a href="#41" id="41">These notions of joint ability are, however, very different from resolution-as-ability.</a>
<a href="#42" id="42">The former is based on implicit coordination through individual knowledge, where each agent chooses a strategy based only on her own knowledge and beliefs about what the other agents will do, without any communication or other kinds of information sharing or explicit coordination.</a>
<a href="#43" id="43">Resolution-as-ability, on the other hand, is about the group's ability to obtain certain individual epistemic states, states from which the first type of ability can be considered, through some kind of communication.</a>
<a href="#44" id="44">Combining these two types of ability, which individual knowledge states a group can achieve and what a group can achieve with no (or only implicit) coordination based on individual knowledge states, is an interesting opportunity for future work.</a>
<a href="#45" id="45">In fact, we are not aware of any formalization of distributed knowledge in situation calculus, and importing distributed knowledge and resolution into situation calculus frameworks could be a starting point for formalizing a more sophisticated notion of joint ability in these frameworks.</a>
<a href="#46" id="46">On a related note, we believe that the work on resolution in this article could be particularly useful in the area of multi-agent epistemic planning [5] mentioned in the introduction, which is based on modal logic and on the same type of update semantics used to model resolution in this paper.</a>
<a href="#47" id="47">There has been some work on group coordination in this framework [14], but also here only on implicit coordination.</a>
<a href="#48" id="48">Implementing resolution operators in this framework could be both natural and useful for reasoning about group plans.</a>
</body>
</html>