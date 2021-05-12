<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Vector spaces for historical linguistics: Using distributional semantics to study syntactic productivity in diachrony.
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
       This paper describes an application of distributional semantics to the study of syntactic productivity in diachrony, i.e., the property of grammatical constructions to attract new lexical items over time. By providing an empirical measure of semantic similarity between words derived from lexical co-occurrences, distributional semantics not only reliably captures how the verbs in the distribution of a construction are related, but also enables the use of visualization techniques and statistical modeling to analyze the semantic development of a construction over time and identify the semantic determinants of syntactic productivity in naturally occurring data.
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
        Language change does not exclusively consist of drastic shifts in ‘core’ aspects of grammar, such as changes in word order. Variation in usage, which can occur in no more than a few decades, is much more common, and to many linguists constitutes linguistic change in the making. Among these aspects of language use that are subject to diachronic change, this paper is concerned with the productivity of syntactic constructions, i.e., the range of lexical items with which a construction can be used. A given construction might occur with very different distributions at different points in time, even when the function it conveys remains the same. This is what Israel
        [Israel1996]
        finds for the pattern “Verb
        one’s way
        Path”, commonly called the
        way
        -construction
        [Goldberg1995]
        , exemplified by (1) and (2) below.
       </p>
      </div>
      <li class="ltx_item" style="list-style-type:none;">
       <span class="ltx_tag ltx_tag_section">
        (1)
       </span>
       <div class="ltx_para" id="S1.p2">
        <p class="ltx_p">
         They hacked their way through the jungle.
        </p>
        <li class="ltx_item" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_p">
          (2)
         </span>
         <div class="ltx_para" id="S1.p2.p1">
          <p class="ltx_p">
           She typed her way to a promotion.
          </p>
         </div>
         <div class="ltx_para" id="S1.p2.p2">
          <p class="ltx_p">
           As reported by Israel, examples like (1), in which the main verb describes the physical means whereby motion towards a goal is enabled, are attested as early as the 16
           <sup class="ltx_sup">
            th
           </sup>
           century, but it was not until the 19
           <sup class="ltx_sup">
            th
           </sup>
           century that examples like (2) started to appear, in which the action depicted by the verb provides a more indirect (and abstract) way of attaining the agent’s goal.
          </p>
         </div>
         <div class="ltx_para" id="S1.p2.p3">
          <p class="ltx_p">
           The productivity of a construction may appear partly arbitrary, but a growing body of evidence suggests that it is tied to the previous experience of speakers with that construction
           [Barðdal2008, Bybee and Eddington2006, Suttle and Goldberg2011]
           . More specifically, previous research points to a strong semantic component, in that the possibility of a novel use depends on how it semantically relates to prior usage. Along these lines, Suttle and Goldberg
           [Suttle and Goldberg2011, 1254]
           posit a criterion of coverage, defined as “the degree to which attested instances ‘cover’ the category determined jointly by attested instances together with the target coinage”. Coverage relates to how the semantic domain of a construction is populated in the vicinity of a given target coinage, and in particular to the density of the semantic space.
          </p>
         </div>
        </li>
       </div>
       <div class="ltx_para" id="S1.p3">
        <p class="ltx_p">
         The importance of semantics for syntactic productivity implies that the meaning of lexical items must be appropriately taken into account when studying the distribution of constructions, which calls for an empirical operationalization of semantics. Most existing studies rely either on the semantic intuitions of the analyst, or on semantic norming studies
         [Bybee and Eddington2006]
         . In this paper, I present a third alternative that takes advantage of advances in computational linguistics and draws on a distributionally-based measure of semantic similarity. On the basis of a case study of the construction “V
         the hell out of
         NP”, I show how distributional semantics can profitably be applied to the study of syntactic productivity.
        </p>
       </div>
      </li>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       The
       hell
       -construction
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The case study presented in this paper considers the syntactic pattern “V
        the hell out of
        NP”, as exemplified by the following sentences from the Corpus of Contemporary American English (COCA; Davies, 2008):
       </p>
      </div>
      <li class="ltx_item" style="list-style-type:none;">
       <span class="ltx_tag ltx_tag_section">
        (3)
       </span>
       <div class="ltx_para" id="S2.p2">
        <p class="ltx_p">
         Snakes just scare the hell out of me.
        </p>
        <li class="ltx_item" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_p">
          (4)
         </span>
         <div class="ltx_para" id="S2.p2.p1">
          <p class="ltx_p">
           It surprised the hell out of me when I heard what he’s been accused of.
          </p>
          <li class="ltx_item" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_p">
            (5)
           </span>
           <div class="ltx_para" id="S2.p2.p1.p1">
            <p class="ltx_p">
             You might kick the hell out of me like you did that doctor.
            </p>
           </div>
           <div class="ltx_para" id="S2.p2.p1.p2">
            <p class="ltx_p">
             The construction generally conveys an intensifying function (very broadly defined). Thus,
             scare/surprise the hell out of
             means “scare/surprise very much”, and
             kick the hell out of
             means “kick very hard”. The particular aspect that is intensified may be highly specific to the verb and depend to some extent on the context.
             Scare
             and
             beat
             are the most typical verbs in that construction (and arguably the two that first come to mind), but a wide and diverse range of other verbs can also be found, such that
             avoid
             in (6),
             drive
             (a car) in (7) and even an intransitive verb (
             listen
             ) in (8):
            </p>
           </div>
          </li>
          <li class="ltx_item" style="list-style-type:none;">
           <span class="ltx_tag ltx_tag_item">
            (6)
           </span>
           <div class="ltx_para" id="S2.p2.p1.p3">
            <p class="ltx_p">
             I […] avoided the hell out of his presence.
            </p>
            <li class="ltx_item" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_p">
              (7)
             </span>
             <div class="ltx_para" id="S2.p2.p1.p3.p1">
              <p class="ltx_p">
               But you drove the hell out of it!
              </p>
              <li class="ltx_item" style="list-style-type:none;">
               <span class="ltx_tag ltx_tag_p">
                (8)
               </span>
               <div class="ltx_para" id="S2.p2.p1.p3.p1.p1">
                <p class="ltx_p">
                 I’ve been listening the hell out of your tape.
                </p>
               </div>
               <div class="ltx_para" id="S2.p2.p1.p3.p1.p2">
                <p class="ltx_p">
                 To examine how the construction evolved over time, I used diachronic data from the Corpus of Historical American English (COHA; Davies 2010), which contains about 20 million words of written American English for each decade between 1810 and 2009 roughly balanced for genre (fiction, magazines, newspapers, non-fiction). Instances of the
                 hell
                 -construction were filtered out manually from the results of the query “[v*] the hell out of”, mostly ruling out locative constructions like
                 get the hell out of here
                 . The diachronic evolution of the verb slot in terms of token and type frequency is plotted in Figure
                 1
                 . Since the corpus size varies slightly in each decade, the token frequencies are normalized per million words.
                </p>
               </div>
              </li>
             </div>
             <div class="ltx_para" id="S2.p2.p1.p3.p2">
              <p class="ltx_p">
               The construction is first attested in the corpus in the 1930s. Since then, it has been steadily increasing in token frequency (to the exception of a sudden decrease in the 1990s). Also, more and more different verbs are attested in the construction, as shown by the increase in type frequency. This reflects a general expansion of the productivity of the construction, but it does not show what this productivity consists of. For instance, it does not say what kinds of verbs joined the distribution and to what extent the distribution becomes semantically more diverse over time. To answer these questions, I will analyze the distribution of the construction from a semantic point of view by using a measure of semantic similarity derived from distributional information.
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
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Distributional measure of semantic similarity
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Drawing on the observation that words occurring in similar contexts tend to have related meanings
        [Miller and Charles1991]
        , distributional approaches to semantics seek to capture the meaning of words through their distribution in large text corpora
        [Lenci2008, Turney and Pantel2010, Erk2012]
        . One benefit of the distributional semantics approach is that it allows semantic similarity between words to be quantified by measuring the similarity in their distribution. This is achieved by means of a vector-space model that assigns an array of numerical values (i.e., a vector) derived from distributional information to each word. A wide range of distributional information can be employed in vector-based models; the present study uses the ‘bag of words’ approach, which is based on the frequency of co-occurrence of words within a given context window. According to Sahlgren
        [Sahlgren2008]
        , this kind of model captures to what extent words can be substituted for each other, which is a good measure of semantic similarity between verbs. As it turns out, even this relatively coarse model captures semantic distinctions in the distribution of the
        hell
        -construction that make intuitive sense.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        All instances of the relevant verbs were extracted from the COCA
        with their context of occurrence. In order to make sure that enough distributional information is available to reliably assess semantic similarity, verbs with less than 2,000 occurrences were excluded, which left 92 usable items (out of 105). The words in the sentence contexts extracted from the COCA were lemmatized and annotated for part-of-speech using TreeTagger
        [Schmid1994]
        . The part-of-speech annotated lemma of each collocate within a 5-word window was extracted from the COCA data to build the co-occurrence matrix recording the frequency of co-occurrence of each verb with its collocates. Only the nouns, verbs, adjectives, and adverbs listed among the 5,000 most frequent words in the corpus were considered (to the exclusion of
        be
        ,
        have
        , and
        do
        ), thus ignoring function words (articles, prepositions, conjunctions, etc.) and all words that did not make the top 5,000.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The co-occurrence matrix was transformed by applying a Point-wise Mutual Information weighting scheme, using the DISSECT toolkit
        [Dinu et al.2013]
        , to turn the raw frequencies into weights that reflect how distinctive a collocate is for a given target word with respect to the other target words under consideration. The resulting matrix, which contains the distributional information (in 4,683 columns) for 92 verbs occurring in the
        hell
        -construction, constitutes the semantic space under consideration in this case study. Pairwise distances between the target verbs were calculated using the cosine distance. The rest of the analysis was conducted on the basis of this distance matrix in the R environment
        [R Development Core Team2013]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Application of the vector-space model
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Semantic plots
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         One of the advantages conferred by the quantification of semantic similarity is that lexical items can be precisely considered in relation to each other, and by aggregating the similarity information for all items in the distribution, we can produce a visual representation of the structure of the semantic domain of the construction in order to observe how verbs in that domain are related to each other, and to immediately identify the regions of the semantic space that are densely populated (with tight clusters of verbs), and those that are more sparsely populated (fewer and/or more scattered verbs). Multidimensional scaling (MDS) provides a way both to aggregate similarity information and to represent it visually. This technique aims to place objects in a space with two (or more) dimensions such that the between-object distances are preserved as much as possible.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         The pairwise distances between verbs were submitted to multidimensional scaling into two dimensions.
         To visualize the semantic development of the
         hell
         -construction over time, the diachronic data was divided into four successive twenty-year periods: 1930-1949, 1950-1969, 1970-1989, and 1990-2009. The semantic plots corresponding to the distribution of the construction in each period are presented in Figure
         2
         . For convenience and ease of visualization, the verbs are color-coded according to four broad semantic groupings that were identified inductively by means of hierarchical clustering (using Ward’s criterion).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         By comparing the plots in Figure
         2
         , we can follow the semantic development of the
         hell
         -construction. The construction is strikingly centered around two kinds of verbs: mental verbs (in red:
         surprise
         ,
         please
         ,
         scare
         , etc.) and verbs of hitting (most verbs in green:
         smash
         ,
         kick
         ,
         whack
         , etc.), a group that is orbited by other kinds of forceful actions (such as
         pinch
         ,
         push
         , and
         tear
         ). These two types of verbs account for most of the distribution at the onset, and they continue to weigh heavily throughout the history of the construction. These two classes also correspond to the regions of the semantic domain that attract the most new members, and they constantly do so in all periods. Outside of these two clusters, the semantic space is much more sparsely populated. In the first period (1930-1949), only a few peripheral members are found. They are joined by other distantly related items in later periods, although by no more than a handful in each. In other words, the construction is markedly less productive in these outer domains, which never form proper clusters of verbs.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         In sum, the semantic plots show that densely populated regions of the semantic space appear to be the most likely to attract new members. Outside of the two identified domains of predilection, other classes never become important, assumedly because they do not receive a “critical mass” of items, and therefore attract new members more slowly.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Statistical analysis
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         With the quantification of semantic similarity provided by the distributional semantic model, it is also possible to properly test the hypothesis that productivity is tied to the structure of the semantic space. On the reasonable assumption that the semantic contribution of the construction did not change, and therefore that all verbs ever attested in it are equally plausible from a semantic point of view, the fact that some verbs joined the distribution later than others is in want of an explanation. In view of the observations collected on the semantic plots and in line with previous research (especially Suttle and Goldberg’s notion of coverage), I suggest that the occurrence of a new item in the construction in a given period is related to the density of the semantic space around that item in the previous period. If the semantic space around the novel item is dense, i.e., if there is a high number of similar items, the coinage will be very likely. The sparser the semantic space around a given item, the less likely this item can be used.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         The measure of density used in this study considers the set of the N nearest neighbors of a given item in the semantic space, and is defined by the following formula:
        </p>
        D⁢e⁢n⁢s⁢i⁢t⁢yV,N=1-∑n=1Nd⁢(V,Vn)N
        <p class="ltx_p">
         where
         d⁢(V,Vn)
         is the distance between a verb V and its n
         <sup class="ltx_sup">
          th
         </sup>
         nearest neighbor. In plain language, density equals one minus the mean distance to the N nearest neighbors. The latter value decreases with space density (i.e., if there are many close neighbors), and is therefore technically a measure of sparsity; since cosine distances are between 0 and 1, subtracting the mean distance from one returns a measure of density within the same boundaries.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         This measure of density was used as a factor in logistic regression to predict the first occurrence of a verb in the construction, coded as the binary variable
         Occurrence
         , set to 1 for the first period in which the verb is attested in the construction, and to 0 for all preceding periods (later periods were discarded). For each
         Verb
         -
         Period
         -
         Occurrence
         triplet, the density of the semantic space around the verb in the immediately preceding period was calculated. Six different versions of the density measure, with the number of neighbors under consideration (N) varying between 3 and 8, were used to fit six mixed effects regression models with
         Occurrence
         as the dependent variable,
         Density
         as a fixed effect, and random by-verb intercepts and slopes
         [Bates et al.2011]
         . The results of these models are summarized in Table
         1
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p4">
        <p class="ltx_p">
         For all values of N, we find a positive effect of
         Density
         , i.e., there is a positive relation between the measure of density and the probability of first occurrence of a verb in the construction. However, the effect is only significant for N
         ≥
         7; hence, the hypothesis that space density increases the odds of a coinage occurs in the construction is supported for measures of density based on these values of N.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p5">
        <p class="ltx_p">
         More generally, the
         p
         -value decreases as N increases, which means that the positive relation between
         Density
         and
         Occurrence
         is less systematic when
         Density
         is measured with fewer neighbors. This is arguably because a higher N helps to better discriminate between dense clusters where all items are close together from looser ones that consist of a few ‘core’ items surrounded by more distant neighbors. This result illustrates the role of type frequency in syntactic productivity: a measure of density that is supported by a higher number of types makes better prediction than a measure supported by fewer types. This means that productivity not only hinges on how the existing semantic space relates to the novel item, it also occurs more reliably when this relation is attested by more items. These finding support the view that semantic density and type frequency, while they both positively influence syntactic productivity, do so in different ways: density defines the necessary conditions for a new coinage to occur, while type frequency increases the confidence that this coinage is indeed possible.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
