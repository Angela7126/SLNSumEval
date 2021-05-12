<html>
<head>
<meta name="TextLength" content="SENT_NUM:9, WORD_NUM:231">
</head>
<body bgcolor="white">
<a href="#0" id="0">Forecasting the flow of crowds is of great importance to traffic management and public safety, and very challenging as it is affected by many complex factors, including spatial dependencies (nearby and distant), temporal dependencies (closeness, period, trend), and external conditions (e.g. weather and events).</a>
<a href="#1" id="1">We propose a deep-learning-based approach, called ST-ResNet, to collectively forecast two types of crowd flows (i.e. inflow and outflow) in each and every region of a city.</a>
<a href="#2" id="2">We design an end-to-end structure of ST-ResNet based on unique properties of spatio-temporal data.</a>
<a href="#3" id="3">More specifically, we employ the residual neural network framework to model the temporal closeness, period, and trend properties of crowd traffic.</a>
<a href="#4" id="4">For each property, we design a branch of residual convolutional units, each of which models the spatial properties of crowd traffic.</a>
<a href="#5" id="5">ST-ResNet learns to dynamically aggregate the output of the three residual neural networks based on data, assigning different weights to different branches and regions.</a>
<a href="#6" id="6">The aggregation is further combined with external factors, such as weather and day of the week, to predict the final traffic of crowds in each and every region.</a>
<a href="#7" id="7">We have developed a real-time system based on Microsoft Azure Cloud, called UrbanFlow, providing the crowd flow monitoring and forecasting in Guiyang City of China.</a>
<a href="#8" id="8">In addition, we present an extensive experimental evaluation using two types of crowd flows in Beijing and New York City (NYC), where ST-ResNet outperforms nine well-known baselines.</a>
</body>
</html>