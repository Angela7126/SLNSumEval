<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Automated conjecturing I: Fajtlowicz's Dalmatian heuristic revisited.
   </title>
   <abstract>
    We discuss a new implementation of, and new experiments with, Fajtlowicz's Dalmatian conjecture-making heuristic. Our program makes conjectures about relations of real number invariants of mathematical objects. Conjectures in matrix theory, number theory, and graph theory are reported, together with an experiment in using conjectures to automate game play. The program can be used in a way that, by design, advances mathematical research. These experiments suggest that automated conjecture-making can be a useful ability in the design of machines that can perform a variety of tasks that require intelligence.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      We have reimplemented Fajtlowicz's useful but little-known Dalmatian heuristic for the automation of mathematical conjecture-making (this heuristic, for instance, has never been referenced in the pages of this journal). The heuristic is general and can be used to conjecture relations between real number invariants of any objects, mathematical or otherwise. We include examples of conjectures in number theory, matrix theory, graph theory and the characterization of game positions. One of the number theory conjectures implies, and is stronger than, Goldbach's Conjecture. Some of the number theory conjectures seem to imply the Riemann Hypothesis. And some of the graph theory conjectures would advance the lower bound theory of the independence number of a graph, a widely-studied NP-hard graph invariant. We have also implemented an idea, suggested to us by Barry Mazur, to include existing theorems in the program; when used in this way the program is guaranteed to produce statements that are not implied by existing mathematical knowledge.
     </paragraph>
     <paragraph>
      Our program often makes interesting and useful conjectures on the basis of only a few examples. Humans, ordinarily and of necessity, make decisions based on very limited data. A general automated conjecture-making module that can make plausible and useful guesses based on limited data may be a central architectural feature in the design of machines that are intelligent. Guesses can be used, for instance, to constrain a search of possible actions. Fajtlowicz introduced his Dalmatian heuristic for the automation of mathematical conjecture-making more than 20 years ago [1]. Simply put, the heuristic is to produce a considered mathematical statement if it is both true—with respect to some given examples (matrices, integers, graphs, etc.)—and if the statement gives new information about those objects, in particular, if it says something about at least one of the objects which is not implied by any other stored statement or conjecture.
     </paragraph>
     <paragraph>
      It was very successful—both in limiting the number of conjectures produced by earlier versions of his Graffiti program and in producing conjectures of interest to research mathematicians. His student DeLaVina reimplemented the heuristic in a program that produces conjectures that have led to research and publications by mathematicians [2]; otherwise the heuristic has not been used. Fajtlowicz made some experiments to demonstrate the domain independence of the Dalmatian heuristic; nevertheless, the predominant and best-known uses of the heuristic—in the programs of Fajtlowicz and DeLaVina—has been in the production of graph theory conjectures. But the heuristic is not specific to the production of graph theory conjectures.
     </paragraph>
     <paragraph>
      Our program is open-source, written in Python and C, and implemented as a Sage package. Details about the acquisition and use of our program, the Sage open-source mathematical computing environment, and how to reproduce our results are relegated to Appendix A.
     </paragraph>
     <paragraph>
      Our experiments in implementing and applying this heuristic, including in domains where the authors have no more knowledge than anyone who has browsed a textbook or reference book, lead us to make several conclusions, which we will elaborate and discuss.
     </paragraph>
     <list>
      <list-item label="1.">
       Successful mathematical discovery heuristics can be applicable in a variety of mathematical domains.
      </list-item>
      <list-item label="2.">
       Good conjectures can be based on very limited data.
      </list-item>
      <list-item label="3.">
       Mathematical discovery programs should aim to produce conjectures that address and advance pre-existing mathematical questions.
      </list-item>
      <list-item label="4.">
       Intelligent conjecture-making programs for a domain do not require developer expertise in that domain.
      </list-item>
     </list>
     <paragraph>
      Some of these conclusions should be surprising and, we hope, inspire new research in automated scientific discovery.
     </paragraph>
     <paragraph>
      We see conjecture-making—and conjecture-revision in the face of contradictory data (counterexamples)—as a central feature of intelligence. We make guesses, based on our previous experience in relevantly similar situations, learn that our guesses are wrong, revise them, and test them against our experience.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background &amp; related work
     </section-title>
     <paragraph>
      Turing, famously, proposed the idea of designing intelligent machines as an engineering problem, and proposed a test for evaluating the success of such machines. In 1948 he suggested designing machines to do mathematical research as a starting point: mathematical research certainly requires intelligence and, it would be a good starting point as mathematical research would “require little contact with the outside world” [3]. In the 1950s Newell and Simon developed the Logic Theorist program that could prove (some) theorems in first-order logic, and went on to predict that a computer would discover and prove an important mathematical theorem within another decade [4]. Success did not come quite that quickly—but there has been significant progress in many areas of automating mathematical discovery, and there is no theoretical impediment to continued improvement. There is every reason to believe that Newell and Simon's prediction will be achieved—and likely sooner rather than later.
     </paragraph>
     <paragraph>
      The automation of theorem proving is by far the largest and best-developed area of automated mathematical discovery research. A highlight in this area was the 1996 computer proof of the Robbins Conjecture [5]. More recently Timothy Gowers, a Fields Medalist, and likely the most accomplished mathematician to do research in automated mathematical discovery has, together with Mohan Ganesalingam, developed a theorem-proving program.{sup:2}
     </paragraph>
     <paragraph>
      Research on automated conjecture-making was initiated by Wang in the late-1950s [6]. His Program II produced thousands of statements in propositional logic that could be considered as conjectures or potential theorems. His program included heuristics for deciding which statements to output. Evaluated as a tool for advancing mathematical research, Wang's program was a failure. He wrote: It was at first thought that these crude principles are sufficient to cut down the number of theorems to a degree that only a reasonably small number of theorems remain. It turns out that there are still too many theorems. The number of theorems printed out after running the machine for a few hours is so formidable that the writer has not even attempted to analyze the mass of data obtained [6]. What Wang really wanted was for his program to produce a limited number of statements of interest to logicians. Wang selected a few statements to include in publication—but what was really needed was a way for the program itself to identify the interesting, useful or important statements.
     </paragraph>
     <paragraph>
      The first program to make conjectures leading to published mathematical research was Fajtlowicz's Graffiti program [7], [8], [9], [10], [1]. An early version of Graffiti was called the “Sorcerer's Apprentice” [11] because the program, like Wang's, produced a large number of statements. In the Goethe poem (and the Disney Fantasia version with Mickey Mouse) a sorcerer's apprentice intends to use his master's spells to animate a broom to help him carry a bucket of water but he ends up with so many brooms and buckets of water that the “help” is no help at all—the flood of water is a bigger mess than he had to clean up in the first place. The Sorcerer's Apprentice Problem is how to reduce the flood of potential conjectures to a useable or scannable number—how to design a program to produce just the most “significant”, “interesting” or useful statements? It is not difficult to program a computer to produce an endless stream of mathematical statements. And given a stream of mathematical statements, there is a chance that some of these statements will be of mathematical interest. The problem is to produce just these ones.
     </paragraph>
     <paragraph>
      This problem was remedied by Fajtlowicz's invention of his Dalmatian heuristic, implemented in early-1990s versions of Graffiti[12]. The Dalmatian heuristic, by design, limits both the quantity of output statements and guarantees the quality of the output statements. The program cannot make any more conjectures than the number of objects being considered (stored in the program)—so the number of generated conjectures is fundamentally limited. Each conjecture must be significant with respect to at least one object—each must provide better information about a stored object than any of the other conjectures. When applied to the problem of finding bounds of invariants—in cases where bounds are of pre-existing research interest—and provided with examples (objects) where existing theory does not suffice to predict the value of the invariant for the example, a program implementing the Dalmatian heuristic will produce a conjecture. In the sense that the truth of the conjecture would advance existing theory, the conjecture can be said to be interesting or significant. The utility of the output can be further improved by including existing knowledge in the program. We will discuss one experiment implementing this new idea.
     </paragraph>
     <paragraph>
      The Graffiti program and some of its conjectures are described in Fajtlowicz's papers and in [13]. The Dalmatian heuristic first appears in [1]. DeLaVina's Graffiti.pc program, a successor to Graffiti which implements this heuristic, is described in [2]. Selected conjectures of Graffiti with commentary were collected by Fajtlowicz and included in his evolving report Written on the Wall (WoW); these were distributed by email to interested researchers.{sup:3} The conjectures of Graffiti.pc are collected by DeLaVina in Written on the Wall II (WoW2).{sup:4}
     </paragraph>
     <paragraph>
      It is worth noting some differences between these programs. Fajtlowicz experimented with a variety of heuristics and only used a small number of objects (predominantly graphs). DeLaVina's Graffiti.pc could compute, maintain and use data from millions of graphs. Graffiti was written in Pascal, had a command-line interface, and was not generally distributed. Graffiti.pc was written in C++ and Visual Basic, was designed with other users in mind, has an attractive GUI interface, and was distributed to interested students and researchers. The code for these programs was not distributed. Our program shares only its use of the Dalmatian heuristic with Graffiti and Graffiti.pc. Our code is freely available to be downloaded, experimented with, modified, and used. It is a goal of this project to encourage the general use and experimentation with conjecture-making programs, and to make this easy. The use of existing bounds to improve conjecture quality is new to the described program. Fajtlowicz reports that the conjectures in [1] were based on a database of some 600 graphs; the memory available on the computers of its day were a natural limitation on the number of objects that could be used by Graffiti. DeLaVina often uses a database of all connected graphs up to a small number of vertices, with typically more than a million graphs. While the computers our program runs on have relatively huge amounts of memory, and our program could use large numbers of objects, we have in practice only used very small number of objects in generating conjectures. The number it can use is limited only by the memory limits of the machine it is on. We can, and have, generated millions of objects in our searches for counterexamples to its conjectures.
     </paragraph>
     <paragraph>
      A variety of programs have been developed that either attempt to simulate how research mathematicians make conjectures, or that try to produce conjectures of interest to mathematicians, or both. These include the programs of Fajtlowicz and DeLaVina, as well as Lenat's AM[14], [15], [16], [17], Epstein's GT [18], [19], Colton's HR [20], [21], [22], [23], Hansen and Caporossi's AGX[24], [25], [26], and Mélot's Graphedron[27], [28]. Graffiti, Graffiti.pc and AGX have led to an especially large number of publications by mathematical researchers. There is also related and interesting work on the automation of mathematical discovery by many others including the GRAPH program of Cvetkovíc and a large group of University of Belgrade collaborators [29], Brigham and Dutton's INGRID program [30], [31], the geometry programs of Bagai and collaborators [32], [33], the hypergeometric series work of Wilf and Zeilberger [34], and applications of automatic recognition of integer-relations of Borwein, Bailey and their collaborators [35].
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      The Dalmatian heuristic
     </section-title>
     <paragraph>
      Fajtlowicz's Dalmatian heuristic is used to conjecture relations between real number invariants of objects. Many common object-types, including graphs, natural numbers, and matrices, have associated real number invariants. (Some mathematical objects, including arbitrary topological spaces, do not obviously have associated real number invariants.) The numerical invariants of a graph include the number of vertices of the graph, its number of edges, the maximum degree of any of the vertices, among numerous others. The numerical invariants of a matrix would include the determinant of the matrix, its rank, the number of rows, etc. The numerical invariants of a natural number would include the number itself, its number of factors, the number of primes no more than the number, and the number of distinct primes in its unique factorization.
     </paragraph>
     <paragraph>
      It is possible to generate conjectures using only a single stored object. Counterexamples to existing conjectures can be added as additional objects. On this approach, all objects in the database are included exactly because they had some theoretical value—no object is included arbitrarily. Fajtlowicz suggests that this approach may have its own benefits when conducting research [1]. The produced conjectures are based on a limited number of examples of objects of the given type.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}O1,…,On be examples of objects of a given type. Let {a mathematical formula}α1,…,αk be real number invariants. And let α be an invariant for which conjectured upper or lower bounds are of interest. An unlimited stream of algebraic functions of the invariants can then be formed: {a mathematical formula}α1+α2, {a mathematical formula}α1, {a mathematical formula}α1α3, {a mathematical formula}(α2+α4)2, etc. (One natural way to do this, and our own approach, is to grow trees representing these expressions with operators representing algebraic operations on the non-leaf nodes—with the number of sub-nodes equal to the arity of the operator—and invariants on the leaf nodes.) These expressions can then be used to form conjectured bounds for α. If we are interested in upper bounds for α, say, we can form the inequalities {a mathematical formula}α≤α1+α2, {a mathematical formula}α≤α1, {a mathematical formula}α≤α1α3, {a mathematical formula}α≤(α2+α4)2, etc.
     </paragraph>
     <paragraph>
      These inequalities can be interpreted as being true for all the objects of the given type. That is, the inequality {a mathematical formula}α≤α1+α2 can be interpreted as, “For every object {a mathematical formula}O, {a mathematical formula}α(O)≤α1(O)+α2(O).” A conjectured upper bound u is only added to the database of conjectures if the bound passes the following two tests.
     </paragraph>
     <list>
      <list-item label="1.">
       (Truth test.) The candidate conjecture {a mathematical formula}α≤u is true for all of the stored objects {a mathematical formula}O1,…,On, and
      </list-item>
      <list-item label="2.">
       (Significance test.) There is an object {a mathematical formula}O∈{O1,…,On} such that {a mathematical formula}u(O)&lt;min⁡{u1(O),…,ur(O)}, where {a mathematical formula}u1,…,ur are the currently stored conjectures. That is, the candidate conjecture would give a better bound for {a mathematical formula}α(O) than any previously conjectured (upper) bound.
      </list-item>
     </list>
     <paragraph>
      These criteria capture what Fajtlowicz calls the “Principle of the Strongest Conjecture”: make the strongest conjecture for which no counterexample is known. By design, the truth test guarantees that the program does not know a counterexample, and the significance test guarantees that each conjectured bound is “stronger” (gives a better bounding value) than any other—at least for a single object known to the program.
     </paragraph>
     <paragraph>
      What follows is pseudocode for this main loop of our program for the case where conjectured upper bounds for some invariant is desired. upper_bound, a potential conjectured upper bound for invariant, is an expression constructed from the invariants and operators included in the program. objects is the list of examples known to the program. The value of invariant and upper_bound applied to each {a mathematical formula}O in objects is a real number; similarly, the value of u applied to {a mathematical formula}O, for each u in conjectured_upper_bounds and each {a mathematical formula}O in objects is a real number. In the case where both the truth and significance tests are passed, upper_bound is added to the conjectures store conjectured_upper_bounds. The main loop for the case of lower bound conjectures would parallel this.
     </paragraph>
     <list>
      <list-item>
       deftruth(invariant,upper_bound,objects):forOinobjects:ifinvariant(O)&gt;upper_bound(O):returnFailelse:returnPassdefsignificance(upper_bound,conjectured_upper_bounds,objects):forOinobjects:ifupper_bound(O)&lt;min([u(O)foruinconjectured_upper_bounds]):returnPasselse:returnFaildefdalmatian(invariant,upper_bound,conjectured_upper_bounds,objects):iftruth(invariant,upper_bound,objects)==Passandsignificance(upper_bound,conjectured_upper_bounds,objects)==Pass:conjectured_upper_bounds+=[upper_bound]defmain(objects,invariants,invariant):conjectured_upper_bounds=[]while(stopping_condition==False):upper_bound=generate_next_potential_upper_bound()dalmatian(invariant,upper_bound,conjectured_upper_bounds,objects)
      </list-item>
     </list>
     <paragraph>
      Here is a concrete illustration of how the Dalmatian heuristic works, with an example from number theory—as the invariants here should be generally known. We will step through the generation of conjectured lower bounds for {a mathematical formula}π(x), the number of primes no more than x. Note, here, that {a mathematical formula}π(5)=3 and {a mathematical formula}π(16)=6. So, ideally, we will generate lower bounds for {a mathematical formula}π(x) where the maximum of the conjectured lower bounds applied to the object 5 is 3, while the maximum for 16 is 6.
     </paragraph>
     <paragraph>
      The initial objects are 5 and 16, the invariants used to form potential lower bounds are sum_of_digits, number_prime_factors, and number_of_divisors, while the operators are ^2, +, and +1. Here we also assume that, after a significant conjecture is added to the conjectures store, that insignificant conjectures are removed. The order that potential lower bounds are considered corresponds to the iteration number in Table 1. First all of the invariants themselves (each represented by a tree with a root and no other nodes) are considered, followed by the application of the unary squaring operator to these invariants, followed by application of the binary sum operator applied to each distinct pair of invariants. Expressions formed with the unary “add 1” operator are never formed as the program stops after the ninth iteration, at which point the conjectures in the conjecture store exactly predict the value of {a mathematical formula}π(x) for all objects x in {a mathematical formula}{5,16}.
     </paragraph>
     <paragraph>
      The considered conjecture in Iteration 1 in Table 1 is “the sum of the digits of an integer x is no more than {a mathematical formula}π(x)”. This is not true of all objects known to the program, does not pass the truth test, and the conjecture store remains empty. The next considered conjecture is “the number of prime factors of any integer x is no more than {a mathematical formula}π(x)”. This conjecture passes the truth test, as it is true for all known objects, and trivially passes the significance test. The conjectures store is updated to include this lower bound. The considered conjecture in Iteration 3 is “the number of divisors of an integer x is no more than {a mathematical formula}π(x)”. This is true for all of the objects and is significant as this lower bound is better than the number_prime_factors lower bound for at least one of the known objects; so number_prime_factors is added to the conjectures store. In fact it is at least as good for all the known objects. Since there is no object x in {a mathematical formula}{5,16} where number_prime_factors(x) &gt; number_of_divisors(x). The number_of_divisors bound is removed from the conjectures store as insignificant. The next change to the conjectures store comes after Iteration 9. The considered conjecture is “the number of prime factors of an integer x plus the number of its divisors is no more than {a mathematical formula}π(x)”. This is true for all known objects, and the bound passes the truth test. The bound gives a larger value than number_of_divisors for at least one known objects and is thus significant and added to the conjecture store. In fact number_of_divisors is no longer a significant bound and it is removed. At this point, for each object x, the maximum of the conjectured bounds equals the actual value of {a mathematical formula}π(x). No further bounds can be significant and the program stops.
     </paragraph>
     <paragraph>
      Some of Graffiti's best-known conjectures are the following lower bounds for the independence number α of a graph (the maximum number of pairwise non-adjacent vertices in the graph, an NP-hard-to-compute graph invariant), and were made prior to the addition of the Dalmatian heuristic to that program.{sup:5}
     </paragraph>
     <list>
      <list-item label="1.">
       If G is a connected graph then {a mathematical formula}d¯≤α, where {a mathematical formula}d¯ is the average distance between distinct vertices of G. Both the average distance of a connected graph and the independence number of a graph are well-studied concepts. This conjecture was proved by Chung [36].
      </list-item>
      <list-item label="2.">
       If G is a connected graph then {a mathematical formula}r≤α where r is the radius of G. This conjecture was originally proved by Erdős, Saks and Sós in [37]. Another proof, due to Fajtlowicz, follows from the characterization of graphs where its radius equals its independence number [38].
      </list-item>
      <list-item label="3.">
       For any graph G, {a mathematical formula}R≤α, where R is the residue of G (this is the number of zeros remaining after repeated application of the Havel–Hakimi procedure to the degree sequence of the graph). This conjecture was originally proved by Favaron, Mahéo and Saclé [39], and has since been reproved in the literature more than once. One nice proof is due to Griggs and Kleitman [40].
      </list-item>
     </list>
     <paragraph>
      Pre-Dalmatian versions of Graffiti were also used to generate some interesting number theory conjectures including, for instance, a formula for {a mathematical formula}π(x).
     </paragraph>
     <paragraph>
      We now record some examples of Graffiti's Dalmatian heuristic conjectures in various domains.
     </paragraph>
     <list>
      <list-item label="1.">
       (Graph theory, WoW #747) If G is a connected graph then {a mathematical formula}d¯≤b2, where b is the bipartite number, the order of a largest induced bipartite subgraph [1]. Here the objects are connected graphs, and the average distance and bipartite number are graph invariants. This conjecture generalizes Chung's theorem, mentioned earlier, and was recently proved by Hansen and collaborators [41].
      </list-item>
      <list-item label="2.">
       (Geometry, WoW #738) For a vertex v of a triangle, {a mathematical formula}a≤s, where a is the length of the line segment which bisects v and extends to the opposite side and s is the length of the line segment from v to the midpoint of the opposite side. Here the objects are triangle vertices, and a and s are triangle vertex invariants. It is reasonable to believe that useful geometric knowledge awaits discovery. In fact, Coxeter has claimed that “geometry is developing as fast as any other kind of mathematics” [42]. Nevertheless, Graffiti's geometry conjectures did not initiate any research. This can be explained for various reasons; the most fundamental would be that this conjecture does not directly advance any existing research question, in particular, that there is neither any existing interest in upper bounds for the length of a line segment that bisects a vertex and extends to the opposite side, nor in lower bounds for the length of the line segment from a vertex to the midpoint of the opposite side.
      </list-item>
      <list-item label="3.">
       (Chemistry, WoW #895) For any fullerene, the separator of the fullerene is no more than 1. Here the objects are fullerenes, and the separator is a fullerene invariant. Fullerenes are a recently-discovered (1985) form of carbon which include the 60-atom soccerball-shaped buckyball. Mathematically the structure of a fullerene is a trivalent planar graph with pentagonal and hexagonal faces. There are, for instance, 1812 mathematically possible 60-atom fullerenes but only one that appears in experiment [43]. Many other fullerenes with different atom counts have appeared in experiment as either hollow structures like {a mathematical formula}C60, endohedral structures, or which form tubes (which are technically incomplete fullerenes).The fullerene literature is now vast and includes a large number of papers connecting invariants of their mathematical structure to physical invariants. A mathematical fullerene invariant would include the difference between the largest and second-largest eigenvalue (or separator) of the symmetric matrix representing the bonding structure of its atoms. There is some empirical evidence connecting large separator values with fullerene stability [44], [45]. Graffiti's conjecture was proved by Stevanović and Caporossi [46].It is worth noting that DeLaVina's Graffiti.pc program also made some conjectures related to the electronic structure of fullerenes; these are reported in [47, pp. 127–128].It might be said that these fullerene conjectures are more about graph theory than about chemistry. But graphs have been used to represent molecules since the 19th century—in a way that advances both chemists' understanding of their subject and their ability to predict chemical phenomenon [43]. A prototypical example is the Coulson–Rushbrooke Pairing Theorem [48] which can be found in both chemical and graph theoretic language: it can be stated either in terms of π-electron energy levels for alternant hydrocarbons or in terms of eigenvalues of bipartite graphs. In books such as Fowler and Manolopoulos' Atlas of Fullerenes, for instance, what might be counted as “chemistry” and what might be counted as “graph theory” can hardly be distinguished.
      </list-item>
     </list>
     <paragraph>
      Fajtlowicz generated conjectures in domains other than graph theory largely to demonstrate that the heuristics that he invented were not limited to use in graph theory but were general (“domain independent”).
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The program
     </section-title>
     <paragraph>
      An expression generating program (written in C for speed) is at the heart of our program. In this context an expression is just a rooted, labeled binary tree, that is, a rooted tree where each node has at most two children and each node with, respectively, two, one or no children is labeled with, respectively, a binary operator, a unary operator or an invariant. The expressions are generated according to increasing complexity, which is defined as twice the number of binary operators plus the number of unary operators. The program uses the algorithm described in [49] and the numbers of generated structures have been compared to the implementation in [50]. The generated expressions are tested for being true for the provided invariant values (truth test) and can then be handed over to an internal heuristic or can just be output. Internally we have implemented two conjecture-making heuristics: the Dalmatian heuristic and—for testing purposes—the heuristic described in [49].
     </paragraph>
     <paragraph>
      Importantly, the results we describe in the following sections are reproducible. Details about where to find the code and associated scripts are collected in the final section of this paper.
     </paragraph>
     <paragraph>
      The general approach to generating conjectures is as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       Produce a stream of inequalities with evaluable functions of the invariants on each side of the inequality symbol. Some of these will pass the truth and significance tests and be stored as conjectures.
      </list-item>
      <list-item label="2.">
       Initialize an initial collection of objects. These can be as few as one.
      </list-item>
      <list-item label="3.">
       Generate conjectures that are true for all stored objects and significant with respect to these objects and the previously stored conjectures. Pass each generated statement to the truth and significance tests. The program needs a stopping condition. The best case is that, for each object, there is at least one conjecture that gives the exact value for the object. In this case there is no possibility of improving the current conjectures—in the sense that no other conjectures can make better predictions about the values of the existing objects—exact predictive power for all objects has been achieved. In the case where this natural stopping condition is never attained, another stopping condition will be required. One possibility is to simply stop making conjectures after some hardcoded or user-specified time.
      </list-item>
      <list-item label="4.">
       Remove insignificant conjectures. After a conjecture is added to the store of conjectures, it may be the case that another conjecture in the store is no longer significant. If conjectured upper bounds (for example) for an invariant α are being generated then a conjectured bound {a mathematical formula}αi in the conjectures store is significant, with respect to the stored objects, if and only if there is an object {a mathematical formula}O such that {a mathematical formula}αi(O)&lt;min⁡{αj(O):j≠i}, that is, if and only if, there is an object {a mathematical formula}O where the bound gives a better predicted value for {a mathematical formula}α(O) than any other conjectured bound does. Insignificant conjectures are then removed.
      </list-item>
      <list-item label="5.">
       Search for a counterexample to any of these conjectures. This can be done by a human or automated in some way. In the case of number theory conjectures, the conjectures can easily be checked by testing the conjectures for each integer from 1 up to an arbitrary large integer. In the case of other objects, it will usually require some work to generate a stream of distinct objects. In the case of graphs, McKay's geng provides a stream of examples from graphs with a single vertex up to any user-specified number of vertices.
      </list-item>
      <list-item label="6.">
       Add the counterexample, and repeat the conjecture generating and testing process. The program can never make more conjectures than the number of objects it has stored: the reason is exactly because each conjecture in the conjectures store must give a better bound for at least one stored object than any other conjecture does.If there were, for instance, two stored objects and three conjectured bounds, at least one of the conjectured bounds could not possibly be significant: at best one of the conjectures could be the best bound for one of the objects and another for the second object—but the third conjecture would have no possible remaining objects for which it could give the unique best predicted value; this conjecture would have been removed as insignificant.
      </list-item>
     </list>
     <paragraph>
      From the point of view of a user of our program, the required inputs of the program are three:
     </paragraph>
     <list>
      <list-item label="1.">
       A list of objects. The type is arbitrary, but they will usually all be of the same type. To get meaningful results they will all represent the same mathematical type of object. For instance, if you want to generate conjectures about graphs, and c5, k5 and petersen are pre-defined graph objects, you would define objects = [c5, k5, petersen], and give objects as a parameter to the program.
      </list-item>
      <list-item label="2.">
       A list of invariants. These must be functions that are defined for the type of objects in the objects list. For instance, if radius, size and order are pre-defined real-valued graph functions, you would define invariants = [radius, size, order] and give invariants as a parameter to the program.
      </list-item>
      <list-item label="3.">
       A positive integer listing the position of the invariant in the list of invariants that you would like to conjecture bounds for from the list of invariants. For instance if conjectures for the radius of a graph are desired, the user would enter 0 in the list of parameters to the C program.
      </list-item>
     </list>
     <paragraph>
      A concrete example of the use of the program may be found in Appendix A. The outputs of the program are conjecture objects. These look like the statements given in the examples in the subsequent sections of this paper. In fact these conjectures are text representations of relationships between the invariants themselves, and have further useful features encoded in their methods. The program, by default, conjectures upper bounds for the chosen invariant. There are many other non-required user options. In particular, one option generates lower bound conjectures. The operators used in the expression are not user options. They are hard-coded in the program, since, unlike the functions computing the invariants, these operators are also needed in the C program. Additional operators can be added by making additions to the code. A user can exclude operators from being used. All conjectures reported here were made with the same set of operators; no code changes were made.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Matrix theory examples
     </section-title>
     <paragraph>
      Neither author is a matrix theorist, which is one reason that we chose matrix theory as a domain for experimentation. Sage has a number of built-in matrix invariants. We implemented other invariants (that we found in [51]) as Sage procedures; these function in the same way as Sage's built-in invariants.
     </paragraph>
     <paragraph>
      The objects are symmetric matrices (which thus have the property that all of their eigenvalues are real). The invariants we used are the determinant, nullity (number of zero eigenvalues), rank (number of non-zero eigenvalues), trace (sum of the diagonal entries), nrows (number of rows of the matrix), permanent, maximum_eigenvalue, minimum_eigenvalue, average_eigenvalue, number_of_distinct_eigenvalues, spectral_radius (the difference between the largest and smallest eigenvalues), ratio_min_max_absolute_eigenvalues (the ratio of the absolute values of the largest and smallest eigenvalues), sqrt_abs (the square root of the sum of the absolute values of the entries of the matrix), frobenius_norm (the square root of the sum of the squares of the entries of the matrix), max_column_sum (the maximum of the sum of the entries of each column), l_inf_norm (the maximum of the absolute value of the entries of the matrix), and the separator (the difference between the largest and second largest eigenvalues).
     </paragraph>
     <paragraph>
      Bounds for the determinant of a matrix exist in the matrix theory literature. For instance, Hadamard's Inequality says that the determinant of a matrix is no more than the product of the Euclidean lengths of the vectors defined by its columns [51]. We presume that new bounds might also be of interest to researchers. The following conjectures should be taken as an example of what can be done with the program. Matrix theorists can generate conjectured bounds for any invariant that might advance their research.
     </paragraph>
     <paragraph>
      The first round of conjectures for upper bounds for the determinant (det) of a symmetric matrix are included in Table 2. In general, we expect counterexamples of existing conjectures to be the best objects to input to a conjecture-making program. We find these ourselves, from experts, or by systematically generating matrices and testing whether each satisfied the conjecture or whether it was a counterexample.
     </paragraph>
     <paragraph>
      We also generated a round of conjectured lower bounds for the determinant of a symmetric matrix. These can be found in Table 3. One further round of upper and lower bound conjectures for the absolute value of the determinant is included here. The upper bound conjectures are in Table 4. The lower bound conjectures for the absolute value of the determinant of a matrix are in Table 5. The second conjecture is, of course, trivially true; nevertheless, at the point that it was made it had to have given a better bound for the absolute value of the determinant of some object than the bound in the first conjecture.
     </paragraph>
     <paragraph>
      While one use for conjectured bounds for an invariant is as statements for mathematical investigation, another possible use is for the heuristic estimation of an invariant value. An estimate for the value of the determinant of a matrix can be made by using either of the minimum of the values of the conjectured upper bounds for the determinant, or the maximum of the values of the conjectured lower bounds. While the determinant of a matrix is efficiently computable and an estimate may not be of any practical interest, there are other hard-to-compute invariants—for example, the independence number of a graph—where estimates generated from efficiently computable conjectured bounds may be of interest. Another case where conjecture-driven invariant estimates might be of use is in characterizing a class of objects. An example will be discussed in connection with the game Chomp.
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Number theory conjectures
     </section-title>
     <paragraph>
      We also chose number theory as a domain for experimentation because neither author has any special knowledge of this subject. We were aware of Goldbach's Conjecture, interest in the distribution of the prime numbers and the Prime Number Theorem, and the Riemann Hypothesis. While we did not expect to make any contribution to this classical and well-researched area of mathematics, we did think that our experiments could be of interest.
     </paragraph>
     <paragraph>
      Goldbach, in a 1742 letter to Euler, conjectured that every even integer ({a mathematical formula}n&gt;2) is the sum of two primes [52]. The conjecture has been verified by computer for all integers up to at least {a mathematical formula}4⋅1014[53], and there are a large number of partial results and continuing interest. Let Goldbach(x) be the number of representations of x as a sum of two primes (so {a mathematical formula}Goldbach(6)=1 and {a mathematical formula}Goldbach(8)=2). Clearly Goldbach's Conjecture is true if and only if {a mathematical formula}Goldbach(x)&gt;0 for even {a mathematical formula}x&gt;2. Thus, conjectured lower bounds for Goldbach(x) are of potential utility to researchers: they could yield new avenues of investigation.
     </paragraph>
     <paragraph>
      The objects here are even integers, and the invariants are integer invariants. The first run of conjectures for Goldbach(x) involved the invariants prime_pi (the number of primes ≤x), euler_phi (the number of integers ≤x which are relatively prime to x), number (which returns the number x itself), digits10 (the number of digits in the base-10 representation of x), digits2 (the number of digits in the base-2 representation of x), sigma (the sum of all divisors of x), count_divisors (the number of divisors of x), next_prime (the smallest prime greater than x), previous_prime (the largest prime smaller than x), and count_quadratic_residues (the number of quadratic residues of x). Most of these invariants were included merely because they were built-in Sage functions.
     </paragraph>
     <paragraph>
      Table 6 records the first round of Goldbach(x) conjectures. Conjecture 1 is curious as the bound goes to 0 as x gets large, and the bound is of little predictive use. Nevertheless, the only object initially known to the program was the integer 4, and for this object the lower bound exactly predicts the true value of 1 for Goldbach(4). The second conjecture, which is much stronger in general, fails to predict Goldbach(4) and thus does not supersede the first conjecture (the first conjecture is “stronger” for {a mathematical formula}x=4). Both conjectures were tested and were true for values of x up to 1,000,000. No counterexample was found to the second conjecture and, thus, no further conjectures could be added to the list of conjectures. The second conjecture is, in general, stronger than Goldbach's Conjecture and, if true, would imply it.
     </paragraph>
     <paragraph>
      In order to generate different conjectures, we removed digits10 as an invariant, and added some new invariants: mertens (the sum of the values of the Möbius function for the integers no more than x[54, p. 36]), li (the logarithmic integral with lower bound 0), zeta (the Riemann zeta function), reciprocal_prime_sum (the sum of the reciprocals of the primes up to x), max_prime_divisor (the largest prime divisor of x), and prime_product (the product of all primes no more than x). The second run of the program produced the conjectures in Table 7.
     </paragraph>
     <paragraph>
      The distribution of the prime numbers has been of interest at least since the time of Gauss, who famously conjectured that {a mathematical formula}π(x), the number of primes no more than x, is asymptotic to {a mathematical formula}xlog⁡(x). This is now the Prime Number Theorem (PNT), which was proved independently by Hadamard and Vallée–Poussin in 1896 [52]. prime_pi(x) is the Sage implementation of {a mathematical formula}π(x). There is an interest in getting good explicit estimates for {a mathematical formula}π(x). One bound due to Rosser [55], says that, for {a mathematical formula}x≥55,{a mathematical formula} Other well-known bounds of Rosser and Schoenfeld can be found in [56].
     </paragraph>
     <paragraph>
      Conjectures from the first run of the program are recorded in Table 8. The invariants used in these are the same as those used in the first run of conjectures for Goldbach(x). By the design of the program, we know that the truth of these conjectures was tested for only 49 integers (all less than 440). Conjectures 2, 13 and 26 from Table 8 seemed of possible interest as they are similar in form to the PNT. We further tested the truth of these three conjectures for all integers no more than {a mathematical formula}x=1,000,000. Conjecture 26 is false for {a mathematical formula}x=467. Conjectures 2 and 13 are true for all tested values of x.
     </paragraph>
     <paragraph>
      Lastly, we generated some conjectures that could be related to the Riemann Hypothesis. The best-known version of the conjecture, and the one posed by Riemann, is a claim about the zeros of the Riemann zeta function. Von Koch showed that the Riemann hypothesis is equivalent to the statement that {a mathematical formula}|π(x)−Li(x)|≤x⋅ln⁡(x) for {a mathematical formula}x≥2.01, where {a mathematical formula}Li(x)=∫2x1ln⁡(t)dt is the (offset) logarithmic integral (so {a mathematical formula}Li(x)=li(x)−li(2)) [54, p. 37]. Thus we expect bounds for {a mathematical formula}|π(x)−Li(x)| to be of interest to researchers.
     </paragraph>
     <paragraph>
      In our initial run, we encountered the Sorcerer's Apprentice Problem. Starting with a single (integer) object the program generated conjectures, found counterexamples, added these to the store of objects, and repeated the process. In making repeated rounds, the program soon produced 200 counterexamples and 71 corresponding conjectures and was stopped (the first 25 conjectures are in Table 9). The list had become too long and of less and less potential interest: experts can't be expected to consider 71 conjectures with as much interest as they might have for a mere handful of conjectures.
     </paragraph>
     <paragraph>
      The conjectures that we really wanted were ones that would be of possible use in proving the Riemann Hypothesis. In light of this, we filtered the conjectured bounds for the ones that were no more than {a mathematical formula}x⋅ln⁡(x) for all integers x between 3 and {a mathematical formula}1,000,000. The produced conjectures satisfying this additional condition are in Table 10.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Bounds for the graph theoretic domination number
     </section-title>
     <paragraph>
      Both authors are graph theorists. Our interests and research specialties include independence number theory, graph generation, chemical graph theory, and algorithm design; neither of us is an expert in the theory of dominating sets and domination number of a graph.
     </paragraph>
     <paragraph>
      A dominating set in a graph is a set D such that every vertex of the graph which is not in D is adjacent to at least one vertex in D; the domination number of a graph is the cardinality of a minimum dominating set [57]. Computing the domination number of a graph is intractable (NP-hard) and currently impossible for general graphs of even moderate size. Conjectured bounds for the domination number are of theoretical interest—bounds which are functions of efficiently computable invariants are also of practical interest—these can lead to speed up of domination number computations.
     </paragraph>
     <paragraph>
      The objects are connected graphs. The invariants we started with included domination_number, matching_number, annihilation_number, girth, radius, fractional_independence_number, average_distance, diameter, order, size, szeged_index, wiener_index, average_degree, min_degree, max_degree, and residue. Many of these are standard graph theoretic invariants that can be found in introductory texts such as [58]. These invariants were either built-in Sage functions or were coded by us as Sage procedures. For acyclic graphs, girth was set to infinity. The Szeged and Wiener indices are of special interest in chemical graph theory. The fractional independence number is the optimum solution to the relaxation of the independence number linear program (and thus an upper bound for the independence number). The annihilation number is a degree sequence upper bound for the independence number introduced by Pepper [59], [60], and the residue is a degree sequence lower bound for the independence number introduced by Fajtlowicz [39].
     </paragraph>
     <paragraph>
      The three invariants listed after domination_number are known upper bounds for the domination number and were eventually removed in order to try to generate better upper bound conjectures. Manual removal of invariants in this way is no longer required: the inclusion and use of known bounds would have precluded the initial production of these conjectures.
     </paragraph>
     <paragraph>
      We used McKay's program geng[61] to generate all graphs up to some (small) specified order in a loop to automatedly find counterexamples to generated conjectures and, thus, automatedly improve the produced conjectures. In our run generating upper bound conjectures for the domination number, the program ended up with four examples (found by this automated search for counterexamples) and the conjecture that the domination number of a graph is no more than its matching number. The conjecture exactly predicted the true value of the domination number of these four graphs—and, hence, the program stopped. This is a known (and not difficult to prove) fact about the domination number. Again, if existing theory had been included, this conjecture could not have been made.
     </paragraph>
     <paragraph>
      In the next run, we removed matching_number from the list of invariants and the program generated the three conjectures in Table 11. The first two we knew to be true. The third is false: Ryan Pepper found a 24 vertex counterexample; this is the graph in Fig. 1.
     </paragraph>
     <paragraph>
      After adding Pepper's counterexample, we generated another run of upper bound domination conjectures. These are in Table 12. Stephen Hedetniemi, a co-author of the standard reference on domination [57], points out that the second of these conjectures is false for {a mathematical formula}K1 and {a mathematical formula}K2—we had only been including graphs of order {a mathematical formula}n≥3 in our automated counterexample search—and trivially true for graphs or order {a mathematical formula}n≥3. The truth of Conjecture 7 follows from a well-known result. He also provided counterexamples to Conjectures 3, 4, 5, and 11. The graph in Fig. 2 disproves these: it has 201 vertices, domination number of 100, girth of 3, maximum degree of 100, average distance of 2.97, diameter of 4, and radius of 2.
     </paragraph>
     <paragraph>
      We added Hedetniemi's counterexamples as objects to the program and generated a second round of conjectures for upper bounds for the domination number of a graph; the results are in Table 13. Several of these conjectures reappeared in the second round. All of these conjectures other than the first remain open.
     </paragraph>
     <paragraph>
      Finally, we generated a round of conjectured lower bounds for the domination number of a graph. The results are in Table 14. The first conjecture is false: Pepper points out that large enough cycles are counterexamples. The second and third conjectures are curious as they are trivially true; but, at some point in the conjecture-making process, there must have been graphs for which these bounds gave a larger predicted domination number than the previously conjectured bounds.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Lower bounds for the graph-theoretic independence number
     </section-title>
     <paragraph>
      The independence number of a graph (also called the stability number, vertex packing number and node packing number) is the largest number of mutually pairwise non-adjacent vertices in the graph. It is NP-hard to compute [62], of both practical and theoretical interest, and has a large literature. There are at least 50 published bounds for this graph invariant. In this case our goal was to generate conjectured lower bounds for the independence number which are not consequences of existing (proved) lower bounds. It is practically impossible to compute the independence number of arbitrary graphs of even moderate size (say, with 2000 vertices{sup:6}).
     </paragraph>
     <paragraph>
      In this case the authors are specialists. The first author has written papers on the theory of maximum independent sets, the computation of this number, and applications [63], [64], [60], [65], [45]. But a similar investigation could have been carried out by a non-specialist who had the collected published facts that we make use of. Special use was made of this knowledge only to find counterexamples to conjectures; if finding counterexamples could be automated then this investigation could have been done entirely without expert knowledge.
     </paragraph>
     <paragraph>
      In the previously reported experiments, no existing bounds were included in the program—and, thus, the program could make “rediscoveries.” Mazur later suggested including known bounds—theoretical knowledge—in the program to keep the program from making conjectures that were implied by existing theory. This was easy to implement: the conjectures store can simple be seeded with these known bounds. In this way, the program only produces conjectures that are mathematically significant in a precise sense: they will give better invariant value predictions for some objects than any known bounds will. The known bounds that we included in these experiments are the following: the aforementioned radius and residue, Fajtlowicz's max-even-minus-min-horizontal bound (the maximum, over all vertices v, of the number of vertices minus the number of edges for the subgraph induced by the vertices at even distance from v), together with a bound due to Angel, Campigotto and Laforest [66].
     </paragraph>
     <paragraph>
      The upper bound theory for the independence number is surprisingly good: there is an efficiently computable upper bound for the independence number of a graph which can give very good estimates for the true value of this invariant: this is the famous Lovász number ϑ of a graph. Lovász's original definition was in terms of orthogonal representations of the graph [67]. There are now known to be several equivalent definitions [68]. All these definitions are all relatively technical and not worth detailing here. One definition is as the optimal value of a semidefinite program—and solving semidefinite programs is something that can be done efficiently [69]. We have computed both the Lovász number and the independence number for all graphs with up to 10 vertices (there are more than 12 million simple graphs with 10 vertices [70]). For all of these graphs, the floor of the Lovász number equals the independence number; that is, the Lovász number exactly predicts the independence number.
     </paragraph>
     <paragraph>
      No similar lower bound exists. For small graphs the residue can be very good. But, as the order of the graph increases, the residue becomes less and less good. Our goal was to find new lower bounds that would advance this theory. While it is unlikely that there is any single lower bound that will be as predictive as the Lovász number upper bound, it is possible that, with enough lower bounds, at least one of them may be predictive for a given graph. We conducted two investigations, the first was for small “hard” graphs, and the second was for random graphs.
     </paragraph>
     <paragraph>
      In our first investigation we used only independence irreducible graphs [64] as examples for the program. These graphs admit various definitions. The significance of these graphs is that the calculation of the independence number of any graph can be efficiently reduced to the calculation of the independence number of an independence irreducible subgraph. In this sense these are the “hardest” graphs for independence number computations.
     </paragraph>
     <paragraph>
      Here we included all of the efficiently computable graph invariants that are either built-in to Sage or that we have coded (as Sage procedures). So this investigation did not include domination_number but did include, for instance, lovasz_theta. The complete list is: independence_number, card_center, Graph.connected_components_number, cycle_space_dimension, card_periphery, Graph.density, Graph.average_distance, Graph.diameter, Graph.radius, Graph.girth, Graph.order, Graph.size, Graph.szeged_index, min_degree, Graph.wiener_index, max_degree, Graph.average_degree, matching_number, residue, annihilation_number, lovasz_theta, and cvetkovic.
     </paragraph>
     <paragraph>
      Here we do not report all the conjectures made by the program but only those that attracted the first author due either to their simplicity or their relation to known bounds. The first of these is the conjecture that, for independence irreducible graphs, independence_number ≥ min(girth-1, cvetkovic). cvetkovic is the Cvetković bound, the minimum of the number of non-negative and non-positive eigenvalues of the graph. It is an upper bound of the independence number. The fact that it showed up in a simple formula for a conjectured lower bound is surprising. The conjecture was verified for all graphs of up to ten vertices. But there is a counterexample with eleven vertices: this is the graph in Fig. 3.
     </paragraph>
     <paragraph>
      The next conjecture is that independence_number ≥ 2*matching_number-2*maximum_degree for all independence irreducible graphs. This conjecture was also verified for all graphs with up to ten vertices. But here there is a counterexample with fourteen vertices, namely the graph formed by putting a single edge from any vertex in one 7-cycle (a cycle graph on seven vertices) to any vertex on a second 7-cycle.
     </paragraph>
     <paragraph>
      The two conjectures in Table 15, which were also verified for all graphs with up to ten vertices, remain open.
     </paragraph>
     <paragraph>
      In the previous run of the program, potential counterexamples were searched for by systematically generating all small graphs using McKay's geng. Counterexamples were then added as objects to the program, and the process was iterated. In the next run of the program we did not use geng. We wanted to use larger graphs as potential counterexamples and here systematic generation is impossible: there are, for instance, approximately 10{sup:65} graphs of order 25. We chose random selections of graphs from orders 10 to 25 in our search for counterexamples. These were generated, essentially, by choosing the order of the graph and, for each pair of vertices, flipping a coin to determine whether or not to include an edge between the vertices (the theory of random graphs is large and dates back to the 1950s [71]). Three of these conjectures are in Table 16. They should be interpreted as being true for random graphs. The first and third conjectures in Table 16 are interesting because they, in some sense, generalize the radius lower bound for the independence number of a graph (mentioned earlier, following a conjecture of Graffiti). The second conjecture involves the periphery, which is the cardinality of the set of vertices of maximum eccentricity.
     </paragraph>
    </section>
    <section label="9">
     <section-title>
      Chomp
     </section-title>
     <paragraph>
      A conjecture-making program can be used in the design of a game-playing program. We describe how this might be done, and an initial experiment, for the game of Chomp. Chomp is an impartial two-player perfect information game that terminates in a finite number of moves; thus it has a winning strategy [72]. The game is played on a rectangular board which is, at the beginning, completely covered with “cookies”. The upper left corner of the board contains a “poisoned cookie”. Which ever player eats the poison cookie loses. A move consists of a player choosing a square with a cookie on it, removing that cookie and all cookies to the right of it or below it and any other cookie which is both to the right and below it.
     </paragraph>
     <paragraph>
      There are board positions from which, if the next player to move N played perfectly, N would be guaranteed to win, regardless of what future moves the previous player to play P makes. The winning strategy for N is known in special cases, for instance, if the cookies form an “L”, or if there are only one or two rows of cookies. A winning strategy for N in the general case is not known. Given a board position, what is the best move for N to make in order to secure an eventual victory? A position may be theoretically “solvable” despite the fact that no human (nor machine) knows the solution—it is beyond current human and machine powers. N's goal is to get from the current board position to one that is known to be solvable.
     </paragraph>
     <paragraph>
      Our idea is use known winning positions (where N has a known winning strategy) as objects, and generate conjectures about these positions to use in the choice of a move. For Chomp the game board can easily be represented as a 0–1 matrix with 1s in the entries representing squares of the board with cookies on them. Various invariants can then be defined. We defined only invariants that are Chomp-specific; that is, we did not use any matrix invariants such as the largest singular value, that did not have any obvious interpretation in terms of game play. “Chomp conjectures” involving only natural Chomp invariants might be provable—in terms of game strategy—and initiate a Chomp Theory. Our ideal Chomp Theory would consist of some number of invariant-relation statements that would all be satisfied for any winning position and which would not all be satisfied for a losing position.
     </paragraph>
     <paragraph>
      The invariants we used are: cookie_rank (the number of different rows with a different number of 1s, equals the matrix rank), duplicate_columns (the number of duplicated columns), duplicate_rows (the number of duplicated rows), first_two_columns_difference (the difference between the number of 1s in the first and second columns), first_two_rows_difference (the difference between the number of 1s in the first and second rows), possible_cookies (the initial number of 1s at the beginning of the game), number_of_cookies (the number of 1s in the matrix), L_difference (difference between the length of the longest row and longest column), diagonal_cookies (the number of 1s on the diagonal of the matrix), max_column_cookies (the number of 1s in the leftmost column of the matrix), max_row_cookies (the number of 1s in the topmost row of the matrix), and inside (the number of 1s not in the leftmost column or topmost row).
     </paragraph>
     <paragraph>
      The objects that we used were 26 mostly simple winning game positions derived from Gale's original paper. We then generated conjectured upper and lower bounds for each of the 12 invariants. A possible game position would either satisfy these “winning position conjectures” or it would not: if every conjecture were true then any winning position would satisfy all of the conjectures. At any moment in the game N will have a number of possible moves. The move heuristic that we used was to choose the move yielding a board position that satisfied the fewest number of the conjectures—on the theory that this move would yield a position that was least likely to be a winning position for P. We did not implement any look-ahead in our move heuristic.
     </paragraph>
     <paragraph>
      A sample of the generated conjectures—all the upper bound conjectures for the number of cookies on the diagonal of the game board—are recorded in Table 17. To the extent that all of the conjectures are true, it may be that they completely characterize winning game positions. In this case a player, human or robot, basing their moves on these conjectures can play a maximally intelligent game of Chomp.
     </paragraph>
    </section>
    <section label="10">
     <section-title>
      Future work
     </section-title>
     <paragraph>
      These preliminary results show that a conjecture-making program based on the Dalmatian heuristic can be of use to researchers in their investigations of bounds of real number invariants of objects. Our example of a conjecture-based Chomp playing program suggests how an automated conjecture-making functionality might be used in the design of other intelligent behaviors.
     </paragraph>
     <paragraph>
      Researchers who use our program may be able to improve their results in various ways. Some possibilities include the following.
     </paragraph>
     <list>
      <list-item label="1.">
       Add more invariants. This is not an issue in the design of our program but, rather, in its use. We used relatively small numbers of invariants. In contrast, DeLaVina's Graffiti.pc included more than 100 invariants when it was originally developed in 2001 [2], and which now has many more.
      </list-item>
      <list-item label="2.">
       Vary the counterexample-finding process. Instead of systematically generating all possible small counterexamples, or choosing random examples of various size objects, it might be useful to choose examples that are extremal with respect to one of the invariants in the formula for a conjectured bound. Hansen and Caporossi's AGX, for instance, is able to generate these examples.
      </list-item>
      <list-item label="3.">
       Add existing bounds (ones proved in the literature) and conjectures to the program. In this way, the program could only produce conjectures that for which there is at least one example where the produced conjecture gives a better bound than any known theorem or conjecture. In Fajtlowicz's terms, the produced conjectures would be “informative” or “significant” compared to existing theory. We did not do this in our initial experiments but did use this idea successfully for our independence number conjectures.
      </list-item>
      <list-item label="4.">
       Use a property-relations conjecture-making program. Generated counterexamples may have certain properties. If these commonalities can be identified, it may be possible to refine many conjectures which are “almost true”. The generalization of the Dalmatian heuristic to the design of a program that makes conjectures about relations of properties of objects is explained below.
      </list-item>
     </list>
     <paragraph>
      Lastly we discuss an idea for extending the automation of invariant-relation conjectures to the automation of property-relation conjectures. The Dalmatian heuristic, as described, is used to make conjectures about relations between the invariants of an object. Conjectures between the properties of an object may also be of interest. A property is a condition that an object does or does not have. An integer is perfect if it equals the sum of its proper divisors. “Being perfect” is an integer property: any given integer does or does not have this property. (“Being wet” is not an integer property.) An example of a property-relation conjecture is: If an integer is perfect then it is even. This can also be stated as “Being perfect is a sufficient condition for being even” or, “Being even is a necessary condition for being perfect.”
     </paragraph>
     <paragraph>
      The analogues of upper or lower bounds for an invariant of interest are necessary or sufficient conditions for a property of interest. Let P be the property that an integer is perfect. If sufficient conditions for an integer to have this property are desired, a conjecture-making program would need to produce property-expressions {a mathematical formula}Q1,Q2,…, and statements of the form, “If an integer has property {a mathematical formula}Qi then it has property P” (or, more simply, “If {a mathematical formula}Qi then P”). If necessary conditions are desired then the program would need to produce statements of the form, “If an integer has property P then it has property {a mathematical formula}Qi.”
     </paragraph>
     <paragraph>
      Let {a mathematical formula}O1,…,On be examples of objects of a given type. Let {a mathematical formula}Q1,…,Qk be properties. And let P be a property for which conjectured necessary or sufficient conditions are of interest. If the objects are the integers {a mathematical formula}G1,…,Gn, and P is the property “is perfect” then {a mathematical formula}P(Gi) would be True if {a mathematical formula}Gi is perfect and False if {a mathematical formula}Gi is not perfect.
     </paragraph>
     <paragraph>
      An unlimited stream of boolean functions of the invariants can then be formed: {a mathematical formula}Q1∧Q2, {a mathematical formula}¬Q1, {a mathematical formula}Q1∨Q3, {a mathematical formula}(Q2∧Q4)∨Q3, etc. This stream can be produced in any way at all. These expressions can then be used to form conjectured necessary or sufficient conditions for P. If we are interested in necessary conditions for P, say, we can form the statements {a mathematical formula}P⇒Q1∧Q2, {a mathematical formula}P⇒¬Q1, {a mathematical formula}P⇒Q1∨Q3, {a mathematical formula}P⇒(Q2∧Q4)∨Q3, etc. These statements can be interpreted as being true for all the objects of the given type. That is, the statement {a mathematical formula}P⇒Q1∧Q2 can be interpreted as, “For every object {a mathematical formula}O, {a mathematical formula}P(O)⇒Q1(O)∧Q2(O).” A conjectured necessary condition Q is only added to the database of conjectures if the property passes the following two tests.
     </paragraph>
     <list>
      <list-item label="1.">
       (Truth test.) The candidate conjecture {a mathematical formula}P⇒Q is true for all of the stored objects {a mathematical formula}O1,…,On, and
      </list-item>
      <list-item label="2.">
       (Significance test.) There is an object {a mathematical formula}O∈{O1,…,On} such that {a mathematical formula}¬Q(O)∧(Q1(O)∧…∧Qr(O)), where {a mathematical formula}Q1,…,Qr are the currently stored conjectures. That is, the candidate conjecture would give a better necessary condition for {a mathematical formula}P(O) than any previously conjectured necessary condition.
      </list-item>
     </list>
     <paragraph>
      If we are interested in sufficient conditions for P we can form the statements {a mathematical formula}Q1∧Q2⇒P, {a mathematical formula}¬Q1⇒P, {a mathematical formula}Q1∨Q3⇒P, {a mathematical formula}(Q2∧Q4)∨Q3⇒P, etc. These statements can be interpreted as being true for all the objects of the given type. That is, the statement {a mathematical formula}Q1∧Q2⇒P can be interpreted as, “For every object {a mathematical formula}O, {a mathematical formula}Q1(O)∧Q2(O)⇒P(O).” A conjectured sufficient condition Q is only added to the database of conjectures if the property passes the Truth and Significance tests. In this case the significance test would be as follows: Check that there is an object {a mathematical formula}O∈{O1,…,On} such that {a mathematical formula}Q(O)∧¬(Q1(O)∧…∧Qr(O)), where {a mathematical formula}Q1,…,Qr are the currently stored conjectures. That is, the candidate conjecture would give a better sufficient condition for {a mathematical formula}P(O) than any previously conjectured sufficient condition.
     </paragraph>
     <paragraph>
      Another way to think about property-relation conjectures is in terms of the sets of objects that have some property. Let {a mathematical formula}P be the set of objects that have property P. Necessary conditions for membership in {a mathematical formula}P define a super-class {a mathematical formula}N of {a mathematical formula}P. What is wanted are conjectures that make this super-class smaller and smaller. So a conjectured necessary condition Q is informative if, together with the previous conjectures, it defines a smaller super-class {a mathematical formula}N′ with {a mathematical formula}P⊆N′⊂N.
     </paragraph>
     <paragraph>
      Similarly, sufficient conditions for membership in {a mathematical formula}P define a sub-class {a mathematical formula}S of {a mathematical formula}P. What is wanted here are conjectures that make this sub-class larger and larger. So a conjectured sufficient condition Q is informative if, together with the previous conjectures, it defines a larger sub-class {a mathematical formula}S′ with {a mathematical formula}S⊂S′⊆P.
     </paragraph>
     <paragraph>
      The first author described a Dalmatian-style necessary condition heuristic in [13]. DeLaVina and Waller described and implemented a Dalmatian-style sufficient condition heuristic in [73], that they call “Sophie”. The Sophie version of Graffiti.pc has produced some useful conjectures including the following.
     </paragraph>
     <list>
      <list-item label="1.">
       (WoW2 #196a) For any connected graph G, if {a mathematical formula}α(G)=r(G) then G has a Hamiltonian path [73], where α is the independence number of the graph, and r is the radius. A Hamiltonian path in a graph is a path which visits each vertex exactly once. Here the objects are graphs, and the properties are “has equal independence number and radius” and “has a Hamiltonian path”. Sufficient conditions for a graph having a Hamiltonian path have been of continuing interest [74], [75].
      </list-item>
      <list-item label="2.">
       (WoW2 #329) For any graph G, G is König–Egerváry if and only if {a mathematical formula}α(G)=αc(G), where α is the independence number of the graph, and {a mathematical formula}αc is the critical independence number of the graph. A graph is König–Egerváry if the independence number of the graph plus the matching number of the graph equals the number of vertices of the graph. These graphs are a generalization of bipartite graphs (the König–Egerváry Theorem guarantees that bipartite graphs have this property [58]). It has been of continuing interest to find new characterizations for this class of graphs [76], [77], [78], [79]. Sophie's conjecture was proved in [64].
      </list-item>
     </list>
     <paragraph>
      We conclude this section by emphasizing that the Dalmatian heuristic can be applied to the production of non-mathematical conjectures: there is no requirement that the object-types be mathematical. They can just as well be physical. The only requirement is that the object-types have real number invariants. Application of the Dalmatian heuristic in a given situation requires that the problem can be represented as a question about the value of a numerical invariant of an “object”. The answer will be found in terms of relations of other numerical invariants of the object. So once the object, main invariant, and other invariants are specified, and one or more data examples are provided, conjectured bounds for the main invariant can be generated; and, assuming we have the values of the other invariants, these conjectures can be used to make predictions about the value of the main invariant. In a sequel to this paper we plan to discuss our ideas for using automated conjecture-making programs in the design of conscious robots.
     </paragraph>
     <paragraph>
      We believe that automated conjecture-making of invariant and property relations have even broader applications than we have described here, and that researchers will experiment with conjecture-making programs in a variety of settings.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Acquiring and using the program
     </section-title>
     <paragraph>
      We provide a program for experimentation and further development. Readers are encouraged to make their own explorations. Our program Conjecturing is available at: nvcleemp.github.io/conjecturing/. It functions as a package of the Sage open source mathematical software program [84]. Sage is intended as a free replacement for general mathematical software programs such as Maple, Matlab and Mathematica. In contrast with proprietary programs, anyone can examine, correct, and improve Sage's included algorithms and code. Sage users who develop programs for their own research are encouraged to include them in the public distribution of Sage, for general use; the user base, and community of developers, are large and growing. Versions of Sage for all major operating systems, manuals, and documentation are available at: www.sagemath.org. Examples, and the use of our program, are discussed below.
     </paragraph>
     <paragraph>
      Our program is designed as a Sage package. The attraction of Sage for this project stems from the fact that it is free, that it is easy-to-use, that it has a large number of built-in invariants for a variety of mathematical objects, and that other researchers can easily use our code. Sage uses Python as its interface language and includes well-known packages such as GAP for computer algebra, SINGULAR for algebraic geometry, PARI for number theory, LAPACK for linear algebra, R for statistical computation, NumPy and SciPy for numerical computing, and CVXOPT for convex optimization, linear and semidefinite programming.
     </paragraph>
     <paragraph>
      The first part of the program is the expression generator described earlier. This C program is wrapped into a Sage package which allows it to be installed with one command. The second part of the program, containing the main loop, is the Python file conjecturing.py. This file can be loaded into Sage to provide a seamless integration of the expressions generator using the Dalmatian heuristic. It provides a method conjecture that—in its most basic form—takes three arguments: a list of objects, a list of invariants and a main invariant, that is, the invariant for which one wants to find a bound. The objects can be any (Sage) objects; the only provision is that the invariants are able to translate the objects to numerical values. The invariants must be functions of a single argument (the inputs are the objects). The main invariant is represented by the index of its location in the list of invariants.
     </paragraph>
     <paragraph>
      The conjecture-making code was partly based on Patrick Gaskill's code for a related project, and is available at: github.com/IndependenceNumberProject/inp.
     </paragraph>
     <paragraph>
      What follows is a short example of how the conjecture method can be used in Sage.{a mathematical formula} The first two lines of this example define a new (that is, not existing in Sage) graph theoretic invariant max_degree. The next line specifies invariants to be a list of built-in and user-defined invariants; these will potentially appear in the conjectured expressions; and the user can remove any of these and add as many others as she likes. The fourth line specifies objects to be a list of graphs that will be used by the program when making conjectures—in this case the list is initialized with three complete graphs. Again, the user can remove any of these and add arbitrarily many others. The conjecture function takes the lists of invariants and objects, together with a number specifying which of the invariants in the invariants list should be used as the main invariant; in this case, 0 is input, indicating that invariants[0]—namely, Graph.size—should be used as the main invariant. The last three lines are the output of the program, three conjectured upper bounds for the size of a graph. All three conjectures happen to be false: they are all necessarily true for the complete graphs on 3, 4 and 5 vertices—but are false for other graphs not in the input list.
     </paragraph>
     <paragraph>
      Scripts that generate the conjectures for most of the reported runs of our program are also available at: nvcleemp.github.io/conjecturing/. The scripts used to generate the conjectures above are listed in Table 18. The purpose of providing these scripts is two-fold. They allow for the reproducibility of our results, and they also provide models for researchers to imitate in generating their own conjectures. Exact reproducibility will depend on whether the researcher is using a machine that is the same speed as the second author's. The expression generation program times out after 5 seconds. A user on a faster machine will generate more expressions to test for truth and significance than our machine did; one on a slower machine will generate fewer expressions. In either case, there is then a possibility of ending up with slightly different conjectures than the conjectures we report below.
     </paragraph>
     <paragraph>
      All invariants used in our experiments are either built-in Sage functions or user-defined procedures. The code for the user-defined procedures can be found in the files: matrixtheory.py, numbertheory.py, and graphtheory.py.
     </paragraph>
     <paragraph>
      Here are more details about the generation of the matrix theory conjectures. The first rounds of conjectures used symmetric {a mathematical formula}2×2 matrices with integer entries ranging from −10 to 10. This was to allow systematic generation of a family of examples. In fact, {a mathematical formula}2×2 matrices turned out to be too special of a subclass of matrices to lead to good conjectures—other researchers quickly found {a mathematical formula}3×3 matrices that were counterexamples to many of these.
     </paragraph>
     <paragraph>
      Furthermore, the specialness of these examples led to non-general conjectures. In one run, for instance, the program conjectured that, for any symmetric matrix, the absolute value of the determinant is at least as large as the smallest eigenvalue. In fact, this conjecture is true for {a mathematical formula}2×2 matrices with integer entries. But it is certainly not true in general (a diagonal matrix with {a mathematical formula}12's on the diagonal is a counterexample).
     </paragraph>
     <paragraph>
      We expect that generation of larger matrices with a larger range of entries would lead to better conjectures. In this case it will become impossible to systematically generate any interesting class, and a researcher may experiment with choosing randomly generated matrices from a chosen class.
     </paragraph>
     <paragraph>
      McKay's program geng, which we used for generating all graphs up to any specified order, is freely available for non-commercial use and works easily with Sage.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>