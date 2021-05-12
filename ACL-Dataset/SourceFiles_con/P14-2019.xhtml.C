<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Constructing a Turkish-English Parallel TreeBank.
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
       In this paper, we report our preliminary efforts in building an English-Turkish parallel treebank corpus for statistical machine translation. In the corpus, we manually generated parallel trees for about 5,000 sentences from Penn Treebank. English sentences in our set have a maximum of 15 tokens, including punctuation. We constrained the translated trees to the reordering of the children and the replacement of the leaf nodes with appropriate glosses. We also report the tools that we built and used in our tree translation task.
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
        Turkish is an agglutinative and morphologically rich language with a free constituent order. Although statistical NLP research on Turkish has taken significant steps in recent years, much remains to be done. Especially for the annotated corpora, Turkish is still behind similar languages such as Czech, Finnish, or Hungarian. For example, EuroParl corpus
        [13]
        , one of the biggest parallel corpora in statistical machine translation, contains 22 languages (but not Turkish). Although there exist some recent works to produce parallel corpora for Turkish-English pair, the produced corpus is only applicable for phrase-based training
        [22, 8]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In recent years, many efforts have been made to annotate parallel corpora with syntactic structure to build parallel treebanks. A parallel treebank is a parallel corpus where the sentences in each language are syntactically (if necessary morphologically) annotated, and the sentences and words are aligned. In the parallel treebanks, the syntactic annotation usually follows constituent and/or dependency structure. Well-known parallel treebank efforts are
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Prague Czech-English dependency treebank annotated with dependency structure
           [6]
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           English-German parallel treebank, annotated with POS, constituent structures, functional relations, and predicate-argument structures
           [7]
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Linköping English-Swedish parallel treebank that contains 1,200 sentences annotated with POS and dependency structures
           [1]
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i4.p1">
          <p class="ltx_p">
           Stockholm multilingual treebank that contains 1,000 sentences in English, German and Swedish annotated with constituent structure
           [12]
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this study, we report our preliminary efforts in constructing an English-Turkish parallel treebank corpus for statistical machine translation. Our approach converts English parse trees into equivalent Turkish parse trees by applying several transformation heuristics. The main components of our strategy are (i) tree permutation, where we permute the children of a node; and (ii) leaf replacement, where we replace English word token at a leaf node.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        This paper is organized as follows: In Section
        2
        , we give the literature review for parallel treebank construction efforts in Turkish. In Section
        3
        , we give a very brief overview on Turkish syntax. We give the details of our corpus construction strategy in Section
        4
        and explain our transformation heuristics in Section
        5
        . Finally, we conclude in Section
        6
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Literature Review
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Turkish Treebank creation efforts started with the METU-Sabancı dependency Treebank. METU-Sabancı Treebank explicitly represents the head-dependent relations and functional categories. In order to adapt the corpus written in 1990’s Turkish to further studies, a subset of 7.262 sentences of the corpus was manually annotated morphologically and syntactically
        [2]
        . METU-Sabancı Treebank is then used in many Turkish NLP studies
        [11, 23, 19, 20, 9, 10]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        METU-Sabancı Treebank is also subject to transformation efforts from dependency-structure to constituency-structure. Combinatory Categorical Grammar (CCG) is extracted from the METU-Sabancı Treebank with annotation of lexical categories
        [3]
        . Sub-lexical units revealing the internal structure of the words are used to generate a Lexical Grammar Formalism (LGF) for Turkish with the help of finite state machines
        [4, 5]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Swedish-Turkish parallel treebank is the first parallel Treebank effort for Turkish
        [16]
        . The treebank is a balanced syntactically annotated corpus containing both fiction and technical documents. In total, it consists of approximately 160,000 tokens in Swedish and 145,000 in Turkish. Parallel texts are linguistically annotated using different layers from part of speech tags and morphological features to dependency annotation.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        English-Swedish-Turkish parallel treebank
        [15]
        , mainly the successor of the Swedish-Turkish parallel treebank, consists of approximately 300,000 tokens in Swedish, 160,000 in Turkish and 150,000 in English. The majority of the original text is written in Swedish and translated to Turkish and/or English. For the syntactic description, dependency structure is chosen instead of the constituent structure. All data is automatically annotated with syntactic tags using MaltParser
        [17]
        . MaltParser is trained on the Penn Treebank for English, on the Swedish treebank Talbanken05
        [18]
        , and on the METU-Sabancı Turkish Treebank
        [2]
        , respectively.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        ParGram parallel treebank
        [21]
        is a joint effort for the construction of a parallel treebank involving ten languages (English, Georgian, German, Hungarian, Indonesian, Norwegian, Polish, Turkish, Urdu, Wolof) from six language families. The treebank is based on deep Lexical-Functional Grammars that were developed within the framework of the Parallel Grammar effort. ParGram treebank allows for the alignment of sentences at several levels: dependency structures, constituency structures and POS information.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Turkish syntax
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Turkish is an agglutinative language with rich derivational and inflectional morphology through suffixes. Word forms usually have a complex yet fairly regular morphotactics.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Turkish sentences have an unmarked SOV order. However, depending on the discourse, constituents can be scrambled to emphasize, topicalize and focus certain elements. Case markings identify the syntactic functions of the constituents,
        [14]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Corpus construction strategy
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In order to constrain the syntactic complexity of the sentences in the corpus,
we selected from the Penn Treebank II 9560 trees which contain a maximum of 15 tokens. These include 8660 trees from the training set of the Penn Treebank, 360 trees from its development set and 540 trees from its test set. In the first phase of our work, we translated 4247 trees of the training set and all of those in the development and the test sets.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Tools
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         Manual annotation is an error prone task. From simple typos to disagreements among annotators, the range of errors is fairly large. An annotation tool needs to help reduce these errors and help the annotator locate them when they occur. Moreover, the tool needs to present the annotator with a visual tree that is both easy to understand and manipulate for the translation task.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         We built a range of custom tools to display, manipulate and save annotated trees in the treebank. The underlying data structure is still textual and uses the standard Treebank II style of syntactic bracketing.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         We also implemented a simple statistical helper function within the tool. When translating an English word to a gloss in Turkish, the translator may choose from a list of glosses sorted according their likelihood calculated over their previous uses in similar cases. Thus, as the corpus grows in size, the translators use the leverage of their previous choices.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         Figure
         1
         shows a screenshot of our tree translation tool.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Tree permutation
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         In translating an English syntactic tree, we confine ourselves to two operations. We can permute the children of a node and we can replace the English word token at a leaf node. No other modification of the tree is allowed. In particular, we use the same set of tags and predicate labels in the non-leaf nodes and do not use new tags for the Turkish trees. Adding or deleting nodes are not allowed either.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         This might seem like a rather restrictive view of translation. Indeed, it is very easy to construct pairs of translated sentences which involve operations outside our restricted set when transformed into each other.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         However, we use the following method to alleviate the restrictions of the small set of operations.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         We use the *NONE* tag when we can not use any direct gloss for an English token. In itself, this operation corresponds to effectively mapping an English token to a null token. However, when we use the *NONE* tag, permute the nodes and choose the full inflected forms of the glosses in the Turkish tree, we have a powerful method to convert subtrees to an inflected word. The tree in Figure
         2
         . illustrates this. Note that the POS tag sequence VP-RB-MD-PRP in the Turkish sentence corresponds to the morphological analysis “geç-NEG-FUT-2SG” of the verb “geçmeyeceksin”. In general, we try to permute the nodes so as to correspond to the order of inflectional morphemes in the chosen gloss.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Transformation heuristics
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        When we have a sufficiently rich corpus of parallel trees, our next step is to train a SMT learner to imitate the human translator who operates under our restricted set of operations. Naturally, human translators often base their transformation decisions on the whole tree. Still, having a common set of rules and heuristics helps the translators in both consistency and speed. In the following, we illustrate these heuristics.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Constituent and morpheme order
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         Majority of unmarked Turkish sentences have the SOV order. When translating English trees, we permute its shallow subtrees to reflect the change of constituent order in Turkish.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Also, the agglutinative suffixes of Turkish words dictate the order when permuting the constituents which correspond to prepositions and particles.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         The semantic aspects expressed by prepositions, modals, particles and verb tenses in English in general correspond to specific morphemes attached to the corresponding word stem. For example, “Ali/NNP will/MD sit/VB on/IN a/DT chair/NN” is literally translated as
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Ali bir sandalye-ye otur-acak.
         Ali a chair-DAT sit-FUT.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p5">
        <p class="ltx_p">
         If we embed a constituent in the morphemes of a Turkish stem, we replace the English constituent leaf with *NONE*.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p6">
        <p class="ltx_p">
         In some cases, the personal pronouns acting as subjects are naturally embedded in the verb inflection. In those cases, pronoun in the original tree is replaced with *NONE* and its subtree is moved to after the verb phrase. See Figure
         3
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        The determiner “the”
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         There is no definite article in Turkish corresponding to “the”. Depending on the context, “the” is translated either as *NONE* or one of the demonstrative adjectives in Turkish, corresponding to “this” and “that” in English. See Figure
         3
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Case markers
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         Turkish, being a fairly scrambling language, uses case markers to denote the syntactic functions of nouns and noun groups. For example, accusative case may be used to mark the direct object of a transitive verb and locative case may be used to mark the head of a prepositional phrase. In translation from English to Turkish, the prepositions are usually replaced with *NONE* and their corresponding case is attached to the nominal head of the phrase. See Figure
         4
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Plural in nouns and verb inflection
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         Number agreement between the verb in the predicate and the subject is somewhat loose in Turkish. We preserved this freedom in translation and chose the number inflection that sounds more natural. Also, plural nouns under NNS tag in the English tree are sometimes translated as singular. In those cases, we kept the original POS tag NNS intact but used the singular gloss. See Figure
         5
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.5
        </span>
        Tense ambiguity
       </h3>
       <div class="ltx_para" id="S5.SS5.p1">
        <p class="ltx_p">
         It is in general not possible to find an exact mapping among the tense classes in a pair of languages. When translating the trees, we mapped the English verb tenses to their closest semantic classes in Turkish while trying to keep the overall flow of the Turkish sentence natural. In many cases, we mapped the perfective tense in English to the past tense in Turkish. Similarly, we sometimes mapped the present tense to present continuous. See Figure
         5
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS6">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.6
        </span>
        WH- Questions
       </h3>
       <div class="ltx_para" id="S5.SS6.p1">
        <p class="ltx_p">
         Question sentences require special attention during transformation. As opposed to movement in English question sentences, any constituent in Turkish can be questioned by replacing it with an inflected question word. In the Penn Treebank II annotation, the movement leaves a trace and is associated with wh- constituent with a numeric marker. For example, “WHNP-17” and “*T*-17” are associated.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS6.p2">
        <p class="ltx_p">
         When we translate the tree for a question sentence, we replace the wh- constituent with *NONE* and replace its trace with the appropriate question pronoun in Turkish. See Figure
         6
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS7">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.7
        </span>
        Miscellany
       </h3>
       <div class="ltx_para" id="S5.SS7.p1">
        <p class="ltx_p">
         In the translation of nominal clauses, the copula marker “-dIr” corresponding to verb “be” is often dropped.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS7.p2">
        <p class="ltx_p">
         The proper nouns are translated with their common Turkish gloss if there is one. So, “London” becomes “Londra”.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS7.p3">
        <p class="ltx_p">
         Subordinating conjunctions, marked as “IN” in English sentences, are transformed to *NONE* and the appropriate participle morpheme is appended to the stem in the Turkish translation.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS7.p4">
        <p class="ltx_p">
         A multiword expression may correspond to a single English word. Conversely, more than one words in English may correspond to a single word in Turkish. In the first case, we use the multiword expression as the gloss. In the latter case, we replace some English words with *NONE*.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
