<html>
<head>
<meta name="TextLength" content="SENT_NUM:9, WORD_NUM:205">
</head>
<body bgcolor="white">
<a href="#0" id="0">Our goal is to construct a translator from a full programming language like C or Java to first-order logic.</a>
<a href="#1" id="1">Once this is done, reasoning about programs can then be done in logic using techniques including but not limited to induction and loop invariants.</a>
<a href="#2" id="2">In this paper, we show how this is possible for a core procedural programming language with loops, functions, and simple pointers.</a>
<a href="#3" id="3">We have extended it to more complex mutable data structures including lists and trees and are working on extending it to thread-based concurrency.</a>
<a href="#4" id="4">The complexity of the translated first-order theory of a given program depends on what the program is about.</a>
<a href="#5" id="5">If all program variables are propositional, then the resulting first-order theory is decidable for proving both partial and total correctness of the program with respect to any given propositional specification.</a>
<a href="#6" id="6">If the program is about natural numbers and involves addition and multiplication, then we may need full arithmetic to reason about it.</a>
<a href="#7" id="7">If the program is about predicting the trajectory of a planet, then a theory of physics is needed in order to prove anything interesting about it.</a>
<a href="#8" id="8">How to integrate logical reasoning with a domain theory has long been a challenge in AI as well as in computer science.</a>
</body>
</html>