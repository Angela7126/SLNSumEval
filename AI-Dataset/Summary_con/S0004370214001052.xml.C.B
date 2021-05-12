<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:836">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we present the ICARUS framework, a powerful tool for expressing information capture and reuse enhancements in MCTS.</a>
<a href="#1" id="1">The ICARUS framework is expressive enough to enable all existing MCTS enhancements to be defined and provides a new tool for discovery of novel types of enhancement.</a>
<a href="#2" id="2">ICARUS provide a consistent method for expressing how an MCTS enhancement captures and reuses information, enabling us to easily analyse similarities and differences between enhancements and define composition operators which are compatible with all ICARUSes.</a>
<a href="#3" id="3">We have presented information capture and reuse as the principles upon which all general purpose enhancements to MCTS are based, and separated the mechanisms for capture and reuse as a tool for understanding existing enhancements and designing new ones.</a>
<a href="#4" id="4">We found the ε-greedy and UCB1 algorithms to be particularly effective at balancing the exploration and exploitation of moves during MCTS simulations.</a>
<a href="#5" id="5">Considering which states map to which records during playout and backpropagation gives a clear indication as to which parts of the tree share information.</a>
<a href="#6" id="6">We conjecture that the effectiveness of information capture is determined by the degree of correlation of state values in these regions of the underlying game tree.</a>
<a href="#7" id="7">In Section 6 we discussed how the effectiveness of these enhancements can be explained in the context of sharing information between states.</a>
<a href="#8" id="8">We developed the EPIC enhancement within the ICARUS framework by considering the notion of episodes, which turns out to generalise readily to several other games.</a>
<a href="#9" id="9">Using episodes based on the episodic structure of each game proved to be effective across our test domains.</a>
<a href="#10" id="10">Many games have a natural episodic nature and EPIC may prove to be useful in exploiting this.</a>
<a href="#11" id="11">MAST, LGR and NAST may be viewed as techniques which reuse information based on short episodes, of length 1 for MAST, length 2 for LGR, and arbitrary fixed length {a mathematical formula}n≥1 for NAST.</a>
<a href="#12" id="12">The fact that NAST with {a mathematical formula}n=2 performs at least as well as EPIC in our experiments suggests that, for the games studied here, the choice of episode does not require careful injection of knowledge.</a>
<a href="#13" id="13">This is unlikely to be true for all games.</a>
<a href="#14" id="14">The enhancements we consider are general purpose, in the sense that they can be applied to any game without injection of knowledge.</a>
<a href="#15" id="15">RAVE, MAST, LGR and NAST are general purpose; strictly speaking EPIC is not, but the degree of domain knowledge required is small.</a>
<a href="#16" id="16">General purpose enhancements are useful tools for tackling new domains where expert knowledge is not available, and essential for domains such as General Game Playing where input of external knowledge is not possible.</a>
<a href="#17" id="17">No general purpose enhancement has yet been discovered that is beneficial in all domains, and the existence of such an enhancement seems unlikely, but some are more robust than others: even in domains where they provide no clear benefit, they are usually not detrimental.</a>
<a href="#18" id="18">Robustness is an essential criterion in choosing a general purpose enhancement.</a>
<a href="#19" id="19">We have demonstrated for our test domains that MAST, LGR, NAST and EPIC are robust while RAVE is not.</a>
<a href="#20" id="20">The ICARUS framework enables combination operators for enhancements to be defined, with the strongest play often coming from a combination of enhancements.</a>
<a href="#21" id="21">One possible direction for future work is to develop more robust composition operators, for example ones based on majority voting rather than weighted sums, effectively adopting an ensemble approach to enhancement combination.</a>
<a href="#22" id="22">We have also shown that enhancements designed for perfect information games can be effective in imperfect information games, despite the increased level of uncertainty and sparsity of search.</a>
<a href="#23" id="23">Current MCTS enhancements do not explicitly address information asymmetry and stochasticity in games.</a>
<a href="#24" id="24">However we could define new ICARUSes that consider information asymmetry in information capture, for example by sharing information between states that are distinguishable to a player but indistinguishable to their opponent.</a>
<a href="#25" id="25">The MCTS algorithm is also easily parallelisable [78], which suggests a new class of enhancements that capture information in one search thread and reuse it in others running concurrently.</a>
<a href="#26" id="26">This would require modification of Algorithm 1 to perform a multithreaded variant of MCTS, and locking mechanisms to ensure the same record is not updated while another thread is reading or updating it, but otherwise ICARUS enhancements could be used without modification.</a>
<a href="#27" id="27">In future work we plan to investigate the automation of designing and choosing enhancements for a particular game, and ICARUS provides a framework for doing this.</a>
<a href="#28" id="28">For example, we could directly measure the correlation between different areas of the tree and use this information to select the most appropriate enhancements from a predefined library.</a>
<a href="#29" id="29">This could be done offline before the search begins, or online to dynamically activate and deactivate enhancements as the search progresses.</a>
<a href="#30" id="30">Additionally, we can automatically discover new enhancements using evolutionary techniques; the ICARUS framework could give a compact yet expressive representation for genetic programming or other evolutionary algorithms.</a>
<a href="#31" id="31">This kind of dynamically self-enhancing system combined with MCTS would take us several steps further towards a truly general purpose AI system for acting in challenging games and complex sequential decision problems.</a>
</body>
</html>