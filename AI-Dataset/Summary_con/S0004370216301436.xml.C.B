<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:386">
</head>
<body bgcolor="white">
<a href="#0" id="0">The original contribution of this paper, the Alors method, provides a sound methodology to tackle algorithm selection, and to analyze where the AS difficulties might come from.</a>
<a href="#1" id="1">A first possible source of errors is the insufficient representativity of the problem instances w.r.t.</a>
<a href="#2" id="2">the algorithm portfolio.</a>
<a href="#3" id="3">This error is diagnosed when the matrix reporting the performance of the algorithms on the problem instances can hardly be reconstructed from an excerpt thereof.</a>
<a href="#4" id="4">Otherwise, the CF matrix yields an accurate latent representation of the problem instances and the algorithms.</a>
<a href="#5" id="5">A second possible source of errors is the inadequate representation of the problem instances.</a>
<a href="#6" id="6">A main result of the paper is to provide empirical evidence that both difficulties are distinct: on the OpenML benchmark, excellent Matrix Completion results coexist with poor Cold Start results, suggesting that the initial OpenML features are insufficient.</a>
<a href="#7" id="7">The comparison of the latent and initial representations further provides a visual and quantitative assessment for each initial feature (section 6.4).</a>
<a href="#8" id="8">A short-term perspective for further work is to extend Alors to achieve both algorithm selection and configuration, selecting the best suited algorithm and the optimal hyper-parameters for a problem instance.</a>
<a href="#9" id="9">A natural idea is to consider each algorithm-configuration as an algorithm with a (varying length) feature description, its hyper-parameter setting, along the lines of AutoWeka [52].</a>
<a href="#10" id="10">Some care must be taken, though, in order to limit the sparsity of the collaborative matrix when dealing with continuous hyper-parameters.</a>
<a href="#11" id="11">Another perspective is to extend Alors to build pre-schedulers, taking advantage of the per-instance ranking of the algorithms defined by Alors.</a>
<a href="#12" id="12">Pre-schedulers could then be derived by allocating to the top-ranked algorithms a given part of the computational budget; as these top-ranked algorithms depend on the current instance, one would thus get a per-instance pre-scheduler.</a>
<a href="#13" id="13">Our main research perspective regards the design of initial features.</a>
<a href="#14" id="14">As witnessed by the AS successes in SAT and CSP, the initial features in these domains are quite accurate; but their design required significant manual efforts, and further efforts might be required when the SAT and CSP domains will face new families of problems.</a>
<a href="#15" id="15">In the ML and KDD domain, the design of initial features also consumed huge manual efforts for over two decades.</a>
<a href="#16" id="16">The search for efficient initial features might be facilitated by using the distortion w.r.t.</a>
<a href="#17" id="17">latent features to assess candidate initial features.</a>
</body>
</html>