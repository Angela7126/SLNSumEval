<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:513">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have shown in this article that FO-rewritability of conjunctive queries and OWL 2 QL-ontologies does not yet mean that database systems can evaluate the rewritings as efficiently as they usually do for standard SQL queries.</a>
<a href="#1" id="1">Indeed, the rewritings can be prohibitively large and/or complex compared to the user queries.</a>
<a href="#2" id="2">We have also seen that the size of rewritings depends on the logical and non-logical means we want or are allowed to use.</a>
<a href="#3" id="3">These results clearly indicate that more theoretical and experimental research is needed to make the OBDA paradigm successful.</a>
<a href="#4" id="4">Here we briefly outline some important directions for future research that are related to this article.</a>
<a href="#5" id="5">On the one (theoretical) hand, we obviously need various conditions ensuring efficient OBDA, with first promising steps having already been made.</a>
<a href="#6" id="6">For example, a sufficient semantic-based condition on CQs and OWL 2 QL-ontologies that guarantees polynomial PE-rewritability has been obtained in [33].</a>
<a href="#7" id="7">It has also been demonstrated [30], [31] that there exist polynomial-size NDL-rewritings of CQs and OWL 2 QL-ontologies of depth 1 (whose chases do not contain two labelled nulls that are involved in some relation), as well as polynomial-size PE-rewritings of tree-shaped CQs (but not of arbitrary ones).</a>
<a href="#8" id="8">For tree-shaped Boolean CQs q, the problem ‘{a mathematical formula}(Σ,D)⊨q?’ turns out to be fixed-parameter tractable (with parameter {a mathematical formula}|q|) [31].</a>
<a href="#9" id="9">Moreover, any tree-shaped CQ and OWL 2 QL ontology with polynomially-many tree-witnesses have a polynomial-size NDL-rewriting [8].</a>
<a href="#10" id="10">A kind of preservation result has been obtained in [8]: if CQs in some class can be evaluated in polynomial time over plain databases, then answering CQs in that class over OWL 2 QL-ontologies without role inclusion axioms, that is, without tgds of the form {a mathematical formula}∀x,y(P(x,y)→R(x,y)), is also tractable (a polynomial-time NDL-rewriting algorithm is given for acyclic CQs).</a>
<a href="#11" id="11">These initial results open a way to a more comprehensive description of classes of queries and ontologies with and without polynomial rewritability.</a>
<a href="#12" id="12">To fully understand the complexity of OBDA with OWL 2 QL-ontologies, we also plan to investigate the size of rewritings over a fixed ontology and the size of rewritings of tree-shaped CQs and ontologies of bounded depth.</a>
<a href="#13" id="13">On the other (practical) hand, we have to study the structure of queries and ontologies that can typically be used in OBDA systems.</a>
<a href="#14" id="14">The recent experiments [20], [35], [46], [54], [52], [51] indicate that rewritings of the available ‘real-world’ CQs and ontologies are often of acceptable size and can be further optimised using various techniques.</a>
<a href="#15" id="15">However, the ontologies used in those experiments do not seem to be sufficiently representative.</a>
<a href="#16" id="16">It would also be interesting to evaluate performance of database systems on rewritings with additional quantifiers and special constants, which can be used to encode nondeterministic guesses in a compact way as in Section 4 (another rewriting of [33] employs a single special constant to guess whether an existentially quantified variable in the query is matched in {a mathematical formula}ΔD or in the labelled nulls).</a>
<a href="#17" id="17">Additional constants are also used in the combined approach to OBDA [40], [37], [38], [39], where they represent the labelled nulls in the database.</a>
</body>
</html>