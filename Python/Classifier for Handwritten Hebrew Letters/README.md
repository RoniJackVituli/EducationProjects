# Authors' Contact Information
* Roni Jack Vituli 

# Description

This program is a k-NN classifier for classifying images of characters from the Hindi Handwritten Digits dataset. 
It first preprocesses the images by converting them to greyscale, adding white padding as needed, resizing them to 32x32, and binarizing them.
It then splits the images into training, validation, and testing sets, and uses the training set to train a k-NN classifier using various values of k. 
The classifier is then evaluated on the validation set to find the optimal value of k, and the results are reported in a file called "results.txt". 
Finally, the classifier is used to classify the images in the testing set and the results are reported in a file called "confusion.matrix.csv".


# Environment
This program was developed and tested on a Windows 10 operating system. It requires Python 3.x and the following libraries:
* OpenCV
* Scikit-learn


To install the required libraries, you can use the following command:

```sh
pip install opencv-python scikit-learn
```

# How to Run the Program
To run the program, use the following command:

1. Open a terminal or command prompt.
2. Navigate to the directory where the program and dataset are located.
3. Run the following command:
```bash 
   python knn_classifier.py path/to/hhd_dataset
```
Replace ```path/to/hhd_dataset``` with the actual path to the Hindi Handwritten Digits dataset on your machine.
The program will then preprocess the images, split them into training, validation, and testing sets, train and evaluate the k-NN classifier, and report the results in the "results.txt" and "confusion.matrix.csv" files.

to get the hhd_dataset please enter to this link and download.

```
https://drive.google.com/file/d/1G7q2R4tLUlViQQLjgX1U2g-k5-aWz_Kn/view?usp=share_link
```
The program will preprocess the images in the dataset, split them into training, validation, and testing sets, train a k-NN classifier, evaluate its performance on the validation set, and select the optimal value of k. It will then evaluate the classifier's performance on the testing set and generate a confusion matrix. The results will be written to a file named results.txt and the confusion matrix will be written to a file named confusion.matrix.csv.

# References 

[I. Rabaev, B. Kurar Barakat, A. Churkin and J. El-Sana. The HHD Dataset. The 17 th International Conference on Frontiers in Handwriting
Recognition, pp. 228-233, 2020.](https://www.researchgate.net/publication/343880780_The_HHD_Dataset)
