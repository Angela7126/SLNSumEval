<html>
<head>
<meta name="TextLength" content="SENT_NUM:50, WORD_NUM:963">
</head>
<body bgcolor="white">
<a href="#0" id="0">Deliberate action is a central research issue in robotics.</a>
<a href="#1" id="1">It is an issue motivated by critical capabilities needed by autonomous robots facing a variety of environments, tasks and interactions.</a>
<a href="#2" id="2">Many applications in exploration, service, and personal robotics depend greatly on further progress and development of robotic deliberation capabilities.</a>
<a href="#3" id="3">Numerous contributions for the design of deliberation functions for a robot have been proposed.</a>
<a href="#4" id="4">A few have been discussed in the preceding sections.</a>
<a href="#5" id="5">The state of the art is broad and rich, but quite fragmented.</a>
<a href="#6" id="6">The relationships between these fragments are not studied enough.</a>
<a href="#7" id="7">It is indeed clear from our survey that only a few approaches take a global integrative view.</a>
<a href="#8" id="8">One finds more results about how to speedup a given technique then comprehensive characterizations of that technique, how it complements other approaches, and how it can be integrated with them.</a>
<a href="#9" id="9">For the purpose of this survey, we have outlined six deliberation functions and discussed their requirements and characteristics.</a>
<a href="#10" id="10">These functions may widely overlap in a given implementation.</a>
<a href="#11" id="11">The rational for their organization within an operational architecture has to take into account numerous requirements, in particular a hierarchy of closed loops, from the most dynamic inner loop, closest to the sensory-motor functions, to the most external outer loop.</a>
<a href="#12" id="12">A critical aspect is the relationship between planning and acting.</a>
<a href="#13" id="13">Acting cannot be reduced to the reactive triggering of sensory-motor commands mapped from planned actions or observed events.</a>
<a href="#14" id="14">There is a need for significant deliberation between what is planned and the commands achieving it.</a>
<a href="#15" id="15">This deliberation may even use different planning techniques, in particular motion, manipulation and other domain specific techniques.</a>
<a href="#16" id="16">It has to be done in different yet well integrated state spaces, action spaces and event spaces.</a>
<a href="#17" id="17">Although we insisted on distinguishing the two functions of acting and planning on top of the execution platform, there is no reason to believe that just three levels is the right number.</a>
<a href="#18" id="18">There can be a hierarchy of planning–acting levels, each refining a task planned further up into more concrete actions, adapted to the acting context and foreseen events.</a>
<a href="#19" id="19">It would be elegant to address this hierarchy within a homogeneous approach.</a>
<a href="#20" id="20">However, conflicting requirements, e.g., for handling domain specific representations and different levels of nondeterminism, uncertainty and inaccuracy, favor a variety of representations and approaches.</a>
<a href="#21" id="21">Deliberation functions encompass other open issues that we have not discussed in this survey.</a>
<a href="#22" id="22">Notable among them are the problems of interaction and social behavior.</a>
<a href="#23" id="23">Interaction impacts all functions discussed here, from the observing requirements in a multi-modal dialogue, to planning and acting at the levels of task sharing and plan understanding for multi-robots and human–robot interaction.</a>
<a href="#24" id="24">In summary, the take home message of this survey is that:</a>
<a href="#25" id="25">deliberation in robotics does not reduce to task planning, acting is a context and task dependent reaction to events and refinement of planned actions into commands, hierarchy of action refinements over several levels of state and action spaces is essential, monitoring needs strong links to prediction in planning and acting, observing requires significant deliberation, it does not reduce to signal processing, integrated and consistent representations and the acquisition of corresponding models are a clear bottleneck.</a>
<a href="#26" id="26">Future research directions emphasize representation, modeling and integration issues at various levels:</a>
<a href="#27" id="27">Descriptive models for task planning tend to favor the performance of search algorithms at the cost of shallow predictions.</a>
<a href="#28" id="28">Often in robotics, available knowledge, changing environments and the type of missions do not allow for or require plans with thousands of actions, at a proper level of abstraction.</a>
<a href="#29" id="29">The bottleneck is more on improving prediction capabilities of the models then on scaling up of search techniques.</a>
<a href="#30" id="30">Promising directions include detailed simulation systems and sampling techniques.</a>
<a href="#31" id="31">Heterogeneous knowledge representations can be desirable, although more difficult to integrate and verify.</a>
<a href="#32" id="32">Operational models for acting, to refine planned actions and react to events, have to lead to executable procedures, but they should not be just executable code.</a>
<a href="#33" id="33">They should allow for several decision making functions, e.g., choice, instantiation, look-ahead, time and context handling, etc.</a>
<a href="#34" id="34">Here also predictive capabilities are needed, but at a shorter range and in a closed loop with perception.</a>
<a href="#35" id="35">Open environment models and their relationship with descriptive and operational models for planning and acting offer exciting problems and perspectives.</a>
<a href="#36" id="36">Robots do not need to reinvent the wheel.</a>
<a href="#37" id="37">Their deliberation capabilities may build on communication and social mechanisms.</a>
<a href="#38" id="38">Model acquisition is certainly a bottleneck for deliberation functions.</a>
<a href="#39" id="39">Most approaches surveyed in this paper demand strong robotics expertise for designing and structuring required models.</a>
<a href="#40" id="40">Machine learning techniques are critical for the development of deliberative robots; they lead to numerous open problems.</a>
<a href="#41" id="41">Learning should be combined with model synthesis from higher level specifications.</a>
<a href="#42" id="42">For example, monitoring models should be synthesized from the operational and descriptive models for planning and acting.</a>
<a href="#43" id="43">Model verification problems have also to be stressed, e.g., in order to relate operational models to descriptive models, hand-specified or learned.</a>
<a href="#44" id="44">Consistency verification is harder with heterogeneous representations.</a>
<a href="#45" id="45">In many cases, verification can be a powerful tool in model acquisition techniques.</a>
<a href="#46" id="46">The observing function and its integration with other deliberation functions involve very challenging open problems in deliberation robotics, covering a wide spectrum from anchoring to symbol grounding, from object recognition to functional categorization, and from semantic map building to situation and dynamic environment understanding.</a>
<a href="#47" id="47">Finally, integration and architecture issues remain critical in the design of a deliberation system.</a>
<a href="#48" id="48">The conceptual view of a few deliberation functions sharing knowledge and data and interacting with sensory-motor functions serves a clarifying purpose.</a>
<a href="#49" id="49">It needs to be mapped into a more effective architecture whose organizational principle is a hierarchy of deliberation and sensory-motor functions relying on a hierarchy of clearly related representations and models, allowing for a plasticity of reconfiguration, as well as for sharing models and developments among roboticists as well as between robots.</a>
</body>
</html>