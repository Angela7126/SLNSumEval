<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Lost in translation: Language independence in propositional logic – application to belief change.
   </title>
   <abstract>
    While propositional logic is widely used as a representation framework for many AI applications, the concept of language independence in the propositional setting has not received much attention so far. In this paper, we define language independence for a propositional operator as robustness w.r.t. symbol translation. We motivate the need to focus on symbol translations of restricted types, introduce and study several families of translations of interest, and provide a number of characterization results. We also identify the computational complexity of recognizing symbol translations from those families. Then we investigate the robustness of belief merging, belief revision and belief update operators w.r.t. translations of different types. It turns out that some rational merging/revision/update operators are not guaranteed to offer the most basic (yet non-trivial) form of language independence.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In propositional logic, propositional symbols are the formal counterparts of propositions which are not analyzed (i.e., decomposed) within the language of the logic but can be arbitrarily sophisticated nevertheless. For instance, an (informal) proposition like “Johnʼs house is located north of the station” can be represented by a propositional symbol like jn. Provided that “north” means either “north-west” or “north-east”, the same informal proposition can also be represented by slightly more complex formulae, like {a mathematical formula}jnw⊕jne where ⊕ denotes the exclusive-or connective, and jnw means “Johnʼs house is located north-west of the station” and jne means “Johnʼs house is located north-east of the station”.
     </paragraph>
     <paragraph>
      The problem of which informal propositions of interest should be associated with propositional symbols is not ruled by logic since this is mainly a domain-dependent modeling issue. Thus, if “Johnʼs house is located north-west of the station” is also a proposition of interest, then representing “Johnʼs house is located north of the station” as {a mathematical formula}jnw⊕jne is an alternative to the representation of it by jn; on the other hand, one may consider that jn is a representation of “Johnʼs house is located north of the station”, and then represent “Johnʼs house is located north-west of the station” as {a mathematical formula}jn∧jw where jw is associated with “Johnʼs house is located west of the station”.
     </paragraph>
     <paragraph>
      Representing information as propositional formulae raises some expressiveness limitations. An informal proposition like “Johnʼs house is located north of the station” also refers to a number of terms like “John”, “house”, “station”, “being north of” used to build it, but which cannot be represented within propositional logic. Furthermore, when this informal proposition is stated, a number of implicit propositions which are logical consequences of it can be considered: “in the city where John lives there is a station”, “John lives in a house”, etc. Of course, whatever the informal proposition is represented as jn or as {a mathematical formula}jnw⊕jne, it is impossible to derive from the representation any of the implicit propositions above, because such propositions cannot be expressed as Boolean combinations of jn, jnw or jne. These limitations are not problematic if none of those propositions is of specific interest (and, again, this is not a logical concern but a domain-dependent one). What is important from a logical point of view is to make a representation choice so that every proposition of interest can be represented as a formula based on the chosen propositional symbols (otherwise the corresponding propositional language is not expressive enough w.r.t. the propositions of interest). Several representation choices are usually possible without questioning such an expressiveness issue.
     </paragraph>
     <paragraph>
      In artificial intelligence, propositional formulae are used to build propositional structures which represent propositional information. In applications where propositional logic is enough from a representation perspective, information processing can typically be modeled as a combination of queries (e.g., deducing some facts from the available beliefs or inferring some plausible conclusions from them) and transformations (e.g., forgetting some facts, revising or updating some beliefs, etc.). Propositional queries and propositional transformations can be formalized as propositional operators, which are mappings from propositional structures to propositional structures.
     </paragraph>
     <paragraph>
      In this paper, the language independence issue for propositional operators is addressed. Intuitively, a propositional operator Ω is language-independent if and only if whenever the representation language is modified in such a way that symbols in the original language correspond to formulae in the target language, if the input of Ω is modified so as to reflect the language change, then the output of Ω should be modified accordingly. Thus, language change can be modeled by symbol translations (i.e., substitutions), and language independence for a propositional operator is the faculty for it to be robust w.r.t. symbol translations.
     </paragraph>
     <paragraph>
      For instance, assume that mn represents the fact that “Maryʼs house is located north of the station”. If it is known that “Johnʼs house is located north of the station” (jn) and that “Johnʼs house is located north of the station” if and only if “Maryʼs house is located north of the station” ({a mathematical formula}jn⇔mn) since Mary and John live together, then one can deduce that “Maryʼs house is located north of the station”: mn is a logical consequence of {a mathematical formula}jn∧(jn⇔mn). If we consider another representation choice, where “Johnʼs house is located north of the station” is represented by {a mathematical formula}jnw⊕jne, then the same conclusion follows: from {a mathematical formula}(jnw⊕jne)∧((jnw⊕jne)⇔mn), the formula mn can still be deduced. Accordingly, the deduction operator is robust when the symbol translation σ such that {a mathematical formula}σ(jn)=jnw⊕jne is applied to the formula {a mathematical formula}jn∧(jn⇔mn).
     </paragraph>
     <paragraph>
      Clearly, such a notion of language independence should not be confused with the notion of syntax independence, which reflects the ability of an operator to be robust w.r.t. substitution of formulae (or sets of formulae) by equivalent formulae (or sets), a topic which got much attention in artificial intelligence. Quite surprisingly, the language independence issue in propositional logic has not received so far a systematic investigation, despite the fundamental nature of the issue and the significance of propositional languages in artificial intelligence.
     </paragraph>
     <paragraph>
      This paper is intended to fill the gap. The main contributions are as follows. First of all, language independence is defined as robustness w.r.t. symbol translations; we provide a number of characterization results for symbol translations, including a model-based characterization of translations in terms of injective, surjective relations over worlds. Then we motivate the need to focus on symbol translations of restricted types, i.e., satisfying some additional properties, which leads to refined notions of language independence. A model-based characterization for each of the refined notions is given, and we make precise how those notions are logically connected. We also identify the complexity of recognizing symbol translations satisfying properties of interest. Finally, the robustness of propositional belief change operators (revision, update and merging) w.r.t. translations of different types is investigated within our language independence setting. It turns out that only limited forms of language independence are satisfied in the general case by belief change operators. Especially, we show that rational revision (resp. update, merging) operators, i.e., those satisfying the AGM (resp. KM, IC) postulates, are not guaranteed to satisfy the most basic (yet non-trivial) form of language independence. We have also derived characterization results based on language independence for the distance-based IC merging operator {a mathematical formula}ΔdD,Σ (where the drastic distance {a mathematical formula}dD and sum as an aggregation function are used), as well as for the corresponding AGM revision and KM update operators; the obtained results show those rational change operators as the most robust operators in terms of language independence.
     </paragraph>
     <paragraph>
      The rest of the paper is organized as follows. After some formal preliminaries in Section 2, the notion of symbol translation and some characterization results are pointed out in Section 3. In Section 4 the notion of language independence is defined as robustness w.r.t. symbol translations, and several refinements of it are presented. Some complexity results are provided in Section 5. In Section 6, belief change operators are put in the setting and the level of language independence achieved by those operators is identified. Some related work is discussed in Section 7, before the conclusion. For ease of reading, proofs are reported in a final Appendix A.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Formal preliminaries
     </section-title>
     <paragraph>
      We consider a finite set PS of propositional symbols. For any subset X of PS, {a mathematical formula}PROPX denotes the propositional language over X defined in the usual way from X and a finite set of connectives, including the Boolean constants ⊤ (true) and ⊥ (false) and the standard connectives ¬, ∨, ∧, ⇒, ⇔, ⊕. For every formula α, {a mathematical formula}α+ denotes α and {a mathematical formula}α− denotes ¬α. For every formula α, {a mathematical formula}Var(α) is the set of propositional symbols occurring in α.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}X⊆PS. An interpretation ω (or a world) over X is a mapping from X to {a mathematical formula}{0,1}, which can also be viewed an element of {a mathematical formula}2X, i.e., as a subset of X such that for each {a mathematical formula}x∈X, x belongs to it if and only if {a mathematical formula}ω(x)=1. A canonical term associated with ω is a term over X (i.e., a conjunction of literals over X) such that for each {a mathematical formula}x∈X, x occurs as a literal of the term if {a mathematical formula}ω(x)=1, else ¬x occurs in it. To avoid heavy expressions, given a set X of propositional symbols, the notions of interpretation over X, element of {a mathematical formula}2X and canonical term will be confounded throughout the paper. For instance, if {a mathematical formula}X={p,q}, then the world ω over X such that {a mathematical formula}ω(p)=1 and {a mathematical formula}ω(q)=0 is also viewed as the set {a mathematical formula}{p} and as the term {a mathematical formula}p∧¬q. When a total, strict order &lt; over X is provided, any interpretation ω is also represented as a binary sequence. Thus, provided that {a mathematical formula}p&lt;q, the world ω above is also represented as the sequence 10.
     </paragraph>
     <paragraph>
      The notion of satisfaction of a formula is the usual one. ⊨ denotes logical entailment and ≡ denotes logical equivalence. A formula is said to be complete w.r.t. X iff it admits exactly one model over X, i.e., it is equivalent to a canonical term over X. {a mathematical formula}Mod(α) denotes the set of models over PS of a formula α.
     </paragraph>
     <paragraph>
      A formula α is said to be generated from a set C of connectives and a set Σ of formulae iff {a mathematical formula}α∈Σ or there exists a connective {a mathematical formula}c∈C of arity {a mathematical formula}n&gt;0 such that {a mathematical formula}α≡c(α1,…,αn) where each {a mathematical formula}αi ({a mathematical formula}i∈1,…,n) is generated from C and Σ. {a mathematical formula}{¬,∧} is said to be functionally complete w.r.t. X given a set Σ of formulae iff for every propositional formula α generated from {a mathematical formula}{¬,∧} and X, there exists a propositional formula β generated from {a mathematical formula}{¬,∧} and Σ such that {a mathematical formula}β≡α.
     </paragraph>
     <paragraph label="Definition 1">
      The following definition recalls some properties of binary relations which will be considered in the following: Properties of binary relationsLet {a mathematical formula}E,F be two sets and let R be a binary relation over {a mathematical formula}E×F. R is said to be:
     </paragraph>
     <list>
      <list-item label="•">
       injective if and only if({a mathematical formula}∀e,e′∈E, {a mathematical formula}∀f∈F, if {a mathematical formula}R(e,f) and {a mathematical formula}R(e′,f) then {a mathematical formula}e=e′);
      </list-item>
      <list-item label="•">
       functional if and only if({a mathematical formula}∀e∈E, {a mathematical formula}∀f,f′∈F, if {a mathematical formula}R(e,f) and {a mathematical formula}R(e,f′) then {a mathematical formula}f=f′);
      </list-item>
      <list-item label="•">
       surjective if and only if ({a mathematical formula}∀f∈F, {a mathematical formula}∃e∈E such that {a mathematical formula}R(e,f));
      </list-item>
      <list-item label="•">
       left-total if and only if ({a mathematical formula}∀e∈E, {a mathematical formula}∃f∈F such that {a mathematical formula}R(e,f)).
      </list-item>
     </list>
     <paragraph>
      Lastly, {a mathematical formula}|E| denotes the cardinality of any set E.
     </paragraph>
     <paragraph>
      In the following, we are interested in the robustness to symbol translations offered by propositional operators over propositional structures:
     </paragraph>
     <paragraph label="Definition 2">
      Propositional structureA propositional structure Σ over a set {a mathematical formula}X⊆PS of propositional symbols is a vector of sets of propositional formulae from {a mathematical formula}PROPX (only finite vectors and finite sets are considered). If n is the dimension of the vector, Σ is an n-propositional structure.
     </paragraph>
     <paragraph>
      Sets of formulae are interpreted conjunctively, so that two (finite) sets of formulae α and β are equivalent, denoted {a mathematical formula}α≡β, when the conjunction of formulae of α is equivalent to the conjunction of formulae of β. While a belief base is standardly defined as a (possibly infinite) set of formulae, it is considered as a finite set of formulae in the following.
     </paragraph>
     <paragraph>
      Two n-propositional structures {a mathematical formula}Σ=〈α1,…,αn〉 and {a mathematical formula}Σ′=〈α1′,…,αn′〉 are equivalent, denoted {a mathematical formula}Σ≡Σ′ iff {a mathematical formula}∀i∈1,…,n, we have {a mathematical formula}αi≡αi′.
     </paragraph>
     <paragraph label="Definition 3">
      Propositional operatorA propositional operator Ω is a mapping associating a propositional structure with a propositional structure.
     </paragraph>
     <paragraph>
      Many propositional queries and transformations can be viewed as propositional operators; here are a few examples of operators considered in the paper:
     </paragraph>
     <paragraph label="Example 1">
      <list>
       <list-item label="•">
        ded (deduction): {a mathematical formula}〈{α1,…,αn}, {a mathematical formula}{β}〉↦〈{⊤}〉 if β is a logical consequence of the belief base {a mathematical formula}{α1,…,αn}, and {a mathematical formula}〈{⊥}〉 otherwise;
       </list-item>
       <list-item label="•">
        ∘ (belief revision): {a mathematical formula}〈{α1,…,αn},{β}〉↦〈{β1,…,βm}〉 where {a mathematical formula}{β1,…,βm} is the belief base resulting from revising the belief base {a mathematical formula}{α1,…,αn} by β using the belief revision operator ∘;
       </list-item>
       <list-item label="•">
        ⋄ (belief update): {a mathematical formula}〈{α1,…,αn},{β}〉↦〈{β1,…,βm}〉 where {a mathematical formula}{β1,…,βm} is the belief base resulting from updating the belief base {a mathematical formula}{α1,…,αn} by β using the belief update operator ⋄;
       </list-item>
       <list-item label="•">
        Δ (belief merging): {a mathematical formula}〈{α11,…,αn(1)1},…,{α1p,…,αn(p)p},{μ}〉↦〈{β1,…,βm}〉 where {a mathematical formula}{β1,…,βm} is the belief base resulting from merging the vector of belief bases {a mathematical formula}〈{α11,…,αn(1)1},…,{α1p,…,αn(p)p}〉 using the belief merging operator Δ when μ is the integrity constraint.
       </list-item>
      </list>
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      On translations
     </section-title>
     <section label="3.1">
      <section-title>
       Definition
      </section-title>
      <paragraph>
       The key notion for defining notions of language independence is that of symbol translation; in the rest of the paper, when not stated explicitly, X and Y denote subsets of PS.
      </paragraph>
      <paragraph label="Definition 4">
       TranslationA (symbol) translation σ is a mapping from X to {a mathematical formula}PROPY, which is extended to a morphism (also denoted σ) from propositional structures over X to propositional structures over Y, defined inductively by (for any positive integer n):
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}σ(⊤)=⊤ and {a mathematical formula}σ(⊥)=⊥;
       </list-item>
       <list-item label="•">
        for every connective c of arity n, {a mathematical formula}σ(c(α1,…,αn))=c(σ(α1),…,σ(αn)),
       </list-item>
       <list-item label="•">
        {a mathematical formula}σ({α1,…,αn})={σ(α1),…,σ(αn)};
       </list-item>
       <list-item label="•">
        {a mathematical formula}σ(〈α1,…,αn〉)=〈σ(α1),…,σ(αn)〉.
       </list-item>
      </list>
      <paragraph>
       There is no need to assume any connection between X and Y, i.e., we may have {a mathematical formula}X∩Y=∅, but, conversely, this is not forbidden (e.g., we may have {a mathematical formula}X=Y). For instance, if σ is such that {a mathematical formula}X={p,q}, {a mathematical formula}Y={q,r}, {a mathematical formula}σ(p)=q and {a mathematical formula}σ(q)=¬q∨r, we have {a mathematical formula}σ(p∧¬q)=q∧¬(¬q∨r)≡q∧¬r. Finally, for every {a mathematical formula}Z⊆PS such that {a mathematical formula}X⊆Z, every symbol translation σ from {a mathematical formula}PROPYX is naturally extended as a symbol translation still denoted σ from {a mathematical formula}PROPY∪ZZ such that {a mathematical formula}∀z∈Z∖X, {a mathematical formula}σ(z)=z.
      </paragraph>
      <paragraph>
       A fundamental result in propositional logic when dealing with such symbol translations is the well-known substitution theorem, which results directly from the truth functionality of connectives and can be found in many textbooks (e.g., [1]):
      </paragraph>
      <paragraph label="Proposition 1">
       Substitution theoremLet α, β be two formulae from{a mathematical formula}PROPX. If{a mathematical formula}α≡βthen for every symbol translation σ of{a mathematical formula}PROPYX, we have{a mathematical formula}σ(α)≡σ(β).
      </paragraph>
      <paragraph>
       The following corollary presents alternative ways to state this theorem:
      </paragraph>
      <paragraph label="Corollary 1">
       <list>
        <list-item label="1.">
         Let{a mathematical formula}{α1,…,αn}be a finite set of formulae from{a mathematical formula}PROPX, and let β be a formula from{a mathematical formula}PROPX. We have{a mathematical formula}{α1,…,αn}⊨βif and only if for every symbol translation σ of{a mathematical formula}PROPYX, we have{a mathematical formula}
        </list-item>
        <list-item label="2.">
         ⊨α if and only if for every symbol translation σ of{a mathematical formula}PROPYX, we have{a mathematical formula}⊨σ(α). Similarly,{a mathematical formula}⊨¬αif and only if for every symbol translation σ of{a mathematical formula}PROPYX, we have{a mathematical formula}⊨¬σ(α).
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       Let us illustrate point 1 of Corollary 1 by considering the example provided in the introduction. We have {a mathematical formula}jn∧(jn⇔mn)⊨mn. Let {a mathematical formula}σ:jn↦(jnw⊕jne). Then {a mathematical formula}σ(jn∧(jn⇔mn))=(jnw⊕jne)∧((jnw⊕jne)⇔mn) implies {a mathematical formula}σ(mn)=mn.
      </paragraph>
      <paragraph>
       Obviously enough, in the general case, there is no direct logical connections between a formula α and the associated translated formula {a mathematical formula}σ(α). They can be logically independent, like {a mathematical formula}α=p and {a mathematical formula}σ(α)=q when {a mathematical formula}σ:p↦q is considered. It can also be the case that one of them implies the other one (consider {a mathematical formula}α=p, {a mathematical formula}σ1:p↦p∧q and {a mathematical formula}σ2:p↦p∨q) or that the formulae are jointly inconsistent (consider {a mathematical formula}α=p and {a mathematical formula}σ:p↦¬p). Actually, the only direct logical connections between α and {a mathematical formula}σ(α) are obtained in the specific case α is valid or α is contradictory (and are given by point 2 of Corollary 1). See also the forthcoming Proposition 4.
      </paragraph>
      <paragraph>
       Nevertheless, some indirect logical connections between α and {a mathematical formula}σ(α) exist, as stated by the following proposition:
      </paragraph>
      <paragraph label="Proposition 2">
       Let α be a formula from{a mathematical formula}PROPX. Let σ be a symbol translation from X to{a mathematical formula}PROPY. We have{a mathematical formula}⋀x∈X(x⇔σ(x))⊨α⇔σ(α).
      </paragraph>
      <paragraph>
       This proposition shows that α and {a mathematical formula}σ(α) are equivalent modulo the theory where each symbol in X is equivalent to its image by σ.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       A model-based characterization of symbol translations
      </section-title>
      <paragraph>
       We investigate now how a symbol translation looks like from a model-based point of view. We provide a characterization of every symbol translation σ from X to {a mathematical formula}PROPY (modulo equivalence) in terms of a binary relation over {a mathematical formula}2X×2Y.
      </paragraph>
      <paragraph label="Definition 5">
       Semantical mappingThe semantical mapping Ψ of symbol translations is the mapping associating with every symbol translation σ of {a mathematical formula}PROPYX the binary relation {a mathematical formula}Rσ⊆2X×2Y such that for every {a mathematical formula}ω∈2X, {a mathematical formula}ω′∈2Y, {a mathematical formula}(ω,ω′)∈Rσ if and only if {a mathematical formula}ω′⊨σ(ω). {a mathematical formula}Rσ(ω) denotes the set {a mathematical formula}{ω′∈2Y|Rσ(ω,ω′)}.
      </paragraph>
      <paragraph>
       Given a symbol translation σ the relation {a mathematical formula}Rσ provides us with a canonical representation of σ from a model-based point of view. Indeed, one can easily check that for every symbol translation σ from {a mathematical formula}PROPYX, for every interpretation ω over X, we have{a mathematical formula}
      </paragraph>
      <paragraph>
       The following model-based characterization of symbol translations shows that Ψ is a one-to-one correspondence; accordingly, its inverse mapping {a mathematical formula}Ψ−1 associates any injective, surjective relation R on {a mathematical formula}2X×2Y with a symbol translation {a mathematical formula}σR=Ψ−1(R):
      </paragraph>
      <paragraph label="Proposition 3">
       The semantical mapping Ψ of symbol translations is a one-to-one correspondence from{a mathematical formula}PROPYX/≡, the set of all symbol translations (modulo equivalence), to the set of all injective, surjective relations over{a mathematical formula}2X×2Y. Its inverse mapping{a mathematical formula}Ψ−1associates for every subsets{a mathematical formula}X,Yof PS, an injective, surjective relation R over{a mathematical formula}2X×2Ywith a representative symbol translation, denoted{a mathematical formula}σR, such that for every propositional symbol{a mathematical formula}x∈X,{a mathematical formula}
      </paragraph>
      <paragraph>
       When R is not functional, the associated symbol translation {a mathematical formula}σR “refines” some worlds over X by making each one of them correspond to several worlds over Y. By contrast, when R is not left-total, {a mathematical formula}σR “discards” some worlds over X, namely no world over Y corresponds to them.
      </paragraph>
      <paragraph label="Example 2">
       Let {a mathematical formula}X={x,y}, {a mathematical formula}Y={p,q,r} and let R be the injective, surjective relation R over {a mathematical formula}2X×2Y defined as {a mathematical formula}R({x,y})={{p,q,r},{p}}, {a mathematical formula}R({x})={{p,q}}, {a mathematical formula}R({y})={{p,r},{q,r},{q}, {a mathematical formula}{r},{}} and {a mathematical formula}R({})={}. Then by Proposition 3, R provides a canonical representation of the symbol translation {a mathematical formula}Ψ−1(R)=σR:x↦p∧(q∨¬r);y↦¬p∨¬q∨r. One can easily check that for every formula α from {a mathematical formula}PROPX, {a mathematical formula}σR(α)≡⋁{R(ω)|ω⊨α}. Fig. 1 provides a graphical representation of the relation R, a formula {a mathematical formula}α=¬x∨¬y from {a mathematical formula}PROPX and its translation {a mathematical formula}σR(α)≡¬p∨(q⊕r) from {a mathematical formula}PROPY.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      On language independence
     </section-title>
     <section label="4.1">
      <section-title>
       Language independence based on translations
      </section-title>
      <paragraph>
       We are now ready to define language independence as robustness w.r.t. symbol translations satisfying some properties:
      </paragraph>
      <paragraph label="Definition 6">
       Language independenceLet P be a property on symbol translations from X to {a mathematical formula}PROPY. A propositional operator Ω associating an m-propositional structure with an n-propositional structure is P-language independent if and only if for every n-propositional structure Σ over X, for every translation {a mathematical formula}σPROPYX satisfying P, we have{a mathematical formula} When P always holds (i.e., P is a valid condition), every symbol translation σ can be considered, and Ω is said to be ⊤-language independent.
      </paragraph>
      <paragraph>
       Fig. 2 provides a graphical representation of the behavior of a language-independent propositional operator.
      </paragraph>
      <paragraph>
       In general, P characterizes what should be preserved (or dually what can be lost) when a symbol translation is applied. Indeed, replacing in a uniform way propositional symbols by formulae may lead to question a number of properties which hold for propositional symbols but can be lost when formulae are considered. Especially, unlike general formulae, propositional symbols are neither inconsistent nor valid, conjunction of possibly negated but distinct propositional symbols is always consistent, and they are complete formulae, i.e., propositional symbols are enough to generate a full propositional language over them whenever a functionally complete set of connectives (as {a mathematical formula}{¬,∧}) is considered.
      </paragraph>
      <paragraph>
       Formally, we focus on the following properties:
      </paragraph>
      <paragraph label="Definition 7">
       Properties of symbol translationsA symbol translation σ from {a mathematical formula}X={x1,…,xn} to {a mathematical formula}PROPY satisfies:
      </paragraph>
      <list>
       <list-item label="•">
        SIN (symbol insensitivity) if and only if σ is a bijection from X to Y;
       </list-item>
       <list-item label="•">
        TPR (triviality prevention) if and only if {a mathematical formula}∀x∈X, {a mathematical formula}σ(x) is consistent but not valid;
       </list-item>
       <list-item label="•">
        AIP (atom independence preservation) if and only if{a mathematical formula}∀s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈Xσ(xi)si is consistent;
       </list-item>
       <list-item label="•">
        BAP (belief amount preservation) if and only if for every complete formula α from {a mathematical formula}PROPX, {a mathematical formula}σ(α) is a complete formula from {a mathematical formula}PROPY.
       </list-item>
       <list-item label="•">
        FCP (functional completeness preservation) if and only if {a mathematical formula}{¬,∧} is functionally complete w.r.t. Y given {a mathematical formula}{σ(x)|x∈X};
       </list-item>
       <list-item label="•">
        REV (reversibility) if and only if there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}∀x∈X, {a mathematical formula}θ(σ(x))≡x.
       </list-item>
      </list>
      <paragraph>
       ⊤-language independence is hard to be satisfied since it leads to consider as admissible the symbol translations which do not preserve anything from the input propositional structure, except trivialities (tautologies and contradictions) which are always kept. Indeed, we have the following result:
      </paragraph>
      <paragraph label="Proposition 4">
       Let α be a formula of{a mathematical formula}PROPXand β a formula of{a mathematical formula}PROPY. If α is neither valid nor inconsistent, then there exists a symbol translation{a mathematical formula}σ∈PROPYXsuch that{a mathematical formula}σ(α)≡β.
      </paragraph>
      <paragraph>
       This motivates the need to restrict the set of admissible translations.
      </paragraph>
      <paragraph>
       SIN-language independence asks the choice of the symbols names to be non-significant. This independence property is highly expected. However, as we will see in the following, it is not always guaranteed for revision/merging/update operators.
      </paragraph>
      <paragraph>
       The rationale for TPR is to set aside translations which leads to replace a symbol, which is in essence neither valid nor inconsistent, by a formula which would be valid or inconsistent.
      </paragraph>
      <paragraph>
       The principle of AIP is as follows: at start, all the symbols of PS are logically independent, which means that {a mathematical formula}∀s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈PSxisi is consistent; for instance, if {a mathematical formula}PS={x,y}, then {a mathematical formula}¬x∧¬y is consistent. If another representation choice is made, such an independence should be preserved. For instance, {a mathematical formula}x↦p∨q;y↦¬p∨q does not satisfy AIP since {a mathematical formula}¬(p∨q)∧¬(¬p∨q) is inconsistent; contrastingly, {a mathematical formula}x↦p;y↦q∨r satisfies AIP.
      </paragraph>
      <paragraph>
       BAP-language independence requires admissible translations to leave unchanged the number of models of formulae, i.e., every formula admits the same number of models in both the initial and the target languages. For example, {a mathematical formula}x↦p⇔q;y↦p satisfies BAP, while {a mathematical formula}x↦p;y↦q∨r does not.
      </paragraph>
      <paragraph>
       FCP asks for the preservation of functional completeness. At start, taking any fully expressive set of connectives (like {a mathematical formula}{¬,∧}) proves enough to represent every Boolean function over any subset X of PS. When another representation choice is made, it is expected that any functionally complete set of connectives proves enough to represent every Boolean function over Y given that the set of “atoms” is now {a mathematical formula}{σ(x)|x∈X}. As an example, consider again {a mathematical formula}x↦p∨q;y↦¬p∨q; this symbol translation does not satisfy FCP since p cannot be defined using {a mathematical formula}{¬,∧} when the set of “atoms” is {a mathematical formula}{p∨q,¬p∨q}; on the other hand, {a mathematical formula}x↦p⇔q;y↦p satisfies FCP: both p and q can be defined using {a mathematical formula}{¬,∧} when the set of atoms is {a mathematical formula}{p⇔q,p}; this is obvious for p, and for q, we have {a mathematical formula}q≡(p⇔q)⇔p.{sup:1} Clearly enough, {a mathematical formula}{¬,∧} is functionally complete w.r.t. Y given {a mathematical formula}{σ(x)|x∈X} if and only if for every formula β of {a mathematical formula}PROPY, there exists a formula α of {a mathematical formula}PROP{σ(x)|x∈X} such that {a mathematical formula}α≡β. This is equivalent to state that for every {a mathematical formula}y∈Y, there exists a formula {a mathematical formula}αy of {a mathematical formula}PROP{σ(x)|x∈X} such that {a mathematical formula}αy≡y (i.e., Y is definable from {a mathematical formula}{σ(x)|x∈X}), which is in its turn equivalent to state that for every {a mathematical formula}y∈Y, there exists a formula {a mathematical formula}αy of {a mathematical formula}PROPX such that {a mathematical formula}σ(αy)≡y.
      </paragraph>
      <paragraph>
       The idea underlying REV is the one of reversibility. The intuition is that nothing important is lost in a symbol translation when the translation can be reversed, which requires the target language of the translation to be at least as expressive as the initial language. For instance, {a mathematical formula}x↦p∨q;y↦¬p∨q does not satisfy REV since the system of equations {a mathematical formula}{p∨q≡x,¬p∨q≡y} with variables p and q has no solution over {a mathematical formula}PROP{x,y}. Contrastingly, {a mathematical formula}σ:x↦p⇔q;y↦p satisfies REV since {a mathematical formula}θ:p↦y,q↦y⇔x is such that {a mathematical formula}θ(σ(x))≡x and {a mathematical formula}θ(σ(y))≡y.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Connections between notions of language independence
      </section-title>
      <paragraph>
       Clearly enough, none of the properties above is trivial in the sense that it would be satisfied by every (or by no) symbol translation. Thus, the identity translation {a mathematical formula}σ:x↦x satisfies all the properties above, while {a mathematical formula}σ:x↦⊥, {a mathematical formula}y↦p∨q satisfies none of them.
      </paragraph>
      <paragraph>
       Discovering connections between notions of language independence boils down to study the dependencies between the properties of translations.
      </paragraph>
      <paragraph>
       First, while based on quite different intuitions, it turns out that REV and AIP are the same property:
      </paragraph>
      <paragraph label="Proposition 5">
       REV and AIP are equivalent.
      </paragraph>
      <paragraph>
       Now, most of the remaining dependencies w.r.t. the other properties can be easily derived from the following proposition which provides, in a similar fashion as to Proposition 3, for every property P on symbol translations listed above, a model-based characterization of symbol translations satisfying P, or more precisely, for any subsets {a mathematical formula}X,Y of PS, a characterization of the quotient set {a mathematical formula}PROPYX/≡ satisfying P in terms of some specific injective, surjective relations over {a mathematical formula}2X×2Y.
      </paragraph>
      <paragraph label="Proposition 6">
       Let σ be a symbol translation from{a mathematical formula}PROPYXand{a mathematical formula}Rσbe its semantical mapping:
      </paragraph>
      <list>
       <list-item label="1.">
        σ satisfies AIP if and only if{a mathematical formula}Rσis left-total;
       </list-item>
       <list-item label="2.">
        σ satisfies BAP if and only if{a mathematical formula}Rσis a one-to-one correspondence;
       </list-item>
       <list-item label="3.">
        σ satisfies FCP if and only if{a mathematical formula}Rσis functional;
       </list-item>
       <list-item label="4.">
        σ satisfies SIN if and only if{a mathematical formula}Rσis a one-to-one correspondence which is decomposable, i.e., there exists a bijection{a mathematical formula}ηRσfrom X to Y defined by{a mathematical formula}∀x∈X,{a mathematical formula}∀y∈Y,{a mathematical formula}ηRσ(x)=yif and only if{a mathematical formula}{Rσ(ω)|ω∈2X,ω⊨x}={ω′|ω′∈2Y,ω′⊨y};
       </list-item>
       <list-item label="5.">
        σ satisfies TPR if and only if{a mathematical formula}∀x∈X,{a mathematical formula}∃ω,ω′∈2X,{a mathematical formula}ω⊨x,{a mathematical formula}ω′⊨¬x,{a mathematical formula}Rσ(ω)≠∅and{a mathematical formula}Rσ(ω′)≠∅.
       </list-item>
      </list>
      <paragraph>
       From Proposition 6, one can easily derive some of the following dependencies between properties of symbol translations:
      </paragraph>
      <paragraph label="Proposition 7">
       SIN implies BAP. BAP implies FCP. BAP also implies REV, which implies TPR. Each implication is strict (i.e., the converse does not hold). Moreover, if a symbol translation satisfies REV and FCP, then it satisfies BAP. Lastly, FCP does not imply and is not implied by any of REV or TPR.
      </paragraph>
      <paragraph>
       These logical implications between properties of symbol translations are exhaustively represented through the implication graph given in Fig. 3, where for the sake of clarity, arrows coming from the reflexivity and the transitivity of implication are omitted.
      </paragraph>
      <paragraph>
       Other notable consequences of Proposition 6 are listed in the following corollary:
      </paragraph>
      <paragraph label="Corollary 2">
       Let σ be a symbol translation of{a mathematical formula}PROPYX.
      </paragraph>
      <list>
       <list-item label="1.">
        σ satisfies AIP (or, equivalently, REV) only if{a mathematical formula}|X|⩽|Y|;
       </list-item>
       <list-item label="2.">
        σ satisfies BAP only if{a mathematical formula}|X|=|Y|;
       </list-item>
       <list-item label="3.">
        σ satisfies FCP only if{a mathematical formula}|X|⩾|Y|;
       </list-item>
       <list-item label="4.">
        if{a mathematical formula}|X|=|Y|then AIP, BAP and FCP are equivalent.
       </list-item>
      </list>
      <paragraph>
       The first point comes from the fact that when R is an injective, surjective relation over {a mathematical formula}2X×2Y which is left-total, then {a mathematical formula}R−1 is a surjective mapping from {a mathematical formula}2Y to {a mathematical formula}2X, hence {a mathematical formula}|X|⩽|Y|. The second point is obvious since a one-to-one correspondence between two finite sets {a mathematical formula}2X and {a mathematical formula}2Y may exist only if the two sets have the same number of elements, i.e., precisely when {a mathematical formula}|X|=|Y|. The third point comes from the fact that when R is an injective, surjective relation over {a mathematical formula}2X×2Y which is functional, then {a mathematical formula}R−1 is an injective mapping from {a mathematical formula}2Y to {a mathematical formula}2X, hence {a mathematical formula}|X|⩾|Y|. The last point comes from the fact that every injective, surjective relation over {a mathematical formula}2X×2Y where X and Y are finite sets such that {a mathematical formula}|X|=|Y|, is left-total if and only if it is functional.
      </paragraph>
      <paragraph>
       To conclude this section, let us now turn to the concept of syntax independence. Syntax independence at the belief base level has received much attention so far (see e.g., [3], [4], [5], [6]). It can be stated as follows when propositional operators are considered:
      </paragraph>
      <paragraph label="Definition 8">
       Syntax independenceA propositional operator Ω which associates a m-propositional structure with a given n-propositional structure is said to be syntax-independent if and only if whenever {a mathematical formula}〈α1,…,αn〉≡〈α1′,…,αn′〉, we also have {a mathematical formula}Ω(〈α1,…,αn〉)≡Ω(〈α1′,…,αn′〉).
      </paragraph>
      <paragraph>
       It turns out that the concept of syntax independence and the concept of P-language independence (whatever P among the choices we considered) are logically independent, in the sense that one can find propositional operators satisfying both properties, while other operators satisfy none of them and still other operators satisfy only one of them:
      </paragraph>
      <paragraph label="Proposition 8">
       The concept of syntax independence and the concept of P-language independence for propositional operators are logically independent.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      The complexity of recognizing translations
     </section-title>
     <paragraph>
      In this section, we consider the problem of determining whether a given symbol translation satisfies one of the properties considered in the previous section. Such an issue has to be addressed each time a representation change is expected, given a propositional operator which is known as P-language independent. Indeed, a symbol translation is acceptable in this case only if it satisfies P.
     </paragraph>
     <paragraph>
      First, we show that FCP amounts to a definability issue (see [7] for details):
     </paragraph>
     <paragraph label="Proposition 9">
      {a mathematical formula}σ:{x1,…,xn}→PROPYsatisfies FCP if and only if{a mathematical formula}⋀i=1n(zi⇔σ(xi))defines Y in terms of{a mathematical formula}{z1,…,zn}, where{a mathematical formula}{z1,…,zn} ∩ {a mathematical formula}Y=∅.
     </paragraph>
     <paragraph>
      We have also derived the results reported in Proposition 10 (symbol translations {a mathematical formula}σ∈PROPYX are supposed to be represented extensionally as {a mathematical formula}〈X,Y,{(x,σ(x))|x∈X}〉). This proposition shows that the complexity of deciding whether a given symbol translation satisfies one of the properties of interest varies with the property under consideration between (deterministic) polynomial time and the second level of the polynomial hierarchy.
     </paragraph>
     <paragraph label="Proposition 10">
      <list>
       <list-item label="1.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies SIN is in{a mathematical formula}P.
       </list-item>
       <list-item label="2.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies TPR is{a mathematical formula}NP-complete.
       </list-item>
       <list-item label="3.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies FCP is{a mathematical formula}coNP-complete in the general case. The problem is in{a mathematical formula}Pif{a mathematical formula}|X|&lt;|Y|.
       </list-item>
       <list-item label="4.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies BAP is{a mathematical formula}coNP-complete in the general case. The problem is in{a mathematical formula}Pif{a mathematical formula}|X|≠|Y|.
       </list-item>
       <list-item label="5.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies REV (or, equivalently, AIP) is{a mathematical formula}Π2p-complete. The problem is{a mathematical formula}coNP-complete if{a mathematical formula}|X|=|Y|, and is in{a mathematical formula}Pif{a mathematical formula}|X|&gt;|Y|.
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      Interestingly, the problem of determining whether a given symbol translation {a mathematical formula}σ∈PROPYX satisfies REV is a specific case of the following problem of propositional matching (given 2n formulae {a mathematical formula}α1,β1,…,αn,βn, determining whether there exists a substitution θ from {a mathematical formula}X=⋃i=1nVar(αi) to {a mathematical formula}PROPY with {a mathematical formula}Y=⋃i=1nVar(βi) such that for {a mathematical formula}i∈1,…,n, {a mathematical formula}θ(αi)≡βi). Hence, point 5 of Proposition 10 shows that the problem of propositional matching is at least as hard as the problem of Boolean unification with constants [8].
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Language independence for belief change
     </section-title>
     <section label="6.1">
      <section-title>
       Preliminaries on belief revision, belief merging and belief update
      </section-title>
      <paragraph>
       Belief merging operators aim at defining a belief base (the merged base) which represents the beliefs of a group of agents given their individual belief bases, and some integrity constraints. Formally, a (belief) base K denotes the set of beliefs of an agent, it is a finite set of propositional formulae, interpreted conjunctively. A profile {a mathematical formula}E=〈K1,…,Kn〉 is a finite and non-empty vector of consistent bases representing the beliefs from the group of n agents involved in the merging process. When {a mathematical formula}E=〈K1,…,Kn〉, the dimension of E is n. The assumption that all bases forming a profile are consistent is standard [9], since an inconsistent belief base is often considered to provide no information for the merging process. In general, agents are expected to play equivalent roles in the merging process, so that a profile {a mathematical formula}E=〈K1,…,Kn〉 is also viewed as a multi-set {a mathematical formula}{K1,…,Kn}. The integrity constraints μ are represented by a formula. ⊔ denotes the union operator for multi-sets, ∖ denotes the difference operator for multi-sets, and ≡ the equivalence of profiles (two multi-sets of bases are equivalent when there is a bijection between them so that each base from a profile is equivalent to its image in the other profile). ⋀E denotes the conjunction of the belief bases of E, i.e., {a mathematical formula}⋀E=⋀Ki∈EKi. Then, the notation {a mathematical formula}ω⊨E stands for {a mathematical formula}ω⊨⋀E. Lastly, a preorder ⩽ over a set S is a reflexive, transitive relation over S. For each preorder ⩽, ≃ denotes the corresponding indifference relation and &lt; the corresponding strict ordering.
      </paragraph>
      <paragraph>
       A merging operator Δ is a mapping associating a formula μ (representing the integrity constraints) and a profile E with a new base {a mathematical formula}Δμ(E). Let us recall the standard logical properties which are expected for belief merging operators [9]:
      </paragraph>
      <paragraph label="Definition 9">
       IC merging operatorA merging operator Δ is an IC merging operator if and only if for every formula μ, for every profile E, {a mathematical formula}E1, {a mathematical formula}E2 and for every consistent belief base {a mathematical formula}K1, {a mathematical formula}K2, it satisfies the following postulates (so-called IC postulates):
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}Δμ(E)⊨μ;
       </list-item>
       <list-item>
        If μ is consistent, then {a mathematical formula}Δμ(E) is consistent;
       </list-item>
       <list-item>
        If {a mathematical formula}⋀E∧μ is consistent, then {a mathematical formula}Δμ(E)≡⋀E∧μ;
       </list-item>
       <list-item>
        If {a mathematical formula}E1≡E2 and {a mathematical formula}μ1≡μ2, then {a mathematical formula}Δμ1(E1)≡Δμ2(E2);
       </list-item>
       <list-item>
        If {a mathematical formula}K1⊨μ, {a mathematical formula}K2⊨μ and {a mathematical formula}Δμ(〈K1,K2〉)∧K1 is consistent, then {a mathematical formula}Δμ(〈K1,K2〉)∧K2 is consistent;
       </list-item>
       <list-item>
        {a mathematical formula}Δμ(E1)∧Δμ(E2)⊨Δμ(E1⊔E2);
       </list-item>
       <list-item>
        If {a mathematical formula}Δμ(E1)∧Δμ(E2) is consistent, then {a mathematical formula}Δμ(E1⊔E2)⊨Δμ(E1)∧Δμ(E2);
       </list-item>
       <list-item>
        {a mathematical formula}Δμ1(E)∧μ2⊨Δμ1∧μ2(E);
       </list-item>
       <list-item>
        If {a mathematical formula}Δμ1(E)∧μ2 is consistent, then {a mathematical formula}Δμ1∧μ2(E)⊨Δμ1(E)∧μ2.
       </list-item>
      </list>
      <paragraph>
       Each IC merging operator corresponds to a syncretic assignment [9]:
      </paragraph>
      <paragraph label="Definition 10">
       Syncretic assignmentA syncretic assignment is a mapping which associates with every profile E a total preorder {a mathematical formula}⩽E{sup:2} over worlds and such that for every profile E, {a mathematical formula}E1, {a mathematical formula}E2 and for every consistent belief base {a mathematical formula}K1, {a mathematical formula}K2, it satisfies the following conditions:
      </paragraph>
      <list>
       <list-item label="(1)">
        If {a mathematical formula}ω⊨E and {a mathematical formula}ω′⊨E, then {a mathematical formula}ω≃Eω′;
       </list-item>
       <list-item label="(2)">
        If {a mathematical formula}ω⊨E and {a mathematical formula}ω′⊭E, then {a mathematical formula}ω&lt;Eω′;
       </list-item>
       <list-item label="(3)">
        If {a mathematical formula}E1≡E2, then {a mathematical formula}⩽E1=⩽E2;
       </list-item>
       <list-item label="(4)">
        If {a mathematical formula}ω⊨K1, then {a mathematical formula}∃ω′⊨K2ω′⩽〈K1,K2〉ω;
       </list-item>
       <list-item label="(5)">
        If {a mathematical formula}ω⩽E1ω′ and {a mathematical formula}ω⩽E2ω′, then {a mathematical formula}ω⩽E1⊔E2ω′;
       </list-item>
       <list-item label="(6)">
        If {a mathematical formula}ω&lt;E1ω′ and {a mathematical formula}ω⩽E2ω′, then {a mathematical formula}ω&lt;E1⊔E2ω′.
       </list-item>
      </list>
      <paragraph label="Theorem 1">
       (See[9].) A merging operator Δ is an IC merging operator if and only if there exists a syncretic assignment associating every profile E with a total preorder{a mathematical formula}⩽Esuch that for every formula μ,{a mathematical formula}
      </paragraph>
      <paragraph>
       Distance-based merging operators are characterized by a distance (actually, a pseudo-distance is enough, i.e., triangular inequality is not mandatory) between worlds and an aggregation function f (a mapping associating with a tuple of non-negative real numbers a non-negative real number) [10]:
      </paragraph>
      <paragraph label="Definition 11">
       Distance-based merging operatorLet d be a distance between worlds and f be an aggregation function. The merging operator {a mathematical formula}Δd,f is defined for every profile E and every formula μ by {a mathematical formula}Mod(Δμd,f(E))=min(Mod(μ),⩽E) where the total preorder {a mathematical formula}⩽E over worlds induced by E is defined by:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ω⩽Eω′ if and only if d(ω,E)⩽d(ω′,E);
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(ω,E)=fK∈E(d(ω,K));
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(ω,K)=minω′⊨Kd(ω,ω′).{sup:3}
       </list-item>
      </list>
      <paragraph>
       Usual distances are {a mathematical formula}dD, the drastic distance ({a mathematical formula}dD(ω,ω′)=0 if {a mathematical formula}ω=ω′ and 1 otherwise), which corresponds to the infinity-norm distance, also known as Chebyshev distance, and {a mathematical formula}dH the Hamming distance ({a mathematical formula}dH(ω,ω′)=n if ω and {a mathematical formula}ω′ differ on n variables), which corresponds to the 1-norm distance, also referred to as the Manhattan distance. Note that some distance-based operators are not IC merging ones (conditions of non-decreasingness, minimality, identity, symmetry, composition and decomposition must be satisfied by f in the general case, see [10] for details), but taking advantage of “usual” aggregation functions as Σ, Gmax (leximax), etc. leads to IC merging operators.
      </paragraph>
      <paragraph>
       Belief revision operators can be viewed as belief merging operators restricted to singleton profiles, so that a revision operator ∘ is a mapping associating a base K and a formula μ with a new base {a mathematical formula}K∘μ. Note that in contrast with IC merging operators which consider that all the bases forming a profile are consistent, revision operators do not require bases K to be consistent; however, this slight difference between belief merging operators and belief revision operators does not affect the results presented in the rest of this section.
      </paragraph>
      <paragraph>
       AGM postulates [11], [12] for belief revision are direct counterparts of IC postulates for singleton profiles. Stricto sensu, the following postulates are not the AGM ones but those pointed out by Katsuno and Mendelzon in [12]; since they are equivalent to the AGM ones when a finite propositional logic is considered and belief sets are represented by the deductive closures of formulae, this misuse of language is harmless; it also prevents from any confusion with the KM postulates dedicated to belief update:
      </paragraph>
      <paragraph label="Definition 12">
       AGM revision operatorA revision operator ∘ is an AGM revision operator if and only if for every formula μ, {a mathematical formula}μ1, {a mathematical formula}μ2, for every base K, {a mathematical formula}K1, {a mathematical formula}K2, it satisfies the following postulates:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}K∘μ⊨μ;
       </list-item>
       <list-item>
        If {a mathematical formula}K∧μ is consistent, then {a mathematical formula}K∘μ≡K∧μ;
       </list-item>
       <list-item>
        If μ is consistent, then {a mathematical formula}K∘μ is consistent;
       </list-item>
       <list-item>
        If {a mathematical formula}K1≡K2 and {a mathematical formula}μ1≡μ2, then {a mathematical formula}K1∘μ1≡K2∘μ2;
       </list-item>
       <list-item>
        {a mathematical formula}(K∘μ1)∧μ2⊨K∘(μ1∧μ2);
       </list-item>
       <list-item>
        If {a mathematical formula}(K∘μ1)∧μ2 is consistent, then {a mathematical formula}K∘(μ1∧μ2)⊨(K∘μ1)∧μ2.
       </list-item>
      </list>
      <paragraph>
       For instance, the AGM postulate (R2) (resp. {a mathematical formula}(R3)) for belief revision corresponds to the IC postulate (IC2) (resp. (IC1)). Then, as to the case of IC merging operators, AGM revision operators can be characterized in terms of total preorders over worlds. Indeed, each AGM revision operator corresponds to a faithful assignment [12], that is, a syncretic assignment (cf. Definition 10) restricted to singleton profiles.{sup:4}
      </paragraph>
      <paragraph label="Definition 13">
       Faithful assignmentA faithful assignment is a mapping which associates with every base K a preorder {a mathematical formula}⩽K over worlds and such that for every base K, {a mathematical formula}K1, {a mathematical formula}K2, it satisfies the following conditions:
      </paragraph>
      <list>
       <list-item label="(1)">
        If {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊨K, then {a mathematical formula}ω≃Kω′;
       </list-item>
       <list-item label="(2)">
        If {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊭K, then {a mathematical formula}ω&lt;Kω′;
       </list-item>
       <list-item label="(3)">
        If {a mathematical formula}K1≡K2, then {a mathematical formula}⩽K1=⩽K2.
       </list-item>
      </list>
      <paragraph label="Theorem 2">
       (See[12].) A revision operator ∘ is an AGM revision operator if and only if there exists a faithful assignment associating every base K with a total preorder{a mathematical formula}⩽Kover worlds such that for every formula μ,{a mathematical formula}
      </paragraph>
      <paragraph>
       Noteworthy, AGM revision operators include Dalalʼs revision operator {a mathematical formula}∘Dal[11] and the drastic revision operator {a mathematical formula}∘D. Dalalʼs revision operator {a mathematical formula}∘Dal (respectively, the drastic revision operator {a mathematical formula}∘D) corresponds for any aggregation function f to the distance-based merging operator {a mathematical formula}ΔdH,f (resp. {a mathematical formula}ΔdD,f) when restricted to singleton profiles.{sup:5} The corresponding faithful assignments associate respectively with every base K the total preorders {a mathematical formula}⩽KH and {a mathematical formula}⩽KD over worlds such that {a mathematical formula}ω⩽KHω′ if and only if {a mathematical formula}dH(ω,K)⩽dH(ω′,K) and {a mathematical formula}ω⩽KDω′ if and only if {a mathematical formula}dD(ω,K)⩽dD(ω′,K). In a simpler way, {a mathematical formula}∘D can be defined for every base K and every formula μ as:{a mathematical formula}
      </paragraph>
      <paragraph>
       A last family of change operators that we consider in this paper is that of belief update operators [13]. Like a revision operator, an update operator ⋄ is a mapping associating a base K and a formula μ with a new base {a mathematical formula}K⋄μ. However, update operators perform a model-wise change, whereas belief revision operators make a change at the whole base level (see [13] for a discussion). The expected behavior for update operators is captured through the following set of KM postulates [13]:
      </paragraph>
      <paragraph label="Definition 14">
       KM update operatorAn update operator ⋄ is a KM update operator if and only if for every formula μ, {a mathematical formula}μ1, {a mathematical formula}μ2, for every base K, {a mathematical formula}K1, {a mathematical formula}K2, it satisfies the following postulates:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}K⋄μ⊨μ;
       </list-item>
       <list-item>
        If {a mathematical formula}K⊨μ, then {a mathematical formula}K⋄μ≡K;
       </list-item>
       <list-item>
        If K is consistent and μ is consistent, then {a mathematical formula}K⋄μ is consistent;
       </list-item>
       <list-item>
        If {a mathematical formula}K1≡K2 and {a mathematical formula}μ1≡μ2, then {a mathematical formula}K1⋄μ1≡K2⋄μ2;
       </list-item>
       <list-item>
        {a mathematical formula}(K⋄μ1)∧μ2⊨K⋄(μ1∧μ2);
       </list-item>
       <list-item>
        If {a mathematical formula}(K⋄μ1)⊨μ2 and {a mathematical formula}(K⋄μ2)⊨μ1, then {a mathematical formula}K⋄μ1≡K⋄μ2;
       </list-item>
       <list-item>
        If K is a complete base, then {a mathematical formula}(K⋄μ1)∧(K⋄μ2)⊨K⋄(μ1∨μ2);
       </list-item>
       <list-item>
        {a mathematical formula}(K1∨K2)⋄μ≡(K1⋄μ)∨(K2⋄μ).
       </list-item>
      </list>
      <paragraph>
       We have the following characterization theorem for KM update operators in terms of partial preorders over worlds:
      </paragraph>
      <paragraph label="Theorem 3">
       (See[12].) An update operator ⋄ is a KM update operator if and only if there exists a faithful assignment associating every interpretation ω with a preorder{a mathematical formula}⩽ωsuch that for every base K and formula μ,{a mathematical formula}
      </paragraph>
      <paragraph>
       KM update operators include Forbusʼ operator {a mathematical formula}⋄F[14], which is the distance-based update operator based on the Hamming distance, and the drastic update operator {a mathematical formula}⋄D, which is the distance-based update operator based on the drastic distance. Accordingly, the corresponding faithful assignments associate respectively with every world ω the total preorders {a mathematical formula}⩽ωH and {a mathematical formula}⩽ωD over worlds such that {a mathematical formula}ω′⩽ωHω″ if and only if {a mathematical formula}dH(ω′,ω)⩽dH(ω″,ω) and {a mathematical formula}ω′⩽ωDω″ if and only if {a mathematical formula}dD(ω′,ω)⩽dD(ω″,ω). In a simpler way, the drastic update operator {a mathematical formula}⋄D can be defined for every base K and every formula μ as:{a mathematical formula}
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Language independence for belief change
      </section-title>
      <paragraph>
       As a case study, we have investigated how some belief change operators from the literature are language-independent.
      </paragraph>
      <paragraph>
       As Proposition 4 suggests, ⊤-language independence is hardly achieved by operators which have to deal with jointly inconsistent (but typically individually consistent) propositional information, while avoiding trivialization. Surprisingly, KM postulates for update operators are compatible with ⊤-language independence, as stated by the following proposition:
      </paragraph>
      <paragraph label="Proposition 11">
       The KM drastic update operator{a mathematical formula}⋄Dis ⊤-language independent.
      </paragraph>
      <paragraph>
       However, no similar result holds for AGM revision operators and IC merging operators. Actually, focusing on translations satisfying TPR or FCP is not enough as well, since AGM revision operators and IC merging operators are nor TPR-language independent, nor FCP-language independent; more precisely:
      </paragraph>
      <paragraph label="Proposition 12">
       Let P be a property on symbol translations which does not imply AIP, i.e., there exists a symbol translation satisfying P but not satisfying AIP. Then no belief revision operator ∘ satisfying (R2) and (R3) and no belief merging operator Δ satisfying{a mathematical formula}(IC1)and{a mathematical formula}(IC2)is P-language independent.
      </paragraph>
      <paragraph>
       Hence, for AGM revision operators and IC merging operators one needs to consider forms of language independence that are at least as restrictive as AIP-language independence. We first investigate whether AIP-language independence is compatible with AGM and IC postulates. The following proposition gives a positive answer to this question; actually, it turns out that there is exactly one AGM revision operator (resp. exactly one IC merging operator, exactly one KM update operator) that is AIP-language independent; furthermore, this AGM revision operator (resp. IC merging operator, KM update operator) is the unique AGM revision operator (resp. IC merging operator, KM update operator) that is BAP-language independent:
      </paragraph>
      <paragraph label="Proposition 13">
       <list>
        <list-item label="1.">
         The distance-based merging operator{a mathematical formula}ΔdD,Σ, based on the drastic distance{a mathematical formula}dDand on the aggregation function Σ, is the only IC merging operator that is AIP-language independent; it is also the only IC merging operator that is BAP-language independent;
        </list-item>
        <list-item label="2.">
         The drastic revision operator{a mathematical formula}∘Dis the only AGM revision operator that is AIP-language independent; it is also the only AGM revision operator that is BAP-language independent;
        </list-item>
        <list-item label="3.">
         The drastic update operator{a mathematical formula}⋄Dis the only KM update operator that is AIP-language independent; it is also the only KM update operator that is BAP-language independent.
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       Note that point 1 of Proposition 13 actually holds for every merging operator {a mathematical formula}ΔdD,f, based on the drastic distance {a mathematical formula}dD and on an aggregation function f satisfying non-decreasingness, minimality, identity, symmetry and strict monotony, since all these operators are equal to {a mathematical formula}ΔdD,Σ[15].
      </paragraph>
      <paragraph>
       Proposition 13 can be considered as a representation theorem for the three operators {a mathematical formula}ΔdD,Σ, {a mathematical formula}∘D, and {a mathematical formula}⋄D. Note that in [16] Konieczny et al. provide a first full axiomatic characterization of the distance-based merging operator {a mathematical formula}ΔdD,Σ in terms of independence property to rationalization by expansion. Indeed, {a mathematical formula}ΔdD,Σ is the only IC merging operator Δ satisfying the following property: for every profile {a mathematical formula}〈K1,…,Km〉, for every formula μ,{a mathematical formula}Proposition 13 provides a further characterization of the distance-based operator {a mathematical formula}ΔdD,Σ in terms of language independence. It shows that, under IC postulates, the notion of independence to rationalization by expansion and the one of AIP-language independence (or, BAP-language independence) coincide.
      </paragraph>
      <paragraph>
       Let us now go back to the language independence issue. Since there is only one belief revision operator, one belief merging operator and one belief update operator that is BAP-language independent, in order to investigate how other belief change operators behave, one needs to consider a weaker form of language independence. As SIN-language independence asks the choice of the symbols names to be non-significant, this property is highly expected for belief change operators. However, quite surprisingly, SIN-language independence is not always guaranteed by rational operators:
      </paragraph>
      <paragraph label="Proposition 14">
       There exist belief revision (resp. belief merging, belief update) operators which satisfy all AGM postulates (resp. all IC postulates, all KM postulates) but are not SIN-language independent.
      </paragraph>
      <paragraph>
       This calls for three further axioms expressing such a form of language independence ((SIN-R) for belief revision, (SIN-M) for belief merging, and (SIN-U) for belief update), stating respectively that for every bijective symbol translation σ from PS to PS:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}σ(K∘μ)≡σ(K)∘σ(μ);
       </list-item>
       <list-item>
        {a mathematical formula}σ(Δμ(E))≡Δσ(μ)(σ(E));
       </list-item>
       <list-item>
        {a mathematical formula}σ(K⋄μ)≡σ(K)⋄σ(μ).
       </list-item>
      </list>
      <paragraph>
       Those axioms complement the ones related to syntax independence ((R4) for belief revision, (U4) for belief update and (IC3) for belief merging) and seem highly desirable. Actually, the distance-based belief change operators, based on “standard distances” (like the drastic distance and the Hamming one), satisfy those axioms. More generally, when {a mathematical formula}PS={x1,…,xn} contains n atoms, let a distance d over interpretations over X be decomposable when there exists a mapping {a mathematical formula}fd:Rn→R symmetric in each argument and a mapping {a mathematical formula}gd:{0,1}×{0,1}→R such that {a mathematical formula}d(ω1,ω2)=fd(gd(ω1(x1)),ω2(x1)),…,gd(ω1(xn),ω2(xn)). We have:
      </paragraph>
      <paragraph label="Proposition 15">
       Every belief change operator based on a decomposable distance is SIN-language independent.
      </paragraph>
      <paragraph>
       Clearly enough, both {a mathematical formula}dD and {a mathematical formula}dH are decomposable; for the drastic distance {a mathematical formula}dD, we can take {a mathematical formula}fdD=max and {a mathematical formula}gdD(x,y)=0 if {a mathematical formula}x=y, =1 otherwise; for the Hamming distance {a mathematical formula}dH, we can take {a mathematical formula}fdH=Σ and {a mathematical formula}gdH=gdD. Thus, as a direct consequence of Proposition 15, Dalalʼs revision operator {a mathematical formula}∘Dal and Forbusʼ update operator {a mathematical formula}⋄F are SIN-language independent.
      </paragraph>
      <paragraph>
       The following proposition shows that the converse of Proposition 15 does not hold for AGM revision operators and KM update operators; that is, there exist rational belief revision/update operators that are not based on a decomposable distance and are SIN-language independent. We actually prove the stronger result:
      </paragraph>
      <paragraph label="Proposition 16">
       There exist belief revision (resp. belief update) operators which satisfy all AGM postulates (resp. all KM postulates), are not distance-based operators but satisfy{a mathematical formula}(SIN-R) (resp.{a mathematical formula}(SIN-U)).
      </paragraph>
      <paragraph>
       The question remains open for belief merging operators which satisfy all IC postulates, i.e., it is not known whether there exist IC merging operators which are not based on a decomposable distance and satisfy (SIN-M). In fact, as far as we know the existence of IC merging operators which are not distance-based is still an open issue; however, given any property P on revision/update operators, in general it is easy to exhibit an AGM revision operator (resp. a KM revision operator) which is not distance-based and satisfy P; this is due to the weakness of conditions (1–3) of the faithful assignment which do not require any dependence between the preorders {a mathematical formula}⩽K and {a mathematical formula}⩽K′, for any base K, {a mathematical formula}K′ with {a mathematical formula}K≢K′.
      </paragraph>
      <paragraph>
       Table 1 summarizes the results presented in the section with a systematic picture of the dependencies between rational belief change operators and the different forms of language independence of interest in this paper; for each family of belief change operators and each property P on symbol translations, it provides some conditions on the sets O of rational change operators satisfying P-language independence. In the table, IC (resp. AGM, KM) denotes the set of all IC merging (resp. AGM revision, KM update) operators. The obtained characterization results are complete ones, except for SIN-language independence.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Other related work
     </section-title>
     <paragraph>
      Independence is well-known as a key notion in many domains within artificial intelligence, especially graphical models for representing beliefs (e.g., Bayes nets) or preferences (e.g., CP-nets or GAI-nets). In propositional logic, since Belnapʼs work about relevance logic in the sixties, a number of concepts of independence (also referred to as irrelevance, separability, etc.) has been pointed out in the literature (see [17], [18] for a survey). Qualitative independence, i.e., how the fact of learning a new piece of evidence individually affects previous beliefs, has been studied as well for a while [19]. None of these notions of independence in propositional logic are directly related to a form of language independence (in all the works cited above, no symbol translation is considered), and none of those papers is concerned with the language independence issue of propositional belief change operators.
     </paragraph>
     <paragraph>
      Makinson [20] studied a notion of relevance (canonical relevance) which is expected to be respected in belief change (roughly, contracting a belief base/set K with some piece of information α should preserve every consequence β of K when α is irrelevant to β). While canonical relevance is syntax-independent in the usual sense, Makinson shows that it is not language-independent; revisiting Makinsonʼs counter-example in the light of our work, we can state more precisely that canonical relevance is SIN-language independent, but it is not REV-language independent. Though language independence is considered in this paper in the context of belief change, the focus is on canonical relevance; unlike our paper, no investigation of the concept of language independence is reported and no study of robustness w.r.t. symbol translations of many belief change operators is provided.
     </paragraph>
     <paragraph>
      More closely related to our work is [21]. In this paper, Jaeger points out a very general setting for representation independence and investigates the representation independence of a number of non-monotonic inference rules. The notion of representation independence of inference relations pointed out by Jaeger is anchored on the concept of representational variants. When instantiated to classical propositional logic and assuming that so-called “abstract interpretations” are limited to symbol translations (which is a natural choice in this case, see [21]), representational variants can be defined as follows: two propositional formulae {a mathematical formula}ϕ∈PROPY1 and {a mathematical formula}ψ∈PROPY2 are representational variants w.r.t. {a mathematical formula}σ:X→PROPY1 and {a mathematical formula}τ:X→PROPY2 if and only if for any formula {a mathematical formula}α∈PROPX, we have {a mathematical formula}ϕ⊨σ(α) if and only if {a mathematical formula}ψ⊨τ(α). Then an inference relation ⊢ is representation independent whenever two representational variants {a mathematical formula}ϕ∈PROPY1 and {a mathematical formula}ψ∈PROPY2 w.r.t. {a mathematical formula}σ:X→PROPY1 and {a mathematical formula}τ:X→PROPY2 have the same consequences modulo the corresponding “abstract interpretations” σ and τ, i.e., for any formula {a mathematical formula}α∈PROPX, we have {a mathematical formula}ϕ⊢σ(α) if and only if {a mathematical formula}ψ⊢τ(α).
     </paragraph>
     <paragraph>
      Interestingly, Jaeger points out the need to restrict the set of admissible “abstract interpretations” to make the concept of representation independence meaningful (this is reminiscent to the restriction on symbol translations we considered).
     </paragraph>
     <paragraph>
      Despite this similarity, Jaegerʼs work and the present one differ in a number of aspects. Thus, Jaegerʼs setting is not restricted to classical propositional logic but is suited to more general logical systems. In addition, even when instantiated to classical propositional logic and lifted to propositional operators, Jaegerʼs representation independence does not coincide with our concept of language independence. Indeed, let us state that two n-propositional structures {a mathematical formula}Σ=〈α1,…,αn〉 over {a mathematical formula}Y1 and {a mathematical formula}Σ′=〈α1′,…,αn′〉 over {a mathematical formula}Y2 are representational variants w.r.t. {a mathematical formula}σ:X→PROPY1 and {a mathematical formula}τ:X→PROPY2 if and only for each {a mathematical formula}i∈{1,…,n}, {a mathematical formula}αi and {a mathematical formula}αi′ are representational variants w.r.t. σ and τ; and let us state that a propositional operator Ω is representation independent if and only if whenever Σ and {a mathematical formula}Σ′ are representation independent w.r.t. σ and τ, {a mathematical formula}Ω(Σ) and {a mathematical formula}Ω(Σ′) are also representation independent w.r.t. σ and τ. It turns out that this concept of representational independence does not coincide with language independence. Thus, consider the propositional operator {a mathematical formula}Ω¬ which associates every 1-propositional structure {a mathematical formula}〈α〉 with the 1-propositional structure {a mathematical formula}〈¬α〉; obviously enough, {a mathematical formula}Ω¬ is ⊤-language independent; however, it is not representation independent: take {a mathematical formula}Σ=〈⊤〉 and {a mathematical formula}Σ′=〈x〉, and consider the symbol translations {a mathematical formula}σ:∅→PROPY1 and {a mathematical formula}τ:∅→PROPY2. There are only two distinct formulae {a mathematical formula}α∈PROP∅ up to logical equivalence, namely ⊤ and ⊥. Since {a mathematical formula}⊤⊨⊤, {a mathematical formula}x⊨⊤, {a mathematical formula}⊤⊭⊥, and {a mathematical formula}x⊭⊥, ⊤ and x are representational variants in Jaegerʼs sense. Accordingly, Σ and {a mathematical formula}Σ′ are representational variants w.r.t. σ and τ. However, {a mathematical formula}Ω¬(Σ) and {a mathematical formula}Ω¬(Σ′) are not representational variants w.r.t. σ and τ since {a mathematical formula}¬⊤⊨⊥ while {a mathematical formula}¬x⊭⊥.
     </paragraph>
     <paragraph>
      Finally, while Jaeger investigates the representational independence of many non-monotonic inference relations (including forms of closed world reasoning, rational closure, and propositional probabilistic inference), he does not focus on the language independence issue for belief change operators. This makes another significant difference between his work and the present work.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <paragraph label="Proposition 2">
      Let α be a formula from{a mathematical formula}PROPX. Let σ be a symbol translation from X to{a mathematical formula}PROPY. We have{a mathematical formula}⋀x∈X(x⇔σ(x))⊨α⇔σ(α).
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}⋀x∈X(x⇔σ(x)) is equivalent to {a mathematical formula}⋀x∈X(x∧σ(x))∨(¬x∧¬σ(x)). Distributing ⋀ over ∨, given the substitution theorem, we get that {a mathematical formula}⋀x∈X(x⇔σ(x)) is equivalent to {a mathematical formula}⋁ω∈2PS(ω∧σ(ω)). Now, given an interpretation ω, there are two cases:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}ω⊨α. Then from point 1 of Corollary 1, we also have {a mathematical formula}σ(ω)⊨σ(α). Hence, {a mathematical formula}ω∧σ(ω)⊨α∧σ(α)⊨α⇔σ(α).
      </list-item>
      <list-item label="•">
       {a mathematical formula}ω⊨¬α. Then from point 1 of Corollary 1, we also have {a mathematical formula}σ(ω)⊨¬σ(α). Hence, {a mathematical formula}ω∧σ(ω)⊨¬α∧¬σ(α)⊨α⇔σ(α).
      </list-item>
     </list>
     <paragraph label="Proposition 3">
      The semantical mapping Ψ of symbol translations is a one-to-one correspondence from{a mathematical formula}PROPYX/≡, the set of all symbol translations (modulo equivalence), to the set of all injective, surjective relations over{a mathematical formula}2X×2Y. Its inverse mapping{a mathematical formula}Ψ−1associates for every subsets{a mathematical formula}X,Yof PS, an injective, surjective relation R over{a mathematical formula}2X×2Ywith a representative symbol translation, denoted{a mathematical formula}σR, such that for every propositional symbol{a mathematical formula}x∈X,{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      The proof takes advantage of the following lemma:Let{a mathematical formula}σ:X→PROPY,{a mathematical formula}α∈PROPXand{a mathematical formula}ω′⊨σ(α). There is one and only one interpretation{a mathematical formula}ω∈2Xsuch that{a mathematical formula}ω′⊨σ(ω); moreover,{a mathematical formula}ω⊨α.Let {a mathematical formula}σ:X→PROPY, {a mathematical formula}α∈PROPX and {a mathematical formula}ω′⊨σ(α). From the substitution theorem {a mathematical formula}σ(α)≡σ(⋁{ω|ω⊨α}), that is, {a mathematical formula}σ(α)≡⋁{σ(ω)|ω⊨α}. Hence, {a mathematical formula}ω′⊨⋁{σ(ω)|ω⊨α}. Since all the distinct models ω, {a mathematical formula}ω″ of α are jointly inconsistent, from Corollary 1, it is also the case that for all such pairs ω, {a mathematical formula}ω″, their images by σ are jointly inconsistent (i.e., {a mathematical formula}σ(ω)∧σ(ω″)⊨⊥). Therefore, from {a mathematical formula}ω′⊨⋁{σ(ω)|ω⊨α}, we get that there exists a model ω of α such that {a mathematical formula}ω′⊨σ(ω). Suppose that there exists another interpretation {a mathematical formula}ω″⊨α such that {a mathematical formula}ω′⊨σ(ω″). Again, since {a mathematical formula}ω∧ω″⊨⊥, from Corollary 1, we get that {a mathematical formula}σ(ω)∧σ(ω″)⊨⊥. This conflicts with the fact that {a mathematical formula}ω′⊨σ(ω) and {a mathematical formula}ω′⊨σ(ω″). Thus, ω is the unique model of α such that {a mathematical formula}ω′⊨σ(ω). Finally, suppose that a model {a mathematical formula}ω″ of ¬α satisfies {a mathematical formula}ω′⊨σ(ω″). Then we would get from Corollary 1 that {a mathematical formula}σ(ω″)⊨σ(¬α). Hence by transitivity of entailment, we would have {a mathematical formula}ω′⊨σ(¬α). But we know that {a mathematical formula}ω′⊨σ(ω), and {a mathematical formula}σ(¬α)∧σ(α)≡σ(¬α∧α)≡σ(⊥)≡⊥ is inconsistent, and {a mathematical formula}ω′ should be a model of it, contradiction.  □We now prove Proposition 3:From Lemma 1 there is a unique interpretation {a mathematical formula}ω∈2X such that {a mathematical formula}ω′⊨σ(ω). Therefore {a mathematical formula}Ψ(σ)=Rσ is an injective, surjective relation. We now show that Ψ is injective and surjective:(Injectivity of Ψ) Let {a mathematical formula}σ,σ′ two symbol translations from X to {a mathematical formula}PROPY, which are not equivalent. Then there exists {a mathematical formula}x∈X such that {a mathematical formula}σ(x)≢σ′(x). Hence, we have {a mathematical formula}σ(x)⊭σ′(x) or {a mathematical formula}σ′(x)⊭σ(x). Assume that {a mathematical formula}σ(x)⊭σ′(x) (the remaining case is symmetric). Then there exists {a mathematical formula}ω′∈2Y such that {a mathematical formula}ω′⊨σ(x) and {a mathematical formula}ω′⊭σ′(x) (or equivalently, {a mathematical formula}ω′⊨σ′(¬x)). From Lemma 1{a mathematical formula}∃ω1∈2X such that {a mathematical formula}ω1⊨x and {a mathematical formula}ω′⊨σ(ω1), hence {a mathematical formula}∃ω1⊨x such that {a mathematical formula}ω′∈Rσ(ω1). From Lemma 1 again, {a mathematical formula}∃ω2∈2X such that {a mathematical formula}ω2⊨¬x and {a mathematical formula}ω′⊨σ′(ω2), hence {a mathematical formula}∃ω2⊨¬x such that {a mathematical formula}ω′∈Rσ′(ω2) (where, of course, {a mathematical formula}Rσ′ stands for {a mathematical formula}Ψ(σ′)). Since {a mathematical formula}ω1⊨x and {a mathematical formula}ω2⊨¬x, {a mathematical formula}ω1 and {a mathematical formula}ω2 are distinct interpretations. Since {a mathematical formula}ω1 is the unique interpretation such that {a mathematical formula}ω′⊨σ(ω1), we have {a mathematical formula}ω′⊭σ(ω2), i.e., {a mathematical formula}ω′∉Rσ(ω2). The fact that {a mathematical formula}ω′∈Rσ′(ω2) enables to conclude that {a mathematical formula}Rσ≠Rσ′.(Surjectivity of Ψ) Let {a mathematical formula}R′ be an injective, surjective relation on {a mathematical formula}2X×2Y and let {a mathematical formula}σR′ be the symbol translation from X to {a mathematical formula}PROPY such that for every propositional symbol {a mathematical formula}x∈2X, {a mathematical formula}σR′(x)=⋁{ω′∈2Y|ω′∈R′(ω),ω⊨x}. We show now that {a mathematical formula}RσR′(=Ψ(σR′))=R′. Let {a mathematical formula}ω∈2X. Let {a mathematical formula}Xω+={x∈X|ω⊨x} and {a mathematical formula}Xω−={x∈X|ω⊨¬x}. We have {a mathematical formula}σR′(ω)≡⋀x∈Xω+{σR′(x)}∧⋀x∈Xω−{σR′(¬x)}≡⋀x∈Xω+{σR′(x)}∧⋀x∈Xω−{¬σR′(x)}≡⋀x∈Xω+{⋁{ω′∈2Y|ω′∈R′(ω″),ω″⊨x}}∧⋀x∈Xω−{¬⋁{ω′∈2Y|ω′∈R′(ω″),ω″⊨x}}. Now, let {a mathematical formula}ω⁎∈2Y. We have {a mathematical formula}ω⁎⊨σR′(ω) if and only if ({a mathematical formula}ω⁎⊨⋀x∈Xω+{⋁{ω′∈2Y|ω′∈R′(ω″),ω″⊨x}} and {a mathematical formula}ω⁎⊨⋀x∈Xω−{¬⋁{ω′∈2Y|ω′∈R′(ω″),ω″⊨x}}) if and only if ({a mathematical formula}∀x∈Xω+, {a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨x} and {a mathematical formula}∀x∈Xω−, {a mathematical formula}ω⁎∉⋃{R′(ω″)|ω″⊨x}) if and only if ({a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨⋀x∈Xω+x} and {a mathematical formula}ω⁎∉⋃{R′(ω″)|ω″⊨⋁x∈Xω−x}). But since {a mathematical formula}R′ is an injective, surjective relation we get that {a mathematical formula}ω⁎∉⋃{R′(ω″)|ω″⊨⋁x∈Xω−x} if and only if {a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨⋀x∈Xω−¬x} (the if part comes from the injectivity of {a mathematical formula}R′, the only if part comes from the surjectivity of {a mathematical formula}R′). Hence, we have {a mathematical formula}ω⁎⊨σR′(ω) if and only if ({a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨⋀x∈Xω+x} and {a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨⋀x∈Xω−¬x}) if and only if {a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″⊨⋀x∈Xω+x∧⋀x∈Xω−¬x} if and only if {a mathematical formula}ω⁎∈⋃{R′(ω″)|ω″=ω} if and only if {a mathematical formula}ω⁎∈R′(ω). We got that {a mathematical formula}ω⁎∈R′(ω) if and only if {a mathematical formula}ω⁎⊨σR′(ω). Furthermore, by definition of {a mathematical formula}RσR′, we have {a mathematical formula}ω⁎⊨σR′(ω) if and only if {a mathematical formula}ω⁎∈RσR′(ω). Hence, {a mathematical formula}ω⁎∈R′(ω) if and only if {a mathematical formula}ω⁎∈RσR′(ω). Therefore, {a mathematical formula}RσR′=R′, which concludes the proof.  □
     </paragraph>
     <paragraph label="Proposition 4">
      Let α be a formula of{a mathematical formula}PROPXand β a formula of{a mathematical formula}PROPY. If α is neither valid nor inconsistent, then there exists a symbol translation{a mathematical formula}σ∈PROPYXsuch that{a mathematical formula}σ(α)≡β.
     </paragraph>
     <paragraph label="Proof">
      We take advantage of the semantical mapping of symbol translations (cf. Definition 5). Let α be a formula from {a mathematical formula}PROPX that is consistent and not valid, and let β be a formula from {a mathematical formula}PROPY. Let {a mathematical formula}ω,ω′ be two (distinct) interpretations over X such that {a mathematical formula}ω⊨α and {a mathematical formula}ω′⊭α. We construct the binary relation R on {a mathematical formula}2X×2Y as follows: {a mathematical formula}R(ω)=Mod(β), {a mathematical formula}R(ω′)=Mod(¬β) and for every interpretation {a mathematical formula}ω″ over X distinct from ω and {a mathematical formula}ω′, {a mathematical formula}R(ω″)=∅. R is obviously an injective, surjective relation, so that from Proposition 3 there is a symbol translation {a mathematical formula}Ψ−1(R)=σR that satisfies {a mathematical formula}σR(ω)≡β, i.e., that satisfies {a mathematical formula}σR(α)≡β.  □
     </paragraph>
     <paragraph label="Proposition 5">
      REV and AIP are equivalent.
     </paragraph>
     <paragraph label="Proof">
      First of all, we show that we can assume without loss of generality that the input symbol translation {a mathematical formula}σ:X→PROPY is such that {a mathematical formula}X∩Y=∅. Indeed, let us prove that a symbol translation σ satisfies REV iff the symbol translation {a mathematical formula}σ′:X→PROPY′ given by {a mathematical formula}∀x∈X, {a mathematical formula}σ′(x)=σ(x)′ satisfies REV as well (note that {a mathematical formula}Y′ is such that {a mathematical formula}X∩Y′=∅). By construction, {a mathematical formula}σ′ is equal to the restriction over X of the symbol translation {a mathematical formula}τ∘σ where {a mathematical formula}τ:Y→PROPY′ is the bijective symbol translation such that {a mathematical formula}∀y∈Y, {a mathematical formula}τ(y)=y′. If {a mathematical formula}σ′ is such that there exists a symbol translation {a mathematical formula}θ′ from {a mathematical formula}Y′ to {a mathematical formula}PROPX such that {a mathematical formula}∀x∈X, {a mathematical formula}θ′(σ′(x))≡x, then we have {a mathematical formula}∀x∈X, {a mathematical formula}θ′(τ(σ(x)))≡x; accordingly, the symbol translation {a mathematical formula}θ=θ′∘τ is such that {a mathematical formula}∀x∈X, {a mathematical formula}θ(σ(x))≡x. The other way around, if σ is such that there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}∀x∈X, {a mathematical formula}θ(σ(x))≡x, then we also have {a mathematical formula}∀x∈X, {a mathematical formula}θ(τ−1(τ(σ(x))))≡x; this shows that the symbol translation {a mathematical formula}θ′=θ∘τ−1 is such that {a mathematical formula}∀x∈X, {a mathematical formula}θ′(σ′(x))≡x.Suppose now that {a mathematical formula}σ:X→PROPY is such that {a mathematical formula}X∩Y=∅. By definition, σ satisfies REV iff there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}∀xi∈X={x1,…,xn}, {a mathematical formula}θ(σ(xi))≡xi iff there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}∀xi∈X, {a mathematical formula}θ(σ(xi))⇔xi is valid. Since {a mathematical formula}∀xi∈X, {a mathematical formula}Var(σ(xi))⊆Y and {a mathematical formula}X∩Y=∅, this is also equivalent to stating that there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}∀xi∈X, {a mathematical formula}θ(σ(xi)⇔xi) is valid. This holds iff there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}θ(⋀xi∈X(σ(xi)⇔xi)) is valid.Now, for each {a mathematical formula}yj∈Y, the restriction {a mathematical formula}yj↦θ(yj) of θ can be viewed as a Skolem function, so that there exists a symbol translation θ from Y to {a mathematical formula}PROPX such that {a mathematical formula}θ(⋀xi∈X(σ(xi)⇔xi)) is valid iff the quantified Boolean formula {a mathematical formula}∀X.(∃Y.(⋀xi∈X(σ(xi)⇔xi))) is valid (see e.g. [22] for details). This holds iff the quantified Boolean formula (with free variables X){a mathematical formula} is valid. Now, {a mathematical formula}⋀xi∈X(σ(xi)⇔xi) is equivalent to {a mathematical formula}⋁s1,…,sn∈{+,−}(⋀xi∈X(σ(xi)si∧xisi)). Hence, {a mathematical formula}∃Y.(⋀xi∈X(σ(xi)⇔xi)) is equivalent to{a mathematical formula} which in turn is equivalent to {a mathematical formula}⋁s1,…,sn∈{+,−}∃Y.(⋀xi∈X(σ(xi)si∧xisi)), since existential quantifications “distributes over” disjunctions (see e.g. [23] for details). Finally, {a mathematical formula}∃Y.⋀xi∈X(σ(xi)si∧xisi) is equivalent to{a mathematical formula} Since {a mathematical formula}Var(⋀xi∈Xσ(xi)si)⊆Y, the formula {a mathematical formula}∃Y.(⋀xi∈Xσ(xi)si) is equivalent to ⊤ if {a mathematical formula}⋀xi∈Xσ(xi)si is consistent and to ⊥ otherwise (see e.g. [23]). Thus, {a mathematical formula}⋁s1,…,sn∈{+,−}∃Y.(⋀xi∈X(σ(xi)si∧xisi)) is equivalent to {a mathematical formula}⋁s1,…,sn∈{+,−}⋀xi∈Xxisi iff for each {a mathematical formula}s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈Xσ(xi)si is consistent. The fact that {a mathematical formula}⋁s1,…,sn∈{+,−}⋀xi∈Xxisi is valid completes the proof.  □
     </paragraph>
     <paragraph label="Proposition 6">
      Let σ be a symbol translation from{a mathematical formula}PROPYXand{a mathematical formula}Rσbe its semantical mapping:
     </paragraph>
     <list>
      <list-item label="1.">
       σ satisfies AIP if and only if{a mathematical formula}Rσis left-total;
      </list-item>
      <list-item label="2.">
       σ satisfies BAP if and only if{a mathematical formula}Rσis a one-to-one correspondence;
      </list-item>
      <list-item label="3.">
       σ satisfies FCP if and only if{a mathematical formula}Rσis functional;
      </list-item>
      <list-item label="4.">
       σ satisfies SIN if and only if{a mathematical formula}Rσis a one-to-one correspondence which is decomposable, i.e., there exists a bijection{a mathematical formula}ηRσfrom X to Y defined by{a mathematical formula}∀x∈X,{a mathematical formula}∀y∈Y,{a mathematical formula}ηRσ(x)=yif and only if{a mathematical formula}{Rσ(ω)|ω∈2X,ω⊨x}={ω′|ω′∈2Y,ω′⊨y};
      </list-item>
      <list-item label="5.">
       σ satisfies TPR if and only if{a mathematical formula}∀x∈X,{a mathematical formula}∃ω,ω′∈2X,{a mathematical formula}ω⊨x,{a mathematical formula}ω′⊨¬x,{a mathematical formula}Rσ(ω)≠∅and{a mathematical formula}Rσ(ω′)≠∅.
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        AIP. Let σ be a symbol translation from {a mathematical formula}X={x1,…,xn} to {a mathematical formula}PROPY satisfying AIP. Then {a mathematical formula}∀s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈Xσ(xi)si is consistent, thus {a mathematical formula}σ(⋀xi∈Xxisi) is consistent, so {a mathematical formula}∀ω∈2X, {a mathematical formula}Rσ(ω)≠∅. Therefore, {a mathematical formula}Rσ is left-total. Conversely, let {a mathematical formula}X,Y⊆PS and R be an injective, surjective, left-total relation on {a mathematical formula}2X×2Y. For every {a mathematical formula}ω∈2X, {a mathematical formula}R(ω)≠∅ since R is left-total. Thus for every {a mathematical formula}ω∈2X, {a mathematical formula}σR(ω)≡⋁{ω′|ω′∈R(ω)} is consistent. Furthermore {a mathematical formula}∀s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈XσR(xi)si, which is equivalent to {a mathematical formula}σR(⋀xi∈Xxisi), is equivalent to {a mathematical formula}σR(ω) for the interpretation {a mathematical formula}ω∈2X which is equivalent to {a mathematical formula}⋀xi∈Xxisi. Thus {a mathematical formula}∀s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈XσR(xi)si is consistent. Therefore, {a mathematical formula}σR satisfies AIP.
       </list-item>
       <list-item label="2.">
        BAP. Let σ be a symbol translation from X to {a mathematical formula}PROPY satisfying BAP. For every complete formula α from {a mathematical formula}PROPX, {a mathematical formula}σ(α) is a complete formula from {a mathematical formula}PROPY, thus for every interpretation {a mathematical formula}ω∈2X, {a mathematical formula}σ(ω) admits exactly one model, i.e., {a mathematical formula}Rσ(ω) is a singleton. This means that {a mathematical formula}Rσ is left-total and functional. Conversely, let {a mathematical formula}X,Y⊆PS and R be a one-to-one correspondence on {a mathematical formula}2X×2Y. For every complete formula α from {a mathematical formula}PROPX, let ω be its unique model. Since R is one-to-one, {a mathematical formula}R(ω) is a singleton. Thus for every complete formula α, {a mathematical formula}σR(α) is a complete formula from {a mathematical formula}PROPY. Therefore, {a mathematical formula}σR satisfies BAP.
       </list-item>
       <list-item label="3.">
        FCP. Let σ be a symbol translation from {a mathematical formula}X={x1,…,xn} to {a mathematical formula}PROPY satisfying FCP. Let {a mathematical formula}ω1′,ω2′∈2Y such that {a mathematical formula}ω1′≠ω2′. Since σ satisfies FCP, there is a formula {a mathematical formula}α1 from {a mathematical formula}PROPX such that {a mathematical formula}σ(α1)≡ω1′ and there is a formula {a mathematical formula}α2 from {a mathematical formula}PROPX such that {a mathematical formula}σ(α2)≡ω2′. Then since {a mathematical formula}ω1′≠ω2′, we have {a mathematical formula}σ(α1)∧σ(α2)⊨⊥. Now, by Lemma 1 (see the proof of Proposition 3), since {a mathematical formula}ω1′⊨σ(α1) and {a mathematical formula}ω2′⊨σ(α2), there is a unique interpretation {a mathematical formula}ω1∈2X such that {a mathematical formula}ω1′⊨σ(ω1), i.e., such that {a mathematical formula}ω1′∈Rσ(ω1), and there is a unique interpretation {a mathematical formula}ω2∈2X such that {a mathematical formula}ω2′⊨σ(ω2), i.e., such that {a mathematical formula}ω2′∈Rσ(ω2); moreover, {a mathematical formula}ω1⊨α1 and {a mathematical formula}ω2⊨α2. Towards a contradiction, assume that {a mathematical formula}ω1=ω2. Then {a mathematical formula}ω1⊨α1∧α2. Thus {a mathematical formula}σ(ω1)⊨σ(α1)∧σ(α2)⊨⊥. This contradicts {a mathematical formula}ω1′⊨σ(ω1). Hence, {a mathematical formula}ω1≠ω2. This shows that {a mathematical formula}Rσ is functional. Conversely, let {a mathematical formula}X,Y⊆PS and R be an injective, surjective, functional relation on {a mathematical formula}2X×2Y. Since R is surjective and functional, for every interpretation {a mathematical formula}ω′∈2Y, there exists a unique interpretation {a mathematical formula}R−1(ω′)∈2X such that {a mathematical formula}(R−1(ω′),ω′)∈R. Accordingly, {a mathematical formula}ω′ is equivalent to {a mathematical formula}σR(R−1(ω′)). Furthermore, since {a mathematical formula}R−1(ω′)∈2X, we have that {a mathematical formula}R−1(ω′) is equivalent to {a mathematical formula}⋀i=1nxisi for some {a mathematical formula}s1,…,sn∈{+,−}. As a consequence, {a mathematical formula}σR(R−1(ω′)) is equivalent to {a mathematical formula}⋀i=1nσR(xi)si for some {a mathematical formula}s1,…,sn∈{+,−}, which shows that {a mathematical formula}σR(R−1(ω′)) (hence, {a mathematical formula}ω′) is definable from {a mathematical formula}{σR(x)|x∈X}. Finally, let β be any formula from {a mathematical formula}PROPY. Since every model {a mathematical formula}ω′ of β is definable from {a mathematical formula}{σR(x)|x∈X}, this is also the case of their disjunction. Thus, β is definable from {a mathematical formula}{σR(x)|x∈X}, which shows that {a mathematical formula}σR satisfies FCP.
       </list-item>
       <list-item label="4.">
        SIN. Let σ be a symbol translation from {a mathematical formula}X={x1,…,xn} to {a mathematical formula}PROPY satisfying SIN. For every interpretation {a mathematical formula}ω∈2X, ω is equivalent to {a mathematical formula}⋀xi∈Xxisi, for some {a mathematical formula}s1,…,sn∈{+,−}. Hence {a mathematical formula}σ(ω)≡σ(⋀xi∈Xxisi)≡⋀xi∈Xσ(xi)si≡⋀yi∈Yyisi, that is, an element of {a mathematical formula}2Y. Hence, for every {a mathematical formula}ω∈2X, {a mathematical formula}Rσ(ω) is a singleton. This means that {a mathematical formula}Rσ is left-total and functional. Therefore, {a mathematical formula}Rσ is a one-to-one correspondence. Now from Corollary 1, {a mathematical formula}∀x∈X, {a mathematical formula}∀ω∈2X, we have {a mathematical formula}ω⊨x iff {a mathematical formula}σ(ω)⊨σ(x). Thus there exists a bijection {a mathematical formula}ηRσ=σ from X to Y such that {a mathematical formula}∀x∈X, {a mathematical formula}∀y∈Y, {a mathematical formula}σ(x)=y if and only if {a mathematical formula}{Rσ(ω)|ω∈2X,ω⊨x}={ω′|ω′∈2Y,ω′⊨y}. Conversely, let {a mathematical formula}X,Y⊆PS and R be a one-to-one correspondence on {a mathematical formula}2X×2Y such that there is a bijection {a mathematical formula}ηR from X to Y defined by {a mathematical formula}∀x∈X, {a mathematical formula}∀y∈Y, {a mathematical formula}ηR(x)=y if and only if {a mathematical formula}{R(ω)|ω∈2X,ω⊨x}={ω′|ω′∈2Y,ω′⊨y}. By definition of {a mathematical formula}σR, we have {a mathematical formula}∀x∈X, {a mathematical formula}σR(x)=⋁{ω′∈2Y|ω′∈R(ω) and {a mathematical formula}ω⊨x}. Since each {a mathematical formula}R(ω) is a singleton, this is equal to {a mathematical formula}⋁{R(ω) and {a mathematical formula}ω⊨x}. By definition of {a mathematical formula}ηR, {a mathematical formula}{R(ω) and {a mathematical formula}ω⊨x}={ω′∈2Y|ω′⊨η(x)}. Hence {a mathematical formula}σR(x)=⋁{ω′∈2Y|ω′⊨η(x)}. But {a mathematical formula}⋁{ω′∈2Y|ω′⊨η(x)} is equivalent to {a mathematical formula}η(x). Thus {a mathematical formula}σR is equivalent to {a mathematical formula}ηR. Since {a mathematical formula}ηR is a bijection from X to Y, {a mathematical formula}σR is also a bijection from X to Y, thus {a mathematical formula}σR satisfies SIN.
       </list-item>
       <list-item label="5.">
        TPR. Let σ be a symbol translation from X to {a mathematical formula}PROPY satisfying TPR. Then for every {a mathematical formula}x∈X, {a mathematical formula}σ(x) is consistent and not valid. Let {a mathematical formula}x∈X. There exist two interpretations {a mathematical formula}ω1,ω2 from {a mathematical formula}2Y such that {a mathematical formula}ω1⊨σ(x) and {a mathematical formula}ω2⊨¬σ(x). By Lemma 1 (see the proof of Proposition 3), there exist two interpretations {a mathematical formula}ω,ω′ from {a mathematical formula}2X, {a mathematical formula}ω⊨x, {a mathematical formula}ω′⊨¬x, such that {a mathematical formula}ω1⊨σ(ω) and {a mathematical formula}ω2⊨σ(ω′). Therefore, for every {a mathematical formula}x∈X, there exist two interpretations {a mathematical formula}ω,ω′∈2X, {a mathematical formula}ω⊨x, {a mathematical formula}ω′⊨¬x, such that {a mathematical formula}Rσ(ω)≠∅ and {a mathematical formula}Rσ(ω′)≠∅. Conversely, let {a mathematical formula}X,Y⊆PS and R be an injective, surjective relation on {a mathematical formula}2X×2Y such that {a mathematical formula}∀x∈X, {a mathematical formula}∃ω,ω′∈2X, {a mathematical formula}ω⊨x, {a mathematical formula}ω′⊨¬x, {a mathematical formula}R(ω)≠∅ and {a mathematical formula}R(ω′)≠∅. Let {a mathematical formula}x∈X. Then there exist two interpretations {a mathematical formula}ω,ω′ from {a mathematical formula}2X such that {a mathematical formula}ω⊨x, {a mathematical formula}ω′⊨¬x and such that {a mathematical formula}σR(ω) and {a mathematical formula}σR(ω′) are both consistent. Yet from point 1 of Corollary 1, {a mathematical formula}σR(ω)⊨σR(x) and {a mathematical formula}σR(ω′)⊨σR(¬x), this shows that {a mathematical formula}σR(x) and {a mathematical formula}σR(¬x) are both consistent, or equivalently, that {a mathematical formula}σR(x) is consistent and not valid. Therefore, {a mathematical formula}σR satisfies TPR.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proposition 7">
      SIN implies BAP. BAP implies FCP. BAP also implies REV, which implies TPR. Each implication is strict (i.e., the converse does not hold). Moreover, if a symbol translation satisfies REV and FCP, then it satisfies BAP. Lastly, FCP does not imply and is not implied by any of REV or TPR.
     </paragraph>
     <paragraph label="Proof">
      <list>
       <list-item label="•">
        SIN implies BAP. Direct from Proposition 6. The implication is strict: let {a mathematical formula}X={x}, {a mathematical formula}Y={p} and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=¬p. Clearly, σ satisfies BAP but does not satisfy SIN.
       </list-item>
       <list-item label="•">
        BAP implies FCP. Direct from Proposition 6. The implication is strict: let {a mathematical formula}X={x,y}, {a mathematical formula}Y={p} and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=⊤ and {a mathematical formula}σ(y)=p. Clearly, σ satisfies FCP but does not satisfy BAP.
       </list-item>
       <list-item label="•">
        BAP implies REV. BAP implies AIP from Proposition 6. And from Proposition 5, AIP and REV are equivalent properties.
       </list-item>
       <list-item label="•">
        REV implies TPR. Let σ be a symbol translation from {a mathematical formula}PROPYX satisfying AIP. From Proposition 5, σ satisfies REV. Then {a mathematical formula}Rσ is a left-total relation over {a mathematical formula}2X×2Y. Let {a mathematical formula}x∈X. Then {a mathematical formula}∀ω∈2X such that {a mathematical formula}ω⊨x, {a mathematical formula}Rσ(ω)≠∅. Moreover, {a mathematical formula}∀ω′∈2X such that {a mathematical formula}ω′⊨¬x, {a mathematical formula}Rσ(ω′)≠∅. Since {a mathematical formula}ω≠ω′ and {a mathematical formula}Rσ is injective, we have {a mathematical formula}Rσ(ω)∩Rσ(ω′)=∅, thus {a mathematical formula}Rσ(ω)≠2Y. Therefore, from Proposition 6σ satisfies TPR. The implication is strict: let {a mathematical formula}X={x,y}, {a mathematical formula}Y={p}, and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=p, and {a mathematical formula}σ(y)=¬p. σ satisfies TPR but does not satisfy AIP.
       </list-item>
       <list-item label="•">
        If a symbol translation satisfies REV and FCP, then it satisfies BAP. Direct from Proposition 6.
       </list-item>
       <list-item label="•">
        FCP does not imply REV and is not implied by REV. If FCP would imply REV, then it would imply TPR as well, since REV implies TPR, but FCP does not imply TPR. On the other hand, let {a mathematical formula}X={x}, {a mathematical formula}Y={p,q} and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=p. σ satisfies REV but it does not satisfy FCP.
       </list-item>
       <list-item label="•">
        FCP does not imply TPR and is not implied by TPR. Indeed, let {a mathematical formula}X={x}, {a mathematical formula}Y=∅ and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=⊥. σ trivially satisfies FCP but does not satisfy TPR. Now, let {a mathematical formula}X={x}, {a mathematical formula}Y={p,q} and {a mathematical formula}σ∈PROPYX such that {a mathematical formula}σ(x)=p∨q. σ satisfies TPR but does not satisfy FCP.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proposition 8">
      The concept of syntax independence and the concept of P-language independence for propositional operators are logically independent.
     </paragraph>
     <paragraph label="Proof">
      Given Proposition 7, it is enough to point out (1) a propositional operator which is both syntax-independent and ⊤-language independent, (2) a propositional operator which is syntax-independent but not SIN-language independent, (3) a propositional operator which is ⊤-language independent but not syntax-independent, and finally (4) a propositional operator which neither is syntax-independent nor is SIN-language independent.
     </paragraph>
     <list>
      <list-item label="1.">
       ded (the deduction operator) is both syntax-independent and ⊤-language independent.
      </list-item>
      <list-item label="2.">
       Just consider the AGM revision operator ∘ given in the proof of Proposition 14.
      </list-item>
      <list-item label="3.">
       Consider for instance the propositional operator Ω that associates with every 1-propositional structure {a mathematical formula}〈{α}〉 the 1-propositional structure {a mathematical formula}〈{⊤}〉 if α is a conjunctive formula of the form {a mathematical formula}β∧γ where β, γ are propositional formulae, and {a mathematical formula}〈{⊥}〉 otherwise. Ω obviously is ⊤-language independent but it is not syntax-independent.
      </list-item>
      <list-item label="4.">
       Consider for instance the propositional operator Ω that associates with every 1-propositional structure {a mathematical formula}〈{α}〉 the 1-propositional structure {a mathematical formula}〈{⊤}〉 if {a mathematical formula}α=⊤, and {a mathematical formula}〈{p}〉 otherwise, where {a mathematical formula}p∈PS. Then Ω neither is syntax-independent nor is SIN-language independent.  □
      </list-item>
     </list>
     <paragraph label="Proposition 9">
      {a mathematical formula}σ:{x1,…,xn}→PROPYsatisfies FCP if and only if{a mathematical formula}⋀i=1n(zi⇔σ(xi))defines Y in terms of{a mathematical formula}{z1,…,zn}, where{a mathematical formula}{z1,…,zn}∩Y=∅.
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}{¬,∧} is functionally complete w.r.t. Y given {a mathematical formula}{σ(x)|x∈X} iff for every {a mathematical formula}y∈Y, there exists a formula {a mathematical formula}αy generated from {a mathematical formula}{¬,∧} and {a mathematical formula}{σ(x)|x∈X} as the set of “atoms” such that {a mathematical formula}αy≡y. Under the assumption that {a mathematical formula}⋀i=1n(zi⇔σ(xi)) holds, this is equivalent to state that for every {a mathematical formula}y∈Y there exists a formula {a mathematical formula}αy generated from {a mathematical formula}{¬,∧} and {a mathematical formula}{z1,…,zn} as the set of atoms such that {a mathematical formula}αy≡y. Each {a mathematical formula}αy can be viewed as a definition of y in terms of {a mathematical formula}{z1,…,zn} in {a mathematical formula}⋀i=1n(zi⇔σ(xi)).  □
     </paragraph>
     <paragraph label="Proposition 10">
      <list>
       <list-item label="1.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies SIN is in{a mathematical formula}P.
       </list-item>
       <list-item label="2.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies TPR is{a mathematical formula}NP-complete.
       </list-item>
       <list-item label="3.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies FCP is{a mathematical formula}coNP-complete in the general case. The problem is in{a mathematical formula}Pif{a mathematical formula}|X|&lt;|Y|.
       </list-item>
       <list-item label="4.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies BAP is{a mathematical formula}coNP-complete in the general case. The problem is in{a mathematical formula}Pif{a mathematical formula}|X|≠|Y|.
       </list-item>
       <list-item label="5.">
        Determining whether a given symbol translation{a mathematical formula}σ∈PROPYXsatisfies REV (or, equivalently, AIP) is{a mathematical formula}Π2p-complete. The problem is{a mathematical formula}coNP-complete if{a mathematical formula}|X|=|Y|, and is in{a mathematical formula}Pif{a mathematical formula}|X|&gt;|Y|.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}X={x1,…,xn}.
     </paragraph>
     <list>
      <list-item label="1.">
       SIN. Obvious.
      </list-item>
      <list-item label="2.">
       TPR. For each {a mathematical formula}x∈X, {a mathematical formula}σ(x) is consistent and not valid iff one can find a model of it and a counter-model of it. In order to determine whether σ satisfies TPR it is enough to guess for each {a mathematical formula}x∈X an interpretation from {a mathematical formula}2Y which satisfies {a mathematical formula}σ(x) and an interpretation from {a mathematical formula}2Y which satisfies {a mathematical formula}¬σ(x); this can be easily done in non-deterministic polynomial time. We prove {a mathematical formula}NP-hardness by exhibiting a polynomial reduction from the satisfiability problem. Let α be any propositional formula. Let us associate with it in polynomial time the symbol translation {a mathematical formula}σ:{x}→Var(α)∪{y} with {a mathematical formula}y∉Var(α) such that {a mathematical formula}σ(x)=α∧y. α is consistent if and only if σ satisfies TPR.
      </list-item>
      <list-item label="3.">
       FCP. Proposition 9 gives a polynomial reduction of this problem to the definability one. Since the latter is in {a mathematical formula}coNP[7] and {a mathematical formula}coNP is closed under polynomial reduction, the membership of the former to {a mathematical formula}coNP follows. We prove {a mathematical formula}coNP-hardness by exhibiting a polynomial reduction from the unsatisfiability problem. Consider a propositional formula α from {a mathematical formula}PROPX; let us associate with it in polynomial time the symbol translation σ from {a mathematical formula}PROPYX where {a mathematical formula}X=Var(α)∪{p,q} (with {a mathematical formula}Var(α)∩{p,q}=∅), {a mathematical formula}Y=X, such that {a mathematical formula}∀x∈Var(α), {a mathematical formula}σ(x)=x, and {a mathematical formula}σ(p)=(p∧α)∨q, and {a mathematical formula}σ(q)=(q∧α)∨p. If α is inconsistent, then every {a mathematical formula}y∈Y is definable from {a mathematical formula}{σ(x)|x∈X}. Indeed, in such a case, for every {a mathematical formula}y∈Y, if {a mathematical formula}y∈Var(α), then the formula y from {a mathematical formula}PROP{σ(x)|x∈X} is such that {a mathematical formula}y≡y, and in the remaining case when {a mathematical formula}y=p (resp. {a mathematical formula}y=q) we can find {a mathematical formula}σ(q) (resp. {a mathematical formula}σ(p)) in {a mathematical formula}PROP{σ(x)|x∈X} such that {a mathematical formula}p≡σ(q) (resp. {a mathematical formula}q≡σ(p)). Accordingly, if α is inconsistent then σ satisfies FCP. Now, if α is consistent, then σ does not satisfy FCP. Indeed, taking advantage of Proposition 9, it is enough to prove that {a mathematical formula}Σ=⋀i=1n(zi⇔xi){a mathematical formula}∧(zp⇔((p∧α)∨q))∧(zq⇔((q∧α)∨p)) does not define p in terms of {a mathematical formula}{z1,…,zn,zp,zq}. To do so, it is enough to prove that {a mathematical formula}∃{x1,…,xn,p,q}.(Σ∧p) does not imply {a mathematical formula}¬∃{x1,…,xn,p,q}.(Σ∧¬p) (see Corollary 9 in [7]). This is the case because when α is consistent, the implicant {a mathematical formula}zp∧zq of {a mathematical formula}∃{x1,…,xn,p,q}.(Σ∧p) does not imply the implicate {a mathematical formula}¬zp∨¬zq∨¬αz of {a mathematical formula}¬∃{x1,…,xn,p,q}.(Σ∧¬p), where {a mathematical formula}αz is the formula obtained from α by replacing each {a mathematical formula}xi by {a mathematical formula}zi ({a mathematical formula}i∈1,…,n). Thus, α is inconsistent if and only if σ satisfies FCP, which concludes the proof.The fact that the problem is in {a mathematical formula}P if {a mathematical formula}|X|&lt;|Y| directly comes from Corollary 2, since σ satisfies FCP only if {a mathematical formula}|X|⩾|Y|.
      </list-item>
      <list-item label="4.">
       BAP. The membership to {a mathematical formula}coNP directly follows from Corollary 2 and from point 3 of this proposition, since σ satisfies BAP if it satisfies FCP and {a mathematical formula}|X|=|Y|. We prove {a mathematical formula}coNP-hardness by exhibiting a polynomial reduction from the unsatisfiability problem. Consider a propositional formula α from {a mathematical formula}PROPX; let us associate with it in polynomial time the symbol translation σ from {a mathematical formula}PROPYX where {a mathematical formula}X=Var(α)∪{new} (with {a mathematical formula}new∉Var(α)), {a mathematical formula}Y=X, such that {a mathematical formula}∀x∈Var(α), {a mathematical formula}σ(x)=x, and {a mathematical formula}σ(new)=α∨new. If α is inconsistent, then {a mathematical formula}∀ω∈2X, we have {a mathematical formula}σ(ω)≡ω. If α is consistent, then there exists {a mathematical formula}ω∈2Var(α) such that {a mathematical formula}ω⊨α. {a mathematical formula}ω∧¬new corresponds to an interpretation from {a mathematical formula}2X such that {a mathematical formula}σ(ω∧¬new)≡ω∧¬α∧¬new≡⊥. Thus, α is inconsistent if and only if σ satisfies BAP.The fact that the problem is in {a mathematical formula}P if {a mathematical formula}|X|≠|Y| directly comes from Corollary 2, since σ satisfies BAP only if {a mathematical formula}|X|=|Y|.
      </list-item>
      <list-item label="5.">
       REV. We take advantage of the equivalence given by Proposition 5. For membership to {a mathematical formula}Π2p, one considers the complementary problem (determine whether σ does not satisfy AIP) and shows that it belongs to {a mathematical formula}Σ2p. Consider the following algorithm: guess {a mathematical formula}s1,…,sn∈{+,−} then check using one call to an {a mathematical formula}NP-oracle that {a mathematical formula}⋀xi∈Xσ(xi)si is inconsistent. Clearly enough, this non-deterministic algorithm with oracle {a mathematical formula}NP solves the complementary problem, showing that it belongs to {a mathematical formula}Σ2p. We prove {a mathematical formula}Π2p-hardness by considering a reduction from the validity problem for quantified Boolean formulas (QBFs) of the form {a mathematical formula}∀A.(∃B.α) where {a mathematical formula}A={a1,…,an} and {a mathematical formula}B={b1,…,bm} are two disjoint sets of propositional atoms and {a mathematical formula}Var(α)=A∪B. Consider such a quantified Boolean formula (QBF). We associate with this QBF in polynomial time the symbol translation {a mathematical formula}σ∈PROPYX with {a mathematical formula}X={x0,x1,…,xn}, {a mathematical formula}Y=A∪B∪{new} and {a mathematical formula}new∉A∪B, defined by {a mathematical formula}σ(x0)=α∧new and for each {a mathematical formula}i∈1,…,n, {a mathematical formula}σ(xi)=ai. σ satisfies REV (or equivalently AIP) iff {a mathematical formula}∀s0,…,sn∈{+,−}, {a mathematical formula}⋀xi∈Xσ(xi)si is consistent iff {a mathematical formula}∀s0∈{+,−}∀A{a mathematical formula}(α∧new)s0 is consistent iff {a mathematical formula}∀A.(¬α∨¬new) is consistent and ∀A{a mathematical formula}(α∧new) is consistent. Clearly enough, the QBF {a mathematical formula}∀A.(¬α∨¬new) is consistent (every interpretation ω such that {a mathematical formula}ω(new)=0 is a model of it). Finally, the QBF {a mathematical formula}∀A.(α∧new) is consistent iff the QBF {a mathematical formula}∀A.α is consistent iff the QBF {a mathematical formula}∀A.(∃B.α) is valid. The fact that the latter problem is {a mathematical formula}Π2p-complete completes the proof.The fact that the problem is {a mathematical formula}coNP-complete if {a mathematical formula}|X|=|Y| comes from Corollary 2. Indeed, if {a mathematical formula}|X|=|Y|, REV and BAP are equivalent properties. The problem is in {a mathematical formula}P if {a mathematical formula}|X|&gt;|Y|, since from Corollary 2σ satisfies REV only if {a mathematical formula}|X|⩾|Y|.  □
      </list-item>
     </list>
     <paragraph label="Proposition 11">
      The KM drastic update operator{a mathematical formula}⋄Dis ⊤-language independent.
     </paragraph>
     <paragraph label="Proof">
      Let σ be any symbol translation from {a mathematical formula}PROPYX, K be a base from {a mathematical formula}PROPX and μ be a formula from {a mathematical formula}PROPX. By definition of {a mathematical formula}⋄D, we have {a mathematical formula}K⋄Dμ≡K if {a mathematical formula}K⊨μ, ≡μ otherwise; hence, we have {a mathematical formula}σ(K)⋄Dσ(μ)≡σ(K) if {a mathematical formula}σ(K)⊨σ(μ), {a mathematical formula}≡σ(μ) otherwise. Yet from point 1 of Corollary 1, we have {a mathematical formula}K⊨μ if and only if {a mathematical formula}σ(K)⊨σ(μ). Thus, {a mathematical formula}σ(K)⋄Dσ(μ)≡σ(K) if {a mathematical formula}K⊨μ, {a mathematical formula}≡σ(μ) otherwise. Therefore, {a mathematical formula}σ(K)⋄Dσ(μ)≡σ(K⋄Dμ).  □
     </paragraph>
     <paragraph label="Proposition 12">
      Let P be a property on symbol translations which does not imply AIP, i.e., there exists a symbol translation satisfying P but not satisfying AIP. Then no belief revision operator ∘ satisfying{a mathematical formula}(R2)and{a mathematical formula}(R3)and no belief merging operator Δ satisfying{a mathematical formula}(IC1)and{a mathematical formula}(IC2)is P-language independent.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}PS={x1,…,xn}, and let σ be a symbol translation from {a mathematical formula}PROPYX that does not satisfy AIP. This means that {a mathematical formula}∃s1,…,sn∈{+,−}, {a mathematical formula}⋀xi∈PSσ(xi)si is inconsistent, or equivalently, {a mathematical formula}σ(⋀xi∈PSxisi) is inconsistent. Thus, there is a consistent formula {a mathematical formula}ασ such that {a mathematical formula}σ(ασ) is inconsistent. Now, consider a belief revision operator ∘ satisfying the rationality postulates {a mathematical formula}(R2) and {a mathematical formula}(R3) and a belief merging operator Δ satisfying the rationality postulates {a mathematical formula}(IC1) and {a mathematical formula}(IC2). For every consistent formula α, {a mathematical formula}(R2) implies that {a mathematical formula}α∘⊤≡α and {a mathematical formula}(IC2) implies that {a mathematical formula}Δ(〈α〉)⊤≡α. Thus, both {a mathematical formula}α∘⊤ and {a mathematical formula}Δ(〈α〉)⊤ are consistent when α is consistent. If ∘ (resp. Δ) would satisfy P-language independence with P a property on symbol translations which does not imply AIP, then for every σ satisfying P but not satisfying AIP, {a mathematical formula}(R3) (resp. {a mathematical formula}(IC1)) would imply that {a mathematical formula}σ(ασ)∘σ(⊤)≡σ(ασ) (resp. {a mathematical formula}Δ(σ(〈ασ〉))σ(⊤)≡σ(ασ)) is consistent, which is not the case.  □
     </paragraph>
     <paragraph label="Proposition 13">
      <list>
       <list-item label="1.">
        The distance-based merging operator{a mathematical formula}ΔdD,Σ, based on the drastic distance{a mathematical formula}dDand on the aggregation function Σ, is the only IC merging operator that is AIP-language independent; it is also the only IC merging operator that is BAP-language independent;
       </list-item>
       <list-item label="2.">
        The drastic revision operator{a mathematical formula}∘Dis the only AGM revision operator that is AIP-language independent; it is also the only AGM revision operator that is BAP-language independent;
       </list-item>
       <list-item label="3.">
        The drastic update operator{a mathematical formula}⋄Dis the only KM update operator that is AIP-language independent; it is also the only KM update operator that is BAP-language independent.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      In this proof, we denote by {a mathematical formula}ϕM a formula whose models are those of the set M. To alleviate heavy notations, for every base {a mathematical formula}K,K′, {a mathematical formula}K∖K′ will stand for {a mathematical formula}ϕMod(K)∖Mod(K′).
     </paragraph>
     <list>
      <list-item label="1.">
       We first show that the distance-based merging operator {a mathematical formula}ΔdD,Σ is AIP-language independent.Let {a mathematical formula}X⊆PS, E be a profile of bases containing formulae from {a mathematical formula}PROPX, μ be a formula from {a mathematical formula}PROPX and σ be a symbol translation from {a mathematical formula}PROPYX satisfying AIP.By construction, the models of {a mathematical formula}ΔμdD,Σ(E) are precisely the models of μ satisfying a maximal number of bases in the profile E.Let {a mathematical formula}ω′ be an interpretation over Y such that {a mathematical formula}ω′⊨σ(μ); since μ is equivalent to the disjunction of all its canonical terms associated with its models, there must exist an interpretation ω over X such that {a mathematical formula}ω′⊨σ(ω).Consider now any ω be an interpretation over X, and {a mathematical formula}ω′ an interpretation over Y such that {a mathematical formula}ω′⊨σ(ω). Then (A) for every base K in the profile E, {a mathematical formula}ω′⊨σ(K) if and only if {a mathematical formula}ω⊨K. Indeed, if {a mathematical formula}ω⊨K, then from point 1 of Corollary 1, we have {a mathematical formula}σ(ω)⊨σ(K), and by transitivity of ⊨, we also have {a mathematical formula}ω′⊨σ(K); and if {a mathematical formula}ω⊨¬K, then from point 1 of Corollary 1, we have {a mathematical formula}σ(ω)⊨¬σ(K), and by transitivity of ⊨, we also have {a mathematical formula}ω′⊨¬σ(K). Similarly, we can show that {a mathematical formula}ω′⊨σ(μ) if and only if {a mathematical formula}ω⊨μ.Accordingly, if ω is a model of μ satisfying a maximal number (say k) of bases of E, then every model {a mathematical formula}ω′ of {a mathematical formula}σ(ω) is a model of {a mathematical formula}σ(μ) satisfying k bases of {a mathematical formula}σ(E); furthermore, there is no model {a mathematical formula}ω″ of {a mathematical formula}σ(μ) satisfying at least {a mathematical formula}k+1 bases of {a mathematical formula}σ(E): if this were the case, then there would exist a model {a mathematical formula}ω‴ of μ such that {a mathematical formula}ω″⊨σ(ω‴), and because of (A), {a mathematical formula}ω‴ would satisfy at least {a mathematical formula}k+1 bases of E, contradicting the fact that no model of μ satisfies more than k bases of E. Hence, if {a mathematical formula}ω⊨ΔμdD,Σ(E), then every model {a mathematical formula}ω′ of {a mathematical formula}σ(ω) satisfies {a mathematical formula}ω′⊨Δσ(μ)dD,Σ(σ(E)).The other way around, let {a mathematical formula}ω′ be a model of {a mathematical formula}σ(μ) satisfying a maximal number (say k) of bases of {a mathematical formula}σ(E). Let ω be any model of μ such that {a mathematical formula}ω′⊨σ(ω). From (A), we know that ω satisfies k bases of E. Furthermore, there is no model {a mathematical formula}ω‴ of μ satisfying at least {a mathematical formula}k+1 bases of E: indeed, consider any model {a mathematical formula}ω″ of {a mathematical formula}σ(ω‴) (since σ satisfies AIP, {a mathematical formula}σ(ω‴) is necessarily consistent, hence such a model {a mathematical formula}ω″ exists). Since {a mathematical formula}ω‴⊨μ, we have {a mathematical formula}σ(ω‴)⊨σ(μ) and by transitivity of ⊨, {a mathematical formula}ω″ is a model of {a mathematical formula}σ(μ). Because of (A), {a mathematical formula}ω″ would satisfy at least {a mathematical formula}k+1 bases of {a mathematical formula}σ(E), contradicting the fact that no model of {a mathematical formula}σ(μ) satisfies more than k bases of {a mathematical formula}σ(E). Hence, if {a mathematical formula}ω′⊨Δσ(μ)dD,Σ(σ(E)), then for every {a mathematical formula}ω⊨μ such that {a mathematical formula}ω′⊨σ(ω), we have {a mathematical formula}ω⊨ΔμdD,Σ(E).Altogether, we get that {a mathematical formula}σ(ΔμdD,Σ(E))≡Δσ(μ)dD,Σ(σ(E)), showing that the distance-based merging operator {a mathematical formula}ΔdD,Σ is AIP-language independent.Now, let Δ be an IC merging operator that is BAP-language independent. Let us first show that for every consistent base K, for every interpretation {a mathematical formula}ω,ω′, {a mathematical formula}ω&lt;Kω′ implies {a mathematical formula}ω⊨K. Let K be a consistent base, {a mathematical formula}ω,ω′ two interpretations such that {a mathematical formula}ω&lt;Kω′. Since {a mathematical formula}⩽K is a preorder, {a mathematical formula}ω&lt;Kω′ implies that ω and {a mathematical formula}ω′ are distinct interpretations. Towards a contradiction, suppose {a mathematical formula}ω⊭K. Let R be a relation on {a mathematical formula}2PS×2PS defined as {a mathematical formula}R(ω)={ω′}, {a mathematical formula}R(ω′)={ω} and for every other interpretation {a mathematical formula}ω″, {a mathematical formula}R(ω″)={ω″}. R obviously is a one-to-one correspondence. Thus from point 2 of Proposition 6, R is the image by the semantical mapping Ψ of a symbol translation {a mathematical formula}σR that satisfies BAP. Suppose that {a mathematical formula}ω′⊨K. Under the assumption that {a mathematical formula}ω⊭K, using condition (2) of the syncretic assignment we get that {a mathematical formula}ω′&lt;Kω, which contradicts {a mathematical formula}ω&lt;Kω′. Hence, under the assumption {a mathematical formula}ω⊭K, we must have {a mathematical formula}ω′⊭K. Given the definition of R, we have {a mathematical formula}σR(K)≡K and {a mathematical formula}σR(ϕ{ω,ω′})≡ϕ{ω,ω′}. Now, since Δ is BAP-language independent, we have {a mathematical formula}σR(Δϕ{ω,ω′}(〈K〉))≡ΔσR(ϕ{ω,ω′})(σR(〈K〉)), or equivalently, {a mathematical formula}σR(Δϕ{ω,ω′}(〈K〉))≡Δϕ{ω,ω′}(〈K〉). Since {a mathematical formula}Δϕ{ω,ω′}(〈K〉)≡ω (from the fact that {a mathematical formula}ω&lt;Kω′ and from Theorem 1) we get {a mathematical formula}σR(Δϕ{ω,ω′}(K))≡σR(ω)≡ω, this contradicts {a mathematical formula}σR(ω)≡ω′, thus this contradicts the initial assumption {a mathematical formula}ω⊭K. Therefore, for every consistent base K, for every interpretation {a mathematical formula}ω,ω′, {a mathematical formula}ω&lt;Kω′ implies {a mathematical formula}ω⊨K. Taking this last result together with conditions (1) and (2) of the syncretic assignment, we get for every consistent base K, for every interpretation {a mathematical formula}ω,ω′,{a mathematical formula} The equivalence reported at Eq. (1) shows that every IC merging operator that is BAP-language independent corresponds to a syncretic assignment that ranks all the worlds over at most two plausibility levels for any singleton profile.We intend now to prove that for every consistent base K, {a mathematical formula}K′, for every interpretation ω, {a mathematical formula}ω′, if {a mathematical formula}ω&lt;Kω′ and {a mathematical formula}ω′&lt;K′ω, then {a mathematical formula}ω≃〈K,K′〉ω′. Let {a mathematical formula}ω,ω′ be two interpretations, {a mathematical formula}K,K′ be two consistent bases. Assume that {a mathematical formula}ω&lt;Kω′ and {a mathematical formula}ω′&lt;K′ω. Towards a contradiction, suppose that {a mathematical formula}ω′&lt;〈K,K′〉ω (the remaining case can be treated in a similar way due to the fact that {a mathematical formula}(ω,K), and {a mathematical formula}(ω′,K′) play symmetric roles in the statement to be proven). From Eq. (1) above, {a mathematical formula}ω∈Mod(K)∖Mod(K′) and {a mathematical formula}ω′∈Mod(K′)∖Mod(K). Thus we have {a mathematical formula}K⊭K′ and {a mathematical formula}K′⊭K. There are two remaining cases:
       <list>
        Case 1: assume {a mathematical formula}K∧K′⊨⊥. Let {a mathematical formula}Mod(K)={ω1,…,ωp}. Let R be a relation on {a mathematical formula}2PS×2PS defined as {a mathematical formula}R(ωi)={ωi+1} for every {a mathematical formula}i∈{1,…,p−1}, {a mathematical formula}R(ωp)={ω1} and for every interpretation {a mathematical formula}ω″⊭K, {a mathematical formula}R(ω″)={ω″}. Note that ω is one of the {a mathematical formula}ωi (for {a mathematical formula}i∈{1,…,p}) and that {a mathematical formula}R(ω′)={ω′}. R is obviously a one-to-one correspondence. Thus from point 2 of Proposition 6, R is the image by the semantical mapping Ψ of a symbol translation {a mathematical formula}σR that satisfies BAP.Our assumption is that
       </list>
       <paragraph>
        {a mathematical formula}ω&lt;Kω′, {a mathematical formula}ω′&lt;K′ω and {a mathematical formula}ω′&lt;〈K,K′〉ω. Since Δ is BAP-language independent, we have for every {a mathematical formula}j⩾1, {a mathematical formula}σRj(ω)&lt;σRj(K)σRj(ω′), {a mathematical formula}σRj(ω′)&lt;σRj(K′)σRj(ω) and {a mathematical formula}σRj(ω′)&lt;〈σRj(K),σRj(K′)〉σRj(ω), where {a mathematical formula}σRj=σR∘⋯∘σR︸j. Yet by construction of R, on the one hand we have for every {a mathematical formula}j⩾1, {a mathematical formula}σRj(K)≡K, {a mathematical formula}σRj(K′)≡K′ and {a mathematical formula}σRj(ω′)≡ω′; on the other hand we have for every {a mathematical formula}ωi⊨K, there exists {a mathematical formula}j⩾1 such that {a mathematical formula}σRj(ω)≡ωi. This implies that for every {a mathematical formula}ωi⊨K, {a mathematical formula}ωi&lt;〈K〉ω′, {a mathematical formula}ω′&lt;〈K′〉ωi and {a mathematical formula}ω′&lt;〈K,K′〉ωi. Hence, there is an interpretation {a mathematical formula}ω′⊨K′ such that for every interpretation {a mathematical formula}ωi⊨K, {a mathematical formula}ω′&lt;〈K,K′〉ωi. However, since {a mathematical formula}ω′⊨K′, condition (4) of the syncretic assignment requires that there exists {a mathematical formula}ωi⊨K such that {a mathematical formula}ωi⩽〈K,K′〉ω′, contradiction.
       </paragraph>
       <list>
        <list-item label="•">
         Case 2: assume {a mathematical formula}K∧K′⊭⊥. Notice that since {a mathematical formula}K⊭K′ and {a mathematical formula}K′⊭K, each of {a mathematical formula}K∖K′ and {a mathematical formula}K′∖K is a consistent base. From Eq. (1), we know that {a mathematical formula}ω&lt;〈K∖K′〉ω′ and {a mathematical formula}ω′&lt;〈K′∖K〉ω. Thus, from Case 1 above we deduce that {a mathematical formula}ω≃〈K,K′∖K〉ω′ (i), {a mathematical formula}ω≃〈K′,K∖K′〉ω′ (ii) and {a mathematical formula}ω≃〈K∖K′,K′∖K〉ω′ (iii). On the one hand, from (i), (ii) and from condition (5) of the syncretic assignment we get that {a mathematical formula}ω≃〈K,K′,K∖K′,K′∖K〉ω′. On the other hand, from (iii), from the initial assumption that {a mathematical formula}ω′&lt;〈K,K′〉ω and from condition (6) of the syncretic assignment we get that {a mathematical formula}ω′&lt;〈K,K′,K∖K′,K′∖K〉ω, contradiction. Therefore, we have for every consistent base {a mathematical formula}K,K′ and every interpretation {a mathematical formula}ω,ω′,{a mathematical formula}Let us now show that for every interpretation {a mathematical formula}ω,ω′, every profile E and every consistent base K, if {a mathematical formula}ω&lt;Eω′, then {a mathematical formula}ω⩽E⊔〈K〉ω′. We prove it by induction on the dimension n of E:
        </list-item>
        <list-item label="•">
         Base case ({a mathematical formula}n=1): let {a mathematical formula}ω&lt;〈K〉ω′. Then we have {a mathematical formula}ω⩽〈K〉ω′. Let {a mathematical formula}K′ be a consistent base, if {a mathematical formula}ω⩽〈K′〉ω′, then by condition (5) of the syncretic assignment we get {a mathematical formula}ω⩽〈K,K′〉ω′. In the remaining case, i.e., if {a mathematical formula}ω′&lt;〈K′〉ω, then using Eq. (2) we get {a mathematical formula}ω≃〈K,K′〉ω′, which implies that {a mathematical formula}ω⩽〈K〉ω′.
        </list-item>
        <list-item label="•">
         Inductive step ({a mathematical formula}n&gt;1): The implication to be proven, i.e., if {a mathematical formula}ω&lt;Eω′, then {a mathematical formula}ω⩽E⊔〈K〉ω′, is equivalent to its contrapositive, which is equivalent to: if {a mathematical formula}ω&lt;E⊔〈K〉ω′ then {a mathematical formula}ω⩽Eω′. Thus, the induction hypothesis can be stated as: for every base {a mathematical formula}K′ of E, {a mathematical formula}ω&lt;Eω′ then {a mathematical formula}ω⩽E∖〈K′〉ω′. Consider ω and {a mathematical formula}ω′ such that {a mathematical formula}ω&lt;E⊔〈K〉ω′. Since {a mathematical formula}⩽E⊔〈K〉 is total, this is equivalent to {a mathematical formula}ω′⩽̸E⊔〈K〉ω. Using condition (5) of the syncretic assignment, this implies that ({a mathematical formula}ω′⩽̸Eω or {a mathematical formula}ω′⩽̸Kω), or equivalently, ({a mathematical formula}ω&lt;Eω′ or {a mathematical formula}ω&lt;〈K〉ω′). If {a mathematical formula}ω&lt;Eω′ then {a mathematical formula}ω⩽Eω′ holds, which is the expected conclusion. Hence it remains to consider the case when {a mathematical formula}ω≮Eω′ (which is equivalent to {a mathematical formula}ω′⩽Eω) and {a mathematical formula}ω&lt;〈K〉ω′. If {a mathematical formula}ω′⩽Eω then there are two possible cases: {a mathematical formula}ω′≃Eω and {a mathematical formula}ω′&lt;Eω. In the first case {a mathematical formula}ω′≃Eω, we have {a mathematical formula}ω⩽Eω′ holds, which is the expected conclusion. In the second case {a mathematical formula}ω′&lt;Eω, by induction hypothesis, we have that for every base {a mathematical formula}K′ of E, {a mathematical formula}ω′⩽E∖〈K′〉ω. Furthermore, when {a mathematical formula}ω′&lt;Eω, condition (5) on the syncretic assignment requires that there exists a base {a mathematical formula}K″ of E such that {a mathematical formula}ω′&lt;〈K″〉ω. Exploiting the induction hypothesis with {a mathematical formula}K′=K″, we get that {a mathematical formula}ω′⩽E∖〈K″〉ω. Using Eq. (2), from {a mathematical formula}ω&lt;〈K〉ω′ and {a mathematical formula}ω′&lt;〈K″〉ω, we derive that {a mathematical formula}ω≃〈K,K″〉ω′, which implies that {a mathematical formula}ω′⩽〈K,K″〉ω. Using condition (5) on the syncretic assignment, from {a mathematical formula}ω′⩽E∖〈K″〉ω and {a mathematical formula}ω′⩽〈K,K″〉ω, we derive that {a mathematical formula}ω′⩽E⊔〈K〉ω, which contradicts {a mathematical formula}ω&lt;E⊔〈K〉ω′. Hence, when {a mathematical formula}ω&lt;E⊔〈K〉ω′ holds, it cannot be the case that {a mathematical formula}ω′&lt;Eω. Stated otherwise, we must also have {a mathematical formula}ω⩽Eω′ in the second case. This is the expected conclusion: for every interpretation {a mathematical formula}ω,ω′, for every profile E and every consistent base K,{a mathematical formula}Now, for every profile E and every interpretation ω let us denote {a mathematical formula}|ω(E)|=|{Ki base of {a mathematical formula}E|ω⊨Ki}|, i.e., the number of belief bases in E which are satisfied by ω. We intend to prove that for every profile E and every interpretation {a mathematical formula}ω,ω′, {a mathematical formula}ω&lt;Eω′ if and only if {a mathematical formula}|ω(E)|&gt;|ω′(E)|. We prove it by induction on the dimension n of E:
        </list-item>
        <list-item label="•">
         Base case ({a mathematical formula}n=1): using Eq. (1), {a mathematical formula}ω&lt;〈K〉ω′ if and only if {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊭K, this directly leads us to {a mathematical formula}|ω(E)|&gt;|ω′(E)|.
        </list-item>
        <list-item label="•">
         Base case ({a mathematical formula}n=2): let us show that {a mathematical formula}ω&lt;〈K,K′〉ω′ if and only if ({a mathematical formula}ω⩽〈K〉ω′ and {a mathematical formula}ω&lt;〈K′〉ω′) or ({a mathematical formula}ω&lt;〈K〉ω′ and {a mathematical formula}ω⩽〈K′〉ω′).(Only If) Direct from condition (6) of the syncretic assignment.(If) Let {a mathematical formula}ω&lt;〈K,K′〉ω′. Towards a contradiction, assume {a mathematical formula}ω′&lt;〈K〉ω. Assuming {a mathematical formula}ω′⩽〈K′〉ω (respectively, {a mathematical formula}ω&lt;〈K′〉ω′) contradicts {a mathematical formula}ω&lt;〈K,K′〉ω′ by condition (5) of the syncretic assignment (respectively, by Eq. (2)). Hence, {a mathematical formula}ω⩽〈K〉ω′. Since K and {a mathematical formula}K′ play symmetric roles in the equivalence to be proven, we can prove in a similar way that {a mathematical formula}ω⩽〈K′〉ω′. Now, assuming {a mathematical formula}ω≃〈K〉ω′ and {a mathematical formula}ω≃〈K′〉ω′ contradicts {a mathematical formula}ω&lt;〈K,K′〉ω′ by condition (5) of the syncretic assignment. Hence, ({a mathematical formula}ω⩽〈K〉ω′ and {a mathematical formula}ω&lt;〈K′〉ω′) or ({a mathematical formula}ω&lt;〈K〉ω′ and {a mathematical formula}ω⩽〈K′〉ω′).Since {a mathematical formula}ω&lt;〈K,K′〉ω′ if and only if ({a mathematical formula}ω⩽〈K〉ω′ and {a mathematical formula}ω&lt;〈K′〉ω′) or ({a mathematical formula}ω&lt;〈K〉ω′ and {a mathematical formula}ω⩽〈K′〉ω′), then by Eq. (1) and condition (2) on the syncretic assignment we deduce that {a mathematical formula}ω&lt;〈K,K′〉ω′ if and only if {a mathematical formula}|ω(〈K,K′〉)|&gt;|ω′(〈K,K′〉)|.
        </list-item>
        <list-item label="•">
         Inductive step ({a mathematical formula}n⩾2): assume that for every profile E such that {a mathematical formula}|E|=k with {a mathematical formula}k⩽n, we have {a mathematical formula}ω&lt;Eω′ if and only if {a mathematical formula}|ω(E)|&gt;|ω′(E)|. Let E be a profile of dimension {a mathematical formula}n+1. We need to show that {a mathematical formula}ω&lt;Eω′ if and only if {a mathematical formula}|ω(E)|&gt;|ω′(E)|.(Only If) Assume that {a mathematical formula}ω&lt;Eω′. Let K be a base of E:
         <list>
          Assume {a mathematical formula}ω&lt;〈K〉ω′. Since {a mathematical formula}ω&lt;Eω′, then using the contrapositive of the implication reported at Eq. (3), we have {a mathematical formula}ω⩽E∖〈K〉ω′. By induction hypothesis, we have {a mathematical formula}|ω(〈K〉)|&gt;|ω′(〈K〉)| and {a mathematical formula}|ω(E∖〈K〉)|⩾|ω′(E∖〈K〉)|. Hence, {a mathematical formula}|ω(E)|&gt;|ω′(E)|.Assume {a mathematical formula}ω≃〈K〉ω′. Since {a mathematical formula}ω&lt;Eω′, then by condition (5) of the syncretic assignment we have {a mathematical formula}ω&lt;E∖〈K〉ω′. By induction hypothesis, we have {a mathematical formula}|ω(〈K〉)|=|ω′(〈K〉)| and {a mathematical formula}|ω(E∖〈K〉)|&gt;|ω′(E∖〈K〉)|. Hence, {a mathematical formula}|ω(E)|&gt;|ω′(E)|.Assume {a mathematical formula}ω′&lt;〈K〉ω. Since {a mathematical formula}ω&lt;Eω′, then by condition (5) of the syncretic assignment there exists a belief base {a mathematical formula}K′∈E such that {a mathematical formula}ω&lt;〈K′〉ω′. By Eq. (2), we get {a mathematical formula}ω≃〈K,K′〉ω′. And by condition (5) of the syncretic assignment, we necessarily have {a mathematical formula}ω&lt;E∖〈K,K′〉ω′. By induction hypothesis, we have {a mathematical formula}|ω(〈K,K′〉)|=|ω′(〈K,K′〉)| and {a mathematical formula}|ω(E∖〈K,K′〉)|&gt;|ω′(E∖〈K,K′〉)|. Hence, {a mathematical formula}|ω(E)|&gt;|ω′(E)|.Therefore, we have for every profile
         </list>
         <paragraph>
          E and every interpretation {a mathematical formula}ω,ω′,{a mathematical formula}Lastly, it is easy to verify that the syncretic assignment satisfying the equivalence at Eq. (4) above is associated with the distance-based merging operator {a mathematical formula}ΔdD,Σ. Hence, we have just proved that {a mathematical formula}ΔdD,Σ is the only IC merging operator that is BAP-language independent.
         </paragraph>
        </list-item>
       </list>
      </list-item>
      <list-item label="2.">
       The drastic AGM revision operator {a mathematical formula}∘D is obviously AIP-language independent and BAP-language independent, since it corresponds to the distance-based merging operator {a mathematical formula}ΔdD,Σ restricted to singleton profiles (i.e., {a mathematical formula}K∘Dμ≡ΔμdD,Σ(〈K〉)), and {a mathematical formula}ΔdD,Σ is AIP-language independent and BAP-language independent (cf. point 1 of this proof). Now, Eq. (1) (cf. point 1 of this proof) also holds for any AGM revision operator that is BAP-language independent. Indeed, to prove Eq. (1), we only used conditions (1) and (2) of the syncretic assignment of the IC merging operator, plus the assumption that this operator is BAP-language independent. The point is that conditions (1) and (2) of the faithful assignment for AGM revision operators are equivalent to conditions (1) and (2) of the syncretic assignment for IC merging operators. Thus, Eq. (1) also holds for any AGM revision operator ∘ that is BAP-language independent. Now, from Eq. (1), condition (1) of the faithful assignment and Theorem 2 [12] (which requires that the faithful assignment associated with an AGM revision operator ∘ maps every base K to a total preorder {a mathematical formula}⩽K), the faithful assignment associated with ∘ must be such that for every base K, and interpretations ω, {a mathematical formula}ω′, {a mathematical formula}ω≃Kω′ iff ({a mathematical formula}ω⊨K and {a mathematical formula}ω′⊨K) or ({a mathematical formula}ω⊭K and {a mathematical formula}ω′⊭K), and {a mathematical formula}ω&lt;Kω′ iff {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊭K. Thus, whatever the BAP-language independent AGM revision operator ∘, there is a unique total preorder {a mathematical formula}⩽K associated with K by the faithful assignment corresponding to ∘. This shows that every AGM revision operator which is BAP-language independent coincides with {a mathematical formula}∘D. Hence this is also the case for AIP-language independence: every AGM revision operator which is AIP-language independent coincides with {a mathematical formula}∘D.
      </list-item>
      <list-item label="3.">
       From Proposition 11, the drastic update operator {a mathematical formula}⋄D is obviously AIP-language independent and BAP-language independent. Moreover, it is the only KM update operator that is BAP-language independent. Indeed, Eq. (1) (cf. point 1 of this proof) also holds for any KM update operator that is BAP-language independent. Indeed, to prove Eq. (1), we only used conditions (1) and (2) of the syncretic assignment of the IC merging operator, plus the assumption that this operator is BAP-language independent. Especially, we did not take advantage of the fact that {a mathematical formula}⩽K is total. Furthermore, conditions (1) and (2) of the faithful assignment for AGM revision operators (or for KM update operators) are equivalent to conditions (1) and (2) of the syncretic assignment for IC merging operators. Thus, Eq. (1) also holds for any KM update operator that is BAP-language independent. Once this is stated, let us consider any KM update operator ⋄ that is BAP-language independent. From Theorem 3 [12], for any base K and formula μ, we have {a mathematical formula}Mod(K⋄μ)=⋃ω⊨Kmin(Mod(μ),⩽ω){a mathematical formula}=⋃ω⊨KMod(ω⋄μ). For every pair of distinct interpretations ω and {a mathematical formula}ω′, by condition (2) of the faithful assignment, we have {a mathematical formula}ω&lt;ωω′. Hence if {a mathematical formula}ω⊨μ, then {a mathematical formula}ω⋄μ≡ω≡ω⋄Dμ. In the remaining case (i.e., if {a mathematical formula}ω⊭μ), then from Eq. (1), for every pair {a mathematical formula}ω′ and {a mathematical formula}ω″ of models of μ, we have {a mathematical formula}ω′≮ωω″ and {a mathematical formula}ω″≮ωω′, which means that ω and {a mathematical formula}ω′ are either indifferent w.r.t. {a mathematical formula}⩽ω (i.e., {a mathematical formula}ω′≃ωω″) or incomparable w.r.t. {a mathematical formula}⩽ω (i.e., {a mathematical formula}ω′⩽̸ωω″ and {a mathematical formula}ω″⩽̸ωω′). Whatever the case, we have {a mathematical formula}min({ω′,ω″},⩽ω)={ω′,ω″}. Thus, when {a mathematical formula}ω⊭μ, we have {a mathematical formula}min(Mod(μ),⩽ω)=Mod(μ). This shows that when {a mathematical formula}ω⊭μ, we have {a mathematical formula}ω⋄μ≡μ≡ω⋄Dμ, and this completes the proof.  □
      </list-item>
     </list>
     <paragraph label="Proposition 14">
      There exist belief revision (resp. belief merging, belief update) operators which satisfy all AGM postulates (resp. all IC postulates, all KM postulates) but are not SIN-language independent.
     </paragraph>
     <paragraph label="Proof">
      Consider a belief revision operator ∘ and a belief update operator ⋄, both associated with a faithful assignment such that:{a mathematical formula}{a mathematical formula} when {a mathematical formula}PS={a,b}. Now, let {a mathematical formula}σ:a↦b; {a mathematical formula}b↦a be a bijective substitution over PS. Let {a mathematical formula}α=a∧¬b and {a mathematical formula}β=b. We have {a mathematical formula}α∘β≡α⋄β≡¬a∧b. We also have {a mathematical formula}σ(α)≡¬a∧b and {a mathematical formula}σ(β)≡a. We finally have {a mathematical formula}σ(α)∘σ(β)≡σ(α)⋄σ(β)≡a∧b. This is not equivalent to {a mathematical formula}σ(α∘β) or {a mathematical formula}σ(α⋄β), which are both equivalent to {a mathematical formula}a∧¬b.The proof is similar for a belief merging operator, considering a profile with a unique base α and β as integrity constraints. Especially, what remains to be done is to show that there exists a syncretic assignment which is “compatible” with the faithful assignment above. A syncretic assignment is a mapping which associates with every profile a complete preorder over the interpretations (while a faithful assignment associates with every base a complete preorder over the interpretations). The conditions that a syncretic assignment have to satisfied are more demanding than those that faithful assignments must satisfy (see [9] for details). Especially, it is not the case that every faithful assignment can be extended to a syncretic assignment. Let us show that this is nevertheless the case for the assignment considered above. Recall that every merging operator based on a pseudo-distance and the aggregation function Σ is an IC merging operator [9]. Consider for instance any mapping d from {a mathematical formula}2PS×2PS to the natural numbers satisfying {a mathematical formula}d(ω,ω)=0 for every interpretation ω, {a mathematical formula}d(ω1,ω2)=d(ω2,ω1) for every pair of interpretations {a mathematical formula}ω1, {a mathematical formula}ω2, and:
      <list>
       {a mathematical formula}d(01,11)=2,{a mathematical formula}d(01,10)=3,{a mathematical formula}d(00,01)=d(10,11)=4,{a mathematical formula}d(00,10)=5,{a mathematical formula}d(00,11)=6.By construction,
      </list>
      <paragraph>
       d is a pseudo-distance (in fact, it is a distance, i.e., the triangular inequality is also satisfied by d). Consider any admissible aggregation function (e.g., Σ). Now it is easy to check that we have:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}d(10,10)=0&lt;d(10,01)=3&lt;d(10,11)=4&lt;d(10,00)=5,
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(01,01)=0&lt;d(01,11)=2&lt;d(01,10)=3&lt;d(01,00)=4.
       </list-item>
      </list>
      <paragraph>
       Accordingly, we have {a mathematical formula}Δbd,Σ({a∧¬b})≡¬a∧b, and {a mathematical formula}Δad,Σ({b∧¬a})≡a∧b. Clearly, for {a mathematical formula}σ:a↦b; {a mathematical formula}b↦a a bijective symbol translation from PS to PS, {a mathematical formula}α=a∧¬b and {a mathematical formula}β=b, we do not have {a mathematical formula}σ(Δβd,Σ(〈α〉)) equivalent to {a mathematical formula}Δσ(β)d,Σ(〈σ(α)〉).  □
      </paragraph>
     </paragraph>
     <paragraph label="Proposition 15">
      Every belief change operator based on a decomposable distance is SIN-language independent.
     </paragraph>
     <paragraph label="Proof">
      Let σ be a symbol translation satisfying SIN, i.e., a bijection from X to Y. We can associate with σ a symbol translation {a mathematical formula}σ′ from PS to PS, with {a mathematical formula}PS={x1,…,xn} defined by: for every {a mathematical formula}x∈X, {a mathematical formula}σ′(x)=σ(x), and for every {a mathematical formula}x∈PS∖X, {a mathematical formula}σ′(x)=τ(x), where τ is any bijection from {a mathematical formula}PS∖X to {a mathematical formula}PS∖Y. It is easy to see that for every formula α from {a mathematical formula}PROPX, {a mathematical formula}σ(α)=σ′(α). Moreover, {a mathematical formula}σ′ is a bijection from PS to PS, so it satisfies SIN. Therefore, a propositional operator ω is SIN-language independent iff for every n-propositional structure Σ over X, for every bijection {a mathematical formula}σ′ from PS to PS, we have {a mathematical formula}Ω(σ′(Σ))≡σ′(Ω(Σ)).From point 4 of Proposition 6, {a mathematical formula}Rσ′ is a bijection from {a mathematical formula}2PS to {a mathematical formula}2PS, so for proving the result, it is enough to show that for every pair of interpretations {a mathematical formula}ω1, {a mathematical formula}ω2 over PS, we have {a mathematical formula}d(ω1,ω2)=d(σ′(ω1),σ′(ω2)). Since d is decomposable, there exists a mapping {a mathematical formula}fd:Rn→R which is symmetric in each argument and a mapping {a mathematical formula}gd:{0,1}×{0,1}→R such that {a mathematical formula}d(ω1,ω2)=fd(gd(ω1(x1),ω2(x1)),…,gd(ω1(xn),ω2(xn))). Thus, we have to show that {a mathematical formula}fd(gd(ω1(x1),ω2(x1)),…,gd(ω1(xn),ω2(xn)))=d(σ′(ω1),σ′(ω2))=fd(gd(σ′(ω1)(x1),σ′(ω2)(x1)),…,gd(σ′(ω1)(xn),σ′(ω2)(xn))). Slightly abusing the notations, let us also note {a mathematical formula}σ′ the permutation over {a mathematical formula}{1,…,n} such that for any {a mathematical formula}i∈1,…,n, {a mathematical formula}σ(i)=j if and only if {a mathematical formula}σ′(xi)=xj. Now, for every {a mathematical formula}xi∈PS, if {a mathematical formula}σ′(xi)=xj, we have {a mathematical formula}ω1(xi)=σ′(ω1)(xj)=σ′(ω1)(xσ′(i)) and {a mathematical formula}ω2(xi)=σ′(ω2)(xj)=σ′(ω2)(xσ′(i)). As a consequence, {a mathematical formula}d(ω1,ω2)=fd(gd(ω1(x1),ω2(x1)),…,gd(ω1(xn),ω2(xn)))=fd(gd(σ′(ω1)(xσ(1)),σ′(ω2)(xσ(1))),…,gd(σ′(ω1)(xσ(n)),σ′(ω2)(xσ′(n)))). For every pair of interpretations {a mathematical formula}ω1, {a mathematical formula}ω2 over PS, we have {a mathematical formula}d(ω1,ω2)=d(σ′(ω1),σ′(ω2)). The fact that {a mathematical formula}σ′ is a permutation and that {a mathematical formula}fd is symmetric in each argument completes the proof.  □
     </paragraph>
     <paragraph label="Proposition 16">
      There exist belief revision (resp. belief update) operators which satisfy all AGM postulates (resp. all KM postulates), are not distance-based operators but satisfy{a mathematical formula}(SIN-R) (resp.{a mathematical formula}(SIN-U)).
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}PS={a,b} and consider a belief revision operator ∘ and a belief update operator ⋄, both associated with a faithful assignment such that:{a mathematical formula}{a mathematical formula} and such that for every base K such that {a mathematical formula}K≢a∧¬b and {a mathematical formula}K≢¬a∧b, {a mathematical formula}⩽K is a two-level total preorder satisfying conditions (1–3) of the faithful assignment, that is, for every interpretation {a mathematical formula}ω,ω′, {a mathematical formula}ω&lt;Kω′ if and only if {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊭K. We have to show that for every base K and every interpretation {a mathematical formula}ω,ω′, {a mathematical formula}ω⩽Kω′ implies {a mathematical formula}σ(ω)⩽σ(K)σ(ω′) for every symbol translation σ which satisfy SIN. Yet since {a mathematical formula}|PS|=2, there is only one bijection from X to Y (with {a mathematical formula}X,Y⊆PS) which is not the identity function, i.e., {a mathematical formula}σ:a↦b; {a mathematical formula}b↦a. Then, let {a mathematical formula}ω,ω′ be two interpretations and K be a base such that {a mathematical formula}ω⩽Kω′. If {a mathematical formula}K≡a∧¬b or {a mathematical formula}K≡¬a∧b, then one can see from the definition of {a mathematical formula}⩽10 and {a mathematical formula}⩽01 that {a mathematical formula}σ(ω)⩽σ(K)σ(ω′) by enumerating all cases. Otherwise, {a mathematical formula}K≢a∧¬b and {a mathematical formula}K≢¬a∧b. Then there are two cases:
      <list>
       {a mathematical formula}ω&lt;Kω′: in this case {a mathematical formula}ω⊨K and {a mathematical formula}ω′⊭K. From point 1 of Corollary 1 we get that {a mathematical formula}σ(ω)⊨σ(K) and {a mathematical formula}σ(ω′)⊭σ(K). Therefore, {a mathematical formula}σ(ω)&lt;σ(K)σ(ω′).{a mathematical formula}ω≃Kω′: then two cases must be considered:It remains to show that ∘ and ⋄ are not distance-based ones. Assume towards a contradiction that ∘, ⋄ are based on a pseudo-distance
      </list>
      <paragraph>
       d. We know that {a mathematical formula}⩽00 and {a mathematical formula}⩽11 are two-level total preorders satisfying conditions (1–3) of the faithful assignment, so we have {a mathematical formula}d(01,00)=d(10,00) and {a mathematical formula}d(01,11)=d(10,11). Yet from the definition of {a mathematical formula}⩽10 and {a mathematical formula}⩽01 we get that {a mathematical formula}d(10,11)&lt;d(10,00) and {a mathematical formula}d(01,11)&gt;d(01,00). Contradiction.  □
      </paragraph>
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>