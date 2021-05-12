<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Dependency-based Pre-ordering for Chinese-English Machine Translation.
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
       In statistical machine translation (SMT), syntax-based pre-ordering of the source language is an effective method for dealing with language pairs where there are great differences in their respective word orders. This paper introduces a novel pre-ordering approach based on dependency parsing for Chinese-English SMT. We present a set of dependency-based pre-ordering rules which improved the BLEU score by 1.61 on the NIST 2006 evaluation data. We also investigate the accuracy of the rule set by conducting human evaluations.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       UTF8gbsn
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
        SMT systems have difficulties translating between distant language pairs such as Chinese and English. The reason for this is that there are great differences in their word orders. Reordering therefore becomes a key issue in SMT systems between distant language pairs.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Previous work has shown that the approaches tackling the problem by introducing a pre-ordering procedure into phrase-based SMT (PBSMT) were effective. These pre-ordering approaches first parse the source language sentences to create parse trees. Then, syntactic reordering rules are applied to these parse trees with the goal of reordering the source language sentences into the word order of the target language. Syntax-based pre-ordering by employing constituent parsing have demonstrated effectiveness in many language pairs, such as English-French
        [2004]
        , German-English
        [2005]
        , Chinese-English
        [2007, 2008]
        , and English-Japanese
        [2010]
        . As a kind of constituent structure, HPSG
        [1994]
        parsing-based pre-ordering showed improvements in SVO-SOV translations, such as English-Japanese
        [2010, 2011]
        and Chinese-Japanese
        [2012]
        . Since dependency parsing is more concise than constituent parsing in describing sentences, some research has used dependency parsing in pre-ordering approaches for language pairs such as Arabic-English
        [2007]
        , and English-SOV languages
        [2009, 2011]
        . The pre-ordering rules can be made manually
        [2005, 2007, 2012]
        or extracted automatically from a parallel corpus
        [2004, 2007, 2007, 2011]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        The purpose of this paper is to introduce a novel dependency-based pre-ordering approach through creating a pre-ordering rule set and applying it to the Chinese-English PBSMT system. Experiment results showed that our pre-ordering rule set improved the BLEU score on the NIST 2006 evaluation data by 1.61. Moreover, this rule set substantially decreased the total times of rule application about 60%, compared with a constituent-based approach (Wang et al., 2007). We also conducted human evaluations in order to assess its accuracy. To our knowledge, our manually created pre-ordering rule set is the first Chinese-English dependency-based pre-ordering rule set.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The most similar work to this paper is that of Wang et al. (2007). They created a set of pre-ordering rules for constituent parsers for Chinese-English PBSMT. In contrast, we propose a set of pre-ordering rules for dependency parsers. We argue that even though the rules by Wang et al. (2007) exist, it is almost impossible to automatically convert their rules into rules that are applicable to dependency parsers. In fact, we abandoned our initial attempts to automatically convert
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        their rules into rules for dependency parsers, and spent more than two months discovering the rules introduced in this paper. By applying our rules and Wang et al.’s rules, one can use both dependency and constituency parsers for pre-ordering in Chinese-English PBSMT.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        This is especially important on the point of the system combination of PBSMT systems, because the diversity of outputs from machine translation systems is important for system combination
        [2013]
        . By using both our rules and Wang et al.’s rules, one can obtain diverse machine translation results because the pre-ordering results of these two rule sets are generally different.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Another similar work is that of
        [2009]
        . They created a pre-ordering rule set for dependency parsers from English to several SOV languages. In contrast, our rule set is for Chinese-English PBSMT. That is, the direction of translation is opposite. Because there are a lot of language specific decisions that reflect specific aspects of the source language and the language pair combination, our rule set provides a valuable resource for pre-ordering in Chinese-English PBSMT.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Dependency-based Pre-ordering Rule Set
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Figure 1 shows a constituent parse tree and its
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Stanford typed dependency parse tree for the same Chinese sentence. As shown in the figure, the number of nodes in the dependency parse tree (i.e. 9) is much fewer than that in its corresponding constituent parse tree (i.e. 17). Because dependency parse trees are generally more concise than the constituent ones, they can conduct long-distance reorderings in a finer way. Thus, we attempted to conduct pre-ordering based on dependency parsing. There are two widely-used dependency systems – Stanford typed dependencies and CoNLL typed dependencies. For Chinese, there are 45 types of grammatical relations for Stanford typed dependencies
        [2009]
        and 25 for CoNLL typed dependencies. As we thought that Stanford typed dependencies could describe language phenomena more meticulously owing to more types of grammatical relations, we preferred to use it for searching candidate pre-ordering rules.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        We designed two types of formats in our dependency-based pre-ordering rules. They are:
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.ix1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
         </span>
         <div class="ltx_para" id="I1.ix1.p1">
          <p class="ltx_p">
           Type-1:
           x
           :
           y
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
         </span>
         <div class="ltx_para" id="I1.ix2.p1">
          <p class="ltx_p">
           Type-2:
           x
           -
           y
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Here, both
        x
        and
        y
        are
        dependency relations
        (e.g., plmod or lobj in Figure 2). We define the
        dependency structure
        of a dependency relation as the structure containing the dependent word (e.g., the word directly indicated by plmod, or “å” in Figure 2) and the whole subtree under the dependency relation (all of the words that directly or indirectly depend on the dependent word, or the words under “å” in Figure 2). Further, we define
        X
        and
        Y
        as the corresponding dependency structures of the dependency relations
        x
        and
        y
        , respectively. We define
        X\Y
        as structure
        X
        except
        Y
        . For example, in Figure 2, let
        x
        and
        y
        denote plmod and lobj dependency relations, then
        X
        represents “å” and all words under “å”,
        Y
        represents “å¤§ä½¿é¦” and all words under
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        “å¤§ä½¿é¦”, and
        X\Y
        represents “å”. For Type-1,
        Y
        is a sub-structure of
        X
        . The rule repositions
        X\Y
        to the position before
        Y
        . For Type-2,
        X
        and
        Y
        are ordered sibling structures under a same parent node. The rule repositions
        X
        to the position after
        Y
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        We obtained rules as the following steps:
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.ix1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          1
         </span>
         <div class="ltx_para" id="I2.ix1.p1">
          <p class="ltx_p">
           Search the Chinese dependency parse trees in the corpus and rank all of the structures matching the two types of rules respectively according to their frequencies. Note that while calculating the frequencies of Type-1 structures, we dismissed the structures in which
           X
           occurred before
           Y
           originally.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.ix2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          2
         </span>
         <div class="ltx_para" id="I2.ix2.p1">
          <p class="ltx_p">
           Filtration. 1) Filter out the structures which occurred less than 5,000 times. 2) Filter out the structures from which it was almost impossible to derive candidate pre-ordering rules because
           x
           or
           y
           was an “irrespective” dependency relation, for example, root, conj, cc and so on.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.ix3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          3
         </span>
         <div class="ltx_para" id="I2.ix3.p1">
          <p class="ltx_p">
           Investigate the remaining structures. For each kind of structure, we selected some of the sample dependency parse trees that contained it, tried to restructure the parse trees according to the matched rule and judged the reordered Chinese phrases. If the reordering produced a Chinese phrase that had a closer word order to that of the English one, this structure would be a candidate pre-ordering rule.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.ix4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          4
         </span>
         <div class="ltx_para" id="I2.ix4.p1">
          <p class="ltx_p">
           Conduct primary experiments which used the same training set and development set as the experiments described in Section 3. In the primary experiments, we tested the effectiveness of the candidate rules and filtered the ones that did not work based on the BLEU scores on the development set.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p9">
       <p class="ltx_p">
        As a result, we obtained eight pre-ordering rules in total, which can be divided into three dependency relation categories. They are: plmod (localizer modifier of a preposition), rcmod (relative clause modifier) and prep (preposition modifer). Each of these categories are discussed in detail below.
       </p>
      </div>
      <div class="ltx_para" id="S2.p10">
       <p class="ltx_p">
        plmod
        Figure 2 shows an example of a prepositional phrase with a plmod structure, which translates literally into “in the US embassy front”. In Chinese, the dependent word of a plmod relation (e.g., “å” in Figure 2) occurs in the last position of the prepositional phrase. However, in English, this kind of word (e.g., “front” in the caption of Figure 2) always occur directly after prepositions, which is to say, in the second position in a prepositional phrase. Therefore, we applied a rule
        plmod
        :
        lobj
        (localizer object) to reposition the dependent word of the plmod relation (e.g., “å” in Figure 2) to the position before the lobj structure (e.g., “ç¾å½ å¤§ä½¿é¦” in Figure 2). In this case, it also comes directly after the preposition. Similarly, we created a rule
        plmod
        :
        lccomp
        (clausal complement of a localizer).
       </p>
      </div>
      <div class="ltx_para" id="S2.p11">
       <p class="ltx_p">
        rcmod
        Figure 3 shows an example of an rcmod structure under an nsubj (nominal subject) structure. Here “mw” means “measure word”. As shown in the figure, relative clause modifiers in Chinese (e.g., “æ¥è¿ å¤é ç” in Figure 3) occurs before the noun being modified, which is in contrast to English (e.g., “close to Sharon” in the caption of Figure 3), where they come after. Thus, we introduced a series of rules
        NOUN
        :
        rcmod
        to restructure rcmod structures so that the noun is moved to the head. In this example, with the application of an
        nsubj
        :
        rcmod
        rule, the phrase can be translated into “a senior official close to Sharon say”, which has a word order very close to English. Since a noun can be nsubj, dobj (direct object), pobj (prepositional object)
       </p>
      </div>
      <div class="ltx_para" id="S2.p12">
       <p class="ltx_p">
        and lobj in Stanford typed dependencies, we created four rules from the NOUN pattern. Note that for some preposition modifiers, we needed a rule
        rcmod
        :
        prep
        to conduct the same work. For instance, the Chinese phrase in Figure 4 can be translated into “hold in Kabul press conference” with the application of this rule.
       </p>
      </div>
      <div class="ltx_para" id="S2.p13">
       <p class="ltx_p">
        prep
        Within verb phrases, the positions of prep structures are quite different between Chinese and English. Figure 5 shows an example of a verb phrase with a preposition modifier (prep), which literally translates into “Musharraf at this place tell reporter”. Recognizing that prep structures occur before the verb in Chinese (e.g., “å¨ æ­¤ å°” in Figure 5) but after the verb in English (usually in the last position of a verb phrase, e.g., “here” in the caption of Figure 5), we applied a rule
        prep
        -
        dobj
        to reposition prep structures after their sibling dobj structures.
       </p>
      </div>
      <div class="ltx_para" id="S2.p14">
       <p class="ltx_p">
        In summary, the dependency-based pre-ordering rule set has eight rules: plmod : lobj, plmod : lccomp, nsubj : rcmod, dobj : rcmod, pobj : rcmod, lobj : rcmod, rcmod : prep, and prep - dobj.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We used the MOSES PBSMT system
        [2007]
        in our experiments. The training data, which included those data used in Wang et al.
        [2007]
        , contained 1 million pairs of sentences extracted from the Linguistic Data Consortium’s parallel news corpora. Our development set was the official NIST MT evaluation data from 2002 to 2005, consisting of 4476 Chinese-English sentences pairs. Our test set was the NIST 2006 MT evaluation data, consisting of 1664 sentence pairs. We employed the Stanford Segmenter
        to segment all of the data sets. For evaluation, we used BLEU scores
        [2002]
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We implemented the constituent-based pre-ordering rule set in Wang et al.
        [2007]
        for comparison, which is called WR07 below. The Berkeley Parser
        [2006]
        was employed for parsing the Chinese sentences. For training the Berkeley Parser, we used Chinese Treebank (CTB) 7.0.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        We conducted our dependency-based pre-ordering experiments on the Berkeley Parser and the Mate Parser
        [2010]
        , which were shown to be the two best parsers for Stanford typed dependencies
        [2012]
        . First, we converted the constituent parse trees in the results of the Berkeley Parser into dependency parse trees by employing a tool in the Stanford Parser
        [2003]
        . For the Mate Parser, POS tagged inputs are required both in training and in inference. Thus, we then extracted the POS information from the results of the Berkeley Parser and used these as the pre-specified POS tags for the Mate Parser. Finally, we applied our dependency-based pre-ordering rule set to the dependency parse trees created from the converted Berkeley Parser and the Mate Parser, respectively.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Table 1 presents a comparison of the system without pre-ordering, the constituent system using WR07 and two dependency systems employing the converted Berkeley Parser and the Mate Parser, respectively. It shows the BLEU scores on the test set and the statistics of pre-ordering on the training set, which includes the total count of each rule set and the number of sentences they were applied to. Both of our dependency systems outperformed WR07 slightly but were not significant at p = 0.05. However, both of them substantially decreased the total times about 60% (or 1,600,000) for pre-ordering rule applications on the training set, compared with WR07. In our opinion, the reason for the great decrease was that the dependency parse trees were more concise than the constituent parse trees in describing sentences and they could also describe the reordering at the sentence level in a finer way. In contrast, the constituent parse trees were more redundant and they needed more nodes to conduct long-distance reordering. In this case, the affect of the performance of the constituent parsers on pre-ordering is larger than that of the dependency ones so that the constituent parsers are likely to bring about more incorrect pre-orderings.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Similar to Wang et al.
        [2007]
        , we carried out human evaluations to assess the accuracy of our dependency-based pre-ordering rules by employing the system “OUR DEP 2” in Table 1. The evaluation set contained 200 sentences randomly selected from the development set. Among them, 107 sentences contained at least one rule and the rules were applied 185 times totally. Since the accuracy check for dependency parse trees took great deal of time, we did not try to select error free (100% accurately parsed) sentences. A bilingual speaker of Chinese and English looked at an original Chinese phrase and the pre-ordered one with their corresponding English phrase and judged whether the pre-ordering obtained a Chinese phrase that had a closer word order to the English one. Table 2 shows the accuracies of three categories of our dependency-based pre-ordering rules. The overall accuracy of this rule set is 60.0%, which is almost at the same level as the WR07 rule set (62.1%), according to the similar evaluation (200 sentences and one annotator) conducted in Wang et al.
        [2007]
        . Notice that some of the incorrect pre-orderings may be caused by erroneous parsing as also suggested by Wang et al.
        [2007]
        . Through human evaluations, we found that 19 out of the total 74 incorrect pre-orderings resulted from errors in parsing. Among them, 13 incorrect pre-orderings applied the rules of the rcmod category. The analysis suggests that we need to introduce constraints on the rule application of this category in the future.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
