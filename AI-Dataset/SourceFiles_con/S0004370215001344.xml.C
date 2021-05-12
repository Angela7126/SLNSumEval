<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Semantic-based regularization for learning and inference.
   </title>
   <abstract>
    This paper proposes a unified approach to learning from constraints, which integrates the ability of classical machine learning techniques to learn from continuous feature-based representations with the ability of reasoning using higher-level semantic knowledge typical of Statistical Relational Learning. Learning tasks are modeled in the general framework of multi-objective optimization, where a set of constraints must be satisfied in addition to the traditional smoothness regularization term. The constraints translate First Order Logic formulas, which can express learning-from-example supervisions and general prior knowledge about the environment by using fuzzy logic. By enforcing the constraints also on the test set, this paper presents a natural extension of the framework to perform collective classification. Interestingly, the theory holds for both the case of data represented by feature vectors and the case of data simply expressed by pattern identifiers, thus extending classic kernel machines and graph regularization, respectively. This paper also proposes a probabilistic interpretation of the proposed learning scheme, and highlights intriguing connections with probabilistic approaches like Markov Logic Networks. Experimental results on classic benchmarks provide clear evidence of the remarkable improvements that are obtained with respect to related approaches.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      This paper presents Semantic Based Regularization (SBR), a unified framework for inference and learning that is centered around the notion of a constraint and of the parsimony principle. Semantic Based Regularization bridges the ability of machine learning techniques to learn from continuous feature-based representations with the ability of modeling arbitrary pattern relationships, typically used in Statistical Relational Learning (SRL) to model and learn from high-level semantic knowledge. In order to provide a unified context for manipulating perceptual data and prior knowledge, we propose to use the unifying concept of a constraint, which is sufficiently general to represent different kinds of sensorial data along with their relations, as well as to express abstract knowledge on the tasks. We unify continuous and discrete computational mechanisms, so as to accommodate in the same framework very different stimuli. In this paper, we focus on the kernel machine mathematical and algorithmic apparatus to learn from feature-based pattern representations and on constraints resulting from a fuzzy translation of First Order Logic (FOL) formulas, expressing the prior knowledge about the learning task at hand.
     </paragraph>
     <paragraph>
      More specifically, SBR builds a multi-layer architecture having kernel machines at the input layer. The output of the kernel machines is fed to the higher layers implementing a fuzzy generalization of the FOL knowledge. Thanks to the basic properties of fuzzy FOL and kernel machines, the resulting model is continuous with respect to the feature values. Therefore, the high-level semantic inference provided by the logic can be back-propagated down to the kernel machines using any gradient-based schema. This process can be iterated during training until convergence. This is an extremely powerful technique to get advantage of the available unsupervised data, as the inference process performed on this data via the logic knowledge can be used to correct the output of the kernel machines.
     </paragraph>
     <paragraph>
      In this paper we propose a novel collective classification method to enforce the constraints on the test set, thus exploiting the full expressiveness of FOL, like in other statistical relational learning (SRL) approaches. Once again, the distinctive feature of the solution proposed in this paper arises when considering that the collective computational scheme also naturally exploits real-valued feature pattern representations.probabilistic linksWe extend studies on the probabilistic interpretation of regularization networks [38] to our case of learning from constraints. From one side, this highlights connections with Markov Logic Networks (MLNs) [40], while from the other side, this interpretation clearly shows the natural integration of real-valued features and object identifiers in SBR.
     </paragraph>
     <paragraph>
      Furthermore, the paper presents how plain SVM, Transductive, and Laplacian SVMs can be derived as special cases of the proposed SBR framework. The paper also introduces new heuristics, connected to the ones employed in constraint satisfaction programming, to improve the quality of the found solutions. Finally, we present experimental results to show the effectiveness and generality of the approach.
     </paragraph>
     <paragraph>
      The paper is organized as follows: in the next section previous work in the field is reviewed. Section 3 introduces First Order Logic and its fuzzy extensions, while Section 4 discusses learning from constraints with kernel machines. Section 5 presents how SBR generalizes several models commonly used in relational and transductive learning. Details on how training is performed in the SBR framework is presented in Section 6. In Section 7 a collective classification approach for SBR is presented and Section 8 presents connections between SBR and probabilistic models like Markov Logic Networks. The experimental evaluation of SBR is presented in Section 9 and, finally, Section 10 draws some conclusions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Previous work
     </section-title>
     <paragraph>
      Statistical Relational Learning (SRL) combines robust parameter estimation in the presence of noise with learning complex relational structures. Probabilistic Relational Models (PRMs) [13] are an early SRL approach that learns a statistical model from a relational database. PRMs build a probability distribution over the attributes of the objects as an instance of a schema. A Bayesian network with one node for each attribute is built and parameters are estimated from the data. Relational Dependency Networks [34] learn a (local) conditional probability distribution for each node given its Markov blanket by using a conditional learner (like logistic regression or decision trees).
     </paragraph>
     <paragraph>
      Markov Logic Networks (MLNs) [40] have received a lot of attention in the SRL community and have been extensively applied in many fields like bioinformatics [28] and computer vision [46]. Markov Logic Networks generalize and combine first-order logic and probabilistic graphical models. Thanks to their flexibility, MLNs have been used to tackle all the SRL main tasks: collective classification, link prediction, link-based clustering, social network modeling, and object identification. Many papers have also studied how to learn the structure of Markov Logic Networks from data without requiring an expert to express the structure in terms of prior knowledge [23], [22]. Hybrid Markov Logic Networks (HMLNs) [49] extend MLNs to deal with continuous variables.
     </paragraph>
     <paragraph>
      Probabilistic Soft Logic (PSL) [5] is another SRL approach, which relaxes MLNs to continuous fuzzy values in the {a mathematical formula}[0,1] interval and restricts the considered FOL formulas to the ones with conjunctive body and a single literal head. PSL weight training can be solved via a convex optimization problem, but it can face only a small subset of the tasks that are potentially solved by a MLN.
     </paragraph>
     <paragraph>
      One disadvantage of both MLNs and PSL in real-world applications is how they deal with entities that are associated to complex feature-based representations. Let's take as an example the common scenario of a multi-class classification task where the patterns are represented by large vectors of numeric features. In order to perform learning and inference in this domain using classical SRL techniques, different approaches are possible:
     </paragraph>
     <list>
      <list-item label="•">
       the value of a feature can be correlated with one output class using one specific rule. For example, let x be a generic pattern in the domain and f be a binary feature, it is possible to express the rule {a mathematical formula}HasTrueValue(f,x)∧BelongsTo(x,c) for each category c. The training process will estimate a weight modeling the strength of this correlation. MLNs can capture a logistic regression model using this approach [11], [12]. The advantage of this solution is that it employs a coherent framework for dealing with the pattern representations and the higher-level semantic knowledge. However, it requires to deal with a large number of weights and groundings. Furthermore, only very simple correlations between features and classes can be captured as more complex models would be too large to be tractable.
      </list-item>
      <list-item label="•">
       Another approach is to pre-train an arbitrary classifier working on the low-level feature representations and let a SRL layer use the classifier as a prior for the assignments. The SRL layer will assign a proper weight to this prior during training and then the predictions of the base classifier can be refined during the prediction step. This approach uses standard machine learning techniques to learn from the low level data. Complex feature dependencies can be efficiently captured by, for example changing the employed kernel when using a kernel machine as the base classifier. The main disadvantage of this approach is that the two layers are sequentially trained in a greedy fashion. This means that the high level semantic inference is stacked up on top of a pre-trained frozen layer, which processes the pattern representations. This does not allow to use the output of the inference process performed at the higher level to improve the predictions of the base classifier. This is a huge limitation whenever a large number of unsupervised patterns is available and the decision made by the semantic layer could be used as additional supervisions at the lower level.
      </list-item>
     </list>
     <paragraph>
      SBR encodes a multi-layer architecture having kernel machines at the input layer, which provides the input to the higher-level layers implementing a fuzzy generalization of the FOL knowledge. Since the fuzzy FOL generalization of the knowledge is continuous with respect to the values coming from the input layer, information can flow in both directions in this architecture. This allows to back-propagate the information from the high-level inference performed by the logic knowledge down to the kernel machines using a simple gradient-based schema. This allows SBR to preserve the compactness and efficiency of kernel machines to deal with the feature space representations at the input level, while exploiting the full power of FOL to express the higher-level semantics.
     </paragraph>
     <paragraph>
      As it will be discussed later in the paper, keeping two separate but communicating layers one dedicated to processing the feature space and one to performing the higher conceptual reasoning allows to devise more efficient training techniques breaking the complexity of learning. SBR optimization tasks are very similar to the nested optimization problems studied by bilevel programming [2]. Unfortunately, the results obtained in the context of bilevel programming are not easy to reuse for SBR training, as the outer SBR optimization problem is generally neither quadratic nor linear.
     </paragraph>
     <paragraph>
      Other SRL approaches have focused on high level cognitive decision processes with no native integration with learning in the presence of continuous high dimensional data representations. Integration between logic and learning has been traditionally hard to achieve because of the barriers erected by the different mathematical models classically used to handle logical reasoning and learning from examples with real numbers. Connections between logic and kernel machines have been studied in the context of finding relationships between symbolic and sub-symbolic models in AI [21], with particular emphasis on hybrid models. When restricting to kernel machines, a rich analysis of the literature can be found in the survey [26], while a broader coverage of the field with emphasis on the connections with inductive logic programming can be found in DeRaedt at al. [39].
     </paragraph>
     <paragraph>
      Convolution kernels in discrete structures [20] have been one of the main sources of inspiration for exploring connections of kernel machines with logic. Feature Description Logic (FDL) is introduced to support learning in relational domains [8], [9]. The paradigm provides a natural solution to the problem of learning and representing relational data and extends and unifies several lines of works in machine learning. Muggleton et al. [33] presents support vector machines based on a kernel that is an inner product in the feature space spanned by a given set of first-order hypothesized formulas. The inductive logic programming system FOIL is combined with kernel methods in Landwehr et al. [24]. The resulting model (kFOIL) implements a dynamic propositionalization approach allowing to perform both classification and regression tasks. Landwehr et al. [25] presents a general theoretical framework for statistical logical learning based on dynamic propositionalization, where structure learning corresponds to inferring a suitable kernel on logical objects, and parameter learning corresponds to function learning in the resulting reproducing kernel Hilbert space. In the context of multi-task learning, functions can be coupled via dependencies induced by the structure of special multi-task kernels [6].
     </paragraph>
     <paragraph>
      Quite a different approach is based on imposing constraints in the perceptual space [14], [15], [27], where the prior knowledge is incorporated in the form of constraints into a support vector machine classifier.
     </paragraph>
     <paragraph>
      Most of the reviewed papers have already proposed different frameworks for incorporating prior knowledge expressed by logic formalisms into kernel machines. However, the integration seems to be shallow, being based on asking the kernel to play the additional role of incorporating logic structures, instead of primarily measuring the smoothness of the solution according to the Occam's razor. While this is a very interesting idea, the remarkable residual degree of freedom on the way the logic structures can be incorporated suggests that we are only partially addressing the inherent limitation of kernel methods.
     </paragraph>
     <paragraph>
      In the presented framework, the adoption of T-norms allows to simply express most classic logic formalisms by constraints on real-valued functions. Therefore, the general and unified notion of constraint employed in this paper seems to be most natural and straightforward extension of the classic statistical framework of learning from examples, since they are just another special instance of a constraint.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      First order fuzzy logic
     </section-title>
     <paragraph>
      The term fuzzy logic was firstly used by L.A. Zadeh in 1965 [51]. Classical logic works with variables assuming a binary truth value. Fuzzy Logic, instead, is a form of many-values logic or probabilistic logic. It deals with reasoning that is approximate rather than exact [18], where variables have a truth degree that ranges in {a mathematical formula}[0,1]: zero and one meaning that the variable is false and true with certainty, respectively. A fuzzy generalization of FOL has been first proposed by Novak [36].
     </paragraph>
     <section>
      <section>
       <section>
        <section-title>
         T-norm and residuum
        </section-title>
        <paragraph>
         A t-norm is a function {a mathematical formula}t:[0,1]×[0,1]→[0,1], which is continuous, commutative, associative, monotone, and featuring a neutral element 1 (i.e. {a mathematical formula}t(a,1)=a). A strict t-norm is also strictly monotone. A t-norm fuzzy logic is defined by its t-norm {a mathematical formula}t(a1,a2) that models the logical AND. Given a variable {a mathematical formula}a¯ with continuous generalization a in {a mathematical formula}[0,1], its negation {a mathematical formula}¬a¯ corresponds to {a mathematical formula}1−a. Once the t-norm functions corresponding to the logical AND and NOT are defined, they can be composed to convert any arbitrary logic proposition into a continuous function. A t-norm expression behaves as classical logic when the variables assume the crisp values 0 (false) or 1 (true). Many different t-norm fuzzy logics have been proposed in the literature. For example, given two Boolean values {a mathematical formula}a¯1,a¯2 and their continuous generalizations {a mathematical formula}a1,a2 in the {a mathematical formula}[0,1] range, the product t-norm is defined as:{a mathematical formula} The ∨ operator is then consequently defined by using the De Morgan rule:{a mathematical formula} Another commonly used t-norm is the minimum t-norm defined as:{a mathematical formula} from which it follows:{a mathematical formula}
        </paragraph>
        <paragraph>
         The equivalence {a mathematical formula}a¯1⇒a¯2≡¬a¯1∨a¯2 is used in classic logic to represent implications (modus ponens). However, this equivalence is not appropriate to perform deductions with fuzzy variable values. Any t-norm has a corresponding binary operator ⇒ called residuum, which is used in fuzzy logic to generalize implications when dealing with continuous variables. A t-norm residuum provides a natural way to express human fuzzy reasoning, while being equivalent to modus ponens when fuzzy variable values approach the extremes of the {a mathematical formula}[0,1] range.
        </paragraph>
        <paragraph>
         In particular, the residuum converting an implication for the minimum t-norm is defined as:{a mathematical formula} while for the product t-norm the residuum is defined as:{a mathematical formula} The residuum allows to relax the condition of satisfaction for the implication, which is satisfied as soon as the t-norm expression of the head has a higher truth degree than the t-norm expression of the formula body.
        </paragraph>
       </section>
       <section>
        <section-title>
         Quantifiers
        </section-title>
        <paragraph>
         With no loss of generality, we restrict our attention to FOL formulas in the Prenex Normal Form (PNF) form, where all the quantifiers ({a mathematical formula}∀,∃) and their associated quantified variables are placed at the beginning of the expression. For example:{a mathematical formula}
        </paragraph>
        <paragraph>
         Please note that, since we are dealing with variables ranging in {a mathematical formula}[0,1], the quantifier-free part of the expression is equivalent to an assertion in fuzzy propositional logic once all the quantified variables are grounded. Hence, a t-norm fuzzy logic can be used to convert it into a continuous function.
        </paragraph>
        <paragraph>
         Let's consider a FOL formula with variables {a mathematical formula}x1,x2,… assuming values in the finite sets {a mathematical formula}X1,X2,…. {a mathematical formula}P={p1,p2,…} is the vector of predicates, where the j-th n-ary predicate is grounded from {a mathematical formula}Xj∘=Xj1×Xj2×…. In case of an unary predicate {a mathematical formula}Xj∘=Xj1. Let {a mathematical formula}pj(Xj∘) indicate the set of possible groundings for the j-th predicate, and {a mathematical formula}P(X) indicate all possible grounded predicates, such that {a mathematical formula}P(X)=p1(X1∘)∪p2(X2∘)∪….
        </paragraph>
        <paragraph>
         Assuming that the atoms {a mathematical formula}P(X) are generalized to assume real values in {a mathematical formula}[0,1], the degree of truth of a formula containing an expression E with a universally quantified variable {a mathematical formula}xi is defined as the minimum of {a mathematical formula}tE(⋅) obtained as the t-norm generalization of E when grounding {a mathematical formula}xi over {a mathematical formula}Xi:{a mathematical formula}
        </paragraph>
        <paragraph>
         For the existential quantifier, the truth degree is instead defined as the maximum of the t-norm expression over the domain of the quantified variable:{a mathematical formula}
        </paragraph>
        <paragraph>
         The two above generalizations correspond to the conjunction and disjunction of the minimum t-norm expressions of the propositional formula computed over all the groundings, respectively.
        </paragraph>
        <paragraph>
         When multiple universally or existentially quantified variables are present, the conversion is performed recursively from the outer to the inner variables. Please note that any fuzzy FOL formula returns a value in the {a mathematical formula}[0,1] range. The fuzzy formula expression is continuous and differentiable (except that over a set of points with null measure) with respect to the fuzzy value of a predicate.
        </paragraph>
        <paragraph>
         A small modification to classic Fuzzy FOL has been used in this paper, in particular the universal quantifier is generalized as:{a mathematical formula} where the min operator over the t-norm values has been replaced by the average over the set. This definition allows faster convergence during the training of the model: the classical Fuzzy FOL formulation directly depends only on one item over the set of groundings (the argmin element), whereas the average depends on all elements and allows parallel optimization during training. Obviously, the Fuzzy FOL expression in this new formulation is perfectly verified (e.g. it assumes the value 1) iff the same atom assignments would make the old formulation be verified, so the two formulations are consistent.
        </paragraph>
        <paragraph label="Example 3.1">
         The formula {a mathematical formula}∀x1∃x2A(x1)∧B(x2), using a product t-norm for the quantifier-free part conversion corresponds to the following continuous generalization:{a mathematical formula} where {a mathematical formula}A(x1), {a mathematical formula}B(x2) are the fuzzy truth values of the two predicates A and B grounded with {a mathematical formula}x1 and {a mathematical formula}x2.
        </paragraph>
        <paragraph>
         As commonly done in description logic [1], a different operator called n-existential quantifier, indicated as {a mathematical formula}∃n, can be defined to express a property that should hold true for at least n objects. The fuzzy generalization of this quantifier is defined as{a mathematical formula} where {a mathematical formula}Mn(tE,P,Xi,X) is the set of groundings of {a mathematical formula}xi∈Xi corresponding to the n maximum values for {a mathematical formula}tE(P(X)). The conversion of this quantifier collapses into the universal quantifier conversion as {a mathematical formula}n→|Xi| and into the existential quantifier as {a mathematical formula}n→1.
        </paragraph>
        <paragraph>
         It is interesting to note that this translation is computationally more approachable than what can be done in most other SRL approaches. MLNs, for example, replace the existential quantifier by a disjunction over all the groundings. The {a mathematical formula}∃n quantifier can be expressed as n nested existential quantifiers in a MLN, but the number of groundings of the formula would scale as {a mathematical formula}|G|n, where {a mathematical formula}|G| is the number of groundings of the considered variable. In SBR, the {a mathematical formula}∃n corresponds to selecting the n groundings that are the best candidates to satisfy the formula. This candidate selection can be done with complexity {a mathematical formula}O(|G|log⁡n) by using a heap data structure.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="4">
     <section-title>
      Semantic based regularization
     </section-title>
     <paragraph>
      Consider a multi-task learning problem, where a set of T functions must be estimated (query or unknown functions) and another {a mathematical formula}T′ functions (evidence or given functions) are known a priori. Let {a mathematical formula}f={f1,…,fT,fT+1,…,fT+T′} indicate the vector of functions.
     </paragraph>
     <paragraph>
      We assume that a set of H functional constraints in the form {a mathematical formula}1−Φh(f)=0,0≤Φh(f)≤1,h=1,…,H are provided in order to describe how the query functions should behave. Functionals can express a property of a single function or correlate multiple functions, so that learning can be helped by exploiting these correlations.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Hk be the functional space where the k-th function lives. Following the classical penalty approach for constrained optimization, the constraint satisfaction can be enforced by adding a term that penalizes their violation. The resulting cost function to be minimized is:{a mathematical formula} where the first term penalizes non-smooth solutions and {a mathematical formula}λh is the weight for the h-th constraint. A higher value of {a mathematical formula}λh makes it more costly not respecting the constraint, and the constraint becomes hard as {a mathematical formula}λh→∞.
     </paragraph>
     <paragraph>
      The learning problem is relaxed by assuming that the constraints are enforced only over a finite sample of the input patterns. Typically, each pattern is represented as a vector of real-valued features, but we will see also cases where the patterns are simply represented by a unique identifier. In particular, the j-th function is associated to a set {a mathematical formula}Xj∘ of pattern representations {a mathematical formula}xj. It is possible that multiple functions share the same sample of patterns (e.g. {a mathematical formula}Xj∘=Xi∘i≠j). Since some functions may express relations across multiple patterns, the pattern representations associated to a function can be generally expressed as the combination of the patterns from a set of finite domains: {a mathematical formula}Xj∘=Xj1×Xj2×….
     </paragraph>
     <paragraph>
      Let {a mathematical formula}fk(Xk∘) indicate the vector of values obtained by applying the function {a mathematical formula}fk to the set of patterns {a mathematical formula}Xk∘ and {a mathematical formula}f(X)=f1(X1∘)∪f2(X2∘)∪… collects the groundings for all functions. Enforcing the constraints only over the samples of data, yields the following cost function:{a mathematical formula} Please note that for the sake of simplicity (and with abuse of notation), the same symbol Φ was used to refer to both the exact and empirical approximation functionals.
     </paragraph>
     <paragraph>
      The solution to the optimization task defined by the objective function in Equation (2) is a kernel expansion in the form:{a mathematical formula} where {a mathematical formula}βk is a bias and {a mathematical formula}Kk(⋅,⋅) is the reproducing kernel associated to the space {a mathematical formula}Hk. The proof [10] is a straightforward extension of the Representer Theorem for plain kernel machines [42]. The bias {a mathematical formula}βk is added to specify the default value of a function. The weights of the k-th function are indicated as {a mathematical formula}wk={wk1,…,wk|Xk∘|}. Plugging Equation (3) into (2), we get an expression that can be minimized by optimizing the {a mathematical formula}wk by gradient descent:{a mathematical formula} where {a mathematical formula}f(X)={G1w1,…,GTwT,fT+1(XT+1∘),…,fT+T′(XT+T′∘)} and {a mathematical formula}Gk is the Gram matrix for the k-th function, whose {a mathematical formula}(i,j) element is equal to {a mathematical formula}Kk(xki,xkj). For the sake of simplicity, we have not explicitly added the vector of bias values as input to {a mathematical formula}Φh(f(X)).
     </paragraph>
     <section label="4.1">
      <section-title>
       Logic and constraints
      </section-title>
      <paragraph>
       Let us assume that a knowledge base KB, consisting of a set of FOL formulas and a set of groundings for the variables, is provided to express some domain knowledge. Some of the predicates are unknown and must be estimated. The j-th unknown predicate is approximated by the function {a mathematical formula}σ(fj(⋅)) where {a mathematical formula}fj is the function that must be learned, and {a mathematical formula}σ(⋅) is a sigmoidal function mapping the functions' outputs onto the {a mathematical formula}[0,1] range, on which the t-norms are defined. In the remainder of the paper we drop the σ to not overload the notation. The variables in the KB that are input to any {a mathematical formula}fj are replaced with the feature-based representation of the object grounded by the variables. We will indicate as {a mathematical formula}xi the representation of the object grounded by {a mathematical formula}xi, where {a mathematical formula}ρ(xi)=xi is a function mapping a pattern representation into its object identifier. The groundings {a mathematical formula}Xi of the i-th variable are therefore replaced by the set {a mathematical formula}Xi, indicating the set of feature-based representations of the groundings. One constraint {a mathematical formula}1−Φi(⋅)=0 for each formula {a mathematical formula}Fi in the knowledge base is built by taking the fuzzy FOL generalization of the formula {a mathematical formula}Φi(⋅), where the unknown predicates are replaced by the learned functions, and the variables input to the learned functions are replaced by their duals iterating over the feature-based representations of the groundings.
      </paragraph>
      <paragraph label="Example 4.1">
       Let's suppose to have a text categorization task, where the documents must be assigned to the categories {a mathematical formula}A,B,C,D. Let d be a generic document to be classified and {a mathematical formula}A(d),B(d),C(d),D(d) be the unknown indicator functions for the classes. We indicate with d the feature representation for d, which would typically be its bag-of-word TF or TF-IDF representation. The functions {a mathematical formula}fA(d), {a mathematical formula}fB(d), {a mathematical formula}fC(d), {a mathematical formula}fD(d) must be estimated to approximate respectively the unknown {a mathematical formula}A(d), {a mathematical formula}B(d), {a mathematical formula}C(d), {a mathematical formula}D(d). We will assume that the variable d will be grounded with two documents {a mathematical formula}{d1,d2}, having as bag-of-word representations: {a mathematical formula}D={d1,d2}, respectively. We will use this simple learning task as running example for the rest of the paper.
      </paragraph>
      <paragraph>
       The fuzzy FOL generalization of the knowledge base provides a continuous and differentiable surrogate of the initial logic formulas such that {a mathematical formula}0≤Φi(⋅)≤1. Therefore, the resulting constraints {a mathematical formula}1−Φi(⋅)=0 are continuous and differentiable as well, and this will allow to train the query functions using any gradient-based learning schema.
      </paragraph>
      <paragraph>
       The form of the constraints depends on which t-norm has been used to generalize the FOL rules. Whereas it is always true that all t-norms are consistent with classical logic when variables assume crisp values ({a mathematical formula}0,1), the behavior of the various t-norms differs for the intermediate values, ultimately leading to different constraints. Similarly to the selection of the right kernel for kernel machines, the choice of a t-norm is always a matter of context, and it depends on the problem which is modeled [17]. For example, the minimum t-norm can be a better choice than a product t-norm when performing inference in presence of long conjunctive chains, where the value of the conjunction would vanish exponentially in the number of terms when using a product t-norm. The product t-norm is correct in this case as well, since it behaves consistently to its probabilistic-independence assumption, but training may be too slow. The t-norm selection should not have a strong impact in most applications, and it did not provide any significant change in all the experiments presented in this paper.
      </paragraph>
      <paragraph label="Example 4.2">
       Continuing the text categorization example, we can assume to have some external knowledge about the categories: {a mathematical formula}∀dA(d)∨B(d) expressing that any document must belong to class A or B. The constraint resulting from the fuzzy FOL generalization of the formula after substituting the query predicates with the unknown functions and the two document representations is:{a mathematical formula} where {a mathematical formula}t(⋅) is the minimum t-norm representation for the propositional part of the formula. This constraint can be directly plugged into Equation (4) for optimization.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Nodes with no feature vector representation
      </section-title>
      <paragraph>
       It is common to have query predicates for which the input arguments (their groundings) have no associated feature representation. Most Statistical Relational Learning approaches are indeed assuming this case. In this case, the inputs can simply be listed as a sequence of unique identifiers. Equation (4) can still be used as generic expression of the cost function by setting the Gram matrix to be the identity matrix for all predicates that have no vectorial input e.g. {a mathematical formula}Gk=I. In this case the vector of weights becomes the vector of values of the function over the inputs as {a mathematical formula}fk(Xk∘)=Gkwk=Iwk=wk. These unknown values must be directly estimated without generalizing over the input space (which is null).
      </paragraph>
      <paragraph>
       Obviously, an interesting case is when some functions have inputs represented as vectors of features and others don't. The experimental section will present some experiments in this mixed setting.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       SBR as a multi-layer architecture
      </section-title>
      <paragraph>
       Given an arbitrary KB, the procedure described in the previous section can be generally encoded by a multi-layer network with the following structure:
      </paragraph>
      <list>
       <list-item label="•">
        input layer: computation of the atoms, this is performed by computing the query and evidence function values for all possible groundings;
       </list-item>
       <list-item label="•">
        propositional layer: the value of the t-norm expression of the propositional part of each formula is computed for each compatible combination of atoms;
       </list-item>
       <list-item label="•">
        quantifier layers: the t-norm values computed at the previous layer are aggregated by the average or max operator for the universal and existential quantifiers, respectively. Please note that the number of quantifier layers is not fixed, as the aggregation of the outputs is recursively nested according to the number of quantifiers in the FOL formula. The output of this layer is a score in {a mathematical formula}[0,1] expressing how strongly the FOL formula is respected.
       </list-item>
       <list-item label="•">
        output layer: accumulation by summation of the contributions coming from the single formulas.
       </list-item>
      </list>
      <paragraph>
       Learning and inference are intractable in large domains, because of the exponential growth of the number of groundings with respect to the number of nested quantifiers. However, in most applications, a large portion of the ground clauses are trivially satisfied or not satisfied by the known evidence atoms regardless of unknown assignments. These groundings can be discarded without introducing any approximation in the training or inference process. In the context of MLNs, many heuristics and algorithms like FROG preprocessing [43], Tuffy [35] or LazySAT [44] have been proposed to detect and discard these non-informative groundings. Since the grounding process of MLNs and SBR is essentially the same, these algorithms can be directly reused in SBR. In particular, FROG preprocessing has been used in the presented experiments to prune the encoded network in the input and propositional layers, whenever the grounding of the evidence predicates makes the formula always holding true or false, independently on the values assumed by the query predicates. In this case the contribution to the cost function of the grounding is constant and it has no effect on the learning process. Therefore, it is useless to instantiate this grounding in the encoded network. A common case where the pruning process can be applied is when dealing with a FOL formula in the following form: {a mathematical formula}R(x)⇒A(x) where {a mathematical formula}R(x) is an evidence predicate. When it holds that {a mathematical formula}R(p)=false given the grounding {a mathematical formula}x=p, the rule is verified regardless of the value of the query predicate {a mathematical formula}A(p). Therefore the grounded predicates {a mathematical formula}R(p),A(p) can be safely discarded from the encoding network during training, unless appearing in another FOL formula.
      </paragraph>
      <paragraph>
       To summarize, the network encoded by SBR for a given KB can be defined as in the following.
      </paragraph>
      <paragraph label="Definition 4.3">
       SBR networkAssume a FOL KB composed by rules and predicates, which are grounded by a set of constants. Let x represent the feature vector associated to a grounding x. We indicate with {a mathematical formula}fi(⋅) the function implemented by a Kernel Machine, approximating the i-th unknown predicate {a mathematical formula}pi, where {a mathematical formula}fi(⋅) takes as input the feature vector representations of the constants grounding the predicate. SBR builds a multi-layer network {a mathematical formula}N computing the fuzzy FOL approximation of the KB, where the value {a mathematical formula}fi(x) replaces a grounded unknown predicate {a mathematical formula}pi(x).
      </paragraph>
      <paragraph>
       Some examples of KB and relative network encodings will be shown in the remainder of the paper.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Some special cases of SBR
     </section-title>
     <paragraph>
      This section will show how SBR can reproduce standard and Transductive SVMs, manifold and graph regularization. At the same time all these learning schemas can be mixed and extended arbitrarily with the full expressiveness of FOL.
     </paragraph>
     <section label="5.1">
      <section-title>
       Case 1: SVMs
      </section-title>
      <paragraph>
       Let {a mathematical formula}Xk+,Xk− be the sets of positive and negative examples for the k-th unknown predicate {a mathematical formula}pk, ({a mathematical formula}Xk∘=Xk+∪Xk−). The following logic formula expresses the fact that {a mathematical formula}pk is constrained on the values assumed over the supervised data:{a mathematical formula} where {a mathematical formula}x∈Xk and the predicate {a mathematical formula}Pk(x) is an evidence function holding true iff x is a positive example for the query predicate {a mathematical formula}pk (e.g. {a mathematical formula}x∈Xk+). Using the minimum t-norm and replacing {a mathematical formula}pk with its approximation {a mathematical formula}fk, this corresponds to the following constraint:{a mathematical formula} where {a mathematical formula}max⁡(0,1−fk(x)) is the hinge loss used by regular SVM. The same hinge loss would appear for negative supervisions if using the −1 value for negative supervisions instead of the 0 used here. Therefore, plugging the previous constraint into Equation (4) shows that classical SVMs are a special case in our framework, when expressing the fitting of the supervised data as logic knowledge. Please note that the constraints resulting from the supervised data fitting are a special case of a constraint that is convex and relatively easy to optimize. We will discuss this point into more details in the following section.
      </paragraph>
      <paragraph>
       When unsupervised data is also available, it is possible to express the supervisions using two evidence predicates. In particular, let {a mathematical formula}Xk+, {a mathematical formula}Xk−, {a mathematical formula}Xku be the available positive, negative and unsupervised examples for task k (e.g. {a mathematical formula}Xk∘=Xk+∪Xk−∪Xku). The learned function is constrained in terms of the assumed values on the supervised data by specifying the following logic formulas {a mathematical formula}Fp,Fn:{a mathematical formula}{a mathematical formula} where {a mathematical formula}Pk(x) and {a mathematical formula}Nk(x) are evidence functions holding true iff x is a positive or negative example for the query predicate {a mathematical formula}pk, respectively. Also this formulation corresponds to the learning task solved by standard SVM training (patterns that are neither positive nor negative supervised do not contribute to the cost function) and it will be used as base step for solving more complicated learning tasks, where unsupervised data plays a role, in the remainder of the paper.
      </paragraph>
      <paragraph label="Example 5.1">
       In our text categorization example, let us assume that {a mathematical formula}d1 belongs to class A and {a mathematical formula}d2 does not. This can be expressed by stating that {a mathematical formula}d1 is a positive supervised example: {a mathematical formula}PA(d1)=true, while {a mathematical formula}PA(d2)=false. We can then express the rule: {a mathematical formula}∀d(PA(d)∧A(d))∨(¬PA(d)∧¬A(d)) to incorporate the labeled data into the learning task. The following constraint results from the fuzzy FOL generalization of the formulas using the minimum t-norm and after substituting the document identifiers with their feature representations and the query predicates with the corresponding functions to estimate:{a mathematical formula}Fig. 1 shows the network which is encoded when performing this simple learning task.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Case 2: manifold regularization
      </section-title>
      <paragraph>
       Manifold Regularization [3] assumes that the learned function should be regular over the input manifold, which is represented as a graph, whose edges connect the input patterns. The graph can be directly built over the input data distribution, or built from external knowledge like html hyperlinks in a web page classification problem. Laplacian SVM (LSVM) [31] is an effective semi-supervised approach to train SVMs under the manifold regularization assumption.
      </paragraph>
      <paragraph>
       Manifold Regularization is a special case of SBR, where there are rules forcing the fitting of the supervised examples, as previously described, and an additional rule expressing the manifold assumption. In particular, let {a mathematical formula}R(x,y) be a given (evidence) relation expressing whether {a mathematical formula}x,y are connected on the manifold. The manifold assumption in a logic setting for a predicate p is expressed by the following FOL formula, asserting that two connected points should either be both true or both false:{a mathematical formula}
      </paragraph>
      <paragraph label="Example 5.2">
       Let us assume that, in the previously considered text categorization task, {a mathematical formula}d1 links to {a mathematical formula}d2 via a hyperlink {a mathematical formula}R(d1,d2)=1, while no links are available between the other documents. Manifold regularization in this domain is expressed for the category A by a formula {a mathematical formula}FR, whose fuzzy FOL generalization {a mathematical formula}ΦFR is obtained by substituting the query predicate A with the unknown function {a mathematical formula}fA and using the minimum t-norm. This yields the following constraint:{a mathematical formula} where the first contribution comes from the 3 groundings for which the R predicate is false and the rule trivially verified. This contribution does not affect the training process and can be dropped. This constraint can be plugged into Equation (4) to get the cost function to optimize. Fig. 2 shows the encoded network after FROG-preprocessing for this learning task with also added one positive supervision expressed by a formula indicated as F. This rule is in the form that can also account for any unsupervised data as previously described. FROG-preprocessing keeps in the network only the groundings for which either {a mathematical formula}PA or R are true, as the rules F and {a mathematical formula}FR are always verified based on the evidence predicates otherwise. Similar rules could be added to express manifold regularization for the other classes {a mathematical formula}B,C,D.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Case 3: hierarchical classification
      </section-title>
      <paragraph>
       Complex classification tasks often involve a large number of classes organized into a hierarchy. Typically, a hierarchy can be represented as a Directed Ordered Acyclic Graph (DOAG), where each node corresponds to a class. A single root node is provided as starting point of the classification process, from where all other nodes can be reached. The classification process explores a set of paths on the graph, where each path ends with a leaf node. A two level-hierarchical classification with n classes at the first level can be expressed by the rules:{a mathematical formula}{a mathematical formula} where {a mathematical formula}pi,i=1,…,n are the father classes at the first level of the hierarchy, {a mathematical formula}ni is the number of child classes of class {a mathematical formula}pi and {a mathematical formula}pijc,j=1,…,ni are the child classes of {a mathematical formula}pi. Class priors for each category can also be expressed via the rules:{a mathematical formula}{a mathematical formula} where {a mathematical formula}mi and {a mathematical formula}mij can estimated from the supervised data. This schema can be recursively generalized to taxonomies of arbitrary depth.
      </paragraph>
      <paragraph label="Example 5.3">
       For the text categorization example, we assume that C is the only child class of A in the taxonomy. Therefore, the formula {a mathematical formula}FT:=∀dA(d)⇒C(d) expresses the taxonomical information that any document belonging to class A belongs also to class C. The resulting constraint obtained from the fuzzy FOL generalization {a mathematical formula}ΦFT of the formula over the set {a mathematical formula}D of available documents is:{a mathematical formula} where {a mathematical formula}tT is the fuzzy generalization of the formula {a mathematical formula}FT using the residuum of the minimum t-norm.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Case 4: transductive SVMs
      </section-title>
      <paragraph>
       Transductive SVMs (TSVMs) [48] extend SVMs by finding a hyperplane with maximum separation margin for the labeled data and the labeling of the unsupervised data induced by the hyperplane itself. Therefore, Transductive SVMs tend to place the separating hyperplane on low density regions of the input space.
      </paragraph>
      <paragraph>
       TSVMs can be expressed in SBR by adding a FOL formula forcing all pattern classifications to be either true of false:{a mathematical formula} where {a mathematical formula}pk(x) is the k-th query predicate that returns true iff a pattern x belongs to a given class. While the above formula is always trivially verified in standard FOL, the same does not apply to the fuzzy generalizations of FOL, where the classification scores can be anywhere in the {a mathematical formula}[0,1] range.
      </paragraph>
      <paragraph>
       As in Transductive SVMs, trivial solutions are avoided by forcing the balancing between the number of unlabeled patterns to be positively or negatively classified using a prior determined over the supervised data:{a mathematical formula} where, given the sample {a mathematical formula}Xk of the variable x, {a mathematical formula}nk,mk ({a mathematical formula}nk+mk=|Xk|) are the expected numbers of patterns in the sample for which the unknown predicate should hold true and false, respectively.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Case 5: graph regularization
      </section-title>
      <paragraph>
       Graph regularization [52] is a transductive learning task where all generalization happens during training. All the data patterns are arranged as nodes of a graph, whose edges are associated to the weights expressing the degree of similarity of the connected patterns. Some graph nodes are supervised and, therefore, associated with a target value. The learning task consists in assigning a value to all the nodes in the graph, while being smooth over similar (connected) nodes. No feature representation is available in any node and generalization happens at a purely topological level.
      </paragraph>
      <paragraph>
       In SBR, the supervisions for a Graph Regularization task are expressed using the same logic formulas described in Section 5.1. Like for manifold regularization, let {a mathematical formula}R(x,y) be a known relation expressing whether two patterns are connected, then the following rule can be used to express the smoothness over the graph connections: {a mathematical formula}∀x∀yR(x,y)⇒(pk(x)∧pk(y))∨(¬pk(x)∧¬pk(y)), for the k-th query predicate {a mathematical formula}pk. The encoded network has the same structure as the example presented in Fig. 2, but with void input representations in the first layer and functions implemented via the special kernel discussed in Section 4.2.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Training
     </section-title>
     <paragraph>
      Training in SBR means to determine the weights of the kernel machines in the input layer or, directly, the outputs for the functions with null feature-based inputs. The weights are optimized via gradient descent using a back-propagation schema, where the output layer computes the derivative with respect to each constraint: {a mathematical formula}∂Ce∂Φk. In the quantifier layers, the derivative of a constraint with respect to each predicate grounding is computed: {a mathematical formula}∂Φk∂tΦk. At the propositional level the derivatives with respect to the single functions are computed: {a mathematical formula}∂tΦk∂fi. At the input level the derivatives with respect to the single parameters are computed: {a mathematical formula}∂fi∂wij=Ki(xj,⋅).
     </paragraph>
     <paragraph>
      The overall derivative of the cost function with respect to the j-th weight of the i-th function {a mathematical formula}wij is:{a mathematical formula}
     </paragraph>
     <paragraph>
      When no input feature representation is provided, the weight is the function value itself {a mathematical formula}wij=fij, and no back-propagation over the function weights is needed. Resilient gradient descent using a custom learning rate for each parameter was empirically found to converge very quickly and was therefore used in all the presented experiments.
     </paragraph>
     <section label="6.1">
      <section-title>
       Logic formulas and complexity in optimization
      </section-title>
      <paragraph>
       Not all FOL formulas are translated into a constraint which is well suited for optimization. Indeed, this section will show that the general intractability of FOL inference is directly translated into a SBR cost function that is plagued by many local minima.
      </paragraph>
      <paragraph>
       Let's consider universally quantified FOL formulas in DNF form:{a mathematical formula} where {a mathematical formula}nij determines whether the j-th variable in the i-th minterm is negated or not. Applying a double negation and using the DeMorgan rule, yields the following expression for each grounding:{a mathematical formula}
      </paragraph>
      <paragraph>
       Now converting the above propositional expression using the product t-norm, and assuming to generalize the atoms in the {a mathematical formula}[0,1] range using the unknown function approximations, we get the constraint:{a mathematical formula} where {a mathematical formula}Arp and {a mathematical formula}A1n are the set of non-negated and negated atoms in the r-th minterm and, as in the rest of the paper, we have omitted the squashing function {a mathematical formula}σ(⋅) in front of each {a mathematical formula}fi(⋅) which keeps the values in the {a mathematical formula}[0,1] range. An assignment verifying the r-th minterm will result in {a mathematical formula}∏i∈Arpfi(xi)∏j∈Arn(1−fj(xj))=1. Therefore, a null contribution will result from any assignment verifying one minterm when summing over all the groundings. Since all minterms are by construction different and the polynomial equation is continuous and assuming values greater or equal to zero as guaranteed by any t-norm, the resulting expression has as many local minima as the number of true configurations in the truth table for the grounded propositional formula (e.g. this number is by construction equal to the number of minterms in the initial DNF). Therefore, there is a perfect duality between the number of possible assignments of the atoms verifying the FOL formula for a given grounding of the variables, and the number of local minima introduced into the constraint resulting from generalizing the formula to a continuous domain. Not surprisingly, this shows that optimization in the continuous domain is as hard as finding the correct assignments in the original FOL formulation. It is clear that formulas with a single minterm correspond to a convex constraint and have a single minimum, we will see examples of this special case in the following paragraph. While the product t-norm was used in this paragraph, because it is simple to study the solutions of the resulting polynomial, this result can be extended to any strict t-norm, since all strict t-norms are isomorphic to the product t-norm [45].
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Stage-based learning
      </section-title>
      <paragraph>
       As shown in the previous sections, the cost function is plagued by many local minima when dealing with a non-trivial knowledge base. This section will discuss a heuristic, which has been experimentally proved to allow to successfully train models on large scale datasets.
      </paragraph>
      <paragraph>
       In constraint satisfaction programming [41], picking up the variable with the smallest number of admissible values remaining in its domain is one of the most commonly used heuristics to select the next variable to assign during search [16]. As explained by Haralick and Elliot [19], this heuristic minimizes the depth of the search tree. Following the standard notation used in Rossi et al. [41], we will refer to this heuristic as dom. In the context of SBR, the dom heuristic corresponds to force earlier the formulas with a lower number of possible valid (e.g. verifying the formula) assignments to the atoms to be learned, once the evidence predicates have been grounded. As explained in the previous section, these formulas introduce a lower number of local minima into the cost function.
      </paragraph>
      <paragraph>
       For example, let's consider the following KB:{a mathematical formula}{a mathematical formula}{a mathematical formula} where the predicates {a mathematical formula}p1,p2,p3 must be learned. The first rule has the same form of the one presented in Section 5.1 to express the fitting of the supervised examples. This rule has the minimum possible degree of freedom as there is only one possible assignment to the atom {a mathematical formula}p1(x) for each evidence grounding of {a mathematical formula}P1(x). Therefore, this rule should always be the first to be used in training according to the dom heuristic. Not surprisingly, the previous section showed that rules with one single degree of freedom are convex when translated into a continuous constraint using t-norms. Rule 2 has three and four possible assignments when the evidence grounded predicate {a mathematical formula}P1(x) holds true and false, respectively. Rule 3 has seven possible different assignments of the query predicates. Therefore, the rule 2 should be added to the training process before than the last one, as it has less degrees of freedom. Since the assignments verifying a rule depend on the evidence predicate assignments, we usually use the average over all possible evidence groundings for a rule (in the example the average is 3.5 for rule 2). We leave for further studies how to improve this simple schema. For example, it would be possible to compute the expected number of possible assignments of the query predicates from the distribution of the observed evidence groundings in the training data.
      </paragraph>
      <paragraph>
       The dom heuristic applied to SBR has connections with research in deep learning that has shifted the attention on teaching plans in a more systematic way [4], but also at a more generic level with studies in the field of developmental psychology, since it is well-known that many animals experiment stage-based learning [37]. The experimental results will show that it is indeed beneficial to split the optimization problem into multiple stages, where the constraints are introduced in order of complexity as dictated by dom.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Collective classification
     </section-title>
     <paragraph>
      Collective Classification is the task of performing inference over a set of instances that are connected among each other via a set of relationships. Collective classification is often an easier task than independent pattern classification, because the relationships can be exploited to enforce classification consistency.
     </paragraph>
     <paragraph>
      Collective classification in SBR assumes to have available some FOL knowledge, which is converted into a set of constraints using the previously described methodology. Given a test set composed of a set of groundings, the collective classification process will force the test set classification assignments to respect the constraints.
     </paragraph>
     <paragraph>
      In particular, let {a mathematical formula}fk(Xk′) indicate the vector of values obtained by evaluating the kernel machine function {a mathematical formula}fk over the data points of the test set {a mathematical formula}Xk′. The set of vectors will be compactly referred to as: {a mathematical formula}f(X′)=f1(X1′)∪…∪fT(XT′). If no kernel machine has been trained for {a mathematical formula}fk (no examples or no feature representations were available during training), {a mathematical formula}fk(Xk′) is assumed to be just filled with default values equal to 0.5.
     </paragraph>
     <paragraph>
      Collective classification searches for the values {a mathematical formula}f¯(X′)=f1¯(X1′)∪…∪fT¯(XT′) respecting the FOL formulas on the test data, while being close to the prior values established by the kernel machines over the test data:{a mathematical formula}
     </paragraph>
     <paragraph>
      Optimization can be performed via gradient descend by computing the derivative with respect to the function values:{a mathematical formula}
     </paragraph>
     <paragraph>
      As shown in Equation (6), SBR collective classification reuses the same schema to compute the gradients of the constraints {a mathematical formula}∂Φh∂fk¯ as shown in Equation (5). However, whereas the gradient was computed with respect to the functions' weights in the training phase, only the first terms of the chain rule have to be taken into account during collective classification:{a mathematical formula} Indeed, since the input weights are now fixed, no back-propagation of the derivative of the error down to the weights is needed. This provides an elegant solution to collective classification, which employs the same back-propagation routines used in training with no additional complexity in the implementation.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      SBR as a probabilistic model
     </section-title>
     <paragraph>
      In this section we highlight some probabilistic interpretations of the solutions found by SBR. Given the constraints {a mathematical formula}Φ={Φ1,…,ΦH} computed over the data {a mathematical formula}X, the probability distribution {a mathematical formula}P(V=f|X,Φ) of the possible assignments to the functions f is assumed to follow an exponential model as:{a mathematical formula} where Z is a normalization factor, {a mathematical formula}ϕ(f(X),Φ) measures how well f respects the constraints and {a mathematical formula}ϕpr(f) penalizes irregular solutions. The prior is the expression of the classical Tikhonov regularization in terms of prior probabilities [50] when assuming a Gaussian prior: {a mathematical formula}Ppr(f)∝ϕpr(f)=exp⁡(−∑k‖fk‖2). Therefore,{a mathematical formula} This result provides a probabilistic interpretation of the SBR formulation given in Equation (2) (the change of sign is due to the fact that the probability is maximized, where in Equation (2) the cost is minimized). In the special case of a constraint representing a formula with only universal quantifiers, it holds that:{a mathematical formula} where {a mathematical formula}ih iterates over the {a mathematical formula}Gh possible groundings of the h formula {a mathematical formula}Fh, having {a mathematical formula}tΦh(⋅) as its the t-norm conversion, {a mathematical formula}xih is the set of pattern representations of the i-th grounding of {a mathematical formula}Fh, {a mathematical formula}f(xih) indicates the set of values returned by the functions when computed on {a mathematical formula}xih and {a mathematical formula}λh′=λh|Gh|.
     </paragraph>
     <section label="8.1">
      <section-title>
       SBR and Markov logic networks
      </section-title>
      <paragraph>
       A Markov network is a model for the joint distribution of a set of variables V and it is composed of an undirected graph expressing the variable dependencies and a set of potential functions. The graph has a node for each variable, and the model has a potential function for each clique in the graph. A potential function is a non-negative function of the state of the corresponding clique. The joint distribution represented by a Markov network is given by{a mathematical formula} where {a mathematical formula}v{k} is the state of the variables that appear in that clique and Z is the partition function. Markov networks are often represented as log-linear models, where each clique potential is replaced by an exponentiated weighted sum of features of the state:{a mathematical formula}
      </paragraph>
      <paragraph>
       A Markov Logic Network (MLN) [40] is a set of pairs {a mathematical formula}(Fh,λh), where {a mathematical formula}Fh is a formula in first-order logic and {a mathematical formula}λh is a real number. Given a finite set of constants {a mathematical formula}Ch, defining the groundings of all the variables appearing in the {a mathematical formula}Fh, a Markov network MLN is defined as:
      </paragraph>
      <list>
       <list-item label="1.">
        an MLN contains one node for each possible grounding of each predicate, the value of the node is 1 iff the atom is true.
       </list-item>
       <list-item label="2.">
        an MLN contains one feature for each possible grounding of each formula {a mathematical formula}Fh. The value of this feature is equal to 1 iff the ground formula is true. The weight of the feature is {a mathematical formula}λh.
       </list-item>
      </list>
      <paragraph>
       The probability distribution over possible assignments v specified by the ground Markov network MLN is given by{a mathematical formula} where {a mathematical formula}nh(v) is the number of true groundings of {a mathematical formula}Fh in v.
      </paragraph>
      <paragraph label="Definition 8.1">
       A Markov Fuzzy Logic Network (MFLN) is a set of pairs {a mathematical formula}(Fh,λh), where {a mathematical formula}Fh is a formula in first-order logic and {a mathematical formula}λh is a real number. Together with a finite set of constants {a mathematical formula}Ch, defining the groundings of all the variables appearing in the {a mathematical formula}Fh, it defines a Markov network MFLN as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        an MFLN contains one node for each possible grounding of each predicate, the value of the node is the degree of truth of the atom.
       </list-item>
       <list-item label="2.">
        an MFLN contains one feature for each possible grounding of each formula {a mathematical formula}Fh. The value of this feature is equal to the degree of truth of the formula computed via a fuzzy FOL generalization of {a mathematical formula}Fh. The weight of the feature is {a mathematical formula}λh.
       </list-item>
      </list>
      <paragraph>
       The resulting network will contain one clique for each grounded formula. An MFLN extends an MLN allowing non-binary features and a continuous degree of truth for the predicates. While a MLN counts the number of true groundings of a formula in the world, an MFLN computes the sum of the degrees of satisfaction of the formula computed via a t-norm.
      </paragraph>
      <paragraph>
       Let's assume that the unknown predicates are approximated with the output of the kernel machines f applied over the groundings. Let {a mathematical formula}xih be the set of pattern representations associated to the i-th grounding of {a mathematical formula}Fh and {a mathematical formula}f(xih) be the set of values returned by the functions when computed over the {a mathematical formula}xih. The value of the feature associated to this grounding is the t-norm value {a mathematical formula}tΦh(f(xih)).
      </paragraph>
      <paragraph>
       Therefore,{a mathematical formula}
      </paragraph>
      <paragraph>
       By comparing Equations (8) and (9), it emerges that SBR can be seen as a MLN where the FOL formulas and node values are replaced by their fuzzy generalization with the node values computed by kernel machines.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Discussion
      </section-title>
      <paragraph>
       A fundamental difference among MLNs and SBR is that MLNs either in their standard or hybrid version [49] cannot incorporate the feature-based pattern representations if not associating a rule and weight to each feature: for example see how text categorization with MLNs is performed by Domingos and Summer [12]. On the other hand, SBR implements a multi-layer architecture where pattern representations can be dealt using kernel machines at the first layer. This has various advantages in terms of training and flexibility. Indeed, MLNs see all the weights (defining the input and higher level inference) at the same level, while SBR can employ more appropriate and efficient learning schema for the input level, or it can even perform different training phases like the simple strategy employed described in Section 6.2. Unlike MLNs, SBR can deal with continuous, high-dimensional and highly correlated feature vectors. Furthermore, SBR can be defined in cases where the input representation is not vectorial or even unknown, as only the kernel values over the inputs are needed in order to perform training and inference.
      </paragraph>
      <paragraph>
       The connections that have been enlighten in this paragraph between MLNs and SBR suggest that it is possible to reuse the MLN training mechanism to learn the rule weights {a mathematical formula}λh in the output layer of SBR using Equation (9). Like in MLNs this would require to compute the partition function, which often leads to inefficiency and approximations. However, the experimental results show that learning the input layer weights in SBRs is often more effective than solving the MLN learning task in many contexts.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      The proposed framework has been the subject of a large experimental analysis that was carried out by using the SBR software package.{sup:1}
     </paragraph>
     <section label="9.1">
      <section-title>
       Transductive learning: text categorization on the CORA dataset
      </section-title>
      <paragraph>
       The CORA research paper dataset is a relational dataset containing information about papers and associated authors [30]. The CORA dataset collects papers classified into a topic hierarchy of 80 classes with 10 classes at the first level.{sup:2} In addition, authors have been classified into a set of 10 classes depending on their major topic of research interest. A random sample of 2000 papers belonging to at least one of the 10 top level classes was extracted together with the 3928 authors having at least one publication in the selected sample of papers. Each paper was associated with a vectorial representation containing the title represented as bag-of-words with TF-IDF weights. There is no profile of authors, being symbolic entities without feature representation. The learning task consists of predicting the category of the papers and the author research area. This is a multi-label dataset, since authors can be associated to multiple categories. Papers have been split into three sets: published before the year 1995, papers published in year 1995 and all later papers. The resulting sets contain 949 papers and 2272 authors, 316 papers and 605 authors, and 735 papers and 1051 authors, respectively. The three sets form the pools from which the training, validation and test datasets are sampled from, respectively. This simulates a real world scenario, where the training process is performed at a certain time and testing is expected to involve new incoming papers. In particular, five folds have been generated by randomly selecting n% of the papers and n% of authors {a mathematical formula}(n=10,20,30,40,50) for which supervisions are kept in the first and second sets as training and validation data. Experiments have been carried out in a transductive context, where the test data is available as unsupervised data during training, and by averaging over 5 folds.
      </paragraph>
      <section>
       <section>
        <section-title>
         Knowledge base
        </section-title>
        <paragraph>
         The available prior knowledge is modeled in terms of FOL predicates. Let {a mathematical formula}B:={false,true} and let us denote the paper and author domains by {a mathematical formula}P and {a mathematical formula}A, respectively. Notice that while {a mathematical formula}P∈Rd, {a mathematical formula}A is simply a set of author identifiers. Let us define the following predicates according to the relational representation in Fig. 3:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} When considering all the categories {a mathematical formula}i=1,…,10, the knowledge base (KB) that we use to represent the learning task is composed of 52 rules:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
        </paragraph>
        <paragraph>
         The 0 formulas express the supervised data. The 10 i formulas state that papers tend to cite other papers of the same category, while the ii ones state that co-authors belong to the same research area. The iii formulas enforce the coherence of the categories given to papers and authors. iv is a formula in Disjunctive Normal Form stating the exclusive classification assumption ({a mathematical formula}[¬]i≠j adds a negation in front of each predicate excluding the j-th), such that each paper is assigned to one and only one of the 10 classes. Finally, v states the close-world assumption forcing each author to be assigned to at least one of the 10 classes.
        </paragraph>
       </section>
       <section>
        <section-title>
         Results and discussion
        </section-title>
        <paragraph>
         In a first experiment we validated the dom heuristic proposed in Section 6.2. In particular, SBR was tested using the following configurations:
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}(0,i,ii,iii,iv,v): introducing all the constraints together at the beginning of training;
         </list-item>
         <list-item label="•">
          {a mathematical formula}(0),(i,ii,iii,iv,v): learning from the supervised data first and, after the training data has been learned, introducing all the other constraints. In particular, the second group of constraints is added when the gradient module becomes small, which was empirically observed to happen after around 30 iterations of gradient decent in this experiment;
         </list-item>
         <list-item label="•">
          {a mathematical formula}(0),(i,ii,iii),(iv),(v): splitting the training into multiple stages, where the constraints are sequentially introduced according to the dom heuristic by looking at the degree of freedom in the assignments of each formula. A new set of constraints is added when the gradient module becomes small. The formulas in the sets {a mathematical formula}(i,ii,iii) have the same degree of freedom (possible different assignments to the query predicates verifying the formula) and are introduced together.
         </list-item>
        </list>
        <paragraph>
         Table 1 reports the classification scores for the 3 different learning schemas, obtained on the test set for patterns in the paper and research area domains. Since each pattern in the paper domain belongs to a single class (single-label classification task), standard classification accuracy has been used as metric for this task. The F1 metric has been used for the research area domain, since this is a multi-label multi-class classification task. For all configurations, SBR used the minimum t-norm and the linear kernel with meta-parameters selected to maximize the classification accuracy for the paper category on the validation set of the considered fold. It is clear from the results that the dom heuristic effectively breaks the learning complexity, allowing to find better solutions. As shown by the smaller gains from moving from the {a mathematical formula}(0),(i,ii,iii,iv,v) to the {a mathematical formula}(0),(i,ii,iii),(iv),(v) learning schema, a significant portion of the gains comes from introducing higher level semantic rules after the predicates have been approximated by fitting the supervised data.
        </paragraph>
        <paragraph>
         A comparison against Markov Logic Networks both in their discrete (MLN) and hybrid versions (HMLN) has been carried out by using the implementation provided by the Alchemy software package{sup:3} using discriminative weight training optimized via rescaled conjugate gradient, which provided the best results on this task. MLNs have been trained using the same knowledge base previously employed by SBR, where rules iv and v has been added as hard constraints. Furthermore, the following formulas have been added to take care of the bag-of-words representation of the page by linking the words to the document categories in the MLN rule definitions:{a mathematical formula} where x is a variable spanning over all the papers and, following the Alchemy syntax, the “+” means that one rule is added for each {a mathematical formula}(word,class) pair. This follows the experimental set up for text categorization suggested in Domingos et al. [12]. In the case of Hybrid Markov Logic Networks, the TF-IDF score is used to associate a numeric feature to each ground clause for the previous rule. In particular, any TF-IDF score below 1 has been gaussian decayed using Alchemy soft equality penalty function.
        </paragraph>
        <paragraph>
         In order to compare against Probabilistic Soft Logic (PSL), some modifications to the KB have been required, since PSL can process only rules with conjunctive bodies and single-literal head (e.g. any propositional formula obtained after the evaluation of the grounded predicates must be a Horn Clause). Therefore, each formula, creating a manifold structure over the authors or papers, has been split into two corresponding formulas for the PSL evaluation, such that the new formulas can be processed by PSL and the logical AND of them is equivalent to the original formulation. For example the first manifold rule in SBR has been replaced by the pair of formulas:{a mathematical formula} The same procedure has been performed for the formulas expressing the manifold with respect to the CoAuthor and Author predicates. The formulas implementing the logic OR operation over the classes cannot be implemented in PSL. Unlike SBR, PSL has no direct integration with an SVM processing the input pattern representations. However, like done in the Bröcheler et al. [5] for their Wikipedia Category Prediction experiment, PSL can employ the output of a previously trained feature-based classifier as a prior for its assignments. This was done by reusing the same SVMs previously trained and then adding the following rules to the PSL learning task definition:{a mathematical formula} where {a mathematical formula}SVMCategory(x,i) is an evidence predicate holding a true value iff the SVM assigns the tag i to the pattern x (e.g. the SVM trained for the tag i provides an output greater than 0 when processing as input the pattern x). PSL formula weights have been learned over the validation set using the LazyMaxLikelihoodMPE algorithm (Most Probable Explanation Max likelihood), which provided the best results on the task and is also the employed training algorithm in all the examples provided with the PSL software package.
        </paragraph>
        <paragraph>
         SBR has also been compared against standard, Structured and Transductive SVMs for the paper classification task. Structured SVMs have been used to perform native multi-class classification as explained by Tsochantaridis et al. [47]. Like for SBR, a linear kernel with meta-parameters selected to maximize the accuracy and F1 scores on the validation set have been used for all SVM experiments. The libSVM software package{sup:4} was used as implementation for plain SVMs, while the SVMlight software package{sup:5} was used for Transductive and Structured SVM. Since authors are not associated with a feature representation, they can only be classified by a purely relational approach and no comparison against SVM-based classification schemas was possible.
        </paragraph>
        <paragraph>
         PSL has been tested using either SVM or Transductive SVM as base classifier providing a prior for the classification. These two versions will been indicated as PSL-SVM and PSL-TSVM, respectively.
        </paragraph>
        <paragraph>
         Table 2 reports the accuracy and F1 scores on the test set for patterns representing papers and authors, respectively. Since some methods do not allow to express exclusive classification via an explicit rule in the KB, the output class for these methods has been selected as the class associated to the highest value among the classification outputs for each pattern.
        </paragraph>
        <paragraph>
         Metrics in bold represent statistically significant gains (95%) over all the other classifiers. Since this is a transductive learning task, it is no surprise that Transductive SVMs are the best performers among the non-relational classifiers. Both PSL-SVM and PSL-TSVM outperform the corresponding base non-relational classifiers, and PSL-TSVM outperforms PSL-SVM because of the better performing base classifier. The SBR model outperforms all the non-relational classifiers, since it can integrate a much richer prior knowledge. The large improvement of SBR over the tested SRL models is due to two important factors. First, SBR provides a larger flexibility in designing the KB: some rules had to be dropped or modified in the PSL definitions, not having a conjunctive body and single head. Secondly, SBR integrates the processing of the input feature representations and of the higher level logic knowledge. This means that SBR natively back-propagates the output of the inference process performed during learning using the KB to the underlying SVMs, significantly improving their performances when little supervised data is available. PSL uses a frozen SVM as prior for its classifications and has no ability to improve the underlying classifier using the unsupervised data. This is huge advantage for SBR in a transductive context with a large portion of unsupervised data.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="9.2">
      <section-title>
       Collective classification in WebKB
      </section-title>
      <paragraph>
       This experiment evaluates the proposed collective classification approach on the WebKB benchmark. The WebKB dataset is a relational dataset which consists of labeled web pages from the computer science departments of 4 universities. We used the version of the dataset from Craven and Slattery [7], used also in many other following papers [29], [32], which features about 4100 webpages and {a mathematical formula}10000 hyperlinks. Each webpage is associated with a vectorial representation of its content represented as bag-of-words, while each link is associated with its anchor text. Each webpage belongs to at least one of the 5 categories: person, course, department, researchproject, other. In addition, the anchor's links belong at least one of the 5 classes: toPerson, toCourse, toDepartment, toResearchProject, toOther, depending on the category of the pointed webpage. The goal of the benchmark is to predict the categories of the webpages and of the links from the given data.
      </paragraph>
      <paragraph>
       Each university represents an independent world, therefore a 4-fold crossvalidation is the most natural evaluation procedure to evaluate the performance of classification. 4 folds are generated by keeping the data of one university out as test set, then selecting the first two other remaining universities as training set and the last one as validation data.
      </paragraph>
      <section>
       <section>
        <section-title>
         Knowledge base
        </section-title>
        <paragraph>
         Let us assume that {a mathematical formula}W and {a mathematical formula}A denote the set of web pages and anchor text identifiers, respectively. {a mathematical formula}B represents a Boolean value. We consider the following predicates, following the relational representation shown in Fig. 4{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
        </paragraph>
        <paragraph>
         The following KB was used for the task:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The 0 formulas express the fitting of the supervised data. The i formulas state that linked pages tend to be of the same class (manifold regularization), while the ii ones dictate classification consistency among the predicted class for pages and anchors. Formulas iii and iv impose the close-world assumption, forcing each web page and anchor to belong to at least one of the 5 classes in the corresponding domain. The overall knowledge base consists of 42 rules.
        </paragraph>
        <paragraph>
         The following formulas representing how words are correlated to webpage and link categories have also been added to the MLN rule definitions:{a mathematical formula}{a mathematical formula} where the “+” is used to define one rule for each {a mathematical formula}(word,class) and {a mathematical formula}(word,anchorclass) pairs, respectively. The rules {a mathematical formula}iii,iv have been added as hard constraints in the MLN experiments as they should be always verified.
        </paragraph>
        <paragraph>
         For the PSL experimental comparison, the same procedure described in the previous experiment has been used to express the manifolds built by the Link and LinkTo predicates. The input pattern representations have been embedded into the PSL classification by adding a set of rules expressing the consistency between PSL and SVM class assignments, where one SVM has been previously trained for each class. PSL formula weights have been learned over the validation set using the LazyMaxLikelihoodMPE algorithm.
        </paragraph>
       </section>
       <section>
        <section-title>
         Results and discussion
        </section-title>
        <paragraph>
         Since the training set for each single fold is completely supervised, one SBR classifier per fold has been trained using the 0 rules converted via the minimum t-norm (e.g. a plain kernel machine with a linear kernel). Classification performance on the validation set was used to select the optimal regularization parameter for each fold. The output of the learned functions has been used to initialize the collective classification step for the validation and test sets. In particular, collective classification was performed separately on the validation set of each fold using different {a mathematical formula}λc parameters, then selecting the {a mathematical formula}λc¯ value providing the best results for each fold. Finally, collective classification was performed on the test set of each fold, using {a mathematical formula}λc=λc¯, as selected at the previous step. The results obtained by Semantic Based Regularization using the minimum t-norm and collective classification (SBR-CC) have been compared against a plain SVM and Markov Logic Network (MLN). We used the Alchemy software implementation of MLNs, using discriminative weight training optimized via rescaled conjugate gradient. The libSVM software package was used to implement plain SVMs using a linear kernel. The SVM C parameter (trade off between model complexity and fitting of the supervised data) was selected to maximize the classification metrics on the validation set.
        </paragraph>
        <paragraph>
         Table 3 shows the F1 and AUC scores obtained on the test set for the webpage and anchor link categories as an average over the 4 folds. SVM classification metrics are very good for webpages, where the rich feature-based representations allow to well discriminate the patterns. SVM performances are much worse for anchors, where the anchor text represented in the feature vector is small, noisy and often not very representative. MLNs perform slightly worse than SVMs on the webpage classification task, because MLNs do not get full advantage of the information available in the feature vectors. On the other hand, MLNs can get advantage of the available KB to improve the classification of the anchors with respect to SVMs. PSL performs quite well on the webpage classification task thanks to the good performance of its base classifier. However, the less rich additional KB that can be integrated in PSL limits its performance on the anchor patterns. SBR-CC is the best performer on both domains (even if with a small margin over the best competitor for each separate domains): it can fully get advantage of the feature-based representations, plus it can perform inference over the anchor domain using the entire KB.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="9.3">
      <section-title>
       Arnetminer
      </section-title>
      <paragraph>
       The Arnetminer Movie benchmark{sup:6} is a relational dataset containing information about movies and associated directors, writers and actors. The Arnetminer dataset assigns a set of tags to each movie. We selected all the movies with at least one tag containing one of the 12 most common keywords: horror, drama, comedy, television, teen, musical, adventure, western, mystery, thriller and biographical. Each of these tags was assumed to correspond to an underlying genre that we want to predict. The goal of this experiment is to predict the movie genres by looking at the movie title, represented as bag-of-words. Please note that this is a multi-label dataset, since movies can be associated to multiple genres. The movies have been split into three sets: one set composed by the movies released up to the year 1979, another by the movies from 1980 to 1997 and, finally, and all later movies have been added to the last set. The resulting datasets contain 7567, 4234 and 5653 movies, respectively.
      </paragraph>
      <paragraph>
       The first, second and third sets form the pools from which the training, validation and test data are selected for the single experiments, respectively. This is to simulate a real world scenario, where training is performed at some point in time over some available previous data and then the trained model is used to perform predictions over newly received data. A variable percentage of supervised labels from the movies in the first and second sets has been kept for training to evaluate how the performance is affected by the amount of labeled data. The remaining unlabeled patterns are still provided in the training set as unsupervised data. 5 different folds have been generated by performing different samples for each percentage of labels that are kept available in the training and validation sets.
      </paragraph>
      <paragraph>
       Together with the rules expressing the fitting of the supervised data, the following rules have been added as prior knowledge for each tag {a mathematical formula}Ci of the dataset:{a mathematical formula} to express the fact that movies sharing the same director, producer or writer tend to belong to the same genres. The following two rules for each tag {a mathematical formula}Ci express the Transductive SVM assumption:{a mathematical formula}{a mathematical formula} where N is the overall number of available movies in the considered dataset and {a mathematical formula}n,m are estimated looking at the distribution of {a mathematical formula}Ci,¬Ci in the training data of each fold, respectively.
      </paragraph>
      <paragraph>
       After training the SBR models using the minimum t-norm and the linear kernel for different {a mathematical formula}λc meta-parameters, the best model has been selected on the validation set. Finally, Semantic Based Regularization collective classification (SBR-CC) has been performed over the test set using the selected model. The SBR-CC results have been compared against Semantic Based Regularization (SBR), where no collective classification is performed on the test set, but the trained kernel machines are directly used to perform the predictions. Furthermore, SBR-CC was compared against standard SVM (using only supervised labels), Transductive SVM (TSVM), Laplacian SVM (LSVM) using the same director, producer or writer rules to build the manifold of data and Probabilistic Soft Logic using SVM (PSL-SVM) and TSVM classifiers as priors (PSL-TSVM). One separate binary classifier for each class has been built for SVM, LSVM, TSVM. In particular, the same software simulator used for the experiments in Melacci and Belkin [31] was used as implementation of Laplacian SVMs. The same software simulators used in the previous experiments have been employed as implementations of SVMs and TSVMs. All SVM-based classifiers employed a linear kernel and the models have been trained using different meta-parameters. The best model has been fold-by-fold selected by cross validation on the validation set.
      </paragraph>
      <paragraph>
       Similarly to the previous experiments, each formula, creating a manifold structure over the movies, has been split into two corresponding formulas for the PSL evaluation. For example the first manifold rule in SBR has been replaced by the pair of formulas in the PSL rule definitions:{a mathematical formula} The same procedure has been performed for the formulas expressing the manifold with respect to the SameProducer and SameWriter predicates. The formulas implementing the Transductive SVM assumption cannot be expressed in PSL and have been not used for this experimental comparison. Like for the previous experiments, the rules expressing the consistency between PSL class assignments and the output of the SVMs trained for each class have been added to the PSL rule definitions. PSL formula weights have been learned over the validation set using the LazyMaxLikelihoodMPE algorithm, which provided the best results on this task. Finally, the PSL collective classification step using the rule weights learned in training has been performed over the test set. The output of the collective classification step has been used to determine PSL classification performances.
      </paragraph>
      <paragraph>
       Fig. 5 reports the classification results as an average over the 5 folds. SVMs are, as expected, the worst performers on this task, as they are the only tested model that cannot benefit from the unsupervised data seen in training. PSL, TSVM and LSVM perform similarly, but they are outperformed by SBR. PSL-TSVM takes advantage of the better performing base classifier and outperforms PSL-SVM. Both PSL versions perform worse than SBR in this task, because PSL cannot get advantage of the unsupervised data to improve the underlying classifiers that it uses as classification priors. Finally, SBR with collective classification (SBR-CC) slightly improves over SBR in all tested configurations by enforcing the rules also over the test set.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>