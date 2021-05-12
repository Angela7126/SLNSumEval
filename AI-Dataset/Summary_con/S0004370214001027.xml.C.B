<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:469">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper proposes novel algorithms for computing MESes.</a>
<a href="#1" id="1">The main contributions of the paper can be summarized as follows: (i) Adapting existing MUS extraction algorithms for MES extraction; (ii) Development of model rotation for MES extraction, and analysis of why clause set refinement cannot be applied; (iii) Reduction of MES to group-MUS extraction, which enables both model rotation and clause set refinement to be applied; (iv) Use of chunks for incremental reduction of MES to group-MUS extraction, aiming at reducing the hardness of instances of SAT when the formula includes the negation of a CNF formula; (v) Extension of the techniques to the group-MES computation problem; (vi) Development of a very effective technique for pruning redundant clauses using backbone computation; and (vii) Development of a solution for the independent certification of the correctness of computed MESes.</a>
<a href="#2" id="2">The experimental results indicate that the algorithms proposed in this paper improve the direct approach [3] significantly, more than doubling the number of instances that can be solved, and with significant performance gains, which can exceed two orders of magnitude when combined with backbone-based pruning.</a>
<a href="#3" id="3">The experimental evaluation carried out in the paper demonstrates that the developed algorithms are relevant for the practical applications of SAT.</a>
<a href="#4" id="4">Indeed, our results show that many real-world SAT instances have significant percentages of redundant clauses.</a>
<a href="#5" id="5">These findings clearly motivate revisiting the CNF encoding techniques used for generating these instances.</a>
<a href="#6" id="6">The extension of the MES algorithms to the group-MES computation problem proposed in this paper could enable the identification and the removal of redundant constraints in other domains, such as CSP [16], [17], [18], SMT [19], and Ontologies [20].</a>
<a href="#7" id="7">The proposed algorithms could be applied in the context of Quantified Boolean Formulas (QBF) [13] as a preprocessing technique (propositional simplifications have been successfully applied to QBF in the past [14], [15]).</a>
<a href="#8" id="8">Another interesting direction for future work is the development of efficient algorithms for the computation of Maximal Non-equivalent Subformulas (MNSes) [35], and Minimal Distinguishing Subformulas (MDSes), which are the generalizations of the well-known concepts of Maximal Satisfiable Subformulas (MSSes) and Minimal Correction Subset (MCSes).</a>
<a href="#9" id="9">An extension of the recently proposed effective algorithms for the computation of Minimal Correction Subsets (cf.</a>
<a href="#10" id="10">[72]) using the idea of a witness of equivalence is a possible approach to development of such algorithms.</a>
<a href="#11" id="11">The backbone-based technique enables removing certain redundant clauses that contain a backbone literal.</a>
<a href="#12" id="12">This technique could be extended to removing redundant clauses that contain a certain implicate of the formula, i.e. a clause implied by the formula (note that a backbone literal is an implicate of size 1).</a>
<a href="#13" id="13">However, implicate computation is in general very expensive [1] and therefore some discriminating heuristics would need to be devised.</a>
<a href="#14" id="14">Finally, the development of clause-selection and clause-partitioning heuristics for the MES computation problem is an additional future research direction from our work.</a>
</body>
</html>