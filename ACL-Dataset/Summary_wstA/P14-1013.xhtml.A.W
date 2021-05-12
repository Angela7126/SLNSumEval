<html>
 <head>
  <meta content="SENT_NUM: 7, WORD_NUM: 173" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   Due to their origin in computer graphics, graphics processing units (GPUs) are highly optimized for dense problems, where the exact same operation is applied repeatedly to all data points.
  </a>
  <a href="#1" id="1">
   Natural language processing algorithms, on the other hand, are traditionally constructed in ways that exploit structural sparsity.
  </a>
  <a href="#2" id="2">
   Recently, Canny et al. ( 2013 ) presented an approach to GPU parsing that sacrifices traditional sparsity in exchange for raw computational power, obtaining a system that can compute Viterbi parses for a high-quality grammar at about 164 sentences per second on a mid-range GPU.
  </a>
  <a href="#3" id="3">
   In this work, we reintroduce sparsity to GPU parsing by adapting a coarse-to-fine pruning approach to the constraints of a GPU.
  </a>
  <a href="#4" id="4">
   The resulting system is capable of computing over 404 Viterbi parses per second more than a 2x speedup on the same hardware.
  </a>
  <a href="#5" id="5">
   Moreover, our approach allows us to efficiently implement less GPU-friendly minimum Bayes risk inference, improving throughput for this more accurate algorithm from only 32 sentences per second unpruned to over 190 sentences per second using pruning nearly a 6x speedup.
  </a>
 </body>
</html>