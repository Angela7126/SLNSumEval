<html>
<head>
<meta name="TextLength" content="SENT_NUM:12, WORD_NUM:357">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented a semantic mapping system that creates a triangle mesh of an office environment, detects several classes of furniture, and replaces them by their corresponding CAD models, based on Kinect point cloud data captured using a mobile robot.</a>
<a href="#1" id="1">The system was evaluated both on single frames and fully registered scenes of two datasets containing 810 single point clouds.</a>
<a href="#2" id="2">Our system achieved a detection rate of 46.0% for the office dataset, containing one particularly large object and several seamlessly connected instances of shelves and of 79.4% on the seminar room with less variation of the classified furniture.</a>
<a href="#3" id="3">The current system creates a hybrid semantic map (i.e., the map data contains geometric information as well as semantic knowledge); it does so incrementally by processing each RGB-D frame separately; and it also does so in closed loop by feeding the output of the reasoning system back into the low-level data interpretation routine.</a>
<a href="#4" id="4">In future work, we intend to implement an active data interpretation/gathering loop that identifies and actively explores regions with potentially valuable but missing data, thereby closing the loop even down to the action level, not just the perception level.</a>
<a href="#5" id="5">Another necessary improvement is a matching criterion that decides how well a CAD model was matched in the point cloud.</a>
<a href="#6" id="6">Such a criterion could be used to reject false hypotheses, and to disambiguate between similar models.</a>
<a href="#7" id="7">The performance of the final ICP pose correction could be improved by explicitly taking occlusion into account.</a>
<a href="#8" id="8">Instead of trying to match a full CAD model to the point cloud, a pre-assignment filter similar to [49] could take only those CAD model points into account, which are expected to have a corresponding point in the sensor data and vice versa.</a>
<a href="#9" id="9">Furthermore, we need to improve the generation of the object hypotheses, especially in scenes where we detect planes that are larger than expected due to gap-free placement of several pieces of furniture.</a>
<a href="#10" id="10">On top of this it could prove worthwhile to incorporate the color information provided by RGB-D cameras when merging planar regions.</a>
<a href="#11" id="11">Last, we plan to automate the extraction of OWL-DL structural models for hypothesis generation from the CAD models.</a>
</body>
</html>