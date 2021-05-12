<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:686">
</head>
<body bgcolor="white">
<a href="#0" id="0">The FLP answer set semantics [26], [27] has been widely used to define answer sets for different types of logic programs.</a>
<a href="#1" id="1">However, when being extended from normal logic programs to more general classes of logic programs, the FLP answer set semantics suffers from circular justifications.</a>
<a href="#2" id="2">The intuitive reason behind the circular justification problem is that the FLP answer set semantics does not induce a level mapping for its answer sets.</a>
<a href="#3" id="3">In this paper, we have overcome this shortcoming by enhancing the FLP answer set semantics with a suitable level mapping.</a>
<a href="#4" id="4">Inspired by the fact that each answer set I of a normal logic program Π under the standard answer set semantics has a level mapping that is induced by the fixpoint construction of I using the van Emden–Kowalski one-step provability operator {a mathematical formula}TΠI(S) for the Gelfond–Lifschitz reduct {a mathematical formula}ΠI, we define well-justified FLP answer sets I of a general logic program Π as fixpoints that are obtained by iteratively applying an extended van Emden–Kowalski operator {a mathematical formula}TfΠI(O,N) for the FLP reduct {a mathematical formula}fΠI; such FLP answer sets always have a level mapping and are thus free of circular justifications.</a>
<a href="#5" id="5">As a generic approach, the well-justified answer set semantics applies to logic programs with first-order formulas, logic programs with aggregates or c-atoms, and description logic programs.</a>
<a href="#6" id="6">It can easily be extended to other well-known types of logic programs, such as hex-programs, tightly coupled dl-programs and modular logic programs, by a suitable adjustment of the satisfaction relation.</a>
<a href="#7" id="7">To the best of our knowledge, the answer set semantics presented here is the first that is free of circular justifications for such general kinds of logic programs.</a>
<a href="#8" id="8">We have studied in depth the computational complexity of the FLP and the well-justified FLP answer set semantics for general logic programs.</a>
<a href="#9" id="9">For the major reasoning tasks, the FLP and the well-justified FLP answer set semantics fall in the same complexity classes.</a>
<a href="#10" id="10">This means that the well-justified FLP answer set semantics enhances the FLP answer set semantics with a level mapping formalism without affecting the worst-case complexity.</a>
<a href="#11" id="11">We have implemented the well-justified FLP answer set semantics by extending the ASP reasoner dlvhex, which currently can compute well-justified FLP answer sets for normal logic programs with aggregates, dl-programs and hex-programs.</a>
<a href="#12" id="12">We also conducted an experimental evaluation, which shows on benchmark problems the potential of the well-justified FLP answer set semantics in two respects: it not only employs a stronger notion of foundedness than the FLP answer set semantics, but it is also faster to compute (due to its fixpoint design, which is beneficial for answer set checking).</a>
<a href="#13" id="13">To find some FLP answer set, it thus seems attractive to start the search by finding a well-justified FLP answer set.</a>
<a href="#14" id="14">Open issues We focused in this article on logic programs with rules of the form {a mathematical formula}H←B, where H and B are first-order formulas, possibly with aggregates and/or dl-atoms.</a>
<a href="#15" id="15">Such logic programs do not cover disjunctive logic programs introduced in [34], which consist of rules of the form {a mathematical formula}A1|⋯|Al←B1∧⋯∧Bm∧¬C1∧⋯∧¬Cn, where each {a mathematical formula}Ai, {a mathematical formula}Bi and {a mathematical formula}Ci is an atom, and | is an epistemic disjunction operator that is different from the classical disjunction connective ∨ (see [31] for their differences).</a>
<a href="#16" id="16">As future work, it is interesting to extend the well-justified FLP answer set semantics to logic programs with rules of the form {a mathematical formula}H1|⋯|Hl←B, where B and each {a mathematical formula}Hi are first-order formulas.</a>
<a href="#17" id="17">In connection with this, it remains to deploy well-justified answer sets to further classes of logic programs.</a>
<a href="#18" id="18">On the computational side, a study of the decidability and computational complexity of first-order logic programs with formulas from various decidable fragments of first-order logic, under different notions of answer sets (including well-justified FLP answer sets) is an interesting issue.</a>
<a href="#19" id="19">Moreover, to develop methods for further improving the efficiency of the current implementation of the well-justified FLP answer set semantics is a challenging task.</a>
<a href="#20" id="20">Finally, it is of practical significance to exploit real-world applications where the well-justified FLP answer set semantics yields more intuitive results than the existing state-of-the-art answer set semantics.</a>
</body>
</html>