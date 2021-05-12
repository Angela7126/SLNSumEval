<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    kLog: A language for logical and relational learning with kernels.
   </title>
   <abstract>
    We introduce kLog, a novel approach to statistical relational learning. Unlike standard approaches, kLog does not represent a probability distribution directly. It is rather a language to perform kernel-based learning on expressive logical and relational representations. kLog allows users to specify learning problems declaratively. It builds on simple but powerful concepts: learning from interpretations, entity/relationship data modeling, logic programming, and deductive databases. Access by the kernel to the rich representation is mediated by a technique we call graphicalization: the relational representation is first transformed into a graph — in particular, a grounded entity/relationship diagram. Subsequently, a choice of graph kernel defines the feature space. kLog supports mixed numerical and symbolic data, as well as background knowledge in the form of Prolog or Datalog programs as in inductive logic programming systems. The kLog framework can be applied to tackle the same range of tasks that has made statistical relational learning so popular, including classification, regression, multitask learning, and collective classification. We also report about empirical comparisons, showing that kLog can be either more accurate, or much faster at the same level of accuracy, than Tilde and Alchemy. kLog is GPLv3 licensed and is available at http://klog.dinfo.unifi.it along with tutorials.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The field of statistical relational learning (SRL) is populated with a fairly large number of models and alternative representations, a state of affairs often referred to as the “SRL alphabet soup” [1], [2]. Even though there are many differences between these approaches, they typically extend a probabilistic representation (most often, a graphical model) with a logical or relational one [3], [4]. The resulting models then define a probability distribution over possible worlds, which are typically (Herbrand) interpretations assigning a truth value to every ground fact.
     </paragraph>
     <paragraph>
      However, the machine learning literature contains — in addition to probabilistic graphical models — several other types of statistical learning methods. In particular, kernel-based learning and support vector machines are amongst the most popular and powerful machine learning systems that exist today. But this type of learning system has — with a few notable exceptions to relational prediction [5], [6] — not yet received a lot of attention in the SRL literature. Furthermore, while it is by now commonly accepted that frameworks like Markov logic networks (MLNs) [7], probabilistic relational models (PRMs) [8], or probabilistic programming [3], [4] are general logical and relational languages that support a wide range of learning tasks, there exists today no such language for kernel-based learning. It is precisely this gap that we ultimately want to fill.
     </paragraph>
     <paragraph>
      This paper introduces the kLog language and framework for kernel-based logical and relational learning. The key contributions of this framework are threefold: (1) kLog is a language that allows users to declaratively specify relational learning tasks in a similar way as statistical relational learning and inductive logic programming approaches but it is based on kernel methods rather than on probabilistic modeling; (2) kLog compiles the relational domain and learning task into a graph-based representation using a technique called graphicalization; and (3) kLog uses a graph kernel to construct the feature space where eventually the learning takes place. This whole process is reminiscent of knowledge-based model construction in statistical relational learning. We now sketch these contributions in more detail and discuss the relationships with statistical relational learning.
     </paragraph>
     <paragraph>
      One contribution of this paper is the introduction of the kLog language and framework for kernel-based logical and relational learning. kLog is embedded in Prolog (hence the name) and allows users to specify different types of logical and relational learning problems at a high level in a declarative way. kLog adopts, as many other logical and relational learning systems, the learning from interpretations framework [9]. In this way, the entities (or objects) and the relationships amongst them can be naturally represented. However, unlike typical statistical relational learning frameworks, kLog does not employ a probabilistic framework but is rather based on linear modeling in a kernel-defined feature space.
     </paragraph>
     <paragraph>
      kLog constitutes a first step into the direction of a general kernel-based SRL approach. kLog generates a set of features starting from a logical and relational learning problem and uses these features for learning a (linear) statistical model. This is not unlike Markov logic but there are two major differences. First, kLog is based on a linear statistical model instead of a Markov network. Second, the feature space is not immediately defined by the declared logical formulae but it is constructed by a graph kernel, where nodes in the graph correspond to entities and relations, some given in the data, and some (expressing background knowledge) defined declaratively in Prolog. Complexity of logical formulae being comparable, graph kernels leverage a much richer feature space than MLNs. In order to learn, kLog essentially describes learning problems at three different levels. The first level specifies the logical and relational learning problem. At this level, the description consists of an E/R-model describing the structure of the data and the data itself, which is similar to that of traditional SRL systems [10]. The data at this level is then graphicalized, that is, the interpretations are transformed into graphs. This leads to the specification of a graph learning problem at the second level. Graphicalization is the equivalent of knowledge-based model construction. Indeed, SRL systems such as PRMs and MLNs also (at least conceptually) produce graphs, although these graphs represent probabilistic graphical models. Finally, the graphs produced by kLog are turned into feature vectors using a graph kernel, which leads to a statistical learning problem at the third level. Again there is an analogy with systems such as Markov logic as the Markov network that is generated in knowledge-based model construction lists also the features. Like in these systems, kLog features are tied together as every occurrence is counted and is captured by a single same parameter in the final linear model.
     </paragraph>
     <paragraph>
      It is important to realize that kLog is a very flexible architecture in which only the specification language of the first level is fixed; at this level, we employ an entity/relationship (E/R) model. The second level is then completely determined by the choice of the graph kernel. In the current implementation of kLog that we describe in this paper, we employ the neighborhood subgraph pairwise distance kernel (NSPDK) [11] but the reader should keep in mind that other graph kernels can be incorporated. Similarly, for learning the linear model at level three we mainly experimented with variants of SVM learners but again it is important to realize that other learners can be plugged in. This situation is akin to that for other statistical relational learning representations, for which a multitude of different inference and learning algorithms has been devised (see also Section 8 for a discussion of the relationships between kLog and other SRL systems).
     </paragraph>
     <paragraph>
      In the next section, we illustrate the main steps of kLog modeling with a complete example in a real world domain. In Section 3, we formalize the assumed statistical setting for supervised learning from interpretations, provide some background on statistical modeling from a relational learning point of view, and position kLog more clearly in the context of related systems such as Markov logic, M{sup:3}N [6], etc. In Section 4, we formalize the semantics of the language and illustrate what types of learning problems can be formulated in the framework. Further examples are given in Section 5. The graphicalization approach and the graph kernel are detailed in Section 6. Some empirical evaluation is reported in Section 7 and, finally, the relationships to other SRL systems are discussed in Section 8.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      A kLog example
     </section-title>
     <paragraph>
      Before delving into the technical details of kLog, we illustrate the different steps on a real-life example using the UW-CSE data set prepared by Domingos et al. for demonstrating the capabilities of MLNs [7]. Anonymous data was obtained from the University of Washington Department of Computer Science and Engineering. Basic entities include persons (students or professors), scientific papers, and academic courses. Available relations specify, e.g., whether a person was the author of a certain paper, or whether he/she participated in the teaching activities of a certain course. The learning task consists of predicting students' advisors, i.e., to predict the binary relation advised_by between students and professors.
     </paragraph>
     <section label="2.1">
      <section-title>
       Data format
      </section-title>
      <paragraph>
       Data comes in the form of true ground atoms, under the closed-world assumption. Since (first-order logic) functions are not allowed in the language, a ground atom is essentially like a tuple in a relational database, for example taught_by(course170,person211,winter_0102).
      </paragraph>
      <paragraph>
       kLog learns from interpretations. This means that the data is given as a set of interpretations (or logical worlds) where each interpretation is a set of ground atoms which are true in that world. In this example there are five interpretations: ai, graphics, language, systems, and theory, corresponding to different research groups in the department. For instance, a fragment of the interpretation ai is shown in Listing 1.
      </paragraph>
      <paragraph>
       All ground atoms in a particular interpretation together form an instance of a relational database and the overall data set consists of several (disjoint) databases.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Data modeling and learning
      </section-title>
      <paragraph>
       The first step in kLog modeling is to describe the domain using a classic database tool: entity relationship diagrams. We begin by modeling two entity sets: student and professor, two unary relations: in_phase and has_position, and one binary relation: advised_by (which is the target in this example). The diagram is shown in Fig. 1. The kLog data model is written using the fragment of code of Listing 2.
      </paragraph>
      <paragraph>
       Every entity or relationship that kLog will later use to generate features (see feature generation below) is declared by using the special keyword signature. Signatures are similar to the declarative bias used in inductive logic programming systems. There are two kinds of signatures, annotated by the reserved words extensional and intensional. In the extensional case, all ground atoms have to be listed explicitly in the data file; in the intensional case, ground atoms are defined implicitly using Prolog definite clauses. A signature has a name and a list of arguments with types. A type is either the name of an entity set (declared in some other signature) or the special type property used for numerical or categorical attributes. In the ground atoms, constants that are not properties are regarded as identifiers and are simply used to connect ground atoms (these constants disappear in the result of the graphicalization procedure explained below).{sup:1}
      </paragraph>
      <paragraph>
       One of the powerful features of kLog is its ability to introduce novel relations using a mechanism resembling deductive databases. Such relations are typically a means of injecting domain knowledge. In our example, it may be argued that the likelihood that a professor advises a student increases if the two persons have been engaged in some form of collaboration, such as co-authoring a paper, or working together in teaching activities. In Listing 3 we show two intensional signatures for this purpose. An intensional signature declaration must be complemented by a predicate (written in Prolog) which defines the new relation. When working on a given interpretation, kLog asserts all the true ground atoms in that interpretation in the Prolog database and collects all true groundings for the predicate associated with the intensional signature. Intensional signatures can also be effectively exploited to introduce aggregated attributes [9]. The last signature in Listing 3 shows for example how to count the number of papers a professor and a student have published together.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Graphicalization
      </section-title>
      <paragraph>
       Graphicalization is our approach to capture the relational structure of the data by means of a graph. It enables the use of kernel methods in SRL via a graph kernel, which measures the similarity between two graphs. The procedure maps a set of ground atoms into a bipartite undirected graph whose nodes are true ground atoms and whose edges connect an entity atom to a relationship atom if the identifier of the former appears as an argument in the latter. The graph resulting from the graphicalization of the ai interpretation is shown in Fig. 2.{sup:2} It is from this graph that kLog will generate propositional features (based on a graph kernel) for use in the learning procedure. The details of the graphicalization procedure and the kernel are given in Sections 6 and 6.2, respectively.
      </paragraph>
      <paragraph>
       Now that we have specified the inputs to the learning system, we still need to determine the learning problem. This is declared in kLog by designating one (or more) signature(s) as target (in this domain, the target relation is advised_by). Several library predicates are designed for training, e.g., kfold performs a k-fold cross validation. These predicates accept a list of target signatures which specifies the learning problem.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Statistical setting
     </section-title>
     <paragraph>
      Our general approach to construct a statistical model is based on the learning from interpretations setting [9]. An interpretation, or logical world, is a set of ground atoms z. We assume that interpretations are sampled identically and independently from a fixed and unknown distribution D. We denote by {a mathematical formula}{zi;i∈I} the resulting data set, where {a mathematical formula}I is a given index set (e.g., the first n natural numbers) that can be thought of as interpretation identifiers. Like in other statistical learning systems, the goal is to use a data sample to make some form of (direct or indirect) inference about this distribution.
     </paragraph>
     <paragraph>
      For the sake of simplicity, throughout this paper we will mainly focus on supervised learning. In this case, it is customary to think of data as consisting of two separate portions: inputs (called predictors or independent variables in statistics) and outputs (called responses or dependent variables). In our framework, this distinction is reflected in the set of ground atoms in a given interpretation. That is, z is partitioned into two sets: x (input or evidence atoms) and y (output or query atoms).
     </paragraph>
     <paragraph>
      The goal of supervised learning in this setting is to construct a prediction function f that maps the set of input atoms x (a partial interpretation) into a set of output atoms {a mathematical formula}f(x). To this end, a feature vector{sup:3}{a mathematical formula}ϕ(x,y) is associated with each complete interpretation {a mathematical formula}z=(x,y). A potential function based on the linear model {a mathematical formula}F(x,y)=w⊤ϕ(x,y) is then used to “score” the interpretation. Prediction (or inference) is the process of maximizing F with respect to y, i.e. {a mathematical formula}f(x)=argmaxy⁡F(x,y). Learning is the process of fitting w to the available data, typically using some statistically motivated loss function that measures the discrepancy between the prediction {a mathematical formula}f(xi) and the observed output {a mathematical formula}yi on the i-th training interpretation. This setting is related to other kernel-based approaches to structured output learning (e.g., [12]), which may be developed without associating a probabilistic interpretation with F.
     </paragraph>
     <paragraph>
      The above perspective covers a number of commonly used algorithms ranging from propositional to relational learning. To see this, consider first binary classification of categorical attribute–value data. In this case, models such as naive Bayes, logistic regression, and support vector machines (SVM) can all be constructed to share exactly the same feature space. Using indicator functions on attribute values as features, the three models use a hyperplane as their decision function: {a mathematical formula}f(x)=argmaxy∈{false,true}⁡w⊤ϕ(x,y) where for naive Bayes, the joint probability of {a mathematical formula}(x,y) is proportional to {a mathematical formula}exp⁡(w⊤ϕ(x,y)). The only difference between the three models is actually in the way w is fitted to data: SVM optimizes a regularized functional based on the hinge loss function, logistic regression maximizes the conditional likelihood of outputs given inputs (which can be seen as minimizing a smoothed version of the SVM hinge loss), and naive Bayes maximizes the joint likelihood of inputs and outputs. The last two models are often cited as an example of generative–discriminative conjugate pairs because of the above reasons [13].
     </paragraph>
     <paragraph>
      When moving up to a slightly richer data type like sequences (perhaps the simplest case of relational data), the three models have well known extensions: naive Bayes extends to hidden Markov models (HMMs), logistic regression extends to conditional random fields (CRFs) [14], and SVM extends to structured output SVM for sequences [15], [12]. Note that when HMMs are used in the supervised learning setting (in applications such as part-of-speech tagging) the observation x is the input sequence, and the states form the output sequence y (which is observed in training data). In the simplest version of these three models, {a mathematical formula}ϕ(x,y) contains a feature for every pair of states (transitions) and a feature for every state-observation pair (emissions). Again, these models all use the same feature space (see, e.g., [14] for a detailed discussion).
     </paragraph>
     <paragraph>
      When moving up to arbitrary relations, the three above models can again be generalized but many complications arise, and the large number of alternative models suggested in the literature has originated the SRL alphabet soup mentioned at the beginning of the paper. Among generative models, one natural extension of HMMs is stochastic context free grammars [16], which in turn can be extended to stochastic logic programs [17]. More expressive systems include probabilistic relational models (PRMs) [8] and Markov logic networks (MLNs) [7], when trained generatively. Generalizations of SVM for relational structures akin to context free grammars have also been investigated [12]. Among discriminative models, CRFs can be extended from linear chains to arbitrary relations [14], for example in the form of discriminative Markov networks [18] and discriminative Markov logic networks [7]. The use of SVM-like loss functions has also been explored in max-margin Markov networks (M{sup:3}N) [6]. These models can cope with relational data by adopting a richer feature space. kLog contributes to this perspective as it is a language for generating a set of features starting from a logical and relational learning problem and using these features for learning a (linear) statistical model.
     </paragraph>
     <paragraph>
      Table 1 shows the relationships among some of these approaches. Methods on the same row use similar loss functions, while methods in the same column can be arranged to share the same feature space. In principle, kLog features can be used with any loss.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The kLog language
     </section-title>
     <paragraph>
      A kLog program consists of:
     </paragraph>
     <list>
      <list-item label="•">
       a set of ground facts, embedded in a standard Prolog database, representing the data of the learning problem (see, e.g., Listing 1);
      </list-item>
      <list-item label="•">
       a set of signature declarations (e.g., Listing 2);
      </list-item>
      <list-item label="•">
       a set of Prolog predicates associated with intensional signatures (e.g., Listing 3);
      </list-item>
      <list-item label="•">
       a standard Prolog program which specifies the learning problem and makes calls to kLog library predicates.
      </list-item>
     </list>
     <section label="4.1">
      <section-title>
       Data modeling and signatures
      </section-title>
      <paragraph>
       In order to specify the semantics of the language, it is convenient to formalize the domain of the learning problem as a set of constants (objects) {a mathematical formula}C and a finite set of relations {a mathematical formula}R. Constants are partitioned into a set of entity identifiers{a mathematical formula}E (or identifiers for short) and set of property values{a mathematical formula}V. Identifiers are themselves partitioned into k entity-sets{a mathematical formula}E1,…,Ek. A ground atom {a mathematical formula}r(c1,…,cn) is a relation symbol (or predicate name) r of arity n followed by an n-tuple of constant symbols {a mathematical formula}ci. An interpretation (for the learning problem) is a finite set of ground atoms.
      </paragraph>
      <paragraph>
       The signature for a relation {a mathematical formula}r/m∈R is an expression of the form{a mathematical formula} where, for all {a mathematical formula}j=1,…,m, {a mathematical formula}typej∈{E1,…,Ek,V} and {a mathematical formula}namej is the name of the j-th column of r. If column j does not have type {a mathematical formula}V, then its name can optionally include a role field using the syntax {a mathematical formula}namej@rolej. If unspecified, {a mathematical formula}rolej is set to j by default. The level of a signature is either intensional or extensional. In the extensional case, all the atoms which contribute to every interpretation are those and only those listed in the data. In the intensional case, ground atoms are those which result from the Prolog intensional predicates using Prolog semantics (optionally with tabling). In this way, users may take advantage of many of the extensions of definite clause logic that are built into Prolog.
      </paragraph>
      <paragraph>
       The ability to specify intensional predicates through clauses (see an example in Listing 3) is most useful for introducing background knowledge in the learning process and common practice in inductive logic programming [9]. As explained in Section 6.2, features for the learning process are derived from a graph whose vertices are ground facts in the database; hence the ability to declare rules that specify relations directly translates into the ability to design and maintain features in a declarative fashion. This is a key characteristic of kLog and, in our opinion, one of the key reasons behind the success of related systems like Markov logic.
      </paragraph>
      <paragraph>
       In order to ensure the well-definedness of the subsequent graphicalization procedure (see Section 6), we introduce two additional database assumptions. First, we require that the primary key of every relation consists of the columns whose type belongs to {a mathematical formula}{E1,…,Ek} (i.e., purely of identifiers). This is perhaps the main difference between the kLog and the E/R data models. As it will become more clear in the following, identifiers are just placeholders and are kept separate from property values so that learning algorithms will not rely directly on their values to build a decision function.{sup:4}
      </paragraph>
      <paragraph>
       The relational arity of a relation is the length of its primary key. As a special case, relations of zero relational arity are admitted and they must consist of at most a single ground atom in any interpretation.{sup:5} Second, for every entity-set {a mathematical formula}Ei there must be a distinguished relation {a mathematical formula}r/m∈R that has relational arity 1 and key of type {a mathematical formula}Ei. These distinguished relations are called E-relations and are used to introduce entity-sets, possibly with {a mathematical formula}(m−1) attached properties as satellite data. The remaining {a mathematical formula}|R|−k relations are called R-relations or relationships,{sup:6} which may also have properties. Thus, primary keys for R-relations are tuples of foreign keys.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Supervised learning jobs
      </section-title>
      <paragraph>
       A supervised learning job in kLog is specified as a set of relations. We begin defining the semantics of a job consisting of a single relation. Without loss of generality, let us assume that this relation has signature{a mathematical formula} with {a mathematical formula}i(j)∈{1,…,k} for {a mathematical formula}j=1,…,n. Conventionally, if {a mathematical formula}n=0 there are no identifiers and if {a mathematical formula}m=0 there are no properties. Recall that under our assumptions the primary key of r must consist of entity identifiers (the first n columns). Hence, {a mathematical formula}n&gt;0 and {a mathematical formula}m&gt;0 implies that r represents a function with domain {a mathematical formula}Ei(1)×⋯×Ei(n) and range {a mathematical formula}Vm. If {a mathematical formula}m=0 then r can be seen as a function with a Boolean range.
      </paragraph>
      <paragraph>
       Having specified a target relation r, kLog is able to infer the partition {a mathematical formula}x∪y of ground atoms into inputs and outputs in the supervised learning setting. The output y consists of all ground atoms of r and all ground atoms of any intensional relation {a mathematical formula}r′ which depends on r. The partition is inferred by analyzing the dependency graphs of Prolog predicates defining intensional relations, using an algorithm reminiscent of the call graph computation in ViPReSS [19].
      </paragraph>
      <paragraph>
       We assume that the training data is a set of complete interpretations.{sup:7} During prediction, we are given a partial interpretation consisting of ground atoms x, and are required to complete the interpretation by predicting output ground atoms y. For the purpose of prediction accuracy estimation, we will be only interested in the ground atoms of the target relation (a subset of y).
      </paragraph>
      <paragraph>
       Several situations may arise depending on the relational arity n and the number of properties m in the target relation r, as summarized in Table 2. When {a mathematical formula}n=0, the declared job consists of predicting one or more properties of an entire interpretation, when {a mathematical formula}n=1 one or more properties of certain entities, when {a mathematical formula}n=2 one or more properties of pairs of entities, and so on. When {a mathematical formula}m=0 (no properties) we have a binary classification task (where positive cases are ground atoms that belong to the complete interpretation). Multiclass classification can be properly declared by using {a mathematical formula}m=1 with a categorical property, which ensures mutual exclusiveness of classes. Regression is also declared by using {a mathematical formula}m=1 but in this case the property should be numeric. Note that property types (numerical vs. categorical) are automatically inferred by kLog by inspecting the given training data. An interesting scenario occurs when {a mathematical formula}m&gt;1 so that two or more properties are to be predicted at the same time. A similar situation occurs when the learning job consists of several target relations. kLog recognizes that such a declaration defines a multitask learning job. However having recognized a multitask job does not necessarily mean that kLog will have to use a multitask learning algorithm capable of taking advantage of correlations between tasks (like, e.g., [20]). This is because, by design and in line with the principles of declarative languages, kLog separates “what” a learning job looks like and “how” it is solved by applying a particular learning algorithm. We believe that the separation of concerns at this level permits greater flexibility and extendability and facilitates plugging-in alternative learning algorithms (a.k.a. kLog models) that have the ability to provide a solution to a given job.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Implementation
      </section-title>
      <paragraph>
       kLog is currently embedded in Yap Prolog [21] and consists of three main components: (1) a domain-specific interpreter, (2) a database loader, and (3) a library of predicates that are used to specify the learning task, to declare the graph kernel and the learning model, and to perform training, prediction, and performance evaluation. The domain-specific interpreter parses the signature declarations (see Section 4.1), possibly enriched with intensional and auxiliary predicates. The database loader reads in a file containing extensional ground facts and generates a graph for each interpretation, according to the procedure detailed in Section 6. The library includes common utilities for training and testing. Most of kLog is written in Prolog except feature vector generation and the statistical learners, which are written in C++. kLog incorporates LibSVM [22] and Stochastic gradient descent [23] and can interface with arbitrary (external) SVM solvers by coding appropriate data conversion wrappers.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Examples
     </section-title>
     <paragraph>
      In Section 2 we have given a detailed example of kLog in a link prediction problem. The kLog setting encompasses a larger ensemble of machine learning scenarios, as detailed in the following examples, which we order according to growing complexity of the underlying learning task.
     </paragraph>
     <paragraph label="Example 5.1">
      Classification of independent interpretationsThis is the simplest supervised learning problem with structured input data and scalar (unstructured) output. For the sake of concreteness, let us consider the problem of small molecule classification as pioneered in the relational learning setting in [24]. This domain is naturally modeled in kLog as follows. Each molecule corresponds to one interpretation; there is one E-relation, atom, that may include properties such as element and charge; there is one relationship of relational arity 2, bond, that may include a bond_type property to distinguish among single, double, and resonant chemical bonds; there is finally a zero-arity relationship, active, distinguishing between positive and negative interpretations. A concrete example is given in Section 7.1.
     </paragraph>
     <paragraph label="Example 5.2">
      Regression and multitask learningThe above example about small molecules can be extended to the case of regression where the task is to predict a real-valued property associated with a molecule, such as its biological activity or its octanol/water partition coefficient (logP) [25]. Many problems in quantitative structure-activity relationships (QSAR) are actually formulated in this way. The case of regression can be handled simply by introducing a target relation with signature activity(act::property).If there are two or more properties to be predicted, one possibility is to declare several target relations, e.g., we might add logP(logp::property). Alternatively we may introduce a target relation such as:target_properties(activity::property,logp::property).Multitask learning can be handled trivially by learning independent predictors; alternatively, more sophisticated algorithms that take into account correlations amongst tasks (such as [26]) could be used.
     </paragraph>
     <paragraph label="Example 5.3">
      Entity classificationA more complex scenario is the collective classification of several entities within a given interpretation. We illustrate this case using the classic WebKB domain [27]. The data set consists of Web pages from four Computer Science departments and thus there are four interpretations: cornell, texas, washington, and wisconsin. In this domain there are two E-relations: page (for webpages) and link (for hypertextual links). Text in each page is represented as a bag-of-words (using the R-relation has) and hyperlinks are modeled by the R-relations link_to and link_from. Text associated with hyperlink anchors is represented by the R-relation has_anchor.The goal is to classify each Web page. There are different data modeling alternatives for setting up this classification task. One possibility is to introduce several unary R-relations associated with the different classes, such as course, faculty, project, and student. The second possibility is to add a property to the entity-set page, called category, and taking values on the different possible categories. It may seem that in the latter case we are just reifying the R-relations describing categories. However there is an additional subtle but important difference: in the first modeling approach it is perfectly legal to have an interpretation where a page belongs simultaneously to different categories. This becomes illegal in the second approach since otherwise there would be two or more atoms of the E-relation page with the same identifier.From a statistical point of view, since pages for the same department are part of the same interpretation and connected by hyperlinks, the corresponding category labels are interdependent random variables and we formally have an instance of a supervised structured output problem [28], that in this case might also be referred to as collective classification[18]. There are however studies in the literature that consider pages to be independent (e.g., [29]).
     </paragraph>
     <paragraph label="Example 5.4">
      One-interpretation domainsWe illustrate this case on the Internet Movie Database (IMDb) data set. Following the setup in [30], the problem is to predict “blockbuster” movies, i.e., movies that will earn more than $2 million in their opening weekend. The entity-sets in this domain are movie, studio, and individual. Relationships include acted_in(actor::individual, m::movie), produced(s::studio, m::movie), and directed(director::individual, m::movie). The target unary relation blockbuster(m::movie) collects positive cases. Training in this case uses a partial interpretation (typically movies produced before a given year). When predicting the class of future movies, data about past movies' receipts can be used to construct features (indeed, the count of blockbuster movies produced by the same studio is one of the most informative features [31]).A similar scenario occurs for protein function prediction. Assuming data for just a single organism is available, there is one entity set (protein) and a binary relation interact expressing protein–protein interaction [32], [33].
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Graphicalization and feature generation
     </section-title>
     <paragraph>
      The goal is to map an interpretation {a mathematical formula}z=(x,y) into a feature vector {a mathematical formula}ϕ(z)=ϕ(x,y)∈F (see Section 3). This enables the application of several supervised learning algorithms that construct linear functions in the feature space {a mathematical formula}F. In this context, {a mathematical formula}ϕ(z) can be either computed explicitly or defined implicitly, via a kernel function {a mathematical formula}K(z,z′)=〈ϕ(z),ϕ(z′)〉. Kernel-based solutions are very popular, sometimes computationally faster, and can exploit infinite-dimensional feature spaces. On the other hand, explicit feature map construction may offer advantages in our setting, in particular when dealing with large scale learning problems (many interpretations) and structured output tasks (exponentially many possible predictions). Our framework is based on two steps: first an interpretation z is mapped into an undirected labeled graph {a mathematical formula}Gz; then a feature vector {a mathematical formula}ϕ(z) is extracted from {a mathematical formula}Gz. Alternatively, a kernel function on pairs of graphs {a mathematical formula}K(z,z′)=K(Gz,Gz′) could be computed. The corresponding potential function is then defined directly as {a mathematical formula}F(z)=w⊤ϕ(z) or as a kernel expansion {a mathematical formula}F(z)=∑iciK(z,zi).
     </paragraph>
     <paragraph>
      The use of an intermediate graphicalized representation is novel in the context of propositionalization, a well-known technique in logical and relational learning [9] that transforms graph-based or relational data directly into an attribute–value learning format, or possibly into a multi-instance learning one.{sup:8} This typically results in a loss of information, cf. [9]. Our approach transforms the relational data into an equivalent graph-based format, without loss of information. After graphicalization, kLog uses the results on kernels for graph-based data to derive an explicit high-dimensional feature-based representation. Thus kLog directly upgrades these graph-based kernels to a fully relational representation. Furthermore, there is an extensive literature on graph kernels and virtually all existing solutions can be plugged into the learning from interpretations setting with minimal effort. This includes implementation issues but also the ability to reuse existing theoretical analyses. Finally, it is notationally simpler to describe a kernel and feature vectors defined on graphs, than to describe the equivalent counterpart using the Datalog notation.
     </paragraph>
     <paragraph>
      The graph kernel choice implicitly determines how predicates' attributes are combined into features.
     </paragraph>
     <section label="6.1">
      <section-title>
       Graphicalization procedure
      </section-title>
      <paragraph>
       Given an interpretation z, we construct a bipartite graph {a mathematical formula}Gz([Vz,Fz],Ez) as follows (see Appendix B for notational conventions and Fig. 2 for an example). Vertices:there is a vertex in {a mathematical formula}Vz for every ground atom of every E-relation, and there is a vertex in {a mathematical formula}Fz for every ground atom of every R-relation. Vertices are labeled by the predicate name of the ground atom, followed by the list of property values. Identifiers in a ground atom do not appear in the labels but they uniquely identify vertices. The tuple {a mathematical formula}ids(v) denotes the identifiers in the ground atom mapped into vertex v.Edges:{a mathematical formula}uv∈Ez if and only if {a mathematical formula}u∈Vz, {a mathematical formula}v∈Fz, and {a mathematical formula}ids(u)⊂ids(v). The edge uv is labeled by the role under which the identifier of u appears in v (see Section 4.1). Note that, because of our data modeling assumptions (see Section 4.1), the degree of every vertex {a mathematical formula}v∈Fz equals the relational arity of the corresponding R-relation. The degree of vertices in {a mathematical formula}Vz is instead unbounded and may grow really large in some domains (e.g., social networks or World-Wide-Web networks). The graphicalization process can be nicely interpreted as the unfolding of an E/R diagram over the data, i.e., the E/R diagram is a template that is expanded according to the given ground atoms (see Fig. 2). There are several other examples in the literature where a graph template is expanded into a ground graph, including the plate notation in graphical models [35], encoding networks in neural networks for learning data structures [36], and the construction of Markov networks in Markov logic [7]. The semantics of kLog graphs for the learning procedure is however quite different and intimately related to the concept of graph kernels, as detailed in the following section.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Graph kernel
      </section-title>
      <paragraph>
       Learning in kLog is performed using a suitable graph kernel on the graphicalized interpretations. While in principle any graph kernel can be employed, there are several requirements that the chosen kernel has to meet in practice. On the one hand, computational efficiency is very important, both with respect to the number of graphs, and with respect to the graph size, as the grounding phase in the graphicalization procedure can yield very large graphs. On the other hand, we need a general purpose kernel with a flexible bias to adapt to a wide variety of application scenarios. In the case of independent interpretations (as in Example 5.1, Example 5.2), any graph kernel (several exist in the literature, see e.g. [11], [37], [38], [39], [40], [41], [42] and references therein) can be directly applied to the result of the graphicalization procedure since there is exactly one graph for each interpretation. However, when the task requires to make predictions about tuples of entities within the same interpretation (as in Section 2 or in Example 5.3, Example 5.4) an immediate application of existing graph kernels (such as those in the above references) is not straightforward. Additionally, if the graph has vertices with large degree (as in Example 5.3), kernels based on hard subgraph matching may severely overfit the data.
      </paragraph>
      <paragraph>
       In the current implementation, we use an extension of NSPDK [11]. While the original kernel is suitable for sparse graphs with discrete vertex and edge labels, here we propose extensions to deal with soft matches (Section 6.2.4) and a larger class of graphs whose labels are tuples of mixed discrete and numerical types (Section 6.2.5). In Section 6.3 we finally introduce a variant of NSPDK with viewpoints, which can handle the case of multiple predictions within the same interpretation. Similar extensions could be devised for other kinds of kernels but we do not discuss them in this paper.
      </paragraph>
      <section label="6.2.1">
       <section-title>
        Kernel definition and notation
       </section-title>
       <paragraph>
        The NSPDK is an instance of a decomposition kernel, where “parts” are pairs of subgraphs (for more details on decomposition kernels see Appendix C). For a given graph {a mathematical formula}G=(V,E), and an integer {a mathematical formula}r≥0, let {a mathematical formula}Nrv(G) denote the subgraph of G rooted in v and induced by the set of vertices{a mathematical formula} where {a mathematical formula}d⋆(x,v) is the shortest-path distance between x and v.{sup:9} A neighborhood is therefore a topological ball with center v. Let us also introduce the following neighborhood-pair relation:{a mathematical formula} that is, relation {a mathematical formula}Rr,d identifies pairs of neighborhoods of radius r whose roots are exactly at distance d (Fig. 3). We define {a mathematical formula}κr,d over graph pairs as the decomposition kernel on the relation {a mathematical formula}Rr,d, that is:{a mathematical formula} where {a mathematical formula}Rr,d−1(G) indicates the multiset of all pairs of neighborhoods of radius r with roots at distance d that exist in G.
       </paragraph>
       <paragraph>
        We can now obtain a flexible parametric family of kernel functions by specializing the kernel κ. The general structure of κ is:{a mathematical formula} In the following, we assume{a mathematical formula} where 1 denotes the indicator function, {a mathematical formula}r(A) is the root of A and {a mathematical formula}ℓ(v) the label of vertex v. The role of {a mathematical formula}κroot is to ensure that only neighborhoods centered on the same type of vertex will be compared. Assuming a valid kernel for {a mathematical formula}κsubgraph (in the following sections we give details on concrete instantiations), we can finally define the NSPDK as:{a mathematical formula} For efficiency reasons we consider the zero-extension of K obtained by imposing an upper bound on the radius and the distance parameter: {a mathematical formula}Kr⁎,d⁎(G,G′)=∑r=0r⁎∑d=0d⁎κr,d(G,G′), that is, we limit the sum of the {a mathematical formula}κr,d kernels for all increasing values of the radius (distance) parameter up to a maximum given value {a mathematical formula}r⁎ ({a mathematical formula}d⁎). Furthermore we consider a normalized version of {a mathematical formula}κr,d, that is: {a mathematical formula}κˆr,d(G,G′)=κr,d(G,G′)κr,d(G,G)κr,d(G′,G′), to ensure that relations induced by all values of radii and distances are equally weighted regardless of the size of the induced part sets.
       </paragraph>
       <paragraph>
        Finally, it is easy to show that the NSPDK is a valid kernel as: (1) it is built as a decomposition kernel over the countable space of all pairs of neighborhood subgraphs of graphs of finite size; (2) the kernel over parts is a valid kernel; (3) the zero-extension to bounded values for the radius and distance parameters preserves positive definiteness and symmetry; and (4) so does the normalization step.
       </paragraph>
      </section>
      <section label="6.2.2">
       <section-title>
        Subgraph kernels
       </section-title>
       <paragraph>
        The role of {a mathematical formula}κsubgraph is to compare pairs of neighborhood graphs extracted from two graphs. The application of the graphicalization procedure to diverse relational data sets can potentially induce graphs with significantly different characteristics. In some cases (discrete property domains) an exact matching between neighborhood graphs is appropriate, in other cases however (continuous properties domains) it is more appropriate to use a soft notion of matching.
       </paragraph>
       <paragraph>
        In the following sections, we introduce variants of {a mathematical formula}κsubgraph to be used when the atoms in the relational data set can maximally have a single discrete or continuous property, or when more general tuples of properties are allowed.
       </paragraph>
      </section>
      <section label="6.2.3">
       <section-title>
        Exact graph matching
       </section-title>
       <paragraph>
        An important case is when the atoms, that are mapped by the graphicalization procedure to the vertex set of the resulting graph, can maximally have a single discrete property. In this case, an atom {a mathematical formula}r(c) becomes a vertex v, whose label is obtained by concatenation of the signature name and the attribute value. In this case, {a mathematical formula}κsubgraph has the following form:{a mathematical formula} where 1 denotes the indicator function and ≅ isomorphism between graphs. Note that {a mathematical formula}1A≅A′ is a valid kernel between graphs under the feature map {a mathematical formula}ϕcl that transforms A into {a mathematical formula}ϕcl(A), a sequence of all zeros except the i-th element equal to 1 in correspondence to the identifier for the canonical representation of A[43], [44].
       </paragraph>
       <paragraph>
        Evaluating the kernel in Eq. (8) requires as a subroutine graph isomorphism, a problem for which it is unknown whether polynomial algorithms exist. Algorithms that are in the worst case exponential but that are fast in practice do exist [43], [44]. For special graph classes, such as bounded degree graphs [45], there exist polynomial time algorithms. However, since it is hard to limit the type of graph produced by the graphicalization procedure (e.g., cases with very high vertex degree are possible as in general an entity atom may play a role in an arbitrary number of relationship atoms), we prefer an approximate solution with efficiency guarantees based on topological distances similar in spirit to [46].
       </paragraph>
       <paragraph>
        The key idea is to compute an integer pseudo-identifier for each graph such that isomorphic graphs are guaranteed to bear the same number (i.e., the function is a graph invariant), but non-isomorphic graphs are likely to bear a different number. A trivial identity test between the pseudo-identifiers then approximates the isomorphism test. Appendix D details the computation of the pseudo-identifier.
       </paragraph>
      </section>
      <section label="6.2.4">
       <section-title>
        Soft matches
       </section-title>
       <paragraph>
        The idea of counting exact neighborhood subgraphs matches to express graph similarity is adequate when the graphs are sparse (that is, when the edge and the vertex set sizes are of the same order) and when the maximum vertex degree is low. However, when the graph is not sparse or some vertices exhibit large degrees, the likelihood that two neighborhoods match exactly quickly approaches zero, yielding a diagonal dominant kernel prone to overfitting.{sup:10} In these cases a better solution is to relax the all-or-nothing type of match, allowing subgraphs to match partially or in a soft way. Although there exist several graph kernels that are based on this type of match, they generally suffer from very high computational costs [41]. To ensure efficiency, we use an idea introduced in the Weighted Decomposition Kernel [47]: given a subgraph, we consider only the multinomial distribution (i.e., the histogram) of the labels, discarding all structural information. In the soft match kernel (Fig. 4), the comparison between two pairs of neighborhood subgraphs is replaced by{sup:11}:{a mathematical formula} where {a mathematical formula}V(A) is the set of vertices of A. In words, for each pair of close neighborhoods, we build a histogram counting the vertices with the same label in either of the neighborhood subgraphs. The kernel is then computed as the dot product of the corresponding histograms.
       </paragraph>
      </section>
      <section label="6.2.5">
       <section-title>
        Tuples of properties
       </section-title>
       <paragraph>
        A standard assumption in graph kernels is that vertex and edge labels are elements of a discrete domain. However, in kLog the information associated with vertices is a tuple that can contain both discrete and real values. Here we extend NSPDK to allow both a hard and a soft match type over graphs with property tuples that can be discrete, real, or a mix of both types. While similar extensions can be conceived, in principle, for other graph kernels, the literature has mainly focused on kernels with single categorical labels. The key idea is to use the canonical vertex identifier (introduced in Section 6.2.3) to further characterize each property: in this way the kernel is defined only between tuples of vertices that correspond under isomorphism.
       </paragraph>
       <paragraph>
        The general structure of the kernel on the subgraph can be written as:{a mathematical formula} where, for an atom{sup:12}{a mathematical formula}r(c1,c2,…,cm) mapped into vertex v, {a mathematical formula}ℓ(v) returns the signature name r. {a mathematical formula}κsubgraph is a kernel that is defined over sets of vertices (atoms) and can be decomposed in a part that ensures matches between atoms with the same signature name, and a second part that takes into account the tuple of property values. In particular, depending on the type of property values and the type of matching required, we obtain the following six cases.
       </paragraph>
       <paragraph>
        Soft match for discrete tuples. When the tuples contain only discrete elements and one chooses to ignore the structure in the neighborhood graphs, then each property is treated independently. Formally:{a mathematical formula} where for an atom {a mathematical formula}r(c1,c2,…,cd,…,cm) mapped into vertex v, {a mathematical formula}propd(v) returns the property value {a mathematical formula}cd.
       </paragraph>
       <paragraph>
        Hard match for discrete tuples. When the tuples contain only discrete elements and one chooses to consider the structure, then each property key is encoded taking into account the identity of the vertex in the neighborhood graph and all properties are required to match jointly. In practice, this is equivalent to the hard match of Section 6.2.3 where the property value is replaced with the concatenation of all property values in the tuple. Formally, we replace the label {a mathematical formula}ℓ(v) in Eq. (10) with the labeling procedure {a mathematical formula}Lv explained in Section 6.2.3. In this way, each vertex receives a canonical label that uniquely identifies it in the neighborhood graphs. The double summation of {a mathematical formula}1ℓ(v)=ℓ(v′) in Eq. (10) is then performing the selection of the corresponding vertices v and {a mathematical formula}v′ in the two pairs of neighborhood that are being compared. Finally, we consider all the elements of the tuple jointly in order to identify a successful match:{a mathematical formula}
       </paragraph>
       <paragraph>
        Soft match for real tuples. To upgrade the soft match kernel to tuples of real values we replace the exact match with the standard product.{sup:13} The kernel on the tuple then becomes:{a mathematical formula}
       </paragraph>
       <paragraph>
        Hard match for real tuples. We proceed in an analogous fashion as for the hard match for discrete tuples, that is, we replace the label {a mathematical formula}ℓ(v) in Eq. (10) with the labeling procedure {a mathematical formula}Lv. In this case, however, we combine the real valued tuple of corresponding vertices with the standard product as in Eq. (13):{a mathematical formula}
       </paragraph>
       <paragraph>
        Soft match for mixed discrete and real tuples. When dealing with tuples of mixed discrete and real values, the contribution of the kernels on the separate collections of discrete and real attributes are combined via summation:{a mathematical formula} where indices d and c run exclusively over the discrete and continuous properties respectively.
       </paragraph>
       <paragraph>
        Hard match for mixed discrete and real tuples. In an analogous fashion, provided that {a mathematical formula}ℓ(v) in Eq. (10) is replaced with the labeling procedure {a mathematical formula}Lv (see Section 6.2.3) we have:{a mathematical formula} In this way, each vertex receives a canonical label that uniquely identifies it in the neighborhood graph. The discrete labels of corresponding vertices are concatenated and matched for identity, while the real tuples of corresponding vertices are combined via the standard dot product.
       </paragraph>
      </section>
      <section label="6.2.6">
       <section-title>
        Domain knowledge bias via kernel points
       </section-title>
       <paragraph>
        At times it is convenient, for efficiency reasons or to inject domain knowledge into the kernel, to be able to explicitly select the neighborhood subgraphs. We provide a way to do so, declaratively, by introducing the set of kernel points, a subset of {a mathematical formula}V(G) which includes all vertices associated with ground atoms of some specially marked signatures. We then redefine the relation {a mathematical formula}Rr,d(A,B,G) used in Eq. (4) like in Section 6.2.1 but with the additional constraints that the roots of A and B be kernel points.
       </paragraph>
       <paragraph>
        Kernel points are typically vertices that are believed to represent information of high importance for the task at hand. Vertices that are not kernel points contribute to the kernel computation only when they occur in the neighborhoods of kernel points. In kLog, kernel points are declared as a list of domain relations: all vertices that correspond to ground atoms of these relations become kernel points.
       </paragraph>
      </section>
     </section>
     <section label="6.3">
      <section-title>
       Viewpoints
      </section-title>
      <paragraph>
       The above approach effectively defines a kernel over interpretations{a mathematical formula} where {a mathematical formula}Gz is the result of graphicalization applied to interpretation z. For learning jobs such as classification or regression on interpretations (see Table 2), this kernel is directly usable in conjunction with plain kernel machines like SVM. When moving to more complex jobs involving, e.g., classification of entities or tuples of entities, the kernel induces a feature vector {a mathematical formula}ϕ(x,y) suitable for the application of a structured output technique where {a mathematical formula}f(x)=argmaxy⁡w⊤ϕ(x,y). Alternatively, we may convert the structured output problem into a set of independent subproblems as follows. For simplicity, assume the learning job consists of a single relation r of relational arity n. We call each ground atom of r a case. Intuitively, cases correspond to training targets or prediction-time queries in supervised learning. Usually an interpretation contains several cases corresponding to specific entities such as individual Web pages (as in Section 5.3) or movies (as in Section 5.4), or tuples of entities for link prediction problems (as in Section 2). Given a case {a mathematical formula}c∈y, the viewpoint of c, {a mathematical formula}Wc, is the set of vertices that are adjacent to c in the graph. In order to define the kernel, we first consider the mutilated graph {a mathematical formula}Gc where all vertices in y, except c, are removed (see Fig. 5 for an illustration). We then define a kernel {a mathematical formula}κˆ on mutilated graphs, following the same approach of the NSPDK, but with the additional constraint that the first endpoint must be in {a mathematical formula}Wc. The decomposition is thus defined as{a mathematical formula} We obtain in this way a kernel “centered” around case c:{a mathematical formula} and finally we let{a mathematical formula} This kernel corresponds to the potential{a mathematical formula} which is clearly maximized by maximizing, independently, all sub-potentials {a mathematical formula}w⊤ϕˆ(x,c) with respect to c.
      </paragraph>
      <paragraph>
       By following this approach, we do not obtain a collective prediction (individual ground atoms are predicted independently). Still, even in this reduced setting, the kLog framework can be exploited in conjunction with meta-learning approaches that surrogate collective prediction. For example, Prolog predicates in intensional signatures can effectively be used as expressive relational templates for stacked graphical models [48] where input features for one instance are computed from predictions on other related instances. Results in Section 7.2 for the “partial information” setting are obtained using a special form of stacking.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Parameterization in kLog
      </section-title>
      <paragraph>
       The kernels presented in this section, together with the graphicalization procedure, yield a statistical model working in a potentially very high-dimensional feature space. Although large-margin learners offer some robustness against high-dimensional representations, it is still the user's responsibility to choose appropriate kernel parameters ({a mathematical formula}r⁎ and {a mathematical formula}d⁎) to avoid overfitting. It should be noted that subgraphs in the NSPDK effectively act like templates which are matched against graphicalized interpretations for new data. Since identifiers themselves do not appear in the result of the graphicalization procedure, the same template can match multiple times realizing a form of parameter tying as in other statistical relational learning methods.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      kLog in practice
     </section-title>
     <paragraph>
      In this section, we illustrate the use of kLog in a number of application domains. All experimental results reported in this section were obtained using LibSVM in binary classification, multiclass, or regression mode, as appropriate.
     </paragraph>
     <section label="7.1">
      <section-title>
       Predicting a single property of one interpretation
      </section-title>
      <paragraph>
       We now expand the ideas outlined in Example 5.1. Predicting the biological activity of small molecules is a major task in chemoinformatics and can help drug development [49] and toxicology [50], [51]. Most existing graph kernels have been tested on data sets of small molecules (see, e.g., [37], [38], [39], [41], [52]). From the kLog perspective the data consists of several interpretations, one for each molecule. In the case of binary classification (e.g., active vs. nonactive), there is a single target predicate whose truth state corresponds to the class of the molecule. To evaluate kLog we used two data sets. The Bursi data set [53] consists of 4337 molecular structures with associated mutagenicity labels (2401 mutagens and 1936 nonmutagens) obtained from a short-term in vitro assay that detects genetic damage. The Biodegradability data set [54] contains 328 compounds and the regression task is to predict their half-life for aerobic aqueous biodegradation starting from molecular structure and global molecular measurements.
      </paragraph>
      <paragraph>
       Listing 4 shows a kLog script for the Bursi domain. Relevant predicates in the extensional database are a/2, b/3 (atoms and bonds, respectively, extracted from the chemical structure), sub/3 (functional groups, computed by DMax Chemistry Assistant [55], [56]), fused/3, connected/4 (direct connection between two functional groups), linked/4 (connection between functional groups via an aliphatic chain). Aromaticity (used in the bond-type property of b/3) was also computed by DMax Chemistry Assistant. The intensional signatures essentially serve the purpose of simplifying the original data representation. For example atm/2 omits some entities (hydrogen atoms), and fg_fused/3 replaces a list of atoms by its length. In signature bnd(atom_1@b::atm,atom_2@b::atm) we use a role fieldb (introduced by the symbol @). Using the same role twice declares that the two atoms play the same role in the chemical bond, i.e. that the relation is symmetric. In this way, each bond can be represented by one tuple only, while a more traditional relational representation, which is directional, would require two tuples. While this may at first sight appear to be only syntactic sugar, it does provide extra abilities for modeling which is important in some domains. For instance, when modeling ring-structures in molecules, traditional logical and relational learning systems need to employ either lists to capture all the elements in a ring structure, or else need to include all permutations of the atoms participating in a ring structure. For rings involving 6 atoms, this requires {a mathematical formula}6!=720 different tuples, an unnecessary blow-up. Also, working with lists typically leads to complications such as having to deal with a potentially infinite number of terms. The target relation mutagenic has relational arity zero since it is a property of the whole interpretation.
      </paragraph>
      <paragraph>
       As shown in Table 3, results are relatively stable with respect to the choice of kernel hyperparameter (maximum radius and distance) and SVM regularization and essentially match the best results reported in [11] (AUROC {a mathematical formula}0.92±0.02) even without composition with a polynomial kernel. These results are not surprising since the graphs generated by kLog are very similar in this case to the expanded molecular graphs used in [11].
      </paragraph>
      <paragraph>
       We compared kLog to Tilde on the same task. A kLog domain specification can be trivially ported to background knowledge for Tilde. Both systems can then access the same set of Prolog atoms. Table 4 summarizes the results and can be compared with Table 3. Augmenting the language with the functional groups from [56] unexpectedly gave worse results in Tilde compared to a plain atom-bond language. The presence of some functional groups correlates well with the target and hence those tests are used near the root of the decision tree. Unfortunately, the greedy learner is unable to refine its hypothesis down to the atom level and relies almost exclusively on the coarse-grained functional groups. Such local-optimum traps can sometimes be escaped from by looking ahead further, but this is expensive and Tilde ran out of memory for lookaheads higher than 1. Tilde's built-in bagging can boost its results, especially when functional groups are used. A comparison between Table 4, Table 3 shows that Tilde with our language bias definition is not well suited for this problem.
      </paragraph>
      <paragraph>
       The kLog code for biodegradability is similar to Bursi but being a regression task we have a target relation declared as{a mathematical formula} We estimated prediction performance by repeating five times a ten-fold cross validation procedure as described in [54] (using exactly the same folds in each trial). Results — rooted mean squared error (RMSE), squared correlation coefficient (SCC), and mean absolute percentage error (MAPE) — are reported in Table 5. For comparison, the best RMSE obtained by kFOIL on this data set (and same folds) is {a mathematical formula}1.14±0.04 (kFOIL was shown to outperform Tilde and S-CART in [5]).
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Link prediction
      </section-title>
      <paragraph>
       We report here experimental results on the UW-CSE domain that we have already extensively described in Section 2. To assess kLog behavior we evaluated prediction accuracy according to the leave-one-research-group-out setup of [7], using the domain description of Listing 2, Listing 3, together with a NSPDK kernel with distance 2, radius 2, and soft match. Comparative results with respect to Markov logic are reported in Fig. 6 (MLN results published in [7]). The whole 5-fold procedure runs in about 20 seconds on a single core of a 2.5 GHz Core i7 CPU. Compared to MLNs, kLog in the current implementation has the disadvantage of not performing collective assignment but the advantage of defining more powerful features thanks to the graph kernel. Additionally, MLN results use a much larger knowledge base. The advantage of kLog over MLN in Fig. 6 is due to the more powerful feature space. Indeed, when setting the graph kernel distance and radius to 0 and 1, respectively, the feature space has just one feature for each ground signature, in close analogy to MLN. The empirical performance (area under recall-precision curve, AURPC) of kLog using the same set of signatures drops dramatically from 0.28 (distance 2, radius 2) to 0.09 (distance 1, radius 0).
      </paragraph>
      <paragraph>
       In a second experiment, we predicted the relation advised_by starting from partial information (i.e., when relations Student (and its complement Professor) are unknown, as in [7]). In this case, we created a pipeline of two predictors. Our procedure is reminiscent of stacked generalization [57]. In the first stage, a leave-one-research-group-out cross-validation procedure was applied to the training data to obtain predicted groundings for Student (a binary classification task on entities). Predicted groundings were then fed to the second stage which predicts the binary relation advised_by. The overall procedure was repeated using one research group at the time for testing. Results are reported in Fig. 7 (MLN results published in [7]).
      </paragraph>
      <paragraph>
       Since kLog is embedded in the programming language Prolog, it is easy to use the output of one learning task as the input for the next one as illustrated in the pipeline. This is because both the inputs and the outputs are relations. Relations are treated uniformly regardless of whether they are defined intensionally, extensionally, or are the result of a previous learning run. Thus kLog satisfies what has been called the closure principle in the context of inductive databases [58], [59]; it is also this principle together with the embedding of kLog inside a programming language (Prolog) that turns kLog into a true programming language for machine learning [60], [61], [62]. Such programming languages possess — in addition to the usual constructs — also primitives for learning, that is, to specify the inputs and the outputs of the learning problems. In this way, they support the development of software in which machine learning is embedded without requiring the developer to be a machine learning expert. According to Mitchell [60], the development of such languages is a long outstanding research question.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Entity classification
      </section-title>
      <paragraph>
       The WebKB data set [27] has been widely used to evaluate relational methods for text categorization. It consists of academic Web pages from four computer science departments and the task is to identify the category (such as student page, course page, professor page, etc). Fig. 8 shows the E/R diagram used in kLog. One of the most important relationships in this domain is has, that associates words with web pages. After graphicalization, vertices representing webpages have large degree (at least the number of words), making the standard NSPDK of [11] totally inadequate: even by setting the maximum distance {a mathematical formula}d⁎=1 and the maximum radius {a mathematical formula}r⁎=2, the hard match would essentially create a distinct feature for every page. In this domain we can therefore appreciate the flexibility of the kernel defined in Section 6.2. In particular, the soft match kernel creates histograms of word occurrences in the page, which is very similar to the bag-of-words (with counts) representation that is commonly used in text categorization problems. The additional signature cs_in_url embodies common sense background knowledge that many course web pages contains the string “cs” followed by some digits and is intensionally defined using a Prolog predicate that holds true when the regular expression :cs(e*)[0-9]+: matches the page URL.
      </paragraph>
      <paragraph>
       Empirical results using only four Universities (Cornell, Texas, Washington, Wisconsin) in the leave-one-university-out setup are reported in Table 6.
      </paragraph>
      <paragraph>
       We compared kLog to MLN and to Tilde on the same task. For MLN we used the Alchemy system and the following set of formulae, which essentially encode the same domain knowledge exploited in kLog:{a mathematical formula} Ground atoms for the predicate LinkTo were actually precalculated externally in Prolog (same code as for the kLog's intensional signature) since regular expressions are not available in Alchemy. We did not enforce mutually exclusive categories since results tended to be worse. For learning we used the preconditioned scaled conjugate gradient approach described in [63] and we tried a wide range of values for the learning rate and the number of iterations. The best results, reported in Table 6, used the trick of averaging MLN weights across all iterations as in [63]. MC-SAT inference was used during prediction. In spite of the advantage of MLN for using a collective inference approach, results (Table 7) are comparable to those obtained with kLog (MLN tends to overpredict the class “student”, resulting in a slightly lower average {a mathematical formula}F1 measure, but accuracies are identical). Thus the feature extracted by kLog using the graph kernel are capable of capturing enough contextual information from the input portion of the data to obviate the lack of collective inference.
      </paragraph>
      <paragraph>
       In the case of Tilde, we used the following language bias:{a mathematical formula} Results are reported in Table 8 and are slightly worse than those attained by kLog and MLN.
      </paragraph>
      <paragraph>
       Although the accuracies of the three methods are essentially comparable, their requirements in terms of CPU time are dramatically different: using a single core of a second generation Intel Core i7, kLog took 36 s, Alchemy 27,041 s (for 100 iterations, at which the best accuracy is attained), and Tilde: 5259 s.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Domains with a single interpretation
      </section-title>
      <paragraph>
       The Internet Movie Database (IMDb) collects information about movies and their cast, people, and companies working in the motion picture industry. We focus on predicting, for each movie, whether its first weekend box-office receipts are over US$2 million, a learning task previously defined in [30], [64]. The learning setting defined so far (learning from independent interpretations) is not directly applicable since train and test data must necessarily occur within the same interpretation. The notion of slicing in kLog allows us to overcome this difficulty. A slice system is a partition of the true ground atoms in a given interpretation: {a mathematical formula}z={z(i1),…,z(in)} where the disjoint sets {a mathematical formula}z(j) are called slices and the index set {a mathematical formula}I={i1,…,in} is endowed with a total order ⪯. For example, a natural choice for I in the IMDb domain is the set of movie production years (e.g., {a mathematical formula}{1996,…,2005}), where the index associated with a ground atom of an entity such as actor is the debut year.
      </paragraph>
      <paragraph>
       In this way, given two disjoint subsets of I, T and S, such that {a mathematical formula}max⪯⁡(T)⪯min⪯⁡(S), it is reasonable during training to use for some index {a mathematical formula}t∈T∖{min⪯⁡(T)} the set of ground atoms {a mathematical formula}{x(i):i∈T∧i⪯t}t∪{y(i):i∈T∧i≺t}t (where {a mathematical formula}i≺t iff {a mathematical formula}i⪯t and {a mathematical formula}i≠t) as the input portion of the data, and {a mathematical formula}{y(t)}t as the output portion (targets). Similarly, during testing we can for each {a mathematical formula}s∈S use the set of ground atoms {a mathematical formula}{x(i):i∈S∧i⪯s}s∪{y(i):i∈S∧i≺s}s for predicting {a mathematical formula}{y(s)}s.
      </paragraph>
      <paragraph>
       The kLog data set was created after downloading the whole database from http://www.imdb.com. Adult movies, movies produced outside the US, and movies with no opening weekend data were discarded. Persons and companies with a single appearance in this subset of movies were also discarded. The resulting data set is summarized in Table 9. We modeled the domain in kLog using extensional signatures for movies, persons (actors, producers, directors), and companies (distributors, production companies, special effects companies). We additionally included intensional signatures counting, for each movie the number of companies involved also in other blockbuster movies. We sliced the data set according to production year, and starting from year {a mathematical formula}y=1997, we trained on the frame {a mathematical formula}{y−1,y−2} and tested on the frame {a mathematical formula}{y}. Results (area under the ROC curve) are summarized in Table 9, together with comparative results against MLN and Tilde. In all three cases we used the same set of ground atoms for training and testing, but in the case of MLN the Alchemy software does not differentiate between evidence and query ground atoms of the same predicate. We therefore introduced an extra predicate called PrevBlockbuster to inject evidence for years {a mathematical formula}{y−3,y−4,…}, together with the hard rule{a mathematical formula} and used Blockbuster as the query predicate when training on years {a mathematical formula}{y−1,y−2} and testing on year y. MLN rules were designed to capture past performance of actors, directors, distribution companies, etc. For example:{a mathematical formula} In the case of Tilde, we used as background knowledge exactly the same intensional signature definitions used in kLog. The MLN was trained using the discriminative weight learning algorithm implemented in Alchemy. MCMC (Gibbs sampling) was used during prediction to obtain probabilities for all query atoms.
      </paragraph>
      <paragraph>
       On this data set, Tilde was the fastest system, completing all training and test phases in 220 s, followed by kLog (1394 s) and Alchemy (12,812 s). However, the AUC obtained by kLog is consistently higher across all prediction years.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      As kLog is a language for logical and relational learning with kernels it is related to work on inductive logic programming, to statistical relational learning, to graph kernels, and to propositionalization. We now discuss each of these lines of work and their relation to kLog.
     </paragraph>
     <paragraph>
      First, the underlying representation of the data that kLog employs at the first level is very close to that of standard inductive logic programming systems such as Progol [65], Aleph [66], and Tilde [67] in the sense that the input is essentially (a variation of) a Prolog program for specifying the data and the background knowledge. Prolog allows us to encode essentially any program as background knowledge. The E/R model used in kLog is related to the Probabilistic Entity Relationship models introduced by Heckerman et al. in [10]. The signatures play a similar role as the notion of a declarative bias in inductive logic programming [9]. The combined use of the E/R model and the graphicalization has provided us with a powerful tool for visualizing both the structure of the data (the E/R diagram) as well as specific cases (through their graphs). This has proven to be very helpful when preparing data sets for kLog. On the other hand, due to the adoption of a database framework, kLog forbids functors in the signature relations (though functors can be used inside predicates needed to compute these relations inside the background knowledge). This contrasts with some inductive logic programming systems such as Progol [65] and Aleph [66].
     </paragraph>
     <paragraph>
      Second, kLog is related to many existing statistical relational learning systems such as Markov logic [7], probabilistic similarity logic [68], probabilistic relational models [8], Bayesian logic programs [69], and ProbLog [70] in that the representations of the inputs and outputs are essentially the same, that is, both in kLog and in statistical relational learning systems inputs are partial interpretations which are completed by predictions. What kLog and statistical relational learning techniques have in common is that they both construct (implicitly or explicitly) graphs representing the instances. For statistical relational learning methods such as Markov logic [7], probabilistic relational models [8], and Bayesian logic programs [69] the knowledge-based model construction process will result in a graphical model (Bayesian or Markov network) for each instance representing a class of probability distributions, while in kLog the process of graphicalization results in a graph representing an instance by unrolling the E/R-diagram. Statistical relational learning systems then learn a probability distribution using the features and parameters in the graphical model, while kLog learns a function using the features derived by the kernel from the graphs. Notice that in both cases, the resulting features are tied together. Indeed, in statistical relational learning each ground instance of a particular template or expression that occurs in the graph has the same parameters. kLog features correspond to subgraphs that represent relational templates and that may match (and hence be grounded) multiple times in the graphicalization. As each such feature has a single weight, kLog also realizes parameter tying in a similar way as statistical relational learning methods. One difference between these statistical relational learning models and kLog is that the former do not really have a second level as does kLog. Indeed, the knowledge base model construction process directly generates the graphical model that includes all the features used for learning, while in kLog these features are derived from the graph kernel. While statistical relational learning systems have been commonly used for collective learning, this is still a question for further research within kLog. A combination of structured-output learning [12] and iterative approaches (as incorporated in the EM algorithm) can form the basis for further work in this direction. Another interesting but more speculative direction for future work is concerned with lifted inference. Lifted inference has been the focus of a lot of attention in statistical relational learning; see [71] for an overview. One view on lifted inference is that it is trying to exploit symmetries in the graphical models that would be the result of the knowledge based model construction step, e.g., [72]. From this perspective, it might be interesting to explore the use of symmetries in graphs and features constructed by kLog.
     </paragraph>
     <paragraph>
      kLog builds also upon the many results on learning with graph kernels, see [73] for an overview. A distinguishing feature of kLog is, however, that the graphs obtained by graphicalizing a relational representation contain very rich labels, which can be both symbolic and numeric. This contrasts with the kind of graphs needed to represent for instance small molecules. In this regard, kLog is close in spirit to the work of [74], who define a kernel on hypergraphs, where hypergraphs are used to represent relational interpretations. A distinctive feature of kLog is automatic graphicalization of relational representations, which also allows users to naturally specify multitask and collective learning tasks.
     </paragraph>
     <paragraph>
      The graphicalization approach introduced in kLog is closely related to the notion of propositionalization, a commonly applied technique in logical and relational learning [75], [9] to generate features from a relational representation. The advantage of graphicalization is that the obtained graphs are essentially equivalent to the relational representation and that — in contrast to the existing propositionalization approaches in logical and relational learning — this does not result in a loss of information. After graphicalization, any graph kernel can in principle be applied to the resulting graphs. Even though many of these kernels (such as the one used in kLog) compute — implicitly or explicitly — a feature vector, the dimensionality of the obtained vector is far beyond that employed by traditional propositionalization approaches. kFOIL [5] is one such propositionalization technique that has been tightly integrated with a kernel-based method. It greedily derives a (small) set of features in a way that resembles the rule-learning algorithm of FOIL [76].
     </paragraph>
     <paragraph>
      Several other approaches to relational learning and mining have employed graph-based encodings of the relational data, e.g., [77], [78], [79], [80]. kLog encodes a set of ground atoms into a bipartite undirected graph whose nodes are true ground atoms and whose edges connect an entity atom to a relationship atom if the identifier of the former appears as an argument in the latter. This differs from the usual encoding employed in graph-based approaches to relational learning and mining, which typically use labeled edges to directly represent the relationships between the nodes corresponding to the entities. Furthermore, these approaches typically use the graph-based representation as the single representation, and unlike kLog do neither consider the graph-based representation as an intermediate representation nor work at three levels of representation (logical, graph-based and feature-based).
     </paragraph>
     <paragraph>
      Other domain specific languages for machine learning have been developed whose goals are closely related to those of kLog. Learning based Java [62] was designed to specifically address applications in natural language processing. It builds on the concept of data-driven compilation to perform feature extraction and nicely exploits the constrained conditional model framework [81] for structured output learning. FACTORIE [82] allows users to concisely define features used in a factor graph and, consequently, arbitrarily connected conditional random fields. Like with MLN, there is an immediate dependency of the feature space on the sentences of the language, whereas in kLog this dependency is indirect since the exact feature space is eventually defined by the graph kernel.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Syntax of the kLog domain declaration section
     </section-title>
     <paragraph>
      A kLog program consists of Prolog code augmented by a domain declaration section delimited by the pair of keywords begin_domain and end_domain and one or more signature declarations. A signature declaration consists of a signature header followed by one or more Prolog clauses. Clauses in a signature declaration form the declaration of signature predicates and are automatically connected to the current signature header. There are a few signature predicates with a special meaning for kLog, as discussed in this section. A brief BNF description of the grammar of kLog domains is given in Fig. 9.
     </paragraph>
     <paragraph>
      Additionally, kLog provides a library of Prolog predicates for handling data, learning, and performance measurement.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Definitions
     </section-title>
     <paragraph>
      For the sake of completeness we report here a number of graph theoretical definitions used in the paper. We closely follow the notation in [91]. A graph {a mathematical formula}G=(V,E) consists of two sets V and E. The notation {a mathematical formula}V(G) and {a mathematical formula}E(G) is used when G is not the only graph considered. The elements of V are called vertices and the elements of E are called edges. Each edge has a set of two elements in V associated with it, which are called its endpoints, which we denote by concatenating the vertices variables, e.g. we represent the edge between the vertices u and v with uv. In this case we say that u is adjacent to v and that uv is incident on u and v. The degree of a vertex is number of edges incident on it. A graph is bipartite if its vertex set can be partitioned into two subsets X and Y so that every edge has one end in X and the other in Y. A graph is rooted when we distinguish one of its vertices, called root. The neighborhood of a vertex v is the set of vertices that are adjacent to v and is indicated with {a mathematical formula}N(v). The neighborhood of radius r of a vertex v is the set of vertices at a distance less than or equal to r from v and is denoted by {a mathematical formula}Nr(v). In a graph G, the induced subgraph on a set of vertices {a mathematical formula}W={w1,…,wk} is a graph that has W as its vertex set and it contains every edge of G whose endpoints are in W. The neighborhood subgraph of radius r of vertex v is the subgraph induced by the neighborhood of radius r of v and is denoted by {a mathematical formula}Nrv. A labeled graph is a graph whose vertices and/or edges are labeled, possibly with repetitions, using symbols from a finite alphabet. We denote the function that maps the vertex/edge to the label symbol as ℓ. Two simple graphs {a mathematical formula}G1=(V1,E1) and {a mathematical formula}G2=(V2,E2) are isomorphic, which we denote by {a mathematical formula}G1≃G2, if there is a bijection {a mathematical formula}ϕ:V1→V2, such that for any two vertices {a mathematical formula}u,v∈V1, there is an edge uv if and only if there is an edge {a mathematical formula}ϕ(u)ϕ(v) in {a mathematical formula}G2. An isomorphism is a structure-preserving bijection. Two labeled graphs are isomorphic if there is an isomorphism that preserves also the label information, i.e. {a mathematical formula}ℓ(ϕ(v))=ℓ(v). An isomorphism invariant or graph invariant is a graph property that is identical for two isomorphic graphs (e.g. the number of vertices and/or edges). A certificate for isomorphism is an isomorphism invariant that is identical for two graphs if and only if they are isomorphic.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Decomposition kernels
     </section-title>
     <paragraph>
      We follow the notation in [92]. Given a set X and a function {a mathematical formula}K:X×X→R, we say that K is a kernel on{a mathematical formula}X×X if K is symmetric, i.e. if for any x and {a mathematical formula}y∈XK(x,y)=K(y,x), and if K is positive–semidefinite, i.e. if for any {a mathematical formula}N≥1 and any {a mathematical formula}x1,…,xN∈X, the matrix K defined by {a mathematical formula}Kij=K(xi,xj) is positive–semidefinite, that is {a mathematical formula}∑ijcicjKij≥0 for all {a mathematical formula}c1,…,cN∈R or equivalently if all its eigenvalues are nonnegative. It is easy to see that if each {a mathematical formula}x∈X can be represented as {a mathematical formula}ϕ(x)={ϕn(x)}n≥1 such that K is the ordinary {a mathematical formula}l2 dot product {a mathematical formula}K(x,y)=〈ϕ(x),ϕ(y)〉=∑nϕn(x)ϕn(y) then K is a kernel. The converse is also true under reasonable assumptions (which are almost always verified) on X and K, that is, a given kernel K can be represented as {a mathematical formula}K(x,y)=〈ϕ(x),ϕ(y)〉 for some choice of ϕ. In particular it holds for any kernel K over {a mathematical formula}X×X where X is a countable set. The vector space induced by ϕ is called the feature space. Note that it follows from the definition of positive–semidefinite that the zero-extension of a kernel is a valid kernel, that is, if {a mathematical formula}S⊆X and K is a kernel on {a mathematical formula}S×S then K may be extended to be a kernel on {a mathematical formula}X×X by defining {a mathematical formula}K(x,y)=0 if x or y is not in S. It is easy to show that kernels are closed under summation, i.e. a sum of kernels is a valid kernel.
     </paragraph>
     <paragraph>
      Let now {a mathematical formula}x∈X be a composite structure such that we can define {a mathematical formula}x1,…,xD as its parts.{sup:14} Each part is such that {a mathematical formula}xd∈Xd for {a mathematical formula}d=1,…,D with {a mathematical formula}D≥1 where each {a mathematical formula}Xd is a countable set. Let R be the relation defined on the set {a mathematical formula}X1×…×XD×X, such that {a mathematical formula}R(x1,…,xD,x) is true iff {a mathematical formula}x1,…,xD are the parts of x. We denote with {a mathematical formula}R−1(x) the inverse relation that yields the parts of x, that is {a mathematical formula}R−1(x)={x1,…,xD:R(x1,…,xD,x)}. In [92] it is demonstrated that, if there exist a kernel {a mathematical formula}Kd over {a mathematical formula}Xd×Xd for each {a mathematical formula}d=1,…,D, and if two instances {a mathematical formula}x,y∈X can be decomposed in {a mathematical formula}x1,…,xd and {a mathematical formula}y1,…,yd, then the following generalized convolution:{a mathematical formula} is a valid kernel called a convolution or decomposition kernel.{sup:15} In words: a decomposition kernel is a sum (over all possible ways to decompose a structured instance) of the product of valid kernels over the parts of the instance.
     </paragraph>
    </section>
    <section label="Appendix D">
     <section-title>
      Graph invariant pseudo-identifier computation
     </section-title>
     <paragraph>
      We obtain the pseudo-identifier of a rooted neighborhood graph {a mathematical formula}Gh by first constructing a graph invariant encoding {a mathematical formula}Lg(Gh). Then we apply a hash function {a mathematical formula}H(Lg(Gh))→N to the encoding. The algorithm was first described in [11] but we present it again here for self-sufficiency. Fig. 10 shows an overview.
     </paragraph>
     <paragraph>
      Note that we cannot hope to exhibit an efficient certificate for isomorphism in this way, and in general there can be collisions between two non-isomorphic graphs, either because these are assigned the same encoding or because the hashing procedure introduces a collision even when the encodings are different.
     </paragraph>
     <paragraph>
      Hashing is not a novel idea in machine learning; it is commonly used, e.g., for creating compact representations of molecular structures [38], and has been advocated as a tool for compressing very high-dimensional feature spaces [93]. In the present context, hashing is mainly motivated by the computational efficiency gained by approximating the isomorphism test.
     </paragraph>
     <paragraph>
      The graph encoding {a mathematical formula}Lg(Gh) that we propose is best described by introducing two new label functions: one for the vertices and one for the edges, denoted {a mathematical formula}Lv and {a mathematical formula}Le respectively. {a mathematical formula}Lv(v) assigns to vertex v a lexicographically sorted sequence of pairs composed by a topological distance and a vertex label, that is, {a mathematical formula}Lv(v) returns a sorted list of pairs {a mathematical formula}〈D(v,u),ℓ(u)〉 for all {a mathematical formula}u∈Gh. Moreover, since {a mathematical formula}Gh is a rooted graph, we can use the knowledge about the identity of the root vertex h and prepend to the returned list the additional information of the distance from the root node {a mathematical formula}D(v,h). The new edge label is produced by composing the new vertex labels with the original edge label, that is {a mathematical formula}Le(uv) assigns to edge uv the triplet {a mathematical formula}〈Lv(u),Lv(v),ℓ(uv)〉. Finally {a mathematical formula}Lg(Gh) assigns to the rooted graph {a mathematical formula}Gh the lexicographically sorted list of {a mathematical formula}Le(uv) for all {a mathematical formula}uv∈E(Gh). In words: we relabel each vertex with a sequence that encodes the vertex distance from all other (labeled) vertices (plus the distance from the root vertex); the graph encoding is obtained as the sorted edge list, where each edge is annotated with the endpoints' new labels. For a proof that {a mathematical formula}Lg(Gh) is graph invariant, see [94, p. 53].
     </paragraph>
     <paragraph>
      We finally resort to a Merkle–Damgård construction-based hashing function for variable-length data to map the various lists to integers, that is, we map the distance-label pairs, the new vertex labels, the new edge labels and the new edge sequences to integers (in this order). Note that it is trivial to control the size of the feature space by choosing the hash codomain size (or alternatively the bit size for the returned hashed values). Naturally there is a tradeoff between the size of the feature space and the number of hash collisions.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>