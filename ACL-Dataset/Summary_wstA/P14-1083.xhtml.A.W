<html>
 <head>
  <meta content="SENT_NUM: 9, WORD_NUM: 170" name="TextLength"/>
 </head>
 <body bgcolor="white">
  <a href="#0" id="0">
   Recent work has shown success in using neural network language models (NNLMs) as features in MT systems.
  </a>
  <a href="#1" id="1">
   Here, we present a novel formulation for a neural network joint model (NNJM), which augments the NNLM with a source context window.
  </a>
  <a href="#2" id="2">
   Our model is purely lexicalized and can be integrated into any MT decoder.
  </a>
  <a href="#3" id="3">
   We also present several variations of the NNJM which provide significant additive improvements.
  </a>
  <a href="#4" id="4">
   Although the model is quite simple, it yields strong empirical results.
  </a>
  <a href="#5" id="5">
   On the NIST OpenMT12 Arabic-English condition, the NNJM features produce a gain of +3.0 BLEU on top of a powerful, feature-rich baseline which already includes a target-only NNLM.
  </a>
  <a href="#6" id="6">
   The NNJM features also produce a gain of +6.3 BLEU on top of a simpler baseline equivalent to Chiang s [ 5 ] original Hiero implementation.
  </a>
  <a href="#7" id="7">
   Additionally, we describe two novel techniques for overcoming the historically high cost of using NNLM-style models in MT decoding.
  </a>
  <a href="#8" id="8">
   These techniques speed up NNJM computation by a factor of 10,000x, making the model as fast as a standard back-off LM.
  </a>
 </body>
</html>