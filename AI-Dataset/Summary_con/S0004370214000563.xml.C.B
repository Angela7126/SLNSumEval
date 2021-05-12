<html>
<head>
<meta name="TextLength" content="SENT_NUM:42, WORD_NUM:1090">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have discussed a new efficient method for determining the flexibility of a schedule for the Simple Temporal Problem.</a>
<a href="#1" id="1">The main advantage of this flexibility metric is that, unlike previous methods that have been proposed in the literature, it takes into account dependencies between events.</a>
<a href="#2" id="2">As a consequence, this metric does not suffer from overestimations of the flexibility in an STN.</a>
<a href="#3" id="3">We have shown that the method used in obtaining this flexibility metric might be used in other contexts, too.</a>
<a href="#4" id="4">First of all, we could state a very simple and elegant solution to the strong controllability problem in STNUs.</a>
<a href="#5" id="5">Moreover, our approach allows for a simple solution to generalizations of the strong controllability problem in STNUs as well.</a>
<a href="#6" id="6">Finally, we could show that the use of the flexibility metric allows us to disprove a rather widespread belief in the research community, i.e., that temporal decoupling of an STN necessarily results in a reduction of its flexibility: We showed that once the flexibility of an STN has been determined, it can be used to construct a temporal decoupling that does not affect the (total) flexibility of the system.</a>
<a href="#7" id="7">Note that we computed the flexibility metric {a mathematical formula}flex(S) as the result of solving an LP to determine a maximum flexible interval schedule for an STN S. Such an interval schedule enables an executor to provide a flexible schedule by choosing the dispatching times of an event within its interval.</a>
<a href="#8" id="8">In this sense it offers an alternative to approaches that transform an STN into a dispatchable network [9] where at every time an actual starting time of an event has been chosen, the consequences of such a choice are propagated through the network.</a>
<a href="#9" id="9">Both approaches to dispatching have their advantages and disadvantages.</a>
<a href="#10" id="10">In a dispatchable network we might compute an interval for the starting time of the first event to be dispatched and based on the actual dispatching time recompute the interval(s) for the dispatching of the next events by local propagation.</a>
<a href="#11" id="11">Here, in principle, in selecting an interval for the next event to be dispatched, the flexibility for choosing the starting time in a dispatchable network might be larger than the corresponding length of the precomputed interval as computed by our method.</a>
<a href="#12" id="12">On the other hand, taking – in a dispatchable network – the time window for each new event to be dispatched should be considered as a specification of the potential flexibility of that event.</a>
<a href="#13" id="13">The realized flexibility of an event can be defined as the difference between the minimum allowable time point for dispatching the event and its actual dispatching time.</a>
<a href="#14" id="14">It is not difficult to see that in any dispatching of an STN S, the sum of all realized flexibilities is upper bounded by {a mathematical formula}flex(S).</a>
<a href="#15" id="15">So in this sense we can't do better.</a>
<a href="#16" id="16">Also, in a dispatchable network, we have to recompute time windows after an event has been dispatched.</a>
<a href="#17" id="17">In this sense, we may be forced to a strictly sequential dispatching strategy, while in our interval schedule framework, we allow for complete concurrency in computing the dispatching of events.</a>
<a href="#18" id="18">The careful reader might have noticed that our flexibility metric is not restricted to Simple Temporal Networks where only binary difference constraints occur.</a>
<a href="#19" id="19">In fact, the method can be easily generalized as we have already done (see [27]) to compute the flexibility of general linear systems {a mathematical formula}Ax≤b.</a>
<a href="#20" id="20">This offers the possibility of computing sets of solutions for such systems that guarantee that whatever value for a variable is selected in each of the intervals, the maximum value of the objective function for this combination of values is preserved.</a>
<a href="#21" id="21">Moreover, this method can be used to give an efficient solution for decoupling problems for general linear systems such as analyzed by [28].</a>
<a href="#22" id="22">With respect to future research, we would like to mention the following issues.</a>
<a href="#23" id="23">First of all, sometimes our flexibility metric gives counter-intuitive results, especially in cases where concurrency in choosing the execution of events should be avoided.</a>
<a href="#24" id="24">For example, suppose an STN S consists of two events {a mathematical formula}t1 and {a mathematical formula}t2 that have to be executed simultaneously in the interval {a mathematical formula}[0,10].</a>
<a href="#25" id="25">Intuitively, the flexibility of S is 10.</a>
<a href="#26" id="26">Using our flexibility metric, however, it turns out that {a mathematical formula}flex(S)=0.</a>
<a href="#27" id="27">The reason is that {a mathematical formula}flex(S) measures the total flexibility in making independent choices.</a>
<a href="#28" id="28">In this system S, however, we should choose for the flexibility of one of the events first.</a>
<a href="#29" id="29">The remaining flexibility after this choice is 0.</a>
<a href="#30" id="30">A possible solution would be to search for suitable network contractions of an STN.</a>
<a href="#31" id="31">For example, in this system S, we could easily contract the set of time points to one time point.</a>
<a href="#32" id="32">The flexibility of the resulting system then corresponds to our intuition.</a>
<a href="#33" id="33">Secondly, as the reader might have observed, the total flexibility of a system can be obtained in many, sometimes even quite unfair, ways.</a>
<a href="#34" id="34">For example, preserving the total flexibility of the system could mean that a decoupling heavily favors some specific agents by giving them a lot of flexibility, while harming other agents by taking away their flexibility.</a>
<a href="#35" id="35">To prevent this, we need to come up with fair flexibility distribution schemes as an objective to grant every agent an almost equal portion of flexibility.</a>
<a href="#36" id="36">We could propose more fair distributions of flexibility and evaluate their performance by comparing it to the maximally obtainable flexibility as we have proposed in our paper to establish the price of fairness.</a>
<a href="#37" id="37">An initial investigation into the effects of different methods of distributing the available flexibility in a schedule has already been performed by the authors (see [29]), but more work is needed in this area.</a>
<a href="#38" id="38">Finally, another question we did not deal with in this paper is how we should distribute flexibility over the events in order to ensure that a given interval schedule as proposed could enhance the robustness of a schedule.</a>
<a href="#39" id="39">For example, if some events are considered as critical or more susceptible to delays, we could try to provide them with a larger scheduling interval.</a>
<a href="#40" id="40">Research in this direction also should pay attention to the dependencies of events upon other events (as expressed by the STN) to minimize scheduling violations.</a>
<a href="#41" id="41">Together with extensions of the STN framework with stochastic interpretations of the upper bounds {a mathematical formula}cij on the constraints, this would enable stochastic interpretations of the total flexibility of an STN and encourage empirical research into optimal distributions of flexibility over the events in order to ensure maximal (expected) robustness of the resulting schedule.</a>
</body>
</html>