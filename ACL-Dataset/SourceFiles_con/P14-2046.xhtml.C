<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   How to Speak a Language without Knowing It.
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
       We develop a system that lets people overcome language barriers by letting them speak a language they do not know. Our system accepts text entered by a user, translates the text, then converts the translation into a phonetic spelling in the user’s own orthography. We trained the system on phonetic spellings in travel phrasebooks.
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
        Can people speak a language they don’t know? Actually, it happens frequently. Travel phrasebooks contain phrases in the speaker’s language (e.g., ‘‘thank you’’) paired with foreign-language translations (e.g., ‘‘
спасибо’’). Since the speaker may not be able to pronounce the foreign-language orthography, phrasebooks additionally provide phonetic spellings that approximate the sounds of the foreign phrase. These spellings employ the familiar writing system and sounds of the speaker’s language. Here is a sample entry from a French phrasebook for English speakers:
       </p>
       <table class="ltx_tabular ltx_centering ltx_align_middle">
        <tbody class="ltx_tbody">
         <tr class="ltx_tr">
          <td class="ltx_td ltx_align_left">
           English:
          </td>
          <td class="ltx_td ltx_align_left">
           Leave me alone.
          </td>
         </tr>
         <tr class="ltx_tr">
          <td class="ltx_td ltx_align_left">
           French:
          </td>
          <td class="ltx_td ltx_align_left">
           Laissez-moi tranquille.
          </td>
         </tr>
         <tr class="ltx_tr">
          <td class="ltx_td ltx_align_left">
           Franglish:
          </td>
          <td class="ltx_td ltx_align_left">
           Less-ay mwah trahn-KEEL.
          </td>
         </tr>
        </tbody>
       </table>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The user ignores the French and goes straight to the Franglish. If the Franglish is well designed, an English speaker can pronounce it and be understood by a French listener.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Figure
        1
        shows a sample entry from another book—an English phrasebook for Chinese speakers. If a Chinese speaker wants to say ‘‘
        UTF8gkai非常感谢你这顿美餐’’, she need only read off the Chinglish “
        UTF8gkai三可 油 否 热斯 弯德否 米欧”, which approximates the sounds of “Thank you for this wonderful meal” using Chinese characters.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Phrasebooks permit a form of accurate, personal, oral communication that speech-to-speech translation devices lack. However, the user is limited to a small set of fixed phrases. In this paper, we lift this restriction by designing and evaluating a software program with the following:
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           Input: Text entered by the speaker, in her own language.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           Output: Phonetic rendering of a foreign-language translation of that text, which, when pronounced by the speaker, can be understood by the listener.
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p6">
       <p class="ltx_p">
        The main challenge is that different languages have different orthographies, different phoneme inventories, and different phonotactic constraints, so mismatches are inevitable. Despite this, the system’s output should be both unambiguously pronounceable by the speaker and readily understood by the listener.
       </p>
      </div>
      <div class="ltx_para" id="S1.p7">
       <p class="ltx_p">
        Our goal is to build an application that covers many language pairs and directions. The current paper describes a single system that lets a Chinese person speak English.
       </p>
      </div>
      <div class="ltx_para" id="S1.p8">
       <p class="ltx_p">
        We take a statistical modeling approach to this problem, as is done in two lines of research that are most related. The first is machine transliteration
        [3]
        , in which names and technical terms are translated across languages with different sound systems. The other is respelling generation
        [2]
        , where an English speaker is given a phonetic hint about how to pronounce a rare or foreign word to another English speaker. By contrast, we aim to help people issue full utterances that cross language barriers.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Evaluation
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Our system’s input is Chinese. The output is a string of Chinese characters that approximate English sounds, which we call Chinglish. We build several candidate Chinese-to-Chinglish systems and evaluate them as follows:
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           We compute the normalized edit distance between the system’s output and a human-generated Chinglish reference.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           A Chinese speaker pronounces the system’s output out loud, and an English listener takes dictation. We measure the normalized edit distance against an English reference.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i3.p1">
          <p class="ltx_p">
           We automate the previous evaluation by replace the two humans with: (1) a Chinese speech synthesizer, and (2) a English speech recognizer.
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Data
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        We seek to imitate phonetic transformations found in phrasebooks, so phrasebooks themselves are a good source of training data. We obtained a collection of 1312
        &lt;
        Chinese, English, Chinglish
        &gt;
        phrasebook tuples
        (see Table
        1
        ).
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We use 1182 utterances for training, 65 for development, and 65 for test. We know of no other computational work on this type of corpus.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Our Chinglish has interesting gross empirical properties. First, because Chinglish and Chinese are written with the same characters, they render the same inventory of 416 distinct syllables. However, the distribution of Chinglish syllables differs a great deal from Chinese (Table
        2
        ). Syllables ‘‘si’’ and ‘‘te’’ are very popular, because while consonant clusters like English ‘‘st’’ are impossible to reproduce exactly, the particular vowels in ‘‘si’’ and ‘‘te’’ are fortunately very weak.
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        We find that multiple occurrences of an English word type are generally associated with the same Chinglish sequence. Also, Chinglish characters do not generally span multiple English words. It is reasonable for ‘‘can I’’ to be rendered as ‘‘kan nai’’, with ‘‘nai’’ spanning both English words, but this is rare.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Model
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We model Chinese-to-Chinglish translation with a cascade of weighted finite-state transducers (wFST), shown in Figure
        2
        . We use an online MT system to convert Chinese to an English word sequence (Eword), which is then passed through FST A to generate an English sound sequence (Epron). FST A is constructed from the CMU Pronouncing Dictionary
        [6]
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        Next, wFST B translates English sounds into Chinese sounds (Pinyin-split). Pinyin is an official syllable-based romanization of Mandarin Chinese characters, and Pinyin-split is a standard separation of Pinyin syllables into initial and final parts. Our wFST allows one English sound token to map to one or two Pinyin-split tokens, and it also allows two English sounds to map to one Pinyin-split token.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        Finally, FST C converts Pinyin-split into Pinyin, and FST D chooses Chinglish characters. We also experiment with an additional wFST E that translates English words directly into Chinglish.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Training
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        FSTs A, C, and D are unweighted, and remain so throughout this paper.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Phoneme-based model
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We must now estimate the values of FST B parameters, such as P(
         si|S
         ). To do this, we first take our phrasebook triples and construct sample string pairs
         &lt;
         Epron, Pinyin-split
         &gt;
         by pronouncing the phrasebook English with FST A, and by pronouncing the phrasebook Chinglish with FSTs D and C. Then we run the EM algorithm to learn FST B parameters (Table
         3
         ) and Viterbi alignments, such as:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            ae n
           </td>
           <td class="ltx_td ltx_align_left">
            d
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            uan
           </td>
           <td class="ltx_td ltx_align_left">
            d e
           </td>
          </tr>
         </tbody>
        </table>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Phoneme-phrase-based model
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         Mappings between phonemes are context-sensitive. For example, when we decode English ‘‘grandmother’’, we get:
        </p>
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            ae n
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            m
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            ah
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            dh
           </td>
           <td class="ltx_td ltx_align_left">
            er
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            an
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            m u
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d
           </td>
           <td class="ltx_td ltx_align_left">
            e
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         where as the reference Pinyin-split sequence is:
        </p>
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            g
           </td>
           <td class="ltx_td ltx_align_left">
            e
           </td>
           <td class="ltx_td ltx_align_left">
            r
           </td>
           <td class="ltx_td ltx_align_left">
            uan
           </td>
           <td class="ltx_td ltx_align_left">
            d
           </td>
           <td class="ltx_td ltx_align_left">
            e
           </td>
           <td class="ltx_td ltx_align_left">
            m
           </td>
           <td class="ltx_td ltx_align_left">
            a
           </td>
           <td class="ltx_td ltx_align_left">
            d
           </td>
           <td class="ltx_td ltx_align_left">
            e
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         Here, ‘‘ae n’’ should be decoded as ‘‘uan’’ when preceded by ‘‘r’’. Following phrase-based methods in statistical machine translation
         [4]
         and machine transliteration
         [1]
         , we model substitution of longer sequences. First, we obtain Viterbi alignments using the phoneme-based model, e.g.:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            ae n
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            m
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            ah
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            dh
           </td>
           <td class="ltx_td ltx_align_left">
            er
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            g e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            r
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            uan
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d e
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            m
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            a
           </td>
           <td class="ltx_td ltx_align_left ltx_border_r">
            d
           </td>
           <td class="ltx_td ltx_align_left">
            e
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS2.p5">
        <p class="ltx_p">
         Second, we extract phoneme phrase pairs consistent with these alignments. We use no phrase-size limit, but we do not cross word boundaries. From the example above, we pull out phrase pairs like:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p6">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            g
            →
            g e
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            g r
            →
            g e r
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            …
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            r
            →
            r
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            r ae n
            →
            r uan
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left">
            …
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS2.p7">
        <p class="ltx_p">
         We add these phrase pairs to FST B, and call this the phoneme-phrase-based model.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.3
        </span>
        Word-based model
       </h3>
       <div class="ltx_para" id="S5.SS3.p1">
        <p class="ltx_p">
         We now turn to WFST E, which short-cuts directly from English words to Pinyin. We create
         &lt;
         English, Pinyin
         &gt;
         training pairs from our phrasebook simply by pronouncing the Chinglish with FST D. We initially allow each English word type to map to any sequence of Pinyin, up to length 7, with uniform probability. EM learns values for parameters like
         P(nai te|night)
         , plus Viterbi alignments such as:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS3.p2">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            accept
           </td>
           <td class="ltx_td ltx_align_left">
            tips
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            a ke sha pu
           </td>
           <td class="ltx_td ltx_align_left">
            te ti pu si
           </td>
          </tr>
         </tbody>
        </table>
       </div>
       <div class="ltx_para" id="S5.SS3.p3">
        <p class="ltx_p">
         Notice that this model makes alignment errors due to sparser data (e.g., the word ‘‘tips’’ and ‘‘ti pu si’’ only appear once each in the training data).
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.4
        </span>
        Hybrid training
       </h3>
       <div class="ltx_para" id="S5.SS4.p1">
        <p class="ltx_p">
         To improve the accuracy of word-based EM alignment, we use the phoneme based model to decode each English word in the training data to Pinyin. From the 100-best list of decodings, we collect combinations of start/end Pinyin syllables for the word. We then modify the initial, uniform English-to-Pinyin mapping probabilities by giving higher initial weight to mappings that respect observed start/end pairs. When we run EM, we find that alignment errors for ‘‘tips’’ in section
         5.3
         are fixed:
        </p>
       </div>
       <div class="ltx_para" id="S5.SS4.p2">
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            accept
           </td>
           <td class="ltx_td ltx_align_left">
            tips
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_left ltx_border_r">
            a ke sha pu te
           </td>
           <td class="ltx_td ltx_align_left">
            ti pu si
           </td>
          </tr>
         </tbody>
        </table>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS5">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.5
        </span>
        Hybrid decoding
       </h3>
       <div class="ltx_para" id="S5.SS5.p1">
        <p class="ltx_p">
         The word-based model can only decode 29 of the 65 test utterances, because wFST E fails if an utterance contains a new English word type, previously unseen in training. The phoneme-based models are more robust, able to decode 63 of the 65 utterances, failing only when some English word type falls outside the CMU pronouncing dictionary (FST A).
        </p>
       </div>
       <div class="ltx_para" id="S5.SS5.p2">
        <p class="ltx_p">
         Our final model combines these two, using the word-based model for known English words, and the phoneme-based models for unknown English words.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Experiments
      </h2>
      <div class="ltx_para" id="S6.p1">
       <p class="ltx_p">
        Our first evaluation (Table
        4
        ) is intrinsic, measuring our Chinglish output against references from the test portion of our phrasebook, using edit distance. Here, we start with reference English and measure the accuracy of Pinyin syllable production, since the choice of Chinglish character does not affect the Chinglish pronunciation. We see that the Word-based method has very high accuracy, but low coverage. Our best system uses the Hybrid training/decoding method. As Table
        6
        shows, the ratio of unseen English word tokens is small, thus large portion of tokens are transformed using word-based method. The average edit distance of phoneme-phrase model and that of hybrid training/decoding model are close, indicating that long phoneme-phrase pairs can emulate word-pinyin mappings.
       </p>
      </div>
      <div class="ltx_para" id="S6.p2">
       <p class="ltx_p">
        Our second evaluation is a dictation task. We speak our Chinglish character sequence output aloud and ask an English monolingual person to transcribe it. (Actually, we use a Chinese synthesizer to remove bias.) Then we measure edit distance between the human transcription and the reference English from our phrasebook. Results are shown in Table
        7
        .
       </p>
      </div>
      <div class="ltx_para" id="S6.p3">
       <p class="ltx_p">
        Finally, we repeat the last experiment, but removing the human from the loop, using both automatic Chinese speech synthesis and English speech recognition. Results are shown in Table
        8
        . Speech recognition is more fragile than human transcription, so edit distances are greater. Table
        5
        shows a few examples of the Chinglish generated by the hybrid training and decoding method, as well as the recognized English from the dictation and ASR tasks.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
