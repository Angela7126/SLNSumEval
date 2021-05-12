<html>
<head>
<meta name="TextLength" content="SENT_NUM:37, WORD_NUM:923">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we introduced the expert crowdsourcing problem with variable worker performance, heterogeneous costs and task limits per worker.</a>
<a href="#1" id="1">In this problem, an employer wishes to assign tasks within a limited budget to a set of workers such that its total utility is maximised.</a>
<a href="#2" id="2">To solve this problem, we introduced a new MAB model, the bounded MAB, with a limited number of pulls per arm to represent task limits.</a>
<a href="#3" id="3">Given this, we proposed a simple, but efficient, bounded ε-first-based algorithm that uses a uniform pull strategy for exploration, and a bounded knapsack-based approach for exploitation.</a>
<a href="#4" id="4">We proved that this algorithm has an {a mathematical formula}O(B23) theoretical upper bound for its performance regret.</a>
<a href="#5" id="5">This result means that our algorithm has the desirable zero-regret property, implying that the algorithm asymptotically converges to the optimal solution as the budget tends to infinity.</a>
<a href="#6" id="6">To establish the performance of our algorithm in realistic expert crowdsourcing settings, we also applied it to real data from oDesk, a prominent expert crowdsourcing website.</a>
<a href="#7" id="7">We showed that the algorithm consistently outperforms state-of-the-art crowdsourcing algorithms within this domain by up to {a mathematical formula}300%, also achieving up to {a mathematical formula}95% of a hypothetical optimal benchmark that has full information about the workers' performance distributions.</a>
<a href="#8" id="8">Furthermore, the empirical results confirmed our theoretical bounds, indicating that the algorithm works best for projects with large budgets.</a>
<a href="#9" id="9">As a result, our work could potentially form a promising basis to crowdsourcing websites which aim to provide efficient teams of experts.</a>
<a href="#10" id="10">We envisage that it could be used to automate the formation of curated crowds, which are currently mostly formed on an ad hoc basis (see Section 2.1).</a>
<a href="#11" id="11">In particular, our algorithm could be employed to implement a crowdsourcing intermediary, which, given a customer's budget for a project, automatically explores a potential crowd of workers and then assembles a promising team of the best performers.</a>
<a href="#12" id="12">In addition to this, our work also constitutes a general contribution to the field of MABs and is applicable to a wide range of decision-making problems under uncertainty beyond the domain of expert crowdsourcing.</a>
<a href="#13" id="13">In more traditional labour markets, our approach could be used to hire unknown contractors to work on a large project, or it could be used to allocate existing workers within a company to a new project (where costs are incurred by removing workers from their day jobs and performance may be unknown if no similar projects have been carried out in the past).</a>
<a href="#14" id="14">Another potential application of our work is cloud computing, where services are potentially unreliable or vary in their quality, and where the maximum number of jobs on one service is restricted either by a fixed deadline or by user quotas.</a>
<a href="#15" id="15">Finally, our work applies generally to resource allocation problems with costly but limited resources of an unknown quality.</a>
<a href="#16" id="16">For example, a government may need to procure medicines to fight a new epidemic, but it is uncertain what medicines work best and it is restricted by budget constraints and stock levels of the medicines.</a>
<a href="#17" id="17">Currently, our work also has a number of limitations that we will explore further in future work.</a>
<a href="#18" id="18">First, our approach does not exploit the fact that in many real-world applications employers typically have additional information about the applicants, which could be used to find the best workers more quickly (e.g., reputation ratings or lists of qualifications).</a>
<a href="#19" id="19">However, as this information might not be accurate either, it is not trivial how to efficiently handle it in practice.</a>
<a href="#20" id="20">One possible way is to maintain belief-based models for each user's profile, which measures the uncertainty of our knowledge about the user, based on current observations.</a>
<a href="#21" id="21">These belief models are then iteratively updated as we observe the utility values from the users while assigning tasks to them.</a>
<a href="#22" id="22">Our model, however, does not currently handle such belief updates.</a>
<a href="#23" id="23">Thus, as possible future work, we intend to extend our analysis to these settings.</a>
<a href="#24" id="24">Our current work also assumes that a particular worker's performance is static, that is, it is drawn from a stationary distribution.</a>
<a href="#25" id="25">However, it may be the case that due to external reasons (e.g., health and weather conditions, or other duties), the performance distribution may vary over time.</a>
<a href="#26" id="26">The bounded ε-first algorithm might fail to tackle these settings, as it is not capable of handling dynamic environments.</a>
<a href="#27" id="27">In particular, due to the explicit split of exploration from exploitation, our algorithm might not be able to detect future changes once the exploration phase is completed.</a>
<a href="#28" id="28">One possible way to extend our model is to use bandit algorithms that do not split exploration from exploitation, such as UCB or ε-greedy (for more details, see [30], [32]).</a>
<a href="#29" id="29">However, these algorithms are not designed for the bounded multi-armed bandit model, and thus, it is not trivial how to extend them to our settings.</a>
<a href="#30" id="30">Given this, we also aim to extend our proposed algorithm to systems with dynamic behaviour.</a>
<a href="#31" id="31">Furthermore, our model considers independent tasks, where the total utility of the tasks is the sum of each individual task's utility.</a>
<a href="#32" id="32">However, tasks may affect each other's value, and thus, the total utility of these tasks may not be equal to their sum of utility.</a>
<a href="#33" id="33">For example, two tasks may contain overlapping parts.</a>
<a href="#34" id="34">This implies that their total utility is less than their sum.</a>
<a href="#35" id="35">In contrast, two other tasks might complement each other, boosting each other's value if both are completed (i.e., their total utility is higher than their sum).</a>
<a href="#36" id="36">As our algorithm is currently not designed to address this setting, we intend to extend our model to this scenario as well.</a>
</body>
</html>