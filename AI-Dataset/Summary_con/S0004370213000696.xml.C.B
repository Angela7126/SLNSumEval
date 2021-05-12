<html>
<head>
<meta name="TextLength" content="SENT_NUM:40, WORD_NUM:960">
</head>
<body bgcolor="white">
<a href="#0" id="0">The main contributions of this article are in the contexts of two specific instantiations of ad hoc teamwork chosen to represent the simplest, most fundamental cases.</a>
<a href="#1" id="1">Specifically, we focused our attention on cases with a single teammate that exhibits fixed and known behavior, and then examined two variations on this theme.</a>
<a href="#2" id="2">First, in Section 2, we considered simultaneous, repeated action settings by adopting the iterated matrix game formalism.</a>
<a href="#3" id="3">Second, in Section 3, we considered a turn-taking scenario by adopting, and adapting, the k-armed bandit formalism.</a>
<a href="#4" id="4">In both cases, we proved several theorems regarding situations in which we know which actions are or cannot be optimal for the ad hoc team agent.</a>
<a href="#5" id="5">In both cases, we supplemented our theoretical results with some experiments analysis designed to test the aspects of the problems that were not analyzable theoretically.</a>
<a href="#6" id="6">First, we introduced (Section 2) a novel game theoretic formulation for modeling ad hoc teamwork for simultaneous decision making.</a>
<a href="#7" id="7">We focused on the case in which an intelligent agent interacts repeatedly in a fully cooperative setting with a teammate that responds by selecting its best response to a fixed history of actions, possibly with some randomness.</a>
<a href="#8" id="8">Based on its teammateʼs behavior, the intelligent agent can lead it to take a series of joint actions that is optimal for their joint long-term payoff.</a>
<a href="#9" id="9">The length of this series was proven to be linear in the minimal number of actions of Agent A or B when Bʼs memory is of size 1, leading to a polynomial time complexity for determining the optimal set of actions for the ad hoc agent.</a>
<a href="#10" id="10">When B bases its decisions on a longer memory size, this time complexity cannot be guaranteed.</a>
<a href="#11" id="11">Specifically, we have shown that determining the maximal size of an optimal series of joint actions is NP hard.</a>
<a href="#12" id="12">We then presented (Section 3) a multiagent cooperative k-armed bandit for modeling sequential decision making in ad hoc teamwork.</a>
<a href="#13" id="13">Here, the agents have different knowledge states and different action capabilities.</a>
<a href="#14" id="14">We have studied in detail the task of a teacher that knows the payoff distributions of all of the arms as it interacts with a learner that does not know the distributions, and that can only pull a subset of the arms.</a>
<a href="#15" id="15">The teacherʼs goal is to maximize the expected sum of payoffs as the two agents alternate actions.</a>
<a href="#16" id="16">At any point, it can either exploit its best available action or increase the learnerʼs knowledge by demonstrating one of the learnerʼs actions.</a>
<a href="#17" id="17">Within the specific scenario examined in this article, we proved several theorems regarding situations in which we know which actions are or cannot be optimal for the teacher.</a>
<a href="#18" id="18">We then narrowed our focus to two different types of probability distributions for the arms.</a>
<a href="#19" id="19">For discrete distributions, we presented a polynomial memory and time algorithm for finding the teacherʼs optimal action.</a>
<a href="#20" id="20">When the arms have Gaussian distributions, we can only find the optimal action efficiently when there is one round left.</a>
<a href="#21" id="21">In both cases we augment the theoretical results with some experimental analysis using our fully-implemented algorithms.</a>
<a href="#22" id="22">Our analysis—both in matrix game representation and in the k-armed bandit—opens up various exciting directions for future research.</a>
<a href="#23" id="23">In both models of ad hoc teamwork, it is assumed that the ad hoc agent is well aware of the its teammate behavior (although little of our analysis relies on the fact that Agent B is following a specific policy).</a>
<a href="#24" id="24">Examining unknown behavior is a key factor in ad hoc teamwork, that should be addressed in the future.</a>
<a href="#25" id="25">Similarly, leading and teaching more sophisticated agents—those that may explore independently—is also an important future direction.</a>
<a href="#26" id="26">Our current approaches are limited to leading or teaching one teammate.</a>
<a href="#27" id="27">Facing multiple teammates in ad hoc settings is a fundamental problem that will open various interesting research directions in the future, that include, other than the simplest, yet challenging, case of multiple agents as described in this article, also multiple possible teammate behavior, uncertainty in teammate behavior and more (note that initial results for leading multiple teammates in ad hoc settings can be found in [75]).</a>
<a href="#28" id="28">In addition, our proposed algorithm for leading a teammate is exponential in the teammateʼs memory size, making solutions to interaction scenarios with more than a few possible actions per agent intractable.</a>
<a href="#29" id="29">Heuristics enabling a streamlining of this algorithm would be very useful.</a>
<a href="#30" id="30">Many other generalizations to this cooperative k-armed bandit are possible.</a>
<a href="#31" id="31">For example, we have verified that at least some of our results can be extended to the discounted, infinite horizon case [76].</a>
<a href="#32" id="32">Specifically, we verified that in the 3-arm case, the teacher should still consider pulling Arm1, but should never pull Arm2, and that it should never pull Arm1 when {a mathematical formula}n1=0 and/or {a mathematical formula}n2=0.</a>
<a href="#33" id="33">The results for more than three arms from Section 3.5 were also verified in the discounted, infinite horizon case.</a>
<a href="#34" id="34">One could also consider arms with additional types of distributions, or types of distributions that differ among the arms (e.g. some discrete and some Gaussian).</a>
<a href="#35" id="35">Additionally, our algorithm for computing the optimal teaching algorithm is exponential in the number of arms.</a>
<a href="#36" id="36">Exploring possible approximation algorithms could be beneficial.</a>
<a href="#37" id="37">In the broader context, this research is just one step towards the long-term goal of creating a fully capable ad hoc team player.</a>
<a href="#38" id="38">In order to achieve this goal, many more studies of this magnitude will be needed that consider situations in which, for example, there are more than two teammates, the teammates can communicate directly, the teammatesʼ behaviors are not fully known, or some teammates have more knowledge and/or capabilities than our agent.</a>
<a href="#39" id="39">We intend to follow up on these challenges in our future research and hope that this research will inspire others to also work towards the eventual creation of fully general ad hoc team players.</a>
</body>
</html>