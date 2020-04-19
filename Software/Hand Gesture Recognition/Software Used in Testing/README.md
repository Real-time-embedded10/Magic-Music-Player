Software Used in Testing
--
The purpose is to test the work in Database Establishment.<br> 
<br> 
In file `Cross_Validation1.py`, a method named Cross Validation is applied to test whether our feature matrix extracted is useful. To train the machine learning model, 160 samples of each gesture, totaling of 960 * 21 features, are selected randomly to input. The remaining 120 samples (20 samples per gesture) are used to test the trained model.<br> 
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Testing/Flowchart%20of%20Cross%20Validation%201.jpg)<br>
<br> 
File `Cross_Validation2.py` is used to test whether weight gradient matrix and bias gradient matrix calculated are useful. The result demonstrates that weight gradient matrix and bias gradient matrix can work well.<br> 
![](https://github.com/Real-time-embedded10/Magic-Music-Player/blob/master/Software/Hand%20Gesture%20Recognition/Software%20Used%20in%20Testing/Test%20Result%20of%20Cross%20Validation%202.jpg)<br>
