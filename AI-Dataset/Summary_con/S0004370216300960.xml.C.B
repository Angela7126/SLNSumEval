<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:240">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we discussed the theory of regression, developing it as a practical tool for online belief tracking in contingent domains, showing that it enjoys potentially better worst-case theoretical guarantees than FBT.</a>
<a href="#1" id="1">We evaluated the use of regression empirically, showing that it scales up very well on many current contingent benchmark domains.</a>
<a href="#2" id="2">Regression over actions naturally enjoys a focus on relevant variables only, and over observations, too, if their regression is conjoined to the initial state.</a>
<a href="#3" id="3">As regression takes a lazy approach, constructing formulas during queries, it may not be as beneficial for planners that require many queries.</a>
<a href="#4" id="4">Repeatedly checking the precondition validity of a large set of actions may well be less efficient using regression than using a DBN [17] or FBT.</a>
<a href="#5" id="5">The success of approximate FBT and CBT techniques points to potentially interesting line of future work focusing on approximate regression methods.</a>
<a href="#6" id="6">For example, by possibly weakening the regression formula in some cases and maintaining a simple syntactic form, one might be able to reduce its computational cost in practice, at the price of some loss of completeness.</a>
<a href="#7" id="7">In addition, it may be possible to combine ideas from CBT and regression to obtain a hybrid method, where the information maintained by CBT would be used to simplify the regression formula, or even to refrain from using it when the condition is already implied by the maintained belief state, while regression will ensure the completeness of the approach.</a>
</body>
</html>