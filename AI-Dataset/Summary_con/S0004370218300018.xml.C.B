<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:824">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have considered the description logic-based Contextualized Knowledge Repository (CKR) framework [12], [16], [17], [2], which serves to represent and reason about information in contexts that model individual views within a global environment.</a>
<a href="#1" id="1">Notably, the description of the global part of a CKR comprises both general information and knowledge about the structure of the contexts, which can be interrelated through extensional access among each other.</a>
<a href="#2" id="2">To address inconsistency due to inheritance of global information to contexts, we have presented an extension of CKRs with defeasible axioms whose instances can be overridden, viewing them as exceptions that are justified by provable evidence.</a>
<a href="#3" id="3">We have discussed some semantic properties of this approach for CKRs based on {a mathematical formula}SROIQ-RL (a description logic underlying the OWL RL profile) and we have introduced and studied the computational complexity of major reasoning tasks for CKRs.</a>
<a href="#4" id="4">As for realization, we have developed reasoning on CKRs as a translation into datalog under stable models semantics: such encoding, that matches the intrinsic complexity, follows a materialization calculus approach as in [20], [60], [1].</a>
<a href="#5" id="5">We then described a prototype implementation for such translation (called CKRew ), as well as experimental results.</a>
<a href="#6" id="6">Finally, we have compared the approach with related proposals for contextual reasoning and defeasibility in description logics.</a>
<a href="#7" id="7">Notably, reasoning by cases as it emerges in the well-known Nixon Diamond scenario, for instance, can be properly handled by it.</a>
<a href="#8" id="8">Our work contributes to a general program of providing extensions for formalisms based on description logics, where the use of database technology such as SQL and datalog play a prominent role, based on the fact that a rich body of work in this area is available, with ongoing improvements of which the reasoning systems on top can take advantage.</a>
<a href="#9" id="9">Nonetheless, however, future work is suggestive to address issues both on the computational and the modeling side.</a>
<a href="#10" id="10">As regards computation, in order to increase the practical applicability of the defeasible CKRs to larger sets of data, the translation described in this paper and its implementation need optimization.</a>
<a href="#11" id="11">One possible direction for this regards the study of alternative datalog translations that limit the need for materialization; furthermore, engines other than DLV supporting non-ground query answering, such as the recent s(ASP) solver,{sup:26} could be explored.</a>
<a href="#12" id="12">As discussed in Section 5.4, one possibility is to limit the use of tests environments only to CKRs that are not “safe” with respect to a direct reasoning on negative facts.</a>
<a href="#13" id="13">Orthogonal to this is to use, instead of a uniform (factual) CKR encoding, one where datalog rules are generated ad-hoc: this could offer the possibility to take advantage of internal optimizations of the used datalog engine.</a>
<a href="#14" id="14">Another possibility is to study different approaches, like e.g. abstraction refinement methods [61].</a>
<a href="#15" id="15">Moreover, such alternative translations might open the possibility to treat different or more expressive description logics (e.g. non-Horn fragments of {a mathematical formula}SROIQ).</a>
<a href="#16" id="16">This also includes the challenge to identify and study fragments of the CKR formalism in which reasoning is highly efficiently realizable; this includes, for instance, syntactic criteria which ensure justification safeness.</a>
<a href="#17" id="17">On the other hand, approximation of query results may be considered: the well-founded semantics can be readily applied to our datalog translation to be used as a tractable approximation.</a>
<a href="#18" id="18">On the modeling side, a natural continuation of our work is to allow defeasible axioms across local contexts, possibly along an explicit hierarchical relation between contexts (as the coverage relation [12]), or across knowledge modules, so as to allow for overriding in specific instances of context classes that are associated with such modules.</a>
<a href="#19" id="19">In this respect, a notion of priority across defeasible axioms in local contexts should be defined to resolve the clashes among instances of such axioms at different contexts (cf.</a>
<a href="#20" id="20">[31]); naturally, a respective priority order could be defined exactly as (or compatible to) the hierarchical order defined by the contexts coverage relation.</a>
<a href="#21" id="21">Another way to allow defeasible axioms in local contexts is to interpret them only inside the local context interpretation (i.e. CKRs become structures of locally defeasible knowledge bases): in this case, different interpretations of defeasibility can be adopted and compared (as, e.g., the semantics described in Section 7) and we may study the interaction of such “local defeasibility” with the interpretation of the current “global defeasible” axioms and its inheritance across local contexts.</a>
<a href="#22" id="22">Another direction would be to extend the current CKR definition and allow multiple global contexts: in particular, this may require a preference order among these global contexts, in order to decide clashes in the inheritance of defeasible axioms in local contexts.</a>
<a href="#23" id="23">Allowing defeasible axioms in local contexts also opens the discussion on how the eval operator should be interpreted when used as a local defeasible axiom, thus allowing a notion of “defeasible propagation” of knowledge along local contexts (cf.</a>
<a href="#24" id="24">mapping rules in [29]).</a>
<a href="#25" id="25">Furthermore, for interactions across contexts, currently the knowledge of the CKR is consistent: another direction would be to allow local inconsistencies in contexts, similarly to defeasible MCS [29].</a>
</body>
</html>