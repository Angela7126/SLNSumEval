<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:528">
</head>
<body bgcolor="white">
<a href="#0" id="0">An intelligent, autonomous, and interactive agent or robot should learn to solve different tasks in different environments.</a>
<a href="#1" id="1">An intelligent agent should focus attention on the most relevant task and environmental features for problem solving.</a>
<a href="#2" id="2">An intelligent agent should also retain or store the knowledge learned in previous tasks, and “understands” if, how, and when the learned knowledge can be effectively used in new situations.</a>
<a href="#3" id="3">Toward these objectives, we have presented a framework for learning and transferring multiple expectations or views about world dynamics in heterogeneous environments.</a>
<a href="#4" id="4">Unlike most existing efforts, the proposed framework is scalable as it does not assume fixed actions to be taken or constant environmental features, nor does it require accurate mapping functions to be defined across different tasks or environments.</a>
<a href="#5" id="5">The framework can work with very little or no data available in the tasks or environments, which is a major challenge in transfer learning in both static and dynamic domains.</a>
<a href="#6" id="6">When the environments are different, the combination of learning multiple views and dynamically selecting the most promising ones yields a system that can learn a good policy faster and gain higher accumulated reward as compared to the common strategy of learning just a single good model and using it on all occasions.</a>
<a href="#7" id="7">Applying and maintaining multiple models require additional computation and memory.</a>
<a href="#8" id="8">We have shown that by a clever decomposition of the transition function, model selection and model updating can be accomplished efficiently using online algorithms.</a>
<a href="#9" id="9">Our experiments have shown that performance improvements in multi-dimensional, heterogeneous environments can be achieved with a small computational cost.</a>
<a href="#10" id="10">In addition, we have demonstrated how online multinomial logistic regression with group lasso can be used to quickly obtain a parsimonious transition model in model based RL.</a>
<a href="#11" id="11">The method leads to fast learning since a single transition model can be learned using samples from all the states with a small set of features.</a>
<a href="#12" id="12">The efficiency is gained, however, at the expense of losing generality.</a>
<a href="#13" id="13">Not all transition functions can be accurately represented as predicting action effects using state features via logistic regression.</a>
<a href="#14" id="14">Nevertheless, we believe that this compromise between scalability and generality is often a useful one.</a>
<a href="#15" id="15">The generality problem may also be alleviated by introducing non-linear features that are combinations of the original ones.</a>
<a href="#16" id="16">Other generalizations such as stochastic features and vector valued effects are also possible but are left for future work.</a>
<a href="#17" id="17">The current work addresses the question of learning good models, but the problem of learning good policies in large state spaces still remains.</a>
<a href="#18" id="18">Our model learning method is independent of the policy learning task, thus it can well be coupled with any scalable approximate policy learning algorithms.</a>
<a href="#19" id="19">There are still many open problems and assumptions to address, yet this study has provided some insights for future research and development.</a>
<a href="#20" id="20">The proposed transfer learning framework would serve as a base intelligent agent platform for monitoring, problem solving, and general decision support in heterogeneous, dynamic environments.</a>
<a href="#21" id="21">We envision that this platform can be integrated with the latest agent-based or environmental sensors, navigation and localization functions, and higher level cognitive capabilities such as activity recognition, speech understanding, and decision making to develop a new generation of human-interactive robots.</a>
</body>
</html>