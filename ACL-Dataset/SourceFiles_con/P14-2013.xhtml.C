<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Graph Ranking for Collective Named Entity Disambiguation.
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
       Named Entity Disambiguation (NED) refers to the task of mapping different named entity mentions
in running text to their correct interpretations in a specific knowledge base (KB).
This paper presents a collective disambiguation approach using a graph model. All possible NE candidates are represented as nodes in the graph and associations between different candidates are represented by edges between the nodes. Each node has an initial confidence score, e.g. entity popularity. Page-Rank is used to rank nodes and the final rank is combined with the initial confidence for candidate selection.
Experiments on 27,819 NE textual mentions show the effectiveness of using Page-Rank in conjunction with initial confidence: 87% accuracy is achieved, outperforming both baseline and state-of-the-art approaches.
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
        Named entities (NEs) have received much attention over the last two decades
        [14]
        , mostly focused on recognizing the boundaries of textual NE mentions and classifying them as, e.g., Person, Organization or Location. However, references to entities in the real world are often ambiguous: there is a many-to-many relation between NE mentions and the entities they denote in the real world.
For example,
        Norfolk
        may refer to a person, “Peter Norfolk, a wheelchair tennis player”, a place in the UK, “Norfolk County”, or in the US, “Norfolk, Massachusetts”; conversely, one entity may be known by many names, such as “Cat Stevens”, “Yusuf Islam” and “Steven Georgiou”. The NED task is to establish a correct mapping between each NE mention in a document and the real world entity it denotes.
Following most researchers in this area, we treat entries in a large knowledge base (KB) as surrogates for real world entities when carrying out NED and, in particular, use Wikipedia as the reference KB for disambiguating NE mentions.
NED is important for tasks like KB population, where we want to extract new information from text about an entity and add this to a pre-existing entry in a KB; or for information retrieval, where we may want to cluster or filter results for different entities with the same textual mentions.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The main hypothesis in this work is that different NEs in a document help to disambiguate each other.
The problem is that other textual mentions in the document are also ambiguous. So, what is needed is a
        collective disambiguation
        approach that jointly disambiguates all NE textual mentions.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In our approach we model each possible candidate for every NE mention in a document as a distinct node in a graph and model candidate coherence by links between the nodes. We call such graphs
        solution graphs
        . Figure
        1
        shows an example of the solution graph for three mentions “A”, “B”, and “C” found in a document, where the candidate entities for each mention are referred to using the lower case form of the mention’s letter together with a distinguishing subscript.
The goal of disambiguation is to find a set of nodes where only one candidate is selected from the set of entities associated with each mention, e.g.
        a3
        ,
        b2
        ,
        c2
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        Our approach first ranks all nodes in the solution graph using the Page-Rank algorithm, then re-ranks all nodes by combining the initial confidence and graph ranking scores. We consider several different measures for computing the initial confidence assigned to each node and several measures for determining and weighting the graph edges. Node linking relies on the fact that
the textual portion of KB entries typically contains mentions of other NEs. When these mentions are hyper-linked to KB entries, we can infer that there is some relation between the real world entities corresponding to the KB entries, i.e. that they should be linked in our solution graph. These links also allow us to build up statistical co-occurrence counts between entities that occur in the same context which may be used to weight links in our graph.
       </p>
      </div>
      <div class="ltx_para" id="S1.p5">
       <p class="ltx_p">
        We evaluate our approach on the AIDA dataset
        [10]
        . Comparison with the baseline approach and some state-of-the-art approaches shows our approach offers substantial improvements in disambiguation accuracy.
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
        In 2009, NIST proposed the shared task challenge of Entity Linking (EL)
        [12]
        . EL is a similar but broader task than NED because NED is concerned with disambiguating a textual NE mention where the correct entity is known to be one of the KB entries, while EL also requires systems to deal with the case where there is no entry for the NE in the reference KB.
Ji et al.
        [11]
        group and summarise the different approaches to EL taken by participating systems.
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        In general, there are two main lines of approach to the NED problem.
        Single entity disambiguation approaches (SNED)
        , disambiguate one entity at a time without considering the effect of other NEs. These approaches use local context textual features of the mention and compare them to the textual features of NE candidate documents in the KB, and link to the most similar. The first approach in this line was Bunescu and Pasca
        [4]
        , who measure similarity between the textual context of the NE mention and the Wikipedia categories of the candidate. More similarity features were added by Cucerzan
        [5]
        who realized that topical coherence between a candidate entity and other entities in the context will improve NED accuracy and by
Milne and Witten
        [13]
        who built on Cucerzan’s work.
Han and Sun
        [9]
        combine different forms of disambiguation knowledge using evidence from mention-entity associations and entity popularity in the KB, and context similarity.
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        The second line of approach is
        collective named entity disambiguation (CNED)
        , where all mentions of entities in the document are disambiguated jointly. These approaches try to model the interdependence between the different candidate entities for different NE mentions in the query document, and reformulate the problem of NED as a global optimization problem whose aim is to find the best set of entities. As this new formulation is NP-hard, many approximations have been proposed.
Alhelbawy and Gaizauskas
        [2]
        proposed a sequence dependency model using HMMs to model NE interdependency. Another approximation uses a mixture of local and global features to train the coefficients of a linear ranking SVM to rank different NE candidates
        [17]
        . Shirakawa et al.
        [18]
        cluster related textual mentions and assign a concept to each cluster using a probabilistic taxonomy. The concept associated with a mention is used in selecting the correct entity from the Freebase KB.
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        Graph models are widely used in collective approaches
        . All these approaches model NE interdependencies, while different methods may be used for disambiguation. Han
        [8]
        uses local dependency between NE mention and the candidate entity, and semantic relatedness between candidate entities to construct a referent graph, proposing a collective inference algorithm to infer the correct reference node in the graph. Hoffert
        [10]
        poses the problem as one of finding a dense sub-graph, which is infeasible in a huge graph. So, an algorithm originally used to find strongly interconnected, size-limited groups in social media is adopted to prune the graph, and then a greedy algorithm is used to find the densest graph.
       </p>
      </div>
      <div class="ltx_para" id="S2.p5">
       <p class="ltx_p">
        Our proposed model uses the Page-Rank (PR) algorithm
        [16]
        , which to our knowledge has not previously been applied to NED.
Xing and Ghorbani
        [20]
        adopted PR to consider the weights of links and the nodes’ importance. PR and Personalized PR algorithms have been used successfully in WSD
        [19, 1]
        .
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Solution Graph
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In this section we discuss the construction of a graph representation that we call the
        solution graph
        . The input is a document containing pre-tagged NE textual mentions. The solution graph is an undirected graph
        G=(V,D)
        where
        V
        is the node set of all possible NE candidates for different textual mentions in the input document and
        D
        is the set of edges between nodes. Edges are not drawn between different nodes for the same mention. They are drawn between two entities when there is a relation between them, as described below.
Each candidate has associated with it an initial confidence score, also detailed below.
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        Assume the input document
        D
        has a set of mentions
        M={m1,m2,m3,…,mk}
        . For each
        mi∈M
        , we rank each candidate entity, where the list of candidates for a mention
        mi
        is
        Ei={ei,1,ei,2,…,ei,j}
        .
The graph nodes are formulated as a set
        V={(mi,ei,j)∣∀ei,j∈Ei,∀mi∈M}
        . Nodes are represented as ordered pairs of textual mentions and candidate entities, since the same entity may be found multiple times as a candidate for different textual mentions and each occurrence must be evaluated independently.
       </p>
      </div>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        NE Candidate Generation
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The first step in constructing a solution graph is to find all possible candidates for each NE mention in the query document.
For each such mention the KB entry titles are searched to find all entries to which the mention could refer. This includes entries with titles that fully or partially contain the query mention and those that could be an acronym of the query mention.
These candidate entries are paired with their textual mentions in the document to become nodes in the solution graph.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Initial Confidence
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         Initial confidence
         I⁢C⁢o⁢n⁢f⁢(ei,j)
         is an independent feature of the NE candidate regardless of other candidates in the document. This confidence may be calculated locally using the local mention context, or globally using, e.g., the Freebase popularity score for the KB entry
         [3]
         .
        </p>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Local NE Candidate Confidence:
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          The local confidence is computed by a similarity measure between the NE mention in the query document and the KB entry of the candidate entity. We propose four different measures to be used in the disambiguation phase.
          <span class="ltx_text ltx_font_bold">
           cos:
          </span>
          The cosine similarity between the named entity textual mention and the KB entry title.
          <span class="ltx_text ltx_font_bold">
           jwSim:
          </span>
          While the cosine similarity between a textual mention in the document and the candidate NE title in the KB is widely used in NED, this similarity is a misleading feature. For example, the textual mention “Essex” may refer to either of the following candidates “Essex County Cricket Club” or “Danbury, Essex”, both of which are returned by the candidate generation process. The cosine similarity between “Essex” and “Danbury, Essex” is higher than that between “Essex” and “Essex County Cricket Club”, which is not helpful in the NED setting.
We adopted a new mention-candidate similarity function,
          j⁢w⁢S⁢i⁢m
          , which uses Jaro-Winkler similarity as a first estimate of the initial confidence value for each candidate. This function considers all terms found in the candidate entity KB entry title, but not in the textual mention as disambiguation terms.
The percentage of disambiguation terms found in the query document is used to boost in the initial
          j⁢w⁢S⁢i⁢m
          value, in addition to an acronym check (whether the NE textual mention could be an acronym for a specific candidate entity title).
Experiments show that
          j⁢w⁢S⁢i⁢m
          performs much better than
          c⁢o⁢s
          .
          <span class="ltx_text ltx_font_bold">
           ctxt:
          </span>
          The cosine similarity between the sentence containing the NE mention in the query document and the textual description of the candidate NE in the KB (we use the first section of the Wikipedia article as the candidate entity description).
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Global NE Candidate Confidence:
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          Global confidence is a measure of the global importance of the candidate entity. Entity popularity has been used successfully as a discriminative feature for NED
          [15]
          . Freebase provides an API to get an entity’s popularity score (
          FB
          ), which is computed during Freebase indexing. This score is a function of the entity’s inbound and outbound link counts in Freebase and Wikipedia
          .
The initial confidence is not normalized across all NEs because each score is calculated independently. Initial confidence scores of all candidates for a single NE mention are normalized to sum to 1.
         </p>
        </div>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.3
        </span>
        Entity Coherence
       </h3>
       <div class="ltx_para" id="S3.SS3.p1">
        <p class="ltx_p">
         Entity coherence refers to the real world relatedness of different entities which are candidate interpretations of different textual mentions in the document. It is not based on context, so it is always the same regardless of the query document.
Coherence is represented as an edge between nodes in the solution graph. We used two measures for coherence, described as follows:
        </p>
       </div>
       <div class="ltx_paragraph" id="S3.SS3.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Ref:
        </h4>
        <div class="ltx_para" id="S3.SS3.SSS0.P1.p1">
         <p class="ltx_p">
          Uses the Wikipedia documents for both entity candidates to check if either document has a link to the other. This relation is directed, but we assume an inverse relation also exists; so this relation is represented as undirected.
         </p>
         Ref⁢(ei,ej)={1,if ei or ej refers to the other0,otherwise

(1)
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS3.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         JProb:
        </h4>
        <div class="ltx_para" id="S3.SS3.SSS0.P2.p1">
         <p class="ltx_p">
          An estimate of the probability of both entities appearing in the same sentence. Wikipedia documents are used to estimate this probability, as shown in (
          2
          ), where
          S⁢(e)
          is the set of all sentences that contain the entity
          e
          and
          S
          the set of sentences containing any entity references.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS3.SSS0.P2.p2">
         JProb⁢(ei,ej)=|S⁢(ei)⁢⋂S⁢(ej)||S|

(2)
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Disambiguation
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        The solution graph contains all possible candidates for each NE mention in the document. Each candidate has an initial confidence, with some connected by association relations. The disambiguation phase ranks all nodes in the solution graph and selects the best from the candidate list for each NE textual mention. The process of disambiguation consists of three steps. The first step is initial graph ranking, where all nodes are ranked according to the link structure. The second step is to re-rank the nodes by combining the graph rank with the initial confidence.
The highest rank is not always correct, so in the third step a selection algorithm is used to choose the best candidate.
       </p>
      </div>
      <div class="ltx_paragraph" id="S4.SS3.SSS0.P1">
       <h4 class="ltx_title ltx_title_paragraph">
        Graph Ranking:
       </h4>
       <div class="ltx_para" id="S4.SS3.SSS0.P1.p1">
        <p class="ltx_p">
         The links between different candidates in the solution graph represent real world relations. These relations may be used to reliably boost relevant candidates. All nodes in the graph are ranked according to these relations using PR. Initial confidence is used as an initial rank for the graph nodes, while entities’ coherence measures are used as link weights which play a role in distributing a node’s rank over its outgoing nodes.
        </p>
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS3.SSS0.P2">
       <h4 class="ltx_title ltx_title_paragraph">
        Candidate Re-ranking:
       </h4>
       <div class="ltx_para" id="S4.SS3.SSS0.P2.p1">
        <p class="ltx_p">
         A problem with Page-Rank for our purposes is the dissipation of initial node weight (confidence) over all outgoing nodes. The final rank of a node is based solely on the importance of incoming nodes and the initial confidence play no further role. In our case this is not appropriate, so
the final rank for each mention is determined after graph ranking, by combining the graph rank with the initial confidence.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.SSS0.P2.p2">
        <p class="ltx_p">
         Let us refer to the graph rank of a candidate as
         P⁢R⁢(ei)
         . Two combination schemes
are used:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.SSS0.P2.p3">
        Rs⁢(ei,j)=I⁢C⁢o⁢n⁢f⁢(ei,j)+P⁢R⁢(ei,j)

(3)
        Rm⁢(ei,j)=I⁢C⁢o⁢n⁢f⁢(ei,j)×P⁢R⁢(ei,j)

(4)
       </div>
      </div>
      <div class="ltx_paragraph" id="S4.SS3.SSS0.P3">
       <h4 class="ltx_title ltx_title_paragraph">
        Named Entity Selection:
       </h4>
       <div class="ltx_para" id="S4.SS3.SSS0.P3.p1">
        <p class="ltx_p">
         The simplest approach is to select the highest ranked entity in the list for each mention
         mi
         according to equation
         5
         , where
         R
         could refer to
         Rm
         or
         Rs
         . However, we found that a dynamic choice between the re-ranking schemes, based on the difference between the top two candidates, as described in algorithm
         4
         and indicated by
         eg
         ,works best.
The underlying intuition of this algorithm is that a greater difference between the top ranks reflects more confident discrimination between candidates. So, the two combination schemes assign different ranks to the candidates and the algorithm selects the scheme which appears more discriminative.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS3.SSS0.P3.p2">
        e^i=argmaxei,j⁢R⁢(ei,j)

(5)
       </div>
       <span class="ltx_ERROR undefined">
        \KwData
       </span>
       <div class="ltx_para" id="S4.SS3.SSS0.P3.p3">
        <p class="ltx_p">
         Two lists, R1 and R2, of candidates Ei, where R1 is ranked using Rs, and R2 is ranked using Rm
One NE eig
Sort R1 and R2 in descending order 
R1diff = R1[0]-R1[1] 
R2diff = R2[0]-R2[1] 
R1diff &gt; R2diff
return highest rank scored entity of R1

return highest rank scored entity of R2

Selection Algorithm
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experiments and Results
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        We used AIDA dataset
        , which is based on the CoNLL 2003 data for NER tagging. All mentions are manually disambiguated against Wikipedia
        [10]
        .
This dataset contains 1393 documents and 34,965 annotated mentions. We only consider NE mentions with an entry in the Wikipedia KB, ignoring the 20% of query mentions (7136) without a link to the KB, as Hoffart did.
Micro-averaged and macro-averaged accuracy are used for evaluation.
In this context micro-averaged accuracy corresponds to the
proportion of textual mentions correctly disambiguated
while macro-averaged accuracy corresponds to the proportion of textual mentions correctly disambiguated per entity, averaged over all entities.
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         Initially, we evaluated the performance of two baselines. One is a setup where a ranking based solely on different initial confidence scores is used for candidate selection, i.e. without using PR. In this setup a ranking based on Freebase popularity does best, with micro- and macro-averaged accuracy scores of 80.55% and 78.09% respectively. This is a high baseline, close to the state-of-the-art. Our second baseline is the basic PR algorithm, where weights of nodes and edges are uniform (i.e. initial node and edge weights set to 1, edges being created wherever REF or JProb are not zero). Micro and macro accuracy scores of 70.60% and 60.91% were obtained with this baseline.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         To study graph ranking using PR, and the contributions of the initial confidence and entity coherence,
experiments were carried out using PR in different modes and with different selection techniques.
In the first experiment, referred to as
         P⁢RI
         ,
initial confidence is used as an initial node rank for PR and edge weights are uniform, edges, as in the PR baseline, being created wherever REF or JProb are not zero.
Table
         2
         shows the results both before re-ranking, i.e. using only the
         P⁢R
         score for ranking, and after re-ranking using the dynamic selection scheme
         eg
         .
When comparing these results to the PR baseline we notice a slight positive effect when using the initial confidence as an initial rank instead of uniform ranking. The major improvement comes from re-ranking nodes by combining initial confidence with PR score.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         In our second experiment,
         P⁢RC
         , entity coherence features are tested by setting the edge weights to the coherence score and using uniform initial node weights.
We compared JProb and Ref edge weighting approaches, where for each approach edges were created only where the coherence score according to the approach was non-zero. We also investigated a variant, called JProb + Ref, in which the Ref edge weights are normalized to sum to 1 over the whole graph and then added to the JProb edge weights (here edges result wherever JProb or Ref scores are non-zero).
Results in Table
         3
         show the
         J⁢P⁢r⁢o⁢b
         feature seems to be more discriminative than the
         R⁢e⁢f
         feature but the combined
         J⁢p⁢r⁢o⁢b+R⁢e⁢f
         feature performs better than each separately, just outperforming the baseline.
We used the best initial confidence score (Freebase) for re-ranking. Again, combining the initial confidence with the PR score improves the results.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         Finally, Table
         4
         shows the accuracy when using different combinations of initial confidence and entity coherence scores just in the case when re-ranking is applied. Here the
         j⁢p⁢r⁢o⁢b+r⁢e⁢f⁢s
         combination does not add any value over
         j⁢p⁢r⁢o⁢b
         alone. Interestingly using initial confidence with differentially weighted edges does not show any benefit over using initial confidence and uniformly weighted edges (Table
         2
         ).
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p5">
        <p class="ltx_p">
         To compare our results with the state-of-the-art, we report Hoffart et al.’s
         [10]
         results as they re-implemented two other systems and also ran them over the AIDA dataset. We also compare with
Alhelbawy and Gaizauskas
         [2]
         and Shirakawa et al.
         [18]
         who carried out their experiments using the same dataset. Table
         1
         presents a comparison between our approach and the state-of-the-art and shows our approach exceeds the state-of-the-art. Futhermore our approach is very simple and direct to apply, unlike Hoffart et al.’s and Shirakawa et al.’s which are considerably more complex. Also, our approach does not need any kind of training, as does the Alhelbawy approach.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
