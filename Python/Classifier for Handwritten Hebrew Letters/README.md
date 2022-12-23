# Authors' Contact Information
* Roni Jack Vituli - 315369967
* Daniel Dahan - 208906909

# Description

This program is a k-NN classifier for classifying images of characters from the Hindi Handwritten Digits dataset. 
It first preprocesses the images by converting them to greyscale, adding white padding as needed, resizing them to 32x32, and binarizing them.
It then splits the images into training, validation, and testing sets, and uses the training set to train a k-NN classifier using various values of k. 
The classifier is then evaluated on the validation set to find the optimal value of k, and the results are reported in a file called "results.txt". 
Finally, the classifier is used to classify the images in the testing set and the results are reported in a file called "confusion.matrix.csv".


# Environment
OS: This program was developed and tested on a machine running Windows 10 and Python 3.8. It requires the following libraries:
* opencv-python
* numpy
* scikit-learn

#How to Run the Program
To run this program, you will need to have Python and the above libraries installed. Then, follow these steps:

1. Open a terminal or command prompt.
2. Navigate to the directory where the program and dataset are located.
3. Run the following command:
```bash 
   python knn_classifier.py path/to/hhd_dataset
```
Replace path/to/hhd_dataset with the actual path to the Hindi Handwritten Digits dataset on your machine.
The program will then preprocess the images, split them into training, validation, and testing sets, train and evaluate the k-NN classifier, and report the results in the "results.txt" and "confusion.matrix.csv" files.

