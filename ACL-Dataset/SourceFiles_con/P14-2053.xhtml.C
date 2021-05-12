<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Linguistic Considerations in Automatic Question Generation.
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
       As students read expository text, comprehension is improved by pausing to answer questions that reinforce the material. We describe an automatic question generator that uses semantic pattern recognition to create questions of varying depth and type for self-study or tutoring. Throughout, we explore how linguistic considerations inform system design. In the described system, semantic role labels of source sentences are used in a domain-independent manner to generate both questions and answers related to the source sentence. Evaluation results show a 44% reduction in the error rate relative to the best prior systems, averaging over all metrics, and up to 61% reduction in the error rate on grammaticality judgments.
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
        Studies of student learning show that answering questions increases depth of student learning, facilitates transfer learning, and improves students’ retention of material (McDaniel et al., 2007; Carpenter, 2012; Roediger and Pyc, 2012). The aim of this work is to automatically generate questions for such pedagogical purposes.
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
        Approaches to automatic question generation from text span nearly four decades. The vast majority of systems generate questions by selecting one sentence at a time, extracting portions of the source sentence, then applying transformation rules or patterns in order to construct a question. A well-known early work is Wolfe’s AUTOQUEST (Wolfe, 1976), a syntactic pattern matching system. A recent approach from Heilman and Smith (2009, 2010) uses syntactic parsing and transformation rules to generate questions. Syntactic, sentence-level approaches outnumber other approaches as seen in the Question Generation Shared Task Evaluation Challenge 2010 (Boyer and Piwek, 2010) which received only one paragraph-level, semantic entry. Argawal, Shah and Mannem (2011) continue the paragraph-level approach using discourse cues to find appropriate text segments upon which to construct questions at a deeper conceptual level. The uniqueness of their work lies in their use of discourse cues to extract semantic content for question generation. They generate questions of types:
        why
        ,
        when
        ,
        give an example
        , and
        yes/no
        .
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        In contrast to the above systems, other approaches have an intermediate step of transforming input into some sort of semantic representation. Examples of this intermediate step can be found in Yao and Zhang (2010) which uses Minimal Recursive Semantics, and in Olney et al. (2012) which uses concept maps. These approaches can potentially ask deeper questions due to their focus on semantics. A novel question generator by Curto et al. (2012) leverages lexico-syntactic patterns gleaned from the web with seed question-answer pairs.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        Another recent approach is Lindberg et al. (2013), which used semantic role labeling to identify patterns in the source text from which questions can be generated. This work most closely parallels our own with a few exceptions: our system only asks questions that can be answered from the source text, our approach is domain-independent, and the patterns also identify the answer to the question.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Approach
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        The system consists of a straightforward pipeline. First, the source text is divided into sentences which are processed by SENNA
        software, described in (Collobert et al., 2011). SENNA provides the tokenizing, pos tagging, syntactic constituency parsing and semantic role labeling used in the system. SENNA produces separate semantic role labels for each predicate in the sentence. For each predicate and its associated semantic arguments, a matcher function is called which will return a list of patterns that match the source sentence’s predicate-argument structure. Then questions are generated and stored by question type in a question hash table.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Generation patterns specify the text, verb forms and semantic arguments from the source sentence to form the question. Additionally, patterns indicate the semantic arguments that provide the answer to the question, required fields, and filter condition fields. As these patterns are matched, they will be rejected as candidates for generation for a particular sentence if the required arguments are absent or if filter conditions are present. For example, a filter for personal pronouns will prevent a question being generated with an argument that starts with a personal pronoun. From:
        It means that the universe is expanding
        , we do not want to generate a vague question such as:
        What does it mean?
        Coreference resolution, which could help avoid vague question generation, is discussed in Section 5. Table 1 shows selected required and filter fields, Section 3.3 gives examples of their use.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Patterns specify whether verbs should be included in their lexical form or as they appear in the source text. Either form will include subsequent particles such as: The lungs
        take in
        air. The most common use of the verb as it appears in the sentence is with the verb
        be
        , as in: What
        were
        fused into helium nuclei? This pattern takes the copular
        be
        as it appears in the source text. However, most patterns use the lexical form of the main verb along with the appropriate form of the auxiliary
        do
        (do, does, did), for the subject-auxiliary inversion required in forming interrogatives.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Pattern Authoring
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The system at the time of this evaluation had 42 patterns. SENNA uses the 2005 PropBank coding scheme and we followed the documentation in (Babko-Malaya, 2005) for the patterns. The most commonly used semantic roles are A0, A1 and A2, as well as the ArgM modifiers.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Software Tools and Source Text
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         The system was created using SENNA and Python. Importing NLTK within Python provides a simple interface to WordNet from which we determine the lexical form of verbs. SENNA provided all the necessary processing of the data, quickly, accurately and in one run.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         In order to generate questions, passages were selected from science textbooks downloaded from www.ck12.org. Textbooks were chosen rather than hand-crafted source material so that a more realistic assessment of performance could be achieved. For the experiments in this paper, we selected three passages from the subjects of biology, chemistry, and earth science, filtering out references to equations and figures. The passages average around 60 sentences each, and represent chapter sections. The average grade level is approximately grade 10 as indicated by the on-line readability scorer read-able.com.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Examples
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Table 2 provides examples of generated questions. The pattern that generated Question 1 requires argument A1 (underlined in Table 2) and a causation ArgM (italicized). The pattern also filters out sentences with A0 or A2. The patterns are designed to match only the arguments used as part of the question or the answer, in order to prevent over generation of questions. The system inserted the correct forms of
         release
         and
         do
         , and ignored the phrase
         As this occurs
         since it is not part of the semantic argument.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p2">
        <p class="ltx_p">
         The pattern that generated Question 2 requires A0, A1 and a verb whose lexical form is
         mean
         (V=mean in Table 1). In this pattern, A1 (italicized) forms the answer and A0 (underlined) becomes part of the question along with the appropriate form of
         do
         . This pattern supplies the word
         indicate
         instead of the source text’s
         mean
         which broadens the question context.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p3">
        <p class="ltx_p">
         Question 3 is from the source sentence’s 3rd predicate-argument set because this matched the pattern requirements: A1, A2, V=call. The answer is the text from the A2 argument. The ability to generate questions from any predicate-argument set means that sentence simplification is not required as a preprocessing step, and that the sentence can match multiple patterns. For example, this sentence could also match patterns to generate questions such as:
         What are positively charged particles called?
         or
         Describe the nucleus
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS3.p4">
        <p class="ltx_p">
         Question 4 requires A1 and an ArgM that includes the discourse cue
         if
         . The ArgM (underlined) becomes part of the question, while the rest of the source sentence forms the answer. This pattern also requires that ArgM contain nouns (AxNN from Table 1), which helps filter vague questions.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Results
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        This paper focuses on evaluating generated questions primarily in terms of their linguistic quality, as did Heilman and Smith (2010a). In a related work (Mazidi and Nielsen, 2014) we evaluated the quality of the questions and answers from a pedagogical perspective, and our approach outperformed comparable systems in both linguistic and pedagogical evaluations. However, the task here is to explore the linguistic quality of generated questions. The annotators are university students who are science majors and native speakers of English. Annotators were given instructions to read a paragraph, then the questions based on that paragraph. Two annotators evaluated each set of questions using Likert-scale ratings from 1 to 5, where 5 is the best rating, for grammaticality, clarity, and naturalness. The average inter-annotator agreement, allowing a difference of one between the annotators’ ratings was 88% and Pearson’s r=0.47 was statistically significant (p&lt;0.001), suggesting a high correlation and agreement between annotators. The two annotator ratings were averaged for all the evaluations reported here.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We present results on three linguistic evaluations: (1) evaluation of our generated questions, (2) comparison of our generated questions with those from Heilman and Smith’s question generator, and (3) comparison of our generated questions with those from Lindberg, Popowich, Nesbit and Winne. We compared our system to the H&amp;S and LPN&amp;W systems because they produce questions that are the most similar to ours, and for the same purpose: reading comprehension reinforcement. The Heilman and Smith system is available online;
        Lindberg graciously shared his code with us.
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Evaluation of our Generated Questions
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         This evaluation was conducted with one file (Chemistry: Bonds) which had 59 sentences, from which the system generated 142 questions. The purpose of this evaluation was to determine if any patterns consistently produce poor questions. The average linguistics score per pattern in this evaluation was 5.0 to 4.18. We were also interested to know if first predicates make better questions than later ones. The average score by predicate position is shown in Table 3. Note that the Rating column gives the average of the grammaticality, clarity and naturalness scores.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         Based on this sample of questions there is no significant difference in linguistic scores for questions generated at various predicate positions. Some question generation systems simplify complex sentences in initial stages of their system. In our approach this is unnecessary, and simplifying could miss many valid questions.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Comparison with Heilman and Smith
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         This task utilized a file (Biology: the body) with 56 source sentences from which our system generated 102 questions. The Heilman and Smith system, as they describe it, takes an over-generate and rank approach. We only took questions that scored a 2.0 or better with their ranking system,
         which resulted in less than 27% of their top questions. In all, 84 of their questions were evaluated. The questions again were presented with accompanying paragraphs of the source text. Questions from the two systems were randomly intermingled. Annotators gave 1 - 5 scores for each category of grammaticality, clarity and naturalness.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         As seen in Table 4, our results represent a 44% reduction in the error rate relative to Heilman and Smith on the average rating over all metrics, and as high as 61% reduction in the error rate on grammaticality judgments. The error reduction calculation is shown below. Note that
         r⁢a⁢t⁢i⁢n⁢g*
         is the maximum rating of 5.0.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        r⁢a⁢t⁢i⁢n⁢gs⁢y⁢s⁢t⁢e⁢m⁢2-r⁢a⁢t⁢i⁢n⁢gs⁢y⁢s⁢t⁢e⁢m⁢1r⁢a⁢t⁢i⁢n⁢g*-r⁢a⁢t⁢i⁢n⁢gs⁢y⁢s⁢t⁢e⁢m⁢1×100.0

(1)
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Comparison with Lindberg et al.
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         For a comparison with the Lindberg, Popowich, Nesbit and Winne system we used a file (Earth science: weather fronts) that seemed most similar to the text files for which their system was designed. The file has 93 sentences and our system generated 184 questions; the LPN&amp;W system generated roughly 4 times as many questions. From each system, 100 questions were randomly selected, making sure that the LPN&amp;W questions did not include questions generated from domain-specific templates such as:
         Summarize the influence of the maximum amount on the environment.
         The phrases
         Summarize the influence of
         and
         on the environment
         are part of a domain-specific template. The comparison results are shown in Table 5. Interestingly, our system again achieved a 44% reduction in the error rate when averaging over all metrics, just as it did in the Heilman and Smith comparison.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Linguistic Challenges
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        Natural language generation faces many linguistic challenges. Here we briefly describe three challenges: negation detection, coreference resolution, and verb forms.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Negation Detection
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         Negation detection is a complicated task because negation can occur at the word, phrase or clause level, and because there are subtle shades of negation between definite positive and negative polarities (Blanco and Moldovan, 2011). For our purposes we focused on negation as identified by the NEG label in SENNA which identified
         not
         in verb phrases. We have left for future work the task of identifying other negative indicators, which occasionally does lead to poor question/answer quality as in the following:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         Source sentence:
         In Darwin’s time and today, many people incorrectly believe that evolution means humans come from monkeys.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         Question:
         What does evolution mean?
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Answer:
         that humans come from monkeys
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p5">
        <p class="ltx_p">
         The negation in the word
         incorrectly
         is not identified.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Coreference Resolution
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         Currently, our system does not use any type of coreference resolution. Experiments with existing coreference software performed well only for personal pronouns, which occur infrequently in most expository text. Not having coreference resolution leads to vague questions, some of which can be filtered as discussed previously. However, further work on filters is needed to avoid questions such as:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         Source sentence:
         Air cools when it comes into contact with a cold surface or when it rises.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         Question:
         What happens when it comes into contact with a cold surface or when it rises?
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         Heilman and Smith chose to filter out questions with personal pronouns, possessive pronouns and noun phrases composed simply of determiners such as
         those
         . Lindberg et al. used the emPronoun system from Charniak and Elsner, which only handles personal pronouns. Since current state-of-the-art systems do not deal well with relative and possessive pronouns, this will continue to be a limitation of natural language generation systems for the time being.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Verb Forms
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         Since our focus is on expository text, system patterns deal primarily with the present and simple past tenses. Some patterns look for modals and so can handle future tense:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <p class="ltx_p">
         Source sentence:
         If you continue to move atoms closer and closer together, eventually the two nuclei will begin to repel each other.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         Question:
         Discuss what the two nuclei will repel.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p4">
        <p class="ltx_p">
         Light verbs pose complications in NLG because they are highly idiosyncratic and subject to syntactic variability (Sag et al., 2002). Light verbs can either carry semantic meaning (
         take
         your passport) or can be bleached of semantic content when combined with other words as in:
         make
         a decision,
         have
         a drink,
         take
         a walk. Common English verbs that can be light verbs include give, have, make, take. Handling these constructions as well as other multi-word expressions may require both rule-based and statistical approaches. The catenative construction also potentially adds complexity (Huddleston and Pullum, 2005), as shown in this example: As the universe expanded, it became less dense and
         began
         to
         cool
         . Care must be taken not to generate questions based on one predicate in the catenative construction.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p5">
        <p class="ltx_p">
         We are also hindered at times by the performance of the part of speech tagging and parsing software. The most common error observed was confusion between the noun and verb roles of a word. For example in:
         Plant roots and bacterial decay use carbon dioxide in the process of respiration,
         the word
         use
         was classified as NN, leaving no predicate and no semantic role labels in this sentence.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
