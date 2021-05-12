<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A computational framework for conceptual blending.
   </title>
   <abstract>
    We present a computational framework for conceptual blending, a concept invention method that is advocated in cognitive science as a fundamental and uniquely human engine for creative thinking. Our framework treats a crucial part of the blending process, namely the generalisation of input concepts, as a search problem that is solved by means of modern answer set programming methods to find commonalities among input concepts. We also address the problem of pruning the space of possible blends by introducing metrics that capture most of the so-called optimality principles, described in the cognitive science literature as guidelines to produce meaningful and serendipitous blends. As a proof of concept, we demonstrate how our system invents novel concepts and theories in domains where creativity is crucial, namely mathematics and music.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Creativity is an inherent human capability that is crucial for the development and invention of new ideas and concepts [3]. This paper addresses a kind of creativity which Boden [3] calls combinational, and which has been studied by Fauconnier and Turner [27] in their framework of conceptual blending. In brief, conceptual blending is a process where one invents a novel concept, called the blend, by combining two familiar input concepts. For illustration, consider the classical example of blending the concepts house and boat (e.g.  [34], [27]). A possible result is the invention of a house-boat concept, where the medium on which a house is situated (land) becomes the medium on which boat is situated (water), and the inhabitant of the house becomes the passenger of the boat. Another possible blend is the boat-house, where the boat ‘inhabits’ the house.
     </paragraph>
     <paragraph>
      An inherent computational problem of conceptual blending is to find a common ground, called generic space, between the two input concepts [27]. For example, the house-boat blend has the generic space of a person being inside an object that is not situated on any medium (or that is situated on a more general medium). Once the generic space has been identified, one can develop possible blends by specialising the generic space with elements from the input concepts in a meaningful way. However, this is not trivial because the naive union of input spaces can lead to inconsistencies. For example, the medium on which an object is situated can not be land and water at the same time. Hence, before combining the input concepts, it is necessary to generalise at least one medium assignment. Another problem is the huge number of possible blends, which are often not meaningful. For example, blending house and boat such that the house becomes the passenger of the boat – imagine a house-transporting cargo vessel – is not very convincing. Consequently, one has to prune the search space by ruling out such low-quality blends.
     </paragraph>
     <paragraph>
      Conceptual blending is perceived as a milestone in human cultural development [27]. The main motivation behind blending from an AI perspective is to find a computational interpretation of the human blending process, which could be an equally important milestone in the development of intelligent agents and autonomous systems. The value of conceptual blending for the development of creative systems has been witnessed by several works in the field of Artificial Intelligence and cognitive science, where particular implementations of this cognitive theory have been proposed [83], [63], [64], [33], [36].
     </paragraph>
     <paragraph>
      As we show in our survey in Sec. 5, existing approaches propose computational characterisations of conceptual blending by using different formal representations for the input spaces and different techniques for performing the blending operation, and for the evaluation of the blends. For instance, Goguen and Harrell [33] logically formalise conceptual blending in terms of algebraic theories, Pereira [64] uses concept maps and frames, and rules and constraints to implement blend evaluation, while Veale and Donoghue [83] focus on the use semantic networks. The survey shows that providing a full computational account for conceptual blending is very challenging, in particular for the following two reasons:
     </paragraph>
     <list>
      <list-item label="•">
       When combining two input spaces, the generic space is of particular importance to steer possible variations of blends. However, computing the generic space is a challenging issue (e.g., [76]), especially for expressive representation languages. Most existing blending frameworks are therefore not capable of computing a generic space automatically.
      </list-item>
      <list-item label="•">
       Having identified a generic space, there typically remains a huge number of possible combinations to generate blends. To prune this result space, blends need to be evaluated. One way to do this is to check their consistency and to apply certain quality metrics.
      </list-item>
     </list>
     <paragraph>
      In this paper, we address these issues and ask the following question: How can we orchestrate the blending of input concepts in a computationally efficient and feasible way, that is faithful to the cognitive theory of conceptual blending and can therefore be considered as computationally creative?
     </paragraph>
     <paragraph>
      To answer this question, we build a general creative computational framework for conceptual blending that allows the creation and evaluation of new blended concepts. The main contributions of this paper are as follows:
     </paragraph>
     <list>
      <list-item label="•">
       We provide a blending framework that accepts input concepts in form of semiotic systems (see Sec. 2.2). Herein, we use algebraic specifications similar to those proposed by Goguen [34, Def. 1], with the difference that we assign priorities not only to constructors, i.e., operators, but also to sorts, predicates, and axioms. This extra level of knowledge allows us to guide the generalisation search process and create meaningful generalisations of the input spaces more efficiently, and we also use it for the evaluation of blends.
      </list-item>
      <list-item label="•">
       We automate the discovery of generic spaces by applying amalgams, a notion known from case-based reasoning [61] (see Sec. 2.3). This process coordinates the interleaved generalisation and combination of input concepts as a non-monotonic search problem. We solve this search problem by using the declarative framework of Answer Set Programming (ASP) (e.g., [2]), as described in Sec. 3.
      </list-item>
      <list-item label="•">
       We evaluate blends by re-interpreting the optimality principles of Fauconnier and Turner [27] and give them a full computational account (see Sec. 2.1 and 3.6). This helps to prune the search space.
      </list-item>
      <list-item label="•">
       As a proof of concept, we implement our framework as an exploratory creative tool that can create interesting blends in the domain of mathematics and music. We also reproduce several blends that can be found in the literature. Finally, we show how our framework finds blends that belong to different domains (see Sec. 4).
      </list-item>
      <list-item label="•">
       We provide a survey to characterise existing computational blending systems (see Sec. 5) and position our own work within the state of the art.
      </list-item>
     </list>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      Our framework is inspired by the cognitive theory of conceptual blending as presented in Fauconnier and Turner [27], whose underlying principles are described in detail in Sec. 2.1. To realise these principles computationally, we follow the work by Goguen [34], who provides a category theoretical account of blending (see Sec. 2.2). Moreover, to make Goguen's work computationally feasible, we implement blending as an amalgam-based workflow [61], a notion that was developed in case-based reasoning (see Sec. 2.3). The implementation framework for the amalgam-based workflow is Answer Set Programming (ASP), for which we provide a brief background in Sec. 2.4.
     </paragraph>
     <section label="2.1">
      <section-title>
       Cognitive principles of blending
      </section-title>
      <paragraph>
       Creativity, understood as an unfamiliar combinations of familiar ideas, goes back to the notion of bisociation, the idea that creativity is often a result of an intersection and selective combination of rather distinct frames of reference, presented by Arthur Koestler in his book The Act of Creation in 1964 [46]. Based on these basic intuitions, within the cognitive sciences these ideas have been further developed into more concrete approaches of how to produce novel ideas (which may be concepts, theories, solutions to problems, works of art, etc.). One particular such approach, known as the theory of conceptual blending or conceptual integration has been proposed by Fauconnier and Turner [26] as a kind of primitive or fundamental cognitive operation underlying much of everyday thought and language. The process by which two concepts are blended into a novel idea is seen as a complex event in which particular elements and their relations pertaining to the initial two concepts are combined selectively into a new whole, which is understood to be structurally richer, in a sense we will make precise below, than the mere commonalities of the two concepts.
      </paragraph>
      <paragraph>
       Fauconnier's view of concepts is prior to the notion of blending, and his Mental Spaces Theory is a highly influential cognitive theory of meaning construction, developed in [24] and [25]. According to Fauconnier, meaning construction involves two processes: (1) the building of mental spaces; and (2) the establishment of mappings between those mental spaces. Moreover, the mapping relations are guided by the local discourse context, which means that meaning construction is always situated or context-dependent.
      </paragraph>
      <paragraph>
       Fauconnier and Turner [27] describe several constitutive elements of conceptual blending. These are (i) the input spaces that are to be blended, (ii) a partial cross-space mapping that connects counterparts in the input mental spaces, (iii) a generic space that is an abstraction from what the input spaces have in common, (iv) a blending operation that produces a blend of the input spaces and into which the structure of the input spaces is selectively projected, and (v) an emergent structure, i.e., structure that is a synergistic gain to the naive sum of the structure of input spaces.
      </paragraph>
      <paragraph>
       These constitutive elements can be organised in a conceptual integration network, i.e., the network of all input spaces, generic spaces and blend spaces together with the selective projections that model a particular blending process. Finally, Fauconnier and Turner propose certain optimality principles that govern the blending process, and that can be taken as a way to assess the quality of a blend. Let us briefly review these constitutive elements and optimality principles as put forth in Fauconnier and Turner's model, using the house-boat blend depicted in Fig. 1 as an illustrative example.
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Constitutive elements of conceptual blending
       </section-title>
       <paragraph>
        According to cognitive theory, the conceptual blending process involves the following elements:
       </paragraph>
       <list>
        <list-item label="•">
         Input Spaces: Fauconnier and Turner [27] consider the input spaces of a blend to be mental spaces – small conceptual packets constructed as we think and talk, for purposes of local understanding and action. According to Fauconnier [24], mental spaces are connected to long-term schematic knowledge, by means of frames, which model how certain elements and relations are organised as a package that we already know about. Often these frames are so-called image schemas[52], described by Johnson [44] as ‘a recurring, dynamic pattern of our perceptual interactions and motor programs that gives coherence and structure to our experience’. Image schemas are also critical for the semantic compositionality of language, and they are, therefore, often used by cognitive linguists to implement embodied construction grammars [22], [23], [81].Moreover, mental spaces are built on-demand, for a particular linguistic situation, resulting in concrete and temporary packets of conceptual structure. For example, contrary to a naive view of meaning, there is no fixed understanding of the concepts of house and boat: there are mental spaces for house and boat that are constructed in particular linguistic situations. Hence, one cannot assume that input mental spaces are the same in all possible output blends, since the content of a mental space is neither constant nor preexisting to the context in which they are used. For example, a house in a poor developing country has different properties than a house in a rich urban area. However, many computational blending systems (e.g., [37], [83]) that emanate from the work by Fauconnier and Turner [27] often simplify this aspect of their theory and consider blending to be an operation that takes two input spaces as given and generates one or more output spaces, i.e., blends. The approach taken in this paper is to formalise the notion of mental spaces being built on-demand, but allowing heuristic generalisation and adaptation of the input spaces, as well as the computation of a blend. This is demonstrated in the examples shown in Sec. 4.2 and Sec. 4.3.
        </list-item>
        <list-item label="•">
         Cross-space mapping: According to [27, p. 41], “[...] a partial cross-space mapping connects counterparts in the input mental spaces.” As an example consider the house-boat blend, where the passenger of the boat is mapped to the resident of the house, and the ride relation between passenger and boat is mapped to the live-in relation between resident and house.
        </list-item>
        <list-item label="•">
         Generic Space: The cross-space mapping points to what might constitute the generic space, which essentially contains what is common to or shared among the two input mental spaces. For example, the mapping between passenger and resident in the house-boat blend suggests a generic space with a concept person that generalises the concepts of passenger and resident.
        </list-item>
        <list-item label="•">
         The close relationship between the generic and the blend spaces, makes it important for any formal model of blending to come to grips how the generic space arises from the blending process as well as what role it plays.
        </list-item>
        <list-item label="•">
         From an Artificial Intelligence viewpoint, composition combines a selective projection of inputs. Completion adds background knowledge to the blend, until it is completed, i.e., has all that is needed for the purpose at hand. Elaboration involves reasoning or inference, in the sense that background knowledge is used to reason about actions that some elements can perform, or actions that can be performed on some elements, in order to elucidate the eventual consequences of the blended mental space.
        </list-item>
        <list-item label="•">
         Conceptual Integration Network: As stated in Fauconnier and Turner [27, p. 44], “Building an integration network involves setting up mental spaces, matching across spaces, projecting selectively to a blend, locating shared structures, projecting backward to inputs, recruiting new structure to the inputs or the blend, and running various operations in the blend itself.”
        </list-item>
       </list>
      </section>
      <section label="2.1.2">
       <section-title>
        Optimality principles
       </section-title>
       <paragraph>
        Optimality principles play the role of an assessment measure for blends. As we mention earlier, two input spaces can be blended together in many different ways, and finding a particular blend that is creative and useful is not trivial.
       </paragraph>
       <paragraph>
        The optimality principles that Fauconnier and Turner [27] mention compete with each other, and satisfying one principle may dissatisfy another one. In the following, we summarize how Fauconnier and Turner [26], [27] define the particular principles that we consider in this paper, and we provide examples by explaining their role in the house-boat blend.
       </paragraph>
       <list>
        <list-item label="•">
         Topology Principle:  “For any input space and any element in that space projected into the blend, it is optimal for the relations of the element in the blend to match the relations of its counterpart.”[26]In terms of the house-boat blend, if the elements passenger and resident are blended to a passenger-resident of a house-boat, then the lives-in relation between the resident and the house remains the lives-in relation between the passenger-resident and the house-boat.
        </list-item>
        <list-item label="•">
         Pattern Completion Principle:  “Other things being equal, complete elements in the blend by using existing integrated patterns as additional inputs. Other things being equal, use a completing frame that has relations that can be the compressed versions of the important outer-space vital relations between the inputs.”[27, p. 328]This principle is related to the work on image schemas by Lakoff [51]. Image schemas are completing frames that are abstract versions of the input spaces. For example, in the house-boat blend, the Container image schema is used as an abstraction for a house, which is a container for a resident and a boat, which is a container for a passenger. The pattern completion principle is related to the emergent structure of a blend, because emergent structure only arises through completion and elaboration.
        </list-item>
        <list-item label="•">
         Integration Principle:  “The blend must constitute a tightly integrated scene that can be manipulated as a unit. More generally, every space in the blend structure should have integration.”[26]For example, one could blend a scene of a house and a scene of a boat as the simple union of both scenes, so that there is a house with a resident and a boat with a passenger in the blend. However, this is not perceived well as a unit. A better blend in terms of integration is the new concept of house-boat, which can be treated much better as a unit.
        </list-item>
        <list-item label="•">
         Maximisation of Vital Relations Principle:  “Other things being equal, maximise vital relations in the network. In particular, maximise the vital relations in the blended space and reflect them in outer-space vital relations.”Intensification of Vital Relations Principle:  “Other things being equal, intensify vital relations.”[27, p. 330]{sup:1}According to Fauconnier and Turner [27], blending does not only happen to creatively invent new concepts, but it also serves as a means to compress the information in the input spaces using so-called vital relations, which are fundamental in the particular network of interest. As examples, Fauconnier and Turner [27] mention cause-effect, time, space, identity, change, and uniqueness relations. If such relations exist between the input spaces, then blending causes them to reappear in compressed form in the blend. Maximising and/or intensifying vital relations in a blend also increases the degree of compression that a blend produces. This underpins not only the importance of blending as a means for creativity, but also for efficient cognitive operation.
        </list-item>
        <list-item label="•">
         Web Principle:  “Other things being equal, manipulating the blend as a unit must maintain the web of appropriate connections to the input spaces easily and without additional surveillance or computation.”[27, p. 331]This refers to relations between spaces in the network. For example, placing a houseboat into a new environment such as a river scene maintains the connections to the input spaces of house and boat: the relation between the resident of a house and the passenger-resident of a house-boat is still there. As another example, consider the case where some form of residential fee has to be paid for a house-boat. If the fee is raised for a house-boat, then one should be able to infer that it is also raised for a house.
        </list-item>
        <list-item label="•">
         The Unpacking Principle:  “Other things being equal, the blend all by itself should prompt for the reconstruction of the entire network.”[27, p. 332]For example, by focusing on the concept of a house-boat we still can access the concept of house with its properties and its relationship to other concepts. Similarly, we can also access the notion of boat with its properties and its relationship to other concepts.
        </list-item>
        <list-item label="•">
         Relevance Principle:  This is sometimes also called the Good Reason Principle. Fauconnier and Turner [27, p. 333] describe it as follows: “Other things being equal, an element in the blend should have relevance, including relevance for establishing links to other spaces and for running the blend. Conversely, an outer-space relation between the inputs that is important for the purpose of the network should have a corresponding compression in the blend.”What eventually constitutes the house-boat concept will very much depend on what we are pursuing when blending. So, if the relation live-in is relevant, it should be included in the blend. But maybe another relation (e.g., number-of-rooms) might not be relevant, and should, therefore, not be considered in the blend.
        </list-item>
       </list>
       <paragraph>
        In general, the optimality principles are defined in a vague cognitive way, and not meant to be perceived as rigid rules. However, if one is to computationalize conceptual blending, then it is necessary to find some way of formalizing the optimality principles. Our attempt to do so results in an encoding of some of the principles as a quantitative evaluation metric, as presented in Sec. 3.6.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       A categorical view on blending
      </section-title>
      <paragraph label="Definition 1">
       Goguen [34] proposes to model the input concepts of blending as semiotic systems, which are essentially algebraic specifications described in a logical representation language. The main advantage of this approach is being able to provide a general enough, but computational feasible representation, while being able to resolve inconsistencies. We represent semiotic systems using the Common Algebraic Specification Language (CASL) [60], and extend it by considering priority information for operators, sorts, predicates and axioms as follows: Prioritised CASL specificationA prioritised CASL specification (PCS) is a tuple {a mathematical formula}s=〈ST,≲,O,P,A,prio〉 with:
      </paragraph>
      <list>
       <list-item label="•">
        a set {a mathematical formula}ST of sorts, along with a preorder ≲ that defines a sub-sort relationship;
       </list-item>
       <list-item label="•">
        a set {a mathematical formula}O of operators {a mathematical formula}o:s1×⋯×sn↦sr that map zero or more objects of argument sorts {a mathematical formula}s1,⋯,sn to a range sort {a mathematical formula}sr;
       </list-item>
       <list-item label="•">
        a set {a mathematical formula}P of predicates {a mathematical formula}p:s1×⋯×sn that map zero or more objects of argument sorts {a mathematical formula}s1,⋯,sn to Boolean values;
       </list-item>
       <list-item label="•">
        a set {a mathematical formula}A of axioms;
       </list-item>
       <list-item label="•">
        a function {a mathematical formula}prio:ST∪O∪P∪A↦N0 that assigns a priority to all elements in a specification. The lower the number, the lower the priority.
       </list-item>
      </list>
      <paragraph>
       A good motivation for using priorities can be found in prior work [20]. Intuitively, it is an instrument to express the salience level of elements in concept, and it also helps algorithmically to prune the search space, as described in Sec. 3. Goguen [34]'s algebraic view on blending suggests to compute the blend of input specifications as their categorical colimit (see e.g., [69]). The colimit is a general unification operation for categories, similar to the union operation for sets. In this case the categories are algebraic signatures, so that the colimit can be used to unify algebraic specifications, as described by Mossakowski [57]. The colimit requires morphisms to be defined between the signatures of algebraic specifications, in particular between the generic space and the input concepts. Our blending algorithm uses colimit of algebraic specifications as the basis for composing input spaces, as described in Sec. 3.5. We do consider priorities when computing the colimit, but use them instead as a means to reward the compression of structure in a blend. This supports [27]'s optimality principles, as described in Sec. 3.5.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       The notion of amalgams
      </section-title>
      <paragraph>
       As shown in [4], the process of conceptual blending can be characterised using amalgams[61], a notion that was developed in case-based reasoning as an approach to combine solutions coming from multiple cases. According to this approach, input concepts are generalised until a generic space is found, and pairs of generalised versions of the input concepts are combined to create blends.
      </paragraph>
      <paragraph>
       Formally, the notion of amalgams can be defined in any representation language {a mathematical formula}L for which a subsumption relation (⊑) between formulas (or descriptions) of {a mathematical formula}L can be defined. We say that a description {a mathematical formula}I1 subsumes another description {a mathematical formula}I2 ({a mathematical formula}I1⊑I2) when {a mathematical formula}I1 is more general (or equal) than {a mathematical formula}I2. Next, for any two descriptions {a mathematical formula}I1 and {a mathematical formula}I2 in {a mathematical formula}L we can define their unification, ({a mathematical formula}I1⊔I2), which is the most general specialisation of two given descriptions, and their anti-unification, ({a mathematical formula}I1⊓I2), defined as the least general generalisation of two descriptions, representing the most specific description that subsumes both. Intuitively, a unifier is a description that has all the information in both the original descriptions. The anti-unification {a mathematical formula}I1⊓I2 contains all that is common to both {a mathematical formula}I1 and {a mathematical formula}I2.
      </paragraph>
      <paragraph>
       An amalgam of two descriptions is a new description that contains parts from these original descriptions. For instance, an amalgam of ‘a red French sedan’ and ‘a blue German minivan’ could be ‘a red German sedan’; clearly, there are always multiple possibilities for amalgams, like ‘a blue French minivan’. An amalgam of two descriptions is defined as follows.
      </paragraph>
      <paragraph label="Definition 2">
       A description {a mathematical formula}A∈L is an amalgam of two inputs {a mathematical formula}I1 and {a mathematical formula}I2 (with anti-unification {a mathematical formula}G=I1⊓I2) if there exist two generalisations {a mathematical formula}I¯1 and {a mathematical formula}I¯2 such that (1) {a mathematical formula}G⊑I¯1⊑I1, (2) {a mathematical formula}G⊑I¯2⊑I2, and (3) {a mathematical formula}A=I¯1⊔I¯2 and A is consistent.
      </paragraph>
      <paragraph>
       This definition is illustrated in Fig. 2, where the anti-unification of the inputs is indicated as G, and the amalgam A is the unification of two concrete generalizations {a mathematical formula}I¯1 and {a mathematical formula}I¯2 of the inputs.
      </paragraph>
      <paragraph>
       The generalisation of a description of a language {a mathematical formula}L is usually done by means of generalisation operators [61]. Formally, a generalisation operator is defined as:{a mathematical formula} Intuitively, a generalisation operator ‘transforms’ a description into a more general (or equal) one. For instance, the description of a ‘red French sedan’ can be generalised to a ‘red European sedan’ but also to a ‘coloured French sedan’ or to a ‘red French car’, since, typically, more than one generalisation is possible. The anti-unification of our input descriptions – a ‘coloured European car’ – is obtained by keeping on generalising the descriptions until they are equal. The anti-unification serves as an upper bound of the generalisation space to be explored and plays the role of the generic space in conceptual blending, which states the shared structure of both concepts.{sup:2}
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Answer Set Programming
      </section-title>
      <paragraph>
       Answer Set Programming (ASP) is a declarative approach to solve NP-hard search problems (see e.g. [31], [2]). ASP is often used for realizing the deliberation and problem solving skills of autonomous systems (e.g., [16], [19]) and other forms of logical reasoning, such as epistemic or abductive inference [18], [17], decision making under uncertainty [8], and preference reasoning [7]. In this work, we explore its use for Computational Creativity and logical theory generalisation.
      </paragraph>
      <paragraph>
       An ASP program is similar to a PROLOG program in that it follows a non-monotonic semantics, takes logic programming style Horn clauses as input, and uses negation-as-failure (NaF). However, instead of using Kowalski [47]'s SLDNF resolution semantics as in PROLOG, it employs Gelfond and Lifschitz [32]'s Stable Model semantics, which makes it truly declarative. This means that the order in which ASP rules appear in a Logic Program does not affect the solution. Furthermore, the Stable Model Semantics has the advantage that Answer Set Programs always terminate, while PROLOG programs do not. For example, given a program {a mathematical formula}notp←q. and {a mathematical formula}notq←p., asking whether p holds results in an infinite loop for PROLOG, while ASP returns two stable models as solution, namely the sets {a mathematical formula}{p} and {a mathematical formula}{q}.
      </paragraph>
      <paragraph>
       An ASP program consists of a set of rules, facts and constraints. Its solutions are called Stable Models (SM). In this paper we only consider so-called normal rules [2], which are written as:{a mathematical formula} in which {a mathematical formula}a1,...,an are atoms and not is negation-as-failure. When {a mathematical formula}n=0 the rule {a mathematical formula}a0← is called a fact and the ← is omitted. A constraint is a rule of the form {a mathematical formula}←a1,…,aj,notaj+1,…,notan. Constraints are rules that are used to discard some models of a logic program.
      </paragraph>
      <paragraph>
       The stable models of an ASP program are defined in terms of the so-called Gelfond–Lifschitz reduction[32]. Let {a mathematical formula}LP be the set of atoms in the language of a normal logic program P, then for any set {a mathematical formula}M⊆LP, the Gelfond–Lifschitz reduction {a mathematical formula}PM is the definite logic program obtained from P by deleting:
      </paragraph>
      <list>
       <list-item>
        each rule that has a formula {a mathematical formula}nota in its body with {a mathematical formula}a∈M, and
       </list-item>
       <list-item>
        all formulæ of the form {a mathematical formula}nota in the bodies of the remaining rules.
       </list-item>
      </list>
      <paragraph>
       M is called a stable model of P if and only if M is the minimal model of {a mathematical formula}PM. A stable model M of an ASP program P contains those atoms that satisfy all the rules in the program and, consequently, represents a solution of the problem that the program P represents.
      </paragraph>
      <paragraph>
       ASP is interesting because it can capture complex knowledge representation problems, and also because efficient ASP implementations, such as clingo[29], exist. The clingo solver offers a step-oriented, incremental approach that allows to control and modify an ASP program at run-time, without the need of restarting the grounding of the solving process from scratch. To this end, a program is partitioned into a base part, describing the static knowledge independent of a step parameter t, a cumulative part, capturing knowledge accumulating with increasing t, and a volatile part specific for each value of t. The grounding and integration of these subprograms into the solving process is completely modular and controllable from a scripting language such as Python.
      </paragraph>
      <paragraph>
       The ASP implementation in this paper follows this methodology of specifying and solving a problem incrementally. For further details about incremental solving, we refer to [30], where several examples can be found.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Blending with amalgams
     </section-title>
     <paragraph>
      We employ an interleaved declarative-imperative amalgam-based workflow to search for generalisations of input spaces that produce and evaluate consistent blends. The blending theory in principle allows for any finite number {a mathematical formula}S≥2 input specifications, but in the implementation we use {a mathematical formula}S=2 for simplicity. The notion of consistency in our work refers to logical consistency of algebraic specifications.
     </paragraph>
     <section label="3.1">
      <section-title>
       System description
      </section-title>
      <paragraph>
       The workflow of our system is depicted in Fig. 3. Most of the reasoning is done using Answer Set Programming (ASP) by generating a sequence of theory transitions. The ASP implementation is combined with Python scripts that perform external information processing if necessary. The main purpose of the implementation is to realize the theory transitions that occur during the generalisation process. A theory transition can either be the removal of an element (generalisation) or the renaming of an element in a specification. Towards this, the input PCS {a mathematical formula}s1, {a mathematical formula}s2 are first translated into ASP facts, as described in Sec. 3.2. Second, {a mathematical formula}s1, {a mathematical formula}s2 are undergoing sequences of theory transitions that are guided by an ASP solver until a generic space is found. Each transition is represented by a fact {a mathematical formula}exec(γ,s,t), where t is an iterator and γ is a transition operator that removes or renames elements in the input specifications (see Sec. 3.3). The execution of transition operators is repeated until the generalised versions of the input specifications are compatible in the sense of Definition 1. We write {a mathematical formula}s(t) to denote the specification that results form the t-th transition of {a mathematical formula}s. For example, after the first theory transition, the house concept might be the concept of a house that is not situated on any medium. Note that in iterative ASP-solving, an iterator t causes atoms to be instantiated for a predefined number of steps (see e.g., [28], [29]).
      </paragraph>
      <paragraph>
       In order to find consistent blends, we apply the category-theoretical colimit[57] to compose transitioned input specifications. To this end, we use the HEterogeneous Tool Set (HETS) [58]. The colimit is applied on different combinations of transitions, and for each result we query theorem provers such as eProver and darwin, which are embedded in HETS, in order to check for consistency. An example for a consistent house-boat blend is the combination of the generalised boat on the medium water, but without a passenger, and a generalised house with a resident, but without a medium, where ‘passenger’ in ‘boat’ is renamed to ‘resident’ in house.
      </paragraph>
      <paragraph>
       To eliminate uninteresting blends from our search process, we consider that more promising blends are those that require less generalisations. Consequently, we go from less general generalisations to more general generalisations and stop when a consistent colimit is achieved. Thereafter, the result is evaluated using certain metrics that are inspired by Fauconnier and Turner [27]'s optimality principles of blending to assess the quality of the blend (see Sec. 3.5). Note that different stable models, and therefore different generalisations and renamings, can be found by the ASP solver. Each combination leads to a different set of blends.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Modelling algebraic specifications in ASP
      </section-title>
      <paragraph>
       In order to find the generic space and to avoid inconsistencies that arise from the naive combination of input specifications, we weaken prioritised CASL specifications using transition operators in a step-wise search process. Firstly, renaming operators modify specifications by renaming their elements. Secondly, removal operators generalise algebraic specifications by removing operators, sorts, predicates or axioms. In the following, we use t to denote a step-counter that represents the number of transitions that a specification has undergone. We assume that sorts, operators and axioms for data (in the sense of Definition 1) are common among input specifications, so that we do not need to consider them in the ASP-based reasoning process. With this, we represent prioritised CASL specifications in ASP as follows:
      </paragraph>
      <paragraph>
       ►  For each sort s in a specification {a mathematical formula}s with a parent sort {a mathematical formula}sp we state the facts:{a mathematical formula}{a mathematical formula} A fact (3a) assigns a sort s to a specification {a mathematical formula}s at a step t, and (3b) assigns a parent sort.
      </paragraph>
      <paragraph>
       ►  For each operator{a mathematical formula}o:s1×⋯×sn↦sr in a specification {a mathematical formula}s we have:{a mathematical formula}{a mathematical formula}{a mathematical formula}(4b), (4c) state the argument sorts and the range sorts of an operator. {a mathematical formula}1…n determine the position of the argument sort and rng is simply a constant to denote that the sort is the range sort of the operator.
      </paragraph>
      <paragraph>
       ►  Similarly, for each predicate{a mathematical formula}p:s1×⋯×sn in {a mathematical formula}s we generate the LP facts:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       ►  For each axiom a we determine an equivalence class of that axiom, denoted {a mathematical formula}eqa, by passing the axiom to a respective Python function.{sup:3} All logically equivalent axioms have the same equivalence class, e.g., {a mathematical formula}¬a∨b has the same equivalence class as {a mathematical formula}a→b. We also determine the elements, i.e, sorts, operators and predicates, that are involved in an axiom. This information is used in the preconditions of removal operators. For example, operator removal has the precondition that there exists no atom that involves the operator. Having computed the equivalence class {a mathematical formula}eqa and determined {a mathematical formula}ne elements that are involved in an axiom, we generate the following facts for each axiom a in a specification {a mathematical formula}s.{a mathematical formula}{a mathematical formula}{a mathematical formula} We represent the priority function prio of a PCS as facts {a mathematical formula}priority(s,e,vp) for each element e in a specification {a mathematical formula}s. Compatibility among two input specifications, as defined in Definition 1, is represented by atoms {a mathematical formula}incompatible(s1,s2,t), which are triggered by additional LP rules if, for {a mathematical formula}s1 and {a mathematical formula}s2, at step t, (i) sorts or subsort relationships are not equal, or (ii) operator or predicate names are not equal, or (iii) argument and range sorts of operators and predicates are not equal, or (iv) axioms are not equivalent.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Formalising transition operators in ASP
      </section-title>
      <paragraph>
       We consider two kinds of transition operators for PCS. The first kind involves the renaming of an element to the name of an element in another input specification. Since we consider syntactically equal elements to be conceptually equal in our implementation, this can be seen as identifying the commonalities among input spaces. The second kind is generalisation and involves the removal of an element in a specification. Generalisation operators are executed after all renaming actions have happened. Considering Definition 1, it is trivial to see that removal of elements in a PCS are generalisation operators in the sense of Eq. (1).
      </paragraph>
      <paragraph>
       Each generalisation operator is defined via a precondition rule, an inertia rule, and, in case of renaming operations, an effect rule. Preconditions are modelled with a predicate poss that states when it is possible to execute a transition, and inertia is modelled with a predicate noninertial that states when an element of a specification stays as it is after a transition. Effect rules model how a transition operator changes an input specification. We represent the execution of a transition operator with atoms {a mathematical formula}exec(γ,s,t), to denote that a generalisation operator γ was applied to {a mathematical formula}s at a step t.
      </paragraph>
      <paragraph>
       Removal operators. A fact {a mathematical formula}exec(rm(e),s,t) denotes the removal of an element e from a specification {a mathematical formula}s at a step t. It has different precondition rules for removing axioms (7a), operators (7b), predicates (7c) and sorts (7d):{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The precondition (7a) for removing an axiom from a specification is that an atom {a mathematical formula}exOtherSpecWithoutEqivAx(s,e,t) holds. Such atoms are produced, if there exists at least one other specification{sup:4} that does not have an axiom of the same logical equivalence class. For the removal of other elements we have a similar precondition, i.e., {a mathematical formula}exOtherSpecWithoutElem(s,e,t), which denotes that an element can only be removed if it is not involved in another specification. Such preconditions are required to allow only generic spaces that are least general for all input specifications, in the sense that elements can not be removed if they are contained in all specifications. We also require operators, predicates and sorts not to be involved in any axiom before they can be removed (denoted by {a mathematical formula}0{ax(s,A,t):axInvolvesElem(s,A,e,t)}0). Precondition (7d) for removing sorts has the additional requirement that no operator or predicate with an argument or range of the sort to be removed exists in the specification, which is implemented with noOpUsesSort and noPredUsesSort facts respectively. These are triggered by additional simple LP rules. Another condition for sort removal is that the sort is not the parent sort of another sort. Consequently, for sort removal, all axioms, operators and predicate that involve the sort must be removed first, and child sorts must also be removed first. The inertia rules for removing elements from a specification are quite simple:{a mathematical formula} All noninertial atoms will cause an element e to remain in a specification (see rule (12a), (12b), (12c), (12d)).
      </paragraph>
      <paragraph>
       Renaming operators. A fact {a mathematical formula}exec(rename(e,e′,s′),s,t) denotes the renaming of an element e of a specification {a mathematical formula}s to an element {a mathematical formula}e′ in a specification {a mathematical formula}s′. In contrast to removal, renaming can only be applied to predicates, operators and sorts. Axioms are automatically rewritten according to the renamings of the involved elements. Again, we have different preconditions for renaming operators (9a), predicates (9b) and sorts (9c):{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} A common precondition for all three renaming operations is that the element e must exist in the specification {a mathematical formula}s, and that {a mathematical formula}e′ must exist in {a mathematical formula}s′. Furthermore, it must not be the case that {a mathematical formula}e′ is already part of {a mathematical formula}s, and that e is part of {a mathematical formula}s′. In case of renaming operators and predicates, the argument and range sorts of e and {a mathematical formula}e′ must also be equivalent for the renaming to become possible. For example, an operator {a mathematical formula}situatedOn:Object↦Medium can not be mapped to an operator {a mathematical formula}usedBy:Object↦Person, which has a different range sort.
      </paragraph>
      <paragraph>
       The inertia rules for renaming elements e in a specification are analogous to the inertial rule for removing elements:{a mathematical formula} For renaming, we have the following set of effect rules that assign the new name for the respective element:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} In general, the rules state that a specification will contain an element {a mathematical formula}e′ at a step {a mathematical formula}t+1 if an element e has been renamed to {a mathematical formula}e′ at step t. Rules (11a)–(11e) state how renaming sorts affects the generalization. It also considers the effects on parent-child relations as well as predicate and operator arguments and range. Rules (11f), (11g) and (11h), (11i) describe the effects of renaming operators and predicates respectively. Rule (11j) states how the auxiliary predicate axInvolvesElem is affected by renaming.
      </paragraph>
      <paragraph>
       Inertia. In order to use the inertia rules (8, 10), we need the following rules to state that elements e remain in a specification {a mathematical formula}s if they are inertial:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Updating axiom equivalence. When operators, predicates or sorts that are involved in an axiom are renamed, then the axiom's equivalent class changes. Determining logical equivalence of FOL axioms is a well understood research domain on its own, and we make use of existing theorem proving tools here. Towards this, we use an external Python function renameEleAndGetNewEqClass in rule (13) during the ASP solving process, which updates the equivalence class by querying theorem proving tools that determine a new equivalence class for an axiom if elements are renamed. This happens by accessing an internal dictionary of axioms within Python, that is built dynamically during the ASP grounding process.{a mathematical formula} Additional rules that update the axInvolvesElem atoms if elements are renamed are also part of our implementation.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Transition search process
      </section-title>
      <paragraph label="Definition 3">
       The search process that we use ASP for, is to find a generic space and transitioned versions of the input specifications which lead to a consistent blend. This is done by successively applying transition operators to the input specifications. Herein, we first apply only renaming operators to find the commonalities among input specifications. We then ‘cut off’ elements that the input specifications do not have in common by applying removal operators. Note that a simple intersection operation (as in set theory) is not possible because of the preconditions that the transition operators have. These impose a strong restriction on the allowed order in which transition operators may occur and make the problem inherently non-monotonic. A sequence of transition operators defines a transition path, which itself consists of a commonalisation path followed by a removal path. Commonalisation, removal, and transition pathsLet {a mathematical formula}S={s1,…,s|S|} be input specifications to be blended. Let {a mathematical formula}{γ1,…,γn} be renaming operators and {a mathematical formula}t1&lt;⋯&lt;tn be steps. Then we call a set of atoms {a mathematical formula}C={exec(γ1,sx,t1),⋯,exec(γn,sy,tn)} a commonalisation path of {a mathematical formula}S (with {a mathematical formula}sx,sy∈S). Let {a mathematical formula}{γn+1,…,γm} be removal operators and {a mathematical formula}tn+1&lt;⋯&lt;tm be steps. Then we call a set of atoms {a mathematical formula}R={exec(γn+1,su,tn+1),⋯,exec(γm,sv,tm)} a removal path of {a mathematical formula}S (with {a mathematical formula}su,sv∈S). We call {a mathematical formula}C∪R a transition path of {a mathematical formula}S.
      </paragraph>
      <paragraph label="Definition 4">
       We refer to transition paths in Section 3.5, when we describe how we combine different transitioned versions of the input specifications, which are generated by prefixes of removal paths. Formally, the prefix of a removal path is the subsequence of its first l removal operators. Removal path prefixGiven a removal path {a mathematical formula}R={exec(γn+1,su,tn+1),⋯,exec(γm,sv,tm)}, we call {a mathematical formula}Rpre={exec(γn+1,su,tn+1),⋯,exec(γl,sw,tl)} a prefix of R if {a mathematical formula}l≤m (with {a mathematical formula}su,sv,sw∈S).
      </paragraph>
      <paragraph>
       A general problem of amalgams is that the space of possible transition paths and hence also the space of possible blends is usually very huge. To prune the search space, we only consider those transition paths where elements with a low priority are removed before elements with a higher priority, and where elements with a high priority are commonalised before elements with a low priority.{sup:5}
      </paragraph>
      <paragraph>
       Since we have separated the commonalisation and removal process we need to decide when we switch from the one to the other. The simplest solution would be to switch when all possible commonalities have been found, but this would prevent the system from being flexible in that it would not generate blends where not all possible commonalisations are considered. As an example, consider blending house and boat to obtain the boat house concept, described in Sec. 4.1. In this blend, not all commonalities are considered but the concept of a boat-house is definitely interesting. Hence, we define a predicate findCrossSpaceMapPhaseFinished(t) which determines the step t when the search for the cross space mapping, i.e., the commonalities is finished. This is used in the following choice rule for the commonalisation search process:{a mathematical formula} The renameAct predicate denotes that a is a renaming operator. The removal and generic space search process is done using another choice rule as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The predicate notGenericReached is triggered when the generic space has been reached, i.e., when the search terminates because the generalised versions of all input specifications are equal. This is the case when all axioms are logically equivalent, and all sorts, predicates and operators are syntactically equal. The removeAct predicate denotes that a is a removal operator.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Composition of transitioned input spaces
      </section-title>
      <paragraph label="Definition 5">
       The transition part of our framework generates one stable model for each combination of transition paths that leads to a generic space. The next step in the amalgam-based workflow is to compose transitioned versions of input specifications to generate a candidate blend (see Fig. 3). The key component of this composition process is the categorical colimit [57] of the generalised specifications and the generic space. This requires also the morphisms from the generic space to the input specifications, which are inherently given with the commonalisation path (see Definition 3). Since the colimit of algebraic specification signatures does not consider consistency and priority information, we need to define a composition operation for prioritised CASL specification, that is based on the colimit but that also considers priorities and consistency. Composition of PCSThe composition {a mathematical formula}c of n PCS {a mathematical formula}S, a generic space {a mathematical formula}g and one total morphisms {a mathematical formula}m:g↦s for each {a mathematical formula}s∈S is defined as follows: Let {a mathematical formula}scolimit be the colimit of the PCS without the priorities, i.e., the colimit of the algebraic CASL specifications that underly the PCS. Let the morphisms {a mathematical formula}m1c:s1↦scolimit,…mnc:sn↦scolimit be defined with respect to these specifications. Then the composition {a mathematical formula}c of {a mathematical formula}S is a PCS that is constituted by the colimit {a mathematical formula}scolimit, enriched with the following priority function for elements e in the composed PCS:{a mathematical formula} Hence, to assign the priorities for the elements e in the composition, Equation (16) simply adds up the priorities of the respective source elements {a mathematical formula}es in the morphisms. The intuition behind this is to give those elements in a blend a higher priority that represent compressed structure. For example, if two operators in two input spaces point to the same operator in the blend, then the blend compresses the structure imposed by the operators. Similar for axioms, sorts and predicates. This supports Fauconnier and Turner [27]'s optimality principles and helps to evaluate the blends, as we explain in Sec. 3.6.
      </paragraph>
      <paragraph>
       One may argue that also the product or the maximum of the priorities of the input elements could be used instead of the sum. However, during our experiments we found that just using the maximum does not reward compression enough, and the product rewards compression too much. The intuition of using the sum to add up the priorities is that a single compressed target element in a composition should be exactly as important as its individual input elements together.
      </paragraph>
      <paragraph>
       For example, consider the predicate {a mathematical formula}liveIn:Person×House of the House specification and the predicate {a mathematical formula}ride:Person×Boat of the Boat specification, as shown in Fig. 4. Both are mapped to the same element in the composition. Note that, due to our categorical approach, the syntactic label of that element in the composition is not important. We use either the label of one of the input specifications, or we concatenate the symbols of the input specifications with an _ character in a postprocessing step, as, e.g., {a mathematical formula}liveIn_ride:Person_Passenger×House_Boat. Since {a mathematical formula}liveIn_ride is commonalised, it carries the information of both input spaces and it should therefore also have the joint priority of both input elements, as implemented by summing up the priorities of the corresponding operators liveIn and ride in the input spaces (see Definition 5).
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       Evaluating blends
      </section-title>
      <paragraph>
       The next step in the blending process is to evaluate the composition as a whole, according to several factors that reflect the rather informal optimality principles proposed by Fauconnier and Turner [27]. To this end, we take the following three evaluation metrics into account:
      </paragraph>
      <list>
       <list-item label="1.">
        We support blends that keep as much as possible and the most important parts from their input concepts by using the priority information of elements in the input concepts. This supports those optimality principles in [27], which imply that as much as possible from the input spaces should be projected to the blend, namely at least the so-called unpacking, web and integration principles.
       </list-item>
       <list-item label="2.">
        We support blends that maximise common relations among input concepts as a means to compress the structure of the input spaces. Relations are made common by appropriate renamings of elements in the input specification. This supports the vital relations principles in [27].
       </list-item>
       <list-item label="3.">
        We support blends where the amount of information from the input specifications is balanced. This supports the multi-scope property of blends, which is described by Fauconnier and Turner [27] as “... what we typically find in scientific, artistic, and literary discoveries and inventions.”
       </list-item>
      </list>
      <paragraph>
       The rationale behind choosing the above metrics is to have a simple but effective way to evaluate the blends from two perspectives: the informational content and the content structure. On the one hand, we want to favour those blended concepts that maintain the information from the input concepts as much as possible. This is done by a first metric defining the amount of information of a blend as the sum of the priorities of all its elements. On the other hand, we also want to favour those blends that maintain the structure of the input concepts as much as possible. This is done by other two metrics, blend compression, which essentially measures how many morphisms were applied to the different elements, and blend imbalance, which penalizes those blends created mainly using elements of one of the input spaces. We now define these metrics formally.
      </paragraph>
      <paragraph>
       The amount of information in a PCS is given as:{a mathematical formula} Equation (17) defines the amount of information in a PCS as the sum of the priorities of all of its elements. A measure for the compression of structure in a composition {a mathematical formula}c with n morphisms {a mathematical formula}M={m1:s1↦c,…,mn:sn↦c} is defined as:{a mathematical formula}{a mathematical formula} The compression value of the composition {a mathematical formula}c is the sum of the compression values of its individual elements (denoted by eleComp). The compression value of an individual element is the priority of that element, multiplied by the number of morphisms to it, and normalised by the total number of input morphisms.
      </paragraph>
      <paragraph>
       We also account for the balance of information from both input specifications. That is, we consider blends to be better where the amount of information from the input specifications is similar. Towards this we define an imbalance penalty as the half of the difference of the amount of information from the input specification as follows:{a mathematical formula} Taking only the half of the difference as imbalance penalty turned out to be more useful than taking the full difference, because this still encourages blends which have more information in total, even if they are imbalanced. The final evaluation of a blend is done by summing up the three evaluation metrics and by considering logical consistency as follows:{a mathematical formula} Note that the imbalance penalty can never be bigger than the information value, so that the blend value is always positive. An interesting extension of computing the value is to parameterise the different metrics. However, we have so far not experimented with this.
      </paragraph>
      <paragraph>
       The transition path pruning described in Sec. 3.4 supports the information value and compression value metrics because by removing low-priority elements before high-priority elements (information value), and by commonalising high-priority elements before low-priority elements (compression value), low-value blends are not generated. We have not yet implemented a feasible solution to also consider the imbalance penalty in the pruning mechanism.
      </paragraph>
      <paragraph>
       The issue of how blends are to be evaluated is an important one in the theory of conceptual blending, and in addition to these evaluation metrics, which are generic for any kind of blends, more domain specific criteria can (and eventually should) be added to the blending framework. For this reason we have also explored how different audiences and their respective values can be brought into the blend evaluation process [12] and we have proposed evaluation techniques that draw from argumentation theory [9] and coherence theory [75]. Beyond the evaluation of blends, the Computational Creativity community has extensively studied how to evaluate the creativity of computational systems in general, and several models have been proposed [72], [6], [45]; we have applied some of these models to the evaluation of our framework [62], as we describe in the following Section 4.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Proof of concept
     </section-title>
     <paragraph>
      To demonstrate our system we first present the use case of the house-boat, which primarily serves illustrative purposes. Then we consider several examples from two real-world domains where creativity is important, namely mathematics and music. The examples for harmony invention (Sec. 4.2), lemma invention (Sec. 4.3) and cross-domain blending (Sec. 4.4) are also illustrated in the supplementary video.
     </paragraph>
     <section label="4.1">
      <section-title>
       The house-boat blend
      </section-title>
      <paragraph>
       A classical concept blending example is the blend between the concepts house and boat [34], [27]. In Fig. 4 we depict the axiomatisation of these concepts which is similar to how they are proposed in [35]. Priorities are equal for all elements in the specifications, so we omit them here for brevity. The CASL theories for House and Boat introduce the sorts, operators and predicates that form the mental spaces house and boat by focusing on particular properties of these concepts. The precise formalisation is not critical at this point, different ones exist [35], [63], but all provide similar distinctions. In principle, the House and Boat specifications could be directly blended (they do not generate any inconsistency), but the blended specification is not considered a good blend since it does not maximise the common relations among the two input specifications. Instead, more interesting blends are created depending on how the House and Boat are transitioned. A house-boat blend is created when the medium on which a house is situated (land) becomes the medium on which boat is situated (water), and the resident of the house becomes the passenger of the boat. In our system, this is achieved using the generic space depicted in Fig. 5. This generic space is obtained by removing the {a mathematical formula}on(house,land) axiom from the House specification, the water operator and the {a mathematical formula}on(boat,water) axiom from the Boat specification, and by renaming the operators ride to liveIn, passenger to resident, boat to house and the sort Boat to House in the Boat specification. The morphisms between the generic space and the input spaces are shown in the right part of Fig. 5.
      </paragraph>
      <paragraph>
       The colimit that results from the generic space and the above morphisms is a theory in which the boat is a house and the passenger is a resident of the house-boat (see Fig. 6, left). Our system is also able to generate other classic blends. For instance, a boat-house is created which turns the boat into a person by renaming resident to boat and Person to Boat, along with some other minor generalisations (see Fig. 6, right). Here, the colimit expresses a blend in which the boat lives in the house.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Harmony invention for music composition
      </section-title>
      <paragraph>
       In the music domain we invent novel chord progressions by blending existing ones, and demonstrate how our approach extends the musicological framework proposed in our previous work [20]. Specifically, we show how we blend chords to invent novel cadences – short chord progressions that can be understood as ‘punctuation’ within a music piece. While the system depicted in [20] is limited to blending single chords, we are now able to blend whole chord progressions, as for example the perfect cadence and Phrygian cadence. We present the relevant parts, i.e., the first chord of each cadence, as algebraic specifications in Fig. 7.
      </paragraph>
      <paragraph>
       Both specifications are built on a background theory ChordProg about chord progressions, which defines the predicate succ to denote the successor relation among chords, the predicate absNote to determine the absolute notes of a chord, and the predicate relNote to determine the notes of a chord relative to the root note (indicated by the root operator). ChordProg also contains an axiom {a mathematical formula}hasRelNote(c,n)⇔hasAbsNote(c,plus(n,root(c)) that defines the relation between absolute and relative notes in the background theory, and that states when a chord is dissonant. Dissonance is captured via axioms that forbid certain relative note combinations. For example, they express that a chord cannot have a major third (relative note 4) and a minor third (relative note 3) at the same time, i.e., {a mathematical formula}∀c:Chord.¬(relNote(c,3)∧relNote(c,4)). Given a C major key, the Phrygian cadence involves a {a mathematical formula}B♭min chord followed by a C chord, and the perfect cadence is a G7 chord followed by a C. The priorities of the axioms that assign notes to the chords are musicologically justified as described in [20], i.e., the relatives are given a higher priority, and those absolute notes which are salient within the key are also given a higher priority. In addition to these axioms, our system also considers the priority of individual chords which are represented as operators c1Perf (G7 chord), c2Perf (C chord), c1Phryg ({a mathematical formula}B♭min chord) and c2Phryg (C chord).
      </paragraph>
      <paragraph>
       Blending the two cadences produces a Tritone substitution cadence as the result with the highest value. The tritone substitution was invented in jazz music decades after the Phrygian and perfect cadence. It takes the D♭ note from the first chord of the Phrygian cadence, specified by {a mathematical formula}absNote(c1Phryg,1), as root of the first chord of the novel Tritone cadence. The blending also adds the relative seventh of the G7 chord of the perfect cadence ({a mathematical formula}relNote(c1Perf,10)), as well as the major third ({a mathematical formula}relNote(c1Perf,4)) and the fifth ({a mathematical formula}relNote(c1Perf,7)) which are present in both chords. The result is a {a mathematical formula}D♭7 chord as first chord of the Tritone substitution. The system also allows to blend the second chord of one cadence with the first chord of another, so that a novel chord progression of three notes is produced. Note that, due to the renaming operators, this can be done on the level of cadences and chord progressions as a whole, and not only on the level of single chords.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Lemma invention for theorem proving
      </section-title>
      <paragraph>
       In the mathematics domain, we present a general approach for using blending to exploit existing creative lemmas in a well understood theory, to automatically generate creative lemmas in another less understood theory. For illustration, consider the prioritised theories of natural numbers and lists shown in Fig. 8. An illustration and demo of this blending application is provided in the supplementary video (after 7:00).
      </paragraph>
      <paragraph>
       Important elements of these specifications are the constructor operators s, i.e., the successor function, and {a mathematical formula}cons, i.e., the constructor for lists. Due to their importance, we give them a high priority. Of particular interest here are also the theorems (NT) and (LT), which are also given a high priority because they provide important insights about the relation between the tail-recursive functions {a mathematical formula}qrev and {a mathematical formula}qsum, and their primitively recursive counterparts rev and sum. Proving such theorems by induction is very hard due to the absence of a universally quantified variable in the second argument of the tail-recursive version [42]. An expert's solution here is to use a lemma that generalises the theorem. An example of such a generalisation is the eureka lemma (NL) in the naturals, which we assume to be known in this scenario. Discovering such lemmas is in general a very challenging and well-known problem – see [56], [43] for example. Our goal is to use blending to discover an analogous lemma which facilitates the inductive proof of (LT) in List.
      </paragraph>
      <paragraph>
       The first step of blending is to find a generic space. However, this is problematic because the constructor {a mathematical formula}s(n) in the naturals is unary, whereas the constructor {a mathematical formula}cons(h,l) in lists is binary. In order to resolve this problem we take inspiration from a classical set theoretic construction of the naturals as the cardinality of a set (see [1] for example). That is, we describe the theory of the naturals as a theory of lists of exactly the same element.{sup:6} As a result, we generalise the theory of naturals by adding an extra argument to the successor function, i.e., {a mathematical formula}s(n) becomes {a mathematical formula}s(c,n) where c is some canonical element of a canonical sort C. The definition of plus, for example, then simply becomes {a mathematical formula}plus(s(c,n),m)=s(c,plus(n,m)). This way we obtain a correctly typed generic space by interpreting the renaming and removal operators from the ASP solver, which allows us to associate the constructors of Nat and List with the following generalisation paths{sup:7}:{a mathematical formula}
      </paragraph>
      <paragraph>
       After applying the respective renamings and removals, a generic space is reached, using the symbols from the List theory. Note, that even though the symbols of the lists theory are used in the generic space, their meaning is now much more general because they map to both, the List and the Nat theory, and represent now analogies between both theories as depicted in Table 1. That is, the generic space is a general theory with sorts for the constructed data types and their elements, a binary constructor, a terminal element, a primitively recursive function, and a tail-recursive function which is defined in terms of the auxiliary function. After finding the generic space, our framework iterates over different combinations of transitioned input specifications and computes the colimit. It then checks the colimit's consistency and computes the blend value. In this example, the highest composition value for a consistent colimit is 90, where the specifications that result from the 4th transition of List and the 8th transition of Nat are used as input. The result is a theory of lists with the newly invented lemma {a mathematical formula}app(rev(x),y)=qrev(x,y) which can be used successfully as a generalisation lemma to prove (LT).
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Cross-domain blending
      </section-title>
      <paragraph>
       So far we only considered input concepts from the same domains, i.e., we blend chord progressions with chord progressions and mathematical theories with mathematical theories. However, one of the biggest challenges in creative systems is being able to deal also with concepts coming from different domains. Generally, in cross-domain blending, one aims to transfer the knowledge of the two domains, to create something new, possibly by some adaptation. Blending multi-domain concepts is challenging, since different domains contain different knowledge and different symbols and representations that need to be cross-mapped in order to find new meaningful blended concepts. Our framework is general enough to blend concepts from different domains, and in this example, we show how we can blend chords with mathematical theories. We refer to our supplementary video for a detailed illustration (after 8:30) and for audio samples (after 18:00).
      </paragraph>
      <paragraph>
       In what follows we construct theories via blending which specify a logical hull. This means that the definitions in the theories need to be evaluated in order to determine the contents of the theory. In particular we make use of recursive functions. Evaluating these on all inputs gives facts about the theories about which we can reason.
      </paragraph>
      <section label="4.4.1">
       <section-title>
        Group theory and chord construction
       </section-title>
       <paragraph>
        Consider the case of blending the specification of cyclic groups of elements with a specification for chords defined via intervals between their notes, as shown in Fig. 9.
       </paragraph>
       <paragraph>
        The general theory of a group in mathematics is the combination of a set of elements {a mathematical formula}G and a binary operation ∼. A group {a mathematical formula}(G,∼) has the following axioms:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Extending the notion of group to a cyclic group, involves restricting the set of elements to be finite, and to introduce the notion of a generator element. The size of the set is then given by an order o. Elements of the group can be constructed with successive applications of the binary operation on the generator element and we introduce the shorthand {a mathematical formula}λx,y.xy to denote successive application; for example {a mathematical formula}g3=g∼(g∼g). We then add the following axioms about a cyclic group,{a mathematical formula} This axiom means that the inverse ({a mathematical formula}x−1) of an element x can be constructed also from the generator element, as can the identity element e.
       </paragraph>
       <paragraph>
        In the CASL theories shown in Fig. 9, we model these axioms in the specification CyclicGroup and can compute the elements of the cyclic group using the function binop for ∼ and introduce the recursive function binops for the successive application operator ({a mathematical formula}λx,y.xy). We also introduce a predicate hasElement which defines the elements of the cyclic group.
       </paragraph>
       <paragraph>
        In the case of the generator chord specification shown also in Fig. 9 we extend the notion of chord previously defined in Sec. 4.2 to include a “generator note” which is included as a relative note in the chord. Thus a generator chord with generator note 3 will always contains a minor third. We also introduce the notion of adding an interval with the operator plus.
       </paragraph>
       <paragraph>
        In our case, the generic space was computed as depicted in Table 2. During blending we used a priority of 1 for all elements. This leads to the blend specification show in Fig. 10.
       </paragraph>
       <paragraph>
        Conceptually this blend corresponds to a specification of a chord, whose notes are generated using the axioms of a cyclic group of order 12 – the number of notes in a scale. The specification alone does not define the notes in the chord – it defines a way of calculating the specific notes given a generator note or interval. Calculating the logical hull of the specification given a particular instantiation of gennote gives us the notes in the chord. Specifically evaluating the function binops over the natural numbers generates the notes which exist relatively in the logical hull by virtue of the axiom {a mathematical formula}hasRelNote(chord,binops(gennote,n)).
       </paragraph>
       <paragraph>
        A theorem of cyclic group theory is that if the prime factors of the generator do not divide the cardinality of the set, then it will generate every member of the set. In this case, the numbers which do not divide 12 – the number of notes in a scale – is the set {a mathematical formula}{1,5,7,11}. Let us first discuss the significance of the chord specifications generated using generated notes which do divide 12 and hence form subgroups, These are itemised here by the axiom which is added to the specification to generate chord by calculating the logical hull. . gennote = 2This corresponds to adding a relative major second to the specification. The logical hull of adding this axiom to the CyclicGroupChordBlend gives us the relative notes {a mathematical formula}{0,2,4,6,8,10} which is a chord constructed from the whole tone scale. This can sometimes be used as an altered chord. For example in the key of C this gives us {a mathematical formula}{C,D,E,F#,A♭,B♭}. Generalising this chord by removing some elements allows us to create various potential chords including a {a mathematical formula}C7♭13, a C augmented or even a C9.. gennote = 3This corresponds to adding a relative minor third to the specification. The logical hull of adding this axiom to the CyclicGroupChordBlend gives us the relative notes {a mathematical formula}{0,3,6,9} which specifies a diminished chord. For example, in the key of C, this is {a mathematical formula}{C,Eb,F#,A}, which is a diminished chord. This is interesting as it forms the top 4 notes of an A♭7♭9 chord, which is a modified dominant chord used very often in jazz to resolve to the key of D♭. Because the chord is naturally cyclic (on account of the blend with cyclic group theory), it can equally be used to transition to the keys of E, G or B♭ meaning that its function is very versatile. Bach used this versatility of the diminished chord to perform seemless but unexpected key changes in his pieces very often.. gennote = 4This corresponds to adding a relative major third to the specification. The logical hull of adding this axiom to the CyclicGroupChordBlend gives us the relative notes {a mathematical formula}{0,4,8} which specify an augmented chord. In the key of C this is {a mathematical formula}{C,E,A♭}. This is often used as a transition chord.. gennote = 6This corresponds to adding a diminished fifth to the specification. This only produces the two notes {a mathematical formula}{0,6} and as such is not particularly interesting except to provide a means for dissonance within a piece.. gennote = 8This is equivalent to the situation where we add . gennote = 4. gennote = 9This is equivalent to the situation where we add . gennote = 3. gennote = 10This is equivalent to the situation where we add . gennote = 2
       </paragraph>
       <paragraph>
        This is conceptually uninteresting as the chord is formed sequentially by playing the chromatic scale, and hence almost immediately too dissonant to have function.. gennote = 5This corresponds to adding a perfect fourth, thus generating the sequence of relative notes {a mathematical formula}{0,5,10,3,8,2,6,11,4,9,2,7}. This corresponds to the way in which tetrachords are formed. For example in C one could play {a mathematical formula}{C,F,B♭,E♭} – as specified by the initial 4 notes in this sequence. This is the sort of chord that McCoy Tyner uses often to create a modern accompanying sound.. gennote = 7This corresponds to adding a perfect fourth, thus generating the sequence of relative notes {a mathematical formula}{0,7,2,9,4,11,6,1,8,3,10,5}. This corresponds to playing chords constructed by incrementing intervals of 5ths. For example in C one could play {a mathematical formula}{C,G,D,A} – as specified by the initial 4 notes. This constitutes a suspended type of chord.. gennote = 11This corresponds to adding a major 7th incrementally, thus generating the sequence of notes {a mathematical formula}{0,11,10,9,8,7,6,5,4,3,2,1}. Enforcing the constraint that the constructed chord must consist of increasing intervals makes it unplayable and very dissonant. We do not know of any piece where this type of chord is employed.
       </paragraph>
      </section>
      <section label="4.4.2">
       <section-title>
        Progression theory and constructing Coltrane changes
       </section-title>
       <paragraph>
        In a similar way to chord construction, one can construct chord progressions using blends which involve cyclical groups. The only difference is that each number is associated either with a chord or the tonal centre of a cadence. Fig. 11 shows how the cyclic group can be defined using the specification of list given in Fig. 8. Polymorphism is modelled here using the CASL with operator where the elements of the list in the list spec can be defined as a particular sort.{a mathematical formula}
       </paragraph>
       <paragraph>
        In order to model cyclic groups in a more computational way, we introduce a function calc_subseq which calculates a list of elements in a group of a certain order. The binary operation associated with the group is constrained by introducing a partial minus operation into the natural numbers. The idea is then that a list of elements of a cyclic group can be associated with tonal centres to form a progression. The tonal centre can be simply a chord, or as is shown in Fig. 11, a perfect cadence. The progression has a function calc_prog which shows how to compute a list of chords defining the progression. The operator lin defines a list of input tonal centres. This way, the list of tonal centres defined by computing different cyclic groups of order 12 can generate interesting progressions. For example, Fig. 11 shows a refined specification Cyc12, which defines an order of 12, and a generator element of 4. The blend then produces a theory which has successive perfect cadences at tonal centres determined by the list of elements of the group. The Generic space and morphisms is shown in Table 3. Depending on the choice of value for gen, and the choice of cadence, different progressions are generated. In the case of the Cyc12 specification we generate a progression known in jazz as Coltrane Changes. With a generator of 4, subseq is calculated as 0,8,4. If these are interpreted as the tonal centres of progressive perfect cadences as is specified by the blend, then in the key of B major this becomes | F#7 B | D7 G | B♭7 E♭ | which is (excepting the initial dominant F#7) exactly how the iconic John Coltrane tune Giant Steps is started.
       </paragraph>
       <paragraph>
        An example of such a progression (with C as root) is | D♭7 C| F#7 F | B7 B♭ | E7 E♭ | A7 A♭ | D7 D♭ | G7 F# | C7 B | F7 E | B♭7 A | E♭7 D | A♭7 G |. As far as the authors know this has not been used in any existing composition. The above examples show that using this approach both recreates existing creative leaps in the theory and composition of jazz progressions, and also creates some previously unused progressions, which cannot be discovered in existing compositions. The technique of employing conceptual blending allows elements of music theory to exist in the blend, together with elements from the mathematical theory of cyclic groups. Had the system simply picked notes from integer sequence generation, the constraints from music theory that exist within the ListChord theory would not have been expressed, and notions of cadences (as discussed in Sec 4.2) and their associated constraints would have rendered an entirely unconstrained chord and progression theory. The restriction of the resulting blends to musically surprising, yet viable progressions can be attributed directly to the approach taken in this paper.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Several approaches of formal and computational models for conceptual blending have been proposed [11], [13], [12], [20], [21], [49], [35], [83], [63], [64], [33], [36]. Many of these models are inspired by the work of Fauconnier and Turner [27], but there are also other approaches emanating from analogical reasoning [76] and neuroscience [79].
     </paragraph>
     <paragraph>
      Amalgam-based conceptual blending have been developed to blend {a mathematical formula}EL++ concepts in [10], [11], [13]. In these works, the generalisation of an {a mathematical formula}EL++ concept is achieved by means of a generalisation refinement operator. This line of work has also been extended to the general debugging problem for ontologies combining ideas from social choice theory and generalisation operators [70]. The refinement operator is implemented in ASP as a step-wise transition process – similar to the one presented in this paper – that looks for a generic space between two (or more) concepts. The operator generalises a concept by taking the TBox knowledge (terminology) into account. Good blends are selected by re-interpreting some optimality principles. Blending ontologies rather than concepts has been explored in the ontological blending framework of Kutz et al. [49], where blends are computed as colimits of blending diagrams specified according to the Distributed Ontology Language (DOL) [59], a recent OMG international ontology interoperability standard. In that framework, the blending process is not characterised in terms of amalgams, nor are input concepts generalised syntactically. Rather, the generic space is assumed to be given and mapped to the input ontologies via theory interpretations.
     </paragraph>
     <paragraph>
      Confalonieri et al. [12] propose a general process model for concept invention that extends the conceptual blending theory of Fauconnier and Turner [27]. Apart from the blending mechanism modelling the creation of new concepts, the authors focus on two extra dimensions that are typically not addressed in computational approaches of concept blending. On the one hand, they describe how a Rich Background supports the discovery of input concepts to be blended. On the other hand, they show how arguments, promoting or demoting the values of an audience, to which the invention is headed, can be used to evaluate candidate blends. Besides, in Schorlemmer et al. [75], the evaluation of new blended concepts is achieved by taking the computational theory of conceptual coherence by Thagard [78] into account. In this setting, newly invented concepts are evaluated with respect to a background ontology of conceptual knowledge so as to decide which of them are to be accepted into a system of familiar concepts. A similar approach has been taken more recently in [14] for determining the joint coherence of {a mathematical formula}ALC concepts w.r.t. a background ontology.
     </paragraph>
     <paragraph>
      The Alloy algorithm [35] for conceptual blending incorporates many ideas of the algebraic semiotics approach by Goguen [34] and the conceptual blending theory by Fauconnier and Turner [27]. Alloy has been integrated in the Griot system for automated narrative generation [35], [39], [38]. Apart from the primary conceptual blending approach realised with Alloy, Griot also uses a secondary structural blending mechanism that blends the dynamic elements of natural language narratives to generate poetry. The input spaces of the Alloy algorithm are theories defined in the algebraic specification language BOBJ (see e.g., [53]). This allows one to represent sorts, operators, constants and axioms. The blending algorithm generates two binary trees that are based on the input graph. The two trees represent (i) the space of possible mappings of relations and (ii) the space of possible mappings of constants respectively. The trees are then combined in the sense that the leaves of the constants-tree are applied to the relations-tree. The resulting combined tree has leaves that represent all possible sort-preserving mappings of relations and constants, i.e., all possible blends. During the tree generation, certain optimality principles are applied to prune the space. The authors do not explicitly account for a cross-space mapping. However, the edges between relations and constants from different theories can be understood as a weak form of a cross-space mapping. Alloy uses these edges (and hence the potential cross-space mapping) to determine a generic space.
     </paragraph>
     <paragraph>
      Sapper was originally developed by Veale and Keane [84] as a computational model of metaphor and analogy. It computes a mapping between two separate domains – understood as graphs of concepts – that respects the relational structure between the concepts in each domain. Strictly speaking, Sapper does not produce blends, but structural mappings between input concepts. It can, however, be seen as a computational model for conceptual blending, because the mappings between the pairs of concepts that constitute its output can be manipulated as atomic units, as blended concepts [83]. Furthermore, Sapper does not work with a priori given input spaces. It is the structure mapping algorithm itself which, given two domains to be mapped, determines the set of concepts and relations between these concepts that constitute the spaces that are blended. It does so by searching within its semantic memory for the largest substructures (bounded by a previously fixed size) at the root concepts of these domains that are isomorphic as with respect to their relational structure, and whose concepts are metaphorically related. Semantic memory is represented as a semantic network [71], a graph whose nodes represent concepts and whose edges represent binary relations between concepts. The actual correspondence or blend between concepts is computed by applying a spreading activation algorithm according to which Sapper locates pairs of paths that are structurally isomorphic (of equal length and constituted by the same sequence of semantic relations) and that terminate at concepts that Sapper considers semantically bridgeable. In Sapper, most of the optimality principles are captured and serve to rank and filter the correspondences that comprise the mappings computed by the algorithm. Veale [82] also proposes a web-based approach to generate more loosely defined blends that he calls conceptual mash-ups. Inconsistencies and evaluation metrics are not addressed in this work; instead, the author focuses on the Internet as a provider for the massive amount of background information that is required to generate meaningful blends.
     </paragraph>
     <paragraph>
      The research in [65], [66], [67] led to the development of Divago [63], [68], [64], probably the first complete implementation of conceptual blending. Pereira draws the terminology and definitions for his formal and computational model from Wiggin's formalisation of creative systems [86]. The implementation of Divago is realised in Prolog. The Divago's architecture includes different modules. A knowledge base contains different micro-theories and their instantiations. Of these, two are selected for the blending by the user or randomly. A mapper then generates the generic space between the inputs, and passes it to a blender module which generates the ‘blendoid’, i.e., a projection that defines the space of possible blends. Blending in Divago is done on a pair of concepts, taken from the multi-domain{sup:8} knowledge base of the system. A factory component is used to select the best blends among the blendoid by means of a genetic algorithm. A dedicated module implements the optimality principles. Given a blend, this module computes a measure for each principle. These measures yield a preference value of the blend that is taken as the fitness value of the genetic algorithm. Recent works [87], [55] describe the use of Divago as a blending component within a computational creativity infrastructure, and discuss the relevance of the optimality principles in the Divago's architecture.
     </paragraph>
     <paragraph>
      Guhe et al. [36] present an approach to use Heuristic-Driven Theory Projection (HDTP) [76] for blending and concept invention. HDTP is originally a framework for analogical reasoning, using a many-sorted first order language to represent conceptual spaces. In HDTP-based analogical reasoning, knowledge is mapped and transferred from a usually well-known source domain S to a target domain T. This happens in two phases. In the mapping phase, source and target are compared to find commonalities. In particular, HDTP uses second-order anti-unification, which is restricted in way that renders the process decidable. In the transfer phase, unmatched knowledge in source is mapped to the target to establish new hypotheses. The blending of two theories happens in three steps. First, core blend laws are applied, second, preferred conjectures are added, and third, extra conjectures are added. The authors do not directly account for the optimality principles by Fauconnier and Turner. However, the preferred and extra conjectures can be seen as alternative optimality principles, similar to the structural optimality principles proposed by Goguen and Harrell [35], that guide the algorithm to select useful blends among the huge space of possible blends.
     </paragraph>
     <paragraph>
      A complementary approach to syntactic-driven approaches, such as HDTP, is to focus on the cognitively inspired notion of image schemas, as mentioned in Sec. 2.1.1. The theory of image schemas was developed within cognitive linguistics, and has been extremely influential since Lakoff &amp; Johnson's work in the late 1980s. In cognitive science, image schemas are identified as fundamental pattern of cognition, that are perceived, conceptualised and manipulated spatially and temporally [54]. Examples of image schemas, proposed in the literature, are containment, support, and source_path_goal. The core idea is that after an image schema has been formed, it can be generalised and the structure can be transferred through analogical reasoning to other domains with similar characteristics [54]. From a formal perspective, previous research on image schemas (e.g., [48], [85], [77]) has provided a valuable portfolio of approaches that can be build on further. The relation of image schemas and conceptual blending – and, particularly, their role in computational concept invention – have been explored in [40], [41], [74]. In this setting, image schemas are conceived as a set of theories ordered by logical entailment that can be used to guide the search for a generic space and as heuristics for the creation of new concepts.
     </paragraph>
     <paragraph>
      The combinatorial kind of creativity [3] that we are interested in has been investigated from a neurological perspective by Thagard and Stewart [80]. The major motivation of their approach is to explain and to model the Aha! or Eureka! effect that occurs when humans make serendipitous discoveries by means of creative thinking. The authors build their work on findings from neuroscience and approaches to realise human thinking with neural networks [79]. The key idea is to represent mental concepts as activity patterns of vectors of neurons and to perform a convolution operation to combine these patterns. Activity patterns of neurons are mathematically represented as vectors of numbers that represent the firing rate of neurons. According to Thagard and Stewart [80], a mental concept can then be represented as a huge but finite vector of such numbers. The blend is generated by mathematical convolution of vectors. The underlying mathematical model is based on the so-called LIF model of neuronal activity (see e.g., [79]). It accounts for various details on the neuronal level, such as neuron voltage, input current, membrane time, direction vector of neuron patterns, and synaptic connection weights. Thagard and Stewart [80] do not use Fauconnier and Turner's optimality principles to distinguish reasonable blends within the huge space of possible blends. Instead, they combine the blend of two input spaces with another space representing emotional reaction to assess blends. However, the authors do not provide a detailed description how to model the emotional input spaces computationally.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Previous work
     </section-title>
     <paragraph>
      This work is based on and extends the publications [20], [21] and the COINVENT project deliverable [4]:
     </paragraph>
     <list>
      <list-item label="•">
       In Eppe et al. [20], published at the International Joint Conference on Artificial Intelligence (IJCAI), we started exploring blending in the music domain and performed first experiments to blend single chords. This paper shows how whole chord progressions are blended.
      </list-item>
      <list-item label="•">
       In Eppe et al. [21], published at the International Conference on Logic Programming and Nonmonotonic Reasoning (LPNMR), we presented a first version of the amalgam-based workflow. The system was extended substantially in the present paper. Besides performance improvements, the evaluation metrics were improved. Furthermore, we now separate the generalisation path in the amalgam-based workflow into a removal path and a commonalisation path, which eliminates duplicate generic spaces.
      </list-item>
      <list-item label="•">
       In Bou et al. [4], we provide the theoretical background to demonstrate in how far an amalgam-based workflow can be seen as blending with colimits using Goguen [34]'s approach. In this paper, we go a step further and implement the theory.
      </list-item>
     </list>
     <paragraph>
      In addition to the above considerations, we extend our previous work by presenting cross-domain blending examples.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>