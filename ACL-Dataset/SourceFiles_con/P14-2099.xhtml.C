<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Unsupervised Alignment of Privacy Policies using Hidden Markov Models.
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
       To support empirical study of online privacy policies,
as well as tools for users with privacy concerns, we consider the problem of aligning sections of a thousand
policy documents, based on the issues they address.
We apply an unsupervised HMM; in two new (and reusable) evaluations, we find the approach more effective than clustering and
topic models.
      </p>
     </div>
     <div class="ltx_para" id="p1">
      <p class="ltx_p">
       topsep=0pt,itemsep=-0.4em,labelwidth=0.5em,leftmargin=0.6em
       topsep=0pt,itemsep=-0.4em,labelwidth=0.5em,leftmargin=0.75em
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
        Privacy policy documents are verbose, often esoteric legal documents that many people encounter as clients of companies that provide services on the web.
        McDonald and Cranor (2008)
        showed that, if users were to read the privacy policies of every website they access during the course of a year, they would end up spending a substantial amount of their time doing just that and would often still not be able to answer basic questions about what these policies really say. Unsurprisingly, many people do not read them
        [9]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        Such policies therefore offer an excellent opportunity for NLP tools that summarize or extract key information that (i) helps users understand the implications of agreeing to these policies and (ii) helps legal analysts understand the contents of these policies and make recommendations on how they can be improved or made more clear. Past applications of NLP have sought to parse privacy policies into machine-readable representations
        [5]
        or extract sub-policies from larger documents
        [14]
        . Machine learning has been applied to assess certain attributes of policies
        [7, 1, 6, 15]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        This paper instead analyzes policies in aggregate, seeking to
        align
        sections of policies. This task is motivated by an expectation that many policies will address similar issues,
        such as
collection of a user’s contact, location, health, and financial information, sharing with third parties, and deletion of data.
This expectation is supported by recommendation by privacy experts
        [10]
        and policymakers
        [9]
        ; in the financial services sector,
the Gramm-Leach-Bliley Act
        requires
        these institutions to address a specific set of issues.
Aligning policy sections is a first step toward our aforementioned summarization and extraction goals.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        We present the following contributions:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i1.p1">
          <p class="ltx_p">
           A new corpus of over 1,000 privacy policies gathered from widely used websites, manually segmented into subtitled sections by crowdworkers (§
           2
           ).
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i2.p1">
          <p class="ltx_p">
           An unsupervised approach to aligning the policy sections based on the issues they discuss. For example, sections that discuss “user data on the company’s server” should be grouped together. The approach is inspired by the application of hidden Markov models to sequence alignment in computational biology (Durbin et al., 1998;
           §
           3
           ).
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.i3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I1.i3.p1">
          <p class="ltx_p">
           Two reusable evaluation benchmarks for the resulting alignment of policy sections (§
           4
           ). We demonstrate that our approach outperforms naïve methods (§
           5
           ).
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        Our corpus and benchmarks are available at
        http://usableprivacy.org/data
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Data Collection
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        We collected 1,010
unique privacy policy documents from the top websites ranked by
Alexa.com.
        These policies were
collected during a period of six weeks during December 2013 and
January 2014. They are a snapshot of privacy policies of mainstream
websites covering fifteen of Alexa.com’s seventeen categories (Table
        1
        ).
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        Finding a website’s policy is not trivial. Though many well-regulated
commercial websites provide a “privacy” link on their homepages, not
all do. We found university websites to be exceptionally unlikely to
provide such a link. Even once the policy’s URL is identified,
extracting the text presents the usual challenges associated with
scraping documents from the web. Since every site is different in
its placement of the document (e.g., buried deep within the website,
distributed across several pages, or mingled together with Terms of Service)
and format (e.g., HTML, PDF, etc.), and since
we wish to preserve as much document structure as possible (e.g.,
section labels), full automation was not a viable solution.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        We therefore crowdsourced the privacy policy document collection using
Amazon Mechanical Turk. For each website, we
created a HIT in which a worker was asked to copy and paste the
following privacy policy-related information into text boxes:
(i) privacy policy URL;
(ii) last updated date (or effective date) of the current privacy policy;
(iii) privacy policy full text; and
(iv) the section subtitles in the top-most layer of the privacy policy.
To identify the privacy policy URL, workers were encouraged to go to the website and search for the privacy link.
Alternatively, they could form a search query using the website name and “privacy policy” (e.g., “Amazon.com privacy policy”) and search in the returned results for the most appropriate privacy policy URL.
Given the privacy policy full text and the section subtitles,
we partition the full privacy document into different sections, delimited by the section subtitles.
A privacy policy is then converted into XML.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Each HIT was completed by three workers, paid $0.05, for a total
cost of $380 (including Amazon’s surcharge).
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
        Given the corpus of privacy policies described in §
        2
        , we designed a model to efficiently infer an alignment of policy sections. While we expect that different kinds of websites will likely address different privacy issues, we believe that many policies will discuss roughly the same set of issues. Aligning the policies is a first step in a larger effort to (i) automatically analyze policies to make them less opaque to users and (ii) support legal experts who wish to characterize the state of privacy online and make recommendations
        [7, 1, 6]
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        We are inspired by multiple sequence alignment methods in computational biology
        [8]
        and by
        Barzilay and Lee (2004)
        , who described a hidden Markov model (HMM) for document content where each state corresponds to a distinct topic and generates sentences relevant to that topic according to a language model. We estimate an HMM-like model on our corpus, exploiting similarity across privacy policies to the extent it is evident in the data. In our formulation, each hidden state corresponds to an issue or topic, characterized by a distribution over words and bigrams appearing in privacy policy sections addressing that issue. The transition distribution captures tendencies of privacy policy authors to organize these sections in similar orders, though with some variation.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        The generative story for our model is as follows. Let
        𝒮
        denote the set of hidden states.
       </p>
       <ol class="ltx_enumerate" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          1.
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           Choose a start state
           y1
           from
           𝒮
           according to the start-state distribution.
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_enumerate">
          2.
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           For
           t=1,2,…
           , until
           yt
           is the stopping state:
          </p>
          <ol class="ltx_enumerate" id="I2.I1">
           <li class="ltx_item" id="I2.I1.i1" style="list-style-type:none;">
            <span class="ltx_tag ltx_tag_enumerate">
             (a)
            </span>
            <div class="ltx_para" id="I2.I1.i1.p1">
             <p class="ltx_p">
              Sample the
              t
              th section of the document by drawing a bag of terms,
              𝒐t
              , according to the emission multinomial distribution for state
              yt
              . Note the difference from traditional HMMs, in which a
              single
              observation symbol is drawn at each time step.
              𝒐t
              is generated by repeatedly sampling from a distribution over terms that includes all unigrams and bigrams except those that occur in fewer than 5% of the documents and in more than 98% of the documents. This filtering rule was designed to eliminate uninformative stopwords as well as company-specific terms (e.g., the name of the company).
             </p>
            </div>
           </li>
           <li class="ltx_item" id="I2.I1.i2" style="list-style-type:none;">
            <span class="ltx_tag ltx_tag_enumerate">
             (b)
            </span>
            <div class="ltx_para" id="I2.I1.i2.p1">
             <p class="ltx_p">
              Sample the next state,
              yt+1
              , according to the transition distribution over
              𝒮
              .
             </p>
            </div>
           </li>
          </ol>
         </div>
        </li>
       </ol>
       <p class="ltx_p">
        This model can nearly be understood as a hidden
        semi
        -Markov model
        [3]
        , though we treat the section lengths as observable. Indeed, our model does not even generate these lengths, since doing so would force the states to “explain” the length of each section, not just its content. The likelihood function for the model is shown in Figure
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        The parameters of the model are almost identical to those of a classic HMM (start state distribution, emission distributions, and transition distributions), except that emissions are characterized by multinomial rather than a categorical distributions. These are learned using Expectation-Maximization, with a forward-backward algorithm to calculate marginals (E-step) and smoothed maximum likelihood estimation for the M-step
        [13]
        .
After learning, the most probable assignment of a policy’s sections to states can be recovered using a variant of the Viterbi algorithm.
       </p>
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        We consider three HMM variants.
“Vanilla” allows all transitions. The other two posit an ordering on the states
        𝒮={s1,s2,…,sK}
        , and restrict the set of transitions that are possible, imposing bias on the learner. “All Forward” only allows
        sk
        to transition to
        {sk,sk+1,…,sK}
        . “Strict Forward” only allows
        sk
        to transition to
        sk
        or
        sk+1
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Evaluation
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        Developing a gold-standard alignment of privacy policies would either require an interface that allows each annotator to interact with the entire corpus of previously aligned documents while reading the one she is annotating, or the definition (and likely iterative refinement) of a set of categories for manually labeling policy sections. These were too costly for us to consider, so
we instead propose two generic methods to evaluate models for sequence alignment of a collection of documents with generally similar content. Though our model (particularly the restricted variants) treats the problem as one of
        alignment
        , our evaluations consider
        groupings
        of policy sections. In the sequel, a grouping on a set
        X
        is defined as a collection of subsets
        Xi⊆X
        ; these may overlap (i.e., there might be
        x∈Xi∩Xj
        ) and need not be exhaustive (i.e., there might be
        x∈X∖⋃iXi
        ).
       </p>
      </div>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Evaluation by Human QA
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         This study was carried out as part of a larger collaboration with legal scholars who study privacy. In that work, we have formulated a set of nine multiple choice questions about a single policy that ask about collection of contact, location, health, and financial information, sharing of each with third parties, and deletion of data.
         The questions were inspired primarily by the substantive interest of these domain experts—not by this particular algorithmic study.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         For thirty policies, we obtained answers from each of six domain experts who were not involved in designing the questions. For the purposes of this study, the experts’ answers are not important. In addition to answering each question for each policy, we also asked each expert to copy and paste the text of the policy that contains the answer. Experts were allowed to select as many sections for each question as they saw fit, since answering some questions may require synthesizing information from different sections.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <p class="ltx_p">
         For each of the nine questions, we take the union of all policy sections that contain text selected by any annotator as support for her answer. This results in nine groups of policy sections, which we call
         answer-sets
         denoted
         A1,…,A9
         . Our method allows these to overlap (63% of the sections in any
         Ai
         occurred in more than one
         Ai
         ), and they are not exhaustive (since many sections of the policies were not deemed to contain answers to any of the nine questions by any expert).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         Together, these can be used as a gold standard grouping of policy sections, against which we can compare our system’s output. To do this, we define the set of section
         pairs
         that are grouped together in answer sets,
         G=|{⟨a,b⟩∣∃Ai∋a,b}|
         , and a similar set of pairs
         H
         from a model’s grouping. From these sets, we calculate estimates of precision (
         |G∩H|/|H|
         ) and recall (
         |G∩H|/|G|
         ).
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         One shortcoming of this approach, for which the second evaluation seeks to compensate, is that a very small, and likely biased, subset of the policy sections is considered.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Evaluation by Direct Judgment
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We created a separate gold standard of judgments of pairs of privacy policy sections. The data selected for judgment was a sample of pairs stratified by a simple measure of text similarity.
We derived unigram tfidf vectors for each section in each of 50 randomly sampled policies per category.
We then binned
         pairs
         of sections by cosine similarity (into four bins bounded by 0.25, 0.5, and 0.75). We sampled 994 section pairs uniformly across the 15 categories’ four bins each.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         Crowdsourcing was used to determine, for each pair, whether the two sections should be grouped together.
A HIT consisted of a pair of policy sections and a multiple choice question, “After reading the two sections given below, would you say that they broadly discuss the same topic?” The possible answers were:
        </p>
        <ol class="ltx_enumerate" id="I3">
         <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I3.i1.p1">
           <p class="ltx_p">
            Yes, both the sections essentially convey the same message in a privacy policy.
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I3.i2.p1">
           <p class="ltx_p">
            Although, the sections do not convey the same message, the broadly discuss the same topic. (For ease of understanding, some examples of content on “the same topic” were included.)
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I3.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           3.
          </span>
          <div class="ltx_para" id="I3.i3.p1">
           <p class="ltx_p">
            No, the sections discuss two different topics.
           </p>
          </div>
         </li>
        </ol>
        <p class="ltx_p">
         The first two options were considered a “yes” for the majority voting and for defining a gold standard.
Every section-pair was annotated by at least three annotators (as many as 15, increased until an absolute majority was reached). Turkers with an acceptance rate greater than 95% with an experience of at least 100 HITs were allowed and paid $0.03 per annotation. The total cost including some initial trials was $130. 535 out of the 994 pairs were annotated to be similar in topic. An example is shown in Figure
         2
         .
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p3">
        <p class="ltx_p">
         As in §
         4.1
         , we calculate precision and recall on pairs. This does not penalize the model for grouping together a “no” pair; we chose it nonetheless because it is interpretable.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiment
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        In this section, we evaluate the three HMM variants described in
§
        3
        , and two baselines,
using the methods in §
        4
        . All of the methods
require the specification of the number of groups or hidden states,
which we fix to ten, the average number of sections per policy.
       </p>
      </div>
      <div class="ltx_paragraph" id="S5.SS2.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Baselines.
       </h4>
       <div class="ltx_para" id="S5.SS2.SSS0.P1.p1">
        <p class="ltx_p">
         Our first baseline is a greedy divisive clustering algorithm
         to partition the policy
sections into ten clusters. In this method, the desired
         K
         -way
clustering solution is computed by performing a sequence of bisections. The implementation uses unigram features and
cosine similarity.
Our second baseline is latent Dirichlet allocation (LDA;
         Blei et al., 2003), with ten topics and online variational Bayes for inference
         [11]
         .
         To more closely match our models, LDA is given access to the same
unigram and bigram tokens.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S5.SS2.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Results.
       </h4>
       <div class="ltx_para" id="S5.SS2.SSS0.P2.p1">
        <p class="ltx_p">
         Table
         3
         shows the results. For LDA and the HMM
variants (which use random initialization), we report mean and
standard deviation across ten independent runs. All three variants of the HMM improve over the baselines on both tasks, in terms of
         F1
         . In the human QA evaluation, this is mostly due to recall improvements (i.e., more pairs of sections relevant to the same policy question were grouped together).
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.SSS0.P2.p2">
        <p class="ltx_p">
         The three variants of the model performed similarly on average, though Strict Forward had very high variance. Its maximum performance across ten runs was very high (67% and 53%
         F1
         on the two tasks), suggesting the potential benefits of good initialization or model selection.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
