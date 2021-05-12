<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:418">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we have developed a novel comprehensive framework for distributed qualitative fault diagnosis of continuous systems using structural model decomposition, where PCs are used to decouple the faults from the measurements and compute minimal submodels for distributed diagnosis.</a>
<a href="#1" id="1">Then, the basic PC framework is extended to allow merging of PCs to design globally diagnosable diagnosis submodels.</a>
<a href="#2" id="2">We proposed an algorithm that merges PCs (when necessary) to design local distributed diagnosis submodels based on global diagnosability.</a>
<a href="#3" id="3">These local distributed diagnosis submodels are then used to construct local event-based distributed diagnosers.</a>
<a href="#4" id="4">Finally, we use the model decomposition capabilities of the PCs not only to improve the design, but also to integrate within our framework a distributed fault identification approach by developing independent local parameter estimators.</a>
<a href="#5" id="5">Our main conclusion is that using a structural model decomposition method, such as PCs, together with the existing consistency-based diagnosis approach using qualitative information, results in an event-based distributed diagnosis framework covering fault detection, isolation, and identification that scales well, and where the local diagnosers are independent at every level (no communication between them at any stage is required), do not need a central coordinator, and have no single point of failure.</a>
<a href="#6" id="6">Experimental results on a rover showed the improvement of the design using submodels against the approach that uses the global model of the system [10].</a>
<a href="#7" id="7">The decoupling obtained by the PCs improved the design process and the size of the local diagnosers, thus providing a scalable solution.</a>
<a href="#8" id="8">Using the rover, we also ran several experiments to compare the performance of a centralized approach against our distributed approach regarding fault detection, isolation and identification.</a>
<a href="#9" id="9">Results for different kinds of faults with several fault magnitudes have shown that the distributed approach is able to obtain similar detection and isolation results to the centralized approach, while avoiding the problems related to the centralized scheme.</a>
<a href="#10" id="10">Regarding fault identification, results obtained using the distributed approach with the local parameter estimators showed an improvement in the accuracy of the estimation with just a small loss in precision.</a>
<a href="#11" id="11">Some limitations of the current approach are the single fault assumption, and the applicability to only continuous systems.</a>
<a href="#12" id="12">In future work, we plan to extend our approach to multiple faults, based on results presented in [35], and to hybrid systems, based on results presented in [56], [57].</a>
<a href="#13" id="13">We are also planning to integrate our distributed diagnosis framework into a distributed prognostics framework (that also uses structural model decomposition with PCs [58]) to develop an integrated distributed diagnostics and prognostics framework.</a>
</body>
</html>