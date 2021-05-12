<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Learning Word Sense Distributions, Detecting Unattested Senses
and Identifying Novel Senses Using Topic Models.
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
       Unsupervised word sense disambiguation (
       wsd
       ) methods are an
attractive approach to all-words
       wsd
       due to their non-reliance on
expensive annotated data. Unsupervised estimates of sense frequency
have been shown to be very useful for
       wsd
       due to the skewed nature of
word sense distributions. This paper presents a fully unsupervised
topic modelling-based approach to sense frequency estimation, which is
highly portable to different corpora and sense inventories, in being
applicable to any part of speech, and not requiring a hierarchical
sense inventory, parsing or parallel text. We demonstrate the
effectiveness of the method over the tasks of predominant sense
learning and sense distribution acquisition, and also the novel tasks
of detecting senses which aren’t attested in the corpus, and
identifying novel senses in the corpus which aren’t captured in the
sense inventory.
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
        The automatic determination of word sense information has been a
long-term pursuit of the NLP community
        []
        . Word sense distributions tend
to be Zipfian, and as such, a simple but surprisingly high-accuracy
back-off heuristic for word sense disambiguation (
        wsd
        ) is to tag each
instance of a given word with its predominant sense
        []
        . Such an approach requires knowledge of
predominant senses; however, word sense distributions — and
predominant senses too — vary from corpus to corpus. Therefore,
methods for automatically learning predominant senses and sense
distributions for specific corpora are required
        [12]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        In this paper, we propose a method which uses topic models to estimate
word sense distributions. This method is in principle applicable to all
parts of speech, and moreover does not require a parser, a hierarchical
sense representation or parallel text. Topic models have been used for
        wsd
        in a number of
studies
        [1, 13, 19, 3, 11]
        ,
but our work extends significantly on this earlier work in focusing on
the acquisition of prior word sense distributions (and predominant
senses).
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Because of domain differences and the skewed nature of word sense
distributions, it is often the case that some senses in a sense
inventory will not be attested in a given corpus. A system capable of
automatically finding such senses could reduce ambiguity, particularly
in domain adaptation settings, while retaining rare but nevertheless
viable senses. We further propose a method for applying our sense
distribution acquisition system to the task of finding unattested senses
— i.e., senses that are in the sense inventory but not attested in a
given corpus. In contrast to the previous work of
        McCarthy et al. (2004)
        on this topic which uses the sense ranking score from
        to remove low-frequency senses from
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        ,
we focus on finding senses that are unattested in the corpus on the
premise that, given accurate disambiguation, rare senses in a corpus
contribute to correct interpretation.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Corpus instances of a word can also correspond to senses that are not
present in a given sense inventory. This can be due to, for example,
words taking on new meanings over time (e.g. the relatively recent
senses of
        tablet
        and
        swipe
        related to touchscreen
computers) or domain-specific terms not being included in a more
general-purpose sense inventory. A system for automatically identifying
such novel senses — i.e. senses that are attested in the corpus but
not in the sense inventory — would be a very valuable lexicographical
tool for keeping sense inventories up-to-date
        []
        . We
further propose an application of our proposed method to the
identification of such novel senses. In contrast to
        , the use of topic models makes this possible,
using topics as a proxy for
sense
        []
        . Earlier
work on identifying novel senses focused on individual tokens
        [7]
        , whereas our approach goes further in identifying groups
of tokens exhibiting the same novel sense.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Background and Related Work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        There has been a considerable amount of research on representing word
senses and disambiguating usages of words in context (
        wsd
        ) as, in order
to produce computational systems that understand and produce natural
language, it is essential to have a means of representing and
disambiguating word sense.
        wsd
        algorithms require word sense
information to disambiguate token instances of a given ambiguous word,
e.g. in the form of sense definitions
        []
        , semantic
relationships
        [17]
        or annotated
data
        [20]
        . One extremely useful piece of
information is the word sense prior or expected word sense frequency
distribution. This is important because word sense distributions are
typically skewed
        []
        , and systems do far better when
they take bias into account
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Typically, word frequency distributions are estimated with respect to a
sense-tagged corpus such as SemCor
        [15]
        , a 220,000 word
corpus tagged with
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        []
        senses. Due to the
expense of hand tagging, and sense distributions being sensitive to
domain and genre, there has been some work on trying to estimate sense
frequency information
automatically
        [5, 16, 6]
        .
Much of this work has been focused on ranking word senses to find the
predominant sense in a given corpus
        [16]
        ,
which is a very powerful heuristic approach to
        wsd
        . Most
        wsd
        systems rely upon this heuristic for back-off in the absence of strong
contextual evidence
        []
        .
        proposed a method which relies on distributionally similar words
(nearest neighbours) associated with the target word in an automatically
acquired thesaurus
        []
        . The distributional similarity scores
of the nearest neighbours are associated with the respective target word
senses using a
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        similarity measure, such as those proposed
by
        and
        . The word
senses are ranked based on these similarity scores, and the most
frequent sense is selected for the corpus that the distributional
similarity thesaurus was trained over.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        As well as sense ranking for predominant sense acquisition, automatic
estimates of sense frequency distribution can be very useful for
        wsd
        for training data sampling purposes
        []
        , entropy
estimation
        []
        , and prior probability
estimates, all of which can be integrated within a
        wsd
        system
        [5, 6, 12]
        . Various approaches have
been adopted, such as normalizing sense ranking scores to obtain a
probability distribution
        []
        , using subcategorisation information as
an indication of verb sense
        [12]
        or alternatively using parallel
text
        [5, 6]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        The work of
        Boyd-Graber and Blei (2007)
        is highly
related in that it extends the method of
        to
provide a generative model which assumes the words in a given document
are generated according to the topic distribution appropriate for that
document. They then predict the most likely sense for each word in the
document based on the topic distribution and the words in context
(“corroborators”), each of which, in turn, depends on the document’s
topic distribution. Using this approach, they get comparable results to
McCarthy et al. when context is ignored (i.e. using a model with one
topic), and at most a 1% improvement on SemCor when they use more
topics in order to take context into account.  Since the results do not improve on
McCarthy et al. as regards sense distribution acquisition irrespective
of context, we will compare our model with that proposed by McCarthy et
al.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Recent work on finding novel senses has tended to focus on comparing
diachronic corpora
        []
        and has
also considered topic models
        []
        . In a similar vein,
        Peirsman et al. (2010)
        considered the identification of words having
a sense particular to one language variety with respect to another
(specifically Belgian and Netherlandic Dutch). In contrast to these
studies, we propose a model for comparing a corpus with a sense
inventory.
        Carpuat et al. (2013)
        exploit parallel corpora to
identify words in domain-specific monolingual corpora with
previously-unseen translations; the method we propose does not require
parallel data.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Methodology
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Our methodology is based on the WSI system described in
        ,
        which has been shown
        []
        to achieve state-of-the-art
results over the WSI tasks from SemEval-2007
        []
        ,
SemEval-2010
        []
        and SemEval-2013
        []
        . The system is built
around a Hierarchical Dirichlet Process (HDP:
        ),
a non-parametric variant of a Latent Dirichlet Allocation topic model
        []
        where the model automatically optimises the number of
topics in a fully-unsupervised fashion over the training data.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        To learn the senses of a target lemma, we train a single topic model per
target lemma. The system reads in a collection of usages of that lemma,
and automatically induces topics (= senses) in the form of a multinomial
distribution over words, and per-usage topic assignments (=
probabilistic sense assignments) in the form of a multinomial
distribution over topics. Following
        , we assign one
topic to each usage by selecting the topic that has the highest
cumulative probability density, based on the topic allocations of all
words in the context window for that usage.
        Note that in their original work,
        experimented with the use of features extracted
from a dependency parser. Due to the computational overhead associated
with these features, and the fact that the empirical impact of the
features was found to be marginal, we make no use of parser-based
features in this paper.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The induced topics take the form of word multinomials, and are often
represented by the top-
        N
        words in descending order of conditional
probability. We interpret each topic as a sense of the target
lemma.
        To illustrate this, we give the example
of topics induced by the HDP model for
        network
        in
Table
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        We refer to this method as HDP-WSIhenceforth.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        In predominant sense acquisition, the task is to learn, for each target
lemma, the most frequently occurring word sense in a particular domain
or corpus, relative to a predefined sense inventory. The WSI system
provides us with a topic allocation per usage of a given word, from
which we can derive a distribution of topics over usages and a
        predominant topic
        . In order to map this onto the
        predominant sense
        , we need to have some way of aligning a
topic with a sense. We design our topic–sense alignment methodology
with portability in mind — it should be applicable to any sense
inventory. As such, our alignment methodology assumes only that we have
access to a conventional sense gloss or definition for each sense, and
does not rely on ontological/structural knowledge (e.g. the
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        hierarchy).
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        To compute the similarity between a sense and a topic, we first convert
the words in the gloss/definition into a multinomial distribution over
words, based on simple maximum likelihood estimation.
        We then calculate the Jensen–Shannon divergence between the multinomial
distribution (over words) of the gloss and that of the topic, and
convert the divergence value into a similarity score by subtracting it
from
        1
        . Formally, the similarity sense
        si
        and topic
        tj
        is:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          sim⁢(si,tj)
         </td>
         <td class="ltx_td ltx_align_left">
          =1-JS(S∥T)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (1)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        S
        and
        T
        are the multinomial distributions over words for
sense
        si
        and topic
        tj
        , respectively, and
        JS(X∥Y)
        is the
Jensen–Shannon divergence for distribution
        X
        and
        Y
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        To learn the predominant sense, we compute the
        prevalence
score
        of each sense and take the sense with the highest prevalence
score as the predominant sense. The prevalence score for a sense is
computed by summing the product of its similarity scores with each topic
(i.e.
        sim⁢(si,tj)
        ) and the prior probability of the topic in
question (based on maximum likelihood estimation). Formally, the
prevalence score of sense
        si
        is given as follows:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          prevalence⁢(si)
         </td>
         <td class="ltx_td ltx_align_left">
          =∑jT(sim⁢(si,tj)×P⁢(tj))
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (2)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
         </td>
         <td class="ltx_td ltx_align_left">
          =∑jT(sim⁢(si,tj)×f⁢(tj)∑kTf⁢(tk))
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        f⁢(tj)
        is the frequency of topic
        tj
        (i.e. the number of
usages assigned to topic
        tj
        ), and
        T
        is the number of topics.
       </p>
      </div>
      <div class="ltx_para" id="S3.p8">
       <p class="ltx_p">
        The intuition behind the approach is that the predominant sense should
be the sense that has relatively high similarity (in terms of lexical
overlap) with high-probability topic(s).
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       <span class="ltx_text ltx_font_sansserif">
        WordNet
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We first test the proposed method over the tasks of predominant sense
learning and
sense distribution induction, using the
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        -tagged dataset
of
        , which is made up of 3 collections of documents:
a domain-neutral corpus (
        BNC
        ), and two domain-specific corpora (
        SPORTS
        and
        FINANCE
        ). For each domain, annotators were asked to sense-annotate
a random selection of sentences for each of 40 target nouns, based on
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        v1.7. The predominant sense and distribution across senses for
each target lemma was obtained by aggregating over the sense
annotations. The authors evaluated their method in terms of
        wsd
        accuracy over a given corpus, based on assigning all instances of a
target word with the predominant sense learned from that corpus. For the
remainder of the paper, we denote their system as
MKWC.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        To compare our system (HDP-WSI) with MKWC, we apply it to the three
datasets of
        . For each dataset, we use HDP to
induce topics for each target lemma, compute the similarity between the
topics and the
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        senses (Equation (
        1
        )), and rank the senses
based on the prevalence scores (Equation (
        2
        )). In addition to
the
        wsd
        accuracy based on the predominant sense inferred from a
particular corpus, we additionally compute: (1)
        Accub
        , the upper
bound for the first sense-based
        wsd
        accuracy (using the gold standard
predominant sense for disambiguation);
        and (2)
        ERR
        , the error rate
reduction between the accuracy for a given system (
        Acc
        ) and the upper
bound (
        Accub
        ), calculated as follows:
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="S6.EGx3">
        <tr class="ltx_equation ltx_align_baseline" id="S4.Ex2">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          ERR=1-Accub-AccAccub
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Looking at the results in Table
        2
        , we see little
difference in the results for the two methods, with MKWCperforming
better over two of the datasets (
        BNC
        and
        SPORTS
        ) and HDP-WSIperforming better over the third (
        FINANCE
        ), but all differences are
small. Based on the McNemar’s Test with Yates correction for continuity,
MKWCis significantly better over
        BNC
        and HDP-WSIis significantly
better over
        FINANCE
        (
        p&lt;0.0001
        in both cases), but the difference
over
        SPORTS
        is not statistically significance (
        p&gt;0.1
        ). Note that
there is still much room for improvement with both systems, as we see in
the gap between the upper bound (based on perfect determination of the
first sense) and the respective system accuracies.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Given that both systems compute a continuous-valued prevalence score for
each sense of a target lemma, a distribution of senses can be obtained
by normalising the prevalence scores across all senses. The predominant
sense learning task of
        evaluates the ability of
a method to identify only the head of this distribution, but it is also
important to evaluate the full sense distribution
        []
        . To
this end, we introduce a second evaluation metric: the Jensen–Shannon
(JS) divergence between the inferred sense distribution and the
gold-standard sense distribution, noting that smaller values are better
in this case, and that it is now theoretically possible to obtain a JS
divergence of 0 in the case of a perfect estimate of the sense
distribution. Results are presented in Table
        3
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        HDP-WSIconsistently achieves lower JS divergence, indicating that the
distribution of senses that it finds is closer to the gold standard
distribution. Testing for statistical significance over the paired JS divergence values for
each lemma using the Wilcoxon signed-rank test, the result for
        FINANCE
        is significant (
        p&lt;0.05
        ) but the
results for the other two datasets are not (
        p&gt;0.1
        in each
case).
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        To summarise, the results for MKWCand HDP-WSIare fairly even for
predominant sense learning (each outperforms the other at a level of
statistical significance over one dataset), but HDP-WSIis better at
inducing the overall sense distribution.
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        It is important to bear in mind that MKWCin these experiments
makes use of full-text parsing in calculating the distributional
similarity thesaurus, and the
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        graph structure in calculating
the similarity between associated words and different senses. Our
method, on the other hand, uses no parsing, and only the synset
definitions (and not the graph structure) of
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        .
        The non-reliance on parsing is significant in terms of
portability to text sources which are less amenable to parsing (such as
Twitter:
        []
        ), and the non-reliance on the graph
structure of
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        is significant in terms of portability to
conventional “flat” sense inventories. While comparable results on a
different dataset have been achieved with a proximity thesaurus
        []
        compared to a dependency one,
        it is not
stated how wide a window is needed for the proximity thesaurus. This
could be a significant issue with Twitter data, where context tends to
be limited. In the next section, we demonstrate the robustness of the
method in experimenting with two new datasets, based on Twitter and a
web corpus, and the
        <span class="ltx_text ltx_font_sansserif">
         Macmillan English Dictionary
        </span>
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       <span class="ltx_text ltx_font_sansserif">
        Macmillan
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In our second set of experiments, we move to a new dataset
        [9]
        based on text from ukWaC
        [8]
        and Twitter, and annotated using the
        <span class="ltx_text ltx_font_sansserif">
         Macmillan English
Dictionary
         <span class="ltx_note ltx_role_footnote">
          <sup class="ltx_note_mark">
           10
          </sup>
          <span class="ltx_note_outer">
           <span class="ltx_note_content">
            <sup class="ltx_note_mark">
             10
            </sup>
            <a class="ltx_ref ltx_url" href="http://www.macmillandictionary.com/" title="">
             <span class="ltx_text ltx_font_typewriter">
              http://www.macmillandictionary.com/
             </span>
            </a>
           </span>
          </span>
         </span>
        </span>
        (henceforth “
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        ”). For the purposes of this research, the
choice of
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        is significant in that it is a conventional
dictionary with sense definitions and examples, but no linking between
senses.
        In terms of the original research which
gave rise to the sense-tagged dataset,
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        was chosen over
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        for reasons including: (1) the well-documented difficulties of
sense tagging with fine-grained
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        senses
        []
        ; (2) the regular update cycle of
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        (meaning it contains many recently-emerged senses); and (3)
the finding in a preliminary sense-tagging task that it better captured
Twitter usages than
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        (and also
        <span class="ltx_text ltx_font_sansserif">
         OntoNotes
        </span>
        :
        ).
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        The dataset is made up of 20 target nouns which were selected to span
the high- to mid-frequency range in both Twitter and the ukWaC corpus,
and have at least 3
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        senses. The average sense ambiguity of
the 20 target nouns in
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        is 5.6 (but 12.3 in
        <span class="ltx_text ltx_font_sansserif">
         WordNet
        </span>
        ). 100
usages of each target noun were sampled from each of Twitter (from a
crawl over the time period Jan 3–Feb 28, 2013 using the Twitter
Streaming API) and ukWaC, after language identification using
        langid.py[]
        and POS tagging (based on the CMU ARK Twitter
POS tagger v2.0
        []
        for Twitter, and the POS tags
provided with the corpus for ukWaC). Amazon Mechanical Turk (AMT) was
then used to 5-way sense-tag each usage relative to
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        ,
including allowing the annotators the option to label a usage as
“Other” in instances where the usage was not captured by any of the
        <span class="ltx_text ltx_font_sansserif">
         Macmillan
        </span>
        senses. After quality control over the annotators/annotations
(see
        Gella et al. (to appear)
        for details), and aggregation of the
annotations into a single sense per usage (possibly “Other”), there
were 2000 sense-tagged ukWaC sentences and Twitter messages over the 20
target nouns. We refer to these two datasets as
        ukWaC
        and
        Twitter
        henceforth.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        To apply our method to the two datasets, we use HDP-WSIto train a model
for each target noun, based on the combined set of usages of that lemma
in each of the two background corpora, namely the original Twitter crawl
that gave rise to the
        Twitter
        dataset, and all of ukWaC.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Learning Sense Distributions
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         As in Section
         4
         , we evaluate in terms of
         wsd
         accuracy
(Table
         4
         ) and JS divergence over the
gold-standard sense distribution (Table
         5
         ). We also
present the results for: (a) a supervised baseline
(“FS
         corpus
         ”), based on the most frequent sense in the
corpus; and (b) an unsupervised baseline (“FS
         dict
         ”), based on the
first-listed sense in
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         . In each case, the sense distribution
is based on allocating all probability mass for a given word to the
single sense identified by the respective method.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         We first notice that, despite the coarser-grained senses of
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         as compared to
         <span class="ltx_text ltx_font_sansserif">
          WordNet
         </span>
         , the upper bound
         wsd
         accuracy using
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         is comparable to that of the
         <span class="ltx_text ltx_font_sansserif">
          WordNet
         </span>
         -based datasets over
the balanced BNC, and quite a bit lower than that of the two domain
corpora of
         . This suggests that both datasets
are diverse in domain and content.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         In terms of
         wsd
         accuracy, the results over
         ukWaC
         (
         ERR
         = 0.895) are
substantially higher than those for
         BNC
         , while those over
         Twitter
         (
         ERR
         = 0.716) are comparable. The accuracy is significantly higher than
the dictionary-based first sense baseline (FS
         dict
         ) over both
datasets (McNemar’s test;
         p&lt;0.0001
         ), and the
         ERR
         is also
considerably higher than for the two domain datasets in Section
         4
         (
         FINANCE
         and
         SPORTS
         ). One cause of difficulty in sense-modelling
         Twitter
         is large numbers of missing senses, with 12.3% of usages in
         Twitter
         and 6.6% in
         ukWaC
         having no corresponding
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         sense.
         This
challenges the assumption built into the sense prevalence calculation
that all topics will align to a pre-existing sense, a point we return
to in Section
         5.2
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         The JS divergence results for both datasets are well below (= better
than) the results for all three
         <span class="ltx_text ltx_font_sansserif">
          WordNet
         </span>
         -based datasets, and also
superior to both the supervised and unsupervised first-sense
baselines. Part of the reason for this improvement is simply that the
average polysemy in
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         (5.6 senses per target lemma) is slightly
less than in
         <span class="ltx_text ltx_font_sansserif">
          WordNet
         </span>
         (6.7 senses per target lemma),
         making the task slightly easier in the
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         case.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Identification of Unattested Senses
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We observed in Section
         5.1
         that there are relatively
frequent occurrences of usages (e.g. 12.3% for
         Twitter
         ) which aren’t
captured by
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         . Conversely, there are also senses in
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         which aren’t attested in the annotated sample of usages. Specifically,
of the 112 senses defined for the 20 target lemmas, 25 (= 22.3%) of the senses
are not attested in the 2000 usages in either corpora. Given that our
methodology computes a prevalence score for each sense, it can equally
be applied to the detection of these unattested senses, and it is this
task that we address in this section: the identification of senses that
are defined in the sense inventory but not attested in a given corpus.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Intuitively, an unused sense should have low similarity with the HDP
induced topics. As such, we introduce sense-to-topic affinity, a measure
that estimates how likely a sense is not attested in the
corpus:
        </p>
        st-affinity⁢(si)=∑jTsim⁢(si,tj)∑kS∑lTsim⁢(sk,tl)

(3)
        <p class="ltx_p">
         where
         sim⁢(si,tj)
         is carried over from Equation (
         1
         ), and
         T
         and
         S
         represent the number of topics and senses, respectively.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         We treat the task of identification of unused senses as a binary
classification problem, where the goal is to find a sense-to-topic
affinity threshold below which a sense will be considered to be
unused. We pool together all the senses and run 10-fold cross validation
to learn the threshold for identifying unused senses,
         evaluated using
sense-level precision (
         P
         ), recall (
         R
         ) and F-score
(
         F
         ) at detecting unattested senses. We repeat the experiment 10
times (partitioning the items randomly into folds) and collect the mean
precision, recall and F-scores across the 10 runs. We found encouraging
results for the task, as detailed in Table
         6
         . For the
threshold, the average value with standard deviation is
         0.092±0.044
         over
         ukWaC
         and
         0.125±0.052
         over
         Twitter
         , indicating relative
stability in the value of the threshold both internally within a
dataset, and also across datasets.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Identification of Novel Senses
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         In both
         Twitter
         and
         ukWaC
         , we observed frequent occurrences of usages
of our target nouns which didn’t map onto a pre-existing
         <span class="ltx_text ltx_font_sansserif">
          Macmillan
         </span>
         sense. A natural question to ask is whether our method can be used to
predict word senses that are missing from our sense inventory, and
identify usages associated with each such missing sense. We will term
these “novel senses”, and define “novel sense identification” to be
the task of identifying new senses that are not recorded in the
inventory but are seen in the corpus.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         An immediate complication in evaluating novel sense identification is
that we are attempting to identify senses which explicitly aren’t in our
sense inventory. This contrasts with the identification of unattested
senses, e.g., where we were attempting to identify which of the
         known
         senses wasn’t observed in the corpus. Also, while we have
annotations of “Other” usages in
         Twitter
         and
         ukWaC
         , there is no real
expectation that all such usages will correspond to the same sense: in
practice, they are attributable to a myriad of effects such as
incorporation in a non-compositional multiword expression, and errors in
POS tagging (i.e. the usage not being nominal). As such, we can’t use
the “Other” annotations to evaluate novel sense identification. The
evaluation of systems for this task is a known challenge, which we
address similarly to
         Erk (2006)
         by artificially synthesising
novel senses through removal of senses from the sense inventory. In this way,
even if we remove multiple senses for a given word, we still have access
to information about which usages correspond to which novel sense. An
additional advantage of this procedure is that it allows us to control
an important property of novel senses: their frequency of occurrence.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         In the experiments that follow, we randomly select senses for removal
from three frequency bands: low, medium and high frequency senses.
Frequency is defined by relative occurrence in the annotated usages: low
= 0.0–0.2; medium = 0.2–0.4; and high = 0.4–0.6. Note that we do not
consider high-frequency senses with frequency higher than 0.6, as it is
rare for a medium- to high-frequency word to take on a novel sense which
is then the predominant sense in a given corpus. Note also that not all
target lemmas will have a novel sense through synthesis, as they may
have no senses that fall within the indicated bounds of relative
occurrence (e.g. if
         &gt;60⁢%
         of usages are a single sense). For
example, only 6 of our 20 target nouns have senses which are candidates
for high-frequency novel senses.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         As before, we treat the novel sense identification task as a
classification problem, although with a significantly different
formulation: we are no longer attempting to identify pre-existing
senses, as novel senses are by definition not included in the sense
inventory. Instead, we are seeking to identify clusters of usages which
are instances of a novel sense, e.g. for presentation to a
lexicographer as part of a dictionary update process
         []
         . That is, for each usage, we
want to classify whether it is an instance of a given novel sense.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         A usage that corresponds to a novel sense should have a topic that does
not align well with any of the pre-existing senses in the sense
inventory. Based on this intuition, we introduce topic-to-sense affinity
to estimate the similarity of a topic to the set of senses, as follows:
        </p>
        ts-affinity⁢(tj)=∑iSsim⁢(si,tj)∑lT∑kSsim⁢(sk,tl)

(4)
        <p class="ltx_p">
         where, once again,
         sim⁢(si,tj)
         is defined as in Equation (
         1
         ),
and
         T
         and
         S
         represent the number of topics and senses, respectively.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p6">
        <p class="ltx_p">
         Using topic-to-sense affinity as the sole feature, we pool together all
instances and optimise the affinity feature to classify instances that
have novel senses. Evaluation is done by computing the mean precision,
recall and F-score across 10 separate runs; results are summarised in
Table
         7
         . Note that we evaluate only over
         ukWaC
         in this section, for ease of presentation.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p7">
        <p class="ltx_p">
         The results show that instances with high-frequency novel senses are
more easily identifiable than instances with medium/low-frequency novel
senses. This is unsurprising given that high-frequency senses have a
higher probability of generating related topics (sense-related words are
observed more frequently in the corpus), and as such are more easily
identifiable.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p8">
        <p class="ltx_p">
         We are interested in understanding whether pooling all instances —
instances from target lemmas that have a sense artificially removed and
those that do not — impacted the results (recall that not all target
lemmas have a removed sense). To that end, we chose to include only
instances from lemmas with a removed sense, and repeated the experiment
for the medium- and high-frequency novel sense condition (for the
low-frequency condition, all target lemmas have a novel sense). In
other words, we are assuming knowledge of which words have novel sense,
and the task is to identify specifically what the novel sense is, as
represented by novel usages. Results are presented in
Table
         8
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p9">
        <p class="ltx_p">
         From the results, we see that the F-scores improved notably. This
reveals that an additional step is necessary to determine whether a
target lemma has a potential novel sense before feeding its instances to
learn which of them contains the usage of the novel sense.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p10">
        <p class="ltx_p">
         In the last experiment, we propose a new measure to tackle this: the
identification of target lemmas that have a novel sense. We introduce
         novelty
         , a measure of the likelihood of a target lemma
         w
         having a
novel sense:
        </p>
        novelty⁢(w)=mintj⁡(maxsi⁡sim⁢(si,tj)f⁢(tj))

(5)
        <p class="ltx_p">
         where
         f⁢(tj)
         is the frequency of topic
         tj
         in the corpus. The
intuition behind
         novelty
         is that a target lemma with a novel sense
should have a (somewhat-)frequent topic that has low association with
any sense. That we use the frequency rather than the probability of the
topic here is deliberate, as topics with a higher raw number of
occurrences (whether as a low-probability topic for a high-frequency word, or a
high-probability topic for a low-frequency word) are indicative of a
novel word sense.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p11">
        <p class="ltx_p">
         For each of our three datasets (with low-, medium- and high-frequency
novel senses, respectively), we compute the novelty of the target lemmas
and the
         p
         -value of a one-tailed Wilcoxon rank sum test to test if the
two groups of lemmas (i.e. lemmas with a novel sense vs. lemmas
without a novel sense) are statistically different.
         Results are
presented in Table
         9
         . We see that the novelty measure
can readily identify target lemmas with high- and medium-frequency novel
senses (
         p&lt;0.05
         ), but the results are less promising for the
low-frequency novel senses.
        </p>
       </div>
      </div>
     </div>
      <div class="ltx_subsection" id="S6.SSx1">
       <h3 class="ltx_title ltx_title_subsection">
        Acknowledgements
       </h3>
       <div class="ltx_para" id="S6.SSx1.p1">
        <p class="ltx_p">
         We wish to thank the anonymous reviewers for their valuable comments. This research was
supported in part by funding from the Australian Research Council.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
