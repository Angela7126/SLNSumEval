<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   An Empirical Study on the Effect of Negation Words on Sentiment.
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
       Negation words, such as
       no
       and
       not
       , play a fundamental
role in modifying sentiment of textual expressions. We will refer to a
negation word as the
       negator
       and the text span within the scope
of the negator as the
       argument
       . Commonly used heuristics to
estimate the sentiment of negated expressions rely simply on the
sentiment of argument (and not on the negator or the argument itself).
We use a sentiment treebank to show that these existing heuristics are
poor estimators of sentiment. We then modify these heuristics to be
dependent on the negators and show that this improves prediction.
Next, we evaluate a recently proposed composition model
       []
       that relies on both the negator and the
argument. This model learns the syntax and semantics of the negator’s
argument with a recursive neural network. We show that this approach
performs better than those mentioned above. In addition, we explicitly
incorporate the prior sentiment of the argument and observe that this
information can help reduce fitting errors.
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
        define negation to be “a grammatical
category that allows the changing of the truth value of a
proposition”. Negation is often expressed through the use of negative
signals or negators–words like
        isn’t
        and
        never
        , and
it can significantly affect the sentiment of its scope. Understanding
the impact of negation on sentiment is essential in automatic analysis
of sentiment. The literature contains interesting research attempting
to model and understand the behavior (reviewed in Section
        2
        ). For example, a simple yet influential hypothesis
posits that a negator reverses the sign of the sentiment value of the
modified text
        []
        . The
        shifting
        hypothesis
        []
        , however, assumes that negators change
sentiment values by a constant amount. In this paper, we refer to a
negation word as the
        negator
        (e.g.,
        isn’t
        ), a text
span being modified by and composed with a negator as the
        argument
        (e.g.,
        very good
        ), and entire phrase (e.g.,
        isn’t very good
        ) as the
        negated phrase
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The recently available Stanford Sentiment Treebank
        []
        renders manually annotated, real-valued sentiment scores for all
phrases in parse trees. This corpus provides us with the data to
further understand the quantitative behavior of negators, as the
effect of negators can now be studied with
        arguments
        of rich
syntactic and semantic variety. Figure
        1
        illustrates the effect of a common list of negators on sentiment as
observed on the Stanford Sentiment Treebank.
        Each dot in the figure corresponds to a
        negated phrase
        in the
treebank. The x-axis is the sentiment score of its
        argument
        s⁢(w→)
        and y-axis the sentiment score of the entire negated
phrase
        s⁢(wn,w→)
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We can see that the
        reversing
        assumption (the red diagonal
line) does capture some regularity of human perception, but rather
roughly. Moreover, the figure shows that same or similar
        s⁢(w→)
        scores (x-axis) can correspond to very different
        s⁢(wn,w→)
        scores (y-axis), which, to some degree, suggests the potentially
complicated behavior of negators.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        This paper describes a quantitative study of the effect of a list of
frequent negators on sentiment. We regard the negators’ behavior as an
underlying function embedded in annotated data; we aim to model this
function from different aspects. By examining sentiment compositions
of negators and arguments, we model the quantitative behavior of
negators in changing sentiment. That is, given a negated phrase
(e.g.,
        isn’t very good
        ) and the sentiment score of its
argument (e.g.,
        s⁢(`⁢`⁢v⁢e⁢r⁢y⁢g⁢o⁢o⁢d′′)=0.5
        ), we focus on understanding
the negator’s quantitative behavior in yielding the sentiment score of
the negated phrase
        s⁢(`⁢`⁢i⁢s⁢n′⁢t⁢v⁢e⁢r⁢y⁢g⁢o⁢o⁢d′′)
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We first evaluate the modeling capabilities of two influential
heuristics and show that they capture only very limited regularity of
negators’ effect. We then extend the models to be dependent on the
negators and demonstrate that such a simple extension can
significantly improve the performance of fitting to the human
annotated data. Next, we evaluate a recently proposed composition
model (Socher, 2013) that relies on both the negator and the
argument. This model learns the syntax and semantics of the negator’s
argument with a recursive neural network. This approach performs
significantly better than those mentioned above. In addition, we
explicitly incorporate the prior sentiment of the argument and observe
that this information helps reduce fitting errors.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Related work
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Automatic sentiment analysis
        The expression of
sentiment is an integral component of human language. In written text,
sentiment is conveyed with word senses and their composition, and in
speech also via prosody such as pitch
        []
        . Early work on
automatic sentiment analysis includes the widely cited work of
        []
        , among others. Since then,
there has been an explosion of research addressing various aspects of
the problem, including detecting subjectivity, rating and classifying
sentiment, labeling sentiment-related semantic roles (e.g., target of
sentiment), and visualizing sentiment (see surveys by
        and
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Negation modeling
        Negation is a general
grammatical category pertaining to the changing of the truth values of
propositions; negation modeling is not limited to sentiment. For
example, paraphrase and contradiction detection systems rely on
detecting negated expressions and opposites
        []
        . In
general, a negated expression and the opposite of the expression may
or may not convey the same meaning. For example,
        not alive
        has
the same meaning as
        dead
        , however,
        not tall
        does not
always mean
        short
        . Some automatic methods to detect opposites
were proposed by
        and
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Negation modeling for sentiment
        An early yet
influential
        reversing
        assumption conjectures that a negator
reverses the sign of the sentiment value of the modified text
        []
        , e.g., from +0.5 to -0.5, or vice versa. A
different hypothesis, called the
        shifting
        hypothesis in this
paper, assumes that negators change the sentiment values by a constant
amount
        []
        . Other approaches to negation modeling
have been discussed in
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        In the process of semantic composition, the effect of negators could
depend on the syntax and semantics of the text spans they modify. The
approaches of modeling this include bag-of-word-based models. For
example, in the work of
        []
        , a feature
        not_good
        will be created if the word
        good
        is encountered within a
predefined range after a negator.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        There exist different ways of incorporating more complicated syntactic
and semantic information. Much recent work considers sentiment
analysis from a semantic-composition
perspective
        []
        , which
achieved the state-of-the-art performance.
        used a
collection of hand-written compositional rules to assign sentiment
values to different granularities of text spans.
        proposed a learning-based framework. The more recent work of
        []
        proposed models based on recursive neural
networks that do not rely on any heuristic rules. Such models work in
a bottom-up fashion over the parse tree of a sentence to infer the
sentiment label of the sentence as a composition of the sentiment
expressed by its constituting parts. The approach leverages a
principled method, the forward and backward propagation, to learn a
vector representation to optimize the system performance. In principle
neural network is able to fit very complicated functions
        []
        , and in this paper, we adapt the
state-of-the-art approach described in
        []
        to help
understand the behavior of negators specifically.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Negation models based on heuristics
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We begin with previously proposed methods that leverage heuristics to
model the behavior of negators. We then propose to extend them to
consider lexical information of the negators themselves.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Non-lexicalized assumptions and modeling
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         In previous research, some influential, widely adopted assumptions
posit the effect of negators to be independent of both the
specific negators and the semantics and syntax of the arguments. In
this paper, we call a model based on such assumptions a
non-lexicalized model. In general, we can simply define this category
of models in Equation
         1
         . That is, the model parameters
are only based on the sentiment value of the arguments.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        s⁢(wn,w→)=deff⁢(s⁢(w→))

(1)
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.1
         </span>
         Reversing hypothesis
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS1.p1">
         <p class="ltx_p">
          A typical model falling into this
category is the
          reversing
          hypothesis discussed in Section
          2
          , where a negator simply reverses the sentiment
score
          s⁢(w→)
          to be
          -s⁢(w→)
          ; i.e.,
          f⁢(s⁢(w→))=-s⁢(w→)
          .
         </p>
        </div>
       </div>
       <div class="ltx_subsubsection" id="S3.SS1.SSS2">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          3.1.2
         </span>
         Shifting hypothesis
        </h4>
        <div class="ltx_para" id="S3.SS1.SSS2.p1">
         <p class="ltx_p">
          Basic shifting
          Similarly, a
          shifting
          based model depends on
          s⁢(w→)
          only, which can
be written as:
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS2.p2">
         f⁢(s⁢(w→))=s⁢(w→)-s⁢i⁢g⁢n⁢(s⁢(w→))*C

(2)
        </div>
        <div class="ltx_para" id="S3.SS1.SSS2.p3">
         <p class="ltx_p">
          where
          sign(.)
          is the standard
          sign
          function which
determines if the constant
          C
          should be added to or deducted from
          s⁢(wn)
          : the constant is added to a negative
          s⁢(w→)
          but
deducted from a positive one.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS1.SSS2.p4">
         <p class="ltx_p">
          Polarity-based shifting
          As will be shown
in our experiments, negators can have different shifting power when
modifying a positive or a negative phrase. Thus, we explore the use of
two different constants for these two situations, i.e.,
          f⁢(s⁢(w→))=s⁢(w→)-s⁢i⁢g⁢n⁢(s⁢(w→))*C⁢(s⁢i⁢g⁢n⁢(s⁢(w→)))
          . The
constant
          C
          now can take one of two possible values. We will show
that this simple modification improves the fitting performance
statistically significantly. Note also that instead of determining
these constants by human intuition, we use the training data to find
the constants in all shifting-based models as well as for the
parameters in other models.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Simple lexicalized assumptions
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         The above negation hypotheses rely on
         s⁢(w→)
         . As intuitively
shown in Figure
         1
         , the capability of the
non-lexicalized heuristics might be limited. Further semantic or
syntactic information from either the negators or the phrases they
modify could be helpful. The most straightforward way of expanding the
non-lexicalized heuristics is probably to make the models to be
dependent on the negators.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        s⁢(wn,w→)=deff⁢(wn,s⁢(w→))

(3)
       </div>
       <div class="ltx_para" id="S3.SS2.p3">
        <p class="ltx_p">
         Negator-based shifting
         We can simply
extend the basic shifting model above to consider the lexical
information of negators:
         f⁢(s⁢(w→))=s⁢(w→)-s⁢i⁢g⁢n⁢(s⁢(w→))*C⁢(wn)
         . That is, each
negator has its own
         C
         . We call this model
         negator-based
shifting
         . We will show that this model also statistically
significantly outperforms the basic shifting without overfitting,
although the number of parameters have increased.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p4">
        <p class="ltx_p">
         Combined shifting
         We further combine the
         negator-based shifting
         and
         polarity-based shifting
         above:
         f⁢(s⁢(w→))=s⁢(w→)-s⁢i⁢g⁢n⁢(s⁢(w→))*C⁢(wn,s⁢i⁢g⁢n⁢(s⁢(w→)))
         . This shifting model is based on negators and the
polarity of the text they modify: constants can be different for each
negator-polarity pair. The number of parameters in this model is the
multiplication of number of negators by two (the number of sentiment
polarities). This model further improves the fitting performance on
the test data.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Semantics-enriched modeling
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Negators can interact with arguments in complex ways. Figure
        1
        shows the distribution of the effect of
negators on sentiment without considering further semantics of the
arguments. The question then is that whether and how much
incorporating further syntax and semantic information can help better
fit or predict the negation effect. Above, we have considered the
semantics of the negators. Below, we further make the models to be
dependent on the arguments. This can be written as:
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       s⁢(wn,w→)=deff⁢(wn,s⁢(w→),r⁢(w→))

(4)
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        In the formula,
        r⁢(w→)
        is a certain type of representation for
the argument
        w→
        and it models the semantics or/and syntax of
the argument. There exist different ways of implementing
        r⁢(w→)
        . We consider two models in this study: one drops
        s⁢(w→)
        in Equation
        4
        and directly models
        f⁢(wn,r⁢(w→))
        . That is, the non-uniform information shown in
Figure
        1
        is not directly modeled. The
other takes into account
        s⁢(w→)
        too.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        For the former, we adopt the recursive neural tensor network (RNTN)
proposed recently by
        , which has showed to achieve
the state-of-the-art performance in sentiment analysis. For the
latter, we propose a prior sentiment-enriched tensor network (PSTN) to
take into account the prior sentiment of the argument
        s⁢(w→)
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        RNTN: Recursive neural tensor network
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         A recursive neural tensor network (RNTN) is a specific form of
feed-forward neural network based on syntactic (phrasal-structure)
parse tree to conduct compositional sentiment analysis. For
completeness, we briefly review it here. More details can be found in
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         As shown in the
         black
         portion of Figure
         2
         , each instance
of RNTN corresponds to a binary parse tree of a given sentence. Each
node of the parse tree is a fixed-length vector that encodes
compositional semantics and syntax, which can be used to predict the
sentiment of this node. The vector of a node, say
         p2
         in
Figure
         2
         , is computed from the
         d
         -dimensional vectors of its
two children, namely
         a
         and
         p1
         (a,p1∈ℝd×1)
         , with a non-linear function:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S4.E5">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           p2
          </td>
          <td class="ltx_td ltx_align_left">
           =t⁢a⁢n⁢h⁢([ap1]T⁢V[1:d]⁢[ap1]+W⁢[ap1])
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (5)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         where,
         W∈ℝd×(d+d)
         and
         V∈ℝ(d+d)×(d+d)×d
         are the matrix and tensor for the
composition function. A major difference of RNTN from the
conventional recursive neural network (RRN)
         []
         is the use of the tensor
         V
         in
order to directly capture the multiplicative interaction of two input
vectors, although the matrix
         W
         implicitly
         captures the
nonlinear interaction between the input vectors. The training of
RNTN uses conventional forward-backward propagation.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        PSTN: Prior sentiment-enriched tensor network
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         The non-uniform distribution in Figure
         1
         has showed certain correlations between the sentiment values of
         s⁢(wn,w→)
         and
         s⁢(w→)
         , and such information has been
leveraged in the models discussed in Section
         3
         . We
intend to devise a model that implements Equation
         4
         . It bridges between the models we have
discussed above that use either
         s⁢(w→)
         or
         r⁢(w→)
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         We extend RNTN to directly consider the sentiment information of
arguments. Consider the node
         p2
         in Figure
         2
         . When
calculating its vector, we aim to directly engage the sentiment
information of its right child, i.e., the argument. To this end, we
make use of the sentiment class information of
         p1
         , noted as
         p1s⁢e⁢n
         . As a result, the vector of
         p2
         is calculated as
follows:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx2">
         <tr class="ltx_equation ltx_align_baseline" id="S4.E6">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           p2
          </td>
          <td class="ltx_td ltx_align_left">
           =tanh([ap1]TV[1:d][ap1]+W[ap1]
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (6)
           </span>
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S4.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           +[ap1s⁢e⁢n]TVs⁢e⁢n[1:d][ap1s⁢e⁢n]+Ws⁢e⁢n[ap1s⁢e⁢n])
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         As shown in Equation
         6
         , for the node vector
         p1∈ℝd×1
         , we employ a matrix, namely
         Ws⁢e⁢n∈ℝd×(d+m)
         and a tensor,
         Vs⁢e⁢n∈ℝ(d+m)×(d+m)×d
         , aiming at explicitly capturing the
interplays between the sentiment class of
         p1
         , denoted as
         p1s⁢e⁢n
         (
         ∈ℝm×1
         ), and the negator
         a
         . Here, we assume the sentiment task has
         m
         classes. Following the
idea of
         , we regard the sentiment of
         p1
         as a
         prior
         sentiment as it has not been affected by the specific context
(negators), so we denote our method as prior sentiment-enriched tensor
network (PSTN). In Figure
         2
         , the
         red
         portion shows the
added components of PSTN.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         Note that depending on different purposes,
         p1s⁢e⁢n
         can take
the value of the automatically predicted sentiment distribution
obtained in forward propagation, the gold sentiment annotation of node
         p1
         , or even other normalized prior sentiment value or confidence
score from external sources (e.g., sentiment lexicons or external
training data). This is actually an interesting place to extend the
current recursive neural network to consider extrinsic
knowledge. However, in our current study, we focus on exploring the
behavior of negators. As we have discussed above, we will use the
human annotated sentiment for the arguments, same as in the models
discussed in Section
         3
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p6">
        <p class="ltx_p">
         With the new matrix and tensor, we then have
         θ=(V,Vs⁢e⁢n,W,Ws⁢e⁢n,Wl⁢a⁢b⁢e⁢l,L)
         as the PSTN model’s
parameters. Here,
         L
         denotes the vector representations of the word
dictionary.
        </p>
       </div>
       <div class="ltx_subsubsection" id="S4.SS2.SSS1">
        <h4 class="ltx_title ltx_title_subsubsection">
         <span class="ltx_tag ltx_tag_subsubsection">
          4.2.1
         </span>
         Inference and Learning
        </h4>
        <div class="ltx_para" id="S4.SS2.SSS1.p1">
         <p class="ltx_p">
          Inference and learning in PSTN follow a forward-backward propagation
process similar to that in
          []
          , and for completeness, we
depict the details as follows. To train the model, one first needs to
calculate the predicted sentiment distribution for each
node:
         </p>
         pis⁢e⁢n=Wl⁢a⁢b⁢e⁢l⁢pi,  pis⁢e⁢n∈ℝm×1
         <p class="ltx_p">
          and then compute the posterior probability
over the
          m
          labels:
         </p>
         yi=softmax⁢(pis⁢e⁢n)
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p2">
         <p class="ltx_p">
          During learning, following the method used by the RNTN model in
          []
          , PSTN also aims to minimize the cross-entropy error
between the predicted distribution
          yi∈ℝm×1
          at node
          i
          and the target distribution
          ti∈ℝm×1
          at that node. That is, the error for a
sentence is calculated as:
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p3">
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx3">
          <tr class="ltx_equation ltx_align_baseline" id="S4.E7">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            E⁢(θ)=∑i∑jtji⁢log⁢yji+λ⁢∥θ∥2
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
           <td class="ltx_align_middle ltx_align_right" rowspan="1">
            <span class="ltx_tag ltx_tag_equation">
             (7)
            </span>
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where,
          λ
          represents the regularization hyperparameters, and
          j∈m
          denotes the
          j
          -th element of the multinomial target distribution.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p4">
         <p class="ltx_p">
          To minimize
          E⁢(θ)
          , the gradient of the objective function with
respect to each of the parameters in
          θ
          is calculated
efficiently via backpropagation through structure, as proposed by
          . Specifically, we first
compute the prediction errors in all tree nodes bottom-up. After this
forward process, we then calculate the derivatives of the softmax
classifiers at each node in the tree in a top-down fashion. We will
discuss the gradient computation for the
          Vs⁢e⁢n
          and
          Ws⁢e⁢n
          in
detail next. Note that the gradient calculations for the
          V,W,Wl⁢a⁢b⁢e⁢l,L
          are the same as that of presented in
          []
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p5">
         <p class="ltx_p">
          In the backpropogation process of the training, each node (except the
root node) in the tree carries two kinds of errors: the local softmax
error and the error passing down from its parent node. During the
derivative computation, the two errors will be summed up as the
complement incoming error for the node. We denote the complete
incoming error and the softmax error vector for node
          i
          as
          δi,c⁢o⁢m∈ℝd×1
          and
          δi,s∈ℝd×1
          , respectively. With this notation, the error
for the root node
          p2
          can be formulated as follows.
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx4">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex4">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            δp2,c⁢o⁢m
           </td>
           <td class="ltx_td ltx_align_left">
            =δp2,s
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.E8">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            =(WT⁢(yp2-tp2))⊗f′⁢([a;p1])
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
          where
          ⊗
          is the Hadamard product between the two vectors and
          f′
          is the element-wise derivative of
          f=t⁢a⁢n⁢h
          . With the results
from Equation
          4.2.1
          , we then can calculate the derivatives for the
          Ws⁢e⁢n
          at node
          p2
          using the following equation:
         </p>
         ∂⁡Ep2Ws⁢e⁢n=δp2,c⁢o⁢m⁢([a;p1s⁢e⁢n])T
         <p class="ltx_p">
          Similarly, for the derivative of each slice
          k(k=1,…,d)
          of the
          Vs⁢e⁢n
          tensor, we have the following:
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx5">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex6">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            ∂⁡Ep2V[k]s⁢e⁢n=δkp2,c⁢o⁢m⁢[ap1s⁢e⁢n]⁢[ap1s⁢e⁢n]T
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p6">
         <p class="ltx_p">
          Now, let’s form the equations for computing the error for the two
children of the
          p2
          node. The difference for the error at
          p2
          and its two children is that the error for the latter will need to
compute the error message passing down from
          p2
          . We denote the
error passing down as
          δp2,d⁢o⁢w⁢n
          , where the left child and
the right child of
          p2
          take the 1
          s⁢t
          and 2
          n⁢d
          half of the
error
          δp2,d⁢o⁢w⁢n
          , namely
          δp2,d⁢o⁢w⁢n[1:d]
          and
          δp2,d⁢o⁢w⁢n[d+1:2d]
          , respectively. Following this notation,
we have the error message for the two children of
          p2
          , provided
that we have the
          δp2,d⁢o⁢w⁢n
          :
         </p>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p7">
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx6">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex7">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            δp1,c⁢o⁢m
           </td>
           <td class="ltx_td ltx_align_left">
            =δp1,s+δp2,d⁢o⁢w⁢n[d+1:2d]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex8">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            =(WT⁢(yp1-tp1))⊗f′⁢([b;c])
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex9">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            +δp2,d⁢o⁢w⁢n[d+1:2d]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p8">
         <p class="ltx_p">
          The incoming error message of node
          a
          can be calculated
similarly. Finally, we can finish the above equations with the
following formula for computing
          δp2,d⁢o⁢w⁢n
          :
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx7">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex10">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
            δp2,d⁢o⁢w⁢n
           </td>
           <td class="ltx_td ltx_align_left">
            =(WT⁢δp2,c⁢o⁢m)⊗f′⁢([a;p1])+δt⁢e⁢n⁢s⁢o⁢r
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
         <p class="ltx_p">
          where
         </p>
         <table class="ltx_equationgroup ltx_eqn_align" id="S7.EGx8">
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex11">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            δt⁢e⁢n⁢s⁢o⁢r=[δV[1:d]+δVs⁢e⁢n[1:d],δV[d+1:2d]]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex12">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            =∑k=1dδkp2,c⁢o⁢m(V[k]+(V[k])T)⊗f′([a;p1])[1:d]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex13">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            +∑k=1dδkp2,c⁢o⁢m(V[k]s⁢e⁢n+(V[k]s⁢e⁢n)T)⊗f′([a;p1s⁢e⁢n])[1:d]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
          <tr class="ltx_equation ltx_align_baseline" id="S4.Ex14">
           <td class="ltx_eqn_center_padleft">
           </td>
           <td class="ltx_td ltx_align_right">
           </td>
           <td class="ltx_td ltx_align_left">
            +∑k=1dδkp2,c⁢o⁢m(V[k]+(V[k])T)⊗f′([a;p1])[d+1:2d]
           </td>
           <td class="ltx_eqn_center_padright">
           </td>
          </tr>
         </table>
        </div>
        <div class="ltx_para" id="S4.SS2.SSS1.p9">
         <p class="ltx_p">
          After the models are trained, they are applied to predict the
sentiment of the test data. The original RNTN and the PSTN predict
5-class sentiment for each negated phrase; we map the output to
real-valued scores based on the scale that
          used
to map real-valued sentiment scores to sentiment
categories. Specifically, we conduct the mapping with the formula:
          pir⁢e⁢a⁢l=yi⋅[0.1 0.3 0.5 0.7 0.9]
          ; i.e., we calculate
the dot product of the posterior probability
          yi
          and the scaling
vector. For example, if
          yi=[0.5 0.5 0 0 0]
          , meaning this
phrase has a 0.5 probability to be in the first category (strong
negative) and 0.5 for the second category (weak negative), the
resulting
          pir⁢e⁢a⁢l
          will be 0.2 (0.5*0.1+0.5*0.3).
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiment set-up
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Data
        As described earlier, the Stanford Sentiment
Treebank
        []
        has manually annotated, real-valued
sentiment values for all phrases in parse trees. This provides us with
the training and evaluation data to study the effect of negators with
syntax and semantics of different complexity in a natural setting. The
data contain around 11,800 sentences from movie reviews that were
originally collected by
        . The sentences were parsed
with the Stanford parser
        []
        . The phrases at all tree
nodes were manually annotated with one of 25 sentiment values that
uniformly span between the positive and negative poles. The values are
normalized to the range of [0, 1].
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        In this paper, we use a list of most frequent negators that include the
words
        not
        ,
        no
        ,
        never
        , and their
combinations with auxiliaries (e.g.,
        didn’t
        ). We search these
negators in the Stanford Sentiment Treebank and normalize the same
negators to a single form; e.g.,
        “is n’t”
        ,
        “isn’t”
        , and
        “is not”
        are all normalized to
“is_not”. Each occurrence of a negator and the phrase it is directly
composed with in the treebank, i.e.,
        ⟨wn,w→⟩
        , is
considered a data point in our study. In total, we collected 2,261
pairs, including 1,845 training and 416 test cases. The split of
training and test data is same as specified in
        []
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        Evaluation metrics
        We use the mean absolute error
(MAE) to evaluate the models, which measures the averaged absolute
offsets between the predicted sentiment values and the gold
standard. More specifically, MAE is calculated as:
        M⁢A⁢E=1N⁢∑⟨wn,w→⟩|(s^⁢(wn,w→)-s⁢(wn,w→))|
        , where
        s^⁢(wn,w→)
        denotes the gold sentiment value and
        s⁢(wn,w→)
        the predicted one for the pair
        ⟨wn,w→⟩
        , and N is the total number of test instances. Note
that mean square error (MSE) is another widely used measure for
regression, but it is less intuitive for out task here.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Experimental results
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        Overall regression performance
        Table
        1
        shows the overall fitting performance of all
models. The first row of the table is a random baseline, which simply
guesses the sentiment value for each test case randomly in the range
[0,1]. The table shows that the basic
        reversing
        and
        shifting
        heuristics do capture negators’ behavior to some
degree, as their MAE scores are higher than that of the
baseline. Making the basic shifting model to be dependent on the
negators (model 4) reduces the prediction error significantly as
compared with the error of the basic shifting (model 3). The same is
true for the polarity-based shifting (model 5), reflecting that the
roles of negators are different when modifying positive and negative
phrases. Merging these two models yields additional improvement (model
6).
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Furthermore, modeling the syntax and semantics with the
state-of-the-art recursive neural network (model 7 and 8) can
dramatically improve the performance over model 6. The PSTN model,
which takes into account the human-annotated
        prior
        sentiment
of arguments, performs the best. This could suggest that additional
external knowledge, e.g., that from human-built resources or
automatically learned from other data (e.g., as in
        []
        ), including sentiment that cannot be inferred
from its constituent expressions, might be incorporated to benefit the
current neural-network-based models as
        prior
        knowledge.
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Note that the two neural network based models incorporate the syntax
and semantics by representing each node with a vector. One may
consider that a straightforward way of considering the semantics of
the modified phrases is simply memorizing them. For example, if a
phrase
        very good
        modified by a negator
        not
        appears
in the training and test data, the system can simply memorize the
sentiment score of
        not very good
        in training and use this
score at testing. When incorporating this memorizing strategy into
model (6), we observed a MAE score of 0.1222. It’s not surprising that
memorizing the phrases has some benefit, but such matching relies on
the exact reoccurrences of phrases. Note that this is a special case
of what the neural network based models can model.
       </p>
      </div>
      <div class="ltx_para" id="S6.p4">
       <p class="ltx_p">
        Discriminating negators
        The results in Table
        1
        has demonstrated the benefit of discriminating
negators. To understand this further, we plot in Figure
        3
        the behavior of different negators: the x-axis is a
subset of our negators and the y-axis denotes absolute shifting in
sentiment values. For example, we can see that the negator “is_never”
on average shifts the sentiment of the arguments by 0.26, which
is a significant change considering the range of sentiment value is
[0, 1]. For each negator, a 95% confidence interval is shown by the
boxes in the figure, which is calculated with the bootstrapping
resampling method. We can observe statistically significant
differences of shifting abilities between many negator pairs such as
that between “
        is_never
        ” and “
        do_not
        ” as well
as between “
        does_not
        ” and “
        can_not
        ”.
       </p>
      </div>
      <div class="ltx_para" id="S6.p5">
       <p class="ltx_p">
        Figure
        3
        also includes three diminishers (the white
bars), i.e.,
        barely
        ,
        unlikely
        , and
        superficial
        . By following
        []
        , we extracted 319
diminishers (also called
        understatement
        or
        downtoners
        ) from
        General
Inquirer
        . We
calculated their shifting power in the same manner as for the negators
and found three diminishers having shifting capability in the shifting
range of these negators. This shows that the boundary between negators
and diminishers can by fuzzy. In general, we argue that one should
always consider modeling negators individually in a sentiment analysis
system. Alternatively, if the modeling has to be done in groups, one
should consider clustering valence shifters by their shifting
abilities in training or external data.
       </p>
      </div>
      <div class="ltx_para" id="S6.p6">
       <p class="ltx_p">
        Figure
        4
        shows the shifting capacity of negators when
they modify positive (blue boxes) or negative phrases (red boxes). The
figure includes five most frequently used negators found in the
sentiment treebank. Four of them have significantly different shifting
power when composed with positive or negative phrases, which can
explain why the polarity-based shifting model achieves improvement
over the basic shifting model.
       </p>
      </div>
      <div class="ltx_para" id="S6.p7">
       <p class="ltx_p">
        Modeling syntax and semantics
        We have seen above that modeling syntax and semantics through
the-state-of-the-art neural networks help improve the fitting
performance. Below, we take a closer look at the fitting errors made
at different depths of the sentiment treebank. The
        depth
        here
is defined as the longest distance between the root of a
negator-phrase pair
        ⟨wn,w→⟩
        and their
descendant leafs. Negators appearing at deeper levels of the tree
tend to have more complicated syntax and semantics. In Figure
        5
        , the x-axis corresponds to different depths and
y-axis is the mean absolute errors (MAE).
       </p>
      </div>
      <div class="ltx_para" id="S6.p8">
       <p class="ltx_p">
        The figure shows that both RNTN and PSTN perform much better at all
depths than the model 6 in Table
        1
        . When the depths
are within 4, the RNTN performs very well and the (human annotated)
        prior
        sentiment of arguments used in PSTN does not bring
additional improvement over RNTN. PSTN outperforms RNTN at greater
depths, where the syntax and semantics are more complicated and harder
to model. The errors made by model 6 is bumpy, as the model considers
no semantics and hence its errors are not dependent on the depths. On
the other hand, the errors of RNTN and PSTN monotonically increase
with depths, indicating the increase in the task difficulty.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
