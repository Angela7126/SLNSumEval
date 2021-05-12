<html>
<head>
<meta name="TextLength" content="SENT_NUM:25, WORD_NUM:625">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work we presented a novel class of methods for structured learning problems with mixed Boolean and numerical variables.</a>
<a href="#1" id="1">These methods, termed Learning Modulo Theories, are based on a combination of structured-output SVMs and Satisfiability Modulo Theories.</a>
<a href="#2" id="2">In contrast to classical First-Order Logic, SMT allows to natively describe, and reason over, numerical variables and mixed logical/arithmetical constraints.</a>
<a href="#3" id="3">By leveraging the existing state-of-the-art OMT solvers, LMT is well-suited for dealing with hybrid constructive learning problems, avoiding the combinatorial explosion of the state space that would affect an equivalent FOL formulation.</a>
<a href="#4" id="4">Experimental results on both artificial and real world datasets show the potential of this approach.</a>
<a href="#5" id="5">The stairway application is a simple instance of a layout problem, where the task is to find an optimal layout subject to a set of constraints.</a>
<a href="#6" id="6">Automated or interactive layout synthesis has a broad range of potential applications, including urban pattern layout [52], decorative mosaics [53] and furniture arrangement [54], [55], [56].</a>
<a href="#7" id="7">Note that many spatial constraints can be encoded in terms of relationships between blocks [54].</a>
<a href="#8" id="8">Existing approaches typically design an energy function to be minimized by stochastic search.</a>
<a href="#9" id="9">Our approach suggests how to automatically identify the relevant constraints and their respective weights, and can accommodate hard constraints and exact search.</a>
<a href="#10" id="10">This is especially relevant for water-tight layouts [57], where the whole space needs to be filled (i.e. no gaps or overlaps) by deforming basic elements from a predetermined set of templates (as in residential building layout [58]).</a>
<a href="#11" id="11">The character drawing application shows how to learn symbolic representations from a handful of very noisy training instances.</a>
<a href="#12" id="12">Deep generative networks have been previously used for similar tasks, see for instance the work by Hinton [59] on generating images of digits with Deep Boltzmann Machines.</a>
<a href="#13" id="13">However, these methods do not learn symbolic representations for characters and generate bitmaps rather than vectorial representations.</a>
<a href="#14" id="14">Furthermore, they require thousands of training examples to be learned.</a>
<a href="#15" id="15">Recent extensions have been developed addressing the problem of learning from few [60] or even single [61] examples, but they focus on clean images of the target symbols.</a>
<a href="#16" id="16">Generally speaking, the LMT framework allows to introduce a learning stage in all application domains where SMT and OMT approaches have shown their potential, ranging, e.g., from hardware and software verification [62], [63], [39], to engineering of chemical reactions [64] and synthetic biology [65].</a>
<a href="#17" id="17">This work can be extended in a number of directions.</a>
<a href="#18" id="18">First, the current formulation assumes knowledge of the desired output for training examples.</a>
<a href="#19" id="19">This requirement can be loosened by introducting latent variables for the unobserved part of the output, to be maximized over during training [66].</a>
<a href="#20" id="20">Second, OMT is currently limited to quantifier free formulae and linear algebra for what concerns numeric theories.</a>
<a href="#21" id="21">The former requires to ground all predicates before performing inference, while the latter prevents the formulation of non-linear constraints, e.g. on areas and Euclidean distances.</a>
<a href="#22" id="22">Some attempts to extend SMT solvers to quantified formulae [48], [49], [50] and to non-linear arithmetic [67], [68], [69] have been presented in the literature; although the state of the art of these extensions is not yet satisfactory in terms of efficiency, since they can currently handle problems which are much smaller—in terms of size, number of variables and of arithmetical operations—than the quantifier-free problems with linear constraints at the reach of current SMT solvers, these techniques are evolving rapidly and promise rapid improvements in terms of performances in the next few years; hence, we can rather easily extend our framework in these directions as soon as the underlying SMT technology is mature enough.</a>
<a href="#23" id="23">Finally, LMT is currently focused on the task of finding the maximal configuration, and cannot compute marginal probabilities.</a>
<a href="#24" id="24">We are planning to introduce support for probability computation by leveraging ideas from weighted model counting [70].</a>
</body>
</html>