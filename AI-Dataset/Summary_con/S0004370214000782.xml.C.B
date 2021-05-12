<html>
<head>
<meta name="TextLength" content="SENT_NUM:35, WORD_NUM:799">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented a formal dialogue model for assumption-based argumentation (ABA) [7], [12], [40].</a>
<a href="#1" id="1">We use ABA for the representation of arguments and attacks and for determining “success” of dialogues.</a>
<a href="#2" id="2">ABA is well-suited as a foundation for argumentation-based dialogues since it is a general purpose, structured argumentation framework with several applications (e.g. see [12], [40]), well-understood theoretically (e.g. as an instance of other argumentation frameworks, notably abstract argumentation [15], [40]) and ASPIC+ [34], and equipped with provably correct computational mechanisms with respect to several semantics [14], [15], [41] that we rely upon in order to prove our formal soundness results.</a>
<a href="#3" id="3">We proved that our model is sound by connecting it with the admissibility, grounded and ideal argumentation semantics for ABA.</a>
<a href="#4" id="4">Thus, our dialogues can be seen as a distributed mechanism for computing admissible, grounded and ideal extensions (supporting claims) of argumentation frameworks while these are generated/jointly constructed.</a>
<a href="#5" id="5">Our dialogue model has two main advantages:</a>
<a href="#6" id="6">Our dialogues meet soundness criteria with respect to different argumentation semantics, obtained by lifting soundness results for the underlying argumentation framework, ABA;</a>
<a href="#7" id="7">Our model is not tailored to any dialogue type.</a>
<a href="#8" id="8">Indeed, it is generic and flexible as it is composed of many loosely coupled components (i.e., legal-move and outcome functions) that can be freely combined to construct dialogues with different aims and of different types.</a>
<a href="#9" id="9">We have assumed that agents exchange their views in ABA-format, namely ABA serves as a standard for the exchange of information between agents.</a>
<a href="#10" id="10">However, agents may adopt an internal representation different from ABA.</a>
<a href="#11" id="11">Our dialogue model relies upon several legal-move functions and outcome functions.</a>
<a href="#12" id="12">Table 7 summarises the main kinds of dialogues we have defined with these legal-move and outcome functions, as well as the core properties they enjoy.</a>
<a href="#13" id="13">Our work opens several avenues for future research, as follows.</a>
<a href="#14" id="14">We have focused on soundness results only, and ignored the important issue of completeness.</a>
<a href="#15" id="15">Completeness results for dispute derivations for ABA in [15], [41] are a useful starting point for studying the completeness of our dialogues.</a>
<a href="#16" id="16">Our model for argumentation-based dialogues has very clear formal properties, thanks to the use of ABA and leveraging formal results for its computational counterparts.</a>
<a href="#17" id="17">It would be interesting to see whether the model could be modified and/or extended to support argumentation dialogue with respect to other types of structured argumentation.</a>
<a href="#18" id="18">This may require the need for additional utterances, e.g., in the case of ASPIC+ [34], conveying preferences by an agent of one rule over another.</a>
<a href="#19" id="19">We have only considered two agents, for simplicity.</a>
<a href="#20" id="20">We believe that our model naturally generalises to several agents.</a>
<a href="#21" id="21">Indeed, debate trees and forests are completely neutral as to which agent plays the (fictitious) role of proponent and opponent, and focus instead on the content of utterances.</a>
<a href="#22" id="22">This generalisation would require extending the turn-making function to accommodate several agents, allowing, in particular, for agents to play different roles within the same dialogue (e.g. in the case of inquiry [43]) or to stick to a specific role (e.g. in the case of persuasion [43]) and form coalitions (for and against acceptability of the dialogue claim).</a>
<a href="#23" id="23">We plan to study this generalisation in the future, taking into account the challenges raised in the literature [10].</a>
<a href="#24" id="24">We have focused on three semantics for ABA (although some other semantics, of preferred and complete extensions, are accommodated for free, as we discuss at the end of Section 6).</a>
<a href="#25" id="25">It would be interesting to consider other semantics, e.g. that of stable extensions [11], [7].</a>
<a href="#26" id="26">For simplicity we have restricted dialogues to be patient, but non-patient dialogues could also be used to guarantee successful dialogues.</a>
<a href="#27" id="27">The soundness results for i-successful dialogues are obtained in a semi-constructive manner, by checking that opponent arguments in debate trees do not belong to admissible sets in the ABA framework drawn from the dialogue.</a>
<a href="#28" id="28">It would be useful to be able to check this condition using dialogues in turn, e.g. inspired by the notion of Fail-dispute derivation in [15].</a>
<a href="#29" id="29">We have focused on dialogues that generate flat ABA frameworks.</a>
<a href="#30" id="30">It would be interesting to see whether the model could be generalised to the case of non-flat ABA frameworks, and in particular to deal with settings where agents may disagree on whether a sentence is an assumption or not.</a>
<a href="#31" id="31">Future work also includes applying our dialogue framework to various dialogue types, e.g., negotiation and deliberation, following the lines of [17], [18], [19], [20], and extending our framework to model sequences of dialogues.</a>
<a href="#32" id="32">Although these initial attempts show promise in the deployment of our general model, much work is required to explore this challenge in full.</a>
<a href="#33" id="33">An interesting question, for example, is whether all forms of deliberation as discussed in [28] can indeed be supported and/or accommodated.</a>
<a href="#34" id="34">Finally, it would be interesting to see how our framework can be applied in human-agent dialogical interactions.</a>
</body>
</html>