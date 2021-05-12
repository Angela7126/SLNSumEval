<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Linked taxonomies to capture usersʼ subjective assessments of items to facilitate accurate collaborative filtering.
   </title>
   <abstract>
    Subjective assessments (SAs), such as “elegant” and “gorgeous,” are assigned to items by users, and they are common in the reviews and tags found on many online sites. Analyzing the linked information provided by an SA assigned by a user to an item can improve the recommendation accuracy. This is because this information contains the reason why the user assigned a high or low rating value to the item. However, previous studies have failed to use SAs in an effective manner to improve the recommendation accuracy because few users rate the same items with the same SAs, which leads to the sparsity problem during collaborative filtering. To overcome this problem, we propose a novel method, called Linked Taxonomies, which links a taxonomy of items to a taxonomy of SAs to capture the userʼs interests in detail. First, our method groups the SAs assigned by users to an item into subjective classes (SCs), which are defined using a taxonomy of SAs such as those in WordNet, and they reflect the SAs/SCs assigned to an item based on their classes. Thus, our method can measure the similarity of users based on the SAs/SCs assigned to items and their classes (item classes are defined using a taxonomy of items), which overcomes the sparsity problem. Furthermore, SAs that are ineffective for accurate recommendations are excluded automatically from the taxonomy of SAs using this method. This is highly beneficial for the designers of taxonomies of SAs because it helps to ensure the production of accurate recommendations. We conducted investigations using a movie ratings/tags dataset with a taxonomy of SAs extracted from WordNet and a restaurant ratings/reviews dataset with an expert-created taxonomy of SAs, which demonstrated that our method generated more accurate recommendations than previous methods.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Many content providers such as Amazon{sup:1} and Last.fm{sup:2} employ user-generated reviews and tags of items, as well as rating values. Subjective assessments (SAs) are common in the reviews or tags of items, which represent subjective judgments such as “unforgettable” and “elegant” [1]. These SAs are valuable sources of information when analyzing why users assign high or low rating values to items. Thus, mining the SAs assigned to items could potentially improve the recommendation accuracy. If recommendation systems can utilize SAs in an effective manner, it will be possible to provide recommendations that match the desires of users.
     </paragraph>
     <paragraph>
      Most commercial recommendation systems use methods based on collaborative filtering (CF). CF is based on the intuition that users who access the same items as an active user, i.e., the user who receives the recommendation, tend to have similar interests to the active user. Several researchers have employed user-generated tags to analyze information linked to “a tag assigned by a user to an item” for improving the recommendation accuracy by CF [1], [2], [3], [4], [5]. For example, Cantador et al. analyzed the tags used by the Flickr social tagging system{sup:3} and classified the tags into the following four categories: content, context, subjective, and organizational [1]. Content tags are descriptions of objects that appear in a photo. Context tags are contextual information related to items, such as the location or the time when the photo was taken. Subjective tags are descriptive subjective judgments about items. Organizational tags are related to organizational aspects, such as self-references and personal tasks. It was found that the content information of these items was useful for improving the recommendation accuracy. However, their results also showed that subjective tags are not highly effective for improving the recommendation accuracy. We assume that the poor recommendation accuracy of SAs in previous studies was attributable to sparsity, i.e., the datasets used to measure the similarity of users were not sufficient. This is a well-known problem, which is referred to as the sparsity problem, which explains the low recommendation accuracy of CF [6].
     </paragraph>
     <paragraph>
      The sparsity problem has two causes when using SAs in CF. First, different users do not always access and assign SAs using the same items. Thus, it is difficult to measure the similarity among users based on these items, even if they use the same SAs. Second, the ratings dataset contains few items assigned with the same SAs. For example, “excellent” and “wonderful” are distinct words and previous methods have treated these words as different SAs, although they have similar meanings. Thus, users who rate items as “excellent” and those who rate the same items as “wonderful” were not treated as similar by previous methods.
     </paragraph>
     <paragraph>
      The problems mentioned above can be addressed using taxonomy-based methods, although not simultaneously [7], [8]. The first problem can be resolved using taxonomy-based methods, which use a taxonomy of items and measure the similarity of users based on the usersʼ ratings of items and the classes that include them. Thus, they can measure the similarity of users accurately, even when there are sparse item transactions. For example, in Fig. 1, a previous method solved the sparsity problem by assuming that user u, who likes the romance movie item “Talk to Her,” may also like other romance movie items such as “Brokeback Mountain” and “Youʼve Got Mail.” In Fig. 1, subjective classes (SCs) are defined using a taxonomy of SAs, such as those found in WordNet.
     </paragraph>
     <paragraph>
      However, the previous method based on a single taxonomy could not resolve the problem of the sparsity of items and that of SAs simultaneously, while still maintaining the semantic relationships expressed by the linked information of a tag assigned to an item by a user. This is because the taxonomies of items and SAs are based on different types of item classifications. We could construct a single taxonomy by merging a taxonomy of SAs with a taxonomy of items in a naive manner, as shown in Fig. 2, before applying the merged taxonomy to the previous taxonomy-based method. However, this means that we cannot analyze the semantic relationships expressed by the linked information of the tag “thrilling,” which is an SA in SC {a mathematical formula}sc1 and was assigned by user u to the item “Talk to Her” in the item class “romance.” Moreover, no solutions allow multiple taxonomies to be handled when analyzing the semantic relationships expressed by the linked information of a tag assigned by a user to an item.
     </paragraph>
     <paragraph>
      To solve the sparsity problem while retaining the semantics of the usersʼ item transactions, we propose a novel taxonomy-based method, named Linked Taxonomies, which links separate taxonomies of SAs and items. Our method groups the SAs assigned by users to items in SCs. Next, our method matches the SAs/SCs assigned to an item in its classes. This approach is based on our observation that users who assign high ratings to an item and who provide an SA, may also like items from the same class and similar SAs. For example, in Fig. 1, if user u gives a high rating to the romance movie “Talk to Her” and assigns it with the SA “thrilling,” the user is expected to prefer romance movies assigned the SA “breathtaking” by other users. This is because “thrilling” and “breathtaking” share the same SC {a mathematical formula}sc1. As a result, the Linked Taxonomies treats user v, who likes the romance movie “Brokeback Mountain” (the user gives it the SA “breathtaking”), as similar to u. Moreover, it treats user w, who likes the romance movie “Youʼve Got Mail” (the user gives it the SA “happy”), as dissimilar to u. Thus, our algorithm computes the user similarity from the SAs/SCs assigned to items and their classes.
     </paragraph>
     <paragraph>
      We provide another example to facilitate a better understanding of our approach. In Fig. 3, if user u gives a high rating to the pasta restaurant Figlio and assigns it with the SA “light”, this user is expected to prefer pasta restaurants assigned with the SA “non-fatty” by other users. This is because “light” and “non-fatty” share the same SC {a mathematical formula}sc1. As a result, Linked Taxonomies treats user v, who likes the pasta restaurant Laria (this user gives it the SA “non-fatty”), as similar to u. Moreover, it treats user w, who likes pasta restaurant Fratelli (this user gives it the SA “rich”), as dissimilar to u. Thus, our algorithm computes the user similarity from the SAs/SCs assigned to items and their classes.
     </paragraph>
     <paragraph>
      Furthermore, our linked taxonomies method automatically learns the SAs that should be included or excluded from the taxonomy. It optimizes the combination of SAs based on all possible combinations of SAs using hill-climbing search [9]. As a result, it greatly improves the accuracy of item recommendations using the optimized SA set that remains in the taxonomy of SAs. This also helps the designers of SA taxonomies to ensure that they remain practical for making accurate recommendations.
     </paragraph>
     <paragraph>
      We applied our concept to the widely used neighborhood-based model in CF. Neighborhood-based models are popular because they have several advantages, such as explaining the reasoning behind computed recommendations [10]. We consider that reasoning is important when recommending items with SAs, because they are often ambiguous and difficult to understand. Linked taxonomies can provide information about why items are recommended to users based on the relationships identified in the taxonomies of SAs and items, as well as information related to users who assign SAs in their reviews or who tag items.
     </paragraph>
     <paragraph>
      The major contributions of our study are as follows:
     </paragraph>
     <list>
      <list-item label="•">
       This is the first study to use taxonomies of items and SAs to address the sparsity problem while maintaining the semantic relationships expressed by linked information for tags assigned by users to items. Our method can measure the similarity of users based on items or SAs assigned to items by users, as well as using the item classes, which include the item and the that SCs contain the SAs. This approach overcomes the sparsity problem.
      </list-item>
      <list-item label="•">
       Our method can automatically classify SAs as effective or ineffective from a recommendation accuracy perspective. We assume that manually creating the ideal classification system for effective or ineffective SAs is a difficult task for taxonomy designers. Our method can automatically adjust the taxonomy of SAs to increase the recommendation accuracy by excluding ineffective SAs from the taxonomy. This helps the SA taxonomy designer to ensure that taxonomy remains practical, so it is capable of producing accurate recommendations for the intended service domain.
      </list-item>
      <list-item label="•">
       We conducted comprehensive investigations using a MovieLens dataset, which included the tags and ratings assigned to items by users. To prepare the taxonomy of SAs, we extracted SAs from tags and automatically grouped similar SAs into SCs by referring to WordNet. We also used data from a popular restaurant review site, Tabelog. We extracted SAs from the review descriptions and created the taxonomy of SAs based on discussions with human experts. Our experiments showed that linked taxonomies generated more accurate recommendations than previous methods, especially in terms of the highly ranked items in the recommendation list. Linked Taxonomies provides high accuracy results for multiple datasets, i.e., a tag dataset for movies and a review dataset for restaurants, so we consider that it may be applicable to datasets from diverse domains.
      </list-item>
     </list>
     <paragraph>
      This paper is organized as follows. We describe related work in the next section. We describe linked taxonomies in detail in Section 3, including how to link separate taxonomies of SAs and items to measure the similarity of users. We present evaluations of our method using datasets related to movies and restaurants in Section 4. Finally, we conclude the paper in Section 5.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section, we described previous research related to our present study.
     </paragraph>
     <section label="2.1">
      <section-title>
       Methods for extracting SAs related to items from text
      </section-title>
      <paragraph>
       Several methods have been proposed for extracting the SAs given by users to items from their tags or reviews of items. The term “subjective” has a more general meaning than “affect” and it includes the notion of subjective judgments about items [1]. A recent study extracted the SAs of items from the user-generated tags assigned to items. The parts of speech (POS)-tuple patterns were defined as: [&lt;adjective&gt;], [&lt;adjective&gt;&lt;noun&gt;], [*&lt;pronoun&gt;*&lt;adjective&gt;*], and [&lt;adverb&gt;] because these patterns reflect the subjective ratings of users. Tags were then extracted that included these patterns. In our study, “subjective” has the same meaning as that used by Cantador et al. [1].
      </paragraph>
      <paragraph>
       Previous sentiment analysis studies have conduct semantic analysis using a syntactic parser and a sentiment lexicon, such as WordNet, to extract the affective features of users from the content items in review texts [11], [12], [13]. This method can be used to extract affective features from review texts, but sentiment analysis studies have focused on the valence and abstract polarity concepts (i.e., positive or negative; bad or good), rather than assigning a text to a particular affective concept (e.g., angry or sad). WordNet-Affect [14] is an affective lexical resource, which uses a lexical repository of affective words. It is an extension of WordNet, which was produced by selecting and labeling synsets that represent affective concepts.
      </paragraph>
      <paragraph>
       WordNet concepts (synsets) are defined using fine-grained semantics. We can analyze the similarity of users in more detail using WordNet concepts compared with the abstract polarity concepts extracted by sentiment analysis. Therefore, we used the WordNet concepts defined by WordNet as SCs to measure the user similarity.{sup:4}
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Recommendation algorithms that integrate tags to improve their accuracy
      </section-title>
      <paragraph>
       We provide an overview of tag-based CF because linked taxonomies can be applied to other tags in addition to SAs. For example, we can link tags that represent the content of movies such as “Zombies” and “Vampires”, which are classified using content tags, to a movie content taxonomy to analyze the interests of users in detail. Users rate movie items and assign relevant content keywords to the same items.
      </paragraph>
      <paragraph>
       First, we provide a brief introduction to CF methods. CF methods can be classified using two approaches: memory-based CF and model-based CF. Memory-based CF assumes that each user belongs to a larger group of users with similar behavior. Indeed, this method is also referred to as user-oriented memory-based CF. An analogous method that builds item similarity groups based on the co-purchase history is known as item-oriented CF [15]. By contrast, model-based CF generates predictions using a model, which is optimized with training data. Clustering [16], [17] and Bayesian network models [1], [4], [18] are examples of the model-based approach.
      </paragraph>
      <paragraph>
       We introduce the user-oriented memory-based CF method because we use it to implement linked taxonomies. To compute the user similarity, user-oriented memory-based CF methods often use Pearsonʼs correlation coefficient [19]. If we let u be the active user, Pearsonʼs correlation coefficient measures the similarity between the active user u and user v, {a mathematical formula}S(u,v), as follows:{a mathematical formula} where {a mathematical formula}M is the set of items rated by users u and v, {a mathematical formula}ru,i is the rating value given by user u to item i, and {a mathematical formula}r¯u is the average value of the item ratings given by u. The advantage of using Pearsonʼs correlation coefficient is that it considers that different users might have different rating schemes. If {a mathematical formula}N is the set of users that are most similar to u who have rated item i, the predicted rating of u given to i, {a mathematical formula}pu,i, is obtained using the following equation:{a mathematical formula} This equation implies that CF methods recommend items based on user similarities. Therefore, the effective assessment of user similarities is important for improving the recommendation accuracy of CF methods.
      </paragraph>
      <paragraph>
       Next, we introduce tag-based CF methods. Several studies have employed the user-generated tags of items to improve the recommendation accuracy in CF [1], [2], [3], [4]. The pioneering study that applied user-generated tags to CF was performed by Tso-Sutter et al. [2]. Their method allowed tags to be incorporated into memory-based CF algorithms, such as user- and item-based CF, by reducing three-dimensional (user, item, tag) correlations to three two-dimensional correlations, before applying a fusion method to re-associate their correlations.
      </paragraph>
      <paragraph>
       Zhen et al. analyzed the tags assigned by users with a probabilistic matrix factorization (PMF) method [3]. This matrix factorization method created latent factors, which were inferred from the item ratings or tag assignment patterns, and it connected users and items, even if the users did not access the same items with the same tags. Their evaluation used the MovieLens dataset, which contains many user ratings, and they showed that their method was more accurate than a previous PMF-based method. However, their method failed to improve upon the results obtained using the method based on Pearsonʼs correlation coefficient. The latter method can provide highly accurate recommendations if many ratings are assigned to items by users, which is true of the MovieLens dataset.
      </paragraph>
      <paragraph>
       Liang et al. tried to integrate user-generated tags with an item taxonomy to improve the item recommendation accuracy [20]. They also tried to solve the problem of low information sharing, which is caused by the free-style vocabulary of tags, and the long tails of the distributions of tags assigned to items. They mapped tags onto their item classes and tried to reduce the diversity of the tags assigned by users. Our linked taxonomies link different taxonomies without mapping taxonomies onto each other, which increases the diversity of user views for items and allows user interests to be captured in detail.
      </paragraph>
      <paragraph>
       Cantador et al. analyzed the Flickr social tagging system and classified tags into the following four categories; content, context, subjective, and organizational [1]. Their proposed method constructed a graph where the nodes were tags, users, and items, and edges were placed between nodes if users assigned tags to items, were connected to other users, or they accessed items. They then performed a random walk with restart (RWR) [21] from an active user node on the graph to compute the relatedness between nodes on the graph, which generated recommendations for the active user. Their evaluation showed that the content tags of items were most useful for improving the recommendation accuracy, whereas subjective tags were not as useful. This was attributable to the sparsity of the dataset, as explained in the Introduction. Their earlier evaluation [4] used a dataset of the listening histories of music tracks from Last.fm and they found that the tag-based recommendations yielded by the RWR method had higher accuracy. However, the RWR method cannot provide highly accurate recommendations when the ratings dataset contains sparse SAs, as explained in detail in the evaluation section. Thus, the RWR method cannot handle sparse tags of items assigned by users.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Recommendation algorithms based on taxonomies
      </section-title>
      <paragraph>
       Several previous studies have explored taxonomy-based recommendation [7], [8], [22], [23], [24], [25]. Our method is an extension of these studies. Using a taxonomy of items, these methods measure the similarity of users based on class information. Thus, these methods can accurately predict user interests, even if the ratings dataset is sparse. In the pioneering research into taxonomy-based CF, Ziegler et al. [24] modeled user interests based on classes that included items rated by users and they measured the user similarity using only these classes. Their method modeled a userʼs item transaction history based on the vector of the transaction frequencies of these classes. The user similarity was also calculated based on Pearsonʼs correlation coefficient of the usersʼ vectors. In our previous study [22], we improved this earlier method [24] by computing the user similarity from both of the items transacted by users and their classes. Thus, we computed the user similarity using the structure of the classes in the taxonomy. Specifically, we computed the user similarity by investigating their similarity compared with all of the class/subclasses relationships and the class/items relationships in the taxonomy.
      </paragraph>
      <paragraph>
       Recently, several studies have used taxonomies of items to compute recommendations even when the interests of users change dynamically over time. Ziegler and McNee [25] proposed a matrix factorization model, which incorporated a rich bias model with terms that captured information from the taxonomy of items and the different temporal dynamics of music ratings. We [7] proposed a method that accurately predicted user interests by dividing historical data into discrete time periods, or epochs, before identifying the periods that best matched the current transactions of an active user. A taxonomy-based approach was used to model the transactions made by users, which was effective in identifying the similarity of transactions even when there were only a few transactions in each epoch.
      </paragraph>
      <paragraph>
       By focusing on improving the accuracy, the taxonomy-based method can increase the diversity of recommendation list entries, or present the active user with the semantic relationships between predicted items and the previous interests of the user by referring to the taxonomy. Ziegler and McNee [25] proposed an algorithm that increased the diversity of recommendation list entries. The list included items in several classes, which were defined based on the taxonomy of items. This method improves user satisfaction but the accuracy of item predictions was degraded. In our previous study [7], we detected novel items for the active user. We assessed novelty in terms of the distance between the present interests of the user and the recommended item, according to the taxonomy of items. An online evaluation showed that users tended to click on items with moderately high novelty [22]. In the present study, we also assume that it is important to present the semantic relationships between user interests and recommendation results, particularly when recommending items based on the SAs given by users, which is often difficult for users to understand. Thus, we use a taxonomy of items and a taxonomy of subjective words to explain the reasoning behind the recommendations. However, all previous studies used only a single taxonomy to measure the similarity of user interests. Thus, they lacked a mechanism for integrating several different classification approaches (taxonomies) for items, such as a taxonomy of items and a taxonomy of SAs. Thus, the diverse views of users about items have not been handled effectively in previous studies.
      </paragraph>
      <paragraph>
       The basic concept employed in this study was first presented in [26], but the present study provides the following novel insights:
      </paragraph>
      <list>
       <list-item label="•">
        We introduce related works on SA extraction from tags or reviews, and CF methods that use taxonomies of items in the Related Work section.
       </list-item>
       <list-item label="•">
        We provide detailed procedures for extracting SAs from tags or review texts and for creating taxonomies of SAs using a simple disambiguation approach based on WordNet, as well as providing many actual examples.
       </list-item>
       <list-item label="•">
        We demonstrate the high and reproducible accuracy of our proposed method based on comprehensive investigations of multiple datasets, i.e. a tag dataset of movies and a review dataset of restaurants.
       </list-item>
       <list-item label="•">
        Further validation is provided based on a comparison of linked taxonomies and the most popular taxonomy-based method [24].
       </list-item>
       <list-item label="•">
        We confirmed the effectiveness of linking separate taxonomies of SAs and items by comparing the results obtained using linked taxonomies with those using a previous method [7] with a single taxonomy that merged subjective and item taxonomies in a naive manner.
       </list-item>
      </list>
      <paragraph>
       Recently, more taxonomies have been made available on the Web, such as those in DBPedia [27], WordNet,{sup:5} and YAGO [28]. Furthermore, a method is available that labels the semantic relations between categories using methods based on connectivity in the network and lexicon-syntactic matching, thereby generating a more elaborate taxonomy [29]. Thus, we consider that recommendation methods that can link these taxonomies to analyze user interests in detail are becoming more practical.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Computing recommendations by linking separate taxonomies of SAs and items
     </section-title>
     <paragraph>
      Next, we explain our linked taxonomies method. Our method uses a taxonomy of SAs, so we start by explaining the approach used for its creation.
     </paragraph>
     <section label="3.1">
      <section-title>
       Taxonomy of SAs
      </section-title>
      <paragraph>
       First, we explain how to extract SAs from tags or reviews, before constructing a taxonomy of SAs.
      </paragraph>
      <section label="3.1.1">
       <section-title>
        Determining and extracting SAs
       </section-title>
       <paragraph>
        To determine and extract SAs from tags, we use an approach described in a previous study [1]. We remove certain stop-words (e.g., conjunctions) and determine the phrases as POS-tuples, before compare the resulting set with a set of POS-tuple patterns, which were defined for classifying SAs. We used Brill tagger [30] to assign the POS to each word in the tags. POS-tuple patterns have the following five forms according to Cantador et al. [1]: [&lt;adjective&gt;], [&lt;adjective&gt;&lt;noun&gt;], [&lt;adverb&gt;], [&lt;adverb&gt;&lt;adjective&gt;], and [*&lt;pronoun&gt;*&lt;adjective&gt;*]. We also add a [&lt;adverb&gt;&lt;adjective&gt;] pattern to the patterns used by Cantador et al. [1]. For example, the SA tag “beautiful” comprises the POS-tuple pattern [&lt;adjective&gt;], the SA tag “beautiful painting” comprises the POS-tuple pattern [&lt;adjective&gt;&lt;noun&gt;], the SA tag “well” comprises the POS-tuple pattern [&lt;adverb&gt;], the SA tag “really beautiful” comprises the POS-tuple pattern [&lt;adverb&gt;&lt;adjective&gt;], and the SA tag “it is beautiful” comprises the POS-tuple pattern [*&lt;pronoun&gt;*&lt;adjective&gt;*].
       </paragraph>
       <paragraph>
        We can use sentiment analysis methods to extract SAs from item reviews [31]. In reviews, the subject of the review is an item that has been reviewed, i.e., if we consider restaurant reviews, the subject is a restaurant. However, extracting all of the POS-tuple patterns from review texts is not a suitable method for extracting SAs. This is because several sentences describe subjects other than items reviewed. For example, the following description includes several candidate SAs that match the above POS-tuple patterns: “Cakes are elegant and charming. We discussed interesting topics while we ate them.” However, the word “interesting” is not suitable for determining SAs for restaurants whereas “elegant” and “charming” are suitable. Thus, we need to use syntactic analysis to extract SAs to analyze the relationships between the SA candidates and reviewed items, according to the following procedures: (1) We model the characteristics of items that can be assigned SAs by users. For example, the menu provided by a restaurant is a suitable characteristic if we consider restaurant reviews. (2) Next, we analyze the relationships between these characteristics and the SA candidates using a syntactic analysis tool [32]. The tool is based on a supervised learning method and it can detect the relationship between a given pair of words, which may be located in different sentences, based on centering theory, as well as conventional syntactic and word-based features. These features are organized into a tree structure and they are fed into a boosting-based classification algorithm. The algorithm is described in detail in [32]. In the example mentioned above, “interesting” is more distant from “cake” than “charming” or “elegant.” Thus, this tool judges that “interesting” is syntactically unsuitable for forming a relationship with “cake.”
       </paragraph>
      </section>
      <section label="3.1.2">
       <section-title>
        Creating a taxonomy of SAs
       </section-title>
       <paragraph>
        Content providers such as allmusic{sup:6} and Jinni{sup:7} use the term “mood,” which an affective state like emotion [33]. They construct taxonomies of mood words, which they to items. Thus, users can search for items that suit their “mood” at by selecting a mood word from the taxonomy. The SAs considered in our study include user tags or comments related to the affect of users with respect to specific items, as explained in Section 2. Thus, we can use these existing taxonomies of mood words to produce affect-based recommendations.
       </paragraph>
       <paragraph>
        If we cannot use an existing taxonomy, however, one must be created. Thus, we explain how to create a taxonomy of SAs using two possible approaches. The first approach uses WordNet and the second approach is to create the taxonomy manually. The first approach is recommended if the tags or reviews are written in English, such as our movie dataset. This is because WordNet is directed mainly toward the English language. Alternatively, we can create a taxonomy using manual procedures, such as the Japanese restaurant dataset used in our evaluation.
       </paragraph>
       <paragraph>
        In the first approach, we use a simple disambiguation method to assign polysemous words to a suitable SC. In WordNet, each word is classified into one or more synsets, or synonym sets, each of which represents a concept and they contain sets of words. Moreover, each set uses a specific name (or sense) for the concept it includes. Thus, we can use this sense as an SC. Furthermore, WordNet provides the polysemous count of a word, i.e., the number of synsets that contain the word. Given that a word can occur in several synsets (i.e., it has several senses) then some senses are typically much more common than others. WordNet quantifies this based the frequency score. In several sample texts, all of the words are semantically tagged with the corresponding synset and a count is provided, which indicates how often the word appears in a specific sense. We use this frequency number to create a taxonomy of SAs and to disambiguate polysemous SAs. If a target SA belongs more than two synsets, we extract the most frequent synset and assign the corresponding sense of the chosen synset as the SC for the target SA. Each synset for a target adverb also contains several identical adverb synsets in WordNet. We use these synset groups as SCs and classify the target adverb into the corresponding SCs. We also check the frequency of each synset assigned to the target adverb and try to disambiguate polysemous SAs when creating a taxonomy of SAs, in the same way as adjectives. Note that we classify those SAs that correspond to [&lt;adjective&gt;&lt;noun&gt;] pattern and [*&lt;pronoun&gt;*&lt;adjective&gt;*] pattern, according to the adjective in the pattern. For SAs that correspond to [&lt;adverb&gt;&lt;adjective&gt;] pattern, we classify them according to the adjective in the pattern. Based on empirical tests, we found that the usersʼ intuition about this pattern is reflected in the adjective, while the adverb reinforces the adjective. Next, we provide two examples of our disambiguation method:
       </paragraph>
       <list>
        <list-item label="•">
         The SA “beautiful,” which is an adjective, is classified into the following two synsets. One synset is beautiful(1), which has the meaning of delighting the senses or exciting intellectual or emotional admiration. The examples offered by WordNet are “a beautiful child,” “beautiful country,” “a beautiful painting,” “a beautiful theory,” and “a beautiful party.” The other synset, beautiful(2), has the meaning of highly enjoyable weather. The example given in WordNet is “what a beautiful day.” In WordNet, the frequency scores for beautiful(1) is 25 and that for beautiful(2) is less than 1. The most frequent synset is beautiful(1), so we set synset beautiful(1) as the SC for the target SA “beautiful.”
        </list-item>
        <list-item label="•">
         The SAs “well” and “good,” which are adverbs, are classified into 13 synsets. For example, well(1) has the meaning of (often used as a combining form) being in a good, proper, or satisfactory state, or to a high standard. In WordNet, the examples of both words are “the children behaved well,” “a task well done,” “the party went well,” “he slept well,” and “the baby can walk pretty well.” Another example is well(2), which has the meaning of (often used as a combining form) thoroughly or completely, and fully. In WordNet, the examples are “The problem is well understood,” “she was well informed,” “shake well before using,” “well-done beef,” “well-satisfied customers,” and “well-educated.” In WordNet, the frequency score for well(1) is 75 and that for well(2) is 30. The most frequent form is well(1), so we select the synset well(1) as the SC for the target SA “well” or “good.”
        </list-item>
       </list>
       <paragraph>
        The above disambiguation approach is quite simple. We used it because tags contain only a few words and we cannot use many of the contextual words that surround our POS-tuple patterns. Moreover, we demonstrate in the evaluation section that the accuracy can be improved by linking the taxonomies of SAs and items, although the method used to create taxonomies is very simple.
       </paragraph>
       <paragraph>
        However, the accuracy can be improved further if the tags comprise several words and if we use more sophisticated disambiguation methods [34], [35]. For example, the ambiguous word “cool” in the tag “the weather is cool” can be disambiguated by using the word “weather” near “cool.” Thus, the introduction of this method, called JIGSAW [34], [35], is useful for readers because it allows them to apply our method to their datasets. JIGSAW takes an input document {a mathematical formula}d={w1,w2,…,wh} and returns a list of WordNet synsets {a mathematical formula}X={s1,s2,…,sk}. Each synset s is obtained by disambiguating the target word w based on the information obtained from WordNet regarding the contextual words, and a few immediately surrounding words, of w. The context of the target word w is defined as a window of n words to the left and another n words to the right, giving a total of 2n surrounding words. Next, JIGSAW disambiguates word w using the contextual information. This algorithm was described in previous studies [34], [35].
       </paragraph>
       <paragraph>
        If we cannot use an existing taxonomy or refer to a thesaurus such as WordNet, we must create a taxonomy of SAs manually. Thus, we explain the procedure used to create a taxonomy of SAs based on discussions with several human experts:
       </paragraph>
       <list>
        <list-item label="•">
         The classification of an SA in one or more SCs is accepted if all of the experts are in agreement.
        </list-item>
        <list-item label="•">
         If there is no candidate SC for SA classification, the experts create an SC.
        </list-item>
        <list-item label="•">
         However, this classification is accepted only if two or more experts agree.
        </list-item>
       </list>
       <paragraph>
        This approach allows us to create a taxonomy of SAs, which reflects an unambiguous classification.
       </paragraph>
      </section>
     </section>
     <section label="3.2">
      <section-title>
       Modeling user interests
      </section-title>
      <paragraph>
       We now consider modeling user interests by linking separate taxonomies of SAs and items. Our model of user interests is based on the observation that users who assign a high rating to an item with an SA, may also like items from the same class and similar SAs. Thus, we model user interests with the following vectors:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}r→u is the vector of the ratings of items given by user u, i.e., each element in {a mathematical formula}r→u corresponds to the rating value assigned to each item by user u.
       </list-item>
       <list-item label="•">
        {a mathematical formula}a→u,i is the vector of SAs assigned by user u to item i. Each element in {a mathematical formula}a→u,i corresponds to the frequency of each SA assigned by user u to item i.
       </list-item>
       <list-item label="•">
        {a mathematical formula}c→u,i is the vector of SCs assigned to item i by user u. Each element in {a mathematical formula}c→u,i corresponds to the frequency of each SC assigned by user u to item i. For example, the element that corresponds to SC sc, {a mathematical formula}c→u,i(sc), is computed by considering the SA s given to SC sc if sc includes s, i.e., {a mathematical formula}c→u,i(sc)=∑s∈sca→u,i(s).
       </list-item>
       <list-item label="•">
        {a mathematical formula}a→u,c is the vector of SAs assigned by user u to the item class c. Each element of this vector denotes the assignment frequency of each SA given by user u to the item class c. If we denote {a mathematical formula}I(c) as the item set where the members have the item class c as an ancestor, {a mathematical formula}a→u,c is computed by {a mathematical formula}∑i∈I(c)a→u,i.
       </list-item>
       <list-item label="•">
        {a mathematical formula}c→u,c is the vector of the SCs assigned to item class c by user u. Each element of this vector denotes the assignment frequency of each SC given by user u to the item class c. {a mathematical formula}c→u,c is computed by {a mathematical formula}∑i∈I(c)c→u,i.
       </list-item>
      </list>
     </section>
     <section label="3.3">
      <section-title>
       Measuring the similarity of users
      </section-title>
      <paragraph>
       We assume that the interests of users are similar if they rate the same items using the same SAs. In addition, we try to measure the similarity of user interests, even if the users rate few items with SAs that are similar to other words. Thus, Linked Taxonomies measures the similarity of user interests based on the SAs and the SCs assigned to transacted items. The process of our algorithm is shown below:
      </paragraph>
      <list>
       <list-item label="1.">
        First, we measure the similarity of users based on the SAs given to item i, {a mathematical formula}Si(u,v), by summing the cosine similarity of {a mathematical formula}a→u,i and {a mathematical formula}a→v,i and that of {a mathematical formula}c→u,i and {a mathematical formula}c→v,i as follows:{a mathematical formula} where {a mathematical formula}cos(x→,y→) is the cosine similarity of vector {a mathematical formula}x→ and {a mathematical formula}y→.
       </list-item>
       <list-item label="2.">
        Next, we compute the similarity of users based on the SAs given to each item class, {a mathematical formula}Sc(u,v), by summing the cosine similarity of {a mathematical formula}a→u,c and {a mathematical formula}a→v,c and that of {a mathematical formula}c→u,c and {a mathematical formula}c→v,c as follows:{a mathematical formula}In this case, the denominator of the equation is based on the concept described by [23], i.e., it has the effect of avoiding strong biases for {a mathematical formula}Sc(u,v) if item class c has many items as descendants. This is because classes with many items have a high possibility of being associated with many users. As a result, many users are computed as highly similar because of these classes, which reduces the accuracy. Thus, the denominator is required to avoid such biases.
       </list-item>
       <list-item label="3.">
        We measure the similarity of users by summing the similarity of users based on the SAs given to each item and each item class. Function {a mathematical formula}f(x) transforms the distribution of x into a normal distribution {a mathematical formula}N(0,1). This similarity of users for SAs, {a mathematical formula}Ss(u,v), is computed according to the following equation:{a mathematical formula} where {a mathematical formula}M is the set of items rated by users u and v, and {a mathematical formula}C denotes a class set (except for the “root” class) in the taxonomy of items. Normalization is necessary because we want to harmonize the impact of the similarity of users for the SAs given to each item and to each item class. If normalization is not applied, {a mathematical formula}SC(u,v) is typically greater than {a mathematical formula}SI(u,v) because the number of classes shared by users is much greater than that of items.
       </list-item>
       <list-item label="4.">
        We also measure the similarity of users based on their ratings, {a mathematical formula}Sr(u,v), using Pearsonʼs correlation coefficient, i.e., Eq. (1) in Section 2.2.
       </list-item>
       <list-item label="5.">
        We then sum the normalized similarities to compute the similarity of users:{a mathematical formula}
       </list-item>
       <list-item label="6.">
        If {a mathematical formula}N is the set of users that are most similar to u, according to {a mathematical formula}S(u,v) computed using Eq. (6), the predicted rating of u for item i, {a mathematical formula}pu,i, is obtained by the following equation:{a mathematical formula}
       </list-item>
      </list>
      <paragraph>
       The approach described above measures the similarity of users based on linked taxonomies rather than a single taxonomy of items, which is the case in previous taxonomy-based method [7], [24]. Thus, our method overcomes the sparsity problem, that occurs when applying SAs in CF, by utilizing the SAs/SCs assigned by users to items and their item classes.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Optimizing the SA set to improve the accuracy
      </section-title>
      <paragraph>
       When linking a taxonomy of SAs to a taxonomy of items, it is important to determine the SAs that are useful for measuring the similarity of users to improve recommendations. Linked Taxonomies is designed to accurately recommend items that are ranked highly in the recommendation list by optimizing the SA set, which is based on maximizing the average precision (AP) when predicting user interests. AP is a widely used measure in information retrieval studies [36]. Let the number of ranked items be k, the number of correct answers among the top-j ranked items be {a mathematical formula}Nj, and the number of all correct answers be D (which are defined as the items that the user assign ratings in the prediction dataset), where AP is defined as follows:{a mathematical formula} where {a mathematical formula}relevant(j) is a function that returns 1 if the j-th ranked item is one of the correct answers, but 0 otherwise.
      </paragraph>
      <paragraph>
       Optimizing the combination of SAs based on all possible combinations of SAs is defined as the combinatorial optimization that finds the optimized SA set {a mathematical formula}S that maximizes AP subject to {a mathematical formula}s∈S. Because this is an NP-hard problem, we use hill-climbing search [9] to optimize the SA set that maximizes AP when predicting user interests. Algorithm 1 describes our optimization algorithm:
      </paragraph>
      <paragraph>
       First, we initialize the SA set, {a mathematical formula}S, to extract all of the SAs from the reviews/tags, and we select the candidate SA, s, one by one from {a mathematical formula}S. We then remove s from {a mathematical formula}S and compute the recommendations for users, while evaluating AP {a mathematical formula}As at the same time. We add the removed SA s to {a mathematical formula}S and select another candidate SA from {a mathematical formula}S. After checking all of the candidates in {a mathematical formula}S, we determines that SA s has to be removed from {a mathematical formula}S if {a mathematical formula}maxs∈S{As}&gt;A. We iterate this removal process using the remaining SA set until the AP exhibits no further improvement.
      </paragraph>
      <paragraph>
       Note that hill-climbing is useful for finding local optima, but it is not guaranteed to find the best possible combination from all possible combinations. However, this approach is effective for improving recommendation accuracy, as demonstrated in the next section. Furthermore, this method is extremely useful for helping human experts to maintain the taxonomy of SAs. Clearly, it would be difficult to manually classify whether SAs are effective or not. Fortunately, our method automatically optimizes the generated taxonomy of SAs.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Evaluation
     </section-title>
     <paragraph>
      The main goal of this experimental evaluation was to show that our proposed method solves the sparsity problem, thereby improving the recommendation accuracy.
     </paragraph>
     <section label="4.1">
      <section-title>
       Datasets
      </section-title>
      <paragraph>
       We used the movie dataset provided by MovieLens{sup:8} and a restaurant dataset to evaluate linked taxonomies. The movie dataset included user-generated tags and the ratings for items, and a taxonomy of SAs was created automatically by referring to WordNet. The restaurant dataset was obtained from a popular Japanese restaurant review site, Tabelog, and the taxonomy of SAs was created by human experts who analyzed the SAs extracted from reviews. The use of two different datasets with different SA taxonomies (one was created automatically from WordNet and the other was created manually) allowed us to validate the reproducibility of our methods.
      </paragraph>
      <section label="4.1.1">
       <section-title>
        Movie dataset with WordNet
       </section-title>
       <paragraph>
        We used data from MovieLens, a well-known online movie recommendation system, to evaluate the performance of the proposed method. Table 1 summarizes the characteristics of the movie data. This dataset contains a huge volume of tags and the ratings assigned by users to items. The maximum user rating was 5 and the minimum rating was 0.5. A low item rating indicated little interest in that item. We used these data because, as far as we know, this is the only publicly available dataset that contains both tagging and rating information. Note that we did not use the standard training-test set split provided for MovieLens.{sup:9} This is because there are few ratings with tags in the original MovieLens dataset. Indeed, only about 1% of all the ratings have tags. Moreover, only about 0.2% of all the ratings have SAs. To avoid tag datasets that were too sparse, we focused on users whose tagging history contained at least three distinct SAs. We have made the taxonomy of SAs available online,{sup:10} so readers can use it to conduct their own studies.
       </paragraph>
       <paragraph>
        First, we extracted the SAs using the procedures described in Section 3.1.1, which yielded 19 481 SAs from about 95 580 tags. It should be emphasized that our method is not applicable in situations where only rating information is available, i.e., there is no information about SAs. For those users without any SAs, the subjective-based similarities between them and the other users were 0, so the last term in Eq. (6) had no effect on those users. Thus, the recommendation results for those users without subjective information were similar to the results obtained using Pearsonʼs correlation coefficient-based methods. The dataset comprised 128 511 ratings made by 231 anonymous users for 7426 movies. The average number of ratings assigned to each item was 17.3.
       </paragraph>
       <paragraph>
        This taxonomy of movie items was simple, i.e., it only had 19 genres as classes, and only two hierarchies: the root class, “Movie,” and subclasses. The taxonomy of SAs for movie tags was constructed according to the procedure described in Section 3.1.2. We used Java WordNet Library (JWNL){sup:11} to analyze the WordNet thesaurus. This yielded a taxonomy of SAs that classified 1808 SAs into 716 SCs. Table 2 shows an example of the SCs created. Note that our evaluation only used SA tags because our investigation focused on the effects of SA tags in enhancing the recommendation accuracy.
       </paragraph>
       <paragraph>
        In our movie dataset, the users rated 556.3 items on average, but they assigned SAs to only 84.3 items. The total number of user assignments of SA tags was 19 474. Thus, this dataset contained sparse SA assignments to items compared with the user ratings of items. It would be difficult for a conventional approach to improve the recommendation accuracy using such sparse SAs.
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        Restaurant dataset with a manually created subjective taxonomy
       </section-title>
       <paragraph>
        We also used a dataset obtained from the popular Japanese restaurant website Tabelog to evaluate the performance of the proposed method. Table 3 summarizes the characteristics of our restaurant data. We extracted 262 137 reviews made by 2879 users for 44,321 restaurants (items) to create the evaluation dataset. We only included users whose reviews contained at least three distinct SAs (which also applied to the movie dataset). The taxonomy of restaurants was quite deep, i.e., it included 318 genres as item classes and four or five hierarchy levels. For example, the end classes of this taxonomy had genres such as “Wine bar” and “Beer garden.” The maximum user rating was 5 and the minimum rating was 0. A low item rating indicated little interest in that item.
       </paragraph>
       <paragraph>
        The SAs were extracted from the restaurant review descriptions according to the following procedures. First, we analyzed the dependency between phrases and restaurant menus in each sentence of the reviews using a Japanese dependency extraction parser, as described in Section 3.1.2[32]. The menu dataset contained 1810 menus, which were provided by Life Scape Marketing Corporation.{sup:12} The phrases were classified automatically into SAs. First, we removed some stop-words (e.g., conjunctions) and determined the phrases as POS tuples, before comparing each with a set of POS-tuple patterns that was defined for classifying SAs. The POS-tuple patterns had the following two forms; [&lt;adjective&gt;], [&lt;adjective&gt;&lt;noun&gt;].{sup:13} Next, three human experts had a discussion and they classified the SAs into two or more SCs, according to the procedure described in Section 3.1.2. Thus, we generated 44 SCs with 283 SAs. Examples of the SCs created are shown in Table 4.{sup:14}
       </paragraph>
       <paragraph>
        In our restaurant dataset, the users rated 90.9 items on average, but they only assigned SAs to 16.3 items. The total number of user-assigned SA tags was 46 928. Thus, this dataset contained sparse SAs assigned to items compared with the user ratings of items. It would be very difficult for a conventional approach to utilize these sparse SAs to improve the recommendation accuracy.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Comparison of methods
      </section-title>
      <paragraph>
       We compared our method, Linked Taxonomies, with the following methods:
      </paragraph>
      <list>
       <list-item label="•">
        Pearsonʼs correlation coefficient (Pearson): the similarity of users was measured using Pearsonʼs correlation coefficient, which is explained in Section 2.2. The predicted values of items were computed using Eq. (1) and Eq. (2).
       </list-item>
       <list-item label="•">
        Method using RWR (RWR): this method was proposed by Cantador et al. [1]. This is the most recent study to investigate the usefulness of subjective tags for enhancing the recommendation accuracy, which is why we selected this method for the comparison. This method creates a graph where the nodes are users, items, and tags, and RWR is performed on the graph to calculate the recommendations. The weights of the edges between a user and a tag, between an item and a tag, and between a tag and a tag were computed using the same method as Cantador et al. [1]. The weights of the edges from a user to items were proportional to the rating values assigned to items by the user so the total sum of the weights for each user was equal to one, as described previously [5]. Clements et al. [5] describe how even low ratings can be used to retrieve relevant items. Moreover, the weights of the edges from items to users were proportional to the rating values assigned to items by users so the total sum of the weights for each item was equal to one. Our dataset lacked social connections among users, so there were no edges between users. The restart parameter of RWR was set to 0.8 because this value gave the best recommendation accuracy.
       </list-item>
       <list-item label="•">
        The method proposed by Nakatsuji (Nakatsuji): this method was proposed by Nakatsuji et al. [7] and it is the most accurate of the existing taxonomy-based methods. This method computes the user similarity based on the ratings assigned by users to items and classes in a single taxonomy of items.
       </list-item>
       <list-item label="•">
        The method proposed by Ziegler (Ziegler): the user similarity was measured using the method proposed by Ziegler et al. [24]. This is the best-known taxonomy-based method for item recommendations. We set the parameter χ in this method to an appropriate value for each dataset to yield the most accurate results.
       </list-item>
      </list>
     </section>
     <section label="4.3">
      <section-title>
       Methodology
      </section-title>
      <paragraph>
       We divided the dataset of ratings per user into two halves, a training dataset and a predicted dataset, as follows: (1) We extracted the ratings with tags for each user. (2) Next, we randomly divided the ratings per user into two datasets: a training dataset and a predicted dataset. (3) We also selected the ratings without tags for each user. (4) We randomly divided the ratings per user into two datasets and incorporated the divided dataset into the training dataset and the predicted dataset, which were computed using procedure (2). (5) Finally, we combined the per user training dataset and the per user predicted dataset.
      </paragraph>
      <paragraph>
       We then used the training dataset to measure the similarity of users. We computed the predicted values of the items for each user by adding the similarities of the users to Eq. (2). In the evaluations, we exchanged the training dataset with the predicted dataset and investigated the reproducibility of the results. We used a twofold cross-validation strategy and confirmed that the results had the same tendencies in both evaluations. The results described later are the average values of these two evaluations. Note that our evaluations treated the ratings of items in the predicted dataset as relevant, whereas the unrated items were considered irrelevant. This is because we could not know whether the unrated items were relevant for the user if the predicted dataset had no ratings for these items.
      </paragraph>
      <paragraph>
       We used the AP and mean average precision (MAP) to evaluate the recommendation lists produced, which were also used in previous studies [1], [4]. AP was formulated using Eq. (8) and MAP was computed using Eq. (8), where k was set to the total number of items in the list.
      </paragraph>
      <paragraph>
       We selected AP and MAP to evaluate the recommendation accuracy because we wanted to obtain a ranked list of the items that each user had not rated yet but was likely to rate highly. This problem definition was used in several previous studies [5], [37], [38] because it is more natural, particularly in common scenarios with a very large number of items, most of which are unknown to the user. We also report the number of relevant items in the list, together with the MAP. We denote the number of relevant items as RelNum in this study. RelNum is useful for investigating how many of the correct answers produced by each algorithm can be found in the recommendation list.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Parameter settings
      </section-title>
      <paragraph>
       Next, we describe the parameter settings used in our evaluations. The parameters had the same values for both datasets (movie and restaurant). We set the total number of items in the list for the MAP computation for each user as 200 because we assumed that the high ranked items would be more important. Next, we checked the AP values to identify the top-k ranked items. We set k to 20, 50, 70, and 100 in our evaluations, and the corresponding results are denoted as AP@20, AP@50, AP@70, and AP@100. As a result, we found that Linked Taxonomies had the highest accuracy among all of the methods with all numbers of users, i.e., {a mathematical formula}N in Eq. (2): 10, 20, and, 30. {a mathematical formula}N was the set of users that were most similar to each active user. In the following, we describe the results obtained where {a mathematical formula}N=20, although the results showed that our method always had the highest accuracy based on the high ranked items in the recommendation list. Table 5 shows the accuracy when we changed the number of users {a mathematical formula}N.
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Accuracy
      </section-title>
      <paragraph>
       First, we describe the accuracy of the methods, before discussing the effects of SA set optimization. We evaluated the accuracy of Linked Taxonomies by changing the number of items recommended to the user. The RelNum, MAP, and AP@k results for the movie dataset are shown in Table 6 while those for the restaurant dataset are shown in Table 7. The results presented exclude ineffective SAs. The results obtained with both datasets confirmed that our method yielded better AP@K values than the baseline method, Pearson, with a statistically significant difference at {a mathematical formula}p&lt;0.05 (t-test). Our method also yielded better RelNum, MAP, and AP@K values than the other methods in all cases. In particular, the MAP for the restaurant dataset was better than that achieved using Pearson, with a statistically significant difference at {a mathematical formula}p&lt;0.05 (t-test). This indicates that Linked Taxonomies, which links the taxonomies of SAs and items, can capture the user interests in more detail and provide more accurate recommendations, especially for highly ranked items. Users tend to look only at the high ranked items in recommendation list. Thus, these results suggest that Linked Taxonomies may be a useful method in practical applications.
      </paragraph>
      <paragraph>
       Linked Taxonomies was also more accurate than the RWR method. The RWR method had a low recommendation accuracy because it does not use a taxonomy of SAs or a taxonomy of items, so it is affected severely by the sparsity problem when handling SAs. The results obtained using RWR with the movie dataset indicate that the performance was better than that with the restaurant dataset, especially when there were many items in the recommendation list. This suggests that the RWR method could connect similar users more efficiently using SAs because the movie dataset had more SAs and less sparsity than the restaurant dataset. However, it was less accurate than Linked Taxonomies.
      </paragraph>
      <paragraph>
       Linked Taxonomies was also more accurate than the methods of Nakatsuji and Ziegler because they assessed user interests based only a single taxonomy. Thus, they simply reflect the user ratings of items in their classes and they do not utilize the SAs users give to items. Linked Taxonomies assesses user interests in more detail by linking taxonomies of items and SAs, which generates much more accurate recommendations. Note that the method of Ziegler was more accurate than the Pearson method using the dataset in their original paper [24]. However, the original dataset was sparser than our dataset. In the original dataset, the users provided 5.24 item ratings on average. Compared with the corresponding values in the original dataset, each user in the movie dataset rated 106 times more items on average, and each user in the restaurant dataset rated 17 times more items on average. The original taxonomy-based method was useful when the ratings dataset was sparse. The restaurant dataset was sparser than the movie dataset, so the Ziegler method performed better with the restaurant dataset. For example, it performed better than the previous tag-based method with PMF [3] described in the related work section. Moreover, the Pearson method performed better when the dataset was dense, like the MovieLens dataset. By contrast, Linked Taxonomies linked the taxonomies to measure the similarity of users in more detail. The method of Nakatsuji is useful for solving the rating prediction problem but it is not as useful for the item ranking problem. This is because the method of Nakatsuji recommends highly novel items in classes that the user has not yet transacted and it maintains a high rating prediction accuracy. Normally, these novel items are not ranked highly in the recommendation list. Thus, this method is focused on the rating prediction accuracy rather than item ranking prediction.
      </paragraph>
      <paragraph>
       Next, we investigated the effects of using subjective classes on the item recommendations. Thus, we compared Linked Taxonomies with a method that did not use a taxonomy of SAs.{sup:15} We also investigated the effects of using item classes on the item recommendations. Thus, we compared Linked Taxonomies with a method that used only a taxonomy of SAs.{sup:16} The results for the movie dataset are shown in Table 8 while those for the restaurant dataset are shown in Table 9. We denote the method without a taxonomy of SAs as Without subjective classes and the method with only a taxonomy of SAs as Without item classes. The results show that Linked Taxonomies had the highest accuracy in all cases for all the numbers of items in the recommendation list examined. Linked Taxonomies improved the recommendation accuracy by measuring the similarity of users using the SAs/SCs assigned to items and those given to item classes.
      </paragraph>
      <paragraph>
       Note that the sparsity problem occurs often in real recommendation applications, such as our evaluation datasets acquired from real applications. Thus, these results suggest that Linked Taxonomies overcomes the sparsity problem that occurs when using SAs. Furthermore, the movie dataset was sparser than the restaurant dataset, i.e., compare “the average number of ratings assigned to items by users” to “the average number of ratings with SAs assigned to items by users” in Table 1, Table 3. Linked Taxonomies also improved MAP for the restaurant dataset compared with the movie dataset. Based on these results, we can see that Linked Taxonomies improved the accuracy more when the dataset was sparser.
      </paragraph>
      <paragraph>
       Finally, we compared Linked Taxonomies with a single taxonomy that merged items and SAs. The single taxonomy was created by merging a taxonomy of items and a taxonomy of SAs based on the root class, as shown in Fig. 2. To handle items and SAs in a single taxonomy, we attached an SA to an item, even if just one user assigned an SA to the item. In other words, if a user rated an item with an SA, then another user who rated the same item was assumed to have assigned the same SA even if they did not assign SAs to that item. For example, in Fig. 2, if some users assigned the SA “thrilling” to the item “Talk to Her”, the item “Talk to Her” was classified under the class “thrilling.” Another user who rated the item “Talk to Her” was assumed to have assigned the same SA “thrilling,” although they did not assign SAs to that item. Next, we measured the similarity of users with the Nakatsuji method based on the merged taxonomy. The results for the movie dataset and the restaurant dataset are shown in Table 10 and Table 11, respectively. The results show that by linking the two separate taxonomies in an efficient manner, Linked Taxonomies improved the accuracy much more than the method that simply merged the two different taxonomies into one. This means that Linked Taxonomies can integrate different classification approaches (taxonomies) for items, i.e., a taxonomy of items and a taxonomy of SAs in the present evaluation.
      </paragraph>
     </section>
     <section label="4.6">
      <section-title>
       Optimized SA set
      </section-title>
      <paragraph>
       Next, we investigated the effect of optimizing the SA set {a mathematical formula}S. We determined the SAs that were effective, i.e., the recommendation accuracy was degraded greatly when we removed them from {a mathematical formula}S, and those that were ineffective, i.e., their removal from {a mathematical formula}S significantly enhanced the accuracy. Table 12 and Table 13 show typical examples of effective and ineffective SAs for the movie dataset and restaurant dataset, respectively.
      </paragraph>
      <paragraph>
       First, we analyzed the accuracy when we did not exclude ineffective SAs from the taxonomy of SAs. Table 14 and Table 15 show the accuracy when ineffective SAs were included in the SA set for the movie dataset and the restaurant dataset, respectively. These results show that the accuracy was improved greatly by identifying and excluding ineffective SAs from the SA set. However, most of the results in Table 14 and Table 15 indicate that higher accuracy was possible even when the ineffective SAs were retained, compared with that using the Pearson method (see Table 6 and Table 7).
      </paragraph>
      <paragraph>
       A comparison of the effective and ineffective SAs in Table 12 and Table 13 shows that taxonomy designers would have great difficulty creating a framework for the manual classification of SAs as effective or ineffective. Fortunately, Linked Taxonomies can automatically optimize the taxonomy of SAs to increase the recommendation accuracy by excluding ineffective SAs from the taxonomy. Thus, our method is very useful for SA taxonomy designers.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>