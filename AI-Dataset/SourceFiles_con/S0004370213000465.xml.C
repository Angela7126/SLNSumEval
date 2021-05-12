<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Qualitative constraint satisfaction problems: An extended framework with landmarks.
   </title>
   <abstract>
    Dealing with spatial and temporal knowledge is an indispensable part of almost all aspects of human activity. The qualitative approach to spatial and temporal reasoning, known as Qualitative Spatial and Temporal Reasoning (QSTR), typically represents spatial/temporal knowledge in terms of qualitative relations (e.g., to the east of, after), and reasons with spatial/temporal knowledge by solving qualitative constraints. When formulating qualitative constraint satisfaction problems (CSPs), it is usually assumed that each variable could be “here, there and everywhere”.1 Practical applications such as urban planning, however, often require a variable to take its value from a certain finite domain, i.e. it is required to be ‘here or there, but not everywhere’. Entities in such a finite domain often act as reference objects and are called “landmarks” in this paper. The paper extends the classical framework of qualitative CSPs by allowing variables to take values from finite domains. The computational complexity of the consistency problem in this extended framework is examined for the five most important qualitative calculi, viz. Point Algebra, Interval Algebra, Cardinal Relation Algebra, RCC5, and RCC8. We show that all these consistency problems remain in NP and provide, under practical assumptions, efficient algorithms for solving basic constraints involving landmarks for all these calculi.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Spatial and temporal information is pervasive and forms an increasing part of our everyday life. Many tasks in the real or virtual world require sophisticated spatial and temporal reasoning abilities. Furthermore, the rapid progress in science and technology in this century continues to present new challenges for spatial and temporal reasoning. Taking spatial information as an example, on one hand, people can now easily acquire location information with the help of GPS-enabled mobile equipment and web GISs such as Google Maps. This has greatly increased the publicʼs demand for location-based services. On the other hand, the development of technologies such as remote sensing, medical imaging, and sensor networks has generated volumes of spatial data, which makes the phenomenon of ‘rich data but poor knowledge’ particularly serious in the area of spatial knowledge management.
     </paragraph>
     <paragraph>
      The qualitative approach to spatial and temporal reasoning, known as Qualitative Spatial and Temporal Reasoning (QSTR), has the potential to resolve the conflict between data and knowledge. This is because the main aims of QSTR research are to design (i) human comprehensible and cognitively plausible spatial relation models (or query languages), and (ii) efficient algorithms for consistency checking (or query preprocessing). For intelligent systems, the ability to understand and process qualitative, vague or even inconsistent (textual, graphical or speech) information collected from human beings or the Web is very important. This is because ‘the input and the output of spatial processes is often qualitative rather than quantitative’ [36].
     </paragraph>
     <paragraph>
      QSTR represents spatial/temporal information in terms of human comprehensible qualitative relations (e.g. partially overlaps, west of, after) and reduces spatial/temporal reasoning to solving constraint satisfaction problems (CSPs). Qualitative relations are widely used in temporal and spatial reasoning (see e.g. [1], [38], [24]). This is partially because they are close to the way humans represent and reason about commonsense knowledge, are easy to specify, and provide a flexible way to deal with incomplete knowledge. Usually, these relations are taken from a qualitative calculus, which is a finite set of relations defined on an infinite universe U of entities [25]. Well-known qualitative calculi include among others Point Algebra (PA) [44], Interval Algebra (IA) [1], Cardinal Relation Algebra (CRA) [24], RCC5, and RCC8 [38], [24].
     </paragraph>
     <paragraph>
      A central reasoning problem of QSTR is the consistency problem. An instance of the consistency problem is a set Γ of constraints like {a mathematical formula}(xαy), where {a mathematical formula}x,y are variables taken from a finite set V, and α is a qualitative relation. Unlike classical CSPs, the domain of a variable appearing in a qualitative constraint is usually infinite, and Hirsch [16] has shown that it may be undecidable for determining consistency for binary CSPs with infinite domains. However, for the five qualitative calculi that we have mentioned above, the consistency problems are all in NP and can be solved by using path-consistency and backtracking (cf. [7], [41]).
     </paragraph>
     <paragraph>
      In the past three decades, QSTR has made significant progress, and prominent qualitative calculi such as IA and RCC8 have been applied in areas such as natural language processing, geographical information systems, robotics, and content-based image retrieval (see e.g. [7]). There is a growing consensus, however, that breakthroughs are necessary to bring spatial/temporal reasoning theory closer to practical applications. One reason might be that the current qualitative reasoning scheme uses a rather restricted constraint language: constraints in a qualitative CSP are always taken from the same calculus and only relate variables from the same infinite domain. This is highly undesirable, as constraints involving restricted variables and/or multiple aspects of information frequently appear in practical tasks such as urban planning and spatial query processing.
     </paragraph>
     <paragraph>
      Consider the following example. Suppose you are recommended a restaurant in Sydney by a friend who has dined there before. The spatial information about the restaurant may be similar to “it is in downtown and close to a MacDonaldʼs, and it is to the west of or southwest of Central Station.” In this example, topological, directional, and distance information appears together. While the position of the restaurant may be completely unknown, the position of Central Station is fixed as a landmark, and the position of downtown is also fixed somehow, but the position of “MacDonaldʼs” is only finitely fixed because there are several branches of MacDonaldʼs in downtown Sydney.
     </paragraph>
     <paragraph>
      While some recent works have considered how to reason with qualitative constraints from different spatial or temporal calculi [13], [20], [28], [45], [21], the importance of solving constraints that involve restricted variables has been totally neglected. Cohn and Renz regarded this as a major future challenge, and commented in their chapter [7, p. 578] in “Handbook of Knowledge Representation” that One problem with this [constraint-based] approach is that spatial entities are treated as variables which have to be instantiated using values of an infinite domain. How to integrate this with settings where some spatial entities are known or can only be from a small domain is still unknown and is one of the main future challenges of constraint-based spatial reasoning.
     </paragraph>
     <paragraph>
      This paper aims to address the above challenge. We say that a variable is finitely restricted if it can only take its value from a finite subset of the universe in a qualitative calculus. We propose to extend the qualitative CSP framework by allowing variables to be finitely restricted. In such a qualitative CSP, the constraints are taken from a fixed qualitative calculus, and the domain of each variable is either the universe of the calculus or a (nonempty) finite subset of the universe. The entities in each finite domain usually act as reference spatial/temporal objects in the constraint network. In this paper, we address these entities as “landmarks”.
     </paragraph>
     <paragraph>
      Landmarks (e.g. Sydney Opera House or Big Ben) are external, outstanding physical objects that act as reference objects. As found in many spatial discourses, landmarks play a fundamental role in cognitive spatial representations, in particular in human navigation and route planning. There are many works in geographical information science that are devoted to characterising or generating landmarks. Lynch [31] is perhaps the first such attempt, which although informal is very influential. Grabler et al. [14] developed a system to generate tourist maps enriched with landmarks. Duckham, Winter, and Robinson [11] considered how to incorporate cognitively salient landmarks in computer-generated navigation instructions. Landmarks are also used as a metaphor in automatic planning, where a landmark acts as an auxiliary sub-goal [15], [42].
     </paragraph>
     <paragraph>
      In this paper, landmarks are used as reference objects for formulating constraints. This is related to but different from Allenʼs ‘reference intervals’ [1], which are used to group clusters of intervals, and the intervals in one cluster are related to intervals outside the cluster only indirectly via the reference intervals.
     </paragraph>
     <paragraph>
      An important research question is, how does this extension affect the computational complexity of deciding the consistency of qualitative CSPs? This paper examines the effect for the five most important qualitative calculi, viz. PA, IA, CRA, RCC5 and RCC8. We show that in the extended framework the consistency problem remains in NP for each calculus. Moreover, we propose practical efficient algorithms for solving basic constraints involving landmarks for these qualitative calculi.
     </paragraph>
     <paragraph>
      The remainder of this paper proceeds as follows. Section 2 introduces basic notions in qualitative constraint solving as well as the five qualitative calculi discussed in this paper. The extended qualitative CSP framework is also presented there. Section 3 discusses the computational complexity of reasoning with the point-based calculi PA, IA, and CRA, and Section 4 considers the same problem for the region-based calculi RCC5 and RCC8. The last section concludes the paper and outlines problems for future study.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this section, we first recall several well-known qualitative calculi and basic notions in qualitative constraint solving, and then introduce the extended qualitative CSP framework.
     </paragraph>
     <section label="2.1">
      <section-title>
       Qualitative calculi
      </section-title>
      <paragraph>
       The qualitative approach to spatial and temporal knowledge representation and reasoning is mainly based on qualitative calculi. In this paper, we only consider binary relations, but the extended qualitative CSP framework can be straightforwardly extended to ternary and any n-ary relations.
      </paragraph>
      <paragraph>
       Suppose U is the universe of spatial or temporal entities. Write {a mathematical formula}Rel(U) for the Boolean algebra of binary relations on U. A qualitative calculus on U is defined as a finite Boolean subalgebra of {a mathematical formula}Rel(U). Let {a mathematical formula}M be a qualitative calculus on U. A relation α in {a mathematical formula}M is a basic relation if it is an atom in {a mathematical formula}M. We write {a mathematical formula}BM for the set of basic relations in {a mathematical formula}M.
      </paragraph>
      <paragraph>
       We next recall the well-known Point Algebra (PA) [44], [43], Cardinal Relation Algebra (CRA) [12], [24], Interval Algebra (IA) [1], and RCC5 and RCC8 [38].
      </paragraph>
      <paragraph label="Definition 1">
       Point Algebra(See [44].) Let U be the set of real numbers. The Point Algebra is the Boolean subalgebra generated by the jointly exhaustive and pairwise disjoint (JEPD) set of relations {a mathematical formula}{&lt;,&gt;,=}, where {a mathematical formula}&lt;,&gt;,=are defined as usual.
      </paragraph>
      <paragraph>
       PA contains eight relations, viz. the three basic relations {a mathematical formula}&lt;,&gt;,=, the empty relation, and the four non-basic nonempty relations {a mathematical formula}⩽,⩾,≠,?, where ? stands for the universal relation.
      </paragraph>
      <paragraph label="Definition 2">
       Cardinal Relation Algebra(See [12], [24].) Let U be the real plane. Define binary relations {a mathematical formula}NW,N,NE,W,EQ,E,SW,S,SE as in Table 1. The Cardinal Relation Algebra (CRA) is generated by these nine JEPD relations. (See Fig. 1.)
      </paragraph>
      <paragraph>
       CRA can be viewed as the Cartesian product of two PAs.
      </paragraph>
      <paragraph label="Definition 3">
       Interval Algebra(See [1].) Let U be the set of closed intervals on the real line. Thirteen binary relations between two intervals {a mathematical formula}x=[x−,x+] and {a mathematical formula}y=[y−,y+] are defined by the order of the four endpoints of x and y, see Table 2. The Interval Algebra (IA) is generated by these JEPD relations.
      </paragraph>
      <paragraph>
       Unlike the above qualitative calculi, the RCC algebras have interpretations in arbitrary topological spaces. Since applications in GIS and many other spatial reasoning tasks mainly consider objects represented in the real plane, in this paper, we only consider interpretations where regions are interpreted as nonempty regular closed sets, and two regions are connected if they somehow intersect.{sup:2}
      </paragraph>
      <paragraph label="Definition 4">
       RCC5 and RCC8 algebrasLet U be the set of nonempty regular closed sets, or regions, in the real plane. The RCC8 algebra is generated by the eight topological relations{a mathematical formula} where {a mathematical formula}DC,EC,PO,TPP and {a mathematical formula}NTPP are defined in Table 3, {a mathematical formula}EQ is the identity relation, and {a mathematical formula}TPPi and {a mathematical formula}NTPPi are the converses of {a mathematical formula}TPP and {a mathematical formula}NTPP respectively. See Fig. 2 for illustration. It is worth mentioning that these eight relations are all definable by the connectedness relation {a mathematical formula}C, which is the complement of {a mathematical formula}DC and two regions are connected if they have nonempty intersection.The RCC5 algebra is the subalgebra of RCC8 generated by the five part-whole relations{a mathematical formula} where {a mathematical formula}DR=DC∪EC, {a mathematical formula}PP=TPP∪NTPP, and {a mathematical formula}PPi=TPPi∪NTPPi.
      </paragraph>
      <paragraph>
       While the RCC algebras defined as above using a ‘weak’ connectedness relation, we will introduce another interpretation in Section 4.4.3 based on a ‘strong’ connectedness relation.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Qualitative constraint satisfaction problem
      </section-title>
      <paragraph>
       A qualitative calculus {a mathematical formula}M provides a constraint language by using formulas of the form {a mathematical formula}(viαvj), where α is a relation in {a mathematical formula}M and {a mathematical formula}vi,vj are variables taking values from the universe of {a mathematical formula}M. Formulas of the form {a mathematical formula}(viαvj) are called constraints (over {a mathematical formula}M). If α is a basic relation in {a mathematical formula}M, {a mathematical formula}(viαvj) is called a basic constraint. The classical consistency problem over {a mathematical formula}M can then be formulated as below.
      </paragraph>
      <paragraph label="Definition 5">
       (See [7].) Let {a mathematical formula}M be a qualitative calculus on universe U. Suppose {a mathematical formula}S is a subset of {a mathematical formula}M. The consistency problem cspsat ({a mathematical formula}S) is defined as follows:
       <list>
        Instance: A 2-tuple {a mathematical formula}(V,Γ). Here V is a finite set of variables {a mathematical formula}{v1,v2,…,vn}, and {a mathematical formula}Γ={viγijvj:1⩽i,j⩽n} is a binary constraint network and each {a mathematical formula}γij is in {a mathematical formula}S.Question: Is there an instantiation {a mathematical formula}ν:V→U such that all the constraints in Γ are satisfied?If
       </list>
       <paragraph>
        ν satisfies all the constraints in Γ, then we say ν is a solution of Γ and say Γ is consistent or satisfiable.
       </paragraph>
      </paragraph>
      <paragraph label="Notation">
       In this paper, we also represent an instantiation {a mathematical formula}ν:V→U as an n-tuple {a mathematical formula}(ν(v1),ν(v2),…,ν(vn)).
      </paragraph>
      <paragraph>
       We note that each instance {a mathematical formula}(V,Γ) in cspsat({a mathematical formula}S) is complete in the sense that the relation {a mathematical formula}γij between any two variables {a mathematical formula}vi,vj is taken from {a mathematical formula}S. Given a binary constraint work {a mathematical formula}Γ={viγijvj:1⩽i,j⩽n}, we say Γ is a basic constraint network if {a mathematical formula}γij is either the universal relation or a basic relation for any two variables {a mathematical formula}vi,vj; and say Γ is a complete basic constraint network if {a mathematical formula}γij is a basic relation for any two variables {a mathematical formula}vi,vj. In other words, each complete basic constraint network is an instance of cspsat({a mathematical formula}BM), while each basic constraint network is an instance of cspsat({a mathematical formula}BM∪{⁎M}), where {a mathematical formula}BM is the set of basic relations in {a mathematical formula}M, and {a mathematical formula}⁎M is the universal relation of {a mathematical formula}M.{sup:3}
      </paragraph>
      <paragraph>
       The consistency problem as defined in Definition 5 has been investigated for many calculi (see e.g. [1], [43], [34], [35], [40], [30], [26]). In particular, the consistency problem cspsat(PA) can be solved in {a mathematical formula}O(n2) time, where n is the number of variables [43]. For most other qualitative calculi, including IA, CRA, RCC5, and RCC8, the consistency problem cspsat({a mathematical formula}M) is NP-complete.
      </paragraph>
      <paragraph>
       When only basic constraint networks are considered, however, the consistency problem over each of these four calculi becomes tractable. In fact, it can be decided by checking whether the network is path-consistent. For binary relations α and β, we write {a mathematical formula}α∼ for the converse of α, and {a mathematical formula}α∘β for the usual composition of α and β. We say a complete basic constraint network {a mathematical formula}Γ={viαijvj:1⩽i,j⩽n} is path-consistent, if for any three variables {a mathematical formula}vi,vj,vk, we have{sup:4}{a mathematical formula}
      </paragraph>
      <paragraph>
       Note that for complete basic constraint networks, path-consistency is equivalent to saying that every subnetwork with three variables is consistent. As a local property, path-consistency can be enforced in cubic time.
      </paragraph>
      <paragraph>
       We summarise the computational complexity results of these calculi in the following theorem.
      </paragraph>
      <paragraph label="Theorem 1">
       (See[34], [35], [24], [40].) The consistency problem{a mathematical formula}cspsat(PA)is in P. Let{a mathematical formula}Mbe one of IA, CRA, RCC5, and RCC8. Then{a mathematical formula}cspsat(BM)is in P and{a mathematical formula}cspsat(M)is NP-complete.
      </paragraph>
      <paragraph label="Theorem 2">
       A complete basic network is globally consistent if any partial solution can be extended to a global solution. The following theorem can be directly proven by exploiting the density of real numbers. Let{a mathematical formula}Mbe one of PA, IA, and CRA. Then a complete basic network is globally consistent if it is path-consistent.
      </paragraph>
      <paragraph>
       We note that RCC5 and RCC8 do not have this property.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Extended qualitative CSP
      </section-title>
      <paragraph>
       By Definition 5, in the classical consistency problem, each variable can in principle take any value in the universe. In many practical applications, however, it is very common to have additional knowledge about some variables (cf. the restaurant and MacDonaldʼs example in the Introduction), which will affect the consistency of qualitative CSPs. It is therefore necessary to extend the qualitative CSP framework to allow restricted domains of variables.
      </paragraph>
      <paragraph label="Definition 6">
       Let {a mathematical formula}M be a qualitative calculus on universe U. Suppose {a mathematical formula}S is a subset of {a mathematical formula}M. The consistency problem {a mathematical formula}cspsatf(S) is defined as follows, where the subscript ‘f’ stands for ‘finite’:
       <list>
        Instance: A 3-tuple {a mathematical formula}(V,Γ,D). Here V is a finite set of variables {a mathematical formula}{v1,v2,…,vn}, D is an n-tuple {a mathematical formula}(D1,D2,…,Dn), where each {a mathematical formula}Di is either U or a nonempty finite subset of U, and {a mathematical formula}Γ={viγijvj:1⩽i,j⩽n} is a binary constraint network and each {a mathematical formula}γij is in {a mathematical formula}S.Question: Is there an instantiation {a mathematical formula}ν:V→U such that {a mathematical formula}ν(vi)∈Di for each i and all the constraints in Γ are satisfied?As a special case, if each finite domain
       </list>
       <paragraph>
        {a mathematical formula}Di is required to be a singleton, we write the corresponding consistency problem {a mathematical formula}cspsats(S), where the subscript ‘s’ denotes ‘singleton’.
       </paragraph>
      </paragraph>
      <paragraph>
       An instance of {a mathematical formula}cspsat(S) is clearly an instance of both {a mathematical formula}cspsats(S) and {a mathematical formula}cspsatf(S): we only need to let each {a mathematical formula}Di be the universe.
      </paragraph>
      <paragraph label="Proposition 1">
       Suppose{a mathematical formula}BMis the set of basic relations in a qualitative calculus{a mathematical formula}M, and{a mathematical formula}Sis a subclass of{a mathematical formula}M. Then we have
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}cspsat(S)⊂cspsats(S)⊂cspsatf(S);
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}cspsatf(M)is in NP if{a mathematical formula}cspsatf(BM)is in NP;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}cspsatf(S)is in NP if{a mathematical formula}cspsats(S)is in NP;
       </list-item>
       <list-item label="(iv)">
        {a mathematical formula}cspsatf(M)is in NP if{a mathematical formula}cspsats(BM)is in NP.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i) follows directly from the definition. As for (ii), suppose we already have a nondeterministic Turing machine {a mathematical formula}T0 which solves {a mathematical formula}cspsatf(BM) in polynomial time. Given a non-basic constraint network {a mathematical formula}(V,Γ,D), it is consistent iff there is a consistent basic constraint network {a mathematical formula}Γ′ that refines Γ in the sense that for each constraint {a mathematical formula}(xαy) in Γ there exists a constraint {a mathematical formula}(xα′y) in {a mathematical formula}Γ′ such that {a mathematical formula}α′⊆α. A basic constraint network that refines Γ is often called a scenario of Γ. We devise a nondeterministic Turing machine T as follows. T first guesses a scenario {a mathematical formula}(V,Γ′,D) of {a mathematical formula}(V,Γ,D), and then calls {a mathematical formula}T0 to decide the consistency of {a mathematical formula}(V,Γ′,D). {a mathematical formula}T′ asserts the instance to be consistent if T returns consistent in any branch. It is clear that the nondeterministic Turing machine T decides the consistency of {a mathematical formula}(V,Γ,D) in polynomial time. Similar argument applies to (iii), and (iv) follows from (ii) and (iii) directly.  □
      </paragraph>
      <paragraph label="Corollary 1">
       By the above proposition, the computational complexity of {a mathematical formula}cspsatf is in general higher than that of {a mathematical formula}cspsats and cspsat, as far as the same subset {a mathematical formula}S of the same calculus is considered. In particular, recall that the classical consistency problems for CRA, IA, RCC5 and RCC8 are all NP-complete. We have the following corollary. The consistency problem{a mathematical formula}cspsats(M)and{a mathematical formula}cspsatf(M)are all NP-hard for{a mathematical formula}Mbeing any one of IA, CRA, RCC5, and RCC8.
      </paragraph>
      <paragraph>
       To determine the computational complexity of reasoning with a qualitative calculus {a mathematical formula}M, we will begin with {a mathematical formula}cspsats(BM).
      </paragraph>
      <paragraph>
       Our computational complexity results are summarised in Table 4, where qualitative calculus {a mathematical formula}M is PA, IA, CRA, RCC5 or RCC8, and {a mathematical formula}S is either {a mathematical formula}BM or {a mathematical formula}M itself (i.e., we consider either complete basic networks or the most general case).
      </paragraph>
      <paragraph>
       In the following sections, we first consider point-based calculi PA, CRA, and IA, and then consider region-based calculi RCC5 and RCC8. Unlike point-based calculi, the geometrical representation (in particular, shape and location) of the landmarks may affect the existence of solutions in the plane. To make the analysis more meaningful, we assume that all the landmarks in RCC5 and RCC8 constraint networks are represented as polygons which may have different connected components and holes. This assumption is practical because polygons are the most widely used approximations of regions in spatial databases.
      </paragraph>
      <paragraph>
       The NP-hardness results in Table 4 obtained in this paper are mainly achieved by designing polynomial reductions from the Graph 3-Colouring problem, which is a well-known NP-complete problem. Recall that a graph {a mathematical formula}G=(V,E) is 3-colourable if there is a function {a mathematical formula}f:V→{0,1,2} such that {a mathematical formula}f(v)≠f(v′) for each edge {a mathematical formula}(v,v′)∈E. The Graph 3-Colouring problem is to decide whether a graph is 3-colourable.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Point-based qualitative calculi
     </section-title>
     <paragraph>
      This section discusses the consistency problems in the extended framework for the three point-based qualitative calculi, viz. Point Algebra, Interval Algebra, and Cardinal Relation Algebra.
     </paragraph>
     <section label="3.1">
      <section-title>
       Some simple results
      </section-title>
      <paragraph>
       To prove the computational complexity results, we will need the following notion of a finitely restricted sub-instance.
      </paragraph>
      <paragraph label="Definition 7">
       Let {a mathematical formula}M be a qualitative calculus with universe U, and let {a mathematical formula}S be a subclass of {a mathematical formula}M. Suppose {a mathematical formula}(V,Γ,D) is an instance of {a mathematical formula}cspsatf(S), where {a mathematical formula}V={v1,…,vn}, {a mathematical formula}D=(D1,…,Dn) and {a mathematical formula}Γ={viαijvj}1⩽i,j⩽n. Let {a mathematical formula}V′={vi:Di≠U} be the set of finitely restricted variables in V. Suppose {a mathematical formula}V′={vi1,vi2,…,vik}. Let {a mathematical formula}Γ′={virαirisvis}1⩽r,s⩽k and {a mathematical formula}D′=(Di1,Di2,…,Dik). We call {a mathematical formula}(V′,Γ′,D′), which is also an instance of {a mathematical formula}cspsatf(S), the finitely restricted sub-instance of {a mathematical formula}(V,Γ,D).
      </paragraph>
      <paragraph>
       For complete basic constraint networks, we have the following general result.
      </paragraph>
      <paragraph label="Lemma 1">
       Let{a mathematical formula}Mbe one of PA, IA, and CRA. Suppose{a mathematical formula}(V,Γ,D)is an instance of{a mathematical formula}cspsatf(BM). Then{a mathematical formula}(V,Γ,D)is consistent iff Γ is path-consistent and the finitely restricted sub-instance of{a mathematical formula}(V,Γ,D)is consistent.
      </paragraph>
      <paragraph label="Proof">
       The cases for IA and CRA can be proven in the same way.  □
      </paragraph>
      <paragraph>
       Using Lemma 1, we are able to show the following computational complexity results.
      </paragraph>
      <paragraph label="Theorem 3">
       For PA, we have{a mathematical formula}cspsats(BPA)and{a mathematical formula}cspsats(PA)are in P and{a mathematical formula}cspsatf(PA)is in NP. Let{a mathematical formula}Mbe IA or CRA. Then{a mathematical formula}cspsats(BM)is in P, and{a mathematical formula}cspsats(M)and{a mathematical formula}cspsatf(M)are NP-complete.
      </paragraph>
      <paragraph label="Proof">
       For PA, we recall that {a mathematical formula}cspsat(PA) can be solved in {a mathematical formula}O(n2) time [43]. Suppose {a mathematical formula}(V,Γ,D) is an instance of {a mathematical formula}cspsats(PA). We show that the consistency of {a mathematical formula}(V,Γ,D) can be determined in polynomial time. For a pair of variables {a mathematical formula}vi and {a mathematical formula}vj such that {a mathematical formula}Di={di} and {a mathematical formula}Dj={dj} are both singletons, suppose {a mathematical formula}(viαvj) is in Γ, and β is the basic PA relation between {a mathematical formula}di and {a mathematical formula}dj. It is clear that {a mathematical formula}(V,Γ,D) is inconsistent if β is not included in α. Without loss of generality, we assume α is a basic relation and {a mathematical formula}α=β. Under this assumption, we show that {a mathematical formula}(V,Γ,D) is consistent iff the {a mathematical formula}cspsat(PA) instance {a mathematical formula}(V,Γ′) is consistent. The necessity is clear. For the sufficiency, suppose {a mathematical formula}(V,Γ) is consistent and has a consistent scenario {a mathematical formula}(V,Γ0). Note that the finitely restricted sub-instance of {a mathematical formula}(V,Γ0,D) is consistent, as the constraint between any two variables with a singleton domain is the actual relation between the corresponding landmarks. By Lemma 1, we have {a mathematical formula}(V,Γ,D) is consistent. Because the consistency of {a mathematical formula}(V,Γ) can be decided in polynomial time [43], we know that {a mathematical formula}cspsats(PA) is in P and consequently {a mathematical formula}cspsats(BPA) is in P and {a mathematical formula}cspsatf(PA) is in NP.{sup:5}For {a mathematical formula}M being IA or CRA, suppose {a mathematical formula}(V,Γ,D) is an instance of {a mathematical formula}cspsats(BM), and {a mathematical formula}(V′,Γ′,D′) is its finitely restricted sub-instance. Assume that V has n variables and {a mathematical formula}V′ has {a mathematical formula}m⩽n variables. The path-consistency of Γ can be checked in {a mathematical formula}O(n3) time. Moreover, the consistency of {a mathematical formula}(V′,Γ′,D′) can be decided in {a mathematical formula}O(m2) time, as we only need to check for each pair of variables {a mathematical formula}vi and {a mathematical formula}vj in {a mathematical formula}V′ whether the unique landmarks specified for them satisfy the constraint between them. By Lemma 1, the consistency of {a mathematical formula}(V,Γ,D) can be determined in {a mathematical formula}O(n3) time. Therefore, {a mathematical formula}cspsats(BM) is in P. By Proposition 1, we know {a mathematical formula}cspsats(M) and {a mathematical formula}cspsatf(M) are all in NP. Meanwhile, the NP-completeness of {a mathematical formula}cspsat(M) implies that {a mathematical formula}cspsats(M) and {a mathematical formula}cspsatf(M) are all NP-complete.  □
      </paragraph>
      <paragraph>
       The following subsections will respectively show that (i) {a mathematical formula}cspsatf(BPA) is in P but {a mathematical formula}cspsatf(PA) is NP-complete, and (ii) {a mathematical formula}cspsatf(BM) is NP-complete for {a mathematical formula}M being IA or CRA.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Point Algebra
      </section-title>
      <paragraph>
       We first propose a polynomial algorithm that solves {a mathematical formula}cspsatf(BPA) and then provide a polynomial reduction from Graph 3-Colouring to {a mathematical formula}cspsatf(PA).
      </paragraph>
      <paragraph>
       Let {a mathematical formula}(V,Γ,D) be an instance of {a mathematical formula}cspsatf(BPA). By Lemma 1 we know that {a mathematical formula}(V,Γ,D) is consistent iff Γ is path-consistent and the finitely restricted sub-instance {a mathematical formula}(V′,Γ′,D′) of {a mathematical formula}(V,Γ,D) is consistent. Because path-consistency can be determined in cubic time, we only need to devise a polynomial algorithm for checking whether {a mathematical formula}(V′,Γ′,D′) is consistent. To this end, we show that such a consistent instance of {a mathematical formula}cspsatf(BPA) has a minimal solution in a sense.
      </paragraph>
      <paragraph label="Proposition 2">
       Suppose{a mathematical formula}(V,Γ,D)is an instance of{a mathematical formula}cspsatf(BPA)such that{a mathematical formula}D={D1,D2,…,Dn}and each{a mathematical formula}Diis a finite set of real numbers. If{a mathematical formula}(V,Γ,D)is consistent, then there is a unique solution{a mathematical formula}(a1,…,an)such that{a mathematical formula}ai⩽ai′{a mathematical formula}(1⩽i⩽n)for any other solution{a mathematical formula}(a1′,a2′,…,an′). Furthermore, if{a mathematical formula}Γ={vi&lt;vj}1⩽i&lt;j⩽n, then
      </paragraph>
      <list>
       <list-item label="–">
        {a mathematical formula}a1=minD1;
       </list-item>
       <list-item label="–">
        {a mathematical formula}ak=min{x∈Dk:x&gt;ak−1}for{a mathematical formula}k=2,3,…,n.
       </list-item>
      </list>
      <paragraph label="Proof">
       Assume {a mathematical formula}Γ={vi&lt;vj}1⩽i&lt;j⩽n. This does not lose generality because we can combine variables related by the ‘=’ constraint and then sort the variables by the ‘&lt;’ and ‘&gt;’ constraints. Every {a mathematical formula}Di is a finite set, so {a mathematical formula}(V,Γ,D) has at most finitely many, say k, solutions. Suppose {a mathematical formula}(a1i,a2i,…,ani)(i=1,2,…,k) enumerate all solutions. Let {a mathematical formula}aj=min{aji}1⩽i⩽k. We claim that {a mathematical formula}(a1,a2,…,an) is the minimal solution. We only need to prove that it is a solution of {a mathematical formula}(V,Γ,D), i.e. to show (i) each {a mathematical formula}aj is in {a mathematical formula}Dj; and (ii) {a mathematical formula}a1&lt;a2&lt;⋯&lt;an. Because {a mathematical formula}aji∈Dj, we know {a mathematical formula}aj=min{aji}1⩽i⩽k is in {a mathematical formula}Dj. We next prove {a mathematical formula}a1&lt;a2. Suppose {a mathematical formula}a2=a2j for some j by definition. Then {a mathematical formula}a1=min{a1i}1⩽i⩽k⩽a1j&lt;a2j=a2. By using induction, we can also prove {a mathematical formula}a2&lt;a3&lt;⋯&lt;an. Therefore, {a mathematical formula}(a1,a2,…,an) is the minimal solution of {a mathematical formula}(V,Γ,D).  □
      </paragraph>
      <paragraph>
       We next propose a polynomial algorithm that solves {a mathematical formula}cspsatf(BPA) based on Proposition 2. For any instance {a mathematical formula}(V,Γ,D) of {a mathematical formula}cspsatf(BPA), we first check whether Γ is consistent. If it is inconsistent, then so is {a mathematical formula}(V,Γ,D). Otherwise, we check whether the finitely restricted sub-instance {a mathematical formula}(V′,Γ′,D′) of {a mathematical formula}(V,Γ,D) is consistent. To this end, we attempt to compute the minimal solution {a mathematical formula}(a1,…,an) by procedures described in Proposition 2. If in the k-th step {a mathematical formula}{x∈Dk:x&gt;ak−1} is empty, then we conclude that the sub-instance, and thus the original instance, is inconsistent. If we succeed in computing {a mathematical formula}(a1,a2,…,an), then it is a solution of the sub-instance and can be extended to a solution of the original instance. The soundness of the algorithm is clear by the above argument.
      </paragraph>
      <paragraph label="Theorem 4">
       Algorithm 1solves{a mathematical formula}cspsatf(BPA).
      </paragraph>
      <paragraph label="Proposition 3">
       We next analyse the computational complexity of the algorithm. Suppose there are n variables in V, and the sum of the cardinalities of all finite {a mathematical formula}Di is L. Then the input size is {a mathematical formula}O(n2+L) ({a mathematical formula}n2 constraints and L points). The following proposition shows the optimality of the algorithm. The computational complexity ofAlgorithm 1is{a mathematical formula}O(n2+L).
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}(V,Γ,D) be an instance of {a mathematical formula}cspsatf(BPA). The consistency of Γ can be computed in {a mathematical formula}O(n2) time by Algorithm cspan proposed in [43]. Sorting {a mathematical formula}V′ takes {a mathematical formula}O(nlogn) time. Let {a mathematical formula}li be the cardinality of {a mathematical formula}Di′. Then step ‘{a mathematical formula}a1←minD1′’ takes {a mathematical formula}O(l1) time, and the i-th loop body takes {a mathematical formula}O(li+1) time ({a mathematical formula}i=1,2,…,n′−1). Therefore, the computational complexity of the algorithm is {a mathematical formula}O(n2+nlogn+l1+l2+⋯+ln′)=O(n2+L).  □
      </paragraph>
      <paragraph>
       Despite the fact that both {a mathematical formula}cspsat(PA) and {a mathematical formula}cspsatf(BPA) are in P, the next theorem shows that {a mathematical formula}cspsatf(PA) is NP-hard. We prove this by using a polynomial reduction from the Graph 3-Colouring problem to {a mathematical formula}cspsatf(PA).
      </paragraph>
      <paragraph label="Proof">
       The consistency problem{a mathematical formula}cspsatf(PA)is NP-complete.Let {a mathematical formula}G=(V,E) be a graph, where {a mathematical formula}V={v0,…,vn}. Define a {a mathematical formula}cspsatf(PA) instance {a mathematical formula}(UG,ΓG,DG) as follows{sup:6}:{a mathematical formula}{a mathematical formula}{a mathematical formula} That is, we construct for each vertex {a mathematical formula}vi∈V a corresponding temporal variable {a mathematical formula}ui which takes value from {a mathematical formula}{0,1,2}; and we specify for each edge {a mathematical formula}(vi,vi′)∈E a constraint {a mathematical formula}(ui≠ui′). It is clear that {a mathematical formula}G=(V,E) can be 3-colourable iff {a mathematical formula}(UG,ΓG,DG) is satisfiable. Therefore the consistency problem {a mathematical formula}cspsatf(PA) is NP-hard, and hence NP-complete as its NP-membership has been identified in Theorem 3.  □
      </paragraph>
      <paragraph label="Remark 1">
       The NP-hardness of {a mathematical formula}cspsatf(PA) is due to the uncertainty of the non-equal (≠) constraints and the finiteness of the domains. It can be proven that {a mathematical formula}cspsatf(S) is in P for {a mathematical formula}S={&lt;,=,&gt;,⩽,⩾,?} (i.e., with ≠ removed from PA). A polynomial algorithm can be devised based on the observation that the concept of a minimal solution still applies. The algorithm first merges the variables which are required to be equal by the constraints (see [43]). Note the domains of the merged variables should also be revised as the intersection of their original domains. The algorithm then adopts a topological sort, during which each finitely restricted variable is assigned a value in its domain as small as possible.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Cardinal Relation Algebra
      </section-title>
      <paragraph>
       To show that {a mathematical formula}cspsatf(BCRA) is NP-hard, we design a polynomial reduction from Graph 3-Colouring to {a mathematical formula}cspsatf(BCRA). Suppose {a mathematical formula}G=(V,E) is a graph with vertex set {a mathematical formula}V={v0,…,vn}. We construct an instance {a mathematical formula}(UG,ΓG,DG) of {a mathematical formula}cspsatf(BCRA) such that {a mathematical formula}(UG,ΓG,DG) is satisfiable iff G is 3-colourable.{sup:7}
      </paragraph>
      <paragraph>
       First, for each vertex {a mathematical formula}vi∈V, we introduce a spatial variable {a mathematical formula}ui with domain{a mathematical formula} We say {a mathematical formula}ui is at position p (where {a mathematical formula}p∈{0,1,2}), if it takes the point {a mathematical formula}(3i+p,3i+p) in {a mathematical formula}Dui. Second, for each edge {a mathematical formula}ej=(vi,vi′)∈E (assuming {a mathematical formula}i&lt;i′), we introduce a spatial variable {a mathematical formula}wj with domain{a mathematical formula} and add two constraints {a mathematical formula}(wjEui) and {a mathematical formula}(wjSui′) to {a mathematical formula}ΓG. That is to say, {a mathematical formula}wj should be to the east of {a mathematical formula}ui and to the south of {a mathematical formula}ui′. The domain of {a mathematical formula}wj is used to rule out the cases when {a mathematical formula}ui and {a mathematical formula}ui′ are at the same position (with respect to their own domains), which correspond to the requirement that vertices {a mathematical formula}vi and {a mathematical formula}vi′ cannot be coloured the same as they are connected by edge {a mathematical formula}ej.
      </paragraph>
      <paragraph>
       Note that each {a mathematical formula}cspsatf(BCRA) instance is a complete network. This means that we should specify for each pair of variables in {a mathematical formula}UG a basic CRA constraint. In above we have specified such a constraint for two spatial variables {a mathematical formula}ui and {a mathematical formula}wj when {a mathematical formula}vi is a vertex incident to edge {a mathematical formula}ej in G. There are three other cases unspecified:
      </paragraph>
      <list>
       <list-item label="•">
        The constraint between {a mathematical formula}ui and {a mathematical formula}ui′;
       </list-item>
       <list-item label="•">
        The constraint between {a mathematical formula}ui and {a mathematical formula}wj, where {a mathematical formula}vi is not incident to edge {a mathematical formula}ej in G;
       </list-item>
       <list-item label="•">
        The constraint between {a mathematical formula}wj and {a mathematical formula}wj′.
       </list-item>
      </list>
      <paragraph>
       In each case it is straightforward to specify a basic constraint between the two spatial variables.
      </paragraph>
      <paragraph label="Example 1">
       Suppose {a mathematical formula}G=(V,E) is a graph, where {a mathematical formula}V={v0,v1,v2} and {a mathematical formula}E={(v0,v1),(v1,v2)}. Let {a mathematical formula}(UG,ΓG,DG) be the {a mathematical formula}cspsatf(BCRA) instance constructed as above for G. Then {a mathematical formula}UG={u0,u1,u2,w0,w1}, with their domains shown in Fig. 3. The constraints in {a mathematical formula}ΓG are given in Table 5, where constraints in bold are those corresponding to edges in E.
      </paragraph>
      <paragraph label="Proof">
       Straightforward.  □
      </paragraph>
      <paragraph label="Theorem 6">
       As a consequence, we have: The problem{a mathematical formula}cspsatf(BCRA)is NP-complete.
      </paragraph>
      <paragraph label="Proof">
       Since the reduction above is polynomial, we know that {a mathematical formula}cspsatf(BCRA) is NP-hard. Meanwhile, the NP-membership of {a mathematical formula}cspsatf(BCRA) follows from Theorem 3. Therefore, {a mathematical formula}cspsatf(BCRA) is an NP-complete problem.  □
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Interval Algebra
      </section-title>
      <paragraph>
       To show that {a mathematical formula}cspsatf(BIA) is NP-hard, we design a polynomial reduction from {a mathematical formula}cspsatf(BCRA). Note that an interval {a mathematical formula}[x,y] corresponds to the point {a mathematical formula}(x,y) on the half-plane {a mathematical formula}{(x,y):x&lt;y}. Suppose {a mathematical formula}(V,Γ,D) is a {a mathematical formula}cspsatf(BCRA) instance, where {a mathematical formula}V={u1,…,un}, {a mathematical formula}Γ={uiαijuj:1⩽i,j⩽n}, {a mathematical formula}D=(D1,…,Dn). Note that {a mathematical formula}Di is either the universe of CRA {a mathematical formula}UCRA (viz. the real plane), or a finite subset of {a mathematical formula}UCRA. We now translate {a mathematical formula}(V,Γ,D) into a {a mathematical formula}cspsatf(BIA) instance {a mathematical formula}(V′,Γ′,D′), where {a mathematical formula}Γ′ is a complete basic IA network. The translation maps
      </paragraph>
      <list>
       <list-item label="–">
        each variable {a mathematical formula}ui in V to variable {a mathematical formula}ui′ in {a mathematical formula}V′;
       </list-item>
       <list-item label="–">
        each basic CRA relation {a mathematical formula}αij to a basic IA relation {a mathematical formula}βij as specified in Table 6;
       </list-item>
       <list-item label="–">
        each {a mathematical formula}Di to {a mathematical formula}Di′, such that if {a mathematical formula}Di=UCRA then {a mathematical formula}Di′ is the universe of IA {a mathematical formula}UIA; if {a mathematical formula}Di is finite, then {a mathematical formula}Di′={[x,y+Δ]:(x,y)∈Di}. Here Δ is a fixed large number such that {a mathematical formula}x&lt;y+Δ for any point {a mathematical formula}(x,y) in any restricted domain {a mathematical formula}Di.
       </list-item>
      </list>
      <paragraph label="Proof">
       We show that the translation preserves consistency. An instance{a mathematical formula}(V,Γ,D)in{a mathematical formula}cspsatf(BCRA)is consistent iff the corresponding instance{a mathematical formula}(V′,Γ′,D′)in{a mathematical formula}cspsatf(BIA)as constructed above is consistent.Suppose {a mathematical formula}(a1,…,an) is a solution of {a mathematical formula}(V,Γ,D), where {a mathematical formula}ai=(xi,yi)∈Di. Define interval {a mathematical formula}ai′=[xi,yi+Δ]∈Di′. We prove that {a mathematical formula}(a1′,…,ai′) is a solution of {a mathematical formula}(V′,Γ′,D′). It is clear that {a mathematical formula}ai′∈Di′ by the translation from {a mathematical formula}Di to {a mathematical formula}Di′. We only need to verify that all the constraints in {a mathematical formula}Γ′ are satisfied by {a mathematical formula}(a1′,…,ai′). This can be done by discussing each of the nine kinds of basic IA constraints in {a mathematical formula}Γ′.Suppose {a mathematical formula}(ui′diuj′) is a constraint in {a mathematical formula}Γ′. We need to prove {a mathematical formula}[xi,yi+Δ]di[xj,yj+Δ], i.e., {a mathematical formula}xi&lt;xj&lt;yj+Δ&lt;yi+Δ. By the translation we know that {a mathematical formula}(uiNWuj) is in Γ. Therefore {a mathematical formula}(xi,yi)NW(xj,yj), i.e., {a mathematical formula}xi&lt;xj and {a mathematical formula}yi&gt;yj. Meanwhile {a mathematical formula}xj&lt;yj+Δ is guaranteed by the selection of Δ, so the constraint {a mathematical formula}(ui′diuj′) is satisfied by {a mathematical formula}(a1′,…,an′). The remaining eight cases can be proven analogously.  □
      </paragraph>
      <paragraph label="Proof">
       Therefore we obtain the following result. The consistency problem{a mathematical formula}cspsatf(BIA)is NP-complete.Since the reduction from {a mathematical formula}cspsatf(BCRA) to {a mathematical formula}cspsatf(BIA) is polynomial, we know that {a mathematical formula}cspsatf(BIA) is NP-hard. Moreover, by Theorem 3, we have {a mathematical formula}cspsatf(BIA) is in NP. This shows that {a mathematical formula}cspsatf(BIA) is NP-complete.  □
      </paragraph>
      <paragraph>
       So far, we have completed the discussion for the three point-based qualitative calculi. The next section will address region-based qualitative calculi.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Region-based qualitative calculi RCC5 and RCC8
     </section-title>
     <paragraph>
      This section discusses the consistency problems over RCC5 and RCC8 in the extended qualitative CSP framework. Note that although the universe of RCC5 (or RCC8) is the set of all regions in the plane, it is reasonable to assume that all landmarks are represented as polygons. This is because landmarks, as inputs of instances, are required to be representable in computers. In other words, they should be finitely representable. Meanwhile, general polygons (which may have holes or multiple components) are the most widely used approximations of regions: they are simple, intuitive, and expressive.{sup:8}
     </paragraph>
     <paragraph>
      Under the assumption that all landmarks are represented by general polygons, we show in this section that all these consistency problems are in NP. In particular, we show that {a mathematical formula}cspsats(BRCC5) is in P, but that {a mathematical formula}cspsatf(BRCC5) and {a mathematical formula}cspsats(BRCC8) are all NP-complete. It is not surprising that {a mathematical formula}cspsatf(BRCC5) is NP-complete if we regard the finitely restricted sub-instance of each instance of {a mathematical formula}cspsatf(BRCC5) as a classical CSP, but the NP-hardness of {a mathematical formula}cspsats(BRCC8) is quite undesirable. One way to circumvent this obstacle is to use a stronger connectedness instead of the one used in Definition 4.
     </paragraph>
     <paragraph>
      The remainder of this section is organised as follows. We first introduce a simple computational complexity result in Section 4.1 showing that {a mathematical formula}cspsatf(BRCC5) is NP-hard. Several of our results are related to computing the intersection of landmarks (represented as polygons), so we analyse its computational complexity in Section 4.2. The tractability of {a mathematical formula}cspsats(BRCC5) is then proven in Section 4.3. Section 4.4 shows that {a mathematical formula}cspsats(BRCC8) is NP-complete if the RCC8 relations are interpreted as in Definition 4, and proves that the same problem is in P (i.e. tractable) if we adopt another interpretation that uses a stronger connectedness.
     </paragraph>
     <section label="4.1">
      The NP-hardness of {a mathematical formula}cspsatf(BRCC5)
      <paragraph>
       We prove the NP-hardness of {a mathematical formula}cspsatf(BRCC5) by designing a polynomial reduction from the Graph 3-Colouring problem.
      </paragraph>
      <paragraph label="Proposition 6">
       The consistency problem{a mathematical formula}cspsatf(BRCC5)is NP-hard.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}G=(V,E) be a graph, where {a mathematical formula}V={v0,…,vn} and {a mathematical formula}E={e0,…,em}. For each vertex {a mathematical formula}v∈V, we introduce three regions (represented by rectangles) {a mathematical formula}rv0,rv1 and {a mathematical formula}rv2; for each edge {a mathematical formula}e∈E, we introduce three regions (represented by rectangles) {a mathematical formula}se0,se1 and {a mathematical formula}se2. These rectangles are required to be pairwise disjoint.For any {a mathematical formula}1⩽i⩽n and {a mathematical formula}0⩽p⩽2, we define a landmark {a mathematical formula}lip as{a mathematical formula}Because rectangles {a mathematical formula}rvp,sep are pairwise disjoint for {a mathematical formula}v∈V,e∈E and {a mathematical formula}p∈{0,1,2}, it is clear that {a mathematical formula}lip∩ljq=∅ if {a mathematical formula}p≠q. For {a mathematical formula}i≠j and {a mathematical formula}p=q, it is also straightforward to see that {a mathematical formula}lip∩ljq=sep is a rectangle if {a mathematical formula}e=(vi,vj)∈E and {a mathematical formula}lip∩ljq=∅ otherwise.The {a mathematical formula}cspsats(BRCC5) instance {a mathematical formula}(VG,ΓG,DG) is constructed as follows.{a mathematical formula}{a mathematical formula}{a mathematical formula} Note that spatial variable {a mathematical formula}ui corresponds to vertex {a mathematical formula}vi, and “vertex {a mathematical formula}vi is coloured with colour p” corresponds to that “variable {a mathematical formula}ui takes value {a mathematical formula}lip”. It is routine to show that G is 3-colourable iff {a mathematical formula}(VG,ΓG,DG) is consistent. Because the reduction is polynomial, we know the consistency problem {a mathematical formula}cspsatf(BRCC5) is NP-hard.  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Planar subdivision and overlay computation
      </section-title>
      <paragraph>
       In the following subsections we will see that computing the intersection of landmarks (represented as polygons) is critically important when solving the consistency problems for RCC5 and RCC8 in the extended qualitative CSP framework. To facilitate the discussion, this subsection analyses the computational complexity of computing the intersection of multiple polygons. Our discussion is based on the doubly-connected edge list (DCEL) structure for representing planar subdivisions (cf. e.g. [9]).
      </paragraph>
      <paragraph>
       A planar subdivision is an embedding of a planar graph in the plane such that its edges are mapped into straight line segments. It consists of vertices, edges, and faces. Vertices are endpoints of line segments, edges are interiors of line segments, and faces are maximally connected subsets of the plane with all edges and vertices removed. In particular, each face is a connected open set, which may have holes. The outer face is unbounded, but every other face is bounded and its boundary consists of vertices and edges. The complexity of a planar subdivision is defined as the sum of the number of its vertices, the number of its edges, and the number of its faces. For example, the planar subdivision of the rectangle in Fig. 4(a) has two faces (Fig. 4(a)), four vertices (Fig. 4(b)) and four edges (Fig. 4(c)), and thus has a complexity of ten.{sup:9}
      </paragraph>
      <paragraph>
       In what follows, we write {a mathematical formula}Face, {a mathematical formula}Edge, and {a mathematical formula}Vtx respectively for the set of faces, the set of edges, and the set of vertices in a planar subdivision, and use lower Fraktur symbols {a mathematical formula}f,e,v (possibly with indices) to denote, respectively, faces, edges, and vertices in the subdivision.
      </paragraph>
      <paragraph label="Proof">
       The following lemma shows that the complexity of a planar subdivision is of the same order as the number of its vertices. Let S be a planar subdivision with k vertices. Then the complexity of S is{a mathematical formula}O(k).Recall that each planar subdivision is an embedding of a planar graph in the plane. By Eulerʼs formula (cf. [10]), if S has C connected components then{a mathematical formula} Furthermore, since each face is bounded by at least three edges, and each edge touches at most two faces, it is straightforward to prove that{a mathematical formula} Therefore the complexity of S is {a mathematical formula}O(k).  □
      </paragraph>
      <paragraph>
       In Computational Geometry, a planar subdivision is usually represented by the doubly-connected edge list (DCEL), where each edge is considered as two directed half-edges with opposite directions. The DCEL of a subdivision maintains a table for each vertex, each half-edge, and each face. The table allows the retrieve from an object (viz. vertex, half-edge, or faced) to its incident (or adjacent) objects efficiently. For a planar subdivision {a mathematical formula}S with complexity k, the DCEL of {a mathematical formula}S takes {a mathematical formula}O(k) space.
      </paragraph>
      <paragraph>
       The overlay of two planar subdivisions {a mathematical formula}S1 and {a mathematical formula}S2 is the planar subdivision S induced by all edges from {a mathematical formula}S1 and {a mathematical formula}S2. Each vertex of S is either a vertex of {a mathematical formula}S1 or {a mathematical formula}S2, or the intersection point of two edges from {a mathematical formula}S1 and {a mathematical formula}S2. Each edge is either an edge of {a mathematical formula}S1 or {a mathematical formula}S2, or a part of an edge of {a mathematical formula}S1 cut by an edge of {a mathematical formula}S2, or vice versa. Similarly, each face of S is either a face of {a mathematical formula}S1 or {a mathematical formula}S2, or the intersection of two faces from {a mathematical formula}S1 and {a mathematical formula}S2. Figs. 4(e) and 4(f) illustrate the overlay of the rectangle in Fig. 4(a) and the triangle in Fig. 4(d), which has four faces, eleven edges and nine vertices, and hence has a complexity of 24.
      </paragraph>
      <paragraph>
       We have the following result about the complexity of the overlay.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}S1and{a mathematical formula}S2be two planar subdivisions of complexity{a mathematical formula}k1and{a mathematical formula}k2respectively. Then the overlay of{a mathematical formula}S1and{a mathematical formula}S2has complexity{a mathematical formula}O(k1k2).Note that each vertex in the overlay is either a vertex of {a mathematical formula}S1, or a vertex of {a mathematical formula}S2, or the intersection point of two edges from different subdivisions. As the numbers of vertices and edges of {a mathematical formula}Si are less than {a mathematical formula}ki, the overlay has {a mathematical formula}O(k1k2) vertices. The complexity of the overlay then follows from Lemma 2.  □
      </paragraph>
      <paragraph>
       The computational complexity of the overlay computation is as follows.
      </paragraph>
      <paragraph label="Proposition 7">
       (See[9, Theorem 2.6].) Let{a mathematical formula}S1and{a mathematical formula}S2be two planar subdivisions of complexity{a mathematical formula}k1and{a mathematical formula}k2respectively. Then the overlay of{a mathematical formula}S1and{a mathematical formula}S2can be constructed in{a mathematical formula}O((k1+k2+k)log(k1+k2))time, where k is the complexity of the overlay.
      </paragraph>
      <paragraph>
       Proposition 7 only considers the overlay of two subdivisions. For the consistency problems {a mathematical formula}cspsats(BRCC5) and {a mathematical formula}cspsats(BRCC8), we need to compute the overlay {a mathematical formula}O of the subdivisions induced by landmarks {a mathematical formula}l1,…,lm ({a mathematical formula}m⩾3). At first glance, the computational complexity seems to be very high. Suppose each landmark is represented by a polygon with k vertices. If we use Lemma 2 successively then the overlay will have complexity {a mathematical formula}O(km). As a consequence, the computational complexity of computing the overlay will be exponential if we use Proposition 7 successively. The following result shows that, however, {a mathematical formula}O can be computed in polynomial time. The key idea is that the complexity of the overlay of the m subdivisions is, instead of {a mathematical formula}O(km), polynomial in m and k (if we assume each landmark has k vertices).
      </paragraph>
      <paragraph label="Lemma 4">
       Suppose{a mathematical formula}liis a polygon with{a mathematical formula}kivertices for each{a mathematical formula}1⩽i⩽m. Let{a mathematical formula}K=∑i=1mkiand{a mathematical formula}Obe the overlay of the subdivisions induced by these polygons. Then{a mathematical formula}Ohas complexity{a mathematical formula}O(K2)and can be computed in{a mathematical formula}O(mK2logK)time.
      </paragraph>
      <paragraph label="Proof">
       It is clear that there are in total {a mathematical formula}O(K) vertices and, by Lemma 2, {a mathematical formula}O(K) edges in the subdivisions induced by these polygons. As each vertex in the overlay {a mathematical formula}O is either a vertex of a subdivision, or the intersection point of two edges from different subdivisions, we know that {a mathematical formula}O has {a mathematical formula}O(K2) vertices. By Lemma 2, the complexity of {a mathematical formula}O is also {a mathematical formula}O(K2).Write {a mathematical formula}Oi for the overlay of the subdivisions induced by the first i polygons {a mathematical formula}l1,…,li. The complexity of each {a mathematical formula}Oi is no more than that of {a mathematical formula}O=Om. By Proposition 7 we know {a mathematical formula}Oi+1 can be computed in {a mathematical formula}O((K2+K+K2)log(K2+K))=O(K2logK) time from {a mathematical formula}Oi+1 and {a mathematical formula}li+1. Therefore, the overlay {a mathematical formula}O can be computed in {a mathematical formula}O(mK2logK) time from {a mathematical formula}l1,…,lm.  □
      </paragraph>
      <paragraph>
       We note that the DCEL of {a mathematical formula}O contains incidence and adjacency information between two elements in {a mathematical formula}Face, {a mathematical formula}Edge, and {a mathematical formula}Vtx. The relationship between such an element and a polygon in L, however, is not provided. For example, the DCEL does not tell us whether an edge lies inside, outside, or on the boundary of a polygon {a mathematical formula}li. To represent the complete topological information of the polygon system L, we introduce the following functions, which can be computed by supplying a number of attributes to each object in the DCEL of the overlay.
      </paragraph>
      <paragraph>
       For each polygon {a mathematical formula}li∈L, we write {a mathematical formula}IFace(li) ({a mathematical formula}EFace(li), resp.) for the set of faces in {a mathematical formula}O that lie in the interior (exterior, resp.) of {a mathematical formula}li:{a mathematical formula}{a mathematical formula} It is clear that {a mathematical formula}IFace(li)∪EFace(li)=Face and {a mathematical formula}IFace(li)∩EFace(li)=∅.
      </paragraph>
      <paragraph>
       For each polygon {a mathematical formula}li, we define{a mathematical formula}{a mathematical formula}{a mathematical formula} and similarly,{a mathematical formula}{a mathematical formula}{a mathematical formula} Because each edge and each vertex is either in the interior of {a mathematical formula}li, or in the exterior of {a mathematical formula}li, or on the boundary of {a mathematical formula}li, we know that {a mathematical formula}{IEdge(li),EEdge(li),BEdge(li)} is a partition of {a mathematical formula}Edge, and {a mathematical formula}{IVtx(li),EVtx(li),BVtx(li)} is a partition of {a mathematical formula}Vtx.
      </paragraph>
      <paragraph label="Example 2">
       We provide an example to illustrate these functions. Suppose {a mathematical formula}L={l1,l2,l3} consists of the three polygons illustrated in Fig. 5(a). Then we have {a mathematical formula}Face={f0,…,f4}, {a mathematical formula}Vtx={v1,…,v11} and {a mathematical formula}Edge={e1,…,e14}, as shown in Figs. 5(b)–5(d). In particular, for landmark {a mathematical formula}l1, we have{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Together with the functions defined in (1), (2), (3), (4), (5), (6), (7), (8), the DCEL of the overlay of polygons in L completely describes the topological information of polygons in L. The following lemma shows that these functions can also be computed in polynomial time.
      </paragraph>
      <paragraph label="Lemma 5">
       Suppose{a mathematical formula}liis a polygon with{a mathematical formula}ki&gt;2vertices for each{a mathematical formula}1⩽i⩽m. Let{a mathematical formula}Obe the overlay of all these polygons, and K be the sum of all{a mathematical formula}ki. Then the functions defined in(1), (2), (3), (4), (5), (6), (7), (8)for all{a mathematical formula}1⩽i⩽mcan be computed in{a mathematical formula}O(m2K2)time in total.
      </paragraph>
      <paragraph label="Proof">
       As in the proof of Lemma 4, suppose {a mathematical formula}Ok is the overlay of the first k polygons {a mathematical formula}l1,…,lk and {a mathematical formula}O=Om. For each element (i.e., a face, edge or vertex) c in overlay {a mathematical formula}Oi, we introduce an additional vector to represent the relation between c and polygons {a mathematical formula}l1,l2,…,li. When updating the overlay {a mathematical formula}Oi to {a mathematical formula}Oi+1, we need to update these vectors correspondingly. Note that each {a mathematical formula}Oi has {a mathematical formula}O(K2) elements. There are {a mathematical formula}O(K2) vectors, each of which has {a mathematical formula}i⩽m indices. Therefore we need {a mathematical formula}O(mK2) time to update all vectors for each overlay {a mathematical formula}Oi, and thus {a mathematical formula}O(m2K2) time in total for {a mathematical formula}O. The functions in (1), (2), (3), (4), (5), (6), (7), (8) can be computed from the vectors for {a mathematical formula}O directly in {a mathematical formula}O(mK2) time. In summary, it takes an additional {a mathematical formula}O(m2K2) time to compute all the functions.  □ Combined with Lemma 4, this shows that the overlay and the functions can be computed in {a mathematical formula}O(m2K2logK) time.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Solving basic RCC5 constraints involving polygonal landmarks
      </section-title>
      <paragraph>
       This subsection shows that {a mathematical formula}cspsats(BRCC5) is in P, provided that all landmarks are represented as polygons. We obtain this by giving a necessary and sufficient condition for deciding the consistency of {a mathematical formula}cspsats(BRCC5) instances, which can be checked in polynomial time.
      </paragraph>
      <paragraph>
       In what follows, we write an instance of {a mathematical formula}cspsats(BRCC5) or {a mathematical formula}cspsats(BRCC8) explicitly as {a mathematical formula}(V⊎L,Γ), where {a mathematical formula}V={v1,v2,…,vn} is the set of unrestricted variables, {a mathematical formula}L={l1,l2,…,lm} is the set of uniquely restricted variables. We write, for simplicity, {a mathematical formula}li for the only value (viz. a polygonal landmark) it takes and assume that the constraint between two landmarks is the actual relation between them.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        A necessary and sufficient condition
       </section-title>
       <paragraph>
        Suppose {a mathematical formula}(V⊎L,Γ) is an instance of {a mathematical formula}cspsats(BRCC5), where {a mathematical formula}V={v1,v2,…,vn} and {a mathematical formula}L={l1,l2,…,lm}. Let {a mathematical formula}O be the overlay of polygons in L. Recall that for each {a mathematical formula}lj and each face {a mathematical formula}f in {a mathematical formula}O, {a mathematical formula}f is either in {a mathematical formula}IFace(lj) (the set of faces contained in {a mathematical formula}lj) or in {a mathematical formula}EFace(lj) (the set of faces that lie outside {a mathematical formula}lj). Constraints in Γ may impose similar relationships between {a mathematical formula}f and the variables in V. For a variable {a mathematical formula}vi, the constraints about {a mathematical formula}vi may force {a mathematical formula}f to be part of {a mathematical formula}vi, or outside {a mathematical formula}vi. Precisely, {a mathematical formula}f is required to be part of {a mathematical formula}vi if there is a landmark {a mathematical formula}lj such that {a mathematical formula}f∈IFace(lj) and {a mathematical formula}ljPPvi, and {a mathematical formula}f is required to lie outside {a mathematical formula}vi if either {a mathematical formula}viDRlj and {a mathematical formula}f∈IFace(lj), or {a mathematical formula}viPPlj and {a mathematical formula}f∈EFace(lj). For each variable {a mathematical formula}vi∈V, we thus define {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi) as follows:{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph label="Example 3">
        Suppose {a mathematical formula}(V⊎L,Γ) is an instance of {a mathematical formula}cspsats(BRCC5), where {a mathematical formula}V={v1} and {a mathematical formula}L={l1,l2,l3}. Landmarks {a mathematical formula}l1,l2,l3 are shown in Fig. 5(a). The constraints related to {a mathematical formula}v1 are specified as {a mathematical formula}l1PPv1,l2PPv1,v1POl3. Then we have{a mathematical formula}
       </paragraph>
       <paragraph label="Proof">
        The following proposition asserts that no face belongs to both {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi), given that the constraint network is path-consistent. Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC5), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. If Γ is path-consistent, then{a mathematical formula}IFace(vi)∩EFace(vi)=∅.Assume {a mathematical formula}f∈IFace(vi)∩EFace(vi). By definition there exist {a mathematical formula}lj and {a mathematical formula}lk such that {a mathematical formula}ljPPvi and {a mathematical formula}f∈IFace(lj), and either (i) {a mathematical formula}viDRlk and {a mathematical formula}f∈IFace(lk) or (ii) {a mathematical formula}viPPlk and {a mathematical formula}f∈EFace(lk). We show that both cases lead to a contradiction. For the first case, we know {a mathematical formula}f⊆lj∩lk, while the path-consistency of Γ implies that {a mathematical formula}ljDRlk since {a mathematical formula}ljPPvi and {a mathematical formula}viDRlk. For the second case, we have {a mathematical formula}f⊆lj and {a mathematical formula}f∩lk=∅, but the path-consistency of Γ implies {a mathematical formula}ljPPlk since {a mathematical formula}ljPPvi and {a mathematical formula}viPPlk.  □
       </paragraph>
       <paragraph>
        The following theorem provides a necessary and sufficient condition that decides {a mathematical formula}cspsats(BRCC5). Note that the condition only involves{a mathematical formula} and constraints in the network, hence it can be checked after constructing the overlay of all landmarks and computing {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi) for each {a mathematical formula}vi.
       </paragraph>
       <paragraph label="Theorem 8">
        Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC5), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. Then{a mathematical formula}(V⊎L,Γ)is consistent, if and only if
       </paragraph>
       <list>
        <list-item label="•">
         Γ is path-consistent.
        </list-item>
        <list-item label="•">
         For any{a mathematical formula}vi∈V,{a mathematical formula}EFace(vi)≠Face.
        </list-item>
        <list-item label="•">
         All the conditions inTable 7hold.
        </list-item>
       </list>
       <paragraph>
        Conditions in Table 7 are very natural. For instance, the three conditions for constraint {a mathematical formula}(viPOlj) guarantee, respectively, that (i) {a mathematical formula}vi is not a proper subset of {a mathematical formula}lj, (ii) {a mathematical formula}vi is not a proper superset of {a mathematical formula}lj, and (iii) {a mathematical formula}vi may overlap with {a mathematical formula}lj, i.e., not every face in {a mathematical formula}IFace(lj) is excluded from {a mathematical formula}vi. Consider Example 3 again.
       </paragraph>
       <paragraph label="Example 3">
        continuedIn this example, we have {a mathematical formula}IFace(v1)={f1,f2,f3,f4} and {a mathematical formula}EFace(v1)=∅. Since {a mathematical formula}EFace(l3)={f0,f1,f4}, we know {a mathematical formula}IFace(v1)∪EFace(l3)={f0,f1,f2,f3,f4}=Face. Because {a mathematical formula}(v1POl3)∈Γ, Row 3 of Table 7 is violated. By Theorem 8 we know this instance is inconsistent.
       </paragraph>
       <paragraph>
        We prove the necessity part here and leave the sufficiency part to Appendix A.
       </paragraph>
       <paragraph label="Proof of Theorem 8 (Necessity)">
        The remaining cases are either straightforward or similar to the above two cases.  □
       </paragraph>
       <paragraph>
        Using Theorem 8, we are able to determine the consistency of any instance of {a mathematical formula}cspsats(BRCC5) in the following procedure:
       </paragraph>
       <list>
        <list-item label="–">
         Compute {a mathematical formula}IFace(lj) and {a mathematical formula}EFace(lj) for each landmark {a mathematical formula}lj (this relies on the computation of the overlay planar subdivision {a mathematical formula}O).
        </list-item>
        <list-item label="–">
         Compute {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi) for each variable {a mathematical formula}vi.
        </list-item>
        <list-item label="–">
         Check the conditions in Theorem 8.
        </list-item>
       </list>
       <paragraph>
        Therefore the computational complexity of solving {a mathematical formula}cspsats(BRCC5) consists of three parts, corresponding to (i) computing {a mathematical formula}IFace(lj) and {a mathematical formula}EFace(lj), (ii) computing {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi), and (iii) checking the conditions in Theorem 8. Putting them together, we come to the following theorem.
       </paragraph>
       <paragraph label="Theorem 9">
        Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC5), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. Let{a mathematical formula}kibe the complexity of the planar subdivision induced by{a mathematical formula}li, and let{a mathematical formula}K=∑i=1mki. Then the consistency of{a mathematical formula}(V⊎L,Γ)can be decided in{a mathematical formula}O(n3+n2K2+m2K2logK)time.
       </paragraph>
       <paragraph label="Proof">
        Lemma 4, Lemma 5 show that {a mathematical formula}O, the overlay of all landmarks in L, together with {a mathematical formula}IFace(lj) and {a mathematical formula}EFace(lj), can be computed in {a mathematical formula}O(m2K2logK) time. Moreover, all {a mathematical formula}IFace(vi) and {a mathematical formula}EFace(vi) can be computed in {a mathematical formula}O(nmK2) time by definition. For the conditions in Theorem 8, it takes {a mathematical formula}O((n+m)3) time to check the path-consistency of Γ, and {a mathematical formula}O(K2) time to check each of the remaining {a mathematical formula}O(n(n+m)) conditions. Therefore, it takes {a mathematical formula}O((n+m)3+n(n+m)K2) time to check all the conditions in Theorem 8. Summing these up, the consistency of {a mathematical formula}(V⊎L,Γ) can be determined in {a mathematical formula}O((n+m)3+n(n+m)K2+m2K2logK) time. Note that {a mathematical formula}m⩽∑i=1mki=K. If {a mathematical formula}m⩽n, then {a mathematical formula}O((m+n)3)=O(n3); if {a mathematical formula}n⩽m, then {a mathematical formula}O((m+n)3)=O(m3). In both cases we have {a mathematical formula}O((m+n)3)=O(m3+n3). Similarly we have {a mathematical formula}O(mnK2)=O(m2K2+n2K2). Therefore,{a mathematical formula} and the consistency of {a mathematical formula}(V⊎L,Γ) can be decided in {a mathematical formula}O(n3+n2K2+m2K2logK) time.  □
       </paragraph>
       <paragraph label="Proof">
        As a direct consequence, we have Assuming that all landmarks are represented by polygons, then the consistency problem{a mathematical formula}cspsats(BRCC5)is in P, and the consistency problems{a mathematical formula}cspsatf(BRCC5),{a mathematical formula}cspsats(RCC5), and{a mathematical formula}cspsatf(RCC5)are all NP-complete.It follows directly from Theorem 9 that {a mathematical formula}cspsats(BRCC5) is in P. Moreover, by Proposition 1 we know that {a mathematical formula}cspsatf(BRCC5), {a mathematical formula}cspsats(RCC5), and {a mathematical formula}cspsatf(RCC5) are all in NP. The NP-hardness of {a mathematical formula}cspsatf(BRCC5) is proven in Proposition 6, and the NP-hardness of {a mathematical formula}cspsats(RCC5) and {a mathematical formula}cspsatf(RCC5) follows from the NP-hardness of {a mathematical formula}cspsat(RCC5).  □
       </paragraph>
       <paragraph>
        Although {a mathematical formula}cspsats(BRCC5) is in P, we show in the next subsection that the consistency problem {a mathematical formula}cspsats(BRCC8) is NP-hard.
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Solving basic RCC8 constraints involving landmarks
      </section-title>
      <paragraph>
       This subsection investigates the consistency problem {a mathematical formula}cspsats(BRCC8). First, we show that the problem is NP-hard by exploiting the fact that two polygons may have multiple ‘meeting’ points. Second, we show that the problem is still in NP by providing a polynomial nondeterministic algorithm. We then consider another interpretation of the RCC8 model by using a stronger connectedness. Under this interpretation, we show that {a mathematical formula}cspsats(BRCC8) is still tractable.
      </paragraph>
      <section label="4.4.1">
       The NP-hardness of {a mathematical formula}cspsats(BRCC8)
       <paragraph>
        We reduce the Graph 3-Colouring problem to the {a mathematical formula}cspsats(BRCC8) problem.
       </paragraph>
       <paragraph label="Proposition 9">
        Assuming that all landmarks are represented by polygons, the consistency problem{a mathematical formula}cspsats(BRCC8)is NP-hard.
       </paragraph>
       <paragraph label="Proof">
        Suppose {a mathematical formula}G=(V,E) is a graph and {a mathematical formula}V={v0,…,vn}. We construct a {a mathematical formula}cspsats(BRCC8) instance {a mathematical formula}(VG⊎L,ΓG) as follows. The landmark set L is independent of the choice of G and contains the two polygons l and {a mathematical formula}l′ in Fig. 6(a). Note that l and {a mathematical formula}l′ are externally connected and have exactly three meeting points {a mathematical formula}Q0,Q1 and {a mathematical formula}Q2, which are used to mimic the three colours in the Graph 3-Colouring problem.The spatial variable set {a mathematical formula}VG is defined as {a mathematical formula}{u0,u1,…,un}, where spatial variable {a mathematical formula}ui corresponds to vertex {a mathematical formula}vi in V. The constraint network {a mathematical formula}ΓG is defined as follows.{a mathematical formula}We have finished the construction of the instance. The idea behind this reduction is as follows. Because l and {a mathematical formula}l′ have only three meeting points (viz. {a mathematical formula}Q0,Q1 and {a mathematical formula}Q2), each {a mathematical formula}ui can be connected to {a mathematical formula}l′ only via (one or more of) the three points {a mathematical formula}Q0,Q1,Q2. Determining which point {a mathematical formula}ui should occupy is essentially equivalent to choosing a colour for vertex {a mathematical formula}vi. For {a mathematical formula}vi and {a mathematical formula}vj, if {a mathematical formula}(vi,vj) is an edge in E, then they cannot be coloured the same. Correspondingly, in such a case there is a constraint {a mathematical formula}uiDCuj, which forbids that {a mathematical formula}ui and {a mathematical formula}uj occupy the same point in {a mathematical formula}{Q0,Q1,Q2}.We now prove that G is 3-colourable iff {a mathematical formula}(VG⊎L,ΓG) is consistent. Suppose {a mathematical formula}π:V→{0,1,2} is a valid 3-colouring of G. We choose three candidate regions {a mathematical formula}ri0, {a mathematical formula}ri1 and {a mathematical formula}ri2 for each variable {a mathematical formula}ui, where {a mathematical formula}rip is a triangle contained in l with a vertex being {a mathematical formula}Qp. The candidate regions {a mathematical formula}r0p,r1p,…,rnp are externally connected at {a mathematical formula}Qp, as illustrated in Fig. 6(b). If we assign {a mathematical formula}riπ(vi) to {a mathematical formula}ui, then all the {a mathematical formula}DC constraints are satisfied. This is because, {a mathematical formula}riπ(vi) and {a mathematical formula}rjπ(vj) are connected iff {a mathematical formula}π(vi)=π(vj). This assignment, however, cannot fulfil all the {a mathematical formula}EC constraints. For each unsatisfied {a mathematical formula}EC constraint {a mathematical formula}(uiECuj), we introduce a pair of rectangles {a mathematical formula}rij and {a mathematical formula}rij′, which are external connected and contained in l. We require that these rectangles are small enough and disjoint from any other rectangles {a mathematical formula}ri′j′, {a mathematical formula}ri′j′′ and any triangle {a mathematical formula}rkp. We then add {a mathematical formula}rij and {a mathematical formula}rij′ into, respectively, the candidate regions we have selected for {a mathematical formula}ui and {a mathematical formula}uj. It is routine to verify that the modified assignment satisfies all constraints in {a mathematical formula}ΓG and hence is a solution of {a mathematical formula}(VG⊎L,ΓG).For the other direction, suppose {a mathematical formula}(a0,…,an) is a solution of {a mathematical formula}(VG⊎L,ΓG). Note that each {a mathematical formula}ai occupies at least one point in {a mathematical formula}{Q0,Q1,Q2}. Define {a mathematical formula}π:V→{0,1,2} by assigning {a mathematical formula}vi the smallest index q such that {a mathematical formula}ai occupies {a mathematical formula}Qq. The assignment π is a valid 3-colouring for graph G. In fact, suppose {a mathematical formula}π(vi)=π(vj)=p. Then by definition both {a mathematical formula}ai and {a mathematical formula}aj occupies {a mathematical formula}Qp. Hence {a mathematical formula}(uiDCuj) is not a constraint in {a mathematical formula}ΓG, which happens only when {a mathematical formula}(vi,vj)∉E.The reduction given above is polynomial because there are only two landmarks and {a mathematical formula}|V| spatial variables in {a mathematical formula}(VG⊎L,ΓG). Therefore, the consistency problem {a mathematical formula}cspsats(BRCC8) is NP-hard.  □
       </paragraph>
       <paragraph>
        In the next subsection we show that {a mathematical formula}cspsats(BRCC8) is still in NP by designing a nondeterministic algorithm.
       </paragraph>
      </section>
      <section label="4.4.2">
       A nondeterministic algorithm for {a mathematical formula}cspsats(BRCC8)
       <paragraph>
        Suppose {a mathematical formula}(V⊎L,Γ) is an instance of {a mathematical formula}cspsats(BRCC8), where {a mathematical formula}V={v1,v2,…,vn}, {a mathematical formula}L={l1,l2,…,lm}, and each {a mathematical formula}li is a polygon. We write {a mathematical formula}O for the overlay of all landmarks in L, and define{a mathematical formula} as in (1), (2), (3), (4), (5), (6), (7), (8) for representing the topological relations between faces, edges, vertices in {a mathematical formula}O and landmarks in L. As in the case of {a mathematical formula}cspsats(BRCC5), we extend these definitions from landmarks to variables. In the following, we say an edge {a mathematical formula}e or a vertex {a mathematical formula}v in {a mathematical formula}O is incident to a face {a mathematical formula}f in {a mathematical formula}O if {a mathematical formula}e or {a mathematical formula}v is contained in the boundary of {a mathematical formula}f, and write{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Note that {a mathematical formula}SFace(e) has exactly two faces and {a mathematical formula}SFace(v) may have more than two faces. These two functions can be directly obtained from the DCEL of the overlay.
       </paragraph>
       <paragraph>
        Similarly as in the RCC5 case, we define {a mathematical formula}IFace(vi) as the set of faces that should be part of {a mathematical formula}vi and define {a mathematical formula}EFace(vi) as the set of faces that should be excluded from {a mathematical formula}vi.{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Moreover, we define {a mathematical formula}IEdge(vi) as the set of edges that should lie in the interior of {a mathematical formula}vi, {a mathematical formula}EEdge(vi) as the set of edges that should lie in the exterior of {a mathematical formula}vi, and {a mathematical formula}BEdge(vi) as the set of edges that are required to be parts of the boundary of {a mathematical formula}vi.{a mathematical formula}{a mathematical formula}{a mathematical formula} A brief explanation for the above notions follows. For an edge {a mathematical formula}e, if its two incident faces (i.e., faces in {a mathematical formula}SFace(e)) are both in {a mathematical formula}IFace(vi) ({a mathematical formula}EFace(vi), resp.), then {a mathematical formula}e itself should be in the interior (exterior, resp.) of {a mathematical formula}vi. If one incident face of {a mathematical formula}e is in {a mathematical formula}IFace(vi) while the other is in {a mathematical formula}EFace(vi), we know that {a mathematical formula}e should be on the boundary of {a mathematical formula}vi (i.e. {a mathematical formula}e∈BEdge(vi)). Moreover, suppose {a mathematical formula}e is a boundary edge of {a mathematical formula}lj (i.e. {a mathematical formula}e∈BEdge(lj)). If {a mathematical formula}ljNTPPvi, then {a mathematical formula}e should lie in the interior of {a mathematical formula}vi (i.e. {a mathematical formula}e∈IEdge(vi)); if {a mathematical formula}viDClj or {a mathematical formula}viNTPPlj, then {a mathematical formula}e should lie in the exterior of {a mathematical formula}vi (i.e. {a mathematical formula}e∈EEdge(vi)).
       </paragraph>
       <paragraph>
        In the same way, we define {a mathematical formula}IVtx(vi), {a mathematical formula}EVtx(vi) and {a mathematical formula}BVtx(vi):{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Note that {a mathematical formula}SFace(v) may contain multiple faces while {a mathematical formula}SFace(e) contains exactly two faces.
       </paragraph>
       <paragraph label="Proposition 10">
        Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC8), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. If Γ is path-consistent, then for each variable{a mathematical formula}viwe have
       </paragraph>
       <list>
        <list-item label="(1)">
         {a mathematical formula}IFace(vi)∩EFace(vi)=∅.
        </list-item>
        <list-item label="(2)">
         {a mathematical formula}IVtx(vi),{a mathematical formula}EVtx(vi), and{a mathematical formula}BVtx(vi)are pairwise disjoint.
        </list-item>
        <list-item label="(3)">
         {a mathematical formula}IEdge(vi),{a mathematical formula}EEdge(vi), and{a mathematical formula}BEdge(vi)are pairwise disjoint.
        </list-item>
       </list>
       <paragraph label="Proof">
        (1) can be proven in the same way as Proposition 8. The remaining two can be similarly proven. Here we only show {a mathematical formula}IVtx(vi)∩BVtx(vi)=∅ as an example.Suppose otherwise that there exists a vertex {a mathematical formula}v∈Vtx such that {a mathematical formula}v∈IVtx(vi) and {a mathematical formula}v∈BVtx(vi). Because {a mathematical formula}v∈BVtx(vi) we know there exist {a mathematical formula}f1,f2 that are incident to {a mathematical formula}v and {a mathematical formula}f1∈IFace(vi),f2∈EFace(vi). This implies that not all incident faces of {a mathematical formula}v are in {a mathematical formula}IFace(vi). Therefore, by {a mathematical formula}v∈IVtx(vi), we know there exists a landmark {a mathematical formula}lj such that {a mathematical formula}ljNTPPvi and {a mathematical formula}v∈BVtx(lj).As {a mathematical formula}f2∈EFace(vi), by definition, we know that there exists a landmark {a mathematical formula}lk such that either (i) {a mathematical formula}f2∈IFace(lk) and {a mathematical formula}viDClk or {a mathematical formula}viEClk; or (ii) {a mathematical formula}f2∈EFace(lk) and {a mathematical formula}viNTPPlk or {a mathematical formula}viTPPlk. Note that Γ is path-consistent. Case (i) implies that {a mathematical formula}f2⊂lk and {a mathematical formula}ljDClk. Because {a mathematical formula}v is incident to {a mathematical formula}f2, this shows that {a mathematical formula}v is in {a mathematical formula}lk. By {a mathematical formula}v∈BVtx(lj) we also have {a mathematical formula}v∈lj. This contradicts the conclusion {a mathematical formula}ljDClk. In Case (ii), we have {a mathematical formula}ljNTPPlk and {a mathematical formula}f2∩lk=∅. This also leads to a contradiction, because {a mathematical formula}ljNTPPlk implies {a mathematical formula}v is in the interior of {a mathematical formula}lk, and {a mathematical formula}f2∩lk=∅ implies that {a mathematical formula}v is not in the interior of {a mathematical formula}lk.Therefore, we have {a mathematical formula}IVtx(vi)∩BVtx(vi)=∅.  □
       </paragraph>
       <paragraph>
        For convenience, we define{a mathematical formula}{a mathematical formula}{a mathematical formula} where {a mathematical formula}P denotes ‘pending’. We note that while {a mathematical formula}BVtx(vi) is the set of vertices that must lie on the boundary of {a mathematical formula}vi, {a mathematical formula}PVtx(vi) contains all the vertices that may lie on the boundary of {a mathematical formula}vi. The pairwise disjointness of {a mathematical formula}IVtx(vi),EVtx(vi) and {a mathematical formula}BVtx(vi) implies {a mathematical formula}BVtx(vi)⊆PVtx(vi).
       </paragraph>
       <paragraph>
        Suppose Γ is consistent and has a solution {a mathematical formula}v¯1,v¯2,…,v¯n. Write {a mathematical formula}S¯i for the set of vertices on the boundary of {a mathematical formula}v¯i, i.e., {a mathematical formula}S¯i={v∈Vtx:v∈∂v¯i}. Then it is straightforward to show that{a mathematical formula}
       </paragraph>
       <paragraph>
        As we have seen in the reduction, determining {a mathematical formula}S¯i could be intractable. If all {a mathematical formula}S¯i are given in advance as a constraint for spatial variable {a mathematical formula}vi (i.e., we explicitly specify whether vertex {a mathematical formula}e in the overlay is on the boundary of {a mathematical formula}vi for all {a mathematical formula}e and {a mathematical formula}vi), then the existence of such a solution can be determined in polynomial time.
       </paragraph>
       <paragraph label="Lemma 6">
        Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC8), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. Assume furthermore that{a mathematical formula}Siis a subset of{a mathematical formula}Vtxfor{a mathematical formula}i=1,2,…,n. If Γ is path-consistent, then{a mathematical formula}(V⊎L,Γ)has a solution{a mathematical formula}{v¯1,v¯2,…,v¯n}such that{a mathematical formula}∂v¯i∩Vtx=Siif and only if
       </paragraph>
       <list>
        <list-item label="(a)">
         {a mathematical formula}EFace(vi)≠Faceand{a mathematical formula}BVtx(vi)⊆Si⊆PVtx(vi)for each{a mathematical formula}vi.
        </list-item>
        <list-item label="(b)">
         All the conditions inTable 8hold, where{a mathematical formula}{a mathematical formula}
        </list-item>
       </list>
       <paragraph label="Proof">
        See Appendix B.  □
       </paragraph>
       <paragraph label="Proof">
        Based on this result, we have the following theorem. Suppose all landmarks are represented by polygons. Then the consistency problem{a mathematical formula}cspsats(BRCC8)is NP-complete. Moreover, the consistency problems{a mathematical formula}cspsatf(BRCC8),{a mathematical formula}cspsats(RCC8), and{a mathematical formula}cspsatf(RCC8)are all NP-complete.We propose a nondeterministic algorithm which solves {a mathematical formula}cspsats(BRCC8). The algorithm first guesses a configuration of {a mathematical formula}Si and uses it as an additional constraint, then determines the consistency by Lemma 11. Note that each {a mathematical formula}Si has {a mathematical formula}O(K2) points, which are polynomial in the input size. Thus guessing a configuration of {a mathematical formula}Si takes polynomial time. Meanwhile, checking all the conditions also takes polynomial time. Therefore, the extended consistency problem {a mathematical formula}cspsats(BRCC8) is in NP, and hence NP-complete as its NP-hardness has been confirmed in Proposition 9.By Proposition 1 (ii) and (iii) we know {a mathematical formula}cspsatf(BRCC8), {a mathematical formula}cspsats(RCC8), and {a mathematical formula}cspsatf(RCC8) are all in NP. Meanwhile, they are also NP-hard because they all contain the NP-hard problem {a mathematical formula}cspsats(BRCC8) as a sub-problem. Therefore, they are all NP-complete.  □
       </paragraph>
       <paragraph label="Remark 2">
        Recall that in the reduction from the Graph 3-Colouring problem to {a mathematical formula}cspsats(BRCC8) the landmark l is a concave polygon which has three meeting points with landmark {a mathematical formula}l′ (see Fig. 6(a)). This property of landmarks plays a critical role in designing the reduction. Another reduction from the 3-SAT problem to {a mathematical formula}cspsats(BRCC8), given in [29], also uses concave landmarks. Note that two convex polygons cannot have multiple isolated meeting points (i.e. they either have only one meeting point or share a line segment). One may conjecture that the consistency problem {a mathematical formula}cspsats(BRCC8) becomes tractable if all landmarks are represented as convex polygons. This, however, is not true.In fact, a polynomial reduction from 3-SAT to {a mathematical formula}cspsats(BRCC8) exists even if all landmarks are represented by rectangles with edges parallel to the coordinate axes. The reduction is more complicated than the reduction provided in the proof of Proposition 9. The main idea is, although landmarks are all convex regions, spatial variables can be interpreted as arbitrary regions, and we can constrain a spatial variable by using these rectangular landmarks in a way such that it may have multiple meeting points with some landmark. For example, suppose {a mathematical formula}l0,l1,l2 are three rectangles as shown in Fig. 7, where {a mathematical formula}l1TPPl0, {a mathematical formula}l0ECl2 and {a mathematical formula}l1ECl2. Assume that v is a spatial variable and {a mathematical formula}vTPPl0, {a mathematical formula}vECl1 and {a mathematical formula}vECl2. These constraints require v to contain (at least) one of the two points {a mathematical formula}Q+ and {a mathematical formula}Q−, which may be used to simulate a propositional variable. Based on this obversion, a reduction from 3-SAT can be devised. Therefore, the consistency problem {a mathematical formula}cspsats(BRCC8) remains NP-hard even for rectangular landmarks.
       </paragraph>
       <paragraph label="Remark 3">
        In practice, we may reduce the problem {a mathematical formula}cspsats(BRCC8) to SAT (i.e. deciding the satisfiability of propositional formulas in conjunctive normal form). As stated in the proof of Theorem 11, {a mathematical formula}cspsats(BRCC8) is equivalent to deciding whether there exist {a mathematical formula}Si⊆Vtx for each i such that all the conditions in Lemma 6 are satisfied. Note that, once the instance is given, the conditions in the lemma can be simplified (in polynomial time) into a set of conditions concerning {a mathematical formula}Si of the following forms: {a mathematical formula}R⊆Si⊆R′, {a mathematical formula}Si∩R≠∅, {a mathematical formula}Si∩Sj=∅, and {a mathematical formula}Si∩Sj≠∅, where R and {a mathematical formula}R′ are subsets of {a mathematical formula}Vtx determined by the instance. For each {a mathematical formula}Si and each vertex {a mathematical formula}v∈Vtx, we introduce a propositional variable which is assigned {a mathematical formula}true iff {a mathematical formula}v is in {a mathematical formula}Si. In this way, each condition in one of the above forms is transformed into a disjunction clause or a number of disjunction clauses, and thus a {a mathematical formula}cspsats(BRCC8) instance is transformed into an equivalent SAT instance. Therefore, {a mathematical formula}cspsats(BRCC8) can be reduced to SAT, which enables us to solve the problem by the well-developed SAT solvers.
       </paragraph>
       <paragraph>
        The NP-hardness of {a mathematical formula}cspsats(BRCC8) is quite undesirable, as it is the simplest and most fundamental case of introducing landmarks to reasoning with RCC8. In the following subsection, we show that the same problem becomes tractable if we interpret RCC8 relations by using a stronger connectedness relation.
       </paragraph>
      </section>
      <section label="4.4.3">
       <section-title>
        RCC8 model based on strong connectedness
       </section-title>
       <paragraph>
        In the standard RCC8 model, two regions are considered to be connected if they have a common point. Consequently, two externally connected ({a mathematical formula}EC) regions may share one or more isolated boundary points (see Fig. 6(a)). In this subsection, we turn to another interpretation of RCC8, which uses a stronger version of connectedness: two regions are considered as connected if they share a common curve, where a curve is defined as a topological embedding of the closed interval {a mathematical formula}[0,1] in the plane. As a result, two non-overlapping regions are externally connected iff their boundaries share at least a curve. Formally, we have
       </paragraph>
       <paragraph label="Definition 8">
        RCC8 algebra based on strong connectednessLet U be the set of nonempty regular closed sets, or regions, in the real plane. The RCC8 algebra based on strong connectedness, written RCC8′, is generated by the following eight topological relations{a mathematical formula} where {a mathematical formula}TPPi and {a mathematical formula}NTPPi are the converses of {a mathematical formula}TPP and {a mathematical formula}NTPP respectively, and {a mathematical formula}EQ is the identity relation, and for two regions {a mathematical formula}a,b,
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}aDCb iff {a mathematical formula}a∩b does not contain any curve;
        </list-item>
        <list-item label="•">
         {a mathematical formula}aECb iff {a mathematical formula}a∘∩b∘=∅ and {a mathematical formula}a∩b contains at least one curve;
        </list-item>
        <list-item label="•">
         {a mathematical formula}aNTPPb iff {a mathematical formula}a⊂b and {a mathematical formula}∂a∩∂b does not contain any curve;
        </list-item>
        <list-item label="•">
         {a mathematical formula}aTPPb iff {a mathematical formula}a⊂b and {a mathematical formula}∂a∩∂b contains at least one curve;
        </list-item>
        <list-item label="•">
         {a mathematical formula}aPOb iff {a mathematical formula}a∘∩b∘≠∅ and {a mathematical formula}a⊈b, {a mathematical formula}b⊈a.
        </list-item>
       </list>
       <paragraph>
        It is easy to see that this connectedness relation (i.e. the complement of {a mathematical formula}DC) is stronger than (i.e. contained in) the connectedness relation given in Definition 4.
       </paragraph>
       <paragraph>
        Intuitively, the NP-hardness of {a mathematical formula}cspsats(BRCC8) (for weak connectedness) is due to that there are exponentially many possibilities of {a mathematical formula}Si (the intersection of {a mathematical formula}Vtx and the boundary of {a mathematical formula}vi), since points in {a mathematical formula}Si may be evidences of {a mathematical formula}EC constraints (cf. the reduction in Section 4.4.1). In the strong connectedness interpretation, however, isolated meeting points have no effects on RCC8 relations. Therefore {a mathematical formula}Si may be ignored safely and the problem {a mathematical formula}cspsats(BRCC8′) becomes tractable, as shown in the following theorem.
       </paragraph>
       <paragraph label="Theorem 12">
        The consistency problem{a mathematical formula}cspsats(BRCC8′)can be decided in polynomial time.
       </paragraph>
       <paragraph>
        The computational complexity of {a mathematical formula}cspsats(BRCC8′) is the same as that of {a mathematical formula}cspsats(BRCC5) (see Theorem 9), as the argument for RCC5 still applies here. Precisely, the consistency of an instance of {a mathematical formula}cspsats(BRCC8′) can be decided by checking the conditions in Lemma 6 and neglecting all conditions involving {a mathematical formula}Si. That is, we discard the following conditions:
       </paragraph>
       <list>
        <list-item label="•">
         the condition {a mathematical formula}BVtx(vi)⊆Si⊆PVtx(vi) in condition (a);
        </list-item>
        <list-item label="•">
         the condition {a mathematical formula}Si∩Sj=∅ whenever {a mathematical formula}(viDCvj)∈Γ in Row 4 of Table 8;
        </list-item>
        <list-item label="•">
         the disjunct {a mathematical formula}Si∩BVtx(lj)≠∅ in (25);
        </list-item>
        <list-item label="•">
         the disjunct {a mathematical formula}Si∩Sj≠∅ in (26).
        </list-item>
       </list>
       <paragraph>
        The above theorem can be proven by modifying the proof of Lemma 6 with a slightly different construction. The proof sketch is provided in Appendix C.
       </paragraph>
       <paragraph label="Remark 4">
        The strong connectedness introduced above has been considered in [3], [8]. In particular, in [3], Borgo, Guarino, and Masolo argued that the classical Whiteheadian connectedness may be considered too weak in many cases. For example, “a worm cannot pass from the interior of one apple to another, which touch just at a point, without becoming visible to the exterior – so from the wormʼs point of view we might as well say that the apples are not ‘sufficiently’ connected.”As far as consistency and realisations are concerned, Li [19] has shown that any consistent RCC8 network has a solution in any RCC model. The cubic realisation algorithm described there can be easily adapted to construct a solution in the RCC8 model based on strong connectedness. This implies in particular that an RCC8 network (without landmarks) has a solution in the RCC8 model with ‘weak’ connectedness iff it has a solution in the RCC8 model with ‘strong’ connectedness.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Proof of Theorem 8 (Sufficiency)
     <paragraph>
      The sufficiency part is proven by a realisation algorithm which generates a solution of the constraint network. The algorithm is similar to the classical realisation algorithm introduced in [19], [22]. We first construct for each variable {a mathematical formula}vi a region {a mathematical formula}ai such that {a mathematical formula}{a1,a2,…,an} satisfies all except the {a mathematical formula}PP constraints, and then construct regions {a mathematical formula}{c1,c2,…,cn} which is a solution of Γ.
     </paragraph>
     <paragraph>
      For each variable {a mathematical formula}vi, we define{a mathematical formula}
     </paragraph>
     <paragraph>
      A number of ‘base regions’ are necessary in the construction of {a mathematical formula}{a1,a2,…,an}. Base regions are arbitrarily selected, as long as they are pairwise disjoint polygons and are so small that their union does not contain any face. We use {a mathematical formula}Xi to denote the set of base regions being selected for variable {a mathematical formula}vi. The construction is as follows, where each {a mathematical formula}Xi is initialised as the empty set.
     </paragraph>
     <list>
      <list-item label="1.">
       For each face {a mathematical formula}f∈PFace(vi), select a base region contained in {a mathematical formula}f and put it into {a mathematical formula}Xi.
      </list-item>
      <list-item label="2.">
       For any {a mathematical formula}i&lt;j such that {a mathematical formula}(viPOvj)∈Γ and {a mathematical formula}PFace(vi)∩PFace(vj)≠∅, select a face {a mathematical formula}f in {a mathematical formula}PFace(vi)∩PFace(vj) and a base region contained in {a mathematical formula}f. Put the base region into both {a mathematical formula}Xi and {a mathematical formula}Xj.
      </list-item>
      <list-item label="3.">
       For each i, let {a mathematical formula}ai=⋃Xi.
      </list-item>
      <list-item label="4.">
       For each i, let {a mathematical formula}bi=ai∪⋃{aj:(vjPPvi)∈Γ}.
      </list-item>
      <list-item label="5.">
       For each i, let {a mathematical formula}ci=bi∪⋃{lj:(ljPPvi)∈Γ}.
      </list-item>
     </list>
     <paragraph label="Lemma 7">
      Suppose{a mathematical formula}(V⊎L,Γ)is an instance of{a mathematical formula}cspsats(BRCC5), where{a mathematical formula}V={v1,v2,…,vn},{a mathematical formula}L={l1,l2,…,lm}, and each{a mathematical formula}liis a polygon. Suppose Γ is path-consistent. Assume that{a mathematical formula}ai,bi,ci{a mathematical formula}(1⩽i⩽n)are as in the construction given above. Then for each face{a mathematical formula}f∈Facewe have
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}f∈IFace(vi)iff{a mathematical formula}f⊆ci.
      </list-item>
      <list-item label="•">
       {a mathematical formula}f∈EFace(vi)iff{a mathematical formula}f∩ci=∅.
      </list-item>
      <list-item label="•">
       {a mathematical formula}f∈PFace(vi)iff{a mathematical formula}f⊈ciand{a mathematical formula}f∩ci≠∅.
      </list-item>
     </list>
     <paragraph label="Proof">
      We first prove the necessity part.Suppose {a mathematical formula}f∈IFace(vi). There exists a landmark l such that {a mathematical formula}f∈IFace(l) and {a mathematical formula}lPPvi. Because {a mathematical formula}l⊆ci, the first statement holds directly.Assume {a mathematical formula}f∈EFace(vi). Because each base region in {a mathematical formula}Xi is contained in a face in {a mathematical formula}PFace(vi), we know that {a mathematical formula}f∩ai=∅. Suppose {a mathematical formula}(vjPPvi)∈Γ. By the definition of {a mathematical formula}EFace(vj) and the path-consistency of Γ, it is direct to prove that {a mathematical formula}f is also in {a mathematical formula}EFace(vj). Therefore we have {a mathematical formula}f∩aj=∅, and thus {a mathematical formula}f∩bi=∅ by the construction of {a mathematical formula}bi. Similarly, for any landmark l such that {a mathematical formula}(lPPvi)∈Γ, we can prove that {a mathematical formula}f∩l=∅. Therefore, we have {a mathematical formula}f∩ci=∅.Now assume {a mathematical formula}f∈PFace(vi). Clearly we have {a mathematical formula}f∩ai≠∅ because {a mathematical formula}Xi has a base region contained in {a mathematical formula}f. We only need to prove {a mathematical formula}f⊈ci. By the selection of base regions, {a mathematical formula}f is not contained in the union of all base regions, and hence it is not contained in {a mathematical formula}bi. Moreover, for any landmark {a mathematical formula}lj, if {a mathematical formula}(ljPPvi)∈Γ, then {a mathematical formula}f∈EFace(lj) (otherwise, {a mathematical formula}f∈IFace(lj)⊆IFace(vi)). That is to say, {a mathematical formula}f is disjoint with {a mathematical formula}lj. Therefore, {a mathematical formula}f⊈ci.The sufficiency part follows from {a mathematical formula}IFace(vi)∪EFace(vi)∪PFace(vi)=Face.  □
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula}(V⊎L,Γ)and{a mathematical formula}cibe as inLemma 7. Furthermore, suppose{a mathematical formula}(V⊎L,Γ)satisfies all the conditions inTheorem 8. Then{a mathematical formula}{c1,c2,…,cn}satisfies all the constraints in Γ of the form{a mathematical formula}viαlj.Because {a mathematical formula}(V⊎L,Γ) satisfies the conditions in Theorem 8, we know in particular that {a mathematical formula}EFace(vi)≠Face for each {a mathematical formula}1⩽i⩽n. That is, there exists a face {a mathematical formula}f in {a mathematical formula}IFace(vi)∪PFace(vi). By Lemma 7, this implies that each {a mathematical formula}ci is nonempty.(1) If {a mathematical formula}(viPPlj)∈Γ, then we have {a mathematical formula}EFace(lj)⊆EFace(vi) by (10). Lemma 7 directly implies that {a mathematical formula}ci⊆lj. Because {a mathematical formula}IFace(vi)≠IFace(lj) (Row 2 in Table 7), there exists a face {a mathematical formula}f which is in {a mathematical formula}IFace(lj) but not in {a mathematical formula}IFace(vi). By Lemma 7, {a mathematical formula}f is not contained in {a mathematical formula}ci. Therefore, {a mathematical formula}ci⊂lj, i.e. {a mathematical formula}ciPPlj.(2) If {a mathematical formula}(ljPPvi)∈Γ, clearly we have {a mathematical formula}lj⊆ci. Because {a mathematical formula}EFace(vi)≠EFace(lj) (Row 3 in Table 7) and {a mathematical formula}EFace(vi)⊆Face−IFace(vi)⊆Face−IFace(lj)=EFace(lj), we know that {a mathematical formula}EFace(vi)⊂EFace(lj), i.e. there exists a face {a mathematical formula}f in {a mathematical formula}EFace(lj) but not in {a mathematical formula}EFace(vi). Therefore {a mathematical formula}f∩lj=∅ and {a mathematical formula}f∩ci≠∅. That is, {a mathematical formula}lj⊂ci, i.e. {a mathematical formula}ljPPci.(3) If {a mathematical formula}(viDRlj)∈Γ, then we have {a mathematical formula}IFace(lj)⊆EFace(vi). Lemma 7 directly implies that {a mathematical formula}ci∩lj∘=∅, i.e. {a mathematical formula}ciDRlj.(4) If {a mathematical formula}(viPOlj)∈Γ, then by Row 1 in Table 7, we know that {a mathematical formula}EFace(vi)∪EFace(lj)≠Face. That is, there exists a face {a mathematical formula}f such that {a mathematical formula}f∉EFace(vi) and {a mathematical formula}f∉EFace(lj) (hence {a mathematical formula}f∈IFace(lj)). Therefore {a mathematical formula}f⊆lj and {a mathematical formula}f∩ci≠∅ by Lemma 7, and hence {a mathematical formula}ci overlaps {a mathematical formula}lj, i.e. they have a common interior point. It can be proven that {a mathematical formula}ci⊈lj and {a mathematical formula}lj⊈ci as in the first two cases above. Therefore, {a mathematical formula}ciPOlj holds.  □
     </paragraph>
     <paragraph>
      We next prove that {a mathematical formula}{c1,…,cn} is a solution of Γ.
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula}(V⊎L,Γ)and{a mathematical formula}cibe as inCorollary 2. Then{a mathematical formula}{c1,…,cn}is a solution of{a mathematical formula}(V⊎L,Γ).We only need to prove that constraints of the form {a mathematical formula}(viαvj) are satisfied.(1) If {a mathematical formula}(viPPvj)∈Γ, it can be proven that {a mathematical formula}bi⊆bj and {a mathematical formula}ci⊆cj by the path-consistency of Γ. We next prove {a mathematical formula}ci≠cj. By {a mathematical formula}IFace(vi)∪EFace(vj)≠Face (last row in Table 7), there exists a face {a mathematical formula}f that is in neither {a mathematical formula}IFace(vi) nor {a mathematical formula}EFace(vj). Therefore {a mathematical formula}f is either in {a mathematical formula}EFace(vi) or {a mathematical formula}PFace(vi). If {a mathematical formula}f∈EFace(vi), then {a mathematical formula}f∩ci=∅. By Lemma 7 and {a mathematical formula}f∉EFace(vj), we also know {a mathematical formula}f∩cj≠∅, and thus {a mathematical formula}ci≠cj. Now suppose {a mathematical formula}f∈PFace(vi). By Lemma 7 we have {a mathematical formula}f⊈ci. Note that {a mathematical formula}f is in either {a mathematical formula}IFace(vj) or {a mathematical formula}PFace(vj). In the first case, we have {a mathematical formula}f⊆cj and thus {a mathematical formula}ci≠cj. In the second case, by the construction of {a mathematical formula}Xj we know that there exists some base region r contained in {a mathematical formula}f that belongs to {a mathematical formula}Xj only. Therefore r is disjoint with {a mathematical formula}ai and hence disjoint with {a mathematical formula}bi. Moreover, r cannot be contained in {a mathematical formula}ci. Otherwise, there must exist some landmark l such that {a mathematical formula}lPPvi and {a mathematical formula}r⊆l. This implies that {a mathematical formula}f∈IFace(l), which further implies {a mathematical formula}f∈IFace(vi), a contradiction. Therefore, we have {a mathematical formula}r⊈ci and {a mathematical formula}r⊆cj and thus {a mathematical formula}ci≠cj. In conclusion, we know {a mathematical formula}ci⊂cj, i.e. {a mathematical formula}ciPPcj.(2) If {a mathematical formula}(viDRvj)∈Γ, we show {a mathematical formula}ci∩cj∘=∅. By construction we have {a mathematical formula}ai∩aj=∅, because {a mathematical formula}Xi∩Xj=∅ unless {a mathematical formula}(viPOvj)∈Γ. Note that {a mathematical formula}(vkPPvi)∈Γ implies {a mathematical formula}(vkDRvj)∈Γ by path-consistency. Therefore, we also have {a mathematical formula}ak∩aj=∅. By the construction of {a mathematical formula}bi we know {a mathematical formula}bi∩aj=∅. Similarly we can prove that {a mathematical formula}bi∩bj=∅. In the same way, it can be further proven that {a mathematical formula}ci∩cj∘=∅, i.e. {a mathematical formula}ciDRcj.(3) If {a mathematical formula}(viPOvj)∈Γ, we first show that {a mathematical formula}ci overlaps {a mathematical formula}cj. By {a mathematical formula}EFace(vi)∪EFace(vj)≠Face (Row 6 in Table 7), there exists a face {a mathematical formula}f such that {a mathematical formula}f∉EFace(vi) and {a mathematical formula}f∉EFace(vj). In other words, we have {a mathematical formula}f∈IFace(vi)∪PFace(vi) and {a mathematical formula}f∈IFace(vj)∪PFace(vj). If {a mathematical formula}f∈PFace(vi)∩PFace(vj), then by the construction of {a mathematical formula}ai and {a mathematical formula}aj there exists a base region r selected from a face in {a mathematical formula}PFace(vi)∩PFace(vj) (not necessarily {a mathematical formula}f) such that {a mathematical formula}r∈Xi∩Xj. Therefore, {a mathematical formula}r⊆ai∩aj and hence {a mathematical formula}r⊆ci∩cj. If {a mathematical formula}f∈IFace(vi)∩IFace(vj), then {a mathematical formula}f is contained in both {a mathematical formula}ci and {a mathematical formula}cj. If {a mathematical formula}f∈IFace(vi)∩PFace(vj), then we know {a mathematical formula}f⊆ci and {a mathematical formula}f∩cj≠∅. Thus {a mathematical formula}ci also overlaps {a mathematical formula}cj. The last case can be proven similarly. Therefore {a mathematical formula}ci overlaps {a mathematical formula}cj. It remains to show that {a mathematical formula}ci and {a mathematical formula}cj are incomparable (i.e., one is not contained in the other). This can be proven in the same way as in the case of {a mathematical formula}(viPOlj)∈Γ. In conclusion, we know {a mathematical formula}ciPOcj.In summary, all the constraints are satisfied and {a mathematical formula}{c1,…,cn} is a solution of Γ.  □
     </paragraph>
    </section>
    <section label="Appendix B">
     Proof of Lemma 6
     <section label="B.1">
      <section-title>
       Necessity
      </section-title>
      <paragraph>
       Suppose {a mathematical formula}{v¯1,v¯2,…,v¯n} is a solution of Γ and {a mathematical formula}v¯i∩Vtx=Si for each i. By the definitions of {a mathematical formula}BVtx(vi) and {a mathematical formula}PVtx(vi), it is straightforward to show that {a mathematical formula}BVtx(vi)⊆Si⊆PVtx(vi). Similarly to the RCC5 case, we can prove that {a mathematical formula}EFace(vi)≠Face for any {a mathematical formula}vi∈V. We first prove the following lemmas.
      </paragraph>
      <paragraph label="Lemma 9">
       Suppose{a mathematical formula}{v¯1,v¯2,…,v¯n}is a solution of Γ, then for any{a mathematical formula}v¯1we have
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}f⊆(v¯i)∘for any face{a mathematical formula}f∈IFace(vi);
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}f∩v¯i=∅for any face{a mathematical formula}f∈EFace(vi);
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}e⊆(v¯i)∘for any edge{a mathematical formula}ein{a mathematical formula}IEdge(vi);
       </list-item>
       <list-item label="(iv)">
        {a mathematical formula}e′∩v¯i=∅for any edge{a mathematical formula}e′in{a mathematical formula}EEdge(vi);
       </list-item>
       <list-item label="(v)">
        {a mathematical formula}v∈(v¯i)∘for any vertex{a mathematical formula}vin{a mathematical formula}IVtx(vi);
       </list-item>
       <list-item label="(vi)">
        {a mathematical formula}v∉v¯ifor any vertex{a mathematical formula}vin{a mathematical formula}EVtx(vi).
       </list-item>
      </list>
      <paragraph label="Proof">
       (v) and (vi) can be proven in the same way.  □
      </paragraph>
      <paragraph label="Proof">
       The other part of the lemma can be proven similarly.  □
      </paragraph>
      <paragraph>
       The necessity of conditions in Table 8 can then be proven straightforwardly.
      </paragraph>
     </section>
     <section label="B.2">
      <section-title>
       Sufficiency
      </section-title>
      <paragraph>
       Suppose {a mathematical formula}(V⊎L,Γ) and {a mathematical formula}Si ({a mathematical formula}i=1,…,n) satisfy the conditions in Lemma 6, we construct a solution {a mathematical formula}{v¯1,…,v¯n} of Γ such that {a mathematical formula}Si=∂v¯i∩Vtx. The construction procedure is similar to that in [19], [22]. For each spatial variable {a mathematical formula}vi, we select a set of small triangles, denoted by {a mathematical formula}Xi, in the following way.
      </paragraph>
      <list>
       <list-item label="•">
        For each face {a mathematical formula}f∈PFace(vi), select a small triangle in {a mathematical formula}f and put it in {a mathematical formula}Xi, see Fig. B.8(a).
       </list-item>
       <list-item label="•">
        For each vertex {a mathematical formula}v∈Si−BVtx(vi)⊆PVtx(vi)−BVtx(vi), by Proposition 10 we know that {a mathematical formula}v is not in {a mathematical formula}BVtx(vi)∪IVtx(vi)∪EVtx(vi). We have that {a mathematical formula}SFace(v)∩PFace(vi)≠∅. Otherwise, {a mathematical formula}SFace(v) is contained in {a mathematical formula}IFace(vi)∪EFace(vi), which implies that {a mathematical formula}v is either in {a mathematical formula}IVtx(vi), or in {a mathematical formula}EVtx(vi), or in {a mathematical formula}BVtx(vi). We select a face {a mathematical formula}f from {a mathematical formula}SFace(v)∩PFace(vi), and select a small triangle in {a mathematical formula}f that contains {a mathematical formula}v. Put the triangle in {a mathematical formula}Xi, see Fig. B.8(b).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}viEClj is in Γ, then by Table 8 we have either {a mathematical formula}PEdge(vi)∩BEdge(lj)≠∅ or {a mathematical formula}Si∩BVtx(lj)≠∅ (i.e. (25)). If {a mathematical formula}Si∩BVtx(lj)≠∅, do nothing. Otherwise, we select an edge {a mathematical formula}e from {a mathematical formula}PEdge(vi)∩BEdge(lj). Let {a mathematical formula}f and {a mathematical formula}f′ be the two incident faces of {a mathematical formula}e such that {a mathematical formula}f∈IFace(lj) and {a mathematical formula}f′∈EFace(lj). By definition, we know {a mathematical formula}f∈EFace(vi). We note that {a mathematical formula}f′ cannot be in {a mathematical formula}EFace(vi). This is because, otherwise, we have {a mathematical formula}SFace(e)={f,f′}⊆EFace(vi) and hence {a mathematical formula}e∈EEdge(vi), which contradicts the assumption that {a mathematical formula}e∈PEdge(vi). If {a mathematical formula}f′∈IFace(vi), do nothing. If {a mathematical formula}f′∈PFace(vi), select a triangle in face {a mathematical formula}f′ with one edge on {a mathematical formula}e and put it in {a mathematical formula}Xi, see Fig. B.8(c).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}viTPPlj is in Γ, then by Table 8 we also have {a mathematical formula}PEdge(vi)∩BEdge(lj)≠∅ or {a mathematical formula}Si∩BVtx(lj)≠∅ (i.e. (25)). If {a mathematical formula}Si∩BVtx(lj)≠∅, do nothing. Otherwise, select an edge {a mathematical formula}e from {a mathematical formula}PEdge(vi)∩BEdge(lj). Let {a mathematical formula}f and {a mathematical formula}f′ be the two incident faces of {a mathematical formula}e such that {a mathematical formula}f∈IFace(lj) and {a mathematical formula}f′∈EFace(lj). By definition, we know {a mathematical formula}f′∈EFace(vi). Similar to the case of {a mathematical formula}viEClj, {a mathematical formula}f cannot be in {a mathematical formula}EFace(vi). If {a mathematical formula}f∈IFace(vi), do nothing. If {a mathematical formula}f∈PFace(vi), select a triangle in face {a mathematical formula}f with one edge on {a mathematical formula}e and put it in {a mathematical formula}Xi.
       </list-item>
       <list-item label="•">
        If {a mathematical formula}viECvj is in Γ, then by Table 8 we have {a mathematical formula}PFace(vi)∩PFace(vj)≠∅, or {a mathematical formula}PEdge(vi)∩PEdge(vj)≠∅, or {a mathematical formula}Si∩Sj≠∅. If {a mathematical formula}Si∩Sj≠∅, do nothing. If {a mathematical formula}Si∩Sj=∅ and {a mathematical formula}PFace(vi)∩PFace(vj)≠∅, select a face {a mathematical formula}f∈PFace(vi)∩PFace(vj) and two externally connected triangles in {a mathematical formula}f. Put one triangle in {a mathematical formula}Xi and put the other in {a mathematical formula}Xj, see Fig. B.8(d). If {a mathematical formula}Si∩Sj=∅, {a mathematical formula}PFace(vi)∩PFace(vj)=∅, and {a mathematical formula}PEdge(vi)∩PEdge(vj)≠∅, then select edge {a mathematical formula}e∈PEdge(vi)∩PEdge(vj). Suppose {a mathematical formula}f and {a mathematical formula}f′ are the two incident faces of {a mathematical formula}e. We have four subcases depending on whether {a mathematical formula}e is in {a mathematical formula}BEdge(vi) and {a mathematical formula}BEdge(vj).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}viTPPvj is in Γ, then by Table 8 we also have {a mathematical formula}PFace(vi)∩PFace(vj)≠∅, or {a mathematical formula}PEdge(vi)∩PEdge(vj)≠∅, or {a mathematical formula}Si∩Sj≠∅. If {a mathematical formula}Si∩Sj≠∅, then do nothing. If {a mathematical formula}Si∩Sj=∅ and {a mathematical formula}PFace(vi)∩PFace(vj)≠∅, then select a face {a mathematical formula}f∈PFace(vi)∩PFace(vj) and one triangle in {a mathematical formula}f. Put the triangle in both {a mathematical formula}Xi and {a mathematical formula}Xj. If {a mathematical formula}Si∩Sj=∅, {a mathematical formula}PFace(vi)∩PFace(vj)=∅, and {a mathematical formula}PEdge(vi)∩PEdge(vj)≠∅, then select an edge {a mathematical formula}e∈PEdge(vi)∩PEdge(vj). Suppose {a mathematical formula}f and {a mathematical formula}f′ are the two incident faces of {a mathematical formula}e. At least one of {a mathematical formula}f and {a mathematical formula}f′ is not in {a mathematical formula}EFace(vi) (otherwise {a mathematical formula}e is in {a mathematical formula}EEdge(vi)). W.l.o.g., suppose {a mathematical formula}f∉EFace(vi). If {a mathematical formula}f∈IFace(vi), then do nothing. If {a mathematical formula}f∈PFace(vi), we select a triangle in {a mathematical formula}f with one edge on {a mathematical formula}e and put it in {a mathematical formula}Xi.
       </list-item>
       <list-item label="•">
        If {a mathematical formula}viPOvj is in Γ, then by Table 8 we have {a mathematical formula}EFace(vi)∪EFace(vj)≠Face. There exists a face {a mathematical formula}f in {a mathematical formula}(IFace(vi)∪PFace(vi))∩(IFace(vj)∪PFace(vj)). If {a mathematical formula}f is in {a mathematical formula}PFace(vi)∩PFace(vj), then select a triangle in face {a mathematical formula}f and put it in both {a mathematical formula}Xi and {a mathematical formula}Xj. Otherwise, we do nothing.
       </list-item>
      </list>
      <paragraph>
       We assume that all the triangles are pairwise disjoint and are sufficiently small such that the union of all the triangles does not entirely occupy any face or any edge. Now {a mathematical formula}Xi contains all the triangles we need for spatial variable {a mathematical formula}vi. For clarity, we now consider each face as its closure, and we use {a mathematical formula}(vjPPvi)∈Γ to denote that {a mathematical formula}vjTPPvi or {a mathematical formula}vjNTPPvi is a constraint in Γ. Define {a mathematical formula}ai and {a mathematical formula}bi as follows:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       We assert that {a mathematical formula}{b1,b2,…,bn} satisfies all the constraints in Γ except that some {a mathematical formula}NTPP constraints may be realised as {a mathematical formula}TPP. This assertion can be proven in the same way as in the proof of Lemma 8.
      </paragraph>
      <paragraph>
       Let X be the union of all {a mathematical formula}Xi, i.e. X is the set of all the triangles selected for spatial variables. To cope with the {a mathematical formula}NTPP constraints, we introduce the {a mathematical formula}expand function from {a mathematical formula}(X∪Face)×{1,2,…,n} to regions in the plane such that for any {a mathematical formula}x,x′∈X∪Face,
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}expand(x,1)=x.
       </list-item>
       <list-item label="•">
        {a mathematical formula}expand(x,i)NTPPexpand(x,i+1) for {a mathematical formula}i=1,2,…,n−1.
       </list-item>
       <list-item label="•">
        {a mathematical formula}expand(x,i)DCexpand(x′,i′) if {a mathematical formula}xDCx′, for {a mathematical formula}i,i′=1,2,…,n.
       </list-item>
       <list-item label="•">
        {a mathematical formula}expand(x,i)POexpand(x′,i′) if {a mathematical formula}xECx′, for {a mathematical formula}i,i′=1,2,…,n.
       </list-item>
      </list>
      <paragraph>
       That is to say, {a mathematical formula}expand(x,i) ({a mathematical formula}i=1,2,…,n) is a series of nested regions among which x is the innermost core. Meanwhile, {a mathematical formula}expand(x,i) should be small enough to not touch or overlap any other regions or any other {a mathematical formula}expand(x′,i′) whenever possible. Fig. B.9 provides illustrations for {a mathematical formula}expand(x,1).
      </paragraph>
      <paragraph>
       We can extend the domain of the function {a mathematical formula}expand to include all {a mathematical formula}bi defined above and all landmarks by{a mathematical formula} where {a mathematical formula}y∈{b1,…,bn,l1,…,lm} and {a mathematical formula}i=1,2,…,n.
      </paragraph>
      <paragraph>
       Define a function {a mathematical formula}dNTPP:V×(V∪L)→N, such that {a mathematical formula}dNTPP(vi,w) is the length of the longest {a mathematical formula}NTPPi chain from {a mathematical formula}vi to w, where w is either variable {a mathematical formula}vj or landmark {a mathematical formula}lj. Furthermore, define{a mathematical formula}
      </paragraph>
      <paragraph>
       It can be proven that {a mathematical formula}{c1,…,cn} is a solution of Γ such that {a mathematical formula}Si=∂ci∩Vtx for {a mathematical formula}i=1,2,…,n in the same way as in [19], [22]. We omit the details here.
      </paragraph>
     </section>
    </section>
    <section label="Appendix C">
     Proof sketch of Theorem 12
     <paragraph>
      We need to adjust the construction given in the sufficiency part to cope with the strong connectedness. The only differences from the standard RCC8 interpretation are: (i) we assume {a mathematical formula}Si=∅ for each variable {a mathematical formula}vi; (ii) although the requirements for {a mathematical formula}expand(⋅,⋅) still apply, we need to modify the construction of this function to cater for the change in the interpretations of RCC8 relations. If x is a face in {a mathematical formula}Face, or a triangle in X on some vertex {a mathematical formula}v, {a mathematical formula}expand(x,1) should be modified as shown in Figs. C.10(a) and C.10(c) respectively, which can be contrasted with Figs. B.9(a) and B.9(c). Note that in Fig. C.10(c), it holds that {a mathematical formula}xDCf1 because their intersection is a point (not a curve). Therefore, {a mathematical formula}expand(x,1) is supposed to be disjoint with {a mathematical formula}f1 (under the strong connectedness interpretation of RCC8) due to the requirement of {a mathematical formula}expand(⋅,⋅). The case in Fig. C.10(a) is similar: the boundary of the expanded face does not intersect with any face which is disjoint with the original face.
     </paragraph>
     <paragraph>
      All the remaining parts of the construction, including the selection of triangles (note that {a mathematical formula}Si=∅ here), definitions of {a mathematical formula}ai, {a mathematical formula}bi, and verification of {a mathematical formula}bi as a solution of Γ, are completely the same as in the standard interpretation of RCC8 relations.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>