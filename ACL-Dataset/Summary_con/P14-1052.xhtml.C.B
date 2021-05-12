<html>
 <head>
  <meta content="SENT_NUM:13, WORD_NUM:207" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We have proposed STRUCT, a general-purpose natural language generation system which is comparable to current state-of-the-art generators.
  </a>
  <a href="#1" id="1">
   STRUCT formalizes the generation problem as an MDP and applies a version of the UCT algorithm, a fast online MDP planner, to solve it.
  </a>
  <a href="#2" id="2">
   Thus, STRUCT naturally handles probabilistic grammars.
  </a>
  <a href="#3" id="3">
   We demonstrate empirically that STRUCT is anytime, comparable to existing generation-as-planning systems in certain NLG tasks, and is also capable of handling other, more complex tasks such as negated communicative goals.
  </a>
  <a href="#4" id="4">
   Though STRUCT has many interesting properties, many directions for exploration remain.
  </a>
  <a href="#5" id="5">
   Among other things, it would be desirable to integrate STRUCT with discourse planning and dialog systems.
  </a>
  <a href="#6" id="6">
   Fortunately, reinforcement learning has already been investigated in such contexts [ 13 ] , indicating that an MDP-based generation procedure could be a natural fit in more complex generation systems.
  </a>
  <a href="#7" id="7">
   This is a primary direction for future work.
  </a>
  <a href="#8" id="8">
   A second direction is that, due to the nature of the approach, STRUCT is highly amenable to parallelization.
  </a>
  <a href="#9" id="9">
   None of the experiments reported here use parallelization, however, to be fair to CRISP.
  </a>
  <a href="#10" id="10">
   We plan to parallelize STRUCT in future work, to take advantage of current multicore architectures.
  </a>
  <a href="#11" id="11">
   This should obviously further reduce generation time.
  </a>
  <a href="#12" id="12">
   STRUCT is open source and available from github.com upon request.
  </a>
 </body>
</html>