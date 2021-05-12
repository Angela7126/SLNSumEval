<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:285">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have presented MultiWiBi, a new approach for constructing bitaxonomies of Wikipedia in arbitrary languages, where each bitaxonomy is made up of two taxonomies which establish is-a relations between Wikipedia pages and categories, respectively.</a>
<a href="#1" id="1">For each language, the approach is mainly divided into three phases.</a>
<a href="#2" id="2">The first phase aims at building a taxonomy for the page side of Wikipedia; the second phase triggers an iterative algorithm that incrementally populates a taxonomy for the category side of Wikipedia by exploiting the interlanguage links existing between the two sides; the third phase is aimed at solving some problems affecting the structure of Wikipedia categories so as to output a polished category taxonomy.</a>
<a href="#3" id="3">Our contribution is three-fold.</a>
<a href="#4" id="4">First, the two taxonomies of each bitaxonomy are aligned (pages are aligned to categories) and the bitaxonomies are also aligned across languages (concepts in English are aligned to the corresponding concepts in all other languages).</a>
<a href="#5" id="5">Second, in marked contrast to other approaches, our work crucially pivots on the English edition of Wikipedia for inducing bitaxonomies in the other languages, without relying on any external resource (like WordNet or manual upper ontologies), parallel corpus or tool.</a>
<a href="#6" id="6">Third, our experiments show that our bitaxonomies are characterized by higher accuracy and specificity than all other alternatives, making MultiWiBi the best set of taxonomies in the literature at the time of writing.</a>
<a href="#7" id="7">We have also integrated MultiWiBi into BabelNet,{sup:18} thanks to which a full-fledged taxonomy of lexicographic and encyclopedic knowledge is now available.</a>
<a href="#8" id="8">In order to maintain a high precision we integrated all those edges in MultiWiBi for which taxonomies in different languages agree.</a>
<a href="#9" id="9">We plan to exploit MultiWiBi in several applications such as multilingual distributional semantics [62], [63] and question answering.</a>
</body>
</html>