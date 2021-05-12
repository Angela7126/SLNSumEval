<html>
<head>
<meta name="TextLength" content="SENT_NUM:39, WORD_NUM:801">
</head>
<body bgcolor="white">
<a href="#0" id="0">The information that actions carry may depend on agentsʼ knowledge of protocols.</a>
<a href="#1" id="1">In this paper we studied cases where protocols are not commonly known and proposed a semantics-driven logical framework for updating knowledge by observations based on epistemic protocols.</a>
<a href="#2" id="2">We have left a complexity analysis, for example, in line of [4], for the future.</a>
<a href="#3" id="3">Although our semantics-driven logics POL and EPL are ‘dynamic epistemic’ in spirit, the usual reduction-based completeness proof for DEL-like logics does not apply, since the dynamic operators {a mathematical formula}[π] in POL cannot be eliminated.</a>
<a href="#4" id="4">Complete axiomatizations of POL and EPL demand new techniques, pioneered in [28], [29].</a>
<a href="#5" id="5">We have partial results but we leave a systematic study to a future occasion.</a>
<a href="#6" id="6">Let us consider various other extensions of our work.</a>
<a href="#7" id="7">We only used Boolean tests in the language {a mathematical formula}Lprot.</a>
<a href="#8" id="8">A more expressive protocol language includes epistemic tests.</a>
<a href="#9" id="9">An example of such a protocol would be {a mathematical formula}(?¬Kp⋅(a+b))⁎⋅(?Kp⋅c): as long as you do not know p, keep choosing an a or b action, until you get to know p, and then do c. As observed in [30], knowledge-based protocols are much more involved than fact-based protocols.</a>
<a href="#10" id="10">Defining the interpretation and executability of such protocols is a challenge, because checking epistemic formulas is non-local.</a>
<a href="#11" id="11">Also, the introduction of knowledge tests may make the satisfiability problem of the logic undecidable.</a>
<a href="#12" id="12">For example, the observations may easily encode iterated public announcement, which is known as a source of undecidability in such logics [27].</a>
<a href="#13" id="13">On the positive side, by including more expressive tests we expect better matching between epistemic expectation models and epistemic protocols (cf.</a>
<a href="#14" id="14">Theorem 29).</a>
<a href="#15" id="15">Another extension is to consider less radical update mechanisms for installing new protocols.</a>
<a href="#16" id="16">In our current approach, when installing a new protocol, we simply ignore and overwrite the old expected observations completely.</a>
<a href="#17" id="17">Consider a singleton observation epistemic model with observation {a mathematical formula}a+c.</a>
<a href="#18" id="18">Now, when updating with the protocol {a mathematical formula}a+b we simply replace {a mathematical formula}a+c by {a mathematical formula}a+b.</a>
<a href="#19" id="19">Instead, we could integrate {a mathematical formula}a+c with {a mathematical formula}a+b, somehow.</a>
<a href="#20" id="20">For example, such a ‘non-radical’ protocol update with {a mathematical formula}a+b could result in b (intersected refinement), or in {a mathematical formula}(b+c)⋅(a+b) (concatenation), or in {a mathematical formula}(b+c)+(a+b) (choice), and so on.</a>
<a href="#21" id="21">See [15] for a discussion.</a>
<a href="#22" id="22">Finally, we could relax the assumption of public observation, for example, some actions might not be observable to certain agents.</a>
<a href="#23" id="23">It would also be interesting to relax the underlying logic and to use KD45, modeling belief, instead of S5, modeling knowledge.</a>
<a href="#24" id="24">For example, in the models of protocol updates for the story of Example 1 of the introduction (see p.</a>
<a href="#25" id="25">27), it would fit more naturally with the story if the link for Ann between the alternatives in the epistemic protocol model were uni-directional only, namely from {a mathematical formula}?g⋅a+?¬g⋅b to {a mathematical formula}a+b, plus a Jane-loop from {a mathematical formula}?g⋅a+?¬g⋅b to itself and Janeand Ann-loops from {a mathematical formula}a+b to itself, as follows.</a>
<a href="#26" id="26">{a mathematical formula}</a>
<a href="#27" id="27">This would model installing the protocol wherein Anne is unaware of the gay interpretation.</a>
<a href="#28" id="28">Currently, the model on p.</a>
<a href="#29" id="29">27 installs the possibly later observed information that Ann is uncertain whether the statement is to be interpreted as ‘Kate is gay’ or not, but she considers the option.</a>
<a href="#30" id="30">By contrast, in the actual story, Jane will only interpret a as a sure sign of ‘Kate is gay’ and b as a sign of ‘Kate is not gay’.</a>
<a href="#31" id="31">We would rather be able to model that Jane considers both the ‘Kate is gay’ and the ‘no double meaning’ interpretation of a and b, corresponding to Annʼs stance in the current model, whereas Ann only considers the ‘no double meaning’ interpretation and believes that Jane does so too.</a>
<a href="#32" id="32">The subject of hidden protocols is also interesting from the point of view of language pragmatics.</a>
<a href="#33" id="33">Speakers who intend to convey information to only some of their listeners in such a way that others will not understand what is going on, are deliberately acting against some of Griceʼs maxims of cooperative conversation [31].</a>
<a href="#34" id="34">Forms of indirect or uncooperative communication, such as veiled bribes and threats, have already been investigated from the perspective of pragmatics and cognitive science, relating them also to aspects like lack of common knowledge [32], [33], [34], [35].</a>
<a href="#35" id="35">Our analysis of hidden protocols in this paper, by distinguishing between expected observations and actions, is more fine-grained than the changes in ‘standard’ dynamic epistemic logic, but could benefit from taking such Gricean aspects into account.</a>
<a href="#36" id="36">Thus, in addition to observational powers of the agents, also their assertive powers may be modeled.</a>
<a href="#37" id="37">Finally, it would be interesting to investigate the role of the interlocutorsʼ goals and intentions when they utter a veiled speech act that is part of a hidden protocol (cf.</a>
<a href="#38" id="38">[36], [37], [38], [39]).</a>
</body>
</html>