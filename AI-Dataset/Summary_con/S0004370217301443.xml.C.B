<html>
<head>
<meta name="TextLength" content="SENT_NUM:50, WORD_NUM:1332">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have introduced reactive Multi-Context Systems (rMCSs), an adaptation of multi-context systems suitable for continuous reasoning in dynamic environments, with the objective to achieve two goals at the same time: integrating heterogeneous knowledge sources and opening knowledge-based systems for dynamic scenarios in the presence of incoming information.</a>
<a href="#1" id="1">For addressing the first goal, we have built rMCSs upon managed multi-context systems, inheriting their functionality for integrating heterogeneous knowledge sources, admitting also relevant operations on knowledge bases.</a>
<a href="#2" id="2">To accommodate the dynamic aspects, rMCSs are equipped with several extensions.</a>
<a href="#3" id="3">For one, bridge rules in our framework allow for input atoms to incorporate the information of multiple external streams of data.</a>
<a href="#4" id="4">Moreover, contrary to standard MCSs which possess only one type of bridge rules modeling the information flow which needs to be taken into account when equilibria are computed (or the operations that need to be applied in case of mMCSs), rMCS have an additional, different type of bridge rules, distinguished by the occurrence of the operator next in the head.</a>
<a href="#5" id="5">These rules are used to specify how the configuration of knowledge bases evolves whenever an equilibrium was computed providing the definition of equilibria streams which define the semantics of rMCSs over time.</a>
<a href="#6" id="6">The resulting formalism is indeed very expressive offering the capabilities to model the integration of heterogeneous knowledge in the presence of incoming information in different dynamic scenarios.</a>
<a href="#7" id="7">Based on a running example dealing with assisted living, we have demonstrated how to model such different dynamic scenarios using rMCSs and addressed several temporal aspects of modeling such as incorporating time on the object level and forgetting.</a>
<a href="#8" id="8">Other real world use cases of an even larger scale can be handled as well, such as the one described in [40] where the customs service needs to assess imported cargo for a variety of risk factors including terrorism, narcotics, food and consumer safety, pest infestation, tariff violations, and intellectual property rights.</a>
<a href="#9" id="9">Assessing this risk, even at a preliminary level, involves extensive knowledge about commodities, business entities, trade patterns, government policies and trade agreements.</a>
<a href="#10" id="10">Some of this knowledge may be external to a given customs agency: for instance the broad classification of commodities according to the international Harmonized Tariff System (HTS), or international trade agreements.</a>
<a href="#11" id="11">Other knowledge may be internal to a customs agency, such as lists of suspected violators or of importers who have a history of good compliance with regulations.</a>
<a href="#12" id="12">In [40], all this extensive knowledge is encoded in ontologies based on description logics and logic programming rules under the answer set semantics, and rMCSs naturally cover these formalisms as shown, e.g., in the running example.</a>
<a href="#13" id="13">In addition, they easily allow for the direct modular integration of information given in databases or for example business rules without the need for any prior conversion (which may not be readily available for arbitrary formalisms).</a>
<a href="#14" id="14">While some of the knowledge in this risk assessment scenario is relatively stable, much of it changes rapidly.</a>
<a href="#15" id="15">Changes are made not only at a specific level, such as knowledge about the expected arrival date of a shipment; but at a more general level as well.</a>
<a href="#16" id="16">For instance, while the broad HTS code for tomatoes (0702) does not change, the full classification and tariffs for cherry tomatoes for import into the US changes seasonally.</a>
<a href="#17" id="17">Here again, rMCSs provide mechanisms to easily make changes no matter if they are of a mere temporary nature or more persistent by using sensor data and the incorporation of knowledge via next respectively.</a>
<a href="#18" id="18">And, unlike [40], this flexibility is achieved without having to ensure or to test whether the integrated heterogeneous knowledge is organized in so-called layers.</a>
<a href="#19" id="19">Naturally, dealing with inconsistency is an important issue in dynamic settings where knowledge changes over time.</a>
<a href="#20" id="20">Indeed, we may face different kinds of inconsistencies when using rMCSs, e.g., in the form of inconsistent sensor input for which we discuss modeling-based solutions.</a>
<a href="#21" id="21">Another type of inconsistency is the absence of equilibria at certain time points which could potentially render an entire system useless.</a>
<a href="#22" id="22">We have addressed this problem first by showing sufficient conditions on the contexts and the bridge rules that ensure the existence of an equilibria stream.</a>
<a href="#23" id="23">In the cases where these conditions are not met, we have presented two possible solutions, one following an approach based on repairs – essentially the selective removal of bridge rules to regain an equilibria stream – and a second by relaxing the notion of equilibria stream to ensure that intermediate inconsistent states can be recovered.</a>
<a href="#24" id="24">Thus, rMCSs remain usable in the face of possible inconsistencies which may always occur in real use cases where knowledge and sensor data from different sources is integrated.</a>
<a href="#25" id="25">We have also addressed the non-determinism of rMCSs and discussed possibilities for avoiding it in situations where it is not desired.</a>
<a href="#26" id="26">To this end, we have also provided a well-founded stream semantics for rMCSs.</a>
<a href="#27" id="27">The study of computational complexity we conducted confirms worst case complexities similar to managed multi-context systems.</a>
<a href="#28" id="28">Hence, the additional integration of sensor data does not raise the worst case complexity of reasoning with heterogeneous knowledge integrated in multi-context systems.</a>
<a href="#29" id="29">In addition, the results confirm that if very efficient reasoning with such rich knowledge is essential, we can restrict to the well-founded stream.</a>
<a href="#30" id="30">This implies some restrictions on the permitted expressiveness, but we have argued that often these restrictions can be accommodated.</a>
<a href="#31" id="31">Finally, we compared our approach to related work.</a>
<a href="#32" id="32">Most importantly, we have shown that rMCSs can capture two relevant approaches in stream reasoning, namely LARS [7] and STARQL [37], thus showcasing that rMCSs are indeed “defined in the right way” for the intended integration of constant streams of data.</a>
<a href="#33" id="33">Regarding future work, several interesting lines of research can be considered.</a>
<a href="#34" id="34">First, we may want to extend rMCSs to enhance their applicability in an even wider set of scenarios.</a>
<a href="#35" id="35">Namely, one might adopt language constructs for expressing preferences in ASP such as optimization statements [24] or weak constraints [13], which assign a quality measure to equilibria.</a>
<a href="#36" id="36">This would allow us, e.g., to improve on the potentially high non-determinism when faced with several equilibria at one time point and thus avoid having to consider a possibly huge number of different equilibria.</a>
<a href="#37" id="37">We would also like to explore giving bridge rules access to the entire belief set of another context or an input and not just to one element.</a>
<a href="#38" id="38">A potential application would be counting, e.g., to ask if there was no sensor reading.</a>
<a href="#39" id="39">An alternative to deal with inconsistent states is to follow a paraconsistent approach, as proposed for hybrid knowledge bases in [21], [31].</a>
<a href="#40" id="40">Also, following the idea of EVOLP [2] as explored in [28], we could allow the bridge rules to change with time, strengthening the evolving and adaptation capabilities of rMCSs.</a>
<a href="#41" id="41">We would also like to establish bridges to asynchronous MCSs [19], a framework for loosely coupling knowledge representation formalisms whose semantics assumes that every context delivers output whenever available.</a>
<a href="#42" id="42">Finally, we may build on existing implementations of distributed (static) MCSs [14] for providing an implementation of rMCSs that handles the integration and evolution of distributed, heterogeneous knowledge with incoming streams of data and reasoning over such integration.</a>
<a href="#43" id="43">The framework introduced in this paper is highly abstract.</a>
<a href="#44" id="44">Needless to say this was our intention.</a>
<a href="#45" id="45">We wanted to capture a wide range of situations without imposing any restrictions on the KR formalisms used.</a>
<a href="#46" id="46">It is a matter of the application to choose the best suited formalisms to solve a specific task.</a>
<a href="#47" id="47">The downside of this generality, of course, is that the framework as such needs to be instantiated in various ways before it is ready-to-use.</a>
<a href="#48" id="48">In particular, we need to select the context logics and define the ways in which contexts and dynamic information interact by specifying adequate bridge rules.</a>
<a href="#49" id="49">We still believe our approach provides a valuable and to the best of our knowledge unique – solution to the problems outlined in the introduction, that is, problems which originate in the heterogeneous and dynamic nature of the information available in many challenging applications.</a>
</body>
</html>