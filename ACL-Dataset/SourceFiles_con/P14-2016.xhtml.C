<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Automatic Detection of Multilingual Dictionaries on the Web.
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
       This paper presents an approach to query construction to detect
multilingual dictionaries for predetermined language combinations on
the web, based on the identification of terms which are likely to
occur in bilingual dictionaries but not in general web documents. We
use eight target languages for our case study, and train our method on
pre-identified multilingual dictionaries and the Wikipedia dump for
each of our languages.
      </p>
     </div>
     <div class="ltx_section" id="S1">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        1
       </span>
       Motivation
      </h2>
      <div class="ltx_para" id="S1.p1">
       <p class="ltx_p">
        Translation dictionaries and other multilingual lexical resources are
valuable in a myriad of contexts, from language preservation
        [21]
        to language learning
        [10]
        , cross-language information retrieval
        [17]
        and machine translation
        [15, 20]
        . While there are syndicated
efforts to produce multilingual dictionaries for different pairings of
the world’s languages such as
        freedict.org
        , more commonly,
multilingual dictionaries are developed in isolation for a specific set
of languages, with ad hoc formatting, great variability in lexical
coverage, and no central indexing of the content or existence of that
dictionary
        [2]
        . Projects such as
        panlex.org
        aspire to aggregate these dictionaries into a single lexical database,
but are hampered by the need to identify individual multilingual
dictionaries, especially for language pairs where there is a sparsity of
data from existing dictionaries
        [2, 9]
        . This paper is an attempt to
automate the detection of multilingual dictionaries on the web, through
query construction for an arbitrary language pair. Note that for the
method to work, we require that the dictionary occurs in “list form”,
that is it takes the form of a single document (or at least, a
significant number of dictionary entries on a single page), and is not
split across multiple small-scale sub-documents.
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
        This research seeks to identify documents of a particular type on the
web, namely multilingual dictionaries. Related work broadly falls into
four categories: (1) mining of parallel corpora; (2) automatic
construction of bilingual dictionaries/thesauri; (3) automatic detection
of multilingual documents; and (4) classification of document genre.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Parallel corpus construction is the task of automatically detecting
document sets that contain the same content in different languages,
commonly based on a combination of site-structural and content-based
features
        [3, 19]
        . Such methods could
potentially identify parallel word lists from which to construct a
bilingual dictionary, although more realistically, bilingual
dictionaries exist as single documents and are not well suited to this
style of analysis.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Methods have also been proposed to automatically construct bilingual
dictionaries or thesauri, e.g. based on crosslingual glossing in
predictable patterns such as a technical term being immediately
proceeded by that term in a lingua franca source language such as
English
        [16, 24]
        . Alternatively, comparable or
parallel corpora can be used to extract bilingual dictionaries based on
crosslingual distributional similarity
        [14, 7]
        . While the
precision of these methods is generally relatively high, the recall is
often very low, as there is a strong bias towards novel technical terms
being glossed but more conventional terms not.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Also relevant to this work is research on language identification, and
specifically the detection of multilingual documents
        [18, 23, 11]
        . Here,
multi-label document classification methods have been adapted to
identify what mix of languages is present in a given document, which
could be used as a pre-filter to locate documents containing a given
mixture of languages, although there is, of course, no guarantee that a
multilingual document is a dictionary.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Finally, document genre classification is relevant in that it is
theoretically possible to develop a document categorisation method which
classifies documents as multilingual dictionaries or not, with the
obvious downside that it would need to be applied exhaustively to all
documents on the web. The general assumption in genre classification is
that the type of a document should be judged not by its content but
rather by its form. A variety of document genre methods have been
proposed, generally based on a mixture of structural and content-based
features
        [12, 5, 25]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        While all of these lines of research are relevant to this work, as far
as we are aware, there has not been work which has proposed a direct
method for identifying pre-existing multilingual dictionaries in document
collections.
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
        Our method is based on a query formulation approach, and querying
against a pre-existing index of a document collection (e.g. the web)
via an information retrieval system.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The first intuition underlying our approach is that certain words are a
priori more “language-discriminating” than others, and should be
preferred in query construction (e.g.
        sushi
        occurs as a
[transliterated] word in a wide variety of languages, whereas
        anti-discriminatory
        is found predominantly in English
documents). As such, we prefer search terms
        wi
        with a higher value
for
        maxlP(l|wi)
        , where
        l
        is the language of interest.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The second intuition is that the lexical coverage of dictionaries varies
considerably, especially with multilingual lexicons, which are often
compiled by a single developer or small community of developers, with
little systematicity in what is including or not included in the
dictionary. As such, if we are to follow a query construction approach
to lexicon discovery, we need to be able to predict the likelihood of a
given word
        wi
        being included in an arbitrarily-selected dictionary
        Dl
        incorporating language
        l
        (i.e.
        P(wi|Dl)
        ). Factors which
impact on this include the lexical prior of the word in the language
(e.g.
        P(𝑝𝑎𝑝𝑒𝑟|en)
        &gt;
        P(𝑝𝑎𝑝𝑦𝑟𝑢𝑠|en)
        ), whether they are
lemmas or not (noting that multilingual dictionaries tend not to contain
inflected word forms), and their word class (e.g. multilingual
dictionaries tend to contain more nouns and verbs than function words).
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The third intuition is that certain word
        combinations
        are more
selective of multilingual dictionaries than others, i.e. if certain words
are found together (e.g.
        cruiser
        ,
        gospel
        and
        noodle
        ),
the containing document is highly likely to be a dictionary of some
description rather than a “conventional” document.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        Below, we describe our methodology for query construction based on these
elements in greater detail. The only assumption on the method is that we
have access to a selection of dictionaries
        D
        (mono- or multilingual)
and a corpus of conventional (non-dictionary) documents
        C
        , and
knowledge of the language(s) contained in each dictionary and document.
       </p>
      </div>
      <div class="ltx_para" id="S3.p6">
       <p class="ltx_p">
        Given a set of dictionaries
        Dl
        for a language
        l
        and the complement
set
        Dl¯=D∖Dl
        , we first construct the lexicon
        Ll
        for that language as follows:
       </p>
       Ll={wi|wi∈Dl∩wi∉Dl¯}

(1)
       <p class="ltx_p">
        This creates a language-discriminating lexicon for each language,
satisfying the first criterion.
       </p>
      </div>
      <div class="ltx_para" id="S3.p7">
       <p class="ltx_p">
        Lexical resources differ in size, scope and coverage. For instance, a
well-developed, mature multilingual dictionary may contain over 100,000
multilingual lexical records, while a specialised 5-way multilingual domain
dictionary may contain as few as 100 multilingual lexical records. In
line with our second criterion, we want to select words which have a
higher likelihood of occurrence in a multilingual dictionary involving
that language. To this end, we calculate the weight
        sdict⁢(wi,l)
        for
each word
        wi,l∈Ll
        :
       </p>
       sdict(wi,l)=∑d∈Dl{|Ll|-|d||Ll|if ⁢wi,l∈d-|d||Ll|otherwise

(2)
       <p class="ltx_p">
        where
        |d|
        is the size of dictionary
        d
        in terms of the number of
lexemes it contains.
       </p>
      </div>
      <div class="ltx_para" id="S3.p8">
       <p class="ltx_p">
        The final step is to weight words by their typicality in a given
language, as calculated by their likelihood of occurrence in a random
document in that language. This is estimated by the proportion of
Wikipedia documents in that language which contain the word in question:
       </p>
       Score⁢(wi,l)=d⁢f⁢(wi,l)Nl⁢sdict⁢(wi,l)

(3)
       <p class="ltx_p">
        where
        d⁢f⁢(wi,l)
        is the count of Wikipedia documents of language
        l
        which contain
        wi
        , and
        Nl
        is the total number of Wikipedia
documents in language
        l
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p9">
       <p class="ltx_p">
        In all experiments in this paper, we assume that we have access to at
least one multilingual dictionary containing each of our target
languages, but in absence of such a dictionary,
        sdict⁢(wi,l)
        could be set to 1 for all words
        wi,l
        in the language.
       </p>
      </div>
      <div class="ltx_para" id="S3.p10">
       <p class="ltx_p">
        The result of this term weighing is a ranked list of words for each
language. The next step is to identify combinations of words that are
likely to be found in multilingual dictionaries and not standard
documents for a given language, in accordance with our third criterion.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Apriori-based query generation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We perform query construction for each language based on frequent item
set mining, using the Apriori algorithm
         [1]
         . For a
given combination of languages (e.g. English and Swaheli), queries are
then formed simply by combining monolingual queries for the component
languages.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         The basic approach is to use a modified support formulation within the
Apriori algorithm to prefer word combinations that do not cooccur in
regular documents. Based on the assumption that querying a (pre-indexed)
document collection is relatively simple, we generate a range of queries
of decreasing length and increasing likelihood of term co-occurrence in
standard documents, and query until a non-empty set of results is
returned.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         The modified support formulation is as follows:
        </p>
        <table class="ltx_equationgroup ltx_eqn_eqnarray" id="S6.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_left" colspan="3">
           cscore⁢(w1,…,wn)=
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_align_baseline">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_center">
          </td>
          <td class="ltx_td ltx_align_left">
           {0if ⁢∃d,wi,wj:cod⁢(wi,wj)∏iS⁢c⁢o⁢r⁢e⁢(wi)otherwise
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         cod⁢(wi,wj)
         is a Boolean function which
evaluates to true iff
         wi
         and
         wj
         co-occur in document
         d
         . That is,
we reject any combinations of words which are found to co-occur in
Wikipedia documents for that language. Note that the actual calculation
of this co-occurrence can be performed efficiently, as: (a) for a given
iteration of Apriori, it only needs to be performed between the new word
that we are adding to the query (“item set” in the terminology of
Apriori) and each of the other words in a non-zero support itemset from
the previous iteration of the algorithm (which are guaranteed to not
co-occur with each other); and (b) the determination of whether two
terms collocate can be performed efficiently using an inverted index of
Wikipedia for that language.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         In our experiments, we apply the Apriori algorithm exhaustively for a
given language with a support threshold of 0.5, and return the resultant
item sets in ranked order of combined score for the component words.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p5">
        <p class="ltx_p">
         A random selection of queries learned for each of the 8 languages
targeted in this research is presented in Figure
         1
         .
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experimental methodology
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We evaluate our proposed methodology in two ways:
       </p>
       <ol class="ltx_enumerate" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           against a synthetic dataset, whereby we injected bilingual
dictionaries into a collection of web documents, and evaluated the
ability of the method to return multilingual dictionaries for
individual languages; in this, we naively assume that all web
documents in the background collection are not multilingual
dictionaries, and as such, the results are potentially an
underestimate of the true retrieval effectiveness.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           against the open web via the Google search API for a given
combination of languages, and hand evaluation of the returned
documents
          </p>
         </div>
        </li>
       </ol>
       <p class="ltx_p">
        Note that the first evaluation with the synthetic dataset is based on
        monolingual
        dictionary retrieval effectiveness because we have
very few (and often no) multilingual dictionaries for a given pairing of
our target languages. For a given language, we are thus evaluating the
ability of our method to retrieve multilingual dictionaries containing
that language (and other indeterminate languages).
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        For both the synthetic dataset and open web experiments, we evaluate our
method based on mean average precision (MAP), that is the mean of the
average precision scores for each query which returns a non-empty
result set.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        To train our method, we use 52 bilingual Freedict
        [6]
        dictionaries and Wikipedia
        documents for
each of our target languages. As there are no bilingual dictionaries in
Freedict for Chinese and Japanese, the training of
        Score
        values
is based on the Wikipedia documents only. Morphological segmentation for
these two languages was carried out using MeCab
        [13]
        and the
Stanford Word Segmenter
        [22]
        , respectively. See
Table
        1
        for details of the number of Wikipedia articles
and dictionaries for each language.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Below, we detail the construction of the synthetic dataset.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Synthetic dataset
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         The synthetic dataset was constructed using a subset of ClueWeb09
         [4]
         as the background web document collection. The original
ClueWeb09 dataset consists of around 1 billion web pages in ten
languages that were collected in January and February 2009. The relative
proportions of documents in the different languages in the original
dataset are as detailed in Table
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         We randomly downsampled ClueWeb09 to 10 million documents for the 8
languages targeted in this research (the original 10 ClueWeb09 languages
minus Korean and Portuguese). We then sourced a random set of 246
multilingual dictionaries that were used in the construction of
         panlex.org
         , and injected them into the document collection. Each
of these dictionaries contains at least one of our 8 target languages,
with the second language potentially being outside the 8. A total of 49
languages are contained in the dictionaries.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         We indexed the synthetic dataset using Indri
         [8]
         .
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
        First, we present results over the synthetic dataset in
Table
        3
        . As our baseline, we simply query for the
language name and the term
        dictionary
        in the local language (e.g.
        English dictionary
        , for English) in the given language.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        For languages that had bilingual dictionaries for training, the best
results were obtained for Spanish, German, Italian and
Arabic. Encouragingly, the results for languages with only Wikipedia
documents (and no dictionaries) were largely comparable to those for
languages with dictionaries, with Japanese achieving a MAP score
comparable to the best results for languages with dictionary training
data. The comparably low result for English is potentially affected by
its prevalence both in the bilingual dictionaries in training
(restricting the effective vocabulary size due to our
        Ll
        filtering),
and in the document collection. Recall also that our MAP scores are an
underestimate of the true results, and some of the ClueWeb09 documents
returned for our queries are potentially relevant documents (i.e. multilingual dictionaries including the language of interest). For all
languages, the baseline results were below 0.1, and substantially lower
than the results for our method.
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Looking next to the open web, we present in Table
        4
        results based on querying the Google search API with the 1000 longest
queries for English paired with each of the other 7 target
languages. Most queries returned no results; indeed, for the en-ar
language pair, only 49/1000 queries returned documents. The results in
Table
        4
        are based on manual evaluation of all documents
returned for the first 50 queries, and determination of whether they
were multilingual dictionaries containing the indicated languages.
       </p>
      </div>
      <div class="ltx_para" id="S5.p4">
       <p class="ltx_p">
        The baseline results are substantially higher than those for the
synthetic dataset, almost certainly a direct result of the greater
sophistication and optimisation of the Google search engine (including
query log analysis, and link and anchor text analysis). Despite this,
the results for our method are lower than those over the synthetic
dataset, we suspect largely as a result of the style of queries we issue
being so far removed from standard Google query patterns. Having said
this, MAP scores of 0.32–0.92 suggest that the method is highly usable
(i.e. at any given cutoff in the document ranking, an average of at
least one in three documents is a genuine multilingual dictionary), and
any non-dictionary documents returned by the method could easily be
pruned by a lexicographer. Among the 7 language pairs, en-es, en-de,
en-fr and en-it achieved the highest MAP scores. In terms of unique
lexical resources found with 50 queries, the most successful language
pairs were en-fr, en-de and en-it.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
