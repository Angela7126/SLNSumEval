<html>
<head>
<meta name="TextLength" content="SENT_NUM:50, WORD_NUM:1306">
</head>
<body bgcolor="white">
<a href="#0" id="0">The semantics of N is almost completely determined by the application of defeasible inclusions and overriding.</a>
<a href="#1" id="1">The underlying monotonic logic forces only the elementary inclusions {a mathematical formula}NC⊑C.</a>
<a href="#2" id="2">In this respect, {a mathematical formula}DLN is more similar to rational closure than typicality logics, as the latter's monotonic fragment gives the typicality operator several nontrivial properties, such as (50) and the analogues of and 1 and or 2.</a>
<a href="#3" id="3">Note that (50) alone suffices to enforce CMT and CTT.</a>
<a href="#4" id="4">The application of defeasible inclusions and the overriding criterion of {a mathematical formula}DLN (with its new conflict handling approach) make {an inline-figure} a cumulative consequence relation.</a>
<a href="#5" id="5">The remaining rules, OR and RM, are sound under the additional assumption that consistent concepts have at least one normal instance.</a>
<a href="#6" id="6">Interestingly, in typicality logics, the existence of normal individuals is forced by the monotonic layer of the semantics, through the smoothness property of the normality relation.</a>
<a href="#7" id="7">Similarly, we plan to investigate variants of {a mathematical formula}DLN where the existence assumption is cast into the monotonic part of the semantics.</a>
<a href="#8" id="8">This should be done with some care, though: if too many individuals were forced to be normal, then the undesirable closed-world assumption effects described in [5], that affect typicality logics, might be introduced in {a mathematical formula}DLN.</a>
<a href="#9" id="9">The above results provide an immediate comparison with the consequence relations of Circumscribed DLs (that are preferential) and those of Default and Autoepistemic DLs (that are not cumulative).</a>
<a href="#10" id="10">Unfortunately, not much is known about the metalevel postulates satisfied by the DLs based on typicality, rational closure, and lexicographic closure (although the arguments put forward by Kraus, Lehmann and Magidor to support some of their postulates are general enough to apply in these contexts as well).</a>
<a href="#11" id="11">As of today, we only know that some typicality DLs and the rational closure of {a mathematical formula}ALC extended with the universal role U violate RM and OR, respectively (cf.</a>
<a href="#12" id="12">Section 7 and Appendix F), but this is not enough for an extended comparison at this level.</a>
<a href="#13" id="13">Next we studied the logical properties of N. With the goals of {a mathematical formula}DLN in mind, we argued that the boolean operators should not be unconditionally forced to commute with N and that only the inclusion {a mathematical formula}N¬C⊑¬NC should always hold.</a>
<a href="#14" id="14">Concerning the internalized version of the KLM postulates listed in Table 4, the refined semantics of {a mathematical formula}DLN unconditionally satisfies REF, LLE, and RW.</a>
<a href="#15" id="15">Example 8, Example 9, and Appendix C show that, in general, the other postulates of Table 4 conflict with either the principle that as many defaults as consistently possible should be applied, or with the principle that conflicts should be resolved in favor of higher priority axioms (with strong inclusions as top priority axioms).</a>
<a href="#16" id="16">Example 8 explains also that this clash between principles arises because {a mathematical formula}DLN relativizes the notion of typicality, that is, it does not assume that such notion is unique and concept-independent.</a>
<a href="#17" id="17">Moreover, as shown in Example 9, CM interferes with the novel conflict handling approach of {a mathematical formula}DLN.</a>
<a href="#18" id="18">In particular, if {a mathematical formula}NC is inconsistent, then CM forces all concepts {a mathematical formula}N(C⊓D) to be inconsistent, too, thereby preventing any resolution of the conflicts in C's prototype, no matter which piece of strong information D is added to C (cf.</a>
<a href="#19" id="19">Example 9).</a>
<a href="#20" id="20">This observation raises two interesting questions: Should internalized cautious monotonicity hold universally in a logic where unresolved conflicts yield inconsistent prototypes?</a>
<a href="#21" id="21">What is the right way of harmonizing the KLM postulates with the emerging knowledge engineering needs?</a>
<a href="#22" id="22">These issues could not be observed nor discussed in the original KLM framework, because it adopted the traditional, silent conflict removal approach.</a>
<a href="#23" id="23">Typicality DLs preserve both the default application principle underlying default logic and the analogue of Table 4 (with the possible exception of RM) by means of strong axioms, based on the assumption that the notion of typicality is concept-independent (cf.</a>
<a href="#24" id="24">Section 5 and Appendix B).</a>
<a href="#25" id="25">This assumption has some debatable consequences (cf.</a>
<a href="#26" id="26">Example 6) and the authors of [25] plan to investigate logics with multiple, relativized typicality relations.</a>
<a href="#27" id="27">However, as argued in Appendix B, the internalized postulates are so closely related to the concept-independence assumption that this objective is likely to be challenging.</a>
<a href="#28" id="28">The issues related to the novel conflict resolution approach, instead, are not visible in typicality logics, because in general the conflicts arising from multiple inheritance are silently removed.</a>
<a href="#29" id="29">{sup:20}</a>
<a href="#30" id="30">The DLs based on rational closure recalled in Section 2.4 satisfy the analogue of Table 4 where each inclusion {a mathematical formula}NC⊑D corresponds to a conditional {a mathematical formula}C{an inline-figure}D. In this case, the cost to be payed is the inability of applying defeasible axioms to role values (so our counterexamples cannot be modeled).</a>
<a href="#31" id="31">Of course, {a mathematical formula}DLN could be restricted in a similar way by allowing only N-free knowledge bases.</a>
<a href="#32" id="32">It is interesting to note that, with this restriction, the internalized postulates satisfied by the two frameworks become almost identical.</a>
<a href="#33" id="33">Using the refined semantics introduced in Sec.</a>
<a href="#34" id="34">6, the internalized versions of the KLM axioms illustrated in Table 4 are all satisfied with the partial exception of CM, that is guaranteed to apply only to consistent concepts {a mathematical formula}NC.</a>
<a href="#35" id="35">As discussed above, we leave it as an open question whether CM should be applied also to the inconsistent normality concepts produced by the novel conflict handling approach of {a mathematical formula}DLN.</a>
<a href="#36" id="36">We have also reported a second internalized version of the KLM axioms, centred around defeasible inclusions (cf.</a>
<a href="#37" id="37">Table 2), that has been technically studied in [5].</a>
<a href="#38" id="38">We enriched the illustration of these rules by highlighting their relationships with Lehmann's redefinition of default reasoning.</a>
<a href="#39" id="39">Using the notation of [30], a DI {a mathematical formula}C⊑nD corresponds to a default {a mathematical formula}(C:D).</a>
<a href="#40" id="40">Since defeasible inclusions have the same role as Reiter's defaults as well as Lehmann's, they have similar behavior: for all concepts {a mathematical formula}NE, a DI {a mathematical formula}C⊑nD is either overridden in {a mathematical formula}NE (and hence irrelevant) or it is applied; in the latter case, it yields the same effects as the corresponding classical inclusion {a mathematical formula}NE⊓C⊑D.</a>
<a href="#41" id="41">Accordingly, all the rules of Table 2 hold when their premises are not overridden, analogously to Lehmann's approach.</a>
<a href="#42" id="42">Summarizing the comparison of the above logics, the metalevel KLM postulates are still partly unexplored, while their internalized versions are currently satisfied at a cost.</a>
<a href="#43" id="43">In {a mathematical formula}DLN – whose goals are not completely aligned with those of the KLM framework – the dilemma is solved in favor of other desiderata, namely, full expressiveness (i.e. supporting role restriction to normal instances), relativized typicality, and tight correspondence between inconsistent prototypes and unresolved conflicts.</a>
<a href="#44" id="44">It is not yet clear to what extent the various incarnations of the KLM postulates can be harmonized with the above desiderata, nor what the ideal tradeoff should be, for each of the possible applications of nonmonotonic reasoning listed in [35].</a>
<a href="#45" id="45">The answer to these questions probably lies in the study of first-order versions of the KLM theory supporting the novel conflict handling approach.</a>
<a href="#46" id="46">Should the KLM postulates turn out to be inherently incompatible with some of the other requirements, Remark 1, Remark 2 suggest an interesting direction for further research, namely, designing a flexible logic whose inferences can be tuned to application needs by including suitable axioms in the knowledge base.</a>
<a href="#47" id="47">Finally, note that the postulates studied here do not directly relate {a mathematical formula}⊑n and N. Currently, the mutual relations between DIs and their effects on normality concepts can be partially and indirectly evinced from the results applying to Table 2, Table 4.</a>
<a href="#48" id="48">A complete account requires studying hybrid versions of the postulates, e.g. those obtained by taking the premises from Table 2 and the consequents from Table 4.</a>
<a href="#49" id="49">This investigation, that is needed to complete the analysis of {a mathematical formula}DLN, will be the subject of future work.</a>
</body>
</html>