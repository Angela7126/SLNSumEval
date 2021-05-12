<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    The co-occurrence test for non-monotonic inference.
   </title>
   <abstract>
    According to the co-occurrence test, q is (non-monotonically) inferrible from p if and only if q holds in all the reasonably plausible belief change outcomes in which p holds. A formal model is introduced that contains representations of both the co-occurrence test (for non-monotonic inference) and the Ramsey test (for conditionals). In this model, (non-nested) conditionals and non-monotonic inference satisfy the same logical principles. However, in spite of this similarity the two notions do not coincide. They should be carefully distinguished from each other.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      It is often assumed that the logic of non-monotonic inference coincides with that of “the flat (i.e. nonnested) fragment of a conditional logic” [17, p. 171]. Under the equally common assumption that conditionals are related to belief revision via the Ramsey test this means that the Ramsey test will be applicable to non-monotonic inference as well. This was also suggested by Makinson and Gärdenfors [19], according to whom “q follows non-monotonically from p” means that q holds if an “arbitrary but fixed background theory” (p. 189) is revised by p. Denoting that theory by K, belief revision by ⁎, and non-monotonic consequence by {a mathematical formula}|∼ we obtain:
     </paragraph>
     <list>
      <list-item>
       The Ramsey test for non-monotonic inference{a mathematical formula}p|∼q holds if and only if {a mathematical formula}q∈K⁎p.
      </list-item>
     </list>
     <paragraph>
      This proposal has been further investigated by Gärdenfors and Makinson [7], Wobcke [24], del Val [4], Rott [23, pp. 111–119], and many others. However conditionality and inferribility are distinct albeit related concepts. Even if both of them are connected with belief revision they need not be connected in the same way. It is the purpose of the present contribution to investigate what happens if we replace
     </paragraph>
     <list>
      <list-item>
       Ramsey's criterionIf the agent revises her beliefs by p, then she will believe that q.
      </list-item>
     </list>
     <paragraph>
      by the following alternative criterion:
     </paragraph>
     <list>
      <list-item>
       The co-occurrence criterionIf the agent comes to believe that p, then she will believe that q.
      </list-item>
     </list>
     <paragraph>
      The two criteria differ since an agent can come to believe in p not only as the result of revising her beliefs by p but also as the result of revising them by some other input. According to the co-occurrence criterion q has to be an element not only of {a mathematical formula}K⁎p but also of other belief sets containing p. The criterion concerns whether we will in general (given our present epistemic commitments) believe in q if we come to believe in p, not only whether we will do so in one singular case. This seems to make it better aligned with the notion of inferribility (in contradistinction to conditionality) than what Ramsey's criterion is.
     </paragraph>
     <paragraph>
      The co-occurrence test needs to be specified with respect to which of the belief sets containing p we should include in the analysis. A simple answer would be to include all potential belief change outcomes that contain p, i.e. all belief sets {a mathematical formula}K⁎r such that {a mathematical formula}p∈K⁎r. However, such an approach would be inadequate since it does not reflect the essential feature of non-monotonic reasoning that comparatively remote possibilities are left out of consideration. When you conclude from “Tweety is a bird” that “Tweety can fly” that is precisely because you do not take remote possibilities into account. The degree of remoteness referred to here is relative to the antecedent. Some of the possibilities that are too remote to be taken into account when considering “Tweety is a bird” would be quite close at hand when considering “Tweety is a bird who was born in Antarctica”.
     </paragraph>
     <paragraph>
      To sum this up, when evaluating non-monotonic inferences with p as the antecedent we have to consider not only {a mathematical formula}K⁎p but also other, reasonably plausible, p-containing belief sets. This amounts to the following test of inferribility:
     </paragraph>
     <list>
      <list-item>
       The co-occurrence test for non-monotonic inference{a mathematical formula}p|∼q holds if and only if q holds in all the p-satisfying belief change outcomes that are reasonably plausible as compared to other p-satisfying belief change outcomes.
      </list-item>
     </list>
     <paragraph>
      It should be noted that this criterion does not exclude the existence of some belief change outcome in which {a mathematical formula}p&amp;¬q holds. There can be some sentence r, less plausible than p, such that {a mathematical formula}p&amp;¬q holds in some or all of the r-satisfying belief change outcomes. (For an example, let p denote that Bitsy is a female mammal, q that Bitsy gives birth to live young, and r that Bitsy is a platypus.)
     </paragraph>
     <paragraph>
      One immediate difference between the Ramsey test and the co-occurrence test concerns the following property of conditionals: (The symbol ↣ will be used to denote “standard” Ramsey test conditionals.)
     </paragraph>
     <list>
      <list-item>
       Property CSIf p and q both hold then so does {a mathematical formula}p↣q.
      </list-item>
     </list>
     <paragraph>
      It is usually assumed that if {a mathematical formula}p∈K, then {a mathematical formula}K⁎p=K. From this it follows directly that a relation ↣ that is based on ⁎ via the Ramsey test will satisfy CS. However, an operation {a mathematical formula}|∼ based on the co-occurrence test will not in general do so. Even if {a mathematical formula}K⁎p=K and {a mathematical formula}q∈K there may be other reasonably plausible p-containing belief sets that do not contain q, and then {a mathematical formula}p|∼q will not hold.
     </paragraph>
     <paragraph>
      This difference between the two tests seems to correspond fairly well to a difference between conditionality and inferribility. To see that, let p denote that it rains in London today and q that Real Madrid wins the match they are playing tonight in Berlin. If I become convinced that both p and q are true, then I may arguably conclude that “if p then q”.{sup:1} However, it would be absurd to also conclude that “from p it can be inferred that q”.{sup:2} More generally speaking, inferribility seems to imply conditionality, but not the other way around.
     </paragraph>
     <paragraph>
      In Section 2 a framework for belief revision will be presented that is useful for our present purposes since it contains a straightforward representation of the differences in plausibility between belief sets. In Section 3, representations of conditionality (↣) according to the Ramsey test and non-monotonic inference ({a mathematical formula}|∼) according to the co-occurrence test will be introduced into that framework. In Section 4 a theorem is presented, showing that they have (nearly) the same logic. Finally, in Section 5 the interpretation of that theorem is discussed and it is argued that the two concepts should nevertheless be distinguished from each other.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      The formal framework
     </section-title>
     <paragraph>
      The analysis will be based on descriptor revision, a model of belief change that was introduced in [11]. Like most other formal models of belief change it employs a selection mechanism, but that mechanism does not operate on possible worlds or remainders but on the belief sets that are potential outcomes of change. Several such selection mechanisms are available [11], [12], [13]. Here the following simple construction will be used. A centrolinear model is a pair {a mathematical formula}〈X,≦〉, where {a mathematical formula}X is a set of logically closed sets (belief sets) in the object language ({a mathematical formula}L), and ≦ (with the strict part &lt;) is an ordering on {a mathematical formula}X, such that for any sentence p, there is a unique ≦-minimal element of {a mathematical formula}X that contains p.{sup:3}A centrolinear model is exhaustive if and only if {a mathematical formula}⋃X=L. Intuitively, {a mathematical formula}X consists of all the belief sets that are stable, coherent, or plausible enough to be outcomes of a belief change. ≦ represents degrees of plausibility or closeness.
     </paragraph>
     <paragraph>
      The use of a relation to guide choices among epistemic objects has a long tradition in formal epistemology. In his account of counterfactuals, David Lewis [18, p. 13] employed a notion of degrees of similarity to the actual world. The position of a possible world in Adam Grove's sphere system for belief change is said to represent its closeness to the set of worlds that are compatible with the agent's present beliefs [9, p. 159]. Peter Gärdenfors has proposed a criterion of informational economy, based on the idea that “when we, for some reason or other, change our beliefs we want to retain as much as possible of our old beliefs”, in particular the more important of them [6, p. 136]. These and many other approaches in formal epistemology are based on comparisons of epistemic objects in terms of how much they differ from the agent's current beliefs in the respects deemed important. In formal languages, such comparisons are expressed with a relation. As was noted in the AGM article, such a relation will have to be the same for all inputs since otherwise all choices among the epistemic objects would be trivially relational [1, p. 518].
     </paragraph>
     <paragraph>
      Many if not most approaches to belief change employ a relation to select among epistemic objects. However, there is a wide variation in the types of epistemic objects that these relations are applied to: possible worlds, (inclusion-maximal) remainders, sentences to remove etc. [15]. It is a weakness of many of these constructions that the relation operates on epistemic objects that are cognitively inaccessible, and in some cases the relation between the objects of selection and the actual outcome is far from transpicuous. To avoid these problems, this investigation will be performed in a framework where the relation operates directly on the potential belief outcomes themselves, rather than on intermediate objects to be used in a construction of the outcome. (For additional justification of this approach, see [11].) There are various ways in which such a relation can be interpreted. From a formal point of view, the crucial aspects of the construction are that the belief change is obtained by a direct choice among the potential belief sets, that this choice is relational, and that the relation is the same for all inputs. Informally, this relation (≦) will be referred to as a representation of the plausibility of the potential outputs. If an agent chooses the belief set X rather than the belief set Y as an outcome, then this can be interpreted as meaning that X is a more plausible belief set than Y. However, nothing hinges on this intuitive interpretation.
     </paragraph>
     <paragraph>
      The ≦-minimal element of {a mathematical formula}X is assumed to be the original belief set. Following convention in the belief revision literature it will be denoted K. (Thus, {a mathematical formula}K≦X for all {a mathematical formula}X∈X.) For simplicity we will assume that the strict part of ≦ is a wellordering with an order type that is either finite or ω.{sup:4}
     </paragraph>
     <paragraph>
      Belief revision has an obvious interpretation in this framework. When we revise by p we choose the ≦-minimal potential outcome:
     </paragraph>
     <list>
      <list-item>
       Belief revision in an exhaustive centrolinear model{a mathematical formula}K⁎p is the ≦-minimal element of {a mathematical formula}X that contains p.
      </list-item>
     </list>
     <paragraph>
      Three comments are in place before we proceed to introduce conditionality and inferribility into this framework.
     </paragraph>
     <paragraph>
      First, a centrolinear model has to be exhaustive in order for the success postulate for revision ({a mathematical formula}p∈K⁎p) to hold. Although good arguments can be given for relaxing that criterion [10], we will only consider exhaustive models here. In this way we avoid the rather uninteresting limiting cases of conditionality and inference with non-satisfiable antecedents ({a mathematical formula}p↣q and {a mathematical formula}p|∼q when the epistemic agent cannot be brought to believe that p is true).
     </paragraph>
     <paragraph>
      Secondly, the belief revision model presented here is a generalization of the “gold standard” in the belief revision literature [1], namely transitively relational partial meet revision (revision satisfying all the basic and supplementary AGM postulates). In other words, if ⁎ is a transitively relational partial meet revision on the belief set K, then there is a centrolinear model {a mathematical formula}〈X,≦〉 such that K is the ≦-minimal element of {a mathematical formula}X and that ⁎ coincides with the belief revision derived from {a mathematical formula}〈X,≦〉 according to the simple principle just referred to [14].
     </paragraph>
     <paragraph>
      Thirdly, the model proposed here is a fragment of descriptor revision, a framework that provides a unified approach to a wide variety of belief change operations. In descriptor revision the inputs are not sentences in the object language but instead metalinguistic sentences constructed with a belief predicate {a mathematical formula}B. For any sentence p in the object language, {a mathematical formula}Bp signifies that p is believed. A belief descriptor is a set of molecular combinations of such {a mathematical formula}B-sentences, for instance {a mathematical formula}{¬Bp,¬B¬p} means that neither p nor its negation is believed and {a mathematical formula}{Bp∨Bq} that either p or q is believed. With this notation, a wide variety of belief change operations can be subsumed under a unified operation ∘. Hence {a mathematical formula}K∘{¬Bp} is the ≦-minimal element of {a mathematical formula}X in which {a mathematical formula}¬Bp is satisfied (corresponding to contraction by p) and {a mathematical formula}K∘{¬Bp,Bq} is the ≦-minimal element of {a mathematical formula}X in which {a mathematical formula}{¬Bp,Bq} is satisfied (corresponding to replacement of p by q). In this more general framework, {a mathematical formula}K⁎p is of course an abbreviation of {a mathematical formula}K∘{Bp}.{sup:5}
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Introducing the two tests
     </section-title>
     <paragraph>
      We are now ready to introduce the two tests into the formal framework. The Ramsey test can be applied in the usual way:
     </paragraph>
     <list>
      <list-item>
       The Ramsey test in an exhaustive centrolinear model{a mathematical formula}p↣q holds if and only if {a mathematical formula}q∈K⁎p.
      </list-item>
     </list>
     <paragraph>
      For the co-occurrence test we need to identify, for each sentence p, a set of reasonably plausible belief sets containing p. We can assume that this set satisfies the following continuity property: If Z is a reasonably plausible p-containing set, and Y is a p-containing set such that {a mathematical formula}Y≦Z, then Y is a reasonably plausible p-containing set. Furthermore, we can assume that {a mathematical formula}K⁎p is the ≦-minimal p-containing set and that it is reasonably plausible.{sup:6} It then remains to identify, for each p, the ≦-outermost reasonably plausible p-containing set. We will assume for simplicity, that if {a mathematical formula}K⁎p1=K⁎p2 then the sets of plausible belief sets containing {a mathematical formula}p1 respectively {a mathematical formula}p2 have the same outer limit. This provides us with the following definition: The triple {a mathematical formula}〈X,≦,ℓ〉 is a dilated centrolinear model if and only if {a mathematical formula}〈X,≦〉 is a centrolinear model and ℓ (the delimiter) is a function from and to {a mathematical formula}X such that {a mathematical formula}X≦ℓ(X) for all {a mathematical formula}X∈X.{sup:7}A belief set {a mathematical formula}X∈X is self-limited according to ℓ if and only if {a mathematical formula}X=ℓ(X). (Another plausible property of ℓ is: If {a mathematical formula}X≦Y then {a mathematical formula}ℓ(X)≦ℓ(Y). It will not be needed here.)
     </paragraph>
     <paragraph>
      We can now express the co-occurrence test in a fully precise manner:
     </paragraph>
     <list>
      <list-item>
       The co-occurrence test in an exhaustive and dilated centrolinear model{a mathematical formula}p|∼q holds if and only if it holds for all {a mathematical formula}Y∈X that if {a mathematical formula}K⁎p≦Y≦ℓ(K⁎p) and {a mathematical formula}p∈Y, then {a mathematical formula}q∈Y.
      </list-item>
     </list>
     <paragraph>
      In the limiting case when all elements of {a mathematical formula}X are self-limited according to ℓ, the co-occurrence test coincides with the Ramsey test (and thus {a mathematical formula}|∼ coincides with ↣).
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The theorem
     </section-title>
     <paragraph label="Theorem">
      Let{a mathematical formula}〈X,≦,ℓ〉be an exhaustive and dilated centrolinear model such that the strict part of ≦ is a wellordering with an order type that is either finite or ω. Furthermore, let{a mathematical formula}|∼be the non-monotonic inference relation that is based on{a mathematical formula}〈X,≦,ℓ〉via the co-occurrence test. Then there is a centrolinear model{a mathematical formula}〈X′,≦′〉such that{a mathematical formula}|∼coincides with the conditional ↣ that is based on{a mathematical formula}〈X′,≦′〉via the Ramsey test.Furthermore, if K is the ≦-minimal element of{a mathematical formula}Xand{a mathematical formula}K′is the{a mathematical formula}≦′-minimal element of{a mathematical formula}X′, then{a mathematical formula}K′⊆K.
     </paragraph>
     <paragraph label="Proof">
      The proofs of the base case and the inductive step are so similar that only the latter will be given in detail.The inductive step: construction: We start with a series{a mathematical formula} and a delimiter {a mathematical formula}ℓn−1 according to which each of {a mathematical formula}Y1,…,Yk is self-limited. Let {a mathematical formula}Z be the set of subsets of {a mathematical formula}{Xn,Xn+1,Xn+2,…} such that (i) {a mathematical formula}Xn∈Z and (ii) there is some sentence p such that {a mathematical formula}K⁎p=Xn and {a mathematical formula}Z={Z|Xn≦Z≦ℓ(Xn) and p∈Z}.Case i, {a mathematical formula}Z=∅:Let {a mathematical formula}Xn=Y1,…,Yk,Xn+1,Xn+2,… and let {a mathematical formula}ℓn be the restriction of {a mathematical formula}ℓn−1 to the elements of the new series.Case ii, {a mathematical formula}Z≠∅: Let {a mathematical formula}Zˆ={⋂V|V∈Z} and let {a mathematical formula}Z1n,Z2n,…Zmnn be a list on which each element of {a mathematical formula}Zˆ appears exactly once, and such that if {a mathematical formula}Z,Z′∈Zˆ and {a mathematical formula}Z′⊂Z then {a mathematical formula}Z′ comes before Z on the list. (The existence of such a series follows from the order extension principle that follows from the axiom of choice, see [16, p. 19].)Now let:{a mathematical formula} and let {a mathematical formula}ℓn be such that (i) {a mathematical formula}ℓn(X)=X for all {a mathematical formula}X∈{Y1,…,Yk,Z1n…,Zmnn}, and (ii) {a mathematical formula}ℓn(X)=ℓn−1(X) for all {a mathematical formula}X∈{Xn+1,Xn+2,…}.The inductive step: verification: The verification is straightforward in Case i of the construction. In Case ii, let {a mathematical formula}|∼n−1 be the inference relation derivable from {a mathematical formula}〈Xn−1,ℓn−1〉, and let {a mathematical formula}|∼n be the inference relation derivable from {a mathematical formula}〈Xn,ℓn〉. We are going to show that for all p and q: {a mathematical formula}p|∼nq if and only if {a mathematical formula}p|∼n−1q. There are three cases.Case 1, {a mathematical formula}p∈⋃{Y1,…,Yk}: The desired result follows directly since {a mathematical formula}ℓn and {a mathematical formula}ℓn−1 coincide in this part of the series.Case 2, {a mathematical formula}p∉⋃{Y1,…,Yk} and {a mathematical formula}p∈Xn: Then {a mathematical formula}p|∼n−1q holds if and only if q holds in all elements of {a mathematical formula}{X|Xn≦X≦ℓn−1(Xn) and p∈X}, i.e. if and only if {a mathematical formula}q∈⋂{X|Xn≦X≦ℓn−1(Xn) and p∈X}. Now, {a mathematical formula}⋂{X|Xn≦X≦ℓn−1(Xn) and p∈X} is an element of {a mathematical formula}Zˆ, and moreover it is the leftmost element of {a mathematical formula}Zˆ that contains p. (This is because it is a proper subset of all other elements of {a mathematical formula}Zˆ that contain p.) It follows that {a mathematical formula}p|∼nq holds if and only if {a mathematical formula}q∈⋂{X|Xn≦X≦ℓn−1(Xn) and p∈X}, thus {a mathematical formula}p|∼nq holds if and only if {a mathematical formula}p|∼n−1q holds.Case 3, {a mathematical formula}p∉⋃{Y1,…,Yk,Xn}: The desired result follows directly since {a mathematical formula}ℓn and {a mathematical formula}ℓn−1 coincide in the subseries {a mathematical formula}Xn+1,Xn+2,… .  □
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>