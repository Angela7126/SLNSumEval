<html>
<head>
<meta name="TextLength" content="SENT_NUM:43, WORD_NUM:934">
</head>
<body bgcolor="white">
<a href="#0" id="0">Mathematical optimization relies on the availability of knowledge that can be used to construct a mathematical model for the problem at hand.</a>
<a href="#1" id="1">This knowledge is not always available.</a>
<a href="#2" id="2">For instance, in multiagent problems, agents are autonomous and often unwilling to share their local information.</a>
<a href="#3" id="3">Frequently, this autonomy and private information influence the outcome of the optimization, making finding an optimal solution very difficult.</a>
<a href="#4" id="4">In this paper, we adopt the idea of using machine learning techniques to estimate these influences for an optimization problem with many unknowns: the optimal ordering for sequential auctions (OOSA) problem.</a>
<a href="#5" id="5">We have demonstrated our approach by transforming historical auctions into data sets for learning regression trees and linear regression models, which subsequently are used to predict the expected value of orderings for new auctions.</a>
<a href="#6" id="6">We proposed two types of optimization methods with learned models, a black-box best-first search approach, and a novel white-box approach that maps learned models to integer linear programs (ILP).</a>
<a href="#7" id="7">We built an auction simulator with a set of bidder agents to simulate an auction environment.</a>
<a href="#8" id="8">The simulator was used for generating historical auction data, and for evaluating the orderings of items returned by our methods.</a>
<a href="#9" id="9">We ran an extensive set of experiments with different agents and bidding strategies.</a>
<a href="#10" id="10">Although optimizing the orderings in sequential auctions is a hard problem, our proposed methods obtained very high values, significantly outperforming the naive methods proposed in the literature.</a>
<a href="#11" id="11">The experimental results also demonstrate the advantage of using the white-box method for optimization, which significantly outperforms the black-box approach in nearly all settings.</a>
<a href="#12" id="12">In addition, they indicate that when the learned model becomes more complex, it potentially results in more constraints and consequently, an increase in the time needed to solve the problem in a white-box fashion.</a>
<a href="#13" id="13">Since more complex models are (potentially) better predictors, this shows a clear trade-off between modeling and optimization power in white-box optimization.</a>
<a href="#14" id="14">In our opinion, the benefits of the white-box approach largely outweigh the benefits of using black-box optimization.</a>
<a href="#15" id="15">Finally, the extended experiments demonstrate that although our encodings are efficient, the regression tree breaks down when the data becomes too noisy.</a>
<a href="#16" id="16">An intriguing extension would therefore be to use regression forests instead of individual trees.</a>
<a href="#17" id="17">These are known to handle noisy data much better because of the crisp boundaries in individual trees.</a>
<a href="#18" id="18">The same experiments also show that our method does not yet scale very well with the number of items, most likely due to the increase in the number of trees that need to be evaluated.</a>
<a href="#19" id="19">We expect that a method based on regression forests will therefore require several simplifications or optimizations in order to be feasible.</a>
<a href="#20" id="20">Besides an improved performance, a very big benefit of the white-box formulation is that it provides a new way of obtaining traditional mathematical models.</a>
<a href="#21" id="21">Our method therefore has many other potential application areas, especially in problems where more and more data is being collected.</a>
<a href="#22" id="22">Even in cases where there already exists a handcrafted optimization model, a model that is learned and translated using our method can easily be integrated into existing (I)LP formulations in order to determine part of the objective function based on data.</a>
<a href="#23" id="23">In this way, one can combine the vast amount of expert knowledge available in these domains with the knowledge in the readily available data.</a>
<a href="#24" id="24">We would like to investigate this combination in the future.</a>
<a href="#25" id="25">We chose a relatively simple auction model for ease of explanation in this paper.</a>
<a href="#26" id="26">However, our approach works whenever regression models are able to provide reliable predictions of the bidding values.</a>
<a href="#27" id="27">Hence we believe it can be applied to other auction formats with more complex valuation functions (i.e. combinatorial preferences [53]) and more complex bidding strategies.</a>
<a href="#28" id="28">The results of our method on the larger experiments with 80 items shows that scaling the approach up to large real-world auctions will require several non-trivial simplifications.</a>
<a href="#29" id="29">Moreover, in this paper, we learned regression trees and linear models from simulated data in order to test the optimization performance.</a>
<a href="#30" id="30">When applying our approach to real-world data, it is important to test whether the regressors assumptions are satisfied.</a>
<a href="#31" id="31">If not, it may be needed to transform or filter them.</a>
<a href="#32" id="32">We plan to discover the simplifications and test our approach with real auction data in the near future.</a>
<a href="#33" id="33">Our experiments highlight some interesting properties of the white-box method.</a>
<a href="#34" id="34">Firstly, they show an improvement in performance when the number of features is reduced and/or the models are less complex.</a>
<a href="#35" id="35">It would therefore be very interesting to investigate the effect of pruning and feature selection or reduction on the performance of our methods.</a>
<a href="#36" id="36">Secondly, they show a tendency of the regression tree optimizer to overestimate, i.e., find orderings that have a much higher expected revenue than their revenue in practice.</a>
<a href="#37" id="37">Intuitively, the solver abuses the crisp nature of the regression tree in order to find a solution that satisfies exactly the right constraints.</a>
<a href="#38" id="38">Part of the problem is that, although these constraints are learned from data, and therefore uncertain, the solver treats them as exact.</a>
<a href="#39" id="39">Fortunately, there exists a long history of methods that try to optimize in the presence of such uncertainties in the area of robust optimization, see, e.g., [54].</a>
<a href="#40" id="40">As future work, we will investigate the potential uses of these techniques for learned models.</a>
<a href="#41" id="41">Recently, regression tree models with linear models in the leaf nodes have also been successfully used as black-box surrogate functions [55].</a>
<a href="#42" id="42">Since it is also straightforward to translate these trees given our two encodings (replace the leaf variables by indicators for which linear function to use), it would be very interesting to investigate the possibility of a white-box alternative.</a>
</body>
</html>