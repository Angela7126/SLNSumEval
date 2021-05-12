<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:614">
</head>
<body bgcolor="white">
<a href="#0" id="0">Negotiation is the science and art of resolving disputes and reaching consensus between human parties.</a>
<a href="#1" id="1">Automated bilateral multi issue negotiations are a special kind of traditional negotiations where two intelligent automated negotiating agents undertake the task of making an agreement on multiple issues on behalf of their human clients.</a>
<a href="#2" id="2">Each automated negotiating agent strategy can be of the following subcomponents [1]: (1) Opponent Modeling, (2) Bidding Strategy, and (3) Acceptance Strategy.</a>
<a href="#3" id="3">Thus, the negotiation strategy could be thought of as a larger component, which embodies the aforementioned subcomponents, and manages an efficient collaboration and interaction between them to accomplish the whole negotiation task.</a>
<a href="#4" id="4">Opponent modeling techniques, as one of the constituent components of a negotiation strategy, are highly contributive in the success of a negotiating agent, in terms of both obtaining better individual utilities and achieving higher social welfare values.</a>
<a href="#5" id="5">Therefore they are widely studied in the literature of Automated Negotiations.</a>
<a href="#6" id="6">In this article, a new technique is proposed based on perceptron units, called POPPONENT, in order to model the preferences of the opponent in bilateral multi issue negotiations with linear utility functions.</a>
<a href="#7" id="7">In fact, POPPONENT is a very successful implementation of a generalized version of the Standard Gradient Descent search algorithm (GD), referred to as the Multi Bipartite Gradient Descent search (MBGD) in a practical AI problem.</a>
<a href="#8" id="8">The performance of the POPPONENT model is compared with the state of the art models from the Genius repository [36], [37].</a>
<a href="#9" id="9">The POPPONENT is evaluated in 5 separate states which include the perfect information state (PP), the constant value states (with constant values of 0.6 (P6), 0.8 (P8), 1 (P1)), and the Adaptive state (AP).</a>
<a href="#10" id="10">In the perfect information state, it is revealed that this outperforms the state of the art models in average accuracy by a large margin, when the accuracy is measured over all opponents including predictable (conceding opponents), unpredictable, random, conceding opponents with an offset, and non-conceding.</a>
<a href="#11" id="11">It is found in the experiments that the accuracy of POPPONENT (in all the three constant value states) exceeds the accuracy of the most accurate state of the art model against all opponents in average and most other scenarios.</a>
<a href="#12" id="12">Evaluating the performance of POPPONENT through Genius indicates that it overcomes the most accurate state of the art opponent models.</a>
<a href="#13" id="13">The results indicate that POPPONENT overcomes all the state of the art models in at least one domain for all the performance/accuracy measures.</a>
<a href="#14" id="14">In Experiment I, three constant values (together with perfect information) are applied to estimate the utility of a received bid in the opponent's utility space.</a>
<a href="#15" id="15">In Experiment II, an adaptive method is applied to estimate the bidding behavior of the opponent.</a>
<a href="#16" id="16">It is believed that there is still a possibility for more improvements in accuracy and performance through adaptive methods.</a>
<a href="#17" id="17">In the future, we plan to work further on the estimation of the opponent bids utilities, to design and implement highly efficient adaptive methods in order to estimate bid utilities through the history of bids which are received from the opponent in an incremental manner, and to evaluate the accuracy of this model while employing such adaptive methods.</a>
<a href="#18" id="18">Another interesting future study direction would be the evaluation of this proposed model through different parameter values (i.e. learning rate, number of repeats, etc.).</a>
<a href="#19" id="19">It is unknown how the accuracy and performance of this model is affected by the changes made to its parameters, and whether the model accuracy and performance could be further improved with proper parameter values.</a>
<a href="#20" id="20">POPPONENT is a successful implementation of this new search method, with MBGD in the area of preference modeling automated negotiations.</a>
<a href="#21" id="21">We are interested in the applicability of this new method to other practical areas of Artificial Intelligence.</a>
</body>
</html>