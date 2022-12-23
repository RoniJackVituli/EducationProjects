import sys
import cv2
import numpy as np
from operator import itemgetter

# check if we could open the img
def check_success(img):
    if img is None:
        print('error in reading the file')
        exit()


def sorte_points(boxPts):
    PointsX = sorted(boxPts, key=itemgetter(0))
    if PointsX[0][1] > PointsX[1][1]:
        down_left = PointsX[0]
        up_left = PointsX[1]
    else:
        down_left = PointsX[1]
        up_left = PointsX[0]

    if PointsX[2][1] > PointsX[3][1]:
        down_right = PointsX[2]
        up_right = PointsX[3]
    else:
        down_right = PointsX[3]
        up_right = PointsX[2]
    return [up_left, up_right, down_left, down_right]


def max_conturs_obj_in_img(cnts):
    max = 0
    index = 0
    for i in range(len(cnts)):
        size = len(cnts[i])
        if size > max:
            max = size
            index = i
    return index




def main():

    path = sys.argv
    img = cv2.imread(path[1])
    check_success(img)




    imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blur = cv2.blur(imgGray, (23,23))
    # ImgB - have background black and the obj is white.
    thres, imgB = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)  # find all contours in the image and draw them
    cv2.imwrite('./Output/binarization.jpg', imgB)
    ContourImgCyanBox = img.copy()
    minAreaRectImg = img.copy()
    # find only external contours in the image and draw them
    (cnts, _) = cv2.findContours(imgB, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    index = max_conturs_obj_in_img(cnts)

    cv2.drawContours(ContourImgCyanBox, cnts, index, (255, 255, 0), 20)
    cv2.imwrite('./Output/ContourImgCyanBox.jpg', ContourImgCyanBox)


    for i in range(len(cnts)):
        if i == index:
            box = cv2.minAreaRect(cnts[i])
            boxPts = np.int0(cv2.boxPoints(box))
            points = sorte_points(boxPts)
            width = points[1][0] - points[0][0]
            height = points[3][1] - points[1][1]
            if width > height:
                temp = height
                height = width
                width = temp
            cv2.drawContours(minAreaRectImg, [boxPts], -1, (0, 255, 0), 20)


    cv2.imwrite('./Output/minAreaRect.jpg', minAreaRectImg)
    print("COORDS = " , points)
    # Coordinates that you want to Perspective Transform
    pts1 = np.float32(points)
    # Size of the Transformed Image
    pts2 = np.float32([[0, 0], [width, 0], [0, height], [width, height]])
    M = cv2.getPerspectiveTransform(pts1, pts2)
    dst = cv2.warpPerspective(img, M, (width, height))

    cv2.imwrite(path[2], dst)


if __name__ == "__main__":
    main()

