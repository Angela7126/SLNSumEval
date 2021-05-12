<html>
<head>
<meta name="TextLength" content="SENT_NUM:52, WORD_NUM:1146">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper has presented a probabilistic and decision theoretic formulation of affect control theory called BayesAct, and has shown its use for human interactive systems.</a>
<a href="#1" id="1">The paper's main contributions are the theoretical model development, and a demonstration that a computational agent can use BayesAct to integrate reasoning about emotions with application decisions in a parsimonious and well-grounded way.</a>
<a href="#2" id="2">Overall, our model uses the underlying principle of deflection minimisation from affect control theory to provide a general-purpose affective monitoring, analysis and intervention theory.</a>
<a href="#3" id="3">The key contributions of this paper are</a>
<a href="#4" id="4">A formulation of affect control theory as a probabilistic and decision theoretic model that generalises the original presentation in the social psychological literature in the following ways:</a>
<a href="#5" id="5">A set of simulations that demonstrate some of the capabilities of this generalised model of ACT under varying environmental noise.</a>
<a href="#6" id="6">A formulation of a general-purpose model for intelligent interaction that augments the model proposed by BayesAct in the following ways:</a>
<a href="#7" id="7">Demonstrative examples of building two simple intelligent interactive systems (a tutor and an assistive agent for person's with a cognitive disability) that use the proposed model to better align itself with a user.</a>
<a href="#8" id="8">Our current work is investigating methods for learning affective dictionaries automatically from text [99], and on implementing hierarchical models of identity [103].</a>
<a href="#9" id="9">In future, the measurement of EPA behaviours and the translation of EPA actions requires further study.</a>
<a href="#10" id="10">We also plan to investigate usages of the model for collaborative agents in more complex domains, for competitive, manipulative or therapeutic agents, conversational agents, social networks, and for social simulations where we have more than two agents acting.</a>
<a href="#11" id="11">Emotions have been shown to be important for decision making in general [41], [73], and we believe that BayesAct can play a significant role in this regard.</a>
<a href="#12" id="12">We also plan to investigate methods for automatically learning the parameters of the prediction equations, and the identity labels.</a>
<a href="#13" id="13">This would allow longer-term learning and adaptation for agents.</a>
<a href="#14" id="14">Finally, we plan to investigate how to handle more complex time structures in BayesAct, including interruptions.</a>
<a href="#15" id="15">A BayesAct agent uses the affect control principle to make predictions about the behaviours of the agents it interacts with.</a>
<a href="#16" id="16">This principle states that humans will act to minimise the deflection between their culturally shared fundamental (learned and slowly changing) affective sentiments and the transient sentiments created by specific events and situations.</a>
<a href="#17" id="17">In situations where both agents follow this principle, and know each other's affective identities, the agents do not have to compute long-term predictions: they can simply assume the predictions of the affect control principle are correct and act accordingly.</a>
<a href="#18" id="18">A breakdown occurs if these predictions no longer hold.</a>
<a href="#19" id="19">There are three types of breakdown.</a>
<a href="#20" id="20">The first is simple environmental noise.</a>
<a href="#21" id="21">However, we have seen that, alone, this does not have a significant effect.</a>
<a href="#22" id="22">Agents essentially “ignore” other agents in the presence of environmental noise, if they can assume the other agents are following the affect control principle.</a>
<a href="#23" id="23">In combination with the other two breakdown types, it can have a much more significant effect.</a>
<a href="#24" id="24">The second type of breakdown can occur if one agent does not know the identity of the other agent.</a>
<a href="#25" id="25">We have investigated this situation in detail in this paper in simulation, and found that BayesAct agents can learn the affective identities of other BayesAct agents under significant environmental noise.</a>
<a href="#26" id="26">Finally, the third type of breakdown is when one agent is deliberately trying to manipulate the other.</a>
<a href="#27" id="27">In such cases, both agents must do more complex policy computation, as the predictive power of the affect control principle no longer holds.</a>
<a href="#28" id="28">Computing these policies for such manipulative agents is a significant area for future work [9].</a>
<a href="#29" id="29">For example BayesAct agents are free to use X to model other agents at any level of detail (including as full POMDPs [104]).</a>
<a href="#30" id="30">Such more complex modelling will allow agents to reason about how other agents are reasoning (cognitively) about them, etc.</a>
<a href="#31" id="31">Nevertheless, even such cognitively capable agents will need to follow the norms of the society they are trying to manipulate, otherwise other agents will be unlikely to respond predictably.</a>
<a href="#32" id="32">In this regard, it is interesting to note that the default (normative) policy specified by Equation (32) may correspond roughly with what behavioural economists have called fast or “System 1” thinking [8].</a>
<a href="#33" id="33">The Monte-Carlo method for forward search can be set up to explore only actions that are nearby to this default action for each state, providing the agent with a quick-and-dirty method for quickly finding reasonable policies that will be socially acceptable or normative.</a>
<a href="#34" id="34">In a resource limited agent, this type of fast thinking may be just enough to “get by”.</a>
<a href="#35" id="35">Given enough time or sufficient cognitive resources, and agent may then resort to slow (“System 2”) thinking, and explore (in simulation) actions that are further away from the default.</a>
<a href="#36" id="36">This slow thinking can lead an agent to discover slightly non-normative actions that lead to higher self reward, without giving away the fact (so remaining close enough to the normative default).</a>
<a href="#37" id="37">The opens the door for building effective manipulative agents [9].</a>
<a href="#38" id="38">In a similar vein, the theory of social commitments [105] argues that human relationships combine relational (affective) and transactional (rational) components.</a>
<a href="#39" id="39">Lawler argues that modern society, becoming more and more influenced by economics and individualism, is moving towards an ecology of transactional ties, creating shallow, brittle and more dangerous (for the species) social structures [105].</a>
<a href="#40" id="40">His analysis carefully explores the space between these two views, and gives guidelines and arguments for how group processes can be built to take advantage of both.</a>
<a href="#41" id="41">BayesAct also combines relational and transactional ideas, by arguing that the core driving force behind human behaviour is relational and based on shared affective sentiments about identities and behaviours.</a>
<a href="#42" id="42">However, cognitive transactional processes come into play when relations break down.</a>
<a href="#43" id="43">Transactional relationships are set up to handle the breakdowns, but are rapidly integrated into relational processes if they are required to maintain the social order.</a>
<a href="#44" id="44">These considerations of breakdown lead to a tantalizing avenue for future research.</a>
<a href="#45" id="45">One way to handle breakdowns would be to increase the size of the (non-affective) state vector (denoted X in this paper).</a>
<a href="#46" id="46">Additional values of X would be needed in order to better predict when the breakdowns occur and what the effects are.</a>
<a href="#47" id="47">For example, an agent could learn what situations caused another agent to change identities, or could learn what types of identities are present in certain situations (called “settings” in ACT [1]).</a>
<a href="#48" id="48">Such an increase of X is a creation of new “meaning” in an agent [106], [107].</a>
<a href="#49" id="49">These new meanings would need to be validated with other agents, a process of negotiation attempting to get back to the easy state of “flow” where less reasoning is required [108].</a>
<a href="#50" id="50">A learning paradigm that is fundamentally based on affective reasoning would therefore arise.</a>
<a href="#51" id="51">Such a paradigm has been discussed as fundamental in the phenomenological view of intelligence [107], [106].</a>
</body>
</html>