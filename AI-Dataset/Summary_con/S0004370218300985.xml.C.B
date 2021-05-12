<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:730">
</head>
<body bgcolor="white">
<a href="#0" id="0">Training deep architectures with backpropagation on digital computers is useful for practical applications, and it has become easier than ever, in part because of the creation of software packages with automatic differentiation capabilities.</a>
<a href="#1" id="1">This convenience, however, can be misleading as it hampers thinking about the constraints of learning in physical neural systems, which are merely being mimicked on digital computers.</a>
<a href="#2" id="2">Thinking about learning in physical systems is useful in many ways: it leads to the notion of local learning rules, which in turn identifies two fundamental problems facing backpropagation in physical systems.</a>
<a href="#3" id="3">First backpropagation is not local, and thus a learning channel is required to communicate error information from the output layer to the deep weights.</a>
<a href="#4" id="4">Second, backpropagation requires symmetric weights, a significant challenge for those physical systems that cannot use the forward channel in the reverse direction, thus requiring a different pathway to communicate errors to the deep weights.</a>
<a href="#5" id="5">RBP is one mode for communicating information over the learning channel, that completely bypasses the need for symmetric weights, by using fixed random weights instead.</a>
<a href="#6" id="6">However RBP is only one possibility among many other ones for harnessing randomness in the learning channel.</a>
<a href="#7" id="7">Here we have derived several variants of RBP and studied them through simulations and mathematical analyses.</a>
<a href="#8" id="8">Additional variants are studied in a followup paper [4] which considers additional symmetry issues such as having a learning channel with an architecture that is not a symmetric version of the forward architecture, or having non-linear units in the learning channel that are similar to the non-linear units of the forward architecture.</a>
<a href="#9" id="9">In combination, the main emerging picture is that the general concept of RBP is remarkably robust as most of the variants lead to robust learning.</a>
<a href="#10" id="10">RBP and its many variants do not seem to have a practical role in digital simulations as they often lead to slower learning, but they should be useful in the future both to better understand biological neural systems, and to implement new neural physical systems in silicon or other substrates.</a>
<a href="#11" id="11">In supervised learning, the critical equations show that in principle any deep weights must depend on all the training examples and all the other weights of the network.</a>
<a href="#12" id="12">Backpropagation shows that it is possible to derive effective learning rules of the form {a mathematical formula}Δwijh=ηIijhOjh−1 where the role of the lower part of the network is subsumed by the presynaptic activity term {a mathematical formula}Ojh−1 and {a mathematical formula}Iijh is a signal communicated through the deep learning channel that carries information about the outputs and the targets to the deep synapses.</a>
<a href="#13" id="13">Here we have studied what kind of information must be carried by the signal {a mathematical formula}Iijh and how much it can be simplified (Table 2).</a>
<a href="#14" id="14">The main conclusion is that the postsynaptic terms must: (1) implement gradient descent for the top layer (i.e. random weights in the learning channel for the top layer do not work at all); (2) for any other deep layer h it should be of the form {a mathematical formula}f′F(T−O), where {a mathematical formula}f′ represents the local derivatives of the activations of the units in layer h (the derivatives for the layers above are not necessary) and F is some reasonable function of the error {a mathematical formula}T−O.</a>
<a href="#15" id="15">By reasonable, we mean that the function F can be linear, or a composition of linear propagation with non-linear activation functions, it can be fixed or slowly varying, and when matrices are involved these can be random, sparse, etc.</a>
<a href="#16" id="16">As can be expected, it is better if these matrices are full rank although gracious degradation, as opposed to catastrophic failure, is observed when these matrices deviate from the full rank case.</a>
<a href="#17" id="17">Furthermore, the function F should satisfy {a mathematical formula}F(0)=0 to prevent weight changes when the error is zero and thus, to a first order of approximation, F should be linear with no biases.</a>
<a href="#18" id="18">The robustness and other properties of these algorithms cry for explanations and more general principles.</a>
<a href="#19" id="19">We have provided both intuitive and formal explanations for several of these properties.</a>
<a href="#20" id="20">On the mathematical side, polynomial learning rules in linear networks lead to systems of polynomial differential equations.</a>
<a href="#21" id="21">We have shown in several cases that the corresponding ODEs converge to an optimal solution.</a>
<a href="#22" id="22">However these polynomial systems of ODEs rapidly become complex and, while the results provided are useful, they are not yet complete, thus providing directions for future research.</a>
</body>
</html>