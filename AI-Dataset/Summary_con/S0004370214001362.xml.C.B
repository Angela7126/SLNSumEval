<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:504">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have presented a method to improve music recommendation by tackling the problem of sparse tagging.</a>
<a href="#1" id="1">We propose a dynamic hybrid representation that combines tags and pseudo-tags to reduce the sparsity of a track-tag representation matrix of a given dataset.</a>
<a href="#2" id="2">There are two main contributions: the generation of pseudo-tags learned from similar tracks; and the dynamic combination of these pseudo-tags with existing tags.</a>
<a href="#3" id="3">Pseudo-tags are learned by aggregating tags from similar tracks; i.e. tracks whose audio content is similar according to the MFS music inspired texture representation.</a>
<a href="#4" id="4">We note that pseudo-tags are not learned from content, they are learned from content and tags for other tracks.</a>
<a href="#5" id="5">Tags capture human interpretations of low level music features as well as social/contextual concepts, and frequently used tags in musical neighbourhoods can provide a consensus of high level and social/contextual information.</a>
<a href="#6" id="6">For tracks that are weakly tagged, this has the effect that pseudo-tags enable them to inherit human interpretation of content and social/contextual information, from the tags of similar tracks.</a>
<a href="#7" id="7">In this way useful tag information is spread to neighbouring tracks in the content space.</a>
<a href="#8" id="8">The dynamic combination of these pseudo-tags with existing tags creates a hybrid representation which assigns more or less influence to pseudo-tags depending on how well-tagged a track is already.</a>
<a href="#9" id="9">Sparsely tagged tracks attract more pseudo-tags, and these new tags are more equally weighted with existing tags; well-tagged tracks use existing tags to dominate the representation.</a>
<a href="#10" id="10">Our Hybrid recommender system generates recommendations using these combined tags and pseudo-tags.</a>
<a href="#11" id="11">Synergy from a hybrid system should be able to outperform its component parts, regardless of the sparseness of tagging.</a>
<a href="#12" id="12">Our results demonstrate that Hybrid provides improved recommendations compared to Tag and Content individually.</a>
<a href="#13" id="13">The benefit from the social and contextual information in this combined meta-data can be seen in good recommendations when tracks are sparsely tagged.</a>
<a href="#14" id="14">There is also improved recommendation quality for well-tagged tracks, indicating that the small influence of pseudo-tags is not harmful but adds some diversification to the representation.</a>
<a href="#15" id="15">Sparsely tagged tracks suffer from the cold-start problem in music recommendation.</a>
<a href="#16" id="16">Since learning pseudo-tags is based on content-based retrieval, pseudo-tagging does not suffer from cold-start, unless all similar tracks are untagged.</a>
<a href="#17" id="17">For extreme cases of cold-start, when a track has no tags, pseudo-tags provide a stronger alternative to content.</a>
<a href="#18" id="18">We have shown that pseudo-tags with high precision may be learned by taking advantage of the order of tracks in content-based retrieval.</a>
<a href="#19" id="19">In future work, it will be interesting to investigate a similar approach with different tasks/domains.</a>
<a href="#20" id="20">For example, in a recommender system which uses collaborative filtering, it may be possible to reduce cold-start by learning pseudo-profiles for new users.</a>
<a href="#21" id="21">In this case the hybrid representation would potentially consist of real user track plays, and pseudo-user track plays.</a>
<a href="#22" id="22">There are other domains with dual representations that could benefit from using our dynamic approach to creating a hybrid representation; e.g. image retrieval with pixel content and incomplete captioning could exploit pseudo-captions; product recommendation with some available reviews could learn key comments for pseudo-reviews.</a>
</body>
</html>