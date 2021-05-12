<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Agent planning programs.
   </title>
   <abstract>
    This work proposes a novel high-level paradigm, agent planning programs, for modeling agents behavior, which suitably mixes automated planning with agent-oriented programming. Agent planning programs are finite-state programs, possibly containing loops, whose atomic instructions consist of a guard, a maintenance goal, and an achievement goal, which act as precondition-invariance-postcondition assertions in program specification. Such programs are to be executed in possibly nondeterministic planning domains and their execution requires generating plans that meet the goals specified in the atomic instructions, while respecting the program control flow. In this paper, we define the problem of automatically synthesizing the required plans to execute an agent planning program, propose a solution technique based on model checking of two-player game structures, and use it to characterize the worst-case computational complexity of the problem as EXPTIME-complete. Then, we consider the case of deterministic domains and propose a different technique to solve agent planning programs, which is based on iteratively solving classical planning problems and on exploiting goal preferences and plan adaptation methods. Finally, we study the effectiveness of this approach for deterministic domains through an experimental analysis on well-known planning domains.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      This work proposes a novel paradigm for programming intelligent agents and controllers in a task-oriented way that mixes automated planning with agent-oriented programming w.r.t. behavior specification.{sup:1} Generally speaking, we envision the designer providing a high-level model of the “space of deliberation” of the agent—called an agent planning program—that is meant to be “realized” into an executable program via automatic synthesis. Agent planning programs are finite-state programs, possibly containing loops, whose atomic instructions are classical precondition-invariance-postcondition declarative assertions. Such programs are to be executed in possibly nondeterministic domains. A “realization” of such programs in the domain of concern amounts, basically, to a collection of inter-related plans that meet the assertions in the atomic instructions while respecting the program control flow in its totality (that is, a plan for an assertion should not preclude the realization of potential future instructions).
     </paragraph>
     <paragraph>
      Technically, the dynamics of the world is described with a planning domain and a given initial state, as usually done in domain-independent planning [46] and reasoning about action [88]. On top of such (rooted) domain, an agent planning program is modeled as a finite transition system, typically including loops, in which states represent choice points and transitions specify possible objectives that the agent may decide to pursue. Such transitions constitute the high-level actions available to the agent, and are characterized by: (i) a guard, which poses executability preconditions; (ii) a maintenance goal, which specifies invariants that are guaranteed to hold for the course of actions to execute; and (iii) an achievement goal, which specifies the postcondition of the transition. In other words, those triples are a direct counterpart of the classical triple precondition-invariant-postcondition, used in program specification [38], [42], [55] and nowadays in “design-by-contract” or “code-by contract” development [74].
     </paragraph>
     <paragraph>
      Intuitively, agent planning programs are meant to work as follows: at any point in time, based on the current state of the domain and that of the agent planning program, the agent decides, autonomously, which enabled program transition to pursue. A (synthesized) plan satisfying the assertions in the chosen transition is then executed, thus moving the domain and the program to their next states, from which a new transition will be “requested” by the agent, a new plan executed again, and so on. The agent planning program is said to be realized if an adequate plan can always be associated to the execution of transitions, according to the planning program control flow. Note that, although the planning program is a finite transition system, it may generate, due to loops, an infinite computation tree; in principle, one needs to synthesize plans for each of the infinitely many transitions of such a tree. A key point is that, in synthesizing a plan for a particular transition, one needs to take into account that the resulting state of the domain must not only satisfy the corresponding achievement goal assertion, but also must allow for the existence of plans for each possible next transition, and this must hold again after such plans, and so on.
     </paragraph>
     <paragraph>
      By combining declarative and procedural approaches to behavior specification, together with automatic synthesis techniques, the agent planning program approach has the potential to provide convenient and powerful specification of behavior in complex scenarios. For example, they can be used to encode knowledge-intensive business processes (processes reflecting “preferred work practices” whose execution is controlled by contingent agent decision making, coupled with contextual data and knowledge production) [27], [99],{sup:2} or even non-linear storylines behind characters' actions in a video game [18], [85]. Planning programs can also be a convenient model of an embedded system for a smart house controller [52] or a Holonic manufacturing system [50], in which the actual concrete manner of doing things may vary from setting to setting. Last, but not least, they can be used to specify the requirements for a web-service [72]. The assumption is that the agent (e.g., a human interacting with a business process, embedded system, or a game narrative generator) issues, step-by-step, goal requests within the given space of deliberation, which are to be fulfilled by appropriate plans computed by the solver.
     </paragraph>
     <paragraph>
      In this paper, we study the above realizability (and associated synthesis) problem and provide the following contributions:
     </paragraph>
     <list>
      <list-item label="•">
       A formal definition of the problem of realizing an agent planning program and its solution.
      </list-item>
      <list-item label="•">
       A correct and terminating technique for synthesizing realizations, which resorts to automated synthesis for certain kinds of Linear-time Temporal Logic (LTL) specifications based on model checking game structures [80], [82]. Interestingly, such a technique can be readily implemented using available tools for synthesis based on model checking of game structures, such as the well-known TLV[84], JTLV[83], or the more recent NuGaT[17], which we use for our experiments.
      </list-item>
      <list-item label="•">
       A worst-case complexity characterization of the problem as EXPTIME-complete, where we use the above technique for establishing membership in EXPTIME. The EXPTIME-hardness comes from the EXPTIME-completeness of conditional planning with full observability in nondeterministic domains [90], which is a special case of our problem: a planning program formed by a single transition labelled with an achievement goal.
      </list-item>
     </list>
     <paragraph>
      The output obtained from our general realization technique is akin to a sort of sophisticated form of universal plan [92], which is obviously a costly solution [48]. To deal with this, in the second part of the paper, we look for alternative computational approaches based on exploiting state-of-the-art classical planning systems. In particular, we focus on the case of deterministic underlying domains, widely studied in automated planning, for which classical planning systems have shown excellent performance. The contributions for this case are the following:
     </paragraph>
     <list>
      <list-item label="•">
       We show that the worst-case complexity of the problem remains EXPTIME-complete even for deterministic domains. In particular, for membership we can still use the general algorithm, while for the hardness we show a reduction from the service composition problem [76].
      </list-item>
      <list-item label="•">
       We devise a technique for realizing planning programs that is based on classical planning tools, which involves iteratively constructing and synchronizing a set of plans. Importantly, the technique makes use of goal preferences and plan adaptation to considerably speed up plan synthesis and synchronization when realizing looping transitions.
      </list-item>
      <list-item label="•">
       We develop and perform a thorough set of experiments to test our planning-based approach using benchmarks from planning competitions. In the experiments, we drop all transition guards (i.e., we set them to true). Note that realizing planning programs without guards does not represent a simplification in experimenting our algorithm, since it forces the algorithm to realize all outgoing transitions, even those that guards would disable. We consider both maintenance and achievement goals stated as conjunctions.
      </list-item>
      <list-item label="•">
       We demonstrate, via experimental analysis, that our planning-based approach excels in domains in which the backtracking due to planning failures during the transitions realization is limited. In particular, this is the case for planning domains without deadends, where the failures are due to the given limits of the computational resources (CPU time or memory consumption limits), or to the incompleteness of the planner used. As expected, though, as the need for backtracking increases, the performance degrade, and the high worst-case complexity shows up.
      </list-item>
     </list>
     <paragraph>
      Such experimental evaluation indicates that our iterated planning technique constitutes an effective baseline for handling agent planning programs in deterministic domains.
     </paragraph>
     <paragraph>
      As mentioned, agent planning programs advocate a novel paradigm for “programming” complex task-oriented behaviors, by suitably mixing key ingredients of automated planning [46] and agent-oriented programming [66], [67], [87], [97]. From the former, they inherit the ability to specify behaviors in a declarative manner, thus providing an abstract and powerful mechanism that caters for flexible behaviors from first principle, that is, without the need to specify detailed procedural information. As already accepted in the literature, declarative goals provide several other advantages, including decoupling plan execution and goal achievement, facilitating goal dynamics and plan failure handling, enabling reasoning about goal and plan interaction, and enhancing goal and plan communication [101]. From the latter, in turn, planning programs draw the ability to specify useful available “know-how” information, albeit at a high-level of abstraction. By doing so, it is possible to better focus on the relevant decisions—the “space of deliberation.” Concretely, this is achieved by encoding the temporal/procedural relations among the declarative goals of concern: planning programs restrict the options that will be available after the (current) goal is brought about.{sup:3}
     </paragraph>
     <paragraph>
      We note that research on integrating these two approaches has a certain tradition in AI. For example, [106] advocates the use of a high-level model for describing the behaviors of interest in embedded systems, which then need to be “compiled” on-the-fly by a suitable solver into a low-level executable code for a given plant. In [93] planning for temporal goals consisting of a mixture of declarative and procedural assertions are considered. Mixing planning and programs is one of the original motivations behind the Golog family of high-level programming languages [5], [29], [68], possibly the most prominent programming language proposals in reasoning about action. There has also been substantial effort in bringing deliberative planning into standard BDI-style agent architectures, e.g., [39], [91], [103]. In fact, the necessity of studying more systematically planning in combination with acting and programming has been recently thoroughly advocated in [46]. Our proposal of agent planning programs goes exactly in this direction, thus contributing to both agent programming and planning research areas.
     </paragraph>
     <paragraph>
      The rest of the paper is structured as follows. In Section 2, we formally define agent planning programs and the corresponding realization problem. In Section 3, we ground such notions on a full fledged example. Then, in Section 4, we look into the general solution for realizing agent planning programs by resorting to LTL synthesis via model checking of two-player game structures. We show that our solution is sound and complete, and characterize the worst-case computational complexity as EXPTIME-complete. In Section 5, we focus on the case where the domain is deterministic. We prove EXPTIME-completeness also in this case, and we provide our planning based technique and analyze it from the point of view of its correctness and optimizability. After that, in Section 6, we report on a set of experiments that provides evidence of the effectiveness in practice of such technique. Finally, we discuss related work and draw conclusions in Sections 7 and 8, respectively. For the sake of readability, a concrete encoding of planning programs in SMV (the input language of TLV, JTLV and NuGaT), as well as detailed proofs and additional experimental results, are given in appendices.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Agent planning programs
     </section-title>
     <paragraph>
      Agent Planning Programs are high-level representations of the behavior of agents acting in a domain. Essentially, they are transition systems, with states representing decision points, and transitions labelled by triples consisting of a guard, a maintenance goal and an achievement goal, over the domain. For instance, an agent planning program for a researcher's everyday-life routine is depicted in Fig. 1b, under which the agent (i.e., the researcher) can decide to move between home (state {a mathematical formula}v0), work (state {a mathematical formula}v1), and the pub (state {a mathematical formula}v2). So, at planning program state {a mathematical formula}v1, the researcher may decide to go back home (transition to state {a mathematical formula}v0) or instead go out to the pub (transition to state {a mathematical formula}v1). Once at the pub, the agent can only return to her home, where the routine iterates again for the next day.
     </paragraph>
     <paragraph>
      Informally, in order for an agent planning program to be executable, each labeling goal requires a plan to bring it about. Importantly, those plans ought to be “synchronized” so that the final world state generated by each plan is a suitable initial state for the subsequent plans associated with the next goals. When this is the case, the planning program is realized. In general, however, computing a realization does not simply amount to matching program transitions with appropriate plans. The fact is that, as plans are executed, both the state of the planning program and that of the underlying domain evolve and, in general, the planning program may reach the same state in different domain states, so that there is no guarantee that a single plan would work in all such domain states. Thus, a more sophisticated solution concept is required.
     </paragraph>
     <paragraph>
      Our framework consists of two basic components: (i) a planning domain, formalizing the environment that the agent acts in; and (ii) an agent planning program, providing a high-level representation of the agent's space of deliberation.
     </paragraph>
     <paragraph label="Definition 1">
      Planning domainA planning domain is a tuple {a mathematical formula}D=〈P,A,τ〉, where:
     </paragraph>
     <list>
      <list-item label="•">
       P is a finite set of domain propositions; a state of the domain is a subset in {a mathematical formula}2P;
      </list-item>
      <list-item label="•">
       A is the finite set of domain actions; and
      </list-item>
      <list-item label="•">
       {a mathematical formula}τ⊆2P×A×2P is the transition relation; we freely interchange notations {a mathematical formula}〈s,a,s′〉∈τ and {a mathematical formula}s→as′ in {a mathematical formula}D. □
      </list-item>
     </list>
     <paragraph>
      We say that an action a is executable in a state s, if there exists some state {a mathematical formula}s′ such that {a mathematical formula}s→as′ in {a mathematical formula}D. Notice that, in general, planning domains are nondeterministic, as their evolution is modeled by a transition relation. We next define what it means for a plan to achieve a goal in a planning domain {a mathematical formula}D. A {a mathematical formula}D-history_h is a finite sequence {a mathematical formula}s0→a1s1⋯sℓ−1→aℓsℓ, such that: (i) for each {a mathematical formula}i∈{0,…,ℓ}, {a mathematical formula}si∈2P; and (ii) for each {a mathematical formula}i∈{0,…,ℓ−1}, {a mathematical formula}si→ai+1si+1 in {a mathematical formula}D. Intuitively, {a mathematical formula}D-histories capture the possible evolutions of {a mathematical formula}D from a state {a mathematical formula}s0. The set of all possible {a mathematical formula}D-histories is denoted by {a mathematical formula}H. Given a sequence {a mathematical formula}η=s0→a1s1⋯sℓ−1→aℓsℓ, we define the {a mathematical formula}length of η_, denoted {a mathematical formula}|η|, as {a mathematical formula}|η|=ℓ+1, if η is finite (e.g., if it is a history), and {a mathematical formula}|η|=∞, otherwise. Moreover, for {a mathematical formula}0&lt;k&lt;|η|+1, we denote the k-length finite prefix of η as {a mathematical formula}η|k=s0→a1⋯→ak−1sk−1 and its last state as {a mathematical formula}end[η]=sℓ.
     </paragraph>
     <paragraph>
      Given a planning domain {a mathematical formula}D, a history-based plan (H-plan) for {a mathematical formula}D is a partial function {a mathematical formula}π:H↦A such that, given a {a mathematical formula}D-history h, if π is defined on h, it returns an action {a mathematical formula}a=π(h) executable in {a mathematical formula}end[h]. Intuitively, H-plans can be seen as “non-Markovian policies”, i.e., functions that prescribe the action to execute next, given the current history (as opposed to the more commonly used “Markovian' policies”, which prescribe actions based on the current state). A trajectory of an H-plan π (over {a mathematical formula}D), also called a π-trajectory, from a state {a mathematical formula}s0∈2P, is a sequence {a mathematical formula}η=s0→a1s1→a2⋯ such that: (i) for all {a mathematical formula}0&lt;k&lt;|η|+1, {a mathematical formula}η|k is a {a mathematical formula}D-history; and (ii) for all {a mathematical formula}0&lt;k&lt;|η|, {a mathematical formula}ak=π(η|k). Observe that trajectories of H-plans can be either finite or infinite. A trajectory η is said to be complete (w.r.t. π) if it is infinite or such that {a mathematical formula}π(η) is undefined (thus η is finite and cannot be extended further, through π). An H-plan is said to be a history-based terminating plan (HT-plan, for a domain {a mathematical formula}D) if all of its complete trajectories are finite. Obviously, HT-plans induce only finite trajectories, which are in fact {a mathematical formula}D-histories. The set of all HT-plans over {a mathematical formula}D is denoted by {a mathematical formula}HTD.
     </paragraph>
     <paragraph>
      A {a mathematical formula}D-history {a mathematical formula}h=s0→a1s1⋯sℓ−1→aℓsℓachieves a goal ϕ, i.e., a propositional formula over the propositions of {a mathematical formula}D, if {a mathematical formula}sℓ⊨ϕ, where satisfaction is defined as usual in propositional logic. Similarly, hmaintains a goal ψ if {a mathematical formula}si⊨ψ, for every {a mathematical formula}i∈{0,…,ℓ−1}. Observe that maintaining a goal ψ requires the goal to remain true up to the second last state {a mathematical formula}sℓ−1 of the history, while the goal ψ is allowed to become false in the last state {a mathematical formula}sℓ (to make ψ remain true also in the last state we may simply require it to be not only maintained but also achieved). Such notions can be extended to HT-plans, as follows. We say that an HT-plan πachieves a goal ϕ from a state s, if all of its complete trajectories from s (which are histories) do so; also, we say that πmaintains a goal ψ from s if all of its (complete or not) trajectories from s do so.
     </paragraph>
     <paragraph>
      Next, we formally define agent planning programs as a network, constituted by the control flow of the program, of declarative goal assertions, the atomic instructions. Each of these instructions consist of a (potential) agent request, under a certain guard (i.e., precondition), to achieve a given achievement goal (i.e., postcondition) while maintaining certain condition (i.e., invariance).
     </paragraph>
     <paragraph label="Definition 2">
      Agent planning programAn agent planning program is a tuple {a mathematical formula}P=〈P,V,v0,δ〉, where:
     </paragraph>
     <list>
      <list-item label="•">
       P is a finite set of domain propositions;
      </list-item>
      <list-item label="•">
       V is the finite set of program states;
      </list-item>
      <list-item label="•">
       {a mathematical formula}v0∈V is the program initial state of {a mathematical formula}P; and
      </list-item>
      <list-item label="•">
       {a mathematical formula}δ⊆V×Φ(P)×Φ(P)×Φ(P)×V is the transition relation of {a mathematical formula}P, where {a mathematical formula}Φ(P) stands for the set of all boolean formulas built from the set of propositions P. A transition {a mathematical formula}〈v,γ,ψ,ϕ,v′〉∈δ—also {a mathematical formula}〈v,〈γ,ψ,ϕ〉,v′〉∈δ or {a mathematical formula}v→γ:ψ,ϕv′ in {a mathematical formula}P for legibility—is used to denote that whenever the guard γ holds (in the domain), the agent planning program {a mathematical formula}P may legally move from state v to state {a mathematical formula}v′ by “achieving ϕ while maintaining ψ.” □
      </list-item>
     </list>
     <paragraph>
      The idea is that when the planning program and the domain are in states v and s (initially {a mathematical formula}v0 and {a mathematical formula}s0), respectively, the agent is allowed to pursue any enabled (i.e., whose guard holds true in s) planning program transition {a mathematical formula}v→γ:ψ,ϕv′ in {a mathematical formula}P. However, being declarative assertions, such transition are not directly executable and actual realizations are required for them. A realization, then, must provide a concrete HT-plan π that brings about the achievement goal ϕ while guaranteeing maintenance of ψ and, furthermore, be compatible with further realizations for subsequent transitions (i.e., atomic instructions) of the planning program. The latter requirement is central to the approach, as the choice points in the planning program are resolved by decisions made by the agent only at runtime. It should be noted that only in special cases we can realize planning programs by simply annotating transitions with plans. In general, the annotation should be done on the (infinite) computation tree generated by the planning program. Indeed, a transition in the planning program may be pursued (i.e., requested by the agent) at different moments in time, from different states of the domain, and so different plans may be required.
     </paragraph>
     <paragraph>
      With this intuition at hand, we are now prepared to formalize the notion of planning program realization, thus providing semantics to agent planning programs. We base such notion on a suitable variant of the formal notion of simulation[75], under which, loosely speaking, transitions are matched by plans, rather than by single actions.
     </paragraph>
     <paragraph label="Definition 3">
      Plan-based simulationLet {a mathematical formula}D=〈P,A,τ〉 be a planning domain and {a mathematical formula}P=〈P,V,v0,δ〉 an agent planning program. A plan-based simulation relation, or PLAN-simulation relation, is a relation {a mathematical formula}R⊆V×2P such that {a mathematical formula}〈v,s〉∈R implies that, for every transition {a mathematical formula}v→γ:ψ,ϕv′ in {a mathematical formula}P such that {a mathematical formula}s⊨γ, there exists an HT-plan π such that:
      <list>
       π achieves ϕ and maintains ψ from s (in which case, plan π is said to realize the transition {a mathematical formula}v→γ:ψ,ϕv′); andfor all complete trajectories h of plan π from domain state s, it is the case that {a mathematical formula}〈v′,end[h]〉∈R (in which case plan π is said to preserveR from {a mathematical formula}〈v,s〉 for {a mathematical formula}v→γ:ψ,ϕv′).A
      </list>
      <paragraph>
       {a mathematical formula}P-state {a mathematical formula}v∈V is said to be PLAN-simulated by a {a mathematical formula}D-state {a mathematical formula}s∈2P, denoted {a mathematical formula}v⪯PLANs, if there exists a PLAN-simulation relation R such that {a mathematical formula}〈v,s〉∈R. □
      </paragraph>
     </paragraph>
     <paragraph>
      As for standard simulation, relation {a mathematical formula}⪯PLAN is a PLAN-simulation relation itself and, in particular, the largest one (with respect to set inclusion)—it can be obtained by taking the union of all PLAN-simulation relations.
     </paragraph>
     <paragraph label="Definition 4">
      Agent planning program realizationA realization of an agent planning program {a mathematical formula}P in planning domain {a mathematical formula}D from an initial {a mathematical formula}D-state {a mathematical formula}s0∈2P is a partial function {a mathematical formula}Ω:2P×δ↦HTD such that for some PLAN-simulation relation R, it is the case that:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}〈v0,s0〉∈R; and
      </list-item>
      <list-item label="•">
       for all pairs {a mathematical formula}〈v,s〉∈R and all transitions {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 in {a mathematical formula}P such that {a mathematical formula}s⊨γ, an HT-plan {a mathematical formula}Ω(s,d) is defined, realizes transition d, and preserves R from {a mathematical formula}〈v,s〉 for d. □
      </list-item>
     </list>
     <paragraph>
      That is, a realization Ω is a function that given a domain state s and a transition request {a mathematical formula}v→γ:ψ,ϕv′, whose guard is satisfied in s, outputs an HT-plan π that achieves ϕ while maintaining ψ from s and guarantees that all potential future requests from {a mathematical formula}v′ after π's execution can also be fulfilled by plans prescribed by the realization function Ω.
     </paragraph>
     <paragraph label="Theorem 1">
      Our first result states if the initial state of {a mathematical formula}P is PLAN-simulated by the initial state of {a mathematical formula}D then it is guaranteed that a realization exists (and obviously viceversa). There exists a realization Ω of an agent planning program{a mathematical formula}Pin a planning domain{a mathematical formula}Dfrom{a mathematical formula}D-state{a mathematical formula}s0if and only if{a mathematical formula}v0⪯PLANs0.
     </paragraph>
     <paragraph label="Proof">
      (If Part) If {a mathematical formula}v0⪯PLANs0, then for all pairs {a mathematical formula}v⪯PLANs and all transitions {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 in {a mathematical formula}P, there exists an HT-plan π that realizes d and preserves {a mathematical formula}⪯PLAN from {a mathematical formula}〈v,s〉 for d. Thus, we define {a mathematical formula}Ω(s,d)=π by taking {a mathematical formula}⪯PLAN itself as the PLAN-simulation relation R.(Only-If Part) Immediately follows from the definition of realization, which requires the existence of a PLAN-simulation R such that {a mathematical formula}〈v0,s0〉∈R. Hence, {a mathematical formula}⪯PLAN being the largest PLAN-simulation, we have that {a mathematical formula}v0⪯PLANs0.  □
     </paragraph>
     <paragraph>
      A planning program {a mathematical formula}P is said to be realizable in a planning domain {a mathematical formula}D if there exists a realization of {a mathematical formula}P in {a mathematical formula}D from {a mathematical formula}D's initial state. When that happens, there exists a realization Ω such that all possible sequences of legal requests that the agent may issue starting from the initial configuration {a mathematical formula}〈v0,s0〉 can be fulfilled by HT-plans returned by Ω.
     </paragraph>
     <paragraph>
      In the next sections, we will devise techniques to check whether an agent planning program {a mathematical formula}P is realizable in a domain {a mathematical formula}D and, if so, to actually build a corresponding realization function Ω. Before doing so we illustrate the above notions with an example.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      An example
     </section-title>
     <paragraph>
      In this section we illustrate the previous notions (and some of their subtleties) through a simple example on the everyday-life behavior of an academic. The researcher moves among four locations, namely: home, the academic department building, the department parking lot, and a pub. To move from one place to another, the researcher can drive a car, take a bus, or just walk. Due to highways, traffic restrictions, and distances, not all alternatives are available from every locations (e.g., it is too far to walk to work and campus circulation is restricted to buses only). In Fig. 1a, all allowed movements in the relevant domain are depicted.
     </paragraph>
     <paragraph>
      Besides the location of the researcher, the domain includes other features not shown in the figure. For instance, some amount of fuel is consumed each time the car changes location and, at any point in time, it may rain (proposition {a mathematical formula}Rain). In our first, deterministic, version of the domain, though, we assume that it is never raining (i.e., {a mathematical formula}Rain is always false) and the fuel in the car's tank decreases by one level with each action drive, that is, from full to low and from low to empty, with each trip (via action drive). As expected, the car cannot be driven when the tank is empty. However, the tank can be brought to its full level by refueling (represented by action refuel). We shall later revisit this assumption in a non-deterministic variant of the example.
     </paragraph>
     <paragraph>
      Let us formalize this planning domain {a mathematical formula}D=〈P,A,τ〉, as follows:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}P={Fuel(full),Fuel(low),Fuel(empty),MyLoc(home),MyLoc(pub),MyLoc(dept),MyLoc(lot),CarLoc(home),CarLoc(pub),CarLoc(lot),Driven,Rain}.
      </list-item>
      <list-item label="•">
       {a mathematical formula}A=Adrive∪Awalk∪AtakeBus∪{refuel}, where:
      </list-item>
      <list-item label="•">
       {a mathematical formula}τ=τdrive∪τrefuel∪τwalk∪τtakeBus, where:
      </list-item>
     </list>
     <paragraph>
      The intended meaning of the propositions in P is self-explanatory: {a mathematical formula}Fuel(l) denotes the tank level; {a mathematical formula}MyLoc(l) and {a mathematical formula}CarLoc(l) denote the location of the researcher and car, respectively; {a mathematical formula}Driven states that the car has just been driven in the previous action; and {a mathematical formula}Rain states that it is raining. Also actions are self-describing. For instance, {a mathematical formula}walk(dept) is the action of the researcher walking to the department building (note there is no action {a mathematical formula}drive(dept), as driving in the campus is not allowed).
     </paragraph>
     <paragraph>
      Executability and effects of actions are captured by the transition relation τ. For example, the set of transitions {a mathematical formula}τdrive represents the transitions between states s and {a mathematical formula}s′ when the agent drives to destination location l. The action can only be executed when the car has fuel, and the agent and the car are co-located at {a mathematical formula}l′ (different from destination l). After the execution of the action, both the agent and the car are located in l, the car has just been driven, and its tank level has decreased by one unit (see {a mathematical formula}τrefuel).
     </paragraph>
     <paragraph>
      Now imagine that the researcher wants to be able to go to work and, after work, maybe drop by the pub before heading back home. Sometimes, e.g., on weekends, she may want to go to the pub directly from home. For safety reasons, the researcher does not want to drive after having been at the pub. Also, a very natural requirement is that the car never runs out of fuel. Such desired behavior can be captured by the agent planning program depicted in Fig. 1b. Each transition is labeled with a triple {a mathematical formula}〈γ,ψ,ϕ〉 encoding the required guard, maintenance and achievement goals, respectively γ, ψ and ϕ. We use the notation {a mathematical formula}v→γ:ψ+,ϕv′ to denote {a mathematical formula}v→γ:ψ,(ϕ∧ψ)v′, to abbreviate the common case where the maintenance goal needs to remain true also at the end. For instance, the maintenance goal {a mathematical formula}(¬Fuel(empty)∧¬Driven)+ annotating the guard-free transition from state {a mathematical formula}v2 to state {a mathematical formula}v0, requires that both the car does not run out of fuel and that the researcher avoids driving after having been at the pub. Notice that such requirements need to hold also when the achievement goal {a mathematical formula}MyLoc(home) is fulfilled.
     </paragraph>
     <paragraph>
      The question is: can the researcher carry out such a program, and if so, how? As an example of positive answer, consider Table 1, which describes a possible realization for this program. The first column represents the current state of the domain; the second one contains the requested program transition; and the third one represents the plan to be executed from the current domain state to realize the requested transition. For simplicity, the second column includes only the source and target state of a program transition, while the corresponding guards, maintenance and achievement goals are specified in Fig. 1. Lastly, the third column reports the corresponding HT-plan, as a sequence of actions given that the domain is deterministic.
     </paragraph>
     <paragraph>
      Consider the first line in the table. If, from the current domain state, the researcher chooses to go to the department (transition {a mathematical formula}〈v0,v1〉), the corresponding plan consists in driving first to the parking lot and then walking to the department. In the domain state resulting from executing this plan (fifth row in the table), the researcher is at the department and the car is at the parking lot with a low fuel level. From this state, when the researcher chooses to go back home, the corresponding plan consists in walking to the parking lot, refueling the car, driving home and finally refueling the car again. Observe that the first refuel action is required to prevent the car from running out of fuel, whereas the second one is not strictly required (the researcher could execute it as the first action of any future plan that includes driving the car). Notice that the state resulting from executing this plan is the one we initially started from. Thus, if the researcher needs to go to work again, the very same plan executed before is still available. Interestingly, this realization example associates the transition {a mathematical formula}v0→v1 with two distinct plans (see third line of the table), depending on the current domain state.
     </paragraph>
     <paragraph>
      Next consider a nondeterministic variant of this example, in which the fuel level and weather evolves nondeterministically. So, with each trip, the tank level may either stay the same, decrease from full to low or from low to empty, and the whether it is raining or not may change at every time-step (i.e., with every action performed). To model the new dynamics for fuel consumption, we replace {a mathematical formula}τdrive for action {a mathematical formula}drive(l) with:{a mathematical formula}
     </paragraph>
     <paragraph>
      For this scenario, the realization needs to work no matter what the outcome of nondeterministic actions turns out to be. It can be seen that there exists a realization of the program for this variant that is similar to the one for the deterministic case, although the plans used are conditional. Observe also that, as a result of nondeterministic actions, the execution of plans may result in on of many states, instead of one only. For instance, take the plan in the first line of Table 1 and consider its execution from the corresponding domain state. As a result of the nondeterminism of drive, after executing the first action, the tank level can be either low or full. Consequently, after the plan is executed (walk is not affected by the fuel level), the domain can be in two possible states, i.e., either {a mathematical formula}{MyLoc(dept),CarLoc(lot),Fuel(full)} or {a mathematical formula}{MyLoc(dept),CarLoc(lot),Fuel(low)}. Thus, in order to realize the planning program, a (HT-) plan must be defined for each of such states. For instance, to realize transition {a mathematical formula}v1→v0, we need to define a plan that is executable from each of the states above. In our case, it is easy to see that the plan defined in the fifth line of the table can be executed from either state, as the maintenance goal {a mathematical formula}¬Fuel(empty) (as well as executability of drive) is guaranteed by the execution of refuel as the second action of the plan, and then again immediately after drive. Finally, notice that when {a mathematical formula}Rain is true, the program transition {a mathematical formula}〈v0,v2〉 is not executable, as {a mathematical formula}¬Rain is a guard for that transition, in fact simplifying the realization of the planning program.
     </paragraph>
     <paragraph>
      An actual, more involved, example in the context of smart homes for disabled people is reported in [27], where an early version of agent planning programs is used.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      General solution technique
     </section-title>
     <paragraph>
      In this section, we develop a general solution approach for realizing planning programs, based on the use of synthesis techniques via model checking of two-player game structures. Concretely, we show that checking the existence of a realization of an agent planning program is equivalent to checking whether a strategy exists to force a certain Linear-time Temporal Logic (LTL) formula in a suitable two-player game structure. Moreover from such strategy it is possible to extract an actual realization for the original problem. The main results of this section are a soundness and completeness theorem for the proposed technique, and the characterization of the computational complexity of the problem as EXPTIME-complete.
     </paragraph>
     <section label="4.1">
      <section-title>
       LTL synthesis based on two-player game structures
      </section-title>
      <paragraph>
       Linear-time Temporal Logic (LTL) is a well-known logic used to specify dynamic or temporal properties of programs [81], [102]. Formulas of LTL are built from a set {a mathematical formula}Q of atomic propositions and are closed under the boolean operators, the unary temporal operators ◯ (next), ◊ (eventually), and □ (always), and the binary temporal operator {a mathematical formula}U (until), which in fact can express both ◊ and □ (as {a mathematical formula}trueUϕ and {a mathematical formula}ϕUfalse, respectively). LTL formulas are interpreted over infinite sequences σ of propositional interpretations for {a mathematical formula}Q, i.e., {a mathematical formula}σ∈(2Q)ω.{sup:4} The set of (true) propositions at position i is denoted by {a mathematical formula}σ(i), that is, {a mathematical formula}σ=σ(0),σ(1),…. Given an interpretation σ, a natural number i, and an LTL formula ϕ, we denote by {a mathematical formula}σ,i⊨ϕ the fact that ϕ holds in σ at position i. This is inductively defined as follows, for {a mathematical formula}p∈Q a proposition, and {a mathematical formula}ϕ,ψ LTL formulas:{a mathematical formula}
      </paragraph>
      <paragraph>
       An interpretation σ satisfies ϕ, written {a mathematical formula}σ⊨ϕ, if {a mathematical formula}σ,0⊨ϕ. Standard logical tasks such as satisfiability or validity are defined as usual, i.e., a formula ϕ is satisfiable if there exists an interpretation that satisfies it, while it is said to be valid if it is satisfied by every possible interpretation. Checking satisfiability or validity of LTL formulas is PSPACE-complete [102].
      </paragraph>
      <paragraph>
       Satisfiability and validity of LTL (and more in general of temporal) formulas are typical in verification. Here we are interested in a different kind of logical task, namely reactive synthesis[82], [102]. This can be described as follows. Assume {a mathematical formula}Q is partitioned into two sets {a mathematical formula}X and {a mathematical formula}Y of propositions, the former controlled by a module called environment, and the latter controlled by a module called system. Let the modules interact through the propositions in {a mathematical formula}Q, and have their own internal structure which defines the way they can change proposition values, based on the current assignments. When running, the environment and the system define a compound dynamic system whose evolutions stem from their interaction and that can be described in terms of sequences of assignments to {a mathematical formula}Q. Assume the environment is uncontrollable, that is, we have no way to change its internal structure, while the system is controllable, meaning that we can restrict its behavior. The problem then is: can we restrict the system behavior to control the values of{a mathematical formula}Yso that no matter which values the environment assigns to the propositions in{a mathematical formula}X, a desired LTL formula is satisfied?
      </paragraph>
      <paragraph>
       Interestingly, LTL synthesis is in general decidable and in fact 2EXPTIME-complete [82], but practically efficient procedures for it are still missing. For this reason, synthesis for special classes of LTL formulas has been investigated. Here we focus on the class of so-called GR(1) LTL formulas studied in [11]. These include formulas that describe transition systems (those that describe the next state given the current one) and formulas like □ϕ, ◊ϕ, and {a mathematical formula}□◊ϕ where ϕ is propositional. In particular, for agent planning programs, we will use those in the latter class, which require that ϕ is satisfied infinitely many times. For such GR(1) LTL formulas, we can efficiently reduce synthesis to model checking of a so-called “two-player game structure” [1], [11], [49], [33].
      </paragraph>
      <paragraph>
       A two-player game structure, 2GS for short, is a tuple {a mathematical formula}G=〈X,Y,I,ρe,ρs〉, where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}X={x1,…,xm} and {a mathematical formula}Y={y1,…,yn} are the disjoint finite sets of environment and system propositional variables, respectively. We define the set of game state variables as {a mathematical formula}V≐X⊎Y (symbol ⊎ denotes disjoint union), and a game state as an interpretation of the variables in {a mathematical formula}V. We represent propositional interpretations {a mathematical formula}i:V↦{⊤,⊥} as subsets {a mathematical formula}W⊆V, adopting the convention that {a mathematical formula}i(w)=true in W if and only if {a mathematical formula}w∈W. Interpretations of {a mathematical formula}X and {a mathematical formula}Y variables are represented accordingly.
       </list-item>
       <list-item label="•">
        {a mathematical formula}I⊆V is the (unique) initial state of the game.
       </list-item>
       <list-item label="•">
        {a mathematical formula}ρe⊆2X×2Y×2X is the environment transition relation, which relates a game state to its possible successor environment states, i.e., {a mathematical formula}X-interpretations.
       </list-item>
       <list-item label="•">
        {a mathematical formula}ρs⊆2X×2Y×2Y is the system transition relation, which relates a current game state to the possible successor system states, i.e., {a mathematical formula}Y-interpretations.
       </list-item>
      </list>
      <paragraph>
       Observe that an interpretation {a mathematical formula}W⊆V is partitioned into two components {a mathematical formula}X⊆X and {a mathematical formula}Y⊆Y. We often refer to a game state W as {a mathematical formula}(X,Y), under the convention that X and Y represent the corresponding total assignments to {a mathematical formula}X and {a mathematical formula}Y, respectively.
      </paragraph>
      <paragraph>
       Intuitively, a 2GS captures the rules of a game where the environment and the system play as opponents. The game starts in the initial state {a mathematical formula}I=(XI,YI), and the players alternate their moves, the environment moving first, by choosing their next state among those their transition relations enable. In details, when the current state of the game is {a mathematical formula}W=(X,Y), the environment chooses some {a mathematical formula}X′⊆X such that {a mathematical formula}ρe((X,Y),X′), and the system responds with some {a mathematical formula}Y′⊆Y such that {a mathematical formula}ρs((X′,Y),Y′). Such moves lead the game to a new state {a mathematical formula}W′=(X′,Y′) from which a new round is played, which in turn leads the game to a new state, and so on. We define the game successor relation as the relation {a mathematical formula}ρ⊆(2X×2Y)×(2X×2Y) such that {a mathematical formula}ρ(W,W′) if and only if, for {a mathematical formula}W=(X,Y) and {a mathematical formula}W′=(X′,Y′), {a mathematical formula}ρe((X,Y),X′) and {a mathematical formula}ρs((X′,Y),Y′). An infinite sequence σ of legal moves starting from the initial state constitutes a play of the game, i.e., {a mathematical formula}σ=W0W1⋯ such that {a mathematical formula}ρ(Wi,Wi+1), for {a mathematical formula}i≥0. Without loss of generality, we make the assumption that ρ is serial, that is, for any finite sequence {a mathematical formula}λ=W0⋯Wn such that, for {a mathematical formula}0≤i&lt;n, {a mathematical formula}ρ(Wi,Wi+1) holds, there exists {a mathematical formula}W′ such that {a mathematical formula}ρ(Wn,W′). This corresponds to the intuition that each player can always reply to the opponent, which in turn yields that 2GSs always admit a play.
      </paragraph>
      <paragraph>
       A 2GS defines the constraints that players must respect when playing, but does not define the goal of the game, or the winning condition, i.e., the condition φ that a player needs to achieve in order to win a play. For this, we consider LTL formulas, in particular GR(1) formulas, over propositions in {a mathematical formula}V, and say that a play, which is an LTL interpretation over {a mathematical formula}V, is winning for the system if it satisfies φ. Notice that a play captures only a possible evolution of the game, while we are interested in defining when the system can force the game to evolve along a play winning for itself, no matter how the environment moves. To this end we introduce the following notion. Given a 2GS with set of game variables {a mathematical formula}V=X⊎Y, a strategy for the system is a partial function {a mathematical formula}f:(2X)+↦2Y such that: (i){a mathematical formula}f(XI)=YI; and (ii) for {a mathematical formula}ℓ≥0, if {a mathematical formula}f(X0⋯Xℓ)=Yℓ is defined, with {a mathematical formula}X0=XI, then, for every X such that {a mathematical formula}ρe((Xℓ,Yℓ),X), it is the case that {a mathematical formula}Y=f(X0⋯XℓX) is defined and {a mathematical formula}ρs((X,Yℓ),Y). Intuitively, a strategy represents the behavior that the system follows, after having observed a sequence of environment moves. Notice that, by the assumptions on ρ, a strategy for the system always exists. Furthermore, observe that the definition of strategy does not mention the system component explicitly. This is implicitly defined, at each step, by f on those plays where the system acts according to f, which are the only plays of interest to synthesis. Such plays are discussed next.
      </paragraph>
      <paragraph>
       A play {a mathematical formula}σ=(X0,Y0)(X1,Y1)⋯ is said to be {a mathematical formula}compliant with a strategyf_ if {a mathematical formula}Yi=f(X0⋯Xi), for all {a mathematical formula}i≥0. That is, plays compliant with f capture the game evolutions where the system plays according to f. Obviously, given a sequence {a mathematical formula}X0X1⋯ of environment states from a play σ compliant with f, the system components of σ can be fully reconstructed by subsequent applications of f.
      </paragraph>
      <paragraph>
       A strategy f is said to be winning for the system if for all plays {a mathematical formula}σ=(X0,Y0)(X1,Y1)⋯ compliant with f, it is the case that {a mathematical formula}σ⊨φ. When such a strategy exists, the game structure is said to be winning for the system, otherwise it is winning for the environment. As it turns out, when the system plays according to a winning strategy, all the plays that can stem from the game, and that correspond to different combinations of legal moves of the environment, are guaranteed to satisfy the winning condition. The synthesis problem is the problem of constructing, given a 2GS and a winning condition φ, a winning strategy for the system. The realizability problem is its decision version, i.e., the problem of checking whether such a strategy exists.
      </paragraph>
      <paragraph label="Proof">
       For our purposes, we focus on game winning conditions that belong to the class of so-called weak-fairness formulas, i.e., formulas of the form {a mathematical formula}□◊ϕ, where ϕ is propositional, which in turn are in the GR(1) class. Specifically a 2GS together with this winning condition defines a so-called Büchi game[49], i.e., a game where the system wins if it can force visiting one of the states in an acceptance set {a mathematical formula}F⊆2X×2Y infinitely often. In particular, we have {a mathematical formula}F={W∈2X×2Y|W⊨ϕ}. For this class of games, we have the following result, based on the fixpoint computation of all states from which a play can be forced to achieve a state in F[49]. Given a 2GS{a mathematical formula}G=〈X,Y,I,ρe,ρs〉and a winning condition{a mathematical formula}φ=□◊ϕ, with ϕ propositional, the realizability and synthesis problems can be solved in time{a mathematical formula}O(n(n+m)), where{a mathematical formula}V=X∪Y,{a mathematical formula}n=2|V|is the number of states in G, and{a mathematical formula}m=|ρe|+|ρs|is the number of transitions in G.Direct consequence of the construction of the winning region in [49, Theorem 2.22].  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Solving agent planning programs
      </section-title>
      <paragraph>
       We now show how to compute a realization of an agent planning program {a mathematical formula}P in a dynamic domain {a mathematical formula}D from an initial state {a mathematical formula}s0, by reduction to synthesis for a 2GS with an LTL weak-fairness formula as winning condition. In the resulting game structure, the environment captures the joint evolution of the domain and the planning program, and the system represents an executor whose available moves are those enabled by the domain. The environment, besides keeping track of the current domain state, requests the next transition to be realized, while the system generates the actions to fulfill the request. Whenever a request is fulfilled, a flag is raised and a new transition is requested by the environment, after which the flag is reset. The winning condition for the system is to make the flag raise infinitely many times, that is, to guarantee that every time a transition is requested, it is eventually realized.
      </paragraph>
      <paragraph>
       We start by building the 2GS G. We first specify the sets of environment and system propositions {a mathematical formula}X and {a mathematical formula}Y, then we describe the initial state I of the game structure, and finally we build the transition relations {a mathematical formula}ρe and {a mathematical formula}ρs. We assume that the planning domain {a mathematical formula}D starts in the initial state {a mathematical formula}s0.
      </paragraph>
      <section>
       <section>
        <section-title>
         Environment and system propositions
        </section-title>
        <paragraph>
         We define the set of environment propositions {a mathematical formula}X as the disjoint union of the following sets:
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}XD=P, containing the propositions of the planning domain {a mathematical formula}D;
         </list-item>
         <list-item label="•">
          {a mathematical formula}XV=V, containing the states of the planning program {a mathematical formula}P;
         </list-item>
         <list-item label="•">
          {a mathematical formula}Xr={reqγ:ψ,ϕv,v′|〈v,〈γ,ψ,ϕ〉,v′〉∈δ}, containing one proposition per program transition, with {a mathematical formula}reqγ:ψ,ϕv,v′ stating that {a mathematical formula}P's transition {a mathematical formula}v→γ:ψ,ϕv′ is currently requested.
         </list-item>
         <list-item label="•">
          {a mathematical formula}Xlr={reqα:⊤,⊤v,v|v∈V,α=⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δ¬γ}, containing one dummy looping request proposition per program state v that can only be requested (i.e., whose guard is true) when no other transition request from v can (i.e., all their guards are false).
         </list-item>
        </list>
        <paragraph>
         Notice that, although the same syntactic symbols are used, the states of {a mathematical formula}P are interpreted as propositions in the game structure.
        </paragraph>
        <paragraph>
         The set of controlled propositions is defined as {a mathematical formula}Y=YA⊎{wait,init,last,violated}, where {a mathematical formula}YA=A. Similarly as above, each action {a mathematical formula}a∈YA∪{wait} is interpreted as a proposition in the game structure denoting the action execution. Distinguished proposition wait stands for a no-op action. Proposition init is used to mark the initial state, last is a special proposition stating that the last action performed has completed the HT-plan under execution, and violated represents the fact that some maintenance goal violation has occurred, either in the current or in some past state.
        </paragraph>
        <paragraph>
         The following syntactic shortcuts will be useful in the following:
        </paragraph>
        <list>
         <list-item label="•">
          for every {a mathematical formula}D-state {a mathematical formula}s∈2P we define a propositional formula {a mathematical formula}ςs=⋀i=1nli, where {a mathematical formula}li=pi, if {a mathematical formula}pi∈s, and {a mathematical formula}li=¬pi, otherwise. That is, {a mathematical formula}ςs states the fact that {a mathematical formula}D is in state s;
         </list-item>
         <list-item label="•">
          for every {a mathematical formula}P-state {a mathematical formula}v∈V we define a propositional formula {a mathematical formula}ςv=v∧⋀v′∈V,v′≠v¬v′. That is, {a mathematical formula}ςv states that {a mathematical formula}P is in state v; and
         </list-item>
         <list-item label="•">
          for every program state {a mathematical formula}v∈V, we define a propositional formula {a mathematical formula}reqv=⋁〈v,〈γ,ψ,ϕ〉,v′〉∈δreqγ:ψ,ϕv,v′. That is, {a mathematical formula}reqv states that (at least) one transition among those available in the state v of the planning program is currently requested.
         </list-item>
        </list>
       </section>
       <section>
        <section-title>
         Initial state
        </section-title>
        <paragraph>
         The initial (dummy) state is simply defined as {a mathematical formula}I={init}, i.e., {a mathematical formula}XI=∅ and {a mathematical formula}YI={init,last}. Notice that neither the agent planning program nor the domain are in their initial state. However, as it will be clear shortly, this configuration is achieved after the first game transition occurs.
        </paragraph>
       </section>
       <section>
        <section-title>
         Environment transition relation
        </section-title>
        <paragraph>
         We describe the transition relations {a mathematical formula}ρe and {a mathematical formula}ρs declaratively, using simple LTL formulas of the form {a mathematical formula}□φe and {a mathematical formula}□φs, respectively, where {a mathematical formula}φe and {a mathematical formula}φs refer only to the current and the next state (the only temporal operator allowed in these formulas is ◯). We adopt the convention that a pair {a mathematical formula}〈W,W′〉, with {a mathematical formula}W⊆V and {a mathematical formula}W′⊆X (respectively, {a mathematical formula}W′⊆Y), is in the transition relation of the environment (resp., of the system) if and only if, for some sequence σ starting with the prefix {a mathematical formula}W,W′, i.e., {a mathematical formula}σ=WW′⋯, it is the case that σ satisfies {a mathematical formula}φe (resp., {a mathematical formula}φs). For instance, if {a mathematical formula}φe=p∧¬◯p is the formula defining {a mathematical formula}ρe, then {a mathematical formula}〈{p},∅〉∈ρe, as {a mathematical formula}σ⊨φe for any sequence {a mathematical formula}σ={p}∅⋯, while {a mathematical formula}〈{p},{p}〉∉ρe, as for no sequence {a mathematical formula}σ={p}{p}⋯, it is the case that {a mathematical formula}σ⊨φe.
        </paragraph>
        <paragraph>
         The transition relation {a mathematical formula}ρe is captured by the formula {a mathematical formula}φe=transD∧transP, where {a mathematical formula}transD and {a mathematical formula}transP capture the transition relations of the domain and the planning program, respectively. In words, {a mathematical formula}φe encodes the synchronous execution of the domain and the planning program, taking into account, when needed, the value of the auxiliary variables init and last.
        </paragraph>
        <paragraph>
         Technically, {a mathematical formula}transD is obtained as a conjunction of the following formulas:
        </paragraph>
        <list>
         <list-item label="E1">
          {a mathematical formula}init→◯ςs0, encoding that the domain is in its initial state, after the initial (dummy) move.
         </list-item>
         <list-item label="E2">
          {a mathematical formula}⋀s∈2P(ςs∧wait→◯ςs), expressing that the domain remains still on action wait.
         </list-item>
         <list-item label="E3">
          {a mathematical formula}⋀s∈2P,a∈YA(ςs∧a→◯⋁〈s,a,s′〉∈τςs′), expressing that if the domain is in state s, action a is to be executed next (which can happen only if the current game state is not I), then all possible successor states of s reachable through τ by executing a can occur next (we assume that an empty set of disjuncts equals false).
         </list-item>
        </list>
        <paragraph>
         Notice that we use the formulas above to encode transitions only for simplicity. In practice, it is not needed to list all of them explicitly, but a compact representation can be used. An example of this appears in Section Appendix A, where we report the encoding in the concrete language SMV used (in slightly different variants) by the systems TLV, JTLV and NuGaT.
        </paragraph>
        <paragraph>
         As to {a mathematical formula}transP, it is the conjunction of the following formulas:
        </paragraph>
        <list>
         <list-item label="E4">
          {a mathematical formula}init→◯v0, which encodes that the planning program is initially in its initial state.
         </list-item>
         <list-item label="E5">
          {a mathematical formula}⋁v∈XV◯[v∧⋀v′∈XV∖{v}¬v′], which encodes that the planning program can move to exactly one of its states.
         </list-item>
         <list-item label="E6">
          {a mathematical formula}⋀v∈XV◯[v→reqv], which encodes that at least one transition available in the state the planning program moves to must be requested next.
         </list-item>
         <list-item label="E7">
          {a mathematical formula}last→⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δ◯[reqγ:ψ,ϕv,v′→γ], which expresses that a new transition {a mathematical formula}v→γ:ψ,ϕv′ can be requested only if, at the time of issuing the request (i.e., after last holds), guard γ is satisfied.
         </list-item>
         <list-item label="E8">
          {a mathematical formula}⋀req,req′∈Xr,req≠req′◯[req→¬req′], that is, at most one program transition can be requested at a time.
         </list-item>
         <list-item label="E9">
          {a mathematical formula}⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δ[reqγ:ψ,ϕv,v′∧last→◯v′], capturing that if transition {a mathematical formula}v→γ:ψ,ϕv′ is currently requested and the last action performed has completed the current HT-plan, then the planning program moves to {a mathematical formula}v′.
         </list-item>
         <list-item label="E10">
          {a mathematical formula}⋀v∈XV[(v∧¬last)→◯v], which expressing that the program remains still if the current HT-plan has not been completed.
         </list-item>
         <list-item label="E11">
          {a mathematical formula}⋀req∈Xr[(req∧¬last)→◯req], capturing that the agent remains requesting the same transition if the current HT-plan has not been completed.
         </list-item>
        </list>
        <paragraph>
         Notice that the environment can always make a move. In particular, when the game represents a program state v for which no actual transition can be requested in the current domain state—all guards are false—the environment can play the dummy transition request included in set {a mathematical formula}Xlr for state v. This, together with the fact that every executable action yields at least one next domain state, guarantees that {a mathematical formula}ρe is serial, that is, every state has a successor. Observe also that the last two formulas of {a mathematical formula}transD and the last three formulas for {a mathematical formula}transP trivially evaluate to true in the initial game state I—they do not constrain the first move of the environment.
        </paragraph>
       </section>
       <section>
        <section-title>
         System transition relation
        </section-title>
        <paragraph>
         We now build {a mathematical formula}φs, the formula that captures system player's transition relation {a mathematical formula}ρs, i.e., the capabilities of the system. In other words, formula {a mathematical formula}φs shall capture when actions can be executed and when the HT-plan under execution can be declared to be completed (via proposition last). The system also keeps track of maintenance goal violations (via proposition violated). The formula {a mathematical formula}φs is the conjunction of the following subformulas:
        </paragraph>
        <list>
         <list-item label="S1">
          {a mathematical formula}φinit=◯¬init, which states that init holds only in the initial state.
         </list-item>
         <list-item label="S2">
          {a mathematical formula}φact=⋁a∈YA∪{wait}◯[a∧⋀a′∈YA,a′≠a¬a′], that is, exactly one domain action, or no-op wait action, is executed at each step.
         </list-item>
         <list-item label="S3">
          {a mathematical formula}φpre=⋀a∈YA◯[a→⋁〈s,a,s′〉∈τςs], which requires that domain action a can be executed only if the domain is in a state s where the action is executable, i.e., its precondition is fulfilled.
         </list-item>
         <list-item label="S4">
          {a mathematical formula}φwait=◯[wait↔(last∨⋀〈s,a,s′〉∈τ¬ςs)], which requires that the no-op action wait is executed if and only if last holds or no domain action can be performed (i.e., the precondition of every action is false).
         </list-item>
         <list-item label="S5">
          {a mathematical formula}φlast=⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δ◯[(reqγ:ψ,ϕv,v′∧last)→(ϕ∧¬violated)], expressing that an HT-plan can be declared completed only if the achievement goal ϕ of the transition currently requested is indeed achieved and no violation of a maintenance goal has (ever) occurred.
         </list-item>
         <list-item label="S6">
          {a mathematical formula}φmaint=◯[⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δreqγ:ψ,ϕv,v′∧¬ψ∧¬last→violated]∧[¬violated∧◯(last∨⋀〈v,〈γ,ψ,ϕ〉,v′〉∈δ(reqγ:ψ,ϕv,v′→ψ)))→◯¬violated], expressing that a violation occurs if and only if the maintenance goal ψ of the requested transition is not satisfied. Note that non-satisfaction of the maintenance formula in the final step of a plan's execution (i.e., when last holds) is not considered a violation (refer to definition of a plan maintaining a goal in page 67).
         </list-item>
         <list-item label="S7">
          {a mathematical formula}φviolated=(violated→◯violated), which expresses that violations, once occurred, are recorded forever.
         </list-item>
        </list>
        <paragraph>
         The behavior of the resulting 2GS can be summarized as follows. The environment initially sets the agent planning program and the domain in their respective initial states, and nondeterministically picks a program transition to be realized (E1, E4–E8). At every step, the system can reply to the environment by either following a plan to realize the current transition, thus choosing a domain action whose precondition holds in the current domain state, or by announcing the end of the current plan, that is the realization of the transition, by setting special proposition last to true and selecting special action wait (S1–S5). In the former case, the environment replies by simply executing the action, thus progressing the domain to one of its possible successor states (given the current state and the action chosen by the system) and keeping the planning program in its current state, with same transition request (E3, E10, E11). If, instead, a transition realization is announced, i.e., the last action of the plan has been executed (proposition last), then the domain remains still (“waits”), while the agent planning program is progressed, according to the current transition requested, to the successor state, and a new transition, outgoing from the new state, is selected for realization (E2, E9). Notice that in order for the system to set last true, the achievement goal must be fulfilled (S5). Also, when selecting a domain action, the system may choose one that violates the maintenance goal of the requested program transition. In this case, as soon as the violation occurs, proposition violated becomes true and remains so forever (S6, S7). Finally, observe that proposition last can be set true by the system only if no violation has occurred (S5). As a result, the system can declare a transition realized only if the corresponding achievement goal has been actually achieved and its maintenance goal has not been violated.
        </paragraph>
        <paragraph>
         We note that because the system can always play wait when no domain action is executable, analogously to {a mathematical formula}ρe also the transition relation {a mathematical formula}ρs is serial—there is always a next available system move. This implies that the game successor relation ρ—built from {a mathematical formula}ρe and {a mathematical formula}ρs—is in turn serial, thus every game state has at least one successor.
        </paragraph>
        <paragraph>
         Once the 2GS is defined, we can use a weak-fairness formula to encode the synthesis goal. Formally, we have:{a mathematical formula} It can be seen that, as a consequence of the constraints implied by {a mathematical formula}φlast, {a mathematical formula}φmaint, and {a mathematical formula}φviolated, {a mathematical formula}φgoal is satisfied by a play if and only if the achievement goal of every request is eventually satisfied and no maintenance requirement is ever violated. Indeed, the current program transition is eventually realized if and only if last is eventually set to true. When this happens, a new transition request is issued, which requires last to eventually hold again, after which a new program transition will be requested, and so on and so forth.
        </paragraph>
        <paragraph>
         In Appendix A we present an actual encoding, obtained by following the construction above, of the nondeterministic variant of the example presented in Section 3.
        </paragraph>
        <paragraph>
         The following result shows correctness of the above construction, by linking the existence of a winning strategy for the system in the 2GS defined above with the existence of a realization of the agent planning program.
        </paragraph>
        <paragraph label="Proof">
         Soundness &amp; completenessThere exists a realization of an agent planning program{a mathematical formula}Pin a planning domain{a mathematical formula}Dfrom a state{a mathematical formula}s0if and only if, for the 2GS G and the winning condition{a mathematical formula}φgoaldefined above, there exists a strategy that is winning for the system.The proof consists in showing how from a strategy for the 2GS that is winning for the system, one can derive a realization for the agent planning program and, viceversa, how from a realization of the agent planning program, one can derive a winning strategy for the game. See Appendix B for full details.  □
        </paragraph>
        <paragraph>
         That is, computing a winning strategy for the synthesis problem defined by the 2GS and the winning condition above is equivalent to realizing the planning program {a mathematical formula}P in {a mathematical formula}D.
        </paragraph>
        <paragraph>
         Next we analyze the worst-case computational complexity of the problem. By Theorem 2, we have that a winning strategy for {a mathematical formula}φgoal in G can be computed in time {a mathematical formula}O(n(n+m)), with n the number of states in G and {a mathematical formula}m=|ρe|+|ρs|. Since {a mathematical formula}|ρe|,|ρs|≤n2, we get a polynomial bound {a mathematical formula}O(n3). However, {a mathematical formula}n≤2|V|, thus checking the existence of a solution (and actually constructing it) can be done in time {a mathematical formula}O(23|V|). Considering the definition of {a mathematical formula}ρe (conjuncts E6 and E9 of {a mathematical formula}transP) and {a mathematical formula}ρs, the number of states n is {a mathematical formula}O(2|P|⋅|δ|⋅|A|), as {a mathematical formula}|Xr|=|δ|. In other words, our technique is exponential in the number of domain propositions, while polynomial in the size of the planning program and number of domain actions.
        </paragraph>
        <paragraph label="Proof">
         Direct consequence of the discussion above.  □
        </paragraph>
        <paragraph>
         Interestingly, in spite of the additional sophistication of agent planning programs, the complexity of realizing them is essentially the same as that of conditional planning (with full observability). In other words, at least from the worst-case complexity point of view, realizing agent planning programs does not require any additional computational effort with respect to conditional planning.
        </paragraph>
        <paragraph>
         Finally, we observe that the kind of solution based on the above technique shares several commonalities with the notion of universal plan[92], in the sense that from every configuration (of planning program state and domain state) a way to fulfill the winning condition by winning the game is provided. Obviously, the class of winning conditions considered here is not reachability (of a state satisfying the goal, as for universal plans), but a more sophisticated one expressing the ability to reach infinitely often a state where last holds. It should be clear, however, that such a solution shares the same criticality of universal plans, including its practical cost (see also [48]).
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Planning programs in deterministic domains
     </section-title>
     <paragraph>
      In this section, we focus on the notable case in which the agent acts in a deterministic domain. A deterministic planning domain[46] is a special case of planning domain {a mathematical formula}D=〈P,A,τ〉, where the transition relation τ is a function {a mathematical formula}τ:2P×A↦2P. We call this case the “deterministic case” and for it we develop an alternative realization technique deeply rooted in the planning technology which consists of suitable calls to a classical planner, careful iterated till the entire planning program is realized. This iterative method is similar to the one implemented in planner NDP to solve non-deterministic planning problems [64], which constructs policies by iterative calls to a classical planner. However, we use some specific planning techniques that are not present in NDP. The kind of solution that our realization algorithm for deterministic domains devises has not the “universal plan” nature of the general procedure presented above, and empirically proves to be quite effective especially for agent planning programs over planning domains that have limited or no deadends in the search space, as shown later.
     </paragraph>
     <paragraph>
      Before going on, we characterize the computational complexity of the deterministic case. Obviously, the general EXPTIME technique shown above applies to the deterministic case as well so this gives us an EXPTIME upper-bound. However the reduction from conditional planning with full observability that we use for the lower bound only gives us a PSPACE-hardness lower-bound for deterministic domains. So the question is: is the problem EXPTIME-hard even in the deterministic case or does it admit a PSPACE algorithm?
     </paragraph>
     <paragraph label="Theorem 5">
      We answer this question by showing the EXPTIME-hardness also in the deterministic case. To do so we resort to a reduction from the composition problem of deterministic agent behaviors, which is known to be EXPTIME-complete [35], [76]. Checking whether an agent planning program is realizable in a deterministic planning domain is EXPTIME-complete.
     </paragraph>
     <paragraph label="Proof">
      It can be shown that composition of deterministic agent behaviors can be polynomially encoded into realization of agent planning programs. Details are in Appendix B.  □
     </paragraph>
     <paragraph>
      Next we detail the specific planning-based technique that we propose to handle the deterministic case.
     </paragraph>
     <section label="5.1">
      <section-title>
       Realizing planning programs for the deterministic case
      </section-title>
      <paragraph>
       In the rest of this section, for technical convenience, an action is represented as a triple {a mathematical formula}〈Pre,Eff+,Eff−〉 where Pre is a set of propositions representing the action preconditions, and {a mathematical formula}Eff+/− is a set of propositions representing the action positive/negative effects. Like in classical planning [46], under the closed world assumption, a state is specified by a set of propositions, an action {a mathematical formula}a=〈Pre,Eff+,Eff−〉 is said to be executable in a domain state s if {a mathematical formula}Pre⊆s, and the domain state {a mathematical formula}s′ obtained by executing a in state s is {a mathematical formula}s∖Eff−∪Eff+. The domain transition function τ is (implicitly) defined by the execution of the domain actions from all the possible domain states.
      </paragraph>
      <paragraph>
       Observe that, because in a deterministic planning domain the execution of an HT-plan produces only a single history, an HT-plan can be simply represented as a sequence π of actions: the corresponding HT-plan function can be obtained by associating each action a of π with the sequence of states obtained by executing, from the initial state of the domain, all the actions that precede a in π. Thus, since in this section we deal with deterministic domains only, for simplicity we represent HT-plans in this form.
      </paragraph>
      <paragraph>
       A state s of {a mathematical formula}D is said to be reachable from an initial state {a mathematical formula}s0 if there exists a plan π such that s is the final state obtained by executing π from {a mathematical formula}s0. In the following, for a domain {a mathematical formula}D, we use {a mathematical formula}S⊆2P to denote the set of all states of a domain that are reachable from an initial state {a mathematical formula}s0. Further, {a mathematical formula}π(s) denotes the sequence of states obtained by executing π from state s and {a mathematical formula}last(π(s)) denotes the final state of such sequence.
      </paragraph>
      <paragraph>
       We address the problem of effectively constructing planning program realizations for deterministic domains by exploiting plan generation techniques for planning problems with preferred end-states (shortly, PESs) and tabu end-states (TESs). A PES is a desired end state for a plan realizing a planning program transition, while a TES is a forbidden plan end state. As will be described, PESs and TESs are generated by the proposed iterative algorithm for realizing agent planning programs, and they are important to guarantee its correctness and efficiency.
      </paragraph>
      <paragraph label="Definition 5">
       A planning problem with PESs and TESs is a tuple {a mathematical formula}〈D,s0,ψ,ϕ,SP,ST〉 where {a mathematical formula}D=〈P,A,τ〉 is a deterministic planning domain, {a mathematical formula}s0 is the initial state, {a mathematical formula}ψ∈Φ(P) is a maintenance goal, {a mathematical formula}ϕ∈Φ(P) is an achievement goal; {a mathematical formula}SP⊆2P is a set of PESs; and, finally, {a mathematical formula}ST⊆2P is a set of TESs. □
      </paragraph>
      <paragraph>
       Given a planning problem {a mathematical formula}Π=〈D,s0,ψ,ϕ,SP,ST〉 with PESs and TESs, an executable plan π for {a mathematical formula}D, and state {a mathematical formula}s′=last(π(s0)), we say that π is valid for Π iff π maintains ψ, {a mathematical formula}s′⊨ϕ and {a mathematical formula}s′∉ST. Moreover, given two valid plans {a mathematical formula}π1 and {a mathematical formula}π2 for Π, we say that {a mathematical formula}π1 is preferred to {a mathematical formula}π2 iff {a mathematical formula}last(π1(s0))∈SP and {a mathematical formula}last(π2(s0))∉SP.
      </paragraph>
      <paragraph>
       Fig. 2 shows the pseudo-code of {a mathematical formula}RealizePlanProg, an algorithm for building planning program realizations. Starting from an open configuration (called open pair in the algorithm) {a mathematical formula}〈s,v〉, where s is a domain state and v is a planning program state (initially {a mathematical formula}s=s0 and {a mathematical formula}v=v0), for each transition d outgoing from v such that the guard of d holds in s, {a mathematical formula}RealizePlanProg constructs a plan π realizing d from s. Then, the algorithm progresses the states of {a mathematical formula}D and {a mathematical formula}P (according to {a mathematical formula}π(s) and d, respectively), possibly generating a new open pair {a mathematical formula}〈s′,v′〉 to process similarly. For each generated pair {a mathematical formula}〈s,v〉 and transition {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 such that {a mathematical formula}s⊨γ, function {a mathematical formula}Ω(s,d) associates with s a plan constructed to achieve ϕ from s while maintaining ψ. If the algorithm generates an open pair {a mathematical formula}〈s,v〉 such that for some transition outgoing from v no realizing plan can be computed from s, backtracking is required, i.e., the plans generating {a mathematical formula}〈s,v〉 need to be removed from Ω. The algorithm terminates when no more open pairs are left, or it is the case that no realization can be found, i.e., for at least a transition {a mathematical formula}d=〈v0,〈γ,ψ,ϕ〉,v〉 outgoing from the initial planning program state {a mathematical formula}v0, and such that γ holds in the initial domain state {a mathematical formula}s0, there exists no plan π constructed from {a mathematical formula}s0 such that π maintains ψ, {a mathematical formula}last(π(s0))⊨ϕ and {a mathematical formula}last(π(s0)) is in the set of domain states from which a transition outgoing from v can be realized.
      </paragraph>
      <paragraph>
       The specification of function Ω under construction implicitly defines the set of open pairs, also called the realization frontier, which is denoted in the algorithm as Open. This set is obtained by considering all possible planning program executions, starting from {a mathematical formula}〈s0,v0〉, using Ω to realize the transitions, and putting in the set all those pairs {a mathematical formula}〈s,v〉 such that for some transition d from v, the guard of d holds in s and {a mathematical formula}Ω(s,d) is currently undefined. Essentially, this corresponds to a straightforward visit of the planning program graph from {a mathematical formula}v0 and {a mathematical formula}s0 using the current (partially defined) Ω. The frontier of this visit is the set of pairs {a mathematical formula}〈s,v〉, of domain and planning program state, such that there is a transition d outgoing from v whose guard holds in s, but for which there is no plan achieving and maintaining the corresponding goal, i.e., {a mathematical formula}Ω(s,d) is undefined. Such a frontier is denoted by {a mathematical formula}Frontier(Ω,τ,s0,v0) and defines the open pairs for the current Ω stored in Open.
      </paragraph>
      <paragraph>
       For example, assume that the current specification of Ω is defined by the first two lines of Table 1. Then, the realization frontier is the set of open pairs{a mathematical formula} The former pair, for instance, is reached by executing the first plan in Table 1 that realizes transition {a mathematical formula}〈v0,〈∅,¬Fuel(empty),MyLoc(dept)〉,v1〉 from the initial state {a mathematical formula}s0={MyLoc(home), {a mathematical formula}CarLoc(home), {a mathematical formula}Fuel(full)}, and it is in the frontier because (a) the transition has no guard (hence, it needs to be realized) and (b) the current specification of Ω is still undefined for the domain state {a mathematical formula}{MyLoc(dept),CarLoc(lot),Fuel(low)} and transitions {a mathematical formula}〈v1,〈⊤,¬Fuel(empty),MyLoc(home)∧¬Fuel(empty)〉,v0〉 and {a mathematical formula}〈v1,〈⊤,¬Fuel(empty),MyLoc(pub)∧¬Fuel(empty)〉,v2〉.
      </paragraph>
      <paragraph>
       Algorithm {a mathematical formula}RealizePlanProg maintains three auxiliary functions {a mathematical formula}States:V→2S, {a mathematical formula}Tabu:V→2S and Source: {a mathematical formula}S×V→2S×δ. Intuitively, {a mathematical formula}States(v) records all domain states reached when {a mathematical formula}P is in v, for some {a mathematical formula}P execution, according to the current Ω; {a mathematical formula}Tabu(v) indicates the states of {a mathematical formula}D that are forbidden when v is reached; and Source associates each open pair {a mathematical formula}〈s′,v′〉 with those pairs {a mathematical formula}〈s,d〉 such that d is a program transition from v to {a mathematical formula}v′ and, for {a mathematical formula}π=Ω(s,d), {a mathematical formula}last(π(s))=s′. Essentially, function Source says how an open pair was generated by the current Ω.
      </paragraph>
      <paragraph>
       Initially (lines 1–4), Function Ω is completely undefined (through the special value noPlan), {a mathematical formula}States(v)=∅ for every {a mathematical formula}v≠v0, {a mathematical formula}States(v0)={s0}, {a mathematical formula}Tabu(v)=∅ for every v, and {a mathematical formula}Open=〈s0,v0〉. At each iteration of the external loop (lines 5–25), an arbitrary open pair {a mathematical formula}〈s,v〉 is extracted from Open and processed by:
      </paragraph>
      <list>
       <list-item>
        computing, for each transition {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 such that {a mathematical formula}s⊨γ and {a mathematical formula}Ω(s,d)=noPlan (i.e., d has not been processed for s yet), a plan π that maintains ψ, achieves ϕ from s with an acceptable end state, i.e., {a mathematical formula}last(π(s0))∉Tabu(v′) (lines 8–10);
       </list-item>
       <list-item>
        appropriately updating Ω, Open, and the auxiliary functions (lines 11–25).
       </list-item>
      </list>
      <paragraph>
       When Open becomes empty, the external loop terminates and the algorithm returns Ω (line 26).
      </paragraph>
      <paragraph>
       Task (i) is accomplished by executing function {a mathematical formula}Plan, which computes a plan for the planning problem with PESs and TESs {a mathematical formula}〈D,s,ψ,ϕ,States(v′),Tabu(v′)〉. Intuitively, the domain states in {a mathematical formula}States(v′) are used as preferred end states to minimize the number of generated open pairs, while the domain states in {a mathematical formula}Tabu(v′) are used as tabu end states to prevent next iterations from generating unrealizable open pairs. Details about how to achieve this behavior in {a mathematical formula}Plan are given in Section 5.2.
      </paragraph>
      <paragraph>
       For task (ii), assume that {a mathematical formula}〈s,v〉 is an open pair, and d is a program transition from program state v to program state {a mathematical formula}v′, whose guard holds in s. If a plan π realizing d from s is found, then the algorithm updates {a mathematical formula}Ω(s,d), {a mathematical formula}States(v′) and {a mathematical formula}Source(s′,v′) as follows: function Ω is updated by setting {a mathematical formula}Ω(s,d) to π; if {a mathematical formula}s′=last(π(s)) is not already in {a mathematical formula}States(v′), the set of open pairs is extended with {a mathematical formula}〈s′,v′〉; state {a mathematical formula}s′ is added to {a mathematical formula}States(v′); and {a mathematical formula}〈s,d〉 is added to {a mathematical formula}Source(s′,v′) (lines 13–17). If for some program transition d outgoing from v such that its guard holds in s, procedure {a mathematical formula}Plan is unable to find a plan achieving/maintaining the goals of d from s, then open pair {a mathematical formula}〈s,v〉 cannot be realized. In the special case {a mathematical formula}s=s0 and {a mathematical formula}v=v0, no realization of {a mathematical formula}P can be built, and hence {a mathematical formula}RealizePlanProg terminates returning failure (lines 18–19). Otherwise ({a mathematical formula}s≠s0 or {a mathematical formula}v≠v0), backtracking is performed on Ω (lines 21–25): s is added to {a mathematical formula}Tabu(v); s is removed from {a mathematical formula}States(v), as clearly no longer preferred; for all pairs {a mathematical formula}〈s″,v″〉∈Source(s,v), {a mathematical formula}Ω(s″,d″) is set undefined ({a mathematical formula}Ω(s″,d″) becomes noPlan), as the corresponding plans need to be recomputed in order to avoid generating the configuration {a mathematical formula}〈s,v〉; and, finally, {a mathematical formula}Frontier(Ω,τ,s0,v0) defines the new set of open pairs (Open).
      </paragraph>
      <paragraph>
       Interestingly, {a mathematical formula}RealizePlanProg is parametric with respect to the specific planning procedure used to implement {a mathematical formula}Plan, thus allowing us to generate different version of our algorithm based on different planning approaches and heuristics.
      </paragraph>
      <paragraph>
       The following results demonstrate the fundamental properties of {a mathematical formula}RealizePlanProg.
      </paragraph>
      <paragraph label="Lemma 1">
       Algorithm RealizePlanProg terminates provided that subroutine Plan terminates.
      </paragraph>
      <paragraph label="Theorem 6">
       SoundnessThe function computed by Algorithm RealizePlanProg is a realization of the input agent planning program{a mathematical formula}P, deterministic planning domain{a mathematical formula}Dand initial domain state{a mathematical formula}s0, provided that subroutine Plan is sound to solve planning problems with achievement and maintenance goals.
      </paragraph>
      <paragraph label="Theorem 7">
       CompletenessAssume that subroutine Plan is complete. Algorithm RealizePlanProg returns a realization of the input planning program{a mathematical formula}P, if it exists; otherwise it returns failure.
      </paragraph>
      <paragraph>
       Proofs for all three claims can be found in Appendix B.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Encoding preferred and tabu end-states into actions with costs
      </section-title>
      <paragraph>
       A planning problem with PESs and TESs can be expressed in pddl3 [43]. In particular, a TES s can be specified by an “at end” constraint (an additional goal formula constraining the goal state) imposing that the disjunction of the negation of the propositions that are true in s and the propositions that are false in s hold at the end of the plan. (Under the closed world assumption, a proposition p is true in s if {a mathematical formula}p∈s, while it is false in s if {a mathematical formula}p∉s, assuming s formalized as a set of propositions.) Similarly, a PES s can be specified by a preferred goal (also called soft goals) imposing that the conjunction of the propositions that are true in s and the negation of the propositions that are false in s preferably holds at the end of the plan.
      </paragraph>
      <paragraph>
       A planning problem with soft goals and constraints can be translated into a classical planning problem with action costs, that can be solved by classical planners supporting real-valued fluents [43]. Keyder and Geffner [62] show that classical planners can solve the problems obtained by their translation scheme for compiling soft goals away more quickly than what it takes to solve the original problems with soft goals.
      </paragraph>
      <paragraph>
       In this section, we propose a scheme to transform a problem with PESs and TESs into a problem with action costs, that is much simpler than the one proposed in [43], as it considers only a special case of the planning problem with soft goals and constraints studied in [43]. Concerning the compilation of PESs, our scheme also differs from the one by Keyder and Geffner both in its purpose and compilation technique. Our compilation is designed for the particular context in which it is used (realizing program transitions involved in a loop) and the type of soft goals that are relevant in this context (preferred end states). We do not propose a method that provides a general translating scheme for compiling soft goals away, as in [62]. Instead, our scheme constructs a planning problem {a mathematical formula}Π′ with action costs from a planning problem Π with PESs so that, if a planner finds a solution plan of {a mathematical formula}Π′ with the lowest cost, such a plan can be easily transformed into a solution plan of Π ending in one of the PESs of Π. Moreover, in our context any valid plan can satisfy at most one preference, and our scheme compiles also TESs, while the compilation scheme described in [62] handles only soft goals.
      </paragraph>
      <paragraph label="Definition 6">
       A planning problem with action costs is a tuple {a mathematical formula}〈D,s0,ψ,ϕ,c〉 where {a mathematical formula}D=〈P,A,τ〉 is a deterministic planning domain, {a mathematical formula}s0 is the initial state, {a mathematical formula}ψ∈Φ(P) is a maintenance goal, {a mathematical formula}ϕ∈Φ(P) is an achievement goal; and {a mathematical formula}c:A↦R is an action cost function. □
      </paragraph>
      <paragraph>
       A planning problem with PESs and TESs {a mathematical formula}Π=〈D,s0,γ,ψ,ϕ,SP,ST〉 where {a mathematical formula}D=〈P,A,τ〉 can be translated into a planning problem with action costs {a mathematical formula}Π′=〈D′,s0′,ψ,ϕ′,c〉 such that{sup:5}:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}D′=〈P′,A′,τ′〉;
       </list-item>
       <list-item label="•">
        {a mathematical formula}P′=P∪PM∪PT;
       </list-item>
       <list-item label="•">
        {a mathematical formula}A′=A+∪AP∪AT;
       </list-item>
       <list-item label="•">
        {a mathematical formula}τ′ is implicitly defined by the preconditions/effects of the actions in {a mathematical formula}A′;
       </list-item>
       <list-item label="•">
        {a mathematical formula}s0′=s0∪{normal-mode};
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ′=ϕ∧check-pref∧⋀pt∈PTpt;
       </list-item>
       <list-item label="•">
        {a mathematical formula}c(o)={1if o=Ignore-pref,0otherwise;
       </list-item>
      </list>
      <paragraph>
       where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}PM={normal-mode,end-mode,check-pref};
       </list-item>
       <list-item label="•">
        {a mathematical formula}PT={not-tabu(s)|s∈ST};
       </list-item>
       <list-item label="•">
        {a mathematical formula}A+={〈Pre∪{normal-mode},Eff+,Eff−〉|〈Pre,Eff+,Eff−〉∈A};
       </list-item>
       <list-item label="•">
        {a mathematical formula}AP=Ignore-pref∪{Sat-pref(s)|s∈SP}, where {a mathematical formula}Ignore-pref is the action {a mathematical formula}〈{normal-mode}, {a mathematical formula}{end-mode,check-pref},{normal-mode}〉 and {a mathematical formula}Sat-pref(s) is the same as {a mathematical formula}Ignore-pref but with the additional set of preconditions {a mathematical formula}{p|p∈s}∪{¬p|p∈P∧p∉s};
       </list-item>
       <list-item label="•">
        {a mathematical formula}AT={a|a∈Act-tabu(s)∧s∈ST}, where {a mathematical formula}Act-tabu(s) is the set of actions {a mathematical formula}{〈{end-mode,¬p},{not-tabu(s)},∅〉|p∈P∧p∈s}∪{〈{end-mode,p},{not-tabu(s)},∅〉|p∈P∧p∉s}.
       </list-item>
      </list>
      <paragraph>
       It is easy to see that the structure of any plan for the translated problem is {a mathematical formula}〈πA+,a,πT〉, {a mathematical formula}πA+ and {a mathematical formula}πT are two (possibly empty) sub-plans of actions in {a mathematical formula}A+ and {a mathematical formula}AT, respectively, and {a mathematical formula}a∈AP. The (possible) presence of action {a mathematical formula}Sat-pref(s), for some s in the plan, indicates that {a mathematical formula}last(πA+) is the preferred domain state s. The (required) presence of an action of {a mathematical formula}Act-tabu(s) in {a mathematical formula}πT, for some tabu state s, indicate that the end state generated by subplan {a mathematical formula}πA+ is different from {a mathematical formula}s∈ST. Note that since the conjunction goal formula {a mathematical formula}ϕ′ contains a conjunct {a mathematical formula}not-tabu(s) for each tabu state {a mathematical formula}s∈ST, subplan {a mathematical formula}πT must contain an action of {a mathematical formula}AT for each {a mathematical formula}s∈ST.
      </paragraph>
      <paragraph>
       The cost of a plan π is the sum of the cost of the actions executed in π. Since there can be at most one occurrence of action {a mathematical formula}Ignore-pref in any valid plan, by definition of cost function c, the cost of every valid plan is either 0 or 1. The plans with cost equal to 0 are the best plans.
      </paragraph>
      <paragraph label="Theorem 8">
       Plan validity and equivalenceLet Π be a solvable planning problem with PESs and TESs, and{a mathematical formula}Π′a planning problem with action costs derived from Π by the translating scheme defined above. Then, (1) there exists a valid plan{a mathematical formula}π′for{a mathematical formula}Π′; and (2) for every plan{a mathematical formula}π′solving{a mathematical formula}Π′, the plan obtained by removing the actions in{a mathematical formula}AT∪APfrom{a mathematical formula}π′and precondition{a mathematical formula}normal-modefrom every action in{a mathematical formula}π′is a valid plan for Π.
      </paragraph>
      <paragraph label="Proof">
       See Appendix B.  □
      </paragraph>
      <paragraph label="Proof">
       Plan preferenceLet Π be a planning problem with PESs and TESs that has a solution plan ending in a PES, and{a mathematical formula}Π′a planning problem with action costs obtained from Π by our translating scheme presented above. Then, (1) there exists a plan{a mathematical formula}π′solving{a mathematical formula}Π′such that{a mathematical formula}c(π′)=0, and (2) for every plan{a mathematical formula}π′solving{a mathematical formula}Π′such that{a mathematical formula}c(π′)=0, the plan obtained by removing the actions in{a mathematical formula}AT∪APfrom{a mathematical formula}π′and precondition{a mathematical formula}normal-modefrom every action in{a mathematical formula}π′is a valid plan solving Π and ending in a PES of Π.See Appendix B.  □
      </paragraph>
      <paragraph>
       Finally, note that there is a difference between the classical definition of planning problems with action costs and ours. In our context, the achievement goal is an arbitrary boolean formula, instead of a conjunction of atomic propositions, and our definition also includes the maintenance goal. Maintenance goals can be compiled away as described in the next section. The formula representing the problem achievement goal can be compiled away into action preconditions (the goal formula of the compiled problem is a conjunction of propositions) [63]. Specifically, first the goal formula is transformed into a DNF formula. Then, for every disjunct δ of the (DNF) achievement goal formula, the set of actions is augmented by an action with a dummy effect and the set of conjuncts of δ as the precondition set of the action. The dummy effect is a conjunct of the new problem goal formula and the original goal formula is removed.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Encoding maintenance goals into action preconditions
      </section-title>
      <paragraph>
       It is known that planning problems with maintenance goals can be translated into propositional planning problems [6], [19], [40], [43]. A very simple translation for the planning problem associated with a program transition having a maintenance goal consists in adding the maintenance goal formula of the transition to the precondition formula of every domain action. The negative side of such a translation is that many planners transform the precondition and goal formulas into disjunctive normal form before planning, and thus the transformation of the formulas obtained by ruling out maintenance goals may blow up. Investigating efficient encodings of maintenance goals is out of the scope of this paper. For our experimental analysis, we considered only planning programs with goal formulas stated as conjunctions, which can be normalized without a blowup of the resulting compiled problem.
      </paragraph>
      <paragraph>
       It is important to note that the end {a mathematical formula}D-state {a mathematical formula}last(π) of any plan π realizing an incoming transition of a {a mathematical formula}P-state v is the initial {a mathematical formula}D-state of any plan realizing a transition outgoing from v. If the computation of π ignored the interdependency between π and the plans realizing the outgoing transitions of v, it could happen that the maintenance goal formula of an outgoing transition is not satisfied in {a mathematical formula}last(π). In this case, the planning problem derived to realize such an outgoing transition would be unsolvable, and therefore algorithm {a mathematical formula}RealizePlanProg would backtrack. In order to reduce the amount of these backtracks the original achieving goals of the program transitions incoming to a {a mathematical formula}P-state v can be augmented as follows. Let {a mathematical formula}{〈v,〈γi,ψi,ϕi〉,vi〉|1≤i≤m} be the set of outgoing transitions of v, where {a mathematical formula}γi, {a mathematical formula}ψi and {a mathematical formula}ϕi are the guard, maintenance goal, and achieving goal formula, respectively. Every incoming transition {a mathematical formula}〈v′,〈γ,ψ,ϕ〉,v〉 of v is changed to{a mathematical formula} As we will see in Section 6.4, indeed such a transformation can reduce significantly the amount of backtracking of {a mathematical formula}RealizePlanProg, and hence considerably improve the performance of {a mathematical formula}RealizePlanProg.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Enhancing the program realization by plan adaptation
      </section-title>
      <paragraph>
       Planning programs may represent routines that include cycles to carry on in the domain. In this case, computing the realization requires to reach at least one goal situation more than once. Assume that at the i-th iteration of the loop 5–25 of {a mathematical formula}RealizePlanProg a transition is processed by invoking subroutine {a mathematical formula}Plan with problem {a mathematical formula}Πi, and, subsequently, at the j-th iteration ({a mathematical formula}j&gt;i) such a transition is processed again by invoking {a mathematical formula}Plan with problem {a mathematical formula}Πj. In order to solve {a mathematical formula}Πj, subroutine {a mathematical formula}Plan could re-use and modify the plan previously computed for {a mathematical formula}Πi, instead of planning from scratch.
      </paragraph>
      <paragraph>
       From a theoretical point of view, in the worst case, adapting an existing plan is not more efficient than a complete regeneration of the plan from scratch [77]. However, in practice, plan adaptation can be much more efficient than generating, when few changes of the existing plan are necessary to adapt it. In the context of the planning program realization, the achievement and maintenance goals of problems {a mathematical formula}Πi and {a mathematical formula}Πj are the same (i.e., the achievement and maintenance goal formulas associated with the transition processed both at the i-th and j-th iteration), and hence adapting the plan previously computed for {a mathematical formula}Πi can be extremely promising when solving {a mathematical formula}Πj.
      </paragraph>
      <paragraph>
       In principle, a transition in a cycle can be processed by {a mathematical formula}RealizePlanProg more than twice, and hence the number of previously computed plans that can be re-used for realizing such a transition may be greater than one. Assume that transition {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 has been already realized {a mathematical formula}n&gt;1 times. Let {a mathematical formula}Πk be the planning problem associated to the k-th realization of d with initial state {a mathematical formula}sk ({a mathematical formula}k∈{1,…,n}), and {a mathematical formula}πk the solution plan computed for {a mathematical formula}Πk so that {a mathematical formula}Ω(sk,d)=πk. Suppose now that, at the current iteration of loop 5–25 of {a mathematical formula}RealizePlanProg, transition d is processed again with an open pair {a mathematical formula}〈s′,v〉 and planning problem {a mathematical formula}Π′. The differences between every {a mathematical formula}Πk and {a mathematical formula}Π′ concern their initial states and sets of PESs and TESs. However, for {a mathematical formula}k=1…n, {a mathematical formula}last(πk) is still in {a mathematical formula}States(v′), and hence it is a PES of {a mathematical formula}Π′. (If {a mathematical formula}last(πk) were not in {a mathematical formula}States(v′), then {a mathematical formula}Ω(sk,d) would not be {a mathematical formula}πk.) In this case, a plan {a mathematical formula}π′ solving {a mathematical formula}Π′ may be constructed as a sequence of two subplans: a subplan reaching {a mathematical formula}sk from {a mathematical formula}s′ (if exists), followed by {a mathematical formula}πk for some {a mathematical formula}k∈{1,…,n}. The expected cost required to adapt plan {a mathematical formula}πk to solve {a mathematical formula}Π′ can be estimated as the number of actions in the relaxed plan constructed to achieve states {a mathematical formula}sk from {a mathematical formula}s′[45], [57]. The plan is relaxed, as it is constructed by ignoring the domain actions' negative effects.
      </paragraph>
      <paragraph>
       Fig. 3 shows an algorithm, called {a mathematical formula}BestPlan, for selecting the best plan to re-use for a doman state s and a transition d from v to {a mathematical formula}v′ involved in a cycle. For each state {a mathematical formula}sv in {a mathematical formula}States(v) such that a plan π realizing d from {a mathematical formula}sv has been already computed, {a mathematical formula}BestPlan generates a relaxed plan {a mathematical formula}πR to reach {a mathematical formula}sv from s (lines 2–4); and, finally, {a mathematical formula}BestPlan returns the plan with the expected lowest adaptation cost (lines 5–8). The selected best plan can then be re-used by algorithm {a mathematical formula}RealizePlanProg invoking a different version of subroutine {a mathematical formula}Plan, that we call {a mathematical formula}AdaptPlan, with additional input the plan {a mathematical formula}πbest returned by {a mathematical formula}BestPlan(s,d). If {a mathematical formula}πbest is equal to ∅, {a mathematical formula}AdaptPlan plans from scratch; otherwise, it adapts {a mathematical formula}πbest to a valid plan that realizes transition d from domain state s with a preferred end state in {a mathematical formula}States(v′).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      We present here the results of an experimental study with the following main goals:
     </paragraph>
     <list>
      <list-item label="•">
       analyzing the effectiveness and the efficiency of our approach to realizing agent planning programs in deterministic domains;
      </list-item>
      <list-item label="•">
       evaluating the usefulness of PESs for the performance of {a mathematical formula}RealizePlanProg;
      </list-item>
      <list-item label="•">
       evaluating the performance of {a mathematical formula}RealizePlanProg using different incorporated planners that support pddl3 preferences for representing PESs, or that can solve the planning problem with action costs obtained by compiling them away;
      </list-item>
      <list-item label="•">
       evaluating our compilation of maintenance goals in the planning problems, and the usefulness of using plan adaptation techniques for realizing the planning program transitions.
      </list-item>
     </list>
     <paragraph>
      In this experimental study, we focus on achievement and maintenance goals that are conjunctive. Moreover, we set all the transition guards to true. Note that realizing planning programs with all guards set to true does not represent a simplification in experimenting our algorithm, since it forces the algorithm to realize all outgoing transitions, even those that guards would rule out. In other words, by considering only planning programs without guards in our experiments, we are not restricting the analysis to planning programs that are computationally easier (than those with guards) to solve for our technique.
     </paragraph>
     <section label="6.1">
      <section-title>
       Experimental settings
      </section-title>
      <paragraph>
       Algorithm {a mathematical formula}RealizePlanProg has been tested using three well-known incorporated planners: Hplan-P[6], {a mathematical formula}LAMA[89], and {a mathematical formula}LPG[45]. In the following, before describing the used benchmark domains and problems, we give a very brief description of each of them. More detailed information is available from the relative referred papers. In the rest of the paper, notation {a mathematical formula}RealizePlanProg[x] denotes {a mathematical formula}RealizePlanProg incorporating planner x.
      </paragraph>
      <paragraph>
       Hplan-P[6] is a heuristic search planner built on top of the TLPlan system [3]. Hplan-P handles pddl3 constraints and preferences by transforming these into parameterized finite state automata. Essentially, it uses an incremental best-first search planning algorithm, guided by a prioritized sequence of heuristics, which combines estimates of the cost of reaching the goals, the cost of satisfying preferences, and different estimates of the final plan metric value. With {a mathematical formula}RealizePlanProg[Hplan-P], a planning problem with PESs and TESs is encoded into a pddl3 problem as described at the beginning of section 5.2, except that the disjunction representing the TESs is part of the Hplan-P's problem goal formula instead of a PDDL3 at end constraint.
      </paragraph>
      <paragraph>
       {a mathematical formula}LAMA[89] translates the pddl problem specification into the multi-valued state variable representation “SAS+” [4] and searches for a plan in the space of the world states using a heuristic derived from the causal graph[53], a particular graph representing the causal dependencies of SAS+ variables. Its core feature is the use of a pseudo-heuristic derived from landmarks, propositions that for every solution of a planning task must be true in some state reached by the solution. Moreover, a weighted {a mathematical formula}A⋆ search is used with iteratively decreasing weights, so that the planner continues to search for plans of better quality. While {a mathematical formula}LAMA does not support reasoning over pddl3 preferences and constraints, it supports planning with action costs through the usage of real-valued fluents. With {a mathematical formula}RealizePlanProg[LAMA], planning problems with PESs and TESs are encoded by using the translation scheme described in Section 5.2, plus the real-valued fluent “cost”: the initial state of each problem assigns value zero to cost; the problem metric function requires to minimize the value of cost; and, finally, each action of the translated problem with cost equal to 1 is encoded with the additional pddl effect “(increase (cost) 1)” increasing the value of fluent cost by 1 unit.
      </paragraph>
      <paragraph>
       LPG[45] is based on a stochastic local search procedure that explores a space of partial plans represented through linear action graphs (shortly, LA-graphs) [45], which are variants of the very well-known planning graph [12]. The search steps are certain graph modifications transforming a LA-graph into another one. LPG's search algorithm selects the successor LA-graph according to a heuristic evaluation function and a “noise parameter”. The heuristic function estimates the number of additional search steps required to find a solution from the graphs obtained by applying the possible modifications. The noise parameter introduces some randomization in the choice of the successor, which is useful to escape from search states corresponding to local minima. When a solution is found, the LA-graph is modified by applying some graph modifications that improve the quality of the represented plan according to the problem plan metric, and the search is restarted to reach a new solution from the resulting LA-graph. LPG is the only planner considered in our experimental analysis that supports plan adaptation, as its initial search state can be either an empty LA-graph (in planning from scratch) or the LA-graph representing an input plan (in plan adaptation). The encoding of PESs and TESs used with {a mathematical formula}RealizePlanProg[LPG] is the same as in {a mathematical formula}RealizePlanProg[LAMA].
      </paragraph>
      <paragraph>
       In our experimental analysis, we have also considered the realization of planning programs using NuGaT, an optimized game solver built on top of NuSMV[21], as a baseline for evaluating the performance of {a mathematical formula}RealizePlanProg. It should be clear that since NuGaT is a solver more general than {a mathematical formula}RealizePlanProg, it is expected that it performs worse than our proposed approach for deterministic domains. Nevertheless, we believe it is a useful baseline for evaluating the performance of {a mathematical formula}RealizePlanProg.
      </paragraph>
      <paragraph>
       In the experiments, planning programs are constructed over 8 benchmark domains and with 6 different program structures defined by the planning program transition relation δ. Seven of the chosen domains were also used in past international planning competitions (IPCs) [2], [43], [54], [56], [59], [70], [71]. They are: Logistics (IPC-1), Blocksworld (IPC-2 typed version), Zenotravel (IPC-3 typed STRIPS version), Pipesworld (IPC-4 propositional “no-tankage” version), Storage (IPC-5 propositional version), Elevators (IPC-6 sequential satisficing version without real-valued fluents), and Barman (IPC-7 sequential satisficing track version without real-valued fluents). All these planning domains have no deadend in their state space. To study the behavior of our approach for planning domains with deadends, we also designed and used an additional “directed” version of Logistics that will be described when we present the results of this experiment. The considered planning program structures are: a single cycle with only achievement goals (shortly, 1C), a single cycle with both achievement and maintenance goals (shortly, 1C+M), multiple binary cycles in sequence (MC), a random sparse directed graph (RS), and a complete directed graph (CG). Moreover, we consider a variant of 1C with one cycle and one external node connected to the cycle by a single edge (shortly 1E1C). More formally, these structures are defined as follows.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}1C[n]: {a mathematical formula}δ={〈vi,Gi,v((imodn)+1)〉|vi∈V,1≤i≤n};
       </list-item>
       <list-item label="•">
        {a mathematical formula}1E1C[n]: {a mathematical formula}δ=〈v1,G1,v2〉∪{〈vi+1,Gi,v((imod(n−1))+2)〉|vi∈V,1≤i&lt;n};
       </list-item>
       <list-item label="•">
        {a mathematical formula}1C+M[n]: {a mathematical formula}δ={〈vi,〈Gi,Mi〉,v(imodn)+1)〉|vi∈V,1≤i≤n};
       </list-item>
       <list-item label="•">
        {a mathematical formula}MC[n]: {a mathematical formula}δ={〈vi,Gi,vi+1〉,〈vi+1,Gi+n−1,vi〉|vi∈V,1≤i&lt;n};
       </list-item>
       <list-item label="•">
        {a mathematical formula}RS[n]:{a mathematical formula}δ={〈vi,Gi,wi〉|(vi,wi)∈ERand,1≤i≤|ERand|=⌈n⋅log2n⌉};
       </list-item>
       <list-item label="•">
        {a mathematical formula}CG[n]: {a mathematical formula}δ={〈vi,Gi⋅n+j,vj〉,〈vj,Gj⋅n+i,vi〉|vi,vj∈V,1≤i≤n,1≤j≤n,i≠j};
       </list-item>
      </list>
      <paragraph>
       where V is the set of program states, {a mathematical formula}n=|V|, {a mathematical formula}ERand is a set of {a mathematical formula}⌈n⋅log2⁡n⌉ randomly selected pairs of program states, {a mathematical formula}Mi denotes the i-th set of maintenance goals, and {a mathematical formula}Gx denotes the x-th set of (randomly generated) achievement goals. Unless differently specified, the sets of achievement goals were obtained by using the existing problem generators. Maintenance goals were hand coded because there exists no automatic generator for them, and developing a tool to generate them which guarantees that the obtained problems are solvable is not trivial. Overall, we constructed 1223 planning programs with a randomly generated initial state and {a mathematical formula}|δ| problem goal sets. Specifically, we constructed the following five benchmarks:
      </paragraph>
      <list>
       <list-item>
        For Blocksworld, 80 planning programs with the domain size ranging from small to middle-size (the domain involves from 2 to 21 blocks) and program transition relation yielding structures 1C[6], MC[4], RS[4], and CG[3] ({a mathematical formula}|δ|=6);
       </list-item>
       <list-item>
        For each considered domain, 80 planning programs with the domain size ranging from small to middle-size (the domain involves from 3 to 30 objects) and program transition relation yielding structures 1C[50], MC[26], RS[14], and CG[8] ({a mathematical formula}|δ|≈50);
       </list-item>
       <list-item>
        For domains Logistics and Storage, 40 planning programs obtained by the programs of benchmark {a mathematical formula}SM50 by adding maintenance goals to the program transitions;
       </list-item>
       <list-item>
        For domains Blocksworld and Zenotravel, 33 planning programs with the domain size ranging from middle-size to large (the domain involves from 40 to 76 objects) and program transition relation yielding structures CG[2-4] ({a mathematical formula}|δ| ranges from 2 to 12);
       </list-item>
       <list-item>
        For each considered domain, 67 planning programs with the same small domain size (the number of domain objects ranges from 2 to 18) and program transition relation yielding structures 1C[5-100], MC[4-51], RS[3-23], and CG[3-11] ({a mathematical formula}|δ| ranges from about 5 to 100).
       </list-item>
      </list>
      <paragraph>
       The considered evaluation criteria are the CPU time used to realize the planning program and the program realization size (number of generated plans in the computed realization). The latter measures the quality of the realization: the lower the program realization size is, the simpler and, we believe, more desirable the realization is. An alternative criterion for measuring the realization quality can be the amount of resources used or produced by the plans forming the program realization (e.g., fuel, money, time, space, etc.). However, in the analysis we did not consider this, since the paper is focused on planning programs where the domain states are sets of propositions, which are unsuitable to effectively encode amounts of resources.
      </paragraph>
      <paragraph>
       The tests were conducted on an Intel Xeon(tm) 3 GHz machine, with 2 Gbytes of RAM. Unless otherwise indicated, the CPU-time limit used by {a mathematical formula}RealizePlanProg to realize planning programs was 1000 seconds. The termination of the incorporated planner was forced after 60 seconds or when two different solution plans (with increasing quality) were computed. Note that in this latter case, the second plan necessarily achieves a PES. Moreover, the second plan computed by every planner incorporated into {a mathematical formula}RealizePlanProg is an optimal solution (in terms of satisfied PESs). This is because (i) Hplan-P maximizes the number of achieved PESs and at most one PES can be reached; (ii) {a mathematical formula}LAMA and {a mathematical formula}LPG minimize the total cost of the plan solving the problem obtained by compiling PESs and TESs away, and, by construction of the compiled problems, at most one action with positive cost can be executed in a valid plan (the cost of every other action is equal to zero).
      </paragraph>
     </section>
     <section label="6.2">
      Performance of {a mathematical formula}RealizePlanProg with different planners
      <paragraph>
       In this section, we experimentally evaluate the performance of {a mathematical formula}RealizePlanProg with planners Hplan-P, {a mathematical formula}LAMA and {a mathematical formula}LPG using benchmarks {a mathematical formula}SM6, {a mathematical formula}SM50 and {a mathematical formula}S5−100.
      </paragraph>
      <paragraph>
       Fig. 4 shows the CPU time of {a mathematical formula}RealizePlanProg and NuGaT (our baseline) for domain Blocksworld in benchmark {a mathematical formula}SM6. As expected, the gap between the performance of {a mathematical formula}RealizePlanProg using any incorporated planner and NuGaT is huge, since NuGaT can realize Blocksworld planning program with only very few blocks within the CPU-time threshold. We think that the (not surprising) poor performance of NuGaT is merely due to the lack of heuristic-based search techniques (for plan construction) in this general purpose reasoning system.
      </paragraph>
      <paragraph>
       Moreover, the results in Fig. 4 indicate that {a mathematical formula}RealizePlanProg using either {a mathematical formula}LAMA or {a mathematical formula}LPG realizes all the planning programs, while using Hplan-P it realizes only the planning programs with small domain instances. For these planning programs, the CPU times of {a mathematical formula}RealizePlanProg using {a mathematical formula}LPG, {a mathematical formula}LAMA and Hplan-P are similar, but for planning programs with larger domain instances (number of blocks) the use of {a mathematical formula}LPG or {a mathematical formula}LAMA makes realizing the programs at least 1–2 orders of magnitude faster.
      </paragraph>
      <paragraph>
       Fig. 5 shows the program realization size of {a mathematical formula}RealizePlanProg for {a mathematical formula}SM6. The size of the program realization computed by {a mathematical formula}RealizePlanProg using {a mathematical formula}LAMA is always the best; the program realization size of {a mathematical formula}RealizePlanProg[LPG] is slightly larger than or equal to {a mathematical formula}RealizePlanProg[LAMA]; finally, for the planning programs with small domain instances, the program realization size of {a mathematical formula}RealizePlanProg[Hplan-P] and of {a mathematical formula}RealizePlanProg using either {a mathematical formula}LAMA or {a mathematical formula}LPG are the same, but for the other planning programs {a mathematical formula}RealizePlanProg[Hplan-P] computes much larger realizations.
      </paragraph>
      <paragraph>
       The results in Fig. 5 indicate that, for large planning domain instances, the plans computed by Hplan-P do not usually achieve PESs. Fig. 4, Fig. 5 also show that the larger the program realization is, the slower {a mathematical formula}RealizePlanProg is. This is because for the considered planning programs the number of open pairs generated by {a mathematical formula}RealizePlanProg is usually similar to the program realization size, and the incorporated planner is run at least once for every open pair.
      </paragraph>
      <paragraph>
       For domains different from Blocksworld and program transition relations larger than those in {a mathematical formula}SM6, we obtained similar results. Appendix A shows the performance of {a mathematical formula}RealizePlanProg for domains Logistics and Pipesworld with benchmark {a mathematical formula}SM50. The appendix gives no result for NuGaT, because it realizes no planning program of this benchmark.
      </paragraph>
      <paragraph>
       Fig. 6, Fig. 7 compare the CPU time and the program realization size of {a mathematical formula}RealizePlanProg using Hplan-P, {a mathematical formula}LAMA and {a mathematical formula}LPG for domain Zenotravel with benchmark {a mathematical formula}S5−100. For all planning programs of {a mathematical formula}S5−100 with domain Zenotravel, the number of involved domain objects is the same and equal to 11. These results indicate that for program structures 1C, MC, and RS, both the CPU time and the program realization size grow roughly linearly w.r.t. the number of program states; for structure CG, they grow quadratically. Therefore, for the experimented program structures, the performance grows linearly w.r.t. the size of the program transition relation. We experimentally observed that for planning programs with domain Zenotravel, the average total number of open pairs generated by every considered incorporated planners is: about {a mathematical formula}1⋅|δ| if the planning-program structure is 1C; about {a mathematical formula}1.5⋅|δ| if the planning-program structure is MC; about {a mathematical formula}2⋅|δ| if the planning-program structure is RS; and, finally, about {a mathematical formula}2.5⋅|δ| if the planning-program structure is CG.
      </paragraph>
      <paragraph>
       Appendix B shows the results of this analysis for two other domains of benchmark {a mathematical formula}S5−100: Elevators and Storage. The results are similar, except for Hplan-P, which fails to realize many planning programs. The rationale for this behavior is that, with domains Elevators and Storage, even for domain instances involving few objects, the size of the domain state can be large, and consequently achieving PESs can be very hard.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Importance of using preferred end states
      </section-title>
      <paragraph>
       In order to evaluate the impact of using PESs on the performance of {a mathematical formula}RealizePlanProg, we compared {a mathematical formula}RealizePlanProg using PESs and ignoring them. Table 2 gives the number of realized planning programs and the average CPU time for the planning programs of benchmark {a mathematical formula}SM50. The average CPU time is computed using the CPU-time limit (1000 seconds) for the planning programs that {a mathematical formula}RealizePlanProg does not realize (within the CPU time limit); the average realization size is computed over the planning programs that {a mathematical formula}RealizePlanProg can solve both with and without using PESs.
      </paragraph>
      <paragraph>
       The results in Table 2 show that planning with PESs has a high positive impact on the number of realized planning programs and the average speed of {a mathematical formula}RealizePlanProg. Using either {a mathematical formula}LAMA or {a mathematical formula}LPG, planning with PESs always allows {a mathematical formula}RealizePlanProg to realize a larger set of planning programs, and makes it (on average) faster than when planning without PESs. Interestingly, very often the algorithm realizes at least two times more planning programs, or is at least one order of magnitude faster (see gray boxes in Table 2). The performance gap is very large especially for planning programs with structures involving several cycles. Concerning {a mathematical formula}RealizePlanProg[Hplan-P], planning with PESs often gives better performance than planning without them, but in some cases we observed a performance decrease. This happened for domain Barman and δ equal to MC[26], RS[14], or CG[8], domain Elevators and δ equal to MC[26], and domain Storage and δ equal to RS[14], or CG[8]. In these cases, Hplan-P often crashes when it attempts to solve planning problems with many preferences or with preferences involving many propositions.
      </paragraph>
      <paragraph>
       Table 3 analyzes the program realization size (i.e., the total number of plans in the computed program realization) for the planning programs of benchmark {a mathematical formula}SM50. The results in this table indicate that planning with PESs is useful also in terms of the realization size. For any considered incorporated planner, exploiting planning with PESs allows {a mathematical formula}RealizePlanProg to compute program realizations that are always smaller, and often at least two times smaller (see gray boxes in Table 3). Specifically, for every considered program structure involving several cycles, the performance gap obtained by planning with/out PESs is almost always very large, except in domain Barman if the realization algorithm uses planners Hplan-P or {a mathematical formula}LAMA. Using {a mathematical formula}LPG, sometimes PESs are useful even when the program structure forms a single cycle. We think that in {a mathematical formula}RealizePlanProg[LPG] PESs are very useful because of the randomization in the local search procedure of {a mathematical formula}LPG: in {a mathematical formula}LPG the choice of the actions for the plan under construction is randomized, and this can lead to generate different plans for the same problem goals, resulting in different plan end states; however, using PESs in {a mathematical formula}LPG guides the search towards the same end states (the preferred ones), ameliorating the diversification determined by the randomization.
      </paragraph>
      <paragraph>
       The data in Table 4 describes the behavior of {a mathematical formula}RealizePlanProg in terms of: the maximum size of the sets {a mathematical formula}SP of PESs and {a mathematical formula}ST of TESs generated for a {a mathematical formula}P-state, and the maximum number of actions in sets {a mathematical formula}AP and {a mathematical formula}AT for benchmark {a mathematical formula}SM50 ({a mathematical formula}AP for Hplan-P in not considered in the table, because with Hplan-P PESs are encoded as PDDL3 preferences). Sets {a mathematical formula}AP and {a mathematical formula}AT, defined in Section 5.2, are used for translating a planning problem with PESs and TESs into a planning problem with action costs; they have size {a mathematical formula}|SP|+1 and {a mathematical formula}|ST|⋅|P|, respectively, where {a mathematical formula}|P| is the set of problem fluents. While in principle the size of these sets can be exponential in the number of problem objects, the results in the table show that this is not the case for benchmark {a mathematical formula}SM50.
      </paragraph>
      <paragraph>
       As for sets {a mathematical formula}ST and {a mathematical formula}AT, since the planning programs of benchmark {a mathematical formula}SM50 have planning domains with no deadend, the program transitions are, in principle, realizable from any (reachable) {a mathematical formula}D-state, and so the sizes of {a mathematical formula}ST and {a mathematical formula}AT can be 0. On the contrary, Table 4 shows that often this is not the case: when using Hplan-P some states are added to {a mathematical formula}ST and {a mathematical formula}AT for every considered domains, and when using {a mathematical formula}LAMA these sets have size greater than zero for domain Storage. This happens because sometimes Hplan-P and {a mathematical formula}LAMA fail to solve (solvable) planning problems within the given CPU-time limit and amount of memory (each failure generates a tabu state).
      </paragraph>
      <paragraph>
       It is worth noting that for planning program structures including loops, even when sets {a mathematical formula}ST and {a mathematical formula}AT are empty, the planning problems with PESs that are solved during the execution of {a mathematical formula}RealizePlanProg are interdependent in the sense that the solution of a planning problem associated with a transition incoming to a {a mathematical formula}P-state v takes into account the solution of the planning problems associated with the transition(s) outgoing from v, as it should (preferably) enable the reuse of the plans already computed for the outgoing transitions (this is the purpose of PESs). The number of not interdependent planning problems is always (at most) the number of program states, i.e., the number of planning problems with an empty set of PESs that are constructed during the execution of {a mathematical formula}RealizePlanProg. Therefore, the average number of solved interdependent planning problems can be derived by subtracting the number of program states from the data in Table 3. For instance, with δ equal to CG[8], the number of program states is 8. For such δ and domain Barman, the average size of the planning program realization generated using {a mathematical formula}LPG and preferred end states is about 252, and hence the number of generated interdependent planning problems is, on average, (at least) {a mathematical formula}252−8=244. The results in Table 3 show that, except for programs with δ equal to 1C[50], most of the planning problems solved by {a mathematical formula}RealizePlanProg are interdependent.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Planning programs with maintenance goals
      </section-title>
      <paragraph>
       The experimental analysis presented so far uses benchmarks formed by planning programs with only achievement goals. In this section, we also consider maintenance goals using benchmark {a mathematical formula}SM+M50, i.e., planning programs with δ equal to 1C+M[50] and domains Logistics and Storage. For Logistics, we designed program transitions with maintenance goals constraining all airplanes but one to stay at a particular airport (the headquarter of their airline), and forcing each of the airplanes to be used in turn (for the different transitions). Similarly, for Storage all hoists but one are constrained to stay at a particular location, and each of them is forced to be used in turn. In these programs, the transitions from any {a mathematical formula}D-state in which the maintenance goal formula is not satisfied are unrealizable. Moreover, having maintenance goals in a planning problem associated with a program transition can make solving it harder for a planner.
      </paragraph>
      <paragraph>
       Since the planners used in our experimental analysis do not natively support maintenance goals, planning programs with maintenance goals have been translated into planning programs without them. We considered two related translation schemes:
      </paragraph>
      <list>
       <list-item>
        the basic schema adding the maintenance goal formula to the precondition formula of every domain action; and
       </list-item>
       <list-item>
        the same schema T1 extended as described in Section 5.3.
       </list-item>
      </list>
      <paragraph>
       By using T2, the plans realizing the incoming transitions of v generate end states satisfying the formulas of all maintenance goals on the transitions outgoing from v.
      </paragraph>
      <paragraph>
       Fig. 8 shows the performance of our approach using {a mathematical formula}LAMA and {a mathematical formula}LPG with the two considered translations for planning programs of benchmark {a mathematical formula}SM+M50. The results show that, with T1, the performance of {a mathematical formula}RealizePlanProg decreases exponentially with the size of the planning programs; on the contrary, with T2 the performance does not degrade significantly, indicating that building plans achieving the maintenance goals on the next transitions is extremely useful. We observed that the performance gap with T1 and T2 using Hplan-P is even grater than when using {a mathematical formula}LAMA and {a mathematical formula}LPG. (These performance results using Hplan-P are omitted from Fig. 8 for the sake of its readability.)
      </paragraph>
      <paragraph>
       The number of tabu states generated by {a mathematical formula}RealizePlanProg with T2 is always zero using {a mathematical formula}LPG and {a mathematical formula}LAMA, except for only two problems (16 and 17) of Storage using {a mathematical formula}LAMA, where {a mathematical formula}LAMA exceeds the given CPU-time limit; on the contrary, using {a mathematical formula}LPG and {a mathematical formula}LAMA with T1, the number of generated tabu states is almost always very high. This happens because with T1 the plan computed to realize a transition incoming to a {a mathematical formula}P-state v usually reaches an end state that does not satisfy all the formulae of the maintenance goals on the outgoing transitions of v, making realizing at least one of such transitions impossible.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Usefulness of using plan adaptation techniques
      </section-title>
      <paragraph>
       In order to show that using plan adaptation techniques can be very useful to compute the program realization, we compared {a mathematical formula}RealizePlanProg with and without using plan adaptation techniques. For this experiment, we considered the well-known domains Blocksworld and Zenotravel. Since plan adaptation can be especially useful when the program structure forms several cycles and the domain instance is large (i.e., when solving the planning problems can be quite hard), for this experiment we considered the planning programs in benchmark {a mathematical formula}ML2−12, which are planning programs with a structure forming a complete directed graph. The planning programs of benchmark {a mathematical formula}ML2−12 have a number of program states ranging from 2 (program transition relation δ forms a single cycle) to 4 (δ forms 20 cycles). For the planning programs over domain Blocksworld, the number of blocks in the domain instances ranges from 40 to 70; for the planning programs over domain Zenotravel, concerning moving people in a network of locations by using aircrafts consuming levels of fuel, the number of aircrafts, cities and fuel levels is 5, 25 and 4, respectively, while the number of persons ranges from 10 to 50.
      </paragraph>
      <paragraph>
       In this experiment, we used only planner {a mathematical formula}LPG, since it is the only considered incorporated planner that supports plan adaptation. The CPU-time limit used by {a mathematical formula}RealizePlanProg to realize a planning program was 2 hours, while the CPU-time limit for solving a planning problem by {a mathematical formula}LPG was 10 minutes. In the following, LPG-Adapt denotes the version of {a mathematical formula}LPG adapting the plan returned by procedure {a mathematical formula}BestPlan described in Section 5.4.
      </paragraph>
      <paragraph>
       Fig. 9 shows the CPU time of {a mathematical formula}RealizePlanProg using {a mathematical formula}LPG and LPG-Adapt for planning programs in benchmark {a mathematical formula}ML2−12. {a mathematical formula}RealizePlanProg[LPG-Adapt] realizes a larger set of planning programs, and is always faster than or similar to {a mathematical formula}RealizePlanProg[LPG]: with LPG-Adapt every considered planning program is realized; without plan adaptation, when the planning programs have more than 2 states, for Blocksworld{a mathematical formula}RealizePlanProg cannot realize the planning programs with the largest instances, while for Zenotravel it realizes no program. Moreover, {a mathematical formula}RealizePlanProg[LPG-Adapt] is generally considerably faster than {a mathematical formula}RealizePlanProg[LPG]. For Zenotravel, it is significantly faster even for relatively small domain instances and program structure forming a single cycle ({a mathematical formula}n=2 in Fig. 9).
      </paragraph>
      <paragraph>
       Fig. 10 shows the program realization size of {a mathematical formula}RealizePlanProg using {a mathematical formula}LPG and LPG-Adapt for benchmark {a mathematical formula}ML2−12. These results indicate that, when using LPG-Adapt, the program realization can be much smaller. The rationale of this behavior is that achieving PESs by LPG-Adapt can be much easier than by {a mathematical formula}LPG. This happens because (i) for benchmark {a mathematical formula}ML2−12 the domain size is large, and hence achieving PESs can be very hard, (ii) for the considered domains, very often the last plan portion (completely) defines the plan end state, and often the last plan portion of the plan computed by LPG-Adapt is the same as of the input plan (because the goals are the same). Therefore, very often the end state of the plan computed by LPG-Adapt is the same as the end state of the input plan; hence, LPG-Adapt often easily generates plans ending in PESs.
      </paragraph>
     </section>
     <section label="6.6">
      <section-title>
       On domains with many deadends
      </section-title>
      <paragraph>
       When the involved planning domain has many deadends in its domain state space, computing a realization of the planning program can be very hard also using the proposed planning-based approach. In this section, we study the performance of {a mathematical formula}RealizePlanProg for domains with a large number of deadends, focusing on an interesting class of planning programs in which agent activities can be repeatedly done and undone indefinitely often.
      </paragraph>
      <paragraph>
       It is worth noting that, when there are deadends, the planning programs for the experimental evaluation need to be very accurately designed in order to guarantee their realizability. For instance, consider a planning program with δ equal to 1C[50] (a single cycle) in which every transition goal requires moving an airplane in a version of domain Zenotravel without action refuel, so that the fuel level of the airplanes can never be restored after their use. Such planning programs can never be realized, even if the airplane movement were optimal (in terms of fuel consumption), because every {a mathematical formula}D-state generated by a plan realizing a transition is different from the {a mathematical formula}D-states generated by any plan previously computed for that same transition. Therefore, with an initial limited amount of fuel, there exists no realization for which the execution of cycle 1C[50] can be executed indefinitely often.
      </paragraph>
      <paragraph>
       The planning programs that we designed for testing {a mathematical formula}RealizePlanProg in domains with deadends use a directed (irreversible) version of domain Logistics, concerning the movement of packages among cities by airplanes and trucks, in which: only certain movements of airplanes are possible; the initial states are defined as depicted in Fig. 11a; the transition relations are modelled using program structure 1E1C; and the achieving goal formulas are defined as depicted in Fig. 11b.
      </paragraph>
      <paragraph>
       The transition relation defined according to 1E1C models the agent behavior formed by a one-shot activity followed by a cyclic activity. The first activity regards the movement of all packages but one (package P0) from airports L00 and L10 to city L21; the cyclic activity regards the recurrent movement of P0 between city L01 and city L11. Airplanes can fly between airports L00 and L10 in both directions, and from L00 to airport L20 but not from L20 to L00. In order to realize a planning program in this class, the trick is moving all packages but P0 from L00 to L20 (and, subsequently, to L21) by using only one airplane. If both the airplanes were used for this movement, subsequently no airplane would be available to move P0 between L01 and L11. Let n be the number of packages to move. The number of deadend {a mathematical formula}D-state for the planning programs of this experiment is {a mathematical formula}8⋅10n over {a mathematical formula}72⋅10n possible reachable {a mathematical formula}D-states.
      </paragraph>
      <paragraph>
       Fig. 12 shows the performance of {a mathematical formula}RealizePlanProg for the described planning programs. With {a mathematical formula}LPG and {a mathematical formula}LAMA only the programs with few packages to move are realized; while with Hplan-P no program is realized. The results in the figure indicate that, when the planning domain has many deadends but the number of generated tabu states is not high, {a mathematical formula}RealizePlanProg can find a solution within the given CPU time limit. However, this happens only for small-size problems. When there are many packages in the domain, the number of deadends significantly increases and {a mathematical formula}RealizePlanProg generates more tabu states, not only because the planning problems associated with the program transitions can be unsolvable, but also because they can be very hard to solve for the planners when they are solvable, leading the planner to fail within the given CPU time.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      The work presented here can be related with two recent efforts to integrate agent-oriented programming and systems with declarative goals and lookahead planning. Efforts to integrate declarative goals (e.g., [24], [25], [26], [58], [91], [100]) stem from the recognized need of providing development frameworks that are more faithful to the notion of rational agent behavior developed in agent theory [14], [23], [97], as well as to enhance those systems with more flexible and robust mechanisms for intelligent action selection. For example, the AgentSpeak-like language CANPlan[91] provides a construct {a mathematical formula}Goal(ϕs,δ,ϕf) with the intended meaning of “achieve (success) goal {a mathematical formula}ϕs by executing (procedural) plan δ, provided failing condition {a mathematical formula}ϕf remains false” (similar constructs were proposed for other agent programming frameworks, such as AgentSpeak itself or 3APL/2APL). While Goal's constructs like the above one resemble planning program's transitions of the form “achieve {a mathematical formula}ϕs while maintaining {a mathematical formula}¬ϕf,” they have some major differences. In particular, there is no effort from agent architectures to proactively enforce the satisfaction of the goals; their support remains at the reactive level (i.e., re-try δ if it has completed without achieving {a mathematical formula}ϕs, and successfully drop it or abandon it with failure if {a mathematical formula}ϕs or {a mathematical formula}ϕf becomes true, resp.). In other words, no reasoning is performed to guarantee that plan δ is in fact executed in a way that would bring about the goal {a mathematical formula}ϕs (while avoiding {a mathematical formula}ϕf). The reason for this is one of efficiency: agent programs are meant to be executed online under soft real-time constraints, and hence rely on the assumption that the given program δ is designed to achieve the goal {a mathematical formula}ϕs on-the-fly, under normal circumstances. Solving planning programs, instead, requires building plans that will not only achieve each local goal (in transitions), but that are also mutually “compatible” within the whole network of goals. On the other hand, planning programs do not provide, at this point, ways of specifying (and using) available procedural domain information to build those plans, something that can arguably help to cope with the complexity of the problem (see below discussion on HGN planning).
     </paragraph>
     <paragraph>
      Another related link between planning programs and agent systems is the integration of automated planning capabilities to the latter. There are indeed a number of platforms and architectures which mix, in some way or another, planning and program execution into a so-called continual planning approach, such as A-SHOP[39], Retsina[78], SRI's Cypress[105], Propice-Plan[37], CANPlan[91], and JADEX[103]. All these systems are able to do some type of lookahead planning within a typical reactive agent execution. In most cases, the type of planning considered is domain-tailored planning, similar to HTN-planning [46], rather than first-principle planning as in planning programs [91], [104]. In addition, the underlying approach is to provide specific programming constructs (e.g., CANPlan's {a mathematical formula}Plan(δ,ϕ)[91] or IndiGolog's {a mathematical formula}Σ(δ;ϕ?)[29] constructs to achieve ϕ using program δ) that allow for calling a planning module to synthesize a course of actions, which is then carried out by the agent execution engine. Roughly speaking, the difference with our work is that the core of continual planning systems is driven by an online executor (which can however resort to local lookahead planning as necessary), whereas planning programs are meant to be fully solved offline in order to obtain execution guarantees for all possible agent behaviors modelled in the program.
     </paragraph>
     <paragraph>
      From the planning perspective, the work on hierarchical goal network (HGN) planning [95], [96] shares motivations and has technical similarities with planning programs, but they also have important differences. HGN planning aims at generalizing “classical” HTN planning to include goal networks, by using a different semantics for tasks and methods. In HGN planning, tasks correspond to classical goals and methods specify ways to decompose goals into sequences of subgoals. There has even been efforts to develop HGN-planning systems that work with partial decomposition knowledge [94]. Like planning programs, HGN planning has the ability to specify agent behaviors in a declarative manner using a network of goals. However, those networks amount to partially-ordered sets of goals (therefore not admitting indefinitely looping behaviors) whose total order of satisfaction is left to the solver to decide. Planning programs admit network with cycles and the ordering of goals is outside the control of the solver. Generally speaking, the behaviors that HGN planning aims to capture are the same as those of planning with temporally extended goals, producing a single plan to be executed. On the other hand, planning programs require generating a controller for multiple alternative synthesized plans that cover the whole space of deliberation of the agent (in order to execute the right plan according to the transition chosen by the agent at each step). The idea, though, of integrating goal networks with subgoal decomposition knowledge as well as the techniques based on landmark reasoning used in existing HGN systems are worth investigating in the context of planning programs, so as to better deal with the intrinsic computational difficulty of the task.
     </paragraph>
     <paragraph>
      One particular agent paradigm that appears capable of encoding planning programs is that of Golog-like situation calculus-based high-level programming languages [28], [29], [68], [5]. Indeed, because those languages offer standard programming constructs (including iteration, conditionals, and even parallel execution) as well as non-deterministic {a mathematical formula}δ1|δ2 (execute {a mathematical formula}δ1 or {a mathematical formula}δ2) and a test construct ϕ? (guarantee ϕ is true), one could imagine that planning programs could be encoded into a particular Golog-like program. This is actually not the case, at least if one considers the standard semantics of these programs [68], the so called “offline execution.” First, Golog-like languages are typically meant to execute the given program to completion and cannot then handle continuous (cyclic) programs/controllers that are meant to run forever, as it is the case for planning programs. Second, the non-deterministic constructs have typically an “angelic” semantic: the planner has to find one that works. In planning programs, the controller has to guarantee executability for every possible choice. Finally, Golog-like languages do not come with sophisticated techniques for the actual synthesis of (iterated) successful executions. A different analysis needs to be carried out for IndiGolog[29]. This variant of Golog has the capabilities of representing our planning programs, by making use of standard constructs to represent the control structure given by the transition system and the special deliberation construct {a mathematical formula}Σ(⋅) for representing “goal-oriented actions” labeling transition. Specifically, each goal-oriented assertion {a mathematical formula}[γ:ψ,ϕ] can be represented as {a mathematical formula}[ifγthenΣ((πa.ψ?;a)⁎;ϕ?)]. Nonetheless, due to their online execution nature, the resulting IndiGolog program would account for a sort of continual planning approach as discussed above, under which goals assertions (modeled as Σ search blocks) are independent of each other.
     </paragraph>
     <paragraph>
      Interestingly, in [5], a language based on Golog has been used to specify domain-control knowledge for solving classical planning problems, and a translation function has been proposed, which given a planning instance and a program described by a Golog-based language outputs a new planning instance that embeds the control stated by the program. This enables any planner to exploit search control specified by the program. We could see our work as an extension of that, where instead of specifying Golog transitions in terms of actions we specify them in terms of goals.
     </paragraph>
     <paragraph>
      A synthesis problem tightly related to the work presented here is that of behavior composition [35]. In fact, such problem is one of the main starting points for our work here. The idea there is to realize (i.e., implement) a given desired, but non-existent, target module that a user is meant to operate (e.g., a home entertainment system) by suitably coordinating a set of existing available modules (e.g., video cameras, game consoles, automatic blinds and lights, etc.) The problem is in fact a generalization, within a broader AI context, of the well-known web-service composition problem [8], [9], [72] in which a target web-service is obtained by putting together a set of existing web-services. Like agents in planning programs, the target module user is assumed to operate a behavior specification by issuing requests that ought to be satisfied (by a smart controller, called the “composition”). However, in the composition task the request is for the execution of a particular action (e.g., play music) rather than the achievement of a state of affairs. Moreover, the challenges involve deciding which of the existing available modules will be able to fulfill such request. Rather than searching for adequate behavior delegations, in planning programs, we look for complex conditional programs that could be “stitched” together so as to guarantee declarative goal requests. Because actual domain actions will generally be executed in concrete devices and available modules, it makes sense to look for plans solving a given planning program that could actually be carried out by proper delegation to such modules. It is indeed possible to extend the planning-program framework to accommodate the “delegation” of plans to their actual performers, in the same way as done in behavior composition. This is done by compiling away all behaviors into the underlying dynamic domain; see [34] for details. What is more, it is possible to suitably encode a complete behavior composition task into a planning-program realization, along the line of the hardness proof of Theorem 5. It follows then that the framework for agent planning programs presented here subsumes that for behavior composition. Lastly, we note that similar techniques based on synthesis over specific game structures [35] or automated planning [86] were used to solve the composition task, among others.
     </paragraph>
     <paragraph>
      The work on agent planning programs is related to generalized planning, in the sense that the result of the planning program realization can be seen as a form of generalized plan (e.g., [13], [33], [98]). Generalized plans are rich control structures that include loops and parametrized or lifted actions whose arguments must be instantiated during execution. The work on generalized planning looks at synthesizing a plan that is general enough to realize the same goal on several planning scenarios. Instead, the work presented in this article looks at synthesizing a plan that realizes, within the control structure imposed by the agent program, a collection of interrelated goals over the same planning domain.
     </paragraph>
     <paragraph>
      Planning programs can also be considered as a form of complex routines, modelling desired domain evolutions and typically including conditions and cycles, that an agent executes in the domain. In planning, similar routines can be specified by temporally extended goals (e.g., [3], [6], [36], [43], [61]), in the following abbreviated with TE-goals. Unlike simple achievement goals, which express required properties of the final state achieved by a plan, TE-goals express required properties or constraints on the whole (possibly cyclic) sequences of states traversed by all possible executions of a valid plan. For instance, TE-goals can be used to require that some state properties are achieved according to a certain sequence, that a property holds in every state generated by the plan execution, that a property is achieved periodically or within a certain number of plan steps from a state where another property holds, etc. Planning with a class of TE-goals can be compiled into classical planning by compilation schemes using additional domain predicates and actions (e.g., [6], [43]).
     </paragraph>
     <paragraph>
      TE-goals can also be used to specify domain-specific control knowledge that a planner can exploit to generate plans more efficiently. For deterministic domains, e.g., the forward search planner TLPlan[3] provides a logic-based platform supporting reasoning about search control knowledge, in the form of temporal logic formulae that promising plan prefixes must not violate. Moreover, TLPlan is capable of building cyclic plans modeling required domain evolutions [61] specified by LTL formulas expressing TE-goals. The planning method used by TLPlan relies on the construction and compilation of Büchi automata equivalent to the TE-goals [107], which recognize the language of (cyclic) execution sequences satisfying the goals. For non-deterministic domains, e.g., planner MBP[22] provides a framework to plan for TE-goals expressed using CTL formulas [41] that distinguishes temporal requirements on all possible and on some plan executions [79]. In order to deal with large search spaces, the planning approach used in MBP relies on symbolic model checking techniques and BDDs [16].
     </paragraph>
     <paragraph>
      While TE-goals are declarative plan requirements, planning programs also provide a way of specifying procedural knowledge of the domain. MBP has been extended to support planning with requirements such as “it should do everything that is possible to achieve a given condition”, with failure situations of the form “try to reach a goal but, in case of failure, do reach a different goal” [65], and with procedural goals specified by constructs expressing conditional and iterative plans. [93]. However, the problems addressed by MBP are quite different from agent planning programs, and it is not clear whether the problem of realizing an agent planning program can be compiled into a MBP problem so that a plan satisfying the MBP's goals corresponds to a planning-program realization. The most significant differences between planning programs and the methods in [65], [93] are that the MBP framework cannot cope with the executor decisions, which introduce a sort of nondeterminism in the planning program definition and is a distinguishing feature in our problem, and that MBP requires that at least one execution reaches a successful state. A consequence of the latter point is, e.g., that procedural goals expressed by loops need to terminate, while in planning programs this is not required.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      An encoding example
     </section-title>
     <paragraph>
      In this Appendix we show the actual encoding of the nondeterministic variant of the example presented in Section 3. The encoding is provided in the language SMV, which is a standard input language for some state-of-the art model checkers (such as NuSMV[20] and SMV[73]) that has been adopted also in the synthesis engines TLV[84], JTLV[83] and NuGaT[17]. The use of SMV also allows us to show how to express transitions in a compact way.
     </paragraph>
     <paragraph>
      An excerpt of the listing is reported in Fig. A.1. The game is organized hierarchically in three modules. The topmost module, main (top of figure), encodes the whole game, and is composed of two submodules: environment, of type environment_module (defined in the bottom right section of the figure), which encodes the behavior of the environment, and agent, of type system_module (bottom left), which captures the behavior of the system. The module type defines what the module (formal) parameters are, i.e., how the module interacts with other modules, and how it behaves.
     </paragraph>
     <paragraph>
      Module definitions have several sections. VAR is where local variables are declared. Variables can be either boolean, such as last of system_module, or of enumerated type, such as fuel of environment_module, which can assume the values full, empty and low. In fact, enumerated types are suitably represented using (arrays of) boolean values, so we can consider the game as defined over boolean variables only. In the case of main also the modules representing the players, although not being proper variables, are declared in section VAR, using the keyword system. According to the semantics of two-player games the state transitions of main are obtained by concatenating an agent transition to an environment's, starting with both players in their initial state, with environment moving first.
     </paragraph>
     <paragraph>
      When a module, such as agent or environment in main, is instantiated, its formal parameters are bound to variables (possibly module instances themselves), which can then be accessed by the instantiated module. For instance, the declaration of environment in main states that environment can access the module instance agent, and in particular all of its local variables, i.e., agent.act, agent.last, agent.viol.
     </paragraph>
     <paragraph>
      The VAR section of system_module contains the declarations of system variables, i.e., the controlled variables. These include one enumerated variable act for actions, as well as boolean variables last and viol. In environment_module, some enumerated variables (fuel, my_loc, car_loc) are used to concisely capture exclusive propositions. For instance, since fuel can be at one level only, the fuel variable can assume values full, low and empty. The boolean variables driven and rain keep track, respectively, of whether the researcher has just driven and whether it is raining. The remaining variables, pp_state and pp_trans, record the current state of the planning program and the current transition requested, respectively. Notice that, for convenience, planning program transitions are named. For instance, tr_1 represents the transition from {a mathematical formula}v0 to {a mathematical formula}v1.
     </paragraph>
     <paragraph>
      In section DEFINE, propositional formulas can be defined. This feature is used only in main, where good is a reserved name for the formula representing the propositional part of the goal. The declaration good:= agent.last asserts that the winning condition of the game, i.e., the formula {a mathematical formula}φgoal, is {a mathematical formula}□◊agent.last (the temporal modalities □ and ◊ are implicit).
     </paragraph>
     <paragraph>
      The remaining sections INIT and TRANS are used to define, respectively, the initial state and the transition relation of a module. The former contains a formula stating what the initial values of local variables are. For instance, the INIT section of system_module expresses the fact that, initially, act is assigned to start, last is true and viol is false (symbols &amp;, | and ! stand, respectively, for logical and, or and not). These are arbitrary default values, assigned so as to have only a single initial state. Action start, the only action that the system can select in the initial state, will set each variable (possibly nondeterministically) to its actual initial value (leaving unconstrained variables free to range over their definition domain). The corresponding section of environment_module has an essentially analogous structure.
     </paragraph>
     <paragraph>
      Section TRANS contains a formula that relates the value of each variable at a state with the values of other variables at current or next state. This essentially defines the transition relation for the module as including all those pairs of (current and successor) states whose variable assignments satisfy the formula. Keyword next is used to refer to the value of a variable at next state. For instance, the expression next(act)!= start expresses that the value of act at next state cannot be start (which is allowed only in the initial state). Typically, TRANS is a complex formula obtained as a conjunction of case blocks which consist of an ordered list of cases, each defined by a condition followed by a consequence, separated by character ‘:’. The semantics of a case stipulates that if the condition holds, the consequence holds too. Cases are evaluated in the order they appear in the block: when a case is encountered whose condition holds, the case block assumes the value of the consequence associated with the selected case. For instance, in the first block of the TRANS section of module_environment, the first case states that after action start is executed (sys.act = start), the fuel level will be full: next(fuel) = full (lines starting with – are commented). The second case, instead, states that if sys.last holds in the current state, the fuel level does not change at next state. The second case, however, is considered only if the condition of the first one is not satisfied.
     </paragraph>
     <paragraph>
      The TRANS sections of system_module and enviroment_module encode the transition relations of the system and environment players, respectively, for our example. Such relations are expressed through boolean formulas, in particular as conjunctions of case blocks.
     </paragraph>
     <paragraph>
      Consider the TRANS section of system_module. The first case block captures action preconditions. In details, the first line expresses that action refuel can be selected for execution at next step only if, at the same step, it is the case that env_myloc and car_loc match, i.e., that the researcher and the car are in the same location. The second line, which is considered only if the condition of the previous case does not hold, requires that, in order for the researcher to be able drive home, the tank of the car must be not empty. In addition to preconditions for regular domain actions, this block includes also constraints and preconditions on action wait, which has to be executed whenever last holds, and can be selected (when last does not hold) only if none of the preconditions for the other actions is satisfied.
     </paragraph>
     <paragraph>
      The second block encodes the same constraints on proposition last discussed in previous section, i.e., that last can hold only if the current achievement goal is indeed achieved and no violation has occurred. So, e.g., the first line of this block encodes that if tr_1 is the current requested transition, last can be true only if the researcher is at the department and no violation has been recorded (in variable viol). The last block captures when violations occur and, in particular in the last line, that once occurred they are recorded forever.
     </paragraph>
     <paragraph>
      As to environment_module, the TRANS section contains a first set of case blocks which capture the effects of actions. For instance, the first block captures how driving actions affect the fuel level of the car. Notice that the evolution of fuel is nondeterministic. For each variable used to encode the domain state there is a distinct case block, each considering all of the possible actions. After these, a block for the transition requests is present, which states what the transitions are that can be requested for each state that the planning program can be in. For instance, at state v0 only tr_1 or (symbol |) can be requested. Notice that if a variable is not constrained by TRANS, its value can freely range over its domain. For instance, variable rain can assume any value after the execution of any action. The next block captures the guards on program transitions. In particular, it requires that, in order for transition tr_4 to be requested, rain must be false (this is the only transition where a guard other than true is present). Observe that the guard is required to be satisfied only when the transition request is new, i.e., immediately after an occurrence of last, which marks the realization of the current transition. Finally, the last block encodes the evolution of program states when the currently requested transition is realized. For example, the second line of this block states that when tr_1 is requested and sys.last holds (meaning that the requested transition is realized), the next state will be v1, i.e., the destination state of the transition.
     </paragraph>
     <paragraph>
      We observe that, in SMV, the use of propositional formulas allows one to refer to sets of states, without having to list them explicitly, by considering a formula as representative of those states that satisfy it. In the same way, through the use of the next operator one can compactly represent transitions between states. Interestingly, TLV, JTLV and NuGaT, as well as many other synthesis engines, take advantage of this symbolic representation [16], typically optimized using ordered binary decision diagrams, to efficiently manipulate sets of states and transitions.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Proofs
     </section-title>
     <paragraph>
      Proof ofTheorem 3(page 75). First of all, by the definition of G, each game state W encodes:
     </paragraph>
     <list>
      <list-item label="•">
       the (current) domain state {a mathematical formula}W[s]={p|p∈W∩P}, that is, the projection of W on the set of {a mathematical formula}D's domain propositions P (recall that {a mathematical formula}XP=P);
      </list-item>
      <list-item label="•">
       the (current) planning program state {a mathematical formula}W[v]∈W∩V, which always exists and is unique due to definition of {a mathematical formula}ρe (recall that {a mathematical formula}XV=V);
      </list-item>
      <list-item label="•">
       the transition {a mathematical formula}W[d]=〈v,γ,ψ,ϕ,v′〉 such that {a mathematical formula}W[v]=v, and {a mathematical formula}v,reqγ:ψ,ϕv,v′∈W, which always exists and is unique due to definition of {a mathematical formula}ρe (see E6 and E8);
      </list-item>
      <list-item label="•">
       the action {a mathematical formula}W[a]∈W∩A, which always exists and is unique by the definition of {a mathematical formula}ρs (S2).
      </list-item>
     </list>
     <paragraph>
      We will say that W represents domain state {a mathematical formula}W[s], planning program state {a mathematical formula}W[v], transition {a mathematical formula}W[d], and action {a mathematical formula}W[a] (or, alternatively, that these are represented in W).
     </paragraph>
     <paragraph>
      (If Part) Assume that a strategy f winning for the system exists, and let {a mathematical formula}σ=W0W1⋯ be a play compliant with f. From now on, we use {a mathematical formula}si=Wi[s], {a mathematical formula}vi=Wi[v], {a mathematical formula}di=Wi[d], and {a mathematical formula}ai=Wi[a], for all {a mathematical formula}i≥0.
     </paragraph>
     <paragraph>
      We start by making two observations. First, transition relations {a mathematical formula}ρe and {a mathematical formula}ρs guarantee that:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}W1 represents the initial domain state {a mathematical formula}s0 of {a mathematical formula}D (E1) and the initial program state {a mathematical formula}v0 of {a mathematical formula}P (E4), that is, {a mathematical formula}W1[s]=s1=s0 and {a mathematical formula}W1[v]=v1=v0;
      </list-item>
      <list-item label="•">
       if {a mathematical formula}last∉Wi and {a mathematical formula}i≥1, then {a mathematical formula}vi,reqγ:ψ,ϕvi,v′∈Wi+1 (i.e., program state and current request remain unchanged; see E10 and E11), and {a mathematical formula}si+1∈τ(si,ai) (i.e., the domain state represented in the next game state is one resulting from the execution of the action executed; see E3);
      </list-item>
      <list-item label="•">
       if {a mathematical formula}last∈Wi and {a mathematical formula}i&gt;0, then {a mathematical formula}si+1=si (i.e., selected action {a mathematical formula}ai has no effect; see E2), and there exists {a mathematical formula}reqγ′:ψ′,ϕ′v′,v″∈Wi+1 such that {a mathematical formula}v′ is represented in {a mathematical formula}Wi+1 (E9), {a mathematical formula}reqγ:ψ,ϕvi,v′∈Wi and {a mathematical formula}si+1⊨γ′ (i.e., {a mathematical formula}Wi+1 represents a new and valid request transition from the new program state; see E6, E7, and E9).
      </list-item>
     </list>
     <paragraph>
      Second, because f is a winning strategy and σ is compliant with f, we have that:
     </paragraph>
     <list>
      <list-item label="•">
       for all {a mathematical formula}i≥0, {a mathematical formula}violated∉Wi, that is, for {a mathematical formula}reqγ:ψ,ϕvi,v′∈Wi, it is the case that either {a mathematical formula}Wi⊨ψ or {a mathematical formula}Wi⊨last (see S5, S6 and S7);
      </list-item>
      <list-item label="•">
       if {a mathematical formula}last∈Wi and {a mathematical formula}reqγ:ψ,ϕvi,v′∈Wi, then {a mathematical formula}Wi⊨ϕ, that is, when the system “plays” last, the achievement goal of the current {a mathematical formula}P-transition requested is achieved (S5);
      </list-item>
      <list-item label="•">
       last holds infinitely many times along σ, as required by {a mathematical formula}φgoal.
      </list-item>
     </list>
     <paragraph>
      Let us prove that {a mathematical formula}P is realizable in {a mathematical formula}D from {a mathematical formula}s0. By Theorem 1, it is enough to prove the existence of a realization by showing a PLAN-based simulation R (Definition 3) such that {a mathematical formula}〈v0,s0〉∈R. To that end, consider the relation {a mathematical formula}R⊆V×2P defined as:{a mathematical formula} Informally {a mathematical formula}〈s,v〉 is in R if there is a winning play where s and v are represented in a state ({a mathematical formula}Wi+1) just after a previous request has been completed (signaled by last being true in {a mathematical formula}Wi). Observe that because {a mathematical formula}last∈W0, this includes the case when s and v are initial for {a mathematical formula}D and {a mathematical formula}P, respectively, i.e., {a mathematical formula}W1[s]=s0 and {a mathematical formula}W1[v]=v0. In other words a new request in domain state s and agent planning program state v has just been initiated (in game state {a mathematical formula}Wi+1).
     </paragraph>
     <paragraph>
      The fact that {a mathematical formula}〈v0,s0〉∈R is trivial given that {a mathematical formula}last∈W0 and, as observed above, {a mathematical formula}W1[s]=s0 and {a mathematical formula}W1[v]=v0 (this holds for any f-compliant play). So, it remains to show that R is a PLAN-based simulation (as defined in Definition 3). To that end, let {a mathematical formula}〈v,s〉 be a pair in R, and consider a transition {a mathematical formula}v→γ:ψ,ϕv′ in {a mathematical formula}P such that {a mathematical formula}s⊨γ. First of all we know that:
     </paragraph>
     <list>
      <list-item label="†">
       Since {a mathematical formula}〈v,s〉∈R, there exists an f-compliant play {a mathematical formula}σ=W0W1⋯WℓWℓ+1⋯ such that {a mathematical formula}Wℓ+1[s]=s and {a mathematical formula}Wℓ+1[v]=v, for some {a mathematical formula}ℓ&gt;0, and {a mathematical formula}last∈Wℓ.
      </list-item>
      <list-item label="††">
       Given that game G accounts for every transition in the agent planning program (see E6), there is one such play σ such that {a mathematical formula}reqγ:ψ,ϕv,v′∈Wℓ+1 (i.e., {a mathematical formula}Wℓ+1[d]=〈v,γ,ψ,ϕ,v′〉).
      </list-item>
     </list>
     <paragraph>
      Next, let us define an HT-plan π for such transition such that π achieves ϕ while maintaining ψ from state s (first constraint in Definition 3), and π preserves R (second constraint in Definition 3). The idea is to define a general (conditional) plan that makes the same action selections, at every step, as those done by the winning strategy f. The key is that the winning strategy f is indeed encoding a valid HT-plan. More concretely, consider the general plan π such that for any history {a mathematical formula}h=s0→a1s1→a2⋯→ansn with {a mathematical formula}s0=s, it is the case that:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}π(s0→a1s1→a2⋯→ansn)=an+1, if there exists a play {a mathematical formula}σˆ=σ|ℓW0W1⋯Wn⋯ such that:
      </list-item>
      <list-item label="•">
       {a mathematical formula}π(s0→a1s1→a2⋯→ansn) is left undefined, otherwise.
      </list-item>
     </list>
     <paragraph>
      It is not difficult to see that, because of all four constraints and the fact that strategies are deterministic, all plays {a mathematical formula}σˆ as above will coincide on all game states {a mathematical formula}W0 to {a mathematical formula}Wn, and hence plan π is well-defined.
     </paragraph>
     <paragraph>
      Let us first prove that π is an HT-plan, that is, that all executions of π are finite. Suppose, on the contrary, that there is an infinite execution {a mathematical formula}h=s0→a1s1→a2⋯ of π. This means that {a mathematical formula}π(s0⋯sk)=ak+1, for each {a mathematical formula}k≥0, and because of the way π was built, this implies that there has to exist an (infinite) play {a mathematical formula}σˆ=σ|ℓW0W1⋯ such that each {a mathematical formula}Wi corresponds to each state {a mathematical formula}si (i.e., {a mathematical formula}Wi[s]=si) and action {a mathematical formula}ai+1 (i.e., {a mathematical formula}Wi[a]=ai+1). More importantly, since h is infinite and π is always defined, it has to be the case, due to the last constraint in definition of π, that {a mathematical formula}last∉Wi, for all {a mathematical formula}i≥0—last does not hold true from {a mathematical formula}W0 onwards. It follows then that {a mathematical formula}σˆ⊭□◊last. However, this is a contradiction, since {a mathematical formula}σˆ is a play compatible with strategy f (by how σ was constructed above), and f is a winning strategy for a game whose goal is indeed {a mathematical formula}φgoal=□◊last. Hence, the above infinite execution h of π may not exists, all executions of π are finite, and π is an HT-plan.
     </paragraph>
     <paragraph>
      Next let us show that the two constraints in the PLAN-based simulation Definition 3 are satisfied. To that end, take any complete execution {a mathematical formula}h=s0→a1s1→a2⋯sn−1→ansn of HT-plan π. Then:
     </paragraph>
     <list>
      <list-item label="•">
       Because of the way that π was constructed we can infer that:
       <list>
        there exists an f-compliant play {a mathematical formula}σˆ=σ|ℓW0W1⋯Wn−1Wn⋯ such that, among other things, {a mathematical formula}last∉Wi and {a mathematical formula}Wi[a]=ai+1, for all {a mathematical formula}0≤i≤n−1;{a mathematical formula}π(h) is undefined, since h is complete (i.e., h cannot be further extended with π);it has to be the case that {a mathematical formula}last∈Wn. Suppose, on the contrary, that this is not the case and {a mathematical formula}last∉Wn. Then, take any f-compliant play {a mathematical formula}σˆ′=σ|ℓW0W1⋯WnW′W″⋯. There has to be at least one such play given that ρ is, by construction, serial (i.e., there are no deadends). Since {a mathematical formula}π(h) is undefined, it has to be the case that play {a mathematical formula}σˆ′ does not satisfy one of the four constraints in the definition of π above. However, {a mathematical formula}σˆ′ trivially satisfies the first three requirements, so {a mathematical formula}last∈Wi, for some {a mathematical formula}i≤n. We know, due to existence of {a mathematical formula}σˆ as above, that {a mathematical formula}last∉Wi, for all {a mathematical formula}0≤i≤n−1. Then, {a mathematical formula}last∈Wn.Now, recall from (††) above, that
       </list>
       <paragraph>
        {a mathematical formula}reqγ:ψ,ϕv,v′∈W0=Wℓ+1. Due to (E11) and the fact that {a mathematical formula}last∉Wi, for all {a mathematical formula}i≤n, such active request is propagated throughout the whole game play up to {a mathematical formula}Wn included. Hence, {a mathematical formula}reqγ:ψ,ϕv,v′∈Wn. That, together with the fact that {a mathematical formula}last∈Wn and (S5), implies that:
       </paragraph>
       <list>
        <list-item label="–">
         {a mathematical formula}Wn[s]=sn⊨ϕ and since h stands for any complete execution of π, π achieves ϕ from state {a mathematical formula}s0=s.
        </list-item>
        <list-item label="–">
         {a mathematical formula}Wn⊨¬violated. Due to axiom (S7), we conclude that {a mathematical formula}W0⊨¬violated. This together with constraint (S6), implies that {a mathematical formula}Wi[s]=si⊨ψ, for all {a mathematical formula}i∈{0,…,n−1}. Thus, π maintains ψ from state {a mathematical formula}s0=s.
        </list-item>
       </list>
       <paragraph>
        So, putting it all together, HT-plan π achieves ϕ while maintaining ψ from state s.
       </paragraph>
      </list-item>
      <list-item label="•">
       Consider the play {a mathematical formula}σˆ=σ|ℓW0W1⋯Wn−1WnWn+1⋯ from above. We already know that the play is complaint with strategy f, and that {a mathematical formula}last,reqγ:ψ,ϕv,v′∈Wn. Due to axiom (E9), it follows then that {a mathematical formula}Wn+1[v]=v′.We also know that {a mathematical formula}Wn[s]=sn. Because {a mathematical formula}last∈Wn, it follows due to axiom (S4) that {a mathematical formula}wait∈Wn (a no-op action is done at game state {a mathematical formula}Wn). Because of axiom (E2), {a mathematical formula}Wn+1[s]=sn has to hold—the domain remains still. Thus, by how R was defined, we conclude that {a mathematical formula}〈v′,sn〉∈R, that is, πpreservesR from {a mathematical formula}〈v,s〉 for transition {a mathematical formula}v→γ:ψ,ϕv′.
      </list-item>
     </list>
     <paragraph>
      Summarizing, we have just demonstrated that for any transition {a mathematical formula}v→γ:ψ,ϕv in {a mathematical formula}P, the plan π is a conditional plan satisfying both requirements of Definition 3. Then, relation R is indeed a PLAN-based simulation and the existence of a realization is guaranteed by Theorem 1.
     </paragraph>
     <paragraph>
      (Only-If Part) Let {a mathematical formula}Ω:2P×δ↦HTD be a realization of {a mathematical formula}P in {a mathematical formula}D from {a mathematical formula}s0. From Ω, we shall derive a winning strategy f for the system, by induction on the length of environment moves {a mathematical formula}X0X1⋯Xn. For the base case, we define {a mathematical formula}f(X0=XI)=YI={init,last}.
     </paragraph>
     <paragraph>
      Assume f is defined for ℓ moves, and let us define the system {a mathematical formula}ℓ+1's move as per strategy f. To that end, consider a legal sequence of {a mathematical formula}ℓ+1 environment moves of the form {a mathematical formula}λ=X0X1⋯XℓXℓ+1, with {a mathematical formula}ℓ≥0, such that {a mathematical formula}σ=W0W1⋯Wℓ is a finite play compliant with λ and f, that is, {a mathematical formula}Wi=(Xi,f(X0⋯Xi)), for {a mathematical formula}0≤i≤ℓ. Then, we define:{a mathematical formula} where:
     </paragraph>
     <list>
      <list-item label="–">
       index {a mathematical formula}k≤ℓ is the largest index such that {a mathematical formula}last∈Wk in σ. That is {a mathematical formula}Wk represents the last state where a transition request was fulfilled and a new request has been issued at {a mathematical formula}Xk+1 and is still “active.”
      </list-item>
      <list-item label="–">
       HT-plan π is defined as {a mathematical formula}π=Ω(Xk+1[s],Xk+1[d]). Basically, plan π is the plan that was prescribed by realization Ω when the transition request {a mathematical formula}Xk+1[d] was issued at state {a mathematical formula}Xk+1[s]. Since {a mathematical formula}Wk is the last step where last holds true, such request is still “active.” We prove below that π does exist.
      </list-item>
     </list>
     <paragraph>
      Next, we are to prove that function f is indeed a strategy for G (in doing so, we show that plan π above always exists). We do so by induction on the length of λ:
     </paragraph>
     <list>
      <list-item label="•">
       If {a mathematical formula}ℓ=0, then {a mathematical formula}λ=X0X1 (and {a mathematical formula}σ=W0). Thus, {a mathematical formula}k=0 (recall {a mathematical formula}last∈W0 since {a mathematical formula}last∈YI) and, by axioms E1 and E4, {a mathematical formula}X1[s]=s0 and {a mathematical formula}X1[v]=v0. Moreover, because of axioms E6 and E7, {a mathematical formula}reqγ:ψ,ϕv0,v′∈X1 denotes some legal request transition {a mathematical formula}X1[d] from {a mathematical formula}v0 with its guard being true in {a mathematical formula}s0 (i.e., {a mathematical formula}s0⊨γ). Due to Definition 4, {a mathematical formula}Ω(X1[s],X1[d]) is defined, that is, {a mathematical formula}Ω(X1[s],X1[d])=π for some HT-plan π that achieves ϕ while maintaining ψ. We need now to consider two cases:
      </list-item>
      <list-item label="•">
       Next consider {a mathematical formula}λ=X0X1⋯XℓXℓ+1, for some {a mathematical formula}ℓ≥0. By induction hypothesis, {a mathematical formula}f(X0X1⋯Xℓ) is defined and is a legal system move. This means that there exists {a mathematical formula}k′&lt;ℓ and a plan {a mathematical formula}π′ as per definition of f above that was used to define {a mathematical formula}f(X0X1⋯Xℓ). We consider again two cases:
      </list-item>
     </list>
     <paragraph>
      □
     </paragraph>
     <paragraph>
      Finally, the fact that f is indeed a winning strategy follows from the fact that it is defined in terms of HT-plans that are finite. This means that, eventually, every HT-plan will complete, will be undefined, and f will eventually always play proposition last, thus meeting G's winning condition.
     </paragraph>
     <paragraph>
      Proof ofTheorem 5(page 76). For EXPTIME membership we just observe that the general procedure works for this special case as well.
     </paragraph>
     <paragraph>
      For the EXPTIME-hardness, we show a reduction from behavior composition problem for deterministic behaviors which is known to be EXPTIME-hard [76].
     </paragraph>
     <paragraph>
      We define an (agent) behavior as a tuple {a mathematical formula}B=〈B,A,b0,ϱ〉, where:
     </paragraph>
     <list>
      <list-item label="•">
       B is the finite set of behavior's states;
      </list-item>
      <list-item label="•">
       A is the finite set of behavior's actions;
      </list-item>
      <list-item label="•">
       {a mathematical formula}b0∈B is the behavior's initial state;
      </list-item>
      <list-item label="•">
       {a mathematical formula}ϱ:B×A↦B is the behavior's partial transition function.
      </list-item>
     </list>
     <paragraph>
      Notice behaviors are deterministic since ϱ is a partial function.
     </paragraph>
     <paragraph>
      The behavior composition problem can be phrased as follows: check if a target behavior {a mathematical formula}T=〈T,A,t0,ϱt〉 can be simulated[75] by the asynchronous product of the available behavior {a mathematical formula}B1,…,Bn with {a mathematical formula}Bi=〈Bi,A,bi0,ϱi〉, with {a mathematical formula}i∈{1,…,n}. The problem is known to be EXPTIME-hard in the number n of available behaviors [76].
     </paragraph>
     <paragraph>
      We reduce to the realization of the planning programs in deterministic domain as follows. First we define the dynamic domain {a mathematical formula}D=〈P,2P,A,ρ〉 and an initial state {a mathematical formula}S0 as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}P=(⋃i=1nPi)∪{Execa|a∈A}∪{Execreset}, where {a mathematical formula}Pi={b|b∈Bi} is a set of new propositions representing the different states of available behavior {a mathematical formula}Bi; propositions {a mathematical formula}Execa records “behavior action” a has just been executed; and proposition {a mathematical formula}Execreset does this for an extra special action reset states whether.
      </list-item>
      <list-item label="2.">
       {a mathematical formula}A′=Ab∪{reset} where {a mathematical formula}Ab={ai|a∈A,i∈{1,…,n}}, that is, the domain actions are formed by the behaviors' actions further annotated with the behavior that just did the action, plus the special action reset.
      </list-item>
      <list-item label="3.">
       {a mathematical formula}ρ⊆2P×A′×2P, such that
      </list-item>
      <list-item label="4.">
       {a mathematical formula}S0={b10,…,bn0}, that is, the initial state of {a mathematical formula}D denotes that all available behavior are in their respective initial states, but also that behavior actions are not enabled (only a reset action can be executed initially).
      </list-item>
     </list>
     <paragraph>
      We next build, based on target behavior {a mathematical formula}T=〈T,A,t0,ϱt〉, the planning program {a mathematical formula}P for the dynamic domain {a mathematical formula}D above as {a mathematical formula}P=〈P,V,v0,δ〉, where
     </paragraph>
     <list>
      <list-item label="•">
       P is the set f propositions of the dynamic domain {a mathematical formula}D;
      </list-item>
      <list-item label="•">
       {a mathematical formula}V={t0,t1|t∈T}, that is the planning program has as states, the states of {a mathematical formula}T annotated with 0 and 1 (i.e., {a mathematical formula}P doubles the states of the target behavior {a mathematical formula}T);
      </list-item>
      <list-item label="•">
       {a mathematical formula}v0=t00, that is, the same initial state of {a mathematical formula}B0 annotated with 0;
      </list-item>
      <list-item label="•">
       δ is defined as follows:
      </list-item>
     </list>
     <paragraph>
      The key point is that the only way to satisfy {a mathematical formula}[true:Execreset,¬Execreset] involves the execution of a single action reset and to satisfy {a mathematical formula}[true:Execa,Execreset] we must use a single action within {a mathematical formula}{a1,…,an}. It is immediate to verify that if the planning program {a mathematical formula}P is PLAN-simulated by {a mathematical formula}D iff {a mathematical formula}T is simulated by the asynchronous product of {a mathematical formula}B1,…,Bn. Hence from the EXPTIME-hardness in [76] we get the EXPTIME-hard lower-bound for our case.  □
     </paragraph>
     <paragraph>
      Proof ofLemma 1(page 78). Termination is guaranteed because the number of possible open pairs that can be generated by the algorithm is finite, at every iteration of the external loop (lines 5–25) an open pair {a mathematical formula}〈s,v〉 is extracted from Open (line 6), and the number of times any open pair is added by steps 15 and 25 to Open is finite. The latter point holds because:
     </paragraph>
     <list>
      <list-item label="•">
       Step 15 never adds the same pair {a mathematical formula}〈s,v〉 to Open more than once, because it adds the pair to Open only if the end state s of the plan computed by {a mathematical formula}Plan for a realization d incoming to v is not in {a mathematical formula}States(v) (step 14); moreover, when {a mathematical formula}〈s,v〉 is added to Open, {a mathematical formula}States(v) is extended with s (step 16), and, when s is removed from {a mathematical formula}States(v), {a mathematical formula}Tabu(v) is extended with s (step 21–22), preventing the generation of any plan achieving s.
      </list-item>
      <list-item label="•">
       Step 25 adds a pair {a mathematical formula}〈s,v〉 to Open only if the realization of {a mathematical formula}〈s‾,v‾〉 fails, where {a mathematical formula}〈s,d〉∈Source(s‾,v‾) and d is a program transition from v to {a mathematical formula}v‾, and only if {a mathematical formula}〈s,v〉 becomes part of the realization frontier using Ω modified by removing the plan that realizes transition d. In the worst case, there exist {a mathematical formula}|V| transitions outgoing from v whose guard holds in s. Since we are assuming that the realization of {a mathematical formula}〈s‾,v‾〉 fails, at least one transition outgoing from {a mathematical formula}v‾ cannot be realized from {a mathematical formula}s‾. When the algorithm fails to realize such a transition, step 21 (permanently) adds {a mathematical formula}s‾ to {a mathematical formula}Tabu(v‾), and hence step 15 cannot add this pair again to Open. Therefore, the algorithm can realize transition d from state s at most {a mathematical formula}|S| times (the maximum number of different end states of a plan), and {a mathematical formula}〈s,v〉 is added to Open at most {a mathematical formula}|S|⋅|V| times.
      </list-item>
     </list>
     <paragraph>
      This guarantees that the condition of the external loop becomes false after a finite number of iterations and so that the algorithm terminates.  □
     </paragraph>
     <paragraph>
      Proof ofTheorem 6(page 78). Assume that the function Ω returned by the algorithm is not a valid realization for the input agent planning program {a mathematical formula}P. Then, by Definition 3, Definition 4, there exists at least one pair {a mathematical formula}〈s,v〉 reached when {a mathematical formula}P is executed according to Ω and a program transition {a mathematical formula}d=〈v,〈γ,ψ,ϕ〉,v′〉 with {a mathematical formula}s⊨γ such that either (1) {a mathematical formula}Ω(s,d)=noPlan, or (2) {a mathematical formula}Ω(s,d)=π and π does not maintain ψ or {a mathematical formula}last(π(s))⊭ϕ. Case (1) cannot hold because Ω is returned only if Open is empty and all pairs {a mathematical formula}〈s,v〉 that are reachable according to Ω are added to Open (steps 13–16), to be then removed from Open when (1.a) every transition d outgoing from v is either correctly realized by {a mathematical formula}Ω(s,d) or the guard of d does not hold in s, or (1.b) an outgoing transition whose guard holds in s cannot be realized. However, pair {a mathematical formula}〈s,v〉 cannot be removed from Open because of (1.a), since we are assuming that {a mathematical formula}Ω(s,d)=noPlan and {a mathematical formula}s⊨γ; {a mathematical formula}〈s,v〉 can neither be removed because of (1.b), since, when a transition outgoing from v whose guard holds in s cannot be realized from state s, Ω is set undefined for all {a mathematical formula}〈s″,d″〉 that are sources of {a mathematical formula}〈s,v〉 (steps 23–24), while we are assuming that {a mathematical formula}〈s,v〉 is reached when {a mathematical formula}P is executed according to Ω. Case (2) cannot hold because we are assuming that procedure {a mathematical formula}Plan is sound.  □
     </paragraph>
     <paragraph>
      Proof ofTheorem 7(page 78). Assume that there exists a realization Ω for {a mathematical formula}P, and let {a mathematical formula}〈s0,v0〉 be the initial open pair. For every transition {a mathematical formula}d=〈v0,〈γ,ψ,ϕ〉,v〉 outgoing from {a mathematical formula}v0 such that {a mathematical formula}s0⊨γ, there exists a plan π such that {a mathematical formula}s′=last(π(s0)), {a mathematical formula}Ω(s0,d)=π, π maintains ψ, and {a mathematical formula}s′⊨ϕ. By construction of {a mathematical formula}Tabu(v) in {a mathematical formula}RealizePlanProg (lines 18–21), {a mathematical formula}s′∉Tabu(v), since any domain state s can be in {a mathematical formula}Tabu(v) only if there exists a transition outgoing from v, with its guard holding in s, that cannot be realized from s, which, by Definition 4, cannot be the case for {a mathematical formula}s=s′. Since the usage of {a mathematical formula}Tabu(v) in subroutine {a mathematical formula}Plan prevents the generation of any plan reaching an end state {a mathematical formula}s∈Tabu(v), {a mathematical formula}s′∉Tabu(v), and {a mathematical formula}Plan can generate a valid plan for every solvable planning problem in the input domain ({a mathematical formula}Plan is complete), {a mathematical formula}Plan cannot generate failure when it realizes transition d from {a mathematical formula}〈s0,v0〉 (lines 10–11 of {a mathematical formula}RealizePlanProg). Thereby, in line 18 of {a mathematical formula}RealizePlanProg, {a mathematical formula}π≠failure when {a mathematical formula}〈s,v〉=〈s0,v0〉, and {a mathematical formula}RealizePlanProg cannot terminate returning failure (line 19). Then, by Lemma 1, {a mathematical formula}RealizePlanProg terminates returning a realization for {a mathematical formula}P.
     </paragraph>
     <paragraph>
      Assume that there exists no valid realization for the underlying planning program. By Lemma 1, {a mathematical formula}RealizePlanProg terminates. By Theorem 6, if {a mathematical formula}RealizePlanProg terminated returning a realization it would be valid, but this would contradict the assumption that there exists no valid realization. Thereby, {a mathematical formula}RealizePlanProg terminates returning failure.  □
     </paragraph>
     <paragraph>
      Proof ofTheorem 8(page 79). (1) Let π be a valid plan for Π. A valid plan {a mathematical formula}π′ for {a mathematical formula}Π′ can be obtained by appending to π action {a mathematical formula}Ignore-pref in {a mathematical formula}AP and, subsequently, a sequence of actions formed by one action in {a mathematical formula}Act-tabu(s) for each TES s. The goal ϕ of Π achieved by subplan π of {a mathematical formula}π′ remains satisfied at the end state of {a mathematical formula}π′ because actions in {a mathematical formula}AP and {a mathematical formula}AT do not delete any proposition in the proposition set P of the domain of Π. Action {a mathematical formula}Ignore-pref∈AP is executable at the end of subplan π, because its precondition {a mathematical formula}normal-mode holds in the initial state of {a mathematical formula}Π′, and it is not deleted by the actions in {a mathematical formula}A+ forming π; {a mathematical formula}Ignore-pref satisfies goal {a mathematical formula}check-pref of {a mathematical formula}Π′, because it is an additive effect of the action, and it is not deleted by the actions in {a mathematical formula}AT. Since π is a valid plan, for each TES s, {a mathematical formula}s≠last(π) holds, and hence there exists {a mathematical formula}p∈P such that either p is false in s and true in {a mathematical formula}last(π), or p is true in s and false in {a mathematical formula}last(π). Therefore, for each conjunct {a mathematical formula}g=not-tabu(s) of the achievement goal formula {a mathematical formula}ϕ′ of {a mathematical formula}Π′, there exists an action a in {a mathematical formula}Act-tabu(s) that is executable after the execution of {a mathematical formula}Ignore-pref in {a mathematical formula}last(π) and achieves g because (i) precondition {a mathematical formula}end-mode of a is added by {a mathematical formula}Ignore-pref and it is deleted by no action in {a mathematical formula}AT, and (ii) by construction of {a mathematical formula}AT, the other precondition of a holds in {a mathematical formula}last(π) and no other action in {a mathematical formula}AT can delete such a precondition. Moreover, plan {a mathematical formula}π′ maintains the maintenance goal ψ of Π and {a mathematical formula}Π′, because π maintains ψ and no action in {a mathematical formula}AP∪AT can make it false. It follows that there exists a valid plan solving the translated problem {a mathematical formula}Π′ that is formed by π followed by an action in {a mathematical formula}AP ({a mathematical formula}Ignore-pref) and a sequence of actions in {a mathematical formula}AT.
     </paragraph>
     <paragraph>
      (2) Since {a mathematical formula}π′ is a valid plan for {a mathematical formula}Π′, {a mathematical formula}ϕ′⊨ϕ and the actions in {a mathematical formula}AP and {a mathematical formula}AT do not add propositions of P, the subplan π of {a mathematical formula}π′ formed by the actions in {a mathematical formula}A+ satisfies the achievement goal of Π, as well as the maintenance goal of Π. Moreover, since {a mathematical formula}π′ is valid, for each TES s, plan {a mathematical formula}π′ contains at least one action {a mathematical formula}a∈Act-tabu(s) achieving conjunct {a mathematical formula}not-tabu(s) of goal formula {a mathematical formula}ϕ′. By construction of {a mathematical formula}AT and {a mathematical formula}Act-tabu(s), since all actions in {a mathematical formula}π′ are executable and the actions in {a mathematical formula}AP and {a mathematical formula}AT do not add/delete propositions of P, {a mathematical formula}last(π) must be different from any TES of Π. Hence, by removing precondition {a mathematical formula}normal-mode from the actions in {a mathematical formula}π′, we obtain a plan solving Π.  □
     </paragraph>
     <paragraph>
      Proof ofTheorem 9(page 80). (1) Let π be a valid plan for Π ending in a PES of Π. A valid plan {a mathematical formula}π′ for problem {a mathematical formula}Π′ such that {a mathematical formula}c(π′)=0 can be obtained by appending to π action {a mathematical formula}Sat-pref(s) and, subsequently, a sequence of actions formed by one action in {a mathematical formula}Act-tabu(s) for each TES s. Action {a mathematical formula}Sat-pref(s) preserves the maintenance goal of {a mathematical formula}Π′ and is executable at the end of subplan π, because {a mathematical formula}Sat-pref(s) has no effect in the proposition set of the domain of Π, precondition {a mathematical formula}normal-mode of {a mathematical formula}Sat-pref(s) holds in the initial state of {a mathematical formula}Π′ and is not deleted by the actions in {a mathematical formula}A+ forming π, and, since s is a PES of Π, by construction of {a mathematical formula}Sat-pref(s), the other preconditions of {a mathematical formula}Sat-pref(s) hold in {a mathematical formula}last(π). Moreover, {a mathematical formula}Sat-pref(s) satisfies conjunct {a mathematical formula}check-pref of the achievement goal formula {a mathematical formula}ϕ′ of {a mathematical formula}Π′, because it is an additive effect of the action, and it is not deleted by the actions in {a mathematical formula}AT. For each conjunct {a mathematical formula}g=not-tabu(s) of {a mathematical formula}ϕ′, there exists an action {a mathematical formula}a∈Act-tabu(s) that achieves g and is executable after the execution of {a mathematical formula}Sat-pref(s) in {a mathematical formula}last(π), because (i) precondition {a mathematical formula}end-mode of a is added by {a mathematical formula}Sat-pref(s) and is deleted by no action in {a mathematical formula}AT, and (ii) by construction of {a mathematical formula}AT, the other precondition of a holds in {a mathematical formula}last(π) and no other action in {a mathematical formula}AT can delete such a precondition. Moreover, every action in {a mathematical formula}Act-tabu(s) preserves the maintenance goal of Π and {a mathematical formula}Π′. Therefore, plan {a mathematical formula}π′ is valid, and, since the cost of every action of {a mathematical formula}π′ is zero, {a mathematical formula}c(π′)=0.
     </paragraph>
     <paragraph>
      (2) By Theorem 8, the subplan π obtained from {a mathematical formula}π′ by removing the actions in {a mathematical formula}AP and {a mathematical formula}AT and precondition {a mathematical formula}normal-mode is valid for Π. Since {a mathematical formula}c(π′)=0 and {a mathematical formula}π′ is valid, {a mathematical formula}π′ contains an action {a mathematical formula}Sat-pref(s) achieving the goal conjunct {a mathematical formula}check-pref of {a mathematical formula}ϕ′, for some PES s of Π. By construction of action set {a mathematical formula}A+ and action {a mathematical formula}Sat-pref(s), {a mathematical formula}Sat-pref(s) can be executed only as the first action after the end of subplan π. Moreover, by construction of {a mathematical formula}Sat-pref(s) and since {a mathematical formula}π′ is valid, subplan π must end in a PES of Π.  □
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Additional experimental results
     </section-title>
     <paragraph>
      Fig. C.1, Fig. C.2 show the CPU time and the program realization size of {a mathematical formula}RealizePlanProg using {a mathematical formula}LPG, {a mathematical formula}LAMA and Hplan-P with PESs for planning programs with domain Logistics and Pipesworld and δ equal to 1C[50], MC[26], RS[14] and CG[8] (s.t. {a mathematical formula}|δ| is about 50). The x-axis of the graphs in these appendixes refers to the program number (higher program numbers correspond to programs with domains that have larger sizes). Fig. C.3, Fig. C.4 show the CPU time and the program realization size for planning programs with instances of domain Elevators based on 9 objects, instances of domain Storage based on 25 objects, and δ equal to 1C[5-100], MC[4-51], RS[3-23] and CG[3-11] (s.t. {a mathematical formula}|δ| ranges from about 5 to 100). The x-axis of the graphs in these latter appendixes refers the number of program states. The fact that Hplan-P does not appear in a graph means that it realizes no planning program among those evaluated in the graph.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>