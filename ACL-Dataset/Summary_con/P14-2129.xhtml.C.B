<html>
 <head>
  <meta content="SENT_NUM:10, WORD_NUM:242" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   We proposed a novel partial parsing approach for applications that require a fast syntactic analysis of the input beyond shallow bracketing.
  </a>
  <a href="#1" id="1">
   The span-limit parameter allows tuning the annotation of internal structure as appropriate for the application domain, trading off annotation complexity against inference time.
  </a>
  <a href="#2" id="2">
   These properties make hedge parsing potentially very useful for incremental text or speech processing, such as streaming text analysis or simultaneous translation.
  </a>
  <a href="#3" id="3">
   One interesting characteristic of these annotations is that they allow for string segmentation prior to inference, provided that the segment boundaries do not cross any hedge boundaries.
  </a>
  <a href="#4" id="4">
   We found that baseline segmentation models did provide a significant speedup in parsing, but that cascading errors remain a problem.
  </a>
  <a href="#5" id="5">
   There are many directions of future work to pursue here.
  </a>
  <a href="#6" id="6">
   First, the current results are all for exhaustive CYK parsing, and we plan to perform a detailed investigation of the performance of hedgebank parsing with prioritization and pruning methods of the sort available in BUBS [ 2 ].
  </a>
  <a href="#7" id="7">
   Further, this sort of annotation seems well suited to incremental parsing with beam search, which has been shown to achieve high accuracies even for fully connected parsing [ 14 ].
  </a>
  <a href="#8" id="8">
   Improvements to the transform (e.g.,, grouping items not in hedges under non-terminals) and to the segmentation model (e.g.,, increasing precision at the expense of recall) could improve accuracy without greatly reducing efficiency.
  </a>
  <a href="#9" id="9">
   Finally, we intend to perform an extrinsic evaluation of this parsing in an on-line task such as simultaneous translation.
  </a>
 </body>
</html>