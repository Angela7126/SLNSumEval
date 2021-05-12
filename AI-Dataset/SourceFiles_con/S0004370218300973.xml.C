<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Predicting citywide crowd flows using deep spatio-temporal residual networks.
   </title>
   <abstract>
    Forecasting the flow of crowds is of great importance to traffic management and public safety, and very challenging as it is affected by many complex factors, including spatial dependencies (nearby and distant), temporal dependencies (closeness, period, trend), and external conditions (e.g. weather and events). We propose a deep-learning-based approach, called ST-ResNet, to collectively forecast two types of crowd flows (i.e. inflow and outflow) in each and every region of a city. We design an end-to-end structure of ST-ResNet based on unique properties of spatio-temporal data. More specifically, we employ the residual neural network framework to model the temporal closeness, period, and trend properties of crowd traffic. For each property, we design a branch of residual convolutional units, each of which models the spatial properties of crowd traffic. ST-ResNet learns to dynamically aggregate the output of the three residual neural networks based on data, assigning different weights to different branches and regions. The aggregation is further combined with external factors, such as weather and day of the week, to predict the final traffic of crowds in each and every region. We have developed a real-time system based on Microsoft Azure Cloud, called UrbanFlow, providing the crowd flow monitoring and forecasting in Guiyang City of China. In addition, we present an extensive experimental evaluation using two types of crowd flows in Beijing and New York City (NYC), where ST-ResNet outperforms nine well-known baselines.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Predicting crowd flows in a city is of great importance to traffic management, risk assessment, and public safety [2]. For instance, massive crowds of people streamed into a strip region at the 2015 New Year's Eve celebrations in Shanghai, resulting in a catastrophic stampede that killed 36 people. In mid-July of 2016, hundreds of “Pokemon Go” players ran through New York City's Central Park in hopes of catching a particularly rare digital monster, leading to a dangerous stampede there. If one can predict the crowd flow in a region, such tragedies can be mitigated or prevented by utilizing emergency mechanisms, such as conducting traffic control, sending out warnings, or evacuating people, in advance.
     </paragraph>
     <paragraph>
      In this paper, we predict two types of crowd flows [3]: inflow and outflow, as shown in Fig. 1(a). Inflow is the total traffic of crowds entering a region from other places during a given time interval. Outflow denotes the total traffic of crowds leaving a region for other places during a given time interval. Both types of flows track the transition of crowds between regions. Knowing them is very beneficial for risk assessment and traffic management. Inflow/outflow can be measured by the number of pedestrians, the number of cars driven nearby roads, the number of people traveling on public transportation systems (e.g. metro, bus), or all of them together if data is available. Fig. 1(b) presents an illustration. We can use mobile phone signals to measure the number of pedestrians, showing that the inflow and outflow of {a mathematical formula}r2 are {a mathematical formula}(3,1), respectively. Similarly, using the GPS trajectories of vehicles, two types of flows are {a mathematical formula}(0,3), respectively. Therefore, the total inflow and outflow of {a mathematical formula}r2 are {a mathematical formula}(3,4), respectively. Apparently, predicting crowd flows can be viewed as a kind of spatio-temporal prediction problem [2].
     </paragraph>
     <paragraph>
      Deep learning [4] has been used successfully in many applications, and is considered to be one of the most cutting-edge artificial intelligence (AI) techniques. Exploring these techniques for spatio-temporal data is of great importance to a series of various spatio-temporal applications, including urban planning, transportation, the environment, energy, social, economy, public safety and security [2]. Although two main types of deep neural networks (DNNs) have considered a sort of spatial or temporal property: 1) convolutional neural networks (CNNs) for capturing spatial structures; 2) recurrent neural networks (RNNs) for learning temporal dependencies. It is still very challenging to apply these existing AI techniques for such spatio-temporal prediction problem because of the following three complex factors:
     </paragraph>
     <list>
      <list-item label="1.">
       Spatial dependencies. NearbyThe inflow of Region {a mathematical formula}r2 (shown in Fig. 1(a)) is affected by outflows of nearby regions (like {a mathematical formula}r1). Likewise, the outflow of {a mathematical formula}r2 would affect inflows of other regions (e.g. {a mathematical formula}r3). The inflow of region {a mathematical formula}r2 would affect its own outflow as well.DistantThe flows can be affected by that of distant regions. For instance, people who lives far away from the office area always go to work by metro or highway, implying that the outflows of distant regions directly affect the inflow of the office area.
      </list-item>
      <list-item label="2.">
       Morning rush hours may gradually happen later as winter comes. When the temperature gradually drops and the sun rises later in the day, people get up later and later.
      </list-item>
      <list-item label="3.">
       External influence. Some external factors, such as weather conditions and events may change the flow of crowds tremendously in different regions of a city. For example, a thunderstorm affects the traffic speed on roads and further changes the flows of regions.
      </list-item>
     </list>
     <paragraph>
      To tackle above mentioned challenges, we here explore DNNs for spatio-temporal data, and propose a deep spatio-temporal residual network (ST-ResNet) to collectively predict inflow and outflow of crowds in every region. Our contributions are five-fold:
     </paragraph>
     <list>
      <list-item label="•">
       ST-ResNet employs convolution-based residual networks to model both nearby and distant spatial dependencies between any two regions in a city, while ensuring the model's prediction accuracy is not comprised by the deep structure of the neural network.
      </list-item>
      <list-item label="•">
       We summarize the temporal properties of crowd flows into three categories, consisting of temporal closeness, period, and trend. ST-ResNet uses three different residual networks to model these properties, respectively.
      </list-item>
      <list-item label="•">
       ST-ResNet dynamically aggregates the output of the three aforementioned networks, assigning different weights to different branches and regions. The aggregation is further combined with external factors (e.g. weather).
      </list-item>
      <list-item label="•">
       We evaluate our approach using Beijing taxicabs' trajectories and meteorological data, and NYC bike trajectory data. The results demonstrate the advantages of our approach compared with 9 baselines.
      </list-item>
      <list-item label="•">
       We develop a real-time crowd flow monitoring and forecasting system using ST-ResNet. And our solution is based on the Cloud and GPU servers, providing powerful and flexible computational environments.
      </list-item>
     </list>
     <paragraph>
      The rest of this paper is organized as follows. In Section 2, we formally describe the crowd flow prediction problem. Section 3 describes the proposed deep spatio-temporal residual networks for predicting crowd flows. Section 4 overviews the real-time crowd flow forecasting system based on ST-ResNet and Microsoft Azure Cloud. We present the evaluation in Section 5 and summarized the related work in Section 6.
     </paragraph>
     <paragraph>
      The differences between this paper and our earlier work [1] are four aspects. First, we have deployed a cloud-based system that continuously forecasts the flow of taxicabs in each and every region of Guiyang City in China, showcasing the capability of ST-ResNet in handling real-world problems. The implementation of the cloud-based system is also introduced in Section 4 of this paper. Second, we extend ST-ResNet from a one-step ahead prediction to a multi-step ahead prediction, enabling the prediction of crowd flows over a farther future time (Section 3.4). Third, we conduct more comprehensive experiments on crowd flow prediction, showcasing the effectiveness and robustness of ST-ResNet: i) comparing our method with more advanced baselines (e.g. three different variants of recurrent neural networks) (Section 5.2); ii) testing more network architectures for ST-ResNet (Section 5.3); iii) adding the experiments of multi-step ahead prediction (Section 5.4); iv) discussing the performance of our method changing over different cloud resources (Section 5.5). Fourth, we have explored more related works (in Section 6), clarifying the differences and connections to the-state-of-the-art. This helps better position our research in the community.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminary
     </section-title>
     <paragraph label="Definition 1">
      We first briefly revisit the crowd flow prediction problem [3]. Region [3]There are many definitions of a location in terms of different granularities and semantic meanings. In this study, we partition a city into an {a mathematical formula}I×J grid map based on the longitude and latitude where a grid cell denotes a region, as shown in Fig. 2(a).
     </paragraph>
     <paragraph label="Definition 2">
      Inflow/outflow [3]Let {a mathematical formula}P be a collection of trajectories at the tth time interval. For a grid cell {a mathematical formula}(i,j) that lies at the ith row and the jth column, the inflow and outflow of the crowds at the time interval t are defined respectively as{a mathematical formula} where {a mathematical formula}Tr:g1→g2→⋯→g|Tr| is a trajectory in {a mathematical formula}P, and {a mathematical formula}gk is the geospatial coordinate; {a mathematical formula}gk∈(i,j) means the point {a mathematical formula}gk lies within grid {a mathematical formula}(i,j), and vice versa; {a mathematical formula}|⋅| denotes the cardinality of a set.
     </paragraph>
     <paragraph>
      At the tth time interval, inflow and outflow in all {a mathematical formula}I×J regions can be denoted as a tensor {a mathematical formula}Xt∈R2×I×J where {a mathematical formula}(Xt)0,i,j=xtin,i,j, {a mathematical formula}(Xt)1,i,j=xtout,i,j. The inflow matrix is shown in Fig. 2(b).
     </paragraph>
     <paragraph label="Problem 1">
      Formally, for a dynamical system over a spatial region represented by a {a mathematical formula}I×J grid map, there are 2 types of flows in each grid over time. Thus, the observation at any time can be represented by a tensor {a mathematical formula}X∈R2×I×J. Given the historical observations {a mathematical formula}{Xt|t=0,⋯,n−1}, predict {a mathematical formula}Xn.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Deep spatio-temporal residual networks
     </section-title>
     <paragraph>
      Recurrent neural networks (RNNs), like long-short term memory (LSTM), is capable of learning long-range temporal dependencies. Using RNNs, however, to model temporal period and trend, it needs very long input sequences (e.g. {a mathematical formula}length=1344),{sup:4} which makes the whole training process non-trivial (see Section 5.2 for empirical evaluation). According to the ST domain knowledge, we know that only a few previous keyframes influence the next keyframe. Therefore, we leverage temporal closeness, period, trend to select keyframes for modeling. Fig. 3 presents the architecture of ST-ResNet, which is comprised of four major components modeling temporal closeness, period, trend, and external influence, respectively.
     </paragraph>
     <paragraph>
      As illustrated in the top-right part of Fig. 3, we first turn inflow and outflow throughout a city at each time interval into a 2-channel image-like matrix respectively, using the approach introduced in Definitions 1 and 2. We then divide the time axis into three fragments, denoting recent time, near history and distant history. The 2-channel flow matrices of intervals in each time fragment are then fed into the first three components separately to model the aforementioned three temporal properties: closeness, period and trend, respectively. The first three components share the same network structure with a convolutional neural network followed by a Residual Unit sequence. Such structure captures the spatial dependency between nearby and distant regions. In the external component, we manually extract some features from external datasets, such as weather conditions and events, feeding them into a two-layer fully-connected neural network. The outputs of the first three components are fused as {a mathematical formula}XRes based on parameter matrices, which assign different weights to the results of different components in different regions. {a mathematical formula}XRes is further integrated with the output of the external component {a mathematical formula}XExt. Finally, the aggregation is mapped into {a mathematical formula}[−1,1] by a Tanh function, which yields a faster convergence than the standard logistic function in the process of back-propagation learning [5] (Section 5.3.5 gives the empirical evaluation and discussion).
     </paragraph>
     <section label="3.1">
      <section-title>
       Structures of the first three components
      </section-title>
      <paragraph>
       The first three components (i.e. closeness, period, trend) share the same network structure, which is composed of two sub-components: convolution and residual unit, as shown in Fig. 4.
      </paragraph>
      <paragraph>
       Convolution. A city usually has a very large size, containing many regions with different distances. Intuitively, the flow of crowds in nearby regions may affect each other, which can be effectively handled by the convolutional neural network (CNN) that has shown its powerful ability to hierarchically capture the spatial structural information [6]. In addition, subway systems and highways connect two locations with a far distance, leading to the dependency between distant regions. In order to capture the spatial dependency of any region, we need to design a CNN with many layers because one convolution only accounts for spatial near dependencies, limited by the size of their kernels. The same problem also has been found in the video sequence generating task where the input and output have the same resolution [7]. Several methods have been introduced to avoid the loss of resolution brought about by subsampling while preserving distant dependencies [8]. Being different from the classical CNN, we do not use subsampling, but only convolutions [9]. As shown in Fig. 4(a), there are three multiple levels of feature maps that are connected with a few convolutions. We find that a node in the high-level feature map depends on nine nodes of the middle-level feature map, those of which depend on all nodes in the lower-level feature map (i.e. input). It means one convolution naturally captures spatial near dependencies, and a stack of convolutions can further capture distant even citywide dependencies.
      </paragraph>
      <paragraph>
       The closeness component of Fig. 3 adopts a few 2-channel flows matrices of intervals in the recent time to model temporal closeness dependency. Let the recent fragment be {a mathematical formula}[Xt−lc,Xt−(lc−1),⋯,Xt−1], which is also known as the closeness dependent sequence. We first concatenate them along with the first axis (i.e. time interval) as one tensor {a mathematical formula}Xc(0)∈R2lc×I×J, which is followed by a convolution (i.e. Conv1 shown in Fig. 3) as:{a mathematical formula} where ⁎ denotes the convolution in a convolutional operator; f is an activation function, e.g. the rectifier {a mathematical formula}f(z):=max⁡(0,z)[10]; {a mathematical formula}Wc(1),bc(1) are the learnable parameters in the first layer.
      </paragraph>
      <paragraph>
       The classical convolution has smaller output size than input size, namely, narrow convolution, as shown in Fig. 5(a). Assume that the input size is {a mathematical formula}5×5 and the filter size is {a mathematical formula}3×3 with stride 1, the output size is {a mathematical formula}3×3 if using narrow convolution. In our task, the final output size should be same as the size of the input (i.e. {a mathematical formula}I×J). For this goal, we employ a special type of convolution, i.e. same convolution (see Fig. 5(b)), which allows a filter to go outside the border of an input, padding each area outside the border with a zero.
      </paragraph>
      <paragraph>
       Residual unit. It is hard to train very deep convolutional networks though the well-known activation function (e.g. ReLU) and regularization techniques are applied [11], [10], [12]. On the other hand, we still need a very deep network to capture very large citywide dependencies. For a typical crowd flow data, assume that the input size is {a mathematical formula}32×32, and the kernel size of convolution is fixed to {a mathematical formula}3×3, if we want to model citywide dependencies (i.e. each node in high-level layer depends on all nodes of the input), it needs more than 15 consecutive convolutional layers. To address this issue, we employ residual learning [13] in our model, which have been demonstrated to be very effective for training super deep neural networks of over 1000 layers.
      </paragraph>
      <paragraph>
       In our ST-ResNet (see Fig. 3), we stack L residual units upon Conv1 as follows,{a mathematical formula} where {a mathematical formula}F is the residual function (i.e. two combinations of “ReLU + Convolution”, see Fig. 4(b)), and {a mathematical formula}θ(l) includes all learnable parameters in the lth residual unit. We also attempt Batch Normalization (BN) [11] that is added before ReLU. On top of the Lth residual unit, we append a convolutional layer (i.e. Conv2 shown in Fig. 3). With 2 convolutions and L residual units, the output of the closeness component of Fig. 3 is {a mathematical formula}Xc(L+2).
      </paragraph>
      <paragraph>
       Likewise, using the above operations, we can construct the period and trend components of Fig. 3. Assume that there are {a mathematical formula}lp time intervals from the period fragment and the period is p. Therefore, the period dependent sequence is {a mathematical formula}[Xt−lp⋅p,Xt−(lp−1)⋅p,⋯,Xt−p]. With the convolutional operation and L residual units like in Eqs. (1) and (2), the output of the period component is {a mathematical formula}Xp(L+2). Meanwhile, the output of the trend component is {a mathematical formula}Xq(L+2) with the input {a mathematical formula}[Xt−lq⋅q,Xt−(lq−1)⋅q,⋯,Xt−q] where {a mathematical formula}lq is the length of the trend dependent sequence and q is the trend span. Note that p and q are actually two different types of periods. In the detailed implementation, p is equal to one-day that describes daily periodicity, and q is equal to one-week that reveals the weekly trend.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       The structure of the external component
      </section-title>
      <paragraph>
       Traffic flows can be affected by many complex external factors, such as weather and events. Fig. 6(a) shows that crowd flows during holidays (Chinese Spring Festival) can be significantly different from the flows during normal days. Fig. 6(b) shows that heavy rain sharply reduces the crowd flows at Office Area compared to the same day of the latter week. Let {a mathematical formula}Et be the feature vector that represents these external factors at predicted time interval t. In our implementation, we mainly consider weather, holiday event, and metadata (e.g. DayOfWeek, Weekday/Weekend). The details are introduced in Table 2. To predict flows at time interval t, the holiday event and metadata can be directly obtained. However, the weather at future time interval t is unknown. Instead, one can use the forecasting weather at time interval t or the approximate weather at time interval {a mathematical formula}t−1. Formally, we stack two fully-connected layers upon {a mathematical formula}Et, the first layer can be viewed as an embedding layer for each sub-factor followed by an activation. The second layer is used to map low to high dimensions that have the same shape as {a mathematical formula}Xt. The output of the external component of Fig. 3 is denoted as {a mathematical formula}XExt with the parameters {a mathematical formula}θExt.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Fusion
      </section-title>
      <paragraph>
       In this section, we discuss how to fuse four components of Fig. 3. We firstly fuse the closeness, period, and trend components with a parametric-matrix-based fusion method, which is then further combined with the external component.
      </paragraph>
      <paragraph>
       Figs. 7(a) and (d) show the ratio curves using Beijing trajectory data presented in Table 2 where x-axis is time gap between two time intervals and y-axis is the average ratio value between arbitrary two inflows that have the same time gap. The curves from two different regions all show an empirical temporal correlation in time series, namely, inflows of recent time intervals are more relevant than ones of distant time intervals, which implies temporal closeness. The two curves have different shapes, which demonstrates that different regions may have different characteristics of closeness. Figs. 7(b) and (e) depict inflows at all time intervals of 7 days. We can see the obvious daily periodicity in both regions. In Office Area, the peak values on weekdays are much higher than ones on weekends. Residential Area has similar peak values for both weekdays and weekends. Figs. 7(c) and (f) describe inflows at a certain time interval (9:00pm–9:30pm) of Tuesday from March 2015 and June 2015. As time goes by, the inflow progressively decreases in Office Area, and increases in Residential Area. It shows the different trends in different regions. In summary, inflows of two regions are all affected by closeness, period, and trend, but the degrees of influence may be very different. We also find the same properties in other regions as well as their outflows.
      </paragraph>
      <paragraph>
       Above all, the different regions are all affected by closeness, period and trend, but the degrees of influence may be different. Inspired by these observations, we propose a parametric-matrix-based fusion method.
      </paragraph>
      <paragraph>
       Parametric-matrix-based fusion. We fuse the first three components (i.e. closeness, period, trend) of Fig. 3 as follows{a mathematical formula} or, equivalently,{a mathematical formula} where ∘ is Hadamard product (i.e. element-wise multiplication), {a mathematical formula}wck,i,j∈Wc, {a mathematical formula}wpk,i,j∈Wp and {a mathematical formula}wqk,i,j∈Wq are the learnable parameters that adjust the degrees affected by closeness, period and trend, respectively. {a mathematical formula}xResk,i,j,xck,i,j,xpk,i,j, and {a mathematical formula}xqk,i,j are respectively an entry of {a mathematical formula}XRes,Xc(L+2),Xp(L+2), and {a mathematical formula}Xq(L+2).
      </paragraph>
      <paragraph>
       Fusing the external component. We here directly merge the output of the first three components with that of the external component, as shown in Fig. 3. Finally, the predicted value at the tth time interval, denoted by {a mathematical formula}Xˆt, is defined as{a mathematical formula} where tanh is a hyperbolic tangent that ensures the output values are between −1 and 1.
      </paragraph>
      <paragraph>
       Our ST-ResNet can be trained to predict {a mathematical formula}Xt from three sequences of flow matrices and external factor features by minimizing mean squared error between the predicted flow matrix and the true flow matrix:{a mathematical formula} where θ are all learnable parameters in the ST-ResNet.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Algorithms and optimization
      </section-title>
      <paragraph>
       Algorithm 1 outlines the ST-ResNet training process. We first construct the training instances from the original sequence data (lines 1–6). Then, ST-ResNet is trained via backpropagation and Adam [14] (lines 7–11).
      </paragraph>
      <paragraph>
       After training, the learned ST-ResNet model {a mathematical formula}M is obtained for the single- or multi-step look-ahead prediction. the process of which is summarized in Algorithm 2. Some types of external features (i.e. weather) used here are different from that in Algorithm 1. In the training process, we use the true weather data, which is replaced by the forecasted weather data in Algorithm 2.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Discussion on different approaches to construct inputs
      </section-title>
      <paragraph>
       We here present two different approaches to construct inputs of closeness, period, and trend components of Fig. 3. Fig. 8 gives an illustration. Let period (p) and trend span (q) be 1 day and 1 week, respectively. According to three temporal properties (i.e. closeness, period, trend), the original constructing approach (Fig. 8(a)) selects the following key frames:
      </paragraph>
      <list>
       <list-item label="•">
        dependent inputs of closeness component: {a mathematical formula}[Xt−lc,Xt−(lc−1),⋯,Xt−1].
       </list-item>
       <list-item label="•">
        dependent inputs of period component: {a mathematical formula}[Xt−lp⋅p,Xt−(lp−1)⋅p,⋯,Xt−p].
       </list-item>
       <list-item label="•">
        dependent inputs of trend component: {a mathematical formula}[Xt−lq⋅q,Xt−(lq−1)⋅q,⋯,Xt−q].
       </list-item>
      </list>
      <paragraph>
       Based on the original approach, we here introduce two approaches (AVG1 and AVG2) that employ averaging the historical frames, in which dependent inputs of closeness component are same with that of the original approach.
      </paragraph>
      <paragraph>
       AVG1 (Fig. 8(b)): averaging respectively dependent inputs of period and trend components of the original approach as new dependent inputs of period and trend components, showing below:
      </paragraph>
      <list>
       <list-item label="•">
        dependent input of period component of AVG1: {a mathematical formula}1lp∑i=1lpXt−i⋅p.
       </list-item>
       <list-item label="•">
        dependent input of trend component of AVG1: {a mathematical formula}1lq∑i=1lqXt−i⋅q.
       </list-item>
      </list>
      <paragraph>
       Compared to the original approach, AVG1 has the same raw inputs, but requires a model that has fewer trainable parameters because its period and trend components both has 1 frame.
      </paragraph>
      <paragraph>
       AVG2: averaging the frames around same time intervals in the original approach, producing the same number frames as the original approach (see Fig. 8(c) for example). Formally, their inputs are below:
      </paragraph>
      <list>
       <list-item label="•">
        dependent inputs of period component of AVG2: {a mathematical formula}[X‾t−lp⋅p,X‾t−(lp−1)⋅p,⋯,X‾t−p], where {a mathematical formula}X‾t−j⋅p=13(Xt−j⋅p−1+Xt−j⋅p+Xt−j⋅p+1), {a mathematical formula}j=1,⋯lp.
       </list-item>
       <list-item label="•">
        dependent inputs of trend component AVG2: {a mathematical formula}[X‾t−lq⋅q,X‾t−(lq−1)⋅q,⋯,X‾t−q]. {a mathematical formula}∀j∈{1,⋯,lq}, {a mathematical formula}X‾t−j⋅q=15∑Xk∈XjweekdaysXk if {a mathematical formula}Xt is in weekday or {a mathematical formula}X‾t−j⋅q=12∑Xk∈XjweekendXk otherwise, where {a mathematical formula}Xjweekdays denotes 5 weekdays and {a mathematical formula}Xjweekend denotes weekend in the previous jth trend span.
       </list-item>
      </list>
      <paragraph>
       Compared to the original approach, AVG2 has the same trainable parameters, but capable of capturing more raw frames.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      System architecture
     </section-title>
     <paragraph>
      Fig. 9 presents the framework of our system, which consists of three major parts: local GPU servers, and the Cloud, and users (e.g. website and QR Code), resulting in offline and online data flows, respectively. The local GPU servers store historical observations, such as taxi trajectories, meteorological data. The Cloud receive real-time data, including real-time traffic data (e.g. trajectories) within a time interval as well as meteorological data. The users access the inflow/outflow data, displaying them on websites or smart phone via scanning QR code.
     </paragraph>
     <section label="4.1">
      <section-title>
       The cloud
      </section-title>
      <paragraph>
       The cloud continuously receives GPS trajectories of taxicabs and crawls meteorological data, and then caches them into a Redis.{sup:5} A virtual machine (VM) (or VMs) on the Cloud pulls these data from the Redis, and then computes crowd flows according to GPS trajectories for each and every region of a city. Meanwhile, the VM extracts the features from meteorological data, event data and others. Afterwards, the VM stores the crowd flow data and extracted features into the storage (a part of the VM). To save the resource on the cloud (more storages need more expensive payment), we only store the crowd flow data and features in past two days. Historical data can be moved to local servers periodically.
      </paragraph>
      <paragraph>
       We use Azure platform as a service (PaaS). Table 1 details the Azure{sup:6} resources for our system. We employ a VM,{sup:7} called A2 standard in Azure, that has 2 cores and 3.5 GB memory for forecasting the crowd flows in near future. The website and web service share a App Service, given the potential heavy accesses by many users. As the historical data is stored in local servers, a 6 GB Redis Cache is enough for caching the real-time trajectories in past half-hour, crowd flow data and extracted features in past two days, and inferred results.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Local GPU servers
      </section-title>
      <paragraph>
       Although all the jobs can be done on the cloud, GPU services on the Cloud is not supported in some areas (e.g. China). On the other hand, we need to pay for other cloud services, like storages and I/O bandwidths. Saving unnecessary cost is vital for a research prototype. In addition, migrating massive data from local servers up to the cloud is time-consuming given the limited network bandwidth. For instance, the historical trajectories can be hundreds of Gigabytes, even Terabytes, leading to a very long time for copying the data from local servers to the cloud.
      </paragraph>
      <paragraph>
       Therefore, we employ a hybrid framework that combines local GPU servers with the cloud. Local GPU servers mainly handle the offline training (learning), including three tasks:
      </paragraph>
      <list>
       <list-item label="•">
        Converting trajectories into inflow/outflow: we first use the massive historical trajectories and employ a calculation module to get crowd flow data, then store them in local.
       </list-item>
       <list-item label="•">
        Extracting features from external data: we fist collect external data (e.g. weather, holiday events) from different data sources and fit them into a feature extraction module to get continuous or discrete features, and then store them in local.
       </list-item>
       <list-item label="•">
        Training model: we use above generated crowd flows and external features to train a predictive model via our proposed ST-ResNet, and then upload the learned model to the cloud. Note that as the dynamic crowd flows and features are stored in the Storage (Azure), we sync up the online data to local servers before each training processing. In this way, we are agile to try new ideas (e.g. re-train the model) while greatly reducing expense for a research prototype.
       </list-item>
      </list>
     </section>
     <section label="4.3">
      <section-title>
       User interface
      </section-title>
      <paragraph>
       Fig. 10(a) presents the website of UrbanFlow [15], where each grid on the map stands for a region and the number associated with it denotes its inflow or outflow of crowds. The user can view inflow or outflow via the top-right button named “InFlow/OutFlow”. The smaller the number is, the sparser the crowd flow. The color of each grid is determined in accordance with its crowd flows, e.g. “red” means “dense” crowd flow and “green” means “sparse” crowd flow. The top-right corner of the website shows the buttons which can switch between different types of flows. A user can select any grid (representing a region) on the website and click it to see the region's detailed flows, as shown in Fig. 10(b) where blue, black, and green curves indicate flows of yesterday, past, and future times at today, respectively. The bottom of the website shows a few sequential timestamps. The heatmap at a certain timestamp will be shown in the website when a user clicks the associated timestamp. Intuitively, the user can watch the movie-style heatmaps (Fig. 10(c)) by clicking “play button” at the bottom-left of Fig. 10(a). At present, we apply UrbanFlow to the area of Guiyang City, China.{sup:8}
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      In this section, we evaluate our ST-ResNet on two types of crowd flows in Beijing and NYC against 9 baselines.
     </paragraph>
     <section label="5.1">
      <section-title>
       Settings
      </section-title>
      <paragraph>
       Datasets. We use two different sets of data as shown in Table 2. Each dataset contains two sub-datasets: trajectories and weather, as detailed as follows.
      </paragraph>
      <list>
       <list-item label="•">
        TaxiBJ: Trajectory data is the taxicab GPS data and meteorology data in Beijing from four time intervals: 1st Jul. 2013–30th Otc. 2013, 1st Mar. 2014–30th Jun. 2014, 1st Mar. 2015–30th Jun. 2015, 1st Nov. 2015–10th Apr. 2016. Using Definition 2, we obtain two types of crowd flows. We choose data from the last four weeks as the testing data, and all data before that as training data.
       </list-item>
       <list-item label="•">
        BikeNYC: Trajectory data is taken from the NYC Bike system in 2014, from Apr. 1st to Sept. 30th. Trip data includes: trip duration, starting and ending station IDs, and start and end times. Among the data, the last 10 days are chosen as testing data, and the others as training data.
       </list-item>
      </list>
      <paragraph>
       Baselines. The baselines and our models are outlined as follows.
      </paragraph>
      <list>
       <list-item label="•">
        HA: We predict inflow and outflow of crowds by the average value of historical inflow and outflow in the corresponding periods, e.g. 9:00am–9:30am on Tuesday, its corresponding periods are all historical time intervals from 9:00am to 9:30am on all historical Tuesdays.
       </list-item>
       <list-item label="•">
        ARIMA: Auto-Regressive Integrated Moving Average (ARIMA) is a well-known model for understanding and predicting future values in a time series.
       </list-item>
       <list-item label="•">
        SARIMA: Seasonal ARIMA. Beyond ARIMA, SARIMA also considers the seasonal terms, capable of both learning closeness and periodic dependencies.
       </list-item>
       <list-item label="•">
        VAR: Vector Auto-Regressive (VAR) is a more advanced spatio-temporal model, which can capture the pairwise relationships among all flows, and has heavy computational costs due to the large number of parameters.
       </list-item>
       <list-item label="•">
        ST-ANN: It first extracts spatial (nearby 8 regions' values) and temporal (8 previous time intervals) features, then fed into an artificial neural network.
       </list-item>
       <list-item label="•">
        DeepST[3]: a deep neural network (DNN)-based prediction model for spatio-temporal data, which shows state-of-the-art results on the crowd flow prediction.
       </list-item>
       <list-item label="•">
        RNN[37]: recurrent neural network (RNN), a deep learning model, which can capture temporal dependencies. Formally, RNN can train on sequences with the arbitrary length. In our experiment, we fix the length of input sequence as one of {a mathematical formula}{3,6,12,24,48,336}. Taking 48 as example, the dependent input sequence is just a one-day data if the interval time is equal to 30 minutes. Therefore, we have 6 RNN variants, including RNN-3, RNN-6, RNN-12, RNN-24, RNN-48, and RNN-336.
       </list-item>
       <list-item label="•">
        LSTM[16]: Long-short-term-memory network (LSTM), a special kind of RNN, capable of learning long-term temporal dependencies. Being same as the setting of RNN, we conduct the experiments on 6 LSTM variants, i.e. LSTM-3, LSTM-6, LSTM-12, LSTM-24, LSTM-48, and LSTM-336.
       </list-item>
       <list-item label="•">
        GRU[17]: Gated-recurrent-unit network, a new kind of RNN, can be used to capture long-term temporal dependencies. Being same as the setting of RNN, the following GRU variants are selected as the baselines: GRU-3, GRU-6, GRU-12, GRU-24, GRU-48, and GRU-336.
       </list-item>
       <list-item label="•">
        ST-ResNet: The model proposed in this paper. The number of residual units is set as 12 for the dataset TaxiBJ, and 4 for BikeNYC.
       </list-item>
       <list-item label="•">
        ST-ResNet-AVG1 and ST-ResNet-AVG2: two ST-ResNet variants with same setting, but different input constructing approaches (see Section 3.5)
       </list-item>
      </list>
      <paragraph>
       Table 3 shows characteristics of these baselines. LSTM and GRU models have the same characteristics as that of RNN. For example, the HA model implicitly capture daily period and weekly trend, but cannot capture spatial dependencies or external factors; VAR considers the relations between inflow and outflow within a region; ST-ANN leverage the flows nearby regions; RNN-336 have assess to daily period and weekly trends, but they are not explicit. Our ST-ResNet can capture all spatial and temporal dependencies as well as external factors.
      </paragraph>
      <paragraph>
       Preprocessing. In the output of the ST-ResNet, we use tanh as our final activation (see Eq. (5)), whose range is between −1 and 1. Here, we use the Min-Max normalization method to scale the data into the range {a mathematical formula}[−1,1]. In the evaluation, we re-scale the predicted value back to the normal values, compared with the groundtruth. For external factors, we use one-hot coding to transform metadata (i.e. DayOfWeek, Weekend/Weekday), holidays and weather conditions into binary vectors, and use Min-Max normalization to scale the Temperature and Wind speed into the range {a mathematical formula}[0,1].
      </paragraph>
      <paragraph>
       Hyperparameters. The learnable parameters are initialized using a uniform distribution with the default parameter in Keras [18]. The convolutions of Conv1 and all residual units use 64 filters of size {a mathematical formula}3×3, and Conv2 uses a convolution with 2 filters of size {a mathematical formula}3×3. For example, a 4-residual-unit of ST-ResNet consists of Conv1, 4 residual unit, and Conv2. See Table 4 for the details. The Adam [14] is used for optimization, and the batch size is 32. There are 5 extra hyperparameters in our ST-ResNet, of which p and q are empirically fixed to one-day and one-week, respectively. For lengths of the three dependent sequences, we set them as: {a mathematical formula}lc∈{1,2,3,4,5},lp∈{1,2,3,4},lq∈{1,2,3,4}. We select 90% of the training data for training each model, and the remaining 10% is chosen as the validation set, which is used to early-stop our training algorithm for each model based on the best validation score. Afterwards, we continue to train the model on the full training data for a fixed number of epochs (e.g. 10, 100 epochs).
      </paragraph>
      <paragraph>
       Evaluation metric: We measure our method by Root Mean Square Error (RMSE){sup:9} as{a mathematical formula} where x and {a mathematical formula}xˆ are the available ground truth and the corresponding predicted value, respectively; z is the number of all available ground truths.
      </paragraph>
      <paragraph>
       Experiments are mainly run on a GPU server, whose detailed information is shown in Table 5. The python libraries, including TensorFlow [19] and Keras [18], are used to build our models.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Evaluation of single-step ahead prediction
      </section-title>
      <paragraph>
       In this section, we evaluate the single-step ahead prediction, namely, predicting the crowd flows at time t using the historical observations. Table 6 shows the RMSE of all methods on both TaxiBJ and BikeNYC. Our ST-ResNet consistently and significantly outperforms all baselines. Specifically, the results on TaxiBJ demonstrates that ST-ResNet (with 12 residual units) is relatively 25% better than ARIMA, 36% better than SARIMA, 25% better than VAR, 12% better than ST-ANN, 6% better than DeepST, 36% to 66% better than RNN, 34% to 58% better than LSTM, 25% to 57% better than GRU. ST-ResNet-noExt is a degraded version of ST-ResNet that does not consider the external factors (e.g. meteorology data). We can see that ST-ResNet-noExt is slightly worse than ST-ResNet, pointing out external factors are always beneficial. DeepST exploits spatio-temporal CNNs and is clearly better than other baselines. While both ST-ANN and VAR use spatial/temporal information and relationships among flows, they are worse than DeepST because they only consider the near spatial information and recent temporal information. Among the temporal models, GRU and LSTM have similar RMSE, and outperform RNN in average because GRU and LSTM both can capture long-term temporal dependencies. However, GRU-336 and LSTM-336 have very bad performance as well as RNN-336, which demonstrates RNN-based models cannot capture very long-term dependencies (i.e. period and trend). Intuitively, we rank all of these models, as shown in Fig. 11(a).
      </paragraph>
      <paragraph>
       Being different from TaxiBJ, BikeNYC consists of two different types of crowd flows, including new-flow and end-flow [20]. We here adopt a total of 4-residual-unit ST-ResNet, and consider the metadata as external features like DeepST [3]. ST-ResNet has relatively from 15% up to 71% lower RMSE than these baselines, demonstrating that our proposed model has good generalization performance on other flow prediction tasks. Fig. 11(b) depicts the ranking of these models.
      </paragraph>
      <paragraph>
       For different input constructing approaches (AVG1 and AVG2 in Section 3.5), we observe ST-ResNet-AVG1 is worst in both datasets because it averages the period dependents and trend dependents, though the model complexity reduces, its error raises. ST-ResNet-AVG2 is worse than ST-ResNet in TaxiBJ but better in BikeNYC. The reason may be that TaxiBJ has some missing time intervals in the data, but there are no missing in BikeNYC, which means ST-ResNet has more training instances than ST-ResNet-AVG2 in the incomplete dataset.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Results of different ST-resnet variants
      </section-title>
      <paragraph>
       We here present the results of different ST-ResNet variants, including changing network configurations, network depth, and different components used.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Impact of different configurations
       </section-title>
       <paragraph>
        Fig. 12 shows the results of different configurations. The same hyper-parameters: {a mathematical formula}lc=3, {a mathematical formula}lp=1, {a mathematical formula}lq=1, number of residual unit = 12.
       </paragraph>
       <list>
        <list-item label="•">
         Effect of batch normalization (BN): We attempt to adopt BN into each residual unit, finding that the RMSE slightly improves in single-step ahead prediction, as shown in Fig. 12(a).
        </list-item>
        <list-item label="•">
         Effect of parametric-matrix-based fusion: We use a parametric-matrix-based fusion mechanism (see Eq. (3)) to fuse temporal closeness, period and trend components. Simply, one also can employ a straightforward method for fusing, i.e. {a mathematical formula}Xc(L+2)+Xp(L+2)+Xq(L+2). Fig. 12(b) shows that ours is better than the straightforward method, demonstrating the effectiveness of our proposed parametric-matrix-based fusion.
        </list-item>
        <list-item label="•">
         Internal structure of residual unit: The proposed residual unit includes 2 convolutions. We here test the performance different setting in the residual unit. From Fig. 12(c), we observe that the model using 2 convolutions is better than using 1 convolution.
        </list-item>
        <list-item label="•">
         True Weather vs. Forecast: Using the same network architecture, we here employ different weather data as the training data: true weather and forecasting. Fig. 12(d) shows the comparison of different weather, demonstrating that it is better to use true weather as the training data. The possible reason is that the weather forecasting provides a coarse-grained predicted values, namely, 6th, 12th, 18th, 24th hours in future.
        </list-item>
       </list>
      </section>
      <section label="5.3.2">
       <section-title>
        Impact of network depth
       </section-title>
       <paragraph>
        Fig. 13 presents the impact of network depth. As the network goes deeper (i.e. the number of residual units increases), the RMSE of the model first decreases and then increases, demonstrating that the deeper network often has a better result because it can capture not only near spatial dependence but also distant one. However, when the network is very deep (e.g. number of residual unit ≥14), training becomes more difficult and the possibility of overfitting becomes larger.
       </paragraph>
      </section>
      <section label="5.3.3">
       <section-title>
        Impact of filter size and number
       </section-title>
       <paragraph>
        The receptive field of a convolution is determined by the size of the filter used. We here change the size of the filter from {a mathematical formula}2×2 to {a mathematical formula}5×5. Fig. 14(a) shows that the larger filter size has the lower RMSE, demonstrating larger receptive field has better ability to model spatial dependency. From Fig. 14(b), we can observe that more filters better result.
       </paragraph>
      </section>
      <section label="5.3.4">
       <section-title>
        Impact of temporal closeness, period, trend
       </section-title>
       <paragraph>
        We here verify the impact of temporal closeness,period, trend components on TaxiBJ, as shown in Fig. 15. Fig. 15(a) shows the effect of temporal closeness where we fix {a mathematical formula}lp=1 and {a mathematical formula}lq=1 but change {a mathematical formula}lc. For example, {a mathematical formula}lc=0 means that we does not employ the closeness component, resulting in a very bad result: {a mathematical formula}33.47±0.34. We can observe that RMSE first decreases and then increases as the length of closeness increases, indicating that {a mathematical formula}lc=4 has the best performance. Fig. 15(b) depicts the effect of period where we set {a mathematical formula}lc as 3 and {a mathematical formula}lq as 1 but change {a mathematical formula}lp. We can see that {a mathematical formula}lp=1 has the best RMSE. The model without the period component (i.e. {a mathematical formula}lp=0) is worse than the model with {a mathematical formula}lp=2,3, but better than the {a mathematical formula}lp=4 model, meaning that short-range periods are always beneficial, and long-range periods may be hard to model or not helpful. Fig. 15(c) presents the effect of trend where {a mathematical formula}lc and {a mathematical formula}lp are fixed to 3 and 2, respectively. We change {a mathematical formula}lq from 0 to 3. The curve points that the {a mathematical formula}lq=1 model outperforms others. Similar to period, it is better to employ the trend component, but long-range trend may be not easy to capture or useless.
       </paragraph>
       <paragraph>
        To better understand the temporal closeness, period and trend, we here visualize the parameters of the parametric-matrix-based fusion layer, which is capable of learning different temporal influence degrees for each region of a city, as shown in Fig. 16. Each element in each sub-figure denotes a learned parameter of a certain region that reflects the influence degree by closeness, period, or trend. We here set a threshold (e.g. 0.3) to see the temporal properties of the whole city. Given a fixed threshold 0.3, we observe that the ratio (the number of regions whose parametric value is less than 0.3) of the closeness is 0, demonstrating all of regions in the city have a more or less closeness. The ratio of the period shows that there are 9% regions only have very weak periodic patterns. Likewise, Fig. 16(c) depicts that 7% regions do not have temporal trend. From Fig. 16(a), we find that the closeness of some main-road-related regions (red dashed frame) is not obvious. One reason is that the crowd flows in these regions can be predicted using period or/and trend, adding slight closeness.
       </paragraph>
      </section>
      <section label="5.3.5">
       <section-title>
        Impact of activation function of output layer
       </section-title>
       <paragraph>
        In these experiments, we investigate the impact of activation functions (sigmoid and tanh) in the output layer. Since the range of the sigmoid function is {a mathematical formula}[0,1], we have to scale the crowd flow data into {a mathematical formula}[0,1]. We run each model 5 times, and train for 50 epochs (without early stopping) using Adam [14]. Other hyperparameters are set as following: 12 (residual units), 32 (batch size), and 0.0002 (learning rate). Results are summarized in Fig. 17. We observe that ST-ResNet with tanh activation has faster convergence, yielding a better result (rmse: {a mathematical formula}16.80±0.46) on the test set with fixed number of epochs.
       </paragraph>
       <paragraph>
        Possible reason: the outputs of the sigmod functions are not zero-centered, and the corresponding inputs of the whole networks are also not zero-centered, which is undesirable since all layers{sup:10} in the network would be receiving data that is not zero-centered. It has implications on the dynamics during gradient descent, because if the data coming into a neuron is always positive then the gradient on weights during back-propagation become either all positive, or all negative. Undesirable zig-zagging dynamics could happen in the gradient updates for the weights.
       </paragraph>
      </section>
     </section>
     <section label="5.4">
      <section-title>
       Evaluation of multi-step ahead prediction
      </section-title>
      <paragraph>
       According to Algorithm 2, we can use historical observations and the recent predicted ones to forecast the crowd flows in subsequent time intervals which is referred to multi-step ahead prediction. Fig. 18 shows multi-step prediction results of 12 different models on TaxiBJ. Among these models, ST-ResNet-BN and ST-ResNet-noExt are variants of ST-ResNet (12 residual units), where ST-ResNet-BN employs BN. LSTM-3, LSTM-6 and LSTM-12 are three variants of LSTM (see details in Section 5.1). From the results of 4-step ahead prediction,{sup:11} we find our ST-ResNet performs best though ST-ResNet-BN is better in the single-step ahead prediction, showing in Fig. 12(a). We observe that LSTM-12 is better than ST-ResNet when the number of the look-ahead steps is greater than 8. The reason may be that LSTM-12 uses the past 12 observations to predict, however, our ST-ResNet only takes past recent 3 observations as the input of the closeness component.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Efficiency and resources
      </section-title>
      <paragraph>
       We test the efficiency on two different virtual machines in the cloud (i.e. Microsoft Azure), as shown in Table 7. As introducing in Section 4.1, there are four main steps to predict crowd flows for each region of a city: (1) pulling trajectories from Redis; (2) converting trajectories into crowd flow data; (3) predicting the crowd flows in near future; (4) pushing results into Redis. We also report the time consumed by above four steps. Totally, A2 standard VM finishes the whole predicting process in 18.56 seconds. It takes 10.93 seconds on D4 standard VM, which is more powerful but expensive. One can choose different Cloud resources according to the requirements and budgets.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Related work
     </section-title>
     <section label="6.1">
      <section-title>
       Crowd flow prediction
      </section-title>
      <paragraph>
       There are some previously published works on predicting an individual's movement based on their location history [21], [22]. They mainly forecast millions, even billions, of individuals' mobility traces rather than the aggregated crowd flows in a region. Such a task may require huge computational resources, and it is not always necessary for the application scenario of public safety. Some other researchers aim to predict travel speed and traffic volume on the road [23], [24], [25]. Most of them are predicting single or multiple road segments, rather than citywide ones [25], [26]. Recently, researchers have started to focus on city-scale traffic flow prediction [20], [27]. Both work are different from ours where the proposed methods naturally focus on the individual region not the city, and they do not partition the city using a grid-based method which needs a more complex method to find irregular regions first.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Classical models for time series prediction
      </section-title>
      <paragraph>
       Predicting the flows of crowds can be viewed as a type of time series prediction problem. There are several conventional linear models for such problem. The historical average model is portable, which simply uses the average value of historical time series to predict future value of time series. However, the model unable to respond to dynamic changes, such as incidents [28]. The Auto-Regressive Integrated Moving Average (ARIMA) model assumes that the future value of time series is a linear combination of previous values and residuals, furthermore, in order to obtain stationarity, the nonstationary time series should be differenced before analysis [29]. ARIMA is not suite for time series with missing data, since they relying on uninterrupted time series, and data filling technique might be problematic as the complexity of the situation increase [30]. The additional seasonal difference is often applied to seasonal time series to obtain stationarity before ARIMA being used, which is called SARIMA. The disadvantage of SARIMA is time consuming [30]. The Vector Autoregressive (VAR) models capture the linear inter dependencies among interrelated time series [31]. However, the correlation between predicted values and residuals is neglected.
      </paragraph>
      <paragraph>
       Being different from the above linear models, the artificial neural network (ANN) model is a nonlinear model and commonly used in time series prediction [32], [33], [34]. ANNs have excellent nonlinear modeling ability, but not enough for linear modeling ability [35].
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Deep neural networks
      </section-title>
      <paragraph>
       Neural networks and deep learning [4], [36], [37] have gained numerous success in the fields such as compute vision [10], [38], speech recognition [39], [40], and natural language processing [41]. For example, convolutional neural networks won the ImageNet [42] competition since 2012, and help AlphaGo [43] beat Go human champion.{sup:12} Recurrent neural networks (RNNs) have been used successfully for sequence learning tasks [44]. The incorporation of long short-term memory (LSTM) [16] or gated recurrent unit (GRU) [17] enables RNNs to learn long-term temporal dependency. However, both kinds of neural networks can only capture spatial or temporal dependencies. Recently, researchers combined above networks and proposed a convolutional LSTM network [45] that learns spatial and temporal dependencies simultaneously. Such a network cannot model very long-range temporal dependencies (e.g. period and trend), and training becomes more difficult as depth increases.
      </paragraph>
      <paragraph>
       In our previous work [3], a general prediction model based on DNNs was proposed for spatio-temporal data. In this paper, to model a specific spatio-temporal prediction (i.e. citywide crowd flows) effectively, we mainly propose employing the residual learning and a parametric-matrix-based fusion mechanism. A survey on data fusion methodologies can be found at [46].
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Urban computing
      </section-title>
      <paragraph>
       Urban computing [2], has emerged as a new research area, which aims to tackle urban challenges (e.g. traffic congestion, energy consumption, and pollution) by using the data that has been generated in cities (e.g. geographical data, traffic flow, and human mobility). A branch of research also partitions a city into grids, and then studies the traffic flow in each region of the city, such as predicting urban air quality [47], [48], detecting anomalous traffic patterns [49], inferring missing air quality [50], forecasting of spatio-temporal data [3]. Besides, some researchers started to research on deep learning methods for urban computing applications. For example, Song et al. proposed a recurrent-neural-network-based model to predict the person's future movement [51]. Chen et al. proposes a deep learning model to understand how human mobility will affect traffic accident risk [52]. Both work are very different from ours in terms of approach and problem setting. To the best of our knowledge, in the field of urban computing, end-to-end deep learning for forecasting citywide crowd flows has never been done.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>