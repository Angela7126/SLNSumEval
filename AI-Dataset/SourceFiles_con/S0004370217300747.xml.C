<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Automatically improving constraint models in Savile Row.
   </title>
   <abstract>
    When solving a combinatorial problem using Constraint Programming (CP) or Satisfiability (SAT), modelling and formulation are vital and difficult tasks. Even an expert human may explore many alternatives in modelling a single problem. We make a number of contributions in the automated modelling and reformulation of constraint models. We study a range of automated reformulation techniques, finding combinations of techniques which perform particularly well together. We introduce and describe in detail a new algorithm, X-CSE, to perform Associative–Commutative Common Subexpression Elimination (AC-CSE) in constraint problems, significantly improving existing CSE techniques for associative and commutative operators such as +. We demonstrate that these reformulation techniques can be integrated in a single automated constraint modelling tool, called Savile Row, whose architecture we describe. We use Savile Row as an experimental testbed to evaluate each reformulation on a set of 50 problem classes, with 596 instances in total. Our recommended reformulations are well worthwhile even including overheads, especially on harder instances where solver time dominates. With a SAT solver we observed a geometric mean of 2.15 times speedup compared to a straightforward tailored model without recommended reformulations. Using a CP solver, we obtained a geometric mean of 5.96 times speedup for instances taking over 10 seconds to solve.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In numerous contexts today we are faced with making decisions of increasing size and complexity, where many different considerations interlock in complex ways. Consider, for example, a staff rostering problem to assign staff to shifts while respecting required shift patterns and staffing levels, physical and staff resources, and staff working preferences. The decision-making process is often further complicated by the need also to optimise an objective, such as to maximise profit or to minimise waste.
     </paragraph>
     <paragraph>
      It is natural to characterise such problems as a set of decision variables, each representing a choice that must be made in order to solve the problem at hand (e.g. which staff member is on duty for the Friday night shift), and a set of constraints describing allowed combinations of variable assignments (e.g. a staff member cannot be assigned to a day shift immediately following a night shift). A solution is an assignment of a value to each variable satisfying all constraints. Many decision-making and optimisation formalisms take this general form, including: constraint programming (CP) [61], propositional satisfiability (SAT) and its extensions [10], and operations research approaches, particularly Mixed Integer Programming (MIP) [32]. These approaches have much in common, but differ in the types of decision variables and constraints they support, and the inference mechanisms used to find solutions.
     </paragraph>
     <paragraph>
      In all of these formalisms the model of the problem is crucial to the efficiency with which it can be solved. A model in this sense is the set of decision variables and constraints chosen to represent a given problem. There are typically many possible models and formulating an effective model is notoriously difficult [54]. Therefore, automating modelling is a key challenge. In this paper we investigate automated reformulation of models when targeting CP and SAT solvers, with the goal of reaching an efficient model by a sequence of reformulations starting with a simple model. We investigate a range of reformulation techniques and some of their interactions, and show in some cases that a very high performance model can be created in this way from a naïve model.
     </paragraph>
     <section label="1.1">
      <section-title>
       Constraint programming, propositional satisfiability, and tailoring
      </section-title>
      <paragraph>
       CP and SAT both follow the general template described above, in that an assignment is sought for a set of variables to satisfy a set of constraints. The key difference is in how CP and SAT represent a given problem. In SAT variables are uniformly Boolean and the constraints are Boolean formulae, expressed in conjunctive normal form [10]. CP provides a richer language of discrete variables with domains either given in extension or expressed in terms of upper and lower bounds, arithmetic and logical operators over these variables, and a library of ‘global’ constraints that capture common reasoning patterns.
      </paragraph>
      <paragraph>
       The two formalisms have complementary strengths. The simplicity of SAT supports the implementation of highly efficient solvers, employing techniques such as conflict-driven learning, watched literals, restarts and dynamic heuristics for backtracking solvers [44], and sophisticated incomplete techniques such as stochastic local search [62]. These solvers are able reliably to find solutions to SAT problems with millions of variables, and as a result SAT has many important applications, such as hardware design and verification, planning, and combinatorial design [40]. The richer language of CP enables concise models, and powerful reasoning driven by global constraints has also given rise to a wide variety of successful applications, including configuration, vehicle routing, scheduling and planning [61].
      </paragraph>
      <paragraph>
       The importance of modelling is well recognised in both fields. In CP a number of constraint modelling languages have been developed, such as OPL [68], MiniZinc [65] and Essence Prime [49]. These languages provide facilities to model parameterised classes of problems (where an individual problem instance is specified by giving values for the class parameters), such as arrays and iteration or comprehension, and to abstract away from the specific details of the many available individual constraint solvers. When targeting SAT, most effort has focussed on constructing performant encodings (i.e. translations into SAT) of classes of constraints such as the allDifferent or arithmetic constraints [53], [69], [29], [63], [67]. There has been little attention on the issue of translating a higher level modelling language effectively to SAT.
      </paragraph>
      <paragraph>
       Tailoring[60] is the process of taking a constraint model of a problem class in a solver-independent modelling language and a value for each of the class parameters, and translating the problem instance into a form suitable for a given solver. We focus herein on reformulation of the constraint modelling language Essence Prime [49], using the constraint modelling assistant Savile Row [47], [50]. Essence Prime is similar to other constraint modelling languages such as OPL and MiniZinc. Savile Row is able to translate Essence Prime to target CP and SAT solvers. Tailoring must be efficient: it is performed separately for each problem instance, hence any computationally expensive reformulation performed during tailoring must pay for itself by saving time during solving. Tailoring presents an opportunity to reformulate a model to improve it in a number of ways, some of which are illustrated in our example below.
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Motivating example
      </section-title>
      <paragraph>
       We use Balanced Incomplete Block Design (BIBD) [52] as a motivating example to illustrate four quite different reformulations working together to dramatically improve a simple model. All four reformulations are automated in Savile Row. BIBD is a problem class with three integer parameters v, k and λ, and two constants derived from the parameters {a mathematical formula}b=λv(v−1)k(k−1) and {a mathematical formula}r=λ(v−1)k−1. The problem is to place each of v objects into a subset of the b blocks, so that each block contains k distinct objects, each object occurs in exactly r blocks, and every two distinct objects occur together in exactly λ blocks. The objects and blocks are both interchangeable. The BIBD problem arose from experimental design theory. We use Meseguer and Torras's first model [43], extended with {a mathematical formula}Lex2 symmetry breaking constraints [19] (i.e. constraints that forbid a set of solutions that are symmetric to other solutions). The model has a v by b matrix m of Boolean decision variables, where the variable {a mathematical formula}m[i,j] indicates whether object i is contained in block j. The model is described in detail in Section 5.9.1.
      </paragraph>
      <paragraph>
       Savile Row first substitutes the values of v, k, λ, b and r throughout. Then the matrix m is replaced with vb individual Boolean variables, and all quantifiers and comprehensions are unrolled to construct the concrete set of constraints. The model is now almost suitable for output to a conventional constraint solver. However, there is an opportunity to substantially improve the model before it is specialised for a solver.
      </paragraph>
      <paragraph>
       Each decision variable has a set of possible values that it may take, called its domain. The first reformulation step is to filter the domains of the decision variables, as described in Section 5.4. Domain filtering removes values from the variable domains that cannot take part in any solution. Consider the problem instance where {a mathematical formula}v=8,k=4,λ=6. Domain filtering assigns 70 of the original 224 decision variables in the matrix m, as shown in Fig. 1. The second step is variable unification, as described in Section 5.4. Variable unification removes decision variables in a number of cases. In this case each of the deleted variables is equal to a constant. For example, {a mathematical formula}m[1,1] is replaced by 0 throughout. After variable unification many of the constraints contain constants. Each expression type in Savile Row has a simplifier (described in Section 3.3). Simplifiers will at least evaluate constant expressions, but can in some cases do significantly more than that. In this case, a sum expression (representing a scalar product constraint between the first and fifth rows) may be simplified.{a mathematical formula}
      </paragraph>
      <paragraph>
       This expression simplifies to a much shorter expression that contains no products:{a mathematical formula}
      </paragraph>
      <paragraph>
       The first two rows and parts of the third row are assigned, allowing many of the scalar product constraints to be simplified. Each row has a sum constraint such as:{a mathematical formula}
      </paragraph>
      <paragraph>
       The fourth step is to extract common subsets of terms between row constraints and (simplified) scalar product constraints. This is a type of common sub-expression elimination (as described in Section 2 below). The common subset {a mathematical formula}m[5,15]+⋯+m[5,28] is represented by a new variable a, resulting in the following three constraints.{a mathematical formula}
      </paragraph>
      <paragraph>
       Variable unification replaces a with 6 throughout, leading to the following:{a mathematical formula}
      </paragraph>
      <paragraph>
       Meseguer and Torras's model was improved by Frisch et al. [23] by the addition of a set of implied constraints (i.e. redundant constraints that are entailed by the original set of constraints), creating the best published model (to our knowledge). Savile Row automatically generates a superset of the implied constraints proposed by Frisch et al., and consequently the Savile Row model outperforms the Frisch et al. model in our experiments in Section 5.9.1. This example illustrates a number of simple reformulations combining to substantially improve the formulation of a constraint model.
      </paragraph>
     </section>
     <section label="1.3">
      <section-title>
       Contributions
      </section-title>
      <paragraph>
       We make three main contributions in this paper.
      </paragraph>
      <list>
       <list-item label="1.">
        We evaluate a range of reformulations for use in automated modelling. Common Sub-expression Elimination (CSE) is a particular focus of this paper [60], [59], [2]. CSE is a type of constraint reformulation that has proved to be useful on a range of problems, including both finite-domain and numerical constraint problems. We contribute new algorithms for Identical CSE and Active CSE that improve on existing work. Furthermore, we have discovered sets of reformulations that together are much more effective than any single reformulation.
       </list-item>
       <list-item label="2.">
        We introduce and describe in detail a new algorithm, X-CSE, to perform AC-CSE (Associative–Commutative Common Sub-expression Elimination). This uses the fact that operators such as + are associative and commutative: expressions containing such operators can be rearranged to reveal additional common subexpressions (CSs). We show that X-CSE is able to find CSs automatically in a variety of problems, and that using these subexpressions can greatly reduce search and improve solving time. A particular advantage of X-CSE is that it is able to find and exploit small CSs that occur in many constraints, as well as larger ones that occur in few constraints. We show that X-CSE can be particularly effective in combination with other reformulations, specifically an automated reformulation of allDifferent constraints leading to sum constraints, and when filtering domains using a variant of Singleton Arc Consistency. When applying X-CSE we demonstrate substantial gains in performance.
       </list-item>
       <list-item label="3.">
        We demonstrate that the reformulations described above can be integrated in a single automated constraint modelling tool, called Savile Row, whose architecture we describe. We use Savile Row as an experimental testbed to evaluate each reformulation on a set of 50 problem classes with 596 instances in total. We describe a very extensive set of experiments where reformulations are switched on one by one and their effects analysed as part of the system.
       </list-item>
      </list>
     </section>
    </section>
    <section label="2">
     <section-title>
      Background and related work
     </section-title>
     <paragraph>
      There are many ways of improving constraint models, some requiring manual interaction [5], and others that are entirely automatic [24]. For example these methods can discover global constraints or automatically detect and remove symmetries [42]. These improvements often complement each other, for example Frisch, Jefferson, and Miguel [23] show how breaking symmetries can lead to effective implied constraints for BIBDs. In this section we review the most relevant related work.
     </paragraph>
     <section label="2.1">
      <section-title>
       Variable unification
      </section-title>
      <paragraph>
       Unifying equal variables is a standard technique implemented by a number of tools including MiniZinc [65], Savile Row [47], [50] and IBM CP Optimizer Presolve [36]. Details of our approach to variable unification are given in Section 5.4.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Variable domain filtering
      </section-title>
      <paragraph>
       Filtering the domains of decision variables is a recognised preprocessing technique in constraint programming. Domain filtering removes values that cannot take part in any solution. Strong consistencies may be used to tighten the formulation of an instance [7], [37]. Domains may be filtered by some form of propagation prior to (and potentially enabling) other reformulations. IBM CP Optimizer Presolve uses propagation to obtain tighter bounds for variables and expressions, and redundant constraints are removed before search [36]. The strength of propagation is unspecified.
      </paragraph>
      <paragraph>
       We have previously [47], [50] filtered the user-defined decision variables using a strong consistency related to Singleton Arc Consistency (SAC) [7]: SACBounds applies the SAC test to prune the upper and lower bound of each variable to exhaustion. The Minion solver [30] was used to establish SACBounds. Leo and Tack filtered domains of both user-defined and introduced decision variables in MiniZinc [39], using the standard level of propagation of the solver Gecode [28]. Variable domain filtering has proven to be valuable alone [39] and as an enabler of other reformulations [47], [50]. Our approach to domain filtering is described in Section 5.4.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Aggregation
      </section-title>
      <paragraph>
       Aggregation algorithms replace a set of constraints with a different formulation, typically to obtain more powerful propagation in a CP solver. CGRASS [24] replaces cliques of not-equal constraints with allDifferent constraints. IBM CP Optimizer Presolve [36] also replaces cliques of not-equal constraints with allDifferent, as well as collecting overlapping count expressions (that constrain the cardinality of a given value in a set of variables). IBM CP Optimizer Presolve also merges overlapping linear constraints on {a mathematical formula}{0,1} variables, and in some cases merges arithmetic constraints with other constraint types.
      </paragraph>
      <paragraph>
       Aggregation is essentially a forward-chaining approach: a pattern is identified in the set of constraints and replaced with an improved formulation such as a global constraint. Other approaches to identifying global constraints are covered in Section 2.7. Two types of aggregation are implemented in Savile Row as described in Section 5.5.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Flattening and identical common subexpression elimination
      </section-title>
      <paragraph>
       Flattening is the process of taking a nested expression and reducing the degree of nesting by replacing a subexpression with a new variable. For example, given the product {a mathematical formula}X×(Y+Z) and a target solver that does not allow sums inside products, the flattening process will add a new variable aux, replace the product with the new expression {a mathematical formula}X×aux and add a new constraint {a mathematical formula}aux=Y+Z. We say that {a mathematical formula}X×(Y+Z) is flattened to {a mathematical formula}X×aux and that {a mathematical formula}Y+Z is extracted.
      </paragraph>
      <paragraph>
       Common sub-expression elimination (CSE) is widely used in compilers to avoid repeated computation [15]. CSE was applied in the context of finite-domain constraint languages by Rendl [60], [59]. CGRASS [24] could also perform CSE through the combination of its introduce and eliminate rules. In its simplest form, which we call “Identical CSE”, CSE takes two or more syntactically identical sub-expressions that must be flattened, and flattens them all using the same auxiliary variable. This reduces both the number of constraints and auxiliary variables. Importantly, Identical CSE can reduce the search space dramatically [60], [59] by linking different constraints together thus strengthening constraint propagation in a conventional CP solver.
      </paragraph>
      <paragraph>
       The SMT solver CVC4 merges identical subtrees in its abstract syntax tree [4]. It is not clear whether this affects the search or is simply a memory saving feature.
      </paragraph>
      <paragraph>
       The algorithm introduced by Rendl [59] and later extended by Stuckey and Tack [65] performs CSE during flattening. The algorithm maintains a hash table that maps each expression extracted so far to the auxiliary variable created for it. When extracting an expression E, the algorithm looks up E in the hash table and (if present) uses the auxiliary variable in the hash table rather than creating a new auxiliary. Rendl's algorithm has the advantage of being a simple addition to the flattening process, however there are two disadvantages: the order in which CSEs are extracted is fixed to the order of flattening, and the candidate expressions for CSE must be the expressions that are extracted by flattening. For example, most constraint solvers can accept inequality constraints without flattening so Rendl's algorithm would miss the common subexpression {a mathematical formula}x+y+z in the constraints {a mathematical formula}x+y+z≤10 and {a mathematical formula}x+y+z≥11.
      </paragraph>
      <paragraph>
       In this paper we present a new algorithm for Identical CSE in Section 5.7 that is independent of flattening thus avoiding both disadvantages of Rendl's algorithm. For example the new algorithm is able to extract {a mathematical formula}x+y+z from {a mathematical formula}x+y+z≤10 and {a mathematical formula}x+y+z≥11 and allow constraint solvers to immediately deduce the contradiction.
      </paragraph>
      <paragraph>
       Stuckey and Tack describe CSE in the constraint language MiniZinc 2 that has user-defined functions and local decision variables [65]. Function call sites must be syntactically identical to trigger CSE, therefore it is a form of Identical CSE, essentially using the same algorithm as Rendl. The current version of Essence Prime does not have user-defined functions.
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       Normalisation and active CSE
      </section-title>
      <paragraph>
       One way CSE has been fruitfully extended is by matching subexpressions that are not syntactically identical [60]. This is achieved in two ways. The first is normalisation, where prior to CSE the expression tree is converted to a normal form. This converts some semantically equivalent expressions (such as {a mathematical formula}C=B+A+1−1 and {a mathematical formula}A+B=C) to syntactically identical expressions. The second is Active CSE, where two expressions A and B may be matched if they are identical after some transformation is applied to one. For example, Active CSE can match {a mathematical formula}A&lt;B with {a mathematical formula}A≥B by a simple negation, replacing one with an auxiliary variable a and the other with ¬a. Rendl's algorithm described above is easily extended to Active CSE [59]. When an expression E is extracted by flattening, the extended algorithm looks up E and each transformation of E in the hash table. When a transformation of E is present, the inverse transformation is applied to the auxiliary variable. For example, suppose the transformation is to negate E then apply one of De Morgan's laws, the inverse is (also) to negate the auxiliary variable. Rendl's Active CSE algorithm has the same problems as the Identical CSE algorithm described above. We present a different algorithm for Active CSE in Section 5.8 and relate it to Rendl's work.
      </paragraph>
     </section>
     <section label="2.6">
      <section-title>
       Associative–commutative CSE
      </section-title>
      <paragraph>
       One of the forms of CSE we investigate is Associative–Commutative CSE (AC-CSE), which exploits the properties of associativity and commutativity of binary operators (e.g. + and ×). Expressions containing these operators can be rearranged to reveal common subexpressions. As an example, take the following two constraints over four variables, each with domain {a mathematical formula}{0…10}: {a mathematical formula}w+x+y+z=6,z+y+w=5. Conventional constraint propagation (bounds({a mathematical formula}R) consistency [13] or GAC [61] applied to both constraints) will not reveal the fact that {a mathematical formula}x=1. AC-CSE can extract {a mathematical formula}w+y+z and replace it with an auxiliary variable a to give the following three constraints: {a mathematical formula}x+a=6,a=5,a=w+y+z. Performing constraint propagation (e.g. bounds({a mathematical formula}R) consistency [13]) on this set will assign x to 1.
      </paragraph>
      <paragraph>
       An Associative–Commutative Common Subexpression (AC-CS) of a set of associative and commutative (AC) expressions is a set of at least two terms that appear in each of the AC expressions. In the example above, the terms {a mathematical formula}w,y,z appear in both the original sum constraints, hence {a mathematical formula}{w,y,z} is an AC-CS of the two sum constraints.
      </paragraph>
      <paragraph>
       A simple normalisation step, such as sorting the terms in the AC expressions, followed by examining contiguous subsequences of terms within AC expressions, can reveal some but not all of the available AC-CSs. More is necessary to find AC-CSs in general. The largest contiguous subsequence in the example above (sorted alphabetically) is {a mathematical formula}y+z, so this approach would miss the maximal AC-CS {a mathematical formula}w+y+z.
      </paragraph>
      <paragraph>
       Araya, Neveu and Trombettoni [2] exploited common subexpressions among + and × expressions in the context of numerical CSP. They proposed two algorithms named I-CSE and I-CSE-NC. Both algorithms apply a form of AC-CSE prior to flattening as a separate operation. The first pass of both algorithms is to transform the abstract syntax tree into a directed acyclic graph where identical subexpressions are represented once. The second step is to intersect each pair of sums and pair of products to create a set of candidate AC-CSs. As we will see in Section 4.3 other AC-CSs (generated by the intersection of three or more sums) can also be useful, but I-CSE and I-CSE-NC will never extract them. Later passes extract the AC-CSs from the original expressions.
      </paragraph>
      <paragraph>
       Araya et al. defined two AC-CSs {a mathematical formula}f1 and {a mathematical formula}f2 to be in conflict if {a mathematical formula}f1∩f2≠∅, {a mathematical formula}f1⊈f2 and {a mathematical formula}f2⊈f1. Two AC-CSs in conflict cannot both be extracted from the same expression. When a set of AC-CSs in conflict are subsets of the same original expression s, then I-CSE copies s a sufficient number of times to extract each of the AC-CSs from at least one copy. I-CSE-NC (for No Conflicts) does not copy s, it simply extracts a single maximal subset of the candidate AC-CSs from s. Consider the following example:{a mathematical formula} In this example I-CSE would extract three AC-CSs: {a mathematical formula}v+w+x, {a mathematical formula}v+w+y and {a mathematical formula}v+w+z. I-CSE would duplicate each of the original constraints resulting in six constraints and three further constraints to define the auxiliary variables. I-CSE-NC can extract only one AC-CS. Suppose it extracts {a mathematical formula}v+w+x, then at this point {a mathematical formula}v+w+y and {a mathematical formula}v+w+z cease to be AC-CSs:{a mathematical formula} I-CSE-NC can only extract AC-CSs from the original expressions, so fails to exploit the AC-CS {a mathematical formula}v+w. Even on this small example I-CSE increases the size of the model substantially. I-CSE-NC has not, but it has missed a potentially useful AC-CS and has not linked {a mathematical formula}v+w+y+z to the other two sums. I-CSE and I-CSE-NC are both compared with our algorithm in Section 5.11. We implement the algorithms exactly as described in Section 4 of Araya et al. [2]. Both I-CSE and I-CSE-NC only extract AC-CSs from the original expressions, not from other AC-CSs.
      </paragraph>
      <paragraph>
       Bessière, Paparrizou and Stergiou [9] define two new consistencies, rBC2 and rBCall, both stronger than bound consistency [13]. Where bound consistency reasons with each constraint separately, rBC2 and rBCall consider multiple constraints together. Two reformulations are proposed that approximate rBC2 and rBCall for linear constraints: rBC2-Y and rBCall-Y. Whenever a pair of linear constraints share more than one variable and the coefficients are in the same proportion in both constraints, rBC2-Y extracts an AC-CS. For example, {a mathematical formula}2x+3y+z=5 and {a mathematical formula}4x+6y+w=5 share variables x and y, and the coefficients of x and y are in the same proportion in both constraints. When a constraint has multiple AC-CSs it is copied once for each. Where rBC2-Y links pairs of constraints, rBCall-Y links sets of constraints that share two or more variables with proportional coefficients. In other respects they are the same. Both are defined for a flat set of linear (in)equality constraints.
      </paragraph>
      <paragraph>
       In contrast to rBC2-Y and rBCall-Y, I-CSE requires coefficients to be identical to extract an AC-CS. However I-CSE can handle nested expressions in an AST and it packs AC-CSs into a minimal set of copies of the original expression.
      </paragraph>
      <paragraph>
       In Section 4 we describe our approach to AC-CSE and set it in context with I-CSE, rBC2-Y and rBCall-Y.
      </paragraph>
     </section>
     <section label="2.7">
      <section-title>
       Other related work
      </section-title>
      <paragraph>
       Charnley, Colton and Miguel [12] proposed an automated method of generating implied constraints for a problem class. They first solve small instances of the class and use machine learning to generate hypothetical implied constraints, and then use a theorem prover to test each hypothesis and those proven correct are added to the model. As a time-intensive method that works on the problem class it is quite different from our approach.
      </paragraph>
      <paragraph>
       Leo et al. [38] proposed a method to suggest global constraints to replace groups of constraints in a model. The method generates sample solutions of each candidate group of constraints and suggests global constraints from its library. This method is also time-intensive, requires human verification and is applied to a problem class.
      </paragraph>
      <paragraph>
       Bessière et al. [8] proposed an approach to learning implied parametric global constraints such as the global cardinality constraint (GCC) for problem instances. While promising results are given, the approach requires some human insight and is also likely to be much more time-consuming than syntactic operations such as aggregation and CSE.
      </paragraph>
      <paragraph>
       Symmetry and dominance breaking constraints may be generated at the class level using the methods of Mears et al. [42], [41]. A dominance breaking constraint rules out sub-optimal solutions of an optimisation problem. Symmetry and dominance breaking constraints are complementary to our work since they can enable other reformulations (as in the motivating example in Section 1.2).
      </paragraph>
      <paragraph>
       In SAT, research on preprocessing [66], [17], and inprocessing [34] interleaves the reformulation of a SAT model with solving. An example reformulation is “self-subsuming resolution” proposed by Eén and Biere [17]. Given the clauses {a mathematical formula}C1={x,a,b}, and {a mathematical formula}C2={x¯,a}, the resolvent is {a mathematical formula}C1′={a,b}. Since {a mathematical formula}C1′ subsumes {a mathematical formula}C1 we can replace {a mathematical formula}C1 with {a mathematical formula}C1′. Common subexpression elimination has been used in SAT by identifying common subclauses and replacing them by a new auxiliary variable and clauses equating the variable with the common subclause [70]. Preprocessing and inprocessing are highly effective in extending the reach of SAT solvers, however they necessarily operate on the lowest level representation of the problem, the raw SAT clauses, where higher-level patterns are difficult and/or costly to identify. In Savile Row, by contrast, a single common subexpression elimination can eliminate many SAT variables and clauses in the encoded problem.
      </paragraph>
      <paragraph>
       In a recent wide-ranging review Achterberg et al. [1] demonstrate the central importance of preprocessing techniques to the performance of modern MIP solvers. Similarly to Savile Row, MIP preprocessing consists of the application of a collection of relatively inexpensive procedures that together work to strengthen the model of a problem instance. These procedures are tailored to the linear inequalities that form the MIP input language, as opposed to the richer constraint language considered by Savile Row, removing redundant inequalities, replacing inequalities with stronger equivalents, strengthening coefficients, and strengthening the bounds on variables.
      </paragraph>
      <paragraph>
       Constraint Handling Rules (CHR) [26] is a declarative, rule-based, general-purpose programming language originally designed to write constraint solvers [27]. The rule-based formalism of CHR is a natural way to encode transformations similar to those made by Savile Row. However, we are not aware of work employing CHR to reformulate problem instances prior to search by a constraint or SAT solver. Cadmium [16] is an associative, commutative term rewriting system, inspired by CHR, designed to map the Zinc [3] language to solvers. To the best of our knowledge, in the transformation of Zinc associativity and commutativity are used not for common-subexpression elimination, but solely for matching local expressions. For example, a rule that matched {a mathematical formula}a∨¬a would also match {a mathematical formula}a∨b∨¬a, because ∨ is associative and commutative.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Architecture of Savile Row
     </section-title>
     <paragraph>
      Savile Row is a multi-pass term rewriting system. The frontend reads a model in the Essence Prime language into an abstract syntax tree (AST), along with a parameter file giving the values of the problem class parameters. Several backends target a range of solvers. The system has many passes, some of which are always performed, others are performed when the choice of backend requires it, and still others are optional reformulations. In this section we give an overview of the essential parts of the system, excluding optional reformulation passes described in Section 5. We refer to the entire process of transforming a model into input for a solver as the tailoring process [59].
     </paragraph>
     <section label="3.1">
      <section-title>
       First steps of the tailoring process
      </section-title>
      <paragraph>
       The first part of the tailoring process puts the problem instance into a form suitable for the later optional reformulation passes. The details are unimportant for this paper but the key points are as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        The relational semantics [25] is implemented by replacing all partial functions (e.g. division) with total functions [49].
       </list-item>
       <list-item label="2.">
        Problem class parameters and other constants are substituted into the model.
       </list-item>
       <list-item label="3.">
        All quantifiers and matrix comprehensions are unrolled.
       </list-item>
       <list-item label="4.">
        Matrices of decision variables (defined by find statements) are separated into individual decision variables. This enables domain filtering and unification of equal variables.
       </list-item>
      </list>
     </section>
     <section label="3.2">
      <section-title>
       Bounds of expressions
      </section-title>
      <paragraph>
       Each numerical expression type has a method to estimate the lower and upper bound of its value. For non-atomic expressions the method recursively finds the bounds of each of its subexpressions then calculates the bounds assuming each subexpression is independent. For example the lower bound of a sum {a mathematical formula}1+x+y is the sum of the lower bounds of 1, x and y. The method for variable identifiers takes the lower and upper bounds of the domain (from the quantifier, comprehension or the global symbol table that defines the variable). Bounds calculated in this way for an expression e are denoted {a mathematical formula}⌊e⌋ and {a mathematical formula}⌈e⌉. The estimated bounds are required to contain the true value of e in all solutions.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Simplifiers
      </section-title>
      <paragraph>
       Each expression type implemented in Savile Row has a simplifier, which is a function that examines an expression and may rewrite it to a semantically equivalent simpler expression. Simplifiers may examine the subexpressions in any way, including looking up the domains of variables and calculating bounds of subexpressions. As a minimum requirement the simplifier must evaluate the expression (i.e. replace it with a constant of the appropriate type) if the expression directly contains only constants. For example, the allDifferent constraint {a mathematical formula}allDiff([1,3,4]) contains a constant matrix, and since all the elements of the matrix are different it must be rewritten to true. On the other hand, {a mathematical formula}allDiff([1,2,x]) where x is a decision variable with domain {a mathematical formula}{3…10} is rewritten to true in the current version of Savile Row, but this is not a requirement.
      </paragraph>
      <paragraph>
       The simplifier for the expression type allDiff (that contains a one-dimensional matrix) performs the following rewrite steps:
      </paragraph>
      <list>
       <list-item label="•">
        If the matrix is unknown (e.g., a matrix comprehension) then do not rewrite the allDiff, otherwise continue.
       </list-item>
       <list-item label="•">
        If the matrix is of size 0 or 1 then rewrite the allDiff to true.
       </list-item>
       <list-item label="•">
        If any pair of expressions in the matrix are numerically equal or their ASTs are identical then rewrite to false.
       </list-item>
       <list-item label="•">
        For each expression in the matrix, find its bounds or (if it is a variable) look up its domain. If any constant c in the matrix is outside the bounds or domain of all other expressions then rewrite to a shorter allDiff that does not contain c.
       </list-item>
      </list>
      <paragraph>
       Notice that the simplifier does nothing if the allDiff contains a matrix comprehension or a function such as flatten. Quantifiers and comprehensions are unrolled early in the tailoring process (Section 3.1), and functions are evaluated as soon as their contents have the appropriate properties. For example, the flatten function is evaluated when the matrix contained in it is iterable in all dimensions. Once flatten has been evaluated, the allDiff simplifier will execute immediately.
      </paragraph>
      <paragraph>
       Simplifiers are applied to the AST in a bottom-up order. This allows each simplifier to assume that the children of the current AST node have already been simplified. Simplifiers are run to quiescence, as follows: suppose some AST node {a mathematical formula}n1 is replaced with {a mathematical formula}n2 by a simplifier. The tree rooted at node {a mathematical formula}n2 is then traversed in bottom-up order and {a mathematical formula}n2 or subtrees of it may be replaced again. Once the entire tree traversal has completed, the simplifier for each node has been executed and no simplifier can perform any further rewrites.
      </paragraph>
      <paragraph>
       Simplifiers have a central role in Savile Row and cannot be switched off. Other passes assume that the simplifiers have been run to quiescence. Whenever one pass makes a change to the AST, the simplifiers are run to quiescence before the next pass.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Negation normal form
       </section-title>
       <paragraph>
        Simplifiers for the logical connectives ∧, ∨ and ¬ are responsible for establishing a type of negation normal form by applying De Morgan's laws to push negation towards the leaves of the AST, and by removing double negation. Implication {a mathematical formula}A→B is rewritten to {a mathematical formula}¬A∨B. In some cases a negated constraint ¬A can be replaced by B where B is no more complex than A (e.g. {a mathematical formula}¬(A=B) is rewritten to {a mathematical formula}A≠B). The numerical comparison operators =, ≠, ≤, &lt; and also table (where the satisfying assignments of the constraint are explicitly listed) and negativetable (the negation of table) are all rewritten when negated.
       </paragraph>
      </section>
     </section>
     <section label="3.4">
      <section-title>
       General flattening
      </section-title>
      <paragraph>
       Once all optional reformulation passes have completed, any remaining nested expressions where the target solver does not support the nesting (e.g. a sum containing a product) are flattened by extracting the inner expression e to a new auxiliary variable a. The domain of a is {a mathematical formula}{⌊e⌋…⌈e⌉} unless extended domain filtering is enabled (Section 5.4 below). Extended domain filtering may provide a smaller domain for a.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Encoding to SAT
      </section-title>
      <paragraph>
       Our goal is to investigate whether reformulations performed on a constraint problem instance are beneficial when it is solved by encoding to SAT and using a state-of-the-art SAT solver. To achieve this we need to ensure that the baseline encoding to SAT is sensible. We have used standard encodings from the literature such as the order encoding for sums [67] and support encoding [29] for binary constraints. Also we do not attempt to encode all constraints in the language: several constraint types are decomposed before encoding to SAT. Further details are given elsewhere [48].
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      The X-CSE algorithm for associative commutative CSE
     </section-title>
     <paragraph>
      We described existing approaches to common subexpression elimination for associative and commutative operators in Section 2.6. One of the main contributions of this paper is a new algorithm, which we call X-CSE, to eliminate AC-CSEs. For any AC operator ⋄ (for example, sum, product or disjunction), the goal of X-CSE is to find common sets containing two or more expressions that are contained in more than one ⋄ expression. These are extracted to a new variable, potentially improving constraint reasoning in the solver and reducing the size of the model.
     </paragraph>
     <paragraph>
      The X-CSE algorithm uses a hash table map from pairs of expressions {a mathematical formula}{a,b} to a list of the ⋄ expressions that contain both a and b. Algorithm 2 (populateMapAC) takes a reference to an AST node and explores the tree, populating map for each ⋄ expression. If the ⋄ expression contains two copies of a, map will contain {a mathematical formula}{a,a}.
     </paragraph>
     <paragraph>
      Algorithm 1 (X-CSE) takes a reference to the AST representing all constraints, a reference to the global symbol table, and the AC operator ⋄. After initialising data structures it calls populateMapAC with the entire AST. Following that it enters the main loop on line 4. On line 5 one pair is selected from map according to a heuristic. If the pair occurs in more than one ⋄ expression then there must exist an AC-CS including that pair. Lines 10–20 find an AC-CS and extract it from all the relevant expressions. The algorithm includes as many ⋄ expressions as possible to maximise the effect of extracting the AC-CS. Line 10 intersects all ⋄ expressions containing the pair. A new ⋄ expression for the AC-CS is constructed, and an auxiliary variable is created. On line 14 a constraint is created to define the auxiliary variable. Each ⋄ expression containing the AC-CS is replaced. At this point, lines 19 and 20 update map to include all the newly created expressions, allowing X-CSE to extract further AC-CSs from the new expressions. Some references to removed ⋄ expressions will remain in map; these will be filtered out on line 8.
     </paragraph>
     <paragraph>
      The implementation of X-CSE is optimised by using a second hash table recording the global number of occurrences of every expression directly contained in a ⋄ expression. If an expression {a mathematical formula}e1 occurs only once, then it cannot take part in an AC-CS and no pairs {a mathematical formula}{e1,e2} are stored in map.
     </paragraph>
     <paragraph>
      We apply X-CSE to sums, products, conjunctions and disjunctions in our experiment in Section 5.9 below.
     </paragraph>
     <section label="4.1">
      <section-title>
       Heuristics
      </section-title>
      <paragraph>
       X-CSE chooses the next pair to process by calling a heuristic on line 5. Recall (from Section 2.6) that two AC-CSs in conflict cannot both be extracted from the same expression, therefore a choice is sometimes required. We experimented informally with eight heuristics. There are four basic heuristics: most occurrences (i.e. select the pair that leads to the longest list ls after line 8 of X-CSE), fewest occurrences, largest AC-CS and smallest AC-CS. In some cases there exists a pair such that its corresponding AC-CS can be extracted without preventing any other AC-CS. We call these non-blocking pairs and it may be helpful to process them first. We created four more heuristics that select non-blocking pairs first, then fall back to one of the four basic heuristics. We found no clear winner among the eight heuristics. We use the ‘most occurrences’ heuristic (without prioritising non-blocking pairs) throughout the rest of this paper because it is cheap to compute and often performs well.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Complexity analysis
      </section-title>
      <paragraph>
       In this analysis we will use n for the number of ⋄ expressions, k for the length of the longest ⋄ expression, d as the depth of the deepest ⋄ expression in the AST, and S as the number of nodes in the AST. Central to the complexity analysis is the observation that at most {a mathematical formula}k−1 AC-CSs may be extracted from one ⋄ by X-CSE. The smallest AC-CS is size two, and extracting this replaces a size two term with a size one term (i.e. the replacement auxiliary variable). If the original expression is size k, we thus find one AC-CS and now have a size {a mathematical formula}k−1 expression. Iterating shows that at most {a mathematical formula}k−1 AC-CSs may be extracted from one ⋄ expression by X-CSE. This gives us a global limit of {a mathematical formula}O(nk) AC-CS extractions.
      </paragraph>
      <paragraph>
       To populate map, populateMapAC traverses the AST with S nodes, and for each ⋄ expression e it inserts a reference to e in {a mathematical formula}O(k2) lists within map. Assuming hash table operations are {a mathematical formula}O(1), populateMapAC takes {a mathematical formula}O(S+nk2) time.{sup:1}
      </paragraph>
      <paragraph>
       X-CSE then enters a loop that continues until map is empty. Each iteration of the loop is as follows. We assume the heuristic takes {a mathematical formula}O(1) time.{sup:2} For the given pair, its list ls has at most n elements. Note that if the pair occurs more than once in an expression it might be entered into ls multiple times: to keep the list at size n, when inserting an expression e into ls we can check the last element of ls: if it is equal to e, we do not insert e for a second time. The list ls is filtered in {a mathematical formula}O(nd) time. If the list has length two or greater, then we extract an AC-CS. For the following we assume that an AC expression is represented by a set data structure with {a mathematical formula}O(1) lookup, insertion and removal. Creating commonset on line 10 takes {a mathematical formula}O(nk) time. Computing the domain and creating the auxiliary variable and the new constraint can be done in {a mathematical formula}O(k) time. The algorithm then replaces commonset in each ls expression in {a mathematical formula}O(nk) time. Re-populating map (on lines 19 and 20) takes {a mathematical formula}O(S+nk2) because the updated AC expressions can contain the entire AST. Therefore the entire cost of extracting one AC-CS is {a mathematical formula}O(S+nk2+nd), and the total cost of X-CSE is {a mathematical formula}O(nkS+n2k3+n2kd).
      </paragraph>
      <paragraph>
       While the complexity may seem high, the algorithm scales with the number of AC-CSs it is able to exploit, therefore it is relatively quick when there are few or no AC-CSs, and it takes more time when there is greater potential benefit.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Comparison with related algorithms
      </section-title>
      <paragraph>
       X-CSE differs from the existing algorithms I-CSE(-NC) in that it can extract AC-CSs that are intersections of more than two expressions and AC-CSs containing auxiliary variables (from earlier steps). Thus it has a larger palette of AC-CSs to choose from. Consider the example from Section 2.6: {a mathematical formula}v+w+x+y=0, {a mathematical formula}v+w+x+z=0, {a mathematical formula}v+w+y+z=0. I-CSE(-NC) would have a palette of three AC-CSs: {a mathematical formula}v+w+x, {a mathematical formula}v+w+y and {a mathematical formula}v+w+z. X-CSE would first extract {a mathematical formula}v+w from all three sums:{a mathematical formula} Second, X-CSE would extract any one of {a mathematical formula}a+x, {a mathematical formula}a+y or {a mathematical formula}a+z, as follows. This second step is not possible in I-CSE(-NC).{a mathematical formula} This result is clearly better than I-CSE-NC that extracted only {a mathematical formula}v+w+x and thus did not connect the third constraint to the other two. I-CSE produced nine constraints on this example. I-CSE can drastically increase the size of the instance where X-CSE often makes it more compact. The two are compared experimentally in Section 5.11.
      </paragraph>
      <paragraph>
       On this example, I-CSE misses the AC-CS {a mathematical formula}v+w that connects all three of the original constraints. We propose I-CSE-Iter that iterates I-CSE. I-CSE-Iter first calls I-CSE on the original constraints, then repeatedly calls I-CSE on the AC-CSs extracted by the previous call until no more AC-CSs are found. The second iteration of I-CSE-Iter would find {a mathematical formula}v+w, and indeed it can extract any AC-CS that X-CSE can extract, solving one potential disadvantage of I-CSE. However, iterating I-CSE may further increase the size of the problem instance. We evaluate I-CSE-Iter in Section 5.11.
      </paragraph>
      <paragraph>
       Both rBC2-Y and rBCall-Y (Section 2.6) are able to extract AC-CSs of sums where the coefficients are not identical but in the same proportion in each sum. They are much closer to I-CSE (rBC2-Y) and I-CSE-Iter (rBCall-Y) than to X-CSE because copies of the original expressions are made to allow extraction of conflicting AC-CSs. However rBC2-Y and rBCall-Y simply copy the expressions once for each AC-CS rather than packing the AC-CSs into the minimal number of copies. We do not compare X-CSE with rBC2-Y and rBCall-Y in our experiments, but we have extended X-CSE to capture a common case of proportional coefficients in Section 5.12 below.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Implied constraints for AC-CSE
      </section-title>
      <paragraph>
       A further step to promote the identification of AC-CSs is in reformulating a model to add implied constraints consisting of AC expressions. Savile Row creates implied sum constraints from allDifferent and global cardinality (GCC) constraints. This is done by finding a lower and upper bound on the sum of the variables in the allDifferent or GCC (lb and ub resp.), then adding either {a mathematical formula}∑≥lb and {a mathematical formula}∑≤ub (when {a mathematical formula}lb≠ub) or {a mathematical formula}∑=lb=ub where ∑ is the sum of the variables in scope of the original constraint (except cardinality variables in GCC). The implied constraints are simple examples of finite-domain cuts as investigated by Bergman and Hooker [6].
      </paragraph>
      <paragraph>
       To find the value of ub (lb) for a given allDifferent or GCC constraint, we find an assignment to all the relevant variables such that each variable takes a value from its domain, the sum of the assignment is maximized (minimized), and the number of occurrences of each value is within the interval permitted for the value (for AllDifferent, the interval is {a mathematical formula}{0…1} for every value). The assignment is found using the minimum cost maximum flow formulation described by Régin [57]. If no assignment exists with the required properties then the constraint is replaced with false. For example, given constraint {a mathematical formula}allDifferent(x,y,z) where all variables have domain {a mathematical formula}{1,3,5,7}, Savile Row adds constraints {a mathematical formula}x+y+z≥1+3+5 and {a mathematical formula}x+y+z≤3+5+7.
      </paragraph>
      <paragraph>
       The implied constraints are only added when AC-CSE is switched on. They are added directly before AC-CSE, and any implied constraint that is unchanged by AC-CSE is removed afterwards.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Reformulations in Savile Row
     </section-title>
     <paragraph>
      In this section we describe a range of reformulations, give algorithms to perform them, and evaluate them on a benchmark set. We evaluate each of the reformulations separately. Their inter-dependence raises a problem: we cannot try every subset. We have opted for a cumulative set of experiments, starting with the bare-bones configuration of Savile Row and in each experiment adding one reformulation. If it is successful, it is retained for all the subsequent experiments.
     </paragraph>
     <section label="5.1">
      <section-title>
       Benchmark set
      </section-title>
      <paragraph>
       The benchmark set is the set of example models and parameter files included with Savile Row 1.6.5 (available from http://savilerow.cs.st-andrews.ac.uk/). There are 50 problem classes with 596 instances in total. The set contains a mixture of satisfaction and optimisation problems. Models are described as required in the sections below.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Experimental context
      </section-title>
      <paragraph>
       In our experiments we target the conventional propagation-based CP solver Minion 1.8 (64-bit), with a static variable and value ordering. The static search order means that any reduction in search tree size must be caused by improved propagation, so we directly see the effects of improving constraint formulation. We switch on Minion's option to perform singleton bound consistency (as described in Section 2.2) directly before starting search. We also target the SAT solver Lingeling [34] which was winner of the Sequential, Application SAT+UNSAT track of the SAT competition 2014.{sup:3} We used Savile Row 1.6.5, executed in the OpenJDK Java 1.7.0_141 VM with the 64-bit server VM. Each reported timing is a median of 5 runs when Minion is the target solver, and 10 runs (with 10 distinct random seeds {a mathematical formula}1,…,10) when targeting Lingeling. Minion always performs the same search given the same input but there is some variation in run time caused by the environment. The search performed by Lingeling may be different for two random seeds, so the larger sample of 10 runs is to mitigate the greater variation in the run times. Both solvers and Savile Row are single-threaded. Experiments were performed with 32 processes in parallel on a 32-core AMD Opteron 6272 at 2.1 GHz with 256 GB RAM.
      </paragraph>
      <paragraph>
       The reported timings for Savile Row include time spent running Minion to do domain filtering, and do not include time spent running the target solver (whether it is Minion or Lingeling). In some cases we report timings of the target solver only, and in other cases total time (which is simply Savile Row time plus target solver time). When Minion is the target solver, a time limit of 30 minutes is applied to the total time. With Lingeling a time limit of 1 hour is applied. Lingeling is able to solve many more of the instances than Minion so this allows us to use a longer time limit.
      </paragraph>
      <paragraph>
       There are 13 configurations of Savile Row used in the experiments, summarised in Table 1. The table refers to the reformulations described in Sections 5.4 to 5.12 below.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Statistical analysis
      </section-title>
      <paragraph>
       To compare two configurations A and B of Savile Row, we first take the median of the total time for each instance and each configuration. The total time is the time taken by Savile Row (including any calls to a solver for preprocessing) plus time taken by the backend solver. We chose the median because it is less affected by outliers than the mean. Instances where either configuration timed out are discarded. For the remaining instances, we take the quotient of the two medians ({a mathematical formula}BA). Finally we take the geometric mean of the set of quotients to obtain a single statistic comparing the two configurations. A is considered better than B iff the geometric mean is greater than 1.
      </paragraph>
      <paragraph>
       We chose the geometric mean because it is more appropriate for quotient values than the arithmetic mean, being based on product rather than sum. Suppose one instance was twice as fast with configuration A, and another was twice as fast with B. The two quotients would be 2 and 0.5, and their geometric mean would be 1. The arithmetic mean would be 1.25 which gives the misleading impression that A is faster.
      </paragraph>
      <paragraph>
       If the geometric mean is close to 1, it may not be clear whether there is a significant improvement between the two configurations. To test for a significant improvement using a traditional statistical test, we would need a non-parametric one-tailed test. However, non-parametric tests are inappropriate as they fail to take account of degree of difference. Suppose (when enabling some feature of Savile Row ) 10% of instances are 100 times faster, and the other 90% are 1% slower. Non-parametric tests would be unlikely to reach significance or may even indicate the feature had a negative effect. Instead of using a traditional non-parametric test we compute a confidence interval for the geometric mean by bootstrapping. There are 596 benchmark instances and we take 100,000 bootstrap samples (with replacement) of size 596 from the set of benchmark instances. For each bootstrap sample we compute the geometric mean and take the quantiles at 2.5% and 97.5% to give a 95% confidence interval. If the interval contains 1 then we have not reached the significance threshold. Otherwise, the difference is statistically significant. The location of the interval (above or below 1) indicates which configuration is faster.
      </paragraph>
      <paragraph>
       For example, when comparing X-CSE to IdentCSE (with the CP solver) the geometric mean is 1.492, and the bootstrap confidence interval is [1.326, 1.693]. Fig. 2 plots the distribution of the bootstrap samples. X-CSE has a large benefit for some benchmark instances and makes almost no difference to others. Despite the highly asymmetric and clustered quotient data, the histogram has a smooth (possibly slightly skewed) bell-curve shape. This gives us confidence that 100,000 samples is sufficient.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Experiment one: variable unification and domain filtering
      </section-title>
      <paragraph>
       Variable unification is implemented in several modelling tools as described in Section 2.1. In Savile Row variable unification is implemented as an addition to the simplifier mechanism (Section 3.3). During a simplifier pass, when an expression {a mathematical formula}x=y or {a mathematical formula}x↔y is found in the top level conjunction, one variable is chosen to be removed. Supposing y will be removed, the new domain of x will be the intersection of the two domains and y will be replaced by x throughout. Similarly when an expression {a mathematical formula}x=c or {a mathematical formula}x↔c is found (with constant c) or the domain of x is {a mathematical formula}{c}, x is replaced by c throughout. Also for a Boolean variable x, if x or ¬x appears in the top level conjunction then x is assigned. When variable unification is used, it is applied during all simplifier passes. In each pass, variable unification and simplifiers are applied until a fixed point is reached.
      </paragraph>
      <paragraph>
       Domain filtering is an established preprocessing technique as described in Section 2.2. In Savile Row domain filtering is implemented by tailoring the problem instance for output to Minion and using Minion's standard propagation combined with singleton consistency [7] applied to the upper and lower bounds only (SACBounds). Subsequently the tailoring process is performed a second time, making use of the filtered variable domains. The second tailoring process may target a different solver or class of solvers, but is otherwise identical to the first tailoring process. MiniZinc employs a similar approach with two tailoring processes [39] using the standard propagation of the Gecode solver [28]. The main difference is that we use the more powerful and time-consuming SACBounds.
      </paragraph>
      <paragraph>
       In this paper we consider two versions of domain filtering. The first (standard domain filtering) is to apply domain filtering to variables defined by find statements only. Variables defined by find statements always have the same name in the first and second tailoring process, therefore it is straightforward to apply the filtered domains in the second tailoring process. This is the version used in our previous work [47], [50]. Extended domain filtering (EDF) transfers filtered domains of auxiliary variables that may have different names in the first and second tailoring process. This is done by linking each auxiliary variable to an expression that it represents. The expression acts as a canonical name that remains the same in the first and second tailoring process. MiniZinc implements extended domain filtering using a different canonical name [39]. The EDF algorithm is given in the supplementary material [48] with an experiment that shows no significant improvement over standard domain filtering.
      </paragraph>
      <paragraph>
       Experimental results
      </paragraph>
      <paragraph>
       For brevity we evaluate variable unification and standard domain filtering together in one experiment. Elsewhere we give fuller results with two separate experiments [48]. In Fig. 3 we compare standard domain filtering plus variable unification to the basic configuration with neither option (DomFilt vs Simp). With the CP solver there is an improving trend: for easy instances the overhead of performing the entire tailoring process twice dominates, but for harder instances the benefit can outweigh the cost. The trend is particularly clear for BIBD, Langford and OPD problem classes. Geometric mean speed-up of all instances is 0.962 with confidence interval [0.939, 0.987]. Instances where Simp took 10 seconds or more (total time) have a geometric mean speed-up of 1.176 with confidence interval [1.129, 1.226].
      </paragraph>
      <paragraph>
       When using the SAT solver the effect varies considerably with some instances being solved (i.e. all variables are assigned) by domain filtering (Send More Money, Magic Sequence) and thus exhibiting large speed-ups. Some other instances such as those of Langford and Killer Sudoku are substantially improved. For 572 of 596 instances the SAT encoding has fewer variables and fewer clauses and for another 13 instances the encoding remains the same size. 11 instances exceeded the clause limit and no SAT encoding was produced. In some cases, performance is degraded and the reason is not clear. For example, on two instances of Peg Solitaire the SAT solver is more than two times slower, despite the number of SAT variables being reduced by 40% on average. However, on the full set of 596 instances the improvement is clear: the geometric mean speed-up is 1.329 with confidence interval [1.256, 1.407].
      </paragraph>
      <paragraph>
       In summary, variable unification and standard domain filtering are beneficial on average for harder instances (taking over 10 seconds) or when targeting SAT. Furthermore they enable AC-CSE to substantially improve the formulation of some problem classes (as shown in Section 5.9 below). Hence both reformulations will be switched on for all subsequent experiments.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Experiment two: aggregation
      </section-title>
      <paragraph>
       Section 2.3 surveys the existing work on aggregation. In the current version of Savile Row two types of aggregation are implemented. The first collects ≠, &lt; and allDifferent expressions into a new allDifferent using a greedy maximal clique finding algorithm. A graph is constructed where vertices represent expressions and edges indicate that two expressions must be different. The algorithm builds a clique starting with an arbitrary edge representing a ≠ or &lt; constraint. If the clique has 3 or more vertices then an allDifferent is introduced and all subsumed ≠ constraints are replaced with true in the AST (the graph remains unchanged). The algorithm continues to build cliques starting with ≠ or &lt; constraints (excluding those that have already been included in a new allDifferent) until all such constraints have been considered. Fig. 4 gives an example. The allDifferent constraints introduced by aggregation may contain any numerical expression. Supposing the graph has n vertices and m edges, the greedy clique finding algorithm takes time {a mathematical formula}O(mn2). Our results with aggregation of allDifferent in Savile Row confirm those reported for other systems that have a similar clique finding algorithm [24], [36].
      </paragraph>
      <paragraph>
       The second type of aggregation collects a set of atleast and atmost constraints with identical scopes into a single global cardinality constraint on the same scope, constraining the union of the sets of values of the source constraints.
      </paragraph>
      <paragraph>
       The two types of aggregation are both lightweight, performing only syntactic operations with no iteration over variable domains, so the risk of slowing down tailoring is small and the potential benefit of identifying a global constraint is significant.
      </paragraph>
      <paragraph>
       Experimental results
      </paragraph>
      <paragraph>
       We compare the configurations Aggreg and DomFilt in Fig. 5. With the CP solver the problem classes Golomb Ruler, Graph Colouring and N-Queens 2 are most affected by aggregation (each case being aggregation of not-equal constraints to allDifferent). Aggregation improves performance of the CP solver, with two exceptions in the Graph Colouring class that take less than 1 s to solve. The largest speed-up is 231 times on the Golomb Ruler instance size 10. On Golomb Ruler, aggregation identifies the global allDifferent constraint and as a side effect removes many identical occurrences of difference expressions ruler[j]–ruler[i]. The geometric mean speed-up quotient (of total time) is 1.066 with confidence interval [1.012, 1.133].
      </paragraph>
      <paragraph>
       The picture is different when using the SAT solver. For Graph Colouring (most instances) and Golomb Ruler, aggregation reduces the performance of the SAT solver. This indicates that the encoding of the set of allDifferent constraints can be worse than the encoding of the original set of not-equal constraints. AllDifferent is decomposed into a sum (≤1) constraint for each value, then a generic sum encoding is used as described in Section 3.5. For Golomb Ruler the decomposition re-introduces duplication of the expressions ruler[j]-ruler[i] for all {a mathematical formula}i&lt;j, hence aggregation is complemented by Identical CSE (as shown in the following experiment).
      </paragraph>
      <paragraph>
       For Graph Colouring, aggregation affects four out of five instances, and for all four it makes the SAT encoding larger. The effect on solver efficiency is negative. A single ≠ constraint can be part of more than one maximal clique and hence after aggregation it may be represented in more than one allDifferent constraint. Therefore when using aggregation a single ≠ constraint may be represented multiple times in the SAT encoding, leading to a larger and less efficient encoding.
      </paragraph>
      <paragraph>
       The geometric mean speed-up with the SAT solver is 0.983 with confidence interval [0.964, 0.999]. In summary, aggregation is beneficial for the CP solver and marginal for the SAT solver, and it will be enabled for all subsequent experiments.
      </paragraph>
     </section>
     <section label="5.6">
      <section-title>
       Normalisation for CSE
      </section-title>
      <paragraph>
       A variety of existing CSE techniques are surveyed in Sections 2.4, 2.5 and 2.6. Normalisation [60] may be applied to extend the reach of CSE reformulations.
      </paragraph>
      <paragraph>
       The simplifiers described in Section 3.3 place the AST into a limited normal form. Normalisation extends this normal form by sorting the subexpressions of all expressions where the order is unimportant. For example, {a mathematical formula}x+y+z and {a mathematical formula}y+z+x are semantically equal and normalisation will make them syntactically identical. Apart from associative–commutative operators this affects numerical functions such as min and max, and Boolean functions such as = and allDiff. Normalisation is performed directly before the execution of any CSE algorithm in all the following experiments.
      </paragraph>
     </section>
     <section label="5.7">
      <section-title>
       Experiment three: identical CSE
      </section-title>
      <paragraph>
       The simplest form of CSE that we consider is Identical CSE, which extracts sets of identical expressions. Suppose {a mathematical formula}x×y occurs three times in a model. Identical CSE would introduce a new decision variable a and new constraint {a mathematical formula}x×y=a. The original occurrences of {a mathematical formula}x×y would be replaced by a. In Savile Row, Identical CSE is implemented with Algorithm 3. Andrea Rendl's Tailor [31], [59] and MiniZinc [65], [39] also implement Identical CSE. In contrast to Tailor and MiniZinc, our algorithm is not tied to the process of flattening nested expressions into primitive expressions supported directly by the constraint solver. This is advantageous because it allows us to identify and exploit common subexpressions in expressions that do not need to be flattened.
      </paragraph>
      <paragraph>
       The first step is to recursively traverse the model (by calling Algorithm 4) to collect sets of identical expressions. Algorithm 4 collects only expressions that are candidates for CSE. Atomic variables and constants are not candidates. Compound expressions are CSE candidates by default, with exceptions that depend on the target solver.
      </paragraph>
      <paragraph>
       When the target is a SAT encoding we exclude all compound expressions that can be encoded as a single SAT literal. This avoids creating a redundant SAT variable that is equal to (or the negation of) another SAT variable, thus improving the encoding. The following expressions are not candidates: {a mathematical formula}x=c, {a mathematical formula}x≠c, {a mathematical formula}x≤c, {a mathematical formula}x&lt;c, {a mathematical formula}x≥c, {a mathematical formula}x&gt;c, ¬x (where x is a decision variable and c is a constant). When the target is Minion, ¬x is not a candidate because negation is natively supported. Unary constraints {a mathematical formula}x=c, {a mathematical formula}x≠c, {a mathematical formula}x≤c, {a mathematical formula}x&lt;c, {a mathematical formula}x≥c, {a mathematical formula}x&gt;c, {a mathematical formula}x∈{c1,c2,…} (where x is a decision variable and {a mathematical formula}c,c1,c2 are constants) are not candidates when they are contained in a conjunction or disjunction. When a unary constraint is propagated it is entirely represented in the domain so extracting unary constraints by CSE will not strengthen propagation. However, when a set of identical unary constraints must be extracted by general flattening (Section 3.4), Identical CSE will reduce the number of auxiliary variables and constraints. Minion natively supports conjunction and disjunction of any constraint [35] so there is no benefit from extracting unary constraints from conjunctions or disjunctions.
      </paragraph>
      <paragraph>
       The second step of Identical CSE is to iterate through sets of expressions in decreasing size order (line 4). When an expression e is eliminated by CSE, the number of occurrences of any expressions contained in e is reduced. Therefore eliminating long expressions first may obviate the need to eliminate short expressions. For each set (of size greater than one) of identical expressions a new decision variable aux is created, and each of the expressions is replaced with aux. One of the expressions e in the set is used to create a new constraint {a mathematical formula}e=aux. Crucially the new constraint contains the original object e so it is possible to extract further CSEs from within e.
      </paragraph>
      <paragraph>
       The domain(e) function (line 9) obtains a finite domain for the new auxiliary variable. When extended domain filtering is off, domain(e) returns {a mathematical formula}{⌊e⌋…⌈e⌉}, otherwise it returns the filtered domain as described in Section 5.4. Finally, if an expression appears in the top-level conjunction, any other occurrences of it are replaced with true.
      </paragraph>
      <paragraph>
       Identical CSE is a relatively straightforward optimisation and is implemented in a number of tools including MiniZinc [65] and IBM CP Optimizer Presolve [36].
      </paragraph>
      <paragraph>
       Experimental results
      </paragraph>
      <paragraph>
       Our experiments confirm that Identical CSE is beneficial for a number of problem classes. Fig. 6 plots our results comparing IdentCSE to Aggreg. When using the CP solver, Nurse Rostering exhibits the largest speed up with Identical CSE. There are identical sums shared between two groups of constraints, and extracting these strengthens propagation. For all other problem instances Identical CSE did not change the search tree. Excluding Nurse Rostering, the largest speed up is 3.13 for the Knights Tour size 7 instance, where expressions such as |tour[1]/7 - tour[2]/7| occur twice, and tour[1]/7 occurs four times initially (twice after the containing expressions are extracted). Extracting these two types of common subexpression simply speeds up propagation. Peg Solitaire Table has no identical common subexpressions, however Identical CSE causes a substantial overhead on this class with Aggreg being (at most) 3.19 times faster than IdentCSE.{sup:4}
      </paragraph>
      <paragraph>
       With the SAT backend, Identical CSE is particularly helpful for Car Sequencing, EFPA and Golomb Ruler. In Car Sequencing the identical expressions are {a mathematical formula}x∈S for some variable x and integer set S that are contained in sums. For EFPA the decomposition of lexicographic ordering constraints (described in Section 3.5) is improved by Identical CSE and is also cross-connected with constraints requiring d differences between rows of the matrix. Golomb Ruler has identical common subexpressions within the decomposition of allDifferent, as described in the section above.
      </paragraph>
      <paragraph>
       For the CP solver the geometric mean speed-up is 1.035 with confidence interval [0.988, 1.097]. The result is likely to be positive but does not quite reach the significance threshold. For the SAT solver the same statistic is 1.238 with confidence interval [1.190, 1.291]. Identical CSE will be switched on for all subsequent experiments.
      </paragraph>
     </section>
     <section label="5.8">
      <section-title>
       Experiment four: active CSE
      </section-title>
      <paragraph>
       Active CSE extends Identical CSE by allowing non-identical expressions to be extracted using a single auxiliary variable. We reviewed the related work in Section 2.5. As an example, suppose we have {a mathematical formula}x=y and {a mathematical formula}x≠y in the model. We can introduce a single Boolean variable a and a new constraint {a mathematical formula}a↔(x=y), then replace {a mathematical formula}x=y with a and {a mathematical formula}x≠y with ¬a. For solvers that natively support negation (such as SAT solvers) ¬a can be expressed in the solver input language with no further rewriting, so we have avoided expressing both {a mathematical formula}x=y and {a mathematical formula}x≠y in the solver input language.
      </paragraph>
      <paragraph>
       The Active CSE algorithm in Savile Row extends Algorithm 3. For each candidate expression e a simple transformation is applied to it (for example producing ¬e). Simplifiers and normalisation are applied to place ¬e in the normal form. The algorithm then queries map to discover expressions matching the transformed expression.
      </paragraph>
      <paragraph>
       Active CSE in Savile Row 1.6.5 applies four transformations: Boolean negation, arithmetic negation, multiply by 2, and multiply by −2. For example, {a mathematical formula}x−y+z matches {a mathematical formula}y−x−z using arithmetic negation. Rendl implemented Boolean negation active CSE in Tailor, along with active reformulations based upon De Morgan's laws and Horn clauses [59]. In Savile Row, the use of negation normal form obviates the use of the latter two. To our knowledge MiniZinc [65], [39] does not implement Active CSE.
      </paragraph>
      <paragraph>
       Experimental results
      </paragraph>
      <paragraph>
       Fig. 7 plots our results comparing ActiveCSE to IdentCSE. With the CP solver Active CSE makes very little difference on any problem class. In most cases the search tree is unchanged, and the largest reduction in search nodes is 0.9%. When using the SAT solver, the instances that are affected by Active CSE are scattered, with some (in each affected class) improved and others degraded. The geometric mean speed-up quotient of total time is 0.936 when using the CP solver, with confidence interval [0.924, 0.949], and 0.976 when using the SAT solver with confidence interval [0.966, 0.985]. Active CSE will not be enabled for any subsequent experiment.
      </paragraph>
     </section>
     <section label="5.9">
      <section-title>
       Experiment five: evaluation of X-CSE
      </section-title>
      <paragraph>
       We introduced the algorithm X-CSE in Section 4. In this experiment we look in detail at six problem classes where AC-CSs arise. We apply X-CSE to disjunction, conjunction, sum and product. These types are represented as a single AST node with n children in Savile Row. Two other AC types appear in our benchmarks: min and max (in one problem class each) and they exhibit no AC-CSs. X-CSE scales with the number of AC-CSs, so the cost of applying X-CSE to min and max would be minimal.
      </paragraph>
      <section label="5.9.1">
       <section-title>
        Case study 1: BIBD
       </section-title>
       <paragraph>
        The BIBD problem is described in high-level terms as our motivating example (Section 1.2). We use Meseguer and Torras' first model of BIBD [43], extended with {a mathematical formula}Lex2 symmetry breaking constraints [19]. BIBD is parameterised by {a mathematical formula}(v,k,λ) and has constants {a mathematical formula}r=λ(v−1)k−1 and {a mathematical formula}b=λv(v−1)k(k−1). The model has a v by b matrix m of Boolean variables. Each of the v rows sums to r (row constraints), and each of the b columns sums to k (column constraints). The scalar product of each pair of rows has value λ:{a mathematical formula} Rows and columns are ordered lexicographically to remove some symmetry:{a mathematical formula} This model initially has no CSs of any type (identical, active or AC). Domain filtering (Section 5.4) assigns some of the variables (as seen in Fig. 1). As discussed in Section 1.2, the scalar product constraints are then simplified causing AC-CSs to appear among scalar product constraints, and between scalar product and row sum constraints.
       </paragraph>
       <paragraph>
        We evaluated X-CSE on the 24 instances in Fig. 1 of Puget [55] and also with {a mathematical formula}(v,k,λ)=(7,3,20) and {a mathematical formula}(8,4,12). When using the CP solver, we found that 3 instances time out with IdentCSE and 2 of those also time out with X-CSE. For the remaining 23 instances where neither time out, X-CSE always decreases the node count. Fig. 8 (upper left) plots the reduction factor for the 23 instances. Harder instances tend to show a greater reduction in node count.
       </paragraph>
       <paragraph>
        Fig. 8 (upper right) plots speed-up of total time with X-CSE. For the easiest instances, the reduction in node count does not cause a measurable difference in the run time of the constraint solver. The slight increase in total time is caused by the up-front cost of X-CSE. On the harder instances, Minion search takes up most of the total time and X-CSE speeds up search substantially by reducing the number of search nodes. Fig. 8 (upper right) peaks with instance {a mathematical formula}(12,3,4), which has a 78-fold reduction in nodes and speed up of 43.2 times. The time taken by Savile Row increased from 1.7 s to 2.6 s. X-CSE typically increases the number of constraints and auxiliary variables, reducing the node rate of the CP solver. With the SAT solver we found that the same 2 instances timed out with both IdentCSE and X-CSE. For the other 24, X-CSE reduces the median search nodes for 22 instances and increases 2, as shown in Fig. 8 (lower left). The reduction in search nodes is much less dramatic than with the CP solver. Fig. 8 (lower right) plots speed-up of total time caused by X-CSE with the SAT solver. The peak speed-up quotient is 4.14 for instance {a mathematical formula}(8,4,12), and the median search nodes is reduced by 7.47 times.
       </paragraph>
      </section>
      <section label="5.9.2">
       <section-title>
        Implied constraints for BIBD
       </section-title>
       <paragraph>
        Frisch, Jefferson, and Miguel [23] derived a set of implied constraints for BIBD that drastically improve the performance of the model. First they observed that the first two rows and first column of the BIBD can be assigned by manually reasoning about the constraints. Second, for each of the remaining rows i, the row sum constraint is split into two parts: all indices where row 1 is 0 sum to {a mathematical formula}r−λ, and all other indices sum to λ (by combining the row sum to r with the scalar product constraint between rows 1 and i). The process is repeated with rows 2 and i, giving four constraints. These implied constraints are derived using an approach resembling manual AC-CSE.
       </paragraph>
       <paragraph>
        The automated approach improves on Frisch et al. in two ways. First, domain filtering assigns not just the first two rows and first column but also parts of other rows and columns (see Fig. 1 for example). Second, X-CSE is able to link multiple scalar product constraints and a row constraint, whereas the implied constraints are each derived from one scalar product and one row constraint.
       </paragraph>
       <paragraph>
        The implied constraints alone reduce node count with the CP solver (see Fig. 8 (upper left)) and for most instances with the SAT solver (lower left), but are not as effective as X-CSE. For most of the harder instances the implied constraints speed up solving but by a smaller degree than X-CSE. Adding the implied constraints then applying X-CSE is slightly more effective than X-CSE alone in reducing node count for the CP solver. However this does not translate to a clear improvement in search efficiency. Remarkably, X-CSE is able to improve the sophisticated model on most instances for both solvers.
       </paragraph>
      </section>
      <section label="5.9.3">
       <section-title>
        Case study 2: optimal portfolio design
       </section-title>
       <paragraph>
        The Optimal Portfolio Design problem [20] (Problem 65 at www.csplib.org) is a challenging problem from computational finance. Following the description given in [20], A Collateralised Debt Obligation (CDO) is a portfolio of credit assets, such as bonds, loans, or credit default swaps. In order to manage risk, CDOs are divided into uniformly sized tranches each consisting of a subset of the underlying collection of credit assets. The task is to choose the constituents of the tranches so that each pair of tranches overlap as little as possible, in order to spread the risk.
       </paragraph>
       <paragraph>
        The OPD problem can be seen as a more challenging optimisation variant of the BIBD problem, in which we are required to find v tranches each composed of a cardinality r subset of b credit assets, while minimising λ, the cardinality of the maximum intersection between any pair of tranches.
       </paragraph>
       <paragraph>
        We evaluated X-CSE on a set of 101 OPD instances composed as follows: All 54 instances from Flener et al. [20]; a further 18 instances from CSPLib; and finally 29 further instances from the above BIBD experiments. The results are plotted in Fig. 9. Similarly to the BIBD results, when using the CP solver X-CSE produces a decrease in node count on all but one instance, and this reduction is more pronounced for the harder instances. In terms of total time, for the easiest instances there is again a small increase caused by the up-front cost of X-CSE, but on the harder instances where search is the dominant cost X-CSE speeds up the search substantially. Overall, for CP the average speed-up is 1.288 with confidence interval [1.107, 1.527]. When using the SAT solver, the average speed up is 1.217 with confidence interval [1.059, 1.428].
       </paragraph>
       <paragraph>
        Although the structure of the OPD problem differs somewhat from that of the BIBD problem, in particular in that there is no sum on the columns of the design matrix, by a similar process to that described for BIBD, Savile Row is able to fix the first row of the OPD matrix and therefore identify sub expressions that X-CSE can exploit.
       </paragraph>
      </section>
      <section label="5.9.4">
       <section-title>
        Case study 3: the SONET problem
       </section-title>
       <paragraph>
        The SONET problem [64] is a network design problem where each node is connected to a set of rings (fibre-optic connections). The simplified SONET problem (Section 3 of [64]) has the following parameters: the number of nodes n, the upper limit on the number of rings m, the maximum number of nodes per ring r, and a set of pairs that must be connected. For each of these pairs there must exist a ring connected to both nodes. The number of node-ring connections is minimised.
       </paragraph>
       <paragraph>
        The problem is modelled as follows. We have a Boolean matrix rings indexed by {a mathematical formula}[1…m,1…n]. {a mathematical formula}rings[a,b] indicates whether ring a is connected to node b. For each ring a we have the sum constraint {a mathematical formula}∑b=1nrings[a,b]≤r. The connectedness constraint between two nodes {a mathematical formula}b1 and {a mathematical formula}b2 is expressed as a disjunction of sums:{a mathematical formula} The minimisation function is the sum of rings. Rings are indistinguishable so we use lexicographic ordering constraints to order the rows of rings. The static variable ordering we use is the reading order of rings and value order is 0 then 1. This model is very simple and does not include implied or dominance constraints [64]. The constraints are already flat and only the minimisation sum needs to be flattened, thus only one auxiliary variable is created by Savile Row without X-CSE. There are AC-CSs among the connectedness constraints, the ring sum constraints and the minimisation sum.
       </paragraph>
       <paragraph>
        We generated 24 instances with {a mathematical formula}n∈{6…13}, {a mathematical formula}r∈{3,4,5}, and {a mathematical formula}m=10. The demand graph when {a mathematical formula}n=13 is Fig. 1 of Smith [64]. For smaller n we take the subgraph with vertices {a mathematical formula}{(n+1)…13}, and edges adjacent to these vertices, removed. Fig. 10 (left) plots the speed-up factor for X-CSE when using the CP solver. For IdentCSE with the CP solver, all instances with {a mathematical formula}n≥10, also {a mathematical formula}n=9,r=4 and {a mathematical formula}n=9,r=3 time out. X-CSE is able to solve to optimality one additional instance {a mathematical formula}n=10,r=5, which solved just within the time limit and appears on the right edge of the plot with a speed-up of 1.23. X-CSE improves solving speed for all but the most trivial instances, with a peak speed-up of 7.17. When using the SAT solver as shown in Fig. 10 (right), IdentCSE solves all but two instances of SONET to optimality, and all instances are solved to optimality with X-CSE. The two instances that are not solved with IdentCSE appear on the far right of the plot. Instance {a mathematical formula}n=13,r=5 exhibits the largest speed-up of 10.7 times, and it is one of the two that timed out with IdentCSE.
       </paragraph>
      </section>
      <section label="5.9.5">
       <section-title>
        Case study 4: Molnar's problem
       </section-title>
       <paragraph>
        Molnar's problem [22] (CSPLib problem 035 [21]) is to find a square matrix M of integers. The model has two parameters: the size k (i.e. M has size {a mathematical formula}k×k) and the maximum absolute value of integers in M, named d. The initial domain of each element of M is {a mathematical formula}{−d…−2}∪{0}∪{2…d}. The first constraint is that the determinant of M is 1 or −1 (following the model of Frisch et al. [22]). For the second constraint we construct another matrix S where each entry of S is the square of the corresponding entry of M. The determinant of S must also be 1 or −1. We used the Leibniz formula for determinants, and expressed {a mathematical formula}a2 as {a mathematical formula}a×a to allow more AC-CSs of products. When {a mathematical formula}k=3 we have the following two matrices and two constraints. In addition we break symmetry on M by lexicographically ordering rows and columns.{a mathematical formula}
       </paragraph>
       <paragraph>
        There are multiple AC-CSs of products, for example aa and aei. Some connect the two sums, and others connect terms within one sum. X-CSE is able to extract a particular AC-CS from the same product more than once on this problem. Consider aei: extracting it once creates a new constraint {a mathematical formula}aei=x and modifies the existing expression aei to x, and the expression {a mathematical formula}aaeeii to {a mathematical formula}x×aei. Now X-CSE extracts aei a second time from the new constraint and one of the modified expressions, creating a second auxiliary variable (that will later be unified with x).
       </paragraph>
       <paragraph>
        Fig. 10 (left) plots the speed-up quotient with the CP solver for Molnar's Problem on the twelve instances where {a mathematical formula}k∈{2…4} and {a mathematical formula}d∈{2…5}. X-CSE is more useful for the more difficult instances. Instances where {a mathematical formula}k=4 and {a mathematical formula}d≥3 time out with both IdentCSE and X-CSE. The peak speed-up quotient is 5.73. Fig. 10 (right) plots the speed-up quotient with the SAT solver. Both IdentCSE and X-CSE time out when {a mathematical formula}k=4 and when {a mathematical formula}k=3 and {a mathematical formula}d≥4. The peak speed-up quotient is 8.79.
       </paragraph>
      </section>
      <section label="5.9.6">
       <section-title>
        Case study 5: Killer Sudoku
       </section-title>
       <paragraph>
        The standard Killer Sudoku [45] has a {a mathematical formula}9×9 grid where each row and column are allDifferent, and the nine non-overlapping {a mathematical formula}3×3 subsquares are also allDifferent. Each slot in the grid is initially empty and takes a digit {a mathematical formula}1…9. Clues are sets of squares that sum to a given value (and are also allDifferent). We found {a mathematical formula}9×9 Killer Sudoku instances to be very easy, so we used a {a mathematical formula}16×16 grid with 16 {a mathematical formula}4×4 subsquares, and each slot takes a number {a mathematical formula}1…16. We generated 100 instances by first creating 100 random assignments to the {a mathematical formula}16×16 grid. These assignments satisfy the row, column and subsquare allDifferent constraints. Second, for each random assignment we generated clues of lengths 1 to 5 using random walks from random starting points. (For brevity we omit full details of instance generation: Instances are included with Savile Row 1.6.5.) Traditional Killer Sudoku puzzles have exactly one solution. The random {a mathematical formula}16×16 instances may be unsatisfiable and may have multiple solutions.
       </paragraph>
       <paragraph>
        AC-CSE alone does nothing because the sums in the clues are the only AC expressions and they do not overlap. However the sums overlap with allDifferent constraints. Each allDifferent constraint on a row, column or subsquare represents a permutation of {a mathematical formula}{1…16} which sum to 136. Savile Row automatically adds implied sum constraints as described in Section 4.4. In the first tailoring process the implied sums will be {a mathematical formula}∑X=136 where X is the set of variables in the row, column or subsquare. In the second tailoring process some variables may be assigned and deleted, with the assigned value removed from other variables in the same row, column or subsquare. The implied sums for rows, columns and subsquares will be of the form {a mathematical formula}∑X=c but the constant c may differ. X-CSE then finds AC-CSs among rows, columns, subsquares and clues.
       </paragraph>
       <paragraph>
        Fig. 11 (left) plots the speed-up quotient for Killer Sudoku when using the CP solver. Without X-CSE, 44 instances timed out. With X-CSE, 24 instances timed out. As the instances become more difficult, the trend is towards greater speed-up by X-CSE. The plot peaks at 1671 times faster. On this instance, with the IdentCSE configuration Savile Row took 1.15 s and Minion timed out after exploring 9,188,782 nodes. With X-CSE, Savile Row took 0.95 s and Minion took 0.13 s to explore 4 nodes. The geometric mean speed-up quotient of total time is 9.72 over 100 instances.
       </paragraph>
       <paragraph>
        When using the SAT solver the results are still very positive, but not as striking. Fig. 11 (right) shows that X-CSE improves most instances but degrades performance on others. The geometric mean speed-up quotient of total time is 2.119 with confidence interval [1.720, 2.625]. IdentCSE times out for three instances and X-CSE is able to solve two more. There are two main groups of instances, one where X-CSE enables domain filtering to solve or almost solve the instances (making the SAT encoding very small), and another where X-CSE is (for the most part) increasing the size of the SAT encoding. In 91 of 100 instances, if the SAT encoding has more variables then the total time is greater.
       </paragraph>
      </section>
      <section label="5.9.7">
       <section-title>
        Case study 6: car sequencing
       </section-title>
       <paragraph>
        The Car Sequencing problem [51] (CSPLib problem 1) serves as a prototypical example of a sequencing problem, of which many other examples exist, and shows how common subexpressions can arise and be exploited. The problem is an abstracted factory scheduling problem, and is NP-hard on its own [18]. The goal is to manufacture cars on an assembly line. The cars are not identical: there are a set of options that may be included (for example, air conditioning). Each option is fitted to the cars at a station on the assembly line, and each station s has a capacity constraint: it can take at most {a mathematical formula}ps of every {a mathematical formula}qs consecutive cars, where {a mathematical formula}ps and {a mathematical formula}qs are given. For each class of (identical) cars, the number of that class to be manufactured is given along with the set of options required by that class.
       </paragraph>
       <paragraph>
        We represent each car class with an integer and the sequence of cars as a sequence of integer variables seq. A global cardinality constraint [56] ensures the required number of each class is manufactured. The station capacity constraints are expressed as sums {a mathematical formula}≤ps of expressions {a mathematical formula}(seq[i]∈Sopt) where {a mathematical formula}Sopt is the set of car classes that require opt. Finally an implied constraint is added for each option that states the option is fitted the required number of times over the whole sequence. These constraints are also sums of {a mathematical formula}(seq[i]∈Sopt) expressions. The model is much simpler than others in the literature [58], [33], [11], [46] and as it stands it will not propagate well in a conventional CP solver. The search branches on seq in order and assigns values in ascending order.
       </paragraph>
       <paragraph>
        The expressions {a mathematical formula}x∈Sopt are extracted by Identical CSE leaving sums of Boolean variables. For each option, the station capacity constraints overlap with each other and also with the implied constraint for the option. X-CSE connects together all the constraints related to a single option, but is not able to exploit every AC-CS since some pairs conflict. Fig. 12 shows a conflicting pair of AC-CSs on a small example.
       </paragraph>
       <paragraph>
        Fig. 13 plots our results with the CP solver and the SAT solver. The SAT solver is more successful in solving these instances both with IdentCSE and X-CSE. For both solvers X-CSE improves the model considerably with peak speed-up quotients of over 100 times on the most difficult instances solvable within the time limit.
       </paragraph>
       <paragraph>
        It is likely that an aggregation approach (producing a set of global sequence constraints [58] or a pre-defined encoding [33], [11]) would perform better than X-CSE on this problem class, however aggregation would also be less general than X-CSE.
       </paragraph>
       <paragraph>
        Finally, applying X-CSE generates part of the Partial Sums encoding of sequence by Brand et al. [11]. Partial Sums introduces a variable for each contiguous subsequence of length 2 to {a mathematical formula}qs (for a station s), which is a superset of the variables X-CSE introduces. Enforcing bound consistency on Partial Sums guarantees GAC on the sequence constraint, whereas X-CSE has no similar guarantee.
       </paragraph>
       <paragraph>
        While we have experimented only on car sequencing, we expect the pattern of overlapping sums seen in Fig. 12 to arise in other sequencing problems, and therefore for AC-CSE to be widely applicable in sequencing problems.
       </paragraph>
      </section>
      <section label="5.9.8">
       <section-title>
        Summary plots for X-CSE
       </section-title>
       <paragraph>
        Fig. 14 compares X-CSE to IdentCSE for all problem classes. The geometric mean speed-up is 1.492 when using the CP solver with confidence interval [1.326, 1.693], and 1.323 when using the SAT solver with confidence interval [1.236, 1.422]. There are two notable problem classes (other than the case studies above): Peg Solitaire Action (with both solvers), and Graph Colouring (with the SAT solver only). Applying X-CSE to Peg Solitaire Action adds a considerable overhead to Savile Row (owing to a large number of long conjunctions nested within constraints) and when targeting the CP solver does not change the search tree. For SAT, more variables are generated, the number of search decisions is increased and Lingeling takes longer.
       </paragraph>
       <paragraph>
        In Graph Colouring with the SAT solver, the two instances that exhibit a very large speed-up are unsatisfiable because of a limit on the number of colours. In both instances, some of the cliques of disequalities are larger than the number of colours. The cliques are collected to an AllDifferent with more variables than domain values. In this case the pass that generates implied sums from AllDifferent creates a false constraint so the SAT encoding becomes trivial.
       </paragraph>
      </section>
     </section>
     <section label="5.10">
      <section-title>
       Interaction of X-CSE with other reformulations
      </section-title>
      <paragraph>
       We have shown that X-CSE is a valuable addition to the set of reformulations we have accumulated so far: Identical CSE, aggregation, standard domain filtering, and variable unification. However, the interaction of X-CSE with the other reformulations is not clear. Here we compare X-CSE alone (referred to as X-CSE-Alone) to X-CSE with all the other reformulations accumulated so far (named simply X-CSE in Table 1).
      </paragraph>
      <paragraph>
       Fig. 15 plots X-CSE against X-CSE-Alone. With the CP solver many problem classes perform better with X-CSE than X-CSE-Alone. BIBD and OPD both have no AC-CSs in the initial model but domain filtering, variable unification and simplifiers create a set of AC-CSs that are then extracted by the X-CSE algorithm. For both Golomb Ruler and Graph Colouring aggregation is essential. In common with experiment one (Section 5.4) there are many easy instances that are solved in less than 10 seconds with X-CSE-Alone, and for most of these instances the overhead of the full set of reformulations is not repaid. The geometric mean speed-up of the full set of instances is 1.060 with confidence interval [0.990, 1.142]. If we exclude instances where X-CSE-Alone takes less than 10 seconds total time, the geometric mean speed-up is 1.795 with confidence interval [1.476, 2.232].
      </paragraph>
      <paragraph>
       With the SAT solver X-CSE is clearly better than X-CSE-Alone with a geometric mean speed-up of 1.853 with confidence interval [1.708, 2.014]. If we compare IdentCSE (i.e. Identical CSE, aggregation, standard domain filtering and variable unification) to Simp the geometric mean speed-up is 1.626 with confidence interval [1.531, 1.730]. The difference in average speed-up indicates that there must be a significant interaction between X-CSE and the four other reformulations. If we examine individual problem classes the results are spread. For example OPD instances are all changed in a similar way by X-CSE (compared to X-CSE-Alone), and most are improved by X-CSE but there are some difficult OPDs where X-CSE-Alone is faster.
      </paragraph>
     </section>
     <section label="5.11">
      <section-title>
       Experiment six: I-CSE, I-CSE-NC and I-CSE-Iter
      </section-title>
      <paragraph>
       We now compare X-CSE to the alternative AC-CSE algorithm I-CSE and its variants (described in Sections 2.6 and 4.3). In each of the I-CSE configurations, the I-CSE algorithm is applied to sums and products (as in the original paper by Araya et al. [2]) and the X-CSE algorithm is applied to conjunctions and disjunctions. Therefore when comparing I-CSE with X-CSE, we are comparing their performance on sums and products only, while treating conjunctions and disjunctions identically.
      </paragraph>
      <paragraph>
       Experimental results
      </paragraph>
      <paragraph>
       Fig. 16 plots the speed-up factor for I-CSE compared to X-CSE. With the CP solver, I-CSE performs better on a very small number of instances, notably four instances of Car Sequencing that can be solved with I-CSE and not with X-CSE. These four instances exhibit a speed-up of 155 to 169 times. As discussed in Section 5.9.7, Car Sequencing has a large number of conflicting pairs of AC-CSs that I-CSE can exploit. Two Killer Sudoku instances time out with I-CSE and are solved with X-CSE. X-CSE can exploit AC-CSs among a subsquare, a row or column, and a clue that are not available to I-CSE because I-CSE considers expressions pairwise. Overall X-CSE is preferable for SONET, Killer Sudoku, and BIBD. When using the SAT solver, broadly the same problem classes are improved or deteriorated when comparing I-CSE to X-CSE.
      </paragraph>
      <paragraph>
       When using the CP solver the geometric mean speed-up is 0.737 (confidence interval [0.689, 0.786]) and it is 0.797 (confidence interval [0.758, 0.837]) when using the SAT solver. With the CP solver both algorithms time out on 174 instances, albeit different sets of 174 instances. With the SAT solver I-CSE times out for 68 instances, and X-CSE times out for 67. Overall it seems that X-CSE strikes a better balance between increasing the size of the constraint set and strengthening propagation.
      </paragraph>
      <paragraph>
       In previous work [47] we found that I-CSE often performed better than X-CSE on Killer Sudoku, whereas here only a small number of Killer Sudoku instances are improved by I-CSE compared to X-CSE. The context here is different in a number of ways. For example, we have added aggregation that can lead to additional implied sum constraints on this problem class.
      </paragraph>
      <paragraph>
       I-CSE-NC is a lighter weight version of I-CSE that does not copy expressions, so it cannot exploit both of a conflicting pair of AC-CSs. On average it is somewhat worse than I-CSE, as discussed in [48, Section D]. I-CSE-Iter extends I-CSE by iterating until a fixpoint is reached. On average it very slightly improves the performance of the CP solver and very slightly degrades the SAT solver when compared to I-CSE. Full results are given elsewhere [48, Section D].
      </paragraph>
     </section>
     <section label="5.12">
      <section-title>
       Experiment seven: active associative–commutative CSE
      </section-title>
      <paragraph>
       Standard AC-CSE requires the extracted subexpressions to be syntactically identical apart from reordering. Normalisation helps by reducing semantic identity to syntactic identity in some cases, but we can extend the reach of AC-CSE further by considering simple transformations as in Active CSE. If we consider some transformation t (for example, multiplying by two then restoring the normal form), an Active AC-CS e is a subexpression that is contained in one set of AC expressions as-is, and the transformed version {a mathematical formula}t(e) is contained in another set of AC expressions. Where e occurs, it is replaced with a new auxiliary variable a, and {a mathematical formula}t(e) is replaced with {a mathematical formula}t(a).
      </paragraph>
      <paragraph>
       An example is found in the reservoir management problem described by Choi and Lee [14]. Their first model has differences {a mathematical formula}xi−yi in one set of sums and {a mathematical formula}yi−xi in another, where i is the day from a period of several months. This is improved by introducing a new set of variables for the differences {a mathematical formula}xi−yi. Their improvement, made manually, is equivalent to Active AC-CSE with an arithmetic negation transformation.
      </paragraph>
      <paragraph>
       A transformation t used in Active AC-CSE may change the type of the AC expression (i.e. e and {a mathematical formula}t(e) are different types). For example, consider a transformation {a mathematical formula}t(e) that takes the Boolean negation of e then restores the normal form. If e is a disjunction, {a mathematical formula}t(e) will be a conjunction and vice versa, so an algorithm that implements Active AC-CSE for this transformation must track both conjunctions and disjunctions.
      </paragraph>
      <paragraph>
       In this paper we investigate one case of Active AC-CSE and propose an algorithm that is an extension of X-CSE. The case we consider is arithmetic negation of sums. The transformation takes a sum {a mathematical formula}c1e1+⋯+cnen (where {a mathematical formula}ci are integers and {a mathematical formula}ei may be any expression) and simply negates each one of the coefficients {a mathematical formula}ci. This captures one case where the coefficients are proportional (as in rBC2-Y and rBCall-Y [9]).
      </paragraph>
      <paragraph>
       The Active AC-CSE algorithm (named Active X-CSE) is an extension of Algorithm 1. The first step, populating map, remains unchanged. The heuristic (called on line 5) is adapted to select a pair where the pair and its negation together have the most occurrences. Once a pair has been selected, the lists for the pair and its negation are retrieved from map and the two lists are filtered (as on line 8). If the total length of the two lists is greater than one, then an (active or standard) AC-CS is extracted. The process is similar to lines 10–20 of Algorithm 1. The largest possible common set is extracted from the expressions in the two lists and replaced in each case with a reference to a new auxiliary variable aux or −aux.
      </paragraph>
      <paragraph>
       Finally, the algorithm is optimised (similarly to X-CSE) by using a second hash table recording the global number of occurrences of every expression contained in a sum. If an expression {a mathematical formula}e1 occurs only once, then it cannot take part in an AC-CS and no pairs {a mathematical formula}{e1,e2} are stored in map. However (unlike X-CSE) the coefficient is not included as part of the expression when counting occurrences.
      </paragraph>
      <paragraph>
       In this experiment we apply Active X-CSE to sums and X-CSE to conjunctions, disjunctions and products. In all other respects the Active X-CSE configuration is identical to the X-CSE configuration. We found that the benchmark set does contain some Active AC-CSs, however there were no substantial improvements to solving performance. Full results are given elsewhere [48, Section E].
      </paragraph>
     </section>
     <section label="5.13">
      <section-title>
       Experimental conclusions
      </section-title>
      <paragraph>
       In the experiments above we have recommended the following set of reformulations: variable unification, standard domain filtering, aggregation, Identical CSE and X-CSE. To gauge how effective this set of recommended reformulations are, Fig. 17 compares using all of them to Savile Row with simplifiers only. Considering only time taken by the solvers, both CP and SAT models are massively improved: the geometric mean speedup is 3.627 for the CP solver and 6.614 for SAT. This is achieved entirely automatically, where the comparison is not with a straw man but a model written by hand and tailored by Savile Row in baseline form. The overhead of extra reformulation reduces the overall speedup. For CP, the geometric mean speed-up of total time is 1.568 with confidence interval [1.359, 1.823] and 32 more instances solved. For SAT it is 2.147 with confidence interval [1.973, 2.340] and 16 more instances solved. For the CP solver there is a general trend that harder instances benefit more from reformulation, and for some problem classes the gains can be hundreds or thousands of times. For instances that Simp solves in more than 10 seconds, the geometric mean speedup of total time is 5.959. We conclude that the recommended reformulations are well worthwhile, especially on harder instances where solver time dominates.
      </paragraph>
      <paragraph>
       The largest gains we have seen have come from AC-CSE, across a diverse range of problem classes including a factory planning problem, a puzzle, combinatorial designs, and a network design problem. For the most part both the CP and SAT solvers have benefited from AC-CSE, implemented with the X-CSE algorithm (including the generation of implied sum constraints from global constraints). Depending on the problem class, the peak speed-up may be tens, hundreds or even thousands of times. In most cases AC-CSE is improving the formulation of overlapping sum constraints.
      </paragraph>
      <paragraph>
       Identical CSE is also beneficial over a wide range of problem classes, particularly with the SAT solver where it avoids the overhead of multiple encodings of the same expression. Aggregation is also important when it applies, and very low-cost when it does not. Other reformulations have proven to be important preparatory steps that complement CSE (particularly AC-CSE): variable unification, domain filtering and applying simplifiers all have a role in revealing common subexpressions. Alone, variable unification and domain filtering provide a small benefit.
      </paragraph>
      <paragraph>
       Both Identical CSE and AC-CSE were extended with active transformations to match non-identical but related terms (Active CSE and Active X-CSE). Neither of these extensions yielded a significant improvement. Our benchmark models were mainly written by expert users. It would be interesting to see whether novice users would write messier models (perhaps expressing the same concept in multiple ways) that would be amenable to Active CSE or Active X-CSE.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>