<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:407">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article we have described a unified graph-based approach for measuring the semantic similarity of arbitrary pairs of linguistic items.</a>
<a href="#1" id="1">Our approach leverages random walks on semantic networks in order to obtain rich unified representations for different kinds of input linguistic items: senses, words, and texts.</a>
<a href="#2" id="2">Three sets of experiments were carried out, at three different linguistic levels, in order to evaluate the proposed similarity measure on multiple datasets and settings.</a>
<a href="#3" id="3">We demonstrated that the same unified approach can outperform state-of-the-art techniques, which are often limited in their type of input, across different linguistic levels, providing a reliable basis for measuring the similarity of arbitrary linguistic items for downstream NLP and AI applications.</a>
<a href="#4" id="4">We have shown how collaboratively-constructed resources such as Wiktionary can be transformed into semantic networks for reliable similarity measurement.</a>
<a href="#5" id="5">Moreover, we proposed two new techniques for handling words that are not defined in the lexical resource: one is based on a simple backing off to string similarity and the other exploits a large-scale taxonomy.</a>
<a href="#6" id="6">Improvements were obtained when using both techniques, although the former of the two, the simpler approach, proved to be the more effective.</a>
<a href="#7" id="7">We remark that our similarity measurement approach, in addition to being reliable, unified, and flexible, has an advantage over conventional similarity measurement techniques in that it provides the disambiguated linguistic items as a byproduct of similarity measurement.</a>
<a href="#8" id="8">As future work, we plan to try our similarity measure on semantic networks obtained from other collaboratively-constructed resources, such as Wikipedia and OmegaWiki, or from thesauri such as Roget's [44].</a>
<a href="#9" id="9">The Wikipedia graph is expected to be particularly suitable for measuring the similarity between texts as it provides a remarkable coverage of proper nouns and domain-specific terms.</a>
<a href="#10" id="10">We also intend to extend the approach so as to measure the semantic similarity of linguistic items across languages in the lines of [53], a goal that can be achieved by the help of large multilingual semantic networks such as BabelNet [18].</a>
<a href="#11" id="11">Finally, we are releasing the Java implementation of our system at https://github.com/pilehvar/adw/, providing the research community with an easy-to-use tool for performing semantic similarity of arbitrary linguistic items out of the box.</a>
<a href="#12" id="12">We also provide an online demo of ADW and the pre-computed semantic signatures for all the synsets in WordNet 3.0 at http://lcl.uniroma1.it/adw/.</a>
<a href="#13" id="13">We hope this framework will provide a reliable basis for similarity measurement in different NLP applications and foster further research in the development of unified similarity techniques.</a>
</body>
</html>