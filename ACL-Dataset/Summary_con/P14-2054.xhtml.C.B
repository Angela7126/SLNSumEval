<html>
 <head>
  <meta content="SENT_NUM:10, WORD_NUM:154" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   In this paper, we proposed two polynomial time decoding algorithms using joint inference for sentence compression.
  </a>
  <a href="#1" id="1">
   The first one is an exact dynamic programming algorithm, and requires O ( n 6 ) running time.
  </a>
  <a href="#2" id="2">
   This one does not show significant advantage in speed over ILP.
  </a>
  <a href="#3" id="3">
   The second one is an approximation of the first algorithm.
  </a>
  <a href="#4" id="4">
   It adopts Lagrangian relaxation to eliminate the compression ratio constraint, yielding lower time complexity T O ( n 4.
  </a>
  <a href="#5" id="5">
   In practice it achieves nearly the same accuracy as the exact one, but is much faster.
  </a>
  <a href="#6" id="6">
   3 3 Our code is available at http://code.google.com/p/sent-compress/.
  </a>
  <a href="#7" id="7">
   The main assumption of our method is that the dependency parse tree is projective, which is not true for some other languages.
  </a>
  <a href="#8" id="8">
   In that case, our method is invalid, but [ 17 ] still works.
  </a>
  <a href="#9" id="9">
   In the future, we will study the non-projective cases based on the recent parsing techniques for 1-endpoint-crossing trees [ 14 ].
  </a>
 </body>
</html>