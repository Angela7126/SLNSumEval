<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Single-Agent vs. Multi-Agent Techniques for Concurrent Reinforcement Learning of Negotiation Dialogue Policies.
  </title>
 </head>
 <body>
  <div class="ltx_page_main">
   <div class="ltx_page_content">
    <div class="ltx_document ltx_authors_1line">
     <div class="ltx_abstract">
      <h6 class="ltx_title ltx_title_abstract">
       Abstract
      </h6>
      <p class="ltx_p">
       We use single-agent and multi-agent Reinforcement Learning (RL)
for learning dialogue
policies in a resource allocation negotiation scenario.
Two agents learn concurrently by interacting
with each other without any need for simulated users (SUs) to train against
or corpora to learn from.
In particular, we compare the Q-learning, Policy Hill-Climbing (PHC)
and Win or Learn Fast Policy Hill-Climbing (PHC-WoLF) algorithms,
varying the scenario complexity (state space size), the
number of training episodes, the learning rate, and the exploration rate.
Our results show that generally Q-learning fails to converge
whereas PHC and PHC-WoLF always converge and perform similarly.
We also show that very high gradually decreasing
exploration rates are required for convergence.
We conclude that multi-agent RL of dialogue policies
is a promising alternative to
using single-agent RL and SUs or learning directly
from corpora.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Introduction
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        The dialogue policy of a dialogue system decides on which actions
the system should perform given a particular
dialogue state (i.e., dialogue context).
Building a dialogue policy can be a challenging task especially
for complex applications. For this reason, recently
much attention has been drawn to machine learning
approaches to dialogue management
and in particular Reinforcement Learning (RL) of dialogue
policies
        [40, 34, 22]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Typically there are three main approaches to the problem of
learning dialogue policies using RL:
(1) learn against a simulated
user (SU), i.e., a model that simulates the behavior of a real user
        [15, 35]
        ;
(2) learn directly from a corpus
        [20, 25]
        ;
or (3) learn via live interaction with human
users
        [36, 13, 12]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We propose a fourth approach: concurrent learning of the
system policy and the SU policy using multi-agent RL
techniques. Both agents are trained simultaneously and there is
no need for building a SU separately or having access to a corpus.
        As we discuss below, concurrent learning could potentially
be used for learning via live interaction with human users.
Moreover, for negotiation in particular there is one more reason
in favor of concurrent learning as opposed to learning against a SU.
Unlike slot-filling domains, in negotiation the behaviors of the system
and the user are symmetric. They are both negotiators, thus
building a good SU is as difficult as building a good
system policy.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        So far research on using RL for dialogue policy learning
has focused on single-agent RL techniques.
Single-agent RL methods
make the assumption that the system learns by interacting
with a stationary environment, i.e., an environment that does not
change over time.
Here the environment is the user.
Generally the assumption that users do not significantly change their
behavior over time holds for simple information providing
tasks (e.g., reserving a flight).
But this is not necessarily
the case for other genres of dialogue, including negotiation.
Imagine a situation where a negotiator is so uncooperative
and arrogant that the other negotiators decide to completely
change their
negotiation strategy in order to punish her.
Therefore it is important to investigate RL approaches that
do not make such assumptions about the user/environment.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Multi-agent RL is designed to work for non-stationary environments.
In this case the environment of a learning agent is one or more other
agents that
can also be learning at the same time.
Therefore, unlike single-agent RL, multi-agent RL can
handle changes in user behavior or in the behavior of other
agents participating in the interaction, and thus potentially
lead to more realistic dialogue policies in complex dialogue
scenarios.
This ability of multi-agent RL can also have important
implications for learning via live interaction with
human users. Imagine a system that learns to change its strategy
as it realizes that a particular user is no longer a novice user,
or that a user no longer cares about five star restaurants.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        We apply multi-agent RL to a resource allocation negotiation
scenario. Two agents with different preferences
negotiate about how to share resources.
We compare Q-learning (a single-agent RL algorithm)
with two multi-agent RL algorithms:
Policy Hill-Climbing (PHC)
and Win or Learn Fast Policy Hill-Climbing (PHC-WoLF)
        [3]
        .
We vary the scenario complexity (i.e., the quantity of
resources to be shared and consequently the state space size), the
number of training episodes, the learning rate, and the exploration rate.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Our research contributions are as follows:
(1) we propose concurrent learning using multi-agent RL
as a way to deal with some of the issues of current approaches
to dialogue policy learning (i.e., the need for SUs and
corpora), which may also potentially prove useful for learning
via live interaction with human users;
(2) we show that concurrent
learning can address changes in user behavior over time, and requires
multi-agent RL techniques and variable exploration rates;
(3) to our knowledge this is the
first time that PHC and PHC-WoLF are used for learning
dialogue policies;
(4) for the first time, the above techniques
are applied to a negotiation domain; and
(5) this is the first study that compares Q-learning,
PHC, and PHC-WoLF
in such a variety of situations
(varying a large number of parameters).
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        The paper is structured as follows. Section
        2
        presents related work. Section
        3
        provides
a brief introduction to single-agent RL and multi-agent RL.
Section
        4
        describes
our negotiation domain and experimental setup.
In section
        5
        we present our results.
Finally,
section
        6
        concludes
and provides some ideas for future work.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Most research in RL for dialogue management has been done in
the framework of slot-filling applications
such as restaurant recommendations
        [24, 39, 14, 9]
        ,
flight reservations
        [20]
        ,
sightseeing recommendations
        [29]
        ,
appointment scheduling
        [17]
        ,
etc.
RL has also been applied to question-answering
        [28]
        ,
tutoring domains
        [38, 6]
        , and
learning negotiation dialogue
policies
        [19, 16, 18]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        As mentioned in section
        1
        ,
there are three main approaches to the problem of
learning dialogue policies using RL.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        In the first approach, a SU is hand-crafted or learned from
a small corpus of human-human or human-machine dialogues.
Then the dialogue policy can be learned by having the system
interact with the SU for a large number of dialogues (usually
thousands of dialogues).
Depending on the application, building a realistic SU can be
just as difficult as building a good dialogue policy. Furthermore, it is not
clear what constitutes a good SU for dialogue policy learning.
Should the SU resemble real user behavior as closely as possible, or
should it exhibit some degree of randomness to explore
a variety of interaction patterns?
Despite much research on the issue, these are still open
questions
        [35, 2, 32]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        In the second approach, no SUs are required. Instead the dialogue
policy is learned directly from a corpus of human-human or
human-machine dialogues. For example,
        Henderson et al. (2008)
        used a combination of RL and supervised learning
to learn a dialogue policy in a flight reservation domain,
whereas
        Li et al. (2009)
        used Least-Squares Policy Iteration
        [23]
        , an RL-based
technique that can learn directly from corpora, in a voice
dialer application.
However, collecting such
corpora is not trivial, especially in new domains. Typically,
data are collected in a Wizard-of-Oz setup where human users think that
they interact with a system while in fact they interact with a human
pretending to be the system, or by having human users interact with
a preliminary version of the dialogue system. In both cases the
resulting interactions are expected to be quite different from
the interactions of human users with the final system. In practice
this means that dialogue policies learned from such data could be far
from optimal.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        The first experiment on learning via live interaction
with human users (third approach) was reported by
        Singh et al. (2002)
        .
They used RL to help the system with two choices: how much
initiative it should allow the user, and whether or not
to confirm information provided by the user.
Recently, learning of “full” dialogue policies (not just
choices at specific points in the dialogue) via live
interaction with human users has become possible with the
use of Gaussian processes
        [10, 33]
        .
Typically learning a dialogue policy is a slow process requiring
thousands of dialogues, hence the need for SUs.
Gaussian processes have been shown to speed up learning. This fact
together with easy access to a large number of human users
through crowd-sourcing has allowed dialogue policy learning via live interaction
with human users
        [13, 12]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        Space constraints prevent us from providing an exhaustive list
of previous work on using RL for dialogue management. Thus below we
focus only on research that is directly related to our work, specifically
research on concurrent learning of the policies of multiple agents,
and the application of RL to negotiation domains.
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        So far research on RL in the dialogue community has focused on using
single-agent RL techniques where the stationary environment is
the user.
Most approaches assume that the user goal is fixed and that the
behavior of the user is rational. Other approaches account for changes
in user goals
        [27]
        . In either case, one can build
a user simulation model that is the average of different user behaviors
or learn a policy
from a corpus that contains a variety of interaction patterns,
and thus safely assume that single-agent RL techniques will work.
However, in the latter case if the behavior of the user changes
significantly over time then
the assumption that the environment is stationary will no longer hold.
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <p class="ltx_p">
        There has been a lot of research on multi-agent RL in the
optimal control
and robotics communities
        [26, 21, 4]
        .
Here two or more agents
learn simultaneously. Thus the environment of an agent
is one or more other agents that continuously change their
behavior because they are also learning at the same time.
Therefore the environment is no longer stationary and single-agent
RL techniques do not work well or do not work at all. We
are particularly interested in the work of
        Bowling and Veloso (2002)
        who proposed the PHC and PHC-WoLF algorithms that we use in this paper.
We chose these two algorithms because, unlike other multi-agent
RL methods
        [26, 21]
        , they do not
make assumptions that do not always hold and do not require
quadratic or linear programming that does not always scale.
       </p>
      </div>
      <div class="ltx_para" id="S2.p9">
       <p class="ltx_p">
        English and Heeman (2005)
        were the first in the dialogue community
to explore the idea of concurrent learning of dialogue policies.
However,
        English and Heeman (2005)
        did not use multi-agent
RL but only standard single-agent RL, in particular an on-policy
Monte Carlo method
        [37]
        .
But single-agent RL techniques
are not well suited for
concurrent learning
where each agent is trained against a continuously changing
environment.
Indeed,
        English and Heeman (2005)
        reported problems
with convergence.
        Chandramohan et al. (2012)
        proposed a framework for
co-adaptation of the dialogue policy and the SU using single-agent RL.
They applied
Inverse Reinforcement Learning (IRL)
        [1]
        to a corpus in order to learn
the reward functions of both the system and the SU.
Furthermore,
        Cuayáhuitl and Dethlefs (2012)
        used hierarchical multi-agent RL for co-ordinating the verbal
and non-verbal actions of a robot.
        Cuayáhuitl and Dethlefs (2012)
        did not use PHC or PHC-WoLF
and did not compare against single-agent RL methods.
       </p>
      </div>
      <div class="ltx_para" id="S2.p10">
       <p class="ltx_p">
        With regard to using RL for learning negotiation policies,
the amount of research that has been performed is very limited
compared to slot-filling.
        English and Heeman (2005)
        learned negotiation policies for
a furniture layout task. Then
        Heeman (2009)
        extended
this work by experimenting with different representations of the
RL state in the same domain (this time learning against a hand-crafted
SU).
In both cases, to reduce the search space,
the RL state included only information about e.g., whether
there was a pending proposal rather than the actual value of this
proposal.
        Paruchuri et al. (2009)
        performed a theoretical study on how
Partially Observable Markov Decision Processes (POMDPs)
can be applied to negotiation domains.
       </p>
      </div>
      <div class="ltx_para" id="S2.p11">
       <p class="ltx_p">
        Georgila and Traum (2011)
        built argumentation dialogue policies
for negotiation against users of different cultural norms
in a one-issue negotiation scenario.
To learn these policies they trained SUs on a
spoken dialogue corpus in a florist-grocer negotiation domain,
and then tweaked these SUs towards a particular cultural norm using
hand-crafted rules.
        Georgila (2013)
        learned argumentation dialogue policies
from a simulated corpus
in a two-issue negotiation scenario (organizing a party).
Finally,
        Nouri et al. (2012)
        used IRL
to learn a model for cultural decision-making in a simple negotiation
game (the Ultimatum Game).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Single-Agent vs. Multi-Agent Reinforcement Learning
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Reinforcement Learning (RL) is a machine learning technique used to learn
the policy of an agent, i.e.,
which action the agent should perform given its current state
        [37]
        .
The goal of an RL-based agent is
to maximize the reward it gets during an interaction.
Because it is very difficult for the agent
to know what will happen in the rest of the interaction, the agent
must select an action based on the average reward it has previously observed
after having performed that action in similar contexts.
This average reward is called
        expected future reward
        .
Single-agent RL is used in the framework of Markov Decision Processes
(MDPs)
        [37]
        or
Partially Observable Markov Decision Processes
(POMDPs)
        [40]
        .
Here we focus on MDPs.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        An MDP is defined as a tuple (
        S
        ,
        A
        ,
        T
        ,
        R
        ,
        γ
        ) where
        S
        is the set of states (representing different contexts) which the agent
may be in,
        A
        is the set of actions
of the agent,
        T
        is the transition function
        S
        ×
        A
        ×
        S
        →
        [0, 1]
which defines
a set of transition
probabilities between states after taking an action,
        R
        is the reward function
        S
        ×
        A
        →
        ℜ
        which defines the reward received when taking an action
from the given state, and
        γ
        is a factor
that discounts future rewards.
Solving the MDP means finding a
policy
        π
        :
        S
        →
        A
        .
The quality of the policy
        π
        is measured by the expected discounted
(with discount factor
        γ
        )
future reward also called Q-value,
        Qπ
        :
        S
        ×
        A
        →
        ℜ
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        A
        stochastic game
        is defined as a tuple (
        n
        ,
        S
        ,
        A1...⁢n
        ,
        T
        ,
        R1...⁢n
        ,
        γ
        )
where
        n
        is the number of agents,
        S
        is the set of states,
        Ai
        is the set of actions available
for agent
        i
        (and
        A
        is the joint action space
        A1
        ×
        A2
        ×
        …
        ×
        An
        ),
        T
        is the transition function
        S
        ×
        A
        ×
        S
        →
        [0, 1]
which defines
a set of transition
probabilities between states after taking a joint action,
        Ri
        is the reward function for the
        i
        th agent
        S
        ×
        A
        →
        ℜ
        ,
and
        γ
        is a factor
that discounts future rewards.
The goal is for each agent
        i
        to learn a mixed policy
        πi
        :
        S
        ×
        Ai
        →
        [0, 1]
that maps states to mixed strategies,
which are probability distributions over the agent’s actions,
so that the agent’s expected discounted (with
discount factor
        γ
        ) future reward is maximized.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Stochastic games are a generalization of MDPs
for multi-agent RL.
In stochastic games there are many agents
that select actions and the next state and rewards depend
on the joint action of all these agents.
The agents can have different reward functions.
Partially Observable Stochastic Games (POSGs) are the equivalent of
POMDPs for multi-agent RL. In POSGs, the agents have different observations,
and uncertainty about the state they are in and the beliefs of their
interlocutors. POSGs are very hard to solve but new algorithms continuously
emerge in the literature.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        In this paper we use three algorithms: Q-learning,
Policy Hill-Climbing (PHC), and Win or Learn Fast Policy Hill-Climbing
(PHC-WoLF).
PHC is an extension of Q-learning. For all three algorithms,
Q-values are updated as follows:
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       Q⁢(s,a)←(1-α)⁢Q⁢(s,a)+α⁢(r+γ⁢\text⁢m⁢a⁢xa′⁢Q⁢(s′,a′))

(1)
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        In Q-learning, for a given state
        s
        , the agent performs the action with
the highest
Q-value for that state.
In addition to Q-values, PHC and PHC-WoLF also
maintain the current mixed policy
        π⁢(s,a)
        .
In each step the mixed policy is updated by increasing the
probability of selecting
the highest valued action
according to a learning rate
        δ
        (see equations (2), (3), and (4) below).
       </p>
      </div>
      <div class="ltx_para" id="S3.p8">
       π⁢(s,a)←π⁢(s,a)+Δs⁢a

(2)
      </div>
      <div class="ltx_para" id="S3.p9">
       Δs⁢a={dcases}-δs⁢a⁢Align⁢\text⁢i⁢f⁢a≠\text⁢a⁢r⁢g⁢m⁢a⁢xa′⁢Q⁢(s,a′)⁢Σa′≠a⁢δs⁢a′⁢Align⁢\text⁢o⁢t⁢h⁢e⁢r⁢w⁢i⁢s⁢e

(3)
      </div>
      <div class="ltx_para" id="S3.p10">
       δs⁢a=\text⁢m⁢i⁢n⁢(π⁢(s,a),δ|Ai|-1)

(4)
      </div>
      <div class="ltx_para" id="S3.p11">
       <p class="ltx_p">
        The difference between PHC and PHC-WoLF is that PHC
uses a constant learning rate
        δ
        whereas
PHC-WoLF uses a variable learning rate (see equation (5) below).
The main idea is that when the agent is “winning”
the learning rate
        δW
        should be low so that the opponents
have more time to adapt to the agent’s policy,
which helps with convergence.
On the other hand when the agent is “losing”
the learning rate
        δL⁢F
        should be high so that the agent
has more time to adapt to the other agents’
policies, which also facilitates convergence.
Thus PHC-WoLF uses two learning rates
        δW
        and
        δL⁢F
        .
PHC-WoLF determines whether the agent is “winning”
or “losing” by comparing the current policy’s
        π⁢(s,a)
        expected payoff
with that of the average policy
        π~⁢(s,a)
        over time.
If the current policy’s expected payoff is greater then the agent is
“winning”, otherwise it is “losing”.
       </p>
      </div>
      <div class="ltx_para" id="S3.p12">
       δ={dcases}⁢δW⁢Align⁢\text⁢i⁢f⁢{dcases}⁢Align⁢Σα′⁢π⁢(s,α′)⁢Q⁢(s,α′)&gt;Align⁢Σα′⁢π~⁢(s,α′)⁢Q⁢(s,α′)⁢δL⁢F⁢Align⁢\text⁢o⁢t⁢h⁢e⁢r⁢w⁢i⁢s⁢e

(5)
      </div>
      <div class="ltx_para" id="S3.p13">
       <p class="ltx_p">
        More details about Q-learning, PHC, and PHC-WoLF can be found
in
        [37, 3]
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p14">
       <p class="ltx_p">
        As discussed in sections
        1
        and
        2
        ,
single-agent RL techniques, such as Q-learning, are not suitable for multi-agent
RL. Nevertheless, despite its shortcomings
Q-learning has been used successfully for multi-agent RL
        [7]
        .
Indeed, as we see in section
        5
        ,
Q-learning can converge to the optimal policy for
small state spaces. However, as the state space size
increases the performance of Q-learning drops (compared
to PHC and PHC-WoLF).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Domain and Experimental Setup
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Our domain is a resource allocation negotiation
scenario. Two agents
negotiate about how to share resources. For the sake of
readability from now on we will refer to apples and oranges.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The two agents have different goals. Also, they have
human-like constraints of imperfect information about each other;
they do not know each other’s reward function or degree of rationality
(during learning our agents can be irrational).
Thus a Nash equilibrium (if there exists one)
cannot be computed in advance.
Agent 1 cares more about apples and Agent 2 cares more about
oranges.
Table
        1
        shows the points that Agents 1 and 2
earn for each apple and each orange that they have at the end
of the negotiation.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        We use a simplified dialogue model with two types of
speech acts: offers and acceptances.
The dialogue proceeds as follows:
one agent makes an offer, e.g., “I give you 3 apples and 1 orange”,
and the other agent may choose to accept it or make a new
offer. The negotiation finishes when one of the agents
accepts the other agent’s offer or time runs out.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        We compare Q-learning with PHC and PHC-WoLF.
For all algorithms and experiments each agent is rewarded only at the
end of the dialogue based on the negotiation outcome
(see Table
        1
        ).
Thus the two agents have different reward functions.
There is also a penalty of -10
for each agent action to ensure that dialogues are not too
long.
Also, to avoid long dialogues,
if none of the agents accepts the other agent’s offers,
the negotiation
finishes after 20 pairs of exchanges
between the two agents (20 offers from Agent 1 and 20 offers
from Agent 2).
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        An example interaction between the two agents
is shown in Figure
        1
        .
As we can see, each agent can offer any combination of apples
and oranges.
So if we have
        X
        apples and
        Y
        oranges for sharing,
there can be (
        X+1
        )
        ×
        (
        Y+1
        ) possible offers.
For example if we have 2 apples and 2 oranges for sharing,
there can be 9 possible offers:
“offer-0-0”, “offer-0-1”, …, “offer-2-2”.
For our experiments we vary the number of fruits
to be shared and choose to keep
        X
        equal to
        Y
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        Table
        2
        shows our state representation,
i.e., the state variables that we keep track of with all
the possible values they can take, where
        X
        is the number of apples
and
        Y
        is the number of oranges to be shared.
The third variable is always set to “no” until one of the agents
accepts the other agent’s offer.
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        Table
        3
        shows the state and action
space sizes for different numbers of apples and oranges to be shared
used in our experiments below.
The number of actions includes the acceptance of an offer.
Table
        3
        also shows the number of state-action pairs (Q-values).
As we will see in section
        5
        , even though
the number of states for each agent is not large,
it takes many iterations and high exploration rates for
convergence due to the fact that both agents are learning at the same
time and
the assumption of interacting with a stationary environment
no longer holds.
For comparison, in
        [11]
        the state
specification for each agent included 5 binary variables
resulting in 32 possible states.
        English and Heeman (2005)
        kept track of whether there was
an offer on the table but not of the actual value of the offer.
For our task it is essential to keep track of the offer values,
which of course results in much larger state spaces.
Also, in
        [11]
        there were 5 possible actions
resulting in 160 state-action pairs.
Our state and action spaces are much larger and furthermore
we explore the effect of different state and action space sizes
on convergence.
       </p>
      </div>
      <div class="ltx_para" id="S4.p8">
       <p class="ltx_p">
        During learning the two agents interact for 5 epochs. Each epoch
contains
        N
        number of episodes. We vary
        N
        from 25,000 up to 400,000
with a step of 25,000 episodes.
        English and Heeman (2005)
        trained their agents
for 200 epochs, where each epoch contained 200 episodes.
       </p>
      </div>
      <div class="ltx_para" id="S4.p9">
       <p class="ltx_p">
        We also vary the exploration rate
per epoch. In particular, in the experiments reported
in section
        5.1
        the exploration rate is set as follows:
0.95 for epoch 1,
0.8 for epoch 2, 0.5 for epoch 3, 0.3 for epoch 4,
and 0.1 for epoch 5.
Section
        5.2
        reports results again with
5 epochs of training but a constant exploration rate
per epoch set to 0.3.
An exploration rate of 0.3 means that 30% of the time the agent
will select an action randomly.
       </p>
      </div>
      <div class="ltx_para" id="S4.p10">
       <p class="ltx_p">
        Finally, we vary the learning rate. For PHC-WoLF we set
        δW
        = 0.05 and
        δL⁢F
        = 0.2 (see section
        3
        ).
These values were chosen with experimentation and the basic
idea is that the agent should learn faster when “losing”
and slower when “winning”.
For PHC we explore two cases.
In the first case which from now on will be referred to as PHC-W,
we set
        δ
        to be equal to
        δW
        (also used for PHC-WoLF).
In the second case which from now on will be referred to as PHC-LF,
we set
        δ
        to be equal to
        δL⁢F
        (also used for PHC-WoLF).
So unlike PHC-WoLF, PHC-W and PHC-LF do not use a variable learning
rate. PHC-W always learns slowly and PHC-LF always learns fast.
       </p>
      </div>
      <div class="ltx_para" id="S4.p11">
       <p class="ltx_p">
        In all the above cases, training stops after 5 epochs.
Then we test the learned policies against each other for
one more epoch the size of which is the same as the size
of the epochs used for training. For example,
if the policies were learned for 5 epochs with each epoch
containing 25,000 episodes, then for testing the two
policies will interact for another 25,000 episodes.
For comparison,
        English and Heeman (2005)
        had their agents interact for 5,000 dialogues during testing.
To ensure that the policies do not converge by chance,
we run the training and test sessions 20 times each and we
report averages. Thus all results presented in section
        5
        are averages of 20 runs.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Given that Agent 1 is more interested in apples and Agent 2
cares more about oranges,
the maximum total utility solution would be
the case where each agent offers to get all the fruits it cares
about and
to give its interlocutor all the fruits it does not care about,
and the other agent accepts this offer.
Thus, when converging to the maximum total utility solution,
in the case of 4 fruits (4 apples and 4 oranges),
the average reward of the two agents should
be 1200 minus 10 for making or accepting an offer.
For 5 fruits the average reward should be 1500 minus 10, and so forth.
We call 1200 (or 1500) the
        convergence reward
        ,
i.e., the reward after converging to the maximum total utility solution
if we do not take into account the action penalty.
For example, in the case of 4 fruits,
if Agent 1 starts the negotiation, after converging to the maximum
total utility solution
the optimal interaction
should be: Agent 1 makes an offer to Agent 2,
namely 0 apples and 4 oranges, and
Agent 2 accepts. Thus the reward for Agent 1 is 1190, the reward
for Agent 2 is 1190, and the average reward of the two agents is
also 1190.
Also, the convergence reward for Agent 1 is 1200 and the
convergence reward for Agent 2 is also 1200.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        Below, in all the graphs that we provide, we show the average
distance from the convergence reward.
This is to make
all graphs comparable because in all cases the
optimal average distance from the convergence reward of the two agents
should be equal to 10 (make the optimal offer or accept
the optimal offer that the other agent makes).
The formulas for calculating the average distance from the convergence
reward are:
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       A⁢D1=∑j=1nr\lvert⁢C⁢R1-R1⁢j⁢\rvertnr

(6)
      </div>
      <div class="ltx_para" id="S5.p4">
       A⁢D2=∑j=1nr\lvert⁢C⁢R2-R2⁢j⁢\rvertnr

(7)
      </div>
      <div class="ltx_para" id="S5.p5">
       A⁢D=A⁢D1+A⁢D22

(8)
      </div>
      <div class="ltx_para" id="S5.p6">
       <p class="ltx_p">
        where
        C⁢R1
        is the convergence reward for Agent 1,
        R1⁢j
        is the reward of Agent 1 for run
        j
        ,
        C⁢R2
        is the convergence reward for Agent 2, and
        R2⁢j
        is the reward of Agent 2 for run
        j
        .
Moreover,
        A⁢D1
        is the average distance from the convergence reward for Agent 1,
        A⁢D2
        is the average distance from the convergence reward for Agent 2,
and
        A⁢D
        is the average of
        A⁢D1
        and
        A⁢D2
        .
All graphs of section
        5
        show
        A⁢D
        values.
Also,
        nr
        is the number of runs (in our
case always equal to 20).
Thus in the case of 4 fruits, we will have
        C⁢R1
        =
        C⁢R2
        =1200,
and if for all runs
        R1⁢j
        =
        R2⁢j
        =1190, then
        A⁢D
        =10.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Variable Exploration Rate
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         In this section we report results with different exploration
rates per training epoch (see section
         4
         ).
Table
         4
         shows
the average distance from the convergence reward over 20 runs
for 100,000 episodes per epoch,
for different numbers of fruits, and for all four methods
(Q-learning, PHC-LF, PHC-W, and PHC-WoLF).
It is clear that as the state space becomes larger 100,000
training episodes per epoch are not enough for convergence.
Also, for 1, 2, and 3 fruits all algorithms converge
and perform comparably.
As the number of fruits increases, Q-learning starts performing
worse than the multi-agent RL algorithms.
For 7 fruits PHC-W appears to perform worse than Q-learning
but this is because, as we can see in Figure
         5
         ,
in this case more than 400,000 episodes per epoch are required for
convergence. Thus after only 100,000 episodes per epoch all policies
still behave somewhat randomly.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Figures
         2
         ,
         3
         ,
         4
         ,
and
         5
         show the average distance
from the convergence reward as a function of the number of episodes
per epoch during training, for 4, 5, 6, and 7 fruits
respectively.
For 4 fruits it takes about 125,000 episodes per epoch and
for 5 fruits it takes about 225,000 episodes per epoch
for the policies to converge.
This number rises to approximately 350,000 for 6 fruits and
becomes even higher for 7 fruits.
Q-learning consistently performs worse than the rest of
the algorithms. The differences between PHC-LF,
PHC-W, and PHC-WoLF are insignificant, which is
a bit surprising given that
         Bowling and Veloso (2002)
         showed that PHC-WoLF performed better than
PHC in a series of benchmark tasks.
In Figures
         2
         and
         3
         ,
PHC-LF appears to be reaching convergence slightly
faster than PHC-W and PHC-WoLF
but this is not statistically significant.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Constant Exploration Rate
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         In this section we report results with a constant exploration
rate for all training epochs (see section
         4
         ).
Figures
         6
         and
         7
         show the average distance
from the convergence reward as a function of the number of episodes
per epoch during training, for 4 and 5 fruits
respectively.
Clearly having a constant exploration rate in all epochs
is problematic. For 4 fruits, after 225,000 episodes
per epoch there is still no convergence. For comparison,
with a variable exploration rate it took about 125,000 episodes
per epoch for the policies to converge.
Likewise for 5 fruits.
After 400,000 episodes
per epoch there is still no convergence. For comparison,
with a variable exploration rate it took about 225,000 episodes
per epoch for convergence.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         The above results show that, unlike single-agent RL where having
a constant exploration rate is perfectly acceptable, here a constant
exploration rate does not work.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
