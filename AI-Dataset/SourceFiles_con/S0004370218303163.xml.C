<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    On the adoption of abductive reasoning for time series interpretation.
   </title>
   <abstract>
    Time series interpretation aims to provide an explanation of what is observed in terms of its underlying processes. The present work is based on the assumption that the common classification-based approaches to time series interpretation suffer from a set of inherent weaknesses, whose ultimate cause lies in the monotonic nature of the deductive reasoning paradigm. In this document we propose a new approach to this problem, based on the initial hypothesis that abductive reasoning properly accounts for the human ability to identify and characterize the patterns appearing in a time series. The result of this interpretation is a set of conjectures in the form of observations, organized into an abstraction hierarchy and explaining what has been observed. A knowledge-based framework and a set of algorithms for the interpretation task are provided, implementing a hypothesize-and-test cycle guided by an attentional mechanism. As a representative application domain, interpretation of the electrocardiogram allows us to highlight the strengths of the proposed approach in comparison with traditional classification-based approaches.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The interpretation and understanding of the behavior of a complex system involves the deployment of a cognitive apparatus aimed at guessing the processes and mechanisms underlying what is observed. The human ability to recognize patterns plays a paramount role as an instrument for highlighting evidence which should require an explanation, by matching information from observations with information retrieved from memory. Classification naturally arises as a pattern recognition task, defined as the assignment of observations to categories.
     </paragraph>
     <paragraph>
      Let us first state precisely at this point what is the problem under consideration: we wish to interpret the behavior of a complex system by measuring a physical quantity along time. This quantity is represented as a time series.
     </paragraph>
     <paragraph>
      The Artificial Intelligence community has devoted a great deal of effort on different paradigms, strategies, methodologies and techniques for time series classification. Nonetheless, in spite of the wide range of proposals for building classifiers, either by eliciting domain knowledge or by induction from a set of observations, the resulting classifiers behaves as deductive system. The present work is premised on the assumption that some of the important weaknesses of this approach lie in its deductive nature, and that an abductive approach can address these shortcomings, which are described below.
     </paragraph>
     <paragraph>
      Let us remember that a deduction contains in its conclusions information that is already implicitly contained in the premises, and thus it is truth-preserving. In this sense, a classifier ultimately assigns a label or a set of labels to observations. This label can designate a process or a mechanism of the system being observed, but it is nothing more than a term that summarizes the premises implied by the observations. Conversely, abduction, or inference to the best explanation, is a form of inference that goes from data to a hypothesis that best explains or accounts for the data [21]. Abductive conclusions contain new information not contained in the premises, and are capable of predicting new evidence, although they are fallible. Abductions are thus truth-widening, and they can make the leap from the language of observations to the language of the underlying processes and mechanisms, responding to the aforementioned problem in a natural way [24]. For example, consider a simple rule stating that if a patient experiences a sudden tachycardia and a decrease in blood pressure, then we can conclude that he or she is suffering from shock due to a loss of blood volume. From a deductive perspective, loss of blood volume is just a name provided by the rule for the satisfaction of the two premises. However, from an abductive perspective, loss of blood volume is an explanatory hypothesis, a conjecture, that expands the truth contained in the premises, enabling the observer to predict additional consequences such as, for example, pallid skin, faintness, dizziness or thirst.
     </paragraph>
     <paragraph>
      Of course, the result of a classifier can be considered as a conjecture, but always from an external agent, since a classifier is monotonic as a logical system and its conclusions cannot be refuted from within. Classifier ensembles aim to overcome the errors of individual classifiers by combining different classification instances to obtain a better result; thus, a classifier can be amended by others in the final result of the ensemble. However, even an ensemble represents a bottom-up mapping, and classification invariably fails above a certain level of distortion within the data. The interpretation and understanding of a complex system usually unfolds along a set of abstraction layers, where at each layer the temporal granularity of the representation is reduced from below. A classification strategy provides an interpretation as the result of connecting a set of classifiers along the abstraction structure, and the monotonicity of deduction entails a propagation of errors from the first abstraction layers upwards, narrowing the capability of making a proper interpretation as new abstraction layers are successively added. Following an abductive process instead, an observation is conjectured at each abstraction layer as the best explanatory hypothesis for the data from the layer or layers below, within the context of information from above, and the non-monotonicity of abduction supports the retraction of any observation at any abstraction layer in the search for the best global explanation. Thus, bottom-up and top-down processing complement one another and provide a joint result. As a consequence, abduction can guess the underlying processes from corrupted data or even in the temporary absence of data.
     </paragraph>
     <paragraph>
      On the other hand, a classifier is based on the assumption that the underlying processes or mechanisms are mutually exclusive. Superpositions of two or more processes are excluded; they must be represented by a new process, corresponding to a new category which is different and usually unrelated to previous ones. Therefore, an artificial casuistry-based heuristics is adopted, increasing the complexity of the interpretation and reducing its adaptability to the variability of observations. In contrast, abduction can reach a conclusion from the availability of partial evidence, refining the result by the incremental addition of new information. This makes it possible to discern different processes just from certain distinguishable features, and at the end to infer a set of explanations as far as the available evidence does not allow us to identify the best one, and they are not incompatible with each other.
     </paragraph>
     <paragraph>
      In a classifier, the truth of the conclusion follows from the truth of all the premises, and missing data usually demand an imputation strategy that results in a conjecture: a sort of abducing to go on deducing. In contrast, an abductive interpretation is posed as a hypothesize-and-test cycle, in which missing data are naturally managed, since a hypothesis can be evoked by every single piece of evidence in isolation and these can be incrementally added to reasoning. This fundamental property of abduction is well suited to the time-varying requirements of the interpretation of time series, where future data can compel changes to previous conclusions, and the interpretation task may be requested to provide the current result as the best explanation at any given time.
     </paragraph>
     <paragraph>
      Abduction has primarily been proposed for diagnostic tasks [10], [33], but also for question answering [15], language understanding [22], story comprehension [6], image understanding [36] or plan recognition [28], amongst others. Some studies have proposed that perception might rely on some form of abduction. Even though abductive reasoning has been proven to be NP-complete or worse, a compiled form of abduction based on a set of pre-stored hypotheses could narrow the generation of hypotheses [24]. The present work takes this assumption as a starting point and proposes a model-based abductive framework for time series interpretation supported on a set of temporal abstraction patterns. An abstraction pattern represents a set of constraints that must be satisfied by some evidence in order to be interpreted as the hypothetical observation of a certain process, together with an observation procedure providing a set of measurements for the features of the conjectured observation. A set of algorithms is devised in order to achieve the best explanation through a process of successive abstraction from raw data, by means of a hypothesize-and-test strategy.
     </paragraph>
     <paragraph>
      Some previous proposals have adopted a non-monotonic schema for time series interpretation. TrenDx system detects significant trends in time series by matching data to predefined trend patterns [19], [20]. One of these patterns plays the role of the expected or normal pattern, and the other patterns are fault patterns. A matching score of each pattern is based on the error between the pattern and the data. Multiple trend patterns can be maintained as competing hypotheses according to their matching score; as additional data arrive some of the patterns can be discarded and new patterns can be triggered. This proposal has been applied to diagnose pediatric growth trends. A similar proposal can be found in [27], taking a step further by providing complex temporal abstractions, the result of finding out specific temporal relationships between a set of significant trends. This proposal has been applied to the infectious surveillance of heart transplanted patients. Another example is the Résumé system, a knowledge-based temporal abstraction framework [42], [39]. Its goal is to provide a set of interval-based temporal abstractions from time-stamped input data, distinguishing four output abstraction types: state, gradient, rate and pattern. It uses a truth maintenance system to retract inferred intervals that are no longer true, and propagate new abstractions. Furthermore, this framework includes a non-monotonic interpolation mechanism for trend detection [41]. This approach has been applied to several clinical domains (protocol-based care, monitoring of children's growth and therapy of diabetes) and to an engineering domain (monitoring of traffic control).
     </paragraph>
     <paragraph>
      The present work includes several examples and results from the domain of electrocardiography. The electrocardiogram (ECG) is the recording at the body's surface of the electrical activity of the heart as it changes with time, and is the primary method for the study and diagnosis of cardiac disease, since the processes involved in cardiac physiology manifest in characteristic temporal patterns on the ECG trace. In other words, a correct reading of the ECG has the potential to provide valuable insight into cardiac phenomena. Learning to interpret the ECG involves the acquisition of perceptual skills from an extensive bibliography with interpretation criteria and worked examples. In particular, pattern recognition is especially important in order to build a bottom-up representation of cardiac phenomena in multiple abstraction levels. This has encouraged extensive research on classification techniques for interpreting the ECG; however, in spite of all these efforts, this is still considered an open problem. We shall try to demonstrate that the problem lies in the nature of deduction itself.
     </paragraph>
     <paragraph>
      The rest of this paper is structured as follows: Section 2 introduces the main concepts and terminology used in the paper in an informal and intuitive way. Following this, in Sections 3, 4 and 5 we formally describe all the components of the interpretation framework, including the knowledge representation model and the algorithms used to obtain effective interpretations within an affordable time. Section 6 illustrates the capabilities of the framework in overcoming some of the most important shortcomings of deductive classifiers. Section 7 presents the main experimental results derived from this work. Finally, in section 8 we discuss the properties of the model compared with other related approaches and draw several conclusions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Interpretation as a process-guessing task
     </section-title>
     <paragraph>
      We propose a knowledge-based interpretation framework upon the principles of abductive reasoning, on the basis of a strategy of hypothesis formation and testing. Taking as a starting point a time series of physical measurements, a set of observations are guessed as conjectures of the underlying processes, through successive levels of abstraction. Each new observation will be generated from previous levels as the underlying processes aggregate, superimpose or concatenate to form more complex processes with greater duration and scope, and are organized into an abstraction hierarchy.
     </paragraph>
     <paragraph>
      The knowledge of the domain is described as a set of abstraction patterns as follows:{a mathematical formula} where {a mathematical formula}hψ(Ah,Thb,The) is an observable of the domain playing the role of a hypothesis on the observation of an underlying process ψ. {a mathematical formula}Ah represents a set of attributes, and {a mathematical formula}Thb and {a mathematical formula}The are two temporal instants representing the beginning and the end of the hypothesis. {a mathematical formula}m1(A1,T1),…,mn(An,Tn) is a set of observables of the domain which plays the role of the evidence suggesting the observation of {a mathematical formula}hψ. Each piece of evidence has its own set of attributes {a mathematical formula}Ai and temporal support {a mathematical formula}Ti, represented here as a single instant for the sake of simplicity, but it could also be an interval {a mathematical formula}(Tib,Tie). C is a set of constraints among the variables involved in the abstraction pattern, which are interpreted as necessary conditions in order for the evidence {a mathematical formula}m1(A1,T1),…,mn(An,Tn) to be abstracted into {a mathematical formula}hψ(Ah,Thb,The). Finally, {a mathematical formula}Θ(A1,T1,…,An,Tn) is an observation procedure that gives as a result an observation of {a mathematical formula}hψ(Ah,Thb,The) from a set of observations for {a mathematical formula}m1(A1,T1),…,{a mathematical formula}mn(An,Tn).
     </paragraph>
     <paragraph>
      To illustrate this concept, consider the sequence of observations in Fig. 1. Each of these observations is an instance of an observable we call point (p), represented as {a mathematical formula}p(A={V},T), where T determines the temporal location of the observation and V is a value attribute.
     </paragraph>
     <paragraph>
      If we analyze these observations visually, we may hypothesize the presence of an underlying sinusoidal process. Let us define an observable {a mathematical formula}sinus for such a sinusoidal process, with two attributes: the amplitude of the process (α) and its frequency (ω). The knowledge necessary to conjecture this hypothesis is collected in the following abstraction pattern:{a mathematical formula}
     </paragraph>
     <paragraph>
      We can estimate the attribute values {a mathematical formula}(α,ω,Thb,The) of this process by a simple observation procedure Θ that calculates {a mathematical formula}α=max(|Vi|), for {a mathematical formula}1≤i≤n, i.e., the amplitude α is obtained as the maximum absolute value of the observations; {a mathematical formula}ω=π/mean(Tjpeak−Tj−1peak), where {a mathematical formula}Tjpeak are point observations representing a peak, satisfying {a mathematical formula}(Vjpeak=Vk,Tjpeak=Tk)∧sign(Vk−Vk−1)≠sign(Vk+1−Vk), so that the frequency ω is obtained as the inverse of the mean temporal separation between consecutive peaks in the sequence of observations; and {a mathematical formula}Thb=T1,The=Tn, i.e., the temporal support of the hypothesis is the time interval between the first and the last evidence points.
     </paragraph>
     <paragraph>
      We can impose the following constraint {a mathematical formula}C(α,ω,Thb,The,V1,T1,…,Vn,Tn) for every pair {a mathematical formula}(Vi,Ti) in the sequence:{a mathematical formula}
     </paragraph>
     <paragraph>
      This constraint provides a model of a sinusoidal process and a measure of how well it fits a set of observations by means of a maximum error ϵ. Fig. 2 shows the continuous representation of the abstracted process, whose resulting observation is {a mathematical formula}hsinus(α=20,ω=0.3,Thb=1,The=94). A value of {a mathematical formula}α/3 has been chosen for ϵ.
     </paragraph>
     <paragraph>
      Of course, various observation procedures can be devised in order to estimate the same or different characteristics of the process being guessed. These procedures can provide one or several valid estimations in terms of their consistency with the abovementioned necessary constraints. In addition, different processes can be guessed from the same set of observations, all of them being valid in terms of their consistency. Hence, further criteria may be needed in order to rank the set of interpretations.
     </paragraph>
     <paragraph>
      This simple example summarizes the common approach to the interpretation of experimental results in science and technology, when the knowledge is available as a model or a set of models. The challenge is to assume that this knowledge is not available in an analytical but in a declarative form, as a pattern or a set of patterns, and that the interpretation task is expected to mimic certain mechanisms of human perception.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Definitions
     </section-title>
     <paragraph>
      In this section we formally define the main pieces of our interpretation framework: observables and observations for representing the behavior of the system under study, and abstraction patterns for representing the knowledge about this system.
     </paragraph>
     <section label="3.1">
      <section-title>
       Representation entities
      </section-title>
      <paragraph>
       An observation is the result of measuring something with the quality of being observable. We call {a mathematical formula}Q={q0,q1,…,qn} the set of observables of a particular domain.
      </paragraph>
      <paragraph label="Definition 1">
       We define an observable as a tuple {a mathematical formula}q=〈ψ,A,Tb,Te〉, where ψ is a name representing the underlying process being observable, {a mathematical formula}A={A1,…,Anq} is a set of attributes to be valued, and {a mathematical formula}Tb and {a mathematical formula}Te are two temporal variables representing the beginning and the end of the observable.
      </paragraph>
      <paragraph>
       We call {a mathematical formula}Vq(Ai) the domain of possible values for the attribute {a mathematical formula}Ai. We assume a representation of the time domain τ isomorphic to the set of real numbers {a mathematical formula}R. In the case of an instantaneous observable, this is represented as {a mathematical formula}q=〈ψ,A,T〉. Some observables can be dually represented from the temporal perspective, as either an observable supported by a temporal interval or as an observable supported by a temporal instant, according to the task to be carried out. A paradigmatic example is found in representing the heart beat, since it can be represented as a domain entity with a temporal extension comprising its constituent waves, and it can also be represented as an instantaneous entity for measuring heart rate.
      </paragraph>
      <paragraph label="Example 3.1">
       In the ECG signal, several distinctive waveforms can be identified, corresponding to the electrical activation-recovery cycle of the different heart chambers. The so-called P wave represents the activation of the atria, and is the first wave of the cardiac cycle. The next group of waves recorded is the QRS complex, representing the simultaneous activation of the right and left ventricles. Finally, the wave that represents the ventricular recovery is called the T wave. Together, these waveforms devise the characteristic pattern of the heart cycle, which is repeated in a normal situation with every beat [46]. An example of a common ECG strip is shown in Fig. 3.According to this description, the observable {a mathematical formula}qPw=〈atrial_activation, {a mathematical formula}{amplitude},Tb,Te〉 represents a P wave resulting from an atrial activation process with an unknown amplitude, localized in a still unknown temporal interval.
      </paragraph>
      <paragraph label="Definition 2">
       We define an observation as a tuple {a mathematical formula}o=〈q,v,tb,te〉, an instance of the observable q resulting from assigning a specific value to each attribute and to the temporal variables, where {a mathematical formula}v=(v1,…,vnq) is the set of attribute values such that {a mathematical formula}v∈Vq(A1)×…×Vq(Anq) and {a mathematical formula}tb,te∈τ are two precise instants limiting the beginning and the end of the observation. We also use the notation {a mathematical formula}(A1=v1,…,Anq=vnq) to represent the assignment of values to the attributes of the observable and {a mathematical formula}Tb=tb and {a mathematical formula}Te=te for representing the assignment of temporal limits to the observation.
      </paragraph>
      <paragraph label="Example 3.2">
       The tuple {a mathematical formula}o=〈qPw,0.17mV,12:16.977,12:17.094〉 represents the particular occurrence of the P wave observable highlighted in Fig. 3.
      </paragraph>
      <paragraph>
       Some notions involving observables and observations are defined below that will be useful in describing certain properties and constraints of the domain concepts, as well as in temporally arranging the interpretation process.
      </paragraph>
      <paragraph label="Definition 3">
       Given a set of observables {a mathematical formula}Q, a generalization relation can be defined between two different observables {a mathematical formula}q=〈ψ,A,Tb,Te〉 and {a mathematical formula}q′=〈ψ′,A′, {a mathematical formula}T′b,T′e〉, denoted by {a mathematical formula}q′is aq, meaning that q generalizes {a mathematical formula}q′ if and only if {a mathematical formula}A⊆A′ and {a mathematical formula}Vq′(Ai)⊆Vq(Ai)∀Ai∈A.
      </paragraph>
      <paragraph>
       The generalization relation is reflexive, antisymmetric and transitive. The inverse of a generalization relation is a specification relation. From a logical perspective, a generalization relation can be read as an implication {a mathematical formula}q′→q, meaning that {a mathematical formula}q′ is more specific than q. It holds that every observation {a mathematical formula}o=〈q′,v,tb,te〉 of the observable {a mathematical formula}q′ is also an observation of q.
      </paragraph>
      <paragraph label="Example 3.3">
       A common example of a generalization relation can be defined from a domain partition of an attribute. For example, the observable {a mathematical formula}q1=〈Sinus_Rhythm,{RR∈[200 ms,4000 ms]},Tb,Te〉 is a generalization of the observables {a mathematical formula}q2=〈Sinus_Tachycardia,{RR∈[200 ms,600 ms]},Tb,Te〉, {a mathematical formula}q3=〈Normal_Rhythm,{RR∈[600 ms,1000 ms]},Tb,Te〉 and {a mathematical formula}q4=〈Sinus_Bradycardia, {a mathematical formula}{RR∈[1000 ms,4000 ms]},Tb,Te〉. The RR attribute represents the measure of the mean time distance between consecutive beats, while {a mathematical formula}q2,q3 and {a mathematical formula}q4 represent the normal cardiac rhythm denominations according to the heart rate [46].
      </paragraph>
      <paragraph label="Definition 4">
       Given a set of observables {a mathematical formula}Q, an exclusion relation can be defined between two different observables {a mathematical formula}q=〈ψ,A,Tb,Te〉 and {a mathematical formula}q′=〈ψ′,A′, {a mathematical formula}T′b,T′e〉, denoted by {a mathematical formula}qexcludesq′, meaning that they are mutually exclusive if and only if their respective processes ψ and {a mathematical formula}ψ′ cannot concurrently occur.
      </paragraph>
      <paragraph>
       The exclusion relation is defined by extension from the knowledge of the domain, and its rationale lies in the nature of the underlying processes and mechanisms. Inasmuch as the occurrence of a process can only be hypothesized as long as it is observable, the exclusion relation behaves as a restriction on observations. Thus, given two observables q and {a mathematical formula}q′, {a mathematical formula}qexcludesq′ entails that they cannot be observed over two overlapping intervals, i.e., every two observations {a mathematical formula}o=〈q,v,tb,te〉 and {a mathematical formula}o′=〈q′,v′,t′b,t′e〉 satisfy either {a mathematical formula}te&lt;t′b or {a mathematical formula}t′e&lt;tb. The opposite is not generally true. The exclusion relation is symmetric and transitive. As an example, in the domain of electrocardiography, the knowledge about the physiology of the heart precludes the observation of a P wave during an episode of Atrial fibrillation[46], so these two observables are mutually exclusive.
      </paragraph>
      <paragraph>
       We call {a mathematical formula}O the set of observations available for the observables in {a mathematical formula}Q. In order to index this set of observations, they will be represented as a sequence by defining an order relation between them. This ordering aims to prioritize the interpretation of the observations as they appear.
      </paragraph>
      <paragraph label="Definition 5">
       Let &lt; be an order relation between two observations {a mathematical formula}oi=〈qi,vi,tib,tie〉 and {a mathematical formula}oj=〈qj,vj,tjb,tje〉 such that {a mathematical formula}(oi&lt;oj)⇔(tib&lt;tjb)∨((tib=tjb)∧(tie&lt;tje))∨((tib=tjb)∧(tie=tje)∧(qi&lt;qj)), assuming a lexicographical order between observable names.
      </paragraph>
      <paragraph>
       A sequence of observations is an ordered set of observations {a mathematical formula}O=(o1,…,oi,…) where for all {a mathematical formula}i&lt;j then {a mathematical formula}oi&lt;oj. Every subset of a sequence of observations is also a sequence. The q-sequence of observations from {a mathematical formula}O, denoted as {a mathematical formula}O(q), is the subset of the observations for the observable q. The exclusion relation forces that any two observations {a mathematical formula}oi=〈q,vi,tib,tie〉 and {a mathematical formula}oj=〈q,vj,tjb,tje〉 in {a mathematical formula}O(q) satisfy {a mathematical formula}oi&lt;oj⇒tie&lt;tjb for the current application domain. By {a mathematical formula}succ(oi) we denote the successor of the observation {a mathematical formula}oi in the sequence {a mathematical formula}O, according to the order relation &lt;. By q-{a mathematical formula}succ(oi) we denote the successor of the observation {a mathematical formula}oi∈O(q) in its q-sequence {a mathematical formula}O(q). Conversely to this notation, we denote by {a mathematical formula}q(oi) the observable corresponding to the {a mathematical formula}oi observation.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Abstraction patterns
      </section-title>
      <paragraph>
       We model an abstraction process as an abduction process, based on the conjectural relation {a mathematical formula}m←h[21], which can be read as ‘the observation of the finding m allows us to conjecture the observation of h as a possible explanatory hypothesis’. For example, a very prominent peak in the ECG signal allows us to conjecture the observation of a heartbeat. A key aspect of the present proposal is that both the hypothesis and the finding are observables, and therefore formally identical, i.e., there exists {a mathematical formula}qi,qj∈Q, with {a mathematical formula}qi≠qj, such that {a mathematical formula}h≡qi=〈ψi,Ai,Tib,Tie〉 and {a mathematical formula}m≡qj=〈ψj,Aj,Tjb,Tje〉. In general, an abstraction process can involve a number of different findings, even multiple findings of the same observable, and a set of constraints among them; thus, for example, a regular sequence of normal heartbeats allows us to conjecture the observation of a sinus rhythm. Additionally, an observation procedure is required in order to produce an observation of the hypothesis from the observation of those findings involved in the abstraction process.
      </paragraph>
      <paragraph label="Definition 6">
       We devise an abstraction process as a knowledge-based reasoning process, supported by the notion of abstraction pattern, which brings together those elements required to perform an abstraction. Formally: An abstraction pattern{a mathematical formula}P=〈h,MP,CP,ΘP〉 consists of a hypothesis h, a set of findings {a mathematical formula}MP={m1,…,mn}, a set of constraints {a mathematical formula}CP={C1,…,Ct} among the findings and the hypothesis, and an observation procedure {a mathematical formula}ΘP(A1,T1b,T1e,…,An,Tnb,Tne)∈O(h).
      </paragraph>
      <paragraph>
       Every constraint {a mathematical formula}Ci∈CP is a relation defined on a subset of the set of variables taking part in the set of findings and the hypothesis {a mathematical formula}{Ah,Thb,The,A1,T1b,T1e,…,An,Tnb,Tne}. Thus, a constraint is a subset of the Cartesian product of the respective domains, and represents the simultaneously valid assignments to the variables involved. We will denote each constraint by making reference to the set of variables being constrained, as in {a mathematical formula}CP(Ah,Thb,The,A1,T1b,T1e,…,An,Tnb,Tne) for the whole abstraction pattern.
      </paragraph>
      <paragraph>
       An abstraction pattern establishes, through the set {a mathematical formula}CP, the conditions for conjecturing the observation of h from a set of findings {a mathematical formula}MP, and through the observation procedure {a mathematical formula}ΘP, the calculations for producing a new observation {a mathematical formula}oh∈O(h) from the observation of these findings. We call {a mathematical formula}MPq={m1q,m2q,…,msq} the set of findings of the observable q in P, being {a mathematical formula}MP=⋃q∈QMPq. Thus, a set of findings allows the elements of a multiset of observables to be distinguished. The interpretation procedure will choose, as we will see later, from the available observations for every observable q satisfying the constraints {a mathematical formula}CP, which are to be assigned to the findings in {a mathematical formula}MPq in order to calculate {a mathematical formula}oh.
      </paragraph>
      <paragraph>
       The set of findings {a mathematical formula}MP is divided into two disjoint sets {a mathematical formula}AP and {a mathematical formula}EP, where {a mathematical formula}AP is the set of findings that is said to be abstracted in {a mathematical formula}oh, and {a mathematical formula}EP is the set of findings that constitute the observation environment of {a mathematical formula}oh, that is, the set of findings needed to properly conjecture {a mathematical formula}oh, but which are not synthesized in {a mathematical formula}oh.
      </paragraph>
      <paragraph>
       A temporal covering assumption can be made as a default assumption[36] on a hypothesis {a mathematical formula}h=〈ψh,Ah,Thb,The〉 with respect to those findings {a mathematical formula}m=〈ψm,Am, {a mathematical formula}Tmb,Tme〉 appearing in an abstraction pattern:
      </paragraph>
      <paragraph label="Default Assumption 1">
       (Temporal covering) Given an abstraction pattern P, it holds that{a mathematical formula}Thb≤Tmband{a mathematical formula}Tme≤The, for all{a mathematical formula}m∈AP⊆MP.
      </paragraph>
      <paragraph>
       The temporal covering assumption allows us to define the exclusiveness of an interpretation as the impossibility of including competing abstractions in the same interpretation.
      </paragraph>
      <paragraph label="Example 3.4">
       According to [11], in the electrocardiography domain a “wave” is a discernible deviation from a horizontal reference line called baseline, where at least two opposite slopes can be identified. The term discernible means that both the amplitude and the duration of the deviation must exceed some minimum values, agreed as 20 μV and 6 ms respectively. A wave can be completely described by a set of attributes: its amplitude (A), voltage polarity ({a mathematical formula}VP∈{+,−}) and its main turning point {a mathematical formula}Ttp, resulting in the following observable:{a mathematical formula}Let us consider the following abstraction pattern:{a mathematical formula} where {a mathematical formula}miECG is a finding representing an ECG sample, with a single attribute {a mathematical formula}Vi representing the sample value, and a temporal variable {a mathematical formula}Ti representing its time point. We set the onset and end of a wave to the time of the second {a mathematical formula}m1ECG and second-to-last {a mathematical formula}mn−1ECG samples, considering {a mathematical formula}m0ECG and {a mathematical formula}mnECG as environmental observations which are used to check the presence of a slope change just before and after the wave; thus {a mathematical formula}EPwave={m0ECG,mnECG}, and {a mathematical formula}APwave={m1ECG,…,mn−1ECG}.A set of temporal constraints are established between the temporal variables: {a mathematical formula}c1={Te−Tb≥6 ms}, {a mathematical formula}c2={Tb=T1}, {a mathematical formula}c3={Te=Tn−1} and {a mathematical formula}c4={Tb&lt;Ttp&lt;Te}. Another set of constraints limit the amplitude and slope changes of the samples included in a wave: {a mathematical formula}c5={sign(V1−V0)≠sign(V2−V1)}, {a mathematical formula}c6={sign(Vn−Vn−1)≠sign(Vn−1−Vn−2)}, {a mathematical formula}c7={sign(Vtp−Vtp−1)=−sign(Vtp+1−Vtp)} and {a mathematical formula}c8={min{|Vtp−V1|,|Vtp−Vn−1|}≥20μV}. These two sets form the complete set of constraints of the pattern {a mathematical formula}CPwave={c1,…,c8}.Once a set of ECG samples has satisfied these constraints, they support the observation of a wave: {a mathematical formula}owave=〈qwave,(a,vp,ttp),tb,te〉. The values of {a mathematical formula}tb and {a mathematical formula}te are completely determined by the constraints {a mathematical formula}c2 and {a mathematical formula}c3, while the observation procedure {a mathematical formula}wave_observation() provides a value for the attributes as follows: {a mathematical formula}vp=sign(Vtp−V1), {a mathematical formula}a=max{|Vtp−V1|,|Vtp−Vn−1|}, and {a mathematical formula}ttp=tb+tp, where {a mathematical formula}tp=argmink{Vk|1≤k≤n−1}, if {a mathematical formula}V1&lt;V0, or {a mathematical formula}tp=argmaxk{Vk|1≤k≤n−1}, if {a mathematical formula}V1&gt;V0.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Abstraction grammars
      </section-title>
      <paragraph>
       According to the definition, an abstraction pattern is defined over a fixed set of evidence findings {a mathematical formula}MP. In general, however, an abstraction involves an undetermined number of pieces of evidence – in the case of an ECG wave, the number of samples. Hence, we provide a procedure for dynamically generating abstraction patterns, based on the theory of formal languages. The set {a mathematical formula}Q of observables can be considered as an alphabet. Given an alphabet {a mathematical formula}Q, the special symbols ∅ (empty set), and λ (empty string), and the operators | (union), ⋅ (concatenation), and ⁎ (Kleene closure), a formal grammar G denotes a pattern of symbols of the alphabet, describing a language {a mathematical formula}L(G)⊆Q⁎ as a subset of the set of possible strings of symbols of the alphabet.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}Gap be the class of formal grammars of abstraction patterns. An abstraction grammar{a mathematical formula}G∈Gap is syntactically defined as a tuple {a mathematical formula}(VN,VT,H,R). For the production rules in R the expressiveness of right-linear grammars is adopted [23]:{a mathematical formula}
      </paragraph>
      <paragraph>
       H is the initial symbol of the grammar, and this plays the role of the hypothesis guessed by the patterns generated by G. {a mathematical formula}VN is the set of non-terminal symbols of the grammar, satisfying {a mathematical formula}H∈VN, although H cannot be found on the right-hand side of any production rule, since a hypothesis cannot be abstracted by itself. {a mathematical formula}VT is the set of terminal symbols of the grammar, representing the set of observables {a mathematical formula}QG⊆Q that can be abstracted by the hypothesis.
      </paragraph>
      <paragraph>
       Given a grammar {a mathematical formula}G∈Gap, we devise a constructive method for generating a set of abstraction patterns {a mathematical formula}PG={P1,…,Pi,…}. Since a formal grammar is simply a syntactic specification of a set of strings, every grammar {a mathematical formula}G∈Gap is semantically extended to an attribute grammar [1], embedded with a set of actions to be performed in order to incrementally build an abstraction pattern by the application of production rules. An abstraction grammar is represented as {a mathematical formula}G=((VN,VT,H,R),B,BR), where {a mathematical formula}B(α) associates each grammar symbol {a mathematical formula}α∈VN∪VT with a set of attributes, and {a mathematical formula}BR(r) associates each rule {a mathematical formula}r∈R with a set of attribute computation rules. An abstraction grammar associates the following attributes: i){a mathematical formula}P(attern), with each non-terminal symbol of the grammar; this will be assigned an abstraction pattern; ii){a mathematical formula}A(bstracted), with each terminal symbol corresponding to an observable {a mathematical formula}q∈QG; this allows us to assign each finding either to the set {a mathematical formula}AP or {a mathematical formula}EP, depending on its value of true or false; iii){a mathematical formula}C(onstraint), with each terminal symbol corresponding to an observable; this will be assigned a set of constraints. There are approaches in the bibliography dealing with different descriptions of Constraint Satisfaction Problems and their semantic expression in different formalisms [2], [5], [12]. By explicitly specifying a constraint as a relation a clear description is provided on its underlying meaning, but this can lead to cumbersome knowledge representation processes. Multiple mathematical conventions can concisely and conveniently describe a constraint as a Boolean-valued function over the variables of a set of observables. However, we will focus on the result of applying a set of constraints among the variables involved.
      </paragraph>
      <paragraph>
       In the following, the set of attribute computation rules associated with the grammar productions is specified to provide a formal method for building abstraction patterns {a mathematical formula}P∈PGh from a grammar {a mathematical formula}Gh∈Gap. {a mathematical formula}PGh gathers the set of abstraction patterns that share the same observable h as a hypothesis; thus, these represent the different ways to conjecture h. Using this method, the application of every production incrementally adds a new observable as a finding and a set of constraints between this finding and previous entities, as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        The initial production {a mathematical formula}H→qD entails:{a mathematical formula}
       </list-item>
       <list-item label="2.">
        All productions in the form {a mathematical formula}D→qF entail:{a mathematical formula}
       </list-item>
       <list-item label="3.">
        Productions in the form {a mathematical formula}D→q conclude the generation of a pattern {a mathematical formula}P∈PGh:{a mathematical formula}
       </list-item>
       <list-item label="4.">
        Productions in the form {a mathematical formula}D→λ also conclude the generation of a pattern:{a mathematical formula}
       </list-item>
      </list>
      <paragraph>
       This constructive method enables the incremental addition of new constraints as new findings are included in the representation of the abstraction pattern, providing a dynamic mechanism for knowledge assembly by language generation. The final constraints in {a mathematical formula}CP are obtained from the conjunction of the constraints added at each step. Moreover, it is possible to design an adaptive observation procedure as new evidence becomes available, since the observation procedure may be different at each step.
      </paragraph>
      <paragraph>
       In the case that no temporal constraints are attributed to a production, a ‘hereafter’ temporal relationship will be assumed by default to exist between the new finding and the set of previous findings. For instance, a production of the form {a mathematical formula}D→qF entails that {a mathematical formula}CF=CP∪{Tib≤Tk+1b|mi∈MP}.
      </paragraph>
      <paragraph>
       Hence, in the absence of any temporal constraint, an increasing temporal order among consecutive findings in every abstraction pattern is assumed. Moreover, every temporal constraint must be consistent with this temporal order.
      </paragraph>
      <paragraph>
       According to the limitation imposed on observations of the same observable which prevents two different observations from occurring at the same time, an additional constraint is added on any two findings of the same observable, and thus {a mathematical formula}∀miq,mjq∈MPq,(Tie&lt;Tjb∨Tje&lt;Tib).
      </paragraph>
      <paragraph>
       Several examples of abstraction pattern grammars modeling common knowledge in electrocardiography are given below, in order to illustrate the expressiveness of the {a mathematical formula}Gap grammars.
      </paragraph>
      <paragraph label="Example 3.5">
       The grammar {a mathematical formula}GN=(VN,VT,H,R) is designed to generate an abstraction pattern for a normal cardiac cycle, represented by the observable {a mathematical formula}qN, including the descriptions of common durations and intervals [46]. In this grammar, {a mathematical formula}VN={H,D,E}, {a mathematical formula}VT={a mathematical formula}{qPw,qQRS,qTw}, and R is given by:{a mathematical formula} This grammar generates a single abstraction pattern, which allows us to interpret the sequence of a P wave, a QRS complex, and a T wave as the coordinated contraction and relaxation of the heart muscle, from the atria to the ventricles. Some additional temporal constraints are required and specified in the semantic description of the production rules. In this case, an observation procedure Θ is not necessary since the attributes of the hypothesis are completely determined by the constraints in the grammar, and do not require additional calculus.
      </paragraph>
      <paragraph>
       The next example shows the ability of an abstraction grammar to generate abstraction patterns dynamically with an undefined number of findings.
      </paragraph>
      <paragraph label="Example 3.6">
       A bigeminy is a heart arrhythmia in which there is a continuous alternation of long and short heart beats. Most often this is due to ectopic heart beats occurring so frequently that there is one after each normal beat, typically premature ventricular contractions (PVCs) [46]. For example, a normal beat is followed shortly by a PVC, which is then followed by a pause. The normal beat then returns, only to be followed by another PVC. The grammar {a mathematical formula}GVB=(VN,VT,H,R) generates a set of abstraction patterns for ventricular bigeminy, where {a mathematical formula}VN={H,D,E,F}, {a mathematical formula}VT={a mathematical formula}{qN,qV}, and R is given by:{a mathematical formula}For simplicity, we have referenced each N and V heart beat with a single temporal variable. Thus {a mathematical formula}Ti represents the time point of the ith heart beat, and is a normal beat if i is odd, and a PVC if i is even. With the execution of these production rules, an unbounded sequence of alternating normal and premature ventricular QRS complexes is generated, described above as ventricular bigeminy. Note that in terms of the {a mathematical formula}{N,V} symbols the {a mathematical formula}GVB grammar is syntactically equivalent to the regular expression {a mathematical formula}NV(NV)+.In this example, as in 3.5, an observation procedure {a mathematical formula}ΘP is not necessary, since the constraints in the grammar completely determine the temporal endpoints of the hypothesis and there are no more attributes to be valued. Fig. 4 shows an example of a ventricular bigeminy pattern.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      An interpretation framework
     </section-title>
     <paragraph>
      In this section, we define and characterize an interpretation problem. Informally, an interpretation problem arises from the availability of a set of initial observations from a given system, and of domain knowledge formalized as a set {a mathematical formula}G={Gq1,…,Gqn} of {a mathematical formula}Gap grammars. Every abstraction grammar {a mathematical formula}Gh∈G generates a set of abstraction patterns that share the same hypothesis h. The whole set of abstraction patterns that can be generated by {a mathematical formula}G is denoted as {a mathematical formula}P.
     </paragraph>
     <paragraph label="Definition 7">
      Let {a mathematical formula}Q be a set of observables and {a mathematical formula}G a set of abstraction grammars. We say {a mathematical formula}G induces an abstraction relation in {a mathematical formula}Q×Q, denoted by {an inline-figure} if and only if there exists an abstraction pattern P generated by some {a mathematical formula}Gh∈G such that:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}qj=h
      </list-item>
      <list-item label="2.">
       {a mathematical formula}MPqi∩AP≠∅
      </list-item>
      <list-item label="3.">
       {an inline-figure}, where {an inline-figure} is the transitive closure of {an inline-figure}
      </list-item>
     </list>
     <paragraph>
      The relation {an inline-figure} is a sort of conjectural consequence relation[16] that allows us to conjecture the presence of {a mathematical formula}qj from the observation of {a mathematical formula}qi. The transitive closure of the abstraction relation is a strict partial order relation between the domain observables, such that {an inline-figure}; that is, if and only if {a mathematical formula}∃qk0,…,qkn∈Q such that {a mathematical formula}qk0=qi, {a mathematical formula}qkn=qj and for all m, with {a mathematical formula}0≤m&lt;n, it holds that {an inline-figure}. We denote by {an inline-figure} an abstraction sequence in n steps that allows the conjecture of {a mathematical formula}qj from {a mathematical formula}qi. This order relation defines an abstraction hierarchy among the observables in {a mathematical formula}Q. From the definition of a strict partial order, there must be at the base of this hierarchy at least one observable we call {a mathematical formula}q0, corresponding in the domain of electrocardiography to the digital signal.
     </paragraph>
     <paragraph label="Example 4.1">
      Let {a mathematical formula}Q={qPw,qQRS,qTw,qN,qV,qVB} and {a mathematical formula}G={GN,GVB}, containing the knowledge represented in Example 3.5, Example 3.6. The derived abstraction relation states that {an inline-figure}, and {an inline-figure}. Intuitively, we can see that this relation splits the observables into three abstraction levels: the wave level, describing the activation/recovery of the different heart chambers; the heartbeat level, describing each cardiac cycle by its origin in the muscle tissue; and the rhythm level, describing the dynamic behavior of the heart over multiple cardiac cycles. These levels match those commonly used by experts in electrocardiogram analysis [46].
     </paragraph>
     <paragraph>
      It is worth noting that the abstraction relation is only established between observables in the {a mathematical formula}AP set. This provides flexibility in defining the evidence forming the context of a pattern, as this may belong to different abstraction levels.
     </paragraph>
     <paragraph label="Definition 8">
      We define an abstraction model as a tuple {an inline-figure}, where {a mathematical formula}Q is the set of domain observables, {an inline-figure} is an abstraction relation between such observables, and {a mathematical formula}G is the available knowledge as a set of abstraction grammars.
     </paragraph>
     <paragraph>
      The successive application of the available abstraction grammars results in a series of observations organized in a hierarchy of abstraction, according to the order relation between observables as described above. We are able to define an interpretation problem as follows.
     </paragraph>
     <paragraph label="Definition 9">
      We define an interpretation problem as a pair {a mathematical formula}IP=〈O,M〉, where {a mathematical formula}O=(o1,o2,…,oi,…) is a sequence of observations requiring interpretation and {a mathematical formula}M is an abstraction model of the domain.
     </paragraph>
     <paragraph>
      It is worth mentioning that this definition of an abductive interpretation problem differs from the common definition of an abductive diagnosis problem, where the difference between normal and faulty behaviors is explicit, leading to the role of faulty manifestations that guide the abductive process of diagnosis. In contrast, in the present framework all the observations have the same status, and the objective of the interpretation process is to provide an interpretation of what is observed at the highest possible abstraction level in terms of the underlying processes. As we will see later, some observables may stand out amongst others regarding the efficiency of the interpretation process, as salient features that can draw some sort of perceptual attention.
     </paragraph>
     <paragraph>
      As discussed above, any observable {a mathematical formula}q∈QP can appear multiple times as different pieces of evidence for an abstraction pattern P, in the form of findings collected in the set {a mathematical formula}MP. As a consequence, P can predict multiple observations of the set {a mathematical formula}O for a given observable {a mathematical formula}q∈QP, each of these corresponding to one of the findings of the set {a mathematical formula}MP through a matching relation. This matching relation is a matter of choice for the agent in charge of the interpretation task, by selecting from the evidence the observation corresponding to each finding in a given pattern.
     </paragraph>
     <paragraph label="Definition 10">
      Given an interpretation problem IP, a matching relation for a pattern {a mathematical formula}P∈P is an injective relation in {a mathematical formula}MP×O, defined by {a mathematical formula}mq↢o if and only if {a mathematical formula}o=〈q,v,tb,te〉∈O(q)⊆O and {a mathematical formula}mq=〈ψ,A,Tb,Te〉∈MP, such that {a mathematical formula}(A1=v1,…,Anq=vnq), {a mathematical formula}Tb=tb and {a mathematical formula}Te=te.
     </paragraph>
     <paragraph>
      A matching relation makes an assignment of a set of observations to a set of findings of a certain pattern, leading us to understand the interpretation problem as a search within the available evidence for a valid assignment for the constraints represented in an abstraction pattern.
     </paragraph>
     <paragraph>
      From the notion of matching relation we can design a mechanism for abductively interpreting a subset of observations in {a mathematical formula}O through the use of abstraction patterns. Thus, a matching relation for a given pattern allows us to hypothesize new observations from previous ones, and to iteratively incorporate new evidence into the interpretation by means of a hypothesize-and-test cycle. The notion of abstraction hypothesis defines those conditions that a subset of observations must satisfy in order to be abstracted by a new observation, and makes it possible to incrementally build an interpretation from the incorporation of new evidence.
     </paragraph>
     <paragraph label="Definition 11">
      Given an interpretation problem IP, we define an abstraction hypothesis as a tuple {a mathematical formula}ħ=〈oh,P,↢〉, where {a mathematical formula}P=〈h,MP,CP,ΘP〉∈P, {a mathematical formula}↢⊆MP×O, and we denote {a mathematical formula}Oħ=codomain(↢), satisfying:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}oh∈O(h).
      </list-item>
      <list-item label="2.">
       {a mathematical formula}oh=ΘP(Oħ).
      </list-item>
      <list-item label="3.">
       {a mathematical formula}CP(Ah,Thb,The,A1,T1b,T1e,…,An,Tnb,Tne)|oh,o1,…,on∈Oħ is satisfied.
      </list-item>
     </list>
     <paragraph>
      These conditions entail: (1) an abstraction hypothesis guesses an observation of the observable hypothesized by the pattern; (2) a new observation is obtained from the application of the observation procedure to those observations being assigned to the set of findings {a mathematical formula}MP by the matching relation; and (3) the observations taking part in an abstraction hypothesis must satisfy those constraints of the pattern whose variables are assigned a value by the observations.
     </paragraph>
     <paragraph>
      Even though the matching relation is a matter of choice, and therefore a conjecture in itself, some additional constraints may be considered as default assumptions. An important default assumption in the abstraction of a periodic process states that consecutive observations are related by taking part in the same hypothesis, defining the basic period of the process. This assumption functions as a sort of operative hypothesis of the abstraction task:
     </paragraph>
     <paragraph label="Default Assumption 2">
      (Basic periodicity) Periodic findings in an abstraction pattern must be assigned consecutive observations by any matching relation:{a mathematical formula}
     </paragraph>
     <paragraph>
      This default assumption allows us to avoid certain combinations of abstraction hypotheses that, although formally correct, are meaningless from an interpretation point of view. For example, without the assumption of basic periodicity, a normal rhythm fragment might be abstracted by two alternating bradycardia hypotheses, as shown in Fig. 5.
     </paragraph>
     <paragraph>
      The set of observations that may be abstracted in an interpretation problem IP is {an inline-figure}, that is, observations corresponding to observables involved in the set of findings to be abstracted by some abstraction pattern. An abstraction hypothesis defines in the set of observations {a mathematical formula}O a counterpart of the subsets {a mathematical formula}AP and {a mathematical formula}EP of the set of findings {a mathematical formula}MP of a pattern P, resulting from the selection of a set of observations {a mathematical formula}Oħ⊆O by means of a matching relation, satisfying those requirements shown in the Definition 11.
     </paragraph>
     <paragraph label="Definition 12">
      Given an interpretation problem IP and an abstraction hypothesis {a mathematical formula}ħ=〈oh,P,↢〉, we define the following sets of observations:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}abstracted_by(oh)={o∈Oħ|miq↢o∧miq∈AP}.
      </list-item>
      <list-item label="•">
       {a mathematical formula}environment_of(oh)={o∈Oħ|miq↢o∧miq∈EP}.
      </list-item>
      <list-item label="•">
       {a mathematical formula}evidence_of(oh)=abstracted_by(oh)∪environment_of(oh).
      </list-item>
     </list>
     <paragraph>
      We denote by {a mathematical formula}abstracted_by(oh) the set of observations abstracted by {a mathematical formula}oh and which are somehow its constituents, while {a mathematical formula}environment_of(oh) denotes the evidential context of {a mathematical formula}oh. We denote by {a mathematical formula}evidence_of(oh) the set of all observations supporting a specific hypothesis. Since the matching relation is injective, it follows that {a mathematical formula}abstracted_by(oh)∩environment_of(oh)=∅.
     </paragraph>
     <paragraph>
      The definition of these sets can be generalized to include as arguments a set of observations {a mathematical formula}O={oh1,…,ohm} from a set of abstraction hypotheses {a mathematical formula}ħ1,…,ħm:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}abstracted_by(O)=⋃oh∈Oabstracted_by(oh)
      </list-item>
      <list-item label="•">
       {a mathematical formula}environment_of(O)=⋃oh∈Oenvironment_of(oh).
      </list-item>
      <list-item label="•">
       {a mathematical formula}evidence_of(O)=⋃oh∈Oevidence_of(oh).
      </list-item>
     </list>
     <paragraph>
      As a result of an abstraction hypothesis, a new observation {a mathematical formula}oh is generated which can be included in the set of domain observations, so that {a mathematical formula}O=O∪{oh}. In this way, an interpretation can be incrementally built from the observations, by means of the aggregation of abstraction hypotheses.
     </paragraph>
     <paragraph label="Definition 13">
      Given an interpretation problem IP, an interpretation is defined as a set of abstraction hypotheses {a mathematical formula}I={ħ1,…,ħm}.
     </paragraph>
     <paragraph>
      An interpretation can be rewritten as {a mathematical formula}I=〈OI,PI,↢I〉, where {a mathematical formula}OI={oh1,…{a mathematical formula},ohm} is the set of observations guessed by performing multiple abstraction hypotheses; {a mathematical formula}PI={P1,…,Pm} is the set of abstraction patterns used in the interpretation; and {a mathematical formula}↢I=↢ħ1∪…∪↢ħm{a mathematical formula}⊆(M1∪…∪Mm)×O is the global matching relation. It should be noted that the global matching relation {a mathematical formula}↢I is not necessarily injective, since some observations may simultaneously belong to both the {a mathematical formula}abstracted_by() and {a mathematical formula}environment_of() sets of different observations.
     </paragraph>
     <paragraph>
      From a given interpretation problem IP, multiple interpretations can be abductively proposed through different sets of abstraction hypotheses. Indeed, the definition of interpretation is actually weak, since even an empty set {a mathematical formula}I=∅ is formally a valid interpretation. Thus, we need additional criteria in order to select the solution to the interpretation problem as the best choice among different possibilities [33].
     </paragraph>
     <paragraph label="Definition 14">
      Given an interpretation problem IP, an interpretation I is a cover of IP if the set of observations to be interpreted {an inline-figure} is included in the set of observations abstracted by I, that is, {an inline-figure}.
     </paragraph>
     <paragraph label="Definition 15">
      Given an interpretation problem IP, two different abstraction hypotheses ħ and {a mathematical formula}ħ′ of the mutually exclusive observables {a mathematical formula}qh and {a mathematical formula}qh′ are alternative hypotheses if and only if {a mathematical formula}abstracted_by(oh)∩abstracted_by(oh′)≠∅.
     </paragraph>
     <paragraph label="Example 4.2">
      A ventricular trigeminy is an infrequent arrhythmia very similar to ventricular bigeminy, except that the ectopic heart beats occur after every pair of normal beats instead of after each one. The grammar for hypothesizing a ventricular trigeminy {a mathematical formula}qVT would therefore be very similar to that described in Example 3.6, with the difference that each {a mathematical formula}qV finding would appear after every pair of {a mathematical formula}qN findings. These two processes are mutually exclusive, insofar as the heart can develop just one of these activation patterns at a given time. For this reason, in the event of an observation of {a mathematical formula}qV, this may be abstracted by either a {a mathematical formula}qVB or a {a mathematical formula}qVT hypothesis, but never by both simultaneously.
     </paragraph>
     <paragraph label="Definition 16">
      Given an interpretation problem IP, a cover I for IP is exclusive if and only if it contains no alternative hypotheses.
     </paragraph>
     <paragraph>
      Thus, two or more different hypotheses of mutually exclusive observables abstracted from the same observation will be incompatible in the same interpretation, since inferring both a statement and its negation is logically prevented, and therefore only one of them can be selected.
     </paragraph>
     <paragraph>
      On the other hand, a parsimony criterion is required, in order to disambiguate the possible interpretations to select as the most plausible those of which the complexity is minimum [33]. We translate this minimum complexity in terms of minimal cardinality.
     </paragraph>
     <paragraph label="Definition 17">
      Given an interpretation problem IP, a cover I for IP is minimal, if and only if its cardinality is the smallest among all covers for IP.
     </paragraph>
     <paragraph>
      Minimality introduces a parsimony criterion on hypothesis generation, promoting temporally maximal hypotheses, that is, those hypotheses of a larger scope rather than multiple equivalent hypotheses of smaller scope. For example, consider an abstraction pattern that allows the conjecture of a regular cardiac rhythm from the presence of three or more consecutive heart beats. Without a parsimony criterion, a sequence of nine consecutive beats could be abstracted by up to three consecutive rhythm observations, even when a single rhythm observation would be sufficient and better.
     </paragraph>
     <paragraph label="Definition 18">
      The solution of an interpretation problem IP is the set of all minimal and exclusive covers of IP.
     </paragraph>
     <paragraph>
      This definition of solution is very conservative and has limited practical value, since the usual objective is to obtain a small set of interpretations explaining what has been observed (and ideally only a single one). However, it allows us to characterize the problem in terms of complexity. Abduction has been formulated under different frameworks according to the task to be addressed, but has always been found an intractable problem in the general case [24]. The next theorem proves that an interpretation problem is also an intractable problem.
     </paragraph>
     <paragraph label="Theorem 1">
      Finding the solution to an interpretation problem is NP-hard.
     </paragraph>
     <paragraph label="Proof">
      We will provide a polynomial-time reduction of the well-known set covering problem to an interpretation problem. Given a set of elements {a mathematical formula}U={u1,…,um} and a set S of subsets of U, a cover is a set {a mathematical formula}C⊆S of subsets of S whose union is U. In terms of complexity analysis, two different problems of interest are identified:
      <list>
       A set covering decision problem, stating that given a pair {a mathematical formula}(U,S) and an integer k the question is whether there is a set covering of size k or less. This decision version of set covering is NP-complete.A set covering optimization problem, stating that given a pair {a mathematical formula}(U,S) the task is to find a set covering that uses the fewest sets. This optimization version of set covering is NP-hard.Given a pair
      </list>
      <paragraph>
       {a mathematical formula}(U,S), let {a mathematical formula}φ(U,S)=〈O,M〉 where:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}O=U={u1,…,um}, such that {a mathematical formula}ui=〈q,true,i〉 and {a mathematical formula}q=〈ψ,present,T〉.
       </list-item>
       <list-item label="2.">
        {an inline-figure}, such that {an inline-figure}.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}∀s={ui1,…,uin}∈S,∃P∈P, being {a mathematical formula}P=〈qP,MP,CP,ΘP〉, where:
       </list-item>
      </list>
      <paragraph>
       Thus, {a mathematical formula}φ(U,S) is an interpretation problem according to this definition. On the other hand, {a mathematical formula}φ(U,S) can be built in polynomial time. In addition, for all {a mathematical formula}s∈S there exists an abstraction hypothesis {a mathematical formula}ħ=〈oh,P,↢〉 such that:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}oh=〈h,true,minui∈s{i},maxui∈s{i}〉.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}ui∈s⇒ui∈codomain(↢).
       </list-item>
       <list-item label="3.">
        ↢ provides a valid assignment, since the set of observations satisfying {a mathematical formula}ΘP=true also satisfies the constraints in {a mathematical formula}CP.
       </list-item>
      </list>
      <paragraph>
       Since each abstraction hypothesis involves a different abstraction pattern there are no alternative hypotheses in any interpretation of {a mathematical formula}φ(U,S).Suppose there is a set covering {a mathematical formula}C⊆S of U of size k or less. For all {a mathematical formula}u∈U there exists {a mathematical formula}ci∈C−{∅} such that {a mathematical formula}u∈ci and, by the above construction, there exists {a mathematical formula}ħi∈I such that {a mathematical formula}abstracted_by(ohi)={u∈codomain(↢ħi)}={u∈ci}=ci, and therefore, {an inline-figure}. That is, the set of abstraction hypotheses I is an exclusive cover of the interpretation problem {a mathematical formula}φ(U,S) of size k or less.Following the same reasoning as for the set covering optimization problem, finding a minimal and a exclusive cover of an interpretation problem {a mathematical formula}φ(U,S) is NP-hard, since we can use the solution of this problem to check whether there is an exclusive cover of the interpretation problem of size k or less, and this has been proven above to be NP-complete.  □
      </paragraph>
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Solving an interpretation problem: A heuristic search approach
     </section-title>
     <paragraph>
      The solution set for an interpretation problem IP consists of all exclusive covers of IP having the minimum possible number of abstraction hypotheses. Obtaining this solution set can be stated as a search on the set of interpretations of IP. The major source of complexity of searching for a solution is the local selection, from the available evidence in {a mathematical formula}O, of the most appropriate matching relation for a number of abstraction hypotheses that can globally shape a minimal and exclusive cover of IP.
     </paragraph>
     <paragraph>
      Nevertheless, the whole concept of solution must be revised in practical terms, due to the intractability of the task and the incompleteness of the abstraction model, that is, of the available knowledge. Indeed, we assume that any realistic abstraction model can hardly provide a cover for every possible interpretation problem. Hence the objective should shift from searching for a solution to searching for an approximate solution.
     </paragraph>
     <paragraph>
      Certain principles applicable to the interpretation problem can be exploited in order to approach a solution in an iterative way, bounding the combinatorial complexity of the search. These principles can be stated as a set of heuristics that make it possible to evaluate and discriminate some interpretations against others from the same base evidence:
     </paragraph>
     <list>
      <list-item label="•">
       A coverage principle, which states the preference for interpretations explaining more initial observations.
      </list-item>
      <list-item label="•">
       A simplicity principle, which states the preference for interpretations with fewer abstraction hypotheses.
      </list-item>
      <list-item label="•">
       An abstraction principle, which states the preference for interpretations involving higher abstraction levels.
      </list-item>
      <list-item label="•">
       A predictability principle, which states the preference for interpretations that properly predict future evidence.
      </list-item>
     </list>
     <paragraph>
      The coverage and simplicity principles are used to define a cost measure for the heuristic search process [14], while the abstraction and predictability principles are used to guide the reasoning process, in an attempt to emulate the same shortcuts used by humans.
     </paragraph>
     <paragraph>
      Given an interpretation problem IP, a heuristic vector for a certain interpretation I can be defined to guide the search, as {a mathematical formula}ϵ(I)=(1−ς(I),κ(I)), where {an inline-figure} is the covering ratio of I, and {a mathematical formula}κ(I)=|OI| is the complexity of I. The main goal of the search strategy is to approach a solution with a maximum covering ratio and a minimum complexity, which is equivalent to the minimization of the heuristic vector. The covering ratio will be considered the primary heuristic, and complexity will be considered for ranking interpretations with the same covering ratio. The {a mathematical formula}ϵ(I) heuristic is intuitive and very easy to calculate, but as a counterpart it is a non-admissible heuristic, since it is not monotone and may underestimate or overestimate the true goal covering. Therefore optimality cannot be guaranteed and we require an algorithm efficient with this type of heuristic. We propose the CONSTRUE() algorithm, whose pseudocode is shown in Algorithm 1. This algorithm is a minor variation of the K-Best First Search algorithm [14], with partial expansion to reduce the number of explored nodes.
     </paragraph>
     <paragraph>
      The CONSTRUE() algorithm takes as its input an interpretation problem IP, and returns the first interpretation found with full coverage, or the interpretation with the maximum covering ratio and minimum complexity if no covers are found, using the abstraction and predictability principles in the searching process. To do this, it manages two ordered lists of interpretations, named {a mathematical formula}open and {a mathematical formula}closed. Each interpretation is annotated with the computed values of the heuristic vector. The {a mathematical formula}open list contains those partial interpretations that can further evolve by (1) appending new hypotheses or (2) extending previously conjectured hypotheses to subsume or predict new evidence. This {a mathematical formula}open list is initialized with the trivial interpretation {a mathematical formula}I0=∅. The {a mathematical formula}closed list contains those interpretations that cannot explain more evidence.
     </paragraph>
     <paragraph>
      At each iteration, the algorithm selects the K most promising interpretations according to the heuristic vector (line 8), and partially expands each one of them to obtain the next descendant node {a mathematical formula}I′. If this node is a solution, then the process ends by returning it (line 13), otherwise it is added to the {a mathematical formula}open list. The partial expansion ensures that the {a mathematical formula}open list grows at each iteration by at most K new nodes, in order to save memory. When a node cannot expand further, it is added to the {a mathematical formula}closed list (line 12), from which the solution is taken if no full coverages are found (line 20).
     </paragraph>
     <paragraph>
      The selection of a value for the K parameter depends on the problem at hand. We select its value as {an inline-figure}, that is, as the maximum number of observables that can be abstracted from any observable {a mathematical formula}qi. The intuition behind this choice is that at any point in the interpretation process, and with the same heuristic values, the same chance is given to any plausible abstraction hypothesis in order to explain a certain observation.
     </paragraph>
     <paragraph>
      In order to expand the current set of interpretations, the GET_DESCEND-ANTS() function relies on different reasoning modes, that is, different forms of abduction and deduction, which are brought into play under the guidance of an attentional mechanism. Since searching for a solution finally involves the election of a matching relation, both observations and findings should be included in the scope of this mechanism. Hence, a focus of attention can be defined to answer the following question: which is the next observation or finding to be processed? The answer to this question takes the form of a hypothesize-and-test cycle: if the attention focuses on an observation, then an abstraction hypothesis explaining this observation should be generated (hypothesize); however, if the attention focuses on a finding predicted by some hypothesis, an observation should be sought to match such finding (test). Thus, the interpretation problem is solved by a reasoning strategy that progresses incrementally over time, coping with new evidence through the dynamic generation of abstraction patterns from a finite number of abstraction grammars, and bounding the theoretical complexity by a parsimony criterion.
     </paragraph>
     <paragraph>
      To illustrate and motivate the reasoning modes implemented in building interpretations and supporting the execution of the CONSTRUE() algorithm, we use a simple, but complete, interpretation problem.
     </paragraph>
     <paragraph label="Example 5.1">
      Let {a mathematical formula}Q={qwave,qPw,qQRS,qTw,qN},G={Gw,GN,GTw}, where {a mathematical formula}Gw models the Example 3.4, {a mathematical formula}GN is described in Example 3.5, and {a mathematical formula}GTw=({H,D},{qQRS,qwave},H,R) describes the knowledge to conjecture a T wave with the following rules:{a mathematical formula}This grammar hypothesizes the observation of a T wave from a wave appearing shortly after the observation of a QRS complex, requiring a significant decrease in the maximum slope of the signal (in the constraint definition {a mathematical formula}Cwave, the expression “max({a mathematical formula}diff(sig[m])” stands for the maximum absolute value of the derivative of the ECG signal between {a mathematical formula}Tmb and {a mathematical formula}Tme). The observation procedure of the generated pattern is denoted as {a mathematical formula}Tw_delin(), and may be any of the methods described in the literature for the delineation of T waves, such as in [26].In addition to the {a mathematical formula}Pwave pattern generated by {a mathematical formula}Gw and detailed in Example 3.4, {a mathematical formula}GN and {a mathematical formula}GTw generate the following abstraction patterns:{a mathematical formula}Finally, let {a mathematical formula}O={o1wave=〈qwave,∅,0.300,0.403〉,o2wave=〈qwave,∅,0.463, {a mathematical formula}0.549〉,oPw=〈qPw,∅,0.300,0.403〉,oQRS=〈qQRS,∅,0.463,0.549〉} be a set of initial observations including a P wave and a QRS complex abstracting two wave observations located at specific time points.Given this interpretation problem, Fig. 6 shows the starting point for the interpretation, where the root of the interpretation process is the trivial interpretation {a mathematical formula}I0, and the attention is focused on the first observation. The sequence of reasoning steps towards the resolution of this interpretation problem will be explained in the following subsections.
     </paragraph>
     <section label="5.1">
      <section-title>
       Focus of attention
      </section-title>
      <paragraph>
       The focus of attention is modeled as a stack; thus, once the focus is set on a particular observation (or finding), any observation that was previously under focus will not return to be focused on until the reasoning process on the current observation is finished. Algorithm 2 shows how the different reasoning modes are invoked based on the content of the focus of attention, resulting in a hypothesize-and-test cycle.
      </paragraph>
      <paragraph>
       Lines 4–8 generate the descendants of an interpretation I when there is an observation at the top of the stack. These descendants are the result of two possible reasoning modes: the deduction of new findings, performed by the DEDUCE() function, provided that the observation being focused on is an abstraction hypothesis; and the abduction of a new hypothesis explaining the observation being focused on, performed by the ABDUCE() function. A last descendant is obtained using the ADVANCE() function, which simply restores the previous focus of attention by means of a POP() operation. If the focus is then empty, ADVANCE() inserts the next observation to explain, which may be selected by temporal order in the general case, or by some domain-dependent saliency criterion to prioritize certain observations over others. By removing the observation at the top of the focus of attention, the ADVANCE() function sets aside that observation as unintelligible in the current interpretation, according to the available knowledge.
      </paragraph>
      <paragraph>
       If the top of the stack contains a finding, then Algorithm 2 obtains the descendants of the interpretation from the SUBSUME() and PREDICT() functions (line 10). The first of these functions looks for an existing observation satisfying the constraints on the finding focused on, while the second makes predictions about observables that have not yet been observed. All of these reasoning modes are described separately and detailed below; we will illustrate how the CONSTRUE() algorithm combines these in order to solve the interpretation problem in Example 5.1.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Building an interpretation: Abduction
      </section-title>
      <paragraph>
       Algorithm 3 enables the abductive generation of new abstraction hypotheses. It is applied when the attention is focused on an observation that can be abstracted by some abstraction pattern, producing a new observation at a higher level of abstraction.
      </paragraph>
      <paragraph>
       The result of ABDUCE() is a set of interpretations {a mathematical formula}I′, each one adding a new abstraction hypothesis with respect to the parent interpretation I. To generate these hypotheses, we iterate through those grammars that can make a conjecture from the observation {a mathematical formula}oi under focus (line 3). Then, for each grammar, each production including the corresponding observable {a mathematical formula}q(oi) (line 4) initializes an abstraction pattern with a single finding of this observable (line 5), and a new hypothesis is conjectured with a matching relation involving both the observation under focus and the finding (line 6). A list structure {a mathematical formula}Lħ and two additional variables {a mathematical formula}Bħ and {a mathematical formula}Eħ are initialized to trace the sequence of productions used to generate the findings in the abstraction pattern; these will play an important role in subsequent reasoning steps (line 7). Finally the new hypothesis opens a new interpretation (lines 8–9) focused on this hypothesis (line 11).
      </paragraph>
      <paragraph>
       In this way, the ABDUCE() function implements, from a single piece of evidence, the hypothesize step of the hypothesize-and-test cycle. Below we explain the reasoning modes involved in the test step of the cycle.
      </paragraph>
      <paragraph label="Example 5.2">
       Let us consider the interpretation problem set out in Example 5.1 and the interpretation {a mathematical formula}I0 shown in Fig. 6. According to Algorithm 2, the ABDUCE() function is used to move forward the interpretation, since the focus of attention points to an observation {a mathematical formula}oPw. The abstraction pattern that supports this operation is {a mathematical formula}PN, and a matching relation is established with the {a mathematical formula}mPw finding. As a result, the following hypothesis is generated:{a mathematical formula}Fig. 6 shows the result of this reasoning process, in a new interpretation called {a mathematical formula}I1. Note that the focus of attention has been moved to the newly created hypothesis (lines 10–11 of the ABDUCE() function).
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Building an interpretation: Deduction
      </section-title>
      <paragraph>
       This reasoning mode is applied when the attention is focused on an observation {a mathematical formula}oh previously conjectured as part of an abstraction hypothesis ħ (see Algorithm 4). The DEDUCE() function takes the evidence that has led to conjecture {a mathematical formula}oh and tries to extend it with new findings which can be expected, i.e., deduced, from the abstraction grammar {a mathematical formula}Gh used to guess the observation. The key point is that this deduction process follows an iterative procedure, as the corresponding abstraction pattern is dynamically generated from the grammar. Hence the DEDUCE() function aims to extend a partial matching relation by providing the next finding to be tested, as part of the test step of the hypothesize-and-test cycle.
      </paragraph>
      <paragraph>
       Since the first finding leading to conjecture {a mathematical formula}oh does not necessarily appear at the beginning of the grammar description, the corresponding abstraction pattern will not, in general, be generated incrementally from the first production of the grammar. Taking as a starting point the production used to conjecture {a mathematical formula}oh (line 4 in Algorithm 3), the goal is to add a new finding by applying a new production at both sides, towards the beginning and the end of the grammar, using the information in the {a mathematical formula}Lħ list. The {a mathematical formula}Bħ variable represents the non-terminal at the left-hand side of the first production in {a mathematical formula}Lħ, while {a mathematical formula}Eħ represents the non-terminal at the right-hand side of the last production in {a mathematical formula}Lħ. Hence, this list has the form {a mathematical formula}Lħ=[(Bħ→q′V′),(V′→q″V″),…,(V′n−1→q′nEħ)]. In case {a mathematical formula}Lħ is empty, both variables {a mathematical formula}Bħ and {a mathematical formula}Eħ represent the H non-terminal. With this information the sequence of findings supporting the hypothesis ħ can be updated in two opposite directions:
      </paragraph>
      <list>
       <list-item label="•">
        Towards the beginning of the grammar (lines 3–14): we explore the set of observables that may occur before the first finding according to the productions of the grammar (line 4), and a new finding is deduced for each of these in different descendant interpretations. A new pattern {a mathematical formula}PBħ associated with the {a mathematical formula}Bħ non-terminal is initialized with the new finding (line 5), and by moving along the sequence of productions generating the previous set of findings (lines 6–8) the pattern associated to the rightmost non-terminal {a mathematical formula}PEħ is updated with a new set of findings containing {a mathematical formula}mq. Consequently, the hypothesis and the interpretation are also updated (lines 9 and 10), and the applied production is inserted at the beginning of {a mathematical formula}Lħ (line 11). Finally the newly deduced finding is focused on (line 12).
       </list-item>
       <list-item label="•">
        Towards the end of the grammar (lines 15–23): for each one of the observables that may occur after the last finding, a new finding {a mathematical formula}mq is deduced, expanding the abstraction pattern associated with the new rightmost non-terminal X. After updating the hypothesis ħ, the previous pattern {a mathematical formula}PEħ in the resulting interpretation {a mathematical formula}I′ is replaced by the new one, {a mathematical formula}PX, and the applied production is inserted at the end of {a mathematical formula}Lħ. Finally, the new finding is focused on (line 21).
       </list-item>
      </list>
      <paragraph label="Example 5.3">
       Let us consider the interpretation problem set out in Example 5.1 and the interpretation {a mathematical formula}I1 shown in Fig. 6. Remember that the grammar used to generate the hypothesis in the focus of attention, {a mathematical formula}GN, has the following form:{a mathematical formula}In this situation, it is possible to deduce new findings from the {a mathematical formula}oN hypothesis. Following Algorithm 3 we can check that {a mathematical formula}Bħ=H and {a mathematical formula}Eħ=D, since the only finding in the matching relation is {a mathematical formula}mPw. Deduction then has to be performed after this last finding, using the production {a mathematical formula}D→qQRSE. After constraint checking, the resulting finding is as follows:{a mathematical formula}Fig. 6 illustrates the outcome of this reasoning process and the uncertainty in the temporal limits of the predicted finding, which is now focused on in the interpretation {a mathematical formula}I2.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Building an interpretation: Subsumption
      </section-title>
      <paragraph>
       Subsumption is performed when the attention is focused on a finding previously deduced from some abstraction grammar (see Algorithm 5). This reasoning mode avoids the generation of a new hypothesis for every piece of available evidence if it can be explained by a previous hypothesis. The SUBSUME() function explores the set of observations {a mathematical formula}O and selects those consistent with the constraints on the finding in the focus of attention (line 3), expanding the matching relation of the corresponding hypothesis in different descendant interpretations (line 4). The focus of attention is then restored to its previous state (line 5), allowing the deduction of new findings from the same hypothesis. The SUBSUME() function clearly enforces the simplicity principle.
      </paragraph>
      <paragraph label="Example 5.4">
       Let us consider the interpretation {a mathematical formula}I2 shown in Fig. 6. If we apply the subsumption procedure, it is possible to set a matching relation between {a mathematical formula}oQRS and {a mathematical formula}mQRS, since this observation satisfies all the constraints on the finding. The result is shown in the interpretation {a mathematical formula}I3. Note that the uncertainty in the end time of the {a mathematical formula}oN hypothesis is now reduced after the matching, having {a mathematical formula}TNe∈[0.631,1.030]. Following this, the attention focuses once again on this hypothesis, and a new deduction operation may be performed.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Building an interpretation: Prediction
      </section-title>
      <paragraph>
       This reasoning mode is also performed when the attention is focused on a finding deduced from some abstraction grammar (see Algorithm 6). In this case, if a finding previously deduced has not yet been observed, it will be predicted.
      </paragraph>
      <paragraph>
       The goal of the PREDICT() function is to conjecture a new observation to match the focused finding. For this, the abstraction model is explored and those grammars whose hypothesized observable is more specific than the predicted observable are selected (line 3). Then, a new pattern is initialized with no evidence supporting it, and a new abstraction hypothesis with an empty matching relation is generated (lines 4–5). Finally, the attention focuses on the observation being guessed (lines 9–10) to enable the DEDUCE() function to start a new test step at a lower abstraction level. Since {a mathematical formula}Lħ is initialized as an empty list (line 6), {a mathematical formula}Bħ and {a mathematical formula}Eħ point to the initial symbol of the grammar, and the corresponding abstraction pattern will be generated only towards the end of the grammar.
      </paragraph>
      <paragraph label="Example 5.5">
       Starting from the {a mathematical formula}I3 interpretation shown in Fig. 6, the next step we can take to move forward the interpretation is a new deduction on the {a mathematical formula}oN hypothesis, generating a new finding {a mathematical formula}mTw and leading to the {a mathematical formula}I4 interpretation. Since there is no available observation of the T wave, a matching with this new finding {a mathematical formula}mTw cannot be made by the SUBSUME() function, thus, the only option for moving forward this interpretation is through prediction. Following the PREDICT() function, the {a mathematical formula}GTw grammar can be selected, and a new observation {a mathematical formula}oTw can be conjectured, generating the {a mathematical formula}I5 interpretation.From {a mathematical formula}I5 we can continue the deduction on the {a mathematical formula}oTw hypothesis. If we apply the DEDUCE() function we obtain the {a mathematical formula}mQRS′ finding from the environment, shown in Fig. 6 as {a mathematical formula}I6. To move on, we can apply the SUBSUME() function, establishing the matching relation {a mathematical formula}{mQRS′↢oQRS}. This leads to the {a mathematical formula}I7 interpretation, in which the uncertainty on the {a mathematical formula}oTw observation is reduced; however, the evidence for the {a mathematical formula}PTw pattern is not yet complete. A new DEDUCE() step is necessary, which deduces the {a mathematical formula}mwave necessary finding in the {a mathematical formula}I8 interpretation. This finding is also absent, so another PREDICT() step is required. In this last step, the {a mathematical formula}Pwave pattern can be applied to observe the deviation in the raw ECG signal, generating the {a mathematical formula}o3wave observation and completing the necessary evidence for the {a mathematical formula}oTw observation and thus also for {a mathematical formula}oN. Constraint solving assigns the value of {a mathematical formula}tTwb, {a mathematical formula}tTwe and {a mathematical formula}tNe, so the result is a cover of the initial interpretation problem in which all the hypotheses have a necessary and sufficient set of evidence. This solution is depicted in {a mathematical formula}I9.It is worth noting that in this example the global matching relation {a mathematical formula}↢I is not injective, since {a mathematical formula}mQRS↢oQRS and {a mathematical formula}mQRS′↢oQRS. Also note that each interpretation only generates one descendant; in a more complex scenario, however, the possibilities are numerous, and the responsibility of finding the proper sequence of reasoning steps lies with the CONSTRUE() algorithm.
      </paragraph>
     </section>
     <section label="5.6">
      <section-title>
       Improving the efficiency of interpretation through saliency
      </section-title>
      <paragraph>
       Starting a hypothesize-and-test cycle for every single sample is not feasible for most of the time series interpretation problems. Still, many problems may benefit from certain saliency features that can guide the attention focus to some limited temporal fragments that can be easily interpretable. Thus, the interpretation of the whole time series can pivot on a reduced number of initial observations, thereby speeding up the interpretation process.
      </paragraph>
      <paragraph>
       A saliency-based attentional strategy can be devised from the definition of abstraction patterns using a subset of their constraints as a coarse filter to identify a set of plausible observations. For example, in the ECG interpretation problem the most common strategy is to begin the analysis by considering a reduced set of time points showing a significant slope in the signal, consistent with the presence of QRS complexes [47]. This small set of evidence allows us to focus the interpretation on the promising signal segments, in the same way that a cardiologist focuses on the prominent peaks to start the analysis [46]. It should be noted that this strategy is primarily concerned with the behavior of the focus of attention, and that it does not discard the remaining, non-salient observations, as these are included later in the interpretation by means of the subsumption and prediction reasoning modes.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Advantages of the framework
     </section-title>
     <paragraph>
      In this section we provide several practical examples which illustrate some of the strengths of the proposed interpretation framework and its ability to overcome typical weaknesses of the strategies based solely on a classification approach.
     </paragraph>
     <section label="6.1">
      <section-title>
       Avoiding a casuistry-based interpretation
      </section-title>
      <paragraph>
       In the time domain, classification-based recognition of multiple processes occurring concurrently usually leads to a casuistry-based proliferation of classes, in which a new class is usually needed for each possible superposition of processes in order to properly identify all situations. It is common to use a representation in the transform domain, where certain regular processes are easily separable, although at the expense of a cumbersome representation of the temporal information [30]. In contrast, in the proposed framework, the hypothesize-and-test cycle aims to conjecture those hypotheses that best explain the available evidence, including simultaneous hypotheses in a natural way as long as these are not mutually exclusive.
      </paragraph>
      <paragraph>
       ECG interpretation provides some interesting examples of this type of problem. Atrial fibrillation, a common heart arrhythmia caused by the independent and erratic contractions of the atrial muscle fibers, is characterized by an irregularly irregular heart rhythm [46]. Most of the classification techniques for the identification of atrial fibrillation are based on the analysis of the time interval between consecutive beats, and attempt to detect this irregularity [34]. These techniques offer good results in those situations in which atrial fibrillation is the only anomaly, but they fail to properly identify complex scenarios which go beyond the distinction between atrial fibrillation and normal rhythm. In the strip shown in Fig. 7, obtained during a pilot study for the home follow-up of patients with cardiac diseases [38], such a classifier would wrongly identify this segment as an atrial fibrillation episode, since the observed rhythm variability is consistent with the description of this arrhythmia. In contrast, the present interpretation framework correctly explains the first five beats as a sinus bradycardia, compatible with the presence of a premature ectopic beat in the second position, followed by a trigeminy pattern during six beats, and finally another ectopic beat with a morphology change. The reason to choose this interpretation, despite being more complex than the atrial fibrillation explanation, is that it is able to abstract some of the small P waves before the QRS complexes, increasing the interpretation coverage.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Coping with ignorance
      </section-title>
      <paragraph>
       Most of the classifiers solve a separability problem among classes, either by learning from a training set or by eliciting prior knowledge, and these are implicitly based on the closed-world assumption, i.e., every new instance to be classified is assigned to one of the predefined classes. Such classifiers may additionally include a ‘reject’ option for all those instances that could be misclassified since they appear too close to the classification boundaries [7], [17]. This reject option is added as another possible answer expressing doubt. However, such classifiers fail to classify new instances of unknown classes, since they cannot express ignorance. An approach to this problem can be found in novelty detection proposals [35], which can detect when a new instance does not fit any of the predefined classes as it substantially differs from those instances available during training. Still, these are limited to a common feature representation for every instance, hindering the identification of what is unintelligible from the available knowledge.
      </paragraph>
      <paragraph>
       The proposed framework provides an expression of ignorance as a common result of the interpretation problem. As long as the abstraction model is incomplete, the non-coverage of some piece of evidence by any interpretation is an expression of partial ignorance. In the extreme case, the trivial interpretation {a mathematical formula}I0 may be a correct solution of an interpretation problem, expressing total ignorance. Furthermore, abduction naturally includes the notion of ignorance in the reasoning process, since any single piece of evidence can be sufficient to guess an interpretation, and the hypothesize-and-test cycle can be understood as a process of incremental addition of evidence against an initial state of ignorance, while being able to provide an interpretation at any time based on the available evidence.
      </paragraph>
      <paragraph>
       As an example, consider the interpretation problem illustrated in Fig. 8. Let the initial evidence be the set of QRS annotations obtained by a state-of-the art detection algorithm [47]. In this short strip, the eighth and ninth annotations correspond to false positives caused by noise. A classification-based strategy processes these two annotations as true QRS complexes, and the monotone nature of the reasoning prevents their possible refutation, probably leading to beat misclassification and false arrhythmia detection, with errors propagating onwards to the end of the processing. In contrast, the present framework provides a single normal rhythm as the best interpretation, which explains all but the two aforementioned annotations, which are ignored and considered unintelligible in the available model. It is also worth noting the ability of this framework to integrate the results of an available classifier as a type of constraint specification in the interpretation cycle.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Looking for missing evidence
      </section-title>
      <paragraph>
       The application of the classification paradigm to pattern detection also entails the potential risk of providing false negative results. In the worst case, a false negative result may be interpreted by a decision maker as evidence of absence, leading to interpretation errors with their subsequent costs, or in the best case as an absence of evidence caused by the lack of a proper detection instrument.
      </paragraph>
      <paragraph>
       Even though abduction is fallible, and false negative results persist, the hypothesize-and-test cycle involves a prediction mechanism that points to missing evidence that is expected and, moreover, estimates when it should appear. Both the bottom-up and top-down processing performed in this cycle reinforces confidence in the interpretation, since the semantics of any conclusion is widened according to its explanatory power.
      </paragraph>
      <paragraph>
       As an example, consider the interpretation problem illustrated in Fig. 9. The initial evidence is again a set of QRS annotations obtained by a state-of-the-art detection algorithm [47]. Note that the eighth beat has not been annotated, due to a sudden decrease in the signal amplitude. This error can be amended in the hypothesize-and-test cycle, since the normal rhythm hypothesis that abstracts the first seven QRS annotations predicts the following QRS to be in the position of the missing annotation, and the PREDICT() procedure can look for this (e.g., checking an alternative set of constraints).
      </paragraph>
      <paragraph>
       The capability of abduction to ignore or look for new evidence has been tested with a simplified version of the present framework in the QRS detection problem [43], leading to a statistically significant improvement over a state-of-the art algorithm.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Interpretability of the reasoning process and the results
      </section-title>
      <paragraph>
       The interpretability of a reasoning formalism, defined as the ability to understand and evaluate its conclusions, is an essential feature for achieving an adequate confidence in decision making [31]. In this sense, there are a number of classification methods with good interpretability; however, the methods that typically offer the best performance belong to the so-called black box approaches.
      </paragraph>
      <paragraph>
       The present interpretation framework is able to provide a justification of any result in relation to the available model. Given any solution or partial solution of an interpretation problem, the searching path up to {a mathematical formula}I0 gives full details of all the reasoning steps taken to this end, and any abstraction hypothesis can be traced back to the information supporting it.
      </paragraph>
      <paragraph>
       This interpretation framework is also able to answer the question of why a certain hypothesis has been rejected or neglected at any reasoning step. This is done by exploring the branches outside the path between {a mathematical formula}I0 and the solution. Since the K exploration parameter within the CONSTRUE() algorithm has been chosen as the maximum number of hypotheses that may explain a given observable, it is possible to reproduce the reasoning steps taken in the conjecture of any abstraction hypothesis, and to check why this did not succeed (non-satisfaction of pattern constraints, lower coverage, etc.). This can be useful in building and refining the knowledge base.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Experimental evaluation: beat labeling and arrhythmia detection
     </section-title>
     <paragraph>
      The interpretation of electrocardiograms has served both as a challenge and as an inspiration for the AI community due to a number of factors that can be summarized as: (1) the complexity of the physiological processes underlying what is observed; and (2) the absence of an accurate model of the heart and the hardly formalizable knowledge that constitutes the experience of the cardiologist. There are numerous problems falling within the scope of ECG interpretation, the most relevant being heartbeat labeling [29]. We have tested the present framework by abductively identifying and measuring a set of qualitative morphological and rhythm attributes for each heartbeat, and using a rule-based classifier to assign a label to clusters of similar heartbeats [44]. It is noteworthy that an explicit representation of knowledge has been adopted, namely the kind of knowledge that can be found in an ECG handbook. Table 1 reproduces the performance comparison between this approach and the most relevant automatic and assisted approaches of the state-of-the art, using sensitivity and positive predictivity of ventricular and supraventricular ectopic beat classes.
     </paragraph>
     <paragraph>
      As it can be seen, this method significantly outperforms any other automatic approaches in the state-of-the-art, and even improves most of the assisted approaches that require expert aid. The most remarkable improvement concerns the classification of supraventricular ectopic beats, which are usually hard to distinguish using only morphological features. The abductive interpretation in multiple abstraction levels, including a rhythm description of signal, is what enables a more precise classification of each individual heartbeat.
     </paragraph>
     <paragraph>
      Furthermore, the abductive interpretation approach has been used for arrhythmia detection in short single-lead ECG records, focusing on atrial fibrillation [45]. The interpretation results are combined with machine learning techniques to obtain an arrhythmia classifier, achieving the best score in the 2017 Physionet/CinC Challenge dataset and outperforming some of the most popular techniques such as deep learning and random forests [8].
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>