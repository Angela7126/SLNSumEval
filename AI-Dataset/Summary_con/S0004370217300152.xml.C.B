<html>
<head>
<meta name="TextLength" content="SENT_NUM:47, WORD_NUM:1300">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we discussed the problem of interactively eliciting the parameters of a Choquet integral in the context of multicriteria decision-making.</a>
<a href="#1" id="1">We presented how an interactive elicitation approach can be applied to the following problems: recommending a single alternative to a decision maker (choice problems), producing a ranking of top-k alternatives (ranking problems) and assigning alternatives to a number of ordered categories (sorting problems).</a>
<a href="#2" id="2">We have adopted the minimax regret approach of Boutilier et al. [29] allowing robust recommendations under uncertainty with guarantees with respect to the worst-case loss, and formalized ranking and sorting problems in terms of regret.</a>
<a href="#3" id="3">Using minimax regret in combination with a utility model based on a Choquet integral poses a number of technical difficulties; these are related to the number of parameters needed to characterize a Choquet capacity and the number of constraints required to characterize the space of admissible capacity functions.</a>
<a href="#4" id="4">We have shown that, assuming that preferences are stated in a particular form (involving a binary alternative of type 1A0 and a constant utility profile of type {a mathematical formula}Λ=(λ,…,λ)), minimax regret optimizations can be performed efficiently in various settings (choice, ranking, sorting): we presented both a linear programming formulation and an even faster iterative algorithm maintaining lower and upper bounds.</a>
<a href="#5" id="5">We presented experimental results validating the practical efficiency of our incremental approaches in terms of computation times, number of queries and quality of decisions.</a>
<a href="#6" id="6">Recall that we stop when it can be proved that further specifications of the model cannot seriously challenge the current recommendation.</a>
<a href="#7" id="7">That is where we really save time with respect to approaches that fully elicit the utility function, making elicitation feasible in practice.</a>
<a href="#8" id="8">In our opinion, this is the specificity and the contribution of incremental elicitation for decision-making.</a>
<a href="#9" id="9">Our work differentiates from previous works on Choquet integrals in the focus on incremental elicitation and on the ability to provide robust recommendations using minimax regret without making any restrictive assumption on the capacity.</a>
<a href="#10" id="10">Notably, Ah-Pine et al. [62] assess a feasible capacity for a Choquet integral given some preferential information that maximize the margin of the induced constraints (in a fashion similar to SVM classifiers).</a>
<a href="#11" id="11">However this kind of “pointwise” estimation ignore the specificity of the available alternatives (while regret-based approach can focus elicitation on the “useful” part of the utility).</a>
<a href="#12" id="12">Moreover, it does not directly provide a natural strategy for choosing the query to ask within an incremental elicitation setting.</a>
<a href="#13" id="13">The problem of minimizing regrets to derive a robust recommendation with a Choquet integral and an imprecise capacity has also been addressed in [63].</a>
<a href="#14" id="14">In this work, another approach to compute {a mathematical formula}MR(x,X,ΘP) is proposed, relying on the fact that {a mathematical formula}MR(x,X,ΘP)=maxv∈ΘP⁎⁡maxy∈X⁡{Cv(y)−Cv(x)} and {a mathematical formula}ΘP⁎ is the (finite) set of extreme points in {a mathematical formula}ΘP.</a>
<a href="#15" id="15">However, the amount of extreme points seems to be prohibitively large for enumeration methods.</a>
<a href="#16" id="16">Hence, using this approach within an incremental elicitation procedure seems unfeasible for general capacities.</a>
<a href="#17" id="17">This approach is however interesting for two-additive capacities because, in this case, the size of {a mathematical formula}ΘP⁎ is quadratic in the number of criteria.</a>
<a href="#18" id="18">The advantage of our approach, beside the fact that it is incremental, is that it applies to any monotone capacity, without any prior restriction.</a>
<a href="#19" id="19">A first direct continuation of this work is to extend the elicitation procedure for set recommendation, following the work on setwise minimax regret [40].</a>
<a href="#20" id="20">Indeed, while most emphasis of works in recommender systems and decision aid is on providing a single recommendation, it is often appropriate to provide a set of alternatives.</a>
<a href="#21" id="21">The approach we have proposed in this paper extends naturally to sets but is computationally more demanding.</a>
<a href="#22" id="22">A second direction concerns the development of new strategies to search for highly informative queries.</a>
<a href="#23" id="23">We are interested in the sequential evaluation of the informative value of a query; note, however, that sequential optimization of the value of a query will usually be prohibitive in most cases.</a>
<a href="#24" id="24">Alternatively, it will be interesting to test highly informative local search approaches like the query-iteration strategy[64], [40] in our settings.</a>
<a href="#25" id="25">In this paper, we also addressed the problem of sorting using thresholds on the overall utility scale.</a>
<a href="#26" id="26">These thresholds are assumed to be defined in a preliminary step with the DM, independently of the set of alternatives.</a>
<a href="#27" id="27">For instance one may want to construct an overall intrinsic evaluation scale using the unit interval (e.g. for evaluating students, projects...) where 0.5 is the neutral point separating good and bad alternatives; one may also want that excellent alternatives receive at least 0.8 and that very bad alternatives receive at most 0.2.</a>
<a href="#28" id="28">Using such thresholds, we have studied the set of capacities that are compatible with the assignment examples obtained from the DM and developed an incremental elicitation method to progressively reduce this set.</a>
<a href="#29" id="29">It would be possible to learn or approximate thresholds in the same time as capacity values which would possibly provide greater flexibility to describe an assignment (but would prevent us to use thresholds prescribed by the DM).</a>
<a href="#30" id="30">The variable thresholds approach has been proposed for instance in [58] for linear aggregators and could be adapted for Choquet integrals.</a>
<a href="#31" id="31">This would however make thresholds and capacities interdependent and both could be influenced by the learning set.</a>
<a href="#32" id="32">Moreover, in our approach, the fact that thresholds are known allows us to considerably simplify the optimization of regrets (see Section 4.3), which speeds-up computation and provides good interaction possibilities.</a>
<a href="#33" id="33">In the literature on multicriteria sorting, another prominent approach for preference-based sorting has been proposed and widely used in the context of multicriteria evaluation: sorting with reference profiles as proposed by Roy in the Electre TRI method [65] and used in multiple variants see, e.g., [66], [67], [57], [68], [69].</a>
<a href="#34" id="34">In such methods, we are given multicriteria profiles describing the “desiderata” (in terms of criteria) for each category; the alternatives are compared to these profiles on each criterion to derive preference indices that are then aggregated to establish the overall preference.</a>
<a href="#35" id="35">Profiles act as multicriteria boundaries of categories used to make preference-based assignments.</a>
<a href="#36" id="36">Various elicitation procedures have been proposed to assess some parameters in these models (e.g., weight of criteria, reference profiles), see e.g., [66], [70], [71].</a>
<a href="#37" id="37">Recently, the elicitation of Choquet capacities has been also studied in this context [72] but the proposed approach is not incremental.</a>
<a href="#38" id="38">The approach we are proposing here for the incremental elicitation of capacities could easily be adapted to multicriteria sorting models based on comparisons with reference profiles.</a>
<a href="#39" id="39">It is worth noting that the absence of any redundancy in preference queries is a key aspect to obtain efficient questionnaires.</a>
<a href="#40" id="40">We remind indeed that the DM is asked to compare a pair of alternatives {a mathematical formula}(x,y) only when both answers “x preferred to y” and “y preferred to x” are consistent with the preferences collected so far.</a>
<a href="#41" id="41">Hence, we implicitly enforce consistency of stated preference statements and inferred preferences.</a>
<a href="#42" id="42">However, we do not check the internal consistency of the DM during the elicitation process nor the adequacy of the Choquet model to her preferences.</a>
<a href="#43" id="43">Revisiting incremental approaches to manage possible internal inconsistencies of the DM (noisy preferences) and to offer the possibility to falsify the decision model (testing consistency of the observed preferences w.r.t.</a>
<a href="#44" id="44">the Choquet model) while keeping fast elicitation sequences would be an interesting but challenging line for further research.</a>
<a href="#45" id="45">Finally, an interesting direction of research, departing from the regret-based approach, would be incremental elicitation of Choquet capacities using a Bayesian approach (following works on Bayesian utility elicitation [26], [73]), adopting a less conservative criterion for selecting preference queries under uncertainty.</a>
<a href="#46" id="46">It would not provide the same guarantee on the robustness of decisions but could possibly reduce the average number of preference queries in the elicitation process by considering the expected value of information instead of performing a worst case analysis.</a>
</body>
</html>