<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Learning Translational and Knowledge-based Similaritiesfrom Relevance Rankings for Cross-Language Retrieval.
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
       We present an approach to cross-language retrieval that combines dense
knowledge-based features and sparse word translations. Both feature types
are learned directly from relevance rankings of bilingual documents in a
pairwise ranking framework. In large-scale experiments for
patent prior art search and cross-lingual retrieval in Wikipedia,
our approach yields considerable improvements over learning-to-rank
with either only dense or only sparse features, and over very competitive
baselines that combine state-of-the-art machine translation and retrieval.
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
        Cross-Language Information Retrieval (CLIR) for the domain of web search successfully leverages state-of-the-art Statistical Machine Translation (SMT) to either produce a single most probable translation, or a weighted list of alternatives, that is used as search query to a standard search engine
        [5, 25]
        . This approach is advantageous if large amounts of in-domain sentence-parallel data are available to train SMT systems, but relevance rankings to train retrieval models are not.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The situation is different for CLIR in special domains such as patents or Wikipedia. Parallel data for translation have to be extracted with some effort from comparable or noisy parallel data
        [26, 22]
        , however, relevance judgments are often straightforwardly encoded in special domains. For example, in patent prior art search, patents granted at any patent office worldwide are considered relevant if they constitute prior art with respect to the invention claimed in the query patent. Since patent applicants and lawyers are required to list relevant prior work explicitly in the patent application, patent citations can be used to automatically extract large amounts of relevance judgments across languages
        [12]
        . In Wikipedia search, one can imagine a Wikipedia author trying to investigate whether a Wikipedia article covering the subject the author intends to write about already exists in another language. Since authors are encouraged to avoid orphan articles and to cite their sources, Wikipedia has a rich linking structure between related articles, which can be exploited to create relevance links between articles across languages
        [2]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Besides a rich citation structure, patent documents and Wikipedia articles contain a number of further cues on relatedness that can be exploited as features in learning-to-rank approaches. For monolingual patent retrieval,
        Guo and Gomes (2009)
        and
        Oh et al. (2013)
        advocate the use of dense features encoding domain knowledge on inventors, assignees, location and date, together with dense similarity scores based on bag-of-word representations of patents.
        Bai et al. (2010)
        show that for the domain of Wikipedia, learning a sparse matrix of word associations between the query and document vocabularies from relevance rankings is useful in monolingual and cross-lingual retrieval.
        Sokolov et al. (2013)
        apply the idea of learning a sparse matrix of bilingual phrase associations from relevance rankings to cross-lingual retrieval in the patent domain. Both show improvements of learning-to-rank on relevance data over SMT-based approaches on their respective domains.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The main contribution of this paper is a thorough evaluation of dense and
sparse features for learning-to-rank that have so far been used only
monolingually or only on either patents or Wikipedia. We show that for both
domains, patents and Wikipedia, jointly learning bilingual sparse word associations
and dense knowledge-based similarities directly on relevance ranked data improves
significantly over approaches that use either only sparse or only dense features, and over approaches that combine query translation by SMT with standard retrieval in the
target language. Furthermore, we show that our approach can be seen as supervised model combination that allows to combine SMT-based and ranking-based
approaches for further substantial
improvements. We conjecture that the gains are due to orthogonal information
contributed by domain-knowledge, ranking-based word associations, and
translation-based information.
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
        CLIR addresses the problem of translating or projecting a query into the language of the document repository across which retrieval is performed. In a
        direct translation
        approach (DT), a state-of-the-art SMT system is used to produce a single best translation that is used as search query in the target language. For example, Google’s CLIR approach combines their state-of-the-art SMT system with their proprietary search engine
        [5]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Alternative approaches avoid to solve the hard problem of word reordering, and
instead rely on token-to-token translations that are used to project the query
terms into the target language with a probabilistic weighting of the standard
term tf-idf scheme.
        Darwish and Oard (2003)
        termed this method the
        probabilistic structured query
        approach (PSQ).
The advantage of this technique is an implicit query expansion effect due to the use of probability distributions over term translations
        [27]
        .
        Ture et al. (2012)
        brought SMT back into this paradigm
by projecting terms from
        n
        -best translations from synchronous context-free
grammars.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Ranking approaches
        have been presented by
        Guo and Gomes (2009)
        and
        Oh et al. (2013)
        . Their method is a classical learning-to-rank setup where pairwise ranking is applied to a few hundred dense features. Methods to learn sparse word-based translation correspondences from supervised ranking signals have been presented by
        Bai et al. (2010)
        and
        Sokolov et al. (2013)
        . Both approaches work in a cross-lingual setting, the former on Wikipedia data, the latter on patents.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Our approach extends the work of
        Sokolov et al. (2013)
        by presenting an alternative learning-to-rank approach that can be used for supervised model combination to integrate dense and sparse features, and by evaluating both approaches on cross-lingual retrieval for patents and Wikipedia. This relates our work to supervised model merging approaches
        [20]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Translation and Ranking for CLIR
      </h2>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        SMT-based Models.
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         We will refer to DT and PSQ as SMT-based models that translate a query, and
then perform monolingual retrieval using BM25.
Translation is agnostic of the retrieval task.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Linear Ranking for Word-Based Models.
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         Let
         𝐪∈{0,1}Q
         be a query and
         𝐝∈{0,1}D
         be a document where the
         jth
         vector dimension
indicates the occurrence of the
         jth
         word for dictionaries of size
         Q
         and
         D
         . A linear ranking model is defined as
        </p>
        f⁢(𝐪,𝐝)=𝐪⊤⁢W⁢𝐝=∑i=1Q∑j=1Dqi⁢Wi⁢j⁢dj,
        <p class="ltx_p">
         where
         W∈I⁢RQ×D
         encodes a matrix of ranking-specific word associations
         [2]
         .
We optimize this model by pairwise ranking, which assumes labeled data in the form
of a set
         ℛ
         of tuples
         (𝐪,𝐝+,𝐝-)
         , where
         𝐝+
         is a relevant
(or higher ranked) document and
         𝐝-
         an irrelevant (or lower ranked) document
for query
         𝐪
         . The goal is to find a weight matrix
         W
         such that an inequality
         f⁢(𝐪,𝐝+)&gt;f⁢(𝐪,𝐝-)
         is violated for the fewest number of tuples from
         ℛ
         . We present two methods for optimizing
         W
         in the following.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        Pairwise Ranking using Boosting (BM).
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         The Boosting-based Ranking baseline
         [9]
         optimizes an exponential loss:
        </p>
        ℒe⁢x⁢p=∑(𝐪,𝐝+,𝐝-)∈ℛ𝒟⁢(𝐪,𝐝+,𝐝-)⁢ef⁢(𝐪,𝐝-)-f⁢(𝐪,𝐝+),
        <p class="ltx_p">
         where
         𝒟⁢(𝐪,𝐝+,𝐝-)
         is a non-negative importance function on
tuples. The algorithm of
         Sokolov et al. (2013)
         combines batch boosting with bagging over a number of independently drawn bootstrap data samples from
         ℛ
         . In each step, the single word pair feature is
selected that provides the largest decrease of
         ℒe⁢x⁢p
         .
The found corresponding models are averaged.
To reduce memory requirements we used random feature hashing
with the size of the hash of 30 bits
         [21]
         .
For regularization we rely on early stopping.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P4">
       <h3 class="ltx_title ltx_title_paragraph">
        Pairwise Ranking with SGD (VW).
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         The second objective is an
         ℓ1
         -regularized hinge loss:
        </p>
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex3">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           ℒh⁢n⁢g=∑(𝐪,𝐝+,𝐝-)∈ℛ(f⁢(𝐪,𝐝+)-f⁢(𝐪,𝐝-))++λ⁢||W||1,
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
        <p class="ltx_p">
         where
         (x)+=max⁡(0,1-x)
         and
         λ
         is the regularization parameter. This newly added model utilizes the standard implementation of online SGD from the Vowpal Wabbit (VW)
toolkit
         [11]
         and was run on a data sample of 5M to 10M tuples from
         ℛ
         .
On each step,
         W
         is updated with a scaled gradient vector
         ∇W⁡ℒh⁢n⁢g
         and clipped to account for
         ℓ1
         -regularization.
Memory usage was reduced using the same hashing technique as for boosting.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S3.SS0.SSS0.P5">
       <h3 class="ltx_title ltx_title_paragraph">
        Domain Knowledge Models.
       </h3>
       <div class="ltx_para" id="S3.SS0.SSS0.P5.p1">
        <p class="ltx_p">
         Domain knowledge features for patents were inspired by
         Guo and Gomes (2009)
         : a
feature fires if two patents share similar aspects, e.g. a common inventor.
As we do not have access to address data, we omit geolocation features
and instead add features that evaluate similarity
w.r.t. patent classes extracted from IPC codes. Documents within a patent
section, i.e. the topmost hierarchy, are too diverse to provide useful
information but more detailed classes and the count of matching classes do.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P5.p2">
        <p class="ltx_p">
         For Wikipedia, we implemented features that compare the relative length of
documents, number of links and images, the number of common links and
common images, and Wikipedia categories: Given the
categories associated with a foreign query, we use the language
links on the Wikipedia category pages to generate a set of “translated”
English categories
         S
         . The English-side category graph is used to
construct sets of super- and subcategories related to the candidate document’s
categories. This expansion is done in both directions for two levels
resulting in 5 category sets. The intersection between
target set
         Tn
         and the source category set
         S
         reflects the category level similarity
between query and document, which we calculate as a mutual
containment score
         sn=12⁢(|S∩Tn|/|S|+|S∩Tn|/|Tn|)
         for
         n∈{-2,-1,0,+1,+2}
         [3]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS0.SSS0.P5.p3">
        <p class="ltx_p">
         Optimization for these additional models including domain knowledge features was done by overloading the vector representation of queries
         𝐪
         and documents
         𝐝
         in the VW linear learner: Instead of sparse word-based features,
         𝐪
         and
         𝐝
         are represented by real-valued vectors of dense domain-knowledge features. Optimization for the overloaded vectors is done as described above for VW.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Model Combination
      </h2>
      <div class="ltx_paragraph" id="S4.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Combination by Borda Counts.
       </h3>
       <div class="ltx_para" id="S4.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         The baseline consensus-based voting Borda Count
procedure endows each voter with a fixed amount of voting points which he is
free to distribute among the scored documents
         [1, 24]
         . The aggregate score for two rankings
         f1⁢(𝐪,𝐝)
         and
         f2⁢(𝐪,𝐝)
         for all
         (𝐪,𝐝)
         in the test set is then a simple linear interpolation:
         fa⁢g⁢g⁢(𝐪,𝐝)=κ⁢f1⁢(𝐪,𝐝)∑𝐝f1⁢(𝐪,𝐝)+(1-κ)⁢f2⁢(𝐪,𝐝)∑𝐝f2⁢(𝐪,𝐝).
         Parameter
         κ
         was adjusted on the dev set.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Combination by Linear Learning.
       </h3>
       <div class="ltx_para" id="S4.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         In order to acquire the best combination of more than two models, we created vectors of model scores along with domain knowledge features and reused the VW pairwise ranking
approach. This means that the vector representation of queries
         𝐪
         and documents
         𝐝
         in the VW linear learner is overloaded once more: In addition to dense domain-knowledge features, we incorporate arbitrary ranking models as dense features whose value is the score of the ranking model. Training data was sampled from the dev set and processed with VW.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Data
      </h2>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Patent Prior Art Search (JP-EN).
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         We use BoostCLIR
         , a Japanese-English (JP-EN)
corpus of patent abstracts from the MAREC and NTCIR data
         [24]
         .
It contains automatically induced relevance judgments for patent abstracts
         [12]
         : EN patents are regarded as relevant with level (3) to
a JP query patent, if they are in a family relationship (e.g., same invention),
cited by the patent examiner (2), or cited by the applicant (1).
Statistics on the ranking data are given in Table
         1
         . On
average, queries and documents contain about 5 sentences.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Wikipedia Article Retrieval (DE-EN).
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         The intuition behind our Wikipedia retrieval setup is as follows: Consider the situation where the German (DE) Wikipedia article on geological sea
         stacks
         does not yet exist. A native speaker of German with profound
knowledge in geology intends to write it, naming it
“
         Brandungspfeiler
         ”, while seeking to align its structure with
the EN counterpart. The task of a CLIR engine is to return relevant EN
Wikipedia articles that may describe the very same concept (
         Stack
(geology)
         ), or relevant instances of it (
         Bako National Park
         ,
         Lange Anna
         ). The information need may be paraphrased as a high-level
definition of the topic. Since typically the first sentence of any
Wikipedia article is such a well-formed definition, this allows us to extract a large set of one sentence queries from Wikipedia articles. For example:
“
         Brandungspfeiler sind vor einer Kliffküste aufragende Felsentürme
und vergleichbare Formationen, die durch Brandungserosion gebildet
werden.
         ”
         Similar to
         Bai et al. (2010)
         we induce relevance
judgments by aligning DE queries with their EN counterparts (“mates”) via the
graph of inter-language links available in articles and
Wikidata
         . We assign relevance level (3) to
the EN mate and level (2) to all other EN articles that link to the mate,
         and
         are linked by the mate. Instead of using all outgoing links from
the mate, we only use articles with bidirectional
links.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         To create this data
         we downloaded XML and SQL dumps of the DE and EN Wikipedia from,
resp., 22
         nd
         and 4
         th
         of November 2013. Wikipedia markup removal and link
extraction was carried out using the Cloud9
toolkit
         . Sentence
extraction was done with NLTK
         . Since Wikipedia
articles vary greatly in length, we restricted EN documents to the first 200
words after extracting the link graph to reduce the number of features for
BM and VW models. To avoid rendering the task too easy for literal keyword
matching of queries about named entities, we removed title words from the German
queries.
Statistics are given in Table
         1
         .
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P3">
       <h3 class="ltx_title ltx_title_paragraph">
        Preprocessing Ranking Data.
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P3.p1">
        <p class="ltx_p">
         In addition to lowercasing and punctuation removal,
we applied Correlated Feature Hashing (CFH), that makes collisions more likely
for words with close meaning
         [2]
         .
For patents, vocabularies contained 60k and 365k words for JP and EN.
Filtering special symbols and stopwords reduced the JP vocabulary
size to 50k (small enough not to resort to CFH). To reduce the EN vocabulary to
a comparable size, we applied similar preprocessing
         and
         CFH with
         F
         =30k
and
         k
         =5.
Since for Wikipedia data, the DE and EN vocabularies were both large (6.7M and 6M),
we used the same filtering and preprocessing
as for the patent data before applying CFH with
         F
         =40k and
         k
         =5 on both sides.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P4">
       <h3 class="ltx_title ltx_title_paragraph">
        Parallel Data for SMT-based CLIR.
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P4.p1">
        <p class="ltx_p">
         For both
tasks, DT and PSQ require an SMT baseline system trained on parallel corpora
that are disjunct from the ranking data. A JP-EN system was trained on data
described and preprocessed by
         Sokolov et al. (2013)
         , consisting of 1.8M
parallel sentences from the NTCIR-7 JP-EN PatentMT subtask
         [10]
         and 2k parallel sentences for parameter development from the NTCIR-8 test
collection.
For Wikipedia, we trained a DE-EN system on 4.1M parallel sentences from
Europarl, Common Crawl, and News-Commentary. Parameter tuning was done on 3k
parallel sentences from the WMT’11 test set.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Experiments
      </h2>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Experiment Settings.
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         The SMT-based models use
         cdec
         [8]
         . Word alignments were created with
         mgiza
         (JP-EN) and
         fast_align
         [7]
         (DE-EN). Language models
were trained with the KenLM toolkit
         [14]
         . The JP-EN system uses a
5-gram language model from the EN side of the training data. For the DE-EN
system, a 4-gram model was built on the EN side of the training data and the EN
Wikipedia documents. Weights for the standard feature set were optimized using
         cdec
         ’s MERT (JP-EN) and MIRA (DE-EN) implementations
         [18, 4]
         .
PSQ on patents reuses settings found by
         Sokolov et al. (2013)
         ;
settings for Wikipedia were adjusted on its dev set (
         n
         =
         1000
         ,
         λ
         =
         0.4
         ,
         L
         =
         0
         ,
         C
         =
         1
         ).
        </p>
       </div>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p2">
        <p class="ltx_p">
         Patent retrieval for DT was done by sentence-wise translation and subsequent
re-joining to form one query per patent, which was ranked against the documents
using BM25. For PSQ, BM25 is computed on expected term and document frequencies.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p3">
        <p class="ltx_p">
         For ranking-based retrieval, we compare several combinations of learners and
features (Table
         2
         ). VW denotes a sparse model using word-based features trained with SGD.
BM denotes a similar model trained using Boosting. DK denotes VW training of a
model that represents queries
         𝐪
         and documents
         𝐝
         by dense domain-knowledge
features instead of by sparse word-based vectors.
In order to simulate pass-through behavior
of out-of-vocabulary terms in SMT systems, additional features accounting for source and target term identity were added to DK and BM models.
The parameter
         λ
         for VW was found on dev set. Statistical significance testing was performed using the paired randomization test
         [23]
         .
        </p>
       </div>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p4">
        <p class="ltx_p">
         Borda
         denotes model combination by Borda Count voting where the linear
interpolation parameter is adjusted for MAP on the respective development sets with grid search. This
type of model combination only allows to combine pairs of rankings. We present
a combination of SMT-based CLIR, DT+PSQ, a combination of dense and sparse
features, DK+VW, and a combination of both combinations, (DT+PSQ)+(DK+VW).
        </p>
       </div>
       <div class="ltx_para" id="S6.SS0.SSS0.P1.p5">
        <p class="ltx_p">
         LinLearn
         denotes model combination by overloading the vector
representation of queries
         𝐪
         and documents
         𝐝
         in the VW linear learner by incorporating arbitrary ranking models as dense features. In difference to grid search for
         Borda
         , optimal
weights for the linear combination of incorporated ranking models can be
learned automatically. We investigate the same
combinations of ranking models as described for
         Borda
         above. We do not
report combination results including the sparse BM model since they were
consistently lower than the ones with the sparse VW model.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S6.SS0.SSS0.P2">
       <h3 class="ltx_title ltx_title_paragraph">
        Test Results.
       </h3>
       <div class="ltx_para" id="S6.SS0.SSS0.P2.p1">
        <p class="ltx_p">
         Experimental results on test data are given in
Table
         2
         . Results are reported with respect to MAP
         [17]
         , NDCG
         [15]
         , and PRES
         [16]
         . Scores were computed on the top 1,000 retrieved documents.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS0.SSS0.P2.p2">
        <p class="ltx_p">
         As can be seen from inspecting the two blocks of results, one for patents, one for Wikipedia, we find the same system rankings on both datasets. In both cases, as
         standalone
         systems, DT and PSQ are very close and far better than any ranking approach, irrespective of the objective function or the choice of sparse or dense features. Model combination of similar models, e.g., DT and PSQ, gives minimal gains, compared to combining orthogonal models, e.g. DK and VW. The best result is achieved by combining DT and PSQ with DK and VW. This is due to the already high scores of the combined models, but also to the combination of yet other types of orthogonal information.
         Borda
         voting gives the best result under MAP which is probably due to the adjustment of the interpolation parameter for MAP on the development set. Under NDCG and PRES,
         LinLearn
         achieves the best results, showing the advantage of automatically learning combination weights that leads to stable results across various metrics.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
