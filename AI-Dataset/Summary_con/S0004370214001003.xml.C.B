<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:884">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we described an unsupervised training method for energy disaggregation systems which tunes general appliance models using only household aggregate data.</a>
<a href="#1" id="1">Unlike existing work, it does not require sub-metered training data from the houses in which disaggregation is performed, nor does it require a manual labelling phase or an exhaustive appliance database.</a>
<a href="#2" id="2">Instead, our approach learns general models of appliance types which generalise to new appliances, and uses aggregate data as obtained from a smart meter to further learn the characteristics unique to a specific appliance instance.</a>
<a href="#3" id="3">The proposed generalisation method uses the existing Tracebase appliance data set to learn an HMM for a number of instances of the same appliance type.</a>
<a href="#4" id="4">It then fits distributions to the HMM parameters of each appliance instance to build a general model for each appliance type.</a>
<a href="#5" id="5">Through a cross validation evaluation, we showed that only a small number of instances of each type are required for simple appliances, such as the kettle.</a>
<a href="#6" id="6">However, we also showed that the number of instances required to sufficiently generalise over an appliance type increases for more complex appliances, such as the washing machine.</a>
<a href="#7" id="7">We also developed a method by which general appliance models can be tuned to the specific appliance instances in a household given only aggregate data as would be collected by a smart meter.</a>
<a href="#8" id="8">The method uses these general models to identify and extract power signatures of individual appliances from the aggregate load, which are subsequently used to tune the general appliance models.</a>
<a href="#9" id="9">We showed that appliance models built using this tuning method explain sub-metered data with a higher likelihood than had the general models been used, and in cases where sufficient signatures can be extracted, such tuned models perform comparably to had sub-metered data been used to tune the models.</a>
<a href="#10" id="10">Furthermore, we showed that our approach outperforms the state of the art, which uses a factorial HMM to tune the appliance parameters using only aggregate data.</a>
<a href="#11" id="11">The primary motivation for proposing an unsupervised training method for energy disaggregation is to enable existing HMM-based disaggregation methods [20], [22] to be applied automatically to previously unseen households.</a>
<a href="#12" id="12">In addition, we also described the direct benefits which tuned appliance models can provide, such as advice regarding appliance energy efficiency and annual costs.</a>
<a href="#13" id="13">Future work will focus on a large-scale deployment of the technology presented in this work integrated with AgentSwitch; an agent-based platform designed to help household occupants manage their electricity consumption [32].</a>
<a href="#14" id="14">We aim to use the general models as constructed from the Tracebase data set, in combination with household aggregate data, to provide intuitive and actionable energy saving advice to household occupants.</a>
<a href="#15" id="15">The accuracy of inferred energy efficiency will be evaluated using limited individual appliance sub-meters, and the operating energy efficiency of appliances will be compared with that quoted by the appliance manufacturer.</a>
<a href="#16" id="16">Furthermore, we will also use such appliance sub-meters to measure whether the energy saving advice has resulted in energy and financial savings.</a>
<a href="#17" id="17">In such a deployment, it might be necessary to construct more extensive general appliance models as larger sub-metered data sets become available.</a>
<a href="#18" id="18">However, the use of longer power sequences will increase the time required to build such general models, and therefore more efficient inference algorithms would be required.</a>
<a href="#19" id="19">One possibility would be to exploit the structure of HMMs through a structured variational inference algorithm.</a>
<a href="#20" id="20">Such an approach would iterate between exact inference over HMM states using the Viterbi algorithm [37], and a variational approximation for the HMM parameters.</a>
<a href="#21" id="21">In most cases, it is trivial to determine the number of states for an appliance type given some examples of power data.</a>
<a href="#22" id="22">However, for more unusual appliances, this might not be the case, and as a result an automated approach will be required to determine the number of states.</a>
<a href="#23" id="23">We believe the infinite hidden Markov model [3] provides a natural representation of appliances in which the number of states is unbounded, and is free to grow as more data is observed.</a>
<a href="#24" id="24">However, new methods will be required to generalise over these models, since an infinite HMM will likely learn a slightly different set of states when applied to multiple appliance instances of the same type.</a>
<a href="#25" id="25">Another interesting challenge for extending this work would be to apply our proposed training methods to appliance models other than those based on HMMs.</a>
<a href="#26" id="26">We have shown HMMs to be a good model for appliances with discrete set of states (e.g. refrigerator or dishwasher), however HMMs are likely to fail for appliances with a continuously variable power demand (e.g. plasma television).</a>
<a href="#27" id="27">In such cases, different graphical models might represent such continuously variable appliances more appropriately.</a>
<a href="#28" id="28">We believe that the approach proposed in this work, which constructs general appliance models and tunes such models using aggregate data, is general and will be applicable to new graphical models.</a>
<a href="#29" id="29">Although the majority of UK households contain a combined refrigerator and freezer [41], some households instead contain a separate refrigerator and freezer.</a>
<a href="#30" id="30">In such cases, there might always be at least two appliances which have recently changed state, and therefore it might not be possible to extract individual appliance signatures in order to tune model parameters.</a>
<a href="#31" id="31">As a result, alternative techniques are required which can tune a small number of appliances simultaneously, while still using the generic models to identify such signature periods.</a>
</body>
</html>