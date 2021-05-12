<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:725">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have defined a new class of problems, Bounded Trajectory Management Problems (BTMPs), and introduced AC voltage control as an instance of this class.</a>
<a href="#1" id="1">We have addressed the problem of AC voltage control by extending the planner popf2, to popf-tif, along two dimensions: Timed Initial Fluents on one dimension and integration with a specialised power flow equation solver on the other.</a>
<a href="#2" id="2">Electrical loads and generation profiles are modelled using TIFs, and the network voltage must always remain within bounds.</a>
<a href="#3" id="3">Actions can change the configurations of network components, causing the voltage to increase or decrease at the busbars.</a>
<a href="#4" id="4">To provide heuristic information in the presence of TIFs we add a lookahead mechanism that allows the planner to calculate the effect of the next TIF on the maintenance of the trajectory constraints.</a>
<a href="#5" id="5">This approach is general to the BTMP class.</a>
<a href="#6" id="6">We model the AC power flow problem by introducing an encapsulated type, Network, allowing us to efficiently capture the network-wide effects of local changes to controllable elements of the network.</a>
<a href="#7" id="7">Managing AC power flow is computationally expensive, so we limit the use of accurate calculations of voltages to the state progression phase of search.</a>
<a href="#8" id="8">During heuristic computation, an abstraction of the network type is used that is based on a first order approximation of the effects of the actions.</a>
<a href="#9" id="9">In some problems, network state changes can undermine the validity of the first order approximations generated in the initial state so we also consider recalculation of the first order approximation in each state as it is evaluated.</a>
<a href="#10" id="10">This more informed approximation of the effects of actions turns out to be of value for some of the problems considered.</a>
<a href="#11" id="11">However, it is a computationally expensive operation and not justified by our experiments.</a>
<a href="#12" id="12">We describe the application of our approach to the AC voltage control of the AuRA-NMS case study network [40].</a>
<a href="#13" id="13">This network models some of the assumptions of future distribution networks, characterised by the presence of distributed generators.</a>
<a href="#14" id="14">In our experiments, a reactive control approach does not perform well, while popf-tif always finds solutions that satisfy the voltage limits of each busbar of the network.</a>
<a href="#15" id="15">We study the limitations of popf-tif, considering networks increasing in size as the number of passive elements (such as busbars and lines) increases, and then as the number of active control points (transformers, capacitors, etc.)</a>
<a href="#16" id="16">increases.</a>
<a href="#17" id="17">The number of passive elements is not an issue for the planner: we observe an increase in the running time, due to the time spent by the external solver to compute the solution of the power flow equations, but this does not affect the number of states evaluated by the planner.</a>
<a href="#18" id="18">In contrast, performance on networks with an increasing number of control points is affected, but it remains acceptable for networks with tens of control elements and many tens of busbars.</a>
<a href="#19" id="19">The lookahead heuristic, described in this paper, provides a better heuristic estimate than that of the standard temporal relaxed planning graph of popf2, and allows us to solve more problems.</a>
<a href="#20" id="20">The existence of AC voltage control plans in different scenarios shows that there are feasible solutions, even when the industry standard HTC method does not find them.</a>
<a href="#21" id="21">Unlike the HTC controller, popf-tif can make use of coordinated action across the network, without being tied to an ineffectual, delay-based communication mechanism.</a>
<a href="#22" id="22">Being able to look ahead, at forecasted future demand and generation profiles, enables more robust performance than can be achieved using reactive methods.</a>
<a href="#23" id="23">AI Planning is automatic, proactive and partially robust, with the degree of robustness depending on the forecasting errors and the planning horizon.</a>
<a href="#24" id="24">In this paper we have used AC power flow as an example of a BTMP that requires the external solver interface.</a>
<a href="#25" id="25">We developed popf-tif to meet both requirements of this domain.</a>
<a href="#26" id="26">The BTMP management is fully general, as the lookahead heuristic can give advantages in any domains with background numeric events modelled as TIFs.</a>
<a href="#27" id="27">We have provided one instantiation of the external solver interface, that is specific to the AC voltage control problem.</a>
<a href="#28" id="28">However, popf-tif can easily be configured for other domains, simply by replacing the external solver with an appropriate one, and defining a new set of external functions.</a>
<a href="#29" id="29">In our future work we will explore the generality of the popf-tif framework, and extend the type-based abstraction method further in the direction of planning modulo theories [27].</a>
</body>
</html>