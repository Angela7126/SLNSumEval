<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Modelling structured societies: A multi-relational approach to context permeability.
   </title>
   <abstract>
    The structure of social relations is fundamental for the construction of plausible simulation scenarios. It shapes the way actors interact and create their identity within overlapping social contexts. Each actor interacts in multiple contexts within different types of social relations that constitute their social space. In this article, we present an approach to model structured agent societies with multiple coexisting social networks. We study the notion of context permeability, using a game in which agents try to achieve global consensus. We design and analyse two different models of permeability. In the first model, agents interact concurrently in multiple social networks. In the second, we introduce a context switching mechanism which adds a dynamic temporal component to agent interaction in the model. Agents switch between the different networks spending more or less time in each one. We compare these models and analyse the influence of different social networks regarding the speed of convergence to consensus. We conduct a series of experiments that show the impact of different configurations for coexisting social networks. This approach unveils both the limitations of the current modelling approaches and possible research directions for complex social space simulations.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In most simulations of complex social phenomena, agents are considered to inhabit a space in which structure is very simple. This space has little resemblance with the social world it is supposed to depict and for which conclusions are supposed to be extrapolated. This simplicity does not come by chance, rather, it is necessary and desired by the researchers: the problems to be approached are themselves so complex that whichever factors of complexity can be reduced (or at least postponed), the reduction is always welcome. So, it is common practice that geographical space is reduced to a two-dimensional grid, and all social relations between agents are condensed into one more or less structured abstract relation. Most social simulation and modelling approaches disregard the fact that we engage in multiple social relations. Moreover, each kind of social relation can possess distinctive characteristics that include: rich information such as degree of connectivity, centrality, trust, interactions frequency, asymmetry, and so on.
     </paragraph>
     <paragraph>
      To explore the addition of multiple relations and its consequences for the dissemination of phenomena in social simulations, we put forward to reduce the emphasis given on agent individual interactions. We accomplished this by choosing a simple – and especially neutral – game to model those interactions. Our main concern was that the game itself would not provide biases or trends in the collective phenomenon being studied, so we chose the consensus formation game, with a straightforward majority rule to decide the outcome of each individual move.
     </paragraph>
     <paragraph>
      While most models are simplified descriptions – reductions – of real-world phenomena, many constitute complex systems themselves and thus, we need techniques such as simulation to explore their properties. We can make a distinction between two types of complexity: the complexity of real systems (ontological complexity) and the complexity of models (descriptive complexity) [1]. The levels of abstraction in a simulation model can then range from data-driven paradigms to more abstract descriptions that allow us to create what-if-scenarios. The study of this abstract descriptive complexity in simulation models is as valuable as its data-driven counterpart. We may not be able to make predictions based on the direct application of such models; but, their study can inspire the engineering of artificial complex systems and reveal properties with applications beyond the explanation of observable phenomena. Studying consensus formation can thus advance our understanding of related real-world social phenomena.
     </paragraph>
     <paragraph>
      Examples of thematic real-world phenomena in social simulation models include for instance the joint assessments of policies or, in the context of economics and politics, the voting problem. Herbert Simon's investigations on this problem were one of the first stepping stones to the field of social simulation [2]; which then inspired models (like the one we present in this article) related to evolution and dissemination of opinions, which we call opinion dynamics. In agent-based opinion dynamics, agent interactions are guided by social space abstractions. In some models, the dimensionality and structure of this space is irrelevant (any agent can interact with any other agent). Other models use an underlying artefact that structures agent neighbourhoods. Axelrod for instance, represents agent neighbourhoods as a bi-dimensional grid in its model of dissemination of culture[3]. In an attempt to mimic real social systems, one can also make use of complex network models to create the infrastructure that guides agent interaction (see [4] for an example).
     </paragraph>
     <paragraph>
      In real-world scenarios, actors engage in a multitude of social relations different in kind and quality. Most simulation models don't explore social space designs that take into account the differentiation between coexisting social networks. Modelling multiple coexisting relations was an idea pioneered by Peter Albin in [5] but without further development. The process of interacting in these different complex social dimensions can be seen as the basis for the formation of our social identity [6], [7].
     </paragraph>
     <paragraph>
      In this article, we explore the modelling of opinion dynamics with multiple social networks. We look at how the properties of different network models influence the convergence to opinion consensus. We present a series of models that use these networks in different ways: which create distinct emergent dynamics. We want to study the consequences of using multiple social networks at the same time while maintaining the interaction model as simple and abstract as possible (following the methodology in most opinion dynamics literature). We present two models where agents can: interact at the same time in the multiple networks (choosing partners from any network); or switch between networks (choosing only partners from their current network).
     </paragraph>
     <section label="1.1">
      <section-title>
       Article structure
      </section-title>
      <paragraph>
       This article is organised as follows. In the next section, we present the work related to opinion dynamics, social space modelling and complex network models. In the following section, we describe our game of consensus and introduce our multiple model variations. These are designed to study the notion of context permeability and consensus formation in multiple social networks. Section 4 describes the experimental setup; the set of tool and methodologies followed to conduct our investigations. In Section 5, we present and discuss our results and compare the different simulation models. Finally, we summarise what we learned from our experiments and point out future research directions.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section, we present work related to opinion dynamics, social space modelling, and complex network models.
     </paragraph>
     <section label="2.1">
      <section-title>
       Opinion dynamics and consensus formation
      </section-title>
      <paragraph>
       Formal opinion dynamics models provide an understanding, if not an analysis, of opinion formation processes. An early formulation of such models was created as a way to understand complex phenomena found empirically in groups [8]. The work on consensus building (in the context of decision-making) was first studied by DeGroot [9] and Lehrer [10]. Empirical studies of opinion formation in large populations have methodological limitations. Computational sociology arises with a set of tools – simulation models in particular – to cope with such limitations. We use multi-agent simulation (MAS) as a methodological framework to study such social phenomena in a larger scale. Most opinion dynamics models make use of binary opinion values [11], [12], or continuous values [13], [14]. For a detailed analysis over some opinion dynamics models, refer to [15].
      </paragraph>
      <paragraph>
       Opinion dynamics models allow us to discover under which circumstances a population of agents reaches consensus or polarisation. Agent-based models can have broader application outside social simulation though. In computational distributed systems, consensus is a means by which processes agree on some data value needed during computation. Typically, this agreement is the result of a negotiation process (often with the aid of a mediator). In human societies, social conventions emerge to deal with coordination and subsequently with cooperation problems [16]. These conventions are regularities of behaviour that can turn normative if they come to be persistent solutions to recurrent problems. MAS are also capable of producing emergent conventions in coordination or cooperation problems [17]. The decentralised nature of these computational models of consensus is highly desirable for dynamic control problems. In these scenarios, creating conventions before hand (off-line), or developing a central control mechanism for generating them, can be a difficult and intractable task: either due to the uncertainty and complexity associated with the environment, or due to the system scale and heterogeneity (which makes it very difficult to handcraft each component).
      </paragraph>
      <paragraph>
       Consensus models are also investigated as means to create conventions in MAS. Shoham and Tennenholtz create a bridge between economic literature and machine learning by studying a series of models in which multiple agents are engaged in learning a particular convention [18]. They call this process co-learning. The complexity of these systems comes from its concurrent nature: one agent adapts to the behaviour of another agents it has encountered, these other agents update their behaviour in a similar fashion, which results in a highly non-linear system dynamics. In their work, Shoham and Tennenholtz define the notion of stochastic social games and compare different rules with the objective of establishing conventions in a decentralised fashion. In their stochastic games, they present one particular rule that we use in our models:
      </paragraph>
      <paragraph label="Definition 1">
       External Majority (EM) update rule: adopt action i if so far it was observed in other agents more often than other action and remain with your current action in the case of equality.
      </paragraph>
      <paragraph>
       This EM rule was shown to coincide with Highest Cumulative Reward (HCR), which is a simple rule that states that “an agent should adopt an action that has yielded the highest cumulative reward to date.” We use the EM rule in our simulation models for its simplicity and success in the evolution of conventions.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Social structure in simulation models
      </section-title>
      <paragraph>
       The usage of a bi-dimensional grid to represent abstract social spaces in simulation models, is one of the most widely used approaches in the agent-based simulation and modelling literature. This has its origins in the “checkerboard” model introduced in computational social sciences by Schelling and Sakoda [19], [20]. Another famous example that uses bi-dimensional grids as social structure is the social simulation model of dissemination of culture from Axelrod [3].
      </paragraph>
      <paragraph>
       Cellular automata (CA) are an example from the area of artificial life that also makes use of bi-dimensional structures to model neighbourhood interactions. While these models are idealised frameworks, their exploration can bring us deeper insights than models with high level of descriptive complexity (which would render their analysis very difficult). The work of Flache and Hegselmann relaxes the standard CA assumptions about the regular bi-dimensional grids by considering irregular grid structures (Voronoi diagrams) [21]. They present results on the robustness of some important general properties in relation to variations in the typical grid structure. There are also contributions that incorporate both the complexity of network models and the behaviour of dynamic processes. One example is the work in [22], which explores a graph-based cellular automaton to study the relationship between spatial forms of urban systems and the robustness of different process dynamics under spatial change. Moreover, this shows how we can use real geographical information to construct graph-based cellular automata (thus making a connection between purely abstract models and data-driven models).
      </paragraph>
      <paragraph>
       Finally, another type of social space models are the random graph/network models. Each complex network – or class of complex networks – captures specific topological properties. These properties are found in real-world network structures. One of the first complex network models is the random graph from Erdős and Rényi [23]. Other examples include the model of preferential attachment [24], and the small-world networks [25]. One common issue of these models is the fact that once generated, the network structure is static. The models are not really suitable for the description of highly dynamic groups or communities. An example of a model that takes such dynamics into account is the model of team formation in [26]. A more in-depth review of network models (and their properties) is given in [27].
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Multi-context models
     </section-title>
     <paragraph>
      In this section, we present our modelling approach to explore the concept of permeability between contexts. We use multiple social networks to represent the complex social space in which an agent is inserted. In a simulation model, this setting can be seen as an n-dimensional scenario where each dimension contains a network that represents a different social relation (see Fig. 1). The word “context” is used in many different senses and it is by itself subjected to many analysis [28]. Here, we use the term social context in a simpler and more strict way. Agents belong to distinct social contexts which are their neighbourhoods in these multiple networks. The social context of an agent is thus a set of neighbours currently available for interaction at a particular network or set of networks. Context permeability is the ability of a particular norm, strategy, opinion, or trend, to permeate from one social relation to another. Agents belonging to disjoint neighbourhoods in different networks serve as bridges between subsets of the population that wouldn't otherwise be influenced by a consensus formed in a distant coalition.
     </paragraph>
     <paragraph>
      We study the notion of context permeability in different simulation models in which agents interact using a simple consensus game. The society of agents has to adopt a binary opinion value according to a majority rule. We use the speed of consensus as a measure for self-organisation and explore the relationship between different network topologies and this measure.
     </paragraph>
     <paragraph>
      We partitioned the design space of our experiments using different simulation models. Each model is designed to analyse different aspects of context permeability. In a first model [29], [30], we study the notion of permeability by overlapping social networks. In a second model [12], we analyse the dynamics introduced by switching between social contexts (neighbourhoods in different networks). This adds a temporal component that changes the dynamics of the game: agents can only perform encounters with neighbours that are active in their current context. (It also adds the chance for some agents to be isolated during the simulation.)
     </paragraph>
     <section label="3.1">
      <section-title>
       Simulation and consensus game
      </section-title>
      <paragraph>
       Our agent-based models are designed as discrete-event models. On each simulation cycle, every agent executes a simulation step. The agents are selected in a random uniform fashion for execution. This is common practice in agent-based simulation and guarantees that there is no bias caused by the order in which the agents are executed. For each simulation model, we present a description of the individual agent behaviour. Every model we present can be seen as a binary opinion dynamics model, or a consensus game. In this game, the society of agents tries to reach an arbitrary global consensus about two possible choices or opinion values. During a simulation run, each agent keeps track of the number of each opinion value of their interaction partners. In each iteration, each agent selects an available neighbour to interact with and observes its current opinion value. The agent decides to switch its current opinion choice if the observed opinion value becomes the majority of the two possible choices. The goal of the game is to reach a global consensus, but the particular choice that gets collectively selected is irrelevant. What is important is that overall agreement is achieved. In the consensus game we consider, each agent uses the previously presented external majority (EM) rule to update its opinion value (see Definition 1 in Section 2).
      </paragraph>
      <paragraph>
       The reason we are not interested in which exact option gets selected is the same reason why we chose such a content-neutral game for the individual interactions. From the very beginning, our research questions were focused on the collective properties, the structure of the networks involved, and the dynamical outcomes of the simulations: thus leaving out issues related with individual motivations and desired results (either for any individual agent or the society). Granted, most applications of this research will often include such goals, for inquisition into complex social issues, including possibly policy design, in which the individual rationality must be considered, and will have a very strong influence on the collective outcomes.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Context permeability
      </section-title>
      <paragraph>
       The first model of context permeability [29], [30] is designed to study the setting where an agent is immersed in a complex social world: where it engages in a multitude of relations with other agents. In this model, we consider that the context permeability is created by agents that can belong simultaneously to several relations. As an example, two agents can be simultaneously family and co-workers. While some links might not connect two agents directly, others can contain neighbourhoods in which they are related (either directly or through a common neighbour). Model 1 describes the behaviour of each agent for each simulated step.
      </paragraph>
      <paragraph>
       In this model, on each time step, each agent select a random neighbour from any social network available and updates its opinion based on the opinion of the selected partner using the external majority rule.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Context switching
      </section-title>
      <paragraph>
       In the context switching model [12] (Model 2), agents are embedded in multiple relations (represented as static social networks). Agents switch contexts with a probability {a mathematical formula}ζCi associated with context {a mathematical formula}Ci: this switching probability is the same for every agent in a given network. The agents are only active in one context at a time, and can only perform encounters with neighbours in the same context. We can think of context switching as a temporary deployment in another place, such as what happens with temporary immigration. The network topology is static; when an agent switches from one network to another, they become inactive in one network and active in their destination.
      </paragraph>
      <paragraph>
       In this model, agents select an (active) partner from their current neighbourhood. If a partner is available, the agents update their opinion value based on EM. At the end of the interaction, the agent switches from the current context to a different one with a probability associated with its current context.
      </paragraph>
      <paragraph>
       This model describes an abstract way to represent the time spent on each network using the switching probability {a mathematical formula}ζCi. Here, the permeability between contexts is achieved using this temporal component. Context switching introduces a notion that has not been explored in the literature so far: the fact that, although some social contexts can be relatively stable, our social peers are not always available for interaction and spend different amounts of time in distinct social contexts.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Experimental setup
     </section-title>
     <paragraph>
      In this section, we present all the tools and processes necessary to produce the current research output. The experiments were developed using the MASON [31] simulation framework written in Java. All the code for the simulation models can be found here [32]. Moreover, all the results presented in this article were made reproducible by using the statistical computing language R[33] and the R package knitr[34]. Knitr is used for generating reports that contain the code, the results of its execution (plots and tables), and the textual description for such results. All the R code used to produce the data analysis and the configuration files used to reproduce the data can be found in [35].
     </paragraph>
     <paragraph>
      For each configuration in our experiments, we performed 100 independent simulation runs. The results are analysed in terms of value distribution, average and standard deviation, or variance over the 100 runs. Like we described in Section 3.1, our models are discrete-event models. In each cycle agents execute a step in a random order: this is so that this dynamical system – our simulation model – is not influenced by the order in which agents are executed. Simulations end when total consensus is achieved or 2000 steps have passed.
     </paragraph>
     <section label="4.1">
      <section-title>
       Social network models
      </section-title>
      <paragraph>
       The social networks used in our models are k-regular and scale-free. A k-regular network is a network where all the nodes have the same number of connections. These networks are constructed by arranging the nodes in a ring and connecting each node to their next k neighbours. Each network has 2k edges per vertex.
      </paragraph>
      <paragraph>
       Scale-free networks are networks in which the degree distribution follows a power law, at least asymptotically. That is, the fraction {a mathematical formula}P(k) of nodes in the network having k connections to other nodes goes for large values of k as: {a mathematical formula}P(k)∼k−γ where γ is a parameter whose value is typically in the range {a mathematical formula}2&lt;γ&lt;3.
      </paragraph>
      <paragraph>
       We use the method proposed in [24] by Barabási and Albert to construct the scale-free network instances using a preferential attachment. This model builds upon the perception of a common property of many large networks: a scale-free-power-law distribution of node connectivity. This feature was found to be a consequence of two generic mechanisms: networks expand continuously by the addition of new vertices, and new vertices attach preferentially to sites that are already well connected (more commonly known as “preferential attachment”). In these networks, the probability {a mathematical formula}P(k) of two nodes being connected to each other decays as a power law, following {a mathematical formula}P(k)∼k−γ.
      </paragraph>
      <paragraph>
       The network instances were generated using the b-have network library[36]. This is a Java library that allows the creation and manipulation of network/graph data structures. It also includes the more commonly used random network models from the literature.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Measuring network properties
      </section-title>
      <paragraph>
       We measure two structural properties of our networks: the average path length and the clustering coefficient. The average path length measures the typical separation between two vertices in the graph. The clustering coefficient measures the average cliquishness of the graph neighbourhood. This measure quantifies how close the neighbours of a node are to forming a clique. Duncan J. Watts and Steven Strogatz [25] introduced the measure to characterise a class of complex networks called small-world networks.
      </paragraph>
      <paragraph>
       These properties characterise structures that can be found in the real scenarios. The small-world networks generated by the models of Watts and Strogatz for instance, model real-world social networks with short average path length, local clustering structures, and triadic closures between the nodes [25]. One shortcoming of this model, is the fact that these networks do not possess node hubs found in many real-world social networks. (Nevertheless, these models are designed to create networks with specific properties, not as general models for all kinds of real social networks)
      </paragraph>
      <paragraph>
       Since we construct scenarios where we overlap highly clustered k-regular networks and scale-free networks with node hubs, we are interested in the kind of properties that emerge from merging these structures – and if/how they are comparable to the existing models –. The networks were produced by the b-have network library[36], exported to files, and analysed using the igraph R package[37].
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Results and discussion
     </section-title>
     <paragraph>
      In this section, we analyse and discuss the results for different experiments with both the context permeability and context switching models. We start by analysing the structural properties that arise from combining different networks. We then observe the impact of different model configurations in the convergence to consensus. We correlate the outcomes of our context permeability model simulations with the structural properties of the multi-network structures. We also explore how the new dynamics introduced by the context switching mechanism affects the consensus building process.
     </paragraph>
     <section label="5.1">
      <section-title>
       Overlapping network properties
      </section-title>
      <paragraph>
       In this first analysis, we investigate the properties of different network topologies used in our models. One of the parameters in some experiments is the number of networks in which the agents interact. Adding more networks implies the addition of more connections. We show that what is important is not just the number of connections, but the properties of the resulting structure (when we merge the networks). We analyse the networks as follows.
      </paragraph>
      <paragraph>
       Each network is generated in such a way that the node indexes are randomised. This means that we can have multiple networks with the same topology and each node can have different neighbourhoods in different networks. Also, neighbourhoods do not necessarily overlap due to the node shuffling. Adding more networks to the social space is not the same as creating a single network with twice the number of connections.
      </paragraph>
      <paragraph>
       Consider Fig. 2. We created two random k-regular networks with {a mathematical formula}k=10 and merged them ignoring edges from common neighbours. (In the simulation models this edge agglutination is not performed, we use it here for the purposes of network analysis.) Common edges are highlighted with a different colour.
      </paragraph>
      <paragraph>
       The networks are drawn using the Kamada–Kawai Layout [38] which treats the “geometric” (Euclidean) distance between two vertices in the drawing as the “graph theoretic” distance between them in the corresponding graph. We can see by the results of the layout in Fig. 2, that the distance between nodes in the network has decreased, this is also confirmed by the reduced average path length of the combined networks (see Table 1). To illustrate our point, we analysed one k-regular network with {a mathematical formula}k=20 (see Fig. 3 and the corresponding entry on Table 1). The clustering coefficient of a 20-regular network is approximately the same as the one of a 10-regular network (higher than the combination of two 10-regular networks). The average path length also decreases as there are more connections between previously distant nodes. As we will show, these properties may vary due to the node indexes being subjected to random permutations.
      </paragraph>
      <paragraph>
       Since we model the agent social space as a multitude of networks, we need to investigate the properties resulting from the merging of these networks. We do this empirically by taking the network instances used in the simulations, and analysing the distribution of clustering coefficient and average path length for the different configurations.
      </paragraph>
      <section label="5.1.1">
       Properties of overlapping k-regular networks
       <paragraph>
        We will now investigate what kind of properties we can get from merging k-regular networks. First, we analysed the distribution for the average path length and the clustering coefficient values over 100 network instances (each with 100 nodes). From a box plot preliminary analysis (see Fig. A.2, Fig. A.1), we can see that the average path length does not vary much for the 100 instances, as such, the average makes a good descriptor for these properties.
       </paragraph>
       <paragraph>
        Fig. 4 shows the average value for the average path length of 100 k-regular network instances (each with 100 nodes). We can see that the average path length changes more drastically when we go from 1 to 2 networks. This is precisely the effect we can see in Fig. 2. Merging these networks at random effectively creates multiple shortcuts between points that were not connected in the original k-regular topology. Beyond this point, adding more networks does not modify this structural property in a significant way. Note that, since each network has 100 nodes, with {a mathematical formula}k=50 the network is fully connected (hence the average path length being 1).
       </paragraph>
       <paragraph>
        Fig. 5 shows the results for the average clustering coefficient of 100 instances of overlapping k-regular networks. Adding multiple networks changes the clustering coefficient of the resulting structure. For {a mathematical formula}k≤20, the clustering coefficient drops when we add a second network. This happens because when we merge these networks, their connectivity is not high enough to generate shortcuts with tightly clustered neighbourhoods. The clustering coefficient is computed by taking the average local clustering coefficient of each node in the network. An initial highly clustered k-regular network (with all the nodes having the same structure) is affected when you modify the node neighbourhoods in such a way that some are more clustered than others. Networks with {a mathematical formula}k=1 have a ring-like structure, so there are no nodes forming a clique{sup:1} with their neighbours.
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Properties of overlapping scale-free networks
       </section-title>
       <paragraph>
        We also looked at the properties that result from merging scale-free networks (see Fig. A.3). Like the previous results, the properties don't vary much between the 100 different instances. We can then say that specific configurations display a specific average path length and clustering coefficient both for k-regular networks and scale-free networks. We plotted the average of the average path length (Fig. 6a) and clustering coefficient (Fig. A.3b) for each overlapping network configuration.
       </paragraph>
       <paragraph>
        The parameter d (Fig. 6) dictates how many edges are added by preferential attachment (see Section 4.1). For {a mathematical formula}d=1, the resulting network is a forest: a network composed of disjoint tree graphs. Fig. 6a shows us that the average path length still decreases consistently when we add more networks. One of the characteristics of scale-free networks is its short average path length, thus, for {a mathematical formula}d≥2, adding more edges does not make a significant difference. Scale-free networks also have a reduced clustering coefficient (see Fig. 6b). When we add more networks the clustering coefficient increases.
       </paragraph>
      </section>
      <section label="5.1.3">
       <section-title>
        Merging K-regular with scale-free networks
       </section-title>
       <paragraph>
        Finally, we look at what happens when we merge k-regular networks with scale-free networks. We didn't make an exhaustive analysis for this configuration, but we show what is the resulting structure of such merging. You can see in Fig. 7 that this results in a network with a lower average path length due to the shortcuts created by the scale-free network. It is also less dense than the structure with two 10-regular networks (Fig. 2). We consider only the merging of two networks.
       </paragraph>
       <paragraph>
        Fig. 8 shows the average path length of 100 independently generated instances of combinations of one k-regular network and one scale-free network with different values k and d respectively. For configurations where the k-regular networks have low values of k (Fig. 8a), adding a scale-free network always decreases the average path length. Moreover, the higher the d, the lower the path length (as more connections are formed between different nodes). With higher values of k (Fig. 8) however, increasing the value of d does not decrease the average path length. This is not surprising given the level of connectivity of this structure. The first network is already highly dense and connected, so adding a few extra connections doesn't matter; what does matter is that we have a scale-free network creating shortcuts between nodes that were not previously connected.
       </paragraph>
       <paragraph>
        Fig. 9 shows the results for the clustering coefficient. These are similar to the results we get for k-regular networks (see Fig. 5). The difference is that we are not adding more networks but rather increasing the parameter d of the scale-free (number of connections added by preferential attachment for each note). In this case, the effects are qualitatively similar with the ones of merged k-regular network with low value of k. In contrast, for high values of k (Fig. 9b), a higher value of d is not enough to make the network more clustered. This happens because scale-free networks are more sparse and have a very low number of triangles between nodes.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Context permeability
      </section-title>
      <paragraph>
       In this section, we discuss the results for various sets of experiments on the context permeability model[29], [30]. First, we used k-regular and scale-free networks with our model. Each network layer was configured with the same topology. We analyse the context permeability model in terms of convergence to consensus: the ratio of simulations that converged to total consensus over 3000 runs; and how many agent encounters were needed for this to happen.
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Convergence ratio
       </section-title>
       <paragraph>
        To analyse the ratio of convergence to consensus for different network configurations, we correlate this ratio with the properties that the combined network structure exhibits. As we have seen in Section 5.1, the properties don't vary much for different random instances, so we use the average as the descriptor for these properties.
       </paragraph>
       <paragraph>
        The following tables show the results of our simulations. Table 2 shows the percentage of total consensus achieved with 2000 cycles for 3000 runs. For k-regular networks with a small k, consensus is rarely achieved with a single network. However, as soon as we add more networks, consensus is achieved in a significantly greater number of occasions. These results are especially interesting for the scale-free networks (Table 3): as soon as we add more networks, for a scale-free with {a mathematical formula}d≥2, we can achieve consensus in a lot of occasions. This is to show that achieving consensus is not just a matter of connectivity. With scale-free networks, we can achieve consensus more often with less clustered networks. This convergence is achieved not because of the clustering coefficient but rather due to lower average path length. This is difficult to visualise using only the tables and the previous plots so, to confirm this hypothesis, we measured the Spearman's correlation{sup:2} between the ratio of convergences to consensus, the average average path length, and the average clustering coefficient for the corresponding network configurations (see Table 4).
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Number of encounters to achieve consensus
       </section-title>
       <paragraph>
        We now analyse the convergence in terms of average number of meetings during a simulation run. Since the maximum number of simulation cycles is 2000, the maximum number of encounters is 2 000 000 (we have 100 agents and each one performs one encounter per cycle). We show that for some configurations, the average of encounters is not a good descriptor since it varies greatly from run to run. Rather than considering the average, it is better to look at the distributions of these measures. Nevertheless, we included the data with all the average number of encounters, as well as the respective standard deviations for different network configurations. You can find this data in Appendix B.
       </paragraph>
       <paragraph>
        First, we present the results for k-regular networks. To observe the distribution of the number of encounters, consider the box plots for {a mathematical formula}k={1,2,3,4,5} (Fig. 10a) and {a mathematical formula}k={10,20,30,40,50} (Fig. 10b). Fig. 10 shows the results for configurations with a number of networks ≥3 (since less networks lead to much worse results in terms of convergence speed). These plots reveal two types of situations: the typical runs, in which the number of encounters doesn't vary much, and some “outlier runs,” which present some interesting dynamics, as we will see later on.
       </paragraph>
       <paragraph>
        Fig. 10 shows us results qualitatively similar to what we previously observed for convergence ratios (see Section 5.2.1). Networks with lesser connectivity and a greater average path length lead to total convergence less often. The simulation outcomes also vary much more in comparison with the other configurations ({a mathematical formula}k&gt;1 and {a mathematical formula}networks≥3).
       </paragraph>
       <paragraph>
        Notice that for {a mathematical formula}k=3 and {a mathematical formula}networks=3 (10b), we still have runs that deviate from what we consider the typical behaviour. Instead of disregarding this as an outlier, we explore this behaviour to better understand the dynamics of our External Majority consensus game.
       </paragraph>
       <paragraph>
        We analysed the network structure from this run and observed that there were no distinct differences between the network instances from the “outlier run” and the ones of the “typical” run. This pointed to the consensus game itself as a possible cause for the irregular behaviour – not to the network structure –. What happens is that the agents reach a state from which converging towards consensus is significantly harder. Villatoro [39] found that some complex network models lead consensus games to form metastable sub-conventions. These are very difficult to break and reaching 100% agreement is not as straightforward as assumed by previous researchers. We are not concerned with this difficulty, instead, we want to explore how to describe what happens in similar cases. Fig. 11 shows the consensus progression for two simulation runs a typical case and the outlier.
       </paragraph>
       <paragraph>
        We take the outlier in the configuration with {a mathematical formula}k=3 and {a mathematical formula}networks=3, and look at the memory that agents use in the consensus game. As we described previously, agents record the number of individuals encountered with each opinion value (two possible values in this case). We look at the average difference between the number of values observed for all the agents. We also look at the variance to find how the opinion observations evolve throughout the simulation. Fig. 12 shows the average difference between opinion memory for the first 10 steps (which was when the simulation converged for the normal run).
       </paragraph>
       <paragraph>
        We can see that both the average difference in the opinion memory and the variance grow faster in the normal run than in the outlier run. This is not enough to establish a significant difference between the two. Moreover, the memory differences are quite similar, but the number of agents for each opinion was quite even. This happens due to the position of agents in the network and their initial opinion values. These circumstances led the agents to a initial stability. Note that the opinion difference continues to rise throughout the simulation along with the variance. The variance starts to increase more rapidly after 200 steps. The exponential growth reveals that the convergence to consensus is not done evenly throughout the network, this is one of the reasons why consensus takes more time to be achieved. Also, the low variance in the first 200 steps shows us that the opinion strength was evenly distributed: we have almost the same number of agents for each opinion but the memory differences are qualitatively the same for both opinions. As soon as this variance increases, one of the opinions breaks the stable state and convergence towards global consensus begins.
       </paragraph>
       <paragraph>
        {a mathematical formula}
       </paragraph>
       <paragraph>
        In other words, different neighbourhoods in the network lead to different opinion observation configurations (possibly even creating self-reinforcing structures). Thus, the influence of heterogeneous connectivity is reflected on the growth of opinion difference variance.
       </paragraph>
       <paragraph>
        Fig. 14 shows the average number of encounters during 100 independent simulation runs for scale-free networks. (We don't include the configuration for one network and {a mathematical formula}d=1 because these never converge.) The convergence ratio is very low for the configurations with one network {a mathematical formula}d=2 and 2 networks with {a mathematical formula}d=1; hence the high number of encounters (see also Table 3).
       </paragraph>
       <paragraph>
        These results are similar to those of k-regular in that adding more networks speeds up the convergence to consensus. The difference is that more “atypical” runs occur with multiple scale-free networks. Again, this is the effect of these types of topologies. As we discussed previously, in these less connected topologies, agents are more prone to be arranged in such a way that progression towards consensus is more difficult to attain due to bottlenecks. Different regions in the network might converge towards different opinion values.
       </paragraph>
      </section>
      <section label="5.2.3">
       <section-title>
        Heterogeneous network configuration
       </section-title>
       <paragraph>
        We also performed experiments with mixed network topologies: we used one scale-free and one k-regular networks. Table 5 shows the convergence ratio for the heterogeneous network configuration with the multiple values for d and k for the scale-free and k-regular respectively.
       </paragraph>
       <paragraph>
        One of the differences between this configuration and the previous ones can be observed in the simulations with {a mathematical formula}d=1 and {a mathematical formula}k=1. The convergence ratio is higher than with 2 1-regular networks (see Table 2) – but not better than two scale-free networks. This happens because with {a mathematical formula}k=1 the network is basically a ring and has the maximum possible average path length for a connected graph. Adding two rings improves the convergence ratio but the underlying structure is still very susceptible to self-reinforcing structures (a connected sub-graph is basically a line). Adding a scale-free changes this drastically as we are mixing tree-like network components with a ring.
       </paragraph>
       <paragraph>
        Fig. 15 shows the results for the number of encounters necessary for the agents to achieve consensus. We focus on the k-regular networks with higher values of k. We can see that with these two networks, the configurations with values of {a mathematical formula}d&gt;=2 for scale-free networks produce drastically better results in terms of speed of convergence. The data for the average number of encounters, as well as the respective standard deviations referent to the results in Fig. 15, can be found in Appendix B, Table B.3.
       </paragraph>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Context switching
      </section-title>
      <paragraph>
       In this section, we present the results relative to the context switching model. The difference between this model and the previous one is that the agents no longer interact in multiple networks at the same time (being able to select any neighbour at a given simulation step). In this model, they become active in a single network at a time. Agents can switch to a different network at the end of each step. The switching mechanism uses a probability associated with each network. With this new idea of swapping contexts, we covered some space left undeveloped in Antunes and colleagues original work [29], [30].
      </paragraph>
      <paragraph>
       As we discussed in Section 3.3 (see model 2), the switching probability dictates the frequency with which an agent switches from the current network after an encounter has been performed. In an abstract manner, this allows us to model how much time agents spend on each network. A further development of this model will be to assign different preferences to different networks for each agent. This can help us model phenomena such as real-world agents that dedicate more or less time consuming content from different social networks. For now, we attribute this probability to the network to restrain the model complexity.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Exploring the switching probability
       </section-title>
       <paragraph>
        We first look at the influence of the new parameter (switching probability) in the convergence to consensus. We span the switching probability between 0 and 1 in intervals of 0.05. We do this for 2 networks with k-regular and scale-free topologies. Fig. 16 shows the results for two k-regular networks: one configuration with {a mathematical formula}k=10 and one configuration with {a mathematical formula}k=30. We use these two configurations to study the relationship between the number of encounters, the switching probability parameter, and the connectivity of the networks. Remember that with {a mathematical formula}k=30 the average path length is also lower (Section 5.1.1).
       </paragraph>
       <paragraph>
        For smaller values of k, symmetry in the context switching probability (having the same probability in both networks) is more important if the agent switches less from one of the networks. Switching less from one network means spending more time in that network. This means that switching more from the other network can be disruptive to a neighbourhood that has already converged to a sub-convention. This can be observed in configurations with k-regular networks (Fig. 16a) but it is especially apparent in scale-free networks (Fig. 17a).
       </paragraph>
       <paragraph>
        When we increase the connectivity (and lower the average path length), both in k-regular and scale-free networks, the switching probability becomes “irrelevant” – for any probability value, the speed of convergence will be the same –. The exception is obviously when considering the switching probability with value 0. In this case, agents are isolated (they are initially equally distributed throughout the networks) and reaching consensus becomes very hard. (Especially because agents are active only in one network and this can create disconnected graphs.)
       </paragraph>
       <paragraph>
        One major difference from the previous model is that the agents no longer interact with a neighbour from any network at any time. The neighbour selection has to be made from the network they are currently active in. This causes the agents to spend different amounts of time in different networks. An agent can be very influential in one network – being a very central node in that context – and marginally important in another: in a sense its opinion in one network can be more important to overall convergence than in other network, due to its position in the network.
       </paragraph>
       <paragraph>
        To explore the contribution of connectivity to the new context switching dynamics, we setup two scale-free networks; one with {a mathematical formula}d=1 and the other with {a mathematical formula}d=5. We then spanned the switching probability in increments of 0.05. The results can be seen in Fig. 18.
       </paragraph>
       <paragraph>
        In this case it is more important (to convergence speed) to switch from the network with lower average path length and a forest-like composition (and a probability of at least the same value or more than the one of the other network with {a mathematical formula}d=5). The same can be observed when we mix k-regular with scale-free networks (see Fig. 19).
       </paragraph>
       <paragraph>
        Switching less from the less connected network is bad in both cases: it is possible that spending more time in the network with bigger neighbourhoods allows for a stabler convergence. Sub-conventions can emerge in scale-free networks with {a mathematical formula}d=1 because usually some network regions are isolated by a single node – the root of the sub-tree they belong to.
       </paragraph>
      </section>
      <section label="5.3.2">
       <section-title>
        Comparison with context permeability
       </section-title>
       <paragraph>
        Finally, to compare the context switching model with the previous model of context permeability, we froze the switching probabilities with values {a mathematical formula}ζ=0.25,0.5,0.75 and varied the number of networks. (We considered these values because they conveniently characterise the probability in low, medium and high switching.) We compare the results with the context permeability in terms of average number of encounters to achieve consensus. Note that in some cases, due to the distribution of the number of encounters, the average is not an accurate descriptor for the convergence. Nonetheless, configurations with highly variable outcomes usually produce an average that is qualitatively distinct from the rest (see Fig. 10 in Section 5.2.2). We took the average number of encounters during the simulations to compare the context switching model with the context permeability model.
       </paragraph>
       <paragraph>
        Fig. 20 shows that for 2 networks the results in terms of number of encounters for the context switching approximate those for context permeability. When we increase the number of networks ({a mathematical formula}n≥3), the configurations with higher switching probability lead the results to be closer to what happens in context permeability. This is no surprise since more switching makes agents switch more often between networks and consequently allows them too choose more often from different neighbourhoods. This is almost the same as having a larger neighbourhood to choose from, which is what happened in the context permeability model.
       </paragraph>
       <paragraph>
        The surprise was that for values of {a mathematical formula}k≥20, the results where practically the same for both models independently of the switching probability – even when we increased the number of networks, the number of encounters remained around 2000 on average for all the models. Above a certain level of neighbourhood size (and overlapping, which causes the average path length to drop), the switching probability becomes less influential. It is still important that we get comparable results because we are introducing a temporal component that was never explored before in these types of opinion dynamics models: the fact that the agents can become active in different networks at different points in time.
       </paragraph>
       <paragraph>
        For scale-free networks, Fig. 21 shows us similar results. Switching with a higher probability displays results similar with those of context permeability. In this case, adding more networks makes so that lowering switching probabilities displays slightly worse results. This influence comes from the neighbourhoods being considerably smaller in scale-free networks – even with values of {a mathematical formula}d=5 – so the impact of low switching was bound to be noticed.
       </paragraph>
       <paragraph>
        An increasing number of networks seems to always reduce the number of encounters to achieve consensus in both models. This happens due to what we called permeability. Having multiple points of dissemination that permeate between different social networks enhances the overall convergence to consensus. With permeability there are more previously isolated nodes being reached in sparsely connected networks such as scale-free networks.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Overlapping network properties
     </section-title>
     <section label="A.1">
      <section-title>
       Homogeneous network topology configurations
      </section-title>
     </section>
     <section label="A.2">
      <section-title>
       Heterogeneous network topology configurations
      </section-title>
     </section>
    </section>
    <section label="Appendix B">
     <section-title>
      Context permeability analysis
     </section-title>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Context switching analysis
     </section-title>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>