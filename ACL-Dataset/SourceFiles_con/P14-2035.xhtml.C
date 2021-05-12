<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Resolving Lexical Ambiguity in Tensor Regression Models of Meaning.
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
       This paper provides a method for improving tensor-based compositional distributional models of meaning by the addition of an explicit disambiguation step prior to composition. In contrast with previous research where this hypothesis has been successfully tested against relatively simple compositional models, in our work we use a robust model trained with linear regression. The results we get in two experiments show the superiority of the prior disambiguation method and suggest that the effectiveness of this approach is model-independent.
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
        The provision of compositionality in distributional models of meaning, where a word is represented as a vector of co-occurrence counts with every other word in the vocabulary, offers a solution to the fact that no text corpus, regardless of its size, is capable of providing reliable co-occurrence statistics for anything but very short text constituents. By
        composing
        the vectors for the words within a sentence, we are still able to create a vectorial representation for that sentence that is very useful in a variety of natural language processing tasks, such as paraphrase detection, sentiment analysis or machine translation. Hence, given a sentence
        w1⁢w2⁢…⁢wn
        , a compositional distributional model provides a function
        f
        such that:
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       s→=f⁢(w1→,w2→,…,wn→)

(1)
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        where
        wi→
        is the distributional vector of the
        i
        th word in the sentence and
        s→
        the resulting composite sentential vector.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        An interesting question that has attracted the attention of researchers lately refers to the way in which these models affect ambiguous words; in other words, given a sentence such as “a man was waiting by the bank”, we are interested to know to what extent a composite vector can appropriately reflect the intended use of word ‘bank’ in that context, and how such a vector would differ, for example, from the vector of the sentence “a fisherman was waiting by the bank”.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Recent experimental evidence
        []
        suggests that for a number of compositional models the introduction of a disambiguation step
        prior
        to the actual compositional process results in better composite representations. In other words, the suggestion is that Eq.
        1
        should be replaced by:
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       s→=f⁢(ϕ⁢(w1→),ϕ⁢(w2→),…,ϕ⁢(wn→))

(2)
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        where the purpose of function
        ϕ
        is to return a disambiguated version of each word vector given the rest of the context (e.g. all the other words in the sentence). The composition operation, whatever that could be, is then applied on these unambiguous representations of the words, instead of the original distributional vectors.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        Until now this idea has been verified on relatively simple compositional functions, usually involving some form of element-wise operation between the word vectors, such as addition or multiplication. An exception to this is the work of Kartsaklis and Sadrzadeh
        []
        , who apply Eq.
        2
        on
        partial
        tensor-based compositional models. In a tensor-based model, relational words such as verbs and adjectives are represented by multi-linear maps; composition takes place as the application of those maps on vectors representing the arguments (usually nouns). What makes the models of the above work ‘partial’ is that the authors used simplified versions of the linear maps, projected onto spaces of order lower than that required by the theoretical framework. As a result, a certain amount of transformational power was traded off for efficiency.
       </p>
      </div>
      <div class="ltx_para" id="S1.p9">
       <p class="ltx_p">
        A potential explanation then for the effectiveness of the proposed prior disambiguation method can be sought on the limitations imposed by the compositional models under test. After all, the idea of having disambiguation emerge as a direct consequence of the compositional process, without the introduction of any explicit step, seems more natural and closer to the way the human mind resolves lexical ambiguities.
       </p>
      </div>
      <div class="ltx_para" id="S1.p10">
       <p class="ltx_p">
        The purpose of this paper is to investigate the hypothesis whether prior disambiguation is important in a pure tensor-based compositional model, where no simplifying assumptions have been made. We create such a model by using linear regression, and we explain how an explicit disambiguation step can be introduced to this model prior to composition. We then proceed by comparing the composite vectors produced by this approach with those produced by the model alone in a number of experiments. The results show a clear superiority of the priorly disambiguated models following Eq.
        2
        , confirming previous research and suggesting that the reasons behind the success of this approach are more fundamental than the form of the compositional function.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Composition in distributional models
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Compositional distributional models of meaning vary in sophistication, from simple element-wise operations between vectors such as addition and multiplication
        []
        to deep learning techniques based on neural networks
        []
        .
        Tensor-based models
        , formalized by Coecke et al.
        []
        , comprise a third class of models lying somewhere in between these two extremes. Under this setting relational words such as verbs and adjectives are represented by multi-linear maps (tensors of various orders) acting on a number of arguments. An adjective for example is a linear map
        f:N→N
        (where
        N
        is our basic vector space for nouns), which takes as input a noun and returns a modified version of it. Since every map of this sort can be represented by a matrix living in the tensor product space
        N⊗N
        , we now see that the meaning of a phrase such as ‘red car’ is given by
        r⁢e⁢d¯×c⁢a⁢r→
        , where
        r⁢e⁢d¯
        is an adjective matrix and
        ×
        indicates matrix multiplication. The same concept applies for functions of higher order, such as a transitive verb (a function of two arguments, so a tensor of order 3). For these cases, matrix multiplication generalizes to the more generic notion of
        tensor contraction
        . The meaning of a sentence such as ‘kids play games’ is computed as:
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       k⁢i⁢d⁢s→𝖳×p⁢l⁢a⁢y¯×g⁢a⁢m⁢e⁢s→

(3)
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        where
        p⁢l⁢a⁢y¯
        here is an order-3 tensor (a “cube”) and
        ×
        now represents tensor contraction. A concise introduction to compositional distributional models can be found in
        []
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Disambiguation and composition
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The idea of separating disambiguation from composition first appears in a work of Reddy et al.
        []
        , where the authors show that the introduction of an explicit disambiguation step prior to simple element-wise composition is beneficial for noun-noun compounds. Subsequent work by Kartsaklis et al.
        []
        reports very similar findings for verb-object structures, again on additive and multiplicative models. Finally, in
        []
        these experiments were extended to include tensor-based models following the categorical framework of Coecke et al.
        []
        , where again all “unambiguous” models present superior performance compared to their “ambiguous” versions.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        However, in this last work one of the dimensions of the tensors was kept empty (filled in with zeros). This simplified the calculations but also weakened the effectiveness of the multi-linear maps. If, for example, instead of using an order-3 tensor for a transitive verb, one uses some of the matrix instantiations of Kartsaklis and Sadrzadeh, Eq.
        3
        is reduced to one of the following forms:
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
        <tr class="ltx_equation ltx_align_baseline" id="S3.E4">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td ltx_align_right">
          p⁢l⁢a⁢y¯⊙(k⁢i⁢d⁢s→⊗g⁢a⁢m⁢e⁢s→), k⁢i⁢d⁢s→⊙(p⁢l⁢a⁢y¯×g⁢a⁢m⁢e⁢s→)⁢(k⁢i⁢d⁢s→𝖳×p⁢l⁢a⁢y¯)⊙g⁢a⁢m⁢e⁢s→
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
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        where symbol
        ⊙
        denotes element-wise multiplication and
        p⁢l⁢a⁢y¯
        is a matrix. Here, the model does not fully exploit the space provided by the theoretical framework (i.e. an order-3 tensor), which has two disadvantages: firstly, we lose space that could hold valuable information about the verb in this case and relational words in general; secondly, the generally non-commutative tensor contraction operation is now partly relying on element-wise multiplication, which is commutative, thus forgets (part of the) order of composition.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        In the next section we will see how to apply linear regression in order to create full tensors for verbs and use them for a compositional model that avoids these pitfalls.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Creating tensors for verbs
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The essence of any tensor-based compositional model is the way we choose to create our sentence-producing maps, i.e. the verbs. In this paper we adopt a method proposed by Baroni and Zamparelli
        []
        for building adjective matrices, which can be generally applied to any relational word. In order to create a matrix for, say, the intransitive verb ‘play’, we first collect all instances of the verb occurring with some subject in the training corpus, and then we create non-compositional holistic vectors for these elementary sentences following exactly the same methodology as if they were words. We now have a dataset with instances of the form
        ⟨s⁢u⁢b⁢ji→,s⁢u⁢b⁢ji⁢p⁢l⁢a⁢y→⟩
        (e.g. the vector of ‘kids’ paired with the holistic vector of ‘kids play’, and so on), that can be used to train a linear regression model in order to produce an appropriate matrix for verb ‘play’. The premise of a model like this is that the multiplication of the verb matrix with the vector of a new subject will produce a result that approximates the distributional behaviour of all these elementary two-word exemplars used in training.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We present examples and experiments based on this method, constructing ambiguous and disambiguated tensors of order 2 (that is, matrices) for verbs taking one argument. In principle, our method is directly applicable to tensors of higher order, following a multi-step process similar to that of Grefenstette et al.
        []
        who create order-3 tensors for transitive verbs using similar means. Instead of using subject-verb constructs as above we concentrate on elementary verb phrases of the form
        verb-object
        (e.g. ‘play football’, ‘admit student’), since in general objects comprise stronger contexts for disambiguating the usage of a verb.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experimental setting
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Our basic vector space is trained from the ukWaC corpus
        []
        , originally using as a basis the 2,000 content words with the highest frequency (but excluding a list of stop words as well as the 50 most frequent content words since they exhibit low information content). We created vectors for all content words with at least 100 occurrences in the corpus. As context we considered a 5-word window from either side of the target word, while as our weighting scheme we used local mutual information (i.e. point-wise mutual information multiplied by raw counts). This initial semantic space achieved a score of 0.77 Spearman’s
        ρ
        (and 0.71 Pearson’s
        r
        ) on the well-known benchmark dataset of Rubenstein and Goodenough
        []
        . In order to reduce the time of regression training, our vector space was normalized and projected onto a 300-dimensional space using singular value decomposition (SVD). The performance of the reduced space on the R&amp;G dataset was again very satisfying, specifically 0.73 Spearman’s
        ρ
        and 0.72 Pearson’s
        r
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        In order to create the vector space of the holistic verb phrase vectors, we first collected all instances where a verb participating in the experiments appeared at least 100 times in a verb-object relationship with some noun in the corpus. As context of a verb phrase we considered any content word that falls into a 5-word window from either side of the verb
        or
        the object. For the 68 verbs participating in our experiments, this procedure resulted in 22k verb phrases, a vector space that again was projected into 300 dimensions using SVD.
       </p>
      </div>
      <div class="ltx_paragraph" id="S5.SS0.SSS0.P1">
       <h3 class="ltx_title ltx_title_paragraph">
        Linear regression
       </h3>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p1">
        <p class="ltx_p">
         For each verb we use simple linear regression with gradient descent directly applied on matrices
         𝐗
         and
         𝐘
         , where the rows of
         𝐗
         correspond to vectors of the nouns that appear as objects for the given verb and the rows of
         𝐘
         to the holistic vectors of the corresponding verb phrases. Our objective function then becomes:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p2">
        𝐖^=arg⁢min𝐖⁢12⁢m⁢(∥𝐖𝐗𝖳-𝐘𝖳∥2+λ⁢∥𝐖∥2)

(5)
       </div>
       <div class="ltx_para" id="S5.SS0.SSS0.P1.p3">
        <p class="ltx_p">
         where
         m
         is the number of training examples and
         λ
         a regularization parameter. The matrix
         𝐖
         is used as the tensor for the specific verb.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Supervised disambiguation
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        In our first experiment we test the effectiveness of a prior disambiguation step for a tensor-based model in a “sandbox” using supervised learning. The goal is to create composite vectors for a number of elementary verb phrases of the form
        verb-object
        with and without an explicit disambiguation step, and evaluate which model approximates better the holistic vectors of these verb phrases.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        The verb phrases of our dataset are based on the 5 ambiguous verbs of Table
        1
        . Each verb has been combined with two different sets of nouns that appear in a verb-object relationship with that verb in the corpus (a total of 343 verb phrases). The nouns of each set have been manually selected in order to explicitly represent a different meaning of the verb. As an example, in the verb ‘play’ we impose the two distinct meanings of using a musical instrument and participating in a sport; so the first set of objects contains nouns such as ‘oboe’, ‘piano’, ‘guitar’, and so on, while in the second set we see nouns such as ‘football’, ’baseball” etc.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        In more detail, the creation of the dataset was done in the following way: First, all verb entries with more than one definition in the Oxford Junior Dictionary
        []
        were collected into a list. Next, a linguist (native speaker of English) annotated the semantic difference between the definitions of each verb in a scale from 1 (similar) to 5 (distinct). Only verbs with definitions exhibiting completely distinct meanings (marked with 5) were kept for the next step. For each one of these verbs, a list was constructed with all the nouns that appear at least 50 times under a verb-object relationship in the corpus with the specific verb. Then, each object in the list was manually annotated as
        exclusively
        belonging to one of the two senses; so, an object could be selected only if it was related to a single sense, but not both. For example, ‘attention’ was a valid object for the
        attract
        sense of verb ‘draw’, since it is unrelated to the
        sketch
        sense of that verb. On the other hand, ‘car’ is not an appropriate object for either sense of ‘draw’, since it could actually appear under both of them in different contexts. The verbs of Table
        1
        were the ones with the highest numbers of exemplars per sense, creating a dataset of significant size for the intended task (each holistic vector is compared with 343 composite vectors).
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        We proceed as follows: We apply linear regression in order to train verb matrices using jointly the object sets for both meanings of each verb, as well as separately—so in this latter case we get two matrices for each verb, one for each sense. For each verb phrase, we create a composite vector by matrix-multiplying the verb matrix with the vector of the specific object. Then we use 4-fold cross validation to evaluate which version of composite vectors (the one created by the ambiguous tensors or the one created by the unambiguous ones) approximates better the holistic vectors of the verb phrases in our test set. This is done by comparing each holistic vector with all the composite ones, and then evaluating the rank of the correct composite vector within the list of results.
       </p>
      </div>
      <div class="ltx_para" id="S6.p5">
       <p class="ltx_p">
        In order to get a proper mixing of objects from both senses of a verb in training and testing sets, we set the cross-validation process as follows: We first split both sets of objects in 4 parts. For each fold then, our training set is comprised by
        34
        of set #1 plus
        34
        of set #2, while the test set consists of the remaining
        14
        of set #1 plus
        14
        of set #2. The data points of the training set are presented in the learning algorithm in random order.
       </p>
      </div>
      <div class="ltx_para" id="S6.p6">
       <p class="ltx_p">
        We measure approximation in three different metrics. The first one, accuracy, is the strictest, and evaluates in how many cases the composite vector of a verb phrase is the closest one (the first one in the result list) to the corresponding holistic vector. A more relaxed and perhaps more representative method is to calculate the mean reciprocal rank (MRR), which is given by:
       </p>
      </div>
      <div class="ltx_para" id="S6.p7">
       MRR=1m⁢∑i=1m1𝑟𝑎𝑛𝑘i

(6)
      </div>
      <div class="ltx_para" id="S6.p8">
       <p class="ltx_p">
        where
        m
        is the number of objects and
        ranki
        refers to the rank of the correct composite vector for the
        i
        th object.
       </p>
      </div>
      <div class="ltx_para" id="S6.p9">
       <p class="ltx_p">
        Finally, a third way to evaluate the efficiency of each model is to simply calculate the average cosine similarity between every holistic vector and its corresponding composite vector.
The results are presented in Table
        2
        , reflecting a clear superiority (
        p&lt;0.001
        for average cosine similarity) of the prior disambiguation method for every verb and every metric.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S7">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        7
       </span>
       Unsupervised disambiguation
      </h2>
      <div class="ltx_para" id="S7.p1">
       <p class="ltx_p">
        In Section
        6
        we used a controlled procedure to collect genuinely ambiguous verbs and we trained our models from manually annotated data. In this section we briefly outline how the process of creating tensors for distinct senses of a verb can be automated, and we test this idea on a generic verb phrase similarity task.
       </p>
      </div>
      <div class="ltx_para" id="S7.p2">
       <p class="ltx_p">
        First, we use unsupervised learning in order to detect the latent senses of each verb in the corpus, following a procedure first described by Schütze
        []
        . For every occurrence of the verb, we create a vector representing the surrounding context by averaging the vectors of every other word in the same sentence. Then, we apply hierarchical agglomerative clustering (HAC) in order to cluster these context vectors, hoping that different groups of contexts will correspond to the different senses under which the word has been used in the corpus. The clustering algorithm uses Ward’s method as inter-cluster measure, and Pearson correlation for measuring the distance of vectors within a cluster. Since HAC returns a dendrogram embedding all possible groupings, we measure the quality of each partitioning by using the variance ratio criterion
        []
        and we select the partitioning that achieves the best score (so the number of senses varies from verb to verb).
       </p>
      </div>
      <div class="ltx_para" id="S7.p3">
       <p class="ltx_p">
        The next step is to classify every noun that has been used as an object with that verb to the most probable verb sense, and then use these sets of nouns as before for training tensors for the various verb senses. Being equipped with a number of sense clusters created as above for every verb, the classification of each object to a relevant sense is based on the cosine distance of the object vector from the centroids of the clusters.
        Every sense with less than 3 training exemplars is merged to the dominant sense of the verb. The union of all object sets is used for training a single unambiguous tensor for the verb. As usual, data points are presented to learning algorithm in random order. No objects in our test set are used for training.
       </p>
      </div>
      <div class="ltx_para" id="S7.p4">
       <p class="ltx_p">
        We test this system on a verb phase similarity task introduced in
        []
        . The goal is to assess the similarity between pairs of short verb phrases (verb-object constructs) and evaluate the results against human annotations. The dataset consists of 72 verb phrases, paired in three different ways to form groups of various degrees of phrase similarity—a total of 108 verb phrase pairs.
       </p>
      </div>
      <div class="ltx_para" id="S7.p5">
       <p class="ltx_p">
        The experiment has the following form: For every pair of verb phrases, we construct composite vectors and then we evaluate their cosine similarity. For the ambiguous regression model, the composition is done by matrix-multiplying the ambiguous verb matrix (learned by the union of all object sets) with the vector of the noun. For the disambiguated version, we first detect the most probable sense of the verb given the noun, again by comparing the vector of the noun with the centroids of the verb clusters; then, we matrix-multiply the corresponding unambiguous tensor created exclusively from objects that have been classified as closer to this specific sense of the verb with the noun. We also test a number of baselines: the ‘verbs-only’ model is a non-compositional baseline where only the two verbs are compared; ‘additive’ and ‘multiplicative’ compose the word vectors of each phrase by applying simple element-wise operations.
       </p>
      </div>
      <div class="ltx_para" id="S7.p6">
       <p class="ltx_p">
        The results are presented in Table
        3
        , where again the version with the prior disambiguation step shows performance superior to that of the ambiguous version. There are two interesting observations that can be made on the basis of Table
        3
        . First of all, the regression model is based on the assumption that the holistic vectors of the exemplar verb phrases follow an ideal distributional behaviour that the model aims to approximate as close as possible. The results of Table
        3
        confirm this: using just the holistic vectors of the corresponding verb phrases (no composition is involved here) returns the best correlation with human annotations (0.403), providing a proof that the holistic vectors of the verb phrases are indeed reliable representations of each verb phrase’s meaning. Next, observe that the prior disambiguation model approximates this behaviour very closely (0.399) on unseen data, with a difference
        not
        statistically significant. This is very important, since a regression model can only perform as well as its training dataset allows it; and in our case this is achieved to a very satisfactory level.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
