<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Improving the Recognizability of Syntactic Relations Using Contextualized Examples.
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
       A common task in qualitative data analysis is to characterize the usage of a linguistic entity by issuing queries over syntactic relations between words.
Previous interfaces for searching over syntactic structures require programming-style queries. User interface research suggests that it is easier to recognize a pattern than to compose it from scratch; therefore, interfaces for non-experts should show previews of syntactic relations. What these previews should look like is an open question that we explored with a 400-participant Mechanical Turk experiment. We found that syntactic relations are recognized with 34% higher accuracy when contextual examples are shown than a baseline of naming the relations alone. This suggests that user interfaces should display contextual examples of syntactic relations to help users choose between different relations.
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
        The ability to search over grammatical relationships between words is useful in many non-scientific fields. For example, a social scientist trying to characterize different perspectives on immigration might ask how adjectives applying to ‘immigrant’ have changed in the last 30 years. A scholar interested in gender might search a collection to find out whether different nouns enter into possessive relationships with ‘his’ and ‘her’
        [14]
        . In other fields, grammatical queries can be used to develop patterns for recognizing entities in text, such as medical terms
        [6, 13]
        , and products and organizations
        [3]
        , and for coding qualitative data such as survey results.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Most existing interfaces for syntactic search (querying over grammatical and syntactic structures) require structured query syntax. For example, the popular Stanford Parser includes Tregex, which allows for sophisticated regular expression search over syntactic tree structures
        [12]
        .
The Finite Structure Query tool for querying syntactically annotated corpora requires its queries to be stated in first order logic
        [9]
        . In the Corpus Query Language
        [8]
        , a query is a pattern of attribute-value pairs, where values can include regular expressions containing parse tree nodes and words.
Several approaches have adopted XML representations and the associated query language families of XPATH and SPARQL. For example, LPath augments XPath with additional tree operators to give it further expressiveness
        [11]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        However, most potential users do not have programming expertise, and are not likely to be at ease composing rigidly-structured queries. One survey found that even though linguists wished to make very technical linguistic queries, 55% of them did not know how to program
        [20]
        . In another
        [5]
        , humanities scholars and social scientists are frequently skeptical of digital tools, because they are often difficult to use. This reduces the likelihood that existing structured-query tools for syntactic search will be usable by non-programmers
        [15]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        A related approach is the query-by-example work seen in the past in interfaces to database systems
        [1]
        . For instance, the Linguist’s Search Engine
        [17]
        uses a query-by-example strategy in which a user types in an initial sentence in English, and the system produces a graphical view of a parse tree as output, which the user can alter.
The user can either click on the tree or modify the LISP expression to generalize the query. SPLICR also contains a graphical tree editor tool
        [16]
        .
According to Shneiderman and Plaisant
        [18]
        , query-by-example has largely fallen out of favor as a user interface design approach. A downside of QBE is that the user must manipulate an example to arrive at the desired generalization.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        More recently auto-suggest, a faster technique that does not require the manipulation of query by example, has become a widely-used approach in search user interfaces with strong support in terms of its usability
        [2, 21, 7]
        . A list of selectable options is shown under the search bar, filtered to be relevant as the searcher types. Searchers can recognize and select the option that matches their information need, without having to generate the query themselves.
       </p>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        The success of auto-suggest depends upon showing users options they can recognize. However, we know of no prior work on how to display grammatical relations so that they can be easily recognized. One current presentation (not used with auto-suggest) is to name the relation and show blanks where the words that satisfy it would appear as in
        X is the subject of Y
        [14]
        ; we used this as the baseline presentation in our experiments because it employs the relation definitions found in the Stanford Dependency Parser’s manual
        [4]
        . Following the principle of recognition over recall, we hypothesized that showing contextualized usage examples would make the relations more recognizable.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Our results confirm that showing examples in the form of words or phrases significantly improves the accuracy with which grammatical relationships are recognized over the standard baseline of showing the relation name with blanks. Our findings also showed that clausal relationships, which span longer distances in sentences, benefited significantly more from example phrases than either of the other treatments.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        These findings suggest that a query interface in which a user enters a word of interest and the system shows candidate grammatical relations augmented with examples from the text will be more successful than the baseline of simply naming the relation and showing gaps where the participating words appear.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Experiment
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We gave participants a series of identification tasks. In each task, they were shown a list of sentences containing a particular syntactic relationship between highlighted words. They were asked to identify the relationship type from a list of four options. We presented the options in three different ways, and compared the accuracy.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        We chose Amazon’s Mechanical Turk (MTurk) crowdsourcing platform as a source of study participants. The wide range of backgrounds provided by MTurk is desirable because our goal is to find a representation that is understandable to most people, not just linguistic experts or programmers. This platform has become widely used for both obtaining language judgements and for usability studies
        [10, 19]
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Our hypothesis was:
       </p>
       <blockquote class="ltx_quote">
        <p class="ltx_p">
         Grammatical relations are identified more accurately when shown with examples of contextualizing words or phrases than without.
        </p>
       </blockquote>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        To test it, participants were given a series of identification tasks. In each task, they were shown a list of 8 sentences, each containing a particular relationship between highlighted words. They were asked to identify the relationship from a list of 4 choices. Additionally, one word was chosen as a
        focus word
        that was present in all the sentences, to make the relationship more recognizable (“life” in Figure
        4
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        The choices were displayed in 3 different ways (Figure
        4
        ). The
        baseline
        presentation
(Figure
        4
        ) named the linguistic relation and showed a blank space with a pink background for the varying word in the relationship, the focus word highlighted in yellow and underlined, and any necessary additional words necessary to convey the relationship (such as “of” for the prepositional relationship “of”, the third option).
       </p>
      </div>
      <div class="ltx_para" id="S2.p6">
       <p class="ltx_p">
        The
        words
        presentation showed the baseline design, and in addition beneath was the word “Examples:” followed by a list of 4 example words that could fill in the pink blank slot (Figure
        4
        ). The
        phrases
        presentation again showed the baseline design, beneath which was the phrase “Patterns like:” and a list of 4 example phrases in which fragments of text including both the pink and the yellow highlighted portions of the relationship appeared (Figure
        4
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p7">
       <p class="ltx_p">
        Method:
        We used a between-subjects design. The task order and the choice order were not varied: the only variation between participants was the presentation of the choices. To avoid the possibility of guessing the right answer by pattern-matching, we ensured that there was no overlap between the list of sentences shown, and the examples shown in the choices as words or phrases.
       </p>
      </div>
      <div class="ltx_para" id="S2.p8">
       <p class="ltx_p">
        Tasks:
        The tasks were generated using the Stanford Dependency Parser
        [4]
        on the text of
        Moby Dick
        by Herman Melville. We tested the 12 most common grammatical relationships in the novel in order to cover the most content and to be able to provide as many real examples as possible. These relationships fell into two categories, listed below with examples.
       </p>
      </div>
      <div class="ltx_para" id="S2.p9">
       <p class="ltx_p">
        Clausal or long-distance relations:
       </p>
       <ul class="ltx_itemize">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Adverbial clause:
           I walk while talking
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Open clausal complement:
           I love to sing
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Clausal complement:
           he saw us leave
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i4.p1">
          <p class="ltx_p">
           Relative clause modifier:
           the letter I wrote reached
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p10">
       <p class="ltx_p">
        Non-clausal relations:
       </p>
       <ul class="ltx_itemize">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           Subject of verb:
           he threw the ball
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           Object of verb:
           he threw the ball
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           Adjective modifier
           red ball
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i4.p1">
          <p class="ltx_p">
           Preposition (in):
           a hole in a bucket
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i5" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i5.p1">
          <p class="ltx_p">
           Preposition (of):
           the piece of cheese
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i6" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i6.p1">
          <p class="ltx_p">
           Conjunction (and)
           mind and body
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i7" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i7.p1">
          <p class="ltx_p">
           Adverb modifier:
           we walk slowly
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i8" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i8.p1">
          <p class="ltx_p">
           Noun compound:
           Mr. Brown
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p11">
       <p class="ltx_p">
        We tested each of these 12 relations with 4 different focus words, 2 in each role. For example, the
        Subject of Verb
        relation was tested in the following forms:
       </p>
       <ul class="ltx_itemize">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           (Ahab, ___)
           : the sentences each contained ‘Ahab’, highlighted in yellow, as the subject of different verbs highlighted in pink.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           (captain, ___)
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i3.p1">
          <p class="ltx_p">
           (___, said)
           : the sentences each contained the verb ‘said’, highlighted in yellow, but with different subjects, highlighted in pink.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I3.i4" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i4.p1">
          <p class="ltx_p">
           (___, stood)
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S2.p12">
       <p class="ltx_p">
        To maximize coverage, yet keep the total task time reasonable (average 6.8 minutes), we divided the relations above into 4 task sets, each testing recognition of 3 different relations. Each of relations was tested with 4 different words, making a total of 12 tasks per participant.
       </p>
      </div>
      <div class="ltx_para" id="S2.p13">
       <p class="ltx_p">
        Participants:
        400 participants completed the study distributed randomly over the 4 task sets and the 3 presentations. Participants were paid 50c (U.S.) for completing the study, with an additional 50c bonus if they correctly identified 10 or more of the 12 relationships. They were informed of the possibility of the bonus before starting.
       </p>
      </div>
      <div class="ltx_para" id="S2.p14">
       <p class="ltx_p">
        To gauge their syntactic familiarity, we also asked them to rate how familiar they were with the terms ‘adjective’ (88% claimed they could define it), ‘infinitive’ (43%), and ‘clausal complement’ (18%). To help ensure the quality of effort, we included a multiple-choice screening question, “What is the third word of this sentence?” The 27 participants (out of 410) who answered incorrectly were eliminated.
       </p>
      </div>
      <div class="ltx_para" id="S2.p15">
       <p class="ltx_p">
        Results:
        The results (Figure
        5
        ) confirm our hypothesis. Participants in conditions that showed examples (
        phrases
        and
        words
        ) were significantly more accurate at identifying the relations than participants in the
        baseline
        condition. We used the Wilcoxson signed-rank test, an alternative to the standard T-test that does not assume samples are normally distributed. The average success rate in the
        baseline
        condition was 41%, which is significantly less accurate than
        words
        : 52%, (p=0.00019, W=6136), and
        phrases
        : 55%, (p=0.00014, W=5546.5).
       </p>
      </div>
      <div class="ltx_para" id="S2.p16">
       <p class="ltx_p">
        Clausal relations operate over longer distances in sentences, and so it is to be expected that showing longer stretches of context would perform better in these cases; that is indeed what the results showed.
Phrases significantly outperformed words and baseline for clausal relations. The average success rate was 48% for
        phrases
        , which is significantly more than
        words
        : 38%, (p=0.017 W=6976.5) and
        baseline
        : 24%, (p=1.9
        ×10-9
        W=4399.0), which was indistinguishable from random guessing (25%). This is a strong improvement, given that only 18% of participants reported being able to define ‘clausal complement’.
       </p>
      </div>
      <div class="ltx_para" id="S2.p17">
       <p class="ltx_p">
        For the non-clausal relations, there was no significant difference between
        phrases
        and
        words
        , although they were both overall significantly better than the baseline (words: p=0.0063 W=6740, phrases: p=0.023 W=6418.5). Among these relations, adverb modifiers stood out (Figure
        5
        ), because evidence suggested that
        words
        (63% success) made the relation more recognizable than
        phrases
        (47% success, p=0.056, W=574.0) – but the difference was only almost significant, due to the smaller sample size (only 96 participants encountered this relation). This may be because the words are the most salient piece of information in an adverbial relation – adverbs usually end in ‘ly’ – and in the phrases condition the additional information distracts from recognition of this pattern.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Acknowledgements
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We thank Björn Hartmann for his helpful comments. This work is supported by National Endowment for the Humanities grant HK-50011.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
