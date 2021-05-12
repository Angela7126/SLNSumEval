<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Sliding Alignment Windows for Real-Time Crowd Captioning.
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
       The primary way of providing real-time speech to text captioning for hard
of hearing people is to employ expensive professional stenographers
who can type as fast as natural speaking rates. Recent work has shown
that a feasible alternative is to combine the partial captions of
ordinary typists, each of whom is able to type only part of what they hear.
In this paper, we extend the state of the art fixed-window alignment
algorithm
       []
       for combining the individual captions into
a final output sequence. Our method performs alignment on a sliding window
of the input sequences, drastically reducing both the number of errors and
the latency of the system to the end user over the previously published approaches.
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
        Real-time captioning provides deaf or hard of hearing people access to speech in mainstream classrooms, at public events, and on live television.
Studies performed in the classroom setting show that the latency between when a word was said and when it is displayed must be under five seconds to maintain consistency between the captions being read and other visual cues
        []
        .
The most common approach to real-time captioning is to recruit a trained stenographer with a special purpose phonetic keyboard, who transcribes the speech to text with less than five seconds of latency.
Unfortunately, professional captionists are quite expensive ($150 per hour), must be recruited in blocks of an hour or more, and are difficult to schedule on short notice.
Automatic speech recognition (ASR) systems
        []
        , on the other hand, attempts to provide a cheap and fully automated solution to this problem.
However, the accuracy of ASR quickly plummets to below 30% when used on an untrained speaker’s voice, in a new environment, or in the absence of a high quality microphone
        []
        .
The accuracy of the ASR systems can be improved using the ‘re-speaking’ technique, which requires a person that the ASR has been trained on to repeat the words said by a speaker as he hears them. Simultaneously hearing and speaking, however, is not straightforward, and requires some training.
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        An alternative approach is to combine the efforts of multiple
non-expert captionists (anyone who can type), instead of relying
on trained workers
        []
        . In this
approach, multiple non-expert human workers transcribe an audio
stream containing speech in real-time. Workers type as much as
they can of the input, and, while no one worker’s transcript is
complete, the portions captured by various workers tend to
overlap. For each input word, a timestamp is recorded,
indicating when the word is typed by a worker. The partial inputs
are combined to produce a final transcript (see Figure 1). This
approach has been shown to dramatically outperform ASR in terms
of both accuracy and Word Error Rate
(WER)
        []
        .
Furthermore, recall of individual words irrespective of their order approached and even exceeded that of a trained expert stenographer with seven workers contributing, suggesting that the information is present to meet the performance of a stenographer
        []
        . However, aligning these individual words in the correct sequential order remains a challenging problem.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        Lasecki et al.
        []
        addressed this alignment problem using
off-the-shelf multiple sequence alignment tools, as well as an
algorithm based on incrementally building a precedence graph over
output words.
Improved results for the alignment problem were shown using weighted A
        *
        search by
Naim et al.
        []
        .
To speed the search for the best alignment, Naim et al.
        []
        divided sequences
into chunks of a fixed time duration, and applied the
A
        *
        alignment algorithm to each chunk independently. Although this method speeds the search for the best alignment, it introduces a significant number of errors to the output of the system due to inconsistency at the boundaries of the chunks.
In this paper, we introduce a novel sliding window technique which
avoids the errors produced by previous systems at the boundaries
of the chunks used for alignment. This technique produces
dramatically fewer errors for the same amount of computation time.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Problem Overview and Background
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        The problem of aligning and combining multiple transcripts can be mapped to the well-studied Multiple Sequence Alignment (MSA) problem
        []
        .
Let
        S1,…,SK,K≥2
        , be the
        K
        sequences over an alphabet
        Σ
        , and having length
        N1,…,NK
        . For the caption alignment task, we treat each individual word as a symbol in our alphabet
        Σ
        . The special gap symbol ‘
        -
        ’ represents a missing word and does not belong to
        Σ
        . Let
        A=(ai⁢j)
        be a
        K×Nf
        matrix, where
        ai⁢j∈Σ∪{-}
        , and the
        it⁢h
        row has exactly
        (Nf-Ni)
        gaps and is identical to
        Si
        if we ignore the gaps. Every column of
        A
        must have at least one non-gap symbol. Therefore, the
        jt⁢h
        column of
        A
        indicates an alignment state for the
        jt⁢h
        position, where the state can have one of the
        2K-1
        possible combinations. Our goal is to find the optimum alignment matrix
        AO⁢P⁢T
        that minimizes the sum of pairs (SOP) cost function:
       </p>
       c⁢(A)=∑1≤i≤j≤Kc⁢(Ai⁢j)

(1)
       <p class="ltx_p">
        where
        c⁢(Ai⁢j)
        is the cost of the pairwise alignment between
        Si
        and
        Sj
        according to
        A
        . Formally,
        c⁢(Ai⁢j)=∑l=1Nfsub⁢(ai⁢l,aj⁢l)
        , where
        sub⁢(ai⁢l,aj⁢l)
        denotes the cost of substituting
        aj⁢l
        for
        ai⁢l
        . If
        ai⁢l
        and
        aj⁢l
        are identical, the substitution cost is zero. The substitution cost for two words is estimated based on the edit distance between two words. The exact solution to the SOP optimization problem is NP-Complete
        []
        , but many methods solve it approximately. Our approach is based on weighted A
        *
        search for approximately solving the MSA problem
        []
        .
        [t]
        MSA-A* Algorithm
        [1]
        <math alttext="K" class="ltx_Math" display="inline" id="S2.p1.m32" xmlns="http://www.w3.org/1998/Math/MathML">
         <mi>
          K
         </mi>
        </math>
        input sequences 𝒮={S1,…,SK} having length N1,…,NK, heuristic weight w, beam size b
       </p>
      </div>
      <div class="ltx_para" id="S2.p2">
       <p class="ltx_p">
        input s⁢t⁢a⁢r⁢t∈ℕK, g⁢o⁢a⁢l∈ℕk
       </p>
      </div>
      <div class="ltx_para" id="S2.p3">
       <p class="ltx_p">
        output an N×K matrix of integers indicating the index into each input sequence
of each position in the output sequence
g⁢(s⁢t⁢a⁢r⁢t)←0, f⁢(s⁢t⁢a⁢r⁢t)←w×h⁢(s⁢t⁢a⁢r⁢t).
Q←{s⁢t⁢a⁢r⁢t}
Q≠∅
n← EXTRACT-MIN(Q)
s∈{0,1}K-{0K}
ni←n+s
ni=g⁢o⁢a⁢l
Return the alignment matrix for the reconstructed path from s⁢t⁢a⁢r⁢t to ni
ni∉B⁢e⁢a⁢m⁢(b)
continue;
\STATEg⁢(ni)←g⁢(n)+c⁢(n,ni)
f⁢(ni)←g⁢(ni)+w×h⁢(ni)
INSERT-ITEM(Q,ni,f(ni))
\ENDFOR
       </p>
      </div>
      <div class="ltx_para" id="S2.p4">
       <p class="ltx_p">
        [t]
        Fixed Window Algorithm
        [1]
        <math alttext="K" class="ltx_Math" display="inline" id="S2.p4.m1" xmlns="http://www.w3.org/1998/Math/MathML">
         <mi>
          K
         </mi>
        </math>
        input sequences 𝒮={S1,…,SK} having length N1,…,NK, window parameter c⁢h⁢u⁢n⁢k⁢_⁢l⁢e⁢n⁢g⁢t⁢h.
\STATEs⁢t⁢a⁢r⁢t⁢_⁢t⁢i⁢m⁢e←0
g⁢o⁢a⁢l≺[N1,…,NK]
i
s⁢t⁢a⁢r⁢t⁢[i]←c⁢l⁢o⁢s⁢e⁢s⁢t⁢_⁢w⁢o⁢r⁢d⁢(i,s⁢t⁢a⁢r⁢t⁢_⁢t⁢i⁢m⁢e)
\STATEe⁢n⁢d⁢_⁢t⁢i⁢m⁢e←s⁢t⁢a⁢r⁢t⁢_⁢t⁢i⁢m⁢e+c⁢h⁢u⁢n⁢k⁢_⁢l⁢e⁢n⁢g⁢t⁢h
i
g⁢o⁢a⁢l⁢[i]←c⁢l⁢o⁢s⁢e⁢s⁢t⁢_⁢w⁢o⁢r⁢d⁢(i,e⁢n⁢d⁢_⁢t⁢i⁢m⁢e)-1
\STATEa⁢l⁢i⁢g⁢n⁢m⁢a⁢t⁢r⁢i⁢x←MSA-A(start,goal)*
concatenate a⁢l⁢i⁢g⁢n⁢m⁢a⁢t⁢r⁢i⁢x onto end of f⁢i⁢n⁢a⁢l⁢m⁢a⁢t⁢r⁢i⁢x
s⁢t⁢a⁢r⁢t⁢_⁢t⁢i⁢m⁢e←e⁢n⁢d⁢_⁢t⁢i⁢m⁢e
\STATEReturn f⁢i⁢n⁢a⁢l⁢m⁢a⁢t⁢r⁢i⁢x
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Weighted A
        *
        Search for MSA
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         The problem of minimizing the SOP cost function for
         K
         sequences
is equivalent to estimating the shortest path between a single source node and a single sink node in a
         K
         -dimensional mesh graph,
where each node corresponds to a distinct position in the
         K
         sequences.
The source node is
         [0,…,0]
         and the sink node is
         [N1,…,NK]
         . The total number of nodes in the lattice is
         (N1+1)×(N2+1)×⋯×(NK+1)
         , and each node has
         2K-1
         possible successors and predecessors.
The A
         *
         search algorithm treats each node position
         n=[n1,…,nK]
         as a search state, and estimates the cost function
         g⁢(n)
         and the heuristic function
         h⁢(n)
         for each state. The cost function
         g⁢(n)
         represents the exact minimum SOP cost to align the
         K
         sequences from the beginning to the current position. The heuristic function represents the approximate minimum cost of aligning the suffixes of the
         K
         sequences, starting after the current position
         n
         .
The commonly used heuristic function is
         hp⁢a⁢i⁢r⁢(n)
         :
        </p>
        hp⁢a⁢i⁢r(n)=L(n→t)=∑1≤i&lt;j≤Kc(Ap*(σin,σjn))

(2)
        <p class="ltx_p">
         where
         L(n→t)
         denotes the lower bound on the cost of the
shortest path from
         n
         to destination
         t
         ,
         Ap*
         is the optimal pairwise alignment, and
         σin
         is the suffix of node
         n
         in the
         i
         -th sequence. The weighted A
         *
         search uses a priority queue
         Q
         to store the search states
         n
         .
At each step of the A
         *
         search algorithm, the node with the smallest evaluation function,
         f⁢(n)=g⁢(n)+w⁢hp⁢a⁢i⁢r⁢(n)
         (where
         w≥1
         ),
is extracted from the priority queue
         Q
         and expanded by one edge. The search continues until the goal node is extracted from
         Q
         . To further speed up the search, a beam constraint is applied on the search space using the timestamps of each individual input words. If the beam size is set to
         b
         seconds, then any state that aligns two words having more than
         b
         seconds time lag is ignored. The detailed procedure is shown in Algorithm
         2
         . After the alignment, the captions are combined via majority voting at each position of the alignment matrix. We ignore the alignment columns where the majority vote is below a certain threshold
         tv
         (typically
         tv=2
         ), and thus filter out spurious errors and spelling mistakes.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Although weighted A
         *
         significantly speeds the search for the best alignment, it is still too slow for very long sequences.
For this reason, Naim et al.
         []
         divided the sequences into chunks of a fixed time duration, and applied the A
         *
         alignment algorithm to each chunk independently.
The chunks were concatenated to produce the final output sequence, as shown in Algorithm
         2
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Limitations of Fixed Window Algorithm
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         The fixed window based alignment has two key limitations.
First, aligning disjoint chunks independently tends to introduce a large number of errors at the boundary of each chunk. This is because the chunk boundaries are defined with respect to the timestamps associated with each word in the captions, but the timestamps can vary greatly between words that should in fact be aligned. After all, if the timestamps
corresponded precisely to the original time at which each word was spoken, the entire alignment problem would be trivial.
The fact that the various instances of a single word in each transcription may fall on either side of a chunk boundary leads to errors where a word is either duplicated in the final output for more than one chunk, or omitted entirely. This problem also causes errors in ordering among the words remaining within one chunk, because there is less information available to constrain the ordering relations between transcriptions.
Second, the fixed window alignment algorithm requires longer chunks (
         ≥
         10 seconds) to obtain reasonable accuracy, and thus introduces unsatisfactory latency.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Sliding Alignment Windows
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        In order to address the problems described above, we explore a technique based on a sliding alignment window, shown in Algorithm
        3
        . We start with alignment with a fixed chunk size.
After aligning the first chunk, we use the information derived from the
alignment to determine where the next chunk should begin within each transcription. We use a single point in the aligned output as the starting point for the next chunk, and determine the corresponding starting position
within each original transcription.
This single point is determined by a tunable parameter
        k⁢e⁢e⁢p⁢_⁢l⁢e⁢n⁢g⁢t⁢h
        (line 10 of Algorithm
        3
        ).
The materials in the output alignment that follow this point is thrown away, and replaced with the output produced by aligning the next chunk starting from this point (line 8).
The process continues iteratively, allowing us to avoid using the erroneous output alignments in the neighborhood of the arbitrary endpoints for each chunk.
        [t]
        Sliding Window Algorithm
        [1]
        <math alttext="K" class="ltx_Math" display="inline" id="S3.p1.m2" xmlns="http://www.w3.org/1998/Math/MathML">
         <mi>
          K
         </mi>
        </math>
        input sequences 𝒮={S1,…,SK} having length N1,…,NK, window parameters c⁢h⁢u⁢n⁢k⁢_⁢l⁢e⁢n⁢g⁢t⁢h and k⁢e⁢e⁢p⁢_⁢l⁢e⁢n⁢g⁢t⁢h.

s⁢t⁢a⁢r⁢t←0K, g⁢o⁢a⁢l←0K
g⁢o⁢a⁢l≺[N1,…,NK]
e⁢n⁢d⁢t⁢i⁢m⁢e←c⁢h⁢u⁢n⁢k⁢_⁢l⁢e⁢n⁢g⁢t⁢h+maxi⁡t⁢i⁢m⁢e⁢(s⁢t⁢a⁢r⁢t⁢[i])
i
g⁢o⁢a⁢l⁢[i]←c⁢l⁢o⁢s⁢e⁢s⁢t⁢_⁢w⁢o⁢r⁢d⁢(i,e⁢n⁢d⁢t⁢i⁢m⁢e)
\STATEa⁢l⁢i⁢g⁢n⁢m⁢a⁢t⁢r⁢i⁢x←MSA-A(start,goal)*
concatenate first k⁢e⁢e⁢p⁢_⁢l⁢e⁢n⁢g⁢t⁢h columns of 
 a⁢l⁢i⁢g⁢n⁢m⁢a⁢t⁢r⁢i⁢x onto end of f⁢i⁢n⁢a⁢l⁢m⁢a⁢t⁢r⁢i⁢x
i
s⁢t⁢a⁢r⁢t⁢[i]←a⁢l⁢i⁢g⁢n⁢m⁢a⁢t⁢r⁢i⁢x⁢[k⁢e⁢e⁢p⁢_⁢l⁢e⁢n⁢g⁢t⁢h]⁢[i]
\ENDWHILEReturn f⁢i⁢n⁢a⁢l⁢m⁢a⁢t⁢r⁢i⁢x
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experimental Results
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We evaluate our system on a dataset of four 5-minute long audio clips of lectures in electrical engineering and chemistry lectures taken from MIT OpenCourseWare. The same dataset used by
        []
        and
        []
        .
Each audio clip is transcribed by 10 non-expert human workers in real time. We measure the accuracy in terms of Word Error Rate (WER) with respect to a reference transcription.
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        We are interested in investigating how the three key parameters of the algorithm, i.e., the chunk size (
        c
        ), the heuristic weight (
        w
        ) and the keep-length (
        k
        ), affect the system latency, the search speed, and the alignment accuracy.
The chunk size directly determines the latency of the system to the end user, as alignment cannot begin until an entire chunk is captured. Furthermore, the chunk size, the heuristic weight, and the keep-length help us to trade-off speed versus accuracy. We also compare the performance of our algorithm with that of the most accurate fixed alignment window algorithm
        []
        . The performance in terms of WER for sliding and fixed alignment windows is presented in Figure 2. Out of the systems in Figure 2, the first three systems consist of sliding alignment window algorithm with different values of keep-length parameter: (1) keep-length = 0.5; (2) keep-length = 0.67; and (3) keep-length = 0.85. The other systems are the graph-based algorithm of
        []
        , the MUSCLE algorithm of
        []
        , and the most accurate fixed alignment window algorithm of
        []
        . We set the heuristic weight parameter (
        w
        ) to 3 and the chunk size parameter (
        c
        ) to 5 seconds for all the three sliding window systems and the fixed window system. Sliding alignment window produces better results and outperforms the other algorithms even for large values of the keep-length parameter. The sliding alignment window with keep-length 0.5 achieves 0.5679 average accuracy in terms of (1-WER), providing a 18.09% improvement with respect to the most accurate fixed alignment window (average accuracy 0.4857). On the same dataset, Lasecki et al.
        []
        reported 36.6% accuracy using the Dragon Naturally Speaking ASR system (version 11.5 for Windows).
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        To show the trade-off between latency and accuracy, we fix the heuristic weight (
        w=3
        ) and plot the accuracy as a function of chunk size in Figure
        3
        .
We repeat this experiment for different values of keep-length. We observe that the sliding window approach dominates the fixed window approach across a wide range of chunk sizes. Furthermore, we can see that for smaller values of the
chunk size parameter, increasing the keep-length makes the system less accurate.
As the chunk size parameter increases, the performance of sliding window systems with different values of keep-length parameter converges. Therefore, at larger chunk sizes, for which there are smaller number of boundaries, the keep-length parameter has lower impact.
       </p>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Next, we show the trade-off between computation speed and accuracy in Figure 3, as we fix the heuristic weight and vary the chunk size over the range [5, 10, 15, 20, 30] seconds. Larger chunks are more accurately aligned but require computation time that grows as
        NK
        in the chunk size
        N
        in the worst case. Furthermore, smaller weights allow faster alignment, but provide lower accuracy.
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
