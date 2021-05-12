<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:317">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have introduced STR3, a new GAC algorithm for positive table constraints that is competitive and complementary to STR2, a state-of-the-art algorithm.</a>
<a href="#1" id="1">STR3 is able to completely avoid unnecessary traversal of tables.</a>
<a href="#2" id="2">Along with AC5TC [31], STR3 is one of the only two path-optimal GAC algorithms that have been reported so far.</a>
<a href="#3" id="3">Unlike AC5TC's performance, which declines as arity increases, STR3's is consistent across a wide range of arity.</a>
<a href="#4" id="4">Indeed, we have shown that it correlates to the average proportion (avgP) and number (avgS) of tuples remaining in tables during search.</a>
<a href="#5" id="5">Compared to STR2, STR3 is faster on problems in which avgP and avgS are not low.</a>
<a href="#6" id="6">Interestingly, the advantage of STR2 appears to depend largely on excessively high rates of table reduction (very low avgP).</a>
<a href="#7" id="7">As soon as the reduction rate drops below 90%, STR2 becomes much less effective.</a>
<a href="#8" id="8">Another dividing line is satisfiability: STR3 is stronger on unsatisfiable problems but weaker on satisfiable problems whereas STR2 is the opposite.</a>
<a href="#9" id="9">STR3 is an instance of fine-grained algorithms as its propagation is guided by deleted values.</a>
<a href="#10" id="10">Both STR2 and STR3 are extended to handle compressed tuples (c-tuples) in [36].</a>
<a href="#11" id="11">While STR3 is more complex than STR2, once implemented the algorithm is easier to extend because it is based on just one notion: checking a tuple's validity; as a result, only the routine involving validity test needs modification.</a>
<a href="#12" id="12">By contrast, STR2 may process a tuple twice in different manners — testing its validity and then collecting values from its components.</a>
<a href="#13" id="13">Extending STR2 to cope with c-tuples is therefore twice more complicated conceptually.</a>
<a href="#14" id="14">This is true for fine-grained vs.</a>
<a href="#15" id="15">coarse-grained propagation in general.</a>
<a href="#16" id="16">In recent years, STR2 has been incorporated into many other algorithms [45], [46], [47], [48], and it remains to be seen whether STR3 can be adopted in a similar fashion.</a>
<a href="#17" id="17">The work which extends STR2 and STR3 to c-tuples [36] is a start in this direction.</a>
</body>
</html>