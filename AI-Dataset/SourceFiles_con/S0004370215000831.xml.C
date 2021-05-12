<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A flexible ILP formulation for hierarchical clustering.
   </title>
   <abstract>
    Hierarchical clustering is a popular approach in a number of fields with many well known algorithms. However, all existing work to our knowledge implements a greedy heuristic algorithm with no explicit objective function. In this work we formalize hierarchical clustering as an integer linear programming (ILP) problem with a natural objective function and the dendrogram properties enforced as linear constraints. Our experimental work shows that even for small data sets finding the global optimum produces more accurate results. Formalizing hierarchical clustering as an ILP with constraints has several advantages beyond finding the global optima. Relaxing the dendrogram constraints such as transitivity can produce novel problem variations such as finding hierarchies with overlapping clusterings. It is also possible to add constraints to encode guidance such as must–link, cannot–link, must–link–before etc. Finally, though exact solvers exist for ILP we show that a simple randomized algorithm and a linear programming (LP) relaxation can be used to provide approximate solutions faster.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A survey [1] of applications of clustering showed that in published scientific articles, hierarchical algorithms are used far more than non-hierarchical clustering. However, most algorithmic research and papers focus on non-hierarchical (partitional) clustering. Applications of hierarchical clustering typically can be divided into those that build large trees so that, for instance, a user can navigate a large collection of click-stream behavior, and those that build trees to represent a scientific process, such as phylogenetic trees (evolutionary trees). We can further differentiate these works by noting that the data collected for the first type of application is easy to collect and hence voluminous, whilst the later application typically takes much time to collect and are typically small.
     </paragraph>
     <paragraph>
      Our own earlier work [2] showed how to scale hierarchical clustering using hashing to huge data sets. In this paper the focus is the latter category of applications involving a small number of instances which took a long time to collect and which must be thoroughly analyzed. This means that spending hours for an algorithm to run is not uncalled for since a precise answer is worth the wait. Colloquially, going back to our examples, no one will complain if a dendrogram places click-streams in a good but non-optimal ordering but will if species are shown to evolve in the wrong order.
     </paragraph>
     <paragraph>
      Hierarchical clustering algorithms remain relatively under-studied with most algorithms being relatively straight-forward greedy algorithms implemented in procedural language. For example, in the above mentioned survey most implementations mentioned were simple agglomerative algorithms (see Fig. 1) that start with each instance in a cluster by itself and then the closest two clusters are merged at each and every level. Even more advanced methods published in the database literature such as CLARANS and DBSCAN [3] still use this base approach but have more complex distance measures or methods to build the tree iteratively. Whereas non-hierarchical clustering algorithms have moved to elegant linear algebra formulations such as spectral clustering [4] hierarchical clustering has not.
     </paragraph>
     <paragraph>
      Contributions. In this work we provide the first formalization of agglomerative clustering as an ILP problem (for a general introduction to the topic see [5] and for an example of an application of ILP to the non-hierarchical clustering data mining problem see [6]). Formulating the problem as an ILP allows the use of high quality solvers (free and commercial) such as CPLEX and Gurobi (used in all our experiments) to find solutions and automatically take advantage of multi-core architectures. Formulating the problem as an ILP has a number of additional benefits that we now briefly discuss and provide details of later.
     </paragraph>
     <list>
      <list-item label="•">
       Explicit Global Objective Function Optimizing. As mentioned most existing work greedily determines the best join at each and every level of the hierarchy. At no time is it possible to reset or revisit an earlier join. This is adequate when a “near enough” dendrogram is required, such as building a tree to organize song lists. Finding the global optima is more important when the data represents a physical phenomenon. This is discussed in the Section Hierarchical Clustering as an ILP, and we show this produces comparable or better quantitative results for scientific data sets such as language evolution in Table 3 and for hierarchical organization of fMRI scans in Table 4.
      </list-item>
      <list-item label="•">
       Novel Problem Variations with Relaxing Constraints. A side benefit of formalizing hierarchy learning is that the properties of a legal dendrogram are explicitly modeled as constraints to the optimization. We will show how novel problem variations can arise if some constraints are relaxed. In particular we show that relaxing the transitivity property allows for overlapping hierarchical clustering, that is, an instance can appear multiple times at the same level in the hierarchy and is akin to overlapping clustering. To our knowledge the problem of building dendrograms when an object appears multiple times is understudied [7]. This topic is explored in the Section Relaxed Problem Settings. In Fig. 8 we show empirically that our method is capable of discovering overlapping hierarchies.
      </list-item>
      <list-item label="•">
       Novel Forms of Guidance By Adding Constraints. The area of constrained clustering [8], [9], [10] has typically added constraints to procedural implementations. Here we show how we can add a number of typically used data mining constraints {a mathematical formula}must–link, {a mathematical formula}cannot–link, and {a mathematical formula}must–link–before as linear constraints. This topic is explored in the Section Adding Guidance and in Fig. 9 we show this can obtain even better empirical results.
      </list-item>
      <list-item label="•">
       Approximation Schemes. Finding the global optima to an intractable problem by definition must be time consuming. However, a large literature exists on general methods to create approximate methods for ILPs. We provide two initial steps in that direction by exploiting a simple randomized algorithm that can create a factor two approximation scheme. We also explore using LP relaxations and randomized rounding. Fig. 10 shows the empirical results of how well our LP relaxation and randomized rounding scheme compares to the optimal solution.
      </list-item>
     </list>
     <paragraph>
      We organize the paper as follows. In Section 2 we describe our ILP formulation of hierarchical clustering. In Section 3 we describe an interesting variant of this formulation that allows us to learn overlapping hierarchical clustering by relaxing some of the constraints. Adding guidance that can encode domain knowledge or problem constraints in the form of additional ILP constraints is explored in Section 4. Section 5 describes two approximation algorithms to our overlapping hierarchical clustering algorithms. Finally in Section 6 we describe the questions we attempted to answer through empirical analysis and described the methods we devised to solve them as well as our results.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Hierarchical clustering as an ILP
     </section-title>
     <paragraph>
      In this section, we discuss how to formulate hierarchical clustering as an ILP problem. We begin with a brief introduction of hierarchical clustering that can be skipped by the informed reader.
     </paragraph>
     <section label="2.1">
      <section-title>
       A brief introduction to agglomerative hierarchical clustering
      </section-title>
      <paragraph>
       Agglomerative hierarchical clustering algorithms take as input a distance function and create a dendrogram, which is a tree structure which can be interpreted as a k-block set partition for each value of k between 1 and n, where n is the number of data points to cluster. These algorithms not only allow a user to choose a particular clustering granularity, but in many domains [11], [12], [13] clusters naturally form a hierarchy; that is, clusters are part of other clusters such as in the case of phylogenetic (evolutionary) trees. The popular agglomerative algorithms are easy to implement as they just begin with each point in its own cluster and progressively join two closest clusters to reduce the number of clusters by 1 until {a mathematical formula}k=1. The basic agglomerative hierarchical clustering, which our method is compared to in this paper, is shown in Fig. 1.
      </paragraph>
      <paragraph>
       This algorithm is very popular and was first postulated in the 1950s and 60s in the numerical taxonomy literature [14], [7]. Though useful they are unlike most modern machine learning methods since they were not derived to optimize an objective function. In comparison consider non-hierarchical clustering methods such as spectral clustering, k-means and mixture models. Each has an explicit object function: graph min-cut, vector quantization error, maximum likelihood respectively, and their algorithms are derived to optimize this function. Our purpose in this paper is to move hierarchical clustering forward by explicitly deriving an objective function and optimizing it. We have chosen an ILP formulation since our focus is on exact optimization.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Solving hierarchical clustering
      </section-title>
      <paragraph>
       Using ILP allows us to formally define an objective function and then find globally optimal solutions to hierarchical clustering problems. The two challenges to an ILP formulation are: i) ensuring that the resultant solution is a legal dendrogram; and ii) encoding a useful objective function. To address the former challenge, we must model the dendrogram as a collection of variables, those variables are clearly dependent on each other and we must formalize this relationship. For the later, we must use these same variables to define a meaningful objective function.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Enforcing a legal dendrogram
      </section-title>
      <paragraph>
       In this section, we describe how a function (referred to as merge or as {a mathematical formula}M within the ILP formulation), representable using {a mathematical formula}O(n2) integer variables (where n is the number of instances), can represent any dendrogram. The variables represent what level a pair of instances are first joined at and the constraints described in this section enforce that these variables obey this intended meaning. The merge function is described in Definition 1 as follows.
      </paragraph>
      <paragraph label="Definition 1">
       Merge function{a mathematical formula}
      </paragraph>
      <paragraph>
       In this work we will learn this function. For a particular instance pair {a mathematical formula}a,b the intended meaning of {a mathematical formula}merge(a,b)=ℓ is that instances {a mathematical formula}a,b are in the same cluster at level ℓ (and higher) of the corresponding dendrogram, but not at level {a mathematical formula}ℓ−1 and lower. Therefore the domain of the merge function is all pairs of instances and the range is the integers between zero (tree bottom) and the maximum hierarchy level L (tree top).
      </paragraph>
      <paragraph>
       The fact that any dendrogram from standard hierarchical clustering algorithms can be represented using this scheme is clear, but it is not the case that any such merge function represents a legal dendrogram. Consider a simple example with three instances {a mathematical formula}a,b,c and with {a mathematical formula}merge(a,b)=1, {a mathematical formula}merge(a,c)=2 and {a mathematical formula}merge(b,c)=3. Such a merge function does not represent a legal dendrogram because it does not obey transitivity. To ensure we learn a legal dendrogram we must encode the following partition properties: reflexivity, symmetry, and transitivity (Definition 2, Definition 3, Definition 4). Later we shall see how to enforce these requirements as linear inequalities in an ILP.
      </paragraph>
      <paragraph label="Definition 2">
       ReflexivityAn instance is always in the same cluster as itself.{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 4">
       SymmetryIf instance a is in the same cluster as instance b then instance b is also in the same cluster as instance a.{a mathematical formula}Hierarchy and transitivityIf instance a is in the same cluster as instance b at level q and b is in the same cluster as c at level r, then a must be in the same cluster as c at level q or r (which-ever is largest).{a mathematical formula}
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Hierarchical clustering objective
      </section-title>
      <paragraph>
       The objective for agglomerative hierarchical clustering is traditionally specified as a greedy process where clusters that are closest together are merged at each level as shown in Fig. 1. These objectives are called linkage functions (e.g. single [15], complete [16], UPGMA [17], WPGMA [18]) and effectively define a new distance function ({a mathematical formula}d(i,j) in Fig. 1) to decide which clusters are closest and should therefore be merged next. The intuition behind this process can be interpreted to mean that points that are close together should be merged together before points that are far apart. Our work formalizes this intuition into an ILP.
      </paragraph>
      <paragraph>
       {a mathematical formula}
      </paragraph>
      <paragraph>
       To formalize that intuition we created an objective function that favors hierarchies where closer points are joined before further-away points. For example if {a mathematical formula}D(a,c) (distance between a and c) is larger than {a mathematical formula}D(a,b) then the points a and c should be merged after the points a and b are merged. This would require the merge function learnt to have {a mathematical formula}merge(a,b)&lt;merge(a,c). Though learning the merge function directly allows us to recover the dendrogram easily, it is difficult to define an objective around it. Hence, we introduce the binary variable {a mathematical formula}Oabc which is set to TRUE (value one) if the instances a and b are merged before a and c are merged. In our formulation we must constrain O and merge so they are consistent with each other. We need both sets of variables since O is useful for specifying the objective function but difficult to specify the properties of a hierarchy on, and merge is challenging to specify an objective function on but useful for specifying the properties of a hierarchy. To complete the objective function we introduce {a mathematical formula}wabc a non-binary variable which indicates how close a and b are compared to a and c. In our experiments we set {a mathematical formula}wabc=D(a,c)−D(a,b) which means it is set to 0 if a and b are equal distance to a and c and a positive (negative) number if they are closer (further). We can interpret {a mathematical formula}wabc as being a reward if positive or a penalty if negative. Fig. 2 gives an example of how our objective works and Eqs. (1), (2), (3) define it formally.{a mathematical formula} where:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       It should be noted that in all our experiments O is optimized over and w is a constant that is derived from the distance function D. However, in practice, w could be provided by a human expert either partially or completely. In the former case we would optimize over the not specified values of w which can be considered as a semi-supervised setting in that for some triplets you don't know their distance relationships but learn them. Using these variables allows an objective function to maximize shown formally in Equation (1) which captures the intuition of agglomerative hierarchical clustering (join closer points together before further points). An ILP it will find the global optimum rather than converge to a local optimum since the ILP does not gradually build up the solution as greedy heuristic methods do.
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       ILP transformation
      </section-title>
      <paragraph>
       Now that we have presented a global objective function for hierarchical clustering we will address how to find globally optimum legal hierarchies by translating the problem into an integer linear program (ILP). Fig. 3 shows at a high level the optimization problem we are solving.
      </paragraph>
      <paragraph>
       Fig. 4 shows the ILP equivalent of the problem in Fig. 3. To ensure that {a mathematical formula}M is a legal merge function we need to ensure the resultant hierarchy is legal. This requires encoding the constraints to enforce the previously mentioned properties of reflexivity, symmetry, and transitivity properties (Definition 2, Definition 3, Definition 4). Recall that {a mathematical formula}M can be represented as square matrix of {a mathematical formula}n×n variables indicating at what level a pair of points are joined. Then reflexivity and symmetry are both easily enforced by removing redundant variables from the matrix, in particular removing all diagonal variables for reflexivity, and all lower triangle variables for symmetry. Transitivity can be turned into a set of linear constraints by noticing that the previously mentioned inequality {a mathematical formula}max(M(a,b),M(b,c))≥M(a,c) is logically equivalent to:{a mathematical formula}
      </paragraph>
      <paragraph>
       In the final ILP (Fig. 4) there is a variable Z introduced for each clause/inequality from Equation (4) (i.e. {a mathematical formula}Zab≥ac and {a mathematical formula}Zbc≥ac) and there are three constraints added to enforce that the disjunction of the inequalities is satisfied. Constraints are also added to ensure that the O variables and the variables in {a mathematical formula}M are consistent.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Relaxed problem settings – removing constraints
     </section-title>
     <paragraph>
      A benefit of formalizing hierarchy building is that individual parts of the formulization can be relaxed. Here we explore two aspects of relaxation. Firstly, we can relax the formal definitions of a legal hierarchy to obtain novel problem settings. In particular we consider the effect of relaxing the transitivity constraint of our ILP formulation of hierarchical clustering. Relaxing transitivity allows a form of hierarchical clustering where instances can appear in multiple clusters at the same level (i.e. overlapping clustering). Secondly, we relax the integer constraints so that we can create approximation algorithms by relaxing the problem into an LP and using randomized rounding schemes (see Section 5).
     </paragraph>
     <section label="3.1">
      <section-title>
       Overlapping hierarchies
      </section-title>
      <paragraph>
       If the transitivity property is satisfied then the clusters at each level in the hierarchy can be obtained by computing the connected components over the pairwise together relations obtained from the relation {a mathematical formula}M. For any level ℓ we say two points a and b are together if {a mathematical formula}M(a,b)≤ℓ and then compute transitive closure over the together relation. Furthermore, for a legal/standard hierarchy the set of maximal cliques will be the same as the set of connected components (because the together relation will be transitive for a hierarchy), which motivates our use of maximal cliques for non-transitive hierarchies. When the transitivity property of the merge function is relaxed, the clusterings corresponding to each level of the dendrogram found by taking the maximal cliques of the level's together relation will no longer necessarily be set a partitions. Clustering over non-transitive relations/graphs is common in the community detection literature [19] where overlapping clusters are learned by finding all maximal cliques in the graph (or weaker generalizations of maximal clique). We use this same approach in our work, finding maximal cliques for each level in the hierarchy to create a sequence of overlapping clusterings.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Overlapping clustering objective
      </section-title>
      <paragraph>
       Rather than completely relaxing the transitivity requirement we allow transitivity to be violated with a penalty. Intuitively graphs in which transitivity is better satisfied will lead to simpler overlapping clusterings. We therefore added transitivity in the objective function (rather than having it as a constraint) as shown in Equation (5) which introduces a new variable {a mathematical formula}Tabc (Equation (6)) whose value reflects whether the instance triple {a mathematical formula}a,b,c obeys transitivity. We also introduce a new weight {a mathematical formula}wt which specifies how important transitivity will be to the objective. To ensure transitivity we set {a mathematical formula}wt to be very large and to ignore it we set {a mathematical formula}wt=0.{a mathematical formula}{a mathematical formula} The full ILP, with the new objective presented in Equation (5) and relaxed transitivity, is presented in Fig. 5.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Adding guidance – adding constraints
     </section-title>
     <paragraph>
      Guidance constraints such as {a mathematical formula}must–link, {a mathematical formula}cannot–link, and {a mathematical formula}must–link–before constraints can be used to encode domain knowledge or problem constraints into otherwise unsupervised problems such as hierarchical clustering. Previous work showed that hierarchical clustering results can benefit from the addition of these constraints [20], [21], [22], but all previous work relied on ad-hoc schemes to integrate constraint solving into agglomerative clustering algorithms. An advantage to our ILP formulation of hierarchical clustering is that data mining constraints can be added naturally by encoding them as linear constraints, which is straight forward.
     </paragraph>
     <paragraph>
      Encoding Global Must-Link and Cannot-Link Constraints. A global {a mathematical formula}cannot–link (CL) or {a mathematical formula}must–link (ML) constraint, specifies that two instances must be together or apart throughout the entire hierarchy. For {a mathematical formula}must–link, this implies that the points must have be joined from the very first level of the hierarchy as shown in Equation (7). Typically a global {a mathematical formula}cannot–link constraint would specify that two points can never be together anywhere in the hierarchy, and thus a single {a mathematical formula}cannot–link constraint will lead to a non-full tree hierarchy (a forest). Since in this work, we do not attempt to model non-full tree hierarchies we instead use this constraint to specify that two points cannot be merged until the highest level (the root) as show in Equation (8).{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Encoding Local Must-Link and Cannot-Link Constraints. While global {a mathematical formula}cannot–link or {a mathematical formula}must–link constraints have been shown to improve the performance of hierarchical clustering, they were designed for flat clustering and do not take into account the hierarchical nature of a dendrogram. Local {a mathematical formula}cannot–link ({a mathematical formula}CLi) or {a mathematical formula}must–link ({a mathematical formula}MLi) constraints were created to allow these constraints to address particular levels in a hierarchy. For example {a mathematical formula}MLi(a,b) specifies that points a and b must be together at level i in the hierarchy (or sooner) which is shown in Equation (9). Likewise {a mathematical formula}CLi(a,b) specifies that a and b cannot be together at level i (in other words they must be merged later) as is shown in Equation (10).{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Encoding Local Must-Link-Before Constraints. Another constraint type that was specifically devised for hierarchical clustering is the {a mathematical formula}must–link–before (MLB) constraints [23]. In some ways this constraint is less powerful than local {a mathematical formula}must–link constraints because they only specifies the relative ordering of how points should be merged. However in practice local constraints are difficult to specify whereas it is generally easy to specify a {a mathematical formula}must–link–before constraint. As Equation (11) shows, the definition of {a mathematical formula}MLB(a,b,c) is that points a and b must be merged before a and c or b and c.{a mathematical formula}
     </paragraph>
     <paragraph>
      The simplification of the conjunction in Equation (11) is logically equivalent because of the properties of a hierarchy that {a mathematical formula}M obeys. If {a mathematical formula}M(a,b)&lt;M(a,c) then {a mathematical formula}M(a,c)=M(b,c) due to the nature of hierarchies, and therefore {a mathematical formula}M(a,b)&lt;M(b,c).
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Scaling our method
     </section-title>
     <paragraph>
      There are many methods to scale ILPs [24]. These can be divided into two categories, those that still find an exact solution and those that find an approximation. In the first category we explore a simple cutting plane method and in the second category we explore the LP relaxation and corresponding approximation bounds.
     </paragraph>
     <section label="5.1">
      <section-title>
       A cutting plane method
      </section-title>
      <paragraph>
       The cutting plane idea relies on the assumption that not all constraints are required to find the optimal solution and not encoding those not required can greatly improve run-time performance. This is indeed the case for our work since the transitivity constraints are not all required. Consider two extreme (far away) points. Our formulation in Fig. 4 will encode a constraint for transitivity between these points and other similarly extreme points even though they won't be part of the same cluster if we perform {a mathematical formula}N−1 merges instead of N merges. The iterative method we discuss below can exploit such superfluous constraints to reduce the total number of constraints given to the ILP solver.
      </paragraph>
      <list>
       <list-item label="1.">
        Set up and solve an ILP (which we shall call F) as shown in Fig. 4 except do not include constraints (5), (6) and (7). Call the solution S.
       </list-item>
       <list-item label="2.">
        Let Q be the set of constraints from (5), (6) and (7) in Fig. 4 that S violates.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}Q=∅ then S is the optimal solution to the original problem in Fig. 4 else add Q to F and solve. Call the solution S and go to step 2.
       </list-item>
      </list>
      <paragraph>
       How well this method scales will depend on the data set properties. In our experiments it produced a 8, 23 and 78 fold speed up for the language, movie and newsgroup data sets. For even larger data sets we expect even greater speed ups since the number of transitivity constraints is related to the number of points.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Polynomial time approximation algorithms
      </section-title>
      <paragraph>
       In this sub-section we consider some theoretical results for approximations of the ILP formulation presented in Fig. 5 (i.e. the overlapping hierarchy formulation). This formulation allows transitivity to be violated, and has an interpretation that allows any variable assignment to be translated into a valid hierarchy (with overlapping clusters).
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Factor two approximation
       </section-title>
       <paragraph label="Theorem 1">
        Let{a mathematical formula}M0be created by independently sampling each value from the uniform distribution{a mathematical formula}{1…L}, and{a mathematical formula}M⁎be the optimal solution to ILP inFig. 5. Then{a mathematical formula}E[f(M0)]≥L−12Lf(M⁎).
       </paragraph>
       <paragraph label="Proof">
        {a mathematical formula}  □
       </paragraph>
       <paragraph>
        Note that in the proof we use the following results for the values of {a mathematical formula}E[Oabc] and {a mathematical formula}E[Tabc]:{a mathematical formula}{a mathematical formula} The bound {a mathematical formula}E[f(M0)]≥L−12Lf(M⁎) is a constant given L (parameter specifying number of levels in hierarchy), and will generally be close to one half since the number of levels L is typically much greater than 2.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        LP relaxation
       </section-title>
       <paragraph>
        The problem in Fig. 5 can be solved as a linear program by relaxing the integer constraints, but the resulting solution, {a mathematical formula}Mf⁎ will not necessarily have all integer values. Given such a solution, we can independently round each value up with probability {a mathematical formula}Mf⁎(a,b)−⌊Mf⁎(a,b)⌋ and down otherwise. The expectation of the objective value for the LP relaxation can be calculated and in the experimental section we calculate both optimal integer solutions and the expectation for this simple rounding scheme. Fig. 10 shows that their difference is usually very small. If {a mathematical formula}M0 is the solution created by rounding {a mathematical formula}Mf⁎, then the expectation can be calculated as:{a mathematical formula} The expectation for each variable (T and O) breaks down into a piecewise function. The expectation for {a mathematical formula}Oabc is listed below. This variable relies on the ordering of {a mathematical formula}Mf⁎(a,b) and {a mathematical formula}Mf⁎(a,c). When those variables are far apart (e.g. distance of 2 or greater) then rounding them will not change the value of {a mathematical formula}Oabc. When they are close the value of {a mathematical formula}Oabc will depend on how they are rounded, which breaks down into two cases depending on whether {a mathematical formula}Mf⁎(a,b) and {a mathematical formula}Mf⁎(a,c) are in the same integer boundary.{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        The expectation for {a mathematical formula}Tabc can be calculated using similar reasoning but it is not listed here because it breaks down into a piecewise function with more cases and is very large.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      Here we overview our data sets, research questions, and experiments in that order. As in our previous work the code and data sets will be made available to aid in reproducibility of our results.
     </paragraph>
     <section label="6.1">
      <section-title>
       Data sets and performance measures
      </section-title>
      <paragraph>
       In keeping with the motivation of our work, these data sets are difficult to obtain so the time to find the global optimum is justified. For example, the fMRI study took many years to collect (it is a longitudinal study), the language data set is unique, and the movie data set can only grow by a few hundred instances per year.
      </paragraph>
      <section label="6.1.1">
       <section>
        <section-title>
         Languages data set
        </section-title>
        <paragraph>
         The language data set contains phonological, morphological, lexical character usage of twenty four historic languages [25] (http://www.cs.rice.edu/~nakhleh/CPHL/). We chose this data set because it allowed us to test our method's ability to find a ground truth hierarchy from high dimensional data (each instance is represented by over 200 features). These languages are known to have evolved from each other with scientists agreeing upon the ground truth. In such problem settings, finding the exact order of evolution of the entities (in this case languages) is important and even small improvements are considered significant.
        </paragraph>
       </section>
       <section>
        <section-title>
         fMRI data set
        </section-title>
        <paragraph>
         An important problem in cognitive research is determining how brain behavior contributes to mental disorders such as dementia. We use a set of one hundred fMRI brain scans of patients who had also been given a series of cognitive tests/scores by doctors. These scores can be used to organize the patients into a natural hierarchy based on their mental health status and forms our ground truth hierarchy. We can then cluster the fMRI scans and see how well the hierarchy obtained from the scans matches the hierarchy obtained from the cognitive scores. Once again finding the best hierarchy is important since it can be used to determine those most at risk without the need for time consuming tests/scores. Each scan consists of brain activity mapped onto a {a mathematical formula}63×52×72 grid over 200+ time steps. Thus each instance consists of over 500,000 columns and is an example of an extremely high dimensional data set.
        </paragraph>
       </section>
       <section>
        <section-title>
         Movie lens
        </section-title>
        <paragraph>
         The Movie Lens data set [26] is a subset of one thousand user ratings of movies. This data set is of interest because each movie also has a set of associated genres, and the sets of movies belonging to each genre typically have a very high overlap. For example romantic-comedy movies will belong to two genres as well as science fiction horror films. Thus traditional hierarchical algorithms cannot easily discover these overlapping hierarchies as they require each data point (movies in this case) to appear only once at each level. In contrast our methods allow a data point to appear multiple times at each level and hence the one movie can appear in the romance part of the tree as well as the comedy part of the tree if it were a romantic comedy.
        </paragraph>
        <paragraph>
         We created overlapping ground truth hierarchies from all the genres and cross-genres (e.g. romantic comedy, action comedy) and tested our method's ability to find these overlapping clusterings as compared to standard agglomerative clustering methods.
        </paragraph>
       </section>
       <section>
        <section-title>
         20 newsgroups
        </section-title>
        <paragraph>
         The 20 Newsgroups dataset is a collection of one thousand documents that are known to be organized into a hierarchy that is shown in Table 2.
        </paragraph>
       </section>
       <section>
        <section-title>
         Artificial data set
        </section-title>
        <paragraph>
         We created three artificial hierarchical clustering data sets with a known ground truth hierarchies, so that we could use them to precisely answer important questions about our new hierarchical clustering formulation. Since we often injected noise into our experiments many times we created small data sets so experiments can be repeated many times.
        </paragraph>
        <list>
         <list-item label="1.">
          The first artificial hierarchy we created had 80 instances, 4 levels, was a balanced tree, and did not have overlapping clusterings. The ground truth hierarchy for this dataset was therefore always the same. We can turn the hierarchy into a pairwise distance matrix with the distance between two points a and b being the level of their first common ancestor. We increased the complexity of this dataset by increasingly adding uniform error to the distances. We used this data set to evaluate our basic ILP formulation which enforced transitivity (Fig. 4) and compared the results with standard hierarchical clustering algorithms (single, complete, UPGMA, WPGMA).
         </list-item>
         <list-item label="2.">
          The second artificial data set was created very similarly to the first, in that it also had 80 instances, 4 levels and was balanced, but each of the clusters on the highest non-root level shared 50% of their instances with another cluster (overlap). We increased the challenge of the problem by increasingly adding uniform error to the distance matrix.
         </list-item>
         <list-item label="3.">
          The third set of artificial datasets was different than the previous two. We created a random ground truth hierarchies by first creating a random distance matrix and then applying a single linkage agglomerative clustering algorithm to learn the ground truth hierarchy. We then added increasing random uniform error to increase the complexity of the problem.
         </list-item>
        </list>
       </section>
      </section>
      <section label="6.1.2">
       <section-title>
        Performance measures
       </section-title>
       <paragraph>
        We use two standard measurements to evaluate our algorithm.
       </paragraph>
       <section>
        <section-title>
         H-correlation
        </section-title>
        <paragraph>
         The H-Correlation [23] measures the distance to a ground truth hierarchy with a value of 1 being an exact perfect match and is formally defined as:{a mathematical formula} Where {a mathematical formula}MGT is the ground truth hierarchy, {a mathematical formula}ML is the learned hierarchy that is being evaluated and δ is a Kronecker delta function. The more the relative order of hierarchical distances agree between the learned and ground truth hierarchy, the higher the H-Correlation.
        </paragraph>
       </section>
       <section>
        <section-title>
         F1 score
        </section-title>
        <paragraph>
         The F1 score is commonly used to compare clustering results to ground truth clusters by first matching the clusters from the two different sets and then calculating:{a mathematical formula} We measured F1 score by first calculating the set of all clusters generated within the ground truth and learned dendrograms, and then matching the learned clusters with the best true clusters. The matching between the clusters from the learned hierarchy and the ground truth hierarchy was created so that it maximized the total F1 score.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="6.2">
      <section-title>
       Questions
      </section-title>
      <paragraph>
       Our contributions are formulating hierarchical clustering as an optimization problem, hence we begin our experiments with the question: 1. Does our global optimization formulation of hierarchical clustering provide better results than greedy algorithms? Our results in Table 3, Table 4 show that our method outperforms standard hierarchical clustering for real world language evolution and fMRI data sets for finding the best hierarchy (matching the ground truth). Furthermore, Fig. 6 show that for artificial data sets our method performs better than existing greedy algorithms when the data set contains noise in the pairwise distances. This is a likely situation as the distances are typically measured via the instance features which may be corrupt or contain errors.
      </paragraph>
      <paragraph>
       We also explore the novel idea of overlapping hierarchies, which raises the next experimental question: 2. Can our method find overlapping clusters in datasets?Fig. 8 shows the results of our method on Artificial Dataset 2 which was created to contain overlapping clusters. Table 5 shows the results for a real data set of movies where overlapping clusters naturally occur due to multiple genres and the results show that our method had better average results as well as a smaller variance than all of the agglomerative clustering algorithms. Finally, Table 6 shows our methods ability to find crosspostings (messages that belong to two different newsgroups/forum topics) with the 20 Newsgroup dataset.
      </paragraph>
      <paragraph>
       3. Does the addition of constraints improve performance and run time of the algorithms? Most work on adding constraints to clustering [8] improves clustering results but at the cost of efficiency. We explore if adding constraints to our formulation improves the accuracy of recovering the ground truth hierarchy and also if it improves performance run-time. Fig. 9 shows the results for our methods.
      </paragraph>
      <paragraph>
       Finally, our approximation schemes have a bound on their performance which we test: 4. How tight is the theoretical bounds for the difference between the expected and optimal solutions. In practice how do the random solutions compare to optimal solutions? The results for our experiment showing the difference between the ILP solutions to overlapping hierarchical clustering and the LP approximation scheme solutions are shown in Fig. 10.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Experimental methodology
      </section-title>
      <paragraph>
       We now address the research questions proposed above in order.
      </paragraph>
      <paragraph>
       1. Does our global optimization formulation of hierarchical clustering provide better results than greedy algorithms?
      </paragraph>
      <paragraph>
       The results of the first experiment we used to answer this question are shown in Fig. 6, and they shows our method's ability to outperform many standard agglomerative clustering algorithms for standard hierarchical clustering (no overlapping clusters) on artificial data (Artificial Dataset 1). The results show that our algorithm performs better when there is increasing distance error which is expected since agglomerative algorithms are greedy and erroneous steps cannot be undone. It is significant to note that even in small data sets finding the global optimum is beneficial and we expect this improvement to be larger in bigger data sets. This experiment was performed by using the F1 score to measure the difference for learned and ground truth hierarchies and repeating each test 10 times for each error factor. The error factor is the quantity of error added, so that the ground truth hierarchical distances had uniform error added in the range {a mathematical formula}[0,errorfactor].
      </paragraph>
      <paragraph>
       We then tried our algorithm on Artificial Dataset 3, whose ground truth hierarchies were created using agglomerative clustering algorithms (single linkage), and were therefore potentially more difficult for our algorithm to compete on. To see this, note that in Fig. 7, the single linkage algorithm performs better than the other agglomerative clustering algorithms, which is unusual. We used single linkage because it is known to be most flexible in the types and shapes of hierarchies that is capable of learning. Fig. 7 shows not only that our ILP formulation works better than standard agglomerative clustering in this setting, but also shows how more noisy problems effect the runtime of our ILP formulation. The plot on the right side of Fig. 7 shows that the ILP formulation can be very quick for many problems, but that increasing the amount of noise leads to exponential increases in run time.
      </paragraph>
      <paragraph>
       We next tried our algorithms on real world data sets where we know the ground truth. Here we measure the H-correlation between the ground truth hierarchy and the hierarchy found by the algorithms. Table 3 shows that our algorithm did a better job of learning the ground truth hierarchy of languages as defined by our current understanding of language evolution. Because of the small nature of this dataset we only performed this experiment once and reported the H-correlation. For the fMRI data however, we were able to compare our method against standard agglomerative clustering multiple times and report mean and standard deviations for the H-correlation measures (see Table 4). Our method was statistically significantly better than agglomerative clustering.
      </paragraph>
      <paragraph>
       2. Can our method find overlapping clusters in datasets? We evaluated our overlapping clustering formulation against standard hierarchical clustering, using Artificial Dataset 2 and presented the results in Fig. 8. We used the same overlapping hierarchy to test how well our expected linear programming results compared to the optimal results found using an ILP solver. Those results are presented in Fig. 10 and show that in practice using an LP solution along with a very simple rounding scheme leads to results very close to the optimal ILP objective.
      </paragraph>
      <paragraph>
       We also used the 20 Newsgroup dataset to test our methods ability to find overlapping clustering. The idea behind this experiment is that there are many newsgroup postings that can naturally fit into multiple newsgroups. For example the newsgroups “comp.os.mswindows.misc” and “comp.sys.ibm.pc.hardware” are very likely to contain posts that could be cross-posted since these software and hardware platforms have traditionally been tied together. Since the 20 Newsgroups data set we used did not contain cross-postings, we simulated them by taking two messages from similar newsgroups and adding together their bag of word representations. We repeated this experiment 10 times for different samples of the 20 Newsgroup dataset of size 100, each time creating simulated cross postings and then used our overlapping hierarchical clustering formulation. We then looked at the number of clusters that each point belonged to in the entire hierarchy and measured the average of the standard points and the simulated cross-posted points. Table 6 shows that the simulated cross postings are in many more clusters than the standard points.
      </paragraph>
      <paragraph>
       3. Does the addition of constraints improve performance and run time of the algorithms?Fig. 9 shows the results of our experiment that attempted to simulate how a data mining practitioner might add constraints representing domain knowledge to our formulation. At each iteration of this experiment we learned a hierarchy and found errors in the result by comparing to the ground truth (from Artificial Data Set 3). Five new constraints were created during each iteration which were then added to a list of constraints to be used in the next iteration of the experiment. As we expected, adding a small number of constraints lead to a significant increase in the quality of results as measured using H-correlation. Another side effect that we suspected might be the case, was that adding constraints representing domain knowledge also decreased the amount of time needed to solve the problems. These constraints added were all {a mathematical formula}must–link–before constraints which apparently have the effect of decreasing the search space without increasing the difficulty of solving corresponding linear programs.
      </paragraph>
      <paragraph>
       4. How tight is the theoretical bounds for the difference between the expected and optimal solutions. In practice how do the random solutions compare to optimal solutions?
      </paragraph>
      <paragraph>
       We used the artificial overlapping hierarchy (Artificial Dataset 2) to test how well our expected linear programming results compared to the optimal results found using an ILP solver. Those results are presented in Fig. 10 and show that in practice using an LP solution along with a very simple rounding scheme leads to results very close to the optimal ILP objective.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>