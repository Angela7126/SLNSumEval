<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Belief revision and projection in the epistemic situation calculus.
   </title>
   <abstract>
    This article considers defeasible beliefs in dynamic settings. In particular, we examine the belief projection problem: what is believed after performing an action and/or receiving new information? The approach is based on an epistemic variant of Reiter's situation calculus, where actions not only have physical effects but may also provide new information to the agent. The preferential belief structure is initially determined using conditional statements. New information is then incorporated using two popular belief revision schemes, namely natural and lexicographic revision. The projection problem is solved twofold in this formalism: by goal regression and by knowledge base progression.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Knowledge and actions have long been identified as two key aspects of an intelligent system: McCarthy's pioneering 1959 paper [1] envisions a computer program that chooses its actions based on knowledge about its current situation. Ensuing from McCarthy's original situation calculus[2], numerous logical languages for modeling such dynamic systems have been developed. One of the most successful approaches is Reiter's variant of the situation calculus [3], [4], whose popularity is due to its simple yet powerful solutions for the frame problem and the projection problem. Projection refers to determining whether a certain formula is true after a sequence of actions; it is the fundamental operation in reasoning about actions and plays an essential role in planning. The versatility of Reiter's framework has been proven by a wide range of extensions that accommodate concepts such as time, concurrency, complex actions, decision theory, and, of particular relevance to this paper, knowledge and sensing. An explicit notion of knowledge allows for modeling both knowledge and lack thereof within the object language. For instance, we could express that a gift box is known to contain an unknown gift.
     </paragraph>
     <paragraph>
      Unequivocal knowledge however is rare in everyday situations. More often than not, intelligent agents merely have beliefs which may or may not hold true in actuality. In fact, agents often consider both cases possible, but regard one of the options to be more plausible than the other. For example, an agent might believe that the gift box presumably is empty, but that if it is not empty, then most likely it contains a gift (whatever that gift may be). The second belief here is called conditional because it is constrained by a hypothesis (namely the box not being empty). Such conditionals are an intuitive way of expressing beliefs about different contingencies and, implicitly, their plausibility.
     </paragraph>
     <paragraph>
      In a dynamic setting, beliefs are subject to change. Change comes in two types: physical change reflects what actually happens in the environment; epistemic change occurs when the agent receives new information about its environment. In our scenario, dropping the box could have the physical effect of breaking the objects inside the box. But it might be only after the following clinking noise that agent realizes the box was not empty and something actually broke inside it. Possible inconsistencies among beliefs and such new information can be resolved by belief revision, which aims to give up just enough old beliefs in order to accommodate the new information [5].
     </paragraph>
     <paragraph>
      For an intelligent agent—a robot, for example—it is important to behave reasonably in such dynamic and uncertain conditions. The key problem that arises when reasoning about actions and beliefs is the belief projection problem: what does the agent believe after a sequence of actions brings about physical and/or epistemic change? More formally, the question can be cast as one of logical entailment: given a knowledge base comprising initial beliefs and knowledge about actions, a query formula about the agent's beliefs and a sequence of actions, does the knowledge base entail the query after the action sequence is performed? The goal is to reduce this problem to an equivalent static entailment, that is, to another entailment problem where no actions are involved, which can therefore be tackled without having to take the dynamics into consideration.
     </paragraph>
     <paragraph>
      The projection problem can be approached from two opposite directions:
     </paragraph>
     <list>
      <list-item label="•">
       Regression rewrites the query to roll back the action sequence and checks this new, action-less query against the original knowledge base.
      </list-item>
      <list-item label="•">
       Progression, on the other hand, applies the effects of the actions to the knowledge base in order to roll the knowledge base forward, so that the original query can be tested against that updated knowledge base.
      </list-item>
     </list>
     <paragraph>
      Regression and progression both have their own strengths and weaknesses. While the procedure to regress a query is often simple and elegant, in a long-lived system with a history of thousands or even millions of actions, regression is not feasible as it would need to revert this huge sequence of actions for every single query. By contrast, a knowledge base only needs to be progressed once for every action; however, this may be very expensive computationally and is not even first-order definable in general [6], [7]. Given this duality, a reasoning system might use regression for short-term planning, and periodically progress the knowledge base during its “mental idle time” to keep up with the actual change of its environment [8].
     </paragraph>
     <paragraph>
      In this paper we study the belief projection problem and present results for both regression and progression.{sup:1} While the question of modeling belief change in the situation calculus has also been addressed by others in various ways [12], [13], [14], [15], these approaches focus more on representational aspects and do not provide the sort of expressivity that we found is necessary for belief projection. For this reason, instead of adopting one of the referenced frameworks, we propose a novel formalism that can be characterized in the following way:
     </paragraph>
     <list>
      <list-item label="•">
       Beliefs about different contingencies are expressed through if-then statements such as “if the box is not empty, then it presumably contains a gift”; so-called conditional beliefs. Furthermore, by way of a concept called only-believing it is possible to capture that a conditional knowledge base is all the agent believes. Only-believing hence implicitly specifies the agent's non-beliefs, which are essential to infer, for instance, that the box is believed to contain an unknown gift.
      </list-item>
      <list-item label="•">
       Physical and epistemic change is caused by actions. Physical change means that an action may directly affect and change the value of predicates, like dropping a box has the effect of breaking the fragile items inside the box. Epistemic change, on the other hand, means that an action may convey new information that leads to a reassessment of how plausible the agent considers its different beliefs to be, like the clinking noise tells the agent that something seems to be broken in the box; this information is taken into account by belief revision.
      </list-item>
     </list>
     <paragraph>
      As we shall see, belief projection in such a framework comprising physical and revision effects fundamentally relies on conditional belief: our regression operator will exploit relationships between the conditional beliefs before and after an action, and the progression results relate the original and the updated conditional knowledge base by means of only-believing. This comes as no surprise considering the relationship between belief revision and conditional belief manifested in Ramsey's test [16], [17], according to which a conditional is accepted iff the consequent is true after revising by its antecedent.
     </paragraph>
     <paragraph>
      Revision operators can be differently radical in terms of how firmly they hold on to the new information after subsequent revisions. We consider two particular operators in this paper: natural [18], [19] as well as lexicographic revision [20], [21], which we refer to as weak and strong revision here because lexicographic revision leads to firmer belief in the new information than natural revision. While these are only two among many revision schemes proposed in the literature and especially natural revision has drawn criticism, they are also perhaps the most well-known operators and stand out due to their straightforward definitions.
     </paragraph>
     <paragraph>
      The language we propose builds on first-order logic, which makes reasoning in our framework undecidable in general. Nevertheless the paper's contribution goes beyond the conceptual level, as fragments of the language are decidable. In particular, the ideas presented here are compatible with the idea of limited belief, where decidability is achieved through semantic restrictions [22], [23].
     </paragraph>
     <paragraph>
      On the technical side, we abandon Reiter's axiomatic formulation of the situation calculus in favor of Lakemeyer and Levesque's semantical characterization [24], which amalgamates Levesque's logic of only-knowing [25], [26] with actions in the spirit of Reiter's situation calculus. We see three benefits of the semantical over the traditional axiomatic approach. Firstly, proofs in the possible-worlds semantics are often much more straightforward than in the comparable epistemic formalisms that use Tarskian semantics and reify possible worlds. Secondly, the language and the semantics naturally support arbitrary nesting of actions, quantification, and beliefs. Finally, the semantical approach allows for a much clearer definition of only-believing, which in classical first-order logic, if expressible at all, requires a complex meta-logical belief closure operation [4].
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. In the next section we review related work in the fields of reasoning about actions, belief revision, and their intersection. Section 3 introduces our formalism and presents some relevant properties. In the next section we introduce the Reiter-style action theories and the belief projection problem in our variant of the situation calculus. The following two sections are devoted to solving the belief projection problem, first by goal regression and then by theory progression. Finally we compare our work with the standard belief revision frameworks in Section 7. Then we conclude.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      We begin our survey of related work with the situation calculus and its epistemic extensions, proceed with particular focus on other variants that accommodate belief change, and finally review literature on classical belief revision.
     </paragraph>
     <section label="2.1">
      <section-title>
       Reasoning about actions and knowledge
      </section-title>
      <paragraph>
       The situation calculus was originally proposed by McCarthy [2] to allow programs like the fictitious Advice Taker program [1] to reason about which action to take next. The most thoroughly investigated variant of the situation calculus however is due to Reiter [4]; his approach views situations as sequences of actions which represent the “world history.” Other significant action formalisms include the fluent calculus [27] and more distant relatives like the event calculus [28] and the family of action languages {a mathematical formula}A[29].
      </paragraph>
      <paragraph>
       Reiter's situation calculus is formulated in classical predicate logic with Tarskian semantics. His axiomatic approach requires standardization of models through unique-name axioms and other foundational axioms, including a second-order one, and makes extensive use of reification to represent situations. This can become quite cumbersome in particular when combined with epistemic reasoning as introduced by Scherl and Levesque [30], where not just one but potentially many possible worlds need to be considered.
      </paragraph>
      <paragraph>
       Lakemeyer and Levesque address this issue in their epistemic situation calculus {a mathematical formula}ES[24], a first-order modal logic with possible-worlds semantics that amalgamates Levesque's logic of only-knowing [25], [26] with actions in the spirit of Reiter's situation calculus and Scherl and Levesque's epistemic extension [30]. Actions occur in this language as modal operators, whereas possible worlds and situations are purely semantic concepts. While {a mathematical formula}ES has been shown to faithfully reconstruct Reiter's situation calculus [24], the semantical formulation arguably yields a cleaner language and usually leads to more straightforward proofs.
      </paragraph>
      <paragraph>
       Besides the classical notion of knowledge, {a mathematical formula}ES also provides a way of expressing that a knowledge base is all the agent knows, implicitly meaning that anything that does not follow from the knowledge base is not known. In Reiter's axiomatization of the situation calculus, such a closed-world assumption on knowledge can be achieved, too, albeit through a meta-logical operation that augments the knowledge base with (infinitely many) sentences about what the agent does not know [4]. In this paper we generalize this notion of only-knowing to handle conditional knowledge bases. As we shall see in Section 3.4, the natural extension of Reiter's meta-logical operation to the case of conditional knowledge bases is not well-behaved.
      </paragraph>
      <paragraph>
       Reiter proposed his situation calculus along with basic action theories in order to solve the frame problem and the projection problem [3], [4]. His regression mechanism was later generalized for knowledge [30], [24]; in Section 5 we take it another step further to conditional beliefs. Lin and Reiter introduced progression of basic action theories as an alternative solution of the projection problem [6]. Lakemeyer and Levesque extended Lin and Reiter's progression to {a mathematical formula}ES by using a dynamic variant of only-knowing [31]. Our progression of conditional knowledge bases from Section 6 generalizes their results further to conditional beliefs. While progression has been shown to be first-order definable for certain classes of basic action theories [6], [32], it remains an open question if and how these results generalize to knowledge bases with conditional beliefs.
      </paragraph>
      <paragraph>
       Scherl and Levesque [30] and most subsequent work on epistemic reasoning in the situation calculus, including {a mathematical formula}ES, only consider unrevisable knowledge. Sensing in these formalisms means that all worlds that disagree with the actual world on the value of a specific formula are deemed impossible. In its binary form, sensing answers yes–no questions such as “is the gift broken?”; these answers are definitive and cannot be revised. A sensing result that contradicts the agent's knowledge therefore irrevocably leads to a state of logical inconsistency, where no meaningful inferences can be made. This sort of sensing corresponds to belief expansion in the belief revision literature.
      </paragraph>
      <paragraph>
       Our approach avoids this limitation by accommodating new information through a different mechanism where the information carried by an action need not be grounded by the actual world and may hence be incorrect. Such new information is incorporated using classical belief revision schemes, which give up a minimal set of previous beliefs when necessary. These differences notwithstanding, our mechanism of informing can simulate Scherl and Levesque's sensing for the most part as we shall briefly argue in Section 4.1.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Belief change in the situation calculus
      </section-title>
      <paragraph>
       A number of extensions of the situation calculus that address belief change have been proposed [12], [13], [14], [15], [33]. These papers however focus more on representational aspects than on belief projection. The main difference between the present and the referenced papers is consequently our investigation of the belief projection problem. There are also major differences among the formalisms; particularly the prominent role of conditional belief in our approach stands out compared to the others.
      </paragraph>
      <paragraph>
       The formalism by Shapiro et al. [12] is arguably the closest to ours. Shapiro et al. follow Scherl and Levesque [30] in their use of sensing, which eliminates possible worlds that disagree with sensed information, which they combine with a plausibility ranking of possible worlds. As usual, belief is defined as what is true in the most-plausible worlds. Belief revision hence occurs when a sensing result eliminates all most-plausible worlds, so that other worlds become the most-plausible ones. Unfortunately, this scheme implies that sensed information itself cannot be revised: after sensing information that contradicts an earlier sensing, all possible worlds are eliminated, and the agent is caught in a state of inconsistency. This is due to the use of classical sensing, which irrevocably eliminates worlds, as opposed to updating the plausibility ranking as done by classical revision operators.
      </paragraph>
      <paragraph>
       Shapiro et al. also briefly discuss a conditional belief operator for the purpose of specifying the initial beliefs. Capturing a knowledge base with that operator is however quite cumbersome as typically also a (potentially huge) number of negative conditionals is required to also capture the intended non-beliefs. As it stands, these conditionals need to be determined by hand; a closure operation analogous to Reiter's knowledge closure [4] seems inappropriate as it may be inconsistent as we shall illustrate in Section 3.4. In our approach the need for such a meta-logical belief closure is obviated by only-believing.
      </paragraph>
      <paragraph>
       Shapiro et al. opt for classical sensing instead of belief revision because any plausibility updating scheme would conflict with belief introspection in their approach. The anomalies they mention do not occur in our logic because here a world's plausibility is a property of that world alone (and of the epistemic state), independent of the currently considered actual world. Theorem 17 shows that introspection as well as quantifying-in are well-behaved in our framework.
      </paragraph>
      <paragraph>
       The next-closest relative is by Delgrande and Levesque [14]. In this formalism, actions can inform the agent that some information is true like in our approach; new information is then incorporated by a revision scheme based on Spohn's ranking functions [34]. Among the mentioned approaches, this is the only one that follows a traditional revision scheme like ours. However, it differs in that actions may be fallible, which means that an agent may do a different action than it actually intended to do. This is modeled using a binary fluent relation between actions that may be mistaken for another. Delgrande and Levesque focus on these representational aspects and do not consider projection. To what extent the techniques developed in this paper could be transferred to their formalism is an open question.
      </paragraph>
      <paragraph>
       Fang and Liu [15] use plausibility rankings on worlds and actions; the plausibility ranking then changes according to the executed actions. Both rankings are explicitly specified in the beginning. Fang et al. also consider progression [33], however only in the propositional case.
      </paragraph>
      <paragraph>
       Demolombe and Pozos-Parra's proposal [13] avoids any plausibility ranking by compiling physical and epistemic effects on predetermined beliefs of interest to special successor-state axioms. Our approach however shows that ranking the worlds by plausibility can be considered a purely semantic concept; plausibilities are not needed in the object language.
      </paragraph>
      <paragraph>
       Another framework to deal with faulty sensors in the situation calculus is the Bayesian approach by Bacchus et al. [35]. They also use extra action parameters to indicate the real-world outcome, similar to our mimicking of classical sensing described in Section 4.1.
      </paragraph>
      <paragraph>
       Belief revision has also been addressed in dynamic epistemic logic [36] by several authors [37], [38], [39], [40]. Closest to our work is van Benthem's [40], which gives semantics to conditional belief through a plausibility ranking of possible worlds and considers natural and lexicographic revision, like we do. Most importantly, van Benthem reduces beliefs after revision to beliefs before that revision in a regression-like fashion; these reduction theorems resemble our Theorem 27, Theorem 28.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Belief revision and conditional belief
      </section-title>
      <paragraph>
       The seminal work on belief revision is the system of eight postulates proposed by Alchourrón, Gärdenfors, and Makinson [41], [42] and named AGM after their initials. These postulates aim to govern how a belief revision operator should incorporate new information into an existing set of beliefs in a reasonable way.
      </paragraph>
      <paragraph>
       Building on AGM's work on one-time revision, Darwiche and Pearl later proposed postulates to address iterated revision as well [43]. What is being revised in their framework is no longer merely a set of beliefs, but an epistemic state where some beliefs are more plausible than others; revision updates the associated plausibility ranking and produces a new epistemic state. The question of iterated revision however remains disputed and has produced numerous alternative postulate systems, including [21], [44], [45], [46].
      </paragraph>
      <paragraph>
       It is no surprise given this controversy about the postulates that there is no commonly agreed-on revision operator. Among the proposed revision operators are natural revision [18], [19], lexicographic revision [20], [21], restrained revision [45], irrevocable revision [47], and Darwiche and Pearl's operator [43]. While these operators all give highest priority to the new information, they vary in how firmly they hold on to these beliefs after new information comes in. For instance, natural revision very readily gives up information from an earlier revision after a subsequent revision, whereas lexicographic revision is much more reluctant to do so. For that reason, we refer to natural as weak revision and to lexicographic as strong revision. Similarly, Rott refers to them as conservative and moderate revision, respectively, as natural revision minimally modifies the plausibility ranking.
      </paragraph>
      <paragraph>
       Natural revision in particular has drawn criticism for giving up information from previous revisions too readily [43], [45], [48], [49]. Booth and Meyer's restrained revision attempts to behave more intuitively here. They propose a more restricted class of iterated revision operators called admissible operators. In this class, restrained revision replaces natural revision as the most conservative operator.
      </paragraph>
      <paragraph>
       Despite these valid criticisms we opt for natural and lexicographic revision in this paper mainly for pragmatic reasons. On the one hand, they are perhaps the best-known revision operators and, on the other, they feature very simple definitions which make them quite easy to work with.
      </paragraph>
      <paragraph>
       Which of the many known revision operators is most suitable is a hard question; it appears to depend at least on the context and the sort of information that was obtained [45]. A meta-theory about when to choose which revision operator as called for by Rott [50] is however beyond the scope of this paper. Instead, it is up to the modeler in our framework, which revision operator (among natural and lexicographic) to choose for which kind of information.
      </paragraph>
      <paragraph>
       Another popular framework for iterated revision is due to Spohn [34]. His ordinal conditional functions map worlds to plausibilities, which are not only taken to order the worlds but also interpreted quantitatively. Revision then not only takes a new formula, but also a parameter that indicates how firmly this new information is believed.
      </paragraph>
      <paragraph>
       AGM-style belief revision is not intended and in fact inappropriate for dealing with physical change. While we follow Reiter's situation calculus here to account for physical change, Katsuno and Mendelzon have proposed a postulate system that addresses physical change in the spirit of AGM's framework [51]. The belief update approach differs fundamentally from the situation calculus. For instance, it is possible to update beliefs by any disjunctive formula in Katsuno and Mendelzon's framework, whereas Reiter's basic action theories only allow for deterministic change. On the other hand, belief update is a meta-logical operation and as such has no concept of actions at the object-language level. Boutilier has folded belief revision and update into a single framework [52]: when an event happens, the beliefs are revised by the event's precondition and then updated by its effect. This view is also applicable to actions in our framework.
      </paragraph>
      <paragraph>
       Conditional belief and belief revision are closely related through what is known as the Ramsey test [17]: the conditional “if α, then plausibly β” shall be believed iff β is believed after revision by α. This relationship also underlies our Theorem 27, Theorem 28 that relate beliefs before and after an action. The most influential work on conditional logic is Lewis' book on counterfactuals [53]. The system-of-spheres model we use for epistemic states to capture conditional belief is chiefly due to him and to Grove [54]. While Lewis argues against a finiteness assumption for the number of spheres on philosophical grounds, we make this assumption here as it simplifies the technical treatment and since finitely many spheres suffice for our purposes.
      </paragraph>
      <paragraph>
       Our semantics of (nested) conditionals is somewhat unconventional; an antecedent has no repercussions on any nested beliefs in the consequent (Property 15 in Theorem 17). Semantically, the reason is that the system of spheres is independent of the actual world, a condition Lewis calls uniformity [53]. This is different to both Boutilier's original account of natural revision [18] as well as Levi's philosophical considerations on nested beliefs [55]. Our semantics has some advantages. Firstly, making nested beliefs in the consequent independent of the outer antecedent greatly simplifies Theorem 27, Theorem 28, which are fundamental for belief regression. Without that independence, action operators would have to be pushed inside of all possibly nested beliefs in order to avoid redundant revisions. Although possible, this is quite cumbersome. Secondly, the simple semantics makes it possible to reduce conditional beliefs to a series of non-modal reasoning tasks as shown in [10], [56], which we do not discuss in this paper. Considering these issues and that there is no commonly-agreed-on semantics for nested beliefs [53], [55], we believe our simpler (as it does not modify the epistemic state) semantics of conditional beliefs is preferable for the purposes of this paper.
      </paragraph>
      <paragraph>
       Only-believing has relations to both Levesque's only-knowing [26] and Pearl's meta-logical System Z [57], as we shall discuss in Section 3.4. Like only-knowing, only-believing works by including as many worlds as possible into the epistemic state. Additionally, it imposes a plausibility ranking on these worlds, which can be shown to be equivalent to Pearl's Z-ranking [56], [57]. A concept similar to only-believing was used by Boutilier [58] to semantically capture System Z, too. Only-knowing can be considered a combination of (ordinary) knowing at least and knowing at most[26]. Boutilier introduces a conditional belief variant of the latter, by which he forces worlds to be as normal as possible and ultimately replicates System Z.
      </paragraph>
     </section>
    </section>
    <section label="3">
     The logic {a mathematical formula}ESB
     <paragraph>
      In this section we introduce a first-order{sup:2} logic with modal operators for both actions and beliefs. The language features predicates, equality, functions, and countably many standard names, which serve as rigid designators of all elements in the domain. Predicates are either fluent, meaning their value varies as the result of actions, or rigid. Functions are assumed to be rigid for simplicity. The terms of the language come in two sorts, action and object. Actions are further divided into the subsorts weak-revision and strong-revision actions: an action may, besides its (physical) effect on fluents, also carry new information, and the action's subsort determines how this new information is incorporated into the current beliefs. The language supports conditional belief, including a variant called only-belief which implicitly also specifies what is not believed.
     </paragraph>
     <paragraph>
      We define the language in Section 3.1 and give the semantics in Section 3.2. In Sections 3.3 and 3.4 we further investigate conditional beliefs and only-believing, respectively. In particular, we prove a unique-model property, which is foundational for many subsequent results of this paper.
     </paragraph>
     <section label="3.1">
      <section-title>
       The syntax
      </section-title>
      <paragraph label="Definition 1">
       The symbols of our language are taken from the following vocabulary:
      </paragraph>
      <list>
       <list-item label="•">
        infinitely many object standard names {a mathematical formula}1#,2#,…;
       </list-item>
       <list-item label="•">
        infinitely many first-order variables, written schematically as x:
       </list-item>
       <list-item label="•">
        infinitely many function symbols:
       </list-item>
       <list-item label="•">
        infinitely many predicate symbols:
       </list-item>
       <list-item label="•">
        connectives and other symbols: =, ∨, ¬, ∃, □, B, O, ⇒, round/square/curly brackets, comma.
       </list-item>
      </list>
      <paragraph label="Definition 2">
       The terms of the language are of sorts either object or action, where actions are divided in the subsorts weak- and strong-revision actions. The terms are formed from first-order variables, standard names, and function symbols. Standard names serve as unique identifiers of all individuals; they are defined as follows:
      </paragraph>
      <list>
       <list-item label="•">
        the object standard names are {a mathematical formula}1#,2#,3#,…;
       </list-item>
       <list-item label="•">
        the action standard names are of the form {a mathematical formula}A(n1,…,nk) where A is an action function symbol and the {a mathematical formula}ni are standard names.
       </list-item>
      </list>
      <paragraph>
       For example, if unbox is a unary action symbol, {a mathematical formula}unbox(5#) is an action standard name. If gift is an object constant, {a mathematical formula}unbox(gift) is an action term, but not a standard name. Throughout the paper, we use n for standard names and t for terms.
      </paragraph>
      <paragraph label="Definition 3">
       The set of well-formed formulas of the language is the least set such that:
       <list>
        {a mathematical formula}R(t1,…,tk) and {a mathematical formula}F(t1,…,tk) is a formula where R and F are fluent and rigid predicate symbols and {a mathematical formula}ti are terms;{a mathematical formula}(t1=t2) is a formula where {a mathematical formula}t1 and {a mathematical formula}t2 are terms;¬α, {a mathematical formula}(α∨β), and {a mathematical formula}∃xα are formulas where α and β are formulas and x is a variable;{a mathematical formula}[t]α and □α are formulas where α is a formula and t is an action term;{a mathematical formula}B(α⇒β) is a formula where α and β are formulas;{a mathematical formula}O{ϕ1⇒ψ1,…,ϕm⇒ψm} is a formula where {a mathematical formula}ϕi and {a mathematical formula}ψi are formulas without B or O.By
       </list>
       <paragraph>
        {a mathematical formula}αtx we denote the formula α with t substituted for all free occurrences of the variable x. A sentence is a formula with no free variable. We use the usual abbreviations {a mathematical formula}(α∧β), {a mathematical formula}(α⊃β), {a mathematical formula}(α≡β), {a mathematical formula}∀xα, {an inline-figure}, {an inline-figure}, and {a mathematical formula}(t1≠t2). Additionally,
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}Bα stands for {an inline-figure};
        </list-item>
        <list-item label="•">
         {a mathematical formula}Kα stands for {an inline-figure}.
        </list-item>
       </list>
       <paragraph>
        {a mathematical formula}Bα and {a mathematical formula}Kα are read as “α is believed” and “α is known,” respectively.
       </paragraph>
      </paragraph>
      <paragraph>
       The language features one special fluent predicate, {a mathematical formula}IF(t). The general idea is that when action t is executed, this informs the agent that most plausibly {a mathematical formula}IF(t) holds. In a sense, {a mathematical formula}IF(t) represents the most-plausible precondition of t, so when t is executed, this tells the agent that it is plausible that {a mathematical formula}IF(t) was true. For example, a knowledge base might stipulate that {a mathematical formula}IF(clink) is true when something breaks to pieces, and that {a mathematical formula}IF(unbox(5#)) is true only if {a mathematical formula}5# actually is in the box (we formalize this example in Section 4). It is noteworthy that this information does not necessarily depend on what is true in the real world; in particular, the information may actually be mistaken. Unlike the classical approach to sensing [30], [24], we can therefore model that incoming information contradict each other. Such inconsistencies are then resolved by means of belief revision. We elaborate on the intuition behind this model in Section 4.1.
      </paragraph>
      <paragraph>
       To ease the readability of formulas we often omit brackets. Then the convention is that □ shall be the weakest binding operator of all; the other unary operators bind stronger than the logical connectives; and the connective ∧ binds stronger than ∨. Free variables are implicitly universally quantified with maximal scope unless noted otherwise. For example, {a mathematical formula}□[a]Broken(y)≡Broken(y)∨InBox(y)∧Fragile(y)∧a=dropbox abbreviates the formula {a mathematical formula}∀a∀y□(([a]Broken(y))≡(Broken(y)∨((InBox(y)∧Fragile(y))∧(a=dropbox)))). Intuitively this formula means that after any sequence of actions (□), an object y is broken after another action a iff it either was broken already or it is fragile and in the box which is dropped.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       The semantics
      </section-title>
      <paragraph>
       We now give a semantics for this language using possible worlds. We will begin with the objective fragment of the logic, that is, the part of the language that is not concerned with beliefs. The key ingredient of our semantics is worlds. A world assigns a standard name to each primitive term and a truth value to each primitive atom, which in case of fluent atoms also depends on the sequence of actions executed thus far. A world is therefore not just a snapshot but also determines the future. In the following we formalize these notions.
      </paragraph>
      <paragraph label="Definition 4">
       An action sequence is the empty sequence 〈〉 or the concatenation {a mathematical formula}z⋅n of an action sequence z and an action standard name n. A world w is a function:
      </paragraph>
      <list>
       <list-item label="•">
        from the primitive object terms {a mathematical formula}g(n1,…,nk) to object standard names;
       </list-item>
       <list-item label="•">
        from the primitive rigid atoms {a mathematical formula}R(n1,…,nk) to truth values {a mathematical formula}{0,1};
       </list-item>
       <list-item label="•">
        from the primitive fluent atoms {a mathematical formula}F(n1,…,nk) and action sequences to truth values {a mathematical formula}{0,1}.
       </list-item>
      </list>
      <paragraph>
       For example, to say that {a mathematical formula}5# is the gift, is fragile, and breaks after dropbox, a world w might stipulate {a mathematical formula}w[gift]=5#, {a mathematical formula}w[Fragile(5#)]=1, {a mathematical formula}w[Broken(5#),〈〉]=0, and {a mathematical formula}w[Broken(5#),〈dropbox〉]=1; such a world is depicted in Fig. 1a. In that world's progression by dropbox, the object is broken: {a mathematical formula}(w≫dropbox)[Broken(5#),〈〉]=1, as depicted in Fig. 1b. Note that dropbox is not interpreted by the world, as it is an action standard name.
      </paragraph>
      <paragraph label="Definition 5">
       The denotation{a mathematical formula}w(t) of a term t in a world w is defined as follows:
      </paragraph>
      <list>
       <list-item label="•">
        if n is a standard name, {a mathematical formula}w(n)=n;
       </list-item>
       <list-item label="•">
        if g is an object function symbol, {a mathematical formula}w(g(t1,…,tk))=w[g(n1,…,nk)] where {a mathematical formula}ni=w(ti);
       </list-item>
       <list-item label="•">
        if A is an action function symbol, {a mathematical formula}w(A(t1,…,tk))=A(n1,…,nk) where {a mathematical formula}ni=w(ti).
       </list-item>
      </list>
      <paragraph>
       For example, if {a mathematical formula}w[gift]=5#, then the denotation of {a mathematical formula}unbox(gift) is {a mathematical formula}w(unbox(gift))=unbox(5#).
      </paragraph>
      <paragraph label="Definition 6">
       Truth of an objective sentence is defined with respect to a world w:
      </paragraph>
      <list>
       <list-item label="S'1.">
        {a mathematical formula}w⊨R(t1,…,tk)  iff  {a mathematical formula}w[R(n1,…,nk)]=1 where {a mathematical formula}ni=w(ti) for every rigid predicate symbol R;
       </list-item>
       <list-item label="S'2.">
        {a mathematical formula}w⊨F(t1,…,tk)  iff  {a mathematical formula}w[F(n1,…,nk),〈〉]=1 where {a mathematical formula}ni=w(ti) for every fluent predicate symbol F;
       </list-item>
       <list-item label="S'3.">
        {a mathematical formula}w⊨(t1=t2)  iff  {a mathematical formula}n1 and {a mathematical formula}n2 are identical standard names where {a mathematical formula}ni=w(ti);
       </list-item>
       <list-item label="S'4.">
        {a mathematical formula}w⊨¬ϕ  iff  {a mathematical formula}w⊭ϕ;
       </list-item>
       <list-item label="S'5.">
        {a mathematical formula}w⊨(ϕ∨ψ)  iff  {a mathematical formula}w⊨ϕ or {a mathematical formula}w⊨ψ;
       </list-item>
       <list-item label="S'6.">
        {a mathematical formula}w⊨∃xϕ  iff  {a mathematical formula}w⊨ϕnx for some standard name n of the same sort as x;
       </list-item>
       <list-item label="S'7.">
        {a mathematical formula}w⊨[t]ϕ  iff  {a mathematical formula}w≫n⊨ϕ where {a mathematical formula}n=w(t);
       </list-item>
       <list-item label="S'8.">
        {a mathematical formula}w⊨□ϕ  iff  {a mathematical formula}w≫z⊨ϕ for every action sequence z.
       </list-item>
      </list>
      <paragraph>
       The above rules capture the objective fragment of our logic, that is, the sentences without B or O. It is largely identical to the objective semantics of {a mathematical formula}ES[24], yet it departs from its ancestor in two respects to simplify the formalism: firstly, action functions are not interpreted but form the action standard names instead; secondly, the actions executed thus far are accounted for by progressing the world instead of making the history of actions an explicit part of the model. Unlike classical first-order logic, Rule S'6 handles quantification substitutionally, made possible by the use of standard names as both terms of the language and the universe of discourse. While there are philosophical arguments against substitutional quantification [59], it greatly simplifies the formal machinery. The computational aspects remain however unaltered by substitutional quantification: a static and objective sentence without standard names is satisfiable in {a mathematical formula}ESB iff it is satisfiable in classical first-order logic [26].
      </paragraph>
      <paragraph>
       Before we proceed with the semantics of beliefs, let us briefly familiarize ourselves with the objective semantics by showing that{a mathematical formula} logically entails{a mathematical formula} The entailment is proved by showing that every world that satisfies the first sentence also satisfies the second. Suppose w satisfies the former sentence. Recall that ∀, ∧, ⊃, and ≡ are the usual abbreviations for expressions involving ∃, ∨, and ¬. Following the rules of the semantics for the quantifiers and for □, we obtain that {a mathematical formula}w≫z⊨[dropbox]Broken(n)≡Broken(n)∨InBox(n)∧Fragile(n)∧dropbox=dropbox for every object standard name n and every action sequence z. In particular, since {a mathematical formula}w=w≫z for {a mathematical formula}z=〈〉, we obtain {a mathematical formula}w⊨[dropbox]Broken(n)≡Broken(n)∨InBox(n)∧Fragile(n) for every object standard name n. It is easy to see that this implies {a mathematical formula}w⊨InBox(n)∧Fragile(n)⊃[dropbox]Broken(n) for every object standard name n. Introducing a universal quantifier for n yields {a mathematical formula}w⊨∀y′(InBox(y′)∧Fragile(y′)⊃[dropbox]Broken(y′)), which is what we wanted to prove.
      </paragraph>
      <paragraph>
       We now extend Definition 6 to also give a semantics to beliefs. Following the system of concentric spheres model popular in belief revision [53], [54], the possible worlds are stratified into spheres. The first, or innermost, sphere represents the actual beliefs; the outer spheres add less-plausible beliefs. Semantically, each sphere is modeled as a set of possible worlds, and a system of spheres is hence represented as a sequence of sets of possible worlds, also referred to as epistemic state. An example is depicted in Fig. 2a. To keep matters simple, we assume only finitely many different spheres. The spheres are numbered consecutively with natural numbers, also called plausibilities. A smaller value indicates higher plausibility. The concentricity means that every sphere, or (plausibility) level, subsumes the less-plausible levels. The plausibility of a world is the plausibility of the first level that contains that world. The plausibility of a sentence corresponds to the most-plausible world that satisfies that sentence; we denote the plausibility of α in an epistemic state e by {a mathematical formula}⌊e|α⌋. In case there is no such world in e, {a mathematical formula}⌊e|α⌋ cannot be a natural number. For that purpose, we use {a mathematical formula}∞∉N to denote an “undefined” plausibility, with the understanding that {a mathematical formula}p&lt;∞ and {a mathematical formula}∞+p=∞ for all {a mathematical formula}p∈N and {a mathematical formula}∞+∞=∞. Thus, {a mathematical formula}⌊e|α⌋=∞ indicates that all worlds in e satisfy ¬α. To avoid confusion, we always make explicit when an expression may take the value ∞.
      </paragraph>
      <paragraph>
       When new information comes in, a system of spheres needs to be revised to take into account that information. In that process, less-plausible worlds may be promoted to become the new most-plausible worlds, and the beliefs may thus change. There are several ways to revise a plausibility ranking [50]. The ones we consider here are natural revision[18], [19] and lexicographic revision[20], [21]. After a single revision, both natural and lexicographic revision lead to the same beliefs, as they both promote to the innermost sphere the most-plausible worlds that satisfy the new information. However, the outer spheres are determined differently, and therefore natural and lexicographic revision differ in how strongly the agent holds on to the new information. Natural revision by ϕ only makes the most-plausible ϕ-worlds the new most-plausible worlds (Fig. 2b). Lexicographic revision, on the other hand, promotes all ϕ-worlds over all ¬ϕ-worlds (Fig. 2c). Consequently, after lexicographic revision logically stronger new evidence is needed to give up belief in ϕ compared to natural revision. In other words, belief in ϕ after natural revision is weaker than after lexicographic revision. In the following we therefore refer to natural revision as weak revision and to lexicographic revision as strong revision. The following definition makes these intuitions precise.
      </paragraph>
      <paragraph label="Definition 7">
       An epistemic state e is an infinite sequence of sets of worlds {a mathematical formula}ep, {a mathematical formula}p∈N={1,2,…}, that
      </paragraph>
      <list>
       <list-item label="•">
        is concentric, that is, {a mathematical formula}ep⊆ep+1 for all {a mathematical formula}p∈N;
       </list-item>
       <list-item label="•">
        converges, that is, {a mathematical formula}eq=ep for some {a mathematical formula}q∈N and all {a mathematical formula}p≥q.
       </list-item>
      </list>
      <paragraph>
       Intuitively, {a mathematical formula}⌊e⌋∈N∪{∞} denotes the first non-empty level of e, and {a mathematical formula}⌈e⌉∈N refers to the last distinct level. Note that {a mathematical formula}⌊e⌋≤⌈e⌉ holds when there is a non-empty level; otherwise, when all levels are empty, we have {a mathematical formula}⌊e⌋=∞ and {a mathematical formula}⌈e⌉=1. Together, {a mathematical formula}⌊e⌋ and {a mathematical formula}e|ϕ express the plausibility {a mathematical formula}⌊e|ϕ⌋ of ϕ in e. Epistemic states are defined to be infinite sequences of sets of worlds in order to simplify the technical treatment (it saves us from normalizing the length of these sequences). The convergence condition however guarantees that every epistemic state is determined by a finite prefix. For convenience, we shall use the notation {a mathematical formula}〈e1,…,eq〉 for some {a mathematical formula}q∈N as a shorthand for the infinite sequence of sets of worlds e with levels {a mathematical formula}e1,…,eq and {a mathematical formula}ep=eq for all {a mathematical formula}p≥q. Note that q need not be minimal: for example, {a mathematical formula}〈e1,e2〉=〈e1,e2,e2,e2〉; and generally, {a mathematical formula}e=〈e1,…,e⌈e⌉〉.
      </paragraph>
      <paragraph>
       With these definitions, we can formalize revision of e.
      </paragraph>
      <paragraph label="Definition 8">
       The weak revision{a mathematical formula}e⁎wϕ of an epistemic state e by an objective sentence ϕ is defined as follows:
      </paragraph>
      <list>
       <list-item label="•">
        if {a mathematical formula}⌊e|ϕ⌋=∞:  {a mathematical formula}e⁎wϕ=〈{}〉;
       </list-item>
       <list-item label="•">
        if {a mathematical formula}⌊e|ϕ⌋≠∞:  {a mathematical formula}e⁎wϕ=〈W,e1∪W,…,e⌈e⌉∪W〉 where {a mathematical formula}W=(e|ϕ)⌊e|ϕ⌋.
       </list-item>
      </list>
      <paragraph>
       When the revision mechanism is clear from context or irrelevant, we just write {a mathematical formula}e⁎ϕ. In particular, we mean by {a mathematical formula}e⁎IF(n) the revision according to the sort of n, that is, {a mathematical formula}e⁎wIF(n) if n is a weak-revision action and {a mathematical formula}e⁎sIF(n) if n is a strong-revision action.
      </paragraph>
      <paragraph>
       An epistemic state is progressed by an action n by first revising it by {a mathematical formula}IF(n) and then progressing the individual worlds by n.
      </paragraph>
      <paragraph label="Definition 9">
       The progression of a set of worlds W and of an epistemic state e are defined as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}W≫n={w≫n|w∈W};
       </list-item>
       <list-item label="•">
        {a mathematical formula}e≫n=〈e1′≫n,…,eq′≫n〉 where 〈e1′,…,eq′〉=e⁎IF(n).
       </list-item>
      </list>
      <paragraph>
       These definitions introduce the toolbox we need for the semantics of beliefs: epistemic states, their revision, and their progression. The following lemma says that the revision and the progression of an epistemic state are well-behaved.
      </paragraph>
      <paragraph label="Lemma 10">
       {a mathematical formula}e⁎wϕ,{a mathematical formula}e⁎sϕ, and{a mathematical formula}e≫nare epistemic states.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}e=〈e1,…,eq〉 be an epistemic state. Clearly, {a mathematical formula}e⁎wϕ is a finite sequence and {a mathematical formula}(e⁎wϕ)p⊆(e⁎wϕ)p+1 for all {a mathematical formula}p∈N, so it is an epistemic state. Likewise, {a mathematical formula}e⁎sϕ is a finite sequence and {a mathematical formula}(e⁎sϕ)p⊆(e⁎sϕ)p+1 for all {a mathematical formula}p∈N, so it is an epistemic state, too.Now consider {a mathematical formula}e≫n, which simply progresses the individual worlds in {a mathematical formula}e⁎IF(n). It is immediate from Definition 4 that the progression {a mathematical formula}w≫n of a world w again is a world. Thus {a mathematical formula}W≫n is a set of worlds if W is one, and if {a mathematical formula}W⊆W′, then {a mathematical formula}W≫n⊆W′≫n. Thus and since {a mathematical formula}e⁎IF(n) is an epistemic state, {a mathematical formula}e≫n is one, too.  □
      </paragraph>
      <paragraph>
       As mentioned above, weak and strong revision of the same epistemic state lead to the same most-plausible beliefs (but typically differ in the less-plausible beliefs). The next lemma records this.
      </paragraph>
      <paragraph label="Lemma 11">
       {a mathematical formula}(e⁎wϕ)1=(e⁎sϕ)1and either{a mathematical formula}⌊e⁎ϕ|ϕ⌋=1or{a mathematical formula}(e⁎wϕ)=(e⁎sϕ).
      </paragraph>
      <paragraph label="Proof">
       First suppose {a mathematical formula}⌊e|ϕ⌋=∞. Then {a mathematical formula}e⁎wϕ=〈{}〉=e⁎sϕ, so the lemma follows. Now suppose {a mathematical formula}⌊e|ϕ⌋=∞. Then {a mathematical formula}(e|ϕ)⌊e|ϕ⌋≠{}. Thus {a mathematical formula}(e⁎wϕ)1=(e⁎sϕ)1 and {a mathematical formula}⌊e⁎ϕ|ϕ⌋=1.  □
      </paragraph>
      <paragraph>
       We can now give a semantics to the full language. Rules S2–S8 below are simply the ones from Definition 6 retrofitted with an additional epistemic state e, which in case of {a mathematical formula}[t] and □ needs to be progressed on the right-hand side. The relevant addition are the ones for beliefs, Rules S9 and S10.
      </paragraph>
      <paragraph label="Definition 12">
       Truth of a sentence is defined with respect to an epistemic state e and a world w:
      </paragraph>
      <list>
       <list-item label="S1.">
        {a mathematical formula}e,w⊨R(t1,…,tk)  iff  {a mathematical formula}w[R(n1,…,nk)]=1 where {a mathematical formula}ni=w(ti) for every rigid predicate symbol R;
       </list-item>
       <list-item label="S2.">
        {a mathematical formula}e,w⊨F(t1,…,tk)  iff  {a mathematical formula}w[F(n1,…,nk),〈〉]=1 where {a mathematical formula}ni=w(ti) for every fluent predicate symbol F;
       </list-item>
       <list-item label="S3.">
        {a mathematical formula}e,w⊨(t1=t2)  iff  {a mathematical formula}n1 and {a mathematical formula}n2 are identical standard names where {a mathematical formula}ni=w(ti);
       </list-item>
       <list-item label="S4.">
        {a mathematical formula}e,w⊨¬α  iff  {a mathematical formula}e,w⊭α;
       </list-item>
       <list-item label="S5.">
        {a mathematical formula}e,w⊨(α∨β)  iff  {a mathematical formula}e,w⊨α or {a mathematical formula}e,w⊨β;
       </list-item>
       <list-item label="S6.">
        {a mathematical formula}e,w⊨∃xα  iff  {a mathematical formula}e,w⊨αnx for some standard name n of the same sort as x;
       </list-item>
       <list-item label="S7.">
        {a mathematical formula}e,w⊨[t]α  iff  {a mathematical formula}e≫n,w≫n⊨α where {a mathematical formula}n=w(t);
       </list-item>
       <list-item label="S8.">
        {a mathematical formula}e,w⊨□α  iff  {a mathematical formula}e≫z,w≫z⊨α for every action sequence z;
       </list-item>
       <list-item label="S9.">
        {a mathematical formula}e,w⊨B(α⇒β)  iff  for all {a mathematical formula}p∈N and every world {a mathematical formula}w′, if {a mathematical formula}p≤⌊e|α⌋ and {a mathematical formula}w′∈ep, then {a mathematical formula}e,w′⊨(α⊃β);
       </list-item>
       <list-item label="S10.">
        {a mathematical formula}e,w⊨O{ϕ1⇒ψ1,…,ϕm⇒ψm}  iff  for all {a mathematical formula}p∈N and every world {a mathematical formula}w′, {a mathematical formula}w′∈ep iff {a mathematical formula}e,w′⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi);
       </list-item>
      </list>
      <paragraph>
       It is immediate that Definition 6, Definition 12 agree on the truth of objective sentences, because the only difference between Rules S'1–S'8 and Rules S1–S8 is the extra parameter for the epistemic state carried around.
      </paragraph>
      <paragraph>
       By Rule S9 the conditional belief {a mathematical formula}B(α⇒β) holds when the most-plausible α-worlds satisfy β. It thus captures our reading “if α is true, then presumably β is also true.” Notice that the belief vacuously holds if there is no α-world. We elaborate on conditional beliefs in Section 3.3.
      </paragraph>
      <paragraph>
       Rule S10 defines the semantics of only-believing {a mathematical formula}O{ϕ1⇒ψ1,…,ϕm⇒ψm}. This means that, for one thing, {a mathematical formula}B(ϕi⇒ψi) shall be believed, that is, {a mathematical formula}(ϕi⊃ψi) must be satisfied by all worlds up to the first sphere that contains a {a mathematical formula}ϕi-world and, for another, the spheres shall be maximal with that property. This maximization intuitively means that any world shall be considered as plausible as possible provided that it is compatible with the conditional beliefs; it thus captures the “only” in only-believing. Only-believing generalizes Levesque's only-knowing [26] to conditional belief, and we will also see a close relation to Pearl's System Z [57] in Section 3.4.
      </paragraph>
      <paragraph>
       In the rest of the paper, we sometimes omit e or w in {a mathematical formula}e,w⊨α when it is irrelevant to the truth of α. For example, when α is objective, we may leave out e. A set of sentences Σ entails a sentence α, written {a mathematical formula}Σ⊨α, iff for all e and w, if {a mathematical formula}e,w⊨β for all {a mathematical formula}β∈Σ, then {a mathematical formula}e,w⊨α. We write ⊨α when {a mathematical formula}Σ={}.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Properties of conditional beliefs
      </section-title>
      <paragraph>
       The conditional belief operator {a mathematical formula}B(α⇒β) is used to form queries about the agent's beliefs. It expresses the agent's belief that if α was true, then β would be true as well. Or in terms of possible worlds, the most-plausible α-worlds must satisfy β as well. This operator turns out to be a quite versatile tool. In particular, it can capture the following intuitions:
      </paragraph>
      <list>
       <list-item label="•">
        {an inline-figure} represents actual belief in α: it holds when all most-plausible worlds satisfy α. It is therefore abbreviated by {a mathematical formula}Bα.
       </list-item>
       <list-item label="•">
        {an inline-figure} captures the usual semantics of indefeasible knowledge of α: all worlds at all plausibility levels satisfy α. It is therefore abbreviated by {a mathematical formula}Kα.
       </list-item>
       <list-item label="•">
        {a mathematical formula}B(α∨β⇒¬β) asserts that α is strictly more plausible than β: the first {a mathematical formula}(α∨β)-worlds must be ¬β-worlds.
       </list-item>
       <list-item label="•">
        {a mathematical formula}¬B(α⇒¬β) says that β would be considered possible if α were true: among the most-plausible α-worlds at least one is a β-world. In particular, {an inline-figure} and {a mathematical formula}¬K¬α express that there is at least one α-world.
       </list-item>
      </list>
      <paragraph>
       In this section we examine a few properties of conditional belief. En route, we shall familiarize ourselves with the formalism. To begin with, we observe the following alternative formulation of its semantics, which sometimes is more convenient to work with than Rule S9.
      </paragraph>
      <paragraph label="Theorem 13">
       {a mathematical formula}e⊨B(α⇒β)iff{a mathematical formula}⌊e|α⌋=∞or{a mathematical formula}e,w⊨(α⊃β)for all{a mathematical formula}w∈e⌊e|α⌋.
      </paragraph>
      <paragraph label="Proof">
       For the only-if direction let {a mathematical formula}e⊨B(α⇒β). Then by Rule S9, for all {a mathematical formula}p∈N, if {a mathematical formula}p≤⌊e|α⌋ and {a mathematical formula}w∈ep, then {a mathematical formula}e,w⊨(α⊃β). If {a mathematical formula}⌊e|α⌋=∞, the right-hand side of the theorem trivially holds. Otherwise {a mathematical formula}e,w⊨(α⊃β) for all {a mathematical formula}w∈e⌊e|α⌋, and the right-hand side holds again.For the if direction first let {a mathematical formula}⌊e|α⌋=∞. Then {a mathematical formula}e,w⊭α for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Hence {a mathematical formula}e,w⊨(α⊃β) for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N, and so {a mathematical formula}e⊨B(α⇒β) by Rule S9. Now let {a mathematical formula}⌊e|α⌋≠∞ and {a mathematical formula}e,w⊨(α⊃β) for all {a mathematical formula}w∈e⌊e|α⌋. By Definition 7, {a mathematical formula}e1⊆…⊆e⌊e|α⌋. Thus for all {a mathematical formula}p∈N, if {a mathematical formula}p≤⌊e|α⌋ and {a mathematical formula}w∈ep, then {a mathematical formula}e,w⊨(α⊃β), which by Rule S9 gives {a mathematical formula}e⊨B(α⇒β).  □
      </paragraph>
      <paragraph>
       Another easy exercise is to confirm that {a mathematical formula}Kα indeed expresses knowledge of α as claimed above.
      </paragraph>
      <paragraph label="Theorem 14">
       {a mathematical formula}e⊨Kαiff{a mathematical formula}e,w⊨αfor all{a mathematical formula}w∈epand{a mathematical formula}p∈N.
      </paragraph>
      <paragraph label="Proof">
       For the only-if direction, let {a mathematical formula}e⊨Kα. By Rule S9, for all {a mathematical formula}p∈N, if {a mathematical formula}p≤⌊e|¬α⌋ and {a mathematical formula}w∈ep, then {an inline-figure}, which simplifies to {a mathematical formula}e,w⊨α (*). We show by induction on p that {a mathematical formula}p≤⌊e|¬α⌋ for all {a mathematical formula}p∈N, which immediately gives us the right-hand side of the theorem. The base case holds trivially. For the induction step, suppose {a mathematical formula}p≤⌊e|¬α⌋. Then {a mathematical formula}e,w⊨α for all {a mathematical formula}w∈ep by (*), and thus {a mathematical formula}⌊e|¬α⌋&gt;p, that is, {a mathematical formula}p+1≤⌊e|¬α⌋.Conversely, let {a mathematical formula}e,w⊨α for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Then {a mathematical formula}⌊e|¬α⌋=∞, and by Rule S9, {a mathematical formula}e⊨Kα.  □
      </paragraph>
      <paragraph>
       Next, we prove that {a mathematical formula}B(α∨β⇒¬β) says that α is more plausible than β.
      </paragraph>
      <paragraph label="Theorem 15">
       {a mathematical formula}e⊨B(α∨β⇒¬β)iff{a mathematical formula}⌊e|α⌋&lt;⌊e|β⌋or{a mathematical formula}⌊e|α⌋=⌊e|β⌋=∞.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}e⊨B(α∨β⇒¬β) iff (by Theorem 13) {a mathematical formula}⌊e|α∨β⌋=∞ or {a mathematical formula}e,w⊨(α∨β⊃¬β) for all {a mathematical formula}w∈e⌊e|α∨β⌋. The former is equivalent to {a mathematical formula}⌊e|α⌋=⌊e|β⌋=∞. The latter holds iff {a mathematical formula}e,w⊭β for all {a mathematical formula}w∈e⌊e|α∨β⌋ iff {a mathematical formula}⌊e|β⌋&gt;⌊e|α∨β⌋=⌊e|α⌋.  □
      </paragraph>
      <paragraph>
       Before we turn to more general properties of the conditional belief operator, we need the following simple lemma.
      </paragraph>
      <paragraph label="Lemma 16">
       {a mathematical formula}⊨□αiff ⊨α.
      </paragraph>
      <paragraph label="Proof">
       For the only-if direction suppose {a mathematical formula}⊨□α. Then by Rule S8, {a mathematical formula}e≫z,w≫z⊨α for all e, w, and z. In particular, this holds for {a mathematical formula}z=〈〉, and since {a mathematical formula}e≫〈〉=e and {a mathematical formula}w≫〈〉=w, we have {a mathematical formula}e,w⊨α for all e, w, so ⊨α. Conversely, suppose ⊨α. Therefore and by Lemma 10, for all e, w, z, we have {a mathematical formula}e≫z,w≫z⊨α, and by Rule S8 {a mathematical formula}e,w⊨□α. Thus {a mathematical formula}⊨□α.  □
      </paragraph>
      <paragraph>
       The following theorem establishes several general properties of the conditional belief operator. Notice that, by the above lemma, all the validities also hold after an arbitrary sequence of actions.
      </paragraph>
      <paragraph label="Theorem 17">
       <list>
        <list-item>
         {a mathematical formula}⊭Kα⊃α;
        </list-item>
        <list-item>
         {a mathematical formula}⊭B(α⇒β)∧B(β⇒γ)⊃B(α⇒γ);
        </list-item>
        <list-item>
         {a mathematical formula}⊭B(α⇒γ)⊃B(α∧β⇒γ);
        </list-item>
        <list-item>
         {a mathematical formula}⊭B(α⇒β)≡B(¬β⇒¬α);
        </list-item>
        <list-item>
         {a mathematical formula}⊨B(α⇒β)⊃B(α⊃β);
        </list-item>
        <list-item>
         {a mathematical formula}⊨Bα∧Bβ⊃B(α⇒β);
        </list-item>
        <list-item>
         {a mathematical formula}⊨Bα∧B(α⊃β)⊃Bβ;
        </list-item>
        <list-item>
         {a mathematical formula}⊨Kα∧K(α⊃β)⊃Kβ;
        </list-item>
        <list-item>
         {a mathematical formula}⊨Bα∧B(α⇒β)⊃Bβ;
        </list-item>
        <list-item>
         {a mathematical formula}⊨Kα⊃Bα;
        </list-item>
        <list-item>
         {a mathematical formula}⊨B(α⇒β)⊃KB(α⇒β);
        </list-item>
        <list-item>
         {a mathematical formula}⊨¬B(α⇒β)⊃K¬B(α⇒β);
        </list-item>
        <list-item>
         {a mathematical formula}⊨∀xB(α⇒β)⊃B(α⇒∀xβ)where x does not occur freely in α;
        </list-item>
        <list-item>
         {a mathematical formula}⊨Kαif ⊨α;
        </list-item>
        <list-item>
         {a mathematical formula}⊨B(α⇒B(β⇒γ))∧¬K¬α⊃B(β⇒γ).
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       Let us explain the properties in English before we prove them. To begin with, our logic does not require the agent's knowledge to be actually true, that is, the epistemic state does not have to contain the actual world (Property 1). As usual, neither transitivity nor monotonicity nor contraposition hold for conditional beliefs (Properties 2, 3, 4). A conditional belief does however imply believing the material implication, which corresponds to Lewis' [53] weak centering, and strong centering holds as well (Properties 5 and 6). Knowledge and belief are closed under modus ponens from material implications and from belief conditionals (Properties 7, 8, 9), and what is believed is a subset of what is known (Property 10). The abbreviations {a mathematical formula}Bα and {a mathematical formula}Kα both are negatively and positively introspective (Properties 10, 11, 12). Hence, they are weak-S5 operators [60]. The Barcan formula is satisfied as well (Property 13) and the agent is moreover omniscient (Property 14). Somewhat surprising is perhaps Property 15: when a conditional is nested in another conditional's consequent, then the outer conditional's antecedent is irrelevant to the inner conditional. Alternatively one could condition the nested belief on the outer conditional's antecedent as well. Our simple semantics has some advantages as we discuss in Section 2.
      </paragraph>
      <paragraph label="Proof">
       <list>
        <list-item label="1.">
         Let R be a rigid atom and {a mathematical formula}e=〈e1〉 with {a mathematical formula}e1={w|w⊨R}, and let {a mathematical formula}w′ a world such that {a mathematical formula}w′⊭R. We show that {a mathematical formula}e,w′⊭KR⊃R, that is, {a mathematical formula}e,w′⊨KR∧¬R. Firstly, {a mathematical formula}e⊨KR because (by Theorem 14) {a mathematical formula}w⊨R for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Secondly, by construction, {a mathematical formula}w′⊨¬R.
        </list-item>
        <list-item label="2.">
         Let R be a rigid atom and {a mathematical formula}e=〈e1,e2〉 with {a mathematical formula}e1={w|w⊨R} and {an inline-figure}. We show that {an inline-figure}. Firstly, {an inline-figure} iff (by Theorem 13) {a mathematical formula}⌊e|¬R⌋=∞ or {an inline-figure} for all {a mathematical formula}w∈e⌊e|¬R⌋, which trivially holds. Secondly, {an inline-figure} iff (by Theorem 13) {an inline-figure} or {an inline-figure} for all {an inline-figure}, which holds by definition of {a mathematical formula}e1. However, {a mathematical formula}e⊨B(¬R⇒R) iff {a mathematical formula}⌊e|¬R⌋=∞ or {a mathematical formula}w⊨¬R⊃R for all {a mathematical formula}w∈e⌊e|¬R⌋, which is false since {a mathematical formula}⌊e|¬R⌋=2 and {a mathematical formula}w⊭R for some {a mathematical formula}w∈e2.
        </list-item>
        <list-item label="3.">
         Let R and e be as in the previous case. We showed that {an inline-figure}, but {a mathematical formula}e⊭B(¬R⇒R), so clearly strengthening the premise in {an inline-figure} by ¬R renders it false: {an inline-figure}.
        </list-item>
        <list-item label="4.">
         Again let R and e be as in the first case. We show {an inline-figure}, which is just what the abbreviation {a mathematical formula}BR≡KR stands for. In the first case we already showed that {an inline-figure}. However, {a mathematical formula}w⊭R for some {a mathematical formula}w∈e2, so {a mathematical formula}e⊭KR by Theorem 14.
        </list-item>
        <list-item label="5.">
         We show that {a mathematical formula}e⊨B(α⇒β)⊃B(α⊃β) for all e. According to Rule S9 we have
        </list-item>
        <list-item label="6.">
         We show that {a mathematical formula}e⊨Bα∧Bβ⊃B(α⇒β) for all e. Let {a mathematical formula}e⊨Bα∧Bβ. By Theorem 13, either {an inline-figure}, or {an inline-figure} and {an inline-figure} for all {an inline-figure}. If {an inline-figure}, then also {a mathematical formula}⌊e|α⌋=∞ and hence {a mathematical formula}e⊨B(α⇒β) by Theorem 13. Otherwise, {an inline-figure} and {a mathematical formula}e,w⊨(α∧β) for all {an inline-figure}. Then clearly {an inline-figure} and {a mathematical formula}e,w⊨(α⊃β) for all {a mathematical formula}w∈e⌊e|α⌋, and therefore {a mathematical formula}e⊨B(α⇒β) by Theorem 13.
        </list-item>
        <list-item label="7.">
         We show that {a mathematical formula}e⊨Bα∧B(α⊃β)⊃Bβ for all e. Let {a mathematical formula}e⊨Bα∧B(α⊃β). We need to show that {a mathematical formula}e⊨Bβ, which by Theorem 13 holds iff {an inline-figure} or {a mathematical formula}e,w⊨β for all {an inline-figure}. Suppose {an inline-figure}, for otherwise {a mathematical formula}e⊨Bβ follows trivially. From the antecedent {a mathematical formula}e⊨Bα∧B(α⊃β) we obtain by Theorem 13 that {a mathematical formula}e,w⊨α∧(α⊃β) for all {an inline-figure}. Thus {a mathematical formula}e,w⊨β for all {an inline-figure}, and so {a mathematical formula}e⊨Bβ.
        </list-item>
        <list-item label="8.">
         We show that {a mathematical formula}e⊨Kα∧K(α⊃β)⊃Kβ for all e. Let {a mathematical formula}e⊨Kα∧K(α⊃β). By Theorem 14, {a mathematical formula}e,w⊨α and {a mathematical formula}e,w⊨(α⊃β) for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Hence, {a mathematical formula}e,w⊨β for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N, and so {a mathematical formula}e,w⊨Kβ by Theorem 14.
        </list-item>
        <list-item label="9.">
         We show that {a mathematical formula}e⊨Bα∧B(α⇒β)⊃Bβ for all e. Let {a mathematical formula}e⊨Bα∧B(α⇒β). By Property 5, {a mathematical formula}e⊨B(α⊃β), and thus by Property 7, {a mathematical formula}e⊨Bβ.
        </list-item>
        <list-item label="10.">
         Let {a mathematical formula}e⊨Kα. Then by Theorem 14, {a mathematical formula}e,w⊨α for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N, particularly when {an inline-figure}. Thus by Rule S9, {a mathematical formula}e⊨Bα.
        </list-item>
        <list-item label="11.">
         Let {a mathematical formula}e⊨B(α⇒β). Then {a mathematical formula}e,w⊨B(α⇒β) for arbitrary w, and particularly for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Thus by Theorem 14, {a mathematical formula}e⊨KB(α⇒β).
        </list-item>
        <list-item label="12.">
         Let {a mathematical formula}e⊭B(α⇒β). Then similar to the above, {a mathematical formula}e,w⊭B(α⇒β) for arbitrary w, and particularly for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Thus by Theorem 14, {a mathematical formula}e⊨K¬B(α⇒β).
        </list-item>
        <list-item label="13.">
         Let {a mathematical formula}e⊨∀xB(α⇒β). By Rules S4, S6, and S9, for all standard names n, for all {a mathematical formula}p∈N, if {a mathematical formula}p≤⌊e|α⌋ and {a mathematical formula}w∈ep, then {a mathematical formula}e,w⊨α⊃βnx. Reintroducing the quantifier by Rules S4 and S6 in front of β yields that for all {a mathematical formula}p∈N, if {a mathematical formula}p≤⌊e|α⌋ and {a mathematical formula}w∈ep, then {a mathematical formula}e,w⊨α⊃∀xβ. Thus by Rule S9, {a mathematical formula}e⊨B(α⇒∀xβ).
        </list-item>
        <list-item label="14.">
         Let {a mathematical formula}e,w⊨α for all {a mathematical formula}e,w. Then {an inline-figure} for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N for all e, so by Theorem 14, {a mathematical formula}e⊨Kα follows.
        </list-item>
        <list-item label="15.">
         Let {a mathematical formula}e⊨B(α⇒B(β⇒γ))∧¬K¬α. The first assumption implies by Theorem 13 that {a mathematical formula}⌊e|α⌋≠∞ or {a mathematical formula}e,w⊨α⊃B(β⇒γ) for all {a mathematical formula}w∈e⌊e|α⌋. The second assumption implies by Theorem 14 that {a mathematical formula}⌊e|α⌋≠∞, and thus {a mathematical formula}e,w⊨α for some {a mathematical formula}w∈e⌊e|α⌋. Hence {a mathematical formula}e,w⊨α∧(α⊃B(β⇒γ)) for that w, so {a mathematical formula}e⊨B(β⇒γ).  □
        </list-item>
       </list>
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Properties of only-believing
      </section-title>
      <paragraph>
       The idea behind only-believing is to specify that a given set of conditional beliefs is all the agent believes. Only-believing hence not only captures what the agent believes, but also what she does not believe. Such an account not only of belief but also non-belief is vital to obtain meaningful results for queries that involve meta-belief such as {a mathematical formula}B(InBox(gift)∧¬∃yBgift=y), which says that the agent believes an unidentified gift is in the box.
      </paragraph>
      <paragraph>
       In this section we show that only-believing exhibits a unique model. As it turns out, this model can be determined in a greedy fashion, namely by maximizing the spheres one after another, starting with the inner-most. While this is not to say that this is the only imaginable way to express only-belief, we will observe a close relationship between only-believing and Levesque's only-knowing as well as Pearl's System Z. We will further see that an ordinary closed-world assumption for conditional belief is not well-behaved and hence not a viable alternative to only-believing.
      </paragraph>
      <paragraph>
       To begin with, we show the unique-model property for only-believing in the next two theorems.
      </paragraph>
      <paragraph label="Theorem 18">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective. If{a mathematical formula}e⊨OΓand{a mathematical formula}e′⊨OΓ, then{a mathematical formula}e=e′.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}e⊨OΓ and {a mathematical formula}e′⊨OΓ. We show by induction on {a mathematical formula}p∈N that {a mathematical formula}ep=ep′ and that {a mathematical formula}⌊e|ϕi⌋&gt;p iff {a mathematical formula}⌊e′|ϕi⌋&gt;p for all i. For the base case consider {a mathematical formula}p=1. By Rule S10, {a mathematical formula}w∈e1 iff {a mathematical formula}w⊨⋀1≤i≤m(ϕi⊃ψi) iff {a mathematical formula}w∈e1′. Thus {a mathematical formula}e1=e1′, and {a mathematical formula}⌊e|ϕi⌋&gt;1 iff {a mathematical formula}w⊭ϕi for all {a mathematical formula}w∈e1=e1′ iff {a mathematical formula}⌊e′|ϕi⌋&gt;1. For the induction step suppose the statement holds for {a mathematical formula}p−1. By induction, {a mathematical formula}⌊e|ϕi⌋≥p iff {a mathematical formula}⌊e′|ϕi⌋≥p for all i (*). By Rule S10, {a mathematical formula}w∈ep iff {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi) iff (by (*)) {a mathematical formula}w⊨⋀i:⌊e′|ϕi⌋≥p(ϕi⊃ψi) iff {a mathematical formula}w∈ep′. Thus {a mathematical formula}ep=ep′, and {a mathematical formula}⌊e|ϕi⌋&gt;p iff {a mathematical formula}w⊭ϕi for all {a mathematical formula}w∈ep=ep′ iff {a mathematical formula}⌊e′|ϕi⌋&gt;p.  □
      </paragraph>
      <paragraph label="Theorem 19">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective. Then there is an e such that{a mathematical formula}e⊨OΓ.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}e=〈e1,…,em+1〉, where {a mathematical formula}e1={w|w⊨⋀i(ϕi⊃ψi)} and {a mathematical formula}ep={w|w⊨⋀i:⌊〈e1,…,ep−1〉|ϕi⌋≥p(ϕi⊃ψi)} for {a mathematical formula}p&gt;1. This is well-defined as the right-hand side for {a mathematical formula}ep only refers to {a mathematical formula}e1,…,ep−1. Note that {a mathematical formula}⌊〈e1,…,ep−1〉|ϕ⌋≥p iff {a mathematical formula}⌊e|ϕ⌋≥p for any objective ϕ (*). To see that for all i either {a mathematical formula}⌊e|ϕi⌋≤m or {a mathematical formula}⌊e|ϕi⌋=∞ (**), suppose there is a “hole” in the plausibility ranking, that is, there is some p and i such that {a mathematical formula}p+1=⌊e|ϕi⌋≠∞, and {a mathematical formula}⌊e|ϕj⌋≠p for all j. Then {a mathematical formula}w∈ep iff (by (*)) {a mathematical formula}w⊨⋀k:⌊e|ϕk⌋≥p(ϕk⊃ψk) iff (since p is a hole) {a mathematical formula}w⊨⋀k:⌊e|ϕk⌋≥p+1(ϕk⊃ψk) iff {a mathematical formula}w∈ep+1. Then {a mathematical formula}w⊨ϕi for some {a mathematical formula}w∈ep+1=ep, which contradicts the assumption {a mathematical formula}p+1=⌊e|ϕi⌋. By (*) and (**), e satisfies Rule S10.  □
      </paragraph>
      <paragraph>
       The proof reveals a close relationship between only-believing and System Z [57]: the definition of e reflects Pearl's labeling procedure which produces his Z-ranking. Only-believing orders the {a mathematical formula}ϕi⇒ψi by their plausibilities {a mathematical formula}⌊e|ϕi⌋; this ordering thus matches the Z-ranking. (System Z is only defined for propositional logic and requires the conditionals to be consistent, which in our terminology means that {a mathematical formula}⌊e|ϕi⌋≠∞ for all rules. However, these restrictions are not essential for the Z-ranking. A full analysis can be found in [56].)
      </paragraph>
      <paragraph>
       Together, Theorem 18, Theorem 19 constitute the unique-model property of only-believing.
      </paragraph>
      <paragraph label="Corollary 20">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective. Then there is one unique e with{a mathematical formula}e⊨OΓ.
      </paragraph>
      <paragraph>
       Intuitively, only-believing expresses all that is believed by maximizing the epistemic state. More precisely, for some formula α involving beliefs, we say e is maximal with {a mathematical formula}e⊨α when no worlds can be added to any plausibility level without falsifying α, that is, {a mathematical formula}e′⊭α for all {a mathematical formula}e′ with {a mathematical formula}ep′⊇ep for all {a mathematical formula}p∈N and {a mathematical formula}ep′′⊋ep′ for some {a mathematical formula}p′∈N.
      </paragraph>
      <paragraph label="Theorem 21">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective. Then{a mathematical formula}e⊨OΓiff{a mathematical formula}e⊨⋀iB(ϕi⇒ψi)and e is maximal.
      </paragraph>
      <paragraph label="Proof">
       For the if direction suppose {a mathematical formula}e⊨B(ϕi⇒ψi) for all i and e is maximal with that property. Let {a mathematical formula}p∈N and w be a world. By Rule S9, if {a mathematical formula}p≤⌊e|ϕi⌋ and {a mathematical formula}w∈ep, then {a mathematical formula}w⊨ϕi⊃ψi for all i. Since e is maximal, if {a mathematical formula}p≤⌊e|ϕi⌋ and {a mathematical formula}w∉ep, then {a mathematical formula}w⊭ϕi⊃ψi for some i. Therefore {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi) iff {a mathematical formula}w∈ep. Hence {a mathematical formula}e⊨O{ϕ1⇒ψ1,…,ϕm⇒ψm}.For the only-if direction suppose {a mathematical formula}e⊨O{ϕ1⇒ψ1,…,ϕm⇒ψm}. Then from Rules S9 and S10 immediately follows that {a mathematical formula}e⊨B(ϕi⇒ψi) for all i. To see that e is maximal, suppose {a mathematical formula}e′⊨B(ϕi⇒ψi) for all i and {a mathematical formula}ep⊆ep′ for all {a mathematical formula}p∈N. Then by the if direction {a mathematical formula}e′⊨O{ϕ1⇒ψ1,…,ϕm⇒ψm}, and by Theorem 18{a mathematical formula}e=e′.  □
      </paragraph>
      <paragraph>
       The theorem illustrates the connection between only-believing and Levesque's only-knowing [26]. Only-knowing α means that all the agent knows is α, where knowledge differs from belief in that it cannot be revised. In Levesque's semantics, this means the epistemic state satisfies {a mathematical formula}Kα and is maximal. The very same effect is achieved in our logic by {an inline-figure}. Only-believing can hence be considered to generalize only-knowing to the case of conditional beliefs. For the formal proof that {a mathematical formula}ESB subsumes Levesque's logic of only-knowing we refer to [56].
      </paragraph>
      <paragraph>
       Only-believing a set of conditionals aims to express that these conditionals are believed, but nothing else is. This idea resembles a closed-world assumption, and indeed Levesque's only-knowing can be simulated by a closed-world assumption on knowledge to some extent: Reiter [4] proposes the infinite knowledge base {a mathematical formula}{Kϕ}∪{¬Kψ|Kϕ⊭Kψ} to capture that ϕ is all that is known. For queries without nested K, this closed-world assumption on knowledge is equivalent to Levesque's only-knowing. (It fails to deal with introspective queries like {a mathematical formula}K(InBox(gift)∧¬∃yKgift=y), though.)
      </paragraph>
      <paragraph>
       So the question may arise: does Reiter's closed-world assumption work similarly for conditional belief? Perhaps surprisingly, the answer is no. As a matter of fact, making a closed-world assumption on belief does not even preserve satisfiability. Analogous to Reiter's definition [4], let us define the closed-world assumption on {a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm} as{a mathematical formula} To see that this closed-world assumption does not preserve satisfiability, consider {a mathematical formula}Γ={R1⇒R2,R3⇒R4}: {a mathematical formula}CWA(Γ) contains the negative beliefs {a mathematical formula}¬B(R1⇒(R3⊃R4)) and {a mathematical formula}¬B(R3⇒(R1⊃R2)), which are inconsistent with the positive beliefs {a mathematical formula}B(R1⇒R2) and {a mathematical formula}B(R3⇒R4) in {a mathematical formula}CWA(Γ) (as can be easily verified by confirming that {a mathematical formula}R1 and {a mathematical formula}R3 must be equally plausible, and at least one of the most-plausible {a mathematical formula}R1-worlds must falsify {a mathematical formula}(R3⊃R4), but all of them must satisfy {a mathematical formula}(R3⊃R4), which is a contradiction). A closed-world assumption on conditional belief is therefore no viable alternative to only-believing, as it adds too many negative beliefs. In particular, there seems to be no obvious way of capturing a conditional knowledge base in formalisms like Shapiro et al.'s [12].
      </paragraph>
      <paragraph>
       However, only-believing is not free from counterintuitive behavior either. In the above example, it is somewhat odd that {a mathematical formula}O{R1⇒R2,R3⇒R4}⊨¬B(R1∧¬R2∧R3⇒R4), although there is no reason why evidence of {a mathematical formula}R1∧¬R2 should defeat that {a mathematical formula}R3 usually implies {a mathematical formula}R4. The same problem occurs in System Z. It is noteworthy that c-representations [61] avoid this problem.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      The belief projection problem
     </section-title>
     <paragraph>
      The belief projection problem is to decide if a certain belief holds true after a sequence of actions. Logically this is expressed as an entailment problem: given a knowledge base about the domain's dynamics and the agent's initial (conditional) beliefs, does a certain formula about actions and beliefs follow?
     </paragraph>
     <paragraph>
      Besides the agent's initial beliefs, such a knowledge base needs to represent the dynamics of the worlds. For this purpose, we adopt Reiter's solution of the frame problem through successor-state axioms[4], [24]. The idea is to specify one axiom per fluent that specifies its truth value after the next action in terms of some formula before that action. In our language, a successor-state axiom for a fluent F has the form {a mathematical formula}□[a]F(x1,…,xk)≡γF, where {a mathematical formula}γF is static The axiom says that after any sequence of actions, the fluent {a mathematical formula}F(x1,…,xk) is true after another action a iff the formula {a mathematical formula}γF is true before that action a. It is very common to have {a mathematical formula}γF be of the form {a mathematical formula}γF+∨F(x1,…,xk)∧¬γF−, where {a mathematical formula}γF+ represents the positive effect condition, that is, the condition under which {a mathematical formula}F(x1,…,xk) is set to true, and {a mathematical formula}γF− accordingly is the negative effect condition. Such an axiom {a mathematical formula}□[a]F(x1,…,xk)≡γF+∨F(x1,…,xk)∧¬γF− then intuitively means that {a mathematical formula}F(x1,…,xk) holds after a iff it is either turned on ({a mathematical formula}γF+) or not turned off ({a mathematical formula}¬γF−) by a.
     </paragraph>
     <paragraph>
      While successor-state axioms take care of the physical effects of actions, another kind of axiom is needed to capture their epistemic effects. Recall that any action a induces a belief revision by {a mathematical formula}IF(a). In order to assign a deeper meaning to this new information, a knowledge base shall contain an axiom of the form {a mathematical formula}□IF(a)≡φ, which we call an informed-fluent axiom. A customary pattern for φ is a conjunction of formulas {a mathematical formula}((a=A(x1,…,xk))⊃φA): when an action matches the antecedent of one of the conjuncts, it revises {a mathematical formula}φA; if it matches none of the conjuncts, then φ evaluates to {an inline-figure}, which effectively means that the action has no epistemic effect.
     </paragraph>
     <paragraph>
      Based on these ideas, and in the spirit Reiter's situation calculus [4], [24], the knowledge bases we consider in this paper adhere to the following definition.
     </paragraph>
     <paragraph label="Definition 22">
      Let {a mathematical formula}F be a finite set of fluent predicate symbols and {a mathematical formula}IF∉F. A formula is fluent when it is objective, static, and all fluent predicate symbols are from {a mathematical formula}F. A basic action theory over {a mathematical formula}F consists of two sets {a mathematical formula}Σdyn and {a mathematical formula}Σbel, where
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Σdyn contains dynamic axioms, namely:
      </list-item>
      <list-item label="•">
       {a mathematical formula}Σbel contains finitely many conditionals {a mathematical formula}ϕ⇒ψ where ϕ and ψ are fluent sentences.
      </list-item>
     </list>
     <paragraph>
      Notice that in the conditional {an inline-figure} in {a mathematical formula}O(Σdyn,Σbel) expresses that the agent knows the dynamic axioms {a mathematical formula}Σdyn, that is, the successor-state axioms and the informed-fluent axiom are unequivocal.
     </paragraph>
     <paragraph>
      In Sections 5 and 6 we provide two solutions for the belief projection problem, one by regression and another by progression. Briefly said, regression takes the dynamics out of the projection problem by rewriting the query to undo the actions. Progression, on the other hand, eliminates the actions by applying their effects to the initial beliefs.
     </paragraph>
     <section label="4.1">
      <section-title>
       A model of being informed
      </section-title>
      <paragraph>
       The intuition behind our model of receiving new information is that actions inform the agent that some information is likely true. The informed-fluent axiom {a mathematical formula}□IF(a)≡φ of a basic action theory is to specify this, and before the action a is performed, the beliefs are revised by {a mathematical formula}IF(a). Hence {a mathematical formula}IF(a) can also be considered a (plausible) precondition of a being executable; so whenever a is executed, it is plausible that {a mathematical formula}IF(a) is true, and the revision by {a mathematical formula}IF(a) ensures that this is believed. Let us briefly discuss the advantages of informing over the classical sensing model for our purposes.
      </paragraph>
      <paragraph>
       The traditional approach to perception in the situation calculus is that an action senses whether an associated formula holds in the actual world [30], [24]. The intuitive difference between classical sensing and our approach is as follows. Classical sensing answers questions based on the real world's ground truth (for example, “is the gift broken?”); such an answer is definitive and cannot be retracted. In our model, on the other hand, actions inherently carry information which is assumed to be likely true (for example, “the gift is broken” or “the gift is not broken”); that information is not checked back with the real world and may thus very well be wrong.
      </paragraph>
      <paragraph>
       The view of informing as opposed to sensing enables us to handle contradicting information in a reasonable way. Whereas the classical approach then gets caught in an inconsistent state (where “everything” is known), our logic displaces the old information by belief revision.
      </paragraph>
      <paragraph>
       The intuition behind an informing action is however somewhat different from a classical sensing action. The classical view is that the action is under the control of the agent. Informing actions are often better seen as exogenous actions, meaning not the agent executes them but nature. For example, the clinking noise in our introductory example is not performed by the agent, but is an event that occurs outside of the agent's control. (We refer to [4] for how to model the emergence of exogenous actions in the situation calculus.)
      </paragraph>
      <paragraph>
       Nevertheless we can mimic classical sensing in our approach using an additional parameter for the sensing outcome. Suppose A should sense whether or not ϕ holds in the actual world. We can simulate this with a strong-revision action {a mathematical formula}A(outcome), where outcome takes a binary value to represent whether ϕ holds in the real world (for example, {a mathematical formula}outcome=1# iff ϕ is true), and {a mathematical formula}IF(A(y)) is defined as ϕ or ¬ϕ depending on the value of y. Then {a mathematical formula}A(outcome) informs the agent about the real-world value of ϕ, and the revision promotes the worlds that accord with this value. Thus, when the agent performs a sequence of sensings of this form, she believes their outcomes afterwards (provided they are consistent): if she first senses {a mathematical formula}ϕ1 and then {a mathematical formula}¬ϕ2, say, then after strong revision by {a mathematical formula}ϕ1 and then by {a mathematical formula}¬ϕ2, the most-plausible worlds satisfy {a mathematical formula}ϕ1∧¬ϕ2 (this follows from the NPP3 and AGM2 postulates shown in Section 7). This modeling is not limited to binary sensing. For instance, a sonar sensor that senses a distance to some obstacle can be represented with an action {a mathematical formula}sonar(y), where y is the sensed distance. When the basic action theory stipulates {a mathematical formula}IF(sonar(y))≡distance=y, then {a mathematical formula}∀y((distance=y)⊃[sonar(y)]B(distance=y)) holds, that is, the agent believes the correct distance.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       An example
      </section-title>
      <paragraph>
       We recap the gift box example from Section 1 and model it with a basic action theory. The scenario comprises a single box that may contain items, which we represent by a fluent predicate {a mathematical formula}InBox(n). The box can be dropped by action dropbox, and an item n can be taken out of the box by action {a mathematical formula}unbox(n). Dropping the box breaks all fragile items in it, which is formalized using a rigid predicate {a mathematical formula}Fragile(n) and another fluent predicate {a mathematical formula}Broken(n). A clinking noise, represented by the action clink, indicates that something in the box seems to be broken: {a mathematical formula}∃y(InBox(y)∧Broken(y)). Intuitively clink is exogenous, that is, it is not under the agent's control but she observes (nature executing) a clink. Unboxing an item n through action {a mathematical formula}unbox(n) tells us that this item was in the box and is not broken: {a mathematical formula}InBox(n)∧¬Broken(n). The successor-state axioms for InBox and Broken and the informed-fluent axiom constitute the dynamic axioms:{a mathematical formula} We still need to decide of which revision sort the actions are. As pointed out earlier, there is no definite answer to the question which operator is most appropriate in certain circumstances. Since a clinking noise is a rather unreliable hint that something is broken, we decide to make clink a weak-revision action. By contrast, when one takes an object out of the box, that object must indeed have been in the box and be in one piece (otherwise one probably hallucinates), so {a mathematical formula}unbox(n) shall be a strong-revision action. We let dropbox be a strong-revision action, too; since {a mathematical formula}IF(dropbox) is vacuously true (as {a mathematical formula}Σdyn⊨IF(dropbox)) the revision has no effect anyway.
      </paragraph>
      <paragraph>
       Our agent believes that most likely the box is empty; but taking the possibility into account that she may be wrong about that, she believes that in this case only the gift would be in the box. We use the object constant gift to refer to the gift that may or may not be in the box. Note that it is not a standard name, so the agent might have no clue what the gift actually is. She moreover believes that if there was something in the box, it would not be broken yet. Thus we define the initial beliefs as{a mathematical formula}
      </paragraph>
      <paragraph>
       Let us conclude the example for now by investigating a few queries.
      </paragraph>
      <list>
       <list-item label="1.">
        Initially the agent believes the box is empty: {a mathematical formula}O(Σdyn,Σbel)⊨B∀y¬InBox(y).
       </list-item>
       <list-item label="2.">
        After dropping the box, she still believes the box is empty, but also that if something fragile is in the box, then presumably it is broken: {a mathematical formula}O(Σdyn,Σbel)⊨[dropbox](B(∀y¬InBox(y))∧∀yB(InBox(y)∧Fragile(y)⇒Broken(y))).
       </list-item>
       <list-item label="3.">
        When a clink occurs after dropping the box, she comes to believe that the gift is in the box, but she has no idea what the gift is: {a mathematical formula}O(Σdyn,Σbel)⊨[dropbox][clink]B(InBox(gift)∧Broken(gift)∧¬∃yBgift=y).
       </list-item>
       <list-item label="4.">
        When the object {a mathematical formula}5# is taken out of the box, she believes that this must be the gift, and that it is not broken after all{sup:4}: {a mathematical formula}O(Σdyn,Σbel)⊨[dropbox][clink][unbox(5#)]∃yB(gift=y∧¬InBox(gift)∧¬Broken(gift)).
       </list-item>
      </list>
      <paragraph>
       We will use the latter query to illustrate the techniques developed in the upcoming sections of the paper to automate the reasoning task. But for now let us verify the entailments through semantical proofs.
      </paragraph>
      <paragraph>
       Firstly we need to determine the epistemic state {a mathematical formula}e⊨O(Σdyn,Σbel). By Corollary 20, e is unique, and using the idea from the proof of Theorem 19 we generate {a mathematical formula}e=〈e1,e2,e3〉. The first level {a mathematical formula}e1 contains all worlds that satisfy {a mathematical formula}Σdyn and the material-implication-versions of all conditionals in {a mathematical formula}Σbel, which simplifies to{a mathematical formula} Thus {an inline-figure} and {a mathematical formula}⌊e|∃yInBox(y)⌋&gt;1, so the next level {a mathematical formula}e2 contains all worlds that satisfy {a mathematical formula}Σdyn and {a mathematical formula}∃yInBox(y)⊃∀y(InBox(y)≡y=gift) as well as {a mathematical formula}∃yInBox(y)⊃∀y(InBox(y)⊃¬Broken(y)), which simplifies to{a mathematical formula} Hence {a mathematical formula}⌊e|∃yInBox(y)⌋=2, so all following levels contain all worlds that satisfy {a mathematical formula}Σdyn, that is,{a mathematical formula}
      </paragraph>
      <paragraph>
       The first query, {a mathematical formula}B∀y¬InBox(y), obviously holds because {a mathematical formula}w⊨∀y¬InBox(y) for all {a mathematical formula}w∈e1. For the other queries we need to progress e. The action dropbox makes each {a mathematical formula}Broken(n) true when {a mathematical formula}Fragile(n) and {a mathematical formula}InBox(n) are true. Since dropbox makes a (strong) revision by the vacuously true {a mathematical formula}IF(dropbox), there effectively is no revision. The progression {a mathematical formula}e≫dropbox is thus{a mathematical formula}It is then easy to see that the second query holds. Clearly {a mathematical formula}[dropbox]B∀y¬InBox(y) is true. And for all n, there is some {a mathematical formula}w∈(e≫dropbox)2 such that {a mathematical formula}w⊨InBox(n)∧Fragile(n), and then also {a mathematical formula}w⊨Broken(n), so {a mathematical formula}[dropbox]∀yB(InBox(y)∧Fragile(y)⇒Broken(y)) holds as well.
      </paragraph>
      <paragraph>
       In the third query the agent hears a clink after dropping the box. The action clink does not change the truth value of any fluents, but it triggers a weak revision by {a mathematical formula}∃y(InBox(y)∧Broken(y)), that is, the most-plausible worlds from {a mathematical formula}e≫dropbox satisfying this formula constitute the first plausibility level in {a mathematical formula}(e≫dropbox)⁎IF(clink). It is therefore easy to see that {a mathematical formula}(e≫dropbox)≫clink=(e≫dropbox)⁎IF(clink) is defined by{a mathematical formula} We therefore have {a mathematical formula}w⊨InBox(gift)∧Broken(gift) for all {a mathematical formula}w∈(e≫dropbox≫clink)1. Moreover, the worlds do not agree on the denotation of gift, so there is no standard name n such that {a mathematical formula}w⊨gift=n for all {a mathematical formula}w∈(e≫dropbox≫clink)1. Thus the third query, {a mathematical formula}O(Σdyn,Σbel)⊨[dropbox][clink]B(InBox(gift)∧Broken(gift)∧¬∃yBgift=y)), meaning that the gift is believed to be in the box and broken but the agent has no clue what the gift is, comes out true.
      </paragraph>
      <paragraph>
       For the last query, we need to make another progression by {a mathematical formula}unbox(5#). Firstly, the state is strongly revised by {a mathematical formula}IF(unbox(5#)), which is equivalent to {a mathematical formula}InBox(5#)∧¬Broken(5#). The first two levels of the revised state thus contain the {a mathematical formula}IF(unbox(5#))-worlds from {a mathematical formula}(e≫dropbox≫clink)3 and {a mathematical formula}(e≫dropbox≫clink)4. For space reasons we only consider the first plausibility level, which is{a mathematical formula} and when we then apply the physical effect of {a mathematical formula}unbox(5#), namely make {a mathematical formula}InBox(5#) false, we obtain{a mathematical formula} The fourth query, {a mathematical formula}[dropbox][clink][unbox(5#)]∃yB(gift=y∧¬InBox(gift)∧¬Broken(gift)), is thus true, because all worlds at the first plausibility level agree on gift being {a mathematical formula}5#.
      </paragraph>
      <paragraph>
       It is interesting that the fourth query would not have come out true if clink was a strong-revision action. Then the agent would have rather believed that there were two (or more) items in the box than that the clink was due to something other than an object in the box breaking. That is quite reasonable: a strong-revision action clink would have made the agent very reluctant to give up the belief that something inside the box broke.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Belief projection by regression
     </section-title>
     <paragraph>
      The first solution we offer for the belief projection problem is by regression. Regression rewrites a formula about future situations to a formula about the initial situation. The idea, due to Reiter [3], [4], is to successively replace subformulas {a mathematical formula}[t]F(t1,…,tk) with the right-hand side of F's successor-state axiom {a mathematical formula}γF. Intuitively this is sound because the successor-state axioms ensure that actions have deterministic effects. As we shall see in this section, we can regress beliefs after actions in a similar way. Our regression operator can thus handle formulas with no □ or O, provided the fluent predicates are taken from {a mathematical formula}F∪{IF}. We call such a formula regressable.
     </paragraph>
     <paragraph>
      To ease the technical treatment we assume that the formula to be regressed adheres to the following form:
     </paragraph>
     <list>
      <list-item label="•">
       it is rectified: quantifiers use distinct variables, and none of the variables occurs in the basic action theory;
      </list-item>
      <list-item label="•">
       action terms {a mathematical formula}A(t1,…,tn) have only standard names or variables as arguments {a mathematical formula}ti.
      </list-item>
     </list>
     <paragraph>
      It is easy to see that any formula can be rewritten to satisfy these constraints. For example, {a mathematical formula}IF(unbox(gift)) is transformed to {a mathematical formula}∃y(y=gift∧IF(unbox(y))). The first restriction is needed because otherwise scopes of variables may collide during regression. The second one will allow us to push action operators inside B, which would be inappropriate for action terms like {a mathematical formula}unbox(gift) because the denotation of gift shall be determined by the real world.
     </paragraph>
     <paragraph>
      Section 5.1 is only concerned with objective formulas, whose regression works the same way as in {a mathematical formula}ES[24]. Section 5.2 then extends the regression operator to also handle beliefs as well. In Section 5.3 we discuss an example.
     </paragraph>
     <section label="5.1">
      <section-title>
       Regression of objective formulas
      </section-title>
      <paragraph>
       For objective regressable formulas, our regression operator follows the one presented by Lakemeyer and Levesque [24] for the logic {a mathematical formula}ES. Intuitively, it works by pushing action operators {a mathematical formula}[t] inwards and replacing subformulas of the form {a mathematical formula}[t]F(t1,…,tk) for {a mathematical formula}F∈F with the right-hand side of F's successor-state axiom {a mathematical formula}γF as well as replacing atoms {a mathematical formula}IF(t) with the right-hand side of the informed-fluent axiom φ. That way, eventually all {a mathematical formula}[t] operators are eliminated.
      </paragraph>
      <paragraph label="Definition 23">
       The regression of an objective regressable formula α after actions r with respect to a basic action theory over fluents {a mathematical formula}F is defined as follows:
      </paragraph>
      <list>
       <list-item label="R1.">
        {a mathematical formula}R[r,R(t1,…,tk)]=R(t1,…,tk) for rigid predicate symbols R;
       </list-item>
       <list-item label="R2.">
        {a mathematical formula}R[r,F(t1,…,tk)] for fluent predicate symbols {a mathematical formula}F∈F is defined inductively on r:
       </list-item>
       <list-item label="R3.">
        {a mathematical formula}R[r,IF(t)]=R[r,φta];
       </list-item>
       <list-item label="R4.">
        {a mathematical formula}R[r,(t1=t2)]=(t1=t2);
       </list-item>
       <list-item label="R5.">
        {a mathematical formula}R[r,¬α]=¬R[r,α];
       </list-item>
       <list-item label="R6.">
        {a mathematical formula}R[r,(α1∨α2)]=(R[r,α1]∨R[r,α2]);
       </list-item>
       <list-item label="R7.">
        {a mathematical formula}R[r,∃xα]=∃xR[r,α];
       </list-item>
       <list-item label="R8.">
        {a mathematical formula}R[r,[t]α]=R[r⋅t,α].
       </list-item>
      </list>
      <paragraph label="Theorem 24">
       Let{a mathematical formula}Σdynbe the dynamic axioms of a basic action theory, ϕ be a fluent sentence, and ψ be an objective regressable sentence. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       The theorem is very similar to one in [24]. The proof is in Appendix A.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Regression of non-objective formulas
      </section-title>
      <paragraph>
       The key to extending regression to beliefs is the relationship between beliefs after an action and the (conditional) beliefs before that action. We will use this correspondence to regress beliefs similar to how we use successor-state axioms to regress fluent atoms.
      </paragraph>
      <paragraph>
       The next two lemmas relate the plausibilities of sentences in e to {a mathematical formula}e≫n. These relations are not surprising as they mirror the definitions of {a mathematical formula}e⁎wIF(n) and {a mathematical formula}e⁎sIF(n), respectively, from Definition 8.
      </paragraph>
      <paragraph label="Lemma 25">
       Let n be a weak-revision action standard name and{a mathematical formula}⌊e|IF(n)⌋≠∞.
      </paragraph>
      <list>
       <list-item>
        If{a mathematical formula}⌊e|IF(n)⌋=⌊e|IF(n)∧[n]α⌋, then{a mathematical formula}⌊e≫n|α⌋=1.
       </list-item>
       <list-item>
        If{a mathematical formula}⌊e|IF(n)⌋≠⌊e|IF(n)∧[n]α⌋, then{a mathematical formula}⌊e≫n|α⌋=⌊e|[n]α⌋+1.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i) By assumption {a mathematical formula}e,w⊨IF(n)∧[n]α for some {a mathematical formula}w∈e⌊e|IF(n)⌋. Thus {a mathematical formula}e,w⊨[n]α for some {a mathematical formula}w∈(e⁎wIF(n))1, and so by Rule S7, {a mathematical formula}e≫n,w⊨α for some {a mathematical formula}w∈(e≫n)1. Therefore {a mathematical formula}⌊e≫n|α⌋=1.(ii) By assumption, {a mathematical formula}e,w⊭IF(n)∧[n]α for all {a mathematical formula}w∈e⌊e|IF(n)⌋. Thus {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈(e⁎wIF(n))1 (*). Thus {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)1, and hence {a mathematical formula}⌊e≫n|α⌋&gt;1. Now let {a mathematical formula}p∈N. First suppose {a mathematical formula}p&lt;⌊e|[n]α⌋. Then {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈ep. Hence and by (*), {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈(e⁎wIF(n))p+1. Thus {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)p+1, and therefore {a mathematical formula}p+1&lt;⌊e≫n|α⌋. Now suppose {a mathematical formula}p≥⌊e|[n]α⌋. Then {a mathematical formula}e,w⊨[n]α for some {a mathematical formula}w∈ep⊆(e⁎wIF(n))p+1. Thus {a mathematical formula}e≫n,w⊨α for some {a mathematical formula}w∈(e≫n)p+1, and hence {a mathematical formula}p+1≥⌊e≫n|α⌋.  □
      </paragraph>
      <paragraph label="Lemma 26">
       Let n be a strong-revision action standard name and{a mathematical formula}⌊e|IF(n)⌋≠∞.
      </paragraph>
      <list>
       <list-item>
        If{a mathematical formula}⌊e|IF(n)∧[n]α⌋≠∞, then{a mathematical formula}⌊e≫n|α⌋=⌊e|IF(n)∧[n]α⌋−⌊e|IF(n)⌋+1.
       </list-item>
       <list-item>
        If{a mathematical formula}⌊e|IF(n)∧[n]α⌋=∞and{a mathematical formula}⌊e|¬IF(n)⌋≠∞, then{a mathematical formula}⌊e≫n|α⌋=⌊e|[n]α⌋+⌈e⌉−⌊e|IF(n)⌋−⌊e|¬IF(n)⌋+2.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i) Suppose {a mathematical formula}⌊e|IF(n)⌋≤p&lt;⌊e|IF(n)∧[n]α⌋. Then {a mathematical formula}e,w⊭IF(n)∧[n]α for all {a mathematical formula}w∈ep. Thus {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈(e⁎sIF(n))p−⌊e|IF(n)⌋+1. By Rule S7, {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)p−⌊e|IF(n)⌋+1. Thus {a mathematical formula}p−⌊e|IF(n)⌋+1&lt;⌊e≫n|α⌋. Analogously {a mathematical formula}p≥⌊e|IF(n)∧[n]α⌋ implies {a mathematical formula}p−⌊e|IF(n)⌋+1≥⌊e≫n|α⌋.(ii) Suppose {a mathematical formula}⌊e|¬IF(n)⌋≤p&lt;⌊e|[n]α⌋. Then {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈ep. So {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈(e⁎sIF(n))p⁎ where {a mathematical formula}p⁎=p+⌈e⌉−⌊e|IF(n)⌋+1−⌊e|¬IF(n)⌋+1, because by the same argument as in (i), {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)p′ and {a mathematical formula}p′≤⌈e⌉−⌊e|IF(n)⌋+1. By Rule S7, {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)p⁎. Thus {a mathematical formula}p⁎&lt;⌊e≫n|α⌋. Analogously {a mathematical formula}p≥⌊e|[n]α⌋ implies {a mathematical formula}p⁎≥⌊e≫n|α⌋.  □
      </paragraph>
      <paragraph>
       We are now ready to establish the relationship between beliefs after and before an action. Theorem 27 considers weak-revision actions, Theorem 28 is about strong-revision actions.
      </paragraph>
      <paragraph label="Theorem 27">
       Let a be a weak-revision action variable. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively the disjunction on the right-hand side considers three different cases. Action a triggers a revision, which promotes certain worlds to the first plausibility level. In the first case, at least one of these worlds satisfies α after a, and therefore we need to consider information learned by a in the antecedent. In the second case, none of them satisfies α after a, and therefore the revision is not relevant to the belief. The third case deals with revision by inconsistent information. The formal proof follows that intuition.
      </paragraph>
      <paragraph label="Proof">
       We prove that the equivalence holds in any epistemic state e for any weak-revision action n substituted for a. We distinguish three cases. The first case supposes {a mathematical formula}e⊭B(IF(n)⇒¬[n]α). The second one supposes the opposite plus {a mathematical formula}⌊e|IF(n)⌋≠∞. The third case supposes {a mathematical formula}⌊e|IF(n)⌋=∞. For each case we show the equivalence. Since the cases are exhaustive, the theorem follows.First suppose {a mathematical formula}e⊭B(IF(n)⇒¬[a]α). Then also {an inline-figure}. Hence the equivalence to be shown reduces to {a mathematical formula}e⊨[n]B(α⇒β)≡B(IF(n)∧[n]α⇒[n]β). Notice that by assumption {a mathematical formula}⌊e|IF(n)⌋=⌊e|IF(n)∧[n]α⌋≠∞ (*), and by Lemma 25{a mathematical formula}⌊e≫n|α⌋≠∞ (**). Now we prove the equivalence: {a mathematical formula}e⊨B(IF(n)∧[n]α⇒[n]β) iff (by Theorem 13 and (*)) {a mathematical formula}e,w⊨IF(n)∧[n]α⊃[n]β for all {a mathematical formula}w∈e⌊e|IF(n)⌋ iff {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈(e⁎wIF(n))1 iff (by (**)) {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)⌊e≫n|α⌋ iff (by Theorem 13 and (**)) {a mathematical formula}e⊨[n]B(α⇒β).Now suppose {a mathematical formula}⌊e|IF(n)⌋≠∞ and {a mathematical formula}e⊨B(IF(n)⇒¬[n]α). Then {an inline-figure}. Similar to the previous case, the remaining equivalence is {a mathematical formula}e⊨[n]B(α⇒β)≡B([n]α⇒[n]β). Notice that by assumption, {a mathematical formula}e,w⊨IF(n)⊃¬[n]α for all {a mathematical formula}w∈e⌊e|IF(n)⌋, so {a mathematical formula}e,w⊭[n]α for all {a mathematical formula}w∈(e⁎wIF(n))1 (*). Now we prove the equivalence: {a mathematical formula}e⊨B([n]α⇒[n]β) iff {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈ep for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e|[n]α⌋ iff (by (*)) {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈(e⁎wIF(n))p for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e|[n]α⌋+1 iff (by Lemma 25) {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)p for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e≫n|α⌋ iff {a mathematical formula}e⊨[n]B(α⇒β).Finally suppose {a mathematical formula}⌊e|IF(n)⌋=∞. Then {a mathematical formula}e,w⊭IF(n) for all {a mathematical formula}p∈N and {a mathematical formula}w∈ep, and so {an inline-figure}. Since {a mathematical formula}⌊e|IF(n)⌋=∞, {a mathematical formula}(e≫n)p={} for all {a mathematical formula}p∈N, and so {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)p. Thus {a mathematical formula}e⊨[n]B(α⇒β).  □
      </paragraph>
      <paragraph label="Theorem 28">
       Let a be a strong-revision action variable. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       The three cases on the right-hand side are similar to the ones for weak revision in Theorem 27. The strong revision caused by a promotes all {a mathematical formula}IF(a)-worlds over all {a mathematical formula}¬IF(a)-worlds. In case some of the former worlds satisfy α after a, some of them make up the most-plausible α-worlds after a, so the belief must also be conditioned on {a mathematical formula}IF(a). This is covered by the first case. Otherwise, if none of the promoted worlds satisfies α after a, the revision is irrelevant for that particular conditional belief. The third case deals with revision by inconsistent information. The formal argument follows this intuition and proceeds generally similar to the one of Theorem 27.
      </paragraph>
      <paragraph label="Proof">
       We prove that the equivalence holds in any epistemic state e for any strong-revision action n substituted for a. We distinguish three cases. The first case supposes {an inline-figure}. The second one supposes the opposite plus {a mathematical formula}⌊e|IF(n)⌋≠∞. The third case supposes {a mathematical formula}⌊e|IF(n)⌋=∞. For each case we show the equivalence. Since the cases are exhaustive, the theorem follows.First suppose {an inline-figure}. Then also {an inline-figure}. Hence the equivalence to be proved reduces to {a mathematical formula}e⊨[n]B(α⇒β)≡B(IF(n)∧[n]α⇒[n]β). Notice that by assumption {a mathematical formula}⌊e|IF(n)∧[n]α⌋≠∞ (*), and by Lemma 25{a mathematical formula}⌊e≫n|α⌋≠∞ (**). Now we can prove the equivalence: {a mathematical formula}e⊨B(IF(n)∧[n]α⇒[n]β) iff (by Theorem 13 and (*)) {a mathematical formula}e,w⊨IF(n)∧[n]α⊃[n]β for all {a mathematical formula}w∈e⌊e|IF(n)∧[n]α⌋ iff {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈(e⁎sIF(n))⌊e|IF(n)∧[n]α⌋−⌊e|IF(n)⌋+1 iff (by Lemma 26) {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)⌊e≫n|α⌋ iff (by Theorem 13 and (**)) {a mathematical formula}e⊨[n]B(α⇒β).Now suppose {an inline-figure} and {a mathematical formula}⌊e|IF(n)⌋≠∞. Then {an inline-figure}. Hence the equivalence left to be shown is {a mathematical formula}e⊨[n]B(α⇒β)≡B([n]α⇒[n]β). Notice that by assumption, {a mathematical formula}e,w⊭IF(n)∧[n]α for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N (*). Thus also {a mathematical formula}e≫n,w⊭α for all {a mathematical formula}w∈(e≫n)p for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌈e⌉−⌊e|IF(n)⌋+1 (**). Now we prove the equivalence. If {a mathematical formula}⌊e|¬IF(n)⌋=∞, then there are no {a mathematical formula}¬IF(n)-worlds in e, so {a mathematical formula}e⊨B([n]α⇒[n]β) holds by (*) and {a mathematical formula}e⊨[n]B(α⇒β) holds by (**). Otherwise the equivalence is shown as follows: {a mathematical formula}e⊨B([n]α⇒[n]β) iff {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈ep for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e|[n]α⌋ iff (by (**)) {a mathematical formula}e,w⊨[n]α⊃[n]β for all {a mathematical formula}w∈(e⁎sIF(n))p for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e|[n]α⌋+⌈e⌉−⌊e|IF(n)⌋−⌊e|¬IF(n)⌋+2 iff (by Lemma 26) {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)p for all {a mathematical formula}p∈N with {a mathematical formula}p≤⌊e≫n|α⌋ iff {a mathematical formula}e⊨[n]B(α⇒β).Finally suppose {a mathematical formula}⌊e|IF(n)⌋=∞. Then {a mathematical formula}e,w⊭IF(n) for all {a mathematical formula}p∈N and {a mathematical formula}w∈ep, and so {an inline-figure}. Since {a mathematical formula}⌊e|IF(n)⌋=∞, {a mathematical formula}(e≫n)p={} for all {a mathematical formula}p∈N, and so {a mathematical formula}e≫n,w⊨α⊃β for all {a mathematical formula}w∈(e≫n)p. Thus {a mathematical formula}e⊨[n]B(α⇒β).  □
      </paragraph>
      <paragraph>
       Theorem 27, Theorem 28 resemble successor-state axioms in that the action a occurs outside of the belief at the left-hand side, but not at the right-hand side of the equivalence. We can use them in a similar fashion to Rule R2 to push inside the scope of B. Once that is done, regression proceeds with the antecedent and consequent in B.
      </paragraph>
      <paragraph label="Definition 29">
       The regression of a regressable formula α is defined as in Definition 23 plus the following rule:
      </paragraph>
      <list>
       <list-item label="R9.">
        {a mathematical formula}R[r,B(α⇒β)] is defined inductively on r:
       </list-item>
      </list>
      <paragraph>
       The following theorem states the correctness of regression:
      </paragraph>
      <paragraph label="Theorem 30">
       Let{a mathematical formula}Σdyn,Σbelbe a basic action theory and let α be a regressable sentence. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       The proof can be found in Appendix A.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       An example
      </section-title>
      <paragraph>
       Let us illustrate regression using the gift-giving example. More precisely, we use the fourth example query from Section 4.2:{a mathematical formula} We first regress {a mathematical formula}[unbox(5#)]∃yB(gift=y∧¬InBox(gift)∧¬Broken(gift)), and then show that the regressed sentence is satisfied by {a mathematical formula}e≫dropbox≫clink, the progression of the model of {a mathematical formula}O(Σdyn,Σbel), which we determined in Section 4.2. We do not regress by clink and dropbox here for space reasons; we will handle them in the next section by progression. After rewriting the formula to adhere to the normal form required for regression, the task is to determine{a mathematical formula} Regression then moves inside the existential and the action {a mathematical formula}unbox(5#) and we obtain{a mathematical formula} The action {a mathematical formula}unbox(5#) is then pushed inside of the belief modalities and we obtain, after minor simplifications,{a mathematical formula} Now regression proceeds inside the belief modalities with the antecedents and consequents. In particular, regressing ψ substitutes {a mathematical formula}InBox(y′) and {a mathematical formula}Broken(y′) with the right-hand sides of the successor-state axioms:{a mathematical formula} After some trivial simplifications, the final regressed formula is equivalent to{a mathematical formula} Finally we need to prove that {a mathematical formula}e≫dropbox≫clink satisfies this formula. Note that there are {a mathematical formula}w∈(e≫dropbox≫clink)3 with {a mathematical formula}w⊨InBox(5#)∧¬Broken(5#). Consider any such w. Since such worlds do exist, {an inline-figure} is true, and therefore we need to prove that {a mathematical formula}∃yB(InBox(5#)∧¬Broken(5#)⇒gift=5#∧gift=y∧¬Broken(5#)) is true as well. We substitute {a mathematical formula}5# for the existentially quantified y. Since {a mathematical formula}w⊨InBox(5#) by assumption and nothing but gift is in the box at level {a mathematical formula}(e≫dropbox≫clink)3, w also satisfies the consequent, namely {a mathematical formula}w⊨gift=5#∧(gift=y)5#y∧¬Broken(5#). Thus {a mathematical formula}e≫dropbox≫clink satisfies the regressed formula. We will finish the proof of the query in the next section where we also handle dropbox and clink.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Belief projection by progression
     </section-title>
     <paragraph>
      Another way to solve the projection problem is by progression. Progression means to update the knowledge base to account for the effects of actions. It is commonly considered necessary, particularly in long-lived systems, so that the system can move on and discard historic states. Unfortunately, progression in general requires second-order logic due to results by Lin and Reiter [6] and Vassos and Levesque [7]. Lin and Reiter showed that progression is closely related to logical forgetting: one needs to forget the obsolete values of the predicates. The syntactic way to forget a predicate in a knowledge base is to substitute it with an existentially quantified second-order variable.
     </paragraph>
     <paragraph>
      In this section, we show how beliefs can be progressed. Given a basic action theory and an action n, we aim to project the epistemic and the physical effects of n onto the initial beliefs. The result of this operation shall be a new, progressed basic action theory. At first, we extend the only-believing operator by a mechanism to forget predicates, and show that all former results carry over to that extended operator. Said extension is not full second-order logic but allows for existential quantification of predicates within only-believing for reasons we elaborate below. Then we proceed by first investigating how revision of a conditional knowledge base can be captured by only-believing in Section 6.2. This allows us to account for the epistemic effects of actions, and in Section 6.3 we then add the physical effects and obtain the progression theorem. Section 6.4 continues our running example.
     </paragraph>
     <section label="6.1">
      <section-title>
       Only-believing with forgetting
      </section-title>
      <paragraph>
       Following Lin and Reiter [6], we use logical forgetting to represent the effects of actions on the knowledge base. As mentioned above, forgetting a predicate in a knowledge base boils down to making that predicate an existentially quantified second-order variable. For the purposes of forgetting in {a mathematical formula}O{ϕ1⇒ψ1,…,ϕm⇒ψm}, what should the scope of that second-order variable be? It clearly should be quantified within O, yet its scope should encompass all {a mathematical formula}ϕi and {a mathematical formula}ψi, so that all occurrences in {a mathematical formula}ϕi,ψi refer to the same variable. Adding full support of second-order quantifiers and allowing them to appear between the O and its arguments {a mathematical formula}{ϕ1⇒ψ1,…,ϕm⇒ψm} requires a quite cumbersome semantics, though. On the other hand, full second-order logic is not even required for forgetting; existentials between O and its arguments suffice. As it permits a much simpler semantics, we parameterize the only-believing operator with a set of function and predicate symbols, which are taken to be existentially quantified inside O.
      </paragraph>
      <paragraph label="Definition 31">
       The set of well-formed formulas is the least set formed from the rules from Definition 3 and
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}OS{ϕ1⇒ψ1,…,ϕm⇒ψm} is a formula where the {a mathematical formula}ϕi and {a mathematical formula}ψi are objective formulas and {a mathematical formula}S is a finite set of object function and predicate symbols.
       </list-item>
      </list>
      <paragraph>
       Due to the relationship between existential quantification and forgetting, we read {a mathematical formula}OS{ϕ1⇒ψ1,…,ϕm⇒ψm} as “before everything about {a mathematical formula}S is forgotten, the conditionals {a mathematical formula}ϕi⇒ψi are all that is believed.”
      </paragraph>
      <paragraph>
       To characterize the semantics of existential quantification, we use the following relation to say that two worlds agree on everything except perhaps certain symbols.
      </paragraph>
      <paragraph label="Definition 32">
       For a set of object function and predicate symbols {a mathematical formula}S, we define {a mathematical formula}w≈Sw′ iff
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}w[g(n1,…,nk)]=w′[g(n1,…,nk)] for all object function symbols {a mathematical formula}g∉S;
       </list-item>
       <list-item label="•">
        {a mathematical formula}w[R(n1,…,nk)]=w′[R(n1,…,nk)] for all rigid predicate symbols {a mathematical formula}R∉S;
       </list-item>
       <list-item label="•">
        {a mathematical formula}w[F(n1,…,nk),z]=w′[F(n1,…,nk),z] for all fluent predicate symbols {a mathematical formula}F∉S and action sequences z.
       </list-item>
      </list>
      <paragraph>
       Intuitively, {a mathematical formula}w≈Sw′ means that w and {a mathematical formula}w′ agree on everything except perhaps {a mathematical formula}S. Notice that {a mathematical formula}w≈{}w′ iff {a mathematical formula}w=w′. Hence, {a mathematical formula}eS intuitively denotes the epistemic state that results from forgetting everything about {a mathematical formula}S in the original epistemic state e. For example, consider an epistemic state e with {a mathematical formula}e1={w|w⊨R∧(R≡R′)}. Then {a mathematical formula}w[R]=w[R′]=1 for all {a mathematical formula}w∈e1. Belief in R is then lost in {a mathematical formula}e{R}, while {a mathematical formula}R′ is retained: for every {a mathematical formula}w∈e1, not only {a mathematical formula}w∈(e{R})1, but there also is a {a mathematical formula}w′∈(e{R})1 which agrees with w on everything except that {a mathematical formula}w′[R]=0, so we have {a mathematical formula}(e{R})1={w|w⊨R′}.
      </paragraph>
      <paragraph label="Definition 33">
       The semantics of the new only-believing operator is defined using standard only-believing:
      </paragraph>
      <list>
       <list-item label="S11.">
        {a mathematical formula}e,w⊨OS{ϕ1⇒ψ1,…,ϕm⇒ψm}  iff  for some {a mathematical formula}e′, {a mathematical formula}e′,w⊨O{ϕ1⇒ψ1,…,ϕm⇒ψm} and {a mathematical formula}e=eS′.
       </list-item>
      </list>
      <paragraph>
       Note that extended only-believing subsumes standard only-believing, as their semantics coincide for {a mathematical formula}S={}. It is not surprising that earlier results such as the unique-model property from Corollary 20 and the regression result Theorem 30 carry over to the extended operator.
      </paragraph>
      <paragraph label="Corollary 34">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective. Then there is one unique e with{a mathematical formula}e⊨OSΓ.
      </paragraph>
      <paragraph label="Proof">
       By Corollary 20, there is a unique {a mathematical formula}e′ such that {a mathematical formula}e′⊨OΓ. By Rule S11, {a mathematical formula}eS′ is unique such that {a mathematical formula}eS′⊨OSΓ.  □
      </paragraph>
      <paragraph label="Theorem 35">
       Let{a mathematical formula}Σdyn,Σbelbe a basic action theory with{a mathematical formula}S-free{a mathematical formula}Σdynand let α be a regressable sentence. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       For the proof see Appendix A.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Revision of only-believing
      </section-title>
      <paragraph>
       Semantically, performing an action brings along a revision of the epistemic state, which promotes certain worlds over others. In this subsection we examine how the semantic revision can be matched syntactically. More precisely, we are looking for a set of conditionals {a mathematical formula}Γ⁎υ which is only-believed when Γ was only-believed before revising by υ.
      </paragraph>
      <paragraph>
       Recall that by Theorem 15, {a mathematical formula}B(α∨β⇒¬β) asserts that α is more plausible than β or both are considered impossible. We use this to define {a mathematical formula}Γα as the set of conditionals whose material implication holds up to the plausibility level of α.
      </paragraph>
      <paragraph label="Definition 36">
       For {a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}, we define {a mathematical formula}Γα={ϕ⇒ψ∈Γ|OΓ⊨B(α∨¬(ϕ⊃ψ)⇒(ϕ⊃ψ))}.
      </paragraph>
      <paragraph>
       A syntactic representation of weak revision by υ needs to reflect that the most-plausible υ-worlds are promoted to the first level. To this end we use a new dummy predicate R to partition the worlds: the R-worlds represent those which are promoted, and the ¬R-worlds represent the beliefs before the revision.
      </paragraph>
      <paragraph label="Definition 37">
       Let R be a rigid predicate symbol. Let {a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm} and υ be objective and {a mathematical formula}{R}-free. Then the weak revision of Γ by υ is{a mathematical formula}
      </paragraph>
      <paragraph>
       We now prove that the revised set of conditionals (after forgetting R) matches semantic weak revision. To begin with, we prove a few technical lemmas that will also be helpful for the strong revision theorem.
      </paragraph>
      <paragraph label="Lemma 38">
       If{a mathematical formula}⌊e|α⌋&gt;⌈e⌉, then{a mathematical formula}⌊e|α⌋=∞.
      </paragraph>
      <paragraph label="Proof">
       Suppose {a mathematical formula}⌊e|α⌋≠∞. Then {a mathematical formula}e,w⊨α for some {a mathematical formula}w∈ep and {a mathematical formula}p∈N. Since {a mathematical formula}ep⊆e⌈e⌉, {a mathematical formula}⌊e|α⌋≤⌈e⌉.  □
      </paragraph>
      <paragraph label="Lemma 39">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective, let e be such that{a mathematical formula}e⊨OΓ, and let{a mathematical formula}p∈N∪{∞}such that{a mathematical formula}p≥⌊e|α⌋. Then{a mathematical formula}⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi)≡⋀ϕ⇒ψ∈Γαwithmax⁡{⌊e|ϕ⌋,⌊e|α⌋}≥p(ϕ⊃ψ).
      </paragraph>
      <paragraph label="Proof">
       By Corollary 20 and Theorem 15, {a mathematical formula}ϕ⇒ψ∈Γα iff {a mathematical formula}⌊e|α⌋=⌊e|¬(ϕ⊃ψ)⌋=∞ or {a mathematical formula}⌊e|α⌋&lt;⌊e|¬(ϕ⊃ψ)⌋ (*).For the only-if direction, suppose {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi) and let {a mathematical formula}ϕ⇒ψ∈Γα with {a mathematical formula}max⁡{⌊e|ϕ⌋,⌊e|α⌋}≥p. Then {a mathematical formula}w∈emin⁡{p,⌈e⌉} by Rule S10. Note that {a mathematical formula}w′⊨(ϕ⊃ψ) for all {a mathematical formula}w′∈ep′ and {a mathematical formula}p′∈N with {a mathematical formula}p′≤⌊e|ϕ⌋ by Rule S10. Likewise, {a mathematical formula}w′⊨(ϕ⊃ψ) for all {a mathematical formula}w′∈ep′ and {a mathematical formula}p′∈N with {a mathematical formula}p′≤⌊e|α⌋ by (*). Hence, since {a mathematical formula}p≤max⁡{⌊e|ϕ⌋,⌊e|α⌋}, {a mathematical formula}w⊨(ϕ⊃ψ).Conversely, suppose {a mathematical formula}w⊭(ϕi⊃ψi) for some i with {a mathematical formula}⌊e|ϕi⌋≥p. Then trivially {a mathematical formula}max⁡{⌊e|ϕi⌋,⌊e|α⌋}≥p, so we only need to show that {a mathematical formula}ϕi⇒ψi∈Γα. By Rule S10, {a mathematical formula}w′⊨(ϕi⊃ψi) for all {a mathematical formula}w′∈ep′ and {a mathematical formula}p′∈N with {a mathematical formula}p′≤p. Hence {a mathematical formula}p&lt;⌊e|¬(ϕi⊃ψi)⌋. If {a mathematical formula}⌊e|α⌋≤⌈e⌉, then {a mathematical formula}⌊e|α⌋≤p&lt;⌊e|¬(ϕi⊃ψi)⌋. Otherwise, if {a mathematical formula}⌈e⌉&lt;⌊e|α⌋, then {a mathematical formula}⌈e⌉≤p&lt;⌊e|¬(ϕi⊃ψi)⌋, and by Lemma 38, {a mathematical formula}⌊e|α⌋=⌊e|¬(ϕi⊃ψi)⌋=∞. In both cases, by (*), {a mathematical formula}ϕi⇒ψi∈Γα.  □
      </paragraph>
      <paragraph label="Lemma 40">
       Let ϕ be objective and{a mathematical formula}S-free, and{a mathematical formula}w≈Sw′. Then{a mathematical formula}w⊨ϕiff{a mathematical formula}w′⊨ϕ.
      </paragraph>
      <paragraph label="Proof">
       Follows by a trivial induction on the length of ϕ.
      </paragraph>
      <paragraph label="Lemma 41">
       Let ϕ be objective and{a mathematical formula}S-free. Then{a mathematical formula}(e⁎ϕ)S=eS⁎ϕ.
      </paragraph>
      <paragraph label="Proof">
       By Lemma 40, {a mathematical formula}⌊e|ϕ⌋=⌊eS|ϕ⌋ and {a mathematical formula}(eS|ϕ)p=((e|ϕ)p)S. Thus by Definition 8 the lemma follows.  □
      </paragraph>
      <paragraph label="Theorem 42">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}and υ be objective and{a mathematical formula}S-free. Let R be the nullary rigid predicate newly introduced in{a mathematical formula}Γ⁎wυ. If{a mathematical formula}e⊨OSΓ, then{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       We show the theorem for the case {a mathematical formula}S={} first. Let {a mathematical formula}e⊨OΓ. We construct an {a mathematical formula}e′ such that {a mathematical formula}e′⊨OΓ⁎wυ and {a mathematical formula}e{R}′=e⁎wυ, which gives {a mathematical formula}e⁎wυ⊨O{R}Γ⁎wυ. If {a mathematical formula}⌊e|υ⌋=∞, we let {a mathematical formula}ep′={} for all {a mathematical formula}p∈N. Otherwise, we let {a mathematical formula}e1′=((e|υ)|R)⌊e|υ⌋ and {a mathematical formula}ep′=e1′∪(e|¬R)p−1 for {a mathematical formula}p&gt;1.First suppose {a mathematical formula}⌊e|υ⌋=∞. Then {a mathematical formula}e⁎wυ=〈{}〉. Clearly, {a mathematical formula}⌊〈{}〉|ϕ⌋=∞ for all ϕ, so {a mathematical formula}es{}⊨OΓ⁎wυ if (by Rule S10) {an inline-figure} is unsatisfiable iff {a mathematical formula}⋀ϕ⇒ψ∈Γυ(ϕ⊃ψ)∧υ∧R is unsatisfiable if (by Lemma 39) {a mathematical formula}⋀i:⌊e|ϕi⌋=∞(ϕi⊃ψi)∧υ is unsatisfiable, which holds by Rule S10 and {a mathematical formula}⌊e|υ⌋=∞.Now suppose {a mathematical formula}⌊e|υ⌋≠∞. We show that {a mathematical formula}e′⊨OΓ⁎wυ for the following plausibilities of the conditionals in {a mathematical formula}Γ⁎wυ:
       <list>
        {an inline-figure}; because by assumption {a mathematical formula}⌊e|υ⌋≠∞ and thus {a mathematical formula}e1′≠{}.{a mathematical formula}⌊e′|¬(R⊃υ)⌋=∞; because {a mathematical formula}w⊨υ for all {a mathematical formula}w∈e1′, and {a mathematical formula}w⊭R for all {a mathematical formula}w∈ep′∖e1′.{a mathematical formula}⌊e′|¬(R⊃(ϕ⊃ψ))⌋=∞ for all {a mathematical formula}ϕ⇒ψ∈Γυ; because by Lemma 39, {a mathematical formula}w⊨(ϕ⊃ψ) for all {a mathematical formula}w∈e⌊e|υ⌋⊇e1′, and {a mathematical formula}w⊭R for all {a mathematical formula}w∈ep′∖e1′.{a mathematical formula}⌊e′|(¬R∧ϕ)⌋=⌊e|ϕ⌋+1 for all {a mathematical formula}ϕ⇒ψ∈Γ; because {a mathematical formula}w⊨R for all {a mathematical formula}w∈e1′, and so for all {a mathematical formula}p∈N we have {a mathematical formula}p+1≥⌊e′|(¬R∧ϕ)⌋ iff {a mathematical formula}w⊨(¬R∧ϕ) for some {a mathematical formula}w∈ep+1′ iff {a mathematical formula}w⊨(¬R∧ϕ) for some {a mathematical formula}w∈(e|¬R)p iff (since {a mathematical formula}Γ,υ are {a mathematical formula}{R}-free and by Rule S10 and Lemma 40) {a mathematical formula}w⊨ϕ for some {a mathematical formula}w∈ep iff {a mathematical formula}p≥⌊e|ϕ⌋.Since Γ and
       </list>
       <paragraph>
        υ are {a mathematical formula}{R}-free, for each {a mathematical formula}w∈(e|υ)⌊e|υ⌋ there is a {a mathematical formula}w′∈e1′ with {a mathematical formula}w≈{R}w′ by Lemma 40 and Rule S10. Likewise, for each {a mathematical formula}w∈ep there is a {a mathematical formula}w′∈(e|¬R)p with {a mathematical formula}w≈{R}w′. Thus {a mathematical formula}e⁎wυ=e{R}′, and hence {a mathematical formula}e⁎wυ⊨O{R}Γ⁎wυ.Now let {a mathematical formula}S≠{}. Let {a mathematical formula}e⊨OSΓ and {a mathematical formula}e′⊨OΓ. By Rule S11 and Corollary 34, {a mathematical formula}e=eS′. By the case for {a mathematical formula}S={}, {a mathematical formula}e′⁎wυ⊨O{R}Γ⁎wυ. By Rule S11, {a mathematical formula}(e′⁎wυ)S⊨OS∪{R}Γ⁎wυ. By Lemma 41, {a mathematical formula}e⁎wυ⊨OS∪{R}Γ⁎wυ.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Strong revision changes the ranking of the worlds more profoundly than weak revision, and representing this change is hence more complex. Strong revision by υ promotes all υ-worlds over all ¬υ-worlds. We therefore duplicate the conditionals from Γ twice using new predicates, and require υ to be true in the first copy. The revised truth values are then set through additional conditionals based on the dummies' truth values.
      </paragraph>
      <paragraph>
       To ease the presentation, we restrict our consideration of strong revision to static formulas. They are sufficient for our purposes of progressing a basic action theories, since the initial beliefs {a mathematical formula}Σbel are static as well. Extending the below definition and theorem for non-static conditionals is straightforward.
      </paragraph>
      <paragraph label="Definition 43">
       Let {a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm} and υ be objective and static. Let {a mathematical formula}S′ be the object function and predicate symbols in Γ, and let {a mathematical formula}S″ be just as many object function and rigid predicate symbols of corresponding arity which do not occur in Γ or υ. For any formula β, let {a mathematical formula}β⁎ be the formula obtained from β by replacing each symbol from {a mathematical formula}S′ with the corresponding symbol from {a mathematical formula}S″. Let {a mathematical formula}Δ={ϕ⇒ψ∈Γυ|OΓ⊭K(ϕ⊃ψ)}. Then the strong revision of Γ by υ is defined as{a mathematical formula}
      </paragraph>
      <paragraph>
       The first and the third line account for the promoted υ-worlds in the revised epistemic state. In particular, the third line asserts that there is the right number of levels where υ holds. The material implications in the last three lines set the original predicates according to the values of the dummy predicates.
      </paragraph>
      <paragraph>
       As with weak revision, the syntactic strong revision {a mathematical formula}Γ⁎sυ matches its semantic counterpart.
      </paragraph>
      <paragraph label="Theorem 44">
       Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}and υ be objective and static. Let{a mathematical formula}Sbe a set of object function and predicate symbols, and let υ be{a mathematical formula}S-free. Let{a mathematical formula}S″be the symbols newly introduced in{a mathematical formula}Γ⁎sυ. If{a mathematical formula}e⊨OSΓ, then{a mathematical formula}
      </paragraph>
      <paragraph>
       The proof is similar to the proof of Theorem 42. It can be found in Appendix B.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Progression of only-believing
      </section-title>
      <paragraph>
       We are now ready to define the progression of a basic action theory {a mathematical formula}Σdyn,Σbel. Given an action standard name n, we first revise the theory by n's information and then apply n's effects on fluents. The revision is captured by {a mathematical formula}Σbel⁎φna where φ is from the informed-fluent axiom {a mathematical formula}□IF(a)≡φ∈Σdyn, and the type of revision corresponds to the subsort of n. (The reason for taking {a mathematical formula}φna instead of {a mathematical formula}IF(n) is to keep the belief conditionals fluent.) In this subsection we show how the physical effects of n are handled.
      </paragraph>
      <paragraph>
       For two sets of predicate symbols {a mathematical formula}F={F1,…,Fk} and {a mathematical formula}R={R1,…,Rk} of corresponding arity we denote by {a mathematical formula}αRF the formula obtained by replacing each {a mathematical formula}Fi with {a mathematical formula}Ri in α. Recall that, in the context of a basic action theory, {a mathematical formula}γF denotes the right-hand side of the successor-state axiom for a fluent F and φ is the right-hand side of the informed-fluent axiom.
      </paragraph>
      <paragraph label="Definition 45">
       Let {a mathematical formula}Σdyn,Σbel be a basic action theory over fluents {a mathematical formula}F={F1,…,Fk}, and let {a mathematical formula}R={R1,…,Rk} be rigid predicates of corresponding arity which do not otherwise occur in {a mathematical formula}Σdyn or {a mathematical formula}Σbel⁎φna. Let n be a action standard name. Then the progression of {a mathematical formula}Σbel by n is defined as{a mathematical formula}
      </paragraph>
      <paragraph>
       The intuition behind the definition is as follows. When n is executed, the beliefs are first revised by the information {a mathematical formula}φna produced by n, which leads to {a mathematical formula}Σbel⁎φna. The beliefs {a mathematical formula}(Σbel⁎φna)RF represent the same conditionals belief as {a mathematical formula}Σbel⁎φna, except that each {a mathematical formula}Fi is renamed to {a mathematical formula}Ri. Intuitively, {a mathematical formula}Ri memorizes the value of {a mathematical formula}Fi before the physical effect of n. The additional conditionals in {a mathematical formula}Σbel≫n initialize each fluent {a mathematical formula}F(x1,…,xl) with its value after doing n, that is, {a mathematical formula}γFnRaF. Notice that the progression of a basic action theory again is a basic action theory over {a mathematical formula}F, so progression can iterate.
      </paragraph>
      <paragraph>
       The following two results establish the correctness of progression. The first theorem says that, if all that is believed is a basic action theory, then after doing action n all that is believed is the progressed basic action theory:
      </paragraph>
      <paragraph label="Theorem 46">
       Let{a mathematical formula}Σdyn,Σbelbe a basic action theory. Let{a mathematical formula}S′be the symbols newly introduced by{a mathematical formula}Σbel≫n. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       The second theorem says that the same beliefs are entailed by a basic action theory after doing action n and the progression by n of that basic action theory:
      </paragraph>
      <paragraph label="Theorem 47">
       Let{a mathematical formula}Σdyn,Σbelbe a basic action theory. Let{a mathematical formula}S′be the symbols newly introduced by{a mathematical formula}Σbel≫n. Then{a mathematical formula}
      </paragraph>
      <paragraph>
       The proofs of both theorems are in Appendix B. They proceed in two steps. First, we show that {a mathematical formula}Σbel⁎φna and {a mathematical formula}(Σbel⁎φna)RF determine the same conditional beliefs modulo the substitution of {a mathematical formula}F by {a mathematical formula}R, where {a mathematical formula}R⊆S′ is the set of rigid predicates from Definition 45. Second, we see that after progressing the individual worlds in the model of {a mathematical formula}O(Σdyn,Σbel⁎φna) by n, the resulting epistemic state agrees with the model of {a mathematical formula}O(Σdyn,Σbel≫n) on everything except perhaps {a mathematical formula}R. We therefore have that, when using standard only-believing, the semantic progression and the syntactic progression agree on everything except {a mathematical formula}R. With the extended only-believing operator, the differences in {a mathematical formula}R vanish as well.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       An example
      </section-title>
      <paragraph>
       Let us proceed with the query from the gift-giving example which we investigated in Section 5.3 already. The query involves the action sequence dropbox, clink, {a mathematical formula}unbox(5#). Since dropbox is a physical action with no epistemic effect, let us take an abbreviation instead of doing it by the definitions: it is easy to see that {a mathematical formula}e≫dropbox from Section 4.2 satisfies {a mathematical formula}O(Σdyn,Σbel′) where{a mathematical formula} We focus on the progression of {a mathematical formula}O(Σdyn,Σbel′) by the weak-revision action clink. According to Definition 37, the revision {a mathematical formula}Σbel′⁎φclinka contains the conditionals
      </paragraph>
      <list>
       <list-item label="•">
        {an inline-figure};
       </list-item>
       <list-item label="•">
        {an inline-figure};
       </list-item>
       <list-item label="•">
        {an inline-figure} for each {a mathematical formula}ϕ⇒ψ∈Σbel′ such that {a mathematical formula}OΣbel′⊨B(φclinka∨¬(ϕ⊃ψ)⇒(ϕ⊃ψ));
       </list-item>
       <list-item label="•">
        {a mathematical formula}¬R∧ϕ⇒ψ for each {a mathematical formula}ϕ⇒ψ∈Σbel′.
       </list-item>
      </list>
      <paragraph>
       This amounts to{a mathematical formula}In the progression {a mathematical formula}Σbel′≫clink the fluents InBox and Broken are renamed {a mathematical formula}RInBox and {a mathematical formula}RBroken, respectively, and two conditionals are added to set InBox and Broken to its correct value:{a mathematical formula}
      </paragraph>
      <paragraph>
       Let us consider the fourth example projection problem from Section 4.2 another time:{a mathematical formula} In this section, we have determined the progression of {a mathematical formula}Σbel by dropbox and clink, and in Section 5.3 we regressed the query by {a mathematical formula}unbox(5#). Together, this projection problem can therefore be recast as the purely static entailment problem{a mathematical formula} The equivalence of both entailment problems follows from the progression and regression results of Theorem 47, Theorem 35. Let us confirm for this example that the (regressed) query indeed is a logical consequence of the (progressed) theory. In Section 4.2 we proved that {a mathematical formula}e≫dropbox≫clink satisfies the regressed query. So it suffices to show that {a mathematical formula}e≫dropbox≫clink also is the model of {a mathematical formula}O{R,RInBox,RBroken}(Σdyn,Σbel′≫clink). Following the procedure from the proof of Theorem 19, {a mathematical formula}e′⊨O(Σdyn,Σbel′≫clink) iff {a mathematical formula}e′=〈e1′,e2′,e3′,e4′〉 where{a mathematical formula}and then it is easy to verify that {a mathematical formula}e{R,RInBox,RBroken}′=e≫dropbox≫clink: the R-worlds in {a mathematical formula}e′ represent the worlds from {a mathematical formula}(e≫dropbox≫clink)1, and the ¬R-worlds represent the additional worlds in {a mathematical formula}(e≫dropbox≫clink)p. Since there is no other model by Corollary 34, the action-less entailment indeed holds.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Belief revision postulates
     </section-title>
     <paragraph>
      In this section we relate {a mathematical formula}ESB to the most well known accounts of belief change: the postulates by Alchourrón, Gärdenfors, and Makinson (AGM) for single revision [41], [42], Darwiche and Pearl's (DP) postulates for iterated revision [43], and the alternative proposal by Nayak, Pagnucco, and Peppas (NPP) [21]. We will see that the AGM postulates are satisfied and a slight weakening of the DP postulates hold. For strong revision furthermore all but the first NPP postulate are satisfied as well. The divergences from these postulate systems only concern the special case of revision by an inconsistent formula: this leads to the inconsistent epistemic state {a mathematical formula}es{}, and our semantics provides no escape from the inconsistent state once it is reached.
     </paragraph>
     <paragraph>
      We rephrase and prove the postulates in our semantic framework here, that is, with respect to an epistemic state e. The corresponding results for theory revision follow by the theorems from Section 6.2. Our translation of the postulates to {a mathematical formula}ESB is similar to Shapiro et. al's [12]. Perhaps the most notable translation is that belief expansion is modeled as material implication: {a mathematical formula}e⊨B(ϕ⊃ψ) represents that ψ is in the belief set after it is expanded with ϕ. It may also be worth noting that we phrase conditions like consistency or equivalence of objective formulas with respect to knowledge in the epistemic state, such as {a mathematical formula}e⊭K¬ϕ instead of {a mathematical formula}⊭¬ϕ, and {a mathematical formula}e⊨K(ϕ≡ψ) instead of {a mathematical formula}⊨(ϕ≡ψ). We remark that this is no effective restriction, as we prove the below theorems for arbitrary epistemic states, which particularly includes those where precisely the valid sentences are known.
     </paragraph>
     <paragraph>
      For the remainder of this section let e be an arbitrary epistemic state and ϕ, ψ, υ be objective sentences.
     </paragraph>
     <paragraph label="Theorem 48">
      The AGM postulates are satisfied:
     </paragraph>
     <list>
      <list-item>
       If{a mathematical formula}e⁎ϕ⊨Bψand{a mathematical formula}e⁎ϕ⊨B(ψ⊃υ), then{a mathematical formula}e⁎ϕ⊨Bυ.
      </list-item>
      <list-item>
       {a mathematical formula}e⁎ϕ⊨Bϕ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⁎ϕ⊨Bυ, then{a mathematical formula}e⊨B(ϕ⊃υ).
      </list-item>
      <list-item>
       If{a mathematical formula}e⊭B¬ϕand{a mathematical formula}e⊨B(ϕ⊃υ), then{a mathematical formula}e⁎ϕ⊨Bυ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⊭K¬ϕ, then{an inline-figure}.
      </list-item>
      <list-item>
       If{a mathematical formula}e⊨K(ϕ≡ψ), then{a mathematical formula}e⁎ϕ⊨Bυiff{a mathematical formula}e⁎ψ⊨Bυ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⁎(ϕ∧ψ)⊨Bυ, then{a mathematical formula}e⁎ϕ⊨B(ψ⊃υ).
      </list-item>
      <list-item>
       If{a mathematical formula}e⁎ϕ⊭B¬ψand{a mathematical formula}e⁎ϕ⊨B(ψ⊃υ), then{a mathematical formula}e⁎(ϕ∧ψ)⊨Bυ.
      </list-item>
     </list>
     <paragraph label="Proof">
      We suppose {a mathematical formula}ep≠{} for some {a mathematical formula}p∈N, for otherwise the postulates hold trivially as {a mathematical formula}(e⁎δ)p={} and thus {an inline-figure}. Since the postulates refer only to a single revision and {a mathematical formula}(e⁎wδ)1=(e⁎sδ)1 by Lemma 11, the proof does not need to distinguish between weak and strong revision.
     </paragraph>
     <list>
      <list-item label="1.">
       Follows from Property 7 of Theorem 17.
      </list-item>
      <list-item label="2.">
       If there is no ϕ-world, {a mathematical formula}(e⁎ϕ)p={} for all {a mathematical formula}p∈N; else for all {a mathematical formula}w∈(e⁎ϕ)1≠{}, {a mathematical formula}w⊨ϕ. In either case, {a mathematical formula}e⁎ϕ⊨Bϕ.
      </list-item>
      <list-item label="3.">
       Let {a mathematical formula}e⁎ϕ⊨Bυ. Suppose {a mathematical formula}e⊭B(ϕ⊃υ). Then for some {an inline-figure}, {a mathematical formula}w⊨ϕ∧¬υ. Then {a mathematical formula}w∈(e⁎ϕ)1, and therefore {a mathematical formula}e⁎ϕ⊭Bυ, which contradicts the assumption. Thus {a mathematical formula}e⊨B(ϕ⊃υ).
      </list-item>
      <list-item label="4.">
       Let {a mathematical formula}e⊭B¬ϕ and {a mathematical formula}e⊨B(ϕ⊃υ). Then for some {a mathematical formula}w∈e⌊e⌋, {a mathematical formula}w⊨ϕ, and for all {a mathematical formula}w∈e⌊e⌋, {a mathematical formula}w⊨ϕ⊃υ. Therefore {a mathematical formula}(e⁎ϕ)1⊆ep, and for all {a mathematical formula}w∈(e⁎ϕ)1, {a mathematical formula}w⊨ϕ∧υ, so {a mathematical formula}e⁎ϕ⊨Bυ.
      </list-item>
      <list-item label="5.">
       Let {a mathematical formula}e⊭K¬ϕ. Then for some {a mathematical formula}w∈e⌊e⌋, {a mathematical formula}w⊨ϕ. Hence {a mathematical formula}(e⁎ϕ)1≠{}, so {an inline-figure}.
      </list-item>
      <list-item label="6.">
       Let {a mathematical formula}e⊨K(ϕ≡ψ). Then {a mathematical formula}w⊨ϕ iff {a mathematical formula}w⊨ψ for all {a mathematical formula}p∈N and {a mathematical formula}w∈ep. Thus {a mathematical formula}e⁎ϕ=e⁎ψ.
      </list-item>
      <list-item label="7.">
       If there is no ϕ-world, {a mathematical formula}e⁎ϕ⊨B(ψ⊃υ) holds trivially. Otherwise, consider {a mathematical formula}w∈(e⁎ϕ)1 with {a mathematical formula}w⊨ψ. Then {a mathematical formula}w∈(e⁎(ϕ∧ψ))1 and by assumption, {a mathematical formula}w⊨υ. Hence {a mathematical formula}e⁎ϕ⊨B(ψ⊃υ).
      </list-item>
      <list-item label="8.">
       Let {a mathematical formula}e⁎ϕ⊭B¬ψ and {a mathematical formula}e⁎ϕ⊨B(ψ⊃υ). Then for some {a mathematical formula}w∈(e⁎ϕ)1, {a mathematical formula}w⊨ψ. Therefore {a mathematical formula}(e⁎(ϕ∧ψ))1⊆(e⁎ϕ)1, and for all {a mathematical formula}w∈(e⁎(ϕ∧ψ))1, {a mathematical formula}w⊨ψ∧(ψ⊃υ), and so {a mathematical formula}w⊨υ. Hence {a mathematical formula}(e⁎(ϕ∧ψ))⊨Bυ.  □
      </list-item>
     </list>
     <paragraph>
      A slightly restricted version of the DP postulates for iterated revision holds as well. The restriction concerns the special case of revision by an inconsistent formula. Since {a mathematical formula}ESB provides no escape from the empty epistemic state, DP2 holds in case the first revision is by an inconsistent formula only if the second revision is by an inconsistent formula as well. We hence require {a mathematical formula}e⊨K¬ϕ⊃K¬ψ in our variant of DP2. We remark that the restricted postulate is still slightly stronger than NPP4 (see below).
     </paragraph>
     <paragraph label="Theorem 49">
      The DP postulates are satisfied for a restricted second postulate:
     </paragraph>
     <list>
      <list-item>
       If{a mathematical formula}e⊨K(ψ⊃ϕ), then{a mathematical formula}(e⁎ϕ)⁎ψ⊨Bυiff{a mathematical formula}e⁎ψ⊨Bυ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⊨K(ψ⊃¬ϕ)and{a mathematical formula}e⊨K¬ϕ⊃K¬ψ, then{a mathematical formula}(e⁎ϕ)⁎ψ⊨Bυiff{a mathematical formula}e⁎ψ⊨Bυ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⁎ψ⊨Bϕ, then{a mathematical formula}(e⁎ϕ)⁎ψ⊨Bϕ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⁎ψ⊭B¬ϕ, then{a mathematical formula}(e⁎ϕ)⁎ψ⊭B¬ϕ.
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Let {a mathematical formula}e⊨K(ψ⊃ϕ). Then {a mathematical formula}(e|ψ)p⊆(e|ϕ)p for all {a mathematical formula}p∈N (*). Therefore {a mathematical formula}w∈((e⁎ϕ)⁎ψ)1 iff {a mathematical formula}⌊e⁎ϕ|ψ⌋≠∞ and {a mathematical formula}w∈(e⁎ϕ|ψ)⌊e⁎ϕ|ψ⌋ iff (by (*)) {a mathematical formula}⌊e|ψ⌋≠∞ and {a mathematical formula}w∈(e|ψ)⌊e|ψ⌋ iff {a mathematical formula}w∈(e⁎ψ)1.
       </list-item>
       <list-item label="2.">
        The proof is very similar to 1. Let {a mathematical formula}e⊨K(ψ⊃¬ϕ) and {a mathematical formula}e⊨K¬ϕ⊃K¬ψ. If {a mathematical formula}⌊e|ψ⌋=∞, then {a mathematical formula}⌊e⁎ϕ|ψ⌋=∞, and therefore {a mathematical formula}e⁎ψ=(e⁎ϕ)⁎ψ=〈{}〉, so the postulate holds. Now suppose {a mathematical formula}⌊e|ψ⌋≠∞. By the second assumption, {a mathematical formula}e⊭K¬ϕ, so {a mathematical formula}⌊e|ϕ⌋≠∞. By the first assumption, {a mathematical formula}w⊭ψ for all {a mathematical formula}w∈(e|ϕ)p for all {a mathematical formula}p∈N. Thus {a mathematical formula}(e|ϕ)p∩(e|ψ)p={} (*), so neither weak nor strong revision by ϕ affects the relative order of the ψ-worlds. Hence {a mathematical formula}w∈((e⁎ϕ)⁎ψ)1 iff {a mathematical formula}w∈(e⁎ϕ|ψ)⌊e⁎ϕ|ψ⌋ iff (by (*)) {a mathematical formula}w∈(e|ψ)⌊e|ψ⌋ iff {a mathematical formula}w∈(e⁎ψ)1.
       </list-item>
       <list-item label="3.">
        Let {a mathematical formula}e⁎ψ⊨Bϕ. If {a mathematical formula}⌊e|ϕ⌋=∞, then {a mathematical formula}e⁎ϕ=(e⁎ϕ)⁎ψ=〈{}〉, so the postulate holds. If {a mathematical formula}⌊e|ψ⌋=∞, then {a mathematical formula}⌊e⁎ϕ|ψ⌋=∞, and therefore {a mathematical formula}(e⁎ϕ)⁎ψ=〈{}〉, so the postulate holds. Now suppose {a mathematical formula}⌊e|ϕ⌋≠∞ and {a mathematical formula}⌊e|ψ⌋≠∞. By assumption, {a mathematical formula}(e|ψ)⌊e|ψ⌋⊆(e|ϕ)⌊e|ψ⌋. Therefore the most-plausible ψ-worlds remain most plausible after weak or strong revision by ϕ, so {a mathematical formula}(e⁎ϕ|ψ)⌊e⁎ϕ|ψ⌋⊆(e⁎ϕ|ϕ)⌊e⁎ϕ|ψ⌋. Thus, if {a mathematical formula}w∈((e⁎ϕ)⁎ψ)1, then {a mathematical formula}w∈(e⁎ϕ|ψ)⌊e⁎ϕ|ψ⌋, and {a mathematical formula}w∈(e⁎ϕ|ϕ)⌊e⁎ϕ|ψ⌋, so {a mathematical formula}w⊨ϕ.
       </list-item>
       <list-item label="4.">
        Let {a mathematical formula}e⁎ψ⊭B¬ϕ. Then {a mathematical formula}⌊e⁎ψ|ϕ⌋≠∞, and so {a mathematical formula}⌊e|ϕ⌋≠∞ and {a mathematical formula}⌊e|ψ⌋≠∞. By assumption, for some {a mathematical formula}(e|ψ∧ϕ)⌊e|ψ⌋≠{}. The ϕ-worlds among the most-plausible ψ-worlds remain most plausible after weak or strong revision by ϕ, so {a mathematical formula}(e⁎ϕ|ψ∧ϕ)⌊e⁎ϕ|ψ⌋≠{}. Hence there is some {a mathematical formula}w∈(e⁎ϕ|ψ∧ϕ)⌊e⁎ϕ|ψ⌋, and therefore also {a mathematical formula}w∈(e⁎ϕ|ψ)⌊e⁎ϕ|ψ⌋. Thus {a mathematical formula}w⊨ϕ for some {a mathematical formula}w∈((e⁎ϕ)⁎ψ)1.  □
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      The Nayak–Pagnucco–Peppas postulates hold with two exceptions: for one thing, the absurdity postulate NPP1 does not hold; for another, the conjunction postulate NPP3 only holds for strong revision. The absurdity postulate NPP1 facilitates recovery from an inconsistent state: it says that after revising an inconsistent state by ϕ, ϕ shall be all that is believed. In our language, the absurdity postulate could be written as
     </paragraph>
     <list>
      <list-item label="1.">
       If {an inline-figure}, then {an inline-figure}.
      </list-item>
     </list>
     <paragraph>
      Only-believing ϕ alone intuitively does not suffice, though, because we would lose any indefeasible knowledge we might have had already before reaching the inconsistent e (such as the dynamic axioms of a basic action theory).
     </paragraph>
     <paragraph label="Theorem 50">
      The NPP postulates except for NPP1 and except for NPP3 for weak revision hold:
     </paragraph>
     <list>
      <list-item>
       AGM1–6 hold.
      </list-item>
      <list-item>
       If{a mathematical formula}e⊭K¬(ϕ∧ψ)then{a mathematical formula}(e⁎sϕ)⁎sψ⊨Bυiff{a mathematical formula}e⁎s(ϕ∧ψ)⊨Bυ.
      </list-item>
      <list-item>
       If{a mathematical formula}e⊨K(ψ⊃¬ϕ)and{a mathematical formula}e⊭K¬ϕ, then{a mathematical formula}(e⁎ϕ)⁎ψ⊨Bυiff{a mathematical formula}e⁎ψ⊨Bυ.
      </list-item>
     </list>
     <paragraph label="Proof">
      We only need to prove NPP3, as we have shown the AGM1–6 in Theorem 48 already and NPP4 is a special case of DP2. Suppose {a mathematical formula}w∈((e⁎sϕ)⁎sψ)1. Then {a mathematical formula}w∈(e⁎sϕ)⌊e⁎sϕ|ψ⌋. By assumption, {a mathematical formula}⌊e⁎sϕ|ψ⌋&lt;⌊e⁎sϕ|¬ϕ⌋, so {a mathematical formula}w⊨ϕ and, since the revision by ϕ did not affect the relative ordering of the {a mathematical formula}(ϕ∧ψ)-worlds, also {a mathematical formula}w∈e⌊e|ϕ∧ψ⌋. Thus {a mathematical formula}w∈(e⁎sϕ∧ψ)1. Conversely, suppose {a mathematical formula}w∈(e⁎sϕ∧ψ)1. Then {a mathematical formula}w∈e⌊e|ϕ∧ψ⌋. Therefore {a mathematical formula}w∈(e⁎sϕ)⌊(e⁎sϕ)|ψ⌋, and thus {a mathematical formula}w∈((e⁎sϕ)⁎sψ)1.  □
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proof of belief projection by regression
     </section-title>
     <paragraph>
      In this appendix we prove the regression results. We begin with Theorem 24, Theorem 30 from Section 5. Then we generalize Theorem 30 for the extended only-believing operator to show Theorem 35.
     </paragraph>
     <paragraph>
      Proving Theorem 24, Theorem 30 follows a scheme similar to the knowledge regression proof sketched in [24]. Namely, we show that every world and epistemic state can be converted to one that adheres to the dynamic axioms {a mathematical formula}Σdyn without changing its initial truth values. In Lemma 60 we show that an epistemic state and a world satisfy a regressed sentence iff their {a mathematical formula}Σdyn-compliant counterparts satisfy the non-regressed sentence. The regression theorem is then an easy consequence.
     </paragraph>
     <paragraph>
      For the rest of this section, let {a mathematical formula}Σdyn,Σbel be a basic action theory over fluents {a mathematical formula}F. Recall that {a mathematical formula}Σdyn contains the successor state axioms {a mathematical formula}□[a]F(x1,…,xk)≡γF for {a mathematical formula}F∈F, and the informed-fluent axiom {a mathematical formula}□IF(a)≡φ.
     </paragraph>
     <paragraph label="Definition 51">
      For a world w, {a mathematical formula}wΣdyn is a world such that {a mathematical formula}wΣdyn≈F∪{IF}w and
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}wΣdyn[F(n1,…,nk),〈〉]=w[F(n1,…,nk),〈〉] for all {a mathematical formula}F∈F;
      </list-item>
      <list-item label="•">
       {a mathematical formula}wΣdyn[F(n1,…,nk),z⋅n]=1 iff {a mathematical formula}wΣdyn≫z⊨γFn1…nknx1…xka for all {a mathematical formula}F∈F, action sequences z, and actions n;
      </list-item>
      <list-item label="•">
       {a mathematical formula}wΣdyn[IF(n),z]=1 iff {a mathematical formula}wΣdyn≫z⊨φna for all action sequences z.
      </list-item>
     </list>
     <paragraph label="Lemma 52">
      {a mathematical formula}wΣdynis uniquely defined.
     </paragraph>
     <paragraph label="Proof">
      Intuitively, once all values except for IF are fixed after z, the truth of {a mathematical formula}γF and φ after z is uniquely determined as they are fluent formulas, and thus by definition also the value of F after {a mathematical formula}z⋅n and of IF after z are uniquely determined. The formal proof is by straightforward induction on z and subinduction on the length of {a mathematical formula}γF and φ.  □
     </paragraph>
     <paragraph label="Lemma 53">
      {a mathematical formula}wΣdyn⊨Σdyn.
     </paragraph>
     <paragraph label="Proof">
      By definition, {a mathematical formula}wΣdyn[F(n1,…,nk),z⋅n]=1 iff {a mathematical formula}wΣdyn≫z⊨γFn1…nknx1…xka, so {a mathematical formula}wΣdyn⊨□[a]F(x1,…,xk)≡γF for all {a mathematical formula}F∈F. Analogously, {a mathematical formula}wΣdyn⊨□IF(a)≡φ. Hence {a mathematical formula}wΣdyn⊨Σdyn.  □
     </paragraph>
     <paragraph label="Lemma 54">
      If{a mathematical formula}w⊨Σdyn, then{a mathematical formula}wΣdyn=w.
     </paragraph>
     <paragraph label="Proof">
      Suppose {a mathematical formula}w⊨Σdyn. Then {a mathematical formula}w⊨□[a]F(x1,…,xn)≡γF and {a mathematical formula}w⊨□IF(a)≡φ. Thus, w satisfies the conditions from Definition 51: {a mathematical formula}w[F(n1,…,nk),z⋅n]=1 iff {a mathematical formula}(w≫z⋅n)[F(n1,…,nk),〈〉]=1 iff {a mathematical formula}w≫z⊨γFn1…nknx1…xka for all {a mathematical formula}F∈F; analogously, {a mathematical formula}w[IF(n),z]=1 iff {a mathematical formula}(w≫z)[IF(n),〈〉]=1 iff {a mathematical formula}w≫z⊨φna. By Lemma 52{a mathematical formula}wΣdyn is unique, so {a mathematical formula}wΣdyn=w.  □
     </paragraph>
     <paragraph label="Lemma 55">
      Let ϕ be a fluent sentence. Then{a mathematical formula}w⊨ϕiff{a mathematical formula}wΣdyn⊨ϕ.
     </paragraph>
     <paragraph label="Proof">
      By an easy induction on the length of ϕ since {a mathematical formula}w,wΣdyn agree on all initial values except perhaps for IF.  □
     </paragraph>
     <paragraph label="Lemma 56">
      If{a mathematical formula}e⊨OΣbel, then{a mathematical formula}eΣdyn⊨O(Σdyn,Σbel).
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}Σbel={ϕ1⇒ψ1,…,ϕm⇒ψm} and {a mathematical formula}e⊨OΣbel. We show that {a mathematical formula}eΣdyn⊨O(Σdyn,Σbel). Note that by Lemma 55, {a mathematical formula}⌊e|ϕi⌋=⌊eΣdyn|ϕi⌋ (*). Suppose {a mathematical formula}w∈(eΣdyn)p. Then there is some {a mathematical formula}w′∈ep such that {a mathematical formula}wΣdyn′=w, and {a mathematical formula}w′⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi) iff (by Lemma 53, Lemma 55 and (*)) {a mathematical formula}w⊨Σdyn∧⋀i:⌊eΣdyn|ϕi⌋≥p(ϕi⊃ψi). Conversely, suppose {a mathematical formula}w⊨Σdyn∧⋀i:⌊eΣdyn|ϕi⌋≥p(ϕi⊃ψi). Then {a mathematical formula}w∈ep by Rule S10 and (*). By Lemma 54, {a mathematical formula}w=wΣdyn∈(eΣdyn)p.  □
     </paragraph>
     <paragraph>
      For induction proofs about regression we introduce the following non-standard measure. Intuitively, {a mathematical formula}‖α‖ measures the length of the regressed formula {a mathematical formula}R[α] plus how many “calls” to the regression operator it takes to determine {a mathematical formula}R[α] (not counting Rule R8).
     </paragraph>
     <paragraph label="Definition 57">
      Let α be a regressable formula and {a mathematical formula}k≥0. We define the measure {a mathematical formula}‖α‖ with respect to a basic action theory with dynamic axioms {a mathematical formula}Σdyn as
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]R(t1′,…,tl′)‖=1 for rigid R;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]F(t1′,…,tl′)‖={1if k=01+‖[t1]…[tk−1]γF‖if k&gt;0for fluentF∈F;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]IF(t)‖=1+‖[t1]…[tk]φ‖;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk](t1′=t2′)‖=1;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]¬α‖=1+‖[t1]…[tk]α‖;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk](α∨β)‖=1+‖[t1]…[tk]α‖+‖[t1]…[tk]β‖;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]∃xα‖=1+‖[t1]…[tk]α‖;
      </list-item>
      <list-item label="•">
       {a mathematical formula}‖[t1]…[tk]B(α⇒β)‖={1+‖(α⊃β)‖if k=01+‖[t1]…[tk−1]σ‖if k&gt;0 where σ is the right-hand side of Theorem 27 or 28 depending on the sort of {a mathematical formula}tk.
      </list-item>
     </list>
     <paragraph>
      Observe that {a mathematical formula}‖[t1]…[tk]α‖ reflects the regression operator {a mathematical formula}R[〈t1,…,tk〉,α] from Definition 23, Definition 29. For example, {a mathematical formula}‖[t]F(t′)‖=1+‖γF‖ corresponds to {a mathematical formula}R[[t]F(t′)]=R[γFt′txa]; similarly for the other cases. This makes {a mathematical formula}‖⋅‖ very useful for induction proofs involving regression: the base cases are {a mathematical formula}‖[t1]…[tk]R(t1′,…,tl′)‖ for rigid R, {a mathematical formula}‖F(t1′,…,tl′)‖ for fluent {a mathematical formula}F∈F, and {a mathematical formula}‖[t1]…[tk](t=t′)‖, whose regression is trivial; all other cases are proved by induction.
     </paragraph>
     <paragraph>
      We first need to show that {a mathematical formula}‖⋅‖ is a well-defined function from the regressable formulas to the natural numbers. Intuitively this is true because the right-hand sides of {a mathematical formula}‖⋅‖ for fluent atoms and beliefs eliminate an action or push it inside the belief, respectively, and the right-hand side for IF mentions no IF itself. Given the construction of {a mathematical formula}‖⋅‖ it then follows immediately that the measure for expressions on the left-hand side of the equations in Definition 57 is always bigger than the measure of expressions on the right-hand side.
     </paragraph>
     <paragraph label="Lemma 58">
      {a mathematical formula}‖⋅‖is a well-defined function from the regressable formulas to the natural numbers.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}|α|B be the nesting depth of B operators: {a mathematical formula}|R(t1,…,tk)|B=|F(t1,…,tk)|B=|(t=t′)|B=0 for rigid R and fluent F; {a mathematical formula}|¬α|B=|∃xα|B=|[t]α|B=|α|B; {a mathematical formula}|(α∨β)|B=max⁡{|α|B,|β|B}; and {a mathematical formula}|B(α⇒β)|B=1+max⁡{|α|B,|β|B}.Let {a mathematical formula}|α|A be as follows: {a mathematical formula}|R(t1,…,tk)|A=|F(t1,…,tk)|A=|(t=t′)|A=0 for rigid R and fluent F; {a mathematical formula}|¬α|A=|∃xα|A=|α|A; {a mathematical formula}|(α∨β)|A=|B(α⇒β)|A=max⁡{|α|A,|β|A}; and {a mathematical formula}|[t]α|A=2|α|B+|α|A. Note that for objective ϕ, {a mathematical formula}|ϕ|A is just the number of nested action operators in ϕ. In subjective formulas every action is additionally penalized with {a mathematical formula}|⋅|B.First we show that {a mathematical formula}|[t1]…[tk]B(α⇒β)|A&gt;|[t1]…[tk−1]σ|A for {a mathematical formula}k&gt;0 where σ is the right-hand side of Theorem 27 or 28 (*). Let {a mathematical formula}|B(α⇒β)|B=n. Then {a mathematical formula}|[t1]…[tk]B(α⇒β)|A=k⋅2n+max⁡{|α|A,|β|A}. We also have that {a mathematical formula}|σ|B=n. Hence {a mathematical formula}|[t1]…[tk−1]σ|A=(k−1)⋅2n+|σ|A. It is immediate from Theorem 27, Theorem 28 that {a mathematical formula}|σ|A=max⁡{|[tk]α|A,|[tk]β|A}. Since {a mathematical formula}|α|B≤n−1 and {a mathematical formula}|β|B≤n−1, we have {a mathematical formula}max⁡{|[tk]α|A,|[tk]β|A}≤2n−1+max⁡{|α|A,|β|A}. Thus {a mathematical formula}|[t1]…[tk−1]σ|A≤(k−1)⋅2n+2n−1+max⁡{|α|A,|β|A}. Since {a mathematical formula}k⋅2n&gt;(k−1)⋅2n+2n−1, (*) holds.Now we prove the lemma by induction on {a mathematical formula}|α|A. For the base case, consider regressable α with {a mathematical formula}|α|A=0. We show that {a mathematical formula}‖α‖ is well-defined by subinduction on the length of α, where we take the length of {a mathematical formula}IF(t) to be the length of φ plus 1 (which is well-behaved because φ contains no IF), and the length of {a mathematical formula}B(α⇒β) to be the length of {a mathematical formula}(α⊃β) plus 1. The subinduction base cases {a mathematical formula}‖R(t1′,…,tl′)‖=1 for rigid R, {a mathematical formula}‖F(t1′,…,tl′)‖=1 for fluent {a mathematical formula}F∈F, and {a mathematical formula}‖(t=t′)‖=1 are obviously well-defined. For the subinduction steps, {a mathematical formula}‖IF(t)‖ is well-defined iff {a mathematical formula}‖φ‖ is well-defined, {a mathematical formula}‖¬α‖ is well-defined iff {a mathematical formula}‖α‖ is well-defined, {a mathematical formula}‖(α∨β)‖ is well-defined if {a mathematical formula}‖α‖ and {a mathematical formula}‖β‖ are well-defined, {a mathematical formula}‖∃xα‖ is well-defined iff {a mathematical formula}‖α‖ is well-defined, {a mathematical formula}‖B(α⇒β)‖ is well-defined iff {a mathematical formula}‖(α⊃β)‖ is well-defined, all of which is the case by subinduction.For the induction step consider α with {a mathematical formula}|α|A=m&gt;0 and suppose that {a mathematical formula}‖β‖ is well defined for all regressable β with {a mathematical formula}|β|A&lt;m. We show that {a mathematical formula}‖α‖ is well-defined by a subinduction in the same vein as in the main base case. The first base case {a mathematical formula}‖[t1]…[tm]F(t1′,…,tl′)‖ for fluent {a mathematical formula}F∈F is well-defined iff {a mathematical formula}‖[t1]…[tm−1]γF‖ is well-defined, which holds by induction since {a mathematical formula}γF is fluent and thus mentions neither actions, beliefs, nor IF, so {a mathematical formula}|[t1]…[tm−1]γF|A=m−1. The other base cases {a mathematical formula}‖[t1]…[tm]R(t1′,…,tl′)‖=1 for rigid R and {a mathematical formula}‖[t1]…[tm](t=t′)‖=1 are immediate. For the first subinduction step, {a mathematical formula}‖[t1]…[tm]IF(t)‖ is well-defined iff {a mathematical formula}‖[t1]…[tm]φ‖ is well-defined, which holds by subinduction. For disjunction with {a mathematical formula}|[t1]…[tk](α∨β)|A=m, {a mathematical formula}‖[t1]…[tk](α∨β)‖ is well-defined iff {a mathematical formula}‖[t1]…[tk]α‖ and {a mathematical formula}‖[t1]…[tk]β‖ are well-defined, which for α holds by induction in case {a mathematical formula}|[t1]…[tk]α|A&lt;m and otherwise by subinduction, and likewise for β. The subinduction steps {a mathematical formula}‖[t1]…[tk]¬α‖ and {a mathematical formula}‖[t1]…[tk]∃xα‖ trivially hold by subinduction. For the subinduction step for beliefs, let {a mathematical formula}|[t1]…[tk]B(α⇒β)|A=m; then {a mathematical formula}‖[t1]…[tk]B(α⇒β)‖ is well-defined iff {a mathematical formula}‖[t1]…[tk−1]σ‖ is well-defined where σ is the right-hand side of Theorem 27 or 28 depending on the sort of {a mathematical formula}tk, which holds by induction since {a mathematical formula}|[t1]…[tk]B(α⇒β)|A&gt;|[t1]…[tk−1]σ|A by (*).  □
     </paragraph>
     <paragraph>
      Since {a mathematical formula}‖α‖ is a natural number for every regressable α, we can prove properties of α by induction over {a mathematical formula}‖α‖, as we will do in the next two lemmas. For example, for the induction step for a fluent atom {a mathematical formula}[t1]…[tk]F(t1′,…,tl′) after {a mathematical formula}k≥1 actions, we have {a mathematical formula}R[[t1]…[tk]F(t1′,…,tl′)]=R[[t1]…[tk−1]γFt1′…tl′tkx1…xla] by the definition of {a mathematical formula}R[], and then use the induction assumption since clearly {a mathematical formula}‖[t1]…[tk]F(t1′,…,tl′)‖&gt;‖[t1]…[tk−1]γF‖ by Definition 57.
     </paragraph>
     <paragraph label="Lemma 59">
      Let α be a regressable sentence. Then{a mathematical formula}R[αnx]=R[α]nx.
     </paragraph>
     <paragraph label="Proof">
      By induction on {a mathematical formula}‖α‖. For the base case let {a mathematical formula}‖α‖=1. For rigid R and {a mathematical formula}k≥0, {a mathematical formula}R[([t1]…[tk]R(t1′,…,tl′))nx]=R(t1′,…,tl′)nx=R[[t1]…[tk]R(t1′,…,tl′)]nx; analogously for {a mathematical formula}[t1]…[tk](t=t′). For fluent {a mathematical formula}F∈F, {a mathematical formula}R[F(t1′,…,tl′)nx]=F(t1′,…,tl′)nx=R[F(t1′,…,tl′)]nx.For the induction step let {a mathematical formula}‖α‖=m&gt;1 and suppose the lemma holds for all β with {a mathematical formula}‖β‖&lt;m. For fluent {a mathematical formula}F∈F and {a mathematical formula}k≥1, {a mathematical formula}R[([t1]…[tk]F(t1′,…,tl′))nx]=(by Rules R2 and R8)R[[t1nx]…[tk−1nx]γFt1′nx…tl′tknxx1…xla] = {a mathematical formula}(sinceγF]does not mentionxdue to rectification){a mathematical formula}R[([t1]…[tk−1]γFt1′…tl′tkx1…xla)nx] = {a mathematical formula}(by induction since‖[t1]…[tk−1]γF‖&lt;m){a mathematical formula}R[[t1]…[tk−1]γFt1′…tl′tkx1…xla]nx = {a mathematical formula}(by Rules R2 and R8){a mathematical formula}R[[t1]…[tk]F(t1′,…,tl′)]nx. Similarly for the induction step for IF, {a mathematical formula}R[([t1]…[tk]IF(t))nx] = {a mathematical formula}R[[t1nx]…[tknx]IF(tnx)] = {a mathematical formula}(by Rules R3 and R8){a mathematical formula}R[[t1nx]…[tknx]φtnxa] = {a mathematical formula}(sincexdoes not occur inφ){a mathematical formula}R[([t1]…[tk]φta)nx] = {a mathematical formula}(by induction since‖[t1]…[tk]φ‖&lt;m){a mathematical formula}R[[t1]…[tk]φta]nx = {a mathematical formula}(by Rules R3 and R8){a mathematical formula}R[IF(t)]nx.For a quantifier, {a mathematical formula}R[([t1]…[tk]∃x′α)nx] = {a mathematical formula}(sincex′,xare distinct due to rectification and by Rules R7 and R8)∃x′R[[t1nx]…[tknx]αnx] = {a mathematical formula}(by induction since‖[t1]…[tk]α‖&lt;m){a mathematical formula}∃x′R[[t1]…[tk]α]nx = {a mathematical formula}(sincex′,xare distinct and byRules R8 and R7){a mathematical formula}R[[t1]…[tk]∃x′α]nx. We omit the similar induction steps for {a mathematical formula}[t1]…[tk]¬α and {a mathematical formula}[t1]…[tk](α∨β).For beliefs after no actions, {a mathematical formula}R[B(α⇒β)nx]=R[B(αnx⇒βnx)]=(by Rule R9){a mathematical formula}B(R[αnx]⇒R[βnx])=(by induction since‖α‖&lt;mand‖β‖&lt;m){a mathematical formula}B(R[α]nx⇒R[β]nx)=B(R[α]⇒R[β])nx(by Rule R9)R[B(α⇒β)]nx. Finally, for beliefs after {a mathematical formula}k≥1 actions, {a mathematical formula}R[([t1]…[tk]B(α⇒β))nx]=(by Rules R9 and R8,whereσis the right-hand side of Theorem 27 or 28depending on the sort oftk){a mathematical formula}R[[t1nx]…[tk−1nx]σntknxxa] = {a mathematical formula}R[([t1]…[tk−1]σtka)nx] = (by induction since {a mathematical formula}‖[t1]…[tk−1]σ‖&lt;m) {a mathematical formula}R[[t1]…[tk−1]σtka]nx = (by Rules R9 and R8) {a mathematical formula}R[[t1]…[tk]B(α⇒β)]nx.  □
     </paragraph>
     <paragraph label="Lemma 60">
      Let α be a regressable sentence. Then{a mathematical formula}e,w⊨R[α]iff{a mathematical formula}eΣdyn,wΣdyn⊨α.
     </paragraph>
     <paragraph label="Proof">
      By induction on {a mathematical formula}‖α‖. For the base case let {a mathematical formula}‖α‖=1. For rigid R and {a mathematical formula}k≥0, {a mathematical formula}wΣdyn⊨[t1]…[tk]R(t1′,…,tl′) iff {a mathematical formula}wΣdyn[R(n1′,…,nl′)]=1 where {a mathematical formula}ni′=wΣdyn(ti′) iff {a mathematical formula}w[R(n1′,…,nl′)]=1 where {a mathematical formula}ni′=w(ti′) iff {a mathematical formula}w⊨R(t1′,…,tl′) iff (by Rule R1) {a mathematical formula}w⊨R[R(t1′,…,tl′)]; similarly for {a mathematical formula}[t1]…[tk](t=t′). For fluent {a mathematical formula}F∈F, {a mathematical formula}wΣdyn⊨F(t1′,…,tl′) iff {a mathematical formula}wΣdyn[F(n1′,…,nl′),〈〉]=1 where {a mathematical formula}ni′=wΣdyn(ti′) iff (by definition of {a mathematical formula}wΣdyn) {a mathematical formula}w[F(n1′,…,nl′),〈〉]=1 where {a mathematical formula}ni′=w(ti′) iff {a mathematical formula}w⊨F(t1′,…,tl′) iff (by Rule R2) {a mathematical formula}w⊨R[F(t1′,…,tl′)].For the induction step let {a mathematical formula}‖α‖=m&gt;1 and suppose the lemma holds for all β with {a mathematical formula}‖β‖&lt;m. For fluent {a mathematical formula}F∈F and {a mathematical formula}k≥1, {a mathematical formula}wΣdyn⊨[t1]…[tk]F(t1′,…,tl′) iff (by Rule S7) {a mathematical formula}(wΣdyn≫n1≫…≫nk)[F(n1′,…,nl′),〈〉]=1 where {a mathematical formula}ni=wΣdyn(ti) and {a mathematical formula}ni′=wΣdyn(ti′) iff (by definition of {a mathematical formula}wΣdyn and Rule S7) {a mathematical formula}wΣdyn⊨[t1]…[tk−1]γFt1′…tl′tkx1…xla iff (by induction since {a mathematical formula}‖[t1]…[tk−1]γF‖&lt;m) {a mathematical formula}w⊨R[[t1]…[tk−1]γFt1′…tl′tkx1…xla] iff (by Rules R2 and R8) {a mathematical formula}w⊨R[[t1]…[tk]F(t1′,…,tl′)]. Similarly for IF, {a mathematical formula}wΣdyn⊨[t1]…[tk]IF(t) iff (by Rule S7) {a mathematical formula}(wΣdyn≫n1≫…≫nk)[IF(n),〈〉]=1 where {a mathematical formula}ni=wΣdyn(ti) and {a mathematical formula}n=wΣdyn(t) iff (by definition of {a mathematical formula}wΣdyn and Rule S7) {a mathematical formula}wΣdyn⊨[t1]…[tk]φta iff (by induction since {a mathematical formula}‖[t1]…[tk]φ‖&lt;m) {a mathematical formula}w⊨R[[t1]…[tk]φta] iff (by Rules R3 and R8) {a mathematical formula}w⊨R[[t1]…[tk]IF(t)].For a quantifier, {a mathematical formula}eΣdyn,wΣdyn⊨[t1]…[tk]∃xα iff (by Rules S6 and S7) {a mathematical formula}eΣdyn,wΣdyn⊨([t1]…[tk]α)nx for some n iff (by induction since {a mathematical formula}‖[t1]…[tk]α‖&lt;m) {a mathematical formula}e,w⊨R[([t1]…[tk]α)nx] for some n iff (by Lemma 59) {a mathematical formula}e,w⊨R[[t1]…[tk]α]nx for some n iff (by Rule S6) {a mathematical formula}e,w⊨∃xR[[t1]…[tk]α] iff (by Rules R7 and R8) {a mathematical formula}e,w⊨R[[t1]…[tk]∃xα]. We omit the similar induction steps for {a mathematical formula}[t1]…[tk]¬α and {a mathematical formula}[t1]…[tk](α∨β).For beliefs after no actions, {a mathematical formula}eΣdyn⊨B(α⇒β) iff (by Theorem 13) {a mathematical formula}⌊eΣdyn|α⌋=∞ or {a mathematical formula}eΣdyn,w⊨(α⊃β) for all {a mathematical formula}w∈(eΣdyn)⌊eΣdyn|α⌋ iff (by definition of {a mathematical formula}eΣdyn) {a mathematical formula}⌊eΣdyn|α⌋=∞ or {a mathematical formula}eΣdyn,wΣdyn⊨(α⊃β) for all {a mathematical formula}w∈e⌊eΣdyn|α⌋ iff (by induction since {a mathematical formula}‖(α⊃β)‖&lt;m) {a mathematical formula}⌊e|R[α]⌋=∞ or {a mathematical formula}e,w⊨R[(α⊃β)] for all {a mathematical formula}w∈e⌊e|R[α]⌋ iff (by Rules R5 and R6) {a mathematical formula}⌊e|R[α]⌋=∞ or {a mathematical formula}e,w⊨(R[α]⊃R[β]) for all {a mathematical formula}w∈e⌊e|R[α]⌋ iff (by Theorem 13) {a mathematical formula}e⊨B(R[α]⇒R[β]) iff (by Rule R9) {a mathematical formula}e⊨R[B(α⇒β)]. Finally, for beliefs after {a mathematical formula}k≥1 actions, {a mathematical formula}eΣdyn,wΣdyn⊨[t1]…[tk]B(α⇒β) iff (by Rule S7 and, depending on the sort of {a mathematical formula}tk, Theorem 27 or 28, where σ is that theorem's right-hand side) {a mathematical formula}eΣdyn,wΣdyn⊨[t1]…[tk−1]σnka where {a mathematical formula}nk=wΣdyn(tk) iff (since by assumption action terms in formulas to be regressed only have variables or names as arguments) {a mathematical formula}eΣdyn,wΣdyn⊨[t1]…[tk−1]σtka iff (by induction since {a mathematical formula}‖[t1]…[tk−1]σ‖&lt;m) {a mathematical formula}e,w⊨R[[t1]…[tk−1]σtka] iff (by Rules R9 and R8) {a mathematical formula}e,w⊨R[[t1]…[tk]B(α⇒β)].  □
     </paragraph>
     <paragraph label="Theorem 24">
      Let ϕ be a fluent sentence and ψ be an objective regressable sentence. Then{a mathematical formula}Σdyn∧ϕ⊨ψiff{a mathematical formula}ϕ⊨R[ψ].
     </paragraph>
     <paragraph label="Proof">
      For the only-if direction suppose {a mathematical formula}Σdyn∧ϕ⊨ψ and {a mathematical formula}w⊨ϕ. By Lemma 55 and the assumption, {a mathematical formula}wΣdyn⊨ψ, and by Lemma 60, {a mathematical formula}w⊨R[ψ]. Conversely, suppose {a mathematical formula}ϕ⊨R[ψ] and {a mathematical formula}w⊨Σdyn∧ϕ. Then {a mathematical formula}w⊨R[ψ] by assumption, and thus {a mathematical formula}wΣdyn⊨ψ by Lemma 60. By Lemma 54, {a mathematical formula}wΣdyn=w, so {a mathematical formula}w⊨ψ.  □
     </paragraph>
     <paragraph label="Theorem 30">
      Let α be a regressable sentence. Then{a mathematical formula}O(Σdyn,Σbel)⊨αiff{a mathematical formula}OΣbel⊨R[α].
     </paragraph>
     <paragraph label="Proof">
      For the only-if direction suppose {a mathematical formula}O(Σdyn,Σbel)⊨α and {a mathematical formula}e⊨OΣbel. By Lemma 56, {a mathematical formula}eΣdyn⊨O(Σdyn,Σbel). By assumption, {a mathematical formula}eΣdyn⊨α. By Lemma 60, {a mathematical formula}e⊨R[α]. Conversely, suppose {a mathematical formula}OΣbel⊨R[α] and {a mathematical formula}e⊨O(Σdyn,Σbel). Let {a mathematical formula}e′⊨OΣbel, which exists by Theorem 19. By assumption, {a mathematical formula}e′⊨R[α]. By Lemma 60, {a mathematical formula}eΣdyn′⊨α. By Lemma 56, {a mathematical formula}eΣdyn′⊨O(Σdyn,Σbel). By Theorem 18, {a mathematical formula}eΣdyn′=e, so {a mathematical formula}e⊨α.  □
     </paragraph>
     <paragraph>
      To generalize the regression result for the extended only-believing operator from Section 6.1, suppose {a mathematical formula}S is a finite set of object function and predicate symbols and that {a mathematical formula}Σdyn is {a mathematical formula}S-free from now on. It suffices to generalize Lemma 56, as the other lemmas involved do not refer to only-believing.
     </paragraph>
     <paragraph label="Lemma 61">
      If{a mathematical formula}e⊨OSΣbel, then{a mathematical formula}eΣdyn⊨OS(Σdyn,Σbel).
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}e⊨OΣbel. By Lemma 56, {a mathematical formula}eΣdyn⊨O(Σdyn,Σbel). Then {a mathematical formula}eS⊨OSΣbel, and {a mathematical formula}(eΣdyn)S⊨OS(Σdyn,Σbel). We need to show that {a mathematical formula}(eS)Σdyn=(eΣdyn)S. Let {a mathematical formula}w∈((eS)Σdyn)p. Then for some {a mathematical formula}w′∈(eS)p, {a mathematical formula}wΣdyn′=w. Then for some {a mathematical formula}w″∈ep, {a mathematical formula}w″≈Sw′, and therefore {a mathematical formula}wΣdyn″≈SwΣdyn′=w. Since {a mathematical formula}wΣdyn″∈(eΣdyn)p, {a mathematical formula}w∈((eΣdyn)S)p. Conversely, let {a mathematical formula}w∈((eΣdyn)S)p. Then for some {a mathematical formula}w′∈(eΣdyn)p, {a mathematical formula}w′≈Sw. Then {a mathematical formula}w′∈ep, and so {a mathematical formula}w∈(eS)p. By Lemma 53, {a mathematical formula}w′⊨Σdyn. Thus by Lemma 40 and since {a mathematical formula}Σdyn is {a mathematical formula}S-free, {a mathematical formula}w⊨Σdyn. By Lemma 54, {a mathematical formula}w=wΣdyn, so {a mathematical formula}w∈((eS)Σdyn)p.  □
     </paragraph>
     <paragraph label="Theorem 35">
      Let α be a regressable sentence. Then{a mathematical formula}OS(Σdyn,Σbel)⊨αiff{a mathematical formula}OSΣbel⊨R[α].
     </paragraph>
     <paragraph label="Proof">
      Proceeds by the exact same argument as the proof of Theorem 30, with O replaced by {a mathematical formula}OS, Lemma 56 replaced by Lemma 61, and Theorem 19, Theorem 18 replaced by Corollary 34.  □
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Proof of belief projection by progression
     </section-title>
     <paragraph>
      In this appendix we first prove Theorem 44, which claims correctness of our strong revision of a conditional knowledge base. Then we proceed with the actual progression results, Theorem 46, Theorem 47.
     </paragraph>
     <paragraph label="Definition 62">
      We say ⁎ is a symbol involution when it maps object function symbols to object function symbols and predicate symbols to predicate symbols of corresponding arities, and {a mathematical formula}S=S⁎⁎ for all object function or predicate symbols S. We denote by {a mathematical formula}α⁎ the formula obtained from α by simultaneously replacing each object function or predicate symbol S with {a mathematical formula}S⁎. For a world w, we define the world {a mathematical formula}w⁎ such that
     </paragraph>
     <list>
      <list-item label="•">
       for all object function symbols g, {a mathematical formula}w⁎[g⁎(n1,…,nk)]=w[g(n1,…,nk)];
      </list-item>
      <list-item label="•">
       for all rigid predicate symbols R and action sequences {a mathematical formula}z≠〈〉,
      </list-item>
      <list-item label="•">
       for all fluent predicate symbols F and action sequences z,
      </list-item>
     </list>
     <paragraph>
      We use symbol involutions to rename the symbols of a formula: when {a mathematical formula}S′ contains all symbols of α, and ⁎ maps each of them to a new symbol from a set {a mathematical formula}S″ disjoint with {a mathematical formula}S′, then {a mathematical formula}α⁎ is just the result of replacing every symbol from {a mathematical formula}S′ with the corresponding symbol from {a mathematical formula}S″.
     </paragraph>
     <paragraph label="Lemma 63">
      Let ⁎ be a symbol involution. Then{a mathematical formula}w=w⁎⁎,{a mathematical formula}W=W⁎⁎, and{a mathematical formula}e=e⁎⁎.
     </paragraph>
     <paragraph label="Proof">
      For {a mathematical formula}w=w⁎⁎, the only non-trivial cases are when a fluent F is mapped to rigid {a mathematical formula}F⁎ or the other way around. If R is rigid and {a mathematical formula}R⁎ is fluent, then {a mathematical formula}w⁎⁎[R(n1,…,nk)]=w⁎⁎[R⁎⁎(n1,…,nk)]=w⁎[R⁎(n1,…,nk),〈〉]=w[R(n1,…,nk)]. If F is fluent and {a mathematical formula}F⁎ is rigid, then {a mathematical formula}w⁎⁎[F(n1,…,nk),〈〉]=w⁎⁎[F⁎⁎(n1,…,nk),〈〉]=w⁎[F⁎(n1,…,nk)]=w[F(n1,…,nk),〈〉], and {a mathematical formula}w⁎⁎[F(n1,…,nk),z]=w⁎⁎[F⁎⁎(n1,…,nk),z]=w⁎[F⁎(n1,…,nk),z]=w[F(n1,…,nk),z] for all {a mathematical formula}z≠〈〉. Thus {a mathematical formula}w=w⁎⁎. {a mathematical formula}W=W⁎⁎ and {a mathematical formula}e=e⁎⁎ then follow immediately from the definition.  □
     </paragraph>
     <paragraph label="Lemma 64">
      Let ϕ be objective static and let ⁎ be a symbol involution. Then{a mathematical formula}w⊨ϕiff{a mathematical formula}w⁎⊨ϕ⁎.
     </paragraph>
     <paragraph label="Proof">
      By induction on the length of ϕ. We show the base case only for fluent predicate symbols F with rigid image {a mathematical formula}F⁎ (the other cases are analogous): {a mathematical formula}w⊨F(t1,…,tk) iff {a mathematical formula}w[F(n1,…,nk),〈〉]=1 where {a mathematical formula}ni=w(ti) iff {a mathematical formula}w⁎[F⁎(n1,…,nk)]=1 where {a mathematical formula}ni=w⁎(ti⁎) iff {a mathematical formula}w⁎⊨(F(t1,…,tk))⁎. The induction steps for ¬ϕ, {a mathematical formula}(ϕ∨β), and {a mathematical formula}∃xϕ are trivial.  □
     </paragraph>
     <paragraph label="Lemma 65">
      Let ϕ be objective static and let ⁎ be a symbol involution. Then{a mathematical formula}{w|w⊨ϕ}⁎={w|w⊨ϕ⁎}.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}w⁎∈{w′|w′⊨ϕ}⁎. Then {a mathematical formula}w⊨ϕ, and by Lemma 64, {a mathematical formula}w⁎⊨ϕ⁎, so {a mathematical formula}w⁎∈{w′|w′⊨ϕ⁎}. Conversely, let {a mathematical formula}w∈{w′|w′⊨ϕ⁎}. Then {a mathematical formula}w⊨ϕ⁎. By Lemma 64, {a mathematical formula}w⁎⁎⊨ϕ, and by Lemma 63, {a mathematical formula}w=w⁎⁎∈{w′|w′⊨ϕ}⁎.  □
     </paragraph>
     <paragraph label="Lemma 66">
      Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}be objective and static, and let ⁎ be a symbol involution. Then{a mathematical formula}e⊨OΓiff{a mathematical formula}e⁎⊨OΓ⁎.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}e⊨OΓ and {a mathematical formula}e′⊨OΓ⁎. Then {a mathematical formula}ep={w|w⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi)}, and {a mathematical formula}ep′={w′|w′⊨⋀i:⌊e′|ϕi⁎⌋≥p(ϕi⁎⊃ψi⁎)} by Rule S10. We show by induction on p that {a mathematical formula}ep⁎=ep′, and {a mathematical formula}⌊e|ϕi⌋&gt;p iff {a mathematical formula}⌊e′|ϕi⁎⌋&gt;p. For {a mathematical formula}p=1, this follows from Lemma 65, Lemma 64, respectively. For {a mathematical formula}p&gt;1, by induction {a mathematical formula}⌊e|ϕi⌋≥p iff {a mathematical formula}⌊e′|ϕi⁎⌋≥p. Thus, just like in the base case, {a mathematical formula}ep⁎=ep′ by Lemma 65, and {a mathematical formula}⌊e|ϕi⌋&gt;p iff {a mathematical formula}⌊e′|ϕi⁎⌋&gt;p by Lemma 64. Thus {a mathematical formula}e⁎=e′. The only-if direction of the lemma thus holds. Conversely, the if direction holds because ⁎ is an involution: if {a mathematical formula}e⁎⊨OΓ⁎ for some e, then {a mathematical formula}e⁎⁎⊨OΓ⁎⁎ by the only-if direction, and since {a mathematical formula}e⁎⁎=e by Lemma 63 and {a mathematical formula}OΓ⁎⁎=OΓ, {a mathematical formula}e⊨OΓ.  □
     </paragraph>
     <paragraph label="Lemma 67">
      Let{a mathematical formula}ϕ1,ϕ2be objective sentences over object function and predicate symbols{a mathematical formula}S1,S2and let{a mathematical formula}S1,S2be disjoint. Suppose{a mathematical formula}w1⊨ϕ1,{a mathematical formula}w2⊨ϕ2. Then there is some w such that{a mathematical formula}w⊨ϕ1∧ϕ2and{a mathematical formula}w≈S2w1and{a mathematical formula}w≈S1w2.
     </paragraph>
     <paragraph label="Proof">
      Since {a mathematical formula}S1 and {a mathematical formula}S2 are disjoint, there clearly is a w with {a mathematical formula}w≈S2w1 and {a mathematical formula}w≈S1w2. By a simple induction on {a mathematical formula}ϕ1, {a mathematical formula}w⊨ϕ1 because {a mathematical formula}ϕ1 does not mention any symbol from {a mathematical formula}S2. Analogously, {a mathematical formula}w⊨ϕ2.  □
     </paragraph>
     <paragraph label="Theorem 44">
      Let{a mathematical formula}Γ={ϕ1⇒ψ1,…,ϕm⇒ψm}and υ be objective and static. Let{a mathematical formula}Sbe a set of object function and predicate symbols, and let υ be{a mathematical formula}S-free. Let{a mathematical formula}S″be the symbols newly introduced in{a mathematical formula}Γ⁎sυ. If{a mathematical formula}e⊨OSΓ, then{a mathematical formula}e⁎sυ⊨OS∪S″Γ⁎sυ.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}S′ be the object function and predicate symbols that occur in Γ and ⁎ be the symbol involution that maps each symbol from {a mathematical formula}S′ to the corresponding symbol from {a mathematical formula}S″. Recall that {a mathematical formula}Δ={ϕ⇒ψ∈Γυ|OΓ⊭K(ϕ⊃ψ)}. Then {a mathematical formula}Γ⁎sυ=Γυ′∪Γ¬υ′∪Δ′∪Λ1∪Λ2∪Λ3, where{a mathematical formula} We show the theorem for the case {a mathematical formula}S={} first. Let {a mathematical formula}e⊨OΓ. We show that {a mathematical formula}e⁎sυ⊨OS″Γ⁎sυ.First suppose {a mathematical formula}⌊e|υ⌋=∞. Then {a mathematical formula}e⁎sυ=〈{}〉. Clearly, {a mathematical formula}⌊〈{}〉|ϕ⌋=∞ for all ϕ, so {a mathematical formula}es{}⊨OΓ⁎sυ if (by Rule S10) {an inline-figure} is unsatisfiable. By Rule S10 and {a mathematical formula}⌊e|υ⌋=∞, {a mathematical formula}⋀i:⌊e|ϕ⌋=∞(ϕ⊃ψ)∧υ is unsatisfiable, and by Lemma 39, {a mathematical formula}⋀ϕ⇒ψ∈Γυ(ϕ⊃ψ)∧υ is unsatisfiable, too, and by Lemma 64, {a mathematical formula}⋀ϕ⇒ψ∈Γυ(ϕ⁎⊃ψ⁎)⊨¬υ⁎. Hence, the formula mentioned before is indeed inconsistent.Now suppose {a mathematical formula}⌊e|υ⌋≠∞. To show {a mathematical formula}e⁎sυ⊨OS″Γ⁎sυ we construct a model of {a mathematical formula}OΓ⁎sυ and show that forgetting {a mathematical formula}S″ in this epistemic state yields {a mathematical formula}e⁎sυ. The proof proceeds in three steps. Step 1 is to show {a mathematical formula}e′⊨OΓυ′∪Γ¬υ′∪Δ′ where{a mathematical formula} Step 2 is to show {a mathematical formula}(e′|λ)⊨OΓ⁎sυ, where {a mathematical formula}λ=⋀ϕ⇒ψ∈Λ1′∪Λ2′∪Λ3′(ϕ⊃ψ). Step 3 is to prove {a mathematical formula}(e′|λ)S″=e⁎sυ.Step 1. We now prove that {a mathematical formula}e′⊨OΠ where {a mathematical formula}Π=Γυ′∪Γ¬υ′∪Δ′ for the following plausibilities of the conditionals in Π:
      <list>
       {a mathematical formula}⌊e′|ϕ⁎⌋=max⁡{⌊e|υ⌋,⌊e|ϕ⌋}−⌊e|υ⌋+1 for all {a mathematical formula}ϕ⇒ψ∈Γυ; because for all {a mathematical formula}p∈N with {a mathematical formula}p≥⌊e|υ⌋ we have {a mathematical formula}p≥⌊e|ϕ⌋ iff {a mathematical formula}w⊨ϕ for some {a mathematical formula}w∈ep iff (by Lemma 64) {a mathematical formula}w⊨ϕ⁎ for some {a mathematical formula}w∈ep⁎ iff (by Rule S10 and Lemma 67) {a mathematical formula}w⊨ϕ⁎∧υ for some {a mathematical formula}w∈ep⁎ iff {a mathematical formula}w⊨ϕ⁎ for some {a mathematical formula}w∈ep−⌊e|υ⌋+1′ iff {a mathematical formula}p−⌊e|υ⌋+1≥⌊e′|ϕ⁎⌋.{a mathematical formula}⌊e′|ϕ⁎∧¬υ⌋=max⁡{⌊e|¬υ⌋,⌊e|ϕ⌋}+⌈e⌉−⌊e|υ⌋−⌊e|¬υ⌋+2 for all {a mathematical formula}ϕ⇒ψ∈Γ¬υ; because, very similarly to the above, for all {a mathematical formula}p∈N with {a mathematical formula}p≥⌊e|¬υ⌋ we have {a mathematical formula}p≥⌊e|ϕ⌋ iff {a mathematical formula}w⊨ϕ for some {a mathematical formula}w∈ep iff (by Lemma 64) {a mathematical formula}w⊨ϕ⁎ for some {a mathematical formula}w∈ep⁎ iff (by Rule S10 and Lemma 67) {a mathematical formula}w⊨ϕ⁎∧¬υ for some {a mathematical formula}w∈ep⁎ iff (since {a mathematical formula}w⊨υ for all {a mathematical formula}w∈ep′′ and {a mathematical formula}p′≤⌈e⌉−⌊e|υ⌋+1) {a mathematical formula}w⊨ϕ⁎∧¬υ for some {a mathematical formula}w∈ep−⌊e|¬υ⌋+1+⌈e⌉−⌊e|υ⌋+1′ iff {a mathematical formula}p+⌈e⌉−⌊e|υ⌋−⌊e|¬υ⌋+2≥⌊e′|ϕ⁎∧¬υ⌋.{an inline-figure}; for the following reason. If {a mathematical formula}Δ={}, then {a mathematical formula}⌊e|υ⌋=⌈e⌉, and since {a mathematical formula}⌊e|υ⌋≠∞, {an inline-figure}. Now suppose {a mathematical formula}ϕ⇒ψ∈Δ. Then {a mathematical formula}⌊e|¬(ϕ⊃ψ)⌋≠∞, and by Lemma 38, {a mathematical formula}⌊e|¬(ϕ⊃ψ)⌋≤⌈e⌉. Moreover, {a mathematical formula}w⊨(ϕ⊃ψ) for all {a mathematical formula}w∈e⌊e|ϕ⌋, so {a mathematical formula}⌊e|¬(ϕ⊃ψ)⌋≥⌊e|ϕ⌋+1. In particular, there is some {a mathematical formula}ϕ⇒ψ∈Δ with {a mathematical formula}⌊e|ϕ⌋=⌈e⌉−1, for otherwise {a mathematical formula}e⌈e⌉−1=e⌈e⌉ by Rule S10; hence {a mathematical formula}⌊e|¬(ϕ⊃ψ)⌋=⌈e⌉. By Lemma 64 and since {a mathematical formula}w⊭¬υ for all {a mathematical formula}w∈ep′ and {a mathematical formula}p≤⌈e⌉−⌊e|υ⌋+1, the equality follows.First consider
      </list>
      <paragraph>
       {a mathematical formula}p≤⌈e⌉−⌊e|υ⌋+1. Then {a mathematical formula}w∈ep′ iff {a mathematical formula}w∈(e⁎|υ)p+⌊e|υ⌋−1 iff (by Rule S10 and Lemma 64) {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p+⌊e|υ⌋−1(ϕi⁎⊃ψi⁎)∧υ iff (by Lemma 39) {a mathematical formula}w⊨⋀ϕ⇒ψ∈Γυ with max⁡{⌊e|υ⌋,⌊e|ϕ⌋}≥p+⌊e|υ⌋−1(ϕ⁎⊃ψ⁎)∧υ iff (since {a mathematical formula}⊨υ⊃(ϕ⁎∧¬υ⊃ψ⁎) as well as {a mathematical formula}⊨υ≡((¬(ϕ⁎⊃ψ⁎)∨¬υ)⊃υ) and by the above plausibilities)
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}w⊨⋀ϕ⇒ψ∈Γυ and ⌊e′|ϕ⁎⌋≥p(ϕ⁎⊃ψ⁎)∧⋀ϕ⇒ψ∈Γ¬υ and ⌊e′|ϕ⁎∧¬υ⌋≥p(ϕ⁎∧¬υ⊃ψ⁎)∧
       </list-item>
       <list-item>
        {an inline-figure} iff
       </list-item>
      </list>
      <paragraph>
       {a mathematical formula}w⊨⋀ϕ⇒ψ∈Π with ⌊e′|ϕ⌋≥p(ϕ⊃ψ).Now consider {a mathematical formula}p&gt;⌈e⌉−⌊e|υ⌋+1. Then {a mathematical formula}w∈ep′ iff {a mathematical formula}w∈(e⁎|υ)⌈e⌉ or {a mathematical formula}w∈(e⁎|¬υ)p−⌈e⌉+⌊e|υ⌋+⌊e|¬υ⌋−2 iff (by Lemma 64) {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋=∞(ϕi⁎⊃ψi⁎)∧υ or {a mathematical formula}w⊨⋀⌊e|ϕi⌋≥p−⌈e⌉+⌊e|υ⌋+⌊e|¬υ⌋−2(ϕi⁎⊃ψi⁎)∧¬υ iff (by Lemma 39 and by the above plausibilities)
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}w⊨⋀ϕ⇒ψ∈Γ¬υ and ⌊e′|ϕ⁎⌋=∞(ϕ⁎⊃ψ⁎)∧υ or w⊨⋀ϕ⇒ψ∈Γ¬υ and ⌊e′|ϕ⁎∧¬υ⌋≥p(ϕ⁎⊃ψ⁎)∧¬υ iff
       </list-item>
       <list-item>
        {a mathematical formula}w⊨⋀ϕ⇒ψ∈Γ¬υ and ⌊e′|ϕ⁎⌋=∞(ϕ⁎⊃ψ⁎)∧⋀ϕ⇒ψ∈Γ¬υ and ⌊e′|ϕ⁎∧¬υ⌋≥p(ϕ⁎∧¬υ⊃ψ⁎) iff
       </list-item>
      </list>
      <paragraph>
       {a mathematical formula}w⊨⋀ϕ⇒ψ∈Π with ⌊e′|ϕ⌋≥p(ϕ⊃ψ). Therefore {a mathematical formula}e⊨OΠ and Step 1 is completed.Step 2. The second step of the proof is to show {a mathematical formula}(e′|λ)⊨OΓ⁎sυ. The conditionals added in {a mathematical formula}Γ⁎sυ over Π are those from {a mathematical formula}Λ1′∪Λ2′∪Λ3′, which simply assert knowledge of λ as they have unsatisfiable consequents. Having shown {a mathematical formula}e′⊨OΠ in Step 1, it is immediate from Rule S10 that {a mathematical formula}(e′|λ)⊨OΓ⁎sυ if {a mathematical formula}⌊e′|τ⌋=⌊(e′|λ)|τ⌋ for the antecedents {a mathematical formula}τ∈{ϕ⁎,ϕ⁎∧¬υ,(ϕ⁎∧ψ⁎)∨¬υ} of the conditionals in Π. Clearly, {a mathematical formula}⌊e′|τ⌋≤⌊(e′|λ)|τ⌋. To show the converse, we let {a mathematical formula}w∈ep′ be arbitrary and show that there is some {a mathematical formula}w′∈(e′|λ)p such that {a mathematical formula}w′⊨τ iff {a mathematical formula}w⊨τ. First suppose {a mathematical formula}w⊨¬υ∧υ⁎. Since {a mathematical formula}w⊨¬υ, by definition of {a mathematical formula}e′, {a mathematical formula}⌊e|¬υ⌋≠∞. Hence {a mathematical formula}⋀ϕ⇒ψ∈Γ¬υ(ϕ⊃ψ)∧¬υ is satisfiable by Lemma 39. By Lemma 67 there is some {a mathematical formula}w′ with {a mathematical formula}w′≈S′w with {a mathematical formula}w′⊨⋀ϕ⇒ψ∈Γ¬υ((¬υ∧υ⁎)⊃(ϕ⊃ψ))∧¬υ∧υ⁎, so {a mathematical formula}w′⊨λ. Since {a mathematical formula}w′⊨υ iff {a mathematical formula}w⊨υ and by Lemma 40 we have that for all {a mathematical formula}ϕ⇒ψ∈Π, {a mathematical formula}w′⊨ϕ iff {a mathematical formula}w⊨ϕ as well as {a mathematical formula}w′⊨ψ iff {a mathematical formula}w⊨ψ, so {a mathematical formula}w′∈ep′ by Rule S10. Therefore {a mathematical formula}w′∈(e′|λ)p, and {a mathematical formula}w′⊨τ iff {a mathematical formula}w⊨τ. The case for {a mathematical formula}w⊨υ∧¬υ⁎ is analogous. Now suppose {a mathematical formula}w⊨υ≡υ⁎. By Lemma 64, {a mathematical formula}⋀ϕ⇒ψ∈Γ(±ϕ∧±ψ)∧±υ is satisfiable where ±β stands for β if {a mathematical formula}w⊨β⁎ and for ¬β otherwise. By Lemma 67 there is some {a mathematical formula}w′ with {a mathematical formula}w≈S′w′ with {a mathematical formula}w′⊨⋀ϕ⇒ψ∈Γ(±ϕ∧±ψ)∧±υ. Since {a mathematical formula}w′⊨υ iff {a mathematical formula}w⊨υ and by Lemma 40 we have that for all {a mathematical formula}ϕ⇒ψ∈Π, {a mathematical formula}w′⊨ϕ iff {a mathematical formula}w⊨ϕ as well as {a mathematical formula}w′⊨ψ iff {a mathematical formula}w⊨ψ, so {a mathematical formula}w′∈ep′ by Rule S10. Therefore {a mathematical formula}w′∈(e′|λ)p, and {a mathematical formula}w′⊨τ iff {a mathematical formula}w⊨τ.Step 3. Lastly, we need to show that {a mathematical formula}(e′|λ)S″=e⁎sυ. Let {a mathematical formula}w∈((e′|λ)S″)p. Then there is some {a mathematical formula}w′∈(e′|λ)p with {a mathematical formula}w≈S″w′. Thus {a mathematical formula}w′⊨⋀ϕ⇒ψ∈Γ⁎sυ with ⌊e′|ϕ⌋≥p(ϕ⊃ψ). First suppose {a mathematical formula}p≤⌈e⌉−⌊e|υ⌋+1. Then {a mathematical formula}w⊨υ. If {a mathematical formula}w′⊨υ≡υ⁎, then by Lemma 40 and {a mathematical formula}Λ3, {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p+⌊e|υ⌋−1(ϕi⊃ψi)∧υ, and thus {a mathematical formula}w∈(e|υ)p+⌊e|υ⌋−1=(e⁎sυ)p. Otherwise, {a mathematical formula}w′⊨υ∧¬υ⁎, and then by Lemma 40 and {a mathematical formula}Λ1, {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥⌊e|υ⌋(ϕi⊃ψi)∧υ, and thus {a mathematical formula}w∈(e|υ)⌊e|υ⌋⊆(e|υ)p+⌊e|υ⌋−1=(e⁎sυ)p. Now suppose {a mathematical formula}p&gt;⌈e⌉−⌊e|υ⌋+1. The cases for {a mathematical formula}w′⊨υ≡υ⁎ and {a mathematical formula}w′⊨υ∧¬υ⁎ are analogous. If {a mathematical formula}w′⊨¬υ∧υ⁎, then by Lemma 40 and {a mathematical formula}Λ2, {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥⌊e|¬υ⌋(ϕi⊃ψi)∧¬υ, and thus {a mathematical formula}w∈(e|¬υ)⌊e|¬υ⌋⊆(e|¬υ)p−⌈e⌉+⌊e|υ⌋+⌊e|¬υ⌋−2⊆(e⁎sυ)p. For the converse direction, let {a mathematical formula}w′∈(e⁎sυ)p. Since ⁎ swaps the (initial) values of {a mathematical formula}S′ and {a mathematical formula}S″, there clearly is a w such that {a mathematical formula}w≈S″w′ and {a mathematical formula}w⁎=w. Thus {a mathematical formula}w⊨υ iff {a mathematical formula}w⁎⊨υ, and therefore {a mathematical formula}w∈ep′. For all {a mathematical formula}ϕ⇒ψ∈Γ, {a mathematical formula}w⊨ϕ iff (by Lemma 64) {a mathematical formula}w⁎⊨ϕ⁎ iff {a mathematical formula}w⊨ϕ⁎, and likewise for ψ. Thus {a mathematical formula}w⊨λ, and hence {a mathematical formula}w∈(e′|λ)p. As {a mathematical formula}w≈S″w′, we have {a mathematical formula}w′∈((e′|λ)S″)p.Now let {a mathematical formula}S≠{}. Let {a mathematical formula}e⊨OSΓ and {a mathematical formula}e′⊨OΓ. By Rule S11 and Corollary 34, {a mathematical formula}e=eS′. By the case for {a mathematical formula}S={}, {a mathematical formula}e′⁎sυ⊨OS″Γ⁎sυ. By Rule S11, {a mathematical formula}(e′⁎sυ)S⊨OS∪S″Γ⁎sυ. By Lemma 41, {a mathematical formula}e⁎sυ⊨OS∪S″Γ⁎sυ.  □
      </paragraph>
     </paragraph>
     <paragraph>
      In the rest of this appendix we prove the correctness of progression, that is, Theorem 46, Theorem 47. We use the following assumptions throughout the rest of the appendix.
     </paragraph>
     <list>
      <list-item label="•">
       Let {a mathematical formula}Σbel,Σdyn be a basic action theory over fluents {a mathematical formula}F={F1,…,Fl}, and let n be an action standard name. Recall that {a mathematical formula}Σdyn contains the successor state axioms {a mathematical formula}□[a]F(x1,…,xk)≡γF for {a mathematical formula}F∈F, and the informed-fluent axiom {a mathematical formula}□IF(a)≡φ.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}S′ be the symbols newly introduced in {a mathematical formula}Σbel≫n, which is partitioned into two subsets: {a mathematical formula}R={R1,…,Rl}⊆S′ contains the rigid predicates for the physical progression as in Definition 45; {a mathematical formula}S′∖R contains the rigid symbols introduced by the revision as in Definition 37 or 43.
      </list-item>
      <list-item label="•">
       Let ⁎ be the symbol involution that maps {a mathematical formula}Fi to {a mathematical formula}Ri and leaves the rest unchanged.
      </list-item>
     </list>
     <paragraph label="Definition 68">
      For a world w and an action n, {a mathematical formula}wn is a world such that {a mathematical formula}wn≈F(w≫n) and
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}wn[F(n1,…,nk),〈〉]=1 iff {a mathematical formula}wn⊨(γFn1…nknx1…xka)⁎ for all {a mathematical formula}F∈F;
      </list-item>
      <list-item label="•">
       {a mathematical formula}wn[F(n1,…,nk),z]=w[F(n1,…,nk),z] for all {a mathematical formula}F∈F and action sequences {a mathematical formula}z≠〈〉.
      </list-item>
     </list>
     <paragraph>
      Intuitively, {a mathematical formula}wn sets the initial values of every fluent {a mathematical formula}F∈F to the its value after n when the values before n are memorized in {a mathematical formula}R: {a mathematical formula}wn⊨F(n1,…,nk) iff {a mathematical formula}wn⊨(γFn1…nknx1…xka)⁎, where ⁎ replaces all fluents in {a mathematical formula}γF with the corresponding rigid predicates from {a mathematical formula}R.
     </paragraph>
     <paragraph label="Lemma 69">
      {a mathematical formula}wnis uniquely defined.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}w′≈F(w≫n) be such that for every {a mathematical formula}F∈F, {a mathematical formula}w′[F(n1,…,nk),〈〉]=1 iff {a mathematical formula}w≫n⊨(γFn1…nknx1…xka)⁎, and moreover {a mathematical formula}w′[F(n1,…,nk),z]=w[F(n1,…,nk),z] for all {a mathematical formula}z≠〈〉. Clearly such a {a mathematical formula}w′ exists and is uniquely defined. By Lemma 40 and since {a mathematical formula}γF⁎ is {a mathematical formula}F-free, {a mathematical formula}w′⊨(γFn1…nknx1…xka)⁎ iff {a mathematical formula}w≫n⊨(γFn1…nknx1…xka)⁎. Thus {a mathematical formula}w′=wn.  □
     </paragraph>
     <paragraph label="Lemma 70">
      Let ϕ be fluent. Then{a mathematical formula}w⊨ϕ⁎iff{a mathematical formula}wn⊨ϕ⁎.
     </paragraph>
     <paragraph label="Proof">
      Since ϕ is fluent and by definition of ⁎, {a mathematical formula}ϕ⁎ mentions only rigid predicates. By Lemma 69, {a mathematical formula}wn is uniquely defined, and since w and {a mathematical formula}wn agree on all rigids, a simple induction on the length of ϕ shows that the lemma holds.  □
     </paragraph>
     <paragraph label="Lemma 71">
      If{a mathematical formula}e⊨O(Σbel⁎φna)⁎, then{a mathematical formula}en⊨OΣbel≫n.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}(Σbel⁎φna)⁎={ϕ1⇒ψ1,…,ϕm⇒ψm} and {a mathematical formula}e⊨O(Σbel⁎φna)⁎. We show that {a mathematical formula}en⊨OΣbel≫n for the same plausibilities and plausibility ∞ for the added conditionals. We first show that {a mathematical formula}⌊e|ϕi⌋=⌊en|ϕi⌋ for all i and {a mathematical formula}⌊en|ϕ⌋=∞ for the newly added conditionals {a mathematical formula}ϕ⇒ψ∈(Σbel≫n)∖(Σbel⁎φna). If {a mathematical formula}p&lt;⌊e|ϕi⌋, then {a mathematical formula}w⊭ϕi for all {a mathematical formula}w∈ep, and by Lemma 70, {a mathematical formula}w⊭ϕi for all {a mathematical formula}w∈epn, so {a mathematical formula}p&lt;⌊en|ϕi⌋. Analogously, if {a mathematical formula}p≥⌊e|ϕi⌋, then {a mathematical formula}p≥⌊en|ϕi⌋. Thus {a mathematical formula}⌊e|ϕi⌋=⌊e|ϕi⌋. All other conditionals from {a mathematical formula}Σbel≫n are of the form {an inline-figure} for some {a mathematical formula}F∈F, and by definition of {a mathematical formula}wn, {a mathematical formula}⌊en|¬(F(x1,…,xk)≡(γFn1…nknx1…xka)⁎)⌋=∞.Now we prove {a mathematical formula}w∈epn iff {an inline-figure}, that is, {a mathematical formula}en satisfies Rule S10. For the only-if direction suppose {a mathematical formula}w′∈epn. Then for some {a mathematical formula}w∈ep, {a mathematical formula}wn=w′. By Rule S10 for e we have {a mathematical formula}w⊨⋀i:⌊e|ϕi⌋≥p(ϕi⊃ψi). Since {a mathematical formula}w′=wn and by {a mathematical formula}⌊e|ϕi⌋=⌊en|ϕi⌋ and Lemma 70, {a mathematical formula}w′⊨⋀i:⌊en|ϕi⌋≥p(ϕi⊃ψi), and by of {a mathematical formula}wn also {a mathematical formula}w′⊨F(x1,…,xk)≡(γFn1…nknx1…xka)⁎ for every {a mathematical formula}F∈F. Thus the right-hand side holds. Conversely, suppose {a mathematical formula}w′∉epn. If there is some w with {a mathematical formula}wn=w′, then {a mathematical formula}w∉ep, and hence by {a mathematical formula}⌊e|ϕi⌋=⌊en|ϕi⌋, {a mathematical formula}w′⊭⋀i:⌊ep|ϕi⌋≥p(ϕi⊃ψi). Otherwise, for all w, {a mathematical formula}wn≠w′, and hence {a mathematical formula}w′⊭F(x1,…,xk)≡(γFn1…nknx1…xka)⁎ for some {a mathematical formula}F∈F. In either case the right-hand side is false.  □
     </paragraph>
     <paragraph label="Lemma 72">
      {a mathematical formula}(wΣdyn≫n)≈R((w⁎)n)Σdyn.
     </paragraph>
     <paragraph label="Proof">
      The cases for object function symbols and rigid predicate symbols {a mathematical formula}R∉R are trivial as they are left unchanged by the involved Definition 9, Definition 51, Definition 62, Definition 68. For {a mathematical formula}F∈F and {a mathematical formula}z=〈〉, {a mathematical formula}(wΣdyn≫n)[F(n1,…,nk),〈〉]=1 iff {a mathematical formula}wΣdyn[F(n1,…,nk),n]=1 iff {a mathematical formula}wΣdyn⊨γFn1…nknx1…xka iff (by Lemma 55) {a mathematical formula}w⊨γFn1…nknx1…xka iff (by Lemma 64) {a mathematical formula}w⁎⊨(γFn1…nknx1…xka)⁎ iff {a mathematical formula}(w⁎)n[F(n1,…,nk),〈〉]=1 iff {a mathematical formula}((w⁎)n)Σdyn[F(n1,…,nk),〈〉]=1. The cases for {a mathematical formula}F∈F with {a mathematical formula}z≠〈〉 and for IF follow from the definition of {a mathematical formula}wΣdyn and φ, {a mathematical formula}γF being {a mathematical formula}R-free and fluent. Finally, {a mathematical formula}F∉F∪{IF} follows because both {a mathematical formula}w≫n and {a mathematical formula}wn progress F by n.  □
     </paragraph>
     <paragraph label="Lemma 73">
      Let{a mathematical formula}e⊨O(Σdyn,Σbel⁎φna)and{a mathematical formula}e′⊨O(Σdyn,Σbel≫n). Then for all{a mathematical formula}p∈N,{a mathematical formula}(ep≫n)=(eR′)p.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}e″⊨OΣbel⁎φna, which exists by Theorem 19. By Lemma 56, {a mathematical formula}eΣdyn″⊨O(Σdyn,Σbel⁎φna), and by Theorem 18, {a mathematical formula}e=eΣdyn″ (*). By Lemma 66, {a mathematical formula}e″⁎⊨O(Σbel⁎φna)⁎, and by Lemma 71, {a mathematical formula}(e″⁎)n⊨OΣbel≫n, and by Lemma 56, {a mathematical formula}((e″⁎)n)Σdyn⊨O(Σdyn,Σbel≫n), and by Theorem 18, {a mathematical formula}((e″⁎)n)Σdyn=e′ (**).For the ⊆ direction let {a mathematical formula}w′∈(ep≫n). By (*) there is some {a mathematical formula}w∈ep″ such that {a mathematical formula}(wΣdyn≫n)=w′. Also, by (**), {a mathematical formula}((w⁎)n)Σdyn∈ep′. By Lemma 72, {a mathematical formula}(wΣdyn≫n)≈R((w⁎)n)Σdyn. Thus {a mathematical formula}w′=(wΣdyn≫n)∈(eR′)p, so {a mathematical formula}(ep≫n)⊆(eR′)p.Conversely, let {a mathematical formula}w∈(eR′)p. Then {a mathematical formula}w≈Rw′ for some {a mathematical formula}w′∈ep′. By (**) there is some {a mathematical formula}w″∈ep″ such that {a mathematical formula}((w″⁎)n)Σdyn=w′. By Lemma 72, {a mathematical formula}(wΣdyn″≫n)≈Rw′, and thus {a mathematical formula}(wΣdyn″≫n)≈Rw. Hence {a mathematical formula}w∈((ep″)Σdyn≫n)R=(ep≫n)R with (*). Thus {a mathematical formula}(eR′)p⊆(ep≫n)R. Since {a mathematical formula}Σdyn,Σbel⁎φna are {a mathematical formula}R-free and by Lemma 40, {a mathematical formula}(ep)R=ep, and so {a mathematical formula}(ep≫n)R=(ep≫n). Thus {a mathematical formula}(eR′)p⊆(ep≫n).  □
     </paragraph>
     <paragraph label="Lemma 74">
      If{a mathematical formula}e⊨OS(Σdyn,Σbel), then{a mathematical formula}e⁎IF(n)⊨OS∪(S′∖R)(Σdyn,Σbel⁎φna).
     </paragraph>
     <paragraph label="Proof">
      Since {a mathematical formula}w⊨□IF(n)≡φna for all {a mathematical formula}w∈ep and {a mathematical formula}p∈N, we have {a mathematical formula}e⁎IF(n)=e⁎φna. Hence by Theorem 42, Theorem 44, {an inline-figure}. Let {an inline-figure}. It is easy to see that {a mathematical formula}⋀ϕ⇒ψ∈Θ(ϕ⊃ψ) is equivalent to {an inline-figure}. Therefore {a mathematical formula}e⁎IF(n)⊨OS∪(S′∖R)(Σdyn,Σbel⁎φna).  □
     </paragraph>
     <paragraph label="Theorem 46">
      {a mathematical formula}⊨OS(Σdyn,Σbel)⊃[n]OS∪S′(Σdyn,Σbel≫n).
     </paragraph>
     <paragraph label="Proof">
      Suppose {a mathematical formula}e⊨OS(Σdyn,Σbel). Let {a mathematical formula}e′⊨O(Σdyn,Σbel⁎φna) and {a mathematical formula}e″⊨O(Σdyn,Σbel≫n), which exist by Theorem 19. By Lemma 74, {a mathematical formula}e⁎IF(n)⊨OS∪(S′∖R)(Σdyn,Σbel⁎φna). By Rule S11 and Theorem 18, {a mathematical formula}e⁎IF(n)=eS∪(S′∖R)′. By Lemma 73, {a mathematical formula}(ep′≫n)=(eR″)p. Thus {a mathematical formula}(eS∪(S′∖R)′)p≫n=(eS∪S′″)p, and so {a mathematical formula}e≫n=eS∪S′″. Moreover by assumption and Rule S11, {a mathematical formula}eS∪S′″⊨OS∪S′(Σdyn,Σbel≫n). Thus by Rule S7, {a mathematical formula}e⊨[n]OS∪S′(Σdyn,Σbel≫n).  □
     </paragraph>
     <paragraph label="Theorem 47">
      {a mathematical formula}OS(Σdyn,Σbel)⊨[n]αiffOS∪S′(Σdyn,Σbel≫n)⊨α.
     </paragraph>
     <paragraph label="Proof">
      For the only-if direction suppose {a mathematical formula}OS(Σdyn,Σbel)⊨[n]α and let {a mathematical formula}e⊨OS∪S′(Σdyn,Σbel≫n). By Corollary 34, there is some {a mathematical formula}e′⊨OS(Σdyn,Σbel). By assumption, {a mathematical formula}e′,w⊨[n]α for all w, and thus {a mathematical formula}e′≫n,w⊨α for all w. By Theorem 46, {a mathematical formula}e′≫n⊨OS∪S′(Σdyn,Σbel≫n), and again by Corollary 34, {a mathematical formula}e=e′≫n. Thus {a mathematical formula}e,w⊨α for all w.For the if direction, suppose {a mathematical formula}OS∪S′(Σdyn,Σbel≫n)⊨α and let {a mathematical formula}e⊨OS(Σdyn,Σbel). By Theorem 46, {a mathematical formula}e≫n⊨OS∪S′(Σdyn,Σbel≫n). By assumption, {a mathematical formula}e≫n,w≫n⊨α for all w. By Rule S7, {a mathematical formula}e,w⊨[n]α for all w.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>