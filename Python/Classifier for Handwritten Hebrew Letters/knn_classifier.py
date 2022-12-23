import os
import sys
import cv2
import csv
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix


# Set the directory where the folders are located
def preProcessing(path):
    root_directory = path
    # Use a for loop to iterate over the folders in the root directory
    for folder in os.listdir(root_directory):
        # Set the directory where the images are located
        if os.path.isdir(os.path.join(root_directory, folder)):
            directory = os.path.join(root_directory, folder)
            # Use a nested for loop to iterate over the images in the directory
            for filename in os.listdir(directory):
                # Read the image
                image = cv2.imread(os.path.join(directory, filename))

                # Convert the image to greyscale
                image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
                # Get the width and height of the image
                height, width = image.shape
                # Add white padding to the image as needed
                if width < height:
                    # Calculate the amount of padding needed
                    padding = (height - width) // 2
                    # Add padding to the left and right of the image
                    image = cv2.copyMakeBorder(image, 0, 0, padding, padding, cv2.BORDER_CONSTANT, value=255)
                else:
                    # Calculate the amount of padding needed
                    padding = (width - height) // 2
                    # Add padding to the top and bottom of the image
                    image = cv2.copyMakeBorder(image, padding, padding, 0, 0, cv2.BORDER_CONSTANT, value=255)

                # Resize the image to 32x32
                image = cv2.resize(image, (32, 32))

                # Binarize the image
                _, image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
                image = cv2.GaussianBlur(image, (3, 3), 0)

                # Save the modified image
                cv2.imwrite(os.path.join(directory, filename), image)
        else:
            continue

def spliting_to_groups():
    ratio = (0.8, 0.1, 0.1)
    root_directory = './hhd_dataset'
    # Set the directories for the training, validation, and testing sets
    training_directory = './training'
    validation_directory = './validation'
    testing_directory = './testing'

    # Use a for loop to iterate over the folders in the root directory
    for folder in os.listdir(root_directory):
        # Set the directory where the images are located
        if os.path.isdir(os.path.join(root_directory, folder)):
            directory = os.path.join(root_directory, folder)

            # Create an empty list to store the images and label
            images = []

            # Use a for loop to iterate over the images in the directory
            for filename in os.listdir(directory):
                # Read the image
                image = cv2.imread(os.path.join(directory, filename))

                # Extract the label from the filename
                label, rest = filename.split('_')[0], filename.split('_')[1]


                # Add the image and label to the list
                images.append((image, label, rest))

            # Divide the images into training, validation, and testing sets
            training_set, validation_set, testing_set = divide_images(images, ratio)

            # Save the resulting sets to separate directories
            for image, label, rest in training_set:
                cv2.imwrite(os.path.join(training_directory, label + '_' + rest), image)
            for image, label, rest in validation_set:
                cv2.imwrite(os.path.join(validation_directory, label + '_' + rest),
                            image)
            for image, label, rest in testing_set:
                cv2.imwrite(os.path.join(testing_directory, label + '_' + rest), image)
        else:
            continue

def divide_images(images, ratio):


    # Calculate the number of images in each group
    training_size = int(len(images) * ratio[0])
    validation_size = int(len(images) * ratio[1])
    testing_size = int(len(images) * ratio[2])

    # Initialize the training, validation, and testing sets
    training_set = []
    validation_set = []
    testing_set = []

    # Initialize counters for each group
    training_count = 0
    validation_count = 0
    testing_count = 0

    # Iterate over the images and divide them into the three groups
    for image in images:

        # Add the current image to the appropriate group based on the counters
        if training_count < training_size:
            training_set.append(image)
            training_count += 1
        elif validation_count < validation_size:
            validation_set.append(image)
            validation_count += 1
        elif testing_count < testing_size:
            testing_set.append(image)
            testing_count += 1

    # Return the training, validation, and testing sets
    return training_set, validation_set, testing_set


def learn_the_modal_print_result():

    X_train = []
    y_train = []
    for filename in os.listdir('./training'):
        # Read the image
        image = cv2.imread(os.path.join('./training', filename))
        # Extract the label from the filename
        label, _ = filename.split('_')[0], filename.split('_')[1]
        # Add the image and label to the training data and labels
        X_train.append(image.flatten())
        y_train.append(label)

    # Load the validation and testing data and labels
    X_val = []
    y_val = []


    for filename in os.listdir('./validation'):
        # Read the image
        image = cv2.imread(os.path.join('./validation', filename))
        # Extract the label from the filename
        label, _ = filename.split('_')[0], filename.split('_')[1]
        # Add the image and label to the validation data and labels
        X_val.append(image.flatten())
        y_val.append(label)

    X_test = []
    y_test = []

    for filename in os.listdir('./testing'):
        # Read the image
        image = cv2.imread(os.path.join('./testing', filename))
        # Extract the label from the filename
        label, _ = filename.split('_')[0], filename.split('_')[1]
        # Add the image and label to the testing data and labels
        X_test.append(image.flatten())
        y_test.append(label)

    # Try different values of k
    max_accuracy = 0
    optimal_k = 0
    for k in range(1, 15, 2):
        # Create a k-NN classifier
        knn = KNeighborsClassifier(n_neighbors=k, metric='euclidean')
        # Fit the classifier to the training data
        knn.fit(X_train, y_train)
        # Evaluate the accuracy on the validation data
        accuracy = knn.score(X_val, y_val)
        accuracy_rounded = round(accuracy * 100, 2)
        print(f"k = {k}: accuracy = {accuracy_rounded}")
        if accuracy > max_accuracy:
            max_accuracy = accuracy
            optimal_k = k

    print("optimal_k = ", optimal_k)
    # Train the k-NN classifier with the best value of k on the training data
    knn = KNeighborsClassifier(n_neighbors=optimal_k, metric='euclidean')
    knn.fit(X_train, y_train)

    accuracy = knn.score(X_test, y_test)
    print(f"Final accuracy on test set: {accuracy}")



    # Create a dictionary to store the label accuracies
    label_accuracies = {}
    labels = [str(i) for i in range(27)]
    # Iterate over the labels
    for label in labels:
        # Select the images and labels for this label
        images = [X_test[i] for i in range(len(X_test)) if y_test[i] == label]
        labels = [y_test[i] for i in range(len(y_test)) if y_test[i] == label]

        accuracy = knn.score(images, labels)

        # Add the accuracy to the dictionary
        label_accuracies[label] = accuracy

    # Open the file in write mode
    with open('results.txt', 'w') as file:
        # Write the optimal value of k
        file.write(f"k = {optimal_k}\n")
        # Write the label accuracies
        for label, accuracy in label_accuracies.items():
            accuracy_rounded = round(accuracy * 100, 2)
            file.write(f"{label}: {accuracy_rounded}%\n")

        # Calculate the predicted labels for the test set
        y_pred = knn.predict(X_test)

        # Calculate the confusion matrix
        confusion_mat = confusion_matrix(y_test, y_pred)
        labels = [str(i) for i in range(27)]
        # Write the confusion matrix to a file
        with open("confusion.matrix.csv", "w") as file:
            writer = csv.writer(file)
            writer.writerow(["true_label", "predicted_label", "count"])
            # Iterate over the rows and columns of the confusion matrix
            for i in range(len(labels)):
                for j in range(len(labels)):
                    # Write a row to the file
                    writer.writerow([labels[i], labels[j], confusion_mat[i][j]])


def main():
    path = sys.argv
    preProcessing(path[1])
    spliting_to_groups()
    learn_the_modal_print_result()



if __name__ == '__main__':
    main()