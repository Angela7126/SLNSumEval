<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>
   Nonparametric Learning of Phonological Constraints in Optimality Theory.
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
       We present a method to jointly learn features and weights directly from distributional data in a log-linear framework. Specifically, we propose a non-parametric Bayesian model for learning phonological markedness constraints directly from the distribution of input-output mappings in an Optimality Theory (OT) setting. The model uses an Indian Buffet Process prior to learn the feature values used in the log-linear method, and is the first algorithm for learning phonological constraints without presupposing constraint structure.
The model learns a system of constraints that explains observed data as well as the phonologically-grounded constraints of a standard analysis, with a violation structure corresponding to the standard constraints. These results suggest an alternative data-driven source for constraints instead of a fully innate constraint set.
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
        Many aspects of human cognition involve the interaction of constraints that push a decision-maker toward different options, whether in something so trivial as choosing a movie or so important as a fight-or-flight response. These constraint-driven decisions can be modeled with a log-linear system. In these models, a set of constraints is weighted and their violations are used to determine a probability distribution over outcomes. But where do these constraints come from?
       </p>
      </div>
      <div class="ltx_para" id="S1.p2">
       <p class="ltx_p">
        We consider this question by examining the dominant framework in modern phonology, Optimality Theory
        [, OT]
        , implemented in a log-linear framework, MaxEnt OT
        []
        , with output forms’ probabilities based on a weighted sum of constraint violations. OT analyses generally assume that the constraints are innate and universal, both to obviate the problem of learning constraints’ identities and to limit the set of possible languages.
       </p>
      </div>
      <div class="ltx_para" id="S1.p3">
       <p class="ltx_p">
        We propose a new approach: to learn constraints with limited innate phonological knowledge by identifying sets of constraint violations that explain the observed distributional data, instead of selecting constraints from an innate set of constraint definitions. Because the constraints are identified as sets of violations, this also permits constraints specific to a given language to be learned. This method, which we call IBPOT, uses an Indian Buffet Process (IBP) prior to define the space of possible constraint violation matrices, and uses Bayesian reasoning to identify constraint matrices likely to have generated the observed data.
In identifying constraints solely by their extensional violation profiles, this method does not directly identify the intensional definitions of the identified constraints, but to the extent that the resulting violation profiles are phonologically interpretable, we may conclude that the data themselves guide constraint identification.
We test IBPOT on tongue-root vowel harmony in Wolof, a West African language.
       </p>
      </div>
      <div class="ltx_para" id="S1.p4">
       <p class="ltx_p">
        The set of constraints learned by the model satisfy two major goals: they explain the data as well as the standard phonological analysis, and their violation structures correspond to the standard constraints. This suggests an alternative data-driven genesis for constraints, rather than the traditional assumption of fully innate constraints.
       </p>
      </div>
     </div>
     <div class="ltx_section" id="S2">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        2
       </span>
       Phonology and Optimality Theory
      </h2>
      <div class="ltx_subsection" id="S2.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.1
        </span>
        OT structure
       </h3>
       <div class="ltx_para" id="S2.SS1.p1">
        <p class="ltx_p">
         Optimality Theory has been used for constraint-based analysis of many areas of language, but we focus on its most successful application: phonology. We consider an OT analysis of the mappings between underlying forms and their phonological manifestations – i.e., mappings between forms in the mental lexicon and the actual vocalized forms of the words.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p2">
        <p class="ltx_p">
         Stated generally, an OT system takes some input, generates a set of candidate outputs, determines what constraints each output violates, and then selects a candidate output with a relatively unobjectionable violation profile. To do this, an OT system contains four major components: a generator
         Gen
         , which generates candidate output forms for the input; a set of constraints
         Con
         , which penalize candidates; a evaluation method
         Eval
         , which selects an winning candidate; and
         H
         , a language-particular weighting of constraints that
         Eval
         uses to determine the winning candidate.
Previous OT work has focused on identifying the appropriate formulation of
         Eval
         and the values and acquisition of
         H
         , while taking
         Gen
         and
         Con
         as given. Here, we expand the learning task by proposing an acquisition method for
         Con
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS1.p3">
        <p class="ltx_p">
         To learn
         Con
         , we propose a data-driven markedness constraint learning system that avoids both innateness and tractability issues. Unlike previous OT learning methods, which assume known constraint definitions and only learn the relative strength of these constraints, the IBPOT learns constraint violation profiles and weights for them simultaneously. The constraints are derived from sets of violations that effectively explain the observed data, rather than being selected from a pre-existing set of possible constraints.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.2
        </span>
        OT as a weighted-constraint method
       </h3>
       <div class="ltx_para" id="S2.SS2.p1">
        <p class="ltx_p">
         Although all OT systems share the same core structure, different choices of
         Eval
         lead to different behaviors. In IBPOT, we use the log-linear
         Eval
         developed by
         in their MaxEnt OT system. MEOT extends traditional OT to account for variation (cases in which multiple candidates can be the winner), as well as gradient/probabilistic productions
         []
         and other constraint interactions (e.g., cumulativity) that traditional OT cannot handle
         []
         . MEOT also is motivated by the general MaxEnt framework, whereas most other OT formulations are ad hoc constructions specific to phonology.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS2.p2">
        <p class="ltx_p">
         In MEOT, each constraint
         Ci
         is associated with a weight
         wi&lt;0
         . (Weights are always negative in OT; a constraint violation can never make a candidate more likely to win.) For a given input-candidate pair
         (x,y)
         ,
         fi⁢(y,x)
         is the number of violations of constraint
         Ci
         by the pair. As a maximum entropy model, the probability of
         y
         given
         x
         is proportional to the exponential of the weighted sum of violations,
         ∑iwi⁢fi⁢(y,x)
         . If
         𝒴⁢(x)
         is the set of all output candidates for the input
         x
         , then the probability of
         y
         as the winning output is:
        </p>
        p(y|x)=exp⁡(∑iwi⁢fi⁢(y,x))∑z∈𝒴⁢(x)exp⁡(∑iwi⁢fi⁢(z,x))

(1)
       </div>
       <div class="ltx_para" id="S2.SS2.p3">
        <p class="ltx_p">
         This formulation represents a probabilistic extension of the traditional formulation of OT
         []
         . Traditionally, constraints form a strict hierarchy, where a single violation of a high-ranked constraint is worse than any number of violations of lower-ranked constraints. Traditional OT is also deterministic, with the optimal candidate always selected. In MEOT, the constraint weights define hierarchies of varying strictness, and some probability is assigned to all candidates. If constraints’ weights are close together, multiple violations of lower-weighted constraints can reduce a candidate’s probability below that of a competitor with a single high-weight violation. As the distance between weights in MEOT increases, the probability of a suboptimal candidate being chosen approaches zero; thus the traditional formulation is a limit case of MEOT.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.3
        </span>
        OT in practice
       </h3>
       <div class="ltx_para" id="S2.SS3.p1">
        <p class="ltx_p">
         Figure
         1
         shows
         tableaux
         , a visualization for OT, applied in Wolof
         []
         . We are interested in four Wolof constraints that combine to induce vowel harmony:
         *I
         ,
         Parse
         [rtr],
         Harmony
         , and
         Parse
         [atr]. The meaning of these constraints will be discussed in Sect.
         4.1
         ; for now, we will only consider their violation profiles. Each column represents a constraint, with weights decreasing left-to-right. Each tableau looks at a single input form, noted in the top-left cell:
         ete,
         EtE,
         Ite, or
         itE.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p2">
        <p class="ltx_p">
         Each row is a candidate output form. A black cell indicates that the candidate, or input-candidate pair, violates the constraint in that column.
         A white cell indicates no violation. Grey stripes are overlaid on cells whose value will have a negligible impact on the distribution due to the values of higher-ranked constraint.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p3">
        <p class="ltx_p">
         Constraints fall into two categories, faithfulness and markedness, which differ in what information they use to assign violations. Faithfulness constraints penalize mismatches between the input and output, while markedness constraints consider only the output. Faithfulness violations include phoneme additions or deletions between the input and output; markedness violations include penalizing specific phonemes in the output form, regardless of whether the phoneme is present in the input.
        </p>
       </div>
       <div class="ltx_para" id="S2.SS3.p4">
        <p class="ltx_p">
         In MaxEnt OT, each constraint has a weight, and the candidates’ scores are the sums of the weights of violated constraints. In the
         ete tableau at top left, output
         ete has no violations, and therefore a score of zero. Outputs
         Ete and
         etE violate both
         Harmony
         (weight 16) and
         Parse
         [atr] (weight 8), so their scores are 24. Output
         EtE violates
         Parse
         [atr], and has score 8. Thus the log-probability of output
         EtE is 1/8 that of
         ete, and the log-probability of disharmonious
         Ete and
         etE are each 1/24 that of
         ete. As the ratio between scores increases, the log-probability ratios can become arbitrarily close to zero, approximating the deterministic situation of traditional OT.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S2.SS4">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         2.4
        </span>
        Learning Constraints
       </h3>
       <div class="ltx_para" id="S2.SS4.p1">
        <p class="ltx_p">
         Choosing a winning candidate presumes that a set of constraints
         Con
         is available, but where do these constraints come from? The standard assumption within OT is that
         Con
         is innate and universal. But in the absence of direct evidence of innate constraints, we should prefer a method that can derive the constraints from cognitively-general learning over one that assumes they are pre-specified. Learning appropriate model features has been an important idea in the development of constraint-based models
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p2">
        <p class="ltx_p">
         The innateness assumption can induce tractability issues as well. The strictest formulation of innateness posits that virtually all constraints are shared across all languages, even when there is no evidence for the constraint in a particular language
         []
         . Strict universality is undermined by the extremely large set of constraints it must weight, as well as the possible existence of language-particular constraints
         []
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p3">
        <p class="ltx_p">
         A looser version of universality supposes that constraints are built compositionally from a set of constraint templates or primitives or phonological features
         []
         . This version allows language-particular constraints, but it comes with a computational cost, as the learner must be able to generate and evaluate possible constraints while learning the language’s phonology. Even with relatively simple constraint templates, such as the phonological constraint learner of Hayes and Wilson
         []
         , the number of possible constraints expands exponentially. Depending on the specific formulation of the constraints, the constraint identification problem may even be NP-hard
         []
         . Our approach of casting the learning problem as one of identifying violation profiles is an attempt to determine the amount that can be learned about the active constraints in a paradigm without hypothesizing intensional constraint definitions.
The violation profile information used by our model could then be used to narrow the search space for intensional constraints, either by performing post-hoc analysis of the constraints identified by our model or by combining intensional constraint search into the learning process. We discuss each of these possibilities in Section
         5.2
         .
        </p>
       </div>
       <div class="ltx_para" id="S2.SS4.p4">
        <p class="ltx_p">
         Innateness is less of a concern for faithfulness than markedness constraints. Faithfulness violations are determined by the changes between an input form and a candidate, yielding an independent motivation for a universal set of faithfulness constraints
         []
         . Some markedness constraints can also be motivated in a universal manner
         []
         , but many markedness constraints lack such grounding.
         As such, it is unclear where a universal set of markedness constraints would come from.
        </p>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S3">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        3
       </span>
       The IBPOT Model
      </h2>
      <div class="ltx_subsection" id="S3.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.1
        </span>
        Structure
       </h3>
       <div class="ltx_para" id="S3.SS1.p1">
        <p class="ltx_p">
         The IBPOT model defines a generative process for mappings between input and output forms based on three latent variables: the constraint violation matrices
         F
         (faithfulness) and
         M
         (markedness), and the weight vector
         w
         . The cells of the violation matrices correspond to the number of violations of a constraint by a given input-output mapping.
         Fi⁢j⁢k
         is the number of violations of faithfulness constraint
         Fk
         by input-output pair type
         (xi,yj)
         ;
         Mj⁢l
         is the number of violations of markedness constraint
         M⋅l
         by output candidate
         yj
         . Note that
         M
         is shared across inputs, as
         Mj⁢l
         has the same value for all input-output pairs with output
         yj
         . The weight vector
         w
         provides weight for both
         F
         and
         M
         . Probabilities of output forms are given by a log-linear function:
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p2">
        <table class="ltx_equationgroup ltx_eqn_align" id="Sx1.EGx1">
         <tr class="ltx_equation ltx_align_baseline" id="S3.Ex1">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
           p(yj|xi)=
          </td>
          <td class="ltx_td ltx_align_left">
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
         </tr>
         <tr class="ltx_equation ltx_align_baseline" id="S3.E2">
          <td class="ltx_eqn_center_padleft">
          </td>
          <td class="ltx_td ltx_align_right">
          </td>
          <td class="ltx_td ltx_align_left">
           exp⁡(∑kwk⁢Fi⁢j⁢k+∑lwl⁢Mj⁢l)∑yz∈𝒴⁢(xi)exp⁡(∑kwk⁢Fi⁢z⁢k+∑lwl⁢Mz⁢l)
          </td>
          <td class="ltx_eqn_center_padright">
          </td>
          <td class="ltx_align_middle ltx_align_right" rowspan="1">
           <span class="ltx_tag ltx_tag_equation">
            (2)
           </span>
          </td>
         </tr>
        </table>
       </div>
       <div class="ltx_para" id="S3.SS1.p3">
        <p class="ltx_p">
         Note that this is the same structure as Eq.
         1
         but with faithfulness and markedness constraints listed separately. As discussed in Sect.
         2.4
         , we assume that
         F
         is known as part of the output of
         Gen
         []
         . The goal of the IBPOT model is to learn the markedness matrix
         M
         and weights
         w
         for both the markedness and faithfulness constraints.
        </p>
       </div>
       <div class="ltx_para" id="S3.SS1.p4">
        <p class="ltx_p">
         As for
         M
         , we need a non-parametric prior, as there is no inherent limit to the number of markedness constraints a language will use. We use the Indian Buffet Process
         []
         , which defines a proper probability distribution over binary feature matrices with an unbounded number of columns. The IBP can be thought of as representing the set of dishes that diners eat at an infinite buffet table. Each diner (i.e., output form) first draws dishes (i.e., constraint violations) with probability proportional to the number of previous diners who drew it:
         p(Mj⁢l=1|{Mz⁢l}z&lt;j)=nl/j
         . After choosing from the previously taken dishes, the diner can try additional dishes that no previous diner has had. The number of new dishes that the
         j
         -th customer draws follows a Poisson(
         α/j
         ) distribution. The complete specification of the model is then:
        </p>
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_center">
            M∼I⁢B⁢P⁢(α)
            ;
           </td>
           <td class="ltx_td ltx_align_center">
            𝒴⁢(xi)=Gen⁢(xi)
           </td>
          </tr>
          <tr class="ltx_tr">
           <td class="ltx_td ltx_align_center">
            w∼-Γ⁢(1,1)
            ;
           </td>
           <td class="ltx_td ltx_align_center">
            y|xi∼LogLin(M,F,w,𝒴(xi))
           </td>
          </tr>
         </tbody>
        </table>
       </div>
      </div>
      <div class="ltx_subsection" id="S3.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         3.2
        </span>
        Inference
       </h3>
       <div class="ltx_para" id="S3.SS2.p1">
        <p class="ltx_p">
         To perform inference in this model, we adopt a common Markov chain Monte Carlo estimation procedure for IBPs
         []
         . We alternate approximate Gibbs sampling over the constraint matrix
         M
         , using the IBP prior, with a Metropolis-Hastings method to sample constraint weights
         w
         .
        </p>
       </div>
       <div class="ltx_para" id="S3.SS2.p2">
        <p class="ltx_p">
         We initialize the model with a randomly-drawn markedness violation matrix
         M
         and weight vector
         w
         . To learn, we iterate through the output forms
         yj
         ; for each, we split
         M-j⁣⋅
         into “represented” constraints (those that are violated by at least one output form other than
         yj
         ) and “non-represented” constraints (those violated only by
         yj
         ). For each represented constraint
         M⋅l
         , we re-sample the value for the cell
         Mj⁢l
         . All non-represented constraints are removed, and we propose new constraints, violated only by
         yj
         , to replace them. After each iteration through
         M
         , we use Metropolis-Hastings to update the weight vector
         w
         .
        </p>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Represented constraint sampling
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P1.p1">
         <p class="ltx_p">
          We begin by resampling
          Mj⁢l
          for all represented constraints
          M⋅l
          , conditioned on the rest of the violations (
          M-(j⁢l),F
          ) and the weights
          w
          . This is the sampling counterpart of drawing existing features in the IBP generative process. By Bayes’ Rule, the posterior probability of a violation is proportional to product of the likelihood
          p(Y|Mj⁢l=1,M-j⁢l,F,w)
          from Eq.
          2
          and the IBP prior probability
          p(Mj⁢l=1|M-j⁢l)=n-j⁢l/n
          , where
          n-j⁢l
          is the number of outputs other than
          yj
          that violate constraint
          M⋅l
          .
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Non-represented constraint sampling
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P2.p1">
         <p class="ltx_p">
          After sampling the represented constraints for
          yj
          , we consider the addition of new constraints that are violated only by
          yj
          . This is the sampling counterpart to the Poisson draw for new features in the IBP generative process. Ideally, this would draw new constraints from the infinite feature matrix; however, this requires marginalizing the likelihood over possible weights, and we lack an appropriate conjugate prior for doing so. We approximate the infinite matrix with a truncated Bernoulli draw over unrepresented constraints
          []
          . We consider in each sample at most
          K*
          new constraints, with weights based on the auxiliary vector
          w*
          . This approximation retains the unbounded feature set of the IBP, as repeated sampling can add more and more constraints without limit.
         </p>
        </div>
        <div class="ltx_para" id="S3.SS2.SSS0.P2.p2">
         <p class="ltx_p">
          The auxiliary vector
          w*
          contains the weights of all the constraints that have been removed in the previous step. If the number of constraints removed is less than
          K*
          ,
          w*
          is filled out with draws from the prior distribution over weights. We then consider adding any subset of these new constraints to
          M
          , each of which would be violated only by
          yj
          . Let
          M*
          represent a (possibly empty) set of constraints paired with a subset of
          w*
          . The posterior probability of drawing
          M*
          from the truncated Bernoulli distribution is the product of the prior probability of
          M*
          (αK*NY+αK*)
          and the likelihood
          p(Y|M*,w*,M,w,F)
          , including the new constraints
          M*
          .
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S3.SS2.SSS0.P3">
        <h4 class="ltx_title ltx_title_paragraph">
         Weight sampling
        </h4>
        <div class="ltx_para" id="S3.SS2.SSS0.P3.p1">
         <p class="ltx_p">
          After sampling through all candidates, we use Metropolis-Hastings to estimate new weights for both constraint matrices. Our proposal distribution is
          G⁢a⁢m⁢m⁢a⁢(wk2/η,η/wk)
          , with mean
          wk
          and mode
          wk-ηwk
          (for
          wk&gt;1
          ). Unlike Gibbs sampling on the constraints, which occurs only on markedness constraints, weights are sampled for both markedness and faithfulness features.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S4">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        4
       </span>
       Experiment
      </h2>
      <div class="ltx_subsection" id="S4.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.1
        </span>
        Wolof vowel harmony
       </h3>
       <div class="ltx_para" id="S4.SS1.p1">
        <p class="ltx_p">
         We test the model by learning the markedness constraints driving Wolof vowel harmony
         []
         . Vowel harmony in general refers to a phonological phenomenon wherein the vowels of a word share certain features in the output form even if they do not share them in the input. In the case of Wolof, harmony encourages forms that have consistent tongue root positions.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p2">
        <p class="ltx_p">
         The Wolof vowel system has two relevant features, tongue root position and vowel height. The tongue root can either be advanced (ATR) or retracted (RTR), and the body of the tongue can be in the high, middle, or low part of the mouth. These features define six vowels:
        </p>
        <table class="ltx_tabular ltx_centering ltx_align_middle">
         <thead class="ltx_thead">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_border_l ltx_border_r ltx_border_t">
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            high
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            mid
           </th>
           <th class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            low
           </th>
          </tr>
         </thead>
         <tbody class="ltx_tbody">
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_l ltx_border_r ltx_border_t">
            ATR
           </th>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            i
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            e
           </td>
           <td class="ltx_td ltx_align_center ltx_border_r ltx_border_t">
            @
           </td>
          </tr>
          <tr class="ltx_tr">
           <th class="ltx_td ltx_align_center ltx_border_b ltx_border_l ltx_border_r ltx_border_t">
            RTR
           </th>
           <td class="ltx_td ltx_align_center ltx_border_b ltx_border_r ltx_border_t">
            I
           </td>
           <td class="ltx_td ltx_align_center ltx_border_b ltx_border_r ltx_border_t">
            E
           </td>
           <td class="ltx_td ltx_align_center ltx_border_b ltx_border_r ltx_border_t">
            a
           </td>
          </tr>
         </tbody>
        </table>
        <p class="ltx_p">
         We test IBPOT on the harmony system provided in the Praat program
         []
         , previously used as a test case by
         for MEOT learning with known constraints. This system has four constraints:
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p3">
        <ul class="ltx_itemize" id="I1">
         <li class="ltx_item" id="I1.i1" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i1.p1">
           <p class="ltx_p">
            Markedness:
           </p>
           <ul class="ltx_itemize" id="I1.I1">
            <li class="ltx_item" id="I1.I1.i1" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I1.I1.i1.p1">
              <p class="ltx_p">
               *I
               : do not have
               I (high RTR vowel)
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I1.I1.i2" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I1.I1.i2.p1">
              <p class="ltx_p">
               Harmony
               : do not have RTR and ATR vowels in the same word
              </p>
             </div>
            </li>
           </ul>
          </div>
         </li>
         <li class="ltx_item" id="I1.i2" style="list-style-type:none;">
          <span class="ltx_tag ltx_tag_itemize">
           •
          </span>
          <div class="ltx_para" id="I1.i2.p1">
           <p class="ltx_p">
            Faithfulness:
           </p>
           <ul class="ltx_itemize" id="I1.I2">
            <li class="ltx_item" id="I1.I2.i1" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I1.I2.i1.p1">
              <p class="ltx_p">
               Parse
               [rtr]: do not change RTR input to ATR output
              </p>
             </div>
            </li>
            <li class="ltx_item" id="I1.I2.i2" style="list-style-type:none;">
             <span class="ltx_tag ltx_tag_itemize">
              –
             </span>
             <div class="ltx_para" id="I1.I2.i2.p1">
              <p class="ltx_p">
               Parse
               [atr]: do not change ATR input to RTR output
              </p>
             </div>
            </li>
           </ul>
          </div>
         </li>
        </ul>
       </div>
       <div class="ltx_para" id="S4.SS1.p4">
        <p class="ltx_p">
         These constraints define the phonological standard that we will compare IBPOT to, with a ranking from strongest to weakest of
         *I
         &gt;⁣&gt;
         Parse
         [rtr]
         &gt;⁣&gt;
         Harmony
         &gt;⁣&gt;
         Parse
         [atr]. Under this ranking, Wolof harmony is achieved by changing a disharmonious ATR to an RTR, unless this creates an
         I vowel. We see this in Figure
         1
         , where three of the four winners are harmonic, but with input
         itE, harmony would require violating one of the two higher-ranked constraints.
As in previous MEOT work, all Wolof candidates are faithful with respect to vowel height, either because height changes are not considered by
         Gen
         , or because of a high-ranked faithfulness constraint blocking height changes.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p5">
        <p class="ltx_p">
         The Wolof constraints provide an interesting testing ground for the model, because it is a small set of constraints to be learned, but contains the
         Harmony
         constraint, which can be violated by non-adjacent segments. Non-adjacent constraints are difficult for string-based approaches because of the exponential number of possible relationships across non-adjacent segments. However, the Wolof results show that by learning violations directly, IBPOT does not encounter problems with non-adjacent constraints.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p6">
        <p class="ltx_p">
         The Wolof data has 36 input forms, each of the form
         V1⁢t⁢V2
         , where
         V1
         and
         V2
         are vowels that agree in height. Each input form has four candidate outputs, with one output always winning. The outputs appear for multiple inputs, as shown in Figure
         1
         . The candidate outputs are the four combinations of tongue-roots for the given vowel heights; the inputs and candidates are known to the learner. We generate simulated data by observing 1000 instances of the winning output for each input.
         The model must learn the markedness constraints
         *I
         and
         Harmony
         , as well as the weights for all four constraints.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS1.p7">
        <p class="ltx_p">
         We make a small modification to the constraints for the test data: all constraints are limited to binary values. For constraints that can be violated multiple times by an output (e.g.,
         *I
         twice by
         ItI), we use only a single violation. This is necessary in the current model definition because the IBP produces a prior over binary matrices. We generate the simulated data using only single violations of each constraint by each output form. Overcoming the binarity restriction is discussed in Sect.
         5.2
         .
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.2
        </span>
        Experiment Design
       </h3>
       <div class="ltx_para" id="S4.SS2.p1">
        <p class="ltx_p">
         We run the model for 10000 iterations, using deterministic annealing through the first 2500 iterations. The model is initialized with a random markedness matrix drawn from the IBP and weights from the exponential prior. We ran versions of the model with parameter settings between
         0.01
         and
         1
         for
         α
         ,
         0.05
         and
         0.5
         for
         η
         , and
         2
         and
         5
         for
         K*
         . All these produced quantitatively similar results; we report values for
         α=1
         ,
         η=0.5
         , and
         K*=5
         , which provides the least bias toward small constraint sets.
        </p>
       </div>
       <div class="ltx_para" id="S4.SS2.p2">
        <p class="ltx_p">
         To establish performance for the phonological standard, we use the IBPOT learner to find constraint weights but do not update
         M
         . The resultant learner is essentially MaxEnt OT with the weights estimated through Metropolis sampling instead of gradient ascent. This is done so that the IBPOT weights and phonological standard weights are learned by the same process and can be compared. We use the same parameters for this baseline as for the IBPOT tests. The results in this section are based on nine runs each of IBPOT and MEOT; ten MEOT runs were performed but one failed to converge and was removed from analysis.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S4.SS3">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         4.3
        </span>
        Results
       </h3>
       <div class="ltx_para" id="S4.SS3.p1">
        <p class="ltx_p">
         A successful set of learned constraints will satisfy two criteria: achieving good data likelihood (no worse than the phonological-standard constraints) and acquiring constraint violation profiles that are phonologically interpretable. We find that both of these criteria are met by IBPOT on Wolof.
        </p>
       </div>
       <div class="ltx_paragraph" id="S4.SS3.SSS0.P1">
        <h4 class="ltx_title ltx_title_paragraph">
         Likelihood comparison
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS0.P1.p1">
         <p class="ltx_p">
          First, we calculate the joint probability of the data and model given the priors,
          p(Y,M,w|F,α)
          , which is proportional to the product of three terms: the data likelihood
          p(Y|M,F,w)
          , the markedness matrix probability
          p(M|α)
          , and the weight probability
          p⁢(w)
          . We present both the mean and MAP values for these over the final 1000 iterations of each run. Results are shown in Table
          1
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P1.p2">
         <p class="ltx_p">
          All eight differences are significant according to
          t
          -tests over the nine runs. In all cases but mean
          M
          , the IBPOT method has a better log-probability. The most important differences are those in the data probabilities, as the matrix and weight probabilities are reflective primarily of the choice of prior. By both measures, the IBPOT constraints explain the observed data better than the phonologically standard constraints.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P1.p3">
         <p class="ltx_p">
          Interestingly, the mean
          M
          probability is lower for IBPOT than for the phonological standard. Though the phonologically standard constraints exist independently of the IBP prior, they fit the prior better than the average IBPOT constraints do. This shows that the IBP’s prior preferences can be overcome in order to have constraints that better explain the data.
         </p>
        </div>
       </div>
       <div class="ltx_paragraph" id="S4.SS3.SSS0.P2">
        <h4 class="ltx_title ltx_title_paragraph">
         Constraint comparison
        </h4>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p1">
         <p class="ltx_p">
          Our second criterion is the acquisition of meaningful constraints, that is, ones whose violation profiles have phonologically-grounded explanations. IBPOT learns the same number of markedness constraints as the phonological standard (two); over the final 1000 iterations of the model runs,
          99.2⁢%
          of the iterations had two markedness constraints, and the rest had three.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p2">
         <p class="ltx_p">
          Turning to the form of these constraints, Figure
          2
          shows violation profiles from the last iteration of a representative IBPOT run.
          Because vowel heights must be faithful between input and output, the Wolof data is divided into nine separate
          paradigms
          , each containing the four candidates (ATR/RTR
          ×
          ATR/RTR) for the vowel heights in the input.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p3">
         <p class="ltx_p">
          The violations on a given output form only affect probabilities within its paradigm. As a result, learned constraints are consistent within paradigms, but across paradigms, the same constraint may serve different purposes.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p4">
         <p class="ltx_p">
          For instance, the strongest learned markedness constraint, shown as
          M1
          in Figure
          2
          , has the same violations as the top-ranked constraint that actively distinguishes between candidates in each paradigm. For the five paradigms with at least one high vowel (the top row and left column),
          M1
          has the same violations as
          *I
          , as
          *I
          penalizes some but not all of the candidates. In the other four paradigms,
          *I
          penalizes none of the candidates, and the IBPOT learner has no reason to learn it. Instead, it learns that
          M1
          has the same violations as
          Harmony
          , which is the highest-weighted constraint that distinguishes between candidates in these paradigms. Thus in the high-vowel paradigms,
          M1
          serves as
          *I
          , while in the low/mid-vowel paradigms, it serves as
          Harmony
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p5">
         <p class="ltx_p">
          The lower-weighted
          M2
          is defined noisily, as the higher-ranked
          M1
          makes some values of
          M2
          inconsequential. Consider the top-left paradigm of Figure
          2
          , the high-high input, in which only one candidate does not violate
          M1
          (
          *I
          ). Because
          M1
          has a much higher weight than
          M2
          , a violation of
          M2
          has a negligible effect on a candidate’s probability.
          In such cells, the constraint’s value is influenced more by the prior than by the data. These inconsequential cells are overlaid with grey stripes in Figure
          2
          .
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p6">
         <p class="ltx_p">
          The meaning of
          M2
          , then, depends only on the consequential cells. In the high-vowel paradigms,
          M2
          matches
          Harmony
          , and the learned and standard constraints agree on all consequential violations, despite being essentially at chance on the indistinguishable violations (58%). On the non-high paradigms, the meaning of
          M2
          is unclear, as
          Harmony
          is handled by
          M1
          and
          *I
          is unviolated. In all four paradigms, the model learns that the RTR-RTR candidate violates
          M2
          and the ATR-ATR candidate does not; this appears to be the model’s attempt to reinforce a pattern in the lowest-ranked faithfulness constraint (
          Parse
          [atr]), which the ATR-ATR candidate never violates.
         </p>
        </div>
        <div class="ltx_para" id="S4.SS3.SSS0.P2.p7">
         <p class="ltx_p">
          Thus, while the IBPOT constraints are not identical to the phonologically standard ones, they reflect a version of the standard constraints that is consistent with the IBPOT framework.
          In paradigms where each markedness constraint distinguishes candidates, the learned constraints match the standard constraints. In paradigms where only one constraint distinguishes candidates, the top learned constraint matches it and the second learned constraint exhibits a pattern consistent with a low-ranked faithfulness constraint.
         </p>
        </div>
       </div>
      </div>
     </div>
     <div class="ltx_section" id="S5">
      <h2 class="ltx_title ltx_title_section">
       <span class="ltx_tag ltx_tag_section">
        5
       </span>
       Discussion and Future Work
      </h2>
      <div class="ltx_subsection" id="S5.SS1">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.1
        </span>
        Relation to phonotactic learning
       </h3>
       <div class="ltx_para" id="S5.SS1.p1">
        <p class="ltx_p">
         Our primary finding from IBPOT is that it is possible to identify constraints that are both effective at explaining the data and representative of theorized phonologically-grounded constraints, given only input-output mappings and faithfulness violations. Furthermore, these constraints are successfully acquired without any knowledge of the phonological structure of the data beyond the faithfulness violation profiles. The model’s ability to infer constraint violation profiles without theoretical constraint structure provides an alternative solution to the problems of the traditionally innate and universal OT constraint set.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p2">
        <p class="ltx_p">
         As it jointly learns constraints and weights, the IBPOT model calls to mind Hayes and Wilson’s
         []
         joint phonotactic learner. Their learner also jointly learns weights and constraints, but directly selects its constraints from a compositional grammar of constraint definitions. This limits their learner in practice by the rapid explosion in the number of constraints as the maximum constraint definition size grows. By directly learning violation profiles, the IBPOT model avoids this explosion, and the violation profiles can be automatically parsed to identify the constraint definitions that are consistent with the learned profile. The inference method of the two models is different as well; the phonotactic learner selects constraints greedily, whereas the sampling on
         M
         in IBPOT asymptotically approaches the posterior.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS1.p3">
        <p class="ltx_p">
         The two learners also address related but different phonological problems. The phonotactic learner considers phonotactic problems, in which only output matters. The constraints learned by Hayes and Wilson’s learner are essentially OT markedness constraints, but their learner does not have to account for varied inputs or effects of faithfulness constraints.
        </p>
       </div>
      </div>
      <div class="ltx_subsection" id="S5.SS2">
       <h3 class="ltx_title ltx_title_subsection">
        <span class="ltx_tag ltx_tag_subsection">
         5.2
        </span>
        Extending the learning model
       </h3>
       <div class="ltx_para" id="S5.SS2.p1">
        <p class="ltx_p">
         IBPOT, as proposed here, learns constraints based on binary violation profiles, defined extensionally. A complete model of constraint acquisition should provide intensional definitions that are phonologically grounded and cover potentially non-binary constraints. We discuss how to extend the model toward these goals.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p2">
        <p class="ltx_p">
         IBPOT currently learns extensional constraints, defined by which candidates do or do not violate the constraint. Intensional definitions are needed to extend constraints to unseen forms. Post hoc violation profile analysis, as in Sect.
         4.3
         , provides a first step toward this goal. Such analysis can be integrated into the learning process using the Rational Rules model
         []
         to identify likely constraint definitions compositionally. Alternately, phonological knowledge could be integrated into a joint constraint learning process in the form of a naturalness bias on the constraint weights or a phonologically-motivated replacement for the IBP prior.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p3">
        <p class="ltx_p">
         The results presented here use binary constraints, where each candidate violates each constraint only once, a result of the IBP’s restriction to binary matrices. Non-binarity can be handled by using the binary matrix
         M
         to indicate whether a candidate violates a constraint, with a second distribution determining the number of violations.
Alternately, a binary matrix can directly capture non-binary constraints;
         converted existing non-binary constraints into a binary OT system by representing non-binary constraints as a set of equally-weighted overlapping constraints, each accounting for one violation. The non-binary harmony constraint, for instance, becomes a set {*(at least one disharmony), *(at least two disharmonies), etc.}.
        </p>
       </div>
       <div class="ltx_para" id="S5.SS2.p4">
        <p class="ltx_p">
         Lastly, the Wolof vowel harmony problem provides a test case with overlaps in the candidate sets for different inputs. This candidate overlap helps the model find appropriate constraint structures. Analyzing other phenomena may require the identification of appropriate abstractions to find this same structural overlap. English regular plurals, for instance, fall into broad categories depending on the features of the stem-final phoneme. IBPOT learning in such settings may require learning an appropriate abstraction as well.
        </p>
       </div>
      </div>
     </div>
    </div>
   </div>
  </div>
 </body>
</html>
