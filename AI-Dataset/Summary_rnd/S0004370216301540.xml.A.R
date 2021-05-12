<html>
<head>
<meta name="TextLength" content="SENT_NUM:12, WORD_NUM:314">
</head>
<body bgcolor="white">
<a href="#0" id="0">In the latter category of approaches where no assumption is made on pre-existing cross-system mappings, researches have been focused on capturing the group-level behaviors of users for knowledge transfer.</a>
<a href="#1" id="1">With the margin-based {a mathematical formula}δu(d), we can implement the active entity selection strategy introduced in Section 4.1.2 with the extended MMMF method.</a>
<a href="#2" id="2">We query their correspondences in the source system.</a>
<a href="#3" id="3">Therefore, besides focusing on prediction uncertainty, we need to take the long tail issue into consideration when designing an active entity selection strategy for building cross-system correspondences.</a>
<a href="#4" id="4">In the second experiment, we aim to verify the performance of our proposed active transfer learning framework plugging with different entity selection strategies.</a>
<a href="#5" id="5">)” in the table suggest that aligning all the source and target data to a unified item-user matrix and then performing state-of-the-art CF models on it cannot help to boost the recommendation performance, but may even hurt the performance compared to that of applying CF models on the target domain data only.</a>
<a href="#6" id="6">However, in many real-world scenarios, this assumption is hard to satisfy because users may only be familiar with some items in the system, and may fail to provide ratings on the actively selected items.</a>
<a href="#7" id="7">Therefore, we propose to use the following regularization term on the factor sub-matrices,{a mathematical formula} where {a mathematical formula}tr(⋅) denotes the trace of a matrix, and {a mathematical formula}LC(s)=[LU(s)00LV(s)], with {a mathematical formula}LU(s)=DU(s)−AU(s) and {a mathematical formula}LV(s)=DV(s)−AV(s), where {a mathematical formula}AU(s)=UC(s)⊤UC(s) and {a mathematical formula}AV(s)=VC(s)⊤VC(s) are the similarity matrices of the corresponding users and items in the source system, respectively.</a>
<a href="#8" id="8">This approach is also known as cross-system CF.</a>
<a href="#9" id="9">Margins on entities.</a>
<a href="#10" id="10">There remain 270,000 ratings on 3,500 books, and 1,400,000 ratings on 8,000 movies, given by {a mathematical formula}11,000 users.</a>
<a href="#11" id="11">Similarly, denote by {a mathematical formula}UC(d) and {a mathematical formula}VC(d) the factor sub-matrices for the entities in the target system, whose indices are in {a mathematical formula}C, respectively.</a>
</body>
</html>