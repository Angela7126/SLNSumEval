<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:438">
</head>
<body bgcolor="white">
<a href="#0" id="0">Many real-world applications, such as robotics, have to deal with numerous sources of uncertainty, the main culprit being sensor noise.</a>
<a href="#1" id="1">Probabilistic error models have proven to be essential in state estimation, allowing the beliefs of a robot to be strengthened over time.</a>
<a href="#2" id="2">But to use these models, the modeler is left with the difficult task of deciding how the domain is to be captured in terms of random variables, and shifting conditional independences and distributions.</a>
<a href="#3" id="3">In the BHL model, one simply provides a specification of some initial beliefs, characterizes the physical laws of the domain, and suitable posterior beliefs are entailed.</a>
<a href="#4" id="4">The applicability of BHL was limited, however, by its inability to handle continuous distributions, a limitation we lift in this article.</a>
<a href="#5" id="5">By recasting the assessment of belief in terms of fluent values, we now seamlessly combine the situation calculus with discrete probability distributions, densities and difficult combinations of the two.</a>
<a href="#6" id="6">We demonstrated that distributions evolve appropriately after actions, emerging as a side-effect of the general specification.</a>
<a href="#7" id="7">Our formal framework was then shown to easily accommodate the interaction between discrete and continuous fluents, discrete and continuous noise models, and logical connectives.</a>
<a href="#8" id="8">At a specification level, the framework provides the necessary bridge between logic-based action formalisms and probabilistic ones.</a>
<a href="#9" id="9">Armed with this general specification language, we are in a position to investigate specialized reasoning machinery.</a>
<a href="#10" id="10">To give a few examples, in [35], [84], we identified general projection techniques, where we transform a property of belief after a sequence of (noisy) actions and observations to what is believed initially.</a>
<a href="#11" id="11">In later work [85], we provided an efficient implementation of a projection technique under some reasonable assumptions, in service of enabling richer domain axiomatizations for robotics applications.</a>
<a href="#12" id="12">Finally, a version of Golog was recently embedded in our model of belief [26], in the style of knowledge-based programming [10], [86].</a>
<a href="#13" id="13">A major criticism leveled at much of the work in cognitive robotics [87], and logic-based knowledge representation more generally is that the languages are far removed from the kind of uncertainty and noise seen in machine learning and robotics applications.</a>
<a href="#14" id="14">A formal language such as the one considered in this article addresses this concern.</a>
<a href="#15" id="15">It also shows the advantages of appealing to logical machinery: firstly, in admitting natural, rich and intuitive physical laws; secondly, in allowing belief specifications that can exploit the full power of logical connectives, thereby going considerably beyond standard probabilistic formalisms; and thirdly, in alleviating the burden of determining how these probabilistic beliefs are affected in dynamical systems.</a>
<a href="#16" id="16">In the long term, we hope it takes steps towards a general-purpose epistemologically-adequate representation language as envisioned by McCarthy and Hayes.</a>
</body>
</html>