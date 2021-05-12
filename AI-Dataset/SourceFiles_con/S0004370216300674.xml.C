<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A note on the complexity of the causal ordering problem.
   </title>
   <abstract>
    In this note we provide a concise report on the complexity of the causal ordering problem, originally introduced by Simon to reason about causal dependencies implicit in systems of mathematical equations. We show that Simon's classical algorithm to infer causal ordering is NP-Hard—an intractability previously guessed but never proven. We present then a detailed account based on Nayak's suggested algorithmic solution (the best available), which is dominated by computing transitive closure—bounded in time by O(|V|⋅|S|), where S(E,V) is the input system structure composed of a set E of equations over a set V of variables with number of variable appearances (density) |S|. We also comment on the potential of causal ordering for emerging applications in large-scale hypothesis management and analytics.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The causal ordering problem has long been introduced by Simon as a technique to infer the causal dependencies implicit in a deterministic mathematical model [1]. For instance, let {a mathematical formula}f1(x1) and {a mathematical formula}f2(x1,x2) be two equations defined over variables {a mathematical formula}x1,x2. Then the causal ordering problem is to infer all existing causal dependencies, in this case the only one is {a mathematical formula}(x1,x2), read ‘{a mathematical formula}x2 causally depends on {a mathematical formula}x1.’ It is obtained by first matching each equation to a variable that appears in it, e.g., {a mathematical formula}f2↦x2. Intuitively, this means that {a mathematical formula}f2 is to be assigned to compute the value of {a mathematical formula}x2—using the value of {a mathematical formula}x1, which establishes a direct causal dependency between these two variables. Indirect dependencies may then arise and can be computed, which is specially useful when the system of equations is very large.
     </paragraph>
     <paragraph>
      Causal ordering inference can then support users with uncertainty management, say, towards the discovery of what is wrong with a model for enabling efficient and effective modeling intervention. If multiple values of {a mathematical formula}x1 are admissible for a modeler, then as a user of the causal ordering machinery she has support to track their influence on the values of {a mathematical formula}x2. One major application for that is probabilistic database design [2].
     </paragraph>
     <paragraph>
      Back in the 1950s, Simon was motivated by studies in econometrics and not very concerned with the algorithmic aspects of the Causal Ordering Problem (COP). Yet his vision on COP and its relevance turned out to be influential in the artificial intelligence literature. In a more recent study, Dash and Druzdzel revisit and motivate it in light of modern applications [3]. They show that Simon's original algorithm, henceforth the Causal Ordering Algorithm (COA), is correct in the sense that any valid causal ordering that can be extracted from a self-contained (well-posed) system of equations must be compatible with the one that is output by COA [3]. Their aim has also been (sic.) to validate decades of research that has shown the causal ordering to provide a powerful tool for operating on models. In addition to the result on the correctness of COA, their note also provides a convenient survey of related work that connects to Simon's early vision on causal reasoning.
     </paragraph>
     <paragraph>
      However, Simon's formulation of COP into COA—originally in [1], and reproduced in [3], turns out to be intractable. There is a need to distinguish Simon's COA from COP itself. The former still seems to be the main entry point to the latter in the specialized literature. In fact, there is a lack of a review on the computational properties of COA—and as we show in this note, it tries to address an NP-Hard problem as one of its steps. The interested reader who needs an efficient algorithmic approach to address COP in a real, large-scale application can only scarcely find some comments spread through Nayak [4, pp. 287–291], and then Iwasaki and Simon [5, p. 149] and Pearl [6, p. 226] both pointing to the former. Regarding Simon's COA itself, the classical approach to COP, it is only Nayak who suggests in words that (sic.) ‘[it] is a worst-case exponential time algorithm’ [7, p. 37]. We discuss this ambiguity that exists in the most up-to-date literature shortly in §1.2.
     </paragraph>
     <paragraph>
      COP is significant also in view of emerging applications in large-scale hypothesis management and analytics [2]. The modeling of physical and socio-economical systems as a set of mathematical equations is a traditional approach in science and engineering and a very large bulk of models exist which are ever more available in machine-readable format. Simon's early vision on the automatic extraction of the “causal mechanisms” implicit in (large-scale) models for the sake of informed intervention finds nowadays new applications in the context of open simulation laboratories [8], large-scale model management [9] and online, shared model repositories [10], [11], [12].
     </paragraph>
     <paragraph>
      In this paper we review the causal ordering problem (§2). Our core contributions are (§3) to originally show that COA aims at addressing an NP-Hard problem, confirming Nayak's earlier intuition; and then (§4) to organize into a concise yet complete note his hints to solve COP in polynomial time.
     </paragraph>
     <section label="1.1">
      <section-title>
       Informal preliminaries
      </section-title>
      <paragraph>
       Given a system of mathematical equations involving a set of variables, the causal ordering problem consists in detecting the hidden asymmetry between variables. As an intermediate step towards it, one needs to establish a one-to-one mapping between equations and variables [1].
      </paragraph>
      <paragraph>
       For instance, Einstein's famous equation {a mathematical formula}E=mc2 states the equivalence of mass and energy, summarizing (in its scalar version) a theory that can be imposed two different asymmetries for different applications. Say, given a fixed amount of mass {a mathematical formula}m=m0 (and recalling that c is a constant), find the particle's relativistic rest energy E; or rather, given the particle's rest energy, find its mass or potential for nuclear fission. That is, the causal ordering depends on what variables are set as input and which ones are “influenced” by them. Suppose there is uncertainty, say, a user considers two values to set the mass, {a mathematical formula}m=m0 or {a mathematical formula}m=m0′. Then this uncertainty will flow through the causal ordering and affect all variables that are dependent on it (energy E).
      </paragraph>
      <paragraph>
       For really large systems, having structures say in the order of one million equations [13], the causal ordering problem is critical to provide more specific accountability on the accuracy of the system—viz., what specific variables and subsystems account for possibly inaccurate outcomes. This is key for managing and tracking the uncertainty of alternative modeling variations systematically [8], [13].
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       COA. Dash and Druzdzel [3] provide a high-level description of how Simon's COA [1] proceeds to discover the causal dependencies implicit in a structure. It returns a ‘partial’ causal mapping: from partitions on the set of equations to same-cardinality partitions on the set of variables—a ‘total’ causal mapping would instead map every equation to exactly one variable.
      </paragraph>
      <paragraph>
       They show then that any valid total causal mapping produced over a structure must be consistent with COA's partial causal mapping. Nonetheless, no observation at all is made regarding COA's computational properties in [3], leaving in the most up-to-date literature an impression that Simon's COA is the way to go for COP. In this note we show that Simon's COA tries to address an NP-Hard problem in one of its steps, and then clearly recommend Nayak's efficient approach to COP as a fix to COA.
      </paragraph>
      <paragraph>
       COP. Inspired by Serrano and Gossard's work on constraint modeling and reasoning [14], Nayak describes an approach that is provably efficient to process the causal ordering: extract any valid total causal mapping and then compute the transitive closure of the direct causal dependencies, viz, the causal ordering. Nayak's is a provably correct approach to COP, as all valid ‘total’ causal mappings must have the same causal ordering.
      </paragraph>
      <paragraph>
       In this note we arrange those insights into a concise yet detailed recipe that can be followed straightforwardly to solve COP efficiently.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      The causal ordering problem
     </section-title>
     <paragraph>
      We start with some preliminaries on notation and basic concepts to eventually state COP formally.
     </paragraph>
     <paragraph>
      For an equation {a mathematical formula}f(x1,x2,…,xℓ)=0, we will write {a mathematical formula}Vars(f)≜{x1,x2,…,xℓ} to denote the set of variables that appear in it.
     </paragraph>
     <paragraph label="Definition 1">
      A structure is a pair {a mathematical formula}S(E,V), where {a mathematical formula}E is a set of equations over a set {a mathematical formula}V of variables, {a mathematical formula}V≜⋃f∈EVars(f), such that:
     </paragraph>
     <list>
      <list-item label="(a)">
       In any subset {a mathematical formula}E′⊆E of {a mathematical formula}k&gt;0 equations of the structure, at least k different variables appear, i.e., {a mathematical formula}|E′|≤|V′|;
      </list-item>
      <list-item label="(b)">
       In any subset of {a mathematical formula}k&gt;0 equations in which r variables appear, {a mathematical formula}k≤r, if the values of any {a mathematical formula}(r−k) variables are chosen arbitrarily, then the values of the remaining k variables can be determined uniquely—finding these unique values is a matter of solving the equations.
      </list-item>
     </list>
     <paragraph>
      Note in Definition 1 that structures are composed of equations, and variables are only part of them indirectly as part of equations. Accordingly, set inclusion and all set operations such as union, intersection and difference are computed w.r.t. the equations. That is, if {a mathematical formula}S(E,V) and {a mathematical formula}S′(E′,V′) are structures, then we write {a mathematical formula}S′⊂S when {a mathematical formula}E′⊂E. An additional operation for ‘variables elimination’ shall be used. We write {a mathematical formula}T:=S÷S′, to denote a structure {a mathematical formula}T resulting from both (i) removing equations {a mathematical formula}E′ from {a mathematical formula}E, and (ii) enforcing elimination of variables {a mathematical formula}V′=⋃f∈E′Vars(f) from {a mathematical formula}E∖E′.
     </paragraph>
     <paragraph label="Definition 2">
      Let {a mathematical formula}S(E,V) be a structure. We say that {a mathematical formula}S is self-contained or complete if {a mathematical formula}|E|=|V|.
     </paragraph>
     <paragraph>
      In short, COP will be concerned with systems of equations that are ‘structural’ (Definition 1) and ‘complete’ (Definition 2), viz., that have as many equations as variables and no subset of equations has fewer variables than equations.{sup:1}
     </paragraph>
     <paragraph>
      Now Definition 3 introduces a data structure that is an intermediate product towards addressing COP. We shall state COP formally in the sequel.
     </paragraph>
     <paragraph label="Definition 3">
      Let {a mathematical formula}S(E,V) be a complete structure. Then a total causal mapping over {a mathematical formula}S is a bijection {a mathematical formula}φ:E→V such that, for all {a mathematical formula}f∈E, if {a mathematical formula}φ(f)=x then {a mathematical formula}x∈Vars(f).
     </paragraph>
     <paragraph>
      Note that such total causal mapping φ induces a set {a mathematical formula}Cφ of direct causal dependencies (see Eq. (1)), which shall give us the causal dependencies (Definition 4).{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 4">
      Let {a mathematical formula}S(E,V) be a structure with variables {a mathematical formula}xa,xb∈V, and φ a total causal mapping over {a mathematical formula}S inducing set of direct causal dependencies {a mathematical formula}Cφ and indirectly a transitive closure {a mathematical formula}Cφ+. We say that {a mathematical formula}(xa,xb) is a direct causal dependency in {a mathematical formula}S if {a mathematical formula}(xa,xb)∈Cφ, and that {a mathematical formula}(xa,xb) is a causal dependency in {a mathematical formula}S if {a mathematical formula}(xa,xb)∈Cφ+.
     </paragraph>
     <paragraph>
      In other words, {a mathematical formula}(xa,xb) is in {a mathematical formula}Cφ iff {a mathematical formula}xb direct and causally depends on {a mathematical formula}xa, given the causal asymmetries induced by φ. Then by transitive reasoning on {a mathematical formula}Cφ we shall be able to infer the transitive closure {a mathematical formula}Cφ+, which is the causal ordering. Now we can state COP more formally as Problem 1.
     </paragraph>
     <paragraph label="Problem 1">
      COPGiven a complete structure {a mathematical formula}S(E,V), find a total causal mapping φ over {a mathematical formula}S and derive a set {a mathematical formula}Cφ+ of causal dependencies induced by it.
     </paragraph>
     <paragraph>
      In the sequel we shall see two different algorithmic approaches to COP (Problem 1). First, the classical approach informally described by Simon in the 1950s [1], and reproduced recently in [3]; and then Nayak's one proposed in the 1990s [4]. We shall present the algorithms and analyze their corresponding complexities.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Simon's causal ordering algorithm and its complexity
     </section-title>
     <paragraph>
      We introduce now additional concepts that are specific to Simon's COA.
     </paragraph>
     <paragraph label="Definition 5">
      Let {a mathematical formula}S be a structure. We say that {a mathematical formula}S is minimal if it is complete and there is no complete substructure {a mathematical formula}S′⊂S.
     </paragraph>
     <paragraph label="Example 1">
      Consider structure {a mathematical formula}S(E,V), where {a mathematical formula}E={f1(x1),f2(x2),f3(x3),f4(x1,x2,x3,x4,x5),f5(x1,x3,x4,x5),f6(x4,x6),f7(x5,x7)}. Note that {a mathematical formula}S is complete, as {a mathematical formula}|E|=|V|=7, but not minimal. There are exactly three minimal substructures {a mathematical formula}S1,S2,S3⊂S, whose sets of equations are {a mathematical formula}E1={f1(x1)},E2={f2(x2)},E3={f3(x3)}.  □
     </paragraph>
     <paragraph>
      Now Lemma 1 and Proposition 1 are stated to back up a ‘disjointness’ assumption that is made by COA upon minimal structures (Definition 5). The proof we present here for Proposition 1 is a conveniently derived alternative to Simon's own proof to his original ‘Theorem 3.2’ [1, p. 59].
     </paragraph>
     <paragraph label="Lemma 1">
      Let{a mathematical formula}S1(E1,V1)and{a mathematical formula}S2(E2,V2)be structures. If{a mathematical formula}V1∩V2=∅then{a mathematical formula}S1∩S2=∅(i.e.,{a mathematical formula}E1∩E2=∅). That is, disjointness of variables is strong enough to warrant disjointness of equations.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}V1∩V2=∅. Now by contradiction assume {a mathematical formula}S1∩S2≠∅, then there must be at least one shared equation {a mathematical formula}f∈E1,E2. Since both {a mathematical formula}S1,S2 are structures, by Definition 1 we know that {a mathematical formula}|Vars(f)|≥1 and {a mathematical formula}Vars(f)⊆V1∩V2. Yet {a mathematical formula}V1∩V2=∅. ↯. Therefore {a mathematical formula}V1∩V2=∅ implies {a mathematical formula}S1∩S2=∅.  □
     </paragraph>
     <paragraph label="Definition 6">
      Let {a mathematical formula}S1(E1,V1) and {a mathematical formula}S2(E2,V2) be structures. Then we say that they are disjoint if {a mathematical formula}V1∩V2=∅.
     </paragraph>
     <paragraph label="Proposition 1">
      Let{a mathematical formula}Sbe a complete structure. If{a mathematical formula}S1,S2⊂Sare any different minimal substructures of{a mathematical formula}S, then they are disjoint.
     </paragraph>
     <paragraph label="Proof">
      We show the statement by case analysis and then contradiction out of Definition 1, Definition 2 and Definition 5, Definition 6. See Appendix A.  □
     </paragraph>
     <paragraph>
      Simon's COA is also based on a data structure introduced in Definition 7.
     </paragraph>
     <paragraph label="Definition 7">
      The structure matrix{a mathematical formula}AS of a structure {a mathematical formula}S(E,V), with {a mathematical formula}f1,f2,…,fn∈E and {a mathematical formula}x1,x2,…,xm∈V, is a {a mathematical formula}|E|×|V| matrix of 1's and 0's in which entry {a mathematical formula}aij is non-zero if variable {a mathematical formula}xj appears in equation {a mathematical formula}fi, and zero otherwise.
     </paragraph>
     <paragraph>
      Elementary row operations on the structure matrix may hinder the structure's causal ordering and then are not valid in general [1]. This also emphasizes that the problem of causal ordering is not about solving the system of equations of a structure, but identifying its hidden asymmetries.
     </paragraph>
     <paragraph label="Definition 8">
      Simon's COA also brings forth the concept of ‘strongly coupled’ variables (Definition 8). Intuitively, these are variables whose values can only be determined simultaneously. Let {a mathematical formula}S(E,V) be a structure with variables {a mathematical formula}x1,x2∈V. We say that {a mathematical formula}x1,x2 are strongly coupled if {a mathematical formula}S is minimal.
     </paragraph>
     <section label="3.1">
      <section-title>
       Simon's causal ordering algorithm
      </section-title>
      <paragraph>
       Simon has described his Causal Ordering Algorithm (COA) only informally at a high level of abstraction [1]. It is given a complete structure {a mathematical formula}S(E,V) and computes a causal mapping φ. The causal ordering itself is to be obtained as a post-processing (transitive closure) out of the causal mapping φ and its induced set {a mathematical formula}Cφ of direct causal dependencies. Example 1 (continued) warms up for Simon's algorithm.
      </paragraph>
      <paragraph label="Example 1">
       (continued) Fig. 1a shows the matrix of the structure {a mathematical formula}S given above in this example. By eliminating the variables identified with the minimal substructures {a mathematical formula}S1,S2,S3⊂S, a smaller structure {a mathematical formula}T is derived to be input at the next recursive step (see Fig. 1b). This is the main insight of Simon's to arrive at his recursive causal ordering algorithm, as described next.  □
      </paragraph>
      <paragraph>
       Algorithm 1 describes the variant of Simon's original description that returns a ‘total’ causal mapping (satisfies Definition 3).{sup:2} We refer to its core procedure as RTCM (recursive total causal mapping). It comprises the actual source of intractability in Simon's original description, while lines 3–7 of the COA procedure were not described by himself but only considered as matter of a post-processing. We illustrate RTCM through Example 1 and Fig. 1.
      </paragraph>
      <paragraph label="Example 1">
       (continued) Let {a mathematical formula}T=S÷(S1∪S2∪S3) be the structure returned by COA's first recursive step {a mathematical formula}k=0 for this example. Then a valid total causal mapping that can be returned at {a mathematical formula}k=1 (see Fig. 1b) is {a mathematical formula}COA(T)={〈f4,x4〉,〈f5,x5〉}. Since {a mathematical formula}x4 and {a mathematical formula}x5 are strongly coupled (Definition 8), COA maps them arbitrarily—e.g., it could be {a mathematical formula}f4↦x5,f5↦x4 instead. Such total causal mapping φ renders a cycle in the directed causal graph {a mathematical formula}Gφ induced by φ (see Fig. 1c), which might not be desirable for some applications.  □
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Hardness of Simon's recursive COA
      </section-title>
      <paragraph>
       First of all, we state a decision problem associated with finding the minimal structures in a given structure (line 3 of Simon's RTCM procedure in Algorithm 1). For short, we shall refer to this problem as the Complete Substructure Decision Problem (CSDP).{a mathematical formula}
      </paragraph>
      <paragraph>
       In this section we carry out an original study on CSDP and show that it is NP-Complete. We consider a basic observation by Nayak [4] apud. [14], that there is a correspondence between Simon's structures and bipartite graphs. A graph is said bipartite if its vertices can be divided into two disjoint sets {a mathematical formula}V1 and {a mathematical formula}V2 and every edge connects a vertex in {a mathematical formula}V1 to one in {a mathematical formula}V2[15]. Moreover it is said to be ℓ-balanced if {a mathematical formula}|V1|=|V2|=ℓ, and is said to be connected if {a mathematical formula}deg(w)≥1 for all {a mathematical formula}w∈V1∪V2. Definition 9 introduces the mentioned correspondence and provides us some shorthand notation.
      </paragraph>
      <paragraph label="Definition 9">
       Let {a mathematical formula}S(E,V) be a structure, and {a mathematical formula}G=(V1∪V2,E) be a bipartite graph where {a mathematical formula}V1↦E and {a mathematical formula}V2↦V, and {a mathematical formula}E↦S so that an edge {a mathematical formula}(f,x)∈E if and only if we have {a mathematical formula}x∈Vars(f). We say that G is the bipartite graph that corresponds to structure {a mathematical formula}S, and for short write {a mathematical formula}G∼S.
      </paragraph>
      <paragraph>
       Fig. 2 shows the bipartite graph {a mathematical formula}G∼S, where {a mathematical formula}S is the initial structure given in Example 1.
      </paragraph>
      <paragraph>
       Definition 10 introduces a bipartite graph property of our interest, and then Lemma 2 originally establishes an equivalence of two problems: searching for complete substructures {a mathematical formula}S′⊂S and searching for specific bipartite subgraphs {a mathematical formula}G′⊂G.
      </paragraph>
      <paragraph label="Definition 10">
       Let {a mathematical formula}G(V1∪V2,E) be a bipartite graph. We say that G is structural if, for every {a mathematical formula}V1′⊆V1, there is a connected bipartite subgraph {a mathematical formula}G′(V1′∪V2′,E′) with {a mathematical formula}|V1′|≤|V2′|. (Note resemblance with Definition 1.)
      </paragraph>
      <paragraph label="Lemma 2">
       Let{a mathematical formula}S(V,E)be a complete structure with{a mathematical formula}|E|=|V|=mand{a mathematical formula}1≤ℓ&lt;mprovide an instance of CSDP. Let also{a mathematical formula}G(V1∪V2,E)be a bipartite graph{a mathematical formula}G∼S. Then{a mathematical formula}Shas a substructure{a mathematical formula}S′that gives a yes answer to CSDP if and only if G has a bipartite subgraph{a mathematical formula}G′(V1′∪V2′,E′)such that{a mathematical formula}G′∼S′and all of these conditions hold:
      </paragraph>
      <list>
       <list-item label="(i)">
        Bipartite subgraph{a mathematical formula}G′is structural;
       </list-item>
       <list-item label="(ii)">
        For every{a mathematical formula}f∈V1′, there is an edge{a mathematical formula}(f,x)∈Eonly if{a mathematical formula}x∈V2′;
       </list-item>
       <list-item label="(iii)">
        Bipartite subgraph{a mathematical formula}G′is ℓ-balanced, that is,{a mathematical formula}|V1′|=|V2′|=ℓ.
       </list-item>
      </list>
      <paragraph label="Proof">
       We establish conditions (i–iii) as the bipartite subgraph properties that correspond to a yes answer to CSDP. See Appendix B.  □
      </paragraph>
      <paragraph>
       We now reach the key property in our argument to show COA's hardness. A biclique (or complete bipartite graph) is a bipartite graph {a mathematical formula}G=(V1∪V2,E) such that for every two vertices {a mathematical formula}u∈V1, {a mathematical formula}v∈V2, we have {a mathematical formula}(u,v)∈E[16]. Thus the number of edges in a biclique is {a mathematical formula}|E|=|V1|⋅|V2|. A biclique with partitions of size {a mathematical formula}|V1|=m and {a mathematical formula}|V2|=n is denoted {a mathematical formula}Km,n. For instance, the bipartite graph G shown in Fig. 2 has a {a mathematical formula}K2,2 biclique, viz., {a mathematical formula}G′(V1′∪V2′,E′), where {a mathematical formula}V1′={f4,f5}, {a mathematical formula}V2′={x4,x5} and {a mathematical formula}E′={(f4,x4),(f4,x5),(f5,x4),(f5,x5)}. Let us now consider Example 2.
      </paragraph>
      <paragraph label="Example 2">
       We introduce another structure {a mathematical formula}S, whose structure matrix is shown in Fig. 3a together with the bipartite graph {a mathematical formula}G∼S in Fig. 3b. Let us consider subgraph {a mathematical formula}G′(V1′∪V2′,E′) in G that has {a mathematical formula}V1′={f1,f2,f3} and {a mathematical formula}V2′={x1,x2,x3}. Observe that we have {a mathematical formula}G′∼S′, where {a mathematical formula}S′⊂S is the complete substructure represented by the shaded {a mathematical formula}3×3 matrix in Fig. 3a.Note also that such bipartite subgraph {a mathematical formula}G′ satisfies the conditions (i–iii) of Lemma 2 and in fact {a mathematical formula}S′ is a complete substructure in {a mathematical formula}S. Clearly, {a mathematical formula}G′∼S′ is not a biclique, as it is not the case that {a mathematical formula}deg(w)=3 for all {a mathematical formula}w∈V1′∪V2′. So there is no obvious connection between identifying complete substructures in a structure and bicliques in a bipartite graph.  □
      </paragraph>
      <paragraph>
       The key insight to COA's hardness comes as follows—consider Example 2 and Fig. 3 for illustration. Recall from Lemma 2(ii) that, if we had an edge, say, connecting {a mathematical formula}(f1,x4)∈E, then by Definition 1 the substructure {a mathematical formula}S′(E′,V′) with {a mathematical formula}E′={f1,f2,f3} would have {a mathematical formula}V′=⋃f∈E′Vars(f)={x1,x2,x3,x4} instead. That is, it would no more be a complete substructure. In fact, verifying such a negative property (Lemma 2(ii)) in structural bipartite graphs translates onto a neat positive property (biclique) in the bipartite complement of bipartite graph G.
      </paragraph>
      <paragraph>
       The bipartite complement of a bipartite graph {a mathematical formula}G(V1∪V2,E) is a bipartite graph {a mathematical formula}Gc(V1∪V2,Ec) where an edge {a mathematical formula}(u,v)∈Ec iff {a mathematical formula}(u,v)∉E for every {a mathematical formula}u∈V1 and {a mathematical formula}v∈V2. Given a bipartite graph {a mathematical formula}G(V1∪V2,E), it is easy to see that we can render {a mathematical formula}Gc(V1∪V2,Ec) in polynomial time—consider, e.g., the biadjacency matrix of G (viz., the structure matrix in Fig. 3a), and run a full scan on it to switch the boolean value of each entry in time {a mathematical formula}O(|V1|⋅|V2|). Moreover, this operation is clearly invertible, as there is a one-to-one correspondence between G and {a mathematical formula}Gc.
      </paragraph>
      <paragraph>
       Fig. 3c shows the bipartite complement graph {a mathematical formula}Gc of the bipartite graph G from Fig. 3b. Note that {a mathematical formula}Gc has a biclique {a mathematical formula}K3,1 with its vertices shaded in dark grey. To emphasize the point, if we had an edge {a mathematical formula}(f1,x4)∈E (see Fig. 3b), then such a biclique {a mathematical formula}K3,1 would not exist in {a mathematical formula}Gc (see Fig. 3c). We would have a {a mathematical formula}K2,1 biclique instead with all edges in {a mathematical formula}{f2,f3}×{x4}, but note that {a mathematical formula}2+1=3 does not sum up to {a mathematical formula}|V1|=|V2|=m=4.
      </paragraph>
      <paragraph label="Proof">
       We can now establish the result we seek. We introduce below the Exact Node Cardinality Decision Problem (ENCD), which is a variant of biclique problem in bipartite graphs that is known to be NP-Complete [17, p. 393]. Theorem 1 establishes its connection with CSDP.{a mathematical formula}CSDP is NP-Complete.We shall construct an instance of ENCD and describe its polynomial-time reduction to an instance of CSDP. We refer to Definition 10 and Lemma 2 and present the argument in detail in Appendix C.  □
      </paragraph>
      <paragraph label="Corollary 1">
       Finally, we formulate an optimization problem associated with CSDP. We refer to it as the Minimal Substructures Problem (MSP). Corollary 1 then finally establishes the hardness of Simon's COA based on RTCM.{a mathematical formula}Let{a mathematical formula}Sbe a complete structure. The extraction of its causal ordering by Simon's{a mathematical formula}COA(S)through its RTCM procedure requires solving MSP, which is NP-Hard.
      </paragraph>
      <paragraph label="Proof">
       Clearly, MSP is the optimization problem that needs to be solved at each recursive step k of Simon's RTCM procedure—Algorithm 1, line 3, “find all minimal substructures {a mathematical formula}S′⊆S.” But MSP is clearly an optimization problem that subsumes CSDP, which we know from Theorem 1 that is NP-Complete by a reduction from ENCD.In fact, an instance of {a mathematical formula}ENCD′ (as an optimization variant of ENCD) that can be reduced to MSP is as follows: given a bipartite graph {a mathematical formula}G(V1∪V2,E) that bears the complement structural property (cf. Theorem 1) and has {a mathematical formula}|V1|=|V2|=m, list all bicliques {a mathematical formula}Kℓ,m−ℓ contained in G where {a mathematical formula}1≤ℓ&lt;m is minimal. In worst-case scenario, it requires searching for all bicliques {a mathematical formula}Kℓ,m−ℓ for each of the {a mathematical formula}m−1 possible values of ℓ.ENCD is NP-Complete, therefore {a mathematical formula}ENCD′ is NP-Hard. Accordingly, CSDP is NP-Complete (cf. Theorem 1) therefore MSP is NP-Hard.  □
      </paragraph>
      <paragraph>
       COP (Problem 1), nonetheless, can be solved efficiently by means of a different approach due to Nayak [4], which we describe in next section.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Nayak's efficient algorithm to COP
     </section-title>
     <paragraph>
      The first part of COP requires finding a total causal mapping {a mathematical formula}φ:E→V over a given complete structure {a mathematical formula}S. While Simon's RTCM goes into an intractable step, inspired by Serrano and Gossard's work [14] on constraint modeling and reasoning Nayak has found a polynomial-time approach to that task. We cover it next in all of its steps and see their complexity in some detail.
     </paragraph>
     <section label="4.1">
      <section-title>
       Total causal mappings
      </section-title>
      <paragraph>
       Given a structure {a mathematical formula}S, there may be more than one total causal mappings over {a mathematical formula}S (recall Example 1). So a question that arises is whether the transitive closure {a mathematical formula}Cφ+ is the same for any total causal mapping φ over {a mathematical formula}S; that is, whether the causal ordering of {a mathematical formula}S is unique. Proposition 2, from Nayak [4], ensures that is the case.
      </paragraph>
      <paragraph>
       Before proceeding, we reformulate Definition 8 given in §3 in order to detach the notion of ‘strongly coupled’ variables from Simon's ‘minimal structures’ (Definition 5) and connect it to Nayak's concept of ‘causal dependency’ (Definition 4).
      </paragraph>
      <paragraph label="Definition 8">
       (reformulated) Let {a mathematical formula}S(E,V) be a structure with variables {a mathematical formula}xa,xb∈V, and {a mathematical formula}Cφ+ be the set of causal dependencies induced by total causal mapping φ over {a mathematical formula}S. We say that {a mathematical formula}xa and {a mathematical formula}xb are strongly coupled if we have both {a mathematical formula}(xa,xb),(xb,xa)∈Cφ+.
      </paragraph>
      <paragraph>
       Recall from Example 1 the strongly coupled variables, {a mathematical formula}x4 and {a mathematical formula}x5. Now we can see it only in terms of causal dependencies.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}S(E,V)be a structure, and{a mathematical formula}φ1:E→Vand{a mathematical formula}φ2:E→Vbe any two total causal mappings over{a mathematical formula}S. Then{a mathematical formula}Cφ1+=Cφ2+.The proof is based on an argument from Nayak [4], which we present in a bit more of detail (see Appendix D). Intuitively, it shows that if {a mathematical formula}φ1 and {a mathematical formula}φ2 differ in the variable an equation f is mapped to, then such variables, viz., {a mathematical formula}φ1(f)=xa and {a mathematical formula}φ2(f)=xb, must be causally dependent on each other (strongly coupled).  □
      </paragraph>
      <paragraph>
       Another issue is concerned with the precise conditions under which total causal mappings exist (i.e., whether or not all variables in the equations can be causally determined). In fact, by Proposition 3, based on Nayak [4] apud. Hall [16, pp. 135–137], we know that the existence condition holds if and only if the given structure is complete. We refer to Even [16] to briefly introduce the additional graph-theoretic concepts that are necessary here:
      </paragraph>
      <list>
       <list-item label="•">
        A matching in a graph is a subset of edges such that no two edges in the matching share a common node.
       </list-item>
       <list-item label="•">
        A matching is said maximum if no edge can be added to the matching (without hindering the matching property).
       </list-item>
       <list-item label="•">
        Finally, a matching in a graph is said ‘perfect’ if every vertex is an end-point of some edge in the matching—in a bipartite graph, a perfect matching is said to be a complete matching.
       </list-item>
      </list>
      <paragraph label="Proposition 3">
       Let{a mathematical formula}S(E,V)be a structure. Then a total causal mapping{a mathematical formula}φ:E→Vover{a mathematical formula}Sexists if and only if{a mathematical formula}Sis complete.
      </paragraph>
      <paragraph label="Proof">
       We observe that a total causal mapping {a mathematical formula}φ:E→V over {a mathematical formula}S corresponds exactly to a complete matching M in a bipartite graph {a mathematical formula}B=(V1∪V2,E), where {a mathematical formula}V1↦E, {a mathematical formula}V2↦V, and {a mathematical formula}E↦S. In fact, by Even apud. Hall's theorem (cf. [16, pp. 135–137]), we know that B has a complete matching iff (a) for every subset of vertices {a mathematical formula}F⊆V1, we have {a mathematical formula}|F|≤|E(F)|, where {a mathematical formula}E(F) is the set of all vertices connected to the vertices in F by edges in E; and (b) {a mathematical formula}|V1|=|V2|. By Definition 1 (no subset of equations has fewer variables than equations), and Definition 2 (number of equations is the same as number of variables), it is easy to see that conditions (a) and (b) above hold iff {a mathematical formula}S is a complete structure.  □
      </paragraph>
      <paragraph>
       The problem of finding a maximum matching is a well-studied algorithmic problem. The Hopcroft–Karp algorithm is a classical solution [18], bounded in polynomial time by {a mathematical formula}O(|V1|+|V2||E|). It solves maximum matching in a bipartite graph efficiently as a problem of maximum flow in a network (cf. [16, pp. 135–137], or [19, p. 763]). That is, we can handle the problem of finding a total causal mapping φ over a structure {a mathematical formula}S (see Algorithm 2) by first translating it to the problem of maximum matching in a bipartite graph in time {a mathematical formula}O(|S|). Then we can just apply the Hopcroft–Karp algorithm to get the matching and finally translate it back to the total causal mapping φ. This procedure has been suggested by Nayak in connection with his Proposition 3 and its respective proof [4].
      </paragraph>
      <paragraph>
       Fig. 4 shows the complete matching found by the Hopcroft–Karp algorithm for the structure given in Example 1. Corollary 2 and Remark 1 summarize the results presented in this note.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}S(E,V)be a complete structure. Then a total causal mapping{a mathematical formula}φ:E→Vover{a mathematical formula}Scan be found by (Algorithm 2) TCM in time that is bounded by{a mathematical formula}O(|V|⋅|S|).Let {a mathematical formula}B=(V1∪V2,E) be the bipartite graph corresponding to complete structure {a mathematical formula}S given to TCM, where {a mathematical formula}V1↦E, {a mathematical formula}V2↦V, and {a mathematical formula}E↦S. The translation of {a mathematical formula}S into B is done by a scan over it. This scan is of length {a mathematical formula}|S|=|E|. Note that number {a mathematical formula}|E| of edges rendered is precisely the length {a mathematical formula}|S| of structure, where the denser the structure, the greater {a mathematical formula}|S| is. The re-translation of the matching computed by internal procedure Hopcroft–Karp, in turn, is done at expense of {a mathematical formula}|E|=|V|≤|S|. Thus, it is easy to see that TCM is dominated by the maximum matching algorithm Hopcroft–Karp, which is known to be {a mathematical formula}O(|V1|+|V2|⋅|E|), i.e., {a mathematical formula}O(|E|+|V|⋅|S|). Since {a mathematical formula}S is assumed complete, we have {a mathematical formula}|E|=|V| then {a mathematical formula}|V|+|V|=2|V|. Therefore, TCM must have running time at most {a mathematical formula}O(|V|⋅|S|).  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Computing transitive closure
      </section-title>
      <paragraph>
       Finally, recall that the set {a mathematical formula}Cφ of direct causal dependencies induced by a total causal mapping φ over a given structure {a mathematical formula}S(E,V) produces to the so-called ‘causal graph,’ i.e., a directed graph (digraph) {a mathematical formula}G(V,E) where {a mathematical formula}V↦V and {a mathematical formula}E↦Cφ. So, computing set {a mathematical formula}Cφ+ of causal dependencies given {a mathematical formula}Cφ corresponds to computing transitive closure (reachability links) on G. Note that {a mathematical formula}|V|=|V|, and also note that {a mathematical formula}|E|=|Cφ|=|S|−|V|=O(|S|).
      </paragraph>
      <paragraph>
       Classical algorithms for such task (e.g., Floyd–Warshall's) are bounded in time {a mathematical formula}O(|V|3)[19, p. 697]. Another way to do it is by discovering reachability links using either one of the popular graph traversal algorithms, breadth-first search or depth-first search (DFS) [19, p. 603]. Algorithm 3 describes DFS-based transitive closure over digraph {a mathematical formula}G(V,E). It runs in time {a mathematical formula}O(|V|⋅|E|), which means {a mathematical formula}O(|V|⋅|S|) for a complete structure {a mathematical formula}S(E,V).
      </paragraph>
      <paragraph label="Remark 1">
       Let {a mathematical formula}S(E,V) be a complete structure. Then we know (cf. Proposition 3) that a total causal mapping over {a mathematical formula}S exists. Let it be defined {a mathematical formula}φ≜TCM(S), which can be done in {a mathematical formula}O(|V|⋅|S|). Then the causal ordering implicit in {a mathematical formula}S can be correctly extracted (cf. Proposition 2) by computing {a mathematical formula}Cφ+, the set of causal dependencies induced by φ, in terms of graph transitive closure (TC). The latter is bounded in time by {a mathematical formula}O(|V|⋅|S|), that is, the complexity of COP is dominated by TC.In other words, the complete recipe to solve COP consists in replacing Simon's RTCM by Nayak's TCM in COA (Algorithm 1). Transitive closure (TC) in turn is computed as described in Algorithm 3.  □
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Proof of Proposition 1
     <paragraph>
      Let {a mathematical formula}S be a complete structure. If {a mathematical formula}S1,S2⊂S are any different minimal substructures of {a mathematical formula}S, then they are disjoint.
     </paragraph>
     <paragraph label="Proof">
      We show the statement by case analysis and then contradiction out of Definition 1, Definition 2, Definition 3, Definition 4, Definition 5. By assumption both {a mathematical formula}S1,S2 are minimal (hence complete). Let their size be {a mathematical formula}|V1|=|E1|=ℓ and {a mathematical formula}|V2|=|E2|=m. Let also {a mathematical formula}ℓ≤m. The argument is analogous otherwise but it shall be convenient to keep a placeholder for the size of the smaller substructure (with no loss of generality).By Definition 5 (minimal structures), we know that {a mathematical formula}S1⊈S2 and {a mathematical formula}S1⊉S2. Now suppose {a mathematical formula}S1,S2 are not disjoint. Then by Definition 6 there must be at least one shared variable {a mathematical formula}x∈V1,V2, and thus we must have {a mathematical formula}|V1∪V2|≤ℓ+m−1.We can then proceed through case analysis by inquiring how many equations are shared by {a mathematical formula}S1,S2. Since {a mathematical formula}S1 is minimal with {a mathematical formula}|E1|=|V1|=ℓ for {a mathematical formula}1≤ℓ≤m, the number of equations that are shared with {a mathematical formula}S2 could be any {a mathematical formula}0≤k&lt;ℓ. (Note that the case of {a mathematical formula}k=ℓ shared equations would lead to the more obvious contradiction that {a mathematical formula}S1⊆S2, even though {a mathematical formula}S2 is minimal.)Let us start with the case {a mathematical formula}E1∩E2=∅ to illustrate the rationale in its simplest form. In this case, no equations are shared yet at least one variable is. Then we have {a mathematical formula}|E1∪E2|=ℓ+m, but {a mathematical formula}|V1∪V2|≤ℓ+m−1. Since we have both {a mathematical formula}S1,S2⊂S, in fact we have their sets of equations {a mathematical formula}E1,E2⊂E as well and then {a mathematical formula}E1∪E2⊆E. Now, by Definition 1 (valid structure), we know that in any subset of {a mathematical formula}k&gt;0 equations of {a mathematical formula}S, at least k different variables must appear. But rather we have {a mathematical formula}|E1∪E2|=ℓ+m and yet {a mathematical formula}|V1∪V2|≤ℓ+m−1. That is, we reach a contradiction to Definition 1, viz., {a mathematical formula}|E1∪E2|&gt;|V1∪V2|. ↯.The next case is when one equation is shared ({a mathematical formula}|E1∩E2|=1). Note that, if we had {a mathematical formula}|E1|=|V1|=ℓ=1 in particular then the only equation {a mathematical formula}f∈E1 would have {a mathematical formula}|Vars(f)|=1 and be shared with {a mathematical formula}E2, making {a mathematical formula}S1⊆S2 even though {a mathematical formula}S2 is assumed minimal. ↯. We rather know that {a mathematical formula}|E1|=ℓ≥2. Also, note that we must have {a mathematical formula}|Vars(f)|≥2 for all {a mathematical formula}f∈E1, otherwise there would be some {a mathematical formula}g∈E1 with {a mathematical formula}|Vars(g)|=1 even though {a mathematical formula}|E1|≥2. That is, we would have a minimal substructure within {a mathematical formula}S1, although it is minimal.So, since one equation is shared and for all {a mathematical formula}f∈E1 we have {a mathematical formula}|Vars(f)|≥2, then at least two variables must be shared. Observe then that {a mathematical formula}|E1∪E2|=ℓ+m−1 (since exactly one equation is shared) and {a mathematical formula}|V1∪V2|≤ℓ+m−2 (at least two variables are shared). Again, we see the same contradiction in face of Definition 1, viz., {a mathematical formula}|E1∪E2|&gt;|V1∪V2|. ↯.Now we complete the case analysis by making the argument abstract for any number of shared equations, {a mathematical formula}0≤k&lt;ℓ (an inductive step, n.b., is not required because {a mathematical formula}k∈N is bounded). Note that, for any such number {a mathematical formula}0≤k&lt;ℓ, we must have at least {a mathematical formula}k+1 shared variables, otherwise the shared substructure having k equations, formed out of {a mathematical formula}E1∩E2, would be minimal as well even though {a mathematical formula}E1∩E2⊆E1,E2 (that is, rendering both {a mathematical formula}S1,S2 non-minimal. ↯). However, once more we see that this contradicts Definition 1. ↯.  □
     </paragraph>
    </section>
    <section label="Appendix B">
     Proof of Lemma 2
     <paragraph>
      Let {a mathematical formula}S(V,E) be a complete structure with {a mathematical formula}|E|=|V|=m and {a mathematical formula}1≤ℓ&lt;m provide an instance of CSDP. Let also {a mathematical formula}G(V1∪V2,E) be a bipartite graph {a mathematical formula}G∼S. Then {a mathematical formula}S has a substructure {a mathematical formula}S′ that gives a yes answer to CSDP if and only if G has a bipartite subgraph {a mathematical formula}G′(V1′∪V2′,E′) such that {a mathematical formula}G′∼S′ and all of these conditions hold:
     </paragraph>
     <list>
      <list-item label="(i)">
       Bipartite subgraph {a mathematical formula}G′ is structural;
      </list-item>
      <list-item label="(ii)">
       For every {a mathematical formula}f∈V1′, there is an edge {a mathematical formula}(f,x)∈E only if {a mathematical formula}x∈V2′;
      </list-item>
      <list-item label="(iii)">
       Bipartite subgraph {a mathematical formula}G′ is ℓ-balanced, that is, {a mathematical formula}|V1′|=|V2′|=ℓ.
      </list-item>
     </list>
     <paragraph label="Proof">
      First, we consider the ‘if’ statement—that is, all conditions (i–iii) together are sufficient. Let {a mathematical formula}G′⊂G be a bipartite subgraph {a mathematical formula}G′(V1′∪V2′,E′) that satisfies all conditions (i–iii), and {a mathematical formula}S′(E′,V′) be a substructure of {a mathematical formula}S with {a mathematical formula}G′∼S′. We shall see that such {a mathematical formula}S′ does give a yes answer to CSDP, that is, it is a complete substructure with {a mathematical formula}|E′|=|V′|=ℓ.From condition (i) we know that {a mathematical formula}G′ is structural (Definition 10). That is, for every {a mathematical formula}V1″⊆V1′, there is a connected bipartite subgraph {a mathematical formula}G″(V1″∪V2″,E″) with {a mathematical formula}|V1″|≤|V2″|. Since {a mathematical formula}V1′↦E′, {a mathematical formula}V2′↦V′ and {a mathematical formula}E′↦S′, such property bears obvious resemblance with Definition 1 (structure). That is, the ‘connected’ bipartite subgraph aspect implies that, for any subset of {a mathematical formula}|E″| equations in {a mathematical formula}E′, at least {a mathematical formula}|V″|≥|E″| variables appear and each such variable {a mathematical formula}x∈V″ appears in some {a mathematical formula}f∈E″, otherwise {a mathematical formula}x∈V2″ would be disconnected in {a mathematical formula}G″(V1″∪V2″,E″).Condition (ii) ensures in addition that {a mathematical formula}⋃f∈E′Vars(f)=V′. That is, the variables in {a mathematical formula}V′ are exhaustive w.r.t. {a mathematical formula}E′. Thus, structure {a mathematical formula}S′ satisfies Definition 1. Finally, condition (iii) ensures that {a mathematical formula}S′ is complete with {a mathematical formula}|E′|=|V′|=ℓ.We consider now the ‘only if’ statement—i.e., every condition (i–iii) is necessary. We assume a bipartite graph {a mathematical formula}G′∼S′ and show that lacking any one such condition implies that {a mathematical formula}S′ cannot be complete or cannot be a structure at all. First, it is easy to see that when condition (iii) does not hold for {a mathematical formula}G′ then a structure {a mathematical formula}S′ with {a mathematical formula}G′∼S′ cannot be complete.Now suppose condition (ii) does not for {a mathematical formula}G′. That is, there is some {a mathematical formula}f∈V1′ that has incidence with some {a mathematical formula}x∈V2∖V2′. Thus we have {a mathematical formula}V1′↦E′ and {a mathematical formula}V2′↦V′ but {a mathematical formula}⋃f∈E′Vars(f)≠V′. Therefore either {a mathematical formula}S′ does not satisfy Definition 1 or we cannot actually have {a mathematical formula}G′∼S′. ↯.Finally, consider that {a mathematical formula}G′ is not structural (Definition 10). That is, there is some {a mathematical formula}V1″⊆V1′ such that no connected bipartite subgraph {a mathematical formula}G″(V1″∪V2″,E″) exists in {a mathematical formula}G′ with {a mathematical formula}|V1″|≤|V2″|. Considering {a mathematical formula}G′∼S′, that would imply for {a mathematical formula}S′(E′,V′) either an equation {a mathematical formula}f∈E′ with no variables (a disconnected vertex {a mathematical formula}x∈V1′), or a redundant subset of equations—number of equations is larger than number of variables appearing in it. Either conditions violate Definition 1, so {a mathematical formula}S′ cannot be a structure even though {a mathematical formula}G′∼S′. ↯.  □
     </paragraph>
    </section>
    <section label="Appendix C">
     Proof of Theorem 1
     <paragraph>
      CSDP is NP-Complete.
     </paragraph>
     <paragraph label="Proof">
      We shall construct an instance of ENCD and describe its polynomial-time reduction to an instance of CSDP by using Lemma 2.Constructing an instance of ENCD. Let {a mathematical formula}G(V1∪V2,E) be a bipartite graph such that, for every {a mathematical formula}V1′⊆V1, there is a bipartite subgraph {a mathematical formula}G′(V1′∪V2′,E′) with {a mathematical formula}|V1′|≤|V2′| and {a mathematical formula}deg(f)&lt;|V2′| for all {a mathematical formula}f∈V1′. Note that this is the complement property of the structural bipartite graph property (see Definition 10). It is meant to ensure that the bipartite complement graph {a mathematical formula}Gc(V1∪V2,Ec) of G is structural—satisfies Definition 10. That is, when we produce {a mathematical formula}Gc, we know that it can possibly correspond to a structure {a mathematical formula}S such that {a mathematical formula}Gc∼S. Let also G have {a mathematical formula}|V1|=|V2|=m in order to ensure that such structure {a mathematical formula}S will be complete as well—recall that {a mathematical formula}S given in CSDP is assumed complete indeed.Now let G and an integer {a mathematical formula}1≤ℓ&lt;m provide an instance of ENCD for integers {a mathematical formula}a=ℓ and {a mathematical formula}b=m−ℓ. That is, our problem is to decide whether G has a biclique {a mathematical formula}Kℓ,m−ℓ. Imposing both of the above properties on G, n.b., incurs in no loss of generality w.r.t. ENCD as it does not open a pruning opportunity in searching for a biclique {a mathematical formula}Kℓ,m−ℓ in powerset {a mathematical formula}P(V1×V2). Such a biclique {a mathematical formula}Kℓ,m−ℓ, if existing in G, can be denoted {a mathematical formula}C(V1′∪V2⋆,K), where {a mathematical formula}|V1′|=ℓ and {a mathematical formula}|V2⋆|=m−ℓ, and K is a complete set of edges between {a mathematical formula}V1′ and {a mathematical formula}V2⋆. Note also that {a mathematical formula}V1′⊂V1 and {a mathematical formula}V2⋆⊂V2.Production of an instance of CSDP from the ENCD one. Let {a mathematical formula}Gc(V1∪V2,Ec) be the bipartite complement graph of G, where an edge {a mathematical formula}(f,x)∈Ec if and only if {a mathematical formula}(f,x)∉E for {a mathematical formula}f∈V1 and {a mathematical formula}x∈V2. Clearly, bipartite graph {a mathematical formula}Gc can be produced in polynomial time from G—as mentioned in §3.2, consider the ‘structure matrix’ (biadjacency matrix) of G and run a full scan on it to switch the boolean value of each entry in time {a mathematical formula}O(|V1|⋅|V2|) and then get {a mathematical formula}Gc.Decision problem correspondence. Now we show that a biclique {a mathematical formula}Kℓ,m−ℓ in G, if existing, corresponds to a bipartite subgraph {a mathematical formula}Gc′(V1′∪V2′,Ec′) in {a mathematical formula}Gc that satisfies the conditions (i–iii) of Lemma 2. That is, we show that a yes answer to ENCD implies a yes answer to CSDP.In fact, as {a mathematical formula}Gc is the bipartite complement graph of G, then the biclique {a mathematical formula}C(V1′∪V2⋆,K) in G becomes a bipartite subgraph {a mathematical formula}Cc(V1′∪V2⋆,∅) in {a mathematical formula}Gc. Now let {a mathematical formula}Gc′(V1′∪V2′,Ec′) be such that {a mathematical formula}V2′=V2∖V2⋆ and {a mathematical formula}(f,x)∈Ec′ if and only if {a mathematical formula}(f,x)∈Ec for {a mathematical formula}f∈V1′ and {a mathematical formula}x∈V2′. We observe that:
      <list>
       The presence of biclique {a mathematical formula}C(V1′∪V2⋆,K) in G indicates that {a mathematical formula}V2⋆ could not have contributed to satisfy the complement structural property for {a mathematical formula}V1′, only {a mathematical formula}V2′=V2∖V2⋆ could. But such property turns into the structural property in {a mathematical formula}Gc, thus {a mathematical formula}Gc′(V1′∪V2′,Ec′) must be structural indeed. That is, condition (i) of Lemma 2 is ensured.By the fact that we have {a mathematical formula}Cc(V1′∪V2⋆,∅) in {a mathematical formula}Gc we know that, for all {a mathematical formula}f∈V1′, there can only be an edge {a mathematical formula}(f,x)∈Ec if {a mathematical formula}x∈V2′ indeed. That is, condition (ii) of Lemma 2 is ensured.The presence of biclique {a mathematical formula}C(V1′∪V2⋆,K) of form {a mathematical formula}Kℓ,m−ℓ in G implies that {a mathematical formula}V1′ has size {a mathematical formula}|V1′|=ℓ. Besides, {a mathematical formula}V2′ will have size {a mathematical formula}|V2′|=|V2|−|V2⋆|=m−(m−ℓ)=ℓ. That is, we must have {a mathematical formula}|V1′|=|V2′|=ℓ and then condition (iii) of Lemma 2 is ensured as well.We have then established that the existence of a biclique
      </list>
      <paragraph>
       ENCD is NP-Complete. Thus CSDP must be NP-Complete as well.  □
      </paragraph>
     </paragraph>
    </section>
    <section label="Appendix D">
     Proof of Proposition 2
     <paragraph label="Proof">
      Let {a mathematical formula}S(E,V) be a structure, and {a mathematical formula}φ1:E→V and {a mathematical formula}φ2:E→V be any two total causal mappings over {a mathematical formula}S. Then {a mathematical formula}C1+=C2+. The proof is based on an argument from Nayak [4], which we reproduce here in a bit more of detail. Intuitively, it shows that if {a mathematical formula}φ1 and {a mathematical formula}φ2 differ in the variable an equation f is mapped to, then such variables, viz., {a mathematical formula}φ1(f) and {a mathematical formula}φ2(f), must be causally dependent on each other (strongly coupled).To show {a mathematical formula}C1+=C2+ reduces to show both {a mathematical formula}C1+⊆C2+ and {a mathematical formula}C2+⊆C1+. We show the first containment, and the second is understood as following by symmetry. Closure operators are extensive, {a mathematical formula}X⊆cl(X), and idempotent, {a mathematical formula}cl(cl(X))=cl(X). That is, if we have {a mathematical formula}C1⊆C2+, then we shall have {a mathematical formula}C1+⊆(C2+)+ and, by idempotence, {a mathematical formula}C1+⊆C2+.Then it suffices to show that {a mathematical formula}C1⊆C2+, i.e., for any {a mathematical formula}(x′,x)∈C1, we must show that {a mathematical formula}(x′,x)∈C2+ as well. Observe by Definition 3 that both {a mathematical formula}φ1 and {a mathematical formula}φ2 are bijections, then, invertible functions. If {a mathematical formula}φ1−1(x)=φ2−1(x), then we have {a mathematical formula}(x′,x)∈C2 and thus, trivially, {a mathematical formula}(x′,x)∈C2+. Else, {a mathematical formula}φ1 and {a mathematical formula}φ2 disagree in which equations they map onto x. But we show next, in any case, that we shall have {a mathematical formula}(x′,x)∈C2+.Take all equations {a mathematical formula}g∈E′⊆E such that {a mathematical formula}φ1(g)≠φ2(g), and let {a mathematical formula}n≤|E| be the number of such ‘disagreed’ equations. Now, let {a mathematical formula}f∈E′ be such that its mapped variable is {a mathematical formula}x=φ1(f). Construct a sequence of length 2n such that, {a mathematical formula}s0=φ1(f)=x and, for {a mathematical formula}1≤i≤2n, element {a mathematical formula}si is defined {a mathematical formula}si=φ2(φ1−1(si−1)). That is, we are defining the sequence such that, for each equation {a mathematical formula}g∈E′, its disagreed mappings {a mathematical formula}φ1(g)=xa and {a mathematical formula}φ2(g)=xb are such that {a mathematical formula}φ1(g) is immediately followed by {a mathematical formula}φ2(g). As {a mathematical formula}xa,xb∈Vars(g), we have {a mathematical formula}(xa,xb)∈C2 and, symmetrically, {a mathematical formula}(xb,xa)∈C1. The sequence is of form {a mathematical formula}s=〈x,xf︸f,…,xa,xb︸g,…,x2n−1,x2n︸h〉.Since x must be in the codomain of {a mathematical formula}φ2, we must have a repetition of x at some point {a mathematical formula}2≤k≤2n in the sequence index, with {a mathematical formula}sk=x and {a mathematical formula}sk−1=x″ such that {a mathematical formula}(x″,x)∈C2. If {a mathematical formula}x″=x′, then {a mathematical formula}(x′,x)∈C2 and obviously {a mathematical formula}(x′,x)∈C2+. Else, note that {a mathematical formula}xf must also be in the codomain of {a mathematical formula}φ1, while {a mathematical formula}x″ in the codomain of {a mathematical formula}φ2. Let ℓ be the point in the sequence, {a mathematical formula}3≤ℓ≤2n−1, at which {a mathematical formula}sℓ=xf=xa and {a mathematical formula}sℓ+1=xb for some {a mathematical formula}xb such that {a mathematical formula}(xf,xb)∈C2. It is easy to see that, either we have {a mathematical formula}xb=x″ or {a mathematical formula}xb≠x″ but {a mathematical formula}(xb,x″)∈C2+. Thus, by transitivity on such a causal chain, we must have {a mathematical formula}(xf,x″)∈C2+ and eventually {a mathematical formula}(xf,x)∈C2+. Finally, since {a mathematical formula}x′∈Vars(f) and {a mathematical formula}φ2(f)=xf, we have {a mathematical formula}(x′,xf)∈C2 and, by transitivity, {a mathematical formula}(x′,x)∈C2+.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>