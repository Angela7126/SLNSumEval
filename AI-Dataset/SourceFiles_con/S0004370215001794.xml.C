<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    The scope and limits of simulation in automated reasoning.
   </title>
   <abstract>
    In scientific computing and in realistic graphic animation, simulation – that is, step-by-step calculation of the complete trajectory of a physical system – is one of the most common and important modes of calculation. In this article, we address the scope and limits of the use of simulation, with respect to AI tasks that involve high-level physical reasoning. We argue that, in many cases, simulation can play at most a limited role. Simulation is most effective when the task is prediction, when complete information is available, when a reasonably high quality theory is available, and when the range of scales involved, both temporal and spatial, is not extreme. When these conditions do not hold, simulation is less effective or entirely inappropriate. We discuss twelve features of physical reasoning problems that pose challenges for simulation-based reasoning. We briefly survey alternative techniques for physical reasoning that do not rely on simulation.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Computer simulations – broadly speaking, computations in which the trajectory of a temporally evolving system is traced in detail – have become ubiquitous. Programmers have created extremely detailed simulations of the interactions of 200,000,000 deformable red blood cells in plasma [51]; the air flow around the blades of a helicopter [46]; the interaction of colliding galaxies [3]; and the injuries caused by the explosion of an IED under a tank [59]. Software, such as NVidia PhysX, that can simulate the interactions of a range of materials, including rigid solid objects, cloth, and liquids, in real time, is available for the use of game designers as off-the-shelf freeware [31]. In artificial intelligence (AI) programs, simulation has been used for physical reasoning [28], [48], robotics [45], motion tracking [61], and planning [67].
     </paragraph>
     <paragraph>
      In cognitive psychology, likewise, simulation in a much broader sense has been proposed as the primary mechanism underlying physical reasoning, reasoning about other minds, language comprehension, and many other cognitive functions [43]. For instance, Kaup et al. [32] suggest that “creating simulations is necessary for [the] comprehension” of language, and Battaglia et al. [2, p. 18327] propose a model of physical reasoning based on an “intuitive physics engine,” a cognitive mechanism similar to computer engines that simulate rich physics in video games and graphics, but that uses approximate, probabilistic simulations to make robust and fast inferences. Similarly, Sanborn et al. [54] propose that “people's judgments [about physical events such as colliding objects] are based on optimal statistical inference over a Newtonian physical model that incorporates sensory noise and intrinsic uncertainty about the physical properties of the objects being viewed.”
     </paragraph>
     <paragraph>
      For many reasoning tasks, simulation is unquestionably a powerful tool and an intuitively appealing one; however, it is important to recognize its limitations. Here, we analyze the scope and limits of simulation as a technique of automated physical reasoning for general AI. (In a separate paper, we analyze corresponding limits in cognitive models [42].) We develop a categorization of tasks where simulation works well and is plausible as a reasoning mechanism; tasks where simulation does not work at all, and is therefore impossible as a reasoning mechanism; and tasks where simulation could work, but other techniques are likely to be more effective.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Computer simulation of physical systems
     </section-title>
     <paragraph>
      In a typical simulation, the input is a detailed description of an initial scenario. The program then uses the dynamic laws of the domain to extrapolate an equally detailed description of the state of the scenario a short time later. The program continues to extrapolate each state to the next state until some stopping condition is met. The program returns the entire trajectory of states as its prediction of what will happen. Table 1 shows a description of this process in pseudocode.
     </paragraph>
     <paragraph>
      For instance, consider a ball falling to the ground. In this simulation the initial state at a given time t is specified in terms of the height of the ball, {a mathematical formula}x(t), and its velocity {a mathematical formula}v(t), both measured upward. To extrapolate from one state at time t to the next state at time {a mathematical formula}t+Δ, we calculate that the height decreases by Δ times the current downward velocity, and that the downward velocity increased by Δ times the acceleration of gravity, denoted g.{a mathematical formula} The simulation stops when {a mathematical formula}x(t)≤0, since at that point the ball has hit the ground.
     </paragraph>
     <paragraph>
      Some simulations, such as assessments of the aerodynamics of airplanes, aim for high precision; they are extremely specialized in terms of both the physical phenomena and the kinds of scenario under consideration; and they involve immense computational burdens. Others, such as simulations used for real-time animation, particularly in video games, aim at plausible images rather than physical precision, often in real time on a personal laptop, rather than off-line on supercomputers.
     </paragraph>
     <paragraph>
      AI programs that deal with physical objects often use simulations, with good reason. Although numerous technical difficulties exist (many described below), simulation is conceptually and methodologically simple and comparatively straightforward to implement. Furthermore simulation can be used directly to produce a viewable animation, which is very helpful both for the end-user and for program development and debugging; moreover, physics engines of ever-increasing power, quality, and scope are publicly available for use. In some circumstances, they represent an ideal solution.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Simulation: challenges in automated systems
     </section-title>
     <paragraph>
      It is easy, however, for the non-expert to overestimate the state of the art of physical simulation, and assume that there is a plug-and-play physics engine that works for pretty much any physical situation. Although physics engines are now commonplace in video games, when it comes to the real-world, their fidelity is often quite limited; plug-and-play engines capture only narrowly-defined environments; more sophisticated applications require hard work from experts. A few seconds of realistic CGI in a disaster film may well require several person-days of work; an accurate and complex scientific computation may require several person-months. Nils Thuerey (personal communication) writes, There are... inherent difficulties with these simulations: we are still very far from being able to accurately simulate the complexity of nature around us. Additionally, the numerical methods that are commonly used are notoriously difficult to fine-tune and control. Plug-and-play physics engines are also subject to bugs and anomalies,{sup:1} and may require careful tuning to work correctly. In a systematic evaluation of seven physics engines, Boeing and Bräunl [4] found that all seven gave significantly and obviously erroneous answers on certain simple problems involving solid objects.
     </paragraph>
     <paragraph>
      In this section, we review twelve challenges that arise in the construction of simulations, some widely known, others less so; together, they help to articulate the scope and limits of when simulation can and cannot serve as an appropriate tool for automated physical reasoning.
     </paragraph>
     <section label="3.1">
      <section-title>
       The challenge of finding an appropriate modeling approach
      </section-title>
      <paragraph>
       The first hurdle in implementing a simulator is developing a domain model. In some cases, this is well understood. However choosing an appropriate model is often difficult, even for familiar objects, materials, and physical processes. The theory of physical systems that are changing temperature rapidly (“non-equilibrium thermodynamics”) currently has very large gaps{sup:2}; the theory of liquids and gasses also has significant gaps, including turbulence [7] and the interaction of flexible solids with liquids, such as occurs in swimming [56]. Within the theory of rigid solid objects, which are the simplest kinds of materials encountered in everyday activities, the analysis of collisions has not been wholly resolved [30], [58].
      </paragraph>
      <paragraph>
       Even in mundane situations, it may be challenging to find adequate models. Consider, for instance, cutting materials with tools. An ordinary household has perhaps a dozen kinds of tools for cutting: a few kinds of kitchen knives; more specialized kitchen equipment such as graters and peelers; a few kinds of scissors; a drill, a saw, a lawn mower, and so on. (A specialist, such as a carpenter or a surgeon, has many more.) Most people understand how they should be used and what would happen if you used the wrong tool for the material; if, for example, you tried to cut firewood with a scissors. But it would be hard to find good models for these in the physics or engineering literature.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       The challenge of discretizing time
      </section-title>
      <paragraph>
       Most simulation algorithms employ a discrete model of time{sup:3}: The timeline generally consists of a sequence of discrete instants; it is assumed that the system follows a uniform trajectory during the intervals separating the instants. In some instances, converting continuous physical time{sup:4} into a discrete model is unproblematic, but in a surprisingly broad range of problems, difficulties arise from this conversion.
      </paragraph>
      <paragraph>
       Consider, for example, the problem of choosing a proper time increment Δ in simulating rigid objects. If Δ is chosen too small, then many time steps must be calculated, increasing the computational burden. If Δ is too large, two objects may collide, interpenetrate, and pass through one another between one time point and the next. For instance, suppose that you are holding one compact disc (X) in the air, and you drop another (Y) directly on top of it from 1 meter above. By the time Y reaches X, it is traveling at a speed of about 4.5 m/sec. If the time increment is greater than a third of a millisecond, the collision will be missed (Fig. 1). As Boeing and Braunl [4] demonstrated, current physics engines are not immune to this kind of error.
      </paragraph>
      <paragraph>
       Alternatively, one can calculate exactly what is the time to the next collision or state change. But this kind of calculation can be extremely challenging.{sup:5}
      </paragraph>
      <paragraph>
       Discretizing time can also lead to more subtle problems. For instance if the simulation of a rigid pendulum uses a simple Euler method for the updating of the physical state from one time point to the next, the simulation will incorrectly predict that the pendulum swings back and forth a few times, reaching a higher angle on each swing, until eventually it rotates in a full vertical circle in one direction. A more sophisticated updating procedure is required to avoid this. In domains with richer physics than a pendulum, such as fluid dynamics, these kinds of problems can arise in much more complex forms [6], [23]. For instance, many basic methods for fluid simulation have the undesirable characteristic that the quantity of fluid in the system steadily decreases over time.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       The challenge of discontinuous dynamics
      </section-title>
      <paragraph>
       In some problems, a small change to the starting situation leads to a correspondingly small change in the overall trajectory. For instance, if you change the angle of a cannon by a small amount, the path of the ball changes only slightly. In other problems, two nearly identical starting situations can lead to significantly different behaviors. In these, enormous precision is required in both measurement and simulation to ensure an accurate answer. Consider the problem of a rolling die, which is the archetype of a physical process whose outcome is hard to predict, and in which slight differences in initial conditions can lead to entirely different outcomes. Although it is relatively easy to carry out an approximate computer simulation of a die rolling and to render it in an animation, it is extremely difficult to accurately predict the outcome of an actual roll of dice, even if the starting conditions are specified precisely [29].
      </paragraph>
      <paragraph>
       A related problem is that simulators can make predictions that are correct in a mathematical sense but impossible physically because of instability. For example, all seven simulators tested by Boeing and Bräunl [4] predicted incorrectly that if three spheres were dropped one exactly on top of the next, they would stack.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       The challenge of choosing an idealization
      </section-title>
      <paragraph>
       Virtually all simulations represent idealizations; in some, friction is ignored, in others three dimensions are abstracted as two. In most situations, many different idealizations are possible; and the idealization should be chosen so that, on the one hand, the calculation is not unnecessarily difficult, and on the other, the important features of the situation are preserved. Consider, for instance, the simulation of a pendulum on a string. If you are using an off-the-shelf physics engine, then you would use one of the idealizations that the engine supports. For example, a typical engine might model the bob as an extended rigid shape and model the string as an abstract constraint requiring that the distance between the objects tied at opposite ends not exceed a fixed length. In that case, simulating the pendulum would require you to specify the structure of the pendulum, the mass and shape of the bob, the length of the string, and the initial position and velocity of the bob. A student in freshman physics, by contrast, will probably approximate the bob as a point mass which is constrained to move on a circle of fixed radius; the resulting simulation will certainly be easier to carry out and quite possibly more accurate. However, to set up the simulation in this way, the student must understand the essential form of the behavior in advance, viz. that the string remains fully extended while the bob swings.
      </paragraph>
      <paragraph>
       Other scenarios are more complex. A bob may swing in a horizontal circle; spin on the axis of the string; rotate about its center of mass like a yo-yo, or fly through the air (Fig. 2). The string itself may be taut, loose, tangled, knotted, or twisted; it may get in the way of the bob; it may even unravel or snap. Although these behaviors are familiar to anyone who has spent time playing with objects on strings, few if any existing physics engines support any but the taut and loose conditions of the string and perhaps snapping.
      </paragraph>
      <paragraph>
       Efficient reasoning about these different possible behaviors of the string and the bob requires using a variety of different idealizations. Space can be two-dimensional or three-dimensional. A bob can be idealized as a point object, a rigid object, or an elastic object. A string of length L can be idealized as an abstract constraint restricting the motion of the bob; a one-dimensional curve of length L, with or without mass; or a three-dimensional flexible object, either uniform or with some internal structure (e.g. twisted out of threads or a chain of links.) Influence on the system can be limited to gravity, or can include friction and air resistance. In looking at any one simulation that has been well-worked out, it is easy to lose sight of how much careful work goes on in choosing the right idealization; as yet there is no algorithmic way to guarantee an efficient solution for arbitrary problems. Using the most realistic model possible is no panacea; highly realistic models both require more laborious calculation and more detailed information.
      </paragraph>
      <paragraph>
       Moreover, different high-quality physics engines can give radically difficult predictions for a single problem, particularly when the problem involves a device with feedback. Fig. 3, from [5] shows the paths calculated by three different physics engines for a submarine robot trying to follow a wall. These are radically different, even though, as Boeing and Bräunl emphasize, all three results come from “valid and accepted fluid simulation methods”.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       The challenge of rapidly drawing “easy” inferences
      </section-title>
      <paragraph>
       The output of a simulation is always precise,{sup:6} though not always accurate. Often, however, the reasoner has no need for the level of precision that a simulation provides. Consider, for example a child who has built a tower of blocks and is now planning to knock it over by hitting it with another block. The child does not generally need to know details of the final disposition of each individual block nor a probability distribution over possible final dispositions; it may suffice to know that the tower will fall with a satisfying clatter. Likewise if you ride a bicycle on a bumpy road while carrying a half-full closed water canteen, all that matters is that the water stays inside the canteen, not the trajectory of the water splashing inside the canteen. In such cases, fully detailed simulations seem like inefficient and inappropriate tools.
      </paragraph>
      <paragraph>
       There are many kinds of rules that allow quick inference or quick transference of results from a known situation to a new one. Invariance under time and space: If a mechanism worked in a particular way at home on Monday, it will work in the same way at work on Tuesday. Invariance under irrelevant changes: If a jar fits on a shelf, and you fill it with pennies, it will still fit on the shelf. Invariance under changes of scale (for certain physical theories, such as kinematics): A large pair of gears works in the same way as a much smaller scale model. Approximation: If a jug holds a gallon of water, then another jug of similar dimensions and shape will hold about a gallon. Ordering on a relevant dimension: If a toy fits in a box, then it will fit in a larger box, under a proper definition of “larger” [14]. Decomposition: If a system consists of two uncoupled subsystems, then one can reason about each separately.
      </paragraph>
      <paragraph>
       There can also be rules of thumb: useful generalizations for common cases. For instance, if you spill a cup of coffee in your office, it should not be necessary to resort to simulation to infer that the coffee will not end up in some other office. Rather, one can use a rule of thumb that a small amount of liquid dropped from a moderate “height onto a horizontal surface will end up not very far from the point where it was dropped, where “small amount”, “moderate height”, and “not very far” have some very approximate quantitative measurements.
      </paragraph>
      <paragraph>
       Moreover, these alternative forms of inference may do well under circumstances where simulation scales badly. Consider the following scenario: you put a number of objects in a box, close the lid, and shake it up and down violently. We now wish to infer that the objects are still in the box. Simulating the motion of the objects will become rapidly more complicated as the number of objects increases, the shapes of the objects become more complex, and the shaking of the box becomes more complex and violent. By contrast a single simple rule. “An object in a closed container remains in the container” suffices to carry out the inference.
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       The challenge of incorporating extra-physical information
      </section-title>
      <paragraph>
       In some cases, reasoning about a physical system can be carried out more reliably and effectively using extra-physical information. Suppose that you see a baseball pitcher throw a ball. If you simulate the motion of the ball, using the best information you can gather about the angle, velocity, and so on, of the ball when it left his hand, and factor in the imprecision of this information, you will predict that it has a rather low probability of ending up anywhere close to the batter. You would obtain better results – predicting that the ball will end up close to the strike zone, just inside it or just outside – by relying on the known accuracy of the pitcher, plus quite specific information about the state of play and the pitcher's willingness to risk an out-of-strike zone pitch rather than a hit.
      </paragraph>
     </section>
     <section label="3.7">
      <section-title>
       The challenge of incomplete information
      </section-title>
      <paragraph>
       Carrying out a physical simulation is generally only possible if the geometric and physical characteristics of the initial condition are known precisely. In many common real-world situations, reasoning must be carried out on the basis of partial, sometimes extremely limited, information. Perception may be imperfect or incomplete. For instance, an object may be partially occluded. (An opaque object always self-occludes its own far side from the viewer.) Knowledge of the physical situation may come from natural language text or sketches. Knowledge of aspects of the situation may come from inference; for example, if you see someone attempt unsuccessfully to pick up a suitcase, you can infer that the suitcase is unusually heavy; you can then use that inference for future prediction. Or the precise details may not have been determined yet. For instance, suppose that you are going to the furniture store to buy a dining room table. You can reason that you will not be able to carry it home on foot or riding a bicycle, even though you have not yet chosen a particular table.
      </paragraph>
      <paragraph>
       Of course, no representation is truly complete or entirely precise; in any representation, some aspects are omitted, some are simplified, and some are approximated. However, the simulation algorithm requires that the initial conditions of the scenario be fully specified relative to a given level of description. That is, the representational framework specifies some number of critical relations between entities and properties of entities. A complete representation of a situation relative to that framework enumerates all the entities that are relevant to the situation, and specifies all the relations in the framework that hold between those entities. The description must be detailed and precise enough that the situation at the next time step is likewise fully specified, in the same sense.
      </paragraph>
      <section label="3.7.1">
       <section-title>
        Limits to Monte Carlo simulation as an approach to partial knowledge
       </section-title>
       <paragraph>
        One common method for using simulations in situations with partial knowledge is to use Monte Carlo methods, or probabilistic simulation [26], [49]. Given a probability distribution over a space of physical situations, a program generates some large collection of specific situations following the distribution; it carries out a simulation based on each of these; and then it considers these behaviors as a random sample of the possible behaviors. Then for any particular proposition Φ of interest, the probability that Φ will be true in the actual situation can be estimated as the fraction of simulations in which Φ is true. Conditional probabilities can be computed in a similar way: to calculate the conditional probability {a mathematical formula}P(Φ|λ), generate random scenarios satisfying λ and find the fraction of these that satisfy Φ. This technique can be adapted to situations in which one starts with a set of constraints rather than a distribution by using a distribution that is, in some sense, uniform over the space of situations satisfying the constraints.
       </paragraph>
       <paragraph>
        For example, Battaglia et al. [2] consider a situation where an observer is looking at a tower of blocks, but has imperfect information; specifically, the perceived position of the block varies from the true position by an error that follows a Gaussian distribution. Their program uses this distribution to generate a collection of different towers, and simulates the behavior of each of these hypothetical towers. The probability that the true tower is stable is estimated as the fraction of simulations in which the tower remains stable. Conditional probabilities such as “the probability that the blue block and red block end up less than an inch apart, given that the tower falls over” can be estimated by generating random towers, selecting those in which the tower falls over, and then, within that restricted set, considering the fraction in which the blue block and red block end up less than an inch apart.
       </paragraph>
       <paragraph>
        Probabilistic simulation can often be effective, but it has its own problems. First, the concept of a random shape is problematic. If you know that a block is a rectangular solid, then you can reasonably specify the distributions of its length, width, and height as distributions of some standard form (e.g. Gaussians), or collectively as a joint distribution. However, if you have imperfect knowledge of the shape of the blocks, then it is much less clear how to proceed. There does not seem to be any natural probability distribution over the class of all shapes.
       </paragraph>
       <paragraph>
        Second, Monte Carlo simulation runs the risk of missing scenarios that are important and possible, though improbable. Suppose, for example, that you are standing underneath a scaffold next to a building, and you observe that a tool on the scaffold is precariously balanced. You wish to know whether you are safe, so you carry out a number of simulations of the tool falling off the scaffold. If the tool does not hit you in any of them, you conclude, erroneously, that there is no need to worry.
       </paragraph>
       <paragraph>
        Third, the calculation of the conditional probability {a mathematical formula}P(Φ|λ) relies on generating random elements satisfying λ. However, if λ is only rarely satisfied, it may be difficult to generate these. For instance, suppose that you see a nut in a bolt, and you have reliable information that the nut fits properly in the bolt (that is, after all, a safe default assumption when a nut is on the bolt). You cannot, however, see the threads of either. You wish to infer something about the number of turns needed to remove the nut from the bolt; almost certainly greater than half a turn and almost certainly less than 50 turns. That is, you want to estimate {a mathematical formula}P(Φk|λ) where {a mathematical formula}Φk is the proposition, “It will require exactly k turns to remove the nut from the bolt” and λ is the proposition, “The nut fits on the bolt”.
       </paragraph>
       <paragraph>
        If you sample random shapes for the nut and the bolt separately, then you will never come across a pair in which the nut fits on the bolt; and if you have no samples for λ, you certainly cannot estimate {a mathematical formula}P(Φk|λ). Rather, you must generate the shapes for the nut and bolt concurrently. But at this point you need a quite specialized Monte Carlo shape generator that can generate fitting nuts and bolts simultaneously. If the generator is to be created by the automated reasoner, and not supplied by a human programmer, then that in itself would require powerful spatial and physical reasoning capacities that can hardly be the product of unaided simulation. (The problem of generating distributions corresponding to low-probability distributions is central to the implementation of probabilistic programming languages such as Church [22]; but it is not clear how well the techniques used there will adapt to the geometric and physical constraints involved in the kinds of examples were considering here.)
       </paragraph>
       <paragraph>
        Finally, the assumption that ignorance can always be characterized in terms of a probability distribution is inherently questionable. There is often no particularly reasonable or well-motivated way to assign probabilities to alternatives if these arise simply from ignorance of what is going on. The engineering literature (e.g. [1]) makes the useful distinction between aleatory uncertainty (i.e. uncertainty due to chance) and epistemic uncertainty (uncertainty due to ignorance); and caution is advised in assuming that it is meaningful to apply probabilistic methods to epistemic uncertainty.
       </paragraph>
      </section>
      <section label="3.7.2">
       <section-title>
        Reasoning with incomplete information about containers
       </section-title>
       <paragraph>
        One important domain of physical reasoning where reasoning with incomplete information is both common and effective is in reasoning about containers – boxes, bottles, cups, bags, and so on – and their contents [15]. Containers are ubiquitous in everyday life, and children learn to use containers at a very early age.
       </paragraph>
       <paragraph>
        A container can be made of a wide range of materials: rigid materials, paper, cloth, animal body parts, or combinations of these. The only requirement is that the material should maintain its shape to a sufficient degree that holes do not open up through which the contents can escape. Under some circumstances, one can even have a contained space whose bottom boundary is a liquid; for instance, an insect can be trapped in a region formed by the water in a basin and an upside-down cup. It can also have a wide range of shapes. The only constraint on the shape of a closed container is that there exists an internal cavity. The only constraint on an open container is that the material of the container plus a horizontal surface at its top delimit an internal cavity. Either a closed or an open container may additionally have small holes that penetrate from inside to outside e.g. a cage or a sieve.
       </paragraph>
       <paragraph>
        The material of the contents of a container is even less constrained. In the case of a closed container, the only constraint is that the material of the contents cannot penetrate or be absorbed into the material of the container (e.g. you cannot carry water in a paper bag or carry light in a cardboard box); and that the contents cannot destroy the material of the container (you cannot keep a gorilla in a balsa wood cage). Using an open container requires additionally that the contents cannot fly out the top [13]. Using a container with holes requires that the contents cannot fit or squeeze through the holes.
       </paragraph>
       <paragraph>
        Those are all the constraints. In the case of a closed container, the material of the contents can be practically anything.
       </paragraph>
       <paragraph>
        If the only goal is to infer that the object remains inside the container, then simulation is at best extremely inefficient and at worst essentially impossible. Suppose, for example, that you have an eel inside a closed fish tank and you wish to infer that it remains in the tank. If we are to solve this problem by probabilistic simulation, we would need, first to understand how an eel swims, and second to simulate all kinds of possible motions of the eel and confirm that they all end with the eel inside the tank. If we do not know the mechanisms of swimming in eels, then the only way to use probabilistic simulation is to generate some random distribution of mechanisms that eels might use. Clearly, this is not plausible.
       </paragraph>
       <paragraph>
        Another, similar example: You pack a shirt in a suitcase, you lock the suitcase, you check it onto a flight to Chicago. The suitcase is lost. Three days later, it turns up at the Dallas airport. It's pretty banged up, but intact. Who knows what they did to it or how it got there. However, if it's still locked, you can be sure that the shirt is still inside. In this case, it is impossible to effectively simulate because there is no information about the exogenous events involved.
       </paragraph>
      </section>
      <section label="3.7.3">
       <section-title>
        Reasoning with incomplete knowledge about people, animals, and robots
       </section-title>
       <paragraph>
        Much of the physical reasoning that is important for any intelligence, natural or artificial, has to do with the physical capacities and limitations of physical agents that can move autonomously – people, animals, or robots. In animals, especially, capturing prey and evading predators is one of the most important functions of cognition.
       </paragraph>
       <paragraph>
        There is at this point a large industry in developing simulators both for robots, to help in planning and to lower costs of testing [34], [38], and for various aspects of human activity and human physiology, mostly for medical purposes [40]. However, these require detailed knowledge of (generally very complex) physical characteristics of the creature. Moreover, if one wants to simulate how the creature will behave, then it is additionally necessary to simulate its perception and possibly also the control feedback that connects perception to action.
       </paragraph>
       <paragraph>
        For example, suppose that a machine reading program wishes to understand the following short text (from the Wikipedia article on “Camoflague”) Some animals, such as the Horned Lizards of North America, have evolved elaborate measures to eliminate shadow. Their bodies are flattened, with the sides thinning to an edge; the animals habitually press their bodies to the ground; and their sides are fringed with white scales which effectively hide and disrupt any remaining areas of shadow there may be under the edge of the body. The reader can perhaps simulate the appearance of the sunlit lizard on the ground, and understand how this results in there being no visible shadow. However, to understand the passage, one also has to understand why it is important not to cast a shadow; which requires understanding that an implicit predator, of entirely unspecified characteristics, would be able to detect the presence of the lizard, and catch and eat it, if it saw the shadow, but will not detect the presence and therefore cannot catch it if there is no shadow. One could perhaps simulate that as well, but obviously the reasoning needed to figure out that this simulation is relevant and to set up the simulation is much more complex than the simulation itself.
       </paragraph>
      </section>
      <section label="3.7.4">
       <section-title>
        The physical dynamics of unknown entities
       </section-title>
       <paragraph>
        Suppose that you are walking along the beach and you see an oddly shaped green object. The object has a cavity at the top, and inside the cavity is some white stuff. You want to know what will happen if you try to lift the green thing, putting one hand on either side.
       </paragraph>
       <paragraph>
        Since you have no idea what the green thing or the white stuff is, you obviously cannot predict very much about this. Still you are not entirely at a loss for conclusions to draw. It is very unlikely that picking up the green thing will cause the white stuff to fly up twenty feet into the air or will cause a large sinkhole to appear under your feet. It is impossible that the green thing will turn out to be a mountain or that the white stuff will turn into a canary.
       </paragraph>
       <paragraph>
        With some more observation, further conclusions can be drawn. If the green thing has sharp edges, then it is probably not soft or malleable, and therefore is likely to preserve its shape when you pick it up, unless it consists of multiple pieces, in which case you might be able to see cracks between the pieces. If the white stuff has a horizontal top surface and fills the cavity below the top surface, then it may well be a liquid. Simulation-based reasoners cannot readily draw these sorts of inferences.
       </paragraph>
      </section>
     </section>
     <section label="3.8">
      <section-title>
       The challenge of irrelevant information
      </section-title>
      <paragraph>
       In physical reasoning, as in most forms of reasoning, it is important to focus on the relevant aspects of the situation and ignore the irrelevant.
      </paragraph>
      <paragraph>
       In modeling and simulation, irrelevancies are generally excluded manually. The human being who sets up the simulation formulates the problem in terms of the relevant features and ignores the irrelevant ones. However, this expedient will not do for a general AI program or a cognitive theory. There must be a well-defined process to exclude irrelevant information in physical reasoning, and it is hard to see how this exclusion process itself can rely on simulation.
      </paragraph>
      <paragraph>
       Suppose for example that you are eating a picnic in the middle of a country fair. You are pouring lemonade from a thermos, while all around you the fair is bustling; the Ferris wheel is turning, carnival touts are barking, hot dog vendors are grilling hot dogs and so on. In most cases, in reasoning about pouring the lemonade, you can safely ignore all this other activity.
      </paragraph>
      <paragraph>
       As a second example, let us return to the problem of automatically generating samples of nuts and bolts discussed in Section 3.7. Suppose that you have some irrelevant information about the shape of the bolt: it is a regular heptagon and the manufacturer's monogram is engraved on one side. If this is included as part of the given information λ, then the problem of generating random samples satisfying λ becomes that much harder.
      </paragraph>
     </section>
     <section label="3.9">
      <section-title>
       The challenge of range of scales
      </section-title>
      <paragraph>
       Consider the following scenario. At night, you look up at the Little Dipper, and see Polaris, the North Star. However, if you close your eyes, then you don't see Polaris.
      </paragraph>
      <paragraph>
       How do we know this? Although in principle it would be possible to compute this using a physics engine, in practical terms, such an approach is wildly unwieldy. The natural way to use simulation to understand this scenario is to simulate a photon being emitted in a random direction from Polaris, and then keep simulating until you have a respectable collection of photons that meet the pupil of the observer. (A minimum of three photons are needed just to get the correct color.) The trouble derives from the scales involved. You see Polaris at its observed brightness and color because every 100 ms, about 500,000 photons from Polaris reach your pupil. Polaris is 433 light-years away, so these were emitted in 1580 AD. The probability that a particular photon emitted from Polaris will meet one particular 1 cm{sup:2} pupil is about {a mathematical formula}3×10−42; even with high-speed computers, it is not practical to compute this by tracking individual photons over such vast scales.{sup:7}
      </paragraph>
      <paragraph>
       Less straightforward solutions that still depend primarily on simulation raise their own complications. Suppose that we can avoid that problem of probabilistic simulation and directly generate a simulation of a photon that starts at Polaris and travels in a straight line to the eye. This involves the problem of interpolating a simulation with constraints at multiple time points, discussed in the next section. Even so, the problem of discretizing time remains. If we discretize time into equal time-steps, then to detect the interaction of the photon with the 1 mm thick eyelid would require a time step of {a mathematical formula}10−11 seconds, and therefore about 10{sup:20} time steps would be needed to span the 400 years. In all but one of these time steps, the photon moves forward 1 millimeter through empty space or the atmosphere. Clearly this is not feasible. Rather the simulation must represent only the time points when something interesting happens. One can preserve a small role for simulation, but most of the work then goes into decide what to include in the simulation; executing the simulation is providing at most a very small final piece in the puzzle.
      </paragraph>
      <paragraph>
       Of course, there is no difficulty in computing the appearance of the night sky; simple astronomy programs can do that. The difficulty is in integrating this with reasoning about objects that might interfere with passage of light. For example, an astronomy student should be easily able to determine, or infer, that if he closes his eyes, he will not see Polaris; that an mile-wide asteroid in the asteroid belt could occlude a star, but only for a fraction of a second; that a mile-wide object orbiting Polaris would not occlude Polaris, and so on.
      </paragraph>
      <paragraph>
       Reasoning that integrates wide ranges of scales is common in science. Stellar evolution is related to nuclear reactions; this involves a mass ratio of about 10{sup:57}. Species evolution is related to genes; this is a factor of about 10{sup:34}. Everyday life also involves scale ratios that are large, though not astronomical. You are setting out for a trip to California of 3000 miles, and you turn the keys in the ignition through a distance of 1 cm; this is a ratio of {a mathematical formula}5×108. A soldier is hit by a bullet in an event taking {a mathematical formula}10−3 seconds and carries it for the rest of his 70 year lifetime; this is a factor of {a mathematical formula}2×1012.
      </paragraph>
      <paragraph>
       Specialized simulation techniques have been developed that can deal with a wide range of scales; for example Vogelsberger et al. [60] described a simulation of cosmological evolution that spans 6 orders of magnitude in linear dimension, from 100 megaparsecs to 48 parsecs. But it should be possible to carry out the simple inferences described above without calling on this very sophisticated, very computationally demanding technology.
      </paragraph>
     </section>
     <section label="3.10">
      <section-title>
       The challenge of tasks other than prediction
      </section-title>
      <paragraph>
       For example, if an object is blown away by a gentle wind, a human reasoner can readily infer that it is a light object. Few simulation systems are set up to derive this sort of inference.Design:Construct an object to achieve a specified functionality. Suppose, for instance, you want to design a terrarium for your pet toad that will sit on the window sill. One can immediately infer a number of constraints; it can't be completely closed, or the toad will suffocate; it can't be open on top, or the toad will jump out; it must be possible to get food and water to the toad and clean the terrarium; it needs to have a flat bottom; it needs to fit on the shelf; and so on. These constraints must be derived before the design and dimensions of the terrarium can be chosen or simulated.Comparative analysis:How does a modification to a problem affect the solution? For instance, you can reason that if you make an object heavier, then it will become more difficult to lift. This inference can be done without knowing the actual weight of the object [16].
      </paragraph>
     </section>
     <section label="3.11">
      <section-title>
       The challenge of the frame problem
      </section-title>
      <paragraph>
       Simulation theories, might at first blush seem to be immune to the so-called frame problem – of efficiently reasoning about the aspects of a situation that do not change over time– that has often bedeviled knowledge-based theories [44]; in reality, the frame problem arises in simulation in very much the same ways and to the same extent as in knowledge-based theories, avoidable in simple cases [55], [52], daunting in many more complex cases.
      </paragraph>
      <paragraph>
       An example of a case where simulation runs into the frame problem is as follows. Consider a situation where there are two stable towers of blocks on the ground with a substantial space between them, tower A and tower B. You now drop a block onto tower A. It is immediately obvious to a human onlooker that whatever happens in tower A, tower B will be unaffected. To determine this, a physics engine, such as we discuss in Sections 2 and 3, would need compute all the forces between blocks in tower B, and calculate that the net force and net torque on each block is zero. Moreover, in order to accurately predict how tower A will collapse, the engine would need to use a very fine discretization of time with many time steps; and it would need repeat this identical calculation over tower B at each time step. The key hallmark of the frame problem here is the needless repetition of the calculation that nothing in tower B changes; in particular categories of cases, it may be possible to recognize that this part of the situation is repeated, and to retrieve the previous results rather than redo the calculation; but as the situation becomes more complicated, this rapidly becomes increasingly difficult to do.
      </paragraph>
     </section>
     <section label="3.12">
      <section-title>
       The challenge of using common sense to check simulations
      </section-title>
      <paragraph>
       As we have seen, technical problems in simulations can give results that are not merely wrong in detail, but physically nonsensical. If the wrong time increment is used in simulating solid objects, the simulation can predict that one object passes through another. If a simulation of a pendulum uses the wrong updating rule, it will predict that the pendulum swings higher and higher (Section 3.2).
      </paragraph>
      <paragraph>
       If there is a human in the loop, they can examine the output of the simulator and at least see that this cannot be right, particularly if the simulator outputs an animation. If there is no human in the loop, then it would be very desirable for the physical reasoning system to be able to detect these kinds of problems by itself. If the simulation is the only reasoning mechanism, this cannot be done.
      </paragraph>
      <paragraph>
       There have been a number of reasoning systems that uses qualitative reasoning to exclude Modelica or Matlab simulations with nonsensical outcomes [33].
      </paragraph>
     </section>
     <section label="3.13">
      <section-title>
       Summary
      </section-title>
      <paragraph>
       Simulation is effective for automated physical reasoning when the task is prediction, when complete information is available, when a reasonably high quality theory is available, and when the range of scales involved, both temporal and spatial, is not extreme. If these conditions do not hold, then simulation becomes to some extent problematic. We have identified many categories of problems where these conditions do not hold, and demonstrated by examples that these categories include many natural and simple examples.
      </paragraph>
      <paragraph>
       Furthermore, even when these conditions do hold, there may be simpler approaches either based on other kinds of physical knowledge or based on non-physical knowledge.
      </paragraph>
      <paragraph>
       Probabilistic simulation can be effective when a plausible probability distribution can be posited, and when it is easy to generate a random sample of instances satisfying the known constraints. In many cases these conditions are not met. If the given information is too weak, as in the cases of objects of unknown shape or material, then there may be no natural probability distribution. If a complex constraint is known, as in the case of the screw and bolt that fit together, then it may be difficult to generate a random sample satisfying the constraint.
      </paragraph>
      <paragraph>
       Table 2 enumerates the categories of challenges we have discussed, and reviews the examples.
      </paragraph>
      <paragraph>
       Some of these problems are well-discussed in the literature of modeling and simulation; others not. The problems of finding a dynamic model, of discretizing time, and of discontinuity are discussed very extensively; these are central issues in the theory of modeling and simulation, and there is a large technical literature that addresses them. The problems of choosing an idealization and of checking that simulations make sense are discussed, but generally in informal terms e.g. [53], [66]. The problems of incomplete information, irrelevant information, range of scale, non-predictive tasks, and the frame problem have been examined only to a limited degree, and the technical literature within the theory of modeling and simulation is small.{sup:9} The issues of easy inference or of inference from non-physical information are hardly discussed. For simulation to serve as a general solution to the problem of physical reasoning, in either human or automated form, all would need to be solved. At present, no actually implemented automated system has come close.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Alternatives to simulation
     </section-title>
     <paragraph>
      What alternatives are there? One possibility is a knowledge-based reasoning engine in which both the knowledge of the domain physics and the problem specifications are largely declaratively expressed. Several different aspects of knowledge-based physical reasoning have been developed in the AI literature (see [12] for an overview):
     </paragraph>
     <list>
      <list-item label="•">
       Symbolic reasoning based on a theory of the physical domain. The theory may be composed of valid qualitative rules such “An object inside a closed container remains inside.” [24], [25], [10], [13]; or it may be an “intuitive” or “naïve” theory such as an impulse theory of motion.
      </list-item>
      <list-item label="•">
       Qualitative reasoning: A collection of algorithms developed for reasoning about relative size of physical quantities and direction of change [19], [36], [65]. For instance, these algorithms support the qualitative inference that, if two objects at different temperatures are in thermal contact, then heat will flow from the hotter to the colder until they reach the same temperature.
      </list-item>
      <list-item label="•">
       Reasoning by analogy [21]. For instance the analogy between pressure and flow in hydraulic systems to voltage and current in electronic systems allows the reasoner to conceptualize electric circuits in terms of water flow, which is more familiar.
      </list-item>
      <list-item label="•">
       Meta-level reasoning; reasoning explicitly about the structure and use of theories [39], [19], [36], [18], [62], [63], [47]. For instance, one can use a rule that states that the theory of rigid solid objects will suffice to describe wooden blocks in the context of a child playing, but not in the context of architecture.
      </list-item>
     </list>
     <paragraph>
      These different approaches are largely complementary rather than in opposition; they deal with different aspects of reasoning; a complete theory would presumably involve integrating these, together with further techniques for other issues that have not yet been addressed.
     </paragraph>
     <paragraph>
      Qualitative reasoning has been by far the most extensively studied, and achieved some notable successes, e.g. in text understanding, [35] and analogical mapping and geometric reasoning [41]. The Flame system [50] for failure mode and effects analysis in automotive electrical systems has been used by multiple companies for years. Fromherz et al. [20] discuss a system for automatically generating model-based control strategies for high-end printing systems.{sup:10} Other suggestive analogues in other forms of reasoning include non-simulative planning methods such as partial-order planning [8], [64] and hierarchical planning [17] and on symbolic reasoning for verification of computer software [9], such at the software that controls complex physical systems such as airplanes [57]; the latter inherently combines physical reasoning with complex logical reasoning.
     </paragraph>
     <paragraph>
      Highly trained physical reasoning, such as catching a fly ball or predicting the trajectory of a billiard ball with spin, probably also involves interpolation from a database of stored examples, derived from personal experience combined with using a tight perception-action feedback loop, learned using reinforcement learning or some similar strategy.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>