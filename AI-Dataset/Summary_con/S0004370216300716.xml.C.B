<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:646">
</head>
<body bgcolor="white">
<a href="#0" id="0">Centrality and importance in social networks are closely interlinked concepts.</a>
<a href="#1" id="1">Central vertices are assumed to be important and vice versa.</a>
<a href="#2" id="2">However, in real-world online social networks, people who are considered important or authoritative on some topics may be considered very unimportant on others.</a>
<a href="#3" id="3">For instance, an influential sports commentator is not likely to be an influential movie critic.</a>
<a href="#4" id="4">Moreover, the importance of an individual should be measured by an influence related factor.</a>
<a href="#5" id="5">A person who can influence 1000 people about movies should be considered more important (with regard to movies) than one who can influence just 500.</a>
<a href="#6" id="6">Diffusion models are a mechanism to capture the spread of concepts or phenomena through a network.</a>
<a href="#7" id="7">Many diffusion models have been developed to successfully predict the extent of spread of memes and concepts through networks.</a>
<a href="#8" id="8">In this paper, we propose the novel concept of Diffusion Centrality and show how it can be computed with respect to a wide array of diffusion models.</a>
<a href="#9" id="9">[51] shows that the framework of generalized annotated programs (GAPs) can express most known diffusion models.</a>
<a href="#10" id="10">In this paper, we increase the breadth of knowledge about GAPs by introducing novel specific classes of GAPs and present the HyperDC algorithm that exactly computes the top-k diffusion centrality vertices w.r.t.</a>
<a href="#11" id="11">any GAP-expressible diffusion models.</a>
<a href="#12" id="12">In addition, we present a novel (but approximate) Coarsening Back and Forth (CBAF) algorithm that allows us to take a huge social network, and reduce it to a manageable size to efficiently solve (in an approximate way) the problem of finding the top-k vertices.</a>
<a href="#13" id="13">We conduct a very detailed experimental study on several real-world social networks.</a>
<a href="#14" id="14">A first set of experiments compares the runtime and spread generated via the HyperDC algorithm with classical centrality measures.</a>
<a href="#15" id="15">Our results show that HyperDC is efficient and produces better spread than current centrality measures.</a>
<a href="#16" id="16">A second set of experiments looks at the scalability of CBAF, showing that it almost always has a lower runtime than HyperDC, while achieving high spreads.</a>
<a href="#17" id="17">In particular, CBAF was tested on networks with over 2M vertices and over 20M edges and achieved acceptable runtime.</a>
<a href="#18" id="18">Using MemeTracker data, we show that diffusion centrality captures the importance of people who are truly responsible for the spread of a meme more effectively than past centrality measures.</a>
<a href="#19" id="19">This work opens up a dramatic new set of possible diffusion models that can be automatically learned from data that take into account the rich semantics that can be associated with vertices and edges in modern social networks like Twitter, Facebook, and LinkedIn.</a>
<a href="#20" id="20">For instance, in the case of predicting election outcomes using Twitter data [30], we might learn rules that identify the likelihood that person P will vote for a candidate C by taking their gender, demographic factors, tweets, and the tendencies of their neighbors to vote for C. Alternatively, we might look at the diffusion of banking crises throughout the world's nations by considering network flows of exposures—the nodes in such a network would be countries and the edges would be labeled with the exposure a country has to another [44].</a>
<a href="#21" id="21">High exposure of country A to country B would suggest that a systemic banking crisis in country B could lead to default, triggering a systemic banking crisis in country A. Clearly, there are many other factors to be considered.</a>
<a href="#22" id="22">For instance, political factors (represented as semantic properties of vertices) might capture the likelihood of country A taking intelligent steps to forestall a crisis.</a>
<a href="#23" id="23">Mutual trust (a property of the edge) might determine whether A and B can work together to address the problem.</a>
<a href="#24" id="24">Such a diffusion model will use the rich semantic opportunities offered by research in knowledge representation via GAPs, as well as other paradigms, to learn more fine-grained diffusion models than the relatively coarse grained diffusion models that were developed in the past.</a>
<a href="#25" id="25">We believe this would form a rich line of inquiry for the future.</a>
</body>
</html>