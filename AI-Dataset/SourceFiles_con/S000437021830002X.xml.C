<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    The complexity landscape of decompositional parameters for ILP.
   </title>
   <abstract>
    Integer Linear Programming (ILP) can be seen as the archetypical problem for NP-complete optimization problems, and a wide range of problems in artificial intelligence are solved in practice via a translation to ILP. Despite its huge range of applications, only few tractable fragments of ILP are known, probably the most prominent of which is based on the notion of total unimodularity. Using entirely different techniques, we identify new tractable fragments of ILP by studying structural parameterizations of the constraint matrix within the framework of parameterized complexity. In particular, we show that ILP is fixed-parameter tractable when parameterized by the treedepth of the constraint matrix and the maximum absolute value of any coefficient occurring in the ILP instance. Together with matching hardness results for the more general parameter treewidth, we give an overview of the complexity of ILP w.r.t. decompositional parameters defined on the constraint matrix.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Integer Linear Programming (ILP) is among the most successful and general paradigms for solving computationally intractable optimization problems in computer science. In particular, a wide variety of problems in artificial intelligence are efficiently solved in practice via a translation into an Integer Linear Program, including problems from areas such as process scheduling [10], planning [31], [32], vehicle routing [30], packing [23], and network hub location [1]. In its most general form ILP can be formalized as follows:
     </paragraph>
     <paragraph>
      {an inline-figure}
     </paragraph>
     <paragraph>
      Closely related to ILP is the ILP-feasibility problem, where given A and b as above, the problem is to decide whether there is an {a mathematical formula}x∈Zn such that {a mathematical formula}Ax≤b. The decision version of ILP, ILP-feasibility and various other highly restricted variants are well-known to be {a mathematical formula}NP-complete [28].
     </paragraph>
     <paragraph>
      Despite the importance of the problem, an understanding of the influence of structural restrictions on the complexity of ILP is still in its infancy. This is in stark contrast to another well-known and general paradigm for the solution of problems in Computer Science, the Satisfiability problem (SAT). There, the parameterized complexity framework [7] has yielded deep results capturing the tractability and intractability of SAT with respect to a plethora of structural restrictions. In the context of SAT, one often considers structural restrictions on a graphical representation of the formula (such as the primal graph), and the aim is to design efficient fixed-parameter algorithms for SAT, i.e., algorithms running in time {a mathematical formula}O(f(k)nO(1)) where k is the value of the considered structural parameter for the given SAT instance and n is its input size. It is known that SAT is fixed-parameter tractable w.r.t. a variety of structural parameters, including the prominent parameters treewidth [29] but also more specialized parameters [9], [13], [14].
     </paragraph>
     <paragraph>
      Our contribution  In this work, we carry out a similar line of research for ILP by studying the parameterized complexity of ILP w.r.t. various structural parameterizations. In particular, we consider parameterizations of the primal graph of the ILP instance, i.e., the undirected graph whose vertex set is the set of variables of the ILP instance and whose edges represent the occurrence of two variables in a common expression. We obtain a complete picture of the parameterized complexity of ILP w.r.t. well-known decompositional parameters of the primal graph, specifically treedepth, treewidth, and cliquewidth; our results are summarized in Table 1.
     </paragraph>
     <paragraph>
      Our main algorithmic result (Theorem 6) shows that ILP is fixed-parameter tractable parameterized by the treedepth of the primal graph and the maximum absolute value ℓ of any coefficient occurring in A or b. Together with the classical results for totally unimodular matrices [27, Section 13.2.] and fixed number of variables [22], which use entirely different techniques, our result is one of the few tractability results for ILP without additional restrictions. We note that the presented algorithm is primarily of theoretical interest; the intent here is to classify the complexity of ILP by providing runtime guarantees, not to compete with state-of-the-art ILP solvers.
     </paragraph>
     <paragraph>
      We complement our algorithmic results with matching lower bounds, provided in terms of paraNP -hardness results (see the Preliminaries); an overview of the obtained results is provided in Table 1. Namely, we show that already ILP-feasibility is unlikely to be fixed-parameter tractable when parameterized by treedepth (whereas the case of parameterizing by only ℓ is known to be hard); in fact, our results also exclude algorithms running in time {a mathematical formula}(n+m)f(k), where k is the parameter. Moreover, the hardness results provided here also hold in the strong sense, i.e., even for ILP instances whose size is bounded by a polynomial of n and m; it is worth noting that this requires a more careful approach than what would suffice for weak paraNP -hardness.
     </paragraph>
     <paragraph>
      One might be tempted to think that, as is the case for SAT and numerous other problems, the fixed-parameter tractability result for treedepth carries over to the more general structural parameter treewidth. We show that this is not the case for ILP. Along with recent results for the Mixed Chinese Postman Problem [18], this is only the second known case of a natural problem where using treedepth instead of treewidth actually “helps” in terms of fixed parameter tractability. In fact, we show that already ILP-feasibility remains {a mathematical formula}NP-hard for ILP instances of treewidth at most two and whose maximum coefficient is at most one. Observe that this also implies the same intractability results for the more general parameter clique-width [2].
     </paragraph>
     <paragraph>
      Related work  We are not the first to consider decompositional parameterizations of the primal graph for ILP. However, previous results in this area required either implicit or explicit bounds on the domain values of variables together with further restrictions on the coefficients. In particular, for the case of non-negative ILP instances, i.e., ILP instances where all coefficients as well as all variable domains are assumed to be non-negative, ILP is known to be fixed-parameter tractable parameterized by the branchwidth, a decompositional parameter closely related to treewidth, of the primal graph and the maximum value B of any coefficient in the constraint vector b[3]. Note that B also bounds the maximum domain value of any variable in the case of non-negative ILP instances. A more recent result by Jansen and Kratsch [20] showed that ILP is fixed-parameter tractable parameterized by the treewidth of the primal graph and the maximum absolute domain value of any variable. Hence in both cases the maximum absolute domain value of any variable is bounded by the considered parameters, whereas the results presented in this paper do not require any bound on the domain values of variables.
     </paragraph>
     <paragraph>
      Furthermore, a series of tractability results for ILP based on restrictions on the constraint matrix A, instead of restrictions on the primal graph, have been obtained [5], [19], [26]. These results apply whenever the constraint matrix A can be written as an arbitrary large product of matrices of bounded size and are usually referred to as n-fold ILP, two-stage stochastic ILP, and 4-block n-fold ILP.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      We will use standard graph terminology, see for instance [6]. A graph G is a tuple {a mathematical formula}(V,E), where V or {a mathematical formula}V(G) is the vertex set and E or {a mathematical formula}E(G) is the edge set. A graph H is a subgraph of a graph G, denoted {a mathematical formula}H⊆G, if H can be obtained by deleting vertices and edges from G. All our graphs are simple and loopless.
     </paragraph>
     <paragraph>
      A path from vertex {a mathematical formula}v1 to vertex {a mathematical formula}vj in G is a sequence of distinct vertices {a mathematical formula}v1,…,vj such that for each {a mathematical formula}1≤i&lt;j, {a mathematical formula}{vi,vi+1}∈E(G). A tree is a graph in which, for any two vertices {a mathematical formula}v,w∈G, there is precisely one unique path from v to w; a tree is rooted if it contains a specially designated vertex r, the root. Given a vertex v in a tree G with root r, the parent of v is the unique vertex w with the property that {a mathematical formula}{v,w} is the first edge on the path from v to r.
     </paragraph>
     <section label="2.1">
      <section-title>
       Integer Linear Programming
      </section-title>
      <paragraph>
       For our purposes, it will be useful to view an ILP instance as a set of linear inequalities rather than using the constraint matrix. Formally, let an ILP instance I be a tuple {a mathematical formula}(F,η) where {a mathematical formula}F is a set of linear inequalities over variables {a mathematical formula}X={x1,…,xn} and η is a linear function over X of the form {a mathematical formula}η(X)=s1x1+…+snxn. Each inequality {a mathematical formula}A∈F ranges over variables {a mathematical formula}var(A) is said to have arity {a mathematical formula}|var(A)|=l and is assumed to be of the form {a mathematical formula}cA,1xA,1+cA,2xA,2+…+cA,lxA,l≤bA; we also define {a mathematical formula}var(I)=X. We say that two constraints are equal if they range over the same variables with the same coefficients and have the same right-hand side.
      </paragraph>
      <paragraph>
       For a set of variables Y, let {a mathematical formula}F(Y) denote the subset of {a mathematical formula}F containing all inequalities {a mathematical formula}A∈F such that {a mathematical formula}Y∩var(A)≠∅. We will generally use the term coefficients to refer to numbers that occur in the inequalities in {a mathematical formula}F. In some cases, we will be dealing with certain selected “named” variables which will not be marked with subscripts to improve readability (e.g., a); there, we may use {a mathematical formula}sa to denote the coefficient of a in η, i.e., {a mathematical formula}sa is shorthand for {a mathematical formula}sj where {a mathematical formula}a=xj.
      </paragraph>
      <paragraph>
       An assignment α is a mapping from X to {a mathematical formula}Z. For an assignment α and an inequality A of arity l, we denote by {a mathematical formula}A(α) the left-side value of A obtained by applying α, i.e., {a mathematical formula}A(α)=cA,1α(xA,1)+cA,2α(xA,2)+…+cA,lα(xA,l). Similarly, we let {a mathematical formula}η(α) denote the value of the linear function η after applying α.
      </paragraph>
      <paragraph>
       An assignment α is called feasible if it satisfies every {a mathematical formula}A∈F, i.e., if {a mathematical formula}A(α)≤bA for each {a mathematical formula}A∈F. Furthermore, α is called a solution if the value of {a mathematical formula}η(α) is maximized over all feasible assignments; observe that the existence of a feasible assignment does not guarantee the existence of a solution (there may exist an infinite sequence of feasible assignments α with increasing values of {a mathematical formula}η(α)). Given an instance I, the task in the ILP problem is to compute a solution for I if one exists, and otherwise to decide whether there exists a feasible assignment. On the other hand, the ILP-feasibility problem asks whether a given instance I admits a feasible assignment (here, we may assume without loss of generality that all coefficients in η are equal to 0).
      </paragraph>
      <paragraph>
       Given an ILP instance {a mathematical formula}I=(F,η), the primal graph {a mathematical formula}GI of I is the graph whose vertex set is the set X of variables in I, and two vertices {a mathematical formula}a,b are adjacent iff either there exists some {a mathematical formula}A∈F containing both a and b or {a mathematical formula}a,b both occur in η with non-zero coefficients.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Parameterized complexity
      </section-title>
      <paragraph>
       In parameterized algorithmics [4], [11], [25], [7] the runtime of an algorithm is studied with respect to a parameter {a mathematical formula}k∈N and input size n. The basic idea is to find a parameter that describes the structure of the instance such that the combinatorial explosion can be confined to this parameter. In this respect, the most favorable complexity class is FPT (fixed-parameter tractable) which contains all problems that can be decided by an algorithm running in time {a mathematical formula}f(k)⋅nO(1), where f is a computable function. Algorithms with this running time are called fpt-algorithms.
      </paragraph>
      <paragraph>
       To obtain our lower bounds, we will need the notion of a parameterized reduction and the complexity class paraNP[7]. Since we obtain all our lower bounds already for ILP-feasibility, we only need to consider these notions for decision problems; formally, a parameterized decision problem is a subset of {a mathematical formula}Σ⁎×N, where Σ is the input alphabet.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}L1 and {a mathematical formula}L2 be parameterized decision problems, with {a mathematical formula}L1⊆Σ1⁎×N and {a mathematical formula}L2⊆Σ2⁎×N. A parameterized reduction (or fpt-reduction) from {a mathematical formula}L1 to {a mathematical formula}L2 is a mapping {a mathematical formula}P:Σ1⁎×N→Σ2⁎×N such that:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(x,k)∈L1 if and only if {a mathematical formula}P(x,k)∈L2;
       </list-item>
       <list-item label="2.">
        the mapping can be computed by an fpt-algorithm with respect to parameter k;
       </list-item>
       <list-item label="3.">
        there is a computable function g such that {a mathematical formula}k′≤g(k), where {a mathematical formula}(x′,k′)=P(x,k).
       </list-item>
      </list>
      <paragraph>
       There is a variety of classes capturing parameterized intractability. For our results, we require only the class paraNP, which is defined as the class of problems that are solvable by a nondeterministic Turing-machine in fpt-time. We will make use of the characterization of paraNP -hardness given by Flum and Grohe [11], Theorem 2.14: any parameterized (decision) problem that remains {a mathematical formula}NP-hard when the parameter is set to some constant is paraNP -hard. Showing paraNP -hardness for a problem rules out the existence of an fpt-algorithm under the assumption that {a mathematical formula}P≠NP. In fact, it even allows us to rule out algorithms running in time {a mathematical formula}nf(k) for any function f (these are sometimes called XP algorithms).
      </paragraph>
      <paragraph>
       For our algorithms, we will use the following result as a subroutine. Note that this is a streamlined version of the original statement of the theorem, as used in the area of parameterized algorithms [8], [15].
      </paragraph>
      <paragraph label="Theorem 1">
       [22], [21], [12]An ILP instance{a mathematical formula}I=(F,η)can be solved in time{a mathematical formula}O(p2.5p+o(p)⋅|I|), where{a mathematical formula}p=|var(I)|.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Treewidth and treedepth
      </section-title>
      <paragraph>
       Treewidth is the most prominent structural parameter and has been extensively studied in a number of fields. In order to define treewidth, we begin with the definition of its associated decomposition. A tree-decomposition{a mathematical formula}T of a graph {a mathematical formula}G=(V,E) is a pair {a mathematical formula}(T,χ), where T is a tree and χ is a function that assigns each tree node t a set {a mathematical formula}χ(t)⊆V of vertices such that the following conditions hold:
      </paragraph>
      <list>
       <list-item label="(P1)">
        For every vertex {a mathematical formula}u∈V, there is a tree node t such that {a mathematical formula}u∈χ(t).
       </list-item>
       <list-item label="(P2)">
        For every edge {a mathematical formula}{u,v}∈E(G) there is a tree node t such that {a mathematical formula}u,v∈χ(t).
       </list-item>
       <list-item label="(P3)">
        For every vertex {a mathematical formula}v∈V(G), the set of tree nodes t with {a mathematical formula}v∈χ(t) forms a subtree of T.
       </list-item>
      </list>
      <paragraph>
       The sets {a mathematical formula}χ(t) are called bags of the decomposition {a mathematical formula}T and {a mathematical formula}χ(t) is the bag associated with the tree node t. The width of a tree-decomposition {a mathematical formula}(T,χ) is the size of a largest bag minus 1. A tree-decomposition of minimum width is called optimal. The treewidth of a graph G, denoted by {a mathematical formula}tw(G), is the width of an optimal tree decomposition of G.
      </paragraph>
      <paragraph>
       Another important notion that we make use of extensively is that of treedepth. Treedepth is a structural parameter closely related to treewidth, and the structure of graphs of bounded treedepth is well understood [24]. A useful way of thinking about graphs of bounded treedepth is that they are (sparse) graphs with no long paths.
      </paragraph>
      <paragraph label="Proposition 4">
       We formalize a few notions needed to define treedepth. A rooted forest is a disjoint union of rooted trees. For a vertex x in a tree T of a rooted forest, the height (or depth) of x in the forest is the number of vertices in the path from the root of T to x. The height of a rooted forest is the maximum height of a vertex of the forest. TreedepthLet the closure of a rooted forest {a mathematical formula}F be the graph {a mathematical formula}clos(F)=(Vc,Ec) with the vertex set {a mathematical formula}Vc=⋃T∈FV(T) and the edge set {a mathematical formula}Ec={xy:xis an ancestor ofy in some T∈F}. A treedepth decomposition of a graph G is a rooted forest {a mathematical formula}F such that {a mathematical formula}G⊆clos(F). The treedepth{a mathematical formula}td(G) of a graph G is the minimum height of any treedepth decomposition of G. We will later use {a mathematical formula}Tx to denote the vertex set of the subtree of T rooted at a vertex x of T. Similarly to treewidth, it is possible to determine the treedepth of a graph in FPT time. [24]Given a graph G with n nodes and a constant w, it is possible to decide whether G has treedepth at most w, and if so, to compute an optimal treedepth decomposition of G in time{a mathematical formula}O(n). The following alternative (equivalent) characterization of treedepth will be useful later for ascertaining the exact treedepth in our reduction (specifically in Theorem 12). [24]Let{a mathematical formula}Gibe the connected components of G. Then{a mathematical formula} We conclude with a few useful facts about treedepth.
      </paragraph>
      <paragraph label="Proposition 5">
       [24]
       <list>
        If a graph G has no path of length d, then{a mathematical formula}td(G)≤d.If{a mathematical formula}td(G)≤d, then G has no path of length{a mathematical formula}2d.{a mathematical formula}tw(G)≤td(G).If{a mathematical formula}td(G)≤d, then{a mathematical formula}td(G′)≤d+1for any graph{a mathematical formula}G′obtained by adding one vertex into G.Within this manuscript, for an ILP instance I we will use
       </list>
       <paragraph>
        treewidth (treedepth) of Ias shorthand for the treewidth (treedepth) of the primal graph{a mathematical formula}GIof I.
       </paragraph>
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Exploiting treedepth to solve ILP
     </section-title>
     <paragraph>
      Our goal in this section is to show that ILP is fixed parameter tractable when parameterized by the treedepth of the primal graph and the maximum coefficient in any constraint. We begin by formalizing our parameters. Given an ILP instance I, let {a mathematical formula}td(I) be the treedepth of {a mathematical formula}GI and let {a mathematical formula}ℓ(I) be the maximum absolute coefficient which occurs in any inequality in I; to be more precise, {a mathematical formula}ℓ(I)=max⁡{|cA,j|,|bA|:A∈F,j∈N}. When the instance I is clear from the context, we will simply write ℓ and {a mathematical formula}k=td(I) for brevity. We will now state our main algorithmic result of this section.
     </paragraph>
     <paragraph label="Theorem 6">
      ILP is fixed-parameter tractable parameterized by ℓ and k.
     </paragraph>
     <paragraph>
      The main idea behind our fixed-parameter algorithm for ILP is to show that we can reduce the instance into an “equivalent instance” such that the number of variables of the reduced instance can be bounded by our parameters ℓ and k. We then apply Theorem 1 to solve the reduced instance.
     </paragraph>
     <paragraph>
      For the following considerations, we fix an ILP instance {a mathematical formula}I=(F,η) of size n along with a treedepth decomposition T of {a mathematical formula}GI with depth k. Given a variable set Y, the operation of omitting consists of deleting all inequalities containing at least one variable in Y and all variables in Y; formally, omitting Y from I results in the instance {a mathematical formula}I′=(F′,η′) where {a mathematical formula}F′=F∖F(Y) and {a mathematical formula}η′ is obtained by removing all variables in Y from η.
     </paragraph>
     <paragraph>
      The following notion of equivalence will be crucial for the proof of Theorem 6. Let {a mathematical formula}x,y be two variables that share a common parent in T, and recall that {a mathematical formula}Tx ({a mathematical formula}Ty) denotes the vertex set of the subtree of T rooted at x (y). We say that x are y are equivalent, denoted {a mathematical formula}x∼y, if there exists a bijective function {a mathematical formula}δx,y:Tx→Ty (called the renaming function) such that {a mathematical formula}δx,y(F(Tx))=F(Ty); here {a mathematical formula}δx,y(F(Tx)) denotes the set of inequalities in {a mathematical formula}F(Tx) after the application of {a mathematical formula}δx,y on each variable in {a mathematical formula}Tx. In other words, {a mathematical formula}x∼y means that there exists a way of “renaming” the variables in {a mathematical formula}Ty so that {a mathematical formula}F(Ty) becomes {a mathematical formula}F(Tx).
     </paragraph>
     <paragraph label="Lemma 7">
      It is easy to verify that ∼ is indeed an equivalence relation. Intuitively, the following lemma shows that if {a mathematical formula}x∼y for two variables x and y of I, then (up to renaming) the set of all feasible assignments of the variables in {a mathematical formula}Tx is equal to the set of all feasible assignments of the variables in {a mathematical formula}Ty; it will be useful to recall the meaning of {a mathematical formula}sa from Subsection 2.1. Let{a mathematical formula}x,ybe two variables of I such that{a mathematical formula}x∼yand{a mathematical formula}sa=0for each{a mathematical formula}a∈Tx∪Ty. Let{a mathematical formula}I′=(F′,η′)be the instance obtained from I by omitting{a mathematical formula}Ty. Then there exists a solution α of{a mathematical formula}var(I)of value{a mathematical formula}w=η(α)if and only if there exists a solution{a mathematical formula}α′of{a mathematical formula}var(I′)of value{a mathematical formula}w=η′(α′). Moreover, a solution α can be computed from any solution{a mathematical formula}α′in linear time if the renaming function{a mathematical formula}δx,yis known.
     </paragraph>
     <paragraph label="Proof">
      Let α be a solution of {a mathematical formula}var(I) of value {a mathematical formula}w=η(α). Since {a mathematical formula}F′⊆F, it follows that setting {a mathematical formula}α′ to be a restriction of α to {a mathematical formula}var(I)∖Ty satisfies every inequality in {a mathematical formula}F′. Since variables in {a mathematical formula}Ty do not contribute to η, it also follows that {a mathematical formula}η(α)=η(α′).On the other hand, let {a mathematical formula}α′ be a solution of {a mathematical formula}var(I′) of value {a mathematical formula}w=η′(α′). Consider the assignment α obtained by extending {a mathematical formula}α′ to {a mathematical formula}Ty by reusing the assignments of {a mathematical formula}Tx on {a mathematical formula}Ty. Formally, for each {a mathematical formula}z∈Ty we set {a mathematical formula}α(z)=α′(δx,y−1(z)) and for all other variables {a mathematical formula}w∈var(I′) we set {a mathematical formula}α(w)=α′(w). By assumption, α and {a mathematical formula}α′ must assign the same values to any variable w such that {a mathematical formula}sw≠0, and hence {a mathematical formula}η(α)=η(α′). To argue feasibility, first observe that any {a mathematical formula}A∈F′ must be satisfied by α since α and {a mathematical formula}α′ only differ on variables which do not occur in {a mathematical formula}I′. Moreover, by definition of ∼ for each {a mathematical formula}A∈F∖F′=F(Ty) there exists an inequality {a mathematical formula}A′∈F′ such that {a mathematical formula}δx,y(A′)=A. In particular, this implies that {a mathematical formula}A(α)=A′(α)=A′(α′), and since {a mathematical formula}A′(α′)≤bA′=bA we conclude that {a mathematical formula}A(α)≤bA. Consequently, α satisfies A.The final claim of the lemma follows from the construction of α described above.  □
     </paragraph>
     <paragraph label="Lemma 8">
      In the following let z be a variable of I at depth {a mathematical formula}k−i in T for every i with {a mathematical formula}1≤i&lt;k and let Z be the set of all children of z in T. Moreover, let m be the maximum size of any subtree rooted at a child of z in T, i.e., {a mathematical formula}m:=maxz′∈Z⁡|Tz′|. We will show next that the number of equivalence classes among the children of z can be bounded by the function {a mathematical formula}#C(ℓ,k,i,m):=2(2ℓ+1)k+1⋅mi. Observe that this bound depends only on ℓ, k, m, and i and not on the size of I. The equivalence relation ∼ has at most{a mathematical formula}#C(ℓ,k,i,m)equivalence classes over Z.
     </paragraph>
     <paragraph label="Lemma 9">
      Consider an element {a mathematical formula}a∈Z. By construction of {a mathematical formula}GI, each inequality {a mathematical formula}A∈F(Ta) only contains at most {a mathematical formula}k−i variables outside of {a mathematical formula}Ta (specifically, the ancestors of a) and at most i variables in {a mathematical formula}Ta. Furthermore, {a mathematical formula}bA and each coefficient of a variable in A is an integer whose absolute value does not exceed ℓ. From this it follows that there exists a finite number of inequalities which can occur in {a mathematical formula}F(Ta). Specifically, the number of distinct combinations of coefficients for all the variables in A and for {a mathematical formula}bA is {a mathematical formula}(2ℓ+1)k+1, and the number of distinct choices of variables in {a mathematical formula}var(A)∩Ta is upper-bounded by {a mathematical formula}(mi), and so we arrive at {a mathematical formula}|F(Ta)|≤(2ℓ+1)k+1⋅(mi)≤(2ℓ+1)k+1⋅mi.Consequently, the set of inequalities for each child {a mathematical formula}y∈Z of z has bounded cardinality. We will use this to bound the number of equivalence classes in {a mathematical formula}#C(ℓ,k,i,m) by observing that two elements are equivalent if and only if they occur in precisely the same sets of inequalities (up to renaming). To formalize this intuition, we need a formal way of canonically renaming all variables in the individual subtrees rooted in Z; without renaming, each {a mathematical formula}F(Ty) would span a distinct set of variables and hence it would not be possible to bound the set of all such inequalities. So, for each y let {a mathematical formula}δy,x0 be a bijective renaming function which renames all of the variables in {a mathematical formula}Ty to the variable set {a mathematical formula}{x01,x02,…,x0|Ty|} (in an arbitrary way). Now we can formally define {a mathematical formula}Γz={F(Tx0):δy,x0(F(Ty)),y∈Z}, and observe that {a mathematical formula}Γz has cardinality at most {a mathematical formula}2(2ℓ+1)k+1⋅mi=#C(ℓ,k,i,m). To conclude the proof, recall that if two variables {a mathematical formula}a,b satisfy {a mathematical formula}F(Ta)=δb,a(F(Tb)) for a bijective renaming function {a mathematical formula}δb,a, then {a mathematical formula}b∼a. Hence, the absolute bound on the cardinality of {a mathematical formula}Γz implies that ∼ has at most {a mathematical formula}#C(ℓ,k,i,m) equivalence classes over Z.  □ It follows from the above lemma that if z has more than {a mathematical formula}#C(ℓ,k,i,m) children, then two of those must be equivalent. The next lemma shows that it is also possible to find such a pair of equivalent children efficiently. Given a subset{a mathematical formula}Z′of Z with{a mathematical formula}|Z′|=#C(ℓ,k,i,m)+1, then in time{a mathematical formula}O(#C(ℓ,k,i,m)2⋅m!m)one can find two children x and y of Z such that{a mathematical formula}x∼ytogether with a renaming function{a mathematical formula}δx,ywhich certifies this.
     </paragraph>
     <paragraph label="Proof">
      Consider the following algorithm {a mathematical formula}A. First, {a mathematical formula}A computes a subset {a mathematical formula}Z′ consisting of exactly (arbitrarily chosen) {a mathematical formula}#C(ℓ,k,i,m)+1 children of Z. Then {a mathematical formula}A branches over all distinct pairs {a mathematical formula}x,y∈Z′ in time at most {a mathematical formula}O(#C(ℓ,k,i,m)2). Second, {a mathematical formula}A branches over all of the at most m! bijective renaming functions {a mathematical formula}δx,y. Third, {a mathematical formula}A computes {a mathematical formula}δx,y(F(Tx)) and tests whether it is equal to {a mathematical formula}F(Ty) (which takes at most {a mathematical formula}O(m) time); if this is the case, then {a mathematical formula}A terminates and outputs {a mathematical formula}x,y and {a mathematical formula}δx,y.We argue correctness. By Lemma 8 and due to the cardinality of {a mathematical formula}Z′, there must exist {a mathematical formula}x,y∈Z′ such that {a mathematical formula}x∼y. In particular, there must exist a renaming function {a mathematical formula}δx,y such that {a mathematical formula}δx,y(F(Tx))=F(Ty). But then {a mathematical formula}A is guaranteed to find such {a mathematical formula}x,y,δx,y since it performs an exhaustive search.  □
     </paragraph>
     <paragraph>
      Combining Lemma 7 and Lemma 9, we arrive at the following corollary.
     </paragraph>
     <paragraph label="Corollary 10">
      If{a mathematical formula}|Z|&gt;#C(ℓ,k,i,m)+1, then in time{a mathematical formula}O(#C(ℓ,k,i,m)2⋅m!m)one can compute a subinstance{a mathematical formula}I′=(F′,η)of I with strictly less variables and the following property: there exists a solution α of I of value{a mathematical formula}w=η(α)if and only if there exists a solution{a mathematical formula}α′of{a mathematical formula}I′of value w. Moreover, a solution α can be computed from any solution{a mathematical formula}α′in linear time.
     </paragraph>
     <paragraph label="Proof">
      In order to avoid having to consider all children of z, the algorithm first computes (an arbitrary) subset {a mathematical formula}Z′ of Z such that {a mathematical formula}|Z′|=#C(ℓ,k,i,m)+2. Then to be able to apply Lemma 9 without changing the set of solutions of I, the algorithm computes a subset {a mathematical formula}Z″ of {a mathematical formula}Z′ such that {a mathematical formula}|Z″|=#C(ℓ,k,i,m)+1 and for every {a mathematical formula}z′∈Z″ it holds that {a mathematical formula}sz″=0 for every {a mathematical formula}z″∈Tz′. Note that since there are at most k variables of I with non-zero coefficients in η and these variables form a clique in {a mathematical formula}GI, all of them occur only in a single branch of {a mathematical formula}Tz. It follows that {a mathematical formula}Z″ as specified above exists and it can be obtained from {a mathematical formula}Z′ by removing the (at most one) element {a mathematical formula}z′ in {a mathematical formula}Z′ with {a mathematical formula}sz″≠0 for some {a mathematical formula}z″∈Tz′. Observe that this step of the algorithm takes time at most {a mathematical formula}O(m⋅(#C(ℓ,k,i,m)+1)).The algorithm then proceeds as follows. It uses Lemma 9 to find two variables {a mathematical formula}x,y∈Z″ such that {a mathematical formula}x∼y and computes {a mathematical formula}I′ from I by omitting {a mathematical formula}Ty from I. The running time of the algorithm follows from Lemma 9 since the running times of the other steps of the algorithm are dominated by the application of Lemma 9. The corollary now follows from Lemma 7 and Lemma 9, which certify that:
     </paragraph>
     <list>
      <list-item label="•">
       there exists a solution α of I of value {a mathematical formula}w=η(α) if and only if there exists a solution {a mathematical formula}α′ of {a mathematical formula}I′ of value w, and
      </list-item>
      <list-item label="•">
       a solution α can be computed from any solution {a mathematical formula}α′ in linear time.  □
      </list-item>
     </list>
     <paragraph>
      Let {a mathematical formula}ei and {a mathematical formula}di for every i with {a mathematical formula}1≤i≤k be defined inductively by setting {a mathematical formula}ek=1, {a mathematical formula}dk=0, {a mathematical formula}di=#C(ℓ,k,i,si+1)+1, and {a mathematical formula}ei=diei+1+1. The following lemma shows that in time {a mathematical formula}O(|I|d12⋅e1!e1) one can compute an “equivalent” subinstance {a mathematical formula}I′ of I containing at most {a mathematical formula}e1 variables. Informally, {a mathematical formula}ei is an upper bound on the number of nodes in a subtree rooted at depth i and {a mathematical formula}di is an upper bound on the number of children of a node at level i in {a mathematical formula}I′.
     </paragraph>
     <paragraph label="Lemma 11">
      There exists an algorithm that takes as input I and T, runs in time{a mathematical formula}O(|I|d12⋅e1!e1)and outputs an ILP instance{a mathematical formula}I′containing at most{a mathematical formula}e1variables with the following property: there exists a solution α of I of value{a mathematical formula}w=η(α)if and only if there exists a solution{a mathematical formula}α′of{a mathematical formula}I′of value{a mathematical formula}w=η′(α′). Moreover, a solution α can be computed from any solution{a mathematical formula}α′in linear time.
     </paragraph>
     <paragraph label="Proof">
      The algorithm exhaustively applies Corollary 10 to every variable of T in a bottom-up manner, i.e., it starts by applying the corollary exhaustively to all variables at depth {a mathematical formula}k−1 and then proceeds up the levels of T until it reaches depth 1. Let {a mathematical formula}T′ be the subtree of T obtained after the exhaustive application of Corollary 10 to T.We will first show that if x is a variable at depth i of {a mathematical formula}T′, then x has at most {a mathematical formula}di children and {a mathematical formula}|Tx′|≤ei. We will show the claim by induction on the depth i starting from depth k. Because all variables x of T at level k are leaves, it holds that x has {a mathematical formula}0=dk children in {a mathematical formula}T′ and {a mathematical formula}|Tx′|=1≤ek, showing the start of the induction. Now let x be a variable at depth i of {a mathematical formula}T′ and let y be a child of x in {a mathematical formula}T′. It follows from the induction hypothesis that {a mathematical formula}|Ty′|≤ei+1. Moreover, using Corollary 10, we obtain that x has at most {a mathematical formula}#C˜(ℓ,k,i,ei+1)+1=di children in {a mathematical formula}T′ and thus {a mathematical formula}|Tx′|≤diei+1+1=ei, as required.The running time of the algorithm now follows from the observation that (because every application of Corollary 10 removes at least one variable of I) Corollary 10 is applied at most {a mathematical formula}|I| times and moreover the maximum running time of any call to Corollary 10 is at most {a mathematical formula}O(d12⋅e1!e1). Correctness and the fact that α can be computed from {a mathematical formula}α′ follow from Corollary 10; more specifically, we extend {a mathematical formula}α′ into α by assigning pruned variables in the same way as their equivalent counterparts.  □
     </paragraph>
     <paragraph label="Proof of Theorem 6">
      The algorithm proceeds in three steps. First, it applies Lemma 11 to reduce the instance I into an “equivalent” instance {a mathematical formula}I′ containing at most {a mathematical formula}e1 variables in time {a mathematical formula}O(|I|d12⋅e1!e1); in particular, a solution α of I can be computed in linear time from a solution {a mathematical formula}α′ of {a mathematical formula}I′. Second, it uses Theorem 1 to compute a solution {a mathematical formula}α′ of {a mathematical formula}I′ in time at most {a mathematical formula}O(e12.5e1+o(e1)⋅|I′|); because {a mathematical formula}e1 and {a mathematical formula}d1 are bounded by our parameters, the whole algorithm runs in FPT time. Third, it transforms the solution {a mathematical formula}α′ into a solution α of I. Correctness follows from Lemma 11 and Theorem 1.  □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Lower bounds and hardness
     </section-title>
     <paragraph>
      In this section we will complement our algorithmic results by providing matching hardness results. Namely, we will show that already the ILP-feasibility problem is {a mathematical formula}NP-hard on graphs of bounded treedepth and also {a mathematical formula}NP-hard on graphs of bounded treewidth and bounded maximum coefficient.{sup:1}
     </paragraph>
     <paragraph>
      We begin by noting that ILP-feasibility remains {a mathematical formula}NP-hard even if the maximum absolute value of any coefficient is at most one. This follows, e.g., by enhancing the standard reduction from the decision version of Vertex Cover (given a graph G and a bound ν, does G admit a vertex cover of size at most ν?) to ILP-feasibility as follows:
     </paragraph>
     <list>
      <list-item label="•">
       add variables {a mathematical formula}x1,…,xν and force each of them to be 1,
      </list-item>
      <list-item label="•">
       set {a mathematical formula}x=∑i∈[ν]xi,
      </list-item>
      <list-item label="•">
       add a constraint requiring that the sum of all variables which represent vertices of G is at most x.
      </list-item>
     </list>
     <paragraph label="Observation 1">
      ILP-feasibility is {a mathematical formula}NP-hard even on instances with a maximum absolute value of every coefficient of 1.
     </paragraph>
     <paragraph>
      To simplify the constructions in the hardness proofs, we will often talk about constraints as equalities instead of inequalities. Clearly, every equality can be written in terms of two inequalities.
     </paragraph>
     <paragraph label="Proof">
      ILP-feasibilityis{a mathematical formula}NP-hard even on instances of bounded treedepth.We will show the theorem by a polynomial-time reduction from the well-known {a mathematical formula}NP-hard 3-Colorability problem [16]: given a graph, decide whether the vertices of G can be colored with three colors such that no two adjacent vertices of G share the same color.The main idea behind the reduction is to represent a 3-partition of the vertex set of G (which in turn represents a 3-coloring of G) by the domain values of three “global” variables. The value of each of these global variables will represent a subset of vertices of G that will be colored using the same color. To represent a subset of the vertices of G in terms of domain values of the global variables, we will represent every vertex of G with a unique prime number and a subset by the value obtained from the multiplication of all prime numbers of vertices contained in the subset. To ensure that the subsets represented by the global variables correspond to a valid 3-partition of G we will introduce constraints which ensure that:
      <list>
       For every prime number representing some vertex of G exactly one of the global variables is divisible by that prime number. This ensures that every vertex of G is assigned to exactly one color class.For every edge {a mathematical formula}{u,v} of G it holds that no global variable is divisible by the prime numbers representing u and v at the same time. This ensures that no two adjacent vertices of G are assigned to the same color class.Following the construction and explanations provided above, it is not difficult to see that
      </list>
      <paragraph>
       I has a feasible assignment if and only if G has a 3-coloring. Indeed, for any 3-coloring of G, one can construct a feasible assignment of I by computing the prime-number encoding for the vertex sets that receive colors {a mathematical formula}1,2,3 and assign these three numbers to {a mathematical formula}g1,g2,g3, respectively. Such an assignment allows us to straightforwardly satisfy the constraints ensuring C1 holds (since each prime occurs in exactly one global constraint), the constraints ensuring C2 holds (since each edge is incident to at most one of each color) while maintaining the domain bounds.On the other hand, for any feasible assignment α, clearly each of {a mathematical formula}α(g1),α(g2),α(g3) will be divisible by some subset of prime numbers between 2 and {a mathematical formula}p(|V(G)|). In particular, since α is feasible it follows from the construction of our first group of constraints that each prime between 2 and {a mathematical formula}p(|V(G)|) divides precisely one of {a mathematical formula}α(g1),α(g2),α(g3), and so this uniquely encodes a corresponding candidate 3-coloring for the vertices of the graph. Finally, since α also satisfies the second group of constraints, this candidate 3-coloring must have the property that each edge is incident to exactly 2 colors, and so it is in fact a valid 3-coloring.It remains to show that the treedepth of I is at most 8. We will show this by using the characterization of treedepth given in Proposition 4. We first observe that the graph {a mathematical formula}GI∖{g1,g2,g3} consists of the following components:
      </paragraph>
      <list>
       <list-item label="•">
        for every i with {a mathematical formula}1≤i≤|V(G)|, one component on the vertices {a mathematical formula}mi,1,…,mi,3, {a mathematical formula}ri,1,ri,2,ri,3, {a mathematical formula}ui,1,ui,2,ui,3. Note that all of these components are isomorphic to each other and we will therefore in the following refer to these components as vertex-type components;
       </list-item>
       <list-item label="•">
        for every {a mathematical formula}e={w,v}∈E(G) and j with {a mathematical formula}1≤j≤3, one component on the vertices {a mathematical formula}me,w,j, {a mathematical formula}me,v,j, {a mathematical formula}re,w,j, {a mathematical formula}re,v,j, {a mathematical formula}ue,w,j, and {a mathematical formula}ue,v,j. Note that all of these components are isomorphic to each other and we will therefore in the following refer to these components as edge-type components.
       </list-item>
      </list>
      <paragraph>
       The two types of components are illustrated in Fig. 1. We will show next that any vertex-type component has treedepth at most 5 and every edge-type component has treedepth at most 4. This would then imply that {a mathematical formula}GI has treedepth at most 8 (since it suffices to remove the vertices {a mathematical formula}{g1,g2,g3} in order to decompose the graph into these components). Hence let i with {a mathematical formula}1≤i≤|V(G)| and consider the vertex-type component {a mathematical formula}Ci on the vertices {a mathematical formula}mi,1,mi,2,mi,3, {a mathematical formula}ri,1,ri,2,ri,3, {a mathematical formula}ui,1,ui,2,ui,3. Note that {a mathematical formula}Ci∖{ui,1,ui,2,ui,3} consists of one component for every j with {a mathematical formula}1≤j≤3 that contains the vertices {a mathematical formula}mi,j and {a mathematical formula}ri,j. Clearly each of these three components has treedepth at most 2 and hence the treedepth of {a mathematical formula}Ci is at most {a mathematical formula}2+3=5, as required.In order to show that every edge-type component has treedepth at most 4, consider an edge {a mathematical formula}e={w,v}∈E(G) and some j satisfying {a mathematical formula}1≤j≤3. Let {a mathematical formula}Ce,j be the edge-type component consisting of the vertices {a mathematical formula}me,w,j, {a mathematical formula}me,v,j, {a mathematical formula}re,w,j, {a mathematical formula}re,v,j, {a mathematical formula}ue,w,j, and {a mathematical formula}ue,v,j. Note that {a mathematical formula}Ce,j∖{ue,w,j,ue,v,j} consists of two components, one containing the vertices {a mathematical formula}me,w,j and {a mathematical formula}re,u,j and one containing the vertices {a mathematical formula}me,v,j and {a mathematical formula}re,v,j. Clearly, each of these two components has treedepth at most 2 and hence the treedepth of {a mathematical formula}Ce,j is at most {a mathematical formula}2+2=4, as required.  □
      </paragraph>
     </paragraph>
     <paragraph label="Claim 1">
      The next theorem shows that ILP-feasibility is paraNP -hard parameterized by both treewidth and the maximum absolute value of any number in the instance; observe that since we are bounding all numbers in the instance, the theorem in particular implies {a mathematical formula}NP-hardness. We note that the idea to reduce from Subset Sum was inspired by previous work of Jansen and Kratsch [20]. ILP-feasibilityis{a mathematical formula}NP-hard even on instances with treewidth at most two and where the maximum absolute value of any coefficient is at most one.We show the result by a polynomial reduction from the Subset Sum problem, which is well-known to be weakly {a mathematical formula}NP-complete. {an inline-figure} Let {a mathematical formula}I:=(Q,r) with {a mathematical formula}Q:={q1,…,qn} be an instance of Subset Sum, which we assume to be given in binary encoding. We will construct an instance {a mathematical formula}I′ of ILP-feasibility equivalent to I in polynomial-time (with respect to the input size of I) with treewidth at most 2 that uses only −1, 0, and 1 as coefficients. Crucial to our construction are the following auxiliary ILP instances.For every {a mathematical formula}q∈N and any two variables x and y there is an ILP instance {a mathematical formula}I(q,x,y) satisfying the following conditions:
      <list>
       {a mathematical formula}I(q,x,y) has at most {a mathematical formula}O(log⁡q) variables and constraints,the maximum absolute value of any coefficient in {a mathematical formula}I(q,x,y) is at most one,the treewidth of {a mathematical formula}I(q,x,y) is at most two andfor every feasible assignment α of {a mathematical formula}I(q,x,y), it holds that {a mathematical formula}α(y)∈{α(x),α(x)+q}.We now obtain
      </list>
      <paragraph>
       {a mathematical formula}I′ as the (non-disjoint) union of the instances {a mathematical formula}I(q1,y1), {a mathematical formula}I(qi,yi−1,yi) for every i with {a mathematical formula}1&lt;i≤n, and the instance {a mathematical formula}IC(r,yn) (see Fig. 3 for an illustration of {a mathematical formula}I′). The size of each of these {a mathematical formula}n+1 instances is bounded by {a mathematical formula}O(log⁡m), where m is the maximum of {a mathematical formula}{q1,…,qn,r}, and it can be verified that each of these instances can be constructed in time {a mathematical formula}O(log⁡m). Hence the construction of {a mathematical formula}I′ from I can be completed in polynomial time (with respect to the size of the binary encoding of I). We also observe that the maximum absolute value of any coefficient in {a mathematical formula}I′ is at most 1. Finally, because {a mathematical formula}I′ is a simple concatenation of ILP instances with treewidth at most 2, it is straightforward to verify that {a mathematical formula}I′ has treewidth at most 2.  □
      </paragraph>
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>