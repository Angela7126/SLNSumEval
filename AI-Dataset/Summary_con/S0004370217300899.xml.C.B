<html>
<head>
<meta name="TextLength" content="SENT_NUM:33, WORD_NUM:990">
</head>
<body bgcolor="white">
<a href="#0" id="0">Acyclicity is a highly desirable property of games, as it means that the agents will reach a deterministic stable state (equilibrium), even if they act myopically with little knowledge and coordination.</a>
<a href="#1" id="1">It is particularly useful in the analysis and design of voting mechanisms: allowing voters to freely modify their votes will let them reach an equilibrium regardless of their initial votes and the information about other voters' preferences.</a>
<a href="#2" id="2">Importantly, in the context of voting such myopic dynamics define a natural and straightforward process, which, coupled with the convergence properties demonstrated in this paper, makes it an attractive candidate method for predicting human voter behavior in elections and designing artificial agents with strategic voting capabilities—two of the most important, and also the hardest, goals of social choice research.</a>
<a href="#3" id="3">The outcome of such voting processes can be thought of as compromise reached by means of an iterative game—the agents might start voting for their favorites, but looking at the current scores, might like to compromise and support less preferred candidates if they (unlike the top choice candidates) have more chances to win the election.</a>
<a href="#4" id="4">Importantly, recent theoretical and empirical work demonstrates that these compromise outcomes are never much worse than the truthful Plurality outcome, and are often significantly better according to Condorcet efficiency, voters' social welfare and other metrics [32], [33], [34].</a>
<a href="#5" id="5">These findings, together with our convergence results, thus suggest that online voting platforms such as Doodle and Facebook should enable and maybe even encourage their users to look at current candidates' scores and update their votes dynamically, as this would guarantee both stable and socially desirable outcome.</a>
<a href="#6" id="6">Beyond the direct implication of various acyclicity properties on interactive settings where agents vote one by one, strong/weak acyclicity is tightly linked to convergence properties of more sophisticated learning strategies in repeated games [57], [58], which gives another reason to understand them.</a>
<a href="#7" id="7">However, while there exist some broad classes of acyclic games (with congestion/potential games being probably the best known representative), there are not many natural game forms that demonstrate acyclicity [7].</a>
<a href="#8" id="8">To this end, Fabrikant et al. [18] provide a sufficient condition for weak acyclicity, namely that any subgame contains a unique Nash equilibrium; another sufficient condition due to Apt and Simon [8] is by eliminating never-best reply strategies.</a>
<a href="#9" id="9">Unfortunately, both these criteria are not applicable to most voting rules, where typically (at least) all unanimous votes form equilibria, and every strategy is a best reply to some joint vote of the others.</a>
<a href="#10" id="10">In this work, we focus on the common Plurality voting rule and show that it has the desired acyclicity property: natural better reply dynamics guarantees that voters will converge to an equilibrium, while the exact conditions under which this will occur may depend on the tie-breaking method.</a>
<a href="#11" id="11">A key insight for these results is the identification of direct replies—a natural restriction on voters' actions that might be generalized to other voting rules.</a>
<a href="#12" id="12">Moreover, we provide a joint rigorous framework for the study of iterative voting, as part of the broader literature on acyclicity of games and game forms, which allows us to compare all known convergence results from the literature, and derive some new entailments.</a>
<a href="#13" id="13">In particular, we demonstrate variations of Plurality that are weakly acyclic but not order-free acyclic, thereby settling an open question on whether such game forms exist [7].</a>
<a href="#14" id="14">We summarize all known results on iterative voting that we are aware of in Table 3, Table 4.</a>
<a href="#15" id="15">Note that in some cases we get positive results if we restrict the initial state, the number of voters, or some other parameter (not shown in the table).</a>
<a href="#16" id="16">For Plurality we provide a more detailed picture in Fig. 8, Fig. 9.</a>
<a href="#17" id="17">The tables also visualize which questions are still open (mainly for rules other than Plurality).</a>
<a href="#18" id="18">We added a short reminder for the meaning of the various notions of convergence in Table 2.</a>
<a href="#19" id="19">Note that previous papers whose results are covered in the tables often use different terminology and thus theorems and examples need to be rephrased (and sometimes slightly modified) to be directly comparable.</a>
<a href="#20" id="20">These rephrasing and necessary modifications are explained in detail in [56].</a>
<a href="#21" id="21">Based on the progress made in this paper and the other results published since the introduction of iterative voting in [1], we believe that research on iterative voting should focus on three primary directions:</a>
<a href="#22" id="22">Weak acyclicity seems more indicative than order-free acyclicity to determine convergence in practice.</a>
<a href="#23" id="23">Thus, theorists should study which voting rules are weak-FIP, perhaps under reasonable restrictions (as we demonstrated, this property is distinct from order-free-FIP).</a>
<a href="#24" id="24">We highlight that even in rules where there are counter-examples for weak acyclicity (k-approval, Borda), these examples use only two voters, and games with more voters may well be weakly acyclic.</a>
<a href="#25" id="25">It is important to experimentally study how people really vote in iterative settings (both in and out of the lab), so that this behavior can be formalized and behavioral models can be improved.</a>
<a href="#26" id="26">The work of [60] is a preliminary step in this direction, but there is much more to learn.</a>
<a href="#27" id="27">Ideally, we would like to identify a few types of voters, such that for each type we can relatively accurately predict the next action in a particular state.</a>
<a href="#28" id="28">It would be even better if these types are not specific to a particular voting rule or contextual details.</a>
<a href="#29" id="29">We would like to know not only if a voting rule converges under a particular dynamics (always or often), but also what are the properties of the attained outcome—in particular, whether the iterative process improves welfare or fairness, avoids “voting paradoxes” [61], and so on.</a>
<a href="#30" id="30">Towards this end, several researchers (e.g., [32], [34], [35], [36], [37]) have started to explore these questions via theory and simulations.</a>
<a href="#31" id="31">However, a good understanding of how iterative voting shapes the outcome, whether the population of voters consists of humans or artificial agents, is still under way.</a>
<a href="#32" id="32">We hope that this paper will help in focusing and classifying future work.</a>
</body>
</html>