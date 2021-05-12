<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Political Ideology Detection Using Recursive Neural Networks.
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
       An individual’s words often reveal their political ideology. Existing automated
techniques to identify ideology from text focus on bags of words or wordlists,
ignoring syntax. Taking inspiration from recent work in sentiment analysis that
successfully models the compositional aspect of language, we apply a recursive
neural network (
       RNN
       ) framework to the task of identifying the political
position evinced by a sentence. To show the importance of modeling
subsentential elements, we crowdsource political annotations at a phrase and
sentence level. Our model outperforms existing models on our newly annotated
dataset and an existing dataset.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       smalign
      </p>
      <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
       <tr class="ltx_equation ltx_align_baseline" id="S0.E1">
        <td class="ltx_eqn_center_padleft">
        </td>
        <td class="ltx_td ltx_align_right">
         \BODY
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
        Many of the issues discussed by politicians and the media are so
nuanced that even word choice entails choosing an ideological
position. For example, what liberals call the “estate tax”
conservatives call the “death tax”; there are no ideologically
neutral alternatives
        [14]
        . While objectivity remains
an important principle of journalistic professionalism, scholars and
watchdog groups claim that the media are
biased
        [10, 6, 18]
        ,
backing up their assertions by publishing examples of obviously biased
articles on their websites. Whether or not it reflects an underlying
lack of objectivity, quantitative changes in the popular framing of an
issue over time—favoring one ideologically-based position over
another—can have a substantial effect on the evolution of policy
        [5]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Manually identifying ideological bias in political text, especially in the age
of big data, is an impractical and expensive process. Moreover, bias may be
localized to a small portion of a document, undetectable by coarse-grained
methods. In this paper, we examine the problem of detecting ideological bias on
the sentence level. We say a sentence contains
        ideological bias
        if its
author’s political position (here
        liberal
        or
        conservative
        , in the sense of U.S. politics) is evident
from the text.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Ideological bias is difficult to detect, even for humans—the task
relies not only on political knowledge but also on the annotator’s
ability to pick up on subtle elements of language use.
For example, the sentence in Figure
        1
        includes phrases typically associated with conservatives, such as
“small businesses” and “death tax”. When we take more of the
structure into account, however, we find that scare quotes and a
negative propositional attitude (
        a lie about X
        ) yield an
evident liberal bias.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Existing approaches toward bias detection have not gone far beyond
“bag of words” classifiers, thus ignoring richer linguistic context
of this kind and often operating at the level of whole documents. In
contrast, recent work in sentiment analysis has used deep learning to
discover compositional effects
        [27, 28]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Building from those insights, we introduce a recursive neural network
(
        rnn
        ) to detect ideological bias on the sentence level. This
model requires richer data than currently available, so we develop a
new political ideology dataset annotated at the phrase level. With
this new dataset we show that
        rnn
        s not only label sentences well but also improve further when given additional phrase-level
annotations.
        rnn
        s are quantitatively more effective than
existing methods that use syntactic and semantic features separately,
and we also illustrate how our model correctly identifies ideological
bias in complex syntactic constructions.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Recursive Neural Networks
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Recursive neural networks (
        rnn
        s) are machine learning
models that capture syntactic and semantic composition. They have achieved
state-of-the-art performance on a variety of sentence-level
        nlp
        tasks, including sentiment analysis, paraphrase detection, and parsing
        [26, 13]
        .
        rnn
        models represent a shift from previous research on ideological bias
detection in that they do not rely on hand-made lexicons,
dictionaries, or rule sets. In this section, we describe a supervised
        rnn
        model for bias detection and highlight differences from
previous work in training procedure and initialization.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Model Description
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         By taking into account the hierarchical nature of language,
         rnn
         s
can model
         semantic composition
         , which is the principle that a
phrase’s meaning is a combination of the meaning of the words within
that phrase and the syntax that combines those words. While semantic
composition does not apply universally (e.g., sarcasm and idioms),
most language follows this principle. Since most ideological bias
becomes identifiable only at higher levels of sentence trees (as
verified by our annotation, Figure
         4
         ), models relying
primarily on word-level distributional statistics are not desirable
for our problem.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         The basic idea behind the standard
         rnn
         model is that each word
         w
         in a
sentence is associated with a vector representation
         xw∈ℝd
         .
Based on a parse tree, these words form phrases
         p
         (Figure
         2
         ). Each of these phrases also has an associated
vector
         xp∈ℝd
         of the same dimension as the word vectors. These
phrase vectors should represent the meaning of the phrases composed of
individual words. As phrases themselves merge into complete sentences, the
underlying vector representation is trained to retain the sentence’s whole meaning.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         The challenge is to describe how vectors combine to form complete
representations. If two words
         wa
         and
         wb
         merge to form phrase
         p
         , we
posit that the phrase-level vector is
        </p>
        xp=f⁢(WL⋅xa+WR⋅xb+b1),

(2)
        <p class="ltx_p">
         where
         WL
         and
         WR
         are
         d×d
         left and right composition matrices
shared across all nodes in the tree,
         b1
         is a bias term, and
         f
         is a
nonlinear activation function such as
         tanh
         . The word-level vectors
         xa
         and
         xb
         come from a
         d×V
         dimensional word embedding matrix
         We
         , where
         V
         is the size of the vocabulary.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p4">
        <p class="ltx_p">
         We are interested in learning representations that can distinguish
political polarities given labeled data. If an element of this vector space,
         xd
         , represents a sentence with liberal bias, its vector should be distinct
from the vector
         xr
         of a conservative-leaning sentence.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p5">
        <p class="ltx_p">
         Supervised
         rnn
         s achieve this distinction by applying a regression that takes the
node’s vector
         xp
         as input and produces a prediction
         y^p
         . This is
a softmax layer
        </p>
        y^d=softmax⁢(Wc⁢a⁢t⋅xp+b2),

(3)
        <p class="ltx_p">
         where the softmax function is
        </p>
        softmax⁢(q)=exp⁡q∑j=1kexp⁡qj

(4)
        <p class="ltx_p">
         and
         Wc⁢a⁢t
         is a
         k×d
         matrix for a dataset with
         k
         -dimensional labels.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p6">
        <p class="ltx_p">
         We want the predictions of the softmax layer to match our annotated
data; the discrepancy between categorical predictions and annotations
is measured through the cross-entropy loss. We optimize the model
parameters to minimize the cross-entropy loss over all sentences in
the corpus. The cross-entropy loss of a single sentence is the sum
over the true labels
         yi
         in the sentence,
        </p>
        ℓ⁢(y^s)=∑p=1kyp*l⁢o⁢g⁢(y^p).

(5)
       </div>
       <div class="ltx_para" id="S2.SS1.p7">
        <p class="ltx_p">
         This induces a supervised objective function over all sentences: a
regularized sum over all node losses normalized by the number of nodes
         N
         in the training set,
        </p>
        C=1N⁢∑iNℓ⁢(p⁢r⁢e⁢di)+λ2⁢∥θ∥2.

(6)
       </div>
       <div class="ltx_para" id="S2.SS1.p8">
        <p class="ltx_p">
         We use
         l-bfgs
         with parameter averaging
         [12]
         to optimize the
model parameters
         θ=(WL,WR,Wc⁢a⁢t,We,b1,b2)
         . The gradient of
the objective, shown in Eq. (
         7
         ), is computed using backpropagation through
structure
         [8]
         ,
        </p>
        ∂⁡C∂⁡θ=1N⁢∑iN∂⁡ℓ⁢(y^i)∂⁡θ+λ⁢θ.

(7)
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Initialization
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         When initializing our model, we have two choices: we can initialize all of our
parameters randomly or provide the model some prior knowledge. As we see in
Section
         4
         , these choices have a significant effect on final
performance.
        </p>
       </div>
       <div class="ltx_paragraph" id="S2.SS2.SSS0.P1">
        <h5 class="ltx_title ltx_title_paragraph">
         Random
        </h5>
        <div class="ltx_para" id="S2.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          The most straightforward choice is to initialize the word embedding matrix
          We
          and composition matrices
          WL
          and
          WR
          randomly such that without any
training, representations for words and phrases are arbitrarily projected into
the vector space.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S2.SS2.SSS0.P2">
        <h5 class="ltx_title ltx_title_paragraph">
         word2vec
        </h5>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          The other alternative is to initialize the word embedding matrix
          We
          with
values that reflect the meanings of the associated word types. This improves
the performance of
          rnn
          models over random initializations
          [4, 26]
          . We initialize our model with
300-dimensional
          word2vec
          toolkit vectors generated by a continuous
skip-gram model trained on around 100 billion words from the Google News corpus
          [16]
          .
         </p>
        </div>
        <div class="ltx_para" id="S2.SS2.SSS0.P2.p2">
         <p class="ltx_p">
          The word2vec embeddings have linear relationships (e.g., the closest vectors to
the average of “green” and “energy” include phrases such as “renewable
energy”, “eco-friendly”, and “efficient lightbulbs”). To preserve these
relationships as phrases are formed in our sentences, we initialize our left and
right composition matrices such that parent vector
          p
          is computed by taking the
average of children
          a
          and
          b
          (
          WL=WR=0.5⁢𝕀d×d
          ). This
initialization of the composition matrices has previously been effective for
parsing
          [25]
          .
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
       Datasets
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We performed initial experiments on a dataset of Congressional debates that has
annotations on the author level for partisanship, not ideology. While the two
terms are highly correlated (e.g., a member of the Republican party likely agrees
with conservative stances on most issues), they are not identical. For example,
a moderate Republican might agree with the liberal position on increased gun
control but take conservative positions on other issues. To avoid conflating
partisanship and ideology we create a new dataset annotated for ideological bias
on the sentence and phrase level. In this section we describe our initial
dataset (Convote) and explain the procedure we followed for creating our new
dataset (
        ibc
        ).
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Convote
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The Convote dataset
         [29]
         consists of
         us
         Congressional floor debate transcripts from 2005 in which all speakers
have been labeled with their political party (Democrat, Republican, or
independent). We propagate party labels down from the speaker to all
of their individual sentences and map from party label to ideology
label (Democrat
         →
         liberal,
Republican
         →
         conservative). This is an expedient choice;
in future work we plan to make use of work in political science
characterizing candidates’ ideological positions empirically based on
their behavior
         [3]
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <p class="ltx_p">
         While the Convote dataset has seen widespread use for document-level
political classification, we are unaware of similar efforts at the
sentence level.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.1
         </span>
         Biased Sentence Selection
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS1.p1">
         <p class="ltx_p">
          The strong correlation between
          us
          political parties and
political ideologies (Democrats with liberal, Republicans with
conservative) lends confidence that this dataset contains a rich mix
of ideological statements. However, the raw Convote dataset contains
a low percentage of sentences with explicit ideological
bias.
          We therefore use the features
in Yano et al.
          [32]
          , which correlate with
political bias, to select sentences to annotate that have a higher
likelihood of containing bias. Their features come from the
Linguistic Inquiry and Word Count lexicon (
          liwc
          )
          [20]
          , as well as from lists of “sticky
bigrams”
          [2]
          strongly associated with one party or
another (e.g., “illegal aliens” implies conservative, “universal
healthcare” implies liberal).
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS1.p2">
         <p class="ltx_p">
          We first extract the subset of sentences that contains any words in the
          liwc
          categories of Negative Emotion, Positive Emotion,
Causation, Anger, and Kill verbs.
          After computing a list of the top
100 sticky bigrams for each category, ranked by log-likelihood ratio,
and selecting another subset from the original data that included only
sentences containing at least one sticky bigram, we take the union of
the two subsets. Finally, we balance the resulting dataset so that
it contains an equal number of sentences from Democrats and
Republicans, leaving us with a total of 7,816 sentences.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Ideological Books
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         In addition to Convote, we use the Ideological
Books Corpus (
         ibc
         ) developed by Gross et
al.
         [11]
         . This is a collection of books and
magazine articles written between 2008 and 2012 by authors with well-known
political leanings. Each document in the
         ibc
         has been manually labeled with
coarse-grained ideologies (right, left, and center) as well as fine-grained
ideologies (e.g., religious-right, libertarian-right) by political science
experts.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         There are over a million sentences in the
         ibc
         , most of which have no
noticeable political bias. Therefore we use the filtering procedure outlined in
Section
         3.1.1
         to obtain a subset of 55,932 sentences. Compared
to our final Convote dataset, an even larger percentage of the
         ibc
         sentences
exhibit no noticeable political bias.
         Because our goal is to distinguish between
liberal and conservative bias, instead of the more general task of classifying
sentences as “neutral” or “biased”, we filter the dataset further using
         dualist
         [23]
         , an active learning tool, to reduce the
proportion of neutral sentences in our dataset. To train the
         dualist
         classifier, we manually assigned class labels of “neutral” or “biased” to 200
sentences, and selected typical partisan unigrams to represent the “biased”
class.
         dualist
         labels 11,555 sentences as politically biased, 5,434 of
which come from conservative authors and 6,121 of which come from liberal
authors.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S3.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.2.1
         </span>
         Annotating the
         ibc
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS1.p1">
         <p class="ltx_p">
          For purposes of annotation, we define the task of political ideology
detection as identifying, if possible, the political position of a
given sentence’s author, where position is either
          liberal
          or
          conservative
          .
          We used the
Crowdflower crowdsourcing platform (crowdflower.com), which has
previously been used for subsentential sentiment annotation
          [22]
          , to obtain human annotations of the
filtered
          ibc
          dataset for political bias on both the sentence and
phrase level. While members of the Crowdflower workforce are certainly
not experts in political science, our simple task and the ubiquity of
political bias allows us to acquire useful annotations.
         </p>
        </div>
        <div class="ltx_paragraph" id="S3.SS2.SSS1.P1">
         <h5 class="ltx_title ltx_title_paragraph">
          Crowdflower Task
         </h5>
         <div class="ltx_para" id="S3.SS2.SSS1.P1.p1">
          <p class="ltx_p">
           First, we parse the filtered
           ibc
           sentences using the Stanford constituency
parser
           [25]
           . Because of the expense of labeling every node in a sentence, we only label one path in each sentence. The
process for selecting paths is as follows: first, if any paths contain one of
the top-ten partisan unigrams,
           we select the longest such path; otherwise, we select the path with the most open class
constituencies (
           np
           ,
           vp
           ,
           adjp
           ). The root node of a sentence is
always included in a path.
          </p>
         </div>
         <div class="ltx_para" id="S3.SS2.SSS1.P1.p2">
          <p class="ltx_p">
           Our task is shown in Figure
           3
           . Open class constituencies are
revealed to the worker incrementally, starting with the
           np
           ,
           vp
           , or
           adjp
           furthest from the root and progressing up the tree. We choose this
design to prevent workers from changing their lower-level phrase annotations
after reading the full sentence.
          </p>
         </div>
        </div>
        <div class="ltx_paragraph" id="S3.SS2.SSS1.P2">
         <h5 class="ltx_title ltx_title_paragraph">
          Filtering the Workforce
         </h5>
         <div class="ltx_para" id="S3.SS2.SSS1.P2.p1">
          <p class="ltx_p">
           To ensure our annotators have a basic understanding of
           us
           politics, we restrict workers to
           us
           ip
           addresses and
require workers manually annotate one node from 60 different “gold ”
paths annotated by the authors. We select these nodes such that the
associated phrase is either obviously biased or obviously
neutral. Workers must correctly annotate at least six of eight gold
paths before they are granted access to the full task. In addition,
workers must maintain 75% accuracy on gold paths that randomly appear
alongside normal paths. Gold paths dramatically improve the quality of
our workforce: 60% of contributors passed the initial quiz (the 40%
that failed were barred from working on the task), while only 10% of
workers who passed the quiz were kicked out for mislabeling subsequent
gold paths.
          </p>
         </div>
        </div>
        <div class="ltx_paragraph" id="S3.SS2.SSS1.P3">
         <h5 class="ltx_title ltx_title_paragraph">
          Annotation Results
         </h5>
         <div class="ltx_para" id="S3.SS2.SSS1.P3.p1">
          <p class="ltx_p">
           Workers receive the following instructions:
          </p>
         </div>
         <div class="ltx_para" id="S3.SS2.SSS1.P3.p2">
          <table class="ltx_tabular ltx_align_middle">
           <tbody class="ltx_tbody">
            <tr class="ltx_tr">
             <td class="ltx_td ltx_align_justify ltx_border_l ltx_border_r ltx_border_t" style="width:390.3pt;" width="390.3pt">
              Each task on this page contains a set of phrases from a single sentence. For each phrase, decide whether or not the author favors a political position to the left (
              Liberal
              ) or right (
              Conservative
              ) of center.
             </td>
            </tr>
            <tr class="ltx_tr">
             <td class="ltx_td ltx_align_justify ltx_border_l ltx_border_r" style="width:390.3pt;" width="390.3pt">
              <li class="ltx_item">
               <div class="ltx_para" id="S3.SS2.SSS1.P3.p2.p1">
                <p class="ltx_p">
                 If the phrase is indicative of a position to the left of center, please choose
                 Liberal
                 .
                </p>
                <li class="ltx_item">
                 <div class="ltx_para" id="S3.SS2.SSS1.P3.p2.p1.p1">
                  <p class="ltx_p">
                   If the phrase is indicative of a position to the right of center, please choose
                   Conservative
                   .
                  </p>
                  <li class="ltx_item">
                   <div class="ltx_para" id="S3.SS2.SSS1.P3.p2.p1.p1.p1">
                    <p class="ltx_p">
                     If you feel like the phrase indicates some position to the left or right of the political center, but you’re not sure which direction, please mark
                     Not neutral, but I’m unsure of which direction
                     .
                    </p>
                    <li class="ltx_item">
                     <div class="ltx_para" id="S3.SS2.SSS1.P3.p2.p1.p1.p1.p1">
                      <p class="ltx_p">
                       If the phrase is not indicative of a position to the left or right of center, please mark
                       Neutral
                       .
                      </p>
                     </div>
                    </li>
                   </div>
                  </li>
                 </div>
                </li>
               </div>
              </li>
             </td>
            </tr>
            <tr class="ltx_tr">
             <td class="ltx_td ltx_align_justify ltx_border_l ltx_border_r ltx_border_t" style="width:390.3pt;" width="390.3pt">
             </td>
            </tr>
           </tbody>
          </table>
         </div>
         <div class="ltx_para" id="S3.SS2.SSS1.P3.p3">
          <p class="ltx_p">
           We had workers annotate 7,000 randomly selected paths from the filtered
           ibc
           dataset, with half of the paths coming from conservative authors and
the other half from liberal authors, as annotated by Gross et
al.
           [11]
           . Three workers annotated each path in the
dataset, and we paid $0.03 per sentence. Since identifying political bias is a
relatively difficult and subjective task, we include all sentences where at
least two workers agree on a label for the root node in our final dataset,
except when that label is “Not neutral, but I’m unsure of which direction”. We
only keep phrase-level annotations where at least two workers agree on the
label: 70.4% of all annotated nodes fit this definition of agreement. All
unannotated nodes receive the label of their closest annotated ancestor. Since
the root of each sentence is always annotated, this strategy ensures that every
node in the tree has a label. Our final balanced
           ibc
           dataset consists of
3,412 sentences (4,062 before balancing and removing neutral sentences) with a
total of 13,640 annotated nodes. Of these sentences, 543 switch polarity
(liberal
           →
           conservative or vice versa) on an annotated path.
          </p>
         </div>
         <div class="ltx_para" id="S3.SS2.SSS1.P3.p4">
          <p class="ltx_p">
           While we initially wanted to incorporate neutral labels into our model, we
observed that lower-level phrases are almost always neutral while full sentences
are much more likely to be biased (Figure
           4
           ). Due to this
discrepancy, the objective function in Eq. (
           6
           ) was minimized by making
neutral predictions for almost every node in the dataset.
          </p>
         </div>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        In this section we describe our experimental framework. We discuss strong
baselines that use lexical and syntactic information (including framing-specific features from previous work) as well as multiple
        RNN
        configurations. Each of these models have the same
task: to predict sentence-level ideology labels for sentences in a test set. To account for label imbalance, we subsample the data so that there are an equal
number of labels and report accuracy over this balanced dataset.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Baselines
       </h3>
       <li class="ltx_item">
        <div class="ltx_para" id="S4.SS1.p1">
         <p class="ltx_p">
          The
          random
          baseline chooses a label at random from
{
          liberal
          ,
          conservative
          }.
         </p>
         <li class="ltx_item">
          <div class="ltx_para" id="S4.SS1.p1.p1">
           <p class="ltx_p">
            lr
            1
            , our most basic logistic regression baseline, uses only
bag of words (
            BoW
            ) features.
           </p>
           <li class="ltx_item">
            <div class="ltx_para" id="S4.SS1.p1.p1.p1">
             <p class="ltx_p">
              lr
              2
              uses only
              BoW
              features. However,
              lr
              2
              also
includes phrase-level annotations as separate training
instances.
             </p>
             <li class="ltx_item">
              <div class="ltx_para" id="S4.SS1.p1.p1.p1.p1">
               <p class="ltx_p">
                lr
                3
                uses
                BoW
                features as well as syntactic pseudo-word
features from Greene &amp; Resnik
                [9]
                . These
features from dependency relations specify properties of verbs
(e.g., transitivity or nominalization).
               </p>
               <li class="ltx_item">
                <div class="ltx_para" id="S4.SS1.p1.p1.p1.p1.p1">
                 <p class="ltx_p">
                  lr
                  -(
                  w2v
                  )
                  is a logistic regression model trained on the
average of the pretrained word embeddings for each sentence
(Section
                  2.2
                  ).
                 </p>
                </div>
                <div class="ltx_para" id="S4.SS1.p1.p1.p1.p1.p2">
                 <p class="ltx_p">
                  The
                  lr
                  -(
                  w2v
                  )
                  baseline allows us to compare against a strong
lexical representation that encodes syntactic and semantic information without the
                  RNN
                  tree structure.
(
                  lr
                  1
                  ,
                  lr
                  2
                  ) offer a comparison to simple bag of words models, while the
                  lr
                  3
                  baseline contrasts traditional syntactic features with those learned by
                  RNN
                  models.
                 </p>
                </div>
               </li>
              </div>
             </li>
            </div>
           </li>
          </div>
         </li>
        </div>
       </li>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        rnn
        Models
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         For
         rnn
         models, we generate a feature vector for every node in the tree.
Equation
         2
         allows us to percolate the representations to the root of the
tree. We generate the final instance representation by concatenating the root
vector and the average of all other vectors
         [27]
         . We train
an
         L2
         -regularized logistic regression model over these concatenated vectors
to obtain final accuracy numbers on the sentence level.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         To analyze the effects of initialization and phrase-level annotations, we report
results for three different
         rnn
         settings. All three models were
implemented as described in Section
         2
         with the nonlinearity
         f
         set to the normalized
         tanh
         function,
        </p>
        f⁢(v)=tanh⁡(v)∥tanh⁡(v)∥.

(8)
        <p class="ltx_p">
         We perform 10-fold cross-validation on the training data to find the best
         rnn
         hyperparameters.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         We report results for
         rnn
         models with the following configurations:
        </p>
        <li class="ltx_item">
         <div class="ltx_para" id="S4.SS2.p3.p1">
          <p class="ltx_p">
           rnn
           1
           initializes all parameters randomly and uses only sentence-level labels for training.
          </p>
          <li class="ltx_item">
           <div class="ltx_para" id="S4.SS2.p3.p1.p1">
            <p class="ltx_p">
             rnn
             1-(
             w2v
             )
             uses the word2vec initialization described in Section
             2.2
             but is also trained on only sentence-level labels.
            </p>
            <li class="ltx_item">
             <div class="ltx_para" id="S4.SS2.p3.p1.p1.p1">
              <p class="ltx_p">
               rnn
               2-(
               w2v
               )
               is initialized using word2vec embeddings and also includes annotated
phrase labels in its training. For this model, we also introduce a hyperparameter
               β
               that weights the error at annotated nodes (
               1-β
               ) higher than
the error at unannotated nodes (
               β
               ); since we have more confidence in
the annotated labels, we want them to contribute more towards the objective
function.
              </p>
             </div>
             <div class="ltx_para" id="S4.SS2.p3.p1.p1.p2">
              <p class="ltx_p">
               For all RNN models, we set the word vector dimension
               d
               to 300 to facilitate
direct comparison against the
               lr
               -(
               w2v
               )
               baseline.
              </p>
             </div>
            </li>
           </div>
          </li>
         </div>
        </li>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Where Compositionality Helps Detect Ideological Bias
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In this section, we examine the
        rnn
        models to see why they improve over our baselines. We also give examples of sentences that are correctly classified by our best
        rnn
        model but incorrectly classified by all of the baselines. Finally, we investigate sentence constructions that our model cannot handle and offer possible explanations for these errors.
       </p>
      </div>
      <div class="ltx_paragraph" id="S5.SS2.SSS1.P1">
       <h5 class="ltx_title ltx_title_paragraph">
        Experimental Results
       </h5>
       <div class="ltx_para" id="S5.SS2.SSS1.P1.p1">
        <p class="ltx_p">
         Table
         1
         shows the
         rnn
         models outperforming the bag-of-words baselines as well as the word2vec baseline on both datasets. The increased accuracy suggests that the trained
         rnn
         s are capable of detecting bias polarity switches at higher levels in parse trees. While phrase-level annotations do not improve baseline performance, the
         rnn
         model significantly benefits from these annotations because the phrases are themselves derived from nodes in the network structure. In particular, the phrase annotations allow our best model to detect bias accurately in complex sentences that the baseline models cannot handle.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.SSS1.P1.p2">
        <p class="ltx_p">
         Initializing the
         rnn
         We
         matrix with word2vec embeddings
improves accuracy over randomly initialization by 1%. This is similar
to improvements from pretrained vectors from neural language models
         [27]
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.SSS1.P1.p3">
        <p class="ltx_p">
         We obtain better results on Convote than on
         ibc
         with both bag-of-words and
         rnn
         models. This result was unexpected since the Convote labels are noisier than the annotated
         ibc
         labels; however, there are three possible explanations for the discrepancy. First, Convote has twice as many sentences as
         ibc
         , and the extra training data might help the model more than
         ibc
         ’s better-quality labels. Second, since the sentences in Convote were originally spoken, they are almost half as short (21.3 words per sentence) as those in the
         ibc
         (42.2 words per sentence). Finally, some information is lost at every propagation step, so
         rnn
         s are able to model the shorter sentences in Convote more effectively than the longer
         ibc
         sentences.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS2.SSS1.P2">
       <h5 class="ltx_title ltx_title_paragraph">
        Qualitative Analysis
       </h5>
       <div class="ltx_para" id="S5.SS2.SSS1.P2.p1">
        <p class="ltx_p">
         As in previous work
         [27]
         , we visualize the learned vector space by
listing the most probable n-grams for each political affiliation in
Table
         2
         . As expected, conservatives emphasize values such as freedom and religion while disparaging excess government spending and their liberal opposition. Meanwhile, liberals inveigh against the gap between the rich and the poor while expressing concern for minority groups and the working class.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.SSS1.P2.p2">
        <p class="ltx_p">
         Our best model is able to accurately model the compositional effects of bias in sentences with complex syntactic structures. The first three sentences in Figure
         5
         were correctly classified by our best model (
         rnn
         2-(
         w2v
         )
         ) and incorrectly classified by all of the baselines. Figures
         5
         A and C show traditional conservative phrases, “free market ideology” and “huge amounts of taxpayer money”, that switch polarities higher up in the tree when combined with phrases such as “made worse by” and “saved by”. Figure
         5
         B shows an example of a bias polarity switch in the opposite direction: the sentence negatively portrays supporters of nationalized health care, which our model picks up on.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.SSS1.P2.p3">
        <p class="ltx_p">
         Our model often makes errors when polarity switches occur at nodes that are high
up in the tree. In Figure
         5
         D, “be used as an instrument to achieve charitable or social ends” reflects a liberal ideology, which the model predicts
correctly. However, our model is unable to detect the polarity switch when this
phrase is negated with “should not”. Since many different issues are discussed
in the
         ibc
         , it is likely that our dataset has too few examples of some of
these issues for the model to adequately learn the appropriate ideological
positions, and more training data would resolve many of these errors.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        A growing
        nlp
        subfield detects private states such as opinions,
sentiment, and beliefs
        [31, 19]
        from text. In general, work in this category tends to combine
traditional surface lexical modeling (e.g., bag-of-words) with
hand-designed syntactic features or lexicons. Here we review the most
salient literature related to the present paper.
       </p>
      </div>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        Automatic Ideology Detection
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         Most previous work on ideology detection ignores the syntactic
structure of the language in use in favor of familiar bag-of-words
representations for the sake of simplicity. For example, Gentzkow and
Shapiro
         [6]
         derive a “slant index” to
rate the ideological leaning of newspapers. A newspaper’s slant index
is governed by the frequency of use of partisan collocations of 2-3
tokens. Similarly, authors have relied on simple models of language
when leveraging inferred ideological positions. E.g.,
         Gerrish and Blei (2011)
         predict the voting patterns of
Congress members based on bag-of-words representations of bills and
inferred political leanings of those members.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         Recently,
         Sim et al. (2013)
         have proposed a model to infer
mixtures of ideological positions in documents, applied to
understanding the evolution of ideological rhetoric used by political
candidates during the campaign cycle. They use an
         hmm
         -based
model, defining the states as a set of fine-grained political
ideologies, and rely on a closed set of lexical bigram features
associated with each ideology, inferred from a manually labeled
ideological books corpus. Although it takes elements of discourse
structure into account (capturing the“burstiness” of ideological
terminology usage), their model explicitly ignores intrasentential
contextual influences of the kind seen in
Figure
         1
         . Other approaches on the document level use
topic models to analyze bias in news articles, blogs, and political
speeches
         [1, 15, 17]
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        Subjectivity Detection
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         Detecting subjective language, which conveys opinion or speculation, is a
related
         nlp
         problem. While sentences lacking subjective language may
contain ideological bias (e.g., the topic of the sentence), highly-opinionated
sentences likely have obvious ideological leanings. In addition,
sentiment and subjectivity analysis offers methodological approaches that can be
applied to automatic bias detection.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         Wiebe et al. (2004)
         show that low-frequency words and some collocations
are a good indicators of subjectivity. More recently,
         Recasens et al. (2013)
         detect biased words in sentences using indicator
features for bias cues such as hedges and factive verbs in addition to standard
bag-of-words and part-of-speech features. They show that this type of
linguistic information dramatically improves performance over several standard
baselines.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         Greene and Resnik (2009)
         also emphasize the connection between syntactic and
semantic relationships in their work on “implicit sentiment”, which refers to
sentiment carried by sentence structure and not word choice. They use syntactic
dependency relation features combined with lexical information to achieve then
state-of-the-art performance on standard sentiment analysis datasets. However,
these syntactic features are only computed for a thresholded list of
domain-specific verbs. This work extends their insight of modeling
sentiment as an interaction between syntax and semantics to
ideological bias.
        </p>
       </div>
       <div class="ltx_paragraph" id="S6.SS2.SSS1.P1">
        <h5 class="ltx_title ltx_title_paragraph">
         Future Work
        </h5>
        <div class="ltx_para" id="S6.SS2.SSS1.P1.p1">
         <p class="ltx_p">
          There are a few obvious directions in which this work can be
expanded. First, we can consider more nuanced political ideologies
beyond
          liberal
          and
          conservative
          . We show that it is
possible to detect ideological bias given this binary problem;
however, a finer-grained study that also includes neutral annotations
may reveal more subtle distinctions between ideologies. While
acquiring data with obscure political biases from the
          ibc
          or
Convote is unfeasible, we can apply a similar analysis to social media
(e.g., Twitter or Facebook updates) to discover how many different
ideologies propagate in these networks.
         </p>
        </div>
        <div class="ltx_para" id="S6.SS2.SSS1.P1.p2">
         <p class="ltx_p">
          Another direction is to implement more sophisticated
          rnn
          models
(along with more training data) for bias detection. We attempted to
apply syntactically-untied
          rnn
          s
          [25]
          to our
data with the idea that associating separate matrices for phrasal
categories would improve representations at high-level nodes. While
there were too many parameters for this model to work well here, other
variations might prove successful, especially with more data. Finally,
combining sentence-level and document-level models might improve bias
detection at both levels.
         </p>
        </div>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
