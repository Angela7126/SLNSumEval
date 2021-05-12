<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:808">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have discussed how we can structure a knowledge base for robots to help them with their tasks.</a>
<a href="#1" id="1">Our main insight is that we need a combination of different knowledge areas, different knowledge sources and different inference mechanisms to cover the breadth and depth of required knowledge and inferences.</a>
<a href="#2" id="2">At the same time, all components need to be integrated in a coherent knowledge base such that the robot can combine different knowledge sources and inference methods in a single query and integrate their results.</a>
<a href="#3" id="3">We therefore use a shared ontology as common representation and Prolog as interlingua for integrating inference techniques.</a>
<a href="#4" id="4">Finding appropriate representations for a robot's knowledge base has been a research topic for decades, dating back to the seminal work on the Shakey robot [31] that already used an internal world model based on predicate logics.</a>
<a href="#5" id="5">Compared to Shakey, modern robots have perception techniques that can handle the complexity of real scenes and manipulation capabilities that allow them to interact with objects.</a>
<a href="#6" id="6">Both aspects lead to significantly more complex scene representations and to a massive increase in knowledge about actions and objects that is required for performing actions.</a>
<a href="#7" id="7">While various methods have been developed in the AI community for representing and reasoning about temporal relations, action effects and changing situations, most of them focus on individual inference problems: Allen's interval calculus [1], for example, is mainly used for reasoning about temporal intervals, the Region Connection Calculus [34] extends it to two-dimensional (spatial) problems.</a>
<a href="#8" id="8">The Situation Calculus [25], [35] and the related Fluent calculus [47] focus on the representation and reasoning about changing domains, e.g. caused by robot actions.</a>
<a href="#9" id="9">The Qualitative Process Theory by Forbus [13] allows qualitative inference about physical or chemical processes.</a>
<a href="#10" id="10">Planning languages like STRIPS [12], PDDL [16], or Hierarchical Task Networks [9] specialize in the generation of plans for achieving a given goal.</a>
<a href="#11" id="11">Other rather formalized approaches for representing a robot's knowledge [48] allow reasoning about what the robot knows and what it does not know, but lack support for e.g. temporal reasoning, detailed spatial representations, information about object types or about processes in the environment.</a>
<a href="#12" id="12">Similar to reasoning methods, there are also many knowledge bases that partially cover a robot's needs: General-purpose knowledge bases like Cyc [23] or SUMO [30] provide a large breadth of encyclopedic knowledge, but often lack the depth in topis like object manipulation that is required by robots.</a>
<a href="#13" id="13">Recent efforts to automate the construction of knowledge bases by extracting encyclopedic knowledge from sources like Wikipedia [55], [40], [17] can provide knowledge in specialized areas, though often not directly relevant for robotics (e.g. countries, people or historic events).</a>
<a href="#14" id="14">On the other end, representations developed in robotics have largely focused on modeling and reasoning with uncertainty, leading to the development of many sophisticated, though often special-purpose probabilistic models [49].</a>
<a href="#15" id="15">However, most of these models are specialized for a single modality, for example perception [19], articulation model learning [39], or robot localization [8], and usually lack clear semantics.</a>
<a href="#16" id="16">Just recently, research in semantic environment maps has started to investigate models that combine spatial with grounded semantic representations [15], [58].</a>
<a href="#17" id="17">Wyatt et al. present a system that integrates geometric and conceptual spatial representations with planning and learning techniques [57].</a>
<a href="#18" id="18">The system is able to reason about knowledge gaps and tries to resolve them using autonomous learning, though not for object manipulation tasks.</a>
<a href="#19" id="19">In our research, we try to combine (parts of) these approaches in a common system to provide robots with comprehensive knowledge and inference capabilities.</a>
<a href="#20" id="20">The representation of object poses, for instance, is similar to the Fluent calculus [47], but also stores the provenance of information, i.e. if the robot believes, predicts or desires an object to be at some location.</a>
<a href="#21" id="21">This allows further interpretation of the information as well as describing different (possible) world states without causing conflicts in the knowledge base, which is important if the belief results from noisy perception.</a>
<a href="#22" id="22">The action representation as hierarchical partially-ordered plans with prerequisites, effects, and temporal information is related to Hierarchical Task Networks [9], but extended with qualitative projection methods for processes that are started as side-effects of actions, which are inspired by the Qualitative Process Theory Forbus [13].</a>
<a href="#23" id="23">Inference about temporal relations between actions or events is implemented according to Allen's interval calculus [1].</a>
<a href="#24" id="24">All inferences can be combined in Prolog queries, read the required information from the knowledge stored as OWL statements, and return their results in terms of OWL descriptions.</a>
<a href="#25" id="25">The knowledge base can be populated automatically with perception results and log data of robot actions.</a>
<a href="#26" id="26">Procedural attachments allow symbolic inference about sub-symbolic data by computing semantic information from it on demand at query time.</a>
<a href="#27" id="27">With these capabilities, KnowRob is significantly more expressive and flexible than other robot knowledge bases that purely rely on the rather limited OWL inference, for example ORO [22] or OUR-K [24].</a>
</body>
</html>