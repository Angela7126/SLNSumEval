<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:484">
</head>
<body bgcolor="white">
<a href="#0" id="0">Any solution to the problem of interactive shaping—i.e., learning sequential tasks from human-generated reward—requires the definition of a reward-based objective and an agent algorithm.</a>
<a href="#1" id="1">This article examines the relationship between reward discounting rates, episodicity, reward positivity, acting approximately MDP-optimally or not, and the ultimate objective, task performance.</a>
<a href="#2" id="2">These relationships are examined in six experiments across two domains.</a>
<a href="#3" id="3">The table in Fig. 22 summarizes our findings.</a>
<a href="#4" id="4">We note the following contributions in this article:</a>
<a href="#5" id="5">identifying and ultimately giving sufficient justification for the myopic trend in past work on learning from human reward; linking human reward positivity to positive circuits and empirically establishing positive circuits' prevalence; adding structure to the body of past work on learning from human reward by framing and comparatively analyzing the impact on task performance of temporal discounting, whether the task is experienced as episodic or continuing, and other factors; empirically finding that for approximately MDP-optimal agents, converting the otherwise episodic grid-world task to a continuing task (a) enables successful training at non-myopic discount rates, (b) removes negative correlations between reward positivity and discount factor values, and (c) removes negative correlations between reward positivity and task performance within non-myopic conditions; achieving the first known instance of consistently successful training of a non-myopic agent by live, human-generated reward signals; demonstrating that successfully trained agents with non-myopic objectives learn higher-level task information, making them more robust to changes in their environments and better able to act from states in which they lack experience; and showing that when the agent's MDP-based performance is worsened—as it must be for complex tasks—by the common practice of locally biased learning, task performance worsens significantly in continuing tasks.</a>
<a href="#6" id="6">This article also presents a contribution from a broader perspective.</a>
<a href="#7" id="7">The work herein—an in-depth case study on adapting a machine learning problem to include human interaction—clearly indicates that machine learning algorithms generally cannot be applied with naive hopes that the human will conform to the assumptions of the algorithms.</a>
<a href="#8" id="8">Rather, the human element must be explicitly investigated.</a>
<a href="#9" id="9">This article represents substantial progress in the effort to create effective algorithms for learning from human-generated reward.</a>
<a href="#10" id="10">We note, however, that more analysis is required to establish the generality of our observations.</a>
<a href="#11" id="11">Changing the reward-giving interface, the mapping of reward cues (e.g. keys) to scalar values, the instructions to trainers, our algorithmic choices, and the task to be learned—though all carefully chosen to avoid overt bias—might create qualitatively different results.</a>
<a href="#12" id="12">From this research, we believe that the greatest future contributions of learning from human reward will come from non-myopic objectives and will likely be in continuing tasks.</a>
<a href="#13" id="13">However, we expect that naively designed agents with biases towards local updates—agents often well-suited for complex tasks—will ineffectively learn from human reward even in continuing tasks; the problems of reward positivity extend beyond episodic tasks.</a>
<a href="#14" id="14">Identifying algorithms that learn non-myopically from human-generated reward in complex domains—where approximately MDP-optimal behavior will likely be impossible—remains a critical research question.</a>
</body>
</html>