<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Semantic Parsing for Single-Relation Question Answering.
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
       We develop a semantic parsing framework based on semantic similarity for open domain question answering (QA).
We focus on single-relation questions and decompose each question into an entity mention and a relation pattern.
Using convolutional neural network models, we measure the similarity of entity mentions with entities in the knowledge base (KB) and the similarity of relation patterns and relations in the KB.
We score relational triples in the KB using these measures and select the top scoring relational triple to answer the question.
When evaluated on an open-domain QA task, our method achieves higher precision across different recall points compared to the previous approach, and can improve F
       1
       by 7 points.
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
        Open-domain question answering (QA) is an important and yet challenging problem
that remains largely unsolved. In this paper, we focus on answering single-relation factual questions, which are the most common type of question
observed in various community QA sites
        [7]
        , as well as in search query logs. We assumed such questions are answerable by issuing a single-relation query that consists of the relation and an argument entity, against a knowledge base (KB). Example questions of this type include: “
        Who is the CEO of Tesla?
        ” and “
        Who founded Paypal?
        ”
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        While single-relation questions are easier to handle than questions with more complex and multiple relations, such as “
        When was the child of the former Secretary of State in Obama’s administration born?
        ”, single-relation questions are still far from completely solved.
Even in this restricted domain there are a large number of paraphrases of the same question. That is to say that the problem of mapping from a question to a particular relation and entity in the KB is non-trivial.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we propose a semantic parsing framework tailored to single-relation questions. At the core of our approach is a novel semantic
similarity model using convolutional neural networks. Leveraging the question paraphrase data mined from the WikiAnswers corpus by
        Fader et al. (2013)
        , we train two semantic similarity models: one links a
mention from the question to an entity in the KB and the other maps a relation pattern to a relation. The answer to the question can thus
be derived by finding the relation–entity triple
        r⁢(e1,e2)
        in the KB and returning the entity not mentioned in the question.
By using a general semantic similarity model to match patterns and relations, as well as mentions and entities, our system outperforms the existing rule learning system,
        Paralex
        [7]
        , with higher precision at all the recall points when answering the questions in the same test set. The highest achievable F
        1
        score of our system is 0.61, versus 0.54 of
        Paralex
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The rest of the paper is structured as follows. We first survey related work in Sec.
        2
        , followed by the problem definition and the high-level description of our approach in Sec.
        3
        . Sec.
        4
        details our semantic models and Sec.
        5
        shows the experimental results. Finally, Sec.
        6
        concludes the paper.
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
        Semantic parsing of questions, which maps natural language questions to database queries, is a critical component for KB-supported QA.
An early example of this research is the semantic parser for answering geography-related questions, learned using inductive logic programming
        [18]
        . Research in this line originally used small, domain-specific databases, such as GeoQuery
        [16, 10]
        . Very recently, researchers have started developing semantic parsers for large, general-domain knowledge bases like Freebase and DBpedia
        [3, 1, 9]
        .
Despite significant progress, the problem remains challenging. Most methods have not yet been scaled to large KBs that can support general open-domain QA.
In contrast,
        Fader et al. (2013)
        proposed the
        Paralex
        system, which targets answering single-relation questions using an automatically created knowledge base, ReVerb
        [6]
        . By applying simple seed templates to the KB and by leveraging community-authored paraphrases of questions from WikiAnswers, they successfully demonstrated a high-quality lexicon of pattern-matching rules can be learned for this restricted form of semantic parsing.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        The other line of work related to our approach is continuous representations for semantic similarity,
which has a long history and is still an active research topic.
In information retrieval,
TF-IDF vectors
        [13]
        , latent semantic analysis
        [5]
        and topic models
        [2]
        take the bag-of-words approach, which
captures well the contextual information for documents, but is often too coarse-grained to be effective for sentences.
In a separate line of research, deep learning based techniques have been proposed for semantic understanding
        [11, 8, 15, 12, 17]
        .
We adapt the work of
        [8, 15]
        for measuring the semantic distance between a question and relational triples in the KB as the core component of our semantic parsing approach.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Problem Definition &amp; Approach
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this paper, we focus on using a knowledge base to answer
        single-relation
        questions.
A single-relation question is defined as a question composed of an entity mention and a binary relation
description, where the answer to this question would be an entity that has the relation with
the given entity. An example of a single-relation question is “
        When were DVD players invented?
        ”
The entity is
        dvd-player
        and the relation is
        be-invent-in
        . The answer can thus be
described as the following lambda expression:
       </p>
       λ⁢x.be-invent-in⁢(dvd-player,x)
       <p class="ltx_p">
        A knowledge base in this work can be simply viewed as a collection of
binary relation instances in the form of
        r⁢(e1,e2)
        , where
        r
        is the relation and
        e1
        and
        e2
        are the first and second entity arguments.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Single-relation questions are perhaps the easiest form of questions that can directly be
answered by a knowledge base. If the mapping of the relation and entity in the question can be
correctly resolved, then the answer can be derived by a simple table lookup, assuming that
the fact exists in the KB. However, due to the large number of paraphrases of the same question,
identifying the mapping accurately remains a difficult problem.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Our approach in this work can be viewed as a simple semantic parser tailored to
single-relation questions, powered by advanced semantic similarity models
to handle the paraphrase issue. Given a question, we first separate it into two disjoint parts:
the
        entity mention
        and the
        relation pattern
        . The entity mention is a subsequence
of consecutive words in the question, where the relation pattern is the question where the mention
is substituted by a special symbol. The mapping between the pattern and the relation in
the KB, as well as the mapping between the mention and the entity are determined by
corresponding semantic similarity models. The high-level approach can be viewed as a very simple context-free
grammar, which is shown in Figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The probability of the rule in (
        1
        ) is 1 since we assume the input is a single-relation question.
For the exact decomposition of the question (e.g., (
        2
        ), (
        3
        )),
we simply enumerate all combinations and assign equal probabilities to them. The performance of this approach
depends mainly on whether the relation pattern and entity mention can be resolved correctly (e.g., (
        1
        ),
(
        1
        )). To determine the probabilities of such mappings, we propose using a semantic similarity model based
on convolutional neural networks, which is the technical focus in this paper.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Convolutional Neural Network based Semantic Model
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Following
        [4, 15]
        , we develop a new convolutional neural network (CNN) based semantic model (CNNSM) for semantic parsing. The CNNSM first uses a convolutional layer to project each word within a context window to a local contextual feature vector, so that semantically similar word-
        n
        -grams are projected to vectors that are close to each other in the contextual feature space. Further, since the overall meaning of a sentence is often determined by a few key words in the sentence, CNNSM uses a max pooling layer to extract the most salient local features to form a fixed-length global feature vector. The global feature vector can be then fed to feed-forward neural network layers to extract non-linear semantic features.
The architecture of the CNNSM is illustrated in Figure
        2
        . In what follows, we describe each layer of the CNNSM in detail, using the annotation illustrated in Figure
        2
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        In our model, we leverage the word hashing technique proposed in
        [8]
        where we first represent a word by a letter-trigram count vector. For example, given a word (e.g., cat), after adding word boundary symbols (e.g., #cat#), the word is segmented into a sequence of letter-
        n
        -grams (e.g., letter-trigrams: #-c-a, c-a-t, a-t-#). Then, the word is represented as a count vector of letter-trigrams. For example, the letter-trigram representation of “cat” is:
        <img alt="" class="ltx_graphics" height="190" id="S4.p2.g1" src="P14-2105/image003.png" width="541"/>
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        In Figure
        2
        , the word hashing matrix
        Wf
        denotes the transformation from a word to its letter-trigram count vector, which requires no learning. Word hashing not only makes the learning more scalable by controlling the size of the vocabulary, but also can effectively handle the OOV issues, sometimes due to spelling mistakes.
Given the letter-trigram based word representation, we represent a word-
        n
        -gram by concatenating the letter-trigram vectors of each word, e.g., for the
        t
        -th word-
        n
        -gram at the word-
        n
        -gram layer, we have:
       </p>
       lt=[ft-dT,⋯,ftT,⋯,ft+dT]𝐓,t=1,⋯,T
       <p class="ltx_p">
        where
        ft
        is the letter-trigram representation of the
        t
        -th word, and
        n=2⁢d+1
        is the size of the contextual window.
The convolution operation can be viewed as sliding window based feature extraction. It captures the word-
        n
        -gram contextual features. Consider the
        t
        -th word-
        n
        -gram, the convolution matrix projects its letter-trigram representation vector
        lt
        to a contextual feature vector
        ht
        . As shown in Figure
        2
        ,
        ht
        is computed by
       </p>
       ht=tanh⁡(Wc⋅lt),t=1,⋯,T
       <p class="ltx_p">
        where
        Wc
        is the feature transformation matrix, as known as the convolution matrix, which are shared among all word
        n
        -grams.

The output of the convolutional layer is a
sequence of local contextual feature vectors, one for each word (within a contextual window). Since many words do not have significant influence on the semantics of the sentence, we want to retain in the global feature vector only the salient features from a few key words. For this purpose, we use a max operation, also known as max pooling, to force the network to retain only the most useful local features produced by the convolutional layers.
Referring to the max-pooling layer of Figure
        2
        , we have
       </p>
       v⁢(i)=maxt=1,⋯,T⁡{ft⁢(i)},i=1,⋯,K
       <p class="ltx_p">
        where
        v⁢(i)
        is the
        i
        -th element of the max pooling layer
        v
        ,
        ht⁢(i)
        is the
        i
        -th element of the
        t
        -th local feature vector
        ht
        .
        K
        is the dimensionality of the max pooling layer, which is the same as the dimensionality of the local contextual feature vectors
        {ht}
        .
One more non-linear transformation layer is further applied on top of the global feature vector
        v
        to extract the high-level semantic representation, denoted by
        y
        . As shown in Figure
        2
        , we have
        y=t⁢a⁢n⁢h⁢â⁢⁢¡⁢(Ws⋅v)
        , where
        v
        is the global feature vector after max pooling,
        Ws
        is the semantic projection matrix, and
        y
        is the vector representation of the input query (or document) in latent semantic space.
Given a pattern and a relation, we compute their relevance score by measuring the cosine similarity between their semantic vectors. The semantic relevance score between a pattern
        Q
        and a relation
        R
        is defined as the cosine score of their semantic vectors
        yQ
        and
        yR
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        We train two CNN semantic models from sets of pattern–relation and mention–entity pairs, respectively. Following
        [8]
        , for every pattern, the corresponding relation is treated as a positive example and 100 randomly selected other relations are used as negative examples. The setting for the mention–entity model is similar.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        The posterior probability of the positive relation given the pattern is computed based on the cosine scores using softmax:
       </p>
       P(R+|Q)=exp⁡(γ⋅cos⁡(yR+,yQ))∑R′exp⁡(γ⋅cos⁡(yR′,yQ))
       <p class="ltx_p">
        where
        γ
        is a scaling factor set to 5. Model training is done by maximizing the log-posteriori using stochastic gradient descent.
More detail can be found in
        [14]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In order to provide a fair comparison to previous work, we experimented with our approach using the
        Paralax
        dataset
        [7]
        , which consists of paraphrases of questions mined from WikiAnswers
and answer triples from ReVerb. In this section, we briefly introduce the dataset, describe the system training and evaluation processes and, finally, present our experimental results.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Data &amp; Model Training
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         The
         Paralex
         training data consists of approximately 1.8 million pairs
of questions and single-relation database queries, such as “When were DVD players invented?”, paired with
         be-invent-in(dvd-player,?)
         .
For evaluation, the authors further sampled 698 questions that belong to 37 clusters
and hand labeled the answer triples returned by their systems.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         To train our two CNN semantic models, we derived two parallel corpora based on the
         Paralex
         training data. For relation patterns, we first scanned the original training corpus
to see if there was an exact surface form match of the entity (e.g.,
         dvd-player
         would map to “DVD player” in the question). If an exact
match was found, then the pattern would be derived by replacing the mention in the question with the special symbol. The corresponding relation of
this pattern was thus the relation used in the original database query, along with the variable argument position (i.e., 1 or 2, indicating whether
the answer entity was the first or second argument of the relation). In the end, we derived about 1.2 million pairs of patterns and
relations.
We then applied these patterns to all the 1.8 million training questions, which helped discover 160 thousand new mentions that did not have the
exact surface form matches to the entities.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         When training the CNNSM for the pattern–relation similarity measure, we randomly split the 1.2 million pairs of patterns and relations into two sets: the training set of 1.19 million pairs, and the validation set of 12 thousand pairs for hyper-parameter tuning. Data were tokenized by replacing hyphens with blank spaces. In the experiment, we used a context window (i.e., the receptive field) of three words in the convolutional neural networks. There were 15 thousand unique letter-trigrams observed in the training set (used for word hashing). Five hundred neurons were used in the convolutional layer, the max-pooling layer and the final semantic layer, respectively. We used a learning rate of 0.002 and the training converged after 150 iterations. A similar setting was used for the CNNSM for the mention–entity model, which was trained on 160 thousand mention-entity pairs.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We used the same test questions in the
         Paralex
         dataset to evaluate whether our system could find the answers from the ReVerb database.
Because our systems might find triples that were not returned by the
         Paralex
         systems, we labeled these new question–triple pairs ourselves.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Given a question, the system first enumerated all possible decompositions of the mentions and patterns, as described earlier. We then computed the similarity
scores between the pattern and all relations in the KB and retained 150 top-scoring relation candidates.
For each selected relation, the system then checked all triples
in the KB that had this relation and computed the similarity score between the mention and corresponding argument entity. The product of the probabilities of these two models, which are derived from the cosine similarity scores using softmax as described in Sec.
         4
         , was used as the final score of the triple for ranking the answers. The top answer triple was used to compute the precision and recall of the system when reporting the system performance. By limiting the systems to output only answer triples with scores higher than a predefined threshold, we could control the trade-off between recall and precision and thus plot the precision–recall curve.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         Table
         1
         shows the performance in F
         1
         , precision, recall and mean average precision of our systems and
         Paralex
         . We provide
two variations here. CNNSM
         p⁢m
         is the full system and consists of two semantic similarity models for pattern–relation and mention–entity. The
other model, CNNSM
         p
         , only measures the similarity between the patterns and relations, and maps a mention to an entity when they have the same surface
form.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         Since the trade-off between precision and recall can be adjusted by varying the threshold, it is more informative to compare systems on the precision–recall curves, which are shown in Figure
         3
         . As we can observe from the figure, the precision of our CNNSM
         p⁢m
         system is consistently higher than
         Paralex
         across all recall regions. The CNNSM
         m
         system also performs similarly to CNNSM
         p⁢m
         in the high precision regime, but is inferior when recall is higher. This is understandable since the system does not match mentions with entities of different surface forms (e.g., “Robert Hooke” to “Hooke”). Notice that the highest F
         1
         values of them are
         0.61
         and
         0.56
         , compared to
         0.54
         of
         Paralex
         . Tuning the thresholds using a validation set would be needed if there is a metric (e.g., F
         1
         ) that specifically needs to be optimized.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
