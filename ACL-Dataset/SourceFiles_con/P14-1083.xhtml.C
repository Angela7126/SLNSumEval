<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Response-based Learning for Grounded Machine Translation.
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
       We propose a novel learning approach for statistical machine translation (SMT) that allows to extract supervision signals for structured learning from an extrinsic response to a translation input. We show how to generate responses by grounding SMT in the task of executing a semantic parse of a translated query against a database. Experiments on the
       Geoquery
       database show an improvement of about 6 points in F1-score for response-based learning over learning from references only on returning the correct answer from a semantic parse of a translated query. In general, our approach alleviates the dependency on human reference translations and solves the reachability problem in structured learning for SMT.
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
        In this paper, we propose a novel approach for learning and evaluation in statistical machine translation (SMT) that borrows ideas from response-based learning for grounded semantic parsing. In this framework, the meaning of a sentence is defined in the context of an extrinsic task. Successful communication of meaning is measured by a successful interaction in this task, and feedback from this interaction is used for learning.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        We suggest that in a similar way the preservation of meaning in machine translation should be defined in the context of an interaction in an extrinsic task. For example, in the context of a game, a description of a game rule is translated successfully if correct game moves can be performed based only on the translation. In the context of a question-answering scenario, a question is translated successfully if the correct answer is returned based only on the translation of the query.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We propose a framework of response-based learning that allows to extract supervision signals for structured learning from the response of an extrinsic task to a translation input. Here, learning proceeds by “trying out” translation hypotheses, receiving a response from interacting in the task, and converting this response into a supervision signal for updating model parameters. In case of positive feedback, the predicted translation can be treated as reference translation for a structured learning update. In case of negative feedback, a structural update can be performed against translations that have been approved previously by positive task feedback. This framework has several advantages:
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           The supervision signal in response-based learning has a different quality than supervision by human-generated reference translations. While a human reference translation is generated independently of the SMT task, conversion of predicted translations into references is always done with respect to a specific task. In this sense we speak of grounding meaning transfer in an extrinsic task.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Response-based learning can repeatedly try out system predictions by interacting in the extrinsic task. Instead of and in addition to learning from human reference translations, response-based learning allows to convert multiple system translations into references. This alleviates the supervision problem in cases where parallel data are scarce.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Task-specific response acts upon system translations. This avoids the problem of unreachability of independently generated reference translations by the SMT system.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        The proposed approach of response-based learning opens the doors for various extrinsic tasks in which SMT systems can be trained and evaluated. In this paper, we present a proof-of-concept experiment that uses feedback from a simulated world environment. Building on prior work in grounded semantic parsing, we generate translations of queries, and receive feedback by executing semantic parses of translated queries against the database. Successful response is defined as receiving the same answer from the semantic parses for the translation and the original query. Our experimental results show an improvement of about 6 points in F1-score for response-based learning over standard structured learning from reference translations. We show in an error analysis that this improvement can be attributed to using structural and lexical variants of reference translations as positive examples in response-based learning. Furthermore, translations produced by response-based learning are found to be grammatical. This is due to the possibility to boost similarity to human reference translations by the additional use of a cost function in our approach.
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
        The key idea of
        grounded language learning
        is to study natural language in the context of a non-linguistic environment, in which meaning is grounded in perception and/or action. This presents an analogy to human learning, where a learner tests her understanding in an actionable setting.
Such a setting can be a simulated world environment in which the linguistic representation can be directly executed by a computer system. For example, in semantic parsing, the learning goal is to produce and successfully execute a meaning representation. Executable system actions include access to databases such as the
        Geoquery
        database on U.S. geography (
        Wong and Mooney2006
        ,
        inter alia
        ), the
        Atis
        travel planning database (
        Zettlemoyer and Collins2009
        ,
        inter alia
        ), robotic control in simulated navigation tasks (
        Chen and Mooney2011
        ,
        inter alia
        ), databases of simulated card games (
        Goldwasser and Roth2013
        ,
        inter alia
        ), or the user-generated contents of
        Freebase
        (
        Cai and Yates2013
        ,
        inter alia
        ). Since there are many possible correct parses, matching against a single gold standard falls short of grounding in a non-linguistic environment. Rather, the semantic context for interpretation, as well as the success criterion in evaluation is defined by successful execution of an action in the extrinsic environment, e.g., by receiving the correct answer from the database or by successful navigation to the destination.
Recent attempts to learn semantic parsing from question-answer pairs without recurring to annotated logical forms have been presented by
        Kwiatowski et al.2013
        ,
        Berant et al.2013
        , or
        Goldwasser and Roth2013
        . The algorithms presented in these works are variants of structured prediction that take executability of semantic parses into account. Our work builds upon these ideas, however, to our knowledge the presented work is the first to embed translations into grounded scenarios in order to use feedback from interactions in these scenarios for structured learning in SMT.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        A recent important research direction in SMT has focused on employing automated translation as an aid to human translators.
        Computer assisted translation
        (CAT) subsumes several modes of interaction, ranging from binary feedback on the quality of the system prediction
        [Saluja et al.2012]
        , to human post-editing operations on a system prediction resulting in a reference translation
        [Cesa-Bianchi et al.2008]
        , to human acceptance or overriding of sentence completion predictions
        [Langlais et al.2000, Barrachina et al.2008, Koehn and Haddow2009]
        . In all interaction scenarios, it is important that the system learns dynamically from its errors in order to offer the user the experience of a system that adapts to the provided feedback. Since retraining the SMT model after each interaction is too costly,
        online adaptation
        after each interaction has become the learning protocol of choice for CAT. Online learning has been applied in generative SMT, e.g., using incremental versions of the EM algorithm
        [Ortiz-Martínez et al.2010, Hardt and Elming2010]
        , or in discriminative SMT, e.g., using perceptron-type algorithms
        [Cesa-Bianchi et al.2008, Martínez-Gómez et al.2012, Wäschle et al.2013, Denkowski et al.2014]
        .
In a similar way to deploying human feedback, extrinsic loss functions have been used to provide learning signals for SMT. For example,
        Nikoulina et al.2012
        propose a setup where an SMT system feeds into cross-language information retrieval, and receives feedback from the performance of translated queries with respect to cross-language retrieval performance. This feedback is used to train a reranker on an
        n
        -best list of translations order with respect to retrieval performance.
In contrast to our work, all mentioned approaches to interactive or adaptive learning in SMT rely on human post-edits or human reference translations. Our work differs from these approaches in that exactly this dependency is alleviated by learning from responses in an extrinsic task.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Interactive scenarios have been used for evaluation purposes of translation systems for nearly 50 years, especially using
        human reading comprehension
        testing
        [Pfafflin1965, Fuji1999, Jones et al.2005]
        , and more recently, using face-to-face conversation mediated via machine translation
        [Sakamoto et al.2013]
        . However, despite offering direct and reliable prediction of translation quality, the cost and lack of reusability has confined task-based evaluations involving humans to
        testing
        scenarios, but prevented a use for interactive
        training
        of SMT systems as in our work.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Lastly, our work is related to
        cross-lingual natural language processing
        such as cross-lingual question answering or cross-lingual information retrieval as conducted at recent evaluation campaigns of the CLEF initiative.
        While these approaches focus on improvements of the respective natural language processing task, our goal is to improve SMT by gathering feedback from the task.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Grounding SMT in Semantic Parsing
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this paper, we present a proof-of-concept of our ideas of embedding SMT into simulated world environments as used in semantic parsing. We use the well-known
        Geoquery
        database on U.S. geography for this purpose. Embedding SMT in a semantic parsing scenario means to define translation quality by the ability of a semantic parser to construct a meaning representation from the translated query, which returns the correct answer when executed against the database. If viewed as simulated gameplay, a valid game move in this scenario returns the correct answer to a translated query.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The diagram in Figure
        1
        gives a sketch of response-based learning from semantic parsing in the geographical domain. Given a manual German translation of the English query as source sentence, the SMT system produces an English target translation. This sentence is fed into a semantic parser that produces an executable parse representation
        ph
        . Feedback is generated by executing the parse against the database of geographical facts. Positive feedback means that the correct answer is received, i.e.,
        exec⁢(pg)=?exec⁢(ph)
        indicates that the same answer is received from the gold standard parse
        pg
        and the parse for the hypothesis translation
        ph
        ; negative feedback results in case a different or no answer is received.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The key advantage of response-based learning is the possibility to receive positive feedback even from predictions that differ from gold standard reference translations, but yet receive the correct answer when parsed and matched against the database. Such structural and lexical variation broadens the learning capabilities in contrast to learning from fixed labeled data.
For example, assume the following English query in the geographical domain, and assume positive feedback from executing the corresponding semantic parse against the geographical database:
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Name prominent elevations in the USA
        </p>
       </blockquote>
       <p class="ltx_p">
        The manual translation of the English original reads
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Nenne prominente Erhebungen in den USA
        </p>
       </blockquote>
       <p class="ltx_p">
        An automatic translation
        of the German string produces the result
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Give prominent surveys in the US
        </p>
       </blockquote>
       <p class="ltx_p">
        This translation will trigger negative task-based feedback: A comparison with the original allows the error to be traced back to the ambiguity of the German word
        Erhebung
        . Choosing a general domain translation instead of a translation appropriate for the geographical domain hinders the construction of a semantic parse that returns the correct answer from the database. An alternative translation might look as follows:
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Give prominent heights in the US
        </p>
       </blockquote>
       <p class="ltx_p">
        Despite a large difference to the original English string, key terms such as
        elevations
        and
        heights
        , or
        USA
        and
        US
        , can be mapped into the same predicate in the semantic parse, thus allowing to receive positive feedback from parse execution against the geographical database.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Response-based Online Learning
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Recent approaches to machine learning for SMT formalize the task of discriminating good from bad translations as a structured prediction problem.
Assume a joint feature representation
        ϕ⁢(x,y)
        of input sentences
        x
        and output translations
        y∈Y⁢(x)
        , and a linear scoring function
        s⁢(x,y;w)
        for predicting a translation
        y^
        (where
        ⟨⋅,⋅⟩
        denotes the standard vector dot product) s.t.
       </p>
       y^=arg⁢maxy∈Y⁢(x)⁡s⁢(x,y;w)=arg⁢maxy∈Y⁢(x)⁡⟨w,ϕ⁢(x,y)⟩.
       <p class="ltx_p">
        The structured perceptron algorithm
        [Collins2002]
        learns an optimal weight vector
        w
        by updating
        w
        on input
        x(i)
        by the following rule, in case the predicted translation
        y^
        is different from and scored higher than the reference translation
        y(i)
        :
       </p>
       w=w+ϕ⁢(x(i),y(i))-ϕ⁢(x(i),y^).
       <p class="ltx_p">
        This stochastic structural update aims to demote weights of features corresponding to incorrect decisions, and to promote weights of features for correct decisions.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        An application of structured prediction to SMT involves more than a straightforward replacement of labeled output structures by reference translations. Firstly, update rules that require to compute a feature representation for the reference translation are suboptimal in SMT, because often human-generated reference translations cannot be generated by the SMT system. Such “unreachable” gold-standard translations need to be replaced by “surrogate” gold-standard translations that are close to the human-generated translations and still lie within the reach of the SMT system. Computation of distance to the reference translation usually involves cost functions based on sentence-level BLEU (
        Nakov et al.2012
        ,
        inter alia
        ) and incorporates the current model score, leading to various ramp loss objectives described in
        Gimpel and Smith2012
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        An alternative approach to alleviate the dependency on labeled training data is response-based learning.
        Clarke et al.2010
        or
        Goldwasser and Roth2013
        describe a response-driven learning framework for the area of semantic parsing: Here a meaning representation is “tried out” by iteratively generating system outputs, receiving feedback from world interaction, and updating the model parameters. Applied to SMT, this means that we predict translations and use positive response from acting in the world to create “surrogate” gold-standard translations. This decreases the dependency on a few (mostly only one) reference translations and guides the learner to promote translations that perform well with respect to the extrinsic task.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        In the following, we will present a framework that combines standard structured learning from given reference translations with response-based learning from task-approved references. We need to ensure that gold-standard translations lead to positive task-based feedback, that means they can be parsed and executed successfully against the database. In addition, we can use translation-specific cost functions based on sentence-level BLEU in order to boost similarity of translations to human reference translations.
       </p>
      </div>
      <div class="ltx_para" id="S4.p5">
       <p class="ltx_p">
        We denote feedback by a binary execution function
        e⁢(y)∈{1,0}
        that tests whether executing the semantic parse for the prediction against the database receives the same answer as the parse for the gold standard reference. Our cost function
        c⁢(y(i),y)=(1-BLEU⁢(y(i),y))
        is based on a version of sentence-level BLEU
        Nakov et al.2012
        . Define
        y+
        as a surrogate gold-standard translation that receives positive feedback, has a high model score, and a low cost of predicting
        y
        instead of
        y(i)
        :
       </p>
       y+=arg⁢maxy∈Y⁢(x(i)):e⁢(y)=1⁡(s⁢(x(i),y;w)-c⁢(y(i),y)).
       <p class="ltx_p">
        The opposite of
        y+
        is the translation
        y-
        that leads to negative feedback, has a high model score, and a high cost. It is defined as follows:
       </p>
       y-=arg⁢maxy∈Y⁢(x(i)):e⁢(y)=0⁡(s⁢(x(i),y;w)+c⁢(y(i),y)).
       <p class="ltx_p">
        Update rules can be derived by minimization of the following ramp loss objective:
       </p>
       minw⁡(-maxy∈Y⁢(x(i)):e⁢(y)=1⁡(s⁢(x(i),y;w)-c⁢(y(i),y))+maxy∈Y⁢(x(i)):e⁢(y)=0⁡(s⁢(x(i),y;w)+c⁢(y(i),y))).
       <p class="ltx_p">
        Minimization of this objective using stochastic (sub)gradient descent
        [McAllester and Keshet2011]
        yields the following update rule:
       </p>
       w=w+ϕ⁢(x(i),y+)-ϕ⁢(x(i),y-).
       <p class="ltx_p">
        The intuition behind this update rule is to discriminate the translation
        y+
        that leads to positive feedback and best approximates (or is identical to) the reference within the means of the model from a translation
        y-
        which is favored by the model but does not execute and has high cost. This is done by putting all the weight on the former.
       </p>
      </div>
      <div class="ltx_para" id="S4.p6">
       <p class="ltx_p">
        Algorithm 1 presents pseudo-code for our response-driven learning scenario. Upon predicting translation
        y^
        , in case of positive feedback from the task, we treat the prediction as surrogate reference by setting
        y+←y^
        , and by adding it to the set of reference translations for future use. Then we need to compute
        y-
        , and update by the difference in feature representations of
        y+
        and
        y-
        , at a learning rate
        η
        . If the feedback is negative, we want to move the weights away from the prediction, thus we treat it as
        y-
        . To perform an update, we need to compute
        y+
        . If either
        y+
        or
        y-
        cannot be computed, the example is skipped.
       </p>
      </div>
      <div class="ltx_para" id="S4.p7">
       <p class="ltx_p">
        The sketched algorithm allows several variations. In the form depicted above, it allows to use human reference translations in addition to task-approved surrogate references. The cost function can be implemented by different versions of sentence-wise BLEU, or it can be omitted completely so that learning relies on task-based feedback alone, similar to algorithms recently suggested for semantic parsing
        [Goldwasser and Roth2013, Kwiatowski et al.2013, Berant et al.2013]
        . Lastly, regularization can be introduced by using update rules corresponding to primal form optimization variants of support vector machines
        [Collobert and Bengio2004, Chapelle2007, Shalev-Shwartz et al.2007]
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
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Experimental Setup
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         In our experiments, we use the
         Geoquery
         database on U.S. geography as provided by
         Jones et al.2012
         .
         The dataset includes 880 English questions and their logical forms. The English strings were manually translated into German by the authors of
         Jones et al.2012
         ), and corrected for typos by the authors of this paper. We follow the provided split into 600 training examples and 280 test examples.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         For response-based learning, we retrained the semantic parser of
         Andreas et al.2013
         on the full 880
         Geoquery
         examples in order to reach full parse coverage. This parser is itself based on SMT, trained on parallel data consisting of English queries and linearized logical forms, and on a language model trained on linearized logical forms. We used the hierarchical phrase-based variant of the parser.
Note that we do not use
         Geoquery
         test data in SMT training. Parser training includes
         Geoquery
         test data in order to be less dependent on parse and execution failures in the evaluation: If a translation system, response-based or reference-based, translates the German input into the gold standard English query it should be rewarded by positive task feedback. To double-check whether including the 280 test examples in parser training gives an unfair advantage to response-based learning, we also present experimental results using the original parser of
         Andreas et al.2013
         that is trained only on the 600
         Geoquery
         training examples.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         The bilingual SMT system used in our experiments is the state-of-the-art SCFG decoder
         cdec
         [Dyer et al.2010]
         . We built grammars using its implementation of the suffix array extraction method described in
         Lopez2007
         . For language modeling, we built a modified Kneser-Ney smoothed 5-gram language model using the English side of the training data.
We trained the SMT system on the English-German parallel web data provided in the
         Common Crawl
         [Smith et al.2013]
         dataset.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Compared Systems
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         Method 1 is the baseline system, consisting of the
         cdec
         SMT system trained on the
         Common Crawl
         data as described above. This system does not use any
         Geoquery
         data for training. Methods 2-4 use the 600 training examples from
         Geoquery
         for discriminative training only.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Variants of the response-based learning algorithm described above are implemented as a stand-alone tool that operates on
         cdec
         n
         -best lists of 10,000 translations of the
         Geoquery
         training data. All variants use sparse features of
         cdec
         as described in
         Simianer et al.2012
         that extract rule shapes, rule identifiers, and bigrams in rule source and target directly from grammar rules. Method 4, named
         Rebol
         , implements REsponse-Based Online Learning by instantiating
         y+
         and
         y-
         to the form described in Section
         4
         : In addition to the model score
         s
         , it uses a cost function
         c
         based on sentence-level BLEU
         [Nakov et al.2012]
         and tests translation hypotheses for task-based feedback using a binary execution function
         e
         . This algorithm can convert predicted translations into references by task-feedback, and additionally use the given original English queries as references. Method 2, named
         Exec
         , relies on task-execution by function
         e
         and searches for executable or non-executable translations with highest score
         s
         to distinguish positive from negative training examples. It does not use a cost function and thus cannot make use of the original English queries.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         We compare response-based learning with a standard structured prediction setup that omits the use of the execution function
         e
         in the definition of
         y+
         and
         y-
         . This algorithm can be seen as a stochastic (sub)gradient descent variant of
         Rampion
         [Gimpel and Smith2012]
         . It does not make use of the semantic parser, but defines positive and negative examples based on score
         s
         and cost
         c
         with respect to human reference translations.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         We report BLEU
         [Papineni et al.2001]
         of translation system output measured against the original English queries. Furthermore, we report precision, recall, and F1-score for executing semantic parses built from translation system outputs against the
         Geoquery
         database. Precision is defined as the percentage of correctly answered examples out of those for which a parse could be produced; recall is defined as the percentage of total examples answered correctly; F1-score is the harmonic mean of both. Statistical significance is measured using Approximate Randomization
         [Noreen1989]
         where result differences with a
         p
         -value smaller than
         0.05
         are considered statistically significant.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p5">
        <p class="ltx_p">
         Methods 2-4 perform structured learning for SMT on the 600
         Geoquery
         training examples and re-translate the 280 unseen
         Geoquery
         test data, following the data split of
         Jones et al.2012
         . Training for
         Rampion
         ,
         Rebol
         and
         Exec
         was repeated for 10 epochs. The learning rate
         η
         is set to a constant that is adjusted by cross-validation on the 600 training examples.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Empirical Results
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         We present an experimental comparison of the four different systems according to BLEU and F1, using an extended semantic parser (trained on 880
         Geoquery
         examples) and the original parser (trained on 600
         Geoquery
         training examples). The extended parser reaches and F1-score of
         99.64⁢%
         on the 280
         Geoquery
         test examples; the original parser yields an F1-score of
         82.76⁢%
         .
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         Table
         2
         reports results for the extended semantic parser. A system ranking according to F1-score shows about 6 points difference between the respective methods, ranking
         Rebol
         over
         Rampion
         ,
         Exec
         and
         cdec
         . The exploitation of task-feedback allows both
         Exec
         and
         Rebol
         to improve task-performance over the baseline.
         Rebol
         ’s combination of task feedback with a cost function achieves the best results since positively executable hypotheses and reference translations can both be exploited to guide the learning process. Since all English reference queries lead to positively executable parses in the setup that uses the extended semantic parser,
         Rampion
         implicitly also has access to task feedback. This allows
         Rampion
         to improve F1 over the baseline. All result differences are statistically significant.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         In terms of BLEU score measured against the original English
         Geoquery
         queries, the best nominal result is obtained by
         Rampion
         which uses them as reference translations.
         Rebol
         performs worse since BLEU performance is optimized only implicitly in cases where original English queries function as positive examples. However, the result differences between these two systems do not score as statistically significant. Despite not optimizing for BLEU performance against references, the fact that positively executable translations include the references allows even
         Exec
         to improve BLEU over
         cdec
         which does not use
         Geoquery
         data at all in training. This result difference is statistically significant.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         Table
         3
         compares the same systems using the original parser trained on 600 training examples. The system ranking according to F1-score shows the same ordering that is obtained when using an extended semantic parser. However, the respective methods are separated only by 3 or less points in F1 score such that only the result difference of
         Rebol
         over the baseline
         cdec
         and over
         Exec
         is statistically significant. We conjecture that this is due to a higher number of empty parses on the test set which makes this comparison unstable.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         In terms of BLEU measured against the original queries, the result differences between
         Rebol
         and
         Rampion
         are not statistically significant, and neither are the result differences between
         Exec
         and
         cdec
         . The result differences between systems of the former group and the systems of latter group are statistically significant.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Error Analysis
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         For a better understanding of the differences between the results produced by supervised and response-based learning, we conducted an error analysis on the test examples. Table
         4
         shows examples where the translation predicted by response-based learning (
         Rebol
         ) differs from the gold standard reference translation, but yet leads to positive feedback via a parse that returns the correct answer from the database. The examples show structural and lexical variation that leads to differences on the string level at equivalent positive feedback from the extrinsic task. This can explain the success of response-based learning: Lexical and structural variants of reference translations can be used to boost model parameters towards translations with positive feedback, while the same translations might be considered as negative examples in standard structured learning.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <p class="ltx_p">
         Table
         5
         shows examples where translations from
         Rebol
         and
         Rampion
         differ from the gold standard reference, and predictions by
         Rebol
         lead to positive feedback, while predictions by
         Rampion
         lead to negative feedback. Table
         6
         shows examples where translations from
         Rampion
         outperform translations from
         Rebol
         in terms of task feedback.
We see that predictions from both systems are in general grammatical. This can be attributed to the use of sentence-level BLEU as cost function in
         Rampion
         and
         Rebol
         . Translation errors of
         Rampion
         can be traced back to mistranslations of key terms (
         city
         versus
         capital
         ,
         limits
         or
         boundaries
         versus
         border
         ). Translation errors of
         Rebol
         more frequently show missing translations of terms.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
