<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Can You Repeat That? Using Word Repetition to Improve Spoken Term Detection.
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
       We aim to improve
       spoken term detection
       performance by incorporating contextual information beyond traditional N-gram language models. Instead of taking a broad view of topic context in spoken documents, variability of word co-occurrence statistics across corpora leads us to focus instead the on phenomenon of word repetition within single documents. We show that given the detection of one instance of a term we are more likely to find additional instances of that term in the same document. We leverage this
       burstiness
       of keywords by taking the most confident keyword hypothesis in each document and interpolating with lower scoring hits. We then develop a principled approach to select interpolation weights using only the ASR training data. Using this re-weighting approach we demonstrate consistent improvement in the term detection performance across all five languages in the
       BABEL
       program.
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
        The
        spoken term detection
        task arises as a key subtask in applying NLP applications to spoken content. Tasks like topic identification and named-entity detection require transforming a continuous acoustic signal into a stream of discrete tokens which can then be handled by NLP and other statistical machine learning techniques. Given a small vocabulary of interest (1000-2000 words or multi-word terms) the aim of the term detection task is to enumerate occurrences of the keywords within a target corpus. Spoken term detection converts the raw acoustics into time-marked keyword occurrences, which may subsequently be fed (e.g. as a bag-of-terms) to standard NLP algorithms.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Although spoken term detection does not require the use of word-based automatic speech recognition (ASR), it is closely related. If we had perfectly accurate ASR in the language of the corpus, term detection is reduced to an exact string matching task. The word error rate (WER) and term detection performance are clearly correlated. Given resource constraints, domain, channel, and vocabulary limitations, particularly for languages other than English, the errorful token stream makes term detection a non-trivial task.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In order to improve detection performance, and restricting ourselves to an existing ASR system or systems at our disposal, we focus on leveraging
        broad document context
        around detection hypotheses. ASR systems traditionally use N-gram language models to incorporate prior knowledge of word occurrence patterns into prediction of the next word in the token stream. N-gram models cannot, however, capture complex linguistic or topical phenomena that occur outside the typical 3-5 word scope of the model. Yet, though many language models more sophisticated than N-grams have been proposed, N-grams are empirically hard to beat in terms of WER.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We consider term detection rather than the transcription task in considering how to exploit topic context, because in evaluating the retrieval of certain key terms we need not focus on improving the entire word sequence. Confidence scores from an ASR system (which incorporate N-gram probabilities) are optimized in order to produce the most likely sequence of words rather than the accuracy of individual word detections. Looking at broader document context within a more limited task might allow us to escape the limits of N-gram performance. We will show that by focusing on contextual information in the form of word repetition within documents, we obtain consistent improvement
        across five languages
        in the so called Base Phase of the
        IARPA BABEL
        program.
       </p>
      </div>
      <div class="ltx_subsection" id="S1.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         1.1
        </span>
        Task Overview
       </h3>
       <div class="ltx_para" id="S1.SS1.p1">
        <p class="ltx_p">
         We evaluate term detection and word repetition-based re-scoring on the
         IARPA BABEL
         training and development corpora
         for five languages Cantonese, Pashto, Turkish, Tagalog and Vietnamese
         []
         . The
         BABEL
         task is modeled on the 2006 NIST Spoken Term Detection evaluation
         []
         but focuses on limited resource conditions. We focus specifically on the so called
         no target audio reuse
         (NTAR) condition to make our method broadly applicable.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p2">
        <p class="ltx_p">
         In order to arrive at our eventual solution, we take the
         BABEL
         Tagalog corpus and analyze word co-occurrence and repetition statistics in detail. Our observation of the variability in co-occurrence statistics between Tagalog training and development partitions leads us to narrow the scope of document context to same word co-occurrences, i.e.
         word repetitions
         .
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p3">
        <p class="ltx_p">
         We then analyze the tendency towards within-document repetition. The strength of this phenomenon suggests it may be more viable for improving term-detection than, say, topic-sensitive language models. We validate this by developing an interpolation formula to boost putative word repetitions in the search results, and then investigate a method for setting interpolation weights without manually tuning on a development set.
        </p>
       </div>
       <div class="ltx_para" id="S1.SS1.p4">
        <p class="ltx_p">
         We then demonstrate that the method generalizes well, by applying it to the 2006 English data and the remaining four 2013
         BABEL
         languages. We demonstrate consistent improvements in all languages in both the Full LP (80 hours of ASR training data) and Limited LP (10 hours) settings.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Motivation
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We seek a workable definition of
        broad document context
        beyond N-gram models that will improve term detection performance on an arbitrary set of queries. Given the rise of unsupervised latent topic modeling with Latent Dirchlet Allocation
        []
        and similar latent variable approaches for discovering meaningful word co-occurrence patterns in large text corpora, we ought to be able to leverage these topic contexts instead of merely N-grams. Indeed there is work in the literature that shows that various topic models, latent or otherwise, can be useful for improving language model perplexity and word error rate (Khudanpur and Wu, 1999; Chen, 2009; Naptali et al., 2012). However, given the preponderance of highly frequent non-content words in the computation of a corpus’ WER, it’s not clear that a 1-2% improvement in WER would translate into an improvement in term detection.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Still, intuition suggests that knowing the topic context of a detected word ought to be useful in predicting whether or not a term does belong in that context. For example, if we determine the context of the detection hypothesis is about computers, containing words like ‘monitor,’ ‘internet’ and ‘mouse,’ then we would be more confident of a term such as ‘keyboard’ and less confident of a term such as ‘cheese board’. The difficulty in this approach arises from the variability in word co-occurrence statistics. Using topic information will be helpful if ‘monitor,’ ‘keyboard’ and ‘mouse’ consistently predict that ‘keyboard’ is present. Unfortunately, estimates of co-occurrence from small corpora are not very consistent, and often over- or underestimate concurrence probabilities needed for term detection.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        We illustrate this variability by looking at how consistent word co-occurrences are between two separate corpora in the same language: i.e., if we observe words that frequently co-occur with a keyword in the training corpus, do they also co-occur with the keywords in a second held-out corpus? Figure
        1
        , based on the
        BABEL
        Tagalog corpus, suggests this is true only for high frequency keywords.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Each point in Figure
        1
        represents one of 355 Tagalog keywords used for system development by all
        BABEL
        participants. For each keyword
        k
        , we count how often it co-occurs in the same conversation as a vocabulary word
        w
        in the ASR training data and the development data, and designate the counts
        T⁢(k,w)
        and
        D⁢(k,w)
        respectively. The
        x
        -coordinate of each point in Figure
        1
        is the frequency of
        k
        in the training data, and the
        y
        -coordinate is the correlation coefficient
        ρk
        between
        T⁢(k,w)
        and
        D⁢(k,w)
        . A high
        ρk
        implies that words
        w
        that co-occur frequently with
        k
        in the training data also do so in the search collection.
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        To further illustrate how Figure
        1
        was obtained, consider the high-frequency keyword
        bukas
        (count
        =𝟖𝟕𝟗
        ) and the low-frequency keyword
        Davao
        (count
        =𝟏𝟏
        ), and plot
        T⁢(k, ⋅)
        versus
        D⁢(k, ⋅)
        , as done in Figure
        4
        . The correlation coefficients
        ρ𝑏𝑢𝑘𝑎𝑠
        and
        ρ𝐷𝑎𝑣𝑎𝑜
        from the two plots end up as two points in Figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        Figure
        1
        suggests that
        (k,w)
        co-occurrences are consistent between the two corpora (
        ρk&gt;0.8
        ) for keywords occurring 100 or more times. However, if the goal is to help a speech retrieval system detect content-rich (and presumably infrequent) keywords, then using word co-occurrence information (i.e. topic context) does not appear to be too promising, even though intuition suggests that such information ought to be helpful.
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <p class="ltx_p">
        In light of this finding, we will restrict the type of
        context
        we use for term detection to the co-occurrence of the term itself elsewhere within the document. As it turns out this ‘burstiness’ of words within documents, as the term is defined by Church and Gale in their work on Poisson mixtures (1995), provides a more reliable framework for successfully exploiting document context.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Related Work
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         A number of efforts have been made to augment traditional N-gram models with latent topic information (Khudanpur and Wu, 1999; Florian and
Yarowsky, 1999; Liu and Liu, 2008; Hsu and Glass, 2006; Naptali et al., 2012) including some of the early work on Probabilistic Latent Semantic Analysis by
         . In all of these cases WER gains in the 1-2% range were observed by interpolating latent topic information with N-gram models.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The re-scoring approach we present is closely related to adaptive or cache language models (Jelinek, 1997; Kuhn and De Mori, 1990; Kneser and Steinbiss, 1993). The primary difference between this and previous work on similar language models is the narrower focus here on the term detection task, in which we consider each search term in isolation, rather than all words in the vocabulary. Most recently,
         looked at word bursts in the
         IARPA BABEL
         conversational corpora, and were also able to successfully improve performance by leveraging the burstiness of language. One advantage of the approach proposed here, relative to their approach, is its simplicity and its not requiring an additional tuning set to estimate parameters.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p5">
        <p class="ltx_p">
         In the information retrieval community, clustering and latent topic models have yielded improvements over traditional vector space models. We will discuss in detail in the following section related works by Church and Gale (1995, 1999, and 2000). Work by
         and
         take a language model-based approach to information retrieval, and again, interpolate latent topic models with N-grams to improve retrieval performance. However, in many text retrieval tasks, queries are often tens or hundreds of words in length rather than short spoken phrases. In these efforts, the topic model information was helpful in boosting retrieval performance above the baseline vector space or N-gram models.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p6">
        <p class="ltx_p">
         Clearly topic or context information is relevant to a retrieval type task, but we need a stable, consistent framework in which to apply it.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Term and Document Frequency Statistics
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        To this point we have assumed an implicit property of low-frequency words which Church and Gale state concisely in their 1999 study of
        inverse document frequency
        :
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Low frequency words tend to be rich in content, and vice versa. But not all equally frequent words are equally meaningful.
         .
        </p>
       </blockquote>
       <p class="ltx_p">
        The typical use of Document Frequency (
        DF
        ) in information retrieval or text categorization is to emphasize words that occur in only a few documents and are thus more “rich in content”. Close examination of
        DF
        statistics by Church and Gale in their work on Poisson Mixtures (1995) resulted in an analysis of the
        burstiness
        of content words.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        In this section we look at
        DF
        and
        burstiness
        statistics applying some of the analyses of
        to the
        BABEL
        Tagalog corpus. We observe, in 648 Tagalog conversations, similar phenomena as observed by Church and Gale on 89,000 AP English newswire articles. We proceed in this fashion to make a case for why burstiness ought to help in the term detection task.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        For the Tagalog conversations, as with English newswire, we observe that the document frequency,
        DFw
        , of a word
        w
        is not a linear function of word frequency
        fw
        in the log domain, as would be expected under a naive Poisson generative assumption. The implication of deviations from a Poisson model is that
        words tend to be concentrated in a small number of documents
        rather than occurring uniformly across the corpus. This is the
        burstiness
        we leverage to improve term detection.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The first illustration of word burstiness can be seen by plotting observed inverse document frequency,
        IDFw
        , versus
        fw
        in the log domain (Figure
        7
        ). We use the same definition of
        IDFw
        as
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E1">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          IDFw
         </td>
         <td class="ltx_td ltx_align_left">
          =-log2⁡DFwN,
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
        N
        is the number of documents (i.e. conversations) in the corpus.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        There is good linear correlation (
        ρ=0.73
        ) between
        log⁡fw
        and
        IDFw
        . Yet, visually, the relationship in Figure
        7
        is clearly not linear. In contrast, the AP English data exhibits a correlation of
        ρ=0.93
        []
        . Thus the deviation in the Tagalog corpus is more pronounced, i.e. words are less uniformly distributed across documents.
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        A second perspective on word burstiness that follows from
        is that a Poisson assumption should lead us to predict:
       </p>
       IDF^w=-log2⁡(1-e-fwN).

(2)
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        For the AP newswire, Church and Gale found the largest deviation between the predicted
        IDFw^
        and observed
        IDFw
        to occur in the middle of the frequency range. We see a somewhat different picture for Tagalog speech in Figure
        7
        . Observed
        IDFw
        values again deviate significantly from their predictions (
        2
        ), but all along the frequency range.
       </p>
      </div>
      <div class="ltx_para" id="S3.p8">
       <p class="ltx_p">
        There is a noticeable quantization effect occurring in the high
        IDF
        range, given that our
        N
        is at least a factor of 100 smaller than the number of AP articles they studied: 648 vs. 89,000. Figure
        8
        also shows the difference between and observed
        IDFw
        and Poisson estimate
        IDF^w
        and further illustrates the high variance in
        IDFw
        for low frequency words.
       </p>
      </div>
      <div class="ltx_para" id="S3.p9">
       <p class="ltx_p">
        Two questions arise: what is happening with infrequent words, and why does this matter for term detection? To look at the data from a different perspective, we consider the random variable
        k
        , which is the number of times a word occurs in a particular document. In Figure
        9
        we plot the following ratio, which
        define as
        burstiness
        :
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx2">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E3">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          Ew⁢[k⁢|k&gt;⁢0]
         </td>
         <td class="ltx_td ltx_align_left">
          =fwDFw
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (3)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        as a function of
        fw
        . We denote this as
        E⁢[k]
        and can interpret burstiness as the expected word count given we see
        w
        at least once.
       </p>
      </div>
      <div class="ltx_para" id="S3.p10">
       <p class="ltx_p">
        In Figure
        9
        we see two classes of words emerge. A similar phenomenon is observed concerning adaptive language models
        []
        . In general, we can think of using word repetitions to re-score term detection as applying a limited form of adaptive or cache language model
        []
        . Likewise, Katz attempts to capture these two classes in his G model of word frequencies (1996).
       </p>
      </div>
      <div class="ltx_para" id="S3.p11">
       <p class="ltx_p">
        For the first class, burstiness increases slowly but steadily as
        w
        occurs more frequently. Let us label these Class A words. Since our corpus size is fixed, we might expect this to occur, as more word occurrences must be pigeon-holed into the same number of documents
       </p>
      </div>
      <div class="ltx_para" id="S3.p12">
       <p class="ltx_p">
        Looking close to the
        y
        -axis in Figure
        9
        , we observe a second class of exclusively low frequency words whose burstiness ranges from highly concentrated to singletons. We will refer to these as Class B words. If we take the Class A concentration trend as typical, we can argue that most Class B words exhibit a larger than average concentration. In either case we see evidence that
        both high and low frequency words tend towards repeating within a document
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Unigram Probabilities
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In applying the
         burstiness
         quantity to term detection, we recall that the task requires us to locate a particular instance of a term, not estimate a count, hence the utility of N-gram language models predicting words in sequence.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         We encounter the burstiness property of words again by looking at unigram occurrence probabilities. We compare the unconditional unigram probability (the probability that a given word token is
         w
         ) with the conditional unigram probability,
         given the term has occurred once in the document
         . We compute the conditional probability for
         w
         using frequency information.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx3">
         <tr class="ltx_equation ltx_align_baseline" id="S3.E4">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           P⁢(w⁢|k&gt;⁢0)
          </td>
          <td class="ltx_td ltx_align_left">
           =fw-DFw∑D:w∈D|D|
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (4)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         Figure
         10
         shows the difference between conditional and unconditional unigram probabilities. Without any other information, Zipf’s law suggests that most word types do not occur in a particular document. However, conditioning on one occurrence, most word types are more likely to occur again, due to their burstiness.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         Finally we measure the
         adaptation
         of a word, which is defined by
         as:
        </p>
        Pa⁢d⁢a⁢p⁢t(w)=Pw(k&gt;1|k&gt;0)

(5)
        <p class="ltx_p">
         When we plot adaptation versus
         fw
         (Figure
         11
         ) we see that all high-frequency and a significant number of low-frequency terms have adaptation greater that 50%. To be precise, 26% of all tokens and 25% of low-frequency (
         fw&lt;100
         ) have at least 50% adaptation. Given that adaptation values are roughly an order of magnitude higher than the conditional unigram probabilities, in the next two sections we describe how we use adaptation to boost term detection scores.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Term Detection Re-scoring
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We summarize our re-scoring of repeated words with the observation:
        given a correct detection, the likelihood of additional terms in the same documents should increase
        . When we observe a term detection score with high confidence, we boost the other lower-scoring terms in the same document to reflect this increased likelihood of repeated terms.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        For each term
        t
        and document
        d
        we propose interpolating the ASR confidence score for a particular detection
        td
        with the top scoring hit in
        d
        which we’ll call
        t^d
        .
       </p>
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx4">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E6">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          S⁢(td)
         </td>
         <td class="ltx_td ltx_align_left">
          =(1-α)Pasr(td|O)+αPasr(t^d|O)
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (6)
          </span>
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        We will we develop a principled approach to selecting
        α
        using the adaptation property of the corpus. However to verify that this approach is worth pursuing, we sweep a range of small
        α
        values, on the assumption that we still do want to mostly rely on the ASR confidence score for term detection. For the Tagalog data, we let
        α
        range from 0 (the baseline) to 0.4 and re-score each term detection score according to (
        6
        ). Table
        1
        shows the results of this parameter sweep and yields us 1 to 2% absolute performance gains in a number of term detection metrics.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        The primary metric for the
        BABEL
        program, Actual Term Weighted Value (ATWV) is defined by NIST using a cost function of the false alarm probability
        P⁢(FA)
        and
        P⁢(Miss)
        , averaged over a set of queries
        []
        . The manner in which the components of ATWV are defined:
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx5">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E7">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P⁢(Miss)
         </td>
         <td class="ltx_td ltx_align_left">
          =1-Ntrue⁢(term)/fterm
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (7)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E8">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          P⁢(FA)
         </td>
         <td class="ltx_td ltx_align_left">
          =Nfalse/D⁢u⁢r⁢a⁢t⁢i⁢o⁢ncorpus
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="1">
          <span class="ltx_tag ltx_tag_equation">
           (8)
          </span>
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        implies that cost of a miss is inversely proportional to the frequency of the term in the corpus, but the cost of a false alarm is fixed. For this reason, we report both ATWV and the
        P⁢(Miss)
        component. A decrease in
        P⁢(Miss)
        reflects the fact that we are able to boost correct detections of the repeated terms.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Interpolation Weights
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We would prefer to use prior knowledge rather than naive tuning to select an interpolation weight
         α
         . Our analysis of word burstiness suggests that
         adaptation
         , is a reasonable candidate. Adaptation also has the desirable property that we can estimate it for each word in the training vocabulary directly from training data and not post-hoc on a per-query basis. We consider several different estimates and we can show that the favorable result extends across languages.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Intuition suggests that we prefer per-term interpolation weights related to the term’s
         adaptation
         . But despite the strong evidence of the adaptation phenomenon in both high and low-frequency words (Figure
         11
         ), we have less confidence in the adaptation strength of any particular word.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         As with word co-occurrence, we consider if estimates of
         Pa⁢d⁢a⁢p⁢t⁢(w)
         from training data are consistent when estimated on development data. Figure
         12
         shows the difference between
         Pa⁢d⁢a⁢p⁢t⁢(w)
         measured on the two corpora (for words occurring in both).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         We see that the adaptation estimates are only consistent between corpora for high-frequency words. Using this
         Pa⁢d⁢a⁢p⁢t⁢(w)
         estimate directly actually hurts ATWV performance by 4.7% absolute on the 355 term development query set (Table
         2
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         Given the variability in estimating
         Pa⁢d⁢a⁢p⁢t⁢(w)
         , an alternative approach would be take
         Pw^
         as an upper bound on
         α
         , reached as the
         DFw
         increases (cf. Equation
         9
         ). We would discount the adaptation factor when
         DFw
         is low and we are unsure of the effect.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p6">
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx6">
         <tr class="ltx_equation ltx_align_baseline" id="S4.E9">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           αw
          </td>
          <td class="ltx_td ltx_align_left">
           =(1-e-DFw)⋅P^a⁢d⁢a⁢p⁢t⁢(w)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (9)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S4.SS1.p7">
        <p class="ltx_p">
         This approach shows a significant improvement (0.7% absolute) over the baseline. However, considering this estimate in light of the two classes of words in Figure
         9
         , there are clearly words in Class B with high burstiness that will be ignored by trying to compensate for the high adaptation variability in the low-frequency range.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p8">
        <p class="ltx_p">
         Alternatively, we take a weighted average of
         αw
         ’s estimated on training transcripts to obtain a single
         α^
         per language (cf. Equation
         10
         ).
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx7">
         <tr class="ltx_equation ltx_align_baseline" id="S4.E10">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           α^
          </td>
          <td class="ltx_td ltx_align_left">
           =Avgw⁡[(1-e-DFw)⋅P^a⁢d⁢a⁢p⁢t⁢(w)]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (10)
           </span>
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         Using this average as a single interpolation weight for all terms gives near the best performance as we observed in our parameter sweep. Table
         2
         contrasts the results for using the three different interpolation heuristics on the Tagalog development queries. Using the mean
         α^
         instead of individual
         αw
         ’s provides an additional 0.5% absolute improvement, suggesting that we find additional gains boosting low-frequency words.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Now that we have tested word repetition-based re-scoring on a small Tagalog development set we want to know if our approach, and particularly our
        α^
        estimate is sufficiently robust to apply broadly. At our disposal, we have the five
        BABEL
        languages — Tagalog, Cantonese, Pashto, Turkish and Vietnamese — as well as the development data from the NIST 2006 English evaluation. The
        BABEL
        evaluation query sets contain roughly 2000 terms each and the 2006 English query set contains roughly 1000 terms.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        The procedure we follow for each language condition is as follows. We first estimate adaptation probabilities from the ASR training transcripts. From these we take the weighted average as described previously to obtain a single interpolation weight
        α^
        for each training condition. We train ASR acoustic and language models from the training corpus using the Kaldi speech recognition toolkit
        []
        following the default
        BABEL
        training and search recipe which is described in detail by
        . Lastly, we re-score the search output by interpolating the top term detection score for a document with subsequent hits according to Equation
        6
        using the
        α^
        estimated for this training condition.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        For each of the
        BABEL
        languages we consider both the FullLP (80 hours) and LimitedLP (10 hours) training conditions. For the English system, we also train a Kaldi system on the 240 hours of the Switchboard conversational English corpus. Although Kaldi can produce multiple types of acoustic models, for simplicity we report results using discriminatively trained Subspace Gaussian Mixture Model (SGMM) acoustic output densities, but we do find that similar results can be obtained with other acoustic model configurations.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        Using our final algorithm, we are able to boost repeated term detections and improve results in
        all languages and training conditions
        . Table
        3
        lists complete results and the associated estimates for
        α^
        . For the
        BABEL
        languages, we observe improvements in ATWV from 0.7% to 1.3% absolute and reductions in the miss rate of 0.8% to 1.9%. The only test for which
        P⁢(Miss)
        did not improve was the Vietnamese Limited LP setting, although overall ATWV did improve, reflecting a lower
        P⁢(FA)
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p5">
       <p class="ltx_p">
        In all conditions we also obtain
        α
        estimates which correspond to our expectations for particular languages. For example, adaptation is lowest for the agglutinative Turkish language where longer word tokens should be less likely to repeat. For Vietnamese, with shorter, syllable length word tokens, we observe the lowest adaptation estimates.
       </p>
      </div>
      <div class="ltx_para" id="S5.p6">
       <p class="ltx_p">
        Lastly, the reductions in
        P⁢(Miss)
        suggests that we are improving the term detection metric, which is sensitive to threshold changes, by doing what we set out to do, which is to boost lower confidence repeated words and correctly asserting them as true hits. Moreover, we are able to accomplish this in a wide variety of languages.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
