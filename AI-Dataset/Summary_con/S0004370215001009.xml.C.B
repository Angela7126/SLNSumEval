<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:393">
</head>
<body bgcolor="white">
<a href="#0" id="0">We introduced a new generalised distribution semantics for probabilistic logic programming making it possible to use random variables with arbitrary ranges.</a>
<a href="#1" id="1">The semantics illustrate that the integration of various known techniques can provide a powerful formalism.</a>
<a href="#2" id="2">In particular, we combine the ability of logic to represent relational knowledge, probability theory to deal with uncertainty and constraints representing conditions on variables with various ranges.</a>
<a href="#3" id="3">As commonly known, exact probabilistic inference is only possible under conditions which pose strong restrictions on distributions.</a>
<a href="#4" id="4">As an alternative to many other approximation methods, we propose to use a framework based on credal sets where lower and upperbounds on posteriors can be guaranteed.</a>
<a href="#5" id="5">Placing the method in the theory of imprecise probabilities provides a clear view on the approach, allowing one to explore its properties and to compare with other approaches.</a>
<a href="#6" id="6">Also, powerful applications of the approach can straightforwardly be defined, for instance approximating probabilities of events with known and arbitrarily small maximum error in hybrid distributions.</a>
<a href="#7" id="7">We further show that a concrete language can be based on that concept and that we can perform exact inference with similar complexity as for the precise case, which is a quite unique property for an imprecise formalism.</a>
<a href="#8" id="8">We developed a concrete inference algorithm, based on a generalisation of WMC.</a>
<a href="#9" id="9">The algorithm is able to exploit the same kinds of structure as ordinary WMC, which is the state-of-the-art of precise probabilistic inference.</a>
<a href="#10" id="10">This again shows the benefit of our general semantic foundation integrating existing AI approaches.</a>
<a href="#11" id="11">The language can straightforwardly be extended with arbitrary constraint theories, such as ordinary constraint logic programming.</a>
<a href="#12" id="12">Furthermore, for performing inference we can make use of existing algorithms from the field of logic programming and constraint satisfaction, in particular modern SMT solvers, and generalise probabilistic inference by weighted model counting, inheriting the method's strengths.</a>
<a href="#13" id="13">In the future the most important aspect to make PCLP practically useful is to implement efficient inference mechanisms.</a>
<a href="#14" id="14">One research direction is to apply knowledge compilation techniques, which are already successfully applied for the standard WMC problem.</a>
<a href="#15" id="15">Also, the naive way to discretise continuous distributions used in this article can probability be improved enormously.</a>
<a href="#16" id="16">Further, computing expectations of random variables values is an important problem to solve for practical applications.</a>
<a href="#17" id="17">We finally plan to apply PCLP for building information fusion models in the context of the maritime safety and security project METIS[97], [98].</a>
</body>
</html>