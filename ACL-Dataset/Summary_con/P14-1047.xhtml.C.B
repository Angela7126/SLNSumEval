<html>
 <head>
  <meta content="SENT_NUM:23, WORD_NUM:532" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We used single-agent RL and multi-agent RL for learning dialogue policies in a resource allocation negotiation scenario.
  </a>
  <a href="#1" id="1">
   Two agents interacted with each other and both learned at the same time.
  </a>
  <a href="#2" id="2">
   The advantage of this approach is that it does not require SUs to train against or corpora to learn from.
  </a>
  <a href="#3" id="3">
   We compared a traditional single-agent RL algorithm (Q-learning) against two multi-agent RL algorithms (PHC and PHC-WoLF) varying the scenario complexity (state space size), the number of training episodes, and the learning and exploration rates.
  </a>
  <a href="#4" id="4">
   Our results showed that Q-learning is not suitable for concurrent learning given that it is designed for learning against a stationary environment.
  </a>
  <a href="#5" id="5">
   Q-learning failed to converge in all cases, except for very small state space sizes.
  </a>
  <a href="#6" id="6">
   On the other hand, both PHC and PHC-WoLF always converged (or in the case of 7 fruits they needed more training episodes) and performed similarly.
  </a>
  <a href="#7" id="7">
   We also showed that in concurrent learning very high gradually decreasing exploration rates are required for convergence.
  </a>
  <a href="#8" id="8">
   We conclude that multi-agent RL of dialogue policies is a promising alternative to using single-agent RL and SUs or learning directly from corpora.
  </a>
  <a href="#9" id="9">
   The focus of this paper is on comparing single-agent RL and multi-agent RL for concurrent learning, and studying the implications for convergence and exploration/learning rates.
  </a>
  <a href="#10" id="10">
   Our next step is testing with human users.
  </a>
  <a href="#11" id="11">
   We are particularly interested in users whose behavior changes during the interaction and continuous testing against expert repeat users, which has never been done before.
  </a>
  <a href="#12" id="12">
   Another interesting question is whether corpora or SUs may still be required for designing the state and action spaces and the reward functions of the interlocutors, bootstrapping the policies, and ensuring that information about the behavior of human users is encoded in the resulting learned policies.
  </a>
  <a href="#13" id="13">
   Ga i et al.
  </a>
  <a href="#14" id="14">
   2013 ) showed that it is possible to learn full dialogue policies just via interaction with human users (without any bootstrapping using corpora or SUs.
  </a>
  <a href="#15" id="15">
   Similarly, concurrent learning could be used in an on-line fashion via live interaction with human users.
  </a>
  <a href="#16" id="16">
   Or alternatively concurrent learning could be used off-line to bootstrap the policies and then these policies could be improved via live interaction with human users (again using concurrent learning to address possible changes in user behavior.
  </a>
  <a href="#17" id="17">
   These are open research questions for future work.
  </a>
  <a href="#18" id="18">
   Furthermore, we intend to apply multi-agent RL to more complex negotiation domains, e.g.,, experiment with more than two types of resources (not just apples and oranges) and more types of actions (not just offers and acceptances.
  </a>
  <a href="#19" id="19">
   We would also like to compare policies learned with multi-agent RL techniques with policies learned with SUs or from corpora both in simulation and with human users.
  </a>
  <a href="#20" id="20">
   Finally, we aim to experiment with different feature-based representations of the state and action spaces.
  </a>
  <a href="#21" id="21">
   Currently all possible deal combinations are listed as possible actions and as elements of the state, which can quickly lead to very large state and action spaces as the application becomes more complex (in our case as the number of fruits increases.
  </a>
  <a href="#22" id="22">
   However, abstraction is not trivial because the agents have no guarantee that the value of a deal is a simple function of the value of its parts, and values may differ for different agents.
  </a>
 </body>
</html>