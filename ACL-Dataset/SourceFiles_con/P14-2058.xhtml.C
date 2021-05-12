<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Automation and Evaluation of the Keyword Method for Second Language Learning.
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
       In this paper, we combine existing NLP techniques with minimal supervision to build memory tips according to the keyword method, a well established mnemonic device for second language learning. We present what we believe to be the first extrinsic evaluation of a creative sentence generator on a vocabulary learning task. The results demonstrate that NLP techniques can effectively support the development of resources for second language learning.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       [1]itemsep=-3pt
      </p>
     </div>
     <span class="ltx_ERROR undefined">
      \algorithmicindent
     </span>
     <div class="ltx_para" id="p2">
      <p class="ltx_p">
       0.8em
       *EndIf
       *EndFor
       *EndWhile
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
        The keyword method is a mnemonic device
        []
        that is especially suitable for vocabulary acquisition in second language learning
        []
        . In this method, a
        target
        word in a foreign language L2 can be learned by a native speaker of another language L1 in two main steps: 1) one or more L1 words, possibly referring to a concrete entity, are chosen based on orthographic or phonetic similarity with the
target word; 2) an L1 sentence is constructed in which an association between the translation of the target word and the keyword(s) is established,
so that the learner, when seeing or hearing the word, immediately recalls
the keyword(s).
To illustrate, for teaching the Italian word
        cuore
        which means
        heart
        in English, the learner might be asked to imagine
        “a lonely heart with a hard core”
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The keyword method has already been proven to be a valuable teaching device. However, the preparation of the memorization tips for each new word is an activity that requires considerable time, linguistic competence and creativity.
To the best of our knowledge, there is only one study which attempts to automate the mechanism of the keyword method.
In
        []
        , we proposed to automate the keyword method by retrieving sentences from the Web. However, we did not provide any evaluation to demonstrate the effectiveness of our approach in a real life scenario. In addition, we observed that retrieval poses severe limitations in terms of recall and sentence quality, and it might incur copyright violations.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper, we overcome these limitations by introducing a semi-automatic system implementing the keyword method that builds upon the keyword selection mechanism of
        and combines it with a state-of-the-art creative sentence generation framework
        []
        .
We set up an experiment to simulate the situation in which a teacher needs to prepare material for a vocabulary teaching resource. According to our scenario, the teacher relies on automatic techniques to generate relatively few, high quality mnemonics in English to teach Italian vocabulary. She only applies a very light supervision in the last step of the process, in which the most suitable among the generated sentences are selected before being presented to the learners. In this stage, the teacher may want to consider factors which are not yet in reach of automatic linguistic processors, such as the evocativeness or the memorability of a sentence. We show that the automatically generated sentences help learners to establish memorable connections which augment their ability to assimilate new vocabulary. To the best of our knowledge, this work is the first documented extrinsic evaluation of a creative sentence generator on a real-world application.
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
        The effectiveness of the keyword method (KM) is a well-established fact
        []
        .
        found that using KM to teach French made learning easier and faster than conventional methods.
        compared the effectiveness of
three learning methods including the semantic mapping, rote memorization (i.e., memorization by pure repetition, with no mnemonic aid) and keyword on beginner learners of a second language.
Their results show that using KM
leads to better learning of second language vocabulary for beginners.
Similar results have been reported by
        and
        .
Besides all the experimental results demonstrating the effectiveness of KM, it is worthwhile to mention about the computational efforts to automate the mechanism. In
        []
        we proposed an automatic vocabulary teaching system which combines NLP and IR techniques to automatically generate memory tips for vocabulary acquisition. The system exploits orthographic and phonetic similarity metrics to find the best L2 keywords for each target L1 word.
Sentences containing the keywords and the translation of the target word are retrieved from the Web, but
we did not carry out an evaluation of the quality or the coverage of the retrieved sentences.
In
        we proposed an extensible framework for the generation of creative sentences in which users are able to force several words to appear in the sentences. While we had discussed the potentiality of creative sentence generation as a useful teaching device, we had not validated our claim experimentally yet. As a previous attempt at using NLP for education,
        employ a riddle generator to create a language playground for children with complex communication needs.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Memory tip generation
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Preparing memory tips based on KM includes two main ingredients: one or more keywords which are orthographically or phonetically similar to the L2 word to be learned; and a sentence in which the keywords and the translation of the target L2 word are combined in a meaningful way. In this section, we detail the process that we employed to generate such memory tips semi-automatically.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Target word selection and keyword generation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         We started by compiling a collection of Italian nouns consisting of three syllables from various resources for vocabulary teaching including
         http://didattica.org/italiano.htm
         and
         http://ielanguages.com
         , and produced a list of 185 target L2 words.
To generate the L1 keywords for each target word, we adopted a similar strategy to
         . For each L2 target word
         t
         , the keyword selection module generates a list of possible keyword pairs,
         K
         . A keyword pair
         k∈K
         can either consist of two non-empty strings, i.e.,
         k=[w0,w1]
         , or of one non-empty and one empty string, i.e.,
         w1=ϵ
         . Each keyword pair has the property that the concatenation of its elements is either orthographically or phonetically similar to the target word
         t
         . Orthographic and phonetic similarity are evaluated by means of the Levenshtein distance
         []
         . For orthographic similarity, the distance is calculated over the characters in the words, while for phonetic similarity it is calculated over the phonetic representations of
         t
         and
         w0+w1
         . We use the CMU pronunciation dictionary
         to retrieve the phonetic representation of English words. For Italian words, instead, their phonetic representation is obtained from an unpublished phonetic lexicon developed at FBK-irst.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Keyword filtering and ranking
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Unlike in
         []
         , where we did not enforce any constraints for selecting the keywords, in this case we applied a more sophisticated filtering and ranking strategy. We require at least one keyword in each pair to be a content word; then, we require that at least one keyword has length
         ≥
         3; finally, we discard pairs containing at least one proper noun.
We allowed the keyword generation module to consider all the entries in the CMU dictionary, and rank the keyword pairs based on the following criteria in decreasing order of precedence:
1) Keywords with a smaller orthographic/phonetic distance are preferred;
2) Keywords consisting of a single word are preferred over two words (e.g., for the target word
         lavagna
         , which means
         blackboard
         ,
         lasagna
         takes precedence over
         love
         and
         onion
         );
3) Keywords that do not contain stop words are preferred (e.g., for the target word
         pettine
         , which means
         comb
         , the keyword pair
         pet
         and
         inn
         is ranked higher than
         pet
         and
         in
         , since
         in
         is a stop word);
4) Keyword pairs obtained with orthographic similarity are preferred over those obtained with phonetic similarity, as learners might be unfamiliar with the phonetic rules of the target language. For example, for the target word
         forbice
         , which means
         scissors
         , the keyword pair
         for
         and
         bid
         is preferred to
         for
         and
         beach
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         We selected up to three of the highest ranked keyword pairs for each target word, obtaining 407 keyword combinations for the initial 185 Italian words, which we used as the input for the sentence generator.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Sentence generation
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         In this step, our goal was to generate, for each Italian word, sentences containing its L1 translation and the set of orthographically (or phonetically) similar keywords that we previously selected.
For each keyword combination, starting from the top-ranked ones, we generated up to 10 sentences by allowing any known part-of-speech for the keywords. The sentences were produced by the state of the art sentence generator of
         . The system relies on two corpora of automatic parses as a repository of sentence templates and lexical statistics. As for the former, we combined two resources: a corpus of 16,000 proverbs
         []
         and a collection of 5,000 image captions
         collected by
         . We chose these two collections since they offer a combination of catchy or simple sentences that we expect to be especially suitable for second language learning. As for the second corpus, we used LDC’s English GigaWord 5th Edition
         .
Of the 12 feature functions described in
         []
         , we only implemented the following scorers: Variety (to prevent duplicate words from appearing in the sentences); Semantic Cohesion (to enforce the generation of sentence as lexically related to the target words as possible); Alliteration, Rhyme and Plosive (to introduce hooks to echoic memory in the output); Dependency Operator and
         N
         -gram (to enforce output grammaticality).
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         We observed that the sentence generation module was not able to generate a sentence for 24% of the input configurations. For comparison, when we attempted to retrieve sentences from the Web as suggested in
         , we could collect an output for less than 10% of the input configurations. Besides, many of the retrieved sentences were exceedingly long and complex to be used in a second language learning experiment.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.4
        </span>
        Sentence selection
       </h3>
       <div class="ltx_para" id="S3.SS4.p1">
        <p class="ltx_p">
         For each L1 keyword pair obtained for each L2 target word, we allowed the system to output up to 10 sentences.
We manually assessed the quality of the generated sentences in terms of meaningfulness, evocativeness and grammaticality to select the most appropriate sentences to be used for the task.
In addition, for keyword pairs not containing the empty string, we prioritized the sentences in which the keywords were closer to each other. For example, let us assume that we have the keywords
         call
         and
         in
         for the target word
         collina
         . Among the sentences “
         The girl received a call in the bathroom
         ” and “
         Call the blond girl in case you need
         ”, the first one is preferred, since the keywords are closer to each other. Furthermore, we gave priority to the sentences that included the keywords in the right order. To illustrate, for the same keywords and the target words, we would prefer the sentence “
         I called him in the morning yesterday
         ” over “
         You talk a lot in a call
         ”.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS4.p2">
        <p class="ltx_p">
         Accordingly, for each target word in random order, we sequentially scanned the outputs generated for each keyword pair.
As soon as a sentence of adequate quality was found, we added it to our evaluation data and moved on to the next keyword. We continued this process until we selected a sentence for 40 distinct target words, which we set as the target size of the experiment. We had to inspect the outputs generated for 48 target words before we were able to select 40 good examples, meaning that for 17% of the target words the sentence generator could not produce a sentence of acceptable quality.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiment setup
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        For our experiment, we drew inspiration from
        . We compared the retention error rate of learners who tried to memorize new words with or without the aid of the automatically generated sentences. Through academic channels, we recruited 20 native English speakers with no prior knowledge of Italian.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        After obtaining the sentences as explained in Section
        3
        , we shuffled and then divided the whole set including 40 target words together with their translation, the generated keywords and sentences into 2 batches (A, B) and further divided each batch into 2 groups consisting of 10 elements (A1, A2, B1 and B2). The set of sentences assigned to each group is listed in Table
        1
        : Column “
        Target
        ” reports the Italian target word being taught; Column “
        Sentence
        ” shows the automatically generated sentence, where the translation of the target word is shown in bold and the keyword(s) in italic.
For the experiments, we randomly assigned each subject to one of the batches (A or B). Then, each subject was asked to memorize all the word pairs in a batch, but they would see the memory tips only for one of the two groups, which was again randomly assigned. This approach resulted in 4 different memorization exercises, namely 1) A1 with tips and A2 without, 2) A2 with tips and A1 without, 3) B1 with tips and B2 without, 4) B2 with tips and B1 without.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        When memorizing the translations without the aid of memory tips, the subjects were instructed to focus only on the Italian word and its English translation and to repeat them over and over in their mind. Conversely, when relying on the automatic memory tips the subjects were shown the word, its translation and the generated sentence including the keywords. In this case, the subjects were instructed to read the sentence over and over trying to visualize it.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        After going through each set of slides, we distracted the subjects with a short video in order to reset their short term memory. After that, their retention was tested. For each Italian word in the exercise, they were asked to select the English translation among 5 alternatives, including the correct translation and 4 other words randomly selected from the same group. In this way, the subjects would always have to choose among the words that they encountered during the exercise.
        We also added an extra option “
        I already knew this word
        ” that the subjects were instructed to select in case they already knew the Italian word prior to taking part in the experiment.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiment results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Table
        2
        summarizes the outcome of the experiment. The contribution of the automatically generated sentences to the learning task is assessed in terms of error rate-reduction, which we measure both within each group (rows 1-4) and on the whole evaluation set (rows 5-6). Due to the presence of the “
        I already knew this word
        ” option in the learning-assessment questionnaire, the number of the actual answers provided by each subject can be slightly different, hence the difference between macro- and micro-average.
       </p>
      </div>
      <div class="ltx_para" id="S5.p2">
       <p class="ltx_p">
        The error rate for each memorization technique
        t
        (where
        t=R
        for “Rote memorization” and
        t=K
        for “keyword-aided memorization”) is calculated as:
        et=itct+it
        ,
where
        ct
        and
        it
        are the number of correct and incorrect answers provided by the subjects, respectively. The absolute error rate reduction
        Δ⁢e
        is calculated as the absolute difference in error rate between rote and keyword-aided memorization, i.e.:
        Δe=eR-eK
        .
Finally, the relative error rate reduction
        %e
        is calculated as the the ratio between the absolute error rate reduction
        Δ⁢e
        and the error rate of rote memorization
        eR
        , i.e.,:
        %e=ΔeeR=eR-eKeR
        .
       </p>
      </div>
      <div class="ltx_para" id="S5.p3">
       <p class="ltx_p">
        The overall results (rows 5 and 6 in Table
        2
        ) show that vocabulary learning noticeably improves when supported by the generated sentences, with error rates dropping by almost 30% in terms of macro-average (almost 27% for micro-average). The breakdown of the error rate across the 4 groups shows a clear pattern. The results clearly indicate that one group (A1) by chance contained easier words to memorize as shown by the low error rate (between 3% and 4%) obtained with both methods. Similarly, groups A2 and B1 are of average difficulty, whereas group B2 appears to be the most difficult, with an error rate higher than 22% when using only rote memorization. Interestingly, there is a strong correlation (Pearson’s
        r=0.85
        ) between the difficulty of the words in each group (measured as the error rate on rote memorization) and the positive contribution of the generated sentences to the learning process. In fact, we can see how the relative error rate reduction
        %e
        increases from
        ∼
        17% (group A1) to almost 45% (group B2).
Based on the results obtained by
        , who showed that the keyword method results in better long-term word retention than rote memorization, we would expect the error rate reduction to be even higher in a delayed post-test.
All in all, these findings clearly support the claim that a state-of-the-art sentence generator can be successfully employed to support keyword-based second language learning.
After completing their exercise, the subjects were asked to provide feedback about their experience as learners. We set up a 4-items Likert scale
        []
        where each item consisted of a statement and a 5-point scale of values ranging from (1) [I strongly disagree] to (5) [I strongly agree].
The distribution of the answers to the questions is shown in Table
        3
        .
60% of the subjects acknowledged that the memory tips helped them in the memorization process; 45% found that the sentences were overall correct; 65% confirmed that the sentences were catchy and easy to remember; and 50% found the sentences to be overall witty although the sentence generator does not include a mechanism to generate humor. Finally, it is worth mentioning that none of the subjects noticed that the sentences were machine generated, which we regard as a very positive assessment of the quality of the sentence generation framework. From their comments, it emerges that the subjects actually believed that they were just comparing two memorization techniques.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
