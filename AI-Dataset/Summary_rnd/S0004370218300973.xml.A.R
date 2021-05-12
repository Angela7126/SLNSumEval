<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:228">
</head>
<body bgcolor="white">
<a href="#0" id="0">Therefore, we leverage temporal closeness, period, trend to select keyframes for modeling.</a>
<a href="#1" id="1">ST-ResNet-AVG1 and ST-ResNet-AVG2: two ST-ResNet variants with same setting, but different input constructing approaches (see Section 3.5)</a>
<a href="#2" id="2">On top of the Lth residual unit, we append a convolutional layer (i.e. Conv2 shown in Fig. 3).</a>
<a href="#3" id="3">We develop a Cloud-based system, called UrbanFlow, that can monitor the real-time crowd flows and provide the forecasting crowd flows in near future using our ST-ResNet.</a>
<a href="#4" id="4">Converting trajectories into inflow/outflow: we first use the massive historical trajectories and employ a calculation module to get crowd flow data, then store them in local.</a>
<a href="#5" id="5">Afterwards, the VM stores the crowd flow data and extracted features into the storage (a part of the VM).</a>
<a href="#6" id="6">Among these models, ST-ResNet-BN and ST-ResNet-noExt are variants of ST-ResNet (12 residual units), where ST-ResNet-BN employs BN.</a>
<a href="#7" id="7">We fuse the first three components (i.e. closeness, period, trend) of Fig. 3 as follows{a mathematical formula} or, equivalently,{a mathematical formula} where ∘ is Hadamard product (i.e. element-wise multiplication), {a mathematical formula}wck,i,j∈Wc, {a mathematical formula}wpk,i,j∈Wp and {a mathematical formula}wqk,i,j∈Wq are the learnable parameters that adjust the degrees affected by closeness, period and trend, respectively.</a>
<a href="#8" id="8">The number of residual units is set as 12 for the dataset TaxiBJ, and 4 for BikeNYC.</a>
<a href="#9" id="9">NearbyThe inflow of Region {a mathematical formula}r2 (shown in Fig. 1(a)) is affected by outflows of nearby regions (like {a mathematical formula}r1).</a>
</body>
</html>