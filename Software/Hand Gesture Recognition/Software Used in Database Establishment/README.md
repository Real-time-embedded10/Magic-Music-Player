Software Used in Database Establishment
--
The aim of this folder is to find a practical process methond (for example, what parameters are better for segmentation, which features are useful for classification, etc.) that can be used in the final real-time program. <br>
 <br>
The process of gesture recognition can be categorized into four stages, namely data acquisition, pre-processing, features extraction and classification. The input data of the system is acquired from accelerometer sensor (MPU6050), and then pre-processed to find the Region of Interest (ROI), where hand gesture is, for further processing. This stage is also called hand gesture segmentation. Features extraction is a stage whereby using some statistical features from time domain to complete the transformation of segmented gesture data into sets of feature vector. Afterwards, for classification, machine learning is used to model the selected features, mapping them to a specific hand gesture.<br>
 <br>
Detailed instructions for each stage and related codes are in each folder.<br>

