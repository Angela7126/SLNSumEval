<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:547">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented a novel and general approach to propagating small constraints.</a>
<a href="#1" id="1">The approach is to generate a custom stateless propagator that enforces GAC in {a mathematical formula}O(nd).</a>
<a href="#2" id="2">This is a spectacular improvement over other general techniques, which are exponential in the worst case, but comes with an equally spectacular tradeoff.</a>
<a href="#3" id="3">This is that the stored propagator can be very large — it scales exponentially in the size of the constraint — therefore generating and storing it is only feasible in general at very small sizes.</a>
<a href="#4" id="4">We have presented two methods for storing and then executing the generated constraints.</a>
<a href="#5" id="5">One is to construct special purpose code (in our case in {a mathematical formula}C++) and then compile it before use.</a>
<a href="#6" id="6">The second is that we use a simple virtual machine with a tiny special purpose instruction set in which propagator trees can be executed.</a>
<a href="#7" id="7">The second method has the advantage of not requiring compilation — apart from the convenience of not needing a compiler sometimes the propagator code becomes too big to compile.</a>
<a href="#8" id="8">We demonstrated that the propagator generation approach can be highly efficient compared to table constraints.</a>
<a href="#9" id="9">For example, on Life {a mathematical formula}n=7, {a mathematical formula}p=4, the standard propagator tree is 9.7 times faster than MDDC, and 7.2 times faster than an encoding using a sum constraint.</a>
<a href="#10" id="10">Remarkably, propagator trees can even be faster than hand-optimised propagators.</a>
<a href="#11" id="11">For example, we achieved a 27% speedup on a min constraint in peg solitaire instance 10.</a>
<a href="#12" id="12">We significantly extended the scalability of our approach by exploiting symmetry within the constraint.</a>
<a href="#13" id="13">To do this we introduced symmetry-reduced trees and algorithms for dealing with them.</a>
<a href="#14" id="14">This allowed us to scale up from the Life constraint (with 20 literals) to extended variants of Life with 30 literals.</a>
<a href="#15" id="15">While this may seem a small step, it enabled us to solve variants of Life for which we could not previously build trees.</a>
<a href="#16" id="16">On the LABS problem we observed three orders of magnitude reduction in the size of the generated propagator tree.</a>
<a href="#17" id="17">Again we provided both compiled and virtual machine implementations.</a>
<a href="#18" id="18">However run time worsens to {a mathematical formula}O(n2d2) in the worst case from {a mathematical formula}O(nd) in the non-symmetric case.</a>
<a href="#19" id="19">This did cause a slowdown in our experiments compared to the non-symmetric version where available, but we still achieved very good performance.</a>
<a href="#20" id="20">Our analysis of the XCSP benchmark set showed that while there were 750,346 different constraint relations applied to over 6.5 million scopes, the most common 827 constraint relations covered over 85% of the constraint scopes.</a>
<a href="#21" id="21">This demonstrates how a small number of specialised propagators can cover a large proportion of the constraint scopes in a large set of benchmarks.</a>
<a href="#22" id="22">We believe that our approach of building special purpose generated constraint propagators has considerable promise for the future.</a>
<a href="#23" id="23">While surprisingly fast, the propagator trees are entirely stateless — there is no state stored between calls, and no local variables.</a>
<a href="#24" id="24">They also do not make use of trigger events, which are often essential to the efficiency of propagators.</a>
<a href="#25" id="25">Therefore we believe there is scope to scale the approach further and to improve efficiency.</a>
<a href="#26" id="26">Additionally, we believe that symmetry-reduced trees are worthy of further study.</a>
<a href="#27" id="27">They are a general construction and further study may show them to have other important applications beyond constructing efficient propagators.</a>
</body>
</html>