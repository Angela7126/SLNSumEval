<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Modeling the complex dynamics and changing correlations of epileptic events.
   </title>
   <abstract>
    Patients with epilepsy can manifest short, sub-clinical epileptic “bursts” in addition to full-blown clinical seizures. We believe the relationship between these two classes of events—something not previously studied quantitatively—could yield important insights into the nature and intrinsic dynamics of seizures. A goal of our work is to parse these complex epileptic events into distinct dynamic regimes. A challenge posed by the intracranial EEG (iEEG) data we study is the fact that the number and placement of electrodes can vary between patients. We develop a Bayesian nonparametric Markov switching process that allows for (i) shared dynamic regimes between a variable number of channels, (ii) asynchronous regime-switching, and (iii) an unknown dictionary of dynamic regimes. We encode a sparse and changing set of dependencies between the channels using a Markov-switching Gaussian graphical model for the innovations process driving the channel dynamics and demonstrate the importance of this model in parsing and out-of-sample predictions of iEEG data. We show that our model produces intuitive state assignments that can help automate clinical analysis of seizures and enable the comparison of sub-clinical bursts and full clinical seizures.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Despite over three decades of research, we still have very little idea of what defines a seizure. This ignorance stems both from the complexity of epilepsy as a disease and a paucity of quantitative tools that are flexible enough to describe epileptic events but restrictive enough to distill intelligible information from them. Much of the recent machine learning work in electroencephalogram (EEG) analysis has focused on seizure prediction, [cf., [1], [2]], an important area of study but one that generally has not focused on parsing the EEG directly, as a human EEG reader would. Such parsings are central for diagnosis and relating various types of abnormal activity. Recent evidence shows that the range of epileptic events extends beyond clinical seizures to include shorter, sub-clinical “bursts” lasting fewer than 10 seconds [3]. What is the relationship between these shorter bursts and the longer seizures? In this work, we demonstrate that machine learning techniques can have substantial impact in this domain by unpacking how seizures begin, progress, and end.
     </paragraph>
     <paragraph>
      In particular, we build a Bayesian nonparametric time series model to analyze intracranial EEG (iEEG) data. We take a modeling approach similar to a physician's in analyzing EEG events: look directly at the evolution of the raw EEG voltage traces. EEG signals exhibit nonstationary behavior during a variety of neurological events, and time-varying autoregressive (AR) processes have been proposed to model single channel data [4]. Here we aim to parse the recordings into interpretable regions of activity and thus propose to use autoregressive hidden Markov models (AR-HMMs) to define locally stationary processes. In the presence of multiple channels of simultaneous recordings, as is almost always the case in EEG, we wish to share AR states between the channels while allowing for asynchronous switches. The recent beta process (BP) AR-HMM of Fox et al. [5] provides a flexible model of such dynamics: a shared library of infinitely many possible AR states is defined and each time series uses a finite subset of the states. The process encourages sharing of AR states, while allowing for time-series-specific variability.
     </paragraph>
     <paragraph>
      Conditioned on the selected AR dynamics, the BP-AR-HMM assumes independence between time series. In the case of iEEG, this assumption is almost assuredly false. Fig. 1 shows an example of a {a mathematical formula}4×8 intracranial electrode grid and the residual EEG traces of 16 channels after subtracting the predicted value in each channel using a conventional BP-AR-HMM. While the error term in some channels remains low throughout the recording, other channels—especially those spatially adjacent in the electrode grid—have very correlated error traces. We propose to capture correlations between channels by modeling a multivariate innovations process that drives independently evolving channel dynamics. We demonstrate the importance of accounting for this error trace in predicting heldout seizure recordings, making this a crucial modeling step before undertaking large-scale EEG analysis.
     </paragraph>
     <paragraph>
      To aid in scaling to large electrode grids, we exploit a sparse dependency structure for the multivariate innovations process. In particular, we assume a graph with known vertex structure that encodes conditional independencies in the multivariate innovations process. The graph structure is based on the spatial adjacencies of the iEEG channels, with a few exceptions to make the graphical model fully decomposable. Fig. 1 (bottom left) shows an example of such a graphical model over the channels. Although the relative position of channels in the electrode grid is clear, determining the precise 3D location of each channel is extremely difficult. Furthermore, unlike in scalp EEG or magentoencephalogram (MEG), which have generally consistent channel positions from patient to patient, iEEG channels vary in number and position for each patient. These issues impede the use of alternative spatial and multivariate time series modeling techniques.
     </paragraph>
     <paragraph>
      It is well-known that the correlations between EEG channels usually vary during the beginning, middle, and end of a seizure [6], [7]. Prado et al. [8] employ a mixture-of-expert vector autoregressive (VAR) model to describe the different dynamics present in seven channels of scalp EEG. We take a similar approach by allowing for a Markov evolution to an underlying innovations covariance state.
     </paragraph>
     <paragraph>
      An alternative modeling approach is to treat the channel recordings as a single multivariate time series, perhaps using a switching VAR process as in Prado et al. [8]. However, such an approach (i) assumes synchronous switches in dynamics between channels, (ii) scales poorly with the number of channels, and (iii) requires an identical number of channels between patients to share dynamics between event recordings.
     </paragraph>
     <paragraph>
      Other work has explored nonparametric modeling of multiple time series. The infinite factorial HMM of Van Gael et al. [9] considers an infinite collection of chains each with a binary state space. The infinite hierarchical HMM [10] also involves infinitely many chains with finite state spaces, but with constrained transitions between the chains in a top down fashion. The infinite DBN of Doshi-Velez et al. [11] considers more general connection structures and arbitrary state spaces. Alternatively, the graph-coupled HMM of Dong et al. [12] allows graph-structured dependencies in the underlying states of some N Markov chains. Here, we consider a finite set of chains with infinite state spaces that evolve independently. The factorial structure combines the chain-specific AR dynamic states and the graph-structured innovations to generate the multivariate observations with sparse dependencies.
     </paragraph>
     <paragraph>
      Expanding upon previous work [13], we show that our model for correlated time series has better out-of-sample predictions of iEEG data than standard AR- and BP-AR-HMMs and demonstrate the utility of our model in comparing short, sub-clinical epileptic bursts with longer, clinical seizures. Our inferred parsings of iEEG data concur with key features hand-annotated by clinicians but provide additional insight beyond what can be extracted from a visual read of the data. The importance of our methodology is multifold: (i) the output is interpretable to a practitioner and (ii) the parsings can be used to relate seizure types both within and between patients even with different electrode setups. Enabling such broad-scale automatic analysis, and identifying dynamics unique to sub-clinical seizures, can lead to new insights in epilepsy treatments.
     </paragraph>
     <paragraph>
      Although we are motivated by the study of seizures from iEEG data, our work is much more broadly applicable in time series analysis. For example, perhaps one has a collection of stocks and wants to model shared dynamics between them while capturing changing correlations. The BP-AR-HMM was applied to the analysis of a collection of motion capture data assuming independence between individuals; our modeling extension could account for coordinated motion with a sparse dependency structure between individuals. Regardless, we find the impact in the neuroscience domain to be quite significant.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      A structured Bayesian nonparametric factorial AR-HMM
     </section-title>
     <section label="2.1">
      <section-title>
       Dynamic model
      </section-title>
      <paragraph>
       Consider an event with N univariate time series of length T. This event could be a seizure, where each time series is one of the iEEG voltage-recording channels. For clarity of exposition, we refer to the individual univariate time series as channels and the resulting N-dimensional multivariate time series (stacking up the channel series) as the event. We denote the scalar value for each channel i at each (discrete) time point t as {a mathematical formula}yt(i) and model it using an r-order AR-HMM [5]. That is, each channel is modeled via Markov switches between a set of AR dynamics. Denoting the latent state at time t by {a mathematical formula}zt(i), we have:{a mathematical formula} Here, {a mathematical formula}ak=(ak,1,…,ak,r)T are the AR parameters for state k and {a mathematical formula}πk is the transition distribution from state k to any other state. We also introduce the notation {a mathematical formula}y˜t(i) as the vector of r previous observations {a mathematical formula}(yt−1(i),…,yt−r(i))T.
      </paragraph>
      <paragraph>
       In contrast to a vector AR (VAR) HMM specification of the event, our modeling of channel dynamics separately as in Eq. (1) allows for (i) asynchronous switches and (ii) sharing of dynamic parameters between recordings with a potentially different number of channels. However, a key aspect of our data is the fact that the channels are correlated. Likewise, these correlations change as the patient progresses through various seizure event states (e.g., “resting”, “onset”, “offset”, …). That is, the channels may display one innovation covariance before a seizure (e.g., relatively independent and low-magnitude) but quite a different covariance during a seizure (e.g., correlated, higher magnitude). To capture this, we jointly model the innovations {a mathematical formula}ϵt=(ϵt(1),…,ϵt(N))T driving the AR-HMMs of Eq. (1) as{a mathematical formula} where {a mathematical formula}Zt denotes a Markov-evolving event state distinct from the individual channel states {a mathematical formula}{zt(i)}, {a mathematical formula}ϕl the transition distributions, and {a mathematical formula}Δk the event-state-specific channel covariance. That is each {a mathematical formula}Δl describes a different set of channel relationships.
      </paragraph>
      <paragraph>
       For compactness, we sometimes alternately write{a mathematical formula} where {a mathematical formula}yt is the concatenation of N channel observations at time t and {a mathematical formula}zt is the vector of concatenated channel states. The overall dynamic model is represented graphically in Fig. 2.
      </paragraph>
      <section>
       <section-title>
        Scaling to large electrode grids
       </section-title>
       <paragraph>
        To scale our model to a large number of channels, we consider a Gaussian graphical model (GGM) for {a mathematical formula}ϵt capturing a sparse dependency structure amongst the channels. Let {a mathematical formula}G=(V,E) be an undirected graph with V the set of channel nodes i and E the set of edges with {a mathematical formula}(i,j)∈E if i and j are connected by an edge in the graph. Then, {a mathematical formula}[Δl−1]ij=0 for all {a mathematical formula}(i,j)∉E, implying {a mathematical formula}ϵt(i) is conditionally independent of {a mathematical formula}ϵt(j) given {a mathematical formula}ϵt(k) for all channels {a mathematical formula}k≠i,j. In our dynamic model of Eq. (1), statements of conditional independence of {a mathematical formula}ϵt translate directly to statements of the observations {a mathematical formula}yt.
       </paragraph>
       <paragraph>
        In our application, we choose G based on the spatial adjacencies of channels in the electrode grid, as depicted in Fig. 1 (bottom left). In addition to encoding the spatial proximities of iEEG electrodes, the graphical model also yields a sparse precision matrix {a mathematical formula}Δl−1, allowing for more efficient scaling to the large number of channels commonly present in iEEG. These computational efficiencies are made clear in Section 3.
       </paragraph>
      </section>
      <section>
       <section-title>
        Interpretation as a sparse factorial HMM
       </section-title>
       <paragraph>
        Recall that our formulation involves {a mathematical formula}N+1 independently evolving Markov chains: N chains for the channel states {a mathematical formula}zt(i) plus one for the event state sequence {a mathematical formula}Zt. As indicated by the observation model of Eq. (3), the {a mathematical formula}N+1 Markov chains jointly generate our observation vector {a mathematical formula}yt leading to an interpretation of our formulation as a factorial HMM [14]. However, here we have a sparse dependency structure in how the Markov chains influence a given observation {a mathematical formula}yt, as induced by the conditional independencies in {a mathematical formula}ϵt encoded in the graph G. That is, {a mathematical formula}yt(i) only depends on {a mathematical formula}Zt the set of {a mathematical formula}zt(j) for which j is a neighbor of i in G.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Prior specification
      </section-title>
      <paragraph>
       Emission parameters
      </paragraph>
      <paragraph>
       As in the AR-HMM, we place a multivariate normal prior on the AR coefficients,{a mathematical formula} with mean {a mathematical formula}m0 and covariance {a mathematical formula}Σ0. Throughout this work, we let {a mathematical formula}m0=0.
      </paragraph>
      <paragraph>
       For the channel covariances {a mathematical formula}Δl with sparse precisions {a mathematical formula}Δl−1 determined by the graph G, we specify a hyper-inverse Wishart (HIW) prior,{a mathematical formula} where {a mathematical formula}b0 denotes the degrees of freedom and {a mathematical formula}D0 the scale. The HIW prior [15] enforces hyper-Markov conditions specified by G.
      </paragraph>
      <paragraph>
       Feature constrained channel transition distributions
      </paragraph>
      <paragraph>
       A natural question is how many AR states are the channels switching between? Likewise, which are shared between the channels and which are unique? We expect to see similar dynamics present in the channels (sharing of AR processes), but also some differences. For example, maybe only some of the channels ever get excited into a certain state. To capture this structure, we take a Bayesian nonparametric approach building on the beta process (BP) AR-HMM of Fox et al. [16]. Through the beta process prior [17], the BP-AR-HMM defines a shared library of infinitely many AR coefficients {a mathematical formula}{ak}, but encourages each channel to only use a sparse subset of them.
      </paragraph>
      <paragraph>
       The BP-AR-HMM specifically defines a featural model. Let {a mathematical formula}f(i) be a binary feature vector associated with channel i with {a mathematical formula}fk(i)=1 indicating that channel i uses the dynamic described by {a mathematical formula}ak. Formally, the feature assignments {a mathematical formula}fk(i) and their corresponding parameters {a mathematical formula}ak are generated by a beta process random measure and the conjugate Bernoulli process (BeP),{a mathematical formula} with base measure {a mathematical formula}B0 over the parameter space {a mathematical formula}Θ=Rr for our r-order autoregressive parameters {a mathematical formula}ak. As specified in Eq. (4), we take the normalized measure {a mathematical formula}B0/B0(Θ) to be {a mathematical formula}N(m0,Σ0). The discrete measures B and {a mathematical formula}X(i) can be represented as{a mathematical formula} with {a mathematical formula}fk(i)∼Ber(ωk).
      </paragraph>
      <paragraph>
       The resulting feature vectors {a mathematical formula}f(i) constrain the set of available states {a mathematical formula}zt(i) can take by constraining each transition distributions, {a mathematical formula}πj(i), to be 0 when {a mathematical formula}fk(i)=0. Specifically, the BP-AR-HMM defines {a mathematical formula}πj(i) by introducing a set of gamma random variables, {a mathematical formula}ηjk(i), and setting{a mathematical formula}{a mathematical formula} The positive elements of {a mathematical formula}πj(i) can also be thought of as a sample from a finite Dirichlet distribution with only {a mathematical formula}K(i) dimensions, where {a mathematical formula}K(i)=∑kfk(i) represents the number of states channel i uses. For convenience, we sometimes denote the set of transition variables {a mathematical formula}{ηjk(i)}j as {a mathematical formula}η(i). As in the sticky HDP-HMM of Fox et al. [18], the parameter {a mathematical formula}κc encourages self-transitions (i.e., state j at time {a mathematical formula}t−1 to state j at time t).
      </paragraph>
      <paragraph>
       Unconstrained event transition distributions
      </paragraph>
      <paragraph>
       We again take a Bayesian nonparametric approach to define the event state HMM, building on the sticky HDP-HMM [18]. In particular, the transition distributions {a mathematical formula}ϕl are hierarchically defined as{a mathematical formula} where {a mathematical formula}stick(α) refers to a stick-breaking measure, also known as {a mathematical formula}GEM(α), with β generated by{a mathematical formula} Again, the sticky parameter {a mathematical formula}κe promotes self-transitions, reducing state redundancy.
      </paragraph>
      <paragraph>
       We term this model the sparse factorial BP-AR-HMM. Although the graph G can be arbitrarily structured, because of our motivating seizure modeling application with a focus on a spatial-based graph structure, we often describe the sparse factorial BP-AR-HMM as capturing spatial correlations. We depict this model in the directed acyclic graphs shown in Fig. 3. Note that while we formally consider a model of only a single event for notational simplicity, our formulation scales straightforwardly to multiple independent events. In this case, everything except the library of AR states {a mathematical formula}{ak} becomes event-specific. If all events share the same channel setup, we can assume the channel covariances {a mathematical formula}{Δl} are shared as well.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Posterior computations
     </section-title>
     <paragraph>
      Although the components of our model related to the individual channel dynamics are similar to those in the BP-AR-HMM, our posterior computations are significantly different due to the coupling of the Markov chains via the correlated innovations {a mathematical formula}ϵt. In the BP-AR-HMM, conditioned on the feature assignments, each time series is independent. Here, however, we are faced with a factorial HMM structure and the associated challenges. Yet the underlying graph structure of the channel dependencies mitigates the scale of these challenges.
     </paragraph>
     <paragraph>
      Conditioned on channel sequences {a mathematical formula}{z1:T(i′)}, we can marginalize {a mathematical formula}z1:T(i); because of the graph structure, we need only condition on a sparse set of other channels {a mathematical formula}i′ (i.e., neighbors of channel i in the graph). This step is important for efficiently sampling the feature assignments {a mathematical formula}f(i).
     </paragraph>
     <paragraph>
      At a high level, each MCMC iteration proceeds through sampling channel states, events states, dynamic model parameters, and hyperparameters. Algorithm 1 summarizes these steps, which we briefly describe below and more fully in Appendix B Individual channel variables posterior, Appendix C Event state variables posterior, Appendix D Hyperparameters posterior.
     </paragraph>
     <section>
      <section-title>
       Individual channel variables
      </section-title>
      <paragraph>
       We harness the fact that we can compute the marginal likelihood of {a mathematical formula}y1:T given {a mathematical formula}f(i) and the neighborhood set of other channels {a mathematical formula}z1:T(i′) in order to block sample {a mathematical formula}{f(i),z1:T(i)}. That is, we first sample {a mathematical formula}f(i) marginalizing {a mathematical formula}z1:T(i) and then sample {a mathematical formula}z1:T(i) given the sampled {a mathematical formula}f(i). Sampling the active features {a mathematical formula}f(i) for channel i follows as in Fox et al. [5], using the Indian buffet process (IBP) [19] predictive representation associated with the beta process, but using a likelihood term that conditions on neighboring channel state sequences {a mathematical formula}z1:T(i′) and observations {a mathematical formula}y1:T(i′). We additionally condition on the event state sequence {a mathematical formula}Z1:T to define the sequence of distributions on the innovations. Generically, this yields{a mathematical formula} Here, {a mathematical formula}F−ik denotes the set of feature assignments not including {a mathematical formula}fk(i). The first term is given by the IBP prior and the second term is the marginal conditional likelihood (marginalizing {a mathematical formula}z1:T(i)). Based on the derived marginal conditional likelihood, feature sampling follows similarly to that of Fox et al. [5].
      </paragraph>
      <paragraph>
       Conditioned on {a mathematical formula}f(i), we block sample the state sequence {a mathematical formula}z1:T(i) using a backward filtering forward sampling algorithm (see Appendix A) based on a decomposition of the full conditional as{a mathematical formula}
      </paragraph>
      <paragraph>
       For sampling the transition parameters {a mathematical formula}η(i), we follow Hughes et al. [20, Supplement] and sample from the full conditional{a mathematical formula} where {a mathematical formula}njk(i) denotes the number of times channel i transitions from state j to state k. We sample {a mathematical formula}ηj(i)=Cj(i)η¯j(i) from its posterior via two auxiliary variables,{a mathematical formula} where {a mathematical formula}nj(i) gives the transition counts from state j in channel i.
      </paragraph>
     </section>
     <section>
      Event variables {a mathematical formula}{ϕl,Δl,Z1:T}
      <paragraph>
       Conditioned on the channel state sequences {a mathematical formula}z1:T and AR coefficients {a mathematical formula}{ak}, we can compute an innovations sequence as {a mathematical formula}ϵt=yt−AztY˜t, where we recall the definition of {a mathematical formula}Ak and {a mathematical formula}Y˜t from Eq. (3). These innovations are the observations of the sticky HDP-HMM of Eq. (2). For simplicity and to allow block-sampling of {a mathematical formula}z1:T, we consider a weak limit approximation of the sticky HDP-HMM as in [18]. The top-level Dirichlet process is approximated by an L-dimensional Dirichlet distribution [21], inducing a finite Dirichlet for {a mathematical formula}ϕl:{a mathematical formula} Here, L provides an upper bound on the number of states in the HDP-HMM. The weak limit approximation still encourages using a subset of these L states.
      </paragraph>
      <paragraph>
       Based on the weak limit approximation, we first sample the parent transition distribution β as in [22], [18], followed by sampling each {a mathematical formula}ϕl from its Dirichlet posterior,{a mathematical formula} where {a mathematical formula}nl is a vector of transition counts of {a mathematical formula}Z1:T from state l to the L different states.
      </paragraph>
      <paragraph>
       Using standard conjugacy results, based on “observations” {a mathematical formula}ϵt=yt−AztY˜t for t such that {a mathematical formula}Zt=l, the full conditional for {a mathematical formula}Δl is given by{a mathematical formula} where{a mathematical formula}{a mathematical formula} Details on how to efficiently sample from a HIW distribution are provided in [23].
      </paragraph>
      <paragraph>
       Conditioned on the truncated HDP-HMM event transition distributions {a mathematical formula}{ϕl} and emission parameters {a mathematical formula}{Δl}, we use a standard backward filtering forward sampling scheme to block sample {a mathematical formula}Z1:T.
      </paragraph>
     </section>
     <section>
      AR coefficients, {a mathematical formula}{ak}
      <paragraph>
       Each observation {a mathematical formula}yt is generated based on a matrix of AR parameters {a mathematical formula}Azt=[azt(1)|⋯|azt(N)]. Thus, sampling {a mathematical formula}ak involves conditioning on {a mathematical formula}{ak′}k′≠k and disentangling the contribution of {a mathematical formula}ak on each {a mathematical formula}yt. As derived in Appendix E, the full conditional for {a mathematical formula}ak is a multivariate normal{a mathematical formula} where{a mathematical formula}{a mathematical formula} The vectors {a mathematical formula}k+ and {a mathematical formula}k− denote the indices of channels assigned and not assigned to state k at time t, respectively. We use these to index into the rows and columns of the vectors {a mathematical formula}ϵt, {a mathematical formula}yt, and matrix {a mathematical formula}ΔZt. Each column of matrix {a mathematical formula}Y¯t(k+) is the previous r observations for one of the channels assigned to state k at time t.
      </paragraph>
     </section>
     <section>
      <section-title>
       Hyperparameters
      </section-title>
      <paragraph>
       See Appendix D for the prior and full conditionals of the hyperparameters {a mathematical formula}γc, {a mathematical formula}κc, {a mathematical formula}αe, {a mathematical formula}κe, {a mathematical formula}γe, and {a mathematical formula}αc=B0(Θ).
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Experiments
     </section-title>
     <section label="4.1">
      <section-title>
       Simulation experiments
      </section-title>
      <paragraph>
       To initially explore some characteristics of our sparse factorial BP-AR-HMM, we examined a small simulated dataset of six time series in a {a mathematical formula}2×3 spatial arrangement, with vertices connecting all adjacent nodes (i.e., two cliques of 4 nodes each). We generated an event of length 2000 time points as follows. We defined five first-order AR channel states linearly spaced between −0.9 and 0.9 and three event states with covariances shown in the bottom left of Fig. 4. Channel and event state transition distributions were set to 0.99 and 0.9, respectively, for a self-transition and uniform between the other states. Channel feature indicators {a mathematical formula}fk(i) were simulated from an IBP with {a mathematical formula}αc=10 (no channel had indicators exceeding the five specified states). The sampled {a mathematical formula}f(i) were then used to modify the channel state transition distributions by setting to 0 transitions to states with {a mathematical formula}fk(i)=0 and then renormalizing. Using these feature-constrained transition distributions, we simulated sequences {a mathematical formula}z1:T(i) for each channel {a mathematical formula}i=1,…,6 and for {a mathematical formula}T=2000. The event sequence {a mathematical formula}Z1:T was likewise simulated. Based on these sampled state sequences, and using the defined state-specific AR coefficients and channel covariances, we generated observations {a mathematical formula}y1:T as in Eq. (3).
      </paragraph>
      <paragraph>
       We ran our MCMC sampler for 6000 iterations, discarding the first 1000 as burn-in and thinning the chain by 10. Fig. 4 shows the generated data and its true states along with the inferred states and learned channel covariances for a representative posterior sample. The event state matching is almost perfect, and the channel state matching is quite good, though we see that the sampler added an additional (yellow) state in the middle of the first time series when it should have assigned that section to the cyan state. The scale and structure of the estimated event state covariances match the true covariances quite well. Furthermore, Table 1 shows how the posterior estimates of the channel state AR coefficients also center well around the true values.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Parsing a seizure
      </section-title>
      <paragraph>
       We tested the sparse factorial BP-AR-HMM on two similar seizures (events) from a patient of the Children's Hospital of Pennsylvania. These seizures were chosen because qualitatively they displayed a variety of dynamics throughout the beginning, middle, and end of the seizure and thus are ideal for exploring the extent to which our sparse factorial BP-AR-HMM can parse a set of rich neurophysiologic signals. We used the 90 seconds of data after the clinically-determined starts of each seizure from 16 channels, whose spatial layout in the electrode grid is shown in Fig. 5 along with the graph encoding our conditional independence assumptions. The data were low-pass filtered and downsampled from 200 to 50 Hz, preserving the clinically important signals but reducing the computational burden of posterior inference. The data was also scaled to have 99% of values within {a mathematical formula}[−10,10] for numerical reasons. We examined a 5th-order sparse factorial BP-AR-HMM and ran 10 MCMC chains for 6000 iterations, discarding 1000 samples as burn-in and using 10-sample thinning.
      </paragraph>
      <paragraph>
       The sparse factorial BP-AR-HMM inferred state sequences for the sample corresponding to a minimum expected Hamming distance criterion [18] are shown in Fig. 5. The results were analyzed by a board-certified epileptologist who agreed with the model's judgement in identifying the subtle changes from the background dynamic (cyan) initially present in all channels. The model's grouping of spatially-proximate channels into similar state transition patterns (e.g., channels 03, 07, 11, 15) was clinically intuitive and consistent with his own reading of the raw EEG. Using only the raw EEG, and prior to disclosing our results, he independently identified roughly six points in the duration of the seizure where the dynamics fundamentally change. The three main event state transitions shown in Fig. 5 occurred almost exactly at the same time as three of his own marked transitions. The fourth coincides with a major shift in the channel dynamics with most channels transitioning to the green dynamic. The other two transitions he marked that are not displayed occurred after this onset period. From this analysis, we see that our event states provide an important global summary of the dynamics of the seizure that augments the information conveyed from the channel state sequences.
      </paragraph>
      <section>
       <section-title>
        Clinical relevance
       </section-title>
       <paragraph>
        While interpreting these state sequences and covariances from the model, it is important to keep in mind that they are ultimately estimates of a system whose parsing even highly-trained physicians disagree upon. Nevertheless, we believe that the event states directly describe the activity of particular clinical interest.
       </paragraph>
       <paragraph>
        In modeling the correlations between channels, the event states give insight into how different physiologic areas of the brain interact over the course of a seizure. In the clinical workup for resective brain surgery, these event states could help define and specifically quantify the full range of ways in which neurophysiologic regions initiate seizures and how others are recruited over the numerous seizures of a patient. In addition, given fixed model parameters, our model can fit the channel and event state sequences of an hour's worth of 64-channel EEG data in a matter of minutes on a single 8-core machine, possibly facilitating epileptologist EEG annotation of long-term monitoring records.
       </paragraph>
       <paragraph>
        The ultimate clinical aim of this work, however, involves understanding the relationship between epileptic bursts and seizures. Because the event state aspect of our model involves a Markov assumption, the intrinsic length of the event has little bearing on the states assigned to particular time points. Thus, these event states allow us to straightforwardly compare the neurophysiologic relationship dynamics in short bursts (often less than two seconds long) to those in much longer seizures (on the order of two minutes long), as explored in Section 4.4. Prior to this analysis, we first examine the importance of our various model components by comparing to baseline alternatives.
       </paragraph>
      </section>
     </section>
     <section label="4.3">
      <section-title>
       Model comparison
      </section-title>
      <section>
       <section-title>
        The advantages of a spatial model
       </section-title>
       <paragraph>
        We explored the extent to which the spatial information and sparse dependencies encoded in the HIW prior improves our predictions of heldout data relative to a number of baseline models. To assess the impact of the sparse dependencies induced by the Gaussian graphical model for {a mathematical formula}ϵt, we compare to a full-covariance model with an IW prior on {a mathematical formula}Δl (dense factorial). For assessing the importance of spatial correlations, we additionally compare to two alternatives where channels evolve independently: the BP-AR-HMM of Fox et al. [5] and an AR-HMM without the feature-based modeling provided by the beta process [24]. Both of these models use inverse gamma (IG) priors on the individual channel innovation variances. We learned a set of AR coefficients {a mathematical formula}{ak} and event covariances {a mathematical formula}{Δl} on one seizure and then computed the heldout log-likelihood on a separate seizure, constraining it use the learned model parameters from the training seizure.
       </paragraph>
       <paragraph>
        For the training seizure, MCMC samples were collected over 5000 samples across 10 chains, each with a 1000-sample burn in and 10-sample thinning. To compute the predictive log-likelihood of the heldout seizure, we analytically marginalized the heldout event state sequence {a mathematical formula}Z1:T but perform a Monte Carlo integration over the feature vectors {a mathematical formula}f(i) and channel states {a mathematical formula}z1:T using our MCMC sampler. For each original MCMC sample generated from the training seizure, a secondary chain is run fixing {a mathematical formula}{ak} and {a mathematical formula}{Δl} and sampling {a mathematical formula}zt(i), {a mathematical formula}Zt, {a mathematical formula}f(i), {a mathematical formula}η(i), and {a mathematical formula}{ϕl} for the heldout seizure. We approximate {a mathematical formula}p(y1:T|{ϕl},{ak},{Δl}) by averaging the secondary chain's closed-form {a mathematical formula}p(y1:T|z1:T,{ϕl},{ak},{Δl}), described in Appendix B.
       </paragraph>
       <paragraph>
        Fig. 6 (left) shows how conditioning on the innovations of neighboring channels in the sparse factorial model improves the prediction of an individual channel, as seen by its reduced innovation trace relative to the original BP-AR-HMM. The quantitative benefits of accounting for these correlations are seen in our predictions of heldout events, as depicted in Fig. 6 (right), which compares the heldout log-likelihoods for the original and the factorial models listed above. As expected, the factorial models have significantly larger predictive power than the original models. Though hard to see due to the large factorial/original difference, the BP-based model also improves on the standard non-feature-based AR-HMM. Performance of the sparse factorial model is also at least as competitive as a full-covariance model (dense factorial). We would expect to see even larger gains for electrode grids with more channels due to the parsimonious representation presented by the graphical model. Regardless, these results demonstrate that the assumptions of sparsity in the channel dependencies do not adversely affect our performance.
       </paragraph>
      </section>
      <section>
       <section-title>
        The advantages of sparse factorial dependencies
       </section-title>
       <paragraph>
        In addition to providing a parsimonious modeling tool, the sparse dependencies among channels induced by the HIW prior allow our computations to scale linearly to the large number of channels present in iEEG. We compared a dense factorial BP-AR-HMM (entailing a fully-connected spatial graph) and a sparse factorial BP-AR-HMM on five datasets of 8, 16, 32, 64, and 96 channels (from three 32-channel electrodes) from the same seizure used previously. We ran the two models on each of the five datasets for at least 1000 MCMC iterations, using a profiler to tabulate the time spent in each step of the MCMC iteration.
       </paragraph>
       <paragraph>
        Fig. 7 shows the average time required to calculate the channel likelihoods at each time point under each AR channel state. This computation is used both for calculating the marginal likelihood (averaging over all the state sequences {a mathematical formula}z1:T(i)) required in active feature sampling as well as in sampling the state sequences {a mathematical formula}z1:T(i). In our sparse factorial model, each channel has a constant set of M dependencies, assuming M neighboring channels. As such, the channel likelihood computation at each time point has an {a mathematical formula}O(M) complexity, implying an {a mathematical formula}O(MN) complexity for calculating the likelihoods of all N channels at each time point. In contrast, the likelihood computation at each time point under the full covariance model had complexity {a mathematical formula}O(N), implying {a mathematical formula}O(N2) for calculating all the channel likelihoods. For {a mathematical formula}M≪N, as is typically the case, our sparse dependency model is significantly more computationally efficient.
       </paragraph>
       <paragraph>
        Anecdotally, we also found that the IW prior experiments—especially those with larger number of channels—tended to occasionally have numerical underflow problems associated with the inverse term {a mathematical formula}ΔZt−1(i′,i′) in the conditional channel likelihood calculation. This underflow in the IW prior model calculations is not surprising since the matrices inverted are of dimension {a mathematical formula}N−1 (for N channels), whereas in the HIW prior, the sparse spatial dependencies of the electrode grids make these matrices no larger than eight-by-eight.
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Comparing epileptic events of different scales
      </section-title>
      <paragraph>
       We applied our sparse factorial BP-AR-HMM to six channels of iEEG over 15 events from a human patient with hippocampal depth electrodes. These events comprise 14 short sub-clinical epileptic bursts of roughly five to eight seconds and a final, 2–3 minute clinical seizure. Our hypothesis was that the sub-clinical bursts display initiation dynamics similar to those of a full, clinical seizure and thus contain information about the seizure-generation process.
      </paragraph>
      <paragraph>
       The events were automatically extracted from the patient's continuous iEEG record by taking sections of iEEG whose median line-length feature [25] crossed a preset threshold, also including 10 seconds before and after each event. The iEEG was preprocessed in the same way as in the previous section. The six channels studied came from a depth electrode implanted in the left temporal lobe of the patient's brain. We ran our MCMC sampler jointly on the 15 events. In particular, the AR channel state and event state parameters, {a mathematical formula}{ak} and {a mathematical formula}{Δl}, were shared between the 15 events such that the parsings of each recording jointly informed the posteriors of these shared parameters. The hyperparameter settings, number of MCMC iterations, chains, and thinning was as in the experiment of Section 4.2.
      </paragraph>
      <paragraph>
       Fig. 8 compares two of the 14 sub-clinical bursts and the onset of the single seizure. We have aligned the three events relative to the beginnings of the red event state common to all three, which we treat as the start of the epileptic activity. The individual channel states of the four middle channels are also all green throughout most of the red event state. It is interesting to note that at this time the fifth channel's activity in all three events is much lower than those of the three channels above it, yet it is still assigned to the green state and continues in that state along with the other three channels as the event state switches from the red to the lime green state in all three events. While clinical opinions can vary widely in EEG reading, a physician would most likely not consider this segment of the fifth channel similar to the other three, as our model consistently does. But on a relative voltage axis, the segments actually look quite similar. In a sense, the fifth channel has the same dynamics as the other three but just with smaller magnitude. This kind of relationship is difficult for the human EEG readers to identify and shows how models such as ours are capable of providing new perspectives not readily apparent to a human reader. Additionally, we note the similarities in event state transitions.
      </paragraph>
      <paragraph>
       The similarities mentioned above, among others, suggest some relationship between these two different classes of epileptic events. However, all bursts make a notable departure from the seizure: a large one-second depolarization in the middle three channels, highlighted at the end by the magenta event state and followed shortly thereafter by the end of the event. Neither the states assigned by our model nor the iEEG itself indicates that dynamic present in the clinical seizure. This difference leads us to posit that perhaps these sub-clinical bursts are a kind of false-start seizure, with similar onset patterns but a disrupting discharge that prevents the event from escalating to a full-blown seizure.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      HMM sum-product algorithm
     </section-title>
     <paragraph>
      Consider a hidden Markov model of a sequence {a mathematical formula}y1:T with corresponding discrete states {a mathematical formula}z1:T, each of which takes one of K values. The joint probability of {a mathematical formula}y1:t and {a mathematical formula}zt=ℓ is{a mathematical formula} sometimes called a forward message, which depends on a recursive call for {a mathematical formula}y1:t−1 and {a mathematical formula}zt−1=k with{a mathematical formula}
     </paragraph>
     <paragraph>
      Calculating the marginal likelihood {a mathematical formula}p(y1:T) simply involves one last marginalization over {a mathematical formula}zT,{a mathematical formula}Algorithm 2 provides a numerically stable recipe for calculating this marginal likelihood.
     </paragraph>
     <paragraph>
      We can sample the states {a mathematical formula}z1:T from their joint distribution, also known as block sampling, via a similar recursive formulation. The conditional likelihood of the last {a mathematical formula}T−t samples given the state at t is{a mathematical formula} which depends recursively on the backward messages{a mathematical formula}p(yt+2:T|zt+1=k) for each {a mathematical formula}k∈{1,…,K}. To sample {a mathematical formula}z1:T at once we use the joint posterior distribution of the entire state sequence {a mathematical formula}z1:T, which factors into{a mathematical formula} If we first sample {a mathematical formula}z1, we can condition on it to then sample {a mathematical formula}z2 and continue in this fashion until we finish with {a mathematical formula}zT. The posterior for {a mathematical formula}zt is the product of the backward message, the likelihood of {a mathematical formula}yt given {a mathematical formula}zt, and the probability of {a mathematical formula}zt given {a mathematical formula}zt−1,{a mathematical formula} where {a mathematical formula}p(zt|zt−1)≜p(z1) for {a mathematical formula}t=1. A numerical stable recipe for this backward-filtering forward-sampling is given in Algorithm 3.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Individual channel variables posterior
     </section-title>
     <paragraph>
      Sampling the variables associated with the individual channel i involves first sampling active features {a mathematical formula}f(i) (while marginalizing {a mathematical formula}z1:T(i)), then conditioning on these feature assignments {a mathematical formula}f(i) to block sample the state sequence {a mathematical formula}z1:T(i), and finally sampling the transition distribution {a mathematical formula}π(i) given the feature indicators {a mathematical formula}f(i) and state sequence {a mathematical formula}z1:T(i). Explicit algorithms for this sampling are given in Wulsin [26, Section 4.2.1].
     </paragraph>
     <section>
      <section-title>
       Channel marginal likelihood
      </section-title>
      <paragraph>
       Let {a mathematical formula}i′⊆{1,…,N} index the neighboring channels in the graph upon which channel i is conditioned. The conditional likelihood of observation {a mathematical formula}yt(i) under AR model k given the neighboring observations {a mathematical formula}yt(i′) at time t is{a mathematical formula} for{a mathematical formula} which follows from the conditional distribution of the multivariate normal [27, pg. 579]. Using the forward-filtering scheme (see Algorithm 2) to marginalize over the exponentially many state sequences {a mathematical formula}z1:T(i), we can calculate the channel marginal likelihood,{a mathematical formula} of channel i's observations over all {a mathematical formula}t=1,…,T given the observations {a mathematical formula}y1:T(i′) and the assigned states {a mathematical formula}z1:T(i′) of neighboring channels {a mathematical formula}i′ and given the event state sequence {a mathematical formula}Z1:T. As previously discussed, taking the non-zero elements of the infinite-dimensional transition distributions {a mathematical formula}π(i), derived from {a mathematical formula}f(i) and {a mathematical formula}η(i) as in Eq. (9), yields a set of {a mathematical formula}K(i)-dimensional active feature transition distributions {a mathematical formula}π˜={π˜j}, reducing this marginalization to a series of matrix-vector products.
      </paragraph>
     </section>
     <section>
      Sampling active features, {a mathematical formula}f(i)
      <paragraph>
       We briefly describe the active feature sampling scheme given in detail by Fox et al. [5]. Recall that for our HIW-spatial BP-AR-HMM, we need to condition on neighboring channel state sequences {a mathematical formula}z1:T(i′) and event state sequences {a mathematical formula}Z1:T. Sampling the feature indicators {a mathematical formula}f(i) for channel i via the Indian buffet process (IBP) involves considering those features shared by other channels and those unique to channel i. Let {a mathematical formula}K+=∑k=1K1(fk(1)∨⋯∨fk(N)) denote the total number of active features used by at least one of the channels. We consider the set of shared features across channels not including those specific to channel i as {a mathematical formula}S(−i)⊆{1,…,K+} and the set of unique features for channel i as {a mathematical formula}U(i)⊆{1,…,K+}/S(−i).
      </paragraph>
      <section>
       <section-title>
        Shared features
       </section-title>
       <paragraph>
        The posterior for each shared feature {a mathematical formula}k∈S(−i) for channel i is given by{a mathematical formula} where the marginal likelihood of {a mathematical formula}y1:T(i) term (see Eq. (B.3)) follows from the sum-product algorithm. Recalling the form of the IBP posterior predictive distribution, we have {a mathematical formula}p(fk(i)=1|F−ik)=mk(−i)/N, where {a mathematical formula}mk(−i) denotes the number of other channels that use feature k. We use this posterior to formulate a Metropolis–Hastings proposal that flips the current indicator value {a mathematical formula}fk(i) to its complement {a mathematical formula}f¯k(i) with probability {a mathematical formula}ρ(f¯k(i)|fk(i)),{a mathematical formula} where{a mathematical formula}
       </paragraph>
      </section>
      <section>
       <section-title>
        Unique features
       </section-title>
       <paragraph>
        We either propose a new feature or remove a unique feature for channel i using a birth and death reversible jump MCMC sampler [28], [29], [30] (see Fox et al. [16] for details relevant to the BP-AR-HMM). We denote the number of unique features for channel i as {a mathematical formula}n(i)=|U(i)|. We define the vector of shared feature indicators as {a mathematical formula}f−(i)=fk′|k′∈S(−i)(i) and that for unique feature indicators as {a mathematical formula}f+(i)=fk′|k′∈U(i)(i), which together {a mathematical formula}(f−(i),f+(i)) define the full feature indicator vector {a mathematical formula}f(i) for channel i. Similarly, {a mathematical formula}a+(i) and {a mathematical formula}η+(i) describe the model dynamics and transition parameters associated with these unique features. We propose a new unique feature vector {a mathematical formula}f′+ and corresponding model dynamics {a mathematical formula}a′+ and transition parameters {a mathematical formula}η′+ (sampled from their priors in the case of feature birth) with a proposal distribution of{a mathematical formula} A new unique feature is proposed with probability 0.5 and each existing unique feature is removed with probability {a mathematical formula}0.5/n(i). This proposal is accepted with probability{a mathematical formula}
       </paragraph>
      </section>
     </section>
     <section>
      Channel state sequence, {a mathematical formula}z1:T(i)
      <paragraph>
       We block sample the state sequence for all the time points of channel i, given that channel's feature-constrained transition distributions {a mathematical formula}π(i), the state parameters {a mathematical formula}{ak}, the observations {a mathematical formula}y1:T(i), and the neighboring observations {a mathematical formula}y1:T(i′) and current states {a mathematical formula}z1:T(i′). The joint probability of the state sequence {a mathematical formula}z1:T(i) is given by{a mathematical formula} Again following the backward filtering forward sampling scheme (Algorithm 3), at each time point t we sample state {a mathematical formula}zt(i) conditioned on {a mathematical formula}zt−1(i) by marginalizing {a mathematical formula}zt+1:T(i). The conditional probability of {a mathematical formula}zt(i) is given by{a mathematical formula} where {a mathematical formula}π˜zt−1(i)(i) is the transition distribution given the assigned state at {a mathematical formula}t−1, {a mathematical formula}ut(i)∈RK(i) is the vector of likelihoods under each possible state at time t (as in Eq. (B.1)), and {a mathematical formula}ψt∈RK(i) is the vector of backwards messages (see Eq. (A.4)) from time point {a mathematical formula}t+1 to t.
      </paragraph>
     </section>
     <section>
      Channel transition parameters, {a mathematical formula}η(i)
      <paragraph>
       Following [20, Supplement], the posterior for the transition variable {a mathematical formula}ηjk(i) is given by{a mathematical formula} where {a mathematical formula}njk(i) denotes the number of times channel i transitions from state j to state k. We can sample from this posterior via two auxiliary variables,{a mathematical formula}
      </paragraph>
     </section>
    </section>
    <section label="Appendix C">
     <section-title>
      Event state variables posterior
     </section-title>
     <paragraph>
      Since we model the event state process with a (truncated approximation to the) HDP-HMM, inference is more straightforward than with the channel states. We block sample the event state sequence {a mathematical formula}Z1:T and then sample the event state transition distributions ϕ.
     </paragraph>
     <section>
      <section-title>
       Event marginal likelihood
      </section-title>
      <paragraph>
       Let {a mathematical formula}zt denote the vector of N channel states at time t. Since the space of {a mathematical formula}zt is exponentially large, we cannot integrate it out to compute the marginal conditional likelihood of the data given the event state sequence {a mathematical formula}Z1:T (and model parameters). Instead, we consider the conditional likelihood of an observation at time t given channel states {a mathematical formula}zt and event state {a mathematical formula}Zt=l,{a mathematical formula} Recalling Eq. (3), we see that this conditional likelihood of {a mathematical formula}yt is equivalent to a zero-mean multivariate normal model on the channel innovations {a mathematical formula}ϵt,{a mathematical formula} As with the channel marginal likelihoods, we use the forward-filtering algorithm (see Algorithm 2) to marginalize over the possible event state sequences {a mathematical formula}Z1:T, yielding a likelihood conditional on the channel states {a mathematical formula}zt and autoregressive parameters {a mathematical formula}{ak}, in addition to the event transition distribution ϕ and event state covariances {a mathematical formula}{Δl},{a mathematical formula}
      </paragraph>
     </section>
     <section>
      Event state sequence, {a mathematical formula}Z1:T
      <paragraph>
       The mechanics of sampling the event state sequence {a mathematical formula}Z1:T directly parallel those of sampling the individual channel state sequences {a mathematical formula}z1:T(i). The joint probability of the event state sequence is given by{a mathematical formula} We again use the backward filtering forward sampling scheme of the sum-product algorithm to block sample each event state whose conditional probability distribution over the L states is given by{a mathematical formula} where {a mathematical formula}ϕZt−1 is the transition distribution given the assigned state at {a mathematical formula}t−1, {a mathematical formula}vt∈RL is the vector of likelihoods under each of the L possible states at time t (as in Eq. (C.1)), and {a mathematical formula}ψt∈RL is again the vector of backwards messages from time point {a mathematical formula}t+1 to t. ∘ denotes element-wise product.
      </paragraph>
     </section>
     <section>
      Event transition parameters, ϕ
      <paragraph>
       The Dirichlet posterior for the event state l's transition distribution {a mathematical formula}ϕl simply involves the transition counts {a mathematical formula}nl from event state l to all L states,{a mathematical formula} for global weights β, concentration parameter {a mathematical formula}αe, and self-transition parameter {a mathematical formula}κe.
      </paragraph>
     </section>
     <section>
      Global transition parameters, β
      <paragraph>
       The Dirichlet posterior of the global transition distribution β involves the auxiliary variables {a mathematical formula}(m¯⋅1,…,m¯⋅L),{a mathematical formula} where these auxiliary variables are defined as{a mathematical formula} and {a mathematical formula}m⋅l′=∑lmll′. See Fox [31, Appendix A] for full derivations.
      </paragraph>
     </section>
    </section>
    <section label="Appendix D">
     <section-title>
      Hyperparameters posterior
     </section-title>
     <paragraph>
      Below we give brief descriptions for the MCMC sampling of the hyperparameters in our model. Full derivations are given in Fox [31, Section 5.2.3, Appendix C].
     </paragraph>
     <section>
      Channel dynamics model hyperparameters, {a mathematical formula}γc, {a mathematical formula}κc
      <paragraph>
       We use Metropolis–Hastings steps to propose a new value {a mathematical formula}γc′ from gamma distributions with fixed variance {a mathematical formula}σγc2 and accept with probability {a mathematical formula}min⁡(r(γc′|γc),1),{a mathematical formula} where {a mathematical formula}ν=γc2/σγc2, {a mathematical formula}ν′=γc′2/σγc2, and we have a {a mathematical formula}Gamma(a,b) prior on {a mathematical formula}γc. The likelihood term {a mathematical formula}p({π(i)}|γc′,κ,{f(i)}) follows from the Dirichlet distribution and is given by{a mathematical formula} where that for {a mathematical formula}p({π(i)}|γc,κ,{f(i)}) is similar. Recall that the transition parameters {a mathematical formula}{π(i)} are independent over i, and thus their likelihoods multiply. The proposal and acceptance ratio for {a mathematical formula}κc is similar.
      </paragraph>
     </section>
     <section>
      Channel active features model hyperparameter {a mathematical formula}αc
      <paragraph>
       We place a {a mathematical formula}Gamma(aαc,bαc) prior on {a mathematical formula}αc, which implies a gamma posterior of the form{a mathematical formula} where {a mathematical formula}K+=∑k=1K1(fk(1)∨⋯∨fk(N)) denotes the number of channel states activated in at least one of the channels.
      </paragraph>
     </section>
     <section>
      Event dynamics model hyperparameters, {a mathematical formula}γe, {a mathematical formula}αe, {a mathematical formula}κe, {a mathematical formula}ρe
      <paragraph>
       Instead of sampling {a mathematical formula}αe and {a mathematical formula}κe independently, we an additional parameter {a mathematical formula}ρe=κe/(αe+κe) and sample {a mathematical formula}(αe+κe) and {a mathematical formula}ρe, which is simpler than sampling {a mathematical formula}αe and {a mathematical formula}κe independently.
      </paragraph>
      <section>
       {a mathematical formula}(αe+κe)
       <paragraph>
        With a {a mathematical formula}Gamma(aαe+κe,bαe+κe) prior on {a mathematical formula}(αe+κe), we use auxiliary variables {a mathematical formula}{rl}l=1L and {a mathematical formula}{sl}l=1L to define the posterior,{a mathematical formula} where {a mathematical formula}m¯⋅⋅=∑l,l′=1Lm¯ll′ is the sum over auxiliary variables {a mathematical formula}m¯ll′ defined in Eq. (C.7), and the auxiliary variables {a mathematical formula}rl and {a mathematical formula}sl are sampled as{a mathematical formula}{a mathematical formula}
       </paragraph>
      </section>
      <section>
       {a mathematical formula}ρe
       <paragraph>
        With a {a mathematical formula}Beta(cρe,dρe) prior on {a mathematical formula}ρe, we use auxiliary variables {a mathematical formula}{wl⋅}l=1L to define the posterior,{a mathematical formula} For {a mathematical formula}wls∼Ber(ρ) over {a mathematical formula}s=1,…,mll, the posterior of the auxiliary variable {a mathematical formula}wl⋅ is{a mathematical formula}
       </paragraph>
      </section>
      <section>
       {a mathematical formula}γe
       <paragraph>
        With a {a mathematical formula}Gamma(aγe,bγe) prior on {a mathematical formula}γe, we use auxiliary variables v and q to define the posterior,{a mathematical formula} The auxiliary variables are sampled via{a mathematical formula}{a mathematical formula}
       </paragraph>
      </section>
     </section>
    </section>
    <section label="Appendix E">
     <section-title>
      Autoregressive state coefficients posterior
     </section-title>
     <paragraph>
      Recall that our prior on the autoregressive coefficients {a mathematical formula}ak is a multivariate normal with zero mean and covariance {a mathematical formula}Σ0,{a mathematical formula} The conditional event likelihood given the channel states {a mathematical formula}z1:T and the event states {a mathematical formula}Z1:T is{a mathematical formula} The product of these prior and likelihood terms is the joint distribution over {a mathematical formula}ak and {a mathematical formula}y1:T,{a mathematical formula} We take a brief tangent to prove a useful identity,
     </paragraph>
     <paragraph label="Lemma Appendix E.1">
      Let the column vector{a mathematical formula}x∈Rmand the symmetric matrix{a mathematical formula}A∈Sm×mbe defined as{a mathematical formula}where{a mathematical formula}y∈Rp,{a mathematical formula}z∈Rq,{a mathematical formula}B∈Sp×p,{a mathematical formula}D∈Sq×q,{a mathematical formula}C∈Rp×q, and{a mathematical formula}m=p+q. Then{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}  □ Note that this identity also holds for any permutation p applied to the rows of x and the rows and columns of A. We now can manipulate the likelihood term of Eq. (E.3) into a form that separates {a mathematical formula}ak from {a mathematical formula}ak′≠k. Suppose that {a mathematical formula}k+ denotes the indices of the N channels where {a mathematical formula}zt(i)=k and {a mathematical formula}k−={1,…,N}/k+ denotes those for whom {a mathematical formula}zt(i)≠k. Furthermore, we use the superscript indexing on these two sets of indices to select the corresponding portions of the {a mathematical formula}yt vector and the {a mathematical formula}Azt, {a mathematical formula}Y˜T, and {a mathematical formula}ΔZt−1 matrices. We start by decomposing the likelihood term into three parts,{a mathematical formula} which we then insert into our previous expression for the joint distribution of {a mathematical formula}ak and {a mathematical formula}y1:T (Eq. (E.3)),{a mathematical formula} Conditioning on {a mathematical formula}y1:T allows us to absorb the third term of the sum into the proportionality, and after replacing {a mathematical formula}Azt(k+,k+)Y˜(k+,k+) with a more explicit expression, we have{a mathematical formula} which we can further expand to yield{a mathematical formula} Absorbing more terms unrelated to {a mathematical formula}ak into the proportionality, we have{a mathematical formula} which after some rearranging gives{a mathematical formula} Before completing the square, we will find it useful to introduce a bit more notation to simplify the expression,{a mathematical formula} yielding{a mathematical formula} We desire an expression in the form {a mathematical formula}−12(ak−μk)TΣk−1(ak−μk) for unknown {a mathematical formula}μk and {a mathematical formula}Σk−1 so that it conforms to the multivariate normal density with mean {a mathematical formula}μk and precision {a mathematical formula}Σk−1. We already have our {a mathematical formula}Σk−1 value from the quadratic term above,{a mathematical formula} which allows us to solve the cross-term for {a mathematical formula}μk,{a mathematical formula} We can pull the final required {a mathematical formula}−12μkTΣk−1μk term from the proportionality and complete the square. Thus, we have the form of the posterior for {a mathematical formula}ak,{a mathematical formula} where{a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix F">
     <section-title>
      Experiment parameters
     </section-title>
     <paragraph>
      Below, we give explicit values for the various priors and parameters used in our experiments.
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>