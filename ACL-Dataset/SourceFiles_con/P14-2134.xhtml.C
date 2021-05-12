<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Distributed Representations of Geographically Situated Language.
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
       We introduce a model for incorporating contextual information (such as geography) in learning vector-space representations of
       situated
       language.
In contrast to approaches to multimodal representation learning that have used properties of the
       object
       being described (such as its color), our model includes information about the
       subject
       (i.e., the speaker), allowing us to learn the contours of a word’s meaning that are shaped by the context in which it is uttered.
In a quantitative evaluation on the task of judging geographically informed semantic similarity
between representations learned from 1.1 billion words of geo-located tweets,
our joint model outperforms comparable independent models that learn meaning in isolation.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       noitemsep,topsep=10pt,parsep=0pt,partopsep=0pt
       noitemsep,topsep=10pt,parsep=0pt,partopsep=0pt
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
        The vast textual resources used in NLP – newswire, web text, parliamentary proceedings – can encourage a view of language as a disembodied phenomenon. The rise of social media, however, with its large volume of text paired with information about its author and social context, reminds us that each word
is uttered by a particular person at a particular place and time.
In short: language is
        situated
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The coupling of text with demographic information has enabled computational modeling of linguistic variation, including uncovering words and topics that are characteristic of geographical regions
        []
        , learning correlations between words and socioeconomic variables
        []
        ;
and charting how new terms spread geographically
        []
        . These models can tell us that
        hella
        was (at one time) used most often by a particular demographic group in northern California, echoing earlier linguistic studies
        []
        , and that
        wicked
        is used most often in New England
        []
        ;
and they have practical applications, facilitating tasks like text-based geolocation
        []
        .
One desideratum that remains, however, is how the
        meaning
        of these terms is shaped by geographical influences – while
        wicked
        is used throughout the United States to mean
        bad
        or
        evil
        (“he is a wicked man”),
in New England it is used as an adverbial intensifier (“my boy’s wicked smart”).
In leveraging grounded social media to uncover linguistic variation, what we want to learn is how a word’s meaning is shaped by its geography.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we introduce a method that extends vector-space lexical semantic models to learn representations of geographically situated language. Vector-space models of lexical semantics have been a popular and effective approach to learning representations of word meaning
        [, inter alia]
        . In bringing in extra-linguistic information to learn word representations, our work falls into the general domain of multimodal learning;
while other work has used visual information to improve distributed representations
        []
        , this work generally exploits information about the object being described (e.g.,
        strawberry
        and a picture of a strawberry);
in contrast, we use information about the
        speaker
        to learn representations that vary according to contextual variables from the speaker’s perspective.
Unlike classic multimodal systems that incorporate multiple active modalities (such as gesture) from a user
        []
        , our primary input is textual data, supplemented with metadata about the author and the moment of authorship.
This information enables learning models of word meaning that are sensitive to such factors, allowing us to distinguish, for example, between the usage of
        wicked
        in Massachusetts from the usage of that word elsewhere, and letting us better associate geographically grounded named entities (e.g,
        Boston
        ) with their hypernyms (
        city
        ) in their respective regions.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Model
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The model we introduce is grounded in the distributional hypothesis
        []
        , that two words are similar by appearing in the same kinds of contexts (where “context” itself can be variously defined as the bag or sequence of tokens around a target word, either by linear distance or dependency path).
We can invoke the distributional hypothesis for many instances of regional variation by observing that such variants often appear in similar contexts.
For example:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           my boy’s
           wicked
           smart
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           my boy’s
           hella
           smart
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           my boy’s
           very
           smart
          </p>
         </div>
        </li>
       </ul>
       <p class="ltx_p">
        Here, all three variants can often be seen in an immediately pre-adjectival position (as is common with intensifying adverbs).
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Given the empirical success of vector-space representations in capturing semantic properties and their success at a variety of NLP tasks
        []
        , we use a simple, but state-of-the-art neural architecture
        []
        to learn low-dimensional real-valued representations of words.
The graphical form of this model is illustrated in figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        This model corresponds to an extension of the “skip-gram” language model
        []
        (hereafter SGLM).
Given an input sentence
        𝒔
        and a context window of size
        t
        , each word
        si
        is conditioned on in turn to predict the identities of all of the tokens within
        t
        words around it.
For a vocabulary
        V
        , each input word
        si
        is represented as a one-hot vector
        𝒘i
        of length
        |V|
        .
The SGLM has two sets of parameters.
The first is the representation matrix
        W∈ℝ|V|×k
        , which encodes the real-valued embeddings for each word in the vocabulary.
A matrix multiply
        𝒉=𝒘⊤W,∈ℝk
        serves to index the particular embedding for word
        𝒘
        , which constitutes the model’s hidden layer.
To predict the value of the context word
        y
        (again, a one-hot vector of dimensionality
        |V|
        ), this hidden representation
        𝒉
        is then multiplied by a second parameter matrix
        X∈ℝ|V|×k
        .
The final prediction over the output vocabulary is then found by passing this resulting vector through the softmax function
        𝒐=softmax⁢(X⁢𝒉)
        , giving a vector in the
        |V|
        -dimensional unit simplex.
Backpropagation using (input
        x
        , output
        y
        ) word tuples learns the values of
        W
        (the embeddings) and
        X
        (the output parameter matrix) that maximize the likelihood of
        y
        (i.e., the context words) conditioned on
        x
        (i.e., the
        si
        ’s).
During backpropagation, the errors propagated are the difference between
        𝒐
        (a probability distribution with
        k
        outcomes) and the true (one-hot) output
        y
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Let us define a set of contextual variables
        𝒞
        ; in the experiments that follow,
        𝒞
        is comprised solely of geographical state
        𝒞𝑠𝑡𝑎𝑡𝑒={AK,AL,…,WY}
        ) but could in principle include any number of features, such as calendar month, day of week, or other demographic variables of the speaker.
Let
        |𝒞|
        denote the sum of the cardinalities of all variables in
        𝒞
        (i.e.,
        51
        states, including the District of Columbia).
Rather than using a single embedding matrix
        W
        that contains low-dimensional representations for every word in the vocabulary, we define a global embedding matrix
        W𝑚𝑎𝑖𝑛∈ℝ|V|×k
        and an additional
        |𝒞|
        such matrices (each again of size
        |V|×k
        , which capture the effect that each variable value has on each word in the vocabulary.
Given an input word
        𝒘
        and set of active variable values
        𝒜
        (e.g.,
        𝒜={𝑠𝑡𝑎𝑡𝑒=MA}
        ), we calculate the hidden layer
        𝒉
        as the sum of these independent embeddings:
        𝒉=𝒘⊤⁢W𝑚𝑎𝑖𝑛+∑a∈𝒜𝒘⊤⁢Wa
        .
While the word
        wicked
        has a common low-dimensional representation in
        W𝑚𝑎𝑖𝑛,𝑤𝑖𝑐𝑘𝑒𝑑
        that is invoked for every instance of its use (regardless of the place), the corresponding vector
        WMA,𝑤𝑖𝑐𝑘𝑒𝑑
        indicates how that common representation should shift in
        k
        -dimensional space when used in Massachusetts.
Backpropagation functions as in standard SGLM, with gradient updates for each training example
        {x,y}
        touching not only
        W𝑚𝑎𝑖𝑛
        (as in SGLM), but all active
        W𝒜
        as well.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        The additional
        W
        embeddings we add lead to an increase in the number of total parameters by a factor of
        |𝒞|
        .
To control for the extra degrees of freedom this entails, we add squared
        ℓ2
        regularization to all parameters, using stochastic gradient descent for backpropagation with minibatch updates for the regularization term.
As in Mikolov et al.
        []
        , we speed up computation using the hierarchical softmax
        []
        on the output matrix
        X
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        This model defines a joint parameterization over all variable values in the data, where information from data originating in California, for instance, can influence the representations learned for Wisconsin;
a naive alternative would be to simply train individual models on each variable value (a “California” model using data only from California, etc.).
A joint model has three
        a priori
        advantages over independent models: (i) sharing data across variable values encourages representations across those values to be similar;
e.g., while
        city
        may be closer to
        Boston
        in Massachusetts and
        Chicago
        in Illinois, in both places it still generally connotes a
        municipality
        ;
(ii) such sharing can mitigate data sparseness for less-witnessed areas;
and (iii) with a joint model, all representations are guaranteed to be in the same vector space and can therefore be compared to each other;
with individual models (each with different initializations), word vectors across different states may not be directly compared.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Evaluation
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We evaluate our model by confirming its face validity in a qualitative analysis and estimating its accuracy at the quantitative task of judging geographically-informed semantic similarity.
We use 1.1 billion tokens from 93 million geolocated tweets gathered between September 1, 2011 and August 30, 2013 (approximately 127,000 tweets per day evenly sampled over those two years).
This data only includes tweets that have been geolocated to state-level granularity in the United States using high-precision pattern matching on the user-specified location field (e.g., “new york ny”
        →
        NY, “chicago”
        →
        IL, etc.).
As a preprocessing step, we identify a set of target multiword expressions in this corpus as the maximal sequence of adjectives + nouns with the highest pointwise mutual information;
in all experiments described below, we define the vocabulary
        V
        as the most frequent 100,000 terms (either unigrams or multiword expressions) in the total data, and set the dimensionality of the embedding
        k=100
        .
In all experiments, the contextual variable is the observed US state (including DC),
so that
        |𝒞|=51
        ;
the vector space representation of word
        𝒘
        in state
        s
        is
        𝒘⊤⁢W𝑚𝑎𝑖𝑛+𝒘⊤⁢Ws
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Qualitative Evaluation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         To illustrate how the model described above can learn geographically-informed semantic representations of words, table
         1
         displays the terms with the highest cosine similarity to
         wicked
         in Kansas and Massachusetts after running our joint model on the full 1.1 billion words of Twitter data;
while
         wicked
         in Kansas is close to other evaluative terms like
         evil
         and
         pure
         and religious terms like
         gods
         and
         spirit
         , in Massachusetts it is most similar to other intensifiers like
         super
         ,
         ridiculously
         and
         insanely
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         Table
         2
         likewise presents the terms with the highest cosine similarity to
         city
         in both California and New York;
while the terms most evoked by
         city
         in California include regional locations like Chinatown, Los Angeles’ South Bay and San Francisco’s East Bay, in New York the most similar terms include
         hamptons
         ,
         upstate
         and
         borough
         (New York City’s term of administrative division).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Quantitative Evaluation
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         As a quantitative measure of our model’s performance, we consider the task of judging semantic similarity among words whose meanings are likely to evoke strong geographical correlations.
In the absence of a sizable number of linguistically interesting terms (like
         wicked
         ) that are known to be geographically variable, we consider the proxy of estimating the named entities evoked by specific terms in different geographical regions.
As noted above, geographic terms like
         city
         provide one such example: in Massachusetts we expect the term
         city
         to be more strongly connected to grounded named entities like
         Boston
         than to other US cities.
We consider seven categories for which we can reasonably expect the connotations of each term to vary by geography; in each case, we calculate the distance between two terms
         x
         and
         y
         using representations learned for a given state (
         δ𝑠𝑡𝑎𝑡𝑒⁢(x,y)
         ).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <ol class="ltx_enumerate" id="I2">
         <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I2.i1.p1">
           <p class="ltx_p">
            city
            . For each state, we measure the distance between the word
            city
            and the state’s most populous city; e.g.,
            δAZ⁢(𝑐𝑖𝑡𝑦,𝑝ℎ𝑜𝑒𝑛𝑖𝑥)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I2.i2.p1">
           <p class="ltx_p">
            state
            . For each state, the distance between the word
            state
            and the state’s name; e.g.,
            δWI⁢(𝑠𝑡𝑎𝑡𝑒,𝑤𝑖𝑠𝑐𝑜𝑛𝑠𝑖𝑛)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I2.i3.p1">
           <p class="ltx_p">
            football
            . For all NFL teams, the distance between the word
            football
            and the team name; e.g.,
            δIL⁢(𝑓𝑜𝑜𝑡𝑏𝑎𝑙𝑙,𝑏𝑒𝑎𝑟𝑠)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           4.
          </span>
          <div class="ltx_para" id="I2.i4.p1">
           <p class="ltx_p">
            basketball
            . For all NBA teams from a US state, the distance between the word
            basketball
            and the team name; e.g.,
            δFL⁢(𝑏𝑎𝑠𝑘𝑒𝑡𝑏𝑎𝑙𝑙,ℎ𝑒𝑎𝑡)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           5.
          </span>
          <div class="ltx_para" id="I2.i5.p1">
           <p class="ltx_p">
            baseball
            . For all MLB teams from a US state, the distance between the word
            baseball
            and the team name; e.g.,
            δIL⁢(𝑏𝑎𝑠𝑒𝑏𝑎𝑙𝑙,𝑐𝑢𝑏𝑠)
            ,
            δIL⁢(𝑏𝑎𝑠𝑒𝑏𝑎𝑙𝑙,𝑤ℎ𝑖𝑡𝑒⁢𝑠𝑜𝑥)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i6" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           6.
          </span>
          <div class="ltx_para" id="I2.i6.p1">
           <p class="ltx_p">
            hockey
            . For all NHL teams from a US state, the distance between the word
            hockey
            and the team name; e.g.,
            δPA⁢(ℎ𝑜𝑐𝑘𝑒𝑦,𝑝𝑒𝑛𝑔𝑢𝑖𝑛𝑠)
            .
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I2.i7" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           7.
          </span>
          <div class="ltx_para" id="I2.i7.p1">
           <p class="ltx_p">
            park
            . For all US national parks, the distance between the word
            park
            and the park name; e.g.,
            δAK⁢(𝑝𝑎𝑟𝑘,𝑑𝑒𝑛𝑎𝑙𝑖)
            .
           </p>
          </div>
         </li>
        </ol>
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Each of these questions asks the following: what words are evoked for a given target word (like
         football
         )? While
         football
         may everywhere evoke similar sports like
         baseball
         or
         soccer
         or more specific football-related terms like
         touchdown
         or
         field goal
         , we expect that particular sports teams will be evoked more strongly by the word
         football
         in their particular geographical region: in Wisconsin,
         football
         should evoke
         packers
         , while in Pennsylvania,
         football
         evokes
         steelers
         .
Note that this is not the same as simply asking which sports team is most frequently (or most characteristically) mentioned in a given area;
by measuring the distance to a target word (
         football
         ), we are attempting to estimate the varying strengths of association between concepts in different regions.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         For each category, we measure similarity as the average cosine similarity between the vector for the target word for that category (e.g.,
         city
         ) and the corresponding vector for each state-specific answer (e.g.,
         chicago
         for IL;
         boston
         for MA). We compare three different models:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p5">
        <ol class="ltx_enumerate" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Joint
            . The full model described in section
            2
            , in which we learn a global representation for each word along with deviations from that common representation for each state.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Individual
            . For comparison, we also partition the data among all 51 states, and train a single model for each state using only data from that state. In this model, there is no sharing among states; California has the most data with 11,604,637 tweets; Wyoming has the least with 47,503 tweets.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I3.i3.p1">
           <p class="ltx_p">
            –Geo
            . We also train a single model on all of the training data, but ignore any state metadata. In this case the distance
            δ
            between two terms is their overall distance within the entire United States.
           </p>
          </div>
         </li>
        </ol>
       </div>
       <div class="ltx_para" id="S3.SS2.p6">
        <p class="ltx_p">
         As one concrete example of these differences between individual data points, the cosine similarity between
         city
         and
         seattle
         in the
         –Geo
         model is
         0.728
         (
         seattle
         is ranked as the 188th most similar term to
         city
         overall); in the
         Individual
         model using only tweets from Washington state,
         δW⁢A⁢(c⁢i⁢t⁢y,s⁢e⁢a⁢t⁢t⁢l⁢e)=0.780
         (rank #32); and in the
         Joint
         model, using information from the entire United States with deviations for Washington,
         δW⁢A⁢(c⁢i⁢t⁢y,s⁢e⁢a⁢t⁢t⁢l⁢e)=0.858
         (rank #6). The overall similarity for the city category of each model is the average of 51 such tests (one for each city).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p7">
        <p class="ltx_p">
         Figure
         2
         present the results of the full evaluation, including 95% confidence intervals for each mean.
While the two models that include geographical information naturally outperform the model that does not, the
         Joint
         model generally far outperforms the
         Individual
         models trained on state-specific subsets of the data.
         A model that can exploit all of the information in the data, learning core vector-space representations for all words along with deviations for each contextual variable, is able to learn more geographically-informed representations for this task than strict geographical models alone.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Acknowledgments
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        The research reported in this article was supported by US NSF grants IIS-1251131 and CAREER IIS-1054319, and by an ARCS scholarship to D.B. This work was made possible through the use of computing resources made available by the Open Cloud Consortium, Yahoo and the Pittsburgh Supercomputing Center.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
