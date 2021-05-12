<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Building Sentiment Lexicons for All Major Languages.
  </title>
 </head>
 <body>
  <div class="ltx_page_main">
   <div class="ltx_page_content">
    <div class="ltx_document ltx_authors_1line">
     <div class="ltx_abstract">
      <h6 class="ltx_title ltx_title_abstract">
       Abstract
      </h6>
      <p class="ltx_p">
       Sentiment analysis in a multilingual world remains a challenging problem, because developing language-specific sentiment lexicons is an extremely resource-intensive process. Such lexicons remain a scarce resource for most languages.
      </p>
      <p class="ltx_p">
       In this paper, we address this lexicon gap by building high-quality sentiment lexicons for 136 major languages. We integrate a variety of linguistic resources to produce an immense knowledge graph. By appropriately propagating from seed words, we construct sentiment lexicons for each component language of our graph. Our lexicons have a polarity agreement of 95.7% with published lexicons, while achieving an overall coverage of 45.2%.
      </p>
      <p class="ltx_p">
       We demonstrate the performance of our lexicons in an extrinsic analysis of 2,000 distinct historical figures’ Wikipedia articles on 30 languages. Despite cultural difference and the intended neutrality of Wikipedia articles, our lexicons show an average sentiment correlation of 0.28 across all language pairs.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Introduction
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        Sentiment analysis of English texts has become a large and active research area, with many commercial applications, but the barrier of language limits the ability to assess the sentiment of most of the world’s population.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Although several well-regarded sentiment lexicons are available in English
        [9, 17]
        , the same is not true for most of the world’s languages. Indeed, our literature search identified only 12
        publicly available
        sentiment lexicons for only 5 non-English languages (Chinese mandarin, German, Arabic, Japanese and Italian). No doubt we missed some, but it is clear that these resources are not widely available for most important languages.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we strive to produce a comprehensive set of sentiment lexicons for the worlds’ major languages. We make the following contributions:
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           New Sentiment Analysis Resources
           –
We have generated sentiment lexicons for 136 major languages via graph propagation which are now publicly available
           . We validate our own work through other publicly available, human annotated sentiment lexicons. Indeed, our lexicons have polarity agreement of 95.7% with these published lexicons, plus an overall coverage of 45.2%.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Large-Scale Language Knowledge Graph Analysis
           –
We have created a massive comprehensive knowledge graph of 7 million vocabulary words from 136 languages with over 131 million semantic inter-language links, which proves valuable when doing alignment between definitions in different languages.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Extrinsic Evaluation
           –
We elucidate the sentiment consistency of entities reported in different language editions of Wikipedia using our propagated lexicons. In particular, we pick 30 languages and compute sentiment scores for 2,000 distinct historical figures. Each language pair exhibits a Spearman sentiment correlation of at least 0.14, with an average correlation of 0.28 over all pairs.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        The rest of this paper is organized as follows.
We review related work in Section
        2
        . In Section
        3
        , we describe our resource processing and design decisions. Section
        4
        discusses graph propagation methods to identify sentiment polarity across languages. Section
        5
        evaluates our results against each available human-annotated lexicon. Finally, in Section
        6
        we present our extrinsic evaluation of sentiment consistency in Wikipedia prior to our conclusions.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Sentiment analysis is an important area of NLP with a large and growing literature. Excellent surveys of the field include
        [18, 21]
        , establishing that rich online resources have greatly expanded opportunities for opinion mining and sentiment analysis.
        Godbole et al. (2007)
        build up an English lexicon-based sentiment analysis system to evaluate the general reputation of entities.
        Taboada et al. (2011)
        present a more sophisticated model by considering patterns, including negation and repetition using adjusted weights.
        Liu (2010)
        introduces an efficient method, at the state of the art, for doing sentiment analysis and subjectivity in English.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Researchers have investigated topic or domain dependent approaches to identify opinions.
        Jijkoun et al. (2010)
        focus on generating topic specific sentiment lexicons.
        Li et al. (2010)
        extract sentiment with global and local topic dependency.
        Gindl et al. (2010)
        perform sentiment analysis according to cross-domain contextualization and
        Pak and Paroubek (2010)
        focus on Twitter, doing research on colloquial format of English.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Work has been done to generalize sentiment analysis to other languages.
        Denecke (2008)
        performs multilingual sentiment analysis using SentiWordNet.
        Mihalcea et al. (2007)
        learn multilingual subjectivity via cross-lingual projections.
        Abbasi et al. (2008)
        extract specific language features of Arabic which requires language-specific knowledge.
        Gînscă et al. (2011)
        work on better sentiment analysis system in Romanian.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        The ready availability of machine translation to and from English has prompted efforts to employ translation for sentiment analysis
        [6]
        .
        Banea et al. (2008)
        demonstrate that machine translation can perform quite well when extending the subjectivity analysis to multi-lingual environment, which makes it inspiring to replicate their work on lexicon-based sentiment analysis.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Machine learning approaches to sentiment analysis are attractive, because of the promise of reduced manual processing.
        Boiy and Moens (2009)
        conduct machine learning sentiment analysis using multilingual web texts. Deep learning approaches draft off of distributed word embedding which offer concise features reflecting the semantics of the underlying vocabulary.
        Turian et al. (2010)
        create powerful word embedding by training on real and corrupted phrases, optimizing for the replaceability of words.
        Zou et al. (2013)
        combine machine translation and word representation to generate bilingual language resources.
        Socher et al. (2012)
        demonstrates a powerful approach to English sentiment using word embedding, which can easily be extended to other languages by training on appropriate text corpora.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Knowledge Graph Construction
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section we will describe how we leverage off a variety of NLP resources to construct the semantic connection graph we will use to propagate sentiment lexicons.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The Polyglot project
        [3]
        identified the 100,000 most frequently used words in each language’s Wikipedia. Drawing a candidate lexicon from Wikipedia has some downsides (e.g. limited use of informal words), but is representative and convenient over a large number of languages. In particular, we collect total of 7,741,544 high-frequency words from 136 languages to serve as vertices in our graph.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        We seek to identify as many semantic links across languages as possible to connect our network, and so integrated several resources:
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           Wiktionary
           – This growing resource has entries for 171 languages, edited by people with sufficient background knowledge. Wiktionary provides about 19.7% of the total links covering 382,754 vertices in our graph.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           Machine Translation
           -
We script the Google translation API to get even more semantic links. In particular we ask for translations of each word in our English vocabulary to 57 languages with available translators as well as going from each known vocabulary word in other languages to English. In total, machine translation provides 53.2% of the total links and establishes connections between 3.5 million vertices.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           Transliteration Links
           –
Natural flow brings words across languages with little morphological change. Closely related language pairs (i.e. Russian and Ukrainian) share many characters/words in common. Though not always true, words with same spelling usually have similar meanings so this can improve the coverage of semantic links. Transliteration provides 22.1% of the total links in our experiment.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           WordNet
           –
Finally, we gather synonyms and antonyms of English words from WordNet, which prove particularly useful in propagating sentiment across languages.
In total we collect over 100,000 pairs of synonyms and antonyms and created 5.0% of the total links.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Links do not always agree in a bidirectional manner, particularly for multi-sense words, thus all links in our network are unidirectional. Figure
        1
        illustrates how we encode links from different resources in an integer edge value.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Graph Propagation
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Sentiment propagation starts from English sentiment lexicons. Through semantic links in our knowledge graph, words are able to extend their sentiment polarities to adjacent neighbors. We experimented with both graph propagation algorithm
        [28]
        and label propagation algorithm
        [29, 22]
        . The primary difference between is that label propagation takes multiple paths between two vertices into consideration, while graph propagation utilizes only the best path between word pairs.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We report results from using Liu’s lexicons
        [17]
        as seed words. Liu’s lexicons contain 2006 positive words and 4783 negative words. Of these, 1422 positive words and 2956 negative words (roughly 64.5%) appear among the 100,000 English vertices in our graph.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Our knowledge network is comprised of links from a heterogeneous collection of sources, of different coverage and reliability. For the task of deciding sentiment polarity of words, only antonym links are negative. An edge gains zero weight if both negative and positive links exist. Edges having multiple positive links will be credited the highest weight among all these links. We conducted a grid search on the weight of each type of links to maximize the best overall accuracy on our test data of published non-English sentiment lexicons. To avoid potential overfitting problems, grid search starts from SentiWordNet English lexicons
        [9]
        instead of Liu’s.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Lexicon Evaluation
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        We collected all available published sentiment lexicons from non-English languages to serve as standard for our evaluation, including Arabic, Italian, German and Chinese. Coupled with English sentiment lexicons provides in total seven different test cases to experiment against, specifically:
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <ul class="ltx_itemize" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           Arabic
           :
           [2]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           German
           :
           [23]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           English
           :
           [9]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i4.p1">
          <p class="ltx_p">
           Italian
           :
           [5]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i5" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i5.p1">
          <p class="ltx_p">
           Japanese
           :
           [15]
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i6" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i6.p1">
          <p class="ltx_p">
           Chinese-1
           ,
           Chinese-2
           :
           [13]
           .
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        We present the accuracy and coverage achieved by two propagation model in Table
        1
        . Both models achieve similar accuracy while slightly more words in graph propagation can be verified via published lexicons. Performance is not good on Japanese because of mismatching between our dictionary and the test data.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        Table
        2
        reveals that very sparse sentiment lexicons resulted for a small but notable fraction of the languages we analyzed.
In particular, only 20 languages yielded lexicons of less than 100 words. Without exception, they all have very small available definitions in Wikitionary. By contrast, 48 languages had lexicons with over 2,000 words, another 16 with between 1,000 and 2,000: clearly large enough to perform a meaningful analysis.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Extrinsic Evaluation: Consistency of Wikipedia Sentiment
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        We consider evaluating our lexicons on the consistency of Wikipedia pages about a particular individual person among various languages. As our candidate entities for analysis, we use the Wikipedia pages of 2,000 most significant people as measured in the recent book
        Who’s Bigger?
        [24]
        . The sentiment polarity of a page is simply computed by subtracting the number of negative words from that of positive words, divided by the sum of both.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        The differing ratio of positive and negative polarity terms in Table
        2
        means that sentiment cannot be directly compared across languages. For more consistent evaluation we compute the z-score of each entity against the distribution of all its language’s entities.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        We use the Spearman correlation coefficient to measure the consistence of sentiment distribution across all entities with pages in a particular language pair.
Figure
        2
        shows the results for 30 languages with largest propagated sentiment lexicon size. All pairs of language exhibit positive correlation (and hence generally stable and consistent sentiment), with an average correlation of 0.28.
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Finally, Table
        3
        illustrates sentiment consistency over all 136 languages (represented by blue tick marks), with the first 10 languages in Figure
        2
        granted labels.
Respected artists like
        Steven Spielberg
        and
        Leonardo da Vinci
        show as consistently positive sentiment as notorious figures like
        Osama bin Laden
        and
        Adolf Hitler
        are negative.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
