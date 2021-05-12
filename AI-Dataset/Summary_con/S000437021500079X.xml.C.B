<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:686">
</head>
<body bgcolor="white">
<a href="#0" id="0">Previous approaches automatically configure sequential portfolios with a large set of training data.</a>
<a href="#1" id="1">Also, it has been shown that remarkable results in Automated Planning are possible with the uniform method, which allocates the same amount of time to each solver in the sequential portfolio.</a>
<a href="#2" id="2">We introduce gop, a Mixed-Integer Programming approach to address both issues.</a>
<a href="#3" id="3">We have shown that gop can compute an upper bound on the performance that is feasible with a linear combination of candidate solvers for a particular training data set.</a>
<a href="#4" id="4">Our results show that it is possible to solve up to 265 planning instances (with a total quality of 252.75) from the pool of 280 tasks of the sequential satisficing track of the IPC 2011 with state-of-the-art planners that do not communicate among them.</a>
<a href="#5" id="5">In our view, reaching a total quality higher than 252.75 in the same pool of planning tasks, under the same conditions, would be a remarkable achievement.</a>
<a href="#6" id="6">In addition, we have performed an empirical analysis to determine the composition of the best training data set to configure high-performance portfolios.</a>
<a href="#7" id="7">Our results show that not all problems provide the same information, termed utility here, and that portfolios configured with small training data sets can perform very well.</a>
<a href="#8" id="8">Indeed, we have derived exactly the same portfolio using a training data set with only 27 problems than with the whole collection of problems (composed of 280 instances) defined for the optimal track of the IPC 2011.</a>
<a href="#9" id="9">Therefore, we conjecture that the best training problems set should contain only a small number of instances that a few solvers are able to solve.</a>
<a href="#10" id="10">We have compared the performance of gop and fdss, one of the most successful approaches to automatically configure portfolios in planning.</a>
<a href="#11" id="11">fdss sorts the execution sequence of its sequential satisficing portfolios, implements dynamic behavior and exchanges information among the component planners.</a>
<a href="#12" id="12">Our results show that not using the sophisticated mechanisms of fdss, using far fewer training problems and considering the same set of candidate planners, it is possible to outperform the best configuration of fdss for satisficing planning.</a>
<a href="#13" id="13">Also, we have compared gop with the most recent approach to configure sequential portfolios in satisficing planning: the approach followed by Seipp et al. It is an empirical approach that generates first a set of domain-dependent planners and analyzes the best technique to combine them.</a>
<a href="#14" id="14">Our results have shown that gop, a theoretically-grounded method dominates the best technique found by them with the same set of candidate planners (with respect to the portfolio configuration step).</a>
<a href="#15" id="15">Moreover, we have submitted a participant planner termed MIPlan to the learning track of the IPC 2014 with the aim of assessing gop in this track.</a>
<a href="#16" id="16">The results show that MIPlan, the planning system which uses gop to generate a sequential portfolio for each given planning domain, outperforms others.</a>
<a href="#17" id="17">It achieved the best overall quality and also the best coverage in the competition.</a>
<a href="#18" id="18">Therefore, MIPlan won the overall best quality award.</a>
<a href="#19" id="19">Finally, we have evaluated gop on the SAT Competition 2013.</a>
<a href="#20" id="20">We have submitted one sequential portfolio to the open track, which was specifically defined for portfolio approaches.</a>
<a href="#21" id="21">The results of this track show that our portfolio is the second best solver.</a>
<a href="#22" id="22">It only solved three instances less than the winner.</a>
<a href="#23" id="23">Also, we have shown that the best performance achievable with a linear combination of the participant solvers is the same than the performance achieved by the winner.</a>
<a href="#24" id="24">Therefore, our portfolio only solves three instances less than the best portfolio configuration for the open track.</a>
<a href="#25" id="25">We hypothesize that the order in which solvers are invoked is important in the particular case of satisficing planning.</a>
<a href="#26" id="26">Therefore, in the future, we will analyze the performance of the same sequential portfolio applying different algorithms to sort its execution sequence.</a>
<a href="#27" id="27">Also, we leave as future work generalizing the MIP model to the parallel case.</a>
<a href="#28" id="28">Additionally, we want to study different behaviors in the sequential portfolio once the first solution has been found.</a>
<a href="#29" id="29">We believe that developing dynamic portfolios (i.e., that can change their behavior without using predefined rules) while solving an instance, might improve the performance of the static portfolios considered here.</a>
</body>
</html>