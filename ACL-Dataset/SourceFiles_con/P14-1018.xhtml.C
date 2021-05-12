<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Inferring User Political Preferences from Streaming Communications.
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
       Existing models for social media personal analytics assume access to
thousands of messages per user, even though most users author content
only sporadically over time. Given this sparsity, we: (i) leverage
content from the local neighborhood of a user; (ii) evaluate batch
models as a function of size and the amount of messages in various
types of neighborhoods; and (iii) estimate the amount of time and
tweets required for a dynamic model to predict user preferences. We
show that even when limited or no self-authored data is available,
language from friend, retweet and user mention communications provide
sufficient evidence for prediction. When updating models over time
based on Twitter, we find that political preference can be often be
predicted using roughly 100 tweets, depending on the context of user
selection, where this could mean hours, or weeks, based on the
author’s tweeting frequency.
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
        Inferring latent user attributes such as gender, age, and political preferences
        [30, 42, 6]
        automatically from
personal communications and social media including emails, blog posts or
public discussions has become increasingly popular with the web getting more social and volume of data available. Resources like Twitter
        or Facebook
        become extremely valuable for studying the underlying properties of such informal communications because of its volume, dynamic nature, and diverse population
        [18, 33]
        .
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        The existing batch models for predicting latent user attributes rely on thousands of tweets per author
        [31, 7, 27, 5, 42, 21]
        . However, most Twitter users are less prolific than those examined in these works, and thus do not produce the thousands of tweets required to obtain their levels of accuracy e.g., the median number of tweets produced by a random Twitter user per day is 10. Moreover, recent changes to Twitter API querying rates further restrict the speed of access to this resource, effectively reducing the amount of data that can be collected in a given time period.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        In this paper we analyze and go beyond static models formulating personal analytics in social media as a streaming task. We first evaluate batch models that are cognizant of low-resource prediction setting described above, maximizing the efficiency of content in calculating personal analytics. To the best of our knowledge, this is the first work that makes explicit the tradeoff between accuracy and cost (manifest as calls to the Twitter API), and optimizes to a different tradeoff than state-of-the-art approaches, seeking maximal performance when limited data is available. In addition, we propose streaming models for personal analytics that dynamically update user labels based on their stream of communications which has been addressed previously by
        Van Durme (2012b)
        . Such models better capture the real-time nature of evidence being used in latent author attribute predictions tasks. Our main contributions include:
       </p>
       <ul class="ltx_itemize" id="I1">
        <li class="ltx_item" id="I1.ix1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          -
         </span>
         <div class="ltx_para" id="I1.ix1.p1">
          <p class="ltx_p">
           develop low-resource and real-time dynamic approaches for personal analytics using as an example the prediction of political preference of Twitter users;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          -
         </span>
         <div class="ltx_para" id="I1.ix2.p1">
          <p class="ltx_p">
           examine the relative utility of six different notions of “similarity” between users in an implicit Twitter social network for personal analytics;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I1.ix3" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          -
         </span>
         <div class="ltx_para" id="I1.ix3.p1">
          <p class="ltx_p">
           experiments are performed across multiple datasets supporting the prediction of political preference in Twitter, to highlight the significant differences in performance that arise from the underlying collection and annotation strategies.
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Identifying Twitter Social Graph
      </h2>
      <div class="ltx_para" id="S2.p1">
       <p class="ltx_p">
        Twitter users interact with one another and engage in direct communication in different ways e.g., using retweets, user mentions e.g.,
        @youtube
        or hashtags e.g.,
        #tcot
        , in addition to having explicit connections among themselves such as following, friending. To investigate all types of social relationships between Twitter users and construct Twitter social graphs we collect lists of followers and friends, and extract user mentions, hashtags, replies and retweets from communications.
       </p>
      </div>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        Social Graph Definition
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Lets define an attributed, undirected graph
         G=(V,E)
         , where
         V
         is a set of vertices and
         E
         is a set of edges. Each vertex
         vi
         represents someone in a communication graph i.e.,
         communicant
         : here a Twitter user. Each vertex is attributed with a feature vector
         f→⁢(vi)
         which encodes communications e.g., tweets available for a given user. Each vertex is associated with a latent attribute
         a⁢(vi)
         , in our case it is binary
         a⁢(vi)∈{D,R}
         , where
         D
         stands for Democratic and
         R
         for Republican users. Each edge
         ei⁢j∈E
         represents a connection between
         vi
         and
         vj
         ,
         ei⁢j=(vi,vj)
         and defines different social circles between Twitter users e.g., follower
         (f)
         , friend
         (b)
         , user mention
         (m)
         , hashtag
         (h)
         , reply
         (y)
         and retweet
         (w)
         . Thus,
         E∈V(2)×{f,b,h,m,w,y}
         . We denote a set of edges of a given type as
         ϕr⁢(E)
         for
         r∈{f,b,h,m,w,y}
         . We denote a set of vertices adjacent to
         vi
         by social circle type
         r
         as
         Nr⁢(vi)
         which is equivalent to
         {vj∣ei⁢j∈ϕr⁢(E)}
         . Following
         Filippova (2012)
         we refer to
         Nr⁢(vi)
         as
         vi
         ’s social circle, otherwise known as a neighborhood. In most cases, we only work with a sample of a social circle, denoted by
         Nr′⁢(vi)
         where
         |Nr′⁢(vi)|=k
         is its size for
         vi
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Figure
         1
         presents an example of a social graph derived from Twitter. Notably, users from different social circles can be shared across the users of the same or different classes e.g., a user
         vj
         can be in both follower circle
         vj∈Nf⁢(vi),vi∈D
         and retweet circle
         vj∈Nw⁢(vk),vk∈R
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        Candidate-Centric Graph
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         We construct candidate-centric graph
         Gc⁢a⁢n⁢d
         by looking into following relationships between the users and Democratic or Republican candidates during the 2012 US Presidential election. In the Fall of 2012, leading up to the elections, we randomly sampled
         n=516
         Democratic and
         m=515
         Republican users.
We labeled users as Democratic if they exclusively follow both Democratic candidates
         – BarackObama and JoeBiden but do not follow both Republican candidates – MittRomney and RepPaulRyan and vice versa. We collectively refer to
         D
         and
         R
         as our “users of interest” for which we aim to predict political preference. For each such user we collect recent tweets and randomly sample their immediate
         k=10
         neighbors from follower, friend, user mention, reply, retweet and hashtag social circles.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        Geo-Centric Graph
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         We construct a geo-centric graph
         Gg⁢e⁢o
         by collecting
         n=135
         Democratic and
         m=135
         Republican users from the Maryland, Virginia and Delaware region of the US with self-reported political preference in their biographies. Similar to the candidate-centric graph, for each user we collect recent tweets and randomly sample user social circles in the Fall of 2012. We collect this data to get a sample of politically less active users compared to the users from candidate-centric graph.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        ZLR Graph
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         We also consider a
         GZ⁢L⁢R
         graph constructed from a dataset previously used for political affiliation classification
         [42]
         . This dataset consists of 200 Republican and 200 Democratic users associated with 925 tweets on average per user.
         Each user has on average 6155 friends with 642 tweets per friend. Sharing restrictions and rate limits on Twitter data collection only allowed us to recreate a semblance of ZLR data
         – 193 Democratic and 178 Republican users with 1K tweets per user, and 20 neighbors of four types including follower, friends, user mention and retweet with 200 tweets per neighbor for each user of interest.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       Batch Models
      </h2>
      <div class="ltx_para" id="S3.p1">
       <p class="ltx_p">
        Baseline User Model
        As input we are given a set of vertices representing users of interest
        vi∈V
        along with feature vectors
        f→⁢(vi)
        derived from content authored by the user of interest. Each user is associated with a non-zero number of publicly posted tweets. Our goal is assign to a category each user of interest
        vi
        based on
        f→⁢(vi)
        . Here we focus on a binary assignment into the categories Democratic
        D
        or Republican
        R
        . The log-linear model
        for such binary classification is:
       </p>
       Φvi={D(1+exp⁡[-θ→⋅f→⁢(vi)])-1≥0.5,Rotherwise.

(1)
       <p class="ltx_p">
        where features are normalized word ngram counts extracted from
        vi
        ’s tweets
        f→t⁢(vi):D×t⁢(vi)→ℝ
        .
       </p>
      </div>
      <div class="ltx_para" id="S3.p2">
       <p class="ltx_p">
        The proposed baseline model follows the same trends as the existing state-of-the-art approaches for user attribute classification in social media as described in Section
        8
        . Next we propose to extend the baseline model by taking advantage of language in user social circles as describe below.
       </p>
      </div>
      <div class="ltx_para" id="S3.p3">
       <p class="ltx_p">
        Neighbor Model
        As input we are given user-local neighborhood
        Nr⁢(vi)
        , where
        r
        is a neighborhood type. Besides the neighborhood’s type
        r
        , each is characterized by:
       </p>
       <ul class="ltx_itemize" id="I2">
        <li class="ltx_item" id="I2.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i1.p1">
          <p class="ltx_p">
           the number of communications per neighbor
           f→t⁢(Nr)
           ,
           t={5,10,15,25,50,100,200}
           ;
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I2.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I2.i2.p1">
          <p class="ltx_p">
           the order of the social circle – the number of neighbors per user of interest
           |Nr|=d⁢e⁢g⁢(vi)
           ,
           n={1,2,5,10}
           .
          </p>
         </div>
        </li>
       </ul>
      </div>
      <div class="ltx_para" id="S3.p4">
       <p class="ltx_p">
        Our goal is to classify users of interest using evidence (e.g., communications) from their local neighborhood
        ∑nf→t⁢[Nr⁢(vi)]≡f→⁢(Nr)
        as Democratic or Republican. The corresponding log-linear model is defined as:
       </p>
       ΦNr={D(1+exp⁡[-θ→⋅f→⁢(Nr)])-1≥0.5,Rotherwise.

(2)
      </div>
      <div class="ltx_para" id="S3.p5">
       <p class="ltx_p">
        To check whether our static models are cognizant of low-resource prediction settings we compare the performance of the user model from Eq.
        1
        and the neighborhood model from Eq.
        2
        . Following the streaming nature of social media, we see the scarce available resource as the number of requests allowed per day to the Twitter API. Here we abstract this to a model assumption where we receive one tweet
        tk
        at a time and aim to maximize classification performance with as few tweets per user as possible:
       </p>
       <ul class="ltx_itemize" id="I3">
        <li class="ltx_item" id="I3.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i1.p1">
          <p class="ltx_p">
           for the baseline user model:
          </p>
          <table class="ltx_equationgroup" id="S3.E3">
           <tr class="ltx_equation ltx_align_baseline" id="S3.E3X">
            <td class="ltx_eqn_center_padleft">
            </td>
            <td class="ltx_td">
            </td>
            <td class="ltx_td ltx_align_left">
             minimize𝑘
            </td>
            <td class="ltx_td">
            </td>
            <td class="ltx_td ltx_align_left">
             ∑ktk⁢(vi),
            </td>
            <td class="ltx_eqn_center_padright">
            </td>
            <td class="ltx_align_middle ltx_align_right" rowspan="1">
             <span class="ltx_tag ltx_tag_equationgroup">
              (3)
             </span>
            </td>
           </tr>
          </table>
         </div>
        </li>
        <li class="ltx_item" id="I3.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I3.i2.p1">
          <p class="ltx_p">
           for the neighborhood model:
          </p>
          <table class="ltx_equationgroup" id="S3.E4">
           <tr class="ltx_equation ltx_align_baseline" id="S3.E4X">
            <td class="ltx_eqn_center_padleft">
            </td>
            <td class="ltx_td">
            </td>
            <td class="ltx_td ltx_align_left">
             minimize𝑘
            </td>
            <td class="ltx_td">
            </td>
            <td class="ltx_td ltx_align_left">
             ∑n∑ktk⁢[Nr⁢(vi)].
            </td>
            <td class="ltx_eqn_center_padright">
            </td>
            <td class="ltx_align_middle ltx_align_right" rowspan="1">
             <span class="ltx_tag ltx_tag_equationgroup">
              (4)
             </span>
            </td>
           </tr>
          </table>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Streaming Models
      </h2>
      <div class="ltx_para" id="S4.p1">
       <p class="ltx_p">
        We rely on straightforward Bayesian rule update to our batch models
in order to simulate a real-time streaming prediction scenario as a
first step beyond the existing models as shown in
Figure
        2
        .
       </p>
      </div>
      <div class="ltx_para" id="S4.p2">
       <p class="ltx_p">
        The model makes predictions of a latent user attribute e.g., Republican under a model assumption of sequentially arriving, independent and identically distributed observations
        T=(t1,…,tk)
        . The model dynamically updates posterior probability estimates
        p(a(vi)=R|tk)
        for a given user
        vi
        as an additional evidence
        tk
        is acquired, as defined in a general form below for any latent attribute
        a⁢(vi)∈A
        given the tweets
        T
        of user
        vi
        :
       </p>
       <table class="ltx_equationgroup" id="S4.E5">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E5X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td">
         </td>
         <td class="ltx_td ltx_align_left">
          p(a(vi)=x∈A∣T)=
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="3">
          <span class="ltx_tag ltx_tag_equationgroup">
           (5)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E5Xa">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td">
         </td>
         <td class="ltx_td ltx_align_left">
          p(T∣a(vi)=x)⋅p(a(vi)=x)∑y∈Ap(T∣a(vi)=y)⋅p(a(vi)=y)=
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E5Xb">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td">
         </td>
         <td class="ltx_td ltx_align_left">
          ∏kp(tk∣a(vi)=x)⋅p(a(vi)=x)∑y∈A∏kp(tk∣a(vi)=y)⋅p(a(vi)=y),
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
       <p class="ltx_p">
        where
        y
        is the number of all possible attribute values, and
        k
        is the number of tweets per user.
       </p>
      </div>
      <div class="ltx_para" id="S4.p3">
       <p class="ltx_p">
        For example, to predict user political preference, we start with a prior
        P⁢(R)=0.5
        , and sequentially update the posterior
        p(R∣T)
        by accumulating evidence from the likelihood
        p(tk|R)
        :
       </p>
       <table class="ltx_equationgroup" id="S4.E6">
        <tr class="ltx_equation ltx_align_baseline" id="S4.E6X">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td">
         </td>
         <td class="ltx_td ltx_align_left">
          p(R∣T)=
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
         <td class="ltx_align_middle ltx_align_right" rowspan="2">
          <span class="ltx_tag ltx_tag_equationgroup">
           (6)
          </span>
         </td>
        </tr>
        <tr class="ltx_equation ltx_align_baseline" id="S4.E6Xa">
         <td class="ltx_eqn_center_padleft">
         </td>
         <td class="ltx_td">
         </td>
         <td class="ltx_td ltx_align_left">
          ∏kp(tk|R)⋅p(R)∏kP(tk|R)⋅p(R)+∏kP(tk|D)⋅p(D).
         </td>
         <td class="ltx_eqn_center_padright">
         </td>
        </tr>
       </table>
      </div>
      <div class="ltx_para" id="S4.p4">
       <p class="ltx_p">
        Our goal is to maximize posterior probability estimates given a stream of communications for each user in the data over (a) time
        τ
        and (b) the number of tweets
        T
        . For that, for each user we take tweets that arrive continuously over time and apply two different streaming models:
       </p>
       <ul class="ltx_itemize" id="I4">
        <li class="ltx_item" id="I4.i1" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I4.i1.p1">
          <p class="ltx_p">
           User Model with Dynamic Updates:
           relies exclusively on user tweets
           t1(vi),…,tk(vi)
           following the order they arrive over time
           τ
           , where for each user
           vi
           we dynamically update the posterior
           p(R∣t1(vi),…,tk(vi))
           .
          </p>
         </div>
        </li>
        <li class="ltx_item" id="I4.i2" style="list-style-type:none;">
         <span class="ltx_tag ltx_tag_itemize">
          •
         </span>
         <div class="ltx_para" id="I4.i2.p1">
          <p class="ltx_p">
           User-Neighbor Model with Dynamic Updates:
           relies on both neighbor
           Nr
           communications including friend, follower, retweet, user mention and user tweets
           t1(vi),…,tk(Nr)
           following the order they arrive over time
           τ
           ; here we dynamically update the posterior probability
           p(R∣t1(vi),…,tk(Nr))
           .
          </p>
         </div>
        </li>
       </ul>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Experimental Setup
      </h2>
      <div class="ltx_para" id="S5.p1">
       <p class="ltx_p">
        We design a set of experiments to analyze static and dynamic models for political
affiliation classification defined in Sections
        3
        and
        4
        .
       </p>
      </div>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Batch Classification Experiments
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         We first answer whether communications from user-local neighborhoods can
help predict political preference for the user. To explore the contribution of different neighborhood types we learn static user and neighbor models on
         Gc⁢a⁢n⁢d
         ,
         Gg⁢e⁢o
         and
         GZ⁢L⁢R
         graphs. We also examine the ability of our static models to predict user political preferences in low-resource setting e.g., 5 tweets.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         The existing models follow a standard setup when either user or neighbor tweets are available during train and test. For a static neighbor model we go beyond that, and train our the model on all data available per user, but only apply part of the data at the test time, pushing the boundaries of how little is truly required for classification. For example, we only use follower tweets for
         Gt⁢e⁢s⁢t
         , but we use tweets from all types of neighbors for
         Gt⁢r⁢a⁢i⁢n
         . Such setup will simulate different real-world prediction scenarios which have not been previously explored, to our knowledge e.g., when a user has a private profile or has not tweeted yet, and only user neighbor tweets are available.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         We experiment with our static neighbor model defined in Eq.
         2
         with the aim to:
        </p>
        <ol class="ltx_enumerate" id="I5">
         <li class="ltx_item" id="I5.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           1.
          </span>
          <div class="ltx_para" id="I5.i1.p1">
           <p class="ltx_p">
            evaluate neighborhood size influence, we change the number of neighbors and try
            n=[1,2,5,10]
            neighbor(s) per user;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I5.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_enumerate">
           2.
          </span>
          <div class="ltx_para" id="I5.i2.p1">
           <p class="ltx_p">
            estimate neighbor content influence, we alternate the amount of content per neighbor and try
            t=[5,10,15,25,50,100,200]
            tweets.
           </p>
          </div>
         </li>
        </ol>
       </div>
       <div class="ltx_para" id="S5.SS1.p4">
        <p class="ltx_p">
         We perform 10-fold cross validation
         and run 100 random restarts for every
         n
         and
         t
         parameter combination. We compare our static neighbor and user models using the cost functions from Eq.
         3
         and Eq.
         4
         . For all experiments we use
         LibLinear
         [9]
         , integrated in the
         Jerboa
         toolkit
         [37]
         . Both models defined in Eq.
         1
         and Eq.
         2
         are learned using normalized count-based word ngram features extracted from either user or neighbor tweets.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Streaming Classification Experiments
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         We evaluate our models with dynamic Bayesian updates on a continuous stream of communications over time as shown in Figure
         2
         . Unlike static model experiments, we are not modeling the influence of the number of neighbors or the amount of content per neighbor. Here, we order user and neighbor communication streams by real world time of posting and measure changes in posterior probabilities over time. The main purpose of these experiments is to quantitatively evaluate (1) the number of tweets and (2) the amount of real world time it takes to observe enough evidence on Twitter to make reliable predictions.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         We experiment with log-linear models defined in Eq.
         1
         and
         2
         and continuously estimate the posterior probabilities
         P(R∣T)
         as defined in Eq.
         6
         . We average the posterior probability results over the users in
         Gc⁢a⁢n⁢d
         ,
         Gg⁢e⁢o
         and
         GZ⁢L⁢R
         graphs. We train streaming models on an attribute balanced subset of tweets for each user
         vi
         excluding
         vi
         ’s tweets (or
         vi
         ’s neighbor tweets for a joint model). This setup is similar to leave-one-out classification. The classifier is learned using binary word ngram features extracted from user or user-neighbor communications. We prefer binary to normalized count-based features to overcome sparsity issues caused by making predictions on each tweet individually.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S6">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        6
       </span>
       Static Classification Results
      </h2>
      <div class="ltx_subsection" id="S6.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.1
        </span>
        Modeling User Content Influence
       </h3>
       <div class="ltx_para" id="S6.SS1.p1">
        <p class="ltx_p">
         We investigate classification decision probabilities for our static user model
         Φvi
         by making predictions on a random set of 5 vs. 100 tweets per user. To our knowledge only limited work on personal analytics
         [5, 38]
         have performed this straight-forward comparison. For that purpose, we take a random partition containing 100 users of
         Gc⁢a⁢n⁢d
         graph and perform four independent classification experiments – two runs using 5 and two runs using 100 tweets per user.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS1.p2">
        <p class="ltx_p">
         Figure
         3
         demonstrates that more tweets during prediction time lead to higher accuracy by showing that more users with 100 tweets are correctly classified e.g., filled green markers in the right upper quadrant are true Republicans and in the left lower quadrant are true Democrats. Moreover, a lot of users with 100 tweets are close to 0.5 decision probability which suggests that the classifier is just uncertain rather then being completely off, e.g., misclassified Republican users with 5 tweets (not filled blue markers in the right lower quadrant) are close to 0. These results follow naturally from the underlying feature representation: having more tweets per user leads to a lower variance
estimate of a target multinomial distribution. The more robustly this distribution is estimated (based on having more tweets) the more confident we should be in the classifier output.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.2
        </span>
        Modeling Neighbor Content Influence
       </h3>
       <div class="ltx_para" id="S6.SS2.p1">
        <p class="ltx_p">
         Here we discuss the results for our static neighborhood model. We study the influence of the neighborhood type
         r
         and size in terms of the number of neighbors
         n
         and tweets
         t
         per neighbor.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p2">
        <p class="ltx_p">
         In Figure
         4
         we present accuracy results for
         Gc⁢a⁢n⁢d
         and
         Gg⁢e⁢o
         graphs. Following Eq.
         3
         and
         4
         , we spent an equal amount of resources to obtain 100 user tweets and 10 tweets from 10 neighbors. We annotate these ‘points of equal number of communications’ with a line on top marked with a corresponding number of user tweets.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p3">
        <p class="ltx_p">
         We show that three of six social circles – friend, retweet and user-mention yield better accuracy compared to the user model for all graphs when
         t≥250
         . Thus, for effectively classifying a given user
         vi
         it is better to take 200 tweets each from 10 neighbors rather than 2,000 tweets from the user.
        </p>
       </div>
       <div class="ltx_para" id="S6.SS2.p4">
        <p class="ltx_p">
         The best accuracy for
         Gc⁢a⁢n⁢d
         is 0.75 for friend, follower, retweet and user-mention neighborhoods which is 0.03 higher than the user baseline; for
         Gg⁢e⁢o
         is 0.67 for user-mention and 0.64 for retweet circles compared to 0.57 for the user model; for
         GZ⁢L⁢R
         is 0.863 for retweet and 0.849 for friend circles which is 0.11 higher that the user baseline. Finally, similarly to the results for the user model given in Figure
         3
         , increasing the number of tweets per neighbor from 5 to 200 leads to a significant gain in performance for all neighborhood types.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S6.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         6.3
        </span>
        Modeling Neighborhood Size
       </h3>
       <div class="ltx_para" id="S6.SS3.p1">
        <p class="ltx_p">
         In Figure
         5
         we present accuracy results to show neighborhood size influence on classification performance for
         Gg⁢e⁢o
         and
         Gc⁢a⁢n⁢d
         graphs. Our results demonstrate that even small changes to the neighborhood size
         n
         lead to better performance which does not support the claims by
         Zamal et al. (2012)
         . We demonstrate that increasing the size of the neighborhood leads to better performance across six neighborhood types. Friend, user mention and retweet neighborhoods yield the highest accuracy for all graphs. We observe that when the number of neighbors is
         n=1
         , the difference in accuracy across all neighborhood types is less significant but for
         n≥2
         it becomes more significant.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S7">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        7
       </span>
       Streaming Classification Results
      </h2>
      <div class="ltx_subsection" id="S7.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         7.1
        </span>
        Modeling Dynamic Posterior Updates from a User Stream
       </h3>
       <div class="ltx_para" id="S7.SS1.p1">
        <p class="ltx_p">
         Figures
         6
         and
         6
         demonstrate dynamic user model prediction results averaged over users from
         Gc⁢a⁢n⁢d
         and
         GZ⁢L⁢R
         graphs. Each figure outlines changes in sequential average probability estimates
         pμ(R∣T)
         for each individual self-authored tweet
         tk
         as defined in Eq.
         6
         . The average probability estimates
         pμ(R∣T)
         are reported for every 5 tweets in a stream
         T=(t1,…⁢tk)
         as
         ∑Pn(R∣tk)n
         , where
         n
         is the total number of users with the same attribute
         R
         or
         D
         . We represent
         pμ(R∣T)
         as a box and whisker plot with the median, lower and upper quantiles to show the variance; the length of whiskers indicate lower and upper extreme values.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p2">
        <p class="ltx_p">
         We find similar behavior across all three graphs. In particular, the posterior estimates converge faster when predicting Democratic than Republican users but it has been trained on an equal number of tweets per class. We observe that average posterior estimates
         Pμ(R∣T)
         converge faster to 0 (Democratic) than to 1 (Republican) in Figures
         6
         and
         6
         . It suggests that language of Democrats is more expressive of their political preference than language of Republicans. For example, frequent politically influenced terms used widely by Democratic users include
         faith4liberty, constitutionally, pass, vote2012, terroristic.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p3">
        <p class="ltx_p">
         The variance for average posterior estimates decreases when the number of tweets increases for all three datasets. Moreover, we detect that
         Pμ(R|T)
         estimates for users in
         Gc⁢a⁢n⁢d
         converge 2-3 times faster in terms of number of tweets than for users in
         GZ⁢L⁢R
         . The lowest convergence is detected for
         Gg⁢e⁢o
         where after
         tk=250
         tweets the average posterior estimate
         Pμ(R∣tk)=0.904±0.044
         and
         Pμ(D∣tk)=0.861±0.008
         . It means that users in
         Gc⁢a⁢n⁢d
         are more politically vocal compared to users in
         GZ⁢L⁢R
         and
         Gg⁢e⁢o
         . As a result, less active users in
         Gg⁢e⁢o
         just need more than 250 tweets to converge to a true 0 or 1 class. These results are coherent with the outcomes for our static models shown in Figures
         4
         and
         5
         . These findings further confirm that differences in performance are caused by various biases present in the data due to distinct sampling and annotation approaches.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS1.p4">
        <p class="ltx_p">
         Figure
         7
         a and
         7
         b illustrate the amount of time required for the user model to infer political preferences estimated for 1,031 users in
         Gc⁢a⁢n⁢d
         and 371 users in
         GZ⁢L⁢R
         . The amount of time needed can be evaluated for different accuracy levels e.g., 0.75 and 0.95. Thus, with 75% accuracy we classify:
        </p>
        <ul class="ltx_itemize" id="I6">
         <li class="ltx_item" id="I6.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i1.p1">
           <p class="ltx_p">
            100 (
            ∼
            20%) Republican users in 3.6 hours and Democratic users in 2.2 hours for
            Gc⁢a⁢n⁢d
            ;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I6.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i2.p1">
           <p class="ltx_p">
            100 (
            ∼
            56%)
            R
            users in 20 weeks and 100 (
            ∼
            52%)
            D
            users in 8.9 weeks for
            GZ⁢L⁢R
            which is 800 times longer that for
            Gc⁢a⁢n⁢d
            ;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I6.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I6.i3.p1">
           <p class="ltx_p">
            100 (
            ∼
            75%)
            R
            users in 12 weeks and 80 (
            ∼
            60%)
            D
            users in 19 weeks for
            Gg⁢e⁢o
            .
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S7.SS1.p5">
        <p class="ltx_p">
         Such extreme divergences in the amount of time required for classification across all graphs should be of strong interest to researchers concerned with latent attribute prediction tasks because Twitter users produce messages with extremely different frequencies. In our case, users in
         GZ⁢L⁢R
         tweet approximately 800 times less frequently than users in
         Gc⁢a⁢n⁢d
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S7.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         7.2
        </span>
        Modeling Dynamic Posterior Updates from a Joint User-Neighbor Stream
       </h3>
       <div class="ltx_para" id="S7.SS2.p1">
        <p class="ltx_p">
         We estimate dynamic posterior updates from a joint stream of user and neighbor communications in
         Gg⁢e⁢o
         ,
         Gc⁢a⁢n⁢d
         and
         GZ⁢L⁢R
         graphs. To make a fair comparison with a streaming user model, we start with the same user tweet
         t0⁢(vi)
         . Then instead of waiting for the next user tweet we rely on any neighbor tweets that appear until the user produces the next tweet
         t1⁢(vi)
         . We rely on communications from four types of neighbors such as friends, followers, retweets and user mentions.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS2.p2">
        <p class="ltx_p">
         The convergence rate for the average posterior probability estimates
         Pμ(R|T)
         depending on the number of tweets is similar to the user model results presented in Figure
         6
         . However, for
         Gg⁢e⁢o
         the variance for
         Pμ(R|T)
         is higher for Democratic users; for
         GZ⁢L⁢R
         Pμ(R|T)→1
         for Republicans in less than 110 tweets which is
         Δ⁢t=40
         tweets faster than the user model; for
         Gc⁢a⁢n⁢d
         the convergence for both
         Pμ(R|T)→1
         and
         Pμ(D|T)→0
         is not significantly different than the user model.
        </p>
       </div>
       <div class="ltx_para" id="S7.SS2.p3">
        <p class="ltx_p">
         Figures
         7
         c and
         7
         d show the amount of time required for a joint user-neighbor model to infer political preferences estimated for users in
         Gc⁢a⁢n⁢d
         and
         GZ⁢L⁢R
         . We find that with 75% accuracy we can classify 100 users for:
        </p>
        <ul class="ltx_itemize" id="I7">
         <li class="ltx_item" id="I7.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I7.i1.p1">
           <p class="ltx_p">
            Gc⁢a⁢n⁢d
            : Republican users in 23 minutes and Democratic users in 10 minutes;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I7.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I7.i2.p1">
           <p class="ltx_p">
            GZ⁢L⁢R
            :
            R
            users in 3.2 weeks and
            D
            users in 1.1 weeks which is 7 times faster on average across attributes than for the user model;
           </p>
          </div>
         </li>
         <li class="ltx_item" id="I7.i3" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I7.i3.p1">
           <p class="ltx_p">
            Gg⁢e⁢o
            :
            R
            users in 1.2 weeks and
            D
            users in 3.5 weeks which is on average 6 times faster across attributes than for the user model.
           </p>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S7.SS2.p4">
        <p class="ltx_p">
         Similar or better
         Pμ(R|T)
         convergence in terms of the number of tweets and, especially, in the amount of time needed for user and user-neighbor models further confirms that neighborhood content is useful for political preference prediction. Moreover, communications from a joint stream allow to make an inference up to 7 times faster.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S8">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        8
       </span>
       Related Work
      </h2>
      <div class="ltx_para" id="S8.p1">
       <p class="ltx_p">
        Supervised Batch Approaches
        The vast majority of work on predicting latent user attributes in social media apply supervised static SVM models for discrete categorical e.g., gender and regression models for continuous attributes e.g., age with lexical bag-of-word features for classifying user gender
        [11, 31, 5, 38]
        , age
        [31, 22, 21]
        or political orientation. We present an overview of the existing models for political preference prediction in Table
        1
        .
       </p>
      </div>
      <div class="ltx_para" id="S8.p2">
       <p class="ltx_p">
        Bergsma et al.
        [2]
        following up on Rao’s work
        [31]
        on adding socio-linguistic features to improve gender, ethnicity and political preference prediction show that incorporating stylistic and syntactic information to the bag-of-word features improves gender classification.
       </p>
      </div>
      <div class="ltx_para" id="S8.p3">
       <p class="ltx_p">
        Other methods characterize Twitter users by applying limited amounts of network structure information in addition to lexical features.
Connover et al.
        [7]
        rely on identifying strong partisan clusters of Democratic and Republican users in a Twitter network based on retweet and user mention degree of connectivity, and then combine this clustering information with the follower and friend neighborhood size features. Pennacchiotti et al.
        [27, 26]
        focus on user behavior, network structure and linguistic features. Similar to our work, they assume that users from a particular class tend to reply and retweet messages of the users from the same class. We extend this assumption and study other relationship types e.g., friends, user mentions etc. Recent work by Wong et al.
        [20]
        investigates tweeting and retweeting behavior for political learning during 2012 US Presidential election. The most similar work to ours is by
        Zamal et al. (2012)
        , where the authors apply features from the tweets authored by a user’s friend to infer attributes of that user. In this paper, we study different types of user social circles in addition to a friend network.
       </p>
      </div>
      <div class="ltx_para" id="S8.p4">
       <p class="ltx_p">
        Additionally, using social media for mining political opinions
        [23, 19]
        or understanding socio-political trends and voting outcomes
        [36, 12, 15]
        is becoming a common practice. For instance, Lampos et al.
        [15]
        propose a bilinear user-centric model for predicting voting intentions in the UK and Australia from social media data. Other works explore political blogs to predict what content will get the most comments
        [41]
        or analyze communications from Capitol Hill
        to predict campaign contributors based on this content
        [40]
        .
       </p>
      </div>
      <div class="ltx_para" id="S8.p5">
       <p class="ltx_p">
        Unsupervised Batch Approaches
        Bergsma et al.
        [1]
        show that large-scale clustering of user names improves gender, ethnicity and location classification on Twitter. O’Connor et al.
        [24]
        following the work by Eisenstein
        [8]
        propose a Bayesian generative model to discover demographic language variations in Twitter. Rao et al.
        [30]
        suggest a hierarchical Bayesian model which takes advantage of user name morphology for predicting user gender and ethnicity. Golbeck et al.
        [13]
        incorporate Twitter data in a spatial model of political ideology.
       </p>
      </div>
      <div class="ltx_para" id="S8.p6">
       <p class="ltx_p">
        Streaming Approaches
        Van Durme (2012b)
        proposed streaming models to predict user gender in Twitter. Other works suggested to process text streams for a variety of NLP tasks e.g., real-time opinion mining and sentiment analysis in social media
        [25]
        , named entity disambiguation
        [32]
        , statistical machine translation
        [16]
        , first story detection
        [28]
        , and unsupervised dependency parsing
        [14]
        . Massive Online Analysis (MOA) toolkit developed by
        Bifet et al. (2010)
        is an alternative to the Jerboa package used in this work developed by
        Van Durme (2012a)
        . MOA has been effectively used to detect sentiment changes in Twitter streams
        [4]
        .
       </p>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
