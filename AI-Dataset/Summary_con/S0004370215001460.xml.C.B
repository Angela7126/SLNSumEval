<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:284">
</head>
<body bgcolor="white">
<a href="#0" id="0">Aerosol Optical Depth is an important input parameter to complex climate models developed to predict and better understand Earth's climate.</a>
<a href="#1" id="1">Consequently, accurate AOD estimation is the problem of global significance, and in this paper we address this task by proposing a semi-supervised method for aggregation of AOD predictions from noisy satellite-borne sensors into a single, more accurate estimate.</a>
<a href="#2" id="2">By assuming that expert predictions follow multivariate Gaussian distribution, the method accounts for both missing experts and unlabeled data in a principled manner, addressing an issue inherent to the remote sensing domain.</a>
<a href="#3" id="3">Furthermore, by introducing a context-dependent AOD prior, the model is capable of incorporating additional data sources and providing estimates even when there are no available experts.</a>
<a href="#4" id="4">Lastly, we also cluster the data during training by introducing a latent indicator variable for each cluster, resulting in a more interpretable model.</a>
<a href="#5" id="5">Results on a synthetic data set and real-world aerosol data set comprising 5 satellite-borne sensors strongly indicate the benefits of the proposed aggregation method.</a>
<a href="#6" id="6">The described approach makes several assumptions that resulted in a simplified model of aerosol distribution, yet do not necessarily hold in practice.</a>
<a href="#7" id="7">In particular, we assumed that the data points are sampled IID, and did not account for spatio-temporal correlations that inherently exist in the aerosol data [37], [38].</a>
<a href="#8" id="8">In addition, the covariance matrix in this work is assumed static, and is not affected by the context in which the data points appear.</a>
<a href="#9" id="9">Lastly, we assumed that errors in measurements are Gaussian, and that all experts have equal, zero biases.</a>
<a href="#10" id="10">We are investigating approaches where we weaken or altogether drop these simplifying assumptions in order to extend and further improve modeling of aerosol distribution, and leave these ideas for future work.</a>
</body>
</html>