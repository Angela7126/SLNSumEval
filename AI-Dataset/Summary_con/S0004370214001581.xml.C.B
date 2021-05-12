<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:420">
</head>
<body bgcolor="white">
<a href="#0" id="0">Taking “some deletes into account” has been a challenge ever since delete relaxation heuristics were first invented.</a>
<a href="#1" id="1">Red–black planning tackles this challenge by relaxing only a subset of the state variables, thus generalizing both regular and delete-relaxed planning, and allowing to smoothly interpolate between the two.</a>
<a href="#2" id="2">We have provided a first complexity analysis and, focusing on a particular tractable fragment, have shown that practically useful heuristic functions can be derived this way.</a>
<a href="#3" id="3">In our view, the main virtue of the red–black planning framework lies in its elegance and simplicity.</a>
<a href="#4" id="4">We believe that we have only scratched the surface of both, its analysis, and its potentially useful applications.</a>
<a href="#5" id="5">On the theory side, a major construction site is the structural analysis of dependencies across black and red variables.</a>
<a href="#6" id="6">Can one restrict these in interesting ways to obtain tractability?</a>
<a href="#7" id="7">In particular, as we have shown, just by considering the black causal graph, useful tractable fragments can be obtained.</a>
<a href="#8" id="8">But what about the combined red–black causal graph?</a>
<a href="#9" id="9">Can one identify interesting fragments based on criteria on that graph, taking the different vertex colors into account?</a>
<a href="#10" id="10">On the practical side, a major issue – not just for red–black planning but for partial delete relaxation in general – is the runtime overhead incurred by the more complex reasoning inside the heuristic function.</a>
<a href="#11" id="11">This severely limits the amount of “un-relaxation” one can apply, to the point of rendering the interpolation ability useless.</a>
<a href="#12" id="12">But no one forces us to use red–black planning that way!</a>
<a href="#13" id="13">We believe that there is a space of unlimited possibilities in alternate uses.</a>
<a href="#14" id="14">Instead of generating a new red–black plan for every search state, one could generate one red–black plan, or a small set of red–black plans, for the initial state only, i.e., allow substantial runtime to obtain highly “un-relaxed” plan templates.</a>
<a href="#15" id="15">One could then design distance-to-template heuristics for guiding state space search.</a>
<a href="#16" id="16">Another possibility is to use the templates as seed plans in plan-space searches such as partial-order planning (e.g. [49], [50]) or LPG [10], or to seed Nakhost and Müller's plan neighborhood graph search [51].</a>
<a href="#17" id="17">Finally, an exciting approach is incremental red–black planning, where one would obtain a relaxed plan in iteration 0, paint one more variable black in every iteration, and rely on the information obtained when solving iteration i to provide search guidance for iteration {a mathematical formula}i+1.</a>
<a href="#18" id="18">In summary, red–black planning is an elegant approach to partial delete relaxation, whose exploration has only just begun.</a>
<a href="#19" id="19">We hope that other researchers will be inspired to join us in this effort.</a>
</body>
</html>