<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Cross-language and Cross-encyclopedia Article Linking Using Mixed-language Topic Model and Hypernym Translation.
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
       Creating cross-language article links among different online encyclopedias is now an important task in the unification of multilingual knowledge bases.
In this paper, we propose a cross-language article linking method using a mixed-language topic model and hypernym translation features based on an SVM model to link English Wikipedia and Chinese Baidu Baike, the most widely used Wiki-like encyclopedia in China.
To evaluate our approach, we compile a data set from the top 500 Baidu Baike articles and their corresponding English Wiki articles.
The evaluation results show that our approach achieves 80.95% in MRR and 87.46% in recall.
Our method does not heavily depend on linguistic characteristics and can be easily extended to generate cross-language article links among different online encyclopedias in other languages.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       UTF8nsung
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
        Online encyclopedias are among the most frequently used Internet services today.
        One of the largest and best known online encyclopedias is Wikipedia.
Wikipedia has many language versions, and articles in one language contain hyperlinks to corresponding pages in other languages.
However, the coverage of different language ver-sions of Wikipedia is very inconsistent.
Table
        1
        shows the statistics of inter-language link pages in the English and Chinese editions in February 2014.
The total number of Chinese articles is about one-quarter of English ones, and only 2.3% of English articles have inter-language links to their Chinese versions.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        However, there are alternatives to Wikipedia for some languages.
In China, for example Baidu Baike and Hudong are the largest encyclopedia sites, containing more than 6.2 and 7 million Chinese articles respectively.
Similarly, in Korea, Naver Knowledge Encyclopedia has a large presence.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Since alternative encyclopedias like Baidu Baike are larger (by article count) and growing faster than the Chinese Wikipedia, it is worth-while to investigate creating cross-language links among different online encyclopedias.
Several works have focused on creating cross-language links between Wikipedia language versions
        [7, 9]
        or finding a cross-language link for each entity mention in a Wikipedia article, namely Cross-Language Link Discovery (CLLD)
        [10, 5]
        .
These works were able to exploit the link structure and metadata common to all Wikipedia language versions.
However, when linking between different online encyclopedia platforms this is more difficult as many of these structural features are different or not shared.
To date, little research has been done into linking between encyclopedias on different platforms.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Title translation is an effective and widely used method of creating cross-language links between encyclopedia articles.
        [11, 1]
        However, title translation alone is not always sufficient.
In some cases, for example, the titles of corresponding articles in different languages do not even match.
Other methods must be used along with title translation to create a more robust linking tool.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        In this paper, we propose a method comprising title and hypernym translation and mixed-language topic model methods to select and link related articles between the English Wikipedia and Baidu Baike online encyclopedias.
We also compile a suitable dataset from the above two encyclopedias to evaluate the linking accuracy of our method.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Method
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Cross-language article linking between different encyclopedias can be formulated as follows:
For each encyclopedia
        K
        , a collection of human-written articles, can be defined as
        K={ai}i=1n
        , where
        ai
        is an article in
        K
        and
        n
        is the size of
        K
        .
Article linking can then be defined as follows:
Given two encyclopedia
        K1
        and
        K2
        , cross-language article linking is the task of finding the corresponding equivalent article
        aj
        from encyclopedia
        K2
        for each article
        ai
        from encyclopedia
        K1
        .
Equivalent articles are articles that describe the same topic in different languages.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Our approach to cross-language article linking comprises two stages: candidate selection, which produces a list of candidate articles, and candidate ranking, which ranks that list.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Candidate Selection
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Since knowledge bases (KB) may contain millions of articles, comparison between all possible pairs in two knowledge bases is time-consuming and sometimes impractical.
To avoid brute-force comparison, we first select plausible candidate articles on which to focus our efforts.
To extract possible candidates, two similarity calculation methods are carried out: title matching and title similarity.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.1
         </span>
         Title Matching
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS1.p1">
         <p class="ltx_p">
          In our title matching method, we formulate candidate selection as an English-Chinese cross-language information retrieval (CLIR) problem
          [8]
          , in which every English articleâs title is treated as a query and all the articles in the Chinese encyclopedia are treated as the documents.
We employ the two main CLIR methods: query translation and document translation.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS1.p2">
         <p class="ltx_p">
          In query translation, we translate the title of every English article into Chinese and then use these translated titles as queries to retrieve articles from the Chinese encyclopedia.
In document translation, we translate the contents of the entire Chinese encyclopedia into English and then search them using the original English titles.
The top 100 results for the query-translation and the top 100 results for document-translation steps are unionized.
The resulting list contains our title-matching candidates.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS1.SSS1.p3">
         <p class="ltx_p">
          For the query- and document-translation steps, we use the Lucene search engine with similarity scores calculated by the Okapi BM25 ranking function
          [2]
          .
We separate all words in the translated and original English article titles with the “OR” operator before submission to the search engine.
For all E-C and C-E translation tasks, we use Google Translate.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          2.1.2
         </span>
         Title Similarity
        </h4>
        <div class="ltx_para" id="S2.SS1.SSS2.p1">
         <p class="ltx_p">
          In the title similarity method, every Chinese article title is represented as a vector, and each distinct character in all these titles is a dimension of all vectors.
The title of each English article is translated into Chinese and represented as a vector.
Then, cosine similarity between this vector and the vector of each Chinese title is measured as title similarity.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Candidate Ranking
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         The second stage of our approach is to score each viable candidate using a supervised learning method, and then sort all candidates in order of score from high to low as final output.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         Each article
         xi
         in KB
         K1
         can be represented by a feature vector
         𝐱i=(f1⁢(xi),f2⁢(xi),…,fn⁢(xi))
         . Also, we have
         𝐲j=(f1⁢(yj),f2⁢(yj),…,fn⁢(yj))
         for a candidate article
         yj
         in KB
         K2
         .
Then, individual feature functions
         Fk⁢(xi,yj)
         are based on the feature properties of both article
         ai
         and
         aj
         .
The top predicted corresponding article
         yj
         in the knowledge base
         K2
         for an input article
         xi
         in
         K1
         should receive a higher score than any other entity in
         K2,am∈K2,m≠j
         .
We use the support vector machine (SVM) approach to determine the probability of each pair
         (𝐱i,𝐲j)
         being equivalent.
Our SVM model’s features are described below.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S2.SS2.SSSx1">
        <h4 class="ltx_title ltx_title_subsubsection">
         Title Matching and Title Similarity Feature (Baseline)
        </h4>
        <div class="ltx_para" id="S2.SS2.SSSx1.p1">
         <p class="ltx_p">
          We use the results of title matching and title similarity from the candidate selection stage as two features for the candidate ranking stage.
The similarity values generated by title matching and title similarity are used directly as real value features in the SVM model.
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS2.SSSx2">
        <h4 class="ltx_title ltx_title_subsubsection">
         Mixed-language Topic Model Feature (MTM)
        </h4>
        <div class="ltx_para" id="S2.SS2.SSSx2.p1">
         <p class="ltx_p">
          For a linked English-Chinese article pair, the distribution of words used in each usually shows some convergence.
The two semantically corresponding articles often have many related terms, which results in clusters of specific words.
If two articles do not describe the same topic, the distribution of terms is often scattered.
          [6]
          Thus, the distribution of terms is good measurement of article similarity.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSSx2.p2">
         <p class="ltx_p">
          Because the number of all possible words is too large, we adopt a topic model to gather the words into some latent topics.
For this feature, we use the Latent Dirichlet Allocation (LDA)
          [3]
          .
LDA can be seen as a typical probabilistic approach to latent topic computation.
Each topic is represented by a distribution of words, and each word has a probability score used to measure its contribution to the topic.
To train the LDA model, the pair English and Chinese articles are concatenated into a single document.
English and Chinese terms are all regarded as terms of the same language and the LDA topic model, namely mixed-language topic model, generates both English and Chinese terms for each latent topic.
Then, for each English article and Chinese candidate pair in testing, the LDA model provides the distribution of the latent topics.
Next, we can use entropy to measure the distribution of topics.
The entropy of the estimated topic distribution of a related article is expected to be lower than that of an unrelated article. We can calculate the entropy of the distribution as a value for SVM. The entropy is defined as follows:
         </p>
         H=-∑j=1Tθd⁢j→⁢log⁡θd⁢j→
         <p class="ltx_p">
          where
          T
          is the number of latent topics,
          θd⁢j
          is the topic distribution of a given topic
          j
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS2.SSSx3">
        <h4 class="ltx_title ltx_title_subsubsection">
         Hypernym Translation Feature (HT)
        </h4>
        <div class="ltx_para" id="S2.SS2.SSSx3.p1">
         <p class="ltx_p">
          The first sentence of an encyclopedia article usually contains the title of the article.
It may also contain a hypernym that defines the category of the article.
For example, the first sentence of the “iPad” article in the English Wikipedia begins, “iPad is a line of tablet computers designed and marketed by Apple Inc
          …
          ”
In this sentence, the term “tablet computers” is the hypernym of iPad.
These extracted hypernyms can be treated as article categories.
Therefore, articles containing the same hypernym are likely to belong to the same category.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSSx3.p2">
         <p class="ltx_p">
          In this study, we only carry out title hypernym extraction on the first sentences of English articles due to the looser syntactic structure of Chinese.
To generate dependency parse trees for the sentences, we adopt the Stanford Dependency Parser.
Then, we manually designed seven patterns to extract hypernyms from the parse tree structures.
To demonstrate this idea, let us take the English article “The Hunger Games” for example.
The first sentence of this article is “The Hunger Games is a 2008 young adult novel by American writer Suzanne Collins.”
Since article titles may be named entities or compound nouns, the dependency parser may mislabel them and thus output an incorrect parse tree.
To avoid this problem, we first replace all instances of an article’s title in the first sentence with pronouns.
For example, the previous sentence is rewritten as “It is a 2008 young adult novel by American writer Suzanne Collins.”
Then, the dependency parser generates the following parse tree:
         </p>
         <img alt="" class="ltx_graphics ltx_centering" height="223" id="S2.SS2.SSSx3.p2.g1" src="P14-2096/image001.png" width="298"/>
        </div>
        <div class="ltx_para" id="S2.SS2.SSSx3.p3">
         <p class="ltx_p">
          Next, we apply our predefined syntactic patterns to extract the hypernym.
          [4]
          If any pattern matches the structure of the dependency parse tree, the hypernym can be extracted.
In the above example, the following pattern is matched:
         </p>
         <img alt="" class="ltx_graphics ltx_centering" height="90" id="S2.SS2.SSSx3.p3.g1" src="P14-2096/image002.png" width="120"/>
        </div>
        <div class="ltx_para" id="S2.SS2.SSSx3.p4">
         <p class="ltx_p">
          In this pattern, the rightmost leaf is the hypernym target.
Thus, we can extract the hypernym “novel” from the previous example.
The term “novel” is the extracted hypernym of the English article “The Hunger Games”.
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSSx3.p5">
         <p class="ltx_p">
          After extracting the hypernym of the English article, the hypernym is translated into Chinese.
The value of this feature in the SVM model is calculated as follows:
         </p>
         Fh⁢y⁢p⁢e⁢r⁢n⁢y⁢m⁢(h)=log⁡c⁢o⁢u⁢n⁢t⁢(t⁢r⁢a⁢n⁢s⁢l⁢a⁢t⁢e⁢d⁢(h))
         <p class="ltx_p">
          where
          h
          is the hypernym,
          t⁢r⁢a⁢n⁢s⁢l⁢a⁢t⁢e⁢d⁢(h)
          is the Chinese translation of the term
          h
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S2.SS2.SSSx4">
        <h4 class="ltx_title ltx_title_subsubsection">
         English Title Occurrence Feature (ETO)
        </h4>
        <div class="ltx_para" id="S2.SS2.SSSx4.p1">
         <p class="ltx_p">
          In a Baidu Baike article, the first sentence may contain a parenthetical translation of the main title.
For example, the first sentence of the Chinese article on San Francisco is “æ§éå±±ï¼San Franciscoï¼ï¼åè¯âå£å¼æè¥¿æ¯ç§âãâä¸è©å¸âã”.
We regard the appearance of the English title in the first sentence of a Baidu Baike article as a binary feature:
If the English title appears in the first sentence, the value of this feature is 1; otherwise, the value is 0.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Evalutaion
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Evaluation Dataset
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In order to evaluate the performance of cross-language article linking between English Wikiepdia and Chinese Baidu Baike, we compile an English-Chinese evaluation dataset from Wikipedia and Baidu Baike online encyclopedias.
First, our spider crawls the entire contents of English Wikipedia and Chinese Baidu Baike.
Since the two encyclopedias’ article formats differ, we copy the information in each article (title, content, category, etc.) into a standardized XML structure.
In order to generate the gold standard evaluation sets of correct English and Chinese article pairs, we automatically collect English-Chinese inter-language links from Wikipedia.
For pairs that have both English and Chinese articles, the Chinese article title is regarded as the translation of the English one.
Next, we check if there is a Chinese article in Baidu Baike with exactly the same title as the one in Chinese Wikipedia.
If so, the corresponding English Wikipedia article and the Baidu Baike article are paired in the gold standard.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         To evaluate the performance of our method on linking different types of encyclopedia articles, we compile a set containing the most popular articles.
We select the top 500 English-Chinese article pairs with the highest page view counts in Baidu Baike.
This set represents the articles people in China are most interested in.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Because our approach uses an SVM model, the data set should be split into training and test sets.
For statistical generality, each data set is randomly split 4:1 (training:test) 30 times.
The final evaluation results are calculated as the mean of the average of these 30 evaluation sets.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Evaluation Metrics
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         To measure the quality of cross-language entity linking, we use the following three metrics.
For each English article queries, ten output Baidu Baike candidates are generated in a ranked list.
To define the metrics, we use following notations:
         N
         is the number of English query;
         ri,j
         is
         j
         -th correct Chinese article for
         i
         -th English query;
         ci,k
         is
         k
         -th candiate the system output for
         i
         -th English query.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSSx1">
        <h4 class="ltx_title ltx_title_subsubsection">
         Top-
         k
         Accuracy (ACC)
        </h4>
        <div class="ltx_para" id="S3.SS2.SSSx1.p1">
         <p class="ltx_p">
          ACC measures the correctness of the first candidate in the candidate list.
          A⁢C⁢C=1
          means that all top candidates are correctly linked (i.e. they match one of the references), and
          A⁢C⁢C=0
          means that none of the top candidates is correct.
         </p>
         A⁢C⁢C=1N⁢∑i=1N{1if ∃ri,j:ri,j=ci,k0otherwise}
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSSx2">
        <h4 class="ltx_title ltx_title_subsubsection">
         Mean Reciprocal Rank (MRR)
        </h4>
        <div class="ltx_para" id="S3.SS2.SSSx2.p1">
         <p class="ltx_p">
          Traditional MRR measures any correct answer produced by the system from among the candidates.
1/MRR approximates the average rank of the correct transliteration.
An MRR closer to 1 implies that the correct answer usually appears close to the top of the n-best lists.
         </p>
         R⁢Ri={minj⁡1jif ∃ri,j,ci,k:ri,j=ci,k0otherwise}M⁢R⁢R=1N⁢∑i=1NR⁢Ri
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSSx3">
        <h4 class="ltx_title ltx_title_subsubsection">
         Recall
        </h4>
        <div class="ltx_para" id="S3.SS2.SSSx3.p1">
         <p class="ltx_p">
          Recall is the fraction of the retrieved articles that are relevant to the given query.
Recall is used to measure the performance of the candidate selection method.
If the candidate selection method can actually select the correct Chinese candidate, the recall will be high.
         </p>
         R⁢e⁢c⁢a⁢l⁢l=|relevant articles|∩|retrieved articles||relevant articles|
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Evaluation Results
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         The overall results of our method achieves 80.95% in MRR and 87.46% in recall.
Figure
         1
         shows the top-
         k
         ACC from the top 1 to 5.
These results show that our method is very effective in linking articles in English Wikipedia to those in Baidu Baike.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         In order to show the benefits of each feature used in the SVM model, we conduct a experiment to test the performance of different feature combinations.
Because title similarity of the articles is a widely used method, we choose English and Chinese title similarity as the baseline.
Then, another feature is added to each configuration until all the features have been added. Table
         2
         shows the final results of different feature combinations.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         In the results, we can observe that mix-language topic model, hypernym, and English title occurence features all noticeably improve the performance.
Combining two of these three feature has more improvement and the combination of all the features achieves the best.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Discussion
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Although our method can effectively generate cross-language links with high accuracy, some correct candidates are not ranked number one. After examining the results, we can divide errors into several categories:
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The first kind of error is due to large literal differences between the English and Chinese titles.
For example, for the English article “Nero”, our approach ranks the Chinese candidate “å°¼ç¦ç” (“King Nero”) as number one, instead of the correct answer “å°¼ç¦Â·åå³çä¹æ¯Â·å¾·é²èæ¯Â·æ¥è³æ¼å°¼åºæ¯” (the number two candidate).
The title of the correct Chinese article is the full name of the Roman Emperor Nero (Nero Claudius Drusus Germanicus).
The false positive “å°¼ç¦ç” is a historical novel about the life of the Emperor Nero.
Because of the large difference in title lengths, the value of the title similarity feature between the English article “Nero” and the corresponding Chinese article is low. Such length differences may cause the SVM model to rank the correct answer lower when the difference of other features are not so significant because the contents of the Chinese candidates are similar.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        The second error type is caused by articles that have duplicates in Baidu Baike. For example, for the English article “Jensen Ackles”, our approach generates a link to the Chinese article “Jensen” in Baidu Baike.
However, there is another Baidu article “è©¹æ£®Â·é¿åæ¯” (“Jensen Ackles”).
These two articles both describe the actor Jensen Ackles.
In this case, our approach still generates a correct link, although it is not the one in the gold standard.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        The third error type is translation errors.
For example, the English article “Raccoon” is linked to the Baidu article “ç¸” (raccoon dog), though the correct one is âæµ£çâ (raccoon).
The reason is that Google Translate provides the translation “ç¸” instead of “æµ£ç”.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
